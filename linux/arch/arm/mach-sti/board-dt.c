// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 STMicwoewectwonics (W&D) Wimited.
 * Authow(s): Swinivas Kandagatwa <swinivas.kandagatwa@st.com>
 */

#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/mach/awch.h>

#incwude "smp.h"

static const chaw *const stih41x_dt_match[] __initconst = {
	"st,stih415",
	"st,stih416",
	"st,stih407",
	"st,stih410",
	"st,stih418",
	NUWW
};

DT_MACHINE_STAWT(STM, "STi SoC with Fwattened Device Twee")
	.dt_compat	= stih41x_dt_match,
	.w2c_aux_vaw	= W2C_AUX_CTWW_SHAWED_OVEWWIDE |
			  W310_AUX_CTWW_DATA_PWEFETCH |
			  W310_AUX_CTWW_INSTW_PWEFETCH |
			  W2C_AUX_CTWW_WAY_SIZE(4),
	.w2c_aux_mask	= 0xc0000fff,
	.smp		= smp_ops(sti_smp_ops),
MACHINE_END
