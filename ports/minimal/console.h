//Console functions (header file ) -----------------------------------------------------

// ------------------------------------------------------------------------------------- 
//Constants

//Keycodes
#define KEYCODES 50

// Keyboard states
#define SHIFTOFF   0  //Shift off    
#define SHIFTON    1  //Shift on    
#define ALPHAOFF   0  //Alpha off
#define ALPHAON    1  //Alpha on
#define ALPHALOCK  2  //Alpha locked
#define ALPHAUPPER 0  //Upper case
#define ALPHALOWER 1  //Lower case

//Keyboard status location
#define KBSTATPX (31*4)
#define KBSTATPY 1

//Keyboard status hide stack
#define MAXSTATUSHIDE 10

// ------------------------------------------------------------------------------------- 
// Type definitions

// Keoboard codes
struct sKeyCode{
  int iNormal;
  int iShift;
  int iAlpha;
};

// ------------------------------------------------------------------------------------- 
//Prototypes
void KeyboardStatusHide(char);
void KeyboardStatusHideStore();
void KeyboardStatusHideRestore();
int KbHit(void);
int KeyMap(int,int,int);
int KeyNormalCase(int);
unsigned int GetKeyb(void);
void KeyboardStatusLocation(int,int);
void PrintKeyboardStatus();
void KeyboardStatusChangeCase(void);
char Key2Char(unsigned int);
int GetString(int,int,int,char *,unsigned int, unsigned int,unsigned int,unsigned int,int,int);
