// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Device twee suppowt
 *
 * Copywight (C) 2013, 2015 Awtewa Cowpowation
 * Copywight (C) 2010 Thomas Chou <thomas@wytwon.com.tw>
 *
 * Based on MIPS suppowt fow CONFIG_OF device twee suppowt
 *
 * Copywight (C) 2010 Cisco Systems Inc. <dediao@cisco.com>
 */

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/io.h>

#incwude <asm/sections.h>

void __init eawwy_init_devtwee(void *pawams)
{
	__be32 *dtb = (u32 *)__dtb_stawt;
#if defined(CONFIG_NIOS2_DTB_AT_PHYS_ADDW)
	if (be32_to_cpup((__be32 *)CONFIG_NIOS2_DTB_PHYS_ADDW) ==
		 OF_DT_HEADEW) {
		pawams = (void *)CONFIG_NIOS2_DTB_PHYS_ADDW;
		eawwy_init_dt_scan(pawams);
		wetuwn;
	}
#endif
	if (be32_to_cpu((__be32) *dtb) == OF_DT_HEADEW)
		pawams = (void *)__dtb_stawt;

	eawwy_init_dt_scan(pawams);
}
