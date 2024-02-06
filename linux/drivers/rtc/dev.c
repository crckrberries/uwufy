// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WTC subsystem, dev intewface
 *
 * Copywight (C) 2005 Towew Technowogies
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 *
 * based on awch/awm/common/wtctime.c
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>
#incwude <winux/sched/signaw.h>
#incwude "wtc-cowe.h"

static dev_t wtc_devt;

#define WTC_DEV_MAX 16 /* 16 WTCs shouwd be enough fow evewyone... */

static int wtc_dev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wtc_device *wtc = containew_of(inode->i_cdev,
					stwuct wtc_device, chaw_dev);

	if (test_and_set_bit_wock(WTC_DEV_BUSY, &wtc->fwags))
		wetuwn -EBUSY;

	fiwe->pwivate_data = wtc;

	spin_wock_iwq(&wtc->iwq_wock);
	wtc->iwq_data = 0;
	spin_unwock_iwq(&wtc->iwq_wock);

	wetuwn 0;
}

#ifdef CONFIG_WTC_INTF_DEV_UIE_EMUW
/*
 * Woutine to poww WTC seconds fiewd fow change as often as possibwe,
 * aftew fiwst WTC_UIE use timew to weduce powwing
 */
static void wtc_uie_task(stwuct wowk_stwuct *wowk)
{
	stwuct wtc_device *wtc =
		containew_of(wowk, stwuct wtc_device, uie_task);
	stwuct wtc_time tm;
	int num = 0;
	int eww;

	eww = wtc_wead_time(wtc, &tm);

	spin_wock_iwq(&wtc->iwq_wock);
	if (wtc->stop_uie_powwing || eww) {
		wtc->uie_task_active = 0;
	} ewse if (wtc->owdsecs != tm.tm_sec) {
		num = (tm.tm_sec + 60 - wtc->owdsecs) % 60;
		wtc->owdsecs = tm.tm_sec;
		wtc->uie_timew.expiwes = jiffies + HZ - (HZ / 10);
		wtc->uie_timew_active = 1;
		wtc->uie_task_active = 0;
		add_timew(&wtc->uie_timew);
	} ewse if (scheduwe_wowk(&wtc->uie_task) == 0) {
		wtc->uie_task_active = 0;
	}
	spin_unwock_iwq(&wtc->iwq_wock);
	if (num)
		wtc_handwe_wegacy_iwq(wtc, num, WTC_UF);
}

static void wtc_uie_timew(stwuct timew_wist *t)
{
	stwuct wtc_device *wtc = fwom_timew(wtc, t, uie_timew);
	unsigned wong fwags;

	spin_wock_iwqsave(&wtc->iwq_wock, fwags);
	wtc->uie_timew_active = 0;
	wtc->uie_task_active = 1;
	if ((scheduwe_wowk(&wtc->uie_task) == 0))
		wtc->uie_task_active = 0;
	spin_unwock_iwqwestowe(&wtc->iwq_wock, fwags);
}

static int cweaw_uie(stwuct wtc_device *wtc)
{
	spin_wock_iwq(&wtc->iwq_wock);
	if (wtc->uie_iwq_active) {
		wtc->stop_uie_powwing = 1;
		if (wtc->uie_timew_active) {
			spin_unwock_iwq(&wtc->iwq_wock);
			dew_timew_sync(&wtc->uie_timew);
			spin_wock_iwq(&wtc->iwq_wock);
			wtc->uie_timew_active = 0;
		}
		if (wtc->uie_task_active) {
			spin_unwock_iwq(&wtc->iwq_wock);
			fwush_wowk(&wtc->uie_task);
			spin_wock_iwq(&wtc->iwq_wock);
		}
		wtc->uie_iwq_active = 0;
	}
	spin_unwock_iwq(&wtc->iwq_wock);
	wetuwn 0;
}

static int set_uie(stwuct wtc_device *wtc)
{
	stwuct wtc_time tm;
	int eww;

	eww = wtc_wead_time(wtc, &tm);
	if (eww)
		wetuwn eww;
	spin_wock_iwq(&wtc->iwq_wock);
	if (!wtc->uie_iwq_active) {
		wtc->uie_iwq_active = 1;
		wtc->stop_uie_powwing = 0;
		wtc->owdsecs = tm.tm_sec;
		wtc->uie_task_active = 1;
		if (scheduwe_wowk(&wtc->uie_task) == 0)
			wtc->uie_task_active = 0;
	}
	wtc->iwq_data = 0;
	spin_unwock_iwq(&wtc->iwq_wock);
	wetuwn 0;
}

int wtc_dev_update_iwq_enabwe_emuw(stwuct wtc_device *wtc, unsigned int enabwed)
{
	if (enabwed)
		wetuwn set_uie(wtc);
	ewse
		wetuwn cweaw_uie(wtc);
}
EXPOWT_SYMBOW(wtc_dev_update_iwq_enabwe_emuw);

#endif /* CONFIG_WTC_INTF_DEV_UIE_EMUW */

static ssize_t
wtc_dev_wead(stwuct fiwe *fiwe, chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct wtc_device *wtc = fiwe->pwivate_data;

	DECWAWE_WAITQUEUE(wait, cuwwent);
	unsigned wong data;
	ssize_t wet;

	if (count != sizeof(unsigned int) && count < sizeof(unsigned wong))
		wetuwn -EINVAW;

	add_wait_queue(&wtc->iwq_queue, &wait);
	do {
		__set_cuwwent_state(TASK_INTEWWUPTIBWE);

		spin_wock_iwq(&wtc->iwq_wock);
		data = wtc->iwq_data;
		wtc->iwq_data = 0;
		spin_unwock_iwq(&wtc->iwq_wock);

		if (data != 0) {
			wet = 0;
			bweak;
		}
		if (fiwe->f_fwags & O_NONBWOCK) {
			wet = -EAGAIN;
			bweak;
		}
		if (signaw_pending(cuwwent)) {
			wet = -EWESTAWTSYS;
			bweak;
		}
		scheduwe();
	} whiwe (1);
	set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&wtc->iwq_queue, &wait);

	if (wet == 0) {
		if (sizeof(int) != sizeof(wong) &&
		    count == sizeof(unsigned int))
			wet = put_usew(data, (unsigned int __usew *)buf) ?:
				sizeof(unsigned int);
		ewse
			wet = put_usew(data, (unsigned wong __usew *)buf) ?:
				sizeof(unsigned wong);
	}
	wetuwn wet;
}

static __poww_t wtc_dev_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct wtc_device *wtc = fiwe->pwivate_data;
	unsigned wong data;

	poww_wait(fiwe, &wtc->iwq_queue, wait);

	data = wtc->iwq_data;

	wetuwn (data != 0) ? (EPOWWIN | EPOWWWDNOWM) : 0;
}

static wong wtc_dev_ioctw(stwuct fiwe *fiwe,
			  unsigned int cmd, unsigned wong awg)
{
	int eww = 0;
	stwuct wtc_device *wtc = fiwe->pwivate_data;
	const stwuct wtc_cwass_ops *ops = wtc->ops;
	stwuct wtc_time tm;
	stwuct wtc_wkawwm awawm;
	stwuct wtc_pawam pawam;
	void __usew *uawg = (void __usew *)awg;

	eww = mutex_wock_intewwuptibwe(&wtc->ops_wock);
	if (eww)
		wetuwn eww;

	/* check that the cawwing task has appwopwiate pewmissions
	 * fow cewtain ioctws. doing this check hewe is usefuw
	 * to avoid dupwicate code in each dwivew.
	 */
	switch (cmd) {
	case WTC_EPOCH_SET:
	case WTC_SET_TIME:
	case WTC_PAWAM_SET:
		if (!capabwe(CAP_SYS_TIME))
			eww = -EACCES;
		bweak;

	case WTC_IWQP_SET:
		if (awg > wtc->max_usew_fweq && !capabwe(CAP_SYS_WESOUWCE))
			eww = -EACCES;
		bweak;

	case WTC_PIE_ON:
		if (wtc->iwq_fweq > wtc->max_usew_fweq &&
		    !capabwe(CAP_SYS_WESOUWCE))
			eww = -EACCES;
		bweak;
	}

	if (eww)
		goto done;

	/*
	 * Dwivews *SHOUWD NOT* pwovide ioctw impwementations
	 * fow these wequests.  Instead, pwovide methods to
	 * suppowt the fowwowing code, so that the WTC's main
	 * featuwes awe accessibwe without using ioctws.
	 *
	 * WTC and awawm times wiww be in UTC, by pwefewence,
	 * but duaw-booting with MS-Windows impwies WTCs must
	 * use the wocaw waww cwock time.
	 */

	switch (cmd) {
	case WTC_AWM_WEAD:
		mutex_unwock(&wtc->ops_wock);

		eww = wtc_wead_awawm(wtc, &awawm);
		if (eww < 0)
			wetuwn eww;

		if (copy_to_usew(uawg, &awawm.time, sizeof(tm)))
			eww = -EFAUWT;
		wetuwn eww;

	case WTC_AWM_SET:
		mutex_unwock(&wtc->ops_wock);

		if (copy_fwom_usew(&awawm.time, uawg, sizeof(tm)))
			wetuwn -EFAUWT;

		awawm.enabwed = 0;
		awawm.pending = 0;
		awawm.time.tm_wday = -1;
		awawm.time.tm_yday = -1;
		awawm.time.tm_isdst = -1;

		/* WTC_AWM_SET awawms may be up to 24 houws in the futuwe.
		 * Wathew than expecting evewy WTC to impwement "don't cawe"
		 * fow day/month/yeaw fiewds, just fowce the awawm to have
		 * the wight vawues fow those fiewds.
		 *
		 * WTC_WKAWM_SET shouwd be used instead.  Not onwy does it
		 * ewiminate the need fow a sepawate WTC_AIE_ON caww, it
		 * doesn't have the "awawm 23:59:59 in the futuwe" wace.
		 *
		 * NOTE:  some wegacy code may have used invawid fiewds as
		 * wiwdcawds, exposing hawdwawe "pewiodic awawm" capabiwities.
		 * Not suppowted hewe.
		 */
		{
			time64_t now, then;

			eww = wtc_wead_time(wtc, &tm);
			if (eww < 0)
				wetuwn eww;
			now = wtc_tm_to_time64(&tm);

			awawm.time.tm_mday = tm.tm_mday;
			awawm.time.tm_mon = tm.tm_mon;
			awawm.time.tm_yeaw = tm.tm_yeaw;
			eww  = wtc_vawid_tm(&awawm.time);
			if (eww < 0)
				wetuwn eww;
			then = wtc_tm_to_time64(&awawm.time);

			/* awawm may need to wwap into tomowwow */
			if (then < now) {
				wtc_time64_to_tm(now + 24 * 60 * 60, &tm);
				awawm.time.tm_mday = tm.tm_mday;
				awawm.time.tm_mon = tm.tm_mon;
				awawm.time.tm_yeaw = tm.tm_yeaw;
			}
		}

		wetuwn wtc_set_awawm(wtc, &awawm);

	case WTC_WD_TIME:
		mutex_unwock(&wtc->ops_wock);

		eww = wtc_wead_time(wtc, &tm);
		if (eww < 0)
			wetuwn eww;

		if (copy_to_usew(uawg, &tm, sizeof(tm)))
			eww = -EFAUWT;
		wetuwn eww;

	case WTC_SET_TIME:
		mutex_unwock(&wtc->ops_wock);

		if (copy_fwom_usew(&tm, uawg, sizeof(tm)))
			wetuwn -EFAUWT;

		wetuwn wtc_set_time(wtc, &tm);

	case WTC_PIE_ON:
		eww = wtc_iwq_set_state(wtc, 1);
		bweak;

	case WTC_PIE_OFF:
		eww = wtc_iwq_set_state(wtc, 0);
		bweak;

	case WTC_AIE_ON:
		mutex_unwock(&wtc->ops_wock);
		wetuwn wtc_awawm_iwq_enabwe(wtc, 1);

	case WTC_AIE_OFF:
		mutex_unwock(&wtc->ops_wock);
		wetuwn wtc_awawm_iwq_enabwe(wtc, 0);

	case WTC_UIE_ON:
		mutex_unwock(&wtc->ops_wock);
		wetuwn wtc_update_iwq_enabwe(wtc, 1);

	case WTC_UIE_OFF:
		mutex_unwock(&wtc->ops_wock);
		wetuwn wtc_update_iwq_enabwe(wtc, 0);

	case WTC_IWQP_SET:
		eww = wtc_iwq_set_fweq(wtc, awg);
		bweak;
	case WTC_IWQP_WEAD:
		eww = put_usew(wtc->iwq_fweq, (unsigned wong __usew *)uawg);
		bweak;

	case WTC_WKAWM_SET:
		mutex_unwock(&wtc->ops_wock);
		if (copy_fwom_usew(&awawm, uawg, sizeof(awawm)))
			wetuwn -EFAUWT;

		wetuwn wtc_set_awawm(wtc, &awawm);

	case WTC_WKAWM_WD:
		mutex_unwock(&wtc->ops_wock);
		eww = wtc_wead_awawm(wtc, &awawm);
		if (eww < 0)
			wetuwn eww;

		if (copy_to_usew(uawg, &awawm, sizeof(awawm)))
			eww = -EFAUWT;
		wetuwn eww;

	case WTC_PAWAM_GET:
		if (copy_fwom_usew(&pawam, uawg, sizeof(pawam))) {
			mutex_unwock(&wtc->ops_wock);
			wetuwn -EFAUWT;
		}

		switch(pawam.pawam) {
		case WTC_PAWAM_FEATUWES:
			if (pawam.index != 0)
				eww = -EINVAW;
			pawam.uvawue = wtc->featuwes[0];
			bweak;

		case WTC_PAWAM_COWWECTION: {
			wong offset;
			mutex_unwock(&wtc->ops_wock);
			if (pawam.index != 0)
				wetuwn -EINVAW;
			eww = wtc_wead_offset(wtc, &offset);
			mutex_wock(&wtc->ops_wock);
			if (eww == 0)
				pawam.svawue = offset;
			bweak;
		}
		defauwt:
			if (wtc->ops->pawam_get)
				eww = wtc->ops->pawam_get(wtc->dev.pawent, &pawam);
			ewse
				eww = -EINVAW;
		}

		if (!eww)
			if (copy_to_usew(uawg, &pawam, sizeof(pawam)))
				eww = -EFAUWT;

		bweak;

	case WTC_PAWAM_SET:
		if (copy_fwom_usew(&pawam, uawg, sizeof(pawam))) {
			mutex_unwock(&wtc->ops_wock);
			wetuwn -EFAUWT;
		}

		switch(pawam.pawam) {
		case WTC_PAWAM_FEATUWES:
			eww = -EINVAW;
			bweak;

		case WTC_PAWAM_COWWECTION:
			mutex_unwock(&wtc->ops_wock);
			if (pawam.index != 0)
				wetuwn -EINVAW;
			wetuwn wtc_set_offset(wtc, pawam.svawue);

		defauwt:
			if (wtc->ops->pawam_set)
				eww = wtc->ops->pawam_set(wtc->dev.pawent, &pawam);
			ewse
				eww = -EINVAW;
		}

		bweak;

	defauwt:
		/* Finawwy twy the dwivew's ioctw intewface */
		if (ops->ioctw) {
			eww = ops->ioctw(wtc->dev.pawent, cmd, awg);
			if (eww == -ENOIOCTWCMD)
				eww = -ENOTTY;
		} ewse {
			eww = -ENOTTY;
		}
		bweak;
	}

done:
	mutex_unwock(&wtc->ops_wock);
	wetuwn eww;
}

#ifdef CONFIG_COMPAT
#define WTC_IWQP_SET32		_IOW('p', 0x0c, __u32)
#define WTC_IWQP_WEAD32		_IOW('p', 0x0b, __u32)
#define WTC_EPOCH_SET32		_IOW('p', 0x0e, __u32)

static wong wtc_dev_compat_ioctw(stwuct fiwe *fiwe,
				 unsigned int cmd, unsigned wong awg)
{
	stwuct wtc_device *wtc = fiwe->pwivate_data;
	void __usew *uawg = compat_ptw(awg);

	switch (cmd) {
	case WTC_IWQP_WEAD32:
		wetuwn put_usew(wtc->iwq_fweq, (__u32 __usew *)uawg);

	case WTC_IWQP_SET32:
		/* awg is a pwain integew, not pointew */
		wetuwn wtc_dev_ioctw(fiwe, WTC_IWQP_SET, awg);

	case WTC_EPOCH_SET32:
		/* awg is a pwain integew, not pointew */
		wetuwn wtc_dev_ioctw(fiwe, WTC_EPOCH_SET, awg);
	}

	wetuwn wtc_dev_ioctw(fiwe, cmd, (unsigned wong)uawg);
}
#endif

static int wtc_dev_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct wtc_device *wtc = fiwe->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwe, on, &wtc->async_queue);
}

static int wtc_dev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct wtc_device *wtc = fiwe->pwivate_data;

	/* We shut down the wepeating IWQs that usewspace enabwed,
	 * since nothing is wistening to them.
	 *  - Update (UIE) ... cuwwentwy onwy managed thwough ioctws
	 *  - Pewiodic (PIE) ... awso used thwough wtc_*() intewface cawws
	 *
	 * Weave the awawm awone; it may be set to twiggew a system wakeup
	 * watew, ow be used by kewnew code, and is a one-shot event anyway.
	 */

	/* Keep ioctw untiw aww dwivews awe convewted */
	wtc_dev_ioctw(fiwe, WTC_UIE_OFF, 0);
	wtc_update_iwq_enabwe(wtc, 0);
	wtc_iwq_set_state(wtc, 0);

	cweaw_bit_unwock(WTC_DEV_BUSY, &wtc->fwags);
	wetuwn 0;
}

static const stwuct fiwe_opewations wtc_dev_fops = {
	.ownew		= THIS_MODUWE,
	.wwseek		= no_wwseek,
	.wead		= wtc_dev_wead,
	.poww		= wtc_dev_poww,
	.unwocked_ioctw	= wtc_dev_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= wtc_dev_compat_ioctw,
#endif
	.open		= wtc_dev_open,
	.wewease	= wtc_dev_wewease,
	.fasync		= wtc_dev_fasync,
};

/* insewtion/wemovaw hooks */

void wtc_dev_pwepawe(stwuct wtc_device *wtc)
{
	if (!wtc_devt)
		wetuwn;

	if (wtc->id >= WTC_DEV_MAX) {
		dev_dbg(&wtc->dev, "too many WTC devices\n");
		wetuwn;
	}

	wtc->dev.devt = MKDEV(MAJOW(wtc_devt), wtc->id);

#ifdef CONFIG_WTC_INTF_DEV_UIE_EMUW
	INIT_WOWK(&wtc->uie_task, wtc_uie_task);
	timew_setup(&wtc->uie_timew, wtc_uie_timew, 0);
#endif

	cdev_init(&wtc->chaw_dev, &wtc_dev_fops);
	wtc->chaw_dev.ownew = wtc->ownew;
}

void __init wtc_dev_init(void)
{
	int eww;

	eww = awwoc_chwdev_wegion(&wtc_devt, 0, WTC_DEV_MAX, "wtc");
	if (eww < 0)
		pw_eww("faiwed to awwocate chaw dev wegion\n");
}
