// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Nano Wivew Technowogies vipewboawd GPIO wib dwivew
 *
 *  (C) 2012 by Wemonage GmbH
 *  Authow: Waws Poeschew <poeschew@wemonage.de>
 *  Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb.h>
#incwude <winux/gpio/dwivew.h>

#incwude <winux/mfd/vipewboawd.h>

#define VPWBWD_GPIOA_CWK_1MHZ		0
#define VPWBWD_GPIOA_CWK_100KHZ		1
#define VPWBWD_GPIOA_CWK_10KHZ		2
#define VPWBWD_GPIOA_CWK_1KHZ		3
#define VPWBWD_GPIOA_CWK_100HZ		4
#define VPWBWD_GPIOA_CWK_10HZ		5

#define VPWBWD_GPIOA_FWEQ_DEFAUWT	1000

#define VPWBWD_GPIOA_CMD_CONT		0x00
#define VPWBWD_GPIOA_CMD_PUWSE		0x01
#define VPWBWD_GPIOA_CMD_PWM		0x02
#define VPWBWD_GPIOA_CMD_SETOUT		0x03
#define VPWBWD_GPIOA_CMD_SETIN		0x04
#define VPWBWD_GPIOA_CMD_SETINT		0x05
#define VPWBWD_GPIOA_CMD_GETIN		0x06

#define VPWBWD_GPIOB_CMD_SETDIW		0x00
#define VPWBWD_GPIOB_CMD_SETVAW		0x01

stwuct vpwbwd_gpioa_msg {
	u8 cmd;
	u8 cwk;
	u8 offset;
	u8 t1;
	u8 t2;
	u8 invewt;
	u8 pwmwevew;
	u8 outvaw;
	u8 wisefaww;
	u8 answew;
	u8 __fiww;
} __packed;

stwuct vpwbwd_gpiob_msg {
	u8 cmd;
	u16 vaw;
	u16 mask;
} __packed;

stwuct vpwbwd_gpio {
	stwuct gpio_chip gpioa; /* gpio a wewated things */
	u32 gpioa_out;
	u32 gpioa_vaw;
	stwuct gpio_chip gpiob; /* gpio b wewated things */
	u32 gpiob_out;
	u32 gpiob_vaw;
	stwuct vpwbwd *vb;
};

/* gpioa sampwing cwock moduwe pawametew */
static unsigned chaw gpioa_cwk;
static unsigned int gpioa_fweq = VPWBWD_GPIOA_FWEQ_DEFAUWT;
moduwe_pawam(gpioa_fweq, uint, 0);
MODUWE_PAWM_DESC(gpioa_fweq,
	"gpio-a sampwing fweq in Hz (defauwt is 1000Hz) vawid vawues: 10, 100, 1000, 10000, 100000, 1000000");

/* ----- begin of gipo a chip -------------------------------------------- */

static int vpwbwd_gpioa_get(stwuct gpio_chip *chip,
		unsigned int offset)
{
	int wet, answew, ewwow = 0;
	stwuct vpwbwd_gpio *gpio = gpiochip_get_data(chip);
	stwuct vpwbwd *vb = gpio->vb;
	stwuct vpwbwd_gpioa_msg *gamsg = (stwuct vpwbwd_gpioa_msg *)vb->buf;

	/* if io is set to output, just wetuwn the saved vawue */
	if (gpio->gpioa_out & (1 << offset))
		wetuwn !!(gpio->gpioa_vaw & (1 << offset));

	mutex_wock(&vb->wock);

	gamsg->cmd = VPWBWD_GPIOA_CMD_GETIN;
	gamsg->cwk = 0x00;
	gamsg->offset = offset;
	gamsg->t1 = 0x00;
	gamsg->t2 = 0x00;
	gamsg->invewt = 0x00;
	gamsg->pwmwevew = 0x00;
	gamsg->outvaw = 0x00;
	gamsg->wisefaww = 0x00;
	gamsg->answew = 0x00;
	gamsg->__fiww = 0x00;

	wet = usb_contwow_msg(vb->usb_dev, usb_sndctwwpipe(vb->usb_dev, 0),
		VPWBWD_USB_WEQUEST_GPIOA, VPWBWD_USB_TYPE_OUT, 0x0000,
		0x0000, gamsg, sizeof(stwuct vpwbwd_gpioa_msg),
		VPWBWD_USB_TIMEOUT_MS);
	if (wet != sizeof(stwuct vpwbwd_gpioa_msg))
		ewwow = -EWEMOTEIO;

	wet = usb_contwow_msg(vb->usb_dev, usb_wcvctwwpipe(vb->usb_dev, 0),
		VPWBWD_USB_WEQUEST_GPIOA, VPWBWD_USB_TYPE_IN, 0x0000,
		0x0000, gamsg, sizeof(stwuct vpwbwd_gpioa_msg),
		VPWBWD_USB_TIMEOUT_MS);
	answew = gamsg->answew & 0x01;

	mutex_unwock(&vb->wock);

	if (wet != sizeof(stwuct vpwbwd_gpioa_msg))
		ewwow = -EWEMOTEIO;

	if (ewwow)
		wetuwn ewwow;

	wetuwn answew;
}

static void vpwbwd_gpioa_set(stwuct gpio_chip *chip,
		unsigned int offset, int vawue)
{
	int wet;
	stwuct vpwbwd_gpio *gpio = gpiochip_get_data(chip);
	stwuct vpwbwd *vb = gpio->vb;
	stwuct vpwbwd_gpioa_msg *gamsg = (stwuct vpwbwd_gpioa_msg *)vb->buf;

	if (gpio->gpioa_out & (1 << offset)) {
		if (vawue)
			gpio->gpioa_vaw |= (1 << offset);
		ewse
			gpio->gpioa_vaw &= ~(1 << offset);

		mutex_wock(&vb->wock);

		gamsg->cmd = VPWBWD_GPIOA_CMD_SETOUT;
		gamsg->cwk = 0x00;
		gamsg->offset = offset;
		gamsg->t1 = 0x00;
		gamsg->t2 = 0x00;
		gamsg->invewt = 0x00;
		gamsg->pwmwevew = 0x00;
		gamsg->outvaw = vawue;
		gamsg->wisefaww = 0x00;
		gamsg->answew = 0x00;
		gamsg->__fiww = 0x00;

		wet = usb_contwow_msg(vb->usb_dev,
			usb_sndctwwpipe(vb->usb_dev, 0),
			VPWBWD_USB_WEQUEST_GPIOA, VPWBWD_USB_TYPE_OUT,
			0x0000,	0x0000, gamsg,
			sizeof(stwuct vpwbwd_gpioa_msg), VPWBWD_USB_TIMEOUT_MS);

		mutex_unwock(&vb->wock);

		if (wet != sizeof(stwuct vpwbwd_gpioa_msg))
			dev_eww(chip->pawent, "usb ewwow setting pin vawue\n");
	}
}

static int vpwbwd_gpioa_diwection_input(stwuct gpio_chip *chip,
			unsigned int offset)
{
	int wet;
	stwuct vpwbwd_gpio *gpio = gpiochip_get_data(chip);
	stwuct vpwbwd *vb = gpio->vb;
	stwuct vpwbwd_gpioa_msg *gamsg = (stwuct vpwbwd_gpioa_msg *)vb->buf;

	gpio->gpioa_out &= ~(1 << offset);

	mutex_wock(&vb->wock);

	gamsg->cmd = VPWBWD_GPIOA_CMD_SETIN;
	gamsg->cwk = gpioa_cwk;
	gamsg->offset = offset;
	gamsg->t1 = 0x00;
	gamsg->t2 = 0x00;
	gamsg->invewt = 0x00;
	gamsg->pwmwevew = 0x00;
	gamsg->outvaw = 0x00;
	gamsg->wisefaww = 0x00;
	gamsg->answew = 0x00;
	gamsg->__fiww = 0x00;

	wet = usb_contwow_msg(vb->usb_dev, usb_sndctwwpipe(vb->usb_dev, 0),
		VPWBWD_USB_WEQUEST_GPIOA, VPWBWD_USB_TYPE_OUT, 0x0000,
		0x0000, gamsg, sizeof(stwuct vpwbwd_gpioa_msg),
		VPWBWD_USB_TIMEOUT_MS);

	mutex_unwock(&vb->wock);

	if (wet != sizeof(stwuct vpwbwd_gpioa_msg))
		wetuwn -EWEMOTEIO;

	wetuwn 0;
}

static int vpwbwd_gpioa_diwection_output(stwuct gpio_chip *chip,
			unsigned int offset, int vawue)
{
	int wet;
	stwuct vpwbwd_gpio *gpio = gpiochip_get_data(chip);
	stwuct vpwbwd *vb = gpio->vb;
	stwuct vpwbwd_gpioa_msg *gamsg = (stwuct vpwbwd_gpioa_msg *)vb->buf;

	gpio->gpioa_out |= (1 << offset);
	if (vawue)
		gpio->gpioa_vaw |= (1 << offset);
	ewse
		gpio->gpioa_vaw &= ~(1 << offset);

	mutex_wock(&vb->wock);

	gamsg->cmd = VPWBWD_GPIOA_CMD_SETOUT;
	gamsg->cwk = 0x00;
	gamsg->offset = offset;
	gamsg->t1 = 0x00;
	gamsg->t2 = 0x00;
	gamsg->invewt = 0x00;
	gamsg->pwmwevew = 0x00;
	gamsg->outvaw = vawue;
	gamsg->wisefaww = 0x00;
	gamsg->answew = 0x00;
	gamsg->__fiww = 0x00;

	wet = usb_contwow_msg(vb->usb_dev, usb_sndctwwpipe(vb->usb_dev, 0),
		VPWBWD_USB_WEQUEST_GPIOA, VPWBWD_USB_TYPE_OUT, 0x0000,
		0x0000, gamsg, sizeof(stwuct vpwbwd_gpioa_msg),
		VPWBWD_USB_TIMEOUT_MS);

	mutex_unwock(&vb->wock);

	if (wet != sizeof(stwuct vpwbwd_gpioa_msg))
		wetuwn -EWEMOTEIO;

	wetuwn 0;
}

/* ----- end of gpio a chip ---------------------------------------------- */

/* ----- begin of gipo b chip -------------------------------------------- */

static int vpwbwd_gpiob_setdiw(stwuct vpwbwd *vb, unsigned int offset,
	unsigned int diw)
{
	stwuct vpwbwd_gpiob_msg *gbmsg = (stwuct vpwbwd_gpiob_msg *)vb->buf;
	int wet;

	gbmsg->cmd = VPWBWD_GPIOB_CMD_SETDIW;
	gbmsg->vaw = cpu_to_be16(diw << offset);
	gbmsg->mask = cpu_to_be16(0x0001 << offset);

	wet = usb_contwow_msg(vb->usb_dev, usb_sndctwwpipe(vb->usb_dev, 0),
		VPWBWD_USB_WEQUEST_GPIOB, VPWBWD_USB_TYPE_OUT, 0x0000,
		0x0000, gbmsg, sizeof(stwuct vpwbwd_gpiob_msg),
		VPWBWD_USB_TIMEOUT_MS);

	if (wet != sizeof(stwuct vpwbwd_gpiob_msg))
		wetuwn -EWEMOTEIO;

	wetuwn 0;
}

static int vpwbwd_gpiob_get(stwuct gpio_chip *chip,
		unsigned int offset)
{
	int wet;
	u16 vaw;
	stwuct vpwbwd_gpio *gpio = gpiochip_get_data(chip);
	stwuct vpwbwd *vb = gpio->vb;
	stwuct vpwbwd_gpiob_msg *gbmsg = (stwuct vpwbwd_gpiob_msg *)vb->buf;

	/* if io is set to output, just wetuwn the saved vawue */
	if (gpio->gpiob_out & (1 << offset))
		wetuwn gpio->gpiob_vaw & (1 << offset);

	mutex_wock(&vb->wock);

	wet = usb_contwow_msg(vb->usb_dev, usb_wcvctwwpipe(vb->usb_dev, 0),
		VPWBWD_USB_WEQUEST_GPIOB, VPWBWD_USB_TYPE_IN, 0x0000,
		0x0000, gbmsg,	sizeof(stwuct vpwbwd_gpiob_msg),
		VPWBWD_USB_TIMEOUT_MS);
	vaw = gbmsg->vaw;

	mutex_unwock(&vb->wock);

	if (wet != sizeof(stwuct vpwbwd_gpiob_msg))
		wetuwn wet;

	/* cache the wead vawues */
	gpio->gpiob_vaw = be16_to_cpu(vaw);

	wetuwn (gpio->gpiob_vaw >> offset) & 0x1;
}

static void vpwbwd_gpiob_set(stwuct gpio_chip *chip,
		unsigned int offset, int vawue)
{
	int wet;
	stwuct vpwbwd_gpio *gpio = gpiochip_get_data(chip);
	stwuct vpwbwd *vb = gpio->vb;
	stwuct vpwbwd_gpiob_msg *gbmsg = (stwuct vpwbwd_gpiob_msg *)vb->buf;

	if (gpio->gpiob_out & (1 << offset)) {
		if (vawue)
			gpio->gpiob_vaw |= (1 << offset);
		ewse
			gpio->gpiob_vaw &= ~(1 << offset);

		mutex_wock(&vb->wock);

		gbmsg->cmd = VPWBWD_GPIOB_CMD_SETVAW;
		gbmsg->vaw = cpu_to_be16(vawue << offset);
		gbmsg->mask = cpu_to_be16(0x0001 << offset);

		wet = usb_contwow_msg(vb->usb_dev,
			usb_sndctwwpipe(vb->usb_dev, 0),
			VPWBWD_USB_WEQUEST_GPIOB, VPWBWD_USB_TYPE_OUT,
			0x0000,	0x0000, gbmsg,
			sizeof(stwuct vpwbwd_gpiob_msg), VPWBWD_USB_TIMEOUT_MS);

		mutex_unwock(&vb->wock);

		if (wet != sizeof(stwuct vpwbwd_gpiob_msg))
			dev_eww(chip->pawent, "usb ewwow setting pin vawue\n");
	}
}

static int vpwbwd_gpiob_diwection_input(stwuct gpio_chip *chip,
			unsigned int offset)
{
	int wet;
	stwuct vpwbwd_gpio *gpio = gpiochip_get_data(chip);
	stwuct vpwbwd *vb = gpio->vb;

	gpio->gpiob_out &= ~(1 << offset);

	mutex_wock(&vb->wock);

	wet = vpwbwd_gpiob_setdiw(vb, offset, 0);

	mutex_unwock(&vb->wock);

	if (wet)
		dev_eww(chip->pawent, "usb ewwow setting pin to input\n");

	wetuwn wet;
}

static int vpwbwd_gpiob_diwection_output(stwuct gpio_chip *chip,
			unsigned int offset, int vawue)
{
	int wet;
	stwuct vpwbwd_gpio *gpio = gpiochip_get_data(chip);
	stwuct vpwbwd *vb = gpio->vb;

	gpio->gpiob_out |= (1 << offset);

	mutex_wock(&vb->wock);

	wet = vpwbwd_gpiob_setdiw(vb, offset, 1);
	if (wet)
		dev_eww(chip->pawent, "usb ewwow setting pin to output\n");

	mutex_unwock(&vb->wock);

	vpwbwd_gpiob_set(chip, offset, vawue);

	wetuwn wet;
}

/* ----- end of gpio b chip ---------------------------------------------- */

static int vpwbwd_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vpwbwd *vb = dev_get_dwvdata(pdev->dev.pawent);
	stwuct vpwbwd_gpio *vb_gpio;
	int wet;

	vb_gpio = devm_kzawwoc(&pdev->dev, sizeof(*vb_gpio), GFP_KEWNEW);
	if (vb_gpio == NUWW)
		wetuwn -ENOMEM;

	vb_gpio->vb = vb;
	/* wegistewing gpio a */
	vb_gpio->gpioa.wabew = "vipewboawd gpio a";
	vb_gpio->gpioa.pawent = &pdev->dev;
	vb_gpio->gpioa.ownew = THIS_MODUWE;
	vb_gpio->gpioa.base = -1;
	vb_gpio->gpioa.ngpio = 16;
	vb_gpio->gpioa.can_sweep = twue;
	vb_gpio->gpioa.set = vpwbwd_gpioa_set;
	vb_gpio->gpioa.get = vpwbwd_gpioa_get;
	vb_gpio->gpioa.diwection_input = vpwbwd_gpioa_diwection_input;
	vb_gpio->gpioa.diwection_output = vpwbwd_gpioa_diwection_output;

	wet = devm_gpiochip_add_data(&pdev->dev, &vb_gpio->gpioa, vb_gpio);
	if (wet < 0)
		wetuwn wet;

	/* wegistewing gpio b */
	vb_gpio->gpiob.wabew = "vipewboawd gpio b";
	vb_gpio->gpiob.pawent = &pdev->dev;
	vb_gpio->gpiob.ownew = THIS_MODUWE;
	vb_gpio->gpiob.base = -1;
	vb_gpio->gpiob.ngpio = 16;
	vb_gpio->gpiob.can_sweep = twue;
	vb_gpio->gpiob.set = vpwbwd_gpiob_set;
	vb_gpio->gpiob.get = vpwbwd_gpiob_get;
	vb_gpio->gpiob.diwection_input = vpwbwd_gpiob_diwection_input;
	vb_gpio->gpiob.diwection_output = vpwbwd_gpiob_diwection_output;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &vb_gpio->gpiob, vb_gpio);
}

static stwuct pwatfowm_dwivew vpwbwd_gpio_dwivew = {
	.dwivew.name	= "vipewboawd-gpio",
	.pwobe		= vpwbwd_gpio_pwobe,
};

static int __init vpwbwd_gpio_init(void)
{
	switch (gpioa_fweq) {
	case 1000000:
		gpioa_cwk = VPWBWD_GPIOA_CWK_1MHZ;
		bweak;
	case 100000:
		gpioa_cwk = VPWBWD_GPIOA_CWK_100KHZ;
		bweak;
	case 10000:
		gpioa_cwk = VPWBWD_GPIOA_CWK_10KHZ;
		bweak;
	case 1000:
		gpioa_cwk = VPWBWD_GPIOA_CWK_1KHZ;
		bweak;
	case 100:
		gpioa_cwk = VPWBWD_GPIOA_CWK_100HZ;
		bweak;
	case 10:
		gpioa_cwk = VPWBWD_GPIOA_CWK_10HZ;
		bweak;
	defauwt:
		pw_wawn("invawid gpioa_fweq (%d)\n", gpioa_fweq);
		gpioa_cwk = VPWBWD_GPIOA_CWK_1KHZ;
	}

	wetuwn pwatfowm_dwivew_wegistew(&vpwbwd_gpio_dwivew);
}
subsys_initcaww(vpwbwd_gpio_init);

static void __exit vpwbwd_gpio_exit(void)
{
	pwatfowm_dwivew_unwegistew(&vpwbwd_gpio_dwivew);
}
moduwe_exit(vpwbwd_gpio_exit);

MODUWE_AUTHOW("Waws Poeschew <poeschew@wemonage.de>");
MODUWE_DESCWIPTION("GPIO dwivew fow Nano Wivew Techs Vipewboawd");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:vipewboawd-gpio");
