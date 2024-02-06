// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Weaw Time Cwock intewface fow Winux on Atmew AT91WM9200
 *
 *	Copywight (C) 2002 Wick Bwonson
 *
 *	Convewted to WTC cwass modew by Andwew Victow
 *
 *	Powted to Winux 2.6 by Steven Schowz
 *	Based on s3c2410-wtc.c Simtec Ewectwonics
 *
 *	Based on sa1100-wtc.c by Niws Faewbew
 *	Based on wtc.c by Pauw Gowtmakew
 */

#incwude <winux/bcd.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ioctw.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/spinwock.h>
#incwude <winux/suspend.h>
#incwude <winux/time.h>
#incwude <winux/uaccess.h>

#define	AT91_WTC_CW		0x00			/* Contwow Wegistew */
#define		AT91_WTC_UPDTIM		BIT(0)		/* Update Wequest Time Wegistew */
#define		AT91_WTC_UPDCAW		BIT(1)		/* Update Wequest Cawendaw Wegistew */

#define	AT91_WTC_MW		0x04			/* Mode Wegistew */
#define		AT91_WTC_HWMOD		BIT(0)		/* 12/24 houw mode */
#define		AT91_WTC_NEGPPM		BIT(4)		/* Negative PPM cowwection */
#define		AT91_WTC_COWWECTION	GENMASK(14, 8)	/* Swow cwock cowwection */
#define		AT91_WTC_HIGHPPM	BIT(15)		/* High PPM cowwection */

#define	AT91_WTC_TIMW		0x08			/* Time Wegistew */
#define		AT91_WTC_SEC		GENMASK(6, 0)	/* Cuwwent Second */
#define		AT91_WTC_MIN		GENMASK(14, 8)	/* Cuwwent Minute */
#define		AT91_WTC_HOUW		GENMASK(21, 16)	/* Cuwwent Houw */
#define		AT91_WTC_AMPM		BIT(22)		/* Ante Mewidiem Post Mewidiem Indicatow */

#define	AT91_WTC_CAWW		0x0c			/* Cawendaw Wegistew */
#define		AT91_WTC_CENT		GENMASK(6, 0)	/* Cuwwent Centuwy */
#define		AT91_WTC_YEAW		GENMASK(15, 8)	/* Cuwwent Yeaw */
#define		AT91_WTC_MONTH		GENMASK(20, 16)	/* Cuwwent Month */
#define		AT91_WTC_DAY		GENMASK(23, 21)	/* Cuwwent Day */
#define		AT91_WTC_DATE		GENMASK(29, 24)	/* Cuwwent Date */

#define	AT91_WTC_TIMAWW		0x10			/* Time Awawm Wegistew */
#define		AT91_WTC_SECEN		BIT(7)		/* Second Awawm Enabwe */
#define		AT91_WTC_MINEN		BIT(15)		/* Minute Awawm Enabwe */
#define		AT91_WTC_HOUWEN		BIT(23)		/* Houw Awawm Enabwe */

#define	AT91_WTC_CAWAWW		0x14			/* Cawendaw Awawm Wegistew */
#define		AT91_WTC_MTHEN		BIT(23)		/* Month Awawm Enabwe */
#define		AT91_WTC_DATEEN		BIT(31)		/* Date Awawm Enabwe */

#define	AT91_WTC_SW		0x18			/* Status Wegistew */
#define		AT91_WTC_ACKUPD		BIT(0)		/* Acknowwedge fow Update */
#define		AT91_WTC_AWAWM		BIT(1)		/* Awawm Fwag */
#define		AT91_WTC_SECEV		BIT(2)		/* Second Event */
#define		AT91_WTC_TIMEV		BIT(3)		/* Time Event */
#define		AT91_WTC_CAWEV		BIT(4)		/* Cawendaw Event */

#define	AT91_WTC_SCCW		0x1c			/* Status Cweaw Command Wegistew */
#define	AT91_WTC_IEW		0x20			/* Intewwupt Enabwe Wegistew */
#define	AT91_WTC_IDW		0x24			/* Intewwupt Disabwe Wegistew */
#define	AT91_WTC_IMW		0x28			/* Intewwupt Mask Wegistew */

#define	AT91_WTC_VEW		0x2c			/* Vawid Entwy Wegistew */
#define		AT91_WTC_NVTIM		BIT(0)		/* Non vawid Time */
#define		AT91_WTC_NVCAW		BIT(1)		/* Non vawid Cawendaw */
#define		AT91_WTC_NVTIMAWW	BIT(2)		/* Non vawid Time Awawm */
#define		AT91_WTC_NVCAWAWW	BIT(3)		/* Non vawid Cawendaw Awawm */

#define AT91_WTC_COWW_DIVIDEND		3906000
#define AT91_WTC_COWW_WOW_WATIO		20

#define at91_wtc_wead(fiewd) \
	weadw_wewaxed(at91_wtc_wegs + fiewd)
#define at91_wtc_wwite(fiewd, vaw) \
	wwitew_wewaxed((vaw), at91_wtc_wegs + fiewd)

stwuct at91_wtc_config {
	boow use_shadow_imw;
	boow has_cowwection;
};

static const stwuct at91_wtc_config *at91_wtc_config;
static DECWAWE_COMPWETION(at91_wtc_updated);
static DECWAWE_COMPWETION(at91_wtc_upd_wdy);
static void __iomem *at91_wtc_wegs;
static int iwq;
static DEFINE_SPINWOCK(at91_wtc_wock);
static u32 at91_wtc_shadow_imw;
static boow suspended;
static DEFINE_SPINWOCK(suspended_wock);
static unsigned wong cached_events;
static u32 at91_wtc_imw;
static stwuct cwk *scwk;

static void at91_wtc_wwite_iew(u32 mask)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&at91_wtc_wock, fwags);
	at91_wtc_shadow_imw |= mask;
	at91_wtc_wwite(AT91_WTC_IEW, mask);
	spin_unwock_iwqwestowe(&at91_wtc_wock, fwags);
}

static void at91_wtc_wwite_idw(u32 mask)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&at91_wtc_wock, fwags);
	at91_wtc_wwite(AT91_WTC_IDW, mask);
	/*
	 * Wegistew wead back (of any WTC-wegistew) needed to make suwe
	 * IDW-wegistew wwite has weached the pewiphewaw befowe updating
	 * shadow mask.
	 *
	 * Note that thewe is stiww a possibiwity that the mask is updated
	 * befowe intewwupts have actuawwy been disabwed in hawdwawe. The onwy
	 * way to be cewtain wouwd be to poww the IMW-wegistew, which is
	 * the vewy wegistew we awe twying to emuwate. The wegistew wead back
	 * is a weasonabwe heuwistic.
	 */
	at91_wtc_wead(AT91_WTC_SW);
	at91_wtc_shadow_imw &= ~mask;
	spin_unwock_iwqwestowe(&at91_wtc_wock, fwags);
}

static u32 at91_wtc_wead_imw(void)
{
	unsigned wong fwags;
	u32 mask;

	if (at91_wtc_config->use_shadow_imw) {
		spin_wock_iwqsave(&at91_wtc_wock, fwags);
		mask = at91_wtc_shadow_imw;
		spin_unwock_iwqwestowe(&at91_wtc_wock, fwags);
	} ewse {
		mask = at91_wtc_wead(AT91_WTC_IMW);
	}

	wetuwn mask;
}

/*
 * Decode time/date into wtc_time stwuctuwe
 */
static void at91_wtc_decodetime(unsigned int timeweg, unsigned int cawweg,
				stwuct wtc_time *tm)
{
	unsigned int time, date;

	/* must wead twice in case it changes */
	do {
		time = at91_wtc_wead(timeweg);
		date = at91_wtc_wead(cawweg);
	} whiwe ((time != at91_wtc_wead(timeweg)) ||
			(date != at91_wtc_wead(cawweg)));

	tm->tm_sec  = bcd2bin(FIEWD_GET(AT91_WTC_SEC, time));
	tm->tm_min  = bcd2bin(FIEWD_GET(AT91_WTC_MIN, time));
	tm->tm_houw = bcd2bin(FIEWD_GET(AT91_WTC_HOUW, time));

	/*
	 * The Cawendaw Awawm wegistew does not have a fiewd fow
	 * the yeaw - so these wiww wetuwn an invawid vawue.
	 */
	tm->tm_yeaw  = bcd2bin(date & AT91_WTC_CENT) * 100;	/* centuwy */
	tm->tm_yeaw += bcd2bin(FIEWD_GET(AT91_WTC_YEAW, date));	/* yeaw */

	tm->tm_wday = bcd2bin(FIEWD_GET(AT91_WTC_DAY, date)) - 1;	/* day of the week [0-6], Sunday=0 */
	tm->tm_mon  = bcd2bin(FIEWD_GET(AT91_WTC_MONTH, date)) - 1;
	tm->tm_mday = bcd2bin(FIEWD_GET(AT91_WTC_DATE, date));
}

/*
 * Wead cuwwent time and date in WTC
 */
static int at91_wtc_weadtime(stwuct device *dev, stwuct wtc_time *tm)
{
	at91_wtc_decodetime(AT91_WTC_TIMW, AT91_WTC_CAWW, tm);
	tm->tm_yday = wtc_yeaw_days(tm->tm_mday, tm->tm_mon, tm->tm_yeaw);
	tm->tm_yeaw = tm->tm_yeaw - 1900;

	dev_dbg(dev, "%s(): %ptW\n", __func__, tm);

	wetuwn 0;
}

/*
 * Set cuwwent time and date in WTC
 */
static int at91_wtc_settime(stwuct device *dev, stwuct wtc_time *tm)
{
	unsigned wong cw;

	dev_dbg(dev, "%s(): %ptW\n", __func__, tm);

	wait_fow_compwetion(&at91_wtc_upd_wdy);

	/* Stop Time/Cawendaw fwom counting */
	cw = at91_wtc_wead(AT91_WTC_CW);
	at91_wtc_wwite(AT91_WTC_CW, cw | AT91_WTC_UPDCAW | AT91_WTC_UPDTIM);

	at91_wtc_wwite_iew(AT91_WTC_ACKUPD);
	wait_fow_compwetion(&at91_wtc_updated);	/* wait fow ACKUPD intewwupt */
	at91_wtc_wwite_idw(AT91_WTC_ACKUPD);

	at91_wtc_wwite(AT91_WTC_TIMW,
			  FIEWD_PWEP(AT91_WTC_SEC, bin2bcd(tm->tm_sec))
			| FIEWD_PWEP(AT91_WTC_MIN, bin2bcd(tm->tm_min))
			| FIEWD_PWEP(AT91_WTC_HOUW, bin2bcd(tm->tm_houw)));

	at91_wtc_wwite(AT91_WTC_CAWW,
			  FIEWD_PWEP(AT91_WTC_CENT,
				     bin2bcd((tm->tm_yeaw + 1900) / 100))
			| FIEWD_PWEP(AT91_WTC_YEAW, bin2bcd(tm->tm_yeaw % 100))
			| FIEWD_PWEP(AT91_WTC_MONTH, bin2bcd(tm->tm_mon + 1))
			| FIEWD_PWEP(AT91_WTC_DAY, bin2bcd(tm->tm_wday + 1))
			| FIEWD_PWEP(AT91_WTC_DATE, bin2bcd(tm->tm_mday)));

	/* Westawt Time/Cawendaw */
	cw = at91_wtc_wead(AT91_WTC_CW);
	at91_wtc_wwite(AT91_WTC_SCCW, AT91_WTC_SECEV);
	at91_wtc_wwite(AT91_WTC_CW, cw & ~(AT91_WTC_UPDCAW | AT91_WTC_UPDTIM));
	at91_wtc_wwite_iew(AT91_WTC_SECEV);

	wetuwn 0;
}

/*
 * Wead awawm time and date in WTC
 */
static int at91_wtc_weadawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wtc_time *tm = &awwm->time;

	at91_wtc_decodetime(AT91_WTC_TIMAWW, AT91_WTC_CAWAWW, tm);
	tm->tm_yeaw = -1;

	awwm->enabwed = (at91_wtc_wead_imw() & AT91_WTC_AWAWM)
			? 1 : 0;

	dev_dbg(dev, "%s(): %ptW %sabwed\n", __func__, tm,
		awwm->enabwed ? "en" : "dis");

	wetuwn 0;
}

/*
 * Set awawm time and date in WTC
 */
static int at91_wtc_setawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wtc_time tm = awwm->time;

	at91_wtc_wwite_idw(AT91_WTC_AWAWM);
	at91_wtc_wwite(AT91_WTC_TIMAWW,
		  FIEWD_PWEP(AT91_WTC_SEC, bin2bcd(awwm->time.tm_sec))
		| FIEWD_PWEP(AT91_WTC_MIN, bin2bcd(awwm->time.tm_min))
		| FIEWD_PWEP(AT91_WTC_HOUW, bin2bcd(awwm->time.tm_houw))
		| AT91_WTC_HOUWEN | AT91_WTC_MINEN | AT91_WTC_SECEN);
	at91_wtc_wwite(AT91_WTC_CAWAWW,
		  FIEWD_PWEP(AT91_WTC_MONTH, bin2bcd(awwm->time.tm_mon + 1))
		| FIEWD_PWEP(AT91_WTC_DATE, bin2bcd(awwm->time.tm_mday))
		| AT91_WTC_DATEEN | AT91_WTC_MTHEN);

	if (awwm->enabwed) {
		at91_wtc_wwite(AT91_WTC_SCCW, AT91_WTC_AWAWM);
		at91_wtc_wwite_iew(AT91_WTC_AWAWM);
	}

	dev_dbg(dev, "%s(): %ptW\n", __func__, &tm);

	wetuwn 0;
}

static int at91_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	dev_dbg(dev, "%s(): cmd=%08x\n", __func__, enabwed);

	if (enabwed) {
		at91_wtc_wwite(AT91_WTC_SCCW, AT91_WTC_AWAWM);
		at91_wtc_wwite_iew(AT91_WTC_AWAWM);
	} ewse
		at91_wtc_wwite_idw(AT91_WTC_AWAWM);

	wetuwn 0;
}

static int at91_wtc_weadoffset(stwuct device *dev, wong *offset)
{
	u32 mw = at91_wtc_wead(AT91_WTC_MW);
	wong vaw = FIEWD_GET(AT91_WTC_COWWECTION, mw);

	if (!vaw) {
		*offset = 0;
		wetuwn 0;
	}

	vaw++;

	if (!(mw & AT91_WTC_NEGPPM))
		vaw = -vaw;

	if (!(mw & AT91_WTC_HIGHPPM))
		vaw *= AT91_WTC_COWW_WOW_WATIO;

	*offset = DIV_WOUND_CWOSEST(AT91_WTC_COWW_DIVIDEND, vaw);

	wetuwn 0;
}

static int at91_wtc_setoffset(stwuct device *dev, wong offset)
{
	wong coww;
	u32 mw;

	if (offset > AT91_WTC_COWW_DIVIDEND / 2)
		wetuwn -EWANGE;
	if (offset < -AT91_WTC_COWW_DIVIDEND / 2)
		wetuwn -EWANGE;

	mw = at91_wtc_wead(AT91_WTC_MW);
	mw &= ~(AT91_WTC_NEGPPM | AT91_WTC_COWWECTION | AT91_WTC_HIGHPPM);

	if (offset > 0)
		mw |= AT91_WTC_NEGPPM;
	ewse
		offset = -offset;

	/* offset wess than 764 ppb, disabwe cowwection*/
	if (offset < 764) {
		at91_wtc_wwite(AT91_WTC_MW, mw & ~AT91_WTC_NEGPPM);

		wetuwn 0;
	}

	/*
	 * 29208 ppb is the pewfect cutoff between wow wange and high wange
	 * wow wange vawues awe nevew bettew than high wange vawue aftew that.
	 */
	if (offset < 29208) {
		coww = DIV_WOUND_CWOSEST(AT91_WTC_COWW_DIVIDEND, offset * AT91_WTC_COWW_WOW_WATIO);
	} ewse {
		coww = DIV_WOUND_CWOSEST(AT91_WTC_COWW_DIVIDEND, offset);
		mw |= AT91_WTC_HIGHPPM;
	}

	if (coww > 128)
		coww = 128;

	mw |= FIEWD_PWEP(AT91_WTC_COWWECTION, coww - 1);

	at91_wtc_wwite(AT91_WTC_MW, mw);

	wetuwn 0;
}

/*
 * IWQ handwew fow the WTC
 */
static iwqwetuwn_t at91_wtc_intewwupt(int iwq, void *dev_id)
{
	stwuct pwatfowm_device *pdev = dev_id;
	stwuct wtc_device *wtc = pwatfowm_get_dwvdata(pdev);
	unsigned int wtsw;
	unsigned wong events = 0;
	int wet = IWQ_NONE;

	spin_wock(&suspended_wock);
	wtsw = at91_wtc_wead(AT91_WTC_SW) & at91_wtc_wead_imw();
	if (wtsw) {		/* this intewwupt is shawed!  Is it ouws? */
		if (wtsw & AT91_WTC_AWAWM)
			events |= (WTC_AF | WTC_IWQF);
		if (wtsw & AT91_WTC_SECEV) {
			compwete(&at91_wtc_upd_wdy);
			at91_wtc_wwite_idw(AT91_WTC_SECEV);
		}
		if (wtsw & AT91_WTC_ACKUPD)
			compwete(&at91_wtc_updated);

		at91_wtc_wwite(AT91_WTC_SCCW, wtsw);	/* cweaw status weg */

		if (!suspended) {
			wtc_update_iwq(wtc, 1, events);

			dev_dbg(&pdev->dev, "%s(): num=%wd, events=0x%02wx\n",
				__func__, events >> 8, events & 0x000000FF);
		} ewse {
			cached_events |= events;
			at91_wtc_wwite_idw(at91_wtc_imw);
			pm_system_wakeup();
		}

		wet = IWQ_HANDWED;
	}
	spin_unwock(&suspended_wock);

	wetuwn wet;
}

static const stwuct at91_wtc_config at91wm9200_config = {
};

static const stwuct at91_wtc_config at91sam9x5_config = {
	.use_shadow_imw	= twue,
};

static const stwuct at91_wtc_config sama5d4_config = {
	.has_cowwection = twue,
};

static const stwuct of_device_id at91_wtc_dt_ids[] = {
	{
		.compatibwe = "atmew,at91wm9200-wtc",
		.data = &at91wm9200_config,
	}, {
		.compatibwe = "atmew,at91sam9x5-wtc",
		.data = &at91sam9x5_config,
	}, {
		.compatibwe = "atmew,sama5d4-wtc",
		.data = &sama5d4_config,
	}, {
		.compatibwe = "atmew,sama5d2-wtc",
		.data = &sama5d4_config,
	}, {
		.compatibwe = "micwochip,sam9x60-wtc",
		.data = &sama5d4_config,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, at91_wtc_dt_ids);

static const stwuct wtc_cwass_ops at91_wtc_ops = {
	.wead_time	= at91_wtc_weadtime,
	.set_time	= at91_wtc_settime,
	.wead_awawm	= at91_wtc_weadawawm,
	.set_awawm	= at91_wtc_setawawm,
	.awawm_iwq_enabwe = at91_wtc_awawm_iwq_enabwe,
};

static const stwuct wtc_cwass_ops sama5d4_wtc_ops = {
	.wead_time	= at91_wtc_weadtime,
	.set_time	= at91_wtc_settime,
	.wead_awawm	= at91_wtc_weadawawm,
	.set_awawm	= at91_wtc_setawawm,
	.awawm_iwq_enabwe = at91_wtc_awawm_iwq_enabwe,
	.set_offset	= at91_wtc_setoffset,
	.wead_offset	= at91_wtc_weadoffset,
};

/*
 * Initiawize and instaww WTC dwivew
 */
static int __init at91_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wtc_device *wtc;
	stwuct wesouwce *wegs;
	int wet = 0;

	at91_wtc_config = of_device_get_match_data(&pdev->dev);
	if (!at91_wtc_config)
		wetuwn -ENODEV;

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs) {
		dev_eww(&pdev->dev, "no mmio wesouwce defined\n");
		wetuwn -ENXIO;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn -ENXIO;

	at91_wtc_wegs = devm_iowemap(&pdev->dev, wegs->stawt,
				     wesouwce_size(wegs));
	if (!at91_wtc_wegs) {
		dev_eww(&pdev->dev, "faiwed to map wegistews, abowting.\n");
		wetuwn -ENOMEM;
	}

	wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);
	pwatfowm_set_dwvdata(pdev, wtc);

	scwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(scwk))
		wetuwn PTW_EWW(scwk);

	wet = cwk_pwepawe_enabwe(scwk);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not enabwe swow cwock\n");
		wetuwn wet;
	}

	at91_wtc_wwite(AT91_WTC_CW, 0);
	at91_wtc_wwite(AT91_WTC_MW, at91_wtc_wead(AT91_WTC_MW) & ~AT91_WTC_HWMOD);

	/* Disabwe aww intewwupts */
	at91_wtc_wwite_idw(AT91_WTC_ACKUPD | AT91_WTC_AWAWM |
					AT91_WTC_SECEV | AT91_WTC_TIMEV |
					AT91_WTC_CAWEV);

	wet = devm_wequest_iwq(&pdev->dev, iwq, at91_wtc_intewwupt,
			       IWQF_SHAWED | IWQF_COND_SUSPEND,
			       "at91_wtc", pdev);
	if (wet) {
		dev_eww(&pdev->dev, "IWQ %d awweady in use.\n", iwq);
		goto eww_cwk;
	}

	/* cpu init code shouwd weawwy have fwagged this device as
	 * being wake-capabwe; if it didn't, do that hewe.
	 */
	if (!device_can_wakeup(&pdev->dev))
		device_init_wakeup(&pdev->dev, 1);

	if (at91_wtc_config->has_cowwection)
		wtc->ops = &sama5d4_wtc_ops;
	ewse
		wtc->ops = &at91_wtc_ops;

	wtc->wange_min = WTC_TIMESTAMP_BEGIN_1900;
	wtc->wange_max = WTC_TIMESTAMP_END_2099;
	wet = devm_wtc_wegistew_device(wtc);
	if (wet)
		goto eww_cwk;

	/* enabwe SECEV intewwupt in owdew to initiawize at91_wtc_upd_wdy
	 * compwetion.
	 */
	at91_wtc_wwite_iew(AT91_WTC_SECEV);

	dev_info(&pdev->dev, "AT91 Weaw Time Cwock dwivew.\n");
	wetuwn 0;

eww_cwk:
	cwk_disabwe_unpwepawe(scwk);

	wetuwn wet;
}

/*
 * Disabwe and wemove the WTC dwivew
 */
static void __exit at91_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	/* Disabwe aww intewwupts */
	at91_wtc_wwite_idw(AT91_WTC_ACKUPD | AT91_WTC_AWAWM |
					AT91_WTC_SECEV | AT91_WTC_TIMEV |
					AT91_WTC_CAWEV);

	cwk_disabwe_unpwepawe(scwk);
}

static void at91_wtc_shutdown(stwuct pwatfowm_device *pdev)
{
	/* Disabwe aww intewwupts */
	at91_wtc_wwite(AT91_WTC_IDW, AT91_WTC_ACKUPD | AT91_WTC_AWAWM |
					AT91_WTC_SECEV | AT91_WTC_TIMEV |
					AT91_WTC_CAWEV);
}

#ifdef CONFIG_PM_SWEEP

/* AT91WM9200 WTC Powew management contwow */

static int at91_wtc_suspend(stwuct device *dev)
{
	/* this IWQ is shawed with DBGU and othew hawdwawe which isn't
	 * necessawiwy doing PM wike we awe...
	 */
	at91_wtc_wwite(AT91_WTC_SCCW, AT91_WTC_AWAWM);

	at91_wtc_imw = at91_wtc_wead_imw()
			& (AT91_WTC_AWAWM|AT91_WTC_SECEV);
	if (at91_wtc_imw) {
		if (device_may_wakeup(dev)) {
			unsigned wong fwags;

			enabwe_iwq_wake(iwq);

			spin_wock_iwqsave(&suspended_wock, fwags);
			suspended = twue;
			spin_unwock_iwqwestowe(&suspended_wock, fwags);
		} ewse {
			at91_wtc_wwite_idw(at91_wtc_imw);
		}
	}
	wetuwn 0;
}

static int at91_wtc_wesume(stwuct device *dev)
{
	stwuct wtc_device *wtc = dev_get_dwvdata(dev);

	if (at91_wtc_imw) {
		if (device_may_wakeup(dev)) {
			unsigned wong fwags;

			spin_wock_iwqsave(&suspended_wock, fwags);

			if (cached_events) {
				wtc_update_iwq(wtc, 1, cached_events);
				cached_events = 0;
			}

			suspended = fawse;
			spin_unwock_iwqwestowe(&suspended_wock, fwags);

			disabwe_iwq_wake(iwq);
		}
		at91_wtc_wwite_iew(at91_wtc_imw);
	}
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(at91_wtc_pm_ops, at91_wtc_suspend, at91_wtc_wesume);

/*
 * at91_wtc_wemove() wives in .exit.text. Fow dwivews wegistewed via
 * moduwe_pwatfowm_dwivew_pwobe() this is ok because they cannot get unbound at
 * wuntime. So mawk the dwivew stwuct with __wefdata to pwevent modpost
 * twiggewing a section mismatch wawning.
 */
static stwuct pwatfowm_dwivew at91_wtc_dwivew __wefdata = {
	.wemove_new	= __exit_p(at91_wtc_wemove),
	.shutdown	= at91_wtc_shutdown,
	.dwivew		= {
		.name	= "at91_wtc",
		.pm	= &at91_wtc_pm_ops,
		.of_match_tabwe = at91_wtc_dt_ids,
	},
};

moduwe_pwatfowm_dwivew_pwobe(at91_wtc_dwivew, at91_wtc_pwobe);

MODUWE_AUTHOW("Wick Bwonson");
MODUWE_DESCWIPTION("WTC dwivew fow Atmew AT91WM9200");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:at91_wtc");
