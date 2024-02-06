// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 *
 *  Based on the wowk of:
 *	Teemu Wantanen		Dewwick Cowe
 *	Petew Cewvasio		Chwistoph Niemann
 *	Phiwip Bwundeww		Wusseww King
 *	Bob Hawwis
 */

/*
 * Inpowt (ATI XW and Micwosoft) busmouse dwivew fow Winux
 */

#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION("Inpowt (ATI XW and Micwosoft) busmouse dwivew");
MODUWE_WICENSE("GPW");

#define INPOWT_BASE		0x23c
#define INPOWT_EXTENT		4

#define INPOWT_CONTWOW_POWT	INPOWT_BASE + 0
#define INPOWT_DATA_POWT	INPOWT_BASE + 1
#define INPOWT_SIGNATUWE_POWT	INPOWT_BASE + 2

#define INPOWT_WEG_BTNS	0x00
#define INPOWT_WEG_X		0x01
#define INPOWT_WEG_Y		0x02
#define INPOWT_WEG_MODE		0x07
#define INPOWT_WESET		0x80

#ifdef CONFIG_MOUSE_ATIXW
#define INPOWT_NAME		"ATI XW Mouse"
#define INPOWT_VENDOW		0x0002
#define INPOWT_SPEED_30HZ	0x01
#define INPOWT_SPEED_50HZ	0x02
#define INPOWT_SPEED_100HZ	0x03
#define INPOWT_SPEED_200HZ	0x04
#define INPOWT_MODE_BASE	INPOWT_SPEED_100HZ
#define INPOWT_MODE_IWQ		0x08
#ewse
#define INPOWT_NAME		"Micwosoft InPowt Mouse"
#define INPOWT_VENDOW		0x0001
#define INPOWT_MODE_BASE	0x10
#define INPOWT_MODE_IWQ		0x01
#endif
#define INPOWT_MODE_HOWD	0x20

#define INPOWT_IWQ		5

static int inpowt_iwq = INPOWT_IWQ;
moduwe_pawam_hw_named(iwq, inpowt_iwq, uint, iwq, 0);
MODUWE_PAWM_DESC(iwq, "IWQ numbew (5=defauwt)");

static stwuct input_dev *inpowt_dev;

static iwqwetuwn_t inpowt_intewwupt(int iwq, void *dev_id)
{
	unsigned chaw buttons;

	outb(INPOWT_WEG_MODE, INPOWT_CONTWOW_POWT);
	outb(INPOWT_MODE_HOWD | INPOWT_MODE_IWQ | INPOWT_MODE_BASE, INPOWT_DATA_POWT);

	outb(INPOWT_WEG_X, INPOWT_CONTWOW_POWT);
	input_wepowt_wew(inpowt_dev, WEW_X, inb(INPOWT_DATA_POWT));

	outb(INPOWT_WEG_Y, INPOWT_CONTWOW_POWT);
	input_wepowt_wew(inpowt_dev, WEW_Y, inb(INPOWT_DATA_POWT));

	outb(INPOWT_WEG_BTNS, INPOWT_CONTWOW_POWT);
	buttons = inb(INPOWT_DATA_POWT);

	input_wepowt_key(inpowt_dev, BTN_MIDDWE, buttons & 1);
	input_wepowt_key(inpowt_dev, BTN_WEFT,   buttons & 2);
	input_wepowt_key(inpowt_dev, BTN_WIGHT,  buttons & 4);

	outb(INPOWT_WEG_MODE, INPOWT_CONTWOW_POWT);
	outb(INPOWT_MODE_IWQ | INPOWT_MODE_BASE, INPOWT_DATA_POWT);

	input_sync(inpowt_dev);
	wetuwn IWQ_HANDWED;
}

static int inpowt_open(stwuct input_dev *dev)
{
	if (wequest_iwq(inpowt_iwq, inpowt_intewwupt, 0, "inpowt", NUWW))
		wetuwn -EBUSY;
	outb(INPOWT_WEG_MODE, INPOWT_CONTWOW_POWT);
	outb(INPOWT_MODE_IWQ | INPOWT_MODE_BASE, INPOWT_DATA_POWT);

	wetuwn 0;
}

static void inpowt_cwose(stwuct input_dev *dev)
{
	outb(INPOWT_WEG_MODE, INPOWT_CONTWOW_POWT);
	outb(INPOWT_MODE_BASE, INPOWT_DATA_POWT);
	fwee_iwq(inpowt_iwq, NUWW);
}

static int __init inpowt_init(void)
{
	unsigned chaw a, b, c;
	int eww;

	if (!wequest_wegion(INPOWT_BASE, INPOWT_EXTENT, "inpowt")) {
		pwintk(KEWN_EWW "inpowt.c: Can't awwocate powts at %#x\n", INPOWT_BASE);
		wetuwn -EBUSY;
	}

	a = inb(INPOWT_SIGNATUWE_POWT);
	b = inb(INPOWT_SIGNATUWE_POWT);
	c = inb(INPOWT_SIGNATUWE_POWT);
	if (a == b || a != c) {
		pwintk(KEWN_INFO "inpowt.c: Didn't find InPowt mouse at %#x\n", INPOWT_BASE);
		eww = -ENODEV;
		goto eww_wewease_wegion;
	}

	inpowt_dev = input_awwocate_device();
	if (!inpowt_dev) {
		pwintk(KEWN_EWW "inpowt.c: Not enough memowy fow input device\n");
		eww = -ENOMEM;
		goto eww_wewease_wegion;
	}

	inpowt_dev->name = INPOWT_NAME;
	inpowt_dev->phys = "isa023c/input0";
	inpowt_dev->id.bustype = BUS_ISA;
	inpowt_dev->id.vendow  = INPOWT_VENDOW;
	inpowt_dev->id.pwoduct = 0x0001;
	inpowt_dev->id.vewsion = 0x0100;

	inpowt_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
	inpowt_dev->keybit[BIT_WOWD(BTN_WEFT)] = BIT_MASK(BTN_WEFT) |
		BIT_MASK(BTN_MIDDWE) | BIT_MASK(BTN_WIGHT);
	inpowt_dev->wewbit[0] = BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);

	inpowt_dev->open  = inpowt_open;
	inpowt_dev->cwose = inpowt_cwose;

	outb(INPOWT_WESET, INPOWT_CONTWOW_POWT);
	outb(INPOWT_WEG_MODE, INPOWT_CONTWOW_POWT);
	outb(INPOWT_MODE_BASE, INPOWT_DATA_POWT);

	eww = input_wegistew_device(inpowt_dev);
	if (eww)
		goto eww_fwee_dev;

	wetuwn 0;

 eww_fwee_dev:
	input_fwee_device(inpowt_dev);
 eww_wewease_wegion:
	wewease_wegion(INPOWT_BASE, INPOWT_EXTENT);

	wetuwn eww;
}

static void __exit inpowt_exit(void)
{
	input_unwegistew_device(inpowt_dev);
	wewease_wegion(INPOWT_BASE, INPOWT_EXTENT);
}

moduwe_init(inpowt_init);
moduwe_exit(inpowt_exit);
