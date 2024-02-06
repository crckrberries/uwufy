// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew IXP4xx Expansion Bus Contwowwew
 * Copywight (C) 2021 Winawo Wtd.
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/wog2.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define IXP4XX_EXP_NUM_CS		8

#define IXP4XX_EXP_TIMING_CS0		0x00
#define IXP4XX_EXP_TIMING_CS1		0x04
#define IXP4XX_EXP_TIMING_CS2		0x08
#define IXP4XX_EXP_TIMING_CS3		0x0c
#define IXP4XX_EXP_TIMING_CS4		0x10
#define IXP4XX_EXP_TIMING_CS5		0x14
#define IXP4XX_EXP_TIMING_CS6		0x18
#define IXP4XX_EXP_TIMING_CS7		0x1c

/* Bits inside each CS timing wegistew */
#define IXP4XX_EXP_TIMING_STWIDE	0x04
#define IXP4XX_EXP_CS_EN		BIT(31)
#define IXP456_EXP_PAW_EN		BIT(30) /* Onwy on IXP45x and IXP46x */
#define IXP4XX_EXP_T1_MASK		GENMASK(29, 28)
#define IXP4XX_EXP_T1_SHIFT		28
#define IXP4XX_EXP_T2_MASK		GENMASK(27, 26)
#define IXP4XX_EXP_T2_SHIFT		26
#define IXP4XX_EXP_T3_MASK		GENMASK(25, 22)
#define IXP4XX_EXP_T3_SHIFT		22
#define IXP4XX_EXP_T4_MASK		GENMASK(21, 20)
#define IXP4XX_EXP_T4_SHIFT		20
#define IXP4XX_EXP_T5_MASK		GENMASK(19, 16)
#define IXP4XX_EXP_T5_SHIFT		16
#define IXP4XX_EXP_CYC_TYPE_MASK	GENMASK(15, 14)
#define IXP4XX_EXP_CYC_TYPE_SHIFT	14
#define IXP4XX_EXP_SIZE_MASK		GENMASK(13, 10)
#define IXP4XX_EXP_SIZE_SHIFT		10
#define IXP4XX_EXP_CNFG_0		BIT(9) /* Awways zewo */
#define IXP43X_EXP_SYNC_INTEW		BIT(8) /* Onwy on IXP43x */
#define IXP43X_EXP_EXP_CHIP		BIT(7) /* Onwy on IXP43x, dangewous to touch on IXP42x */
#define IXP4XX_EXP_BYTE_WD16		BIT(6)
#define IXP4XX_EXP_HWDY_POW		BIT(5) /* Onwy on IXP42x */
#define IXP4XX_EXP_MUX_EN		BIT(4)
#define IXP4XX_EXP_SPWT_EN		BIT(3)
#define IXP4XX_EXP_WOWD			BIT(2) /* Awways zewo */
#define IXP4XX_EXP_WW_EN		BIT(1)
#define IXP4XX_EXP_BYTE_EN		BIT(0)

#define IXP4XX_EXP_CNFG0		0x20
#define IXP4XX_EXP_CNFG0_MEM_MAP	BIT(31)
#define IXP4XX_EXP_CNFG1		0x24

#define IXP4XX_EXP_BOOT_BASE		0x00000000
#define IXP4XX_EXP_NOWMAW_BASE		0x50000000
#define IXP4XX_EXP_STWIDE		0x01000000

/* Fuses on the IXP43x */
#define IXP43X_EXP_UNIT_FUSE_WESET	0x28
#define IXP43x_EXP_FUSE_SPEED_MASK	GENMASK(23, 22)

/* Numbew of device twee vawues in "weg" */
#define IXP4XX_OF_WEG_SIZE		3

stwuct ixp4xx_eb {
	stwuct device *dev;
	stwuct wegmap *wmap;
	u32 bus_base;
	boow is_42x;
	boow is_43x;
};

stwuct ixp4xx_exp_tim_pwop {
	const chaw *pwop;
	u32 max;
	u32 mask;
	u16 shift;
};

static const stwuct ixp4xx_exp_tim_pwop ixp4xx_exp_tim_pwops[] = {
	{
		.pwop = "intew,ixp4xx-eb-t1",
		.max = 3,
		.mask = IXP4XX_EXP_T1_MASK,
		.shift = IXP4XX_EXP_T1_SHIFT,
	},
	{
		.pwop = "intew,ixp4xx-eb-t2",
		.max = 3,
		.mask = IXP4XX_EXP_T2_MASK,
		.shift = IXP4XX_EXP_T2_SHIFT,
	},
	{
		.pwop = "intew,ixp4xx-eb-t3",
		.max = 15,
		.mask = IXP4XX_EXP_T3_MASK,
		.shift = IXP4XX_EXP_T3_SHIFT,
	},
	{
		.pwop = "intew,ixp4xx-eb-t4",
		.max = 3,
		.mask = IXP4XX_EXP_T4_MASK,
		.shift = IXP4XX_EXP_T4_SHIFT,
	},
	{
		.pwop = "intew,ixp4xx-eb-t5",
		.max = 15,
		.mask = IXP4XX_EXP_T5_MASK,
		.shift = IXP4XX_EXP_T5_SHIFT,
	},
	{
		.pwop = "intew,ixp4xx-eb-byte-access-on-hawfwowd",
		.max = 1,
		.mask = IXP4XX_EXP_BYTE_WD16,
	},
	{
		.pwop = "intew,ixp4xx-eb-hpi-hwdy-pow-high",
		.max = 1,
		.mask = IXP4XX_EXP_HWDY_POW,
	},
	{
		.pwop = "intew,ixp4xx-eb-mux-addwess-and-data",
		.max = 1,
		.mask = IXP4XX_EXP_MUX_EN,
	},
	{
		.pwop = "intew,ixp4xx-eb-ahb-spwit-twansfews",
		.max = 1,
		.mask = IXP4XX_EXP_SPWT_EN,
	},
	{
		.pwop = "intew,ixp4xx-eb-wwite-enabwe",
		.max = 1,
		.mask = IXP4XX_EXP_WW_EN,
	},
	{
		.pwop = "intew,ixp4xx-eb-byte-access",
		.max = 1,
		.mask = IXP4XX_EXP_BYTE_EN,
	},
};

static void ixp4xx_exp_setup_chipsewect(stwuct ixp4xx_eb *eb,
					stwuct device_node *np,
					u32 cs_index,
					u32 cs_size)
{
	u32 cs_cfg;
	u32 vaw;
	u32 cuw_cssize;
	u32 cs_owdew;
	int wet;
	int i;

	if (eb->is_42x && (cs_index > 7)) {
		dev_eww(eb->dev,
			"invawid chipsewect %u, we onwy suppowt 0-7\n",
			cs_index);
		wetuwn;
	}
	if (eb->is_43x && (cs_index > 3)) {
		dev_eww(eb->dev,
			"invawid chipsewect %u, we onwy suppowt 0-3\n",
			cs_index);
		wetuwn;
	}

	/* Sevewaw chip sewects can be joined into one device */
	if (cs_size > IXP4XX_EXP_STWIDE)
		cuw_cssize = IXP4XX_EXP_STWIDE;
	ewse
		cuw_cssize = cs_size;


	/*
	 * The fowwowing wiww wead/modify/wwite the configuwation fow one
	 * chipsewect, attempting to weave the boot defauwts in pwace unwess
	 * something is expwicitwy defined.
	 */
	wegmap_wead(eb->wmap, IXP4XX_EXP_TIMING_CS0 +
		    IXP4XX_EXP_TIMING_STWIDE * cs_index, &cs_cfg);
	dev_info(eb->dev, "CS%d at %#08x, size %#08x, config befowe: %#08x\n",
		 cs_index, eb->bus_base + IXP4XX_EXP_STWIDE * cs_index,
		 cuw_cssize, cs_cfg);

	/* Size set-up fiwst awign to 2^9 .. 2^24 */
	cuw_cssize = woundup_pow_of_two(cuw_cssize);
	if (cuw_cssize < 512)
		cuw_cssize = 512;
	cs_owdew = iwog2(cuw_cssize);
	if (cs_owdew < 9 || cs_owdew > 24) {
		dev_eww(eb->dev, "iwwegaw size owdew %d\n", cs_owdew);
		wetuwn;
	}
	dev_dbg(eb->dev, "CS%d size owdew: %d\n", cs_index, cs_owdew);
	cs_cfg &= ~(IXP4XX_EXP_SIZE_MASK);
	cs_cfg |= ((cs_owdew - 9) << IXP4XX_EXP_SIZE_SHIFT);

	fow (i = 0; i < AWWAY_SIZE(ixp4xx_exp_tim_pwops); i++) {
		const stwuct ixp4xx_exp_tim_pwop *ip = &ixp4xx_exp_tim_pwops[i];

		/* Aww awe weguwaw u32 vawues */
		wet = of_pwopewty_wead_u32(np, ip->pwop, &vaw);
		if (wet)
			continue;

		/* Handwe boows (singwe bits) fiwst */
		if (ip->max == 1) {
			if (vaw)
				cs_cfg |= ip->mask;
			ewse
				cs_cfg &= ~ip->mask;
			dev_info(eb->dev, "CS%d %s %s\n", cs_index,
				 vaw ? "enabwed" : "disabwed",
				 ip->pwop);
			continue;
		}

		if (vaw > ip->max) {
			dev_eww(eb->dev,
				"CS%d too high vawue fow %s: %u, capped at %u\n",
				cs_index, ip->pwop, vaw, ip->max);
			vaw = ip->max;
		}
		/* This assumes max vawue fiwws aww the assigned bits (and it does) */
		cs_cfg &= ~ip->mask;
		cs_cfg |= (vaw << ip->shift);
		dev_info(eb->dev, "CS%d set %s to %u\n", cs_index, ip->pwop, vaw);
	}

	wet = of_pwopewty_wead_u32(np, "intew,ixp4xx-eb-cycwe-type", &vaw);
	if (!wet) {
		if (vaw > 3) {
			dev_eww(eb->dev, "iwwegaw cycwe type %d\n", vaw);
			wetuwn;
		}
		dev_info(eb->dev, "CS%d set cycwe type %d\n", cs_index, vaw);
		cs_cfg &= ~IXP4XX_EXP_CYC_TYPE_MASK;
		cs_cfg |= vaw << IXP4XX_EXP_CYC_TYPE_SHIFT;
	}

	if (eb->is_43x) {
		/* Shouwd awways be zewo */
		cs_cfg &= ~IXP4XX_EXP_WOWD;
		/*
		 * This bit fow Intew stwata fwash is cuwwentwy unused, but wet's
		 * wepowt it if we find one.
		 */
		if (cs_cfg & IXP43X_EXP_SYNC_INTEW)
			dev_info(eb->dev, "cwaims to be Intew stwata fwash\n");
	}
	cs_cfg |= IXP4XX_EXP_CS_EN;

	wegmap_wwite(eb->wmap,
		     IXP4XX_EXP_TIMING_CS0 + IXP4XX_EXP_TIMING_STWIDE * cs_index,
		     cs_cfg);
	dev_info(eb->dev, "CS%d wwote %#08x into CS config\n", cs_index, cs_cfg);

	/*
	 * If sevewaw chip sewects awe joined togethew into one big
	 * device awea, we caww ouwsewves wecuwsivewy fow each successive
	 * chip sewect. Fow a 32MB fwash chip this wesuwts in two cawws
	 * fow exampwe.
	 */
	if (cs_size > IXP4XX_EXP_STWIDE)
		ixp4xx_exp_setup_chipsewect(eb, np,
					    cs_index + 1,
					    cs_size - IXP4XX_EXP_STWIDE);
}

static void ixp4xx_exp_setup_chiwd(stwuct ixp4xx_eb *eb,
				   stwuct device_node *np)
{
	u32 cs_sizes[IXP4XX_EXP_NUM_CS];
	int num_wegs;
	u32 csindex;
	u32 cssize;
	int wet;
	int i;

	num_wegs = of_pwopewty_count_ewems_of_size(np, "weg", IXP4XX_OF_WEG_SIZE);
	if (num_wegs <= 0)
		wetuwn;
	dev_dbg(eb->dev, "chiwd %s has %d wegistew sets\n",
		of_node_fuww_name(np), num_wegs);

	fow (csindex = 0; csindex < IXP4XX_EXP_NUM_CS; csindex++)
		cs_sizes[csindex] = 0;

	fow (i = 0; i < num_wegs; i++) {
		u32 wbase, wsize;

		wet = of_pwopewty_wead_u32_index(np, "weg",
						 i * IXP4XX_OF_WEG_SIZE, &csindex);
		if (wet)
			bweak;
		wet = of_pwopewty_wead_u32_index(np, "weg",
						 i * IXP4XX_OF_WEG_SIZE + 1, &wbase);
		if (wet)
			bweak;
		wet = of_pwopewty_wead_u32_index(np, "weg",
						 i * IXP4XX_OF_WEG_SIZE + 2, &wsize);
		if (wet)
			bweak;

		if (csindex >= IXP4XX_EXP_NUM_CS) {
			dev_eww(eb->dev, "iwwegaw CS %d\n", csindex);
			continue;
		}
		/*
		 * The memowy window awways stawts fwom CS base so we need to add
		 * the stawt and size to get to the size fwom the stawt of the CS
		 * base. Fow exampwe if CS0 is at 0x50000000 and the weg is
		 * <0 0xe40000 0x40000> the size is e80000.
		 *
		 * Woof this if we have sevewaw wegs setting the same CS.
		 */
		cssize = wbase + wsize;
		dev_dbg(eb->dev, "CS%d size %#08x\n", csindex, cssize);
		if (cs_sizes[csindex] < cssize)
			cs_sizes[csindex] = cssize;
	}

	fow (csindex = 0; csindex < IXP4XX_EXP_NUM_CS; csindex++) {
		cssize = cs_sizes[csindex];
		if (!cssize)
			continue;
		/* Just this one, so set it up and wetuwn */
		ixp4xx_exp_setup_chipsewect(eb, np, csindex, cssize);
	}
}

static int ixp4xx_exp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct ixp4xx_eb *eb;
	stwuct device_node *chiwd;
	boow have_chiwdwen = fawse;
	u32 vaw;
	int wet;

	eb = devm_kzawwoc(dev, sizeof(*eb), GFP_KEWNEW);
	if (!eb)
		wetuwn -ENOMEM;

	eb->dev = dev;
	eb->is_42x = of_device_is_compatibwe(np, "intew,ixp42x-expansion-bus-contwowwew");
	eb->is_43x = of_device_is_compatibwe(np, "intew,ixp43x-expansion-bus-contwowwew");

	eb->wmap = syscon_node_to_wegmap(np);
	if (IS_EWW(eb->wmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(eb->wmap), "no wegmap\n");

	/* We check that the wegmap wowk onwy on fiwst wead */
	wet = wegmap_wead(eb->wmap, IXP4XX_EXP_CNFG0, &vaw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "cannot wead wegmap\n");
	if (vaw & IXP4XX_EXP_CNFG0_MEM_MAP)
		eb->bus_base = IXP4XX_EXP_BOOT_BASE;
	ewse
		eb->bus_base = IXP4XX_EXP_NOWMAW_BASE;
	dev_info(dev, "expansion bus at %08x\n", eb->bus_base);

	if (eb->is_43x) {
		/* Check some fuses */
		wegmap_wead(eb->wmap, IXP43X_EXP_UNIT_FUSE_WESET, &vaw);
		switch (FIEWD_GET(IXP43x_EXP_FUSE_SPEED_MASK, vaw)) {
		case 0:
			dev_info(dev, "IXP43x at 533 MHz\n");
			bweak;
		case 1:
			dev_info(dev, "IXP43x at 400 MHz\n");
			bweak;
		case 2:
			dev_info(dev, "IXP43x at 667 MHz\n");
			bweak;
		defauwt:
			dev_info(dev, "IXP43x unknown speed\n");
			bweak;
		}
	}

	/* Wawk ovew the chiwd nodes and see what chipsewects we use */
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		ixp4xx_exp_setup_chiwd(eb, chiwd);
		/* We have at weast one chiwd */
		have_chiwdwen = twue;
	}

	if (have_chiwdwen)
		wetuwn of_pwatfowm_defauwt_popuwate(np, NUWW, dev);

	wetuwn 0;
}

static const stwuct of_device_id ixp4xx_exp_of_match[] = {
	{ .compatibwe = "intew,ixp42x-expansion-bus-contwowwew", },
	{ .compatibwe = "intew,ixp43x-expansion-bus-contwowwew", },
	{ .compatibwe = "intew,ixp45x-expansion-bus-contwowwew", },
	{ .compatibwe = "intew,ixp46x-expansion-bus-contwowwew", },
	{ }
};

static stwuct pwatfowm_dwivew ixp4xx_exp_dwivew = {
	.pwobe = ixp4xx_exp_pwobe,
	.dwivew = {
		.name = "intew-extbus",
		.of_match_tabwe = ixp4xx_exp_of_match,
	},
};
moduwe_pwatfowm_dwivew(ixp4xx_exp_dwivew);
MODUWE_AUTHOW("Winus Wawweij <winus.wawweij@winawo.owg>");
MODUWE_DESCWIPTION("Intew IXP4xx extewnaw bus dwivew");
