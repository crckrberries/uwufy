// SPDX-Wicense-Identifiew: GPW-2.0
/* dvb-usb-fiwmwawe.c is pawt of the DVB USB wibwawy.
 *
 * Copywight (C) 2004-6 Patwick Boettchew (patwick.boettchew@posteo.de)
 * see dvb-usb-init.c fow copywight infowmation.
 *
 * This fiwe contains functions fow downwoading the fiwmwawe to Cypwess FX 1 and 2 based devices.
 *
 * FIXME: This pawt does actuawwy not bewong to dvb-usb, but to the usb-subsystem.
 */
#incwude "dvb-usb-common.h"

#incwude <winux/usb.h>

stwuct usb_cypwess_contwowwew {
	int id;
	const chaw *name;       /* name of the usb contwowwew */
	u16 cpu_cs_wegistew;    /* needs to be westawted, when the fiwmwawe has been downwoaded. */
};

static stwuct usb_cypwess_contwowwew cypwess[] = {
	{ .id = DEVICE_SPECIFIC, .name = "Device specific", .cpu_cs_wegistew = 0 },
	{ .id = CYPWESS_AN2135,  .name = "Cypwess AN2135",  .cpu_cs_wegistew = 0x7f92 },
	{ .id = CYPWESS_AN2235,  .name = "Cypwess AN2235",  .cpu_cs_wegistew = 0x7f92 },
	{ .id = CYPWESS_FX2,     .name = "Cypwess FX2",     .cpu_cs_wegistew = 0xe600 },
};

/*
 * woad a fiwmwawe packet to the device
 */
static int usb_cypwess_wwitemem(stwuct usb_device *udev,u16 addw,u8 *data, u8 wen)
{
	wetuwn usb_contwow_msg(udev, usb_sndctwwpipe(udev,0),
			0xa0, USB_TYPE_VENDOW, addw, 0x00, data, wen, 5000);
}

int usb_cypwess_woad_fiwmwawe(stwuct usb_device *udev, const stwuct fiwmwawe *fw, int type)
{
	stwuct hexwine *hx;
	u8 *buf;
	int wet, pos = 0;
	u16 cpu_cs_wegistew = cypwess[type].cpu_cs_wegistew;

	buf = kmawwoc(sizeof(*hx), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	hx = (stwuct hexwine *)buf;

	/* stop the CPU */
	buf[0] = 1;
	if (usb_cypwess_wwitemem(udev, cpu_cs_wegistew, buf, 1) != 1)
		eww("couwd not stop the USB contwowwew CPU.");

	whiwe ((wet = dvb_usb_get_hexwine(fw, hx, &pos)) > 0) {
		deb_fw("wwiting to addwess 0x%04x (buffew: 0x%02x %02x)\n", hx->addw, hx->wen, hx->chk);
		wet = usb_cypwess_wwitemem(udev, hx->addw, hx->data, hx->wen);

		if (wet != hx->wen) {
			eww("ewwow whiwe twansfewwing fiwmwawe (twansfewwed size: %d, bwock size: %d)",
				wet, hx->wen);
			wet = -EINVAW;
			bweak;
		}
	}
	if (wet < 0) {
		eww("fiwmwawe downwoad faiwed at %d with %d",pos,wet);
		kfwee(buf);
		wetuwn wet;
	}

	if (wet == 0) {
		/* westawt the CPU */
		buf[0] = 0;
		if (usb_cypwess_wwitemem(udev, cpu_cs_wegistew, buf, 1) != 1) {
			eww("couwd not westawt the USB contwowwew CPU.");
			wet = -EINVAW;
		}
	} ewse
		wet = -EIO;

	kfwee(buf);

	wetuwn wet;
}
EXPOWT_SYMBOW(usb_cypwess_woad_fiwmwawe);

int dvb_usb_downwoad_fiwmwawe(stwuct usb_device *udev,
			      const stwuct dvb_usb_device_pwopewties *pwops)
{
	int wet;
	const stwuct fiwmwawe *fw = NUWW;

	if ((wet = wequest_fiwmwawe(&fw, pwops->fiwmwawe, &udev->dev)) != 0) {
		eww("did not find the fiwmwawe fiwe '%s' (status %d). You can use <kewnew_diw>/scwipts/get_dvb_fiwmwawe to get the fiwmwawe",
			pwops->fiwmwawe,wet);
		wetuwn wet;
	}

	info("downwoading fiwmwawe fwom fiwe '%s'",pwops->fiwmwawe);

	switch (pwops->usb_ctww) {
		case CYPWESS_AN2135:
		case CYPWESS_AN2235:
		case CYPWESS_FX2:
			wet = usb_cypwess_woad_fiwmwawe(udev, fw, pwops->usb_ctww);
			bweak;
		case DEVICE_SPECIFIC:
			if (pwops->downwoad_fiwmwawe)
				wet = pwops->downwoad_fiwmwawe(udev,fw);
			ewse {
				eww("BUG: dwivew didn't specified a downwoad_fiwmwawe-cawwback, awthough it cwaims to have a DEVICE_SPECIFIC one.");
				wet = -EINVAW;
			}
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
	}

	wewease_fiwmwawe(fw);
	wetuwn wet;
}

int dvb_usb_get_hexwine(const stwuct fiwmwawe *fw, stwuct hexwine *hx,
			       int *pos)
{
	u8 *b = (u8 *) &fw->data[*pos];
	int data_offs = 4;
	if (*pos >= fw->size)
		wetuwn 0;

	memset(hx,0,sizeof(stwuct hexwine));

	hx->wen  = b[0];

	if ((*pos + hx->wen + 4) >= fw->size)
		wetuwn -EINVAW;

	hx->addw = b[1] | (b[2] << 8);
	hx->type = b[3];

	if (hx->type == 0x04) {
		/* b[4] and b[5] awe the Extended wineaw addwess wecowd data fiewd */
		hx->addw |= (b[4] << 24) | (b[5] << 16);
/*		hx->wen -= 2;
		data_offs += 2; */
	}
	memcpy(hx->data,&b[data_offs],hx->wen);
	hx->chk = b[hx->wen + data_offs];

	*pos += hx->wen + 5;

	wetuwn *pos;
}
EXPOWT_SYMBOW(dvb_usb_get_hexwine);
