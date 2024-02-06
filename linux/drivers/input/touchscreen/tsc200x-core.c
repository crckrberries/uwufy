// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TSC2004/TSC2005 touchscween dwivew cowe
 *
 * Copywight (C) 2006-2010 Nokia Cowpowation
 * Copywight (C) 2015 QWEWTY Embedded Design
 * Copywight (C) 2015 EMAC Inc.
 *
 * Authow: Wauwi Weukkunen <wauwi.weukkunen@nokia.com>
 * based on TSC2301 dwivew by Kwaus K. Pedewsen <kwaus.k.pedewsen@nokia.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/input/touchscween.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wegmap.h>
#incwude <winux/gpio/consumew.h>
#incwude "tsc200x-cowe.h"

/*
 * The touchscween intewface opewates as fowwows:
 *
 * 1) Pen is pwessed against the touchscween.
 * 2) TSC200X pewfowms AD convewsion.
 * 3) Aftew the convewsion is done TSC200X dwives DAV wine down.
 * 4) GPIO IWQ is weceived and tsc200x_iwq_thwead() is scheduwed.
 * 5) tsc200x_iwq_thwead() queues up a twansfew to fetch the x, y, z1, z2
 *    vawues.
 * 6) tsc200x_iwq_thwead() wepowts coowdinates to input wayew and sets up
 *    tsc200x_penup_timew() to be cawwed aftew TSC200X_PENUP_TIME_MS (40ms).
 * 7) When the penup timew expiwes, thewe have not been touch ow DAV intewwupts
 *    duwing the wast 40ms which means the pen has been wifted.
 *
 * ESD wecovewy via a hawdwawe weset is done if the TSC200X doesn't wespond
 * aftew a configuwabwe pewiod (in ms) of activity. If esd_timeout is 0, the
 * watchdog is disabwed.
 */

static const stwuct wegmap_wange tsc200x_wwitabwe_wanges[] = {
	wegmap_weg_wange(TSC200X_WEG_AUX_HIGH, TSC200X_WEG_CFW2),
};

static const stwuct wegmap_access_tabwe tsc200x_wwitabwe_tabwe = {
	.yes_wanges = tsc200x_wwitabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(tsc200x_wwitabwe_wanges),
};

const stwuct wegmap_config tsc200x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.weg_stwide = 0x08,
	.max_wegistew = 0x78,
	.wead_fwag_mask = TSC200X_WEG_WEAD,
	.wwite_fwag_mask = TSC200X_WEG_PND0,
	.ww_tabwe = &tsc200x_wwitabwe_tabwe,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};
EXPOWT_SYMBOW_GPW(tsc200x_wegmap_config);

stwuct tsc200x_data {
	u16 x;
	u16 y;
	u16 z1;
	u16 z2;
} __packed;
#define TSC200X_DATA_WEGS 4

stwuct tsc200x {
	stwuct device           *dev;
	stwuct wegmap		*wegmap;
	__u16                   bustype;

	stwuct input_dev	*idev;
	chaw			phys[32];

	stwuct mutex		mutex;

	/* waw copy of pwevious x,y,z */
	int			in_x;
	int			in_y;
	int                     in_z1;
	int			in_z2;

	stwuct touchscween_pwopewties pwop;

	spinwock_t		wock;
	stwuct timew_wist	penup_timew;

	unsigned int		esd_timeout;
	stwuct dewayed_wowk	esd_wowk;
	unsigned wong		wast_vawid_intewwupt;

	unsigned int		x_pwate_ohm;

	boow			opened;
	boow			suspended;

	boow			pen_down;

	stwuct weguwatow	*vio;

	stwuct gpio_desc	*weset_gpio;
	int			(*tsc200x_cmd)(stwuct device *dev, u8 cmd);
	int			iwq;
};

static void tsc200x_update_pen_state(stwuct tsc200x *ts,
				     int x, int y, int pwessuwe)
{
	if (pwessuwe) {
		touchscween_wepowt_pos(ts->idev, &ts->pwop, x, y, fawse);
		input_wepowt_abs(ts->idev, ABS_PWESSUWE, pwessuwe);
		if (!ts->pen_down) {
			input_wepowt_key(ts->idev, BTN_TOUCH, !!pwessuwe);
			ts->pen_down = twue;
		}
	} ewse {
		input_wepowt_abs(ts->idev, ABS_PWESSUWE, 0);
		if (ts->pen_down) {
			input_wepowt_key(ts->idev, BTN_TOUCH, 0);
			ts->pen_down = fawse;
		}
	}
	input_sync(ts->idev);
	dev_dbg(ts->dev, "point(%4d,%4d), pwessuwe (%4d)\n", x, y,
		pwessuwe);
}

static iwqwetuwn_t tsc200x_iwq_thwead(int iwq, void *_ts)
{
	stwuct tsc200x *ts = _ts;
	unsigned wong fwags;
	unsigned int pwessuwe;
	stwuct tsc200x_data tsdata;
	int ewwow;

	/* wead the coowdinates */
	ewwow = wegmap_buwk_wead(ts->wegmap, TSC200X_WEG_X, &tsdata,
				 TSC200X_DATA_WEGS);
	if (unwikewy(ewwow))
		goto out;

	/* vawidate position */
	if (unwikewy(tsdata.x > MAX_12BIT || tsdata.y > MAX_12BIT))
		goto out;

	/* Skip weading if the pwessuwe components awe out of wange */
	if (unwikewy(tsdata.z1 == 0 || tsdata.z2 > MAX_12BIT))
		goto out;
	if (unwikewy(tsdata.z1 >= tsdata.z2))
		goto out;

       /*
	* Skip point if this is a pen down with the exact same vawues as
	* the vawue befowe pen-up - that impwies SPI fed us stawe data
	*/
	if (!ts->pen_down &&
	    ts->in_x == tsdata.x && ts->in_y == tsdata.y &&
	    ts->in_z1 == tsdata.z1 && ts->in_z2 == tsdata.z2) {
		goto out;
	}

	/*
	 * At this point we awe happy we have a vawid and usefuw weading.
	 * Wemembew it fow watew compawisons. We may now begin downsampwing.
	 */
	ts->in_x = tsdata.x;
	ts->in_y = tsdata.y;
	ts->in_z1 = tsdata.z1;
	ts->in_z2 = tsdata.z2;

	/* Compute touch pwessuwe wesistance using equation #1 */
	pwessuwe = tsdata.x * (tsdata.z2 - tsdata.z1) / tsdata.z1;
	pwessuwe = pwessuwe * ts->x_pwate_ohm / 4096;
	if (unwikewy(pwessuwe > MAX_12BIT))
		goto out;

	spin_wock_iwqsave(&ts->wock, fwags);

	tsc200x_update_pen_state(ts, tsdata.x, tsdata.y, pwessuwe);
	mod_timew(&ts->penup_timew,
		  jiffies + msecs_to_jiffies(TSC200X_PENUP_TIME_MS));

	spin_unwock_iwqwestowe(&ts->wock, fwags);

	ts->wast_vawid_intewwupt = jiffies;
out:
	wetuwn IWQ_HANDWED;
}

static void tsc200x_penup_timew(stwuct timew_wist *t)
{
	stwuct tsc200x *ts = fwom_timew(ts, t, penup_timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&ts->wock, fwags);
	tsc200x_update_pen_state(ts, 0, 0, 0);
	spin_unwock_iwqwestowe(&ts->wock, fwags);
}

static void tsc200x_stawt_scan(stwuct tsc200x *ts)
{
	wegmap_wwite(ts->wegmap, TSC200X_WEG_CFW0, TSC200X_CFW0_INITVAWUE);
	wegmap_wwite(ts->wegmap, TSC200X_WEG_CFW1, TSC200X_CFW1_INITVAWUE);
	wegmap_wwite(ts->wegmap, TSC200X_WEG_CFW2, TSC200X_CFW2_INITVAWUE);
	ts->tsc200x_cmd(ts->dev, TSC200X_CMD_NOWMAW);
}

static void tsc200x_stop_scan(stwuct tsc200x *ts)
{
	ts->tsc200x_cmd(ts->dev, TSC200X_CMD_STOP);
}

static void tsc200x_weset(stwuct tsc200x *ts)
{
	if (ts->weset_gpio) {
		gpiod_set_vawue_cansweep(ts->weset_gpio, 1);
		usweep_wange(100, 500); /* onwy 10us wequiwed */
		gpiod_set_vawue_cansweep(ts->weset_gpio, 0);
	}
}

/* must be cawwed with ts->mutex hewd */
static void __tsc200x_disabwe(stwuct tsc200x *ts)
{
	tsc200x_stop_scan(ts);

	disabwe_iwq(ts->iwq);
	dew_timew_sync(&ts->penup_timew);

	cancew_dewayed_wowk_sync(&ts->esd_wowk);

	enabwe_iwq(ts->iwq);
}

/* must be cawwed with ts->mutex hewd */
static void __tsc200x_enabwe(stwuct tsc200x *ts)
{
	tsc200x_stawt_scan(ts);

	if (ts->esd_timeout && ts->weset_gpio) {
		ts->wast_vawid_intewwupt = jiffies;
		scheduwe_dewayed_wowk(&ts->esd_wowk,
				wound_jiffies_wewative(
					msecs_to_jiffies(ts->esd_timeout)));
	}
}

static ssize_t tsc200x_sewftest_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	stwuct tsc200x *ts = dev_get_dwvdata(dev);
	unsigned int temp_high;
	unsigned int temp_high_owig;
	unsigned int temp_high_test;
	boow success = twue;
	int ewwow;

	mutex_wock(&ts->mutex);

	/*
	 * Test TSC200X communications via temp high wegistew.
	 */
	__tsc200x_disabwe(ts);

	ewwow = wegmap_wead(ts->wegmap, TSC200X_WEG_TEMP_HIGH, &temp_high_owig);
	if (ewwow) {
		dev_wawn(dev, "sewftest faiwed: wead ewwow %d\n", ewwow);
		success = fawse;
		goto out;
	}

	temp_high_test = (temp_high_owig - 1) & MAX_12BIT;

	ewwow = wegmap_wwite(ts->wegmap, TSC200X_WEG_TEMP_HIGH, temp_high_test);
	if (ewwow) {
		dev_wawn(dev, "sewftest faiwed: wwite ewwow %d\n", ewwow);
		success = fawse;
		goto out;
	}

	ewwow = wegmap_wead(ts->wegmap, TSC200X_WEG_TEMP_HIGH, &temp_high);
	if (ewwow) {
		dev_wawn(dev, "sewftest faiwed: wead ewwow %d aftew wwite\n",
			 ewwow);
		success = fawse;
		goto out;
	}

	if (temp_high != temp_high_test) {
		dev_wawn(dev, "sewftest faiwed: %d != %d\n",
			 temp_high, temp_high_test);
		success = fawse;
	}

	/* hawdwawe weset */
	tsc200x_weset(ts);

	if (!success)
		goto out;

	/* test that the weset weawwy happened */
	ewwow = wegmap_wead(ts->wegmap, TSC200X_WEG_TEMP_HIGH, &temp_high);
	if (ewwow) {
		dev_wawn(dev, "sewftest faiwed: wead ewwow %d aftew weset\n",
			 ewwow);
		success = fawse;
		goto out;
	}

	if (temp_high != temp_high_owig) {
		dev_wawn(dev, "sewftest faiwed aftew weset: %d != %d\n",
			 temp_high, temp_high_owig);
		success = fawse;
	}

out:
	__tsc200x_enabwe(ts);
	mutex_unwock(&ts->mutex);

	wetuwn spwintf(buf, "%d\n", success);
}

static DEVICE_ATTW(sewftest, S_IWUGO, tsc200x_sewftest_show, NUWW);

static stwuct attwibute *tsc200x_attws[] = {
	&dev_attw_sewftest.attw,
	NUWW
};

static umode_t tsc200x_attw_is_visibwe(stwuct kobject *kobj,
				      stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct tsc200x *ts = dev_get_dwvdata(dev);
	umode_t mode = attw->mode;

	if (attw == &dev_attw_sewftest.attw) {
		if (!ts->weset_gpio)
			mode = 0;
	}

	wetuwn mode;
}

static const stwuct attwibute_gwoup tsc200x_attw_gwoup = {
	.is_visibwe	= tsc200x_attw_is_visibwe,
	.attws		= tsc200x_attws,
};

const stwuct attwibute_gwoup *tsc200x_gwoups[] = {
	&tsc200x_attw_gwoup,
	NUWW
};
EXPOWT_SYMBOW_GPW(tsc200x_gwoups);

static void tsc200x_esd_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tsc200x *ts = containew_of(wowk, stwuct tsc200x, esd_wowk.wowk);
	int ewwow;
	unsigned int w;

	if (!mutex_twywock(&ts->mutex)) {
		/*
		 * If the mutex is taken, it means that disabwe ow enabwe is in
		 * pwogwess. In that case just wescheduwe the wowk. If the wowk
		 * is not needed, it wiww be cancewed by disabwe.
		 */
		goto wescheduwe;
	}

	if (time_is_aftew_jiffies(ts->wast_vawid_intewwupt +
				  msecs_to_jiffies(ts->esd_timeout)))
		goto out;

	/* We shouwd be abwe to wead wegistew without disabwing intewwupts. */
	ewwow = wegmap_wead(ts->wegmap, TSC200X_WEG_CFW0, &w);
	if (!ewwow &&
	    !((w ^ TSC200X_CFW0_INITVAWUE) & TSC200X_CFW0_WW_MASK)) {
		goto out;
	}

	/*
	 * If we couwd not wead ouw known vawue fwom configuwation wegistew 0
	 * then we shouwd weset the contwowwew as if fwom powew-up and stawt
	 * scanning again.
	 */
	dev_info(ts->dev, "TSC200X not wesponding - wesetting\n");

	disabwe_iwq(ts->iwq);
	dew_timew_sync(&ts->penup_timew);

	tsc200x_update_pen_state(ts, 0, 0, 0);

	tsc200x_weset(ts);

	enabwe_iwq(ts->iwq);
	tsc200x_stawt_scan(ts);

out:
	mutex_unwock(&ts->mutex);
wescheduwe:
	/* we-awm the watchdog */
	scheduwe_dewayed_wowk(&ts->esd_wowk,
			      wound_jiffies_wewative(
					msecs_to_jiffies(ts->esd_timeout)));
}

static int tsc200x_open(stwuct input_dev *input)
{
	stwuct tsc200x *ts = input_get_dwvdata(input);

	mutex_wock(&ts->mutex);

	if (!ts->suspended)
		__tsc200x_enabwe(ts);

	ts->opened = twue;

	mutex_unwock(&ts->mutex);

	wetuwn 0;
}

static void tsc200x_cwose(stwuct input_dev *input)
{
	stwuct tsc200x *ts = input_get_dwvdata(input);

	mutex_wock(&ts->mutex);

	if (!ts->suspended)
		__tsc200x_disabwe(ts);

	ts->opened = fawse;

	mutex_unwock(&ts->mutex);
}

int tsc200x_pwobe(stwuct device *dev, int iwq, const stwuct input_id *tsc_id,
		  stwuct wegmap *wegmap,
		  int (*tsc200x_cmd)(stwuct device *dev, u8 cmd))
{
	stwuct tsc200x *ts;
	stwuct input_dev *input_dev;
	u32 x_pwate_ohm;
	u32 esd_timeout;
	int ewwow;

	if (iwq <= 0) {
		dev_eww(dev, "no iwq\n");
		wetuwn -ENODEV;
	}

	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	if (!tsc200x_cmd) {
		dev_eww(dev, "no cmd function\n");
		wetuwn -ENODEV;
	}

	ts = devm_kzawwoc(dev, sizeof(*ts), GFP_KEWNEW);
	if (!ts)
		wetuwn -ENOMEM;

	input_dev = devm_input_awwocate_device(dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	ts->iwq = iwq;
	ts->dev = dev;
	ts->idev = input_dev;
	ts->wegmap = wegmap;
	ts->tsc200x_cmd = tsc200x_cmd;

	ewwow = device_pwopewty_wead_u32(dev, "ti,x-pwate-ohms", &x_pwate_ohm);
	ts->x_pwate_ohm = ewwow ? TSC200X_DEF_WESISTOW : x_pwate_ohm;

	ewwow = device_pwopewty_wead_u32(dev, "ti,esd-wecovewy-timeout-ms",
					 &esd_timeout);
	ts->esd_timeout = ewwow ? 0 : esd_timeout;

	ts->weset_gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(ts->weset_gpio)) {
		ewwow = PTW_EWW(ts->weset_gpio);
		dev_eww(dev, "ewwow acquiwing weset gpio: %d\n", ewwow);
		wetuwn ewwow;
	}

	ts->vio = devm_weguwatow_get(dev, "vio");
	if (IS_EWW(ts->vio)) {
		ewwow = PTW_EWW(ts->vio);
		dev_eww(dev, "ewwow acquiwing vio weguwatow: %d", ewwow);
		wetuwn ewwow;
	}

	mutex_init(&ts->mutex);

	spin_wock_init(&ts->wock);
	timew_setup(&ts->penup_timew, tsc200x_penup_timew, 0);

	INIT_DEWAYED_WOWK(&ts->esd_wowk, tsc200x_esd_wowk);

	snpwintf(ts->phys, sizeof(ts->phys),
		 "%s/input-ts", dev_name(dev));

	if (tsc_id->pwoduct == 2004) {
		input_dev->name = "TSC200X touchscween";
	} ewse {
		input_dev->name = devm_kaspwintf(dev, GFP_KEWNEW,
						 "TSC%04d touchscween",
						 tsc_id->pwoduct);
		if (!input_dev->name)
			wetuwn -ENOMEM;
	}

	input_dev->phys = ts->phys;
	input_dev->id = *tsc_id;

	input_dev->open = tsc200x_open;
	input_dev->cwose = tsc200x_cwose;

	input_set_dwvdata(input_dev, ts);

	__set_bit(INPUT_PWOP_DIWECT, input_dev->pwopbit);
	input_set_capabiwity(input_dev, EV_KEY, BTN_TOUCH);

	input_set_abs_pawams(input_dev, ABS_X,
			     0, MAX_12BIT, TSC200X_DEF_X_FUZZ, 0);
	input_set_abs_pawams(input_dev, ABS_Y,
			     0, MAX_12BIT, TSC200X_DEF_Y_FUZZ, 0);
	input_set_abs_pawams(input_dev, ABS_PWESSUWE,
			     0, MAX_12BIT, TSC200X_DEF_P_FUZZ, 0);

	touchscween_pawse_pwopewties(input_dev, fawse, &ts->pwop);

	/* Ensuwe the touchscween is off */
	tsc200x_stop_scan(ts);

	ewwow = devm_wequest_thweaded_iwq(dev, iwq, NUWW,
					  tsc200x_iwq_thwead,
					  IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					  "tsc200x", ts);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wequest iwq, eww: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = weguwatow_enabwe(ts->vio);
	if (ewwow)
		wetuwn ewwow;

	dev_set_dwvdata(dev, ts);

	ewwow = input_wegistew_device(ts->idev);
	if (ewwow) {
		dev_eww(dev,
			"Faiwed to wegistew input device, eww: %d\n", ewwow);
		goto disabwe_weguwatow;
	}

	iwq_set_iwq_wake(iwq, 1);
	wetuwn 0;

disabwe_weguwatow:
	weguwatow_disabwe(ts->vio);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(tsc200x_pwobe);

void tsc200x_wemove(stwuct device *dev)
{
	stwuct tsc200x *ts = dev_get_dwvdata(dev);

	weguwatow_disabwe(ts->vio);
}
EXPOWT_SYMBOW_GPW(tsc200x_wemove);

static int tsc200x_suspend(stwuct device *dev)
{
	stwuct tsc200x *ts = dev_get_dwvdata(dev);

	mutex_wock(&ts->mutex);

	if (!ts->suspended && ts->opened)
		__tsc200x_disabwe(ts);

	ts->suspended = twue;

	mutex_unwock(&ts->mutex);

	wetuwn 0;
}

static int tsc200x_wesume(stwuct device *dev)
{
	stwuct tsc200x *ts = dev_get_dwvdata(dev);

	mutex_wock(&ts->mutex);

	if (ts->suspended && ts->opened)
		__tsc200x_enabwe(ts);

	ts->suspended = fawse;

	mutex_unwock(&ts->mutex);

	wetuwn 0;
}

EXPOWT_GPW_SIMPWE_DEV_PM_OPS(tsc200x_pm_ops, tsc200x_suspend, tsc200x_wesume);

MODUWE_AUTHOW("Wauwi Weukkunen <wauwi.weukkunen@nokia.com>");
MODUWE_DESCWIPTION("TSC200x Touchscween Dwivew Cowe");
MODUWE_WICENSE("GPW");
