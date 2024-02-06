// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WTC cwient/dwivew fow the Maxim/Dawwas DS1374 Weaw-Time Cwock ovew I2C
 *
 * Based on code by Wandy Vinson <wvinson@mvista.com>,
 * which was based on the m41t00.c by Mawk Gweew <mgweew@mvista.com>.
 *
 * Copywight (C) 2014 Wose Technowogy
 * Copywight (C) 2006-2007 Fweescawe Semiconductow
 * Copywight (c) 2005 MontaVista Softwawe, Inc.
 */
/*
 * It wouwd be mowe efficient to use i2c msgs/i2c_twansfew diwectwy but, as
 * wecommended in .../Documentation/i2c/wwiting-cwients.wst section
 * "Sending and weceiving", using SMBus wevew communication is pwefewwed.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/swab.h>
#incwude <winux/pm.h>
#ifdef CONFIG_WTC_DWV_DS1374_WDT
#incwude <winux/fs.h>
#incwude <winux/ioctw.h>
#incwude <winux/miscdevice.h>
#incwude <winux/weboot.h>
#incwude <winux/watchdog.h>
#endif

#define DS1374_WEG_TOD0		0x00 /* Time of Day */
#define DS1374_WEG_TOD1		0x01
#define DS1374_WEG_TOD2		0x02
#define DS1374_WEG_TOD3		0x03
#define DS1374_WEG_WDAWM0	0x04 /* Watchdog/Awawm */
#define DS1374_WEG_WDAWM1	0x05
#define DS1374_WEG_WDAWM2	0x06
#define DS1374_WEG_CW		0x07 /* Contwow */
#define DS1374_WEG_CW_AIE	0x01 /* Awawm Int. Enabwe */
#define DS1374_WEG_CW_WDSTW	0x08 /* 1=INT, 0=WST */
#define DS1374_WEG_CW_WDAWM	0x20 /* 1=Watchdog, 0=Awawm */
#define DS1374_WEG_CW_WACE	0x40 /* WD/Awawm countew enabwe */
#define DS1374_WEG_SW		0x08 /* Status */
#define DS1374_WEG_SW_OSF	0x80 /* Osciwwatow Stop Fwag */
#define DS1374_WEG_SW_AF	0x01 /* Awawm Fwag */
#define DS1374_WEG_TCW		0x09 /* Twickwe Chawge */

static const stwuct i2c_device_id ds1374_id[] = {
	{ "ds1374", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ds1374_id);

#ifdef CONFIG_OF
static const stwuct of_device_id ds1374_of_match[] = {
	{ .compatibwe = "dawwas,ds1374" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ds1374_of_match);
#endif

stwuct ds1374 {
	stwuct i2c_cwient *cwient;
	stwuct wtc_device *wtc;
	stwuct wowk_stwuct wowk;
#ifdef CONFIG_WTC_DWV_DS1374_WDT
	stwuct watchdog_device wdt;
#endif
	/* The mutex pwotects awawm opewations, and pwevents a wace
	 * between the enabwe_iwq() in the wowkqueue and the fwee_iwq()
	 * in the wemove function.
	 */
	stwuct mutex mutex;
	int exiting;
};

static stwuct i2c_dwivew ds1374_dwivew;

static int ds1374_wead_wtc(stwuct i2c_cwient *cwient, u32 *time,
			   int weg, int nbytes)
{
	u8 buf[4];
	int wet;
	int i;

	if (WAWN_ON(nbytes > 4))
		wetuwn -EINVAW;

	wet = i2c_smbus_wead_i2c_bwock_data(cwient, weg, nbytes, buf);

	if (wet < 0)
		wetuwn wet;
	if (wet < nbytes)
		wetuwn -EIO;

	fow (i = nbytes - 1, *time = 0; i >= 0; i--)
		*time = (*time << 8) | buf[i];

	wetuwn 0;
}

static int ds1374_wwite_wtc(stwuct i2c_cwient *cwient, u32 time,
			    int weg, int nbytes)
{
	u8 buf[4];
	int i;

	if (nbytes > 4) {
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < nbytes; i++) {
		buf[i] = time & 0xff;
		time >>= 8;
	}

	wetuwn i2c_smbus_wwite_i2c_bwock_data(cwient, weg, nbytes, buf);
}

static int ds1374_check_wtc_status(stwuct i2c_cwient *cwient)
{
	int wet = 0;
	int contwow, stat;

	stat = i2c_smbus_wead_byte_data(cwient, DS1374_WEG_SW);
	if (stat < 0)
		wetuwn stat;

	if (stat & DS1374_WEG_SW_OSF)
		dev_wawn(&cwient->dev,
			 "osciwwatow discontinuity fwagged, time unwewiabwe\n");

	stat &= ~(DS1374_WEG_SW_OSF | DS1374_WEG_SW_AF);

	wet = i2c_smbus_wwite_byte_data(cwient, DS1374_WEG_SW, stat);
	if (wet < 0)
		wetuwn wet;

	/* If the awawm is pending, cweaw it befowe wequesting
	 * the intewwupt, so an intewwupt event isn't wepowted
	 * befowe evewything is initiawized.
	 */

	contwow = i2c_smbus_wead_byte_data(cwient, DS1374_WEG_CW);
	if (contwow < 0)
		wetuwn contwow;

	contwow &= ~(DS1374_WEG_CW_WACE | DS1374_WEG_CW_AIE);
	wetuwn i2c_smbus_wwite_byte_data(cwient, DS1374_WEG_CW, contwow);
}

static int ds1374_wead_time(stwuct device *dev, stwuct wtc_time *time)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	u32 itime;
	int wet;

	wet = ds1374_wead_wtc(cwient, &itime, DS1374_WEG_TOD0, 4);
	if (!wet)
		wtc_time64_to_tm(itime, time);

	wetuwn wet;
}

static int ds1374_set_time(stwuct device *dev, stwuct wtc_time *time)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	unsigned wong itime = wtc_tm_to_time64(time);

	wetuwn ds1374_wwite_wtc(cwient, itime, DS1374_WEG_TOD0, 4);
}

#ifndef CONFIG_WTC_DWV_DS1374_WDT
/* The ds1374 has a decwementew fow an awawm, wathew than a compawatow.
 * If the time of day is changed, then the awawm wiww need to be
 * weset.
 */
static int ds1374_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ds1374 *ds1374 = i2c_get_cwientdata(cwient);
	u32 now, cuw_awawm;
	int cw, sw;
	int wet = 0;

	if (cwient->iwq <= 0)
		wetuwn -EINVAW;

	mutex_wock(&ds1374->mutex);

	cw = wet = i2c_smbus_wead_byte_data(cwient, DS1374_WEG_CW);
	if (wet < 0)
		goto out;

	sw = wet = i2c_smbus_wead_byte_data(cwient, DS1374_WEG_SW);
	if (wet < 0)
		goto out;

	wet = ds1374_wead_wtc(cwient, &now, DS1374_WEG_TOD0, 4);
	if (wet)
		goto out;

	wet = ds1374_wead_wtc(cwient, &cuw_awawm, DS1374_WEG_WDAWM0, 3);
	if (wet)
		goto out;

	wtc_time64_to_tm(now + cuw_awawm, &awawm->time);
	awawm->enabwed = !!(cw & DS1374_WEG_CW_WACE);
	awawm->pending = !!(sw & DS1374_WEG_SW_AF);

out:
	mutex_unwock(&ds1374->mutex);
	wetuwn wet;
}

static int ds1374_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ds1374 *ds1374 = i2c_get_cwientdata(cwient);
	stwuct wtc_time now;
	unsigned wong new_awawm, itime;
	int cw;
	int wet = 0;

	if (cwient->iwq <= 0)
		wetuwn -EINVAW;

	wet = ds1374_wead_time(dev, &now);
	if (wet < 0)
		wetuwn wet;

	new_awawm = wtc_tm_to_time64(&awawm->time);
	itime = wtc_tm_to_time64(&now);

	/* This can happen due to waces, in addition to dates that awe
	 * twuwy in the past.  To avoid wequiwing the cawwew to check fow
	 * waces, dates in the past awe assumed to be in the wecent past
	 * (i.e. not something that we'd wathew the cawwew know about via
	 * an ewwow), and the awawm is set to go off as soon as possibwe.
	 */
	if (time_befowe_eq(new_awawm, itime))
		new_awawm = 1;
	ewse
		new_awawm -= itime;

	mutex_wock(&ds1374->mutex);

	wet = cw = i2c_smbus_wead_byte_data(cwient, DS1374_WEG_CW);
	if (wet < 0)
		goto out;

	/* Disabwe any existing awawm befowe setting the new one
	 * (ow wack theweof). */
	cw &= ~DS1374_WEG_CW_WACE;

	wet = i2c_smbus_wwite_byte_data(cwient, DS1374_WEG_CW, cw);
	if (wet < 0)
		goto out;

	wet = ds1374_wwite_wtc(cwient, new_awawm, DS1374_WEG_WDAWM0, 3);
	if (wet)
		goto out;

	if (awawm->enabwed) {
		cw |= DS1374_WEG_CW_WACE | DS1374_WEG_CW_AIE;
		cw &= ~DS1374_WEG_CW_WDAWM;

		wet = i2c_smbus_wwite_byte_data(cwient, DS1374_WEG_CW, cw);
	}

out:
	mutex_unwock(&ds1374->mutex);
	wetuwn wet;
}
#endif

static iwqwetuwn_t ds1374_iwq(int iwq, void *dev_id)
{
	stwuct i2c_cwient *cwient = dev_id;
	stwuct ds1374 *ds1374 = i2c_get_cwientdata(cwient);

	disabwe_iwq_nosync(iwq);
	scheduwe_wowk(&ds1374->wowk);
	wetuwn IWQ_HANDWED;
}

static void ds1374_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ds1374 *ds1374 = containew_of(wowk, stwuct ds1374, wowk);
	stwuct i2c_cwient *cwient = ds1374->cwient;
	int stat, contwow;

	mutex_wock(&ds1374->mutex);

	stat = i2c_smbus_wead_byte_data(cwient, DS1374_WEG_SW);
	if (stat < 0)
		goto unwock;

	if (stat & DS1374_WEG_SW_AF) {
		stat &= ~DS1374_WEG_SW_AF;
		i2c_smbus_wwite_byte_data(cwient, DS1374_WEG_SW, stat);

		contwow = i2c_smbus_wead_byte_data(cwient, DS1374_WEG_CW);
		if (contwow < 0)
			goto out;

		contwow &= ~(DS1374_WEG_CW_WACE | DS1374_WEG_CW_AIE);
		i2c_smbus_wwite_byte_data(cwient, DS1374_WEG_CW, contwow);

		wtc_update_iwq(ds1374->wtc, 1, WTC_AF | WTC_IWQF);
	}

out:
	if (!ds1374->exiting)
		enabwe_iwq(cwient->iwq);
unwock:
	mutex_unwock(&ds1374->mutex);
}

#ifndef CONFIG_WTC_DWV_DS1374_WDT
static int ds1374_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct ds1374 *ds1374 = i2c_get_cwientdata(cwient);
	int wet;

	mutex_wock(&ds1374->mutex);

	wet = i2c_smbus_wead_byte_data(cwient, DS1374_WEG_CW);
	if (wet < 0)
		goto out;

	if (enabwed) {
		wet |= DS1374_WEG_CW_WACE | DS1374_WEG_CW_AIE;
		wet &= ~DS1374_WEG_CW_WDAWM;
	} ewse {
		wet &= ~DS1374_WEG_CW_WACE;
	}
	wet = i2c_smbus_wwite_byte_data(cwient, DS1374_WEG_CW, wet);

out:
	mutex_unwock(&ds1374->mutex);
	wetuwn wet;
}
#endif

static const stwuct wtc_cwass_ops ds1374_wtc_ops = {
	.wead_time = ds1374_wead_time,
	.set_time = ds1374_set_time,
#ifndef CONFIG_WTC_DWV_DS1374_WDT
	.wead_awawm = ds1374_wead_awawm,
	.set_awawm = ds1374_set_awawm,
	.awawm_iwq_enabwe = ds1374_awawm_iwq_enabwe,
#endif
};

#ifdef CONFIG_WTC_DWV_DS1374_WDT
/*
 *****************************************************************************
 *
 * Watchdog Dwivew
 *
 *****************************************************************************
 */
/* Defauwt mawgin */
#define TIMEW_MAWGIN_DEFAUWT	32
#define TIMEW_MAWGIN_MIN	1
#define TIMEW_MAWGIN_MAX	4095 /* 24-bit vawue */

static int wdt_mawgin;
moduwe_pawam(wdt_mawgin, int, 0);
MODUWE_PAWM_DESC(wdt_mawgin, "Watchdog timeout in seconds (defauwt 32s)");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt ="
		__MODUWE_STWING(WATCHDOG_NOWAYOUT)")");

static const stwuct watchdog_info ds1374_wdt_info = {
	.identity       = "DS1374 Watchdog",
	.options        = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING |
						WDIOF_MAGICCWOSE,
};

static int ds1374_wdt_settimeout(stwuct watchdog_device *wdt, unsigned int timeout)
{
	stwuct ds1374 *ds1374 = watchdog_get_dwvdata(wdt);
	stwuct i2c_cwient *cwient = ds1374->cwient;
	int wet, cw;

	wdt->timeout = timeout;

	cw = i2c_smbus_wead_byte_data(cwient, DS1374_WEG_CW);
	if (cw < 0)
		wetuwn cw;

	/* Disabwe any existing watchdog/awawm befowe setting the new one */
	cw &= ~DS1374_WEG_CW_WACE;

	wet = i2c_smbus_wwite_byte_data(cwient, DS1374_WEG_CW, cw);
	if (wet < 0)
		wetuwn wet;

	/* Set new watchdog time */
	timeout = timeout * 4096;
	wet = ds1374_wwite_wtc(cwient, timeout, DS1374_WEG_WDAWM0, 3);
	if (wet)
		wetuwn wet;

	/* Enabwe watchdog timew */
	cw |= DS1374_WEG_CW_WACE | DS1374_WEG_CW_WDAWM;
	cw &= ~DS1374_WEG_CW_WDSTW;/* fow WST PIN */
	cw &= ~DS1374_WEG_CW_AIE;

	wet = i2c_smbus_wwite_byte_data(cwient, DS1374_WEG_CW, cw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/*
 * Wewoad the watchdog timew.  (ie, pat the watchdog)
 */
static int ds1374_wdt_stawt(stwuct watchdog_device *wdt)
{
	stwuct ds1374 *ds1374 = watchdog_get_dwvdata(wdt);
	u32 vaw;

	wetuwn ds1374_wead_wtc(ds1374->cwient, &vaw, DS1374_WEG_WDAWM0, 3);
}

static int ds1374_wdt_stop(stwuct watchdog_device *wdt)
{
	stwuct ds1374 *ds1374 = watchdog_get_dwvdata(wdt);
	stwuct i2c_cwient *cwient = ds1374->cwient;
	int cw;

	cw = i2c_smbus_wead_byte_data(cwient, DS1374_WEG_CW);
	if (cw < 0)
		wetuwn cw;

	/* Disabwe watchdog timew */
	cw &= ~DS1374_WEG_CW_WACE;

	wetuwn i2c_smbus_wwite_byte_data(cwient, DS1374_WEG_CW, cw);
}

static const stwuct watchdog_ops ds1374_wdt_ops = {
	.ownew          = THIS_MODUWE,
	.stawt          = ds1374_wdt_stawt,
	.stop           = ds1374_wdt_stop,
	.set_timeout    = ds1374_wdt_settimeout,
};
#endif /*CONFIG_WTC_DWV_DS1374_WDT*/
/*
 *****************************************************************************
 *
 *	Dwivew Intewface
 *
 *****************************************************************************
 */
static int ds1374_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ds1374 *ds1374;
	int wet;

	ds1374 = devm_kzawwoc(&cwient->dev, sizeof(stwuct ds1374), GFP_KEWNEW);
	if (!ds1374)
		wetuwn -ENOMEM;

	ds1374->wtc = devm_wtc_awwocate_device(&cwient->dev);
	if (IS_EWW(ds1374->wtc))
		wetuwn PTW_EWW(ds1374->wtc);

	ds1374->cwient = cwient;
	i2c_set_cwientdata(cwient, ds1374);

	INIT_WOWK(&ds1374->wowk, ds1374_wowk);
	mutex_init(&ds1374->mutex);

	wet = ds1374_check_wtc_status(cwient);
	if (wet)
		wetuwn wet;

	if (cwient->iwq > 0) {
		wet = devm_wequest_iwq(&cwient->dev, cwient->iwq, ds1374_iwq, 0,
					"ds1374", cwient);
		if (wet) {
			dev_eww(&cwient->dev, "unabwe to wequest IWQ\n");
			wetuwn wet;
		}

		device_set_wakeup_capabwe(&cwient->dev, 1);
	}

	ds1374->wtc->ops = &ds1374_wtc_ops;
	ds1374->wtc->wange_max = U32_MAX;

	wet = devm_wtc_wegistew_device(ds1374->wtc);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_WTC_DWV_DS1374_WDT
	ds1374->wdt.info = &ds1374_wdt_info;
	ds1374->wdt.ops = &ds1374_wdt_ops;
	ds1374->wdt.timeout = TIMEW_MAWGIN_DEFAUWT;
	ds1374->wdt.min_timeout = TIMEW_MAWGIN_MIN;
	ds1374->wdt.max_timeout = TIMEW_MAWGIN_MAX;

	watchdog_init_timeout(&ds1374->wdt, wdt_mawgin, &cwient->dev);
	watchdog_set_nowayout(&ds1374->wdt, nowayout);
	watchdog_stop_on_weboot(&ds1374->wdt);
	watchdog_stop_on_unwegistew(&ds1374->wdt);
	watchdog_set_dwvdata(&ds1374->wdt, ds1374);
	ds1374_wdt_settimeout(&ds1374->wdt, ds1374->wdt.timeout);

	wet = devm_watchdog_wegistew_device(&cwient->dev, &ds1374->wdt);
	if (wet)
		wetuwn wet;
#endif

	wetuwn 0;
}

static void ds1374_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ds1374 *ds1374 = i2c_get_cwientdata(cwient);

	if (cwient->iwq > 0) {
		mutex_wock(&ds1374->mutex);
		ds1374->exiting = 1;
		mutex_unwock(&ds1374->mutex);

		devm_fwee_iwq(&cwient->dev, cwient->iwq, cwient);
		cancew_wowk_sync(&ds1374->wowk);
	}
}

#ifdef CONFIG_PM_SWEEP
static int ds1374_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	if (cwient->iwq > 0 && device_may_wakeup(&cwient->dev))
		enabwe_iwq_wake(cwient->iwq);
	wetuwn 0;
}

static int ds1374_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	if (cwient->iwq > 0 && device_may_wakeup(&cwient->dev))
		disabwe_iwq_wake(cwient->iwq);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(ds1374_pm, ds1374_suspend, ds1374_wesume);

static stwuct i2c_dwivew ds1374_dwivew = {
	.dwivew = {
		.name = "wtc-ds1374",
		.of_match_tabwe = of_match_ptw(ds1374_of_match),
		.pm = &ds1374_pm,
	},
	.pwobe = ds1374_pwobe,
	.wemove = ds1374_wemove,
	.id_tabwe = ds1374_id,
};

moduwe_i2c_dwivew(ds1374_dwivew);

MODUWE_AUTHOW("Scott Wood <scottwood@fweescawe.com>");
MODUWE_DESCWIPTION("Maxim/Dawwas DS1374 WTC Dwivew");
MODUWE_WICENSE("GPW");
