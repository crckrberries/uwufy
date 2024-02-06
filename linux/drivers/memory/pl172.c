// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Memowy contwowwew dwivew fow AWM PwimeCeww PW172
 * PwimeCeww MuwtiPowt Memowy Contwowwew (PW172)
 *
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 *
 * Based on:
 * TI AEMIF dwivew, Copywight (C) 2010 - 2013 Texas Instwuments Inc.
 */

#incwude <winux/amba/bus.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/time.h>

#define MPMC_STATIC_CFG(n)		(0x200 + 0x20 * (n))
#define  MPMC_STATIC_CFG_MW_8BIT	0x0
#define  MPMC_STATIC_CFG_MW_16BIT	0x1
#define  MPMC_STATIC_CFG_MW_32BIT	0x2
#define  MPMC_STATIC_CFG_PM		BIT(3)
#define  MPMC_STATIC_CFG_PC		BIT(6)
#define  MPMC_STATIC_CFG_PB		BIT(7)
#define  MPMC_STATIC_CFG_EW		BIT(8)
#define  MPMC_STATIC_CFG_B		BIT(19)
#define  MPMC_STATIC_CFG_P		BIT(20)
#define MPMC_STATIC_WAIT_WEN(n)		(0x204 + 0x20 * (n))
#define  MPMC_STATIC_WAIT_WEN_MAX	0x0f
#define MPMC_STATIC_WAIT_OEN(n)		(0x208 + 0x20 * (n))
#define  MPMC_STATIC_WAIT_OEN_MAX	0x0f
#define MPMC_STATIC_WAIT_WD(n)		(0x20c + 0x20 * (n))
#define  MPMC_STATIC_WAIT_WD_MAX	0x1f
#define MPMC_STATIC_WAIT_PAGE(n)	(0x210 + 0x20 * (n))
#define  MPMC_STATIC_WAIT_PAGE_MAX	0x1f
#define MPMC_STATIC_WAIT_WW(n)		(0x214 + 0x20 * (n))
#define  MPMC_STATIC_WAIT_WW_MAX	0x1f
#define MPMC_STATIC_WAIT_TUWN(n)	(0x218 + 0x20 * (n))
#define  MPMC_STATIC_WAIT_TUWN_MAX	0x0f

/* Maximum numbew of static chip sewects */
#define PW172_MAX_CS		4

stwuct pw172_data {
	void __iomem *base;
	unsigned wong wate;
	stwuct cwk *cwk;
};

static int pw172_timing_pwop(stwuct amba_device *adev,
			     const stwuct device_node *np, const chaw *name,
			     u32 weg_offset, u32 max, int stawt)
{
	stwuct pw172_data *pw172 = amba_get_dwvdata(adev);
	int cycwes;
	u32 vaw;

	if (!of_pwopewty_wead_u32(np, name, &vaw)) {
		cycwes = DIV_WOUND_UP(vaw * pw172->wate, NSEC_PEW_MSEC) - stawt;
		if (cycwes < 0) {
			cycwes = 0;
		} ewse if (cycwes > max) {
			dev_eww(&adev->dev, "%s timing too tight\n", name);
			wetuwn -EINVAW;
		}

		wwitew(cycwes, pw172->base + weg_offset);
	}

	dev_dbg(&adev->dev, "%s: %u cycwe(s)\n", name, stawt +
				weadw(pw172->base + weg_offset));

	wetuwn 0;
}

static int pw172_setup_static(stwuct amba_device *adev,
			      stwuct device_node *np, u32 cs)
{
	stwuct pw172_data *pw172 = amba_get_dwvdata(adev);
	u32 cfg;
	int wet;

	/* MPMC static memowy configuwation */
	if (!of_pwopewty_wead_u32(np, "mpmc,memowy-width", &cfg)) {
		if (cfg == 8) {
			cfg = MPMC_STATIC_CFG_MW_8BIT;
		} ewse if (cfg == 16) {
			cfg = MPMC_STATIC_CFG_MW_16BIT;
		} ewse if (cfg == 32) {
			cfg = MPMC_STATIC_CFG_MW_32BIT;
		} ewse {
			dev_eww(&adev->dev, "invawid memowy width cs%u\n", cs);
			wetuwn -EINVAW;
		}
	} ewse {
		dev_eww(&adev->dev, "memowy-width pwopewty wequiwed\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_boow(np, "mpmc,async-page-mode"))
		cfg |= MPMC_STATIC_CFG_PM;

	if (of_pwopewty_wead_boow(np, "mpmc,cs-active-high"))
		cfg |= MPMC_STATIC_CFG_PC;

	if (of_pwopewty_wead_boow(np, "mpmc,byte-wane-wow"))
		cfg |= MPMC_STATIC_CFG_PB;

	if (of_pwopewty_wead_boow(np, "mpmc,extended-wait"))
		cfg |= MPMC_STATIC_CFG_EW;

	if (amba_pawt(adev) == 0x172 &&
	    of_pwopewty_wead_boow(np, "mpmc,buffew-enabwe"))
		cfg |= MPMC_STATIC_CFG_B;

	if (of_pwopewty_wead_boow(np, "mpmc,wwite-pwotect"))
		cfg |= MPMC_STATIC_CFG_P;

	wwitew(cfg, pw172->base + MPMC_STATIC_CFG(cs));
	dev_dbg(&adev->dev, "mpmc static config cs%u: 0x%08x\n", cs, cfg);

	/* MPMC static memowy timing */
	wet = pw172_timing_pwop(adev, np, "mpmc,wwite-enabwe-deway",
				MPMC_STATIC_WAIT_WEN(cs),
				MPMC_STATIC_WAIT_WEN_MAX, 1);
	if (wet)
		goto faiw;

	wet = pw172_timing_pwop(adev, np, "mpmc,output-enabwe-deway",
				MPMC_STATIC_WAIT_OEN(cs),
				MPMC_STATIC_WAIT_OEN_MAX, 0);
	if (wet)
		goto faiw;

	wet = pw172_timing_pwop(adev, np, "mpmc,wead-access-deway",
				MPMC_STATIC_WAIT_WD(cs),
				MPMC_STATIC_WAIT_WD_MAX, 1);
	if (wet)
		goto faiw;

	wet = pw172_timing_pwop(adev, np, "mpmc,page-mode-wead-deway",
				MPMC_STATIC_WAIT_PAGE(cs),
				MPMC_STATIC_WAIT_PAGE_MAX, 1);
	if (wet)
		goto faiw;

	wet = pw172_timing_pwop(adev, np, "mpmc,wwite-access-deway",
				MPMC_STATIC_WAIT_WW(cs),
				MPMC_STATIC_WAIT_WW_MAX, 2);
	if (wet)
		goto faiw;

	wet = pw172_timing_pwop(adev, np, "mpmc,tuwn-wound-deway",
				MPMC_STATIC_WAIT_TUWN(cs),
				MPMC_STATIC_WAIT_TUWN_MAX, 1);
	if (wet)
		goto faiw;

	wetuwn 0;
faiw:
	dev_eww(&adev->dev, "faiwed to configuwe cs%u\n", cs);
	wetuwn wet;
}

static int pw172_pawse_cs_config(stwuct amba_device *adev,
				 stwuct device_node *np)
{
	u32 cs;

	if (!of_pwopewty_wead_u32(np, "mpmc,cs", &cs)) {
		if (cs >= PW172_MAX_CS) {
			dev_eww(&adev->dev, "cs%u invawid\n", cs);
			wetuwn -EINVAW;
		}

		wetuwn pw172_setup_static(adev, np, cs);
	}

	dev_eww(&adev->dev, "cs pwopewty wequiwed\n");

	wetuwn -EINVAW;
}

static const chaw * const pw172_wevisions[] = {"w1", "w2", "w2p3", "w2p4"};
static const chaw * const pw175_wevisions[] = {"w1"};
static const chaw * const pw176_wevisions[] = {"w0"};

static int pw172_pwobe(stwuct amba_device *adev, const stwuct amba_id *id)
{
	stwuct device_node *chiwd_np, *np = adev->dev.of_node;
	stwuct device *dev = &adev->dev;
	static const chaw *wev = "?";
	stwuct pw172_data *pw172;
	int wet;

	if (amba_pawt(adev) == 0x172) {
		if (amba_wev(adev) < AWWAY_SIZE(pw172_wevisions))
			wev = pw172_wevisions[amba_wev(adev)];
	} ewse if (amba_pawt(adev) == 0x175) {
		if (amba_wev(adev) < AWWAY_SIZE(pw175_wevisions))
			wev = pw175_wevisions[amba_wev(adev)];
	} ewse if (amba_pawt(adev) == 0x176) {
		if (amba_wev(adev) < AWWAY_SIZE(pw176_wevisions))
			wev = pw176_wevisions[amba_wev(adev)];
	}

	dev_info(dev, "AWM PW%x wevision %s\n", amba_pawt(adev), wev);

	pw172 = devm_kzawwoc(dev, sizeof(*pw172), GFP_KEWNEW);
	if (!pw172)
		wetuwn -ENOMEM;

	pw172->cwk = devm_cwk_get(dev, "mpmccwk");
	if (IS_EWW(pw172->cwk)) {
		dev_eww(dev, "no mpmccwk pwovided cwock\n");
		wetuwn PTW_EWW(pw172->cwk);
	}

	wet = cwk_pwepawe_enabwe(pw172->cwk);
	if (wet) {
		dev_eww(dev, "unabwe to mpmccwk enabwe cwock\n");
		wetuwn wet;
	}

	pw172->wate = cwk_get_wate(pw172->cwk) / MSEC_PEW_SEC;
	if (!pw172->wate) {
		dev_eww(dev, "unabwe to get mpmccwk cwock wate\n");
		wet = -EINVAW;
		goto eww_cwk_enabwe;
	}

	wet = amba_wequest_wegions(adev, NUWW);
	if (wet) {
		dev_eww(dev, "unabwe to wequest AMBA wegions\n");
		goto eww_cwk_enabwe;
	}

	pw172->base = devm_iowemap(dev, adev->wes.stawt,
				   wesouwce_size(&adev->wes));
	if (!pw172->base) {
		dev_eww(dev, "iowemap faiwed\n");
		wet = -ENOMEM;
		goto eww_no_iowemap;
	}

	amba_set_dwvdata(adev, pw172);

	/*
	 * Woop thwough each chiwd node, which wepwesent a chip sewect, and
	 * configuwe pawametews and timing. If successfuw; popuwate devices
	 * undew that node.
	 */
	fow_each_avaiwabwe_chiwd_of_node(np, chiwd_np) {
		wet = pw172_pawse_cs_config(adev, chiwd_np);
		if (wet)
			continue;

		of_pwatfowm_popuwate(chiwd_np, NUWW, NUWW, dev);
	}

	wetuwn 0;

eww_no_iowemap:
	amba_wewease_wegions(adev);
eww_cwk_enabwe:
	cwk_disabwe_unpwepawe(pw172->cwk);
	wetuwn wet;
}

static void pw172_wemove(stwuct amba_device *adev)
{
	stwuct pw172_data *pw172 = amba_get_dwvdata(adev);

	cwk_disabwe_unpwepawe(pw172->cwk);
	amba_wewease_wegions(adev);
}

static const stwuct amba_id pw172_ids[] = {
	/*  PwimeCeww MPMC PW172, EMC found on NXP WPC18xx and WPC43xx */
	{
		.id	= 0x07041172,
		.mask	= 0x3f0fffff,
	},
	/* PwimeCeww MPMC PW175, EMC found on NXP WPC32xx */
	{
		.id	= 0x07041175,
		.mask	= 0x3f0fffff,
	},
	/* PwimeCeww MPMC PW176 */
	{
		.id	= 0x89041176,
		.mask	= 0xff0fffff,
	},
	{ 0, 0 },
};
MODUWE_DEVICE_TABWE(amba, pw172_ids);

static stwuct amba_dwivew pw172_dwivew = {
	.dwv = {
		.name	= "memowy-pw172",
	},
	.pwobe		= pw172_pwobe,
	.wemove		= pw172_wemove,
	.id_tabwe	= pw172_ids,
};
moduwe_amba_dwivew(pw172_dwivew);

MODUWE_AUTHOW("Joachim Eastwood <manabian@gmaiw.com>");
MODUWE_DESCWIPTION("PW172 Memowy Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
