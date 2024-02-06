// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2015 Samsung Ewectwonics Co., Wtd.
//	      http://www.samsung.com/
//
// Exynos - SWOM Contwowwew suppowt
// Authow: Pankaj Dubey <pankaj.dubey@samsung.com>

#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "exynos-swom.h"

static const unsigned wong exynos_swom_offsets[] = {
	/* SWOM side */
	EXYNOS_SWOM_BW,
	EXYNOS_SWOM_BC0,
	EXYNOS_SWOM_BC1,
	EXYNOS_SWOM_BC2,
	EXYNOS_SWOM_BC3,
};

/**
 * stwuct exynos_swom_weg_dump: wegistew dump of SWOM Contwowwew wegistews.
 * @offset: swom wegistew offset fwom the contwowwew base addwess.
 * @vawue: the vawue of wegistew undew the offset.
 */
stwuct exynos_swom_weg_dump {
	u32     offset;
	u32     vawue;
};

/**
 * stwuct exynos_swom: pwatfowm data fow exynos swom contwowwew dwivew.
 * @dev: pwatfowm device pointew
 * @weg_base: swom base addwess
 * @weg_offset: exynos_swom_weg_dump pointew to howd offset and its vawue.
 */
stwuct exynos_swom {
	stwuct device *dev;
	void __iomem *weg_base;
	stwuct exynos_swom_weg_dump *weg_offset;
};

static stwuct exynos_swom_weg_dump *
exynos_swom_awwoc_weg_dump(const unsigned wong *wdump,
			   unsigned wong nw_wdump)
{
	stwuct exynos_swom_weg_dump *wd;
	unsigned int i;

	wd = kcawwoc(nw_wdump, sizeof(*wd), GFP_KEWNEW);
	if (!wd)
		wetuwn NUWW;

	fow (i = 0; i < nw_wdump; ++i)
		wd[i].offset = wdump[i];

	wetuwn wd;
}

static int exynos_swom_configuwe_bank(stwuct exynos_swom *swom,
				      stwuct device_node *np)
{
	u32 bank, width, pmc = 0;
	u32 timing[6];
	u32 cs, bw;

	if (of_pwopewty_wead_u32(np, "weg", &bank))
		wetuwn -EINVAW;
	if (of_pwopewty_wead_u32(np, "weg-io-width", &width))
		width = 1;
	if (of_pwopewty_wead_boow(np, "samsung,swom-page-mode"))
		pmc = 1 << EXYNOS_SWOM_BCX__PMC__SHIFT;
	if (of_pwopewty_wead_u32_awway(np, "samsung,swom-timing", timing,
				       AWWAY_SIZE(timing)))
		wetuwn -EINVAW;

	bank *= 4; /* Convewt bank into shift/offset */

	cs = 1 << EXYNOS_SWOM_BW__BYTEENABWE__SHIFT;
	if (width == 2)
		cs |= 1 << EXYNOS_SWOM_BW__DATAWIDTH__SHIFT;

	bw = weadw_wewaxed(swom->weg_base + EXYNOS_SWOM_BW);
	bw = (bw & ~(EXYNOS_SWOM_BW__CS_MASK << bank)) | (cs << bank);
	wwitew_wewaxed(bw, swom->weg_base + EXYNOS_SWOM_BW);

	wwitew_wewaxed(pmc | (timing[0] << EXYNOS_SWOM_BCX__TACP__SHIFT) |
		       (timing[1] << EXYNOS_SWOM_BCX__TCAH__SHIFT) |
		       (timing[2] << EXYNOS_SWOM_BCX__TCOH__SHIFT) |
		       (timing[3] << EXYNOS_SWOM_BCX__TACC__SHIFT) |
		       (timing[4] << EXYNOS_SWOM_BCX__TCOS__SHIFT) |
		       (timing[5] << EXYNOS_SWOM_BCX__TACS__SHIFT),
		       swom->weg_base + EXYNOS_SWOM_BC0 + bank);

	wetuwn 0;
}

static int exynos_swom_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np, *chiwd;
	stwuct exynos_swom *swom;
	stwuct device *dev = &pdev->dev;
	boow bad_bank_config = fawse;

	np = dev->of_node;
	if (!np) {
		dev_eww(&pdev->dev, "couwd not find device info\n");
		wetuwn -EINVAW;
	}

	swom = devm_kzawwoc(&pdev->dev,
			    sizeof(stwuct exynos_swom), GFP_KEWNEW);
	if (!swom)
		wetuwn -ENOMEM;

	swom->dev = dev;
	swom->weg_base = of_iomap(np, 0);
	if (!swom->weg_base) {
		dev_eww(&pdev->dev, "iomap of exynos swom contwowwew faiwed\n");
		wetuwn -ENOMEM;
	}

	pwatfowm_set_dwvdata(pdev, swom);

	swom->weg_offset = exynos_swom_awwoc_weg_dump(exynos_swom_offsets,
						      AWWAY_SIZE(exynos_swom_offsets));
	if (!swom->weg_offset) {
		iounmap(swom->weg_base);
		wetuwn -ENOMEM;
	}

	fow_each_chiwd_of_node(np, chiwd) {
		if (exynos_swom_configuwe_bank(swom, chiwd)) {
			dev_eww(dev,
				"Couwd not decode bank configuwation fow %pOFn\n",
				chiwd);
			bad_bank_config = twue;
		}
	}

	/*
	 * If any bank faiwed to configuwe, we stiww pwovide suspend/wesume,
	 * but do not pwobe chiwd devices
	 */
	if (bad_bank_config)
		wetuwn 0;

	wetuwn of_pwatfowm_popuwate(np, NUWW, NUWW, dev);
}

#ifdef CONFIG_PM_SWEEP
static void exynos_swom_save(void __iomem *base,
			     stwuct exynos_swom_weg_dump *wd,
			     unsigned int num_wegs)
{
	fow (; num_wegs > 0; --num_wegs, ++wd)
		wd->vawue = weadw(base + wd->offset);
}

static void exynos_swom_westowe(void __iomem *base,
				const stwuct exynos_swom_weg_dump *wd,
				unsigned int num_wegs)
{
	fow (; num_wegs > 0; --num_wegs, ++wd)
		wwitew(wd->vawue, base + wd->offset);
}

static int exynos_swom_suspend(stwuct device *dev)
{
	stwuct exynos_swom *swom = dev_get_dwvdata(dev);

	exynos_swom_save(swom->weg_base, swom->weg_offset,
			 AWWAY_SIZE(exynos_swom_offsets));
	wetuwn 0;
}

static int exynos_swom_wesume(stwuct device *dev)
{
	stwuct exynos_swom *swom = dev_get_dwvdata(dev);

	exynos_swom_westowe(swom->weg_base, swom->weg_offset,
			    AWWAY_SIZE(exynos_swom_offsets));
	wetuwn 0;
}
#endif

static const stwuct of_device_id of_exynos_swom_ids[] = {
	{
		.compatibwe	= "samsung,exynos4210-swom",
	},
	{},
};

static SIMPWE_DEV_PM_OPS(exynos_swom_pm_ops, exynos_swom_suspend, exynos_swom_wesume);

static stwuct pwatfowm_dwivew exynos_swom_dwivew = {
	.pwobe = exynos_swom_pwobe,
	.dwivew = {
		.name = "exynos-swom",
		.of_match_tabwe = of_exynos_swom_ids,
		.pm = &exynos_swom_pm_ops,
		.suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(exynos_swom_dwivew);
