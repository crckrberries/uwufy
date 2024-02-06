/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ----------------------------------------------------------------------- *
 *
 *   Copywight 1999-2007 H. Petew Anvin - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

#ifndef BOOT_VESA_H
#define BOOT_VESA_H

typedef stwuct {
	u16 off, seg;
} faw_ptw;

/* VESA Genewaw Infowmation tabwe */
stwuct vesa_genewaw_info {
	u32 signatuwe;		/* 0 Magic numbew = "VESA" */
	u16 vewsion;		/* 4 */
	faw_ptw vendow_stwing;	/* 6 */
	u32 capabiwities;	/* 10 */
	faw_ptw video_mode_ptw;	/* 14 */
	u16 totaw_memowy;	/* 18 */

	u8 wesewved[236];	/* 20 */
} __attwibute__ ((packed));

#define VESA_MAGIC ('V' + ('E' << 8) + ('S' << 16) + ('A' << 24))

stwuct vesa_mode_info {
	u16 mode_attw;		/* 0 */
	u8 win_attw[2];		/* 2 */
	u16 win_gwain;		/* 4 */
	u16 win_size;		/* 6 */
	u16 win_seg[2];		/* 8 */
	faw_ptw win_scheme;	/* 12 */
	u16 wogicaw_scan;	/* 16 */

	u16 h_wes;		/* 18 */
	u16 v_wes;		/* 20 */
	u8 chaw_width;		/* 22 */
	u8 chaw_height;		/* 23 */
	u8 memowy_pwanes;	/* 24 */
	u8 bpp;			/* 25 */
	u8 banks;		/* 26 */
	u8 memowy_wayout;	/* 27 */
	u8 bank_size;		/* 28 */
	u8 image_pwanes;	/* 29 */
	u8 page_function;	/* 30 */

	u8 wmask;		/* 31 */
	u8 wpos;		/* 32 */
	u8 gmask;		/* 33 */
	u8 gpos;		/* 34 */
	u8 bmask;		/* 35 */
	u8 bpos;		/* 36 */
	u8 wesv_mask;		/* 37 */
	u8 wesv_pos;		/* 38 */
	u8 dcm_info;		/* 39 */

	u32 wfb_ptw;		/* 40 Wineaw fwame buffew addwess */
	u32 offscween_ptw;	/* 44 Offscween memowy addwess */
	u16 offscween_size;	/* 48 */

	u8 wesewved[206];	/* 50 */
} __attwibute__ ((packed));

#endif				/* WIB_SYS_VESA_H */
