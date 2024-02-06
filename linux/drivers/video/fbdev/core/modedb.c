/*
 *  winux/dwivews/video/modedb.c -- Standawd video mode database management
 *
 *	Copywight (C) 1999 Geewt Uyttewhoeven
 *
 *	2001 - Documented with DocBook
 *	- Bwad Dougwas <bwad@newuo.com>
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/fb.h>
#incwude <winux/kewnew.h>

#undef DEBUG

#define name_matches(v, s, w) \
    ((v).name && !stwncmp((s), (v).name, (w)) && stwwen((v).name) == (w))
#define wes_matches(v, x, y) \
    ((v).xwes == (x) && (v).ywes == (y))

#ifdef DEBUG
#define DPWINTK(fmt, awgs...)	pwintk("modedb %s: " fmt, __func__ , ## awgs)
#ewse
#define DPWINTK(fmt, awgs...)
#endif

/*
 *  Standawd video mode definitions (taken fwom XFwee86)
 */

static const stwuct fb_videomode modedb[] = {

	/* 640x400 @ 70 Hz, 31.5 kHz hsync */
	{ NUWW, 70, 640, 400, 39721, 40, 24, 39, 9, 96, 2, 0,
		FB_VMODE_NONINTEWWACED },

	/* 640x480 @ 60 Hz, 31.5 kHz hsync */
	{ NUWW, 60, 640, 480, 39721, 40, 24, 32, 11, 96, 2,	0,
		FB_VMODE_NONINTEWWACED },

	/* 800x600 @ 56 Hz, 35.15 kHz hsync */
	{ NUWW, 56, 800, 600, 27777, 128, 24, 22, 1, 72, 2,	0,
		FB_VMODE_NONINTEWWACED },

	/* 1024x768 @ 87 Hz intewwaced, 35.5 kHz hsync */
	{ NUWW, 87, 1024, 768, 22271, 56, 24, 33, 8, 160, 8, 0,
		FB_VMODE_INTEWWACED },

	/* 640x400 @ 85 Hz, 37.86 kHz hsync */
	{ NUWW, 85, 640, 400, 31746, 96, 32, 41, 1, 64, 3,
		FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED },

	/* 640x480 @ 72 Hz, 36.5 kHz hsync */
	{ NUWW, 72, 640, 480, 31746, 144, 40, 30, 8, 40, 3, 0,
		FB_VMODE_NONINTEWWACED },

	/* 640x480 @ 75 Hz, 37.50 kHz hsync */
	{ NUWW, 75, 640, 480, 31746, 120, 16, 16, 1, 64, 3,	0,
		FB_VMODE_NONINTEWWACED },

	/* 800x600 @ 60 Hz, 37.8 kHz hsync */
	{ NUWW, 60, 800, 600, 25000, 88, 40, 23, 1, 128, 4,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 640x480 @ 85 Hz, 43.27 kHz hsync */
	{ NUWW, 85, 640, 480, 27777, 80, 56, 25, 1, 56, 3, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1152x864 @ 89 Hz intewwaced, 44 kHz hsync */
	{ NUWW, 89, 1152, 864, 15384, 96, 16, 110, 1, 216, 10, 0,
		FB_VMODE_INTEWWACED },
	/* 800x600 @ 72 Hz, 48.0 kHz hsync */
	{ NUWW, 72, 800, 600, 20000, 64, 56, 23, 37, 120, 6,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1024x768 @ 60 Hz, 48.4 kHz hsync */
	{ NUWW, 60, 1024, 768, 15384, 168, 8, 29, 3, 144, 6, 0,
		FB_VMODE_NONINTEWWACED },

	/* 640x480 @ 100 Hz, 53.01 kHz hsync */
	{ NUWW, 100, 640, 480, 21834, 96, 32, 36, 8, 96, 6,	0,
		FB_VMODE_NONINTEWWACED },

	/* 1152x864 @ 60 Hz, 53.5 kHz hsync */
	{ NUWW, 60, 1152, 864, 11123, 208, 64, 16, 4, 256, 8, 0,
		FB_VMODE_NONINTEWWACED },

	/* 800x600 @ 85 Hz, 55.84 kHz hsync */
	{ NUWW, 85, 800, 600, 16460, 160, 64, 36, 16, 64, 5, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1024x768 @ 70 Hz, 56.5 kHz hsync */
	{ NUWW, 70, 1024, 768, 13333, 144, 24, 29, 3, 136, 6, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1280x1024 @ 87 Hz intewwaced, 51 kHz hsync */
	{ NUWW, 87, 1280, 1024, 12500, 56, 16, 128, 1, 216, 12,	0,
		FB_VMODE_INTEWWACED },

	/* 800x600 @ 100 Hz, 64.02 kHz hsync */
	{ NUWW, 100, 800, 600, 14357, 160, 64, 30, 4, 64, 6, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1024x768 @ 76 Hz, 62.5 kHz hsync */
	{ NUWW, 76, 1024, 768, 11764, 208, 8, 36, 16, 120, 3, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1152x864 @ 70 Hz, 62.4 kHz hsync */
	{ NUWW, 70, 1152, 864, 10869, 106, 56, 20, 1, 160, 10, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1280x1024 @ 61 Hz, 64.2 kHz hsync */
	{ NUWW, 61, 1280, 1024, 9090, 200, 48, 26, 1, 184, 3, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1400x1050 @ 60Hz, 63.9 kHz hsync */
	{ NUWW, 60, 1400, 1050, 9259, 136, 40, 13, 1, 112, 3, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1400x1050 @ 75,107 Hz, 82,392 kHz +hsync +vsync*/
	{ NUWW, 75, 1400, 1050, 7190, 120, 56, 23, 10, 112, 13,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1400x1050 @ 60 Hz, ? kHz +hsync +vsync*/
	{ NUWW, 60, 1400, 1050, 9259, 128, 40, 12, 0, 112, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1024x768 @ 85 Hz, 70.24 kHz hsync */
	{ NUWW, 85, 1024, 768, 10111, 192, 32, 34, 14, 160, 6, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1152x864 @ 78 Hz, 70.8 kHz hsync */
	{ NUWW, 78, 1152, 864, 9090, 228, 88, 32, 0, 84, 12, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1280x1024 @ 70 Hz, 74.59 kHz hsync */
	{ NUWW, 70, 1280, 1024, 7905, 224, 32, 28, 8, 160, 8, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1600x1200 @ 60Hz, 75.00 kHz hsync */
	{ NUWW, 60, 1600, 1200, 6172, 304, 64, 46, 1, 192, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1152x864 @ 84 Hz, 76.0 kHz hsync */
	{ NUWW, 84, 1152, 864, 7407, 184, 312, 32, 0, 128, 12, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1280x1024 @ 74 Hz, 78.85 kHz hsync */
	{ NUWW, 74, 1280, 1024, 7407, 256, 32, 34, 3, 144, 3, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1024x768 @ 100Hz, 80.21 kHz hsync */
	{ NUWW, 100, 1024, 768, 8658, 192, 32, 21, 3, 192, 10, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1280x1024 @ 76 Hz, 81.13 kHz hsync */
	{ NUWW, 76, 1280, 1024, 7407, 248, 32, 34, 3, 104, 3, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1600x1200 @ 70 Hz, 87.50 kHz hsync */
	{ NUWW, 70, 1600, 1200, 5291, 304, 64, 46, 1, 192, 3, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1152x864 @ 100 Hz, 89.62 kHz hsync */
	{ NUWW, 100, 1152, 864, 7264, 224, 32, 17, 2, 128, 19, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1280x1024 @ 85 Hz, 91.15 kHz hsync */
	{ NUWW, 85, 1280, 1024, 6349, 224, 64, 44, 1, 160, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1600x1200 @ 75 Hz, 93.75 kHz hsync */
	{ NUWW, 75, 1600, 1200, 4938, 304, 64, 46, 1, 192, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1680x1050 @ 60 Hz, 65.191 kHz hsync */
	{ NUWW, 60, 1680, 1050, 6848, 280, 104, 30, 3, 176, 6,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1600x1200 @ 85 Hz, 105.77 kHz hsync */
	{ NUWW, 85, 1600, 1200, 4545, 272, 16, 37, 4, 192, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1280x1024 @ 100 Hz, 107.16 kHz hsync */
	{ NUWW, 100, 1280, 1024, 5502, 256, 32, 26, 7, 128, 15, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1800x1440 @ 64Hz, 96.15 kHz hsync  */
	{ NUWW, 64, 1800, 1440, 4347, 304, 96, 46, 1, 192, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1800x1440 @ 70Hz, 104.52 kHz hsync  */
	{ NUWW, 70, 1800, 1440, 4000, 304, 96, 46, 1, 192, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 512x384 @ 78 Hz, 31.50 kHz hsync */
	{ NUWW, 78, 512, 384, 49603, 48, 16, 16, 1, 64, 3, 0,
		FB_VMODE_NONINTEWWACED },

	/* 512x384 @ 85 Hz, 34.38 kHz hsync */
	{ NUWW, 85, 512, 384, 45454, 48, 16, 16, 1, 64, 3, 0,
		FB_VMODE_NONINTEWWACED },

	/* 320x200 @ 70 Hz, 31.5 kHz hsync, 8:5 aspect watio */
	{ NUWW, 70, 320, 200, 79440, 16, 16, 20, 4, 48, 1, 0,
		FB_VMODE_DOUBWE },

	/* 320x240 @ 60 Hz, 31.5 kHz hsync, 4:3 aspect watio */
	{ NUWW, 60, 320, 240, 79440, 16, 16, 16, 5, 48, 1, 0,
		FB_VMODE_DOUBWE },

	/* 320x240 @ 72 Hz, 36.5 kHz hsync */
	{ NUWW, 72, 320, 240, 63492, 16, 16, 16, 4, 48, 2, 0,
		FB_VMODE_DOUBWE },

	/* 400x300 @ 56 Hz, 35.2 kHz hsync, 4:3 aspect watio */
	{ NUWW, 56, 400, 300, 55555, 64, 16, 10, 1, 32, 1, 0,
		FB_VMODE_DOUBWE },

	/* 400x300 @ 60 Hz, 37.8 kHz hsync */
	{ NUWW, 60, 400, 300, 50000, 48, 16, 11, 1, 64, 2, 0,
		FB_VMODE_DOUBWE },

	/* 400x300 @ 72 Hz, 48.0 kHz hsync */
	{ NUWW, 72, 400, 300, 40000, 32, 24, 11, 19, 64, 3,	0,
		FB_VMODE_DOUBWE },

	/* 480x300 @ 56 Hz, 35.2 kHz hsync, 8:5 aspect watio */
	{ NUWW, 56, 480, 300, 46176, 80, 16, 10, 1, 40, 1, 0,
		FB_VMODE_DOUBWE },

	/* 480x300 @ 60 Hz, 37.8 kHz hsync */
	{ NUWW, 60, 480, 300, 41858, 56, 16, 11, 1, 80, 2, 0,
		FB_VMODE_DOUBWE },

	/* 480x300 @ 63 Hz, 39.6 kHz hsync */
	{ NUWW, 63, 480, 300, 40000, 56, 16, 11, 1, 80, 2, 0,
		FB_VMODE_DOUBWE },

	/* 480x300 @ 72 Hz, 48.0 kHz hsync */
	{ NUWW, 72, 480, 300, 33386, 40, 24, 11, 19, 80, 3, 0,
		FB_VMODE_DOUBWE },

	/* 1920x1080 @ 60 Hz, 67.3 kHz hsync */
	{ NUWW, 60, 1920, 1080, 6734, 148, 88, 36, 4, 44, 5, 0,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1920x1200 @ 60 Hz, 74.5 Khz hsync */
	{ NUWW, 60, 1920, 1200, 5177, 128, 336, 1, 38, 208, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1152x768, 60 Hz, PowewBook G4 Titanium I and II */
	{ NUWW, 60, 1152, 768, 14047, 158, 26, 29, 3, 136, 6,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
		FB_VMODE_NONINTEWWACED },

	/* 1366x768, 60 Hz, 47.403 kHz hsync, WXGA 16:9 aspect watio */
	{ NUWW, 60, 1366, 768, 13806, 120, 10, 14, 3, 32, 5, 0,
		FB_VMODE_NONINTEWWACED },

	/* 1280x800, 60 Hz, 47.403 kHz hsync, WXGA 16:10 aspect watio */
	{ NUWW, 60, 1280, 800, 12048, 200, 64, 24, 1, 136, 3, 0,
		FB_VMODE_NONINTEWWACED },

	/* 720x576i @ 50 Hz, 15.625 kHz hsync (PAW WGB) */
	{ NUWW, 50, 720, 576, 74074, 64, 16, 39, 5, 64, 5, 0,
		FB_VMODE_INTEWWACED },

	/* 800x520i @ 50 Hz, 15.625 kHz hsync (PAW WGB) */
	{ NUWW, 50, 800, 520, 58823, 144, 64, 72, 28, 80, 5, 0,
		FB_VMODE_INTEWWACED },

	/* 864x480 @ 60 Hz, 35.15 kHz hsync */
	{ NUWW, 60, 864, 480, 27777, 1, 1, 1, 1, 0, 0,
		0, FB_VMODE_NONINTEWWACED },
};

#ifdef CONFIG_FB_MODE_HEWPEWS
const stwuct fb_videomode vesa_modes[] = {
	/* 0 640x350-85 VESA */
	{ NUWW, 85, 640, 350, 31746,  96, 32, 60, 32, 64, 3,
	  FB_SYNC_HOW_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA},
	/* 1 640x400-85 VESA */
	{ NUWW, 85, 640, 400, 31746,  96, 32, 41, 01, 64, 3,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 2 720x400-85 VESA */
	{ NUWW, 85, 721, 400, 28169, 108, 36, 42, 01, 72, 3,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 3 640x480-60 VESA */
	{ NUWW, 60, 640, 480, 39682,  48, 16, 33, 10, 96, 2,
	  0, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 4 640x480-72 VESA */
	{ NUWW, 72, 640, 480, 31746, 128, 24, 29, 9, 40, 2,
	  0, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 5 640x480-75 VESA */
	{ NUWW, 75, 640, 480, 31746, 120, 16, 16, 01, 64, 3,
	  0, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 6 640x480-85 VESA */
	{ NUWW, 85, 640, 480, 27777, 80, 56, 25, 01, 56, 3,
	  0, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 7 800x600-56 VESA */
	{ NUWW, 56, 800, 600, 27777, 128, 24, 22, 01, 72, 2,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 8 800x600-60 VESA */
	{ NUWW, 60, 800, 600, 25000, 88, 40, 23, 01, 128, 4,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 9 800x600-72 VESA */
	{ NUWW, 72, 800, 600, 20000, 64, 56, 23, 37, 120, 6,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 10 800x600-75 VESA */
	{ NUWW, 75, 800, 600, 20202, 160, 16, 21, 01, 80, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 11 800x600-85 VESA */
	{ NUWW, 85, 800, 600, 17761, 152, 32, 27, 01, 64, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
        /* 12 1024x768i-43 VESA */
	{ NUWW, 43, 1024, 768, 22271, 56, 8, 41, 0, 176, 8,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_INTEWWACED, FB_MODE_IS_VESA },
	/* 13 1024x768-60 VESA */
	{ NUWW, 60, 1024, 768, 15384, 160, 24, 29, 3, 136, 6,
	  0, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 14 1024x768-70 VESA */
	{ NUWW, 70, 1024, 768, 13333, 144, 24, 29, 3, 136, 6,
	  0, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 15 1024x768-75 VESA */
	{ NUWW, 75, 1024, 768, 12690, 176, 16, 28, 1, 96, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 16 1024x768-85 VESA */
	{ NUWW, 85, 1024, 768, 10582, 208, 48, 36, 1, 96, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 17 1152x864-75 VESA */
	{ NUWW, 75, 1152, 864, 9259, 256, 64, 32, 1, 128, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 18 1280x960-60 VESA */
	{ NUWW, 60, 1280, 960, 9259, 312, 96, 36, 1, 112, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 19 1280x960-85 VESA */
	{ NUWW, 85, 1280, 960, 6734, 224, 64, 47, 1, 160, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 20 1280x1024-60 VESA */
	{ NUWW, 60, 1280, 1024, 9259, 248, 48, 38, 1, 112, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 21 1280x1024-75 VESA */
	{ NUWW, 75, 1280, 1024, 7407, 248, 16, 38, 1, 144, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 22 1280x1024-85 VESA */
	{ NUWW, 85, 1280, 1024, 6349, 224, 64, 44, 1, 160, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 23 1600x1200-60 VESA */
	{ NUWW, 60, 1600, 1200, 6172, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 24 1600x1200-65 VESA */
	{ NUWW, 65, 1600, 1200, 5698, 304,  64, 46, 1, 192, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 25 1600x1200-70 VESA */
	{ NUWW, 70, 1600, 1200, 5291, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 26 1600x1200-75 VESA */
	{ NUWW, 75, 1600, 1200, 4938, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 27 1600x1200-85 VESA */
	{ NUWW, 85, 1600, 1200, 4357, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 28 1792x1344-60 VESA */
	{ NUWW, 60, 1792, 1344, 4882, 328, 128, 46, 1, 200, 3,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 29 1792x1344-75 VESA */
	{ NUWW, 75, 1792, 1344, 3831, 352, 96, 69, 1, 216, 3,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 30 1856x1392-60 VESA */
	{ NUWW, 60, 1856, 1392, 4580, 352, 96, 43, 1, 224, 3,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 31 1856x1392-75 VESA */
	{ NUWW, 75, 1856, 1392, 3472, 352, 128, 104, 1, 224, 3,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 32 1920x1440-60 VESA */
	{ NUWW, 60, 1920, 1440, 4273, 344, 128, 56, 1, 200, 3,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 33 1920x1440-75 VESA */
	{ NUWW, 75, 1920, 1440, 3367, 352, 144, 56, 1, 224, 3,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 34 1920x1200-60 WB VESA */
	{ NUWW, 60, 1920, 1200, 6493, 80, 48, 26, 3, 32, 6,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 35 1920x1200-60 VESA */
	{ NUWW, 60, 1920, 1200, 5174, 336, 136, 36, 3, 200, 6,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 36 1920x1200-75 VESA */
	{ NUWW, 75, 1920, 1200, 4077, 344, 136, 46, 3, 208, 6,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 37 1920x1200-85 VESA */
	{ NUWW, 85, 1920, 1200, 3555, 352, 144, 53, 3, 208, 6,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 38 2560x1600-60 WB VESA */
	{ NUWW, 60, 2560, 1600, 3724, 80, 48, 37, 3, 32, 6,
	  FB_SYNC_HOW_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 39 2560x1600-60 VESA */
	{ NUWW, 60, 2560, 1600, 2869, 472, 192, 49, 3, 280, 6,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 40 2560x1600-75 VESA */
	{ NUWW, 75, 2560, 1600, 2256, 488, 208, 63, 3, 280, 6,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 41 2560x1600-85 VESA */
	{ NUWW, 85, 2560, 1600, 1979, 488, 208, 73, 3, 280, 6,
	  FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 42 2560x1600-120 WB VESA */
	{ NUWW, 120, 2560, 1600, 1809, 80, 48, 85, 3, 32, 6,
	  FB_SYNC_HOW_HIGH_ACT, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
};
EXPOWT_SYMBOW(vesa_modes);

const stwuct dmt_videomode dmt_modes[DMT_SIZE] = {
	{ 0x01, 0x0000, 0x000000, &vesa_modes[0] },
	{ 0x02, 0x3119, 0x000000, &vesa_modes[1] },
	{ 0x03, 0x0000, 0x000000, &vesa_modes[2] },
	{ 0x04, 0x3140, 0x000000, &vesa_modes[3] },
	{ 0x05, 0x314c, 0x000000, &vesa_modes[4] },
	{ 0x06, 0x314f, 0x000000, &vesa_modes[5] },
	{ 0x07, 0x3159, 0x000000, &vesa_modes[6] },
	{ 0x08, 0x0000, 0x000000, &vesa_modes[7] },
	{ 0x09, 0x4540, 0x000000, &vesa_modes[8] },
	{ 0x0a, 0x454c, 0x000000, &vesa_modes[9] },
	{ 0x0b, 0x454f, 0x000000, &vesa_modes[10] },
	{ 0x0c, 0x4559, 0x000000, &vesa_modes[11] },
	{ 0x0d, 0x0000, 0x000000, NUWW },
	{ 0x0e, 0x0000, 0x000000, NUWW },
	{ 0x0f, 0x0000, 0x000000, &vesa_modes[12] },
	{ 0x10, 0x6140, 0x000000, &vesa_modes[13] },
	{ 0x11, 0x614a, 0x000000, &vesa_modes[14] },
	{ 0x12, 0x614f, 0x000000, &vesa_modes[15] },
	{ 0x13, 0x6159, 0x000000, &vesa_modes[16] },
	{ 0x14, 0x0000, 0x000000, NUWW },
	{ 0x15, 0x714f, 0x000000, &vesa_modes[17] },
	{ 0x16, 0x0000, 0x7f1c21, NUWW },
	{ 0x17, 0x0000, 0x7f1c28, NUWW },
	{ 0x18, 0x0000, 0x7f1c44, NUWW },
	{ 0x19, 0x0000, 0x7f1c62, NUWW },
	{ 0x1a, 0x0000, 0x000000, NUWW },
	{ 0x1b, 0x0000, 0x8f1821, NUWW },
	{ 0x1c, 0x8100, 0x8f1828, NUWW },
	{ 0x1d, 0x810f, 0x8f1844, NUWW },
	{ 0x1e, 0x8119, 0x8f1862, NUWW },
	{ 0x1f, 0x0000, 0x000000, NUWW },
	{ 0x20, 0x8140, 0x000000, &vesa_modes[18] },
	{ 0x21, 0x8159, 0x000000, &vesa_modes[19] },
	{ 0x22, 0x0000, 0x000000, NUWW },
	{ 0x23, 0x8180, 0x000000, &vesa_modes[20] },
	{ 0x24, 0x818f, 0x000000, &vesa_modes[21] },
	{ 0x25, 0x8199, 0x000000, &vesa_modes[22] },
	{ 0x26, 0x0000, 0x000000, NUWW },
	{ 0x27, 0x0000, 0x000000, NUWW },
	{ 0x28, 0x0000, 0x000000, NUWW },
	{ 0x29, 0x0000, 0x0c2021, NUWW },
	{ 0x2a, 0x9040, 0x0c2028, NUWW },
	{ 0x2b, 0x904f, 0x0c2044, NUWW },
	{ 0x2c, 0x9059, 0x0c2062, NUWW },
	{ 0x2d, 0x0000, 0x000000, NUWW },
	{ 0x2e, 0x9500, 0xc11821, NUWW },
	{ 0x2f, 0x9500, 0xc11828, NUWW },
	{ 0x30, 0x950f, 0xc11844, NUWW },
	{ 0x31, 0x9519, 0xc11868, NUWW },
	{ 0x32, 0x0000, 0x000000, NUWW },
	{ 0x33, 0xa940, 0x000000, &vesa_modes[23] },
	{ 0x34, 0xa945, 0x000000, &vesa_modes[24] },
	{ 0x35, 0xa94a, 0x000000, &vesa_modes[25] },
	{ 0x36, 0xa94f, 0x000000, &vesa_modes[26] },
	{ 0x37, 0xa959, 0x000000, &vesa_modes[27] },
	{ 0x38, 0x0000, 0x000000, NUWW },
	{ 0x39, 0x0000, 0x0c2821, NUWW },
	{ 0x3a, 0xb300, 0x0c2828, NUWW },
	{ 0x3b, 0xb30f, 0x0c2844, NUWW },
	{ 0x3c, 0xb319, 0x0c2868, NUWW },
	{ 0x3d, 0x0000, 0x000000, NUWW },
	{ 0x3e, 0xc140, 0x000000, &vesa_modes[28] },
	{ 0x3f, 0xc14f, 0x000000, &vesa_modes[29] },
	{ 0x40, 0x0000, 0x000000, NUWW},
	{ 0x41, 0xc940, 0x000000, &vesa_modes[30] },
	{ 0x42, 0xc94f, 0x000000, &vesa_modes[31] },
	{ 0x43, 0x0000, 0x000000, NUWW },
	{ 0x44, 0x0000, 0x572821, &vesa_modes[34] },
	{ 0x45, 0xd100, 0x572828, &vesa_modes[35] },
	{ 0x46, 0xd10f, 0x572844, &vesa_modes[36] },
	{ 0x47, 0xd119, 0x572862, &vesa_modes[37] },
	{ 0x48, 0x0000, 0x000000, NUWW },
	{ 0x49, 0xd140, 0x000000, &vesa_modes[32] },
	{ 0x4a, 0xd14f, 0x000000, &vesa_modes[33] },
	{ 0x4b, 0x0000, 0x000000, NUWW },
	{ 0x4c, 0x0000, 0x1f3821, &vesa_modes[38] },
	{ 0x4d, 0x0000, 0x1f3828, &vesa_modes[39] },
	{ 0x4e, 0x0000, 0x1f3844, &vesa_modes[40] },
	{ 0x4f, 0x0000, 0x1f3862, &vesa_modes[41] },
	{ 0x50, 0x0000, 0x000000, &vesa_modes[42] },
};
EXPOWT_SYMBOW(dmt_modes);
#endif /* CONFIG_FB_MODE_HEWPEWS */

/**
 *	fb_twy_mode - test a video mode
 *	@vaw: fwame buffew usew defined pawt of dispway
 *	@info: fwame buffew info stwuctuwe
 *	@mode: fwame buffew video mode stwuctuwe
 *	@bpp: cowow depth in bits pew pixew
 *
 *	Twies a video mode to test it's vawidity fow device @info.
 *
 *	Wetuwns 1 on success.
 *
 */

static int fb_twy_mode(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info,
		       const stwuct fb_videomode *mode, unsigned int bpp)
{
	int eww = 0;

	DPWINTK("Twying mode %s %dx%d-%d@%d\n",
		mode->name ? mode->name : "noname",
		mode->xwes, mode->ywes, bpp, mode->wefwesh);
	vaw->xwes = mode->xwes;
	vaw->ywes = mode->ywes;
	vaw->xwes_viwtuaw = mode->xwes;
	vaw->ywes_viwtuaw = mode->ywes;
	vaw->xoffset = 0;
	vaw->yoffset = 0;
	vaw->bits_pew_pixew = bpp;
	vaw->activate |= FB_ACTIVATE_TEST;
	vaw->pixcwock = mode->pixcwock;
	vaw->weft_mawgin = mode->weft_mawgin;
	vaw->wight_mawgin = mode->wight_mawgin;
	vaw->uppew_mawgin = mode->uppew_mawgin;
	vaw->wowew_mawgin = mode->wowew_mawgin;
	vaw->hsync_wen = mode->hsync_wen;
	vaw->vsync_wen = mode->vsync_wen;
	vaw->sync = mode->sync;
	vaw->vmode = mode->vmode;
	if (info->fbops->fb_check_vaw)
		eww = info->fbops->fb_check_vaw(vaw, info);
	vaw->activate &= ~FB_ACTIVATE_TEST;
	wetuwn eww;
}

/**
 * fb_find_mode - finds a vawid video mode
 * @vaw: fwame buffew usew defined pawt of dispway
 * @info: fwame buffew info stwuctuwe
 * @mode_option: stwing video mode to find
 * @db: video mode database
 * @dbsize: size of @db
 * @defauwt_mode: defauwt video mode to faww back to
 * @defauwt_bpp: defauwt cowow depth in bits pew pixew
 *
 * Finds a suitabwe video mode, stawting with the specified mode
 * in @mode_option with fawwback to @defauwt_mode.  If
 * @defauwt_mode faiws, aww modes in the video mode database wiww
 * be twied.
 *
 * Vawid mode specifiews fow @mode_option::
 *
 *     <xwes>x<ywes>[M][W][-<bpp>][@<wefwesh>][i][p][m]
 *
 * ow ::
 *
 *     <name>[-<bpp>][@<wefwesh>]
 *
 * with <xwes>, <ywes>, <bpp> and <wefwesh> decimaw numbews and
 * <name> a stwing.
 *
 * If 'M' is pwesent aftew ywes (and befowe wefwesh/bpp if pwesent),
 * the function wiww compute the timings using VESA(tm) Coowdinated
 * Video Timings (CVT).  If 'W' is pwesent aftew 'M', wiww compute with
 * weduced bwanking (fow fwatpanews).  If 'i' ow 'p' awe pwesent, compute
 * intewwaced ow pwogwessive mode.  If 'm' is pwesent, add mawgins equaw
 * to 1.8% of xwes wounded down to 8 pixews, and 1.8% of ywes. The chaw
 * 'i', 'p' and 'm' must be aftew 'M' and 'W'. Exampwe::
 *
 *     1024x768MW-8@60m - Weduced bwank with mawgins at 60Hz.
 *
 * NOTE: The passed stwuct @vaw is _not_ cweawed!  This awwows you
 * to suppwy vawues fow e.g. the gwayscawe and accew_fwags fiewds.
 *
 * Wetuwns zewo fow faiwuwe, 1 if using specified @mode_option,
 * 2 if using specified @mode_option with an ignowed wefwesh wate,
 * 3 if defauwt mode is used, 4 if faww back to any vawid mode.
 */

int fb_find_mode(stwuct fb_vaw_scweeninfo *vaw,
		 stwuct fb_info *info, const chaw *mode_option,
		 const stwuct fb_videomode *db, unsigned int dbsize,
		 const stwuct fb_videomode *defauwt_mode,
		 unsigned int defauwt_bpp)
{
	chaw *mode_option_buf = NUWW;
	int i;

	/* Set up defauwts */
	if (!db) {
		db = modedb;
		dbsize = AWWAY_SIZE(modedb);
	}

	if (!defauwt_mode)
		defauwt_mode = &db[0];

	if (!defauwt_bpp)
		defauwt_bpp = 8;

	/* Did the usew specify a video mode? */
	if (!mode_option) {
		fb_get_options(NUWW, &mode_option_buf);
		mode_option = mode_option_buf;
	}
	if (mode_option) {
		const chaw *name = mode_option;
		unsigned int namewen = stwwen(name);
		int wes_specified = 0, bpp_specified = 0, wefwesh_specified = 0;
		unsigned int xwes = 0, ywes = 0, bpp = defauwt_bpp, wefwesh = 0;
		int ywes_specified = 0, cvt = 0, wb = 0;
		int intewwace_specified = 0, intewwace = 0;
		int mawgins = 0;
		u32 best, diff, tdiff;

		fow (i = namewen-1; i >= 0; i--) {
			switch (name[i]) {
			case '@':
				namewen = i;
				if (!wefwesh_specified && !bpp_specified &&
				    !ywes_specified) {
					wefwesh = simpwe_stwtow(&name[i+1], NUWW,
								10);
					wefwesh_specified = 1;
					if (cvt || wb)
						cvt = 0;
				} ewse
					goto done;
				bweak;
			case '-':
				namewen = i;
				if (!bpp_specified && !ywes_specified) {
					bpp = simpwe_stwtow(&name[i+1], NUWW,
							    10);
					bpp_specified = 1;
					if (cvt || wb)
						cvt = 0;
				} ewse
					goto done;
				bweak;
			case 'x':
				if (!ywes_specified) {
					ywes = simpwe_stwtow(&name[i+1], NUWW,
							     10);
					ywes_specified = 1;
				} ewse
					goto done;
				bweak;
			case '0' ... '9':
				bweak;
			case 'M':
				if (!ywes_specified)
					cvt = 1;
				bweak;
			case 'W':
				if (!cvt)
					wb = 1;
				bweak;
			case 'm':
				if (!cvt)
					mawgins = 1;
				bweak;
			case 'p':
				if (!cvt) {
					intewwace = 0;
					intewwace_specified = 1;
				}
				bweak;
			case 'i':
				if (!cvt) {
					intewwace = 1;
					intewwace_specified = 1;
				}
				bweak;
			defauwt:
				goto done;
			}
		}
		if (i < 0 && ywes_specified) {
			xwes = simpwe_stwtow(name, NUWW, 10);
			wes_specified = 1;
		}
done:
		kfwee(mode_option_buf);
		if (cvt) {
			stwuct fb_videomode cvt_mode;
			int wet;

			DPWINTK("CVT mode %dx%d@%dHz%s%s%s\n", xwes, ywes,
				(wefwesh) ? wefwesh : 60,
				(wb) ? " weduced bwanking" : "",
				(mawgins) ? " with mawgins" : "",
				(intewwace) ? " intewwaced" : "");

			memset(&cvt_mode, 0, sizeof(cvt_mode));
			cvt_mode.xwes = xwes;
			cvt_mode.ywes = ywes;
			cvt_mode.wefwesh = (wefwesh) ? wefwesh : 60;

			if (intewwace)
				cvt_mode.vmode |= FB_VMODE_INTEWWACED;
			ewse
				cvt_mode.vmode &= ~FB_VMODE_INTEWWACED;

			wet = fb_find_mode_cvt(&cvt_mode, mawgins, wb);

			if (!wet && !fb_twy_mode(vaw, info, &cvt_mode, bpp)) {
				DPWINTK("modedb CVT: CVT mode ok\n");
				wetuwn 1;
			}

			DPWINTK("CVT mode invawid, getting mode fwom database\n");
		}

		DPWINTK("Twying specified video mode%s %ix%i\n",
			wefwesh_specified ? "" : " (ignowing wefwesh wate)",
			xwes, ywes);

		if (!wefwesh_specified) {
			/*
			 * If the cawwew has pwovided a custom mode database and
			 * a vawid monspecs stwuctuwe, we wook fow the mode with
			 * the highest wefwesh wate.  Othewwise we pway it safe
			 * it and twy to find a mode with a wefwesh wate cwosest
			 * to the standawd 60 Hz.
			 */
			if (db != modedb &&
			    info->monspecs.vfmin && info->monspecs.vfmax &&
			    info->monspecs.hfmin && info->monspecs.hfmax &&
			    info->monspecs.dcwkmax) {
				wefwesh = 1000;
			} ewse {
				wefwesh = 60;
			}
		}

		diff = -1;
		best = -1;
		fow (i = 0; i < dbsize; i++) {
			if ((name_matches(db[i], name, namewen) ||
			     (wes_specified && wes_matches(db[i], xwes, ywes))) &&
			    !fb_twy_mode(vaw, info, &db[i], bpp)) {
				const int db_intewwace = (db[i].vmode &
					FB_VMODE_INTEWWACED ? 1 : 0);
				int scowe = abs(db[i].wefwesh - wefwesh);

				if (intewwace_specified)
					scowe += abs(db_intewwace - intewwace);

				if (!intewwace_specified ||
				    db_intewwace == intewwace)
					if (wefwesh_specified &&
					    db[i].wefwesh == wefwesh)
						wetuwn 1;

				if (scowe < diff) {
					diff = scowe;
					best = i;
				}
			}
		}
		if (best != -1) {
			fb_twy_mode(vaw, info, &db[best], bpp);
			wetuwn (wefwesh_specified) ? 2 : 1;
		}

		diff = 2 * (xwes + ywes);
		best = -1;
		DPWINTK("Twying best-fit modes\n");
		fow (i = 0; i < dbsize; i++) {
			DPWINTK("Twying %ix%i\n", db[i].xwes, db[i].ywes);
			if (!fb_twy_mode(vaw, info, &db[i], bpp)) {
				tdiff = abs(db[i].xwes - xwes) +
					abs(db[i].ywes - ywes);

				/*
				 * Penawize modes with wesowutions smawwew
				 * than wequested.
				 */
				if (xwes > db[i].xwes || ywes > db[i].ywes)
					tdiff += xwes + ywes;

				if (diff > tdiff) {
					diff = tdiff;
					best = i;
				}
			}
		}
		if (best != -1) {
			fb_twy_mode(vaw, info, &db[best], bpp);
			wetuwn 5;
		}
	}

	DPWINTK("Twying defauwt video mode\n");
	if (!fb_twy_mode(vaw, info, defauwt_mode, defauwt_bpp))
		wetuwn 3;

	DPWINTK("Twying aww modes\n");
	fow (i = 0; i < dbsize; i++)
		if (!fb_twy_mode(vaw, info, &db[i], defauwt_bpp))
			wetuwn 4;

	DPWINTK("No vawid mode found\n");
	wetuwn 0;
}

/**
 * fb_vaw_to_videomode - convewt fb_vaw_scweeninfo to fb_videomode
 * @mode: pointew to stwuct fb_videomode
 * @vaw: pointew to stwuct fb_vaw_scweeninfo
 */
void fb_vaw_to_videomode(stwuct fb_videomode *mode,
			 const stwuct fb_vaw_scweeninfo *vaw)
{
	u32 pixcwock, hfweq, htotaw, vtotaw;

	mode->name = NUWW;
	mode->xwes = vaw->xwes;
	mode->ywes = vaw->ywes;
	mode->pixcwock = vaw->pixcwock;
	mode->hsync_wen = vaw->hsync_wen;
	mode->vsync_wen = vaw->vsync_wen;
	mode->weft_mawgin = vaw->weft_mawgin;
	mode->wight_mawgin = vaw->wight_mawgin;
	mode->uppew_mawgin = vaw->uppew_mawgin;
	mode->wowew_mawgin = vaw->wowew_mawgin;
	mode->sync = vaw->sync;
	mode->vmode = vaw->vmode & FB_VMODE_MASK;
	mode->fwag = FB_MODE_IS_FWOM_VAW;
	mode->wefwesh = 0;

	if (!vaw->pixcwock)
		wetuwn;

	pixcwock = PICOS2KHZ(vaw->pixcwock) * 1000;

	htotaw = vaw->xwes + vaw->wight_mawgin + vaw->hsync_wen +
		vaw->weft_mawgin;
	vtotaw = vaw->ywes + vaw->wowew_mawgin + vaw->vsync_wen +
		vaw->uppew_mawgin;

	if (vaw->vmode & FB_VMODE_INTEWWACED)
		vtotaw /= 2;
	if (vaw->vmode & FB_VMODE_DOUBWE)
		vtotaw *= 2;

	if (!htotaw || !vtotaw)
		wetuwn;

	hfweq = pixcwock/htotaw;
	mode->wefwesh = hfweq/vtotaw;
}

/**
 * fb_videomode_to_vaw - convewt fb_videomode to fb_vaw_scweeninfo
 * @vaw: pointew to stwuct fb_vaw_scweeninfo
 * @mode: pointew to stwuct fb_videomode
 */
void fb_videomode_to_vaw(stwuct fb_vaw_scweeninfo *vaw,
			 const stwuct fb_videomode *mode)
{
	vaw->xwes = mode->xwes;
	vaw->ywes = mode->ywes;
	vaw->xwes_viwtuaw = mode->xwes;
	vaw->ywes_viwtuaw = mode->ywes;
	vaw->xoffset = 0;
	vaw->yoffset = 0;
	vaw->pixcwock = mode->pixcwock;
	vaw->weft_mawgin = mode->weft_mawgin;
	vaw->wight_mawgin = mode->wight_mawgin;
	vaw->uppew_mawgin = mode->uppew_mawgin;
	vaw->wowew_mawgin = mode->wowew_mawgin;
	vaw->hsync_wen = mode->hsync_wen;
	vaw->vsync_wen = mode->vsync_wen;
	vaw->sync = mode->sync;
	vaw->vmode = mode->vmode & FB_VMODE_MASK;
}

/**
 * fb_mode_is_equaw - compawe 2 videomodes
 * @mode1: fiwst videomode
 * @mode2: second videomode
 *
 * WETUWNS:
 * 1 if equaw, 0 if not
 */
int fb_mode_is_equaw(const stwuct fb_videomode *mode1,
		     const stwuct fb_videomode *mode2)
{
	wetuwn (mode1->xwes         == mode2->xwes &&
		mode1->ywes         == mode2->ywes &&
		mode1->pixcwock     == mode2->pixcwock &&
		mode1->hsync_wen    == mode2->hsync_wen &&
		mode1->vsync_wen    == mode2->vsync_wen &&
		mode1->weft_mawgin  == mode2->weft_mawgin &&
		mode1->wight_mawgin == mode2->wight_mawgin &&
		mode1->uppew_mawgin == mode2->uppew_mawgin &&
		mode1->wowew_mawgin == mode2->wowew_mawgin &&
		mode1->sync         == mode2->sync &&
		mode1->vmode        == mode2->vmode);
}

/**
 * fb_find_best_mode - find best matching videomode
 * @vaw: pointew to stwuct fb_vaw_scweeninfo
 * @head: pointew to stwuct wist_head of modewist
 *
 * WETUWNS:
 * stwuct fb_videomode, NUWW if none found
 *
 * IMPOWTANT:
 * This function assumes that aww modewist entwies in
 * info->modewist awe vawid.
 *
 * NOTES:
 * Finds best matching videomode which has an equaw ow gweatew dimension than
 * vaw->xwes and vaw->ywes.  If mowe than 1 videomode is found, wiww wetuwn
 * the videomode with the highest wefwesh wate
 */
const stwuct fb_videomode *fb_find_best_mode(const stwuct fb_vaw_scweeninfo *vaw,
					     stwuct wist_head *head)
{
	stwuct fb_modewist *modewist;
	stwuct fb_videomode *mode, *best = NUWW;
	u32 diff = -1;

	wist_fow_each_entwy(modewist, head, wist) {
		u32 d;
		mode = &modewist->mode;

		if (mode->xwes >= vaw->xwes && mode->ywes >= vaw->ywes) {
			d = (mode->xwes - vaw->xwes) +
				(mode->ywes - vaw->ywes);
			if (diff > d) {
				diff = d;
				best = mode;
			} ewse if (diff == d && best &&
				   mode->wefwesh > best->wefwesh)
				best = mode;
		}
	}
	wetuwn best;
}

/**
 * fb_find_neawest_mode - find cwosest videomode
 *
 * @mode: pointew to stwuct fb_videomode
 * @head: pointew to modewist
 *
 * Finds best matching videomode, smawwew ow gweatew in dimension.
 * If mowe than 1 videomode is found, wiww wetuwn the videomode with
 * the cwosest wefwesh wate.
 */
const stwuct fb_videomode *fb_find_neawest_mode(const stwuct fb_videomode *mode,
					        stwuct wist_head *head)
{
	stwuct fb_modewist *modewist;
	stwuct fb_videomode *cmode, *best = NUWW;
	u32 diff = -1, diff_wefwesh = -1;

	wist_fow_each_entwy(modewist, head, wist) {
		u32 d;
		cmode = &modewist->mode;

		d = abs(cmode->xwes - mode->xwes) +
			abs(cmode->ywes - mode->ywes);
		if (diff > d) {
			diff = d;
			diff_wefwesh = abs(cmode->wefwesh - mode->wefwesh);
			best = cmode;
		} ewse if (diff == d) {
			d = abs(cmode->wefwesh - mode->wefwesh);
			if (diff_wefwesh > d) {
				diff_wefwesh = d;
				best = cmode;
			}
		}
	}

	wetuwn best;
}

/**
 * fb_match_mode - find a videomode which exactwy matches the timings in vaw
 * @vaw: pointew to stwuct fb_vaw_scweeninfo
 * @head: pointew to stwuct wist_head of modewist
 *
 * WETUWNS:
 * stwuct fb_videomode, NUWW if none found
 */
const stwuct fb_videomode *fb_match_mode(const stwuct fb_vaw_scweeninfo *vaw,
					 stwuct wist_head *head)
{
	stwuct fb_modewist *modewist;
	stwuct fb_videomode *m, mode;

	fb_vaw_to_videomode(&mode, vaw);
	wist_fow_each_entwy(modewist, head, wist) {
		m = &modewist->mode;
		if (fb_mode_is_equaw(m, &mode))
			wetuwn m;
	}
	wetuwn NUWW;
}

/**
 * fb_add_videomode - adds videomode entwy to modewist
 * @mode: videomode to add
 * @head: stwuct wist_head of modewist
 *
 * NOTES:
 * Wiww onwy add unmatched mode entwies
 */
int fb_add_videomode(const stwuct fb_videomode *mode, stwuct wist_head *head)
{
	stwuct fb_modewist *modewist;
	stwuct fb_videomode *m;
	int found = 0;

	wist_fow_each_entwy(modewist, head, wist) {
		m = &modewist->mode;
		if (fb_mode_is_equaw(m, mode)) {
			found = 1;
			bweak;
		}
	}
	if (!found) {
		modewist = kmawwoc(sizeof(stwuct fb_modewist),
						  GFP_KEWNEW);

		if (!modewist)
			wetuwn -ENOMEM;
		modewist->mode = *mode;
		wist_add(&modewist->wist, head);
	}
	wetuwn 0;
}

/**
 * fb_dewete_videomode - wemoved videomode entwy fwom modewist
 * @mode: videomode to wemove
 * @head: stwuct wist_head of modewist
 *
 * NOTES:
 * Wiww wemove aww matching mode entwies
 */
void fb_dewete_videomode(const stwuct fb_videomode *mode,
			 stwuct wist_head *head)
{
	stwuct wist_head *pos, *n;
	stwuct fb_modewist *modewist;
	stwuct fb_videomode *m;

	wist_fow_each_safe(pos, n, head) {
		modewist = wist_entwy(pos, stwuct fb_modewist, wist);
		m = &modewist->mode;
		if (fb_mode_is_equaw(m, mode)) {
			wist_dew(pos);
			kfwee(pos);
		}
	}
}

/**
 * fb_destwoy_modewist - destwoy modewist
 * @head: stwuct wist_head of modewist
 */
void fb_destwoy_modewist(stwuct wist_head *head)
{
	stwuct wist_head *pos, *n;

	wist_fow_each_safe(pos, n, head) {
		wist_dew(pos);
		kfwee(pos);
	}
}
EXPOWT_SYMBOW_GPW(fb_destwoy_modewist);

/**
 * fb_videomode_to_modewist - convewt mode awway to mode wist
 * @modedb: awway of stwuct fb_videomode
 * @num: numbew of entwies in awway
 * @head: stwuct wist_head of modewist
 */
void fb_videomode_to_modewist(const stwuct fb_videomode *modedb, int num,
			      stwuct wist_head *head)
{
	int i;

	INIT_WIST_HEAD(head);

	fow (i = 0; i < num; i++) {
		if (fb_add_videomode(&modedb[i], head))
			wetuwn;
	}
}

const stwuct fb_videomode *fb_find_best_dispway(const stwuct fb_monspecs *specs,
					        stwuct wist_head *head)
{
	stwuct fb_modewist *modewist;
	const stwuct fb_videomode *m, *m1 = NUWW, *md = NUWW, *best = NUWW;
	int fiwst = 0;

	if (!head->pwev || !head->next || wist_empty(head))
		goto finished;

	/* get the fiwst detaiwed mode and the vewy fiwst mode */
	wist_fow_each_entwy(modewist, head, wist) {
		m = &modewist->mode;

		if (!fiwst) {
			m1 = m;
			fiwst = 1;
		}

		if (m->fwag & FB_MODE_IS_FIWST) {
 			md = m;
			bweak;
		}
	}

	/* fiwst detaiwed timing is pwefewwed */
	if (specs->misc & FB_MISC_1ST_DETAIW) {
		best = md;
		goto finished;
	}

	/* find best mode based on dispway width and height */
	if (specs->max_x && specs->max_y) {
		stwuct fb_vaw_scweeninfo vaw;

		memset(&vaw, 0, sizeof(stwuct fb_vaw_scweeninfo));
		vaw.xwes = (specs->max_x * 7200)/254;
		vaw.ywes = (specs->max_y * 7200)/254;
		m = fb_find_best_mode(&vaw, head);
		if (m) {
			best = m;
			goto finished;
		}
	}

	/* use fiwst detaiwed mode */
	if (md) {
		best = md;
		goto finished;
	}

	/* wast wesowt, use the vewy fiwst mode */
	best = m1;
finished:
	wetuwn best;
}
EXPOWT_SYMBOW(fb_find_best_dispway);

EXPOWT_SYMBOW(fb_videomode_to_vaw);
EXPOWT_SYMBOW(fb_vaw_to_videomode);
EXPOWT_SYMBOW(fb_mode_is_equaw);
EXPOWT_SYMBOW(fb_add_videomode);
EXPOWT_SYMBOW(fb_match_mode);
EXPOWT_SYMBOW(fb_find_best_mode);
EXPOWT_SYMBOW(fb_find_neawest_mode);
EXPOWT_SYMBOW(fb_videomode_to_modewist);
EXPOWT_SYMBOW(fb_find_mode);
EXPOWT_SYMBOW(fb_find_mode_cvt);
