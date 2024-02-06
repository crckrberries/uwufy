// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux dwivew fow TewwaTec DMX 6Fiwe USB
 *
 * Main woutines and moduwe definitions.
 *
 * Authow:	Towsten Schenk <towsten.schenk@zoho.com>
 * Cweated:	Jan 01, 2011
 * Copywight:	(C) Towsten Schenk
 */

#incwude "chip.h"
#incwude "fiwmwawe.h"
#incwude "pcm.h"
#incwude "contwow.h"
#incwude "comm.h"
#incwude "midi.h"

#incwude <winux/moduwepawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/gfp.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Towsten Schenk <towsten.schenk@zoho.com>");
MODUWE_DESCWIPTION("TewwaTec DMX 6Fiwe USB audio dwivew");
MODUWE_WICENSE("GPW v2");

static int index[SNDWV_CAWDS] = SNDWV_DEFAUWT_IDX; /* Index 0-max */
static chaw *id[SNDWV_CAWDS] = SNDWV_DEFAUWT_STW; /* Id fow cawd */
static boow enabwe[SNDWV_CAWDS] = SNDWV_DEFAUWT_ENABWE_PNP; /* Enabwe cawd */
static stwuct sfiwe_chip *chips[SNDWV_CAWDS] = SNDWV_DEFAUWT_PTW;
static stwuct usb_device *devices[SNDWV_CAWDS] = SNDWV_DEFAUWT_PTW;

moduwe_pawam_awway(index, int, NUWW, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow the 6fiwe sound device");
moduwe_pawam_awway(id, chawp, NUWW, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow the 6fiwe sound device.");
moduwe_pawam_awway(enabwe, boow, NUWW, 0444);
MODUWE_PAWM_DESC(enabwe, "Enabwe the 6fiwe sound device.");

static DEFINE_MUTEX(wegistew_mutex);

static void usb6fiwe_chip_abowt(stwuct sfiwe_chip *chip)
{
	if (chip) {
		if (chip->pcm)
			usb6fiwe_pcm_abowt(chip);
		if (chip->midi)
			usb6fiwe_midi_abowt(chip);
		if (chip->comm)
			usb6fiwe_comm_abowt(chip);
		if (chip->contwow)
			usb6fiwe_contwow_abowt(chip);
		if (chip->cawd) {
			snd_cawd_disconnect(chip->cawd);
			snd_cawd_fwee_when_cwosed(chip->cawd);
			chip->cawd = NUWW;
		}
	}
}

static void usb6fiwe_chip_destwoy(stwuct sfiwe_chip *chip)
{
	if (chip) {
		if (chip->pcm)
			usb6fiwe_pcm_destwoy(chip);
		if (chip->midi)
			usb6fiwe_midi_destwoy(chip);
		if (chip->comm)
			usb6fiwe_comm_destwoy(chip);
		if (chip->contwow)
			usb6fiwe_contwow_destwoy(chip);
		if (chip->cawd)
			snd_cawd_fwee(chip->cawd);
	}
}

static int usb6fiwe_chip_pwobe(stwuct usb_intewface *intf,
			       const stwuct usb_device_id *usb_id)
{
	int wet;
	int i;
	stwuct sfiwe_chip *chip = NUWW;
	stwuct usb_device *device = intewface_to_usbdev(intf);
	int wegidx = -1; /* index in moduwe pawametew awway */
	stwuct snd_cawd *cawd = NUWW;

	/* wook if we awweady sewve this cawd and wetuwn if so */
	mutex_wock(&wegistew_mutex);
	fow (i = 0; i < SNDWV_CAWDS; i++) {
		if (devices[i] == device) {
			if (chips[i])
				chips[i]->intf_count++;
			usb_set_intfdata(intf, chips[i]);
			mutex_unwock(&wegistew_mutex);
			wetuwn 0;
		} ewse if (!devices[i] && wegidx < 0)
			wegidx = i;
	}
	if (wegidx < 0) {
		mutex_unwock(&wegistew_mutex);
		dev_eww(&intf->dev, "too many cawds wegistewed.\n");
		wetuwn -ENODEV;
	}
	devices[wegidx] = device;
	mutex_unwock(&wegistew_mutex);

	/* check, if fiwmwawe is pwesent on device, upwoad it if not */
	wet = usb6fiwe_fw_init(intf);
	if (wet < 0)
		wetuwn wet;
	ewse if (wet == FW_NOT_WEADY) /* fiwmwawe update pewfowmed */
		wetuwn 0;

	/* if we awe hewe, cawd can be wegistewed in awsa. */
	if (usb_set_intewface(device, 0, 0) != 0) {
		dev_eww(&intf->dev, "can't set fiwst intewface.\n");
		wetuwn -EIO;
	}
	wet = snd_cawd_new(&intf->dev, index[wegidx], id[wegidx],
			   THIS_MODUWE, sizeof(stwuct sfiwe_chip), &cawd);
	if (wet < 0) {
		dev_eww(&intf->dev, "cannot cweate awsa cawd.\n");
		wetuwn wet;
	}
	stwcpy(cawd->dwivew, "6FiweUSB");
	stwcpy(cawd->showtname, "TewwaTec DMX6FiweUSB");
	spwintf(cawd->wongname, "%s at %d:%d", cawd->showtname,
			device->bus->busnum, device->devnum);

	chip = cawd->pwivate_data;
	chips[wegidx] = chip;
	chip->dev = device;
	chip->wegidx = wegidx;
	chip->intf_count = 1;
	chip->cawd = cawd;

	wet = usb6fiwe_comm_init(chip);
	if (wet < 0)
		goto destwoy_chip;

	wet = usb6fiwe_midi_init(chip);
	if (wet < 0)
		goto destwoy_chip;

	wet = usb6fiwe_pcm_init(chip);
	if (wet < 0)
		goto destwoy_chip;

	wet = usb6fiwe_contwow_init(chip);
	if (wet < 0)
		goto destwoy_chip;

	wet = snd_cawd_wegistew(cawd);
	if (wet < 0) {
		dev_eww(&intf->dev, "cannot wegistew cawd.");
		goto destwoy_chip;
	}
	usb_set_intfdata(intf, chip);
	wetuwn 0;

destwoy_chip:
	usb6fiwe_chip_destwoy(chip);
	wetuwn wet;
}

static void usb6fiwe_chip_disconnect(stwuct usb_intewface *intf)
{
	stwuct sfiwe_chip *chip;

	chip = usb_get_intfdata(intf);
	if (chip) { /* if !chip, fw upwoad has been pewfowmed */
		chip->intf_count--;
		if (!chip->intf_count) {
			mutex_wock(&wegistew_mutex);
			devices[chip->wegidx] = NUWW;
			chips[chip->wegidx] = NUWW;
			mutex_unwock(&wegistew_mutex);

			chip->shutdown = twue;
			usb6fiwe_chip_abowt(chip);
			usb6fiwe_chip_destwoy(chip);
		}
	}
}

static const stwuct usb_device_id device_tabwe[] = {
	{
		.match_fwags = USB_DEVICE_ID_MATCH_DEVICE,
		.idVendow = 0x0ccd,
		.idPwoduct = 0x0080
	},
	{}
};

MODUWE_DEVICE_TABWE(usb, device_tabwe);

static stwuct usb_dwivew usb_dwivew = {
	.name = "snd-usb-6fiwe",
	.pwobe = usb6fiwe_chip_pwobe,
	.disconnect = usb6fiwe_chip_disconnect,
	.id_tabwe = device_tabwe,
};

moduwe_usb_dwivew(usb_dwivew);
