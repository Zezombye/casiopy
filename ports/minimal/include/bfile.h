//---
//
//	gint core module: BFile interface
//
//	Syscall-based interface to the BFile driver (which I would never dare
//	to re-write considering how much the storage memory filesystem is an
//	awful mess).
//
//---

#ifndef	_BFILE_H
#define	_BFILE_H

/*
	BFile_Remove()
	Remove a file from the filesystem. The path must be encoded as two-byte
	fontcharacters!
*/
int BFile_Remove(const uint16_t *file);

/*
	BFile_Create()
	Creates an entry in the filesystem (two-byte fontcharacter path) of the
	given type. The size pointer must point to the file size for files, and
	may be NULL for folders.
*/
enum BFile_EntryType
{
	BFile_File	= 1,
	BFile_Folder	= 5,
};
int BFile_Create(const uint16_t *file, enum BFile_EntryType type, int *size);

/*
	BFile_Open()
	Opens an existing file (two-byte fontcharacter path) with the required
	mode, and returns a handle (positive integer) on success, or an
	negative integer on error.
*/
enum BFile_OpenMode
{
	BFile_ReadOnly	= 0x01,
	BFile_WriteOnly	= 0x02,
	BFile_ReadWrite	= BFile_ReadOnly | BFile_WriteOnly,
};
int BFile_Open(const uint16_t *file, enum BFile_OpenMode mode);

/*
	BFile_Close()
	Closes an open file.
*/
int BFile_Close(int handle);

/*
	BFile_Write()
	Writes data to a file. The data is taken from the second-argument
	buffer. The size to write is given as third argument.
	WARNING: Always write an even number of bytes or you're in for trouble!
*/
int BFile_Write(int handle, const void *ram_buffer, int even_size);

/*
	BFile_Read()
	Reads from an open file. The second and third arguments indicate where
	to store data and how much to read. The location from where the data is
	read depends on the value of `whence`:
	- If `whence` >= 0, it is considered as the absolute location (in
	  bytes) of the requested data in the file;
	- If `whence` == -1, BFile_Read() reads from the current virtual
	  position in the file.
*/
int BFile_Read(int handle, void *ram_buffer, int size, int whence);

#endif	// _BFILE_H
