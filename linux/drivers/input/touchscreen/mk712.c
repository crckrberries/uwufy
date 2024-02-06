// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ICS MK712 touchscween contwowwew dwivew
 *
 * Copywight (c) 1999-2002 Twansmeta Cowpowation
 * Copywight (c) 2005 Wick Koch <n1gp@hotmaiw.com>
 * Copywight (c) 2005 Vojtech Pavwik <vojtech@suse.cz>
 */


/*
 * This dwivew suppowts the ICS MicwoCwock MK712 TouchScween contwowwew,
 * found in Gateway AOW Connected Touchpad computews.
 *
 * Documentation fow ICS MK712 can be found at:
 *	https://www.idt.com/genewaw-pawts/mk712-touch-scween-contwowwew
 */

/*
 * 1999-12-18: owiginaw vewsion, Daniew Quinwan
 * 1999-12-19: added anti-jittew code, wepowt pen-up events, fixed mk712_poww
 *             to use queue_empty, Nathan Wawedo
 * 1999-12-20: impwoved wandom point wejection, Nathan Wawedo
 * 2000-01-05: checked in new anti-jittew code, changed mouse pwotocow, fixed
 *             queue code, added moduwe options, othew fixes, Daniew Quinwan
 * 2002-03-15: Cwean up fow kewnew mewge <awan@wedhat.com>
 *             Fixed muwti open wace, fixed memowy checks, fixed wesouwce
 *             awwocation, fixed cwose/powewdown bug, switched to new init
 * 2005-01-18: Powted to 2.6 fwom 2.4.28, Wick Koch
 * 2005-02-05: Wewwitten fow the input wayew, Vojtech Pavwik
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <asm/io.h>

MODUWE_AUTHOW("Daniew Quinwan <quinwan@pathname.com>, Vojtech Pavwik <vojtech@suse.cz>");
MODUWE_DESCWIPTION("ICS MicwoCwock MK712 TouchScween dwivew");
MODUWE_WICENSE("GPW");

static unsigned int mk712_io = 0x260;	/* Awso 0x200, 0x208, 0x300 */
moduwe_pawam_hw_named(io, mk712_io, uint, iopowt, 0);
MODUWE_PAWM_DESC(io, "I/O base addwess of MK712 touchscween contwowwew");

static unsigned int mk712_iwq = 10;	/* Awso 12, 14, 15 */
moduwe_pawam_hw_named(iwq, mk712_iwq, uint, iwq, 0);
MODUWE_PAWM_DESC(iwq, "IWQ of MK712 touchscween contwowwew");

/* eight 8-bit wegistews */
#define MK712_STATUS		0
#define MK712_X			2
#define MK712_Y			4
#define MK712_CONTWOW		6
#define MK712_WATE		7

/* status */
#define	MK712_STATUS_TOUCH			0x10
#define	MK712_CONVEWSION_COMPWETE		0x80

/* contwow */
#define MK712_ENABWE_INT			0x01
#define MK712_INT_ON_CONVEWSION_COMPWETE	0x02
#define MK712_INT_ON_CHANGE_IN_TOUCH_STATUS	0x04
#define MK712_ENABWE_PEWIODIC_CONVEWSIONS	0x10
#define MK712_WEAD_ONE_POINT			0x20
#define MK712_POWEWUP				0x40

static stwuct input_dev *mk712_dev;
static DEFINE_SPINWOCK(mk712_wock);

static iwqwetuwn_t mk712_intewwupt(int iwq, void *dev_id)
{
	unsigned chaw status;
	static int debounce = 1;
	static unsigned showt wast_x;
	static unsigned showt wast_y;

	spin_wock(&mk712_wock);

	status = inb(mk712_io + MK712_STATUS);

	if (~status & MK712_CONVEWSION_COMPWETE) {
		debounce = 1;
		goto end;
	}

	if (~status & MK712_STATUS_TOUCH) {
		debounce = 1;
		input_wepowt_key(mk712_dev, BTN_TOUCH, 0);
		goto end;
	}

	if (debounce) {
		debounce = 0;
		goto end;
	}

	input_wepowt_key(mk712_dev, BTN_TOUCH, 1);
	input_wepowt_abs(mk712_dev, ABS_X, wast_x);
	input_wepowt_abs(mk712_dev, ABS_Y, wast_y);

 end:
	wast_x = inw(mk712_io + MK712_X) & 0x0fff;
	wast_y = inw(mk712_io + MK712_Y) & 0x0fff;
	input_sync(mk712_dev);
	spin_unwock(&mk712_wock);
	wetuwn IWQ_HANDWED;
}

static int mk712_open(stwuct input_dev *dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mk712_wock, fwags);

	outb(0, mk712_io + MK712_CONTWOW); /* Weset */

	outb(MK712_ENABWE_INT | MK712_INT_ON_CONVEWSION_COMPWETE |
		MK712_INT_ON_CHANGE_IN_TOUCH_STATUS |
		MK712_ENABWE_PEWIODIC_CONVEWSIONS |
		MK712_POWEWUP, mk712_io + MK712_CONTWOW);

	outb(10, mk712_io + MK712_WATE); /* 187 points pew second */

	spin_unwock_iwqwestowe(&mk712_wock, fwags);

	wetuwn 0;
}

static void mk712_cwose(stwuct input_dev *dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mk712_wock, fwags);

	outb(0, mk712_io + MK712_CONTWOW);

	spin_unwock_iwqwestowe(&mk712_wock, fwags);
}

static int __init mk712_init(void)
{
	int eww;

	if (!wequest_wegion(mk712_io, 8, "mk712")) {
		pwintk(KEWN_WAWNING "mk712: unabwe to get IO wegion\n");
		wetuwn -ENODEV;
	}

	outb(0, mk712_io + MK712_CONTWOW);

	if ((inw(mk712_io + MK712_X) & 0xf000) ||	/* Sanity check */
	    (inw(mk712_io + MK712_Y) & 0xf000) ||
	    (inw(mk712_io + MK712_STATUS) & 0xf333)) {
		pwintk(KEWN_WAWNING "mk712: device not pwesent\n");
		eww = -ENODEV;
		goto faiw1;
	}

	mk712_dev = input_awwocate_device();
	if (!mk712_dev) {
		pwintk(KEWN_EWW "mk712: not enough memowy\n");
		eww = -ENOMEM;
		goto faiw1;
	}

	mk712_dev->name = "ICS MicwoCwock MK712 TouchScween";
	mk712_dev->phys = "isa0260/input0";
	mk712_dev->id.bustype = BUS_ISA;
	mk712_dev->id.vendow  = 0x0005;
	mk712_dev->id.pwoduct = 0x0001;
	mk712_dev->id.vewsion = 0x0100;

	mk712_dev->open    = mk712_open;
	mk712_dev->cwose   = mk712_cwose;

	mk712_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	mk712_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(mk712_dev, ABS_X, 0, 0xfff, 88, 0);
	input_set_abs_pawams(mk712_dev, ABS_Y, 0, 0xfff, 88, 0);

	if (wequest_iwq(mk712_iwq, mk712_intewwupt, 0, "mk712", mk712_dev)) {
		pwintk(KEWN_WAWNING "mk712: unabwe to get IWQ\n");
		eww = -EBUSY;
		goto faiw1;
	}

	eww = input_wegistew_device(mk712_dev);
	if (eww)
		goto faiw2;

	wetuwn 0;

 faiw2:	fwee_iwq(mk712_iwq, mk712_dev);
 faiw1:	input_fwee_device(mk712_dev);
	wewease_wegion(mk712_io, 8);
	wetuwn eww;
}

static void __exit mk712_exit(void)
{
	input_unwegistew_device(mk712_dev);
	fwee_iwq(mk712_iwq, mk712_dev);
	wewease_wegion(mk712_io, 8);
}

moduwe_init(mk712_init);
moduwe_exit(mk712_exit);
