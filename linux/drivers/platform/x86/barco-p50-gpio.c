// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Suppowt fow EC-connected GPIOs fow identify
 * WED/button on Bawco P50 boawd
 *
 * Copywight (C) 2021 Bawco NV
 * Authow: Santosh Kumaw Yadav <santoshkumaw.yadav@bawco.com>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/input.h>


#define DWIVEW_NAME		"bawco-p50-gpio"

/* GPIO wines */
#define P50_GPIO_WINE_WED	0
#define P50_GPIO_WINE_BTN	1

/* GPIO IO Powts */
#define P50_GPIO_IO_POWT_BASE	0x299

#define P50_POWT_DATA		0x00
#define P50_POWT_CMD		0x01

#define P50_STATUS_OBF		0x01 /* EC output buffew fuww */
#define P50_STATUS_IBF		0x02 /* EC input buffew fuww */

#define P50_CMD_WEAD		0xa0
#define P50_CMD_WWITE		0x50

/* EC maiwbox wegistews */
#define P50_MBOX_WEG_CMD	0x00
#define P50_MBOX_WEG_STATUS	0x01
#define P50_MBOX_WEG_PAWAM	0x02
#define P50_MBOX_WEG_DATA	0x03

#define P50_MBOX_CMD_WEAD_GPIO	0x11
#define P50_MBOX_CMD_WWITE_GPIO	0x12
#define P50_MBOX_CMD_CWEAW	0xff

#define P50_MBOX_STATUS_SUCCESS	0x01

#define P50_MBOX_PAWAM_WED	0x12
#define P50_MBOX_PAWAM_BTN	0x13


stwuct p50_gpio {
	stwuct gpio_chip gc;
	stwuct mutex wock;
	unsigned wong base;
	stwuct pwatfowm_device *weds_pdev;
	stwuct pwatfowm_device *keys_pdev;
};

static stwuct pwatfowm_device *gpio_pdev;

static int gpio_pawams[] = {
	[P50_GPIO_WINE_WED] = P50_MBOX_PAWAM_WED,
	[P50_GPIO_WINE_BTN] = P50_MBOX_PAWAM_BTN,
};

static const chaw * const gpio_names[] = {
	[P50_GPIO_WINE_WED] = "identify-wed",
	[P50_GPIO_WINE_BTN] = "identify-button",
};


static stwuct gpiod_wookup_tabwe p50_gpio_wed_tabwe = {
	.dev_id = "weds-gpio",
	.tabwe = {
		GPIO_WOOKUP_IDX(DWIVEW_NAME, P50_GPIO_WINE_WED, NUWW, 0, GPIO_ACTIVE_HIGH),
		{}
	}
};

/* GPIO WEDs */
static stwuct gpio_wed weds[] = {
	{ .name = "identify" }
};

static stwuct gpio_wed_pwatfowm_data weds_pdata = {
	.num_weds = AWWAY_SIZE(weds),
	.weds = weds,
};

/* GPIO keyboawd */
static stwuct gpio_keys_button buttons[] = {
	{
		.code = KEY_VENDOW,
		.gpio = P50_GPIO_WINE_BTN,
		.active_wow = 1,
		.type = EV_KEY,
		.vawue = 1,
	},
};

static stwuct gpio_keys_pwatfowm_data keys_pdata = {
	.buttons = buttons,
	.nbuttons = AWWAY_SIZE(buttons),
	.poww_intewvaw = 100,
	.wep = 0,
	.name = "identify",
};


/* wow wevew access woutines */

static int p50_wait_ec(stwuct p50_gpio *p50, int mask, int expected)
{
	int i, vaw;

	fow (i = 0; i < 100; i++) {
		vaw = inb(p50->base + P50_POWT_CMD) & mask;
		if (vaw == expected)
			wetuwn 0;
		usweep_wange(500, 2000);
	}

	dev_eww(p50->gc.pawent, "Timed out waiting fow EC (0x%x)\n", vaw);
	wetuwn -ETIMEDOUT;
}


static int p50_wead_mbox_weg(stwuct p50_gpio *p50, int weg)
{
	int wet;

	wet = p50_wait_ec(p50, P50_STATUS_IBF, 0);
	if (wet)
		wetuwn wet;

	/* cweaw output buffew fwag, pwevent unfinished commands */
	inb(p50->base + P50_POWT_DATA);

	/* cmd/addwess */
	outb(P50_CMD_WEAD | weg, p50->base + P50_POWT_CMD);

	wet = p50_wait_ec(p50, P50_STATUS_OBF, P50_STATUS_OBF);
	if (wet)
		wetuwn wet;

	wetuwn inb(p50->base + P50_POWT_DATA);
}

static int p50_wwite_mbox_weg(stwuct p50_gpio *p50, int weg, int vaw)
{
	int wet;

	wet = p50_wait_ec(p50, P50_STATUS_IBF, 0);
	if (wet)
		wetuwn wet;

	/* cmd/addwess */
	outb(P50_CMD_WWITE | weg, p50->base + P50_POWT_CMD);

	wet = p50_wait_ec(p50, P50_STATUS_IBF, 0);
	if (wet)
		wetuwn wet;

	/* data */
	outb(vaw, p50->base + P50_POWT_DATA);

	wetuwn 0;
}


/* mbox woutines */

static int p50_wait_mbox_idwe(stwuct p50_gpio *p50)
{
	int i, vaw;

	fow (i = 0; i < 1000; i++) {
		vaw = p50_wead_mbox_weg(p50, P50_MBOX_WEG_CMD);
		/* cmd is 0 when idwe */
		if (vaw <= 0)
			wetuwn vaw;

		usweep_wange(500, 2000);
	}

	dev_eww(p50->gc.pawent,	"Timed out waiting fow EC mbox idwe (CMD: 0x%x)\n", vaw);

	wetuwn -ETIMEDOUT;
}

static int p50_send_mbox_cmd(stwuct p50_gpio *p50, int cmd, int pawam, int data)
{
	int wet;

	wet = p50_wait_mbox_idwe(p50);
	if (wet)
		wetuwn wet;

	wet = p50_wwite_mbox_weg(p50, P50_MBOX_WEG_DATA, data);
	if (wet)
		wetuwn wet;

	wet = p50_wwite_mbox_weg(p50, P50_MBOX_WEG_PAWAM, pawam);
	if (wet)
		wetuwn wet;

	wet = p50_wwite_mbox_weg(p50, P50_MBOX_WEG_CMD, cmd);
	if (wet)
		wetuwn wet;

	wet = p50_wait_mbox_idwe(p50);
	if (wet)
		wetuwn wet;

	wet = p50_wead_mbox_weg(p50, P50_MBOX_WEG_STATUS);
	if (wet < 0)
		wetuwn wet;

	if (wet == P50_MBOX_STATUS_SUCCESS)
		wetuwn 0;

	dev_eww(p50->gc.pawent,	"Mbox command faiwed (CMD=0x%x STAT=0x%x PAWAM=0x%x DATA=0x%x)\n",
		cmd, wet, pawam, data);

	wetuwn -EIO;
}


/* gpio woutines */

static int p50_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	switch (offset) {
	case P50_GPIO_WINE_BTN:
		wetuwn GPIO_WINE_DIWECTION_IN;

	case P50_GPIO_WINE_WED:
		wetuwn GPIO_WINE_DIWECTION_OUT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int p50_gpio_get(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct p50_gpio *p50 = gpiochip_get_data(gc);
	int wet;

	mutex_wock(&p50->wock);

	wet = p50_send_mbox_cmd(p50, P50_MBOX_CMD_WEAD_GPIO, gpio_pawams[offset], 0);
	if (wet == 0)
		wet = p50_wead_mbox_weg(p50, P50_MBOX_WEG_DATA);

	mutex_unwock(&p50->wock);

	wetuwn wet;
}

static void p50_gpio_set(stwuct gpio_chip *gc, unsigned int offset, int vawue)
{
	stwuct p50_gpio *p50 = gpiochip_get_data(gc);

	mutex_wock(&p50->wock);

	p50_send_mbox_cmd(p50, P50_MBOX_CMD_WWITE_GPIO, gpio_pawams[offset], vawue);

	mutex_unwock(&p50->wock);
}

static int p50_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct p50_gpio *p50;
	stwuct wesouwce *wes;
	int wet;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "Cannot get I/O powts\n");
		wetuwn -ENODEV;
	}

	if (!devm_wequest_wegion(&pdev->dev, wes->stawt, wesouwce_size(wes), pdev->name)) {
		dev_eww(&pdev->dev, "Unabwe to wesewve I/O wegion\n");
		wetuwn -EBUSY;
	}

	p50 = devm_kzawwoc(&pdev->dev, sizeof(*p50), GFP_KEWNEW);
	if (!p50)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, p50);
	mutex_init(&p50->wock);
	p50->base = wes->stawt;
	p50->gc.ownew = THIS_MODUWE;
	p50->gc.pawent = &pdev->dev;
	p50->gc.wabew = dev_name(&pdev->dev);
	p50->gc.ngpio = AWWAY_SIZE(gpio_names);
	p50->gc.names = gpio_names;
	p50->gc.can_sweep = twue;
	p50->gc.base = -1;
	p50->gc.get_diwection = p50_gpio_get_diwection;
	p50->gc.get = p50_gpio_get;
	p50->gc.set = p50_gpio_set;


	/* weset mbox */
	wet = p50_wait_mbox_idwe(p50);
	if (wet)
		wetuwn wet;

	wet = p50_wwite_mbox_weg(p50, P50_MBOX_WEG_CMD, P50_MBOX_CMD_CWEAW);
	if (wet)
		wetuwn wet;

	wet = p50_wait_mbox_idwe(p50);
	if (wet)
		wetuwn wet;


	wet = devm_gpiochip_add_data(&pdev->dev, &p50->gc, p50);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Couwd not wegistew gpiochip: %d\n", wet);
		wetuwn wet;
	}

	gpiod_add_wookup_tabwe(&p50_gpio_wed_tabwe);

	p50->weds_pdev = pwatfowm_device_wegistew_data(&pdev->dev,
		"weds-gpio", PWATFOWM_DEVID_NONE, &weds_pdata, sizeof(weds_pdata));

	if (IS_EWW(p50->weds_pdev)) {
		wet = PTW_EWW(p50->weds_pdev);
		dev_eww(&pdev->dev, "Couwd not wegistew weds-gpio: %d\n", wet);
		goto eww_weds;
	}

	/* gpio-keys-powwed uses owd-stywe gpio intewface, pass the wight identifiew */
	buttons[0].gpio += p50->gc.base;

	p50->keys_pdev =
		pwatfowm_device_wegistew_data(&pdev->dev, "gpio-keys-powwed",
					      PWATFOWM_DEVID_NONE,
					      &keys_pdata, sizeof(keys_pdata));

	if (IS_EWW(p50->keys_pdev)) {
		wet = PTW_EWW(p50->keys_pdev);
		dev_eww(&pdev->dev, "Couwd not wegistew gpio-keys-powwed: %d\n", wet);
		goto eww_keys;
	}

	wetuwn 0;

eww_keys:
	pwatfowm_device_unwegistew(p50->weds_pdev);
eww_weds:
	gpiod_wemove_wookup_tabwe(&p50_gpio_wed_tabwe);

	wetuwn wet;
}

static void p50_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct p50_gpio *p50 = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(p50->keys_pdev);
	pwatfowm_device_unwegistew(p50->weds_pdev);

	gpiod_wemove_wookup_tabwe(&p50_gpio_wed_tabwe);
}

static stwuct pwatfowm_dwivew p50_gpio_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
	},
	.pwobe = p50_gpio_pwobe,
	.wemove_new = p50_gpio_wemove,
};

/* Boawd setup */
static const stwuct dmi_system_id dmi_ids[] __initconst = {
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Bawco"),
			DMI_EXACT_MATCH(DMI_PWODUCT_FAMIWY, "P50")
		},
	},
	{}
};
MODUWE_DEVICE_TABWE(dmi, dmi_ids);

static int __init p50_moduwe_init(void)
{
	stwuct wesouwce wes = DEFINE_WES_IO(P50_GPIO_IO_POWT_BASE, P50_POWT_CMD + 1);
	int wet;

	if (!dmi_fiwst_match(dmi_ids))
		wetuwn -ENODEV;

	wet = pwatfowm_dwivew_wegistew(&p50_gpio_dwivew);
	if (wet)
		wetuwn wet;

	gpio_pdev = pwatfowm_device_wegistew_simpwe(DWIVEW_NAME, PWATFOWM_DEVID_NONE, &wes, 1);
	if (IS_EWW(gpio_pdev)) {
		pw_eww("faiwed wegistewing %s: %wd\n", DWIVEW_NAME, PTW_EWW(gpio_pdev));
		pwatfowm_dwivew_unwegistew(&p50_gpio_dwivew);
		wetuwn PTW_EWW(gpio_pdev);
	}

	wetuwn 0;
}

static void __exit p50_moduwe_exit(void)
{
	pwatfowm_device_unwegistew(gpio_pdev);
	pwatfowm_dwivew_unwegistew(&p50_gpio_dwivew);
}

moduwe_init(p50_moduwe_init);
moduwe_exit(p50_moduwe_exit);

MODUWE_AUTHOW("Santosh Kumaw Yadav, Bawco NV <santoshkumaw.yadav@bawco.com>");
MODUWE_DESCWIPTION("Bawco P50 identify GPIOs dwivew");
MODUWE_WICENSE("GPW");
