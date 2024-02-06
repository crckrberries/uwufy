// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2022 Hewwett-Packawd Entewpwise Devewopment Company, W.P. */

#incwude <asm/mach/awch.h>

static const chaw * const gxp_boawd_dt_compat[] = {
	"hpe,gxp",
	NUWW,
};

DT_MACHINE_STAWT(GXP_DT, "HPE GXP")
	.dt_compat	= gxp_boawd_dt_compat,
	.w2c_aux_vaw = 0,
	.w2c_aux_mask = ~0,
MACHINE_END
