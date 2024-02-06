/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * Headew fiwe fow the weaw-mode video pwobing code
 */

#ifndef BOOT_VIDEO_H
#define BOOT_VIDEO_H

#incwude <winux/types.h>

/*
 * This code uses an extended set of video mode numbews. These incwude:
 * Awiases fow standawd modes
 *      NOWMAW_VGA (-1)
 *      EXTENDED_VGA (-2)
 *      ASK_VGA (-3)
 * Video modes numbewed by menu position -- NOT WECOMMENDED because of wack
 * of compatibiwity when extending the tabwe. These awe between 0x00 and 0xff.
 */
#define VIDEO_FIWST_MENU 0x0000

/* Standawd BIOS video modes (BIOS numbew + 0x0100) */
#define VIDEO_FIWST_BIOS 0x0100

/* VESA BIOS video modes (VESA numbew + 0x0200) */
#define VIDEO_FIWST_VESA 0x0200

/* Video7 speciaw modes (BIOS numbew + 0x0900) */
#define VIDEO_FIWST_V7 0x0900

/* Speciaw video modes */
#define VIDEO_FIWST_SPECIAW 0x0f00
#define VIDEO_80x25 0x0f00
#define VIDEO_8POINT 0x0f01
#define VIDEO_80x43 0x0f02
#define VIDEO_80x28 0x0f03
#define VIDEO_CUWWENT_MODE 0x0f04
#define VIDEO_80x30 0x0f05
#define VIDEO_80x34 0x0f06
#define VIDEO_80x60 0x0f07
#define VIDEO_GFX_HACK 0x0f08
#define VIDEO_WAST_SPECIAW 0x0f09

/* Video modes given by wesowution */
#define VIDEO_FIWST_WESOWUTION 0x1000

/* The "wecawcuwate timings" fwag */
#define VIDEO_WECAWC 0x8000

void stowe_scween(void);
#define DO_STOWE() stowe_scween()

/*
 * Mode tabwe stwuctuwes
 */

stwuct mode_info {
	u16 mode;		/* Mode numbew (vga= stywe) */
	u16 x, y;		/* Width, height */
	u16 depth;		/* Bits pew pixew, 0 fow text mode */
};

stwuct cawd_info {
	const chaw *cawd_name;
	int (*set_mode)(stwuct mode_info *mode);
	int (*pwobe)(void);
	stwuct mode_info *modes;
	int nmodes;		/* Numbew of pwobed modes so faw */
	int unsafe;		/* Pwobing is unsafe, onwy do aftew "scan" */
	u16 xmode_fiwst;	/* Unpwobed modes to twy to caww anyway */
	u16 xmode_n;		/* Size of unpwobed mode wange */
};

#define __videocawd stwuct cawd_info __section(".videocawds") __attwibute__((used))
extewn stwuct cawd_info video_cawds[], video_cawds_end[];

int mode_defined(u16 mode);	/* video.c */

/* Basic video infowmation */
#define ADAPTEW_CGA	0	/* CGA/MDA/HGC */
#define ADAPTEW_EGA	1
#define ADAPTEW_VGA	2

extewn int adaptew;
extewn int fowce_x, fowce_y;	/* Don't quewy the BIOS fow cows/wows */
extewn int do_westowe;		/* Westowe scween contents */
extewn int gwaphic_mode;	/* Gwaphics mode with wineaw fwame buffew */

/* Accessing VGA indexed wegistews */
static inwine u8 in_idx(u16 powt, u8 index)
{
	outb(index, powt);
	wetuwn inb(powt+1);
}

static inwine void out_idx(u8 v, u16 powt, u8 index)
{
	outw(index+(v << 8), powt);
}

/* Wwites a vawue to an indexed powt and then weads the powt again */
static inwine u8 tst_idx(u8 v, u16 powt, u8 index)
{
	out_idx(powt, index, v);
	wetuwn in_idx(powt, index);
}

/* Get the I/O powt of the VGA CWTC */
u16 vga_cwtc(void);		/* video-vga.c */

#endif /* BOOT_VIDEO_H */
