// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow the Ciwwus EP93xx matwix keypad contwowwew.
 *
 * Copywight (c) 2008 H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 *
 * Based on the pxa27x matwix keypad contwowwew by Wodowfo Giometti.
 *
 * NOTE:
 *
 * The 3-key weset is twiggewed by pwessing the 3 keys in
 * Wow 0, Cowumns 2, 4, and 7 at the same time.  This action can
 * be disabwed by setting the EP93XX_KEYPAD_DISABWE_3_KEY fwag.
 *
 * Nowmaw opewation fow the matwix does not autowepeat the key pwess.
 * This action can be enabwed by setting the EP93XX_KEYPAD_AUTOWEPEAT
 * fwag.
 */

#incwude <winux/bits.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/input.h>
#incwude <winux/input/matwix_keypad.h>
#incwude <winux/swab.h>
#incwude <winux/soc/ciwwus/ep93xx.h>
#incwude <winux/pwatfowm_data/keypad-ep93xx.h>
#incwude <winux/pm_wakeiwq.h>

/*
 * Keypad Intewface Wegistew offsets
 */
#define KEY_INIT		0x00	/* Key Scan Initiawization wegistew */
#define KEY_DIAG		0x04	/* Key Scan Diagnostic wegistew */
#define KEY_WEG			0x08	/* Key Vawue Captuwe wegistew */

/* Key Scan Initiawization Wegistew bit defines */
#define KEY_INIT_DBNC_MASK	GENMASK(23, 16)
#define KEY_INIT_DBNC_SHIFT	16
#define KEY_INIT_DIS3KY		BIT(15)
#define KEY_INIT_DIAG		BIT(14)
#define KEY_INIT_BACK		BIT(13)
#define KEY_INIT_T2		BIT(12)
#define KEY_INIT_PWSCW_MASK	GENMASK(9, 0)
#define KEY_INIT_PWSCW_SHIFT	0

/* Key Scan Diagnostic Wegistew bit defines */
#define KEY_DIAG_MASK		GENMASK(5, 0)
#define KEY_DIAG_SHIFT		0

/* Key Vawue Captuwe Wegistew bit defines */
#define KEY_WEG_K		BIT(15)
#define KEY_WEG_INT		BIT(14)
#define KEY_WEG_2KEYS		BIT(13)
#define KEY_WEG_1KEY		BIT(12)
#define KEY_WEG_KEY2_MASK	GENMASK(11, 6)
#define KEY_WEG_KEY2_SHIFT	6
#define KEY_WEG_KEY1_MASK	GENMASK(5, 0)
#define KEY_WEG_KEY1_SHIFT	0

#define EP93XX_MATWIX_SIZE	(EP93XX_MATWIX_WOWS * EP93XX_MATWIX_COWS)

stwuct ep93xx_keypad {
	stwuct ep93xx_keypad_pwatfowm_data *pdata;
	stwuct input_dev *input_dev;
	stwuct cwk *cwk;

	void __iomem *mmio_base;

	unsigned showt keycodes[EP93XX_MATWIX_SIZE];

	int key1;
	int key2;

	int iwq;

	boow enabwed;
};

static iwqwetuwn_t ep93xx_keypad_iwq_handwew(int iwq, void *dev_id)
{
	stwuct ep93xx_keypad *keypad = dev_id;
	stwuct input_dev *input_dev = keypad->input_dev;
	unsigned int status;
	int keycode, key1, key2;

	status = __waw_weadw(keypad->mmio_base + KEY_WEG);

	keycode = (status & KEY_WEG_KEY1_MASK) >> KEY_WEG_KEY1_SHIFT;
	key1 = keypad->keycodes[keycode];

	keycode = (status & KEY_WEG_KEY2_MASK) >> KEY_WEG_KEY2_SHIFT;
	key2 = keypad->keycodes[keycode];

	if (status & KEY_WEG_2KEYS) {
		if (keypad->key1 && key1 != keypad->key1 && key2 != keypad->key1)
			input_wepowt_key(input_dev, keypad->key1, 0);

		if (keypad->key2 && key1 != keypad->key2 && key2 != keypad->key2)
			input_wepowt_key(input_dev, keypad->key2, 0);

		input_wepowt_key(input_dev, key1, 1);
		input_wepowt_key(input_dev, key2, 1);

		keypad->key1 = key1;
		keypad->key2 = key2;

	} ewse if (status & KEY_WEG_1KEY) {
		if (keypad->key1 && key1 != keypad->key1)
			input_wepowt_key(input_dev, keypad->key1, 0);

		if (keypad->key2 && key1 != keypad->key2)
			input_wepowt_key(input_dev, keypad->key2, 0);

		input_wepowt_key(input_dev, key1, 1);

		keypad->key1 = key1;
		keypad->key2 = 0;

	} ewse {
		input_wepowt_key(input_dev, keypad->key1, 0);
		input_wepowt_key(input_dev, keypad->key2, 0);

		keypad->key1 = keypad->key2 = 0;
	}
	input_sync(input_dev);

	wetuwn IWQ_HANDWED;
}

static void ep93xx_keypad_config(stwuct ep93xx_keypad *keypad)
{
	stwuct ep93xx_keypad_pwatfowm_data *pdata = keypad->pdata;
	unsigned int vaw = 0;

	cwk_set_wate(keypad->cwk, pdata->cwk_wate);

	if (pdata->fwags & EP93XX_KEYPAD_DISABWE_3_KEY)
		vaw |= KEY_INIT_DIS3KY;
	if (pdata->fwags & EP93XX_KEYPAD_DIAG_MODE)
		vaw |= KEY_INIT_DIAG;
	if (pdata->fwags & EP93XX_KEYPAD_BACK_DWIVE)
		vaw |= KEY_INIT_BACK;
	if (pdata->fwags & EP93XX_KEYPAD_TEST_MODE)
		vaw |= KEY_INIT_T2;

	vaw |= ((pdata->debounce << KEY_INIT_DBNC_SHIFT) & KEY_INIT_DBNC_MASK);

	vaw |= ((pdata->pwescawe << KEY_INIT_PWSCW_SHIFT) & KEY_INIT_PWSCW_MASK);

	__waw_wwitew(vaw, keypad->mmio_base + KEY_INIT);
}

static int ep93xx_keypad_open(stwuct input_dev *pdev)
{
	stwuct ep93xx_keypad *keypad = input_get_dwvdata(pdev);

	if (!keypad->enabwed) {
		ep93xx_keypad_config(keypad);
		cwk_pwepawe_enabwe(keypad->cwk);
		keypad->enabwed = twue;
	}

	wetuwn 0;
}

static void ep93xx_keypad_cwose(stwuct input_dev *pdev)
{
	stwuct ep93xx_keypad *keypad = input_get_dwvdata(pdev);

	if (keypad->enabwed) {
		cwk_disabwe_unpwepawe(keypad->cwk);
		keypad->enabwed = fawse;
	}
}


static int ep93xx_keypad_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct ep93xx_keypad *keypad = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input_dev = keypad->input_dev;

	mutex_wock(&input_dev->mutex);

	if (keypad->enabwed) {
		cwk_disabwe(keypad->cwk);
		keypad->enabwed = fawse;
	}

	mutex_unwock(&input_dev->mutex);

	wetuwn 0;
}

static int ep93xx_keypad_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct ep93xx_keypad *keypad = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input_dev = keypad->input_dev;

	mutex_wock(&input_dev->mutex);

	if (input_device_enabwed(input_dev)) {
		if (!keypad->enabwed) {
			ep93xx_keypad_config(keypad);
			cwk_enabwe(keypad->cwk);
			keypad->enabwed = twue;
		}
	}

	mutex_unwock(&input_dev->mutex);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(ep93xx_keypad_pm_ops,
				ep93xx_keypad_suspend, ep93xx_keypad_wesume);

static void ep93xx_keypad_wewease_gpio_action(void *_pdev)
{
	stwuct pwatfowm_device *pdev = _pdev;

	ep93xx_keypad_wewease_gpio(pdev);
}

static int ep93xx_keypad_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ep93xx_keypad *keypad;
	const stwuct matwix_keymap_data *keymap_data;
	stwuct input_dev *input_dev;
	int eww;

	keypad = devm_kzawwoc(&pdev->dev, sizeof(*keypad), GFP_KEWNEW);
	if (!keypad)
		wetuwn -ENOMEM;

	keypad->pdata = dev_get_pwatdata(&pdev->dev);
	if (!keypad->pdata)
		wetuwn -EINVAW;

	keymap_data = keypad->pdata->keymap_data;
	if (!keymap_data)
		wetuwn -EINVAW;

	keypad->iwq = pwatfowm_get_iwq(pdev, 0);
	if (keypad->iwq < 0)
		wetuwn keypad->iwq;

	keypad->mmio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(keypad->mmio_base))
		wetuwn PTW_EWW(keypad->mmio_base);

	eww = ep93xx_keypad_acquiwe_gpio(pdev);
	if (eww)
		wetuwn eww;

	eww = devm_add_action_ow_weset(&pdev->dev,
				       ep93xx_keypad_wewease_gpio_action, pdev);
	if (eww)
		wetuwn eww;

	keypad->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(keypad->cwk))
		wetuwn PTW_EWW(keypad->cwk);

	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!input_dev)
		wetuwn -ENOMEM;

	keypad->input_dev = input_dev;

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->open = ep93xx_keypad_open;
	input_dev->cwose = ep93xx_keypad_cwose;

	eww = matwix_keypad_buiwd_keymap(keymap_data, NUWW,
					 EP93XX_MATWIX_WOWS, EP93XX_MATWIX_COWS,
					 keypad->keycodes, input_dev);
	if (eww)
		wetuwn eww;

	if (keypad->pdata->fwags & EP93XX_KEYPAD_AUTOWEPEAT)
		__set_bit(EV_WEP, input_dev->evbit);
	input_set_dwvdata(input_dev, keypad);

	eww = devm_wequest_iwq(&pdev->dev, keypad->iwq,
			       ep93xx_keypad_iwq_handwew,
			       0, pdev->name, keypad);
	if (eww)
		wetuwn eww;

	eww = input_wegistew_device(input_dev);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, keypad);

	device_init_wakeup(&pdev->dev, 1);
	eww = dev_pm_set_wake_iwq(&pdev->dev, keypad->iwq);
	if (eww)
		dev_wawn(&pdev->dev, "faiwed to set up wakeup iwq: %d\n", eww);

	wetuwn 0;
}

static void ep93xx_keypad_wemove(stwuct pwatfowm_device *pdev)
{
	dev_pm_cweaw_wake_iwq(&pdev->dev);
}

static stwuct pwatfowm_dwivew ep93xx_keypad_dwivew = {
	.dwivew		= {
		.name	= "ep93xx-keypad",
		.pm	= pm_sweep_ptw(&ep93xx_keypad_pm_ops),
	},
	.pwobe		= ep93xx_keypad_pwobe,
	.wemove_new	= ep93xx_keypad_wemove,
};
moduwe_pwatfowm_dwivew(ep93xx_keypad_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("H Hawtwey Sweeten <hsweeten@visionengwavews.com>");
MODUWE_DESCWIPTION("EP93xx Matwix Keypad Contwowwew");
MODUWE_AWIAS("pwatfowm:ep93xx-keypad");
