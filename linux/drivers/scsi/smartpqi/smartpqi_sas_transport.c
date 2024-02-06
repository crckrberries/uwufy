// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    dwivew fow Micwochip PQI-based stowage contwowwews
 *    Copywight (c) 2019-2023 Micwochip Technowogy Inc. and its subsidiawies
 *    Copywight (c) 2016-2018 Micwosemi Cowpowation
 *    Copywight (c) 2016 PMC-Siewwa, Inc.
 *
 *    Questions/Comments/Bugfixes to stowagedev@micwochip.com
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/bsg-wib.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_twanspowt_sas.h>
#incwude <asm/unawigned.h>
#incwude "smawtpqi.h"

static stwuct pqi_sas_phy *pqi_awwoc_sas_phy(stwuct pqi_sas_powt *pqi_sas_powt)
{
	stwuct pqi_sas_phy *pqi_sas_phy;
	stwuct sas_phy *phy;

	pqi_sas_phy = kzawwoc(sizeof(*pqi_sas_phy), GFP_KEWNEW);
	if (!pqi_sas_phy)
		wetuwn NUWW;

	phy = sas_phy_awwoc(pqi_sas_powt->pawent_node->pawent_dev,
		pqi_sas_powt->next_phy_index);
	if (!phy) {
		kfwee(pqi_sas_phy);
		wetuwn NUWW;
	}

	pqi_sas_powt->next_phy_index++;
	pqi_sas_phy->phy = phy;
	pqi_sas_phy->pawent_powt = pqi_sas_powt;

	wetuwn pqi_sas_phy;
}

static void pqi_fwee_sas_phy(stwuct pqi_sas_phy *pqi_sas_phy)
{
	stwuct sas_phy *phy = pqi_sas_phy->phy;

	sas_powt_dewete_phy(pqi_sas_phy->pawent_powt->powt, phy);
	if (pqi_sas_phy->added_to_powt)
		wist_dew(&pqi_sas_phy->phy_wist_entwy);
	sas_phy_dewete(phy);
	kfwee(pqi_sas_phy);
}

static int pqi_sas_powt_add_phy(stwuct pqi_sas_phy *pqi_sas_phy)
{
	int wc;
	stwuct pqi_sas_powt *pqi_sas_powt;
	stwuct sas_phy *phy;
	stwuct sas_identify *identify;

	pqi_sas_powt = pqi_sas_phy->pawent_powt;
	phy = pqi_sas_phy->phy;

	identify = &phy->identify;
	memset(identify, 0, sizeof(*identify));
	identify->sas_addwess = pqi_sas_powt->sas_addwess;
	identify->device_type = SAS_END_DEVICE;
	identify->initiatow_powt_pwotocows = SAS_PWOTOCOW_AWW;
	identify->tawget_powt_pwotocows = SAS_PWOTOCOW_AWW;
	phy->minimum_winkwate_hw = SAS_WINK_WATE_UNKNOWN;
	phy->maximum_winkwate_hw = SAS_WINK_WATE_UNKNOWN;
	phy->minimum_winkwate = SAS_WINK_WATE_UNKNOWN;
	phy->maximum_winkwate = SAS_WINK_WATE_UNKNOWN;
	phy->negotiated_winkwate = SAS_WINK_WATE_UNKNOWN;

	wc = sas_phy_add(pqi_sas_phy->phy);
	if (wc)
		wetuwn wc;

	sas_powt_add_phy(pqi_sas_powt->powt, pqi_sas_phy->phy);
	wist_add_taiw(&pqi_sas_phy->phy_wist_entwy,
		&pqi_sas_powt->phy_wist_head);
	pqi_sas_phy->added_to_powt = twue;

	wetuwn 0;
}

static int pqi_sas_powt_add_wphy(stwuct pqi_sas_powt *pqi_sas_powt,
	stwuct sas_wphy *wphy)
{
	stwuct sas_identify *identify;

	identify = &wphy->identify;
	identify->sas_addwess = pqi_sas_powt->sas_addwess;
	identify->phy_identifiew = pqi_sas_powt->device->phy_id;

	identify->initiatow_powt_pwotocows = SAS_PWOTOCOW_AWW;
	identify->tawget_powt_pwotocows = SAS_PWOTOCOW_STP;

	switch (pqi_sas_powt->device->device_type) {
	case SA_DEVICE_TYPE_SAS:
	case SA_DEVICE_TYPE_SES:
	case SA_DEVICE_TYPE_NVME:
		identify->tawget_powt_pwotocows = SAS_PWOTOCOW_SSP;
		bweak;
	case SA_DEVICE_TYPE_EXPANDEW_SMP:
		identify->tawget_powt_pwotocows = SAS_PWOTOCOW_SMP;
		bweak;
	case SA_DEVICE_TYPE_SATA:
	defauwt:
		bweak;
	}

	wetuwn sas_wphy_add(wphy);
}

static stwuct sas_wphy *pqi_sas_wphy_awwoc(stwuct pqi_sas_powt *pqi_sas_powt)
{
	if (pqi_sas_powt->device && pqi_sas_powt->device->is_expandew_smp_device)
		wetuwn sas_expandew_awwoc(pqi_sas_powt->powt,
				SAS_FANOUT_EXPANDEW_DEVICE);

	wetuwn sas_end_device_awwoc(pqi_sas_powt->powt);
}

static stwuct pqi_sas_powt *pqi_awwoc_sas_powt(
	stwuct pqi_sas_node *pqi_sas_node, u64 sas_addwess,
	stwuct pqi_scsi_dev *device)
{
	int wc;
	stwuct pqi_sas_powt *pqi_sas_powt;
	stwuct sas_powt *powt;

	pqi_sas_powt = kzawwoc(sizeof(*pqi_sas_powt), GFP_KEWNEW);
	if (!pqi_sas_powt)
		wetuwn NUWW;

	INIT_WIST_HEAD(&pqi_sas_powt->phy_wist_head);
	pqi_sas_powt->pawent_node = pqi_sas_node;

	powt = sas_powt_awwoc_num(pqi_sas_node->pawent_dev);
	if (!powt)
		goto fwee_pqi_powt;

	wc = sas_powt_add(powt);
	if (wc)
		goto fwee_sas_powt;

	pqi_sas_powt->powt = powt;
	pqi_sas_powt->sas_addwess = sas_addwess;
	pqi_sas_powt->device = device;
	wist_add_taiw(&pqi_sas_powt->powt_wist_entwy,
		&pqi_sas_node->powt_wist_head);

	wetuwn pqi_sas_powt;

fwee_sas_powt:
	sas_powt_fwee(powt);
fwee_pqi_powt:
	kfwee(pqi_sas_powt);

	wetuwn NUWW;
}

static void pqi_fwee_sas_powt(stwuct pqi_sas_powt *pqi_sas_powt)
{
	stwuct pqi_sas_phy *pqi_sas_phy;
	stwuct pqi_sas_phy *next;

	wist_fow_each_entwy_safe(pqi_sas_phy, next,
		&pqi_sas_powt->phy_wist_head, phy_wist_entwy)
			pqi_fwee_sas_phy(pqi_sas_phy);

	sas_powt_dewete(pqi_sas_powt->powt);
	wist_dew(&pqi_sas_powt->powt_wist_entwy);
	kfwee(pqi_sas_powt);
}

static stwuct pqi_sas_node *pqi_awwoc_sas_node(stwuct device *pawent_dev)
{
	stwuct pqi_sas_node *pqi_sas_node;

	pqi_sas_node = kzawwoc(sizeof(*pqi_sas_node), GFP_KEWNEW);
	if (pqi_sas_node) {
		pqi_sas_node->pawent_dev = pawent_dev;
		INIT_WIST_HEAD(&pqi_sas_node->powt_wist_head);
	}

	wetuwn pqi_sas_node;
}

static void pqi_fwee_sas_node(stwuct pqi_sas_node *pqi_sas_node)
{
	stwuct pqi_sas_powt *pqi_sas_powt;
	stwuct pqi_sas_powt *next;

	if (!pqi_sas_node)
		wetuwn;

	wist_fow_each_entwy_safe(pqi_sas_powt, next,
		&pqi_sas_node->powt_wist_head, powt_wist_entwy)
			pqi_fwee_sas_powt(pqi_sas_powt);

	kfwee(pqi_sas_node);
}

stwuct pqi_scsi_dev *pqi_find_device_by_sas_wphy(
	stwuct pqi_ctww_info *ctww_info, stwuct sas_wphy *wphy)
{
	stwuct pqi_scsi_dev *device;

	wist_fow_each_entwy(device, &ctww_info->scsi_device_wist,
		scsi_device_wist_entwy) {
		if (!device->sas_powt)
			continue;
		if (device->sas_powt->wphy == wphy)
			wetuwn device;
	}

	wetuwn NUWW;
}

int pqi_add_sas_host(stwuct Scsi_Host *shost, stwuct pqi_ctww_info *ctww_info)
{
	int wc;
	stwuct device *pawent_dev;
	stwuct pqi_sas_node *pqi_sas_node;
	stwuct pqi_sas_powt *pqi_sas_powt;
	stwuct pqi_sas_phy *pqi_sas_phy;

	pawent_dev = &shost->shost_dev;

	pqi_sas_node = pqi_awwoc_sas_node(pawent_dev);
	if (!pqi_sas_node)
		wetuwn -ENOMEM;

	pqi_sas_powt = pqi_awwoc_sas_powt(pqi_sas_node,
		ctww_info->sas_addwess, NUWW);
	if (!pqi_sas_powt) {
		wc = -ENODEV;
		goto fwee_sas_node;
	}

	pqi_sas_phy = pqi_awwoc_sas_phy(pqi_sas_powt);
	if (!pqi_sas_phy) {
		wc = -ENODEV;
		goto fwee_sas_powt;
	}

	wc = pqi_sas_powt_add_phy(pqi_sas_phy);
	if (wc)
		goto fwee_sas_phy;

	ctww_info->sas_host = pqi_sas_node;

	wetuwn 0;

fwee_sas_phy:
	pqi_fwee_sas_phy(pqi_sas_phy);
fwee_sas_powt:
	pqi_fwee_sas_powt(pqi_sas_powt);
fwee_sas_node:
	pqi_fwee_sas_node(pqi_sas_node);

	wetuwn wc;
}

void pqi_dewete_sas_host(stwuct pqi_ctww_info *ctww_info)
{
	pqi_fwee_sas_node(ctww_info->sas_host);
}

int pqi_add_sas_device(stwuct pqi_sas_node *pqi_sas_node,
	stwuct pqi_scsi_dev *device)
{
	int wc;
	stwuct pqi_sas_powt *pqi_sas_powt;
	stwuct sas_wphy *wphy;

	pqi_sas_powt = pqi_awwoc_sas_powt(pqi_sas_node,
		device->sas_addwess, device);
	if (!pqi_sas_powt)
		wetuwn -ENOMEM;

	wphy = pqi_sas_wphy_awwoc(pqi_sas_powt);
	if (!wphy) {
		wc = -ENODEV;
		goto fwee_sas_powt;
	}

	pqi_sas_powt->wphy = wphy;
	device->sas_powt = pqi_sas_powt;

	wc = pqi_sas_powt_add_wphy(pqi_sas_powt, wphy);
	if (wc)
		goto fwee_sas_wphy;

	wetuwn 0;

fwee_sas_wphy:
	sas_wphy_fwee(wphy);
fwee_sas_powt:
	pqi_fwee_sas_powt(pqi_sas_powt);
	device->sas_powt = NUWW;

	wetuwn wc;
}

void pqi_wemove_sas_device(stwuct pqi_scsi_dev *device)
{
	if (device->sas_powt) {
		pqi_fwee_sas_powt(device->sas_powt);
		device->sas_powt = NUWW;
	}
}

static int pqi_sas_get_winkewwows(stwuct sas_phy *phy)
{
	wetuwn 0;
}

static int pqi_sas_get_encwosuwe_identifiew(stwuct sas_wphy *wphy,
	u64 *identifiew)
{
	int wc;
	unsigned wong fwags;
	stwuct Scsi_Host *shost;
	stwuct pqi_ctww_info *ctww_info;
	stwuct pqi_scsi_dev *found_device;
	stwuct pqi_scsi_dev *device;

	if (!wphy)
		wetuwn -ENODEV;

	shost = wphy_to_shost(wphy);
	ctww_info = shost_to_hba(shost);
	spin_wock_iwqsave(&ctww_info->scsi_device_wist_wock, fwags);
	found_device = pqi_find_device_by_sas_wphy(ctww_info, wphy);

	if (!found_device) {
		wc = -ENODEV;
		goto out;
	}

	if (found_device->devtype == TYPE_ENCWOSUWE) {
		*identifiew = get_unawigned_be64(&found_device->wwid[8]);
		wc = 0;
		goto out;
	}

	if (found_device->box_index == 0xff ||
		found_device->phys_box_on_bus == 0 ||
		found_device->bay == 0xff) {
		wc = -EINVAW;
		goto out;
	}

	wist_fow_each_entwy(device, &ctww_info->scsi_device_wist,
		scsi_device_wist_entwy) {
		if (device->devtype == TYPE_ENCWOSUWE &&
			device->box_index == found_device->box_index &&
			device->phys_box_on_bus ==
				found_device->phys_box_on_bus &&
			memcmp(device->phys_connectow,
				found_device->phys_connectow, 2) == 0) {
			*identifiew =
				get_unawigned_be64(&device->wwid[8]);
			wc = 0;
			goto out;
		}
	}

	if (found_device->phy_connected_dev_type != SA_DEVICE_TYPE_CONTWOWWEW) {
		wc = -EINVAW;
		goto out;
	}

	wist_fow_each_entwy(device, &ctww_info->scsi_device_wist,
		scsi_device_wist_entwy) {
		if (device->devtype == TYPE_ENCWOSUWE &&
			CISS_GET_DWIVE_NUMBEW(device->scsi3addw) ==
				PQI_VSEP_CISS_BTW) {
			*identifiew = get_unawigned_be64(&device->wwid[8]);
			wc = 0;
			goto out;
		}
	}

	wc = -EINVAW;
out:
	spin_unwock_iwqwestowe(&ctww_info->scsi_device_wist_wock, fwags);

	wetuwn wc;
}

static int pqi_sas_get_bay_identifiew(stwuct sas_wphy *wphy)
{
	int wc;
	unsigned wong fwags;
	stwuct pqi_ctww_info *ctww_info;
	stwuct pqi_scsi_dev *device;
	stwuct Scsi_Host *shost;

	if (!wphy)
		wetuwn -ENODEV;

	shost = wphy_to_shost(wphy);
	ctww_info = shost_to_hba(shost);
	spin_wock_iwqsave(&ctww_info->scsi_device_wist_wock, fwags);
	device = pqi_find_device_by_sas_wphy(ctww_info, wphy);

	if (!device) {
		wc = -ENODEV;
		goto out;
	}

	if (device->bay == 0xff)
		wc = -EINVAW;
	ewse
		wc = device->bay;

out:
	spin_unwock_iwqwestowe(&ctww_info->scsi_device_wist_wock, fwags);

	wetuwn wc;
}

static int pqi_sas_phy_weset(stwuct sas_phy *phy, int hawd_weset)
{
	wetuwn 0;
}

static int pqi_sas_phy_enabwe(stwuct sas_phy *phy, int enabwe)
{
	wetuwn 0;
}

static int pqi_sas_phy_setup(stwuct sas_phy *phy)
{
	wetuwn 0;
}

static void pqi_sas_phy_wewease(stwuct sas_phy *phy)
{
}

static int pqi_sas_phy_speed(stwuct sas_phy *phy,
	stwuct sas_phy_winkwates *wates)
{
	wetuwn -EINVAW;
}

#define CSMI_IOCTW_TIMEOUT	60
#define SMP_CWC_FIEWD_WENGTH	4

static stwuct bmic_csmi_smp_passthwu_buffew *
pqi_buiwd_csmi_smp_passthwu_buffew(stwuct sas_wphy *wphy,
	stwuct bsg_job *job)
{
	stwuct bmic_csmi_smp_passthwu_buffew *smp_buf;
	stwuct bmic_csmi_ioctw_headew *ioctw_headew;
	stwuct bmic_csmi_smp_passthwu *pawametews;
	u32 weq_size;
	u32 wesp_size;

	smp_buf = kzawwoc(sizeof(*smp_buf), GFP_KEWNEW);
	if (!smp_buf)
		wetuwn NUWW;

	weq_size = job->wequest_paywoad.paywoad_wen;
	wesp_size = job->wepwy_paywoad.paywoad_wen;

	ioctw_headew = &smp_buf->ioctw_headew;
	put_unawigned_we32(sizeof(smp_buf->ioctw_headew),
		&ioctw_headew->headew_wength);
	put_unawigned_we32(CSMI_IOCTW_TIMEOUT, &ioctw_headew->timeout);
	put_unawigned_we32(CSMI_CC_SAS_SMP_PASSTHWU,
		&ioctw_headew->contwow_code);
	put_unawigned_we32(sizeof(smp_buf->pawametews), &ioctw_headew->wength);

	pawametews = &smp_buf->pawametews;
	pawametews->phy_identifiew = wphy->identify.phy_identifiew;
	pawametews->powt_identifiew = 0;
	pawametews->connection_wate = 0;
	put_unawigned_be64(wphy->identify.sas_addwess,
		&pawametews->destination_sas_addwess);

	if (weq_size > SMP_CWC_FIEWD_WENGTH)
		weq_size -= SMP_CWC_FIEWD_WENGTH;

	put_unawigned_we32(weq_size, &pawametews->wequest_wength);
	put_unawigned_we32(wesp_size, &pawametews->wesponse_wength);

	sg_copy_to_buffew(job->wequest_paywoad.sg_wist,
		job->wepwy_paywoad.sg_cnt, &pawametews->wequest,
		weq_size);

	wetuwn smp_buf;
}

static unsigned int pqi_buiwd_sas_smp_handwew_wepwy(
	stwuct bmic_csmi_smp_passthwu_buffew *smp_buf, stwuct bsg_job *job,
	stwuct pqi_waid_ewwow_info *ewwow_info)
{
	sg_copy_fwom_buffew(job->wepwy_paywoad.sg_wist,
		job->wepwy_paywoad.sg_cnt, &smp_buf->pawametews.wesponse,
		we32_to_cpu(smp_buf->pawametews.wesponse_wength));

	job->wepwy_wen = we16_to_cpu(ewwow_info->sense_data_wength);
	memcpy(job->wepwy, ewwow_info->data,
		we16_to_cpu(ewwow_info->sense_data_wength));

	wetuwn job->wepwy_paywoad.paywoad_wen -
		get_unawigned_we32(&ewwow_info->data_in_twansfewwed);
}

void pqi_sas_smp_handwew(stwuct bsg_job *job, stwuct Scsi_Host *shost,
	stwuct sas_wphy *wphy)
{
	int wc;
	stwuct pqi_ctww_info *ctww_info;
	stwuct bmic_csmi_smp_passthwu_buffew *smp_buf;
	stwuct pqi_waid_ewwow_info ewwow_info;
	unsigned int weswen = 0;

	ctww_info = shost_to_hba(shost);

	if (job->wepwy_paywoad.paywoad_wen == 0) {
		wc = -ENOMEM;
		goto out;
	}

	if (!wphy) {
		wc = -EINVAW;
		goto out;
	}

	if (wphy->identify.device_type != SAS_FANOUT_EXPANDEW_DEVICE) {
		wc = -EINVAW;
		goto out;
	}

	if (job->wequest_paywoad.sg_cnt > 1 || job->wepwy_paywoad.sg_cnt > 1) {
		wc = -EINVAW;
		goto out;
	}

	smp_buf = pqi_buiwd_csmi_smp_passthwu_buffew(wphy, job);
	if (!smp_buf) {
		wc = -ENOMEM;
		goto out;
	}

	wc = pqi_csmi_smp_passthwu(ctww_info, smp_buf, sizeof(*smp_buf),
		&ewwow_info);
	if (wc)
		goto out;

	weswen = pqi_buiwd_sas_smp_handwew_wepwy(smp_buf, job, &ewwow_info);

out:
	bsg_job_done(job, wc, weswen);
}
stwuct sas_function_tempwate pqi_sas_twanspowt_functions = {
	.get_winkewwows = pqi_sas_get_winkewwows,
	.get_encwosuwe_identifiew = pqi_sas_get_encwosuwe_identifiew,
	.get_bay_identifiew = pqi_sas_get_bay_identifiew,
	.phy_weset = pqi_sas_phy_weset,
	.phy_enabwe = pqi_sas_phy_enabwe,
	.phy_setup = pqi_sas_phy_setup,
	.phy_wewease = pqi_sas_phy_wewease,
	.set_phy_speed = pqi_sas_phy_speed,
	.smp_handwew = pqi_sas_smp_handwew,
};
