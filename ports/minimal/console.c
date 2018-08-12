//Console functions --------------------------------------------------------------------

//Include files
#include <string.h>
#include "fxlib.h"
#include "stdio.h"
#include "font.h"
#include "menu.h"
#include "console.h"

// ------------------------------------------------------------------------------------- 
// Global variables
int _iAlpha=ALPHALOCK;
int _iShift=SHIFTOFF;
int _iACase=ALPHALOWER;
int _iKbStatPx=KBSTATPX;
int _iKbStatPy=KBSTATPY;
char _cAlphaKill=0;
char _cShiftKill=0;
char _cHIndex=0;
char _cKeyStatusHide=0;
char _cStatusHideStack[MAXSTATUSHIDE];

// Keyboard codes table
struct sKeyCode _sKeyCode[KEYCODES]=
{{KEY_CHAR_0      ,KEY_CHAR_IMGNRY    ,KEY_CHAR_Z      },
 {KEY_CHAR_1      ,KEY_CHAR_LIST      ,KEY_CHAR_U      },
 {KEY_CHAR_2      ,KEY_CHAR_MAT       ,KEY_CHAR_V      },
 {KEY_CHAR_3      ,0                  ,KEY_CHAR_W      },
 {KEY_CHAR_4      ,KEY_CTRL_CATALOG   ,KEY_CHAR_P      },
 {KEY_CHAR_5      ,0                  ,KEY_CHAR_Q      },
 {KEY_CHAR_6      ,0                  ,KEY_CHAR_R      },
 {KEY_CHAR_7      ,KEY_CTRL_CAPTURE   ,KEY_CHAR_M      },
 {KEY_CHAR_8      ,KEY_CTRL_CLIP      ,KEY_CHAR_N      },
 {KEY_CHAR_9      ,KEY_CTRL_PASTE     ,KEY_CHAR_O      },
 {KEY_CHAR_DP     ,KEY_CHAR_EQUAL     ,KEY_CHAR_SPACE  },
 {KEY_CHAR_EXP    ,KEY_CHAR_PI        ,KEY_CHAR_DQUATE },
 {KEY_CHAR_PMINUS ,KEY_CHAR_ANS       ,0               },
 {KEY_CHAR_PLUS   ,KEY_CHAR_LBRCKT    ,KEY_CHAR_X      },
 {KEY_CHAR_MINUS  ,KEY_CHAR_RBRCKT    ,KEY_CHAR_Y      },
 {KEY_CHAR_MULT   ,KEY_CHAR_LBRACE    ,KEY_CHAR_S      },
 {KEY_CHAR_DIV    ,KEY_CHAR_RBRACE    ,KEY_CHAR_T      },
 {KEY_CTRL_EXE    ,KEY_CHAR_CR        ,KEY_CTRL_EXE    },
 {KEY_CTRL_DEL    ,KEY_CTRL_INS       ,KEY_CTRL_DEL    },
 {KEY_CTRL_AC     ,KEY_CTRL_AC        ,KEY_CTRL_AC     },
 {KEY_CHAR_FRAC   ,KEY_CTRL_MIXEDFRAC ,KEY_CHAR_G      },
 {KEY_CTRL_FD     ,KEY_CTRL_FRACCNVRT ,KEY_CHAR_H      },
 {KEY_CHAR_LPAR   ,KEY_CHAR_CUBEROOT  ,KEY_CHAR_I      },
 {KEY_CHAR_RPAR   ,KEY_CHAR_RECIP     ,KEY_CHAR_J      },
 {KEY_CHAR_COMMA  ,0                  ,KEY_CHAR_K      },
 {KEY_CHAR_STORE  ,0                  ,KEY_CHAR_L      },
 {KEY_CTRL_XTT    ,KEY_CHAR_ANGLE     ,KEY_CHAR_A      },
 {KEY_CHAR_LOG    ,KEY_CHAR_EXPN10    ,KEY_CHAR_B      },
 {KEY_CHAR_LN     ,KEY_CHAR_EXPN      ,KEY_CHAR_C      },
 {KEY_CHAR_SIN    ,KEY_CHAR_ASIN      ,KEY_CHAR_D      },
 {KEY_CHAR_COS    ,KEY_CHAR_ACOS      ,KEY_CHAR_E      },
 {KEY_CHAR_TAN    ,KEY_CHAR_ATAN      ,KEY_CHAR_F      },
 {KEY_CHAR_SQUARE ,KEY_CHAR_ROOT      ,KEY_CHAR_VALR   },
 {KEY_CHAR_POW    ,KEY_CHAR_POWROOT   ,KEY_CHAR_THETA  },
 {KEY_CTRL_EXIT   ,KEY_CTRL_QUIT      ,KEY_CTRL_EXIT   },
 {KEY_CTRL_SHIFT  ,KEY_CTRL_SHIFT     ,KEY_CTRL_SHIFT  },
 {KEY_CTRL_ALPHA  ,KEY_CTRL_ALPHA     ,KEY_CTRL_ALPHA  },
 {KEY_CTRL_OPTN   ,0                  ,0               },
 {KEY_CTRL_VARS   ,KEY_CTRL_PRGM      ,KEY_CTRL_VARS   },
 {KEY_CTRL_MENU   ,KEY_CTRL_SETUP     ,0               },
 {KEY_CTRL_UP     ,KEY_CTRL_PAGEUP    ,KEY_CTRL_UP     },
 {KEY_CTRL_DOWN   ,KEY_CTRL_PAGEDOWN  ,KEY_CTRL_DOWN   },
 {KEY_CTRL_LEFT   ,0                  ,KEY_CTRL_LEFT   },
 {KEY_CTRL_RIGHT  ,0                  ,KEY_CTRL_RIGHT  },
 {KEY_CTRL_F1     ,KEY_CTRL_F1        ,KEY_CTRL_F1     },
 {KEY_CTRL_F2     ,KEY_CTRL_F2        ,KEY_CTRL_F2     },
 {KEY_CTRL_F3     ,KEY_CTRL_F3        ,KEY_CTRL_F3     },
 {KEY_CTRL_F4     ,KEY_CTRL_F4        ,KEY_CTRL_F4     },
 {KEY_CTRL_F5     ,KEY_CTRL_F5        ,KEY_CTRL_F5     },
 {KEY_CTRL_F6     ,KEY_CTRL_F6        ,KEY_CTRL_F6     }};

// ------------------------------------------------------------------------------------- 
// Hide / Unhide keyboard status
void KeyboardStatusHide(char cHide)
{
  _cKeyStatusHide=cHide;
}

// ------------------------------------------------------------------------------------- 
// Keyboard status hide store
void KeyboardStatusHideStore()
{
  if(_cHIndex<MAXSTATUSHIDE-1)
  {
    _cHIndex++;
    _cStatusHideStack[_cHIndex]=_cKeyStatusHide;
  }
}

// ------------------------------------------------------------------------------------- 
// Keyboard status hide restore
void KeyboardStatusHideRestore()
{
  if(_cHIndex>=0)
  {
    _cKeyStatusHide=_cStatusHideStack[_cHIndex];
    _cHIndex--;
  }
}

// ------------------------------------------------------------------------------------- 
// Check keyboard hit
int KbHit(void)
{  
  //Variables
  
  int ret;
  unsigned int key;

  ret=GetKeyWait(KEYWAIT_HALTOFF_TIMEROFF,1,0,&key);
  if(ret==KEYREP_KEYEVENT){
    return(1);
  }
  else{
    return(0);
  }

}

// ------------------------------------------------------------------------------------- 
// Translate keycode depending on SHIFT and APLHA status
int KeyMap(int iKey, int iShift, int iAlpha)
{
  //Variables
  int i;
  
  //Key loop
  for(i=0;i<KEYCODES;i++)
  {
    if(_sKeyCode[i].iNormal==iKey
    || _sKeyCode[i].iShift ==iKey
    || _sKeyCode[i].iAlpha ==iKey)
    {
      if(iShift==SHIFTON) 
        return(_sKeyCode[i].iShift);
      else if(iAlpha!=ALPHAOFF) 
        return(_sKeyCode[i].iAlpha);
      else 
        return(_sKeyCode[i].iNormal);
    }
  }
  
  //Not found
  return(iKey);

}

// ------------------------------------------------------------------------------------- 
// Translate keycode into normal case 
int KeyNormalCase(int iKey)
{
  //Variables
  int i;
  
  //Key loop
  for(i=0;i<KEYCODES;i++)
  {
    if(_sKeyCode[i].iNormal==iKey
    || _sKeyCode[i].iShift ==iKey
    || _sKeyCode[i].iAlpha ==iKey)
    {
      return(_sKeyCode[i].iNormal);
    }
  }
  
  //Not found
  return(iKey);

}

// ----------------------------------------------------------------
// Get keyboard key
unsigned int GetKeyb(void)
{
  //Variables
  unsigned int iKey; //Keyboard code
    
  //Set shift & alpha kill
  if(_cShiftKill==1 && _iShift==SHIFTON)
  {
    _iShift=SHIFTOFF;
    _cShiftKill=0;
    PrintKeyboardStatus();
    Bdisp_PutDisp_DD();
  }
  if(_cAlphaKill==1 && _iAlpha==ALPHAON)
  {
    _iAlpha=ALPHAOFF;
    _cAlphaKill=0;
    PrintKeyboardStatus();
    Bdisp_PutDisp_DD();
  }
        
  //Get keystroke
  GetKey(&iKey);
  iKey=KeyMap(iKey,_iShift,_iAlpha);
        
  //Set shift & alpha kill
  if(_iShift==SHIFTON) _cShiftKill=1;
  if(_iAlpha==ALPHAON) _cAlphaKill=1;
        
  //Process keys
  switch(iKey)
  {
            
    //Shift key
    case KEY_CTRL_SHIFT:
      _iShift=(_iShift==SHIFTON?SHIFTOFF:SHIFTON);
      _iAlpha=ALPHAOFF;
      _cShiftKill=0;
      _cAlphaKill=0;
      PrintKeyboardStatus();
      Bdisp_PutDisp_DD();
      break;
            
    //Alpha key
    case KEY_CTRL_ALPHA:
      if(_iShift==SHIFTON)
      {
        _iAlpha=ALPHALOCK;
      }
      else
      {
        switch(_iAlpha)
        {
          case ALPHAOFF:  _iAlpha=ALPHAON;  break;
          case ALPHAON:   _iAlpha=ALPHAOFF; break;
          case ALPHALOCK: _iAlpha=ALPHAOFF; break;
        }
      }
      _iShift=SHIFTOFF;
      _cAlphaKill=0;
      _cShiftKill=0;
      PrintKeyboardStatus();
      Bdisp_PutDisp_DD();
      break;
  }
  
  //Return key
  return(iKey);

}            

// ----------------------------------------------------------------
// Change case in keyboard status
void KeyboardStatusChangeCase(void)
{
  if(_iAlpha!=ALPHAOFF)
  {
    _iACase=(_iACase==ALPHAUPPER?ALPHALOWER:ALPHAUPPER);
    _cAlphaKill=0;
    PrintKeyboardStatus();
    Bdisp_PutDisp_DD();
  }
}

// ----------------------------------------------------------------
// Keyboard status
char Key2Char(unsigned int iKey)
{
  //Variables
  char cChr=0;
  
  //Translation
  if(iKey>=32 && iKey <=126)
  {
    if(isalpha(iKey) && _iACase==ALPHALOWER) 
      cChr=tolower(iKey);
    else
      cChr=iKey;
  }
  else if(iKey==KEY_CHAR_PLUS)   cChr='+';
  else if(iKey==KEY_CHAR_MINUS)  cChr='-';
  else if(iKey==KEY_CHAR_MULT)   cChr='*';
  else if(iKey==KEY_CHAR_DIV)    cChr='/';
  else if(iKey==KEY_CHAR_PMINUS) cChr='_';
  else if(iKey==KEY_CHAR_POW)    cChr='^';
  else if(iKey==KEY_CTRL_EXE)    cChr=10;
  else if(iKey==KEY_CHAR_CR)     cChr=10;
  
  //Return character
  return(cChr);
}

// ----------------------------------------------------------------
// Keyboard status location
void KeyboardStatusLocation(int iPx, int iPy)
{
  _iKbStatPx=iPx;
  _iKbStatPy=iPy;
}

// ----------------------------------------------------------------
// Keyboard status
void PrintKeyboardStatus()
{
  
  //Variables
  char cChr;
  char sStr[2];
  
  //Exit if hide keyboard status is on
  if(_cKeyStatusHide==1) return;
  
  //Get character
  if(_iShift==0 && _iAlpha==ALPHAOFF)
    cChr = '1';
  else if(_iShift==1)
    cChr = 'S';
  else if(_iAlpha==ALPHAON && _iACase==ALPHAUPPER)
    cChr = 'A';
  else if(_iAlpha==ALPHAON && _iACase==ALPHALOWER)
    cChr = 'a';
  else if(_iAlpha==ALPHALOCK && _iACase==ALPHAUPPER)
    cChr = 'B';
  else if(_iAlpha==ALPHALOCK && _iACase==ALPHALOWER)
    cChr = 'b';
  
  //String
  sStr[0]=cChr;
  sStr[1]=0;
  
  //Keyboard state
  SetFont(FONTS);
  SetColor(COLREV);
  PrintStrXY(_iKbStatPx-1,_iKbStatPy-1," ");
  PrintStrXY(_iKbStatPx-1,_iKbStatPy+0," ");
  PrintStrXY(_iKbStatPx+0,_iKbStatPy-1," ");
  PrintStrXY(_iKbStatPx+0,_iKbStatPy+0,sStr);

}

// ----------------------------------------------------------------
// Get string
int GetString(int iCx,int iCy, int iMax, char *sText, 
              unsigned int iFNOk,   unsigned int iFNExit,
              unsigned int iFNChar, unsigned int iFNCase,
              int iKbStatPx, int iKbStatPy)
{
    //Variables
    int i;                     //Counter
    int iExit;                 //Exit flag
    int iLen;                  //Text length
    int iPtr=0;                //Pointer
    int iAPtr;                 //Previous pointer position
    int iRCode;                //Return value
    int iRefresh;              //Refresh value
    unsigned int iKey;         //Keyboard code
    char cChr;                 //Character
    char sBlank[50];           //Blank string
    
    //Initializations
    if(strlen(sText)>iMax) sText[iMax]=0;
    memset(sBlank,' ',iMax);
    sBlank[iMax]=0;
    SetFont(FONTL);
    SetColor(COLNOR);
    PrintStr(iCx,iCy,sBlank);
    PrintStr(iCx,iCy,sText);
    SetCursor(iCx,iCy,1,0);
    KeyboardStatusLocation(iKbStatPx,iKbStatPy);
    PrintKeyboardStatus();
    Bdisp_PutDisp_DD();
    
    //Main loop
    iExit=0;
    do{
      
      //Check keystroke
      if(KbHit()){
        
        //Inititializations
        iRefresh=0;
        iAPtr=iPtr;
        
        //Get Key
        iKey=GetKeyb();
        
        //Process keys
        switch(iKey)
        {
          //Function keys
          case KEY_CTRL_F1:
          case KEY_CTRL_F2:
          case KEY_CTRL_F3:
          case KEY_CTRL_F4:
          case KEY_CTRL_F5:
          case KEY_CTRL_F6:
            if(iKey==iFNOk)
            {
              iExit=1;
              iRCode=1;
            }
            else if(iKey==iFNExit)
            {
              iExit=1;
              iRCode=0;
            }
            else if(iKey==iFNChar)
            {
              SaveDisp(SAVEDISP_PAGE3);
              cChr=CharacterSelect(0,NULL);
              RestoreDisp(SAVEDISP_PAGE3);
              if(cChr!=0)
              {
                iLen=strlen(sText);
                if(cChr!=0 && iLen<iMax)
                {
                  for(i=iLen+1;i>iPtr;i--) sText[i]=sText[i-1];
                  sText[iPtr]=cChr;
                  iPtr++;
                  iRefresh=1;
                }
              }
            }
            else if(iKey==iFNCase)
            {
              KeyboardStatusChangeCase();
            }
            break;
            
          //Enter
          case KEY_CTRL_EXE: 
            iExit=1;
            iRCode=1;
            break;
          
          //Exit
          case KEY_CTRL_EXIT: 
            iExit=1;
            iRCode=0;
            break;
          
          //Cursor x++
          case KEY_CTRL_RIGHT: 
            iPtr++;
            iLen=strlen(sText);
            if(iPtr>iLen) iPtr--;
            break;
            
          //Cursor x--
          case KEY_CTRL_LEFT: 
            iPtr--; 
            if(iPtr<0) iPtr=0;
            break;
            
          //Delete fowards
          case KEY_CTRL_AC: 
            
            //Delete character from text
            iLen=strlen(sText);
            if(iPtr<iLen)
            {
              for(i=iPtr;i<iLen;i++) sText[i]=sText[i+1];
            }
            iRefresh=1;
            break;
          
          //Delete backwards
          case KEY_CTRL_DEL: 
            
            //Check cursor at the beginning of the text
            if(iPtr==0) break;
            
            //Move cursor backwards
            iPtr--; 
            
            //Delete character from text
            iLen=strlen(sText);
            if(iPtr<iLen)
            {
              for(i=iPtr;i<iLen;i++) sText[i]=sText[i+1];
            }
            iRefresh=1;
            break;
          
          //Print rest of characters
          default: 
            
            //Translate key into character
            cChr=Key2Char(iKey);
            
            //Insert character into text
            iLen=strlen(sText);
            if(cChr!=0 && iLen<iMax)
            {
              for(i=iLen+1;i>iPtr;i--) sText[i]=sText[i-1];
              sText[iPtr]=cChr;
              iPtr++;
              iRefresh=1;
            }
            break;
        }     

        //Soft refresh (only text)
        if(iRefresh==1)
        {
          SetFont(FONTL);
          SetColor(COLNOR);
          PrintStr(iCx,iCy,sBlank);
          PrintStr(iCx,iCy,sText);
          Bdisp_PutDisp_DD();
        }
        
        //Update cursor position
        if(iAPtr!=iPtr || iRefresh!=0)
        {
          SetFont(FONTL);
          SetColor(COLNOR);
          SetCursor(iCx+iAPtr,iCy,0,0);
          SetCursor(iCx+iPtr ,iCy,1,0);
        }
        
        //Clear refresh flag
        iRefresh=0;
      }
    
    }while(iExit==0);

    //Default keyboard status location
    KeyboardStatusLocation(KBSTATPX,KBSTATPY);
    
    //Return value
    return(iRCode);

}

