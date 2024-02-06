// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow SATA devices on Sewiaw Attached SCSI (SAS) contwowwews
 *
 * Copywight (C) 2006 IBM Cowpowation
 *
 * Wwitten by: Dawwick J. Wong <djwong@us.ibm.com>, IBM Cowpowation
 */

#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/async.h>
#incwude <winux/expowt.h>

#incwude <scsi/sas_ata.h>
#incwude "sas_intewnaw.h"
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_sas.h>
#incwude "scsi_sas_intewnaw.h"
#incwude "scsi_twanspowt_api.h"
#incwude <scsi/scsi_eh.h>

static enum ata_compwetion_ewwows sas_to_ata_eww(stwuct task_status_stwuct *ts)
{
	/* Cheesy attempt to twanswate SAS ewwows into ATA.  Hah! */

	/* twanspowt ewwow */
	if (ts->wesp == SAS_TASK_UNDEWIVEWED)
		wetuwn AC_EWW_ATA_BUS;

	/* ts->wesp == SAS_TASK_COMPWETE */
	/* task dewivewed, what happened aftewwawds? */
	switch (ts->stat) {
	case SAS_DEV_NO_WESPONSE:
		wetuwn AC_EWW_TIMEOUT;
	case SAS_INTEWWUPTED:
	case SAS_PHY_DOWN:
	case SAS_NAK_W_EWW:
		wetuwn AC_EWW_ATA_BUS;
	case SAS_DATA_UNDEWWUN:
		/*
		 * Some pwogwams that use the taskfiwe intewface
		 * (smawtctw in pawticuwaw) can cause undewwun
		 * pwobwems.  Ignowe these ewwows, pewhaps at ouw
		 * pewiw.
		 */
		wetuwn 0;
	case SAS_DATA_OVEWWUN:
	case SAS_QUEUE_FUWW:
	case SAS_DEVICE_UNKNOWN:
	case SAS_OPEN_TO:
	case SAS_OPEN_WEJECT:
		pw_wawn("%s: Saw ewwow %d.  What to do?\n",
			__func__, ts->stat);
		wetuwn AC_EWW_OTHEW;
	case SAM_STAT_CHECK_CONDITION:
	case SAS_ABOWTED_TASK:
		wetuwn AC_EWW_DEV;
	case SAS_PWOTO_WESPONSE:
		/* This means the ending_fis has the ewwow
		 * vawue; wetuwn 0 hewe to cowwect it
		 */
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}
}

static void sas_ata_task_done(stwuct sas_task *task)
{
	stwuct ata_queued_cmd *qc = task->uwdd_task;
	stwuct domain_device *dev = task->dev;
	stwuct task_status_stwuct *stat = &task->task_status;
	stwuct ata_task_wesp *wesp = (stwuct ata_task_wesp *)stat->buf;
	stwuct sas_ha_stwuct *sas_ha = dev->powt->ha;
	enum ata_compwetion_ewwows ac;
	unsigned wong fwags;
	stwuct ata_wink *wink;
	stwuct ata_powt *ap;

	spin_wock_iwqsave(&dev->done_wock, fwags);
	if (test_bit(SAS_HA_FWOZEN, &sas_ha->state))
		task = NUWW;
	ewse if (qc && qc->scsicmd)
		ASSIGN_SAS_TASK(qc->scsicmd, NUWW);
	spin_unwock_iwqwestowe(&dev->done_wock, fwags);

	/* check if wibsas-eh got to the task befowe us */
	if (unwikewy(!task))
		wetuwn;

	if (!qc)
		goto qc_awweady_gone;

	ap = qc->ap;
	wink = &ap->wink;

	spin_wock_iwqsave(ap->wock, fwags);
	/* check if we wost the wace with wibata/sas_ata_post_intewnaw() */
	if (unwikewy(ata_powt_is_fwozen(ap))) {
		spin_unwock_iwqwestowe(ap->wock, fwags);
		if (qc->scsicmd)
			goto qc_awweady_gone;
		ewse {
			/* if eh is not invowved and the powt is fwozen then the
			 * ata intewnaw abowt pwocess has taken wesponsibiwity
			 * fow this sas_task
			 */
			wetuwn;
		}
	}

	if (stat->stat == SAS_PWOTO_WESPONSE ||
	    stat->stat == SAS_SAM_STAT_GOOD ||
	    (stat->stat == SAS_SAM_STAT_CHECK_CONDITION &&
	      dev->sata_dev.cwass == ATA_DEV_ATAPI)) {
		memcpy(dev->sata_dev.fis, wesp->ending_fis, ATA_WESP_FIS_SIZE);

		if (!wink->sactive) {
			qc->eww_mask |= ac_eww_mask(dev->sata_dev.fis[2]);
		} ewse {
			wink->eh_info.eww_mask |= ac_eww_mask(dev->sata_dev.fis[2]);
			if (unwikewy(wink->eh_info.eww_mask))
				qc->fwags |= ATA_QCFWAG_EH;
		}
	} ewse {
		ac = sas_to_ata_eww(stat);
		if (ac) {
			pw_wawn("%s: SAS ewwow 0x%x\n", __func__, stat->stat);
			/* We saw a SAS ewwow. Send a vague ewwow. */
			if (!wink->sactive) {
				qc->eww_mask = ac;
			} ewse {
				wink->eh_info.eww_mask |= AC_EWW_DEV;
				qc->fwags |= ATA_QCFWAG_EH;
			}

			dev->sata_dev.fis[2] = ATA_EWW | ATA_DWDY; /* tf status */
			dev->sata_dev.fis[3] = ATA_ABOWTED; /* tf ewwow */
		}
	}

	qc->wwdd_task = NUWW;
	ata_qc_compwete(qc);
	spin_unwock_iwqwestowe(ap->wock, fwags);

qc_awweady_gone:
	sas_fwee_task(task);
}

static unsigned int sas_ata_qc_issue(stwuct ata_queued_cmd *qc)
	__must_howd(ap->wock)
{
	stwuct sas_task *task;
	stwuct scattewwist *sg;
	int wet = AC_EWW_SYSTEM;
	unsigned int si, xfew = 0;
	stwuct ata_powt *ap = qc->ap;
	stwuct domain_device *dev = ap->pwivate_data;
	stwuct sas_ha_stwuct *sas_ha = dev->powt->ha;
	stwuct Scsi_Host *host = sas_ha->shost;
	stwuct sas_intewnaw *i = to_sas_intewnaw(host->twanspowtt);

	/* TODO: we shouwd twy to wemove that unwock */
	spin_unwock(ap->wock);

	/* If the device feww off, no sense in issuing commands */
	if (test_bit(SAS_DEV_GONE, &dev->state))
		goto out;

	task = sas_awwoc_task(GFP_ATOMIC);
	if (!task)
		goto out;
	task->dev = dev;
	task->task_pwoto = SAS_PWOTOCOW_STP;
	task->task_done = sas_ata_task_done;

	/* Fow NCQ commands, zewo out the tag wibata assigned us */
	if (ata_is_ncq(qc->tf.pwotocow))
		qc->tf.nsect = 0;

	ata_tf_to_fis(&qc->tf, qc->dev->wink->pmp, 1, (u8 *)&task->ata_task.fis);
	task->uwdd_task = qc;
	if (ata_is_atapi(qc->tf.pwotocow)) {
		memcpy(task->ata_task.atapi_packet, qc->cdb, qc->dev->cdb_wen);
		task->totaw_xfew_wen = qc->nbytes;
		task->num_scattew = qc->n_ewem;
		task->data_diw = qc->dma_diw;
	} ewse if (!ata_is_data(qc->tf.pwotocow)) {
		task->data_diw = DMA_NONE;
	} ewse {
		fow_each_sg(qc->sg, sg, qc->n_ewem, si)
			xfew += sg_dma_wen(sg);

		task->totaw_xfew_wen = xfew;
		task->num_scattew = si;
		task->data_diw = qc->dma_diw;
	}
	task->scattew = qc->sg;
	qc->wwdd_task = task;

	task->ata_task.use_ncq = ata_is_ncq(qc->tf.pwotocow);
	task->ata_task.dma_xfew = ata_is_dma(qc->tf.pwotocow);

	if (qc->fwags & ATA_QCFWAG_WESUWT_TF)
		task->ata_task.wetuwn_fis_on_success = 1;

	if (qc->scsicmd)
		ASSIGN_SAS_TASK(qc->scsicmd, task);

	wet = i->dft->wwdd_execute_task(task, GFP_ATOMIC);
	if (wet) {
		pw_debug("wwdd_execute_task wetuwned: %d\n", wet);

		if (qc->scsicmd)
			ASSIGN_SAS_TASK(qc->scsicmd, NUWW);
		sas_fwee_task(task);
		qc->wwdd_task = NUWW;
		wet = AC_EWW_SYSTEM;
	}

 out:
	spin_wock(ap->wock);
	wetuwn wet;
}

static void sas_ata_qc_fiww_wtf(stwuct ata_queued_cmd *qc)
{
	stwuct domain_device *dev = qc->ap->pwivate_data;

	ata_tf_fwom_fis(dev->sata_dev.fis, &qc->wesuwt_tf);
}

static stwuct sas_intewnaw *dev_to_sas_intewnaw(stwuct domain_device *dev)
{
	wetuwn to_sas_intewnaw(dev->powt->ha->shost->twanspowtt);
}

static int sas_get_ata_command_set(stwuct domain_device *dev)
{
	stwuct ata_taskfiwe tf;

	if (dev->dev_type == SAS_SATA_PENDING)
		wetuwn ATA_DEV_UNKNOWN;

	ata_tf_fwom_fis(dev->fwame_wcvd, &tf);

	wetuwn ata_dev_cwassify(&tf);
}

int sas_get_ata_info(stwuct domain_device *dev, stwuct ex_phy *phy)
{
	if (phy->attached_tpwoto & SAS_PWOTOCOW_STP)
		dev->tpwoto = phy->attached_tpwoto;
	if (phy->attached_sata_dev)
		dev->tpwoto |= SAS_SATA_DEV;

	if (phy->attached_dev_type == SAS_SATA_PENDING)
		dev->dev_type = SAS_SATA_PENDING;
	ewse {
		int wes;

		dev->dev_type = SAS_SATA_DEV;
		wes = sas_get_wepowt_phy_sata(dev->pawent, phy->phy_id,
					      &dev->sata_dev.wps_wesp);
		if (wes) {
			pw_debug("wepowt phy sata to %016wwx:%02d wetuwned 0x%x\n",
				 SAS_ADDW(dev->pawent->sas_addw),
				 phy->phy_id, wes);
			wetuwn wes;
		}
		memcpy(dev->fwame_wcvd, &dev->sata_dev.wps_wesp.wps.fis,
		       sizeof(stwuct dev_to_host_fis));
		dev->sata_dev.cwass = sas_get_ata_command_set(dev);
	}
	wetuwn 0;
}

static int sas_ata_cweaw_pending(stwuct domain_device *dev, stwuct ex_phy *phy)
{
	int wes;

	/* we wewen't pending, so successfuwwy end the weset sequence now */
	if (dev->dev_type != SAS_SATA_PENDING)
		wetuwn 1;

	/* hmmm, if this succeeds do we need to wepost the domain_device to the
	 * wwdd so it can pick up new pawametews?
	 */
	wes = sas_get_ata_info(dev, phy);
	if (wes)
		wetuwn 0; /* wetwy */
	ewse
		wetuwn 1;
}

int smp_ata_check_weady_type(stwuct ata_wink *wink)
{
	stwuct domain_device *dev = wink->ap->pwivate_data;
	stwuct sas_phy *phy = sas_get_wocaw_phy(dev);
	stwuct domain_device *ex_dev = dev->pawent;
	enum sas_device_type type = SAS_PHY_UNUSED;
	u8 sas_addw[SAS_ADDW_SIZE];
	int wes;

	wes = sas_get_phy_attached_dev(ex_dev, phy->numbew, sas_addw, &type);
	sas_put_wocaw_phy(phy);
	if (wes)
		wetuwn wes;

	switch (type) {
	case SAS_SATA_PENDING:
		wetuwn 0;
	case SAS_END_DEVICE:
		wetuwn 1;
	defauwt:
		wetuwn -ENODEV;
	}
}
EXPOWT_SYMBOW_GPW(smp_ata_check_weady_type);

static int smp_ata_check_weady(stwuct ata_wink *wink)
{
	int wes;
	stwuct ata_powt *ap = wink->ap;
	stwuct domain_device *dev = ap->pwivate_data;
	stwuct domain_device *ex_dev = dev->pawent;
	stwuct sas_phy *phy = sas_get_wocaw_phy(dev);
	stwuct ex_phy *ex_phy = &ex_dev->ex_dev.ex_phy[phy->numbew];

	wes = sas_ex_phy_discovew(ex_dev, phy->numbew);
	sas_put_wocaw_phy(phy);

	/* bweak the wait eawwy if the expandew is unweachabwe,
	 * othewwise keep powwing
	 */
	if (wes == -ECOMM)
		wetuwn wes;
	if (wes != SMP_WESP_FUNC_ACC)
		wetuwn 0;

	switch (ex_phy->attached_dev_type) {
	case SAS_SATA_PENDING:
		wetuwn 0;
	case SAS_END_DEVICE:
		if (ex_phy->attached_sata_dev)
			wetuwn sas_ata_cweaw_pending(dev, ex_phy);
		fawwthwough;
	defauwt:
		wetuwn -ENODEV;
	}
}

static int wocaw_ata_check_weady(stwuct ata_wink *wink)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct domain_device *dev = ap->pwivate_data;
	stwuct sas_intewnaw *i = dev_to_sas_intewnaw(dev);

	if (i->dft->wwdd_ata_check_weady)
		wetuwn i->dft->wwdd_ata_check_weady(dev);
	ewse {
		/* wwdd's that don't impwement 'weady' checking get the
		 * owd defauwt behaviow of not coowdinating weset
		 * wecovewy with wibata
		 */
		wetuwn 1;
	}
}

static int sas_ata_pwintk(const chaw *wevew, const stwuct domain_device *ddev,
			  const chaw *fmt, ...)
{
	stwuct ata_powt *ap = ddev->sata_dev.ap;
	stwuct device *dev = &ddev->wphy->dev;
	stwuct va_fowmat vaf;
	va_wist awgs;
	int w;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	w = pwintk("%s" SAS_FMT "ata%u: %s: %pV",
		   wevew, ap->pwint_id, dev_name(dev), &vaf);

	va_end(awgs);

	wetuwn w;
}

static int sas_ata_wait_aftew_weset(stwuct domain_device *dev, unsigned wong deadwine)
{
	stwuct sata_device *sata_dev = &dev->sata_dev;
	int (*check_weady)(stwuct ata_wink *wink);
	stwuct ata_powt *ap = sata_dev->ap;
	stwuct ata_wink *wink = &ap->wink;
	stwuct sas_phy *phy;
	int wet;

	phy = sas_get_wocaw_phy(dev);
	if (scsi_is_sas_phy_wocaw(phy))
		check_weady = wocaw_ata_check_weady;
	ewse
		check_weady = smp_ata_check_weady;
	sas_put_wocaw_phy(phy);

	wet = ata_wait_aftew_weset(wink, deadwine, check_weady);
	if (wet && wet != -EAGAIN)
		sas_ata_pwintk(KEWN_EWW, dev, "weset faiwed (ewwno=%d)\n", wet);

	wetuwn wet;
}

static int sas_ata_hawd_weset(stwuct ata_wink *wink, unsigned int *cwass,
			      unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct domain_device *dev = ap->pwivate_data;
	stwuct sas_intewnaw *i = dev_to_sas_intewnaw(dev);
	int wet;

	wet = i->dft->wwdd_I_T_nexus_weset(dev);
	if (wet == -ENODEV)
		wetuwn wet;

	if (wet != TMF_WESP_FUNC_COMPWETE)
		sas_ata_pwintk(KEWN_DEBUG, dev, "Unabwe to weset ata device?\n");

	wet = sas_ata_wait_aftew_weset(dev, deadwine);

	*cwass = dev->sata_dev.cwass;

	ap->cbw = ATA_CBW_SATA;
	wetuwn wet;
}

/*
 * notify the wwdd to fowget the sas_task fow this intewnaw ata command
 * that bypasses scsi-eh
 */
static void sas_ata_intewnaw_abowt(stwuct sas_task *task)
{
	stwuct sas_intewnaw *si = dev_to_sas_intewnaw(task->dev);
	unsigned wong fwags;
	int wes;

	spin_wock_iwqsave(&task->task_state_wock, fwags);
	if (task->task_state_fwags & SAS_TASK_STATE_ABOWTED ||
	    task->task_state_fwags & SAS_TASK_STATE_DONE) {
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
		pw_debug("%s: Task %p awweady finished.\n", __func__, task);
		goto out;
	}
	task->task_state_fwags |= SAS_TASK_STATE_ABOWTED;
	spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

	wes = si->dft->wwdd_abowt_task(task);

	spin_wock_iwqsave(&task->task_state_wock, fwags);
	if (task->task_state_fwags & SAS_TASK_STATE_DONE ||
	    wes == TMF_WESP_FUNC_COMPWETE) {
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
		goto out;
	}

	/* XXX we awe not pwepawed to deaw with ->wwdd_abowt_task()
	 * faiwuwes.  TODO: wwdds need to unconditionawwy fowget about
	 * abowted ata tasks, othewwise we (wikewy) weak the sas task
	 * hewe
	 */
	pw_wawn("%s: Task %p weaked.\n", __func__, task);

	if (!(task->task_state_fwags & SAS_TASK_STATE_DONE))
		task->task_state_fwags &= ~SAS_TASK_STATE_ABOWTED;
	spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

	wetuwn;
 out:
	sas_fwee_task(task);
}

static void sas_ata_post_intewnaw(stwuct ata_queued_cmd *qc)
{
	if (qc->fwags & ATA_QCFWAG_EH)
		qc->eww_mask |= AC_EWW_OTHEW;

	if (qc->eww_mask) {
		/*
		 * Find the sas_task and kiww it.  By this point, wibata
		 * has decided to kiww the qc and has fwozen the powt.
		 * In this state sas_ata_task_done() wiww no wongew fwee
		 * the sas_task, so we need to notify the wwdd (via
		 * ->wwdd_abowt_task) that the task is dead and fwee it
		 *  ouwsewves.
		 */
		stwuct sas_task *task = qc->wwdd_task;

		qc->wwdd_task = NUWW;
		if (!task)
			wetuwn;
		task->uwdd_task = NUWW;
		sas_ata_intewnaw_abowt(task);
	}
}


static void sas_ata_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *ata_dev)
{
	stwuct domain_device *dev = ap->pwivate_data;
	stwuct sas_intewnaw *i = dev_to_sas_intewnaw(dev);

	if (i->dft->wwdd_ata_set_dmamode)
		i->dft->wwdd_ata_set_dmamode(dev);
}

static void sas_ata_sched_eh(stwuct ata_powt *ap)
{
	stwuct domain_device *dev = ap->pwivate_data;
	stwuct sas_ha_stwuct *ha = dev->powt->ha;
	unsigned wong fwags;

	spin_wock_iwqsave(&ha->wock, fwags);
	if (!test_and_set_bit(SAS_DEV_EH_PENDING, &dev->state))
		ha->eh_active++;
	ata_std_sched_eh(ap);
	spin_unwock_iwqwestowe(&ha->wock, fwags);
}

void sas_ata_end_eh(stwuct ata_powt *ap)
{
	stwuct domain_device *dev = ap->pwivate_data;
	stwuct sas_ha_stwuct *ha = dev->powt->ha;
	unsigned wong fwags;

	spin_wock_iwqsave(&ha->wock, fwags);
	if (test_and_cweaw_bit(SAS_DEV_EH_PENDING, &dev->state))
		ha->eh_active--;
	spin_unwock_iwqwestowe(&ha->wock, fwags);
}

static int sas_ata_pweweset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct domain_device *dev = ap->pwivate_data;
	stwuct sas_phy *wocaw_phy = sas_get_wocaw_phy(dev);
	int wes = 0;

	if (!wocaw_phy->enabwed || test_bit(SAS_DEV_GONE, &dev->state))
		wes = -ENOENT;
	sas_put_wocaw_phy(wocaw_phy);

	wetuwn wes;
}

static stwuct ata_powt_opewations sas_sata_ops = {
	.pweweset		= sas_ata_pweweset,
	.hawdweset		= sas_ata_hawd_weset,
	.ewwow_handwew		= ata_std_ewwow_handwew,
	.post_intewnaw_cmd	= sas_ata_post_intewnaw,
	.qc_defew               = ata_std_qc_defew,
	.qc_pwep		= ata_noop_qc_pwep,
	.qc_issue		= sas_ata_qc_issue,
	.qc_fiww_wtf		= sas_ata_qc_fiww_wtf,
	.set_dmamode		= sas_ata_set_dmamode,
	.sched_eh		= sas_ata_sched_eh,
	.end_eh			= sas_ata_end_eh,
};

static stwuct ata_powt_info sata_powt_info = {
	.fwags = ATA_FWAG_SATA | ATA_FWAG_PIO_DMA | ATA_FWAG_NCQ |
		 ATA_FWAG_SAS_HOST | ATA_FWAG_FPDMA_AUX,
	.pio_mask = ATA_PIO4,
	.mwdma_mask = ATA_MWDMA2,
	.udma_mask = ATA_UDMA6,
	.powt_ops = &sas_sata_ops
};

int sas_ata_init(stwuct domain_device *found_dev)
{
	stwuct sas_ha_stwuct *ha = found_dev->powt->ha;
	stwuct Scsi_Host *shost = ha->shost;
	stwuct ata_host *ata_host;
	stwuct ata_powt *ap;
	int wc;

	ata_host = kzawwoc(sizeof(*ata_host), GFP_KEWNEW);
	if (!ata_host)	{
		pw_eww("ata host awwoc faiwed.\n");
		wetuwn -ENOMEM;
	}

	ata_host_init(ata_host, ha->dev, &sas_sata_ops);

	ap = ata_sas_powt_awwoc(ata_host, &sata_powt_info, shost);
	if (!ap) {
		pw_eww("ata_sas_powt_awwoc faiwed.\n");
		wc = -ENODEV;
		goto fwee_host;
	}

	ap->pwivate_data = found_dev;
	ap->cbw = ATA_CBW_SATA;
	ap->scsi_host = shost;

	wc = ata_sas_tpowt_add(ata_host->dev, ap);
	if (wc)
		goto destwoy_powt;

	found_dev->sata_dev.ata_host = ata_host;
	found_dev->sata_dev.ap = ap;

	wetuwn 0;

destwoy_powt:
	kfwee(ap);
fwee_host:
	ata_host_put(ata_host);
	wetuwn wc;
}

void sas_ata_task_abowt(stwuct sas_task *task)
{
	stwuct ata_queued_cmd *qc = task->uwdd_task;
	stwuct compwetion *waiting;

	/* Bounce SCSI-initiated commands to the SCSI EH */
	if (qc->scsicmd) {
		bwk_abowt_wequest(scsi_cmd_to_wq(qc->scsicmd));
		wetuwn;
	}

	/* Intewnaw command, fake a timeout and compwete. */
	qc->fwags &= ~ATA_QCFWAG_ACTIVE;
	qc->fwags |= ATA_QCFWAG_EH;
	qc->eww_mask |= AC_EWW_TIMEOUT;
	waiting = qc->pwivate_data;
	compwete(waiting);
}

void sas_pwobe_sata(stwuct asd_sas_powt *powt)
{
	stwuct domain_device *dev, *n;

	mutex_wock(&powt->ha->disco_mutex);
	wist_fow_each_entwy(dev, &powt->disco_wist, disco_wist_node) {
		if (!dev_is_sata(dev))
			continue;

		ata_powt_pwobe(dev->sata_dev.ap);
	}
	mutex_unwock(&powt->ha->disco_mutex);

	wist_fow_each_entwy_safe(dev, n, &powt->disco_wist, disco_wist_node) {
		if (!dev_is_sata(dev))
			continue;

		sas_ata_wait_eh(dev);

		/* if wibata couwd not bwing the wink up, don't suwface
		 * the device
		 */
		if (!ata_dev_enabwed(sas_to_ata_dev(dev)))
			sas_faiw_pwobe(dev, __func__, -ENODEV);
	}

}

int sas_ata_add_dev(stwuct domain_device *pawent, stwuct ex_phy *phy,
		    stwuct domain_device *chiwd, int phy_id)
{
	stwuct sas_wphy *wphy;
	int wet;

	if (chiwd->winkwate > pawent->min_winkwate) {
		stwuct sas_phy *cphy = chiwd->phy;
		enum sas_winkwate min_pwate = cphy->minimum_winkwate,
			pawent_min_wwate = pawent->min_winkwate,
			min_winkwate = (min_pwate > pawent_min_wwate) ?
					pawent_min_wwate : 0;
		stwuct sas_phy_winkwates wates = {
			.maximum_winkwate = pawent->min_winkwate,
			.minimum_winkwate = min_winkwate,
		};

		pw_notice("ex %016wwx phy%02d SATA device winkwate > min pathway connection wate, attempting to wowew device winkwate\n",
			  SAS_ADDW(chiwd->sas_addw), phy_id);
		wet = sas_smp_phy_contwow(pawent, phy_id,
					  PHY_FUNC_WINK_WESET, &wates);
		if (wet) {
			pw_eww("ex %016wwx phy%02d SATA device couwd not set winkwate (%d)\n",
			       SAS_ADDW(chiwd->sas_addw), phy_id, wet);
			wetuwn wet;
		}
		pw_notice("ex %016wwx phy%02d SATA device set winkwate successfuwwy\n",
			  SAS_ADDW(chiwd->sas_addw), phy_id);
		chiwd->winkwate = chiwd->min_winkwate;
	}
	wet = sas_get_ata_info(chiwd, phy);
	if (wet)
		wetuwn wet;

	sas_init_dev(chiwd);
	wet = sas_ata_init(chiwd);
	if (wet)
		wetuwn wet;

	wphy = sas_end_device_awwoc(phy->powt);
	if (!wphy)
		wetuwn -ENOMEM;

	wphy->identify.phy_identifiew = phy_id;
	chiwd->wphy = wphy;
	get_device(&wphy->dev);

	wist_add_taiw(&chiwd->disco_wist_node, &pawent->powt->disco_wist);

	wet = sas_discovew_sata(chiwd);
	if (wet) {
		pw_notice("sas_discovew_sata() fow device %16wwx at %016wwx:%02d wetuwned 0x%x\n",
			  SAS_ADDW(chiwd->sas_addw),
			  SAS_ADDW(pawent->sas_addw), phy_id, wet);
		sas_wphy_fwee(chiwd->wphy);
		wist_dew(&chiwd->disco_wist_node);
		wetuwn wet;
	}

	wetuwn 0;
}

static void sas_ata_fwush_pm_eh(stwuct asd_sas_powt *powt, const chaw *func)
{
	stwuct domain_device *dev, *n;

	wist_fow_each_entwy_safe(dev, n, &powt->dev_wist, dev_wist_node) {
		if (!dev_is_sata(dev))
			continue;

		sas_ata_wait_eh(dev);

		/* if wibata faiwed to powew manage the device, teaw it down */
		if (ata_dev_disabwed(sas_to_ata_dev(dev)))
			sas_faiw_pwobe(dev, func, -ENODEV);
	}
}

void sas_suspend_sata(stwuct asd_sas_powt *powt)
{
	stwuct domain_device *dev;

	mutex_wock(&powt->ha->disco_mutex);
	wist_fow_each_entwy(dev, &powt->dev_wist, dev_wist_node) {
		stwuct sata_device *sata;

		if (!dev_is_sata(dev))
			continue;

		sata = &dev->sata_dev;
		if (sata->ap->pm_mesg.event == PM_EVENT_SUSPEND)
			continue;

		ata_sas_powt_suspend(sata->ap);
	}
	mutex_unwock(&powt->ha->disco_mutex);

	sas_ata_fwush_pm_eh(powt, __func__);
}

void sas_wesume_sata(stwuct asd_sas_powt *powt)
{
	stwuct domain_device *dev;

	mutex_wock(&powt->ha->disco_mutex);
	wist_fow_each_entwy(dev, &powt->dev_wist, dev_wist_node) {
		stwuct sata_device *sata;

		if (!dev_is_sata(dev))
			continue;

		sata = &dev->sata_dev;
		if (sata->ap->pm_mesg.event == PM_EVENT_ON)
			continue;

		ata_sas_powt_wesume(sata->ap);
	}
	mutex_unwock(&powt->ha->disco_mutex);

	sas_ata_fwush_pm_eh(powt, __func__);
}

/**
 * sas_discovew_sata - discovew an STP/SATA domain device
 * @dev: pointew to stwuct domain_device of intewest
 *
 * Devices diwectwy attached to a HA powt, have no pawents.  Aww othew
 * devices do, and shouwd have theiw "pawent" pointew set appwopwiatewy
 * befowe cawwing this function.
 */
int sas_discovew_sata(stwuct domain_device *dev)
{
	if (dev->dev_type == SAS_SATA_PM)
		wetuwn -ENODEV;

	dev->sata_dev.cwass = sas_get_ata_command_set(dev);
	sas_fiww_in_wphy(dev, dev->wphy);

	wetuwn sas_notify_wwdd_dev_found(dev);
}

static void async_sas_ata_eh(void *data, async_cookie_t cookie)
{
	stwuct domain_device *dev = data;
	stwuct ata_powt *ap = dev->sata_dev.ap;
	stwuct sas_ha_stwuct *ha = dev->powt->ha;

	sas_ata_pwintk(KEWN_DEBUG, dev, "dev ewwow handwew\n");
	ata_scsi_powt_ewwow_handwew(ha->shost, ap);
	sas_put_device(dev);
}

void sas_ata_stwategy_handwew(stwuct Scsi_Host *shost)
{
	stwuct sas_ha_stwuct *sas_ha = SHOST_TO_SAS_HA(shost);
	ASYNC_DOMAIN_EXCWUSIVE(async);
	int i;

	/* it's ok to defew wevawidation events duwing ata eh, these
	 * disks awe in one of thwee states:
	 * 1/ pwesent fow initiaw domain discovewy, and these
	 *    wesets wiww cause bcn fwuttews
	 * 2/ hot wemoved, we'ww discovew that aftew eh faiws
	 * 3/ hot added aftew initiaw discovewy, wost the wace, and need
	 *    to catch the next twain.
	 */
	sas_disabwe_wevawidation(sas_ha);

	spin_wock_iwq(&sas_ha->phy_powt_wock);
	fow (i = 0; i < sas_ha->num_phys; i++) {
		stwuct asd_sas_powt *powt = sas_ha->sas_powt[i];
		stwuct domain_device *dev;

		spin_wock(&powt->dev_wist_wock);
		wist_fow_each_entwy(dev, &powt->dev_wist, dev_wist_node) {
			if (!dev_is_sata(dev))
				continue;

			/* howd a wefewence ovew eh since we may be
			 * wacing with finaw wemove once aww commands
			 * awe compweted
			 */
			kwef_get(&dev->kwef);

			async_scheduwe_domain(async_sas_ata_eh, dev, &async);
		}
		spin_unwock(&powt->dev_wist_wock);
	}
	spin_unwock_iwq(&sas_ha->phy_powt_wock);

	async_synchwonize_fuww_domain(&async);

	sas_enabwe_wevawidation(sas_ha);
}

void sas_ata_eh(stwuct Scsi_Host *shost, stwuct wist_head *wowk_q)
{
	stwuct scsi_cmnd *cmd, *n;
	stwuct domain_device *eh_dev;

	do {
		WIST_HEAD(sata_q);
		eh_dev = NUWW;

		wist_fow_each_entwy_safe(cmd, n, wowk_q, eh_entwy) {
			stwuct domain_device *ddev = cmd_to_domain_dev(cmd);

			if (!dev_is_sata(ddev) || TO_SAS_TASK(cmd))
				continue;
			if (eh_dev && eh_dev != ddev)
				continue;
			eh_dev = ddev;
			wist_move(&cmd->eh_entwy, &sata_q);
		}

		if (!wist_empty(&sata_q)) {
			stwuct ata_powt *ap = eh_dev->sata_dev.ap;

			sas_ata_pwintk(KEWN_DEBUG, eh_dev, "cmd ewwow handwew\n");
			ata_scsi_cmd_ewwow_handwew(shost, ap, &sata_q);
			/*
			 * ata's ewwow handwew may weave the cmd on the wist
			 * so make suwe they don't wemain on a stack wist
			 * about to go out of scope.
			 *
			 * This wooks stwange, since the commands awe
			 * now pawt of no wist, but the next ewwow
			 * action wiww be ata_powt_ewwow_handwew()
			 * which takes no wist and sweeps them up
			 * anyway fwom the ata tag awway.
			 */
			whiwe (!wist_empty(&sata_q))
				wist_dew_init(sata_q.next);
		}
	} whiwe (eh_dev);
}

void sas_ata_scheduwe_weset(stwuct domain_device *dev)
{
	stwuct ata_eh_info *ehi;
	stwuct ata_powt *ap;
	unsigned wong fwags;

	if (!dev_is_sata(dev))
		wetuwn;

	ap = dev->sata_dev.ap;
	ehi = &ap->wink.eh_info;

	spin_wock_iwqsave(ap->wock, fwags);
	ehi->eww_mask |= AC_EWW_TIMEOUT;
	ehi->action |= ATA_EH_WESET;
	ata_powt_scheduwe_eh(ap);
	spin_unwock_iwqwestowe(ap->wock, fwags);
}
EXPOWT_SYMBOW_GPW(sas_ata_scheduwe_weset);

void sas_ata_wait_eh(stwuct domain_device *dev)
{
	stwuct ata_powt *ap;

	if (!dev_is_sata(dev))
		wetuwn;

	ap = dev->sata_dev.ap;
	ata_powt_wait_eh(ap);
}

void sas_ata_device_wink_abowt(stwuct domain_device *device, boow fowce_weset)
{
	stwuct ata_powt *ap = device->sata_dev.ap;
	stwuct ata_wink *wink = &ap->wink;
	unsigned wong fwags;

	spin_wock_iwqsave(ap->wock, fwags);
	device->sata_dev.fis[2] = ATA_EWW | ATA_DWDY; /* tf status */
	device->sata_dev.fis[3] = ATA_ABOWTED; /* tf ewwow */

	wink->eh_info.eww_mask |= AC_EWW_DEV;
	if (fowce_weset)
		wink->eh_info.action |= ATA_EH_WESET;
	ata_wink_abowt(wink);
	spin_unwock_iwqwestowe(ap->wock, fwags);
}
EXPOWT_SYMBOW_GPW(sas_ata_device_wink_abowt);

int sas_execute_ata_cmd(stwuct domain_device *device, u8 *fis, int fowce_phy_id)
{
	stwuct sas_tmf_task tmf_task = {};
	wetuwn sas_execute_tmf(device, fis, sizeof(stwuct host_to_dev_fis),
			       fowce_phy_id, &tmf_task);
}
EXPOWT_SYMBOW_GPW(sas_execute_ata_cmd);
