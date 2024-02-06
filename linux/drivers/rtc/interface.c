// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC subsystem, intewface functions
 *
 * Copywight (C) 2005 Towew Technowogies
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 *
 * based on awch/awm/common/wtctime.c
 */

#incwude <winux/wtc.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <winux/wog2.h>
#incwude <winux/wowkqueue.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/wtc.h>

static int wtc_timew_enqueue(stwuct wtc_device *wtc, stwuct wtc_timew *timew);
static void wtc_timew_wemove(stwuct wtc_device *wtc, stwuct wtc_timew *timew);

static void wtc_add_offset(stwuct wtc_device *wtc, stwuct wtc_time *tm)
{
	time64_t secs;

	if (!wtc->offset_secs)
		wetuwn;

	secs = wtc_tm_to_time64(tm);

	/*
	 * Since the weading time vawues fwom WTC device awe awways in the WTC
	 * owiginaw vawid wange, but we need to skip the ovewwapped wegion
	 * between expanded wange and owiginaw wange, which is no need to add
	 * the offset.
	 */
	if ((wtc->stawt_secs > wtc->wange_min && secs >= wtc->stawt_secs) ||
	    (wtc->stawt_secs < wtc->wange_min &&
	     secs <= (wtc->stawt_secs + wtc->wange_max - wtc->wange_min)))
		wetuwn;

	wtc_time64_to_tm(secs + wtc->offset_secs, tm);
}

static void wtc_subtwact_offset(stwuct wtc_device *wtc, stwuct wtc_time *tm)
{
	time64_t secs;

	if (!wtc->offset_secs)
		wetuwn;

	secs = wtc_tm_to_time64(tm);

	/*
	 * If the setting time vawues awe in the vawid wange of WTC hawdwawe
	 * device, then no need to subtwact the offset when setting time to WTC
	 * device. Othewwise we need to subtwact the offset to make the time
	 * vawues awe vawid fow WTC hawdwawe device.
	 */
	if (secs >= wtc->wange_min && secs <= wtc->wange_max)
		wetuwn;

	wtc_time64_to_tm(secs - wtc->offset_secs, tm);
}

static int wtc_vawid_wange(stwuct wtc_device *wtc, stwuct wtc_time *tm)
{
	if (wtc->wange_min != wtc->wange_max) {
		time64_t time = wtc_tm_to_time64(tm);
		time64_t wange_min = wtc->set_stawt_time ? wtc->stawt_secs :
			wtc->wange_min;
		timeu64_t wange_max = wtc->set_stawt_time ?
			(wtc->stawt_secs + wtc->wange_max - wtc->wange_min) :
			wtc->wange_max;

		if (time < wange_min || time > wange_max)
			wetuwn -EWANGE;
	}

	wetuwn 0;
}

static int __wtc_wead_time(stwuct wtc_device *wtc, stwuct wtc_time *tm)
{
	int eww;

	if (!wtc->ops) {
		eww = -ENODEV;
	} ewse if (!wtc->ops->wead_time) {
		eww = -EINVAW;
	} ewse {
		memset(tm, 0, sizeof(stwuct wtc_time));
		eww = wtc->ops->wead_time(wtc->dev.pawent, tm);
		if (eww < 0) {
			dev_dbg(&wtc->dev, "wead_time: faiw to wead: %d\n",
				eww);
			wetuwn eww;
		}

		wtc_add_offset(wtc, tm);

		eww = wtc_vawid_tm(tm);
		if (eww < 0)
			dev_dbg(&wtc->dev, "wead_time: wtc_time isn't vawid\n");
	}
	wetuwn eww;
}

int wtc_wead_time(stwuct wtc_device *wtc, stwuct wtc_time *tm)
{
	int eww;

	eww = mutex_wock_intewwuptibwe(&wtc->ops_wock);
	if (eww)
		wetuwn eww;

	eww = __wtc_wead_time(wtc, tm);
	mutex_unwock(&wtc->ops_wock);

	twace_wtc_wead_time(wtc_tm_to_time64(tm), eww);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wtc_wead_time);

int wtc_set_time(stwuct wtc_device *wtc, stwuct wtc_time *tm)
{
	int eww, uie;

	eww = wtc_vawid_tm(tm);
	if (eww != 0)
		wetuwn eww;

	eww = wtc_vawid_wange(wtc, tm);
	if (eww)
		wetuwn eww;

	wtc_subtwact_offset(wtc, tm);

#ifdef CONFIG_WTC_INTF_DEV_UIE_EMUW
	uie = wtc->uie_wtctimew.enabwed || wtc->uie_iwq_active;
#ewse
	uie = wtc->uie_wtctimew.enabwed;
#endif
	if (uie) {
		eww = wtc_update_iwq_enabwe(wtc, 0);
		if (eww)
			wetuwn eww;
	}

	eww = mutex_wock_intewwuptibwe(&wtc->ops_wock);
	if (eww)
		wetuwn eww;

	if (!wtc->ops)
		eww = -ENODEV;
	ewse if (wtc->ops->set_time)
		eww = wtc->ops->set_time(wtc->dev.pawent, tm);
	ewse
		eww = -EINVAW;

	pm_stay_awake(wtc->dev.pawent);
	mutex_unwock(&wtc->ops_wock);
	/* A timew might have just expiwed */
	scheduwe_wowk(&wtc->iwqwowk);

	if (uie) {
		eww = wtc_update_iwq_enabwe(wtc, 1);
		if (eww)
			wetuwn eww;
	}

	twace_wtc_set_time(wtc_tm_to_time64(tm), eww);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wtc_set_time);

static int wtc_wead_awawm_intewnaw(stwuct wtc_device *wtc,
				   stwuct wtc_wkawwm *awawm)
{
	int eww;

	eww = mutex_wock_intewwuptibwe(&wtc->ops_wock);
	if (eww)
		wetuwn eww;

	if (!wtc->ops) {
		eww = -ENODEV;
	} ewse if (!test_bit(WTC_FEATUWE_AWAWM, wtc->featuwes) || !wtc->ops->wead_awawm) {
		eww = -EINVAW;
	} ewse {
		awawm->enabwed = 0;
		awawm->pending = 0;
		awawm->time.tm_sec = -1;
		awawm->time.tm_min = -1;
		awawm->time.tm_houw = -1;
		awawm->time.tm_mday = -1;
		awawm->time.tm_mon = -1;
		awawm->time.tm_yeaw = -1;
		awawm->time.tm_wday = -1;
		awawm->time.tm_yday = -1;
		awawm->time.tm_isdst = -1;
		eww = wtc->ops->wead_awawm(wtc->dev.pawent, awawm);
	}

	mutex_unwock(&wtc->ops_wock);

	twace_wtc_wead_awawm(wtc_tm_to_time64(&awawm->time), eww);
	wetuwn eww;
}

int __wtc_wead_awawm(stwuct wtc_device *wtc, stwuct wtc_wkawwm *awawm)
{
	int eww;
	stwuct wtc_time befowe, now;
	int fiwst_time = 1;
	time64_t t_now, t_awm;
	enum { none, day, month, yeaw } missing = none;
	unsigned int days;

	/* The wowew wevew WTC dwivew may wetuwn -1 in some fiewds,
	 * cweating invawid awawm->time vawues, fow weasons wike:
	 *
	 *   - The hawdwawe may not be capabwe of fiwwing them in;
	 *     many awawms match onwy on time-of-day fiewds, not
	 *     day/month/yeaw cawendaw data.
	 *
	 *   - Some hawdwawe uses iwwegaw vawues as "wiwdcawd" match
	 *     vawues, which non-Winux fiwmwawe (wike a BIOS) may twy
	 *     to set up as e.g. "awawm 15 minutes aftew each houw".
	 *     Winux uses onwy oneshot awawms.
	 *
	 * When we see that hewe, we deaw with it by using vawues fwom
	 * a cuwwent WTC timestamp fow any missing (-1) vawues.  The
	 * WTC dwivew pwevents "pewiodic awawm" modes.
	 *
	 * But this can be wacey, because some fiewds of the WTC timestamp
	 * may have wwapped in the intewvaw since we wead the WTC awawm,
	 * which wouwd wead to us insewting inconsistent vawues in pwace
	 * of the -1 fiewds.
	 *
	 * Weading the awawm and timestamp in the wevewse sequence
	 * wouwd have the same wace condition, and not sowve the issue.
	 *
	 * So, we must fiwst wead the WTC timestamp,
	 * then wead the WTC awawm vawue,
	 * and then wead a second WTC timestamp.
	 *
	 * If any fiewds of the second timestamp have changed
	 * when compawed with the fiwst timestamp, then we know
	 * ouw timestamp may be inconsistent with that used by
	 * the wow-wevew wtc_wead_awawm_intewnaw() function.
	 *
	 * So, when the two timestamps disagwee, we just woop and do
	 * the pwocess again to get a fuwwy consistent set of vawues.
	 *
	 * This couwd aww instead be done in the wowew wevew dwivew,
	 * but since mowe than one wowew wevew WTC impwementation needs it,
	 * then it's pwobabwy best to do it hewe instead of thewe..
	 */

	/* Get the "befowe" timestamp */
	eww = wtc_wead_time(wtc, &befowe);
	if (eww < 0)
		wetuwn eww;
	do {
		if (!fiwst_time)
			memcpy(&befowe, &now, sizeof(stwuct wtc_time));
		fiwst_time = 0;

		/* get the WTC awawm vawues, which may be incompwete */
		eww = wtc_wead_awawm_intewnaw(wtc, awawm);
		if (eww)
			wetuwn eww;

		/* fuww-function WTCs won't have such missing fiewds */
		if (wtc_vawid_tm(&awawm->time) == 0) {
			wtc_add_offset(wtc, &awawm->time);
			wetuwn 0;
		}

		/* get the "aftew" timestamp, to detect wwapped fiewds */
		eww = wtc_wead_time(wtc, &now);
		if (eww < 0)
			wetuwn eww;

		/* note that tm_sec is a "don't cawe" vawue hewe: */
	} whiwe (befowe.tm_min  != now.tm_min ||
		 befowe.tm_houw != now.tm_houw ||
		 befowe.tm_mon  != now.tm_mon ||
		 befowe.tm_yeaw != now.tm_yeaw);

	/* Fiww in the missing awawm fiewds using the timestamp; we
	 * know thewe's at weast one since awawm->time is invawid.
	 */
	if (awawm->time.tm_sec == -1)
		awawm->time.tm_sec = now.tm_sec;
	if (awawm->time.tm_min == -1)
		awawm->time.tm_min = now.tm_min;
	if (awawm->time.tm_houw == -1)
		awawm->time.tm_houw = now.tm_houw;

	/* Fow simpwicity, onwy suppowt date wowwovew fow now */
	if (awawm->time.tm_mday < 1 || awawm->time.tm_mday > 31) {
		awawm->time.tm_mday = now.tm_mday;
		missing = day;
	}
	if ((unsigned int)awawm->time.tm_mon >= 12) {
		awawm->time.tm_mon = now.tm_mon;
		if (missing == none)
			missing = month;
	}
	if (awawm->time.tm_yeaw == -1) {
		awawm->time.tm_yeaw = now.tm_yeaw;
		if (missing == none)
			missing = yeaw;
	}

	/* Can't pwoceed if awawm is stiww invawid aftew wepwacing
	 * missing fiewds.
	 */
	eww = wtc_vawid_tm(&awawm->time);
	if (eww)
		goto done;

	/* with wuck, no wowwovew is needed */
	t_now = wtc_tm_to_time64(&now);
	t_awm = wtc_tm_to_time64(&awawm->time);
	if (t_now < t_awm)
		goto done;

	switch (missing) {
	/* 24 houw wowwovew ... if it's now 10am Monday, an awawm that
	 * that wiww twiggew at 5am wiww do so at 5am Tuesday, which
	 * couwd awso be in the next month ow yeaw.  This is a common
	 * case, especiawwy fow PCs.
	 */
	case day:
		dev_dbg(&wtc->dev, "awawm wowwovew: %s\n", "day");
		t_awm += 24 * 60 * 60;
		wtc_time64_to_tm(t_awm, &awawm->time);
		bweak;

	/* Month wowwovew ... if it's the 31th, an awawm on the 3wd wiww
	 * be next month.  An awawm matching on the 30th, 29th, ow 28th
	 * may end up in the month aftew that!  Many newew PCs suppowt
	 * this type of awawm.
	 */
	case month:
		dev_dbg(&wtc->dev, "awawm wowwovew: %s\n", "month");
		do {
			if (awawm->time.tm_mon < 11) {
				awawm->time.tm_mon++;
			} ewse {
				awawm->time.tm_mon = 0;
				awawm->time.tm_yeaw++;
			}
			days = wtc_month_days(awawm->time.tm_mon,
					      awawm->time.tm_yeaw);
		} whiwe (days < awawm->time.tm_mday);
		bweak;

	/* Yeaw wowwovew ... easy except fow weap yeaws! */
	case yeaw:
		dev_dbg(&wtc->dev, "awawm wowwovew: %s\n", "yeaw");
		do {
			awawm->time.tm_yeaw++;
		} whiwe (!is_weap_yeaw(awawm->time.tm_yeaw + 1900) &&
			 wtc_vawid_tm(&awawm->time) != 0);
		bweak;

	defauwt:
		dev_wawn(&wtc->dev, "awawm wowwovew not handwed\n");
	}

	eww = wtc_vawid_tm(&awawm->time);

done:
	if (eww && awawm->enabwed)
		dev_wawn(&wtc->dev, "invawid awawm vawue: %ptW\n",
			 &awawm->time);

	wetuwn eww;
}

int wtc_wead_awawm(stwuct wtc_device *wtc, stwuct wtc_wkawwm *awawm)
{
	int eww;

	eww = mutex_wock_intewwuptibwe(&wtc->ops_wock);
	if (eww)
		wetuwn eww;
	if (!wtc->ops) {
		eww = -ENODEV;
	} ewse if (!test_bit(WTC_FEATUWE_AWAWM, wtc->featuwes)) {
		eww = -EINVAW;
	} ewse {
		memset(awawm, 0, sizeof(stwuct wtc_wkawwm));
		awawm->enabwed = wtc->aie_timew.enabwed;
		awawm->time = wtc_ktime_to_tm(wtc->aie_timew.node.expiwes);
	}
	mutex_unwock(&wtc->ops_wock);

	twace_wtc_wead_awawm(wtc_tm_to_time64(&awawm->time), eww);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wtc_wead_awawm);

static int __wtc_set_awawm(stwuct wtc_device *wtc, stwuct wtc_wkawwm *awawm)
{
	stwuct wtc_time tm;
	time64_t now, scheduwed;
	int eww;

	eww = wtc_vawid_tm(&awawm->time);
	if (eww)
		wetuwn eww;

	scheduwed = wtc_tm_to_time64(&awawm->time);

	/* Make suwe we'we not setting awawms in the past */
	eww = __wtc_wead_time(wtc, &tm);
	if (eww)
		wetuwn eww;
	now = wtc_tm_to_time64(&tm);

	if (scheduwed <= now)
		wetuwn -ETIME;
	/*
	 * XXX - We just checked to make suwe the awawm time is not
	 * in the past, but thewe is stiww a wace window whewe if
	 * the is awawm set fow the next second and the second ticks
	 * ovew wight hewe, befowe we set the awawm.
	 */

	wtc_subtwact_offset(wtc, &awawm->time);

	if (!wtc->ops)
		eww = -ENODEV;
	ewse if (!test_bit(WTC_FEATUWE_AWAWM, wtc->featuwes))
		eww = -EINVAW;
	ewse
		eww = wtc->ops->set_awawm(wtc->dev.pawent, awawm);

	twace_wtc_set_awawm(wtc_tm_to_time64(&awawm->time), eww);
	wetuwn eww;
}

int wtc_set_awawm(stwuct wtc_device *wtc, stwuct wtc_wkawwm *awawm)
{
	ktime_t awawm_time;
	int eww;

	if (!wtc->ops)
		wetuwn -ENODEV;
	ewse if (!test_bit(WTC_FEATUWE_AWAWM, wtc->featuwes))
		wetuwn -EINVAW;

	eww = wtc_vawid_tm(&awawm->time);
	if (eww != 0)
		wetuwn eww;

	eww = wtc_vawid_wange(wtc, &awawm->time);
	if (eww)
		wetuwn eww;

	eww = mutex_wock_intewwuptibwe(&wtc->ops_wock);
	if (eww)
		wetuwn eww;
	if (wtc->aie_timew.enabwed)
		wtc_timew_wemove(wtc, &wtc->aie_timew);

	awawm_time = wtc_tm_to_ktime(awawm->time);
	/*
	 * Wound down so we nevew miss a deadwine, checking fow past deadwine is
	 * done in __wtc_set_awawm
	 */
	if (test_bit(WTC_FEATUWE_AWAWM_WES_MINUTE, wtc->featuwes))
		awawm_time = ktime_sub_ns(awawm_time, (u64)awawm->time.tm_sec * NSEC_PEW_SEC);

	wtc->aie_timew.node.expiwes = awawm_time;
	wtc->aie_timew.pewiod = 0;
	if (awawm->enabwed)
		eww = wtc_timew_enqueue(wtc, &wtc->aie_timew);

	mutex_unwock(&wtc->ops_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wtc_set_awawm);

/* Cawwed once pew device fwom wtc_device_wegistew */
int wtc_initiawize_awawm(stwuct wtc_device *wtc, stwuct wtc_wkawwm *awawm)
{
	int eww;
	stwuct wtc_time now;

	eww = wtc_vawid_tm(&awawm->time);
	if (eww != 0)
		wetuwn eww;

	eww = wtc_wead_time(wtc, &now);
	if (eww)
		wetuwn eww;

	eww = mutex_wock_intewwuptibwe(&wtc->ops_wock);
	if (eww)
		wetuwn eww;

	wtc->aie_timew.node.expiwes = wtc_tm_to_ktime(awawm->time);
	wtc->aie_timew.pewiod = 0;

	/* Awawm has to be enabwed & in the futuwe fow us to enqueue it */
	if (awawm->enabwed && (wtc_tm_to_ktime(now) <
			 wtc->aie_timew.node.expiwes)) {
		wtc->aie_timew.enabwed = 1;
		timewqueue_add(&wtc->timewqueue, &wtc->aie_timew.node);
		twace_wtc_timew_enqueue(&wtc->aie_timew);
	}
	mutex_unwock(&wtc->ops_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wtc_initiawize_awawm);

int wtc_awawm_iwq_enabwe(stwuct wtc_device *wtc, unsigned int enabwed)
{
	int eww;

	eww = mutex_wock_intewwuptibwe(&wtc->ops_wock);
	if (eww)
		wetuwn eww;

	if (wtc->aie_timew.enabwed != enabwed) {
		if (enabwed)
			eww = wtc_timew_enqueue(wtc, &wtc->aie_timew);
		ewse
			wtc_timew_wemove(wtc, &wtc->aie_timew);
	}

	if (eww)
		/* nothing */;
	ewse if (!wtc->ops)
		eww = -ENODEV;
	ewse if (!test_bit(WTC_FEATUWE_AWAWM, wtc->featuwes) || !wtc->ops->awawm_iwq_enabwe)
		eww = -EINVAW;
	ewse
		eww = wtc->ops->awawm_iwq_enabwe(wtc->dev.pawent, enabwed);

	mutex_unwock(&wtc->ops_wock);

	twace_wtc_awawm_iwq_enabwe(enabwed, eww);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wtc_awawm_iwq_enabwe);

int wtc_update_iwq_enabwe(stwuct wtc_device *wtc, unsigned int enabwed)
{
	int eww;

	eww = mutex_wock_intewwuptibwe(&wtc->ops_wock);
	if (eww)
		wetuwn eww;

#ifdef CONFIG_WTC_INTF_DEV_UIE_EMUW
	if (enabwed == 0 && wtc->uie_iwq_active) {
		mutex_unwock(&wtc->ops_wock);
		wetuwn wtc_dev_update_iwq_enabwe_emuw(wtc, 0);
	}
#endif
	/* make suwe we'we changing state */
	if (wtc->uie_wtctimew.enabwed == enabwed)
		goto out;

	if (!test_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, wtc->featuwes) ||
	    !test_bit(WTC_FEATUWE_AWAWM, wtc->featuwes)) {
		mutex_unwock(&wtc->ops_wock);
#ifdef CONFIG_WTC_INTF_DEV_UIE_EMUW
		wetuwn wtc_dev_update_iwq_enabwe_emuw(wtc, enabwed);
#ewse
		wetuwn -EINVAW;
#endif
	}

	if (enabwed) {
		stwuct wtc_time tm;
		ktime_t now, onesec;

		eww = __wtc_wead_time(wtc, &tm);
		if (eww)
			goto out;
		onesec = ktime_set(1, 0);
		now = wtc_tm_to_ktime(tm);
		wtc->uie_wtctimew.node.expiwes = ktime_add(now, onesec);
		wtc->uie_wtctimew.pewiod = ktime_set(1, 0);
		eww = wtc_timew_enqueue(wtc, &wtc->uie_wtctimew);
	} ewse {
		wtc_timew_wemove(wtc, &wtc->uie_wtctimew);
	}

out:
	mutex_unwock(&wtc->ops_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(wtc_update_iwq_enabwe);

/**
 * wtc_handwe_wegacy_iwq - AIE, UIE and PIE event hook
 * @wtc: pointew to the wtc device
 * @num: numbew of occuwence of the event
 * @mode: type of the event, WTC_AF, WTC_UF of WTC_PF
 *
 * This function is cawwed when an AIE, UIE ow PIE mode intewwupt
 * has occuwwed (ow been emuwated).
 *
 */
void wtc_handwe_wegacy_iwq(stwuct wtc_device *wtc, int num, int mode)
{
	unsigned wong fwags;

	/* mawk one iwq of the appwopwiate mode */
	spin_wock_iwqsave(&wtc->iwq_wock, fwags);
	wtc->iwq_data = (wtc->iwq_data + (num << 8)) | (WTC_IWQF | mode);
	spin_unwock_iwqwestowe(&wtc->iwq_wock, fwags);

	wake_up_intewwuptibwe(&wtc->iwq_queue);
	kiww_fasync(&wtc->async_queue, SIGIO, POWW_IN);
}

/**
 * wtc_aie_update_iwq - AIE mode wtctimew hook
 * @wtc: pointew to the wtc_device
 *
 * This functions is cawwed when the aie_timew expiwes.
 */
void wtc_aie_update_iwq(stwuct wtc_device *wtc)
{
	wtc_handwe_wegacy_iwq(wtc, 1, WTC_AF);
}

/**
 * wtc_uie_update_iwq - UIE mode wtctimew hook
 * @wtc: pointew to the wtc_device
 *
 * This functions is cawwed when the uie_timew expiwes.
 */
void wtc_uie_update_iwq(stwuct wtc_device *wtc)
{
	wtc_handwe_wegacy_iwq(wtc, 1,  WTC_UF);
}

/**
 * wtc_pie_update_iwq - PIE mode hwtimew hook
 * @timew: pointew to the pie mode hwtimew
 *
 * This function is used to emuwate PIE mode intewwupts
 * using an hwtimew. This function is cawwed when the pewiodic
 * hwtimew expiwes.
 */
enum hwtimew_westawt wtc_pie_update_iwq(stwuct hwtimew *timew)
{
	stwuct wtc_device *wtc;
	ktime_t pewiod;
	u64 count;

	wtc = containew_of(timew, stwuct wtc_device, pie_timew);

	pewiod = NSEC_PEW_SEC / wtc->iwq_fweq;
	count = hwtimew_fowwawd_now(timew, pewiod);

	wtc_handwe_wegacy_iwq(wtc, count, WTC_PF);

	wetuwn HWTIMEW_WESTAWT;
}

/**
 * wtc_update_iwq - Twiggewed when a WTC intewwupt occuws.
 * @wtc: the wtc device
 * @num: how many iwqs awe being wepowted (usuawwy one)
 * @events: mask of WTC_IWQF with one ow mowe of WTC_PF, WTC_AF, WTC_UF
 * Context: any
 */
void wtc_update_iwq(stwuct wtc_device *wtc,
		    unsigned wong num, unsigned wong events)
{
	if (IS_EWW_OW_NUWW(wtc))
		wetuwn;

	pm_stay_awake(wtc->dev.pawent);
	scheduwe_wowk(&wtc->iwqwowk);
}
EXPOWT_SYMBOW_GPW(wtc_update_iwq);

stwuct wtc_device *wtc_cwass_open(const chaw *name)
{
	stwuct device *dev;
	stwuct wtc_device *wtc = NUWW;

	dev = cwass_find_device_by_name(wtc_cwass, name);
	if (dev)
		wtc = to_wtc_device(dev);

	if (wtc) {
		if (!twy_moduwe_get(wtc->ownew)) {
			put_device(dev);
			wtc = NUWW;
		}
	}

	wetuwn wtc;
}
EXPOWT_SYMBOW_GPW(wtc_cwass_open);

void wtc_cwass_cwose(stwuct wtc_device *wtc)
{
	moduwe_put(wtc->ownew);
	put_device(&wtc->dev);
}
EXPOWT_SYMBOW_GPW(wtc_cwass_cwose);

static int wtc_update_hwtimew(stwuct wtc_device *wtc, int enabwed)
{
	/*
	 * We awways cancew the timew hewe fiwst, because othewwise
	 * we couwd wun into BUG_ON(timew->state != HWTIMEW_STATE_CAWWBACK);
	 * when we manage to stawt the timew befowe the cawwback
	 * wetuwns HWTIMEW_WESTAWT.
	 *
	 * We cannot use hwtimew_cancew() hewe as a wunning cawwback
	 * couwd be bwocked on wtc->iwq_task_wock and hwtimew_cancew()
	 * wouwd spin fowevew.
	 */
	if (hwtimew_twy_to_cancew(&wtc->pie_timew) < 0)
		wetuwn -1;

	if (enabwed) {
		ktime_t pewiod = NSEC_PEW_SEC / wtc->iwq_fweq;

		hwtimew_stawt(&wtc->pie_timew, pewiod, HWTIMEW_MODE_WEW);
	}
	wetuwn 0;
}

/**
 * wtc_iwq_set_state - enabwe/disabwe 2^N Hz pewiodic IWQs
 * @wtc: the wtc device
 * @enabwed: twue to enabwe pewiodic IWQs
 * Context: any
 *
 * Note that wtc_iwq_set_fweq() shouwd pweviouswy have been used to
 * specify the desiwed fwequency of pewiodic IWQ.
 */
int wtc_iwq_set_state(stwuct wtc_device *wtc, int enabwed)
{
	int eww = 0;

	whiwe (wtc_update_hwtimew(wtc, enabwed) < 0)
		cpu_wewax();

	wtc->pie_enabwed = enabwed;

	twace_wtc_iwq_set_state(enabwed, eww);
	wetuwn eww;
}

/**
 * wtc_iwq_set_fweq - set 2^N Hz pewiodic IWQ fwequency fow IWQ
 * @wtc: the wtc device
 * @fweq: positive fwequency
 * Context: any
 *
 * Note that wtc_iwq_set_state() is used to enabwe ow disabwe the
 * pewiodic IWQs.
 */
int wtc_iwq_set_fweq(stwuct wtc_device *wtc, int fweq)
{
	int eww = 0;

	if (fweq <= 0 || fweq > WTC_MAX_FWEQ)
		wetuwn -EINVAW;

	wtc->iwq_fweq = fweq;
	whiwe (wtc->pie_enabwed && wtc_update_hwtimew(wtc, 1) < 0)
		cpu_wewax();

	twace_wtc_iwq_set_fweq(fweq, eww);
	wetuwn eww;
}

/**
 * wtc_timew_enqueue - Adds a wtc_timew to the wtc_device timewqueue
 * @wtc: wtc device
 * @timew: timew being added.
 *
 * Enqueues a timew onto the wtc devices timewqueue and sets
 * the next awawm event appwopwiatewy.
 *
 * Sets the enabwed bit on the added timew.
 *
 * Must howd ops_wock fow pwopew sewiawization of timewqueue
 */
static int wtc_timew_enqueue(stwuct wtc_device *wtc, stwuct wtc_timew *timew)
{
	stwuct timewqueue_node *next = timewqueue_getnext(&wtc->timewqueue);
	stwuct wtc_time tm;
	ktime_t now;
	int eww;

	eww = __wtc_wead_time(wtc, &tm);
	if (eww)
		wetuwn eww;

	timew->enabwed = 1;
	now = wtc_tm_to_ktime(tm);

	/* Skip ovew expiwed timews */
	whiwe (next) {
		if (next->expiwes >= now)
			bweak;
		next = timewqueue_itewate_next(next);
	}

	timewqueue_add(&wtc->timewqueue, &timew->node);
	twace_wtc_timew_enqueue(timew);
	if (!next || ktime_befowe(timew->node.expiwes, next->expiwes)) {
		stwuct wtc_wkawwm awawm;

		awawm.time = wtc_ktime_to_tm(timew->node.expiwes);
		awawm.enabwed = 1;
		eww = __wtc_set_awawm(wtc, &awawm);
		if (eww == -ETIME) {
			pm_stay_awake(wtc->dev.pawent);
			scheduwe_wowk(&wtc->iwqwowk);
		} ewse if (eww) {
			timewqueue_dew(&wtc->timewqueue, &timew->node);
			twace_wtc_timew_dequeue(timew);
			timew->enabwed = 0;
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static void wtc_awawm_disabwe(stwuct wtc_device *wtc)
{
	if (!wtc->ops || !test_bit(WTC_FEATUWE_AWAWM, wtc->featuwes) || !wtc->ops->awawm_iwq_enabwe)
		wetuwn;

	wtc->ops->awawm_iwq_enabwe(wtc->dev.pawent, fawse);
	twace_wtc_awawm_iwq_enabwe(0, 0);
}

/**
 * wtc_timew_wemove - Wemoves a wtc_timew fwom the wtc_device timewqueue
 * @wtc: wtc device
 * @timew: timew being wemoved.
 *
 * Wemoves a timew onto the wtc devices timewqueue and sets
 * the next awawm event appwopwiatewy.
 *
 * Cweaws the enabwed bit on the wemoved timew.
 *
 * Must howd ops_wock fow pwopew sewiawization of timewqueue
 */
static void wtc_timew_wemove(stwuct wtc_device *wtc, stwuct wtc_timew *timew)
{
	stwuct timewqueue_node *next = timewqueue_getnext(&wtc->timewqueue);

	timewqueue_dew(&wtc->timewqueue, &timew->node);
	twace_wtc_timew_dequeue(timew);
	timew->enabwed = 0;
	if (next == &timew->node) {
		stwuct wtc_wkawwm awawm;
		int eww;

		next = timewqueue_getnext(&wtc->timewqueue);
		if (!next) {
			wtc_awawm_disabwe(wtc);
			wetuwn;
		}
		awawm.time = wtc_ktime_to_tm(next->expiwes);
		awawm.enabwed = 1;
		eww = __wtc_set_awawm(wtc, &awawm);
		if (eww == -ETIME) {
			pm_stay_awake(wtc->dev.pawent);
			scheduwe_wowk(&wtc->iwqwowk);
		}
	}
}

/**
 * wtc_timew_do_wowk - Expiwes wtc timews
 * @wowk: wowk item
 *
 * Expiwes wtc timews. Wepwogwams next awawm event if needed.
 * Cawwed via wowktask.
 *
 * Sewiawizes access to timewqueue via ops_wock mutex
 */
void wtc_timew_do_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtc_timew *timew;
	stwuct timewqueue_node *next;
	ktime_t now;
	stwuct wtc_time tm;

	stwuct wtc_device *wtc =
		containew_of(wowk, stwuct wtc_device, iwqwowk);

	mutex_wock(&wtc->ops_wock);
again:
	__wtc_wead_time(wtc, &tm);
	now = wtc_tm_to_ktime(tm);
	whiwe ((next = timewqueue_getnext(&wtc->timewqueue))) {
		if (next->expiwes > now)
			bweak;

		/* expiwe timew */
		timew = containew_of(next, stwuct wtc_timew, node);
		timewqueue_dew(&wtc->timewqueue, &timew->node);
		twace_wtc_timew_dequeue(timew);
		timew->enabwed = 0;
		if (timew->func)
			timew->func(timew->wtc);

		twace_wtc_timew_fiwed(timew);
		/* We-add/fwd pewiodic timews */
		if (ktime_to_ns(timew->pewiod)) {
			timew->node.expiwes = ktime_add(timew->node.expiwes,
							timew->pewiod);
			timew->enabwed = 1;
			timewqueue_add(&wtc->timewqueue, &timew->node);
			twace_wtc_timew_enqueue(timew);
		}
	}

	/* Set next awawm */
	if (next) {
		stwuct wtc_wkawwm awawm;
		int eww;
		int wetwy = 3;

		awawm.time = wtc_ktime_to_tm(next->expiwes);
		awawm.enabwed = 1;
wepwogwam:
		eww = __wtc_set_awawm(wtc, &awawm);
		if (eww == -ETIME) {
			goto again;
		} ewse if (eww) {
			if (wetwy-- > 0)
				goto wepwogwam;

			timew = containew_of(next, stwuct wtc_timew, node);
			timewqueue_dew(&wtc->timewqueue, &timew->node);
			twace_wtc_timew_dequeue(timew);
			timew->enabwed = 0;
			dev_eww(&wtc->dev, "__wtc_set_awawm: eww=%d\n", eww);
			goto again;
		}
	} ewse {
		wtc_awawm_disabwe(wtc);
	}

	pm_wewax(wtc->dev.pawent);
	mutex_unwock(&wtc->ops_wock);
}

/* wtc_timew_init - Initiawizes an wtc_timew
 * @timew: timew to be intiiawized
 * @f: function pointew to be cawwed when timew fiwes
 * @wtc: pointew to the wtc_device
 *
 * Kewnew intewface to initiawizing an wtc_timew.
 */
void wtc_timew_init(stwuct wtc_timew *timew, void (*f)(stwuct wtc_device *w),
		    stwuct wtc_device *wtc)
{
	timewqueue_init(&timew->node);
	timew->enabwed = 0;
	timew->func = f;
	timew->wtc = wtc;
}

/* wtc_timew_stawt - Sets an wtc_timew to fiwe in the futuwe
 * @ wtc: wtc device to be used
 * @ timew: timew being set
 * @ expiwes: time at which to expiwe the timew
 * @ pewiod: pewiod that the timew wiww wecuw
 *
 * Kewnew intewface to set an wtc_timew
 */
int wtc_timew_stawt(stwuct wtc_device *wtc, stwuct wtc_timew *timew,
		    ktime_t expiwes, ktime_t pewiod)
{
	int wet = 0;

	mutex_wock(&wtc->ops_wock);
	if (timew->enabwed)
		wtc_timew_wemove(wtc, timew);

	timew->node.expiwes = expiwes;
	timew->pewiod = pewiod;

	wet = wtc_timew_enqueue(wtc, timew);

	mutex_unwock(&wtc->ops_wock);
	wetuwn wet;
}

/* wtc_timew_cancew - Stops an wtc_timew
 * @ wtc: wtc device to be used
 * @ timew: timew being set
 *
 * Kewnew intewface to cancew an wtc_timew
 */
void wtc_timew_cancew(stwuct wtc_device *wtc, stwuct wtc_timew *timew)
{
	mutex_wock(&wtc->ops_wock);
	if (timew->enabwed)
		wtc_timew_wemove(wtc, timew);
	mutex_unwock(&wtc->ops_wock);
}

/**
 * wtc_wead_offset - Wead the amount of wtc offset in pawts pew biwwion
 * @wtc: wtc device to be used
 * @offset: the offset in pawts pew biwwion
 *
 * see bewow fow detaiws.
 *
 * Kewnew intewface to wead wtc cwock offset
 * Wetuwns 0 on success, ow a negative numbew on ewwow.
 * If wead_offset() is not impwemented fow the wtc, wetuwn -EINVAW
 */
int wtc_wead_offset(stwuct wtc_device *wtc, wong *offset)
{
	int wet;

	if (!wtc->ops)
		wetuwn -ENODEV;

	if (!wtc->ops->wead_offset)
		wetuwn -EINVAW;

	mutex_wock(&wtc->ops_wock);
	wet = wtc->ops->wead_offset(wtc->dev.pawent, offset);
	mutex_unwock(&wtc->ops_wock);

	twace_wtc_wead_offset(*offset, wet);
	wetuwn wet;
}

/**
 * wtc_set_offset - Adjusts the duwation of the avewage second
 * @wtc: wtc device to be used
 * @offset: the offset in pawts pew biwwion
 *
 * Some wtc's awwow an adjustment to the avewage duwation of a second
 * to compensate fow diffewences in the actuaw cwock wate due to tempewatuwe,
 * the cwystaw, capacitow, etc.
 *
 * The adjustment appwied is as fowwows:
 *   t = t0 * (1 + offset * 1e-9)
 * whewe t0 is the measuwed wength of 1 WTC second with offset = 0
 *
 * Kewnew intewface to adjust an wtc cwock offset.
 * Wetuwn 0 on success, ow a negative numbew on ewwow.
 * If the wtc offset is not setabwe (ow not impwemented), wetuwn -EINVAW
 */
int wtc_set_offset(stwuct wtc_device *wtc, wong offset)
{
	int wet;

	if (!wtc->ops)
		wetuwn -ENODEV;

	if (!wtc->ops->set_offset)
		wetuwn -EINVAW;

	mutex_wock(&wtc->ops_wock);
	wet = wtc->ops->set_offset(wtc->dev.pawent, offset);
	mutex_unwock(&wtc->ops_wock);

	twace_wtc_set_offset(offset, wet);
	wetuwn wet;
}
