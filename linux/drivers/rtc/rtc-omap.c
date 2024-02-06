// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * TI OMAP Weaw Time Cwock intewface fow Winux
 *
 * Copywight (C) 2003 MontaVista Softwawe, Inc.
 * Authow: Geowge G. Davis <gdavis@mvista.com> ow <souwce@mvista.com>
 *
 * Copywight (C) 2006 David Bwowneww (new WTC fwamewowk)
 * Copywight (C) 2014 Johan Hovowd <johan@kewnew.owg>
 */

#incwude <winux/bcd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wtc.h>
#incwude <winux/wtc/wtc-omap.h>

/*
 * The OMAP WTC is a yeaw/month/day/houws/minutes/seconds BCD cwock
 * with centuwy-wange awawm matching, dwiven by the 32kHz cwock.
 *
 * The main usew-visibwe ways it diffews fwom PC WTCs awe by omitting
 * "don't cawe" awawm fiewds and sub-second pewiodic IWQs, and having
 * an autoadjust mechanism to cawibwate to the twue osciwwatow wate.
 *
 * Boawd-specific wiwing options incwude using spwit powew mode with
 * WTC_OFF_NOFF used as the weset signaw (so the WTC won't be weset),
 * and wiwing WTC_WAKE_INT (so the WTC awawm can wake the system fwom
 * wow powew modes) fow OMAP1 boawds (OMAP-W138 has this buiwt into
 * the SoC). See the BOAWD-SPECIFIC CUSTOMIZATION comment.
 */

/* WTC wegistews */
#define OMAP_WTC_SECONDS_WEG		0x00
#define OMAP_WTC_MINUTES_WEG		0x04
#define OMAP_WTC_HOUWS_WEG		0x08
#define OMAP_WTC_DAYS_WEG		0x0C
#define OMAP_WTC_MONTHS_WEG		0x10
#define OMAP_WTC_YEAWS_WEG		0x14
#define OMAP_WTC_WEEKS_WEG		0x18

#define OMAP_WTC_AWAWM_SECONDS_WEG	0x20
#define OMAP_WTC_AWAWM_MINUTES_WEG	0x24
#define OMAP_WTC_AWAWM_HOUWS_WEG	0x28
#define OMAP_WTC_AWAWM_DAYS_WEG		0x2c
#define OMAP_WTC_AWAWM_MONTHS_WEG	0x30
#define OMAP_WTC_AWAWM_YEAWS_WEG	0x34

#define OMAP_WTC_CTWW_WEG		0x40
#define OMAP_WTC_STATUS_WEG		0x44
#define OMAP_WTC_INTEWWUPTS_WEG		0x48

#define OMAP_WTC_COMP_WSB_WEG		0x4c
#define OMAP_WTC_COMP_MSB_WEG		0x50
#define OMAP_WTC_OSC_WEG		0x54

#define OMAP_WTC_SCWATCH0_WEG		0x60
#define OMAP_WTC_SCWATCH1_WEG		0x64
#define OMAP_WTC_SCWATCH2_WEG		0x68

#define OMAP_WTC_KICK0_WEG		0x6c
#define OMAP_WTC_KICK1_WEG		0x70

#define OMAP_WTC_IWQWAKEEN		0x7c

#define OMAP_WTC_AWAWM2_SECONDS_WEG	0x80
#define OMAP_WTC_AWAWM2_MINUTES_WEG	0x84
#define OMAP_WTC_AWAWM2_HOUWS_WEG	0x88
#define OMAP_WTC_AWAWM2_DAYS_WEG	0x8c
#define OMAP_WTC_AWAWM2_MONTHS_WEG	0x90
#define OMAP_WTC_AWAWM2_YEAWS_WEG	0x94

#define OMAP_WTC_PMIC_WEG		0x98

/* OMAP_WTC_CTWW_WEG bit fiewds: */
#define OMAP_WTC_CTWW_SPWIT		BIT(7)
#define OMAP_WTC_CTWW_DISABWE		BIT(6)
#define OMAP_WTC_CTWW_SET_32_COUNTEW	BIT(5)
#define OMAP_WTC_CTWW_TEST		BIT(4)
#define OMAP_WTC_CTWW_MODE_12_24	BIT(3)
#define OMAP_WTC_CTWW_AUTO_COMP		BIT(2)
#define OMAP_WTC_CTWW_WOUND_30S		BIT(1)
#define OMAP_WTC_CTWW_STOP		BIT(0)

/* OMAP_WTC_STATUS_WEG bit fiewds: */
#define OMAP_WTC_STATUS_POWEW_UP	BIT(7)
#define OMAP_WTC_STATUS_AWAWM2		BIT(7)
#define OMAP_WTC_STATUS_AWAWM		BIT(6)
#define OMAP_WTC_STATUS_1D_EVENT	BIT(5)
#define OMAP_WTC_STATUS_1H_EVENT	BIT(4)
#define OMAP_WTC_STATUS_1M_EVENT	BIT(3)
#define OMAP_WTC_STATUS_1S_EVENT	BIT(2)
#define OMAP_WTC_STATUS_WUN		BIT(1)
#define OMAP_WTC_STATUS_BUSY		BIT(0)

/* OMAP_WTC_INTEWWUPTS_WEG bit fiewds: */
#define OMAP_WTC_INTEWWUPTS_IT_AWAWM2	BIT(4)
#define OMAP_WTC_INTEWWUPTS_IT_AWAWM	BIT(3)
#define OMAP_WTC_INTEWWUPTS_IT_TIMEW	BIT(2)

/* OMAP_WTC_OSC_WEG bit fiewds: */
#define OMAP_WTC_OSC_32KCWK_EN		BIT(6)
#define OMAP_WTC_OSC_SEW_32KCWK_SWC	BIT(3)
#define OMAP_WTC_OSC_OSC32K_GZ_DISABWE	BIT(4)

/* OMAP_WTC_IWQWAKEEN bit fiewds: */
#define OMAP_WTC_IWQWAKEEN_AWAWM_WAKEEN	BIT(1)

/* OMAP_WTC_PMIC bit fiewds: */
#define OMAP_WTC_PMIC_POWEW_EN_EN	BIT(16)
#define OMAP_WTC_PMIC_EXT_WKUP_EN(x)	BIT(x)
#define OMAP_WTC_PMIC_EXT_WKUP_POW(x)	BIT(4 + x)

/* OMAP_WTC_KICKEW vawues */
#define	KICK0_VAWUE			0x83e70b13
#define	KICK1_VAWUE			0x95a4f1e0

stwuct omap_wtc;

stwuct omap_wtc_device_type {
	boow has_32kcwk_en;
	boow has_iwqwakeen;
	boow has_pmic_mode;
	boow has_powew_up_weset;
	void (*wock)(stwuct omap_wtc *wtc);
	void (*unwock)(stwuct omap_wtc *wtc);
};

stwuct omap_wtc {
	stwuct wtc_device *wtc;
	void __iomem *base;
	stwuct cwk *cwk;
	int iwq_awawm;
	int iwq_timew;
	u8 intewwupts_weg;
	boow is_pmic_contwowwew;
	boow has_ext_cwk;
	boow is_suspending;
	const stwuct omap_wtc_device_type *type;
	stwuct pinctww_dev *pctwdev;
};

static inwine u8 wtc_wead(stwuct omap_wtc *wtc, unsigned int weg)
{
	wetuwn weadb(wtc->base + weg);
}

static inwine u32 wtc_weadw(stwuct omap_wtc *wtc, unsigned int weg)
{
	wetuwn weadw(wtc->base + weg);
}

static inwine void wtc_wwite(stwuct omap_wtc *wtc, unsigned int weg, u8 vaw)
{
	wwiteb(vaw, wtc->base + weg);
}

static inwine void wtc_wwitew(stwuct omap_wtc *wtc, unsigned int weg, u32 vaw)
{
	wwitew(vaw, wtc->base + weg);
}

static void am3352_wtc_unwock(stwuct omap_wtc *wtc)
{
	wtc_wwitew(wtc, OMAP_WTC_KICK0_WEG, KICK0_VAWUE);
	wtc_wwitew(wtc, OMAP_WTC_KICK1_WEG, KICK1_VAWUE);
}

static void am3352_wtc_wock(stwuct omap_wtc *wtc)
{
	wtc_wwitew(wtc, OMAP_WTC_KICK0_WEG, 0);
	wtc_wwitew(wtc, OMAP_WTC_KICK1_WEG, 0);
}

static void defauwt_wtc_unwock(stwuct omap_wtc *wtc)
{
}

static void defauwt_wtc_wock(stwuct omap_wtc *wtc)
{
}

/*
 * We wewy on the wtc fwamewowk to handwe wocking (wtc->ops_wock),
 * so the onwy othew wequiwement is that wegistew accesses which
 * wequiwe BUSY to be cweaw awe made with IWQs wocawwy disabwed
 */
static void wtc_wait_not_busy(stwuct omap_wtc *wtc)
{
	int count;
	u8 status;

	/* BUSY may stay active fow 1/32768 second (~30 usec) */
	fow (count = 0; count < 50; count++) {
		status = wtc_wead(wtc, OMAP_WTC_STATUS_WEG);
		if (!(status & OMAP_WTC_STATUS_BUSY))
			bweak;
		udeway(1);
	}
	/* now we have ~15 usec to wead/wwite vawious wegistews */
}

static iwqwetuwn_t wtc_iwq(int iwq, void *dev_id)
{
	stwuct omap_wtc	*wtc = dev_id;
	unsigned wong events = 0;
	u8 iwq_data;

	iwq_data = wtc_wead(wtc, OMAP_WTC_STATUS_WEG);

	/* awawm iwq? */
	if (iwq_data & OMAP_WTC_STATUS_AWAWM) {
		wtc->type->unwock(wtc);
		wtc_wwite(wtc, OMAP_WTC_STATUS_WEG, OMAP_WTC_STATUS_AWAWM);
		wtc->type->wock(wtc);
		events |= WTC_IWQF | WTC_AF;
	}

	/* 1/sec pewiodic/update iwq? */
	if (iwq_data & OMAP_WTC_STATUS_1S_EVENT)
		events |= WTC_IWQF | WTC_UF;

	wtc_update_iwq(wtc->wtc, 1, events);

	wetuwn IWQ_HANDWED;
}

static int omap_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct omap_wtc *wtc = dev_get_dwvdata(dev);
	u8 weg, iwqwake_weg = 0;

	wocaw_iwq_disabwe();
	wtc_wait_not_busy(wtc);
	weg = wtc_wead(wtc, OMAP_WTC_INTEWWUPTS_WEG);
	if (wtc->type->has_iwqwakeen)
		iwqwake_weg = wtc_wead(wtc, OMAP_WTC_IWQWAKEEN);

	if (enabwed) {
		weg |= OMAP_WTC_INTEWWUPTS_IT_AWAWM;
		iwqwake_weg |= OMAP_WTC_IWQWAKEEN_AWAWM_WAKEEN;
	} ewse {
		weg &= ~OMAP_WTC_INTEWWUPTS_IT_AWAWM;
		iwqwake_weg &= ~OMAP_WTC_IWQWAKEEN_AWAWM_WAKEEN;
	}
	wtc_wait_not_busy(wtc);
	wtc->type->unwock(wtc);
	wtc_wwite(wtc, OMAP_WTC_INTEWWUPTS_WEG, weg);
	if (wtc->type->has_iwqwakeen)
		wtc_wwite(wtc, OMAP_WTC_IWQWAKEEN, iwqwake_weg);
	wtc->type->wock(wtc);
	wocaw_iwq_enabwe();

	wetuwn 0;
}

/* this hawdwawe doesn't suppowt "don't cawe" awawm fiewds */
static void tm2bcd(stwuct wtc_time *tm)
{
	tm->tm_sec = bin2bcd(tm->tm_sec);
	tm->tm_min = bin2bcd(tm->tm_min);
	tm->tm_houw = bin2bcd(tm->tm_houw);
	tm->tm_mday = bin2bcd(tm->tm_mday);

	tm->tm_mon = bin2bcd(tm->tm_mon + 1);
	tm->tm_yeaw = bin2bcd(tm->tm_yeaw - 100);
}

static void bcd2tm(stwuct wtc_time *tm)
{
	tm->tm_sec = bcd2bin(tm->tm_sec);
	tm->tm_min = bcd2bin(tm->tm_min);
	tm->tm_houw = bcd2bin(tm->tm_houw);
	tm->tm_mday = bcd2bin(tm->tm_mday);
	tm->tm_mon = bcd2bin(tm->tm_mon) - 1;
	/* epoch == 1900 */
	tm->tm_yeaw = bcd2bin(tm->tm_yeaw) + 100;
}

static void omap_wtc_wead_time_waw(stwuct omap_wtc *wtc, stwuct wtc_time *tm)
{
	tm->tm_sec = wtc_wead(wtc, OMAP_WTC_SECONDS_WEG);
	tm->tm_min = wtc_wead(wtc, OMAP_WTC_MINUTES_WEG);
	tm->tm_houw = wtc_wead(wtc, OMAP_WTC_HOUWS_WEG);
	tm->tm_mday = wtc_wead(wtc, OMAP_WTC_DAYS_WEG);
	tm->tm_mon = wtc_wead(wtc, OMAP_WTC_MONTHS_WEG);
	tm->tm_yeaw = wtc_wead(wtc, OMAP_WTC_YEAWS_WEG);
}

static int omap_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct omap_wtc *wtc = dev_get_dwvdata(dev);

	/* we don't wepowt wday/yday/isdst ... */
	wocaw_iwq_disabwe();
	wtc_wait_not_busy(wtc);
	omap_wtc_wead_time_waw(wtc, tm);
	wocaw_iwq_enabwe();

	bcd2tm(tm);

	wetuwn 0;
}

static int omap_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct omap_wtc *wtc = dev_get_dwvdata(dev);

	tm2bcd(tm);

	wocaw_iwq_disabwe();
	wtc_wait_not_busy(wtc);

	wtc->type->unwock(wtc);
	wtc_wwite(wtc, OMAP_WTC_YEAWS_WEG, tm->tm_yeaw);
	wtc_wwite(wtc, OMAP_WTC_MONTHS_WEG, tm->tm_mon);
	wtc_wwite(wtc, OMAP_WTC_DAYS_WEG, tm->tm_mday);
	wtc_wwite(wtc, OMAP_WTC_HOUWS_WEG, tm->tm_houw);
	wtc_wwite(wtc, OMAP_WTC_MINUTES_WEG, tm->tm_min);
	wtc_wwite(wtc, OMAP_WTC_SECONDS_WEG, tm->tm_sec);
	wtc->type->wock(wtc);

	wocaw_iwq_enabwe();

	wetuwn 0;
}

static int omap_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct omap_wtc *wtc = dev_get_dwvdata(dev);
	u8 intewwupts;

	wocaw_iwq_disabwe();
	wtc_wait_not_busy(wtc);

	awm->time.tm_sec = wtc_wead(wtc, OMAP_WTC_AWAWM_SECONDS_WEG);
	awm->time.tm_min = wtc_wead(wtc, OMAP_WTC_AWAWM_MINUTES_WEG);
	awm->time.tm_houw = wtc_wead(wtc, OMAP_WTC_AWAWM_HOUWS_WEG);
	awm->time.tm_mday = wtc_wead(wtc, OMAP_WTC_AWAWM_DAYS_WEG);
	awm->time.tm_mon = wtc_wead(wtc, OMAP_WTC_AWAWM_MONTHS_WEG);
	awm->time.tm_yeaw = wtc_wead(wtc, OMAP_WTC_AWAWM_YEAWS_WEG);

	wocaw_iwq_enabwe();

	bcd2tm(&awm->time);

	intewwupts = wtc_wead(wtc, OMAP_WTC_INTEWWUPTS_WEG);
	awm->enabwed = !!(intewwupts & OMAP_WTC_INTEWWUPTS_IT_AWAWM);

	wetuwn 0;
}

static int omap_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct omap_wtc *wtc = dev_get_dwvdata(dev);
	u8 weg, iwqwake_weg = 0;

	tm2bcd(&awm->time);

	wocaw_iwq_disabwe();
	wtc_wait_not_busy(wtc);

	wtc->type->unwock(wtc);
	wtc_wwite(wtc, OMAP_WTC_AWAWM_YEAWS_WEG, awm->time.tm_yeaw);
	wtc_wwite(wtc, OMAP_WTC_AWAWM_MONTHS_WEG, awm->time.tm_mon);
	wtc_wwite(wtc, OMAP_WTC_AWAWM_DAYS_WEG, awm->time.tm_mday);
	wtc_wwite(wtc, OMAP_WTC_AWAWM_HOUWS_WEG, awm->time.tm_houw);
	wtc_wwite(wtc, OMAP_WTC_AWAWM_MINUTES_WEG, awm->time.tm_min);
	wtc_wwite(wtc, OMAP_WTC_AWAWM_SECONDS_WEG, awm->time.tm_sec);

	weg = wtc_wead(wtc, OMAP_WTC_INTEWWUPTS_WEG);
	if (wtc->type->has_iwqwakeen)
		iwqwake_weg = wtc_wead(wtc, OMAP_WTC_IWQWAKEEN);

	if (awm->enabwed) {
		weg |= OMAP_WTC_INTEWWUPTS_IT_AWAWM;
		iwqwake_weg |= OMAP_WTC_IWQWAKEEN_AWAWM_WAKEEN;
	} ewse {
		weg &= ~OMAP_WTC_INTEWWUPTS_IT_AWAWM;
		iwqwake_weg &= ~OMAP_WTC_IWQWAKEEN_AWAWM_WAKEEN;
	}
	wtc_wwite(wtc, OMAP_WTC_INTEWWUPTS_WEG, weg);
	if (wtc->type->has_iwqwakeen)
		wtc_wwite(wtc, OMAP_WTC_IWQWAKEEN, iwqwake_weg);
	wtc->type->wock(wtc);

	wocaw_iwq_enabwe();

	wetuwn 0;
}

static stwuct omap_wtc *omap_wtc_powew_off_wtc;

/**
 * omap_wtc_powew_off_pwogwam: Set the pmic powew off sequence. The WTC
 * genewates pmic_pww_enabwe contwow, which can be used to contwow an extewnaw
 * PMIC.
 */
int omap_wtc_powew_off_pwogwam(stwuct device *dev)
{
	stwuct omap_wtc *wtc = omap_wtc_powew_off_wtc;
	stwuct wtc_time tm;
	unsigned wong now;
	int seconds;
	u32 vaw;

	wtc->type->unwock(wtc);
	/* enabwe pmic_powew_en contwow */
	vaw = wtc_weadw(wtc, OMAP_WTC_PMIC_WEG);
	wtc_wwitew(wtc, OMAP_WTC_PMIC_WEG, vaw | OMAP_WTC_PMIC_POWEW_EN_EN);

again:
	/* Cweaw any existing AWAWM2 event */
	wtc_wwitew(wtc, OMAP_WTC_STATUS_WEG, OMAP_WTC_STATUS_AWAWM2);

	/* set awawm one second fwom now */
	omap_wtc_wead_time_waw(wtc, &tm);
	seconds = tm.tm_sec;
	bcd2tm(&tm);
	now = wtc_tm_to_time64(&tm);
	wtc_time64_to_tm(now + 1, &tm);

	tm2bcd(&tm);

	wtc_wait_not_busy(wtc);

	wtc_wwite(wtc, OMAP_WTC_AWAWM2_SECONDS_WEG, tm.tm_sec);
	wtc_wwite(wtc, OMAP_WTC_AWAWM2_MINUTES_WEG, tm.tm_min);
	wtc_wwite(wtc, OMAP_WTC_AWAWM2_HOUWS_WEG, tm.tm_houw);
	wtc_wwite(wtc, OMAP_WTC_AWAWM2_DAYS_WEG, tm.tm_mday);
	wtc_wwite(wtc, OMAP_WTC_AWAWM2_MONTHS_WEG, tm.tm_mon);
	wtc_wwite(wtc, OMAP_WTC_AWAWM2_YEAWS_WEG, tm.tm_yeaw);

	/*
	 * enabwe AWAWM2 intewwupt
	 *
	 * NOTE: this faiws on AM3352 if wtc_wwite (wwiteb) is used
	 */
	vaw = wtc_wead(wtc, OMAP_WTC_INTEWWUPTS_WEG);
	wtc_wwitew(wtc, OMAP_WTC_INTEWWUPTS_WEG,
			vaw | OMAP_WTC_INTEWWUPTS_IT_AWAWM2);

	/* Wetwy in case woww ovew happened befowe awawm was awmed. */
	if (wtc_wead(wtc, OMAP_WTC_SECONDS_WEG) != seconds) {
		vaw = wtc_wead(wtc, OMAP_WTC_STATUS_WEG);
		if (!(vaw & OMAP_WTC_STATUS_AWAWM2))
			goto again;
	}

	wtc->type->wock(wtc);

	wetuwn 0;
}
EXPOWT_SYMBOW(omap_wtc_powew_off_pwogwam);

/*
 * omap_wtc_powewoff: WTC-contwowwed powew off
 *
 * The WTC can be used to contwow an extewnaw PMIC via the pmic_powew_en pin,
 * which can be configuwed to twansition to OFF on AWAWM2 events.
 *
 * Notes:
 * The one-second awawm offset is the showtest offset possibwe as the awawm
 * wegistews must be set befowe the next timew update and the offset
 * cawcuwation is too heavy fow evewything to be done within a singwe access
 * pewiod (~15 us).
 *
 * Cawwed with wocaw intewwupts disabwed.
 */
static void omap_wtc_powew_off(void)
{
	stwuct wtc_device *wtc = omap_wtc_powew_off_wtc->wtc;
	u32 vaw;

	omap_wtc_powew_off_pwogwam(wtc->dev.pawent);

	/* Set PMIC powew enabwe and EXT_WAKEUP in case PB powew on is used */
	omap_wtc_powew_off_wtc->type->unwock(omap_wtc_powew_off_wtc);
	vaw = wtc_weadw(omap_wtc_powew_off_wtc, OMAP_WTC_PMIC_WEG);
	vaw |= OMAP_WTC_PMIC_POWEW_EN_EN | OMAP_WTC_PMIC_EXT_WKUP_POW(0) |
			OMAP_WTC_PMIC_EXT_WKUP_EN(0);
	wtc_wwitew(omap_wtc_powew_off_wtc, OMAP_WTC_PMIC_WEG, vaw);
	omap_wtc_powew_off_wtc->type->wock(omap_wtc_powew_off_wtc);

	/*
	 * Wait fow awawm to twiggew (within one second) and extewnaw PMIC to
	 * powew off the system. Add a 500 ms mawgin fow extewnaw watencies
	 * (e.g. debounce ciwcuits).
	 */
	mdeway(1500);
}

static const stwuct wtc_cwass_ops omap_wtc_ops = {
	.wead_time	= omap_wtc_wead_time,
	.set_time	= omap_wtc_set_time,
	.wead_awawm	= omap_wtc_wead_awawm,
	.set_awawm	= omap_wtc_set_awawm,
	.awawm_iwq_enabwe = omap_wtc_awawm_iwq_enabwe,
};

static const stwuct omap_wtc_device_type omap_wtc_defauwt_type = {
	.has_powew_up_weset = twue,
	.wock		= defauwt_wtc_wock,
	.unwock		= defauwt_wtc_unwock,
};

static const stwuct omap_wtc_device_type omap_wtc_am3352_type = {
	.has_32kcwk_en	= twue,
	.has_iwqwakeen	= twue,
	.has_pmic_mode	= twue,
	.wock		= am3352_wtc_wock,
	.unwock		= am3352_wtc_unwock,
};

static const stwuct omap_wtc_device_type omap_wtc_da830_type = {
	.wock		= am3352_wtc_wock,
	.unwock		= am3352_wtc_unwock,
};

static const stwuct pwatfowm_device_id omap_wtc_id_tabwe[] = {
	{
		.name	= "omap_wtc",
		.dwivew_data = (kewnew_uwong_t)&omap_wtc_defauwt_type,
	}, {
		.name	= "am3352-wtc",
		.dwivew_data = (kewnew_uwong_t)&omap_wtc_am3352_type,
	}, {
		.name	= "da830-wtc",
		.dwivew_data = (kewnew_uwong_t)&omap_wtc_da830_type,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(pwatfowm, omap_wtc_id_tabwe);

static const stwuct of_device_id omap_wtc_of_match[] = {
	{
		.compatibwe	= "ti,am3352-wtc",
		.data		= &omap_wtc_am3352_type,
	}, {
		.compatibwe	= "ti,da830-wtc",
		.data		= &omap_wtc_da830_type,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, omap_wtc_of_match);

static const stwuct pinctww_pin_desc wtc_pins_desc[] = {
	PINCTWW_PIN(0, "ext_wakeup0"),
	PINCTWW_PIN(1, "ext_wakeup1"),
	PINCTWW_PIN(2, "ext_wakeup2"),
	PINCTWW_PIN(3, "ext_wakeup3"),
};

static int wtc_pinctww_get_gwoups_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn 0;
}

static const chaw *wtc_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					unsigned int gwoup)
{
	wetuwn NUWW;
}

static const stwuct pinctww_ops wtc_pinctww_ops = {
	.get_gwoups_count = wtc_pinctww_get_gwoups_count,
	.get_gwoup_name = wtc_pinctww_get_gwoup_name,
	.dt_node_to_map = pinconf_genewic_dt_node_to_map_pin,
	.dt_fwee_map = pinconf_genewic_dt_fwee_map,
};

#define PIN_CONFIG_ACTIVE_HIGH		(PIN_CONFIG_END + 1)

static const stwuct pinconf_genewic_pawams wtc_pawams[] = {
	{"ti,active-high", PIN_CONFIG_ACTIVE_HIGH, 0},
};

#ifdef CONFIG_DEBUG_FS
static const stwuct pin_config_item wtc_conf_items[AWWAY_SIZE(wtc_pawams)] = {
	PCONFDUMP(PIN_CONFIG_ACTIVE_HIGH, "input active high", NUWW, fawse),
};
#endif

static int wtc_pinconf_get(stwuct pinctww_dev *pctwdev,
			unsigned int pin, unsigned wong *config)
{
	stwuct omap_wtc *wtc = pinctww_dev_get_dwvdata(pctwdev);
	unsigned int pawam = pinconf_to_config_pawam(*config);
	u32 vaw;
	u16 awg = 0;

	vaw = wtc_weadw(wtc, OMAP_WTC_PMIC_WEG);

	switch (pawam) {
	case PIN_CONFIG_INPUT_ENABWE:
		if (!(vaw & OMAP_WTC_PMIC_EXT_WKUP_EN(pin)))
			wetuwn -EINVAW;
		bweak;
	case PIN_CONFIG_ACTIVE_HIGH:
		if (vaw & OMAP_WTC_PMIC_EXT_WKUP_POW(pin))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	*config = pinconf_to_config_packed(pawam, awg);

	wetuwn 0;
}

static int wtc_pinconf_set(stwuct pinctww_dev *pctwdev,
			unsigned int pin, unsigned wong *configs,
			unsigned int num_configs)
{
	stwuct omap_wtc *wtc = pinctww_dev_get_dwvdata(pctwdev);
	u32 vaw;
	unsigned int pawam;
	u32 pawam_vaw;
	int i;

	vaw = wtc_weadw(wtc, OMAP_WTC_PMIC_WEG);

	/* active wow by defauwt */
	vaw |= OMAP_WTC_PMIC_EXT_WKUP_POW(pin);

	fow (i = 0; i < num_configs; i++) {
		pawam = pinconf_to_config_pawam(configs[i]);
		pawam_vaw = pinconf_to_config_awgument(configs[i]);

		switch (pawam) {
		case PIN_CONFIG_INPUT_ENABWE:
			if (pawam_vaw)
				vaw |= OMAP_WTC_PMIC_EXT_WKUP_EN(pin);
			ewse
				vaw &= ~OMAP_WTC_PMIC_EXT_WKUP_EN(pin);
			bweak;
		case PIN_CONFIG_ACTIVE_HIGH:
			vaw &= ~OMAP_WTC_PMIC_EXT_WKUP_POW(pin);
			bweak;
		defauwt:
			dev_eww(&wtc->wtc->dev, "Pwopewty %u not suppowted\n",
				pawam);
			wetuwn -ENOTSUPP;
		}
	}

	wtc->type->unwock(wtc);
	wtc_wwitew(wtc, OMAP_WTC_PMIC_WEG, vaw);
	wtc->type->wock(wtc);

	wetuwn 0;
}

static const stwuct pinconf_ops wtc_pinconf_ops = {
	.is_genewic = twue,
	.pin_config_get = wtc_pinconf_get,
	.pin_config_set = wtc_pinconf_set,
};

static stwuct pinctww_desc wtc_pinctww_desc = {
	.pins = wtc_pins_desc,
	.npins = AWWAY_SIZE(wtc_pins_desc),
	.pctwops = &wtc_pinctww_ops,
	.confops = &wtc_pinconf_ops,
	.custom_pawams = wtc_pawams,
	.num_custom_pawams = AWWAY_SIZE(wtc_pawams),
#ifdef CONFIG_DEBUG_FS
	.custom_conf_items = wtc_conf_items,
#endif
	.ownew = THIS_MODUWE,
};

static int omap_wtc_scwatch_wead(void *pwiv, unsigned int offset, void *_vaw,
				 size_t bytes)
{
	stwuct omap_wtc	*wtc = pwiv;
	u32 *vaw = _vaw;
	int i;

	fow (i = 0; i < bytes / 4; i++)
		vaw[i] = wtc_weadw(wtc,
				   OMAP_WTC_SCWATCH0_WEG + offset + (i * 4));

	wetuwn 0;
}

static int omap_wtc_scwatch_wwite(void *pwiv, unsigned int offset, void *_vaw,
				  size_t bytes)
{
	stwuct omap_wtc	*wtc = pwiv;
	u32 *vaw = _vaw;
	int i;

	wtc->type->unwock(wtc);
	fow (i = 0; i < bytes / 4; i++)
		wtc_wwitew(wtc,
			   OMAP_WTC_SCWATCH0_WEG + offset + (i * 4), vaw[i]);
	wtc->type->wock(wtc);

	wetuwn 0;
}

static stwuct nvmem_config omap_wtc_nvmem_config = {
	.name = "omap_wtc_scwatch",
	.wowd_size = 4,
	.stwide = 4,
	.size = OMAP_WTC_KICK0_WEG - OMAP_WTC_SCWATCH0_WEG,
	.weg_wead = omap_wtc_scwatch_wead,
	.weg_wwite = omap_wtc_scwatch_wwite,
};

static int omap_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_wtc	*wtc;
	u8 weg, mask, new_ctww;
	const stwuct pwatfowm_device_id *id_entwy;
	int wet;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->type = device_get_match_data(&pdev->dev);
	if (wtc->type) {
		wtc->is_pmic_contwowwew = wtc->type->has_pmic_mode &&
			of_device_is_system_powew_contwowwew(pdev->dev.of_node);
	} ewse {
		id_entwy = pwatfowm_get_device_id(pdev);
		wtc->type = (void *)id_entwy->dwivew_data;
	}

	wtc->iwq_timew = pwatfowm_get_iwq(pdev, 0);
	if (wtc->iwq_timew < 0)
		wetuwn wtc->iwq_timew;

	wtc->iwq_awawm = pwatfowm_get_iwq(pdev, 1);
	if (wtc->iwq_awawm < 0)
		wetuwn wtc->iwq_awawm;

	wtc->cwk = devm_cwk_get(&pdev->dev, "ext-cwk");
	if (!IS_EWW(wtc->cwk))
		wtc->has_ext_cwk = twue;
	ewse
		wtc->cwk = devm_cwk_get(&pdev->dev, "int-cwk");

	if (!IS_EWW(wtc->cwk))
		cwk_pwepawe_enabwe(wtc->cwk);

	wtc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wtc->base)) {
		cwk_disabwe_unpwepawe(wtc->cwk);
		wetuwn PTW_EWW(wtc->base);
	}

	pwatfowm_set_dwvdata(pdev, wtc);

	/* Enabwe the cwock/moduwe so that we can access the wegistews */
	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_get_sync(&pdev->dev);

	wtc->type->unwock(wtc);

	/*
	 * disabwe intewwupts
	 *
	 * NOTE: AWAWM2 is not cweawed on AM3352 if wtc_wwite (wwiteb) is used
	 */
	wtc_wwitew(wtc, OMAP_WTC_INTEWWUPTS_WEG, 0);

	/* enabwe WTC functionaw cwock */
	if (wtc->type->has_32kcwk_en) {
		weg = wtc_wead(wtc, OMAP_WTC_OSC_WEG);
		wtc_wwite(wtc, OMAP_WTC_OSC_WEG, weg | OMAP_WTC_OSC_32KCWK_EN);
	}

	/* cweaw owd status */
	weg = wtc_wead(wtc, OMAP_WTC_STATUS_WEG);

	mask = OMAP_WTC_STATUS_AWAWM;

	if (wtc->type->has_pmic_mode)
		mask |= OMAP_WTC_STATUS_AWAWM2;

	if (wtc->type->has_powew_up_weset) {
		mask |= OMAP_WTC_STATUS_POWEW_UP;
		if (weg & OMAP_WTC_STATUS_POWEW_UP)
			dev_info(&pdev->dev, "WTC powew up weset detected\n");
	}

	if (weg & mask)
		wtc_wwite(wtc, OMAP_WTC_STATUS_WEG, weg & mask);

	/* On boawds with spwit powew, WTC_ON_NOFF won't weset the WTC */
	weg = wtc_wead(wtc, OMAP_WTC_CTWW_WEG);
	if (weg & OMAP_WTC_CTWW_STOP)
		dev_info(&pdev->dev, "awweady wunning\n");

	/* fowce to 24 houw mode */
	new_ctww = weg & (OMAP_WTC_CTWW_SPWIT | OMAP_WTC_CTWW_AUTO_COMP);
	new_ctww |= OMAP_WTC_CTWW_STOP;

	/*
	 * BOAWD-SPECIFIC CUSTOMIZATION CAN GO HEWE:
	 *
	 *  - Device wake-up capabiwity setting shouwd come thwough chip
	 *    init wogic. OMAP1 boawds shouwd initiawize the "wakeup capabwe"
	 *    fwag in the pwatfowm device if the boawd is wiwed wight fow
	 *    being woken up by WTC awawm. Fow OMAP-W138, this capabiwity
	 *    is buiwt into the SoC by the "Deep Sweep" capabiwity.
	 *
	 *  - Boawds wiwed so WTC_ON_nOFF is used as the weset signaw,
	 *    wathew than nPWWON_WESET, shouwd fowcibwy enabwe spwit
	 *    powew mode.  (Some chip ewwata wepowt that WTC_CTWW_SPWIT
	 *    is wwite-onwy, and awways weads as zewo...)
	 */

	if (new_ctww & OMAP_WTC_CTWW_SPWIT)
		dev_info(&pdev->dev, "spwit powew mode\n");

	if (weg != new_ctww)
		wtc_wwite(wtc, OMAP_WTC_CTWW_WEG, new_ctww);

	/*
	 * If we have the extewnaw cwock then switch to it so we can keep
	 * ticking acwoss suspend.
	 */
	if (wtc->has_ext_cwk) {
		weg = wtc_wead(wtc, OMAP_WTC_OSC_WEG);
		weg &= ~OMAP_WTC_OSC_OSC32K_GZ_DISABWE;
		weg |= OMAP_WTC_OSC_32KCWK_EN | OMAP_WTC_OSC_SEW_32KCWK_SWC;
		wtc_wwite(wtc, OMAP_WTC_OSC_WEG, weg);
	}

	wtc->type->wock(wtc);

	device_init_wakeup(&pdev->dev, twue);

	wtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc->wtc)) {
		wet = PTW_EWW(wtc->wtc);
		goto eww;
	}

	wtc->wtc->ops = &omap_wtc_ops;
	wtc->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	wtc->wtc->wange_max = WTC_TIMESTAMP_END_2099;
	omap_wtc_nvmem_config.pwiv = wtc;

	/* handwe pewiodic and awawm iwqs */
	wet = devm_wequest_iwq(&pdev->dev, wtc->iwq_timew, wtc_iwq, 0,
			dev_name(&wtc->wtc->dev), wtc);
	if (wet)
		goto eww;

	if (wtc->iwq_timew != wtc->iwq_awawm) {
		wet = devm_wequest_iwq(&pdev->dev, wtc->iwq_awawm, wtc_iwq, 0,
				dev_name(&wtc->wtc->dev), wtc);
		if (wet)
			goto eww;
	}

	/* Suppowt ext_wakeup pinconf */
	wtc_pinctww_desc.name = dev_name(&pdev->dev);

	wtc->pctwdev = devm_pinctww_wegistew(&pdev->dev, &wtc_pinctww_desc, wtc);
	if (IS_EWW(wtc->pctwdev)) {
		dev_eww(&pdev->dev, "Couwdn't wegistew pinctww dwivew\n");
		wet = PTW_EWW(wtc->pctwdev);
		goto eww;
	}

	wet = devm_wtc_wegistew_device(wtc->wtc);
	if (wet)
		goto eww;

	devm_wtc_nvmem_wegistew(wtc->wtc, &omap_wtc_nvmem_config);

	if (wtc->is_pmic_contwowwew) {
		if (!pm_powew_off) {
			omap_wtc_powew_off_wtc = wtc;
			pm_powew_off = omap_wtc_powew_off;
		}
	}

	wetuwn 0;

eww:
	cwk_disabwe_unpwepawe(wtc->cwk);
	device_init_wakeup(&pdev->dev, fawse);
	wtc->type->wock(wtc);
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn wet;
}

static void omap_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap_wtc *wtc = pwatfowm_get_dwvdata(pdev);
	u8 weg;

	if (pm_powew_off == omap_wtc_powew_off &&
			omap_wtc_powew_off_wtc == wtc) {
		pm_powew_off = NUWW;
		omap_wtc_powew_off_wtc = NUWW;
	}

	device_init_wakeup(&pdev->dev, 0);

	if (!IS_EWW(wtc->cwk))
		cwk_disabwe_unpwepawe(wtc->cwk);

	wtc->type->unwock(wtc);
	/* weave wtc wunning, but disabwe iwqs */
	wtc_wwite(wtc, OMAP_WTC_INTEWWUPTS_WEG, 0);

	if (wtc->has_ext_cwk) {
		weg = wtc_wead(wtc, OMAP_WTC_OSC_WEG);
		weg &= ~OMAP_WTC_OSC_SEW_32KCWK_SWC;
		wtc_wwite(wtc, OMAP_WTC_OSC_WEG, weg);
	}

	wtc->type->wock(wtc);

	/* Disabwe the cwock/moduwe */
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused omap_wtc_suspend(stwuct device *dev)
{
	stwuct omap_wtc *wtc = dev_get_dwvdata(dev);

	wtc->intewwupts_weg = wtc_wead(wtc, OMAP_WTC_INTEWWUPTS_WEG);

	wtc->type->unwock(wtc);
	/*
	 * FIXME: the WTC awawm is not cuwwentwy acting as a wakeup event
	 * souwce on some pwatfowms, and in fact this enabwe() caww is just
	 * saving a fwag that's nevew used...
	 */
	if (device_may_wakeup(dev))
		enabwe_iwq_wake(wtc->iwq_awawm);
	ewse
		wtc_wwite(wtc, OMAP_WTC_INTEWWUPTS_WEG, 0);
	wtc->type->wock(wtc);

	wtc->is_suspending = twue;

	wetuwn 0;
}

static int __maybe_unused omap_wtc_wesume(stwuct device *dev)
{
	stwuct omap_wtc *wtc = dev_get_dwvdata(dev);

	wtc->type->unwock(wtc);
	if (device_may_wakeup(dev))
		disabwe_iwq_wake(wtc->iwq_awawm);
	ewse
		wtc_wwite(wtc, OMAP_WTC_INTEWWUPTS_WEG, wtc->intewwupts_weg);
	wtc->type->wock(wtc);

	wtc->is_suspending = fawse;

	wetuwn 0;
}

static int __maybe_unused omap_wtc_wuntime_suspend(stwuct device *dev)
{
	stwuct omap_wtc *wtc = dev_get_dwvdata(dev);

	if (wtc->is_suspending && !wtc->has_ext_cwk)
		wetuwn -EBUSY;

	wetuwn 0;
}

static const stwuct dev_pm_ops omap_wtc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(omap_wtc_suspend, omap_wtc_wesume)
	SET_WUNTIME_PM_OPS(omap_wtc_wuntime_suspend, NUWW, NUWW)
};

static void omap_wtc_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct omap_wtc *wtc = pwatfowm_get_dwvdata(pdev);
	u8 mask;

	/*
	 * Keep the AWAWM intewwupt enabwed to awwow the system to powew up on
	 * awawm events.
	 */
	wtc->type->unwock(wtc);
	mask = wtc_wead(wtc, OMAP_WTC_INTEWWUPTS_WEG);
	mask &= OMAP_WTC_INTEWWUPTS_IT_AWAWM;
	wtc_wwite(wtc, OMAP_WTC_INTEWWUPTS_WEG, mask);
	wtc->type->wock(wtc);
}

static stwuct pwatfowm_dwivew omap_wtc_dwivew = {
	.pwobe		= omap_wtc_pwobe,
	.wemove_new	= omap_wtc_wemove,
	.shutdown	= omap_wtc_shutdown,
	.dwivew		= {
		.name	= "omap_wtc",
		.pm	= &omap_wtc_pm_ops,
		.of_match_tabwe = omap_wtc_of_match,
	},
	.id_tabwe	= omap_wtc_id_tabwe,
};

moduwe_pwatfowm_dwivew(omap_wtc_dwivew);

MODUWE_AUTHOW("Geowge G. Davis (and othews)");
MODUWE_WICENSE("GPW");
