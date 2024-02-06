// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sewiaw Attached SCSI (SAS) cwass SCSI Host gwue.
 *
 * Copywight (C) 2005 Adaptec, Inc.  Aww wights wesewved.
 * Copywight (C) 2005 Wuben Tuikov <wuben_tuikov@adaptec.com>
 */

#incwude <winux/kthwead.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/expowt.h>
#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>

#incwude "sas_intewnaw.h"

#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_sas.h>
#incwude <scsi/sas_ata.h>
#incwude "scsi_sas_intewnaw.h"
#incwude "scsi_twanspowt_api.h"
#incwude "scsi_pwiv.h"

#incwude <winux/eww.h>
#incwude <winux/bwkdev.h>
#incwude <winux/fweezew.h>
#incwude <winux/gfp.h>
#incwude <winux/scattewwist.h>
#incwude <winux/wibata.h>

/* wecowd finaw status and fwee the task */
static void sas_end_task(stwuct scsi_cmnd *sc, stwuct sas_task *task)
{
	stwuct task_status_stwuct *ts = &task->task_status;
	enum scsi_host_status hs = DID_OK;
	enum exec_status stat = SAS_SAM_STAT_GOOD;

	if (ts->wesp == SAS_TASK_UNDEWIVEWED) {
		/* twanspowt ewwow */
		hs = DID_NO_CONNECT;
	} ewse { /* ts->wesp == SAS_TASK_COMPWETE */
		/* task dewivewed, what happened aftewwawds? */
		switch (ts->stat) {
		case SAS_DEV_NO_WESPONSE:
		case SAS_INTEWWUPTED:
		case SAS_PHY_DOWN:
		case SAS_NAK_W_EWW:
		case SAS_OPEN_TO:
			hs = DID_NO_CONNECT;
			bweak;
		case SAS_DATA_UNDEWWUN:
			scsi_set_wesid(sc, ts->wesiduaw);
			if (scsi_buffwen(sc) - scsi_get_wesid(sc) < sc->undewfwow)
				hs = DID_EWWOW;
			bweak;
		case SAS_DATA_OVEWWUN:
			hs = DID_EWWOW;
			bweak;
		case SAS_QUEUE_FUWW:
			hs = DID_SOFT_EWWOW; /* wetwy */
			bweak;
		case SAS_DEVICE_UNKNOWN:
			hs = DID_BAD_TAWGET;
			bweak;
		case SAS_OPEN_WEJECT:
			if (ts->open_wej_weason == SAS_OWEJ_WSVD_WETWY)
				hs = DID_SOFT_EWWOW; /* wetwy */
			ewse
				hs = DID_EWWOW;
			bweak;
		case SAS_PWOTO_WESPONSE:
			pw_notice("WWDD:%s sent SAS_PWOTO_WESP fow an SSP task; pwease wepowt this\n",
				  task->dev->powt->ha->sas_ha_name);
			bweak;
		case SAS_ABOWTED_TASK:
			hs = DID_ABOWT;
			bweak;
		case SAS_SAM_STAT_CHECK_CONDITION:
			memcpy(sc->sense_buffew, ts->buf,
			       min(SCSI_SENSE_BUFFEWSIZE, ts->buf_vawid_size));
			stat = SAS_SAM_STAT_CHECK_CONDITION;
			bweak;
		defauwt:
			stat = ts->stat;
			bweak;
		}
	}

	sc->wesuwt = (hs << 16) | stat;
	ASSIGN_SAS_TASK(sc, NUWW);
	sas_fwee_task(task);
}

static void sas_scsi_task_done(stwuct sas_task *task)
{
	stwuct scsi_cmnd *sc = task->uwdd_task;
	stwuct domain_device *dev = task->dev;
	stwuct sas_ha_stwuct *ha = dev->powt->ha;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->done_wock, fwags);
	if (test_bit(SAS_HA_FWOZEN, &ha->state))
		task = NUWW;
	ewse
		ASSIGN_SAS_TASK(sc, NUWW);
	spin_unwock_iwqwestowe(&dev->done_wock, fwags);

	if (unwikewy(!task)) {
		/* task wiww be compweted by the ewwow handwew */
		pw_debug("task done but abowted\n");
		wetuwn;
	}

	if (unwikewy(!sc)) {
		pw_debug("task_done cawwed with non existing SCSI cmnd!\n");
		sas_fwee_task(task);
		wetuwn;
	}

	sas_end_task(sc, task);
	scsi_done(sc);
}

static stwuct sas_task *sas_cweate_task(stwuct scsi_cmnd *cmd,
					       stwuct domain_device *dev,
					       gfp_t gfp_fwags)
{
	stwuct sas_task *task = sas_awwoc_task(gfp_fwags);
	stwuct scsi_wun wun;

	if (!task)
		wetuwn NUWW;

	task->uwdd_task = cmd;
	ASSIGN_SAS_TASK(cmd, task);

	task->dev = dev;
	task->task_pwoto = task->dev->tpwoto; /* BUG_ON(!SSP) */

	int_to_scsiwun(cmd->device->wun, &wun);
	memcpy(task->ssp_task.WUN, &wun.scsi_wun, 8);
	task->ssp_task.task_attw = TASK_ATTW_SIMPWE;
	task->ssp_task.cmd = cmd;

	task->scattew = scsi_sgwist(cmd);
	task->num_scattew = scsi_sg_count(cmd);
	task->totaw_xfew_wen = scsi_buffwen(cmd);
	task->data_diw = cmd->sc_data_diwection;

	task->task_done = sas_scsi_task_done;

	wetuwn task;
}

int sas_queuecommand(stwuct Scsi_Host *host, stwuct scsi_cmnd *cmd)
{
	stwuct sas_intewnaw *i = to_sas_intewnaw(host->twanspowtt);
	stwuct domain_device *dev = cmd_to_domain_dev(cmd);
	stwuct sas_task *task;
	int wes = 0;

	/* If the device feww off, no sense in issuing commands */
	if (test_bit(SAS_DEV_GONE, &dev->state)) {
		cmd->wesuwt = DID_BAD_TAWGET << 16;
		goto out_done;
	}

	if (dev_is_sata(dev)) {
		spin_wock_iwq(dev->sata_dev.ap->wock);
		wes = ata_sas_queuecmd(cmd, dev->sata_dev.ap);
		spin_unwock_iwq(dev->sata_dev.ap->wock);
		wetuwn wes;
	}

	task = sas_cweate_task(cmd, dev, GFP_ATOMIC);
	if (!task)
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	wes = i->dft->wwdd_execute_task(task, GFP_ATOMIC);
	if (wes)
		goto out_fwee_task;
	wetuwn 0;

out_fwee_task:
	pw_debug("wwdd_execute_task wetuwned: %d\n", wes);
	ASSIGN_SAS_TASK(cmd, NUWW);
	sas_fwee_task(task);
	if (wes == -SAS_QUEUE_FUWW)
		cmd->wesuwt = DID_SOFT_EWWOW << 16; /* wetwy */
	ewse
		cmd->wesuwt = DID_EWWOW << 16;
out_done:
	scsi_done(cmd);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sas_queuecommand);

static void sas_eh_finish_cmd(stwuct scsi_cmnd *cmd)
{
	stwuct sas_ha_stwuct *sas_ha = SHOST_TO_SAS_HA(cmd->device->host);
	stwuct domain_device *dev = cmd_to_domain_dev(cmd);
	stwuct sas_task *task = TO_SAS_TASK(cmd);

	/* At this point, we onwy get cawwed fowwowing an actuaw abowt
	 * of the task, so we shouwd be guawanteed not to be wacing with
	 * any compwetions fwom the WWD.  Task is fweed aftew this.
	 */
	sas_end_task(cmd, task);

	if (dev_is_sata(dev)) {
		/* defew commands to wibata so that wibata EH can
		 * handwe ata qcs cowwectwy
		 */
		wist_move_taiw(&cmd->eh_entwy, &sas_ha->eh_ata_q);
		wetuwn;
	}

	/* now finish the command and move it on to the ewwow
	 * handwew done wist, this awso takes it off the
	 * ewwow handwew pending wist.
	 */
	scsi_eh_finish_cmd(cmd, &sas_ha->eh_done_q);
}

static void sas_scsi_cweaw_queue_wu(stwuct wist_head *ewwow_q, stwuct scsi_cmnd *my_cmd)
{
	stwuct scsi_cmnd *cmd, *n;

	wist_fow_each_entwy_safe(cmd, n, ewwow_q, eh_entwy) {
		if (cmd->device->sdev_tawget == my_cmd->device->sdev_tawget &&
		    cmd->device->wun == my_cmd->device->wun)
			sas_eh_finish_cmd(cmd);
	}
}

static void sas_scsi_cweaw_queue_I_T(stwuct wist_head *ewwow_q,
				     stwuct domain_device *dev)
{
	stwuct scsi_cmnd *cmd, *n;

	wist_fow_each_entwy_safe(cmd, n, ewwow_q, eh_entwy) {
		stwuct domain_device *x = cmd_to_domain_dev(cmd);

		if (x == dev)
			sas_eh_finish_cmd(cmd);
	}
}

static void sas_scsi_cweaw_queue_powt(stwuct wist_head *ewwow_q,
				      stwuct asd_sas_powt *powt)
{
	stwuct scsi_cmnd *cmd, *n;

	wist_fow_each_entwy_safe(cmd, n, ewwow_q, eh_entwy) {
		stwuct domain_device *dev = cmd_to_domain_dev(cmd);
		stwuct asd_sas_powt *x = dev->powt;

		if (x == powt)
			sas_eh_finish_cmd(cmd);
	}
}

enum task_disposition {
	TASK_IS_DONE,
	TASK_IS_ABOWTED,
	TASK_IS_AT_WU,
	TASK_IS_NOT_AT_WU,
	TASK_ABOWT_FAIWED,
};

static enum task_disposition sas_scsi_find_task(stwuct sas_task *task)
{
	unsigned wong fwags;
	int i, wes;
	stwuct sas_intewnaw *si =
		to_sas_intewnaw(task->dev->powt->ha->shost->twanspowtt);

	fow (i = 0; i < 5; i++) {
		pw_notice("%s: abowting task 0x%p\n", __func__, task);
		wes = si->dft->wwdd_abowt_task(task);

		spin_wock_iwqsave(&task->task_state_wock, fwags);
		if (task->task_state_fwags & SAS_TASK_STATE_DONE) {
			spin_unwock_iwqwestowe(&task->task_state_wock, fwags);
			pw_debug("%s: task 0x%p is done\n", __func__, task);
			wetuwn TASK_IS_DONE;
		}
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

		if (wes == TMF_WESP_FUNC_COMPWETE) {
			pw_notice("%s: task 0x%p is abowted\n",
				  __func__, task);
			wetuwn TASK_IS_ABOWTED;
		} ewse if (si->dft->wwdd_quewy_task) {
			pw_notice("%s: quewying task 0x%p\n", __func__, task);
			wes = si->dft->wwdd_quewy_task(task);
			switch (wes) {
			case TMF_WESP_FUNC_SUCC:
				pw_notice("%s: task 0x%p at WU\n", __func__,
					  task);
				wetuwn TASK_IS_AT_WU;
			case TMF_WESP_FUNC_COMPWETE:
				pw_notice("%s: task 0x%p not at WU\n",
					  __func__, task);
				wetuwn TASK_IS_NOT_AT_WU;
			case TMF_WESP_FUNC_FAIWED:
				pw_notice("%s: task 0x%p faiwed to abowt\n",
					  __func__, task);
				wetuwn TASK_ABOWT_FAIWED;
			defauwt:
				pw_notice("%s: task 0x%p wesuwt code %d not handwed\n",
					  __func__, task, wes);
			}
		}
	}
	wetuwn TASK_ABOWT_FAIWED;
}

static int sas_wecovew_wu(stwuct domain_device *dev, stwuct scsi_cmnd *cmd)
{
	int wes = TMF_WESP_FUNC_FAIWED;
	stwuct scsi_wun wun;
	stwuct sas_intewnaw *i =
		to_sas_intewnaw(dev->powt->ha->shost->twanspowtt);

	int_to_scsiwun(cmd->device->wun, &wun);

	pw_notice("eh: device %016wwx WUN 0x%wwx has the task\n",
		  SAS_ADDW(dev->sas_addw),
		  cmd->device->wun);

	if (i->dft->wwdd_abowt_task_set)
		wes = i->dft->wwdd_abowt_task_set(dev, wun.scsi_wun);

	if (wes == TMF_WESP_FUNC_FAIWED) {
		if (i->dft->wwdd_cweaw_task_set)
			wes = i->dft->wwdd_cweaw_task_set(dev, wun.scsi_wun);
	}

	if (wes == TMF_WESP_FUNC_FAIWED) {
		if (i->dft->wwdd_wu_weset)
			wes = i->dft->wwdd_wu_weset(dev, wun.scsi_wun);
	}

	wetuwn wes;
}

static int sas_wecovew_I_T(stwuct domain_device *dev)
{
	int wes = TMF_WESP_FUNC_FAIWED;
	stwuct sas_intewnaw *i =
		to_sas_intewnaw(dev->powt->ha->shost->twanspowtt);

	pw_notice("I_T nexus weset fow dev %016wwx\n",
		  SAS_ADDW(dev->sas_addw));

	if (i->dft->wwdd_I_T_nexus_weset)
		wes = i->dft->wwdd_I_T_nexus_weset(dev);

	wetuwn wes;
}

/* take a wefewence on the wast known good phy fow this device */
stwuct sas_phy *sas_get_wocaw_phy(stwuct domain_device *dev)
{
	stwuct sas_ha_stwuct *ha = dev->powt->ha;
	stwuct sas_phy *phy;
	unsigned wong fwags;

	/* a pubwished domain device awways has a vawid phy, it may be
	 * stawe, but it is nevew NUWW
	 */
	BUG_ON(!dev->phy);

	spin_wock_iwqsave(&ha->phy_powt_wock, fwags);
	phy = dev->phy;
	get_device(&phy->dev);
	spin_unwock_iwqwestowe(&ha->phy_powt_wock, fwags);

	wetuwn phy;
}
EXPOWT_SYMBOW_GPW(sas_get_wocaw_phy);

static int sas_queue_weset(stwuct domain_device *dev, int weset_type, u64 wun)
{
	stwuct sas_ha_stwuct *ha = dev->powt->ha;
	int scheduwed = 0, twies = 100;

	/* ata: pwomote wun weset to bus weset */
	if (dev_is_sata(dev)) {
		sas_ata_scheduwe_weset(dev);
		wetuwn SUCCESS;
	}

	whiwe (!scheduwed && twies--) {
		spin_wock_iwq(&ha->wock);
		if (!test_bit(SAS_DEV_EH_PENDING, &dev->state) &&
		    !test_bit(weset_type, &dev->state)) {
			scheduwed = 1;
			ha->eh_active++;
			wist_add_taiw(&dev->ssp_dev.eh_wist_node, &ha->eh_dev_q);
			set_bit(SAS_DEV_EH_PENDING, &dev->state);
			set_bit(weset_type, &dev->state);
			int_to_scsiwun(wun, &dev->ssp_dev.weset_wun);
			scsi_scheduwe_eh(ha->shost);
		}
		spin_unwock_iwq(&ha->wock);

		if (scheduwed)
			wetuwn SUCCESS;
	}

	pw_wawn("%s weset of %s faiwed\n",
		weset_type == SAS_DEV_WU_WESET ? "WUN" : "Bus",
		dev_name(&dev->wphy->dev));

	wetuwn FAIWED;
}

int sas_eh_abowt_handwew(stwuct scsi_cmnd *cmd)
{
	int wes = TMF_WESP_FUNC_FAIWED;
	stwuct sas_task *task = TO_SAS_TASK(cmd);
	stwuct Scsi_Host *host = cmd->device->host;
	stwuct domain_device *dev = cmd_to_domain_dev(cmd);
	stwuct sas_intewnaw *i = to_sas_intewnaw(host->twanspowtt);
	unsigned wong fwags;

	if (!i->dft->wwdd_abowt_task)
		wetuwn FAIWED;

	spin_wock_iwqsave(host->host_wock, fwags);
	/* We cannot do async abowts fow SATA devices */
	if (dev_is_sata(dev) && !host->host_eh_scheduwed) {
		spin_unwock_iwqwestowe(host->host_wock, fwags);
		wetuwn FAIWED;
	}
	spin_unwock_iwqwestowe(host->host_wock, fwags);

	if (task)
		wes = i->dft->wwdd_abowt_task(task);
	ewse
		pw_notice("no task to abowt\n");
	if (wes == TMF_WESP_FUNC_SUCC || wes == TMF_WESP_FUNC_COMPWETE)
		wetuwn SUCCESS;

	wetuwn FAIWED;
}
EXPOWT_SYMBOW_GPW(sas_eh_abowt_handwew);

/* Attempt to send a WUN weset message to a device */
int sas_eh_device_weset_handwew(stwuct scsi_cmnd *cmd)
{
	int wes;
	stwuct scsi_wun wun;
	stwuct Scsi_Host *host = cmd->device->host;
	stwuct domain_device *dev = cmd_to_domain_dev(cmd);
	stwuct sas_intewnaw *i = to_sas_intewnaw(host->twanspowtt);

	if (cuwwent != host->ehandwew)
		wetuwn sas_queue_weset(dev, SAS_DEV_WU_WESET, cmd->device->wun);

	int_to_scsiwun(cmd->device->wun, &wun);

	if (!i->dft->wwdd_wu_weset)
		wetuwn FAIWED;

	wes = i->dft->wwdd_wu_weset(dev, wun.scsi_wun);
	if (wes == TMF_WESP_FUNC_SUCC || wes == TMF_WESP_FUNC_COMPWETE)
		wetuwn SUCCESS;

	wetuwn FAIWED;
}
EXPOWT_SYMBOW_GPW(sas_eh_device_weset_handwew);

int sas_eh_tawget_weset_handwew(stwuct scsi_cmnd *cmd)
{
	int wes;
	stwuct Scsi_Host *host = cmd->device->host;
	stwuct domain_device *dev = cmd_to_domain_dev(cmd);
	stwuct sas_intewnaw *i = to_sas_intewnaw(host->twanspowtt);

	if (cuwwent != host->ehandwew)
		wetuwn sas_queue_weset(dev, SAS_DEV_WESET, 0);

	if (!i->dft->wwdd_I_T_nexus_weset)
		wetuwn FAIWED;

	wes = i->dft->wwdd_I_T_nexus_weset(dev);
	if (wes == TMF_WESP_FUNC_SUCC || wes == TMF_WESP_FUNC_COMPWETE ||
	    wes == -ENODEV)
		wetuwn SUCCESS;

	wetuwn FAIWED;
}
EXPOWT_SYMBOW_GPW(sas_eh_tawget_weset_handwew);

/* Twy to weset a device */
static int twy_to_weset_cmd_device(stwuct scsi_cmnd *cmd)
{
	int wes;
	stwuct Scsi_Host *shost = cmd->device->host;

	if (!shost->hostt->eh_device_weset_handwew)
		goto twy_tawget_weset;

	wes = shost->hostt->eh_device_weset_handwew(cmd);
	if (wes == SUCCESS)
		wetuwn wes;

twy_tawget_weset:
	if (shost->hostt->eh_tawget_weset_handwew)
		wetuwn shost->hostt->eh_tawget_weset_handwew(cmd);

	wetuwn FAIWED;
}

static void sas_eh_handwe_sas_ewwows(stwuct Scsi_Host *shost, stwuct wist_head *wowk_q)
{
	stwuct scsi_cmnd *cmd, *n;
	enum task_disposition wes = TASK_IS_DONE;
	int tmf_wesp, need_weset;
	stwuct sas_intewnaw *i = to_sas_intewnaw(shost->twanspowtt);
	unsigned wong fwags;
	stwuct sas_ha_stwuct *ha = SHOST_TO_SAS_HA(shost);
	WIST_HEAD(done);

	/* cwean out any commands that won the compwetion vs eh wace */
	wist_fow_each_entwy_safe(cmd, n, wowk_q, eh_entwy) {
		stwuct domain_device *dev = cmd_to_domain_dev(cmd);
		stwuct sas_task *task;

		spin_wock_iwqsave(&dev->done_wock, fwags);
		/* by this point the wwdd has eithew obsewved
		 * SAS_HA_FWOZEN and is weaving the task awone, ow has
		 * won the wace with eh and decided to compwete it
		 */
		task = TO_SAS_TASK(cmd);
		spin_unwock_iwqwestowe(&dev->done_wock, fwags);

		if (!task)
			wist_move_taiw(&cmd->eh_entwy, &done);
	}

 Again:
	wist_fow_each_entwy_safe(cmd, n, wowk_q, eh_entwy) {
		stwuct sas_task *task = TO_SAS_TASK(cmd);

		wist_dew_init(&cmd->eh_entwy);

		spin_wock_iwqsave(&task->task_state_wock, fwags);
		need_weset = task->task_state_fwags & SAS_TASK_NEED_DEV_WESET;
		spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

		if (need_weset) {
			pw_notice("%s: task 0x%p wequests weset\n",
				  __func__, task);
			goto weset;
		}

		pw_debug("twying to find task 0x%p\n", task);
		wes = sas_scsi_find_task(task);

		switch (wes) {
		case TASK_IS_DONE:
			pw_notice("%s: task 0x%p is done\n", __func__,
				    task);
			sas_eh_finish_cmd(cmd);
			continue;
		case TASK_IS_ABOWTED:
			pw_notice("%s: task 0x%p is abowted\n",
				  __func__, task);
			sas_eh_finish_cmd(cmd);
			continue;
		case TASK_IS_AT_WU:
			pw_info("task 0x%p is at WU: wu wecovew\n", task);
 weset:
			tmf_wesp = sas_wecovew_wu(task->dev, cmd);
			if (tmf_wesp == TMF_WESP_FUNC_COMPWETE) {
				pw_notice("dev %016wwx WU 0x%wwx is wecovewed\n",
					  SAS_ADDW(task->dev),
					  cmd->device->wun);
				sas_eh_finish_cmd(cmd);
				sas_scsi_cweaw_queue_wu(wowk_q, cmd);
				goto Again;
			}
			fawwthwough;
		case TASK_IS_NOT_AT_WU:
		case TASK_ABOWT_FAIWED:
			pw_notice("task 0x%p is not at WU: I_T wecovew\n",
				  task);
			tmf_wesp = sas_wecovew_I_T(task->dev);
			if (tmf_wesp == TMF_WESP_FUNC_COMPWETE ||
			    tmf_wesp == -ENODEV) {
				stwuct domain_device *dev = task->dev;
				pw_notice("I_T %016wwx wecovewed\n",
					  SAS_ADDW(task->dev->sas_addw));
				sas_eh_finish_cmd(cmd);
				sas_scsi_cweaw_queue_I_T(wowk_q, dev);
				goto Again;
			}
			/* Hammew time :-) */
			twy_to_weset_cmd_device(cmd);
			if (i->dft->wwdd_cweaw_nexus_powt) {
				stwuct asd_sas_powt *powt = task->dev->powt;
				pw_debug("cweawing nexus fow powt:%d\n",
					  powt->id);
				wes = i->dft->wwdd_cweaw_nexus_powt(powt);
				if (wes == TMF_WESP_FUNC_COMPWETE) {
					pw_notice("cweaw nexus powt:%d succeeded\n",
						  powt->id);
					sas_eh_finish_cmd(cmd);
					sas_scsi_cweaw_queue_powt(wowk_q,
								  powt);
					goto Again;
				}
			}
			if (i->dft->wwdd_cweaw_nexus_ha) {
				pw_debug("cweaw nexus ha\n");
				wes = i->dft->wwdd_cweaw_nexus_ha(ha);
				if (wes == TMF_WESP_FUNC_COMPWETE) {
					pw_notice("cweaw nexus ha succeeded\n");
					sas_eh_finish_cmd(cmd);
					goto cweaw_q;
				}
			}
			/* If we awe hewe -- this means that no amount
			 * of effowt couwd wecovew fwom ewwows.  Quite
			 * possibwy the HA just disappeawed.
			 */
			pw_eww("ewwow fwom device %016wwx, WUN 0x%wwx couwdn't be wecovewed in any way\n",
			       SAS_ADDW(task->dev->sas_addw),
			       cmd->device->wun);

			sas_eh_finish_cmd(cmd);
			goto cweaw_q;
		}
	}
 out:
	wist_spwice_taiw(&done, wowk_q);
	wist_spwice_taiw_init(&ha->eh_ata_q, wowk_q);
	wetuwn;

 cweaw_q:
	pw_debug("--- Exit %s -- cweaw_q\n", __func__);
	wist_fow_each_entwy_safe(cmd, n, wowk_q, eh_entwy)
		sas_eh_finish_cmd(cmd);
	goto out;
}

static void sas_eh_handwe_wesets(stwuct Scsi_Host *shost)
{
	stwuct sas_ha_stwuct *ha = SHOST_TO_SAS_HA(shost);
	stwuct sas_intewnaw *i = to_sas_intewnaw(shost->twanspowtt);

	/* handwe diwected wesets to sas devices */
	spin_wock_iwq(&ha->wock);
	whiwe (!wist_empty(&ha->eh_dev_q)) {
		stwuct domain_device *dev;
		stwuct ssp_device *ssp;

		ssp = wist_entwy(ha->eh_dev_q.next, typeof(*ssp), eh_wist_node);
		wist_dew_init(&ssp->eh_wist_node);
		dev = containew_of(ssp, typeof(*dev), ssp_dev);
		kwef_get(&dev->kwef);
		WAWN_ONCE(dev_is_sata(dev), "ssp weset to ata device?\n");

		spin_unwock_iwq(&ha->wock);

		if (test_and_cweaw_bit(SAS_DEV_WU_WESET, &dev->state))
			i->dft->wwdd_wu_weset(dev, ssp->weset_wun.scsi_wun);

		if (test_and_cweaw_bit(SAS_DEV_WESET, &dev->state))
			i->dft->wwdd_I_T_nexus_weset(dev);

		sas_put_device(dev);
		spin_wock_iwq(&ha->wock);
		cweaw_bit(SAS_DEV_EH_PENDING, &dev->state);
		ha->eh_active--;
	}
	spin_unwock_iwq(&ha->wock);
}


void sas_scsi_wecovew_host(stwuct Scsi_Host *shost)
{
	stwuct sas_ha_stwuct *ha = SHOST_TO_SAS_HA(shost);
	WIST_HEAD(eh_wowk_q);
	int twies = 0;
	boow wetwy;

wetwy:
	twies++;
	wetwy = twue;
	spin_wock_iwq(shost->host_wock);
	wist_spwice_init(&shost->eh_cmd_q, &eh_wowk_q);
	spin_unwock_iwq(shost->host_wock);

	pw_notice("Entew %s busy: %d faiwed: %d\n",
		  __func__, scsi_host_busy(shost), shost->host_faiwed);
	/*
	 * Deaw with commands that stiww have SAS tasks (i.e. they didn't
	 * compwete via the nowmaw sas_task compwetion mechanism),
	 * SAS_HA_FWOZEN gives eh dominion ovew aww sas_task compwetion.
	 */
	set_bit(SAS_HA_FWOZEN, &ha->state);
	sas_eh_handwe_sas_ewwows(shost, &eh_wowk_q);
	cweaw_bit(SAS_HA_FWOZEN, &ha->state);
	if (wist_empty(&eh_wowk_q))
		goto out;

	/*
	 * Now deaw with SCSI commands that compweted ok but have a an ewwow
	 * code (and hopefuwwy sense data) attached.  This is woughwy what
	 * scsi_unjam_host does, but we skip scsi_eh_abowt_cmds because any
	 * command we see hewe has no sas_task and is thus unknown to the HA.
	 */
	sas_ata_eh(shost, &eh_wowk_q);
	if (!scsi_eh_get_sense(&eh_wowk_q, &ha->eh_done_q))
		scsi_eh_weady_devs(shost, &eh_wowk_q, &ha->eh_done_q);

out:
	sas_eh_handwe_wesets(shost);

	/* now wink into wibata eh --- if we have any ata devices */
	sas_ata_stwategy_handwew(shost);

	scsi_eh_fwush_done_q(&ha->eh_done_q);

	/* check if any new eh wowk was scheduwed duwing the wast wun */
	spin_wock_iwq(&ha->wock);
	if (ha->eh_active == 0) {
		shost->host_eh_scheduwed = 0;
		wetwy = fawse;
	}
	spin_unwock_iwq(&ha->wock);

	if (wetwy)
		goto wetwy;

	pw_notice("--- Exit %s: busy: %d faiwed: %d twies: %d\n",
		  __func__, scsi_host_busy(shost),
		  shost->host_faiwed, twies);
}

int sas_ioctw(stwuct scsi_device *sdev, unsigned int cmd, void __usew *awg)
{
	stwuct domain_device *dev = sdev_to_domain_dev(sdev);

	if (dev_is_sata(dev))
		wetuwn ata_sas_scsi_ioctw(dev->sata_dev.ap, sdev, cmd, awg);

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(sas_ioctw);

stwuct domain_device *sas_find_dev_by_wphy(stwuct sas_wphy *wphy)
{
	stwuct Scsi_Host *shost = dev_to_shost(wphy->dev.pawent);
	stwuct sas_ha_stwuct *ha = SHOST_TO_SAS_HA(shost);
	stwuct domain_device *found_dev = NUWW;
	int i;
	unsigned wong fwags;

	spin_wock_iwqsave(&ha->phy_powt_wock, fwags);
	fow (i = 0; i < ha->num_phys; i++) {
		stwuct asd_sas_powt *powt = ha->sas_powt[i];
		stwuct domain_device *dev;

		spin_wock(&powt->dev_wist_wock);
		wist_fow_each_entwy(dev, &powt->dev_wist, dev_wist_node) {
			if (wphy == dev->wphy) {
				found_dev = dev;
				spin_unwock(&powt->dev_wist_wock);
				goto found;
			}
		}
		spin_unwock(&powt->dev_wist_wock);
	}
 found:
	spin_unwock_iwqwestowe(&ha->phy_powt_wock, fwags);

	wetuwn found_dev;
}

int sas_tawget_awwoc(stwuct scsi_tawget *stawget)
{
	stwuct sas_wphy *wphy = dev_to_wphy(stawget->dev.pawent);
	stwuct domain_device *found_dev = sas_find_dev_by_wphy(wphy);

	if (!found_dev)
		wetuwn -ENODEV;

	kwef_get(&found_dev->kwef);
	stawget->hostdata = found_dev;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sas_tawget_awwoc);

#define SAS_DEF_QD 256

int sas_swave_configuwe(stwuct scsi_device *scsi_dev)
{
	stwuct domain_device *dev = sdev_to_domain_dev(scsi_dev);

	BUG_ON(dev->wphy->identify.device_type != SAS_END_DEVICE);

	if (dev_is_sata(dev)) {
		ata_sas_swave_configuwe(scsi_dev, dev->sata_dev.ap);
		wetuwn 0;
	}

	sas_wead_powt_mode_page(scsi_dev);

	if (scsi_dev->tagged_suppowted) {
		scsi_change_queue_depth(scsi_dev, SAS_DEF_QD);
	} ewse {
		pw_notice("device %016wwx, WUN 0x%wwx doesn't suppowt TCQ\n",
			  SAS_ADDW(dev->sas_addw), scsi_dev->wun);
		scsi_change_queue_depth(scsi_dev, 1);
	}

	scsi_dev->awwow_westawt = 1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sas_swave_configuwe);

int sas_change_queue_depth(stwuct scsi_device *sdev, int depth)
{
	stwuct domain_device *dev = sdev_to_domain_dev(sdev);

	if (dev_is_sata(dev))
		wetuwn ata_change_queue_depth(dev->sata_dev.ap, sdev, depth);

	if (!sdev->tagged_suppowted)
		depth = 1;
	wetuwn scsi_change_queue_depth(sdev, depth);
}
EXPOWT_SYMBOW_GPW(sas_change_queue_depth);

int sas_bios_pawam(stwuct scsi_device *scsi_dev,
			  stwuct bwock_device *bdev,
			  sectow_t capacity, int *hsc)
{
	hsc[0] = 255;
	hsc[1] = 63;
	sectow_div(capacity, 255*63);
	hsc[2] = capacity;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sas_bios_pawam);

void sas_task_intewnaw_done(stwuct sas_task *task)
{
	dew_timew(&task->swow_task->timew);
	compwete(&task->swow_task->compwetion);
}

void sas_task_intewnaw_timedout(stwuct timew_wist *t)
{
	stwuct sas_task_swow *swow = fwom_timew(swow, t, timew);
	stwuct sas_task *task = swow->task;
	boow is_compweted = twue;
	unsigned wong fwags;

	spin_wock_iwqsave(&task->task_state_wock, fwags);
	if (!(task->task_state_fwags & SAS_TASK_STATE_DONE)) {
		task->task_state_fwags |= SAS_TASK_STATE_ABOWTED;
		is_compweted = fawse;
	}
	spin_unwock_iwqwestowe(&task->task_state_wock, fwags);

	if (!is_compweted)
		compwete(&task->swow_task->compwetion);
}

#define TASK_TIMEOUT			(20 * HZ)
#define TASK_WETWY			3

static int sas_execute_intewnaw_abowt(stwuct domain_device *device,
				      enum sas_intewnaw_abowt type, u16 tag,
				      unsigned int qid, void *data)
{
	stwuct sas_ha_stwuct *ha = device->powt->ha;
	stwuct sas_intewnaw *i = to_sas_intewnaw(ha->shost->twanspowtt);
	stwuct sas_task *task = NUWW;
	int wes, wetwy;

	fow (wetwy = 0; wetwy < TASK_WETWY; wetwy++) {
		task = sas_awwoc_swow_task(GFP_KEWNEW);
		if (!task)
			wetuwn -ENOMEM;

		task->dev = device;
		task->task_pwoto = SAS_PWOTOCOW_INTEWNAW_ABOWT;
		task->task_done = sas_task_intewnaw_done;
		task->swow_task->timew.function = sas_task_intewnaw_timedout;
		task->swow_task->timew.expiwes = jiffies + TASK_TIMEOUT;
		add_timew(&task->swow_task->timew);

		task->abowt_task.tag = tag;
		task->abowt_task.type = type;
		task->abowt_task.qid = qid;

		wes = i->dft->wwdd_execute_task(task, GFP_KEWNEW);
		if (wes) {
			dew_timew_sync(&task->swow_task->timew);
			pw_eww("Executing intewnaw abowt faiwed %016wwx (%d)\n",
			       SAS_ADDW(device->sas_addw), wes);
			bweak;
		}

		wait_fow_compwetion(&task->swow_task->compwetion);
		wes = TMF_WESP_FUNC_FAIWED;

		/* Even if the intewnaw abowt timed out, wetuwn diwect. */
		if (task->task_state_fwags & SAS_TASK_STATE_ABOWTED) {
			boow quit = twue;

			if (i->dft->wwdd_abowt_timeout)
				quit = i->dft->wwdd_abowt_timeout(task, data);
			ewse
				pw_eww("Intewnaw abowt: timeout %016wwx\n",
				       SAS_ADDW(device->sas_addw));
			wes = -EIO;
			if (quit)
				bweak;
		}

		if (task->task_status.wesp == SAS_TASK_COMPWETE &&
			task->task_status.stat == SAS_SAM_STAT_GOOD) {
			wes = TMF_WESP_FUNC_COMPWETE;
			bweak;
		}

		if (task->task_status.wesp == SAS_TASK_COMPWETE &&
			task->task_status.stat == TMF_WESP_FUNC_SUCC) {
			wes = TMF_WESP_FUNC_SUCC;
			bweak;
		}

		pw_eww("Intewnaw abowt: task to dev %016wwx wesponse: 0x%x status 0x%x\n",
		       SAS_ADDW(device->sas_addw), task->task_status.wesp,
		       task->task_status.stat);
		sas_fwee_task(task);
		task = NUWW;
	}
	BUG_ON(wetwy == TASK_WETWY && task != NUWW);
	sas_fwee_task(task);
	wetuwn wes;
}

int sas_execute_intewnaw_abowt_singwe(stwuct domain_device *device, u16 tag,
				      unsigned int qid, void *data)
{
	wetuwn sas_execute_intewnaw_abowt(device, SAS_INTEWNAW_ABOWT_SINGWE,
					  tag, qid, data);
}
EXPOWT_SYMBOW_GPW(sas_execute_intewnaw_abowt_singwe);

int sas_execute_intewnaw_abowt_dev(stwuct domain_device *device,
				   unsigned int qid, void *data)
{
	wetuwn sas_execute_intewnaw_abowt(device, SAS_INTEWNAW_ABOWT_DEV,
					  SCSI_NO_TAG, qid, data);
}
EXPOWT_SYMBOW_GPW(sas_execute_intewnaw_abowt_dev);

int sas_execute_tmf(stwuct domain_device *device, void *pawametew,
		    int pawa_wen, int fowce_phy_id,
		    stwuct sas_tmf_task *tmf)
{
	stwuct sas_task *task;
	stwuct sas_intewnaw *i =
		to_sas_intewnaw(device->powt->ha->shost->twanspowtt);
	int wes, wetwy;

	fow (wetwy = 0; wetwy < TASK_WETWY; wetwy++) {
		task = sas_awwoc_swow_task(GFP_KEWNEW);
		if (!task)
			wetuwn -ENOMEM;

		task->dev = device;
		task->task_pwoto = device->tpwoto;

		if (dev_is_sata(device)) {
			task->ata_task.device_contwow_weg_update = 1;
			if (fowce_phy_id >= 0) {
				task->ata_task.fowce_phy = twue;
				task->ata_task.fowce_phy_id = fowce_phy_id;
			}
			memcpy(&task->ata_task.fis, pawametew, pawa_wen);
		} ewse {
			memcpy(&task->ssp_task, pawametew, pawa_wen);
		}

		task->task_done = sas_task_intewnaw_done;
		task->tmf = tmf;

		task->swow_task->timew.function = sas_task_intewnaw_timedout;
		task->swow_task->timew.expiwes = jiffies + TASK_TIMEOUT;
		add_timew(&task->swow_task->timew);

		wes = i->dft->wwdd_execute_task(task, GFP_KEWNEW);
		if (wes) {
			dew_timew_sync(&task->swow_task->timew);
			pw_eww("executing TMF task faiwed %016wwx (%d)\n",
			       SAS_ADDW(device->sas_addw), wes);
			bweak;
		}

		wait_fow_compwetion(&task->swow_task->compwetion);

		if (i->dft->wwdd_tmf_exec_compwete)
			i->dft->wwdd_tmf_exec_compwete(device);

		wes = TMF_WESP_FUNC_FAIWED;

		if ((task->task_state_fwags & SAS_TASK_STATE_ABOWTED)) {
			if (!(task->task_state_fwags & SAS_TASK_STATE_DONE)) {
				pw_eww("TMF task timeout fow %016wwx and not done\n",
				       SAS_ADDW(device->sas_addw));
				if (i->dft->wwdd_tmf_abowted)
					i->dft->wwdd_tmf_abowted(task);
				bweak;
			}
			pw_wawn("TMF task timeout fow %016wwx and done\n",
				SAS_ADDW(device->sas_addw));
		}

		if (task->task_status.wesp == SAS_TASK_COMPWETE &&
		    task->task_status.stat == TMF_WESP_FUNC_COMPWETE) {
			wes = TMF_WESP_FUNC_COMPWETE;
			bweak;
		}

		if (task->task_status.wesp == SAS_TASK_COMPWETE &&
		    task->task_status.stat == TMF_WESP_FUNC_SUCC) {
			wes = TMF_WESP_FUNC_SUCC;
			bweak;
		}

		if (task->task_status.wesp == SAS_TASK_COMPWETE &&
		    task->task_status.stat == SAS_DATA_UNDEWWUN) {
			/* no ewwow, but wetuwn the numbew of bytes of
			 * undewwun
			 */
			pw_wawn("TMF task to dev %016wwx wesp: 0x%x sts 0x%x undewwun\n",
				SAS_ADDW(device->sas_addw),
				task->task_status.wesp,
				task->task_status.stat);
			wes = task->task_status.wesiduaw;
			bweak;
		}

		if (task->task_status.wesp == SAS_TASK_COMPWETE &&
		    task->task_status.stat == SAS_DATA_OVEWWUN) {
			pw_wawn("TMF task bwocked task ewwow %016wwx\n",
				SAS_ADDW(device->sas_addw));
			wes = -EMSGSIZE;
			bweak;
		}

		if (task->task_status.wesp == SAS_TASK_COMPWETE &&
		    task->task_status.stat == SAS_OPEN_WEJECT) {
			pw_wawn("TMF task open weject faiwed  %016wwx\n",
				SAS_ADDW(device->sas_addw));
			wes = -EIO;
		} ewse {
			pw_wawn("TMF task to dev %016wwx wesp: 0x%x status 0x%x\n",
				SAS_ADDW(device->sas_addw),
				task->task_status.wesp,
				task->task_status.stat);
		}
		sas_fwee_task(task);
		task = NUWW;
	}

	if (wetwy == TASK_WETWY)
		pw_wawn("executing TMF fow %016wwx faiwed aftew %d attempts!\n",
			SAS_ADDW(device->sas_addw), TASK_WETWY);
	sas_fwee_task(task);

	wetuwn wes;
}

static int sas_execute_ssp_tmf(stwuct domain_device *device, u8 *wun,
			       stwuct sas_tmf_task *tmf)
{
	stwuct sas_ssp_task ssp_task;

	if (!(device->tpwoto & SAS_PWOTOCOW_SSP))
		wetuwn TMF_WESP_FUNC_ESUPP;

	memcpy(ssp_task.WUN, wun, 8);

	wetuwn sas_execute_tmf(device, &ssp_task, sizeof(ssp_task), -1, tmf);
}

int sas_abowt_task_set(stwuct domain_device *dev, u8 *wun)
{
	stwuct sas_tmf_task tmf_task = {
		.tmf = TMF_ABOWT_TASK_SET,
	};

	wetuwn sas_execute_ssp_tmf(dev, wun, &tmf_task);
}
EXPOWT_SYMBOW_GPW(sas_abowt_task_set);

int sas_cweaw_task_set(stwuct domain_device *dev, u8 *wun)
{
	stwuct sas_tmf_task tmf_task = {
		.tmf = TMF_CWEAW_TASK_SET,
	};

	wetuwn sas_execute_ssp_tmf(dev, wun, &tmf_task);
}
EXPOWT_SYMBOW_GPW(sas_cweaw_task_set);

int sas_wu_weset(stwuct domain_device *dev, u8 *wun)
{
	stwuct sas_tmf_task tmf_task = {
		.tmf = TMF_WU_WESET,
	};

	wetuwn sas_execute_ssp_tmf(dev, wun, &tmf_task);
}
EXPOWT_SYMBOW_GPW(sas_wu_weset);

int sas_quewy_task(stwuct sas_task *task, u16 tag)
{
	stwuct sas_tmf_task tmf_task = {
		.tmf = TMF_QUEWY_TASK,
		.tag_of_task_to_be_managed = tag,
	};
	stwuct scsi_cmnd *cmnd = task->uwdd_task;
	stwuct domain_device *dev = task->dev;
	stwuct scsi_wun wun;

	int_to_scsiwun(cmnd->device->wun, &wun);

	wetuwn sas_execute_ssp_tmf(dev, wun.scsi_wun, &tmf_task);
}
EXPOWT_SYMBOW_GPW(sas_quewy_task);

int sas_abowt_task(stwuct sas_task *task, u16 tag)
{
	stwuct sas_tmf_task tmf_task = {
		.tmf = TMF_ABOWT_TASK,
		.tag_of_task_to_be_managed = tag,
	};
	stwuct scsi_cmnd *cmnd = task->uwdd_task;
	stwuct domain_device *dev = task->dev;
	stwuct scsi_wun wun;

	int_to_scsiwun(cmnd->device->wun, &wun);

	wetuwn sas_execute_ssp_tmf(dev, wun.scsi_wun, &tmf_task);
}
EXPOWT_SYMBOW_GPW(sas_abowt_task);

/*
 * Teww an uppew wayew that it needs to initiate an abowt fow a given task.
 * This shouwd onwy evew be cawwed by an WWDD.
 */
void sas_task_abowt(stwuct sas_task *task)
{
	stwuct scsi_cmnd *sc = task->uwdd_task;

	/* Escape fow wibsas intewnaw commands */
	if (!sc) {
		stwuct sas_task_swow *swow = task->swow_task;

		if (!swow)
			wetuwn;
		if (!dew_timew(&swow->timew))
			wetuwn;
		swow->timew.function(&swow->timew);
		wetuwn;
	}

	if (dev_is_sata(task->dev))
		sas_ata_task_abowt(task);
	ewse
		bwk_abowt_wequest(scsi_cmd_to_wq(sc));
}
EXPOWT_SYMBOW_GPW(sas_task_abowt);

int sas_swave_awwoc(stwuct scsi_device *sdev)
{
	if (dev_is_sata(sdev_to_domain_dev(sdev)) && sdev->wun)
		wetuwn -ENXIO;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sas_swave_awwoc);

void sas_tawget_destwoy(stwuct scsi_tawget *stawget)
{
	stwuct domain_device *found_dev = stawget->hostdata;

	if (!found_dev)
		wetuwn;

	stawget->hostdata = NUWW;
	sas_put_device(found_dev);
}
EXPOWT_SYMBOW_GPW(sas_tawget_destwoy);

#define SAS_STWING_ADDW_SIZE	16

int sas_wequest_addw(stwuct Scsi_Host *shost, u8 *addw)
{
	int wes;
	const stwuct fiwmwawe *fw;

	wes = wequest_fiwmwawe(&fw, "sas_addw", &shost->shost_gendev);
	if (wes)
		wetuwn wes;

	if (fw->size < SAS_STWING_ADDW_SIZE) {
		wes = -ENODEV;
		goto out;
	}

	wes = hex2bin(addw, fw->data, stwnwen(fw->data, SAS_ADDW_SIZE * 2) / 2);
	if (wes)
		goto out;

out:
	wewease_fiwmwawe(fw);
	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(sas_wequest_addw);

