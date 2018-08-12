//Menu functions (header file) ---------------------------------------------------------

// ------------------------------------------------------------------------------------- 
// Constants

//Type of menu items
#define ITEMTNU 0 //Not used
#define ITEMTFI 1 //Final
#define ITEMTSN 2 //SubNode

//Maximum menu bars and items
#define MAXMENUNODE 6
#define MAXMENUBARS 20
#define MAXSTORBARS 10
#define MAXBARLEVEL 10

//Menubars
enum MenuBars {
MENUBARNULL,MENUBARMAIN,MENUBARFILE,MENUBAREXPL,MENUBARYESN,
MENUBAROKAY,MENUBARMESS,MENUBARGOTO,MENUBAREDIT,MENUBARAUTO,
MENUBARCHAR,MENUBAREDI2,MENUBAREXP2,MENUBARTXTB,MENUBARINFO,
MENUBARNFIL,MENUBARSTRN,MENUBARROOT,MENUBARBIND, MENUBARPRGM};

//Node return codes
enum node_constants {
NODENOFUNCT ,NODERETURN1 ,NODEALPHA   ,NODEPAGEUP  ,NODEPAGEDOWN,
NODEFILESAVE,NODEFILESVAS,NODEEXPLOPEN,NODEEXPLFLS ,NODEEXPLCRD ,
NODECONTYES ,NODECONTNO  ,NODEOKAYOK  ,NODEOKAYEX  ,NODEMESSOK  ,
NODEGOTOTOP ,NODEGOTOBTM ,NODEGOTOPGD ,NODEGOTOPGU ,NODEEDITCLIP,
NODEEDITCOPY,NODEEDITCUT ,NODEEDITPAST,NODEEDITDEL ,NODEHELPHELP,
NODEHELPABOU,NODEMAINFONT,NODEHELPPAGD,NODEHELPPAGU,NODEHELPEXIT,
NODEFONT3X5 ,NODEFONT3X6 ,NODEFONT4X6 ,NODEFONT5X7 ,NODENLMOWIN ,
NODENLMOUNIX,NODECHARSEL ,NODETRYSDYES,NODETRYSDNO ,NODEAOPEYES ,
NODEAOPENO  ,NODEACFGSET ,NODEACFGCLR ,NODEFILEAUTO,NODEAUTOSET ,
NODECHARINSR,NODEHELPOPTN,NODEEDI2SRC1,NODEEDI2SRCN,NODEEXPLCOPY,
NODEEXPLMOVE,NODEEXPLDEL ,NODEEXPLREN ,NODEHSYSYES ,NODEHSYSNO  ,
NODETXTB04K ,NODETXTB08K ,NODETXTB16K ,NODETXTB24K ,NODETXTB32K ,
NODETXTB40K ,NODECLIB01K ,NODECLIB02K ,NODECLIB04K ,NODECLIB08K ,
NODECLIB12K ,NODECLIB16K ,NODEHELPMEMO,NODEINFOFOLD,NODEINFOCURS,
NODEWWRAPON ,NODEWWRAPOFF,NODEGOTOHOME,NODEGOTOEND ,NODENFIL000 , 
NODENFIL001, NODENFIL002 ,NODENFIL003, NODENFIL004 ,NODENFIL005 , 
NODENFOL000, NODENFOL001 ,NODENFOL002, NODENFOL003 ,NODENFOL004 , 
NODENFOL005, NODESTRNOK  ,NODESTRNCHR, NODESTRNCAS ,NODESTRNEXI, 
NODEEXPLNEW, NODEEXPLMAIN,NODEDFREYES, NODEDFRENO  ,NODEDROOMAIN,
NODEDROOSMEM,NODEDROOSDC ,NODEEXPLNEWF,NODEEXPLDELF,NODECHARBIND,
NODECHARUBND,NODEEXPLEXE, NODEPRGM1,NODEPRGM2,NODEPRGM3,NODEPRGM4,NODEPRGM5,
};



// ---------------------------------------------------------------------------
// Structures

// Menu item
struct MNode
{
    char sName[5];           //Menu entry name
    int  iCode;              //Return code for this entry
    char cSBar;              //Menu bar linked to this item
    char cInv;               //Inverse print mode
    void (*pFunc)(int,int);  //Special routine for node write
    char cUsed;             //Used flag
	char outputText[7];
};

// ------------------------------------------------------------------------------------- 
// Prototypes
void MenuStoreBar();
void MenuRestoreBar();
void MenuInitialize(void);
void MenuSetNode(char,char,char *,int,char,char,void (*pFunc)(int,int));
void MenuSetPrgmNode(char cMBar, char cNode, char *sName, char* outputText, int iCode);
void MenuClear(void);
void MenuPrintBar(char);
void MenuPrintNode(char,char);
void MenuSetBar(char);
int MenuGetBar(void);
int MenuFunctionKey(unsigned int);
void NextButton(int,int);