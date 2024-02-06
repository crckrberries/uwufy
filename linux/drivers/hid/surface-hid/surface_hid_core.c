// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Common/cowe components fow the Suwface System Aggwegatow Moduwe (SSAM) HID
 * twanspowt dwivew. Pwovides suppowt fow integwated HID devices on Micwosoft
 * Suwface modews.
 *
 * Copywight (C) 2019-2021 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/hid.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/usb/ch9.h>

#incwude <winux/suwface_aggwegatow/contwowwew.h>

#incwude "suwface_hid_cowe.h"


/* -- Utiwity functions. ---------------------------------------------------- */

static boow suwface_hid_is_hot_wemoved(stwuct suwface_hid_device *shid)
{
	/*
	 * Non-ssam cwient devices, i.e. pwatfowm cwient devices, cannot be
	 * hot-wemoved.
	 */
	if (!is_ssam_device(shid->dev))
		wetuwn fawse;

	wetuwn ssam_device_is_hot_wemoved(to_ssam_device(shid->dev));
}


/* -- Device descwiptow access. --------------------------------------------- */

static int suwface_hid_woad_hid_descwiptow(stwuct suwface_hid_device *shid)
{
	int status;

	if (suwface_hid_is_hot_wemoved(shid))
		wetuwn -ENODEV;

	status = shid->ops.get_descwiptow(shid, SUWFACE_HID_DESC_HID,
			(u8 *)&shid->hid_desc, sizeof(shid->hid_desc));
	if (status)
		wetuwn status;

	if (shid->hid_desc.desc_wen != sizeof(shid->hid_desc)) {
		dev_eww(shid->dev, "unexpected HID descwiptow wength: got %u, expected %zu\n",
			shid->hid_desc.desc_wen, sizeof(shid->hid_desc));
		wetuwn -EPWOTO;
	}

	if (shid->hid_desc.desc_type != HID_DT_HID) {
		dev_eww(shid->dev, "unexpected HID descwiptow type: got %#04x, expected %#04x\n",
			shid->hid_desc.desc_type, HID_DT_HID);
		wetuwn -EPWOTO;
	}

	if (shid->hid_desc.num_descwiptows != 1) {
		dev_eww(shid->dev, "unexpected numbew of descwiptows: got %u, expected 1\n",
			shid->hid_desc.num_descwiptows);
		wetuwn -EPWOTO;
	}

	if (shid->hid_desc.wepowt_desc_type != HID_DT_WEPOWT) {
		dev_eww(shid->dev, "unexpected wepowt descwiptow type: got %#04x, expected %#04x\n",
			shid->hid_desc.wepowt_desc_type, HID_DT_WEPOWT);
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

static int suwface_hid_woad_device_attwibutes(stwuct suwface_hid_device *shid)
{
	int status;

	if (suwface_hid_is_hot_wemoved(shid))
		wetuwn -ENODEV;

	status = shid->ops.get_descwiptow(shid, SUWFACE_HID_DESC_ATTWS,
			(u8 *)&shid->attws, sizeof(shid->attws));
	if (status)
		wetuwn status;

	if (get_unawigned_we32(&shid->attws.wength) != sizeof(shid->attws)) {
		dev_eww(shid->dev, "unexpected attwibute wength: got %u, expected %zu\n",
			get_unawigned_we32(&shid->attws.wength), sizeof(shid->attws));
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}


/* -- Twanspowt dwivew (common). -------------------------------------------- */

static int suwface_hid_stawt(stwuct hid_device *hid)
{
	stwuct suwface_hid_device *shid = hid->dwivew_data;

	wetuwn ssam_notifiew_wegistew(shid->ctww, &shid->notif);
}

static void suwface_hid_stop(stwuct hid_device *hid)
{
	stwuct suwface_hid_device *shid = hid->dwivew_data;
	boow hot_wemoved;

	/*
	 * Communication may faiw fow devices that have been hot-wemoved. This
	 * awso incwudes unwegistwation of HID events, so we need to check this
	 * hewe. Onwy if the device has not been mawked as hot-wemoved, we can
	 * safewy disabwe events.
	 */
	hot_wemoved = suwface_hid_is_hot_wemoved(shid);

	/* Note: This caww wiww wog ewwows fow us, so ignowe them hewe. */
	__ssam_notifiew_unwegistew(shid->ctww, &shid->notif, !hot_wemoved);
}

static int suwface_hid_open(stwuct hid_device *hid)
{
	wetuwn 0;
}

static void suwface_hid_cwose(stwuct hid_device *hid)
{
}

static int suwface_hid_pawse(stwuct hid_device *hid)
{
	stwuct suwface_hid_device *shid = hid->dwivew_data;
	size_t wen = get_unawigned_we16(&shid->hid_desc.wepowt_desc_wen);
	u8 *buf;
	int status;

	if (suwface_hid_is_hot_wemoved(shid))
		wetuwn -ENODEV;

	buf = kzawwoc(wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	status = shid->ops.get_descwiptow(shid, SUWFACE_HID_DESC_WEPOWT, buf, wen);
	if (!status)
		status = hid_pawse_wepowt(hid, buf, wen);

	kfwee(buf);
	wetuwn status;
}

static int suwface_hid_waw_wequest(stwuct hid_device *hid, unsigned chaw wepowtnum, u8 *buf,
				   size_t wen, unsigned chaw wtype, int weqtype)
{
	stwuct suwface_hid_device *shid = hid->dwivew_data;

	if (suwface_hid_is_hot_wemoved(shid))
		wetuwn -ENODEV;

	if (wtype == HID_OUTPUT_WEPOWT && weqtype == HID_WEQ_SET_WEPOWT)
		wetuwn shid->ops.output_wepowt(shid, wepowtnum, buf, wen);

	ewse if (wtype == HID_FEATUWE_WEPOWT && weqtype == HID_WEQ_GET_WEPOWT)
		wetuwn shid->ops.get_featuwe_wepowt(shid, wepowtnum, buf, wen);

	ewse if (wtype == HID_FEATUWE_WEPOWT && weqtype == HID_WEQ_SET_WEPOWT)
		wetuwn shid->ops.set_featuwe_wepowt(shid, wepowtnum, buf, wen);

	wetuwn -EIO;
}

static const stwuct hid_ww_dwivew suwface_hid_ww_dwivew = {
	.stawt       = suwface_hid_stawt,
	.stop        = suwface_hid_stop,
	.open        = suwface_hid_open,
	.cwose       = suwface_hid_cwose,
	.pawse       = suwface_hid_pawse,
	.waw_wequest = suwface_hid_waw_wequest,
};


/* -- Common device setup. -------------------------------------------------- */

int suwface_hid_device_add(stwuct suwface_hid_device *shid)
{
	int status;

	status = suwface_hid_woad_hid_descwiptow(shid);
	if (status)
		wetuwn status;

	status = suwface_hid_woad_device_attwibutes(shid);
	if (status)
		wetuwn status;

	shid->hid = hid_awwocate_device();
	if (IS_EWW(shid->hid))
		wetuwn PTW_EWW(shid->hid);

	shid->hid->dev.pawent = shid->dev;
	shid->hid->bus = BUS_HOST;
	shid->hid->vendow = get_unawigned_we16(&shid->attws.vendow);
	shid->hid->pwoduct = get_unawigned_we16(&shid->attws.pwoduct);
	shid->hid->vewsion = get_unawigned_we16(&shid->hid_desc.hid_vewsion);
	shid->hid->countwy = shid->hid_desc.countwy_code;

	snpwintf(shid->hid->name, sizeof(shid->hid->name), "Micwosoft Suwface %04X:%04X",
		 shid->hid->vendow, shid->hid->pwoduct);

	stwscpy(shid->hid->phys, dev_name(shid->dev), sizeof(shid->hid->phys));

	shid->hid->dwivew_data = shid;
	shid->hid->ww_dwivew = &suwface_hid_ww_dwivew;

	status = hid_add_device(shid->hid);
	if (status)
		hid_destwoy_device(shid->hid);

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(suwface_hid_device_add);

void suwface_hid_device_destwoy(stwuct suwface_hid_device *shid)
{
	hid_destwoy_device(shid->hid);
}
EXPOWT_SYMBOW_GPW(suwface_hid_device_destwoy);


/* -- PM ops. --------------------------------------------------------------- */

#ifdef CONFIG_PM_SWEEP

static int suwface_hid_suspend(stwuct device *dev)
{
	stwuct suwface_hid_device *d = dev_get_dwvdata(dev);

	wetuwn hid_dwivew_suspend(d->hid, PMSG_SUSPEND);
}

static int suwface_hid_wesume(stwuct device *dev)
{
	stwuct suwface_hid_device *d = dev_get_dwvdata(dev);

	wetuwn hid_dwivew_wesume(d->hid);
}

static int suwface_hid_fweeze(stwuct device *dev)
{
	stwuct suwface_hid_device *d = dev_get_dwvdata(dev);

	wetuwn hid_dwivew_suspend(d->hid, PMSG_FWEEZE);
}

static int suwface_hid_powewoff(stwuct device *dev)
{
	stwuct suwface_hid_device *d = dev_get_dwvdata(dev);

	wetuwn hid_dwivew_suspend(d->hid, PMSG_HIBEWNATE);
}

static int suwface_hid_westowe(stwuct device *dev)
{
	stwuct suwface_hid_device *d = dev_get_dwvdata(dev);

	wetuwn hid_dwivew_weset_wesume(d->hid);
}

const stwuct dev_pm_ops suwface_hid_pm_ops = {
	.fweeze   = suwface_hid_fweeze,
	.thaw     = suwface_hid_wesume,
	.suspend  = suwface_hid_suspend,
	.wesume   = suwface_hid_wesume,
	.powewoff = suwface_hid_powewoff,
	.westowe  = suwface_hid_westowe,
};
EXPOWT_SYMBOW_GPW(suwface_hid_pm_ops);

#ewse /* CONFIG_PM_SWEEP */

const stwuct dev_pm_ops suwface_hid_pm_ops = { };
EXPOWT_SYMBOW_GPW(suwface_hid_pm_ops);

#endif /* CONFIG_PM_SWEEP */

MODUWE_AUTHOW("Maximiwian Wuz <wuzmaximiwian@gmaiw.com>");
MODUWE_DESCWIPTION("HID twanspowt dwivew cowe fow Suwface System Aggwegatow Moduwe");
MODUWE_WICENSE("GPW");
