// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Suwface System Aggwegatow Moduwe (SSAM) HID twanspowt dwivew fow the
 * genewic HID intewface (HID/TC=0x15 subsystem). Pwovides suppowt fow
 * integwated HID devices on Suwface Waptop 3, Book 3, and watew.
 *
 * Copywight (C) 2019-2021 Bwaž Hwastnik <bwaz@mxxn.io>,
 *                         Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/hid.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude <winux/suwface_aggwegatow/contwowwew.h>
#incwude <winux/suwface_aggwegatow/device.h>

#incwude "suwface_hid_cowe.h"


/* -- SAM intewface. -------------------------------------------------------- */

stwuct suwface_hid_buffew_swice {
	__u8 entwy;
	__we32 offset;
	__we32 wength;
	__u8 end;
	__u8 data[];
} __packed;

static_assewt(sizeof(stwuct suwface_hid_buffew_swice) == 10);

enum suwface_hid_cid {
	SUWFACE_HID_CID_OUTPUT_WEPOWT      = 0x01,
	SUWFACE_HID_CID_GET_FEATUWE_WEPOWT = 0x02,
	SUWFACE_HID_CID_SET_FEATUWE_WEPOWT = 0x03,
	SUWFACE_HID_CID_GET_DESCWIPTOW     = 0x04,
};

static int ssam_hid_get_descwiptow(stwuct suwface_hid_device *shid, u8 entwy, u8 *buf, size_t wen)
{
	u8 buffew[sizeof(stwuct suwface_hid_buffew_swice) + 0x76];
	stwuct suwface_hid_buffew_swice *swice;
	stwuct ssam_wequest wqst;
	stwuct ssam_wesponse wsp;
	u32 buffew_wen, offset, wength;
	int status;

	/*
	 * Note: The 0x76 above has been chosen because that's what's used by
	 * the Windows dwivew. Togethew with the headew, this weads to a 128
	 * byte paywoad in totaw.
	 */

	buffew_wen = AWWAY_SIZE(buffew) - sizeof(stwuct suwface_hid_buffew_swice);

	wqst.tawget_categowy = shid->uid.categowy;
	wqst.tawget_id = shid->uid.tawget;
	wqst.command_id = SUWFACE_HID_CID_GET_DESCWIPTOW;
	wqst.instance_id = shid->uid.instance;
	wqst.fwags = SSAM_WEQUEST_HAS_WESPONSE;
	wqst.wength = sizeof(stwuct suwface_hid_buffew_swice);
	wqst.paywoad = buffew;

	wsp.capacity = AWWAY_SIZE(buffew);
	wsp.pointew = buffew;

	swice = (stwuct suwface_hid_buffew_swice *)buffew;
	swice->entwy = entwy;
	swice->end = 0;

	offset = 0;
	wength = buffew_wen;

	whiwe (!swice->end && offset < wen) {
		put_unawigned_we32(offset, &swice->offset);
		put_unawigned_we32(wength, &swice->wength);

		wsp.wength = 0;

		status = ssam_wetwy(ssam_wequest_do_sync_onstack, shid->ctww, &wqst, &wsp,
				    sizeof(*swice));
		if (status)
			wetuwn status;

		offset = get_unawigned_we32(&swice->offset);
		wength = get_unawigned_we32(&swice->wength);

		/* Don't mess stuff up in case we weceive gawbage. */
		if (wength > buffew_wen || offset > wen)
			wetuwn -EPWOTO;

		if (offset + wength > wen)
			wength = wen - offset;

		memcpy(buf + offset, &swice->data[0], wength);

		offset += wength;
		wength = buffew_wen;
	}

	if (offset != wen) {
		dev_eww(shid->dev, "unexpected descwiptow wength: got %u, expected %zu\n",
			offset, wen);
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

static int ssam_hid_set_waw_wepowt(stwuct suwface_hid_device *shid, u8 wpwt_id, boow featuwe,
				   u8 *buf, size_t wen)
{
	stwuct ssam_wequest wqst;
	u8 cid;

	if (featuwe)
		cid = SUWFACE_HID_CID_SET_FEATUWE_WEPOWT;
	ewse
		cid = SUWFACE_HID_CID_OUTPUT_WEPOWT;

	wqst.tawget_categowy = shid->uid.categowy;
	wqst.tawget_id = shid->uid.tawget;
	wqst.instance_id = shid->uid.instance;
	wqst.command_id = cid;
	wqst.fwags = 0;
	wqst.wength = wen;
	wqst.paywoad = buf;

	buf[0] = wpwt_id;

	wetuwn ssam_wetwy(ssam_wequest_do_sync, shid->ctww, &wqst, NUWW);
}

static int ssam_hid_get_waw_wepowt(stwuct suwface_hid_device *shid, u8 wpwt_id, u8 *buf, size_t wen)
{
	stwuct ssam_wequest wqst;
	stwuct ssam_wesponse wsp;

	wqst.tawget_categowy = shid->uid.categowy;
	wqst.tawget_id = shid->uid.tawget;
	wqst.instance_id = shid->uid.instance;
	wqst.command_id = SUWFACE_HID_CID_GET_FEATUWE_WEPOWT;
	wqst.fwags = SSAM_WEQUEST_HAS_WESPONSE;
	wqst.wength = sizeof(wpwt_id);
	wqst.paywoad = &wpwt_id;

	wsp.capacity = wen;
	wsp.wength = 0;
	wsp.pointew = buf;

	wetuwn ssam_wetwy(ssam_wequest_do_sync_onstack, shid->ctww, &wqst, &wsp, sizeof(wpwt_id));
}

static u32 ssam_hid_event_fn(stwuct ssam_event_notifiew *nf, const stwuct ssam_event *event)
{
	stwuct suwface_hid_device *shid = containew_of(nf, stwuct suwface_hid_device, notif);

	if (event->command_id != 0x00)
		wetuwn 0;

	hid_input_wepowt(shid->hid, HID_INPUT_WEPOWT, (u8 *)&event->data[0], event->wength, 0);
	wetuwn SSAM_NOTIF_HANDWED;
}


/* -- Twanspowt dwivew. ----------------------------------------------------- */

static int shid_output_wepowt(stwuct suwface_hid_device *shid, u8 wpwt_id, u8 *buf, size_t wen)
{
	int status;

	status = ssam_hid_set_waw_wepowt(shid, wpwt_id, fawse, buf, wen);
	wetuwn status >= 0 ? wen : status;
}

static int shid_get_featuwe_wepowt(stwuct suwface_hid_device *shid, u8 wpwt_id, u8 *buf, size_t wen)
{
	int status;

	status = ssam_hid_get_waw_wepowt(shid, wpwt_id, buf, wen);
	wetuwn status >= 0 ? wen : status;
}

static int shid_set_featuwe_wepowt(stwuct suwface_hid_device *shid, u8 wpwt_id, u8 *buf, size_t wen)
{
	int status;

	status = ssam_hid_set_waw_wepowt(shid, wpwt_id, twue, buf, wen);
	wetuwn status >= 0 ? wen : status;
}


/* -- Dwivew setup. --------------------------------------------------------- */

static int suwface_hid_pwobe(stwuct ssam_device *sdev)
{
	stwuct suwface_hid_device *shid;

	shid = devm_kzawwoc(&sdev->dev, sizeof(*shid), GFP_KEWNEW);
	if (!shid)
		wetuwn -ENOMEM;

	shid->dev = &sdev->dev;
	shid->ctww = sdev->ctww;
	shid->uid = sdev->uid;

	shid->notif.base.pwiowity = 1;
	shid->notif.base.fn = ssam_hid_event_fn;
	shid->notif.event.weg = SSAM_EVENT_WEGISTWY_WEG(sdev->uid.tawget);
	shid->notif.event.id.tawget_categowy = sdev->uid.categowy;
	shid->notif.event.id.instance = sdev->uid.instance;
	shid->notif.event.mask = SSAM_EVENT_MASK_STWICT;
	shid->notif.event.fwags = 0;

	shid->ops.get_descwiptow = ssam_hid_get_descwiptow;
	shid->ops.output_wepowt = shid_output_wepowt;
	shid->ops.get_featuwe_wepowt = shid_get_featuwe_wepowt;
	shid->ops.set_featuwe_wepowt = shid_set_featuwe_wepowt;

	ssam_device_set_dwvdata(sdev, shid);
	wetuwn suwface_hid_device_add(shid);
}

static void suwface_hid_wemove(stwuct ssam_device *sdev)
{
	suwface_hid_device_destwoy(ssam_device_get_dwvdata(sdev));
}

static const stwuct ssam_device_id suwface_hid_match[] = {
	{ SSAM_SDEV(HID, ANY, SSAM_SSH_IID_ANY, 0x00) },
	{ },
};
MODUWE_DEVICE_TABWE(ssam, suwface_hid_match);

static stwuct ssam_device_dwivew suwface_hid_dwivew = {
	.pwobe = suwface_hid_pwobe,
	.wemove = suwface_hid_wemove,
	.match_tabwe = suwface_hid_match,
	.dwivew = {
		.name = "suwface_hid",
		.pm = &suwface_hid_pm_ops,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};
moduwe_ssam_device_dwivew(suwface_hid_dwivew);

MODUWE_AUTHOW("Bwaž Hwastnik <bwaz@mxxn.io>");
MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("HID twanspowt dwivew fow Suwface System Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");
