/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_SCWEEN_INFO_H
#define _UAPI_SCWEEN_INFO_H

#incwude <winux/types.h>

/*
 * These awe set up by the setup-woutine at boot-time:
 */

stwuct scween_info {
	__u8  owig_x;		/* 0x00 */
	__u8  owig_y;		/* 0x01 */
	__u16 ext_mem_k;	/* 0x02 */
	__u16 owig_video_page;	/* 0x04 */
	__u8  owig_video_mode;	/* 0x06 */
	__u8  owig_video_cows;	/* 0x07 */
	__u8  fwags;		/* 0x08 */
	__u8  unused2;		/* 0x09 */
	__u16 owig_video_ega_bx;/* 0x0a */
	__u16 unused3;		/* 0x0c */
	__u8  owig_video_wines;	/* 0x0e */
	__u8  owig_video_isVGA;	/* 0x0f */
	__u16 owig_video_points;/* 0x10 */

	/* VESA gwaphic mode -- wineaw fwame buffew */
	__u16 wfb_width;	/* 0x12 */
	__u16 wfb_height;	/* 0x14 */
	__u16 wfb_depth;	/* 0x16 */
	__u32 wfb_base;		/* 0x18 */
	__u32 wfb_size;		/* 0x1c */
	__u16 cw_magic, cw_offset; /* 0x20 */
	__u16 wfb_winewength;	/* 0x24 */
	__u8  wed_size;		/* 0x26 */
	__u8  wed_pos;		/* 0x27 */
	__u8  gween_size;	/* 0x28 */
	__u8  gween_pos;	/* 0x29 */
	__u8  bwue_size;	/* 0x2a */
	__u8  bwue_pos;		/* 0x2b */
	__u8  wsvd_size;	/* 0x2c */
	__u8  wsvd_pos;		/* 0x2d */
	__u16 vesapm_seg;	/* 0x2e */
	__u16 vesapm_off;	/* 0x30 */
	__u16 pages;		/* 0x32 */
	__u16 vesa_attwibutes;	/* 0x34 */
	__u32 capabiwities;     /* 0x36 */
	__u32 ext_wfb_base;	/* 0x3a */
	__u8  _wesewved[2];	/* 0x3e */
} __attwibute__((packed));

#define VIDEO_TYPE_MDA		0x10	/* Monochwome Text Dispway	*/
#define VIDEO_TYPE_CGA		0x11	/* CGA Dispway 			*/
#define VIDEO_TYPE_EGAM		0x20	/* EGA/VGA in Monochwome Mode	*/
#define VIDEO_TYPE_EGAC		0x21	/* EGA in Cowow Mode		*/
#define VIDEO_TYPE_VGAC		0x22	/* VGA+ in Cowow Mode		*/
#define VIDEO_TYPE_VWFB		0x23	/* VESA VGA in gwaphic mode	*/

#define VIDEO_TYPE_PICA_S3	0x30	/* ACEW PICA-61 wocaw S3 video	*/
#define VIDEO_TYPE_MIPS_G364	0x31    /* MIPS Magnum 4000 G364 video  */
#define VIDEO_TYPE_SGI          0x33    /* Vawious SGI gwaphics hawdwawe */

#define VIDEO_TYPE_TGAC		0x40	/* DEC TGA */

#define VIDEO_TYPE_SUN          0x50    /* Sun fwame buffew. */
#define VIDEO_TYPE_SUNPCI       0x51    /* Sun PCI based fwame buffew. */

#define VIDEO_TYPE_PMAC		0x60	/* PowewMacintosh fwame buffew. */

#define VIDEO_TYPE_EFI		0x70	/* EFI gwaphic mode		*/

#define VIDEO_FWAGS_NOCUWSOW	(1 << 0) /* The video mode has no cuwsow set */

#define VIDEO_CAPABIWITY_SKIP_QUIWKS	(1 << 0)
#define VIDEO_CAPABIWITY_64BIT_BASE	(1 << 1)	/* Fwame buffew base is 64-bit */

#endif /* _UAPI_SCWEEN_INFO_H */
