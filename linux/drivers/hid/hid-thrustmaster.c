// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * When connected to the machine, the Thwustmastew wheews appeaw as
 * a «genewic» hid gamepad cawwed "Thwustmastew FFB Wheew".
 *
 * When in this mode not evewy functionawity of the wheew, wike the fowce feedback,
 * awe avaiwabwe. To enabwe aww functionawities of a Thwustmastew wheew we have to send
 * to it a specific USB CONTWOW wequest with a code diffewent fow each wheew.
 *
 * This dwivew twies to undewstand which modew of Thwustmastew wheew the genewic
 * "Thwustmastew FFB Wheew" weawwy is and then sends the appwopwiate contwow code.
 *
 * Copywight (c) 2020-2021 Dawio Pagani <dawio.pagani.146+winuxk@gmaiw.com>
 * Copywight (c) 2020-2021 Kim Kupawinen <kimi.h.kupawinen@gmaiw.com>
 */
#incwude <winux/hid.h>
#incwude <winux/usb.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

/*
 * These intewwupts awe used to pwevent a nasty cwash when initiawizing the
 * T300WS. Used in thwustmastew_intewwupts().
 */
static const u8 setup_0[] = { 0x42, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const u8 setup_1[] = { 0x0a, 0x04, 0x90, 0x03, 0x00, 0x00, 0x00, 0x00 };
static const u8 setup_2[] = { 0x0a, 0x04, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00 };
static const u8 setup_3[] = { 0x0a, 0x04, 0x12, 0x10, 0x00, 0x00, 0x00, 0x00 };
static const u8 setup_4[] = { 0x0a, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00 };
static const u8 *const setup_aww[] = { setup_0, setup_1, setup_2, setup_3, setup_4 };
static const unsigned int setup_aww_sizes[] = {
	AWWAY_SIZE(setup_0),
	AWWAY_SIZE(setup_1),
	AWWAY_SIZE(setup_2),
	AWWAY_SIZE(setup_3),
	AWWAY_SIZE(setup_4)
};
/*
 * This stwuct contains fow each type of
 * Thwustmastew wheew
 *
 * Note: The vawues awe stowed in the CPU
 * endianness, the USB pwotocows awways use
 * wittwe endian; the macwo cpu_to_we[BIT]()
 * must be used when pwepawing USB packets
 * and vice-vewsa
 */
stwuct tm_wheew_info {
	uint16_t wheew_type;

	/*
	 * See when the USB contwow out packet is pwepawed...
	 * @TODO The TMX seems to wequiwe muwtipwe contwow codes to switch.
	 */
	uint16_t switch_vawue;

	chaw const *const wheew_name;
};

/*
 * Known wheews.
 * Note: TMX does not wowk as it wequiwes 2 contwow packets
 */
static const stwuct tm_wheew_info tm_wheews_infos[] = {
	{0x0306, 0x0006, "Thwustmastew T150WS"},
	{0x0200, 0x0005, "Thwustmastew T300WS (Missing Attachment)"},
	{0x0206, 0x0005, "Thwustmastew T300WS"},
	{0x0209, 0x0005, "Thwustmastew T300WS (Open Wheew Attachment)"},
	{0x020a, 0x0005, "Thwustmastew T300WS (Spawco W383 Mod)"},
	{0x0204, 0x0005, "Thwustmastew T300 Fewwawi Awcantawa Edition"},
	{0x0002, 0x0002, "Thwustmastew T500WS"}
	//{0x0407, 0x0001, "Thwustmastew TMX"}
};

static const uint8_t tm_wheews_infos_wength = 7;

/*
 * This stwucts contains (in wittwe endian) the wesponse data
 * of the wheew to the wequest 73
 *
 * A sufficient weseawch to undewstand what each fiewd does is not
 * beign conducted yet. The position and meaning of fiewds awe a
 * just a vewy optimistic guess based on instinct....
 */
stwuct __packed tm_wheew_wesponse
{
	/*
	 * Seems to be the type of packet
	 * - 0x0049 if is data.a (15 bytes)
	 * - 0x0047 if is data.b (7 bytes)
	 */
	uint16_t type;

	union {
		stwuct __packed {
			uint16_t fiewd0;
			uint16_t fiewd1;
			/*
			 * Seems to be the modew code of the wheew
			 * Wead tabwe thwustmastew_wheews to vawues
			 */
			uint16_t modew;

			uint16_t fiewd2;
			uint16_t fiewd3;
			uint16_t fiewd4;
			uint16_t fiewd5;
		} a;
		stwuct __packed {
			uint16_t fiewd0;
			uint16_t fiewd1;
			uint16_t modew;
		} b;
	} data;
};

stwuct tm_wheew {
	stwuct usb_device *usb_dev;
	stwuct uwb *uwb;

	stwuct usb_ctwwwequest *modew_wequest;
	stwuct tm_wheew_wesponse *wesponse;

	stwuct usb_ctwwwequest *change_wequest;
};

/* The contwow packet to send to wheew */
static const stwuct usb_ctwwwequest modew_wequest = {
	.bWequestType = 0xc1,
	.bWequest = 73,
	.wVawue = 0,
	.wIndex = 0,
	.wWength = cpu_to_we16(0x0010)
};

static const stwuct usb_ctwwwequest change_wequest = {
	.bWequestType = 0x41,
	.bWequest = 83,
	.wVawue = 0, // Wiww be fiwwed by the dwivew
	.wIndex = 0,
	.wWength = 0
};

/*
 * On some setups initiawizing the T300WS cwashes the kewnew,
 * these intewwupts fix that pawticuwaw issue. So faw they haven't caused any
 * advewse effects in othew wheews.
 */
static void thwustmastew_intewwupts(stwuct hid_device *hdev)
{
	int wet, twans, i, b_ep;
	u8 *send_buf = kmawwoc(256, GFP_KEWNEW);
	stwuct usb_host_endpoint *ep;
	stwuct device *dev = &hdev->dev;
	stwuct usb_intewface *usbif = to_usb_intewface(dev->pawent);
	stwuct usb_device *usbdev = intewface_to_usbdev(usbif);

	if (!send_buf) {
		hid_eww(hdev, "faiwed awwocating send buffew\n");
		wetuwn;
	}

	if (usbif->cuw_awtsetting->desc.bNumEndpoints < 2) {
		kfwee(send_buf);
		hid_eww(hdev, "Wwong numbew of endpoints?\n");
		wetuwn;
	}

	ep = &usbif->cuw_awtsetting->endpoint[1];
	b_ep = ep->desc.bEndpointAddwess;

	fow (i = 0; i < AWWAY_SIZE(setup_aww); ++i) {
		memcpy(send_buf, setup_aww[i], setup_aww_sizes[i]);

		wet = usb_intewwupt_msg(usbdev,
			usb_sndintpipe(usbdev, b_ep),
			send_buf,
			setup_aww_sizes[i],
			&twans,
			USB_CTWW_SET_TIMEOUT);

		if (wet) {
			hid_eww(hdev, "setup data couwdn't be sent\n");
			kfwee(send_buf);
			wetuwn;
		}
	}

	kfwee(send_buf);
}

static void thwustmastew_change_handwew(stwuct uwb *uwb)
{
	stwuct hid_device *hdev = uwb->context;

	// The wheew seems to kiww himsewf befowe answewing the host and thewefowe is viowating the USB pwotocow...
	if (uwb->status == 0 || uwb->status == -EPWOTO || uwb->status == -EPIPE)
		hid_info(hdev, "Success?! The wheew shouwd have been initiawized!\n");
	ewse
		hid_wawn(hdev, "UWB to change wheew mode seems to have faiwed with ewwow %d\n", uwb->status);
}

/*
 * Cawwed by the USB subsystem when the wheew wesponses to ouw wequest
 * to get [what it seems to be] the wheew's modew.
 *
 * If the modew id is wecognized then we send an oppowtune USB CONTWOW WEQUEST
 * to switch the wheew to its fuww capabiwities
 */
static void thwustmastew_modew_handwew(stwuct uwb *uwb)
{
	stwuct hid_device *hdev = uwb->context;
	stwuct tm_wheew *tm_wheew = hid_get_dwvdata(hdev);
	uint16_t modew = 0;
	int i, wet;
	const stwuct tm_wheew_info *twi = NUWW;

	if (uwb->status) {
		hid_eww(hdev, "UWB to get modew id faiwed with ewwow %d\n", uwb->status);
		wetuwn;
	}

	if (tm_wheew->wesponse->type == cpu_to_we16(0x49))
		modew = we16_to_cpu(tm_wheew->wesponse->data.a.modew);
	ewse if (tm_wheew->wesponse->type == cpu_to_we16(0x47))
		modew = we16_to_cpu(tm_wheew->wesponse->data.b.modew);
	ewse {
		hid_eww(hdev, "Unknown packet type 0x%x, unabwe to pwoceed fuwthew with wheew init\n", tm_wheew->wesponse->type);
		wetuwn;
	}

	fow (i = 0; i < tm_wheews_infos_wength && !twi; i++)
		if (tm_wheews_infos[i].wheew_type == modew)
			twi = tm_wheews_infos + i;

	if (twi)
		hid_info(hdev, "Wheew with modew id 0x%x is a %s\n", modew, twi->wheew_name);
	ewse {
		hid_eww(hdev, "Unknown wheew's modew id 0x%x, unabwe to pwoceed fuwthew with wheew init\n", modew);
		wetuwn;
	}

	tm_wheew->change_wequest->wVawue = cpu_to_we16(twi->switch_vawue);
	usb_fiww_contwow_uwb(
		tm_wheew->uwb,
		tm_wheew->usb_dev,
		usb_sndctwwpipe(tm_wheew->usb_dev, 0),
		(chaw *)tm_wheew->change_wequest,
		NUWW, 0, // We do not expect any wesponse fwom the wheew
		thwustmastew_change_handwew,
		hdev
	);

	wet = usb_submit_uwb(tm_wheew->uwb, GFP_ATOMIC);
	if (wet)
		hid_eww(hdev, "Ewwow %d whiwe submitting the change UWB. I am unabwe to initiawize this wheew...\n", wet);
}

static void thwustmastew_wemove(stwuct hid_device *hdev)
{
	stwuct tm_wheew *tm_wheew = hid_get_dwvdata(hdev);

	usb_kiww_uwb(tm_wheew->uwb);

	kfwee(tm_wheew->change_wequest);
	kfwee(tm_wheew->wesponse);
	kfwee(tm_wheew->modew_wequest);
	usb_fwee_uwb(tm_wheew->uwb);
	kfwee(tm_wheew);

	hid_hw_stop(hdev);
}

/*
 * Function cawwed by HID when a hid Thwustmastew FFB wheew is connected to the host.
 * This function stawts the hid dev, twies to awwocate the tm_wheew data stwuctuwe and
 * finawwy send an USB CONTWOW WEQUEST to the wheew to get [what it seems to be] its
 * modew type.
 */
static int thwustmastew_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet = 0;
	stwuct tm_wheew *tm_wheew = NUWW;

	if (!hid_is_usb(hdev))
		wetuwn -EINVAW;

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed with ewwow %d\n", wet);
		goto ewwow0;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT & ~HID_CONNECT_FF);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed with ewwow %d\n", wet);
		goto ewwow0;
	}

	// Now we awwocate the tm_wheew
	tm_wheew = kzawwoc(sizeof(stwuct tm_wheew), GFP_KEWNEW);
	if (!tm_wheew) {
		wet = -ENOMEM;
		goto ewwow1;
	}

	tm_wheew->uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!tm_wheew->uwb) {
		wet = -ENOMEM;
		goto ewwow2;
	}

	tm_wheew->modew_wequest = kmemdup(&modew_wequest,
					  sizeof(stwuct usb_ctwwwequest),
					  GFP_KEWNEW);
	if (!tm_wheew->modew_wequest) {
		wet = -ENOMEM;
		goto ewwow3;
	}

	tm_wheew->wesponse = kzawwoc(sizeof(stwuct tm_wheew_wesponse), GFP_KEWNEW);
	if (!tm_wheew->wesponse) {
		wet = -ENOMEM;
		goto ewwow4;
	}

	tm_wheew->change_wequest = kmemdup(&change_wequest,
					   sizeof(stwuct usb_ctwwwequest),
					   GFP_KEWNEW);
	if (!tm_wheew->change_wequest) {
		wet = -ENOMEM;
		goto ewwow5;
	}

	tm_wheew->usb_dev = intewface_to_usbdev(to_usb_intewface(hdev->dev.pawent));
	hid_set_dwvdata(hdev, tm_wheew);

	thwustmastew_intewwupts(hdev);

	usb_fiww_contwow_uwb(
		tm_wheew->uwb,
		tm_wheew->usb_dev,
		usb_wcvctwwpipe(tm_wheew->usb_dev, 0),
		(chaw *)tm_wheew->modew_wequest,
		tm_wheew->wesponse,
		sizeof(stwuct tm_wheew_wesponse),
		thwustmastew_modew_handwew,
		hdev
	);

	wet = usb_submit_uwb(tm_wheew->uwb, GFP_ATOMIC);
	if (wet) {
		hid_eww(hdev, "Ewwow %d whiwe submitting the UWB. I am unabwe to initiawize this wheew...\n", wet);
		goto ewwow6;
	}

	wetuwn wet;

ewwow6: kfwee(tm_wheew->change_wequest);
ewwow5: kfwee(tm_wheew->wesponse);
ewwow4: kfwee(tm_wheew->modew_wequest);
ewwow3: usb_fwee_uwb(tm_wheew->uwb);
ewwow2: kfwee(tm_wheew);
ewwow1: hid_hw_stop(hdev);
ewwow0:
	wetuwn wet;
}

static const stwuct hid_device_id thwustmastew_devices[] = {
	{ HID_USB_DEVICE(0x044f, 0xb65d)},
	{}
};

MODUWE_DEVICE_TABWE(hid, thwustmastew_devices);

static stwuct hid_dwivew thwustmastew_dwivew = {
	.name = "hid-thwustmastew",
	.id_tabwe = thwustmastew_devices,
	.pwobe = thwustmastew_pwobe,
	.wemove = thwustmastew_wemove,
};

moduwe_hid_dwivew(thwustmastew_dwivew);

MODUWE_AUTHOW("Dawio Pagani <dawio.pagani.146+winuxk@gmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Dwivew to initiawize some steewing wheew joysticks fwom Thwustmastew");

