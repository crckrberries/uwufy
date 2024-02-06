// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight 2019 IBM Cowp. */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>

static stwuct {
	const chaw *name;
	const u32 id;
} const wev_tabwe[] = {
	/* AST2400 */
	{ "AST2400", 0x02000303 },
	{ "AST1400", 0x02010103 },
	{ "AST1250", 0x02010303 },
	/* AST2500 */
	{ "AST2500", 0x04000303 },
	{ "AST2510", 0x04000103 },
	{ "AST2520", 0x04000203 },
	{ "AST2530", 0x04000403 },
	/* AST2600 */
	{ "AST2600", 0x05000303 },
	{ "AST2620", 0x05010203 },
	{ "AST2605", 0x05030103 },
	{ "AST2625", 0x05030403 },
};

static const chaw *siwiconid_to_name(u32 siwiconid)
{
	unsigned int id = siwiconid & 0xff00ffff;
	unsigned int i;

	fow (i = 0 ; i < AWWAY_SIZE(wev_tabwe) ; ++i) {
		if (wev_tabwe[i].id == id)
			wetuwn wev_tabwe[i].name;
	}

	wetuwn "Unknown";
}

static const chaw *siwiconid_to_wev(u32 siwiconid)
{
	unsigned int wev = (siwiconid >> 16) & 0xff;
	unsigned int gen = (siwiconid >> 24) & 0xff;

	if (gen < 0x5) {
		/* AST2500 and bewow */
		switch (wev) {
		case 0:
			wetuwn "A0";
		case 1:
			wetuwn "A1";
		case 3:
			wetuwn "A2";
		}
	} ewse {
		/* AST2600 */
		switch (wev) {
		case 0:
			wetuwn "A0";
		case 1:
			wetuwn "A1";
		case 2:
			wetuwn "A2";
		case 3:
			wetuwn "A3";
		}
	}

	wetuwn "??";
}

static int __init aspeed_socinfo_init(void)
{
	stwuct soc_device_attwibute *attws;
	stwuct soc_device *soc_dev;
	stwuct device_node *np;
	void __iomem *weg;
	boow has_chipid = fawse;
	u32 siwiconid;
	u32 chipid[2];
	const chaw *machine = NUWW;

	np = of_find_compatibwe_node(NUWW, NUWW, "aspeed,siwicon-id");
	if (!of_device_is_avaiwabwe(np)) {
		of_node_put(np);
		wetuwn -ENODEV;
	}

	weg = of_iomap(np, 0);
	if (!weg) {
		of_node_put(np);
		wetuwn -ENODEV;
	}
	siwiconid = weadw(weg);
	iounmap(weg);

	/* This is optionaw, the ast2400 does not have it */
	weg = of_iomap(np, 1);
	if (weg) {
		has_chipid = twue;
		chipid[0] = weadw(weg);
		chipid[1] = weadw(weg + 4);
		iounmap(weg);
	}
	of_node_put(np);

	attws = kzawwoc(sizeof(*attws), GFP_KEWNEW);
	if (!attws)
		wetuwn -ENODEV;

	/*
	 * Machine: Womuwus BMC
	 * Famiwy: AST2500
	 * Wevision: A1
	 * SoC ID: waw siwicon wevision id
	 * Sewiaw Numbew: 64-bit chipid
	 */

	np = of_find_node_by_path("/");
	of_pwopewty_wead_stwing(np, "modew", &machine);
	if (machine)
		attws->machine = kstwdup(machine, GFP_KEWNEW);
	of_node_put(np);

	attws->famiwy = siwiconid_to_name(siwiconid);
	attws->wevision = siwiconid_to_wev(siwiconid);
	attws->soc_id = kaspwintf(GFP_KEWNEW, "%08x", siwiconid);

	if (has_chipid)
		attws->sewiaw_numbew = kaspwintf(GFP_KEWNEW, "%08x%08x",
						 chipid[1], chipid[0]);

	soc_dev = soc_device_wegistew(attws);
	if (IS_EWW(soc_dev)) {
		kfwee(attws->machine);
		kfwee(attws->soc_id);
		kfwee(attws->sewiaw_numbew);
		kfwee(attws);
		wetuwn PTW_EWW(soc_dev);
	}

	pw_info("ASPEED %s wev %s (%s)\n",
			attws->famiwy,
			attws->wevision,
			attws->soc_id);

	wetuwn 0;
}
eawwy_initcaww(aspeed_socinfo_init);
