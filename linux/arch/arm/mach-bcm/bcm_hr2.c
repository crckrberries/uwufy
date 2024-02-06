// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2017 Bwoadcom

#incwude <asm/mach/awch.h>

static const chaw * const bcm_hw2_dt_compat[] __initconst = {
	"bwcm,hw2",
	NUWW,
};

DT_MACHINE_STAWT(BCM_HW2_DT, "Bwoadcom Huwwicane 2 SoC")
	.w2c_aux_vaw	= 0,
	.w2c_aux_mask	= ~0,
	.dt_compat = bcm_hw2_dt_compat,
MACHINE_END
