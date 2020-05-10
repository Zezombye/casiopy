/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : fxlib.h                                         */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __FXLIB_H__
#define __FXLIB_H__

#include "dispbios.h"
#include "filebios.h"
#include "keybios.h"


// Prototypes

void Bdisp_AllClr_DD(void);
void Bdisp_AllClr_VRAM(void);
void Bdisp_AllClr_DDVRAM(void);
void Bdisp_AreaClr_DD(const DISPBOX *pArea);
void Bdisp_AreaClr_VRAM(const DISPBOX *pArea);
void Bdisp_AreaClr_DDVRAM(const DISPBOX *pArea);
void Bdisp_AreaReverseVRAM(int x1, int y1, int x2, int y2);
void Bdisp_GetDisp_DD(unsigned char *pData);
void Bdisp_GetDisp_VRAM(unsigned char *pData);
void Bdisp_PutDisp_DD(void);
void Bdisp_PutDispArea_DD(const DISPBOX *PutDispArea);
void Bdisp_SetPoint_DD(int x, int y, unsigned char point);
void Bdisp_SetPoint_VRAM(int x, int y, unsigned char point);
void Bdisp_SetPoint_DDVRAM(int x, int y, unsigned char point);
int  Bdisp_GetPoint_VRAM(int x, int y);
void Bdisp_WriteGraph_DD(const DISPGRAPH *WriteGraph);
void Bdisp_WriteGraph_VRAM(const DISPGRAPH *WriteGraph);
void Bdisp_WriteGraph_DDVRAM(const DISPGRAPH *WriteGraph);
void Bdisp_ReadArea_DD(const DISPBOX *ReadArea, unsigned char *ReadData);
void Bdisp_ReadArea_VRAM(const DISPBOX *ReadArea, unsigned char *ReadData);
void Bdisp_DrawLineVRAM(int x1, int y1, int x2, int y2);
void Bdisp_ClearLineVRAM(int x1, int y1, int x2, int y2);

void locate(int x, int y);
void Print(const unsigned char *str);
void PrintRev(const unsigned char *str);
void PrintC(const unsigned char *c);
void PrintRevC(const unsigned char *str);
void PrintLine(const unsigned char *str, int max);
void PrintRLine(const unsigned char *str, int max);
void PrintXY(int x, int y, const unsigned char *str, int type);
int PrintMini(int x, int y, const unsigned char *str, int type);
void SaveDisp(unsigned char num);
void RestoreDisp(unsigned char num);
void PopUpWin(int n);

int Bfile_OpenFile(const FONTCHARACTER *filename, int mode);
int Bfile_OpenMainMemory(const unsigned char *name);
int Bfile_ReadFile(int HANDLE, void *buf, int size, int readpos);
int Bfile_WriteFile(int HANDLE, const void *buf, int size);
int Bfile_SeekFile(int HANDLE, int pos);
int Bfile_CloseFile(int HANDLE);
int Bfile_GetMediaFree(enum DEVICE_TYPE devicetype, int *freebytes);
int Bfile_GetFileSize(int HANDLE);
int Bfile_CreateFile(const FONTCHARACTER *filename, int size);
int Bfile_CreateDirectory(const FONTCHARACTER *pathname);
int Bfile_CreateMainMemory(const unsigned char *name);
int Bfile_RenameMainMemory(const unsigned char *oldname, const unsigned char *newname);
int Bfile_DeleteFile(const FONTCHARACTER *filename);
int Bfile_DeleteDirectory(const FONTCHARACTER *pathname);
int Bfile_DeleteMainMemory(const unsigned char *name);
int Bfile_FindFirst(const FONTCHARACTER *pathname, int *FindHandle, FONTCHARACTER *foundfile, FILE_INFO *fileinfo);
int Bfile_FindNext(int FindHandle, FONTCHARACTER *foundfile, FILE_INFO *fileinfo);
int Bfile_FindClose(int FindHandle);

void Bkey_Set_RepeatTime(long FirstCount, long NextCount);
void Bkey_Get_RepeatTime(long *FirstCount, long *NextCount);
void Bkey_Set_RepeatTime_Default(void);
int GetKeyWait(int sel, int time, int menu, unsigned int *keycode);
int IsKeyDown(int keycode);
int IsKeyUp(int keycode);
int GetKey(unsigned int *keycode);

int SetTimer(int ID, int elapse, void (*hander)(void));
int KillTimer(int ID);
void Sleep(int millisecond);

void SetQuitHandler(void (*callback)(void));
int INIT_ADDIN_APPLICATION(int isAppli, unsigned short OptionNum);


#endif

#ifdef __cplusplus
}
#endif
