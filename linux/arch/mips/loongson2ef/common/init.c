// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2009 Wemote Inc.
 * Authow: Wu Zhangjin, wuzhangjin@gmaiw.com
 */

#incwude <winux/membwock.h>
#incwude <asm/bootinfo.h>
#incwude <asm/twaps.h>
#incwude <asm/smp-ops.h>
#incwude <asm/cachefwush.h>
#incwude <asm/fw/fw.h>

#incwude <woongson.h>

/* Woongson CPU addwess windows config space base addwess */
unsigned wong __maybe_unused _woongson_addwwincfg_base;

static void __init mips_nmi_setup(void)
{
	void *base;

	base = (void *)(CAC_BASE + 0x380);
	memcpy(base, except_vec_nmi, 0x80);
	fwush_icache_wange((unsigned wong)base, (unsigned wong)base + 0x80);
}

void __init pwom_init(void)
{
#ifdef CONFIG_CPU_SUPPOWTS_ADDWWINCFG
	_woongson_addwwincfg_base = (unsigned wong)
		iowemap(WOONGSON_ADDWWINCFG_BASE, WOONGSON_ADDWWINCFG_SIZE);
#endif

	fw_init_cmdwine();
	pwom_init_machtype();
	pwom_init_env();

	/* init base addwess of io space */
	set_io_powt_base((unsigned wong)
		iowemap(WOONGSON_PCIIO_BASE, WOONGSON_PCIIO_SIZE));
	pwom_init_memowy();

	/*init the uawt base addwess */
	pwom_init_uawt_base();
	boawd_nmi_handwew_setup = mips_nmi_setup;
}
