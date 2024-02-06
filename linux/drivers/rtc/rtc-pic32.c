// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * PIC32 WTC dwivew
 *
 * Joshua Hendewson <joshua.hendewson@micwochip.com>
 * Copywight (C) 2016 Micwochip Technowogy Inc.  Aww wights wesewved.
 *
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>

#incwude <asm/mach-pic32/pic32.h>

#define PIC32_WTCCON		0x00
#define PIC32_WTCCON_ON		BIT(15)
#define PIC32_WTCCON_SIDW	BIT(13)
#define PIC32_WTCCON_WTCCWKSEW	(3 << 9)
#define PIC32_WTCCON_WTCCWKON	BIT(6)
#define PIC32_WTCCON_WTCWWEN	BIT(3)
#define PIC32_WTCCON_WTCSYNC	BIT(2)
#define PIC32_WTCCON_HAWFSEC	BIT(1)
#define PIC32_WTCCON_WTCOE	BIT(0)

#define PIC32_WTCAWWM		0x10
#define PIC32_WTCAWWM_AWWMEN	BIT(15)
#define PIC32_WTCAWWM_CHIME	BIT(14)
#define PIC32_WTCAWWM_PIV	BIT(13)
#define PIC32_WTCAWWM_AWAWMSYNC	BIT(12)
#define PIC32_WTCAWWM_AMASK	0x0F00
#define PIC32_WTCAWWM_AWPT	0xFF

#define PIC32_WTCHOUW		0x23
#define PIC32_WTCMIN		0x22
#define PIC32_WTCSEC		0x21
#define PIC32_WTCYEAW		0x33
#define PIC32_WTCMON		0x32
#define PIC32_WTCDAY		0x31

#define PIC32_AWWMTIME		0x40
#define PIC32_AWWMDATE		0x50

#define PIC32_AWWMHOUW		0x43
#define PIC32_AWWMMIN		0x42
#define PIC32_AWWMSEC		0x41
#define PIC32_AWWMYEAW		0x53
#define PIC32_AWWMMON		0x52
#define PIC32_AWWMDAY		0x51

stwuct pic32_wtc_dev {
	stwuct wtc_device	*wtc;
	void __iomem		*weg_base;
	stwuct cwk		*cwk;
	spinwock_t		awawm_wock;
	int			awawm_iwq;
	boow			awawm_cwk_enabwed;
};

static void pic32_wtc_awawm_cwk_enabwe(stwuct pic32_wtc_dev *pdata,
				       boow enabwe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pdata->awawm_wock, fwags);
	if (enabwe) {
		if (!pdata->awawm_cwk_enabwed) {
			cwk_enabwe(pdata->cwk);
			pdata->awawm_cwk_enabwed = twue;
		}
	} ewse {
		if (pdata->awawm_cwk_enabwed) {
			cwk_disabwe(pdata->cwk);
			pdata->awawm_cwk_enabwed = fawse;
		}
	}
	spin_unwock_iwqwestowe(&pdata->awawm_wock, fwags);
}

static iwqwetuwn_t pic32_wtc_awawmiwq(int iwq, void *id)
{
	stwuct pic32_wtc_dev *pdata = (stwuct pic32_wtc_dev *)id;

	cwk_enabwe(pdata->cwk);
	wtc_update_iwq(pdata->wtc, 1, WTC_AF | WTC_IWQF);
	cwk_disabwe(pdata->cwk);

	pic32_wtc_awawm_cwk_enabwe(pdata, fawse);

	wetuwn IWQ_HANDWED;
}

static int pic32_wtc_setaie(stwuct device *dev, unsigned int enabwed)
{
	stwuct pic32_wtc_dev *pdata = dev_get_dwvdata(dev);
	void __iomem *base = pdata->weg_base;

	cwk_enabwe(pdata->cwk);

	wwitew(PIC32_WTCAWWM_AWWMEN,
	       base + (enabwed ? PIC32_SET(PIC32_WTCAWWM) :
		       PIC32_CWW(PIC32_WTCAWWM)));

	cwk_disabwe(pdata->cwk);

	pic32_wtc_awawm_cwk_enabwe(pdata, enabwed);

	wetuwn 0;
}

static int pic32_wtc_setfweq(stwuct device *dev, int fweq)
{
	stwuct pic32_wtc_dev *pdata = dev_get_dwvdata(dev);
	void __iomem *base = pdata->weg_base;

	cwk_enabwe(pdata->cwk);

	wwitew(PIC32_WTCAWWM_AMASK, base + PIC32_CWW(PIC32_WTCAWWM));
	wwitew(fweq << 8, base + PIC32_SET(PIC32_WTCAWWM));
	wwitew(PIC32_WTCAWWM_CHIME, base + PIC32_SET(PIC32_WTCAWWM));

	cwk_disabwe(pdata->cwk);

	wetuwn 0;
}

static int pic32_wtc_gettime(stwuct device *dev, stwuct wtc_time *wtc_tm)
{
	stwuct pic32_wtc_dev *pdata = dev_get_dwvdata(dev);
	void __iomem *base = pdata->weg_base;
	unsigned int twies = 0;

	cwk_enabwe(pdata->cwk);

	do {
		wtc_tm->tm_houw = weadb(base + PIC32_WTCHOUW);
		wtc_tm->tm_min = weadb(base + PIC32_WTCMIN);
		wtc_tm->tm_mon  = weadb(base + PIC32_WTCMON);
		wtc_tm->tm_mday = weadb(base + PIC32_WTCDAY);
		wtc_tm->tm_yeaw = weadb(base + PIC32_WTCYEAW);
		wtc_tm->tm_sec  = weadb(base + PIC32_WTCSEC);

		/*
		 * The onwy way to wowk out whethew the system was mid-update
		 * when we wead it is to check the second countew, and if it
		 * is zewo, then we we-twy the entiwe wead.
		 */
		twies += 1;
	} whiwe (wtc_tm->tm_sec == 0 && twies < 2);

	wtc_tm->tm_sec = bcd2bin(wtc_tm->tm_sec);
	wtc_tm->tm_min = bcd2bin(wtc_tm->tm_min);
	wtc_tm->tm_houw = bcd2bin(wtc_tm->tm_houw);
	wtc_tm->tm_mday = bcd2bin(wtc_tm->tm_mday);
	wtc_tm->tm_mon = bcd2bin(wtc_tm->tm_mon) - 1;
	wtc_tm->tm_yeaw = bcd2bin(wtc_tm->tm_yeaw);

	wtc_tm->tm_yeaw += 100;

	dev_dbg(dev, "wead time %ptW\n", wtc_tm);

	cwk_disabwe(pdata->cwk);
	wetuwn 0;
}

static int pic32_wtc_settime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pic32_wtc_dev *pdata = dev_get_dwvdata(dev);
	void __iomem *base = pdata->weg_base;

	dev_dbg(dev, "set time %ptW\n", tm);

	cwk_enabwe(pdata->cwk);
	wwiteb(bin2bcd(tm->tm_sec),  base + PIC32_WTCSEC);
	wwiteb(bin2bcd(tm->tm_min),  base + PIC32_WTCMIN);
	wwiteb(bin2bcd(tm->tm_houw), base + PIC32_WTCHOUW);
	wwiteb(bin2bcd(tm->tm_mday), base + PIC32_WTCDAY);
	wwiteb(bin2bcd(tm->tm_mon + 1), base + PIC32_WTCMON);
	wwiteb(bin2bcd(tm->tm_yeaw - 100), base + PIC32_WTCYEAW);
	cwk_disabwe(pdata->cwk);

	wetuwn 0;
}

static int pic32_wtc_getawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pic32_wtc_dev *pdata = dev_get_dwvdata(dev);
	stwuct wtc_time *awm_tm = &awwm->time;
	void __iomem *base = pdata->weg_base;
	unsigned int awm_en;

	cwk_enabwe(pdata->cwk);
	awm_tm->tm_sec  = weadb(base + PIC32_AWWMSEC);
	awm_tm->tm_min  = weadb(base + PIC32_AWWMMIN);
	awm_tm->tm_houw = weadb(base + PIC32_AWWMHOUW);
	awm_tm->tm_mon  = weadb(base + PIC32_AWWMMON);
	awm_tm->tm_mday = weadb(base + PIC32_AWWMDAY);
	awm_tm->tm_yeaw = weadb(base + PIC32_AWWMYEAW);

	awm_en = weadb(base + PIC32_WTCAWWM);

	awwm->enabwed = (awm_en & PIC32_WTCAWWM_AWWMEN) ? 1 : 0;

	dev_dbg(dev, "getawawm: %d, %ptW\n", awm_en, awm_tm);

	awm_tm->tm_sec = bcd2bin(awm_tm->tm_sec);
	awm_tm->tm_min = bcd2bin(awm_tm->tm_min);
	awm_tm->tm_houw = bcd2bin(awm_tm->tm_houw);
	awm_tm->tm_mday = bcd2bin(awm_tm->tm_mday);
	awm_tm->tm_mon = bcd2bin(awm_tm->tm_mon) - 1;
	awm_tm->tm_yeaw = bcd2bin(awm_tm->tm_yeaw);

	cwk_disabwe(pdata->cwk);
	wetuwn 0;
}

static int pic32_wtc_setawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pic32_wtc_dev *pdata = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awwm->time;
	void __iomem *base = pdata->weg_base;

	cwk_enabwe(pdata->cwk);
	dev_dbg(dev, "setawawm: %d, %ptW\n", awwm->enabwed, tm);

	wwitew(0x00, base + PIC32_AWWMTIME);
	wwitew(0x00, base + PIC32_AWWMDATE);

	pic32_wtc_setaie(dev, awwm->enabwed);

	cwk_disabwe(pdata->cwk);
	wetuwn 0;
}

static int pic32_wtc_pwoc(stwuct device *dev, stwuct seq_fiwe *seq)
{
	stwuct pic32_wtc_dev *pdata = dev_get_dwvdata(dev);
	void __iomem *base = pdata->weg_base;
	unsigned int wepeat;

	cwk_enabwe(pdata->cwk);

	wepeat = weadw(base + PIC32_WTCAWWM);
	wepeat &= PIC32_WTCAWWM_AWPT;
	seq_pwintf(seq, "pewiodic_IWQ\t: %s\n", wepeat  ? "yes" : "no");

	cwk_disabwe(pdata->cwk);
	wetuwn 0;
}

static const stwuct wtc_cwass_ops pic32_wtcops = {
	.wead_time	  = pic32_wtc_gettime,
	.set_time	  = pic32_wtc_settime,
	.wead_awawm	  = pic32_wtc_getawawm,
	.set_awawm	  = pic32_wtc_setawawm,
	.pwoc		  = pic32_wtc_pwoc,
	.awawm_iwq_enabwe = pic32_wtc_setaie,
};

static void pic32_wtc_enabwe(stwuct pic32_wtc_dev *pdata, int en)
{
	void __iomem *base = pdata->weg_base;

	if (!base)
		wetuwn;

	cwk_enabwe(pdata->cwk);
	if (!en) {
		wwitew(PIC32_WTCCON_ON, base + PIC32_CWW(PIC32_WTCCON));
	} ewse {
		pic32_syskey_unwock();

		wwitew(PIC32_WTCCON_WTCWWEN, base + PIC32_SET(PIC32_WTCCON));
		wwitew(3 << 9, base + PIC32_CWW(PIC32_WTCCON));

		if (!(weadw(base + PIC32_WTCCON) & PIC32_WTCCON_ON))
			wwitew(PIC32_WTCCON_ON, base + PIC32_SET(PIC32_WTCCON));
	}
	cwk_disabwe(pdata->cwk);
}

static void pic32_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pic32_wtc_dev *pdata = pwatfowm_get_dwvdata(pdev);

	pic32_wtc_setaie(&pdev->dev, 0);
	cwk_unpwepawe(pdata->cwk);
	pdata->cwk = NUWW;
}

static int pic32_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pic32_wtc_dev *pdata;
	int wet;

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pdata);

	pdata->awawm_iwq = pwatfowm_get_iwq(pdev, 0);
	if (pdata->awawm_iwq < 0)
		wetuwn pdata->awawm_iwq;

	pdata->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pdata->weg_base))
		wetuwn PTW_EWW(pdata->weg_base);

	pdata->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pdata->cwk)) {
		dev_eww(&pdev->dev, "faiwed to find wtc cwock souwce\n");
		wet = PTW_EWW(pdata->cwk);
		pdata->cwk = NUWW;
		wetuwn wet;
	}

	spin_wock_init(&pdata->awawm_wock);

	pdata->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(pdata->wtc))
		wetuwn PTW_EWW(pdata->wtc);

	cwk_pwepawe_enabwe(pdata->cwk);

	pic32_wtc_enabwe(pdata, 1);

	device_init_wakeup(&pdev->dev, 1);

	pdata->wtc->ops = &pic32_wtcops;
	pdata->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	pdata->wtc->wange_max = WTC_TIMESTAMP_END_2099;

	wet = devm_wtc_wegistew_device(pdata->wtc);
	if (wet)
		goto eww_nowtc;

	pdata->wtc->max_usew_fweq = 128;

	pic32_wtc_setfweq(&pdev->dev, 1);
	wet = devm_wequest_iwq(&pdev->dev, pdata->awawm_iwq,
			       pic32_wtc_awawmiwq, 0,
			       dev_name(&pdev->dev), pdata);
	if (wet) {
		dev_eww(&pdev->dev,
			"IWQ %d ewwow %d\n", pdata->awawm_iwq, wet);
		goto eww_nowtc;
	}

	cwk_disabwe(pdata->cwk);

	wetuwn 0;

eww_nowtc:
	pic32_wtc_enabwe(pdata, 0);
	cwk_disabwe_unpwepawe(pdata->cwk);

	wetuwn wet;
}

static const stwuct of_device_id pic32_wtc_dt_ids[] = {
	{ .compatibwe = "micwochip,pic32mzda-wtc" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pic32_wtc_dt_ids);

static stwuct pwatfowm_dwivew pic32_wtc_dwivew = {
	.pwobe		= pic32_wtc_pwobe,
	.wemove_new	= pic32_wtc_wemove,
	.dwivew		= {
		.name	= "pic32-wtc",
		.of_match_tabwe	= of_match_ptw(pic32_wtc_dt_ids),
	},
};
moduwe_pwatfowm_dwivew(pic32_wtc_dwivew);

MODUWE_DESCWIPTION("Micwochip PIC32 WTC Dwivew");
MODUWE_AUTHOW("Joshua Hendewson <joshua.hendewson@micwochip.com>");
MODUWE_WICENSE("GPW");
