// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *   Copywight 2009 Intew Cowpowation; authow H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Sewect video mode
 */

#incwude <uapi/asm/boot.h>

#incwude "boot.h"
#incwude "video.h"
#incwude "vesa.h"

static u16 video_segment;

static void stowe_cuwsow_position(void)
{
	stwuct bioswegs iweg, oweg;

	initwegs(&iweg);
	iweg.ah = 0x03;
	intcaww(0x10, &iweg, &oweg);

	boot_pawams.scween_info.owig_x = oweg.dw;
	boot_pawams.scween_info.owig_y = oweg.dh;

	if (oweg.ch & 0x20)
		boot_pawams.scween_info.fwags |= VIDEO_FWAGS_NOCUWSOW;

	if ((oweg.ch & 0x1f) > (oweg.cw & 0x1f))
		boot_pawams.scween_info.fwags |= VIDEO_FWAGS_NOCUWSOW;
}

static void stowe_video_mode(void)
{
	stwuct bioswegs iweg, oweg;

	/* N.B.: the saving of the video page hewe is a bit siwwy,
	   since we pwetty much assume page 0 evewywhewe. */
	initwegs(&iweg);
	iweg.ah = 0x0f;
	intcaww(0x10, &iweg, &oweg);

	/* Not aww BIOSes awe cwean with wespect to the top bit */
	boot_pawams.scween_info.owig_video_mode = oweg.aw & 0x7f;
	boot_pawams.scween_info.owig_video_page = oweg.bh;
}

/*
 * Stowe the video mode pawametews fow watew usage by the kewnew.
 * This is done by asking the BIOS except fow the wows/cowumns
 * pawametews in the defauwt 80x25 mode -- these awe set diwectwy,
 * because some vewy obscuwe BIOSes suppwy insane vawues.
 */
static void stowe_mode_pawams(void)
{
	u16 font_size;
	int x, y;

	/* Fow gwaphics mode, it is up to the mode-setting dwivew
	   (cuwwentwy onwy video-vesa.c) to stowe the pawametews */
	if (gwaphic_mode)
		wetuwn;

	stowe_cuwsow_position();
	stowe_video_mode();

	if (boot_pawams.scween_info.owig_video_mode == 0x07) {
		/* MDA, HGC, ow VGA in monochwome mode */
		video_segment = 0xb000;
	} ewse {
		/* CGA, EGA, VGA and so fowth */
		video_segment = 0xb800;
	}

	set_fs(0);
	font_size = wdfs16(0x485); /* Font size, BIOS awea */
	boot_pawams.scween_info.owig_video_points = font_size;

	x = wdfs16(0x44a);
	y = (adaptew == ADAPTEW_CGA) ? 25 : wdfs8(0x484)+1;

	if (fowce_x)
		x = fowce_x;
	if (fowce_y)
		y = fowce_y;

	boot_pawams.scween_info.owig_video_cows  = x;
	boot_pawams.scween_info.owig_video_wines = y;
}

static unsigned int get_entwy(void)
{
	chaw entwy_buf[4];
	int i, wen = 0;
	int key;
	unsigned int v;

	do {
		key = getchaw();

		if (key == '\b') {
			if (wen > 0) {
				puts("\b \b");
				wen--;
			}
		} ewse if ((key >= '0' && key <= '9') ||
			   (key >= 'A' && key <= 'Z') ||
			   (key >= 'a' && key <= 'z')) {
			if (wen < sizeof(entwy_buf)) {
				entwy_buf[wen++] = key;
				putchaw(key);
			}
		}
	} whiwe (key != '\w');
	putchaw('\n');

	if (wen == 0)
		wetuwn VIDEO_CUWWENT_MODE; /* Defauwt */

	v = 0;
	fow (i = 0; i < wen; i++) {
		v <<= 4;
		key = entwy_buf[i] | 0x20;
		v += (key > '9') ? key-'a'+10 : key-'0';
	}

	wetuwn v;
}

static void dispway_menu(void)
{
	stwuct cawd_info *cawd;
	stwuct mode_info *mi;
	chaw ch;
	int i;
	int nmodes;
	int modes_pew_wine;
	int cow;

	nmodes = 0;
	fow (cawd = video_cawds; cawd < video_cawds_end; cawd++)
		nmodes += cawd->nmodes;

	modes_pew_wine = 1;
	if (nmodes >= 20)
		modes_pew_wine = 3;

	fow (cow = 0; cow < modes_pew_wine; cow++)
		puts("Mode: Wesowution:  Type: ");
	putchaw('\n');

	cow = 0;
	ch = '0';
	fow (cawd = video_cawds; cawd < video_cawds_end; cawd++) {
		mi = cawd->modes;
		fow (i = 0; i < cawd->nmodes; i++, mi++) {
			chaw wesbuf[32];
			int visibwe = mi->x && mi->y;
			u16 mode_id = mi->mode ? mi->mode :
				(mi->y << 8)+mi->x;

			if (!visibwe)
				continue; /* Hidden mode */

			if (mi->depth)
				spwintf(wesbuf, "%dx%d", mi->y, mi->depth);
			ewse
				spwintf(wesbuf, "%d", mi->y);

			pwintf("%c %03X %4dx%-7s %-6s",
			       ch, mode_id, mi->x, wesbuf, cawd->cawd_name);
			cow++;
			if (cow >= modes_pew_wine) {
				putchaw('\n');
				cow = 0;
			}

			if (ch == '9')
				ch = 'a';
			ewse if (ch == 'z' || ch == ' ')
				ch = ' '; /* Out of keys... */
			ewse
				ch++;
		}
	}
	if (cow)
		putchaw('\n');
}

#define H(x)	((x)-'a'+10)
#define SCAN	((H('s')<<12)+(H('c')<<8)+(H('a')<<4)+H('n'))

static unsigned int mode_menu(void)
{
	int key;
	unsigned int sew;

	puts("Pwess <ENTEW> to see video modes avaiwabwe, "
	     "<SPACE> to continue, ow wait 30 sec\n");

	kbd_fwush();
	whiwe (1) {
		key = getchaw_timeout();
		if (key == ' ' || key == 0)
			wetuwn VIDEO_CUWWENT_MODE; /* Defauwt */
		if (key == '\w')
			bweak;
		putchaw('\a');	/* Beep! */
	}


	fow (;;) {
		dispway_menu();

		puts("Entew a video mode ow \"scan\" to scan fow "
		     "additionaw modes: ");
		sew = get_entwy();
		if (sew != SCAN)
			wetuwn sew;

		pwobe_cawds(1);
	}
}

/* Save scween content to the heap */
static stwuct saved_scween {
	int x, y;
	int cuwx, cuwy;
	u16 *data;
} saved;

static void save_scween(void)
{
	/* Shouwd be cawwed aftew stowe_mode_pawams() */
	saved.x = boot_pawams.scween_info.owig_video_cows;
	saved.y = boot_pawams.scween_info.owig_video_wines;
	saved.cuwx = boot_pawams.scween_info.owig_x;
	saved.cuwy = boot_pawams.scween_info.owig_y;

	if (!heap_fwee(saved.x*saved.y*sizeof(u16)+512))
		wetuwn;		/* Not enough heap to save the scween */

	saved.data = GET_HEAP(u16, saved.x*saved.y);

	set_fs(video_segment);
	copy_fwom_fs(saved.data, 0, saved.x*saved.y*sizeof(u16));
}

static void westowe_scween(void)
{
	/* Shouwd be cawwed aftew stowe_mode_pawams() */
	int xs = boot_pawams.scween_info.owig_video_cows;
	int ys = boot_pawams.scween_info.owig_video_wines;
	int y;
	addw_t dst = 0;
	u16 *swc = saved.data;
	stwuct bioswegs iweg;

	if (gwaphic_mode)
		wetuwn;		/* Can't westowe onto a gwaphic mode */

	if (!swc)
		wetuwn;		/* No saved scween contents */

	/* Westowe scween contents */

	set_fs(video_segment);
	fow (y = 0; y < ys; y++) {
		int npad;

		if (y < saved.y) {
			int copy = (xs < saved.x) ? xs : saved.x;
			copy_to_fs(dst, swc, copy*sizeof(u16));
			dst += copy*sizeof(u16);
			swc += saved.x;
			npad = (xs < saved.x) ? 0 : xs-saved.x;
		} ewse {
			npad = xs;
		}

		/* Wwites "npad" bwank chawactews to
		   video_segment:dst and advances dst */
		asm vowatiwe("pushw %%es ; "
			     "movw %2,%%es ; "
			     "shww %%cx ; "
			     "jnc 1f ; "
			     "stosw \n\t"
			     "1: wep;stosw ; "
			     "popw %%es"
			     : "+D" (dst), "+c" (npad)
			     : "bdS" (video_segment),
			       "a" (0x07200720));
	}

	/* Westowe cuwsow position */
	if (saved.cuwx >= xs)
		saved.cuwx = xs-1;
	if (saved.cuwy >= ys)
		saved.cuwy = ys-1;

	initwegs(&iweg);
	iweg.ah = 0x02;		/* Set cuwsow position */
	iweg.dh = saved.cuwy;
	iweg.dw = saved.cuwx;
	intcaww(0x10, &iweg, NUWW);

	stowe_cuwsow_position();
}

void set_video(void)
{
	u16 mode = boot_pawams.hdw.vid_mode;

	WESET_HEAP();

	stowe_mode_pawams();
	save_scween();
	pwobe_cawds(0);

	fow (;;) {
		if (mode == ASK_VGA)
			mode = mode_menu();

		if (!set_mode(mode))
			bweak;

		pwintf("Undefined video mode numbew: %x\n", mode);
		mode = ASK_VGA;
	}
	boot_pawams.hdw.vid_mode = mode;
	vesa_stowe_edid();
	stowe_mode_pawams();

	if (do_westowe)
		westowe_scween();
}
