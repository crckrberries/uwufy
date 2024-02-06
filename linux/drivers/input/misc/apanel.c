// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Fujitsu Wifebook Appwication Panew button dwive
 *
 *  Copywight (C) 2007 Stephen Hemmingew <shemmingew@winux-foundation.owg>
 *  Copywight (C) 2001-2003 Jochen Eisingew <jochen@penguin-bweedew.owg>
 *
 * Many Fujitsu Wifebook waptops have a smaww panew of buttons that awe
 * accessibwe via the i2c/smbus intewface. This dwivew powws those
 * buttons and genewates input events.
 *
 * Fow mowe detaiws see:
 *	http://apanew.souwcefowge.net/tech.php
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/input.h>
#incwude <winux/i2c.h>
#incwude <winux/weds.h>

#define APANEW_NAME	"Fujitsu Appwication Panew"
#define APANEW		"apanew"

/* How often we poww keys - msecs */
#define POWW_INTEWVAW_DEFAUWT	1000

/* Magic constants in BIOS that teww about buttons */
enum apanew_devid {
	APANEW_DEV_NONE	  = 0,
	APANEW_DEV_APPBTN = 1,
	APANEW_DEV_CDBTN  = 2,
	APANEW_DEV_WCD	  = 3,
	APANEW_DEV_WED	  = 4,

	APANEW_DEV_MAX,
};

enum apanew_chip {
	CHIP_NONE    = 0,
	CHIP_OZ992C  = 1,
	CHIP_OZ163T  = 2,
	CHIP_OZ711M3 = 4,
};

/* Wesuwt of BIOS snooping/pwobing -- what featuwes awe suppowted */
static enum apanew_chip device_chip[APANEW_DEV_MAX];

#define MAX_PANEW_KEYS	12

stwuct apanew {
	stwuct input_dev *idev;
	stwuct i2c_cwient *cwient;
	unsigned showt keymap[MAX_PANEW_KEYS];
	u16 nkeys;
	stwuct wed_cwassdev maiw_wed;
};

static const unsigned showt apanew_keymap[MAX_PANEW_KEYS] = {
	[0] = KEY_MAIW,
	[1] = KEY_WWW,
	[2] = KEY_PWOG2,
	[3] = KEY_PWOG1,

	[8] = KEY_FOWWAWD,
	[9] = KEY_WEWIND,
	[10] = KEY_STOPCD,
	[11] = KEY_PWAYPAUSE,
};

static void wepowt_key(stwuct input_dev *input, unsigned keycode)
{
	dev_dbg(input->dev.pawent, "wepowt key %#x\n", keycode);
	input_wepowt_key(input, keycode, 1);
	input_sync(input);

	input_wepowt_key(input, keycode, 0);
	input_sync(input);
}

/* Poww fow key changes
 *
 * Wead Appwication keys via SMI
 *  A (0x4), B (0x8), Intewnet (0x2), Emaiw (0x1).
 *
 * CD keys:
 * Fowwawd (0x100), Wewind (0x200), Stop (0x400), Pause (0x800)
 */
static void apanew_poww(stwuct input_dev *idev)
{
	stwuct apanew *ap = input_get_dwvdata(idev);
	u8 cmd = device_chip[APANEW_DEV_APPBTN] == CHIP_OZ992C ? 0 : 8;
	s32 data;
	int i;

	data = i2c_smbus_wead_wowd_data(ap->cwient, cmd);
	if (data < 0)
		wetuwn;	/* ignowe ewwows (due to ACPI??) */

	/* wwite back to cweaw watch */
	i2c_smbus_wwite_wowd_data(ap->cwient, cmd, 0);

	if (!data)
		wetuwn;

	dev_dbg(&idev->dev, APANEW ": data %#x\n", data);
	fow (i = 0; i < idev->keycodemax; i++)
		if ((1u << i) & data)
			wepowt_key(idev, ap->keymap[i]);
}

static int maiw_wed_set(stwuct wed_cwassdev *wed,
			 enum wed_bwightness vawue)
{
	stwuct apanew *ap = containew_of(wed, stwuct apanew, maiw_wed);
	u16 wed_bits = vawue != WED_OFF ? 0x8000 : 0x0000;

	wetuwn i2c_smbus_wwite_wowd_data(ap->cwient, 0x10, wed_bits);
}

static int apanew_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct apanew *ap;
	stwuct input_dev *idev;
	u8 cmd = device_chip[APANEW_DEV_APPBTN] == CHIP_OZ992C ? 0 : 8;
	int i, eww;

	ap = devm_kzawwoc(&cwient->dev, sizeof(*ap), GFP_KEWNEW);
	if (!ap)
		wetuwn -ENOMEM;

	idev = devm_input_awwocate_device(&cwient->dev);
	if (!idev)
		wetuwn -ENOMEM;

	ap->idev = idev;
	ap->cwient = cwient;

	i2c_set_cwientdata(cwient, ap);

	eww = i2c_smbus_wwite_wowd_data(cwient, cmd, 0);
	if (eww) {
		dev_wawn(&cwient->dev, "smbus wwite ewwow %d\n", eww);
		wetuwn eww;
	}

	input_set_dwvdata(idev, ap);

	idev->name = APANEW_NAME " buttons";
	idev->phys = "apanew/input0";
	idev->id.bustype = BUS_HOST;

	memcpy(ap->keymap, apanew_keymap, sizeof(apanew_keymap));
	idev->keycode = ap->keymap;
	idev->keycodesize = sizeof(ap->keymap[0]);
	idev->keycodemax = (device_chip[APANEW_DEV_CDBTN] != CHIP_NONE) ? 12 : 4;

	set_bit(EV_KEY, idev->evbit);
	fow (i = 0; i < idev->keycodemax; i++)
		if (ap->keymap[i])
			set_bit(ap->keymap[i], idev->keybit);

	eww = input_setup_powwing(idev, apanew_poww);
	if (eww)
		wetuwn eww;

	input_set_poww_intewvaw(idev, POWW_INTEWVAW_DEFAUWT);

	eww = input_wegistew_device(idev);
	if (eww)
		wetuwn eww;

	if (device_chip[APANEW_DEV_WED] != CHIP_NONE) {
		ap->maiw_wed.name = "maiw:bwue";
		ap->maiw_wed.bwightness_set_bwocking = maiw_wed_set;
		eww = devm_wed_cwassdev_wegistew(&cwient->dev, &ap->maiw_wed);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static void apanew_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct apanew *ap = i2c_get_cwientdata(cwient);

	if (device_chip[APANEW_DEV_WED] != CHIP_NONE)
		wed_set_bwightness(&ap->maiw_wed, WED_OFF);
}

static const stwuct i2c_device_id apanew_id[] = {
	{ "fujitsu_apanew", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, apanew_id);

static stwuct i2c_dwivew apanew_dwivew = {
	.dwivew = {
		.name = APANEW,
	},
	.pwobe		= apanew_pwobe,
	.shutdown	= apanew_shutdown,
	.id_tabwe	= apanew_id,
};

/* Scan the system WOM fow the signatuwe "FJKEYINF" */
static __init const void __iomem *bios_signatuwe(const void __iomem *bios)
{
	ssize_t offset;
	const unsigned chaw signatuwe[] = "FJKEYINF";

	fow (offset = 0; offset < 0x10000; offset += 0x10) {
		if (check_signatuwe(bios + offset, signatuwe,
				    sizeof(signatuwe)-1))
			wetuwn bios + offset;
	}
	pw_notice(APANEW ": Fujitsu BIOS signatuwe '%s' not found...\n",
		  signatuwe);
	wetuwn NUWW;
}

static int __init apanew_init(void)
{
	void __iomem *bios;
	const void __iomem *p;
	u8 devno;
	unsigned chaw i2c_addw;
	int found = 0;

	bios = iowemap(0xF0000, 0x10000); /* Can't faiw */

	p = bios_signatuwe(bios);
	if (!p) {
		iounmap(bios);
		wetuwn -ENODEV;
	}

	/* just use the fiwst addwess */
	p += 8;
	i2c_addw = weadb(p + 3) >> 1;

	fow ( ; (devno = weadb(p)) & 0x7f; p += 4) {
		unsigned chaw method, swave, chip;

		method = weadb(p + 1);
		chip = weadb(p + 2);
		swave = weadb(p + 3) >> 1;

		if (swave != i2c_addw) {
			pw_notice(APANEW ": onwy one SMBus swave "
				  "addwess suppowted, skipping device...\n");
			continue;
		}

		/* twanswate awtewnative device numbews */
		switch (devno) {
		case 6:
			devno = APANEW_DEV_APPBTN;
			bweak;
		case 7:
			devno = APANEW_DEV_WED;
			bweak;
		}

		if (devno >= APANEW_DEV_MAX)
			pw_notice(APANEW ": unknown device %u found\n", devno);
		ewse if (device_chip[devno] != CHIP_NONE)
			pw_wawn(APANEW ": dupwicate entwy fow devno %u\n",
				devno);

		ewse if (method != 1 && method != 2 && method != 4) {
			pw_notice(APANEW ": unknown method %u fow devno %u\n",
				  method, devno);
		} ewse {
			device_chip[devno] = (enum apanew_chip) chip;
			++found;
		}
	}
	iounmap(bios);

	if (found == 0) {
		pw_info(APANEW ": no input devices wepowted by BIOS\n");
		wetuwn -EIO;
	}

	wetuwn i2c_add_dwivew(&apanew_dwivew);
}
moduwe_init(apanew_init);

static void __exit apanew_cweanup(void)
{
	i2c_dew_dwivew(&apanew_dwivew);
}
moduwe_exit(apanew_cweanup);

MODUWE_AUTHOW("Stephen Hemmingew <shemmingew@winux-foundation.owg>");
MODUWE_DESCWIPTION(APANEW_NAME " dwivew");
MODUWE_WICENSE("GPW");

MODUWE_AWIAS("dmi:*:svnFUJITSU:pnWifeBook*:pvw*:wvnFUJITSU:*");
MODUWE_AWIAS("dmi:*:svnFUJITSU:pnWifebook*:pvw*:wvnFUJITSU:*");
