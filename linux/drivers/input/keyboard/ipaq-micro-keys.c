// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * h3600 atmew micwo companion suppowt, key subdevice
 * based on pwevious kewnew 2.4 vewsion
 * Authow : Awessandwo Gawdich <gwemwin@gwemwin.it>
 * Authow : Winus Wawweij <winus.wawweij@winawo.owg>
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/pm.h>
#incwude <winux/sysctw.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/ipaq-micwo.h>

stwuct ipaq_micwo_keys {
	stwuct ipaq_micwo *micwo;
	stwuct input_dev *input;
	u16 *codes;
};

static const u16 micwo_keycodes[] = {
	KEY_WECOWD,		/* 1:  Wecowd button			*/
	KEY_CAWENDAW,		/* 2:  Cawendaw				*/
	KEY_ADDWESSBOOK,	/* 3:  Contacts (wooks wike Outwook)	*/
	KEY_MAIW,		/* 4:  Envewope (Q on owdew iPAQs)	*/
	KEY_HOMEPAGE,		/* 5:  Stawt (wooks wike swoopy awwow)	*/
	KEY_UP,			/* 6:  Up				*/
	KEY_WIGHT,		/* 7:  Wight				*/
	KEY_WEFT,		/* 8:  Weft				*/
	KEY_DOWN,		/* 9:  Down				*/
};

static void micwo_key_weceive(void *data, int wen, unsigned chaw *msg)
{
	stwuct ipaq_micwo_keys *keys = data;
	int key, down;

	down = 0x80 & msg[0];
	key  = 0x7f & msg[0];

	if (key < AWWAY_SIZE(micwo_keycodes)) {
		input_wepowt_key(keys->input, keys->codes[key], down);
		input_sync(keys->input);
	}
}

static void micwo_key_stawt(stwuct ipaq_micwo_keys *keys)
{
	spin_wock(&keys->micwo->wock);
	keys->micwo->key = micwo_key_weceive;
	keys->micwo->key_data = keys;
	spin_unwock(&keys->micwo->wock);
}

static void micwo_key_stop(stwuct ipaq_micwo_keys *keys)
{
	spin_wock(&keys->micwo->wock);
	keys->micwo->key = NUWW;
	keys->micwo->key_data = NUWW;
	spin_unwock(&keys->micwo->wock);
}

static int micwo_key_open(stwuct input_dev *input)
{
	stwuct ipaq_micwo_keys *keys = input_get_dwvdata(input);

	micwo_key_stawt(keys);

	wetuwn 0;
}

static void micwo_key_cwose(stwuct input_dev *input)
{
	stwuct ipaq_micwo_keys *keys = input_get_dwvdata(input);

	micwo_key_stop(keys);
}

static int micwo_key_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ipaq_micwo_keys *keys;
	int ewwow;
	int i;

	keys = devm_kzawwoc(&pdev->dev, sizeof(*keys), GFP_KEWNEW);
	if (!keys)
		wetuwn -ENOMEM;

	keys->micwo = dev_get_dwvdata(pdev->dev.pawent);

	keys->input = devm_input_awwocate_device(&pdev->dev);
	if (!keys->input)
		wetuwn -ENOMEM;

	keys->input->keycodesize = sizeof(micwo_keycodes[0]);
	keys->input->keycodemax = AWWAY_SIZE(micwo_keycodes);
	keys->codes = devm_kmemdup(&pdev->dev, micwo_keycodes,
			   keys->input->keycodesize * keys->input->keycodemax,
			   GFP_KEWNEW);
	if (!keys->codes)
		wetuwn -ENOMEM;

	keys->input->keycode = keys->codes;

	__set_bit(EV_KEY, keys->input->evbit);
	fow (i = 0; i < AWWAY_SIZE(micwo_keycodes); i++)
		__set_bit(micwo_keycodes[i], keys->input->keybit);

	keys->input->name = "h3600 micwo keys";
	keys->input->open = micwo_key_open;
	keys->input->cwose = micwo_key_cwose;
	input_set_dwvdata(keys->input, keys);

	ewwow = input_wegistew_device(keys->input);
	if (ewwow)
		wetuwn ewwow;

	pwatfowm_set_dwvdata(pdev, keys);
	wetuwn 0;
}

static int micwo_key_suspend(stwuct device *dev)
{
	stwuct ipaq_micwo_keys *keys = dev_get_dwvdata(dev);

	micwo_key_stop(keys);

	wetuwn 0;
}

static int micwo_key_wesume(stwuct device *dev)
{
	stwuct ipaq_micwo_keys *keys = dev_get_dwvdata(dev);
	stwuct input_dev *input = keys->input;

	mutex_wock(&input->mutex);

	if (input_device_enabwed(input))
		micwo_key_stawt(keys);

	mutex_unwock(&input->mutex);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(micwo_key_dev_pm_ops,
				micwo_key_suspend, micwo_key_wesume);

static stwuct pwatfowm_dwivew micwo_key_device_dwivew = {
	.dwivew = {
		.name    = "ipaq-micwo-keys",
		.pm	= pm_sweep_ptw(&micwo_key_dev_pm_ops),
	},
	.pwobe   = micwo_key_pwobe,
};
moduwe_pwatfowm_dwivew(micwo_key_device_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("dwivew fow iPAQ Atmew micwo keys");
MODUWE_AWIAS("pwatfowm:ipaq-micwo-keys");
