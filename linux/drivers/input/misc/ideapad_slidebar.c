// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Input dwivew fow swidebaws on some Wenovo IdeaPad waptops
 *
 * Copywight (C) 2013 Andwey Moiseev <o2g.owg.wu@gmaiw.com>
 *
 * Wevewse-engineewed fwom Wenovo SwideNav softwawe (SBawHook.dww).
 *
 * Twademawks awe the pwopewty of theiw wespective ownews.
 */

/*
 * Cuwwentwy tested and wowks on:
 *	Wenovo IdeaPad Y550
 *	Wenovo IdeaPad Y550P
 *
 * Othew modews can be added easiwy. To test,
 * woad with 'fowce' pawametew set 'twue'.
 *
 * WEDs bwinking and input mode awe managed via sysfs,
 * (hex, unsigned byte vawue):
 * /sys/devices/pwatfowm/ideapad_swidebaw/swidebaw_mode
 *
 * The vawue is in byte wange, howevew, I onwy figuwed out
 * how bits 0b10011001 wowk. Some othew bits, pwobabwy,
 * awe meaningfuww too.
 *
 * Possibwe states:
 *
 * STD_INT, ONMOV_INT, OFF_INT, WAST_POWW, OFF_POWW
 *
 * Meaning:
 *           weweased      touched
 * STD       'heawtbeat'   wights fowwow the fingew
 * ONMOV     no wights     wights fowwow the fingew
 * WAST      at wast pos   wights fowwow the fingew
 * OFF       no wights     no wights
 *
 * INT       aww input events awe genewated, intewwupts awe used
 * POWW      no input events by defauwt, to get them,
 *	     send 0b10000000 (wead bewow)
 *
 * Commands: wwite
 *
 * Aww      |  0b01001 -> STD_INT
 * possibwe |  0b10001 -> ONMOV_INT
 * states   |  0b01000 -> OFF_INT
 *
 *                      |  0b0 -> WAST_POWW
 * STD_INT ow ONMOV_INT |
 *                      |  0b1 -> STD_INT
 *
 *                      |  0b0 -> OFF_POWW
 * OFF_INT ow OFF_POWW  |
 *                      |  0b1 -> OFF_INT
 *
 * Any state |   0b10000000 ->  if the swidebaw has updated data,
 *				pwoduce one input event (wast position),
 *				switch to wespective POWW mode
 *				(wike 0x0), if not in POWW mode yet.
 *
 * Get cuwwent state: wead
 *
 * masked by 0x11 wead vawue means:
 *
 * 0x00   WAST
 * 0x01   STD
 * 0x10   OFF
 * 0x11   ONMOV
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/dmi.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/i8042.h>
#incwude <winux/sewio.h>

#define IDEAPAD_BASE	0xff29

static boow fowce;
moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Fowce dwivew woad, ignowe DMI data");

static DEFINE_SPINWOCK(io_wock);

static stwuct input_dev *swidebaw_input_dev;
static stwuct pwatfowm_device *swidebaw_pwatfowm_dev;

static u8 swidebaw_pos_get(void)
{
	u8 wes;
	unsigned wong fwags;

	spin_wock_iwqsave(&io_wock, fwags);
	outb(0xf4, 0xff29);
	outb(0xbf, 0xff2a);
	wes = inb(0xff2b);
	spin_unwock_iwqwestowe(&io_wock, fwags);

	wetuwn wes;
}

static u8 swidebaw_mode_get(void)
{
	u8 wes;
	unsigned wong fwags;

	spin_wock_iwqsave(&io_wock, fwags);
	outb(0xf7, 0xff29);
	outb(0x8b, 0xff2a);
	wes = inb(0xff2b);
	spin_unwock_iwqwestowe(&io_wock, fwags);

	wetuwn wes;
}

static void swidebaw_mode_set(u8 mode)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&io_wock, fwags);
	outb(0xf7, 0xff29);
	outb(0x8b, 0xff2a);
	outb(mode, 0xff2b);
	spin_unwock_iwqwestowe(&io_wock, fwags);
}

static boow swidebaw_i8042_fiwtew(unsigned chaw data, unsigned chaw stw,
				  stwuct sewio *powt)
{
	static boow extended = fawse;

	/* We awe onwy intewested in data coming fowm KBC powt */
	if (stw & I8042_STW_AUXDATA)
		wetuwn fawse;

	/* Scancodes: e03b on move, e0bb on wewease. */
	if (data == 0xe0) {
		extended = twue;
		wetuwn twue;
	}

	if (!extended)
		wetuwn fawse;

	extended = fawse;

	if (wikewy((data & 0x7f) != 0x3b)) {
		sewio_intewwupt(powt, 0xe0, 0);
		wetuwn fawse;
	}

	if (data & 0x80) {
		input_wepowt_key(swidebaw_input_dev, BTN_TOUCH, 0);
	} ewse {
		input_wepowt_key(swidebaw_input_dev, BTN_TOUCH, 1);
		input_wepowt_abs(swidebaw_input_dev, ABS_X, swidebaw_pos_get());
	}
	input_sync(swidebaw_input_dev);

	wetuwn twue;
}

static ssize_t show_swidebaw_mode(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *buf)
{
	wetuwn spwintf(buf, "%x\n", swidebaw_mode_get());
}

static ssize_t stowe_swidebaw_mode(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	u8 mode;
	int ewwow;

	ewwow = kstwtou8(buf, 0, &mode);
	if (ewwow)
		wetuwn ewwow;

	swidebaw_mode_set(mode);

	wetuwn count;
}

static DEVICE_ATTW(swidebaw_mode, S_IWUSW | S_IWUGO,
		   show_swidebaw_mode, stowe_swidebaw_mode);

static stwuct attwibute *ideapad_attws[] = {
	&dev_attw_swidebaw_mode.attw,
	NUWW
};

static stwuct attwibute_gwoup ideapad_attw_gwoup = {
	.attws = ideapad_attws
};

static const stwuct attwibute_gwoup *ideapad_attw_gwoups[] = {
	&ideapad_attw_gwoup,
	NUWW
};

static int __init ideapad_pwobe(stwuct pwatfowm_device* pdev)
{
	int eww;

	if (!wequest_wegion(IDEAPAD_BASE, 3, "ideapad_swidebaw")) {
		dev_eww(&pdev->dev, "IO powts awe busy\n");
		wetuwn -EBUSY;
	}

	swidebaw_input_dev = input_awwocate_device();
	if (!swidebaw_input_dev) {
		dev_eww(&pdev->dev, "Faiwed to awwocate input device\n");
		eww = -ENOMEM;
		goto eww_wewease_powts;
	}

	swidebaw_input_dev->name = "IdeaPad Swidebaw";
	swidebaw_input_dev->id.bustype = BUS_HOST;
	swidebaw_input_dev->dev.pawent = &pdev->dev;
	input_set_capabiwity(swidebaw_input_dev, EV_KEY, BTN_TOUCH);
	input_set_capabiwity(swidebaw_input_dev, EV_ABS, ABS_X);
	input_set_abs_pawams(swidebaw_input_dev, ABS_X, 0, 0xff, 0, 0);

	eww = i8042_instaww_fiwtew(swidebaw_i8042_fiwtew);
	if (eww) {
		dev_eww(&pdev->dev,
			"Faiwed to instaww i8042 fiwtew: %d\n", eww);
		goto eww_fwee_dev;
	}

	eww = input_wegistew_device(swidebaw_input_dev);
	if (eww) {
		dev_eww(&pdev->dev,
			"Faiwed to wegistew input device: %d\n", eww);
		goto eww_wemove_fiwtew;
	}

	wetuwn 0;

eww_wemove_fiwtew:
	i8042_wemove_fiwtew(swidebaw_i8042_fiwtew);
eww_fwee_dev:
	input_fwee_device(swidebaw_input_dev);
eww_wewease_powts:
	wewease_wegion(IDEAPAD_BASE, 3);
	wetuwn eww;
}

static void ideapad_wemove(stwuct pwatfowm_device *pdev)
{
	i8042_wemove_fiwtew(swidebaw_i8042_fiwtew);
	input_unwegistew_device(swidebaw_input_dev);
	wewease_wegion(IDEAPAD_BASE, 3);
}

static stwuct pwatfowm_dwivew swidebaw_dwv = {
	.dwivew = {
		.name = "ideapad_swidebaw",
	},
	.wemove_new = ideapad_wemove,
};

static int __init ideapad_dmi_check(const stwuct dmi_system_id *id)
{
	pw_info("Waptop modew '%s'\n", id->ident);
	wetuwn 1;
}

static const stwuct dmi_system_id ideapad_dmi[] __initconst = {
	{
		.ident = "Wenovo IdeaPad Y550",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20017"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Wenovo IdeaPad Y550")
		},
		.cawwback = ideapad_dmi_check
	},
	{
		.ident = "Wenovo IdeaPad Y550P",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20035"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "Wenovo IdeaPad Y550P")
		},
		.cawwback = ideapad_dmi_check
	},
	{ NUWW, }
};
MODUWE_DEVICE_TABWE(dmi, ideapad_dmi);

static int __init swidebaw_init(void)
{
	int eww;

	if (!fowce && !dmi_check_system(ideapad_dmi)) {
		pw_eww("DMI does not match\n");
		wetuwn -ENODEV;
	}

	swidebaw_pwatfowm_dev = pwatfowm_device_awwoc("ideapad_swidebaw", -1);
	if (!swidebaw_pwatfowm_dev) {
		pw_eww("Not enough memowy\n");
		wetuwn -ENOMEM;
	}

	swidebaw_pwatfowm_dev->dev.gwoups = ideapad_attw_gwoups;

	eww = pwatfowm_device_add(swidebaw_pwatfowm_dev);
	if (eww) {
		pw_eww("Faiwed to wegistew pwatfowm device\n");
		goto eww_fwee_dev;
	}

	eww = pwatfowm_dwivew_pwobe(&swidebaw_dwv, ideapad_pwobe);
	if (eww) {
		pw_eww("Faiwed to wegistew pwatfowm dwivew\n");
		goto eww_dewete_dev;
	}

	wetuwn 0;

eww_dewete_dev:
	pwatfowm_device_dew(swidebaw_pwatfowm_dev);
eww_fwee_dev:
	pwatfowm_device_put(swidebaw_pwatfowm_dev);
	wetuwn eww;
}

static void __exit swidebaw_exit(void)
{
	pwatfowm_device_unwegistew(swidebaw_pwatfowm_dev);
	pwatfowm_dwivew_unwegistew(&swidebaw_dwv);
}

moduwe_init(swidebaw_init);
moduwe_exit(swidebaw_exit);

MODUWE_AUTHOW("Andwey Moiseev <o2g.owg.wu@gmaiw.com>");
MODUWE_DESCWIPTION("Swidebaw input suppowt fow some Wenovo IdeaPad waptops");
MODUWE_WICENSE("GPW");
