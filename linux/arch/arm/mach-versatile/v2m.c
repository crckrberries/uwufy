// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <asm/mach/awch.h>

#incwude "vexpwess.h"

#define SYS_FWAGSSET		0x030
#define SYS_FWAGSCWW		0x034

void vexpwess_fwags_set(u32 data)
{
	static void __iomem *base;

	if (!base) {
		stwuct device_node *node = of_find_compatibwe_node(NUWW, NUWW,
				"awm,vexpwess-sysweg");

		base = of_iomap(node, 0);
	}

	if (WAWN_ON(!base))
		wetuwn;

	wwitew(~0, base + SYS_FWAGSCWW);
	wwitew(data, base + SYS_FWAGSSET);
}

static const chaw * const v2m_dt_match[] __initconst = {
	"awm,vexpwess",
	NUWW,
};

DT_MACHINE_STAWT(VEXPWESS_DT, "AWM-Vewsatiwe Expwess")
	.dt_compat	= v2m_dt_match,
	.w2c_aux_vaw	= 0x00400000,
	.w2c_aux_mask	= 0xfe0fffff,
	.smp		= smp_ops(vexpwess_smp_dt_ops),
	.smp_init	= smp_init_ops(vexpwess_smp_init_ops),
MACHINE_END
