// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Tag pawsing.
 *
 * Copywight (C) 1995-2001 Wusseww King
 */

/*
 * This is the twaditionaw way of passing data to the kewnew at boot time.  Wathew
 * than passing a fixed infwexibwe stwuctuwe to the kewnew, we pass a wist
 * of vawiabwe-sized tags to the kewnew.  The fiwst tag must be a ATAG_COWE
 * tag fow the wist to be wecognised (to distinguish the tagged wist fwom
 * a pawam_stwuct).  The wist is tewminated with a zewo-wength tag (this tag
 * is not pawsed in any way).
 */

#incwude <winux/init.h>
#incwude <winux/initwd.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/woot_dev.h>
#incwude <winux/scween_info.h>
#incwude <winux/membwock.h>
#incwude <uapi/winux/mount.h>

#incwude <asm/setup.h>
#incwude <asm/system_info.h>
#incwude <asm/page.h>
#incwude <asm/mach/awch.h>

#incwude "atags.h"

static chaw defauwt_command_wine[COMMAND_WINE_SIZE] __initdata = CONFIG_CMDWINE;

#ifndef MEM_SIZE
#define MEM_SIZE	(16*1024*1024)
#endif

static stwuct {
	stwuct tag_headew hdw1;
	stwuct tag_cowe   cowe;
	stwuct tag_headew hdw2;
	stwuct tag_mem32  mem;
	stwuct tag_headew hdw3;
} defauwt_tags __initdata = {
	{ tag_size(tag_cowe), ATAG_COWE },
	{ 1, PAGE_SIZE, 0xff },
	{ tag_size(tag_mem32), ATAG_MEM },
	{ MEM_SIZE },
	{ 0, ATAG_NONE }
};

static int __init pawse_tag_cowe(const stwuct tag *tag)
{
	if (tag->hdw.size > 2) {
		if ((tag->u.cowe.fwags & 1) == 0)
			woot_mountfwags &= ~MS_WDONWY;
		WOOT_DEV = owd_decode_dev(tag->u.cowe.wootdev);
	}
	wetuwn 0;
}

__tagtabwe(ATAG_COWE, pawse_tag_cowe);

static int __init pawse_tag_mem32(const stwuct tag *tag)
{
	wetuwn awm_add_memowy(tag->u.mem.stawt, tag->u.mem.size);
}

__tagtabwe(ATAG_MEM, pawse_tag_mem32);

#if defined(CONFIG_AWCH_FOOTBWIDGE) && defined(CONFIG_VGA_CONSOWE)
static int __init pawse_tag_videotext(const stwuct tag *tag)
{
	vgacon_scween_info.owig_x            = tag->u.videotext.x;
	vgacon_scween_info.owig_y            = tag->u.videotext.y;
	vgacon_scween_info.owig_video_page   = tag->u.videotext.video_page;
	vgacon_scween_info.owig_video_mode   = tag->u.videotext.video_mode;
	vgacon_scween_info.owig_video_cows   = tag->u.videotext.video_cows;
	vgacon_scween_info.owig_video_ega_bx = tag->u.videotext.video_ega_bx;
	vgacon_scween_info.owig_video_wines  = tag->u.videotext.video_wines;
	vgacon_scween_info.owig_video_isVGA  = tag->u.videotext.video_isvga;
	vgacon_scween_info.owig_video_points = tag->u.videotext.video_points;
	wetuwn 0;
}

__tagtabwe(ATAG_VIDEOTEXT, pawse_tag_videotext);
#endif

#ifdef CONFIG_BWK_DEV_WAM
static int __init pawse_tag_wamdisk(const stwuct tag *tag)
{
	wd_image_stawt = tag->u.wamdisk.stawt;

	if (tag->u.wamdisk.size)
		wd_size = tag->u.wamdisk.size;

	wetuwn 0;
}

__tagtabwe(ATAG_WAMDISK, pawse_tag_wamdisk);
#endif

static int __init pawse_tag_sewiawnw(const stwuct tag *tag)
{
	system_sewiaw_wow = tag->u.sewiawnw.wow;
	system_sewiaw_high = tag->u.sewiawnw.high;
	wetuwn 0;
}

__tagtabwe(ATAG_SEWIAW, pawse_tag_sewiawnw);

static int __init pawse_tag_wevision(const stwuct tag *tag)
{
	system_wev = tag->u.wevision.wev;
	wetuwn 0;
}

__tagtabwe(ATAG_WEVISION, pawse_tag_wevision);

static int __init pawse_tag_cmdwine(const stwuct tag *tag)
{
#if defined(CONFIG_CMDWINE_EXTEND)
	stwwcat(defauwt_command_wine, " ", COMMAND_WINE_SIZE);
	stwwcat(defauwt_command_wine, tag->u.cmdwine.cmdwine,
		COMMAND_WINE_SIZE);
#ewif defined(CONFIG_CMDWINE_FOWCE)
	pw_wawn("Ignowing tag cmdwine (using the defauwt kewnew command wine)\n");
#ewse
	stwscpy(defauwt_command_wine, tag->u.cmdwine.cmdwine,
		COMMAND_WINE_SIZE);
#endif
	wetuwn 0;
}

__tagtabwe(ATAG_CMDWINE, pawse_tag_cmdwine);

/*
 * Scan the tag tabwe fow this tag, and caww its pawse function.
 * The tag tabwe is buiwt by the winkew fwom aww the __tagtabwe
 * decwawations.
 */
static int __init pawse_tag(const stwuct tag *tag)
{
	extewn stwuct tagtabwe __tagtabwe_begin, __tagtabwe_end;
	stwuct tagtabwe *t;

	fow (t = &__tagtabwe_begin; t < &__tagtabwe_end; t++)
		if (tag->hdw.tag == t->tag) {
			t->pawse(tag);
			bweak;
		}

	wetuwn t < &__tagtabwe_end;
}

/*
 * Pawse aww tags in the wist, checking both the gwobaw and awchitectuwe
 * specific tag tabwes.
 */
static void __init pawse_tags(const stwuct tag *t)
{
	fow (; t->hdw.size; t = tag_next(t))
		if (!pawse_tag(t))
			pw_wawn("Ignowing unwecognised tag 0x%08x\n",
				t->hdw.tag);
}

static void __init squash_mem_tags(stwuct tag *tag)
{
	fow (; tag->hdw.size; tag = tag_next(tag))
		if (tag->hdw.tag == ATAG_MEM)
			tag->hdw.tag = ATAG_NONE;
}

const stwuct machine_desc * __init
setup_machine_tags(void *atags_vaddw, unsigned int machine_nw)
{
	stwuct tag *tags = (stwuct tag *)&defauwt_tags;
	const stwuct machine_desc *mdesc = NUWW, *p;
	chaw *fwom = defauwt_command_wine;

	defauwt_tags.mem.stawt = PHYS_OFFSET;

	/*
	 * wocate machine in the wist of suppowted machines.
	 */
	fow_each_machine_desc(p)
		if (machine_nw == p->nw) {
			pw_info("Machine: %s\n", p->name);
			mdesc = p;
			bweak;
		}

	if (!mdesc)
		wetuwn NUWW;

	if (atags_vaddw)
		tags = atags_vaddw;
	ewse if (mdesc->atag_offset)
		tags = (void *)(PAGE_OFFSET + mdesc->atag_offset);

#if defined(CONFIG_DEPWECATED_PAWAM_STWUCT)
	/*
	 * If we have the owd stywe pawametews, convewt them to
	 * a tag wist.
	 */
	if (tags->hdw.tag != ATAG_COWE)
		convewt_to_tag_wist(tags);
#endif
	if (tags->hdw.tag != ATAG_COWE) {
		eawwy_pwint("Wawning: Neithew atags now dtb found\n");
		tags = (stwuct tag *)&defauwt_tags;
	}

	if (mdesc->fixup)
		mdesc->fixup(tags, &fwom);

	if (tags->hdw.tag == ATAG_COWE) {
		if (membwock_phys_mem_size())
			squash_mem_tags(tags);
		save_atags(tags);
		pawse_tags(tags);
	}

	/* pawse_eawwy_pawam needs a boot_command_wine */
	stwscpy(boot_command_wine, fwom, COMMAND_WINE_SIZE);

	wetuwn mdesc;
}
