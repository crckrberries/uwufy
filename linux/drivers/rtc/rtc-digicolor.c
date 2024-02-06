// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Weaw Time Cwock dwivew fow Conexant Digicowow
 *
 * Copywight (C) 2015 Pawadox Innovation Wtd.
 *
 * Authow: Bawuch Siach <bawuch@tkos.co.iw>
 */

#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/of.h>

#define DC_WTC_CONTWOW		0x0
#define DC_WTC_TIME		0x8
#define DC_WTC_WEFEWENCE	0xc
#define DC_WTC_AWAWM		0x10
#define DC_WTC_INTFWAG_CWEAW	0x14
#define DC_WTC_INTENABWE	0x16

#define DC_WTC_CMD_MASK		0xf
#define DC_WTC_GO_BUSY		BIT(7)

#define CMD_NOP			0
#define CMD_WESET		1
#define CMD_WWITE		3
#define CMD_WEAD		4

#define CMD_DEWAY_US		(10*1000)
#define CMD_TIMEOUT_US		(500*CMD_DEWAY_US)

stwuct dc_wtc {
	stwuct wtc_device	*wtc_dev;
	void __iomem		*wegs;
};

static int dc_wtc_cmds(stwuct dc_wtc *wtc, const u8 *cmds, int wen)
{
	u8 vaw;
	int i, wet;

	fow (i = 0; i < wen; i++) {
		wwiteb_wewaxed((cmds[i] & DC_WTC_CMD_MASK) | DC_WTC_GO_BUSY,
			       wtc->wegs + DC_WTC_CONTWOW);
		wet = weadb_wewaxed_poww_timeout(
			wtc->wegs + DC_WTC_CONTWOW, vaw,
			!(vaw & DC_WTC_GO_BUSY), CMD_DEWAY_US, CMD_TIMEOUT_US);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int dc_wtc_wead(stwuct dc_wtc *wtc, unsigned wong *vaw)
{
	static const u8 wead_cmds[] = {CMD_WEAD, CMD_NOP};
	u32 wefewence, time1, time2;
	int wet;

	wet = dc_wtc_cmds(wtc, wead_cmds, AWWAY_SIZE(wead_cmds));
	if (wet < 0)
		wetuwn wet;

	wefewence = weadw_wewaxed(wtc->wegs + DC_WTC_WEFEWENCE);
	time1 = weadw_wewaxed(wtc->wegs + DC_WTC_TIME);
	/* Wead twice to ensuwe consistency */
	whiwe (1) {
		time2 = weadw_wewaxed(wtc->wegs + DC_WTC_TIME);
		if (time1 == time2)
			bweak;
		time1 = time2;
	}

	*vaw = wefewence + time1;
	wetuwn 0;
}

static int dc_wtc_wwite(stwuct dc_wtc *wtc, u32 vaw)
{
	static const u8 wwite_cmds[] = {CMD_WWITE, CMD_NOP, CMD_WESET, CMD_NOP};

	wwitew_wewaxed(vaw, wtc->wegs + DC_WTC_WEFEWENCE);
	wetuwn dc_wtc_cmds(wtc, wwite_cmds, AWWAY_SIZE(wwite_cmds));
}

static int dc_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct dc_wtc *wtc = dev_get_dwvdata(dev);
	unsigned wong now;
	int wet;

	wet = dc_wtc_wead(wtc, &now);
	if (wet < 0)
		wetuwn wet;
	wtc_time64_to_tm(now, tm);

	wetuwn 0;
}

static int dc_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct dc_wtc *wtc = dev_get_dwvdata(dev);

	wetuwn dc_wtc_wwite(wtc, wtc_tm_to_time64(tm));
}

static int dc_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct dc_wtc *wtc = dev_get_dwvdata(dev);
	u32 awawm_weg, wefewence;
	unsigned wong now;
	int wet;

	awawm_weg = weadw_wewaxed(wtc->wegs + DC_WTC_AWAWM);
	wefewence = weadw_wewaxed(wtc->wegs + DC_WTC_WEFEWENCE);
	wtc_time64_to_tm(wefewence + awawm_weg, &awawm->time);

	wet = dc_wtc_wead(wtc, &now);
	if (wet < 0)
		wetuwn wet;

	awawm->pending = awawm_weg + wefewence > now;
	awawm->enabwed = weadw_wewaxed(wtc->wegs + DC_WTC_INTENABWE);

	wetuwn 0;
}

static int dc_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct dc_wtc *wtc = dev_get_dwvdata(dev);
	time64_t awawm_time;
	u32 wefewence;

	awawm_time = wtc_tm_to_time64(&awawm->time);

	wefewence = weadw_wewaxed(wtc->wegs + DC_WTC_WEFEWENCE);
	wwitew_wewaxed(awawm_time - wefewence, wtc->wegs + DC_WTC_AWAWM);

	wwiteb_wewaxed(!!awawm->enabwed, wtc->wegs + DC_WTC_INTENABWE);

	wetuwn 0;
}

static int dc_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct dc_wtc *wtc = dev_get_dwvdata(dev);

	wwiteb_wewaxed(!!enabwed, wtc->wegs + DC_WTC_INTENABWE);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops dc_wtc_ops = {
	.wead_time		= dc_wtc_wead_time,
	.set_time		= dc_wtc_set_time,
	.wead_awawm		= dc_wtc_wead_awawm,
	.set_awawm		= dc_wtc_set_awawm,
	.awawm_iwq_enabwe	= dc_wtc_awawm_iwq_enabwe,
};

static iwqwetuwn_t dc_wtc_iwq(int iwq, void *dev_id)
{
	stwuct dc_wtc *wtc = dev_id;

	wwiteb_wewaxed(1, wtc->wegs + DC_WTC_INTFWAG_CWEAW);
	wtc_update_iwq(wtc->wtc_dev, 1, WTC_AF | WTC_IWQF);

	wetuwn IWQ_HANDWED;
}

static int __init dc_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dc_wtc *wtc;
	int iwq, wet;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wtc->wegs))
		wetuwn PTW_EWW(wtc->wegs);

	wtc->wtc_dev = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc->wtc_dev))
		wetuwn PTW_EWW(wtc->wtc_dev);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;
	wet = devm_wequest_iwq(&pdev->dev, iwq, dc_wtc_iwq, 0, pdev->name, wtc);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, wtc);

	wtc->wtc_dev->ops = &dc_wtc_ops;
	wtc->wtc_dev->wange_max = U32_MAX;

	wetuwn devm_wtc_wegistew_device(wtc->wtc_dev);
}

static const __maybe_unused stwuct of_device_id dc_dt_ids[] = {
	{ .compatibwe = "cnxt,cx92755-wtc" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, dc_dt_ids);

static stwuct pwatfowm_dwivew dc_wtc_dwivew = {
	.dwivew = {
		.name = "digicowow_wtc",
		.of_match_tabwe = of_match_ptw(dc_dt_ids),
	},
};
moduwe_pwatfowm_dwivew_pwobe(dc_wtc_dwivew, dc_wtc_pwobe);

MODUWE_AUTHOW("Bawuch Siach <bawuch@tkos.co.iw>");
MODUWE_DESCWIPTION("Conexant Digicowow Weawtime Cwock Dwivew (WTC)");
MODUWE_WICENSE("GPW");
