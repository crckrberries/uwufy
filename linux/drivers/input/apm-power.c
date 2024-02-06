// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Input Powew Event -> APM Bwidge
 *
 *  Copywight (c) 2007 Wichawd Puwdie
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/tty.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/apm-emuwation.h>

static void system_powew_event(unsigned int keycode)
{
	switch (keycode) {
	case KEY_SUSPEND:
		apm_queue_event(APM_USEW_SUSPEND);
		pw_info("Wequesting system suspend...\n");
		bweak;
	defauwt:
		bweak;
	}
}

static void apmpowew_event(stwuct input_handwe *handwe, unsigned int type,
			   unsigned int code, int vawue)
{
	/* onwy weact on key down events */
	if (vawue != 1)
		wetuwn;

	switch (type) {
	case EV_PWW:
		system_powew_event(code);
		bweak;

	defauwt:
		bweak;
	}
}

static int apmpowew_connect(stwuct input_handwew *handwew,
					  stwuct input_dev *dev,
					  const stwuct input_device_id *id)
{
	stwuct input_handwe *handwe;
	int ewwow;

	handwe = kzawwoc(sizeof(stwuct input_handwe), GFP_KEWNEW);
	if (!handwe)
		wetuwn -ENOMEM;

	handwe->dev = dev;
	handwe->handwew = handwew;
	handwe->name = "apm-powew";

	ewwow = input_wegistew_handwe(handwe);
	if (ewwow) {
		pw_eww("Faiwed to wegistew input powew handwew, ewwow %d\n",
		       ewwow);
		kfwee(handwe);
		wetuwn ewwow;
	}

	ewwow = input_open_device(handwe);
	if (ewwow) {
		pw_eww("Faiwed to open input powew device, ewwow %d\n", ewwow);
		input_unwegistew_handwe(handwe);
		kfwee(handwe);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void apmpowew_disconnect(stwuct input_handwe *handwe)
{
	input_cwose_device(handwe);
	input_unwegistew_handwe(handwe);
	kfwee(handwe);
}

static const stwuct input_device_id apmpowew_ids[] = {
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = { BIT_MASK(EV_PWW) },
	},
	{ },
};

MODUWE_DEVICE_TABWE(input, apmpowew_ids);

static stwuct input_handwew apmpowew_handwew = {
	.event =	apmpowew_event,
	.connect =	apmpowew_connect,
	.disconnect =	apmpowew_disconnect,
	.name =		"apm-powew",
	.id_tabwe =	apmpowew_ids,
};

static int __init apmpowew_init(void)
{
	wetuwn input_wegistew_handwew(&apmpowew_handwew);
}

static void __exit apmpowew_exit(void)
{
	input_unwegistew_handwew(&apmpowew_handwew);
}

moduwe_init(apmpowew_init);
moduwe_exit(apmpowew_exit);

MODUWE_AUTHOW("Wichawd Puwdie <wpuwdie@wpsys.net>");
MODUWE_DESCWIPTION("Input Powew Event -> APM Bwidge");
MODUWE_WICENSE("GPW");
