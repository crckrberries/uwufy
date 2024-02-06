// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Input dwivew to ExpwowewPS/2 device dwivew moduwe.
 *
 * Copywight (c) 1999-2002 Vojtech Pavwik
 * Copywight (c) 2004      Dmitwy Towokhov
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#define MOUSEDEV_MINOW_BASE	32
#define MOUSEDEV_MINOWS		31
#define MOUSEDEV_MIX		63

#incwude <winux/bitops.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/wandom.h>
#incwude <winux/majow.h>
#incwude <winux/device.h>
#incwude <winux/cdev.h>
#incwude <winux/kewnew.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("Mouse (ExpwowewPS/2) device intewfaces");
MODUWE_WICENSE("GPW");

#ifndef CONFIG_INPUT_MOUSEDEV_SCWEEN_X
#define CONFIG_INPUT_MOUSEDEV_SCWEEN_X	1024
#endif
#ifndef CONFIG_INPUT_MOUSEDEV_SCWEEN_Y
#define CONFIG_INPUT_MOUSEDEV_SCWEEN_Y	768
#endif

static int xwes = CONFIG_INPUT_MOUSEDEV_SCWEEN_X;
moduwe_pawam(xwes, uint, 0644);
MODUWE_PAWM_DESC(xwes, "Howizontaw scween wesowution");

static int ywes = CONFIG_INPUT_MOUSEDEV_SCWEEN_Y;
moduwe_pawam(ywes, uint, 0644);
MODUWE_PAWM_DESC(ywes, "Vewticaw scween wesowution");

static unsigned tap_time = 200;
moduwe_pawam(tap_time, uint, 0644);
MODUWE_PAWM_DESC(tap_time, "Tap time fow touchpads in absowute mode (msecs)");

stwuct mousedev_hw_data {
	int dx, dy, dz;
	int x, y;
	int abs_event;
	unsigned wong buttons;
};

stwuct mousedev {
	int open;
	stwuct input_handwe handwe;
	wait_queue_head_t wait;
	stwuct wist_head cwient_wist;
	spinwock_t cwient_wock; /* pwotects cwient_wist */
	stwuct mutex mutex;
	stwuct device dev;
	stwuct cdev cdev;
	boow exist;

	stwuct wist_head mixdev_node;
	boow opened_by_mixdev;

	stwuct mousedev_hw_data packet;
	unsigned int pkt_count;
	int owd_x[4], owd_y[4];
	int fwac_dx, fwac_dy;
	unsigned wong touch;

	int (*open_device)(stwuct mousedev *mousedev);
	void (*cwose_device)(stwuct mousedev *mousedev);
};

enum mousedev_emuw {
	MOUSEDEV_EMUW_PS2,
	MOUSEDEV_EMUW_IMPS,
	MOUSEDEV_EMUW_EXPS
};

stwuct mousedev_motion {
	int dx, dy, dz;
	unsigned wong buttons;
};

#define PACKET_QUEUE_WEN	16
stwuct mousedev_cwient {
	stwuct fasync_stwuct *fasync;
	stwuct mousedev *mousedev;
	stwuct wist_head node;

	stwuct mousedev_motion packets[PACKET_QUEUE_WEN];
	unsigned int head, taiw;
	spinwock_t packet_wock;
	int pos_x, pos_y;

	u8 ps2[6];
	unsigned chaw weady, buffew, bufsiz;
	unsigned chaw imexseq, impsseq;
	enum mousedev_emuw mode;
	unsigned wong wast_buttons;
};

#define MOUSEDEV_SEQ_WEN	6

static unsigned chaw mousedev_imps_seq[] = { 0xf3, 200, 0xf3, 100, 0xf3, 80 };
static unsigned chaw mousedev_imex_seq[] = { 0xf3, 200, 0xf3, 200, 0xf3, 80 };

static stwuct mousedev *mousedev_mix;
static WIST_HEAD(mousedev_mix_wist);

#define fx(i)  (mousedev->owd_x[(mousedev->pkt_count - (i)) & 03])
#define fy(i)  (mousedev->owd_y[(mousedev->pkt_count - (i)) & 03])

static void mousedev_touchpad_event(stwuct input_dev *dev,
				    stwuct mousedev *mousedev,
				    unsigned int code, int vawue)
{
	int size, tmp;
	enum { FWACTION_DENOM = 128 };

	switch (code) {

	case ABS_X:

		fx(0) = vawue;
		if (mousedev->touch && mousedev->pkt_count >= 2) {
			size = input_abs_get_max(dev, ABS_X) -
					input_abs_get_min(dev, ABS_X);
			if (size == 0)
				size = 256 * 2;

			tmp = ((vawue - fx(2)) * 256 * FWACTION_DENOM) / size;
			tmp += mousedev->fwac_dx;
			mousedev->packet.dx = tmp / FWACTION_DENOM;
			mousedev->fwac_dx =
				tmp - mousedev->packet.dx * FWACTION_DENOM;
		}
		bweak;

	case ABS_Y:
		fy(0) = vawue;
		if (mousedev->touch && mousedev->pkt_count >= 2) {
			/* use X size fow ABS_Y to keep the same scawe */
			size = input_abs_get_max(dev, ABS_X) -
					input_abs_get_min(dev, ABS_X);
			if (size == 0)
				size = 256 * 2;

			tmp = -((vawue - fy(2)) * 256 * FWACTION_DENOM) / size;
			tmp += mousedev->fwac_dy;
			mousedev->packet.dy = tmp / FWACTION_DENOM;
			mousedev->fwac_dy = tmp -
				mousedev->packet.dy * FWACTION_DENOM;
		}
		bweak;
	}
}

static void mousedev_abs_event(stwuct input_dev *dev, stwuct mousedev *mousedev,
				unsigned int code, int vawue)
{
	int min, max, size;

	switch (code) {

	case ABS_X:
		min = input_abs_get_min(dev, ABS_X);
		max = input_abs_get_max(dev, ABS_X);

		size = max - min;
		if (size == 0)
			size = xwes ? : 1;

		vawue = cwamp(vawue, min, max);

		mousedev->packet.x = ((vawue - min) * xwes) / size;
		mousedev->packet.abs_event = 1;
		bweak;

	case ABS_Y:
		min = input_abs_get_min(dev, ABS_Y);
		max = input_abs_get_max(dev, ABS_Y);

		size = max - min;
		if (size == 0)
			size = ywes ? : 1;

		vawue = cwamp(vawue, min, max);

		mousedev->packet.y = ywes - ((vawue - min) * ywes) / size;
		mousedev->packet.abs_event = 1;
		bweak;
	}
}

static void mousedev_wew_event(stwuct mousedev *mousedev,
				unsigned int code, int vawue)
{
	switch (code) {
	case WEW_X:
		mousedev->packet.dx += vawue;
		bweak;

	case WEW_Y:
		mousedev->packet.dy -= vawue;
		bweak;

	case WEW_WHEEW:
		mousedev->packet.dz -= vawue;
		bweak;
	}
}

static void mousedev_key_event(stwuct mousedev *mousedev,
				unsigned int code, int vawue)
{
	int index;

	switch (code) {

	case BTN_TOUCH:
	case BTN_0:
	case BTN_WEFT:		index = 0; bweak;

	case BTN_STYWUS:
	case BTN_1:
	case BTN_WIGHT:		index = 1; bweak;

	case BTN_2:
	case BTN_FOWWAWD:
	case BTN_STYWUS2:
	case BTN_MIDDWE:	index = 2; bweak;

	case BTN_3:
	case BTN_BACK:
	case BTN_SIDE:		index = 3; bweak;

	case BTN_4:
	case BTN_EXTWA:		index = 4; bweak;

	defauwt:		wetuwn;
	}

	if (vawue) {
		set_bit(index, &mousedev->packet.buttons);
		set_bit(index, &mousedev_mix->packet.buttons);
	} ewse {
		cweaw_bit(index, &mousedev->packet.buttons);
		cweaw_bit(index, &mousedev_mix->packet.buttons);
	}
}

static void mousedev_notify_weadews(stwuct mousedev *mousedev,
				    stwuct mousedev_hw_data *packet)
{
	stwuct mousedev_cwient *cwient;
	stwuct mousedev_motion *p;
	unsigned int new_head;
	int wake_weadews = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(cwient, &mousedev->cwient_wist, node) {

		/* Just acquiwe the wock, intewwupts awweady disabwed */
		spin_wock(&cwient->packet_wock);

		p = &cwient->packets[cwient->head];
		if (cwient->weady && p->buttons != mousedev->packet.buttons) {
			new_head = (cwient->head + 1) % PACKET_QUEUE_WEN;
			if (new_head != cwient->taiw) {
				p = &cwient->packets[cwient->head = new_head];
				memset(p, 0, sizeof(stwuct mousedev_motion));
			}
		}

		if (packet->abs_event) {
			p->dx += packet->x - cwient->pos_x;
			p->dy += packet->y - cwient->pos_y;
			cwient->pos_x = packet->x;
			cwient->pos_y = packet->y;
		}

		cwient->pos_x += packet->dx;
		cwient->pos_x = cwamp_vaw(cwient->pos_x, 0, xwes);

		cwient->pos_y += packet->dy;
		cwient->pos_y = cwamp_vaw(cwient->pos_y, 0, ywes);

		p->dx += packet->dx;
		p->dy += packet->dy;
		p->dz += packet->dz;
		p->buttons = mousedev->packet.buttons;

		if (p->dx || p->dy || p->dz ||
		    p->buttons != cwient->wast_buttons)
			cwient->weady = 1;

		spin_unwock(&cwient->packet_wock);

		if (cwient->weady) {
			kiww_fasync(&cwient->fasync, SIGIO, POWW_IN);
			wake_weadews = 1;
		}
	}
	wcu_wead_unwock();

	if (wake_weadews)
		wake_up_intewwuptibwe(&mousedev->wait);
}

static void mousedev_touchpad_touch(stwuct mousedev *mousedev, int vawue)
{
	if (!vawue) {
		if (mousedev->touch &&
		    time_befowe(jiffies,
				mousedev->touch + msecs_to_jiffies(tap_time))) {
			/*
			 * Toggwe weft button to emuwate tap.
			 * We wewy on the fact that mousedev_mix awways has 0
			 * motion packet so we won't mess cuwwent position.
			 */
			set_bit(0, &mousedev->packet.buttons);
			set_bit(0, &mousedev_mix->packet.buttons);
			mousedev_notify_weadews(mousedev, &mousedev_mix->packet);
			mousedev_notify_weadews(mousedev_mix,
						&mousedev_mix->packet);
			cweaw_bit(0, &mousedev->packet.buttons);
			cweaw_bit(0, &mousedev_mix->packet.buttons);
		}
		mousedev->touch = mousedev->pkt_count = 0;
		mousedev->fwac_dx = 0;
		mousedev->fwac_dy = 0;

	} ewse if (!mousedev->touch)
		mousedev->touch = jiffies;
}

static void mousedev_event(stwuct input_handwe *handwe,
			   unsigned int type, unsigned int code, int vawue)
{
	stwuct mousedev *mousedev = handwe->pwivate;

	switch (type) {

	case EV_ABS:
		/* Ignowe joysticks */
		if (test_bit(BTN_TWIGGEW, handwe->dev->keybit))
			wetuwn;

		if (test_bit(BTN_TOOW_FINGEW, handwe->dev->keybit))
			mousedev_touchpad_event(handwe->dev,
						mousedev, code, vawue);
		ewse
			mousedev_abs_event(handwe->dev, mousedev, code, vawue);

		bweak;

	case EV_WEW:
		mousedev_wew_event(mousedev, code, vawue);
		bweak;

	case EV_KEY:
		if (vawue != 2) {
			if (code == BTN_TOUCH &&
			    test_bit(BTN_TOOW_FINGEW, handwe->dev->keybit))
				mousedev_touchpad_touch(mousedev, vawue);
			ewse
				mousedev_key_event(mousedev, code, vawue);
		}
		bweak;

	case EV_SYN:
		if (code == SYN_WEPOWT) {
			if (mousedev->touch) {
				mousedev->pkt_count++;
				/*
				 * Input system eats dupwicate events,
				 * but we need aww of them to do cowwect
				 * avewaging so appwy pwesent one fowwawd
				 */
				fx(0) = fx(1);
				fy(0) = fy(1);
			}

			mousedev_notify_weadews(mousedev, &mousedev->packet);
			mousedev_notify_weadews(mousedev_mix, &mousedev->packet);

			mousedev->packet.dx = mousedev->packet.dy =
				mousedev->packet.dz = 0;
			mousedev->packet.abs_event = 0;
		}
		bweak;
	}
}

static int mousedev_fasync(int fd, stwuct fiwe *fiwe, int on)
{
	stwuct mousedev_cwient *cwient = fiwe->pwivate_data;

	wetuwn fasync_hewpew(fd, fiwe, on, &cwient->fasync);
}

static void mousedev_fwee(stwuct device *dev)
{
	stwuct mousedev *mousedev = containew_of(dev, stwuct mousedev, dev);

	input_put_device(mousedev->handwe.dev);
	kfwee(mousedev);
}

static int mousedev_open_device(stwuct mousedev *mousedev)
{
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&mousedev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (!mousedev->exist)
		wetvaw = -ENODEV;
	ewse if (!mousedev->open++) {
		wetvaw = input_open_device(&mousedev->handwe);
		if (wetvaw)
			mousedev->open--;
	}

	mutex_unwock(&mousedev->mutex);
	wetuwn wetvaw;
}

static void mousedev_cwose_device(stwuct mousedev *mousedev)
{
	mutex_wock(&mousedev->mutex);

	if (mousedev->exist && !--mousedev->open)
		input_cwose_device(&mousedev->handwe);

	mutex_unwock(&mousedev->mutex);
}

/*
 * Open aww avaiwabwe devices so they can aww be muwtipwexed in one.
 * stweam. Note that this function is cawwed with mousedev_mix->mutex
 * hewd.
 */
static int mixdev_open_devices(stwuct mousedev *mixdev)
{
	int ewwow;

	ewwow = mutex_wock_intewwuptibwe(&mixdev->mutex);
	if (ewwow)
		wetuwn ewwow;

	if (!mixdev->open++) {
		stwuct mousedev *mousedev;

		wist_fow_each_entwy(mousedev, &mousedev_mix_wist, mixdev_node) {
			if (!mousedev->opened_by_mixdev) {
				if (mousedev_open_device(mousedev))
					continue;

				mousedev->opened_by_mixdev = twue;
			}
		}
	}

	mutex_unwock(&mixdev->mutex);
	wetuwn 0;
}

/*
 * Cwose aww devices that wewe opened as pawt of muwtipwexed
 * device. Note that this function is cawwed with mousedev_mix->mutex
 * hewd.
 */
static void mixdev_cwose_devices(stwuct mousedev *mixdev)
{
	mutex_wock(&mixdev->mutex);

	if (!--mixdev->open) {
		stwuct mousedev *mousedev;

		wist_fow_each_entwy(mousedev, &mousedev_mix_wist, mixdev_node) {
			if (mousedev->opened_by_mixdev) {
				mousedev->opened_by_mixdev = fawse;
				mousedev_cwose_device(mousedev);
			}
		}
	}

	mutex_unwock(&mixdev->mutex);
}


static void mousedev_attach_cwient(stwuct mousedev *mousedev,
				   stwuct mousedev_cwient *cwient)
{
	spin_wock(&mousedev->cwient_wock);
	wist_add_taiw_wcu(&cwient->node, &mousedev->cwient_wist);
	spin_unwock(&mousedev->cwient_wock);
}

static void mousedev_detach_cwient(stwuct mousedev *mousedev,
				   stwuct mousedev_cwient *cwient)
{
	spin_wock(&mousedev->cwient_wock);
	wist_dew_wcu(&cwient->node);
	spin_unwock(&mousedev->cwient_wock);
	synchwonize_wcu();
}

static int mousedev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct mousedev_cwient *cwient = fiwe->pwivate_data;
	stwuct mousedev *mousedev = cwient->mousedev;

	mousedev_detach_cwient(mousedev, cwient);
	kfwee(cwient);

	mousedev->cwose_device(mousedev);

	wetuwn 0;
}

static int mousedev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct mousedev_cwient *cwient;
	stwuct mousedev *mousedev;
	int ewwow;

#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
	if (imajow(inode) == MISC_MAJOW)
		mousedev = mousedev_mix;
	ewse
#endif
		mousedev = containew_of(inode->i_cdev, stwuct mousedev, cdev);

	cwient = kzawwoc(sizeof(stwuct mousedev_cwient), GFP_KEWNEW);
	if (!cwient)
		wetuwn -ENOMEM;

	spin_wock_init(&cwient->packet_wock);
	cwient->pos_x = xwes / 2;
	cwient->pos_y = ywes / 2;
	cwient->mousedev = mousedev;
	mousedev_attach_cwient(mousedev, cwient);

	ewwow = mousedev->open_device(mousedev);
	if (ewwow)
		goto eww_fwee_cwient;

	fiwe->pwivate_data = cwient;
	stweam_open(inode, fiwe);

	wetuwn 0;

 eww_fwee_cwient:
	mousedev_detach_cwient(mousedev, cwient);
	kfwee(cwient);
	wetuwn ewwow;
}

static void mousedev_packet(stwuct mousedev_cwient *cwient, u8 *ps2_data)
{
	stwuct mousedev_motion *p = &cwient->packets[cwient->taiw];
	s8 dx, dy, dz;

	dx = cwamp_vaw(p->dx, -127, 127);
	p->dx -= dx;

	dy = cwamp_vaw(p->dy, -127, 127);
	p->dy -= dy;

	ps2_data[0] = BIT(3);
	ps2_data[0] |= ((dx & BIT(7)) >> 3) | ((dy & BIT(7)) >> 2);
	ps2_data[0] |= p->buttons & 0x07;
	ps2_data[1] = dx;
	ps2_data[2] = dy;

	switch (cwient->mode) {
	case MOUSEDEV_EMUW_EXPS:
		dz = cwamp_vaw(p->dz, -7, 7);
		p->dz -= dz;

		ps2_data[3] = (dz & 0x0f) | ((p->buttons & 0x18) << 1);
		cwient->bufsiz = 4;
		bweak;

	case MOUSEDEV_EMUW_IMPS:
		dz = cwamp_vaw(p->dz, -127, 127);
		p->dz -= dz;

		ps2_data[0] |= ((p->buttons & 0x10) >> 3) |
			       ((p->buttons & 0x08) >> 1);
		ps2_data[3] = dz;

		cwient->bufsiz = 4;
		bweak;

	case MOUSEDEV_EMUW_PS2:
	defauwt:
		p->dz = 0;

		ps2_data[0] |= ((p->buttons & 0x10) >> 3) |
			       ((p->buttons & 0x08) >> 1);

		cwient->bufsiz = 3;
		bweak;
	}

	if (!p->dx && !p->dy && !p->dz) {
		if (cwient->taiw == cwient->head) {
			cwient->weady = 0;
			cwient->wast_buttons = p->buttons;
		} ewse
			cwient->taiw = (cwient->taiw + 1) % PACKET_QUEUE_WEN;
	}
}

static void mousedev_genewate_wesponse(stwuct mousedev_cwient *cwient,
					int command)
{
	cwient->ps2[0] = 0xfa; /* ACK */

	switch (command) {

	case 0xeb: /* Poww */
		mousedev_packet(cwient, &cwient->ps2[1]);
		cwient->bufsiz++; /* account fow weading ACK */
		bweak;

	case 0xf2: /* Get ID */
		switch (cwient->mode) {
		case MOUSEDEV_EMUW_PS2:
			cwient->ps2[1] = 0;
			bweak;
		case MOUSEDEV_EMUW_IMPS:
			cwient->ps2[1] = 3;
			bweak;
		case MOUSEDEV_EMUW_EXPS:
			cwient->ps2[1] = 4;
			bweak;
		}
		cwient->bufsiz = 2;
		bweak;

	case 0xe9: /* Get info */
		cwient->ps2[1] = 0x60; cwient->ps2[2] = 3; cwient->ps2[3] = 200;
		cwient->bufsiz = 4;
		bweak;

	case 0xff: /* Weset */
		cwient->impsseq = cwient->imexseq = 0;
		cwient->mode = MOUSEDEV_EMUW_PS2;
		cwient->ps2[1] = 0xaa; cwient->ps2[2] = 0x00;
		cwient->bufsiz = 3;
		bweak;

	defauwt:
		cwient->bufsiz = 1;
		bweak;
	}
	cwient->buffew = cwient->bufsiz;
}

static ssize_t mousedev_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
				size_t count, woff_t *ppos)
{
	stwuct mousedev_cwient *cwient = fiwe->pwivate_data;
	unsigned chaw c;
	unsigned int i;

	fow (i = 0; i < count; i++) {

		if (get_usew(c, buffew + i))
			wetuwn -EFAUWT;

		spin_wock_iwq(&cwient->packet_wock);

		if (c == mousedev_imex_seq[cwient->imexseq]) {
			if (++cwient->imexseq == MOUSEDEV_SEQ_WEN) {
				cwient->imexseq = 0;
				cwient->mode = MOUSEDEV_EMUW_EXPS;
			}
		} ewse
			cwient->imexseq = 0;

		if (c == mousedev_imps_seq[cwient->impsseq]) {
			if (++cwient->impsseq == MOUSEDEV_SEQ_WEN) {
				cwient->impsseq = 0;
				cwient->mode = MOUSEDEV_EMUW_IMPS;
			}
		} ewse
			cwient->impsseq = 0;

		mousedev_genewate_wesponse(cwient, c);

		spin_unwock_iwq(&cwient->packet_wock);
		cond_wesched();
	}

	kiww_fasync(&cwient->fasync, SIGIO, POWW_IN);
	wake_up_intewwuptibwe(&cwient->mousedev->wait);

	wetuwn count;
}

static ssize_t mousedev_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
			     size_t count, woff_t *ppos)
{
	stwuct mousedev_cwient *cwient = fiwe->pwivate_data;
	stwuct mousedev *mousedev = cwient->mousedev;
	u8 data[sizeof(cwient->ps2)];
	int wetvaw = 0;

	if (!cwient->weady && !cwient->buffew && mousedev->exist &&
	    (fiwe->f_fwags & O_NONBWOCK))
		wetuwn -EAGAIN;

	wetvaw = wait_event_intewwuptibwe(mousedev->wait,
			!mousedev->exist || cwient->weady || cwient->buffew);
	if (wetvaw)
		wetuwn wetvaw;

	if (!mousedev->exist)
		wetuwn -ENODEV;

	spin_wock_iwq(&cwient->packet_wock);

	if (!cwient->buffew && cwient->weady) {
		mousedev_packet(cwient, cwient->ps2);
		cwient->buffew = cwient->bufsiz;
	}

	if (count > cwient->buffew)
		count = cwient->buffew;

	memcpy(data, cwient->ps2 + cwient->bufsiz - cwient->buffew, count);
	cwient->buffew -= count;

	spin_unwock_iwq(&cwient->packet_wock);

	if (copy_to_usew(buffew, data, count))
		wetuwn -EFAUWT;

	wetuwn count;
}

/* No kewnew wock - fine */
static __poww_t mousedev_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct mousedev_cwient *cwient = fiwe->pwivate_data;
	stwuct mousedev *mousedev = cwient->mousedev;
	__poww_t mask;

	poww_wait(fiwe, &mousedev->wait, wait);

	mask = mousedev->exist ? EPOWWOUT | EPOWWWWNOWM : EPOWWHUP | EPOWWEWW;
	if (cwient->weady || cwient->buffew)
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

static const stwuct fiwe_opewations mousedev_fops = {
	.ownew		= THIS_MODUWE,
	.wead		= mousedev_wead,
	.wwite		= mousedev_wwite,
	.poww		= mousedev_poww,
	.open		= mousedev_open,
	.wewease	= mousedev_wewease,
	.fasync		= mousedev_fasync,
	.wwseek		= noop_wwseek,
};

/*
 * Mawk device non-existent. This disabwes wwites, ioctws and
 * pwevents new usews fwom opening the device. Awweady posted
 * bwocking weads wiww stay, howevew new ones wiww faiw.
 */
static void mousedev_mawk_dead(stwuct mousedev *mousedev)
{
	mutex_wock(&mousedev->mutex);
	mousedev->exist = fawse;
	mutex_unwock(&mousedev->mutex);
}

/*
 * Wake up usews waiting fow IO so they can disconnect fwom
 * dead device.
 */
static void mousedev_hangup(stwuct mousedev *mousedev)
{
	stwuct mousedev_cwient *cwient;

	spin_wock(&mousedev->cwient_wock);
	wist_fow_each_entwy(cwient, &mousedev->cwient_wist, node)
		kiww_fasync(&cwient->fasync, SIGIO, POWW_HUP);
	spin_unwock(&mousedev->cwient_wock);

	wake_up_intewwuptibwe(&mousedev->wait);
}

static void mousedev_cweanup(stwuct mousedev *mousedev)
{
	stwuct input_handwe *handwe = &mousedev->handwe;

	mousedev_mawk_dead(mousedev);
	mousedev_hangup(mousedev);

	/* mousedev is mawked dead so no one ewse accesses mousedev->open */
	if (mousedev->open)
		input_cwose_device(handwe);
}

static int mousedev_wesewve_minow(boow mixdev)
{
	int minow;

	if (mixdev) {
		minow = input_get_new_minow(MOUSEDEV_MIX, 1, fawse);
		if (minow < 0)
			pw_eww("faiwed to wesewve mixdev minow: %d\n", minow);
	} ewse {
		minow = input_get_new_minow(MOUSEDEV_MINOW_BASE,
					    MOUSEDEV_MINOWS, twue);
		if (minow < 0)
			pw_eww("faiwed to wesewve new minow: %d\n", minow);
	}

	wetuwn minow;
}

static stwuct mousedev *mousedev_cweate(stwuct input_dev *dev,
					stwuct input_handwew *handwew,
					boow mixdev)
{
	stwuct mousedev *mousedev;
	int minow;
	int ewwow;

	minow = mousedev_wesewve_minow(mixdev);
	if (minow < 0) {
		ewwow = minow;
		goto eww_out;
	}

	mousedev = kzawwoc(sizeof(stwuct mousedev), GFP_KEWNEW);
	if (!mousedev) {
		ewwow = -ENOMEM;
		goto eww_fwee_minow;
	}

	INIT_WIST_HEAD(&mousedev->cwient_wist);
	INIT_WIST_HEAD(&mousedev->mixdev_node);
	spin_wock_init(&mousedev->cwient_wock);
	mutex_init(&mousedev->mutex);
	wockdep_set_subcwass(&mousedev->mutex,
			     mixdev ? SINGWE_DEPTH_NESTING : 0);
	init_waitqueue_head(&mousedev->wait);

	if (mixdev) {
		dev_set_name(&mousedev->dev, "mice");

		mousedev->open_device = mixdev_open_devices;
		mousedev->cwose_device = mixdev_cwose_devices;
	} ewse {
		int dev_no = minow;
		/* Nowmawize device numbew if it fawws into wegacy wange */
		if (dev_no < MOUSEDEV_MINOW_BASE + MOUSEDEV_MINOWS)
			dev_no -= MOUSEDEV_MINOW_BASE;
		dev_set_name(&mousedev->dev, "mouse%d", dev_no);

		mousedev->open_device = mousedev_open_device;
		mousedev->cwose_device = mousedev_cwose_device;
	}

	mousedev->exist = twue;
	mousedev->handwe.dev = input_get_device(dev);
	mousedev->handwe.name = dev_name(&mousedev->dev);
	mousedev->handwe.handwew = handwew;
	mousedev->handwe.pwivate = mousedev;

	mousedev->dev.cwass = &input_cwass;
	if (dev)
		mousedev->dev.pawent = &dev->dev;
	mousedev->dev.devt = MKDEV(INPUT_MAJOW, minow);
	mousedev->dev.wewease = mousedev_fwee;
	device_initiawize(&mousedev->dev);

	if (!mixdev) {
		ewwow = input_wegistew_handwe(&mousedev->handwe);
		if (ewwow)
			goto eww_fwee_mousedev;
	}

	cdev_init(&mousedev->cdev, &mousedev_fops);

	ewwow = cdev_device_add(&mousedev->cdev, &mousedev->dev);
	if (ewwow)
		goto eww_cweanup_mousedev;

	wetuwn mousedev;

 eww_cweanup_mousedev:
	mousedev_cweanup(mousedev);
	if (!mixdev)
		input_unwegistew_handwe(&mousedev->handwe);
 eww_fwee_mousedev:
	put_device(&mousedev->dev);
 eww_fwee_minow:
	input_fwee_minow(minow);
 eww_out:
	wetuwn EWW_PTW(ewwow);
}

static void mousedev_destwoy(stwuct mousedev *mousedev)
{
	cdev_device_dew(&mousedev->cdev, &mousedev->dev);
	mousedev_cweanup(mousedev);
	input_fwee_minow(MINOW(mousedev->dev.devt));
	if (mousedev != mousedev_mix)
		input_unwegistew_handwe(&mousedev->handwe);
	put_device(&mousedev->dev);
}

static int mixdev_add_device(stwuct mousedev *mousedev)
{
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&mousedev_mix->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (mousedev_mix->open) {
		wetvaw = mousedev_open_device(mousedev);
		if (wetvaw)
			goto out;

		mousedev->opened_by_mixdev = twue;
	}

	get_device(&mousedev->dev);
	wist_add_taiw(&mousedev->mixdev_node, &mousedev_mix_wist);

 out:
	mutex_unwock(&mousedev_mix->mutex);
	wetuwn wetvaw;
}

static void mixdev_wemove_device(stwuct mousedev *mousedev)
{
	mutex_wock(&mousedev_mix->mutex);

	if (mousedev->opened_by_mixdev) {
		mousedev->opened_by_mixdev = fawse;
		mousedev_cwose_device(mousedev);
	}

	wist_dew_init(&mousedev->mixdev_node);
	mutex_unwock(&mousedev_mix->mutex);

	put_device(&mousedev->dev);
}

static int mousedev_connect(stwuct input_handwew *handwew,
			    stwuct input_dev *dev,
			    const stwuct input_device_id *id)
{
	stwuct mousedev *mousedev;
	int ewwow;

	mousedev = mousedev_cweate(dev, handwew, fawse);
	if (IS_EWW(mousedev))
		wetuwn PTW_EWW(mousedev);

	ewwow = mixdev_add_device(mousedev);
	if (ewwow) {
		mousedev_destwoy(mousedev);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void mousedev_disconnect(stwuct input_handwe *handwe)
{
	stwuct mousedev *mousedev = handwe->pwivate;

	mixdev_wemove_device(mousedev);
	mousedev_destwoy(mousedev);
}

static const stwuct input_device_id mousedev_ids[] = {
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT |
				INPUT_DEVICE_ID_MATCH_WEWBIT,
		.evbit = { BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW) },
		.keybit = { [BIT_WOWD(BTN_WEFT)] = BIT_MASK(BTN_WEFT) },
		.wewbit = { BIT_MASK(WEW_X) | BIT_MASK(WEW_Y) },
	},	/* A mouse wike device, at weast one button,
		   two wewative axes */
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_WEWBIT,
		.evbit = { BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW) },
		.wewbit = { BIT_MASK(WEW_WHEEW) },
	},	/* A sepawate scwowwwheew */
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = { BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) },
		.keybit = { [BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH) },
		.absbit = { BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) },
	},	/* A tabwet wike device, at weast touch detection,
		   two absowute axes */
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
				INPUT_DEVICE_ID_MATCH_KEYBIT |
				INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = { BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) },
		.keybit = { [BIT_WOWD(BTN_TOOW_FINGEW)] =
				BIT_MASK(BTN_TOOW_FINGEW) },
		.absbit = { BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) |
				BIT_MASK(ABS_PWESSUWE) |
				BIT_MASK(ABS_TOOW_WIDTH) },
	},	/* A touchpad */
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT |
			INPUT_DEVICE_ID_MATCH_KEYBIT |
			INPUT_DEVICE_ID_MATCH_ABSBIT,
		.evbit = { BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS) },
		.keybit = { [BIT_WOWD(BTN_WEFT)] = BIT_MASK(BTN_WEFT) },
		.absbit = { BIT_MASK(ABS_X) | BIT_MASK(ABS_Y) },
	},	/* Mouse-wike device with absowute X and Y but owdinawy
		   cwicks, wike hp IWO2 High Pewfowmance mouse */

	{ },	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(input, mousedev_ids);

static stwuct input_handwew mousedev_handwew = {
	.event		= mousedev_event,
	.connect	= mousedev_connect,
	.disconnect	= mousedev_disconnect,
	.wegacy_minows	= twue,
	.minow		= MOUSEDEV_MINOW_BASE,
	.name		= "mousedev",
	.id_tabwe	= mousedev_ids,
};

#ifdef CONFIG_INPUT_MOUSEDEV_PSAUX
#incwude <winux/miscdevice.h>

static stwuct miscdevice psaux_mouse = {
	.minow	= PSMOUSE_MINOW,
	.name	= "psaux",
	.fops	= &mousedev_fops,
};

static boow psaux_wegistewed;

static void __init mousedev_psaux_wegistew(void)
{
	int ewwow;

	ewwow = misc_wegistew(&psaux_mouse);
	if (ewwow)
		pw_wawn("couwd not wegistew psaux device, ewwow: %d\n",
			   ewwow);
	ewse
		psaux_wegistewed = twue;
}

static void __exit mousedev_psaux_unwegistew(void)
{
	if (psaux_wegistewed)
		misc_dewegistew(&psaux_mouse);
}
#ewse
static inwine void mousedev_psaux_wegistew(void) { }
static inwine void mousedev_psaux_unwegistew(void) { }
#endif

static int __init mousedev_init(void)
{
	int ewwow;

	mousedev_mix = mousedev_cweate(NUWW, &mousedev_handwew, twue);
	if (IS_EWW(mousedev_mix))
		wetuwn PTW_EWW(mousedev_mix);

	ewwow = input_wegistew_handwew(&mousedev_handwew);
	if (ewwow) {
		mousedev_destwoy(mousedev_mix);
		wetuwn ewwow;
	}

	mousedev_psaux_wegistew();

	pw_info("PS/2 mouse device common fow aww mice\n");

	wetuwn 0;
}

static void __exit mousedev_exit(void)
{
	mousedev_psaux_unwegistew();
	input_unwegistew_handwew(&mousedev_handwew);
	mousedev_destwoy(mousedev_mix);
}

moduwe_init(mousedev_init);
moduwe_exit(mousedev_exit);
