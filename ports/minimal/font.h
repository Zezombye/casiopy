//Font functions (header file) ---------------------------------------------------------

// ------------------------------------------------------------------------------------- 
//Constants

//Fonts
#define FONTS 0 //3x5
#define FONTT 1 //3x7
#define FONTM 3 //4x6
#define FONTL 2 //5x7

//Colors
#define COLNOR 0
#define COLREV 1

//Maximun sizes
#define FONTMAX 4
#define CONTMAX 10

// ------------------------------------------------------------------------------------- 
// Type definitions

// Font data
struct FData{
  int iAx;               //Font width
  int iAy;               //Font height
  int iSx;               //Screen width size in chars
  int iSy;               //Screen height in chars
  unsigned int *iChData; //Char data
};

// Font context
struct FCntx{
  int iFont;  //Font
  int iColor; //Color
  int iPx0;   //Offset X
  int iPy0;   //Offset y
};

// ------------------------------------------------------------------------------------- 
//Prototypes

void DefineFontContext(int,int,int,int,int);
void SetFontContext(int);
void SetFont(int);
void SetColor(int);
void SetOffset(int,int);
void SetColorCntx(int);
int GetScrCAx(void);
int GetScrCAy(void);
void PrintCharXY(int,int,char);
void PrintChar(int,int,char);
void PrintStr(int,int,char *);
void PrintStrXY(int,int,char *);
void SetCursor(int,int,int,int);
