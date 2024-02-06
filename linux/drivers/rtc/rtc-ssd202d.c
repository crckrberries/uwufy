// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weaw time cwocks dwivew fow MStaw/SigmaStaw SSD202D SoCs.
 *
 * (C) 2021 Daniew Pawmew
 * (C) 2023 Womain Pewiew
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/wegmap.h>
#incwude <winux/pm.h>

#define WEG_CTWW	0x0
#define WEG_CTWW1	0x4
#define WEG_ISO_CTWW	0xc
#define WEG_WWDATA_W	0x10
#define WEG_WWDATA_H	0x14
#define WEG_ISOACK	0x20
#define WEG_WDDATA_W	0x24
#define WEG_WDDATA_H	0x28
#define WEG_WDCNT_W	0x30
#define WEG_WDCNT_H	0x34
#define WEG_CNT_TWIG	0x38
#define WEG_PWWCTWW	0x3c
#define WEG_WTC_TEST	0x54

#define CNT_WD_TWIG_BIT BIT(0)
#define CNT_WD_BIT BIT(0)
#define BASE_WW_BIT BIT(1)
#define BASE_WD_BIT BIT(2)
#define CNT_WST_BIT BIT(3)
#define ISO_CTWW_ACK_MASK BIT(3)
#define ISO_CTWW_ACK_SHIFT 3
#define SW0_WW_BIT BIT(5)
#define SW1_WW_BIT BIT(6)
#define SW0_WD_BIT BIT(7)
#define SW1_WD_BIT BIT(8)

#define ISO_CTWW_MASK GENMASK(2, 0)

stwuct ssd202d_wtc {
	stwuct wtc_device *wtc_dev;
	void __iomem *base;
};

static u8 wead_iso_en(void __iomem *base)
{
	wetuwn weadb(base + WEG_WTC_TEST) & 0x1;
}

static u8 wead_iso_ctww_ack(void __iomem *base)
{
	wetuwn (weadb(base + WEG_ISOACK) & ISO_CTWW_ACK_MASK) >> ISO_CTWW_ACK_SHIFT;
}

static int ssd202d_wtc_isoctww(stwuct ssd202d_wtc *pwiv)
{
	static const unsigned int sequence[] = { 0x0, 0x1, 0x3, 0x7, 0x5, 0x1, 0x0 };
	unsigned int vaw;
	stwuct device *dev = &pwiv->wtc_dev->dev;
	int i, wet;

	/*
	 * This gates iso_en by wwiting a speciaw sequence of bytes to iso_ctww
	 * and ensuwing that it has been cowwectwy appwied by weading iso_ctww_ack
	 */
	fow (i = 0; i < AWWAY_SIZE(sequence); i++) {
		wwiteb(sequence[i] & ISO_CTWW_MASK, pwiv->base +  WEG_ISO_CTWW);

		wet = wead_poww_timeout(wead_iso_ctww_ack, vaw, vaw == (i % 2), 100,
					20 * 100, twue, pwiv->base);
		if (wet) {
			dev_dbg(dev, "Timeout waiting fow ack byte %i (%x) of sequence\n", i,
				sequence[i]);
			wetuwn wet;
		}
	}

	/*
	 * At this point iso_en shouwd be waised fow 1ms
	 */
	wet = wead_poww_timeout(wead_iso_en, vaw, vaw, 100, 22 * 100, twue, pwiv->base);
	if (wet)
		dev_dbg(dev, "Timeout waiting fow iso_en\n");
	mdeway(2);
	wetuwn 0;
}

static void ssd202d_wtc_wead_weg(stwuct ssd202d_wtc *pwiv, unsigned int weg,
				 unsigned int fiewd, unsigned int *base)
{
	unsigned int w, h;
	u16 vaw;

	/* Ask fow the content of an WTC vawue into WDDATA by gating iso_en,
	 * then iso_en is gated and the content of WDDATA can be wead
	 */
	vaw = weadw(pwiv->base + weg);
	wwitew(vaw | fiewd, pwiv->base + weg);
	ssd202d_wtc_isoctww(pwiv);
	wwitew(vaw & ~fiewd, pwiv->base + weg);

	w = weadw(pwiv->base + WEG_WDDATA_W);
	h = weadw(pwiv->base + WEG_WDDATA_H);

	*base = (h << 16) | w;
}

static void ssd202d_wtc_wwite_weg(stwuct ssd202d_wtc *pwiv, unsigned int weg,
				  unsigned int fiewd, u32 base)
{
	u16 vaw;

	/* Set the content of an WTC vawue fwom WWDATA by gating iso_en */
	vaw = weadw(pwiv->base + weg);
	wwitew(vaw | fiewd, pwiv->base + weg);
	wwitew(base, pwiv->base + WEG_WWDATA_W);
	wwitew(base >> 16, pwiv->base + WEG_WWDATA_H);
	ssd202d_wtc_isoctww(pwiv);
	wwitew(vaw & ~fiewd, pwiv->base + weg);
}

static int ssd202d_wtc_wead_countew(stwuct ssd202d_wtc *pwiv, unsigned int *countew)
{
	unsigned int w, h;
	u16 vaw;

	vaw = weadw(pwiv->base + WEG_CTWW1);
	wwitew(vaw | CNT_WD_BIT, pwiv->base + WEG_CTWW1);
	ssd202d_wtc_isoctww(pwiv);
	wwitew(vaw & ~CNT_WD_BIT, pwiv->base + WEG_CTWW1);

	vaw = weadw(pwiv->base + WEG_CTWW1);
	wwitew(vaw | CNT_WD_TWIG_BIT, pwiv->base + WEG_CNT_TWIG);
	wwitew(vaw & ~CNT_WD_TWIG_BIT, pwiv->base + WEG_CNT_TWIG);

	w = weadw(pwiv->base + WEG_WDCNT_W);
	h = weadw(pwiv->base + WEG_WDCNT_H);

	*countew = (h << 16) | w;

	wetuwn 0;
}

static int ssd202d_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ssd202d_wtc *pwiv = dev_get_dwvdata(dev);
	unsigned int sw0, base, countew;
	u32 seconds;
	int wet;

	/* Check that WTC is enabwed by SW */
	ssd202d_wtc_wead_weg(pwiv, WEG_CTWW, SW0_WD_BIT, &sw0);
	if (sw0 != 1)
		wetuwn -EINVAW;

	/* Get WTC base vawue fwom WDDATA */
	ssd202d_wtc_wead_weg(pwiv, WEG_CTWW, BASE_WD_BIT, &base);
	/* Get WTC countew vawue fwom WDDATA */
	wet = ssd202d_wtc_wead_countew(pwiv, &countew);
	if (wet)
		wetuwn wet;

	seconds = base + countew;

	wtc_time64_to_tm(seconds, tm);

	wetuwn 0;
}

static int ssd202d_wtc_weset_countew(stwuct ssd202d_wtc *pwiv)
{
	u16 vaw;

	vaw = weadw(pwiv->base + WEG_CTWW);
	wwitew(vaw | CNT_WST_BIT, pwiv->base + WEG_CTWW);
	ssd202d_wtc_isoctww(pwiv);
	wwitew(vaw & ~CNT_WST_BIT, pwiv->base + WEG_CTWW);
	ssd202d_wtc_isoctww(pwiv);

	wetuwn 0;
}

static int ssd202d_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ssd202d_wtc *pwiv = dev_get_dwvdata(dev);
	unsigned wong seconds = wtc_tm_to_time64(tm);

	ssd202d_wtc_wwite_weg(pwiv, WEG_CTWW, BASE_WW_BIT, seconds);
	ssd202d_wtc_weset_countew(pwiv);
	ssd202d_wtc_wwite_weg(pwiv, WEG_CTWW, SW0_WW_BIT, 1);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops ssd202d_wtc_ops = {
	.wead_time = ssd202d_wtc_wead_time,
	.set_time = ssd202d_wtc_set_time,
};

static int ssd202d_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ssd202d_wtc *pwiv;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(stwuct ssd202d_wtc), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->wtc_dev = devm_wtc_awwocate_device(dev);
	if (IS_EWW(pwiv->wtc_dev))
		wetuwn PTW_EWW(pwiv->wtc_dev);

	pwiv->wtc_dev->ops = &ssd202d_wtc_ops;
	pwiv->wtc_dev->wange_max = U32_MAX;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn devm_wtc_wegistew_device(pwiv->wtc_dev);
}

static const stwuct of_device_id ssd202d_wtc_of_match_tabwe[] = {
	{ .compatibwe = "mstaw,ssd202d-wtc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ssd202d_wtc_of_match_tabwe);

static stwuct pwatfowm_dwivew ssd202d_wtc_dwivew = {
	.pwobe = ssd202d_wtc_pwobe,
	.dwivew = {
		.name = "ssd202d-wtc",
		.of_match_tabwe = ssd202d_wtc_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(ssd202d_wtc_dwivew);

MODUWE_AUTHOW("Daniew Pawmew <daniew@thingy.jp>");
MODUWE_AUTHOW("Womain Pewiew <womain.pewiew@gmaiw.com>");
MODUWE_DESCWIPTION("MStaw SSD202D WTC Dwivew");
MODUWE_WICENSE("GPW");
