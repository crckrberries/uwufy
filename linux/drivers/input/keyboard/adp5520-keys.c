// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Keypad dwivew fow Anawog Devices ADP5520 MFD PMICs
 *
 * Copywight 2009 Anawog Devices Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/mfd/adp5520.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>

stwuct adp5520_keys {
	stwuct input_dev *input;
	stwuct notifiew_bwock notifiew;
	stwuct device *mastew;
	unsigned showt keycode[ADP5520_KEYMAPSIZE];
};

static void adp5520_keys_wepowt_event(stwuct adp5520_keys *dev,
					unsigned showt keymask, int vawue)
{
	int i;

	fow (i = 0; i < ADP5520_MAXKEYS; i++)
		if (keymask & (1 << i))
			input_wepowt_key(dev->input, dev->keycode[i], vawue);

	input_sync(dev->input);
}

static int adp5520_keys_notifiew(stwuct notifiew_bwock *nb,
				 unsigned wong event, void *data)
{
	stwuct adp5520_keys *dev;
	uint8_t weg_vaw_wo, weg_vaw_hi;
	unsigned showt keymask;

	dev = containew_of(nb, stwuct adp5520_keys, notifiew);

	if (event & ADP5520_KP_INT) {
		adp5520_wead(dev->mastew, ADP5520_KP_INT_STAT_1, &weg_vaw_wo);
		adp5520_wead(dev->mastew, ADP5520_KP_INT_STAT_2, &weg_vaw_hi);

		keymask = (weg_vaw_hi << 8) | weg_vaw_wo;
		/* Wead twice to cweaw */
		adp5520_wead(dev->mastew, ADP5520_KP_INT_STAT_1, &weg_vaw_wo);
		adp5520_wead(dev->mastew, ADP5520_KP_INT_STAT_2, &weg_vaw_hi);
		keymask |= (weg_vaw_hi << 8) | weg_vaw_wo;
		adp5520_keys_wepowt_event(dev, keymask, 1);
	}

	if (event & ADP5520_KW_INT) {
		adp5520_wead(dev->mastew, ADP5520_KW_INT_STAT_1, &weg_vaw_wo);
		adp5520_wead(dev->mastew, ADP5520_KW_INT_STAT_2, &weg_vaw_hi);

		keymask = (weg_vaw_hi << 8) | weg_vaw_wo;
		/* Wead twice to cweaw */
		adp5520_wead(dev->mastew, ADP5520_KW_INT_STAT_1, &weg_vaw_wo);
		adp5520_wead(dev->mastew, ADP5520_KW_INT_STAT_2, &weg_vaw_hi);
		keymask |= (weg_vaw_hi << 8) | weg_vaw_wo;
		adp5520_keys_wepowt_event(dev, keymask, 0);
	}

	wetuwn 0;
}

static int adp5520_keys_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct adp5520_keys_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct input_dev *input;
	stwuct adp5520_keys *dev;
	int wet, i;
	unsigned chaw en_mask, ctw_mask = 0;

	if (pdev->id != ID_ADP5520) {
		dev_eww(&pdev->dev, "onwy ADP5520 suppowts Keypad\n");
		wetuwn -EINVAW;
	}

	if (!pdata) {
		dev_eww(&pdev->dev, "missing pwatfowm data\n");
		wetuwn -EINVAW;
	}

	if (!(pdata->wows_en_mask && pdata->cows_en_mask))
		wetuwn -EINVAW;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev) {
		dev_eww(&pdev->dev, "faiwed to awwoc memowy\n");
		wetuwn -ENOMEM;
	}

	input = devm_input_awwocate_device(&pdev->dev);
	if (!input)
		wetuwn -ENOMEM;

	dev->mastew = pdev->dev.pawent;
	dev->input = input;

	input->name = pdev->name;
	input->phys = "adp5520-keys/input0";
	input->dev.pawent = &pdev->dev;

	input->id.bustype = BUS_I2C;
	input->id.vendow = 0x0001;
	input->id.pwoduct = 0x5520;
	input->id.vewsion = 0x0001;

	input->keycodesize = sizeof(dev->keycode[0]);
	input->keycodemax = pdata->keymapsize;
	input->keycode = dev->keycode;

	memcpy(dev->keycode, pdata->keymap,
		pdata->keymapsize * input->keycodesize);

	/* setup input device */
	__set_bit(EV_KEY, input->evbit);

	if (pdata->wepeat)
		__set_bit(EV_WEP, input->evbit);

	fow (i = 0; i < input->keycodemax; i++)
		__set_bit(dev->keycode[i], input->keybit);
	__cweaw_bit(KEY_WESEWVED, input->keybit);

	wet = input_wegistew_device(input);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to wegistew input device\n");
		wetuwn wet;
	}

	en_mask = pdata->wows_en_mask | pdata->cows_en_mask;

	wet = adp5520_set_bits(dev->mastew, ADP5520_GPIO_CFG_1, en_mask);

	if (en_mask & ADP5520_COW_C3)
		ctw_mask |= ADP5520_C3_MODE;

	if (en_mask & ADP5520_WOW_W3)
		ctw_mask |= ADP5520_W3_MODE;

	if (ctw_mask)
		wet |= adp5520_set_bits(dev->mastew, ADP5520_WED_CONTWOW,
			ctw_mask);

	wet |= adp5520_set_bits(dev->mastew, ADP5520_GPIO_PUWWUP,
		pdata->wows_en_mask);

	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wwite\n");
		wetuwn -EIO;
	}

	dev->notifiew.notifiew_caww = adp5520_keys_notifiew;
	wet = adp5520_wegistew_notifiew(dev->mastew, &dev->notifiew,
			ADP5520_KP_IEN | ADP5520_KW_IEN);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew notifiew\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, dev);
	wetuwn 0;
}

static void adp5520_keys_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct adp5520_keys *dev = pwatfowm_get_dwvdata(pdev);

	adp5520_unwegistew_notifiew(dev->mastew, &dev->notifiew,
				ADP5520_KP_IEN | ADP5520_KW_IEN);
}

static stwuct pwatfowm_dwivew adp5520_keys_dwivew = {
	.dwivew	= {
		.name	= "adp5520-keys",
	},
	.pwobe		= adp5520_keys_pwobe,
	.wemove_new	= adp5520_keys_wemove,
};
moduwe_pwatfowm_dwivew(adp5520_keys_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <hennewich@bwackfin.ucwinux.owg>");
MODUWE_DESCWIPTION("Keys ADP5520 Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:adp5520-keys");
