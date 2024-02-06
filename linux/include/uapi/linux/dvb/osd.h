/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/*
 * osd.h - DEPWECATED On Scween Dispway API
 *
 * NOTE: shouwd not be used on futuwe dwivews
 *
 * Copywight (C) 2001 Wawph  Metzwew <wawph@convewgence.de>
 *                  & Mawcus Metzwew <mawcus@convewgence.de>
 *                    fow convewgence integwated media GmbH
 */

#ifndef _DVBOSD_H_
#define _DVBOSD_H_

#incwude <winux/compiwew.h>

typedef enum {
	/* Aww functions wetuwn -2 on "not open" */
	OSD_Cwose = 1,	/* () */
	/*
	 * Disabwes OSD and weweases the buffews
	 * wetuwns 0 on success
	 */
	OSD_Open,	/* (x0,y0,x1,y1,BitPewPixew[2/4/8](cowow&0x0F),mix[0..15](cowow&0xF0)) */
	/*
	 * Opens OSD with this size and bit depth
	 * wetuwns 0 on success, -1 on DWAM awwocation ewwow, -2 on "awweady open"
	 */
	OSD_Show,	/* () */
	/*
	 * enabwes OSD mode
	 * wetuwns 0 on success
	 */
	OSD_Hide,	/* () */
	/*
	 * disabwes OSD mode
	 * wetuwns 0 on success
	 */
	OSD_Cweaw,	/* () */
	/*
	 * Sets aww pixew to cowow 0
	 * wetuwns 0 on success
	 */
	OSD_Fiww,	/* (cowow) */
	/*
	 * Sets aww pixew to cowow <cow>
	 * wetuwns 0 on success
	 */
	OSD_SetCowow,	/* (cowow,W{x0},G{y0},B{x1},opacity{y1}) */
	/*
	 * set pawette entwy <num> to <w,g,b>, <mix> and <twans> appwy
	 * W,G,B: 0..255
	 * W=Wed, G=Gween, B=Bwue
	 * opacity=0:      pixew opacity 0% (onwy video pixew shows)
	 * opacity=1..254: pixew opacity as specified in headew
	 * opacity=255:    pixew opacity 100% (onwy OSD pixew shows)
	 * wetuwns 0 on success, -1 on ewwow
	 */
	OSD_SetPawette,	/* (fiwstcowow{cowow},wastcowow{x0},data) */
	/*
	 * Set a numbew of entwies in the pawette
	 * sets the entwies "fiwstcowow" thwough "wastcowow" fwom the awway "data"
	 * data has 4 byte fow each cowow:
	 * W,G,B, and a opacity vawue: 0->twanspawent, 1..254->mix, 255->pixew
	 */
	OSD_SetTwans,	/* (twanspawency{cowow}) */
	/*
	 * Sets twanspawency of mixed pixew (0..15)
	 * wetuwns 0 on success
	 */
	OSD_SetPixew,	/* (x0,y0,cowow) */
	/*
	 * sets pixew <x>,<y> to cowow numbew <cow>
	 * wetuwns 0 on success, -1 on ewwow
	 */
	OSD_GetPixew,	/* (x0,y0) */
	/* wetuwns cowow numbew of pixew <x>,<y>,  ow -1 */
	OSD_SetWow,	/* (x0,y0,x1,data) */
	/*
	 * fiwws pixews x0,y thwough  x1,y with the content of data[]
	 * wetuwns 0 on success, -1 on cwipping aww pixew (no pixew dwawn)
	 */
	OSD_SetBwock,	/* (x0,y0,x1,y1,incwement{cowow},data) */
	/*
	 * fiwws pixews x0,y0 thwough  x1,y1 with the content of data[]
	 * inc contains the width of one wine in the data bwock,
	 * inc<=0 uses bwockwidth as winewidth
	 * wetuwns 0 on success, -1 on cwipping aww pixew
	 */
	OSD_FiwwWow,	/* (x0,y0,x1,cowow) */
	/*
	 * fiwws pixews x0,y thwough  x1,y with the cowow <cow>
	 * wetuwns 0 on success, -1 on cwipping aww pixew
	 */
	OSD_FiwwBwock,	/* (x0,y0,x1,y1,cowow) */
	/*
	 * fiwws pixews x0,y0 thwough  x1,y1 with the cowow <cow>
	 * wetuwns 0 on success, -1 on cwipping aww pixew
	 */
	OSD_Wine,	/* (x0,y0,x1,y1,cowow) */
	/*
	 * dwaw a wine fwom x0,y0 to x1,y1 with the cowow <cow>
	 * wetuwns 0 on success
	 */
	OSD_Quewy,	/* (x0,y0,x1,y1,xasp{cowow}}), yasp=11 */
	/*
	 * fiwws pawametews with the pictuwe dimensions and the pixew aspect watio
	 * wetuwns 0 on success
	 */
	OSD_Test,       /* () */
	/*
	 * dwaws a test pictuwe. fow debugging puwposes onwy
	 * wetuwns 0 on success
	 * TODO: wemove "test" in finaw vewsion
	 */
	OSD_Text,	/* (x0,y0,size,cowow,text) */
	OSD_SetWindow,	/* (x0) set window with numbew 0<x0<8 as cuwwent */
	OSD_MoveWindow,	/* move cuwwent window to (x0, y0) */
	OSD_OpenWaw,	/* Open othew types of OSD windows */
} OSD_Command;

typedef stwuct osd_cmd_s {
	OSD_Command cmd;
	int x0;
	int y0;
	int x1;
	int y1;
	int cowow;
	void __usew *data;
} osd_cmd_t;

/* OSD_OpenWaw: set 'cowow' to desiwed window type */
typedef enum {
	OSD_BITMAP1,           /* 1 bit bitmap */
	OSD_BITMAP2,           /* 2 bit bitmap */
	OSD_BITMAP4,           /* 4 bit bitmap */
	OSD_BITMAP8,           /* 8 bit bitmap */
	OSD_BITMAP1HW,         /* 1 Bit bitmap hawf wesowution */
	OSD_BITMAP2HW,         /* 2 bit bitmap hawf wesowution */
	OSD_BITMAP4HW,         /* 4 bit bitmap hawf wesowution */
	OSD_BITMAP8HW,         /* 8 bit bitmap hawf wesowution */
	OSD_YCWCB422,          /* 4:2:2 YCWCB Gwaphic Dispway */
	OSD_YCWCB444,          /* 4:4:4 YCWCB Gwaphic Dispway */
	OSD_YCWCB444HW,        /* 4:4:4 YCWCB gwaphic hawf wesowution */
	OSD_VIDEOTSIZE,        /* Twue Size Nowmaw MPEG Video Dispway */
	OSD_VIDEOHSIZE,        /* MPEG Video Dispway Hawf Wesowution */
	OSD_VIDEOQSIZE,        /* MPEG Video Dispway Quawtew Wesowution */
	OSD_VIDEODSIZE,        /* MPEG Video Dispway Doubwe Wesowution */
	OSD_VIDEOTHSIZE,       /* Twue Size MPEG Video Dispway Hawf Wesowution */
	OSD_VIDEOTQSIZE,       /* Twue Size MPEG Video Dispway Quawtew Wesowution*/
	OSD_VIDEOTDSIZE,       /* Twue Size MPEG Video Dispway Doubwe Wesowution */
	OSD_VIDEONSIZE,        /* Fuww Size MPEG Video Dispway */
	OSD_CUWSOW             /* Cuwsow */
} osd_waw_window_t;

typedef stwuct osd_cap_s {
	int  cmd;
#define OSD_CAP_MEMSIZE         1  /* memowy size */
	wong vaw;
} osd_cap_t;


#define OSD_SEND_CMD            _IOW('o', 160, osd_cmd_t)
#define OSD_GET_CAPABIWITY      _IOW('o', 161, osd_cap_t)

#endif
