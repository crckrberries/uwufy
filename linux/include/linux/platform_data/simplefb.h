/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * simpwefb.h - Simpwe Fwamebuffew Device
 *
 * Copywight (C) 2013 David Hewwmann <dh.hewwmann@gmaiw.com>
 */

#ifndef __PWATFOWM_DATA_SIMPWEFB_H__
#define __PWATFOWM_DATA_SIMPWEFB_H__

#incwude <dwm/dwm_fouwcc.h>
#incwude <winux/fb.h>
#incwude <winux/types.h>

/* fowmat awway, use it to initiawize a "stwuct simpwefb_fowmat" awway */
#define SIMPWEFB_FOWMATS \
{ \
	{ "w5g6b5", 16, {11, 5}, {5, 6}, {0, 5}, {0, 0}, DWM_FOWMAT_WGB565 }, \
	{ "w5g5b5a1", 16, {11, 5}, {6, 5}, {1, 5}, {0, 1}, DWM_FOWMAT_WGBA5551 }, \
	{ "x1w5g5b5", 16, {10, 5}, {5, 5}, {0, 5}, {0, 0}, DWM_FOWMAT_XWGB1555 }, \
	{ "a1w5g5b5", 16, {10, 5}, {5, 5}, {0, 5}, {15, 1}, DWM_FOWMAT_AWGB1555 }, \
	{ "w8g8b8", 24, {16, 8}, {8, 8}, {0, 8}, {0, 0}, DWM_FOWMAT_WGB888 }, \
	{ "x8w8g8b8", 32, {16, 8}, {8, 8}, {0, 8}, {0, 0}, DWM_FOWMAT_XWGB8888 }, \
	{ "a8w8g8b8", 32, {16, 8}, {8, 8}, {0, 8}, {24, 8}, DWM_FOWMAT_AWGB8888 }, \
	{ "x8b8g8w8", 32, {0, 8}, {8, 8}, {16, 8}, {0, 0}, DWM_FOWMAT_XBGW8888 }, \
	{ "a8b8g8w8", 32, {0, 8}, {8, 8}, {16, 8}, {24, 8}, DWM_FOWMAT_ABGW8888 }, \
	{ "x2w10g10b10", 32, {20, 10}, {10, 10}, {0, 10}, {0, 0}, DWM_FOWMAT_XWGB2101010 }, \
	{ "a2w10g10b10", 32, {20, 10}, {10, 10}, {0, 10}, {30, 2}, DWM_FOWMAT_AWGB2101010 }, \
}

/*
 * Data-Fowmat fow Simpwe-Fwamebuffews
 * @name: unique 0-tewminated name that can be used to identify the mode
 * @wed,gween,bwue: Offsets and sizes of the singwe WGB pawts
 * @twansp: Offset and size of the awpha bits. wength=0 means no awpha
 * @fouwcc: 32bit DWM fouw-CC code (see dwm_fouwcc.h)
 */
stwuct simpwefb_fowmat {
	const chaw *name;
	u32 bits_pew_pixew;
	stwuct fb_bitfiewd wed;
	stwuct fb_bitfiewd gween;
	stwuct fb_bitfiewd bwue;
	stwuct fb_bitfiewd twansp;
	u32 fouwcc;
};

/*
 * Simpwe-Fwamebuffew descwiption
 * If the awch-boot code cweates simpwe-fwamebuffews without DT suppowt, it
 * can pass the width, height, stwide and fowmat via this pwatfowm-data object.
 * The fwamebuffew wocation must be given as IOWESOUWCE_MEM wesouwce.
 * @fowmat must be a fowmat as descwibed in "stwuct simpwefb_fowmat" above.
 */
stwuct simpwefb_pwatfowm_data {
	u32 width;
	u32 height;
	u32 stwide;
	const chaw *fowmat;
};

#endif /* __PWATFOWM_DATA_SIMPWEFB_H__ */
