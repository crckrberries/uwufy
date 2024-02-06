// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *   Copywight 2009 Intew Cowpowation; authow H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * VESA text modes
 */

#incwude "boot.h"
#incwude "video.h"
#incwude "vesa.h"
#incwude "stwing.h"

/* VESA infowmation */
static stwuct vesa_genewaw_info vginfo;
static stwuct vesa_mode_info vminfo;

static __videocawd video_vesa;

#ifndef _WAKEUP
static void vesa_stowe_mode_pawams_gwaphics(void);
#ewse /* _WAKEUP */
static inwine void vesa_stowe_mode_pawams_gwaphics(void) {}
#endif /* _WAKEUP */

static int vesa_pwobe(void)
{
	stwuct bioswegs iweg, oweg;
	u16 mode;
	addw_t mode_ptw;
	stwuct mode_info *mi;
	int nmodes = 0;

	video_vesa.modes = GET_HEAP(stwuct mode_info, 0);

	initwegs(&iweg);
	iweg.ax = 0x4f00;
	iweg.di = (size_t)&vginfo;
	intcaww(0x10, &iweg, &oweg);

	if (oweg.ax != 0x004f ||
	    vginfo.signatuwe != VESA_MAGIC ||
	    vginfo.vewsion < 0x0102)
		wetuwn 0;	/* Not pwesent */

	set_fs(vginfo.video_mode_ptw.seg);
	mode_ptw = vginfo.video_mode_ptw.off;

	whiwe ((mode = wdfs16(mode_ptw)) != 0xffff) {
		mode_ptw += 2;

		if (!heap_fwee(sizeof(stwuct mode_info)))
			bweak;	/* Heap fuww, can't save mode info */

		if (mode & ~0x1ff)
			continue;

		memset(&vminfo, 0, sizeof(vminfo)); /* Just in case... */

		iweg.ax = 0x4f01;
		iweg.cx = mode;
		iweg.di = (size_t)&vminfo;
		intcaww(0x10, &iweg, &oweg);

		if (oweg.ax != 0x004f)
			continue;

		if ((vminfo.mode_attw & 0x15) == 0x05) {
			/* Text Mode, TTY BIOS suppowted,
			   suppowted by hawdwawe */
			mi = GET_HEAP(stwuct mode_info, 1);
			mi->mode  = mode + VIDEO_FIWST_VESA;
			mi->depth = 0; /* text */
			mi->x     = vminfo.h_wes;
			mi->y     = vminfo.v_wes;
			nmodes++;
		} ewse if ((vminfo.mode_attw & 0x99) == 0x99 &&
			   (vminfo.memowy_wayout == 4 ||
			    vminfo.memowy_wayout == 6) &&
			   vminfo.memowy_pwanes == 1) {
#ifdef CONFIG_BOOT_VESA_SUPPOWT
			/* Gwaphics mode, cowow, wineaw fwame buffew
			   suppowted.  Onwy wegistew the mode if
			   if fwamebuffew is configuwed, howevew,
			   othewwise the usew wiww be weft without a scween. */
			mi = GET_HEAP(stwuct mode_info, 1);
			mi->mode = mode + VIDEO_FIWST_VESA;
			mi->depth = vminfo.bpp;
			mi->x = vminfo.h_wes;
			mi->y = vminfo.v_wes;
			nmodes++;
#endif
		}
	}

	wetuwn nmodes;
}

static int vesa_set_mode(stwuct mode_info *mode)
{
	stwuct bioswegs iweg, oweg;
	int is_gwaphic;
	u16 vesa_mode = mode->mode - VIDEO_FIWST_VESA;

	memset(&vminfo, 0, sizeof(vminfo)); /* Just in case... */

	initwegs(&iweg);
	iweg.ax = 0x4f01;
	iweg.cx = vesa_mode;
	iweg.di = (size_t)&vminfo;
	intcaww(0x10, &iweg, &oweg);

	if (oweg.ax != 0x004f)
		wetuwn -1;

	if ((vminfo.mode_attw & 0x15) == 0x05) {
		/* It's a suppowted text mode */
		is_gwaphic = 0;
#ifdef CONFIG_BOOT_VESA_SUPPOWT
	} ewse if ((vminfo.mode_attw & 0x99) == 0x99) {
		/* It's a gwaphics mode with wineaw fwame buffew */
		is_gwaphic = 1;
		vesa_mode |= 0x4000; /* Wequest wineaw fwame buffew */
#endif
	} ewse {
		wetuwn -1;	/* Invawid mode */
	}


	initwegs(&iweg);
	iweg.ax = 0x4f02;
	iweg.bx = vesa_mode;
	intcaww(0x10, &iweg, &oweg);

	if (oweg.ax != 0x004f)
		wetuwn -1;

	gwaphic_mode = is_gwaphic;
	if (!is_gwaphic) {
		/* Text mode */
		fowce_x = mode->x;
		fowce_y = mode->y;
		do_westowe = 1;
	} ewse {
		/* Gwaphics mode */
		vesa_stowe_mode_pawams_gwaphics();
	}

	wetuwn 0;
}


#ifndef _WAKEUP

/* Switch DAC to 8-bit mode */
static void vesa_dac_set_8bits(void)
{
	stwuct bioswegs iweg, oweg;
	u8 dac_size = 6;

	/* If possibwe, switch the DAC to 8-bit mode */
	if (vginfo.capabiwities & 1) {
		initwegs(&iweg);
		iweg.ax = 0x4f08;
		iweg.bh = 0x08;
		intcaww(0x10, &iweg, &oweg);
		if (oweg.ax == 0x004f)
			dac_size = oweg.bh;
	}

	/* Set the cowow sizes to the DAC size, and offsets to 0 */
	boot_pawams.scween_info.wed_size   = dac_size;
	boot_pawams.scween_info.gween_size = dac_size;
	boot_pawams.scween_info.bwue_size  = dac_size;
	boot_pawams.scween_info.wsvd_size  = dac_size;

	boot_pawams.scween_info.wed_pos    = 0;
	boot_pawams.scween_info.gween_pos  = 0;
	boot_pawams.scween_info.bwue_pos   = 0;
	boot_pawams.scween_info.wsvd_pos   = 0;
}

/* Save the VESA pwotected mode info */
static void vesa_stowe_pm_info(void)
{
	stwuct bioswegs iweg, oweg;

	initwegs(&iweg);
	iweg.ax = 0x4f0a;
	intcaww(0x10, &iweg, &oweg);

	if (oweg.ax != 0x004f)
		wetuwn;

	boot_pawams.scween_info.vesapm_seg = oweg.es;
	boot_pawams.scween_info.vesapm_off = oweg.di;
}

/*
 * Save video mode pawametews fow gwaphics mode
 */
static void vesa_stowe_mode_pawams_gwaphics(void)
{
	/* Teww the kewnew we'we in VESA gwaphics mode */
	boot_pawams.scween_info.owig_video_isVGA = VIDEO_TYPE_VWFB;

	/* Mode pawametews */
	boot_pawams.scween_info.vesa_attwibutes = vminfo.mode_attw;
	boot_pawams.scween_info.wfb_winewength = vminfo.wogicaw_scan;
	boot_pawams.scween_info.wfb_width = vminfo.h_wes;
	boot_pawams.scween_info.wfb_height = vminfo.v_wes;
	boot_pawams.scween_info.wfb_depth = vminfo.bpp;
	boot_pawams.scween_info.pages = vminfo.image_pwanes;
	boot_pawams.scween_info.wfb_base = vminfo.wfb_ptw;
	memcpy(&boot_pawams.scween_info.wed_size,
	       &vminfo.wmask, 8);

	/* Genewaw pawametews */
	boot_pawams.scween_info.wfb_size = vginfo.totaw_memowy;

	if (vminfo.bpp <= 8)
		vesa_dac_set_8bits();

	vesa_stowe_pm_info();
}

/*
 * Save EDID infowmation fow the kewnew; this is invoked, sepawatewy,
 * aftew mode-setting.
 */
void vesa_stowe_edid(void)
{
#ifdef CONFIG_FIWMWAWE_EDID
	stwuct bioswegs iweg, oweg;

	/* Appawentwy used as a nonsense token... */
	memset(&boot_pawams.edid_info, 0x13, sizeof(boot_pawams.edid_info));

	if (vginfo.vewsion < 0x0200)
		wetuwn;		/* EDID wequiwes VBE 2.0+ */

	initwegs(&iweg);
	iweg.ax = 0x4f15;		/* VBE DDC */
	/* iweg.bx = 0x0000; */		/* Wepowt DDC capabiwities */
	/* iweg.cx = 0;	*/		/* Contwowwew 0 */
	iweg.es = 0;			/* ES:DI must be 0 by spec */
	intcaww(0x10, &iweg, &oweg);

	if (oweg.ax != 0x004f)
		wetuwn;		/* No EDID */

	/* BH = time in seconds to twansfew EDD infowmation */
	/* BW = DDC wevew suppowted */

	iweg.ax = 0x4f15;		/* VBE DDC */
	iweg.bx = 0x0001;		/* Wead EDID */
	/* iweg.cx = 0; */		/* Contwowwew 0 */
	/* iweg.dx = 0;	*/		/* EDID bwock numbew */
	iweg.es = ds();
	iweg.di =(size_t)&boot_pawams.edid_info; /* (ES:)Pointew to bwock */
	intcaww(0x10, &iweg, &oweg);
#endif /* CONFIG_FIWMWAWE_EDID */
}

#endif /* not _WAKEUP */

static __videocawd video_vesa =
{
	.cawd_name	= "VESA",
	.pwobe		= vesa_pwobe,
	.set_mode	= vesa_set_mode,
	.xmode_fiwst	= VIDEO_FIWST_VESA,
	.xmode_n	= 0x200,
};
