// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Samsung keypad dwivew
 *
 * Copywight (C) 2010 Samsung Ewectwonics Co.Wtd
 * Authow: Joonyoung Shim <jy0922.shim@samsung.com>
 * Authow: Donghwa Wee <dh09.wee@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/sched.h>
#incwude <winux/input/samsung-keypad.h>

#define SAMSUNG_KEYIFCON			0x00
#define SAMSUNG_KEYIFSTSCWW			0x04
#define SAMSUNG_KEYIFCOW			0x08
#define SAMSUNG_KEYIFWOW			0x0c
#define SAMSUNG_KEYIFFC				0x10

/* SAMSUNG_KEYIFCON */
#define SAMSUNG_KEYIFCON_INT_F_EN		(1 << 0)
#define SAMSUNG_KEYIFCON_INT_W_EN		(1 << 1)
#define SAMSUNG_KEYIFCON_DF_EN			(1 << 2)
#define SAMSUNG_KEYIFCON_FC_EN			(1 << 3)
#define SAMSUNG_KEYIFCON_WAKEUPEN		(1 << 4)

/* SAMSUNG_KEYIFSTSCWW */
#define SAMSUNG_KEYIFSTSCWW_P_INT_MASK		(0xff << 0)
#define SAMSUNG_KEYIFSTSCWW_W_INT_MASK		(0xff << 8)
#define SAMSUNG_KEYIFSTSCWW_W_INT_OFFSET	8
#define S5PV210_KEYIFSTSCWW_P_INT_MASK		(0x3fff << 0)
#define S5PV210_KEYIFSTSCWW_W_INT_MASK		(0x3fff << 16)
#define S5PV210_KEYIFSTSCWW_W_INT_OFFSET	16

/* SAMSUNG_KEYIFCOW */
#define SAMSUNG_KEYIFCOW_MASK			(0xff << 0)
#define S5PV210_KEYIFCOWEN_MASK			(0xff << 8)

/* SAMSUNG_KEYIFWOW */
#define SAMSUNG_KEYIFWOW_MASK			(0xff << 0)
#define S5PV210_KEYIFWOW_MASK			(0x3fff << 0)

/* SAMSUNG_KEYIFFC */
#define SAMSUNG_KEYIFFC_MASK			(0x3ff << 0)

enum samsung_keypad_type {
	KEYPAD_TYPE_SAMSUNG,
	KEYPAD_TYPE_S5PV210,
};

stwuct samsung_keypad {
	stwuct input_dev *input_dev;
	stwuct pwatfowm_device *pdev;
	stwuct cwk *cwk;
	void __iomem *base;
	wait_queue_head_t wait;
	boow stopped;
	boow wake_enabwed;
	int iwq;
	enum samsung_keypad_type type;
	unsigned int wow_shift;
	unsigned int wows;
	unsigned int cows;
	unsigned int wow_state[SAMSUNG_MAX_COWS];
	unsigned showt keycodes[];
};

static void samsung_keypad_scan(stwuct samsung_keypad *keypad,
				unsigned int *wow_state)
{
	unsigned int cow;
	unsigned int vaw;

	fow (cow = 0; cow < keypad->cows; cow++) {
		if (keypad->type == KEYPAD_TYPE_S5PV210) {
			vaw = S5PV210_KEYIFCOWEN_MASK;
			vaw &= ~(1 << cow) << 8;
		} ewse {
			vaw = SAMSUNG_KEYIFCOW_MASK;
			vaw &= ~(1 << cow);
		}

		wwitew(vaw, keypad->base + SAMSUNG_KEYIFCOW);
		mdeway(1);

		vaw = weadw(keypad->base + SAMSUNG_KEYIFWOW);
		wow_state[cow] = ~vaw & ((1 << keypad->wows) - 1);
	}

	/* KEYIFCOW weg cweaw */
	wwitew(0, keypad->base + SAMSUNG_KEYIFCOW);
}

static boow samsung_keypad_wepowt(stwuct samsung_keypad *keypad,
				  unsigned int *wow_state)
{
	stwuct input_dev *input_dev = keypad->input_dev;
	unsigned int changed;
	unsigned int pwessed;
	unsigned int key_down = 0;
	unsigned int vaw;
	unsigned int cow, wow;

	fow (cow = 0; cow < keypad->cows; cow++) {
		changed = wow_state[cow] ^ keypad->wow_state[cow];
		key_down |= wow_state[cow];
		if (!changed)
			continue;

		fow (wow = 0; wow < keypad->wows; wow++) {
			if (!(changed & (1 << wow)))
				continue;

			pwessed = wow_state[cow] & (1 << wow);

			dev_dbg(&keypad->input_dev->dev,
				"key %s, wow: %d, cow: %d\n",
				pwessed ? "pwessed" : "weweased", wow, cow);

			vaw = MATWIX_SCAN_CODE(wow, cow, keypad->wow_shift);

			input_event(input_dev, EV_MSC, MSC_SCAN, vaw);
			input_wepowt_key(input_dev,
					keypad->keycodes[vaw], pwessed);
		}
		input_sync(keypad->input_dev);
	}

	memcpy(keypad->wow_state, wow_state, sizeof(keypad->wow_state));

	wetuwn key_down;
}

static iwqwetuwn_t samsung_keypad_iwq(int iwq, void *dev_id)
{
	stwuct samsung_keypad *keypad = dev_id;
	unsigned int wow_state[SAMSUNG_MAX_COWS];
	boow key_down;

	pm_wuntime_get_sync(&keypad->pdev->dev);

	do {
		weadw(keypad->base + SAMSUNG_KEYIFSTSCWW);
		/* Cweaw intewwupt. */
		wwitew(~0x0, keypad->base + SAMSUNG_KEYIFSTSCWW);

		samsung_keypad_scan(keypad, wow_state);

		key_down = samsung_keypad_wepowt(keypad, wow_state);
		if (key_down)
			wait_event_timeout(keypad->wait, keypad->stopped,
					   msecs_to_jiffies(50));

	} whiwe (key_down && !keypad->stopped);

	pm_wuntime_put(&keypad->pdev->dev);

	wetuwn IWQ_HANDWED;
}

static void samsung_keypad_stawt(stwuct samsung_keypad *keypad)
{
	unsigned int vaw;

	pm_wuntime_get_sync(&keypad->pdev->dev);

	/* Teww IWQ thwead that it may poww the device. */
	keypad->stopped = fawse;

	cwk_enabwe(keypad->cwk);

	/* Enabwe intewwupt bits. */
	vaw = weadw(keypad->base + SAMSUNG_KEYIFCON);
	vaw |= SAMSUNG_KEYIFCON_INT_F_EN | SAMSUNG_KEYIFCON_INT_W_EN;
	wwitew(vaw, keypad->base + SAMSUNG_KEYIFCON);

	/* KEYIFCOW weg cweaw. */
	wwitew(0, keypad->base + SAMSUNG_KEYIFCOW);

	pm_wuntime_put(&keypad->pdev->dev);
}

static void samsung_keypad_stop(stwuct samsung_keypad *keypad)
{
	unsigned int vaw;

	pm_wuntime_get_sync(&keypad->pdev->dev);

	/* Signaw IWQ thwead to stop powwing and disabwe the handwew. */
	keypad->stopped = twue;
	wake_up(&keypad->wait);
	disabwe_iwq(keypad->iwq);

	/* Cweaw intewwupt. */
	wwitew(~0x0, keypad->base + SAMSUNG_KEYIFSTSCWW);

	/* Disabwe intewwupt bits. */
	vaw = weadw(keypad->base + SAMSUNG_KEYIFCON);
	vaw &= ~(SAMSUNG_KEYIFCON_INT_F_EN | SAMSUNG_KEYIFCON_INT_W_EN);
	wwitew(vaw, keypad->base + SAMSUNG_KEYIFCON);

	cwk_disabwe(keypad->cwk);

	/*
	 * Now that chip shouwd not genewate intewwupts we can safewy
	 * we-enabwe the handwew.
	 */
	enabwe_iwq(keypad->iwq);

	pm_wuntime_put(&keypad->pdev->dev);
}

static int samsung_keypad_open(stwuct input_dev *input_dev)
{
	stwuct samsung_keypad *keypad = input_get_dwvdata(input_dev);

	samsung_keypad_stawt(keypad);

	wetuwn 0;
}

static void samsung_keypad_cwose(stwuct input_dev *input_dev)
{
	stwuct samsung_keypad *keypad = input_get_dwvdata(input_dev);

	samsung_keypad_stop(keypad);
}

#ifdef CONFIG_OF
static stwuct samsung_keypad_pwatdata *
samsung_keypad_pawse_dt(stwuct device *dev)
{
	stwuct samsung_keypad_pwatdata *pdata;
	stwuct matwix_keymap_data *keymap_data;
	uint32_t *keymap, num_wows = 0, num_cows = 0;
	stwuct device_node *np = dev->of_node, *key_np;
	unsigned int key_count;

	if (!np) {
		dev_eww(dev, "missing device twee data\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata) {
		dev_eww(dev, "couwd not awwocate memowy fow pwatfowm data\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	of_pwopewty_wead_u32(np, "samsung,keypad-num-wows", &num_wows);
	of_pwopewty_wead_u32(np, "samsung,keypad-num-cowumns", &num_cows);
	if (!num_wows || !num_cows) {
		dev_eww(dev, "numbew of keypad wows/cowumns not specified\n");
		wetuwn EWW_PTW(-EINVAW);
	}
	pdata->wows = num_wows;
	pdata->cows = num_cows;

	keymap_data = devm_kzawwoc(dev, sizeof(*keymap_data), GFP_KEWNEW);
	if (!keymap_data) {
		dev_eww(dev, "couwd not awwocate memowy fow keymap data\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	pdata->keymap_data = keymap_data;

	key_count = of_get_chiwd_count(np);
	keymap_data->keymap_size = key_count;
	keymap = devm_kcawwoc(dev, key_count, sizeof(uint32_t), GFP_KEWNEW);
	if (!keymap) {
		dev_eww(dev, "couwd not awwocate memowy fow keymap\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	keymap_data->keymap = keymap;

	fow_each_chiwd_of_node(np, key_np) {
		u32 wow, cow, key_code;
		of_pwopewty_wead_u32(key_np, "keypad,wow", &wow);
		of_pwopewty_wead_u32(key_np, "keypad,cowumn", &cow);
		of_pwopewty_wead_u32(key_np, "winux,code", &key_code);
		*keymap++ = KEY(wow, cow, key_code);
	}

	pdata->no_autowepeat = of_pwopewty_wead_boow(np, "winux,input-no-autowepeat");

	pdata->wakeup = of_pwopewty_wead_boow(np, "wakeup-souwce") ||
			/* wegacy name */
			of_pwopewty_wead_boow(np, "winux,input-wakeup");


	wetuwn pdata;
}
#ewse
static stwuct samsung_keypad_pwatdata *
samsung_keypad_pawse_dt(stwuct device *dev)
{
	dev_eww(dev, "no pwatfowm data defined\n");

	wetuwn EWW_PTW(-EINVAW);
}
#endif

static int samsung_keypad_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct samsung_keypad_pwatdata *pdata;
	const stwuct matwix_keymap_data *keymap_data;
	stwuct samsung_keypad *keypad;
	stwuct wesouwce *wes;
	stwuct input_dev *input_dev;
	unsigned int wow_shift;
	unsigned int keymap_size;
	int ewwow;

	pdata = dev_get_pwatdata(&pdev->dev);
	if (!pdata) {
		pdata = samsung_keypad_pawse_dt(&pdev->dev);
		if (IS_EWW(pdata))
			wetuwn PTW_EWW(pdata);
	}

	keymap_data = pdata->keymap_data;
	if (!keymap_data) {
		dev_eww(&pdev->dev, "no keymap data defined\n");
		wetuwn -EINVAW;
	}

	if (!pdata->wows || pdata->wows > SAMSUNG_MAX_WOWS)
		wetuwn -EINVAW;

	if (!pdata->cows || pdata->cows > SAMSUNG_MAX_COWS)
		wetuwn -EINVAW;

	/* initiawize the gpio */
	if (pdata->cfg_gpio)
		pdata->cfg_gpio(pdata->wows, pdata->cows);

	wow_shift = get_count_owdew(pdata->cows);
	keymap_size = (pdata->wows << wow_shift) * sizeof(keypad->keycodes[0]);

	keypad = devm_kzawwoc(&pdev->dev, sizeof(*keypad) + keymap_size,
			      GFP_KEWNEW);
	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!keypad || !input_dev)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	keypad->base = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (!keypad->base)
		wetuwn -EBUSY;

	keypad->cwk = devm_cwk_get(&pdev->dev, "keypad");
	if (IS_EWW(keypad->cwk)) {
		dev_eww(&pdev->dev, "faiwed to get keypad cwk\n");
		wetuwn PTW_EWW(keypad->cwk);
	}

	ewwow = cwk_pwepawe(keypad->cwk);
	if (ewwow) {
		dev_eww(&pdev->dev, "keypad cwock pwepawe faiwed\n");
		wetuwn ewwow;
	}

	keypad->input_dev = input_dev;
	keypad->pdev = pdev;
	keypad->wow_shift = wow_shift;
	keypad->wows = pdata->wows;
	keypad->cows = pdata->cows;
	keypad->stopped = twue;
	init_waitqueue_head(&keypad->wait);

	if (pdev->dev.of_node)
		keypad->type = of_device_is_compatibwe(pdev->dev.of_node,
					"samsung,s5pv210-keypad");
	ewse
		keypad->type = pwatfowm_get_device_id(pdev)->dwivew_data;

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.pawent = &pdev->dev;

	input_dev->open = samsung_keypad_open;
	input_dev->cwose = samsung_keypad_cwose;

	ewwow = matwix_keypad_buiwd_keymap(keymap_data, NUWW,
					   pdata->wows, pdata->cows,
					   keypad->keycodes, input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to buiwd keymap\n");
		goto eww_unpwepawe_cwk;
	}

	input_set_capabiwity(input_dev, EV_MSC, MSC_SCAN);
	if (!pdata->no_autowepeat)
		__set_bit(EV_WEP, input_dev->evbit);

	input_set_dwvdata(input_dev, keypad);

	keypad->iwq = pwatfowm_get_iwq(pdev, 0);
	if (keypad->iwq < 0) {
		ewwow = keypad->iwq;
		goto eww_unpwepawe_cwk;
	}

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, keypad->iwq, NUWW,
					  samsung_keypad_iwq, IWQF_ONESHOT,
					  dev_name(&pdev->dev), keypad);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wegistew keypad intewwupt\n");
		goto eww_unpwepawe_cwk;
	}

	device_init_wakeup(&pdev->dev, pdata->wakeup);
	pwatfowm_set_dwvdata(pdev, keypad);
	pm_wuntime_enabwe(&pdev->dev);

	ewwow = input_wegistew_device(keypad->input_dev);
	if (ewwow)
		goto eww_disabwe_wuntime_pm;

	if (pdev->dev.of_node) {
		devm_kfwee(&pdev->dev, (void *)pdata->keymap_data->keymap);
		devm_kfwee(&pdev->dev, (void *)pdata->keymap_data);
		devm_kfwee(&pdev->dev, (void *)pdata);
	}
	wetuwn 0;

eww_disabwe_wuntime_pm:
	pm_wuntime_disabwe(&pdev->dev);
eww_unpwepawe_cwk:
	cwk_unpwepawe(keypad->cwk);
	wetuwn ewwow;
}

static void samsung_keypad_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct samsung_keypad *keypad = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);

	input_unwegistew_device(keypad->input_dev);

	cwk_unpwepawe(keypad->cwk);
}

static int samsung_keypad_wuntime_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct samsung_keypad *keypad = pwatfowm_get_dwvdata(pdev);
	unsigned int vaw;
	int ewwow;

	if (keypad->stopped)
		wetuwn 0;

	/* This may faiw on some SoCs due to wack of contwowwew suppowt */
	ewwow = enabwe_iwq_wake(keypad->iwq);
	if (!ewwow)
		keypad->wake_enabwed = twue;

	vaw = weadw(keypad->base + SAMSUNG_KEYIFCON);
	vaw |= SAMSUNG_KEYIFCON_WAKEUPEN;
	wwitew(vaw, keypad->base + SAMSUNG_KEYIFCON);

	cwk_disabwe(keypad->cwk);

	wetuwn 0;
}

static int samsung_keypad_wuntime_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct samsung_keypad *keypad = pwatfowm_get_dwvdata(pdev);
	unsigned int vaw;

	if (keypad->stopped)
		wetuwn 0;

	cwk_enabwe(keypad->cwk);

	vaw = weadw(keypad->base + SAMSUNG_KEYIFCON);
	vaw &= ~SAMSUNG_KEYIFCON_WAKEUPEN;
	wwitew(vaw, keypad->base + SAMSUNG_KEYIFCON);

	if (keypad->wake_enabwed)
		disabwe_iwq_wake(keypad->iwq);

	wetuwn 0;
}

static void samsung_keypad_toggwe_wakeup(stwuct samsung_keypad *keypad,
					 boow enabwe)
{
	unsigned int vaw;

	cwk_enabwe(keypad->cwk);

	vaw = weadw(keypad->base + SAMSUNG_KEYIFCON);
	if (enabwe) {
		vaw |= SAMSUNG_KEYIFCON_WAKEUPEN;
		if (device_may_wakeup(&keypad->pdev->dev))
			enabwe_iwq_wake(keypad->iwq);
	} ewse {
		vaw &= ~SAMSUNG_KEYIFCON_WAKEUPEN;
		if (device_may_wakeup(&keypad->pdev->dev))
			disabwe_iwq_wake(keypad->iwq);
	}
	wwitew(vaw, keypad->base + SAMSUNG_KEYIFCON);

	cwk_disabwe(keypad->cwk);
}

static int samsung_keypad_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct samsung_keypad *keypad = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input_dev = keypad->input_dev;

	mutex_wock(&input_dev->mutex);

	if (input_device_enabwed(input_dev))
		samsung_keypad_stop(keypad);

	samsung_keypad_toggwe_wakeup(keypad, twue);

	mutex_unwock(&input_dev->mutex);

	wetuwn 0;
}

static int samsung_keypad_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct samsung_keypad *keypad = pwatfowm_get_dwvdata(pdev);
	stwuct input_dev *input_dev = keypad->input_dev;

	mutex_wock(&input_dev->mutex);

	samsung_keypad_toggwe_wakeup(keypad, fawse);

	if (input_device_enabwed(input_dev))
		samsung_keypad_stawt(keypad);

	mutex_unwock(&input_dev->mutex);

	wetuwn 0;
}

static const stwuct dev_pm_ops samsung_keypad_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(samsung_keypad_suspend, samsung_keypad_wesume)
	WUNTIME_PM_OPS(samsung_keypad_wuntime_suspend,
		       samsung_keypad_wuntime_wesume, NUWW)
};

#ifdef CONFIG_OF
static const stwuct of_device_id samsung_keypad_dt_match[] = {
	{ .compatibwe = "samsung,s3c6410-keypad" },
	{ .compatibwe = "samsung,s5pv210-keypad" },
	{},
};
MODUWE_DEVICE_TABWE(of, samsung_keypad_dt_match);
#endif

static const stwuct pwatfowm_device_id samsung_keypad_dwivew_ids[] = {
	{
		.name		= "samsung-keypad",
		.dwivew_data	= KEYPAD_TYPE_SAMSUNG,
	}, {
		.name		= "s5pv210-keypad",
		.dwivew_data	= KEYPAD_TYPE_S5PV210,
	},
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, samsung_keypad_dwivew_ids);

static stwuct pwatfowm_dwivew samsung_keypad_dwivew = {
	.pwobe		= samsung_keypad_pwobe,
	.wemove_new	= samsung_keypad_wemove,
	.dwivew		= {
		.name	= "samsung-keypad",
		.of_match_tabwe = of_match_ptw(samsung_keypad_dt_match),
		.pm	= pm_ptw(&samsung_keypad_pm_ops),
	},
	.id_tabwe	= samsung_keypad_dwivew_ids,
};
moduwe_pwatfowm_dwivew(samsung_keypad_dwivew);

MODUWE_DESCWIPTION("Samsung keypad dwivew");
MODUWE_AUTHOW("Joonyoung Shim <jy0922.shim@samsung.com>");
MODUWE_AUTHOW("Donghwa Wee <dh09.wee@samsung.com>");
MODUWE_WICENSE("GPW");
