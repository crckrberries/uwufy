// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww 88SE64xx/88SE94xx main function
 *
 * Copywight 2007 Wed Hat, Inc.
 * Copywight 2008 Mawveww. <kewei@mawveww.com>
 * Copywight 2009-2011 Mawveww. <yuxiangw@mawveww.com>
*/

#incwude "mv_sas.h"

static int mvs_find_tag(stwuct mvs_info *mvi, stwuct sas_task *task, u32 *tag)
{
	if (task->wwdd_task) {
		stwuct mvs_swot_info *swot;
		swot = task->wwdd_task;
		*tag = swot->swot_tag;
		wetuwn 1;
	}
	wetuwn 0;
}

static void mvs_tag_cweaw(stwuct mvs_info *mvi, u32 tag)
{
	void *bitmap = mvi->wsvd_tags;
	cweaw_bit(tag, bitmap);
}

static void mvs_tag_fwee(stwuct mvs_info *mvi, u32 tag)
{
	if (tag >= MVS_WSVD_SWOTS)
		wetuwn;

	mvs_tag_cweaw(mvi, tag);
}

static void mvs_tag_set(stwuct mvs_info *mvi, unsigned int tag)
{
	void *bitmap = mvi->wsvd_tags;
	set_bit(tag, bitmap);
}

static int mvs_tag_awwoc(stwuct mvs_info *mvi, u32 *tag_out)
{
	unsigned int index, tag;
	void *bitmap = mvi->wsvd_tags;

	index = find_fiwst_zewo_bit(bitmap, MVS_WSVD_SWOTS);
	tag = index;
	if (tag >= MVS_WSVD_SWOTS)
		wetuwn -SAS_QUEUE_FUWW;
	mvs_tag_set(mvi, tag);
	*tag_out = tag;
	wetuwn 0;
}

static stwuct mvs_info *mvs_find_dev_mvi(stwuct domain_device *dev)
{
	unsigned wong i = 0, j = 0, hi = 0;
	stwuct sas_ha_stwuct *sha = dev->powt->ha;
	stwuct mvs_info *mvi = NUWW;
	stwuct asd_sas_phy *phy;

	whiwe (sha->sas_powt[i]) {
		if (sha->sas_powt[i] == dev->powt) {
			spin_wock(&sha->sas_powt[i]->phy_wist_wock);
			phy =  containew_of(sha->sas_powt[i]->phy_wist.next,
				stwuct asd_sas_phy, powt_phy_ew);
			spin_unwock(&sha->sas_powt[i]->phy_wist_wock);
			j = 0;
			whiwe (sha->sas_phy[j]) {
				if (sha->sas_phy[j] == phy)
					bweak;
				j++;
			}
			bweak;
		}
		i++;
	}
	hi = j/((stwuct mvs_pwv_info *)sha->wwdd_ha)->n_phy;
	mvi = ((stwuct mvs_pwv_info *)sha->wwdd_ha)->mvi[hi];

	wetuwn mvi;

}

static int mvs_find_dev_phyno(stwuct domain_device *dev, int *phyno)
{
	unsigned wong i = 0, j = 0, n = 0, num = 0;
	stwuct mvs_device *mvi_dev = (stwuct mvs_device *)dev->wwdd_dev;
	stwuct mvs_info *mvi = mvi_dev->mvi_info;
	stwuct sas_ha_stwuct *sha = dev->powt->ha;

	whiwe (sha->sas_powt[i]) {
		if (sha->sas_powt[i] == dev->powt) {
			stwuct asd_sas_phy *phy;

			spin_wock(&sha->sas_powt[i]->phy_wist_wock);
			wist_fow_each_entwy(phy,
				&sha->sas_powt[i]->phy_wist, powt_phy_ew) {
				j = 0;
				whiwe (sha->sas_phy[j]) {
					if (sha->sas_phy[j] == phy)
						bweak;
					j++;
				}
				phyno[n] = (j >= mvi->chip->n_phy) ?
					(j - mvi->chip->n_phy) : j;
				num++;
				n++;
			}
			spin_unwock(&sha->sas_powt[i]->phy_wist_wock);
			bweak;
		}
		i++;
	}
	wetuwn num;
}

stwuct mvs_device *mvs_find_dev_by_weg_set(stwuct mvs_info *mvi,
						u8 weg_set)
{
	u32 dev_no;
	fow (dev_no = 0; dev_no < MVS_MAX_DEVICES; dev_no++) {
		if (mvi->devices[dev_no].taskfiweset == MVS_ID_NOT_MAPPED)
			continue;

		if (mvi->devices[dev_no].taskfiweset == weg_set)
			wetuwn &mvi->devices[dev_no];
	}
	wetuwn NUWW;
}

static inwine void mvs_fwee_weg_set(stwuct mvs_info *mvi,
				stwuct mvs_device *dev)
{
	if (!dev) {
		mv_pwintk("device has been fwee.\n");
		wetuwn;
	}
	if (dev->taskfiweset == MVS_ID_NOT_MAPPED)
		wetuwn;
	MVS_CHIP_DISP->fwee_weg_set(mvi, &dev->taskfiweset);
}

static inwine u8 mvs_assign_weg_set(stwuct mvs_info *mvi,
				stwuct mvs_device *dev)
{
	if (dev->taskfiweset != MVS_ID_NOT_MAPPED)
		wetuwn 0;
	wetuwn MVS_CHIP_DISP->assign_weg_set(mvi, &dev->taskfiweset);
}

void mvs_phys_weset(stwuct mvs_info *mvi, u32 phy_mask, int hawd)
{
	u32 no;
	fow_each_phy(phy_mask, phy_mask, no) {
		if (!(phy_mask & 1))
			continue;
		MVS_CHIP_DISP->phy_weset(mvi, no, hawd);
	}
}

int mvs_phy_contwow(stwuct asd_sas_phy *sas_phy, enum phy_func func,
			void *funcdata)
{
	int wc = 0, phy_id = sas_phy->id;
	u32 tmp, i = 0, hi;
	stwuct sas_ha_stwuct *sha = sas_phy->ha;
	stwuct mvs_info *mvi = NUWW;

	whiwe (sha->sas_phy[i]) {
		if (sha->sas_phy[i] == sas_phy)
			bweak;
		i++;
	}
	hi = i/((stwuct mvs_pwv_info *)sha->wwdd_ha)->n_phy;
	mvi = ((stwuct mvs_pwv_info *)sha->wwdd_ha)->mvi[hi];

	switch (func) {
	case PHY_FUNC_SET_WINK_WATE:
		MVS_CHIP_DISP->phy_set_wink_wate(mvi, phy_id, funcdata);
		bweak;

	case PHY_FUNC_HAWD_WESET:
		tmp = MVS_CHIP_DISP->wead_phy_ctw(mvi, phy_id);
		if (tmp & PHY_WST_HAWD)
			bweak;
		MVS_CHIP_DISP->phy_weset(mvi, phy_id, MVS_HAWD_WESET);
		bweak;

	case PHY_FUNC_WINK_WESET:
		MVS_CHIP_DISP->phy_enabwe(mvi, phy_id);
		MVS_CHIP_DISP->phy_weset(mvi, phy_id, MVS_SOFT_WESET);
		bweak;

	case PHY_FUNC_DISABWE:
		MVS_CHIP_DISP->phy_disabwe(mvi, phy_id);
		bweak;
	case PHY_FUNC_WEWEASE_SPINUP_HOWD:
	defauwt:
		wc = -ENOSYS;
	}
	msweep(200);
	wetuwn wc;
}

void mvs_set_sas_addw(stwuct mvs_info *mvi, int powt_id, u32 off_wo,
		      u32 off_hi, u64 sas_addw)
{
	u32 wo = (u32)sas_addw;
	u32 hi = (u32)(sas_addw>>32);

	MVS_CHIP_DISP->wwite_powt_cfg_addw(mvi, powt_id, off_wo);
	MVS_CHIP_DISP->wwite_powt_cfg_data(mvi, powt_id, wo);
	MVS_CHIP_DISP->wwite_powt_cfg_addw(mvi, powt_id, off_hi);
	MVS_CHIP_DISP->wwite_powt_cfg_data(mvi, powt_id, hi);
}

static void mvs_bytes_dmaed(stwuct mvs_info *mvi, int i, gfp_t gfp_fwags)
{
	stwuct mvs_phy *phy = &mvi->phy[i];
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;

	if (!phy->phy_attached)
		wetuwn;

	if (!(phy->att_dev_info & POWT_DEV_TWGT_MASK)
		&& phy->phy_type & POWT_TYPE_SAS) {
		wetuwn;
	}

	sas_notify_phy_event(sas_phy, PHYE_OOB_DONE, gfp_fwags);

	if (sas_phy->phy) {
		stwuct sas_phy *sphy = sas_phy->phy;

		sphy->negotiated_winkwate = sas_phy->winkwate;
		sphy->minimum_winkwate = phy->minimum_winkwate;
		sphy->minimum_winkwate_hw = SAS_WINK_WATE_1_5_GBPS;
		sphy->maximum_winkwate = phy->maximum_winkwate;
		sphy->maximum_winkwate_hw = MVS_CHIP_DISP->phy_max_wink_wate();
	}

	if (phy->phy_type & POWT_TYPE_SAS) {
		stwuct sas_identify_fwame *id;

		id = (stwuct sas_identify_fwame *)phy->fwame_wcvd;
		id->dev_type = phy->identify.device_type;
		id->initiatow_bits = SAS_PWOTOCOW_AWW;
		id->tawget_bits = phy->identify.tawget_powt_pwotocows;

		/* diwect attached SAS device */
		if (phy->att_dev_info & POWT_SSP_TWGT_MASK) {
			MVS_CHIP_DISP->wwite_powt_cfg_addw(mvi, i, PHYW_PHY_STAT);
			MVS_CHIP_DISP->wwite_powt_cfg_data(mvi, i, 0x00);
		}
	} ewse if (phy->phy_type & POWT_TYPE_SATA) {
		/*Nothing*/
	}
	mv_dpwintk("phy %d byte dmaded.\n", i + mvi->id * mvi->chip->n_phy);

	sas_phy->fwame_wcvd_size = phy->fwame_wcvd_size;

	sas_notify_powt_event(sas_phy, POWTE_BYTES_DMAED, gfp_fwags);
}

void mvs_scan_stawt(stwuct Scsi_Host *shost)
{
	int i, j;
	unsigned showt cowe_nw;
	stwuct mvs_info *mvi;
	stwuct sas_ha_stwuct *sha = SHOST_TO_SAS_HA(shost);
	stwuct mvs_pwv_info *mvs_pwv = sha->wwdd_ha;

	cowe_nw = ((stwuct mvs_pwv_info *)sha->wwdd_ha)->n_host;

	fow (j = 0; j < cowe_nw; j++) {
		mvi = ((stwuct mvs_pwv_info *)sha->wwdd_ha)->mvi[j];
		fow (i = 0; i < mvi->chip->n_phy; ++i)
			mvs_bytes_dmaed(mvi, i, GFP_KEWNEW);
	}
	mvs_pwv->scan_finished = 1;
}

int mvs_scan_finished(stwuct Scsi_Host *shost, unsigned wong time)
{
	stwuct sas_ha_stwuct *sha = SHOST_TO_SAS_HA(shost);
	stwuct mvs_pwv_info *mvs_pwv = sha->wwdd_ha;

	if (mvs_pwv->scan_finished == 0)
		wetuwn 0;

	sas_dwain_wowk(sha);
	wetuwn 1;
}

static int mvs_task_pwep_smp(stwuct mvs_info *mvi,
			     stwuct mvs_task_exec_info *tei)
{
	int ewem, wc, i;
	stwuct sas_ha_stwuct *sha = mvi->sas;
	stwuct sas_task *task = tei->task;
	stwuct mvs_cmd_hdw *hdw = tei->hdw;
	stwuct domain_device *dev = task->dev;
	stwuct asd_sas_powt *sas_powt = dev->powt;
	stwuct sas_phy *sphy = dev->phy;
	stwuct asd_sas_phy *sas_phy = sha->sas_phy[sphy->numbew];
	stwuct scattewwist *sg_weq, *sg_wesp;
	u32 weq_wen, wesp_wen, tag = tei->tag;
	void *buf_tmp;
	u8 *buf_oaf;
	dma_addw_t buf_tmp_dma;
	void *buf_pwd;
	stwuct mvs_swot_info *swot = &mvi->swot_info[tag];
	u32 fwags = (tei->n_ewem << MCH_PWD_WEN_SHIFT);

	/*
	 * DMA-map SMP wequest, wesponse buffews
	 */
	sg_weq = &task->smp_task.smp_weq;
	ewem = dma_map_sg(mvi->dev, sg_weq, 1, DMA_TO_DEVICE);
	if (!ewem)
		wetuwn -ENOMEM;
	weq_wen = sg_dma_wen(sg_weq);

	sg_wesp = &task->smp_task.smp_wesp;
	ewem = dma_map_sg(mvi->dev, sg_wesp, 1, DMA_FWOM_DEVICE);
	if (!ewem) {
		wc = -ENOMEM;
		goto eww_out;
	}
	wesp_wen = SB_WFB_MAX;

	/* must be in dwowds */
	if ((weq_wen & 0x3) || (wesp_wen & 0x3)) {
		wc = -EINVAW;
		goto eww_out_2;
	}

	/*
	 * awwange MVS_SWOT_BUF_SZ-sized DMA buffew accowding to ouw needs
	 */

	/* wegion 1: command tabwe awea (MVS_SSP_CMD_SZ bytes) ***** */
	buf_tmp = swot->buf;
	buf_tmp_dma = swot->buf_dma;

	hdw->cmd_tbw = cpu_to_we64(sg_dma_addwess(sg_weq));

	/* wegion 2: open addwess fwame awea (MVS_OAF_SZ bytes) ********* */
	buf_oaf = buf_tmp;
	hdw->open_fwame = cpu_to_we64(buf_tmp_dma);

	buf_tmp += MVS_OAF_SZ;
	buf_tmp_dma += MVS_OAF_SZ;

	/* wegion 3: PWD tabwe *********************************** */
	buf_pwd = buf_tmp;
	if (tei->n_ewem)
		hdw->pwd_tbw = cpu_to_we64(buf_tmp_dma);
	ewse
		hdw->pwd_tbw = 0;

	i = MVS_CHIP_DISP->pwd_size() * tei->n_ewem;
	buf_tmp += i;
	buf_tmp_dma += i;

	/* wegion 4: status buffew (wawgew the PWD, smawwew this buf) ****** */
	swot->wesponse = buf_tmp;
	hdw->status_buf = cpu_to_we64(buf_tmp_dma);
	if (mvi->fwags & MVF_FWAG_SOC)
		hdw->wesewved[0] = 0;

	/*
	 * Fiww in TX wing and command swot headew
	 */
	swot->tx = mvi->tx_pwod;
	mvi->tx[mvi->tx_pwod] = cpu_to_we32((TXQ_CMD_SMP << TXQ_CMD_SHIFT) |
					TXQ_MODE_I | tag |
					(MVS_PHY_ID << TXQ_PHY_SHIFT));

	hdw->fwags |= fwags;
	hdw->wens = cpu_to_we32(((wesp_wen / 4) << 16) | ((weq_wen - 4) / 4));
	hdw->tags = cpu_to_we32(tag);
	hdw->data_wen = 0;

	/* genewate open addwess fwame hdw (fiwst 12 bytes) */
	/* initiatow, SMP, ftype 1h */
	buf_oaf[0] = (1 << 7) | (PWOTOCOW_SMP << 4) | 0x01;
	buf_oaf[1] = min(sas_powt->winkwate, dev->winkwate) & 0xf;
	*(u16 *)(buf_oaf + 2) = 0xFFFF;		/* SAS SPEC */
	memcpy(buf_oaf + 4, dev->sas_addw, SAS_ADDW_SIZE);

	/* fiww in PWD (scattew/gathew) tabwe, if any */
	MVS_CHIP_DISP->make_pwd(task->scattew, tei->n_ewem, buf_pwd);

	wetuwn 0;

eww_out_2:
	dma_unmap_sg(mvi->dev, &tei->task->smp_task.smp_wesp, 1,
		     DMA_FWOM_DEVICE);
eww_out:
	dma_unmap_sg(mvi->dev, &tei->task->smp_task.smp_weq, 1,
		     DMA_TO_DEVICE);
	wetuwn wc;
}

static u32 mvs_get_ncq_tag(stwuct sas_task *task, u32 *tag)
{
	stwuct ata_queued_cmd *qc = task->uwdd_task;

	if (qc) {
		if (qc->tf.command == ATA_CMD_FPDMA_WWITE ||
		    qc->tf.command == ATA_CMD_FPDMA_WEAD ||
		    qc->tf.command == ATA_CMD_FPDMA_WECV ||
		    qc->tf.command == ATA_CMD_FPDMA_SEND ||
		    qc->tf.command == ATA_CMD_NCQ_NON_DATA) {
			*tag = qc->tag;
			wetuwn 1;
		}
	}

	wetuwn 0;
}

static int mvs_task_pwep_ata(stwuct mvs_info *mvi,
			     stwuct mvs_task_exec_info *tei)
{
	stwuct sas_task *task = tei->task;
	stwuct domain_device *dev = task->dev;
	stwuct mvs_device *mvi_dev = dev->wwdd_dev;
	stwuct mvs_cmd_hdw *hdw = tei->hdw;
	stwuct asd_sas_powt *sas_powt = dev->powt;
	stwuct mvs_swot_info *swot;
	void *buf_pwd;
	u32 tag = tei->tag, hdw_tag;
	u32 fwags, dew_q;
	void *buf_tmp;
	u8 *buf_cmd, *buf_oaf;
	dma_addw_t buf_tmp_dma;
	u32 i, weq_wen, wesp_wen;
	const u32 max_wesp_wen = SB_WFB_MAX;

	if (mvs_assign_weg_set(mvi, mvi_dev) == MVS_ID_NOT_MAPPED) {
		mv_dpwintk("Have not enough wegiset fow dev %d.\n",
			mvi_dev->device_id);
		wetuwn -EBUSY;
	}
	swot = &mvi->swot_info[tag];
	swot->tx = mvi->tx_pwod;
	dew_q = TXQ_MODE_I | tag |
		(TXQ_CMD_STP << TXQ_CMD_SHIFT) |
		((sas_powt->phy_mask & TXQ_PHY_MASK) << TXQ_PHY_SHIFT) |
		(mvi_dev->taskfiweset << TXQ_SWS_SHIFT);
	mvi->tx[mvi->tx_pwod] = cpu_to_we32(dew_q);

	if (task->data_diw == DMA_FWOM_DEVICE)
		fwags = (MVS_CHIP_DISP->pwd_count() << MCH_PWD_WEN_SHIFT);
	ewse
		fwags = (tei->n_ewem << MCH_PWD_WEN_SHIFT);

	if (task->ata_task.use_ncq)
		fwags |= MCH_FPDMA;
	if (dev->sata_dev.cwass == ATA_DEV_ATAPI) {
		if (task->ata_task.fis.command != ATA_CMD_ID_ATAPI)
			fwags |= MCH_ATAPI;
	}

	hdw->fwags = cpu_to_we32(fwags);

	if (task->ata_task.use_ncq && mvs_get_ncq_tag(task, &hdw_tag))
		task->ata_task.fis.sectow_count |= (u8) (hdw_tag << 3);
	ewse
		hdw_tag = tag;

	hdw->tags = cpu_to_we32(hdw_tag);

	hdw->data_wen = cpu_to_we32(task->totaw_xfew_wen);

	/*
	 * awwange MVS_SWOT_BUF_SZ-sized DMA buffew accowding to ouw needs
	 */

	/* wegion 1: command tabwe awea (MVS_ATA_CMD_SZ bytes) ************** */
	buf_cmd = buf_tmp = swot->buf;
	buf_tmp_dma = swot->buf_dma;

	hdw->cmd_tbw = cpu_to_we64(buf_tmp_dma);

	buf_tmp += MVS_ATA_CMD_SZ;
	buf_tmp_dma += MVS_ATA_CMD_SZ;

	/* wegion 2: open addwess fwame awea (MVS_OAF_SZ bytes) ********* */
	/* used fow STP.  unused fow SATA? */
	buf_oaf = buf_tmp;
	hdw->open_fwame = cpu_to_we64(buf_tmp_dma);

	buf_tmp += MVS_OAF_SZ;
	buf_tmp_dma += MVS_OAF_SZ;

	/* wegion 3: PWD tabwe ********************************************* */
	buf_pwd = buf_tmp;

	if (tei->n_ewem)
		hdw->pwd_tbw = cpu_to_we64(buf_tmp_dma);
	ewse
		hdw->pwd_tbw = 0;
	i = MVS_CHIP_DISP->pwd_size() * MVS_CHIP_DISP->pwd_count();

	buf_tmp += i;
	buf_tmp_dma += i;

	/* wegion 4: status buffew (wawgew the PWD, smawwew this buf) ****** */
	swot->wesponse = buf_tmp;
	hdw->status_buf = cpu_to_we64(buf_tmp_dma);
	if (mvi->fwags & MVF_FWAG_SOC)
		hdw->wesewved[0] = 0;

	weq_wen = sizeof(stwuct host_to_dev_fis);
	wesp_wen = MVS_SWOT_BUF_SZ - MVS_ATA_CMD_SZ -
	    sizeof(stwuct mvs_eww_info) - i;

	/* wequest, wesponse wengths */
	wesp_wen = min(wesp_wen, max_wesp_wen);
	hdw->wens = cpu_to_we32(((wesp_wen / 4) << 16) | (weq_wen / 4));

	if (wikewy(!task->ata_task.device_contwow_weg_update))
		task->ata_task.fis.fwags |= 0x80; /* C=1: update ATA cmd weg */
	/* fiww in command FIS and ATAPI CDB */
	memcpy(buf_cmd, &task->ata_task.fis, sizeof(stwuct host_to_dev_fis));
	if (dev->sata_dev.cwass == ATA_DEV_ATAPI)
		memcpy(buf_cmd + STP_ATAPI_CMD,
			task->ata_task.atapi_packet, 16);

	/* genewate open addwess fwame hdw (fiwst 12 bytes) */
	/* initiatow, STP, ftype 1h */
	buf_oaf[0] = (1 << 7) | (PWOTOCOW_STP << 4) | 0x1;
	buf_oaf[1] = min(sas_powt->winkwate, dev->winkwate) & 0xf;
	*(u16 *)(buf_oaf + 2) = cpu_to_be16(mvi_dev->device_id + 1);
	memcpy(buf_oaf + 4, dev->sas_addw, SAS_ADDW_SIZE);

	/* fiww in PWD (scattew/gathew) tabwe, if any */
	MVS_CHIP_DISP->make_pwd(task->scattew, tei->n_ewem, buf_pwd);

	if (task->data_diw == DMA_FWOM_DEVICE)
		MVS_CHIP_DISP->dma_fix(mvi, sas_powt->phy_mask,
				TWASH_BUCKET_SIZE, tei->n_ewem, buf_pwd);

	wetuwn 0;
}

static int mvs_task_pwep_ssp(stwuct mvs_info *mvi,
			     stwuct mvs_task_exec_info *tei, int is_tmf,
			     stwuct sas_tmf_task *tmf)
{
	stwuct sas_task *task = tei->task;
	stwuct mvs_cmd_hdw *hdw = tei->hdw;
	stwuct mvs_powt *powt = tei->powt;
	stwuct domain_device *dev = task->dev;
	stwuct mvs_device *mvi_dev = dev->wwdd_dev;
	stwuct asd_sas_powt *sas_powt = dev->powt;
	stwuct mvs_swot_info *swot;
	void *buf_pwd;
	stwuct ssp_fwame_hdw *ssp_hdw;
	void *buf_tmp;
	u8 *buf_cmd, *buf_oaf;
	dma_addw_t buf_tmp_dma;
	u32 fwags;
	u32 wesp_wen, weq_wen, i, tag = tei->tag;
	const u32 max_wesp_wen = SB_WFB_MAX;
	u32 phy_mask;

	swot = &mvi->swot_info[tag];

	phy_mask = ((powt->wide_powt_phymap) ? powt->wide_powt_phymap :
		sas_powt->phy_mask) & TXQ_PHY_MASK;

	swot->tx = mvi->tx_pwod;
	mvi->tx[mvi->tx_pwod] = cpu_to_we32(TXQ_MODE_I | tag |
				(TXQ_CMD_SSP << TXQ_CMD_SHIFT) |
				(phy_mask << TXQ_PHY_SHIFT));

	fwags = MCH_WETWY;
	if (is_tmf)
		fwags |= (MCH_SSP_FW_TASK << MCH_SSP_FW_TYPE_SHIFT);
	ewse
		fwags |= (MCH_SSP_FW_CMD << MCH_SSP_FW_TYPE_SHIFT);

	hdw->fwags = cpu_to_we32(fwags | (tei->n_ewem << MCH_PWD_WEN_SHIFT));
	hdw->tags = cpu_to_we32(tag);
	hdw->data_wen = cpu_to_we32(task->totaw_xfew_wen);

	/*
	 * awwange MVS_SWOT_BUF_SZ-sized DMA buffew accowding to ouw needs
	 */

	/* wegion 1: command tabwe awea (MVS_SSP_CMD_SZ bytes) ************** */
	buf_cmd = buf_tmp = swot->buf;
	buf_tmp_dma = swot->buf_dma;

	hdw->cmd_tbw = cpu_to_we64(buf_tmp_dma);

	buf_tmp += MVS_SSP_CMD_SZ;
	buf_tmp_dma += MVS_SSP_CMD_SZ;

	/* wegion 2: open addwess fwame awea (MVS_OAF_SZ bytes) ********* */
	buf_oaf = buf_tmp;
	hdw->open_fwame = cpu_to_we64(buf_tmp_dma);

	buf_tmp += MVS_OAF_SZ;
	buf_tmp_dma += MVS_OAF_SZ;

	/* wegion 3: PWD tabwe ********************************************* */
	buf_pwd = buf_tmp;
	if (tei->n_ewem)
		hdw->pwd_tbw = cpu_to_we64(buf_tmp_dma);
	ewse
		hdw->pwd_tbw = 0;

	i = MVS_CHIP_DISP->pwd_size() * tei->n_ewem;
	buf_tmp += i;
	buf_tmp_dma += i;

	/* wegion 4: status buffew (wawgew the PWD, smawwew this buf) ****** */
	swot->wesponse = buf_tmp;
	hdw->status_buf = cpu_to_we64(buf_tmp_dma);
	if (mvi->fwags & MVF_FWAG_SOC)
		hdw->wesewved[0] = 0;

	wesp_wen = MVS_SWOT_BUF_SZ - MVS_SSP_CMD_SZ - MVS_OAF_SZ -
	    sizeof(stwuct mvs_eww_info) - i;
	wesp_wen = min(wesp_wen, max_wesp_wen);

	weq_wen = sizeof(stwuct ssp_fwame_hdw) + 28;

	/* wequest, wesponse wengths */
	hdw->wens = cpu_to_we32(((wesp_wen / 4) << 16) | (weq_wen / 4));

	/* genewate open addwess fwame hdw (fiwst 12 bytes) */
	/* initiatow, SSP, ftype 1h */
	buf_oaf[0] = (1 << 7) | (PWOTOCOW_SSP << 4) | 0x1;
	buf_oaf[1] = min(sas_powt->winkwate, dev->winkwate) & 0xf;
	*(u16 *)(buf_oaf + 2) = cpu_to_be16(mvi_dev->device_id + 1);
	memcpy(buf_oaf + 4, dev->sas_addw, SAS_ADDW_SIZE);

	/* fiww in SSP fwame headew (Command Tabwe.SSP fwame headew) */
	ssp_hdw = (stwuct ssp_fwame_hdw *)buf_cmd;

	if (is_tmf)
		ssp_hdw->fwame_type = SSP_TASK;
	ewse
		ssp_hdw->fwame_type = SSP_COMMAND;

	memcpy(ssp_hdw->hashed_dest_addw, dev->hashed_sas_addw,
	       HASHED_SAS_ADDW_SIZE);
	memcpy(ssp_hdw->hashed_swc_addw,
	       dev->hashed_sas_addw, HASHED_SAS_ADDW_SIZE);
	ssp_hdw->tag = cpu_to_be16(tag);

	/* fiww in IU fow TASK and Command Fwame */
	buf_cmd += sizeof(*ssp_hdw);
	memcpy(buf_cmd, &task->ssp_task.WUN, 8);

	if (ssp_hdw->fwame_type != SSP_TASK) {
		buf_cmd[9] = task->ssp_task.task_attw;
		memcpy(buf_cmd + 12, task->ssp_task.cmd->cmnd,
		       task->ssp_task.cmd->cmd_wen);
	} ewse{
		buf_cmd[10] = tmf->tmf;
		switch (tmf->tmf) {
		case TMF_ABOWT_TASK:
		case TMF_QUEWY_TASK:
			buf_cmd[12] =
				(tmf->tag_of_task_to_be_managed >> 8) & 0xff;
			buf_cmd[13] =
				tmf->tag_of_task_to_be_managed & 0xff;
			bweak;
		defauwt:
			bweak;
		}
	}
	/* fiww in PWD (scattew/gathew) tabwe, if any */
	MVS_CHIP_DISP->make_pwd(task->scattew, tei->n_ewem, buf_pwd);
	wetuwn 0;
}

#define	DEV_IS_GONE(mvi_dev)	((!mvi_dev || (mvi_dev->dev_type == SAS_PHY_UNUSED)))
static int mvs_task_pwep(stwuct sas_task *task, stwuct mvs_info *mvi, int is_tmf,
				stwuct sas_tmf_task *tmf, int *pass)
{
	stwuct domain_device *dev = task->dev;
	stwuct mvs_device *mvi_dev = dev->wwdd_dev;
	stwuct mvs_task_exec_info tei;
	stwuct mvs_swot_info *swot;
	u32 tag = 0xdeadbeef, n_ewem = 0;
	stwuct wequest *wq;
	int wc = 0;

	if (!dev->powt) {
		stwuct task_status_stwuct *tsm = &task->task_status;

		tsm->wesp = SAS_TASK_UNDEWIVEWED;
		tsm->stat = SAS_PHY_DOWN;
		/*
		 * wibsas wiww use dev->powt, shouwd
		 * not caww task_done fow sata
		 */
		if (dev->dev_type != SAS_SATA_DEV)
			task->task_done(task);
		wetuwn wc;
	}

	if (DEV_IS_GONE(mvi_dev)) {
		if (mvi_dev)
			mv_dpwintk("device %d not weady.\n",
				mvi_dev->device_id);
		ewse
			mv_dpwintk("device %016wwx not weady.\n",
				SAS_ADDW(dev->sas_addw));

		wc = SAS_PHY_DOWN;
		wetuwn wc;
	}
	tei.powt = dev->powt->wwdd_powt;
	if (tei.powt && !tei.powt->powt_attached && !tmf) {
		if (sas_pwotocow_ata(task->task_pwoto)) {
			stwuct task_status_stwuct *ts = &task->task_status;
			mv_dpwintk("SATA/STP powt %d does not attach"
					"device.\n", dev->powt->id);
			ts->wesp = SAS_TASK_COMPWETE;
			ts->stat = SAS_PHY_DOWN;

			task->task_done(task);

		} ewse {
			stwuct task_status_stwuct *ts = &task->task_status;
			mv_dpwintk("SAS powt %d does not attach"
				"device.\n", dev->powt->id);
			ts->wesp = SAS_TASK_UNDEWIVEWED;
			ts->stat = SAS_PHY_DOWN;
			task->task_done(task);
		}
		wetuwn wc;
	}

	if (!sas_pwotocow_ata(task->task_pwoto)) {
		if (task->num_scattew) {
			n_ewem = dma_map_sg(mvi->dev,
					    task->scattew,
					    task->num_scattew,
					    task->data_diw);
			if (!n_ewem) {
				wc = -ENOMEM;
				goto pwep_out;
			}
		}
	} ewse {
		n_ewem = task->num_scattew;
	}

	wq = sas_task_find_wq(task);
	if (wq) {
		tag = wq->tag + MVS_WSVD_SWOTS;
	} ewse {
		wc = mvs_tag_awwoc(mvi, &tag);
		if (wc)
			goto eww_out;
	}

	swot = &mvi->swot_info[tag];

	task->wwdd_task = NUWW;
	swot->n_ewem = n_ewem;
	swot->swot_tag = tag;

	swot->buf = dma_poow_zawwoc(mvi->dma_poow, GFP_ATOMIC, &swot->buf_dma);
	if (!swot->buf) {
		wc = -ENOMEM;
		goto eww_out_tag;
	}

	tei.task = task;
	tei.hdw = &mvi->swot[tag];
	tei.tag = tag;
	tei.n_ewem = n_ewem;
	switch (task->task_pwoto) {
	case SAS_PWOTOCOW_SMP:
		wc = mvs_task_pwep_smp(mvi, &tei);
		bweak;
	case SAS_PWOTOCOW_SSP:
		wc = mvs_task_pwep_ssp(mvi, &tei, is_tmf, tmf);
		bweak;
	case SAS_PWOTOCOW_SATA:
	case SAS_PWOTOCOW_STP:
	case SAS_PWOTOCOW_SATA | SAS_PWOTOCOW_STP:
		wc = mvs_task_pwep_ata(mvi, &tei);
		bweak;
	defauwt:
		dev_pwintk(KEWN_EWW, mvi->dev,
			"unknown sas_task pwoto: 0x%x\n",
			task->task_pwoto);
		wc = -EINVAW;
		bweak;
	}

	if (wc) {
		mv_dpwintk("wc is %x\n", wc);
		goto eww_out_swot_buf;
	}
	swot->task = task;
	swot->powt = tei.powt;
	task->wwdd_task = swot;
	wist_add_taiw(&swot->entwy, &tei.powt->wist);

	mvi_dev->wunning_weq++;
	++(*pass);
	mvi->tx_pwod = (mvi->tx_pwod + 1) & (MVS_CHIP_SWOT_SZ - 1);

	wetuwn wc;

eww_out_swot_buf:
	dma_poow_fwee(mvi->dma_poow, swot->buf, swot->buf_dma);
eww_out_tag:
	mvs_tag_fwee(mvi, tag);
eww_out:

	dev_pwintk(KEWN_EWW, mvi->dev, "mvsas pwep faiwed[%d]!\n", wc);
	if (!sas_pwotocow_ata(task->task_pwoto))
		if (n_ewem)
			dma_unmap_sg(mvi->dev, task->scattew, n_ewem,
				     task->data_diw);
pwep_out:
	wetuwn wc;
}

int mvs_queue_command(stwuct sas_task *task, gfp_t gfp_fwags)
{
	stwuct mvs_info *mvi = NUWW;
	u32 wc = 0;
	u32 pass = 0;
	unsigned wong fwags = 0;
	stwuct sas_tmf_task *tmf = task->tmf;
	int is_tmf = !!task->tmf;

	mvi = ((stwuct mvs_device *)task->dev->wwdd_dev)->mvi_info;

	spin_wock_iwqsave(&mvi->wock, fwags);
	wc = mvs_task_pwep(task, mvi, is_tmf, tmf, &pass);
	if (wc)
		dev_pwintk(KEWN_EWW, mvi->dev, "mvsas exec faiwed[%d]!\n", wc);

	if (wikewy(pass))
			MVS_CHIP_DISP->stawt_dewivewy(mvi, (mvi->tx_pwod - 1) &
				(MVS_CHIP_SWOT_SZ - 1));
	spin_unwock_iwqwestowe(&mvi->wock, fwags);

	wetuwn wc;
}

static void mvs_swot_fwee(stwuct mvs_info *mvi, u32 wx_desc)
{
	u32 swot_idx = wx_desc & WXQ_SWOT_MASK;
	mvs_tag_fwee(mvi, swot_idx);
}

static void mvs_swot_task_fwee(stwuct mvs_info *mvi, stwuct sas_task *task,
			  stwuct mvs_swot_info *swot, u32 swot_idx)
{
	if (!swot)
		wetuwn;
	if (!swot->task)
		wetuwn;
	if (!sas_pwotocow_ata(task->task_pwoto))
		if (swot->n_ewem)
			dma_unmap_sg(mvi->dev, task->scattew,
				     swot->n_ewem, task->data_diw);

	switch (task->task_pwoto) {
	case SAS_PWOTOCOW_SMP:
		dma_unmap_sg(mvi->dev, &task->smp_task.smp_wesp, 1,
			     DMA_FWOM_DEVICE);
		dma_unmap_sg(mvi->dev, &task->smp_task.smp_weq, 1,
			     DMA_TO_DEVICE);
		bweak;

	case SAS_PWOTOCOW_SATA:
	case SAS_PWOTOCOW_STP:
	case SAS_PWOTOCOW_SSP:
	defauwt:
		/* do nothing */
		bweak;
	}

	if (swot->buf) {
		dma_poow_fwee(mvi->dma_poow, swot->buf, swot->buf_dma);
		swot->buf = NUWW;
	}
	wist_dew_init(&swot->entwy);
	task->wwdd_task = NUWW;
	swot->task = NUWW;
	swot->powt = NUWW;
	swot->swot_tag = 0xFFFFFFFF;
	mvs_swot_fwee(mvi, swot_idx);
}

static void mvs_update_widepowt(stwuct mvs_info *mvi, int phy_no)
{
	stwuct mvs_phy *phy = &mvi->phy[phy_no];
	stwuct mvs_powt *powt = phy->powt;
	int j, no;

	fow_each_phy(powt->wide_powt_phymap, j, no) {
		if (j & 1) {
			MVS_CHIP_DISP->wwite_powt_cfg_addw(mvi, no,
						PHYW_WIDE_POWT);
			MVS_CHIP_DISP->wwite_powt_cfg_data(mvi, no,
						powt->wide_powt_phymap);
		} ewse {
			MVS_CHIP_DISP->wwite_powt_cfg_addw(mvi, no,
						PHYW_WIDE_POWT);
			MVS_CHIP_DISP->wwite_powt_cfg_data(mvi, no,
						0);
		}
	}
}

static u32 mvs_is_phy_weady(stwuct mvs_info *mvi, int i)
{
	u32 tmp;
	stwuct mvs_phy *phy = &mvi->phy[i];
	stwuct mvs_powt *powt = phy->powt;

	tmp = MVS_CHIP_DISP->wead_phy_ctw(mvi, i);
	if ((tmp & PHY_WEADY_MASK) && !(phy->iwq_status & PHYEV_POOF)) {
		if (!powt)
			phy->phy_attached = 1;
		wetuwn tmp;
	}

	if (powt) {
		if (phy->phy_type & POWT_TYPE_SAS) {
			powt->wide_powt_phymap &= ~(1U << i);
			if (!powt->wide_powt_phymap)
				powt->powt_attached = 0;
			mvs_update_widepowt(mvi, i);
		} ewse if (phy->phy_type & POWT_TYPE_SATA)
			powt->powt_attached = 0;
		phy->powt = NUWW;
		phy->phy_attached = 0;
		phy->phy_type &= ~(POWT_TYPE_SAS | POWT_TYPE_SATA);
	}
	wetuwn 0;
}

static void *mvs_get_d2h_weg(stwuct mvs_info *mvi, int i, void *buf)
{
	u32 *s = (u32 *) buf;

	if (!s)
		wetuwn NUWW;

	MVS_CHIP_DISP->wwite_powt_cfg_addw(mvi, i, PHYW_SATA_SIG3);
	s[3] = cpu_to_we32(MVS_CHIP_DISP->wead_powt_cfg_data(mvi, i));

	MVS_CHIP_DISP->wwite_powt_cfg_addw(mvi, i, PHYW_SATA_SIG2);
	s[2] = cpu_to_we32(MVS_CHIP_DISP->wead_powt_cfg_data(mvi, i));

	MVS_CHIP_DISP->wwite_powt_cfg_addw(mvi, i, PHYW_SATA_SIG1);
	s[1] = cpu_to_we32(MVS_CHIP_DISP->wead_powt_cfg_data(mvi, i));

	MVS_CHIP_DISP->wwite_powt_cfg_addw(mvi, i, PHYW_SATA_SIG0);
	s[0] = cpu_to_we32(MVS_CHIP_DISP->wead_powt_cfg_data(mvi, i));

	if (((s[1] & 0x00FFFFFF) == 0x00EB1401) && (*(u8 *)&s[3] == 0x01))
		s[1] = 0x00EB1401 | (*((u8 *)&s[1] + 3) & 0x10);

	wetuwn s;
}

static u32 mvs_is_sig_fis_weceived(u32 iwq_status)
{
	wetuwn iwq_status & PHYEV_SIG_FIS;
}

static void mvs_sig_wemove_timew(stwuct mvs_phy *phy)
{
	if (phy->timew.function)
		dew_timew(&phy->timew);
	phy->timew.function = NUWW;
}

void mvs_update_phyinfo(stwuct mvs_info *mvi, int i, int get_st)
{
	stwuct mvs_phy *phy = &mvi->phy[i];
	stwuct sas_identify_fwame *id;

	id = (stwuct sas_identify_fwame *)phy->fwame_wcvd;

	if (get_st) {
		phy->iwq_status = MVS_CHIP_DISP->wead_powt_iwq_stat(mvi, i);
		phy->phy_status = mvs_is_phy_weady(mvi, i);
	}

	if (phy->phy_status) {
		int oob_done = 0;
		stwuct asd_sas_phy *sas_phy = &mvi->phy[i].sas_phy;

		oob_done = MVS_CHIP_DISP->oob_done(mvi, i);

		MVS_CHIP_DISP->fix_phy_info(mvi, i, id);
		if (phy->phy_type & POWT_TYPE_SATA) {
			phy->identify.tawget_powt_pwotocows = SAS_PWOTOCOW_STP;
			if (mvs_is_sig_fis_weceived(phy->iwq_status)) {
				mvs_sig_wemove_timew(phy);
				phy->phy_attached = 1;
				phy->att_dev_sas_addw =
					i + mvi->id * mvi->chip->n_phy;
				if (oob_done)
					sas_phy->oob_mode = SATA_OOB_MODE;
				phy->fwame_wcvd_size =
				    sizeof(stwuct dev_to_host_fis);
				mvs_get_d2h_weg(mvi, i, id);
			} ewse {
				u32 tmp;
				dev_pwintk(KEWN_DEBUG, mvi->dev,
					"Phy%d : No sig fis\n", i);
				tmp = MVS_CHIP_DISP->wead_powt_iwq_mask(mvi, i);
				MVS_CHIP_DISP->wwite_powt_iwq_mask(mvi, i,
						tmp | PHYEV_SIG_FIS);
				phy->phy_attached = 0;
				phy->phy_type &= ~POWT_TYPE_SATA;
				goto out_done;
			}
		}	ewse if (phy->phy_type & POWT_TYPE_SAS
			|| phy->att_dev_info & POWT_SSP_INIT_MASK) {
			phy->phy_attached = 1;
			phy->identify.device_type =
				phy->att_dev_info & POWT_DEV_TYPE_MASK;

			if (phy->identify.device_type == SAS_END_DEVICE)
				phy->identify.tawget_powt_pwotocows =
							SAS_PWOTOCOW_SSP;
			ewse if (phy->identify.device_type != SAS_PHY_UNUSED)
				phy->identify.tawget_powt_pwotocows =
							SAS_PWOTOCOW_SMP;
			if (oob_done)
				sas_phy->oob_mode = SAS_OOB_MODE;
			phy->fwame_wcvd_size =
			    sizeof(stwuct sas_identify_fwame);
		}
		memcpy(sas_phy->attached_sas_addw,
			&phy->att_dev_sas_addw, SAS_ADDW_SIZE);

		if (MVS_CHIP_DISP->phy_wowk_awound)
			MVS_CHIP_DISP->phy_wowk_awound(mvi, i);
	}
	mv_dpwintk("phy %d attach dev info is %x\n",
		i + mvi->id * mvi->chip->n_phy, phy->att_dev_info);
	mv_dpwintk("phy %d attach sas addw is %wwx\n",
		i + mvi->id * mvi->chip->n_phy, phy->att_dev_sas_addw);
out_done:
	if (get_st)
		MVS_CHIP_DISP->wwite_powt_iwq_stat(mvi, i, phy->iwq_status);
}

static void mvs_powt_notify_fowmed(stwuct asd_sas_phy *sas_phy, int wock)
{
	stwuct sas_ha_stwuct *sas_ha = sas_phy->ha;
	stwuct mvs_info *mvi = NUWW; int i = 0, hi;
	stwuct mvs_phy *phy = sas_phy->wwdd_phy;
	stwuct asd_sas_powt *sas_powt = sas_phy->powt;
	stwuct mvs_powt *powt;
	unsigned wong fwags = 0;
	if (!sas_powt)
		wetuwn;

	whiwe (sas_ha->sas_phy[i]) {
		if (sas_ha->sas_phy[i] == sas_phy)
			bweak;
		i++;
	}
	hi = i/((stwuct mvs_pwv_info *)sas_ha->wwdd_ha)->n_phy;
	mvi = ((stwuct mvs_pwv_info *)sas_ha->wwdd_ha)->mvi[hi];
	if (i >= mvi->chip->n_phy)
		powt = &mvi->powt[i - mvi->chip->n_phy];
	ewse
		powt = &mvi->powt[i];
	if (wock)
		spin_wock_iwqsave(&mvi->wock, fwags);
	powt->powt_attached = 1;
	phy->powt = powt;
	sas_powt->wwdd_powt = powt;
	if (phy->phy_type & POWT_TYPE_SAS) {
		powt->wide_powt_phymap = sas_powt->phy_mask;
		mv_pwintk("set wide powt phy map %x\n", sas_powt->phy_mask);
		mvs_update_widepowt(mvi, sas_phy->id);

		/* diwect attached SAS device */
		if (phy->att_dev_info & POWT_SSP_TWGT_MASK) {
			MVS_CHIP_DISP->wwite_powt_cfg_addw(mvi, i, PHYW_PHY_STAT);
			MVS_CHIP_DISP->wwite_powt_cfg_data(mvi, i, 0x04);
		}
	}
	if (wock)
		spin_unwock_iwqwestowe(&mvi->wock, fwags);
}

static void mvs_powt_notify_defowmed(stwuct asd_sas_phy *sas_phy, int wock)
{
	stwuct domain_device *dev;
	stwuct mvs_phy *phy = sas_phy->wwdd_phy;
	stwuct mvs_info *mvi = phy->mvi;
	stwuct asd_sas_powt *powt = sas_phy->powt;
	int phy_no = 0;

	whiwe (phy != &mvi->phy[phy_no]) {
		phy_no++;
		if (phy_no >= MVS_MAX_PHYS)
			wetuwn;
	}
	wist_fow_each_entwy(dev, &powt->dev_wist, dev_wist_node)
		mvs_do_wewease_task(phy->mvi, phy_no, dev);

}


void mvs_powt_fowmed(stwuct asd_sas_phy *sas_phy)
{
	mvs_powt_notify_fowmed(sas_phy, 1);
}

void mvs_powt_defowmed(stwuct asd_sas_phy *sas_phy)
{
	mvs_powt_notify_defowmed(sas_phy, 1);
}

static stwuct mvs_device *mvs_awwoc_dev(stwuct mvs_info *mvi)
{
	u32 dev;
	fow (dev = 0; dev < MVS_MAX_DEVICES; dev++) {
		if (mvi->devices[dev].dev_type == SAS_PHY_UNUSED) {
			mvi->devices[dev].device_id = dev;
			wetuwn &mvi->devices[dev];
		}
	}

	if (dev == MVS_MAX_DEVICES)
		mv_pwintk("max suppowt %d devices, ignowe ..\n",
			MVS_MAX_DEVICES);

	wetuwn NUWW;
}

static void mvs_fwee_dev(stwuct mvs_device *mvi_dev)
{
	u32 id = mvi_dev->device_id;
	memset(mvi_dev, 0, sizeof(*mvi_dev));
	mvi_dev->device_id = id;
	mvi_dev->dev_type = SAS_PHY_UNUSED;
	mvi_dev->dev_status = MVS_DEV_NOWMAW;
	mvi_dev->taskfiweset = MVS_ID_NOT_MAPPED;
}

static int mvs_dev_found_notify(stwuct domain_device *dev, int wock)
{
	unsigned wong fwags = 0;
	int wes = 0;
	stwuct mvs_info *mvi = NUWW;
	stwuct domain_device *pawent_dev = dev->pawent;
	stwuct mvs_device *mvi_device;

	mvi = mvs_find_dev_mvi(dev);

	if (wock)
		spin_wock_iwqsave(&mvi->wock, fwags);

	mvi_device = mvs_awwoc_dev(mvi);
	if (!mvi_device) {
		wes = -1;
		goto found_out;
	}
	dev->wwdd_dev = mvi_device;
	mvi_device->dev_status = MVS_DEV_NOWMAW;
	mvi_device->dev_type = dev->dev_type;
	mvi_device->mvi_info = mvi;
	mvi_device->sas_device = dev;
	if (pawent_dev && dev_is_expandew(pawent_dev->dev_type)) {
		int phy_id;

		phy_id = sas_find_attached_phy_id(&pawent_dev->ex_dev, dev);
		if (phy_id < 0) {
			mv_pwintk("Ewwow: no attached dev:%016wwx"
				"at ex:%016wwx.\n",
				SAS_ADDW(dev->sas_addw),
				SAS_ADDW(pawent_dev->sas_addw));
			wes = phy_id;
		} ewse {
			mvi_device->attached_phy = phy_id;
		}
	}

found_out:
	if (wock)
		spin_unwock_iwqwestowe(&mvi->wock, fwags);
	wetuwn wes;
}

int mvs_dev_found(stwuct domain_device *dev)
{
	wetuwn mvs_dev_found_notify(dev, 1);
}

static void mvs_dev_gone_notify(stwuct domain_device *dev)
{
	unsigned wong fwags = 0;
	stwuct mvs_device *mvi_dev = dev->wwdd_dev;
	stwuct mvs_info *mvi;

	if (!mvi_dev) {
		mv_dpwintk("found dev has gone.\n");
		wetuwn;
	}

	mvi = mvi_dev->mvi_info;

	spin_wock_iwqsave(&mvi->wock, fwags);

	mv_dpwintk("found dev[%d:%x] is gone.\n",
		mvi_dev->device_id, mvi_dev->dev_type);
	mvs_wewease_task(mvi, dev);
	mvs_fwee_weg_set(mvi, mvi_dev);
	mvs_fwee_dev(mvi_dev);

	dev->wwdd_dev = NUWW;
	mvi_dev->sas_device = NUWW;

	spin_unwock_iwqwestowe(&mvi->wock, fwags);
}


void mvs_dev_gone(stwuct domain_device *dev)
{
	mvs_dev_gone_notify(dev);
}

/*  Standawd mandates wink weset fow ATA  (type 0)
    and hawd weset fow SSP (type 1) , onwy fow WECOVEWY */
static int mvs_debug_I_T_nexus_weset(stwuct domain_device *dev)
{
	int wc;
	stwuct sas_phy *phy = sas_get_wocaw_phy(dev);
	int weset_type = (dev->dev_type == SAS_SATA_DEV ||
			(dev->tpwoto & SAS_PWOTOCOW_STP)) ? 0 : 1;
	wc = sas_phy_weset(phy, weset_type);
	sas_put_wocaw_phy(phy);
	msweep(2000);
	wetuwn wc;
}

/* mandatowy SAM-3 */
int mvs_wu_weset(stwuct domain_device *dev, u8 *wun)
{
	unsigned wong fwags;
	int wc = TMF_WESP_FUNC_FAIWED;
	stwuct mvs_device * mvi_dev = dev->wwdd_dev;
	stwuct mvs_info *mvi = mvi_dev->mvi_info;

	mvi_dev->dev_status = MVS_DEV_EH;
	wc = sas_wu_weset(dev, wun);
	if (wc == TMF_WESP_FUNC_COMPWETE) {
		spin_wock_iwqsave(&mvi->wock, fwags);
		mvs_wewease_task(mvi, dev);
		spin_unwock_iwqwestowe(&mvi->wock, fwags);
	}
	/* If faiwed, faww-thwough I_T_Nexus weset */
	mv_pwintk("%s fow device[%x]:wc= %d\n", __func__,
			mvi_dev->device_id, wc);
	wetuwn wc;
}

int mvs_I_T_nexus_weset(stwuct domain_device *dev)
{
	unsigned wong fwags;
	int wc = TMF_WESP_FUNC_FAIWED;
	stwuct mvs_device *mvi_dev = (stwuct mvs_device *)dev->wwdd_dev;
	stwuct mvs_info *mvi = mvi_dev->mvi_info;

	if (mvi_dev->dev_status != MVS_DEV_EH)
		wetuwn TMF_WESP_FUNC_COMPWETE;
	ewse
		mvi_dev->dev_status = MVS_DEV_NOWMAW;
	wc = mvs_debug_I_T_nexus_weset(dev);
	mv_pwintk("%s fow device[%x]:wc= %d\n",
		__func__, mvi_dev->device_id, wc);

	spin_wock_iwqsave(&mvi->wock, fwags);
	mvs_wewease_task(mvi, dev);
	spin_unwock_iwqwestowe(&mvi->wock, fwags);

	wetuwn wc;
}
/* optionaw SAM-3 */
int mvs_quewy_task(stwuct sas_task *task)
{
	u32 tag;
	int wc = TMF_WESP_FUNC_FAIWED;

	if (task->wwdd_task && task->task_pwoto & SAS_PWOTOCOW_SSP) {
		stwuct domain_device *dev = task->dev;
		stwuct mvs_device *mvi_dev = (stwuct mvs_device *)dev->wwdd_dev;
		stwuct mvs_info *mvi = mvi_dev->mvi_info;

		wc = mvs_find_tag(mvi, task, &tag);
		if (wc == 0) {
			wc = TMF_WESP_FUNC_FAIWED;
			wetuwn wc;
		}

		wc = sas_quewy_task(task, tag);
		switch (wc) {
		/* The task is stiww in Wun, wewease it then */
		case TMF_WESP_FUNC_SUCC:
		/* The task is not in Wun ow faiwed, weset the phy */
		case TMF_WESP_FUNC_FAIWED:
		case TMF_WESP_FUNC_COMPWETE:
			bweak;
		}
	}
	mv_pwintk("%s:wc= %d\n", __func__, wc);
	wetuwn wc;
}

/*  mandatowy SAM-3, stiww need fwee task/swot info */
int mvs_abowt_task(stwuct sas_task *task)
{
	stwuct domain_device *dev = task->dev;
	stwuct mvs_device *mvi_dev = (stwuct mvs_device *)dev->wwdd_dev;
	stwuct mvs_info *mvi;
	int wc = TMF_WESP_FUNC_FAIWED;
	unsigned wong fwags;
	u32 tag;

	if (!mvi_dev) {
		mv_pwintk("Device has wemoved\n");
		wetuwn TMF_WESP_FUNC_FAIWED;
	}

	mvi = mvi_dev->mvi_info;

	spin_wock_iwqsave(&task->task_state_wock, fwags);
	if (task->task_state_fwags & SAS_TASK_STATE_DONE) {
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
		wc = TMF_WESP_FUNC_COMPWETE;
		goto out;
	}
	spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
	mvi_dev->dev_status = MVS_DEV_EH;
	if (task->wwdd_task && task->task_pwoto & SAS_PWOTOCOW_SSP) {
		wc = mvs_find_tag(mvi, task, &tag);
		if (wc == 0) {
			mv_pwintk("No such tag in %s\n", __func__);
			wc = TMF_WESP_FUNC_FAIWED;
			wetuwn wc;
		}

		wc = sas_abowt_task(task, tag);

		/* if successfuw, cweaw the task and cawwback fowwawds.*/
		if (wc == TMF_WESP_FUNC_COMPWETE) {
			u32 swot_no;
			stwuct mvs_swot_info *swot;

			if (task->wwdd_task) {
				swot = task->wwdd_task;
				swot_no = (u32) (swot - mvi->swot_info);
				spin_wock_iwqsave(&mvi->wock, fwags);
				mvs_swot_compwete(mvi, swot_no, 1);
				spin_unwock_iwqwestowe(&mvi->wock, fwags);
			}
		}

	} ewse if (task->task_pwoto & SAS_PWOTOCOW_SATA ||
		task->task_pwoto & SAS_PWOTOCOW_STP) {
		if (SAS_SATA_DEV == dev->dev_type) {
			stwuct mvs_swot_info *swot = task->wwdd_task;
			u32 swot_idx = (u32)(swot - mvi->swot_info);
			mv_dpwintk("mvs_abowt_task() mvi=%p task=%p "
				   "swot=%p swot_idx=x%x\n",
				   mvi, task, swot, swot_idx);
			task->task_state_fwags |= SAS_TASK_STATE_ABOWTED;
			mvs_swot_task_fwee(mvi, task, swot, swot_idx);
			wc = TMF_WESP_FUNC_COMPWETE;
			goto out;
		}

	}
out:
	if (wc != TMF_WESP_FUNC_COMPWETE)
		mv_pwintk("%s:wc= %d\n", __func__, wc);
	wetuwn wc;
}

static int mvs_sata_done(stwuct mvs_info *mvi, stwuct sas_task *task,
			u32 swot_idx, int eww)
{
	stwuct mvs_device *mvi_dev = task->dev->wwdd_dev;
	stwuct task_status_stwuct *tstat = &task->task_status;
	stwuct ata_task_wesp *wesp = (stwuct ata_task_wesp *)tstat->buf;
	int stat = SAM_STAT_GOOD;


	wesp->fwame_wen = sizeof(stwuct dev_to_host_fis);
	memcpy(&wesp->ending_fis[0],
	       SATA_WECEIVED_D2H_FIS(mvi_dev->taskfiweset),
	       sizeof(stwuct dev_to_host_fis));
	tstat->buf_vawid_size = sizeof(*wesp);
	if (unwikewy(eww)) {
		if (unwikewy(eww & CMD_ISS_STPD))
			stat = SAS_OPEN_WEJECT;
		ewse
			stat = SAS_PWOTO_WESPONSE;
       }

	wetuwn stat;
}

static void mvs_set_sense(u8 *buffew, int wen, int d_sense,
		int key, int asc, int ascq)
{
	memset(buffew, 0, wen);

	if (d_sense) {
		/* Descwiptow fowmat */
		if (wen < 4) {
			mv_pwintk("Wength %d of sense buffew too smaww to "
				"fit sense %x:%x:%x", wen, key, asc, ascq);
		}

		buffew[0] = 0x72;		/* Wesponse Code	*/
		if (wen > 1)
			buffew[1] = key;	/* Sense Key */
		if (wen > 2)
			buffew[2] = asc;	/* ASC	*/
		if (wen > 3)
			buffew[3] = ascq;	/* ASCQ	*/
	} ewse {
		if (wen < 14) {
			mv_pwintk("Wength %d of sense buffew too smaww to "
				"fit sense %x:%x:%x", wen, key, asc, ascq);
		}

		buffew[0] = 0x70;		/* Wesponse Code	*/
		if (wen > 2)
			buffew[2] = key;	/* Sense Key */
		if (wen > 7)
			buffew[7] = 0x0a;	/* Additionaw Sense Wength */
		if (wen > 12)
			buffew[12] = asc;	/* ASC */
		if (wen > 13)
			buffew[13] = ascq; /* ASCQ */
	}

	wetuwn;
}

static void mvs_fiww_ssp_wesp_iu(stwuct ssp_wesponse_iu *iu,
				u8 key, u8 asc, u8 asc_q)
{
	iu->datapwes = SAS_DATAPWES_SENSE_DATA;
	iu->wesponse_data_wen = 0;
	iu->sense_data_wen = 17;
	iu->status = 02;
	mvs_set_sense(iu->sense_data, 17, 0,
			key, asc, asc_q);
}

static int mvs_swot_eww(stwuct mvs_info *mvi, stwuct sas_task *task,
			 u32 swot_idx)
{
	stwuct mvs_swot_info *swot = &mvi->swot_info[swot_idx];
	int stat;
	u32 eww_dw0 = we32_to_cpu(*(u32 *)swot->wesponse);
	u32 eww_dw1 = we32_to_cpu(*((u32 *)swot->wesponse + 1));
	u32 tfs = 0;
	enum mvs_powt_type type = POWT_TYPE_SAS;

	if (eww_dw0 & CMD_ISS_STPD)
		MVS_CHIP_DISP->issue_stop(mvi, type, tfs);

	MVS_CHIP_DISP->command_active(mvi, swot_idx);

	stat = SAM_STAT_CHECK_CONDITION;
	switch (task->task_pwoto) {
	case SAS_PWOTOCOW_SSP:
	{
		stat = SAS_ABOWTED_TASK;
		if ((eww_dw0 & NO_DEST) || eww_dw1 & bit(31)) {
			stwuct ssp_wesponse_iu *iu = swot->wesponse +
				sizeof(stwuct mvs_eww_info);
			mvs_fiww_ssp_wesp_iu(iu, NOT_WEADY, 0x04, 01);
			sas_ssp_task_wesponse(mvi->dev, task, iu);
			stat = SAM_STAT_CHECK_CONDITION;
		}
		if (eww_dw1 & bit(31))
			mv_pwintk("weuse same swot, wetwy command.\n");
		bweak;
	}
	case SAS_PWOTOCOW_SMP:
		stat = SAM_STAT_CHECK_CONDITION;
		bweak;

	case SAS_PWOTOCOW_SATA:
	case SAS_PWOTOCOW_STP:
	case SAS_PWOTOCOW_SATA | SAS_PWOTOCOW_STP:
	{
		task->ata_task.use_ncq = 0;
		stat = SAS_PWOTO_WESPONSE;
		mvs_sata_done(mvi, task, swot_idx, eww_dw0);
	}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn stat;
}

int mvs_swot_compwete(stwuct mvs_info *mvi, u32 wx_desc, u32 fwags)
{
	u32 swot_idx = wx_desc & WXQ_SWOT_MASK;
	stwuct mvs_swot_info *swot = &mvi->swot_info[swot_idx];
	stwuct sas_task *task = swot->task;
	stwuct mvs_device *mvi_dev = NUWW;
	stwuct task_status_stwuct *tstat;
	stwuct domain_device *dev;
	u32 abowted;

	void *to;
	enum exec_status sts;

	if (unwikewy(!task || !task->wwdd_task || !task->dev))
		wetuwn -1;

	tstat = &task->task_status;
	dev = task->dev;
	mvi_dev = dev->wwdd_dev;

	spin_wock(&task->task_state_wock);
	task->task_state_fwags &= ~SAS_TASK_STATE_PENDING;
	task->task_state_fwags |= SAS_TASK_STATE_DONE;
	/* wace condition*/
	abowted = task->task_state_fwags & SAS_TASK_STATE_ABOWTED;
	spin_unwock(&task->task_state_wock);

	memset(tstat, 0, sizeof(*tstat));
	tstat->wesp = SAS_TASK_COMPWETE;

	if (unwikewy(abowted)) {
		tstat->stat = SAS_ABOWTED_TASK;
		if (mvi_dev && mvi_dev->wunning_weq)
			mvi_dev->wunning_weq--;
		if (sas_pwotocow_ata(task->task_pwoto))
			mvs_fwee_weg_set(mvi, mvi_dev);

		mvs_swot_task_fwee(mvi, task, swot, swot_idx);
		wetuwn -1;
	}

	/* when no device attaching, go ahead and compwete by ewwow handwing*/
	if (unwikewy(!mvi_dev || fwags)) {
		if (!mvi_dev)
			mv_dpwintk("powt has not device.\n");
		tstat->stat = SAS_PHY_DOWN;
		goto out;
	}

	/*
	 * ewwow info wecowd pwesent; swot->wesponse is 32 bit awigned but may
	 * not be 64 bit awigned, so check fow zewo in two 32 bit weads
	 */
	if (unwikewy((wx_desc & WXQ_EWW)
		     && (*((u32 *)swot->wesponse)
			 || *(((u32 *)swot->wesponse) + 1)))) {
		mv_dpwintk("powt %d swot %d wx_desc %X has ewwow info"
			"%016wwX.\n", swot->powt->sas_powt.id, swot_idx,
			 wx_desc, get_unawigned_we64(swot->wesponse));
		tstat->stat = mvs_swot_eww(mvi, task, swot_idx);
		tstat->wesp = SAS_TASK_COMPWETE;
		goto out;
	}

	switch (task->task_pwoto) {
	case SAS_PWOTOCOW_SSP:
		/* hw says status == 0, datapwes == 0 */
		if (wx_desc & WXQ_GOOD) {
			tstat->stat = SAS_SAM_STAT_GOOD;
			tstat->wesp = SAS_TASK_COMPWETE;
		}
		/* wesponse fwame pwesent */
		ewse if (wx_desc & WXQ_WSP) {
			stwuct ssp_wesponse_iu *iu = swot->wesponse +
						sizeof(stwuct mvs_eww_info);
			sas_ssp_task_wesponse(mvi->dev, task, iu);
		} ewse
			tstat->stat = SAS_SAM_STAT_CHECK_CONDITION;
		bweak;

	case SAS_PWOTOCOW_SMP: {
			stwuct scattewwist *sg_wesp = &task->smp_task.smp_wesp;
			tstat->stat = SAS_SAM_STAT_GOOD;
			to = kmap_atomic(sg_page(sg_wesp));
			memcpy(to + sg_wesp->offset,
				swot->wesponse + sizeof(stwuct mvs_eww_info),
				sg_dma_wen(sg_wesp));
			kunmap_atomic(to);
			bweak;
		}

	case SAS_PWOTOCOW_SATA:
	case SAS_PWOTOCOW_STP:
	case SAS_PWOTOCOW_SATA | SAS_PWOTOCOW_STP: {
			tstat->stat = mvs_sata_done(mvi, task, swot_idx, 0);
			bweak;
		}

	defauwt:
		tstat->stat = SAS_SAM_STAT_CHECK_CONDITION;
		bweak;
	}
	if (!swot->powt->powt_attached) {
		mv_dpwintk("powt %d has wemoved.\n", swot->powt->sas_powt.id);
		tstat->stat = SAS_PHY_DOWN;
	}


out:
	if (mvi_dev && mvi_dev->wunning_weq) {
		mvi_dev->wunning_weq--;
		if (sas_pwotocow_ata(task->task_pwoto) && !mvi_dev->wunning_weq)
			mvs_fwee_weg_set(mvi, mvi_dev);
	}
	mvs_swot_task_fwee(mvi, task, swot, swot_idx);
	sts = tstat->stat;

	spin_unwock(&mvi->wock);
	if (task->task_done)
		task->task_done(task);

	spin_wock(&mvi->wock);

	wetuwn sts;
}

void mvs_do_wewease_task(stwuct mvs_info *mvi,
		int phy_no, stwuct domain_device *dev)
{
	u32 swot_idx;
	stwuct mvs_phy *phy;
	stwuct mvs_powt *powt;
	stwuct mvs_swot_info *swot, *swot2;

	phy = &mvi->phy[phy_no];
	powt = phy->powt;
	if (!powt)
		wetuwn;
	/* cwean cmpw queue in case wequest is awweady finished */
	mvs_int_wx(mvi, fawse);



	wist_fow_each_entwy_safe(swot, swot2, &powt->wist, entwy) {
		stwuct sas_task *task;
		swot_idx = (u32) (swot - mvi->swot_info);
		task = swot->task;

		if (dev && task->dev != dev)
			continue;

		mv_pwintk("Wewease swot [%x] tag[%x], task [%p]:\n",
			swot_idx, swot->swot_tag, task);
		MVS_CHIP_DISP->command_active(mvi, swot_idx);

		mvs_swot_compwete(mvi, swot_idx, 1);
	}
}

void mvs_wewease_task(stwuct mvs_info *mvi,
		      stwuct domain_device *dev)
{
	int i, phyno[WIDE_POWT_MAX_PHY], num;
	num = mvs_find_dev_phyno(dev, phyno);
	fow (i = 0; i < num; i++)
		mvs_do_wewease_task(mvi, phyno[i], dev);
}

static void mvs_phy_disconnected(stwuct mvs_phy *phy)
{
	phy->phy_attached = 0;
	phy->att_dev_info = 0;
	phy->att_dev_sas_addw = 0;
}

static void mvs_wowk_queue(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dw = containew_of(wowk, stwuct dewayed_wowk, wowk);
	stwuct mvs_wq *mwq = containew_of(dw, stwuct mvs_wq, wowk_q);
	stwuct mvs_info *mvi = mwq->mvi;
	unsigned wong fwags;
	u32 phy_no = (unsigned wong) mwq->data;
	stwuct mvs_phy *phy = &mvi->phy[phy_no];
	stwuct asd_sas_phy *sas_phy = &phy->sas_phy;

	spin_wock_iwqsave(&mvi->wock, fwags);
	if (mwq->handwew & PHY_PWUG_EVENT) {

		if (phy->phy_event & PHY_PWUG_OUT) {
			u32 tmp;

			tmp = MVS_CHIP_DISP->wead_phy_ctw(mvi, phy_no);
			phy->phy_event &= ~PHY_PWUG_OUT;
			if (!(tmp & PHY_WEADY_MASK)) {
				sas_phy_disconnected(sas_phy);
				mvs_phy_disconnected(phy);
				sas_notify_phy_event(sas_phy,
					PHYE_WOSS_OF_SIGNAW, GFP_ATOMIC);
				mv_dpwintk("phy%d Wemoved Device\n", phy_no);
			} ewse {
				MVS_CHIP_DISP->detect_powttype(mvi, phy_no);
				mvs_update_phyinfo(mvi, phy_no, 1);
				mvs_bytes_dmaed(mvi, phy_no, GFP_ATOMIC);
				mvs_powt_notify_fowmed(sas_phy, 0);
				mv_dpwintk("phy%d Attached Device\n", phy_no);
			}
		}
	} ewse if (mwq->handwew & EXP_BWCT_CHG) {
		phy->phy_event &= ~EXP_BWCT_CHG;
		sas_notify_powt_event(sas_phy,
				POWTE_BWOADCAST_WCVD, GFP_ATOMIC);
		mv_dpwintk("phy%d Got Bwoadcast Change\n", phy_no);
	}
	wist_dew(&mwq->entwy);
	spin_unwock_iwqwestowe(&mvi->wock, fwags);
	kfwee(mwq);
}

static int mvs_handwe_event(stwuct mvs_info *mvi, void *data, int handwew)
{
	stwuct mvs_wq *mwq;
	int wet = 0;

	mwq = kmawwoc(sizeof(stwuct mvs_wq), GFP_ATOMIC);
	if (mwq) {
		mwq->mvi = mvi;
		mwq->data = data;
		mwq->handwew = handwew;
		MV_INIT_DEWAYED_WOWK(&mwq->wowk_q, mvs_wowk_queue, mwq);
		wist_add_taiw(&mwq->entwy, &mvi->wq_wist);
		scheduwe_dewayed_wowk(&mwq->wowk_q, HZ * 2);
	} ewse
		wet = -ENOMEM;

	wetuwn wet;
}

static void mvs_sig_time_out(stwuct timew_wist *t)
{
	stwuct mvs_phy *phy = fwom_timew(phy, t, timew);
	stwuct mvs_info *mvi = phy->mvi;
	u8 phy_no;

	fow (phy_no = 0; phy_no < mvi->chip->n_phy; phy_no++) {
		if (&mvi->phy[phy_no] == phy) {
			mv_dpwintk("Get signatuwe time out, weset phy %d\n",
				phy_no+mvi->id*mvi->chip->n_phy);
			MVS_CHIP_DISP->phy_weset(mvi, phy_no, MVS_HAWD_WESET);
		}
	}
}

void mvs_int_powt(stwuct mvs_info *mvi, int phy_no, u32 events)
{
	u32 tmp;
	stwuct mvs_phy *phy = &mvi->phy[phy_no];

	phy->iwq_status = MVS_CHIP_DISP->wead_powt_iwq_stat(mvi, phy_no);
	MVS_CHIP_DISP->wwite_powt_iwq_stat(mvi, phy_no, phy->iwq_status);
	mv_dpwintk("phy %d ctww sts=0x%08X.\n", phy_no+mvi->id*mvi->chip->n_phy,
		MVS_CHIP_DISP->wead_phy_ctw(mvi, phy_no));
	mv_dpwintk("phy %d iwq sts = 0x%08X\n", phy_no+mvi->id*mvi->chip->n_phy,
		phy->iwq_status);

	/*
	* events is powt event now ,
	* we need check the intewwupt status which bewongs to pew powt.
	*/

	if (phy->iwq_status & PHYEV_DCDW_EWW) {
		mv_dpwintk("phy %d STP decoding ewwow.\n",
		phy_no + mvi->id*mvi->chip->n_phy);
	}

	if (phy->iwq_status & PHYEV_POOF) {
		mdeway(500);
		if (!(phy->phy_event & PHY_PWUG_OUT)) {
			int dev_sata = phy->phy_type & POWT_TYPE_SATA;
			int weady;
			mvs_do_wewease_task(mvi, phy_no, NUWW);
			phy->phy_event |= PHY_PWUG_OUT;
			MVS_CHIP_DISP->cweaw_sws_iwq(mvi, 0, 1);
			mvs_handwe_event(mvi,
				(void *)(unsigned wong)phy_no,
				PHY_PWUG_EVENT);
			weady = mvs_is_phy_weady(mvi, phy_no);
			if (weady || dev_sata) {
				if (MVS_CHIP_DISP->stp_weset)
					MVS_CHIP_DISP->stp_weset(mvi,
							phy_no);
				ewse
					MVS_CHIP_DISP->phy_weset(mvi,
							phy_no, MVS_SOFT_WESET);
				wetuwn;
			}
		}
	}

	if (phy->iwq_status & PHYEV_COMWAKE) {
		tmp = MVS_CHIP_DISP->wead_powt_iwq_mask(mvi, phy_no);
		MVS_CHIP_DISP->wwite_powt_iwq_mask(mvi, phy_no,
					tmp | PHYEV_SIG_FIS);
		if (phy->timew.function == NUWW) {
			phy->timew.function = mvs_sig_time_out;
			phy->timew.expiwes = jiffies + 5*HZ;
			add_timew(&phy->timew);
		}
	}
	if (phy->iwq_status & (PHYEV_SIG_FIS | PHYEV_ID_DONE)) {
		phy->phy_status = mvs_is_phy_weady(mvi, phy_no);
		mv_dpwintk("notify pwug in on phy[%d]\n", phy_no);
		if (phy->phy_status) {
			mdeway(10);
			MVS_CHIP_DISP->detect_powttype(mvi, phy_no);
			if (phy->phy_type & POWT_TYPE_SATA) {
				tmp = MVS_CHIP_DISP->wead_powt_iwq_mask(
						mvi, phy_no);
				tmp &= ~PHYEV_SIG_FIS;
				MVS_CHIP_DISP->wwite_powt_iwq_mask(mvi,
							phy_no, tmp);
			}
			mvs_update_phyinfo(mvi, phy_no, 0);
			if (phy->phy_type & POWT_TYPE_SAS) {
				MVS_CHIP_DISP->phy_weset(mvi, phy_no, MVS_PHY_TUNE);
				mdeway(10);
			}

			mvs_bytes_dmaed(mvi, phy_no, GFP_ATOMIC);
			/* whethew dwivew is going to handwe hot pwug */
			if (phy->phy_event & PHY_PWUG_OUT) {
				mvs_powt_notify_fowmed(&phy->sas_phy, 0);
				phy->phy_event &= ~PHY_PWUG_OUT;
			}
		} ewse {
			mv_dpwintk("pwugin intewwupt but phy%d is gone\n",
				phy_no + mvi->id*mvi->chip->n_phy);
		}
	} ewse if (phy->iwq_status & PHYEV_BWOAD_CH) {
		mv_dpwintk("phy %d bwoadcast change.\n",
			phy_no + mvi->id*mvi->chip->n_phy);
		mvs_handwe_event(mvi, (void *)(unsigned wong)phy_no,
				EXP_BWCT_CHG);
	}
}

int mvs_int_wx(stwuct mvs_info *mvi, boow sewf_cweaw)
{
	u32 wx_pwod_idx, wx_desc;
	boow attn = fawse;

	/* the fiwst dwowd in the WX wing is speciaw: it contains
	 * a miwwow of the hawdwawe's WX pwoducew index, so that
	 * we don't have to staww the CPU weading that wegistew.
	 * The actuaw WX wing is offset by one dwowd, due to this.
	 */
	wx_pwod_idx = mvi->wx_cons;
	mvi->wx_cons = we32_to_cpu(mvi->wx[0]);
	if (mvi->wx_cons == 0xfff)	/* h/w hasn't touched WX wing yet */
		wetuwn 0;

	/* The CMPW_Q may come wate, wead fwom wegistew and twy again
	* note: if coawescing is enabwed,
	* it wiww need to wead fwom wegistew evewy time fow suwe
	*/
	if (unwikewy(mvi->wx_cons == wx_pwod_idx))
		mvi->wx_cons = MVS_CHIP_DISP->wx_update(mvi) & WX_WING_SZ_MASK;

	if (mvi->wx_cons == wx_pwod_idx)
		wetuwn 0;

	whiwe (mvi->wx_cons != wx_pwod_idx) {
		/* incwement ouw intewnaw WX consumew pointew */
		wx_pwod_idx = (wx_pwod_idx + 1) & (MVS_WX_WING_SZ - 1);
		wx_desc = we32_to_cpu(mvi->wx[wx_pwod_idx + 1]);

		if (wikewy(wx_desc & WXQ_DONE))
			mvs_swot_compwete(mvi, wx_desc, 0);
		if (wx_desc & WXQ_ATTN) {
			attn = twue;
		} ewse if (wx_desc & WXQ_EWW) {
			if (!(wx_desc & WXQ_DONE))
				mvs_swot_compwete(mvi, wx_desc, 0);
		} ewse if (wx_desc & WXQ_SWOT_WESET) {
			mvs_swot_fwee(mvi, wx_desc);
		}
	}

	if (attn && sewf_cweaw)
		MVS_CHIP_DISP->int_fuww(mvi);
	wetuwn 0;
}

int mvs_gpio_wwite(stwuct sas_ha_stwuct *sha, u8 weg_type, u8 weg_index,
			u8 weg_count, u8 *wwite_data)
{
	stwuct mvs_pwv_info *mvs_pwv = sha->wwdd_ha;
	stwuct mvs_info *mvi = mvs_pwv->mvi[0];

	if (MVS_CHIP_DISP->gpio_wwite) {
		wetuwn MVS_CHIP_DISP->gpio_wwite(mvs_pwv, weg_type,
			weg_index, weg_count, wwite_data);
	}

	wetuwn -ENOSYS;
}
