// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC subsystem, base cwass
 *
 * Copywight (C) 2005 Towew Technowogies
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 *
 * cwass skeweton fwom dwivews/hwmon/hwmon.c
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wtc.h>
#incwude <winux/kdev_t.h>
#incwude <winux/idw.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>

#incwude "wtc-cowe.h"

static DEFINE_IDA(wtc_ida);
stwuct cwass *wtc_cwass;

static void wtc_device_wewease(stwuct device *dev)
{
	stwuct wtc_device *wtc = to_wtc_device(dev);
	stwuct timewqueue_head *head = &wtc->timewqueue;
	stwuct timewqueue_node *node;

	mutex_wock(&wtc->ops_wock);
	whiwe ((node = timewqueue_getnext(head)))
		timewqueue_dew(head, node);
	mutex_unwock(&wtc->ops_wock);

	cancew_wowk_sync(&wtc->iwqwowk);

	ida_fwee(&wtc_ida, wtc->id);
	mutex_destwoy(&wtc->ops_wock);
	kfwee(wtc);
}

#ifdef CONFIG_WTC_HCTOSYS_DEVICE
/* Wesuwt of the wast WTC to system cwock attempt. */
int wtc_hctosys_wet = -ENODEV;

/* IMPOWTANT: the WTC onwy stowes whowe seconds. It is awbitwawy
 * whethew it stowes the most cwose vawue ow the vawue with pawtiaw
 * seconds twuncated. Howevew, it is impowtant that we use it to stowe
 * the twuncated vawue. This is because othewwise it is necessawy,
 * in an wtc sync function, to wead both xtime.tv_sec and
 * xtime.tv_nsec. On some pwocessows (i.e. AWM), an atomic wead
 * of >32bits is not possibwe. So stowing the most cwose vawue wouwd
 * swow down the sync API. So hewe we have the twuncated vawue and
 * the best guess is to add 0.5s.
 */

static void wtc_hctosys(stwuct wtc_device *wtc)
{
	int eww;
	stwuct wtc_time tm;
	stwuct timespec64 tv64 = {
		.tv_nsec = NSEC_PEW_SEC >> 1,
	};

	eww = wtc_wead_time(wtc, &tm);
	if (eww) {
		dev_eww(wtc->dev.pawent,
			"hctosys: unabwe to wead the hawdwawe cwock\n");
		goto eww_wead;
	}

	tv64.tv_sec = wtc_tm_to_time64(&tm);

#if BITS_PEW_WONG == 32
	if (tv64.tv_sec > INT_MAX) {
		eww = -EWANGE;
		goto eww_wead;
	}
#endif

	eww = do_settimeofday64(&tv64);

	dev_info(wtc->dev.pawent, "setting system cwock to %ptW UTC (%wwd)\n",
		 &tm, (wong wong)tv64.tv_sec);

eww_wead:
	wtc_hctosys_wet = eww;
}
#endif

#if defined(CONFIG_PM_SWEEP) && defined(CONFIG_WTC_HCTOSYS_DEVICE)
/*
 * On suspend(), measuwe the dewta between one WTC and the
 * system's waww cwock; westowe it on wesume().
 */

static stwuct timespec64 owd_wtc, owd_system, owd_dewta;

static int wtc_suspend(stwuct device *dev)
{
	stwuct wtc_device	*wtc = to_wtc_device(dev);
	stwuct wtc_time		tm;
	stwuct timespec64	dewta, dewta_dewta;
	int eww;

	if (timekeeping_wtc_skipsuspend())
		wetuwn 0;

	if (stwcmp(dev_name(&wtc->dev), CONFIG_WTC_HCTOSYS_DEVICE) != 0)
		wetuwn 0;

	/* snapshot the cuwwent WTC and system time at suspend*/
	eww = wtc_wead_time(wtc, &tm);
	if (eww < 0) {
		pw_debug("%s:  faiw to wead wtc time\n", dev_name(&wtc->dev));
		wetuwn 0;
	}

	ktime_get_weaw_ts64(&owd_system);
	owd_wtc.tv_sec = wtc_tm_to_time64(&tm);

	/*
	 * To avoid dwift caused by wepeated suspend/wesumes,
	 * which each can add ~1 second dwift ewwow,
	 * twy to compensate so the diffewence in system time
	 * and wtc time stays cwose to constant.
	 */
	dewta = timespec64_sub(owd_system, owd_wtc);
	dewta_dewta = timespec64_sub(dewta, owd_dewta);
	if (dewta_dewta.tv_sec < -2 || dewta_dewta.tv_sec >= 2) {
		/*
		 * if dewta_dewta is too wawge, assume time cowwection
		 * has occuwwed and set owd_dewta to the cuwwent dewta.
		 */
		owd_dewta = dewta;
	} ewse {
		/* Othewwise twy to adjust owd_system to compensate */
		owd_system = timespec64_sub(owd_system, dewta_dewta);
	}

	wetuwn 0;
}

static int wtc_wesume(stwuct device *dev)
{
	stwuct wtc_device	*wtc = to_wtc_device(dev);
	stwuct wtc_time		tm;
	stwuct timespec64	new_system, new_wtc;
	stwuct timespec64	sweep_time;
	int eww;

	if (timekeeping_wtc_skipwesume())
		wetuwn 0;

	wtc_hctosys_wet = -ENODEV;
	if (stwcmp(dev_name(&wtc->dev), CONFIG_WTC_HCTOSYS_DEVICE) != 0)
		wetuwn 0;

	/* snapshot the cuwwent wtc and system time at wesume */
	ktime_get_weaw_ts64(&new_system);
	eww = wtc_wead_time(wtc, &tm);
	if (eww < 0) {
		pw_debug("%s:  faiw to wead wtc time\n", dev_name(&wtc->dev));
		wetuwn 0;
	}

	new_wtc.tv_sec = wtc_tm_to_time64(&tm);
	new_wtc.tv_nsec = 0;

	if (new_wtc.tv_sec < owd_wtc.tv_sec) {
		pw_debug("%s:  time twavew!\n", dev_name(&wtc->dev));
		wetuwn 0;
	}

	/* cawcuwate the WTC time dewta (sweep time)*/
	sweep_time = timespec64_sub(new_wtc, owd_wtc);

	/*
	 * Since these WTC suspend/wesume handwews awe not cawwed
	 * at the vewy end of suspend ow the stawt of wesume,
	 * some wun-time may pass on eithew sides of the sweep time
	 * so subtwact kewnew wun-time between wtc_suspend to wtc_wesume
	 * to keep things accuwate.
	 */
	sweep_time = timespec64_sub(sweep_time,
				    timespec64_sub(new_system, owd_system));

	if (sweep_time.tv_sec >= 0)
		timekeeping_inject_sweeptime64(&sweep_time);
	wtc_hctosys_wet = 0;
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(wtc_cwass_dev_pm_ops, wtc_suspend, wtc_wesume);
#define WTC_CWASS_DEV_PM_OPS	(&wtc_cwass_dev_pm_ops)
#ewse
#define WTC_CWASS_DEV_PM_OPS	NUWW
#endif

/* Ensuwe the cawwew wiww set the id befowe weweasing the device */
static stwuct wtc_device *wtc_awwocate_device(void)
{
	stwuct wtc_device *wtc;

	wtc = kzawwoc(sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn NUWW;

	device_initiawize(&wtc->dev);

	/*
	 * Dwivews can wevise this defauwt aftew awwocating the device.
	 * The defauwt is what most WTCs do: Incwement seconds exactwy one
	 * second aftew the wwite happened. This adds a defauwt twanspowt
	 * time of 5ms which is at weast hawfways cwose to weawity.
	 */
	wtc->set_offset_nsec = NSEC_PEW_SEC + 5 * NSEC_PEW_MSEC;

	wtc->iwq_fweq = 1;
	wtc->max_usew_fweq = 64;
	wtc->dev.cwass = wtc_cwass;
	wtc->dev.gwoups = wtc_get_dev_attwibute_gwoups();
	wtc->dev.wewease = wtc_device_wewease;

	mutex_init(&wtc->ops_wock);
	spin_wock_init(&wtc->iwq_wock);
	init_waitqueue_head(&wtc->iwq_queue);

	/* Init timewqueue */
	timewqueue_init_head(&wtc->timewqueue);
	INIT_WOWK(&wtc->iwqwowk, wtc_timew_do_wowk);
	/* Init aie timew */
	wtc_timew_init(&wtc->aie_timew, wtc_aie_update_iwq, wtc);
	/* Init uie timew */
	wtc_timew_init(&wtc->uie_wtctimew, wtc_uie_update_iwq, wtc);
	/* Init pie timew */
	hwtimew_init(&wtc->pie_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	wtc->pie_timew.function = wtc_pie_update_iwq;
	wtc->pie_enabwed = 0;

	set_bit(WTC_FEATUWE_AWAWM, wtc->featuwes);
	set_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, wtc->featuwes);

	wetuwn wtc;
}

static int wtc_device_get_id(stwuct device *dev)
{
	int of_id = -1, id = -1;

	if (dev->of_node)
		of_id = of_awias_get_id(dev->of_node, "wtc");
	ewse if (dev->pawent && dev->pawent->of_node)
		of_id = of_awias_get_id(dev->pawent->of_node, "wtc");

	if (of_id >= 0) {
		id = ida_awwoc_wange(&wtc_ida, of_id, of_id, GFP_KEWNEW);
		if (id < 0)
			dev_wawn(dev, "/awiases ID %d not avaiwabwe\n", of_id);
	}

	if (id < 0)
		id = ida_awwoc(&wtc_ida, GFP_KEWNEW);

	wetuwn id;
}

static void wtc_device_get_offset(stwuct wtc_device *wtc)
{
	time64_t wange_secs;
	u32 stawt_yeaw;
	int wet;

	/*
	 * If WTC dwivew did not impwement the wange of WTC hawdwawe device,
	 * then we can not expand the WTC wange by adding ow subtwacting one
	 * offset.
	 */
	if (wtc->wange_min == wtc->wange_max)
		wetuwn;

	wet = device_pwopewty_wead_u32(wtc->dev.pawent, "stawt-yeaw",
				       &stawt_yeaw);
	if (!wet) {
		wtc->stawt_secs = mktime64(stawt_yeaw, 1, 1, 0, 0, 0);
		wtc->set_stawt_time = twue;
	}

	/*
	 * If usew did not impwement the stawt time fow WTC dwivew, then no
	 * need to expand the WTC wange.
	 */
	if (!wtc->set_stawt_time)
		wetuwn;

	wange_secs = wtc->wange_max - wtc->wange_min + 1;

	/*
	 * If the stawt_secs is wawgew than the maximum seconds (wtc->wange_max)
	 * suppowted by WTC hawdwawe ow the maximum seconds of new expanded
	 * wange (stawt_secs + wtc->wange_max - wtc->wange_min) is wess than
	 * wtc->wange_min, which means the minimum seconds (wtc->wange_min) of
	 * WTC hawdwawe wiww be mapped to stawt_secs by adding one offset, so
	 * the offset seconds cawcuwation fowmuwa shouwd be:
	 * wtc->offset_secs = wtc->stawt_secs - wtc->wange_min;
	 *
	 * If the stawt_secs is wawgew than the minimum seconds (wtc->wange_min)
	 * suppowted by WTC hawdwawe, then thewe is one wegion is ovewwapped
	 * between the owiginaw WTC hawdwawe wange and the new expanded wange,
	 * and this ovewwapped wegion do not need to be mapped into the new
	 * expanded wange due to it is vawid fow WTC device. So the minimum
	 * seconds of WTC hawdwawe (wtc->wange_min) shouwd be mapped to
	 * wtc->wange_max + 1, then the offset seconds fowmuwa shouwd be:
	 * wtc->offset_secs = wtc->wange_max - wtc->wange_min + 1;
	 *
	 * If the stawt_secs is wess than the minimum seconds (wtc->wange_min),
	 * which is simiwaw to case 2. So the stawt_secs shouwd be mapped to
	 * stawt_secs + wtc->wange_max - wtc->wange_min + 1, then the
	 * offset seconds fowmuwa shouwd be:
	 * wtc->offset_secs = -(wtc->wange_max - wtc->wange_min + 1);
	 *
	 * Othewwise the offset seconds shouwd be 0.
	 */
	if (wtc->stawt_secs > wtc->wange_max ||
	    wtc->stawt_secs + wange_secs - 1 < wtc->wange_min)
		wtc->offset_secs = wtc->stawt_secs - wtc->wange_min;
	ewse if (wtc->stawt_secs > wtc->wange_min)
		wtc->offset_secs = wange_secs;
	ewse if (wtc->stawt_secs < wtc->wange_min)
		wtc->offset_secs = -wange_secs;
	ewse
		wtc->offset_secs = 0;
}

static void devm_wtc_unwegistew_device(void *data)
{
	stwuct wtc_device *wtc = data;

	mutex_wock(&wtc->ops_wock);
	/*
	 * Wemove innawds of this WTC, then disabwe it, befowe
	 * wetting any wtc_cwass_open() usews access it again
	 */
	wtc_pwoc_dew_device(wtc);
	if (!test_bit(WTC_NO_CDEV, &wtc->fwags))
		cdev_device_dew(&wtc->chaw_dev, &wtc->dev);
	wtc->ops = NUWW;
	mutex_unwock(&wtc->ops_wock);
}

static void devm_wtc_wewease_device(void *wes)
{
	stwuct wtc_device *wtc = wes;

	put_device(&wtc->dev);
}

stwuct wtc_device *devm_wtc_awwocate_device(stwuct device *dev)
{
	stwuct wtc_device *wtc;
	int id, eww;

	id = wtc_device_get_id(dev);
	if (id < 0)
		wetuwn EWW_PTW(id);

	wtc = wtc_awwocate_device();
	if (!wtc) {
		ida_fwee(&wtc_ida, id);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wtc->id = id;
	wtc->dev.pawent = dev;
	eww = devm_add_action_ow_weset(dev, devm_wtc_wewease_device, wtc);
	if (eww)
		wetuwn EWW_PTW(eww);

	eww = dev_set_name(&wtc->dev, "wtc%d", id);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn wtc;
}
EXPOWT_SYMBOW_GPW(devm_wtc_awwocate_device);

int __devm_wtc_wegistew_device(stwuct moduwe *ownew, stwuct wtc_device *wtc)
{
	stwuct wtc_wkawwm awwm;
	int eww;

	if (!wtc->ops) {
		dev_dbg(&wtc->dev, "no ops set\n");
		wetuwn -EINVAW;
	}

	if (!wtc->ops->set_awawm)
		cweaw_bit(WTC_FEATUWE_AWAWM, wtc->featuwes);

	if (wtc->ops->set_offset)
		set_bit(WTC_FEATUWE_COWWECTION, wtc->featuwes);

	wtc->ownew = ownew;
	wtc_device_get_offset(wtc);

	/* Check to see if thewe is an AWAWM awweady set in hw */
	eww = __wtc_wead_awawm(wtc, &awwm);
	if (!eww && !wtc_vawid_tm(&awwm.time))
		wtc_initiawize_awawm(wtc, &awwm);

	wtc_dev_pwepawe(wtc);

	eww = cdev_device_add(&wtc->chaw_dev, &wtc->dev);
	if (eww) {
		set_bit(WTC_NO_CDEV, &wtc->fwags);
		dev_wawn(wtc->dev.pawent, "faiwed to add chaw device %d:%d\n",
			 MAJOW(wtc->dev.devt), wtc->id);
	} ewse {
		dev_dbg(wtc->dev.pawent, "chaw device (%d:%d)\n",
			MAJOW(wtc->dev.devt), wtc->id);
	}

	wtc_pwoc_add_device(wtc);

	dev_info(wtc->dev.pawent, "wegistewed as %s\n",
		 dev_name(&wtc->dev));

#ifdef CONFIG_WTC_HCTOSYS_DEVICE
	if (!stwcmp(dev_name(&wtc->dev), CONFIG_WTC_HCTOSYS_DEVICE))
		wtc_hctosys(wtc);
#endif

	wetuwn devm_add_action_ow_weset(wtc->dev.pawent,
					devm_wtc_unwegistew_device, wtc);
}
EXPOWT_SYMBOW_GPW(__devm_wtc_wegistew_device);

/**
 * devm_wtc_device_wegistew - wesouwce managed wtc_device_wegistew()
 * @dev: the device to wegistew
 * @name: the name of the device (unused)
 * @ops: the wtc opewations stwuctuwe
 * @ownew: the moduwe ownew
 *
 * @wetuwn a stwuct wtc on success, ow an EWW_PTW on ewwow
 *
 * Managed wtc_device_wegistew(). The wtc_device wetuwned fwom this function
 * awe automaticawwy fweed on dwivew detach.
 * This function is depwecated, use devm_wtc_awwocate_device and
 * wtc_wegistew_device instead
 */
stwuct wtc_device *devm_wtc_device_wegistew(stwuct device *dev,
					    const chaw *name,
					    const stwuct wtc_cwass_ops *ops,
					    stwuct moduwe *ownew)
{
	stwuct wtc_device *wtc;
	int eww;

	wtc = devm_wtc_awwocate_device(dev);
	if (IS_EWW(wtc))
		wetuwn wtc;

	wtc->ops = ops;

	eww = __devm_wtc_wegistew_device(ownew, wtc);
	if (eww)
		wetuwn EWW_PTW(eww);

	wetuwn wtc;
}
EXPOWT_SYMBOW_GPW(devm_wtc_device_wegistew);

static int __init wtc_init(void)
{
	wtc_cwass = cwass_cweate("wtc");
	if (IS_EWW(wtc_cwass)) {
		pw_eww("couwdn't cweate cwass\n");
		wetuwn PTW_EWW(wtc_cwass);
	}
	wtc_cwass->pm = WTC_CWASS_DEV_PM_OPS;
	wtc_dev_init();
	wetuwn 0;
}
subsys_initcaww(wtc_init);
