/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013-2016 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <assert.h>
#include <fxlib.h>

#include "py/runtime.h"
#include "py/mperrno.h"
#include "py/reader.h"

int nbOpenedFiles = 0;
int openedFiles[] = {0};

typedef struct _mp_reader_mem_t {
    size_t free_len; // if >0 mem is freed on close by: m_free(beg, free_len)
    const byte *beg;
    const byte *cur;
    const byte *end;
} mp_reader_mem_t;

STATIC mp_uint_t mp_reader_mem_readbyte(void *data) {
    mp_reader_mem_t *reader = (mp_reader_mem_t*)data;
    if (reader->cur < reader->end) {
        return *reader->cur++;
    } else {
        return MP_READER_EOF;
    }
}

STATIC void mp_reader_mem_close(void *data) {
    mp_reader_mem_t *reader = (mp_reader_mem_t*)data;
    if (reader->free_len > 0) {
        m_del(char, (char*)reader->beg, reader->free_len);
    }
    m_del_obj(mp_reader_mem_t, reader);
}

void mp_reader_new_mem(mp_reader_t *reader, const byte *buf, size_t len, size_t free_len) {
    mp_reader_mem_t *rm = m_new_obj(mp_reader_mem_t);
    rm->free_len = free_len;
    rm->beg = buf;
    rm->cur = buf;
    rm->end = buf + len;
    reader->data = rm;
    reader->readbyte = mp_reader_mem_readbyte;
    reader->close = mp_reader_mem_close;
}

#if MICROPY_READER_POSIX

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct _mp_reader_posix_t {
    bool close_fd;
    int fd;
    size_t len;
    size_t pos;
    byte buf[20];
} mp_reader_posix_t;

STATIC mp_uint_t mp_reader_posix_readbyte(void *data) {
    mp_reader_posix_t *reader = (mp_reader_posix_t*)data;
    if (reader->pos >= reader->len) {
        if (reader->len == 0) {
            return MP_READER_EOF;
        } else {
            //int n = read(reader->fd, reader->buf, sizeof(reader->buf));
			int n = Bfile_ReadFile(reader->fd, reader->buf, sizeof(reader->buf), -1);
            if (n <= 0) {
                reader->len = 0;
                return MP_READER_EOF;
            }
            reader->len = n;
            reader->pos = 0;
        }
    }
    return reader->buf[reader->pos++];
}

STATIC void mp_reader_posix_close(void *data) {
    mp_reader_posix_t *reader = (mp_reader_posix_t*)data;
    if (reader->close_fd) {
        //close(reader->fd);
		Bfile_CloseFile(reader->fd);
    }
    m_del_obj(mp_reader_posix_t, reader);
}

void mp_reader_new_file_from_fd(mp_reader_t *reader, int fd, bool close_fd) {
    mp_reader_posix_t *rp = m_new_obj(mp_reader_posix_t);
    rp->close_fd = close_fd;
    rp->fd = fd;
    //int n = read(rp->fd, rp->buf, sizeof(rp->buf));
	int n = Bfile_ReadFile(rp->fd, rp->buf, sizeof(rp->buf), 0);
    if (n == -1) {
        if (close_fd) {
            //close(fd);
			Bfile_CloseFile(fd);
        }
        //mp_raise_OSError(errno);
        mp_raise_OSError(2);
    }
    rp->len = n;
    rp->pos = 0;
    reader->data = rp;
    reader->readbyte = mp_reader_posix_readbyte;
    reader->close = mp_reader_posix_close;
}

void closeAllFiles() {
	/*unsigned int key;
	char str[10] = {0};
	//tfp_sprintf(str, "%d", nbOpenedFiles);
	str[0] = '0' + nbOpenedFiles;
	locate(1,1); Print(str);
	GetKey(&key);*/
	for (int i = 0; i < nbOpenedFiles; i++) {
		Bfile_CloseFile(openedFiles[i]);
	}
}

void initNbOpenedFiles() {
	nbOpenedFiles = 0;
}

#if !MICROPY_VFS_POSIX
// If MICROPY_VFS_POSIX is defined then this function is provided by the VFS layer
void mp_reader_new_file(mp_reader_t *reader, const char *filename) {
    //int fd = open(filename, O_RDONLY, 0644);
	
	//Convert filename string to casio format
	FONTCHARACTER path[] = {'\\', '\\', 'f', 'l', 's', '0', '\\', 'C', 'A', 'S', 'I', 'O', 'P', 'Y', '\\',
	//bunch of 0's for the actual filename (13)
	0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	
	int i;
	for (i = 0; filename[i]; i++) {
		path[15+i] = filename[i];
	}
	
	for (int i = 15; path[i] != '.' && path[i] != '\0'; i++) {
		if (path[i] >= 'a' && filename[i] <= 'z') {
			path[i] -= 32;
		}
	}
	
	//Add .py to name if not already done
	if(!(strlen(filename) >= 3 && !strcmp(filename + strlen(filename) - 3, ".py"))) {
		path[i+0] = '.';
		path[i+1] = 'p';
		path[i+2] = 'y';
		path[i+3] = '\0';
	  }
	  
	
	//casiopy_print(path, strlen(path));
	if (nbOpenedFiles >= 20) {
		mp_raise_OSError(MP_EMFILE);
	}
	int fd = Bfile_OpenFile(path, _OPENMODE_READ);
    if (fd < 0) {
        //mp_raise_OSError(errno);
        mp_raise_OSError(2);
		Bfile_CloseFile(fd);
    }
	openedFiles[nbOpenedFiles] = fd;
	nbOpenedFiles++;
	//shell_print("1", 1);
    mp_reader_new_file_from_fd(reader, fd, true);
}
#endif

#endif
