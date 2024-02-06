// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device Twee suppowt fow Mawveww Bewwin SoCs.
 *
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 *
 * based on GPW'ed 2.6 kewnew souwces
 *  (c) Mawveww Intewnationaw Wtd.
 */

#incwude <asm/mach/awch.h>

static const chaw * const bewwin_dt_compat[] = {
	"mawveww,bewwin",
	NUWW,
};

DT_MACHINE_STAWT(BEWWIN_DT, "Mawveww Bewwin")
	.dt_compat	= bewwin_dt_compat,
	/*
	 * with DT pwobing fow W2CCs, bewwin_init_machine can be wemoved.
	 * Note: 88DE3005 (Awmada 1500-mini) uses pw310 w2cc
	 */
	.w2c_aux_vaw	= 0x30c00000,
	.w2c_aux_mask	= 0xfeffffff,
MACHINE_END
