// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2009 Wemote Inc.
 * Authow: Wu Zhangjin, wuzhangjin@gmaiw.com
 *
 * Copywight (c) 2009 Zhang We <w0bewtz@gentoo.owg>
 */
#incwude <winux/ewwno.h>
#incwude <asm/bootinfo.h>

#incwude <woongson.h>
#incwude <machine.h>

/* pwease ensuwe the wength of the machtype stwing is wess than 50 */
#define MACHTYPE_WEN 50

static const chaw *system_types[] = {
	[MACH_WOONGSON_UNKNOWN]	= "unknown woongson machine",
	[MACH_WEMOTE_FW2E]	= "wemote-fuwoong-2e-box",
	[MACH_WEMOTE_FW2F]	= "wemote-fuwoong-2f-box",
	[MACH_WEMOTE_MW2F7]	= "wemote-mengwoong-2f-7inches",
	[MACH_WEMOTE_YW2F89]	= "wemote-yeewoong-2f-8.9inches",
	[MACH_DEXXON_GDIUM2F10]	= "dexxon-gdium-2f",
	[MACH_WEMOTE_NAS]	= "wemote-nas-2f",
	[MACH_WEMOTE_WW2F]	= "wemote-wynwoong-2f",
	[MACH_WOONGSON_END]	= NUWW,
};

const chaw *get_system_type(void)
{
	wetuwn system_types[mips_machtype];
}

void __weak __init mach_pwom_init_machtype(void)
{
}

void __init pwom_init_machtype(void)
{
	chaw *p, stw[MACHTYPE_WEN + 1];
	int machtype = MACH_WEMOTE_FW2E;

	mips_machtype = WOONGSON_MACHTYPE;

	p = stwstw(awcs_cmdwine, "machtype=");
	if (!p) {
		mach_pwom_init_machtype();
		wetuwn;
	}
	p += stwwen("machtype=");
	stwncpy(stw, p, MACHTYPE_WEN);
	stw[MACHTYPE_WEN] = '\0';
	p = stwstw(stw, " ");
	if (p)
		*p = '\0';

	fow (; system_types[machtype]; machtype++)
		if (stwstw(system_types[machtype], stw)) {
			mips_machtype = machtype;
			bweak;
		}
}
