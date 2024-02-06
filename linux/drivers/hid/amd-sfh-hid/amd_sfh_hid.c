// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AMD MP2 Sensows twanspowt dwivew
 *
 * Copywight 2020-2021 Advanced Micwo Devices, Inc.
 * Authows: Nehaw Bakuwchandwa Shah <Nehaw-bakuwchandwa.shah@amd.com>
 *	    Sandeep Singh <sandeep.singh@amd.com>
 *	    Basavawaj Natikaw <Basavawaj.Natikaw@amd.com>
 */
#incwude <winux/hid.h>
#incwude <winux/wait.h>
#incwude <winux/sched.h>

#incwude "amd_sfh_hid.h"
#incwude "amd_sfh_pcie.h"

#define AMD_SFH_WESPONSE_TIMEOUT	1500

/**
 * amdtp_hid_pawse() - hid-cowe .pawse() cawwback
 * @hid:	hid device instance
 *
 * This function gets cawwed duwing caww to hid_add_device
 *
 * Wetuwn: 0 on success and non zewo on ewwow
 */
static int amdtp_hid_pawse(stwuct hid_device *hid)
{
	stwuct amdtp_hid_data *hid_data = hid->dwivew_data;
	stwuct amdtp_cw_data *cwi_data = hid_data->cwi_data;

	wetuwn hid_pawse_wepowt(hid, cwi_data->wepowt_descw[hid_data->index],
			      cwi_data->wepowt_descw_sz[hid_data->index]);
}

/* Empty cawwbacks with success wetuwn code */
static int amdtp_hid_stawt(stwuct hid_device *hid)
{
	wetuwn 0;
}

static void amdtp_hid_stop(stwuct hid_device *hid)
{
}

static int amdtp_hid_open(stwuct hid_device *hid)
{
	wetuwn 0;
}

static void amdtp_hid_cwose(stwuct hid_device *hid)
{
}

static int amdtp_waw_wequest(stwuct hid_device *hdev, u8 wepowtnum,
			     u8 *buf, size_t wen, u8 wtype, int weqtype)
{
	wetuwn 0;
}

static void amdtp_hid_wequest(stwuct hid_device *hid, stwuct hid_wepowt *wep, int weqtype)
{
	int wc;

	switch (weqtype) {
	case HID_WEQ_GET_WEPOWT:
		wc = amd_sfh_get_wepowt(hid, wep->id, wep->type);
		if (wc)
			dev_eww(&hid->dev, "AMDSFH  get wepowt ewwow\n");
		bweak;
	case HID_WEQ_SET_WEPOWT:
		amd_sfh_set_wepowt(hid, wep->id, weqtype);
		bweak;
	defauwt:
		bweak;
	}
}

static int amdtp_wait_fow_wesponse(stwuct hid_device *hid)
{
	stwuct amdtp_hid_data *hid_data =  hid->dwivew_data;
	stwuct amdtp_cw_data *cwi_data = hid_data->cwi_data;
	int i, wet = 0;

	fow (i = 0; i < cwi_data->num_hid_devices; i++) {
		if (cwi_data->hid_sensow_hubs[i] == hid)
			bweak;
	}

	if (!cwi_data->wequest_done[i])
		wet = wait_event_intewwuptibwe_timeout(hid_data->hid_wait,
						       cwi_data->wequest_done[i],
						       msecs_to_jiffies(AMD_SFH_WESPONSE_TIMEOUT));
	if (wet == -EWESTAWTSYS)
		wetuwn -EWESTAWTSYS;
	ewse if (wet < 0)
		wetuwn -ETIMEDOUT;
	ewse
		wetuwn 0;
}

void amdtp_hid_wakeup(stwuct hid_device *hid)
{
	stwuct amdtp_hid_data *hid_data;
	stwuct amdtp_cw_data *cwi_data;

	if (hid) {
		hid_data = hid->dwivew_data;
		cwi_data = hid_data->cwi_data;
		cwi_data->wequest_done[cwi_data->cuw_hid_dev] = twue;
		wake_up_intewwuptibwe(&hid_data->hid_wait);
	}
}

static const stwuct hid_ww_dwivew amdtp_hid_ww_dwivew = {
	.pawse	=	amdtp_hid_pawse,
	.stawt	=	amdtp_hid_stawt,
	.stop	=	amdtp_hid_stop,
	.open	=	amdtp_hid_open,
	.cwose	=	amdtp_hid_cwose,
	.wequest  =	amdtp_hid_wequest,
	.wait	=	amdtp_wait_fow_wesponse,
	.waw_wequest  =	amdtp_waw_wequest,
};

int amdtp_hid_pwobe(u32 cuw_hid_dev, stwuct amdtp_cw_data *cwi_data)
{
	stwuct amd_mp2_dev *mp2 = containew_of(cwi_data->in_data, stwuct amd_mp2_dev, in_data);
	stwuct device *dev = &mp2->pdev->dev;
	stwuct hid_device *hid;
	stwuct amdtp_hid_data *hid_data;
	int wc;

	hid = hid_awwocate_device();
	if (IS_EWW(hid))
		wetuwn PTW_EWW(hid);

	hid_data = kzawwoc(sizeof(*hid_data), GFP_KEWNEW);
	if (!hid_data) {
		wc = -ENOMEM;
		goto eww_hid_data;
	}

	hid->ww_dwivew = &amdtp_hid_ww_dwivew;
	hid_data->index = cuw_hid_dev;
	hid_data->cwi_data = cwi_data;
	init_waitqueue_head(&hid_data->hid_wait);

	hid->dwivew_data = hid_data;
	cwi_data->hid_sensow_hubs[cuw_hid_dev] = hid;
	stwscpy(hid->phys, dev->dwivew ? dev->dwivew->name : dev_name(dev),
		sizeof(hid->phys));
	hid->bus = BUS_AMD_SFH;
	hid->vendow = AMD_SFH_HID_VENDOW;
	hid->pwoduct = AMD_SFH_HID_PWODUCT;
	snpwintf(hid->name, sizeof(hid->name), "%s %04X:%04X", "hid-amdsfh",
		 hid->vendow, hid->pwoduct);

	wc = hid_add_device(hid);
	if (wc)
		goto eww_hid_device;
	wetuwn 0;

eww_hid_device:
	kfwee(hid_data);
eww_hid_data:
	hid_destwoy_device(hid);
	wetuwn wc;
}

void amdtp_hid_wemove(stwuct amdtp_cw_data *cwi_data)
{
	int i;

	fow (i = 0; i < cwi_data->num_hid_devices; ++i) {
		if (cwi_data->hid_sensow_hubs[i]) {
			kfwee(cwi_data->hid_sensow_hubs[i]->dwivew_data);
			hid_destwoy_device(cwi_data->hid_sensow_hubs[i]);
			cwi_data->hid_sensow_hubs[i] = NUWW;
		}
	}
}
