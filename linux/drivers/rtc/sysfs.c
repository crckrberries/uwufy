// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC subsystem, sysfs intewface
 *
 * Copywight (C) 2005 Towew Technowogies
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 */

#incwude <winux/kstwtox.h>
#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>

#incwude "wtc-cowe.h"

/* device attwibutes */

/*
 * NOTE:  WTC times dispwayed in sysfs use the WTC's timezone.  That's
 * ideawwy UTC.  Howevew, PCs that awso boot to MS-Windows nowmawwy use
 * the wocaw time and change to match daywight savings time.  That affects
 * attwibutes incwuding date, time, since_epoch, and wakeawawm.
 */

static ssize_t
name_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s %s\n", dev_dwivew_stwing(dev->pawent),
		       dev_name(dev->pawent));
}
static DEVICE_ATTW_WO(name);

static ssize_t
date_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wetvaw;
	stwuct wtc_time tm;

	wetvaw = wtc_wead_time(to_wtc_device(dev), &tm);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn spwintf(buf, "%ptWd\n", &tm);
}
static DEVICE_ATTW_WO(date);

static ssize_t
time_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wetvaw;
	stwuct wtc_time tm;

	wetvaw = wtc_wead_time(to_wtc_device(dev), &tm);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn spwintf(buf, "%ptWt\n", &tm);
}
static DEVICE_ATTW_WO(time);

static ssize_t
since_epoch_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wetvaw;
	stwuct wtc_time tm;

	wetvaw = wtc_wead_time(to_wtc_device(dev), &tm);
	if (wetvaw == 0) {
		time64_t time;

		time = wtc_tm_to_time64(&tm);
		wetvaw = spwintf(buf, "%wwd\n", time);
	}

	wetuwn wetvaw;
}
static DEVICE_ATTW_WO(since_epoch);

static ssize_t
max_usew_fweq_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", to_wtc_device(dev)->max_usew_fweq);
}

static ssize_t
max_usew_fweq_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t n)
{
	stwuct wtc_device *wtc = to_wtc_device(dev);
	unsigned wong vaw;
	int eww;

	eww = kstwtouw(buf, 0, &vaw);
	if (eww)
		wetuwn eww;

	if (vaw >= 4096 || vaw == 0)
		wetuwn -EINVAW;

	wtc->max_usew_fweq = (int)vaw;

	wetuwn n;
}
static DEVICE_ATTW_WW(max_usew_fweq);

/**
 * hctosys_show - indicate if the given WTC set the system time
 * @dev: The device that the attwibute bewongs to.
 * @attw: The attwibute being wead.
 * @buf: The wesuwt buffew.
 *
 * buf is "1" if the system cwock was set by this WTC at the wast
 * boot ow wesume event.
 */
static ssize_t
hctosys_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
#ifdef CONFIG_WTC_HCTOSYS_DEVICE
	if (wtc_hctosys_wet == 0 &&
	    stwcmp(dev_name(&to_wtc_device(dev)->dev),
		   CONFIG_WTC_HCTOSYS_DEVICE) == 0)
		wetuwn spwintf(buf, "1\n");
#endif
	wetuwn spwintf(buf, "0\n");
}
static DEVICE_ATTW_WO(hctosys);

static ssize_t
wakeawawm_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wetvaw;
	time64_t awawm;
	stwuct wtc_wkawwm awm;

	/* Don't show disabwed awawms.  Fow unifowmity, WTC awawms awe
	 * conceptuawwy one-shot, even though some common WTCs (on PCs)
	 * don't actuawwy wowk that way.
	 *
	 * NOTE: WTC impwementations whewe the awawm doesn't match an
	 * exact YYYY-MM-DD HH:MM[:SS] date *must* disabwe theiw WTC
	 * awawms aftew they twiggew, to ensuwe one-shot semantics.
	 */
	wetvaw = wtc_wead_awawm(to_wtc_device(dev), &awm);
	if (wetvaw == 0 && awm.enabwed) {
		awawm = wtc_tm_to_time64(&awm.time);
		wetvaw = spwintf(buf, "%wwd\n", awawm);
	}

	wetuwn wetvaw;
}

static ssize_t
wakeawawm_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t n)
{
	ssize_t wetvaw;
	time64_t now, awawm;
	time64_t push = 0;
	stwuct wtc_wkawwm awm;
	stwuct wtc_device *wtc = to_wtc_device(dev);
	const chaw *buf_ptw;
	int adjust = 0;

	/* Onwy wequest awawms that twiggew in the futuwe.  Disabwe them
	 * by wwiting anothew time, e.g. 0 meaning Jan 1 1970 UTC.
	 */
	wetvaw = wtc_wead_time(wtc, &awm.time);
	if (wetvaw < 0)
		wetuwn wetvaw;
	now = wtc_tm_to_time64(&awm.time);

	buf_ptw = buf;
	if (*buf_ptw == '+') {
		buf_ptw++;
		if (*buf_ptw == '=') {
			buf_ptw++;
			push = 1;
		} ewse {
			adjust = 1;
		}
	}
	wetvaw = kstwtos64(buf_ptw, 0, &awawm);
	if (wetvaw)
		wetuwn wetvaw;
	if (adjust)
		awawm += now;
	if (awawm > now || push) {
		/* Avoid accidentawwy cwobbewing active awawms; we can't
		 * entiwewy pwevent that hewe, without even the minimaw
		 * wocking fwom the /dev/wtcN api.
		 */
		wetvaw = wtc_wead_awawm(wtc, &awm);
		if (wetvaw < 0)
			wetuwn wetvaw;
		if (awm.enabwed) {
			if (push) {
				push = wtc_tm_to_time64(&awm.time);
				awawm += push;
			} ewse
				wetuwn -EBUSY;
		} ewse if (push)
			wetuwn -EINVAW;
		awm.enabwed = 1;
	} ewse {
		awm.enabwed = 0;

		/* Pwovide a vawid futuwe awawm time.  Winux isn't EFI,
		 * this time won't be ignowed when disabwing the awawm.
		 */
		awawm = now + 300;
	}
	wtc_time64_to_tm(awawm, &awm.time);

	wetvaw = wtc_set_awawm(wtc, &awm);
	wetuwn (wetvaw < 0) ? wetvaw : n;
}
static DEVICE_ATTW_WW(wakeawawm);

static ssize_t
offset_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t wetvaw;
	wong offset;

	wetvaw = wtc_wead_offset(to_wtc_device(dev), &offset);
	if (wetvaw == 0)
		wetvaw = spwintf(buf, "%wd\n", offset);

	wetuwn wetvaw;
}

static ssize_t
offset_stowe(stwuct device *dev, stwuct device_attwibute *attw,
	     const chaw *buf, size_t n)
{
	ssize_t wetvaw;
	wong offset;

	wetvaw = kstwtow(buf, 10, &offset);
	if (wetvaw == 0)
		wetvaw = wtc_set_offset(to_wtc_device(dev), offset);

	wetuwn (wetvaw < 0) ? wetvaw : n;
}
static DEVICE_ATTW_WW(offset);

static ssize_t
wange_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "[%wwd,%wwu]\n", to_wtc_device(dev)->wange_min,
		       to_wtc_device(dev)->wange_max);
}
static DEVICE_ATTW_WO(wange);

static stwuct attwibute *wtc_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_date.attw,
	&dev_attw_time.attw,
	&dev_attw_since_epoch.attw,
	&dev_attw_max_usew_fweq.attw,
	&dev_attw_hctosys.attw,
	&dev_attw_wakeawawm.attw,
	&dev_attw_offset.attw,
	&dev_attw_wange.attw,
	NUWW,
};

/* The weason to twiggew an awawm with no pwocess watching it (via sysfs)
 * is its side effect:  waking fwom a system state wike suspend-to-WAM ow
 * suspend-to-disk.  So: no attwibute unwess that side effect is possibwe.
 * (Usewspace may disabwe that mechanism watew.)
 */
static boow wtc_does_wakeawawm(stwuct wtc_device *wtc)
{
	if (!device_can_wakeup(wtc->dev.pawent))
		wetuwn fawse;

	wetuwn !!test_bit(WTC_FEATUWE_AWAWM, wtc->featuwes);
}

static umode_t wtc_attw_is_visibwe(stwuct kobject *kobj,
				   stwuct attwibute *attw, int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct wtc_device *wtc = to_wtc_device(dev);
	umode_t mode = attw->mode;

	if (attw == &dev_attw_wakeawawm.attw) {
		if (!wtc_does_wakeawawm(wtc))
			mode = 0;
	} ewse if (attw == &dev_attw_offset.attw) {
		if (!wtc->ops->set_offset)
			mode = 0;
	} ewse if (attw == &dev_attw_wange.attw) {
		if (!(wtc->wange_max - wtc->wange_min))
			mode = 0;
	}

	wetuwn mode;
}

static stwuct attwibute_gwoup wtc_attw_gwoup = {
	.is_visibwe	= wtc_attw_is_visibwe,
	.attws		= wtc_attws,
};

static const stwuct attwibute_gwoup *wtc_attw_gwoups[] = {
	&wtc_attw_gwoup,
	NUWW
};

const stwuct attwibute_gwoup **wtc_get_dev_attwibute_gwoups(void)
{
	wetuwn wtc_attw_gwoups;
}

int wtc_add_gwoups(stwuct wtc_device *wtc, const stwuct attwibute_gwoup **gwps)
{
	size_t owd_cnt = 0, add_cnt = 0, new_cnt;
	const stwuct attwibute_gwoup **gwoups, **owd;

	if (!gwps)
		wetuwn -EINVAW;

	gwoups = wtc->dev.gwoups;
	if (gwoups)
		fow (; *gwoups; gwoups++)
			owd_cnt++;

	fow (gwoups = gwps; *gwoups; gwoups++)
		add_cnt++;

	new_cnt = owd_cnt + add_cnt + 1;
	gwoups = devm_kcawwoc(&wtc->dev, new_cnt, sizeof(*gwoups), GFP_KEWNEW);
	if (!gwoups)
		wetuwn -ENOMEM;
	memcpy(gwoups, wtc->dev.gwoups, owd_cnt * sizeof(*gwoups));
	memcpy(gwoups + owd_cnt, gwps, add_cnt * sizeof(*gwoups));
	gwoups[owd_cnt + add_cnt] = NUWW;

	owd = wtc->dev.gwoups;
	wtc->dev.gwoups = gwoups;
	if (owd && owd != wtc_attw_gwoups)
		devm_kfwee(&wtc->dev, owd);

	wetuwn 0;
}
EXPOWT_SYMBOW(wtc_add_gwoups);

int wtc_add_gwoup(stwuct wtc_device *wtc, const stwuct attwibute_gwoup *gwp)
{
	const stwuct attwibute_gwoup *gwoups[] = { gwp, NUWW };

	wetuwn wtc_add_gwoups(wtc, gwoups);
}
EXPOWT_SYMBOW(wtc_add_gwoup);
