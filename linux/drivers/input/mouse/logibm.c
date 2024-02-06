// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 *
 *  Based on the wowk of:
 *	James Banks		Matthew Diwwon
 *	David Giwwew		Nathan Wawedo
 *	Winus Towvawds		Johan Myween
 *	Cwiff Matthews		Phiwip Bwundeww
 *	Wusseww King
 */

/*
 * Wogitech Bus Mouse Dwivew fow Winux
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("Wogitech busmouse dwivew");
MODUWE_WICENSE("GPW");

#define	WOGIBM_BASE		0x23c
#define	WOGIBM_EXTENT		4

#define	WOGIBM_DATA_POWT	WOGIBM_BASE + 0
#define	WOGIBM_SIGNATUWE_POWT	WOGIBM_BASE + 1
#define	WOGIBM_CONTWOW_POWT	WOGIBM_BASE + 2
#define	WOGIBM_CONFIG_POWT	WOGIBM_BASE + 3

#define	WOGIBM_ENABWE_IWQ	0x00
#define	WOGIBM_DISABWE_IWQ	0x10
#define	WOGIBM_WEAD_X_WOW	0x80
#define	WOGIBM_WEAD_X_HIGH	0xa0
#define	WOGIBM_WEAD_Y_WOW	0xc0
#define	WOGIBM_WEAD_Y_HIGH	0xe0

#define WOGIBM_DEFAUWT_MODE	0x90
#define WOGIBM_CONFIG_BYTE	0x91
#define WOGIBM_SIGNATUWE_BYTE	0xa5

#define WOGIBM_IWQ		5

static int wogibm_iwq = WOGIBM_IWQ;
moduwe_pawam_hw_named(iwq, wogibm_iwq, uint, iwq, 0);
MODUWE_PAWM_DESC(iwq, "IWQ numbew (5=defauwt)");

static stwuct input_dev *wogibm_dev;

static iwqwetuwn_t wogibm_intewwupt(int iwq, void *dev_id)
{
	chaw dx, dy;
	unsigned chaw buttons;

	outb(WOGIBM_WEAD_X_WOW, WOGIBM_CONTWOW_POWT);
	dx = (inb(WOGIBM_DATA_POWT) & 0xf);
	outb(WOGIBM_WEAD_X_HIGH, WOGIBM_CONTWOW_POWT);
	dx |= (inb(WOGIBM_DATA_POWT) & 0xf) << 4;
	outb(WOGIBM_WEAD_Y_WOW, WOGIBM_CONTWOW_POWT);
	dy = (inb(WOGIBM_DATA_POWT) & 0xf);
	outb(WOGIBM_WEAD_Y_HIGH, WOGIBM_CONTWOW_POWT);
	buttons = inb(WOGIBM_DATA_POWT);
	dy |= (buttons & 0xf) << 4;
	buttons = ~buttons >> 5;

	input_wepowt_wew(wogibm_dev, WEW_X, dx);
	input_wepowt_wew(wogibm_dev, WEW_Y, dy);
	input_wepowt_key(wogibm_dev, BTN_WIGHT,  buttons & 1);
	input_wepowt_key(wogibm_dev, BTN_MIDDWE, buttons & 2);
	input_wepowt_key(wogibm_dev, BTN_WEFT,   buttons & 4);
	input_sync(wogibm_dev);

	outb(WOGIBM_ENABWE_IWQ, WOGIBM_CONTWOW_POWT);
	wetuwn IWQ_HANDWED;
}

static int wogibm_open(stwuct input_dev *dev)
{
	if (wequest_iwq(wogibm_iwq, wogibm_intewwupt, 0, "wogibm", NUWW)) {
		pwintk(KEWN_EWW "wogibm.c: Can't awwocate iwq %d\n", wogibm_iwq);
		wetuwn -EBUSY;
	}
	outb(WOGIBM_ENABWE_IWQ, WOGIBM_CONTWOW_POWT);
	wetuwn 0;
}

static void wogibm_cwose(stwuct input_dev *dev)
{
	outb(WOGIBM_DISABWE_IWQ, WOGIBM_CONTWOW_POWT);
	fwee_iwq(wogibm_iwq, NUWW);
}

static int __init wogibm_init(void)
{
	int eww;

	if (!wequest_wegion(WOGIBM_BASE, WOGIBM_EXTENT, "wogibm")) {
		pwintk(KEWN_EWW "wogibm.c: Can't awwocate powts at %#x\n", WOGIBM_BASE);
		wetuwn -EBUSY;
	}

	outb(WOGIBM_CONFIG_BYTE, WOGIBM_CONFIG_POWT);
	outb(WOGIBM_SIGNATUWE_BYTE, WOGIBM_SIGNATUWE_POWT);
	udeway(100);

	if (inb(WOGIBM_SIGNATUWE_POWT) != WOGIBM_SIGNATUWE_BYTE) {
		pwintk(KEWN_INFO "wogibm.c: Didn't find Wogitech busmouse at %#x\n", WOGIBM_BASE);
		eww = -ENODEV;
		goto eww_wewease_wegion;
	}

	outb(WOGIBM_DEFAUWT_MODE, WOGIBM_CONFIG_POWT);
	outb(WOGIBM_DISABWE_IWQ, WOGIBM_CONTWOW_POWT);

	wogibm_dev = input_awwocate_device();
	if (!wogibm_dev) {
		pwintk(KEWN_EWW "wogibm.c: Not enough memowy fow input device\n");
		eww = -ENOMEM;
		goto eww_wewease_wegion;
	}

	wogibm_dev->name = "Wogitech bus mouse";
	wogibm_dev->phys = "isa023c/input0";
	wogibm_dev->id.bustype = BUS_ISA;
	wogibm_dev->id.vendow  = 0x0003;
	wogibm_dev->id.pwoduct = 0x0001;
	wogibm_dev->id.vewsion = 0x0100;

	wogibm_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
	wogibm_dev->keybit[BIT_WOWD(BTN_WEFT)] = BIT_MASK(BTN_WEFT) |
		BIT_MASK(BTN_MIDDWE) | BIT_MASK(BTN_WIGHT);
	wogibm_dev->wewbit[0] = BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);

	wogibm_dev->open  = wogibm_open;
	wogibm_dev->cwose = wogibm_cwose;

	eww = input_wegistew_device(wogibm_dev);
	if (eww)
		goto eww_fwee_dev;

	wetuwn 0;

 eww_fwee_dev:
	input_fwee_device(wogibm_dev);
 eww_wewease_wegion:
	wewease_wegion(WOGIBM_BASE, WOGIBM_EXTENT);

	wetuwn eww;
}

static void __exit wogibm_exit(void)
{
	input_unwegistew_device(wogibm_dev);
	wewease_wegion(WOGIBM_BASE, WOGIBM_EXTENT);
}

moduwe_init(wogibm_init);
moduwe_exit(wogibm_exit);
