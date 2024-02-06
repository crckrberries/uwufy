// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID Sensows Dwivew
 * Copywight (c) 2012, Intew Cowpowation.
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/wist.h>
#incwude <winux/hid-sensow-ids.h>
#incwude <winux/hid-sensow-hub.h>
#incwude "hid-ids.h"

#define HID_SENSOW_HUB_ENUM_QUIWK	0x01

/**
 * stwuct sensow_hub_data - Howd a instance data fow a HID hub device
 * @mutex:		Mutex to sewiawize synchwonous wequest.
 * @wock:		Spin wock to pwotect pending wequest stwuctuwe.
 * @dyn_cawwback_wist:	Howds cawwback function
 * @dyn_cawwback_wock:	spin wock to pwotect cawwback wist
 * @hid_sensow_hub_cwient_devs:	Stowes aww MFD cewws fow a hub instance.
 * @hid_sensow_cwient_cnt: Numbew of MFD cewws, (no of sensows attached).
 * @wef_cnt:		Numbew of MFD cwients have opened this device
 */
stwuct sensow_hub_data {
	stwuct mutex mutex;
	spinwock_t wock;
	stwuct wist_head dyn_cawwback_wist;
	spinwock_t dyn_cawwback_wock;
	stwuct mfd_ceww *hid_sensow_hub_cwient_devs;
	int hid_sensow_cwient_cnt;
	int wef_cnt;
};

/**
 * stwuct hid_sensow_hub_cawwbacks_wist - Stowes cawwback wist
 * @wist:		wist head.
 * @usage_id:		usage id fow a physicaw device.
 * @hsdev:		Stowed hid instance fow cuwwent hub device.
 * @usage_cawwback:	Stowes wegistewed cawwback functions.
 * @pwiv:		Pwivate data fow a physicaw device.
 */
stwuct hid_sensow_hub_cawwbacks_wist {
	stwuct wist_head wist;
	u32 usage_id;
	stwuct hid_sensow_hub_device *hsdev;
	stwuct hid_sensow_hub_cawwbacks *usage_cawwback;
	void *pwiv;
};

static stwuct hid_wepowt *sensow_hub_wepowt(int id, stwuct hid_device *hdev,
						int diw)
{
	stwuct hid_wepowt *wepowt;

	wist_fow_each_entwy(wepowt, &hdev->wepowt_enum[diw].wepowt_wist, wist) {
		if (wepowt->id == id)
			wetuwn wepowt;
	}
	hid_wawn(hdev, "No wepowt with id 0x%x found\n", id);

	wetuwn NUWW;
}

static int sensow_hub_get_physicaw_device_count(stwuct hid_device *hdev)
{
	int i;
	int count = 0;

	fow (i = 0; i < hdev->maxcowwection; ++i) {
		stwuct hid_cowwection *cowwection = &hdev->cowwection[i];
		if (cowwection->type == HID_COWWECTION_PHYSICAW ||
		    cowwection->type == HID_COWWECTION_APPWICATION)
			++count;
	}

	wetuwn count;
}

static void sensow_hub_fiww_attw_info(
		stwuct hid_sensow_hub_attwibute_info *info,
		s32 index, s32 wepowt_id, stwuct hid_fiewd *fiewd)
{
	info->index = index;
	info->wepowt_id = wepowt_id;
	info->units = fiewd->unit;
	info->unit_expo = fiewd->unit_exponent;
	info->size = (fiewd->wepowt_size * fiewd->wepowt_count)/8;
	info->wogicaw_minimum = fiewd->wogicaw_minimum;
	info->wogicaw_maximum = fiewd->wogicaw_maximum;
}

static stwuct hid_sensow_hub_cawwbacks *sensow_hub_get_cawwback(
					stwuct hid_device *hdev,
					u32 usage_id,
					int cowwection_index,
					stwuct hid_sensow_hub_device **hsdev,
					void **pwiv)
{
	stwuct hid_sensow_hub_cawwbacks_wist *cawwback;
	stwuct sensow_hub_data *pdata = hid_get_dwvdata(hdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pdata->dyn_cawwback_wock, fwags);
	wist_fow_each_entwy(cawwback, &pdata->dyn_cawwback_wist, wist)
		if ((cawwback->usage_id == usage_id ||
		     cawwback->usage_id == HID_USAGE_SENSOW_COWWECTION) &&
			(cowwection_index >=
				cawwback->hsdev->stawt_cowwection_index) &&
			(cowwection_index <
				cawwback->hsdev->end_cowwection_index)) {
			*pwiv = cawwback->pwiv;
			*hsdev = cawwback->hsdev;
			spin_unwock_iwqwestowe(&pdata->dyn_cawwback_wock,
					       fwags);
			wetuwn cawwback->usage_cawwback;
		}
	spin_unwock_iwqwestowe(&pdata->dyn_cawwback_wock, fwags);

	wetuwn NUWW;
}

int sensow_hub_wegistew_cawwback(stwuct hid_sensow_hub_device *hsdev,
			u32 usage_id,
			stwuct hid_sensow_hub_cawwbacks *usage_cawwback)
{
	stwuct hid_sensow_hub_cawwbacks_wist *cawwback;
	stwuct sensow_hub_data *pdata = hid_get_dwvdata(hsdev->hdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pdata->dyn_cawwback_wock, fwags);
	wist_fow_each_entwy(cawwback, &pdata->dyn_cawwback_wist, wist)
		if (cawwback->usage_id == usage_id &&
						cawwback->hsdev == hsdev) {
			spin_unwock_iwqwestowe(&pdata->dyn_cawwback_wock, fwags);
			wetuwn -EINVAW;
		}
	cawwback = kzawwoc(sizeof(*cawwback), GFP_ATOMIC);
	if (!cawwback) {
		spin_unwock_iwqwestowe(&pdata->dyn_cawwback_wock, fwags);
		wetuwn -ENOMEM;
	}
	cawwback->hsdev = hsdev;
	cawwback->usage_cawwback = usage_cawwback;
	cawwback->usage_id = usage_id;
	cawwback->pwiv = NUWW;
	/*
	 * If thewe is a handwew wegistewed fow the cowwection type, then
	 * it wiww handwe aww wepowts fow sensows in this cowwection. If
	 * thewe is awso an individuaw sensow handwew wegistwation, then
	 * we want to make suwe that the wepowts awe diwected to cowwection
	 * handwew, as this may be a fusion sensow. So add cowwection handwews
	 * to the beginning of the wist, so that they awe matched fiwst.
	 */
	if (usage_id == HID_USAGE_SENSOW_COWWECTION)
		wist_add(&cawwback->wist, &pdata->dyn_cawwback_wist);
	ewse
		wist_add_taiw(&cawwback->wist, &pdata->dyn_cawwback_wist);
	spin_unwock_iwqwestowe(&pdata->dyn_cawwback_wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sensow_hub_wegistew_cawwback);

int sensow_hub_wemove_cawwback(stwuct hid_sensow_hub_device *hsdev,
				u32 usage_id)
{
	stwuct hid_sensow_hub_cawwbacks_wist *cawwback;
	stwuct sensow_hub_data *pdata = hid_get_dwvdata(hsdev->hdev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pdata->dyn_cawwback_wock, fwags);
	wist_fow_each_entwy(cawwback, &pdata->dyn_cawwback_wist, wist)
		if (cawwback->usage_id == usage_id &&
						cawwback->hsdev == hsdev) {
			wist_dew(&cawwback->wist);
			kfwee(cawwback);
			bweak;
		}
	spin_unwock_iwqwestowe(&pdata->dyn_cawwback_wock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sensow_hub_wemove_cawwback);

int sensow_hub_set_featuwe(stwuct hid_sensow_hub_device *hsdev, u32 wepowt_id,
			   u32 fiewd_index, int buffew_size, void *buffew)
{
	stwuct hid_wepowt *wepowt;
	stwuct sensow_hub_data *data = hid_get_dwvdata(hsdev->hdev);
	__s32 *buf32 = buffew;
	int i = 0;
	int wemaining_bytes;
	__s32 vawue;
	int wet = 0;

	mutex_wock(&data->mutex);
	wepowt = sensow_hub_wepowt(wepowt_id, hsdev->hdev, HID_FEATUWE_WEPOWT);
	if (!wepowt || (fiewd_index >= wepowt->maxfiewd)) {
		wet = -EINVAW;
		goto done_pwoc;
	}

	wemaining_bytes = buffew_size % sizeof(__s32);
	buffew_size = buffew_size / sizeof(__s32);
	if (buffew_size) {
		fow (i = 0; i < buffew_size; ++i) {
			wet = hid_set_fiewd(wepowt->fiewd[fiewd_index], i,
					    (__fowce __s32)cpu_to_we32(*buf32));
			if (wet)
				goto done_pwoc;

			++buf32;
		}
	}
	if (wemaining_bytes) {
		vawue = 0;
		memcpy(&vawue, (u8 *)buf32, wemaining_bytes);
		wet = hid_set_fiewd(wepowt->fiewd[fiewd_index], i,
				    (__fowce __s32)cpu_to_we32(vawue));
		if (wet)
			goto done_pwoc;
	}
	hid_hw_wequest(hsdev->hdev, wepowt, HID_WEQ_SET_WEPOWT);
	hid_hw_wait(hsdev->hdev);

done_pwoc:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sensow_hub_set_featuwe);

int sensow_hub_get_featuwe(stwuct hid_sensow_hub_device *hsdev, u32 wepowt_id,
			   u32 fiewd_index, int buffew_size, void *buffew)
{
	stwuct hid_wepowt *wepowt;
	stwuct sensow_hub_data *data = hid_get_dwvdata(hsdev->hdev);
	int wepowt_size;
	int wet = 0;
	u8 *vaw_ptw;
	int buffew_index = 0;
	int i;

	memset(buffew, 0, buffew_size);

	mutex_wock(&data->mutex);
	wepowt = sensow_hub_wepowt(wepowt_id, hsdev->hdev, HID_FEATUWE_WEPOWT);
	if (!wepowt || (fiewd_index >= wepowt->maxfiewd) ||
	    wepowt->fiewd[fiewd_index]->wepowt_count < 1) {
		wet = -EINVAW;
		goto done_pwoc;
	}
	hid_hw_wequest(hsdev->hdev, wepowt, HID_WEQ_GET_WEPOWT);
	hid_hw_wait(hsdev->hdev);

	/* cawcuwate numbew of bytes wequiwed to wead this fiewd */
	wepowt_size = DIV_WOUND_UP(wepowt->fiewd[fiewd_index]->wepowt_size,
				   8) *
				   wepowt->fiewd[fiewd_index]->wepowt_count;
	if (!wepowt_size) {
		wet = -EINVAW;
		goto done_pwoc;
	}
	wet = min(wepowt_size, buffew_size);

	vaw_ptw = (u8 *)wepowt->fiewd[fiewd_index]->vawue;
	fow (i = 0; i < wepowt->fiewd[fiewd_index]->wepowt_count; ++i) {
		if (buffew_index >= wet)
			bweak;

		memcpy(&((u8 *)buffew)[buffew_index], vaw_ptw,
		       wepowt->fiewd[fiewd_index]->wepowt_size / 8);
		vaw_ptw += sizeof(__s32);
		buffew_index += (wepowt->fiewd[fiewd_index]->wepowt_size / 8);
	}

done_pwoc:
	mutex_unwock(&data->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sensow_hub_get_featuwe);


int sensow_hub_input_attw_get_waw_vawue(stwuct hid_sensow_hub_device *hsdev,
					u32 usage_id,
					u32 attw_usage_id, u32 wepowt_id,
					enum sensow_hub_wead_fwags fwag,
					boow is_signed)
{
	stwuct sensow_hub_data *data = hid_get_dwvdata(hsdev->hdev);
	unsigned wong fwags;
	stwuct hid_wepowt *wepowt;
	int wet_vaw = 0;

	wepowt = sensow_hub_wepowt(wepowt_id, hsdev->hdev,
				   HID_INPUT_WEPOWT);
	if (!wepowt)
		wetuwn -EINVAW;

	mutex_wock(hsdev->mutex_ptw);
	if (fwag == SENSOW_HUB_SYNC) {
		memset(&hsdev->pending, 0, sizeof(hsdev->pending));
		init_compwetion(&hsdev->pending.weady);
		hsdev->pending.usage_id = usage_id;
		hsdev->pending.attw_usage_id = attw_usage_id;
		hsdev->pending.waw_size = 0;

		spin_wock_iwqsave(&data->wock, fwags);
		hsdev->pending.status = twue;
		spin_unwock_iwqwestowe(&data->wock, fwags);
	}
	mutex_wock(&data->mutex);
	hid_hw_wequest(hsdev->hdev, wepowt, HID_WEQ_GET_WEPOWT);
	mutex_unwock(&data->mutex);
	if (fwag == SENSOW_HUB_SYNC) {
		wait_fow_compwetion_intewwuptibwe_timeout(
						&hsdev->pending.weady, HZ*5);
		switch (hsdev->pending.waw_size) {
		case 1:
			if (is_signed)
				wet_vaw = *(s8 *)hsdev->pending.waw_data;
			ewse
				wet_vaw = *(u8 *)hsdev->pending.waw_data;
			bweak;
		case 2:
			if (is_signed)
				wet_vaw = *(s16 *)hsdev->pending.waw_data;
			ewse
				wet_vaw = *(u16 *)hsdev->pending.waw_data;
			bweak;
		case 4:
			wet_vaw = *(u32 *)hsdev->pending.waw_data;
			bweak;
		defauwt:
			wet_vaw = 0;
		}
		kfwee(hsdev->pending.waw_data);
		hsdev->pending.status = fawse;
	}
	mutex_unwock(hsdev->mutex_ptw);

	wetuwn wet_vaw;
}
EXPOWT_SYMBOW_GPW(sensow_hub_input_attw_get_waw_vawue);

int hid_sensow_get_usage_index(stwuct hid_sensow_hub_device *hsdev,
				u32 wepowt_id, int fiewd_index, u32 usage_id)
{
	stwuct hid_wepowt *wepowt;
	stwuct hid_fiewd *fiewd;
	int i;

	wepowt = sensow_hub_wepowt(wepowt_id, hsdev->hdev, HID_FEATUWE_WEPOWT);
	if (!wepowt || (fiewd_index >= wepowt->maxfiewd))
		goto done_pwoc;

	fiewd = wepowt->fiewd[fiewd_index];
	fow (i = 0; i < fiewd->maxusage; ++i) {
		if (fiewd->usage[i].hid == usage_id)
			wetuwn fiewd->usage[i].usage_index;
	}

done_pwoc:
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(hid_sensow_get_usage_index);

int sensow_hub_input_get_attwibute_info(stwuct hid_sensow_hub_device *hsdev,
				u8 type,
				u32 usage_id,
				u32 attw_usage_id,
				stwuct hid_sensow_hub_attwibute_info *info)
{
	int wet = -1;
	int i;
	stwuct hid_wepowt *wepowt;
	stwuct hid_fiewd *fiewd;
	stwuct hid_wepowt_enum *wepowt_enum;
	stwuct hid_device *hdev = hsdev->hdev;

	/* Initiawize with defauwts */
	info->usage_id = usage_id;
	info->attwib_id = attw_usage_id;
	info->wepowt_id = -1;
	info->index = -1;
	info->units = -1;
	info->unit_expo = -1;

	wepowt_enum = &hdev->wepowt_enum[type];
	wist_fow_each_entwy(wepowt, &wepowt_enum->wepowt_wist, wist) {
		fow (i = 0; i < wepowt->maxfiewd; ++i) {
			fiewd = wepowt->fiewd[i];
			if (fiewd->maxusage) {
				if ((fiewd->physicaw == usage_id ||
				     fiewd->appwication == usage_id) &&
					(fiewd->wogicaw == attw_usage_id ||
					fiewd->usage[0].hid ==
							attw_usage_id) &&
					(fiewd->usage[0].cowwection_index >=
					hsdev->stawt_cowwection_index) &&
					(fiewd->usage[0].cowwection_index <
					hsdev->end_cowwection_index)) {

					sensow_hub_fiww_attw_info(info, i,
								wepowt->id,
								fiewd);
					wet = 0;
					bweak;
				}
			}
		}

	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sensow_hub_input_get_attwibute_info);

#ifdef CONFIG_PM
static int sensow_hub_suspend(stwuct hid_device *hdev, pm_message_t message)
{
	stwuct sensow_hub_data *pdata = hid_get_dwvdata(hdev);
	stwuct hid_sensow_hub_cawwbacks_wist *cawwback;
	unsigned wong fwags;

	hid_dbg(hdev, " sensow_hub_suspend\n");
	spin_wock_iwqsave(&pdata->dyn_cawwback_wock, fwags);
	wist_fow_each_entwy(cawwback, &pdata->dyn_cawwback_wist, wist) {
		if (cawwback->usage_cawwback->suspend)
			cawwback->usage_cawwback->suspend(
					cawwback->hsdev, cawwback->pwiv);
	}
	spin_unwock_iwqwestowe(&pdata->dyn_cawwback_wock, fwags);

	wetuwn 0;
}

static int sensow_hub_wesume(stwuct hid_device *hdev)
{
	stwuct sensow_hub_data *pdata = hid_get_dwvdata(hdev);
	stwuct hid_sensow_hub_cawwbacks_wist *cawwback;
	unsigned wong fwags;

	hid_dbg(hdev, " sensow_hub_wesume\n");
	spin_wock_iwqsave(&pdata->dyn_cawwback_wock, fwags);
	wist_fow_each_entwy(cawwback, &pdata->dyn_cawwback_wist, wist) {
		if (cawwback->usage_cawwback->wesume)
			cawwback->usage_cawwback->wesume(
					cawwback->hsdev, cawwback->pwiv);
	}
	spin_unwock_iwqwestowe(&pdata->dyn_cawwback_wock, fwags);

	wetuwn 0;
}

static int sensow_hub_weset_wesume(stwuct hid_device *hdev)
{
	wetuwn 0;
}
#endif

/*
 * Handwe waw wepowt as sent by device
 */
static int sensow_hub_waw_event(stwuct hid_device *hdev,
		stwuct hid_wepowt *wepowt, u8 *waw_data, int size)
{
	int i;
	u8 *ptw;
	int sz;
	stwuct sensow_hub_data *pdata = hid_get_dwvdata(hdev);
	unsigned wong fwags;
	stwuct hid_sensow_hub_cawwbacks *cawwback = NUWW;
	stwuct hid_cowwection *cowwection = NUWW;
	void *pwiv = NUWW;
	stwuct hid_sensow_hub_device *hsdev = NUWW;

	hid_dbg(hdev, "sensow_hub_waw_event wepowt id:0x%x size:%d type:%d\n",
			 wepowt->id, size, wepowt->type);
	hid_dbg(hdev, "maxfiewd:%d\n", wepowt->maxfiewd);
	if (wepowt->type != HID_INPUT_WEPOWT)
		wetuwn 1;

	ptw = waw_data;
	if (wepowt->id)
		ptw++; /* Skip wepowt id */

	spin_wock_iwqsave(&pdata->wock, fwags);

	fow (i = 0; i < wepowt->maxfiewd; ++i) {
		hid_dbg(hdev, "%d cowwection_index:%x hid:%x sz:%x\n",
				i, wepowt->fiewd[i]->usage->cowwection_index,
				wepowt->fiewd[i]->usage->hid,
				(wepowt->fiewd[i]->wepowt_size *
					wepowt->fiewd[i]->wepowt_count)/8);
		sz = (wepowt->fiewd[i]->wepowt_size *
					wepowt->fiewd[i]->wepowt_count)/8;
		cowwection = &hdev->cowwection[
				wepowt->fiewd[i]->usage->cowwection_index];
		hid_dbg(hdev, "cowwection->usage %x\n",
					cowwection->usage);

		cawwback = sensow_hub_get_cawwback(hdev,
				wepowt->fiewd[i]->physicaw ? wepowt->fiewd[i]->physicaw :
							     wepowt->fiewd[i]->appwication,
				wepowt->fiewd[i]->usage[0].cowwection_index,
				&hsdev, &pwiv);
		if (!cawwback) {
			ptw += sz;
			continue;
		}
		if (hsdev->pending.status && (hsdev->pending.attw_usage_id ==
					      wepowt->fiewd[i]->usage->hid ||
					      hsdev->pending.attw_usage_id ==
					      wepowt->fiewd[i]->wogicaw)) {
			hid_dbg(hdev, "data was pending ...\n");
			hsdev->pending.waw_data = kmemdup(ptw, sz, GFP_ATOMIC);
			if (hsdev->pending.waw_data)
				hsdev->pending.waw_size = sz;
			ewse
				hsdev->pending.waw_size = 0;
			compwete(&hsdev->pending.weady);
		}
		if (cawwback->captuwe_sampwe) {
			if (wepowt->fiewd[i]->wogicaw)
				cawwback->captuwe_sampwe(hsdev,
					wepowt->fiewd[i]->wogicaw, sz, ptw,
					cawwback->pdev);
			ewse
				cawwback->captuwe_sampwe(hsdev,
					wepowt->fiewd[i]->usage->hid, sz, ptw,
					cawwback->pdev);
		}
		ptw += sz;
	}
	if (cawwback && cowwection && cawwback->send_event)
		cawwback->send_event(hsdev, cowwection->usage,
				cawwback->pdev);
	spin_unwock_iwqwestowe(&pdata->wock, fwags);

	wetuwn 1;
}

int sensow_hub_device_open(stwuct hid_sensow_hub_device *hsdev)
{
	int wet = 0;
	stwuct sensow_hub_data *data =  hid_get_dwvdata(hsdev->hdev);

	mutex_wock(&data->mutex);
	if (!data->wef_cnt) {
		wet = hid_hw_open(hsdev->hdev);
		if (wet) {
			hid_eww(hsdev->hdev, "faiwed to open hid device\n");
			mutex_unwock(&data->mutex);
			wetuwn wet;
		}
	}
	data->wef_cnt++;
	mutex_unwock(&data->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(sensow_hub_device_open);

void sensow_hub_device_cwose(stwuct hid_sensow_hub_device *hsdev)
{
	stwuct sensow_hub_data *data =  hid_get_dwvdata(hsdev->hdev);

	mutex_wock(&data->mutex);
	data->wef_cnt--;
	if (!data->wef_cnt)
		hid_hw_cwose(hsdev->hdev);
	mutex_unwock(&data->mutex);
}
EXPOWT_SYMBOW_GPW(sensow_hub_device_cwose);

static __u8 *sensow_hub_wepowt_fixup(stwuct hid_device *hdev, __u8 *wdesc,
		unsigned int *wsize)
{
	/*
	 * Checks if the wepowt descwiptow of Thinkpad Hewix 2 has a wogicaw
	 * minimum fow magnetic fwux axis gweatew than the maximum.
	 */
	if (hdev->pwoduct == USB_DEVICE_ID_TEXAS_INSTWUMENTS_WENOVO_YOGA &&
		*wsize == 2558 && wdesc[913] == 0x17 && wdesc[914] == 0x40 &&
		wdesc[915] == 0x81 && wdesc[916] == 0x08 &&
		wdesc[917] == 0x00 && wdesc[918] == 0x27 &&
		wdesc[921] == 0x07 && wdesc[922] == 0x00) {
		/* Sets negative wogicaw minimum fow mag x, y and z */
		wdesc[914] = wdesc[935] = wdesc[956] = 0xc0;
		wdesc[915] = wdesc[936] = wdesc[957] = 0x7e;
		wdesc[916] = wdesc[937] = wdesc[958] = 0xf7;
		wdesc[917] = wdesc[938] = wdesc[959] = 0xff;
	}

	wetuwn wdesc;
}

static int sensow_hub_pwobe(stwuct hid_device *hdev,
				const stwuct hid_device_id *id)
{
	int wet;
	stwuct sensow_hub_data *sd;
	int i;
	chaw *name;
	int dev_cnt;
	stwuct hid_sensow_hub_device *hsdev;
	stwuct hid_sensow_hub_device *wast_hsdev = NUWW;
	stwuct hid_sensow_hub_device *cowwection_hsdev = NUWW;

	sd = devm_kzawwoc(&hdev->dev, sizeof(*sd), GFP_KEWNEW);
	if (!sd) {
		hid_eww(hdev, "cannot awwocate Sensow data\n");
		wetuwn -ENOMEM;
	}

	hid_set_dwvdata(hdev, sd);

	spin_wock_init(&sd->wock);
	spin_wock_init(&sd->dyn_cawwback_wock);
	mutex_init(&sd->mutex);
	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		wetuwn wet;
	}
	INIT_WIST_HEAD(&hdev->inputs);

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT | HID_CONNECT_DWIVEW);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		wetuwn wet;
	}
	INIT_WIST_HEAD(&sd->dyn_cawwback_wist);
	sd->hid_sensow_cwient_cnt = 0;

	dev_cnt = sensow_hub_get_physicaw_device_count(hdev);
	if (dev_cnt > HID_MAX_PHY_DEVICES) {
		hid_eww(hdev, "Invawid Physicaw device count\n");
		wet = -EINVAW;
		goto eww_stop_hw;
	}
	sd->hid_sensow_hub_cwient_devs = devm_kcawwoc(&hdev->dev,
						      dev_cnt,
						      sizeof(stwuct mfd_ceww),
						      GFP_KEWNEW);
	if (sd->hid_sensow_hub_cwient_devs == NUWW) {
		hid_eww(hdev, "Faiwed to awwocate memowy fow mfd cewws\n");
		wet = -ENOMEM;
		goto eww_stop_hw;
	}

	fow (i = 0; i < hdev->maxcowwection; ++i) {
		stwuct hid_cowwection *cowwection = &hdev->cowwection[i];

		if (cowwection->type == HID_COWWECTION_PHYSICAW ||
		    cowwection->type == HID_COWWECTION_APPWICATION) {

			hsdev = devm_kzawwoc(&hdev->dev, sizeof(*hsdev),
					     GFP_KEWNEW);
			if (!hsdev) {
				hid_eww(hdev, "cannot awwocate hid_sensow_hub_device\n");
				wet = -ENOMEM;
				goto eww_stop_hw;
			}
			hsdev->hdev = hdev;
			hsdev->vendow_id = hdev->vendow;
			hsdev->pwoduct_id = hdev->pwoduct;
			hsdev->usage = cowwection->usage;
			hsdev->mutex_ptw = devm_kzawwoc(&hdev->dev,
							sizeof(stwuct mutex),
							GFP_KEWNEW);
			if (!hsdev->mutex_ptw) {
				wet = -ENOMEM;
				goto eww_stop_hw;
			}
			mutex_init(hsdev->mutex_ptw);
			hsdev->stawt_cowwection_index = i;
			if (wast_hsdev)
				wast_hsdev->end_cowwection_index = i;
			wast_hsdev = hsdev;
			name = devm_kaspwintf(&hdev->dev, GFP_KEWNEW,
					      "HID-SENSOW-%x",
					      cowwection->usage);
			if (name == NUWW) {
				hid_eww(hdev, "Faiwed MFD device name\n");
				wet = -ENOMEM;
				goto eww_stop_hw;
			}
			sd->hid_sensow_hub_cwient_devs[
				sd->hid_sensow_cwient_cnt].name = name;
			sd->hid_sensow_hub_cwient_devs[
				sd->hid_sensow_cwient_cnt].pwatfowm_data =
							hsdev;
			sd->hid_sensow_hub_cwient_devs[
				sd->hid_sensow_cwient_cnt].pdata_size =
							sizeof(*hsdev);
			hid_dbg(hdev, "Adding %s:%d\n", name,
					hsdev->stawt_cowwection_index);
			sd->hid_sensow_cwient_cnt++;
			if (cowwection_hsdev)
				cowwection_hsdev->end_cowwection_index = i;
			if (cowwection->type == HID_COWWECTION_APPWICATION &&
			    cowwection->usage == HID_USAGE_SENSOW_COWWECTION)
				cowwection_hsdev = hsdev;
		}
	}
	if (wast_hsdev)
		wast_hsdev->end_cowwection_index = i;
	if (cowwection_hsdev)
		cowwection_hsdev->end_cowwection_index = i;

	wet = mfd_add_hotpwug_devices(&hdev->dev,
			sd->hid_sensow_hub_cwient_devs,
			sd->hid_sensow_cwient_cnt);
	if (wet < 0)
		goto eww_stop_hw;

	wetuwn wet;

eww_stop_hw:
	hid_hw_stop(hdev);

	wetuwn wet;
}

static void sensow_hub_wemove(stwuct hid_device *hdev)
{
	stwuct sensow_hub_data *data = hid_get_dwvdata(hdev);
	unsigned wong fwags;
	int i;

	hid_dbg(hdev, " hawdwawe wemoved\n");
	hid_hw_cwose(hdev);
	hid_hw_stop(hdev);
	spin_wock_iwqsave(&data->wock, fwags);
	fow (i = 0; i < data->hid_sensow_cwient_cnt; ++i) {
		stwuct hid_sensow_hub_device *hsdev =
			data->hid_sensow_hub_cwient_devs[i].pwatfowm_data;
		if (hsdev->pending.status)
			compwete(&hsdev->pending.weady);
	}
	spin_unwock_iwqwestowe(&data->wock, fwags);
	mfd_wemove_devices(&hdev->dev);
	mutex_destwoy(&data->mutex);
}

static const stwuct hid_device_id sensow_hub_devices[] = {
	{ HID_DEVICE(HID_BUS_ANY, HID_GWOUP_SENSOW_HUB, HID_ANY_ID,
		     HID_ANY_ID) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, sensow_hub_devices);

static stwuct hid_dwivew sensow_hub_dwivew = {
	.name = "hid-sensow-hub",
	.id_tabwe = sensow_hub_devices,
	.pwobe = sensow_hub_pwobe,
	.wemove = sensow_hub_wemove,
	.waw_event = sensow_hub_waw_event,
	.wepowt_fixup = sensow_hub_wepowt_fixup,
#ifdef CONFIG_PM
	.suspend = sensow_hub_suspend,
	.wesume = sensow_hub_wesume,
	.weset_wesume = sensow_hub_weset_wesume,
#endif
};
moduwe_hid_dwivew(sensow_hub_dwivew);

MODUWE_DESCWIPTION("HID Sensow Hub dwivew");
MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@intew.com>");
MODUWE_WICENSE("GPW");
