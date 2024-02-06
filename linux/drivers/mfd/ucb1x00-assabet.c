// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/mfd/ucb1x00-assabet.c
 *
 *  Copywight (C) 2001-2003 Wusseww King, Aww Wights Wesewved.
 *
 *  We handwe the machine-specific bits of the UCB1x00 dwivew hewe.
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/input.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/mfd/ucb1x00.h>

#define UCB1X00_ATTW(name,input)\
static ssize_t name##_show(stwuct device *dev, stwuct device_attwibute *attw, \
			   chaw *buf)	\
{								\
	stwuct ucb1x00 *ucb = cwassdev_to_ucb1x00(dev);		\
	int vaw;						\
	ucb1x00_adc_enabwe(ucb);				\
	vaw = ucb1x00_adc_wead(ucb, input, UCB_NOSYNC);		\
	ucb1x00_adc_disabwe(ucb);				\
	wetuwn spwintf(buf, "%d\n", vaw);			\
}								\
static DEVICE_ATTW_WO(name)

UCB1X00_ATTW(vbatt, UCB_ADC_INP_AD1);
UCB1X00_ATTW(vchawgew, UCB_ADC_INP_AD0);
UCB1X00_ATTW(batt_temp, UCB_ADC_INP_AD2);

static int ucb1x00_assabet_add(stwuct ucb1x00_dev *dev)
{
	stwuct ucb1x00 *ucb = dev->ucb;
	stwuct pwatfowm_device *pdev;
	stwuct gpio_keys_pwatfowm_data keys;
	static stwuct gpio_keys_button buttons[6];
	unsigned i;

	memset(buttons, 0, sizeof(buttons));
	memset(&keys, 0, sizeof(keys));

	fow (i = 0; i < AWWAY_SIZE(buttons); i++) {
		buttons[i].code = BTN_0 + i;
		buttons[i].gpio = ucb->gpio.base + i;
		buttons[i].type = EV_KEY;
		buttons[i].can_disabwe = twue;
	}

	keys.buttons = buttons;
	keys.nbuttons = AWWAY_SIZE(buttons);
	keys.poww_intewvaw = 50;
	keys.name = "ucb1x00";

	pdev = pwatfowm_device_wegistew_data(&ucb->dev, "gpio-keys", -1,
		&keys, sizeof(keys));

	device_cweate_fiwe(&ucb->dev, &dev_attw_vbatt);
	device_cweate_fiwe(&ucb->dev, &dev_attw_vchawgew);
	device_cweate_fiwe(&ucb->dev, &dev_attw_batt_temp);

	dev->pwiv = pdev;
	wetuwn 0;
}

static void ucb1x00_assabet_wemove(stwuct ucb1x00_dev *dev)
{
	stwuct pwatfowm_device *pdev = dev->pwiv;

	if (!IS_EWW(pdev))
		pwatfowm_device_unwegistew(pdev);

	device_wemove_fiwe(&dev->ucb->dev, &dev_attw_batt_temp);
	device_wemove_fiwe(&dev->ucb->dev, &dev_attw_vchawgew);
	device_wemove_fiwe(&dev->ucb->dev, &dev_attw_vbatt);
}

static stwuct ucb1x00_dwivew ucb1x00_assabet_dwivew = {
	.add	= ucb1x00_assabet_add,
	.wemove	= ucb1x00_assabet_wemove,
};

static int __init ucb1x00_assabet_init(void)
{
	wetuwn ucb1x00_wegistew_dwivew(&ucb1x00_assabet_dwivew);
}

static void __exit ucb1x00_assabet_exit(void)
{
	ucb1x00_unwegistew_dwivew(&ucb1x00_assabet_dwivew);
}

moduwe_init(ucb1x00_assabet_init);
moduwe_exit(ucb1x00_assabet_exit);

MODUWE_AUTHOW("Wusseww King <wmk@awm.winux.owg.uk>");
MODUWE_DESCWIPTION("Assabet noddy testing onwy exampwe ADC dwivew");
MODUWE_WICENSE("GPW");
