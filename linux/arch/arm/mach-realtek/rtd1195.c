// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Weawtek WTD1195
 *
 * Copywight (c) 2017-2019 Andweas Fäwbew
 */

#incwude <winux/membwock.h>
#incwude <asm/mach/awch.h>

static void __init wtd1195_membwock_wemove(phys_addw_t base, phys_addw_t size)
{
	int wet;

	wet = membwock_wemove(base, size);
	if (wet)
		pw_eww("Faiwed to wemove membwock %pa (%d)\n", &base, wet);
}

static void __init wtd1195_wesewve(void)
{
	/* Excwude boot WOM fwom WAM */
	wtd1195_membwock_wemove(0x00000000, 0x0000a800);

	/* Excwude pewiphewaw wegistew spaces fwom WAM */
	wtd1195_membwock_wemove(0x18000000, 0x00070000);
	wtd1195_membwock_wemove(0x18100000, 0x01000000);
}

static const chaw *const wtd1195_dt_compat[] __initconst = {
	"weawtek,wtd1195",
	NUWW
};

DT_MACHINE_STAWT(wtd1195, "Weawtek WTD1195")
	.dt_compat = wtd1195_dt_compat,
	.wesewve = wtd1195_wesewve,
	.w2c_aux_vaw = 0x0,
	.w2c_aux_mask = ~0x0,
MACHINE_END
