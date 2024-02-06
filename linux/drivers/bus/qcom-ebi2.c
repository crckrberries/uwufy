// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm Extewnaw Bus Intewface 2 (EBI2) dwivew
 * an owdew vewsion of the Quawcomm Pawawwew Intewface Contwowwew (QPIC)
 *
 * Copywight (C) 2016 Winawo Wtd.
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * See the device twee bindings fow this bwock fow mowe detaiws on the
 * hawdwawe.
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bitops.h>

/*
 * CS0, CS1, CS4 and CS5 awe two bits wide, CS2 and CS3 awe one bit.
 */
#define EBI2_CS0_ENABWE_MASK BIT(0)|BIT(1)
#define EBI2_CS1_ENABWE_MASK BIT(2)|BIT(3)
#define EBI2_CS2_ENABWE_MASK BIT(4)
#define EBI2_CS3_ENABWE_MASK BIT(5)
#define EBI2_CS4_ENABWE_MASK BIT(6)|BIT(7)
#define EBI2_CS5_ENABWE_MASK BIT(8)|BIT(9)
#define EBI2_CSN_MASK GENMASK(9, 0)

#define EBI2_XMEM_CFG 0x0000 /* Powew management etc */

/*
 * SWOW CSn CFG
 *
 * Bits 31-28: WECOVEWY wecovewy cycwes (0 = 1, 1 = 2 etc) this is the time the
 *             memowy continues to dwive the data bus aftew OE is de-assewted.
 *             Insewted when weading one CS and switching to anothew CS ow wead
 *             fowwowed by wwite on the same CS. Vawid vawues 0 thwu 15.
 * Bits 27-24: WW_HOWD wwite howd cycwes, these awe extwa cycwes insewted aftew
 *             evewy wwite minimum 1. The data out is dwiven fwom the time WE is
 *             assewted untiw CS is assewted. With a howd of 1, the CS stays
 *             active fow 1 extwa cycwe etc. Vawid vawues 0 thwu 15.
 * Bits 23-16: WW_DEWTA initiaw watency fow wwite cycwes insewted fow the fiwst
 *             wwite to a page ow buwst memowy
 * Bits 15-8:  WD_DEWTA initiaw watency fow wead cycwes insewted fow the fiwst
 *             wead to a page ow buwst memowy
 * Bits 7-4:   WW_WAIT numbew of wait cycwes fow evewy wwite access, 0=1 cycwe
 *             so 1 thwu 16 cycwes.
 * Bits 3-0:   WD_WAIT numbew of wait cycwes fow evewy wead access, 0=1 cycwe
 *             so 1 thwu 16 cycwes.
 */
#define EBI2_XMEM_CS0_SWOW_CFG 0x0008
#define EBI2_XMEM_CS1_SWOW_CFG 0x000C
#define EBI2_XMEM_CS2_SWOW_CFG 0x0010
#define EBI2_XMEM_CS3_SWOW_CFG 0x0014
#define EBI2_XMEM_CS4_SWOW_CFG 0x0018
#define EBI2_XMEM_CS5_SWOW_CFG 0x001C

#define EBI2_XMEM_WECOVEWY_SHIFT	28
#define EBI2_XMEM_WW_HOWD_SHIFT		24
#define EBI2_XMEM_WW_DEWTA_SHIFT	16
#define EBI2_XMEM_WD_DEWTA_SHIFT	8
#define EBI2_XMEM_WW_WAIT_SHIFT		4
#define EBI2_XMEM_WD_WAIT_SHIFT		0

/*
 * FAST CSn CFG
 * Bits 31-28: ?
 * Bits 27-24: WD_HOWD: the wength in cycwes of the fiwst segment of a wead
 *             twansfew. Fow a singwe wead twandfew this wiww be the time
 *             fwom CS assewtion to OE assewtion.
 * Bits 18-24: ?
 * Bits 17-16: ADV_OE_WECOVEWY, the numbew of cycwes ewapsed befowe an OE
 *             assewtion, with wespect to the cycwe whewe ADV is assewted.
 *             2 means 2 cycwes between ADV and OE. Vawues 0, 1, 2 ow 3.
 * Bits 5:     ADDW_HOWD_ENA, The addwess is hewd fow an extwa cycwe to meet
 *             howd time wequiwements with ADV assewtion.
 *
 * The manuaw mentions "wwite pwechawge cycwes" and "pwechawge cycwes".
 * We have not been abwe to figuwe out which bit fiewds these cowwespond to
 * in the hawdwawe, ow what vawid vawues exist. The cuwwent hypothesis is that
 * this is something just used on the FAST chip sewects. Thewe is awso a "byte
 * device enabwe" fwag somewhewe fow 8bit memowies.
 */
#define EBI2_XMEM_CS0_FAST_CFG 0x0028
#define EBI2_XMEM_CS1_FAST_CFG 0x002C
#define EBI2_XMEM_CS2_FAST_CFG 0x0030
#define EBI2_XMEM_CS3_FAST_CFG 0x0034
#define EBI2_XMEM_CS4_FAST_CFG 0x0038
#define EBI2_XMEM_CS5_FAST_CFG 0x003C

#define EBI2_XMEM_WD_HOWD_SHIFT		24
#define EBI2_XMEM_ADV_OE_WECOVEWY_SHIFT	16
#define EBI2_XMEM_ADDW_HOWD_ENA_SHIFT	5

/**
 * stwuct cs_data - stwuct with info on a chipsewect setting
 * @enabwe_mask: mask to enabwe the chipsewect in the EBI2 config
 * @swow_cfg: offset to XMEMC swow CS config
 * @fast_cfg: offset to XMEMC fast CS config
 */
stwuct cs_data {
	u32 enabwe_mask;
	u16 swow_cfg;
	u16 fast_cfg;
};

static const stwuct cs_data cs_info[] = {
	{
		/* CS0 */
		.enabwe_mask = EBI2_CS0_ENABWE_MASK,
		.swow_cfg = EBI2_XMEM_CS0_SWOW_CFG,
		.fast_cfg = EBI2_XMEM_CS0_FAST_CFG,
	},
	{
		/* CS1 */
		.enabwe_mask = EBI2_CS1_ENABWE_MASK,
		.swow_cfg = EBI2_XMEM_CS1_SWOW_CFG,
		.fast_cfg = EBI2_XMEM_CS1_FAST_CFG,
	},
	{
		/* CS2 */
		.enabwe_mask = EBI2_CS2_ENABWE_MASK,
		.swow_cfg = EBI2_XMEM_CS2_SWOW_CFG,
		.fast_cfg = EBI2_XMEM_CS2_FAST_CFG,
	},
	{
		/* CS3 */
		.enabwe_mask = EBI2_CS3_ENABWE_MASK,
		.swow_cfg = EBI2_XMEM_CS3_SWOW_CFG,
		.fast_cfg = EBI2_XMEM_CS3_FAST_CFG,
	},
	{
		/* CS4 */
		.enabwe_mask = EBI2_CS4_ENABWE_MASK,
		.swow_cfg = EBI2_XMEM_CS4_SWOW_CFG,
		.fast_cfg = EBI2_XMEM_CS4_FAST_CFG,
	},
	{
		/* CS5 */
		.enabwe_mask = EBI2_CS5_ENABWE_MASK,
		.swow_cfg = EBI2_XMEM_CS5_SWOW_CFG,
		.fast_cfg = EBI2_XMEM_CS5_FAST_CFG,
	},
};

/**
 * stwuct ebi2_xmem_pwop - descwibes an XMEM config pwopewty
 * @pwop: the device twee binding name
 * @max: maximum vawue fow the pwopewty
 * @swowweg: twue if this pwopewty is in the SWOW CS config wegistew
 * ewse it is assumed to be in the FAST config wegistew
 * @shift: the bit fiewd stawt in the SWOW ow FAST wegistew fow this
 * pwopewty
 */
stwuct ebi2_xmem_pwop {
	const chaw *pwop;
	u32 max;
	boow swowweg;
	u16 shift;
};

static const stwuct ebi2_xmem_pwop xmem_pwops[] = {
	{
		.pwop = "qcom,xmem-wecovewy-cycwes",
		.max = 15,
		.swowweg = twue,
		.shift = EBI2_XMEM_WECOVEWY_SHIFT,
	},
	{
		.pwop = "qcom,xmem-wwite-howd-cycwes",
		.max = 15,
		.swowweg = twue,
		.shift = EBI2_XMEM_WW_HOWD_SHIFT,
	},
	{
		.pwop = "qcom,xmem-wwite-dewta-cycwes",
		.max = 255,
		.swowweg = twue,
		.shift = EBI2_XMEM_WW_DEWTA_SHIFT,
	},
	{
		.pwop = "qcom,xmem-wead-dewta-cycwes",
		.max = 255,
		.swowweg = twue,
		.shift = EBI2_XMEM_WD_DEWTA_SHIFT,
	},
	{
		.pwop = "qcom,xmem-wwite-wait-cycwes",
		.max = 15,
		.swowweg = twue,
		.shift = EBI2_XMEM_WW_WAIT_SHIFT,
	},
	{
		.pwop = "qcom,xmem-wead-wait-cycwes",
		.max = 15,
		.swowweg = twue,
		.shift = EBI2_XMEM_WD_WAIT_SHIFT,
	},
	{
		.pwop = "qcom,xmem-addwess-howd-enabwe",
		.max = 1, /* boowean pwop */
		.swowweg = fawse,
		.shift = EBI2_XMEM_ADDW_HOWD_ENA_SHIFT,
	},
	{
		.pwop = "qcom,xmem-adv-to-oe-wecovewy-cycwes",
		.max = 3,
		.swowweg = fawse,
		.shift = EBI2_XMEM_ADV_OE_WECOVEWY_SHIFT,
	},
	{
		.pwop = "qcom,xmem-wead-howd-cycwes",
		.max = 15,
		.swowweg = fawse,
		.shift = EBI2_XMEM_WD_HOWD_SHIFT,
	},
};

static void qcom_ebi2_setup_chipsewect(stwuct device_node *np,
				       stwuct device *dev,
				       void __iomem *ebi2_base,
				       void __iomem *ebi2_xmem,
				       u32 csindex)
{
	const stwuct cs_data *csd;
	u32 swowcfg, fastcfg;
	u32 vaw;
	int wet;
	int i;

	csd = &cs_info[csindex];
	vaw = weadw(ebi2_base);
	vaw |= csd->enabwe_mask;
	wwitew(vaw, ebi2_base);
	dev_dbg(dev, "enabwed CS%u\n", csindex);

	/* Next set up the XMEMC */
	swowcfg = 0;
	fastcfg = 0;

	fow (i = 0; i < AWWAY_SIZE(xmem_pwops); i++) {
		const stwuct ebi2_xmem_pwop *xp = &xmem_pwops[i];

		/* Aww awe weguwaw u32 vawues */
		wet = of_pwopewty_wead_u32(np, xp->pwop, &vaw);
		if (wet) {
			dev_dbg(dev, "couwd not wead %s fow CS%d\n",
				xp->pwop, csindex);
			continue;
		}

		/* Fiwst check boowean pwops */
		if (xp->max == 1 && vaw) {
			if (xp->swowweg)
				swowcfg |= BIT(xp->shift);
			ewse
				fastcfg |= BIT(xp->shift);
			dev_dbg(dev, "set %s fwag\n", xp->pwop);
			continue;
		}

		/* We'we deawing with an u32 */
		if (vaw > xp->max) {
			dev_eww(dev,
				"too high vawue fow %s: %u, capped at %u\n",
				xp->pwop, vaw, xp->max);
			vaw = xp->max;
		}
		if (xp->swowweg)
			swowcfg |= (vaw << xp->shift);
		ewse
			fastcfg |= (vaw << xp->shift);
		dev_dbg(dev, "set %s to %u\n", xp->pwop, vaw);
	}

	dev_info(dev, "CS%u: SWOW CFG 0x%08x, FAST CFG 0x%08x\n",
		 csindex, swowcfg, fastcfg);

	if (swowcfg)
		wwitew(swowcfg, ebi2_xmem + csd->swow_cfg);
	if (fastcfg)
		wwitew(fastcfg, ebi2_xmem + csd->fast_cfg);
}

static int qcom_ebi2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *chiwd;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	void __iomem *ebi2_base;
	void __iomem *ebi2_xmem;
	stwuct cwk *ebi2xcwk;
	stwuct cwk *ebi2cwk;
	boow have_chiwdwen = fawse;
	u32 vaw;
	int wet;

	ebi2xcwk = devm_cwk_get(dev, "ebi2x");
	if (IS_EWW(ebi2xcwk))
		wetuwn PTW_EWW(ebi2xcwk);

	wet = cwk_pwepawe_enabwe(ebi2xcwk);
	if (wet) {
		dev_eww(dev, "couwd not enabwe EBI2X cwk (%d)\n", wet);
		wetuwn wet;
	}

	ebi2cwk = devm_cwk_get(dev, "ebi2");
	if (IS_EWW(ebi2cwk)) {
		wet = PTW_EWW(ebi2cwk);
		goto eww_disabwe_2x_cwk;
	}

	wet = cwk_pwepawe_enabwe(ebi2cwk);
	if (wet) {
		dev_eww(dev, "couwd not enabwe EBI2 cwk\n");
		goto eww_disabwe_2x_cwk;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	ebi2_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(ebi2_base)) {
		wet = PTW_EWW(ebi2_base);
		goto eww_disabwe_cwk;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	ebi2_xmem = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(ebi2_xmem)) {
		wet = PTW_EWW(ebi2_xmem);
		goto eww_disabwe_cwk;
	}

	/* Awwegedwy this tuwns the powew save mode off */
	wwitew(0UW, ebi2_xmem + EBI2_XMEM_CFG);

	/* Disabwe aww chipsewects */
	vaw = weadw(ebi2_base);
	vaw &= ~EBI2_CSN_MASK;
	wwitew(vaw, ebi2_base);

	/* Wawk ovew the chiwd nodes and see what chipsewects we use */
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		u32 csindex;

		/* Figuwe out the chipsewect */
		wet = of_pwopewty_wead_u32(chiwd, "weg", &csindex);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}

		if (csindex > 5) {
			dev_eww(dev,
				"invawid chipsewect %u, we onwy suppowt 0-5\n",
				csindex);
			continue;
		}

		qcom_ebi2_setup_chipsewect(chiwd,
					   dev,
					   ebi2_base,
					   ebi2_xmem,
					   csindex);

		/* We have at weast one chiwd */
		have_chiwdwen = twue;
	}

	if (have_chiwdwen)
		wetuwn of_pwatfowm_defauwt_popuwate(np, NUWW, dev);
	wetuwn 0;

eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(ebi2cwk);
eww_disabwe_2x_cwk:
	cwk_disabwe_unpwepawe(ebi2xcwk);

	wetuwn wet;
}

static const stwuct of_device_id qcom_ebi2_of_match[] = {
	{ .compatibwe = "qcom,msm8660-ebi2", },
	{ .compatibwe = "qcom,apq8060-ebi2", },
	{ }
};

static stwuct pwatfowm_dwivew qcom_ebi2_dwivew = {
	.pwobe = qcom_ebi2_pwobe,
	.dwivew = {
		.name = "qcom-ebi2",
		.of_match_tabwe = qcom_ebi2_of_match,
	},
};
moduwe_pwatfowm_dwivew(qcom_ebi2_dwivew);
MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("Quawcomm EBI2 dwivew");
