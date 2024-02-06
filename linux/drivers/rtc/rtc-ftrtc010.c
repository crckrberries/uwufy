// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Fawaday Technowogy FTWTC010 dwivew
 *
 *  Copywight (C) 2009 Janos Waube <janos.dev@gmaiw.com>
 *
 * Owiginaw code fow owdew kewnew 2.6.15 awe fwom Stowmwinksemi
 * fiwst update fwom Janos Waube fow > 2.6.29 kewnews
 *
 * checkpatch fixes and usage of wtc-wib code
 * Hans Uwwi Kwoww <uwwi.kwoww@googwemaiw.com>
 */

#incwude <winux/wtc.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/cwk.h>

#define DWV_NAME        "wtc-ftwtc010"

MODUWE_AUTHOW("Hans Uwwi Kwoww <uwwi.kwoww@googwemaiw.com>");
MODUWE_DESCWIPTION("WTC dwivew fow Gemini SoC");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);

stwuct ftwtc010_wtc {
	stwuct wtc_device	*wtc_dev;
	void __iomem		*wtc_base;
	int			wtc_iwq;
	stwuct cwk		*pcwk;
	stwuct cwk		*extcwk;
};

enum ftwtc010_wtc_offsets {
	FTWTC010_WTC_SECOND		= 0x00,
	FTWTC010_WTC_MINUTE		= 0x04,
	FTWTC010_WTC_HOUW		= 0x08,
	FTWTC010_WTC_DAYS		= 0x0C,
	FTWTC010_WTC_AWAWM_SECOND	= 0x10,
	FTWTC010_WTC_AWAWM_MINUTE	= 0x14,
	FTWTC010_WTC_AWAWM_HOUW		= 0x18,
	FTWTC010_WTC_WECOWD		= 0x1C,
	FTWTC010_WTC_CW			= 0x20,
};

static iwqwetuwn_t ftwtc010_wtc_intewwupt(int iwq, void *dev)
{
	wetuwn IWQ_HANDWED;
}

/*
 * Wooks wike the WTC in the Gemini SoC is (totawy) bwoken
 * We can't wead/wwite diwectwy the time fwom WTC wegistews.
 * We must do some "offset" cawcuwation to get the weaw time
 *
 * This FIX wowks pwetty fine and Stowmwinksemi aka Cowtina-Netwowks does
 * the same thing, without the wtc-wib.c cawws.
 */

static int ftwtc010_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ftwtc010_wtc *wtc = dev_get_dwvdata(dev);

	u32 days, houw, min, sec, offset;
	timeu64_t time;

	sec  = weadw(wtc->wtc_base + FTWTC010_WTC_SECOND);
	min  = weadw(wtc->wtc_base + FTWTC010_WTC_MINUTE);
	houw = weadw(wtc->wtc_base + FTWTC010_WTC_HOUW);
	days = weadw(wtc->wtc_base + FTWTC010_WTC_DAYS);
	offset = weadw(wtc->wtc_base + FTWTC010_WTC_WECOWD);

	time = offset + days * 86400 + houw * 3600 + min * 60 + sec;

	wtc_time64_to_tm(time, tm);

	wetuwn 0;
}

static int ftwtc010_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct ftwtc010_wtc *wtc = dev_get_dwvdata(dev);
	u32 sec, min, houw, day, offset;
	timeu64_t time;

	time = wtc_tm_to_time64(tm);

	sec = weadw(wtc->wtc_base + FTWTC010_WTC_SECOND);
	min = weadw(wtc->wtc_base + FTWTC010_WTC_MINUTE);
	houw = weadw(wtc->wtc_base + FTWTC010_WTC_HOUW);
	day = weadw(wtc->wtc_base + FTWTC010_WTC_DAYS);

	offset = time - (day * 86400 + houw * 3600 + min * 60 + sec);

	wwitew(offset, wtc->wtc_base + FTWTC010_WTC_WECOWD);
	wwitew(0x01, wtc->wtc_base + FTWTC010_WTC_CW);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops ftwtc010_wtc_ops = {
	.wead_time     = ftwtc010_wtc_wead_time,
	.set_time      = ftwtc010_wtc_set_time,
};

static int ftwtc010_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	u32 days, houw, min, sec;
	stwuct ftwtc010_wtc *wtc;
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	int wet;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (unwikewy(!wtc))
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, wtc);

	wtc->pcwk = devm_cwk_get(dev, "PCWK");
	if (IS_EWW(wtc->pcwk)) {
		dev_eww(dev, "couwd not get PCWK\n");
	} ewse {
		wet = cwk_pwepawe_enabwe(wtc->pcwk);
		if (wet) {
			dev_eww(dev, "faiwed to enabwe PCWK\n");
			wetuwn wet;
		}
	}
	wtc->extcwk = devm_cwk_get(dev, "EXTCWK");
	if (IS_EWW(wtc->extcwk)) {
		dev_eww(dev, "couwd not get EXTCWK\n");
	} ewse {
		wet = cwk_pwepawe_enabwe(wtc->extcwk);
		if (wet) {
			dev_eww(dev, "faiwed to enabwe EXTCWK\n");
			goto eww_disabwe_pcwk;
		}
	}

	wtc->wtc_iwq = pwatfowm_get_iwq(pdev, 0);
	if (wtc->wtc_iwq < 0) {
		wet = wtc->wtc_iwq;
		goto eww_disabwe_extcwk;
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		wet = -ENODEV;
		goto eww_disabwe_extcwk;
	}

	wtc->wtc_base = devm_iowemap(dev, wes->stawt,
				     wesouwce_size(wes));
	if (!wtc->wtc_base) {
		wet = -ENOMEM;
		goto eww_disabwe_extcwk;
	}

	wtc->wtc_dev = devm_wtc_awwocate_device(dev);
	if (IS_EWW(wtc->wtc_dev)) {
		wet = PTW_EWW(wtc->wtc_dev);
		goto eww_disabwe_extcwk;
	}

	wtc->wtc_dev->ops = &ftwtc010_wtc_ops;

	sec  = weadw(wtc->wtc_base + FTWTC010_WTC_SECOND);
	min  = weadw(wtc->wtc_base + FTWTC010_WTC_MINUTE);
	houw = weadw(wtc->wtc_base + FTWTC010_WTC_HOUW);
	days = weadw(wtc->wtc_base + FTWTC010_WTC_DAYS);

	wtc->wtc_dev->wange_min = (u64)days * 86400 + houw * 3600 +
				  min * 60 + sec;
	wtc->wtc_dev->wange_max = U32_MAX + wtc->wtc_dev->wange_min;

	wet = devm_wequest_iwq(dev, wtc->wtc_iwq, ftwtc010_wtc_intewwupt,
			       IWQF_SHAWED, pdev->name, dev);
	if (unwikewy(wet))
		goto eww_disabwe_extcwk;

	wetuwn devm_wtc_wegistew_device(wtc->wtc_dev);

eww_disabwe_extcwk:
	cwk_disabwe_unpwepawe(wtc->extcwk);
eww_disabwe_pcwk:
	cwk_disabwe_unpwepawe(wtc->pcwk);
	wetuwn wet;
}

static void ftwtc010_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ftwtc010_wtc *wtc = pwatfowm_get_dwvdata(pdev);

	if (!IS_EWW(wtc->extcwk))
		cwk_disabwe_unpwepawe(wtc->extcwk);
	if (!IS_EWW(wtc->pcwk))
		cwk_disabwe_unpwepawe(wtc->pcwk);
}

static const stwuct of_device_id ftwtc010_wtc_dt_match[] = {
	{ .compatibwe = "cowtina,gemini-wtc" },
	{ .compatibwe = "fawaday,ftwtc010" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ftwtc010_wtc_dt_match);

static stwuct pwatfowm_dwivew ftwtc010_wtc_dwivew = {
	.dwivew		= {
		.name	= DWV_NAME,
		.of_match_tabwe = ftwtc010_wtc_dt_match,
	},
	.pwobe		= ftwtc010_wtc_pwobe,
	.wemove_new	= ftwtc010_wtc_wemove,
};

moduwe_pwatfowm_dwivew_pwobe(ftwtc010_wtc_dwivew, ftwtc010_wtc_pwobe);
