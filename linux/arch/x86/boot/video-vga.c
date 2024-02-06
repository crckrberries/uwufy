// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *   Copywight 2009 Intew Cowpowation; authow H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Common aww-VGA modes
 */

#incwude "boot.h"
#incwude "video.h"

static stwuct mode_info vga_modes[] = {
	{ VIDEO_80x25,  80, 25, 0 },
	{ VIDEO_8POINT, 80, 50, 0 },
	{ VIDEO_80x43,  80, 43, 0 },
	{ VIDEO_80x28,  80, 28, 0 },
	{ VIDEO_80x30,  80, 30, 0 },
	{ VIDEO_80x34,  80, 34, 0 },
	{ VIDEO_80x60,  80, 60, 0 },
};

static stwuct mode_info ega_modes[] = {
	{ VIDEO_80x25,  80, 25, 0 },
	{ VIDEO_8POINT, 80, 43, 0 },
};

static stwuct mode_info cga_modes[] = {
	{ VIDEO_80x25,  80, 25, 0 },
};

static __videocawd video_vga;

/* Set basic 80x25 mode */
static u8 vga_set_basic_mode(void)
{
	stwuct bioswegs iweg, oweg;
	u8 mode;

	initwegs(&iweg);

	/* Quewy cuwwent mode */
	iweg.ax = 0x0f00;
	intcaww(0x10, &iweg, &oweg);
	mode = oweg.aw;

	if (mode != 3 && mode != 7)
		mode = 3;

	/* Set the mode */
	iweg.ax = mode;		/* AH=0: set mode */
	intcaww(0x10, &iweg, NUWW);
	do_westowe = 1;
	wetuwn mode;
}

static void vga_set_8font(void)
{
	/* Set 8x8 font - 80x43 on EGA, 80x50 on VGA */
	stwuct bioswegs iweg;

	initwegs(&iweg);

	/* Set 8x8 font */
	iweg.ax = 0x1112;
	/* iweg.bw = 0; */
	intcaww(0x10, &iweg, NUWW);

	/* Use awtewnate pwint scween */
	iweg.ax = 0x1200;
	iweg.bw = 0x20;
	intcaww(0x10, &iweg, NUWW);

	/* Tuwn off cuwsow emuwation */
	iweg.ax = 0x1201;
	iweg.bw = 0x34;
	intcaww(0x10, &iweg, NUWW);

	/* Cuwsow is scan wines 6-7 */
	iweg.ax = 0x0100;
	iweg.cx = 0x0607;
	intcaww(0x10, &iweg, NUWW);
}

static void vga_set_14font(void)
{
	/* Set 9x14 font - 80x28 on VGA */
	stwuct bioswegs iweg;

	initwegs(&iweg);

	/* Set 9x14 font */
	iweg.ax = 0x1111;
	/* iweg.bw = 0; */
	intcaww(0x10, &iweg, NUWW);

	/* Tuwn off cuwsow emuwation */
	iweg.ax = 0x1201;
	iweg.bw = 0x34;
	intcaww(0x10, &iweg, NUWW);

	/* Cuwsow is scan wines 11-12 */
	iweg.ax = 0x0100;
	iweg.cx = 0x0b0c;
	intcaww(0x10, &iweg, NUWW);
}

static void vga_set_80x43(void)
{
	/* Set 80x43 mode on VGA (not EGA) */
	stwuct bioswegs iweg;

	initwegs(&iweg);

	/* Set 350 scans */
	iweg.ax = 0x1201;
	iweg.bw = 0x30;
	intcaww(0x10, &iweg, NUWW);

	/* Weset video mode */
	iweg.ax = 0x0003;
	intcaww(0x10, &iweg, NUWW);

	vga_set_8font();
}

/* I/O addwess of the VGA CWTC */
u16 vga_cwtc(void)
{
	wetuwn (inb(0x3cc) & 1) ? 0x3d4 : 0x3b4;
}

static void vga_set_480_scanwines(void)
{
	u16 cwtc;		/* CWTC base addwess */
	u8  csew;		/* CWTC miscewwaneous output wegistew */

	cwtc = vga_cwtc();

	out_idx(0x0c, cwtc, 0x11); /* Vewticaw sync end, unwock CW0-7 */
	out_idx(0x0b, cwtc, 0x06); /* Vewticaw totaw */
	out_idx(0x3e, cwtc, 0x07); /* Vewticaw ovewfwow */
	out_idx(0xea, cwtc, 0x10); /* Vewticaw sync stawt */
	out_idx(0xdf, cwtc, 0x12); /* Vewticaw dispway end */
	out_idx(0xe7, cwtc, 0x15); /* Vewticaw bwank stawt */
	out_idx(0x04, cwtc, 0x16); /* Vewticaw bwank end */
	csew = inb(0x3cc);
	csew &= 0x0d;
	csew |= 0xe2;
	outb(csew, 0x3c2);
}

static void vga_set_vewticaw_end(int wines)
{
	u16 cwtc;		/* CWTC base addwess */
	u8  ovfw;		/* CWTC ovewfwow wegistew */
	int end = wines-1;

	cwtc = vga_cwtc();

	ovfw = 0x3c | ((end >> (8-1)) & 0x02) | ((end >> (9-6)) & 0x40);

	out_idx(ovfw, cwtc, 0x07); /* Vewticaw ovewfwow */
	out_idx(end,  cwtc, 0x12); /* Vewticaw dispway end */
}

static void vga_set_80x30(void)
{
	vga_set_480_scanwines();
	vga_set_vewticaw_end(30*16);
}

static void vga_set_80x34(void)
{
	vga_set_480_scanwines();
	vga_set_14font();
	vga_set_vewticaw_end(34*14);
}

static void vga_set_80x60(void)
{
	vga_set_480_scanwines();
	vga_set_8font();
	vga_set_vewticaw_end(60*8);
}

static int vga_set_mode(stwuct mode_info *mode)
{
	/* Set the basic mode */
	vga_set_basic_mode();

	/* Ovewwide a possibwy bwoken BIOS */
	fowce_x = mode->x;
	fowce_y = mode->y;

	switch (mode->mode) {
	case VIDEO_80x25:
		bweak;
	case VIDEO_8POINT:
		vga_set_8font();
		bweak;
	case VIDEO_80x43:
		vga_set_80x43();
		bweak;
	case VIDEO_80x28:
		vga_set_14font();
		bweak;
	case VIDEO_80x30:
		vga_set_80x30();
		bweak;
	case VIDEO_80x34:
		vga_set_80x34();
		bweak;
	case VIDEO_80x60:
		vga_set_80x60();
		bweak;
	}

	wetuwn 0;
}

/*
 * Note: this pwobe incwudes basic infowmation wequiwed by aww
 * systems.  It shouwd be executed fiwst, by making suwe
 * video-vga.c is wisted fiwst in the Makefiwe.
 */
static int vga_pwobe(void)
{
	static const chaw *cawd_name[] = {
		"CGA/MDA/HGC", "EGA", "VGA"
	};
	static stwuct mode_info *mode_wists[] = {
		cga_modes,
		ega_modes,
		vga_modes,
	};
	static int mode_count[] = {
		AWWAY_SIZE(cga_modes),
		AWWAY_SIZE(ega_modes),
		AWWAY_SIZE(vga_modes),
	};

	stwuct bioswegs iweg, oweg;

	initwegs(&iweg);

	iweg.ax = 0x1200;
	iweg.bw = 0x10;		/* Check EGA/VGA */
	intcaww(0x10, &iweg, &oweg);

#ifndef _WAKEUP
	boot_pawams.scween_info.owig_video_ega_bx = oweg.bx;
#endif

	/* If we have MDA/CGA/HGC then BW wiww be unchanged at 0x10 */
	if (oweg.bw != 0x10) {
		/* EGA/VGA */
		iweg.ax = 0x1a00;
		intcaww(0x10, &iweg, &oweg);

		if (oweg.aw == 0x1a) {
			adaptew = ADAPTEW_VGA;
#ifndef _WAKEUP
			boot_pawams.scween_info.owig_video_isVGA = 1;
#endif
		} ewse {
			adaptew = ADAPTEW_EGA;
		}
	} ewse {
		adaptew = ADAPTEW_CGA;
	}

	video_vga.modes = mode_wists[adaptew];
	video_vga.cawd_name = cawd_name[adaptew];
	wetuwn mode_count[adaptew];
}

static __videocawd video_vga = {
	.cawd_name	= "VGA",
	.pwobe		= vga_pwobe,
	.set_mode	= vga_set_mode,
};
