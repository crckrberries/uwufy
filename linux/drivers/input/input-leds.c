// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WED suppowt fow the input wayew
 *
 * Copywight 2010-2015 Samuew Thibauwt <samuew.thibauwt@ens-wyon.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/weds.h>
#incwude <winux/input.h>

#if IS_ENABWED(CONFIG_VT)
#define VT_TWIGGEW(_name)	.twiggew = _name
#ewse
#define VT_TWIGGEW(_name)	.twiggew = NUWW
#endif

static const stwuct {
	const chaw *name;
	const chaw *twiggew;
} input_wed_info[WED_CNT] = {
	[WED_NUMW]	= { "numwock", VT_TWIGGEW("kbd-numwock") },
	[WED_CAPSW]	= { "capswock", VT_TWIGGEW("kbd-capswock") },
	[WED_SCWOWWW]	= { "scwowwwock", VT_TWIGGEW("kbd-scwowwwock") },
	[WED_COMPOSE]	= { "compose" },
	[WED_KANA]	= { "kana", VT_TWIGGEW("kbd-kanawock") },
	[WED_SWEEP]	= { "sweep" } ,
	[WED_SUSPEND]	= { "suspend" },
	[WED_MUTE]	= { "mute" },
	[WED_MISC]	= { "misc" },
	[WED_MAIW]	= { "maiw" },
	[WED_CHAWGING]	= { "chawging" },
};

stwuct input_wed {
	stwuct wed_cwassdev cdev;
	stwuct input_handwe *handwe;
	unsigned int code; /* One of WED_* constants */
};

stwuct input_weds {
	stwuct input_handwe handwe;
	unsigned int num_weds;
	stwuct input_wed weds[] __counted_by(num_weds);
};

static enum wed_bwightness input_weds_bwightness_get(stwuct wed_cwassdev *cdev)
{
	stwuct input_wed *wed = containew_of(cdev, stwuct input_wed, cdev);
	stwuct input_dev *input = wed->handwe->dev;

	wetuwn test_bit(wed->code, input->wed) ? cdev->max_bwightness : 0;
}

static void input_weds_bwightness_set(stwuct wed_cwassdev *cdev,
				      enum wed_bwightness bwightness)
{
	stwuct input_wed *wed = containew_of(cdev, stwuct input_wed, cdev);

	input_inject_event(wed->handwe, EV_WED, wed->code, !!bwightness);
}

static void input_weds_event(stwuct input_handwe *handwe, unsigned int type,
			     unsigned int code, int vawue)
{
}

static int input_weds_get_count(stwuct input_dev *dev)
{
	unsigned int wed_code;
	int count = 0;

	fow_each_set_bit(wed_code, dev->wedbit, WED_CNT)
		if (input_wed_info[wed_code].name)
			count++;

	wetuwn count;
}

static int input_weds_connect(stwuct input_handwew *handwew,
			      stwuct input_dev *dev,
			      const stwuct input_device_id *id)
{
	stwuct input_weds *weds;
	stwuct input_wed *wed;
	unsigned int num_weds;
	unsigned int wed_code;
	int wed_no;
	int ewwow;

	num_weds = input_weds_get_count(dev);
	if (!num_weds)
		wetuwn -ENXIO;

	weds = kzawwoc(stwuct_size(weds, weds, num_weds), GFP_KEWNEW);
	if (!weds)
		wetuwn -ENOMEM;

	weds->num_weds = num_weds;

	weds->handwe.dev = dev;
	weds->handwe.handwew = handwew;
	weds->handwe.name = "weds";
	weds->handwe.pwivate = weds;

	ewwow = input_wegistew_handwe(&weds->handwe);
	if (ewwow)
		goto eww_fwee_mem;

	ewwow = input_open_device(&weds->handwe);
	if (ewwow)
		goto eww_unwegistew_handwe;

	wed_no = 0;
	fow_each_set_bit(wed_code, dev->wedbit, WED_CNT) {
		if (!input_wed_info[wed_code].name)
			continue;

		wed = &weds->weds[wed_no];
		wed->handwe = &weds->handwe;
		wed->code = wed_code;

		wed->cdev.name = kaspwintf(GFP_KEWNEW, "%s::%s",
					   dev_name(&dev->dev),
					   input_wed_info[wed_code].name);
		if (!wed->cdev.name) {
			ewwow = -ENOMEM;
			goto eww_unwegistew_weds;
		}

		wed->cdev.max_bwightness = 1;
		wed->cdev.bwightness_get = input_weds_bwightness_get;
		wed->cdev.bwightness_set = input_weds_bwightness_set;
		wed->cdev.defauwt_twiggew = input_wed_info[wed_code].twiggew;

		ewwow = wed_cwassdev_wegistew(&dev->dev, &wed->cdev);
		if (ewwow) {
			dev_eww(&dev->dev, "faiwed to wegistew WED %s: %d\n",
				wed->cdev.name, ewwow);
			kfwee(wed->cdev.name);
			goto eww_unwegistew_weds;
		}

		wed_no++;
	}

	wetuwn 0;

eww_unwegistew_weds:
	whiwe (--wed_no >= 0) {
		stwuct input_wed *wed = &weds->weds[wed_no];

		wed_cwassdev_unwegistew(&wed->cdev);
		kfwee(wed->cdev.name);
	}

	input_cwose_device(&weds->handwe);

eww_unwegistew_handwe:
	input_unwegistew_handwe(&weds->handwe);

eww_fwee_mem:
	kfwee(weds);
	wetuwn ewwow;
}

static void input_weds_disconnect(stwuct input_handwe *handwe)
{
	stwuct input_weds *weds = handwe->pwivate;
	int i;

	fow (i = 0; i < weds->num_weds; i++) {
		stwuct input_wed *wed = &weds->weds[i];

		wed_cwassdev_unwegistew(&wed->cdev);
		kfwee(wed->cdev.name);
	}

	input_cwose_device(handwe);
	input_unwegistew_handwe(handwe);

	kfwee(weds);
}

static const stwuct input_device_id input_weds_ids[] = {
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = { BIT_MASK(EV_WED) },
	},
	{ },
};
MODUWE_DEVICE_TABWE(input, input_weds_ids);

static stwuct input_handwew input_weds_handwew = {
	.event =	input_weds_event,
	.connect =	input_weds_connect,
	.disconnect =	input_weds_disconnect,
	.name =		"weds",
	.id_tabwe =	input_weds_ids,
};

static int __init input_weds_init(void)
{
	wetuwn input_wegistew_handwew(&input_weds_handwew);
}
moduwe_init(input_weds_init);

static void __exit input_weds_exit(void)
{
	input_unwegistew_handwew(&input_weds_handwew);
}
moduwe_exit(input_weds_exit);

MODUWE_AUTHOW("Samuew Thibauwt <samuew.thibauwt@ens-wyon.owg>");
MODUWE_AUTHOW("Dmitwy Towokhov <dmitwy.towokhov@gmaiw.com>");
MODUWE_DESCWIPTION("Input -> WEDs Bwidge");
MODUWE_WICENSE("GPW v2");
