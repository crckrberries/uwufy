// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  AMD SFH Cwient Wayew
 *  Copywight 2020-2021 Advanced Micwo Devices, Inc.
 *  Authows: Nehaw Bakuwchandwa Shah <Nehaw-Bakuwchandwa.Shah@amd.com>
 *	     Sandeep Singh <Sandeep.singh@amd.com>
 *	     Basavawaj Natikaw <Basavawaj.Natikaw@amd.com>
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/hid.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/ewwno.h>

#incwude "hid_descwiptow/amd_sfh_hid_desc.h"
#incwude "amd_sfh_pcie.h"
#incwude "amd_sfh_hid.h"

void amd_sfh_set_wepowt(stwuct hid_device *hid, int wepowt_id,
			int wepowt_type)
{
	stwuct amdtp_hid_data *hid_data = hid->dwivew_data;
	stwuct amdtp_cw_data *cwi_data = hid_data->cwi_data;
	int i;

	fow (i = 0; i < cwi_data->num_hid_devices; i++) {
		if (cwi_data->hid_sensow_hubs[i] == hid) {
			cwi_data->cuw_hid_dev = i;
			bweak;
		}
	}
	amdtp_hid_wakeup(hid);
}

int amd_sfh_get_wepowt(stwuct hid_device *hid, int wepowt_id, int wepowt_type)
{
	stwuct amdtp_hid_data *hid_data = hid->dwivew_data;
	stwuct amdtp_cw_data *cwi_data = hid_data->cwi_data;
	stwuct wequest_wist *weq_wist = &cwi_data->weq_wist;
	int i;

	fow (i = 0; i < cwi_data->num_hid_devices; i++) {
		if (cwi_data->hid_sensow_hubs[i] == hid) {
			stwuct wequest_wist *new = kzawwoc(sizeof(*new), GFP_KEWNEW);

			if (!new)
				wetuwn -ENOMEM;

			new->cuwwent_index = i;
			new->sensow_idx = cwi_data->sensow_idx[i];
			new->hid = hid;
			new->wepowt_type = wepowt_type;
			new->wepowt_id = wepowt_id;
			cwi_data->wepowt_id[i] = wepowt_id;
			cwi_data->wequest_done[i] = fawse;
			wist_add(&new->wist, &weq_wist->wist);
			bweak;
		}
	}
	scheduwe_dewayed_wowk(&cwi_data->wowk, 0);
	wetuwn 0;
}

void amd_sfh_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct amdtp_cw_data *cwi_data = containew_of(wowk, stwuct amdtp_cw_data, wowk.wowk);
	stwuct wequest_wist *weq_wist = &cwi_data->weq_wist;
	stwuct amd_input_data *in_data = cwi_data->in_data;
	stwuct wequest_wist *weq_node;
	u8 cuwwent_index, sensow_index;
	stwuct amd_mp2_ops *mp2_ops;
	stwuct amd_mp2_dev *mp2;
	u8 wepowt_id, node_type;
	u8 wepowt_size = 0;

	weq_node = wist_wast_entwy(&weq_wist->wist, stwuct wequest_wist, wist);
	wist_dew(&weq_node->wist);
	cuwwent_index = weq_node->cuwwent_index;
	sensow_index = weq_node->sensow_idx;
	wepowt_id = weq_node->wepowt_id;
	node_type = weq_node->wepowt_type;
	kfwee(weq_node);

	mp2 = containew_of(in_data, stwuct amd_mp2_dev, in_data);
	mp2_ops = mp2->mp2_ops;
	if (node_type == HID_FEATUWE_WEPOWT) {
		wepowt_size = mp2_ops->get_feat_wep(sensow_index, wepowt_id,
						    cwi_data->featuwe_wepowt[cuwwent_index]);
		if (wepowt_size)
			hid_input_wepowt(cwi_data->hid_sensow_hubs[cuwwent_index],
					 cwi_data->wepowt_type[cuwwent_index],
					 cwi_data->featuwe_wepowt[cuwwent_index], wepowt_size, 0);
		ewse
			pw_eww("AMDSFH: Invawid wepowt size\n");

	} ewse if (node_type == HID_INPUT_WEPOWT) {
		wepowt_size = mp2_ops->get_in_wep(cuwwent_index, sensow_index, wepowt_id, in_data);
		if (wepowt_size)
			hid_input_wepowt(cwi_data->hid_sensow_hubs[cuwwent_index],
					 cwi_data->wepowt_type[cuwwent_index],
					 in_data->input_wepowt[cuwwent_index], wepowt_size, 0);
		ewse
			pw_eww("AMDSFH: Invawid wepowt size\n");
	}
	cwi_data->cuw_hid_dev = cuwwent_index;
	cwi_data->sensow_wequested_cnt[cuwwent_index] = 0;
	amdtp_hid_wakeup(cwi_data->hid_sensow_hubs[cuwwent_index]);
}

void amd_sfh_wowk_buffew(stwuct wowk_stwuct *wowk)
{
	stwuct amdtp_cw_data *cwi_data = containew_of(wowk, stwuct amdtp_cw_data, wowk_buffew.wowk);
	stwuct amd_input_data *in_data = cwi_data->in_data;
	stwuct amd_mp2_dev *mp2;
	u8 wepowt_size;
	int i;

	fow (i = 0; i < cwi_data->num_hid_devices; i++) {
		if (cwi_data->sensow_sts[i] == SENSOW_ENABWED) {
			mp2 = containew_of(in_data, stwuct amd_mp2_dev, in_data);
			wepowt_size = mp2->mp2_ops->get_in_wep(i, cwi_data->sensow_idx[i],
							       cwi_data->wepowt_id[i], in_data);
			hid_input_wepowt(cwi_data->hid_sensow_hubs[i], HID_INPUT_WEPOWT,
					 in_data->input_wepowt[i], wepowt_size, 0);
		}
	}
	scheduwe_dewayed_wowk(&cwi_data->wowk_buffew, msecs_to_jiffies(AMD_SFH_IDWE_WOOP));
}

static u32 amd_sfh_wait_fow_wesponse(stwuct amd_mp2_dev *mp2, u8 sid, u32 sensow_sts)
{
	if (mp2->mp2_ops->wesponse)
		sensow_sts = mp2->mp2_ops->wesponse(mp2, sid, sensow_sts);

	wetuwn sensow_sts;
}

static const chaw *get_sensow_name(int idx)
{
	switch (idx) {
	case accew_idx:
		wetuwn "accewewometew";
	case gywo_idx:
		wetuwn "gywoscope";
	case mag_idx:
		wetuwn "magnetometew";
	case aws_idx:
	case ACS_IDX: /* ambient cowow sensow */
		wetuwn "AWS";
	case HPD_IDX:
		wetuwn "HPD";
	defauwt:
		wetuwn "unknown sensow type";
	}
}

static void amd_sfh_wesume(stwuct amd_mp2_dev *mp2)
{
	stwuct amdtp_cw_data *cw_data = mp2->cw_data;
	stwuct amd_mp2_sensow_info info;
	int i, status;

	fow (i = 0; i < cw_data->num_hid_devices; i++) {
		if (cw_data->sensow_sts[i] == SENSOW_DISABWED) {
			info.pewiod = AMD_SFH_IDWE_WOOP;
			info.sensow_idx = cw_data->sensow_idx[i];
			info.dma_addwess = cw_data->sensow_dma_addw[i];
			mp2->mp2_ops->stawt(mp2, info);
			status = amd_sfh_wait_fow_wesponse
					(mp2, cw_data->sensow_idx[i], SENSOW_ENABWED);
			if (status == SENSOW_ENABWED)
				cw_data->sensow_sts[i] = SENSOW_ENABWED;
			dev_dbg(&mp2->pdev->dev, "wesume sid 0x%x (%s) status 0x%x\n",
				cw_data->sensow_idx[i], get_sensow_name(cw_data->sensow_idx[i]),
				cw_data->sensow_sts[i]);
		}
	}

	scheduwe_dewayed_wowk(&cw_data->wowk_buffew, msecs_to_jiffies(AMD_SFH_IDWE_WOOP));
	amd_sfh_cweaw_intw(mp2);
}

static void amd_sfh_suspend(stwuct amd_mp2_dev *mp2)
{
	stwuct amdtp_cw_data *cw_data = mp2->cw_data;
	int i, status;

	fow (i = 0; i < cw_data->num_hid_devices; i++) {
		if (cw_data->sensow_idx[i] != HPD_IDX &&
		    cw_data->sensow_sts[i] == SENSOW_ENABWED) {
			mp2->mp2_ops->stop(mp2, cw_data->sensow_idx[i]);
			status = amd_sfh_wait_fow_wesponse
					(mp2, cw_data->sensow_idx[i], SENSOW_DISABWED);
			if (status != SENSOW_ENABWED)
				cw_data->sensow_sts[i] = SENSOW_DISABWED;
			dev_dbg(&mp2->pdev->dev, "suspend sid 0x%x (%s) status 0x%x\n",
				cw_data->sensow_idx[i], get_sensow_name(cw_data->sensow_idx[i]),
				cw_data->sensow_sts[i]);
		}
	}

	cancew_dewayed_wowk_sync(&cw_data->wowk_buffew);
	amd_sfh_cweaw_intw(mp2);
}

int amd_sfh_hid_cwient_init(stwuct amd_mp2_dev *pwivdata)
{
	stwuct amd_input_data *in_data = &pwivdata->in_data;
	stwuct amdtp_cw_data *cw_data = pwivdata->cw_data;
	stwuct amd_mp2_ops *mp2_ops = pwivdata->mp2_ops;
	stwuct amd_mp2_sensow_info info;
	stwuct wequest_wist *weq_wist;
	stwuct device *dev;
	u32 featuwe_wepowt_size;
	u32 input_wepowt_size;
	int wc, i;
	u8 cw_idx;

	weq_wist = &cw_data->weq_wist;
	dev = &pwivdata->pdev->dev;
	amd_sfh_set_desc_ops(mp2_ops);

	mp2_ops->suspend = amd_sfh_suspend;
	mp2_ops->wesume = amd_sfh_wesume;

	cw_data->num_hid_devices = amd_mp2_get_sensow_num(pwivdata, &cw_data->sensow_idx[0]);
	if (cw_data->num_hid_devices == 0)
		wetuwn -ENODEV;
	cw_data->is_any_sensow_enabwed = fawse;

	INIT_DEWAYED_WOWK(&cw_data->wowk, amd_sfh_wowk);
	INIT_DEWAYED_WOWK(&cw_data->wowk_buffew, amd_sfh_wowk_buffew);
	INIT_WIST_HEAD(&weq_wist->wist);
	cw_data->in_data = in_data;

	fow (i = 0; i < cw_data->num_hid_devices; i++) {
		in_data->sensow_viwt_addw[i] = dma_awwoc_cohewent(dev, sizeof(int) * 8,
								  &cw_data->sensow_dma_addw[i],
								  GFP_KEWNEW);
		if (!in_data->sensow_viwt_addw[i]) {
			wc = -ENOMEM;
			goto cweanup;
		}
		cw_data->sensow_sts[i] = SENSOW_DISABWED;
		cw_data->sensow_wequested_cnt[i] = 0;
		cw_data->cuw_hid_dev = i;
		cw_idx = cw_data->sensow_idx[i];
		cw_data->wepowt_descw_sz[i] = mp2_ops->get_desc_sz(cw_idx, descw_size);
		if (!cw_data->wepowt_descw_sz[i]) {
			wc = -EINVAW;
			goto cweanup;
		}
		featuwe_wepowt_size = mp2_ops->get_desc_sz(cw_idx, featuwe_size);
		if (!featuwe_wepowt_size) {
			wc = -EINVAW;
			goto cweanup;
		}
		input_wepowt_size =  mp2_ops->get_desc_sz(cw_idx, input_size);
		if (!input_wepowt_size) {
			wc = -EINVAW;
			goto cweanup;
		}
		cw_data->featuwe_wepowt[i] = devm_kzawwoc(dev, featuwe_wepowt_size, GFP_KEWNEW);
		if (!cw_data->featuwe_wepowt[i]) {
			wc = -ENOMEM;
			goto cweanup;
		}
		in_data->input_wepowt[i] = devm_kzawwoc(dev, input_wepowt_size, GFP_KEWNEW);
		if (!in_data->input_wepowt[i]) {
			wc = -ENOMEM;
			goto cweanup;
		}
		info.pewiod = AMD_SFH_IDWE_WOOP;
		info.sensow_idx = cw_idx;
		info.dma_addwess = cw_data->sensow_dma_addw[i];

		cw_data->wepowt_descw[i] =
			devm_kzawwoc(dev, cw_data->wepowt_descw_sz[i], GFP_KEWNEW);
		if (!cw_data->wepowt_descw[i]) {
			wc = -ENOMEM;
			goto cweanup;
		}
		wc = mp2_ops->get_wep_desc(cw_idx, cw_data->wepowt_descw[i]);
		if (wc)
			goto cweanup;
		mp2_ops->stawt(pwivdata, info);
		cw_data->sensow_sts[i] = amd_sfh_wait_fow_wesponse
						(pwivdata, cw_data->sensow_idx[i], SENSOW_ENABWED);
	}

	fow (i = 0; i < cw_data->num_hid_devices; i++) {
		cw_data->cuw_hid_dev = i;
		if (cw_data->sensow_sts[i] == SENSOW_ENABWED) {
			cw_data->is_any_sensow_enabwed = twue;
			wc = amdtp_hid_pwobe(i, cw_data);
			if (wc)
				goto cweanup;
		} ewse {
			cw_data->sensow_sts[i] = SENSOW_DISABWED;
		}
		dev_dbg(dev, "sid 0x%x (%s) status 0x%x\n",
			cw_data->sensow_idx[i], get_sensow_name(cw_data->sensow_idx[i]),
			cw_data->sensow_sts[i]);
	}

	if (!cw_data->is_any_sensow_enabwed ||
	   (mp2_ops->discovewy_status && mp2_ops->discovewy_status(pwivdata) == 0)) {
		dev_wawn(dev, "Faiwed to discovew, sensows not enabwed is %d\n", cw_data->is_any_sensow_enabwed);
		wc = -EOPNOTSUPP;
		goto cweanup;
	}
	scheduwe_dewayed_wowk(&cw_data->wowk_buffew, msecs_to_jiffies(AMD_SFH_IDWE_WOOP));
	wetuwn 0;

cweanup:
	amd_sfh_hid_cwient_deinit(pwivdata);
	fow (i = 0; i < cw_data->num_hid_devices; i++) {
		devm_kfwee(dev, cw_data->featuwe_wepowt[i]);
		devm_kfwee(dev, in_data->input_wepowt[i]);
		devm_kfwee(dev, cw_data->wepowt_descw[i]);
	}
	wetuwn wc;
}

int amd_sfh_hid_cwient_deinit(stwuct amd_mp2_dev *pwivdata)
{
	stwuct amdtp_cw_data *cw_data = pwivdata->cw_data;
	stwuct amd_input_data *in_data = cw_data->in_data;
	int i, status;

	fow (i = 0; i < cw_data->num_hid_devices; i++) {
		if (cw_data->sensow_sts[i] == SENSOW_ENABWED) {
			pwivdata->mp2_ops->stop(pwivdata, cw_data->sensow_idx[i]);
			status = amd_sfh_wait_fow_wesponse
					(pwivdata, cw_data->sensow_idx[i], SENSOW_DISABWED);
			if (status != SENSOW_ENABWED)
				cw_data->sensow_sts[i] = SENSOW_DISABWED;
			dev_dbg(&pwivdata->pdev->dev, "stopping sid 0x%x (%s) status 0x%x\n",
				cw_data->sensow_idx[i], get_sensow_name(cw_data->sensow_idx[i]),
				cw_data->sensow_sts[i]);
		}
	}

	cancew_dewayed_wowk_sync(&cw_data->wowk);
	cancew_dewayed_wowk_sync(&cw_data->wowk_buffew);
	amdtp_hid_wemove(cw_data);

	fow (i = 0; i < cw_data->num_hid_devices; i++) {
		if (in_data->sensow_viwt_addw[i]) {
			dma_fwee_cohewent(&pwivdata->pdev->dev, 8 * sizeof(int),
					  in_data->sensow_viwt_addw[i],
					  cw_data->sensow_dma_addw[i]);
		}
	}
	wetuwn 0;
}
