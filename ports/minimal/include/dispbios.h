/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : dispbios.h                                      */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __DISPBIOS_H__
#define __DISPBIOS_H__


// Defines

#define IM_VRAM_WIDTH               128
#define IM_VRAM_HEIGHT              64

#define IM_VRAM_SIZE                1024

#define IM_CHARACTERS_MAX_LINE      21
#define IM_BYTES_MAX_LINE           (IM_CHARACTERS_MAX_LINE*2)

#define SAVEDISP_PAGE1              1
#define SAVEDISP_PAGE2              5
#define SAVEDISP_PAGE3              6

#define MINI_OVER                   0x10
#define MINI_OR                     0x11
#define MINI_REV                    0x12
#define MINI_REVOR                  0x13

#define IM_BIOS_DD_WIDTH            IM_VRAM_WIDTH
#define IM_BIOS_DD_HEIGHT           IM_VRAM_HEIGHT

#define WRITEKIND                   unsigned char
#define IMB_WRITEKIND_OVER          0x01
#define IMB_WRITEKIND_OR            0x02
#define IMB_WRITEKIND_AND           0x03
#define IMB_WRITEKIND_XOR           0x04

#define WRITEMODIFY                 unsigned char
#define IMB_WRITEMODIFY_NORMAL      0x01
#define IMB_WRITEMODIFY_REVERCE     0x02
#define IMB_WRITEMODIFY_MESH        0x03

#define AREAKIND                    unsigned char
#define IMB_AREAKIND_OVER           0x01
#define IMB_AREAKIND_MESH           0x02
#define IMB_AREAKIND_CLR            0x03
#define IMB_AREAKIND_REVERSE        0x04

#define EFFECTWIN                   unsigned char
#define IMB_EFFECTWIN_OK            0x01
#define IMB_EFFECTWIN_NG            0x02


// Structs

typedef struct tag_DISPBOX{
    int     left;
    int     top;
    int     right;
    int     bottom;
} DISPBOX;

typedef struct tag_GRAPHDATA{
    int             width;
    int             height;
    unsigned char   *pBitmap;
} GRAPHDATA;

typedef struct tag_RECTANGLE{
    DISPBOX         LineArea;
    AREAKIND        AreaKind;
    EFFECTWIN       EffectWin;
} RECTANGLE;

typedef struct tag_DISPGRAPH{
    int             x;
    int             y;
    GRAPHDATA       GraphData;
    WRITEMODIFY     WriteModify;
    WRITEKIND       WriteKind;
} DISPGRAPH;


#endif

#ifdef __cplusplus
}
#endif
