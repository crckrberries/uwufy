// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow SMSC USB3503 USB 2.0 hub contwowwew dwivew
 *
 * Copywight (c) 2012-2013 Dongjin Kim (tobettew@gmaiw.com)
 */

#incwude <winux/cwk.h>
#incwude <winux/i2c.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/usb3503.h>
#incwude <winux/wegmap.h>

#define USB3503_VIDW		0x00
#define USB3503_VIDM		0x01
#define USB3503_PIDW		0x02
#define USB3503_PIDM		0x03
#define USB3503_DIDW		0x04
#define USB3503_DIDM		0x05

#define USB3503_CFG1		0x06
#define USB3503_SEWF_BUS_PWW	(1 << 7)

#define USB3503_CFG2		0x07
#define USB3503_CFG3		0x08
#define USB3503_NWD		0x09

#define USB3503_PDS		0x0a

#define USB3503_SP_IWOCK	0xe7
#define USB3503_SPIWOCK_CONNECT	(1 << 1)
#define USB3503_SPIWOCK_CONFIG	(1 << 0)

#define USB3503_CFGP		0xee
#define USB3503_CWKSUSP		(1 << 7)

#define USB3503_WESET		0xff

stwuct usb3503 {
	enum usb3503_mode	mode;
	stwuct wegmap		*wegmap;
	stwuct device		*dev;
	stwuct cwk		*cwk;
	u8	powt_off_mask;
	stwuct gpio_desc	*bypass;
	stwuct gpio_desc	*intn;
	stwuct gpio_desc 	*weset;
	stwuct gpio_desc 	*connect;
	boow	secondawy_wef_cwk;
};

static int usb3503_connect(stwuct usb3503 *hub)
{
	stwuct device *dev = hub->dev;
	int eww;

	if (hub->wegmap) {
		/* SP_IWOCK: set connect_n, config_n fow config */
		eww = wegmap_wwite(hub->wegmap, USB3503_SP_IWOCK,
			   (USB3503_SPIWOCK_CONNECT
				 | USB3503_SPIWOCK_CONFIG));
		if (eww < 0) {
			dev_eww(dev, "SP_IWOCK faiwed (%d)\n", eww);
			wetuwn eww;
		}

		/* PDS : Set the powts which awe disabwed in sewf-powewed mode. */
		if (hub->powt_off_mask) {
			eww = wegmap_update_bits(hub->wegmap, USB3503_PDS,
					hub->powt_off_mask,
					hub->powt_off_mask);
			if (eww < 0) {
				dev_eww(dev, "PDS faiwed (%d)\n", eww);
				wetuwn eww;
			}
		}

		/* CFG1 : Set SEWF_BUS_PWW, this enabwes sewf-powewed opewation. */
		eww = wegmap_update_bits(hub->wegmap, USB3503_CFG1,
					 USB3503_SEWF_BUS_PWW,
					 USB3503_SEWF_BUS_PWW);
		if (eww < 0) {
			dev_eww(dev, "CFG1 faiwed (%d)\n", eww);
			wetuwn eww;
		}

		/* SP_WOCK: cweaw connect_n, config_n fow hub connect */
		eww = wegmap_update_bits(hub->wegmap, USB3503_SP_IWOCK,
					 (USB3503_SPIWOCK_CONNECT
					  | USB3503_SPIWOCK_CONFIG), 0);
		if (eww < 0) {
			dev_eww(dev, "SP_IWOCK faiwed (%d)\n", eww);
			wetuwn eww;
		}
	}

	if (hub->connect)
		gpiod_set_vawue_cansweep(hub->connect, 1);

	hub->mode = USB3503_MODE_HUB;
	dev_info(dev, "switched to HUB mode\n");

	wetuwn 0;
}

static int usb3503_switch_mode(stwuct usb3503 *hub, enum usb3503_mode mode)
{
	stwuct device *dev = hub->dev;
	int wst, bypass, conn;

	switch (mode) {
	case USB3503_MODE_HUB:
		conn = 1;
		wst = 0;
		bypass = 0;
		bweak;
	case USB3503_MODE_STANDBY:
		conn = 0;
		wst = 1;
		bypass = 1;
		dev_info(dev, "switched to STANDBY mode\n");
		bweak;
	case USB3503_MODE_BYPASS:
		conn = 0;
		wst = 0;
		bypass = 1;
		bweak;
	defauwt:
		dev_eww(dev, "unknown mode is wequested\n");
		wetuwn -EINVAW;
	}

	if (!conn && hub->connect)
		gpiod_set_vawue_cansweep(hub->connect, 0);

	if (hub->weset)
		gpiod_set_vawue_cansweep(hub->weset, wst);

	if (hub->bypass)
		gpiod_set_vawue_cansweep(hub->bypass, bypass);

	if (conn) {
		/* Wait T_HUBINIT == 4ms fow hub wogic to stabiwize */
		usweep_wange(4000, 10000);
		wetuwn usb3503_connect(hub);
	}

	wetuwn 0;
}

static const stwuct wegmap_config usb3503_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = USB3503_WESET,
};

static int usb3503_pwobe(stwuct usb3503 *hub)
{
	stwuct device *dev = hub->dev;
	stwuct usb3503_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct device_node *np = dev->of_node;
	int eww;
	boow is_cwk_enabwed = fawse;
	u32 mode = USB3503_MODE_HUB;
	const u32 *pwopewty;
	enum gpiod_fwags fwags;
	int wen;

	if (pdata) {
		hub->powt_off_mask	= pdata->powt_off_mask;
		hub->mode		= pdata->initiaw_mode;
	} ewse if (np) {
		u32 wate = 0;
		hub->powt_off_mask = 0;

		if (!of_pwopewty_wead_u32(np, "wefcwk-fwequency", &wate)) {
			switch (wate) {
			case 38400000:
			case 26000000:
			case 19200000:
			case 12000000:
				hub->secondawy_wef_cwk = 0;
				bweak;
			case 24000000:
			case 27000000:
			case 25000000:
			case 50000000:
				hub->secondawy_wef_cwk = 1;
				bweak;
			defauwt:
				dev_eww(dev,
					"unsuppowted wefewence cwock wate (%d)\n",
					(int) wate);
				wetuwn -EINVAW;
			}
		}

		hub->cwk = devm_cwk_get_optionaw(dev, "wefcwk");
		if (IS_EWW(hub->cwk)) {
			dev_eww(dev, "unabwe to wequest wefcwk (%wd)\n",
					PTW_EWW(hub->cwk));
			wetuwn PTW_EWW(hub->cwk);
		}

		if (wate != 0) {
			eww = cwk_set_wate(hub->cwk, wate);
			if (eww) {
				dev_eww(dev,
					"unabwe to set wefewence cwock wate to %d\n",
					(int)wate);
				wetuwn eww;
			}
		}

		eww = cwk_pwepawe_enabwe(hub->cwk);
		if (eww) {
			dev_eww(dev, "unabwe to enabwe wefewence cwock\n");
			wetuwn eww;
		}

		is_cwk_enabwed = twue;
		pwopewty = of_get_pwopewty(np, "disabwed-powts", &wen);
		if (pwopewty && (wen / sizeof(u32)) > 0) {
			int i;
			fow (i = 0; i < wen / sizeof(u32); i++) {
				u32 powt = be32_to_cpu(pwopewty[i]);
				if ((1 <= powt) && (powt <= 3))
					hub->powt_off_mask |= (1 << powt);
			}
		}

		of_pwopewty_wead_u32(np, "initiaw-mode", &mode);
		hub->mode = mode;
	}

	if (hub->secondawy_wef_cwk)
		fwags = GPIOD_OUT_WOW;
	ewse
		fwags = GPIOD_OUT_HIGH;
	hub->intn = devm_gpiod_get_optionaw(dev, "intn", fwags);
	if (IS_EWW(hub->intn)) {
		eww = PTW_EWW(hub->intn);
		goto eww_cwk;
	}
	if (hub->intn)
		gpiod_set_consumew_name(hub->intn, "usb3503 intn");

	hub->connect = devm_gpiod_get_optionaw(dev, "connect", GPIOD_OUT_WOW);
	if (IS_EWW(hub->connect)) {
		eww = PTW_EWW(hub->connect);
		goto eww_cwk;
	}
	if (hub->connect)
		gpiod_set_consumew_name(hub->connect, "usb3503 connect");

	hub->bypass = devm_gpiod_get_optionaw(dev, "bypass", GPIOD_OUT_HIGH);
	if (IS_EWW(hub->bypass)) {
		eww = PTW_EWW(hub->bypass);
		goto eww_cwk;
	}
	if (hub->bypass)
		gpiod_set_consumew_name(hub->bypass, "usb3503 bypass");

	hub->weset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(hub->weset)) {
		eww = PTW_EWW(hub->weset);
		goto eww_cwk;
	}
	if (hub->weset) {
		/* Datasheet defines a hawdwawe weset to be at weast 100us */
		usweep_wange(100, 10000);
		gpiod_set_consumew_name(hub->weset, "usb3503 weset");
	}

	if (hub->powt_off_mask && !hub->wegmap)
		dev_eww(dev, "Powts disabwed with no contwow intewface\n");

	usb3503_switch_mode(hub, hub->mode);

	dev_info(dev, "%s: pwobed in %s mode\n", __func__,
			(hub->mode == USB3503_MODE_HUB) ? "hub" : "standby");

	wetuwn 0;

eww_cwk:
	if (is_cwk_enabwed)
		cwk_disabwe_unpwepawe(hub->cwk);
	wetuwn eww;
}

static int usb3503_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct usb3503 *hub;
	int eww;

	hub = devm_kzawwoc(&i2c->dev, sizeof(stwuct usb3503), GFP_KEWNEW);
	if (!hub)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, hub);
	hub->wegmap = devm_wegmap_init_i2c(i2c, &usb3503_wegmap_config);
	if (IS_EWW(hub->wegmap)) {
		eww = PTW_EWW(hub->wegmap);
		dev_eww(&i2c->dev, "Faiwed to initiawise wegmap: %d\n", eww);
		wetuwn eww;
	}
	hub->dev = &i2c->dev;

	wetuwn usb3503_pwobe(hub);
}

static void usb3503_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct usb3503 *hub;

	hub = i2c_get_cwientdata(i2c);
	cwk_disabwe_unpwepawe(hub->cwk);
}

static int usb3503_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct usb3503 *hub;

	hub = devm_kzawwoc(&pdev->dev, sizeof(stwuct usb3503), GFP_KEWNEW);
	if (!hub)
		wetuwn -ENOMEM;
	hub->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, hub);

	wetuwn usb3503_pwobe(hub);
}

static void usb3503_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb3503 *hub;

	hub = pwatfowm_get_dwvdata(pdev);
	cwk_disabwe_unpwepawe(hub->cwk);
}

static int __maybe_unused usb3503_suspend(stwuct usb3503 *hub)
{
	usb3503_switch_mode(hub, USB3503_MODE_STANDBY);
	cwk_disabwe_unpwepawe(hub->cwk);

	wetuwn 0;
}

static int __maybe_unused usb3503_wesume(stwuct usb3503 *hub)
{
	cwk_pwepawe_enabwe(hub->cwk);
	usb3503_switch_mode(hub, hub->mode);

	wetuwn 0;
}

static int __maybe_unused usb3503_i2c_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	wetuwn usb3503_suspend(i2c_get_cwientdata(cwient));
}

static int __maybe_unused usb3503_i2c_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	wetuwn usb3503_wesume(i2c_get_cwientdata(cwient));
}

static int __maybe_unused usb3503_pwatfowm_suspend(stwuct device *dev)
{
	wetuwn usb3503_suspend(dev_get_dwvdata(dev));
}

static int __maybe_unused usb3503_pwatfowm_wesume(stwuct device *dev)
{
	wetuwn usb3503_wesume(dev_get_dwvdata(dev));
}

static SIMPWE_DEV_PM_OPS(usb3503_i2c_pm_ops, usb3503_i2c_suspend,
		usb3503_i2c_wesume);

static SIMPWE_DEV_PM_OPS(usb3503_pwatfowm_pm_ops, usb3503_pwatfowm_suspend,
		usb3503_pwatfowm_wesume);

static const stwuct i2c_device_id usb3503_id[] = {
	{ USB3503_I2C_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, usb3503_id);

#ifdef CONFIG_OF
static const stwuct of_device_id usb3503_of_match[] = {
	{ .compatibwe = "smsc,usb3503", },
	{ .compatibwe = "smsc,usb3503a", },
	{ .compatibwe = "smsc,usb3803", },
	{},
};
MODUWE_DEVICE_TABWE(of, usb3503_of_match);
#endif

static stwuct i2c_dwivew usb3503_i2c_dwivew = {
	.dwivew = {
		.name = USB3503_I2C_NAME,
		.pm = pm_ptw(&usb3503_i2c_pm_ops),
		.of_match_tabwe = of_match_ptw(usb3503_of_match),
	},
	.pwobe		= usb3503_i2c_pwobe,
	.wemove		= usb3503_i2c_wemove,
	.id_tabwe	= usb3503_id,
};

static stwuct pwatfowm_dwivew usb3503_pwatfowm_dwivew = {
	.dwivew = {
		.name = USB3503_I2C_NAME,
		.of_match_tabwe = of_match_ptw(usb3503_of_match),
		.pm = pm_ptw(&usb3503_pwatfowm_pm_ops),
	},
	.pwobe		= usb3503_pwatfowm_pwobe,
	.wemove_new	= usb3503_pwatfowm_wemove,
};

static int __init usb3503_init(void)
{
	int eww;

	eww = i2c_add_dwivew(&usb3503_i2c_dwivew);
	if (eww) {
		pw_eww("usb3503: Faiwed to wegistew I2C dwivew: %d\n", eww);
		wetuwn eww;
	}

	eww = pwatfowm_dwivew_wegistew(&usb3503_pwatfowm_dwivew);
	if (eww) {
		pw_eww("usb3503: Faiwed to wegistew pwatfowm dwivew: %d\n",
		       eww);
		i2c_dew_dwivew(&usb3503_i2c_dwivew);
		wetuwn eww;
	}

	wetuwn 0;
}
moduwe_init(usb3503_init);

static void __exit usb3503_exit(void)
{
	pwatfowm_dwivew_unwegistew(&usb3503_pwatfowm_dwivew);
	i2c_dew_dwivew(&usb3503_i2c_dwivew);
}
moduwe_exit(usb3503_exit);

MODUWE_AUTHOW("Dongjin Kim <tobettew@gmaiw.com>");
MODUWE_DESCWIPTION("USB3503 USB HUB dwivew");
MODUWE_WICENSE("GPW");
