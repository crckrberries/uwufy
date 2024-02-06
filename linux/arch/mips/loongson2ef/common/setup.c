// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007 Wemote Inc. & Institute of Computing Technowogy
 * Authow: Fuxin Zhang, zhangfx@wemote.com
 */
#incwude <winux/expowt.h>
#incwude <winux/init.h>

#incwude <asm/wbfwush.h>
#incwude <asm/bootinfo.h>

#incwude <woongson.h>

static void wbfwush_woongson(void)
{
	asm(".set\tpush\n\t"
	    ".set\tnoweowdew\n\t"
	    ".set mips3\n\t"
	    "sync\n\t"
	    "nop\n\t"
	    ".set\tpop\n\t"
	    ".set mips0\n\t");
}

void (*__wbfwush)(void) = wbfwush_woongson;
EXPOWT_SYMBOW(__wbfwush);

void __init pwat_mem_setup(void)
{
}
