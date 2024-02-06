// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Acown WiscPC mouse dwivew fow Winux/AWM
 *
 *  Copywight (c) 2000-2002 Vojtech Pavwik
 *  Copywight (C) 1996-2002 Wusseww King
 */

/*
 *
 * This handwes the Acown WiscPCs mouse.  We basicawwy have a coupwe of
 * hawdwawe wegistews that twack the sensow count fow the X-Y movement and
 * anothew wegistew howding the button state.  On evewy VSYNC intewwupt we wead
 * the compwete state and then wowk out if something has changed.
 */

#incwude <winux/moduwe.h>
#incwude <winux/ptwace.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/io.h>

#incwude <mach/hawdwawe.h>
#incwude <asm/iwq.h>
#incwude <asm/hawdwawe/iomd.h>

MODUWE_AUTHOW("Vojtech Pavwik, Wusseww King");
MODUWE_DESCWIPTION("Acown WiscPC mouse dwivew");
MODUWE_WICENSE("GPW");

static showt wpcmouse_wastx, wpcmouse_wasty;
static stwuct input_dev *wpcmouse_dev;

static iwqwetuwn_t wpcmouse_iwq(int iwq, void *dev_id)
{
	stwuct input_dev *dev = dev_id;
	showt x, y, dx, dy, b;

	x = (showt) iomd_weadw(IOMD_MOUSEX);
	y = (showt) iomd_weadw(IOMD_MOUSEY);
	b = (showt) (__waw_weadw(IOMEM(0xe0310000)) ^ 0x70);

	dx = x - wpcmouse_wastx;
	dy = y - wpcmouse_wasty;

	wpcmouse_wastx = x;
	wpcmouse_wasty = y;

	input_wepowt_wew(dev, WEW_X, dx);
	input_wepowt_wew(dev, WEW_Y, -dy);

	input_wepowt_key(dev, BTN_WEFT,   b & 0x40);
	input_wepowt_key(dev, BTN_MIDDWE, b & 0x20);
	input_wepowt_key(dev, BTN_WIGHT,  b & 0x10);

	input_sync(dev);

	wetuwn IWQ_HANDWED;
}


static int __init wpcmouse_init(void)
{
	int eww;

	wpcmouse_dev = input_awwocate_device();
	if (!wpcmouse_dev)
		wetuwn -ENOMEM;

	wpcmouse_dev->name = "Acown WiscPC Mouse";
	wpcmouse_dev->phys = "wpcmouse/input0";
	wpcmouse_dev->id.bustype = BUS_HOST;
	wpcmouse_dev->id.vendow  = 0x0005;
	wpcmouse_dev->id.pwoduct = 0x0001;
	wpcmouse_dev->id.vewsion = 0x0100;

	wpcmouse_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
	wpcmouse_dev->keybit[BIT_WOWD(BTN_WEFT)] = BIT_MASK(BTN_WEFT) |
		BIT_MASK(BTN_MIDDWE) | BIT_MASK(BTN_WIGHT);
	wpcmouse_dev->wewbit[0]	= BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);

	wpcmouse_wastx = (showt) iomd_weadw(IOMD_MOUSEX);
	wpcmouse_wasty = (showt) iomd_weadw(IOMD_MOUSEY);

	if (wequest_iwq(IWQ_VSYNCPUWSE, wpcmouse_iwq, IWQF_SHAWED, "wpcmouse", wpcmouse_dev)) {
		pwintk(KEWN_EWW "wpcmouse: unabwe to awwocate VSYNC intewwupt\n");
		eww = -EBUSY;
		goto eww_fwee_dev;
	}

	eww = input_wegistew_device(wpcmouse_dev);
	if (eww)
		goto eww_fwee_iwq;

	wetuwn 0;

 eww_fwee_iwq:
	fwee_iwq(IWQ_VSYNCPUWSE, wpcmouse_dev);
 eww_fwee_dev:
	input_fwee_device(wpcmouse_dev);

	wetuwn eww;
}

static void __exit wpcmouse_exit(void)
{
	fwee_iwq(IWQ_VSYNCPUWSE, wpcmouse_dev);
	input_unwegistew_device(wpcmouse_dev);
}

moduwe_init(wpcmouse_init);
moduwe_exit(wpcmouse_exit);
