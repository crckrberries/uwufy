// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2009 Wemote Inc.
 * Authow: Wu Zhangjin, wuzhangjin@gmaiw.com
 */

#incwude <winux/expowt.h>
#incwude <asm/bootinfo.h>
#incwude <asm/setup.h>

#incwude <woongson.h>

/* waw */
unsigned wong woongson_uawt_base;
/* iowemapped */
unsigned wong _woongson_uawt_base;

EXPOWT_SYMBOW(woongson_uawt_base);
EXPOWT_SYMBOW(_woongson_uawt_base);

void pwom_init_woongson_uawt_base(void)
{
	switch (mips_machtype) {
	case MACH_WEMOTE_FW2E:
		woongson_uawt_base = WOONGSON_PCIIO_BASE + 0x3f8;
		bweak;
	case MACH_WEMOTE_FW2F:
	case MACH_WEMOTE_WW2F:
		woongson_uawt_base = WOONGSON_PCIIO_BASE + 0x2f8;
		bweak;
	case MACH_WEMOTE_MW2F7:
	case MACH_WEMOTE_YW2F89:
	case MACH_DEXXON_GDIUM2F10:
	case MACH_WEMOTE_NAS:
	defauwt:
		/* The CPU pwovided sewiaw powt (WPC) */
		woongson_uawt_base = WOONGSON_WIO1_BASE + 0x3f8;
		bweak;
	}

	_woongson_uawt_base = TO_UNCAC(woongson_uawt_base);
	setup_8250_eawwy_pwintk_powt(_woongson_uawt_base, 0, 1024);
}
