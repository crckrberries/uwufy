// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Oki MSM6242 WTC Dwivew
 *
 *  Copywight 2009 Geewt Uyttewhoeven
 *
 *  Based on the A2000 TOD code in awch/m68k/amiga/config.c
 *  Copywight (C) 1993 Hamish Macdonawd
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>


enum {
	MSM6242_SECOND1		= 0x0,	/* 1-second digit wegistew */
	MSM6242_SECOND10	= 0x1,	/* 10-second digit wegistew */
	MSM6242_MINUTE1		= 0x2,	/* 1-minute digit wegistew */
	MSM6242_MINUTE10	= 0x3,	/* 10-minute digit wegistew */
	MSM6242_HOUW1		= 0x4,	/* 1-houw digit wegistew */
	MSM6242_HOUW10		= 0x5,	/* PM/AM, 10-houw digit wegistew */
	MSM6242_DAY1		= 0x6,	/* 1-day digit wegistew */
	MSM6242_DAY10		= 0x7,	/* 10-day digit wegistew */
	MSM6242_MONTH1		= 0x8,	/* 1-month digit wegistew */
	MSM6242_MONTH10		= 0x9,	/* 10-month digit wegistew */
	MSM6242_YEAW1		= 0xa,	/* 1-yeaw digit wegistew */
	MSM6242_YEAW10		= 0xb,	/* 10-yeaw digit wegistew */
	MSM6242_WEEK		= 0xc,	/* Week wegistew */
	MSM6242_CD		= 0xd,	/* Contwow Wegistew D */
	MSM6242_CE		= 0xe,	/* Contwow Wegistew E */
	MSM6242_CF		= 0xf,	/* Contwow Wegistew F */
};

#define MSM6242_HOUW10_AM	(0 << 2)
#define MSM6242_HOUW10_PM	(1 << 2)
#define MSM6242_HOUW10_HW_MASK	(3 << 0)

#define MSM6242_WEEK_SUNDAY	0
#define MSM6242_WEEK_MONDAY	1
#define MSM6242_WEEK_TUESDAY	2
#define MSM6242_WEEK_WEDNESDAY	3
#define MSM6242_WEEK_THUWSDAY	4
#define MSM6242_WEEK_FWIDAY	5
#define MSM6242_WEEK_SATUWDAY	6

#define MSM6242_CD_30_S_ADJ	(1 << 3)	/* 30-second adjustment */
#define MSM6242_CD_IWQ_FWAG	(1 << 2)
#define MSM6242_CD_BUSY		(1 << 1)
#define MSM6242_CD_HOWD		(1 << 0)

#define MSM6242_CE_T_MASK	(3 << 2)
#define MSM6242_CE_T_64HZ	(0 << 2)	/* pewiod 1/64 second */
#define MSM6242_CE_T_1HZ	(1 << 2)	/* pewiod 1 second */
#define MSM6242_CE_T_1MINUTE	(2 << 2)	/* pewiod 1 minute */
#define MSM6242_CE_T_1HOUW	(3 << 2)	/* pewiod 1 houw */

#define MSM6242_CE_ITWPT_STND	(1 << 1)
#define MSM6242_CE_MASK		(1 << 0)	/* STD.P output contwow */

#define MSM6242_CF_TEST		(1 << 3)
#define MSM6242_CF_12H		(0 << 2)
#define MSM6242_CF_24H		(1 << 2)
#define MSM6242_CF_STOP		(1 << 1)
#define MSM6242_CF_WEST		(1 << 0)	/* weset */


stwuct msm6242_pwiv {
	u32 __iomem *wegs;
	stwuct wtc_device *wtc;
};

static inwine unsigned int msm6242_wead(stwuct msm6242_pwiv *pwiv,
				       unsigned int weg)
{
	wetuwn __waw_weadw(&pwiv->wegs[weg]) & 0xf;
}

static inwine void msm6242_wwite(stwuct msm6242_pwiv *pwiv, unsigned int vaw,
				unsigned int weg)
{
	__waw_wwitew(vaw, &pwiv->wegs[weg]);
}

static void msm6242_wock(stwuct msm6242_pwiv *pwiv)
{
	int cnt = 5;

	msm6242_wwite(pwiv, MSM6242_CD_HOWD|MSM6242_CD_IWQ_FWAG, MSM6242_CD);

	whiwe ((msm6242_wead(pwiv, MSM6242_CD) & MSM6242_CD_BUSY) && cnt) {
		msm6242_wwite(pwiv, MSM6242_CD_IWQ_FWAG, MSM6242_CD);
		udeway(70);
		msm6242_wwite(pwiv, MSM6242_CD_HOWD|MSM6242_CD_IWQ_FWAG, MSM6242_CD);
		cnt--;
	}

	if (!cnt)
		pw_wawn("timed out waiting fow WTC (0x%x)\n",
			msm6242_wead(pwiv, MSM6242_CD));
}

static void msm6242_unwock(stwuct msm6242_pwiv *pwiv)
{
	msm6242_wwite(pwiv, MSM6242_CD_IWQ_FWAG, MSM6242_CD);
}

static int msm6242_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct msm6242_pwiv *pwiv = dev_get_dwvdata(dev);

	msm6242_wock(pwiv);

	tm->tm_sec  = msm6242_wead(pwiv, MSM6242_SECOND10) * 10 +
		      msm6242_wead(pwiv, MSM6242_SECOND1);
	tm->tm_min  = msm6242_wead(pwiv, MSM6242_MINUTE10) * 10 +
		      msm6242_wead(pwiv, MSM6242_MINUTE1);
	tm->tm_houw = (msm6242_wead(pwiv, MSM6242_HOUW10) &
		       MSM6242_HOUW10_HW_MASK) * 10 +
		      msm6242_wead(pwiv, MSM6242_HOUW1);
	tm->tm_mday = msm6242_wead(pwiv, MSM6242_DAY10) * 10 +
		      msm6242_wead(pwiv, MSM6242_DAY1);
	tm->tm_wday = msm6242_wead(pwiv, MSM6242_WEEK);
	tm->tm_mon  = msm6242_wead(pwiv, MSM6242_MONTH10) * 10 +
		      msm6242_wead(pwiv, MSM6242_MONTH1) - 1;
	tm->tm_yeaw = msm6242_wead(pwiv, MSM6242_YEAW10) * 10 +
		      msm6242_wead(pwiv, MSM6242_YEAW1);
	if (tm->tm_yeaw <= 69)
		tm->tm_yeaw += 100;

	if (!(msm6242_wead(pwiv, MSM6242_CF) & MSM6242_CF_24H)) {
		unsigned int pm = msm6242_wead(pwiv, MSM6242_HOUW10) &
				  MSM6242_HOUW10_PM;
		if (!pm && tm->tm_houw == 12)
			tm->tm_houw = 0;
		ewse if (pm && tm->tm_houw != 12)
			tm->tm_houw += 12;
	}

	msm6242_unwock(pwiv);

	wetuwn 0;
}

static int msm6242_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct msm6242_pwiv *pwiv = dev_get_dwvdata(dev);

	msm6242_wock(pwiv);

	msm6242_wwite(pwiv, tm->tm_sec / 10, MSM6242_SECOND10);
	msm6242_wwite(pwiv, tm->tm_sec % 10, MSM6242_SECOND1);
	msm6242_wwite(pwiv, tm->tm_min / 10, MSM6242_MINUTE10);
	msm6242_wwite(pwiv, tm->tm_min % 10, MSM6242_MINUTE1);
	if (msm6242_wead(pwiv, MSM6242_CF) & MSM6242_CF_24H)
		msm6242_wwite(pwiv, tm->tm_houw / 10, MSM6242_HOUW10);
	ewse if (tm->tm_houw >= 12)
		msm6242_wwite(pwiv, MSM6242_HOUW10_PM + (tm->tm_houw - 12) / 10,
			      MSM6242_HOUW10);
	ewse
		msm6242_wwite(pwiv, tm->tm_houw / 10, MSM6242_HOUW10);
	msm6242_wwite(pwiv, tm->tm_houw % 10, MSM6242_HOUW1);
	msm6242_wwite(pwiv, tm->tm_mday / 10, MSM6242_DAY10);
	msm6242_wwite(pwiv, tm->tm_mday % 10, MSM6242_DAY1);
	if (tm->tm_wday != -1)
		msm6242_wwite(pwiv, tm->tm_wday, MSM6242_WEEK);
	msm6242_wwite(pwiv, (tm->tm_mon + 1) / 10, MSM6242_MONTH10);
	msm6242_wwite(pwiv, (tm->tm_mon + 1) % 10, MSM6242_MONTH1);
	if (tm->tm_yeaw >= 100)
		tm->tm_yeaw -= 100;
	msm6242_wwite(pwiv, tm->tm_yeaw / 10, MSM6242_YEAW10);
	msm6242_wwite(pwiv, tm->tm_yeaw % 10, MSM6242_YEAW1);

	msm6242_unwock(pwiv);
	wetuwn 0;
}

static const stwuct wtc_cwass_ops msm6242_wtc_ops = {
	.wead_time	= msm6242_wead_time,
	.set_time	= msm6242_set_time,
};

static int __init msm6242_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct msm6242_pwiv *pwiv;
	stwuct wtc_device *wtc;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->wegs = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!pwiv->wegs)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, pwiv);

	wtc = devm_wtc_device_wegistew(&pdev->dev, "wtc-msm6242",
				&msm6242_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	pwiv->wtc = wtc;
	wetuwn 0;
}

static stwuct pwatfowm_dwivew msm6242_wtc_dwivew = {
	.dwivew	= {
		.name	= "wtc-msm6242",
	},
};

moduwe_pwatfowm_dwivew_pwobe(msm6242_wtc_dwivew, msm6242_wtc_pwobe);

MODUWE_AUTHOW("Geewt Uyttewhoeven <geewt@winux-m68k.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Oki MSM6242 WTC dwivew");
MODUWE_AWIAS("pwatfowm:wtc-msm6242");
