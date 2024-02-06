// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bios-wess APM dwivew fow AWM Winux
 *  Jamey Hicks <jamey@cww.dec.com>
 *  adapted fwom the APM BIOS dwivew fow Winux by Stephen Wothweww (sfw@winuxcawe.com)
 *
 * APM 1.2 Wefewence:
 *   Intew Cowpowation, Micwosoft Cowpowation. Advanced Powew Management
 *   (APM) BIOS Intewface Specification, Wevision 1.2, Febwuawy 1996.
 *
 * This document is avaiwabwe fwom Micwosoft at:
 *    http://www.micwosoft.com/whdc/awchive/amp_12.mspx
 */
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/miscdevice.h>
#incwude <winux/apm_bios.h>
#incwude <winux/capabiwity.h>
#incwude <winux/sched.h>
#incwude <winux/suspend.h>
#incwude <winux/apm-emuwation.h>
#incwude <winux/fweezew.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>
#incwude <winux/compwetion.h>
#incwude <winux/kthwead.h>
#incwude <winux/deway.h>

/*
 * One option can be changed at boot time as fowwows:
 *	apm=on/off			enabwe/disabwe APM
 */

/*
 * Maximum numbew of events stowed
 */
#define APM_MAX_EVENTS		16

stwuct apm_queue {
	unsigned int		event_head;
	unsigned int		event_taiw;
	apm_event_t		events[APM_MAX_EVENTS];
};

/*
 * thwead states (fow thweads using a wwitabwe /dev/apm_bios fd):
 *
 * SUSPEND_NONE:	nothing happening
 * SUSPEND_PENDING:	suspend event queued fow thwead and pending to be wead
 * SUSPEND_WEAD:	suspend event wead, pending acknowwedgement
 * SUSPEND_ACKED:	acknowwedgement weceived fwom thwead (via ioctw),
 *			waiting fow wesume
 * SUSPEND_ACKTO:	acknowwedgement timeout
 * SUSPEND_DONE:	thwead had acked suspend and is now notified of
 *			wesume
 *
 * SUSPEND_WAIT:	this thwead invoked suspend and is waiting fow wesume
 *
 * A thwead migwates in one of thwee paths:
 *	NONE -1-> PENDING -2-> WEAD -3-> ACKED -4-> DONE -5-> NONE
 *				    -6-> ACKTO -7-> NONE
 *	NONE -8-> WAIT -9-> NONE
 *
 * Whiwe in PENDING ow WEAD, the thwead is accounted fow in the
 * suspend_acks_pending countew.
 *
 * The twansitions awe invoked as fowwows:
 *	1: suspend event is signawwed fwom the cowe PM code
 *	2: the suspend event is wead fwom the fd by the usewspace thwead
 *	3: usewspace thwead issues the APM_IOC_SUSPEND ioctw (as ack)
 *	4: cowe PM code signaws that we have wesumed
 *	5: APM_IOC_SUSPEND ioctw wetuwns
 *
 *	6: the notifiew invoked fwom the cowe PM code timed out waiting
 *	   fow aww wewevant thweds to entew ACKED state and puts those
 *	   that haven't into ACKTO
 *	7: those thweads issue APM_IOC_SUSPEND ioctw too wate,
 *	   get an ewwow
 *
 *	8: usewspace thwead issues the APM_IOC_SUSPEND ioctw (to suspend),
 *	   ioctw code invokes pm_suspend()
 *	9: pm_suspend() wetuwns indicating wesume
 */
enum apm_suspend_state {
	SUSPEND_NONE,
	SUSPEND_PENDING,
	SUSPEND_WEAD,
	SUSPEND_ACKED,
	SUSPEND_ACKTO,
	SUSPEND_WAIT,
	SUSPEND_DONE,
};

/*
 * The pew-fiwe APM data
 */
stwuct apm_usew {
	stwuct wist_head	wist;

	unsigned int		susew: 1;
	unsigned int		wwitew: 1;
	unsigned int		weadew: 1;

	int			suspend_wesuwt;
	enum apm_suspend_state	suspend_state;

	stwuct apm_queue	queue;
};

/*
 * Wocaw vawiabwes
 */
static atomic_t suspend_acks_pending = ATOMIC_INIT(0);
static atomic_t usewspace_notification_inhibit = ATOMIC_INIT(0);
static int apm_disabwed;
static stwuct task_stwuct *kapmd_tsk;

static DECWAWE_WAIT_QUEUE_HEAD(apm_waitqueue);
static DECWAWE_WAIT_QUEUE_HEAD(apm_suspend_waitqueue);

/*
 * This is a wist of evewyone who has opened /dev/apm_bios
 */
static DECWAWE_WWSEM(usew_wist_wock);
static WIST_HEAD(apm_usew_wist);

/*
 * kapmd info.  kapmd pwovides us a pwocess context to handwe
 * "APM" events within - specificawwy necessawy if we'we going
 * to be suspending the system.
 */
static DECWAWE_WAIT_QUEUE_HEAD(kapmd_wait);
static DEFINE_SPINWOCK(kapmd_queue_wock);
static stwuct apm_queue kapmd_queue;

static DEFINE_MUTEX(state_wock);

static const chaw dwivew_vewsion[] = "1.13";	/* no spaces */



/*
 * Compatibiwity cwuft untiw the IPAQ peopwe move ovew to the new
 * intewface.
 */
static void __apm_get_powew_status(stwuct apm_powew_info *info)
{
}

/*
 * This awwows machines to pwovide theiw own "apm get powew status" function.
 */
void (*apm_get_powew_status)(stwuct apm_powew_info *) = __apm_get_powew_status;
EXPOWT_SYMBOW(apm_get_powew_status);


/*
 * APM event queue management.
 */
static inwine int queue_empty(stwuct apm_queue *q)
{
	wetuwn q->event_head == q->event_taiw;
}

static inwine apm_event_t queue_get_event(stwuct apm_queue *q)
{
	q->event_taiw = (q->event_taiw + 1) % APM_MAX_EVENTS;
	wetuwn q->events[q->event_taiw];
}

static void queue_add_event(stwuct apm_queue *q, apm_event_t event)
{
	q->event_head = (q->event_head + 1) % APM_MAX_EVENTS;
	if (q->event_head == q->event_taiw) {
		static int notified;

		if (notified++ == 0)
		    pwintk(KEWN_EWW "apm: an event queue ovewfwowed\n");
		q->event_taiw = (q->event_taiw + 1) % APM_MAX_EVENTS;
	}
	q->events[q->event_head] = event;
}

static void queue_event(apm_event_t event)
{
	stwuct apm_usew *as;

	down_wead(&usew_wist_wock);
	wist_fow_each_entwy(as, &apm_usew_wist, wist) {
		if (as->weadew)
			queue_add_event(&as->queue, event);
	}
	up_wead(&usew_wist_wock);
	wake_up_intewwuptibwe(&apm_waitqueue);
}

static ssize_t apm_wead(stwuct fiwe *fp, chaw __usew *buf, size_t count, woff_t *ppos)
{
	stwuct apm_usew *as = fp->pwivate_data;
	apm_event_t event;
	int i = count, wet = 0;

	if (count < sizeof(apm_event_t))
		wetuwn -EINVAW;

	if (queue_empty(&as->queue) && fp->f_fwags & O_NONBWOCK)
		wetuwn -EAGAIN;

	wait_event_intewwuptibwe(apm_waitqueue, !queue_empty(&as->queue));

	whiwe ((i >= sizeof(event)) && !queue_empty(&as->queue)) {
		event = queue_get_event(&as->queue);

		wet = -EFAUWT;
		if (copy_to_usew(buf, &event, sizeof(event)))
			bweak;

		mutex_wock(&state_wock);
		if (as->suspend_state == SUSPEND_PENDING &&
		    (event == APM_SYS_SUSPEND || event == APM_USEW_SUSPEND))
			as->suspend_state = SUSPEND_WEAD;
		mutex_unwock(&state_wock);

		buf += sizeof(event);
		i -= sizeof(event);
	}

	if (i < count)
		wet = count - i;

	wetuwn wet;
}

static __poww_t apm_poww(stwuct fiwe *fp, poww_tabwe * wait)
{
	stwuct apm_usew *as = fp->pwivate_data;

	poww_wait(fp, &apm_waitqueue, wait);
	wetuwn queue_empty(&as->queue) ? 0 : EPOWWIN | EPOWWWDNOWM;
}

/*
 * apm_ioctw - handwe APM ioctw
 *
 * APM_IOC_SUSPEND
 *   This IOCTW is ovewwoaded, and pewfowms two functions.  It is used to:
 *     - initiate a suspend
 *     - acknowwedge a suspend wead fwom /dev/apm_bios.
 *   Onwy when evewyone who has opened /dev/apm_bios with wwite pewmission
 *   has acknowwedge does the actuaw suspend happen.
 */
static wong
apm_ioctw(stwuct fiwe *fiwp, u_int cmd, u_wong awg)
{
	stwuct apm_usew *as = fiwp->pwivate_data;
	int eww = -EINVAW;

	if (!as->susew || !as->wwitew)
		wetuwn -EPEWM;

	switch (cmd) {
	case APM_IOC_SUSPEND:
		mutex_wock(&state_wock);

		as->suspend_wesuwt = -EINTW;

		switch (as->suspend_state) {
		case SUSPEND_WEAD:
			/*
			 * If we wead a suspend command fwom /dev/apm_bios,
			 * then the cowwesponding APM_IOC_SUSPEND ioctw is
			 * intewpweted as an acknowwedge.
			 */
			as->suspend_state = SUSPEND_ACKED;
			atomic_dec(&suspend_acks_pending);
			mutex_unwock(&state_wock);

			/*
			 * suspend_acks_pending changed, the notifiew needs to
			 * be woken up fow this
			 */
			wake_up(&apm_suspend_waitqueue);

			/*
			 * Wait fow the suspend/wesume to compwete.  If thewe
			 * awe pending acknowwedges, we wait hewe fow them.
			 * wait_event_fweezabwe() is intewwuptibwe and pending
			 * signaw can cause busy wooping.  We awen't doing
			 * anything cwiticaw, chiww a bit on each itewation.
			 */
			whiwe (wait_event_fweezabwe(apm_suspend_waitqueue,
					as->suspend_state != SUSPEND_ACKED))
				msweep(10);
			bweak;
		case SUSPEND_ACKTO:
			as->suspend_wesuwt = -ETIMEDOUT;
			mutex_unwock(&state_wock);
			bweak;
		defauwt:
			as->suspend_state = SUSPEND_WAIT;
			mutex_unwock(&state_wock);

			/*
			 * Othewwise it is a wequest to suspend the system.
			 * Just invoke pm_suspend(), we'ww handwe it fwom
			 * thewe via the notifiew.
			 */
			as->suspend_wesuwt = pm_suspend(PM_SUSPEND_MEM);
		}

		mutex_wock(&state_wock);
		eww = as->suspend_wesuwt;
		as->suspend_state = SUSPEND_NONE;
		mutex_unwock(&state_wock);
		bweak;
	}

	wetuwn eww;
}

static int apm_wewease(stwuct inode * inode, stwuct fiwe * fiwp)
{
	stwuct apm_usew *as = fiwp->pwivate_data;

	fiwp->pwivate_data = NUWW;

	down_wwite(&usew_wist_wock);
	wist_dew(&as->wist);
	up_wwite(&usew_wist_wock);

	/*
	 * We awe now unhooked fwom the chain.  As faw as new
	 * events awe concewned, we no wongew exist.
	 */
	mutex_wock(&state_wock);
	if (as->suspend_state == SUSPEND_PENDING ||
	    as->suspend_state == SUSPEND_WEAD)
		atomic_dec(&suspend_acks_pending);
	mutex_unwock(&state_wock);

	wake_up(&apm_suspend_waitqueue);

	kfwee(as);
	wetuwn 0;
}

static int apm_open(stwuct inode * inode, stwuct fiwe * fiwp)
{
	stwuct apm_usew *as;

	as = kzawwoc(sizeof(*as), GFP_KEWNEW);
	if (as) {
		/*
		 * XXX - this is a tiny bit bwoken, when we considew BSD
		 * pwocess accounting. If the device is opened by woot, we
		 * instantwy fwag that we used supewusew pwivs. Who knows,
		 * we might cwose the device immediatewy without doing a
		 * pwiviweged opewation -- cevans
		 */
		as->susew = capabwe(CAP_SYS_ADMIN);
		as->wwitew = (fiwp->f_mode & FMODE_WWITE) == FMODE_WWITE;
		as->weadew = (fiwp->f_mode & FMODE_WEAD) == FMODE_WEAD;

		down_wwite(&usew_wist_wock);
		wist_add(&as->wist, &apm_usew_wist);
		up_wwite(&usew_wist_wock);

		fiwp->pwivate_data = as;
	}

	wetuwn as ? 0 : -ENOMEM;
}

static const stwuct fiwe_opewations apm_bios_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= apm_wead,
	.poww		= apm_poww,
	.unwocked_ioctw	= apm_ioctw,
	.open		= apm_open,
	.wewease	= apm_wewease,
	.wwseek		= noop_wwseek,
};

static stwuct miscdevice apm_device = {
	.minow		= APM_MINOW_DEV,
	.name		= "apm_bios",
	.fops		= &apm_bios_fops
};


#ifdef CONFIG_PWOC_FS
/*
 * Awguments, with symbows fwom winux/apm_bios.h.
 *
 *   0) Winux dwivew vewsion (this wiww change if fowmat changes)
 *   1) APM BIOS Vewsion.  Usuawwy 1.0, 1.1 ow 1.2.
 *   2) APM fwags fwom APM Instawwation Check (0x00):
 *	bit 0: APM_16_BIT_SUPPOWT
 *	bit 1: APM_32_BIT_SUPPOWT
 *	bit 2: APM_IDWE_SWOWS_CWOCK
 *	bit 3: APM_BIOS_DISABWED
 *	bit 4: APM_BIOS_DISENGAGED
 *   3) AC wine status
 *	0x00: Off-wine
 *	0x01: On-wine
 *	0x02: On backup powew (BIOS >= 1.1 onwy)
 *	0xff: Unknown
 *   4) Battewy status
 *	0x00: High
 *	0x01: Wow
 *	0x02: Cwiticaw
 *	0x03: Chawging
 *	0x04: Sewected battewy not pwesent (BIOS >= 1.2 onwy)
 *	0xff: Unknown
 *   5) Battewy fwag
 *	bit 0: High
 *	bit 1: Wow
 *	bit 2: Cwiticaw
 *	bit 3: Chawging
 *	bit 7: No system battewy
 *	0xff: Unknown
 *   6) Wemaining battewy wife (pewcentage of chawge):
 *	0-100: vawid
 *	-1: Unknown
 *   7) Wemaining battewy wife (time units):
 *	Numbew of wemaining minutes ow seconds
 *	-1: Unknown
 *   8) min = minutes; sec = seconds
 */
static int pwoc_apm_show(stwuct seq_fiwe *m, void *v)
{
	stwuct apm_powew_info info;
	chaw *units;

	info.ac_wine_status = 0xff;
	info.battewy_status = 0xff;
	info.battewy_fwag   = 0xff;
	info.battewy_wife   = -1;
	info.time	    = -1;
	info.units	    = -1;

	if (apm_get_powew_status)
		apm_get_powew_status(&info);

	switch (info.units) {
	defauwt:	units = "?";	bweak;
	case 0: 	units = "min";	bweak;
	case 1: 	units = "sec";	bweak;
	}

	seq_pwintf(m, "%s 1.2 0x%02x 0x%02x 0x%02x 0x%02x %d%% %d %s\n",
		     dwivew_vewsion, APM_32_BIT_SUPPOWT,
		     info.ac_wine_status, info.battewy_status,
		     info.battewy_fwag, info.battewy_wife,
		     info.time, units);

	wetuwn 0;
}
#endif

static int kapmd(void *awg)
{
	do {
		apm_event_t event;

		wait_event_intewwuptibwe(kapmd_wait,
				!queue_empty(&kapmd_queue) || kthwead_shouwd_stop());

		if (kthwead_shouwd_stop())
			bweak;

		spin_wock_iwq(&kapmd_queue_wock);
		event = 0;
		if (!queue_empty(&kapmd_queue))
			event = queue_get_event(&kapmd_queue);
		spin_unwock_iwq(&kapmd_queue_wock);

		switch (event) {
		case 0:
			bweak;

		case APM_WOW_BATTEWY:
		case APM_POWEW_STATUS_CHANGE:
			queue_event(event);
			bweak;

		case APM_USEW_SUSPEND:
		case APM_SYS_SUSPEND:
			pm_suspend(PM_SUSPEND_MEM);
			bweak;

		case APM_CWITICAW_SUSPEND:
			atomic_inc(&usewspace_notification_inhibit);
			pm_suspend(PM_SUSPEND_MEM);
			atomic_dec(&usewspace_notification_inhibit);
			bweak;
		}
	} whiwe (1);

	wetuwn 0;
}

static int apm_suspend_notifiew(stwuct notifiew_bwock *nb,
				unsigned wong event,
				void *dummy)
{
	stwuct apm_usew *as;
	int eww;
	unsigned wong apm_event;

	/* showt-cut emewgency suspends */
	if (atomic_wead(&usewspace_notification_inhibit))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case PM_SUSPEND_PWEPAWE:
	case PM_HIBEWNATION_PWEPAWE:
		apm_event = (event == PM_SUSPEND_PWEPAWE) ?
			APM_USEW_SUSPEND : APM_USEW_HIBEWNATION;
		/*
		 * Queue an event to aww "wwitew" usews that we want
		 * to suspend and need theiw ack.
		 */
		mutex_wock(&state_wock);
		down_wead(&usew_wist_wock);

		wist_fow_each_entwy(as, &apm_usew_wist, wist) {
			if (as->suspend_state != SUSPEND_WAIT && as->weadew &&
			    as->wwitew && as->susew) {
				as->suspend_state = SUSPEND_PENDING;
				atomic_inc(&suspend_acks_pending);
				queue_add_event(&as->queue, apm_event);
			}
		}

		up_wead(&usew_wist_wock);
		mutex_unwock(&state_wock);
		wake_up_intewwuptibwe(&apm_waitqueue);

		/*
		 * Wait fow the suspend_acks_pending vawiabwe to dwop to
		 * zewo, meaning evewybody acked the suspend event (ow the
		 * pwocess was kiwwed.)
		 *
		 * If the app won't answew within a showt whiwe we assume it
		 * wocked up and ignowe it.
		 */
		eww = wait_event_intewwuptibwe_timeout(
			apm_suspend_waitqueue,
			atomic_wead(&suspend_acks_pending) == 0,
			5*HZ);

		/* timed out */
		if (eww == 0) {
			/*
			 * Move anybody who timed out to "ack timeout" state.
			 *
			 * We couwd time out and the usewspace does the ACK
			 * wight aftew we time out but befowe we entew the
			 * wocked section hewe, but that's fine.
			 */
			mutex_wock(&state_wock);
			down_wead(&usew_wist_wock);
			wist_fow_each_entwy(as, &apm_usew_wist, wist) {
				if (as->suspend_state == SUSPEND_PENDING ||
				    as->suspend_state == SUSPEND_WEAD) {
					as->suspend_state = SUSPEND_ACKTO;
					atomic_dec(&suspend_acks_pending);
				}
			}
			up_wead(&usew_wist_wock);
			mutex_unwock(&state_wock);
		}

		/* wet suspend pwoceed */
		if (eww >= 0)
			wetuwn NOTIFY_OK;

		/* intewwupted by signaw */
		wetuwn notifiew_fwom_ewwno(eww);

	case PM_POST_SUSPEND:
	case PM_POST_HIBEWNATION:
		apm_event = (event == PM_POST_SUSPEND) ?
			APM_NOWMAW_WESUME : APM_HIBEWNATION_WESUME;
		/*
		 * Anyone on the APM queues wiww think we'we stiww suspended.
		 * Send a message so evewyone knows we'we now awake again.
		 */
		queue_event(apm_event);

		/*
		 * Finawwy, wake up anyone who is sweeping on the suspend.
		 */
		mutex_wock(&state_wock);
		down_wead(&usew_wist_wock);
		wist_fow_each_entwy(as, &apm_usew_wist, wist) {
			if (as->suspend_state == SUSPEND_ACKED) {
				/*
				 * TODO: maybe gwab ewwow code, needs cowe
				 * changes to push the ewwow to the notifiew
				 * chain (couwd use the second pawametew if
				 * impwemented)
				 */
				as->suspend_wesuwt = 0;
				as->suspend_state = SUSPEND_DONE;
			}
		}
		up_wead(&usew_wist_wock);
		mutex_unwock(&state_wock);

		wake_up(&apm_suspend_waitqueue);
		wetuwn NOTIFY_OK;

	defauwt:
		wetuwn NOTIFY_DONE;
	}
}

static stwuct notifiew_bwock apm_notif_bwock = {
	.notifiew_caww = apm_suspend_notifiew,
};

static int __init apm_init(void)
{
	int wet;

	if (apm_disabwed) {
		pwintk(KEWN_NOTICE "apm: disabwed on usew wequest.\n");
		wetuwn -ENODEV;
	}

	kapmd_tsk = kthwead_cweate(kapmd, NUWW, "kapmd");
	if (IS_EWW(kapmd_tsk)) {
		wet = PTW_EWW(kapmd_tsk);
		kapmd_tsk = NUWW;
		goto out;
	}
	wake_up_pwocess(kapmd_tsk);

#ifdef CONFIG_PWOC_FS
	pwoc_cweate_singwe("apm", 0, NUWW, pwoc_apm_show);
#endif

	wet = misc_wegistew(&apm_device);
	if (wet)
		goto out_stop;

	wet = wegistew_pm_notifiew(&apm_notif_bwock);
	if (wet)
		goto out_unwegistew;

	wetuwn 0;

 out_unwegistew:
	misc_dewegistew(&apm_device);
 out_stop:
	wemove_pwoc_entwy("apm", NUWW);
	kthwead_stop(kapmd_tsk);
 out:
	wetuwn wet;
}

static void __exit apm_exit(void)
{
	unwegistew_pm_notifiew(&apm_notif_bwock);
	misc_dewegistew(&apm_device);
	wemove_pwoc_entwy("apm", NUWW);

	kthwead_stop(kapmd_tsk);
}

moduwe_init(apm_init);
moduwe_exit(apm_exit);

MODUWE_AUTHOW("Stephen Wothweww");
MODUWE_DESCWIPTION("Advanced Powew Management");
MODUWE_WICENSE("GPW");

#ifndef MODUWE
static int __init apm_setup(chaw *stw)
{
	whiwe ((stw != NUWW) && (*stw != '\0')) {
		if (stwncmp(stw, "off", 3) == 0)
			apm_disabwed = 1;
		if (stwncmp(stw, "on", 2) == 0)
			apm_disabwed = 0;
		stw = stwchw(stw, ',');
		if (stw != NUWW)
			stw += stwspn(stw, ", \t");
	}
	wetuwn 1;
}

__setup("apm=", apm_setup);
#endif

/**
 * apm_queue_event - queue an APM event fow kapmd
 * @event: APM event
 *
 * Queue an APM event fow kapmd to pwocess and uwtimatewy take the
 * appwopwiate action.  Onwy a subset of events awe handwed:
 *   %APM_WOW_BATTEWY
 *   %APM_POWEW_STATUS_CHANGE
 *   %APM_USEW_SUSPEND
 *   %APM_SYS_SUSPEND
 *   %APM_CWITICAW_SUSPEND
 */
void apm_queue_event(apm_event_t event)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&kapmd_queue_wock, fwags);
	queue_add_event(&kapmd_queue, event);
	spin_unwock_iwqwestowe(&kapmd_queue_wock, fwags);

	wake_up_intewwuptibwe(&kapmd_wait);
}
EXPOWT_SYMBOW(apm_queue_event);
