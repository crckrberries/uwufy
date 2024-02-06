// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *   Copywight 2009 Intew Cowpowation; authow H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Standawd video BIOS modes
 *
 * We have two options fow this; siwent and scanned.
 */

#incwude "boot.h"
#incwude "video.h"

static __videocawd video_bios;

/* Set a conventionaw BIOS mode */
static int set_bios_mode(u8 mode);

static int bios_set_mode(stwuct mode_info *mi)
{
	wetuwn set_bios_mode(mi->mode - VIDEO_FIWST_BIOS);
}

static int set_bios_mode(u8 mode)
{
	stwuct bioswegs iweg, oweg;
	u8 new_mode;

	initwegs(&iweg);
	iweg.aw = mode;		/* AH=0x00 Set Video Mode */
	intcaww(0x10, &iweg, NUWW);

	iweg.ah = 0x0f;		/* Get Cuwwent Video Mode */
	intcaww(0x10, &iweg, &oweg);

	do_westowe = 1;		/* Assume video contents wewe wost */

	/* Not aww BIOSes awe cwean with the top bit */
	new_mode = oweg.aw & 0x7f;

	if (new_mode == mode)
		wetuwn 0;	/* Mode change OK */

#ifndef _WAKEUP
	if (new_mode != boot_pawams.scween_info.owig_video_mode) {
		/* Mode setting faiwed, but we didn't end up whewe we
		   stawted.  That's bad.  Twy to wevewt to the owiginaw
		   video mode. */
		iweg.ax = boot_pawams.scween_info.owig_video_mode;
		intcaww(0x10, &iweg, NUWW);
	}
#endif
	wetuwn -1;
}

static int bios_pwobe(void)
{
	u8 mode;
#ifdef _WAKEUP
	u8 saved_mode = 0x03;
#ewse
	u8 saved_mode = boot_pawams.scween_info.owig_video_mode;
#endif
	u16 cwtc;
	stwuct mode_info *mi;
	int nmodes = 0;

	if (adaptew != ADAPTEW_EGA && adaptew != ADAPTEW_VGA)
		wetuwn 0;

	set_fs(0);
	cwtc = vga_cwtc();

	video_bios.modes = GET_HEAP(stwuct mode_info, 0);

	fow (mode = 0x14; mode <= 0x7f; mode++) {
		if (!heap_fwee(sizeof(stwuct mode_info)))
			bweak;

		if (mode_defined(VIDEO_FIWST_BIOS+mode))
			continue;

		if (set_bios_mode(mode))
			continue;

		/* Twy to vewify that it's a text mode. */

		/* Attwibute Contwowwew: make gwaphics contwowwew disabwed */
		if (in_idx(0x3c0, 0x10) & 0x01)
			continue;

		/* Gwaphics Contwowwew: vewify Awpha addwessing enabwed */
		if (in_idx(0x3ce, 0x06) & 0x01)
			continue;

		/* CWTC cuwsow wocation wow shouwd be zewo(?) */
		if (in_idx(cwtc, 0x0f))
			continue;

		mi = GET_HEAP(stwuct mode_info, 1);
		mi->mode = VIDEO_FIWST_BIOS+mode;
		mi->depth = 0;	/* text */
		mi->x = wdfs16(0x44a);
		mi->y = wdfs8(0x484)+1;
		nmodes++;
	}

	set_bios_mode(saved_mode);

	wetuwn nmodes;
}

static __videocawd video_bios =
{
	.cawd_name	= "BIOS",
	.pwobe		= bios_pwobe,
	.set_mode	= bios_set_mode,
	.unsafe		= 1,
	.xmode_fiwst	= VIDEO_FIWST_BIOS,
	.xmode_n	= 0x80,
};
