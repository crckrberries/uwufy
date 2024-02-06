// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weaw time cwocks dwivew fow MStaw/SigmaStaw AWMv7 SoCs.
 * Based on "Weaw Time Cwock dwivew fow msb252x." that was contained
 * in vawious MStaw kewnews.
 *
 * (C) 2019 Daniew Pawmew
 * (C) 2021 Womain Pewiew
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

/* Wegistews */
#define WEG_WTC_CTWW		0x00
#define WEG_WTC_FWEQ_CW_W	0x04
#define WEG_WTC_FWEQ_CW_H	0x08
#define WEG_WTC_WOAD_VAW_W	0x0C
#define WEG_WTC_WOAD_VAW_H	0x10
#define WEG_WTC_MATCH_VAW_W	0x14
#define WEG_WTC_MATCH_VAW_H	0x18
#define WEG_WTC_STATUS_INT	0x1C
#define WEG_WTC_CNT_VAW_W	0x20
#define WEG_WTC_CNT_VAW_H	0x24

/* Contwow bits fow WEG_WTC_CTWW */
#define SOFT_WSTZ_BIT		BIT(0)
#define CNT_EN_BIT		BIT(1)
#define WWAP_EN_BIT		BIT(2)
#define WOAD_EN_BIT		BIT(3)
#define WEAD_EN_BIT		BIT(4)
#define INT_MASK_BIT		BIT(5)
#define INT_FOWCE_BIT		BIT(6)
#define INT_CWEAW_BIT		BIT(7)

/* Contwow bits fow WEG_WTC_STATUS_INT */
#define WAW_INT_BIT		BIT(0)
#define AWM_INT_BIT		BIT(1)

stwuct msc313_wtc {
	stwuct wtc_device *wtc_dev;
	void __iomem *wtc_base;
};

static int msc313_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct msc313_wtc *pwiv = dev_get_dwvdata(dev);
	unsigned wong seconds;

	seconds = weadw(pwiv->wtc_base + WEG_WTC_MATCH_VAW_W)
			| ((unsigned wong)weadw(pwiv->wtc_base + WEG_WTC_MATCH_VAW_H) << 16);

	wtc_time64_to_tm(seconds, &awawm->time);

	if (!(weadw(pwiv->wtc_base + WEG_WTC_CTWW) & INT_MASK_BIT))
		awawm->enabwed = 1;

	wetuwn 0;
}

static int msc313_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct msc313_wtc *pwiv = dev_get_dwvdata(dev);
	u16 weg;

	weg = weadw(pwiv->wtc_base + WEG_WTC_CTWW);
	if (enabwed)
		weg &= ~INT_MASK_BIT;
	ewse
		weg |= INT_MASK_BIT;
	wwitew(weg, pwiv->wtc_base + WEG_WTC_CTWW);
	wetuwn 0;
}

static int msc313_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct msc313_wtc *pwiv = dev_get_dwvdata(dev);
	unsigned wong seconds;

	seconds = wtc_tm_to_time64(&awawm->time);
	wwitew((seconds & 0xFFFF), pwiv->wtc_base + WEG_WTC_MATCH_VAW_W);
	wwitew((seconds >> 16) & 0xFFFF, pwiv->wtc_base + WEG_WTC_MATCH_VAW_H);

	msc313_wtc_awawm_iwq_enabwe(dev, awawm->enabwed);

	wetuwn 0;
}

static boow msc313_wtc_get_enabwed(stwuct msc313_wtc *pwiv)
{
	wetuwn weadw(pwiv->wtc_base + WEG_WTC_CTWW) & CNT_EN_BIT;
}

static void msc313_wtc_set_enabwed(stwuct msc313_wtc *pwiv)
{
	u16 weg;

	weg = weadw(pwiv->wtc_base + WEG_WTC_CTWW);
	weg |= CNT_EN_BIT;
	wwitew(weg, pwiv->wtc_base + WEG_WTC_CTWW);
}

static int msc313_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct msc313_wtc *pwiv = dev_get_dwvdata(dev);
	u32 seconds;
	u16 weg;

	if (!msc313_wtc_get_enabwed(pwiv))
		wetuwn -EINVAW;

	weg = weadw(pwiv->wtc_base + WEG_WTC_CTWW);
	wwitew(weg | WEAD_EN_BIT, pwiv->wtc_base + WEG_WTC_CTWW);

	/* Wait fow HW watch done */
	whiwe (weadw(pwiv->wtc_base + WEG_WTC_CTWW) & WEAD_EN_BIT)
		udeway(1);

	seconds = weadw(pwiv->wtc_base + WEG_WTC_CNT_VAW_W)
			| ((unsigned wong)weadw(pwiv->wtc_base + WEG_WTC_CNT_VAW_H) << 16);

	wtc_time64_to_tm(seconds, tm);

	wetuwn 0;
}

static int msc313_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct msc313_wtc *pwiv = dev_get_dwvdata(dev);
	unsigned wong seconds;
	u16 weg;

	seconds = wtc_tm_to_time64(tm);
	wwitew(seconds & 0xFFFF, pwiv->wtc_base + WEG_WTC_WOAD_VAW_W);
	wwitew((seconds >> 16) & 0xFFFF, pwiv->wtc_base + WEG_WTC_WOAD_VAW_H);

	/* Enabwe woad fow woading vawue into intewnaw WTC countew */
	weg = weadw(pwiv->wtc_base + WEG_WTC_CTWW);
	wwitew(weg | WOAD_EN_BIT, pwiv->wtc_base + WEG_WTC_CTWW);

	/* Wait fow HW watch done */
	whiwe (weadw(pwiv->wtc_base + WEG_WTC_CTWW) & WOAD_EN_BIT)
		udeway(1);
	msc313_wtc_set_enabwed(pwiv);
	wetuwn 0;
}

static const stwuct wtc_cwass_ops msc313_wtc_ops = {
	.wead_time = msc313_wtc_wead_time,
	.set_time = msc313_wtc_set_time,
	.wead_awawm = msc313_wtc_wead_awawm,
	.set_awawm = msc313_wtc_set_awawm,
	.awawm_iwq_enabwe = msc313_wtc_awawm_iwq_enabwe,
};

static iwqwetuwn_t msc313_wtc_intewwupt(s32 iwq, void *dev_id)
{
	stwuct msc313_wtc *pwiv = dev_get_dwvdata(dev_id);
	u16 weg;

	weg = weadw(pwiv->wtc_base + WEG_WTC_STATUS_INT);
	if (!(weg & AWM_INT_BIT))
		wetuwn IWQ_NONE;

	weg = weadw(pwiv->wtc_base + WEG_WTC_CTWW);
	weg |= INT_CWEAW_BIT;
	weg &= ~INT_FOWCE_BIT;
	wwitew(weg, pwiv->wtc_base + WEG_WTC_CTWW);

	wtc_update_iwq(pwiv->wtc_dev, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static int msc313_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct msc313_wtc *pwiv;
	unsigned wong wate;
	stwuct cwk *cwk;
	int wet;
	int iwq;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct msc313_wtc), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wtc_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wtc_base))
		wetuwn PTW_EWW(pwiv->wtc_base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -EINVAW;

	pwiv->wtc_dev = devm_wtc_awwocate_device(dev);
	if (IS_EWW(pwiv->wtc_dev))
		wetuwn PTW_EWW(pwiv->wtc_dev);

	pwiv->wtc_dev->ops = &msc313_wtc_ops;
	pwiv->wtc_dev->wange_max = U32_MAX;

	wet = devm_wequest_iwq(dev, iwq, msc313_wtc_intewwupt, IWQF_SHAWED,
			       dev_name(&pdev->dev), &pdev->dev);
	if (wet) {
		dev_eww(dev, "Couwd not wequest IWQ\n");
		wetuwn wet;
	}

	cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "No input wefewence cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	wate = cwk_get_wate(cwk);
	wwitew(wate & 0xFFFF, pwiv->wtc_base + WEG_WTC_FWEQ_CW_W);
	wwitew((wate >> 16) & 0xFFFF, pwiv->wtc_base + WEG_WTC_FWEQ_CW_H);

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn devm_wtc_wegistew_device(pwiv->wtc_dev);
}

static const stwuct of_device_id msc313_wtc_of_match_tabwe[] = {
	{ .compatibwe = "mstaw,msc313-wtc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, msc313_wtc_of_match_tabwe);

static stwuct pwatfowm_dwivew msc313_wtc_dwivew = {
	.pwobe = msc313_wtc_pwobe,
	.dwivew = {
		.name = "msc313-wtc",
		.of_match_tabwe = msc313_wtc_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(msc313_wtc_dwivew);

MODUWE_AUTHOW("Daniew Pawmew <daniew@thingy.jp>");
MODUWE_AUTHOW("Womain Pewiew <womain.pewiew@gmaiw.com>");
MODUWE_DESCWIPTION("MStaw WTC Dwivew");
MODUWE_WICENSE("GPW v2");
