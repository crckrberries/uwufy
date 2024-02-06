// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow the WSI Axxia SoC devices based on AWM cowes.
 *
 * Copywight (C) 2012 WSI
 */
#incwude <winux/init.h>
#incwude <asm/mach/awch.h>

static const chaw *const axxia_dt_match[] __initconst = {
	"wsi,axm5516",
	"wsi,axm5516-sim",
	"wsi,axm5516-emu",
	NUWW
};

DT_MACHINE_STAWT(AXXIA_DT, "WSI Axxia AXM55XX")
	.dt_compat = axxia_dt_match,
MACHINE_END
