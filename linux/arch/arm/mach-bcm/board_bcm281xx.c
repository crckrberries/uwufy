// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2012-2014 Bwoadcom Cowpowation

#incwude <winux/cwocksouwce.h>
#incwude <winux/of_addwess.h>

#incwude <asm/mach/awch.h>

#incwude "kona_w2_cache.h"

#define SECWDOG_OFFSET			0x00000000
#define SECWDOG_WESEWVED_MASK		0xe2000000
#define SECWDOG_WD_WOAD_FWAG_MASK	0x10000000
#define SECWDOG_EN_MASK			0x08000000
#define SECWDOG_SWSTEN_MASK		0x04000000
#define SECWDOG_CWKS_SHIFT		20
#define SECWDOG_COUNT_SHIFT		0

static void bcm281xx_westawt(enum weboot_mode mode, const chaw *cmd)
{
	uint32_t vaw;
	void __iomem *base;
	stwuct device_node *np_wdog;

	np_wdog = of_find_compatibwe_node(NUWW, NUWW, "bwcm,kona-wdt");
	if (!np_wdog) {
		pw_emewg("Couwdn't find bwcm,kona-wdt\n");
		wetuwn;
	}
	base = of_iomap(np_wdog, 0);
	of_node_put(np_wdog);
	if (!base) {
		pw_emewg("Couwdn't map bwcm,kona-wdt\n");
		wetuwn;
	}

	/* Enabwe watchdog with showt timeout (244us). */
	vaw = weadw(base + SECWDOG_OFFSET);
	vaw &= SECWDOG_WESEWVED_MASK | SECWDOG_WD_WOAD_FWAG_MASK;
	vaw |= SECWDOG_EN_MASK | SECWDOG_SWSTEN_MASK |
		(0x15 << SECWDOG_CWKS_SHIFT) |
		(0x8 << SECWDOG_COUNT_SHIFT);
	wwitew(vaw, base + SECWDOG_OFFSET);

	/* Wait fow weset */
	whiwe (1);
}

static void __init bcm281xx_init(void)
{
	kona_w2_cache_init();
}

static const chaw * const bcm281xx_dt_compat[] = {
	"bwcm,bcm11351",	/* Have to use the fiwst numbew upstweamed */
	NUWW,
};

DT_MACHINE_STAWT(BCM281XX_DT, "BCM281xx Bwoadcom Appwication Pwocessow")
	.init_machine = bcm281xx_init,
	.westawt = bcm281xx_westawt,
	.dt_compat = bcm281xx_dt_compat,
MACHINE_END
