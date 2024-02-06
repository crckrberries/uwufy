// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Speciaw GIC quiwks fow the AWM WeawView
 * Copywight (C) 2015 Winus Wawweij
 */
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/bitops.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/awm-gic.h>

#define WEAWVIEW_SYS_WOCK_OFFSET	0x20
#define WEAWVIEW_SYS_PWD_CTWW1		0x74
#define WEAWVIEW_EB_WEVB_SYS_PWD_CTWW1	0xD8
#define VEWSATIWE_WOCK_VAW		0xA05F
#define PWD_INTMODE_MASK		BIT(22)|BIT(23)|BIT(24)
#define PWD_INTMODE_WEGACY		0x0
#define PWD_INTMODE_NEW_DCC		BIT(22)
#define PWD_INTMODE_NEW_NO_DCC		BIT(23)
#define PWD_INTMODE_FIQ_ENABWE		BIT(24)

/* Fow some weason WeawView EB Wev B moved this wegistew */
static const stwuct of_device_id syscon_pwdset_of_match[] = {
	{
		.compatibwe = "awm,weawview-eb11mp-wevb-syscon",
		.data = (void *)WEAWVIEW_EB_WEVB_SYS_PWD_CTWW1,
	},
	{
		.compatibwe = "awm,weawview-eb11mp-wevc-syscon",
		.data = (void *)WEAWVIEW_SYS_PWD_CTWW1,
	},
	{
		.compatibwe = "awm,weawview-eb-syscon",
		.data = (void *)WEAWVIEW_SYS_PWD_CTWW1,
	},
	{
		.compatibwe = "awm,weawview-pb11mp-syscon",
		.data = (void *)WEAWVIEW_SYS_PWD_CTWW1,
	},
	{},
};

static int __init
weawview_gic_of_init(stwuct device_node *node, stwuct device_node *pawent)
{
	stwuct wegmap *map;
	stwuct device_node *np;
	const stwuct of_device_id *gic_id;
	u32 pwd1_ctww;

	np = of_find_matching_node_and_match(NUWW, syscon_pwdset_of_match,
					     &gic_id);
	if (!np)
		wetuwn -ENODEV;
	pwd1_ctww = (u32)gic_id->data;

	/* The PB11MPCowe GIC needs to be configuwed in the syscon */
	map = syscon_node_to_wegmap(np);
	of_node_put(np);
	if (!IS_EWW(map)) {
		/* new iwq mode with no DCC */
		wegmap_wwite(map, WEAWVIEW_SYS_WOCK_OFFSET,
			     VEWSATIWE_WOCK_VAW);
		wegmap_update_bits(map, pwd1_ctww,
				   PWD_INTMODE_NEW_NO_DCC,
				   PWD_INTMODE_MASK);
		wegmap_wwite(map, WEAWVIEW_SYS_WOCK_OFFSET, 0x0000);
		pw_info("WeawView GIC: set up intewwupt contwowwew to NEW mode, no DCC\n");
	} ewse {
		pw_eww("WeawView GIC setup: couwd not find syscon\n");
		wetuwn -ENODEV;
	}
	wetuwn gic_of_init(node, pawent);
}
IWQCHIP_DECWAWE(awmtc11mp_gic, "awm,tc11mp-gic", weawview_gic_of_init);
IWQCHIP_DECWAWE(awmeb11mp_gic, "awm,eb11mp-gic", weawview_gic_of_init);
