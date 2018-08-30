//Menu functions (header file) ---------------------------------------------------------

// ------------------------------------------------------------------------------------- 
// Constants

//Type of menu items
#define ITEMTNU 0 //Not used
#define ITEMTFI 1 //Final
#define ITEMTSN 2 //SubNode

//Maximum menu bars and items
#define MAXMENUNODE 6
#define MAXMENUBARS 26
#define MAXSTORBARS 10
#define MAXBARLEVEL 10

//Menubars
//Don't forget to increase MAXMENUBARS when adding to this enum!
enum MenuBars {
MENUBARNULL,MENUBARMAIN,MENUBARFILE,MENUBAREXPL,MENUBARYESN,
MENUBAROKAY,MENUBARMESS,MENUBARGOTO,MENUBAREDIT,MENUBARAUTO,
MENUBARCHAR,MENUBAREDI2,MENUBAREXP2,MENUBARTXTB,MENUBARINFO,
MENUBARNFIL,MENUBARSTRN,MENUBARROOT,MENUBARBIND, //19
MENUBARPRGM,
MENUBARPRGM0, MENUBARPRGM1,MENUBARPRGM2,MENUBARPRGM3,MENUBARPRGM4,MENUBARPRGM5
};

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
NODECHARUBND,NODEEXPLEXE, 
NODEPRGM0,NODEPRGM1,NODEPRGM2,NODEPRGM3,NODEPRGM4,NODEPRGM5,
NODEPRGM6,NODEPRGM7,NODEPRGM8,NODEPRGM9,NODEPRGM10,
NODEPRGM11,NODEPRGM12,NODEPRGM13,NODEPRGM14,NODEPRGM15,
NODEPRGM16,NODEPRGM17,NODEPRGM18,NODEPRGM19,NODEPRGM20,
NODEPRGM21,NODEPRGM22,NODEPRGM23,NODEPRGM24,NODEPRGM25,
NODEPRGM26,NODEPRGM27,NODEPRGM28,NODEPRGM29,NODEPRGM30,
NODEPRGM31,NODEPRGM32,NODEPRGM33,NODEPRGM34,NODEPRGM35,
NODEPRGM36,NODEPRGM37,NODEPRGM38,NODEPRGM39,NODEPRGM40,
NODEPRGM41,NODEPRGM42,NODEPRGM43,NODEPRGM44,NODEPRGM45,
NODEPRGM46,NODEPRGM47,NODEPRGM48,NODEPRGM49,NODEPRGM50,
NODEPRGM51,NODEPRGM52,NODEPRGM53,NODEPRGM54,NODEPRGM55,
NODEPRGM56,NODEPRGM57,NODEPRGM58,NODEPRGM59,NODEPRGM60,
NODEPRGM61,NODEPRGM62,NODEPRGM63,NODEPRGM64,NODEPRGM65,
NODEPRGM66,NODEPRGM67,NODEPRGM68,NODEPRGM69,NODEPRGM70,
NODEPRGM71,NODEPRGM72,NODEPRGM73,NODEPRGM74,NODEPRGM75,
NODEPRGM76,NODEPRGM77,NODEPRGM78,NODEPRGM79,NODEPRGM80,
NODEPRGM81,NODEPRGM82,NODEPRGM83,NODEPRGM84,NODEPRGM85,
NODEPRGM86,NODEPRGM87,NODEPRGM88,NODEPRGM89,NODEPRGM90,
NODEPRGM91,NODEPRGM92,NODEPRGM93,NODEPRGM94,NODEPRGM95,
NODEPRGM96,NODEPRGM97,NODEPRGM98,NODEPRGM99,NODEPRGM100
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
	char *outputText;
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