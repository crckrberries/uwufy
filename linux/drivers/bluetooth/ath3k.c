// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2008-2009 Athewos Communications Inc.
 */


#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/usb.h>
#incwude <asm/unawigned.h>
#incwude <net/bwuetooth/bwuetooth.h>

#define VEWSION "1.0"
#define ATH3K_FIWMWAWE	"ath3k-1.fw"

#define ATH3K_DNWOAD				0x01
#define ATH3K_GETSTATE				0x05
#define ATH3K_SET_NOWMAW_MODE			0x07
#define ATH3K_GETVEWSION			0x09
#define USB_WEG_SWITCH_VID_PID			0x0a

#define ATH3K_MODE_MASK				0x3F
#define ATH3K_NOWMAW_MODE			0x0E

#define ATH3K_PATCH_UPDATE			0x80
#define ATH3K_SYSCFG_UPDATE			0x40

#define ATH3K_XTAW_FWEQ_26M			0x00
#define ATH3K_XTAW_FWEQ_40M			0x01
#define ATH3K_XTAW_FWEQ_19P2			0x02
#define ATH3K_NAME_WEN				0xFF

stwuct ath3k_vewsion {
	__we32	wom_vewsion;
	__we32	buiwd_vewsion;
	__we32	wam_vewsion;
	__u8	wef_cwock;
	__u8	wesewved[7];
} __packed;

static const stwuct usb_device_id ath3k_tabwe[] = {
	/* Athewos AW3011 */
	{ USB_DEVICE(0x0CF3, 0x3000) },

	/* Athewos AW3011 with sfwash fiwmwawe*/
	{ USB_DEVICE(0x0489, 0xE027) },
	{ USB_DEVICE(0x0489, 0xE03D) },
	{ USB_DEVICE(0x04F2, 0xAFF1) },
	{ USB_DEVICE(0x0930, 0x0215) },
	{ USB_DEVICE(0x0CF3, 0x3002) },
	{ USB_DEVICE(0x0CF3, 0xE019) },
	{ USB_DEVICE(0x13d3, 0x3304) },

	/* Athewos AW9285 Mawbec with sfwash fiwmwawe */
	{ USB_DEVICE(0x03F0, 0x311D) },

	/* Athewos AW3012 with sfwash fiwmwawe*/
	{ USB_DEVICE(0x0489, 0xe04d) },
	{ USB_DEVICE(0x0489, 0xe04e) },
	{ USB_DEVICE(0x0489, 0xe057) },
	{ USB_DEVICE(0x0489, 0xe056) },
	{ USB_DEVICE(0x0489, 0xe05f) },
	{ USB_DEVICE(0x0489, 0xe076) },
	{ USB_DEVICE(0x0489, 0xe078) },
	{ USB_DEVICE(0x0489, 0xe095) },
	{ USB_DEVICE(0x04c5, 0x1330) },
	{ USB_DEVICE(0x04CA, 0x3004) },
	{ USB_DEVICE(0x04CA, 0x3005) },
	{ USB_DEVICE(0x04CA, 0x3006) },
	{ USB_DEVICE(0x04CA, 0x3007) },
	{ USB_DEVICE(0x04CA, 0x3008) },
	{ USB_DEVICE(0x04CA, 0x300b) },
	{ USB_DEVICE(0x04CA, 0x300d) },
	{ USB_DEVICE(0x04CA, 0x300f) },
	{ USB_DEVICE(0x04CA, 0x3010) },
	{ USB_DEVICE(0x04CA, 0x3014) },
	{ USB_DEVICE(0x04CA, 0x3018) },
	{ USB_DEVICE(0x0930, 0x0219) },
	{ USB_DEVICE(0x0930, 0x021c) },
	{ USB_DEVICE(0x0930, 0x0220) },
	{ USB_DEVICE(0x0930, 0x0227) },
	{ USB_DEVICE(0x0b05, 0x17d0) },
	{ USB_DEVICE(0x0CF3, 0x0036) },
	{ USB_DEVICE(0x0CF3, 0x3004) },
	{ USB_DEVICE(0x0CF3, 0x3008) },
	{ USB_DEVICE(0x0CF3, 0x311D) },
	{ USB_DEVICE(0x0CF3, 0x311E) },
	{ USB_DEVICE(0x0CF3, 0x311F) },
	{ USB_DEVICE(0x0cf3, 0x3121) },
	{ USB_DEVICE(0x0CF3, 0x817a) },
	{ USB_DEVICE(0x0CF3, 0x817b) },
	{ USB_DEVICE(0x0cf3, 0xe003) },
	{ USB_DEVICE(0x0CF3, 0xE004) },
	{ USB_DEVICE(0x0CF3, 0xE005) },
	{ USB_DEVICE(0x0CF3, 0xE006) },
	{ USB_DEVICE(0x13d3, 0x3362) },
	{ USB_DEVICE(0x13d3, 0x3375) },
	{ USB_DEVICE(0x13d3, 0x3393) },
	{ USB_DEVICE(0x13d3, 0x3395) },
	{ USB_DEVICE(0x13d3, 0x3402) },
	{ USB_DEVICE(0x13d3, 0x3408) },
	{ USB_DEVICE(0x13d3, 0x3423) },
	{ USB_DEVICE(0x13d3, 0x3432) },
	{ USB_DEVICE(0x13d3, 0x3472) },
	{ USB_DEVICE(0x13d3, 0x3474) },
	{ USB_DEVICE(0x13d3, 0x3487) },
	{ USB_DEVICE(0x13d3, 0x3490) },

	/* Athewos AW5BBU12 with sfwash fiwmwawe */
	{ USB_DEVICE(0x0489, 0xE02C) },

	/* Athewos AW5BBU22 with sfwash fiwmwawe */
	{ USB_DEVICE(0x0489, 0xE036) },
	{ USB_DEVICE(0x0489, 0xE03C) },

	{ }	/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, ath3k_tabwe);

#define BTUSB_ATH3012		0x80
/* This tabwe is to woad patch and sysconfig fiwes
 * fow AW3012
 */
static const stwuct usb_device_id ath3k_bwist_tbw[] = {

	/* Athewos AW3012 with sfwash fiwmwawe*/
	{ USB_DEVICE(0x0489, 0xe04e), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe04d), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe056), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe057), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe05f), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe076), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe078), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xe095), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04c5, 0x1330), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3004), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3005), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3006), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3007), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3008), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x300b), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x300d), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x300f), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3010), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3014), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x04ca, 0x3018), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0930, 0x0219), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0930, 0x021c), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0930, 0x0220), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0930, 0x0227), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0b05, 0x17d0), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0CF3, 0x0036), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x3004), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x3008), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x311D), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x311E), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x311F), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0x3121), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0CF3, 0x817a), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0CF3, 0x817b), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0xe004), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0xe005), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0xe006), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0cf3, 0xe003), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3362), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3375), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3393), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3395), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3402), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3408), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3423), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3432), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3472), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3474), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3487), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x13d3, 0x3490), .dwivew_info = BTUSB_ATH3012 },

	/* Athewos AW5BBU22 with sfwash fiwmwawe */
	{ USB_DEVICE(0x0489, 0xE036), .dwivew_info = BTUSB_ATH3012 },
	{ USB_DEVICE(0x0489, 0xE03C), .dwivew_info = BTUSB_ATH3012 },

	{ }	/* Tewminating entwy */
};

static inwine void ath3k_wog_faiwed_woading(int eww, int wen, int size,
					    int count)
{
	BT_EWW("Fiwmwawe woading eww = %d, wen = %d, size = %d, count = %d",
	       eww, wen, size, count);
}

#define USB_WEQ_DFU_DNWOAD	1
#define BUWK_SIZE		4096
#define FW_HDW_SIZE		20
#define TIMEGAP_USEC_MIN	50
#define TIMEGAP_USEC_MAX	100

static int ath3k_woad_fiwmwawe(stwuct usb_device *udev,
				const stwuct fiwmwawe *fiwmwawe)
{
	u8 *send_buf;
	int wen = 0;
	int eww, pipe, size, sent = 0;
	int count = fiwmwawe->size;

	BT_DBG("udev %p", udev);

	send_buf = kmawwoc(BUWK_SIZE, GFP_KEWNEW);
	if (!send_buf) {
		BT_EWW("Can't awwocate memowy chunk fow fiwmwawe");
		wetuwn -ENOMEM;
	}

	eww = usb_contwow_msg_send(udev, 0, USB_WEQ_DFU_DNWOAD, USB_TYPE_VENDOW,
				   0, 0, fiwmwawe->data, FW_HDW_SIZE,
				   USB_CTWW_SET_TIMEOUT, GFP_KEWNEW);
	if (eww) {
		BT_EWW("Can't change to woading configuwation eww");
		goto ewwow;
	}
	sent += FW_HDW_SIZE;
	count -= FW_HDW_SIZE;

	pipe = usb_sndbuwkpipe(udev, 0x02);

	whiwe (count) {
		/* wowkawound the compatibiwity issue with xHCI contwowwew*/
		usweep_wange(TIMEGAP_USEC_MIN, TIMEGAP_USEC_MAX);

		size = min_t(uint, count, BUWK_SIZE);
		memcpy(send_buf, fiwmwawe->data + sent, size);

		eww = usb_buwk_msg(udev, pipe, send_buf, size,
					&wen, 3000);

		if (eww || (wen != size)) {
			ath3k_wog_faiwed_woading(eww, wen, size, count);
			goto ewwow;
		}

		sent  += size;
		count -= size;
	}

ewwow:
	kfwee(send_buf);
	wetuwn eww;
}

static int ath3k_get_state(stwuct usb_device *udev, unsigned chaw *state)
{
	wetuwn usb_contwow_msg_wecv(udev, 0, ATH3K_GETSTATE,
				    USB_TYPE_VENDOW | USB_DIW_IN, 0, 0,
				    state, 1, USB_CTWW_SET_TIMEOUT,
				    GFP_KEWNEW);
}

static int ath3k_get_vewsion(stwuct usb_device *udev,
			stwuct ath3k_vewsion *vewsion)
{
	wetuwn usb_contwow_msg_wecv(udev, 0, ATH3K_GETVEWSION,
				    USB_TYPE_VENDOW | USB_DIW_IN, 0, 0,
				    vewsion, sizeof(*vewsion), USB_CTWW_SET_TIMEOUT,
				    GFP_KEWNEW);
}

static int ath3k_woad_fwfiwe(stwuct usb_device *udev,
		const stwuct fiwmwawe *fiwmwawe)
{
	u8 *send_buf;
	int wen = 0;
	int eww, pipe, size, count, sent = 0;
	int wet;

	count = fiwmwawe->size;

	send_buf = kmawwoc(BUWK_SIZE, GFP_KEWNEW);
	if (!send_buf) {
		BT_EWW("Can't awwocate memowy chunk fow fiwmwawe");
		wetuwn -ENOMEM;
	}

	size = min_t(uint, count, FW_HDW_SIZE);

	wet = usb_contwow_msg_send(udev, 0, ATH3K_DNWOAD, USB_TYPE_VENDOW, 0, 0,
				   fiwmwawe->data, size, USB_CTWW_SET_TIMEOUT,
				   GFP_KEWNEW);
	if (wet) {
		BT_EWW("Can't change to woading configuwation eww");
		kfwee(send_buf);
		wetuwn wet;
	}

	sent += size;
	count -= size;

	pipe = usb_sndbuwkpipe(udev, 0x02);

	whiwe (count) {
		/* wowkawound the compatibiwity issue with xHCI contwowwew*/
		usweep_wange(TIMEGAP_USEC_MIN, TIMEGAP_USEC_MAX);

		size = min_t(uint, count, BUWK_SIZE);
		memcpy(send_buf, fiwmwawe->data + sent, size);

		eww = usb_buwk_msg(udev, pipe, send_buf, size,
					&wen, 3000);
		if (eww || (wen != size)) {
			ath3k_wog_faiwed_woading(eww, wen, size, count);
			kfwee(send_buf);
			wetuwn eww;
		}
		sent  += size;
		count -= size;
	}

	kfwee(send_buf);
	wetuwn 0;
}

static void ath3k_switch_pid(stwuct usb_device *udev)
{
	usb_contwow_msg_send(udev, 0, USB_WEG_SWITCH_VID_PID, USB_TYPE_VENDOW,
			     0, 0, NUWW, 0, USB_CTWW_SET_TIMEOUT, GFP_KEWNEW);
}

static int ath3k_set_nowmaw_mode(stwuct usb_device *udev)
{
	unsigned chaw fw_state;
	int wet;

	wet = ath3k_get_state(udev, &fw_state);
	if (wet) {
		BT_EWW("Can't get state to change to nowmaw mode eww");
		wetuwn wet;
	}

	if ((fw_state & ATH3K_MODE_MASK) == ATH3K_NOWMAW_MODE) {
		BT_DBG("fiwmwawe was awweady in nowmaw mode");
		wetuwn 0;
	}

	wetuwn usb_contwow_msg_send(udev, 0, ATH3K_SET_NOWMAW_MODE,
				    USB_TYPE_VENDOW, 0, 0, NUWW, 0,
				    USB_CTWW_SET_TIMEOUT, GFP_KEWNEW);
}

static int ath3k_woad_patch(stwuct usb_device *udev)
{
	unsigned chaw fw_state;
	chaw fiwename[ATH3K_NAME_WEN];
	const stwuct fiwmwawe *fiwmwawe;
	stwuct ath3k_vewsion fw_vewsion;
	__u32 pt_wom_vewsion, pt_buiwd_vewsion;
	int wet;

	wet = ath3k_get_state(udev, &fw_state);
	if (wet) {
		BT_EWW("Can't get state to change to woad wam patch eww");
		wetuwn wet;
	}

	if (fw_state & ATH3K_PATCH_UPDATE) {
		BT_DBG("Patch was awweady downwoaded");
		wetuwn 0;
	}

	wet = ath3k_get_vewsion(udev, &fw_vewsion);
	if (wet) {
		BT_EWW("Can't get vewsion to change to woad wam patch eww");
		wetuwn wet;
	}

	snpwintf(fiwename, ATH3K_NAME_WEN, "aw3k/AthwBT_0x%08x.dfu",
		 we32_to_cpu(fw_vewsion.wom_vewsion));

	wet = wequest_fiwmwawe(&fiwmwawe, fiwename, &udev->dev);
	if (wet < 0) {
		BT_EWW("Patch fiwe not found %s", fiwename);
		wetuwn wet;
	}

	pt_wom_vewsion = get_unawigned_we32(fiwmwawe->data +
					    fiwmwawe->size - 8);
	pt_buiwd_vewsion = get_unawigned_we32(fiwmwawe->data +
					      fiwmwawe->size - 4);

	if (pt_wom_vewsion != we32_to_cpu(fw_vewsion.wom_vewsion) ||
	    pt_buiwd_vewsion <= we32_to_cpu(fw_vewsion.buiwd_vewsion)) {
		BT_EWW("Patch fiwe vewsion did not match with fiwmwawe");
		wewease_fiwmwawe(fiwmwawe);
		wetuwn -EINVAW;
	}

	wet = ath3k_woad_fwfiwe(udev, fiwmwawe);
	wewease_fiwmwawe(fiwmwawe);

	wetuwn wet;
}

static int ath3k_woad_syscfg(stwuct usb_device *udev)
{
	unsigned chaw fw_state;
	chaw fiwename[ATH3K_NAME_WEN];
	const stwuct fiwmwawe *fiwmwawe;
	stwuct ath3k_vewsion fw_vewsion;
	int cwk_vawue, wet;

	wet = ath3k_get_state(udev, &fw_state);
	if (wet) {
		BT_EWW("Can't get state to change to woad configuwation eww");
		wetuwn -EBUSY;
	}

	wet = ath3k_get_vewsion(udev, &fw_vewsion);
	if (wet) {
		BT_EWW("Can't get vewsion to change to woad wam patch eww");
		wetuwn wet;
	}

	switch (fw_vewsion.wef_cwock) {

	case ATH3K_XTAW_FWEQ_26M:
		cwk_vawue = 26;
		bweak;
	case ATH3K_XTAW_FWEQ_40M:
		cwk_vawue = 40;
		bweak;
	case ATH3K_XTAW_FWEQ_19P2:
		cwk_vawue = 19;
		bweak;
	defauwt:
		cwk_vawue = 0;
		bweak;
	}

	snpwintf(fiwename, ATH3K_NAME_WEN, "aw3k/wamps_0x%08x_%d%s",
		we32_to_cpu(fw_vewsion.wom_vewsion), cwk_vawue, ".dfu");

	wet = wequest_fiwmwawe(&fiwmwawe, fiwename, &udev->dev);
	if (wet < 0) {
		BT_EWW("Configuwation fiwe not found %s", fiwename);
		wetuwn wet;
	}

	wet = ath3k_woad_fwfiwe(udev, fiwmwawe);
	wewease_fiwmwawe(fiwmwawe);

	wetuwn wet;
}

static int ath3k_pwobe(stwuct usb_intewface *intf,
			const stwuct usb_device_id *id)
{
	const stwuct fiwmwawe *fiwmwawe;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	int wet;

	BT_DBG("intf %p id %p", intf, id);

	if (intf->cuw_awtsetting->desc.bIntewfaceNumbew != 0)
		wetuwn -ENODEV;

	/* match device ID in ath3k bwackwist tabwe */
	if (!id->dwivew_info) {
		const stwuct usb_device_id *match;

		match = usb_match_id(intf, ath3k_bwist_tbw);
		if (match)
			id = match;
	}

	/* woad patch and sysconfig fiwes fow AW3012 */
	if (id->dwivew_info & BTUSB_ATH3012) {
		/* New fiwmwawe with patch and sysconfig fiwes awweady woaded */
		if (we16_to_cpu(udev->descwiptow.bcdDevice) > 0x0001)
			wetuwn -ENODEV;

		wet = ath3k_woad_patch(udev);
		if (wet < 0) {
			BT_EWW("Woading patch fiwe faiwed");
			wetuwn wet;
		}
		wet = ath3k_woad_syscfg(udev);
		if (wet < 0) {
			BT_EWW("Woading sysconfig fiwe faiwed");
			wetuwn wet;
		}
		wet = ath3k_set_nowmaw_mode(udev);
		if (wet) {
			BT_EWW("Set nowmaw mode faiwed");
			wetuwn wet;
		}
		ath3k_switch_pid(udev);
		wetuwn 0;
	}

	wet = wequest_fiwmwawe(&fiwmwawe, ATH3K_FIWMWAWE, &udev->dev);
	if (wet < 0) {
		if (wet == -ENOENT)
			BT_EWW("Fiwmwawe fiwe \"%s\" not found",
							ATH3K_FIWMWAWE);
		ewse
			BT_EWW("Fiwmwawe fiwe \"%s\" wequest faiwed (eww=%d)",
							ATH3K_FIWMWAWE, wet);
		wetuwn wet;
	}

	wet = ath3k_woad_fiwmwawe(udev, fiwmwawe);
	wewease_fiwmwawe(fiwmwawe);

	wetuwn wet;
}

static void ath3k_disconnect(stwuct usb_intewface *intf)
{
	BT_DBG("%s intf %p", __func__, intf);
}

static stwuct usb_dwivew ath3k_dwivew = {
	.name		= "ath3k",
	.pwobe		= ath3k_pwobe,
	.disconnect	= ath3k_disconnect,
	.id_tabwe	= ath3k_tabwe,
	.disabwe_hub_initiated_wpm = 1,
};

moduwe_usb_dwivew(ath3k_dwivew);

MODUWE_AUTHOW("Athewos Communications");
MODUWE_DESCWIPTION("Athewos AW30xx fiwmwawe dwivew");
MODUWE_VEWSION(VEWSION);
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE(ATH3K_FIWMWAWE);
