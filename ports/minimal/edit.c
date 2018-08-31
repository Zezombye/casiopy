// ----------------------------------------------------------------
// Text editor for Casio FX-9860G Ver 1.6

// ----------------------------------------------------------------
// Includes
#include <string.h>
#include <stdlib.h>
#include "fxlib.h"
#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include "console.h"
#include "math.h"
#include "font.h"
#include "menu.h"
#include "tinyprintf.h"
#include "i18n.h"
#include "MonochromeLib.h"

// ----------------------------------------------------------------
// Constants

// Text buffer size
#define MAXLINE    2048
#define TXTMINSIZE 4096
#define TXTMINCLIP 1024
#define MAXFNAME   13
#define MAXFNAMEMM 9
#define MAXPATH    50
#define MINFILES   32
#define MINFOLDERS 16
#define MAINHEADER 20
#define MAXCHARMAP 20

//Main memory directory functions
#define INITIALIZE   1
#define CHECKENTRY   2
#define CREATE       3
#define DELETE       4 
#define DELETEFOLDER 5 
#define FINDSTART    6
#define FINDGET      7 

//Special characters
#define ENDMARK   12
#define NEWLINECR 13
#define NEWLINELF 10
#define ARROWUP   "\xE6\x92"
#define ARROWDOWN "\xE6\x93"

//Explorer modes
#define EXPLOREROPEN 1
#define EXPLORERAUTO 2

//Application mode
#define EDITOR   1
#define EXPLORER 2
#define SHELL 3

//New line mode
#define NEWLMODELF   0 
#define NEWLMODECRLF 1

//Info bar mode
#define INFOBARFOLDER 1
#define INFOBARCURSOR 2

//Configuration file
#define CONFIGFILE  "EDIT.CFG"
#define MAINDIRFILE "EDIT.DIR"
#define MAINDIRTEMP "EDIT.TMP"

//Configuration options
#define CONFIGTRYSD  0
#define CONFIGHIDSYS 1
#define CONFIGNLMODE 2
#define CONFIGWWRAP  3
#define CONFIGDFRE   4
#define CONFIGDROO   5
#define CONFIGFONT   6
#define CONFIGINFO   7
#define CONFIGTEXTB  8
#define CONFIGCLIPB  9
#define CONFIGNFIL   10
#define CONFIGNFOL   11
#define CONFIGAOPEN  12
#define CONFIGAROOT  13
#define CONFIGANAME  14
#define CONFIGAFOLDR 15

//Cursor commands
#define CURSORTOP      1
#define CURSORBOTTOM   2
#define CURSORPAGEDOWN 3
#define CURSORPAGEUP   4
#define CURSORRIGHT    5
#define CURSORLEFT     6
#define CURSORDOWN     7
#define CURSORUP       8
#define CURSORHOME     9
#define CURSOREND     10
#define CURSORMARK    11
#define CURSORFIND    12

//Font contexts
#define CONTXEDITS 1 //Edit window small font
#define CONTXEDITT 2 //Edit window tall  font
#define CONTXEDITM 3 //Edit window medium font
#define CONTXEDITL 4 //Edit window large font

//Version
#define EDITVERSION "EDIT16"

//MainMemory check
#define FMAXLEN(s) (strcmp(s,"main")==0?MAXFNAMEMM-1:MAXFNAME-1)

char toupper2(char c)
{
    if(c >= 'a' && c <= 'z') {  //Only if it's a lower letter
          c -= 32;
    }
    return c;
}

char tolower2(char c)
{
    if(c >= 'A' && c <= 'Z') { 
          c += 32;
    }
    return c;
}

// ----------------------------------------------------------------
// Types



//Directory
struct Direc{
  char sCName[MAXFNAME];
  unsigned short iType;
  unsigned long iSize;
  unsigned char cSort;
  unsigned char cSystem;
};

//Directory file structure (main memory)
struct MainDir{
  char sName[MAXFNAMEMM];
  char sFolder[MAXFNAMEMM];
};

//Char map
struct CharMap{
  int iKey;
  char cAscii;
};

//Configuration settings
struct Config{
  char sVersion[8];                    //Version string
  int iTrySD;                          //Try SD card
  int iHideSysFiles;                   //Hide system files in file explorer
  int iNLMode;                         //New line mode
  int iWordWrap;                       //Word wrap enable
  int iDispFree;                       //Disp bytes free in explorer
  char sDefRoot[5];                    //Default root
  int iFont;                           //Text font
  int iInfo;                           //Info bar (1=Folder, 2=Cursor)
  int iAutoOpen;                       //Open file on application open
  char sAutoRoot[5];                   //Root drive for auto open
  char sAutoFile[MAXFNAME];            //File name for auto open
  char sAutoFolder[MAXFNAME];          //Folder name for auto open
  int iTextBuffer;                     //Text buffer size
  int iClipBuffer;                     //Clip buffer size
  int iMaxFiles;                       //Maximum files per directory
  int iMaxFolders;                     //Maximum number of total folders
  struct CharMap sCharMap[MAXCHARMAP]; //Char map
};

// ----------------------------------------------------------------
// Global variables
int key;
char _sRoot[5];          //Root directory
char _sFolder[MAXFNAME]; //Folder name
char _sFile[MAXFNAME];   //File name
char *_sText;            //Text buffer
char *_sClip;            //Clip buffer
int _iBinary;            //Binary file
int _iSaved;             //Saved file
int _iNewFile;           //New file flag
struct Config _sConfig;  //Configuration variables
int _iTextSize;          //Text buffer size
int _iClipSize;          //Clip buffer size
int _iAppMode;           //Application mode
struct Direc *_sFiles;   //File directory
struct Direc *_sFolders; //Folder directory

// ----------------------------------------------------------------
// Prototypes
int Editor(char *,char *,char *,int,struct Config *);
char BindCharHandle(struct Config *);
void QuitHandler(void);
int SDCardPresent(void);
void MoveCursor(int*, int,int,int *,int *,int *,int*, int *,int *,int,int *,char *,int);
void PrintFileName(char *,char *,int,int);
void PrintInfoBar(char *,int,int,struct Config *);
void PrintLineNumber(int,int);
void DumpTextLines(char *,int *,int, int,int,int,int,int);
void CalcLines(char *,int *,int *,int,int,struct Config *);
int LineLength(int,char *,int *,int);
int MainDirectory(int,char *,char *);
void ReadDirectory(char *,char *,struct Direc *,int *,int,unsigned char,int,int);
int Explorer(int,char *, char *, char *,struct Config *,int *);
void AppendDirEntry(int,struct Direc *,struct Direc *);
void PrintFileEntry(int,int,int,int,struct Direc *,int);
int GetFolder(char *,char *,struct Config *);
void PrintFolderEntry(int ,struct Direc *, int);
void Configuration(struct Config *);
void PrintConfigEntry(int,int,struct Config *,int);
void ConfigExport(struct Config *);
void ConfigImport(struct Config *);
char *Font2Char(FONTCHARACTER *,char *);
FONTCHARACTER *Char2Font(char *,FONTCHARACTER *);
FONTCHARACTER *FilePath(char *,char *,char *,FONTCHARACTER *);
int FolderExist(char *,char *,struct Config *);
int FileExist(char *,char *,char *);
int ReadFile(char *,char *,char *,char *, int *);
int WriteFile(char *,char *,char *,char *,int);
int CopyFile(char *,char *,char *,char *,char *,char *);
int DeleteFile(char *,char *,char *);
void ConvertNewLine2CRLF(char *);
void ConvertNewLine2LF(char *);
int PopupContinueYesNo(char *,char *,char *);
void PopupMessage(int,char *,char *,char *,char *,char*);
void PopupMemory(struct Config *);
int GetFileName(char *,int, char);
int GetFolderName(char *);
int GetSearchString(char *);
//void HelpText(void);
void SetEditorFont(int,int *);
void AboutPopup(void);
char CharacterSelect(int,struct Config *);
void Rectangle(int,int,int,int,int);

// ---------------------------------------------------------------
// Main program
int edit_main()
{
    //Variables
    int iAuto;                   //Auto Open file
    int iNew;                    //New file flag
    struct Config sConfig;       //Configuration variables
    char sRoot[5];               //Root directory
    char sFolder[MAXFNAME]="CasioPy";   //Folder name
    char sFile[MAXFNAME]="";     //File name
    
    //Initializations
    Bdisp_AllClr_DDVRAM();
    MenuInitialize();
    MainDirectory(INITIALIZE,"","");
    DefineFontContext(CONTXEDITS,FONTS,COLNOR,1,2);
    DefineFontContext(CONTXEDITT,FONTT,COLNOR,1,0);
    DefineFontContext(CONTXEDITM,FONTM,COLNOR,1,0);
    DefineFontContext(CONTXEDITL,FONTL,COLNOR,0,0);
    
    //Import Configuration file
    ConfigImport(&sConfig);
    
    //Default root
    strcpy(sRoot,sConfig.sDefRoot);
    
    //Allocate memory for text buffer
    _sText=(char *)malloc(sConfig.iTextBuffer+MAXLINE);
    if(_sText==NULL) 
    {
      PopupMessage(1,"Not enough memory","for text buffer.","Minimum size set.","Restart program!",NULL);
      sConfig.iTextBuffer=TXTMINSIZE;     
      ConfigExport(&sConfig);
      goto terminate;
    }
    _iTextSize=sConfig.iTextBuffer;
    memset(_sText,0,_iTextSize);
    
    //Allocate memory for clip buffer
    _sClip=(char *)malloc(sConfig.iClipBuffer);
    if(_sClip==NULL) 
    {
      PopupMessage(1,"Not enough memory","for clip buffer.","Minimum size set.","Restart program!",NULL);
      sConfig.iClipBuffer=TXTMINCLIP;     
      ConfigExport(&sConfig);
      goto terminate;
    }
    _iClipSize=sConfig.iClipBuffer;
    memset(_sClip,0,_iClipSize);
    
    //Allocate memory for file directory buffer
    _sFiles=(struct Direc *)malloc(sConfig.iMaxFiles*sizeof(struct Direc));
    if(_sFiles==NULL) 
    {
      PopupMessage(1,"Not enough memory","for file buffer.","Minimum size set.",
                     "Restart program!",NULL);
      sConfig.iMaxFiles=MINFILES;     
      ConfigExport(&sConfig);
      goto terminate;
    }
    
    //Allocate memory for folder directory buffer
    _sFolders=(struct Direc *)malloc(sConfig.iMaxFolders*sizeof(struct Direc));
    if(_sFolders==NULL) 
    {
      PopupMessage(1,"Not enough memory","for folder buffer","Minimum size set.",
                     "Restart program!",NULL);
      sConfig.iMaxFolders=MINFOLDERS;     
      ConfigExport(&sConfig);
      goto terminate;
    }
    
    
    //Auto open file
    if(sConfig.iAutoOpen==1)
    {
      sprintf(sRoot,sConfig.sAutoRoot);
      sprintf(sFile,sConfig.sAutoFile);
      sprintf(sFolder,sConfig.sAutoFolder);
      Editor(sRoot,sFolder,sFile,0,&sConfig);
    }
    
    //Main loop
    do{
	  //locate(1,1); Print("a"); GetKey(&key);
	  
      //Select file
      Explorer(EXPLOREROPEN,sRoot,sFolder,sFile,&sConfig,&iNew);
      
      //Start editor
      Editor(sRoot,sFolder,sFile,iNew,&sConfig);
      
    }while(1);
    
    //Application must be restarted 
    terminate:
    Bdisp_AllClr_DDVRAM();
	
    //Set quit handler
    QuitHandler();   
    return(1);
}

#define insertChar(cChr) \
iLen=strlen(sText);\
if(cChr!=0 && iLen<_iTextSize)\
{\
	MoveCursor(&tabIndentForCurrentLine, CURSORMARK,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);\
	iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;\
	for(i=iLen+1;i>iPtr;i--) sText[i]=sText[i-1];\
	sText[iPtr]=cChr;\
	CalcLines(sText,iLines,&iLNum,iTopLine,iCntx,sConfig);\
	MoveCursor(&tabIndentForCurrentLine, CURSORFIND,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);\
	MoveCursor(&tabIndentForCurrentLine, CURSORRIGHT,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);\
	iSaved=0;\
	iRefresh=1;\
}

// ----------------------------------------------------------------
// Text editor
int Editor(char *sRoot, char *sFolder, char *sFile, 
           int iNew, struct Config *sConfig)
{
    //Variables
    int i;                       //Counter
    int iExit;                   //Exit flag
    int iCode;                   //Menu code 
    int iCx=0,iCy=1;             //Cursor position
    int iACx=0,iACy=0;           //Previous cursor position
    int iColumn=0;               //Column for cursor movements
    int iLen;                    //Text length
    int iLn2;                    //Text length
    int iTxtPtr=0;               //Text pointer
    int iTopLine=0;              //Text top line
	int leftMostColumn = 0;
    int iMaxPtr;                 //Maximum text pointer value
    int iRefresh=0;              //Refresh screen
    int iPtr;                    //Pointer
    int iBinary=0;               //Binary file
    int iLNum;                   //Text lines
    int iASaved=0;               //Saved file (previous status)
    int iSaved=0;                //Saved file
    int iNewFile;                //New file flag
    int iLines[MAXLINE];         //Text line positions
    int iAnswer;                 //User answer
    int iStart=0;                //Clip start
    int iEnd=0;                  //Clip end
    int iAEnd=-1;                //Clip end (previous position)
    int iClipMode=0;             //Clip mode
    int iCopy;                   //Text copied to clipboard
    int iCntx;                   //Font context for edit window
    int iAFont;                  //Previous font
    int iAWWrap;                 //Previous word wrap mode
    int iFound;                  //Found string
    int iEqual;                  //Equal flag
    int iKey;           //Keyboard code
	int tabIndentForCurrentLine = 0;
    char cChr;                   //Character
    char sRootAux[5]="fls0";     //Root directory (aux)
    char sFolderAux[MAXFNAME]="";//Folder name (aux)
    char sFileAux[MAXFNAME]="";  //File name (aux)
    char sString[16]="";         //Search string
    char *sText;                 //Text buffer
    char *sClip;                 //Clip buffer
	
    //Get Key
	char strKey[50] = {0};
    
    //Application mode
    _iAppMode=EDITOR;
          
    //Global pointers
    sText=_sText;
    sClip=_sClip;
    iNewFile=iNew;
    if(strlen(sClip)>0) 
      iCopy=1; 
    else 
      iCopy=0;
    
    //Load file
    if(iNewFile==1)
    {
      sText[0]=ENDMARK; sText[1]=0;
      iNewFile=1;
      iSaved=0;
    }
    else
    {
      if(ReadFile(sRoot,sFolder,sFile,sText,&iBinary)==1)
      {
        iSaved=1;
        iNewFile=0;
      }
      else
      {
        PopupMessage(1,"File open error!",NULL,NULL,NULL,NULL);
        return(0);
      }
    }
    
    //Initializations
    Bdisp_AllClr_DDVRAM();
    SetEditorFont(sConfig->iFont,&iCntx);
    MenuSetBar(MENUBARMAIN);
    PrintFileName(sRoot,sFile,iBinary,iSaved);
    PrintKeyboardStatus();
    CalcLines(sText,iLines,&iLNum,0,iCntx,sConfig);
    DumpTextLines(sText,iLines,iLNum,iTopLine,leftMostColumn, iStart,iEnd,iCntx);
    PrintInfoBar(sFolder,iCx+leftMostColumn,iCy+iTopLine,sConfig);
    SetFontContext(iCntx);
    SetCursor(iCx,iCy,1,iClipMode);
    KeyboardStatusHideStore();
    KeyboardStatusHide(0);
    Bdisp_PutDisp_DD();
    
    //Main loop
    iExit=0;
    do{
      
      //Inititializations
      iRefresh=0;
      iACx=iCx;
      iACy=iCy;
      iAEnd=iEnd;
      iASaved=iSaved;
      SetFontContext(iCntx);
      
      //Set global variables for quit handler
      _iBinary=iBinary;
      _iSaved=iSaved;
      _iNewFile=iNewFile;
      strcpy(_sRoot,sRoot);
      strcpy(_sFolder,sFolder);
      strcpy(_sFile,sFile);
      memcpy(&_sConfig,sConfig,sizeof(struct Config));      
      
	  
      iKey=waitForKey(strKey);
      
      //Get menu commands
      if(iKey==KEY_CTRL_F1 || iKey==KEY_CTRL_F2
      || iKey==KEY_CTRL_F3 || iKey==KEY_CTRL_F4
      || iKey==KEY_CTRL_F5 || iKey==KEY_CTRL_F6)
        iKey=-MenuFunctionKey(iKey);
      
	  //If in clipboard mode, DEL doesn't print \b but deletes selected text
	  if (iClipMode==1 && iKey == KEY_CTRL_DEL) {
		iKey = -NODEEDITDEL;
	  }
	  
      //Process keys
      switch(iKey)
      {
		  
		  
        //Character selection
        case -NODECHARSEL:
          
          //Do not insert characters in clip mode
          if(iClipMode==1) break;
      
          //Get character
          cChr=CharacterSelect(1,sConfig);
      
          //Insert character into text
          iLen=strlen(sText);
          if(cChr!=0 && iLen<_iTextSize)
          {
            MoveCursor(&tabIndentForCurrentLine, CURSORMARK,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
            iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
            for(i=iLen+1;i>iPtr;i--) sText[i]=sText[i-1];
            sText[iPtr]=cChr;
            CalcLines(sText,iLines,&iLNum,iTopLine,iCntx,sConfig);
            MoveCursor(&tabIndentForCurrentLine, CURSORFIND,1,&iCx,&iCy,&iTopLine,&leftMostColumn, &iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
            MoveCursor(&tabIndentForCurrentLine, CURSORRIGHT,1,&iCx,&iCy,&iTopLine,&leftMostColumn, &iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
            iSaved=0;
          }
          iRefresh=2;
          break;
        
        //Help text
        case -NODEHELPHELP: 
          /*HelpText();
          MenuFunctionKey(KEY_CTRL_EXIT);
          iRefresh=2;*/
          break;
          
        //About
        case -NODEHELPABOU: 
          AboutPopup();
          break;
        
        //Memory status
        case -NODEHELPMEMO: 
          PopupMemory(sConfig);
          break;
        
        //Change upper/lower case
        case -NODEALPHA: 
          KeyboardStatusChangeCase();
          break;
        
        //Go to top
        case -NODEGOTOTOP: 
          MoveCursor(&tabIndentForCurrentLine, CURSORTOP,1,&iCx,&iCy,&iTopLine,&leftMostColumn, &iColumn,
                     &iRefresh,iLNum,iLines,sText,iCntx);
          break;
        
        //Go to bottom
        case -NODEGOTOBTM: 
          MoveCursor(&tabIndentForCurrentLine, CURSORBOTTOM,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,
                     &iRefresh,iLNum,iLines,sText,iCntx);
          break;
          
        //Cursor home
		case KEY_CTRL_HOME:
        case -NODEGOTOHOME: 
          MoveCursor(&tabIndentForCurrentLine, CURSORHOME,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,
                     &iRefresh,iLNum,iLines,sText,iCntx);
          break;

        //Cursor end
		case KEY_CTRL_END:
        case -NODEGOTOEND: 
          MoveCursor(&tabIndentForCurrentLine, CURSOREND,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,
          &iRefresh,iLNum,iLines,sText,iCntx);
          break;
      
        //Page up
		case KEY_CTRL_PAGEUP:
        case -NODEGOTOPGU: 
          MoveCursor(&tabIndentForCurrentLine, CURSORPAGEUP,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,
                     &iRefresh,iLNum,iLines,sText,iCntx);
          break;

        //Page down
		case KEY_CTRL_PAGEDOWN:
        case -NODEGOTOPGD: 
          MoveCursor(&tabIndentForCurrentLine, CURSORPAGEDOWN,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,
          &iRefresh,iLNum,iLines,sText,iCntx);
          break;
      
        //Clip mode on / off
        case KEY_CTRL_CLIP:
        case -NODEEDITCLIP:
          if(iKey==KEY_CTRL_CLIP)
          {
            while(MenuGetBar()!=MENUBARMAIN) MenuFunctionKey(KEY_CTRL_EXIT);
            MenuFunctionKey(KEY_CTRL_F2);
          }
          if(iClipMode==0)
          {
            iClipMode=1;
            iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
            iStart=iPtr;
            iEnd=iPtr;
            iRefresh=1;
          }
          else
          {
            iClipMode=0;
            iStart=0;
            iEnd=0;
            iAEnd=-1;
            iRefresh=1;
          }
          break; 
        
        //Paste
        case KEY_CTRL_PASTE:
        case -NODEEDITPAST:
          if(iCopy==1)
          {
            iLen=strlen(sText);
            iLn2=strlen(sClip);
            if(iLen+iLn2<_iTextSize)
            {
              MoveCursor(&tabIndentForCurrentLine, CURSORMARK,iLn2,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
              iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
              for(i=iLen+iLn2;i>iPtr;i--) sText[i]=sText[i-iLn2];
              for(i=0;i<iLn2;i++) sText[iPtr+i]=sClip[i];
              CalcLines(sText,iLines,&iLNum,iTopLine,iCntx,sConfig);
              MoveCursor(&tabIndentForCurrentLine, CURSORFIND,iLn2,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
              MoveCursor(&tabIndentForCurrentLine, CURSORRIGHT,iLn2,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
              iSaved=0;
              iRefresh=1;
            }
            else
              PopupMessage(1,"Not pasted.","Buffer overflow!",NULL,NULL,NULL);
          }
          else
            PopupMessage(1,"Clipboard empty!",NULL,NULL,NULL,NULL);
          break;

        //Copy & Cut & Delete
        case -NODEEDITCOPY:
        case -NODEEDITCUT:
        case -NODEEDITDEL:
          
          //Copy
          if(iKey==-NODEEDITCOPY || iKey==-NODEEDITCUT)
          {
            if(iClipMode==1 && iStart!=iEnd)
            {
              if(abs(iEnd-iStart)<_iClipSize)
              {
                if(iStart<iEnd)
                {
                  iPtr=iStart;
                  for(i=0;i<iEnd-iStart;i++)
                  {
                    sClip[i]=sText[iPtr];
                    iPtr++;
                   }
                 }
                else
                {
                  iPtr=iEnd;
                  for(i=0;i<iStart-iEnd;i++)
                  {
                    sClip[i]=sText[iPtr];
                    iPtr++;
                  }
                }
                sClip[i]=0;
                iCopy=1;
                if(iKey==-NODEEDITCOPY)
                {
                  iClipMode=0;
                  iStart=0;
                  iEnd=0;
                }
                iRefresh=1;
              }
              else
              {
                PopupMessage(1,"Selected text","is bigger than","clip buffer!",NULL,NULL);
                iKey=0;
              }
            }
            else
              PopupMessage(1,"No text selected!",NULL,NULL,NULL,NULL);
          }
        
          //Delete selected text
          if(iKey==-NODEEDITCUT || iKey==-NODEEDITDEL)
          {
            if(iClipMode==1 && iStart!=iEnd)
            {
              iLen=strlen(sText);
              if(iStart<iEnd)
              {
                MoveCursor(&tabIndentForCurrentLine, CURSORLEFT,iEnd-iStart,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
                MoveCursor(&tabIndentForCurrentLine, CURSORMARK,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
                for(i=iStart;i<iLen;i++) sText[i]=sText[i+iEnd-iStart];
              }
              else if(iStart>iEnd)
              {
                MoveCursor(&tabIndentForCurrentLine, CURSORMARK,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
                for(i=iEnd;i<iLen;i++) sText[i]=sText[i+iStart-iEnd];
              }
              CalcLines(sText,iLines,&iLNum,iTopLine,iCntx,sConfig);
              MoveCursor(&tabIndentForCurrentLine, CURSORFIND,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
              iClipMode=0;
              iStart=0;
              iEnd=0;
              iRefresh=1;
              iSaved=0;
            }
            else
            {
              if(iKey==-NODEEDITDEL) PopupMessage(1,"No text selected!",NULL,NULL,NULL,NULL);
            }
          }
          break;
      
        //Search for string
        case -NODEEDI2SRC1: 
        case -NODEEDI2SRCN: 
          if(iKey==-NODEEDI2SRC1)
          {
            iAnswer=GetSearchString(sString);
          }
          else
          {
            MoveCursor(&tabIndentForCurrentLine, CURSORRIGHT,1,&iCx,&iCy,&iTopLine,&leftMostColumn,
            &iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
            iAnswer=1;
          }
          if(iAnswer==1)
          {
            PopupMessage(0,"Searching...",NULL,NULL,NULL,NULL);
            iFound=0;
            iLen=strlen(sText);
            iLn2=strlen(sString);
            iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
            while(iFound==0 && iPtr<iLen-1)
            {
              iEqual=1;
              for(i=0;i<iLn2;i++) 
                if(sText[iPtr+i]!=sString[i]) iEqual=0;
              if(iEqual==0)
              {
                MoveCursor(&tabIndentForCurrentLine, CURSORRIGHT,1,&iCx,&iCy,&iTopLine,&leftMostColumn,
                &iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
                iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
              }
              else
                iFound=1;
            }
          }
          if(iFound==0) PopupMessage(1,"Not found!",NULL,NULL,NULL,NULL);
          iRefresh=1;
          break;
        
		case -NODEEXPLEXE:
			
			if(iBinary==0)
			{ 
				if(iSaved==0)
				{
				  iAnswer=1;
				  if(iNewFile==1)
				  {
					if(FileExist(sRoot,sFolder,sFile)==1)
					  iAnswer=PopupContinueYesNo(STR_FILEEXISTS,STR_CONTINUE,NULL);
				  }  
				  if(iAnswer==1)
				  {
					if(WriteFile(sRoot,sFolder,sFile,sText,sConfig->iNLMode)==1)
					{
					  MenuFunctionKey(KEY_CTRL_EXIT);
					  iRefresh=2;
					  iSaved=1;
					  iNewFile=0;
					}
					else
					  PopupMessage(1,STR_FILEWRITEERROR,NULL,NULL,NULL,NULL);
				  }
				}
			} else {
				PopupMessage(1,"Binary files can","not be modified.",NULL,NULL,NULL);
			}
			
			mpy_main(sText);
			iRefresh = 2;
			//PopupMessage(1,"wesh","maggle",NULL,NULL,NULL);
			
			break;
		
        //Save file
        case -NODEFILESAVE: 
          if(iBinary==0)
          { 
            if(iSaved==0)
            {
              iAnswer=1;
              if(iNewFile==1)
              {
                if(FileExist(sRoot,sFolder,sFile)==1)
                  iAnswer=PopupContinueYesNo(STR_FILEEXISTS,STR_CONTINUE,NULL);
              }  
              if(iAnswer==1)
              {
                if(WriteFile(sRoot,sFolder,sFile,sText,sConfig->iNLMode)==1)
                {
                  MenuFunctionKey(KEY_CTRL_EXIT);
                  iRefresh=2;
                  iSaved=1;
                  iNewFile=0;
                }
                else
                  PopupMessage(1,STR_FILEWRITEERROR,NULL,NULL,NULL,NULL);
              }
            }
            else
              PopupMessage(1,"Already saved!",NULL,NULL,NULL,NULL);
          }
          else
            PopupMessage(1,"Binary files can","not be modified.",NULL,NULL,NULL);
          break;
        
        //Save as
        case -NODEFILESVAS: 
          if(GetFolder(sRootAux,sFolderAux,sConfig))
          {
            strcpy(sFileAux,sFile);
            if(GetFileName(sFileAux,FMAXLEN(sRootAux), 0))
            {
              if(FileExist(sRootAux,sFolderAux,sFileAux)==1)
                iAnswer=PopupContinueYesNo("File exists.","Overwrite?",NULL);
              else
                iAnswer=1;
              if(iAnswer==1)
              {
                if(WriteFile(sRootAux,sFolderAux,sFileAux,sText,sConfig->iNLMode)==1)
                {
                  strcpy(sRoot,sRootAux);
                  strcpy(sFolder,sFolderAux);
                  strcpy(sFile,sFileAux);
                  MenuFunctionKey(KEY_CTRL_EXIT);
                  iSaved=1;
                  iNewFile=0;
                }
                else
                  PopupMessage(1,"File write error!",NULL,NULL,NULL,NULL);
              }
            }
          }
          iRefresh=2;
          break;
       
        //Set auto file
        case -NODEFILEAUTO: 
          if(iNewFile==1 || iSaved==0)
          {
            PopupMessage(1,"Save file first!",NULL,NULL,NULL,NULL);
          }
          else
          {
            sprintf(sConfig->sAutoRoot,sRoot);
            sprintf(sConfig->sAutoFile,sFile);
            sprintf(sConfig->sAutoFolder,sFolder);
            sConfig->iAutoOpen=1;
            ConfigExport(sConfig);
            PopupMessage(1,"Current file will",
                           "be opened next   ",
                           "time the editor  ",
                           "is started.      ", 
                           NULL);
            MenuFunctionKey(KEY_CTRL_EXIT);
          }
          break;
        
        //Attend exit key (must be outside of switch)
        
		case KEY_CTRL_EXIT:
			
		  if (iClipMode == 1) {
			iClipMode=0;
            iStart=0;
            iEnd=0;
            iAEnd=-1;
            iRefresh=1;
		  }
		
          if(MenuGetBar()==MENUBARMAIN)
          { 
            if(iSaved==0)
            {
              if(sText[0]==ENDMARK)
                iAnswer=1;
              else
                iAnswer=PopupContinueYesNo("File not saved.","Ignore changes?",NULL);
            }
            if(iSaved==1 || (iSaved==0 && iAnswer==1)) iExit=1;
          }
          else 
            MenuFunctionKey(iKey);
          break;
          
        //Set up
        case -NODEHELPOPTN:
        case KEY_CTRL_SETUP:
          iAFont=sConfig->iFont;
          iAWWrap=sConfig->iWordWrap;
          Configuration(sConfig);
          if(iAFont!=sConfig->iFont)
          {
            SetEditorFont(sConfig->iFont,&iCntx);
            SetFontContext(iCntx);
            iTopLine=0; iColumn=0; iCx=0; iCy=1;
            CalcLines(sText,iLines,&iLNum,iTopLine,iCntx,sConfig);
            iClipMode=0;
            iStart=0;
            iEnd=0;
            iAEnd=-1;
          }
          if(iAWWrap!=sConfig->iWordWrap)
          {
            iTopLine=0; iColumn=0; iCx=0; iCy=1;
            CalcLines(sText,iLines,&iLNum,iTopLine,iCntx,sConfig);
            iClipMode=0;
            iStart=0;
            iEnd=0;
            iAEnd=-1;
          }
          MenuFunctionKey(KEY_CTRL_EXIT);
          iRefresh=2;
          break;
        
        //Cursor x++
        case KEY_CTRL_RIGHT: 
          MoveCursor(&tabIndentForCurrentLine, CURSORRIGHT,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,
          &iRefresh,iLNum,iLines,sText,iCntx);
          break;
          
        //Cursor x--
        case KEY_CTRL_LEFT: 
          MoveCursor(&tabIndentForCurrentLine, CURSORLEFT,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,
          &iRefresh,iLNum,iLines,sText,iCntx);
          break;
          
        //Cursor y++
        case KEY_CTRL_DOWN:  
          MoveCursor(&tabIndentForCurrentLine, CURSORDOWN,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,
          &iRefresh,iLNum,iLines,sText,iCntx);
          break;
          
        //Cursor y--
        case KEY_CTRL_UP:    
          MoveCursor(&tabIndentForCurrentLine, CURSORUP,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,
          &iRefresh,iLNum,iLines,sText,iCntx);
          break;
          
        //Delete fowards
        case KEY_CTRL_AC: 
          
          //Do not delete in clip mode
          if(iClipMode==1) break;
          
          //Mark cursor position
          MoveCursor(&tabIndentForCurrentLine, CURSORMARK,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
          
          //Delete character from text
          iLen=strlen(sText);
          iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
          if(iPtr<iLen-1)
          {
            for(i=iPtr;i<iLen;i++) sText[i]=sText[i+1];
            CalcLines(sText,iLines,&iLNum,iTopLine,iCntx,sConfig);
          }
          MoveCursor(&tabIndentForCurrentLine, CURSORFIND,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
          iColumn=iCx;
          iRefresh=1;
          iSaved=0;
          break;
        
        //Print characters
        default: 
			/*Do not insert characters in clip mode*/
			if(iClipMode==1) break;
			
			if (-iKey >= NODEPRGM0) {
		
				//Find the menu text and put it instead of str
				
				int node = (-iKey - NODEPRGM0)%6;
				int mBar = MENUBARPRGM0 + (-iKey-NODEPRGM0)/6;
				extern struct MNode _sMNode[MAXMENUBARS][MAXMENUNODE];

				strcpy(strKey, _sMNode[mBar][node].outputText);
			
			}
			
			int charsAfterCursorCounter = 0;
			char countCharsAfterCursor = 0;
			
			for (int j = 0; strKey[j]; j++) {
				cChr = strKey[j];
				
				if (cChr == '\a') {
					countCharsAfterCursor = 1;
					continue;
					
				} else if (cChr == '\b') {
					if(iLines[iTopLine+iCy-1]+iCx+leftMostColumn==0) {
						//Mark cursor position
						MoveCursor(&tabIndentForCurrentLine, CURSORMARK,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);

						//Delete character from text
						iLen=strlen(sText);
						iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
						if(iPtr<iLen-1)
						{
						for(i=iPtr;i<iLen;i++) sText[i]=sText[i+1];
						CalcLines(sText,iLines,&iLNum,iTopLine,iCntx,sConfig);
						}
						MoveCursor(&tabIndentForCurrentLine, CURSORFIND,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
						iColumn=iCx;
						iRefresh=1;
						iSaved=0;
						break;
					}
					  
					MoveCursor(&tabIndentForCurrentLine, CURSORLEFT,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
					MoveCursor(&tabIndentForCurrentLine, CURSORMARK,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
					  
					iLen=strlen(sText);
					iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
					
					char isSpace = 0;
					if (iPtr < iLen-1) isSpace = sText[iPtr] == ' ';
					  
					if(iPtr<iLen-1)
					{
						for(i=iPtr;i<iLen;i++) sText[i]=sText[i+1];
						CalcLines(sText,iLines,&iLNum,iTopLine,iCntx,sConfig);
					}
					iColumn=iCx;
					MoveCursor(&tabIndentForCurrentLine, CURSORFIND,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
					iRefresh=1;
					iSaved=0;
					
					if (countCharsAfterCursor) {
						charsAfterCursorCounter--;
					}
					  
					if (isSpace && iPtr > 0 && sText[iPtr-1] == ' ' && (iCx+leftMostColumn)%2 == 1) {
						MoveCursor(&tabIndentForCurrentLine, CURSORLEFT,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
						MoveCursor(&tabIndentForCurrentLine, CURSORMARK,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
						  
						iLen=strlen(sText);
						iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
						  
						if(iPtr<iLen-1)
						{
							for(i=iPtr;i<iLen;i++) sText[i]=sText[i+1];
							CalcLines(sText,iLines,&iLNum,iTopLine,iCntx,sConfig);
						}
						iColumn=iCx;
						MoveCursor(&tabIndentForCurrentLine, CURSORFIND,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
						iRefresh=1;
						iSaved=0;
						if (countCharsAfterCursor) {
							charsAfterCursorCounter--;
						}
					}
										
				} else {
					
					int nbIndents = tabIndentForCurrentLine;
				
					//Increase number of indents if current character is ':'
					iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
					if (iPtr > 0 && sText[iPtr-1] == ':') nbIndents++;
					
					if (cChr == '\r') cChr = '\n';
					
					insertChar(cChr);
					
					int j = 0;
					if (cChr == '\n') {
						for (j = 0; j < nbIndents*2; j++) {
							insertChar(' ');
						}
					}
					
					if (countCharsAfterCursor) {
						charsAfterCursorCounter += j+1;
					}
				}
								
				
			}
			
			for (int j = 0; j < charsAfterCursorCounter; j++) {
				MoveCursor(&tabIndentForCurrentLine, CURSORLEFT,1,&iCx,&iCy,&iTopLine,&leftMostColumn,&iColumn,&iRefresh,iLNum,iLines,sText,iCntx);
			}
          
          break;
      }     
	  
	  

      //Calculate clip ending
      if(iClipMode==1)
      {
        iEnd=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
        if(iEnd!=iAEnd) iRefresh=1;
      }
      
      //Soft refresh (only text)
      if(iRefresh==1)
      {
		  
        //PrintKeyboardStatus();
        DumpTextLines(sText,iLines,iLNum,iTopLine, leftMostColumn,iStart,iEnd,iCntx);
        Bdisp_PutDisp_DD();
      }
      
      //Hard refresh (all)
      if(iRefresh==2)
      {
        Bdisp_AllClr_DDVRAM();
        MenuSetBar(MENUBARMAIN);
        PrintFileName(sRoot,sFile,iBinary,iSaved);
        PrintInfoBar(sFolder,iCx+leftMostColumn,iCy+iTopLine,sConfig);
        //PrintInfoBar(sFolder,tabIndentForCurrentLine,iCy+iTopLine,sConfig);
        //PrintKeyboardStatus();
        DumpTextLines(sText,iLines,iLNum,iTopLine, leftMostColumn,iStart,iEnd,iCntx);
        Bdisp_PutDisp_DD();
      }

      //Update cursor position
      if(iACx!=iCx || iACy!=iCy || iRefresh!=0)
      {
        SetFontContext(iCntx);
        if(iClipMode==0 || (iClipMode==1 && iACx==0) )
          SetCursor(iACx,iACy,0,0);
        SetCursor(iCx,iCy,1,iClipMode);
        PrintInfoBar(sFolder,iCx+leftMostColumn,iCy+iTopLine,sConfig);
        //PrintInfoBar(sFolder,tabIndentForCurrentLine,iCy+iTopLine,sConfig);
      }
      
      //File name info
      if(iASaved!=iSaved)
      {
        PrintFileName(sRoot,sFile,iBinary,iSaved);
        PrintInfoBar(sFolder,iCx+leftMostColumn,iCy+iTopLine,sConfig);
      }
      
      //Clear refresh flag
      iRefresh=0;
      
    }while(iExit==0);
    
    //Restore keyboard status
    KeyboardStatusHideRestore();
    
}

// ----------------------------------------------------------------
// Bound character handling
char BindCharHandle(struct Config *sConfig)
{
  //Constants
  #define NEXTBUTTONCODE (int)255
  
  //Variables
  int i;
  int iExit;
  int iNode;
  int iFound;
  int iBindKey;
  int iBindStart;
  int iBindCount;
  int iBindChars;
  char cChr;
  char sText[5];
  
  //Count number of bound chars & exity if there is not any
  iBindChars=0;
  for(i=0;i<MAXCHARMAP;i++){
    if(sConfig->sCharMap[i].iKey!=-1){
      iBindChars++;
    }
  }
  if(iBindChars==0){
    return(0);
  }
    
  //Initializationd
  MenuStoreBar();
  iBindStart=0;
  
  //Loop start
  iExit=0;
  do{
  
    //Initialize menu bar
    for(i=0;i<=5;i++) MenuDisableNode(MENUBARBIND,i);
    
    //Setup menu bar
    iNode=0;
    iBindCount=0;
    for(i=0;i<MAXCHARMAP;i++){
      if(sConfig->sCharMap[i].iKey!=-1){
        if(iBindCount>=iBindStart){
          if(iNode<5 || iBindChars<=6){
            sprintf(sText,"  %c ",sConfig->sCharMap[i].cAscii);
            MenuSetNode(MENUBARBIND,iNode,sText,(int)sConfig->sCharMap[i].cAscii,-1,0,NULL);
            iNode++;
          }  
          else{
            MenuSetNode(MENUBARBIND,iNode,"    ",NEXTBUTTONCODE,-1,0,NextButton);
            break;
          }
        }  
        iBindCount++;
      }
    }
    MenuSetBar(MENUBARBIND);    
  
    //Get keystroke
    iBindKey=KeyNormalCase(GetKeyb());
  
    //Decide on key
    switch(iBindKey){
    
      //Function keys
      case KEY_CTRL_F1:
      case KEY_CTRL_F2:
      case KEY_CTRL_F3:
      case KEY_CTRL_F4:
      case KEY_CTRL_F5:
      case KEY_CTRL_F6:
        iBindKey=MenuFunctionKey(iBindKey);
        if(iBindKey==NEXTBUTTONCODE){
          iBindStart+=5;
        }
        else{
          cChr=(char)iBindKey;  
          iExit=1;
        }
        break;
      
      //Exit key
      case KEY_CTRL_EXIT:
        if(iBindStart==0){
          cChr=0;
          iExit=1;
        }
        else{
          iBindStart-=5;
        }
        break;
      
      //Vars key
      case KEY_CTRL_VARS:
        cChr=0;
        iExit=1;
        break;
      
      //Rest of cases
      default:  
        
        //Find character for bound key
        iFound=0;
        for(i=0;i<MAXCHARMAP;i++){
          if(sConfig->sCharMap[i].iKey==iBindKey){
            iFound=1;
            cChr=sConfig->sCharMap[i].cAscii;
            break;
          }
        }
        if(iFound==0){
          cChr=0;
        }
        iExit=1;
        break;
    
    }
  
  }while(!iExit);    
  
  //Restore menu bar
  MenuRestoreBar();    
             
  //Return char
  return(cChr);
  
}

// ----------------------------------------------------------------
// About Popup
void AboutPopup(void)
{
  PopupMessage(1," Text editor for ",
                 "  casio fx-9860G ",
                 "   series v1.6   ",
                 "Diego Marin, 2012", 
                 "dmarin75@yahoo.es");
}                 

// ----------------------------------------------------------------
// Quit handler
void QuitHandler(void)
{
  //Variables
  int iAnswer;
  int iExit;
  
  //Menu bar
  MenuSetBar(MENUBARNULL);
  
  //Save file before exit
  if(_iBinary==0 && _iSaved==0 && _sText[0]!=ENDMARK && _iAppMode==EDITOR)
  {
    Bdisp_AllClr_DDVRAM();
    iAnswer=PopupContinueYesNo("Save file","before leaving?",NULL);
    if(iAnswer==1)
    {
      iExit=0;
      do
      {
        iAnswer=1;
        if(_iNewFile==1)
        {
          iAnswer=0;
          do
          {
            while(GetFolder(_sRoot,_sFolder,&_sConfig)==0);
            while(GetFileName(_sFile,FMAXLEN(_sRoot), 0)==0);
            if(FileExist(_sRoot,_sFolder,_sFile)==1)
              iAnswer=PopupContinueYesNo("File exists.","Overwrite?",NULL);
            else
              iAnswer=1;
          }while(iAnswer==0);
        }
        if(WriteFile(_sRoot,_sFolder,_sFile,_sText,_sConfig.iNLMode)!=1)
        {
          PopupMessage(1,"File write error.","Try again!",NULL,NULL,NULL);
          _iNewFile=1;
        }
        else
          iExit=1;
      }while(iExit==0);
    }
  }

  //Free memory buffers
  free((void *)_sText);
  free((void *)_sClip);
  free((struct Direc *)_sFiles);
  free((struct Direc *)_sFolders);
}

// ----------------------------------------------------------------
// Editor font
void SetEditorFont(int iFont, int *iCntx)
{  
  //Set editor font
  switch(iFont)
  {
    case FONTS: Bkey_Set_RepeatTime(6,3);
                *iCntx=CONTXEDITS;
                break;
    case FONTT: Bkey_Set_RepeatTime(6,3);
                *iCntx=CONTXEDITT;
                break;
    case FONTM: Bkey_Set_RepeatTime(6,3);
                *iCntx=CONTXEDITM;
                break;
    case FONTL: Bkey_Set_RepeatTime(6,1);
                *iCntx=CONTXEDITL;
                break;
  }

}

// ----------------------------------------------------------------
// Detect SD Card 
int SDCardPresent(void)
{
  int iBytes;
  if(Bfile_GetMediaFree(DEVICE_SD_CARD,&iBytes)!=0)
    return(0);
  else if(iBytes==0)
    return(0);
  else
    return(1);
}    

// ----------------------------------------------------------------
// Cursor movement

#define COPYPASTEDIFELSE1 \
if(iColumn>iLen-1) {\
  \
	if(leftMostColumn >= iLen-1) leftMostColumn = iLen-1-1;\
	if (leftMostColumn < 0) leftMostColumn = 0;\
	iCx=iLen-1-leftMostColumn;\
	if (iCx < 0) iCx = 0;\
	\
} else {\
	iCx=iColumn;\
	if (!(iCx - leftMostColumn >= 0 && iCx - leftMostColumn < GetScrCAx())) {\
		leftMostColumn = iCx - GetScrCAx();\
		if (iColumn >= GetScrCAx()) leftMostColumn++;\
		if (leftMostColumn < 0) leftMostColumn = 0;\
	}\
	\
	iCx -= leftMostColumn;\
}

void MoveCursor(int *tabIndentForCurrentLine, int iCmd,int iTimes, int *iCx0, int *iCy0, 
                int *iTopLine0, int *leftMostColumn0, int *iColumn0,int *iRefresh0, 
                int iLNum, int *iLines,char *sText,int iCntx)
{
  //Static variables
  static int iMark; //Saved pointer position
  
  //Variables
  int k;          //Times
  int i,j;        //Counters
  int iCx;        //Cursor position
  int iCy;        //Cursor position
  int iColumn;    //Column for cursor movements
  int iTopLine;   //Text top line
  int iRefresh;   //Refresh screen
  int iLen;       //Text length
  int iPtr;       //Pointer
  int leftMostColumn = *leftMostColumn0;

  //Set font context
  SetFontContext(iCntx);
  
  //Init variables
  iCx=*iCx0;
  iCy=*iCy0;
  iColumn=*iColumn0;
  iTopLine=*iTopLine0;
  iRefresh=*iRefresh0;
  
  //Loop
  k=0;
  do
  {
  
    //Switch on command
    switch(iCmd)
    {
      //Go to top
      case CURSORTOP: 
        iTopLine=0; iColumn=0; iCx=0; iCy=1;
		leftMostColumn = 0;
        iRefresh=1;
        break;
                
      //Go to bottom
      case CURSORBOTTOM: 
        if(iLNum>GetScrCAy()-2)
        {
          iTopLine=iLNum-(GetScrCAy()-2);
          iLen=LineLength(iLNum-1,sText,iLines,iLNum);
          iColumn=iLen-1;
          COPYPASTEDIFELSE1
          iCy=GetScrCAy()-2;
          iRefresh=1;
        }
        else
        {
          iLen=LineLength(iLNum-1,sText,iLines,iLNum);
          iColumn=iLen-1;
          COPYPASTEDIFELSE1
          iCy=iLNum;
          iRefresh=1;
        }
        break;
                  
      //Page up
      case CURSORPAGEUP: 
        iTopLine=iTopLine-(GetScrCAy()-2);
        if(iTopLine<0)
          iTopLine=0;
        iLen=LineLength(iTopLine+iCy-1,sText,iLines,iLNum);
        COPYPASTEDIFELSE1
        iRefresh=1;
        break;

      //Page down
      case CURSORPAGEDOWN: 
        if(iLNum>GetScrCAy()-2)
        {
          iTopLine=iTopLine+(GetScrCAy()-2);
          if(iTopLine+GetScrCAy()-2>iLNum)
          iTopLine=iLNum-(GetScrCAy()-2);
          iLen=LineLength(iTopLine+iCy-1,sText,iLines,iLNum);
          COPYPASTEDIFELSE1
          iRefresh=1;
        }
        break;
              
      //Cursor home
      case CURSORHOME: 
        iCx=0;
		leftMostColumn = 0;
        iColumn=iCx;
        break;
            
      //Cursor end
      case CURSOREND: 
        if(iTopLine+iCy-1==iLNum-1)
          iCx=LineLength(iTopLine+iCy-1,sText,iLines,iLNum)-1;
        else
          iCx=iLines[iTopLine+iCy-1+1]-iLines[iTopLine+iCy-1]-1;

        iColumn=iCx;
		leftMostColumn = iCx - GetScrCAx();
		if (iColumn >= GetScrCAx()) leftMostColumn++;
		if (leftMostColumn < 0) leftMostColumn = 0;
		iCx -= leftMostColumn;
        break;
            
      //Cursor x++
      case CURSORRIGHT: 
        iCx++;
        iPtr=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
        if(iPtr>=strlen(sText)) {
			
          iCx--;
		  
        } else {
			if(/*iCx>GetScrCAx()-1 ||*/ sText[iPtr-1]==NEWLINELF || iCx>=LineLength(iTopLine+iCy-1,sText,iLines,iLNum)) {
			  
			  iCx=0; 
			  iCy++;
			  leftMostColumn = 0;
			  if(iCy>GetScrCAy()-2 || iTopLine+iCy-1>iLNum-1)
			  { 
				iCy--;
				iTopLine++;
				iRefresh = 1;
				if(iTopLine+GetScrCAy()-2>iLNum)
				  iTopLine--;
				else
				  iRefresh=1;
			  }
			} else {
				if (iCx>GetScrCAx()-1) {
			
				  iCx--;
				  leftMostColumn++;
				  iRefresh = 1;
				}
			}
			
			
		}
		
        iColumn=iCx+leftMostColumn;
        break;
            
      //Cursor x--
      case CURSORLEFT: 
        iCx--;
		if (iCx < 0) {
			leftMostColumn--;
			iCx++;
			iRefresh = 1;
		}
        if(leftMostColumn<0)
        {
          if(iCy==1 && iTopLine==0) {
            leftMostColumn=0;
			iRefresh = 1;
		  } else {
            iCx=iLines[iTopLine+iCy-1]-iLines[iTopLine+iCy-2]-1;
			leftMostColumn = iCx - GetScrCAx()+1;
			if (leftMostColumn < 0) leftMostColumn = 0;
			iCx -= leftMostColumn;
            iCy--; 
            if(iCy<1)
            { 
              iCy=1;
              iTopLine--;
              if(iTopLine<0)
                iTopLine=0;
              else
                iRefresh=1;
            }
          }
        }
        iColumn=iCx+leftMostColumn;
        break;
      
	  
	  //These two commands cause bugs when clipboard is used, and the editor seems to work fine without them.
      //Cursor mark
      case CURSORMARK: 
        //iMark=iLines[iTopLine+iCy-1]+iCx+leftMostColumn;
        break;
      
      //Cursor find
      case CURSORFIND:
		
        /*if(iMark>=strlen(sText)) iMark=strlen(sText)-1;
        for(i=-1;i<2;i++){
        for(j=0;j<GetScrCAx();j++){
          if(iLines[iTopLine+iCy-1+i]+j+leftMostColumn==iMark)
          {
            if(i==-1)
            {
              iCx=j;
              iCy--;
              if(iCy<1)
              {
                iCy=1;
                iTopLine--;
                if(iTopLine<0)
                  iTopLine++;
              }
            }
            else if(i==0)
            {
              iCx=j;
            }
            else if(i==1)
            {
              iCx=j;
              iCy++;
              if(iCy>GetScrCAy()-2 || iTopLine+iCy-1>iLNum-1)
              { 
                iCy--;
                iTopLine++;
                if(iTopLine+GetScrCAy()-2>iLNum)
                  iTopLine--;
              }
            }
            iRefresh=1;
            break;
          }  
        }}
        iColumn=iCx+leftMostColumn;*/
        break;		
		

      //Cursor y++
      case CURSORDOWN:  
        iCy++; 
        if(iCy>GetScrCAy()-2  || iTopLine+iCy-1>iLNum-1)
        { 
          iCy--;
          iTopLine++;
          if(iTopLine+GetScrCAy()-2>iLNum)
            iTopLine--;
          else
          {
            iLen=LineLength(iTopLine+iCy-1,sText,iLines,iLNum);
            COPYPASTEDIFELSE1
			iRefresh=1;
          }
        }
        else
        {
			iLen=LineLength(iTopLine+iCy-1,sText,iLines,iLNum);
			COPYPASTEDIFELSE1
        }
        break;
            
      //Cursor y--
      case CURSORUP:
        iCy--; 
        if(iCy<1)
        { 
          iCy=1;
          iTopLine--;
          if(iTopLine<0)
            iTopLine=0;
          else
          {
            iLen=LineLength(iTopLine+iCy-1,sText,iLines,iLNum);
            COPYPASTEDIFELSE1
            iRefresh=1;
          }
        }
        else
        {
          iLen=LineLength(iTopLine+iCy-1,sText,iLines,iLNum);
          COPYPASTEDIFELSE1
        }
        break;
      
    }
  
    //Increase counter
    k++;
  
  }while(k<iTimes);
  
  
  //Calculate indent
  iPtr=iLines[iTopLine+iCy-1];
  
  int nbSpaces = 0;
  
  for (i = 0; sText[iPtr+i] == ' '; i++) {
	nbSpaces++;
  }
  
  *tabIndentForCurrentLine = nbSpaces/2;
  
  
  //Set result
  *leftMostColumn0 = leftMostColumn;
  *iCx0=iCx;
  *iCy0=iCy;
  *iColumn0=iColumn;
  *iTopLine0=iTopLine;
  *iRefresh0 = 1;
  //*iRefresh0=iRefresh;
}

// ----------------------------------------------------------------
// Calculate text line positions
void CalcLines(char *sText, int *iLines, int *iLNum, int iFrom,
               int iCntx, struct Config *sConfig)
{
  //Variables
  int i,j,k;
  int iLen;
  int iCount;
  int iStart;
  int iLPtr;
 
  //Set font context
  SetFontContext(iCntx);
 
  //Calculate text length
  iLen=strlen(sText);
 
  //Initialize array when text is empty
  if(iLen==0)
  {
    iLines[0]=0;
    *iLNum=1;
    return;
  }
 
  //Calculate lines
  else
  {
   
    //Loop initializations
    if(iFrom==0) iStart=0;
    else iStart=iLines[iFrom];
    iLPtr=iStart;
    iCount=0;
    j=iFrom;
 
    //Calculate line positions
    for(i=iStart;i<iLen;i++)
    {
      if(sText[i]==NEWLINELF)
      {
        iLines[j]=iLPtr;
        iLPtr=i+1;
        j++;
        iCount=0;
      }
      else
      {
        iCount++;
        /*if(iCount==GetScrCAx() && sConfig->iWordWrap==0)
        {
          iLines[j]=iLPtr;
          iLPtr=i+1;
          j++;
          iCount=0;
        }
        else if(iCount==GetScrCAx() && sConfig->iWordWrap==1)
        {
          if(sText[i]!=' ' && sText[i]!=9)
          {
            for(k=0;k<GetScrCAx();k++) if(sText[i-k]==' ' || sText[i-k]==9) break;
            if(k<GetScrCAx())
            {
              i=i-k;  
            }
          }
          iLines[j]=iLPtr;
          iLPtr=i+1;
          j++;
          iCount=0;
        }*/
      }
      if(j>=MAXLINE-1) break;
    }
   
    //Finish loop
    if(iCount==0)
      *iLNum=j;
    else
    {
      iLines[j]=iLPtr;
      *iLNum=j+1;
    }
   
  }

}

// ----------------------------------------------------------------
// Text line length
int LineLength(int iLine, char *sText, int *iLines, int iLNum)
{
    if(iLine==iLNum-1)
    return(strlen(sText)-iLines[iLine]);
  else
    return(iLines[iLine+1]-iLines[iLine]);
}

// ----------------------------------------------------------------
// Dump text lines
void DumpTextLines(char *sText, int *iLines, int iLNum, 
                   int iTopLine, int leftMostColumn, int iStart, int iEnd,int iCntx)
{
   //Variables
   int i,j;
   int iLine;
   int iPtr;
   int iLen;
   char sStr[2];
   
   //Set font context
   SetFontContext(iCntx);
   
   //Print loop
   for(j=1;j<=GetScrCAy()-2;j++){
     iLine=iTopLine+j-1;
     iPtr=iLines[iLine]+leftMostColumn;
     if(iLine<=iLNum-1)
     {
       iLen=LineLength(iLine,sText,iLines,iLNum);
       for(i=0;i<GetScrCAx();i++){
         if(i+leftMostColumn>=iLen || sText[iPtr]==NEWLINELF)
         {
           sStr[0]=' ';
           sStr[1]=0;
         }
         else
         {
           sStr[0]=sText[iPtr];
           sStr[1]=0;
         }
         SetColorCntx(COLNOR);
         if(iStart!=iEnd && i+leftMostColumn<iLen)
         {
           if(iStart<iEnd && iStart<=iPtr && iEnd>iPtr)
             SetColorCntx(COLREV);
           else if(iStart>iEnd && iEnd<=iPtr && iStart>iPtr)
             SetColorCntx(COLREV);
         }
         PrintStr(i,j,sStr);
         iPtr++;
       }
     }
     else
     {
       SetColorCntx(COLNOR);
       for(i=0;i<GetScrCAx()+0;i++){
         PrintStr(i,j," ");
       }
     }
   }
    
   //Restore font color in context
   SetColorCntx(COLNOR);
}

// ----------------------------------------------------------------
// State bar
void PrintFileName(char *sRoot,char *sFile,int iBinary, int iSaved)
{
  //Font
  SetFont(FONTS);
  
  //Init first line
  SetColor(COLREV);
  SetOffset(0,0); PrintStr(0,0," ");
  SetOffset(0,1); PrintStr(0,0," ");
  SetOffset(2,0); PrintStr(26,0," ");
  SetOffset(2,1); PrintStr(26,0," ");
  SetOffset(1,0); PrintStr(0,0,"                           ");
  SetOffset(1,1); PrintStr(0,0,"                 ");
  
  //Storage mem / SD Card
  if(strcmp(sRoot,"main")==0) PrintStr(0,0,"MM");
  if(strcmp(sRoot,"fls0")==0) PrintStr(0,0,"");
  if(strcmp(sRoot,"crd0")==0) PrintStr(0,0,"SD");
  
  //File name
  PrintStr(0,0,sFile);
  //PrintStr(0+strlen(sFile), 0, ".py");
  
  //Folder name
  //if(strlen(sFolder)>0) PrintStr(18,0,sFolder);
  
  //Binary file / Text file
  SetFont(FONTS);
  SetColor(COLREV);
  SetOffset(0,0);
  PrintStrXY(-3+4*30,0," ");
  PrintStrXY(-2+4*30,0," ");
  PrintStrXY(-3+4*30,1," ");
  switch(iBinary) 
  {
    case 0: PrintStrXY(-2+4*30,1,"T"); break;
    case 1: PrintStrXY(-2+4*30,1,"B"); break;
  }
  
  //Save file status
  SetFont(FONTS);
  SetColor(COLREV);
  PrintStrXY(-5+4*29,0," ");
  PrintStrXY(-4+4*29,0," ");
  PrintStrXY(-5+4*29,1," ");
  switch(iSaved) 
  {
    case 0: PrintStrXY(-4+4*29,1,"-"); break;
    case 1: PrintStrXY(-4+4*29,1,"S"); break;
  }
  
}

// ----------------------------------------------------------------
// Info bar
void PrintInfoBar(char *sFolder,int col, int line,
                  struct Config *sConfig)
{
  //Variables
  char sStr[20];
  
  //Switch on option
  switch(sConfig->iInfo)
  {
    case INFOBARFOLDER:
      SetFont(FONTS);
      SetColor(COLREV);
      SetOffset(1,1); PrintStr(17,0,"[        ]");
      if(strlen(sFolder)>0) PrintStr(18,0,sFolder);
      SetOffset(0,0);
      break;
    case INFOBARCURSOR:
      SetFont(FONTS);
      SetColor(COLREV);
      sprintf(sStr,"Ln %i, col %i",line, col);
      SetOffset(1,1); 
      PrintStr(10,0,"                 ");
      PrintStr(17+10-strlen(sStr),0,sStr);
      SetOffset(0,0);
      break;
  }
}

// ----------------------------------------------------------------
// Main directory
int MainDirectory(int iAction, char *sFile,char *sFolder)
{
  //Variables
  int i;
  int iError;
  int iHandle1;
  int iHandle2;
  int iFound;
  int iExit;
  struct MainDir sMainDir;
  static int iHandle;
  static int iSeek;
  static sFolder0[MAXFNAMEMM];
  
  //Switch on action
  switch(iAction)
  {
    //Initialize
    case INITIALIZE:
      iHandle=Bfile_OpenMainMemory(MAINDIRFILE);
      if(iHandle<0)
      {
        Bfile_CreateMainMemory(MAINDIRFILE);
        iHandle=Bfile_OpenMainMemory(MAINDIRFILE);
        if(iHandle>=0)
        {
          memset(&sMainDir,0,sizeof(struct MainDir));
          strcpy(&(sMainDir.sName),CONFIGFILE);
          Bfile_WriteFile(iHandle,(void *)&sMainDir,sizeof(struct MainDir));
          strcpy(&(sMainDir.sName),MAINDIRFILE);
          Bfile_WriteFile(iHandle,(void *)&sMainDir,sizeof(struct MainDir));
        }
      }
      Bfile_CloseFile(iHandle);
      break;
    
    //Check entry exists
    case CHECKENTRY:
      iHandle=Bfile_OpenMainMemory(MAINDIRFILE);
      if(iHandle<0){ Bfile_CloseFile(iHandle); return(-1); }
      iFound=0;
      iSeek=0;
      do{
        if(Bfile_ReadFile(iHandle,(void *)&sMainDir,sizeof(struct MainDir),iSeek)<0)
        {
          break;
        }
        if(strcmp(sFolder,sMainDir.sFolder)==0 && strcmp(sFile,sMainDir.sName)==0)
        {
          iFound=1;
          break;
        }
        iSeek+=sizeof(struct MainDir);
      }while(1);
      Bfile_CloseFile(iHandle);
      return(iFound==1?0:-1);
      break;
    
    //Create entry
    case CREATE:
      iHandle=Bfile_OpenMainMemory(MAINDIRFILE);
      if(iHandle<0){ Bfile_CloseFile(iHandle); return(-1); }
      iError=0;
      iSeek=0;
      do{
        if(Bfile_ReadFile(iHandle,(void *)&sMainDir,sizeof(struct MainDir),iSeek)<0)
        {
          memset(&sMainDir,0,sizeof(struct MainDir));
          strcpy(&(sMainDir.sName),sFile);
          strcpy(&(sMainDir.sFolder),sFolder);
          if(Bfile_WriteFile(iHandle,(void *)&sMainDir,sizeof(struct MainDir))<0)
            iError=1;
          else
            iError=0;
          break;
        }
        iSeek+=sizeof(struct MainDir);
      }while(1);
      Bfile_CloseFile(iHandle);
      return(iError==1?-1:0);
      break;
    
    //Delete entry
    case DELETE:
      iHandle1=Bfile_OpenMainMemory(MAINDIRFILE);
      if(iHandle1<0){ Bfile_CloseFile(iHandle1); return(-1); }
      if(Bfile_CreateMainMemory(MAINDIRTEMP)<0) return(-1);
      iHandle2=Bfile_OpenMainMemory(MAINDIRTEMP);
      if(iHandle2<0)
      { 
        Bfile_CloseFile(iHandle1); 
        Bfile_CloseFile(iHandle2); 
        Bfile_DeleteMainMemory(MAINDIRTEMP);
        return(-1); 
      }
      iError=0;
      iSeek=0;
      do{
        if(Bfile_ReadFile(iHandle1,(void *)&sMainDir,sizeof(struct MainDir),iSeek)<0)
        {
          break;
        }
        if(strcmp(sFile,sMainDir.sName)!=0)
        {
          if(Bfile_WriteFile(iHandle2,(void *)&sMainDir,sizeof(struct MainDir))<0)
          {
            iError=1;
            break;
          }
        }
        iSeek+=sizeof(struct MainDir);
      }while(1);
      Bfile_CloseFile(iHandle1);
      Bfile_CloseFile(iHandle2);
      Bfile_DeleteMainMemory(MAINDIRFILE);
      Bfile_RenameMainMemory(MAINDIRTEMP,MAINDIRFILE);
      return(iError==1?-1:0);
      break;
    
    //Delete all entries in folder
    case DELETEFOLDER:
      iHandle1=Bfile_OpenMainMemory(MAINDIRFILE);
      if(iHandle1<0){ Bfile_CloseFile(iHandle1); return(-1); }
      if(Bfile_CreateMainMemory(MAINDIRTEMP)<0) return(-1);
      iHandle2=Bfile_OpenMainMemory(MAINDIRTEMP);
      if(iHandle2<0)
      { 
        Bfile_CloseFile(iHandle1); 
        Bfile_CloseFile(iHandle2); 
        Bfile_DeleteMainMemory(MAINDIRTEMP);
        return(-1); 
      }
      iError=0;
      iSeek=0;
      do{
        if(Bfile_ReadFile(iHandle1,(void *)&sMainDir,sizeof(struct MainDir),iSeek)<0)
        {
          break;
        }
        if(strcmp(sFolder,sMainDir.sFolder)!=0)
        {
          if(Bfile_WriteFile(iHandle2,(void *)&sMainDir,sizeof(struct MainDir))<0)
          {
            iError=1;
            break;
          }
        }
        else
          Bfile_DeleteMainMemory(sMainDir.sName);
        iSeek+=sizeof(struct MainDir);
      }while(1);
      Bfile_CloseFile(iHandle1);
      Bfile_CloseFile(iHandle2);
      Bfile_DeleteMainMemory(MAINDIRFILE);
      Bfile_RenameMainMemory(MAINDIRTEMP,MAINDIRFILE);
      return(iError==1?-1:0);
      break;
    
    //Find first
    case FINDSTART:
      iSeek=0;
      iHandle=Bfile_OpenMainMemory(MAINDIRFILE);
      if(iHandle<0){ Bfile_CloseFile(iHandle); return(-1); }
      strcpy(sFolder0,sFolder);
      return(0);
      break;
    
    //Find next
    case FINDGET:
      iExit=0;
      do{
        if(Bfile_ReadFile(iHandle,(void *)&sMainDir,sizeof(struct MainDir),iSeek)<0)
        {
          Bfile_CloseFile(iHandle);
          return(-1);
        }
        if(strlen(sFolder0)>0)
        {
          if(strlen(sMainDir.sName)>0 && strcmp(sMainDir.sFolder,sFolder0)==0) iExit=1;        
        }
        else
        {
          if(strlen(sMainDir.sName)==0 || strlen(sMainDir.sFolder)==0) iExit=1;                  
        }
        iSeek+=sizeof(struct MainDir);
      }while(iExit==0);
      strcpy(sFile,sMainDir.sName);
      strcpy(sFolder,sMainDir.sFolder);
      return(0);
      break;
    
  }
}

// ----------------------------------------------------------------
// Fontcharacter string -> Char string
char *Font2Char(FONTCHARACTER *sFont, char *sChar)
{
  int i=0;
  for(i=0;sFont[i]!=0;i++) sChar[i]=sFont[i];
  sChar[i]=0;
  return(sChar);
}

// ----------------------------------------------------------------
// Char string -> Fontcharacter string
FONTCHARACTER *Char2Font(char *sChar, FONTCHARACTER *sFont)
{
  int i=0;
  for(i=0;sChar[i]!=0;i++) sFont[i]=sChar[i];
  sFont[i]=0;
  return(sFont);
}

// ----------------------------------------------------------------
// File path
FONTCHARACTER *FilePath(char *sRoot,char *sFolder,
                        char *sFile,FONTCHARACTER *sFont)
{            

/*locate(1,2); Print(sFolder); GetKey(&key);
locate(1,3); Print(sRoot); GetKey(&key);
locate(1,4); Print(sFile); GetKey(&key);
  locate(1,1); Print("d"); GetKey(&key); */           
  //Variables
  char sPath[50];
  
  //File path without folder
  if(strlen(sFolder)==0)
    sprintf(sPath,"\\\\%s\\%s",sRoot,sFile);
  
  //File path without file
  else if(strlen(sFile)==0)
    sprintf(sPath,"\\\\%s\\%s",sRoot,sFolder);
  
  //File path with file & folder
  else
    sprintf(sPath,"\\\\%s\\%s\\%s",sRoot,sFolder,sFile);
  
  //locate(1,1); Print("e"); GetKey(&key);
  
  //Convert to FONTCHARACTER
  Char2Font(sPath,sFont);
  //locate(1,1); Print("f"); GetKey(&key);
  return(sFont);
}

// ----------------------------------------------------------------
// Insert file into directory with sorting
void AppendDirEntry(int iFiles,struct Direc *sDirec,struct Direc *sDirec0)
{
  //Variables
  int i,j;
  char sName[50];
  char sName0[50];
  char sSort[50];
  char sSort0[50];
  
  //Insert new record
  if(iFiles==0)
  {
    memcpy(&sDirec[0],sDirec0,sizeof(struct Direc));
  }
  else
  {
    i=iFiles-1;
    do{
      if(i<0) break;
      strcpy(sName,sDirec[i].sCName);
      strcpy(sName0,sDirec0->sCName);
      for(j=0;sName[j]!=0;j++) sName[j]=toupper2(sName[j]);
      for(j=0;sName0[j]!=0;j++) sName0[j]=toupper2(sName0[j]);
      sprintf(sSort ,"%1i%s",sDirec[i].cSort,sName );
      sprintf(sSort0,"%1i%s",sDirec0->cSort ,sName0);
      if(strcmp(sSort,sSort0)<=0) break;
      memcpy(&sDirec[i+1],&sDirec[i],sizeof(struct Direc));
      i=i-1;
    }while(1);
    memcpy(&sDirec[i+1],sDirec0,sizeof(struct Direc));
  }

}

// ----------------------------------------------------------------
// Read directory
void ReadDirectory(char *sRoot, char *sFolder,struct Direc *sDirec, 
                   int *iEntries, int iMaxFiles, unsigned char cSort, 
                   int iFoldersOnly, int iHideSysFiles)
{
  //Variables
  int i,j;
  int iFirst;
  int iDot;
  int iError;
  int iHandle;
  char sFile[MAXPATH];
  char sFolder0[MAXPATH];
  FONTCHARACTER sFont[MAXPATH];
  FONTCHARACTER sName[MAXPATH];
  struct Direc sDirec0;
  FILE_INFO sInfo;
  //locate(1,1); Print("b"); GetKey(&key);
  //Init loop
  i=(*iEntries);
  iFirst=0;
  iError=0;
  FilePath(sRoot,sFolder,"*.py",sFont);
  //locate(1,1); Print("c"); GetKey(&key);
  do{
    
    //Read file (Main Memory)
    if(strcmp(sRoot,"main")==0)
    {
      if(iFirst==0)
      {
        MainDirectory(FINDSTART,&(sDirec0.sCName),sFolder);
        iFirst=1;
      }
      iError=MainDirectory(FINDGET,&(sDirec0.sCName),sFolder0);
      if(strlen(sDirec0.sCName)==0)
      {
        sDirec0.iType=DT_DIRECTORY;
        strcpy(sDirec0.sCName,sFolder0);
        sDirec0.iSize=0;
      }
      else
      {
        sDirec0.iType=DT_FILE; 
        iHandle=Bfile_OpenMainMemory(sDirec0.sCName);
        if(iHandle<0) 
          sDirec0.iSize=0;
        else
          sDirec0.iSize=Bfile_GetFileSize(iHandle);
        Bfile_CloseFile(iHandle);
      }
    }
    
    //Read file (Storage memory & SD Card)
    else
    {
	  //locate(1,1); Print("f"); GetKey(&key);
      if(iFirst==0)
      {
        iError=Bfile_FindFirst(sFont,&iHandle,sName,&sInfo);
        iFirst=1;
      }
       else     
      {
        iError=Bfile_FindNext(iHandle,sName,&sInfo);
      }
      Font2Char(sName,sDirec0.sCName);
      sDirec0.iType=sInfo.type; 
      sDirec0.iSize=sInfo.dsize;
    }
    
    //Append to directory
    if(iError==0 && i<iMaxFiles-1)
    {
      //locate(1,1); Print("g"); GetKey(&key);
      //Detect system files
      sDirec0.cSystem=0;
      strcpy(sFile,sDirec0.sCName);
      for(j=0,iDot=0;j<strlen(sFile);j++){ if(sFile[j]=='.') iDot=j; }
      if(sDirec0.iType!=DT_FILE && sDirec0.iType!=DT_DIRECTORY) sDirec0.cSystem=1;
      if(iDot!=0 && toupper2(sFile[iDot+1])=='G' && tolower2(sFile[iDot+1])=='1') sDirec0.cSystem=1;
      if(strcmp(sRoot,"fls0")==0 && strcmp(sFile,"EACTWORK.tmp")==0) sDirec0.cSystem=1;
      if(strcmp(sRoot,"main")==0 && strcmp(sFile,CONFIGFILE)==0) sDirec0.cSystem=1;
      if(strcmp(sRoot,"main")==0 && strcmp(sFile,MAINDIRFILE)==0) sDirec0.cSystem=1;
      //locate(1,1); Print("h"); GetKey(&key);
      //Append entries
      if(iFoldersOnly==0)
      {
        if(sDirec0.iType==DT_DIRECTORY)
        {
          sDirec0.cSort=cSort;
          AppendDirEntry(i,sDirec,&sDirec0);
          i++;
        }
        else
        {
          if(iHideSysFiles==0 || (iHideSysFiles==1 && sDirec0.cSystem==0))
          {
            sDirec0.cSort=cSort+1;
            AppendDirEntry(i,sDirec,&sDirec0);
            i++;
          }
        }
      }
      else if(sDirec0.iType==DT_DIRECTORY)
      {
        sDirec0.cSort=cSort;
        AppendDirEntry(i,sDirec,&sDirec0);
        i++;
      }
    
    }
  
  }while(iError==0);
  if(strcmp("main",sFolder)!=0) Bfile_FindClose(iHandle);
  *iEntries=i;
  
}

// ----------------------------------------------------------------
// File explorer
int Explorer(int iMode,char *sRoot, char *sFolder, 
             char *sFile,struct Config *sConfig,int *iNew)
{
  
  //Variables
  int i;
  int iError;
  int iExit;
  int iFiles;
  int iBytes;
  int iReadFiles=1;
  int iRefresh=1;
  int iAnswer;
  char sStr[50];
  int iStart=0;
  int iRow=0;
  int iARow=0;
  int iCode;
  int iSDPresent;
  int iLines=5;
  unsigned int iKey;
  int iHandle;
  char sRootAux[5];     
  char sFolderAux[MAXFNAME];
  char sFileAux[MAXFNAME];  
  FONTCHARACTER sFont[MAXPATH];
  struct Direc sDirec0;
  
  //Application mode
  _iAppMode=EXPLORER;
          
  //Hide keyboard status
  KeyboardStatusHide(1);
  
  //Detect SD Card
  if(sConfig->iTrySD==0)
    iSDPresent=0;
  else
    iSDPresent=SDCardPresent();
    
  //Modify menus
  if(iSDPresent==0)
  {
    MenuDisableNode(MENUBARROOT,5);
    if(strcmp(sRoot,"crd0")==0) sprintf(sRoot,"fls0");
  }
  else
  {
    MenuEnableNode(MENUBARROOT,5);
  }
    
  //Main loop
  iExit=0;
  do{
    //GetKey(&key);
    //Number of window lines
    if(sConfig->iDispFree==1)
      iLines=5;
    else
      iLines=6;
    
	//GetKey(&key);
    //Init display
    if(iReadFiles==1) Bdisp_AllClr_DDVRAM();
	
	//GetKey(&key);
    
    //Get file table
    if(iReadFiles==1)
    {
      iFiles=0;
      ReadDirectory(sRoot,sFolder,_sFiles,&iFiles,sConfig->iMaxFiles,1,0,sConfig->iHideSysFiles); 
    }
	
	//GetKey(&key);
    
    //Set menu bar
    if(iReadFiles==1)
    {
      if(strlen(sFolder)>0 && iFiles==0)
      {
        MenuDisableNode(MENUBAREXPL,0);
        MenuDisableNode(MENUBAREXPL,1);
        MenuDisableNode(MENUBAREXPL,3);
        MenuDisableNode(MENUBAREXPL,4);
        MenuDisableNode(MENUBAREXPL,5);
        MenuDisableNode(MENUBAREXP2,0);
        MenuDisableNode(MENUBAREXP2,1);
        MenuDisableNode(MENUBAREXP2,2);
        MenuDisableNode(MENUBAREXP2,3);
        MenuDisableNode(MENUBAREXP2,4);
        MenuDisableNode(MENUBARAUTO,0);
      }
      else if(strlen(sFolder)>0)
      {
        MenuEnableNode( MENUBAREXPL,0);
        MenuEnableNode( MENUBAREXPL,5);
        MenuEnableNode( MENUBAREXPL,2);
        MenuEnableNode( MENUBAREXP2,0);
        MenuEnableNode( MENUBAREXP2,1);
        MenuEnableNode( MENUBAREXP2,2);
        MenuDisableNode(MENUBAREXP2,3);
        MenuDisableNode(MENUBAREXP2,4);
        MenuEnableNode( MENUBARAUTO,0);
      }
      else if(iFiles==0)
      {
        MenuDisableNode(MENUBAREXPL,0);
        MenuDisableNode(MENUBAREXPL,5);
        MenuDisableNode(MENUBAREXPL,2);
        MenuDisableNode(MENUBAREXPL,4);
        MenuEnableNode( MENUBAREXPL,3);
        MenuDisableNode(MENUBAREXP2,0);
        MenuDisableNode(MENUBAREXP2,1);
        MenuDisableNode(MENUBAREXP2,2);
        MenuDisableNode( MENUBAREXP2,3);
        MenuDisableNode(MENUBAREXP2,4);
        MenuDisableNode(MENUBARAUTO,0);
      }
      else
      {
        MenuEnableNode(MENUBAREXPL,0);
        MenuEnableNode(MENUBAREXPL,5);
        MenuEnableNode(MENUBAREXPL,2);
        MenuEnableNode(MENUBAREXP2,0);
        MenuEnableNode(MENUBAREXP2,1);
        MenuEnableNode(MENUBAREXP2,2);
        MenuEnableNode(MENUBAREXP2,3);
        MenuEnableNode(MENUBAREXP2,4);
        MenuEnableNode(MENUBARAUTO,0);
      }
      switch(iMode)
      {
        case EXPLOREROPEN: MenuSetBar(MENUBAREXPL); break;
        case EXPLORERAUTO: MenuSetBar(MENUBARAUTO); break;
      }
    }
    
    //Rewrite screen
    if(iRefresh==1)
    {
	  	//GetKey(&key);
      SetFont(FONTL);
      SetColor(COLNOR);
      if(strcmp(sRoot,"main")==0) 
      {
        sprintf(sStr,"Main Memory[%-8s]",sFolder);
        if(Bfile_GetMediaFree(DEVICE_MAIN_MEMORY,&iBytes)!=0) iBytes=0;
      }  
      if(strcmp(sRoot,"fls0")==0) 
      {
        sprintf(sStr,STR_PROGLIST);
        if(Bfile_GetMediaFree(DEVICE_STORAGE,&iBytes)!=0) iBytes=0;
      }  
      if(strcmp(sRoot,"crd0")==0) 
      {
        sprintf(sStr,"SD Card    [%-8s]",sFolder);
        if(Bfile_GetMediaFree(DEVICE_SD_CARD,&iBytes)!=0) iBytes=0;
      }
      PrintStr(0,0,sStr);
      if(sConfig->iDispFree==1)
      {
        sprintf(sStr,"%i Bytes Free",iBytes);
        PrintStr(0,6,sStr);
      }
      if(iFiles>0)
      {
        for(i=0;i<iLines;i++)
        {
          if(i+iStart<iFiles)
            PrintFileEntry(i+1,iStart,iFiles,iLines,&_sFiles[i+iStart],1);
          else
            PrintStr(0,i+1,"                     ");
        }
      }
      else
      {
			//GetKey(&key);
        PrintStr(0,1,"                     ");
        PrintStr(0,2,"                     ");
        PrintStr(0,3,STR_NOPROGS);
        PrintStr(0,4,"                     ");
        PrintStr(0,5,"                     ");
        if(iLines>5)
          PrintStr(0,6,"                     ");
      }
    }
    
    //Cursor position
    if(iFiles>0 && (iRow!=iARow || iRefresh!=0))
    {
      SetFont(FONTL);
      if(iReadFiles==0) PrintFileEntry(iARow+1,iStart,iFiles,iLines,&_sFiles[iARow+iStart],1);
      PrintFileEntry(iRow +1,iStart,iFiles,iLines,&_sFiles[iRow +iStart],0);
    }    
    
    //Flush screen
    if(iRefresh!=0) Bdisp_PutDisp_DD();
    
    //Clear flags
    iRefresh=0;
    iReadFiles=0;
    
    //Previous cursor position
    iARow=iRow;
    
    //Get Key
    iKey=GetKeyb();
      
    //Exit key (must be outside of switch)
    /*if(iKey==KEY_CTRL_EXIT && 
    (  MenuGetBar()==MENUBARAUTO 
    || MenuGetBar()==MENUBAREXPL ) )
    {
      if(strlen(sFolder)!=0)
      {
        sFolder[0]=0;
        iReadFiles=1;
        iRefresh=1;
        iStart=0;
        iRow=0;
        iKey=0;
      }
      else if(MenuGetBar()==MENUBARAUTO)
      {
        iExit=2;
        iKey=0;
      }
    }*/

    //Process keys
    switch(iKey)
    {
      //Process menu commands
      case KEY_CTRL_F1:
      case KEY_CTRL_F2:
      case KEY_CTRL_F3:
      case KEY_CTRL_F4:
      case KEY_CTRL_F5:
      case KEY_CTRL_F6:
      case KEY_CTRL_EXIT:
        iCode=MenuFunctionKey(iKey);
        if(iCode!=NODENOFUNCT)
        {
          switch(iCode)
          {
          
            //File open / Save as / Auto set
            case NODEEXPLOPEN:
            case NODEAUTOSET:
              if(_sFiles[iStart+iRow].iType==DT_DIRECTORY)
              {
                strcpy(sFolder,_sFiles[iStart+iRow].sCName);
                iStart=0;
                iRow=0;
                iReadFiles=1;
                iRefresh=1;
              }
              else
              {
                strcpy(sFile,_sFiles[iStart+iRow].sCName);
                iExit=1;
                *iNew=0;
              }
              break;
            
              
            //New file
            case NODEEXPLNEW: 
              if(iFiles!=0) 
                strcpy(sFileAux,_sFiles[iStart+iRow].sCName);
              else
                memset(sFileAux,0,MAXFNAME);
              iAnswer=GetFileName(sFileAux,FMAXLEN(sRoot), 1);
              if(iAnswer==1)
              {
                if(FileExist(sRoot,sFolder,sFileAux)==1)
                {
                  iAnswer=PopupContinueYesNo(STR_FILEEXISTS,STR_CONTINUE,NULL);
                }
                else
                  iAnswer=1;
                if(iAnswer==1)
                {
                  strcpy(sFile,sFileAux);
                  iExit=1;
                  *iNew=1;
                }
              }
              break;
              
            //File rename
            case NODEEXPLREN:
              if(_sFiles[iStart+iRow].iType!=DT_DIRECTORY)
              {
                strcpy(sFileAux,_sFiles[iStart+iRow].sCName);
                if(GetFileName(sFileAux,FMAXLEN(sRoot), 0))
                {
                  if(FileExist(sRoot,sFolder,sFileAux)==1)
                    iAnswer=PopupContinueYesNo(STR_FILEEXISTS,STR_OVERWRITE,NULL);
                  else
                    iAnswer=1;
                  if(iAnswer==1)
                  {
                    strcpy(sFile,_sFiles[iStart+iRow].sCName);
                    if(CopyFile(sRoot,sFolder,sFile,sRoot,sFolder,sFileAux)==1)
                    {
                      DeleteFile(sRoot,sFolder,sFile);
                      sprintf(sFile,sFileAux);
                      iStart=0;
                      iRow=0;
                      iReadFiles=1;
                    }
                    else
                      PopupMessage(1,STR_RENAMEERROR,NULL,NULL,NULL,NULL);
                  }
                }
                iRefresh=1;
              }
              break;
            
            //File copy
            case NODEEXPLCOPY:
              if(_sFiles[iStart+iRow].iType!=DT_DIRECTORY)
              {
                strcpy(sRootAux,sRoot);
                strcpy(sFolderAux,sFolder);
                if(GetFolder(sRootAux,sFolderAux,sConfig))
                {
                  strcpy(sFileAux,_sFiles[iStart+iRow].sCName);
                  if(GetFileName(sFileAux,FMAXLEN(sRootAux), 0))
                  {
                    if(FileExist(sRootAux,sFolderAux,sFileAux)==1)
                      iAnswer=PopupContinueYesNo(STR_FILEEXISTS,STR_OVERWRITE,NULL);
                    else
                      iAnswer=1;
                    if(iAnswer==1)
                    {
                      strcpy(sFile,_sFiles[iStart+iRow].sCName);
                      if(CopyFile(sRoot,sFolder,sFile,sRootAux,sFolderAux,sFileAux)==1)
                      {
                        iStart=0;
                        iRow=0;
                        iReadFiles=1;
                        iError=0;
                      }
                      else
                      {
                        PopupMessage(1,STR_COPYERROR,NULL,NULL,NULL,NULL);
                        iError=1;
                      }
                    }
                  }
                }
                iRefresh=1;
              }
              break;
            
            //File delete
            case NODEEXPLDEL:
              if(_sFiles[iStart+iRow].iType!=DT_DIRECTORY)
              {
                strcpy(sFileAux,_sFiles[iStart+iRow].sCName);
                iAnswer=PopupContinueYesNo(STR_DELPROG,sFileAux,NULL);
                if(iAnswer==1)
                {
                  DeleteFile(sRoot,sFolder,sFileAux);
                  iStart=0;
                  iRow=0;
                  iReadFiles=1;
                }
              }
              iRefresh=1;
              break;
              
            //File move
            case NODEEXPLMOVE:
              if(_sFiles[iStart+iRow].iType!=DT_DIRECTORY)
              {
                strcpy(sRootAux,sRoot);
                strcpy(sFolderAux,sFolder);
                if(GetFolder(sRootAux,sFolderAux,sConfig))
                {
                  strcpy(sFileAux,_sFiles[iStart+iRow].sCName);
                  if(GetFileName(sFileAux,FMAXLEN(sRootAux), 0))
                  {
                    if(strcmp(sRoot,"main")==0 
                    && strcmp(sRootAux,"main")==0
                    && strcmp(sFileAux,_sFiles[iStart+iRow].sCName)==0)
                    {
                      MainDirectory(DELETE,sFileAux,"");
                      MainDirectory(CREATE,sFileAux,sFolderAux);
                      iStart=0;
                      iRow=0;
                      iReadFiles=1;
                    }
                    else
                    {
                      if(FileExist(sRootAux,sFolderAux,sFileAux)==1)
                        iAnswer=PopupContinueYesNo(STR_FILEEXISTS,STR_OVERWRITE,NULL);
                      else
                        iAnswer=1;
                      if(iAnswer==1)
                      {
                        strcpy(sFile,_sFiles[iStart+iRow].sCName);
                        if(CopyFile(sRoot,sFolder,sFile,sRootAux,sFolderAux,sFileAux)==1)
                        {
                          DeleteFile(sRoot,sFolder,sFile);
                          iStart=0;
                          iRow=0;
                          iReadFiles=1;
                        }
                        else
                          PopupMessage(1,"File move error!",NULL,NULL,NULL,NULL);
                      }
                    }
                  }
                }
                iRefresh=1;
              }
              break;
            
            //New folder
            case NODEEXPLNEWF: 
              memset(sFolderAux,0,MAXFNAME);
              iAnswer=GetFolderName(sFolderAux);
              if(iAnswer==1)
              {
                if(FolderExist(sRoot,sFolderAux,sConfig)==1)
                  PopupMessage(1,"Folder exists!",NULL,NULL,NULL,NULL);
                else
                {
                  if(strcmp(sRoot,"main")==0)
                  {
                    if(MainDirectory(CREATE,"",sFolderAux)<0)
                      PopupMessage(1,"Error while","creating folder!",NULL,NULL,NULL);
                    else
                    {
                      iStart=0;
                      iRow=0;
                      iReadFiles=1;
                    }
                  }
                  else
                  {
                    FilePath(sRoot,sFolderAux,"",sFont);
                    if(Bfile_CreateDirectory(sFont)<0)
                      PopupMessage(1,"Error while","creating folder!",NULL,NULL,NULL);
                    else
                    {
                      iStart=0;
                      iRow=0;
                      iReadFiles=1;
                    }
                  }
                }
              }
              iRefresh=1;
              //iReadFiles=1;
              break;
              
            //File delete
            case NODEEXPLDELF:
              if(_sFiles[iStart+iRow].iType==DT_DIRECTORY)
              {
                strcpy(sFolderAux,_sFiles[iStart+iRow].sCName);
                iAnswer=PopupContinueYesNo("Delete folder?",sFolderAux,NULL);
                if(iAnswer==1)
                {
                  if(strcmp(sRoot,"main")==0)
                  {
                    if(MainDirectory(DELETEFOLDER,"",sFolderAux)<0)
                      PopupMessage(1,"Error while","deleting folder!",NULL,NULL,NULL);
                    else
                    {
                      iStart=0;
                      iRow=0;
                      iReadFiles=1;
                    }
                  }
                  else
                  {
                    FilePath(sRoot,sFolderAux,"",sFont);
                    if(Bfile_DeleteDirectory(sFont)<0)
                      PopupMessage(1,"Error while","deleting folder!",NULL,NULL,NULL);
                    else
                    {
                      iStart=0;
                      iRow=0;
                      iReadFiles=1;
                    }
                  }
                }
              }
              iRefresh=1;
              break;
              
            //Help text
            case NODEHELPHELP: 
              /*HelpText();
              iRefresh=1;*/
              break;
                
            //About
            case NODEHELPABOU: 
              AboutPopup();
              break;
              
             //Set up
            case NODEHELPOPTN:
              Configuration(sConfig);
              iStart=0;
              iRow=0;
              iReadFiles=1;
              iRefresh=1;
              break;
              
            //Memory status
            case NODEHELPMEMO: 
              PopupMemory(sConfig);
              break;
            
            //Select main memory
            case NODEEXPLMAIN:
              if(strcmp(sRoot,"main")!=0)
              {
                sprintf(sRoot,"main");
                sprintf(sFolder,"");
                iStart=0;
                iRow=0;
                iReadFiles=1;
                iRefresh=1;
              }
              break;
          
            //Select storage memory
            case NODEEXPLFLS:
              if(strcmp(sRoot,"fls0")!=0)
              {
                sprintf(sRoot,"fls0");
                sprintf(sFolder,"");
                iStart=0;
                iRow=0;
                iReadFiles=1;
                iRefresh=1;
              }
              break;
          
            //Select SD card
            case NODEEXPLCRD:
              if(strcmp(sRoot,"crd0")!=0)
              {
                sprintf(sRoot,"crd0");
                sprintf(sFolder,"");
                iStart=0;
                iRow=0;
                iReadFiles=1;
                iRefresh=1;
              }
              break;
          
          }
          break;
        }
        break;
       
        //Set up
        case KEY_CTRL_SETUP:
          Configuration(sConfig);
          iStart=0;
          iRow=0;
          iReadFiles=1;
          iRefresh=1;
          break;
        
        //Enter
        case KEY_CTRL_EXE:
          if(iFiles==0)
          {
            iExit=1;
          }
          if(_sFiles[iStart+iRow].iType==DT_DIRECTORY)
          {
            strcpy(sFolder,_sFiles[iStart+iRow].sCName);
            iStart=0;
            iRow=0;
            iReadFiles=1;
            iRefresh=1;
          }
          else
          {
            strcpy(sFile,_sFiles[iStart+iRow].sCName);
            iExit=1;
            *iNew=0;
          }
          break;
      
      //Cursor y++
      case KEY_CTRL_DOWN:
        iRow++;
        if(iStart+iRow>iFiles-1)
        {
          iStart=0;
          iRow=0;
        }
        else if(iRow>iLines-1)
        {
          iRow=iLines-1;
          iStart++;
          if(iStart+iRow>=iFiles)
          { 
            iStart=0;
            iRow=0;
          }
        }
        iRefresh=1;
        break;
          
      //Cursor y--
      case KEY_CTRL_UP:    
        iRow--;
        if(iRow<0)
        {
          iRow=0;
          iStart--;
          if(iStart<0)
          { 
            if(iFiles-1>iLines-1)
            {
              iStart=iFiles-1-(iLines-1);
              iRow=iLines-1;
            }
            else
            {
              iStart=0;
              iRow=iFiles-1;
            }
          }
        }
        iRefresh=1;
        break;
    }
  
  }while(iExit==0);

  //Unhide keyboard status
  KeyboardStatusHide(0);
  
  //Return code
  if(iExit==1) 
    return(1);
  else
    return(0);

}

// ----------------------------------------------------------------
// Print file entry
void PrintFileEntry(int iRow,int iStart,int iFiles,int iLines,
                    struct Direc *sDirec, int iColor)
{
  
  //Variables
  char sDir[13];
  char sLine[50];
  
  //Color
  switch(iColor)
  {
    case 1: SetColor(COLNOR); break;
    case 0: SetColor(COLREV); break;
  }
  
  //Switch depending on file type
  switch(sDirec->iType)
  {
    //Folders
    case DT_DIRECTORY:
      sprintf(sDir,"[%s]",sDirec->sCName);
      sprintf(sLine," %-12s        ",sDir);
      PrintStr(0,iRow,sLine);
      break;
    
    //Files
    default:
      sprintf(sLine," %-12s:%6i ",sDirec->sCName,sDirec->iSize);
      PrintStr(0,iRow,sLine);
      break;
  }

  //Arrows
  if(iRow==1 && iStart>0) PrintXY(20*6,1*8,ARROWUP,iColor==1?0:1);
  if(iRow==iLines && iStart<iFiles-iLines) PrintXY(20*6,iLines*8,ARROWDOWN,iColor==1?0:1);

}

// ----------------------------------------------------------------
// Get folder
int GetFolder(char *sRoot, char *sFolder,struct Config *sConfig)
{
  
  //Constants
  #define MAXROWS 4
  
  //Variables
  int i,j;
  int iError;
  int iExit;
  int iFolders;
  unsigned char cSort;
  int iHandle;
  int iRefresh=1;
  char sStr1[50];
  char sStr2[50];
  int iStart=0;
  int iRow=0;
  int iARow=0;
  int iCode;
  int iSDPresent;
  unsigned int iKey;
  char sRoot0[5];
  FONTCHARACTER sFont[MAXPATH];
  struct Direc sDirec0;
  
  //Prepare display
  KeyboardStatusHide(1);
  SaveDisp(SAVEDISP_PAGE1);
  MenuStoreBar();
  PopUpWin(5);
  SetFont(FONTL);
  SetColor(COLNOR);
  PrintStr(2,1,"Select folder:");
  MenuSetBar(MENUBAROKAY);

  //Detect SD Card
  if(sConfig->iTrySD==0)
    iSDPresent=0;
  else
    iSDPresent=SDCardPresent();
  
  //Get folder list
  iFolders=0;
  for(j=0;j<3;j++)
  {
    if(j==0) 
    { 
      sDirec0.cSort=0;
      strcpy(sDirec0.sCName,"MM\\");
      AppendDirEntry(iFolders,_sFolders,&sDirec0);
      cSort=1;
      iFolders++;
      FilePath("main","","*.*",sFont);
      sprintf(sRoot0,"main");
      ReadDirectory(sRoot0,"",_sFolders,&iFolders,sConfig->iMaxFolders,cSort,1,0); 
    }
    if(j==1) 
    { 
      sDirec0.cSort=2;
      strcpy(sDirec0.sCName,"SM\\");
      AppendDirEntry(iFolders,_sFolders,&sDirec0);
      cSort=3;
      iFolders++;
      FilePath("fls0","","*.*",sFont);
      sprintf(sRoot0,"fls0");
      ReadDirectory(sRoot0,"",_sFolders,&iFolders,sConfig->iMaxFolders,cSort,1,0); 
    }
    if(j==2) 
    {
      if(iSDPresent==0) break;
      sDirec0.cSort=4;
      strcpy(sDirec0.sCName,"SD\\");
      AppendDirEntry(iFolders,_sFolders,&sDirec0);
      cSort=5;
      iFolders++;
      FilePath("crd0","","*.*",sFont);
      sprintf(sRoot0,"crd0");
      ReadDirectory(sRoot0,"",_sFolders,&iFolders,sConfig->iMaxFolders,cSort,1,0); 
    }
  }
  
  //Main loop
  iExit=0;
  do{
      
    //Rewrite screen
    if(iRefresh==1)
    {
      SetFont(FONTL);
      SetColor(COLNOR);
      for(i=0;i<MAXROWS;i++)
      {
        if(i+iStart<iFolders)
          PrintFolderEntry(2+i,&_sFolders[iStart+i],COLNOR);
        else
          PrintStr(2,2+i,"                 ");
      }
    }
    
    //Cursor position
    if(iRow!=iARow || iRefresh!=0)
    {
      PrintFolderEntry(2+iARow,&_sFolders[iStart+iARow],COLNOR);
      PrintFolderEntry(2+iRow ,&_sFolders[iStart+iRow ],COLREV);
    }    
    
    //Flush screen
    if(iRefresh!=0) Bdisp_PutDisp_DD();
    
    //Clear flags
    iRefresh=0;
    
    //Previous cursor position
    iARow=iRow;
    
    //Get Key
    iKey=GetKeyb();
      
    //Process keys
    switch(iKey)
    {
      //Process menu commands
      case KEY_CTRL_F1:
      case KEY_CTRL_F2:
      case KEY_CTRL_F3:
      case KEY_CTRL_F4:
      case KEY_CTRL_F5:
      case KEY_CTRL_F6:
        iCode=MenuFunctionKey(iKey);
        if(iCode!=NODENOFUNCT)
        {
          switch(iCode)
          {
          
            //Ok
            case NODEOKAYOK:
              iExit=1;
              i=iStart+iRow;
              break;
            
            //Exit
            case NODEOKAYEX:
              iExit=2;
              break;
          }
          break;
        }
        break;
       
        //Exit
        case KEY_CTRL_EXIT:
          iExit=2;
          break;
          
        //Enter
        case KEY_CTRL_EXE:
          iExit=1;
          i=iStart+iRow;
          break;
      
      //Cursor y++
      case KEY_CTRL_DOWN:
        iRow++;
        if(iStart+iRow>iFolders-1)
        {
          iStart=0;
          iRow=0;
        }
        else if(iRow>MAXROWS-1)
        {
          iRow=MAXROWS-1;
          iStart++;
          if(iStart+iRow>=iFolders)
          { 
            iStart=0;
            iRow=0;
          }
        }
        iRefresh=1;
        break;
          
      //Cursor y--
      case KEY_CTRL_UP:    
        iRow--;
        if(iRow<0)
        {
          iRow=0;
          iStart--;
          if(iStart<0)
          { 
            if(iFolders-1>MAXROWS-1)
            {
              iStart=iFolders-1-(MAXROWS-1);
              iRow=MAXROWS-1;
            }
            else
            {
              iStart=0;
              iRow=iFolders-1;
            }
          }
        }
        iRefresh=1;
        break;
    }
  
  }while(iExit==0);

  //Restore display
  KeyboardStatusHide(0);
  RestoreDisp(SAVEDISP_PAGE1);
  MenuRestoreBar();
  
  //Return code
  if(iExit==1) 
  {
    switch(_sFolders[i].cSort)
    {
      case 0: sprintf(sRoot,"main");     
              sprintf(sFolder,"");
              break;
      case 1: sprintf(sRoot,"main");     
              sprintf(sFolder,_sFolders[i].sCName);
              break;
      case 2: sprintf(sRoot,"fls0");     
              sprintf(sFolder,"");
              break;
      case 3: sprintf(sRoot,"fls0");     
              sprintf(sFolder,_sFolders[i].sCName);
              break;
      case 4: sprintf(sRoot,"crd0");     
              sprintf(sFolder,"");
              break;
      case 5: sprintf(sRoot,"crd0");     
              sprintf(sFolder,_sFolders[i].sCName);
              break;
    }
    return(1);
  }
  else
  {
    return(0);
  }

}

// ----------------------------------------------------------------
// Print file entry
void PrintFolderEntry(int iRow,struct Direc *sDirec, int iColor)
{
  //Variables
  char sStr1[50];
  char sStr2[50];
  
  //Format
  switch(sDirec->cSort)
  {
    case 0:
    case 2:
    case 4:
      sprintf(sStr2,"%s",sDirec->sCName);
      break;
    case 1:
    case 3:
    case 5:
      sprintf(sStr2," %s",sDirec->sCName);
      break;
  }
  
  //Print
  SetColor(iColor);
  sprintf(sStr1,"%-9s        ",sStr2);
  PrintStr(2,iRow,sStr1);
  
}

// ----------------------------------------------------------------
// Configuration 
void Configuration(struct Config *sConfig)
{
  //Constants
  #define CONFIGLINES 16
  
  //Variables
  int i;
  int iExit;
  int iRefresh=1;
  static int iStart=0;
  static int iRow=0;
  static int iARow=0;
  int iCode;
  int iNew;
  unsigned int iKey;
  char sRoot[5]="";          
  char sFolder[MAXFNAME]=""; 
  char sFile[MAXFNAME]="";   
  
  //Init screen
  MenuStoreBar();
  KeyboardStatusHideStore();
  KeyboardStatusHide(1);
  Bdisp_AllClr_DDVRAM();
  MenuSetBar(MENUBAREXPL); 
  
  //Main loop
  iExit=0;
  do{
      
    //Rewrite screen
    if(iRefresh==1)
    {
      SetFont(FONTL);
      SetColor(COLNOR);
      for(i=0;i<7;i++)
      {
        if(i+iStart<CONFIGLINES)
          PrintConfigEntry(i,iStart+i,sConfig,1);
      }
    }
    
    //Cursor position
    if(iRow!=iARow || iRefresh!=0)
    {
      PrintConfigEntry(iARow,iStart+iARow,sConfig,1);
      PrintConfigEntry(iRow,iStart+iRow,sConfig,0);
      iRefresh=1;
    }    
    
    //Set menu bar
    /*switch(iRow+iStart)
    {
      case CONFIGTRYSD : MenuSetBar(MENUBARTRSD); break;
      case CONFIGHIDSYS: MenuSetBar(MENUBARHSYS); break;
      case CONFIGNLMODE: MenuSetBar(MENUBARNLMO); break;
      case CONFIGWWRAP : MenuSetBar(MENUBARWWRA); break;
      case CONFIGDFRE  : MenuSetBar(MENUBARDFRE); break;
      case CONFIGDROO  : MenuSetBar(MENUBARDROO); break;
      case CONFIGFONT  : MenuSetBar(MENUBARFONT); break;
      case CONFIGINFO  : MenuSetBar(MENUBARINFO); break;
      case CONFIGAOPEN : MenuSetBar(MENUBARAOPE); break;
      case CONFIGAROOT : MenuSetBar(MENUBARACFG); break;
      case CONFIGANAME : MenuSetBar(MENUBARACFG); break;
      case CONFIGAFOLDR: MenuSetBar(MENUBARACFG); break;
      case CONFIGTEXTB:  MenuSetBar(MENUBARTXTB); break;
      case CONFIGCLIPB:  MenuSetBar(MENUBARCLIB); break;
      case CONFIGNFIL :  MenuSetBar(MENUBARNFIL); break;
      case CONFIGNFOL :  MenuSetBar(MENUBARNFOL); break;
    }*/
    
    //Flush screen
    if(iRefresh!=0)
    {
      Bdisp_PutDisp_DD();
      iRefresh=0;
    }
    
    //Previous cursor position
    iARow=iRow;
    
    //Get Key
    iKey=GetKeyb();
      
    //Process keys
    switch(iKey)
    {
      //Process menu commands
      case KEY_CTRL_F1:
      case KEY_CTRL_F2:
      case KEY_CTRL_F3:
      case KEY_CTRL_F4:
      case KEY_CTRL_F5:
      case KEY_CTRL_F6:
        iCode=MenuFunctionKey(iKey);
        if(iCode!=NODENOFUNCT)
        {
          switch(iCode)
          {
          
            //Yes
            case NODETRYSDYES:
              if(sConfig->iTrySD==0)
              {
                sConfig->iTrySD=1;
                iRefresh=1;
              }
              break;
            
            //No
            case NODETRYSDNO:
              if(sConfig->iTrySD==1)
              {
                sConfig->iTrySD=0;
                iRefresh=1;
              }
              break;

            //Hide system files -> Yes
            case NODEHSYSYES:
              if(sConfig->iHideSysFiles==0)
              {
                sConfig->iHideSysFiles=1;
                iRefresh=1;
              }
              break;
            
            //Hide system files -> No
            case NODEHSYSNO:
              if(sConfig->iHideSysFiles==1)
              {
                sConfig->iHideSysFiles=0;
                iRefresh=1;
              }
              break;

            //Info bar -> Folder
            case NODEINFOFOLD:
              if(sConfig->iInfo!=INFOBARFOLDER)
              {
                sConfig->iInfo=INFOBARFOLDER;
                iRefresh=1;
              }
              break;

            //Info bar -> Cursor
            case NODEINFOCURS:
              if(sConfig->iInfo!=INFOBARCURSOR)
              {
                sConfig->iInfo=INFOBARCURSOR;
                iRefresh=1;
              }
              break;

            //Word wrap enable
            case NODEWWRAPON:
              if(sConfig->iWordWrap!=1)
              {
                sConfig->iWordWrap=1;
                iRefresh=1;
              }
              break;

            //Word wrap disnable
            case NODEWWRAPOFF:
              if(sConfig->iWordWrap!=0)
              {
                sConfig->iWordWrap=0;
                iRefresh=1;
              }
              break;

            //Display bytes free in explorer (yes)
            case NODEDFREYES:
              if(sConfig->iDispFree!=1)
              {
                sConfig->iDispFree=1;
                iRefresh=1;
              }
              break;

            //Default root (main)
            case NODEDROOMAIN:
              if(strcmp(sConfig->sDefRoot,"main")!=0)
              {
                strcpy(sConfig->sDefRoot,"main");
                iRefresh=1;
              }
              break;

            //Default root (smem)
            case NODEDROOSMEM:
              if(strcmp(sConfig->sDefRoot,"fls0")!=0)
              {
                strcpy(sConfig->sDefRoot,"fls0");
                iRefresh=1;
              }
              break;

            //Default root (sdc)
            case NODEDROOSDC:
              if(strcmp(sConfig->sDefRoot,"crd0")!=0)
              {
                strcpy(sConfig->sDefRoot,"crd0");
                iRefresh=1;
              }
              break;

            //Display bytes free in explorer (no)
            case NODEDFRENO:
              if(sConfig->iDispFree!=0)
              {
                sConfig->iDispFree=0;
                iRefresh=1;
              }
              break;

            //Font 3x5
            case NODEFONT3X5:
              if(sConfig->iFont!=FONTS)
              {
                sConfig->iFont=FONTS;
                iRefresh=1;
              }
              break;
            
            //Font 3x5
            case NODEFONT3X6:
              if(sConfig->iFont!=FONTT)
              {
                sConfig->iFont=FONTT;
                iRefresh=1;
              }
              break;
            
            //Font 3x5
            case NODEFONT4X6:
              if(sConfig->iFont!=FONTM)
              {
                sConfig->iFont=FONTM;
                iRefresh=1;
              }
              break;
            
            //Font 3x5
            case NODEFONT5X7:
              if(sConfig->iFont!=FONTL)
              {
                sConfig->iFont=FONTL;
                iRefresh=1;
              }
              break;
            
            //New line mode windows
            case NODENLMOWIN:
              if(sConfig->iNLMode!=NEWLMODECRLF)
              {
                sConfig->iNLMode=NEWLMODECRLF;
                iRefresh=1;
              }
              break;
            
            //New line mode unix
            case NODENLMOUNIX:
              if(sConfig->iNLMode!=NEWLMODELF)
              {
                sConfig->iNLMode=NEWLMODELF;
                iRefresh=1;
              }
              break;
            
            //Auto open file enable
            case NODEAOPEYES:
              if(sConfig->iAutoOpen!=1)
              {
                sConfig->iAutoOpen=1;
                iRefresh=1;
              }
              break;
            
            //Auto open file disable
            case NODEAOPENO:
              if(sConfig->iAutoOpen!=0)
              {
                sConfig->iAutoOpen=0;
                iRefresh=1;
              }
              break;
            
            //Auto open file set
            case NODEACFGSET:
              sprintf(sRoot,sConfig->sAutoRoot);
              sprintf(sFolder,sConfig->sAutoFolder);
              if(Explorer(EXPLORERAUTO,sRoot,sFolder,sFile,sConfig,&iNew))
              {
                sprintf(sConfig->sAutoRoot,sRoot);
                sprintf(sConfig->sAutoFile,sFile);
                sprintf(sConfig->sAutoFolder,sFolder);
              }
              KeyboardStatusHide(1);
              iRefresh=1;
              break;
            
            //Auto open file clear
            case NODEACFGCLR:
              if(strlen(sConfig->sAutoRoot)!=0 
              || strlen(sConfig->sAutoFile)!=0
              || strlen(sConfig->sAutoFolder)!=0)
              {
                sprintf(sConfig->sAutoRoot,"fls0");
                sprintf(sConfig->sAutoFile,"");
                sprintf(sConfig->sAutoFolder,"");
                iRefresh=1;
              }
              break;
            
            //Text buffer 4Kb
            case NODETXTB04K:
              if(sConfig->iTextBuffer!=4096)
              {
                sConfig->iTextBuffer=4096;
                iRefresh=1;
              }
              break;
            
            //Text buffer 8Kb
            case NODETXTB08K:
              if(sConfig->iTextBuffer!=8192)
              {
                sConfig->iTextBuffer=8192;
                iRefresh=1;
              }
              break;
            
            //Text buffer 16Kb
            case NODETXTB16K:
              if(sConfig->iTextBuffer!=16384)
              {
                sConfig->iTextBuffer=16384;
                iRefresh=1;
              }
              break;
            
            //Text buffer 24Kb
            case NODETXTB24K:
              if(sConfig->iTextBuffer!=24576)
              {
                sConfig->iTextBuffer=24576;
                iRefresh=1;
              }
              break;
            
            //Text buffer 32Kb
            case NODETXTB32K:
              if(sConfig->iTextBuffer!=32768)
              {
                sConfig->iTextBuffer=32768;
                iRefresh=1;
              }
              break;
            
            //Text buffer 40Kb
            case NODETXTB40K:
              if(sConfig->iTextBuffer!=40960)
              {
                sConfig->iTextBuffer=40960;
                iRefresh=1;
              }
              break;
            
            //Clip buffer 1Kb
            case NODECLIB01K:
              if(sConfig->iClipBuffer!=1024)
              {
                sConfig->iClipBuffer=1024;
                iRefresh=1;
              }
              break;
            
            //Clip buffer 2Kb
            case NODECLIB02K:
              if(sConfig->iClipBuffer!=2048)
              {
                sConfig->iClipBuffer=2048;
                iRefresh=1;
              }
              break;
            
            //Clip buffer 4Kb
            case NODECLIB04K:
              if(sConfig->iClipBuffer!=4096)
              {
                sConfig->iClipBuffer=4096;
                iRefresh=1;
              }
              break;
            
            //Clip buffer 8Kb
            case NODECLIB08K:
              if(sConfig->iClipBuffer!=8192)
              {
                sConfig->iClipBuffer=8192;
                iRefresh=1;
              }
              break;
            
            //Clip buffer 12Kb
            case NODECLIB12K:
              if(sConfig->iClipBuffer!=12288)
              {
                sConfig->iClipBuffer=12288;
                iRefresh=1;
              }
              break;
            
            //Clip buffer 16Kb
            case NODECLIB16K:
              if(sConfig->iClipBuffer!=16384)
              {
                sConfig->iClipBuffer=16384;
                iRefresh=1;
              }
              break;
            
            //Number of files 000
            case NODENFIL000:
              if(sConfig->iMaxFiles!=32)
              {
                sConfig->iMaxFiles=32;
                iRefresh=1;
              }
              break;
            
            //Number of files 001
            case NODENFIL001:
              if(sConfig->iMaxFiles!=48)
              {
                sConfig->iMaxFiles=48;
                iRefresh=1;
              }
              break;
            
            //Number of files 002
            case NODENFIL002:
              if(sConfig->iMaxFiles!=64)
              {
                sConfig->iMaxFiles=64;
                iRefresh=1;
              }
              break;
            
            //Number of files 003
            case NODENFIL003:
              if(sConfig->iMaxFiles!=96)
              {
                sConfig->iMaxFiles=96;
                iRefresh=1;
              }
              break;
            
            //Number of files 004
            case NODENFIL004:
              if(sConfig->iMaxFiles!=128)
              {
                sConfig->iMaxFiles=128;
                iRefresh=1;
              }
              break;
            
            //Number of files 005
            case NODENFIL005:
              if(sConfig->iMaxFiles!=256)
              {
                sConfig->iMaxFiles=256;
                iRefresh=1;
              }
              break;
            
            //Number of folders 000
            case NODENFOL000:
              if(sConfig->iMaxFolders!=16)
              {
                sConfig->iMaxFolders=16;
                iRefresh=1;
              }
              break;
            
            //Number of folders 001
            case NODENFOL001:
              if(sConfig->iMaxFolders!=32)
              {
                sConfig->iMaxFolders=32;
                iRefresh=1;
              }
              break;
            
            //Number of folders 002
            case NODENFOL002:
              if(sConfig->iMaxFolders!=48)
              {
                sConfig->iMaxFolders=48;
                iRefresh=1;
              }
              break;
            
            //Number of folders 003
            case NODENFOL003:
              if(sConfig->iMaxFolders!=64)
              {
                sConfig->iMaxFolders=64;
                iRefresh=1;
              }
              break;
            
            //Number of folders 004
            case NODENFOL004:
              if(sConfig->iMaxFolders!=96)
              {
                sConfig->iMaxFolders=96;
                iRefresh=1;
              }
              break;
            
            //Number of folders 005
            case NODENFOL005:
              if(sConfig->iMaxFolders!=128)
              {
                sConfig->iMaxFolders=128;
                iRefresh=1;
              }
              break;
            
          }
          break;
        }
        break;
       
      //Exit
      case KEY_CTRL_EXIT:
        iExit=1;
        break;
        
      //Enter
      case KEY_CTRL_EXE:
        iExit=1;
        break;
        
      //Cursor y++
      case KEY_CTRL_DOWN:
        iRow++;
        if(iStart+iRow>CONFIGLINES-1)
        {
          iStart=0;
          iRow=0;
        }
        else if(iRow>6)
        {
          iRow=6;
          iStart++;
          if(iStart+iRow>=CONFIGLINES)
          { 
            iStart=0;
            iRow=0;
          }
        }
        iRefresh=1;
        break;
          
      //Cursor y--
      case KEY_CTRL_UP:    
        iRow--;
        if(iRow<0)
        {
          iRow=0;
          iStart--;
          if(iStart<0)
          { 
            if(CONFIGLINES-1>6)
            {
              iStart=CONFIGLINES-1-6;
              iRow=6;
            }
            else
            {
              iStart=0;
              iRow=CONFIGLINES-1;
            }
          }
        }
        iRefresh=1;
        break;
    }
  
    //Export configuration every time something is changed
    ConfigExport(sConfig);
  
  }while(iExit==0);

  //Unhide keyboard status
  KeyboardStatusHideRestore();
  MenuRestoreBar();
  
}

// ----------------------------------------------------------------
// Print config entry
void PrintConfigEntry(int iRow,int iOptio, struct Config *sConfig, int iColor)
{
  
  //Variables
  char sNumber[10];
  
  //Color
  switch(iColor)
  {
    case 1: SetColor(COLNOR); break;
    case 0: SetColor(COLREV); break;
  }
  
  //Switch depending on congiguration option
  switch(iOptio)
  {
    //Try SD
    case CONFIGTRYSD:
      PrintStr(0,iRow,"Try SDC   :");
      if(sConfig->iTrySD==1)
        PrintStr(11,iRow,"Yes       ");
      else
        PrintStr(11,iRow,"No        ");
      break;
    
    //Hide system files
    case CONFIGHIDSYS:
      PrintStr(0,iRow,"Syst.files:");
      if(sConfig->iHideSysFiles==1)
        PrintStr(11,iRow,"Hidden    ");
      else
        PrintStr(11,iRow,"Displayed ");
      break;
    
    //New line mode
    case CONFIGNLMODE:
      PrintStr(0,iRow,"New line  :");
      switch(sConfig->iNLMode)
      {
        case NEWLMODECRLF: PrintStr(11,iRow,"CR+LF(Win)"); break;
        case NEWLMODELF  : PrintStr(11,iRow,"LF(Unix)  "); break;
      }
      break;
    
    //New line mode
    case CONFIGWWRAP:
      PrintStr(0,iRow,"Word Wrap :");
      switch(sConfig->iWordWrap)
      {
        case 1: PrintStr(11,iRow,"On        "); break;
        case 0: PrintStr(11,iRow,"Off       "); break;
      }
      break;
    
    //Display bytes free in explorer
    case CONFIGDFRE:
      PrintStr(0,iRow,"Bytes free:");
      switch(sConfig->iDispFree)
      {
        case 1: PrintStr(11,iRow,"Displayed "); break;
        case 0: PrintStr(11,iRow,"Not disp. "); break;
      }
      break;
    
    //Default root
    case CONFIGDROO:
      PrintStr(0,iRow,"Def. root :");
      if(strcmp(sConfig->sDefRoot,"main")==0)
        PrintStr(11,iRow,"Main Mem. "); 
      else if(strcmp(sConfig->sDefRoot,"fls0")==0)
        PrintStr(11,iRow,"Sto.Memory"); 
      else if(strcmp(sConfig->sDefRoot,"crd0")==0)
        PrintStr(11,iRow,"SD Card   "); 
      break;
    
    //Info bar
    case CONFIGINFO:
      PrintStr(0,iRow,"Info bar  :");
      switch(sConfig->iInfo)
      {
        case INFOBARFOLDER: PrintStr(11,iRow,"Folder    "); break;
        case INFOBARCURSOR: PrintStr(11,iRow,"Cursor    "); break;
      }
      break;
    
    //Font
    case CONFIGFONT:
      PrintStr(0,iRow,"Font size :");
      switch(sConfig->iFont)
      {
        case FONTS: PrintStr(11,iRow,"32col,8lin"); break;
        case FONTT: PrintStr(11,iRow,"32col,7lin"); break;
        case FONTM: PrintStr(11,iRow,"25col,7lin"); break;
        case FONTL: PrintStr(11,iRow,"21col,6lin"); break;
      }
      break;
    
    //Auto open
    case CONFIGAOPEN:
      PrintStr(0,iRow,"Auto Open :");
      switch(sConfig->iAutoOpen)
      {
        case 1: PrintStr(11,iRow,"Enabled   "); break;
        case 0: PrintStr(11,iRow,"Disabled  "); break;
      }
      break;
    
    //Auto root
    case CONFIGAROOT:
      PrintStr(11,iRow,"          ");
      PrintStr(0,iRow,"Auto Root :");
      if(strcmp(sConfig->sAutoRoot,"main")==0)
        PrintStr(11,iRow,"Main Mem. "); 
      else if(strcmp(sConfig->sAutoRoot,"fls0")==0)
        PrintStr(11,iRow,"Sto.Memory"); 
      else if(strcmp(sConfig->sAutoRoot,"crd0")==0)
        PrintStr(11,iRow,"SD Card   "); 
      break;
    
    //Auto name
    case CONFIGANAME:
      PrintStr(0,iRow,"Auto Name :");
      PrintStr(11,iRow,"          ");
      SetFont(FONTM);
      if(strlen(sConfig->sAutoFile)>0)
        PrintStrXY(11*6,1+iRow*8,sConfig->sAutoFile);
      else
        PrintStrXY(11*6,1+iRow*8,"(not set)");
      SetFont(FONTL);
      break;
    
    //Auto folder
    case CONFIGAFOLDR:
      PrintStr(0,iRow,"Auto Foldr:");
      PrintStr(11,iRow,"          ");
      SetFont(FONTM);
      if(strlen(sConfig->sAutoFolder)>0)
        PrintStrXY(11*6,1+iRow*8,sConfig->sAutoFolder);
      else
        PrintStrXY(11*6,1+iRow*8,"(not set)");
      SetFont(FONTL);
      break;
    
    //Text buffer
    case CONFIGTEXTB:
      PrintStr(0,iRow,"Text buff.:");
      PrintStr(11,iRow,"          ");
      sprintf(sNumber,"%i",sConfig->iTextBuffer);
      PrintStr(11,iRow,sNumber);
      break;
    
    //Clip buffer
    case CONFIGCLIPB:
      PrintStr(0,iRow,"Clip buff.:");
      PrintStr(11,iRow,"          ");
      sprintf(sNumber,"%i",sConfig->iClipBuffer);
      PrintStr(11,iRow,sNumber);
      break;
    
    //Maximum number of files per directory
    case CONFIGNFIL:
      PrintStr(0,iRow,"Files/Dir.:");
      PrintStr(11,iRow,"          ");
      sprintf(sNumber,"%i",sConfig->iMaxFiles);
      PrintStr(11,iRow,sNumber);
      break;
    
    //Maximum number of files per directory
    case CONFIGNFOL:
      PrintStr(0,iRow,"Foldr.Max.:");
      PrintStr(11,iRow,"          ");
      sprintf(sNumber,"%i",sConfig->iMaxFolders);
      PrintStr(11,iRow,sNumber);
      break;
    
  }

}

// ----------------------------------------------------------------
// Import Configuration
void ConfigImport(struct Config *sConfig)
{
  //Variables
  int i;
  int iHandle = -1;
  FONTCHARACTER defaultDir[] = {'\\', '\\', 'f', 'l', 's', '0', '\\', 'C', 'a', 's', 'i', 'o', 'P', 'y', 0};
  //Open file
  /*iHandle=Bfile_OpenMainMemory(CONFIGFILE);
  if(iHandle>=0)
  {
    Bfile_ReadFile(iHandle,sConfig,sizeof(struct Config),0);
    Bfile_CloseFile(iHandle);
  }*/
  Bfile_CreateDirectory(defaultDir);
  //Initialize configuration on error
  if(iHandle<0 || strcmp(sConfig->sVersion,EDITVERSION)!=0)
  {
    strcpy(sConfig->sVersion,EDITVERSION);
    strcpy(sConfig->sDefRoot,"fls0");
    sConfig->iTrySD=1;
    sConfig->iHideSysFiles=1;
    sConfig->iNLMode=NEWLMODECRLF;
    sConfig->iWordWrap=0;
    sConfig->iDispFree=0;
    sConfig->iFont=FONTT;
    sConfig->iInfo=INFOBARCURSOR;
    sConfig->iAutoOpen=0;
    strcpy(sConfig->sAutoRoot,"fls0");
    strcpy(sConfig->sAutoFile,"");
    strcpy(sConfig->sAutoFolder,"CasioPy");
    sConfig->iTextBuffer=TXTMINSIZE;
    sConfig->iClipBuffer=TXTMINCLIP;
    sConfig->iMaxFiles=MINFILES;
    sConfig->iMaxFolders=MINFOLDERS;
    for(i=0;i<MAXCHARMAP;i++){
      sConfig->sCharMap[i].iKey=-1;
      sConfig->sCharMap[i].cAscii=0;
    }  
    //ConfigExport(sConfig);
  }
  
}

// ----------------------------------------------------------------
// Export configuration
void ConfigExport(struct Config *sConfig)
{
  //Variables
  int iHandle;
  
  //Delete previous configuration file
  Bfile_DeleteMainMemory(CONFIGFILE);
  
  //Create new configuration file
  if(Bfile_CreateMainMemory(CONFIGFILE)==0)
  {
    iHandle=Bfile_OpenMainMemory(CONFIGFILE);
    if(iHandle>=0)
    {
      Bfile_WriteFile(iHandle,sConfig,sizeof(struct Config));
      Bfile_CloseFile(iHandle);
    }
  }
  
}

// ----------------------------------------------------------------
// Check folder exists
int FolderExist(char *sRoot, char *sFolder,struct Config *sConfig)
{
  //Variables
  int i;
  int iHandle;
  int iFolders;
  //int iFiles;
  int iFound=0;
  FONTCHARACTER sFont[MAXPATH];
  
  //Check folder (Main memory)
  if(strcmp(sRoot,"main")==0)
  {
    if(MainDirectory(CHECKENTRY,"",sFolder)==0) iFound=1;
  }
  
  //Check folder (Storage memory & SD Card)
  else
  {
  
    //Read root directory
    ReadDirectory(sRoot,"",_sFolders,&iFolders,sConfig->iMaxFolders,0,1,0); 
    //ReadDirectory(sRoot,sFolder,_sFiles,&iFiles,sConfig->iMaxFiles,1,0,0); 
  
    //Check if folder exists
    iFound=0;
    for(i=0;i<iFolders;i++)
    {
      if(strcmp(sFolder,_sFiles[i].sCName)==0) 
      //&& _sFiles[i].iType==DT_DIRECTORY)
      {
        iFound=1; 
        break;
      }
    }
  }
  
  //Return code
  if(iFound==1)
    return(1);
  else
    return(0);
}

// ----------------------------------------------------------------
// Check file exists
int FileExist(char *sRoot, char *sFolder, char *sFile)
{
  //Variables
  int iHandle;
  FONTCHARACTER sFont[MAXPATH];
  
  //Open file
  if(strcmp(sRoot,"main")!=0)
  {
    FilePath(sRoot,sFolder,sFile,sFont);
    iHandle=Bfile_OpenFile(sFont,_OPENMODE_READ);
  }
  else
  {
    iHandle=Bfile_OpenMainMemory(sFile);
  }
  Bfile_CloseFile(iHandle);
  
  //Return code
  if(iHandle<0)
    return(0);
  else
    return(1);
}

// ----------------------------------------------------------------
// Read file
int ReadFile(char *sRoot, char *sFolder, char *sFile,
             char *sText, int *iBinary)
{
  //Variables
  int i;
  int iHandle;
  int iError;
  int iLen;
  int iSize;
  FONTCHARACTER sFont[MAXPATH];
  
  //Message
  PopupMessage(0,"Reading file...",NULL,NULL,NULL,NULL);
  
  //Open file
  if(strcmp(sRoot,"main")!=0)
  {
    FilePath(sRoot,sFolder,sFile,sFont);
    iHandle=Bfile_OpenFile(sFont,_OPENMODE_READ);
  }
  else
  {
    iHandle=Bfile_OpenMainMemory(sFile);
  }
  if(iHandle<0) return(0);
  
  //Read file
  iSize=Bfile_GetFileSize(iHandle);
  if(strcmp(sRoot,"main")==0) iSize-=MAINHEADER;
  if(iSize>_iTextSize-1)
  { 
    iSize=_iTextSize-1;
    PopupMessage(1,"File too big.","Not loaded","completely!",NULL,NULL);
  }
  iError=Bfile_ReadFile(iHandle,sText,iSize,0);
  Bfile_CloseFile(iHandle);

  //Return error
  if(iError<0)
  {
    sText[0]=ENDMARK;
    sText[1]=0;
    return(0);
  }
  
  //Place end of text according to characters read
  iLen=iError;
  if(iLen>_iTextSize-1) iLen=_iTextSize-1;
  sText[iLen]=0;
  
  //Filter non ASCII chars
  *iBinary=0;
  for(i=0;i<iLen;i++)
  {
    if(sText[i]!=NEWLINELF && sText[i]!=NEWLINECR 
    && sText[i]!=ENDMARK   && sText[i]<32)
    { 
      *iBinary=1;
      sText[i]=127;
    }
  }
    
  //Convert new line to LF
  ConvertNewLine2LF(sText);
  
  //Place end mark
  iLen=strlen(sText);
  if(sText[iLen-1]!=ENDMARK)
  {
    sText[iLen+0]=ENDMARK;
    sText[iLen+1]=0;
  }
  return(1);
}

// ----------------------------------------------------------------
// Write file
int WriteFile(char *sRoot, char *sFolder, char *sFile, 
              char *sText,int iNLMode)
{
  //Variables
  int i;
  int iSpaces;
  int iHandle;
  int iError;
  int iRCode=1;
  int iLen;
  char buffer[50];
  FONTCHARACTER sFont[MAXPATH];
  
  //Message
  PopupMessage(0,STR_SAVINGFILE,NULL,NULL,NULL,NULL);
  
  //Convert new line to CR+LF
  if(iNLMode==NEWLMODECRLF) ConvertNewLine2CRLF(sText);


  //Remove end mark
  iLen=strlen(sText);
  sText[iLen-1]=0;
  iLen--;
  sprintf(buffer, "%d", iLen);
  //PopupMessage(0,buffer,NULL,NULL,NULL,NULL);
  
  //Add additional spaces at end (main memory only)
  if(strcmp(sRoot,"main")==0)
  {
    iSpaces=((iLen%4)!=0?4-(iLen%4):0);
    for(i=0;i<iSpaces;i++) sText[iLen+i]=' ';
    iLen=iLen+iSpaces;
    sText[iLen]=0;
  }
  
  //Delete previous file
  if(strcmp(sRoot,"main")!=0)
  {
    FilePath(sRoot,sFolder,sFile,sFont);
    Bfile_DeleteFile(sFont);
  }
  else
  {
    Bfile_DeleteMainMemory(sFile);
    MainDirectory(DELETE,sFile,"");
  }
  
  //Create new file
  if(strcmp(sRoot,"main")!=0)
    iError=Bfile_CreateFile(sFont,iLen);
  else
    iError=Bfile_CreateMainMemory(sFile);

  if(iError!=0)
    iRCode=0;
  
  //Continue
  else
  {
    //Open file
    if(strcmp(sRoot,"main")!=0)
      iHandle=Bfile_OpenFile(sFont,_OPENMODE_WRITE);
    else
      iHandle=Bfile_OpenMainMemory(sFile);
    if(iHandle<0) 
      iRCode=0;
      
    //Continue
    else
    {
      //Write to file
      iError=Bfile_WriteFile(iHandle,sText,iLen);
      Bfile_CloseFile(iHandle);
      if(iError<0) iRCode=0;
    }
  }
  
  //Convert new line to LF
  if(iNLMode==NEWLMODECRLF) ConvertNewLine2LF(sText);
  
  //Place end mark again
  iLen=strlen(sText);
  sText[iLen+0]=ENDMARK;
  sText[iLen+1]=0;
  
  //Update directory in main memory
  MainDirectory(CREATE,sFile,sFolder);
  
  //PopupMessage(0,"Writing file...",NULL,NULL,NULL,NULL);
  

  
  //Return code
  return(iRCode);
}

// ----------------------------------------------------------------
// Copy file
int CopyFile(char *sRoot1, char *sFolder1, char *sFile1,
             char *sRoot2, char *sFolder2, char *sFile2)
{
  //Constants
  #define COPYBUFF 512
  
  //Variables
  int i;
  int iError;
  int iErrFlag;
  int iLen0;
  int iLen;
  int iSpaces;
  int iSize;
  int iSize0;
  int iPos;
  int iHandle1;
  int iHandle2;
  FONTCHARACTER sFont1[MAXPATH];
  FONTCHARACTER sFont2[MAXPATH];
  char sBuff[COPYBUFF];
  char sSpaces[4];
  
  //Message
  PopupMessage(0,"Copying file...",NULL,NULL,NULL,NULL);
  
  //Prepare source file
  if(strcmp(sRoot1,"main")!=0)
  {
    FilePath(sRoot1,sFolder1,sFile1,sFont1);
    iHandle1=Bfile_OpenFile(sFont1,_OPENMODE_READ);
  }
  else
  {
    iHandle1=Bfile_OpenMainMemory(sFile1);
  }
  if(iHandle1<0)
  {
    PopupMessage(1,"Cannot open","source file!",NULL,NULL,NULL);
    return(0);
  }
  
  //File size
  if(strcmp(sRoot1,"main")!=0)
    iSize=Bfile_GetFileSize(iHandle1);
  else
    iSize=Bfile_GetFileSize(iHandle1)-MAINHEADER;

  //Prepare destination file
  if(strcmp(sRoot2,"main")!=0)
  {
    FilePath(sRoot2,sFolder2,sFile2,sFont2);
    Bfile_DeleteFile(sFont2);
    if(Bfile_CreateFile(sFont2,iSize)!=0)
    {
      PopupMessage(1,"Cannot create","destination file!",NULL,NULL,NULL);
      return(0);
    }
    iHandle2=Bfile_OpenFile(sFont2,_OPENMODE_WRITE);
  }
  else
  {
    Bfile_DeleteMainMemory(sFile2);
    if(Bfile_CreateMainMemory(sFile2)!=0)
    {
      PopupMessage(1,"Cannot create","destination file!",NULL,NULL,NULL);
      return(0);
    }
    MainDirectory(DELETE,sFile2,"");
    MainDirectory(CREATE,sFile2,sFolder2);
    iHandle2=Bfile_OpenMainMemory(sFile2);
  }
  if(iHandle2<0)
  {
    PopupMessage(1,"Cannot open","destination file!",NULL,NULL,NULL);
    return(0);
  }

  //Copy loop
  iPos=0;
  iErrFlag=0; 
  iSize0=iSize;
  if(iSize0>COPYBUFF) iSize0=COPYBUFF;
  do{
    iError=Bfile_ReadFile(iHandle1,sBuff,iSize0,iPos);
    if(iError<0){ iErrFlag=1; break; }
    iError=Bfile_WriteFile(iHandle2,sBuff,iSize0);    
    if(iError<0){ iErrFlag=1; break; }
    iPos=iPos+iSize0;
    if(iPos>=iSize) break;
    iSize0=iSize-iPos;
    if(iSize0>COPYBUFF) iSize0=COPYBUFF;
  }while(1);
  
  //Add additional spaces at end (main memory only)
  if(strcmp(sRoot2,"main")==0)
  {
    iSpaces=((iSize%4)!=0?4-(iSize%4):0);
    if(iSpaces>0)
    { 
      memset(sSpaces,' ',4);
      Bfile_WriteFile(iHandle2,sSpaces,iSpaces);
    }
  }
  
  //Close files
  Bfile_CloseFile(iHandle1);
  Bfile_CloseFile(iHandle2);
  
  //Error while copying files
  if(iErrFlag==1)
  {
    if(strcmp(sRoot2,"main")!=0)
      Bfile_DeleteFile(sFont2);
    else
      Bfile_DeleteMainMemory(sFile2);
    PopupMessage(1,"Error while","Copying file!",NULL,NULL,NULL);
    return(0);
  }
  
  //Return code
  return(1);
}

// ----------------------------------------------------------------
// Delete file
int DeleteFile(char *sRoot, char *sFolder, char *sFile)
{
  //Variables
  int iError;
  FONTCHARACTER sFont[MAXPATH];
  
  //Delete file from main memory
  if(strcmp(sRoot,"main")==0)
  {
    iError=Bfile_DeleteMainMemory(sFile);
    MainDirectory(DELETE,sFile,"");
  }
  else
  {
    FilePath(sRoot,sFolder,sFile,sFont);
    iError=Bfile_DeleteFile(sFont);
  }
  
  //Return code
  if(iError==0)
  {
    return(1);
  }
  else
  {
    PopupMessage(1,"Error while","deleting file!",NULL,NULL,NULL);
    return(0);
  }
}

// ----------------------------------------------------------------
// Convert new line in text buffer from LF to CR+LF
void ConvertNewLine2CRLF(char *sText)
{
  //Variables
  int i,j;  //Counters
  int iLen; //String length
  int iPtr; //String pointer
  
  //Conversion loop
  j=0;
  iLen=strlen(sText);
  do
  {
    if(sText[j]==NEWLINELF)
    {
      iPtr=j;
      for(i=iLen+1;i>iPtr;i--) sText[i]=sText[i-1];
      sText[iPtr]=NEWLINECR;
      iLen=strlen(sText);
      j++;
    }
    j++;
  }while(j<iLen);
}

// ----------------------------------------------------------------
// Convert new line in text buffer from CR+LF to LF
void ConvertNewLine2LF(char *sText)
{
  //Variables
  int i,j;  //Counters
  int iLen; //String length
  int iPtr; //String pointer
  
  //Conversion loop
  j=0;
  iLen=strlen(sText);
  do
  {
    if(sText[j]==NEWLINECR)
    {
      iPtr=j;
      for(i=iPtr;i<=iLen;i++) sText[i]=sText[i+1];
      iLen=strlen(sText);
    }
    j++;
  }while(j<iLen);
}

// ----------------------------------------------------------------
// Get user input with mesage
int PopupContinueYesNo(char *sLine1, char *sLine2, char *sLine3)
{
  //Variables
  int iAnswer;
  int iLines;
  
  //Hide keyboard status
  KeyboardStatusHideStore();
  KeyboardStatusHide(1);
  
  //Number of lines
  iLines=0;
  if(sLine1!=NULL) iLines++;
  if(sLine2!=NULL) iLines++;
  if(sLine3!=NULL) iLines++;
  if(iLines==0) return(-1);
  
  //Save display & menu bar
  SaveDisp(SAVEDISP_PAGE2);
  MenuStoreBar();

  //Write popup window
  PopUpWin(iLines);
  if(sLine1!=NULL){ locate(3,3); Print(sLine1); }
  if(sLine2!=NULL){ locate(3,4); Print(sLine2); }
  if(sLine3!=NULL){ locate(3,5); Print(sLine3); }
  MenuSetBar(MENUBARYESN);

  //Wait for key
  switch(GetKeyb())
  {
    case KEY_CTRL_F1:   iAnswer=1; break;
    case KEY_CTRL_F6:   iAnswer=0; break;
    case KEY_CTRL_EXIT: iAnswer=0; break;
    case KEY_CTRL_EXE:  iAnswer=1; break;
  }
  
  //Restore display & Menu bar
  RestoreDisp(SAVEDISP_PAGE2);
  MenuRestoreBar();
  
  //Unhide keyboard status
  KeyboardStatusHideRestore();
  
  //Return result
  return(iAnswer);  

}

// ----------------------------------------------------------------
// Get user input with mesage
void PopupMessage(int iWait,char *sLine1, char *sLine2, 
                  char *sLine3,char *sLine4,char *sLine5)
{
  //Variables
  int iLines;

  //Number of lines
  iLines=0;
  if(sLine1!=NULL) iLines++;
  if(sLine2!=NULL) iLines++;
  if(sLine3!=NULL) iLines++;
  if(sLine4!=NULL) iLines++;
  if(sLine5!=NULL) iLines++;
  if(iLines==0) return;
  
  //Save display & menu bar
  if(iWait==1) SaveDisp(SAVEDISP_PAGE2);
  if(iWait==1) MenuStoreBar();
  if(iWait==1) KeyboardStatusHideStore();
  if(iWait==1) KeyboardStatusHide(1);

  //Write popup window
  PopUpWin(iLines);
  switch(iLines)
  {
    case 1: 
      locate(3,4); Print(sLine1); 
      break;
    case 2:
      locate(3,3); Print(sLine1);
      locate(3,4); Print(sLine2);
      break;
    case 3:
      locate(3,3); Print(sLine1);
      locate(3,4); Print(sLine2);
      locate(3,5); Print(sLine3);
      break;
    case 4:
      locate(3,2); Print(sLine1);
      locate(3,3); Print(sLine2);
      locate(3,4); Print(sLine3);
      locate(3,5); Print(sLine4);      
      break;
    case 5:
      locate(3,2); Print(sLine1);
      locate(3,3); Print(sLine2);
      locate(3,4); Print(sLine3);
      locate(3,5); Print(sLine4);      
      locate(3,6); Print(sLine5);      
      break;
  }
  if(iWait==1) MenuSetBar(MENUBARMESS);

  //Wait for key
  if(iWait==1) GetKeyb();

  //Restore display & Menu bar
  if(iWait==1) RestoreDisp(SAVEDISP_PAGE2);
  if(iWait==1) MenuRestoreBar();
  if(iWait==1) KeyboardStatusHideRestore();
  
  //Show display it no wait
  if(iWait==0) Bdisp_PutDisp_DD();

}

// ----------------------------------------------------------------
// Get memory status
void PopupMemory(struct Config *sConfig)
{
  //Variables
  char sLine[50];
  int iLines;
  int iMain=0;
  int iStoM=0;
  int iSDCr=0;
  
  //Get memory status
  if(Bfile_GetMediaFree(DEVICE_MAIN_MEMORY,&iMain)!=0) iMain=0;
  if(Bfile_GetMediaFree(DEVICE_STORAGE    ,&iStoM)!=0) iStoM=0;
  if(sConfig->iTrySD==1) if(Bfile_GetMediaFree(DEVICE_SD_CARD,&iSDCr)!=0) iSDCr=0;
  
  //Hide keyboard status
  KeyboardStatusHideStore();
  KeyboardStatusHide(1);
  
  //Save display & menu bar
  SaveDisp(SAVEDISP_PAGE2);
  MenuStoreBar();

  //Write popup window
  if(sConfig->iTrySD==1)
  {
    PopUpWin(5);
    locate(3,2); Print("   Free memory   ");
    locate(3,4); sprintf(sLine,"Main   :%i",iMain); Print(sLine);
    locate(3,5); sprintf(sLine,"Storage:%i",iStoM); Print(sLine);
    locate(3,6); sprintf(sLine,"SD Card:%i",iSDCr); Print(sLine);
  }
  else
  {
    PopUpWin(4);
    locate(3,2); Print("   Free memory   ");
    locate(3,4); sprintf(sLine,"Main   :%i",iMain); Print(sLine);
    locate(3,5); sprintf(sLine,"Storage:%i",iStoM); Print(sLine);
  }
  MenuSetBar(MENUBARMESS);

  //Wait for key
  GetKeyb();

  //Restore display & Menu bar
  RestoreDisp(SAVEDISP_PAGE2);
  MenuRestoreBar();
  
  //Unhide keyboard status
  KeyboardStatusHideRestore();
  
}

// ----------------------------------------------------------------
// Get file name dialog box
int GetFileName(char *sFile,int iMaxLen, char dontPutNameOfFile)
{
  //Variables
  int iAnswer;
  char sName[MAXFNAME] = {0};
  
  //Keyboard status show
  KeyboardStatusHideStore();
  KeyboardStatusHide(0);
  
  //Save display & menu bar
  SaveDisp(SAVEDISP_PAGE1);
  MenuStoreBar();

  //Write popup window
  PopUpWin(2);
  locate(3,3); Print("Enter file name:");
  locate(3,4); Print("[            ]");
  MenuSetBar(MENUBARSTRN);

  //Get string
  if (dontPutNameOfFile) {
	strcpy(sName,"");
  } else {
	
	strcpy(sName,sFile);
  }
  iAnswer=GetString(3,3,iMaxLen,sName,KEY_CTRL_F1,KEY_CTRL_F6,KEY_CTRL_F3,KEY_CTRL_F4,113,13);

  //Restore display & Menu bar
  RestoreDisp(SAVEDISP_PAGE1);
  MenuRestoreBar();
  
  //Check empty file name
  if(strlen(sName)==0 && iAnswer==1)
  {
    PopupMessage(1,"Invalid filename!",NULL,NULL,NULL,NULL);
    iAnswer=0;
  }
  
  //Keyboard status restore
  KeyboardStatusHideRestore();
  
  //Return result
  if(iAnswer == 1) {
	  int len = strlen(sName);
	  
	  //Check if name ends with ".py"; if not, add it
	  //(ty stackoverflow)
	  if(!(strlen(sName) >= 3 && !strcmp(sName + strlen(sName) - 3, ".py"))) {
		sName[len+0] = '.';
		sName[len+1] = 'p';
		sName[len+2] = 'y';
		sName[len+3] = '\0';
	  }

	  strcpy(sFile,sName);
  }
  return(iAnswer);  

}

// ----------------------------------------------------------------
// Get folder name dialog box
int GetFolderName(char *sFolder)
{
  //Variables
  int iAnswer;
  char sName[MAXFNAME];
  
  //Keyboard status show
  KeyboardStatusHideStore();
  KeyboardStatusHide(0);
  
  //Save display & menu bar
  SaveDisp(SAVEDISP_PAGE1);
  MenuStoreBar();

  //Write popup window
  PopUpWin(2);
  locate(3,3); Print("Folder name:  ");
  locate(3,4); Print("[            ]");
  MenuSetBar(MENUBARSTRN);

  //Get string
  strcpy(sName,sFolder);
  iAnswer=GetString(3,3,8,sName,KEY_CTRL_F1,KEY_CTRL_F6,KEY_CTRL_F3,KEY_CTRL_F4,113,13);

  //Restore display & Menu bar
  RestoreDisp(SAVEDISP_PAGE1);
  MenuRestoreBar();
  
  //Check empty file name
  if(strlen(sName)==0 && iAnswer==1)
  {
    PopupMessage(1,"Invalid folder!",NULL,NULL,NULL,NULL);
    iAnswer=0;
  }
  
  //Keyboard status restore
  KeyboardStatusHideRestore();
  
  //Return result
  if(iAnswer==1) strcpy(sFolder,sName);
  return(iAnswer);  

}

// ----------------------------------------------------------------
// Get string to search
int GetSearchString(char *sString)
{
  //Variables
  int iAnswer;
  char sString0[16];
  
  //Keyboard status show
  KeyboardStatusHideStore();
  KeyboardStatusHide(0);
  
  //Save display & menu bar
  SaveDisp(SAVEDISP_PAGE1);
  MenuStoreBar();

  //Write popup window
  PopUpWin(2);
  locate(3,3); Print("Search string:   ");
  locate(3,4); Print("[               ]");
  MenuSetBar(MENUBARSTRN);

  //Get string
  strcpy(sString0,sString);
  iAnswer=GetString(3,3,15,sString0,KEY_CTRL_F1,KEY_CTRL_F6,KEY_CTRL_F3,KEY_CTRL_F4,113,13);

  //Restore display & Menu bar
  RestoreDisp(SAVEDISP_PAGE1);
  MenuRestoreBar();
  
  //Check empty file name
  if(strlen(sString0)==0 && iAnswer==1)
  {
    PopupMessage(1,"Empty string!",NULL,NULL,NULL,NULL);
    iAnswer=0;
  }
  
  //Keyboard status restore
  KeyboardStatusHideRestore();
  
  //Return result
  if(iAnswer==1) strcpy(sString,sString0);
  return(iAnswer);  

}

/*
// ----------------------------------------------------------------
// Help text
void HelpText(void)
{
  
  //Help text
  char sHelp[][33]=
  {"Text editor for fx-9860G series ",  
   "---------FILE EXPLORER----------",
   "Main menu commands:             ",
   "-OPEN: Open selected file/folder",
   "-NEW:  Create new file.         ",
   "-FILE: Go to File menu.         ",
   "-OPTN: Go to options menu.      ",
   "-ROOT: Changes root directory.  ",
   "-DEL:  Delete selected file.    ",
   "File menu commands:             ",
   "-REN:  Rename file.             ",
   "-COPY: Copy file.               ",
   "-MOVE: Move file.               ",
   "-NEWF: Create new folder.       ",
   "-DELF: Delete selected folder.  ",
   "                                ",
   "                                ",
   "                                ",
   "Options menu commands:          ",
   "-OPTN: Enter set up screen. Set ",
   "       up screen is also called ",
   "       with Shift+SETUP.        ",
   "-MEM : Display memory status.   ",
   "-HELP: This help screen.        ",
   "-ABOU: Information about program",
   "                                ",
   "                                ",
   "Root menu commands:             ",
   "-MAIN: Change to main memory as ",
   "       root directory.          ",
   "-SMEM: Change to storage memory ",
   "       as root directory.       ",
   "-SDC:  Change to SD Card as root",
   "       directory.               ",
   "                                ",
   "                                ",
   "----------TEXT EDITOR-----------",
   "Main menu commands:             ",
   "-FILE: Go to file menu.         ",
   "-EDIT: Go to edit menu.         ",
   "-GOTO: Go to goto menu.         ",
   "-OPTN: Go to options menu.      ",
   "-CHAR: ASCII character set.     ",
   "-A<>a: Change upper/lower case. ",
   "                                ",
   "File menu commands:             ",
   "-SAVE :Save file to current     ",
   "       location memory.         ",
   "-S.AS: Save file with different ",
   "       file/folder names.       ",
   "-AUTO: Set current file to be   ",
   "       opened automatically when",
   "       program starts           ",
   "                                ",
   "Edit menu commands:             ",
   "-CLIP: Text selection on / off. ",
   "       Same as SHIFT+CLIP.      ",
   "-COPY: Copy text to clipboard.  ",
   "-CUT:  Copy text to clipboard   ",
   "       and delete.              ",
   "-PAST: Paste text from clipboard",
   "       Same as SHIFT+PASTE.     ",
   "-DEL:  Delete selected text.    ",
   "-SRC:  Search string within text",
   "-SRC+: Search again.            ",
   "                                ",
   "Goto menu commands:             ",
   "-TOP:  Move cursor to beginning.",
   "-BOTM: Move cursor to ending.   ",
   "-HOME: Go to begining of line.  ",
   "-END:  Go to ending of line.    ",
   "-PAG-: Page up.                 ",
   "-PAG+: Page down.               ",
   "                                ",
   "Options menu commands:          ",
   "-OPTN: Enter set up screen.     ",
   "       Same as SHIFT+SETUP.     ",
   "-MEM:  Display memory status.   ",
   "-HELP: This help screen.        ",
   "-ABOU: Information about program",
   "                                ",
   "ASCII character set commands:   ",
   "-INSR: Inserts char. into text. ",
   "-BIND: Binds character to key.  ",
   "-UBND: Unbinds character.       ",
   "                                ",
   "Bound characters are used in the",
   "editor window by pressing VARS  ",
   "key and then the key defined for",
   "the bound character.            ",
   "Information in the top bar:     ",
   "-MM/SM/SD: Root directory.      ",
   "-File name + [Folder] or Cursor.",
   "-S/-: File saved flag           ",
   "-T/B: Text file / Binary file   ",
   "-1/S/a/A/b/B:Keyboard mode->    ",
   " Numeric,Shift,Alpha lower,     ",
   " Alpha upper,Alpha locked lower,",
   " Alpha locked upper.            ",
   "-------------SET UP-------------",
   "<Try SDC>                       ",
   "-YES: card is checked everytime ",
   " the file explorer is called.   ",
   "-NO: card is not tried never.   ",
   " Use this option if your calc   ",
   " does not have SD card because  ",
   " file explorer opens faster.    ",
   "                                ",
   "<System Files>:                 ",
   "-HIDN: System files are hidden  ",
   " in the file explorer. System   ",
   " files are *.g1? and those in   ",
   " which attribute is not DT_FILE ",
   " or DT_DIRECTORY. Files EDIT.CFG",
   " and EDIT.DIR are system files. ",
   "-DISP: System files are         ",
   " displayed in the file explorer.",
   "<New Line>                      ",
   "-WIN: Files are stored using    ",
   " CR+LF as line terminator as in ",
   " windows systems.               ", 
   "-UNIX: Files are stored using LF",
   " as line terminator as in unix  ",
   " systems.                       ", 
   "                                ",
   "                                ",
   "<Word Wrap>                     ",
   "-ON: Line breaks happen in      ",
   " between of words, no cuts in   ",
   " in the middle of words.        ",
   "-OFF: Line breaks happen        ",
   " anywhere, words are cut in     ",
   " between.                       ",
   "                                ",
   "                                ",
   "<Bytes free>                    ",
   "-YES: Remaining memory is       ",
   " displayed in last row of file  ",
   " explorer.                      ",
   "-NO: Remaining memory is not    ",
   " displayed.                     ",
   "                                ",
   "                                ",
   "                                ",
   "<Default root directory>        ",
   "-MAIN: Set main memory as root  ",
   " when file explorer opens.      ",
   "-SMEM: Set storage memory as    ",
   " root when file explorer opens. ",
   "-SDC: Set SD Card as root when  ",
   " file explorer opens.            ",
   "                                ",
   "                                ",
   "<Font size>                     ",
   "-TINY: Set font size to 3x5     ",
   " 32 columns x 8 rows            ",
   "-SMAL: Set font size to 3x6     ",
   " 32 columns x 7 rows            ",
   "-MEDM: Set font size to 3x6     ",
   " 25 columns x 7 rows            ",
   "-LARG: Set font size to 5x7     ",
   " 21 columns x 6 rows            ",
   "<Info Bar>                      ",
   "-FOLD: Folder name is displayed ",
   " in the top bar.                ",
   "-CURS: Current line and total   ",
   " lines are displayed in the top ",
   " bar.                           ", 
   "                                ",
   "                                ",
   "                                ",
   "<Text buffer size>              ",
   "This option sets the size of the",
   "buffer used to load the files.  ",
   "It is maximun file size that can",
   "be loaded in the text editor.   ",
   "<Clipboard buffer size>         ",
   "Size of the clipboard buffer. It",
   "is the maximun data that you can",
   "and copy and paste.             ",
   "<Files/Dir.>                    ",
   "This is the maximun number of   ",
   "files per folder that can be    ",
   "displayed in the file explorer  ",
   "<Foldr.Max.>                    ",
   "This is the maximun number of   ",
   "folders that can be displayed in",
   "the folder selection window.    ",
   "                                ",
   "<Auto open>                     ",
   "-YES: Enable automatic file open",
   " when application starts.       ",
   "-NO: Disable automatic file open",
   "<Auto root/Auto name/Auto foldr>",
   "-SET: Set path for file to be   ",
   " opened automatically.          ",
   "-CLR: Clear file path.          ",
   "                                ",
   "                                ",
   "  This program was developed    ",
   "  from August 2008 to April     ",
   "  2009 by Diego Marin. Report   ", 
   "  any bugs or comments to:      ",
   "                                ",
   "       dmarin75@yahoo.es        ",
   "%HELPEND%"
   };
  
  //Variables
  int i;
  int iHPag=0;
  int iHPagMax;
  int iStart;
  int iExit;
  int iRefresh=1;
  int iCode;
  int iHelpLines;
  unsigned int iKey;
  
  //Hide keyboard status
  KeyboardStatusHide(1);
  MenuStoreBar();
  
  //Calculate help lines
  for(i=0;strcmp(sHelp[i],"%HELPEND%")!=0;i++);
  iHelpLines=i;
  
  //Init screen
  Bdisp_AllClr_DDVRAM();
  MenuSetBar(MENUBARHNAV);
  iHPagMax=iHelpLines/(GetScrCAy()-1);
  
  //Main loop
  iExit=0;
  do{
      
    //Rewrite screen
    if(iRefresh==1)
    {
      SetFont(FONTS);
      SetColor(COLNOR);
      iStart=iHPag*(GetScrCAy()-1);
      for(i=0;i<(GetScrCAy()-1);i++)
      {
        if(i+iStart<iHelpLines) 
          PrintStr(0,i,sHelp[i+iStart]);
        else
          PrintStr(0,i,"                                ");
      }
    }
    
    //Flush screen
    if(iRefresh!=0)
    {
      Bdisp_PutDisp_DD();
      iRefresh=0;
    }
    
    //Check keystroke
    if(KbHit()){
        
      //Get Key
      iKey=GetKeyb();
        
      //Process keys
      switch(iKey)
      {
        //Process menu commands
        case KEY_CTRL_F1:
        case KEY_CTRL_F2:
        case KEY_CTRL_F3:
        case KEY_CTRL_F4:
        case KEY_CTRL_F5:
        case KEY_CTRL_F6:
          iCode=MenuFunctionKey(iKey);
          if(iCode!=NODENOFUNCT)
          {
            switch(iCode)
            {
            
              //Page+
              case NODEHELPPAGD:
                if(iHPag<iHPagMax)
                {
                  iHPag++;
                  iRefresh=1;
                }
                break;
              
              //Page-
              case NODEHELPPAGU:
                if(iHPag>0)
                {
                  iHPag--;
                  iRefresh=1;
                }
                break;
              
              //Exit
              case NODEHELPEXIT:
                iExit=1;
                break;
              
            }
            break;
          }
          break;
         
          //Exit
          case KEY_CTRL_EXIT:
            iExit=1;
            break;
      }
   
    }
  
  }while(iExit==0);

  //Unhide keyboard status
  KeyboardStatusHide(0);
  MenuRestoreBar();
  
}*/

// ----------------------------------------------------------------
// Character selection 
char CharacterSelect(int iBindMode,struct Config *sConfig)
{
  //Macros
  #define MINCHAR 32
  #define MAXCHAR 126
  #define CHARACTER(x,y) (MINCHAR+(y -1)*19+x)
  
  //Variables
  int i,j,k;
  int iExit;
  int iMapIndex;
  int iBindKey;
  int iFound;
  int iOffsetX;
  int iOffsetY;
  int iRefresh=1;
  int iCode;
  int iChr;
  static int iCx=0,iCy=1;
  static int iACx=0,iACy=1;
  unsigned int iKey;
  
  //Init screen
  KeyboardStatusHideStore();
  KeyboardStatusHide(1);
  MenuStoreBar();
  
  //Main loop
  iExit=0;
  do{
      
    //Rewrite screen
    if(iRefresh==1)
    {
      
      //Clear display
      Bdisp_AllClr_DDVRAM();
  
      //Set menu bar
      if(iBindMode==1){
        MenuEnableNode(MENUBARCHAR,4);
        MenuEnableNode(MENUBARCHAR,5);
      }
      else{
       MenuDisableNode(MENUBARCHAR,4);
       MenuDisableNode(MENUBARCHAR,5);
      }
      MenuSetBar(MENUBARCHAR); 
  
      //Print char map
      SetFont(FONTL);
      PrintStr(0,0,STR_CHARSEL);
      for(i=0;i<19;i++){
      for(j=1;j< 6;j++){
        iOffsetX=-1;
        iOffsetY=0;
        SetFont(FONTL);
        SetColor(COLNOR);
        iChr=CHARACTER(i,j);
        if(iBindMode==1){
          for(k=0;k<MAXCHARMAP;k++){
            if((int)(sConfig->sCharMap[k].cAscii)==iChr){
              iOffsetX=1;
              iOffsetY=1;
              SetFont(FONTS);
              SetColor(COLREV);
              Rectangle(7+(i+0)*6+0,4+(j+0)*8+0,
                        7+(i+1)*6-2,4+(j+1)*8-2,1);
              break;
            } 
          }
        }  
        if(iChr<=MAXCHAR)
          PrintCharXY(7+i*6+iOffsetX,4+j*8+iOffsetY,iChr);
        else
          PrintCharXY(7+i*6+iOffsetX,4+j*8+iOffsetY,' ');
      }}
      SetColor(COLNOR);
    }
    
    //Cursor position
    if(iCx!=iACx || iCy!=iACy || iRefresh!=0)
    {
     
     //Clear previous cursor position
     Rectangle(7+(iACx+0)*6-1,4+(iACy+0)*8-1,
               7+(iACx+1)*6-1,4+(iACy+1)*8-1,0);
     
     //Set current cursor position
     Rectangle(7+(iCx+0)*6-1,4+(iCy+0)*8-1,
               7+(iCx+1)*6-1,4+(iCy+1)*8-1,1);
     
     //Screen refresh
     iRefresh=1;
    
    }    
    
    //Flush screen
    if(iRefresh!=0)
    {
      Bdisp_PutDisp_DD();
      iRefresh=0;
    }
    
    //Previous cursor position
    iACx=iCx;
    iACy=iCy;
    
    //Get Key
    iKey=GetKeyb();
      
    //Get menu commands
    if(iKey==KEY_CTRL_F1 || iKey==KEY_CTRL_F2
    || iKey==KEY_CTRL_F3 || iKey==KEY_CTRL_F4
    || iKey==KEY_CTRL_F5 || iKey==KEY_CTRL_F6)
      iKey=-MenuFunctionKey(iKey);
    
    //Process keys
    switch(iKey)
    {
      //Character selection
      case -NODECHARINSR:
        iChr=CHARACTER(iCx,iCy);
        iExit=1;
        break;
       
      //Bind character into char map
      case -NODECHARBIND:
        
        //Get character to bind
        iChr=CHARACTER(iCx,iCy);
        
        //Check that character has not been bound before
        iFound=0;
        for(k=0;k<MAXCHARMAP;k++){
          if((int)(sConfig->sCharMap[k].cAscii)==iChr){
            iFound=1;
            break;
          }
        }
        if(iFound==1){
          PopupMessage(1,"Character is","already bound.",NULL,NULL,NULL);
          break;
        }
        
        //Find a free space in the char map
        iMapIndex=-1;
        for(k=0;k<MAXCHARMAP;k++){
          if(sConfig->sCharMap[k].iKey==-1){
            iMapIndex=k;
            break;
          }
        }
        if(iMapIndex==-1){
          PopupMessage(1,"Cannot bind more","characters.",NULL,NULL,NULL);
          break;
        }  

        //Get binding key
        PopupMessage(0,"Press bind key or","[EXIT] to cancel.",NULL,NULL,NULL);
        iBindKey=KeyNormalCase(GetKeyb());
        switch(iBindKey){
          
          //Exit key terminates binding
          case KEY_CTRL_EXIT:
          case KEY_CTRL_QUIT:
            break;
          
          //These keys are not allowed to be used
          case 0:
          case KEY_CTRL_F1:
          case KEY_CTRL_F2:
          case KEY_CTRL_F3:
          case KEY_CTRL_F4:
          case KEY_CTRL_F5:
          case KEY_CTRL_F6:
          case KEY_CTRL_SHIFT:
          case KEY_CTRL_ALPHA:
          case KEY_CTRL_VARS:
          case KEY_CTRL_PRGM:
          case KEY_CTRL_MENU:
          case KEY_CTRL_SETUP:
          case KEY_CTRL_AC:
            PopupMessage(1,"Cannot bind to","that key.",NULL,NULL,NULL);
            break;
          
          //Make binding
          default:
            
            //Check if key has been used already           
            iFound=0;
            for(k=0;k<MAXCHARMAP;k++){
              if(sConfig->sCharMap[k].iKey==iBindKey){
                iFound=1;
                break;
              }
            }
            if(iFound==1){
              PopupMessage(1,"This key is","already used for","another character",NULL,NULL);
              break;
            }
            
            //Modify configuration
            sConfig->sCharMap[iMapIndex].cAscii=(char)iChr;
            sConfig->sCharMap[iMapIndex].iKey=iBindKey;
            ConfigExport(sConfig);
            
            //Message
            PopupMessage(1,"Character bind","completed.",NULL,NULL,NULL);
            break;
        }
        iRefresh=1;
        break;
       
      //Unbind character
      case -NODECHARUBND:
        
        //Get character to unbind
        iChr=CHARACTER(iCx,iCy);
        
        //Clear the char from the char map
        iFound=0;
        for(k=0;k<MAXCHARMAP;k++){
          if(sConfig->sCharMap[k].cAscii==(char)iChr){
            iFound=1;
            sConfig->sCharMap[k].cAscii=0;
            sConfig->sCharMap[k].iKey=-1;
          }
        }
        if(iFound==1){
          PopupMessage(1,"Character unbind","completed.",NULL,NULL,NULL);
          ConfigExport(sConfig);
          iRefresh=1;
        }
        else{
          PopupMessage(1,"Character not","bound before.",NULL,NULL,NULL);
        }
        break;
        
      //Exit
      case KEY_CTRL_EXIT:
        iChr=0;
        iExit=1;
        break;
        
      //Enter
      case KEY_CTRL_EXE:
        iChr=CHARACTER(iCx,iCy);
        iExit=1;
        break;
        
      //Cursor x++
      case KEY_CTRL_RIGHT:
        iCx++;
        iChr=CHARACTER(iCx,iCy);
        if(iChr>MAXCHAR || iCx>18) iCx--;
        break;
          
      //Cursor x--
      case KEY_CTRL_LEFT:
        iCx--;
        iChr=CHARACTER(iCx,iCy);
        if(iChr<MINCHAR || iCx<0) iCx++;
        break;
          
      //Cursor y++
      case KEY_CTRL_DOWN:
        iCy++;
        iChr=CHARACTER(iCx,iCy);
        if(iChr>MAXCHAR || iCy>5) iCy--;
        break;
          
      //Cursor y--
      case KEY_CTRL_UP:    
        iCy--;
        iChr=CHARACTER(iCx,iCy);
        if(iChr<MINCHAR || iCy<1) iCy++;
        break;
    }
  
  }while(iExit==0);

  //Restore keyboard status
  KeyboardStatusHideRestore();
  MenuRestoreBar();
  
  //Return character
  return(iChr);
  
}

//Draw rectangle
void Rectangle(int iX1,int iY1, int iX2, int iY2,int iColor)
{
  //Draw
  if(iColor==0){
    Bdisp_ClearLineVRAM(iX1,iY1,iX1,iY2);
    Bdisp_ClearLineVRAM(iX1,iY2,iX2,iY2);
    Bdisp_ClearLineVRAM(iX2,iY2,iX2,iY1);
    Bdisp_ClearLineVRAM(iX2,iY1,iX1,iY1);
  }                       

  //Clear
  else if(iColor==1){
    Bdisp_DrawLineVRAM(iX1,iY1,iX1,iY2);
    Bdisp_DrawLineVRAM(iX1,iY2,iX2,iY2);
    Bdisp_DrawLineVRAM(iX2,iY2,iX2,iY1);
    Bdisp_DrawLineVRAM(iX2,iY1,iX1,iY1);
  }                       

}
/*
// ----------------------------------------------------------------
// Standard part of code (inserted automatically by SDK)
#pragma section _BR_Size
unsigned long BR_Size;
#pragma section
#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}
#pragma section
*/