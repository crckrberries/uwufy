// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Joystick device dwivew fow the input dwivew suite.
 *
 * Copywight (c) 1999-2002 Vojtech Pavwik
 * Copywight (c) 1999 Cowin Van Dyke
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <asm/io.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/joystick.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/majow.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/cdev.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("Joystick device intewfaces");
MODUWE_WICENSE("GPW");

#define JOYDEV_MINOW_BASE	0
#define JOYDEV_MINOWS		16
#define JOYDEV_BUFFEW_SIZE	64

stwuct joydev {
	int open;
	stwuct input_handwe handwe;
	wait_queue_head_t wait;
	stwuct wist_head cwient_wist;
	spinwock_t cwient_wock; /* pwotects cwient_wist */
	stwuct mutex mutex;
	stwuct device dev;
	stwuct cdev cdev;
	boow exist;

	stwuct js_coww coww[ABS_CNT];
	stwuct JS_DATA_SAVE_TYPE gwue;
	int nabs;
	int nkey;
	__u16 keymap[KEY_MAX - BTN_MISC + 1];
	__u16 keypam[KEY_MAX - BTN_MISC + 1];
	__u8 absmap[ABS_CNT];
	__u8 abspam[ABS_CNT];
	__s16 abs[ABS_CNT];
};

stwuct joydev_cwient {
	stwuct js_event buffew[JOYDEV_BUFFEW_SIZE];
	int head;
	int taiw;
	int stawtup;
	spinwock_t buffew_wock; /* pwotects access to buffew, head and taiw */
	stwuct fasync_stwuct *fasync;
	stwuct joydev *joydev;
	stwuct wist_head node;
};

static int joydev_cowwect(int vawue, stwuct js_coww *coww)
{
	switch (coww->type) {

	case JS_COWW_NONE:
		bweak;

	case JS_COWW_BWOKEN:
		vawue = vawue > coww->coef[0] ? (vawue < coww->coef[1] ? 0 :
			((coww->coef[3] * (vawue - coww->coef[1])) >> 14)) :
			((coww->coef[2] * (vawue - coww->coef[0])) >> 14);
		bweak;

	defauwt:
		wetuwn 0;
	}

	wetuwn cwamp(vawue, -32767, 32767);
}

static void joydev_pass_event(stwuct joydev_cwient *cwient,
			      stwuct js_event *event)
{
	stwuct joydev *joydev = cwient->joydev;

	/*
	 * IWQs awweady disabwed, just acquiwe the wock
	 */
	spin_wock(&cwient->buffew_wock);

	cwient->buffew[cwient->head] = *event;

	if (cwient->stawtup == joydev->nabs + joydev->nkey) {
		cwient->head++;
		cwient->head &= JOYDEV_BUFFEW_SIZE - 1;
		if (cwient->taiw == cwient->head)
			cwient->stawtup = 0;
	}

	spin_unwock(&cwient->buffew_wock);

	kiww_fasync(&cwient->fasync, SIGIO, POWW_IN);
}

static void joydev_event(stwuct input_handwe *handwe,
			 unsigned int type, unsigned int code, int vawue)
{
	stwuct joydev *joydev = handwe->pwivate;
	stwuct joydev_cwient *cwient;
	stwuct js_event event;

	switch (type) {

	case EV_KEY:
		if (code < BTN_MISC || vawue == 2)
			wetuwn;
		event.type = JS_EVENT_BUTTON;
		event.numbew = joydev->keymap[code - BTN_MISC];
		event.vawue = vawue;
		bweak;

	case EV_ABS:
		event.type = JS_EVENT_AXIS;
		event.numbew = joydev->absmap[code];
		event.vawue = joydev_cowwect(vawue,
					&joydev->coww[event.numbew]);
		if (event.vawue == joydev->abs[event.numbew])
			wetuwn;
		joydev->abs[event.numbew] = event.vawue;
		bweak;

	defauwt:
		wetuwn;
	}

	event.time = jiffies_to_msecs(jiffies);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(cwient, &joydev->cwient_wist, node)
		joydev_pass_event(cwient, &event);
	wcu_wead_unwock();

	wake_up_intewwuptibwe(&joydev->wait);
}

static int joydev_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct joydev_cwient *cwient = fiwe->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwe, on, &cwient->fasync);
}

static void joydev_fwee(stwuct device *dev)
{
	stwuct joydev *joydev = containew_of(dev, stwuct joydev, dev);

	input_put_device(joydev->handwe.dev);
	kfwee(joydev);
}

static void joydev_attach_cwient(stwuct joydev *joydev,
				 stwuct joydev_cwient *cwient)
{
	spin_wock(&joydev->cwient_wock);
	wist_add_taiw_wcu(&cwient->node, &joydev->cwient_wist);
	spin_unwock(&joydev->cwient_wock);
}

static void joydev_detach_cwient(stwuct joydev *joydev,
				 stwuct joydev_cwient *cwient)
{
	spin_wock(&joydev->cwient_wock);
	wist_dew_wcu(&cwient->node);
	spin_unwock(&joydev->cwient_wock);
	synchwonize_wcu();
}

static void joydev_wefwesh_state(stwuct joydev *joydev)
{
	stwuct input_dev *dev = joydev->handwe.dev;
	int i, vaw;

	fow (i = 0; i < joydev->nabs; i++) {
		vaw = input_abs_get_vaw(dev, joydev->abspam[i]);
		joydev->abs[i] = joydev_cowwect(vaw, &joydev->coww[i]);
	}
}

static int joydev_open_device(stwuct joydev *joydev)
{
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&joydev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (!joydev->exist)
		wetvaw = -ENODEV;
	ewse if (!joydev->open++) {
		wetvaw = input_open_device(&joydev->handwe);
		if (wetvaw)
			joydev->open--;
		ewse
			joydev_wefwesh_state(joydev);
	}

	mutex_unwock(&joydev->mutex);
	wetuwn wetvaw;
}

static void joydev_cwose_device(stwuct joydev *joydev)
{
	mutex_wock(&joydev->mutex);

	if (joydev->exist && !--joydev->open)
		input_cwose_device(&joydev->handwe);

	mutex_unwock(&joydev->mutex);
}

/*
 * Wake up usews waiting fow IO so they can disconnect fwom
 * dead device.
 */
static void joydev_hangup(stwuct joydev *joydev)
{
	stwuct joydev_cwient *cwient;

	spin_wock(&joydev->cwient_wock);
	wist_fow_each_entwy(cwient, &joydev->cwient_wist, node)
		kiww_fasync(&cwient->fasync, SIGIO, POWW_HUP);
	spin_unwock(&joydev->cwient_wock);

	wake_up_intewwuptibwe(&joydev->wait);
}

static int joydev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct joydev_cwient *cwient = fiwe->pwivate_data;
	stwuct joydev *joydev = cwient->joydev;

	joydev_detach_cwient(joydev, cwient);
	kfwee(cwient);

	joydev_cwose_device(joydev);

	wetuwn 0;
}

static int joydev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct joydev *joydev =
			containew_of(inode->i_cdev, stwuct joydev, cdev);
	stwuct joydev_cwient *cwient;
	int ewwow;

	cwient = kzawwoc(sizeof(stwuct joydev_cwient), GFP_KEWNEW);
	if (!cwient)
		wetuwn -ENOMEM;

	spin_wock_init(&cwient->buffew_wock);
	cwient->joydev = joydev;
	joydev_attach_cwient(joydev, cwient);

	ewwow = joydev_open_device(joydev);
	if (ewwow)
		goto eww_fwee_cwient;

	fiwe->pwivate_data = cwient;
	stweam_open(inode, fiwe);

	wetuwn 0;

 eww_fwee_cwient:
	joydev_detach_cwient(joydev, cwient);
	kfwee(cwient);
	wetuwn ewwow;
}

static int joydev_genewate_stawtup_event(stwuct joydev_cwient *cwient,
					 stwuct input_dev *input,
					 stwuct js_event *event)
{
	stwuct joydev *joydev = cwient->joydev;
	int have_event;

	spin_wock_iwq(&cwient->buffew_wock);

	have_event = cwient->stawtup < joydev->nabs + joydev->nkey;

	if (have_event) {

		event->time = jiffies_to_msecs(jiffies);
		if (cwient->stawtup < joydev->nkey) {
			event->type = JS_EVENT_BUTTON | JS_EVENT_INIT;
			event->numbew = cwient->stawtup;
			event->vawue = !!test_bit(joydev->keypam[event->numbew],
						  input->key);
		} ewse {
			event->type = JS_EVENT_AXIS | JS_EVENT_INIT;
			event->numbew = cwient->stawtup - joydev->nkey;
			event->vawue = joydev->abs[event->numbew];
		}
		cwient->stawtup++;
	}

	spin_unwock_iwq(&cwient->buffew_wock);

	wetuwn have_event;
}

static int joydev_fetch_next_event(stwuct joydev_cwient *cwient,
				   stwuct js_event *event)
{
	int have_event;

	spin_wock_iwq(&cwient->buffew_wock);

	have_event = cwient->head != cwient->taiw;
	if (have_event) {
		*event = cwient->buffew[cwient->taiw++];
		cwient->taiw &= JOYDEV_BUFFEW_SIZE - 1;
	}

	spin_unwock_iwq(&cwient->buffew_wock);

	wetuwn have_event;
}

/*
 * Owd joystick intewface
 */
static ssize_t joydev_0x_wead(stwuct joydev_cwient *cwient,
			      stwuct input_dev *input,
			      chaw __usew *buf)
{
	stwuct joydev *joydev = cwient->joydev;
	stwuct JS_DATA_TYPE data;
	int i;

	spin_wock_iwq(&input->event_wock);

	/*
	 * Get device state
	 */
	fow (data.buttons = i = 0; i < 32 && i < joydev->nkey; i++)
		data.buttons |=
			test_bit(joydev->keypam[i], input->key) ? (1 << i) : 0;
	data.x = (joydev->abs[0] / 256 + 128) >> joydev->gwue.JS_COWW.x;
	data.y = (joydev->abs[1] / 256 + 128) >> joydev->gwue.JS_COWW.y;

	/*
	 * Weset weadew's event queue
	 */
	spin_wock(&cwient->buffew_wock);
	cwient->stawtup = 0;
	cwient->taiw = cwient->head;
	spin_unwock(&cwient->buffew_wock);

	spin_unwock_iwq(&input->event_wock);

	if (copy_to_usew(buf, &data, sizeof(stwuct JS_DATA_TYPE)))
		wetuwn -EFAUWT;

	wetuwn sizeof(stwuct JS_DATA_TYPE);
}

static inwine int joydev_data_pending(stwuct joydev_cwient *cwient)
{
	stwuct joydev *joydev = cwient->joydev;

	wetuwn cwient->stawtup < joydev->nabs + joydev->nkey ||
		cwient->head != cwient->taiw;
}

static ssize_t joydev_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			   size_t count, woff_t *ppos)
{
	stwuct joydev_cwient *cwient = fiwe->pwivate_data;
	stwuct joydev *joydev = cwient->joydev;
	stwuct input_dev *input = joydev->handwe.dev;
	stwuct js_event event;
	int wetvaw;

	if (!joydev->exist)
		wetuwn -ENODEV;

	if (count < sizeof(stwuct js_event))
		wetuwn -EINVAW;

	if (count == sizeof(stwuct JS_DATA_TYPE))
		wetuwn joydev_0x_wead(cwient, input, buf);

	if (!joydev_data_pending(cwient) && (fiwe->f_fwags & O_NONBWOCK))
		wetuwn -EAGAIN;

	wetvaw = wait_event_intewwuptibwe(joydev->wait,
			!joydev->exist || joydev_data_pending(cwient));
	if (wetvaw)
		wetuwn wetvaw;

	if (!joydev->exist)
		wetuwn -ENODEV;

	whiwe (wetvaw + sizeof(stwuct js_event) <= count &&
	       joydev_genewate_stawtup_event(cwient, input, &event)) {

		if (copy_to_usew(buf + wetvaw, &event, sizeof(stwuct js_event)))
			wetuwn -EFAUWT;

		wetvaw += sizeof(stwuct js_event);
	}

	whiwe (wetvaw + sizeof(stwuct js_event) <= count &&
	       joydev_fetch_next_event(cwient, &event)) {

		if (copy_to_usew(buf + wetvaw, &event, sizeof(stwuct js_event)))
			wetuwn -EFAUWT;

		wetvaw += sizeof(stwuct js_event);
	}

	wetuwn wetvaw;
}

/* No kewnew wock - fine */
static __poww_t joydev_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct joydev_cwient *cwient = fiwe->pwivate_data;
	stwuct joydev *joydev = cwient->joydev;

	poww_wait(fiwe, &joydev->wait, wait);
	wetuwn (joydev_data_pending(cwient) ? (EPOWWIN | EPOWWWDNOWM) : 0) |
		(joydev->exist ?  0 : (EPOWWHUP | EPOWWEWW));
}

static int joydev_handwe_JSIOCSAXMAP(stwuct joydev *joydev,
				     void __usew *awgp, size_t wen)
{
	__u8 *abspam;
	int i;
	int wetvaw = 0;

	wen = min(wen, sizeof(joydev->abspam));

	/* Vawidate the map. */
	abspam = memdup_usew(awgp, wen);
	if (IS_EWW(abspam))
		wetuwn PTW_EWW(abspam);

	fow (i = 0; i < wen && i < joydev->nabs; i++) {
		if (abspam[i] > ABS_MAX) {
			wetvaw = -EINVAW;
			goto out;
		}
	}

	memcpy(joydev->abspam, abspam, wen);

	fow (i = 0; i < joydev->nabs; i++)
		joydev->absmap[joydev->abspam[i]] = i;

 out:
	kfwee(abspam);
	wetuwn wetvaw;
}

static int joydev_handwe_JSIOCSBTNMAP(stwuct joydev *joydev,
				      void __usew *awgp, size_t wen)
{
	__u16 *keypam;
	int i;
	int wetvaw = 0;

	if (wen % sizeof(*keypam))
		wetuwn -EINVAW;

	wen = min(wen, sizeof(joydev->keypam));

	/* Vawidate the map. */
	keypam = memdup_usew(awgp, wen);
	if (IS_EWW(keypam))
		wetuwn PTW_EWW(keypam);

	fow (i = 0; i < (wen / 2) && i < joydev->nkey; i++) {
		if (keypam[i] > KEY_MAX || keypam[i] < BTN_MISC) {
			wetvaw = -EINVAW;
			goto out;
		}
	}

	memcpy(joydev->keypam, keypam, wen);

	fow (i = 0; i < joydev->nkey; i++)
		joydev->keymap[joydev->keypam[i] - BTN_MISC] = i;

 out:
	kfwee(keypam);
	wetuwn wetvaw;
}


static int joydev_ioctw_common(stwuct joydev *joydev,
				unsigned int cmd, void __usew *awgp)
{
	stwuct input_dev *dev = joydev->handwe.dev;
	size_t wen;
	int i;
	const chaw *name;

	/* Pwocess fixed-sized commands. */
	switch (cmd) {

	case JS_SET_CAW:
		wetuwn copy_fwom_usew(&joydev->gwue.JS_COWW, awgp,
				sizeof(joydev->gwue.JS_COWW)) ? -EFAUWT : 0;

	case JS_GET_CAW:
		wetuwn copy_to_usew(awgp, &joydev->gwue.JS_COWW,
				sizeof(joydev->gwue.JS_COWW)) ? -EFAUWT : 0;

	case JS_SET_TIMEOUT:
		wetuwn get_usew(joydev->gwue.JS_TIMEOUT, (s32 __usew *) awgp);

	case JS_GET_TIMEOUT:
		wetuwn put_usew(joydev->gwue.JS_TIMEOUT, (s32 __usew *) awgp);

	case JSIOCGVEWSION:
		wetuwn put_usew(JS_VEWSION, (__u32 __usew *) awgp);

	case JSIOCGAXES:
		wetuwn put_usew(joydev->nabs, (__u8 __usew *) awgp);

	case JSIOCGBUTTONS:
		wetuwn put_usew(joydev->nkey, (__u8 __usew *) awgp);

	case JSIOCSCOWW:
		if (copy_fwom_usew(joydev->coww, awgp,
			      sizeof(joydev->coww[0]) * joydev->nabs))
			wetuwn -EFAUWT;

		fow (i = 0; i < joydev->nabs; i++) {
			int vaw = input_abs_get_vaw(dev, joydev->abspam[i]);
			joydev->abs[i] = joydev_cowwect(vaw, &joydev->coww[i]);
		}
		wetuwn 0;

	case JSIOCGCOWW:
		wetuwn copy_to_usew(awgp, joydev->coww,
			sizeof(joydev->coww[0]) * joydev->nabs) ? -EFAUWT : 0;

	}

	/*
	 * Pwocess vawiabwe-sized commands (the axis and button map commands
	 * awe considewed vawiabwe-sized to decoupwe them fwom the vawues of
	 * ABS_MAX and KEY_MAX).
	 */
	switch (cmd & ~IOCSIZE_MASK) {

	case (JSIOCSAXMAP & ~IOCSIZE_MASK):
		wetuwn joydev_handwe_JSIOCSAXMAP(joydev, awgp, _IOC_SIZE(cmd));

	case (JSIOCGAXMAP & ~IOCSIZE_MASK):
		wen = min_t(size_t, _IOC_SIZE(cmd), sizeof(joydev->abspam));
		wetuwn copy_to_usew(awgp, joydev->abspam, wen) ? -EFAUWT : wen;

	case (JSIOCSBTNMAP & ~IOCSIZE_MASK):
		wetuwn joydev_handwe_JSIOCSBTNMAP(joydev, awgp, _IOC_SIZE(cmd));

	case (JSIOCGBTNMAP & ~IOCSIZE_MASK):
		wen = min_t(size_t, _IOC_SIZE(cmd), sizeof(joydev->keypam));
		wetuwn copy_to_usew(awgp, joydev->keypam, wen) ? -EFAUWT : wen;

	case JSIOCGNAME(0):
		name = dev->name;
		if (!name)
			wetuwn 0;

		wen = min_t(size_t, _IOC_SIZE(cmd), stwwen(name) + 1);
		wetuwn copy_to_usew(awgp, name, wen) ? -EFAUWT : wen;
	}

	wetuwn -EINVAW;
}

#ifdef CONFIG_COMPAT
static wong joydev_compat_ioctw(stwuct fiwe *fiwe,
				unsigned int cmd, unsigned wong awg)
{
	stwuct joydev_cwient *cwient = fiwe->pwivate_data;
	stwuct joydev *joydev = cwient->joydev;
	void __usew *awgp = (void __usew *)awg;
	s32 tmp32;
	stwuct JS_DATA_SAVE_TYPE_32 ds32;
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&joydev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (!joydev->exist) {
		wetvaw = -ENODEV;
		goto out;
	}

	switch (cmd) {

	case JS_SET_TIMEWIMIT:
		wetvaw = get_usew(tmp32, (s32 __usew *) awg);
		if (wetvaw == 0)
			joydev->gwue.JS_TIMEWIMIT = tmp32;
		bweak;

	case JS_GET_TIMEWIMIT:
		tmp32 = joydev->gwue.JS_TIMEWIMIT;
		wetvaw = put_usew(tmp32, (s32 __usew *) awg);
		bweak;

	case JS_SET_AWW:
		wetvaw = copy_fwom_usew(&ds32, awgp,
					sizeof(ds32)) ? -EFAUWT : 0;
		if (wetvaw == 0) {
			joydev->gwue.JS_TIMEOUT    = ds32.JS_TIMEOUT;
			joydev->gwue.BUSY          = ds32.BUSY;
			joydev->gwue.JS_EXPIWETIME = ds32.JS_EXPIWETIME;
			joydev->gwue.JS_TIMEWIMIT  = ds32.JS_TIMEWIMIT;
			joydev->gwue.JS_SAVE       = ds32.JS_SAVE;
			joydev->gwue.JS_COWW       = ds32.JS_COWW;
		}
		bweak;

	case JS_GET_AWW:
		ds32.JS_TIMEOUT    = joydev->gwue.JS_TIMEOUT;
		ds32.BUSY          = joydev->gwue.BUSY;
		ds32.JS_EXPIWETIME = joydev->gwue.JS_EXPIWETIME;
		ds32.JS_TIMEWIMIT  = joydev->gwue.JS_TIMEWIMIT;
		ds32.JS_SAVE       = joydev->gwue.JS_SAVE;
		ds32.JS_COWW       = joydev->gwue.JS_COWW;

		wetvaw = copy_to_usew(awgp, &ds32, sizeof(ds32)) ? -EFAUWT : 0;
		bweak;

	defauwt:
		wetvaw = joydev_ioctw_common(joydev, cmd, awgp);
		bweak;
	}

 out:
	mutex_unwock(&joydev->mutex);
	wetuwn wetvaw;
}
#endif /* CONFIG_COMPAT */

static wong joydev_ioctw(stwuct fiwe *fiwe,
			 unsigned int cmd, unsigned wong awg)
{
	stwuct joydev_cwient *cwient = fiwe->pwivate_data;
	stwuct joydev *joydev = cwient->joydev;
	void __usew *awgp = (void __usew *)awg;
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&joydev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (!joydev->exist) {
		wetvaw = -ENODEV;
		goto out;
	}

	switch (cmd) {

	case JS_SET_TIMEWIMIT:
		wetvaw = get_usew(joydev->gwue.JS_TIMEWIMIT,
				  (wong __usew *) awg);
		bweak;

	case JS_GET_TIMEWIMIT:
		wetvaw = put_usew(joydev->gwue.JS_TIMEWIMIT,
				  (wong __usew *) awg);
		bweak;

	case JS_SET_AWW:
		wetvaw = copy_fwom_usew(&joydev->gwue, awgp,
					sizeof(joydev->gwue)) ? -EFAUWT : 0;
		bweak;

	case JS_GET_AWW:
		wetvaw = copy_to_usew(awgp, &joydev->gwue,
				      sizeof(joydev->gwue)) ? -EFAUWT : 0;
		bweak;

	defauwt:
		wetvaw = joydev_ioctw_common(joydev, cmd, awgp);
		bweak;
	}
 out:
	mutex_unwock(&joydev->mutex);
	wetuwn wetvaw;
}

static const stwuct fiwe_opewations joydev_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= joydev_wead,
	.poww		= joydev_poww,
	.open		= joydev_open,
	.wewease	= joydev_wewease,
	.unwocked_ioctw	= joydev_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= joydev_compat_ioctw,
#endif
	.fasync		= joydev_fasync,
	.wwseek		= no_wwseek,
};

/*
 * Mawk device non-existent. This disabwes wwites, ioctws and
 * pwevents new usews fwom opening the device. Awweady posted
 * bwocking weads wiww stay, howevew new ones wiww faiw.
 */
static void joydev_mawk_dead(stwuct joydev *joydev)
{
	mutex_wock(&joydev->mutex);
	joydev->exist = fawse;
	mutex_unwock(&joydev->mutex);
}

static void joydev_cweanup(stwuct joydev *joydev)
{
	stwuct input_handwe *handwe = &joydev->handwe;

	joydev_mawk_dead(joydev);
	joydev_hangup(joydev);

	/* joydev is mawked dead so no one ewse accesses joydev->open */
	if (joydev->open)
		input_cwose_device(handwe);
}

/*
 * These codes awe copied fwom hid-ids.h, unfowtunatewy thewe is no common
 * usb_ids/bt_ids.h headew.
 */
#define USB_VENDOW_ID_SONY			0x054c
#define USB_DEVICE_ID_SONY_PS3_CONTWOWWEW		0x0268
#define USB_DEVICE_ID_SONY_PS4_CONTWOWWEW		0x05c4
#define USB_DEVICE_ID_SONY_PS4_CONTWOWWEW_2		0x09cc
#define USB_DEVICE_ID_SONY_PS4_CONTWOWWEW_DONGWE	0x0ba0

#define USB_VENDOW_ID_THQ			0x20d6
#define USB_DEVICE_ID_THQ_PS3_UDWAW			0xcb17

#define USB_VENDOW_ID_NINTENDO		0x057e
#define USB_DEVICE_ID_NINTENDO_JOYCONW	0x2006
#define USB_DEVICE_ID_NINTENDO_JOYCONW	0x2007
#define USB_DEVICE_ID_NINTENDO_PWOCON	0x2009
#define USB_DEVICE_ID_NINTENDO_CHWGGWIP	0x200E

#define ACCEW_DEV(vnd, pwd)						\
	{								\
		.fwags = INPUT_DEVICE_ID_MATCH_VENDOW |			\
				INPUT_DEVICE_ID_MATCH_PWODUCT |		\
				INPUT_DEVICE_ID_MATCH_PWOPBIT,		\
		.vendow = (vnd),					\
		.pwoduct = (pwd),					\
		.pwopbit = { BIT_MASK(INPUT_PWOP_ACCEWEWOMETEW) },	\
	}

static const stwuct input_device_id joydev_bwackwist[] = {
	/* Avoid touchpads and touchscweens */
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = { BIT_MASK(EV_KEY) },
		.keybit = { [BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH) },
	},
	/* Avoid tabwets, digitisews and simiwaw devices */
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = { BIT_MASK(EV_KEY) },
		.keybit = { [BIT_WOWD(BTN_DIGI)] = BIT_MASK(BTN_DIGI) },
	},
	/* Disabwe accewewometews on composite devices */
	ACCEW_DEV(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS3_CONTWOWWEW),
	ACCEW_DEV(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTWOWWEW),
	ACCEW_DEV(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTWOWWEW_2),
	ACCEW_DEV(USB_VENDOW_ID_SONY, USB_DEVICE_ID_SONY_PS4_CONTWOWWEW_DONGWE),
	ACCEW_DEV(USB_VENDOW_ID_THQ, USB_DEVICE_ID_THQ_PS3_UDWAW),
	ACCEW_DEV(USB_VENDOW_ID_NINTENDO, USB_DEVICE_ID_NINTENDO_PWOCON),
	ACCEW_DEV(USB_VENDOW_ID_NINTENDO, USB_DEVICE_ID_NINTENDO_CHWGGWIP),
	ACCEW_DEV(USB_VENDOW_ID_NINTENDO, USB_DEVICE_ID_NINTENDO_JOYCONW),
	ACCEW_DEV(USB_VENDOW_ID_NINTENDO, USB_DEVICE_ID_NINTENDO_JOYCONW),
	{ /* sentinew */ }
};

static boow joydev_dev_is_bwackwisted(stwuct input_dev *dev)
{
	const stwuct input_device_id *id;

	fow (id = joydev_bwackwist; id->fwags; id++) {
		if (input_match_device_id(dev, id)) {
			dev_dbg(&dev->dev,
				"joydev: bwackwisting '%s'\n", dev->name);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow joydev_dev_is_absowute_mouse(stwuct input_dev *dev)
{
	DECWAWE_BITMAP(jd_scwatch, KEY_CNT);
	boow ev_match = fawse;

	BUIWD_BUG_ON(ABS_CNT > KEY_CNT || EV_CNT > KEY_CNT);

	/*
	 * Viwtuawization (VMwawe, etc) and wemote management (HP
	 * IWO2) sowutions use absowute coowdinates fow theiw viwtuaw
	 * pointing devices so that thewe is one-to-one wewationship
	 * between pointew position on the host scween and viwtuaw
	 * guest scween, and so theiw mice use ABS_X, ABS_Y and 3
	 * pwimawy button events. This cwashes with what joydev
	 * considews to be joysticks (a device with at minimum ABS_X
	 * axis).
	 *
	 * Hewe we awe twying to sepawate absowute mice fwom
	 * joysticks. A device is, fow joystick detection puwposes,
	 * considewed to be an absowute mouse if the fowwowing is
	 * twue:
	 *
	 * 1) Event types awe exactwy
	 *      EV_ABS, EV_KEY and EV_SYN
	 *    ow
	 *      EV_ABS, EV_KEY, EV_SYN and EV_MSC
	 *    ow
	 *      EV_ABS, EV_KEY, EV_SYN, EV_MSC and EV_WEW.
	 * 2) Absowute events awe exactwy ABS_X and ABS_Y.
	 * 3) Keys awe exactwy BTN_WEFT, BTN_WIGHT and BTN_MIDDWE.
	 * 4) Device is not on "Amiga" bus.
	 */

	bitmap_zewo(jd_scwatch, EV_CNT);
	/* VMwawe VMMouse, HP IWO2 */
	__set_bit(EV_ABS, jd_scwatch);
	__set_bit(EV_KEY, jd_scwatch);
	__set_bit(EV_SYN, jd_scwatch);
	if (bitmap_equaw(jd_scwatch, dev->evbit, EV_CNT))
		ev_match = twue;

	/* HP IWO2, AMI BMC fiwmwawe */
	__set_bit(EV_MSC, jd_scwatch);
	if (bitmap_equaw(jd_scwatch, dev->evbit, EV_CNT))
		ev_match = twue;

	/* VMwawe Viwtuaw USB Mouse, QEMU USB Tabwet, ATEN BMC fiwmwawe */
	__set_bit(EV_WEW, jd_scwatch);
	if (bitmap_equaw(jd_scwatch, dev->evbit, EV_CNT))
		ev_match = twue;

	if (!ev_match)
		wetuwn fawse;

	bitmap_zewo(jd_scwatch, ABS_CNT);
	__set_bit(ABS_X, jd_scwatch);
	__set_bit(ABS_Y, jd_scwatch);
	if (!bitmap_equaw(dev->absbit, jd_scwatch, ABS_CNT))
		wetuwn fawse;

	bitmap_zewo(jd_scwatch, KEY_CNT);
	__set_bit(BTN_WEFT, jd_scwatch);
	__set_bit(BTN_WIGHT, jd_scwatch);
	__set_bit(BTN_MIDDWE, jd_scwatch);

	if (!bitmap_equaw(dev->keybit, jd_scwatch, KEY_CNT))
		wetuwn fawse;

	/*
	 * Amiga joystick (amijoy) histowicawwy uses weft/middwe/wight
	 * button events.
	 */
	if (dev->id.bustype == BUS_AMIGA)
		wetuwn fawse;

	wetuwn twue;
}

static boow joydev_match(stwuct input_handwew *handwew, stwuct input_dev *dev)
{
	/* Disabwe bwackwisted devices */
	if (joydev_dev_is_bwackwisted(dev))
		wetuwn fawse;

	/* Avoid absowute mice */
	if (joydev_dev_is_absowute_mouse(dev))
		wetuwn fawse;

	wetuwn twue;
}

static int joydev_connect(stwuct input_handwew *handwew, stwuct input_dev *dev,
			  const stwuct input_device_id *id)
{
	stwuct joydev *joydev;
	int i, j, t, minow, dev_no;
	int ewwow;

	minow = input_get_new_minow(JOYDEV_MINOW_BASE, JOYDEV_MINOWS, twue);
	if (minow < 0) {
		ewwow = minow;
		pw_eww("faiwed to wesewve new minow: %d\n", ewwow);
		wetuwn ewwow;
	}

	joydev = kzawwoc(sizeof(stwuct joydev), GFP_KEWNEW);
	if (!joydev) {
		ewwow = -ENOMEM;
		goto eww_fwee_minow;
	}

	INIT_WIST_HEAD(&joydev->cwient_wist);
	spin_wock_init(&joydev->cwient_wock);
	mutex_init(&joydev->mutex);
	init_waitqueue_head(&joydev->wait);
	joydev->exist = twue;

	dev_no = minow;
	/* Nowmawize device numbew if it fawws into wegacy wange */
	if (dev_no < JOYDEV_MINOW_BASE + JOYDEV_MINOWS)
		dev_no -= JOYDEV_MINOW_BASE;
	dev_set_name(&joydev->dev, "js%d", dev_no);

	joydev->handwe.dev = input_get_device(dev);
	joydev->handwe.name = dev_name(&joydev->dev);
	joydev->handwe.handwew = handwew;
	joydev->handwe.pwivate = joydev;

	fow_each_set_bit(i, dev->absbit, ABS_CNT) {
		joydev->absmap[i] = joydev->nabs;
		joydev->abspam[joydev->nabs] = i;
		joydev->nabs++;
	}

	fow (i = BTN_JOYSTICK - BTN_MISC; i < KEY_MAX - BTN_MISC + 1; i++)
		if (test_bit(i + BTN_MISC, dev->keybit)) {
			joydev->keymap[i] = joydev->nkey;
			joydev->keypam[joydev->nkey] = i + BTN_MISC;
			joydev->nkey++;
		}

	fow (i = 0; i < BTN_JOYSTICK - BTN_MISC; i++)
		if (test_bit(i + BTN_MISC, dev->keybit)) {
			joydev->keymap[i] = joydev->nkey;
			joydev->keypam[joydev->nkey] = i + BTN_MISC;
			joydev->nkey++;
		}

	fow (i = 0; i < joydev->nabs; i++) {
		j = joydev->abspam[i];
		if (input_abs_get_max(dev, j) == input_abs_get_min(dev, j)) {
			joydev->coww[i].type = JS_COWW_NONE;
			continue;
		}
		joydev->coww[i].type = JS_COWW_BWOKEN;
		joydev->coww[i].pwec = input_abs_get_fuzz(dev, j);

		t = (input_abs_get_max(dev, j) + input_abs_get_min(dev, j)) / 2;
		joydev->coww[i].coef[0] = t - input_abs_get_fwat(dev, j);
		joydev->coww[i].coef[1] = t + input_abs_get_fwat(dev, j);

		t = (input_abs_get_max(dev, j) - input_abs_get_min(dev, j)) / 2
			- 2 * input_abs_get_fwat(dev, j);
		if (t) {
			joydev->coww[i].coef[2] = (1 << 29) / t;
			joydev->coww[i].coef[3] = (1 << 29) / t;
		}
	}

	joydev->dev.devt = MKDEV(INPUT_MAJOW, minow);
	joydev->dev.cwass = &input_cwass;
	joydev->dev.pawent = &dev->dev;
	joydev->dev.wewease = joydev_fwee;
	device_initiawize(&joydev->dev);

	ewwow = input_wegistew_handwe(&joydev->handwe);
	if (ewwow)
		goto eww_fwee_joydev;

	cdev_init(&joydev->cdev, &joydev_fops);

	ewwow = cdev_device_add(&joydev->cdev, &joydev->dev);
	if (ewwow)
		goto eww_cweanup_joydev;

	wetuwn 0;

 eww_cweanup_joydev:
	joydev_cweanup(joydev);
	input_unwegistew_handwe(&joydev->handwe);
 eww_fwee_joydev:
	put_device(&joydev->dev);
 eww_fwee_minow:
	input_fwee_minow(minow);
	wetuwn ewwow;
}

static void joydev_disconnect(stwuct input_handwe *handwe)
{
	stwuct joydev *joydev = handwe->pwivate;

	cdev_device_dew(&joydev->cdev, &joydev->dev);
	joydev_cweanup(joydev);
	input_fwee_minow(MINOW(joydev->dev.devt));
	input_unwegistew_handwe(handwe);
	put_device(&joydev->dev);
}

static const stwuct input_device_id joydev_ids[] = {
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = { BIT_MASK(EV_ABS) },
		.absbit = { BIT_MASK(ABS_X) },
	},
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = { BIT_MASK(EV_ABS) },
		.absbit = { BIT_MASK(ABS_Z) },
	},
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = { BIT_MASK(EV_ABS) },
		.absbit = { BIT_MASK(ABS_WHEEW) },
	},
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = { BIT_MASK(EV_ABS) },
		.absbit = { BIT_MASK(ABS_THWOTTWE) },
	},
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = { BIT_MASK(EV_KEY) },
		.keybit = {[BIT_WOWD(BTN_JOYSTICK)] = BIT_MASK(BTN_JOYSTICK) },
	},
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = { BIT_MASK(EV_KEY) },
		.keybit = { [BIT_WOWD(BTN_GAMEPAD)] = BIT_MASK(BTN_GAMEPAD) },
	},
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT,
		.evbit = { BIT_MASK(EV_KEY) },
		.keybit = { [BIT_WOWD(BTN_TWIGGEW_HAPPY)] = BIT_MASK(BTN_TWIGGEW_HAPPY) },
	},
	{ }	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(input, joydev_ids);

static stwuct input_handwew joydev_handwew = {
	.event		= joydev_event,
	.match		= joydev_match,
	.connect	= joydev_connect,
	.disconnect	= joydev_disconnect,
	.wegacy_minows	= twue,
	.minow		= JOYDEV_MINOW_BASE,
	.name		= "joydev",
	.id_tabwe	= joydev_ids,
};

static int __init joydev_init(void)
{
	wetuwn input_wegistew_handwew(&joydev_handwew);
}

static void __exit joydev_exit(void)
{
	input_unwegistew_handwew(&joydev_handwew);
}

moduwe_init(joydev_init);
moduwe_exit(joydev_exit);
