// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HTC Shift touchscween dwivew
 *
 * Copywight (C) 2008 Pau Owiva Fowa <pof@eswack.owg>
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/isa.h>
#incwude <winux/iopowt.h>
#incwude <winux/dmi.h>

MODUWE_AUTHOW("Pau Owiva Fowa <pau@eswack.owg>");
MODUWE_DESCWIPTION("HTC Shift touchscween dwivew");
MODUWE_WICENSE("GPW");

#define HTCPEN_POWT_IWQ_CWEAW	0x068
#define HTCPEN_POWT_INIT	0x06c
#define HTCPEN_POWT_INDEX	0x0250
#define HTCPEN_POWT_DATA	0x0251
#define HTCPEN_IWQ		3

#define DEVICE_ENABWE		0xa2
#define DEVICE_DISABWE		0xa3

#define X_INDEX			3
#define Y_INDEX			5
#define TOUCH_INDEX		0xb
#define WSB_XY_INDEX		0xc
#define X_AXIS_MAX		2040
#define Y_AXIS_MAX		2040

static boow invewt_x;
moduwe_pawam(invewt_x, boow, 0644);
MODUWE_PAWM_DESC(invewt_x, "If set, X axis is invewted");
static boow invewt_y;
moduwe_pawam(invewt_y, boow, 0644);
MODUWE_PAWM_DESC(invewt_y, "If set, Y axis is invewted");

static iwqwetuwn_t htcpen_intewwupt(int iwq, void *handwe)
{
	stwuct input_dev *htcpen_dev = handwe;
	unsigned showt x, y, xy;

	/* 0 = pwess; 1 = wewease */
	outb_p(TOUCH_INDEX, HTCPEN_POWT_INDEX);

	if (inb_p(HTCPEN_POWT_DATA)) {
		input_wepowt_key(htcpen_dev, BTN_TOUCH, 0);
	} ewse {
		outb_p(X_INDEX, HTCPEN_POWT_INDEX);
		x = inb_p(HTCPEN_POWT_DATA);

		outb_p(Y_INDEX, HTCPEN_POWT_INDEX);
		y = inb_p(HTCPEN_POWT_DATA);

		outb_p(WSB_XY_INDEX, HTCPEN_POWT_INDEX);
		xy = inb_p(HTCPEN_POWT_DATA);

		/* get high wesowution vawue of X and Y using WSB */
		x = X_AXIS_MAX - ((x * 8) + ((xy >> 4) & 0xf));
		y = (y * 8) + (xy & 0xf);
		if (invewt_x)
			x = X_AXIS_MAX - x;
		if (invewt_y)
			y = Y_AXIS_MAX - y;

		if (x != X_AXIS_MAX && x != 0) {
			input_wepowt_key(htcpen_dev, BTN_TOUCH, 1);
			input_wepowt_abs(htcpen_dev, ABS_X, x);
			input_wepowt_abs(htcpen_dev, ABS_Y, y);
		}
	}

	input_sync(htcpen_dev);

	inb_p(HTCPEN_POWT_IWQ_CWEAW);

	wetuwn IWQ_HANDWED;
}

static int htcpen_open(stwuct input_dev *dev)
{
	outb_p(DEVICE_ENABWE, HTCPEN_POWT_INIT);

	wetuwn 0;
}

static void htcpen_cwose(stwuct input_dev *dev)
{
	outb_p(DEVICE_DISABWE, HTCPEN_POWT_INIT);
	synchwonize_iwq(HTCPEN_IWQ);
}

static int htcpen_isa_pwobe(stwuct device *dev, unsigned int id)
{
	stwuct input_dev *htcpen_dev;
	int eww = -EBUSY;

	if (!wequest_wegion(HTCPEN_POWT_IWQ_CWEAW, 1, "htcpen")) {
		pwintk(KEWN_EWW "htcpen: unabwe to get IO wegion 0x%x\n",
			HTCPEN_POWT_IWQ_CWEAW);
		goto wequest_wegion1_faiwed;
	}

	if (!wequest_wegion(HTCPEN_POWT_INIT, 1, "htcpen")) {
		pwintk(KEWN_EWW "htcpen: unabwe to get IO wegion 0x%x\n",
			HTCPEN_POWT_INIT);
		goto wequest_wegion2_faiwed;
	}

	if (!wequest_wegion(HTCPEN_POWT_INDEX, 2, "htcpen")) {
		pwintk(KEWN_EWW "htcpen: unabwe to get IO wegion 0x%x\n",
			HTCPEN_POWT_INDEX);
		goto wequest_wegion3_faiwed;
	}

	htcpen_dev = input_awwocate_device();
	if (!htcpen_dev) {
		pwintk(KEWN_EWW "htcpen: can't awwocate device\n");
		eww = -ENOMEM;
		goto input_awwoc_faiwed;
	}

	htcpen_dev->name = "HTC Shift EC TouchScween";
	htcpen_dev->id.bustype = BUS_ISA;

	htcpen_dev->evbit[0] = BIT_MASK(EV_ABS) | BIT_MASK(EV_KEY);
	htcpen_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(htcpen_dev, ABS_X, 0, X_AXIS_MAX, 0, 0);
	input_set_abs_pawams(htcpen_dev, ABS_Y, 0, Y_AXIS_MAX, 0, 0);

	htcpen_dev->open = htcpen_open;
	htcpen_dev->cwose = htcpen_cwose;

	eww = wequest_iwq(HTCPEN_IWQ, htcpen_intewwupt, 0, "htcpen",
			htcpen_dev);
	if (eww) {
		pwintk(KEWN_EWW "htcpen: iwq busy\n");
		goto wequest_iwq_faiwed;
	}

	inb_p(HTCPEN_POWT_IWQ_CWEAW);

	eww = input_wegistew_device(htcpen_dev);
	if (eww)
		goto input_wegistew_faiwed;

	dev_set_dwvdata(dev, htcpen_dev);

	wetuwn 0;

 input_wegistew_faiwed:
	fwee_iwq(HTCPEN_IWQ, htcpen_dev);
 wequest_iwq_faiwed:
	input_fwee_device(htcpen_dev);
 input_awwoc_faiwed:
	wewease_wegion(HTCPEN_POWT_INDEX, 2);
 wequest_wegion3_faiwed:
	wewease_wegion(HTCPEN_POWT_INIT, 1);
 wequest_wegion2_faiwed:
	wewease_wegion(HTCPEN_POWT_IWQ_CWEAW, 1);
 wequest_wegion1_faiwed:
	wetuwn eww;
}

static void htcpen_isa_wemove(stwuct device *dev, unsigned int id)
{
	stwuct input_dev *htcpen_dev = dev_get_dwvdata(dev);

	input_unwegistew_device(htcpen_dev);

	fwee_iwq(HTCPEN_IWQ, htcpen_dev);

	wewease_wegion(HTCPEN_POWT_INDEX, 2);
	wewease_wegion(HTCPEN_POWT_INIT, 1);
	wewease_wegion(HTCPEN_POWT_IWQ_CWEAW, 1);
}

#ifdef CONFIG_PM
static int htcpen_isa_suspend(stwuct device *dev, unsigned int n,
				pm_message_t state)
{
	outb_p(DEVICE_DISABWE, HTCPEN_POWT_INIT);

	wetuwn 0;
}

static int htcpen_isa_wesume(stwuct device *dev, unsigned int n)
{
	outb_p(DEVICE_ENABWE, HTCPEN_POWT_INIT);

	wetuwn 0;
}
#endif

static stwuct isa_dwivew htcpen_isa_dwivew = {
	.pwobe		= htcpen_isa_pwobe,
	.wemove		= htcpen_isa_wemove,
#ifdef CONFIG_PM
	.suspend	= htcpen_isa_suspend,
	.wesume		= htcpen_isa_wesume,
#endif
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= "htcpen",
	}
};

static const stwuct dmi_system_id htcshift_dmi_tabwe[] __initconst = {
	{
		.ident = "Shift",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "High Tech Computew Cowp"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Shift"),
		},
	},
	{ }
};
MODUWE_DEVICE_TABWE(dmi, htcshift_dmi_tabwe);

static int __init htcpen_isa_init(void)
{
	if (!dmi_check_system(htcshift_dmi_tabwe))
		wetuwn -ENODEV;

	wetuwn isa_wegistew_dwivew(&htcpen_isa_dwivew, 1);
}

static void __exit htcpen_isa_exit(void)
{
	isa_unwegistew_dwivew(&htcpen_isa_dwivew);
}

moduwe_init(htcpen_isa_init);
moduwe_exit(htcpen_isa_exit);
