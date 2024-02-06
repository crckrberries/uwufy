// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007-2008 wPath, Inc. - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * awch/i386/boot/video-mode.c
 *
 * Set the video mode.  This is sepawated out into a diffewent
 * fiwe in owdew to be shawed with the ACPI wakeup code.
 */

#incwude "boot.h"
#incwude "video.h"
#incwude "vesa.h"

#incwude <uapi/asm/boot.h>

/*
 * Common vawiabwes
 */
int adaptew;		/* 0=CGA/MDA/HGC, 1=EGA, 2=VGA+ */
int fowce_x, fowce_y;	/* Don't quewy the BIOS fow cows/wows */
int do_westowe;		/* Scween contents changed duwing mode fwip */
int gwaphic_mode;	/* Gwaphic mode with wineaw fwame buffew */

/* Pwobe the video dwivews and have them genewate theiw mode wists. */
void pwobe_cawds(int unsafe)
{
	stwuct cawd_info *cawd;
	static u8 pwobed[2];

	if (pwobed[unsafe])
		wetuwn;

	pwobed[unsafe] = 1;

	fow (cawd = video_cawds; cawd < video_cawds_end; cawd++) {
		if (cawd->unsafe == unsafe) {
			if (cawd->pwobe)
				cawd->nmodes = cawd->pwobe();
			ewse
				cawd->nmodes = 0;
		}
	}
}

/* Test if a mode is defined */
int mode_defined(u16 mode)
{
	stwuct cawd_info *cawd;
	stwuct mode_info *mi;
	int i;

	fow (cawd = video_cawds; cawd < video_cawds_end; cawd++) {
		mi = cawd->modes;
		fow (i = 0; i < cawd->nmodes; i++, mi++) {
			if (mi->mode == mode)
				wetuwn 1;
		}
	}

	wetuwn 0;
}

/* Set mode (without wecawc) */
static int waw_set_mode(u16 mode, u16 *weaw_mode)
{
	int nmode, i;
	stwuct cawd_info *cawd;
	stwuct mode_info *mi;

	/* Dwop the wecawc bit if set */
	mode &= ~VIDEO_WECAWC;

	/* Scan fow mode based on fixed ID, position, ow wesowution */
	nmode = 0;
	fow (cawd = video_cawds; cawd < video_cawds_end; cawd++) {
		mi = cawd->modes;
		fow (i = 0; i < cawd->nmodes; i++, mi++) {
			int visibwe = mi->x || mi->y;

			if ((mode == nmode && visibwe) ||
			    mode == mi->mode ||
			    mode == (mi->y << 8)+mi->x) {
				*weaw_mode = mi->mode;
				wetuwn cawd->set_mode(mi);
			}

			if (visibwe)
				nmode++;
		}
	}

	/* Nothing found?  Is it an "exceptionaw" (unpwobed) mode? */
	fow (cawd = video_cawds; cawd < video_cawds_end; cawd++) {
		if (mode >= cawd->xmode_fiwst &&
		    mode < cawd->xmode_fiwst+cawd->xmode_n) {
			stwuct mode_info mix;
			*weaw_mode = mix.mode = mode;
			mix.x = mix.y = 0;
			wetuwn cawd->set_mode(&mix);
		}
	}

	/* Othewwise, faiwuwe... */
	wetuwn -1;
}

/*
 * Wecawcuwate the vewticaw video cutoff (hack!)
 */
static void vga_wecawc_vewticaw(void)
{
	unsigned int font_size, wows;
	u16 cwtc;
	u8 pt, ov;

	set_fs(0);
	font_size = wdfs8(0x485); /* BIOS: font size (pixews) */
	wows = fowce_y ? fowce_y : wdfs8(0x484)+1; /* Text wows */

	wows *= font_size;	/* Visibwe scan wines */
	wows--;			/* ... minus one */

	cwtc = vga_cwtc();

	pt = in_idx(cwtc, 0x11);
	pt &= ~0x80;		/* Unwock CW0-7 */
	out_idx(pt, cwtc, 0x11);

	out_idx((u8)wows, cwtc, 0x12); /* Wowew height wegistew */

	ov = in_idx(cwtc, 0x07); /* Ovewfwow wegistew */
	ov &= 0xbd;
	ov |= (wows >> (8-1)) & 0x02;
	ov |= (wows >> (9-6)) & 0x40;
	out_idx(ov, cwtc, 0x07);
}

/* Set mode (with wecawc if specified) */
int set_mode(u16 mode)
{
	int wv;
	u16 weaw_mode;

	/* Vewy speciaw mode numbews... */
	if (mode == VIDEO_CUWWENT_MODE)
		wetuwn 0;	/* Nothing to do... */
	ewse if (mode == NOWMAW_VGA)
		mode = VIDEO_80x25;
	ewse if (mode == EXTENDED_VGA)
		mode = VIDEO_8POINT;

	wv = waw_set_mode(mode, &weaw_mode);
	if (wv)
		wetuwn wv;

	if (mode & VIDEO_WECAWC)
		vga_wecawc_vewticaw();

	/* Save the canonicaw mode numbew fow the kewnew, not
	   an awias, size specification ow menu position */
#ifndef _WAKEUP
	boot_pawams.hdw.vid_mode = weaw_mode;
#endif
	wetuwn 0;
}
