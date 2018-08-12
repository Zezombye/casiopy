//Menu functions --------------------------------------------------------------------

// ------------------------------------------------------------------------------------- 
//Include files
#include <string.h>
#include "fxlib.h"
#include "stdio.h"
#include "menu.h"
#include "font.h"
#include "console.h"

// ------------------------------------------------------------------------------------- 
// Global variables

// Menu bars
struct MNode _sMNode[MAXMENUBARS][MAXMENUNODE]; 

//Current menu bar, parent bar, store bar
char _cMBar=+0;
char _cBarLevel=0;
char _cPBar[MAXBARLEVEL];
char _cSBar[MAXSTORBARS];
char _cInverse=0;
char _cSIndex=-1;

// ------------------------------------------------------------------------------------- 
// Menu store bar
void MenuStoreBar(void)
{
  if(_cSIndex<MAXSTORBARS-1)
  {
    _cSIndex++;
    _cSBar[_cSIndex]=_cMBar;
  }
}

// ------------------------------------------------------------------------------------- 
// Menu restore bar
void MenuRestoreBar(void)
{
  if(_cSIndex>=0)
  {
    MenuSetBar(_cSBar[_cSIndex]);
    _cSIndex--;
  }
}

// ------------------------------------------------------------------------------------- 
// Menu initialize
void MenuInitialize(void)
{
  
  //Clear all menu nodes
  MenuClear();
  
  //Main menu bar
  MenuSetNode(MENUBARMAIN,0,"FILE",-1          ,MENUBARFILE,0,NULL);
  
  //MenuSetNode(MENUBARFILE,0,"RUN",NODEEXPLEXE,-1         ,0,NULL);
  MenuSetNode(MENUBARMAIN,1,"EDIT",-1          ,MENUBAREDIT,0,NULL);
  MenuSetNode(MENUBARMAIN,2,"GOTO",-1          ,MENUBARGOTO,0,NULL);
  MenuSetNode(MENUBARMAIN,3,"PRGM",-1          ,MENUBARPRGM,0,NULL);
  MenuSetNode(MENUBARMAIN,4,"A<>a",NODEALPHA   ,-1         ,0,NULL);
  MenuSetNode(MENUBARMAIN,5,"CHAR",NODECHARSEL ,-1         ,0,NULL);
  
  //Prgm menu bar
  MenuSetPrgmNode(MENUBARPRGM,0,"if","if", NODEPRGM1);
  MenuSetPrgmNode(MENUBARPRGM,1,"else","else", NODEPRGM2);
  MenuSetPrgmNode(MENUBARPRGM,2,"for","for", NODEPRGM3);
  MenuSetPrgmNode(MENUBARPRGM,3,"prnt","print(", NODEPRGM4);
  MenuSetPrgmNode(MENUBARPRGM,4,"inpt","input(", NODEPRGM5);
  MenuSetNode(MENUBARPRGM,5,"    ",-1          ,MENUBAREDI2,1,NextButton);
  
  
  //File menu bar
  MenuSetNode(MENUBARFILE,0,"SAVE",NODEFILESAVE,-1         ,0,NULL);
  MenuSetNode(MENUBARFILE,1,"S.AS",NODEFILESVAS,-1         ,0,NULL);
  //MenuSetNode(MENUBARFILE,2,"AUTO",NODEFILEAUTO,-1         ,0,NULL);

  //Goto menu bar
  MenuSetNode(MENUBARGOTO,0,"TOP ",NODEGOTOTOP ,-1         ,0,NULL);
  MenuSetNode(MENUBARGOTO,1,"BOTM",NODEGOTOBTM ,-1         ,0,NULL);
  MenuSetNode(MENUBARGOTO,2,"HOME",NODEGOTOHOME,-1         ,0,NULL);
  MenuSetNode(MENUBARGOTO,3,"END ",NODEGOTOEND ,-1         ,0,NULL);
  MenuSetNode(MENUBARGOTO,4,"PAG-",NODEGOTOPGU ,-1         ,0,NULL);
  MenuSetNode(MENUBARGOTO,5,"PAG+",NODEGOTOPGD ,-1         ,0,NULL);
  
  //Edit menu bar
  MenuSetNode(MENUBAREDIT,0,"CLIP",NODEEDITCLIP,-1         ,0,NULL);
  MenuSetNode(MENUBAREDIT,1,"COPY",NODEEDITCOPY,-1         ,0,NULL);
  MenuSetNode(MENUBAREDIT,2,"CUT ",NODEEDITCUT ,-1         ,0,NULL);
  MenuSetNode(MENUBAREDIT,3,"PAST",NODEEDITPAST,-1         ,0,NULL);
  MenuSetNode(MENUBAREDIT,4,"DEL ",NODEEDITDEL ,-1         ,0,NULL);
  MenuSetNode(MENUBAREDIT,5,"    ",-1          ,MENUBAREDI2,1,NextButton);
  
  //Edit menu bar (next)
  MenuSetNode(MENUBAREDI2,0,"SRC ",NODEEDI2SRC1,-1         ,0,NULL);
  MenuSetNode(MENUBAREDI2,1,"SRC+",NODEEDI2SRCN,-1         ,0,NULL);
  MenuSetNode(MENUBAREDI2,5,"    ",NODERETURN1 ,-1         ,0,NextButton);
  
  /*//Option menu bar
  MenuSetNode(MENUBAROPTN,0,"OPTN",NODEHELPOPTN,-1         ,0,NULL);
  MenuSetNode(MENUBAROPTN,1,"MEM ",NODEHELPMEMO,-1         ,0,NULL);
  MenuSetNode(MENUBAROPTN,4,"HELP",NODEHELPHELP,-1         ,0,NULL);
  MenuSetNode(MENUBAROPTN,5,"ABOU",NODEHELPABOU,-1         ,0,NULL);*/
  
  //Explorer menu bar
  MenuSetNode(MENUBAREXPL,0,"EXE",NODEEXPLEXE,-1         ,0,NULL);
  MenuSetNode(MENUBAREXPL,1,"EDIT",NODEEXPLOPEN,-1         ,0,NULL);
  MenuSetNode(MENUBAREXPL,2,"NEW ",NODEEXPLNEW ,-1         ,0,NULL);
  MenuSetNode(MENUBAREXPL,3,"DEL ",NODEEXPLDEL ,-1         ,0,NULL);
  //MenuSetNode(MENUBAREXPL,3,"FILE",-1          ,MENUBAREXP2,0,NULL);
  //MenuSetNode(MENUBAREXPL,3,"OPTN",-1          ,MENUBAROPTN,0,NULL);
  MenuSetNode(MENUBAREXPL,4,"REN ",NODEEXPLREN ,-1         ,0,NULL);
  MenuSetNode(MENUBAREXPL,5,"COPY",NODEEXPLCOPY ,-1         ,0,NULL);
  //MenuSetNode(MENUBAREXPL,4,"ROOT",-1          ,MENUBARROOT,0,NULL);
  
  //Explorer menu bar (extension)
  MenuSetNode(MENUBAREXP2,0,"REN ",NODEEXPLREN ,-1         ,0,NULL);
  MenuSetNode(MENUBAREXP2,1,"COPY",NODEEXPLCOPY,-1         ,0,NULL);
  MenuSetNode(MENUBAREXP2,2,"MOVE",NODEEXPLMOVE,-1         ,0,NULL);
  MenuSetNode(MENUBAREXP2,3,"NEWF",NODEEXPLNEWF,-1         ,0,NULL);
  MenuSetNode(MENUBAREXP2,4,"DELF",NODEEXPLDELF,-1         ,0,NULL);
  
  //Explorer menu bar (Root)
  MenuSetNode(MENUBARROOT,3,"MAIN",NODEEXPLMAIN,-1         ,0,NULL);
  MenuSetNode(MENUBARROOT,4,"SMEM",NODEEXPLFLS ,-1         ,0,NULL);
  MenuSetNode(MENUBARROOT,5,"SDC ",NODEEXPLCRD ,-1         ,0,NULL);
  
  //Explorer menu bar (set auto file mode)
  MenuSetNode(MENUBARAUTO,0,"SET ",NODEAUTOSET ,-1         ,0,NULL);
  MenuSetNode(MENUBARAUTO,4,"ROOT",-1          ,MENUBARROOT,0,NULL);
  
  //Popup continue yes / no
  MenuSetNode(MENUBARYESN,0,"YES",NODECONTYES ,-1           ,0,NULL);
  MenuSetNode(MENUBARYESN,5,"NO ",NODECONTNO  ,-1           ,0,NULL);
  
  //Okay / Exit
  MenuSetNode(MENUBAROKAY,0,"OK  ",NODEOKAYOK ,-1           ,0,NULL);
  MenuSetNode(MENUBAROKAY,5,"EXIT",NODEOKAYEX ,-1           ,0,NULL);
  
  //Getstring
  MenuSetNode(MENUBARSTRN,0,"OK  ",NODESTRNOK ,-1           ,0,NULL);
  MenuSetNode(MENUBARSTRN,2,"CHAR",NODESTRNCHR,-1           ,0,NULL);
  MenuSetNode(MENUBARSTRN,3,"a<>A",NODESTRNCAS,-1           ,0,NULL);
  MenuSetNode(MENUBARSTRN,5,"EXIT",NODESTRNEXI,-1           ,0,NULL);
  
  //Menu bar for messages
  MenuSetNode(MENUBARMESS,0,"OK  ",NODEMESSOK,-1           ,0,NULL);
 /* 
  //Help text navigation
  MenuSetNode(MENUBARHNAV,0,"PAG-",NODEHELPPAGU,-1         ,0,NULL);
  MenuSetNode(MENUBARHNAV,1,"PAG+",NODEHELPPAGD,-1         ,0,NULL);
  MenuSetNode(MENUBARHNAV,5,"EXIT",NODEHELPEXIT,-1         ,0,NULL);
  
  //Configuration mode (Try SD Card)
  MenuSetNode(MENUBARTRSD,0,"YES",NODETRYSDYES,-1          ,0,NULL);
  MenuSetNode(MENUBARTRSD,1,"NO ",NODETRYSDNO ,-1          ,0,NULL);
  
  //Configuration mode (New line mode)
  MenuSetNode(MENUBARNLMO,0,"WIN ",NODENLMOWIN ,-1         ,0,NULL);
  MenuSetNode(MENUBARNLMO,1,"UNIX",NODENLMOUNIX,-1         ,0,NULL);
  
  //Configuration mode (Info)
  MenuSetNode(MENUBARINFO,0,"FOLD",NODEINFOFOLD,-1         ,0,NULL);
  MenuSetNode(MENUBARINFO,1,"CURS",NODEINFOCURS,-1         ,0,NULL);
  
  //Configuration mode (Font)
  MenuSetNode(MENUBARFONT,0,"Tiny",NODEFONT3X5 ,-1         ,0,NULL);
  MenuSetNode(MENUBARFONT,1,"Smal",NODEFONT3X6 ,-1         ,0,NULL);
  MenuSetNode(MENUBARFONT,2,"Medm",NODEFONT4X6 ,-1         ,0,NULL);
  MenuSetNode(MENUBARFONT,3,"Larg",NODEFONT5X7 ,-1         ,0,NULL);
  
  //Configuration mode (Auto open)
  MenuSetNode(MENUBARAOPE,0,"YES",NODEAOPEYES ,-1           ,0,NULL);
  MenuSetNode(MENUBARAOPE,1,"NO ",NODEAOPENO  ,-1           ,0,NULL);
  
  //Configuration mode (Auto name)
  MenuSetNode(MENUBARACFG,0,"SET ",NODEACFGSET,-1           ,0,NULL);
  MenuSetNode(MENUBARACFG,1,"CLR ",NODEACFGCLR,-1           ,0,NULL);
  
  //Configuration mode (Hide system files)
  MenuSetNode(MENUBARHSYS,0,"HIDN",NODEHSYSYES ,-1          ,0,NULL);
  MenuSetNode(MENUBARHSYS,1,"DISP",NODEHSYSNO  ,-1          ,0,NULL);
  
  //Configuration mode (Word Wrap)
  MenuSetNode(MENUBARWWRA,0,"ON  ",NODEWWRAPON ,-1          ,0,NULL);
  MenuSetNode(MENUBARWWRA,1,"OFF ",NODEWWRAPOFF,-1          ,0,NULL);
  
  //Configuration mode (Display bytes free)
  MenuSetNode(MENUBARDFRE,0,"YES ",NODEDFREYES ,-1          ,0,NULL);
  MenuSetNode(MENUBARDFRE,1,"NO  ",NODEDFRENO  ,-1          ,0,NULL);
  
  //Configuration mode (Default root)
  MenuSetNode(MENUBARDROO,0,"MAIN",NODEDROOMAIN,-1          ,0,NULL);
  MenuSetNode(MENUBARDROO,1,"SMEM",NODEDROOSMEM,-1          ,0,NULL);
  MenuSetNode(MENUBARDROO,2,"SDC ",NODEDROOSDC ,-1          ,0,NULL);
  
  //Configuration mode (Text buffer size)
  MenuSetNode(MENUBARTXTB,0," 4Kb",NODETXTB04K ,-1          ,0,NULL);
  MenuSetNode(MENUBARTXTB,1," 8Kb",NODETXTB08K ,-1          ,0,NULL);
  MenuSetNode(MENUBARTXTB,2,"16Kb",NODETXTB16K ,-1          ,0,NULL);
  MenuSetNode(MENUBARTXTB,3,"24Kb",NODETXTB24K ,-1          ,0,NULL);
  MenuSetNode(MENUBARTXTB,4,"32Kb",NODETXTB32K ,-1          ,0,NULL);
  MenuSetNode(MENUBARTXTB,5,"40Kb",NODETXTB40K ,-1          ,0,NULL);
  
  //Configuration mode (Clip buffer size)
  MenuSetNode(MENUBARCLIB,0," 1Kb",NODECLIB01K ,-1          ,0,NULL);
  MenuSetNode(MENUBARCLIB,1," 2Kb",NODECLIB02K ,-1          ,0,NULL);
  MenuSetNode(MENUBARCLIB,2," 4Kb",NODECLIB04K ,-1          ,0,NULL);
  MenuSetNode(MENUBARCLIB,3," 8Kb",NODECLIB08K ,-1          ,0,NULL);
  MenuSetNode(MENUBARCLIB,4,"12Kb",NODECLIB12K ,-1          ,0,NULL);
  MenuSetNode(MENUBARCLIB,5,"16Kb",NODECLIB16K ,-1          ,0,NULL);
  
  //Configuration mode (Maximum number of files per directory)
  MenuSetNode(MENUBARNFIL,0,"32 ",NODENFIL000 ,-1          ,0,NULL);
  MenuSetNode(MENUBARNFIL,1,"48 ",NODENFIL001 ,-1          ,0,NULL);
  MenuSetNode(MENUBARNFIL,2,"64 ",NODENFIL002 ,-1          ,0,NULL);
  MenuSetNode(MENUBARNFIL,3,"96 ",NODENFIL003 ,-1          ,0,NULL);
  MenuSetNode(MENUBARNFIL,4,"128",NODENFIL004 ,-1          ,0,NULL);
  MenuSetNode(MENUBARNFIL,5,"256",NODENFIL005 ,-1          ,0,NULL);
  
  //Configuration mode (Maximum total number of folders)
  MenuSetNode(MENUBARNFOL,0,"16 ",NODENFOL000 ,-1          ,0,NULL);
  MenuSetNode(MENUBARNFOL,1,"32 ",NODENFOL001 ,-1          ,0,NULL);
  MenuSetNode(MENUBARNFOL,2,"48 ",NODENFOL002 ,-1          ,0,NULL);
  MenuSetNode(MENUBARNFOL,3,"64 ",NODENFOL003 ,-1          ,0,NULL);
  MenuSetNode(MENUBARNFOL,4,"96 ",NODENFOL004 ,-1          ,0,NULL);
  MenuSetNode(MENUBARNFOL,5,"128",NODENFOL005 ,-1          ,0,NULL);*/
  
  //Character selection
  MenuSetNode(MENUBARCHAR,0,"INSR",NODECHARINSR,-1          ,0,NULL);
  MenuSetNode(MENUBARCHAR,4,"BIND",NODECHARBIND,-1          ,0,NULL);
  MenuSetNode(MENUBARCHAR,5,"UBND",NODECHARUBND,-1          ,0,NULL);
  
}

// ------------------------------------------------------------------------------------- 
// Menu node enable
void MenuEnableNode(char cMBar, char cNode)
{
  _sMNode[cMBar][cNode].cUsed=1;
}

// ------------------------------------------------------------------------------------- 
// Menu node disable
void MenuDisableNode(char cMBar, char cNode)
{
  _sMNode[cMBar][cNode].cUsed=0;
}

// ------------------------------------------------------------------------------------- 
// Menu set node
void MenuSetNode(char cMBar, char cNode, char *sName,int iCode, 
                 char cSBar, char cInv, void (*pFunc)(int,int))
{
  strcpy(_sMNode[cMBar][cNode].sName,sName);
  _sMNode[cMBar][cNode].iCode = iCode;
  _sMNode[cMBar][cNode].cSBar = cSBar;
  _sMNode[cMBar][cNode].cInv  = cInv;
  _sMNode[cMBar][cNode].pFunc = pFunc;
  _sMNode[cMBar][cNode].cUsed = 1;
}

void MenuSetPrgmNode(char cMBar, char cNode, char *sName, char* outputText, int iCode)
{

  strcpy(_sMNode[cMBar][cNode].sName,sName);
  _sMNode[cMBar][cNode].iCode = iCode;
  _sMNode[cMBar][cNode].cSBar = -1;
  _sMNode[cMBar][cNode].cInv  = 0;
  _sMNode[cMBar][cNode].pFunc = NULL;
  strcpy(_sMNode[cMBar][cNode].outputText,outputText);
  _sMNode[cMBar][cNode].cUsed = 1;
}

// ------------------------------------------------------------------------------------- 
// Menu Clear
void MenuClear(void)
{
  //Variables
  char i,j;
  
  //Clear all menu items
  for(i=0;i<MAXMENUBARS;i++){
  for(j=0;j<MAXMENUNODE;j++){
    sprintf(_sMNode[i][j].sName,"");
    _sMNode[i][j].iCode = 0;
    _sMNode[i][j].cSBar = 0;
    _sMNode[i][j].cUsed = 0;
  }}
}

// ------------------------------------------------------------------------------------- 
// Set menu function
void MenuSetBar(char cBar)
{
  //Print menu bar
  MenuPrintBar(cBar);
  
  //Set current bar
  _cMBar = cBar;
}

// ------------------------------------------------------------------------------------- 
// Get menu function
int MenuGetBar(void)
{
  //Return current bar
  return(_cMBar);
}

// ------------------------------------------------------------------------------------- 
// Process function key
int MenuFunctionKey(unsigned int iKey)
{
  //Variables
  char cNode=0;
  char cExit=0;
  
  //Calculate node from function key
  switch(iKey)
  {
    case KEY_CTRL_F1:   cNode=0;  break;
    case KEY_CTRL_F2:   cNode=1;  break;
    case KEY_CTRL_F3:   cNode=2;  break;
    case KEY_CTRL_F4:   cNode=3;  break;
    case KEY_CTRL_F5:   cNode=4;  break;
    case KEY_CTRL_F6:   cNode=5;  break;
    case KEY_CTRL_EXIT: cExit=1;  break;
    default:            cNode=-1; break;
  }
  
  //Invalid key
  if(cNode==-1) return(NODENOFUNCT);
  
  //Return to previous menu if exit pressed
  if(cExit==1 && _cBarLevel>0)
  {
    _cBarLevel--;
    _cMBar=_cPBar[_cBarLevel];
    MenuPrintBar(_cMBar);
    return(NODENOFUNCT);
  }
  
  //Return to previous menu (initial state)
  else if(cExit==1 && _cBarLevel==0)
  {
    return(NODENOFUNCT);
  }
  
  //Return to previous menu by exit node
  else if(_sMNode[_cMBar][cNode].cSBar==-1 
       && _sMNode[_cMBar][cNode].cUsed==1
       && _sMNode[_cMBar][cNode].iCode==NODERETURN1)
  {
    _cBarLevel--;
    _cMBar=_cPBar[_cBarLevel];
    MenuPrintBar(_cMBar);
    return(NODENOFUNCT);
  }
  
  //Return node code for non parent nodes
  else if(_sMNode[_cMBar][cNode].cSBar==-1 
       && _sMNode[_cMBar][cNode].cUsed==1 )
  {
    return(_sMNode[_cMBar][cNode].iCode);
  }
  
  //Not used or disabled node pressed
  else if(_sMNode[_cMBar][cNode].cUsed==0 )
  {
    return(NODENOFUNCT);
  }
  
  //Set new bar for parent nodes
  else
  {
    _cPBar[_cBarLevel]=_cMBar;
    _cBarLevel++;
    _cMBar=_sMNode[_cMBar][cNode].cSBar;
    MenuPrintBar(_cMBar);
    return(NODENOFUNCT);
  }

}

// ------------------------------------------------------------------------------------- 
// Menu Print Bar
void MenuPrintBar(char cBar)
{
  //Variables
  char i;
  
  //Print menu nodes
  for(i=0;i<MAXMENUNODE;i++){
    MenuPrintNode(cBar,i);
  }
}

// ------------------------------------------------------------------------------------- 
// Menu Print Node
void MenuPrintNode(char cBar,char cNode)
{
  //Clear node space
  Bdisp_ClearLineVRAM(
  cNode*(5*4+1)+2,56+0,(cNode+1)*(5*4+1)-1,56+0);
  Bdisp_ClearLineVRAM(
  cNode*(5*4+1)+2,56+1,(cNode+1)*(5*4+1)-1,56+1);
  Bdisp_ClearLineVRAM(
  cNode*(5*4+1)+2,56+2,(cNode+1)*(5*4+1)-1,56+2);
  Bdisp_ClearLineVRAM(
  cNode*(5*4+1)+2,56+3,(cNode+1)*(5*4+1)-1,56+3);
  Bdisp_ClearLineVRAM(
  cNode*(5*4+1)+2,56+4,(cNode+1)*(5*4+1)-1,56+4);
  Bdisp_ClearLineVRAM(
  cNode*(5*4+1)+2,56+5,(cNode+1)*(5*4+1)-1,56+5);
  Bdisp_ClearLineVRAM(
  cNode*(5*4+1)+2,56+6,(cNode+1)*(5*4+1)-1,56+6);
  Bdisp_ClearLineVRAM(
  cNode*(5*4+1)+2,56+7,(cNode+1)*(5*4+1)-1,56+7);
  
  //Only print used nodes
  if(_sMNode[cBar][cNode].cUsed==1)
  {
    //Final nodes
    if(_sMNode[cBar][cNode].cSBar==-1 || 
      (_sMNode[cBar][cNode].cSBar!=-1 && _sMNode[cBar][cNode].cInv==1)){
      SetFont(FONTS);
      Bdisp_DrawLineVRAM(
      cNode*(5*4+1)+2,56+0,(cNode+1)*(5*4+1)-1-0,56+0);
      Bdisp_DrawLineVRAM(
      cNode*(5*4+1)+2,56+0,cNode*(5*4+1)+2,56+7);
      SetColor(COLNOR);
      if(_sMNode[cBar][cNode].pFunc!=NULL)
        (*_sMNode[cBar][cNode].pFunc)(2+cNode*(5*4+1)+2,58);
      else
        PrintStrXY(2+cNode*(5*4+1)+2,58,_sMNode[cBar][cNode].sName);
    }
    
    //Parent nodes
    else if(_sMNode[cBar][cNode].cSBar!=-1 || 
           (_sMNode[cBar][cNode].cSBar==-1 && _sMNode[cBar][cNode].cInv==1)){
      SetFont(FONTT);
      SetColor(COLREV);
      Bdisp_DrawLineVRAM(
      cNode*(5*4+1)+2,56+0,(cNode+1)*(5*4+1)-1-0,56+0);
      Bdisp_DrawLineVRAM(
      cNode*(5*4+1)+2,56+1,(cNode+1)*(5*4+1)-1-0,56+1);
      Bdisp_DrawLineVRAM(
      cNode*(5*4+1)+2,56+2,(cNode+1)*(5*4+1)-1-0,56+2);
      Bdisp_DrawLineVRAM(
      cNode*(5*4+1)+2,56+3,(cNode+1)*(5*4+1)-1-0,56+3);
      Bdisp_DrawLineVRAM(
      cNode*(5*4+1)+2,56+4,(cNode+1)*(5*4+1)-1-0,56+4);
      Bdisp_DrawLineVRAM(
      cNode*(5*4+1)+2,56+5,(cNode+1)*(5*4+1)-1-1,56+5);
      Bdisp_DrawLineVRAM(
      cNode*(5*4+1)+2,56+6,(cNode+1)*(5*4+1)-1-2,56+6);
      Bdisp_DrawLineVRAM(
      cNode*(5*4+1)+2,56+7,(cNode+1)*(5*4+1)-1-3,56+7);
      if(_sMNode[cBar][cNode].pFunc!=NULL)
        (*_sMNode[cBar][cNode].pFunc)(1+cNode*(5*4+1)+2,57);
      else
        PrintStrXY(1+cNode*(5*4+1)+2,57,_sMNode[cBar][cNode].sName); 
      ML_pixel((cNode+1)*(5*4+1)-1-2,56+7,0);
    }
  }
}

// ------------------------------------------------------------------------------------- 
// Print next menu bar icon
void NextButton(int iPx, int iPy)
{
  SetFont(2);
  SetColor(COLNOR);
  PrintCharXY(iPx+7,iPy-1,7);
}
