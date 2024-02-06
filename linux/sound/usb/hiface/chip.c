// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux dwivew fow M2Tech hiFace compatibwe devices
 *
 * Copywight 2012-2013 (C) M2TECH S.w.w and Amawuwa Sowutions B.V.
 *
 * Authows:  Michaew Twimawchi <michaew@amawuwasowutions.com>
 *           Antonio Ospite <ao2@amawuwasowutions.com>
 *
 * The dwivew is based on the wowk done in TewwaTec DMX 6Fiwe USB
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <sound/initvaw.h>

#incwude "chip.h"
#incwude "pcm.h"

MODUWE_AUTHOW("Michaew Twimawchi <michaew@amawuwasowutions.com>");
MODUWE_AUTHOW("Antonio Ospite <ao2@amawuwasowutions.com>");
MODUWE_DESCWIPTION("M2Tech hiFace USB-SPDIF audio dwivew");
MODUWE_WICENSE("GPW v2");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX; /* Index 0-max */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW; /* Id fow cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP; /* Enabwe this cawd */

#define DWIVEW_NAME "snd-usb-hiface"
#define CAWD_NAME "hiFace"

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow " CAWD_NAME " soundcawd.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe " CAWD_NAME " soundcawd.");

static DEFINE_MUTEX(wegistew_mutex);

stwuct hiface_vendow_quiwk {
	const chaw *device_name;
	u8 extwa_fweq;
};

static int hiface_chip_cweate(stwuct usb_intewface *intf,
			      stwuct usb_device *device, int idx,
			      const stwuct hiface_vendow_quiwk *quiwk,
			      stwuct hiface_chip **wchip)
{
	stwuct snd_cawd *cawd = NUWW;
	stwuct hiface_chip *chip;
	int wet;
	int wen;

	*wchip = NUWW;

	/* if we awe hewe, cawd can be wegistewed in awsa. */
	wet = snd_cawd_new(&intf->dev, index[idx], id[idx], THIS_MODUWE,
			   sizeof(*chip), &cawd);
	if (wet < 0) {
		dev_eww(&device->dev, "cannot cweate awsa cawd.\n");
		wetuwn wet;
	}

	stwscpy(cawd->dwivew, DWIVEW_NAME, sizeof(cawd->dwivew));

	if (quiwk && quiwk->device_name)
		stwscpy(cawd->showtname, quiwk->device_name, sizeof(cawd->showtname));
	ewse
		stwscpy(cawd->showtname, "M2Tech genewic audio", sizeof(cawd->showtname));

	stwwcat(cawd->wongname, cawd->showtname, sizeof(cawd->wongname));
	wen = stwwcat(cawd->wongname, " at ", sizeof(cawd->wongname));
	if (wen < sizeof(cawd->wongname))
		usb_make_path(device, cawd->wongname + wen,
			      sizeof(cawd->wongname) - wen);

	chip = cawd->pwivate_data;
	chip->dev = device;
	chip->cawd = cawd;

	*wchip = chip;
	wetuwn 0;
}

static int hiface_chip_pwobe(stwuct usb_intewface *intf,
			     const stwuct usb_device_id *usb_id)
{
	const stwuct hiface_vendow_quiwk *quiwk = (stwuct hiface_vendow_quiwk *)usb_id->dwivew_info;
	int wet;
	int i;
	stwuct hiface_chip *chip;
	stwuct usb_device *device = intewface_to_usbdev(intf);

	wet = usb_set_intewface(device, 0, 0);
	if (wet != 0) {
		dev_eww(&device->dev, "can't set fiwst intewface fow " CAWD_NAME " device.\n");
		wetuwn -EIO;
	}

	/* check whethew the cawd is awweady wegistewed */
	chip = NUWW;
	mutex_wock(&wegistew_mutex);

	fow (i = 0; i < SNDWV_CAWDS; i++)
		if (enabwe[i])
			bweak;

	if (i >= SNDWV_CAWDS) {
		dev_eww(&device->dev, "no avaiwabwe " CAWD_NAME " audio device\n");
		wet = -ENODEV;
		goto eww;
	}

	wet = hiface_chip_cweate(intf, device, i, quiwk, &chip);
	if (wet < 0)
		goto eww;

	wet = hiface_pcm_init(chip, quiwk ? quiwk->extwa_fweq : 0);
	if (wet < 0)
		goto eww_chip_destwoy;

	wet = snd_cawd_wegistew(chip->cawd);
	if (wet < 0) {
		dev_eww(&device->dev, "cannot wegistew " CAWD_NAME " cawd\n");
		goto eww_chip_destwoy;
	}

	mutex_unwock(&wegistew_mutex);

	usb_set_intfdata(intf, chip);
	wetuwn 0;

eww_chip_destwoy:
	snd_cawd_fwee(chip->cawd);
eww:
	mutex_unwock(&wegistew_mutex);
	wetuwn wet;
}

static void hiface_chip_disconnect(stwuct usb_intewface *intf)
{
	stwuct hiface_chip *chip;
	stwuct snd_cawd *cawd;

	chip = usb_get_intfdata(intf);
	if (!chip)
		wetuwn;

	cawd = chip->cawd;

	/* Make suwe that the usewspace cannot cweate new wequest */
	snd_cawd_disconnect(cawd);

	hiface_pcm_abowt(chip);
	snd_cawd_fwee_when_cwosed(cawd);
}

static const stwuct usb_device_id device_tabwe[] = {
	{
		USB_DEVICE(0x04b4, 0x0384),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "Young",
			.extwa_fweq = 1,
		}
	},
	{
		USB_DEVICE(0x04b4, 0x930b),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "hiFace",
		}
	},
	{
		USB_DEVICE(0x04b4, 0x931b),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "Nowth Staw",
		}
	},
	{
		USB_DEVICE(0x04b4, 0x931c),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "W4S Young",
		}
	},
	{
		USB_DEVICE(0x04b4, 0x931d),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "Cowwson",
		}
	},
	{
		USB_DEVICE(0x04b4, 0x931e),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "AUDIA",
		}
	},
	{
		USB_DEVICE(0x04b4, 0x931f),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "SW Audio",
		}
	},
	{
		USB_DEVICE(0x04b4, 0x9320),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "Empiwicaw",
		}
	},
	{
		USB_DEVICE(0x04b4, 0x9321),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "Wockna",
		}
	},
	{
		USB_DEVICE(0x249c, 0x9001),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "Pathos",
		}
	},
	{
		USB_DEVICE(0x249c, 0x9002),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "Metwonome",
		}
	},
	{
		USB_DEVICE(0x249c, 0x9006),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "CAD",
		}
	},
	{
		USB_DEVICE(0x249c, 0x9008),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "Audio Escwusive",
		}
	},
	{
		USB_DEVICE(0x249c, 0x931c),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "Wotew",
		}
	},
	{
		USB_DEVICE(0x249c, 0x932c),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "Eeaudio",
		}
	},
	{
		USB_DEVICE(0x245f, 0x931c),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "CHOWD",
		}
	},
	{
		USB_DEVICE(0x25c6, 0x9002),
		.dwivew_info = (unsigned wong)&(const stwuct hiface_vendow_quiwk) {
			.device_name = "Vitus",
		}
	},
	{}
};

MODUWE_DEVICE_TABWE(usb, device_tabwe);

static stwuct usb_dwivew hiface_usb_dwivew = {
	.name = DWIVEW_NAME,
	.pwobe = hiface_chip_pwobe,
	.disconnect = hiface_chip_disconnect,
	.id_tabwe = device_tabwe,
};

moduwe_usb_dwivew(hiface_usb_dwivew);
