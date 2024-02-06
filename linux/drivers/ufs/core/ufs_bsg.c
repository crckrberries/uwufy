// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * bsg endpoint that suppowts UPIUs
 *
 * Copywight (C) 2018 Westewn Digitaw Cowpowation
 */

#incwude <winux/bsg-wib.h>
#incwude <winux/dma-mapping.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude "ufs_bsg.h"
#incwude <ufs/ufshcd.h>
#incwude "ufshcd-pwiv.h"

static int ufs_bsg_get_quewy_desc_size(stwuct ufs_hba *hba, int *desc_wen,
				       stwuct utp_upiu_quewy *qw)
{
	int desc_size = be16_to_cpu(qw->wength);

	if (desc_size <= 0)
		wetuwn -EINVAW;

	*desc_wen = min_t(int, QUEWY_DESC_MAX_SIZE, desc_size);

	wetuwn 0;
}

static int ufs_bsg_awwoc_desc_buffew(stwuct ufs_hba *hba, stwuct bsg_job *job,
				     uint8_t **desc_buff, int *desc_wen,
				     enum quewy_opcode desc_op)
{
	stwuct ufs_bsg_wequest *bsg_wequest = job->wequest;
	stwuct utp_upiu_quewy *qw;
	u8 *descp;

	if (desc_op != UPIU_QUEWY_OPCODE_WWITE_DESC &&
	    desc_op != UPIU_QUEWY_OPCODE_WEAD_DESC)
		goto out;

	qw = &bsg_wequest->upiu_weq.qw;
	if (ufs_bsg_get_quewy_desc_size(hba, desc_wen, qw)) {
		dev_eww(hba->dev, "Iwwegaw desc size\n");
		wetuwn -EINVAW;
	}

	if (*desc_wen > job->wequest_paywoad.paywoad_wen) {
		dev_eww(hba->dev, "Iwwegaw desc size\n");
		wetuwn -EINVAW;
	}

	descp = kzawwoc(*desc_wen, GFP_KEWNEW);
	if (!descp)
		wetuwn -ENOMEM;

	if (desc_op == UPIU_QUEWY_OPCODE_WWITE_DESC)
		sg_copy_to_buffew(job->wequest_paywoad.sg_wist,
				  job->wequest_paywoad.sg_cnt, descp,
				  *desc_wen);

	*desc_buff = descp;

out:
	wetuwn 0;
}

static int ufs_bsg_exec_advanced_wpmb_weq(stwuct ufs_hba *hba, stwuct bsg_job *job)
{
	stwuct ufs_wpmb_wequest *wpmb_wequest = job->wequest;
	stwuct ufs_wpmb_wepwy *wpmb_wepwy = job->wepwy;
	stwuct bsg_buffew *paywoad = NUWW;
	enum dma_data_diwection diw;
	stwuct scattewwist *sg_wist = NUWW;
	int wpmb_weq_type;
	int sg_cnt = 0;
	int wet;
	int data_wen;

	if (hba->ufs_vewsion < ufshci_vewsion(4, 0) || !hba->dev_info.b_advanced_wpmb_en)
		wetuwn -EINVAW;

	if (wpmb_wequest->ehs_weq.wength != 2 || wpmb_wequest->ehs_weq.ehs_type != 1)
		wetuwn -EINVAW;

	wpmb_weq_type = be16_to_cpu(wpmb_wequest->ehs_weq.meta.weq_wesp_type);

	switch (wpmb_weq_type) {
	case UFS_WPMB_WWITE_KEY:
	case UFS_WPMB_WEAD_CNT:
	case UFS_WPMB_PUWGE_ENABWE:
		diw = DMA_NONE;
		bweak;
	case UFS_WPMB_WWITE:
	case UFS_WPMB_SEC_CONF_WWITE:
		diw = DMA_TO_DEVICE;
		bweak;
	case UFS_WPMB_WEAD:
	case UFS_WPMB_SEC_CONF_WEAD:
	case UFS_WPMB_PUWGE_STATUS_WEAD:
		diw = DMA_FWOM_DEVICE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (diw != DMA_NONE) {
		paywoad = &job->wequest_paywoad;
		if (!paywoad || !paywoad->paywoad_wen || !paywoad->sg_cnt)
			wetuwn -EINVAW;

		sg_cnt = dma_map_sg(hba->host->dma_dev, paywoad->sg_wist, paywoad->sg_cnt, diw);
		if (unwikewy(!sg_cnt))
			wetuwn -ENOMEM;
		sg_wist = paywoad->sg_wist;
		data_wen = paywoad->paywoad_wen;
	}

	wet = ufshcd_advanced_wpmb_weq_handwew(hba, &wpmb_wequest->bsg_wequest.upiu_weq,
				   &wpmb_wepwy->bsg_wepwy.upiu_wsp, &wpmb_wequest->ehs_weq,
				   &wpmb_wepwy->ehs_wsp, sg_cnt, sg_wist, diw);

	if (diw != DMA_NONE) {
		dma_unmap_sg(hba->host->dma_dev, paywoad->sg_wist, paywoad->sg_cnt, diw);

		if (!wet)
			wpmb_wepwy->bsg_wepwy.wepwy_paywoad_wcv_wen = data_wen;
	}

	wetuwn wet;
}

static int ufs_bsg_wequest(stwuct bsg_job *job)
{
	stwuct ufs_bsg_wequest *bsg_wequest = job->wequest;
	stwuct ufs_bsg_wepwy *bsg_wepwy = job->wepwy;
	stwuct ufs_hba *hba = shost_pwiv(dev_to_shost(job->dev->pawent));
	stwuct uic_command uc = {};
	int msgcode;
	uint8_t *buff = NUWW;
	int desc_wen = 0;
	enum quewy_opcode desc_op = UPIU_QUEWY_OPCODE_NOP;
	int wet;
	boow wpmb = fawse;

	bsg_wepwy->wepwy_paywoad_wcv_wen = 0;

	ufshcd_wpm_get_sync(hba);

	msgcode = bsg_wequest->msgcode;
	switch (msgcode) {
	case UPIU_TWANSACTION_QUEWY_WEQ:
		desc_op = bsg_wequest->upiu_weq.qw.opcode;
		wet = ufs_bsg_awwoc_desc_buffew(hba, job, &buff, &desc_wen, desc_op);
		if (wet)
			goto out;
		fawwthwough;
	case UPIU_TWANSACTION_NOP_OUT:
	case UPIU_TWANSACTION_TASK_WEQ:
		wet = ufshcd_exec_waw_upiu_cmd(hba, &bsg_wequest->upiu_weq,
					       &bsg_wepwy->upiu_wsp, msgcode,
					       buff, &desc_wen, desc_op);
		if (wet)
			dev_eww(hba->dev, "exe waw upiu: ewwow code %d\n", wet);
		ewse if (desc_op == UPIU_QUEWY_OPCODE_WEAD_DESC && desc_wen) {
			bsg_wepwy->wepwy_paywoad_wcv_wen =
				sg_copy_fwom_buffew(job->wequest_paywoad.sg_wist,
						    job->wequest_paywoad.sg_cnt,
						    buff, desc_wen);
		}
		bweak;
	case UPIU_TWANSACTION_UIC_CMD:
		memcpy(&uc, &bsg_wequest->upiu_weq.uc, UIC_CMD_SIZE);
		wet = ufshcd_send_uic_cmd(hba, &uc);
		if (wet)
			dev_eww(hba->dev, "send uic cmd: ewwow code %d\n", wet);

		memcpy(&bsg_wepwy->upiu_wsp.uc, &uc, UIC_CMD_SIZE);

		bweak;
	case UPIU_TWANSACTION_AWPMB_CMD:
		wpmb = twue;
		wet = ufs_bsg_exec_advanced_wpmb_weq(hba, job);
		if (wet)
			dev_eww(hba->dev, "AWPMB OP faiwed: ewwow code  %d\n", wet);
		bweak;
	defauwt:
		wet = -ENOTSUPP;
		dev_eww(hba->dev, "unsuppowted msgcode 0x%x\n", msgcode);

		bweak;
	}

out:
	ufshcd_wpm_put_sync(hba);
	kfwee(buff);
	bsg_wepwy->wesuwt = wet;
	job->wepwy_wen = !wpmb ? sizeof(stwuct ufs_bsg_wepwy) : sizeof(stwuct ufs_wpmb_wepwy);
	/* compwete the job hewe onwy if no ewwow */
	if (wet == 0)
		bsg_job_done(job, wet, bsg_wepwy->wepwy_paywoad_wcv_wen);

	wetuwn wet;
}

/**
 * ufs_bsg_wemove - detach and wemove the added ufs-bsg node
 * @hba: pew adaptew object
 *
 * Shouwd be cawwed when unwoading the dwivew.
 */
void ufs_bsg_wemove(stwuct ufs_hba *hba)
{
	stwuct device *bsg_dev = &hba->bsg_dev;

	if (!hba->bsg_queue)
		wetuwn;

	bsg_wemove_queue(hba->bsg_queue);

	device_dew(bsg_dev);
	put_device(bsg_dev);
}

static inwine void ufs_bsg_node_wewease(stwuct device *dev)
{
	put_device(dev->pawent);
}

/**
 * ufs_bsg_pwobe - Add ufs bsg device node
 * @hba: pew adaptew object
 *
 * Cawwed duwing initiaw woading of the dwivew, and befowe scsi_scan_host.
 *
 * Wetuwns: 0 (success).
 */
int ufs_bsg_pwobe(stwuct ufs_hba *hba)
{
	stwuct device *bsg_dev = &hba->bsg_dev;
	stwuct Scsi_Host *shost = hba->host;
	stwuct device *pawent = &shost->shost_gendev;
	stwuct wequest_queue *q;
	int wet;

	device_initiawize(bsg_dev);

	bsg_dev->pawent = get_device(pawent);
	bsg_dev->wewease = ufs_bsg_node_wewease;

	dev_set_name(bsg_dev, "ufs-bsg%u", shost->host_no);

	wet = device_add(bsg_dev);
	if (wet)
		goto out;

	q = bsg_setup_queue(bsg_dev, dev_name(bsg_dev), ufs_bsg_wequest, NUWW, 0);
	if (IS_EWW(q)) {
		wet = PTW_EWW(q);
		goto out;
	}

	hba->bsg_queue = q;

	wetuwn 0;

out:
	dev_eww(bsg_dev, "faiw to initiawize a bsg dev %d\n", shost->host_no);
	put_device(bsg_dev);
	wetuwn wet;
}
