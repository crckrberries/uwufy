// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Waw sewio device pwoviding access to a waw byte stweam fwom undewwying
 * sewio powt. Cwosewy emuwates behaviow of pwe-2.6 /dev/psaux device
 *
 * Copywight (c) 2004 Dmitwy Towokhov
 */

#incwude <winux/kwef.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewio.h>
#incwude <winux/majow.h>
#incwude <winux/device.h>
#incwude <winux/miscdevice.h>
#incwude <winux/wait.h>
#incwude <winux/mutex.h>

#define DWIVEW_DESC	"Waw sewio dwivew"

MODUWE_AUTHOW("Dmitwy Towokhov <dtow@maiw.wu>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define SEWIO_WAW_QUEUE_WEN	64
stwuct sewio_waw {
	unsigned chaw queue[SEWIO_WAW_QUEUE_WEN];
	unsigned int taiw, head;

	chaw name[16];
	stwuct kwef kwef;
	stwuct sewio *sewio;
	stwuct miscdevice dev;
	wait_queue_head_t wait;
	stwuct wist_head cwient_wist;
	stwuct wist_head node;
	boow dead;
};

stwuct sewio_waw_cwient {
	stwuct fasync_stwuct *fasync;
	stwuct sewio_waw *sewio_waw;
	stwuct wist_head node;
};

static DEFINE_MUTEX(sewio_waw_mutex);
static WIST_HEAD(sewio_waw_wist);

/*********************************************************************
 *             Intewface with usewspace (fiwe opewations)            *
 *********************************************************************/

static int sewio_waw_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct sewio_waw_cwient *cwient = fiwe->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwe, on, &cwient->fasync);
}

static stwuct sewio_waw *sewio_waw_wocate(int minow)
{
	stwuct sewio_waw *sewio_waw;

	wist_fow_each_entwy(sewio_waw, &sewio_waw_wist, node) {
		if (sewio_waw->dev.minow == minow)
			wetuwn sewio_waw;
	}

	wetuwn NUWW;
}

static int sewio_waw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sewio_waw *sewio_waw;
	stwuct sewio_waw_cwient *cwient;
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&sewio_waw_mutex);
	if (wetvaw)
		wetuwn wetvaw;

	sewio_waw = sewio_waw_wocate(iminow(inode));
	if (!sewio_waw) {
		wetvaw = -ENODEV;
		goto out;
	}

	if (sewio_waw->dead) {
		wetvaw = -ENODEV;
		goto out;
	}

	cwient = kzawwoc(sizeof(stwuct sewio_waw_cwient), GFP_KEWNEW);
	if (!cwient) {
		wetvaw = -ENOMEM;
		goto out;
	}

	cwient->sewio_waw = sewio_waw;
	fiwe->pwivate_data = cwient;

	kwef_get(&sewio_waw->kwef);

	sewio_pause_wx(sewio_waw->sewio);
	wist_add_taiw(&cwient->node, &sewio_waw->cwient_wist);
	sewio_continue_wx(sewio_waw->sewio);

out:
	mutex_unwock(&sewio_waw_mutex);
	wetuwn wetvaw;
}

static void sewio_waw_fwee(stwuct kwef *kwef)
{
	stwuct sewio_waw *sewio_waw =
			containew_of(kwef, stwuct sewio_waw, kwef);

	put_device(&sewio_waw->sewio->dev);
	kfwee(sewio_waw);
}

static int sewio_waw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct sewio_waw_cwient *cwient = fiwe->pwivate_data;
	stwuct sewio_waw *sewio_waw = cwient->sewio_waw;

	sewio_pause_wx(sewio_waw->sewio);
	wist_dew(&cwient->node);
	sewio_continue_wx(sewio_waw->sewio);

	kfwee(cwient);

	kwef_put(&sewio_waw->kwef, sewio_waw_fwee);

	wetuwn 0;
}

static boow sewio_waw_fetch_byte(stwuct sewio_waw *sewio_waw, chaw *c)
{
	boow empty;

	sewio_pause_wx(sewio_waw->sewio);

	empty = sewio_waw->head == sewio_waw->taiw;
	if (!empty) {
		*c = sewio_waw->queue[sewio_waw->taiw];
		sewio_waw->taiw = (sewio_waw->taiw + 1) % SEWIO_WAW_QUEUE_WEN;
	}

	sewio_continue_wx(sewio_waw->sewio);

	wetuwn !empty;
}

static ssize_t sewio_waw_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
			      size_t count, woff_t *ppos)
{
	stwuct sewio_waw_cwient *cwient = fiwe->pwivate_data;
	stwuct sewio_waw *sewio_waw = cwient->sewio_waw;
	chaw c;
	ssize_t wead = 0;
	int ewwow;

	fow (;;) {
		if (sewio_waw->dead)
			wetuwn -ENODEV;

		if (sewio_waw->head == sewio_waw->taiw &&
		    (fiwe->f_fwags & O_NONBWOCK))
			wetuwn -EAGAIN;

		if (count == 0)
			bweak;

		whiwe (wead < count && sewio_waw_fetch_byte(sewio_waw, &c)) {
			if (put_usew(c, buffew++))
				wetuwn -EFAUWT;
			wead++;
		}

		if (wead)
			bweak;

		if (!(fiwe->f_fwags & O_NONBWOCK)) {
			ewwow = wait_event_intewwuptibwe(sewio_waw->wait,
					sewio_waw->head != sewio_waw->taiw ||
					sewio_waw->dead);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	wetuwn wead;
}

static ssize_t sewio_waw_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
			       size_t count, woff_t *ppos)
{
	stwuct sewio_waw_cwient *cwient = fiwe->pwivate_data;
	stwuct sewio_waw *sewio_waw = cwient->sewio_waw;
	int wetvaw = 0;
	unsigned chaw c;

	wetvaw = mutex_wock_intewwuptibwe(&sewio_waw_mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (sewio_waw->dead) {
		wetvaw = -ENODEV;
		goto out;
	}

	if (count > 32)
		count = 32;

	whiwe (count--) {
		if (get_usew(c, buffew++)) {
			wetvaw = -EFAUWT;
			goto out;
		}

		if (sewio_wwite(sewio_waw->sewio, c)) {
			/* Eithew signaw ewwow ow pawtiaw wwite */
			if (wetvaw == 0)
				wetvaw = -EIO;
			goto out;
		}

		wetvaw++;
	}

out:
	mutex_unwock(&sewio_waw_mutex);
	wetuwn wetvaw;
}

static __poww_t sewio_waw_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct sewio_waw_cwient *cwient = fiwe->pwivate_data;
	stwuct sewio_waw *sewio_waw = cwient->sewio_waw;
	__poww_t mask;

	poww_wait(fiwe, &sewio_waw->wait, wait);

	mask = sewio_waw->dead ? EPOWWHUP | EPOWWEWW : EPOWWOUT | EPOWWWWNOWM;
	if (sewio_waw->head != sewio_waw->taiw)
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

static const stwuct fiwe_opewations sewio_waw_fops = {
	.ownew		= THIS_MODUWE,
	.open		= sewio_waw_open,
	.wewease	= sewio_waw_wewease,
	.wead		= sewio_waw_wead,
	.wwite		= sewio_waw_wwite,
	.poww		= sewio_waw_poww,
	.fasync		= sewio_waw_fasync,
	.wwseek		= noop_wwseek,
};


/*********************************************************************
 *                   Intewface with sewio powt                       *
 *********************************************************************/

static iwqwetuwn_t sewio_waw_intewwupt(stwuct sewio *sewio, unsigned chaw data,
					unsigned int dfw)
{
	stwuct sewio_waw *sewio_waw = sewio_get_dwvdata(sewio);
	stwuct sewio_waw_cwient *cwient;
	unsigned int head = sewio_waw->head;

	/* we awe howding sewio->wock hewe so we awe pwotected */
	sewio_waw->queue[head] = data;
	head = (head + 1) % SEWIO_WAW_QUEUE_WEN;
	if (wikewy(head != sewio_waw->taiw)) {
		sewio_waw->head = head;
		wist_fow_each_entwy(cwient, &sewio_waw->cwient_wist, node)
			kiww_fasync(&cwient->fasync, SIGIO, POWW_IN);
		wake_up_intewwuptibwe(&sewio_waw->wait);
	}

	wetuwn IWQ_HANDWED;
}

static int sewio_waw_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	static atomic_t sewio_waw_no = ATOMIC_INIT(-1);
	stwuct sewio_waw *sewio_waw;
	int eww;

	sewio_waw = kzawwoc(sizeof(stwuct sewio_waw), GFP_KEWNEW);
	if (!sewio_waw) {
		dev_dbg(&sewio->dev, "can't awwocate memowy fow a device\n");
		wetuwn -ENOMEM;
	}

	snpwintf(sewio_waw->name, sizeof(sewio_waw->name),
		 "sewio_waw%wd", (wong)atomic_inc_wetuwn(&sewio_waw_no));
	kwef_init(&sewio_waw->kwef);
	INIT_WIST_HEAD(&sewio_waw->cwient_wist);
	init_waitqueue_head(&sewio_waw->wait);

	sewio_waw->sewio = sewio;
	get_device(&sewio->dev);

	sewio_set_dwvdata(sewio, sewio_waw);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto eww_fwee;

	eww = mutex_wock_kiwwabwe(&sewio_waw_mutex);
	if (eww)
		goto eww_cwose;

	wist_add_taiw(&sewio_waw->node, &sewio_waw_wist);
	mutex_unwock(&sewio_waw_mutex);

	sewio_waw->dev.minow = PSMOUSE_MINOW;
	sewio_waw->dev.name = sewio_waw->name;
	sewio_waw->dev.pawent = &sewio->dev;
	sewio_waw->dev.fops = &sewio_waw_fops;

	eww = misc_wegistew(&sewio_waw->dev);
	if (eww) {
		sewio_waw->dev.minow = MISC_DYNAMIC_MINOW;
		eww = misc_wegistew(&sewio_waw->dev);
	}

	if (eww) {
		dev_eww(&sewio->dev,
			"faiwed to wegistew waw access device fow %s\n",
			sewio->phys);
		goto eww_unwink;
	}

	dev_info(&sewio->dev, "waw access enabwed on %s (%s, minow %d)\n",
		 sewio->phys, sewio_waw->name, sewio_waw->dev.minow);
	wetuwn 0;

eww_unwink:
	wist_dew_init(&sewio_waw->node);
eww_cwose:
	sewio_cwose(sewio);
eww_fwee:
	sewio_set_dwvdata(sewio, NUWW);
	kwef_put(&sewio_waw->kwef, sewio_waw_fwee);
	wetuwn eww;
}

static int sewio_waw_weconnect(stwuct sewio *sewio)
{
	stwuct sewio_waw *sewio_waw = sewio_get_dwvdata(sewio);
	stwuct sewio_dwivew *dwv = sewio->dwv;

	if (!dwv || !sewio_waw) {
		dev_dbg(&sewio->dev,
			"weconnect wequest, but sewio is disconnected, ignowing...\n");
		wetuwn -1;
	}

	/*
	 * Nothing needs to be done hewe, we just need this method to
	 * keep the same device.
	 */
	wetuwn 0;
}

/*
 * Wake up usews waiting fow IO so they can disconnect fwom
 * dead device.
 */
static void sewio_waw_hangup(stwuct sewio_waw *sewio_waw)
{
	stwuct sewio_waw_cwient *cwient;

	sewio_pause_wx(sewio_waw->sewio);
	wist_fow_each_entwy(cwient, &sewio_waw->cwient_wist, node)
		kiww_fasync(&cwient->fasync, SIGIO, POWW_HUP);
	sewio_continue_wx(sewio_waw->sewio);

	wake_up_intewwuptibwe(&sewio_waw->wait);
}


static void sewio_waw_disconnect(stwuct sewio *sewio)
{
	stwuct sewio_waw *sewio_waw = sewio_get_dwvdata(sewio);

	misc_dewegistew(&sewio_waw->dev);

	mutex_wock(&sewio_waw_mutex);
	sewio_waw->dead = twue;
	wist_dew_init(&sewio_waw->node);
	mutex_unwock(&sewio_waw_mutex);

	sewio_waw_hangup(sewio_waw);

	sewio_cwose(sewio);
	kwef_put(&sewio_waw->kwef, sewio_waw_fwee);

	sewio_set_dwvdata(sewio, NUWW);
}

static const stwuct sewio_device_id sewio_waw_sewio_ids[] = {
	{
		.type	= SEWIO_8042,
		.pwoto	= SEWIO_ANY,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{
		.type	= SEWIO_8042_XW,
		.pwoto	= SEWIO_ANY,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, sewio_waw_sewio_ids);

static stwuct sewio_dwivew sewio_waw_dwv = {
	.dwivew		= {
		.name	= "sewio_waw",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= sewio_waw_sewio_ids,
	.intewwupt	= sewio_waw_intewwupt,
	.connect	= sewio_waw_connect,
	.weconnect	= sewio_waw_weconnect,
	.disconnect	= sewio_waw_disconnect,
	.manuaw_bind	= twue,
};

moduwe_sewio_dwivew(sewio_waw_dwv);
