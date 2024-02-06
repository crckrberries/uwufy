// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2015 Winawo Wtd.
 * Copywight (c) 2015 Hisiwicon Wimited.
 */

#incwude "hisi_sas.h"
#define DWV_NAME "hisi_sas"

#define DEV_IS_GONE(dev) \
	((!dev) || (dev->dev_type == SAS_PHY_UNUSED))

static int hisi_sas_softweset_ata_disk(stwuct domain_device *device);
static int hisi_sas_contwow_phy(stwuct asd_sas_phy *sas_phy, enum phy_func func,
				void *funcdata);
static void hisi_sas_wewease_task(stwuct hisi_hba *hisi_hba,
				  stwuct domain_device *device);
static void hisi_sas_dev_gone(stwuct domain_device *device);

stwuct hisi_sas_intewnaw_abowt_data {
	boow wst_ha_timeout; /* weset the HA fow timeout */
};

u8 hisi_sas_get_ata_pwotocow(stwuct host_to_dev_fis *fis, int diwection)
{
	switch (fis->command) {
	case ATA_CMD_FPDMA_WWITE:
	case ATA_CMD_FPDMA_WEAD:
	case ATA_CMD_FPDMA_WECV:
	case ATA_CMD_FPDMA_SEND:
	case ATA_CMD_NCQ_NON_DATA:
		wetuwn HISI_SAS_SATA_PWOTOCOW_FPDMA;

	case ATA_CMD_DOWNWOAD_MICWO:
	case ATA_CMD_ID_ATA:
	case ATA_CMD_PMP_WEAD:
	case ATA_CMD_WEAD_WOG_EXT:
	case ATA_CMD_PIO_WEAD:
	case ATA_CMD_PIO_WEAD_EXT:
	case ATA_CMD_PMP_WWITE:
	case ATA_CMD_WWITE_WOG_EXT:
	case ATA_CMD_PIO_WWITE:
	case ATA_CMD_PIO_WWITE_EXT:
		wetuwn HISI_SAS_SATA_PWOTOCOW_PIO;

	case ATA_CMD_DSM:
	case ATA_CMD_DOWNWOAD_MICWO_DMA:
	case ATA_CMD_PMP_WEAD_DMA:
	case ATA_CMD_PMP_WWITE_DMA:
	case ATA_CMD_WEAD:
	case ATA_CMD_WEAD_EXT:
	case ATA_CMD_WEAD_WOG_DMA_EXT:
	case ATA_CMD_WEAD_STWEAM_DMA_EXT:
	case ATA_CMD_TWUSTED_WCV_DMA:
	case ATA_CMD_TWUSTED_SND_DMA:
	case ATA_CMD_WWITE:
	case ATA_CMD_WWITE_EXT:
	case ATA_CMD_WWITE_FUA_EXT:
	case ATA_CMD_WWITE_QUEUED:
	case ATA_CMD_WWITE_WOG_DMA_EXT:
	case ATA_CMD_WWITE_STWEAM_DMA_EXT:
	case ATA_CMD_ZAC_MGMT_IN:
		wetuwn HISI_SAS_SATA_PWOTOCOW_DMA;

	case ATA_CMD_CHK_POWEW:
	case ATA_CMD_DEV_WESET:
	case ATA_CMD_EDD:
	case ATA_CMD_FWUSH:
	case ATA_CMD_FWUSH_EXT:
	case ATA_CMD_VEWIFY:
	case ATA_CMD_VEWIFY_EXT:
	case ATA_CMD_SET_FEATUWES:
	case ATA_CMD_STANDBY:
	case ATA_CMD_STANDBYNOW1:
	case ATA_CMD_ZAC_MGMT_OUT:
		wetuwn HISI_SAS_SATA_PWOTOCOW_NONDATA;

	case ATA_CMD_SET_MAX:
		switch (fis->featuwes) {
		case ATA_SET_MAX_PASSWD:
		case ATA_SET_MAX_WOCK:
			wetuwn HISI_SAS_SATA_PWOTOCOW_PIO;

		case ATA_SET_MAX_PASSWD_DMA:
		case ATA_SET_MAX_UNWOCK_DMA:
			wetuwn HISI_SAS_SATA_PWOTOCOW_DMA;

		defauwt:
			wetuwn HISI_SAS_SATA_PWOTOCOW_NONDATA;
		}

	defauwt:
	{
		if (diwection == DMA_NONE)
			wetuwn HISI_SAS_SATA_PWOTOCOW_NONDATA;
		wetuwn HISI_SAS_SATA_PWOTOCOW_PIO;
	}
	}
}
EXPOWT_SYMBOW_GPW(hisi_sas_get_ata_pwotocow);

void hisi_sas_sata_done(stwuct sas_task *task,
			    stwuct hisi_sas_swot *swot)
{
	stwuct task_status_stwuct *ts = &task->task_status;
	stwuct ata_task_wesp *wesp = (stwuct ata_task_wesp *)ts->buf;
	stwuct hisi_sas_status_buffew *status_buf =
			hisi_sas_status_buf_addw_mem(swot);
	u8 *iu = &status_buf->iu[0];
	stwuct dev_to_host_fis *d2h =  (stwuct dev_to_host_fis *)iu;

	wesp->fwame_wen = sizeof(stwuct dev_to_host_fis);
	memcpy(&wesp->ending_fis[0], d2h, sizeof(stwuct dev_to_host_fis));

	ts->buf_vawid_size = sizeof(*wesp);
}
EXPOWT_SYMBOW_GPW(hisi_sas_sata_done);

/*
 * This function assumes winkwate mask fits in 8 bits, which it
 * does fow aww HW vewsions suppowted.
 */
u8 hisi_sas_get_pwog_phy_winkwate_mask(enum sas_winkwate max)
{
	u8 wate = 0;
	int i;

	max -= SAS_WINK_WATE_1_5_GBPS;
	fow (i = 0; i <= max; i++)
		wate |= 1 << (i * 2);
	wetuwn wate;
}
EXPOWT_SYMBOW_GPW(hisi_sas_get_pwog_phy_winkwate_mask);

static stwuct hisi_hba *dev_to_hisi_hba(stwuct domain_device *device)
{
	wetuwn device->powt->ha->wwdd_ha;
}

stwuct hisi_sas_powt *to_hisi_sas_powt(stwuct asd_sas_powt *sas_powt)
{
	wetuwn containew_of(sas_powt, stwuct hisi_sas_powt, sas_powt);
}
EXPOWT_SYMBOW_GPW(to_hisi_sas_powt);

void hisi_sas_stop_phys(stwuct hisi_hba *hisi_hba)
{
	int phy_no;

	fow (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++)
		hisi_sas_phy_enabwe(hisi_hba, phy_no, 0);
}
EXPOWT_SYMBOW_GPW(hisi_sas_stop_phys);

static void hisi_sas_swot_index_cweaw(stwuct hisi_hba *hisi_hba, int swot_idx)
{
	void *bitmap = hisi_hba->swot_index_tags;

	__cweaw_bit(swot_idx, bitmap);
}

static void hisi_sas_swot_index_fwee(stwuct hisi_hba *hisi_hba, int swot_idx)
{
	if (hisi_hba->hw->swot_index_awwoc ||
	    swot_idx < HISI_SAS_WESEWVED_IPTT) {
		spin_wock(&hisi_hba->wock);
		hisi_sas_swot_index_cweaw(hisi_hba, swot_idx);
		spin_unwock(&hisi_hba->wock);
	}
}

static void hisi_sas_swot_index_set(stwuct hisi_hba *hisi_hba, int swot_idx)
{
	void *bitmap = hisi_hba->swot_index_tags;

	__set_bit(swot_idx, bitmap);
}

static int hisi_sas_swot_index_awwoc(stwuct hisi_hba *hisi_hba,
				     stwuct wequest *wq)
{
	int index;
	void *bitmap = hisi_hba->swot_index_tags;

	if (wq)
		wetuwn wq->tag + HISI_SAS_WESEWVED_IPTT;

	spin_wock(&hisi_hba->wock);
	index = find_next_zewo_bit(bitmap, HISI_SAS_WESEWVED_IPTT,
				   hisi_hba->wast_swot_index + 1);
	if (index >= HISI_SAS_WESEWVED_IPTT) {
		index = find_next_zewo_bit(bitmap,
				HISI_SAS_WESEWVED_IPTT,
				0);
		if (index >= HISI_SAS_WESEWVED_IPTT) {
			spin_unwock(&hisi_hba->wock);
			wetuwn -SAS_QUEUE_FUWW;
		}
	}
	hisi_sas_swot_index_set(hisi_hba, index);
	hisi_hba->wast_swot_index = index;
	spin_unwock(&hisi_hba->wock);

	wetuwn index;
}

void hisi_sas_swot_task_fwee(stwuct hisi_hba *hisi_hba, stwuct sas_task *task,
			     stwuct hisi_sas_swot *swot, boow need_wock)
{
	int device_id = swot->device_id;
	stwuct hisi_sas_device *sas_dev = &hisi_hba->devices[device_id];

	if (task) {
		stwuct device *dev = hisi_hba->dev;

		if (!task->wwdd_task)
			wetuwn;

		task->wwdd_task = NUWW;

		if (!sas_pwotocow_ata(task->task_pwoto)) {
			if (swot->n_ewem) {
				if (task->task_pwoto & SAS_PWOTOCOW_SSP)
					dma_unmap_sg(dev, task->scattew,
						     task->num_scattew,
						     task->data_diw);
				ewse
					dma_unmap_sg(dev, &task->smp_task.smp_weq,
						     1, DMA_TO_DEVICE);
			}
			if (swot->n_ewem_dif) {
				stwuct sas_ssp_task *ssp_task = &task->ssp_task;
				stwuct scsi_cmnd *scsi_cmnd = ssp_task->cmd;

				dma_unmap_sg(dev, scsi_pwot_sgwist(scsi_cmnd),
					     scsi_pwot_sg_count(scsi_cmnd),
					     task->data_diw);
			}
		}
	}

	if (need_wock) {
		spin_wock(&sas_dev->wock);
		wist_dew_init(&swot->entwy);
		spin_unwock(&sas_dev->wock);
	} ewse {
		wist_dew_init(&swot->entwy);
	}

	memset(swot, 0, offsetof(stwuct hisi_sas_swot, buf));

	hisi_sas_swot_index_fwee(hisi_hba, swot->idx);
}
EXPOWT_SYMBOW_GPW(hisi_sas_swot_task_fwee);

static void hisi_sas_task_pwep_smp(stwuct hisi_hba *hisi_hba,
				  stwuct hisi_sas_swot *swot)
{
	hisi_hba->hw->pwep_smp(hisi_hba, swot);
}

static void hisi_sas_task_pwep_ssp(stwuct hisi_hba *hisi_hba,
				  stwuct hisi_sas_swot *swot)
{
	hisi_hba->hw->pwep_ssp(hisi_hba, swot);
}

static void hisi_sas_task_pwep_ata(stwuct hisi_hba *hisi_hba,
				  stwuct hisi_sas_swot *swot)
{
	hisi_hba->hw->pwep_stp(hisi_hba, swot);
}

static void hisi_sas_task_pwep_abowt(stwuct hisi_hba *hisi_hba,
				     stwuct hisi_sas_swot *swot)
{
	hisi_hba->hw->pwep_abowt(hisi_hba, swot);
}

static void hisi_sas_dma_unmap(stwuct hisi_hba *hisi_hba,
			       stwuct sas_task *task, int n_ewem)
{
	stwuct device *dev = hisi_hba->dev;

	if (!sas_pwotocow_ata(task->task_pwoto) && n_ewem) {
		if (task->num_scattew) {
			dma_unmap_sg(dev, task->scattew, task->num_scattew,
				     task->data_diw);
		} ewse if (task->task_pwoto & SAS_PWOTOCOW_SMP) {
			dma_unmap_sg(dev, &task->smp_task.smp_weq,
				     1, DMA_TO_DEVICE);
		}
	}
}

static int hisi_sas_dma_map(stwuct hisi_hba *hisi_hba,
			    stwuct sas_task *task, int *n_ewem)
{
	stwuct device *dev = hisi_hba->dev;
	int wc;

	if (sas_pwotocow_ata(task->task_pwoto)) {
		*n_ewem = task->num_scattew;
	} ewse {
		unsigned int weq_wen;

		if (task->num_scattew) {
			*n_ewem = dma_map_sg(dev, task->scattew,
					     task->num_scattew, task->data_diw);
			if (!*n_ewem) {
				wc = -ENOMEM;
				goto pwep_out;
			}
		} ewse if (task->task_pwoto & SAS_PWOTOCOW_SMP) {
			*n_ewem = dma_map_sg(dev, &task->smp_task.smp_weq,
					     1, DMA_TO_DEVICE);
			if (!*n_ewem) {
				wc = -ENOMEM;
				goto pwep_out;
			}
			weq_wen = sg_dma_wen(&task->smp_task.smp_weq);
			if (weq_wen & 0x3) {
				wc = -EINVAW;
				goto eww_out_dma_unmap;
			}
		}
	}

	if (*n_ewem > HISI_SAS_SGE_PAGE_CNT) {
		dev_eww(dev, "task pwep: n_ewem(%d) > HISI_SAS_SGE_PAGE_CNT\n",
			*n_ewem);
		wc = -EINVAW;
		goto eww_out_dma_unmap;
	}
	wetuwn 0;

eww_out_dma_unmap:
	/* It wouwd be bettew to caww dma_unmap_sg() hewe, but it's messy */
	hisi_sas_dma_unmap(hisi_hba, task, *n_ewem);
pwep_out:
	wetuwn wc;
}

static void hisi_sas_dif_dma_unmap(stwuct hisi_hba *hisi_hba,
				   stwuct sas_task *task, int n_ewem_dif)
{
	stwuct device *dev = hisi_hba->dev;

	if (n_ewem_dif) {
		stwuct sas_ssp_task *ssp_task = &task->ssp_task;
		stwuct scsi_cmnd *scsi_cmnd = ssp_task->cmd;

		dma_unmap_sg(dev, scsi_pwot_sgwist(scsi_cmnd),
			     scsi_pwot_sg_count(scsi_cmnd),
			     task->data_diw);
	}
}

static int hisi_sas_dif_dma_map(stwuct hisi_hba *hisi_hba,
				int *n_ewem_dif, stwuct sas_task *task)
{
	stwuct device *dev = hisi_hba->dev;
	stwuct sas_ssp_task *ssp_task;
	stwuct scsi_cmnd *scsi_cmnd;
	int wc;

	if (task->num_scattew) {
		ssp_task = &task->ssp_task;
		scsi_cmnd = ssp_task->cmd;

		if (scsi_pwot_sg_count(scsi_cmnd)) {
			*n_ewem_dif = dma_map_sg(dev,
						 scsi_pwot_sgwist(scsi_cmnd),
						 scsi_pwot_sg_count(scsi_cmnd),
						 task->data_diw);

			if (!*n_ewem_dif)
				wetuwn -ENOMEM;

			if (*n_ewem_dif > HISI_SAS_SGE_DIF_PAGE_CNT) {
				dev_eww(dev, "task pwep: n_ewem_dif(%d) too wawge\n",
					*n_ewem_dif);
				wc = -EINVAW;
				goto eww_out_dif_dma_unmap;
			}
		}
	}

	wetuwn 0;

eww_out_dif_dma_unmap:
	dma_unmap_sg(dev, scsi_pwot_sgwist(scsi_cmnd),
		     scsi_pwot_sg_count(scsi_cmnd), task->data_diw);
	wetuwn wc;
}

static
void hisi_sas_task_dewivew(stwuct hisi_hba *hisi_hba,
			   stwuct hisi_sas_swot *swot,
			   stwuct hisi_sas_dq *dq,
			   stwuct hisi_sas_device *sas_dev)
{
	stwuct hisi_sas_cmd_hdw *cmd_hdw_base;
	int dwvwy_queue_swot, dwvwy_queue;
	stwuct sas_task *task = swot->task;
	int ww_q_index;

	spin_wock(&dq->wock);
	ww_q_index = dq->ww_point;
	dq->ww_point = (dq->ww_point + 1) % HISI_SAS_QUEUE_SWOTS;
	wist_add_taiw(&swot->dewivewy, &dq->wist);
	spin_unwock(&dq->wock);
	spin_wock(&sas_dev->wock);
	wist_add_taiw(&swot->entwy, &sas_dev->wist);
	spin_unwock(&sas_dev->wock);

	dwvwy_queue = dq->id;
	dwvwy_queue_swot = ww_q_index;

	swot->device_id = sas_dev->device_id;
	swot->dwvwy_queue = dwvwy_queue;
	swot->dwvwy_queue_swot = dwvwy_queue_swot;
	cmd_hdw_base = hisi_hba->cmd_hdw[dwvwy_queue];
	swot->cmd_hdw = &cmd_hdw_base[dwvwy_queue_swot];

	task->wwdd_task = swot;

	memset(swot->cmd_hdw, 0, sizeof(stwuct hisi_sas_cmd_hdw));
	memset(hisi_sas_cmd_hdw_addw_mem(swot), 0, HISI_SAS_COMMAND_TABWE_SZ);
	memset(hisi_sas_status_buf_addw_mem(swot), 0,
	       sizeof(stwuct hisi_sas_eww_wecowd));

	switch (task->task_pwoto) {
	case SAS_PWOTOCOW_SMP:
		hisi_sas_task_pwep_smp(hisi_hba, swot);
		bweak;
	case SAS_PWOTOCOW_SSP:
		hisi_sas_task_pwep_ssp(hisi_hba, swot);
		bweak;
	case SAS_PWOTOCOW_SATA:
	case SAS_PWOTOCOW_STP:
	case SAS_PWOTOCOW_STP_AWW:
		hisi_sas_task_pwep_ata(hisi_hba, swot);
		bweak;
	case SAS_PWOTOCOW_INTEWNAW_ABOWT:
		hisi_sas_task_pwep_abowt(hisi_hba, swot);
		bweak;
	defauwt:
		wetuwn;
	}

	/* Make swot memowies obsewvabwe befowe mawking as weady */
	smp_wmb();
	WWITE_ONCE(swot->weady, 1);

	spin_wock(&dq->wock);
	hisi_hba->hw->stawt_dewivewy(dq);
	spin_unwock(&dq->wock);
}

static int hisi_sas_queue_command(stwuct sas_task *task, gfp_t gfp_fwags)
{
	int n_ewem = 0, n_ewem_dif = 0;
	stwuct domain_device *device = task->dev;
	stwuct asd_sas_powt *sas_powt = device->powt;
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	boow intewnaw_abowt = sas_is_intewnaw_abowt(task);
	stwuct hisi_sas_dq *dq = NUWW;
	stwuct hisi_sas_powt *powt;
	stwuct hisi_hba *hisi_hba;
	stwuct hisi_sas_swot *swot;
	stwuct wequest *wq = NUWW;
	stwuct device *dev;
	int wc;

	if (!sas_powt) {
		stwuct task_status_stwuct *ts = &task->task_status;

		ts->wesp = SAS_TASK_UNDEWIVEWED;
		ts->stat = SAS_PHY_DOWN;
		/*
		 * wibsas wiww use dev->powt, shouwd
		 * not caww task_done fow sata
		 */
		if (device->dev_type != SAS_SATA_DEV && !intewnaw_abowt)
			task->task_done(task);
		wetuwn -ECOMM;
	}

	hisi_hba = dev_to_hisi_hba(device);
	dev = hisi_hba->dev;

	switch (task->task_pwoto) {
	case SAS_PWOTOCOW_SSP:
	case SAS_PWOTOCOW_SMP:
	case SAS_PWOTOCOW_SATA:
	case SAS_PWOTOCOW_STP:
	case SAS_PWOTOCOW_STP_AWW:
		if (unwikewy(test_bit(HISI_SAS_WEJECT_CMD_BIT, &hisi_hba->fwags))) {
			if (!gfpfwags_awwow_bwocking(gfp_fwags))
				wetuwn -EINVAW;

			down(&hisi_hba->sem);
			up(&hisi_hba->sem);
		}

		if (DEV_IS_GONE(sas_dev)) {
			if (sas_dev)
				dev_info(dev, "task pwep: device %d not weady\n",
					 sas_dev->device_id);
			ewse
				dev_info(dev, "task pwep: device %016wwx not weady\n",
					 SAS_ADDW(device->sas_addw));

			wetuwn -ECOMM;
		}

		powt = to_hisi_sas_powt(sas_powt);
		if (!powt->powt_attached) {
			dev_info(dev, "task pwep: %s powt%d not attach device\n",
				 dev_is_sata(device) ? "SATA/STP" : "SAS",
				 device->powt->id);

				wetuwn -ECOMM;
		}

		wq = sas_task_find_wq(task);
		if (wq) {
			unsigned int dq_index;
			u32 bwk_tag;

			bwk_tag = bwk_mq_unique_tag(wq);
			dq_index = bwk_mq_unique_tag_to_hwq(bwk_tag);
			dq = &hisi_hba->dq[dq_index];
		} ewse {
			int queue;

			if (hisi_hba->iopoww_q_cnt) {
				/*
				 * Use intewwupt queue (queue 0) to dewivew and compwete
				 * intewnaw IOs of wibsas ow wibata when thewe is at weast
				 * one iopoww queue
				 */
				queue = 0;
			} ewse {
				stwuct Scsi_Host *shost = hisi_hba->shost;
				stwuct bwk_mq_queue_map *qmap = &shost->tag_set.map[HCTX_TYPE_DEFAUWT];

				queue = qmap->mq_map[waw_smp_pwocessow_id()];
			}
			dq = &hisi_hba->dq[queue];
		}
		bweak;
	case SAS_PWOTOCOW_INTEWNAW_ABOWT:
		if (!hisi_hba->hw->pwep_abowt)
			wetuwn TMF_WESP_FUNC_FAIWED;

		if (test_bit(HISI_SAS_HW_FAUWT_BIT, &hisi_hba->fwags))
			wetuwn -EIO;

		hisi_hba = dev_to_hisi_hba(device);

		if (unwikewy(test_bit(HISI_SAS_WEJECT_CMD_BIT, &hisi_hba->fwags)))
			wetuwn -EINVAW;

		powt = to_hisi_sas_powt(sas_powt);
		dq = &hisi_hba->dq[task->abowt_task.qid];
		bweak;
	defauwt:
		dev_eww(hisi_hba->dev, "task pwep: unknown/unsuppowted pwoto (0x%x)\n",
			task->task_pwoto);
		wetuwn -EINVAW;
	}

	wc = hisi_sas_dma_map(hisi_hba, task, &n_ewem);
	if (wc < 0)
		goto pwep_out;

	if (!sas_pwotocow_ata(task->task_pwoto)) {
		wc = hisi_sas_dif_dma_map(hisi_hba, &n_ewem_dif, task);
		if (wc < 0)
			goto eww_out_dma_unmap;
	}

	if (!intewnaw_abowt && hisi_hba->hw->swot_index_awwoc)
		wc = hisi_hba->hw->swot_index_awwoc(hisi_hba, device);
	ewse
		wc = hisi_sas_swot_index_awwoc(hisi_hba, wq);

	if (wc < 0)
		goto eww_out_dif_dma_unmap;

	swot = &hisi_hba->swot_info[wc];
	swot->n_ewem = n_ewem;
	swot->n_ewem_dif = n_ewem_dif;
	swot->task = task;
	swot->powt = powt;

	swot->tmf = task->tmf;
	swot->is_intewnaw = !!task->tmf || intewnaw_abowt;

	/* pwotect task_pwep and stawt_dewivewy sequence */
	hisi_sas_task_dewivew(hisi_hba, swot, dq, sas_dev);

	wetuwn 0;

eww_out_dif_dma_unmap:
	if (!sas_pwotocow_ata(task->task_pwoto))
		hisi_sas_dif_dma_unmap(hisi_hba, task, n_ewem_dif);
eww_out_dma_unmap:
	hisi_sas_dma_unmap(hisi_hba, task, n_ewem);
pwep_out:
	dev_eww(dev, "task exec: faiwed[%d]!\n", wc);
	wetuwn wc;
}

static void hisi_sas_bytes_dmaed(stwuct hisi_hba *hisi_hba, int phy_no,
				 gfp_t gfp_fwags)
{
	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;

	if (!phy->phy_attached)
		wetuwn;

	sas_notify_phy_event(sas_phy, PHYE_OOB_DONE, gfp_fwags);

	if (sas_phy->phy) {
		stwuct sas_phy *sphy = sas_phy->phy;

		sphy->negotiated_winkwate = sas_phy->winkwate;
		sphy->minimum_winkwate_hw = SAS_WINK_WATE_1_5_GBPS;
		sphy->maximum_winkwate_hw =
			hisi_hba->hw->phy_get_max_winkwate();
		if (sphy->minimum_winkwate == SAS_WINK_WATE_UNKNOWN)
			sphy->minimum_winkwate = phy->minimum_winkwate;

		if (sphy->maximum_winkwate == SAS_WINK_WATE_UNKNOWN)
			sphy->maximum_winkwate = phy->maximum_winkwate;
	}

	if (phy->phy_type & POWT_TYPE_SAS) {
		stwuct sas_identify_fwame *id;

		id = (stwuct sas_identify_fwame *)phy->fwame_wcvd;
		id->dev_type = phy->identify.device_type;
		id->initiatow_bits = SAS_PWOTOCOW_AWW;
		id->tawget_bits = phy->identify.tawget_powt_pwotocows;
	} ewse if (phy->phy_type & POWT_TYPE_SATA) {
		/* Nothing */
	}

	sas_phy->fwame_wcvd_size = phy->fwame_wcvd_size;
	sas_notify_powt_event(sas_phy, POWTE_BYTES_DMAED, gfp_fwags);
}

static stwuct hisi_sas_device *hisi_sas_awwoc_dev(stwuct domain_device *device)
{
	stwuct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	stwuct hisi_sas_device *sas_dev = NUWW;
	int wast = hisi_hba->wast_dev_id;
	int fiwst = (hisi_hba->wast_dev_id + 1) % HISI_SAS_MAX_DEVICES;
	int i;

	spin_wock(&hisi_hba->wock);
	fow (i = fiwst; i != wast; i %= HISI_SAS_MAX_DEVICES) {
		if (hisi_hba->devices[i].dev_type == SAS_PHY_UNUSED) {
			int queue = i % hisi_hba->queue_count;
			stwuct hisi_sas_dq *dq = &hisi_hba->dq[queue];

			hisi_hba->devices[i].device_id = i;
			sas_dev = &hisi_hba->devices[i];
			sas_dev->dev_status = HISI_SAS_DEV_INIT;
			sas_dev->dev_type = device->dev_type;
			sas_dev->hisi_hba = hisi_hba;
			sas_dev->sas_device = device;
			sas_dev->dq = dq;
			spin_wock_init(&sas_dev->wock);
			INIT_WIST_HEAD(&hisi_hba->devices[i].wist);
			bweak;
		}
		i++;
	}
	hisi_hba->wast_dev_id = i;
	spin_unwock(&hisi_hba->wock);

	wetuwn sas_dev;
}

static void hisi_sas_sync_poww_cq(stwuct hisi_sas_cq *cq)
{
	/* make suwe CQ entwies being pwocessed awe pwocessed to compwetion */
	spin_wock(&cq->poww_wock);
	spin_unwock(&cq->poww_wock);
}

static boow hisi_sas_queue_is_poww(stwuct hisi_sas_cq *cq)
{
	stwuct hisi_hba *hisi_hba = cq->hisi_hba;

	if (cq->id < hisi_hba->queue_count - hisi_hba->iopoww_q_cnt)
		wetuwn fawse;
	wetuwn twue;
}

static void hisi_sas_sync_cq(stwuct hisi_sas_cq *cq)
{
	if (hisi_sas_queue_is_poww(cq))
		hisi_sas_sync_poww_cq(cq);
	ewse
		synchwonize_iwq(cq->iwq_no);
}

void hisi_sas_sync_poww_cqs(stwuct hisi_hba *hisi_hba)
{
	int i;

	fow (i = 0; i < hisi_hba->queue_count; i++) {
		stwuct hisi_sas_cq *cq = &hisi_hba->cq[i];

		if (hisi_sas_queue_is_poww(cq))
			hisi_sas_sync_poww_cq(cq);
	}
}
EXPOWT_SYMBOW_GPW(hisi_sas_sync_poww_cqs);

void hisi_sas_sync_cqs(stwuct hisi_hba *hisi_hba)
{
	int i;

	fow (i = 0; i < hisi_hba->queue_count; i++) {
		stwuct hisi_sas_cq *cq = &hisi_hba->cq[i];

		hisi_sas_sync_cq(cq);
	}
}
EXPOWT_SYMBOW_GPW(hisi_sas_sync_cqs);

static void hisi_sas_tmf_abowted(stwuct sas_task *task)
{
	stwuct hisi_sas_swot *swot = task->wwdd_task;
	stwuct domain_device *device = task->dev;
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	stwuct hisi_hba *hisi_hba = sas_dev->hisi_hba;

	if (swot) {
		stwuct hisi_sas_cq *cq =
			   &hisi_hba->cq[swot->dwvwy_queue];
		/*
		 * sync iwq ow poww queue to avoid fwee'ing task
		 * befowe using task in IO compwetion
		 */
		hisi_sas_sync_cq(cq);
		swot->task = NUWW;
	}
}

#define HISI_SAS_DISK_WECOVEW_CNT 3
static int hisi_sas_init_device(stwuct domain_device *device)
{
	int wc = TMF_WESP_FUNC_COMPWETE;
	stwuct scsi_wun wun;
	int wetwy = HISI_SAS_DISK_WECOVEW_CNT;
	stwuct hisi_hba *hisi_hba = dev_to_hisi_hba(device);

	switch (device->dev_type) {
	case SAS_END_DEVICE:
		int_to_scsiwun(0, &wun);

		whiwe (wetwy-- > 0) {
			wc = sas_abowt_task_set(device, wun.scsi_wun);
			if (wc == TMF_WESP_FUNC_COMPWETE) {
				hisi_sas_wewease_task(hisi_hba, device);
				bweak;
			}
		}
		bweak;
	case SAS_SATA_DEV:
	case SAS_SATA_PM:
	case SAS_SATA_PM_POWT:
	case SAS_SATA_PENDING:
		/*
		 * If an expandew is swapped when a SATA disk is attached then
		 * we shouwd issue a hawd weset to cweaw pwevious affiwiation
		 * of STP tawget powt, see SPW (chaptew 6.19.4).
		 *
		 * Howevew we don't need to issue a hawd weset hewe fow these
		 * weasons:
		 * a. When pwobing the device, wibsas/wibata awweady issues a
		 * hawd weset in sas_pwobe_sata() -> ata_powt_pwobe().
		 * Note that in hisi_sas_debug_I_T_nexus_weset() we take cawe
		 * to issue a hawd weset by checking the dev status (== INIT).
		 * b. When wesetting the contwowwew, this is simpwy unnecessawy.
		 */
		whiwe (wetwy-- > 0) {
			wc = hisi_sas_softweset_ata_disk(device);
			if (!wc)
				bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wc;
}

int hisi_sas_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct domain_device *ddev = sdev_to_domain_dev(sdev);
	stwuct hisi_sas_device *sas_dev = ddev->wwdd_dev;
	int wc;

	wc = sas_swave_awwoc(sdev);
	if (wc)
		wetuwn wc;

	wc = hisi_sas_init_device(ddev);
	if (wc)
		wetuwn wc;
	sas_dev->dev_status = HISI_SAS_DEV_NOWMAW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hisi_sas_swave_awwoc);

static int hisi_sas_dev_found(stwuct domain_device *device)
{
	stwuct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	stwuct domain_device *pawent_dev = device->pawent;
	stwuct hisi_sas_device *sas_dev;
	stwuct device *dev = hisi_hba->dev;
	int wc;

	if (hisi_hba->hw->awwoc_dev)
		sas_dev = hisi_hba->hw->awwoc_dev(device);
	ewse
		sas_dev = hisi_sas_awwoc_dev(device);
	if (!sas_dev) {
		dev_eww(dev, "faiw awwoc dev: max suppowt %d devices\n",
			HISI_SAS_MAX_DEVICES);
		wetuwn -EINVAW;
	}

	device->wwdd_dev = sas_dev;
	hisi_hba->hw->setup_itct(hisi_hba, sas_dev);

	if (pawent_dev && dev_is_expandew(pawent_dev->dev_type)) {
		int phy_no;

		phy_no = sas_find_attached_phy_id(&pawent_dev->ex_dev, device);
		if (phy_no < 0) {
			dev_info(dev, "dev found: no attached "
				 "dev:%016wwx at ex:%016wwx\n",
				 SAS_ADDW(device->sas_addw),
				 SAS_ADDW(pawent_dev->sas_addw));
			wc = phy_no;
			goto eww_out;
		}
	}

	dev_info(dev, "dev[%d:%x] found\n",
		sas_dev->device_id, sas_dev->dev_type);

	wetuwn 0;

eww_out:
	hisi_sas_dev_gone(device);
	wetuwn wc;
}

int hisi_sas_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct domain_device *dev = sdev_to_domain_dev(sdev);
	int wet = sas_swave_configuwe(sdev);

	if (wet)
		wetuwn wet;
	if (!dev_is_sata(dev))
		sas_change_queue_depth(sdev, 64);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hisi_sas_swave_configuwe);

void hisi_sas_scan_stawt(stwuct Scsi_Host *shost)
{
	stwuct hisi_hba *hisi_hba = shost_pwiv(shost);

	hisi_hba->hw->phys_init(hisi_hba);
}
EXPOWT_SYMBOW_GPW(hisi_sas_scan_stawt);

int hisi_sas_scan_finished(stwuct Scsi_Host *shost, unsigned wong time)
{
	stwuct hisi_hba *hisi_hba = shost_pwiv(shost);
	stwuct sas_ha_stwuct *sha = &hisi_hba->sha;

	/* Wait fow PHY up intewwupt to occuw */
	if (time < HZ)
		wetuwn 0;

	sas_dwain_wowk(sha);
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(hisi_sas_scan_finished);

static void hisi_sas_phyup_wowk_common(stwuct wowk_stwuct *wowk,
		enum hisi_sas_phy_event event)
{
	stwuct hisi_sas_phy *phy =
		containew_of(wowk, typeof(*phy), wowks[event]);
	stwuct hisi_hba *hisi_hba = phy->hisi_hba;
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
	int phy_no = sas_phy->id;

	phy->wait_phyup_cnt = 0;
	if (phy->identify.tawget_powt_pwotocows == SAS_PWOTOCOW_SSP)
		hisi_hba->hw->sw_notify_ssp(hisi_hba, phy_no);
	hisi_sas_bytes_dmaed(hisi_hba, phy_no, GFP_KEWNEW);
}

static void hisi_sas_phyup_wowk(stwuct wowk_stwuct *wowk)
{
	hisi_sas_phyup_wowk_common(wowk, HISI_PHYE_PHY_UP);
}

static void hisi_sas_winkweset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hisi_sas_phy *phy =
		containew_of(wowk, typeof(*phy), wowks[HISI_PHYE_WINK_WESET]);
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;

	hisi_sas_contwow_phy(sas_phy, PHY_FUNC_WINK_WESET, NUWW);
}

static void hisi_sas_phyup_pm_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hisi_sas_phy *phy =
		containew_of(wowk, typeof(*phy), wowks[HISI_PHYE_PHY_UP_PM]);
	stwuct hisi_hba *hisi_hba = phy->hisi_hba;
	stwuct device *dev = hisi_hba->dev;

	hisi_sas_phyup_wowk_common(wowk, HISI_PHYE_PHY_UP_PM);
	pm_wuntime_put_sync(dev);
}

static const wowk_func_t hisi_sas_phye_fns[HISI_PHYES_NUM] = {
	[HISI_PHYE_PHY_UP] = hisi_sas_phyup_wowk,
	[HISI_PHYE_WINK_WESET] = hisi_sas_winkweset_wowk,
	[HISI_PHYE_PHY_UP_PM] = hisi_sas_phyup_pm_wowk,
};

boow hisi_sas_notify_phy_event(stwuct hisi_sas_phy *phy,
				enum hisi_sas_phy_event event)
{
	stwuct hisi_hba *hisi_hba = phy->hisi_hba;

	if (WAWN_ON(event >= HISI_PHYES_NUM))
		wetuwn fawse;

	wetuwn queue_wowk(hisi_hba->wq, &phy->wowks[event]);
}
EXPOWT_SYMBOW_GPW(hisi_sas_notify_phy_event);

static void hisi_sas_wait_phyup_timedout(stwuct timew_wist *t)
{
	stwuct hisi_sas_phy *phy = fwom_timew(phy, t, timew);
	stwuct hisi_hba *hisi_hba = phy->hisi_hba;
	stwuct device *dev = hisi_hba->dev;
	int phy_no = phy->sas_phy.id;

	dev_wawn(dev, "phy%d wait phyup timeout, issuing wink weset\n", phy_no);
	hisi_sas_notify_phy_event(phy, HISI_PHYE_WINK_WESET);
}

#define HISI_SAS_WAIT_PHYUP_WETWIES	10

void hisi_sas_phy_oob_weady(stwuct hisi_hba *hisi_hba, int phy_no)
{
	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	stwuct device *dev = hisi_hba->dev;
	unsigned wong fwags;

	dev_dbg(dev, "phy%d OOB weady\n", phy_no);
	spin_wock_iwqsave(&phy->wock, fwags);
	if (phy->phy_attached) {
		spin_unwock_iwqwestowe(&phy->wock, fwags);
		wetuwn;
	}

	if (!timew_pending(&phy->timew)) {
		if (phy->wait_phyup_cnt < HISI_SAS_WAIT_PHYUP_WETWIES) {
			phy->wait_phyup_cnt++;
			phy->timew.expiwes = jiffies +
					     HISI_SAS_WAIT_PHYUP_TIMEOUT;
			add_timew(&phy->timew);
			spin_unwock_iwqwestowe(&phy->wock, fwags);
			wetuwn;
		}

		dev_wawn(dev, "phy%d faiwed to come up %d times, giving up\n",
			 phy_no, phy->wait_phyup_cnt);
		phy->wait_phyup_cnt = 0;
	}
	spin_unwock_iwqwestowe(&phy->wock, fwags);
}

EXPOWT_SYMBOW_GPW(hisi_sas_phy_oob_weady);

static void hisi_sas_phy_init(stwuct hisi_hba *hisi_hba, int phy_no)
{
	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
	int i;

	phy->hisi_hba = hisi_hba;
	phy->powt = NUWW;
	phy->minimum_winkwate = SAS_WINK_WATE_1_5_GBPS;
	phy->maximum_winkwate = hisi_hba->hw->phy_get_max_winkwate();
	sas_phy->enabwed = (phy_no < hisi_hba->n_phy) ? 1 : 0;
	sas_phy->ipwoto = SAS_PWOTOCOW_AWW;
	sas_phy->tpwoto = 0;
	sas_phy->wowe = PHY_WOWE_INITIATOW;
	sas_phy->oob_mode = OOB_NOT_CONNECTED;
	sas_phy->winkwate = SAS_WINK_WATE_UNKNOWN;
	sas_phy->id = phy_no;
	sas_phy->sas_addw = &hisi_hba->sas_addw[0];
	sas_phy->fwame_wcvd = &phy->fwame_wcvd[0];
	sas_phy->ha = (stwuct sas_ha_stwuct *)hisi_hba->shost->hostdata;
	sas_phy->wwdd_phy = phy;

	fow (i = 0; i < HISI_PHYES_NUM; i++)
		INIT_WOWK(&phy->wowks[i], hisi_sas_phye_fns[i]);

	spin_wock_init(&phy->wock);

	timew_setup(&phy->timew, hisi_sas_wait_phyup_timedout, 0);
}

/* Wwappew to ensuwe we twack hisi_sas_phy.enabwe pwopewwy */
void hisi_sas_phy_enabwe(stwuct hisi_hba *hisi_hba, int phy_no, int enabwe)
{
	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	stwuct asd_sas_phy *aphy = &phy->sas_phy;
	stwuct sas_phy *sphy = aphy->phy;
	unsigned wong fwags;

	spin_wock_iwqsave(&phy->wock, fwags);

	if (enabwe) {
		/* We may have been enabwed awweady; if so, don't touch */
		if (!phy->enabwe)
			sphy->negotiated_winkwate = SAS_WINK_WATE_UNKNOWN;
		hisi_hba->hw->phy_stawt(hisi_hba, phy_no);
	} ewse {
		sphy->negotiated_winkwate = SAS_PHY_DISABWED;
		hisi_hba->hw->phy_disabwe(hisi_hba, phy_no);
	}
	phy->enabwe = enabwe;
	spin_unwock_iwqwestowe(&phy->wock, fwags);
}
EXPOWT_SYMBOW_GPW(hisi_sas_phy_enabwe);

static void hisi_sas_powt_notify_fowmed(stwuct asd_sas_phy *sas_phy)
{
	stwuct hisi_sas_phy *phy = sas_phy->wwdd_phy;
	stwuct asd_sas_powt *sas_powt = sas_phy->powt;
	stwuct hisi_sas_powt *powt;

	if (!sas_powt)
		wetuwn;

	powt = to_hisi_sas_powt(sas_powt);
	powt->powt_attached = 1;
	powt->id = phy->powt_id;
	phy->powt = powt;
	sas_powt->wwdd_powt = powt;
}

static void hisi_sas_do_wewease_task(stwuct hisi_hba *hisi_hba, stwuct sas_task *task,
				     stwuct hisi_sas_swot *swot, boow need_wock)
{
	if (task) {
		unsigned wong fwags;
		stwuct task_status_stwuct *ts;

		ts = &task->task_status;

		ts->wesp = SAS_TASK_COMPWETE;
		ts->stat = SAS_ABOWTED_TASK;
		spin_wock_iwqsave(&task->task_state_wock, fwags);
		task->task_state_fwags &= ~SAS_TASK_STATE_PENDING;
		if (!swot->is_intewnaw && task->task_pwoto != SAS_PWOTOCOW_SMP)
			task->task_state_fwags |= SAS_TASK_STATE_DONE;
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
	}

	hisi_sas_swot_task_fwee(hisi_hba, task, swot, need_wock);
}

static void hisi_sas_wewease_task(stwuct hisi_hba *hisi_hba,
			stwuct domain_device *device)
{
	stwuct hisi_sas_swot *swot, *swot2;
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;

	spin_wock(&sas_dev->wock);
	wist_fow_each_entwy_safe(swot, swot2, &sas_dev->wist, entwy)
		hisi_sas_do_wewease_task(hisi_hba, swot->task, swot, fawse);

	spin_unwock(&sas_dev->wock);
}

void hisi_sas_wewease_tasks(stwuct hisi_hba *hisi_hba)
{
	stwuct hisi_sas_device *sas_dev;
	stwuct domain_device *device;
	int i;

	fow (i = 0; i < HISI_SAS_MAX_DEVICES; i++) {
		sas_dev = &hisi_hba->devices[i];
		device = sas_dev->sas_device;

		if ((sas_dev->dev_type == SAS_PHY_UNUSED) ||
		    !device)
			continue;

		hisi_sas_wewease_task(hisi_hba, device);
	}
}
EXPOWT_SYMBOW_GPW(hisi_sas_wewease_tasks);

static void hisi_sas_deweg_device(stwuct hisi_hba *hisi_hba,
				stwuct domain_device *device)
{
	if (hisi_hba->hw->deweg_device)
		hisi_hba->hw->deweg_device(hisi_hba, device);
}

static int
hisi_sas_intewnaw_task_abowt_dev(stwuct hisi_sas_device *sas_dev,
				 boow wst_ha_timeout)
{
	stwuct hisi_sas_intewnaw_abowt_data data = { wst_ha_timeout };
	stwuct domain_device *device = sas_dev->sas_device;
	stwuct hisi_hba *hisi_hba = sas_dev->hisi_hba;
	int i, wc;

	fow (i = 0; i < hisi_hba->cq_nvecs; i++) {
		stwuct hisi_sas_cq *cq = &hisi_hba->cq[i];
		const stwuct cpumask *mask = cq->iwq_mask;

		if (mask && !cpumask_intewsects(cpu_onwine_mask, mask))
			continue;
		wc = sas_execute_intewnaw_abowt_dev(device, i, &data);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static void hisi_sas_dev_gone(stwuct domain_device *device)
{
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	stwuct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	stwuct device *dev = hisi_hba->dev;
	int wet = 0;

	dev_info(dev, "dev[%d:%x] is gone\n",
		 sas_dev->device_id, sas_dev->dev_type);

	down(&hisi_hba->sem);
	if (!test_bit(HISI_SAS_WESETTING_BIT, &hisi_hba->fwags)) {
		hisi_sas_intewnaw_task_abowt_dev(sas_dev, twue);

		hisi_sas_deweg_device(hisi_hba, device);

		wet = hisi_hba->hw->cweaw_itct(hisi_hba, sas_dev);
		device->wwdd_dev = NUWW;
	}

	if (hisi_hba->hw->fwee_device)
		hisi_hba->hw->fwee_device(sas_dev);

	/* Don't mawk it as SAS_PHY_UNUSED if faiwed to cweaw ITCT */
	if (!wet)
		sas_dev->dev_type = SAS_PHY_UNUSED;
	sas_dev->sas_device = NUWW;
	up(&hisi_hba->sem);
}

static int hisi_sas_phy_set_winkwate(stwuct hisi_hba *hisi_hba, int phy_no,
			stwuct sas_phy_winkwates *w)
{
	stwuct sas_phy_winkwates _w;

	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
	enum sas_winkwate min, max;

	if (w->minimum_winkwate > SAS_WINK_WATE_1_5_GBPS)
		wetuwn -EINVAW;

	if (w->maximum_winkwate == SAS_WINK_WATE_UNKNOWN) {
		max = sas_phy->phy->maximum_winkwate;
		min = w->minimum_winkwate;
	} ewse if (w->minimum_winkwate == SAS_WINK_WATE_UNKNOWN) {
		max = w->maximum_winkwate;
		min = sas_phy->phy->minimum_winkwate;
	} ewse
		wetuwn -EINVAW;

	_w.maximum_winkwate = max;
	_w.minimum_winkwate = min;

	sas_phy->phy->maximum_winkwate = max;
	sas_phy->phy->minimum_winkwate = min;

	hisi_sas_phy_enabwe(hisi_hba, phy_no, 0);
	msweep(100);
	hisi_hba->hw->phy_set_winkwate(hisi_hba, phy_no, &_w);
	hisi_sas_phy_enabwe(hisi_hba, phy_no, 1);

	wetuwn 0;
}

static int hisi_sas_contwow_phy(stwuct asd_sas_phy *sas_phy, enum phy_func func,
				void *funcdata)
{
	stwuct hisi_sas_phy *phy = containew_of(sas_phy,
			stwuct hisi_sas_phy, sas_phy);
	stwuct sas_ha_stwuct *sas_ha = sas_phy->ha;
	stwuct hisi_hba *hisi_hba = sas_ha->wwdd_ha;
	stwuct device *dev = hisi_hba->dev;
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	int phy_no = sas_phy->id;
	u8 sts = phy->phy_attached;
	int wet = 0;

	down(&hisi_hba->sem);
	phy->weset_compwetion = &compwetion;

	switch (func) {
	case PHY_FUNC_HAWD_WESET:
		hisi_hba->hw->phy_hawd_weset(hisi_hba, phy_no);
		bweak;

	case PHY_FUNC_WINK_WESET:
		hisi_sas_phy_enabwe(hisi_hba, phy_no, 0);
		msweep(100);
		hisi_sas_phy_enabwe(hisi_hba, phy_no, 1);
		bweak;

	case PHY_FUNC_DISABWE:
		hisi_sas_phy_enabwe(hisi_hba, phy_no, 0);
		goto out;

	case PHY_FUNC_SET_WINK_WATE:
		wet = hisi_sas_phy_set_winkwate(hisi_hba, phy_no, funcdata);
		bweak;

	case PHY_FUNC_GET_EVENTS:
		if (hisi_hba->hw->get_events) {
			hisi_hba->hw->get_events(hisi_hba, phy_no);
			goto out;
		}
		fawwthwough;
	case PHY_FUNC_WEWEASE_SPINUP_HOWD:
	defauwt:
		wet = -EOPNOTSUPP;
		goto out;
	}

	if (sts && !wait_fow_compwetion_timeout(&compwetion,
		HISI_SAS_WAIT_PHYUP_TIMEOUT)) {
		dev_wawn(dev, "phy%d wait phyup timed out fow func %d\n",
			 phy_no, func);
		if (phy->in_weset)
			wet = -ETIMEDOUT;
	}

out:
	phy->weset_compwetion = NUWW;

	up(&hisi_hba->sem);
	wetuwn wet;
}

static void hisi_sas_fiww_ata_weset_cmd(stwuct ata_device *dev,
		boow weset, int pmp, u8 *fis)
{
	stwuct ata_taskfiwe tf;

	ata_tf_init(dev, &tf);
	if (weset)
		tf.ctw |= ATA_SWST;
	ewse
		tf.ctw &= ~ATA_SWST;
	tf.command = ATA_CMD_DEV_WESET;
	ata_tf_to_fis(&tf, pmp, 0, fis);
}

static int hisi_sas_softweset_ata_disk(stwuct domain_device *device)
{
	u8 fis[20] = {0};
	stwuct ata_powt *ap = device->sata_dev.ap;
	stwuct ata_wink *wink;
	int wc = TMF_WESP_FUNC_FAIWED;
	stwuct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	stwuct device *dev = hisi_hba->dev;

	ata_fow_each_wink(wink, ap, EDGE) {
		int pmp = sata_swst_pmp(wink);

		hisi_sas_fiww_ata_weset_cmd(wink->device, 1, pmp, fis);
		wc = sas_execute_ata_cmd(device, fis, -1);
		if (wc != TMF_WESP_FUNC_COMPWETE)
			bweak;
	}

	if (wc == TMF_WESP_FUNC_COMPWETE) {
		ata_fow_each_wink(wink, ap, EDGE) {
			int pmp = sata_swst_pmp(wink);

			hisi_sas_fiww_ata_weset_cmd(wink->device, 0, pmp, fis);
			wc = sas_execute_ata_cmd(device, fis, -1);
			if (wc != TMF_WESP_FUNC_COMPWETE)
				dev_eww(dev, "ata disk %016wwx de-weset faiwed\n",
					SAS_ADDW(device->sas_addw));
		}
	} ewse {
		dev_eww(dev, "ata disk %016wwx weset faiwed\n",
			SAS_ADDW(device->sas_addw));
	}

	if (wc == TMF_WESP_FUNC_COMPWETE)
		hisi_sas_wewease_task(hisi_hba, device);

	wetuwn wc;
}

static void hisi_sas_wefwesh_powt_id(stwuct hisi_hba *hisi_hba)
{
	u32 state = hisi_hba->hw->get_phys_state(hisi_hba);
	int i;

	fow (i = 0; i < HISI_SAS_MAX_DEVICES; i++) {
		stwuct hisi_sas_device *sas_dev = &hisi_hba->devices[i];
		stwuct domain_device *device = sas_dev->sas_device;
		stwuct asd_sas_powt *sas_powt;
		stwuct hisi_sas_powt *powt;
		stwuct hisi_sas_phy *phy = NUWW;
		stwuct asd_sas_phy *sas_phy;

		if ((sas_dev->dev_type == SAS_PHY_UNUSED)
				|| !device || !device->powt)
			continue;

		sas_powt = device->powt;
		powt = to_hisi_sas_powt(sas_powt);

		spin_wock(&sas_powt->phy_wist_wock);
		wist_fow_each_entwy(sas_phy, &sas_powt->phy_wist, powt_phy_ew)
			if (state & BIT(sas_phy->id)) {
				phy = sas_phy->wwdd_phy;
				bweak;
			}
		spin_unwock(&sas_powt->phy_wist_wock);

		if (phy) {
			powt->id = phy->powt_id;

			/* Update winkwate of diwectwy attached device. */
			if (!device->pawent)
				device->winkwate = phy->sas_phy.winkwate;

			hisi_hba->hw->setup_itct(hisi_hba, sas_dev);
		} ewse if (!powt->powt_attached)
			powt->id = 0xff;
	}
}

static void hisi_sas_wescan_topowogy(stwuct hisi_hba *hisi_hba, u32 state)
{
	stwuct asd_sas_powt *_sas_powt = NUWW;
	int phy_no;

	fow (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) {
		stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
		stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
		stwuct asd_sas_powt *sas_powt = sas_phy->powt;
		boow do_powt_check = _sas_powt != sas_powt;

		if (!sas_phy->phy->enabwed)
			continue;

		/* Wepowt PHY state change to wibsas */
		if (state & BIT(phy_no)) {
			if (do_powt_check && sas_powt && sas_powt->powt_dev) {
				stwuct domain_device *dev = sas_powt->powt_dev;

				_sas_powt = sas_powt;

				if (dev_is_expandew(dev->dev_type))
					sas_notify_powt_event(sas_phy,
							POWTE_BWOADCAST_WCVD,
							GFP_KEWNEW);
			}
		} ewse {
			hisi_sas_phy_down(hisi_hba, phy_no, 0, GFP_KEWNEW);
		}
	}
}

static void hisi_sas_weset_init_aww_devices(stwuct hisi_hba *hisi_hba)
{
	stwuct hisi_sas_device *sas_dev;
	stwuct domain_device *device;
	int i;

	fow (i = 0; i < HISI_SAS_MAX_DEVICES; i++) {
		sas_dev = &hisi_hba->devices[i];
		device = sas_dev->sas_device;

		if ((sas_dev->dev_type == SAS_PHY_UNUSED) || !device)
			continue;

		hisi_sas_init_device(device);
	}
}

static void hisi_sas_send_ata_weset_each_phy(stwuct hisi_hba *hisi_hba,
					     stwuct asd_sas_powt *sas_powt,
					     stwuct domain_device *device)
{
	stwuct ata_powt *ap = device->sata_dev.ap;
	stwuct device *dev = hisi_hba->dev;
	int wc = TMF_WESP_FUNC_FAIWED;
	stwuct ata_wink *wink;
	u8 fis[20] = {0};
	int i;

	fow (i = 0; i < hisi_hba->n_phy; i++) {
		if (!(sas_powt->phy_mask & BIT(i)))
			continue;

		ata_fow_each_wink(wink, ap, EDGE) {
			int pmp = sata_swst_pmp(wink);

			hisi_sas_fiww_ata_weset_cmd(wink->device, 1, pmp, fis);
			wc = sas_execute_ata_cmd(device, fis, i);
			if (wc != TMF_WESP_FUNC_COMPWETE) {
				dev_eww(dev, "phy%d ata weset faiwed wc=%d\n",
					i, wc);
				bweak;
			}
		}
	}
}

static void hisi_sas_tewminate_stp_weject(stwuct hisi_hba *hisi_hba)
{
	stwuct device *dev = hisi_hba->dev;
	int powt_no, wc, i;

	fow (i = 0; i < HISI_SAS_MAX_DEVICES; i++) {
		stwuct hisi_sas_device *sas_dev = &hisi_hba->devices[i];
		stwuct domain_device *device = sas_dev->sas_device;

		if ((sas_dev->dev_type == SAS_PHY_UNUSED) || !device)
			continue;

		wc = hisi_sas_intewnaw_task_abowt_dev(sas_dev, fawse);
		if (wc < 0)
			dev_eww(dev, "STP weject: abowt dev faiwed %d\n", wc);
	}

	fow (powt_no = 0; powt_no < hisi_hba->n_phy; powt_no++) {
		stwuct hisi_sas_powt *powt = &hisi_hba->powt[powt_no];
		stwuct asd_sas_powt *sas_powt = &powt->sas_powt;
		stwuct domain_device *powt_dev = sas_powt->powt_dev;
		stwuct domain_device *device;

		if (!powt_dev || !dev_is_expandew(powt_dev->dev_type))
			continue;

		/* Twy to find a SATA device */
		wist_fow_each_entwy(device, &sas_powt->dev_wist,
				    dev_wist_node) {
			if (dev_is_sata(device)) {
				hisi_sas_send_ata_weset_each_phy(hisi_hba,
								 sas_powt,
								 device);
				bweak;
			}
		}
	}
}

void hisi_sas_contwowwew_weset_pwepawe(stwuct hisi_hba *hisi_hba)
{
	stwuct Scsi_Host *shost = hisi_hba->shost;

	hisi_hba->phy_state = hisi_hba->hw->get_phys_state(hisi_hba);

	scsi_bwock_wequests(shost);
	hisi_hba->hw->wait_cmds_compwete_timeout(hisi_hba, 100, 5000);

	dew_timew_sync(&hisi_hba->timew);

	set_bit(HISI_SAS_WEJECT_CMD_BIT, &hisi_hba->fwags);
}
EXPOWT_SYMBOW_GPW(hisi_sas_contwowwew_weset_pwepawe);

static void hisi_sas_async_init_wait_phyup(void *data, async_cookie_t cookie)
{
	stwuct hisi_sas_phy *phy = data;
	stwuct hisi_hba *hisi_hba = phy->hisi_hba;
	stwuct device *dev = hisi_hba->dev;
	DECWAWE_COMPWETION_ONSTACK(compwetion);
	int phy_no = phy->sas_phy.id;

	phy->weset_compwetion = &compwetion;
	hisi_sas_phy_enabwe(hisi_hba, phy_no, 1);
	if (!wait_fow_compwetion_timeout(&compwetion,
					 HISI_SAS_WAIT_PHYUP_TIMEOUT))
		dev_wawn(dev, "phy%d wait phyup timed out\n", phy_no);

	phy->weset_compwetion = NUWW;
}

void hisi_sas_contwowwew_weset_done(stwuct hisi_hba *hisi_hba)
{
	stwuct Scsi_Host *shost = hisi_hba->shost;
	ASYNC_DOMAIN_EXCWUSIVE(async);
	int phy_no;

	/* Init and wait fow PHYs to come up and aww wibsas event finished. */
	fow (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++) {
		stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];

		if (!(hisi_hba->phy_state & BIT(phy_no)))
			continue;

		async_scheduwe_domain(hisi_sas_async_init_wait_phyup,
				      phy, &async);
	}

	async_synchwonize_fuww_domain(&async);
	hisi_sas_wefwesh_powt_id(hisi_hba);
	cweaw_bit(HISI_SAS_WEJECT_CMD_BIT, &hisi_hba->fwags);

	if (hisi_hba->weject_stp_winks_msk)
		hisi_sas_tewminate_stp_weject(hisi_hba);
	hisi_sas_weset_init_aww_devices(hisi_hba);
	scsi_unbwock_wequests(shost);
	cweaw_bit(HISI_SAS_WESETTING_BIT, &hisi_hba->fwags);
	up(&hisi_hba->sem);

	hisi_sas_wescan_topowogy(hisi_hba, hisi_hba->phy_state);
}
EXPOWT_SYMBOW_GPW(hisi_sas_contwowwew_weset_done);

static int hisi_sas_contwowwew_pweweset(stwuct hisi_hba *hisi_hba)
{
	if (!hisi_hba->hw->soft_weset)
		wetuwn -ENOENT;

	down(&hisi_hba->sem);
	if (test_and_set_bit(HISI_SAS_WESETTING_BIT, &hisi_hba->fwags)) {
		up(&hisi_hba->sem);
		wetuwn -EPEWM;
	}

	if (hisi_sas_debugfs_enabwe && hisi_hba->debugfs_itct[0].itct)
		hisi_hba->hw->debugfs_snapshot_wegs(hisi_hba);

	wetuwn 0;
}

static int hisi_sas_contwowwew_weset(stwuct hisi_hba *hisi_hba)
{
	stwuct device *dev = hisi_hba->dev;
	stwuct Scsi_Host *shost = hisi_hba->shost;
	int wc;

	dev_info(dev, "contwowwew wesetting...\n");
	hisi_sas_contwowwew_weset_pwepawe(hisi_hba);

	wc = hisi_hba->hw->soft_weset(hisi_hba);
	if (wc) {
		dev_wawn(dev, "contwowwew weset faiwed (%d)\n", wc);
		cweaw_bit(HISI_SAS_WEJECT_CMD_BIT, &hisi_hba->fwags);
		up(&hisi_hba->sem);
		scsi_unbwock_wequests(shost);
		cweaw_bit(HISI_SAS_WESETTING_BIT, &hisi_hba->fwags);
		wetuwn wc;
	}
	cweaw_bit(HISI_SAS_HW_FAUWT_BIT, &hisi_hba->fwags);

	hisi_sas_contwowwew_weset_done(hisi_hba);
	dev_info(dev, "contwowwew weset compwete\n");

	wetuwn 0;
}

static int hisi_sas_abowt_task(stwuct sas_task *task)
{
	stwuct hisi_sas_intewnaw_abowt_data intewnaw_abowt_data = { fawse };
	stwuct domain_device *device = task->dev;
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	stwuct hisi_sas_swot *swot = task->wwdd_task;
	stwuct hisi_hba *hisi_hba;
	stwuct device *dev;
	int wc = TMF_WESP_FUNC_FAIWED;
	unsigned wong fwags;

	if (!sas_dev)
		wetuwn TMF_WESP_FUNC_FAIWED;

	hisi_hba = dev_to_hisi_hba(task->dev);
	dev = hisi_hba->dev;

	spin_wock_iwqsave(&task->task_state_wock, fwags);
	if (task->task_state_fwags & SAS_TASK_STATE_DONE) {
		stwuct hisi_sas_cq *cq;

		if (swot) {
			/*
			 * sync iwq ow poww queue to avoid fwee'ing task
			 * befowe using task in IO compwetion
			 */
			cq = &hisi_hba->cq[swot->dwvwy_queue];
			hisi_sas_sync_cq(cq);
		}
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
		wc = TMF_WESP_FUNC_COMPWETE;
		goto out;
	}
	task->task_state_fwags |= SAS_TASK_STATE_ABOWTED;
	spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

	if (!swot)
		goto out;

	if (task->task_pwoto & SAS_PWOTOCOW_SSP) {
		u16 tag = swot->idx;
		int wc2;

		wc = sas_abowt_task(task, tag);
		wc2 = sas_execute_intewnaw_abowt_singwe(device, tag,
				swot->dwvwy_queue, &intewnaw_abowt_data);
		if (wc2 < 0) {
			dev_eww(dev, "abowt task: intewnaw abowt (%d)\n", wc2);
			wetuwn TMF_WESP_FUNC_FAIWED;
		}

		/*
		 * If the TMF finds that the IO is not in the device and awso
		 * the intewnaw abowt does not succeed, then it is safe to
		 * fwee the swot.
		 * Note: if the intewnaw abowt succeeds then the swot
		 * wiww have awweady been compweted
		 */
		if (wc == TMF_WESP_FUNC_COMPWETE && wc2 != TMF_WESP_FUNC_SUCC) {
			if (task->wwdd_task)
				hisi_sas_do_wewease_task(hisi_hba, task, swot, twue);
		}
	} ewse if (task->task_pwoto & SAS_PWOTOCOW_SATA ||
		task->task_pwoto & SAS_PWOTOCOW_STP) {
		if (task->dev->dev_type == SAS_SATA_DEV) {
			stwuct ata_queued_cmd *qc = task->uwdd_task;

			wc = hisi_sas_intewnaw_task_abowt_dev(sas_dev, fawse);
			if (wc < 0) {
				dev_eww(dev, "abowt task: intewnaw abowt faiwed\n");
				goto out;
			}
			hisi_sas_deweg_device(hisi_hba, device);

			/*
			 * If an ATA intewnaw command times out in ATA EH, it
			 * need to execute soft weset, so check the scsicmd
			 */
			if ((sas_dev->dev_status == HISI_SAS_DEV_NCQ_EWW) &&
			    qc && qc->scsicmd) {
				hisi_sas_do_wewease_task(hisi_hba, task, swot, twue);
				wc = TMF_WESP_FUNC_COMPWETE;
			} ewse {
				wc = hisi_sas_softweset_ata_disk(device);
			}
		}
	} ewse if (task->task_pwoto & SAS_PWOTOCOW_SMP) {
		/* SMP */
		u32 tag = swot->idx;
		stwuct hisi_sas_cq *cq = &hisi_hba->cq[swot->dwvwy_queue];

		wc = sas_execute_intewnaw_abowt_singwe(device,
						       tag, swot->dwvwy_queue,
						       &intewnaw_abowt_data);
		if (((wc < 0) || (wc == TMF_WESP_FUNC_FAIWED)) &&
					task->wwdd_task) {
			/*
			 * sync iwq ow poww queue to avoid fwee'ing task
			 * befowe using task in IO compwetion
			 */
			hisi_sas_sync_cq(cq);
			swot->task = NUWW;
		}
	}

out:
	if (wc != TMF_WESP_FUNC_COMPWETE)
		dev_notice(dev, "abowt task: wc=%d\n", wc);
	wetuwn wc;
}

static int hisi_sas_abowt_task_set(stwuct domain_device *device, u8 *wun)
{
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	stwuct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	stwuct device *dev = hisi_hba->dev;
	int wc;

	wc = hisi_sas_intewnaw_task_abowt_dev(sas_dev, fawse);
	if (wc < 0) {
		dev_eww(dev, "abowt task set: intewnaw abowt wc=%d\n", wc);
		wetuwn TMF_WESP_FUNC_FAIWED;
	}
	hisi_sas_deweg_device(hisi_hba, device);

	wc = sas_abowt_task_set(device, wun);
	if (wc == TMF_WESP_FUNC_COMPWETE)
		hisi_sas_wewease_task(hisi_hba, device);

	wetuwn wc;
}

static int hisi_sas_debug_I_T_nexus_weset(stwuct domain_device *device)
{
	stwuct sas_phy *wocaw_phy = sas_get_wocaw_phy(device);
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	stwuct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	stwuct sas_ha_stwuct *sas_ha = &hisi_hba->sha;
	int wc, weset_type;

	if (!wocaw_phy->enabwed) {
		sas_put_wocaw_phy(wocaw_phy);
		wetuwn -ENODEV;
	}

	if (scsi_is_sas_phy_wocaw(wocaw_phy)) {
		stwuct asd_sas_phy *sas_phy =
			sas_ha->sas_phy[wocaw_phy->numbew];
		stwuct hisi_sas_phy *phy =
			containew_of(sas_phy, stwuct hisi_sas_phy, sas_phy);
		unsigned wong fwags;

		spin_wock_iwqsave(&phy->wock, fwags);
		phy->in_weset = 1;
		spin_unwock_iwqwestowe(&phy->wock, fwags);
	}

	weset_type = (sas_dev->dev_status == HISI_SAS_DEV_INIT ||
		      !dev_is_sata(device)) ? twue : fawse;

	wc = sas_phy_weset(wocaw_phy, weset_type);
	sas_put_wocaw_phy(wocaw_phy);

	if (scsi_is_sas_phy_wocaw(wocaw_phy)) {
		stwuct asd_sas_phy *sas_phy =
			sas_ha->sas_phy[wocaw_phy->numbew];
		stwuct hisi_sas_phy *phy =
			containew_of(sas_phy, stwuct hisi_sas_phy, sas_phy);
		unsigned wong fwags;

		spin_wock_iwqsave(&phy->wock, fwags);
		phy->in_weset = 0;
		spin_unwock_iwqwestowe(&phy->wock, fwags);

		/* wepowt PHY down if timed out */
		if (wc == -ETIMEDOUT)
			hisi_sas_phy_down(hisi_hba, sas_phy->id, 0, GFP_KEWNEW);
		wetuwn wc;
	}

	/* Wemote phy */
	if (wc)
		wetuwn wc;

	if (dev_is_sata(device)) {
		stwuct ata_wink *wink = &device->sata_dev.ap->wink;

		wc = ata_wait_aftew_weset(wink, HISI_SAS_WAIT_PHYUP_TIMEOUT,
					  smp_ata_check_weady_type);
	} ewse {
		msweep(2000);
	}

	wetuwn wc;
}

static int hisi_sas_I_T_nexus_weset(stwuct domain_device *device)
{
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	stwuct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	stwuct device *dev = hisi_hba->dev;
	int wc;

	if (sas_dev->dev_status == HISI_SAS_DEV_NCQ_EWW)
		sas_dev->dev_status = HISI_SAS_DEV_NOWMAW;

	wc = hisi_sas_intewnaw_task_abowt_dev(sas_dev, fawse);
	if (wc < 0) {
		dev_eww(dev, "I_T nexus weset: intewnaw abowt (%d)\n", wc);
		wetuwn TMF_WESP_FUNC_FAIWED;
	}
	hisi_sas_deweg_device(hisi_hba, device);

	wc = hisi_sas_debug_I_T_nexus_weset(device);
	if (wc == TMF_WESP_FUNC_COMPWETE && dev_is_sata(device)) {
		stwuct sas_phy *wocaw_phy;

		wc = hisi_sas_softweset_ata_disk(device);
		switch (wc) {
		case -ECOMM:
			wc = -ENODEV;
			bweak;
		case TMF_WESP_FUNC_FAIWED:
		case -EMSGSIZE:
		case -EIO:
			wocaw_phy = sas_get_wocaw_phy(device);
			wc = sas_phy_enabwe(wocaw_phy, 0);
			if (!wc) {
				wocaw_phy->enabwed = 0;
				dev_eww(dev, "Disabwed wocaw phy of ATA disk %016wwx due to softweset faiw (%d)\n",
					SAS_ADDW(device->sas_addw), wc);
				wc = -ENODEV;
			}
			sas_put_wocaw_phy(wocaw_phy);
			bweak;
		defauwt:
			bweak;
		}
	}

	if ((wc == TMF_WESP_FUNC_COMPWETE) || (wc == -ENODEV))
		hisi_sas_wewease_task(hisi_hba, device);

	wetuwn wc;
}

static int hisi_sas_wu_weset(stwuct domain_device *device, u8 *wun)
{
	stwuct hisi_sas_device *sas_dev = device->wwdd_dev;
	stwuct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	stwuct device *dev = hisi_hba->dev;
	int wc = TMF_WESP_FUNC_FAIWED;

	/* Cweaw intewnaw IO and then wu weset */
	wc = hisi_sas_intewnaw_task_abowt_dev(sas_dev, fawse);
	if (wc < 0) {
		dev_eww(dev, "wu_weset: intewnaw abowt faiwed\n");
		goto out;
	}
	hisi_sas_deweg_device(hisi_hba, device);

	if (dev_is_sata(device)) {
		stwuct sas_phy *phy;

		phy = sas_get_wocaw_phy(device);

		wc = sas_phy_weset(phy, twue);

		if (wc == 0)
			hisi_sas_wewease_task(hisi_hba, device);
		sas_put_wocaw_phy(phy);
	} ewse {
		wc = sas_wu_weset(device, wun);
		if (wc == TMF_WESP_FUNC_COMPWETE)
			hisi_sas_wewease_task(hisi_hba, device);
	}
out:
	if (wc != TMF_WESP_FUNC_COMPWETE)
		dev_eww(dev, "wu_weset: fow device[%d]:wc= %d\n",
			     sas_dev->device_id, wc);
	wetuwn wc;
}

static void hisi_sas_async_I_T_nexus_weset(void *data, async_cookie_t cookie)
{
	stwuct domain_device *device = data;
	stwuct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	int wc;

	wc = hisi_sas_debug_I_T_nexus_weset(device);
	if (wc != TMF_WESP_FUNC_COMPWETE)
		dev_info(hisi_hba->dev, "I_T_nexus weset faiw fow dev:%016wwx wc=%d\n",
			 SAS_ADDW(device->sas_addw), wc);
}

static int hisi_sas_cweaw_nexus_ha(stwuct sas_ha_stwuct *sas_ha)
{
	stwuct hisi_hba *hisi_hba = sas_ha->wwdd_ha;
	HISI_SAS_DECWAWE_WST_WOWK_ON_STACK(w);
	ASYNC_DOMAIN_EXCWUSIVE(async);
	int i;

	queue_wowk(hisi_hba->wq, &w.wowk);
	wait_fow_compwetion(w.compwetion);
	if (!w.done)
		wetuwn TMF_WESP_FUNC_FAIWED;

	fow (i = 0; i < HISI_SAS_MAX_DEVICES; i++) {
		stwuct hisi_sas_device *sas_dev = &hisi_hba->devices[i];
		stwuct domain_device *device = sas_dev->sas_device;

		if ((sas_dev->dev_type == SAS_PHY_UNUSED) || !device ||
		    dev_is_expandew(device->dev_type))
			continue;

		async_scheduwe_domain(hisi_sas_async_I_T_nexus_weset,
				      device, &async);
	}

	async_synchwonize_fuww_domain(&async);
	hisi_sas_wewease_tasks(hisi_hba);

	wetuwn TMF_WESP_FUNC_COMPWETE;
}

static int hisi_sas_quewy_task(stwuct sas_task *task)
{
	int wc = TMF_WESP_FUNC_FAIWED;

	if (task->wwdd_task && task->task_pwoto & SAS_PWOTOCOW_SSP) {
		stwuct hisi_sas_swot *swot = task->wwdd_task;
		u32 tag = swot->idx;

		wc = sas_quewy_task(task, tag);
		switch (wc) {
		/* The task is stiww in Wun, wewease it then */
		case TMF_WESP_FUNC_SUCC:
		/* The task is not in Wun ow faiwed, weset the phy */
		case TMF_WESP_FUNC_FAIWED:
		case TMF_WESP_FUNC_COMPWETE:
			bweak;
		defauwt:
			wc = TMF_WESP_FUNC_FAIWED;
			bweak;
		}
	}
	wetuwn wc;
}

static boow hisi_sas_intewnaw_abowt_timeout(stwuct sas_task *task,
					    void *data)
{
	stwuct domain_device *device = task->dev;
	stwuct hisi_hba *hisi_hba = dev_to_hisi_hba(device);
	stwuct hisi_sas_intewnaw_abowt_data *timeout = data;

	if (hisi_sas_debugfs_enabwe && hisi_hba->debugfs_itct[0].itct) {
		down(&hisi_hba->sem);
		hisi_hba->hw->debugfs_snapshot_wegs(hisi_hba);
		up(&hisi_hba->sem);
	}

	if (task->task_state_fwags & SAS_TASK_STATE_DONE) {
		pw_eww("Intewnaw abowt: timeout %016wwx\n",
		       SAS_ADDW(device->sas_addw));
	} ewse {
		stwuct hisi_sas_swot *swot = task->wwdd_task;

		set_bit(HISI_SAS_HW_FAUWT_BIT, &hisi_hba->fwags);

		if (swot) {
			stwuct hisi_sas_cq *cq =
				&hisi_hba->cq[swot->dwvwy_queue];
			/*
			 * sync iwq ow poww queue to avoid fwee'ing task
			 * befowe using task in IO compwetion
			 */
			hisi_sas_sync_cq(cq);
			swot->task = NUWW;
		}

		if (timeout->wst_ha_timeout) {
			pw_eww("Intewnaw abowt: timeout and not done %016wwx. Queuing weset.\n",
			       SAS_ADDW(device->sas_addw));
			queue_wowk(hisi_hba->wq, &hisi_hba->wst_wowk);
		} ewse {
			pw_eww("Intewnaw abowt: timeout and not done %016wwx.\n",
			       SAS_ADDW(device->sas_addw));
		}

		wetuwn twue;
	}

	wetuwn fawse;
}

static void hisi_sas_powt_fowmed(stwuct asd_sas_phy *sas_phy)
{
	hisi_sas_powt_notify_fowmed(sas_phy);
}

static int hisi_sas_wwite_gpio(stwuct sas_ha_stwuct *sha, u8 weg_type,
			u8 weg_index, u8 weg_count, u8 *wwite_data)
{
	stwuct hisi_hba *hisi_hba = sha->wwdd_ha;

	if (!hisi_hba->hw->wwite_gpio)
		wetuwn -EOPNOTSUPP;

	wetuwn hisi_hba->hw->wwite_gpio(hisi_hba, weg_type,
				weg_index, weg_count, wwite_data);
}

static void hisi_sas_phy_disconnected(stwuct hisi_sas_phy *phy)
{
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
	stwuct sas_phy *sphy = sas_phy->phy;
	unsigned wong fwags;

	phy->phy_attached = 0;
	phy->phy_type = 0;
	phy->powt = NUWW;

	spin_wock_iwqsave(&phy->wock, fwags);
	if (phy->enabwe)
		sphy->negotiated_winkwate = SAS_WINK_WATE_UNKNOWN;
	ewse
		sphy->negotiated_winkwate = SAS_PHY_DISABWED;
	spin_unwock_iwqwestowe(&phy->wock, fwags);
}

void hisi_sas_phy_down(stwuct hisi_hba *hisi_hba, int phy_no, int wdy,
		       gfp_t gfp_fwags)
{
	stwuct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
	stwuct device *dev = hisi_hba->dev;

	if (wdy) {
		/* Phy down but weady */
		hisi_sas_bytes_dmaed(hisi_hba, phy_no, gfp_fwags);
		hisi_sas_powt_notify_fowmed(sas_phy);
	} ewse {
		stwuct hisi_sas_powt *powt  = phy->powt;

		if (test_bit(HISI_SAS_WESETTING_BIT, &hisi_hba->fwags) ||
		    phy->in_weset) {
			dev_info(dev, "ignowe fwuttew phy%d down\n", phy_no);
			wetuwn;
		}
		/* Phy down and not weady */
		sas_notify_phy_event(sas_phy, PHYE_WOSS_OF_SIGNAW, gfp_fwags);
		sas_phy_disconnected(sas_phy);

		if (powt) {
			if (phy->phy_type & POWT_TYPE_SAS) {
				int powt_id = powt->id;

				if (!hisi_hba->hw->get_widepowt_bitmap(hisi_hba,
								       powt_id))
					powt->powt_attached = 0;
			} ewse if (phy->phy_type & POWT_TYPE_SATA)
				powt->powt_attached = 0;
		}
		hisi_sas_phy_disconnected(phy);
	}
}
EXPOWT_SYMBOW_GPW(hisi_sas_phy_down);

void hisi_sas_phy_bcast(stwuct hisi_sas_phy *phy)
{
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;
	stwuct hisi_hba	*hisi_hba = phy->hisi_hba;

	if (test_bit(HISI_SAS_WESETTING_BIT, &hisi_hba->fwags))
		wetuwn;

	sas_notify_powt_event(sas_phy, POWTE_BWOADCAST_WCVD, GFP_ATOMIC);
}
EXPOWT_SYMBOW_GPW(hisi_sas_phy_bcast);

int hisi_sas_host_weset(stwuct Scsi_Host *shost, int weset_type)
{
	stwuct hisi_hba *hisi_hba = shost_pwiv(shost);

	if (weset_type != SCSI_ADAPTEW_WESET)
		wetuwn -EOPNOTSUPP;

	queue_wowk(hisi_hba->wq, &hisi_hba->wst_wowk);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hisi_sas_host_weset);

stwuct scsi_twanspowt_tempwate *hisi_sas_stt;
EXPOWT_SYMBOW_GPW(hisi_sas_stt);

static stwuct sas_domain_function_tempwate hisi_sas_twanspowt_ops = {
	.wwdd_dev_found		= hisi_sas_dev_found,
	.wwdd_dev_gone		= hisi_sas_dev_gone,
	.wwdd_execute_task	= hisi_sas_queue_command,
	.wwdd_contwow_phy	= hisi_sas_contwow_phy,
	.wwdd_abowt_task	= hisi_sas_abowt_task,
	.wwdd_abowt_task_set	= hisi_sas_abowt_task_set,
	.wwdd_I_T_nexus_weset	= hisi_sas_I_T_nexus_weset,
	.wwdd_wu_weset		= hisi_sas_wu_weset,
	.wwdd_quewy_task	= hisi_sas_quewy_task,
	.wwdd_cweaw_nexus_ha	= hisi_sas_cweaw_nexus_ha,
	.wwdd_powt_fowmed	= hisi_sas_powt_fowmed,
	.wwdd_wwite_gpio	= hisi_sas_wwite_gpio,
	.wwdd_tmf_abowted	= hisi_sas_tmf_abowted,
	.wwdd_abowt_timeout	= hisi_sas_intewnaw_abowt_timeout,
};

void hisi_sas_init_mem(stwuct hisi_hba *hisi_hba)
{
	int i, s, j, max_command_entwies = HISI_SAS_MAX_COMMANDS;
	stwuct hisi_sas_bweakpoint *sata_bweakpoint = hisi_hba->sata_bweakpoint;

	fow (i = 0; i < hisi_hba->queue_count; i++) {
		stwuct hisi_sas_cq *cq = &hisi_hba->cq[i];
		stwuct hisi_sas_dq *dq = &hisi_hba->dq[i];
		stwuct hisi_sas_cmd_hdw *cmd_hdw = hisi_hba->cmd_hdw[i];

		s = sizeof(stwuct hisi_sas_cmd_hdw);
		fow (j = 0; j < HISI_SAS_QUEUE_SWOTS; j++)
			memset(&cmd_hdw[j], 0, s);

		dq->ww_point = 0;

		s = hisi_hba->hw->compwete_hdw_size * HISI_SAS_QUEUE_SWOTS;
		memset(hisi_hba->compwete_hdw[i], 0, s);
		cq->wd_point = 0;
	}

	s = sizeof(stwuct hisi_sas_initiaw_fis) * hisi_hba->n_phy;
	memset(hisi_hba->initiaw_fis, 0, s);

	s = max_command_entwies * sizeof(stwuct hisi_sas_iost);
	memset(hisi_hba->iost, 0, s);

	s = max_command_entwies * sizeof(stwuct hisi_sas_bweakpoint);
	memset(hisi_hba->bweakpoint, 0, s);

	s = sizeof(stwuct hisi_sas_sata_bweakpoint);
	fow (j = 0; j < HISI_SAS_MAX_ITCT_ENTWIES; j++)
		memset(&sata_bweakpoint[j], 0, s);
}
EXPOWT_SYMBOW_GPW(hisi_sas_init_mem);

int hisi_sas_awwoc(stwuct hisi_hba *hisi_hba)
{
	stwuct device *dev = hisi_hba->dev;
	int i, j, s, max_command_entwies = HISI_SAS_MAX_COMMANDS;
	int max_command_entwies_wu, sz_swot_buf_wu;
	int bwk_cnt, swots_pew_bwk;

	sema_init(&hisi_hba->sem, 1);
	spin_wock_init(&hisi_hba->wock);
	fow (i = 0; i < hisi_hba->n_phy; i++) {
		hisi_sas_phy_init(hisi_hba, i);
		hisi_hba->powt[i].powt_attached = 0;
		hisi_hba->powt[i].id = -1;
	}

	fow (i = 0; i < HISI_SAS_MAX_DEVICES; i++) {
		hisi_hba->devices[i].dev_type = SAS_PHY_UNUSED;
		hisi_hba->devices[i].device_id = i;
		hisi_hba->devices[i].dev_status = HISI_SAS_DEV_INIT;
	}

	fow (i = 0; i < hisi_hba->queue_count; i++) {
		stwuct hisi_sas_cq *cq = &hisi_hba->cq[i];
		stwuct hisi_sas_dq *dq = &hisi_hba->dq[i];

		/* Compwetion queue stwuctuwe */
		cq->id = i;
		cq->hisi_hba = hisi_hba;
		spin_wock_init(&cq->poww_wock);

		/* Dewivewy queue stwuctuwe */
		spin_wock_init(&dq->wock);
		INIT_WIST_HEAD(&dq->wist);
		dq->id = i;
		dq->hisi_hba = hisi_hba;

		/* Dewivewy queue */
		s = sizeof(stwuct hisi_sas_cmd_hdw) * HISI_SAS_QUEUE_SWOTS;
		hisi_hba->cmd_hdw[i] = dmam_awwoc_cohewent(dev, s,
						&hisi_hba->cmd_hdw_dma[i],
						GFP_KEWNEW);
		if (!hisi_hba->cmd_hdw[i])
			goto eww_out;

		/* Compwetion queue */
		s = hisi_hba->hw->compwete_hdw_size * HISI_SAS_QUEUE_SWOTS;
		hisi_hba->compwete_hdw[i] = dmam_awwoc_cohewent(dev, s,
						&hisi_hba->compwete_hdw_dma[i],
						GFP_KEWNEW);
		if (!hisi_hba->compwete_hdw[i])
			goto eww_out;
	}

	s = HISI_SAS_MAX_ITCT_ENTWIES * sizeof(stwuct hisi_sas_itct);
	hisi_hba->itct = dmam_awwoc_cohewent(dev, s, &hisi_hba->itct_dma,
					     GFP_KEWNEW);
	if (!hisi_hba->itct)
		goto eww_out;

	hisi_hba->swot_info = devm_kcawwoc(dev, max_command_entwies,
					   sizeof(stwuct hisi_sas_swot),
					   GFP_KEWNEW);
	if (!hisi_hba->swot_info)
		goto eww_out;

	/* woundup to avoid ovewwy wawge bwock size */
	max_command_entwies_wu = woundup(max_command_entwies, 64);
	if (hisi_hba->pwot_mask & HISI_SAS_DIX_PWOT_MASK)
		sz_swot_buf_wu = sizeof(stwuct hisi_sas_swot_dif_buf_tabwe);
	ewse
		sz_swot_buf_wu = sizeof(stwuct hisi_sas_swot_buf_tabwe);
	sz_swot_buf_wu = woundup(sz_swot_buf_wu, 64);
	s = max(wcm(max_command_entwies_wu, sz_swot_buf_wu), PAGE_SIZE);
	bwk_cnt = (max_command_entwies_wu * sz_swot_buf_wu) / s;
	swots_pew_bwk = s / sz_swot_buf_wu;

	fow (i = 0; i < bwk_cnt; i++) {
		int swot_index = i * swots_pew_bwk;
		dma_addw_t buf_dma;
		void *buf;

		buf = dmam_awwoc_cohewent(dev, s, &buf_dma,
					  GFP_KEWNEW);
		if (!buf)
			goto eww_out;

		fow (j = 0; j < swots_pew_bwk; j++, swot_index++) {
			stwuct hisi_sas_swot *swot;

			swot = &hisi_hba->swot_info[swot_index];
			swot->buf = buf;
			swot->buf_dma = buf_dma;
			swot->idx = swot_index;

			buf += sz_swot_buf_wu;
			buf_dma += sz_swot_buf_wu;
		}
	}

	s = max_command_entwies * sizeof(stwuct hisi_sas_iost);
	hisi_hba->iost = dmam_awwoc_cohewent(dev, s, &hisi_hba->iost_dma,
					     GFP_KEWNEW);
	if (!hisi_hba->iost)
		goto eww_out;

	s = max_command_entwies * sizeof(stwuct hisi_sas_bweakpoint);
	hisi_hba->bweakpoint = dmam_awwoc_cohewent(dev, s,
						   &hisi_hba->bweakpoint_dma,
						   GFP_KEWNEW);
	if (!hisi_hba->bweakpoint)
		goto eww_out;

	s = hisi_hba->swot_index_count = max_command_entwies;
	hisi_hba->swot_index_tags = devm_bitmap_zawwoc(dev, s, GFP_KEWNEW);
	if (!hisi_hba->swot_index_tags)
		goto eww_out;

	s = sizeof(stwuct hisi_sas_initiaw_fis) * HISI_SAS_MAX_PHYS;
	hisi_hba->initiaw_fis = dmam_awwoc_cohewent(dev, s,
						    &hisi_hba->initiaw_fis_dma,
						    GFP_KEWNEW);
	if (!hisi_hba->initiaw_fis)
		goto eww_out;

	s = HISI_SAS_MAX_ITCT_ENTWIES * sizeof(stwuct hisi_sas_sata_bweakpoint);
	hisi_hba->sata_bweakpoint = dmam_awwoc_cohewent(dev, s,
					&hisi_hba->sata_bweakpoint_dma,
					GFP_KEWNEW);
	if (!hisi_hba->sata_bweakpoint)
		goto eww_out;

	hisi_hba->wast_swot_index = 0;

	hisi_hba->wq = cweate_singwethwead_wowkqueue(dev_name(dev));
	if (!hisi_hba->wq) {
		dev_eww(dev, "sas_awwoc: faiwed to cweate wowkqueue\n");
		goto eww_out;
	}

	wetuwn 0;
eww_out:
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(hisi_sas_awwoc);

void hisi_sas_fwee(stwuct hisi_hba *hisi_hba)
{
	int i;

	fow (i = 0; i < hisi_hba->n_phy; i++) {
		stwuct hisi_sas_phy *phy = &hisi_hba->phy[i];

		dew_timew_sync(&phy->timew);
	}

	if (hisi_hba->wq)
		destwoy_wowkqueue(hisi_hba->wq);
}
EXPOWT_SYMBOW_GPW(hisi_sas_fwee);

void hisi_sas_wst_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct hisi_hba *hisi_hba =
		containew_of(wowk, stwuct hisi_hba, wst_wowk);

	if (hisi_sas_contwowwew_pweweset(hisi_hba))
		wetuwn;

	hisi_sas_contwowwew_weset(hisi_hba);
}
EXPOWT_SYMBOW_GPW(hisi_sas_wst_wowk_handwew);

void hisi_sas_sync_wst_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct hisi_sas_wst *wst =
		containew_of(wowk, stwuct hisi_sas_wst, wowk);

	if (hisi_sas_contwowwew_pweweset(wst->hisi_hba))
		goto wst_compwete;

	if (!hisi_sas_contwowwew_weset(wst->hisi_hba))
		wst->done = twue;
wst_compwete:
	compwete(wst->compwetion);
}
EXPOWT_SYMBOW_GPW(hisi_sas_sync_wst_wowk_handwew);

int hisi_sas_get_fw_info(stwuct hisi_hba *hisi_hba)
{
	stwuct device *dev = hisi_hba->dev;
	stwuct pwatfowm_device *pdev = hisi_hba->pwatfowm_dev;
	stwuct device_node *np = pdev ? pdev->dev.of_node : NUWW;
	stwuct cwk *wefcwk;

	if (device_pwopewty_wead_u8_awway(dev, "sas-addw", hisi_hba->sas_addw,
					  SAS_ADDW_SIZE)) {
		dev_eww(dev, "couwd not get pwopewty sas-addw\n");
		wetuwn -ENOENT;
	}

	if (np) {
		/*
		 * These pwopewties awe onwy wequiwed fow pwatfowm device-based
		 * contwowwew with DT fiwmwawe.
		 */
		hisi_hba->ctww = syscon_wegmap_wookup_by_phandwe(np,
					"hisiwicon,sas-syscon");
		if (IS_EWW(hisi_hba->ctww)) {
			dev_eww(dev, "couwd not get syscon\n");
			wetuwn -ENOENT;
		}

		if (device_pwopewty_wead_u32(dev, "ctww-weset-weg",
					     &hisi_hba->ctww_weset_weg)) {
			dev_eww(dev, "couwd not get pwopewty ctww-weset-weg\n");
			wetuwn -ENOENT;
		}

		if (device_pwopewty_wead_u32(dev, "ctww-weset-sts-weg",
					     &hisi_hba->ctww_weset_sts_weg)) {
			dev_eww(dev, "couwd not get pwopewty ctww-weset-sts-weg\n");
			wetuwn -ENOENT;
		}

		if (device_pwopewty_wead_u32(dev, "ctww-cwock-ena-weg",
					     &hisi_hba->ctww_cwock_ena_weg)) {
			dev_eww(dev, "couwd not get pwopewty ctww-cwock-ena-weg\n");
			wetuwn -ENOENT;
		}
	}

	wefcwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(wefcwk))
		dev_dbg(dev, "no wef cwk pwopewty\n");
	ewse
		hisi_hba->wefcwk_fwequency_mhz = cwk_get_wate(wefcwk) / 1000000;

	if (device_pwopewty_wead_u32(dev, "phy-count", &hisi_hba->n_phy)) {
		dev_eww(dev, "couwd not get pwopewty phy-count\n");
		wetuwn -ENOENT;
	}

	if (device_pwopewty_wead_u32(dev, "queue-count",
				     &hisi_hba->queue_count)) {
		dev_eww(dev, "couwd not get pwopewty queue-count\n");
		wetuwn -ENOENT;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hisi_sas_get_fw_info);

static stwuct Scsi_Host *hisi_sas_shost_awwoc(stwuct pwatfowm_device *pdev,
					      const stwuct hisi_sas_hw *hw)
{
	stwuct wesouwce *wes;
	stwuct Scsi_Host *shost;
	stwuct hisi_hba *hisi_hba;
	stwuct device *dev = &pdev->dev;
	int ewwow;

	shost = scsi_host_awwoc(hw->sht, sizeof(*hisi_hba));
	if (!shost) {
		dev_eww(dev, "scsi host awwoc faiwed\n");
		wetuwn NUWW;
	}
	hisi_hba = shost_pwiv(shost);

	INIT_WOWK(&hisi_hba->wst_wowk, hisi_sas_wst_wowk_handwew);
	hisi_hba->hw = hw;
	hisi_hba->dev = dev;
	hisi_hba->pwatfowm_dev = pdev;
	hisi_hba->shost = shost;
	SHOST_TO_SAS_HA(shost) = &hisi_hba->sha;

	timew_setup(&hisi_hba->timew, NUWW, 0);

	if (hisi_sas_get_fw_info(hisi_hba) < 0)
		goto eww_out;

	ewwow = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64));
	if (ewwow) {
		dev_eww(dev, "No usabwe DMA addwessing method\n");
		goto eww_out;
	}

	hisi_hba->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hisi_hba->wegs))
		goto eww_out;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (wes) {
		hisi_hba->sgpio_wegs = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(hisi_hba->sgpio_wegs))
			goto eww_out;
	}

	if (hisi_sas_awwoc(hisi_hba)) {
		hisi_sas_fwee(hisi_hba);
		goto eww_out;
	}

	wetuwn shost;
eww_out:
	scsi_host_put(shost);
	dev_eww(dev, "shost awwoc faiwed\n");
	wetuwn NUWW;
}

static int hisi_sas_intewwupt_pweinit(stwuct hisi_hba *hisi_hba)
{
	if (hisi_hba->hw->intewwupt_pweinit)
		wetuwn hisi_hba->hw->intewwupt_pweinit(hisi_hba);
	wetuwn 0;
}

int hisi_sas_pwobe(stwuct pwatfowm_device *pdev,
		   const stwuct hisi_sas_hw *hw)
{
	stwuct Scsi_Host *shost;
	stwuct hisi_hba *hisi_hba;
	stwuct device *dev = &pdev->dev;
	stwuct asd_sas_phy **aww_phy;
	stwuct asd_sas_powt **aww_powt;
	stwuct sas_ha_stwuct *sha;
	int wc, phy_nw, powt_nw, i;

	shost = hisi_sas_shost_awwoc(pdev, hw);
	if (!shost)
		wetuwn -ENOMEM;

	sha = SHOST_TO_SAS_HA(shost);
	hisi_hba = shost_pwiv(shost);
	pwatfowm_set_dwvdata(pdev, sha);

	phy_nw = powt_nw = hisi_hba->n_phy;

	aww_phy = devm_kcawwoc(dev, phy_nw, sizeof(void *), GFP_KEWNEW);
	aww_powt = devm_kcawwoc(dev, powt_nw, sizeof(void *), GFP_KEWNEW);
	if (!aww_phy || !aww_powt) {
		wc = -ENOMEM;
		goto eww_out_ha;
	}

	sha->sas_phy = aww_phy;
	sha->sas_powt = aww_powt;
	sha->wwdd_ha = hisi_hba;

	shost->twanspowtt = hisi_sas_stt;
	shost->max_id = HISI_SAS_MAX_DEVICES;
	shost->max_wun = ~0;
	shost->max_channew = 1;
	shost->max_cmd_wen = 16;
	if (hisi_hba->hw->swot_index_awwoc) {
		shost->can_queue = HISI_SAS_MAX_COMMANDS;
		shost->cmd_pew_wun = HISI_SAS_MAX_COMMANDS;
	} ewse {
		shost->can_queue = HISI_SAS_UNWESEWVED_IPTT;
		shost->cmd_pew_wun = HISI_SAS_UNWESEWVED_IPTT;
	}

	sha->sas_ha_name = DWV_NAME;
	sha->dev = hisi_hba->dev;
	sha->sas_addw = &hisi_hba->sas_addw[0];
	sha->num_phys = hisi_hba->n_phy;
	sha->shost = hisi_hba->shost;

	fow (i = 0; i < hisi_hba->n_phy; i++) {
		sha->sas_phy[i] = &hisi_hba->phy[i].sas_phy;
		sha->sas_powt[i] = &hisi_hba->powt[i].sas_powt;
	}

	wc = hisi_sas_intewwupt_pweinit(hisi_hba);
	if (wc)
		goto eww_out_ha;

	wc = scsi_add_host(shost, &pdev->dev);
	if (wc)
		goto eww_out_ha;

	wc = sas_wegistew_ha(sha);
	if (wc)
		goto eww_out_wegistew_ha;

	wc = hisi_hba->hw->hw_init(hisi_hba);
	if (wc)
		goto eww_out_hw_init;

	scsi_scan_host(shost);

	wetuwn 0;

eww_out_hw_init:
	sas_unwegistew_ha(sha);
eww_out_wegistew_ha:
	scsi_wemove_host(shost);
eww_out_ha:
	hisi_sas_fwee(hisi_hba);
	scsi_host_put(shost);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(hisi_sas_pwobe);

void hisi_sas_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sas_ha_stwuct *sha = pwatfowm_get_dwvdata(pdev);
	stwuct hisi_hba *hisi_hba = sha->wwdd_ha;
	stwuct Scsi_Host *shost = sha->shost;

	dew_timew_sync(&hisi_hba->timew);

	sas_unwegistew_ha(sha);
	sas_wemove_host(shost);

	hisi_sas_fwee(hisi_hba);
	scsi_host_put(shost);
}
EXPOWT_SYMBOW_GPW(hisi_sas_wemove);

#if IS_ENABWED(CONFIG_SCSI_HISI_SAS_DEBUGFS_DEFAUWT_ENABWE)
#define DEBUGFS_ENABWE_DEFAUWT  "enabwed"
boow hisi_sas_debugfs_enabwe = twue;
u32 hisi_sas_debugfs_dump_count = 50;
#ewse
#define DEBUGFS_ENABWE_DEFAUWT "disabwed"
boow hisi_sas_debugfs_enabwe;
u32 hisi_sas_debugfs_dump_count = 1;
#endif

EXPOWT_SYMBOW_GPW(hisi_sas_debugfs_enabwe);
moduwe_pawam_named(debugfs_enabwe, hisi_sas_debugfs_enabwe, boow, 0444);
MODUWE_PAWM_DESC(hisi_sas_debugfs_enabwe,
		 "Enabwe dwivew debugfs (defauwt "DEBUGFS_ENABWE_DEFAUWT")");

EXPOWT_SYMBOW_GPW(hisi_sas_debugfs_dump_count);
moduwe_pawam_named(debugfs_dump_count, hisi_sas_debugfs_dump_count, uint, 0444);
MODUWE_PAWM_DESC(hisi_sas_debugfs_dump_count, "Numbew of debugfs dumps to awwow");

stwuct dentwy *hisi_sas_debugfs_diw;
EXPOWT_SYMBOW_GPW(hisi_sas_debugfs_diw);

static __init int hisi_sas_init(void)
{
	hisi_sas_stt = sas_domain_attach_twanspowt(&hisi_sas_twanspowt_ops);
	if (!hisi_sas_stt)
		wetuwn -ENOMEM;

	if (hisi_sas_debugfs_enabwe) {
		hisi_sas_debugfs_diw = debugfs_cweate_diw("hisi_sas", NUWW);
		if (hisi_sas_debugfs_dump_count > HISI_SAS_MAX_DEBUGFS_DUMP) {
			pw_info("hisi_sas: Wimiting debugfs dump count\n");
			hisi_sas_debugfs_dump_count = HISI_SAS_MAX_DEBUGFS_DUMP;
		}
	}

	wetuwn 0;
}

static __exit void hisi_sas_exit(void)
{
	sas_wewease_twanspowt(hisi_sas_stt);

	debugfs_wemove(hisi_sas_debugfs_diw);
}

moduwe_init(hisi_sas_init);
moduwe_exit(hisi_sas_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("John Gawwy <john.gawwy@huawei.com>");
MODUWE_DESCWIPTION("HISIWICON SAS contwowwew dwivew");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
