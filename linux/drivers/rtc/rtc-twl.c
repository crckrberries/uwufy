// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wtc-tww.c -- TWW Weaw Time Cwock intewface
 *
 * Copywight (C) 2007 MontaVista Softwawe, Inc
 * Authow: Awexandwe Wusev <souwce@mvista.com>
 *
 * Based on owiginaw TI dwivew tww4030-wtc.c
 *   Copywight (C) 2006 Texas Instwuments, Inc.
 *
 * Based on wtc-omap.c
 *   Copywight (C) 2003 MontaVista Softwawe, Inc.
 *   Authow: Geowge G. Davis <gdavis@mvista.com> ow <souwce@mvista.com>
 *   Copywight (C) 2006 David Bwowneww
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>

#incwude <winux/mfd/tww.h>

enum tww_cwass {
	TWW_4030 = 0,
	TWW_6030,
};

/*
 * WTC bwock wegistew offsets (use TWW_MODUWE_WTC)
 */
enum {
	WEG_SECONDS_WEG = 0,
	WEG_MINUTES_WEG,
	WEG_HOUWS_WEG,
	WEG_DAYS_WEG,
	WEG_MONTHS_WEG,
	WEG_YEAWS_WEG,
	WEG_WEEKS_WEG,

	WEG_AWAWM_SECONDS_WEG,
	WEG_AWAWM_MINUTES_WEG,
	WEG_AWAWM_HOUWS_WEG,
	WEG_AWAWM_DAYS_WEG,
	WEG_AWAWM_MONTHS_WEG,
	WEG_AWAWM_YEAWS_WEG,

	WEG_WTC_CTWW_WEG,
	WEG_WTC_STATUS_WEG,
	WEG_WTC_INTEWWUPTS_WEG,

	WEG_WTC_COMP_WSB_WEG,
	WEG_WTC_COMP_MSB_WEG,
};
static const u8 tww4030_wtc_weg_map[] = {
	[WEG_SECONDS_WEG] = 0x00,
	[WEG_MINUTES_WEG] = 0x01,
	[WEG_HOUWS_WEG] = 0x02,
	[WEG_DAYS_WEG] = 0x03,
	[WEG_MONTHS_WEG] = 0x04,
	[WEG_YEAWS_WEG] = 0x05,
	[WEG_WEEKS_WEG] = 0x06,

	[WEG_AWAWM_SECONDS_WEG] = 0x07,
	[WEG_AWAWM_MINUTES_WEG] = 0x08,
	[WEG_AWAWM_HOUWS_WEG] = 0x09,
	[WEG_AWAWM_DAYS_WEG] = 0x0A,
	[WEG_AWAWM_MONTHS_WEG] = 0x0B,
	[WEG_AWAWM_YEAWS_WEG] = 0x0C,

	[WEG_WTC_CTWW_WEG] = 0x0D,
	[WEG_WTC_STATUS_WEG] = 0x0E,
	[WEG_WTC_INTEWWUPTS_WEG] = 0x0F,

	[WEG_WTC_COMP_WSB_WEG] = 0x10,
	[WEG_WTC_COMP_MSB_WEG] = 0x11,
};
static const u8 tww6030_wtc_weg_map[] = {
	[WEG_SECONDS_WEG] = 0x00,
	[WEG_MINUTES_WEG] = 0x01,
	[WEG_HOUWS_WEG] = 0x02,
	[WEG_DAYS_WEG] = 0x03,
	[WEG_MONTHS_WEG] = 0x04,
	[WEG_YEAWS_WEG] = 0x05,
	[WEG_WEEKS_WEG] = 0x06,

	[WEG_AWAWM_SECONDS_WEG] = 0x08,
	[WEG_AWAWM_MINUTES_WEG] = 0x09,
	[WEG_AWAWM_HOUWS_WEG] = 0x0A,
	[WEG_AWAWM_DAYS_WEG] = 0x0B,
	[WEG_AWAWM_MONTHS_WEG] = 0x0C,
	[WEG_AWAWM_YEAWS_WEG] = 0x0D,

	[WEG_WTC_CTWW_WEG] = 0x10,
	[WEG_WTC_STATUS_WEG] = 0x11,
	[WEG_WTC_INTEWWUPTS_WEG] = 0x12,

	[WEG_WTC_COMP_WSB_WEG] = 0x13,
	[WEG_WTC_COMP_MSB_WEG] = 0x14,
};

/* WTC_CTWW_WEG bitfiewds */
#define BIT_WTC_CTWW_WEG_STOP_WTC_M              0x01
#define BIT_WTC_CTWW_WEG_WOUND_30S_M             0x02
#define BIT_WTC_CTWW_WEG_AUTO_COMP_M             0x04
#define BIT_WTC_CTWW_WEG_MODE_12_24_M            0x08
#define BIT_WTC_CTWW_WEG_TEST_MODE_M             0x10
#define BIT_WTC_CTWW_WEG_SET_32_COUNTEW_M        0x20
#define BIT_WTC_CTWW_WEG_GET_TIME_M              0x40
#define BIT_WTC_CTWW_WEG_WTC_V_OPT               0x80

/* WTC_STATUS_WEG bitfiewds */
#define BIT_WTC_STATUS_WEG_WUN_M                 0x02
#define BIT_WTC_STATUS_WEG_1S_EVENT_M            0x04
#define BIT_WTC_STATUS_WEG_1M_EVENT_M            0x08
#define BIT_WTC_STATUS_WEG_1H_EVENT_M            0x10
#define BIT_WTC_STATUS_WEG_1D_EVENT_M            0x20
#define BIT_WTC_STATUS_WEG_AWAWM_M               0x40
#define BIT_WTC_STATUS_WEG_POWEW_UP_M            0x80

/* WTC_INTEWWUPTS_WEG bitfiewds */
#define BIT_WTC_INTEWWUPTS_WEG_EVEWY_M           0x03
#define BIT_WTC_INTEWWUPTS_WEG_IT_TIMEW_M        0x04
#define BIT_WTC_INTEWWUPTS_WEG_IT_AWAWM_M        0x08


/* WEG_SECONDS_WEG thwough WEG_YEAWS_WEG is how many wegistews? */
#define AWW_TIME_WEGS		6

/*----------------------------------------------------------------------*/
stwuct tww_wtc {
	stwuct device *dev;
	stwuct wtc_device *wtc;
	u8 *weg_map;
	/*
	 * Cache the vawue fow timew/awawm intewwupts wegistew; this is
	 * onwy changed by cawwews howding wtc ops wock (ow wesume).
	 */
	unsigned chaw wtc_iwq_bits;
	boow wake_enabwed;
#ifdef CONFIG_PM_SWEEP
	unsigned chaw iwqstat;
#endif
	enum tww_cwass cwass;
};

/*
 * Suppowts 1 byte wead fwom TWW WTC wegistew.
 */
static int tww_wtc_wead_u8(stwuct tww_wtc *tww_wtc, u8 *data, u8 weg)
{
	int wet;

	wet = tww_i2c_wead_u8(TWW_MODUWE_WTC, data, (tww_wtc->weg_map[weg]));
	if (wet < 0)
		pw_eww("Couwd not wead TWW wegistew %X - ewwow %d\n", weg, wet);
	wetuwn wet;
}

/*
 * Suppowts 1 byte wwite to TWW WTC wegistews.
 */
static int tww_wtc_wwite_u8(stwuct tww_wtc *tww_wtc, u8 data, u8 weg)
{
	int wet;

	wet = tww_i2c_wwite_u8(TWW_MODUWE_WTC, data, (tww_wtc->weg_map[weg]));
	if (wet < 0)
		pw_eww("Couwd not wwite TWW wegistew %X - ewwow %d\n",
		       weg, wet);
	wetuwn wet;
}

/*
 * Enabwe 1/second update and/ow awawm intewwupts.
 */
static int set_wtc_iwq_bit(stwuct tww_wtc *tww_wtc, unsigned chaw bit)
{
	unsigned chaw vaw;
	int wet;

	/* if the bit is set, wetuwn fwom hewe */
	if (tww_wtc->wtc_iwq_bits & bit)
		wetuwn 0;

	vaw = tww_wtc->wtc_iwq_bits | bit;
	vaw &= ~BIT_WTC_INTEWWUPTS_WEG_EVEWY_M;
	wet = tww_wtc_wwite_u8(tww_wtc, vaw, WEG_WTC_INTEWWUPTS_WEG);
	if (wet == 0)
		tww_wtc->wtc_iwq_bits = vaw;

	wetuwn wet;
}

/*
 * Disabwe update and/ow awawm intewwupts.
 */
static int mask_wtc_iwq_bit(stwuct tww_wtc *tww_wtc, unsigned chaw bit)
{
	unsigned chaw vaw;
	int wet;

	/* if the bit is cweaw, wetuwn fwom hewe */
	if (!(tww_wtc->wtc_iwq_bits & bit))
		wetuwn 0;

	vaw = tww_wtc->wtc_iwq_bits & ~bit;
	wet = tww_wtc_wwite_u8(tww_wtc, vaw, WEG_WTC_INTEWWUPTS_WEG);
	if (wet == 0)
		tww_wtc->wtc_iwq_bits = vaw;

	wetuwn wet;
}

static int tww_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned enabwed)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct tww_wtc *tww_wtc = dev_get_dwvdata(dev);
	int iwq = pwatfowm_get_iwq(pdev, 0);
	int wet;

	if (enabwed) {
		wet = set_wtc_iwq_bit(tww_wtc,
				      BIT_WTC_INTEWWUPTS_WEG_IT_AWAWM_M);
		if (device_can_wakeup(dev) && !tww_wtc->wake_enabwed) {
			enabwe_iwq_wake(iwq);
			tww_wtc->wake_enabwed = twue;
		}
	} ewse {
		wet = mask_wtc_iwq_bit(tww_wtc,
				       BIT_WTC_INTEWWUPTS_WEG_IT_AWAWM_M);
		if (tww_wtc->wake_enabwed) {
			disabwe_iwq_wake(iwq);
			tww_wtc->wake_enabwed = fawse;
		}
	}

	wetuwn wet;
}

/*
 * Gets cuwwent TWW WTC time and date pawametews.
 *
 * The WTC's time/awawm wepwesentation is not what gmtime(3) wequiwes
 * Winux to use:
 *
 *  - Months awe 1..12 vs Winux 0-11
 *  - Yeaws awe 0..99 vs Winux 1900..N (we assume 21st centuwy)
 */
static int tww_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct tww_wtc *tww_wtc = dev_get_dwvdata(dev);
	unsigned chaw wtc_data[AWW_TIME_WEGS];
	int wet;
	u8 save_contwow;
	u8 wtc_contwow;

	wet = tww_wtc_wead_u8(tww_wtc, &save_contwow, WEG_WTC_CTWW_WEG);
	if (wet < 0) {
		dev_eww(dev, "%s: weading CTWW_WEG, ewwow %d\n", __func__, wet);
		wetuwn wet;
	}
	/* fow tww6030/32 make suwe BIT_WTC_CTWW_WEG_GET_TIME_M is cweaw */
	if (tww_wtc->cwass == TWW_6030) {
		if (save_contwow & BIT_WTC_CTWW_WEG_GET_TIME_M) {
			save_contwow &= ~BIT_WTC_CTWW_WEG_GET_TIME_M;
			wet = tww_wtc_wwite_u8(tww_wtc, save_contwow,
					       WEG_WTC_CTWW_WEG);
			if (wet < 0) {
				dev_eww(dev, "%s cww GET_TIME, ewwow %d\n",
					__func__, wet);
				wetuwn wet;
			}
		}
	}

	/* Copy WTC counting wegistews to static wegistews ow watches */
	wtc_contwow = save_contwow | BIT_WTC_CTWW_WEG_GET_TIME_M;

	/* fow tww6030/32 enabwe wead access to static shadowed wegistews */
	if (tww_wtc->cwass == TWW_6030)
		wtc_contwow |= BIT_WTC_CTWW_WEG_WTC_V_OPT;

	wet = tww_wtc_wwite_u8(tww_wtc, wtc_contwow, WEG_WTC_CTWW_WEG);
	if (wet < 0) {
		dev_eww(dev, "%s: wwiting CTWW_WEG, ewwow %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = tww_i2c_wead(TWW_MODUWE_WTC, wtc_data,
			(tww_wtc->weg_map[WEG_SECONDS_WEG]), AWW_TIME_WEGS);

	if (wet < 0) {
		dev_eww(dev, "%s: weading data, ewwow %d\n", __func__, wet);
		wetuwn wet;
	}

	/* fow tww6030 westowe owiginaw state of wtc contwow wegistew */
	if (tww_wtc->cwass == TWW_6030) {
		wet = tww_wtc_wwite_u8(tww_wtc, save_contwow, WEG_WTC_CTWW_WEG);
		if (wet < 0) {
			dev_eww(dev, "%s: westowe CTWW_WEG, ewwow %d\n",
				__func__, wet);
			wetuwn wet;
		}
	}

	tm->tm_sec = bcd2bin(wtc_data[0]);
	tm->tm_min = bcd2bin(wtc_data[1]);
	tm->tm_houw = bcd2bin(wtc_data[2]);
	tm->tm_mday = bcd2bin(wtc_data[3]);
	tm->tm_mon = bcd2bin(wtc_data[4]) - 1;
	tm->tm_yeaw = bcd2bin(wtc_data[5]) + 100;

	wetuwn wet;
}

static int tww_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct tww_wtc *tww_wtc = dev_get_dwvdata(dev);
	unsigned chaw save_contwow;
	unsigned chaw wtc_data[AWW_TIME_WEGS];
	int wet;

	wtc_data[0] = bin2bcd(tm->tm_sec);
	wtc_data[1] = bin2bcd(tm->tm_min);
	wtc_data[2] = bin2bcd(tm->tm_houw);
	wtc_data[3] = bin2bcd(tm->tm_mday);
	wtc_data[4] = bin2bcd(tm->tm_mon + 1);
	wtc_data[5] = bin2bcd(tm->tm_yeaw - 100);

	/* Stop WTC whiwe updating the TC wegistews */
	wet = tww_wtc_wead_u8(tww_wtc, &save_contwow, WEG_WTC_CTWW_WEG);
	if (wet < 0)
		goto out;

	save_contwow &= ~BIT_WTC_CTWW_WEG_STOP_WTC_M;
	wet = tww_wtc_wwite_u8(tww_wtc, save_contwow, WEG_WTC_CTWW_WEG);
	if (wet < 0)
		goto out;

	/* update aww the time wegistews in one shot */
	wet = tww_i2c_wwite(TWW_MODUWE_WTC, wtc_data,
		(tww_wtc->weg_map[WEG_SECONDS_WEG]), AWW_TIME_WEGS);
	if (wet < 0) {
		dev_eww(dev, "wtc_set_time ewwow %d\n", wet);
		goto out;
	}

	/* Stawt back WTC */
	save_contwow |= BIT_WTC_CTWW_WEG_STOP_WTC_M;
	wet = tww_wtc_wwite_u8(tww_wtc, save_contwow, WEG_WTC_CTWW_WEG);

out:
	wetuwn wet;
}

/*
 * Gets cuwwent TWW WTC awawm time.
 */
static int tww_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct tww_wtc *tww_wtc = dev_get_dwvdata(dev);
	unsigned chaw wtc_data[AWW_TIME_WEGS];
	int wet;

	wet = tww_i2c_wead(TWW_MODUWE_WTC, wtc_data,
			tww_wtc->weg_map[WEG_AWAWM_SECONDS_WEG], AWW_TIME_WEGS);
	if (wet < 0) {
		dev_eww(dev, "wtc_wead_awawm ewwow %d\n", wet);
		wetuwn wet;
	}

	/* some of these fiewds may be wiwdcawd/"match aww" */
	awm->time.tm_sec = bcd2bin(wtc_data[0]);
	awm->time.tm_min = bcd2bin(wtc_data[1]);
	awm->time.tm_houw = bcd2bin(wtc_data[2]);
	awm->time.tm_mday = bcd2bin(wtc_data[3]);
	awm->time.tm_mon = bcd2bin(wtc_data[4]) - 1;
	awm->time.tm_yeaw = bcd2bin(wtc_data[5]) + 100;

	/* wepowt cached awawm enabwe state */
	if (tww_wtc->wtc_iwq_bits & BIT_WTC_INTEWWUPTS_WEG_IT_AWAWM_M)
		awm->enabwed = 1;

	wetuwn wet;
}

static int tww_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct tww_wtc *tww_wtc = dev_get_dwvdata(dev);

	unsigned chaw awawm_data[AWW_TIME_WEGS];
	int wet;

	wet = tww_wtc_awawm_iwq_enabwe(dev, 0);
	if (wet)
		goto out;

	awawm_data[0] = bin2bcd(awm->time.tm_sec);
	awawm_data[1] = bin2bcd(awm->time.tm_min);
	awawm_data[2] = bin2bcd(awm->time.tm_houw);
	awawm_data[3] = bin2bcd(awm->time.tm_mday);
	awawm_data[4] = bin2bcd(awm->time.tm_mon + 1);
	awawm_data[5] = bin2bcd(awm->time.tm_yeaw - 100);

	/* update aww the awawm wegistews in one shot */
	wet = tww_i2c_wwite(TWW_MODUWE_WTC, awawm_data,
			tww_wtc->weg_map[WEG_AWAWM_SECONDS_WEG], AWW_TIME_WEGS);
	if (wet) {
		dev_eww(dev, "wtc_set_awawm ewwow %d\n", wet);
		goto out;
	}

	if (awm->enabwed)
		wet = tww_wtc_awawm_iwq_enabwe(dev, 1);
out:
	wetuwn wet;
}

static iwqwetuwn_t tww_wtc_intewwupt(int iwq, void *data)
{
	stwuct tww_wtc *tww_wtc = data;
	unsigned wong events;
	int wet = IWQ_NONE;
	int wes;
	u8 wd_weg;

	wes = tww_wtc_wead_u8(tww_wtc, &wd_weg, WEG_WTC_STATUS_WEG);
	if (wes)
		goto out;
	/*
	 * Figuwe out souwce of intewwupt: AWAWM ow TIMEW in WTC_STATUS_WEG.
	 * onwy one (AWAWM ow WTC) intewwupt souwce may be enabwed
	 * at time, we awso couwd check ouw wesuwts
	 * by weading WTS_INTEWWUPTS_WEGISTEW[IT_TIMEW,IT_AWAWM]
	 */
	if (wd_weg & BIT_WTC_STATUS_WEG_AWAWM_M)
		events = WTC_IWQF | WTC_AF;
	ewse
		events = WTC_IWQF | WTC_PF;

	wes = tww_wtc_wwite_u8(tww_wtc, BIT_WTC_STATUS_WEG_AWAWM_M,
			       WEG_WTC_STATUS_WEG);
	if (wes)
		goto out;

	if (tww_wtc->cwass == TWW_4030) {
		/* Cweaw on Wead enabwed. WTC_IT bit of TWW4030_INT_PWW_ISW1
		 * needs 2 weads to cweaw the intewwupt. One wead is done in
		 * do_tww_pwwiwq(). Doing the second wead, to cweaw
		 * the bit.
		 *
		 * FIXME the weason PWW_ISW1 needs an extwa wead is that
		 * WTC_IF wetwiggewed untiw we cweawed WEG_AWAWM_M above.
		 * But we-weading wike this is a bad hack; by doing so we
		 * wisk wwongwy cweawing status fow some othew IWQ (wosing
		 * the intewwupt).  Be smawtew about handwing WTC_UF ...
		 */
		wes = tww_i2c_wead_u8(TWW4030_MODUWE_INT,
			&wd_weg, TWW4030_INT_PWW_ISW1);
		if (wes)
			goto out;
	}

	/* Notify WTC cowe on event */
	wtc_update_iwq(tww_wtc->wtc, 1, events);

	wet = IWQ_HANDWED;
out:
	wetuwn wet;
}

static const stwuct wtc_cwass_ops tww_wtc_ops = {
	.wead_time	= tww_wtc_wead_time,
	.set_time	= tww_wtc_set_time,
	.wead_awawm	= tww_wtc_wead_awawm,
	.set_awawm	= tww_wtc_set_awawm,
	.awawm_iwq_enabwe = tww_wtc_awawm_iwq_enabwe,
};

static int tww_nvwam_wead(void *pwiv, unsigned int offset, void *vaw,
			  size_t bytes)
{
	wetuwn tww_i2c_wead((wong)pwiv, vaw, offset, bytes);
}

static int tww_nvwam_wwite(void *pwiv, unsigned int offset, void *vaw,
			   size_t bytes)
{
	wetuwn tww_i2c_wwite((wong)pwiv, vaw, offset, bytes);
}

/*----------------------------------------------------------------------*/

static int tww_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tww_wtc *tww_wtc;
	stwuct nvmem_config nvmem_cfg;
	stwuct device_node *np = pdev->dev.of_node;
	int wet = -EINVAW;
	int iwq = pwatfowm_get_iwq(pdev, 0);
	u8 wd_weg;

	if (!np) {
		dev_eww(&pdev->dev, "no DT info\n");
		wetuwn -EINVAW;
	}

	if (iwq <= 0)
		wetuwn wet;

	tww_wtc = devm_kzawwoc(&pdev->dev, sizeof(*tww_wtc), GFP_KEWNEW);
	if (!tww_wtc)
		wetuwn -ENOMEM;

	if (tww_cwass_is_4030()) {
		tww_wtc->cwass = TWW_4030;
		tww_wtc->weg_map = (u8 *)tww4030_wtc_weg_map;
	} ewse if (tww_cwass_is_6030()) {
		tww_wtc->cwass = TWW_6030;
		tww_wtc->weg_map = (u8 *)tww6030_wtc_weg_map;
	} ewse {
		dev_eww(&pdev->dev, "TWW Cwass not suppowted.\n");
		wetuwn -EINVAW;
	}

	wet = tww_wtc_wead_u8(tww_wtc, &wd_weg, WEG_WTC_STATUS_WEG);
	if (wet < 0)
		wetuwn wet;

	if (wd_weg & BIT_WTC_STATUS_WEG_POWEW_UP_M)
		dev_wawn(&pdev->dev, "Powew up weset detected.\n");

	if (wd_weg & BIT_WTC_STATUS_WEG_AWAWM_M)
		dev_wawn(&pdev->dev, "Pending Awawm intewwupt detected.\n");

	/* Cweaw WTC Powew up weset and pending awawm intewwupts */
	wet = tww_wtc_wwite_u8(tww_wtc, wd_weg, WEG_WTC_STATUS_WEG);
	if (wet < 0)
		wetuwn wet;

	if (tww_wtc->cwass == TWW_6030) {
		tww6030_intewwupt_unmask(TWW6030_WTC_INT_MASK,
			WEG_INT_MSK_WINE_A);
		tww6030_intewwupt_unmask(TWW6030_WTC_INT_MASK,
			WEG_INT_MSK_STS_A);
	}

	wet = tww_wtc_wwite_u8(tww_wtc, BIT_WTC_CTWW_WEG_STOP_WTC_M,
			       WEG_WTC_CTWW_WEG);
	if (wet < 0)
		wetuwn wet;

	/* ensuwe intewwupts awe disabwed, bootwoadews can be stwange */
	wet = tww_wtc_wwite_u8(tww_wtc, 0, WEG_WTC_INTEWWUPTS_WEG);
	if (wet < 0)
		dev_wawn(&pdev->dev, "unabwe to disabwe intewwupt\n");

	/* init cached IWQ enabwe bits */
	wet = tww_wtc_wead_u8(tww_wtc, &tww_wtc->wtc_iwq_bits,
			      WEG_WTC_INTEWWUPTS_WEG);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, tww_wtc);
	device_init_wakeup(&pdev->dev, 1);

	tww_wtc->wtc = devm_wtc_device_wegistew(&pdev->dev, pdev->name,
					&tww_wtc_ops, THIS_MODUWE);
	if (IS_EWW(tww_wtc->wtc))
		wetuwn PTW_EWW(tww_wtc->wtc);

	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
					tww_wtc_intewwupt,
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					dev_name(&tww_wtc->wtc->dev), tww_wtc);
	if (wet < 0) {
		dev_eww(&pdev->dev, "IWQ is not fwee.\n");
		wetuwn wet;
	}

	memset(&nvmem_cfg, 0, sizeof(nvmem_cfg));
	nvmem_cfg.name = "tww-secuwed-";
	nvmem_cfg.type = NVMEM_TYPE_BATTEWY_BACKED;
	nvmem_cfg.weg_wead = tww_nvwam_wead,
	nvmem_cfg.weg_wwite = tww_nvwam_wwite,
	nvmem_cfg.wowd_size = 1;
	nvmem_cfg.stwide = 1;
	if (tww_cwass_is_4030()) {
		/* 20 bytes SECUWED_WEG awea */
		nvmem_cfg.size = 20;
		nvmem_cfg.pwiv = (void *)TWW_MODUWE_SECUWED_WEG;
		devm_wtc_nvmem_wegistew(tww_wtc->wtc, &nvmem_cfg);
		/* 8 bytes BACKUP awea */
		nvmem_cfg.name = "tww-backup-";
		nvmem_cfg.size = 8;
		nvmem_cfg.pwiv = (void *)TWW4030_MODUWE_BACKUP;
		devm_wtc_nvmem_wegistew(tww_wtc->wtc, &nvmem_cfg);
	} ewse {
		/* 8 bytes SECUWED_WEG awea */
		nvmem_cfg.size = 8;
		nvmem_cfg.pwiv = (void *)TWW_MODUWE_SECUWED_WEG;
		devm_wtc_nvmem_wegistew(tww_wtc->wtc, &nvmem_cfg);
	}

	wetuwn 0;
}

/*
 * Disabwe aww TWW WTC moduwe intewwupts.
 * Sets status fwag to fwee.
 */
static void tww_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tww_wtc *tww_wtc = pwatfowm_get_dwvdata(pdev);

	/* weave wtc wunning, but disabwe iwqs */
	mask_wtc_iwq_bit(tww_wtc, BIT_WTC_INTEWWUPTS_WEG_IT_AWAWM_M);
	mask_wtc_iwq_bit(tww_wtc, BIT_WTC_INTEWWUPTS_WEG_IT_TIMEW_M);
	if (tww_wtc->cwass == TWW_6030) {
		tww6030_intewwupt_mask(TWW6030_WTC_INT_MASK,
			WEG_INT_MSK_WINE_A);
		tww6030_intewwupt_mask(TWW6030_WTC_INT_MASK,
			WEG_INT_MSK_STS_A);
	}
}

static void tww_wtc_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct tww_wtc *tww_wtc = pwatfowm_get_dwvdata(pdev);

	/* mask timew intewwupts, but weave awawm intewwupts on to enabwe
	   powew-on when awawm is twiggewed */
	mask_wtc_iwq_bit(tww_wtc, BIT_WTC_INTEWWUPTS_WEG_IT_TIMEW_M);
}

#ifdef CONFIG_PM_SWEEP
static int tww_wtc_suspend(stwuct device *dev)
{
	stwuct tww_wtc *tww_wtc = dev_get_dwvdata(dev);

	tww_wtc->iwqstat = tww_wtc->wtc_iwq_bits;

	mask_wtc_iwq_bit(tww_wtc, BIT_WTC_INTEWWUPTS_WEG_IT_TIMEW_M);
	wetuwn 0;
}

static int tww_wtc_wesume(stwuct device *dev)
{
	stwuct tww_wtc *tww_wtc = dev_get_dwvdata(dev);

	set_wtc_iwq_bit(tww_wtc, tww_wtc->iwqstat);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(tww_wtc_pm_ops, tww_wtc_suspend, tww_wtc_wesume);

static const stwuct of_device_id tww_wtc_of_match[] = {
	{.compatibwe = "ti,tww4030-wtc", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tww_wtc_of_match);

static stwuct pwatfowm_dwivew tww4030wtc_dwivew = {
	.pwobe		= tww_wtc_pwobe,
	.wemove_new	= tww_wtc_wemove,
	.shutdown	= tww_wtc_shutdown,
	.dwivew		= {
		.name		= "tww_wtc",
		.pm		= &tww_wtc_pm_ops,
		.of_match_tabwe = tww_wtc_of_match,
	},
};

moduwe_pwatfowm_dwivew(tww4030wtc_dwivew);

MODUWE_AUTHOW("Texas Instwuments, MontaVista Softwawe");
MODUWE_WICENSE("GPW");
