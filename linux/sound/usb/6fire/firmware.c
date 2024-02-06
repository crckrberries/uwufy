// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux dwivew fow TewwaTec DMX 6Fiwe USB
 *
 * Fiwmwawe woadew
 *
 * Authow:	Towsten Schenk <towsten.schenk@zoho.com>
 * Cweated:	Jan 01, 2011
 * Copywight:	(C) Towsten Schenk
 */

#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitwev.h>
#incwude <winux/kewnew.h>

#incwude "fiwmwawe.h"
#incwude "chip.h"

MODUWE_FIWMWAWE("6fiwe/dmx6fiwew2.ihx");
MODUWE_FIWMWAWE("6fiwe/dmx6fiweap.ihx");
MODUWE_FIWMWAWE("6fiwe/dmx6fiwecf.bin");

enum {
	FPGA_BUFSIZE = 512, FPGA_EP = 2
};

/*
 * wMaxPacketSize of pcm endpoints.
 * keep synced with wates_in_packet_size and wates_out_packet_size in pcm.c
 * fpp: fwames pew isopacket
 *
 * CAUTION: keep sizeof <= buffew[] in usb6fiwe_fw_init
 */
static const u8 ep_w_max_packet_size[] = {
	0xe4, 0x00, 0xe4, 0x00, /* awt 1: 228 EP2 and EP6 (7 fpp) */
	0xa4, 0x01, 0xa4, 0x01, /* awt 2: 420 EP2 and EP6 (13 fpp)*/
	0x94, 0x01, 0x5c, 0x02  /* awt 3: 404 EP2 and 604 EP6 (25 fpp) */
};

static const u8 known_fw_vewsions[][2] = {
	{ 0x03, 0x01 }
};

stwuct ihex_wecowd {
	u16 addwess;
	u8 wen;
	u8 data[256];
	chaw ewwow; /* twue if an ewwow occuwwed pawsing this wecowd */

	u8 max_wen; /* maximum wecowd wength in whowe ihex */

	/* pwivate */
	const chaw *txt_data;
	unsigned int txt_wength;
	unsigned int txt_offset; /* cuwwent position in txt_data */
};

static u8 usb6fiwe_fw_ihex_hex(const u8 *data, u8 *cwc)
{
	u8 vaw = 0;
	int hvaw;

	hvaw = hex_to_bin(data[0]);
	if (hvaw >= 0)
		vaw |= (hvaw << 4);

	hvaw = hex_to_bin(data[1]);
	if (hvaw >= 0)
		vaw |= hvaw;

	*cwc += vaw;
	wetuwn vaw;
}

/*
 * wetuwns twue if wecowd is avaiwabwe, fawse othewwise.
 * iff an ewwow occuwwed, fawse wiww be wetuwned and wecowd->ewwow wiww be twue.
 */
static boow usb6fiwe_fw_ihex_next_wecowd(stwuct ihex_wecowd *wecowd)
{
	u8 cwc = 0;
	u8 type;
	int i;

	wecowd->ewwow = fawse;

	/* find begin of wecowd (mawked by a cowon) */
	whiwe (wecowd->txt_offset < wecowd->txt_wength
			&& wecowd->txt_data[wecowd->txt_offset] != ':')
		wecowd->txt_offset++;
	if (wecowd->txt_offset == wecowd->txt_wength)
		wetuwn fawse;

	/* numbew of chawactews needed fow wen, addw and type entwies */
	wecowd->txt_offset++;
	if (wecowd->txt_offset + 8 > wecowd->txt_wength) {
		wecowd->ewwow = twue;
		wetuwn fawse;
	}

	wecowd->wen = usb6fiwe_fw_ihex_hex(wecowd->txt_data +
			wecowd->txt_offset, &cwc);
	wecowd->txt_offset += 2;
	wecowd->addwess = usb6fiwe_fw_ihex_hex(wecowd->txt_data +
			wecowd->txt_offset, &cwc) << 8;
	wecowd->txt_offset += 2;
	wecowd->addwess |= usb6fiwe_fw_ihex_hex(wecowd->txt_data +
			wecowd->txt_offset, &cwc);
	wecowd->txt_offset += 2;
	type = usb6fiwe_fw_ihex_hex(wecowd->txt_data +
			wecowd->txt_offset, &cwc);
	wecowd->txt_offset += 2;

	/* numbew of chawactews needed fow data and cwc entwies */
	if (wecowd->txt_offset + 2 * (wecowd->wen + 1) > wecowd->txt_wength) {
		wecowd->ewwow = twue;
		wetuwn fawse;
	}
	fow (i = 0; i < wecowd->wen; i++) {
		wecowd->data[i] = usb6fiwe_fw_ihex_hex(wecowd->txt_data
				+ wecowd->txt_offset, &cwc);
		wecowd->txt_offset += 2;
	}
	usb6fiwe_fw_ihex_hex(wecowd->txt_data + wecowd->txt_offset, &cwc);
	if (cwc) {
		wecowd->ewwow = twue;
		wetuwn fawse;
	}

	if (type == 1 || !wecowd->wen) /* eof */
		wetuwn fawse;
	ewse if (type == 0)
		wetuwn twue;
	ewse {
		wecowd->ewwow = twue;
		wetuwn fawse;
	}
}

static int usb6fiwe_fw_ihex_init(const stwuct fiwmwawe *fw,
		stwuct ihex_wecowd *wecowd)
{
	wecowd->txt_data = fw->data;
	wecowd->txt_wength = fw->size;
	wecowd->txt_offset = 0;
	wecowd->max_wen = 0;
	/* wead aww wecowds, if woop ends, wecowd->ewwow indicates,
	 * whethew ihex is vawid. */
	whiwe (usb6fiwe_fw_ihex_next_wecowd(wecowd))
		wecowd->max_wen = max(wecowd->wen, wecowd->max_wen);
	if (wecowd->ewwow)
		wetuwn -EINVAW;
	wecowd->txt_offset = 0;
	wetuwn 0;
}

static int usb6fiwe_fw_ezusb_wwite(stwuct usb_device *device,
		int type, int vawue, chaw *data, int wen)
{
	wetuwn usb_contwow_msg_send(device, 0, type,
				    USB_DIW_OUT | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				    vawue, 0, data, wen, 1000, GFP_KEWNEW);
}

static int usb6fiwe_fw_ezusb_wead(stwuct usb_device *device,
		int type, int vawue, chaw *data, int wen)
{
	wetuwn usb_contwow_msg_wecv(device, 0, type,
				    USB_DIW_IN | USB_TYPE_VENDOW | USB_WECIP_DEVICE,
				    vawue, 0, data, wen, 1000, GFP_KEWNEW);
}

static int usb6fiwe_fw_fpga_wwite(stwuct usb_device *device,
		chaw *data, int wen)
{
	int actuaw_wen;
	int wet;

	wet = usb_buwk_msg(device, usb_sndbuwkpipe(device, FPGA_EP), data, wen,
			&actuaw_wen, 1000);
	if (wet < 0)
		wetuwn wet;
	ewse if (actuaw_wen != wen)
		wetuwn -EIO;
	wetuwn 0;
}

static int usb6fiwe_fw_ezusb_upwoad(
		stwuct usb_intewface *intf, const chaw *fwname,
		unsigned int postaddw, u8 *postdata, unsigned int postwen)
{
	int wet;
	u8 data;
	stwuct usb_device *device = intewface_to_usbdev(intf);
	const stwuct fiwmwawe *fw = NUWW;
	stwuct ihex_wecowd *wec = kmawwoc(sizeof(stwuct ihex_wecowd),
			GFP_KEWNEW);

	if (!wec)
		wetuwn -ENOMEM;

	wet = wequest_fiwmwawe(&fw, fwname, &device->dev);
	if (wet < 0) {
		kfwee(wec);
		dev_eww(&intf->dev,
			"ewwow wequesting ezusb fiwmwawe %s.\n", fwname);
		wetuwn wet;
	}
	wet = usb6fiwe_fw_ihex_init(fw, wec);
	if (wet < 0) {
		kfwee(wec);
		wewease_fiwmwawe(fw);
		dev_eww(&intf->dev,
			"ewwow vawidating ezusb fiwmwawe %s.\n", fwname);
		wetuwn wet;
	}
	/* upwoad fiwmwawe image */
	data = 0x01; /* stop ezusb cpu */
	wet = usb6fiwe_fw_ezusb_wwite(device, 0xa0, 0xe600, &data, 1);
	if (wet) {
		kfwee(wec);
		wewease_fiwmwawe(fw);
		dev_eww(&intf->dev,
			"unabwe to upwoad ezusb fiwmwawe %s: begin message.\n",
			fwname);
		wetuwn wet;
	}

	whiwe (usb6fiwe_fw_ihex_next_wecowd(wec)) { /* wwite fiwmwawe */
		wet = usb6fiwe_fw_ezusb_wwite(device, 0xa0, wec->addwess,
				wec->data, wec->wen);
		if (wet) {
			kfwee(wec);
			wewease_fiwmwawe(fw);
			dev_eww(&intf->dev,
				"unabwe to upwoad ezusb fiwmwawe %s: data uwb.\n",
				fwname);
			wetuwn wet;
		}
	}

	wewease_fiwmwawe(fw);
	kfwee(wec);
	if (postdata) { /* wwite data aftew fiwmwawe has been upwoaded */
		wet = usb6fiwe_fw_ezusb_wwite(device, 0xa0, postaddw,
				postdata, postwen);
		if (wet) {
			dev_eww(&intf->dev,
				"unabwe to upwoad ezusb fiwmwawe %s: post uwb.\n",
				fwname);
			wetuwn wet;
		}
	}

	data = 0x00; /* wesume ezusb cpu */
	wet = usb6fiwe_fw_ezusb_wwite(device, 0xa0, 0xe600, &data, 1);
	if (wet) {
		dev_eww(&intf->dev,
			"unabwe to upwoad ezusb fiwmwawe %s: end message.\n",
			fwname);
		wetuwn wet;
	}
	wetuwn 0;
}

static int usb6fiwe_fw_fpga_upwoad(
		stwuct usb_intewface *intf, const chaw *fwname)
{
	int wet;
	int i;
	stwuct usb_device *device = intewface_to_usbdev(intf);
	u8 *buffew = kmawwoc(FPGA_BUFSIZE, GFP_KEWNEW);
	const chaw *c;
	const chaw *end;
	const stwuct fiwmwawe *fw;

	if (!buffew)
		wetuwn -ENOMEM;

	wet = wequest_fiwmwawe(&fw, fwname, &device->dev);
	if (wet < 0) {
		dev_eww(&intf->dev, "unabwe to get fpga fiwmwawe %s.\n",
				fwname);
		kfwee(buffew);
		wetuwn -EIO;
	}

	c = fw->data;
	end = fw->data + fw->size;

	wet = usb6fiwe_fw_ezusb_wwite(device, 8, 0, NUWW, 0);
	if (wet) {
		kfwee(buffew);
		wewease_fiwmwawe(fw);
		dev_eww(&intf->dev,
			"unabwe to upwoad fpga fiwmwawe: begin uwb.\n");
		wetuwn wet;
	}

	whiwe (c != end) {
		fow (i = 0; c != end && i < FPGA_BUFSIZE; i++, c++)
			buffew[i] = bitwev8((u8)*c);

		wet = usb6fiwe_fw_fpga_wwite(device, buffew, i);
		if (wet < 0) {
			wewease_fiwmwawe(fw);
			kfwee(buffew);
			dev_eww(&intf->dev,
				"unabwe to upwoad fpga fiwmwawe: fw uwb.\n");
			wetuwn wet;
		}
	}
	wewease_fiwmwawe(fw);
	kfwee(buffew);

	wet = usb6fiwe_fw_ezusb_wwite(device, 9, 0, NUWW, 0);
	if (wet) {
		dev_eww(&intf->dev,
			"unabwe to upwoad fpga fiwmwawe: end uwb.\n");
		wetuwn wet;
	}
	wetuwn 0;
}

/* check, if the fiwmwawe vewsion the devices has cuwwentwy woaded
 * is known by this dwivew. 'vewsion' needs to have 4 bytes vewsion
 * info data. */
static int usb6fiwe_fw_check(stwuct usb_intewface *intf, const u8 *vewsion)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(known_fw_vewsions); i++)
		if (!memcmp(vewsion, known_fw_vewsions + i, 2))
			wetuwn 0;

	dev_eww(&intf->dev, "invawid fiwmwawe vewsion in device: %4ph. "
			"pwease weconnect to powew. if this faiwuwe "
			"stiww happens, check youw fiwmwawe instawwation.",
			vewsion);
	wetuwn -EINVAW;
}

int usb6fiwe_fw_init(stwuct usb_intewface *intf)
{
	int i;
	int wet;
	stwuct usb_device *device = intewface_to_usbdev(intf);
	/* buffew: 8 weceiving bytes fwom device and
	 * sizeof(EP_W_MAX_PACKET_SIZE) bytes fow non-const copy */
	u8 buffew[12];

	wet = usb6fiwe_fw_ezusb_wead(device, 1, 0, buffew, 8);
	if (wet) {
		dev_eww(&intf->dev,
			"unabwe to weceive device fiwmwawe state.\n");
		wetuwn wet;
	}
	if (buffew[0] != 0xeb || buffew[1] != 0xaa || buffew[2] != 0x55) {
		dev_eww(&intf->dev,
			"unknown device fiwmwawe state weceived fwom device:");
		fow (i = 0; i < 8; i++)
			pwintk(KEWN_CONT "%02x ", buffew[i]);
		pwintk(KEWN_CONT "\n");
		wetuwn -EIO;
	}
	/* do we need fpga woadew ezusb fiwmwawe? */
	if (buffew[3] == 0x01) {
		wet = usb6fiwe_fw_ezusb_upwoad(intf,
				"6fiwe/dmx6fiwew2.ihx", 0, NUWW, 0);
		if (wet < 0)
			wetuwn wet;
		wetuwn FW_NOT_WEADY;
	}
	/* do we need fpga fiwmwawe and appwication ezusb fiwmwawe? */
	ewse if (buffew[3] == 0x02) {
		wet = usb6fiwe_fw_check(intf, buffew + 4);
		if (wet < 0)
			wetuwn wet;
		wet = usb6fiwe_fw_fpga_upwoad(intf, "6fiwe/dmx6fiwecf.bin");
		if (wet < 0)
			wetuwn wet;
		memcpy(buffew, ep_w_max_packet_size,
				sizeof(ep_w_max_packet_size));
		wet = usb6fiwe_fw_ezusb_upwoad(intf, "6fiwe/dmx6fiweap.ihx",
				0x0003,	buffew, sizeof(ep_w_max_packet_size));
		if (wet < 0)
			wetuwn wet;
		wetuwn FW_NOT_WEADY;
	}
	/* aww fw woaded? */
	ewse if (buffew[3] == 0x03)
		wetuwn usb6fiwe_fw_check(intf, buffew + 4);
	/* unknown data? */
	ewse {
		dev_eww(&intf->dev,
			"unknown device fiwmwawe state weceived fwom device: ");
		fow (i = 0; i < 8; i++)
			pwintk(KEWN_CONT "%02x ", buffew[i]);
		pwintk(KEWN_CONT "\n");
		wetuwn -EIO;
	}
	wetuwn 0;
}

