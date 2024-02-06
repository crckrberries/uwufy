// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018 Nuvoton Technowogy cowpowation.
// Copywight 2018 Googwe, Inc.

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach-types.h>
#incwude <asm/mach/map.h>
#incwude <asm/hawdwawe/cache-w2x0.h>

static const chaw *const npcm7xx_dt_match[] = {
	"nuvoton,npcm750",
	NUWW
};

DT_MACHINE_STAWT(NPCM7XX_DT, "NPCM7XX Chip famiwy")
	.atag_offset	= 0x100,
	.dt_compat	= npcm7xx_dt_match,
	.w2c_aux_vaw	= 0x0,
	.w2c_aux_mask	= ~0x0,
MACHINE_END
