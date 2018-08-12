/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : filebios.h                                      */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __FILEBIOS_H__
#define __FILEBIOS_H__


// Defines

#define FONTCHARACTER               unsigned short

#define _OPENMODE_READ              0x01
#define _OPENMODE_READ_SHARE        0x80
#define _OPENMODE_WRITE             0x02
#define _OPENMODE_READWRITE         0x03
#define _OPENMODE_READWRITE_SHARE   0x83

#define _CREATEMODE_BINARY          1
#define _CREATEMODE_DIRECTORY       5

enum DEVICE_TYPE{
    DEVICE_MAIN_MEMORY,
    DEVICE_STORAGE,
    DEVICE_SD_CARD,                 // only fx-9860G SD model
};


// File system standard error code
#define IML_FILEERR_NOERROR             0
#define IML_FILEERR_ENTRYNOTFOUND       -1
#define IML_FILEERR_ILLEGALPARAM        -2
#define IML_FILEERR_ILLEGALPATH         -3
#define IML_FILEERR_DEVICEFULL          -4
#define IML_FILEERR_ILLEGALDEVICE       -5
#define IML_FILEERR_ILLEGALFILESYS      -6
#define IML_FILEERR_ILLEGALSYSTEM       -7
#define IML_FILEERR_ACCESSDENYED        -8
#define IML_FILEERR_ALREADYLOCKED       -9
#define IML_FILEERR_ILLEGALTASKID       -10
#define IML_FILEERR_PERMISSIONERROR     -11
#define IML_FILEERR_ENTRYFULL           -12
#define IML_FILEERR_ALREADYEXISTENTRY   -13
#define IML_FILEERR_READONLYFILE        -14
#define IML_FILEERR_ILLEGALFILTER       -15
#define IML_FILEERR_ENUMRATEEND         -16
#define IML_FILEERR_DEVICECHANGED       -17
//#define IML_FILEERR_NOTRECORDFILE     -18     // Not used
#define IML_FILEERR_ILLEGALSEEKPOS      -19
#define IML_FILEERR_ILLEGALBLOCKFILE    -20
//#define IML_FILEERR_DEVICENOTEXIST    -21     // Not used
//#define IML_FILEERR_ENDOFFILE         -22     // Not used
#define IML_FILEERR_NOTMOUNTDEVICE      -23
#define IML_FILEERR_NOTUNMOUNTDEVICE    -24
#define IML_FILEERR_CANNOTLOCKSYSTEM    -25
#define IML_FILEERR_RECORDNOTFOUND      -26
//#define IML_FILEERR_NOTDUALRECORDFILE -27     // Not used
#define IML_FILEERR_NOTALARMSUPPORT     -28
#define IML_FILEERR_CANNOTADDALARM      -29
#define IML_FILEERR_FILEFINDUSED        -30
#define IML_FILEERR_DEVICEERROR         -31
#define IML_FILEERR_SYSTEMNOTLOCKED     -32
#define IML_FILEERR_DEVICENOTFOUND      -33
#define IML_FILEERR_FILETYPEMISMATCH    -34
#define IML_FILEERR_NOTEMPTY            -35
#define IML_FILEERR_BROKENSYSTEMDATA    -36
#define IML_FILEERR_MEDIANOTREADY       -37
#define IML_FILEERR_TOOMANYALARMITEM    -38
#define IML_FILEERR_SAMEALARMEXIST      -39
#define IML_FILEERR_ACCESSSWAPAREA      -40
#define IML_FILEERR_MULTIMEDIACARD      -41
#define IML_FILEERR_COPYPROTECTION      -42
#define IML_FILEERR_ILLEGALFILEDATA     -43

// FILE_INFO.type
#define DT_DIRECTORY            0x0000      // Directory
#define DT_FILE                 0x0001      // File
#define DT_ADDIN_APP            0x0002      // Add-In application
#define DT_EACT                 0x0003      // eActivity
#define DT_LANGUAGE             0x0004      // Language
#define DT_BITMAP               0x0005      // Bitmap
#define DT_MAINMEM              0x0006      // Main Memory data
#define DT_TEMP                 0x0007      // Temporary data
#define DT_DOT                  0x0008      // .  (Current directory)
#define DT_DOTDOT               0x0009      // .. (Parent directory)
#define DT_VOLUME               0x000A      // Volume label


// Structs

typedef struct tag_FILE_INFO
{
    unsigned short  id;
    unsigned short  type;
    unsigned long   fsize;                  // File size
    unsigned long   dsize;                  // Data size
    unsigned int    property;               // The file has not been completed, except when property is 0.
    unsigned long   address;
} FILE_INFO;


#endif

#ifdef __cplusplus
}
#endif
