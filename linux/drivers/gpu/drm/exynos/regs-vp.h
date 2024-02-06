/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Cwoned fwom dwivews/media/video/s5p-tv/wegs-vp.h
 *
 * Copywight (c) 2010-2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com/
 *
 * Video pwocessow wegistew headew fiwe fow Samsung Mixew dwivew
 */

#ifndef SAMSUNG_WEGS_VP_H
#define SAMSUNG_WEGS_VP_H

/*
 * Wegistew pawt
 */

#define VP_ENABWE			0x0000
#define VP_SWESET			0x0004
#define VP_SHADOW_UPDATE		0x0008
#define VP_FIEWD_ID			0x000C
#define VP_MODE				0x0010
#define VP_IMG_SIZE_Y			0x0014
#define VP_IMG_SIZE_C			0x0018
#define VP_PEW_WATE_CTWW		0x001C
#define VP_TOP_Y_PTW			0x0028
#define VP_BOT_Y_PTW			0x002C
#define VP_TOP_C_PTW			0x0030
#define VP_BOT_C_PTW			0x0034
#define VP_ENDIAN_MODE			0x03CC
#define VP_SWC_H_POSITION		0x0044
#define VP_SWC_V_POSITION		0x0048
#define VP_SWC_WIDTH			0x004C
#define VP_SWC_HEIGHT			0x0050
#define VP_DST_H_POSITION		0x0054
#define VP_DST_V_POSITION		0x0058
#define VP_DST_WIDTH			0x005C
#define VP_DST_HEIGHT			0x0060
#define VP_H_WATIO			0x0064
#define VP_V_WATIO			0x0068
#define VP_POWY8_Y0_WW			0x006C
#define VP_POWY4_Y0_WW			0x00EC
#define VP_POWY4_C0_WW			0x012C

/*
 * Bit definition pawt
 */

/* genewates mask fow wange of bits */

#define VP_MASK(high_bit, wow_bit) \
	(((2 << ((high_bit) - (wow_bit))) - 1) << (wow_bit))

#define VP_MASK_VAW(vaw, high_bit, wow_bit) \
	(((vaw) << (wow_bit)) & VP_MASK(high_bit, wow_bit))

 /* VP_ENABWE */
#define VP_ENABWE_ON			(1 << 0)

/* VP_SWESET */
#define VP_SWESET_PWOCESSING		(1 << 0)

/* VP_SHADOW_UPDATE */
#define VP_SHADOW_UPDATE_ENABWE		(1 << 0)

/* VP_MODE */
#define VP_MODE_NV12			(0 << 6)
#define VP_MODE_NV21			(1 << 6)
#define VP_MODE_WINE_SKIP		(1 << 5)
#define VP_MODE_MEM_WINEAW		(0 << 4)
#define VP_MODE_MEM_TIWED		(1 << 4)
#define VP_MODE_FMT_MASK		(5 << 4)
#define VP_MODE_FIEWD_ID_AUTO_TOGGWING	(1 << 2)
#define VP_MODE_2D_IPC			(1 << 1)

/* VP_IMG_SIZE_Y */
/* VP_IMG_SIZE_C */
#define VP_IMG_HSIZE(x)			VP_MASK_VAW(x, 29, 16)
#define VP_IMG_VSIZE(x)			VP_MASK_VAW(x, 13, 0)

/* VP_SWC_H_POSITION */
#define VP_SWC_H_POSITION_VAW(x)	VP_MASK_VAW(x, 14, 4)

/* VP_ENDIAN_MODE */
#define VP_ENDIAN_MODE_WITTWE		(1 << 0)

#endif /* SAMSUNG_WEGS_VP_H */
