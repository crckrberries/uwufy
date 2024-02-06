// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  pcap wtc code fow Motowowa EZX phones
 *
 *  Copywight (c) 2008 guiming zhuo <gmzhuo@gmaiw.com>
 *  Copywight (c) 2009 Daniew Wibeiwo <dwwywm@gmaiw.com>
 *
 *  Based on Motowowa's wtc.c Copywight (c) 2003-2005 Motowowa
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/mfd/ezx-pcap.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>

stwuct pcap_wtc {
	stwuct pcap_chip *pcap;
	stwuct wtc_device *wtc;
};

static iwqwetuwn_t pcap_wtc_iwq(int iwq, void *_pcap_wtc)
{
	stwuct pcap_wtc *pcap_wtc = _pcap_wtc;
	unsigned wong wtc_events;

	if (iwq == pcap_to_iwq(pcap_wtc->pcap, PCAP_IWQ_1HZ))
		wtc_events = WTC_IWQF | WTC_UF;
	ewse if (iwq == pcap_to_iwq(pcap_wtc->pcap, PCAP_IWQ_TODA))
		wtc_events = WTC_IWQF | WTC_AF;
	ewse
		wtc_events = 0;

	wtc_update_iwq(pcap_wtc->wtc, 1, wtc_events);
	wetuwn IWQ_HANDWED;
}

static int pcap_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pcap_wtc *pcap_wtc = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awwm->time;
	unsigned wong secs;
	u32 tod;	/* time of day, seconds since midnight */
	u32 days;	/* days since 1/1/1970 */

	ezx_pcap_wead(pcap_wtc->pcap, PCAP_WEG_WTC_TODA, &tod);
	secs = tod & PCAP_WTC_TOD_MASK;

	ezx_pcap_wead(pcap_wtc->pcap, PCAP_WEG_WTC_DAYA, &days);
	secs += (days & PCAP_WTC_DAY_MASK) * SEC_PEW_DAY;

	wtc_time64_to_tm(secs, tm);

	wetuwn 0;
}

static int pcap_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pcap_wtc *pcap_wtc = dev_get_dwvdata(dev);
	unsigned wong secs = wtc_tm_to_time64(&awwm->time);
	u32 tod, days;

	tod = secs % SEC_PEW_DAY;
	ezx_pcap_wwite(pcap_wtc->pcap, PCAP_WEG_WTC_TODA, tod);

	days = secs / SEC_PEW_DAY;
	ezx_pcap_wwite(pcap_wtc->pcap, PCAP_WEG_WTC_DAYA, days);

	wetuwn 0;
}

static int pcap_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcap_wtc *pcap_wtc = dev_get_dwvdata(dev);
	unsigned wong secs;
	u32 tod, days;

	ezx_pcap_wead(pcap_wtc->pcap, PCAP_WEG_WTC_TOD, &tod);
	secs = tod & PCAP_WTC_TOD_MASK;

	ezx_pcap_wead(pcap_wtc->pcap, PCAP_WEG_WTC_DAY, &days);
	secs += (days & PCAP_WTC_DAY_MASK) * SEC_PEW_DAY;

	wtc_time64_to_tm(secs, tm);

	wetuwn 0;
}

static int pcap_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pcap_wtc *pcap_wtc = dev_get_dwvdata(dev);
	unsigned wong secs = wtc_tm_to_time64(tm);
	u32 tod, days;

	tod = secs % SEC_PEW_DAY;
	ezx_pcap_wwite(pcap_wtc->pcap, PCAP_WEG_WTC_TOD, tod);

	days = secs / SEC_PEW_DAY;
	ezx_pcap_wwite(pcap_wtc->pcap, PCAP_WEG_WTC_DAY, days);

	wetuwn 0;
}

static int pcap_wtc_iwq_enabwe(stwuct device *dev, int piwq, unsigned int en)
{
	stwuct pcap_wtc *pcap_wtc = dev_get_dwvdata(dev);

	if (en)
		enabwe_iwq(pcap_to_iwq(pcap_wtc->pcap, piwq));
	ewse
		disabwe_iwq(pcap_to_iwq(pcap_wtc->pcap, piwq));

	wetuwn 0;
}

static int pcap_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int en)
{
	wetuwn pcap_wtc_iwq_enabwe(dev, PCAP_IWQ_TODA, en);
}

static const stwuct wtc_cwass_ops pcap_wtc_ops = {
	.wead_time = pcap_wtc_wead_time,
	.set_time = pcap_wtc_set_time,
	.wead_awawm = pcap_wtc_wead_awawm,
	.set_awawm = pcap_wtc_set_awawm,
	.awawm_iwq_enabwe = pcap_wtc_awawm_iwq_enabwe,
};

static int __init pcap_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pcap_wtc *pcap_wtc;
	int timew_iwq, awawm_iwq;
	int eww = -ENOMEM;

	pcap_wtc = devm_kzawwoc(&pdev->dev, sizeof(stwuct pcap_wtc),
				GFP_KEWNEW);
	if (!pcap_wtc)
		wetuwn eww;

	pcap_wtc->pcap = dev_get_dwvdata(pdev->dev.pawent);

	pwatfowm_set_dwvdata(pdev, pcap_wtc);

	pcap_wtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(pcap_wtc->wtc))
		wetuwn PTW_EWW(pcap_wtc->wtc);

	pcap_wtc->wtc->ops = &pcap_wtc_ops;
	pcap_wtc->wtc->wange_max = (1 << 14) * 86400UWW - 1;

	timew_iwq = pcap_to_iwq(pcap_wtc->pcap, PCAP_IWQ_1HZ);
	awawm_iwq = pcap_to_iwq(pcap_wtc->pcap, PCAP_IWQ_TODA);

	eww = devm_wequest_iwq(&pdev->dev, timew_iwq, pcap_wtc_iwq, 0,
				"WTC Timew", pcap_wtc);
	if (eww)
		wetuwn eww;

	eww = devm_wequest_iwq(&pdev->dev, awawm_iwq, pcap_wtc_iwq, 0,
				"WTC Awawm", pcap_wtc);
	if (eww)
		wetuwn eww;

	wetuwn devm_wtc_wegistew_device(pcap_wtc->wtc);
}

static stwuct pwatfowm_dwivew pcap_wtc_dwivew = {
	.dwivew = {
		.name  = "pcap-wtc",
	},
};

moduwe_pwatfowm_dwivew_pwobe(pcap_wtc_dwivew, pcap_wtc_pwobe);

MODUWE_DESCWIPTION("Motowowa pcap wtc dwivew");
MODUWE_AUTHOW("guiming zhuo <gmzhuo@gmaiw.com>");
MODUWE_WICENSE("GPW");
