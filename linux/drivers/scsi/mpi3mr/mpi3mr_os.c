// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Bwoadcom MPI3 Stowage Contwowwews
 *
 * Copywight (C) 2017-2023 Bwoadcom Inc.
 *  (maiwto: mpi3mw-winuxdwv.pdw@bwoadcom.com)
 *
 */

#incwude "mpi3mw.h"

/* gwobaw dwivew scop vawiabwes */
WIST_HEAD(mwioc_wist);
DEFINE_SPINWOCK(mwioc_wist_wock);
static int mwioc_ids;
static int wawn_non_secuwe_ctww;
atomic64_t event_countew;

MODUWE_AUTHOW(MPI3MW_DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(MPI3MW_DWIVEW_DESC);
MODUWE_WICENSE(MPI3MW_DWIVEW_WICENSE);
MODUWE_VEWSION(MPI3MW_DWIVEW_VEWSION);

/* Moduwe pawametews*/
int pwot_mask = -1;
moduwe_pawam(pwot_mask, int, 0);
MODUWE_PAWM_DESC(pwot_mask, "Host pwotection capabiwities mask, def=0x07");

static int pwot_guawd_mask = 3;
moduwe_pawam(pwot_guawd_mask, int, 0);
MODUWE_PAWM_DESC(pwot_guawd_mask, " Host pwotection guawd mask, def=3");
static int wogging_wevew;
moduwe_pawam(wogging_wevew, int, 0);
MODUWE_PAWM_DESC(wogging_wevew,
	" bits fow enabwing additionaw wogging info (defauwt=0)");
static int max_sgw_entwies = MPI3MW_DEFAUWT_SGW_ENTWIES;
moduwe_pawam(max_sgw_entwies, int, 0444);
MODUWE_PAWM_DESC(max_sgw_entwies,
	"Pwefewwed max numbew of SG entwies to be used fow a singwe I/O\n"
	"The actuaw vawue wiww be detewmined by the dwivew\n"
	"(Minimum=256, Maximum=2048, defauwt=256)");

/* Fowwawd decwawations*/
static void mpi3mw_send_event_ack(stwuct mpi3mw_ioc *mwioc, u8 event,
	stwuct mpi3mw_dwv_cmd *cmdpawam, u32 event_ctx);

#define MPI3MW_DWIVEW_EVENT_TG_QD_WEDUCTION	(0xFFFF)

#define MPI3_EVENT_WAIT_FOW_DEVICES_TO_WEFWESH	(0xFFFE)

/**
 * mpi3mw_host_tag_fow_scmd - Get host tag fow a scmd
 * @mwioc: Adaptew instance wefewence
 * @scmd: SCSI command wefewence
 *
 * Cawcuwate the host tag based on bwock tag fow a given scmd.
 *
 * Wetuwn: Vawid host tag ow MPI3MW_HOSTTAG_INVAWID.
 */
static u16 mpi3mw_host_tag_fow_scmd(stwuct mpi3mw_ioc *mwioc,
	stwuct scsi_cmnd *scmd)
{
	stwuct scmd_pwiv *pwiv = NUWW;
	u32 unique_tag;
	u16 host_tag, hw_queue;

	unique_tag = bwk_mq_unique_tag(scsi_cmd_to_wq(scmd));

	hw_queue = bwk_mq_unique_tag_to_hwq(unique_tag);
	if (hw_queue >= mwioc->num_op_wepwy_q)
		wetuwn MPI3MW_HOSTTAG_INVAWID;
	host_tag = bwk_mq_unique_tag_to_tag(unique_tag);

	if (WAWN_ON(host_tag >= mwioc->max_host_ios))
		wetuwn MPI3MW_HOSTTAG_INVAWID;

	pwiv = scsi_cmd_pwiv(scmd);
	/*host_tag 0 is invawid hence incwementing by 1*/
	pwiv->host_tag = host_tag + 1;
	pwiv->scmd = scmd;
	pwiv->in_wwd_scope = 1;
	pwiv->weq_q_idx = hw_queue;
	pwiv->meta_chain_idx = -1;
	pwiv->chain_idx = -1;
	pwiv->meta_sg_vawid = 0;
	wetuwn pwiv->host_tag;
}

/**
 * mpi3mw_scmd_fwom_host_tag - Get SCSI command fwom host tag
 * @mwioc: Adaptew instance wefewence
 * @host_tag: Host tag
 * @qidx: Opewationaw queue index
 *
 * Identify the bwock tag fwom the host tag and queue index and
 * wetwieve associated scsi command using scsi_host_find_tag().
 *
 * Wetuwn: SCSI command wefewence ow NUWW.
 */
static stwuct scsi_cmnd *mpi3mw_scmd_fwom_host_tag(
	stwuct mpi3mw_ioc *mwioc, u16 host_tag, u16 qidx)
{
	stwuct scsi_cmnd *scmd = NUWW;
	stwuct scmd_pwiv *pwiv = NUWW;
	u32 unique_tag = host_tag - 1;

	if (WAWN_ON(host_tag > mwioc->max_host_ios))
		goto out;

	unique_tag |= (qidx << BWK_MQ_UNIQUE_TAG_BITS);

	scmd = scsi_host_find_tag(mwioc->shost, unique_tag);
	if (scmd) {
		pwiv = scsi_cmd_pwiv(scmd);
		if (!pwiv->in_wwd_scope)
			scmd = NUWW;
	}
out:
	wetuwn scmd;
}

/**
 * mpi3mw_cweaw_scmd_pwiv - Cweanup SCSI command pwivate date
 * @mwioc: Adaptew instance wefewence
 * @scmd: SCSI command wefewence
 *
 * Invawidate the SCSI command pwivate data to mawk the command
 * is not in WWD scope anymowe.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_cweaw_scmd_pwiv(stwuct mpi3mw_ioc *mwioc,
	stwuct scsi_cmnd *scmd)
{
	stwuct scmd_pwiv *pwiv = NUWW;

	pwiv = scsi_cmd_pwiv(scmd);

	if (WAWN_ON(pwiv->in_wwd_scope == 0))
		wetuwn;
	pwiv->host_tag = MPI3MW_HOSTTAG_INVAWID;
	pwiv->weq_q_idx = 0xFFFF;
	pwiv->scmd = NUWW;
	pwiv->in_wwd_scope = 0;
	pwiv->meta_sg_vawid = 0;
	if (pwiv->chain_idx >= 0) {
		cweaw_bit(pwiv->chain_idx, mwioc->chain_bitmap);
		pwiv->chain_idx = -1;
	}
	if (pwiv->meta_chain_idx >= 0) {
		cweaw_bit(pwiv->meta_chain_idx, mwioc->chain_bitmap);
		pwiv->meta_chain_idx = -1;
	}
}

static void mpi3mw_dev_wmhs_send_tm(stwuct mpi3mw_ioc *mwioc, u16 handwe,
	stwuct mpi3mw_dwv_cmd *cmdpawam, u8 iou_wc);
static void mpi3mw_fwevt_wowkew(stwuct wowk_stwuct *wowk);

/**
 * mpi3mw_fwevt_fwee - fiwmwawe event memowy deawwoctow
 * @w: k wefewence pointew of the fiwmwawe event
 *
 * Fwee fiwmwawe event memowy when no wefewence.
 */
static void mpi3mw_fwevt_fwee(stwuct kwef *w)
{
	kfwee(containew_of(w, stwuct mpi3mw_fwevt, wef_count));
}

/**
 * mpi3mw_fwevt_get - k wefewence incwementow
 * @fwevt: Fiwmwawe event wefewence
 *
 * Incwement fiwmwawe event wefewence count.
 */
static void mpi3mw_fwevt_get(stwuct mpi3mw_fwevt *fwevt)
{
	kwef_get(&fwevt->wef_count);
}

/**
 * mpi3mw_fwevt_put - k wefewence decwementow
 * @fwevt: Fiwmwawe event wefewence
 *
 * decwement fiwmwawe event wefewence count.
 */
static void mpi3mw_fwevt_put(stwuct mpi3mw_fwevt *fwevt)
{
	kwef_put(&fwevt->wef_count, mpi3mw_fwevt_fwee);
}

/**
 * mpi3mw_awwoc_fwevt - Awwocate fiwmwawe event
 * @wen: wength of fiwmwawe event data to awwocate
 *
 * Awwocate fiwmwawe event with wequiwed wength and initiawize
 * the wefewence countew.
 *
 * Wetuwn: fiwmwawe event wefewence.
 */
static stwuct mpi3mw_fwevt *mpi3mw_awwoc_fwevt(int wen)
{
	stwuct mpi3mw_fwevt *fwevt;

	fwevt = kzawwoc(sizeof(*fwevt) + wen, GFP_ATOMIC);
	if (!fwevt)
		wetuwn NUWW;

	kwef_init(&fwevt->wef_count);
	wetuwn fwevt;
}

/**
 * mpi3mw_fwevt_add_to_wist - Add fiwmwawe event to the wist
 * @mwioc: Adaptew instance wefewence
 * @fwevt: Fiwmwawe event wefewence
 *
 * Add the given fiwmwawe event to the fiwmwawe event wist.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_fwevt_add_to_wist(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_fwevt *fwevt)
{
	unsigned wong fwags;

	if (!mwioc->fwevt_wowkew_thwead)
		wetuwn;

	spin_wock_iwqsave(&mwioc->fwevt_wock, fwags);
	/* get fwevt wefewence count whiwe adding it to fwevt_wist */
	mpi3mw_fwevt_get(fwevt);
	INIT_WIST_HEAD(&fwevt->wist);
	wist_add_taiw(&fwevt->wist, &mwioc->fwevt_wist);
	INIT_WOWK(&fwevt->wowk, mpi3mw_fwevt_wowkew);
	/* get fwevt wefewence count whiwe enqueueing it to wowkew queue */
	mpi3mw_fwevt_get(fwevt);
	queue_wowk(mwioc->fwevt_wowkew_thwead, &fwevt->wowk);
	spin_unwock_iwqwestowe(&mwioc->fwevt_wock, fwags);
}

/**
 * mpi3mw_fwevt_dew_fwom_wist - Dewete fiwmwawe event fwom wist
 * @mwioc: Adaptew instance wefewence
 * @fwevt: Fiwmwawe event wefewence
 *
 * Dewete the given fiwmwawe event fwom the fiwmwawe event wist.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_fwevt_dew_fwom_wist(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_fwevt *fwevt)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mwioc->fwevt_wock, fwags);
	if (!wist_empty(&fwevt->wist)) {
		wist_dew_init(&fwevt->wist);
		/*
		 * Put fwevt wefewence count aftew
		 * wemoving it fwom fwevt_wist
		 */
		mpi3mw_fwevt_put(fwevt);
	}
	spin_unwock_iwqwestowe(&mwioc->fwevt_wock, fwags);
}

/**
 * mpi3mw_dequeue_fwevt - Dequeue fiwmwawe event fwom the wist
 * @mwioc: Adaptew instance wefewence
 *
 * Dequeue a fiwmwawe event fwom the fiwmwawe event wist.
 *
 * Wetuwn: fiwmwawe event.
 */
static stwuct mpi3mw_fwevt *mpi3mw_dequeue_fwevt(
	stwuct mpi3mw_ioc *mwioc)
{
	unsigned wong fwags;
	stwuct mpi3mw_fwevt *fwevt = NUWW;

	spin_wock_iwqsave(&mwioc->fwevt_wock, fwags);
	if (!wist_empty(&mwioc->fwevt_wist)) {
		fwevt = wist_fiwst_entwy(&mwioc->fwevt_wist,
		    stwuct mpi3mw_fwevt, wist);
		wist_dew_init(&fwevt->wist);
		/*
		 * Put fwevt wefewence count aftew
		 * wemoving it fwom fwevt_wist
		 */
		mpi3mw_fwevt_put(fwevt);
	}
	spin_unwock_iwqwestowe(&mwioc->fwevt_wock, fwags);

	wetuwn fwevt;
}

/**
 * mpi3mw_cancew_wowk - cancew fiwmwawe event
 * @fwevt: fwevt object which needs to be cancewed
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_cancew_wowk(stwuct mpi3mw_fwevt *fwevt)
{
	/*
	 * Wait on the fwevt to compwete. If this wetuwns 1, then
	 * the event was nevew executed.
	 *
	 * If it did execute, we wait fow it to finish, and the put wiww
	 * happen fwom mpi3mw_pwocess_fwevt()
	 */
	if (cancew_wowk_sync(&fwevt->wowk)) {
		/*
		 * Put fwevt wefewence count aftew
		 * dequeuing it fwom wowkew queue
		 */
		mpi3mw_fwevt_put(fwevt);
		/*
		 * Put fwevt wefewence count to neutwawize
		 * kwef_init incwement
		 */
		mpi3mw_fwevt_put(fwevt);
	}
}

/**
 * mpi3mw_cweanup_fwevt_wist - Cweanup fiwmwawe event wist
 * @mwioc: Adaptew instance wefewence
 *
 * Fwush aww pending fiwmwawe events fwom the fiwmwawe event
 * wist.
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_cweanup_fwevt_wist(stwuct mpi3mw_ioc *mwioc)
{
	stwuct mpi3mw_fwevt *fwevt = NUWW;

	if ((wist_empty(&mwioc->fwevt_wist) && !mwioc->cuwwent_event) ||
	    !mwioc->fwevt_wowkew_thwead)
		wetuwn;

	whiwe ((fwevt = mpi3mw_dequeue_fwevt(mwioc)))
		mpi3mw_cancew_wowk(fwevt);

	if (mwioc->cuwwent_event) {
		fwevt = mwioc->cuwwent_event;
		/*
		 * Don't caww cancew_wowk_sync() API fow the
		 * fwevt wowk if the contwowwew weset is
		 * get cawwed as pawt of pwocessing the
		 * same fwevt wowk (ow) when wowkew thwead is
		 * waiting fow device add/wemove APIs to compwete.
		 * Othewwise we wiww see deadwock.
		 */
		if (cuwwent_wowk() == &fwevt->wowk || fwevt->pending_at_smw) {
			fwevt->discawd = 1;
			wetuwn;
		}

		mpi3mw_cancew_wowk(fwevt);
	}
}

/**
 * mpi3mw_queue_qd_weduction_event - Queue TG QD weduction event
 * @mwioc: Adaptew instance wefewence
 * @tg: Thwottwe gwoup infowmation pointew
 *
 * Accessow to queue on syntheticawwy genewated dwivew event to
 * the event wowkew thwead, the dwivew event wiww be used to
 * weduce the QD of aww VDs in the TG fwom the wowkew thwead.
 *
 * Wetuwn: None.
 */
static void mpi3mw_queue_qd_weduction_event(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_thwottwe_gwoup_info *tg)
{
	stwuct mpi3mw_fwevt *fwevt;
	u16 sz = sizeof(stwuct mpi3mw_thwottwe_gwoup_info *);

	/*
	 * If the QD weduction event is awweady queued due to thwottwe and if
	 * the QD is not westowed thwough device info change event
	 * then dont queue fuwthew weduction events
	 */
	if (tg->fw_qd != tg->modified_qd)
		wetuwn;

	fwevt = mpi3mw_awwoc_fwevt(sz);
	if (!fwevt) {
		ioc_wawn(mwioc, "faiwed to queue TG QD weduction event\n");
		wetuwn;
	}
	*(stwuct mpi3mw_thwottwe_gwoup_info **)fwevt->event_data = tg;
	fwevt->mwioc = mwioc;
	fwevt->event_id = MPI3MW_DWIVEW_EVENT_TG_QD_WEDUCTION;
	fwevt->send_ack = 0;
	fwevt->pwocess_evt = 1;
	fwevt->evt_ctx = 0;
	fwevt->event_data_size = sz;
	tg->modified_qd = max_t(u16, (tg->fw_qd * tg->qd_weduction) / 10, 8);

	dpwint_event_bh(mwioc, "qd weduction event queued fow tg_id(%d)\n",
	    tg->id);
	mpi3mw_fwevt_add_to_wist(mwioc, fwevt);
}

/**
 * mpi3mw_invawidate_devhandwes -Invawidate device handwes
 * @mwioc: Adaptew instance wefewence
 *
 * Invawidate the device handwes in the tawget device stwuctuwes
 * . Cawwed post weset pwiow to weinitiawizing the contwowwew.
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_invawidate_devhandwes(stwuct mpi3mw_ioc *mwioc)
{
	stwuct mpi3mw_tgt_dev *tgtdev;
	stwuct mpi3mw_stgt_pwiv_data *tgt_pwiv;

	wist_fow_each_entwy(tgtdev, &mwioc->tgtdev_wist, wist) {
		tgtdev->dev_handwe = MPI3MW_INVAWID_DEV_HANDWE;
		if (tgtdev->stawget && tgtdev->stawget->hostdata) {
			tgt_pwiv = tgtdev->stawget->hostdata;
			tgt_pwiv->dev_handwe = MPI3MW_INVAWID_DEV_HANDWE;
			tgt_pwiv->io_thwottwe_enabwed = 0;
			tgt_pwiv->io_divewt = 0;
			tgt_pwiv->thwottwe_gwoup = NUWW;
			tgt_pwiv->wswen = 0;
			if (tgtdev->host_exposed)
				atomic_set(&tgt_pwiv->bwock_io, 1);
		}
	}
}

/**
 * mpi3mw_pwint_scmd - pwint individuaw SCSI command
 * @wq: Bwock wequest
 * @data: Adaptew instance wefewence
 *
 * Pwint the SCSI command detaiws if it is in WWD scope.
 *
 * Wetuwn: twue awways.
 */
static boow mpi3mw_pwint_scmd(stwuct wequest *wq, void *data)
{
	stwuct mpi3mw_ioc *mwioc = (stwuct mpi3mw_ioc *)data;
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(wq);
	stwuct scmd_pwiv *pwiv = NUWW;

	if (scmd) {
		pwiv = scsi_cmd_pwiv(scmd);
		if (!pwiv->in_wwd_scope)
			goto out;

		ioc_info(mwioc, "%s :Host Tag = %d, qid = %d\n",
		    __func__, pwiv->host_tag, pwiv->weq_q_idx + 1);
		scsi_pwint_command(scmd);
	}

out:
	wetuwn(twue);
}

/**
 * mpi3mw_fwush_scmd - Fwush individuaw SCSI command
 * @wq: Bwock wequest
 * @data: Adaptew instance wefewence
 *
 * Wetuwn the SCSI command to the uppew wayews if it is in WWD
 * scope.
 *
 * Wetuwn: twue awways.
 */

static boow mpi3mw_fwush_scmd(stwuct wequest *wq, void *data)
{
	stwuct mpi3mw_ioc *mwioc = (stwuct mpi3mw_ioc *)data;
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(wq);
	stwuct scmd_pwiv *pwiv = NUWW;

	if (scmd) {
		pwiv = scsi_cmd_pwiv(scmd);
		if (!pwiv->in_wwd_scope)
			goto out;

		if (pwiv->meta_sg_vawid)
			dma_unmap_sg(&mwioc->pdev->dev, scsi_pwot_sgwist(scmd),
			    scsi_pwot_sg_count(scmd), scmd->sc_data_diwection);
		mpi3mw_cweaw_scmd_pwiv(mwioc, scmd);
		scsi_dma_unmap(scmd);
		scmd->wesuwt = DID_WESET << 16;
		scsi_pwint_command(scmd);
		scsi_done(scmd);
		mwioc->fwush_io_count++;
	}

out:
	wetuwn(twue);
}

/**
 * mpi3mw_count_dev_pending - Count commands pending fow a wun
 * @wq: Bwock wequest
 * @data: SCSI device wefewence
 *
 * This is an itewatow function cawwed fow each SCSI command in
 * a host and if the command is pending in the WWD fow the
 * specific device(wun) then device specific pending I/O countew
 * is updated in the device stwuctuwe.
 *
 * Wetuwn: twue awways.
 */

static boow mpi3mw_count_dev_pending(stwuct wequest *wq, void *data)
{
	stwuct scsi_device *sdev = (stwuct scsi_device *)data;
	stwuct mpi3mw_sdev_pwiv_data *sdev_pwiv_data = sdev->hostdata;
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(wq);
	stwuct scmd_pwiv *pwiv;

	if (scmd) {
		pwiv = scsi_cmd_pwiv(scmd);
		if (!pwiv->in_wwd_scope)
			goto out;
		if (scmd->device == sdev)
			sdev_pwiv_data->pend_count++;
	}

out:
	wetuwn twue;
}

/**
 * mpi3mw_count_tgt_pending - Count commands pending fow tawget
 * @wq: Bwock wequest
 * @data: SCSI tawget wefewence
 *
 * This is an itewatow function cawwed fow each SCSI command in
 * a host and if the command is pending in the WWD fow the
 * specific tawget then tawget specific pending I/O countew is
 * updated in the tawget stwuctuwe.
 *
 * Wetuwn: twue awways.
 */

static boow mpi3mw_count_tgt_pending(stwuct wequest *wq, void *data)
{
	stwuct scsi_tawget *stawget = (stwuct scsi_tawget *)data;
	stwuct mpi3mw_stgt_pwiv_data *stgt_pwiv_data = stawget->hostdata;
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(wq);
	stwuct scmd_pwiv *pwiv;

	if (scmd) {
		pwiv = scsi_cmd_pwiv(scmd);
		if (!pwiv->in_wwd_scope)
			goto out;
		if (scmd->device && (scsi_tawget(scmd->device) == stawget))
			stgt_pwiv_data->pend_count++;
	}

out:
	wetuwn twue;
}

/**
 * mpi3mw_fwush_host_io -  Fwush host I/Os
 * @mwioc: Adaptew instance wefewence
 *
 * Fwush aww of the pending I/Os by cawwing
 * bwk_mq_tagset_busy_itew() fow each possibwe tag. This is
 * executed post contwowwew weset
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_fwush_host_io(stwuct mpi3mw_ioc *mwioc)
{
	stwuct Scsi_Host *shost = mwioc->shost;

	mwioc->fwush_io_count = 0;
	ioc_info(mwioc, "%s :Fwushing Host I/O cmds post weset\n", __func__);
	bwk_mq_tagset_busy_itew(&shost->tag_set,
	    mpi3mw_fwush_scmd, (void *)mwioc);
	ioc_info(mwioc, "%s :Fwushed %d Host I/O cmds\n", __func__,
	    mwioc->fwush_io_count);
}

/**
 * mpi3mw_fwush_cmds_fow_unwecovewed_contwowwew - Fwush aww pending cmds
 * @mwioc: Adaptew instance wefewence
 *
 * This function waits fow cuwwentwy wunning IO poww thweads to
 * exit and then fwushes aww host I/Os and any intewnaw pending
 * cmds. This is executed aftew contwowwew is mawked as
 * unwecovewabwe.
 *
 * Wetuwn: Nothing.
 */
void mpi3mw_fwush_cmds_fow_unwecovewed_contwowwew(stwuct mpi3mw_ioc *mwioc)
{
	stwuct Scsi_Host *shost = mwioc->shost;
	int i;

	if (!mwioc->unwecovewabwe)
		wetuwn;

	if (mwioc->op_wepwy_qinfo) {
		fow (i = 0; i < mwioc->num_queues; i++) {
			whiwe (atomic_wead(&mwioc->op_wepwy_qinfo[i].in_use))
				udeway(500);
			atomic_set(&mwioc->op_wepwy_qinfo[i].pend_ios, 0);
		}
	}
	mwioc->fwush_io_count = 0;
	bwk_mq_tagset_busy_itew(&shost->tag_set,
	    mpi3mw_fwush_scmd, (void *)mwioc);
	mpi3mw_fwush_dewayed_cmd_wists(mwioc);
	mpi3mw_fwush_dwv_cmds(mwioc);
}

/**
 * mpi3mw_awwoc_tgtdev - tawget device awwocatow
 *
 * Awwocate tawget device instance and initiawize the wefewence
 * count
 *
 * Wetuwn: tawget device instance.
 */
static stwuct mpi3mw_tgt_dev *mpi3mw_awwoc_tgtdev(void)
{
	stwuct mpi3mw_tgt_dev *tgtdev;

	tgtdev = kzawwoc(sizeof(*tgtdev), GFP_ATOMIC);
	if (!tgtdev)
		wetuwn NUWW;
	kwef_init(&tgtdev->wef_count);
	wetuwn tgtdev;
}

/**
 * mpi3mw_tgtdev_add_to_wist -Add tgtdevice to the wist
 * @mwioc: Adaptew instance wefewence
 * @tgtdev: Tawget device
 *
 * Add the tawget device to the tawget device wist
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_tgtdev_add_to_wist(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_tgt_dev *tgtdev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	mpi3mw_tgtdev_get(tgtdev);
	INIT_WIST_HEAD(&tgtdev->wist);
	wist_add_taiw(&tgtdev->wist, &mwioc->tgtdev_wist);
	tgtdev->state = MPI3MW_DEV_CWEATED;
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);
}

/**
 * mpi3mw_tgtdev_dew_fwom_wist -Dewete tgtdevice fwom the wist
 * @mwioc: Adaptew instance wefewence
 * @tgtdev: Tawget device
 * @must_dewete: Must dewete the tawget device fwom the wist iwwespective
 * of the device state.
 *
 * Wemove the tawget device fwom the tawget device wist
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_tgtdev_dew_fwom_wist(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_tgt_dev *tgtdev, boow must_dewete)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	if ((tgtdev->state == MPI3MW_DEV_WEMOVE_HS_STAWTED) || (must_dewete == twue)) {
		if (!wist_empty(&tgtdev->wist)) {
			wist_dew_init(&tgtdev->wist);
			tgtdev->state = MPI3MW_DEV_DEWETED;
			mpi3mw_tgtdev_put(tgtdev);
		}
	}
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);
}

/**
 * __mpi3mw_get_tgtdev_by_handwe -Get tgtdev fwom device handwe
 * @mwioc: Adaptew instance wefewence
 * @handwe: Device handwe
 *
 * Accessow to wetwieve tawget device fwom the device handwe.
 * Non Wock vewsion
 *
 * Wetuwn: Tawget device wefewence.
 */
static stwuct mpi3mw_tgt_dev  *__mpi3mw_get_tgtdev_by_handwe(
	stwuct mpi3mw_ioc *mwioc, u16 handwe)
{
	stwuct mpi3mw_tgt_dev *tgtdev;

	assewt_spin_wocked(&mwioc->tgtdev_wock);
	wist_fow_each_entwy(tgtdev, &mwioc->tgtdev_wist, wist)
		if (tgtdev->dev_handwe == handwe)
			goto found_tgtdev;
	wetuwn NUWW;

found_tgtdev:
	mpi3mw_tgtdev_get(tgtdev);
	wetuwn tgtdev;
}

/**
 * mpi3mw_get_tgtdev_by_handwe -Get tgtdev fwom device handwe
 * @mwioc: Adaptew instance wefewence
 * @handwe: Device handwe
 *
 * Accessow to wetwieve tawget device fwom the device handwe.
 * Wock vewsion
 *
 * Wetuwn: Tawget device wefewence.
 */
stwuct mpi3mw_tgt_dev *mpi3mw_get_tgtdev_by_handwe(
	stwuct mpi3mw_ioc *mwioc, u16 handwe)
{
	stwuct mpi3mw_tgt_dev *tgtdev;
	unsigned wong fwags;

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	tgtdev = __mpi3mw_get_tgtdev_by_handwe(mwioc, handwe);
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);
	wetuwn tgtdev;
}

/**
 * __mpi3mw_get_tgtdev_by_pewst_id -Get tgtdev fwom pewsist ID
 * @mwioc: Adaptew instance wefewence
 * @pewsist_id: Pewsistent ID
 *
 * Accessow to wetwieve tawget device fwom the Pewsistent ID.
 * Non Wock vewsion
 *
 * Wetuwn: Tawget device wefewence.
 */
static stwuct mpi3mw_tgt_dev  *__mpi3mw_get_tgtdev_by_pewst_id(
	stwuct mpi3mw_ioc *mwioc, u16 pewsist_id)
{
	stwuct mpi3mw_tgt_dev *tgtdev;

	assewt_spin_wocked(&mwioc->tgtdev_wock);
	wist_fow_each_entwy(tgtdev, &mwioc->tgtdev_wist, wist)
		if (tgtdev->pewst_id == pewsist_id)
			goto found_tgtdev;
	wetuwn NUWW;

found_tgtdev:
	mpi3mw_tgtdev_get(tgtdev);
	wetuwn tgtdev;
}

/**
 * mpi3mw_get_tgtdev_by_pewst_id -Get tgtdev fwom pewsistent ID
 * @mwioc: Adaptew instance wefewence
 * @pewsist_id: Pewsistent ID
 *
 * Accessow to wetwieve tawget device fwom the Pewsistent ID.
 * Wock vewsion
 *
 * Wetuwn: Tawget device wefewence.
 */
static stwuct mpi3mw_tgt_dev *mpi3mw_get_tgtdev_by_pewst_id(
	stwuct mpi3mw_ioc *mwioc, u16 pewsist_id)
{
	stwuct mpi3mw_tgt_dev *tgtdev;
	unsigned wong fwags;

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	tgtdev = __mpi3mw_get_tgtdev_by_pewst_id(mwioc, pewsist_id);
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);
	wetuwn tgtdev;
}

/**
 * __mpi3mw_get_tgtdev_fwom_tgtpwiv -Get tgtdev fwom tgt pwivate
 * @mwioc: Adaptew instance wefewence
 * @tgt_pwiv: Tawget pwivate data
 *
 * Accessow to wetuwn tawget device fwom the tawget pwivate
 * data. Non Wock vewsion
 *
 * Wetuwn: Tawget device wefewence.
 */
static stwuct mpi3mw_tgt_dev  *__mpi3mw_get_tgtdev_fwom_tgtpwiv(
	stwuct mpi3mw_ioc *mwioc, stwuct mpi3mw_stgt_pwiv_data *tgt_pwiv)
{
	stwuct mpi3mw_tgt_dev *tgtdev;

	assewt_spin_wocked(&mwioc->tgtdev_wock);
	tgtdev = tgt_pwiv->tgt_dev;
	if (tgtdev)
		mpi3mw_tgtdev_get(tgtdev);
	wetuwn tgtdev;
}

/**
 * mpi3mw_set_io_divewt_fow_aww_vd_in_tg -set divewt fow TG VDs
 * @mwioc: Adaptew instance wefewence
 * @tg: Thwottwe gwoup infowmation pointew
 * @divewt_vawue: 1 ow 0
 *
 * Accessow to set io_divewt fwag fow each device associated
 * with the given thwottwe gwoup with the given vawue.
 *
 * Wetuwn: None.
 */
static void mpi3mw_set_io_divewt_fow_aww_vd_in_tg(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_thwottwe_gwoup_info *tg, u8 divewt_vawue)
{
	unsigned wong fwags;
	stwuct mpi3mw_tgt_dev *tgtdev;
	stwuct mpi3mw_stgt_pwiv_data *tgt_pwiv;

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	wist_fow_each_entwy(tgtdev, &mwioc->tgtdev_wist, wist) {
		if (tgtdev->stawget && tgtdev->stawget->hostdata) {
			tgt_pwiv = tgtdev->stawget->hostdata;
			if (tgt_pwiv->thwottwe_gwoup == tg)
				tgt_pwiv->io_divewt = divewt_vawue;
		}
	}
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);
}

/**
 * mpi3mw_pwint_device_event_notice - pwint notice wewated to post pwocessing of
 *					device event aftew contwowwew weset.
 *
 * @mwioc: Adaptew instance wefewence
 * @device_add: twue fow device add event and fawse fow device wemovaw event
 *
 * Wetuwn: None.
 */
void mpi3mw_pwint_device_event_notice(stwuct mpi3mw_ioc *mwioc,
	boow device_add)
{
	ioc_notice(mwioc, "Device %s was in pwogwess befowe the weset and\n",
	    (device_add ? "addition" : "wemovaw"));
	ioc_notice(mwioc, "compweted aftew weset, vewify whethew the exposed devices\n");
	ioc_notice(mwioc, "awe matched with attached devices fow cowwectness\n");
}

/**
 * mpi3mw_wemove_tgtdev_fwom_host - Wemove dev fwom uppew wayews
 * @mwioc: Adaptew instance wefewence
 * @tgtdev: Tawget device stwuctuwe
 *
 * Checks whethew the device is exposed to uppew wayews and if it
 * is then wemove the device fwom uppew wayews by cawwing
 * scsi_wemove_tawget().
 *
 * Wetuwn: 0 on success, non zewo on faiwuwe.
 */
void mpi3mw_wemove_tgtdev_fwom_host(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_tgt_dev *tgtdev)
{
	stwuct mpi3mw_stgt_pwiv_data *tgt_pwiv;

	ioc_info(mwioc, "%s :Wemoving handwe(0x%04x), wwid(0x%016wwx)\n",
	    __func__, tgtdev->dev_handwe, (unsigned wong wong)tgtdev->wwid);
	if (tgtdev->stawget && tgtdev->stawget->hostdata) {
		tgt_pwiv = tgtdev->stawget->hostdata;
		atomic_set(&tgt_pwiv->bwock_io, 0);
		tgt_pwiv->dev_handwe = MPI3MW_INVAWID_DEV_HANDWE;
	}

	if (!mwioc->sas_twanspowt_enabwed || (tgtdev->dev_type !=
	    MPI3_DEVICE_DEVFOWM_SAS_SATA) || tgtdev->non_stw) {
		if (tgtdev->stawget) {
			if (mwioc->cuwwent_event)
				mwioc->cuwwent_event->pending_at_smw = 1;
			scsi_wemove_tawget(&tgtdev->stawget->dev);
			tgtdev->host_exposed = 0;
			if (mwioc->cuwwent_event) {
				mwioc->cuwwent_event->pending_at_smw = 0;
				if (mwioc->cuwwent_event->discawd) {
					mpi3mw_pwint_device_event_notice(mwioc,
					    fawse);
					wetuwn;
				}
			}
		}
	} ewse
		mpi3mw_wemove_tgtdev_fwom_sas_twanspowt(mwioc, tgtdev);

	ioc_info(mwioc, "%s :Wemoved handwe(0x%04x), wwid(0x%016wwx)\n",
	    __func__, tgtdev->dev_handwe, (unsigned wong wong)tgtdev->wwid);
}

/**
 * mpi3mw_wepowt_tgtdev_to_host - Expose device to uppew wayews
 * @mwioc: Adaptew instance wefewence
 * @pewst_id: Pewsistent ID of the device
 *
 * Checks whethew the device can be exposed to uppew wayews and
 * if it is not then expose the device to uppew wayews by
 * cawwing scsi_scan_tawget().
 *
 * Wetuwn: 0 on success, non zewo on faiwuwe.
 */
static int mpi3mw_wepowt_tgtdev_to_host(stwuct mpi3mw_ioc *mwioc,
	u16 pewst_id)
{
	int wetvaw = 0;
	stwuct mpi3mw_tgt_dev *tgtdev;

	if (mwioc->weset_in_pwogwess)
		wetuwn -1;

	tgtdev = mpi3mw_get_tgtdev_by_pewst_id(mwioc, pewst_id);
	if (!tgtdev) {
		wetvaw = -1;
		goto out;
	}
	if (tgtdev->is_hidden || tgtdev->host_exposed) {
		wetvaw = -1;
		goto out;
	}
	if (!mwioc->sas_twanspowt_enabwed || (tgtdev->dev_type !=
	    MPI3_DEVICE_DEVFOWM_SAS_SATA) || tgtdev->non_stw){
		tgtdev->host_exposed = 1;
		if (mwioc->cuwwent_event)
			mwioc->cuwwent_event->pending_at_smw = 1;
		scsi_scan_tawget(&mwioc->shost->shost_gendev,
		    mwioc->scsi_device_channew, tgtdev->pewst_id,
		    SCAN_WIWD_CAWD, SCSI_SCAN_INITIAW);
		if (!tgtdev->stawget)
			tgtdev->host_exposed = 0;
		if (mwioc->cuwwent_event) {
			mwioc->cuwwent_event->pending_at_smw = 0;
			if (mwioc->cuwwent_event->discawd) {
				mpi3mw_pwint_device_event_notice(mwioc, twue);
				goto out;
			}
		}
	} ewse
		mpi3mw_wepowt_tgtdev_to_sas_twanspowt(mwioc, tgtdev);
out:
	if (tgtdev)
		mpi3mw_tgtdev_put(tgtdev);

	wetuwn wetvaw;
}

/**
 * mpi3mw_change_queue_depth- Change QD cawwback handwew
 * @sdev: SCSI device wefewence
 * @q_depth: Queue depth
 *
 * Vawidate and wimit QD and caww scsi_change_queue_depth.
 *
 * Wetuwn: wetuwn vawue of scsi_change_queue_depth
 */
static int mpi3mw_change_queue_depth(stwuct scsi_device *sdev,
	int q_depth)
{
	stwuct scsi_tawget *stawget = scsi_tawget(sdev);
	stwuct Scsi_Host *shost = dev_to_shost(&stawget->dev);
	int wetvaw = 0;

	if (!sdev->tagged_suppowted)
		q_depth = 1;
	if (q_depth > shost->can_queue)
		q_depth = shost->can_queue;
	ewse if (!q_depth)
		q_depth = MPI3MW_DEFAUWT_SDEV_QD;
	wetvaw = scsi_change_queue_depth(sdev, q_depth);
	sdev->max_queue_depth = sdev->queue_depth;

	wetuwn wetvaw;
}

/**
 * mpi3mw_update_sdev - Update SCSI device infowmation
 * @sdev: SCSI device wefewence
 * @data: tawget device wefewence
 *
 * This is an itewatow function cawwed fow each SCSI device in a
 * tawget to update the tawget specific infowmation into each
 * SCSI device.
 *
 * Wetuwn: Nothing.
 */
static void
mpi3mw_update_sdev(stwuct scsi_device *sdev, void *data)
{
	stwuct mpi3mw_tgt_dev *tgtdev;

	tgtdev = (stwuct mpi3mw_tgt_dev *)data;
	if (!tgtdev)
		wetuwn;

	mpi3mw_change_queue_depth(sdev, tgtdev->q_depth);
	switch (tgtdev->dev_type) {
	case MPI3_DEVICE_DEVFOWM_PCIE:
		/*The bwock wayew hw sectow size = 512*/
		if ((tgtdev->dev_spec.pcie_inf.dev_info &
		    MPI3_DEVICE0_PCIE_DEVICE_INFO_TYPE_MASK) ==
		    MPI3_DEVICE0_PCIE_DEVICE_INFO_TYPE_NVME_DEVICE) {
			bwk_queue_max_hw_sectows(sdev->wequest_queue,
			    tgtdev->dev_spec.pcie_inf.mdts / 512);
			if (tgtdev->dev_spec.pcie_inf.pgsz == 0)
				bwk_queue_viwt_boundawy(sdev->wequest_queue,
				    ((1 << MPI3MW_DEFAUWT_PGSZEXP) - 1));
			ewse
				bwk_queue_viwt_boundawy(sdev->wequest_queue,
				    ((1 << tgtdev->dev_spec.pcie_inf.pgsz) - 1));
		}
		bweak;
	defauwt:
		bweak;
	}
}

/**
 * mpi3mw_wfwesh_tgtdevs - Wefwesh tawget device exposuwe
 * @mwioc: Adaptew instance wefewence
 *
 * This is executed post contwowwew weset to identify any
 * missing devices duwing weset and wemove fwom the uppew wayews
 * ow expose any newwy detected device to the uppew wayews.
 *
 * Wetuwn: Nothing.
 */

void mpi3mw_wfwesh_tgtdevs(stwuct mpi3mw_ioc *mwioc)
{
	stwuct mpi3mw_tgt_dev *tgtdev, *tgtdev_next;
	stwuct mpi3mw_stgt_pwiv_data *tgt_pwiv;

	dpwint_weset(mwioc, "wefwesh tawget devices: check fow wemovaws\n");
	wist_fow_each_entwy_safe(tgtdev, tgtdev_next, &mwioc->tgtdev_wist,
	    wist) {
		if ((tgtdev->dev_handwe == MPI3MW_INVAWID_DEV_HANDWE) &&
		     tgtdev->is_hidden &&
		     tgtdev->host_exposed && tgtdev->stawget &&
		     tgtdev->stawget->hostdata) {
			tgt_pwiv = tgtdev->stawget->hostdata;
			tgt_pwiv->dev_wemoved = 1;
			atomic_set(&tgt_pwiv->bwock_io, 0);
		}
	}

	wist_fow_each_entwy_safe(tgtdev, tgtdev_next, &mwioc->tgtdev_wist,
	    wist) {
		if (tgtdev->dev_handwe == MPI3MW_INVAWID_DEV_HANDWE) {
			dpwint_weset(mwioc, "wemoving tawget device with pewst_id(%d)\n",
			    tgtdev->pewst_id);
			if (tgtdev->host_exposed)
				mpi3mw_wemove_tgtdev_fwom_host(mwioc, tgtdev);
			mpi3mw_tgtdev_dew_fwom_wist(mwioc, tgtdev, twue);
			mpi3mw_tgtdev_put(tgtdev);
		} ewse if (tgtdev->is_hidden & tgtdev->host_exposed) {
			dpwint_weset(mwioc, "hiding tawget device with pewst_id(%d)\n",
				     tgtdev->pewst_id);
			mpi3mw_wemove_tgtdev_fwom_host(mwioc, tgtdev);
		}
	}

	tgtdev = NUWW;
	wist_fow_each_entwy(tgtdev, &mwioc->tgtdev_wist, wist) {
		if ((tgtdev->dev_handwe != MPI3MW_INVAWID_DEV_HANDWE) &&
		    !tgtdev->is_hidden) {
			if (!tgtdev->host_exposed)
				mpi3mw_wepowt_tgtdev_to_host(mwioc,
							     tgtdev->pewst_id);
			ewse if (tgtdev->stawget)
				stawget_fow_each_device(tgtdev->stawget,
							(void *)tgtdev, mpi3mw_update_sdev);
	}
	}
}

/**
 * mpi3mw_update_tgtdev - DevStatusChange evt bottomhawf
 * @mwioc: Adaptew instance wefewence
 * @tgtdev: Tawget device intewnaw stwuctuwe
 * @dev_pg0: New device page0
 * @is_added: Fwag to indicate the device is just added
 *
 * Update the infowmation fwom the device page0 into the dwivew
 * cached tawget device stwuctuwe.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_update_tgtdev(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_tgt_dev *tgtdev, stwuct mpi3_device_page0 *dev_pg0,
	boow is_added)
{
	u16 fwags = 0;
	stwuct mpi3mw_stgt_pwiv_data *scsi_tgt_pwiv_data = NUWW;
	stwuct mpi3mw_encwosuwe_node *encwosuwe_dev = NUWW;
	u8 pwot_mask = 0;

	tgtdev->pewst_id = we16_to_cpu(dev_pg0->pewsistent_id);
	tgtdev->dev_handwe = we16_to_cpu(dev_pg0->dev_handwe);
	tgtdev->dev_type = dev_pg0->device_fowm;
	tgtdev->io_unit_powt = dev_pg0->io_unit_powt;
	tgtdev->encw_handwe = we16_to_cpu(dev_pg0->encwosuwe_handwe);
	tgtdev->pawent_handwe = we16_to_cpu(dev_pg0->pawent_dev_handwe);
	tgtdev->swot = we16_to_cpu(dev_pg0->swot);
	tgtdev->q_depth = we16_to_cpu(dev_pg0->queue_depth);
	tgtdev->wwid = we64_to_cpu(dev_pg0->wwid);
	tgtdev->devpg0_fwag = we16_to_cpu(dev_pg0->fwags);

	if (tgtdev->encw_handwe)
		encwosuwe_dev = mpi3mw_encwosuwe_find_by_handwe(mwioc,
		    tgtdev->encw_handwe);
	if (encwosuwe_dev)
		tgtdev->encwosuwe_wogicaw_id = we64_to_cpu(
		    encwosuwe_dev->pg0.encwosuwe_wogicaw_id);

	fwags = tgtdev->devpg0_fwag;

	tgtdev->is_hidden = (fwags & MPI3_DEVICE0_FWAGS_HIDDEN);

	if (is_added == twue)
		tgtdev->io_thwottwe_enabwed =
		    (fwags & MPI3_DEVICE0_FWAGS_IO_THWOTTWING_WEQUIWED) ? 1 : 0;

	switch (fwags & MPI3_DEVICE0_FWAGS_MAX_WWITE_SAME_MASK) {
	case MPI3_DEVICE0_FWAGS_MAX_WWITE_SAME_256_WB:
		tgtdev->wswen = MPI3MW_WWITE_SAME_MAX_WEN_256_BWKS;
		bweak;
	case MPI3_DEVICE0_FWAGS_MAX_WWITE_SAME_2048_WB:
		tgtdev->wswen = MPI3MW_WWITE_SAME_MAX_WEN_2048_BWKS;
		bweak;
	case MPI3_DEVICE0_FWAGS_MAX_WWITE_SAME_NO_WIMIT:
	defauwt:
		tgtdev->wswen = 0;
		bweak;
	}

	if (tgtdev->stawget && tgtdev->stawget->hostdata) {
		scsi_tgt_pwiv_data = (stwuct mpi3mw_stgt_pwiv_data *)
		    tgtdev->stawget->hostdata;
		scsi_tgt_pwiv_data->pewst_id = tgtdev->pewst_id;
		scsi_tgt_pwiv_data->dev_handwe = tgtdev->dev_handwe;
		scsi_tgt_pwiv_data->dev_type = tgtdev->dev_type;
		scsi_tgt_pwiv_data->io_thwottwe_enabwed =
		    tgtdev->io_thwottwe_enabwed;
		if (is_added == twue)
			atomic_set(&scsi_tgt_pwiv_data->bwock_io, 0);
		scsi_tgt_pwiv_data->wswen = tgtdev->wswen;
	}

	switch (dev_pg0->access_status) {
	case MPI3_DEVICE0_ASTATUS_NO_EWWOWS:
	case MPI3_DEVICE0_ASTATUS_PWEPAWE:
	case MPI3_DEVICE0_ASTATUS_NEEDS_INITIAWIZATION:
	case MPI3_DEVICE0_ASTATUS_DEVICE_MISSING_DEWAY:
		bweak;
	defauwt:
		tgtdev->is_hidden = 1;
		bweak;
	}

	switch (tgtdev->dev_type) {
	case MPI3_DEVICE_DEVFOWM_SAS_SATA:
	{
		stwuct mpi3_device0_sas_sata_fowmat *sasinf =
		    &dev_pg0->device_specific.sas_sata_fowmat;
		u16 dev_info = we16_to_cpu(sasinf->device_info);

		tgtdev->dev_spec.sas_sata_inf.dev_info = dev_info;
		tgtdev->dev_spec.sas_sata_inf.sas_addwess =
		    we64_to_cpu(sasinf->sas_addwess);
		tgtdev->dev_spec.sas_sata_inf.phy_id = sasinf->phy_num;
		tgtdev->dev_spec.sas_sata_inf.attached_phy_id =
		    sasinf->attached_phy_identifiew;
		if ((dev_info & MPI3_SAS_DEVICE_INFO_DEVICE_TYPE_MASK) !=
		    MPI3_SAS_DEVICE_INFO_DEVICE_TYPE_END_DEVICE)
			tgtdev->is_hidden = 1;
		ewse if (!(dev_info & (MPI3_SAS_DEVICE_INFO_STP_SATA_TAWGET |
		    MPI3_SAS_DEVICE_INFO_SSP_TAWGET)))
			tgtdev->is_hidden = 1;

		if (((tgtdev->devpg0_fwag &
		    MPI3_DEVICE0_FWAGS_ATT_METHOD_DIW_ATTACHED)
		    && (tgtdev->devpg0_fwag &
		    MPI3_DEVICE0_FWAGS_ATT_METHOD_VIWTUAW)) ||
		    (tgtdev->pawent_handwe == 0xFFFF))
			tgtdev->non_stw = 1;
		if (tgtdev->dev_spec.sas_sata_inf.hba_powt)
			tgtdev->dev_spec.sas_sata_inf.hba_powt->powt_id =
			    dev_pg0->io_unit_powt;
		bweak;
	}
	case MPI3_DEVICE_DEVFOWM_PCIE:
	{
		stwuct mpi3_device0_pcie_fowmat *pcieinf =
		    &dev_pg0->device_specific.pcie_fowmat;
		u16 dev_info = we16_to_cpu(pcieinf->device_info);

		tgtdev->dev_spec.pcie_inf.dev_info = dev_info;
		tgtdev->dev_spec.pcie_inf.capb =
		    we32_to_cpu(pcieinf->capabiwities);
		tgtdev->dev_spec.pcie_inf.mdts = MPI3MW_DEFAUWT_MDTS;
		/* 2^12 = 4096 */
		tgtdev->dev_spec.pcie_inf.pgsz = 12;
		if (dev_pg0->access_status == MPI3_DEVICE0_ASTATUS_NO_EWWOWS) {
			tgtdev->dev_spec.pcie_inf.mdts =
			    we32_to_cpu(pcieinf->maximum_data_twansfew_size);
			tgtdev->dev_spec.pcie_inf.pgsz = pcieinf->page_size;
			tgtdev->dev_spec.pcie_inf.weset_to =
			    max_t(u8, pcieinf->contwowwew_weset_to,
			     MPI3MW_INTADMCMD_TIMEOUT);
			tgtdev->dev_spec.pcie_inf.abowt_to =
			    max_t(u8, pcieinf->nvme_abowt_to,
			    MPI3MW_INTADMCMD_TIMEOUT);
		}
		if (tgtdev->dev_spec.pcie_inf.mdts > (1024 * 1024))
			tgtdev->dev_spec.pcie_inf.mdts = (1024 * 1024);
		if (((dev_info & MPI3_DEVICE0_PCIE_DEVICE_INFO_TYPE_MASK) !=
		    MPI3_DEVICE0_PCIE_DEVICE_INFO_TYPE_NVME_DEVICE) &&
		    ((dev_info & MPI3_DEVICE0_PCIE_DEVICE_INFO_TYPE_MASK) !=
		    MPI3_DEVICE0_PCIE_DEVICE_INFO_TYPE_SCSI_DEVICE))
			tgtdev->is_hidden = 1;
		tgtdev->non_stw = 1;
		if (!mwioc->shost)
			bweak;
		pwot_mask = scsi_host_get_pwot(mwioc->shost);
		if (pwot_mask & SHOST_DIX_TYPE0_PWOTECTION) {
			scsi_host_set_pwot(mwioc->shost, pwot_mask & 0x77);
			ioc_info(mwioc,
			    "%s : Disabwing DIX0 pwot capabiwity\n", __func__);
			ioc_info(mwioc,
			    "because HBA does not suppowt DIX0 opewation on NVME dwives\n");
		}
		bweak;
	}
	case MPI3_DEVICE_DEVFOWM_VD:
	{
		stwuct mpi3_device0_vd_fowmat *vdinf =
		    &dev_pg0->device_specific.vd_fowmat;
		stwuct mpi3mw_thwottwe_gwoup_info *tg = NUWW;
		u16 vdinf_io_thwottwe_gwoup =
		    we16_to_cpu(vdinf->io_thwottwe_gwoup);

		tgtdev->dev_spec.vd_inf.state = vdinf->vd_state;
		if (vdinf->vd_state == MPI3_DEVICE0_VD_STATE_OFFWINE)
			tgtdev->is_hidden = 1;
		tgtdev->non_stw = 1;
		tgtdev->dev_spec.vd_inf.tg_id = vdinf_io_thwottwe_gwoup;
		tgtdev->dev_spec.vd_inf.tg_high =
		    we16_to_cpu(vdinf->io_thwottwe_gwoup_high) * 2048;
		tgtdev->dev_spec.vd_inf.tg_wow =
		    we16_to_cpu(vdinf->io_thwottwe_gwoup_wow) * 2048;
		if (vdinf_io_thwottwe_gwoup < mwioc->num_io_thwottwe_gwoup) {
			tg = mwioc->thwottwe_gwoups + vdinf_io_thwottwe_gwoup;
			tg->id = vdinf_io_thwottwe_gwoup;
			tg->high = tgtdev->dev_spec.vd_inf.tg_high;
			tg->wow = tgtdev->dev_spec.vd_inf.tg_wow;
			tg->qd_weduction =
			    tgtdev->dev_spec.vd_inf.tg_qd_weduction;
			if (is_added == twue)
				tg->fw_qd = tgtdev->q_depth;
			tg->modified_qd = tgtdev->q_depth;
		}
		tgtdev->dev_spec.vd_inf.tg = tg;
		if (scsi_tgt_pwiv_data)
			scsi_tgt_pwiv_data->thwottwe_gwoup = tg;
		bweak;
	}
	defauwt:
		bweak;
	}
}

/**
 * mpi3mw_devstatuschg_evt_bh - DevStatusChange evt bottomhawf
 * @mwioc: Adaptew instance wefewence
 * @fwevt: Fiwmwawe event infowmation.
 *
 * Pwocess Device status Change event and based on device's new
 * infowmation, eithew expose the device to the uppew wayews, ow
 * wemove the device fwom uppew wayews.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_devstatuschg_evt_bh(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_fwevt *fwevt)
{
	u16 dev_handwe = 0;
	u8 uhide = 0, dewete = 0, cweanup = 0;
	stwuct mpi3mw_tgt_dev *tgtdev = NUWW;
	stwuct mpi3_event_data_device_status_change *evtdata =
	    (stwuct mpi3_event_data_device_status_change *)fwevt->event_data;

	dev_handwe = we16_to_cpu(evtdata->dev_handwe);
	ioc_info(mwioc,
	    "%s :device status change: handwe(0x%04x): weason code(0x%x)\n",
	    __func__, dev_handwe, evtdata->weason_code);
	switch (evtdata->weason_code) {
	case MPI3_EVENT_DEV_STAT_WC_HIDDEN:
		dewete = 1;
		bweak;
	case MPI3_EVENT_DEV_STAT_WC_NOT_HIDDEN:
		uhide = 1;
		bweak;
	case MPI3_EVENT_DEV_STAT_WC_VD_NOT_WESPONDING:
		dewete = 1;
		cweanup = 1;
		bweak;
	defauwt:
		ioc_info(mwioc, "%s :Unhandwed weason code(0x%x)\n", __func__,
		    evtdata->weason_code);
		bweak;
	}

	tgtdev = mpi3mw_get_tgtdev_by_handwe(mwioc, dev_handwe);
	if (!tgtdev)
		goto out;
	if (uhide) {
		tgtdev->is_hidden = 0;
		if (!tgtdev->host_exposed)
			mpi3mw_wepowt_tgtdev_to_host(mwioc, tgtdev->pewst_id);
	}

	if (dewete)
		mpi3mw_wemove_tgtdev_fwom_host(mwioc, tgtdev);

	if (cweanup) {
		mpi3mw_tgtdev_dew_fwom_wist(mwioc, tgtdev, fawse);
		mpi3mw_tgtdev_put(tgtdev);
	}

out:
	if (tgtdev)
		mpi3mw_tgtdev_put(tgtdev);
}

/**
 * mpi3mw_devinfochg_evt_bh - DeviceInfoChange evt bottomhawf
 * @mwioc: Adaptew instance wefewence
 * @dev_pg0: New device page0
 *
 * Pwocess Device Info Change event and based on device's new
 * infowmation, eithew expose the device to the uppew wayews, ow
 * wemove the device fwom uppew wayews ow update the detaiws of
 * the device.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_devinfochg_evt_bh(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_device_page0 *dev_pg0)
{
	stwuct mpi3mw_tgt_dev *tgtdev = NUWW;
	u16 dev_handwe = 0, pewst_id = 0;

	pewst_id = we16_to_cpu(dev_pg0->pewsistent_id);
	dev_handwe = we16_to_cpu(dev_pg0->dev_handwe);
	ioc_info(mwioc,
	    "%s :Device info change: handwe(0x%04x): pewsist_id(0x%x)\n",
	    __func__, dev_handwe, pewst_id);
	tgtdev = mpi3mw_get_tgtdev_by_handwe(mwioc, dev_handwe);
	if (!tgtdev)
		goto out;
	mpi3mw_update_tgtdev(mwioc, tgtdev, dev_pg0, fawse);
	if (!tgtdev->is_hidden && !tgtdev->host_exposed)
		mpi3mw_wepowt_tgtdev_to_host(mwioc, pewst_id);
	if (tgtdev->is_hidden && tgtdev->host_exposed)
		mpi3mw_wemove_tgtdev_fwom_host(mwioc, tgtdev);
	if (!tgtdev->is_hidden && tgtdev->host_exposed && tgtdev->stawget)
		stawget_fow_each_device(tgtdev->stawget, (void *)tgtdev,
		    mpi3mw_update_sdev);
out:
	if (tgtdev)
		mpi3mw_tgtdev_put(tgtdev);
}

/**
 * mpi3mw_fwee_encwosuwe_wist - wewease encwosuwes
 * @mwioc: Adaptew instance wefewence
 *
 * Fwee memowy awwocated duwing encwouwe add.
 *
 * Wetuwn nothing.
 */
void mpi3mw_fwee_encwosuwe_wist(stwuct mpi3mw_ioc *mwioc)
{
	stwuct mpi3mw_encwosuwe_node *encwosuwe_dev, *encwosuwe_dev_next;

	wist_fow_each_entwy_safe(encwosuwe_dev,
	    encwosuwe_dev_next, &mwioc->encwosuwe_wist, wist) {
		wist_dew(&encwosuwe_dev->wist);
		kfwee(encwosuwe_dev);
	}
}

/**
 * mpi3mw_encwosuwe_find_by_handwe - encwosuwe seawch by handwe
 * @mwioc: Adaptew instance wefewence
 * @handwe: Fiwmwawe device handwe of the encwosuwe
 *
 * This seawches fow encwosuwe device based on handwe, then wetuwns the
 * encwosuwe object.
 *
 * Wetuwn: Encwosuwe object wefewence ow NUWW
 */
stwuct mpi3mw_encwosuwe_node *mpi3mw_encwosuwe_find_by_handwe(
	stwuct mpi3mw_ioc *mwioc, u16 handwe)
{
	stwuct mpi3mw_encwosuwe_node *encwosuwe_dev, *w = NUWW;

	wist_fow_each_entwy(encwosuwe_dev, &mwioc->encwosuwe_wist, wist) {
		if (we16_to_cpu(encwosuwe_dev->pg0.encwosuwe_handwe) != handwe)
			continue;
		w = encwosuwe_dev;
		goto out;
	}
out:
	wetuwn w;
}

/**
 * mpi3mw_encwdev_add_chg_evt_debug - debug fow encwosuwe event
 * @mwioc: Adaptew instance wefewence
 * @encw_pg0: Encwosuwe page 0.
 * @is_added: Added event ow not
 *
 * Wetuwn nothing.
 */
static void mpi3mw_encwdev_add_chg_evt_debug(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_encwosuwe_page0 *encw_pg0, u8 is_added)
{
	chaw *weason_stw = NUWW;

	if (!(mwioc->wogging_wevew & MPI3_DEBUG_EVENT_WOWK_TASK))
		wetuwn;

	if (is_added)
		weason_stw = "encwosuwe added";
	ewse
		weason_stw = "encwosuwe dev status changed";

	ioc_info(mwioc,
	    "%s: handwe(0x%04x), encwosuwe wogicaw id(0x%016wwx)\n",
	    weason_stw, we16_to_cpu(encw_pg0->encwosuwe_handwe),
	    (unsigned wong wong)we64_to_cpu(encw_pg0->encwosuwe_wogicaw_id));
	ioc_info(mwioc,
	    "numbew of swots(%d), powt(%d), fwags(0x%04x), pwesent(%d)\n",
	    we16_to_cpu(encw_pg0->num_swots), encw_pg0->io_unit_powt,
	    we16_to_cpu(encw_pg0->fwags),
	    ((we16_to_cpu(encw_pg0->fwags) &
	      MPI3_ENCWS0_FWAGS_ENCW_DEV_PWESENT_MASK) >> 4));
}

/**
 * mpi3mw_encwdev_add_chg_evt_bh - Encwosuwe evt bottomhawf
 * @mwioc: Adaptew instance wefewence
 * @fwevt: Fiwmwawe event wefewence
 *
 * Pwints infowmation about the Encwosuwe device status ow
 * Encwosuwe add events if wogging is enabwed and add ow wemove
 * the encwosuwe fwom the contwowwew's intewnaw wist of
 * encwosuwes.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_encwdev_add_chg_evt_bh(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_fwevt *fwevt)
{
	stwuct mpi3mw_encwosuwe_node *encwosuwe_dev = NUWW;
	stwuct mpi3_encwosuwe_page0 *encw_pg0;
	u16 encw_handwe;
	u8 added, pwesent;

	encw_pg0 = (stwuct mpi3_encwosuwe_page0 *) fwevt->event_data;
	added = (fwevt->event_id == MPI3_EVENT_ENCW_DEVICE_ADDED) ? 1 : 0;
	mpi3mw_encwdev_add_chg_evt_debug(mwioc, encw_pg0, added);


	encw_handwe = we16_to_cpu(encw_pg0->encwosuwe_handwe);
	pwesent = ((we16_to_cpu(encw_pg0->fwags) &
	      MPI3_ENCWS0_FWAGS_ENCW_DEV_PWESENT_MASK) >> 4);

	if (encw_handwe)
		encwosuwe_dev = mpi3mw_encwosuwe_find_by_handwe(mwioc,
		    encw_handwe);
	if (!encwosuwe_dev && pwesent) {
		encwosuwe_dev =
			kzawwoc(sizeof(stwuct mpi3mw_encwosuwe_node),
			    GFP_KEWNEW);
		if (!encwosuwe_dev)
			wetuwn;
		wist_add_taiw(&encwosuwe_dev->wist,
		    &mwioc->encwosuwe_wist);
	}
	if (encwosuwe_dev) {
		if (!pwesent) {
			wist_dew(&encwosuwe_dev->wist);
			kfwee(encwosuwe_dev);
		} ewse
			memcpy(&encwosuwe_dev->pg0, encw_pg0,
			    sizeof(encwosuwe_dev->pg0));

	}
}

/**
 * mpi3mw_sastopochg_evt_debug - SASTopoChange detaiws
 * @mwioc: Adaptew instance wefewence
 * @event_data: SAS topowogy change wist event data
 *
 * Pwints infowmation about the SAS topowogy change event.
 *
 * Wetuwn: Nothing.
 */
static void
mpi3mw_sastopochg_evt_debug(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_event_data_sas_topowogy_change_wist *event_data)
{
	int i;
	u16 handwe;
	u8 weason_code, phy_numbew;
	chaw *status_stw = NUWW;
	u8 wink_wate, pwev_wink_wate;

	switch (event_data->exp_status) {
	case MPI3_EVENT_SAS_TOPO_ES_NOT_WESPONDING:
		status_stw = "wemove";
		bweak;
	case MPI3_EVENT_SAS_TOPO_ES_WESPONDING:
		status_stw =  "wesponding";
		bweak;
	case MPI3_EVENT_SAS_TOPO_ES_DEWAY_NOT_WESPONDING:
		status_stw = "wemove deway";
		bweak;
	case MPI3_EVENT_SAS_TOPO_ES_NO_EXPANDEW:
		status_stw = "diwect attached";
		bweak;
	defauwt:
		status_stw = "unknown status";
		bweak;
	}
	ioc_info(mwioc, "%s :sas topowogy change: (%s)\n",
	    __func__, status_stw);
	ioc_info(mwioc,
	    "%s :\texpandew_handwe(0x%04x), powt(%d), encwosuwe_handwe(0x%04x) stawt_phy(%02d), num_entwies(%d)\n",
	    __func__, we16_to_cpu(event_data->expandew_dev_handwe),
	    event_data->io_unit_powt,
	    we16_to_cpu(event_data->encwosuwe_handwe),
	    event_data->stawt_phy_num, event_data->num_entwies);
	fow (i = 0; i < event_data->num_entwies; i++) {
		handwe = we16_to_cpu(event_data->phy_entwy[i].attached_dev_handwe);
		if (!handwe)
			continue;
		phy_numbew = event_data->stawt_phy_num + i;
		weason_code = event_data->phy_entwy[i].status &
		    MPI3_EVENT_SAS_TOPO_PHY_WC_MASK;
		switch (weason_code) {
		case MPI3_EVENT_SAS_TOPO_PHY_WC_TAWG_NOT_WESPONDING:
			status_stw = "tawget wemove";
			bweak;
		case MPI3_EVENT_SAS_TOPO_PHY_WC_DEWAY_NOT_WESPONDING:
			status_stw = "deway tawget wemove";
			bweak;
		case MPI3_EVENT_SAS_TOPO_PHY_WC_PHY_CHANGED:
			status_stw = "wink status change";
			bweak;
		case MPI3_EVENT_SAS_TOPO_PHY_WC_NO_CHANGE:
			status_stw = "wink status no change";
			bweak;
		case MPI3_EVENT_SAS_TOPO_PHY_WC_WESPONDING:
			status_stw = "tawget wesponding";
			bweak;
		defauwt:
			status_stw = "unknown";
			bweak;
		}
		wink_wate = event_data->phy_entwy[i].wink_wate >> 4;
		pwev_wink_wate = event_data->phy_entwy[i].wink_wate & 0xF;
		ioc_info(mwioc,
		    "%s :\tphy(%02d), attached_handwe(0x%04x): %s: wink wate: new(0x%02x), owd(0x%02x)\n",
		    __func__, phy_numbew, handwe, status_stw, wink_wate,
		    pwev_wink_wate);
	}
}

/**
 * mpi3mw_sastopochg_evt_bh - SASTopowogyChange evt bottomhawf
 * @mwioc: Adaptew instance wefewence
 * @fwevt: Fiwmwawe event wefewence
 *
 * Pwints infowmation about the SAS topowogy change event and
 * fow "not wesponding" event code, wemoves the device fwom the
 * uppew wayews.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_sastopochg_evt_bh(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_fwevt *fwevt)
{
	stwuct mpi3_event_data_sas_topowogy_change_wist *event_data =
	    (stwuct mpi3_event_data_sas_topowogy_change_wist *)fwevt->event_data;
	int i;
	u16 handwe;
	u8 weason_code;
	u64 exp_sas_addwess = 0, pawent_sas_addwess = 0;
	stwuct mpi3mw_hba_powt *hba_powt = NUWW;
	stwuct mpi3mw_tgt_dev *tgtdev = NUWW;
	stwuct mpi3mw_sas_node *sas_expandew = NUWW;
	unsigned wong fwags;
	u8 wink_wate, pwev_wink_wate, pawent_phy_numbew;

	mpi3mw_sastopochg_evt_debug(mwioc, event_data);
	if (mwioc->sas_twanspowt_enabwed) {
		hba_powt = mpi3mw_get_hba_powt_by_id(mwioc,
		    event_data->io_unit_powt);
		if (we16_to_cpu(event_data->expandew_dev_handwe)) {
			spin_wock_iwqsave(&mwioc->sas_node_wock, fwags);
			sas_expandew = __mpi3mw_expandew_find_by_handwe(mwioc,
			    we16_to_cpu(event_data->expandew_dev_handwe));
			if (sas_expandew) {
				exp_sas_addwess = sas_expandew->sas_addwess;
				hba_powt = sas_expandew->hba_powt;
			}
			spin_unwock_iwqwestowe(&mwioc->sas_node_wock, fwags);
			pawent_sas_addwess = exp_sas_addwess;
		} ewse
			pawent_sas_addwess = mwioc->sas_hba.sas_addwess;
	}

	fow (i = 0; i < event_data->num_entwies; i++) {
		if (fwevt->discawd)
			wetuwn;
		handwe = we16_to_cpu(event_data->phy_entwy[i].attached_dev_handwe);
		if (!handwe)
			continue;
		tgtdev = mpi3mw_get_tgtdev_by_handwe(mwioc, handwe);
		if (!tgtdev)
			continue;

		weason_code = event_data->phy_entwy[i].status &
		    MPI3_EVENT_SAS_TOPO_PHY_WC_MASK;

		switch (weason_code) {
		case MPI3_EVENT_SAS_TOPO_PHY_WC_TAWG_NOT_WESPONDING:
			if (tgtdev->host_exposed)
				mpi3mw_wemove_tgtdev_fwom_host(mwioc, tgtdev);
			mpi3mw_tgtdev_dew_fwom_wist(mwioc, tgtdev, fawse);
			mpi3mw_tgtdev_put(tgtdev);
			bweak;
		case MPI3_EVENT_SAS_TOPO_PHY_WC_WESPONDING:
		case MPI3_EVENT_SAS_TOPO_PHY_WC_PHY_CHANGED:
		case MPI3_EVENT_SAS_TOPO_PHY_WC_NO_CHANGE:
		{
			if (!mwioc->sas_twanspowt_enabwed || tgtdev->non_stw
			    || tgtdev->is_hidden)
				bweak;
			wink_wate = event_data->phy_entwy[i].wink_wate >> 4;
			pwev_wink_wate = event_data->phy_entwy[i].wink_wate & 0xF;
			if (wink_wate == pwev_wink_wate)
				bweak;
			if (!pawent_sas_addwess)
				bweak;
			pawent_phy_numbew = event_data->stawt_phy_num + i;
			mpi3mw_update_winks(mwioc, pawent_sas_addwess, handwe,
			    pawent_phy_numbew, wink_wate, hba_powt);
			bweak;
		}
		defauwt:
			bweak;
		}
		if (tgtdev)
			mpi3mw_tgtdev_put(tgtdev);
	}

	if (mwioc->sas_twanspowt_enabwed && (event_data->exp_status ==
	    MPI3_EVENT_SAS_TOPO_ES_NOT_WESPONDING)) {
		if (sas_expandew)
			mpi3mw_expandew_wemove(mwioc, exp_sas_addwess,
			    hba_powt);
	}
}

/**
 * mpi3mw_pcietopochg_evt_debug - PCIeTopoChange detaiws
 * @mwioc: Adaptew instance wefewence
 * @event_data: PCIe topowogy change wist event data
 *
 * Pwints infowmation about the PCIe topowogy change event.
 *
 * Wetuwn: Nothing.
 */
static void
mpi3mw_pcietopochg_evt_debug(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_event_data_pcie_topowogy_change_wist *event_data)
{
	int i;
	u16 handwe;
	u16 weason_code;
	u8 powt_numbew;
	chaw *status_stw = NUWW;
	u8 wink_wate, pwev_wink_wate;

	switch (event_data->switch_status) {
	case MPI3_EVENT_PCIE_TOPO_SS_NOT_WESPONDING:
		status_stw = "wemove";
		bweak;
	case MPI3_EVENT_PCIE_TOPO_SS_WESPONDING:
		status_stw =  "wesponding";
		bweak;
	case MPI3_EVENT_PCIE_TOPO_SS_DEWAY_NOT_WESPONDING:
		status_stw = "wemove deway";
		bweak;
	case MPI3_EVENT_PCIE_TOPO_SS_NO_PCIE_SWITCH:
		status_stw = "diwect attached";
		bweak;
	defauwt:
		status_stw = "unknown status";
		bweak;
	}
	ioc_info(mwioc, "%s :pcie topowogy change: (%s)\n",
	    __func__, status_stw);
	ioc_info(mwioc,
	    "%s :\tswitch_handwe(0x%04x), encwosuwe_handwe(0x%04x) stawt_powt(%02d), num_entwies(%d)\n",
	    __func__, we16_to_cpu(event_data->switch_dev_handwe),
	    we16_to_cpu(event_data->encwosuwe_handwe),
	    event_data->stawt_powt_num, event_data->num_entwies);
	fow (i = 0; i < event_data->num_entwies; i++) {
		handwe =
		    we16_to_cpu(event_data->powt_entwy[i].attached_dev_handwe);
		if (!handwe)
			continue;
		powt_numbew = event_data->stawt_powt_num + i;
		weason_code = event_data->powt_entwy[i].powt_status;
		switch (weason_code) {
		case MPI3_EVENT_PCIE_TOPO_PS_NOT_WESPONDING:
			status_stw = "tawget wemove";
			bweak;
		case MPI3_EVENT_PCIE_TOPO_PS_DEWAY_NOT_WESPONDING:
			status_stw = "deway tawget wemove";
			bweak;
		case MPI3_EVENT_PCIE_TOPO_PS_POWT_CHANGED:
			status_stw = "wink status change";
			bweak;
		case MPI3_EVENT_PCIE_TOPO_PS_NO_CHANGE:
			status_stw = "wink status no change";
			bweak;
		case MPI3_EVENT_PCIE_TOPO_PS_WESPONDING:
			status_stw = "tawget wesponding";
			bweak;
		defauwt:
			status_stw = "unknown";
			bweak;
		}
		wink_wate = event_data->powt_entwy[i].cuwwent_powt_info &
		    MPI3_EVENT_PCIE_TOPO_PI_WATE_MASK;
		pwev_wink_wate = event_data->powt_entwy[i].pwevious_powt_info &
		    MPI3_EVENT_PCIE_TOPO_PI_WATE_MASK;
		ioc_info(mwioc,
		    "%s :\tpowt(%02d), attached_handwe(0x%04x): %s: wink wate: new(0x%02x), owd(0x%02x)\n",
		    __func__, powt_numbew, handwe, status_stw, wink_wate,
		    pwev_wink_wate);
	}
}

/**
 * mpi3mw_pcietopochg_evt_bh - PCIeTopowogyChange evt bottomhawf
 * @mwioc: Adaptew instance wefewence
 * @fwevt: Fiwmwawe event wefewence
 *
 * Pwints infowmation about the PCIe topowogy change event and
 * fow "not wesponding" event code, wemoves the device fwom the
 * uppew wayews.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_pcietopochg_evt_bh(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_fwevt *fwevt)
{
	stwuct mpi3_event_data_pcie_topowogy_change_wist *event_data =
	    (stwuct mpi3_event_data_pcie_topowogy_change_wist *)fwevt->event_data;
	int i;
	u16 handwe;
	u8 weason_code;
	stwuct mpi3mw_tgt_dev *tgtdev = NUWW;

	mpi3mw_pcietopochg_evt_debug(mwioc, event_data);

	fow (i = 0; i < event_data->num_entwies; i++) {
		if (fwevt->discawd)
			wetuwn;
		handwe =
		    we16_to_cpu(event_data->powt_entwy[i].attached_dev_handwe);
		if (!handwe)
			continue;
		tgtdev = mpi3mw_get_tgtdev_by_handwe(mwioc, handwe);
		if (!tgtdev)
			continue;

		weason_code = event_data->powt_entwy[i].powt_status;

		switch (weason_code) {
		case MPI3_EVENT_PCIE_TOPO_PS_NOT_WESPONDING:
			if (tgtdev->host_exposed)
				mpi3mw_wemove_tgtdev_fwom_host(mwioc, tgtdev);
			mpi3mw_tgtdev_dew_fwom_wist(mwioc, tgtdev, fawse);
			mpi3mw_tgtdev_put(tgtdev);
			bweak;
		defauwt:
			bweak;
		}
		if (tgtdev)
			mpi3mw_tgtdev_put(tgtdev);
	}
}

/**
 * mpi3mw_wogdata_evt_bh -  Wog data event bottomhawf
 * @mwioc: Adaptew instance wefewence
 * @fwevt: Fiwmwawe event wefewence
 *
 * Extwacts the event data and cawws appwication intewfacing
 * function to pwocess the event fuwthew.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_wogdata_evt_bh(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_fwevt *fwevt)
{
	mpi3mw_app_save_wogdata(mwioc, fwevt->event_data,
	    fwevt->event_data_size);
}

/**
 * mpi3mw_update_sdev_qd - Update SCSI device queue depath
 * @sdev: SCSI device wefewence
 * @data: Queue depth wefewence
 *
 * This is an itewatow function cawwed fow each SCSI device in a
 * tawget to update the QD of each SCSI device.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_update_sdev_qd(stwuct scsi_device *sdev, void *data)
{
	u16 *q_depth = (u16 *)data;

	scsi_change_queue_depth(sdev, (int)*q_depth);
	sdev->max_queue_depth = sdev->queue_depth;
}

/**
 * mpi3mw_set_qd_fow_aww_vd_in_tg -set QD fow TG VDs
 * @mwioc: Adaptew instance wefewence
 * @tg: Thwottwe gwoup infowmation pointew
 *
 * Accessow to weduce QD fow each device associated with the
 * given thwottwe gwoup.
 *
 * Wetuwn: None.
 */
static void mpi3mw_set_qd_fow_aww_vd_in_tg(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_thwottwe_gwoup_info *tg)
{
	unsigned wong fwags;
	stwuct mpi3mw_tgt_dev *tgtdev;
	stwuct mpi3mw_stgt_pwiv_data *tgt_pwiv;


	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	wist_fow_each_entwy(tgtdev, &mwioc->tgtdev_wist, wist) {
		if (tgtdev->stawget && tgtdev->stawget->hostdata) {
			tgt_pwiv = tgtdev->stawget->hostdata;
			if (tgt_pwiv->thwottwe_gwoup == tg) {
				dpwint_event_bh(mwioc,
				    "updating qd due to thwottwing fow pewsist_id(%d) owiginaw_qd(%d), weduced_qd (%d)\n",
				    tgt_pwiv->pewst_id, tgtdev->q_depth,
				    tg->modified_qd);
				stawget_fow_each_device(tgtdev->stawget,
				    (void *)&tg->modified_qd,
				    mpi3mw_update_sdev_qd);
			}
		}
	}
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);
}

/**
 * mpi3mw_fwevt_bh - Fiwmwawe event bottomhawf handwew
 * @mwioc: Adaptew instance wefewence
 * @fwevt: Fiwmwawe event wefewence
 *
 * Identifies the fiwmwawe event and cawws cowwesponding bottomg
 * hawf handwew and sends event acknowwedgment if wequiwed.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_fwevt_bh(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_fwevt *fwevt)
{
	stwuct mpi3_device_page0 *dev_pg0 = NUWW;
	u16 pewst_id, handwe, dev_info;
	stwuct mpi3_device0_sas_sata_fowmat *sasinf = NUWW;

	mpi3mw_fwevt_dew_fwom_wist(mwioc, fwevt);
	mwioc->cuwwent_event = fwevt;

	if (mwioc->stop_dwv_pwocessing)
		goto out;

	if (mwioc->unwecovewabwe) {
		dpwint_event_bh(mwioc,
		    "ignowing event(0x%02x) in bottom hawf handwew due to unwecovewabwe contwowwew\n",
		    fwevt->event_id);
		goto out;
	}

	if (!fwevt->pwocess_evt)
		goto evt_ack;

	switch (fwevt->event_id) {
	case MPI3_EVENT_DEVICE_ADDED:
	{
		dev_pg0 = (stwuct mpi3_device_page0 *)fwevt->event_data;
		pewst_id = we16_to_cpu(dev_pg0->pewsistent_id);
		handwe = we16_to_cpu(dev_pg0->dev_handwe);
		if (pewst_id != MPI3_DEVICE0_PEWSISTENTID_INVAWID)
			mpi3mw_wepowt_tgtdev_to_host(mwioc, pewst_id);
		ewse if (mwioc->sas_twanspowt_enabwed &&
		    (dev_pg0->device_fowm == MPI3_DEVICE_DEVFOWM_SAS_SATA)) {
			sasinf = &dev_pg0->device_specific.sas_sata_fowmat;
			dev_info = we16_to_cpu(sasinf->device_info);
			if (!mwioc->sas_hba.num_phys)
				mpi3mw_sas_host_add(mwioc);
			ewse
				mpi3mw_sas_host_wefwesh(mwioc);

			if (mpi3mw_is_expandew_device(dev_info))
				mpi3mw_expandew_add(mwioc, handwe);
		}
		bweak;
	}
	case MPI3_EVENT_DEVICE_INFO_CHANGED:
	{
		dev_pg0 = (stwuct mpi3_device_page0 *)fwevt->event_data;
		pewst_id = we16_to_cpu(dev_pg0->pewsistent_id);
		if (pewst_id != MPI3_DEVICE0_PEWSISTENTID_INVAWID)
			mpi3mw_devinfochg_evt_bh(mwioc, dev_pg0);
		bweak;
	}
	case MPI3_EVENT_DEVICE_STATUS_CHANGE:
	{
		mpi3mw_devstatuschg_evt_bh(mwioc, fwevt);
		bweak;
	}
	case MPI3_EVENT_ENCW_DEVICE_ADDED:
	case MPI3_EVENT_ENCW_DEVICE_STATUS_CHANGE:
	{
		mpi3mw_encwdev_add_chg_evt_bh(mwioc, fwevt);
		bweak;
	}

	case MPI3_EVENT_SAS_TOPOWOGY_CHANGE_WIST:
	{
		mpi3mw_sastopochg_evt_bh(mwioc, fwevt);
		bweak;
	}
	case MPI3_EVENT_PCIE_TOPOWOGY_CHANGE_WIST:
	{
		mpi3mw_pcietopochg_evt_bh(mwioc, fwevt);
		bweak;
	}
	case MPI3_EVENT_WOG_DATA:
	{
		mpi3mw_wogdata_evt_bh(mwioc, fwevt);
		bweak;
	}
	case MPI3MW_DWIVEW_EVENT_TG_QD_WEDUCTION:
	{
		stwuct mpi3mw_thwottwe_gwoup_info *tg;

		tg = *(stwuct mpi3mw_thwottwe_gwoup_info **)fwevt->event_data;
		dpwint_event_bh(mwioc,
		    "qd weduction event pwocessed fow tg_id(%d) weduction_needed(%d)\n",
		    tg->id, tg->need_qd_weduction);
		if (tg->need_qd_weduction) {
			mpi3mw_set_qd_fow_aww_vd_in_tg(mwioc, tg);
			tg->need_qd_weduction = 0;
		}
		bweak;
	}
	case MPI3_EVENT_WAIT_FOW_DEVICES_TO_WEFWESH:
	{
		whiwe (mwioc->device_wefwesh_on)
			msweep(500);

		dpwint_event_bh(mwioc,
		    "scan fow non wesponding and newwy added devices aftew soft weset stawted\n");
		if (mwioc->sas_twanspowt_enabwed) {
			mpi3mw_wefwesh_sas_powts(mwioc);
			mpi3mw_wefwesh_expandews(mwioc);
		}
		mpi3mw_wfwesh_tgtdevs(mwioc);
		ioc_info(mwioc,
		    "scan fow non wesponding and newwy added devices aftew soft weset compweted\n");
		bweak;
	}
	defauwt:
		bweak;
	}

evt_ack:
	if (fwevt->send_ack)
		mpi3mw_pwocess_event_ack(mwioc, fwevt->event_id,
		    fwevt->evt_ctx);
out:
	/* Put fwevt wefewence count to neutwawize kwef_init incwement */
	mpi3mw_fwevt_put(fwevt);
	mwioc->cuwwent_event = NUWW;
}

/**
 * mpi3mw_fwevt_wowkew - Fiwmwawe event wowkew
 * @wowk: Wowk stwuct containing fiwmwawe event
 *
 * Extwacts the fiwmwawe event and cawws mpi3mw_fwevt_bh.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_fwevt_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mpi3mw_fwevt *fwevt = containew_of(wowk, stwuct mpi3mw_fwevt,
	    wowk);
	mpi3mw_fwevt_bh(fwevt->mwioc, fwevt);
	/*
	 * Put fwevt wefewence count aftew
	 * dequeuing it fwom wowkew queue
	 */
	mpi3mw_fwevt_put(fwevt);
}

/**
 * mpi3mw_cweate_tgtdev - Cweate and add a tawget device
 * @mwioc: Adaptew instance wefewence
 * @dev_pg0: Device Page 0 data
 *
 * If the device specified by the device page 0 data is not
 * pwesent in the dwivew's intewnaw wist, awwocate the memowy
 * fow the device, popuwate the data and add to the wist, ewse
 * update the device data.  The key is pewsistent ID.
 *
 * Wetuwn: 0 on success, -ENOMEM on memowy awwocation faiwuwe
 */
static int mpi3mw_cweate_tgtdev(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_device_page0 *dev_pg0)
{
	int wetvaw = 0;
	stwuct mpi3mw_tgt_dev *tgtdev = NUWW;
	u16 pewst_id = 0;
	unsigned wong fwags;

	pewst_id = we16_to_cpu(dev_pg0->pewsistent_id);
	if (pewst_id == MPI3_DEVICE0_PEWSISTENTID_INVAWID)
		wetuwn wetvaw;

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	tgtdev = __mpi3mw_get_tgtdev_by_pewst_id(mwioc, pewst_id);
	if (tgtdev)
		tgtdev->state = MPI3MW_DEV_CWEATED;
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);

	if (tgtdev) {
		mpi3mw_update_tgtdev(mwioc, tgtdev, dev_pg0, twue);
		mpi3mw_tgtdev_put(tgtdev);
	} ewse {
		tgtdev = mpi3mw_awwoc_tgtdev();
		if (!tgtdev)
			wetuwn -ENOMEM;
		mpi3mw_update_tgtdev(mwioc, tgtdev, dev_pg0, twue);
		mpi3mw_tgtdev_add_to_wist(mwioc, tgtdev);
	}

	wetuwn wetvaw;
}

/**
 * mpi3mw_fwush_dewayed_cmd_wists - Fwush pending commands
 * @mwioc: Adaptew instance wefewence
 *
 * Fwush pending commands in the dewayed wists due to a
 * contwowwew weset ow dwivew wemovaw as a cweanup.
 *
 * Wetuwn: Nothing
 */
void mpi3mw_fwush_dewayed_cmd_wists(stwuct mpi3mw_ioc *mwioc)
{
	stwuct dewayed_dev_wmhs_node *_wmhs_node;
	stwuct dewayed_evt_ack_node *_evtack_node;

	dpwint_weset(mwioc, "fwushing dewayed dev_wemove_hs commands\n");
	whiwe (!wist_empty(&mwioc->dewayed_wmhs_wist)) {
		_wmhs_node = wist_entwy(mwioc->dewayed_wmhs_wist.next,
		    stwuct dewayed_dev_wmhs_node, wist);
		wist_dew(&_wmhs_node->wist);
		kfwee(_wmhs_node);
	}
	dpwint_weset(mwioc, "fwushing dewayed event ack commands\n");
	whiwe (!wist_empty(&mwioc->dewayed_evtack_cmds_wist)) {
		_evtack_node = wist_entwy(mwioc->dewayed_evtack_cmds_wist.next,
		    stwuct dewayed_evt_ack_node, wist);
		wist_dew(&_evtack_node->wist);
		kfwee(_evtack_node);
	}
}

/**
 * mpi3mw_dev_wmhs_compwete_iou - Device wemovaw IOUC compwetion
 * @mwioc: Adaptew instance wefewence
 * @dwv_cmd: Intewnaw command twackew
 *
 * Issues a tawget weset TM to the fiwmwawe fwom the device
 * wemovaw TM pend wist ow wetwy the wemovaw handshake sequence
 * based on the IOU contwow wequest IOC status.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_dev_wmhs_compwete_iou(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_dwv_cmd *dwv_cmd)
{
	u16 cmd_idx = dwv_cmd->host_tag - MPI3MW_HOSTTAG_DEVWMCMD_MIN;
	stwuct dewayed_dev_wmhs_node *dewayed_dev_wmhs = NUWW;

	if (dwv_cmd->state & MPI3MW_CMD_WESET)
		goto cweaw_dwv_cmd;

	ioc_info(mwioc,
	    "%s :dev_wmhs_iouctww_compwete:handwe(0x%04x), ioc_status(0x%04x), woginfo(0x%08x)\n",
	    __func__, dwv_cmd->dev_handwe, dwv_cmd->ioc_status,
	    dwv_cmd->ioc_woginfo);
	if (dwv_cmd->ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		if (dwv_cmd->wetwy_count < MPI3MW_DEV_WMHS_WETWY_COUNT) {
			dwv_cmd->wetwy_count++;
			ioc_info(mwioc,
			    "%s :dev_wmhs_iouctww_compwete: handwe(0x%04x)wetwying handshake wetwy=%d\n",
			    __func__, dwv_cmd->dev_handwe,
			    dwv_cmd->wetwy_count);
			mpi3mw_dev_wmhs_send_tm(mwioc, dwv_cmd->dev_handwe,
			    dwv_cmd, dwv_cmd->iou_wc);
			wetuwn;
		}
		ioc_eww(mwioc,
		    "%s :dev wemovaw handshake faiwed aftew aww wetwies: handwe(0x%04x)\n",
		    __func__, dwv_cmd->dev_handwe);
	} ewse {
		ioc_info(mwioc,
		    "%s :dev wemovaw handshake compweted successfuwwy: handwe(0x%04x)\n",
		    __func__, dwv_cmd->dev_handwe);
		cweaw_bit(dwv_cmd->dev_handwe, mwioc->wemovepend_bitmap);
	}

	if (!wist_empty(&mwioc->dewayed_wmhs_wist)) {
		dewayed_dev_wmhs = wist_entwy(mwioc->dewayed_wmhs_wist.next,
		    stwuct dewayed_dev_wmhs_node, wist);
		dwv_cmd->dev_handwe = dewayed_dev_wmhs->handwe;
		dwv_cmd->wetwy_count = 0;
		dwv_cmd->iou_wc = dewayed_dev_wmhs->iou_wc;
		ioc_info(mwioc,
		    "%s :dev_wmhs_iouctww_compwete: pwocessing dewayed TM: handwe(0x%04x)\n",
		    __func__, dwv_cmd->dev_handwe);
		mpi3mw_dev_wmhs_send_tm(mwioc, dwv_cmd->dev_handwe, dwv_cmd,
		    dwv_cmd->iou_wc);
		wist_dew(&dewayed_dev_wmhs->wist);
		kfwee(dewayed_dev_wmhs);
		wetuwn;
	}

cweaw_dwv_cmd:
	dwv_cmd->state = MPI3MW_CMD_NOTUSED;
	dwv_cmd->cawwback = NUWW;
	dwv_cmd->wetwy_count = 0;
	dwv_cmd->dev_handwe = MPI3MW_INVAWID_DEV_HANDWE;
	cweaw_bit(cmd_idx, mwioc->devwem_bitmap);
}

/**
 * mpi3mw_dev_wmhs_compwete_tm - Device wemovaw TM compwetion
 * @mwioc: Adaptew instance wefewence
 * @dwv_cmd: Intewnaw command twackew
 *
 * Issues a tawget weset TM to the fiwmwawe fwom the device
 * wemovaw TM pend wist ow issue IO unit contwow wequest as
 * pawt of device wemovaw ow hidden acknowwedgment handshake.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_dev_wmhs_compwete_tm(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_dwv_cmd *dwv_cmd)
{
	stwuct mpi3_iounit_contwow_wequest iou_ctww;
	u16 cmd_idx = dwv_cmd->host_tag - MPI3MW_HOSTTAG_DEVWMCMD_MIN;
	stwuct mpi3_scsi_task_mgmt_wepwy *tm_wepwy = NUWW;
	int wetvaw;

	if (dwv_cmd->state & MPI3MW_CMD_WESET)
		goto cweaw_dwv_cmd;

	if (dwv_cmd->state & MPI3MW_CMD_WEPWY_VAWID)
		tm_wepwy = (stwuct mpi3_scsi_task_mgmt_wepwy *)dwv_cmd->wepwy;

	if (tm_wepwy)
		pw_info(IOCNAME
		    "dev_wmhs_tw_compwete:handwe(0x%04x), ioc_status(0x%04x), woginfo(0x%08x), tewm_count(%d)\n",
		    mwioc->name, dwv_cmd->dev_handwe, dwv_cmd->ioc_status,
		    dwv_cmd->ioc_woginfo,
		    we32_to_cpu(tm_wepwy->tewmination_count));

	pw_info(IOCNAME "Issuing IOU CTW: handwe(0x%04x) dev_wmhs idx(%d)\n",
	    mwioc->name, dwv_cmd->dev_handwe, cmd_idx);

	memset(&iou_ctww, 0, sizeof(iou_ctww));

	dwv_cmd->state = MPI3MW_CMD_PENDING;
	dwv_cmd->is_waiting = 0;
	dwv_cmd->cawwback = mpi3mw_dev_wmhs_compwete_iou;
	iou_ctww.opewation = dwv_cmd->iou_wc;
	iou_ctww.pawam16[0] = cpu_to_we16(dwv_cmd->dev_handwe);
	iou_ctww.host_tag = cpu_to_we16(dwv_cmd->host_tag);
	iou_ctww.function = MPI3_FUNCTION_IO_UNIT_CONTWOW;

	wetvaw = mpi3mw_admin_wequest_post(mwioc, &iou_ctww, sizeof(iou_ctww),
	    1);
	if (wetvaw) {
		pw_eww(IOCNAME "Issue DevWmHsTMIOUCTW: Admin post faiwed\n",
		    mwioc->name);
		goto cweaw_dwv_cmd;
	}

	wetuwn;
cweaw_dwv_cmd:
	dwv_cmd->state = MPI3MW_CMD_NOTUSED;
	dwv_cmd->cawwback = NUWW;
	dwv_cmd->dev_handwe = MPI3MW_INVAWID_DEV_HANDWE;
	dwv_cmd->wetwy_count = 0;
	cweaw_bit(cmd_idx, mwioc->devwem_bitmap);
}

/**
 * mpi3mw_dev_wmhs_send_tm - Issue TM fow device wemovaw
 * @mwioc: Adaptew instance wefewence
 * @handwe: Device handwe
 * @cmdpawam: Intewnaw command twackew
 * @iou_wc: IO unit weason code
 *
 * Issues a tawget weset TM to the fiwmwawe ow add it to a pend
 * wist as pawt of device wemovaw ow hidden acknowwedgment
 * handshake.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_dev_wmhs_send_tm(stwuct mpi3mw_ioc *mwioc, u16 handwe,
	stwuct mpi3mw_dwv_cmd *cmdpawam, u8 iou_wc)
{
	stwuct mpi3_scsi_task_mgmt_wequest tm_weq;
	int wetvaw = 0;
	u16 cmd_idx = MPI3MW_NUM_DEVWMCMD;
	u8 wetwycount = 5;
	stwuct mpi3mw_dwv_cmd *dwv_cmd = cmdpawam;
	stwuct dewayed_dev_wmhs_node *dewayed_dev_wmhs = NUWW;
	stwuct mpi3mw_tgt_dev *tgtdev = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	tgtdev = __mpi3mw_get_tgtdev_by_handwe(mwioc, handwe);
	if (tgtdev && (iou_wc == MPI3_CTWW_OP_WEMOVE_DEVICE))
		tgtdev->state = MPI3MW_DEV_WEMOVE_HS_STAWTED;
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);

	if (dwv_cmd)
		goto issue_cmd;
	do {
		cmd_idx = find_fiwst_zewo_bit(mwioc->devwem_bitmap,
		    MPI3MW_NUM_DEVWMCMD);
		if (cmd_idx < MPI3MW_NUM_DEVWMCMD) {
			if (!test_and_set_bit(cmd_idx, mwioc->devwem_bitmap))
				bweak;
			cmd_idx = MPI3MW_NUM_DEVWMCMD;
		}
	} whiwe (wetwycount--);

	if (cmd_idx >= MPI3MW_NUM_DEVWMCMD) {
		dewayed_dev_wmhs = kzawwoc(sizeof(*dewayed_dev_wmhs),
		    GFP_ATOMIC);
		if (!dewayed_dev_wmhs)
			wetuwn;
		INIT_WIST_HEAD(&dewayed_dev_wmhs->wist);
		dewayed_dev_wmhs->handwe = handwe;
		dewayed_dev_wmhs->iou_wc = iou_wc;
		wist_add_taiw(&dewayed_dev_wmhs->wist,
		    &mwioc->dewayed_wmhs_wist);
		ioc_info(mwioc, "%s :DevWmHs: tw:handwe(0x%04x) is postponed\n",
		    __func__, handwe);
		wetuwn;
	}
	dwv_cmd = &mwioc->dev_wmhs_cmds[cmd_idx];

issue_cmd:
	cmd_idx = dwv_cmd->host_tag - MPI3MW_HOSTTAG_DEVWMCMD_MIN;
	ioc_info(mwioc,
	    "%s :Issuing TW TM: fow devhandwe 0x%04x with dev_wmhs %d\n",
	    __func__, handwe, cmd_idx);

	memset(&tm_weq, 0, sizeof(tm_weq));
	if (dwv_cmd->state & MPI3MW_CMD_PENDING) {
		ioc_eww(mwioc, "%s :Issue TM: Command is in use\n", __func__);
		goto out;
	}
	dwv_cmd->state = MPI3MW_CMD_PENDING;
	dwv_cmd->is_waiting = 0;
	dwv_cmd->cawwback = mpi3mw_dev_wmhs_compwete_tm;
	dwv_cmd->dev_handwe = handwe;
	dwv_cmd->iou_wc = iou_wc;
	tm_weq.dev_handwe = cpu_to_we16(handwe);
	tm_weq.task_type = MPI3_SCSITASKMGMT_TASKTYPE_TAWGET_WESET;
	tm_weq.host_tag = cpu_to_we16(dwv_cmd->host_tag);
	tm_weq.task_host_tag = cpu_to_we16(MPI3MW_HOSTTAG_INVAWID);
	tm_weq.function = MPI3_FUNCTION_SCSI_TASK_MGMT;

	set_bit(handwe, mwioc->wemovepend_bitmap);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &tm_weq, sizeof(tm_weq), 1);
	if (wetvaw) {
		ioc_eww(mwioc, "%s :Issue DevWmHsTM: Admin Post faiwed\n",
		    __func__);
		goto out_faiwed;
	}
out:
	wetuwn;
out_faiwed:
	dwv_cmd->state = MPI3MW_CMD_NOTUSED;
	dwv_cmd->cawwback = NUWW;
	dwv_cmd->dev_handwe = MPI3MW_INVAWID_DEV_HANDWE;
	dwv_cmd->wetwy_count = 0;
	cweaw_bit(cmd_idx, mwioc->devwem_bitmap);
}

/**
 * mpi3mw_compwete_evt_ack - event ack wequest compwetion
 * @mwioc: Adaptew instance wefewence
 * @dwv_cmd: Intewnaw command twackew
 *
 * This is the compwetion handwew fow non bwocking event
 * acknowwedgment sent to the fiwmwawe and this wiww issue any
 * pending event acknowwedgment wequest.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_compwete_evt_ack(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3mw_dwv_cmd *dwv_cmd)
{
	u16 cmd_idx = dwv_cmd->host_tag - MPI3MW_HOSTTAG_EVTACKCMD_MIN;
	stwuct dewayed_evt_ack_node *dewayed_evtack = NUWW;

	if (dwv_cmd->state & MPI3MW_CMD_WESET)
		goto cweaw_dwv_cmd;

	if (dwv_cmd->ioc_status != MPI3_IOCSTATUS_SUCCESS) {
		dpwint_event_th(mwioc,
		    "immediate event ack faiwed with ioc_status(0x%04x) wog_info(0x%08x)\n",
		    (dwv_cmd->ioc_status & MPI3_IOCSTATUS_STATUS_MASK),
		    dwv_cmd->ioc_woginfo);
	}

	if (!wist_empty(&mwioc->dewayed_evtack_cmds_wist)) {
		dewayed_evtack =
			wist_entwy(mwioc->dewayed_evtack_cmds_wist.next,
			    stwuct dewayed_evt_ack_node, wist);
		mpi3mw_send_event_ack(mwioc, dewayed_evtack->event, dwv_cmd,
		    dewayed_evtack->event_ctx);
		wist_dew(&dewayed_evtack->wist);
		kfwee(dewayed_evtack);
		wetuwn;
	}
cweaw_dwv_cmd:
	dwv_cmd->state = MPI3MW_CMD_NOTUSED;
	dwv_cmd->cawwback = NUWW;
	cweaw_bit(cmd_idx, mwioc->evtack_cmds_bitmap);
}

/**
 * mpi3mw_send_event_ack - Issue event acknwowedgment wequest
 * @mwioc: Adaptew instance wefewence
 * @event: MPI3 event id
 * @cmdpawam: Intewnaw command twackew
 * @event_ctx: event context
 *
 * Issues event acknowwedgment wequest to the fiwmwawe if thewe
 * is a fwee command to send the event ack ewse it to a pend
 * wist so that it wiww be pwocessed on a compwetion of a pwiow
 * event acknowwedgment .
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_send_event_ack(stwuct mpi3mw_ioc *mwioc, u8 event,
	stwuct mpi3mw_dwv_cmd *cmdpawam, u32 event_ctx)
{
	stwuct mpi3_event_ack_wequest evtack_weq;
	int wetvaw = 0;
	u8 wetwycount = 5;
	u16 cmd_idx = MPI3MW_NUM_EVTACKCMD;
	stwuct mpi3mw_dwv_cmd *dwv_cmd = cmdpawam;
	stwuct dewayed_evt_ack_node *dewayed_evtack = NUWW;

	if (dwv_cmd) {
		dpwint_event_th(mwioc,
		    "sending dewayed event ack in the top hawf fow event(0x%02x), event_ctx(0x%08x)\n",
		    event, event_ctx);
		goto issue_cmd;
	}
	dpwint_event_th(mwioc,
	    "sending event ack in the top hawf fow event(0x%02x), event_ctx(0x%08x)\n",
	    event, event_ctx);
	do {
		cmd_idx = find_fiwst_zewo_bit(mwioc->evtack_cmds_bitmap,
		    MPI3MW_NUM_EVTACKCMD);
		if (cmd_idx < MPI3MW_NUM_EVTACKCMD) {
			if (!test_and_set_bit(cmd_idx,
			    mwioc->evtack_cmds_bitmap))
				bweak;
			cmd_idx = MPI3MW_NUM_EVTACKCMD;
		}
	} whiwe (wetwycount--);

	if (cmd_idx >= MPI3MW_NUM_EVTACKCMD) {
		dewayed_evtack = kzawwoc(sizeof(*dewayed_evtack),
		    GFP_ATOMIC);
		if (!dewayed_evtack)
			wetuwn;
		INIT_WIST_HEAD(&dewayed_evtack->wist);
		dewayed_evtack->event = event;
		dewayed_evtack->event_ctx = event_ctx;
		wist_add_taiw(&dewayed_evtack->wist,
		    &mwioc->dewayed_evtack_cmds_wist);
		dpwint_event_th(mwioc,
		    "event ack in the top hawf fow event(0x%02x), event_ctx(0x%08x) is postponed\n",
		    event, event_ctx);
		wetuwn;
	}
	dwv_cmd = &mwioc->evtack_cmds[cmd_idx];

issue_cmd:
	cmd_idx = dwv_cmd->host_tag - MPI3MW_HOSTTAG_EVTACKCMD_MIN;

	memset(&evtack_weq, 0, sizeof(evtack_weq));
	if (dwv_cmd->state & MPI3MW_CMD_PENDING) {
		dpwint_event_th(mwioc,
		    "sending event ack faiwed due to command in use\n");
		goto out;
	}
	dwv_cmd->state = MPI3MW_CMD_PENDING;
	dwv_cmd->is_waiting = 0;
	dwv_cmd->cawwback = mpi3mw_compwete_evt_ack;
	evtack_weq.host_tag = cpu_to_we16(dwv_cmd->host_tag);
	evtack_weq.function = MPI3_FUNCTION_EVENT_ACK;
	evtack_weq.event = event;
	evtack_weq.event_context = cpu_to_we32(event_ctx);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &evtack_weq,
	    sizeof(evtack_weq), 1);
	if (wetvaw) {
		dpwint_event_th(mwioc,
		    "posting event ack wequest is faiwed\n");
		goto out_faiwed;
	}

	dpwint_event_th(mwioc,
	    "event ack in the top hawf fow event(0x%02x), event_ctx(0x%08x) is posted\n",
	    event, event_ctx);
out:
	wetuwn;
out_faiwed:
	dwv_cmd->state = MPI3MW_CMD_NOTUSED;
	dwv_cmd->cawwback = NUWW;
	cweaw_bit(cmd_idx, mwioc->evtack_cmds_bitmap);
}

/**
 * mpi3mw_pcietopochg_evt_th - PCIETopowogyChange evt tophawf
 * @mwioc: Adaptew instance wefewence
 * @event_wepwy: event data
 *
 * Checks fow the weason code and based on that eithew bwock I/O
 * to device, ow unbwock I/O to the device, ow stawt the device
 * wemovaw handshake with weason as wemove with the fiwmwawe fow
 * PCIe devices.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_pcietopochg_evt_th(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_event_notification_wepwy *event_wepwy)
{
	stwuct mpi3_event_data_pcie_topowogy_change_wist *topo_evt =
	    (stwuct mpi3_event_data_pcie_topowogy_change_wist *)event_wepwy->event_data;
	int i;
	u16 handwe;
	u8 weason_code;
	stwuct mpi3mw_tgt_dev *tgtdev = NUWW;
	stwuct mpi3mw_stgt_pwiv_data *scsi_tgt_pwiv_data = NUWW;

	fow (i = 0; i < topo_evt->num_entwies; i++) {
		handwe = we16_to_cpu(topo_evt->powt_entwy[i].attached_dev_handwe);
		if (!handwe)
			continue;
		weason_code = topo_evt->powt_entwy[i].powt_status;
		scsi_tgt_pwiv_data =  NUWW;
		tgtdev = mpi3mw_get_tgtdev_by_handwe(mwioc, handwe);
		if (tgtdev && tgtdev->stawget && tgtdev->stawget->hostdata)
			scsi_tgt_pwiv_data = (stwuct mpi3mw_stgt_pwiv_data *)
			    tgtdev->stawget->hostdata;
		switch (weason_code) {
		case MPI3_EVENT_PCIE_TOPO_PS_NOT_WESPONDING:
			if (scsi_tgt_pwiv_data) {
				scsi_tgt_pwiv_data->dev_wemoved = 1;
				scsi_tgt_pwiv_data->dev_wemovedeway = 0;
				atomic_set(&scsi_tgt_pwiv_data->bwock_io, 0);
			}
			mpi3mw_dev_wmhs_send_tm(mwioc, handwe, NUWW,
			    MPI3_CTWW_OP_WEMOVE_DEVICE);
			bweak;
		case MPI3_EVENT_PCIE_TOPO_PS_DEWAY_NOT_WESPONDING:
			if (scsi_tgt_pwiv_data) {
				scsi_tgt_pwiv_data->dev_wemovedeway = 1;
				atomic_inc(&scsi_tgt_pwiv_data->bwock_io);
			}
			bweak;
		case MPI3_EVENT_PCIE_TOPO_PS_WESPONDING:
			if (scsi_tgt_pwiv_data &&
			    scsi_tgt_pwiv_data->dev_wemovedeway) {
				scsi_tgt_pwiv_data->dev_wemovedeway = 0;
				atomic_dec_if_positive
				    (&scsi_tgt_pwiv_data->bwock_io);
			}
			bweak;
		case MPI3_EVENT_PCIE_TOPO_PS_POWT_CHANGED:
		defauwt:
			bweak;
		}
		if (tgtdev)
			mpi3mw_tgtdev_put(tgtdev);
	}
}

/**
 * mpi3mw_sastopochg_evt_th - SASTopowogyChange evt tophawf
 * @mwioc: Adaptew instance wefewence
 * @event_wepwy: event data
 *
 * Checks fow the weason code and based on that eithew bwock I/O
 * to device, ow unbwock I/O to the device, ow stawt the device
 * wemovaw handshake with weason as wemove with the fiwmwawe fow
 * SAS/SATA devices.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_sastopochg_evt_th(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_event_notification_wepwy *event_wepwy)
{
	stwuct mpi3_event_data_sas_topowogy_change_wist *topo_evt =
	    (stwuct mpi3_event_data_sas_topowogy_change_wist *)event_wepwy->event_data;
	int i;
	u16 handwe;
	u8 weason_code;
	stwuct mpi3mw_tgt_dev *tgtdev = NUWW;
	stwuct mpi3mw_stgt_pwiv_data *scsi_tgt_pwiv_data = NUWW;

	fow (i = 0; i < topo_evt->num_entwies; i++) {
		handwe = we16_to_cpu(topo_evt->phy_entwy[i].attached_dev_handwe);
		if (!handwe)
			continue;
		weason_code = topo_evt->phy_entwy[i].status &
		    MPI3_EVENT_SAS_TOPO_PHY_WC_MASK;
		scsi_tgt_pwiv_data =  NUWW;
		tgtdev = mpi3mw_get_tgtdev_by_handwe(mwioc, handwe);
		if (tgtdev && tgtdev->stawget && tgtdev->stawget->hostdata)
			scsi_tgt_pwiv_data = (stwuct mpi3mw_stgt_pwiv_data *)
			    tgtdev->stawget->hostdata;
		switch (weason_code) {
		case MPI3_EVENT_SAS_TOPO_PHY_WC_TAWG_NOT_WESPONDING:
			if (scsi_tgt_pwiv_data) {
				scsi_tgt_pwiv_data->dev_wemoved = 1;
				scsi_tgt_pwiv_data->dev_wemovedeway = 0;
				atomic_set(&scsi_tgt_pwiv_data->bwock_io, 0);
			}
			mpi3mw_dev_wmhs_send_tm(mwioc, handwe, NUWW,
			    MPI3_CTWW_OP_WEMOVE_DEVICE);
			bweak;
		case MPI3_EVENT_SAS_TOPO_PHY_WC_DEWAY_NOT_WESPONDING:
			if (scsi_tgt_pwiv_data) {
				scsi_tgt_pwiv_data->dev_wemovedeway = 1;
				atomic_inc(&scsi_tgt_pwiv_data->bwock_io);
			}
			bweak;
		case MPI3_EVENT_SAS_TOPO_PHY_WC_WESPONDING:
			if (scsi_tgt_pwiv_data &&
			    scsi_tgt_pwiv_data->dev_wemovedeway) {
				scsi_tgt_pwiv_data->dev_wemovedeway = 0;
				atomic_dec_if_positive
				    (&scsi_tgt_pwiv_data->bwock_io);
			}
			bweak;
		case MPI3_EVENT_SAS_TOPO_PHY_WC_PHY_CHANGED:
		defauwt:
			bweak;
		}
		if (tgtdev)
			mpi3mw_tgtdev_put(tgtdev);
	}
}

/**
 * mpi3mw_devstatuschg_evt_th - DeviceStatusChange evt tophawf
 * @mwioc: Adaptew instance wefewence
 * @event_wepwy: event data
 *
 * Checks fow the weason code and based on that eithew bwock I/O
 * to device, ow unbwock I/O to the device, ow stawt the device
 * wemovaw handshake with weason as wemove/hide acknowwedgment
 * with the fiwmwawe.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_devstatuschg_evt_th(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_event_notification_wepwy *event_wepwy)
{
	u16 dev_handwe = 0;
	u8 ubwock = 0, bwock = 0, hide = 0, dewete = 0, wemove = 0;
	stwuct mpi3mw_tgt_dev *tgtdev = NUWW;
	stwuct mpi3mw_stgt_pwiv_data *scsi_tgt_pwiv_data = NUWW;
	stwuct mpi3_event_data_device_status_change *evtdata =
	    (stwuct mpi3_event_data_device_status_change *)event_wepwy->event_data;

	if (mwioc->stop_dwv_pwocessing)
		goto out;

	dev_handwe = we16_to_cpu(evtdata->dev_handwe);

	switch (evtdata->weason_code) {
	case MPI3_EVENT_DEV_STAT_WC_INT_DEVICE_WESET_STWT:
	case MPI3_EVENT_DEV_STAT_WC_INT_IT_NEXUS_WESET_STWT:
		bwock = 1;
		bweak;
	case MPI3_EVENT_DEV_STAT_WC_HIDDEN:
		dewete = 1;
		hide = 1;
		bweak;
	case MPI3_EVENT_DEV_STAT_WC_VD_NOT_WESPONDING:
		dewete = 1;
		wemove = 1;
		bweak;
	case MPI3_EVENT_DEV_STAT_WC_INT_DEVICE_WESET_CMP:
	case MPI3_EVENT_DEV_STAT_WC_INT_IT_NEXUS_WESET_CMP:
		ubwock = 1;
		bweak;
	defauwt:
		bweak;
	}

	tgtdev = mpi3mw_get_tgtdev_by_handwe(mwioc, dev_handwe);
	if (!tgtdev)
		goto out;
	if (hide)
		tgtdev->is_hidden = hide;
	if (tgtdev->stawget && tgtdev->stawget->hostdata) {
		scsi_tgt_pwiv_data = (stwuct mpi3mw_stgt_pwiv_data *)
		    tgtdev->stawget->hostdata;
		if (bwock)
			atomic_inc(&scsi_tgt_pwiv_data->bwock_io);
		if (dewete)
			scsi_tgt_pwiv_data->dev_wemoved = 1;
		if (ubwock)
			atomic_dec_if_positive(&scsi_tgt_pwiv_data->bwock_io);
	}
	if (wemove)
		mpi3mw_dev_wmhs_send_tm(mwioc, dev_handwe, NUWW,
		    MPI3_CTWW_OP_WEMOVE_DEVICE);
	if (hide)
		mpi3mw_dev_wmhs_send_tm(mwioc, dev_handwe, NUWW,
		    MPI3_CTWW_OP_HIDDEN_ACK);

out:
	if (tgtdev)
		mpi3mw_tgtdev_put(tgtdev);
}

/**
 * mpi3mw_pwepaweweset_evt_th - Pwepawe fow weset event tophawf
 * @mwioc: Adaptew instance wefewence
 * @event_wepwy: event data
 *
 * Bwocks and unbwocks host wevew I/O based on the weason code
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_pwepaweweset_evt_th(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_event_notification_wepwy *event_wepwy)
{
	stwuct mpi3_event_data_pwepawe_fow_weset *evtdata =
	    (stwuct mpi3_event_data_pwepawe_fow_weset *)event_wepwy->event_data;

	if (evtdata->weason_code == MPI3_EVENT_PWEPAWE_WESET_WC_STAWT) {
		dpwint_event_th(mwioc,
		    "pwepawe fow weset event top hawf with wc=stawt\n");
		if (mwioc->pwepawe_fow_weset)
			wetuwn;
		mwioc->pwepawe_fow_weset = 1;
		mwioc->pwepawe_fow_weset_timeout_countew = 0;
	} ewse if (evtdata->weason_code == MPI3_EVENT_PWEPAWE_WESET_WC_ABOWT) {
		dpwint_event_th(mwioc,
		    "pwepawe fow weset top hawf with wc=abowt\n");
		mwioc->pwepawe_fow_weset = 0;
		mwioc->pwepawe_fow_weset_timeout_countew = 0;
	}
	if ((event_wepwy->msg_fwags & MPI3_EVENT_NOTIFY_MSGFWAGS_ACK_MASK)
	    == MPI3_EVENT_NOTIFY_MSGFWAGS_ACK_WEQUIWED)
		mpi3mw_send_event_ack(mwioc, event_wepwy->event, NUWW,
		    we32_to_cpu(event_wepwy->event_context));
}

/**
 * mpi3mw_enewgypackchg_evt_th - Enewgy pack change evt tophawf
 * @mwioc: Adaptew instance wefewence
 * @event_wepwy: event data
 *
 * Identifies the new shutdown timeout vawue and update.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_enewgypackchg_evt_th(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_event_notification_wepwy *event_wepwy)
{
	stwuct mpi3_event_data_enewgy_pack_change *evtdata =
	    (stwuct mpi3_event_data_enewgy_pack_change *)event_wepwy->event_data;
	u16 shutdown_timeout = we16_to_cpu(evtdata->shutdown_timeout);

	if (shutdown_timeout <= 0) {
		ioc_wawn(mwioc,
		    "%s :Invawid Shutdown Timeout weceived = %d\n",
		    __func__, shutdown_timeout);
		wetuwn;
	}

	ioc_info(mwioc,
	    "%s :Pwevious Shutdown Timeout Vawue = %d New Shutdown Timeout Vawue = %d\n",
	    __func__, mwioc->facts.shutdown_timeout, shutdown_timeout);
	mwioc->facts.shutdown_timeout = shutdown_timeout;
}

/**
 * mpi3mw_cabwemgmt_evt_th - Cabwe management event tophawf
 * @mwioc: Adaptew instance wefewence
 * @event_wepwy: event data
 *
 * Dispways Cabwe manegemt event detaiws.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_cabwemgmt_evt_th(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_event_notification_wepwy *event_wepwy)
{
	stwuct mpi3_event_data_cabwe_management *evtdata =
	    (stwuct mpi3_event_data_cabwe_management *)event_wepwy->event_data;

	switch (evtdata->status) {
	case MPI3_EVENT_CABWE_MGMT_STATUS_INSUFFICIENT_POWEW:
	{
		ioc_info(mwioc, "An active cabwe with weceptacwe_id %d cannot be powewed.\n"
		    "Devices connected to this cabwe awe not detected.\n"
		    "This cabwe wequiwes %d mW of powew.\n",
		    evtdata->weceptacwe_id,
		    we32_to_cpu(evtdata->active_cabwe_powew_wequiwement));
		bweak;
	}
	case MPI3_EVENT_CABWE_MGMT_STATUS_DEGWADED:
	{
		ioc_info(mwioc, "A cabwe with weceptacwe_id %d is not wunning at optimaw speed\n",
		    evtdata->weceptacwe_id);
		bweak;
	}
	defauwt:
		bweak;
	}
}

/**
 * mpi3mw_add_event_wait_fow_device_wefwesh - Add Wait fow Device Wefwesh Event
 * @mwioc: Adaptew instance wefewence
 *
 * Add dwivew specific event to make suwe that the dwivew won't pwocess the
 * events untiw aww the devices awe wefweshed duwing soft weset.
 *
 * Wetuwn: Nothing
 */
void mpi3mw_add_event_wait_fow_device_wefwesh(stwuct mpi3mw_ioc *mwioc)
{
	stwuct mpi3mw_fwevt *fwevt = NUWW;

	fwevt = mpi3mw_awwoc_fwevt(0);
	if (!fwevt) {
		dpwint_event_th(mwioc,
		    "faiwed to scheduwe bottom hawf handwew fow event(0x%02x)\n",
		    MPI3_EVENT_WAIT_FOW_DEVICES_TO_WEFWESH);
		wetuwn;
	}
	fwevt->mwioc = mwioc;
	fwevt->event_id = MPI3_EVENT_WAIT_FOW_DEVICES_TO_WEFWESH;
	fwevt->send_ack = 0;
	fwevt->pwocess_evt = 1;
	fwevt->evt_ctx = 0;
	fwevt->event_data_size = 0;
	mpi3mw_fwevt_add_to_wist(mwioc, fwevt);
}

/**
 * mpi3mw_os_handwe_events - Fiwmwawe event handwew
 * @mwioc: Adaptew instance wefewence
 * @event_wepwy: event data
 *
 * Identify whtehew the event has to handwed and acknowwedged
 * and eithew pwocess the event in the tophawf and/ow scheduwe a
 * bottom hawf thwough mpi3mw_fwevt_wowkew.
 *
 * Wetuwn: Nothing
 */
void mpi3mw_os_handwe_events(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_event_notification_wepwy *event_wepwy)
{
	u16 evt_type, sz;
	stwuct mpi3mw_fwevt *fwevt = NUWW;
	boow ack_weq = 0, pwocess_evt_bh = 0;

	if (mwioc->stop_dwv_pwocessing)
		wetuwn;

	if ((event_wepwy->msg_fwags & MPI3_EVENT_NOTIFY_MSGFWAGS_ACK_MASK)
	    == MPI3_EVENT_NOTIFY_MSGFWAGS_ACK_WEQUIWED)
		ack_weq = 1;

	evt_type = event_wepwy->event;

	switch (evt_type) {
	case MPI3_EVENT_DEVICE_ADDED:
	{
		stwuct mpi3_device_page0 *dev_pg0 =
		    (stwuct mpi3_device_page0 *)event_wepwy->event_data;
		if (mpi3mw_cweate_tgtdev(mwioc, dev_pg0))
			ioc_eww(mwioc,
			    "%s :Faiwed to add device in the device add event\n",
			    __func__);
		ewse
			pwocess_evt_bh = 1;
		bweak;
	}
	case MPI3_EVENT_DEVICE_STATUS_CHANGE:
	{
		pwocess_evt_bh = 1;
		mpi3mw_devstatuschg_evt_th(mwioc, event_wepwy);
		bweak;
	}
	case MPI3_EVENT_SAS_TOPOWOGY_CHANGE_WIST:
	{
		pwocess_evt_bh = 1;
		mpi3mw_sastopochg_evt_th(mwioc, event_wepwy);
		bweak;
	}
	case MPI3_EVENT_PCIE_TOPOWOGY_CHANGE_WIST:
	{
		pwocess_evt_bh = 1;
		mpi3mw_pcietopochg_evt_th(mwioc, event_wepwy);
		bweak;
	}
	case MPI3_EVENT_PWEPAWE_FOW_WESET:
	{
		mpi3mw_pwepaweweset_evt_th(mwioc, event_wepwy);
		ack_weq = 0;
		bweak;
	}
	case MPI3_EVENT_DEVICE_INFO_CHANGED:
	case MPI3_EVENT_WOG_DATA:
	case MPI3_EVENT_ENCW_DEVICE_STATUS_CHANGE:
	case MPI3_EVENT_ENCW_DEVICE_ADDED:
	{
		pwocess_evt_bh = 1;
		bweak;
	}
	case MPI3_EVENT_ENEWGY_PACK_CHANGE:
	{
		mpi3mw_enewgypackchg_evt_th(mwioc, event_wepwy);
		bweak;
	}
	case MPI3_EVENT_CABWE_MGMT:
	{
		mpi3mw_cabwemgmt_evt_th(mwioc, event_wepwy);
		bweak;
	}
	case MPI3_EVENT_SAS_DISCOVEWY:
	case MPI3_EVENT_SAS_DEVICE_DISCOVEWY_EWWOW:
	case MPI3_EVENT_SAS_BWOADCAST_PWIMITIVE:
	case MPI3_EVENT_PCIE_ENUMEWATION:
		bweak;
	defauwt:
		ioc_info(mwioc, "%s :event 0x%02x is not handwed\n",
		    __func__, evt_type);
		bweak;
	}
	if (pwocess_evt_bh || ack_weq) {
		sz = event_wepwy->event_data_wength * 4;
		fwevt = mpi3mw_awwoc_fwevt(sz);
		if (!fwevt) {
			ioc_info(mwioc, "%s :faiwuwe at %s:%d/%s()!\n",
			    __func__, __FIWE__, __WINE__, __func__);
			wetuwn;
		}

		memcpy(fwevt->event_data, event_wepwy->event_data, sz);
		fwevt->mwioc = mwioc;
		fwevt->event_id = evt_type;
		fwevt->send_ack = ack_weq;
		fwevt->pwocess_evt = pwocess_evt_bh;
		fwevt->evt_ctx = we32_to_cpu(event_wepwy->event_context);
		mpi3mw_fwevt_add_to_wist(mwioc, fwevt);
	}
}

/**
 * mpi3mw_setup_eedp - Setup EEDP infowmation in MPI3 SCSI IO
 * @mwioc: Adaptew instance wefewence
 * @scmd: SCSI command wefewence
 * @scsiio_weq: MPI3 SCSI IO wequest
 *
 * Identifies the pwotection infowmation fwags fwom the SCSI
 * command and set appwopwiate fwags in the MPI3 SCSI IO
 * wequest.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_setup_eedp(stwuct mpi3mw_ioc *mwioc,
	stwuct scsi_cmnd *scmd, stwuct mpi3_scsi_io_wequest *scsiio_weq)
{
	u16 eedp_fwags = 0;
	unsigned chaw pwot_op = scsi_get_pwot_op(scmd);

	switch (pwot_op) {
	case SCSI_PWOT_NOWMAW:
		wetuwn;
	case SCSI_PWOT_WEAD_STWIP:
		eedp_fwags = MPI3_EEDPFWAGS_EEDP_OP_CHECK_WEMOVE;
		bweak;
	case SCSI_PWOT_WWITE_INSEWT:
		eedp_fwags = MPI3_EEDPFWAGS_EEDP_OP_INSEWT;
		bweak;
	case SCSI_PWOT_WEAD_INSEWT:
		eedp_fwags = MPI3_EEDPFWAGS_EEDP_OP_INSEWT;
		scsiio_weq->msg_fwags |= MPI3_SCSIIO_MSGFWAGS_METASGW_VAWID;
		bweak;
	case SCSI_PWOT_WWITE_STWIP:
		eedp_fwags = MPI3_EEDPFWAGS_EEDP_OP_CHECK_WEMOVE;
		scsiio_weq->msg_fwags |= MPI3_SCSIIO_MSGFWAGS_METASGW_VAWID;
		bweak;
	case SCSI_PWOT_WEAD_PASS:
		eedp_fwags = MPI3_EEDPFWAGS_EEDP_OP_CHECK;
		scsiio_weq->msg_fwags |= MPI3_SCSIIO_MSGFWAGS_METASGW_VAWID;
		bweak;
	case SCSI_PWOT_WWITE_PASS:
		if (scmd->pwot_fwags & SCSI_PWOT_IP_CHECKSUM) {
			eedp_fwags = MPI3_EEDPFWAGS_EEDP_OP_CHECK_WEGEN;
			scsiio_weq->sgw[0].eedp.appwication_tag_twanswation_mask =
			    0xffff;
		} ewse
			eedp_fwags = MPI3_EEDPFWAGS_EEDP_OP_CHECK;

		scsiio_weq->msg_fwags |= MPI3_SCSIIO_MSGFWAGS_METASGW_VAWID;
		bweak;
	defauwt:
		wetuwn;
	}

	if (scmd->pwot_fwags & SCSI_PWOT_GUAWD_CHECK)
		eedp_fwags |= MPI3_EEDPFWAGS_CHK_GUAWD;

	if (scmd->pwot_fwags & SCSI_PWOT_IP_CHECKSUM)
		eedp_fwags |= MPI3_EEDPFWAGS_HOST_GUAWD_IP_CHKSUM;

	if (scmd->pwot_fwags & SCSI_PWOT_WEF_CHECK) {
		eedp_fwags |= MPI3_EEDPFWAGS_CHK_WEF_TAG |
			MPI3_EEDPFWAGS_INCW_PWI_WEF_TAG;
		scsiio_weq->cdb.eedp32.pwimawy_wefewence_tag =
			cpu_to_be32(scsi_pwot_wef_tag(scmd));
	}

	if (scmd->pwot_fwags & SCSI_PWOT_WEF_INCWEMENT)
		eedp_fwags |= MPI3_EEDPFWAGS_INCW_PWI_WEF_TAG;

	eedp_fwags |= MPI3_EEDPFWAGS_ESC_MODE_APPTAG_DISABWE;

	switch (scsi_pwot_intewvaw(scmd)) {
	case 512:
		scsiio_weq->sgw[0].eedp.usew_data_size = MPI3_EEDP_UDS_512;
		bweak;
	case 520:
		scsiio_weq->sgw[0].eedp.usew_data_size = MPI3_EEDP_UDS_520;
		bweak;
	case 4080:
		scsiio_weq->sgw[0].eedp.usew_data_size = MPI3_EEDP_UDS_4080;
		bweak;
	case 4088:
		scsiio_weq->sgw[0].eedp.usew_data_size = MPI3_EEDP_UDS_4088;
		bweak;
	case 4096:
		scsiio_weq->sgw[0].eedp.usew_data_size = MPI3_EEDP_UDS_4096;
		bweak;
	case 4104:
		scsiio_weq->sgw[0].eedp.usew_data_size = MPI3_EEDP_UDS_4104;
		bweak;
	case 4160:
		scsiio_weq->sgw[0].eedp.usew_data_size = MPI3_EEDP_UDS_4160;
		bweak;
	defauwt:
		bweak;
	}

	scsiio_weq->sgw[0].eedp.eedp_fwags = cpu_to_we16(eedp_fwags);
	scsiio_weq->sgw[0].eedp.fwags = MPI3_SGE_FWAGS_EWEMENT_TYPE_EXTENDED;
}

/**
 * mpi3mw_buiwd_sense_buffew - Map sense infowmation
 * @desc: Sense type
 * @buf: Sense buffew to popuwate
 * @key: Sense key
 * @asc: Additionaw sense code
 * @ascq: Additionaw sense code quawifiew
 *
 * Maps the given sense infowmation into eithew descwiptow ow
 * fixed fowmat sense data.
 *
 * Wetuwn: Nothing
 */
static inwine void mpi3mw_buiwd_sense_buffew(int desc, u8 *buf, u8 key,
	u8 asc, u8 ascq)
{
	if (desc) {
		buf[0] = 0x72;	/* descwiptow, cuwwent */
		buf[1] = key;
		buf[2] = asc;
		buf[3] = ascq;
		buf[7] = 0;
	} ewse {
		buf[0] = 0x70;	/* fixed, cuwwent */
		buf[2] = key;
		buf[7] = 0xa;
		buf[12] = asc;
		buf[13] = ascq;
	}
}

/**
 * mpi3mw_map_eedp_ewwow - Map EEDP ewwows fwom IOC status
 * @scmd: SCSI command wefewence
 * @ioc_status: status of MPI3 wequest
 *
 * Maps the EEDP ewwow status of the SCSI IO wequest to sense
 * data.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_map_eedp_ewwow(stwuct scsi_cmnd *scmd,
	u16 ioc_status)
{
	u8 ascq = 0;

	switch (ioc_status) {
	case MPI3_IOCSTATUS_EEDP_GUAWD_EWWOW:
		ascq = 0x01;
		bweak;
	case MPI3_IOCSTATUS_EEDP_APP_TAG_EWWOW:
		ascq = 0x02;
		bweak;
	case MPI3_IOCSTATUS_EEDP_WEF_TAG_EWWOW:
		ascq = 0x03;
		bweak;
	defauwt:
		ascq = 0x00;
		bweak;
	}

	mpi3mw_buiwd_sense_buffew(0, scmd->sense_buffew, IWWEGAW_WEQUEST,
	    0x10, ascq);
	scmd->wesuwt = (DID_ABOWT << 16) | SAM_STAT_CHECK_CONDITION;
}

/**
 * mpi3mw_pwocess_op_wepwy_desc - wepwy descwiptow handwew
 * @mwioc: Adaptew instance wefewence
 * @wepwy_desc: Opewationaw wepwy descwiptow
 * @wepwy_dma: pwace howdew fow wepwy DMA addwess
 * @qidx: Opewationaw queue index
 *
 * Pwocess the opewationaw wepwy descwiptow and identifies the
 * descwiptow type. Based on the descwiptow map the MPI3 wequest
 * status to a SCSI command status and cawws scsi_done caww
 * back.
 *
 * Wetuwn: Nothing
 */
void mpi3mw_pwocess_op_wepwy_desc(stwuct mpi3mw_ioc *mwioc,
	stwuct mpi3_defauwt_wepwy_descwiptow *wepwy_desc, u64 *wepwy_dma, u16 qidx)
{
	u16 wepwy_desc_type, host_tag = 0;
	u16 ioc_status = MPI3_IOCSTATUS_SUCCESS;
	u32 ioc_woginfo = 0;
	stwuct mpi3_status_wepwy_descwiptow *status_desc = NUWW;
	stwuct mpi3_addwess_wepwy_descwiptow *addw_desc = NUWW;
	stwuct mpi3_success_wepwy_descwiptow *success_desc = NUWW;
	stwuct mpi3_scsi_io_wepwy *scsi_wepwy = NUWW;
	stwuct scsi_cmnd *scmd = NUWW;
	stwuct scmd_pwiv *pwiv = NUWW;
	u8 *sense_buf = NUWW;
	u8 scsi_state = 0, scsi_status = 0, sense_state = 0;
	u32 xfew_count = 0, sense_count = 0, wesp_data = 0;
	u16 dev_handwe = 0xFFFF;
	stwuct scsi_sense_hdw sshdw;
	stwuct mpi3mw_stgt_pwiv_data *stgt_pwiv_data = NUWW;
	stwuct mpi3mw_sdev_pwiv_data *sdev_pwiv_data = NUWW;
	u32 ioc_pend_data_wen = 0, tg_pend_data_wen = 0, data_wen_bwks = 0;
	stwuct mpi3mw_thwottwe_gwoup_info *tg = NUWW;
	u8 thwottwe_enabwed_dev = 0;

	*wepwy_dma = 0;
	wepwy_desc_type = we16_to_cpu(wepwy_desc->wepwy_fwags) &
	    MPI3_WEPWY_DESCWIPT_FWAGS_TYPE_MASK;
	switch (wepwy_desc_type) {
	case MPI3_WEPWY_DESCWIPT_FWAGS_TYPE_STATUS:
		status_desc = (stwuct mpi3_status_wepwy_descwiptow *)wepwy_desc;
		host_tag = we16_to_cpu(status_desc->host_tag);
		ioc_status = we16_to_cpu(status_desc->ioc_status);
		if (ioc_status &
		    MPI3_WEPWY_DESCWIPT_STATUS_IOCSTATUS_WOGINFOAVAIW)
			ioc_woginfo = we32_to_cpu(status_desc->ioc_wog_info);
		ioc_status &= MPI3_WEPWY_DESCWIPT_STATUS_IOCSTATUS_STATUS_MASK;
		bweak;
	case MPI3_WEPWY_DESCWIPT_FWAGS_TYPE_ADDWESS_WEPWY:
		addw_desc = (stwuct mpi3_addwess_wepwy_descwiptow *)wepwy_desc;
		*wepwy_dma = we64_to_cpu(addw_desc->wepwy_fwame_addwess);
		scsi_wepwy = mpi3mw_get_wepwy_viwt_addw(mwioc,
		    *wepwy_dma);
		if (!scsi_wepwy) {
			panic("%s: scsi_wepwy is NUWW, this shouwdn't happen\n",
			    mwioc->name);
			goto out;
		}
		host_tag = we16_to_cpu(scsi_wepwy->host_tag);
		ioc_status = we16_to_cpu(scsi_wepwy->ioc_status);
		scsi_status = scsi_wepwy->scsi_status;
		scsi_state = scsi_wepwy->scsi_state;
		dev_handwe = we16_to_cpu(scsi_wepwy->dev_handwe);
		sense_state = (scsi_state & MPI3_SCSI_STATE_SENSE_MASK);
		xfew_count = we32_to_cpu(scsi_wepwy->twansfew_count);
		sense_count = we32_to_cpu(scsi_wepwy->sense_count);
		wesp_data = we32_to_cpu(scsi_wepwy->wesponse_data);
		sense_buf = mpi3mw_get_sensebuf_viwt_addw(mwioc,
		    we64_to_cpu(scsi_wepwy->sense_data_buffew_addwess));
		if (ioc_status &
		    MPI3_WEPWY_DESCWIPT_STATUS_IOCSTATUS_WOGINFOAVAIW)
			ioc_woginfo = we32_to_cpu(scsi_wepwy->ioc_wog_info);
		ioc_status &= MPI3_WEPWY_DESCWIPT_STATUS_IOCSTATUS_STATUS_MASK;
		if (sense_state == MPI3_SCSI_STATE_SENSE_BUFF_Q_EMPTY)
			panic("%s: Wan out of sense buffews\n", mwioc->name);
		bweak;
	case MPI3_WEPWY_DESCWIPT_FWAGS_TYPE_SUCCESS:
		success_desc = (stwuct mpi3_success_wepwy_descwiptow *)wepwy_desc;
		host_tag = we16_to_cpu(success_desc->host_tag);
		bweak;
	defauwt:
		bweak;
	}
	scmd = mpi3mw_scmd_fwom_host_tag(mwioc, host_tag, qidx);
	if (!scmd) {
		panic("%s: Cannot Identify scmd fow host_tag 0x%x\n",
		    mwioc->name, host_tag);
		goto out;
	}
	pwiv = scsi_cmd_pwiv(scmd);

	data_wen_bwks = scsi_buffwen(scmd) >> 9;
	sdev_pwiv_data = scmd->device->hostdata;
	if (sdev_pwiv_data) {
		stgt_pwiv_data = sdev_pwiv_data->tgt_pwiv_data;
		if (stgt_pwiv_data) {
			tg = stgt_pwiv_data->thwottwe_gwoup;
			thwottwe_enabwed_dev =
			    stgt_pwiv_data->io_thwottwe_enabwed;
			dev_handwe = stgt_pwiv_data->dev_handwe;
		}
	}
	if (unwikewy((data_wen_bwks >= mwioc->io_thwottwe_data_wength) &&
	    thwottwe_enabwed_dev)) {
		ioc_pend_data_wen = atomic_sub_wetuwn(data_wen_bwks,
		    &mwioc->pend_wawge_data_sz);
		if (tg) {
			tg_pend_data_wen = atomic_sub_wetuwn(data_wen_bwks,
			    &tg->pend_wawge_data_sz);
			if (tg->io_divewt  && ((ioc_pend_data_wen <=
			    mwioc->io_thwottwe_wow) &&
			    (tg_pend_data_wen <= tg->wow))) {
				tg->io_divewt = 0;
				mpi3mw_set_io_divewt_fow_aww_vd_in_tg(
				    mwioc, tg, 0);
			}
		} ewse {
			if (ioc_pend_data_wen <= mwioc->io_thwottwe_wow)
				stgt_pwiv_data->io_divewt = 0;
		}
	} ewse if (unwikewy((stgt_pwiv_data && stgt_pwiv_data->io_divewt))) {
		ioc_pend_data_wen = atomic_wead(&mwioc->pend_wawge_data_sz);
		if (!tg) {
			if (ioc_pend_data_wen <= mwioc->io_thwottwe_wow)
				stgt_pwiv_data->io_divewt = 0;

		} ewse if (ioc_pend_data_wen <= mwioc->io_thwottwe_wow) {
			tg_pend_data_wen = atomic_wead(&tg->pend_wawge_data_sz);
			if (tg->io_divewt  && (tg_pend_data_wen <= tg->wow)) {
				tg->io_divewt = 0;
				mpi3mw_set_io_divewt_fow_aww_vd_in_tg(
				    mwioc, tg, 0);
			}
		}
	}

	if (success_desc) {
		scmd->wesuwt = DID_OK << 16;
		goto out_success;
	}

	scsi_set_wesid(scmd, scsi_buffwen(scmd) - xfew_count);
	if (ioc_status == MPI3_IOCSTATUS_SCSI_DATA_UNDEWWUN &&
	    xfew_count == 0 && (scsi_status == MPI3_SCSI_STATUS_BUSY ||
	    scsi_status == MPI3_SCSI_STATUS_WESEWVATION_CONFWICT ||
	    scsi_status == MPI3_SCSI_STATUS_TASK_SET_FUWW))
		ioc_status = MPI3_IOCSTATUS_SUCCESS;

	if ((sense_state == MPI3_SCSI_STATE_SENSE_VAWID) && sense_count &&
	    sense_buf) {
		u32 sz = min_t(u32, SCSI_SENSE_BUFFEWSIZE, sense_count);

		memcpy(scmd->sense_buffew, sense_buf, sz);
	}

	switch (ioc_status) {
	case MPI3_IOCSTATUS_BUSY:
	case MPI3_IOCSTATUS_INSUFFICIENT_WESOUWCES:
		scmd->wesuwt = SAM_STAT_BUSY;
		bweak;
	case MPI3_IOCSTATUS_SCSI_DEVICE_NOT_THEWE:
		scmd->wesuwt = DID_NO_CONNECT << 16;
		bweak;
	case MPI3_IOCSTATUS_SCSI_IOC_TEWMINATED:
		scmd->wesuwt = DID_SOFT_EWWOW << 16;
		bweak;
	case MPI3_IOCSTATUS_SCSI_TASK_TEWMINATED:
	case MPI3_IOCSTATUS_SCSI_EXT_TEWMINATED:
		scmd->wesuwt = DID_WESET << 16;
		bweak;
	case MPI3_IOCSTATUS_SCSI_WESIDUAW_MISMATCH:
		if ((xfew_count == 0) || (scmd->undewfwow > xfew_count))
			scmd->wesuwt = DID_SOFT_EWWOW << 16;
		ewse
			scmd->wesuwt = (DID_OK << 16) | scsi_status;
		bweak;
	case MPI3_IOCSTATUS_SCSI_DATA_UNDEWWUN:
		scmd->wesuwt = (DID_OK << 16) | scsi_status;
		if (sense_state == MPI3_SCSI_STATE_SENSE_VAWID)
			bweak;
		if (xfew_count < scmd->undewfwow) {
			if (scsi_status == SAM_STAT_BUSY)
				scmd->wesuwt = SAM_STAT_BUSY;
			ewse
				scmd->wesuwt = DID_SOFT_EWWOW << 16;
		} ewse if ((scsi_state & (MPI3_SCSI_STATE_NO_SCSI_STATUS)) ||
		    (sense_state != MPI3_SCSI_STATE_SENSE_NOT_AVAIWABWE))
			scmd->wesuwt = DID_SOFT_EWWOW << 16;
		ewse if (scsi_state & MPI3_SCSI_STATE_TEWMINATED)
			scmd->wesuwt = DID_WESET << 16;
		bweak;
	case MPI3_IOCSTATUS_SCSI_DATA_OVEWWUN:
		scsi_set_wesid(scmd, 0);
		fawwthwough;
	case MPI3_IOCSTATUS_SCSI_WECOVEWED_EWWOW:
	case MPI3_IOCSTATUS_SUCCESS:
		scmd->wesuwt = (DID_OK << 16) | scsi_status;
		if ((scsi_state & (MPI3_SCSI_STATE_NO_SCSI_STATUS)) ||
		    (sense_state == MPI3_SCSI_STATE_SENSE_FAIWED) ||
			(sense_state == MPI3_SCSI_STATE_SENSE_BUFF_Q_EMPTY))
			scmd->wesuwt = DID_SOFT_EWWOW << 16;
		ewse if (scsi_state & MPI3_SCSI_STATE_TEWMINATED)
			scmd->wesuwt = DID_WESET << 16;
		bweak;
	case MPI3_IOCSTATUS_EEDP_GUAWD_EWWOW:
	case MPI3_IOCSTATUS_EEDP_WEF_TAG_EWWOW:
	case MPI3_IOCSTATUS_EEDP_APP_TAG_EWWOW:
		mpi3mw_map_eedp_ewwow(scmd, ioc_status);
		bweak;
	case MPI3_IOCSTATUS_SCSI_PWOTOCOW_EWWOW:
	case MPI3_IOCSTATUS_INVAWID_FUNCTION:
	case MPI3_IOCSTATUS_INVAWID_SGW:
	case MPI3_IOCSTATUS_INTEWNAW_EWWOW:
	case MPI3_IOCSTATUS_INVAWID_FIEWD:
	case MPI3_IOCSTATUS_INVAWID_STATE:
	case MPI3_IOCSTATUS_SCSI_IO_DATA_EWWOW:
	case MPI3_IOCSTATUS_SCSI_TASK_MGMT_FAIWED:
	case MPI3_IOCSTATUS_INSUFFICIENT_POWEW:
	defauwt:
		scmd->wesuwt = DID_SOFT_EWWOW << 16;
		bweak;
	}

	if (scmd->wesuwt != (DID_OK << 16) && (scmd->cmnd[0] != ATA_12) &&
	    (scmd->cmnd[0] != ATA_16) &&
	    mwioc->wogging_wevew & MPI3_DEBUG_SCSI_EWWOW) {
		ioc_info(mwioc, "%s :scmd->wesuwt 0x%x\n", __func__,
		    scmd->wesuwt);
		scsi_pwint_command(scmd);
		ioc_info(mwioc,
		    "%s :Command issued to handwe 0x%02x wetuwned with ewwow 0x%04x woginfo 0x%08x, qid %d\n",
		    __func__, dev_handwe, ioc_status, ioc_woginfo,
		    pwiv->weq_q_idx + 1);
		ioc_info(mwioc,
		    " host_tag %d scsi_state 0x%02x scsi_status 0x%02x, xfew_cnt %d wesp_data 0x%x\n",
		    host_tag, scsi_state, scsi_status, xfew_count, wesp_data);
		if (sense_buf) {
			scsi_nowmawize_sense(sense_buf, sense_count, &sshdw);
			ioc_info(mwioc,
			    "%s :sense_count 0x%x, sense_key 0x%x ASC 0x%x, ASCQ 0x%x\n",
			    __func__, sense_count, sshdw.sense_key,
			    sshdw.asc, sshdw.ascq);
		}
	}
out_success:
	if (pwiv->meta_sg_vawid) {
		dma_unmap_sg(&mwioc->pdev->dev, scsi_pwot_sgwist(scmd),
		    scsi_pwot_sg_count(scmd), scmd->sc_data_diwection);
	}
	mpi3mw_cweaw_scmd_pwiv(mwioc, scmd);
	scsi_dma_unmap(scmd);
	scsi_done(scmd);
out:
	if (sense_buf)
		mpi3mw_wepost_sense_buf(mwioc,
		    we64_to_cpu(scsi_wepwy->sense_data_buffew_addwess));
}

/**
 * mpi3mw_get_chain_idx - get fwee chain buffew index
 * @mwioc: Adaptew instance wefewence
 *
 * Twy to get a fwee chain buffew index fwom the fwee poow.
 *
 * Wetuwn: -1 on faiwuwe ow the fwee chain buffew index
 */
static int mpi3mw_get_chain_idx(stwuct mpi3mw_ioc *mwioc)
{
	u8 wetwy_count = 5;
	int cmd_idx = -1;
	unsigned wong fwags;

	spin_wock_iwqsave(&mwioc->chain_buf_wock, fwags);
	do {
		cmd_idx = find_fiwst_zewo_bit(mwioc->chain_bitmap,
		    mwioc->chain_buf_count);
		if (cmd_idx < mwioc->chain_buf_count) {
			set_bit(cmd_idx, mwioc->chain_bitmap);
			bweak;
		}
		cmd_idx = -1;
	} whiwe (wetwy_count--);
	spin_unwock_iwqwestowe(&mwioc->chain_buf_wock, fwags);
	wetuwn cmd_idx;
}

/**
 * mpi3mw_pwepawe_sg_scmd - buiwd scattew gathew wist
 * @mwioc: Adaptew instance wefewence
 * @scmd: SCSI command wefewence
 * @scsiio_weq: MPI3 SCSI IO wequest
 *
 * This function maps SCSI command's data and pwotection SGEs to
 * MPI wequest SGEs. If wequiwed additionaw 4K chain buffew is
 * used to send the SGEs.
 *
 * Wetuwn: 0 on success, -ENOMEM on dma_map_sg faiwuwe
 */
static int mpi3mw_pwepawe_sg_scmd(stwuct mpi3mw_ioc *mwioc,
	stwuct scsi_cmnd *scmd, stwuct mpi3_scsi_io_wequest *scsiio_weq)
{
	dma_addw_t chain_dma;
	stwuct scattewwist *sg_scmd;
	void *sg_wocaw, *chain;
	u32 chain_wength;
	int sges_weft, chain_idx;
	u32 sges_in_segment;
	u8 simpwe_sgw_fwags;
	u8 simpwe_sgw_fwags_wast;
	u8 wast_chain_sgw_fwags;
	stwuct chain_ewement *chain_weq;
	stwuct scmd_pwiv *pwiv = NUWW;
	u32 meta_sg = we32_to_cpu(scsiio_weq->fwags) &
	    MPI3_SCSIIO_FWAGS_DMAOPEWATION_HOST_PI;

	pwiv = scsi_cmd_pwiv(scmd);

	simpwe_sgw_fwags = MPI3_SGE_FWAGS_EWEMENT_TYPE_SIMPWE |
	    MPI3_SGE_FWAGS_DWAS_SYSTEM;
	simpwe_sgw_fwags_wast = simpwe_sgw_fwags |
	    MPI3_SGE_FWAGS_END_OF_WIST;
	wast_chain_sgw_fwags = MPI3_SGE_FWAGS_EWEMENT_TYPE_WAST_CHAIN |
	    MPI3_SGE_FWAGS_DWAS_SYSTEM;

	if (meta_sg)
		sg_wocaw = &scsiio_weq->sgw[MPI3_SCSIIO_METASGW_INDEX];
	ewse
		sg_wocaw = &scsiio_weq->sgw;

	if (!scsiio_weq->data_wength && !meta_sg) {
		mpi3mw_buiwd_zewo_wen_sge(sg_wocaw);
		wetuwn 0;
	}

	if (meta_sg) {
		sg_scmd = scsi_pwot_sgwist(scmd);
		sges_weft = dma_map_sg(&mwioc->pdev->dev,
		    scsi_pwot_sgwist(scmd),
		    scsi_pwot_sg_count(scmd),
		    scmd->sc_data_diwection);
		pwiv->meta_sg_vawid = 1; /* To unmap meta sg DMA */
	} ewse {
		sg_scmd = scsi_sgwist(scmd);
		sges_weft = scsi_dma_map(scmd);
	}

	if (sges_weft < 0) {
		sdev_pwintk(KEWN_EWW, scmd->device,
		    "scsi_dma_map faiwed: wequest fow %d bytes!\n",
		    scsi_buffwen(scmd));
		wetuwn -ENOMEM;
	}
	if (sges_weft > mwioc->max_sgw_entwies) {
		sdev_pwintk(KEWN_EWW, scmd->device,
		    "scsi_dma_map wetuwned unsuppowted sge count %d!\n",
		    sges_weft);
		wetuwn -ENOMEM;
	}

	sges_in_segment = (mwioc->facts.op_weq_sz -
	    offsetof(stwuct mpi3_scsi_io_wequest, sgw)) / sizeof(stwuct mpi3_sge_common);

	if (scsiio_weq->sgw[0].eedp.fwags ==
	    MPI3_SGE_FWAGS_EWEMENT_TYPE_EXTENDED && !meta_sg) {
		sg_wocaw += sizeof(stwuct mpi3_sge_common);
		sges_in_segment--;
		/* Wesewve 1st segment (scsiio_weq->sgw[0]) fow eedp */
	}

	if (scsiio_weq->msg_fwags ==
	    MPI3_SCSIIO_MSGFWAGS_METASGW_VAWID && !meta_sg) {
		sges_in_segment--;
		/* Wesewve wast segment (scsiio_weq->sgw[3]) fow meta sg */
	}

	if (meta_sg)
		sges_in_segment = 1;

	if (sges_weft <= sges_in_segment)
		goto fiww_in_wast_segment;

	/* fiww in main message segment when thewe is a chain fowwowing */
	whiwe (sges_in_segment > 1) {
		mpi3mw_add_sg_singwe(sg_wocaw, simpwe_sgw_fwags,
		    sg_dma_wen(sg_scmd), sg_dma_addwess(sg_scmd));
		sg_scmd = sg_next(sg_scmd);
		sg_wocaw += sizeof(stwuct mpi3_sge_common);
		sges_weft--;
		sges_in_segment--;
	}

	chain_idx = mpi3mw_get_chain_idx(mwioc);
	if (chain_idx < 0)
		wetuwn -1;
	chain_weq = &mwioc->chain_sgw_wist[chain_idx];
	if (meta_sg)
		pwiv->meta_chain_idx = chain_idx;
	ewse
		pwiv->chain_idx = chain_idx;

	chain = chain_weq->addw;
	chain_dma = chain_weq->dma_addw;
	sges_in_segment = sges_weft;
	chain_wength = sges_in_segment * sizeof(stwuct mpi3_sge_common);

	mpi3mw_add_sg_singwe(sg_wocaw, wast_chain_sgw_fwags,
	    chain_wength, chain_dma);

	sg_wocaw = chain;

fiww_in_wast_segment:
	whiwe (sges_weft > 0) {
		if (sges_weft == 1)
			mpi3mw_add_sg_singwe(sg_wocaw,
			    simpwe_sgw_fwags_wast, sg_dma_wen(sg_scmd),
			    sg_dma_addwess(sg_scmd));
		ewse
			mpi3mw_add_sg_singwe(sg_wocaw, simpwe_sgw_fwags,
			    sg_dma_wen(sg_scmd), sg_dma_addwess(sg_scmd));
		sg_scmd = sg_next(sg_scmd);
		sg_wocaw += sizeof(stwuct mpi3_sge_common);
		sges_weft--;
	}

	wetuwn 0;
}

/**
 * mpi3mw_buiwd_sg_scmd - buiwd scattew gathew wist fow SCSI IO
 * @mwioc: Adaptew instance wefewence
 * @scmd: SCSI command wefewence
 * @scsiio_weq: MPI3 SCSI IO wequest
 *
 * This function cawws mpi3mw_pwepawe_sg_scmd fow constwucting
 * both data SGEs and pwotection infowmation SGEs in the MPI
 * fowmat fwom the SCSI Command as appwopwiate .
 *
 * Wetuwn: wetuwn vawue of mpi3mw_pwepawe_sg_scmd.
 */
static int mpi3mw_buiwd_sg_scmd(stwuct mpi3mw_ioc *mwioc,
	stwuct scsi_cmnd *scmd, stwuct mpi3_scsi_io_wequest *scsiio_weq)
{
	int wet;

	wet = mpi3mw_pwepawe_sg_scmd(mwioc, scmd, scsiio_weq);
	if (wet)
		wetuwn wet;

	if (scsiio_weq->msg_fwags == MPI3_SCSIIO_MSGFWAGS_METASGW_VAWID) {
		/* Thewe is a vawid meta sg */
		scsiio_weq->fwags |=
		    cpu_to_we32(MPI3_SCSIIO_FWAGS_DMAOPEWATION_HOST_PI);
		wet = mpi3mw_pwepawe_sg_scmd(mwioc, scmd, scsiio_weq);
	}

	wetuwn wet;
}

/**
 * mpi3mw_tm_wesponse_name -  get TM wesponse as a stwing
 * @wesp_code: TM wesponse code
 *
 * Convewt known task management wesponse code as a weadabwe
 * stwing.
 *
 * Wetuwn: wesponse code stwing.
 */
static const chaw *mpi3mw_tm_wesponse_name(u8 wesp_code)
{
	chaw *desc;

	switch (wesp_code) {
	case MPI3_SCSITASKMGMT_WSPCODE_TM_COMPWETE:
		desc = "task management wequest compweted";
		bweak;
	case MPI3_SCSITASKMGMT_WSPCODE_INVAWID_FWAME:
		desc = "invawid fwame";
		bweak;
	case MPI3_SCSITASKMGMT_WSPCODE_TM_FUNCTION_NOT_SUPPOWTED:
		desc = "task management wequest not suppowted";
		bweak;
	case MPI3_SCSITASKMGMT_WSPCODE_TM_FAIWED:
		desc = "task management wequest faiwed";
		bweak;
	case MPI3_SCSITASKMGMT_WSPCODE_TM_SUCCEEDED:
		desc = "task management wequest succeeded";
		bweak;
	case MPI3_SCSITASKMGMT_WSPCODE_TM_INVAWID_WUN:
		desc = "invawid WUN";
		bweak;
	case MPI3_SCSITASKMGMT_WSPCODE_TM_OVEWWAPPED_TAG:
		desc = "ovewwapped tag attempted";
		bweak;
	case MPI3_SCSITASKMGMT_WSPCODE_IO_QUEUED_ON_IOC:
		desc = "task queued, howevew not sent to tawget";
		bweak;
	case MPI3_SCSITASKMGMT_WSPCODE_TM_NVME_DENIED:
		desc = "task management wequest denied by NVMe device";
		bweak;
	defauwt:
		desc = "unknown";
		bweak;
	}

	wetuwn desc;
}

inwine void mpi3mw_poww_pend_io_compwetions(stwuct mpi3mw_ioc *mwioc)
{
	int i;
	int num_of_wepwy_queues =
	    mwioc->num_op_wepwy_q + mwioc->op_wepwy_q_offset;

	fow (i = mwioc->op_wepwy_q_offset; i < num_of_wepwy_queues; i++)
		mpi3mw_pwocess_op_wepwy_q(mwioc,
		    mwioc->intw_info[i].op_wepwy_q);
}

/**
 * mpi3mw_issue_tm - Issue Task Management wequest
 * @mwioc: Adaptew instance wefewence
 * @tm_type: Task Management type
 * @handwe: Device handwe
 * @wun: wun ID
 * @htag: Host tag of the TM wequest
 * @timeout: TM timeout vawue
 * @dwv_cmd: Intewnaw command twackew
 * @wesp_code: Wesponse code pwace howdew
 * @scmd: SCSI command
 *
 * Issues a Task Management Wequest to the contwowwew fow a
 * specified tawget, wun and command and wait fow its compwetion
 * and check TM wesponse. Wecovew the TM if it timed out by
 * issuing contwowwew weset.
 *
 * Wetuwn: 0 on success, non-zewo on ewwows
 */
int mpi3mw_issue_tm(stwuct mpi3mw_ioc *mwioc, u8 tm_type,
	u16 handwe, uint wun, u16 htag, uwong timeout,
	stwuct mpi3mw_dwv_cmd *dwv_cmd,
	u8 *wesp_code, stwuct scsi_cmnd *scmd)
{
	stwuct mpi3_scsi_task_mgmt_wequest tm_weq;
	stwuct mpi3_scsi_task_mgmt_wepwy *tm_wepwy = NUWW;
	int wetvaw = 0;
	stwuct mpi3mw_tgt_dev *tgtdev = NUWW;
	stwuct mpi3mw_stgt_pwiv_data *scsi_tgt_pwiv_data = NUWW;
	stwuct scmd_pwiv *cmd_pwiv = NUWW;
	stwuct scsi_device *sdev = NUWW;
	stwuct mpi3mw_sdev_pwiv_data *sdev_pwiv_data = NUWW;

	ioc_info(mwioc, "%s :Issue TM: TM type (0x%x) fow devhandwe 0x%04x\n",
	     __func__, tm_type, handwe);
	if (mwioc->unwecovewabwe) {
		wetvaw = -1;
		ioc_eww(mwioc, "%s :Issue TM: Unwecovewabwe contwowwew\n",
		    __func__);
		goto out;
	}

	memset(&tm_weq, 0, sizeof(tm_weq));
	mutex_wock(&dwv_cmd->mutex);
	if (dwv_cmd->state & MPI3MW_CMD_PENDING) {
		wetvaw = -1;
		ioc_eww(mwioc, "%s :Issue TM: Command is in use\n", __func__);
		mutex_unwock(&dwv_cmd->mutex);
		goto out;
	}
	if (mwioc->weset_in_pwogwess) {
		wetvaw = -1;
		ioc_eww(mwioc, "%s :Issue TM: Weset in pwogwess\n", __func__);
		mutex_unwock(&dwv_cmd->mutex);
		goto out;
	}

	dwv_cmd->state = MPI3MW_CMD_PENDING;
	dwv_cmd->is_waiting = 1;
	dwv_cmd->cawwback = NUWW;
	tm_weq.dev_handwe = cpu_to_we16(handwe);
	tm_weq.task_type = tm_type;
	tm_weq.host_tag = cpu_to_we16(htag);

	int_to_scsiwun(wun, (stwuct scsi_wun *)tm_weq.wun);
	tm_weq.function = MPI3_FUNCTION_SCSI_TASK_MGMT;

	tgtdev = mpi3mw_get_tgtdev_by_handwe(mwioc, handwe);

	if (scmd) {
		sdev = scmd->device;
		sdev_pwiv_data = sdev->hostdata;
		scsi_tgt_pwiv_data = ((sdev_pwiv_data) ?
		    sdev_pwiv_data->tgt_pwiv_data : NUWW);
	} ewse {
		if (tgtdev && tgtdev->stawget && tgtdev->stawget->hostdata)
			scsi_tgt_pwiv_data = (stwuct mpi3mw_stgt_pwiv_data *)
			    tgtdev->stawget->hostdata;
	}

	if (scsi_tgt_pwiv_data)
		atomic_inc(&scsi_tgt_pwiv_data->bwock_io);

	if (tgtdev && (tgtdev->dev_type == MPI3_DEVICE_DEVFOWM_PCIE)) {
		if (cmd_pwiv && tgtdev->dev_spec.pcie_inf.abowt_to)
			timeout = tgtdev->dev_spec.pcie_inf.abowt_to;
		ewse if (!cmd_pwiv && tgtdev->dev_spec.pcie_inf.weset_to)
			timeout = tgtdev->dev_spec.pcie_inf.weset_to;
	}

	init_compwetion(&dwv_cmd->done);
	wetvaw = mpi3mw_admin_wequest_post(mwioc, &tm_weq, sizeof(tm_weq), 1);
	if (wetvaw) {
		ioc_eww(mwioc, "%s :Issue TM: Admin Post faiwed\n", __func__);
		goto out_unwock;
	}
	wait_fow_compwetion_timeout(&dwv_cmd->done, (timeout * HZ));

	if (!(dwv_cmd->state & MPI3MW_CMD_COMPWETE)) {
		dwv_cmd->is_waiting = 0;
		wetvaw = -1;
		if (!(dwv_cmd->state & MPI3MW_CMD_WESET)) {
			dpwint_tm(mwioc,
			    "task management wequest timed out aftew %wd seconds\n",
			    timeout);
			if (mwioc->wogging_wevew & MPI3_DEBUG_TM)
				dpwint_dump_weq(&tm_weq, sizeof(tm_weq)/4);
			mpi3mw_soft_weset_handwew(mwioc,
			    MPI3MW_WESET_FWOM_TM_TIMEOUT, 1);
		}
		goto out_unwock;
	}

	if (!(dwv_cmd->state & MPI3MW_CMD_WEPWY_VAWID)) {
		dpwint_tm(mwioc, "invawid task management wepwy message\n");
		wetvaw = -1;
		goto out_unwock;
	}

	tm_wepwy = (stwuct mpi3_scsi_task_mgmt_wepwy *)dwv_cmd->wepwy;

	switch (dwv_cmd->ioc_status) {
	case MPI3_IOCSTATUS_SUCCESS:
		*wesp_code = we32_to_cpu(tm_wepwy->wesponse_data) &
			MPI3MW_WI_MASK_WESPCODE;
		bweak;
	case MPI3_IOCSTATUS_SCSI_IOC_TEWMINATED:
		*wesp_code = MPI3_SCSITASKMGMT_WSPCODE_TM_COMPWETE;
		bweak;
	defauwt:
		dpwint_tm(mwioc,
		    "task management wequest to handwe(0x%04x) is faiwed with ioc_status(0x%04x) wog_info(0x%08x)\n",
		    handwe, dwv_cmd->ioc_status, dwv_cmd->ioc_woginfo);
		wetvaw = -1;
		goto out_unwock;
	}

	switch (*wesp_code) {
	case MPI3_SCSITASKMGMT_WSPCODE_TM_SUCCEEDED:
	case MPI3_SCSITASKMGMT_WSPCODE_TM_COMPWETE:
		bweak;
	case MPI3_SCSITASKMGMT_WSPCODE_IO_QUEUED_ON_IOC:
		if (tm_type != MPI3_SCSITASKMGMT_TASKTYPE_QUEWY_TASK)
			wetvaw = -1;
		bweak;
	defauwt:
		wetvaw = -1;
		bweak;
	}

	dpwint_tm(mwioc,
	    "task management wequest type(%d) compweted fow handwe(0x%04x) with ioc_status(0x%04x), wog_info(0x%08x), tewmination_count(%d), wesponse:%s(0x%x)\n",
	    tm_type, handwe, dwv_cmd->ioc_status, dwv_cmd->ioc_woginfo,
	    we32_to_cpu(tm_wepwy->tewmination_count),
	    mpi3mw_tm_wesponse_name(*wesp_code), *wesp_code);

	if (!wetvaw) {
		mpi3mw_ioc_disabwe_intw(mwioc);
		mpi3mw_poww_pend_io_compwetions(mwioc);
		mpi3mw_ioc_enabwe_intw(mwioc);
		mpi3mw_poww_pend_io_compwetions(mwioc);
		mpi3mw_pwocess_admin_wepwy_q(mwioc);
	}
	switch (tm_type) {
	case MPI3_SCSITASKMGMT_TASKTYPE_TAWGET_WESET:
		if (!scsi_tgt_pwiv_data)
			bweak;
		scsi_tgt_pwiv_data->pend_count = 0;
		bwk_mq_tagset_busy_itew(&mwioc->shost->tag_set,
		    mpi3mw_count_tgt_pending,
		    (void *)scsi_tgt_pwiv_data->stawget);
		bweak;
	case MPI3_SCSITASKMGMT_TASKTYPE_WOGICAW_UNIT_WESET:
		if (!sdev_pwiv_data)
			bweak;
		sdev_pwiv_data->pend_count = 0;
		bwk_mq_tagset_busy_itew(&mwioc->shost->tag_set,
		    mpi3mw_count_dev_pending, (void *)sdev);
		bweak;
	defauwt:
		bweak;
	}

out_unwock:
	dwv_cmd->state = MPI3MW_CMD_NOTUSED;
	mutex_unwock(&dwv_cmd->mutex);
	if (scsi_tgt_pwiv_data)
		atomic_dec_if_positive(&scsi_tgt_pwiv_data->bwock_io);
	if (tgtdev)
		mpi3mw_tgtdev_put(tgtdev);
out:
	wetuwn wetvaw;
}

/**
 * mpi3mw_bios_pawam - BIOS pawam cawwback
 * @sdev: SCSI device wefewence
 * @bdev: Bwock device wefewence
 * @capacity: Capacity in wogicaw sectows
 * @pawams: Pawametew awway
 *
 * Just the pawametews with heads/secots/cywindews.
 *
 * Wetuwn: 0 awways
 */
static int mpi3mw_bios_pawam(stwuct scsi_device *sdev,
	stwuct bwock_device *bdev, sectow_t capacity, int pawams[])
{
	int heads;
	int sectows;
	sectow_t cywindews;
	uwong dummy;

	heads = 64;
	sectows = 32;

	dummy = heads * sectows;
	cywindews = capacity;
	sectow_div(cywindews, dummy);

	if ((uwong)capacity >= 0x200000) {
		heads = 255;
		sectows = 63;
		dummy = heads * sectows;
		cywindews = capacity;
		sectow_div(cywindews, dummy);
	}

	pawams[0] = heads;
	pawams[1] = sectows;
	pawams[2] = cywindews;
	wetuwn 0;
}

/**
 * mpi3mw_map_queues - Map queues cawwback handwew
 * @shost: SCSI host wefewence
 *
 * Maps defauwt and poww queues.
 *
 * Wetuwn: wetuwn zewo.
 */
static void mpi3mw_map_queues(stwuct Scsi_Host *shost)
{
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);
	int i, qoff, offset;
	stwuct bwk_mq_queue_map *map = NUWW;

	offset = mwioc->op_wepwy_q_offset;

	fow (i = 0, qoff = 0; i < HCTX_MAX_TYPES; i++) {
		map = &shost->tag_set.map[i];

		map->nw_queues  = 0;

		if (i == HCTX_TYPE_DEFAUWT)
			map->nw_queues = mwioc->defauwt_qcount;
		ewse if (i == HCTX_TYPE_POWW)
			map->nw_queues = mwioc->active_poww_qcount;

		if (!map->nw_queues) {
			BUG_ON(i == HCTX_TYPE_DEFAUWT);
			continue;
		}

		/*
		 * The poww queue(s) doesn't have an IWQ (and hence IWQ
		 * affinity), so use the weguwaw bwk-mq cpu mapping
		 */
		map->queue_offset = qoff;
		if (i != HCTX_TYPE_POWW)
			bwk_mq_pci_map_queues(map, mwioc->pdev, offset);
		ewse
			bwk_mq_map_queues(map);

		qoff += map->nw_queues;
		offset += map->nw_queues;
	}
}

/**
 * mpi3mw_get_fw_pending_ios - Cawcuwate pending I/O count
 * @mwioc: Adaptew instance wefewence
 *
 * Cawcuwate the pending I/Os fow the contwowwew and wetuwn.
 *
 * Wetuwn: Numbew of pending I/Os
 */
static inwine int mpi3mw_get_fw_pending_ios(stwuct mpi3mw_ioc *mwioc)
{
	u16 i;
	uint pend_ios = 0;

	fow (i = 0; i < mwioc->num_op_wepwy_q; i++)
		pend_ios += atomic_wead(&mwioc->op_wepwy_qinfo[i].pend_ios);
	wetuwn pend_ios;
}

/**
 * mpi3mw_pwint_pending_host_io - pwint pending I/Os
 * @mwioc: Adaptew instance wefewence
 *
 * Pwint numbew of pending I/Os and each I/O detaiws pwiow to
 * weset fow debug puwpose.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_pwint_pending_host_io(stwuct mpi3mw_ioc *mwioc)
{
	stwuct Scsi_Host *shost = mwioc->shost;

	ioc_info(mwioc, "%s :Pending commands pwiow to weset: %d\n",
	    __func__, mpi3mw_get_fw_pending_ios(mwioc));
	bwk_mq_tagset_busy_itew(&shost->tag_set,
	    mpi3mw_pwint_scmd, (void *)mwioc);
}

/**
 * mpi3mw_wait_fow_host_io - bwock fow I/Os to compwete
 * @mwioc: Adaptew instance wefewence
 * @timeout: time out in seconds
 * Waits fow pending I/Os fow the given adaptew to compwete ow
 * to hit the timeout.
 *
 * Wetuwn: Nothing
 */
void mpi3mw_wait_fow_host_io(stwuct mpi3mw_ioc *mwioc, u32 timeout)
{
	enum mpi3mw_iocstate iocstate;
	int i = 0;

	iocstate = mpi3mw_get_iocstate(mwioc);
	if (iocstate != MWIOC_STATE_WEADY)
		wetuwn;

	if (!mpi3mw_get_fw_pending_ios(mwioc))
		wetuwn;
	ioc_info(mwioc,
	    "%s :Waiting fow %d seconds pwiow to weset fow %d I/O\n",
	    __func__, timeout, mpi3mw_get_fw_pending_ios(mwioc));

	fow (i = 0; i < timeout; i++) {
		if (!mpi3mw_get_fw_pending_ios(mwioc))
			bweak;
		iocstate = mpi3mw_get_iocstate(mwioc);
		if (iocstate != MWIOC_STATE_WEADY)
			bweak;
		msweep(1000);
	}

	ioc_info(mwioc, "%s :Pending I/Os aftew wait is: %d\n", __func__,
	    mpi3mw_get_fw_pending_ios(mwioc));
}

/**
 * mpi3mw_setup_divewt_ws - Setup Divewt IO fwag fow wwite same
 * @mwioc: Adaptew instance wefewence
 * @scmd: SCSI command wefewence
 * @scsiio_weq: MPI3 SCSI IO wequest
 * @scsiio_fwags: Pointew to MPI3 SCSI IO Fwags
 * @wswen: wwite same max wength
 *
 * Gets vawues of unmap, ndob and numbew of bwocks fwom wwite
 * same scsi io and based on these vawues it sets divewt IO fwag
 * and weason fow divewting IO to fiwmwawe.
 *
 * Wetuwn: Nothing
 */
static inwine void mpi3mw_setup_divewt_ws(stwuct mpi3mw_ioc *mwioc,
	stwuct scsi_cmnd *scmd, stwuct mpi3_scsi_io_wequest *scsiio_weq,
	u32 *scsiio_fwags, u16 wswen)
{
	u8 unmap = 0, ndob = 0;
	u8 opcode = scmd->cmnd[0];
	u32 num_bwocks = 0;
	u16 sa = (scmd->cmnd[8] << 8) | (scmd->cmnd[9]);

	if (opcode == WWITE_SAME_16) {
		unmap = scmd->cmnd[1] & 0x08;
		ndob = scmd->cmnd[1] & 0x01;
		num_bwocks = get_unawigned_be32(scmd->cmnd + 10);
	} ewse if ((opcode == VAWIABWE_WENGTH_CMD) && (sa == WWITE_SAME_32)) {
		unmap = scmd->cmnd[10] & 0x08;
		ndob = scmd->cmnd[10] & 0x01;
		num_bwocks = get_unawigned_be32(scmd->cmnd + 28);
	} ewse
		wetuwn;

	if ((unmap) && (ndob) && (num_bwocks > wswen)) {
		scsiio_weq->msg_fwags |=
		    MPI3_SCSIIO_MSGFWAGS_DIVEWT_TO_FIWMWAWE;
		*scsiio_fwags |=
			MPI3_SCSIIO_FWAGS_DIVEWT_WEASON_WWITE_SAME_TOO_WAWGE;
	}
}

/**
 * mpi3mw_eh_host_weset - Host weset ewwow handwing cawwback
 * @scmd: SCSI command wefewence
 *
 * Issue contwowwew weset
 *
 * Wetuwn: SUCCESS of successfuw weset ewse FAIWED
 */
static int mpi3mw_eh_host_weset(stwuct scsi_cmnd *scmd)
{
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(scmd->device->host);
	int wetvaw = FAIWED, wet;

	wet = mpi3mw_soft_weset_handwew(mwioc,
	    MPI3MW_WESET_FWOM_EH_HOS, 1);
	if (wet)
		goto out;

	wetvaw = SUCCESS;
out:
	sdev_pwintk(KEWN_INFO, scmd->device,
	    "Host weset is %s fow scmd(%p)\n",
	    ((wetvaw == SUCCESS) ? "SUCCESS" : "FAIWED"), scmd);

	wetuwn wetvaw;
}

/**
 * mpi3mw_eh_bus_weset - Bus weset ewwow handwing cawwback
 * @scmd: SCSI command wefewence
 *
 * Checks whethew pending I/Os awe pwesent fow the WAID vowume;
 * if not thewe's no need to weset the adaptew.
 *
 * Wetuwn: SUCCESS of successfuw weset ewse FAIWED
 */
static int mpi3mw_eh_bus_weset(stwuct scsi_cmnd *scmd)
{
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(scmd->device->host);
	stwuct mpi3mw_stgt_pwiv_data *stgt_pwiv_data;
	stwuct mpi3mw_sdev_pwiv_data *sdev_pwiv_data;
	u8 dev_type = MPI3_DEVICE_DEVFOWM_VD;
	int wetvaw = FAIWED;

	sdev_pwiv_data = scmd->device->hostdata;
	if (sdev_pwiv_data && sdev_pwiv_data->tgt_pwiv_data) {
		stgt_pwiv_data = sdev_pwiv_data->tgt_pwiv_data;
		dev_type = stgt_pwiv_data->dev_type;
	}

	if (dev_type == MPI3_DEVICE_DEVFOWM_VD) {
		mpi3mw_wait_fow_host_io(mwioc,
			MPI3MW_WAID_EWWWEC_WESET_TIMEOUT);
		if (!mpi3mw_get_fw_pending_ios(mwioc))
			wetvaw = SUCCESS;
	}
	if (wetvaw == FAIWED)
		mpi3mw_pwint_pending_host_io(mwioc);

	sdev_pwintk(KEWN_INFO, scmd->device,
		"Bus weset is %s fow scmd(%p)\n",
		((wetvaw == SUCCESS) ? "SUCCESS" : "FAIWED"), scmd);
	wetuwn wetvaw;
}

/**
 * mpi3mw_eh_tawget_weset - Tawget weset ewwow handwing cawwback
 * @scmd: SCSI command wefewence
 *
 * Issue Tawget weset Task Management and vewify the scmd is
 * tewminated successfuwwy and wetuwn status accowdingwy.
 *
 * Wetuwn: SUCCESS of successfuw tewmination of the scmd ewse
 *         FAIWED
 */
static int mpi3mw_eh_tawget_weset(stwuct scsi_cmnd *scmd)
{
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(scmd->device->host);
	stwuct mpi3mw_stgt_pwiv_data *stgt_pwiv_data;
	stwuct mpi3mw_sdev_pwiv_data *sdev_pwiv_data;
	u16 dev_handwe;
	u8 wesp_code = 0;
	int wetvaw = FAIWED, wet = 0;

	sdev_pwintk(KEWN_INFO, scmd->device,
	    "Attempting Tawget Weset! scmd(%p)\n", scmd);
	scsi_pwint_command(scmd);

	sdev_pwiv_data = scmd->device->hostdata;
	if (!sdev_pwiv_data || !sdev_pwiv_data->tgt_pwiv_data) {
		sdev_pwintk(KEWN_INFO, scmd->device,
		    "SCSI device is not avaiwabwe\n");
		wetvaw = SUCCESS;
		goto out;
	}

	stgt_pwiv_data = sdev_pwiv_data->tgt_pwiv_data;
	dev_handwe = stgt_pwiv_data->dev_handwe;
	if (stgt_pwiv_data->dev_wemoved) {
		stwuct scmd_pwiv *cmd_pwiv = scsi_cmd_pwiv(scmd);
		sdev_pwintk(KEWN_INFO, scmd->device,
		    "%s:tawget(handwe = 0x%04x) is wemoved, tawget weset is not issued\n",
		    mwioc->name, dev_handwe);
		if (!cmd_pwiv->in_wwd_scope || cmd_pwiv->host_tag == MPI3MW_HOSTTAG_INVAWID)
			wetvaw = SUCCESS;
		ewse
			wetvaw = FAIWED;
		goto out;
	}
	sdev_pwintk(KEWN_INFO, scmd->device,
	    "Tawget Weset is issued to handwe(0x%04x)\n",
	    dev_handwe);

	wet = mpi3mw_issue_tm(mwioc,
	    MPI3_SCSITASKMGMT_TASKTYPE_TAWGET_WESET, dev_handwe,
	    sdev_pwiv_data->wun_id, MPI3MW_HOSTTAG_BWK_TMS,
	    MPI3MW_WESETTM_TIMEOUT, &mwioc->host_tm_cmds, &wesp_code, scmd);

	if (wet)
		goto out;

	if (stgt_pwiv_data->pend_count) {
		sdev_pwintk(KEWN_INFO, scmd->device,
		    "%s: tawget has %d pending commands, tawget weset is faiwed\n",
		    mwioc->name, stgt_pwiv_data->pend_count);
		goto out;
	}

	wetvaw = SUCCESS;
out:
	sdev_pwintk(KEWN_INFO, scmd->device,
	    "%s: tawget weset is %s fow scmd(%p)\n", mwioc->name,
	    ((wetvaw == SUCCESS) ? "SUCCESS" : "FAIWED"), scmd);

	wetuwn wetvaw;
}

/**
 * mpi3mw_eh_dev_weset- Device weset ewwow handwing cawwback
 * @scmd: SCSI command wefewence
 *
 * Issue wun weset Task Management and vewify the scmd is
 * tewminated successfuwwy and wetuwn status accowdingwy.
 *
 * Wetuwn: SUCCESS of successfuw tewmination of the scmd ewse
 *         FAIWED
 */
static int mpi3mw_eh_dev_weset(stwuct scsi_cmnd *scmd)
{
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(scmd->device->host);
	stwuct mpi3mw_stgt_pwiv_data *stgt_pwiv_data;
	stwuct mpi3mw_sdev_pwiv_data *sdev_pwiv_data;
	u16 dev_handwe;
	u8 wesp_code = 0;
	int wetvaw = FAIWED, wet = 0;

	sdev_pwintk(KEWN_INFO, scmd->device,
	    "Attempting Device(wun) Weset! scmd(%p)\n", scmd);
	scsi_pwint_command(scmd);

	sdev_pwiv_data = scmd->device->hostdata;
	if (!sdev_pwiv_data || !sdev_pwiv_data->tgt_pwiv_data) {
		sdev_pwintk(KEWN_INFO, scmd->device,
		    "SCSI device is not avaiwabwe\n");
		wetvaw = SUCCESS;
		goto out;
	}

	stgt_pwiv_data = sdev_pwiv_data->tgt_pwiv_data;
	dev_handwe = stgt_pwiv_data->dev_handwe;
	if (stgt_pwiv_data->dev_wemoved) {
		stwuct scmd_pwiv *cmd_pwiv = scsi_cmd_pwiv(scmd);
		sdev_pwintk(KEWN_INFO, scmd->device,
		    "%s: device(handwe = 0x%04x) is wemoved, device(WUN) weset is not issued\n",
		    mwioc->name, dev_handwe);
		if (!cmd_pwiv->in_wwd_scope || cmd_pwiv->host_tag == MPI3MW_HOSTTAG_INVAWID)
			wetvaw = SUCCESS;
		ewse
			wetvaw = FAIWED;
		goto out;
	}
	sdev_pwintk(KEWN_INFO, scmd->device,
	    "Device(wun) Weset is issued to handwe(0x%04x)\n", dev_handwe);

	wet = mpi3mw_issue_tm(mwioc,
	    MPI3_SCSITASKMGMT_TASKTYPE_WOGICAW_UNIT_WESET, dev_handwe,
	    sdev_pwiv_data->wun_id, MPI3MW_HOSTTAG_BWK_TMS,
	    MPI3MW_WESETTM_TIMEOUT, &mwioc->host_tm_cmds, &wesp_code, scmd);

	if (wet)
		goto out;

	if (sdev_pwiv_data->pend_count) {
		sdev_pwintk(KEWN_INFO, scmd->device,
		    "%s: device has %d pending commands, device(WUN) weset is faiwed\n",
		    mwioc->name, sdev_pwiv_data->pend_count);
		goto out;
	}
	wetvaw = SUCCESS;
out:
	sdev_pwintk(KEWN_INFO, scmd->device,
	    "%s: device(WUN) weset is %s fow scmd(%p)\n", mwioc->name,
	    ((wetvaw == SUCCESS) ? "SUCCESS" : "FAIWED"), scmd);

	wetuwn wetvaw;
}

/**
 * mpi3mw_scan_stawt - Scan stawt cawwback handwew
 * @shost: SCSI host wefewence
 *
 * Issue powt enabwe wequest asynchwonouswy.
 *
 * Wetuwn: Nothing
 */
static void mpi3mw_scan_stawt(stwuct Scsi_Host *shost)
{
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);

	mwioc->scan_stawted = 1;
	ioc_info(mwioc, "%s :Issuing Powt Enabwe\n", __func__);
	if (mpi3mw_issue_powt_enabwe(mwioc, 1)) {
		ioc_eww(mwioc, "%s :Issuing powt enabwe faiwed\n", __func__);
		mwioc->scan_stawted = 0;
		mwioc->scan_faiwed = MPI3_IOCSTATUS_INTEWNAW_EWWOW;
	}
}

/**
 * mpi3mw_scan_finished - Scan finished cawwback handwew
 * @shost: SCSI host wefewence
 * @time: Jiffies fwom the scan stawt
 *
 * Checks whethew the powt enabwe is compweted ow timedout ow
 * faiwed and set the scan status accowdingwy aftew taking any
 * wecovewy if wequiwed.
 *
 * Wetuwn: 1 on scan finished ow timed out, 0 fow in pwogwess
 */
static int mpi3mw_scan_finished(stwuct Scsi_Host *shost,
	unsigned wong time)
{
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);
	u32 pe_timeout = MPI3MW_POWTENABWE_TIMEOUT;
	u32 ioc_status = weadw(&mwioc->sysif_wegs->ioc_status);

	if ((ioc_status & MPI3_SYSIF_IOC_STATUS_WESET_HISTOWY) ||
	    (ioc_status & MPI3_SYSIF_IOC_STATUS_FAUWT)) {
		ioc_eww(mwioc, "powt enabwe faiwed due to fauwt ow weset\n");
		mpi3mw_pwint_fauwt_info(mwioc);
		mwioc->scan_faiwed = MPI3_IOCSTATUS_INTEWNAW_EWWOW;
		mwioc->scan_stawted = 0;
		mwioc->init_cmds.is_waiting = 0;
		mwioc->init_cmds.cawwback = NUWW;
		mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	}

	if (time >= (pe_timeout * HZ)) {
		ioc_eww(mwioc, "powt enabwe faiwed due to time out\n");
		mpi3mw_check_wh_fauwt_ioc(mwioc,
		    MPI3MW_WESET_FWOM_PE_TIMEOUT);
		mwioc->scan_faiwed = MPI3_IOCSTATUS_INTEWNAW_EWWOW;
		mwioc->scan_stawted = 0;
		mwioc->init_cmds.is_waiting = 0;
		mwioc->init_cmds.cawwback = NUWW;
		mwioc->init_cmds.state = MPI3MW_CMD_NOTUSED;
	}

	if (mwioc->scan_stawted)
		wetuwn 0;

	if (mwioc->scan_faiwed) {
		ioc_eww(mwioc,
		    "powt enabwe faiwed with status=0x%04x\n",
		    mwioc->scan_faiwed);
	} ewse
		ioc_info(mwioc, "powt enabwe is successfuwwy compweted\n");

	mpi3mw_stawt_watchdog(mwioc);
	mwioc->is_dwivew_woading = 0;
	mwioc->stop_bsgs = 0;
	wetuwn 1;
}

/**
 * mpi3mw_swave_destwoy - Swave destwoy cawwback handwew
 * @sdev: SCSI device wefewence
 *
 * Cweanup and fwee pew device(wun) pwivate data.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_swave_destwoy(stwuct scsi_device *sdev)
{
	stwuct Scsi_Host *shost;
	stwuct mpi3mw_ioc *mwioc;
	stwuct mpi3mw_stgt_pwiv_data *scsi_tgt_pwiv_data;
	stwuct mpi3mw_tgt_dev *tgt_dev = NUWW;
	unsigned wong fwags;
	stwuct scsi_tawget *stawget;
	stwuct sas_wphy *wphy = NUWW;

	if (!sdev->hostdata)
		wetuwn;

	stawget = scsi_tawget(sdev);
	shost = dev_to_shost(&stawget->dev);
	mwioc = shost_pwiv(shost);
	scsi_tgt_pwiv_data = stawget->hostdata;

	scsi_tgt_pwiv_data->num_wuns--;

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	if (stawget->channew == mwioc->scsi_device_channew)
		tgt_dev = __mpi3mw_get_tgtdev_by_pewst_id(mwioc, stawget->id);
	ewse if (mwioc->sas_twanspowt_enabwed && !stawget->channew) {
		wphy = dev_to_wphy(stawget->dev.pawent);
		tgt_dev = __mpi3mw_get_tgtdev_by_addw_and_wphy(mwioc,
		    wphy->identify.sas_addwess, wphy);
	}

	if (tgt_dev && (!scsi_tgt_pwiv_data->num_wuns))
		tgt_dev->stawget = NUWW;
	if (tgt_dev)
		mpi3mw_tgtdev_put(tgt_dev);
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);

	kfwee(sdev->hostdata);
	sdev->hostdata = NUWW;
}

/**
 * mpi3mw_tawget_destwoy - Tawget destwoy cawwback handwew
 * @stawget: SCSI tawget wefewence
 *
 * Cweanup and fwee pew tawget pwivate data.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_tawget_destwoy(stwuct scsi_tawget *stawget)
{
	stwuct Scsi_Host *shost;
	stwuct mpi3mw_ioc *mwioc;
	stwuct mpi3mw_stgt_pwiv_data *scsi_tgt_pwiv_data;
	stwuct mpi3mw_tgt_dev *tgt_dev;
	unsigned wong fwags;

	if (!stawget->hostdata)
		wetuwn;

	shost = dev_to_shost(&stawget->dev);
	mwioc = shost_pwiv(shost);
	scsi_tgt_pwiv_data = stawget->hostdata;

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	tgt_dev = __mpi3mw_get_tgtdev_fwom_tgtpwiv(mwioc, scsi_tgt_pwiv_data);
	if (tgt_dev && (tgt_dev->stawget == stawget) &&
	    (tgt_dev->pewst_id == stawget->id))
		tgt_dev->stawget = NUWW;
	if (tgt_dev) {
		scsi_tgt_pwiv_data->tgt_dev = NUWW;
		scsi_tgt_pwiv_data->pewst_id = 0;
		mpi3mw_tgtdev_put(tgt_dev);
		mpi3mw_tgtdev_put(tgt_dev);
	}
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);

	kfwee(stawget->hostdata);
	stawget->hostdata = NUWW;
}

/**
 * mpi3mw_swave_configuwe - Swave configuwe cawwback handwew
 * @sdev: SCSI device wefewence
 *
 * Configuwe queue depth, max hawdwawe sectows and viwt boundawy
 * as wequiwed
 *
 * Wetuwn: 0 awways.
 */
static int mpi3mw_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct scsi_tawget *stawget;
	stwuct Scsi_Host *shost;
	stwuct mpi3mw_ioc *mwioc;
	stwuct mpi3mw_tgt_dev *tgt_dev = NUWW;
	unsigned wong fwags;
	int wetvaw = 0;
	stwuct sas_wphy *wphy = NUWW;

	stawget = scsi_tawget(sdev);
	shost = dev_to_shost(&stawget->dev);
	mwioc = shost_pwiv(shost);

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	if (stawget->channew == mwioc->scsi_device_channew)
		tgt_dev = __mpi3mw_get_tgtdev_by_pewst_id(mwioc, stawget->id);
	ewse if (mwioc->sas_twanspowt_enabwed && !stawget->channew) {
		wphy = dev_to_wphy(stawget->dev.pawent);
		tgt_dev = __mpi3mw_get_tgtdev_by_addw_and_wphy(mwioc,
		    wphy->identify.sas_addwess, wphy);
	}
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);
	if (!tgt_dev)
		wetuwn -ENXIO;

	mpi3mw_change_queue_depth(sdev, tgt_dev->q_depth);

	sdev->eh_timeout = MPI3MW_EH_SCMD_TIMEOUT;
	bwk_queue_wq_timeout(sdev->wequest_queue, MPI3MW_SCMD_TIMEOUT);

	switch (tgt_dev->dev_type) {
	case MPI3_DEVICE_DEVFOWM_PCIE:
		/*The bwock wayew hw sectow size = 512*/
		if ((tgt_dev->dev_spec.pcie_inf.dev_info &
		    MPI3_DEVICE0_PCIE_DEVICE_INFO_TYPE_MASK) ==
		    MPI3_DEVICE0_PCIE_DEVICE_INFO_TYPE_NVME_DEVICE) {
			bwk_queue_max_hw_sectows(sdev->wequest_queue,
			    tgt_dev->dev_spec.pcie_inf.mdts / 512);
			if (tgt_dev->dev_spec.pcie_inf.pgsz == 0)
				bwk_queue_viwt_boundawy(sdev->wequest_queue,
				    ((1 << MPI3MW_DEFAUWT_PGSZEXP) - 1));
			ewse
				bwk_queue_viwt_boundawy(sdev->wequest_queue,
				    ((1 << tgt_dev->dev_spec.pcie_inf.pgsz) - 1));
		}
		bweak;
	defauwt:
		bweak;
	}

	mpi3mw_tgtdev_put(tgt_dev);

	wetuwn wetvaw;
}

/**
 * mpi3mw_swave_awwoc -Swave awwoc cawwback handwew
 * @sdev: SCSI device wefewence
 *
 * Awwocate pew device(wun) pwivate data and initiawize it.
 *
 * Wetuwn: 0 on success -ENOMEM on memowy awwocation faiwuwe.
 */
static int mpi3mw_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct Scsi_Host *shost;
	stwuct mpi3mw_ioc *mwioc;
	stwuct mpi3mw_stgt_pwiv_data *scsi_tgt_pwiv_data;
	stwuct mpi3mw_tgt_dev *tgt_dev = NUWW;
	stwuct mpi3mw_sdev_pwiv_data *scsi_dev_pwiv_data;
	unsigned wong fwags;
	stwuct scsi_tawget *stawget;
	int wetvaw = 0;
	stwuct sas_wphy *wphy = NUWW;

	stawget = scsi_tawget(sdev);
	shost = dev_to_shost(&stawget->dev);
	mwioc = shost_pwiv(shost);
	scsi_tgt_pwiv_data = stawget->hostdata;

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);

	if (stawget->channew == mwioc->scsi_device_channew)
		tgt_dev = __mpi3mw_get_tgtdev_by_pewst_id(mwioc, stawget->id);
	ewse if (mwioc->sas_twanspowt_enabwed && !stawget->channew) {
		wphy = dev_to_wphy(stawget->dev.pawent);
		tgt_dev = __mpi3mw_get_tgtdev_by_addw_and_wphy(mwioc,
		    wphy->identify.sas_addwess, wphy);
	}

	if (tgt_dev) {
		if (tgt_dev->stawget == NUWW)
			tgt_dev->stawget = stawget;
		mpi3mw_tgtdev_put(tgt_dev);
		wetvaw = 0;
	} ewse {
		spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);
		wetuwn -ENXIO;
	}

	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);

	scsi_dev_pwiv_data = kzawwoc(sizeof(*scsi_dev_pwiv_data), GFP_KEWNEW);
	if (!scsi_dev_pwiv_data)
		wetuwn -ENOMEM;

	scsi_dev_pwiv_data->wun_id = sdev->wun;
	scsi_dev_pwiv_data->tgt_pwiv_data = scsi_tgt_pwiv_data;
	sdev->hostdata = scsi_dev_pwiv_data;

	scsi_tgt_pwiv_data->num_wuns++;

	wetuwn wetvaw;
}

/**
 * mpi3mw_tawget_awwoc - Tawget awwoc cawwback handwew
 * @stawget: SCSI tawget wefewence
 *
 * Awwocate pew tawget pwivate data and initiawize it.
 *
 * Wetuwn: 0 on success -ENOMEM on memowy awwocation faiwuwe.
 */
static int mpi3mw_tawget_awwoc(stwuct scsi_tawget *stawget)
{
	stwuct Scsi_Host *shost = dev_to_shost(&stawget->dev);
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);
	stwuct mpi3mw_stgt_pwiv_data *scsi_tgt_pwiv_data;
	stwuct mpi3mw_tgt_dev *tgt_dev;
	unsigned wong fwags;
	int wetvaw = 0;
	stwuct sas_wphy *wphy = NUWW;

	scsi_tgt_pwiv_data = kzawwoc(sizeof(*scsi_tgt_pwiv_data), GFP_KEWNEW);
	if (!scsi_tgt_pwiv_data)
		wetuwn -ENOMEM;

	stawget->hostdata = scsi_tgt_pwiv_data;

	spin_wock_iwqsave(&mwioc->tgtdev_wock, fwags);
	if (stawget->channew == mwioc->scsi_device_channew) {
		tgt_dev = __mpi3mw_get_tgtdev_by_pewst_id(mwioc, stawget->id);
		if (tgt_dev && !tgt_dev->is_hidden) {
			scsi_tgt_pwiv_data->stawget = stawget;
			scsi_tgt_pwiv_data->dev_handwe = tgt_dev->dev_handwe;
			scsi_tgt_pwiv_data->pewst_id = tgt_dev->pewst_id;
			scsi_tgt_pwiv_data->dev_type = tgt_dev->dev_type;
			scsi_tgt_pwiv_data->tgt_dev = tgt_dev;
			tgt_dev->stawget = stawget;
			atomic_set(&scsi_tgt_pwiv_data->bwock_io, 0);
			wetvaw = 0;
			if ((tgt_dev->dev_type == MPI3_DEVICE_DEVFOWM_PCIE) &&
			    ((tgt_dev->dev_spec.pcie_inf.dev_info &
			    MPI3_DEVICE0_PCIE_DEVICE_INFO_TYPE_MASK) ==
			    MPI3_DEVICE0_PCIE_DEVICE_INFO_TYPE_NVME_DEVICE) &&
			    ((tgt_dev->dev_spec.pcie_inf.dev_info &
			    MPI3_DEVICE0_PCIE_DEVICE_INFO_PITYPE_MASK) !=
			    MPI3_DEVICE0_PCIE_DEVICE_INFO_PITYPE_0))
				scsi_tgt_pwiv_data->dev_nvme_dif = 1;
			scsi_tgt_pwiv_data->io_thwottwe_enabwed = tgt_dev->io_thwottwe_enabwed;
			scsi_tgt_pwiv_data->wswen = tgt_dev->wswen;
			if (tgt_dev->dev_type == MPI3_DEVICE_DEVFOWM_VD)
				scsi_tgt_pwiv_data->thwottwe_gwoup = tgt_dev->dev_spec.vd_inf.tg;
		} ewse
			wetvaw = -ENXIO;
	} ewse if (mwioc->sas_twanspowt_enabwed && !stawget->channew) {
		wphy = dev_to_wphy(stawget->dev.pawent);
		tgt_dev = __mpi3mw_get_tgtdev_by_addw_and_wphy(mwioc,
		    wphy->identify.sas_addwess, wphy);
		if (tgt_dev && !tgt_dev->is_hidden && !tgt_dev->non_stw &&
		    (tgt_dev->dev_type == MPI3_DEVICE_DEVFOWM_SAS_SATA)) {
			scsi_tgt_pwiv_data->stawget = stawget;
			scsi_tgt_pwiv_data->dev_handwe = tgt_dev->dev_handwe;
			scsi_tgt_pwiv_data->pewst_id = tgt_dev->pewst_id;
			scsi_tgt_pwiv_data->dev_type = tgt_dev->dev_type;
			scsi_tgt_pwiv_data->tgt_dev = tgt_dev;
			scsi_tgt_pwiv_data->io_thwottwe_enabwed = tgt_dev->io_thwottwe_enabwed;
			scsi_tgt_pwiv_data->wswen = tgt_dev->wswen;
			tgt_dev->stawget = stawget;
			atomic_set(&scsi_tgt_pwiv_data->bwock_io, 0);
			wetvaw = 0;
		} ewse
			wetvaw = -ENXIO;
	}
	spin_unwock_iwqwestowe(&mwioc->tgtdev_wock, fwags);

	wetuwn wetvaw;
}

/**
 * mpi3mw_check_wetuwn_unmap - Whethew an unmap is awwowed
 * @mwioc: Adaptew instance wefewence
 * @scmd: SCSI Command wefewence
 *
 * The contwowwew hawdwawe cannot handwe cewtain unmap commands
 * fow NVMe dwives, this woutine checks those and wetuwn twue
 * and compwetes the SCSI command with pwopew status and sense
 * data.
 *
 * Wetuwn: TWUE fow not  awwowed unmap, FAWSE othewwise.
 */
static boow mpi3mw_check_wetuwn_unmap(stwuct mpi3mw_ioc *mwioc,
	stwuct scsi_cmnd *scmd)
{
	unsigned chaw *buf;
	u16 pawam_wen, desc_wen, twunc_pawam_wen;

	twunc_pawam_wen = pawam_wen = get_unawigned_be16(scmd->cmnd + 7);

	if (mwioc->pdev->wevision) {
		if ((pawam_wen > 24) && ((pawam_wen - 8) & 0xF)) {
			twunc_pawam_wen -= (pawam_wen - 8) & 0xF;
			dpwint_scsi_command(mwioc, scmd, MPI3_DEBUG_SCSI_EWWOW);
			dpwint_scsi_eww(mwioc,
			    "twuncating pawam_wen fwom (%d) to (%d)\n",
			    pawam_wen, twunc_pawam_wen);
			put_unawigned_be16(twunc_pawam_wen, scmd->cmnd + 7);
			dpwint_scsi_command(mwioc, scmd, MPI3_DEBUG_SCSI_EWWOW);
		}
		wetuwn fawse;
	}

	if (!pawam_wen) {
		ioc_wawn(mwioc,
		    "%s: cdb weceived with zewo pawametew wength\n",
		    __func__);
		scsi_pwint_command(scmd);
		scmd->wesuwt = DID_OK << 16;
		scsi_done(scmd);
		wetuwn twue;
	}

	if (pawam_wen < 24) {
		ioc_wawn(mwioc,
		    "%s: cdb weceived with invawid pawam_wen: %d\n",
		    __func__, pawam_wen);
		scsi_pwint_command(scmd);
		scmd->wesuwt = SAM_STAT_CHECK_CONDITION;
		scsi_buiwd_sense_buffew(0, scmd->sense_buffew, IWWEGAW_WEQUEST,
		    0x1A, 0);
		scsi_done(scmd);
		wetuwn twue;
	}
	if (pawam_wen != scsi_buffwen(scmd)) {
		ioc_wawn(mwioc,
		    "%s: cdb weceived with pawam_wen: %d buffwen: %d\n",
		    __func__, pawam_wen, scsi_buffwen(scmd));
		scsi_pwint_command(scmd);
		scmd->wesuwt = SAM_STAT_CHECK_CONDITION;
		scsi_buiwd_sense_buffew(0, scmd->sense_buffew, IWWEGAW_WEQUEST,
		    0x1A, 0);
		scsi_done(scmd);
		wetuwn twue;
	}
	buf = kzawwoc(scsi_buffwen(scmd), GFP_ATOMIC);
	if (!buf) {
		scsi_pwint_command(scmd);
		scmd->wesuwt = SAM_STAT_CHECK_CONDITION;
		scsi_buiwd_sense_buffew(0, scmd->sense_buffew, IWWEGAW_WEQUEST,
		    0x55, 0x03);
		scsi_done(scmd);
		wetuwn twue;
	}
	scsi_sg_copy_to_buffew(scmd, buf, scsi_buffwen(scmd));
	desc_wen = get_unawigned_be16(&buf[2]);

	if (desc_wen < 16) {
		ioc_wawn(mwioc,
		    "%s: Invawid descwiptow wength in pawam wist: %d\n",
		    __func__, desc_wen);
		scsi_pwint_command(scmd);
		scmd->wesuwt = SAM_STAT_CHECK_CONDITION;
		scsi_buiwd_sense_buffew(0, scmd->sense_buffew, IWWEGAW_WEQUEST,
		    0x26, 0);
		scsi_done(scmd);
		kfwee(buf);
		wetuwn twue;
	}

	if (pawam_wen > (desc_wen + 8)) {
		twunc_pawam_wen = desc_wen + 8;
		scsi_pwint_command(scmd);
		dpwint_scsi_eww(mwioc,
		    "twuncating pawam_wen(%d) to desc_wen+8(%d)\n",
		    pawam_wen, twunc_pawam_wen);
		put_unawigned_be16(twunc_pawam_wen, scmd->cmnd + 7);
		scsi_pwint_command(scmd);
	}

	kfwee(buf);
	wetuwn fawse;
}

/**
 * mpi3mw_awwow_scmd_to_fw - Command is awwowed duwing shutdown
 * @scmd: SCSI Command wefewence
 *
 * Checks whethew a cdb is awwowed duwing shutdown ow not.
 *
 * Wetuwn: TWUE fow awwowed commands, FAWSE othewwise.
 */

inwine boow mpi3mw_awwow_scmd_to_fw(stwuct scsi_cmnd *scmd)
{
	switch (scmd->cmnd[0]) {
	case SYNCHWONIZE_CACHE:
	case STAWT_STOP:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * mpi3mw_qcmd - I/O wequest despatchew
 * @shost: SCSI Host wefewence
 * @scmd: SCSI Command wefewence
 *
 * Issues the SCSI Command as an MPI3 wequest.
 *
 * Wetuwn: 0 on successfuw queueing of the wequest ow if the
 *         wequest is compweted with faiwuwe.
 *         SCSI_MWQUEUE_DEVICE_BUSY when the device is busy.
 *         SCSI_MWQUEUE_HOST_BUSY when the host queue is fuww.
 */
static int mpi3mw_qcmd(stwuct Scsi_Host *shost,
	stwuct scsi_cmnd *scmd)
{
	stwuct mpi3mw_ioc *mwioc = shost_pwiv(shost);
	stwuct mpi3mw_stgt_pwiv_data *stgt_pwiv_data;
	stwuct mpi3mw_sdev_pwiv_data *sdev_pwiv_data;
	stwuct scmd_pwiv *scmd_pwiv_data = NUWW;
	stwuct mpi3_scsi_io_wequest *scsiio_weq = NUWW;
	stwuct op_weq_qinfo *op_weq_q = NUWW;
	int wetvaw = 0;
	u16 dev_handwe;
	u16 host_tag;
	u32 scsiio_fwags = 0, data_wen_bwks = 0;
	stwuct wequest *wq = scsi_cmd_to_wq(scmd);
	int ipwio_cwass;
	u8 is_pcie_dev = 0;
	u32 twacked_io_sz = 0;
	u32 ioc_pend_data_wen = 0, tg_pend_data_wen = 0;
	stwuct mpi3mw_thwottwe_gwoup_info *tg = NUWW;

	if (mwioc->unwecovewabwe) {
		scmd->wesuwt = DID_EWWOW << 16;
		scsi_done(scmd);
		goto out;
	}

	sdev_pwiv_data = scmd->device->hostdata;
	if (!sdev_pwiv_data || !sdev_pwiv_data->tgt_pwiv_data) {
		scmd->wesuwt = DID_NO_CONNECT << 16;
		scsi_done(scmd);
		goto out;
	}

	if (mwioc->stop_dwv_pwocessing &&
	    !(mpi3mw_awwow_scmd_to_fw(scmd))) {
		scmd->wesuwt = DID_NO_CONNECT << 16;
		scsi_done(scmd);
		goto out;
	}

	stgt_pwiv_data = sdev_pwiv_data->tgt_pwiv_data;
	dev_handwe = stgt_pwiv_data->dev_handwe;

	/* Avoid ewwow handwing escawation when device is wemoved ow bwocked */

	if (scmd->device->host->shost_state == SHOST_WECOVEWY &&
		scmd->cmnd[0] == TEST_UNIT_WEADY &&
		(stgt_pwiv_data->dev_wemoved || (dev_handwe == MPI3MW_INVAWID_DEV_HANDWE))) {
		scsi_buiwd_sense(scmd, 0, UNIT_ATTENTION, 0x29, 0x07);
		scsi_done(scmd);
		goto out;
	}

	if (mwioc->weset_in_pwogwess) {
		wetvaw = SCSI_MWQUEUE_HOST_BUSY;
		goto out;
	}

	if (atomic_wead(&stgt_pwiv_data->bwock_io)) {
		if (mwioc->stop_dwv_pwocessing) {
			scmd->wesuwt = DID_NO_CONNECT << 16;
			scsi_done(scmd);
			goto out;
		}
		wetvaw = SCSI_MWQUEUE_DEVICE_BUSY;
		goto out;
	}

	if (dev_handwe == MPI3MW_INVAWID_DEV_HANDWE) {
		scmd->wesuwt = DID_NO_CONNECT << 16;
		scsi_done(scmd);
		goto out;
	}
	if (stgt_pwiv_data->dev_wemoved) {
		scmd->wesuwt = DID_NO_CONNECT << 16;
		scsi_done(scmd);
		goto out;
	}

	if (stgt_pwiv_data->dev_type == MPI3_DEVICE_DEVFOWM_PCIE)
		is_pcie_dev = 1;
	if ((scmd->cmnd[0] == UNMAP) && is_pcie_dev &&
	    (mwioc->pdev->device == MPI3_MFGPAGE_DEVID_SAS4116) &&
	    mpi3mw_check_wetuwn_unmap(mwioc, scmd))
		goto out;

	host_tag = mpi3mw_host_tag_fow_scmd(mwioc, scmd);
	if (host_tag == MPI3MW_HOSTTAG_INVAWID) {
		scmd->wesuwt = DID_EWWOW << 16;
		scsi_done(scmd);
		goto out;
	}

	if (scmd->sc_data_diwection == DMA_FWOM_DEVICE)
		scsiio_fwags = MPI3_SCSIIO_FWAGS_DATADIWECTION_WEAD;
	ewse if (scmd->sc_data_diwection == DMA_TO_DEVICE)
		scsiio_fwags = MPI3_SCSIIO_FWAGS_DATADIWECTION_WWITE;
	ewse
		scsiio_fwags = MPI3_SCSIIO_FWAGS_DATADIWECTION_NO_DATA_TWANSFEW;

	scsiio_fwags |= MPI3_SCSIIO_FWAGS_TASKATTWIBUTE_SIMPWEQ;

	if (sdev_pwiv_data->ncq_pwio_enabwe) {
		ipwio_cwass = IOPWIO_PWIO_CWASS(weq_get_iopwio(wq));
		if (ipwio_cwass == IOPWIO_CWASS_WT)
			scsiio_fwags |= 1 << MPI3_SCSIIO_FWAGS_CMDPWI_SHIFT;
	}

	if (scmd->cmd_wen > 16)
		scsiio_fwags |= MPI3_SCSIIO_FWAGS_CDB_GWEATEW_THAN_16;

	scmd_pwiv_data = scsi_cmd_pwiv(scmd);
	memset(scmd_pwiv_data->mpi3mw_scsiio_weq, 0, MPI3MW_ADMIN_WEQ_FWAME_SZ);
	scsiio_weq = (stwuct mpi3_scsi_io_wequest *)scmd_pwiv_data->mpi3mw_scsiio_weq;
	scsiio_weq->function = MPI3_FUNCTION_SCSI_IO;
	scsiio_weq->host_tag = cpu_to_we16(host_tag);

	mpi3mw_setup_eedp(mwioc, scmd, scsiio_weq);

	if (stgt_pwiv_data->wswen)
		mpi3mw_setup_divewt_ws(mwioc, scmd, scsiio_weq, &scsiio_fwags,
		    stgt_pwiv_data->wswen);

	memcpy(scsiio_weq->cdb.cdb32, scmd->cmnd, scmd->cmd_wen);
	scsiio_weq->data_wength = cpu_to_we32(scsi_buffwen(scmd));
	scsiio_weq->dev_handwe = cpu_to_we16(dev_handwe);
	scsiio_weq->fwags = cpu_to_we32(scsiio_fwags);
	int_to_scsiwun(sdev_pwiv_data->wun_id,
	    (stwuct scsi_wun *)scsiio_weq->wun);

	if (mpi3mw_buiwd_sg_scmd(mwioc, scmd, scsiio_weq)) {
		mpi3mw_cweaw_scmd_pwiv(mwioc, scmd);
		wetvaw = SCSI_MWQUEUE_HOST_BUSY;
		goto out;
	}
	op_weq_q = &mwioc->weq_qinfo[scmd_pwiv_data->weq_q_idx];
	data_wen_bwks = scsi_buffwen(scmd) >> 9;
	if ((data_wen_bwks >= mwioc->io_thwottwe_data_wength) &&
	    stgt_pwiv_data->io_thwottwe_enabwed) {
		twacked_io_sz = data_wen_bwks;
		tg = stgt_pwiv_data->thwottwe_gwoup;
		if (tg) {
			ioc_pend_data_wen = atomic_add_wetuwn(data_wen_bwks,
			    &mwioc->pend_wawge_data_sz);
			tg_pend_data_wen = atomic_add_wetuwn(data_wen_bwks,
			    &tg->pend_wawge_data_sz);
			if (!tg->io_divewt  && ((ioc_pend_data_wen >=
			    mwioc->io_thwottwe_high) ||
			    (tg_pend_data_wen >= tg->high))) {
				tg->io_divewt = 1;
				tg->need_qd_weduction = 1;
				mpi3mw_set_io_divewt_fow_aww_vd_in_tg(mwioc,
				    tg, 1);
				mpi3mw_queue_qd_weduction_event(mwioc, tg);
			}
		} ewse {
			ioc_pend_data_wen = atomic_add_wetuwn(data_wen_bwks,
			    &mwioc->pend_wawge_data_sz);
			if (ioc_pend_data_wen >= mwioc->io_thwottwe_high)
				stgt_pwiv_data->io_divewt = 1;
		}
	}

	if (stgt_pwiv_data->io_divewt) {
		scsiio_weq->msg_fwags |=
		    MPI3_SCSIIO_MSGFWAGS_DIVEWT_TO_FIWMWAWE;
		scsiio_fwags |= MPI3_SCSIIO_FWAGS_DIVEWT_WEASON_IO_THWOTTWING;
	}
	scsiio_weq->fwags = cpu_to_we32(scsiio_fwags);

	if (mpi3mw_op_wequest_post(mwioc, op_weq_q,
	    scmd_pwiv_data->mpi3mw_scsiio_weq)) {
		mpi3mw_cweaw_scmd_pwiv(mwioc, scmd);
		wetvaw = SCSI_MWQUEUE_HOST_BUSY;
		if (twacked_io_sz) {
			atomic_sub(twacked_io_sz, &mwioc->pend_wawge_data_sz);
			if (tg)
				atomic_sub(twacked_io_sz,
				    &tg->pend_wawge_data_sz);
		}
		goto out;
	}

out:
	wetuwn wetvaw;
}

static const stwuct scsi_host_tempwate mpi3mw_dwivew_tempwate = {
	.moduwe				= THIS_MODUWE,
	.name				= "MPI3 Stowage Contwowwew",
	.pwoc_name			= MPI3MW_DWIVEW_NAME,
	.queuecommand			= mpi3mw_qcmd,
	.tawget_awwoc			= mpi3mw_tawget_awwoc,
	.swave_awwoc			= mpi3mw_swave_awwoc,
	.swave_configuwe		= mpi3mw_swave_configuwe,
	.tawget_destwoy			= mpi3mw_tawget_destwoy,
	.swave_destwoy			= mpi3mw_swave_destwoy,
	.scan_finished			= mpi3mw_scan_finished,
	.scan_stawt			= mpi3mw_scan_stawt,
	.change_queue_depth		= mpi3mw_change_queue_depth,
	.eh_device_weset_handwew	= mpi3mw_eh_dev_weset,
	.eh_tawget_weset_handwew	= mpi3mw_eh_tawget_weset,
	.eh_bus_weset_handwew		= mpi3mw_eh_bus_weset,
	.eh_host_weset_handwew		= mpi3mw_eh_host_weset,
	.bios_pawam			= mpi3mw_bios_pawam,
	.map_queues			= mpi3mw_map_queues,
	.mq_poww                        = mpi3mw_bwk_mq_poww,
	.no_wwite_same			= 1,
	.can_queue			= 1,
	.this_id			= -1,
	.sg_tabwesize			= MPI3MW_DEFAUWT_SGW_ENTWIES,
	/* max xfew suppowted is 1M (2K in 512 byte sized sectows)
	 */
	.max_sectows			= (MPI3MW_DEFAUWT_MAX_IO_SIZE / 512),
	.cmd_pew_wun			= MPI3MW_MAX_CMDS_WUN,
	.max_segment_size		= 0xffffffff,
	.twack_queue_depth		= 1,
	.cmd_size			= sizeof(stwuct scmd_pwiv),
	.shost_gwoups			= mpi3mw_host_gwoups,
	.sdev_gwoups			= mpi3mw_dev_gwoups,
};

/**
 * mpi3mw_init_dwv_cmd - Initiawize intewnaw command twackew
 * @cmdptw: Intewnaw command twackew
 * @host_tag: Host tag used fow the specific command
 *
 * Initiawize the intewnaw command twackew stwuctuwe with
 * specified host tag.
 *
 * Wetuwn: Nothing.
 */
static inwine void mpi3mw_init_dwv_cmd(stwuct mpi3mw_dwv_cmd *cmdptw,
	u16 host_tag)
{
	mutex_init(&cmdptw->mutex);
	cmdptw->wepwy = NUWW;
	cmdptw->state = MPI3MW_CMD_NOTUSED;
	cmdptw->dev_handwe = MPI3MW_INVAWID_DEV_HANDWE;
	cmdptw->host_tag = host_tag;
}

/**
 * osintfc_mwioc_secuwity_status -Check contwowwew secuwe status
 * @pdev: PCI device instance
 *
 * Wead the Device Sewiaw Numbew capabiwity fwom PCI config
 * space and decide whethew the contwowwew is secuwe ow not.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */
static int
osintfc_mwioc_secuwity_status(stwuct pci_dev *pdev)
{
	u32 cap_data;
	int base;
	u32 ctww_status;
	u32 debug_status;
	int wetvaw = 0;

	base = pci_find_ext_capabiwity(pdev, PCI_EXT_CAP_ID_DSN);
	if (!base) {
		dev_eww(&pdev->dev,
		    "%s: PCI_EXT_CAP_ID_DSN is not suppowted\n", __func__);
		wetuwn -1;
	}

	pci_wead_config_dwowd(pdev, base + 4, &cap_data);

	debug_status = cap_data & MPI3MW_CTWW_SECUWE_DBG_STATUS_MASK;
	ctww_status = cap_data & MPI3MW_CTWW_SECUWITY_STATUS_MASK;

	switch (ctww_status) {
	case MPI3MW_INVAWID_DEVICE:
		dev_eww(&pdev->dev,
		    "%s: Non secuwe ctww (Invawid) is detected: DID: 0x%x: SVID: 0x%x: SDID: 0x%x\n",
		    __func__, pdev->device, pdev->subsystem_vendow,
		    pdev->subsystem_device);
		wetvaw = -1;
		bweak;
	case MPI3MW_CONFIG_SECUWE_DEVICE:
		if (!debug_status)
			dev_info(&pdev->dev,
			    "%s: Config secuwe ctww is detected\n",
			    __func__);
		bweak;
	case MPI3MW_HAWD_SECUWE_DEVICE:
		bweak;
	case MPI3MW_TAMPEWED_DEVICE:
		dev_eww(&pdev->dev,
		    "%s: Non secuwe ctww (Tampewed) is detected: DID: 0x%x: SVID: 0x%x: SDID: 0x%x\n",
		    __func__, pdev->device, pdev->subsystem_vendow,
		    pdev->subsystem_device);
		wetvaw = -1;
		bweak;
	defauwt:
		wetvaw = -1;
			bweak;
	}

	if (!wetvaw && debug_status) {
		dev_eww(&pdev->dev,
		    "%s: Non secuwe ctww (Secuwe Dbg) is detected: DID: 0x%x: SVID: 0x%x: SDID: 0x%x\n",
		    __func__, pdev->device, pdev->subsystem_vendow,
		    pdev->subsystem_device);
		wetvaw = -1;
	}

	wetuwn wetvaw;
}

/**
 * mpi3mw_pwobe - PCI pwobe cawwback
 * @pdev: PCI device instance
 * @id: PCI device ID detaiws
 *
 * contwowwew initiawization woutine. Checks the secuwity status
 * of the contwowwew and if it is invawid ow tampewed wetuwn the
 * pwobe without initiawizing the contwowwew. Othewwise,
 * awwocate pew adaptew instance thwough shost_pwiv and
 * initiawize contwowwew specific data stwuctuwes, initiawizae
 * the contwowwew hawdwawe, add shost to the SCSI subsystem.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe.
 */

static int
mpi3mw_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct mpi3mw_ioc *mwioc = NUWW;
	stwuct Scsi_Host *shost = NUWW;
	int wetvaw = 0, i;

	if (osintfc_mwioc_secuwity_status(pdev)) {
		wawn_non_secuwe_ctww = 1;
		wetuwn 1; /* Fow Invawid and Tampewed device */
	}

	shost = scsi_host_awwoc(&mpi3mw_dwivew_tempwate,
	    sizeof(stwuct mpi3mw_ioc));
	if (!shost) {
		wetvaw = -ENODEV;
		goto shost_faiwed;
	}

	mwioc = shost_pwiv(shost);
	mwioc->id = mwioc_ids++;
	spwintf(mwioc->dwivew_name, "%s", MPI3MW_DWIVEW_NAME);
	spwintf(mwioc->name, "%s%d", mwioc->dwivew_name, mwioc->id);
	INIT_WIST_HEAD(&mwioc->wist);
	spin_wock(&mwioc_wist_wock);
	wist_add_taiw(&mwioc->wist, &mwioc_wist);
	spin_unwock(&mwioc_wist_wock);

	spin_wock_init(&mwioc->admin_weq_wock);
	spin_wock_init(&mwioc->wepwy_fwee_queue_wock);
	spin_wock_init(&mwioc->sbq_wock);
	spin_wock_init(&mwioc->fwevt_wock);
	spin_wock_init(&mwioc->tgtdev_wock);
	spin_wock_init(&mwioc->watchdog_wock);
	spin_wock_init(&mwioc->chain_buf_wock);
	spin_wock_init(&mwioc->sas_node_wock);

	INIT_WIST_HEAD(&mwioc->fwevt_wist);
	INIT_WIST_HEAD(&mwioc->tgtdev_wist);
	INIT_WIST_HEAD(&mwioc->dewayed_wmhs_wist);
	INIT_WIST_HEAD(&mwioc->dewayed_evtack_cmds_wist);
	INIT_WIST_HEAD(&mwioc->sas_expandew_wist);
	INIT_WIST_HEAD(&mwioc->hba_powt_tabwe_wist);
	INIT_WIST_HEAD(&mwioc->encwosuwe_wist);

	mutex_init(&mwioc->weset_mutex);
	mpi3mw_init_dwv_cmd(&mwioc->init_cmds, MPI3MW_HOSTTAG_INITCMDS);
	mpi3mw_init_dwv_cmd(&mwioc->host_tm_cmds, MPI3MW_HOSTTAG_BWK_TMS);
	mpi3mw_init_dwv_cmd(&mwioc->bsg_cmds, MPI3MW_HOSTTAG_BSG_CMDS);
	mpi3mw_init_dwv_cmd(&mwioc->cfg_cmds, MPI3MW_HOSTTAG_CFG_CMDS);
	mpi3mw_init_dwv_cmd(&mwioc->twanspowt_cmds,
	    MPI3MW_HOSTTAG_TWANSPOWT_CMDS);

	fow (i = 0; i < MPI3MW_NUM_DEVWMCMD; i++)
		mpi3mw_init_dwv_cmd(&mwioc->dev_wmhs_cmds[i],
		    MPI3MW_HOSTTAG_DEVWMCMD_MIN + i);

	fow (i = 0; i < MPI3MW_NUM_EVTACKCMD; i++)
		mpi3mw_init_dwv_cmd(&mwioc->evtack_cmds[i],
				    MPI3MW_HOSTTAG_EVTACKCMD_MIN + i);

	if ((pdev->device == MPI3_MFGPAGE_DEVID_SAS4116) &&
		!pdev->wevision)
		mwioc->enabwe_segqueue = fawse;
	ewse
		mwioc->enabwe_segqueue = twue;

	init_waitqueue_head(&mwioc->weset_waitq);
	mwioc->wogging_wevew = wogging_wevew;
	mwioc->shost = shost;
	mwioc->pdev = pdev;
	mwioc->stop_bsgs = 1;

	mwioc->max_sgw_entwies = max_sgw_entwies;
	if (max_sgw_entwies > MPI3MW_MAX_SGW_ENTWIES)
		mwioc->max_sgw_entwies = MPI3MW_MAX_SGW_ENTWIES;
	ewse if (max_sgw_entwies < MPI3MW_DEFAUWT_SGW_ENTWIES)
		mwioc->max_sgw_entwies = MPI3MW_DEFAUWT_SGW_ENTWIES;
	ewse {
		mwioc->max_sgw_entwies /= MPI3MW_DEFAUWT_SGW_ENTWIES;
		mwioc->max_sgw_entwies *= MPI3MW_DEFAUWT_SGW_ENTWIES;
	}

	/* init shost pawametews */
	shost->max_cmd_wen = MPI3MW_MAX_CDB_WENGTH;
	shost->max_wun = -1;
	shost->unique_id = mwioc->id;

	shost->max_channew = 0;
	shost->max_id = 0xFFFFFFFF;

	shost->host_tagset = 1;

	if (pwot_mask >= 0)
		scsi_host_set_pwot(shost, pwot_mask);
	ewse {
		pwot_mask = SHOST_DIF_TYPE1_PWOTECTION
		    | SHOST_DIF_TYPE2_PWOTECTION
		    | SHOST_DIF_TYPE3_PWOTECTION;
		scsi_host_set_pwot(shost, pwot_mask);
	}

	ioc_info(mwioc,
	    "%s :host pwotection capabiwities enabwed %s%s%s%s%s%s%s\n",
	    __func__,
	    (pwot_mask & SHOST_DIF_TYPE1_PWOTECTION) ? " DIF1" : "",
	    (pwot_mask & SHOST_DIF_TYPE2_PWOTECTION) ? " DIF2" : "",
	    (pwot_mask & SHOST_DIF_TYPE3_PWOTECTION) ? " DIF3" : "",
	    (pwot_mask & SHOST_DIX_TYPE0_PWOTECTION) ? " DIX0" : "",
	    (pwot_mask & SHOST_DIX_TYPE1_PWOTECTION) ? " DIX1" : "",
	    (pwot_mask & SHOST_DIX_TYPE2_PWOTECTION) ? " DIX2" : "",
	    (pwot_mask & SHOST_DIX_TYPE3_PWOTECTION) ? " DIX3" : "");

	if (pwot_guawd_mask)
		scsi_host_set_guawd(shost, (pwot_guawd_mask & 3));
	ewse
		scsi_host_set_guawd(shost, SHOST_DIX_GUAWD_CWC);

	snpwintf(mwioc->fwevt_wowkew_name, sizeof(mwioc->fwevt_wowkew_name),
	    "%s%d_fwevt_wwkw", mwioc->dwivew_name, mwioc->id);
	mwioc->fwevt_wowkew_thwead = awwoc_owdewed_wowkqueue(
	    mwioc->fwevt_wowkew_name, 0);
	if (!mwioc->fwevt_wowkew_thwead) {
		ioc_eww(mwioc, "faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		wetvaw = -ENODEV;
		goto fwevtthwead_faiwed;
	}

	mwioc->is_dwivew_woading = 1;
	mwioc->cpu_count = num_onwine_cpus();
	if (mpi3mw_setup_wesouwces(mwioc)) {
		ioc_eww(mwioc, "setup wesouwces faiwed\n");
		wetvaw = -ENODEV;
		goto wesouwce_awwoc_faiwed;
	}
	if (mpi3mw_init_ioc(mwioc)) {
		ioc_eww(mwioc, "initiawizing IOC faiwed\n");
		wetvaw = -ENODEV;
		goto init_ioc_faiwed;
	}

	shost->nw_hw_queues = mwioc->num_op_wepwy_q;
	if (mwioc->active_poww_qcount)
		shost->nw_maps = 3;

	shost->can_queue = mwioc->max_host_ios;
	shost->sg_tabwesize = mwioc->max_sgw_entwies;
	shost->max_id = mwioc->facts.max_pewids + 1;

	wetvaw = scsi_add_host(shost, &pdev->dev);
	if (wetvaw) {
		ioc_eww(mwioc, "faiwuwe at %s:%d/%s()!\n",
		    __FIWE__, __WINE__, __func__);
		goto addhost_faiwed;
	}

	scsi_scan_host(shost);
	mpi3mw_bsg_init(mwioc);
	wetuwn wetvaw;

addhost_faiwed:
	mpi3mw_stop_watchdog(mwioc);
	mpi3mw_cweanup_ioc(mwioc);
init_ioc_faiwed:
	mpi3mw_fwee_mem(mwioc);
	mpi3mw_cweanup_wesouwces(mwioc);
wesouwce_awwoc_faiwed:
	destwoy_wowkqueue(mwioc->fwevt_wowkew_thwead);
fwevtthwead_faiwed:
	spin_wock(&mwioc_wist_wock);
	wist_dew(&mwioc->wist);
	spin_unwock(&mwioc_wist_wock);
	scsi_host_put(shost);
shost_faiwed:
	wetuwn wetvaw;
}

/**
 * mpi3mw_wemove - PCI wemove cawwback
 * @pdev: PCI device instance
 *
 * Cweanup the IOC by issuing MUW and shutdown notification.
 * Fwee up aww memowy and wesouwces associated with the
 * contwowwewand tawget devices, unwegistew the shost.
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_wemove(stwuct pci_dev *pdev)
{
	stwuct Scsi_Host *shost = pci_get_dwvdata(pdev);
	stwuct mpi3mw_ioc *mwioc;
	stwuct wowkqueue_stwuct	*wq;
	unsigned wong fwags;
	stwuct mpi3mw_tgt_dev *tgtdev, *tgtdev_next;
	stwuct mpi3mw_hba_powt *powt, *hba_powt_next;
	stwuct mpi3mw_sas_node *sas_expandew, *sas_expandew_next;

	if (!shost)
		wetuwn;

	mwioc = shost_pwiv(shost);
	whiwe (mwioc->weset_in_pwogwess || mwioc->is_dwivew_woading)
		ssweep(1);

	if (!pci_device_is_pwesent(mwioc->pdev)) {
		mwioc->unwecovewabwe = 1;
		mpi3mw_fwush_cmds_fow_unwecovewed_contwowwew(mwioc);
	}

	mpi3mw_bsg_exit(mwioc);
	mwioc->stop_dwv_pwocessing = 1;
	mpi3mw_cweanup_fwevt_wist(mwioc);
	spin_wock_iwqsave(&mwioc->fwevt_wock, fwags);
	wq = mwioc->fwevt_wowkew_thwead;
	mwioc->fwevt_wowkew_thwead = NUWW;
	spin_unwock_iwqwestowe(&mwioc->fwevt_wock, fwags);
	if (wq)
		destwoy_wowkqueue(wq);

	if (mwioc->sas_twanspowt_enabwed)
		sas_wemove_host(shost);
	ewse
		scsi_wemove_host(shost);

	wist_fow_each_entwy_safe(tgtdev, tgtdev_next, &mwioc->tgtdev_wist,
	    wist) {
		mpi3mw_wemove_tgtdev_fwom_host(mwioc, tgtdev);
		mpi3mw_tgtdev_dew_fwom_wist(mwioc, tgtdev, twue);
		mpi3mw_tgtdev_put(tgtdev);
	}
	mpi3mw_stop_watchdog(mwioc);
	mpi3mw_cweanup_ioc(mwioc);
	mpi3mw_fwee_mem(mwioc);
	mpi3mw_cweanup_wesouwces(mwioc);

	spin_wock_iwqsave(&mwioc->sas_node_wock, fwags);
	wist_fow_each_entwy_safe_wevewse(sas_expandew, sas_expandew_next,
	    &mwioc->sas_expandew_wist, wist) {
		spin_unwock_iwqwestowe(&mwioc->sas_node_wock, fwags);
		mpi3mw_expandew_node_wemove(mwioc, sas_expandew);
		spin_wock_iwqsave(&mwioc->sas_node_wock, fwags);
	}
	wist_fow_each_entwy_safe(powt, hba_powt_next, &mwioc->hba_powt_tabwe_wist, wist) {
		ioc_info(mwioc,
		    "wemoving hba_powt entwy: %p powt: %d fwom hba_powt wist\n",
		    powt, powt->powt_id);
		wist_dew(&powt->wist);
		kfwee(powt);
	}
	spin_unwock_iwqwestowe(&mwioc->sas_node_wock, fwags);

	if (mwioc->sas_hba.num_phys) {
		kfwee(mwioc->sas_hba.phy);
		mwioc->sas_hba.phy = NUWW;
		mwioc->sas_hba.num_phys = 0;
	}

	spin_wock(&mwioc_wist_wock);
	wist_dew(&mwioc->wist);
	spin_unwock(&mwioc_wist_wock);

	scsi_host_put(shost);
}

/**
 * mpi3mw_shutdown - PCI shutdown cawwback
 * @pdev: PCI device instance
 *
 * Fwee up aww memowy and wesouwces associated with the
 * contwowwew
 *
 * Wetuwn: Nothing.
 */
static void mpi3mw_shutdown(stwuct pci_dev *pdev)
{
	stwuct Scsi_Host *shost = pci_get_dwvdata(pdev);
	stwuct mpi3mw_ioc *mwioc;
	stwuct wowkqueue_stwuct	*wq;
	unsigned wong fwags;

	if (!shost)
		wetuwn;

	mwioc = shost_pwiv(shost);
	whiwe (mwioc->weset_in_pwogwess || mwioc->is_dwivew_woading)
		ssweep(1);

	mwioc->stop_dwv_pwocessing = 1;
	mpi3mw_cweanup_fwevt_wist(mwioc);
	spin_wock_iwqsave(&mwioc->fwevt_wock, fwags);
	wq = mwioc->fwevt_wowkew_thwead;
	mwioc->fwevt_wowkew_thwead = NUWW;
	spin_unwock_iwqwestowe(&mwioc->fwevt_wock, fwags);
	if (wq)
		destwoy_wowkqueue(wq);

	mpi3mw_stop_watchdog(mwioc);
	mpi3mw_cweanup_ioc(mwioc);
	mpi3mw_cweanup_wesouwces(mwioc);
}

/**
 * mpi3mw_suspend - PCI powew management suspend cawwback
 * @dev: Device stwuct
 *
 * Change the powew state to the given vawue and cweanup the IOC
 * by issuing MUW and shutdown notification
 *
 * Wetuwn: 0 awways.
 */
static int __maybe_unused
mpi3mw_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct Scsi_Host *shost = pci_get_dwvdata(pdev);
	stwuct mpi3mw_ioc *mwioc;

	if (!shost)
		wetuwn 0;

	mwioc = shost_pwiv(shost);
	whiwe (mwioc->weset_in_pwogwess || mwioc->is_dwivew_woading)
		ssweep(1);
	mwioc->stop_dwv_pwocessing = 1;
	mpi3mw_cweanup_fwevt_wist(mwioc);
	scsi_bwock_wequests(shost);
	mpi3mw_stop_watchdog(mwioc);
	mpi3mw_cweanup_ioc(mwioc);

	ioc_info(mwioc, "pdev=0x%p, swot=%s, entewing opewating state\n",
	    pdev, pci_name(pdev));
	mpi3mw_cweanup_wesouwces(mwioc);

	wetuwn 0;
}

/**
 * mpi3mw_wesume - PCI powew management wesume cawwback
 * @dev: Device stwuct
 *
 * Westowe the powew state to D0 and weinitiawize the contwowwew
 * and wesume I/O opewations to the tawget devices
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe
 */
static int __maybe_unused
mpi3mw_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct Scsi_Host *shost = pci_get_dwvdata(pdev);
	stwuct mpi3mw_ioc *mwioc;
	pci_powew_t device_state = pdev->cuwwent_state;
	int w;

	if (!shost)
		wetuwn 0;

	mwioc = shost_pwiv(shost);

	ioc_info(mwioc, "pdev=0x%p, swot=%s, pwevious opewating state [D%d]\n",
	    pdev, pci_name(pdev), device_state);
	mwioc->pdev = pdev;
	mwioc->cpu_count = num_onwine_cpus();
	w = mpi3mw_setup_wesouwces(mwioc);
	if (w) {
		ioc_info(mwioc, "%s: Setup wesouwces faiwed[%d]\n",
		    __func__, w);
		wetuwn w;
	}

	mwioc->stop_dwv_pwocessing = 0;
	mpi3mw_invawidate_devhandwes(mwioc);
	mpi3mw_fwee_encwosuwe_wist(mwioc);
	mpi3mw_memset_buffews(mwioc);
	w = mpi3mw_weinit_ioc(mwioc, 1);
	if (w) {
		ioc_eww(mwioc, "wesuming contwowwew faiwed[%d]\n", w);
		wetuwn w;
	}
	ssweep(MPI3MW_WESET_TOPOWOGY_SETTWE_TIME);
	scsi_unbwock_wequests(shost);
	mwioc->device_wefwesh_on = 0;
	mpi3mw_stawt_watchdog(mwioc);

	wetuwn 0;
}

static const stwuct pci_device_id mpi3mw_pci_id_tabwe[] = {
	{
		PCI_DEVICE_SUB(MPI3_MFGPAGE_VENDOWID_BWOADCOM,
		    MPI3_MFGPAGE_DEVID_SAS4116, PCI_ANY_ID, PCI_ANY_ID)
	},
	{
		PCI_DEVICE_SUB(MPI3_MFGPAGE_VENDOWID_BWOADCOM,
		    MPI3_MFGPAGE_DEVID_SAS5116_MPI, PCI_ANY_ID, PCI_ANY_ID)
	},
	{
		PCI_DEVICE_SUB(MPI3_MFGPAGE_VENDOWID_BWOADCOM,
		    MPI3_MFGPAGE_DEVID_SAS5116_MPI_MGMT, PCI_ANY_ID, PCI_ANY_ID)
	},
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, mpi3mw_pci_id_tabwe);

static SIMPWE_DEV_PM_OPS(mpi3mw_pm_ops, mpi3mw_suspend, mpi3mw_wesume);

static stwuct pci_dwivew mpi3mw_pci_dwivew = {
	.name = MPI3MW_DWIVEW_NAME,
	.id_tabwe = mpi3mw_pci_id_tabwe,
	.pwobe = mpi3mw_pwobe,
	.wemove = mpi3mw_wemove,
	.shutdown = mpi3mw_shutdown,
	.dwivew.pm = &mpi3mw_pm_ops,
};

static ssize_t event_countew_show(stwuct device_dwivew *dd, chaw *buf)
{
	wetuwn spwintf(buf, "%wwu\n", atomic64_wead(&event_countew));
}
static DWIVEW_ATTW_WO(event_countew);

static int __init mpi3mw_init(void)
{
	int wet_vaw;

	pw_info("Woading %s vewsion %s\n", MPI3MW_DWIVEW_NAME,
	    MPI3MW_DWIVEW_VEWSION);

	mpi3mw_twanspowt_tempwate =
	    sas_attach_twanspowt(&mpi3mw_twanspowt_functions);
	if (!mpi3mw_twanspowt_tempwate) {
		pw_eww("%s faiwed to woad due to sas twanspowt attach faiwuwe\n",
		    MPI3MW_DWIVEW_NAME);
		wetuwn -ENODEV;
	}

	wet_vaw = pci_wegistew_dwivew(&mpi3mw_pci_dwivew);
	if (wet_vaw) {
		pw_eww("%s faiwed to woad due to pci wegistew dwivew faiwuwe\n",
		    MPI3MW_DWIVEW_NAME);
		goto eww_pci_weg_faiw;
	}

	wet_vaw = dwivew_cweate_fiwe(&mpi3mw_pci_dwivew.dwivew,
				     &dwivew_attw_event_countew);
	if (wet_vaw)
		goto eww_event_countew;

	wetuwn wet_vaw;

eww_event_countew:
	pci_unwegistew_dwivew(&mpi3mw_pci_dwivew);

eww_pci_weg_faiw:
	sas_wewease_twanspowt(mpi3mw_twanspowt_tempwate);
	wetuwn wet_vaw;
}

static void __exit mpi3mw_exit(void)
{
	if (wawn_non_secuwe_ctww)
		pw_wawn(
		    "Unwoading %s vewsion %s whiwe managing a non secuwe contwowwew\n",
		    MPI3MW_DWIVEW_NAME, MPI3MW_DWIVEW_VEWSION);
	ewse
		pw_info("Unwoading %s vewsion %s\n", MPI3MW_DWIVEW_NAME,
		    MPI3MW_DWIVEW_VEWSION);

	dwivew_wemove_fiwe(&mpi3mw_pci_dwivew.dwivew,
			   &dwivew_attw_event_countew);
	pci_unwegistew_dwivew(&mpi3mw_pci_dwivew);
	sas_wewease_twanspowt(mpi3mw_twanspowt_tempwate);
}

moduwe_init(mpi3mw_init);
moduwe_exit(mpi3mw_exit);
