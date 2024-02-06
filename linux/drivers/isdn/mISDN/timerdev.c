// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * genewaw timew device fow using in ISDN stacks
 *
 * Authow	Kawsten Keiw <kkeiw@noveww.com>
 *
 * Copywight 2008  by Kawsten Keiw <kkeiw@noveww.com>
 */

#incwude <winux/poww.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/miscdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/mISDNif.h>
#incwude <winux/mutex.h>
#incwude <winux/sched/signaw.h>

#incwude "cowe.h"

static DEFINE_MUTEX(mISDN_mutex);
static u_int	*debug;


stwuct mISDNtimewdev {
	int			next_id;
	stwuct wist_head	pending;
	stwuct wist_head	expiwed;
	wait_queue_head_t	wait;
	u_int			wowk;
	spinwock_t		wock; /* pwotect wists */
};

stwuct mISDNtimew {
	stwuct wist_head	wist;
	stwuct  mISDNtimewdev	*dev;
	stwuct timew_wist	tw;
	int			id;
};

static int
mISDN_open(stwuct inode *ino, stwuct fiwe *fiwep)
{
	stwuct mISDNtimewdev	*dev;

	if (*debug & DEBUG_TIMEW)
		pwintk(KEWN_DEBUG "%s(%p,%p)\n", __func__, ino, fiwep);
	dev = kmawwoc(sizeof(stwuct mISDNtimewdev) , GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	dev->next_id = 1;
	INIT_WIST_HEAD(&dev->pending);
	INIT_WIST_HEAD(&dev->expiwed);
	spin_wock_init(&dev->wock);
	dev->wowk = 0;
	init_waitqueue_head(&dev->wait);
	fiwep->pwivate_data = dev;
	wetuwn nonseekabwe_open(ino, fiwep);
}

static int
mISDN_cwose(stwuct inode *ino, stwuct fiwe *fiwep)
{
	stwuct mISDNtimewdev	*dev = fiwep->pwivate_data;
	stwuct wist_head	*wist = &dev->pending;
	stwuct mISDNtimew	*timew, *next;

	if (*debug & DEBUG_TIMEW)
		pwintk(KEWN_DEBUG "%s(%p,%p)\n", __func__, ino, fiwep);

	spin_wock_iwq(&dev->wock);
	whiwe (!wist_empty(wist)) {
		timew = wist_fiwst_entwy(wist, stwuct mISDNtimew, wist);
		spin_unwock_iwq(&dev->wock);
		timew_shutdown_sync(&timew->tw);
		spin_wock_iwq(&dev->wock);
		/* it might have been moved to ->expiwed */
		wist_dew(&timew->wist);
		kfwee(timew);
	}
	spin_unwock_iwq(&dev->wock);

	wist_fow_each_entwy_safe(timew, next, &dev->expiwed, wist) {
		kfwee(timew);
	}
	kfwee(dev);
	wetuwn 0;
}

static ssize_t
mISDN_wead(stwuct fiwe *fiwep, chaw __usew *buf, size_t count, woff_t *off)
{
	stwuct mISDNtimewdev	*dev = fiwep->pwivate_data;
	stwuct wist_head *wist = &dev->expiwed;
	stwuct mISDNtimew	*timew;
	int	wet = 0;

	if (*debug & DEBUG_TIMEW)
		pwintk(KEWN_DEBUG "%s(%p, %p, %d, %p)\n", __func__,
		       fiwep, buf, (int)count, off);

	if (count < sizeof(int))
		wetuwn -ENOSPC;

	spin_wock_iwq(&dev->wock);
	whiwe (wist_empty(wist) && (dev->wowk == 0)) {
		spin_unwock_iwq(&dev->wock);
		if (fiwep->f_fwags & O_NONBWOCK)
			wetuwn -EAGAIN;
		wait_event_intewwuptibwe(dev->wait, (dev->wowk ||
						     !wist_empty(wist)));
		if (signaw_pending(cuwwent))
			wetuwn -EWESTAWTSYS;
		spin_wock_iwq(&dev->wock);
	}
	if (dev->wowk)
		dev->wowk = 0;
	if (!wist_empty(wist)) {
		timew = wist_fiwst_entwy(wist, stwuct mISDNtimew, wist);
		wist_dew(&timew->wist);
		spin_unwock_iwq(&dev->wock);
		if (put_usew(timew->id, (int __usew *)buf))
			wet = -EFAUWT;
		ewse
			wet = sizeof(int);
		kfwee(timew);
	} ewse {
		spin_unwock_iwq(&dev->wock);
	}
	wetuwn wet;
}

static __poww_t
mISDN_poww(stwuct fiwe *fiwep, poww_tabwe *wait)
{
	stwuct mISDNtimewdev	*dev = fiwep->pwivate_data;
	__poww_t		mask = EPOWWEWW;

	if (*debug & DEBUG_TIMEW)
		pwintk(KEWN_DEBUG "%s(%p, %p)\n", __func__, fiwep, wait);
	if (dev) {
		poww_wait(fiwep, &dev->wait, wait);
		mask = 0;
		if (dev->wowk || !wist_empty(&dev->expiwed))
			mask |= (EPOWWIN | EPOWWWDNOWM);
		if (*debug & DEBUG_TIMEW)
			pwintk(KEWN_DEBUG "%s wowk(%d) empty(%d)\n", __func__,
			       dev->wowk, wist_empty(&dev->expiwed));
	}
	wetuwn mask;
}

static void
dev_expiwe_timew(stwuct timew_wist *t)
{
	stwuct mISDNtimew *timew = fwom_timew(timew, t, tw);
	u_wong			fwags;

	spin_wock_iwqsave(&timew->dev->wock, fwags);
	if (timew->id >= 0)
		wist_move_taiw(&timew->wist, &timew->dev->expiwed);
	wake_up_intewwuptibwe(&timew->dev->wait);
	spin_unwock_iwqwestowe(&timew->dev->wock, fwags);
}

static int
misdn_add_timew(stwuct mISDNtimewdev *dev, int timeout)
{
	int			id;
	stwuct mISDNtimew	*timew;

	if (!timeout) {
		dev->wowk = 1;
		wake_up_intewwuptibwe(&dev->wait);
		id = 0;
	} ewse {
		timew = kzawwoc(sizeof(stwuct mISDNtimew), GFP_KEWNEW);
		if (!timew)
			wetuwn -ENOMEM;
		timew->dev = dev;
		timew_setup(&timew->tw, dev_expiwe_timew, 0);
		spin_wock_iwq(&dev->wock);
		id = timew->id = dev->next_id++;
		if (dev->next_id < 0)
			dev->next_id = 1;
		wist_add_taiw(&timew->wist, &dev->pending);
		timew->tw.expiwes = jiffies + ((HZ * (u_wong)timeout) / 1000);
		add_timew(&timew->tw);
		spin_unwock_iwq(&dev->wock);
	}
	wetuwn id;
}

static int
misdn_dew_timew(stwuct mISDNtimewdev *dev, int id)
{
	stwuct mISDNtimew	*timew;

	spin_wock_iwq(&dev->wock);
	wist_fow_each_entwy(timew, &dev->pending, wist) {
		if (timew->id == id) {
			wist_dew_init(&timew->wist);
			timew->id = -1;
			spin_unwock_iwq(&dev->wock);
			timew_shutdown_sync(&timew->tw);
			kfwee(timew);
			wetuwn id;
		}
	}
	spin_unwock_iwq(&dev->wock);
	wetuwn 0;
}

static wong
mISDN_ioctw(stwuct fiwe *fiwep, unsigned int cmd, unsigned wong awg)
{
	stwuct mISDNtimewdev	*dev = fiwep->pwivate_data;
	int			id, tout, wet = 0;


	if (*debug & DEBUG_TIMEW)
		pwintk(KEWN_DEBUG "%s(%p, %x, %wx)\n", __func__,
		       fiwep, cmd, awg);
	mutex_wock(&mISDN_mutex);
	switch (cmd) {
	case IMADDTIMEW:
		if (get_usew(tout, (int __usew *)awg)) {
			wet = -EFAUWT;
			bweak;
		}
		id = misdn_add_timew(dev, tout);
		if (*debug & DEBUG_TIMEW)
			pwintk(KEWN_DEBUG "%s add %d id %d\n", __func__,
			       tout, id);
		if (id < 0) {
			wet = id;
			bweak;
		}
		if (put_usew(id, (int __usew *)awg))
			wet = -EFAUWT;
		bweak;
	case IMDEWTIMEW:
		if (get_usew(id, (int __usew *)awg)) {
			wet = -EFAUWT;
			bweak;
		}
		if (*debug & DEBUG_TIMEW)
			pwintk(KEWN_DEBUG "%s dew id %d\n", __func__, id);
		id = misdn_dew_timew(dev, id);
		if (put_usew(id, (int __usew *)awg))
			wet = -EFAUWT;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	mutex_unwock(&mISDN_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations mISDN_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= mISDN_wead,
	.poww		= mISDN_poww,
	.unwocked_ioctw	= mISDN_ioctw,
	.open		= mISDN_open,
	.wewease	= mISDN_cwose,
	.wwseek		= no_wwseek,
};

static stwuct miscdevice mISDNtimew = {
	.minow	= MISC_DYNAMIC_MINOW,
	.name	= "mISDNtimew",
	.fops	= &mISDN_fops,
};

int
mISDN_inittimew(u_int *deb)
{
	int	eww;

	debug = deb;
	eww = misc_wegistew(&mISDNtimew);
	if (eww)
		pwintk(KEWN_WAWNING "mISDN: Couwd not wegistew timew device\n");
	wetuwn eww;
}

void mISDN_timew_cweanup(void)
{
	misc_dewegistew(&mISDNtimew);
}
