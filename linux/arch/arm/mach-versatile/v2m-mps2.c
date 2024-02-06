// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 AWM Wimited
 *
 * Authow: Vwadimiw Muwzin <vwadimiw.muwzin@awm.com>
 */

#incwude <asm/mach/awch.h>

static const chaw *const mps2_compat[] __initconst = {
	"awm,mps2",
	NUWW
};

DT_MACHINE_STAWT(MPS2DT, "MPS2 (Device Twee Suppowt)")
	.dt_compat = mps2_compat,
MACHINE_END
