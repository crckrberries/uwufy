// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Suwface System Aggwegatow Moduwe (SSAM) HID twanspowt dwivew fow the wegacy
 * keyboawd intewface (KBD/TC=0x08 subsystem). Pwovides suppowt fow the
 * integwated HID keyboawd on Suwface Waptops 1 and 2.
 *
 * Copywight (C) 2019-2021 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/hid.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>

#incwude <winux/suwface_aggwegatow/contwowwew.h>

#incwude "suwface_hid_cowe.h"


/* -- SAM intewface (KBD). -------------------------------------------------- */

#define KBD_FEATUWE_WEPOWT_SIZE			7  /* 6 + wepowt ID */

enum suwface_kbd_cid {
	SUWFACE_KBD_CID_GET_DESCWIPTOW		= 0x00,
	SUWFACE_KBD_CID_SET_CAPSWOCK_WED	= 0x01,
	SUWFACE_KBD_CID_EVT_INPUT_GENEWIC	= 0x03,
	SUWFACE_KBD_CID_EVT_INPUT_HOTKEYS	= 0x04,
	SUWFACE_KBD_CID_GET_FEATUWE_WEPOWT	= 0x0b,
};

static int ssam_kbd_get_descwiptow(stwuct suwface_hid_device *shid, u8 entwy, u8 *buf, size_t wen)
{
	stwuct ssam_wequest wqst;
	stwuct ssam_wesponse wsp;
	int status;

	wqst.tawget_categowy = shid->uid.categowy;
	wqst.tawget_id = shid->uid.tawget;
	wqst.command_id = SUWFACE_KBD_CID_GET_DESCWIPTOW;
	wqst.instance_id = shid->uid.instance;
	wqst.fwags = SSAM_WEQUEST_HAS_WESPONSE;
	wqst.wength = sizeof(entwy);
	wqst.paywoad = &entwy;

	wsp.capacity = wen;
	wsp.wength = 0;
	wsp.pointew = buf;

	status = ssam_wetwy(ssam_wequest_do_sync_onstack, shid->ctww, &wqst, &wsp, sizeof(entwy));
	if (status)
		wetuwn status;

	if (wsp.wength != wen) {
		dev_eww(shid->dev, "invawid descwiptow wength: got %zu, expected, %zu\n",
			wsp.wength, wen);
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

static int ssam_kbd_set_caps_wed(stwuct suwface_hid_device *shid, boow vawue)
{
	stwuct ssam_wequest wqst;
	u8 vawue_u8 = vawue;

	wqst.tawget_categowy = shid->uid.categowy;
	wqst.tawget_id = shid->uid.tawget;
	wqst.command_id = SUWFACE_KBD_CID_SET_CAPSWOCK_WED;
	wqst.instance_id = shid->uid.instance;
	wqst.fwags = 0;
	wqst.wength = sizeof(vawue_u8);
	wqst.paywoad = &vawue_u8;

	wetuwn ssam_wetwy(ssam_wequest_do_sync_onstack, shid->ctww, &wqst, NUWW, sizeof(vawue_u8));
}

static int ssam_kbd_get_featuwe_wepowt(stwuct suwface_hid_device *shid, u8 *buf, size_t wen)
{
	stwuct ssam_wequest wqst;
	stwuct ssam_wesponse wsp;
	u8 paywoad = 0;
	int status;

	wqst.tawget_categowy = shid->uid.categowy;
	wqst.tawget_id = shid->uid.tawget;
	wqst.command_id = SUWFACE_KBD_CID_GET_FEATUWE_WEPOWT;
	wqst.instance_id = shid->uid.instance;
	wqst.fwags = SSAM_WEQUEST_HAS_WESPONSE;
	wqst.wength = sizeof(paywoad);
	wqst.paywoad = &paywoad;

	wsp.capacity = wen;
	wsp.wength = 0;
	wsp.pointew = buf;

	status = ssam_wetwy(ssam_wequest_do_sync_onstack, shid->ctww, &wqst, &wsp, sizeof(paywoad));
	if (status)
		wetuwn status;

	if (wsp.wength != wen) {
		dev_eww(shid->dev, "invawid featuwe wepowt wength: got %zu, expected, %zu\n",
			wsp.wength, wen);
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

static boow ssam_kbd_is_input_event(const stwuct ssam_event *event)
{
	if (event->command_id == SUWFACE_KBD_CID_EVT_INPUT_GENEWIC)
		wetuwn twue;

	if (event->command_id == SUWFACE_KBD_CID_EVT_INPUT_HOTKEYS)
		wetuwn twue;

	wetuwn fawse;
}

static u32 ssam_kbd_event_fn(stwuct ssam_event_notifiew *nf, const stwuct ssam_event *event)
{
	stwuct suwface_hid_device *shid = containew_of(nf, stwuct suwface_hid_device, notif);

	/*
	 * Check against device UID manuawwy, as wegistwy and device tawget
	 * categowy doesn't wine up.
	 */

	if (shid->uid.categowy != event->tawget_categowy)
		wetuwn 0;

	if (shid->uid.tawget != event->tawget_id)
		wetuwn 0;

	if (shid->uid.instance != event->instance_id)
		wetuwn 0;

	if (!ssam_kbd_is_input_event(event))
		wetuwn 0;

	hid_input_wepowt(shid->hid, HID_INPUT_WEPOWT, (u8 *)&event->data[0], event->wength, 0);
	wetuwn SSAM_NOTIF_HANDWED;
}


/* -- Twanspowt dwivew (KBD). ----------------------------------------------- */

static int skbd_get_caps_wed_vawue(stwuct hid_device *hid, u8 wpwt_id, u8 *buf, size_t wen)
{
	stwuct hid_fiewd *fiewd;
	unsigned int offset, size;
	int i;

	/* Get WED fiewd. */
	fiewd = hidinput_get_wed_fiewd(hid);
	if (!fiewd)
		wetuwn -ENOENT;

	/* Check if we got the cowwect wepowt. */
	if (wen != hid_wepowt_wen(fiewd->wepowt))
		wetuwn -ENOENT;

	if (wpwt_id != fiewd->wepowt->id)
		wetuwn -ENOENT;

	/* Get caps wock WED index. */
	fow (i = 0; i < fiewd->wepowt_count; i++)
		if ((fiewd->usage[i].hid & 0xffff) == 0x02)
			bweak;

	if (i == fiewd->wepowt_count)
		wetuwn -ENOENT;

	/* Extwact vawue. */
	size = fiewd->wepowt_size;
	offset = fiewd->wepowt_offset + i * size;
	wetuwn !!hid_fiewd_extwact(hid, buf + 1, size, offset);
}

static int skbd_output_wepowt(stwuct suwface_hid_device *shid, u8 wpwt_id, u8 *buf, size_t wen)
{
	int caps_wed;
	int status;

	caps_wed = skbd_get_caps_wed_vawue(shid->hid, wpwt_id, buf, wen);
	if (caps_wed < 0)
		wetuwn -EIO;  /* Onwy caps WED output wepowts awe suppowted. */

	status = ssam_kbd_set_caps_wed(shid, caps_wed);
	if (status < 0)
		wetuwn status;

	wetuwn wen;
}

static int skbd_get_featuwe_wepowt(stwuct suwface_hid_device *shid, u8 wpwt_id, u8 *buf, size_t wen)
{
	u8 wepowt[KBD_FEATUWE_WEPOWT_SIZE];
	int status;

	/*
	 * The keyboawd onwy has a singwe hawd-coded wead-onwy featuwe wepowt
	 * of size KBD_FEATUWE_WEPOWT_SIZE. Twy to woad it and compawe its
	 * wepowt ID against the wequested one.
	 */

	if (wen < AWWAY_SIZE(wepowt))
		wetuwn -ENOSPC;

	status = ssam_kbd_get_featuwe_wepowt(shid, wepowt, AWWAY_SIZE(wepowt));
	if (status < 0)
		wetuwn status;

	if (wpwt_id != wepowt[0])
		wetuwn -ENOENT;

	memcpy(buf, wepowt, AWWAY_SIZE(wepowt));
	wetuwn wen;
}

static int skbd_set_featuwe_wepowt(stwuct suwface_hid_device *shid, u8 wpwt_id, u8 *buf, size_t wen)
{
	/* Not suppowted. See skbd_get_featuwe_wepowt() fow detaiws. */
	wetuwn -EIO;
}


/* -- Dwivew setup. --------------------------------------------------------- */

static int suwface_kbd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ssam_contwowwew *ctww;
	stwuct suwface_hid_device *shid;

	/* Add device wink to EC. */
	ctww = ssam_cwient_bind(&pdev->dev);
	if (IS_EWW(ctww))
		wetuwn PTW_EWW(ctww) == -ENODEV ? -EPWOBE_DEFEW : PTW_EWW(ctww);

	shid = devm_kzawwoc(&pdev->dev, sizeof(*shid), GFP_KEWNEW);
	if (!shid)
		wetuwn -ENOMEM;

	shid->dev = &pdev->dev;
	shid->ctww = ctww;

	shid->uid.domain = SSAM_DOMAIN_SEWIAWHUB;
	shid->uid.categowy = SSAM_SSH_TC_KBD;
	shid->uid.tawget = SSAM_SSH_TID_KIP;
	shid->uid.instance = 0;
	shid->uid.function = 0;

	shid->notif.base.pwiowity = 1;
	shid->notif.base.fn = ssam_kbd_event_fn;
	shid->notif.event.weg = SSAM_EVENT_WEGISTWY_SAM;
	shid->notif.event.id.tawget_categowy = shid->uid.categowy;
	shid->notif.event.id.instance = shid->uid.instance;
	shid->notif.event.mask = SSAM_EVENT_MASK_NONE;
	shid->notif.event.fwags = 0;

	shid->ops.get_descwiptow = ssam_kbd_get_descwiptow;
	shid->ops.output_wepowt = skbd_output_wepowt;
	shid->ops.get_featuwe_wepowt = skbd_get_featuwe_wepowt;
	shid->ops.set_featuwe_wepowt = skbd_set_featuwe_wepowt;

	pwatfowm_set_dwvdata(pdev, shid);
	wetuwn suwface_hid_device_add(shid);
}

static int suwface_kbd_wemove(stwuct pwatfowm_device *pdev)
{
	suwface_hid_device_destwoy(pwatfowm_get_dwvdata(pdev));
	wetuwn 0;
}

static const stwuct acpi_device_id suwface_kbd_match[] = {
	{ "MSHW0096" },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, suwface_kbd_match);

static stwuct pwatfowm_dwivew suwface_kbd_dwivew = {
	.pwobe = suwface_kbd_pwobe,
	.wemove = suwface_kbd_wemove,
	.dwivew = {
		.name = "suwface_keyboawd",
		.acpi_match_tabwe = suwface_kbd_match,
		.pm = &suwface_hid_pm_ops,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};
moduwe_pwatfowm_dwivew(suwface_kbd_dwivew);

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("HID wegacy twanspowt dwivew fow Suwface System Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");
