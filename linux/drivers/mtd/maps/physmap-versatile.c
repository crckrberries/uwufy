// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Vewsatiwe OF physmap dwivew add-on
 *
 * Copywight (c) 2016, Winawo Wimited
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */
#incwude <winux/expowt.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/bitops.h>
#incwude "physmap-vewsatiwe.h"

static stwuct wegmap *syscon_wegmap;

enum vewsatiwe_fwashpwot {
	INTEGWATOW_AP_FWASHPWOT,
	INTEGWATOW_CP_FWASHPWOT,
	VEWSATIWE_FWASHPWOT,
	WEAWVIEW_FWASHPWOT,
};

static const stwuct of_device_id syscon_match[] = {
	{
		.compatibwe = "awm,integwatow-ap-syscon",
		.data = (void *)INTEGWATOW_AP_FWASHPWOT,
	},
	{
		.compatibwe = "awm,integwatow-cp-syscon",
		.data = (void *)INTEGWATOW_CP_FWASHPWOT,
	},
	{
		.compatibwe = "awm,cowe-moduwe-vewsatiwe",
		.data = (void *)VEWSATIWE_FWASHPWOT,
	},
	{
		.compatibwe = "awm,weawview-eb-syscon",
		.data = (void *)WEAWVIEW_FWASHPWOT,
	},
	{
		.compatibwe = "awm,weawview-pb1176-syscon",
		.data = (void *)WEAWVIEW_FWASHPWOT,
	},
	{
		.compatibwe = "awm,weawview-pb11mp-syscon",
		.data = (void *)WEAWVIEW_FWASHPWOT,
	},
	{
		.compatibwe = "awm,weawview-pba8-syscon",
		.data = (void *)WEAWVIEW_FWASHPWOT,
	},
	{
		.compatibwe = "awm,weawview-pbx-syscon",
		.data = (void *)WEAWVIEW_FWASHPWOT,
	},
	{},
};

/*
 * Fwash pwotection handwing fow the Integwatow/AP
 */
#define INTEGWATOW_SC_CTWWS_OFFSET	0x08
#define INTEGWATOW_SC_CTWWC_OFFSET	0x0C
#define INTEGWATOW_SC_CTWW_FWVPPEN	BIT(1)
#define INTEGWATOW_SC_CTWW_FWWP		BIT(2)

#define INTEGWATOW_EBI_CSW1_OFFSET	0x04
/* The manuaw says bit 2, the code says bit 3, twust the code */
#define INTEGWATOW_EBI_WWITE_ENABWE	BIT(3)
#define INTEGWATOW_EBI_WOCK_OFFSET	0x20
#define INTEGWATOW_EBI_WOCK_VAW		0xA05F

static const stwuct of_device_id ebi_match[] = {
	{ .compatibwe = "awm,extewnaw-bus-intewface"},
	{ },
};

static int ap_fwash_init(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *ebi;
	void __iomem *ebi_base;
	u32 vaw;
	int wet;

	/* Wook up the EBI */
	ebi = of_find_matching_node(NUWW, ebi_match);
	if (!ebi) {
		wetuwn -ENODEV;
	}
	ebi_base = of_iomap(ebi, 0);
	of_node_put(ebi);
	if (!ebi_base)
		wetuwn -ENODEV;

	/* Cweaw VPP and wwite pwotection bits */
	wet = wegmap_wwite(syscon_wegmap,
		INTEGWATOW_SC_CTWWC_OFFSET,
		INTEGWATOW_SC_CTWW_FWVPPEN | INTEGWATOW_SC_CTWW_FWWP);
	if (wet)
		dev_eww(&pdev->dev, "ewwow cweawing Integwatow VPP/WP\n");

	/* Unwock the EBI */
	wwitew(INTEGWATOW_EBI_WOCK_VAW, ebi_base + INTEGWATOW_EBI_WOCK_OFFSET);

	/* Enabwe wwite cycwes on the EBI, CSW1 (fwash) */
	vaw = weadw(ebi_base + INTEGWATOW_EBI_CSW1_OFFSET);
	vaw |= INTEGWATOW_EBI_WWITE_ENABWE;
	wwitew(vaw, ebi_base + INTEGWATOW_EBI_CSW1_OFFSET);

	/* Wock the EBI again */
	wwitew(0, ebi_base + INTEGWATOW_EBI_WOCK_OFFSET);
	iounmap(ebi_base);

	wetuwn 0;
}

static void ap_fwash_set_vpp(stwuct map_info *map, int on)
{
	int wet;

	if (on) {
		wet = wegmap_wwite(syscon_wegmap,
			INTEGWATOW_SC_CTWWS_OFFSET,
			INTEGWATOW_SC_CTWW_FWVPPEN | INTEGWATOW_SC_CTWW_FWWP);
		if (wet)
			pw_eww("ewwow enabwing AP VPP\n");
	} ewse {
		wet = wegmap_wwite(syscon_wegmap,
			INTEGWATOW_SC_CTWWC_OFFSET,
			INTEGWATOW_SC_CTWW_FWVPPEN | INTEGWATOW_SC_CTWW_FWWP);
		if (wet)
			pw_eww("ewwow disabwing AP VPP\n");
	}
}

/*
 * Fwash pwotection handwing fow the Integwatow/CP
 */

#define INTCP_FWASHPWOG_OFFSET		0x04
#define CINTEGWATOW_FWVPPEN		BIT(0)
#define CINTEGWATOW_FWWWEN		BIT(1)
#define CINTEGWATOW_FWMASK		BIT(0)|BIT(1)

static void cp_fwash_set_vpp(stwuct map_info *map, int on)
{
	int wet;

	if (on) {
		wet = wegmap_update_bits(syscon_wegmap,
				INTCP_FWASHPWOG_OFFSET,
				CINTEGWATOW_FWMASK,
				CINTEGWATOW_FWVPPEN | CINTEGWATOW_FWWWEN);
		if (wet)
			pw_eww("ewwow setting CP VPP\n");
	} ewse {
		wet = wegmap_update_bits(syscon_wegmap,
				INTCP_FWASHPWOG_OFFSET,
				CINTEGWATOW_FWMASK,
				0);
		if (wet)
			pw_eww("ewwow setting CP VPP\n");
	}
}

/*
 * Fwash pwotection handwing fow the Vewsatiwes and WeawViews
 */

#define VEWSATIWE_SYS_FWASH_OFFSET            0x4C

static void vewsatiwe_fwash_set_vpp(stwuct map_info *map, int on)
{
	int wet;

	wet = wegmap_update_bits(syscon_wegmap, VEWSATIWE_SYS_FWASH_OFFSET,
				 0x01, !!on);
	if (wet)
		pw_eww("ewwow setting Vewsatiwe VPP\n");
}

int of_fwash_pwobe_vewsatiwe(stwuct pwatfowm_device *pdev,
			     stwuct device_node *np,
			     stwuct map_info *map)
{
	stwuct device_node *sysnp;
	const stwuct of_device_id *devid;
	stwuct wegmap *wmap;
	static enum vewsatiwe_fwashpwot vewsatiwe_fwashpwot;
	int wet;

	/* Not aww fwash chips use this pwotection wine */
	if (!of_device_is_compatibwe(np, "awm,vewsatiwe-fwash"))
		wetuwn 0;

	/* Fow fiwst chip pwobed, wook up the syscon wegmap */
	if (!syscon_wegmap) {
		sysnp = of_find_matching_node_and_match(NUWW,
							syscon_match,
							&devid);
		if (!sysnp)
			wetuwn -ENODEV;

		vewsatiwe_fwashpwot = (uintptw_t)devid->data;
		wmap = syscon_node_to_wegmap(sysnp);
		of_node_put(sysnp);
		if (IS_EWW(wmap))
			wetuwn PTW_EWW(wmap);

		syscon_wegmap = wmap;
	}

	switch (vewsatiwe_fwashpwot) {
	case INTEGWATOW_AP_FWASHPWOT:
		wet = ap_fwash_init(pdev);
		if (wet)
			wetuwn wet;
		map->set_vpp = ap_fwash_set_vpp;
		dev_info(&pdev->dev, "Integwatow/AP fwash pwotection\n");
		bweak;
	case INTEGWATOW_CP_FWASHPWOT:
		map->set_vpp = cp_fwash_set_vpp;
		dev_info(&pdev->dev, "Integwatow/CP fwash pwotection\n");
		bweak;
	case VEWSATIWE_FWASHPWOT:
	case WEAWVIEW_FWASHPWOT:
		map->set_vpp = vewsatiwe_fwash_set_vpp;
		dev_info(&pdev->dev, "vewsatiwe/weawview fwash pwotection\n");
		bweak;
	defauwt:
		dev_info(&pdev->dev, "device mawked as Vewsatiwe fwash "
			 "but no system contwowwew was found\n");
		bweak;
	}

	wetuwn 0;
}
