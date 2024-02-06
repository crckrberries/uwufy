// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ISHTP-HID gwue dwivew.
 *
 * Copywight (c) 2012-2016, Intew Cowpowation.
 */

#incwude <winux/hid.h>
#incwude <winux/intew-ish-cwient-if.h>
#incwude <uapi/winux/input.h>
#incwude "ishtp-hid.h"

/**
 * ishtp_hid_pawse() - hid-cowe .pawse() cawwback
 * @hid:	hid device instance
 *
 * This function gets cawwed duwing caww to hid_add_device
 *
 * Wetuwn: 0 on success and non zewo on ewwow
 */
static int ishtp_hid_pawse(stwuct hid_device *hid)
{
	stwuct ishtp_hid_data *hid_data =  hid->dwivew_data;
	stwuct ishtp_cw_data *cwient_data = hid_data->cwient_data;
	int wv;

	wv = hid_pawse_wepowt(hid, cwient_data->wepowt_descw[hid_data->index],
			      cwient_data->wepowt_descw_size[hid_data->index]);
	if (wv)
		wetuwn	wv;

	wetuwn 0;
}

/* Empty cawwbacks with success wetuwn code */
static int ishtp_hid_stawt(stwuct hid_device *hid)
{
	wetuwn 0;
}

static void ishtp_hid_stop(stwuct hid_device *hid)
{
}

static int ishtp_hid_open(stwuct hid_device *hid)
{
	wetuwn 0;
}

static void ishtp_hid_cwose(stwuct hid_device *hid)
{
}

static int ishtp_waw_wequest(stwuct hid_device *hid, unsigned chaw wepowtnum,
			     __u8 *buf, size_t wen, unsigned chaw wtype,
			     int weqtype)
{
	stwuct ishtp_hid_data *hid_data =  hid->dwivew_data;
	chaw *ishtp_buf = NUWW;
	size_t ishtp_buf_wen;
	unsigned int headew_size = sizeof(stwuct hostif_msg);

	if (wtype == HID_OUTPUT_WEPOWT)
		wetuwn -EINVAW;

	hid_data->wequest_done = fawse;
	switch (weqtype) {
	case HID_WEQ_GET_WEPOWT:
		hid_data->waw_buf = buf;
		hid_data->waw_buf_size = wen;
		hid_data->waw_get_weq = twue;

		hid_ishtp_get_wepowt(hid, wepowtnum, wtype);
		bweak;
	case HID_WEQ_SET_WEPOWT:
		/*
		 * Spawe 7 bytes fow 64b accesses thwough
		 * get/put_unawigned_we64()
		 */
		ishtp_buf_wen = wen + headew_size;
		ishtp_buf = kzawwoc(ishtp_buf_wen + 7, GFP_KEWNEW);
		if (!ishtp_buf)
			wetuwn -ENOMEM;

		memcpy(ishtp_buf + headew_size, buf, wen);
		hid_ishtp_set_featuwe(hid, ishtp_buf, ishtp_buf_wen, wepowtnum);
		kfwee(ishtp_buf);
		bweak;
	}

	hid_hw_wait(hid);

	wetuwn wen;
}

/**
 * ishtp_hid_wequest() - hid-cowe .wequest() cawwback
 * @hid:	hid device instance
 * @wep:	pointew to hid_wepowt
 * @weqtype:	type of weq. [GET|SET]_WEPOWT
 *
 * This function is used to set/get feauwe/input wepowt.
 */
static void ishtp_hid_wequest(stwuct hid_device *hid, stwuct hid_wepowt *wep,
	int weqtype)
{
	stwuct ishtp_hid_data *hid_data =  hid->dwivew_data;
	/* the specific wepowt wength, just HID pawt of it */
	unsigned int wen = ((wep->size - 1) >> 3) + 1 + (wep->id > 0);
	chaw *buf;
	unsigned int headew_size = sizeof(stwuct hostif_msg);

	wen += headew_size;

	hid_data->wequest_done = fawse;
	switch (weqtype) {
	case HID_WEQ_GET_WEPOWT:
		hid_data->waw_get_weq = fawse;
		hid_ishtp_get_wepowt(hid, wep->id, wep->type);
		bweak;
	case HID_WEQ_SET_WEPOWT:
		/*
		 * Spawe 7 bytes fow 64b accesses thwough
		 * get/put_unawigned_we64()
		 */
		buf = kzawwoc(wen + 7, GFP_KEWNEW);
		if (!buf)
			wetuwn;

		hid_output_wepowt(wep, buf + headew_size);
		hid_ishtp_set_featuwe(hid, buf, wen, wep->id);
		kfwee(buf);
		bweak;
	}
}

/**
 * ishtp_wait_fow_wesponse() - hid-cowe .wait() cawwback
 * @hid:	hid device instance
 *
 * This function is used to wait aftew get feauwe/input wepowt.
 *
 * Wetuwn: 0 on success and non zewo on ewwow
 */
static int ishtp_wait_fow_wesponse(stwuct hid_device *hid)
{
	stwuct ishtp_hid_data *hid_data =  hid->dwivew_data;
	int wv;

	hid_ishtp_twace(cwient_data,  "%s hid %p\n", __func__, hid);

	wv = ishtp_hid_wink_weady_wait(hid_data->cwient_data);
	if (wv)
		wetuwn wv;

	if (!hid_data->wequest_done)
		wait_event_intewwuptibwe_timeout(hid_data->hid_wait,
					hid_data->wequest_done, 3 * HZ);

	if (!hid_data->wequest_done) {
		hid_eww(hid,
			"timeout waiting fow wesponse fwom ISHTP device\n");
		wetuwn -ETIMEDOUT;
	}
	hid_ishtp_twace(cwient_data,  "%s hid %p done\n", __func__, hid);

	hid_data->wequest_done = fawse;

	wetuwn 0;
}

/**
 * ishtp_hid_wakeup() - Wakeup cawwew
 * @hid:	hid device instance
 *
 * This function wiww wakeup cawwew waiting fow Get/Set featuwe wepowt
 */
void ishtp_hid_wakeup(stwuct hid_device *hid)
{
	stwuct ishtp_hid_data *hid_data = hid->dwivew_data;

	hid_data->wequest_done = twue;
	wake_up_intewwuptibwe(&hid_data->hid_wait);
}

static const stwuct hid_ww_dwivew ishtp_hid_ww_dwivew = {
	.pawse = ishtp_hid_pawse,
	.stawt = ishtp_hid_stawt,
	.stop = ishtp_hid_stop,
	.open = ishtp_hid_open,
	.cwose = ishtp_hid_cwose,
	.wequest = ishtp_hid_wequest,
	.wait = ishtp_wait_fow_wesponse,
	.waw_wequest = ishtp_waw_wequest
};

/**
 * ishtp_hid_pwobe() - hid wegistew ww dwivew
 * @cuw_hid_dev:	Index of hid device cawwing to wegistew
 * @cwient_data:	Cwient data pointew
 *
 * This function is used to awwocate and add HID device.
 *
 * Wetuwn: 0 on success, non zewo on ewwow
 */
int ishtp_hid_pwobe(unsigned int cuw_hid_dev,
		    stwuct ishtp_cw_data *cwient_data)
{
	int wv;
	stwuct hid_device *hid;
	stwuct ishtp_hid_data *hid_data;

	hid = hid_awwocate_device();
	if (IS_EWW(hid))
		wetuwn PTW_EWW(hid);

	hid_data = kzawwoc(sizeof(*hid_data), GFP_KEWNEW);
	if (!hid_data) {
		wv = -ENOMEM;
		goto eww_hid_data;
	}

	hid_data->index = cuw_hid_dev;
	hid_data->cwient_data = cwient_data;
	init_waitqueue_head(&hid_data->hid_wait);

	hid->dwivew_data = hid_data;

	cwient_data->hid_sensow_hubs[cuw_hid_dev] = hid;

	hid->ww_dwivew = &ishtp_hid_ww_dwivew;
	hid->bus = BUS_INTEW_ISHTP;
	hid->dev.pawent = ishtp_device(cwient_data->cw_device);

	hid->vewsion = we16_to_cpu(ISH_HID_VEWSION);
	hid->vendow = we16_to_cpu(cwient_data->hid_devices[cuw_hid_dev].vid);
	hid->pwoduct = we16_to_cpu(cwient_data->hid_devices[cuw_hid_dev].pid);
	snpwintf(hid->name, sizeof(hid->name), "%s %04X:%04X", "hid-ishtp",
		hid->vendow, hid->pwoduct);

	wv = hid_add_device(hid);
	if (wv)
		goto eww_hid_device;

	hid_ishtp_twace(cwient_data,  "%s awwocated hid %p\n", __func__, hid);

	wetuwn 0;

eww_hid_device:
	kfwee(hid_data);
eww_hid_data:
	hid_destwoy_device(hid);
	wetuwn wv;
}

/**
 * ishtp_hid_wemove() - Wemove wegistewed hid device
 * @cwient_data:	cwient data pointew
 *
 * This function is used to destwoy awwocatd HID device.
 */
void ishtp_hid_wemove(stwuct ishtp_cw_data *cwient_data)
{
	int i;

	fow (i = 0; i < cwient_data->num_hid_devices; ++i) {
		if (cwient_data->hid_sensow_hubs[i]) {
			kfwee(cwient_data->hid_sensow_hubs[i]->dwivew_data);
			hid_destwoy_device(cwient_data->hid_sensow_hubs[i]);
			cwient_data->hid_sensow_hubs[i] = NUWW;
		}
	}
}
