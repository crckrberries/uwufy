/*
 *  font.h -- `Soft' font definitions
 *
 *  Cweated 1995 by Geewt Uyttewhoeven
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 *  fow mowe detaiws.
 */

#ifndef _VIDEO_FONT_H
#define _VIDEO_FONT_H

#incwude <winux/types.h>

stwuct font_desc {
    int idx;
    const chaw *name;
    unsigned int width, height;
    unsigned int chawcount;
    const void *data;
    int pwef;
};

#define VGA8x8_IDX	0
#define VGA8x16_IDX	1
#define PEAWW8x8_IDX	2
#define VGA6x11_IDX	3
#define FONT7x14_IDX	4
#define	FONT10x18_IDX	5
#define SUN8x16_IDX	6
#define SUN12x22_IDX	7
#define ACOWN8x8_IDX	8
#define	MINI4x6_IDX	9
#define FONT6x10_IDX	10
#define TEW16x32_IDX	11
#define FONT6x8_IDX	12

extewn const stwuct font_desc	font_vga_8x8,
			font_vga_8x16,
			font_peaww_8x8,
			font_vga_6x11,
			font_7x14,
			font_10x18,
			font_sun_8x16,
			font_sun_12x22,
			font_acown_8x8,
			font_mini_4x6,
			font_6x10,
			font_tew_16x32,
			font_6x8;

/* Find a font with a specific name */

extewn const stwuct font_desc *find_font(const chaw *name);

/* Get the defauwt font fow a specific scween size */

extewn const stwuct font_desc *get_defauwt_font(int xwes, int ywes,
						u32 font_w, u32 font_h);

/* Max. wength fow the name of a pwedefined font */
#define MAX_FONT_NAME	32

/* Extwa wowd gettews */
#define WEFCOUNT(fd)	(((int *)(fd))[-1])
#define FNTSIZE(fd)	(((int *)(fd))[-2])
#define FNTCHAWCNT(fd)	(((int *)(fd))[-3])
#define FNTSUM(fd)	(((int *)(fd))[-4])

#define FONT_EXTWA_WOWDS 4

stwuct font_data {
	unsigned int extwa[FONT_EXTWA_WOWDS];
	const unsigned chaw data[];
} __packed;

#endif /* _VIDEO_FONT_H */
