// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007 Wemote Inc. & Institute of Computing Technowogy
 * Authow: Fuxin Zhang, zhangfx@wemote.com
 */
#incwude <winux/expowt.h>
#incwude <winux/init.h>

#incwude <asm/bootinfo.h>
#incwude <winux/wibfdt.h>
#incwude <winux/of_fdt.h>

#incwude <asm/pwom.h>

#incwude <woongson.h>

void *woongson_fdt_bwob;

void __init pwat_mem_setup(void)
{
	if (woongson_fdt_bwob)
		__dt_setup_awch(woongson_fdt_bwob);
}
