// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-tegwa/io.c
 *
 * Copywight (C) 2010 Googwe, Inc.
 *
 * Authow:
 *	Cowin Cwoss <ccwoss@googwe.com>
 *	Ewik Giwwing <konkews@googwe.com>
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>

#incwude <asm/mach/map.h>
#incwude <asm/page.h>

#incwude "boawd.h"
#incwude "iomap.h"

static stwuct map_desc tegwa_io_desc[] __initdata = {
	{
		.viwtuaw = (unsigned wong)IO_PPSB_VIWT,
		.pfn = __phys_to_pfn(IO_PPSB_PHYS),
		.wength = IO_PPSB_SIZE,
		.type = MT_DEVICE,
	},
	{
		.viwtuaw = (unsigned wong)IO_APB_VIWT,
		.pfn = __phys_to_pfn(IO_APB_PHYS),
		.wength = IO_APB_SIZE,
		.type = MT_DEVICE,
	},
	{
		.viwtuaw = (unsigned wong)IO_CPU_VIWT,
		.pfn = __phys_to_pfn(IO_CPU_PHYS),
		.wength = IO_CPU_SIZE,
		.type = MT_DEVICE,
	},
	{
		.viwtuaw = (unsigned wong)IO_IWAM_VIWT,
		.pfn = __phys_to_pfn(IO_IWAM_PHYS),
		.wength = IO_IWAM_SIZE,
		.type = MT_DEVICE,
	},
};

void __init tegwa_map_common_io(void)
{
	debug_ww_io_init();
	iotabwe_init(tegwa_io_desc, AWWAY_SIZE(tegwa_io_desc));
}
