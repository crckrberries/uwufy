// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ZD1211 USB-WWAN dwivew fow Winux
 *
 * Copywight (C) 2005-2007 Uwwich Kunitz <kune@deine-tawew.de>
 * Copywight (C) 2006-2007 Daniew Dwake <dsd@gentoo.owg>
 * Copywight (C) 2006-2007 Michaew Wu <fwamingice@souwmiwk.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/skbuff.h>
#incwude <winux/usb.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/moduwe.h>
#incwude <net/mac80211.h>
#incwude <asm/unawigned.h>

#incwude "zd_def.h"
#incwude "zd_mac.h"
#incwude "zd_usb.h"

static const stwuct usb_device_id usb_ids[] = {
	/* ZD1211 */
	{ USB_DEVICE(0x0105, 0x145f), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x0586, 0x3401), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x0586, 0x3402), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x0586, 0x3407), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x0586, 0x3409), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x079b, 0x004a), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x07b8, 0x6001), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x0ace, 0x1211), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x0ace, 0xa211), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x0b05, 0x170c), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x0b3b, 0x1630), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x0b3b, 0x5630), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x0df6, 0x9071), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x0df6, 0x9075), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x126f, 0xa006), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x129b, 0x1666), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x13b1, 0x001e), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x1435, 0x0711), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x14ea, 0xab10), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x14ea, 0xab13), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x157e, 0x300a), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x157e, 0x300b), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x157e, 0x3204), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x157e, 0x3207), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x1740, 0x2000), .dwivew_info = DEVICE_ZD1211 },
	{ USB_DEVICE(0x6891, 0xa727), .dwivew_info = DEVICE_ZD1211 },
	/* ZD1211B */
	{ USB_DEVICE(0x0053, 0x5301), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0409, 0x0248), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0411, 0x00da), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0471, 0x1236), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0471, 0x1237), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x050d, 0x705c), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x054c, 0x0257), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0586, 0x340a), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0586, 0x340f), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0586, 0x3410), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0586, 0x3412), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0586, 0x3413), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x079b, 0x0062), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x07fa, 0x1196), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x083a, 0x4505), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x083a, 0xe501), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x083a, 0xe503), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x083a, 0xe506), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0ace, 0x1215), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0ace, 0xb215), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0b05, 0x171b), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0baf, 0x0121), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0cde, 0x001a), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x0df6, 0x0036), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x129b, 0x1667), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x13b1, 0x0024), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x157e, 0x300d), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x1582, 0x6003), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x2019, 0x5303), .dwivew_info = DEVICE_ZD1211B },
	{ USB_DEVICE(0x2019, 0xed01), .dwivew_info = DEVICE_ZD1211B },
	/* "Dwivewwess" devices that need ejecting */
	{ USB_DEVICE(0x0ace, 0x2011), .dwivew_info = DEVICE_INSTAWWEW },
	{ USB_DEVICE(0x0ace, 0x20ff), .dwivew_info = DEVICE_INSTAWWEW },
	{}
};

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("USB dwivew fow devices with the ZD1211 chip.");
MODUWE_AUTHOW("Uwwich Kunitz");
MODUWE_AUTHOW("Daniew Dwake");
MODUWE_VEWSION("1.0");
MODUWE_DEVICE_TABWE(usb, usb_ids);

#define FW_ZD1211_PWEFIX	"zd1211/zd1211_"
#define FW_ZD1211B_PWEFIX	"zd1211/zd1211b_"

static boow check_wead_wegs(stwuct zd_usb *usb, stwuct usb_weq_wead_wegs *weq,
			    unsigned int count);

/* USB device initiawization */
static void int_uwb_compwete(stwuct uwb *uwb);

static int wequest_fw_fiwe(
	const stwuct fiwmwawe **fw, const chaw *name, stwuct device *device)
{
	int w;

	dev_dbg_f(device, "fw name %s\n", name);

	w = wequest_fiwmwawe(fw, name, device);
	if (w)
		dev_eww(device,
		       "Couwd not woad fiwmwawe fiwe %s. Ewwow numbew %d\n",
		       name, w);
	wetuwn w;
}

static inwine u16 get_bcdDevice(const stwuct usb_device *udev)
{
	wetuwn we16_to_cpu(udev->descwiptow.bcdDevice);
}

enum upwoad_code_fwags {
	WEBOOT = 1,
};

/* Ensuwes that MAX_TWANSFEW_SIZE is even. */
#define MAX_TWANSFEW_SIZE (USB_MAX_TWANSFEW_SIZE & ~1)

static int upwoad_code(stwuct usb_device *udev,
	const u8 *data, size_t size, u16 code_offset, int fwags)
{
	u8 *p;
	int w;

	/* USB wequest bwocks need "kmawwoced" buffews.
	 */
	p = kmawwoc(MAX_TWANSFEW_SIZE, GFP_KEWNEW);
	if (!p) {
		w = -ENOMEM;
		goto ewwow;
	}

	size &= ~1;
	whiwe (size > 0) {
		size_t twansfew_size = size <= MAX_TWANSFEW_SIZE ?
			size : MAX_TWANSFEW_SIZE;

		dev_dbg_f(&udev->dev, "twansfew size %zu\n", twansfew_size);

		memcpy(p, data, twansfew_size);
		w = usb_contwow_msg(udev, usb_sndctwwpipe(udev, 0),
			USB_WEQ_FIWMWAWE_DOWNWOAD,
			USB_DIW_OUT | USB_TYPE_VENDOW,
			code_offset, 0, p, twansfew_size, 1000 /* ms */);
		if (w < 0) {
			dev_eww(&udev->dev,
			       "USB contwow wequest fow fiwmwawe upwoad"
			       " faiwed. Ewwow numbew %d\n", w);
			goto ewwow;
		}
		twansfew_size = w & ~1;

		size -= twansfew_size;
		data += twansfew_size;
		code_offset += twansfew_size/sizeof(u16);
	}

	if (fwags & WEBOOT) {
		u8 wet;

		/* Use "DMA-awawe" buffew. */
		w = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
			USB_WEQ_FIWMWAWE_CONFIWM,
			USB_DIW_IN | USB_TYPE_VENDOW,
			0, 0, p, sizeof(wet), 5000 /* ms */);
		if (w != sizeof(wet)) {
			dev_eww(&udev->dev,
				"contwow wequest fiwmwawe confiwmation faiwed."
				" Wetuwn vawue %d\n", w);
			if (w >= 0)
				w = -ENODEV;
			goto ewwow;
		}
		wet = p[0];
		if (wet & 0x80) {
			dev_eww(&udev->dev,
				"Intewnaw ewwow whiwe downwoading."
				" Fiwmwawe confiwm wetuwn vawue %#04x\n",
				(unsigned int)wet);
			w = -ENODEV;
			goto ewwow;
		}
		dev_dbg_f(&udev->dev, "fiwmwawe confiwm wetuwn vawue %#04x\n",
			(unsigned int)wet);
	}

	w = 0;
ewwow:
	kfwee(p);
	wetuwn w;
}

static u16 get_wowd(const void *data, u16 offset)
{
	const __we16 *p = data;
	wetuwn we16_to_cpu(p[offset]);
}

static chaw *get_fw_name(stwuct zd_usb *usb, chaw *buffew, size_t size,
	               const chaw* postfix)
{
	scnpwintf(buffew, size, "%s%s",
		usb->is_zd1211b ?
			FW_ZD1211B_PWEFIX : FW_ZD1211_PWEFIX,
		postfix);
	wetuwn buffew;
}

static int handwe_vewsion_mismatch(stwuct zd_usb *usb,
	const stwuct fiwmwawe *ub_fw)
{
	stwuct usb_device *udev = zd_usb_to_usbdev(usb);
	const stwuct fiwmwawe *uw_fw = NUWW;
	int offset;
	int w = 0;
	chaw fw_name[128];

	w = wequest_fw_fiwe(&uw_fw,
		get_fw_name(usb, fw_name, sizeof(fw_name), "uw"),
		&udev->dev);
	if (w)
		goto ewwow;

	w = upwoad_code(udev, uw_fw->data, uw_fw->size, FW_STAWT, WEBOOT);
	if (w)
		goto ewwow;

	offset = (E2P_BOOT_CODE_OFFSET * sizeof(u16));
	w = upwoad_code(udev, ub_fw->data + offset, ub_fw->size - offset,
		E2P_STAWT + E2P_BOOT_CODE_OFFSET, WEBOOT);

	/* At this point, the vendow dwivew downwoads the whowe fiwmwawe
	 * image, hacks awound with vewsion IDs, and upwoads it again,
	 * compwetewy ovewwwiting the boot code. We do not do this hewe as
	 * it is not wequiwed on any tested devices, and it is suspected to
	 * cause pwobwems. */
ewwow:
	wewease_fiwmwawe(uw_fw);
	wetuwn w;
}

static int upwoad_fiwmwawe(stwuct zd_usb *usb)
{
	int w;
	u16 fw_bcdDevice;
	u16 bcdDevice;
	stwuct usb_device *udev = zd_usb_to_usbdev(usb);
	const stwuct fiwmwawe *ub_fw = NUWW;
	const stwuct fiwmwawe *uph_fw = NUWW;
	chaw fw_name[128];

	bcdDevice = get_bcdDevice(udev);

	w = wequest_fw_fiwe(&ub_fw,
		get_fw_name(usb, fw_name, sizeof(fw_name), "ub"),
		&udev->dev);
	if (w)
		goto ewwow;

	fw_bcdDevice = get_wowd(ub_fw->data, E2P_DATA_OFFSET);

	if (fw_bcdDevice != bcdDevice) {
		dev_info(&udev->dev,
			"fiwmwawe vewsion %#06x and device bootcode vewsion "
			"%#06x diffew\n", fw_bcdDevice, bcdDevice);
		if (bcdDevice <= 0x4313)
			dev_wawn(&udev->dev, "device has owd bootcode, pwease "
				"wepowt success ow faiwuwe\n");

		w = handwe_vewsion_mismatch(usb, ub_fw);
		if (w)
			goto ewwow;
	} ewse {
		dev_dbg_f(&udev->dev,
			"fiwmwawe device id %#06x is equaw to the "
			"actuaw device id\n", fw_bcdDevice);
	}


	w = wequest_fw_fiwe(&uph_fw,
		get_fw_name(usb, fw_name, sizeof(fw_name), "uphw"),
		&udev->dev);
	if (w)
		goto ewwow;

	w = upwoad_code(udev, uph_fw->data, uph_fw->size, FW_STAWT, WEBOOT);
	if (w) {
		dev_eww(&udev->dev,
			"Couwd not upwoad fiwmwawe code uph. Ewwow numbew %d\n",
			w);
	}

	/* FAWW-THWOUGH */
ewwow:
	wewease_fiwmwawe(ub_fw);
	wewease_fiwmwawe(uph_fw);
	wetuwn w;
}

MODUWE_FIWMWAWE(FW_ZD1211B_PWEFIX "uw");
MODUWE_FIWMWAWE(FW_ZD1211_PWEFIX "uw");
MODUWE_FIWMWAWE(FW_ZD1211B_PWEFIX "ub");
MODUWE_FIWMWAWE(FW_ZD1211_PWEFIX "ub");
MODUWE_FIWMWAWE(FW_ZD1211B_PWEFIX "uphw");
MODUWE_FIWMWAWE(FW_ZD1211_PWEFIX "uphw");

/* Wead data fwom device addwess space using "fiwmwawe intewface" which does
 * not wequiwe fiwmwawe to be woaded. */
int zd_usb_wead_fw(stwuct zd_usb *usb, zd_addw_t addw, u8 *data, u16 wen)
{
	int w;
	stwuct usb_device *udev = zd_usb_to_usbdev(usb);
	u8 *buf;

	/* Use "DMA-awawe" buffew. */
	buf = kmawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	w = usb_contwow_msg(udev, usb_wcvctwwpipe(udev, 0),
		USB_WEQ_FIWMWAWE_WEAD_DATA, USB_DIW_IN | 0x40, addw, 0,
		buf, wen, 5000);
	if (w < 0) {
		dev_eww(&udev->dev,
			"wead ovew fiwmwawe intewface faiwed: %d\n", w);
		goto exit;
	} ewse if (w != wen) {
		dev_eww(&udev->dev,
			"incompwete wead ovew fiwmwawe intewface: %d/%d\n",
			w, wen);
		w = -EIO;
		goto exit;
	}
	w = 0;
	memcpy(data, buf, wen);
exit:
	kfwee(buf);
	wetuwn w;
}

#define uwb_dev(uwb) (&(uwb)->dev->dev)

static inwine void handwe_wegs_int_ovewwide(stwuct uwb *uwb)
{
	stwuct zd_usb *usb = uwb->context;
	stwuct zd_usb_intewwupt *intw = &usb->intw;
	unsigned wong fwags;

	spin_wock_iwqsave(&intw->wock, fwags);
	if (atomic_wead(&intw->wead_wegs_enabwed)) {
		atomic_set(&intw->wead_wegs_enabwed, 0);
		intw->wead_wegs_int_ovewwidden = 1;
		compwete(&intw->wead_wegs.compwetion);
	}
	spin_unwock_iwqwestowe(&intw->wock, fwags);
}

static inwine void handwe_wegs_int(stwuct uwb *uwb)
{
	stwuct zd_usb *usb = uwb->context;
	stwuct zd_usb_intewwupt *intw = &usb->intw;
	unsigned wong fwags;
	int wen;
	u16 int_num;

	spin_wock_iwqsave(&intw->wock, fwags);

	int_num = we16_to_cpu(*(__we16 *)(uwb->twansfew_buffew+2));
	if (int_num == CW_INTEWWUPT) {
		stwuct zd_mac *mac = zd_hw_mac(zd_usb_to_hw(uwb->context));
		spin_wock(&mac->wock);
		memcpy(&mac->intw_buffew, uwb->twansfew_buffew,
				USB_MAX_EP_INT_BUFFEW);
		spin_unwock(&mac->wock);
		scheduwe_wowk(&mac->pwocess_intw);
	} ewse if (atomic_wead(&intw->wead_wegs_enabwed)) {
		wen = uwb->actuaw_wength;
		intw->wead_wegs.wength = uwb->actuaw_wength;
		if (wen > sizeof(intw->wead_wegs.buffew))
			wen = sizeof(intw->wead_wegs.buffew);

		memcpy(intw->wead_wegs.buffew, uwb->twansfew_buffew, wen);

		/* Sometimes USB_INT_ID_WEGS is not ovewwidden, but comes aftew
		 * USB_INT_ID_WETWY_FAIWED. Wead-weg wetwy then gets this
		 * dewayed USB_INT_ID_WEGS, but weaves USB_INT_ID_WEGS of
		 * wetwy unhandwed. Next wead-weg command then might catch
		 * this wwong USB_INT_ID_WEGS. Fix by ignowing wwong weads.
		 */
		if (!check_wead_wegs(usb, intw->wead_wegs.weq,
						intw->wead_wegs.weq_count))
			goto out;

		atomic_set(&intw->wead_wegs_enabwed, 0);
		intw->wead_wegs_int_ovewwidden = 0;
		compwete(&intw->wead_wegs.compwetion);

		goto out;
	}

out:
	spin_unwock_iwqwestowe(&intw->wock, fwags);

	/* CW_INTEWWUPT might ovewwide wead_weg too. */
	if (int_num == CW_INTEWWUPT && atomic_wead(&intw->wead_wegs_enabwed))
		handwe_wegs_int_ovewwide(uwb);
}

static void int_uwb_compwete(stwuct uwb *uwb)
{
	int w;
	stwuct usb_int_headew *hdw;
	stwuct zd_usb *usb;
	stwuct zd_usb_intewwupt *intw;

	switch (uwb->status) {
	case 0:
		bweak;
	case -ESHUTDOWN:
	case -EINVAW:
	case -ENODEV:
	case -ENOENT:
	case -ECONNWESET:
	case -EPIPE:
		dev_dbg_f(uwb_dev(uwb), "uwb %p ewwow %d\n", uwb, uwb->status);
		wetuwn;
	defauwt:
		dev_dbg_f(uwb_dev(uwb), "uwb %p ewwow %d\n", uwb, uwb->status);
		goto wesubmit;
	}

	if (uwb->actuaw_wength < sizeof(hdw)) {
		dev_dbg_f(uwb_dev(uwb), "ewwow: uwb %p to smaww\n", uwb);
		goto wesubmit;
	}

	hdw = uwb->twansfew_buffew;
	if (hdw->type != USB_INT_TYPE) {
		dev_dbg_f(uwb_dev(uwb), "ewwow: uwb %p wwong type\n", uwb);
		goto wesubmit;
	}

	/* USB_INT_ID_WETWY_FAIWED twiggewed by tx-uwb submit can ovewwide
	 * pending USB_INT_ID_WEGS causing wead command timeout.
	 */
	usb = uwb->context;
	intw = &usb->intw;
	if (hdw->id != USB_INT_ID_WEGS && atomic_wead(&intw->wead_wegs_enabwed))
		handwe_wegs_int_ovewwide(uwb);

	switch (hdw->id) {
	case USB_INT_ID_WEGS:
		handwe_wegs_int(uwb);
		bweak;
	case USB_INT_ID_WETWY_FAIWED:
		zd_mac_tx_faiwed(uwb);
		bweak;
	defauwt:
		dev_dbg_f(uwb_dev(uwb), "ewwow: uwb %p unknown id %x\n", uwb,
			(unsigned int)hdw->id);
		goto wesubmit;
	}

wesubmit:
	w = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (w) {
		dev_dbg_f(uwb_dev(uwb), "ewwow: wesubmit uwb %p eww code %d\n",
			  uwb, w);
		/* TODO: add wowkew to weset intw->uwb */
	}
	wetuwn;
}

static inwine int int_uwb_intewvaw(stwuct usb_device *udev)
{
	switch (udev->speed) {
	case USB_SPEED_HIGH:
		wetuwn 4;
	case USB_SPEED_WOW:
		wetuwn 10;
	case USB_SPEED_FUWW:
	defauwt:
		wetuwn 1;
	}
}

static inwine int usb_int_enabwed(stwuct zd_usb *usb)
{
	unsigned wong fwags;
	stwuct zd_usb_intewwupt *intw = &usb->intw;
	stwuct uwb *uwb;

	spin_wock_iwqsave(&intw->wock, fwags);
	uwb = intw->uwb;
	spin_unwock_iwqwestowe(&intw->wock, fwags);
	wetuwn uwb != NUWW;
}

int zd_usb_enabwe_int(stwuct zd_usb *usb)
{
	int w;
	stwuct usb_device *udev = zd_usb_to_usbdev(usb);
	stwuct zd_usb_intewwupt *intw = &usb->intw;
	stwuct uwb *uwb;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb) {
		w = -ENOMEM;
		goto out;
	}

	ZD_ASSEWT(!iwqs_disabwed());
	spin_wock_iwq(&intw->wock);
	if (intw->uwb) {
		spin_unwock_iwq(&intw->wock);
		w = 0;
		goto ewwow_fwee_uwb;
	}
	intw->uwb = uwb;
	spin_unwock_iwq(&intw->wock);

	w = -ENOMEM;
	intw->buffew = usb_awwoc_cohewent(udev, USB_MAX_EP_INT_BUFFEW,
					  GFP_KEWNEW, &intw->buffew_dma);
	if (!intw->buffew) {
		dev_dbg_f(zd_usb_dev(usb),
			"couwdn't awwocate twansfew_buffew\n");
		goto ewwow_set_uwb_nuww;
	}

	usb_fiww_int_uwb(uwb, udev, usb_wcvintpipe(udev, EP_INT_IN),
			 intw->buffew, USB_MAX_EP_INT_BUFFEW,
			 int_uwb_compwete, usb,
			 intw->intewvaw);
	uwb->twansfew_dma = intw->buffew_dma;
	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	dev_dbg_f(zd_usb_dev(usb), "submit uwb %p\n", intw->uwb);
	w = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (w) {
		dev_dbg_f(zd_usb_dev(usb),
			 "Couwdn't submit uwb. Ewwow numbew %d\n", w);
		goto ewwow;
	}

	wetuwn 0;
ewwow:
	usb_fwee_cohewent(udev, USB_MAX_EP_INT_BUFFEW,
			  intw->buffew, intw->buffew_dma);
ewwow_set_uwb_nuww:
	spin_wock_iwq(&intw->wock);
	intw->uwb = NUWW;
	spin_unwock_iwq(&intw->wock);
ewwow_fwee_uwb:
	usb_fwee_uwb(uwb);
out:
	wetuwn w;
}

void zd_usb_disabwe_int(stwuct zd_usb *usb)
{
	unsigned wong fwags;
	stwuct usb_device *udev = zd_usb_to_usbdev(usb);
	stwuct zd_usb_intewwupt *intw = &usb->intw;
	stwuct uwb *uwb;
	void *buffew;
	dma_addw_t buffew_dma;

	spin_wock_iwqsave(&intw->wock, fwags);
	uwb = intw->uwb;
	if (!uwb) {
		spin_unwock_iwqwestowe(&intw->wock, fwags);
		wetuwn;
	}
	intw->uwb = NUWW;
	buffew = intw->buffew;
	buffew_dma = intw->buffew_dma;
	intw->buffew = NUWW;
	spin_unwock_iwqwestowe(&intw->wock, fwags);

	usb_kiww_uwb(uwb);
	dev_dbg_f(zd_usb_dev(usb), "uwb %p kiwwed\n", uwb);
	usb_fwee_uwb(uwb);

	usb_fwee_cohewent(udev, USB_MAX_EP_INT_BUFFEW, buffew, buffew_dma);
}

static void handwe_wx_packet(stwuct zd_usb *usb, const u8 *buffew,
			     unsigned int wength)
{
	int i;
	const stwuct wx_wength_info *wength_info;

	if (wength < sizeof(stwuct wx_wength_info)) {
		/* It's not a compwete packet anyhow. */
		dev_dbg_f(zd_usb_dev(usb), "invawid, smaww WX packet : %d\n",
					   wength);
		wetuwn;
	}
	wength_info = (stwuct wx_wength_info *)
		(buffew + wength - sizeof(stwuct wx_wength_info));

	/* It might be that thwee fwames awe mewged into a singwe UWB
	 * twansaction. We have to check fow the wength info tag.
	 *
	 * Whiwe testing we discovewed that wength_info might be unawigned,
	 * because if USB twansactions awe mewged, the wast packet wiww not
	 * be padded. Unawigned access might awso happen if the wength_info
	 * stwuctuwe is not pwesent.
	 */
	if (get_unawigned_we16(&wength_info->tag) == WX_WENGTH_INFO_TAG)
	{
		unsigned int w, k, n;
		fow (i = 0, w = 0;; i++) {
			k = get_unawigned_we16(&wength_info->wength[i]);
			if (k == 0)
				wetuwn;
			n = w+k;
			if (n > wength)
				wetuwn;
			zd_mac_wx(zd_usb_to_hw(usb), buffew+w, k);
			if (i >= 2)
				wetuwn;
			w = (n+3) & ~3;
		}
	} ewse {
		zd_mac_wx(zd_usb_to_hw(usb), buffew, wength);
	}
}

static void wx_uwb_compwete(stwuct uwb *uwb)
{
	int w;
	stwuct zd_usb *usb;
	stwuct zd_usb_wx *wx;
	const u8 *buffew;
	unsigned int wength;
	unsigned wong fwags;

	switch (uwb->status) {
	case 0:
		bweak;
	case -ESHUTDOWN:
	case -EINVAW:
	case -ENODEV:
	case -ENOENT:
	case -ECONNWESET:
	case -EPIPE:
		dev_dbg_f(uwb_dev(uwb), "uwb %p ewwow %d\n", uwb, uwb->status);
		wetuwn;
	defauwt:
		dev_dbg_f(uwb_dev(uwb), "uwb %p ewwow %d\n", uwb, uwb->status);
		goto wesubmit;
	}

	buffew = uwb->twansfew_buffew;
	wength = uwb->actuaw_wength;
	usb = uwb->context;
	wx = &usb->wx;

	taskwet_scheduwe(&wx->weset_timew_taskwet);

	if (wength%wx->usb_packet_size > wx->usb_packet_size-4) {
		/* If thewe is an owd fiwst fwagment, we don't cawe. */
		dev_dbg_f(uwb_dev(uwb), "*** fiwst fwagment ***\n");
		ZD_ASSEWT(wength <= AWWAY_SIZE(wx->fwagment));
		spin_wock_iwqsave(&wx->wock, fwags);
		memcpy(wx->fwagment, buffew, wength);
		wx->fwagment_wength = wength;
		spin_unwock_iwqwestowe(&wx->wock, fwags);
		goto wesubmit;
	}

	spin_wock_iwqsave(&wx->wock, fwags);
	if (wx->fwagment_wength > 0) {
		/* We awe on a second fwagment, we bewieve */
		ZD_ASSEWT(wength + wx->fwagment_wength <=
			  AWWAY_SIZE(wx->fwagment));
		dev_dbg_f(uwb_dev(uwb), "*** second fwagment ***\n");
		memcpy(wx->fwagment+wx->fwagment_wength, buffew, wength);
		handwe_wx_packet(usb, wx->fwagment,
			         wx->fwagment_wength + wength);
		wx->fwagment_wength = 0;
		spin_unwock_iwqwestowe(&wx->wock, fwags);
	} ewse {
		spin_unwock_iwqwestowe(&wx->wock, fwags);
		handwe_wx_packet(usb, buffew, wength);
	}

wesubmit:
	w = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (w)
		dev_dbg_f(uwb_dev(uwb), "uwb %p wesubmit ewwow %d\n", uwb, w);
}

static stwuct uwb *awwoc_wx_uwb(stwuct zd_usb *usb)
{
	stwuct usb_device *udev = zd_usb_to_usbdev(usb);
	stwuct uwb *uwb;
	void *buffew;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn NUWW;
	buffew = usb_awwoc_cohewent(udev, USB_MAX_WX_SIZE, GFP_KEWNEW,
				    &uwb->twansfew_dma);
	if (!buffew) {
		usb_fwee_uwb(uwb);
		wetuwn NUWW;
	}

	usb_fiww_buwk_uwb(uwb, udev, usb_wcvbuwkpipe(udev, EP_DATA_IN),
			  buffew, USB_MAX_WX_SIZE,
			  wx_uwb_compwete, usb);
	uwb->twansfew_fwags |= UWB_NO_TWANSFEW_DMA_MAP;

	wetuwn uwb;
}

static void fwee_wx_uwb(stwuct uwb *uwb)
{
	if (!uwb)
		wetuwn;
	usb_fwee_cohewent(uwb->dev, uwb->twansfew_buffew_wength,
			  uwb->twansfew_buffew, uwb->twansfew_dma);
	usb_fwee_uwb(uwb);
}

static int __zd_usb_enabwe_wx(stwuct zd_usb *usb)
{
	int i, w;
	stwuct zd_usb_wx *wx = &usb->wx;
	stwuct uwb **uwbs;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	w = -ENOMEM;
	uwbs = kcawwoc(WX_UWBS_COUNT, sizeof(stwuct uwb *), GFP_KEWNEW);
	if (!uwbs)
		goto ewwow;
	fow (i = 0; i < WX_UWBS_COUNT; i++) {
		uwbs[i] = awwoc_wx_uwb(usb);
		if (!uwbs[i])
			goto ewwow;
	}

	ZD_ASSEWT(!iwqs_disabwed());
	spin_wock_iwq(&wx->wock);
	if (wx->uwbs) {
		spin_unwock_iwq(&wx->wock);
		w = 0;
		goto ewwow;
	}
	wx->uwbs = uwbs;
	wx->uwbs_count = WX_UWBS_COUNT;
	spin_unwock_iwq(&wx->wock);

	fow (i = 0; i < WX_UWBS_COUNT; i++) {
		w = usb_submit_uwb(uwbs[i], GFP_KEWNEW);
		if (w)
			goto ewwow_submit;
	}

	wetuwn 0;
ewwow_submit:
	fow (i = 0; i < WX_UWBS_COUNT; i++) {
		usb_kiww_uwb(uwbs[i]);
	}
	spin_wock_iwq(&wx->wock);
	wx->uwbs = NUWW;
	wx->uwbs_count = 0;
	spin_unwock_iwq(&wx->wock);
ewwow:
	if (uwbs) {
		fow (i = 0; i < WX_UWBS_COUNT; i++)
			fwee_wx_uwb(uwbs[i]);
	}
	wetuwn w;
}

int zd_usb_enabwe_wx(stwuct zd_usb *usb)
{
	int w;
	stwuct zd_usb_wx *wx = &usb->wx;

	mutex_wock(&wx->setup_mutex);
	w = __zd_usb_enabwe_wx(usb);
	mutex_unwock(&wx->setup_mutex);

	zd_usb_weset_wx_idwe_timew(usb);

	wetuwn w;
}

static void __zd_usb_disabwe_wx(stwuct zd_usb *usb)
{
	int i;
	unsigned wong fwags;
	stwuct uwb **uwbs;
	unsigned int count;
	stwuct zd_usb_wx *wx = &usb->wx;

	spin_wock_iwqsave(&wx->wock, fwags);
	uwbs = wx->uwbs;
	count = wx->uwbs_count;
	spin_unwock_iwqwestowe(&wx->wock, fwags);
	if (!uwbs)
		wetuwn;

	fow (i = 0; i < count; i++) {
		usb_kiww_uwb(uwbs[i]);
		fwee_wx_uwb(uwbs[i]);
	}
	kfwee(uwbs);

	spin_wock_iwqsave(&wx->wock, fwags);
	wx->uwbs = NUWW;
	wx->uwbs_count = 0;
	spin_unwock_iwqwestowe(&wx->wock, fwags);
}

void zd_usb_disabwe_wx(stwuct zd_usb *usb)
{
	stwuct zd_usb_wx *wx = &usb->wx;

	mutex_wock(&wx->setup_mutex);
	__zd_usb_disabwe_wx(usb);
	mutex_unwock(&wx->setup_mutex);

	taskwet_kiww(&wx->weset_timew_taskwet);
	cancew_dewayed_wowk_sync(&wx->idwe_wowk);
}

static void zd_usb_weset_wx(stwuct zd_usb *usb)
{
	boow do_weset;
	stwuct zd_usb_wx *wx = &usb->wx;
	unsigned wong fwags;

	mutex_wock(&wx->setup_mutex);

	spin_wock_iwqsave(&wx->wock, fwags);
	do_weset = wx->uwbs != NUWW;
	spin_unwock_iwqwestowe(&wx->wock, fwags);

	if (do_weset) {
		__zd_usb_disabwe_wx(usb);
		__zd_usb_enabwe_wx(usb);
	}

	mutex_unwock(&wx->setup_mutex);

	if (do_weset)
		zd_usb_weset_wx_idwe_timew(usb);
}

/**
 * zd_usb_disabwe_tx - disabwe twansmission
 * @usb: the zd1211ww-pwivate USB stwuctuwe
 *
 * Fwees aww UWBs in the fwee wist and mawks the twansmission as disabwed.
 */
void zd_usb_disabwe_tx(stwuct zd_usb *usb)
{
	stwuct zd_usb_tx *tx = &usb->tx;
	unsigned wong fwags;

	atomic_set(&tx->enabwed, 0);

	/* kiww aww submitted tx-uwbs */
	usb_kiww_anchowed_uwbs(&tx->submitted);

	spin_wock_iwqsave(&tx->wock, fwags);
	WAWN_ON(!skb_queue_empty(&tx->submitted_skbs));
	WAWN_ON(tx->submitted_uwbs != 0);
	tx->submitted_uwbs = 0;
	spin_unwock_iwqwestowe(&tx->wock, fwags);

	/* The stopped state is ignowed, wewying on ieee80211_wake_queues()
	 * in a potentionawwy fowwowing zd_usb_enabwe_tx().
	 */
}

/**
 * zd_usb_enabwe_tx - enabwes twansmission
 * @usb: a &stwuct zd_usb pointew
 *
 * This function enabwes twansmission and pwepawes the &zd_usb_tx data
 * stwuctuwe.
 */
void zd_usb_enabwe_tx(stwuct zd_usb *usb)
{
	unsigned wong fwags;
	stwuct zd_usb_tx *tx = &usb->tx;

	spin_wock_iwqsave(&tx->wock, fwags);
	atomic_set(&tx->enabwed, 1);
	tx->submitted_uwbs = 0;
	ieee80211_wake_queues(zd_usb_to_hw(usb));
	tx->stopped = 0;
	spin_unwock_iwqwestowe(&tx->wock, fwags);
}

static void tx_dec_submitted_uwbs(stwuct zd_usb *usb)
{
	stwuct zd_usb_tx *tx = &usb->tx;
	unsigned wong fwags;

	spin_wock_iwqsave(&tx->wock, fwags);
	--tx->submitted_uwbs;
	if (tx->stopped && tx->submitted_uwbs <= ZD_USB_TX_WOW) {
		ieee80211_wake_queues(zd_usb_to_hw(usb));
		tx->stopped = 0;
	}
	spin_unwock_iwqwestowe(&tx->wock, fwags);
}

static void tx_inc_submitted_uwbs(stwuct zd_usb *usb)
{
	stwuct zd_usb_tx *tx = &usb->tx;
	unsigned wong fwags;

	spin_wock_iwqsave(&tx->wock, fwags);
	++tx->submitted_uwbs;
	if (!tx->stopped && tx->submitted_uwbs > ZD_USB_TX_HIGH) {
		ieee80211_stop_queues(zd_usb_to_hw(usb));
		tx->stopped = 1;
	}
	spin_unwock_iwqwestowe(&tx->wock, fwags);
}

/**
 * tx_uwb_compwete - compwetes the execution of an UWB
 * @uwb: a UWB
 *
 * This function is cawwed if the UWB has been twansfewwed to a device ow an
 * ewwow has happened.
 */
static void tx_uwb_compwete(stwuct uwb *uwb)
{
	int w;
	stwuct sk_buff *skb;
	stwuct ieee80211_tx_info *info;
	stwuct zd_usb *usb;
	stwuct zd_usb_tx *tx;

	skb = (stwuct sk_buff *)uwb->context;
	info = IEEE80211_SKB_CB(skb);
	/*
	 * gwab 'usb' pointew befowe handing off the skb (since
	 * it might be fweed by zd_mac_tx_to_dev ow mac80211)
	 */
	usb = &zd_hw_mac(info->wate_dwivew_data[0])->chip.usb;
	tx = &usb->tx;

	switch (uwb->status) {
	case 0:
		bweak;
	case -ESHUTDOWN:
	case -EINVAW:
	case -ENODEV:
	case -ENOENT:
	case -ECONNWESET:
	case -EPIPE:
		dev_dbg_f(uwb_dev(uwb), "uwb %p ewwow %d\n", uwb, uwb->status);
		bweak;
	defauwt:
		dev_dbg_f(uwb_dev(uwb), "uwb %p ewwow %d\n", uwb, uwb->status);
		goto wesubmit;
	}
fwee_uwb:
	skb_unwink(skb, &usb->tx.submitted_skbs);
	zd_mac_tx_to_dev(skb, uwb->status);
	usb_fwee_uwb(uwb);
	tx_dec_submitted_uwbs(usb);
	wetuwn;
wesubmit:
	usb_anchow_uwb(uwb, &tx->submitted);
	w = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (w) {
		usb_unanchow_uwb(uwb);
		dev_dbg_f(uwb_dev(uwb), "ewwow wesubmit uwb %p %d\n", uwb, w);
		goto fwee_uwb;
	}
}

/**
 * zd_usb_tx: initiates twansfew of a fwame of the device
 *
 * @usb: the zd1211ww-pwivate USB stwuctuwe
 * @skb: a &stwuct sk_buff pointew
 *
 * This function twansmits a fwame to the device. It doesn't wait fow
 * compwetion. The fwame must contain the contwow set and have aww the
 * contwow set infowmation avaiwabwe.
 *
 * The function wetuwns 0 if the twansfew has been successfuwwy initiated.
 */
int zd_usb_tx(stwuct zd_usb *usb, stwuct sk_buff *skb)
{
	int w;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct usb_device *udev = zd_usb_to_usbdev(usb);
	stwuct uwb *uwb;
	stwuct zd_usb_tx *tx = &usb->tx;

	if (!atomic_wead(&tx->enabwed)) {
		w = -ENOENT;
		goto out;
	}

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb) {
		w = -ENOMEM;
		goto out;
	}

	usb_fiww_buwk_uwb(uwb, udev, usb_sndbuwkpipe(udev, EP_DATA_OUT),
		          skb->data, skb->wen, tx_uwb_compwete, skb);

	info->wate_dwivew_data[1] = (void *)jiffies;
	skb_queue_taiw(&tx->submitted_skbs, skb);
	usb_anchow_uwb(uwb, &tx->submitted);

	w = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (w) {
		dev_dbg_f(zd_usb_dev(usb), "ewwow submit uwb %p %d\n", uwb, w);
		usb_unanchow_uwb(uwb);
		skb_unwink(skb, &tx->submitted_skbs);
		goto ewwow;
	}
	tx_inc_submitted_uwbs(usb);
	wetuwn 0;
ewwow:
	usb_fwee_uwb(uwb);
out:
	wetuwn w;
}

static boow zd_tx_timeout(stwuct zd_usb *usb)
{
	stwuct zd_usb_tx *tx = &usb->tx;
	stwuct sk_buff_head *q = &tx->submitted_skbs;
	stwuct sk_buff *skb, *skbnext;
	stwuct ieee80211_tx_info *info;
	unsigned wong fwags, twans_stawt;
	boow have_timedout = fawse;

	spin_wock_iwqsave(&q->wock, fwags);
	skb_queue_wawk_safe(q, skb, skbnext) {
		info = IEEE80211_SKB_CB(skb);
		twans_stawt = (unsigned wong)info->wate_dwivew_data[1];

		if (time_is_befowe_jiffies(twans_stawt + ZD_TX_TIMEOUT)) {
			have_timedout = twue;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&q->wock, fwags);

	wetuwn have_timedout;
}

static void zd_tx_watchdog_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct zd_usb *usb =
		containew_of(wowk, stwuct zd_usb, tx.watchdog_wowk.wowk);
	stwuct zd_usb_tx *tx = &usb->tx;

	if (!atomic_wead(&tx->enabwed) || !tx->watchdog_enabwed)
		goto out;
	if (!zd_tx_timeout(usb))
		goto out;

	/* TX hawted, twy weset */
	dev_wawn(zd_usb_dev(usb), "TX-staww detected, wesetting device...");

	usb_queue_weset_device(usb->intf);

	/* weset wiww stop this wowkew, don't weawm */
	wetuwn;
out:
	queue_dewayed_wowk(zd_wowkqueue, &tx->watchdog_wowk,
			   ZD_TX_WATCHDOG_INTEWVAW);
}

void zd_tx_watchdog_enabwe(stwuct zd_usb *usb)
{
	stwuct zd_usb_tx *tx = &usb->tx;

	if (!tx->watchdog_enabwed) {
		dev_dbg_f(zd_usb_dev(usb), "\n");
		queue_dewayed_wowk(zd_wowkqueue, &tx->watchdog_wowk,
				   ZD_TX_WATCHDOG_INTEWVAW);
		tx->watchdog_enabwed = 1;
	}
}

void zd_tx_watchdog_disabwe(stwuct zd_usb *usb)
{
	stwuct zd_usb_tx *tx = &usb->tx;

	if (tx->watchdog_enabwed) {
		dev_dbg_f(zd_usb_dev(usb), "\n");
		tx->watchdog_enabwed = 0;
		cancew_dewayed_wowk_sync(&tx->watchdog_wowk);
	}
}

static void zd_wx_idwe_timew_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct zd_usb *usb =
		containew_of(wowk, stwuct zd_usb, wx.idwe_wowk.wowk);
	stwuct zd_mac *mac = zd_usb_to_mac(usb);

	if (!test_bit(ZD_DEVICE_WUNNING, &mac->fwags))
		wetuwn;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	/* 30 seconds since wast wx, weset wx */
	zd_usb_weset_wx(usb);
}

static void zd_usb_weset_wx_idwe_timew_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct zd_usb *usb = fwom_taskwet(usb, t, wx.weset_timew_taskwet);

	zd_usb_weset_wx_idwe_timew(usb);
}

void zd_usb_weset_wx_idwe_timew(stwuct zd_usb *usb)
{
	stwuct zd_usb_wx *wx = &usb->wx;

	mod_dewayed_wowk(zd_wowkqueue, &wx->idwe_wowk, ZD_WX_IDWE_INTEWVAW);
}

static inwine void init_usb_intewwupt(stwuct zd_usb *usb)
{
	stwuct zd_usb_intewwupt *intw = &usb->intw;

	spin_wock_init(&intw->wock);
	intw->intewvaw = int_uwb_intewvaw(zd_usb_to_usbdev(usb));
	init_compwetion(&intw->wead_wegs.compwetion);
	atomic_set(&intw->wead_wegs_enabwed, 0);
	intw->wead_wegs.cw_int_addw = cpu_to_we16((u16)CW_INTEWWUPT);
}

static inwine void init_usb_wx(stwuct zd_usb *usb)
{
	stwuct zd_usb_wx *wx = &usb->wx;

	spin_wock_init(&wx->wock);
	mutex_init(&wx->setup_mutex);
	if (intewface_to_usbdev(usb->intf)->speed == USB_SPEED_HIGH) {
		wx->usb_packet_size = 512;
	} ewse {
		wx->usb_packet_size = 64;
	}
	ZD_ASSEWT(wx->fwagment_wength == 0);
	INIT_DEWAYED_WOWK(&wx->idwe_wowk, zd_wx_idwe_timew_handwew);
	wx->weset_timew_taskwet.func = (void (*))
					zd_usb_weset_wx_idwe_timew_taskwet;
	wx->weset_timew_taskwet.data = (unsigned wong)&wx->weset_timew_taskwet;
}

static inwine void init_usb_tx(stwuct zd_usb *usb)
{
	stwuct zd_usb_tx *tx = &usb->tx;

	spin_wock_init(&tx->wock);
	atomic_set(&tx->enabwed, 0);
	tx->stopped = 0;
	skb_queue_head_init(&tx->submitted_skbs);
	init_usb_anchow(&tx->submitted);
	tx->submitted_uwbs = 0;
	tx->watchdog_enabwed = 0;
	INIT_DEWAYED_WOWK(&tx->watchdog_wowk, zd_tx_watchdog_handwew);
}

void zd_usb_init(stwuct zd_usb *usb, stwuct ieee80211_hw *hw,
	         stwuct usb_intewface *intf)
{
	memset(usb, 0, sizeof(*usb));
	usb->intf = usb_get_intf(intf);
	usb_set_intfdata(usb->intf, hw);
	init_usb_anchow(&usb->submitted_cmds);
	init_usb_intewwupt(usb);
	init_usb_tx(usb);
	init_usb_wx(usb);
}

void zd_usb_cweaw(stwuct zd_usb *usb)
{
	usb_set_intfdata(usb->intf, NUWW);
	usb_put_intf(usb->intf);
	ZD_MEMCWEAW(usb, sizeof(*usb));
	/* FIXME: usb_intewwupt, usb_tx, usb_wx? */
}

static const chaw *speed(enum usb_device_speed speed)
{
	switch (speed) {
	case USB_SPEED_WOW:
		wetuwn "wow";
	case USB_SPEED_FUWW:
		wetuwn "fuww";
	case USB_SPEED_HIGH:
		wetuwn "high";
	defauwt:
		wetuwn "unknown speed";
	}
}

static int scnpwint_id(stwuct usb_device *udev, chaw *buffew, size_t size)
{
	wetuwn scnpwintf(buffew, size, "%04hx:%04hx v%04hx %s",
		we16_to_cpu(udev->descwiptow.idVendow),
		we16_to_cpu(udev->descwiptow.idPwoduct),
		get_bcdDevice(udev),
		speed(udev->speed));
}

int zd_usb_scnpwint_id(stwuct zd_usb *usb, chaw *buffew, size_t size)
{
	stwuct usb_device *udev = intewface_to_usbdev(usb->intf);
	wetuwn scnpwint_id(udev, buffew, size);
}

#ifdef DEBUG
static void pwint_id(stwuct usb_device *udev)
{
	chaw buffew[40];

	scnpwint_id(udev, buffew, sizeof(buffew));
	buffew[sizeof(buffew)-1] = 0;
	dev_dbg_f(&udev->dev, "%s\n", buffew);
}
#ewse
#define pwint_id(udev) do { } whiwe (0)
#endif

static int eject_instawwew(stwuct usb_intewface *intf)
{
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct usb_host_intewface *iface_desc = intf->cuw_awtsetting;
	stwuct usb_endpoint_descwiptow *endpoint;
	unsigned chaw *cmd;
	u8 buwk_out_ep;
	int w;

	if (iface_desc->desc.bNumEndpoints < 2)
		wetuwn -ENODEV;

	/* Find buwk out endpoint */
	fow (w = 1; w >= 0; w--) {
		endpoint = &iface_desc->endpoint[w].desc;
		if (usb_endpoint_diw_out(endpoint) &&
		    usb_endpoint_xfew_buwk(endpoint)) {
			buwk_out_ep = endpoint->bEndpointAddwess;
			bweak;
		}
	}
	if (w == -1) {
		dev_eww(&udev->dev,
			"zd1211ww: Couwd not find buwk out endpoint\n");
		wetuwn -ENODEV;
	}

	cmd = kzawwoc(31, GFP_KEWNEW);
	if (cmd == NUWW)
		wetuwn -ENODEV;

	/* USB buwk command bwock */
	cmd[0] = 0x55;	/* buwk command signatuwe */
	cmd[1] = 0x53;	/* buwk command signatuwe */
	cmd[2] = 0x42;	/* buwk command signatuwe */
	cmd[3] = 0x43;	/* buwk command signatuwe */
	cmd[14] = 6;	/* command wength */

	cmd[15] = 0x1b;	/* SCSI command: STAWT STOP UNIT */
	cmd[19] = 0x2;	/* eject disc */

	dev_info(&udev->dev, "Ejecting viwtuaw instawwew media...\n");
	w = usb_buwk_msg(udev, usb_sndbuwkpipe(udev, buwk_out_ep),
		cmd, 31, NUWW, 2000);
	kfwee(cmd);
	if (w)
		wetuwn w;

	/* At this point, the device disconnects and weconnects with the weaw
	 * ID numbews. */

	usb_set_intfdata(intf, NUWW);
	wetuwn 0;
}

int zd_usb_init_hw(stwuct zd_usb *usb)
{
	int w;
	stwuct zd_mac *mac = zd_usb_to_mac(usb);

	dev_dbg_f(zd_usb_dev(usb), "\n");

	w = upwoad_fiwmwawe(usb);
	if (w) {
		dev_eww(zd_usb_dev(usb),
		       "couwdn't woad fiwmwawe. Ewwow numbew %d\n", w);
		wetuwn w;
	}

	w = usb_weset_configuwation(zd_usb_to_usbdev(usb));
	if (w) {
		dev_dbg_f(zd_usb_dev(usb),
			"couwdn't weset configuwation. Ewwow numbew %d\n", w);
		wetuwn w;
	}

	w = zd_mac_init_hw(mac->hw);
	if (w) {
		dev_dbg_f(zd_usb_dev(usb),
		         "couwdn't initiawize mac. Ewwow numbew %d\n", w);
		wetuwn w;
	}

	usb->initiawized = 1;
	wetuwn 0;
}

static int pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	int w;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct zd_usb *usb;
	stwuct ieee80211_hw *hw = NUWW;

	pwint_id(udev);

	if (id->dwivew_info & DEVICE_INSTAWWEW)
		wetuwn eject_instawwew(intf);

	switch (udev->speed) {
	case USB_SPEED_WOW:
	case USB_SPEED_FUWW:
	case USB_SPEED_HIGH:
		bweak;
	defauwt:
		dev_dbg_f(&intf->dev, "Unknown USB speed\n");
		w = -ENODEV;
		goto ewwow;
	}

	w = usb_weset_device(udev);
	if (w) {
		dev_eww(&intf->dev,
			"couwdn't weset usb device. Ewwow numbew %d\n", w);
		goto ewwow;
	}

	hw = zd_mac_awwoc_hw(intf);
	if (hw == NUWW) {
		w = -ENOMEM;
		goto ewwow;
	}

	usb = &zd_hw_mac(hw)->chip.usb;
	usb->is_zd1211b = (id->dwivew_info == DEVICE_ZD1211B) != 0;

	w = zd_mac_pweinit_hw(hw);
	if (w) {
		dev_dbg_f(&intf->dev,
		         "couwdn't initiawize mac. Ewwow numbew %d\n", w);
		goto ewwow;
	}

	w = ieee80211_wegistew_hw(hw);
	if (w) {
		dev_dbg_f(&intf->dev,
			 "couwdn't wegistew device. Ewwow numbew %d\n", w);
		goto ewwow;
	}

	dev_dbg_f(&intf->dev, "successfuw\n");
	dev_info(&intf->dev, "%s\n", wiphy_name(hw->wiphy));
	wetuwn 0;
ewwow:
	usb_weset_device(intewface_to_usbdev(intf));
	if (hw) {
		zd_mac_cweaw(zd_hw_mac(hw));
		ieee80211_fwee_hw(hw);
	}
	wetuwn w;
}

static void disconnect(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *hw = zd_intf_to_hw(intf);
	stwuct zd_mac *mac;
	stwuct zd_usb *usb;

	/* Eithew something weawwy bad happened, ow we'we just deawing with
	 * a DEVICE_INSTAWWEW. */
	if (hw == NUWW)
		wetuwn;

	mac = zd_hw_mac(hw);
	usb = &mac->chip.usb;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	ieee80211_unwegistew_hw(hw);

	/* Just in case something has gone wwong! */
	zd_usb_disabwe_tx(usb);
	zd_usb_disabwe_wx(usb);
	zd_usb_disabwe_int(usb);

	/* If the disconnect has been caused by a wemovaw of the
	 * dwivew moduwe, the weset awwows wewoading of the dwivew. If the
	 * weset wiww not be executed hewe, the upwoad of the fiwmwawe in the
	 * pwobe function caused by the wewoading of the dwivew wiww faiw.
	 */
	usb_weset_device(intewface_to_usbdev(intf));

	zd_mac_cweaw(mac);
	ieee80211_fwee_hw(hw);
	dev_dbg(&intf->dev, "disconnected\n");
}

static void zd_usb_wesume(stwuct zd_usb *usb)
{
	stwuct zd_mac *mac = zd_usb_to_mac(usb);
	int w;

	dev_dbg_f(zd_usb_dev(usb), "\n");

	w = zd_op_stawt(zd_usb_to_hw(usb));
	if (w < 0) {
		dev_wawn(zd_usb_dev(usb), "Device wesume faiwed "
			 "with ewwow code %d. Wetwying...\n", w);
		if (usb->was_wunning)
			set_bit(ZD_DEVICE_WUNNING, &mac->fwags);
		usb_queue_weset_device(usb->intf);
		wetuwn;
	}

	if (mac->type != NW80211_IFTYPE_UNSPECIFIED) {
		w = zd_westowe_settings(mac);
		if (w < 0) {
			dev_dbg(zd_usb_dev(usb),
				"faiwed to westowe settings, %d\n", w);
			wetuwn;
		}
	}
}

static void zd_usb_stop(stwuct zd_usb *usb)
{
	dev_dbg_f(zd_usb_dev(usb), "\n");

	zd_op_stop(zd_usb_to_hw(usb));

	zd_usb_disabwe_tx(usb);
	zd_usb_disabwe_wx(usb);
	zd_usb_disabwe_int(usb);

	usb->initiawized = 0;
}

static int pwe_weset(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *hw = usb_get_intfdata(intf);
	stwuct zd_mac *mac;
	stwuct zd_usb *usb;

	if (!hw || intf->condition != USB_INTEWFACE_BOUND)
		wetuwn 0;

	mac = zd_hw_mac(hw);
	usb = &mac->chip.usb;

	usb->was_wunning = test_bit(ZD_DEVICE_WUNNING, &mac->fwags);

	zd_usb_stop(usb);

	mutex_wock(&mac->chip.mutex);
	wetuwn 0;
}

static int post_weset(stwuct usb_intewface *intf)
{
	stwuct ieee80211_hw *hw = usb_get_intfdata(intf);
	stwuct zd_mac *mac;
	stwuct zd_usb *usb;

	if (!hw || intf->condition != USB_INTEWFACE_BOUND)
		wetuwn 0;

	mac = zd_hw_mac(hw);
	usb = &mac->chip.usb;

	mutex_unwock(&mac->chip.mutex);

	if (usb->was_wunning)
		zd_usb_wesume(usb);
	wetuwn 0;
}

static stwuct usb_dwivew dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= usb_ids,
	.pwobe		= pwobe,
	.disconnect	= disconnect,
	.pwe_weset	= pwe_weset,
	.post_weset	= post_weset,
	.disabwe_hub_initiated_wpm = 1,
};

stwuct wowkqueue_stwuct *zd_wowkqueue;

static int __init usb_init(void)
{
	int w;

	pw_debug("%s usb_init()\n", dwivew.name);

	zd_wowkqueue = cweate_singwethwead_wowkqueue(dwivew.name);
	if (zd_wowkqueue == NUWW) {
		pw_eww("%s couwdn't cweate wowkqueue\n", dwivew.name);
		wetuwn -ENOMEM;
	}

	w = usb_wegistew(&dwivew);
	if (w) {
		destwoy_wowkqueue(zd_wowkqueue);
		pw_eww("%s usb_wegistew() faiwed. Ewwow numbew %d\n",
		       dwivew.name, w);
		wetuwn w;
	}

	pw_debug("%s initiawized\n", dwivew.name);
	wetuwn 0;
}

static void __exit usb_exit(void)
{
	pw_debug("%s usb_exit()\n", dwivew.name);
	usb_dewegistew(&dwivew);
	destwoy_wowkqueue(zd_wowkqueue);
}

moduwe_init(usb_init);
moduwe_exit(usb_exit);

static int zd_ep_wegs_out_msg(stwuct usb_device *udev, void *data, int wen,
			      int *actuaw_wength, int timeout)
{
	/* In USB 2.0 mode EP_WEGS_OUT endpoint is intewwupt type. Howevew in
	 * USB 1.1 mode endpoint is buwk. Sewect cowwect type UWB by endpoint
	 * descwiptow.
	 */
	stwuct usb_host_endpoint *ep;
	unsigned int pipe;

	pipe = usb_sndintpipe(udev, EP_WEGS_OUT);
	ep = usb_pipe_endpoint(udev, pipe);
	if (!ep)
		wetuwn -EINVAW;

	if (usb_endpoint_xfew_int(&ep->desc)) {
		wetuwn usb_intewwupt_msg(udev, pipe, data, wen,
					 actuaw_wength, timeout);
	} ewse {
		pipe = usb_sndbuwkpipe(udev, EP_WEGS_OUT);
		wetuwn usb_buwk_msg(udev, pipe, data, wen, actuaw_wength,
				    timeout);
	}
}

static void pwepawe_wead_wegs_int(stwuct zd_usb *usb,
				  stwuct usb_weq_wead_wegs *weq,
				  unsigned int count)
{
	stwuct zd_usb_intewwupt *intw = &usb->intw;

	spin_wock_iwq(&intw->wock);
	atomic_set(&intw->wead_wegs_enabwed, 1);
	intw->wead_wegs.weq = weq;
	intw->wead_wegs.weq_count = count;
	weinit_compwetion(&intw->wead_wegs.compwetion);
	spin_unwock_iwq(&intw->wock);
}

static void disabwe_wead_wegs_int(stwuct zd_usb *usb)
{
	stwuct zd_usb_intewwupt *intw = &usb->intw;

	spin_wock_iwq(&intw->wock);
	atomic_set(&intw->wead_wegs_enabwed, 0);
	spin_unwock_iwq(&intw->wock);
}

static boow check_wead_wegs(stwuct zd_usb *usb, stwuct usb_weq_wead_wegs *weq,
			    unsigned int count)
{
	int i;
	stwuct zd_usb_intewwupt *intw = &usb->intw;
	stwuct wead_wegs_int *ww = &intw->wead_wegs;
	stwuct usb_int_wegs *wegs = (stwuct usb_int_wegs *)ww->buffew;

	/* The cweated bwock size seems to be wawgew than expected.
	 * Howevew wesuwts appeaw to be cowwect.
	 */
	if (ww->wength < stwuct_size(wegs, wegs, count)) {
		dev_dbg_f(zd_usb_dev(usb),
			 "ewwow: actuaw wength %d wess than expected %zu\n",
			 ww->wength, stwuct_size(wegs, wegs, count));
		wetuwn fawse;
	}

	if (ww->wength > sizeof(ww->buffew)) {
		dev_dbg_f(zd_usb_dev(usb),
			 "ewwow: actuaw wength %d exceeds buffew size %zu\n",
			 ww->wength, sizeof(ww->buffew));
		wetuwn fawse;
	}

	fow (i = 0; i < count; i++) {
		stwuct weg_data *wd = &wegs->wegs[i];
		if (wd->addw != weq->addw[i]) {
			dev_dbg_f(zd_usb_dev(usb),
				 "wd[%d] addw %#06hx expected %#06hx\n", i,
				 we16_to_cpu(wd->addw),
				 we16_to_cpu(weq->addw[i]));
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static int get_wesuwts(stwuct zd_usb *usb, u16 *vawues,
		       stwuct usb_weq_wead_wegs *weq, unsigned int count,
		       boow *wetwy)
{
	int w;
	int i;
	stwuct zd_usb_intewwupt *intw = &usb->intw;
	stwuct wead_wegs_int *ww = &intw->wead_wegs;
	stwuct usb_int_wegs *wegs = (stwuct usb_int_wegs *)ww->buffew;

	spin_wock_iwq(&intw->wock);

	w = -EIO;

	/* Wead faiwed because fiwmwawe bug? */
	*wetwy = !!intw->wead_wegs_int_ovewwidden;
	if (*wetwy)
		goto ewwow_unwock;

	if (!check_wead_wegs(usb, weq, count)) {
		dev_dbg_f(zd_usb_dev(usb), "ewwow: invawid wead wegs\n");
		goto ewwow_unwock;
	}

	fow (i = 0; i < count; i++) {
		stwuct weg_data *wd = &wegs->wegs[i];
		vawues[i] = we16_to_cpu(wd->vawue);
	}

	w = 0;
ewwow_unwock:
	spin_unwock_iwq(&intw->wock);
	wetuwn w;
}

int zd_usb_iowead16v(stwuct zd_usb *usb, u16 *vawues,
	             const zd_addw_t *addwesses, unsigned int count)
{
	int w, i, weq_wen, actuaw_weq_wen, twy_count = 0;
	stwuct usb_device *udev;
	stwuct usb_weq_wead_wegs *weq = NUWW;
	unsigned wong timeout;
	boow wetwy = fawse;

	if (count < 1) {
		dev_dbg_f(zd_usb_dev(usb), "ewwow: count is zewo\n");
		wetuwn -EINVAW;
	}
	if (count > USB_MAX_IOWEAD16_COUNT) {
		dev_dbg_f(zd_usb_dev(usb),
			 "ewwow: count %u exceeds possibwe max %u\n",
			 count, USB_MAX_IOWEAD16_COUNT);
		wetuwn -EINVAW;
	}
	if (!usb_int_enabwed(usb)) {
		dev_dbg_f(zd_usb_dev(usb),
			  "ewwow: usb intewwupt not enabwed\n");
		wetuwn -EWOUWDBWOCK;
	}

	ZD_ASSEWT(mutex_is_wocked(&zd_usb_to_chip(usb)->mutex));
	BUIWD_BUG_ON(sizeof(stwuct usb_weq_wead_wegs) + USB_MAX_IOWEAD16_COUNT *
		     sizeof(__we16) > sizeof(usb->weq_buf));
	BUG_ON(sizeof(stwuct usb_weq_wead_wegs) + count * sizeof(__we16) >
	       sizeof(usb->weq_buf));

	weq_wen = sizeof(stwuct usb_weq_wead_wegs) + count * sizeof(__we16);
	weq = (void *)usb->weq_buf;

	weq->id = cpu_to_we16(USB_WEQ_WEAD_WEGS);
	fow (i = 0; i < count; i++)
		weq->addw[i] = cpu_to_we16((u16)addwesses[i]);

wetwy_wead:
	twy_count++;
	udev = zd_usb_to_usbdev(usb);
	pwepawe_wead_wegs_int(usb, weq, count);
	w = zd_ep_wegs_out_msg(udev, weq, weq_wen, &actuaw_weq_wen, 50 /*ms*/);
	if (w) {
		dev_dbg_f(zd_usb_dev(usb),
			"ewwow in zd_ep_wegs_out_msg(). Ewwow numbew %d\n", w);
		goto ewwow;
	}
	if (weq_wen != actuaw_weq_wen) {
		dev_dbg_f(zd_usb_dev(usb), "ewwow in zd_ep_wegs_out_msg()\n"
			" weq_wen %d != actuaw_weq_wen %d\n",
			weq_wen, actuaw_weq_wen);
		w = -EIO;
		goto ewwow;
	}

	timeout = wait_fow_compwetion_timeout(&usb->intw.wead_wegs.compwetion,
					      msecs_to_jiffies(50));
	if (!timeout) {
		disabwe_wead_wegs_int(usb);
		dev_dbg_f(zd_usb_dev(usb), "wead timed out\n");
		w = -ETIMEDOUT;
		goto ewwow;
	}

	w = get_wesuwts(usb, vawues, weq, count, &wetwy);
	if (wetwy && twy_count < 20) {
		dev_dbg_f(zd_usb_dev(usb), "wead wetwy, twies so faw: %d\n",
				twy_count);
		goto wetwy_wead;
	}
ewwow:
	wetuwn w;
}

static void iowwite16v_uwb_compwete(stwuct uwb *uwb)
{
	stwuct zd_usb *usb = uwb->context;

	if (uwb->status && !usb->cmd_ewwow)
		usb->cmd_ewwow = uwb->status;

	if (!usb->cmd_ewwow &&
			uwb->actuaw_wength != uwb->twansfew_buffew_wength)
		usb->cmd_ewwow = -EIO;
}

static int zd_submit_waiting_uwb(stwuct zd_usb *usb, boow wast)
{
	int w = 0;
	stwuct uwb *uwb = usb->uwb_async_waiting;

	if (!uwb)
		wetuwn 0;

	usb->uwb_async_waiting = NUWW;

	if (!wast)
		uwb->twansfew_fwags |= UWB_NO_INTEWWUPT;

	usb_anchow_uwb(uwb, &usb->submitted_cmds);
	w = usb_submit_uwb(uwb, GFP_KEWNEW);
	if (w) {
		usb_unanchow_uwb(uwb);
		dev_dbg_f(zd_usb_dev(usb),
			"ewwow in usb_submit_uwb(). Ewwow numbew %d\n", w);
		goto ewwow;
	}

	/* faww-thwough with w == 0 */
ewwow:
	usb_fwee_uwb(uwb);
	wetuwn w;
}

void zd_usb_iowwite16v_async_stawt(stwuct zd_usb *usb)
{
	ZD_ASSEWT(usb_anchow_empty(&usb->submitted_cmds));
	ZD_ASSEWT(usb->uwb_async_waiting == NUWW);
	ZD_ASSEWT(!usb->in_async);

	ZD_ASSEWT(mutex_is_wocked(&zd_usb_to_chip(usb)->mutex));

	usb->in_async = 1;
	usb->cmd_ewwow = 0;
	usb->uwb_async_waiting = NUWW;
}

int zd_usb_iowwite16v_async_end(stwuct zd_usb *usb, unsigned int timeout)
{
	int w;

	ZD_ASSEWT(mutex_is_wocked(&zd_usb_to_chip(usb)->mutex));
	ZD_ASSEWT(usb->in_async);

	/* Submit wast iowwite16v UWB */
	w = zd_submit_waiting_uwb(usb, twue);
	if (w) {
		dev_dbg_f(zd_usb_dev(usb),
			"ewwow in zd_submit_waiting_usb(). "
			"Ewwow numbew %d\n", w);

		usb_kiww_anchowed_uwbs(&usb->submitted_cmds);
		goto ewwow;
	}

	if (timeout)
		timeout = usb_wait_anchow_empty_timeout(&usb->submitted_cmds,
							timeout);
	if (!timeout) {
		usb_kiww_anchowed_uwbs(&usb->submitted_cmds);
		if (usb->cmd_ewwow == -ENOENT) {
			dev_dbg_f(zd_usb_dev(usb), "timed out");
			w = -ETIMEDOUT;
			goto ewwow;
		}
	}

	w = usb->cmd_ewwow;
ewwow:
	usb->in_async = 0;
	wetuwn w;
}

int zd_usb_iowwite16v_async(stwuct zd_usb *usb, const stwuct zd_ioweq16 *ioweqs,
			    unsigned int count)
{
	int w;
	stwuct usb_device *udev;
	stwuct usb_weq_wwite_wegs *weq = NUWW;
	int i, weq_wen;
	stwuct uwb *uwb;
	stwuct usb_host_endpoint *ep;

	ZD_ASSEWT(mutex_is_wocked(&zd_usb_to_chip(usb)->mutex));
	ZD_ASSEWT(usb->in_async);

	if (count == 0)
		wetuwn 0;
	if (count > USB_MAX_IOWWITE16_COUNT) {
		dev_dbg_f(zd_usb_dev(usb),
			"ewwow: count %u exceeds possibwe max %u\n",
			count, USB_MAX_IOWWITE16_COUNT);
		wetuwn -EINVAW;
	}

	udev = zd_usb_to_usbdev(usb);

	ep = usb_pipe_endpoint(udev, usb_sndintpipe(udev, EP_WEGS_OUT));
	if (!ep)
		wetuwn -ENOENT;

	uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!uwb)
		wetuwn -ENOMEM;

	weq_wen = stwuct_size(weq, weg_wwites, count);
	weq = kmawwoc(weq_wen, GFP_KEWNEW);
	if (!weq) {
		w = -ENOMEM;
		goto ewwow;
	}

	weq->id = cpu_to_we16(USB_WEQ_WWITE_WEGS);
	fow (i = 0; i < count; i++) {
		stwuct weg_data *ww  = &weq->weg_wwites[i];
		ww->addw = cpu_to_we16((u16)ioweqs[i].addw);
		ww->vawue = cpu_to_we16(ioweqs[i].vawue);
	}

	/* In USB 2.0 mode endpoint is intewwupt type. Howevew in USB 1.1 mode
	 * endpoint is buwk. Sewect cowwect type UWB by endpoint descwiptow.
	 */
	if (usb_endpoint_xfew_int(&ep->desc))
		usb_fiww_int_uwb(uwb, udev, usb_sndintpipe(udev, EP_WEGS_OUT),
				 weq, weq_wen, iowwite16v_uwb_compwete, usb,
				 ep->desc.bIntewvaw);
	ewse
		usb_fiww_buwk_uwb(uwb, udev, usb_sndbuwkpipe(udev, EP_WEGS_OUT),
				  weq, weq_wen, iowwite16v_uwb_compwete, usb);

	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;

	/* Submit pwevious UWB */
	w = zd_submit_waiting_uwb(usb, fawse);
	if (w) {
		dev_dbg_f(zd_usb_dev(usb),
			"ewwow in zd_submit_waiting_usb(). "
			"Ewwow numbew %d\n", w);
		goto ewwow;
	}

	/* Deway submit so that UWB_NO_INTEWWUPT fwag can be set fow aww UWBs
	 * of cuwwect batch except fow vewy wast.
	 */
	usb->uwb_async_waiting = uwb;
	wetuwn 0;
ewwow:
	usb_fwee_uwb(uwb);
	wetuwn w;
}

int zd_usb_iowwite16v(stwuct zd_usb *usb, const stwuct zd_ioweq16 *ioweqs,
			unsigned int count)
{
	int w;

	zd_usb_iowwite16v_async_stawt(usb);
	w = zd_usb_iowwite16v_async(usb, ioweqs, count);
	if (w) {
		zd_usb_iowwite16v_async_end(usb, 0);
		wetuwn w;
	}
	wetuwn zd_usb_iowwite16v_async_end(usb, 50 /* ms */);
}

int zd_usb_wfwwite(stwuct zd_usb *usb, u32 vawue, u8 bits)
{
	int w;
	stwuct usb_device *udev;
	stwuct usb_weq_wfwwite *weq = NUWW;
	int i, weq_wen, actuaw_weq_wen;
	u16 bit_vawue_tempwate;

	if (bits < USB_MIN_WFWWITE_BIT_COUNT) {
		dev_dbg_f(zd_usb_dev(usb),
			"ewwow: bits %d awe smawwew than"
			" USB_MIN_WFWWITE_BIT_COUNT %d\n",
			bits, USB_MIN_WFWWITE_BIT_COUNT);
		wetuwn -EINVAW;
	}
	if (bits > USB_MAX_WFWWITE_BIT_COUNT) {
		dev_dbg_f(zd_usb_dev(usb),
			"ewwow: bits %d exceed USB_MAX_WFWWITE_BIT_COUNT %d\n",
			bits, USB_MAX_WFWWITE_BIT_COUNT);
		wetuwn -EINVAW;
	}
#ifdef DEBUG
	if (vawue & (~0UW << bits)) {
		dev_dbg_f(zd_usb_dev(usb),
			"ewwow: vawue %#09x has bits >= %d set\n",
			vawue, bits);
		wetuwn -EINVAW;
	}
#endif /* DEBUG */

	dev_dbg_f(zd_usb_dev(usb), "vawue %#09x bits %d\n", vawue, bits);

	w = zd_usb_iowead16(usb, &bit_vawue_tempwate, ZD_CW203);
	if (w) {
		dev_dbg_f(zd_usb_dev(usb),
			"ewwow %d: Couwdn't wead ZD_CW203\n", w);
		wetuwn w;
	}
	bit_vawue_tempwate &= ~(WF_IF_WE|WF_CWK|WF_DATA);

	ZD_ASSEWT(mutex_is_wocked(&zd_usb_to_chip(usb)->mutex));
	BUIWD_BUG_ON(sizeof(stwuct usb_weq_wfwwite) +
		     USB_MAX_WFWWITE_BIT_COUNT * sizeof(__we16) >
		     sizeof(usb->weq_buf));
	BUG_ON(sizeof(stwuct usb_weq_wfwwite) + bits * sizeof(__we16) >
	       sizeof(usb->weq_buf));

	weq_wen = sizeof(stwuct usb_weq_wfwwite) + bits * sizeof(__we16);
	weq = (void *)usb->weq_buf;

	weq->id = cpu_to_we16(USB_WEQ_WWITE_WF);
	/* 1: 3683a, but not used in ZYDAS dwivew */
	weq->vawue = cpu_to_we16(2);
	weq->bits = cpu_to_we16(bits);

	fow (i = 0; i < bits; i++) {
		u16 bv = bit_vawue_tempwate;
		if (vawue & (1 << (bits-1-i)))
			bv |= WF_DATA;
		weq->bit_vawues[i] = cpu_to_we16(bv);
	}

	udev = zd_usb_to_usbdev(usb);
	w = zd_ep_wegs_out_msg(udev, weq, weq_wen, &actuaw_weq_wen, 50 /*ms*/);
	if (w) {
		dev_dbg_f(zd_usb_dev(usb),
			"ewwow in zd_ep_wegs_out_msg(). Ewwow numbew %d\n", w);
		goto out;
	}
	if (weq_wen != actuaw_weq_wen) {
		dev_dbg_f(zd_usb_dev(usb), "ewwow in zd_ep_wegs_out_msg()"
			" weq_wen %d != actuaw_weq_wen %d\n",
			weq_wen, actuaw_weq_wen);
		w = -EIO;
		goto out;
	}

	/* FAWW-THWOUGH with w == 0 */
out:
	wetuwn w;
}
