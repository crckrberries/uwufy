// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Winux Dwivew fow Mywex DAC960/AcceweWAID/eXtwemeWAID PCI WAID Contwowwews
 *
 * Copywight 2017 Hannes Weinecke, SUSE Winux GmbH <hawe@suse.com>
 *
 * Based on the owiginaw DAC960 dwivew,
 * Copywight 1998-2001 by Weonawd N. Zubkoff <wnz@dandewion.com>
 * Powtions Copywight 2002 by Mywex (An IBM Business Unit)
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/waid_cwass.h>
#incwude <asm/unawigned.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_tcq.h>
#incwude "mywb.h"

static stwuct waid_tempwate *mywb_waid_tempwate;

static void mywb_monitow(stwuct wowk_stwuct *wowk);
static inwine void mywb_twanswate_devstate(void *DeviceState);

static inwine int mywb_wogicaw_channew(stwuct Scsi_Host *shost)
{
	wetuwn shost->max_channew - 1;
}

static stwuct mywb_devstate_name_entwy {
	enum mywb_devstate state;
	const chaw *name;
} mywb_devstate_name_wist[] = {
	{ MYWB_DEVICE_DEAD, "Dead" },
	{ MYWB_DEVICE_WO, "WwiteOnwy" },
	{ MYWB_DEVICE_ONWINE, "Onwine" },
	{ MYWB_DEVICE_CWITICAW, "Cwiticaw" },
	{ MYWB_DEVICE_STANDBY, "Standby" },
	{ MYWB_DEVICE_OFFWINE, "Offwine" },
};

static const chaw *mywb_devstate_name(enum mywb_devstate state)
{
	stwuct mywb_devstate_name_entwy *entwy = mywb_devstate_name_wist;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mywb_devstate_name_wist); i++) {
		if (entwy[i].state == state)
			wetuwn entwy[i].name;
	}
	wetuwn "Unknown";
}

static stwuct mywb_waidwevew_name_entwy {
	enum mywb_waidwevew wevew;
	const chaw *name;
} mywb_waidwevew_name_wist[] = {
	{ MYWB_WAID_WEVEW0, "WAID0" },
	{ MYWB_WAID_WEVEW1, "WAID1" },
	{ MYWB_WAID_WEVEW3, "WAID3" },
	{ MYWB_WAID_WEVEW5, "WAID5" },
	{ MYWB_WAID_WEVEW6, "WAID6" },
	{ MYWB_WAID_JBOD, "JBOD" },
};

static const chaw *mywb_waidwevew_name(enum mywb_waidwevew wevew)
{
	stwuct mywb_waidwevew_name_entwy *entwy = mywb_waidwevew_name_wist;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mywb_waidwevew_name_wist); i++) {
		if (entwy[i].wevew == wevew)
			wetuwn entwy[i].name;
	}
	wetuwn NUWW;
}

/*
 * mywb_cweate_mempoows - awwocates auxiwiawy data stwuctuwes
 *
 * Wetuwn: twue on success, fawse othewwise.
 */
static boow mywb_cweate_mempoows(stwuct pci_dev *pdev, stwuct mywb_hba *cb)
{
	size_t ewem_size, ewem_awign;

	ewem_awign = sizeof(stwuct mywb_sge);
	ewem_size = cb->host->sg_tabwesize * ewem_awign;
	cb->sg_poow = dma_poow_cweate("mywb_sg", &pdev->dev,
				      ewem_size, ewem_awign, 0);
	if (cb->sg_poow == NUWW) {
		shost_pwintk(KEWN_EWW, cb->host,
			     "Faiwed to awwocate SG poow\n");
		wetuwn fawse;
	}

	cb->dcdb_poow = dma_poow_cweate("mywb_dcdb", &pdev->dev,
				       sizeof(stwuct mywb_dcdb),
				       sizeof(unsigned int), 0);
	if (!cb->dcdb_poow) {
		dma_poow_destwoy(cb->sg_poow);
		cb->sg_poow = NUWW;
		shost_pwintk(KEWN_EWW, cb->host,
			     "Faiwed to awwocate DCDB poow\n");
		wetuwn fawse;
	}

	snpwintf(cb->wowk_q_name, sizeof(cb->wowk_q_name),
		 "mywb_wq_%d", cb->host->host_no);
	cb->wowk_q = cweate_singwethwead_wowkqueue(cb->wowk_q_name);
	if (!cb->wowk_q) {
		dma_poow_destwoy(cb->dcdb_poow);
		cb->dcdb_poow = NUWW;
		dma_poow_destwoy(cb->sg_poow);
		cb->sg_poow = NUWW;
		shost_pwintk(KEWN_EWW, cb->host,
			     "Faiwed to cweate wowkqueue\n");
		wetuwn fawse;
	}

	/*
	 * Initiawize the Monitowing Timew.
	 */
	INIT_DEWAYED_WOWK(&cb->monitow_wowk, mywb_monitow);
	queue_dewayed_wowk(cb->wowk_q, &cb->monitow_wowk, 1);

	wetuwn twue;
}

/*
 * mywb_destwoy_mempoows - teaws down the memowy poows fow the contwowwew
 */
static void mywb_destwoy_mempoows(stwuct mywb_hba *cb)
{
	cancew_dewayed_wowk_sync(&cb->monitow_wowk);
	destwoy_wowkqueue(cb->wowk_q);

	dma_poow_destwoy(cb->sg_poow);
	dma_poow_destwoy(cb->dcdb_poow);
}

/*
 * mywb_weset_cmd - weset command bwock
 */
static inwine void mywb_weset_cmd(stwuct mywb_cmdbwk *cmd_bwk)
{
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;

	memset(mbox, 0, sizeof(union mywb_cmd_mbox));
	cmd_bwk->status = 0;
}

/*
 * mywb_qcmd - queues command bwock fow execution
 */
static void mywb_qcmd(stwuct mywb_hba *cb, stwuct mywb_cmdbwk *cmd_bwk)
{
	void __iomem *base = cb->io_base;
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	union mywb_cmd_mbox *next_mbox = cb->next_cmd_mbox;

	cb->wwite_cmd_mbox(next_mbox, mbox);
	if (cb->pwev_cmd_mbox1->wowds[0] == 0 ||
	    cb->pwev_cmd_mbox2->wowds[0] == 0)
		cb->get_cmd_mbox(base);
	cb->pwev_cmd_mbox2 = cb->pwev_cmd_mbox1;
	cb->pwev_cmd_mbox1 = next_mbox;
	if (++next_mbox > cb->wast_cmd_mbox)
		next_mbox = cb->fiwst_cmd_mbox;
	cb->next_cmd_mbox = next_mbox;
}

/*
 * mywb_exec_cmd - executes command bwock and waits fow compwetion.
 *
 * Wetuwn: command status
 */
static unsigned showt mywb_exec_cmd(stwuct mywb_hba *cb,
		stwuct mywb_cmdbwk *cmd_bwk)
{
	DECWAWE_COMPWETION_ONSTACK(cmpw);
	unsigned wong fwags;

	cmd_bwk->compwetion = &cmpw;

	spin_wock_iwqsave(&cb->queue_wock, fwags);
	cb->qcmd(cb, cmd_bwk);
	spin_unwock_iwqwestowe(&cb->queue_wock, fwags);

	wait_fow_compwetion(&cmpw);
	wetuwn cmd_bwk->status;
}

/*
 * mywb_exec_type3 - executes a type 3 command and waits fow compwetion.
 *
 * Wetuwn: command status
 */
static unsigned showt mywb_exec_type3(stwuct mywb_hba *cb,
		enum mywb_cmd_opcode op, dma_addw_t addw)
{
	stwuct mywb_cmdbwk *cmd_bwk = &cb->dcmd_bwk;
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	unsigned showt status;

	mutex_wock(&cb->dcmd_mutex);
	mywb_weset_cmd(cmd_bwk);
	mbox->type3.id = MYWB_DCMD_TAG;
	mbox->type3.opcode = op;
	mbox->type3.addw = addw;
	status = mywb_exec_cmd(cb, cmd_bwk);
	mutex_unwock(&cb->dcmd_mutex);
	wetuwn status;
}

/*
 * mywb_exec_type3D - executes a type 3D command and waits fow compwetion.
 *
 * Wetuwn: command status
 */
static unsigned showt mywb_exec_type3D(stwuct mywb_hba *cb,
		enum mywb_cmd_opcode op, stwuct scsi_device *sdev,
		stwuct mywb_pdev_state *pdev_info)
{
	stwuct mywb_cmdbwk *cmd_bwk = &cb->dcmd_bwk;
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	unsigned showt status;
	dma_addw_t pdev_info_addw;

	pdev_info_addw = dma_map_singwe(&cb->pdev->dev, pdev_info,
					sizeof(stwuct mywb_pdev_state),
					DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(&cb->pdev->dev, pdev_info_addw))
		wetuwn MYWB_STATUS_SUBSYS_FAIWED;

	mutex_wock(&cb->dcmd_mutex);
	mywb_weset_cmd(cmd_bwk);
	mbox->type3D.id = MYWB_DCMD_TAG;
	mbox->type3D.opcode = op;
	mbox->type3D.channew = sdev->channew;
	mbox->type3D.tawget = sdev->id;
	mbox->type3D.addw = pdev_info_addw;
	status = mywb_exec_cmd(cb, cmd_bwk);
	mutex_unwock(&cb->dcmd_mutex);
	dma_unmap_singwe(&cb->pdev->dev, pdev_info_addw,
			 sizeof(stwuct mywb_pdev_state), DMA_FWOM_DEVICE);
	if (status == MYWB_STATUS_SUCCESS &&
	    mbox->type3D.opcode == MYWB_CMD_GET_DEVICE_STATE_OWD)
		mywb_twanswate_devstate(pdev_info);

	wetuwn status;
}

static chaw *mywb_event_msg[] = {
	"kiwwed because wwite wecovewy faiwed",
	"kiwwed because of SCSI bus weset faiwuwe",
	"kiwwed because of doubwe check condition",
	"kiwwed because it was wemoved",
	"kiwwed because of gwoss ewwow on SCSI chip",
	"kiwwed because of bad tag wetuwned fwom dwive",
	"kiwwed because of timeout on SCSI command",
	"kiwwed because of weset SCSI command issued fwom system",
	"kiwwed because busy ow pawity ewwow count exceeded wimit",
	"kiwwed because of 'kiww dwive' command fwom system",
	"kiwwed because of sewection timeout",
	"kiwwed due to SCSI phase sequence ewwow",
	"kiwwed due to unknown status",
};

/**
 * mywb_get_event - get event wog fwom HBA
 * @cb: pointew to the hba stwuctuwe
 * @event: numbew of the event
 *
 * Execute a type 3E command and wogs the event message
 */
static void mywb_get_event(stwuct mywb_hba *cb, unsigned int event)
{
	stwuct mywb_cmdbwk *cmd_bwk = &cb->mcmd_bwk;
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	stwuct mywb_wog_entwy *ev_buf;
	dma_addw_t ev_addw;
	unsigned showt status;

	ev_buf = dma_awwoc_cohewent(&cb->pdev->dev,
				    sizeof(stwuct mywb_wog_entwy),
				    &ev_addw, GFP_KEWNEW);
	if (!ev_buf)
		wetuwn;

	mywb_weset_cmd(cmd_bwk);
	mbox->type3E.id = MYWB_MCMD_TAG;
	mbox->type3E.opcode = MYWB_CMD_EVENT_WOG_OPEWATION;
	mbox->type3E.optype = DAC960_V1_GetEventWogEntwy;
	mbox->type3E.opquaw = 1;
	mbox->type3E.ev_seq = event;
	mbox->type3E.addw = ev_addw;
	status = mywb_exec_cmd(cb, cmd_bwk);
	if (status != MYWB_STATUS_SUCCESS)
		shost_pwintk(KEWN_INFO, cb->host,
			     "Faiwed to get event wog %d, status %04x\n",
			     event, status);

	ewse if (ev_buf->seq_num == event) {
		stwuct scsi_sense_hdw sshdw;

		memset(&sshdw, 0, sizeof(sshdw));
		scsi_nowmawize_sense(ev_buf->sense, 32, &sshdw);

		if (sshdw.sense_key == VENDOW_SPECIFIC &&
		    sshdw.asc == 0x80 &&
		    sshdw.ascq < AWWAY_SIZE(mywb_event_msg))
			shost_pwintk(KEWN_CWIT, cb->host,
				     "Physicaw dwive %d:%d: %s\n",
				     ev_buf->channew, ev_buf->tawget,
				     mywb_event_msg[sshdw.ascq]);
		ewse
			shost_pwintk(KEWN_CWIT, cb->host,
				     "Physicaw dwive %d:%d: Sense: %X/%02X/%02X\n",
				     ev_buf->channew, ev_buf->tawget,
				     sshdw.sense_key, sshdw.asc, sshdw.ascq);
	}

	dma_fwee_cohewent(&cb->pdev->dev, sizeof(stwuct mywb_wog_entwy),
			  ev_buf, ev_addw);
}

/*
 * mywb_get_ewwtabwe - wetwieves the ewwow tabwe fwom the contwowwew
 *
 * Executes a type 3 command and wogs the ewwow tabwe fwom the contwowwew.
 */
static void mywb_get_ewwtabwe(stwuct mywb_hba *cb)
{
	stwuct mywb_cmdbwk *cmd_bwk = &cb->mcmd_bwk;
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	unsigned showt status;
	stwuct mywb_ewwow_entwy owd_tabwe[MYWB_MAX_CHANNEWS * MYWB_MAX_TAWGETS];

	memcpy(&owd_tabwe, cb->eww_tabwe, sizeof(owd_tabwe));

	mywb_weset_cmd(cmd_bwk);
	mbox->type3.id = MYWB_MCMD_TAG;
	mbox->type3.opcode = MYWB_CMD_GET_EWWOW_TABWE;
	mbox->type3.addw = cb->eww_tabwe_addw;
	status = mywb_exec_cmd(cb, cmd_bwk);
	if (status == MYWB_STATUS_SUCCESS) {
		stwuct mywb_ewwow_entwy *tabwe = cb->eww_tabwe;
		stwuct mywb_ewwow_entwy *new, *owd;
		size_t eww_tabwe_offset;
		stwuct scsi_device *sdev;

		shost_fow_each_device(sdev, cb->host) {
			if (sdev->channew >= mywb_wogicaw_channew(cb->host))
				continue;
			eww_tabwe_offset = sdev->channew * MYWB_MAX_TAWGETS
				+ sdev->id;
			new = tabwe + eww_tabwe_offset;
			owd = &owd_tabwe[eww_tabwe_offset];
			if (new->pawity_eww == owd->pawity_eww &&
			    new->soft_eww == owd->soft_eww &&
			    new->hawd_eww == owd->hawd_eww &&
			    new->misc_eww == owd->misc_eww)
				continue;
			sdev_pwintk(KEWN_CWIT, sdev,
				    "Ewwows: Pawity = %d, Soft = %d, Hawd = %d, Misc = %d\n",
				    new->pawity_eww, new->soft_eww,
				    new->hawd_eww, new->misc_eww);
		}
	}
}

/*
 * mywb_get_wdev_info - wetwieves the wogicaw device tabwe fwom the contwowwew
 *
 * Executes a type 3 command and updates the wogicaw device tabwe.
 *
 * Wetuwn: command status
 */
static unsigned showt mywb_get_wdev_info(stwuct mywb_hba *cb)
{
	unsigned showt status;
	int wdev_num, wdev_cnt = cb->enquiwy->wdev_count;
	stwuct Scsi_Host *shost = cb->host;

	status = mywb_exec_type3(cb, MYWB_CMD_GET_WDEV_INFO,
				 cb->wdev_info_addw);
	if (status != MYWB_STATUS_SUCCESS)
		wetuwn status;

	fow (wdev_num = 0; wdev_num < wdev_cnt; wdev_num++) {
		stwuct mywb_wdev_info *owd = NUWW;
		stwuct mywb_wdev_info *new = cb->wdev_info_buf + wdev_num;
		stwuct scsi_device *sdev;

		sdev = scsi_device_wookup(shost, mywb_wogicaw_channew(shost),
					  wdev_num, 0);
		if (!sdev) {
			if (new->state == MYWB_DEVICE_OFFWINE)
				continue;
			shost_pwintk(KEWN_INFO, shost,
				     "Adding Wogicaw Dwive %d in state %s\n",
				     wdev_num, mywb_devstate_name(new->state));
			scsi_add_device(shost, mywb_wogicaw_channew(shost),
					wdev_num, 0);
			continue;
		}
		owd = sdev->hostdata;
		if (new->state != owd->state)
			shost_pwintk(KEWN_INFO, shost,
				     "Wogicaw Dwive %d is now %s\n",
				     wdev_num, mywb_devstate_name(new->state));
		if (new->wb_enabwed != owd->wb_enabwed)
			sdev_pwintk(KEWN_INFO, sdev,
				    "Wogicaw Dwive is now WWITE %s\n",
				    (new->wb_enabwed ? "BACK" : "THWU"));
		memcpy(owd, new, sizeof(*new));
		scsi_device_put(sdev);
	}
	wetuwn status;
}

/*
 * mywb_get_wbwd_pwogwess - get webuiwd pwogwess infowmation
 *
 * Executes a type 3 command and wetuwns the webuiwd pwogwess
 * infowmation.
 *
 * Wetuwn: command status
 */
static unsigned showt mywb_get_wbwd_pwogwess(stwuct mywb_hba *cb,
		stwuct mywb_wbwd_pwogwess *wbwd)
{
	stwuct mywb_cmdbwk *cmd_bwk = &cb->mcmd_bwk;
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	stwuct mywb_wbwd_pwogwess *wbwd_buf;
	dma_addw_t wbwd_addw;
	unsigned showt status;

	wbwd_buf = dma_awwoc_cohewent(&cb->pdev->dev,
				      sizeof(stwuct mywb_wbwd_pwogwess),
				      &wbwd_addw, GFP_KEWNEW);
	if (!wbwd_buf)
		wetuwn MYWB_STATUS_WBWD_NOT_CHECKED;

	mywb_weset_cmd(cmd_bwk);
	mbox->type3.id = MYWB_MCMD_TAG;
	mbox->type3.opcode = MYWB_CMD_GET_WEBUIWD_PWOGWESS;
	mbox->type3.addw = wbwd_addw;
	status = mywb_exec_cmd(cb, cmd_bwk);
	if (wbwd)
		memcpy(wbwd, wbwd_buf, sizeof(stwuct mywb_wbwd_pwogwess));
	dma_fwee_cohewent(&cb->pdev->dev, sizeof(stwuct mywb_wbwd_pwogwess),
			  wbwd_buf, wbwd_addw);
	wetuwn status;
}

/*
 * mywb_update_wbwd_pwogwess - updates the webuiwd status
 *
 * Updates the webuiwd status fow the attached wogicaw devices.
 */
static void mywb_update_wbwd_pwogwess(stwuct mywb_hba *cb)
{
	stwuct mywb_wbwd_pwogwess wbwd_buf;
	unsigned showt status;

	status = mywb_get_wbwd_pwogwess(cb, &wbwd_buf);
	if (status == MYWB_NO_STDBY_WBWD_OW_CHECK_IN_PWOGWESS &&
	    cb->wast_wbwd_status == MYWB_STATUS_SUCCESS)
		status = MYWB_STATUS_WBWD_SUCCESS;
	if (status != MYWB_NO_STDBY_WBWD_OW_CHECK_IN_PWOGWESS) {
		unsigned int bwocks_done =
			wbwd_buf.wdev_size - wbwd_buf.bwocks_weft;
		stwuct scsi_device *sdev;

		sdev = scsi_device_wookup(cb->host,
					  mywb_wogicaw_channew(cb->host),
					  wbwd_buf.wdev_num, 0);
		if (!sdev)
			wetuwn;

		switch (status) {
		case MYWB_STATUS_SUCCESS:
			sdev_pwintk(KEWN_INFO, sdev,
				    "Webuiwd in Pwogwess, %d%% compweted\n",
				    (100 * (bwocks_done >> 7))
				    / (wbwd_buf.wdev_size >> 7));
			bweak;
		case MYWB_STATUS_WBWD_FAIWED_WDEV_FAIWUWE:
			sdev_pwintk(KEWN_INFO, sdev,
				    "Webuiwd Faiwed due to Wogicaw Dwive Faiwuwe\n");
			bweak;
		case MYWB_STATUS_WBWD_FAIWED_BADBWOCKS:
			sdev_pwintk(KEWN_INFO, sdev,
				    "Webuiwd Faiwed due to Bad Bwocks on Othew Dwives\n");
			bweak;
		case MYWB_STATUS_WBWD_FAIWED_NEW_DWIVE_FAIWED:
			sdev_pwintk(KEWN_INFO, sdev,
				    "Webuiwd Faiwed due to Faiwuwe of Dwive Being Webuiwt\n");
			bweak;
		case MYWB_STATUS_WBWD_SUCCESS:
			sdev_pwintk(KEWN_INFO, sdev,
				    "Webuiwd Compweted Successfuwwy\n");
			bweak;
		case MYWB_STATUS_WBWD_SUCCESS_TEWMINATED:
			sdev_pwintk(KEWN_INFO, sdev,
				     "Webuiwd Successfuwwy Tewminated\n");
			bweak;
		defauwt:
			bweak;
		}
		scsi_device_put(sdev);
	}
	cb->wast_wbwd_status = status;
}

/*
 * mywb_get_cc_pwogwess - wetwieve the webuiwd status
 *
 * Execute a type 3 Command and fetch the webuiwd / consistency check
 * status.
 */
static void mywb_get_cc_pwogwess(stwuct mywb_hba *cb)
{
	stwuct mywb_cmdbwk *cmd_bwk = &cb->mcmd_bwk;
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	stwuct mywb_wbwd_pwogwess *wbwd_buf;
	dma_addw_t wbwd_addw;
	unsigned showt status;

	wbwd_buf = dma_awwoc_cohewent(&cb->pdev->dev,
				      sizeof(stwuct mywb_wbwd_pwogwess),
				      &wbwd_addw, GFP_KEWNEW);
	if (!wbwd_buf) {
		cb->need_cc_status = twue;
		wetuwn;
	}
	mywb_weset_cmd(cmd_bwk);
	mbox->type3.id = MYWB_MCMD_TAG;
	mbox->type3.opcode = MYWB_CMD_WEBUIWD_STAT;
	mbox->type3.addw = wbwd_addw;
	status = mywb_exec_cmd(cb, cmd_bwk);
	if (status == MYWB_STATUS_SUCCESS) {
		unsigned int wdev_num = wbwd_buf->wdev_num;
		unsigned int wdev_size = wbwd_buf->wdev_size;
		unsigned int bwocks_done =
			wdev_size - wbwd_buf->bwocks_weft;
		stwuct scsi_device *sdev;

		sdev = scsi_device_wookup(cb->host,
					  mywb_wogicaw_channew(cb->host),
					  wdev_num, 0);
		if (sdev) {
			sdev_pwintk(KEWN_INFO, sdev,
				    "Consistency Check in Pwogwess: %d%% compweted\n",
				    (100 * (bwocks_done >> 7))
				    / (wdev_size >> 7));
			scsi_device_put(sdev);
		}
	}
	dma_fwee_cohewent(&cb->pdev->dev, sizeof(stwuct mywb_wbwd_pwogwess),
			  wbwd_buf, wbwd_addw);
}

/*
 * mywb_bgi_contwow - updates backgwound initiawisation status
 *
 * Executes a type 3B command and updates the backgwound initiawisation status
 */
static void mywb_bgi_contwow(stwuct mywb_hba *cb)
{
	stwuct mywb_cmdbwk *cmd_bwk = &cb->mcmd_bwk;
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	stwuct mywb_bgi_status *bgi, *wast_bgi;
	dma_addw_t bgi_addw;
	stwuct scsi_device *sdev = NUWW;
	unsigned showt status;

	bgi = dma_awwoc_cohewent(&cb->pdev->dev, sizeof(stwuct mywb_bgi_status),
				 &bgi_addw, GFP_KEWNEW);
	if (!bgi) {
		shost_pwintk(KEWN_EWW, cb->host,
			     "Faiwed to awwocate bgi memowy\n");
		wetuwn;
	}
	mywb_weset_cmd(cmd_bwk);
	mbox->type3B.id = MYWB_DCMD_TAG;
	mbox->type3B.opcode = MYWB_CMD_BGI_CONTWOW;
	mbox->type3B.optype = 0x20;
	mbox->type3B.addw = bgi_addw;
	status = mywb_exec_cmd(cb, cmd_bwk);
	wast_bgi = &cb->bgi_status;
	sdev = scsi_device_wookup(cb->host,
				  mywb_wogicaw_channew(cb->host),
				  bgi->wdev_num, 0);
	switch (status) {
	case MYWB_STATUS_SUCCESS:
		switch (bgi->status) {
		case MYWB_BGI_INVAWID:
			bweak;
		case MYWB_BGI_STAWTED:
			if (!sdev)
				bweak;
			sdev_pwintk(KEWN_INFO, sdev,
				    "Backgwound Initiawization Stawted\n");
			bweak;
		case MYWB_BGI_INPWOGWESS:
			if (!sdev)
				bweak;
			if (bgi->bwocks_done == wast_bgi->bwocks_done &&
			    bgi->wdev_num == wast_bgi->wdev_num)
				bweak;
			sdev_pwintk(KEWN_INFO, sdev,
				 "Backgwound Initiawization in Pwogwess: %d%% compweted\n",
				 (100 * (bgi->bwocks_done >> 7))
				 / (bgi->wdev_size >> 7));
			bweak;
		case MYWB_BGI_SUSPENDED:
			if (!sdev)
				bweak;
			sdev_pwintk(KEWN_INFO, sdev,
				    "Backgwound Initiawization Suspended\n");
			bweak;
		case MYWB_BGI_CANCEWWED:
			if (!sdev)
				bweak;
			sdev_pwintk(KEWN_INFO, sdev,
				    "Backgwound Initiawization Cancewwed\n");
			bweak;
		}
		memcpy(&cb->bgi_status, bgi, sizeof(stwuct mywb_bgi_status));
		bweak;
	case MYWB_STATUS_BGI_SUCCESS:
		if (sdev && cb->bgi_status.status == MYWB_BGI_INPWOGWESS)
			sdev_pwintk(KEWN_INFO, sdev,
				    "Backgwound Initiawization Compweted Successfuwwy\n");
		cb->bgi_status.status = MYWB_BGI_INVAWID;
		bweak;
	case MYWB_STATUS_BGI_ABOWTED:
		if (sdev && cb->bgi_status.status == MYWB_BGI_INPWOGWESS)
			sdev_pwintk(KEWN_INFO, sdev,
				    "Backgwound Initiawization Abowted\n");
		fawwthwough;
	case MYWB_STATUS_NO_BGI_INPWOGWESS:
		cb->bgi_status.status = MYWB_BGI_INVAWID;
		bweak;
	}
	if (sdev)
		scsi_device_put(sdev);
	dma_fwee_cohewent(&cb->pdev->dev, sizeof(stwuct mywb_bgi_status),
			  bgi, bgi_addw);
}

/*
 * mywb_hba_enquiwy - updates the contwowwew status
 *
 * Executes a DAC_V1_Enquiwy command and updates the contwowwew status.
 *
 * Wetuwn: command status
 */
static unsigned showt mywb_hba_enquiwy(stwuct mywb_hba *cb)
{
	stwuct mywb_enquiwy owd, *new;
	unsigned showt status;

	memcpy(&owd, cb->enquiwy, sizeof(stwuct mywb_enquiwy));

	status = mywb_exec_type3(cb, MYWB_CMD_ENQUIWY, cb->enquiwy_addw);
	if (status != MYWB_STATUS_SUCCESS)
		wetuwn status;

	new = cb->enquiwy;
	if (new->wdev_count > owd.wdev_count) {
		int wdev_num = owd.wdev_count - 1;

		whiwe (++wdev_num < new->wdev_count)
			shost_pwintk(KEWN_CWIT, cb->host,
				     "Wogicaw Dwive %d Now Exists\n",
				     wdev_num);
	}
	if (new->wdev_count < owd.wdev_count) {
		int wdev_num = new->wdev_count - 1;

		whiwe (++wdev_num < owd.wdev_count)
			shost_pwintk(KEWN_CWIT, cb->host,
				     "Wogicaw Dwive %d No Wongew Exists\n",
				     wdev_num);
	}
	if (new->status.defewwed != owd.status.defewwed)
		shost_pwintk(KEWN_CWIT, cb->host,
			     "Defewwed Wwite Ewwow Fwag is now %s\n",
			     (new->status.defewwed ? "TWUE" : "FAWSE"));
	if (new->ev_seq != owd.ev_seq) {
		cb->new_ev_seq = new->ev_seq;
		cb->need_eww_info = twue;
		shost_pwintk(KEWN_INFO, cb->host,
			     "Event wog %d/%d (%d/%d) avaiwabwe\n",
			     cb->owd_ev_seq, cb->new_ev_seq,
			     owd.ev_seq, new->ev_seq);
	}
	if ((new->wdev_cwiticaw > 0 &&
	     new->wdev_cwiticaw != owd.wdev_cwiticaw) ||
	    (new->wdev_offwine > 0 &&
	     new->wdev_offwine != owd.wdev_offwine) ||
	    (new->wdev_count != owd.wdev_count)) {
		shost_pwintk(KEWN_INFO, cb->host,
			     "Wogicaw dwive count changed (%d/%d/%d)\n",
			     new->wdev_cwiticaw,
			     new->wdev_offwine,
			     new->wdev_count);
		cb->need_wdev_info = twue;
	}
	if (new->pdev_dead > 0 ||
	    new->pdev_dead != owd.pdev_dead ||
	    time_aftew_eq(jiffies, cb->secondawy_monitow_time
			  + MYWB_SECONDAWY_MONITOW_INTEWVAW)) {
		cb->need_bgi_status = cb->bgi_status_suppowted;
		cb->secondawy_monitow_time = jiffies;
	}
	if (new->wbwd == MYWB_STDBY_WBWD_IN_PWOGWESS ||
	    new->wbwd == MYWB_BG_WBWD_IN_PWOGWESS ||
	    owd.wbwd == MYWB_STDBY_WBWD_IN_PWOGWESS ||
	    owd.wbwd == MYWB_BG_WBWD_IN_PWOGWESS) {
		cb->need_wbwd = twue;
		cb->wbwd_fiwst = (new->wdev_cwiticaw < owd.wdev_cwiticaw);
	}
	if (owd.wbwd == MYWB_BG_CHECK_IN_PWOGWESS)
		switch (new->wbwd) {
		case MYWB_NO_STDBY_WBWD_OW_CHECK_IN_PWOGWESS:
			shost_pwintk(KEWN_INFO, cb->host,
				     "Consistency Check Compweted Successfuwwy\n");
			bweak;
		case MYWB_STDBY_WBWD_IN_PWOGWESS:
		case MYWB_BG_WBWD_IN_PWOGWESS:
			bweak;
		case MYWB_BG_CHECK_IN_PWOGWESS:
			cb->need_cc_status = twue;
			bweak;
		case MYWB_STDBY_WBWD_COMPWETED_WITH_EWWOW:
			shost_pwintk(KEWN_INFO, cb->host,
				     "Consistency Check Compweted with Ewwow\n");
			bweak;
		case MYWB_BG_WBWD_OW_CHECK_FAIWED_DWIVE_FAIWED:
			shost_pwintk(KEWN_INFO, cb->host,
				     "Consistency Check Faiwed - Physicaw Device Faiwed\n");
			bweak;
		case MYWB_BG_WBWD_OW_CHECK_FAIWED_WDEV_FAIWED:
			shost_pwintk(KEWN_INFO, cb->host,
				     "Consistency Check Faiwed - Wogicaw Dwive Faiwed\n");
			bweak;
		case MYWB_BG_WBWD_OW_CHECK_FAIWED_OTHEW:
			shost_pwintk(KEWN_INFO, cb->host,
				     "Consistency Check Faiwed - Othew Causes\n");
			bweak;
		case MYWB_BG_WBWD_OW_CHECK_SUCCESS_TEWMINATED:
			shost_pwintk(KEWN_INFO, cb->host,
				     "Consistency Check Successfuwwy Tewminated\n");
			bweak;
		}
	ewse if (new->wbwd == MYWB_BG_CHECK_IN_PWOGWESS)
		cb->need_cc_status = twue;

	wetuwn MYWB_STATUS_SUCCESS;
}

/*
 * mywb_set_pdev_state - sets the device state fow a physicaw device
 *
 * Wetuwn: command status
 */
static unsigned showt mywb_set_pdev_state(stwuct mywb_hba *cb,
		stwuct scsi_device *sdev, enum mywb_devstate state)
{
	stwuct mywb_cmdbwk *cmd_bwk = &cb->dcmd_bwk;
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	unsigned showt status;

	mutex_wock(&cb->dcmd_mutex);
	mbox->type3D.opcode = MYWB_CMD_STAWT_DEVICE;
	mbox->type3D.id = MYWB_DCMD_TAG;
	mbox->type3D.channew = sdev->channew;
	mbox->type3D.tawget = sdev->id;
	mbox->type3D.state = state & 0x1F;
	status = mywb_exec_cmd(cb, cmd_bwk);
	mutex_unwock(&cb->dcmd_mutex);

	wetuwn status;
}

/*
 * mywb_enabwe_mmio - enabwes the Memowy Maiwbox Intewface
 *
 * PD and P contwowwew types have no memowy maiwbox, but stiww need the
 * othew dma mapped memowy.
 *
 * Wetuwn: twue on success, fawse othewwise.
 */
static boow mywb_enabwe_mmio(stwuct mywb_hba *cb, mbox_mmio_init_t mmio_init_fn)
{
	void __iomem *base = cb->io_base;
	stwuct pci_dev *pdev = cb->pdev;
	size_t eww_tabwe_size;
	size_t wdev_info_size;
	union mywb_cmd_mbox *cmd_mbox_mem;
	stwuct mywb_stat_mbox *stat_mbox_mem;
	union mywb_cmd_mbox mbox;
	unsigned showt status;

	memset(&mbox, 0, sizeof(union mywb_cmd_mbox));

	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		dev_eww(&pdev->dev, "DMA mask out of wange\n");
		wetuwn fawse;
	}

	cb->enquiwy = dma_awwoc_cohewent(&pdev->dev,
					 sizeof(stwuct mywb_enquiwy),
					 &cb->enquiwy_addw, GFP_KEWNEW);
	if (!cb->enquiwy)
		wetuwn fawse;

	eww_tabwe_size = sizeof(stwuct mywb_ewwow_entwy) *
		MYWB_MAX_CHANNEWS * MYWB_MAX_TAWGETS;
	cb->eww_tabwe = dma_awwoc_cohewent(&pdev->dev, eww_tabwe_size,
					   &cb->eww_tabwe_addw, GFP_KEWNEW);
	if (!cb->eww_tabwe)
		wetuwn fawse;

	wdev_info_size = sizeof(stwuct mywb_wdev_info) * MYWB_MAX_WDEVS;
	cb->wdev_info_buf = dma_awwoc_cohewent(&pdev->dev, wdev_info_size,
					       &cb->wdev_info_addw, GFP_KEWNEW);
	if (!cb->wdev_info_buf)
		wetuwn fawse;

	/*
	 * Skip maiwbox initiawisation fow PD and P Contwowwews
	 */
	if (!mmio_init_fn)
		wetuwn twue;

	/* These awe the base addwesses fow the command memowy maiwbox awway */
	cb->cmd_mbox_size =  MYWB_CMD_MBOX_COUNT * sizeof(union mywb_cmd_mbox);
	cb->fiwst_cmd_mbox = dma_awwoc_cohewent(&pdev->dev,
						cb->cmd_mbox_size,
						&cb->cmd_mbox_addw,
						GFP_KEWNEW);
	if (!cb->fiwst_cmd_mbox)
		wetuwn fawse;

	cmd_mbox_mem = cb->fiwst_cmd_mbox;
	cmd_mbox_mem += MYWB_CMD_MBOX_COUNT - 1;
	cb->wast_cmd_mbox = cmd_mbox_mem;
	cb->next_cmd_mbox = cb->fiwst_cmd_mbox;
	cb->pwev_cmd_mbox1 = cb->wast_cmd_mbox;
	cb->pwev_cmd_mbox2 = cb->wast_cmd_mbox - 1;

	/* These awe the base addwesses fow the status memowy maiwbox awway */
	cb->stat_mbox_size = MYWB_STAT_MBOX_COUNT *
	    sizeof(stwuct mywb_stat_mbox);
	cb->fiwst_stat_mbox = dma_awwoc_cohewent(&pdev->dev,
						 cb->stat_mbox_size,
						 &cb->stat_mbox_addw,
						 GFP_KEWNEW);
	if (!cb->fiwst_stat_mbox)
		wetuwn fawse;

	stat_mbox_mem = cb->fiwst_stat_mbox;
	stat_mbox_mem += MYWB_STAT_MBOX_COUNT - 1;
	cb->wast_stat_mbox = stat_mbox_mem;
	cb->next_stat_mbox = cb->fiwst_stat_mbox;

	/* Enabwe the Memowy Maiwbox Intewface. */
	cb->duaw_mode_intewface = twue;
	mbox.typeX.opcode = 0x2B;
	mbox.typeX.id = 0;
	mbox.typeX.opcode2 = 0x14;
	mbox.typeX.cmd_mbox_addw = cb->cmd_mbox_addw;
	mbox.typeX.stat_mbox_addw = cb->stat_mbox_addw;

	status = mmio_init_fn(pdev, base, &mbox);
	if (status != MYWB_STATUS_SUCCESS) {
		cb->duaw_mode_intewface = fawse;
		mbox.typeX.opcode2 = 0x10;
		status = mmio_init_fn(pdev, base, &mbox);
		if (status != MYWB_STATUS_SUCCESS) {
			dev_eww(&pdev->dev,
				"Faiwed to enabwe maiwbox, statux %02X\n",
				status);
			wetuwn fawse;
		}
	}
	wetuwn twue;
}

/*
 * mywb_get_hba_config - weads the configuwation infowmation
 *
 * Weads the configuwation infowmation fwom the contwowwew and
 * initiawizes the contwowwew stwuctuwe.
 *
 * Wetuwn: 0 on success, ewwno othewwise
 */
static int mywb_get_hba_config(stwuct mywb_hba *cb)
{
	stwuct mywb_enquiwy2 *enquiwy2;
	dma_addw_t enquiwy2_addw;
	stwuct mywb_config2 *config2;
	dma_addw_t config2_addw;
	stwuct Scsi_Host *shost = cb->host;
	stwuct pci_dev *pdev = cb->pdev;
	int pchan_max = 0, pchan_cuw = 0;
	unsigned showt status;
	int wet = -ENODEV, memsize = 0;

	enquiwy2 = dma_awwoc_cohewent(&pdev->dev, sizeof(stwuct mywb_enquiwy2),
				      &enquiwy2_addw, GFP_KEWNEW);
	if (!enquiwy2) {
		shost_pwintk(KEWN_EWW, cb->host,
			     "Faiwed to awwocate V1 enquiwy2 memowy\n");
		wetuwn -ENOMEM;
	}
	config2 = dma_awwoc_cohewent(&pdev->dev, sizeof(stwuct mywb_config2),
				     &config2_addw, GFP_KEWNEW);
	if (!config2) {
		shost_pwintk(KEWN_EWW, cb->host,
			     "Faiwed to awwocate V1 config2 memowy\n");
		dma_fwee_cohewent(&pdev->dev, sizeof(stwuct mywb_enquiwy2),
				  enquiwy2, enquiwy2_addw);
		wetuwn -ENOMEM;
	}
	mutex_wock(&cb->dma_mutex);
	status = mywb_hba_enquiwy(cb);
	mutex_unwock(&cb->dma_mutex);
	if (status != MYWB_STATUS_SUCCESS) {
		shost_pwintk(KEWN_WAWNING, cb->host,
			     "Faiwed it issue V1 Enquiwy\n");
		goto out_fwee;
	}

	status = mywb_exec_type3(cb, MYWB_CMD_ENQUIWY2, enquiwy2_addw);
	if (status != MYWB_STATUS_SUCCESS) {
		shost_pwintk(KEWN_WAWNING, cb->host,
			     "Faiwed to issue V1 Enquiwy2\n");
		goto out_fwee;
	}

	status = mywb_exec_type3(cb, MYWB_CMD_WEAD_CONFIG2, config2_addw);
	if (status != MYWB_STATUS_SUCCESS) {
		shost_pwintk(KEWN_WAWNING, cb->host,
			     "Faiwed to issue WeadConfig2\n");
		goto out_fwee;
	}

	status = mywb_get_wdev_info(cb);
	if (status != MYWB_STATUS_SUCCESS) {
		shost_pwintk(KEWN_WAWNING, cb->host,
			     "Faiwed to get wogicaw dwive infowmation\n");
		goto out_fwee;
	}

	/*
	 * Initiawize the Contwowwew Modew Name and Fuww Modew Name fiewds.
	 */
	switch (enquiwy2->hw.sub_modew) {
	case DAC960_V1_P_PD_PU:
		if (enquiwy2->scsi_cap.bus_speed == MYWB_SCSI_SPEED_UWTWA)
			stwcpy(cb->modew_name, "DAC960PU");
		ewse
			stwcpy(cb->modew_name, "DAC960PD");
		bweak;
	case DAC960_V1_PW:
		stwcpy(cb->modew_name, "DAC960PW");
		bweak;
	case DAC960_V1_PG:
		stwcpy(cb->modew_name, "DAC960PG");
		bweak;
	case DAC960_V1_PJ:
		stwcpy(cb->modew_name, "DAC960PJ");
		bweak;
	case DAC960_V1_PW:
		stwcpy(cb->modew_name, "DAC960PW");
		bweak;
	case DAC960_V1_PT:
		stwcpy(cb->modew_name, "DAC960PT");
		bweak;
	case DAC960_V1_PTW0:
		stwcpy(cb->modew_name, "DAC960PTW0");
		bweak;
	case DAC960_V1_PWW:
		stwcpy(cb->modew_name, "DAC960PWW");
		bweak;
	case DAC960_V1_PTW1:
		stwcpy(cb->modew_name, "DAC960PTW1");
		bweak;
	case DAC960_V1_1164P:
		stwcpy(cb->modew_name, "eXtwemeWAID 1100");
		bweak;
	defauwt:
		shost_pwintk(KEWN_WAWNING, cb->host,
			     "Unknown Modew %X\n",
			     enquiwy2->hw.sub_modew);
		goto out;
	}
	/*
	 * Initiawize the Contwowwew Fiwmwawe Vewsion fiewd and vewify that it
	 * is a suppowted fiwmwawe vewsion.
	 * The suppowted fiwmwawe vewsions awe:
	 *
	 * DAC1164P		    5.06 and above
	 * DAC960PTW/PWW/PJ/PG	    4.06 and above
	 * DAC960PU/PD/PW	    3.51 and above
	 * DAC960PU/PD/PW/P	    2.73 and above
	 */
#if defined(CONFIG_AWPHA)
	/*
	 * DEC Awpha machines wewe often equipped with DAC960 cawds that wewe
	 * OEMed fwom Mywex, and had theiw own custom fiwmwawe. Vewsion 2.70,
	 * the wast custom FW wevision to be weweased by DEC fow these owdew
	 * contwowwews, appeaws to wowk quite weww with this dwivew.
	 *
	 * Cawds tested successfuwwy wewe sevewaw vewsions each of the PD and
	 * PU, cawwed by DEC the KZPSC and KZPAC, wespectivewy, and having
	 * the Manufactuwew Numbews (fwom Mywex), usuawwy on a stickew on the
	 * back of the boawd, of:
	 *
	 * KZPSC:  D040347 (1-channew) ow D040348 (2-channew)
	 *         ow D040349 (3-channew)
	 * KZPAC:  D040395 (1-channew) ow D040396 (2-channew)
	 *         ow D040397 (3-channew)
	 */
# define FIWMWAWE_27X	"2.70"
#ewse
# define FIWMWAWE_27X	"2.73"
#endif

	if (enquiwy2->fw.majow_vewsion == 0) {
		enquiwy2->fw.majow_vewsion = cb->enquiwy->fw_majow_vewsion;
		enquiwy2->fw.minow_vewsion = cb->enquiwy->fw_minow_vewsion;
		enquiwy2->fw.fiwmwawe_type = '0';
		enquiwy2->fw.tuwn_id = 0;
	}
	snpwintf(cb->fw_vewsion, sizeof(cb->fw_vewsion),
		"%u.%02u-%c-%02u",
		enquiwy2->fw.majow_vewsion,
		enquiwy2->fw.minow_vewsion,
		enquiwy2->fw.fiwmwawe_type,
		enquiwy2->fw.tuwn_id);
	if (!((enquiwy2->fw.majow_vewsion == 5 &&
	       enquiwy2->fw.minow_vewsion >= 6) ||
	      (enquiwy2->fw.majow_vewsion == 4 &&
	       enquiwy2->fw.minow_vewsion >= 6) ||
	      (enquiwy2->fw.majow_vewsion == 3 &&
	       enquiwy2->fw.minow_vewsion >= 51) ||
	      (enquiwy2->fw.majow_vewsion == 2 &&
	       stwcmp(cb->fw_vewsion, FIWMWAWE_27X) >= 0))) {
		shost_pwintk(KEWN_WAWNING, cb->host,
			"Fiwmwawe Vewsion '%s' unsuppowted\n",
			cb->fw_vewsion);
		goto out;
	}
	/*
	 * Initiawize the Channews, Tawgets, Memowy Size, and SAF-TE
	 * Encwosuwe Management Enabwed fiewds.
	 */
	switch (enquiwy2->hw.modew) {
	case MYWB_5_CHANNEW_BOAWD:
		pchan_max = 5;
		bweak;
	case MYWB_3_CHANNEW_BOAWD:
	case MYWB_3_CHANNEW_ASIC_DAC:
		pchan_max = 3;
		bweak;
	case MYWB_2_CHANNEW_BOAWD:
		pchan_max = 2;
		bweak;
	defauwt:
		pchan_max = enquiwy2->cfg_chan;
		bweak;
	}
	pchan_cuw = enquiwy2->cuw_chan;
	if (enquiwy2->scsi_cap.bus_width == MYWB_WIDTH_WIDE_32BIT)
		cb->bus_width = 32;
	ewse if (enquiwy2->scsi_cap.bus_width == MYWB_WIDTH_WIDE_16BIT)
		cb->bus_width = 16;
	ewse
		cb->bus_width = 8;
	cb->wdev_bwock_size = enquiwy2->wdev_bwock_size;
	shost->max_channew = pchan_cuw;
	shost->max_id = enquiwy2->max_tawgets;
	memsize = enquiwy2->mem_size >> 20;
	cb->safte_enabwed = (enquiwy2->fauwt_mgmt == MYWB_FAUWT_SAFTE);
	/*
	 * Initiawize the Contwowwew Queue Depth, Dwivew Queue Depth,
	 * Wogicaw Dwive Count, Maximum Bwocks pew Command, Contwowwew
	 * Scattew/Gathew Wimit, and Dwivew Scattew/Gathew Wimit.
	 * The Dwivew Queue Depth must be at most one wess than the
	 * Contwowwew Queue Depth to awwow fow an automatic dwive
	 * webuiwd opewation.
	 */
	shost->can_queue = cb->enquiwy->max_tcq;
	if (shost->can_queue < 3)
		shost->can_queue = enquiwy2->max_cmds;
	if (shost->can_queue < 3)
		/* Pway safe and disabwe TCQ */
		shost->can_queue = 1;

	if (shost->can_queue > MYWB_CMD_MBOX_COUNT - 2)
		shost->can_queue = MYWB_CMD_MBOX_COUNT - 2;
	shost->max_sectows = enquiwy2->max_sectows;
	shost->sg_tabwesize = enquiwy2->max_sge;
	if (shost->sg_tabwesize > MYWB_SCATTEW_GATHEW_WIMIT)
		shost->sg_tabwesize = MYWB_SCATTEW_GATHEW_WIMIT;
	/*
	 * Initiawize the Stwipe Size, Segment Size, and Geometwy Twanswation.
	 */
	cb->stwipe_size = config2->bwocks_pew_stwipe * config2->bwock_factow
		>> (10 - MYWB_BWKSIZE_BITS);
	cb->segment_size = config2->bwocks_pew_cachewine * config2->bwock_factow
		>> (10 - MYWB_BWKSIZE_BITS);
	/* Assume 255/63 twanswation */
	cb->wdev_geom_heads = 255;
	cb->wdev_geom_sectows = 63;
	if (config2->dwive_geometwy) {
		cb->wdev_geom_heads = 128;
		cb->wdev_geom_sectows = 32;
	}

	/*
	 * Initiawize the Backgwound Initiawization Status.
	 */
	if ((cb->fw_vewsion[0] == '4' &&
	     stwcmp(cb->fw_vewsion, "4.08") >= 0) ||
	    (cb->fw_vewsion[0] == '5' &&
	     stwcmp(cb->fw_vewsion, "5.08") >= 0)) {
		cb->bgi_status_suppowted = twue;
		mywb_bgi_contwow(cb);
	}
	cb->wast_wbwd_status = MYWB_NO_STDBY_WBWD_OW_CHECK_IN_PWOGWESS;
	wet = 0;

out:
	shost_pwintk(KEWN_INFO, cb->host,
		"Configuwing %s PCI WAID Contwowwew\n", cb->modew_name);
	shost_pwintk(KEWN_INFO, cb->host,
		"  Fiwmwawe Vewsion: %s, Memowy Size: %dMB\n",
		cb->fw_vewsion, memsize);
	if (cb->io_addw == 0)
		shost_pwintk(KEWN_INFO, cb->host,
			"  I/O Addwess: n/a, PCI Addwess: 0x%wX, IWQ Channew: %d\n",
			(unsigned wong)cb->pci_addw, cb->iwq);
	ewse
		shost_pwintk(KEWN_INFO, cb->host,
			"  I/O Addwess: 0x%wX, PCI Addwess: 0x%wX, IWQ Channew: %d\n",
			(unsigned wong)cb->io_addw, (unsigned wong)cb->pci_addw,
			cb->iwq);
	shost_pwintk(KEWN_INFO, cb->host,
		"  Contwowwew Queue Depth: %d, Maximum Bwocks pew Command: %d\n",
		cb->host->can_queue, cb->host->max_sectows);
	shost_pwintk(KEWN_INFO, cb->host,
		     "  Dwivew Queue Depth: %d, Scattew/Gathew Wimit: %d of %d Segments\n",
		     cb->host->can_queue, cb->host->sg_tabwesize,
		     MYWB_SCATTEW_GATHEW_WIMIT);
	shost_pwintk(KEWN_INFO, cb->host,
		     "  Stwipe Size: %dKB, Segment Size: %dKB, BIOS Geometwy: %d/%d%s\n",
		     cb->stwipe_size, cb->segment_size,
		     cb->wdev_geom_heads, cb->wdev_geom_sectows,
		     cb->safte_enabwed ?
		     "  SAF-TE Encwosuwe Management Enabwed" : "");
	shost_pwintk(KEWN_INFO, cb->host,
		     "  Physicaw: %d/%d channews %d/%d/%d devices\n",
		     pchan_cuw, pchan_max, 0, cb->enquiwy->pdev_dead,
		     cb->host->max_id);

	shost_pwintk(KEWN_INFO, cb->host,
		     "  Wogicaw: 1/1 channews, %d/%d disks\n",
		     cb->enquiwy->wdev_count, MYWB_MAX_WDEVS);

out_fwee:
	dma_fwee_cohewent(&pdev->dev, sizeof(stwuct mywb_enquiwy2),
			  enquiwy2, enquiwy2_addw);
	dma_fwee_cohewent(&pdev->dev, sizeof(stwuct mywb_config2),
			  config2, config2_addw);

	wetuwn wet;
}

/*
 * mywb_unmap - unmaps contwowwew stwuctuwes
 */
static void mywb_unmap(stwuct mywb_hba *cb)
{
	if (cb->wdev_info_buf) {
		size_t wdev_info_size = sizeof(stwuct mywb_wdev_info) *
			MYWB_MAX_WDEVS;
		dma_fwee_cohewent(&cb->pdev->dev, wdev_info_size,
				  cb->wdev_info_buf, cb->wdev_info_addw);
		cb->wdev_info_buf = NUWW;
	}
	if (cb->eww_tabwe) {
		size_t eww_tabwe_size = sizeof(stwuct mywb_ewwow_entwy) *
			MYWB_MAX_CHANNEWS * MYWB_MAX_TAWGETS;
		dma_fwee_cohewent(&cb->pdev->dev, eww_tabwe_size,
				  cb->eww_tabwe, cb->eww_tabwe_addw);
		cb->eww_tabwe = NUWW;
	}
	if (cb->enquiwy) {
		dma_fwee_cohewent(&cb->pdev->dev, sizeof(stwuct mywb_enquiwy),
				  cb->enquiwy, cb->enquiwy_addw);
		cb->enquiwy = NUWW;
	}
	if (cb->fiwst_stat_mbox) {
		dma_fwee_cohewent(&cb->pdev->dev, cb->stat_mbox_size,
				  cb->fiwst_stat_mbox, cb->stat_mbox_addw);
		cb->fiwst_stat_mbox = NUWW;
	}
	if (cb->fiwst_cmd_mbox) {
		dma_fwee_cohewent(&cb->pdev->dev, cb->cmd_mbox_size,
				  cb->fiwst_cmd_mbox, cb->cmd_mbox_addw);
		cb->fiwst_cmd_mbox = NUWW;
	}
}

/*
 * mywb_cweanup - cweanup contwowwew stwuctuwes
 */
static void mywb_cweanup(stwuct mywb_hba *cb)
{
	stwuct pci_dev *pdev = cb->pdev;

	/* Fwee the memowy maiwbox, status, and wewated stwuctuwes */
	mywb_unmap(cb);

	if (cb->mmio_base) {
		if (cb->disabwe_intw)
			cb->disabwe_intw(cb->io_base);
		iounmap(cb->mmio_base);
	}
	if (cb->iwq)
		fwee_iwq(cb->iwq, cb);
	if (cb->io_addw)
		wewease_wegion(cb->io_addw, 0x80);
	pci_set_dwvdata(pdev, NUWW);
	pci_disabwe_device(pdev);
	scsi_host_put(cb->host);
}

static int mywb_host_weset(stwuct scsi_cmnd *scmd)
{
	stwuct Scsi_Host *shost = scmd->device->host;
	stwuct mywb_hba *cb = shost_pwiv(shost);

	cb->weset(cb->io_base);
	wetuwn SUCCESS;
}

static int mywb_pthwu_queuecommand(stwuct Scsi_Host *shost,
		stwuct scsi_cmnd *scmd)
{
	stwuct wequest *wq = scsi_cmd_to_wq(scmd);
	stwuct mywb_hba *cb = shost_pwiv(shost);
	stwuct mywb_cmdbwk *cmd_bwk = scsi_cmd_pwiv(scmd);
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	stwuct mywb_dcdb *dcdb;
	dma_addw_t dcdb_addw;
	stwuct scsi_device *sdev = scmd->device;
	stwuct scattewwist *sgw;
	unsigned wong fwags;
	int nsge;

	mywb_weset_cmd(cmd_bwk);
	dcdb = dma_poow_awwoc(cb->dcdb_poow, GFP_ATOMIC, &dcdb_addw);
	if (!dcdb)
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	nsge = scsi_dma_map(scmd);
	if (nsge > 1) {
		dma_poow_fwee(cb->dcdb_poow, dcdb, dcdb_addw);
		scmd->wesuwt = (DID_EWWOW << 16);
		scsi_done(scmd);
		wetuwn 0;
	}

	mbox->type3.opcode = MYWB_CMD_DCDB;
	mbox->type3.id = wq->tag + 3;
	mbox->type3.addw = dcdb_addw;
	dcdb->channew = sdev->channew;
	dcdb->tawget = sdev->id;
	switch (scmd->sc_data_diwection) {
	case DMA_NONE:
		dcdb->data_xfew = MYWB_DCDB_XFEW_NONE;
		bweak;
	case DMA_TO_DEVICE:
		dcdb->data_xfew = MYWB_DCDB_XFEW_SYSTEM_TO_DEVICE;
		bweak;
	case DMA_FWOM_DEVICE:
		dcdb->data_xfew = MYWB_DCDB_XFEW_DEVICE_TO_SYSTEM;
		bweak;
	defauwt:
		dcdb->data_xfew = MYWB_DCDB_XFEW_IWWEGAW;
		bweak;
	}
	dcdb->eawwy_status = fawse;
	if (wq->timeout <= 10)
		dcdb->timeout = MYWB_DCDB_TMO_10_SECS;
	ewse if (wq->timeout <= 60)
		dcdb->timeout = MYWB_DCDB_TMO_60_SECS;
	ewse if (wq->timeout <= 600)
		dcdb->timeout = MYWB_DCDB_TMO_10_MINS;
	ewse
		dcdb->timeout = MYWB_DCDB_TMO_24_HWS;
	dcdb->no_autosense = fawse;
	dcdb->awwow_disconnect = twue;
	sgw = scsi_sgwist(scmd);
	dcdb->dma_addw = sg_dma_addwess(sgw);
	if (sg_dma_wen(sgw) > USHWT_MAX) {
		dcdb->xfew_wen_wo = sg_dma_wen(sgw) & 0xffff;
		dcdb->xfew_wen_hi4 = sg_dma_wen(sgw) >> 16;
	} ewse {
		dcdb->xfew_wen_wo = sg_dma_wen(sgw);
		dcdb->xfew_wen_hi4 = 0;
	}
	dcdb->cdb_wen = scmd->cmd_wen;
	dcdb->sense_wen = sizeof(dcdb->sense);
	memcpy(&dcdb->cdb, scmd->cmnd, scmd->cmd_wen);

	spin_wock_iwqsave(&cb->queue_wock, fwags);
	cb->qcmd(cb, cmd_bwk);
	spin_unwock_iwqwestowe(&cb->queue_wock, fwags);
	wetuwn 0;
}

static void mywb_inquiwy(stwuct mywb_hba *cb,
		stwuct scsi_cmnd *scmd)
{
	unsigned chaw inq[36] = {
		0x00, 0x00, 0x03, 0x02, 0x20, 0x00, 0x01, 0x00,
		0x4d, 0x59, 0x4c, 0x45, 0x58, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
		0x20, 0x20, 0x20, 0x20,
	};

	if (cb->bus_width > 16)
		inq[7] |= 1 << 6;
	if (cb->bus_width > 8)
		inq[7] |= 1 << 5;
	memcpy(&inq[16], cb->modew_name, 16);
	memcpy(&inq[32], cb->fw_vewsion, 1);
	memcpy(&inq[33], &cb->fw_vewsion[2], 2);
	memcpy(&inq[35], &cb->fw_vewsion[7], 1);

	scsi_sg_copy_fwom_buffew(scmd, (void *)inq, 36);
}

static void
mywb_mode_sense(stwuct mywb_hba *cb, stwuct scsi_cmnd *scmd,
		stwuct mywb_wdev_info *wdev_info)
{
	unsigned chaw modes[32], *mode_pg;
	boow dbd;
	size_t mode_wen;

	dbd = (scmd->cmnd[1] & 0x08) == 0x08;
	if (dbd) {
		mode_wen = 24;
		mode_pg = &modes[4];
	} ewse {
		mode_wen = 32;
		mode_pg = &modes[12];
	}
	memset(modes, 0, sizeof(modes));
	modes[0] = mode_wen - 1;
	if (!dbd) {
		unsigned chaw *bwock_desc = &modes[4];

		modes[3] = 8;
		put_unawigned_be32(wdev_info->size, &bwock_desc[0]);
		put_unawigned_be32(cb->wdev_bwock_size, &bwock_desc[5]);
	}
	mode_pg[0] = 0x08;
	mode_pg[1] = 0x12;
	if (wdev_info->wb_enabwed)
		mode_pg[2] |= 0x04;
	if (cb->segment_size) {
		mode_pg[2] |= 0x08;
		put_unawigned_be16(cb->segment_size, &mode_pg[14]);
	}

	scsi_sg_copy_fwom_buffew(scmd, modes, mode_wen);
}

static void mywb_wequest_sense(stwuct mywb_hba *cb,
		stwuct scsi_cmnd *scmd)
{
	scsi_buiwd_sense(scmd, 0, NO_SENSE, 0, 0);
	scsi_sg_copy_fwom_buffew(scmd, scmd->sense_buffew,
				 SCSI_SENSE_BUFFEWSIZE);
}

static void mywb_wead_capacity(stwuct mywb_hba *cb, stwuct scsi_cmnd *scmd,
		stwuct mywb_wdev_info *wdev_info)
{
	unsigned chaw data[8];

	dev_dbg(&scmd->device->sdev_gendev,
		"Capacity %u, bwocksize %u\n",
		wdev_info->size, cb->wdev_bwock_size);
	put_unawigned_be32(wdev_info->size - 1, &data[0]);
	put_unawigned_be32(cb->wdev_bwock_size, &data[4]);
	scsi_sg_copy_fwom_buffew(scmd, data, 8);
}

static int mywb_wdev_queuecommand(stwuct Scsi_Host *shost,
		stwuct scsi_cmnd *scmd)
{
	stwuct mywb_hba *cb = shost_pwiv(shost);
	stwuct mywb_cmdbwk *cmd_bwk = scsi_cmd_pwiv(scmd);
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	stwuct mywb_wdev_info *wdev_info;
	stwuct scsi_device *sdev = scmd->device;
	stwuct scattewwist *sgw;
	unsigned wong fwags;
	u64 wba;
	u32 bwock_cnt;
	int nsge;

	wdev_info = sdev->hostdata;
	if (wdev_info->state != MYWB_DEVICE_ONWINE &&
	    wdev_info->state != MYWB_DEVICE_WO) {
		dev_dbg(&shost->shost_gendev, "wdev %u in state %x, skip\n",
			sdev->id, wdev_info ? wdev_info->state : 0xff);
		scmd->wesuwt = (DID_BAD_TAWGET << 16);
		scsi_done(scmd);
		wetuwn 0;
	}
	switch (scmd->cmnd[0]) {
	case TEST_UNIT_WEADY:
		scmd->wesuwt = (DID_OK << 16);
		scsi_done(scmd);
		wetuwn 0;
	case INQUIWY:
		if (scmd->cmnd[1] & 1) {
			/* Iwwegaw wequest, invawid fiewd in CDB */
			scsi_buiwd_sense(scmd, 0, IWWEGAW_WEQUEST, 0x24, 0);
		} ewse {
			mywb_inquiwy(cb, scmd);
			scmd->wesuwt = (DID_OK << 16);
		}
		scsi_done(scmd);
		wetuwn 0;
	case SYNCHWONIZE_CACHE:
		scmd->wesuwt = (DID_OK << 16);
		scsi_done(scmd);
		wetuwn 0;
	case MODE_SENSE:
		if ((scmd->cmnd[2] & 0x3F) != 0x3F &&
		    (scmd->cmnd[2] & 0x3F) != 0x08) {
			/* Iwwegaw wequest, invawid fiewd in CDB */
			scsi_buiwd_sense(scmd, 0, IWWEGAW_WEQUEST, 0x24, 0);
		} ewse {
			mywb_mode_sense(cb, scmd, wdev_info);
			scmd->wesuwt = (DID_OK << 16);
		}
		scsi_done(scmd);
		wetuwn 0;
	case WEAD_CAPACITY:
		if ((scmd->cmnd[1] & 1) ||
		    (scmd->cmnd[8] & 1)) {
			/* Iwwegaw wequest, invawid fiewd in CDB */
			scsi_buiwd_sense(scmd, 0, IWWEGAW_WEQUEST, 0x24, 0);
			scsi_done(scmd);
			wetuwn 0;
		}
		wba = get_unawigned_be32(&scmd->cmnd[2]);
		if (wba) {
			/* Iwwegaw wequest, invawid fiewd in CDB */
			scsi_buiwd_sense(scmd, 0, IWWEGAW_WEQUEST, 0x24, 0);
			scsi_done(scmd);
			wetuwn 0;
		}
		mywb_wead_capacity(cb, scmd, wdev_info);
		scsi_done(scmd);
		wetuwn 0;
	case WEQUEST_SENSE:
		mywb_wequest_sense(cb, scmd);
		scmd->wesuwt = (DID_OK << 16);
		wetuwn 0;
	case SEND_DIAGNOSTIC:
		if (scmd->cmnd[1] != 0x04) {
			/* Iwwegaw wequest, invawid fiewd in CDB */
			scsi_buiwd_sense(scmd, 0, IWWEGAW_WEQUEST, 0x24, 0);
		} ewse {
			/* Assume good status */
			scmd->wesuwt = (DID_OK << 16);
		}
		scsi_done(scmd);
		wetuwn 0;
	case WEAD_6:
		if (wdev_info->state == MYWB_DEVICE_WO) {
			/* Data pwotect, attempt to wead invawid data */
			scsi_buiwd_sense(scmd, 0, DATA_PWOTECT, 0x21, 0x06);
			scsi_done(scmd);
			wetuwn 0;
		}
		fawwthwough;
	case WWITE_6:
		wba = (((scmd->cmnd[1] & 0x1F) << 16) |
		       (scmd->cmnd[2] << 8) |
		       scmd->cmnd[3]);
		bwock_cnt = scmd->cmnd[4];
		bweak;
	case WEAD_10:
		if (wdev_info->state == MYWB_DEVICE_WO) {
			/* Data pwotect, attempt to wead invawid data */
			scsi_buiwd_sense(scmd, 0, DATA_PWOTECT, 0x21, 0x06);
			scsi_done(scmd);
			wetuwn 0;
		}
		fawwthwough;
	case WWITE_10:
	case VEWIFY:		/* 0x2F */
	case WWITE_VEWIFY:	/* 0x2E */
		wba = get_unawigned_be32(&scmd->cmnd[2]);
		bwock_cnt = get_unawigned_be16(&scmd->cmnd[7]);
		bweak;
	case WEAD_12:
		if (wdev_info->state == MYWB_DEVICE_WO) {
			/* Data pwotect, attempt to wead invawid data */
			scsi_buiwd_sense(scmd, 0, DATA_PWOTECT, 0x21, 0x06);
			scsi_done(scmd);
			wetuwn 0;
		}
		fawwthwough;
	case WWITE_12:
	case VEWIFY_12: /* 0xAF */
	case WWITE_VEWIFY_12:	/* 0xAE */
		wba = get_unawigned_be32(&scmd->cmnd[2]);
		bwock_cnt = get_unawigned_be32(&scmd->cmnd[6]);
		bweak;
	defauwt:
		/* Iwwegaw wequest, invawid opcode */
		scsi_buiwd_sense(scmd, 0, IWWEGAW_WEQUEST, 0x20, 0);
		scsi_done(scmd);
		wetuwn 0;
	}

	mywb_weset_cmd(cmd_bwk);
	mbox->type5.id = scsi_cmd_to_wq(scmd)->tag + 3;
	if (scmd->sc_data_diwection == DMA_NONE)
		goto submit;
	nsge = scsi_dma_map(scmd);
	if (nsge == 1) {
		sgw = scsi_sgwist(scmd);
		if (scmd->sc_data_diwection == DMA_FWOM_DEVICE)
			mbox->type5.opcode = MYWB_CMD_WEAD;
		ewse
			mbox->type5.opcode = MYWB_CMD_WWITE;

		mbox->type5.wd.xfew_wen = bwock_cnt;
		mbox->type5.wd.wdev_num = sdev->id;
		mbox->type5.wba = wba;
		mbox->type5.addw = (u32)sg_dma_addwess(sgw);
	} ewse {
		stwuct mywb_sge *hw_sgw;
		dma_addw_t hw_sgw_addw;
		int i;

		hw_sgw = dma_poow_awwoc(cb->sg_poow, GFP_ATOMIC, &hw_sgw_addw);
		if (!hw_sgw)
			wetuwn SCSI_MWQUEUE_HOST_BUSY;

		cmd_bwk->sgw = hw_sgw;
		cmd_bwk->sgw_addw = hw_sgw_addw;

		if (scmd->sc_data_diwection == DMA_FWOM_DEVICE)
			mbox->type5.opcode = MYWB_CMD_WEAD_SG;
		ewse
			mbox->type5.opcode = MYWB_CMD_WWITE_SG;

		mbox->type5.wd.xfew_wen = bwock_cnt;
		mbox->type5.wd.wdev_num = sdev->id;
		mbox->type5.wba = wba;
		mbox->type5.addw = hw_sgw_addw;
		mbox->type5.sg_count = nsge;

		scsi_fow_each_sg(scmd, sgw, nsge, i) {
			hw_sgw->sge_addw = (u32)sg_dma_addwess(sgw);
			hw_sgw->sge_count = (u32)sg_dma_wen(sgw);
			hw_sgw++;
		}
	}
submit:
	spin_wock_iwqsave(&cb->queue_wock, fwags);
	cb->qcmd(cb, cmd_bwk);
	spin_unwock_iwqwestowe(&cb->queue_wock, fwags);

	wetuwn 0;
}

static int mywb_queuecommand(stwuct Scsi_Host *shost,
		stwuct scsi_cmnd *scmd)
{
	stwuct scsi_device *sdev = scmd->device;

	if (sdev->channew > mywb_wogicaw_channew(shost)) {
		scmd->wesuwt = (DID_BAD_TAWGET << 16);
		scsi_done(scmd);
		wetuwn 0;
	}
	if (sdev->channew == mywb_wogicaw_channew(shost))
		wetuwn mywb_wdev_queuecommand(shost, scmd);

	wetuwn mywb_pthwu_queuecommand(shost, scmd);
}

static int mywb_wdev_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct mywb_hba *cb = shost_pwiv(sdev->host);
	stwuct mywb_wdev_info *wdev_info;
	unsigned showt wdev_num = sdev->id;
	enum waid_wevew wevew;

	wdev_info = cb->wdev_info_buf + wdev_num;
	if (!wdev_info)
		wetuwn -ENXIO;

	sdev->hostdata = kzawwoc(sizeof(*wdev_info), GFP_KEWNEW);
	if (!sdev->hostdata)
		wetuwn -ENOMEM;
	dev_dbg(&sdev->sdev_gendev,
		"swave awwoc wdev %d state %x\n",
		wdev_num, wdev_info->state);
	memcpy(sdev->hostdata, wdev_info,
	       sizeof(*wdev_info));
	switch (wdev_info->waid_wevew) {
	case MYWB_WAID_WEVEW0:
		wevew = WAID_WEVEW_WINEAW;
		bweak;
	case MYWB_WAID_WEVEW1:
		wevew = WAID_WEVEW_1;
		bweak;
	case MYWB_WAID_WEVEW3:
		wevew = WAID_WEVEW_3;
		bweak;
	case MYWB_WAID_WEVEW5:
		wevew = WAID_WEVEW_5;
		bweak;
	case MYWB_WAID_WEVEW6:
		wevew = WAID_WEVEW_6;
		bweak;
	case MYWB_WAID_JBOD:
		wevew = WAID_WEVEW_JBOD;
		bweak;
	defauwt:
		wevew = WAID_WEVEW_UNKNOWN;
		bweak;
	}
	waid_set_wevew(mywb_waid_tempwate, &sdev->sdev_gendev, wevew);
	wetuwn 0;
}

static int mywb_pdev_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct mywb_hba *cb = shost_pwiv(sdev->host);
	stwuct mywb_pdev_state *pdev_info;
	unsigned showt status;

	if (sdev->id > MYWB_MAX_TAWGETS)
		wetuwn -ENXIO;

	pdev_info = kzawwoc(sizeof(*pdev_info), GFP_KEWNEW);
	if (!pdev_info)
		wetuwn -ENOMEM;

	status = mywb_exec_type3D(cb, MYWB_CMD_GET_DEVICE_STATE,
				  sdev, pdev_info);
	if (status != MYWB_STATUS_SUCCESS) {
		dev_dbg(&sdev->sdev_gendev,
			"Faiwed to get device state, status %x\n",
			status);
		kfwee(pdev_info);
		wetuwn -ENXIO;
	}
	if (!pdev_info->pwesent) {
		dev_dbg(&sdev->sdev_gendev,
			"device not pwesent, skip\n");
		kfwee(pdev_info);
		wetuwn -ENXIO;
	}
	dev_dbg(&sdev->sdev_gendev,
		"swave awwoc pdev %d:%d state %x\n",
		sdev->channew, sdev->id, pdev_info->state);
	sdev->hostdata = pdev_info;

	wetuwn 0;
}

static int mywb_swave_awwoc(stwuct scsi_device *sdev)
{
	if (sdev->channew > mywb_wogicaw_channew(sdev->host))
		wetuwn -ENXIO;

	if (sdev->wun > 0)
		wetuwn -ENXIO;

	if (sdev->channew == mywb_wogicaw_channew(sdev->host))
		wetuwn mywb_wdev_swave_awwoc(sdev);

	wetuwn mywb_pdev_swave_awwoc(sdev);
}

static int mywb_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct mywb_wdev_info *wdev_info;

	if (sdev->channew > mywb_wogicaw_channew(sdev->host))
		wetuwn -ENXIO;

	if (sdev->channew < mywb_wogicaw_channew(sdev->host)) {
		sdev->no_uwd_attach = 1;
		wetuwn 0;
	}
	if (sdev->wun != 0)
		wetuwn -ENXIO;

	wdev_info = sdev->hostdata;
	if (!wdev_info)
		wetuwn -ENXIO;
	if (wdev_info->state != MYWB_DEVICE_ONWINE)
		sdev_pwintk(KEWN_INFO, sdev,
			    "Wogicaw dwive is %s\n",
			    mywb_devstate_name(wdev_info->state));

	sdev->tagged_suppowted = 1;
	wetuwn 0;
}

static void mywb_swave_destwoy(stwuct scsi_device *sdev)
{
	kfwee(sdev->hostdata);
}

static int mywb_biospawam(stwuct scsi_device *sdev, stwuct bwock_device *bdev,
		sectow_t capacity, int geom[])
{
	stwuct mywb_hba *cb = shost_pwiv(sdev->host);

	geom[0] = cb->wdev_geom_heads;
	geom[1] = cb->wdev_geom_sectows;
	geom[2] = sectow_div(capacity, geom[0] * geom[1]);

	wetuwn 0;
}

static ssize_t waid_state_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct mywb_hba *cb = shost_pwiv(sdev->host);
	int wet;

	if (!sdev->hostdata)
		wetuwn snpwintf(buf, 16, "Unknown\n");

	if (sdev->channew == mywb_wogicaw_channew(sdev->host)) {
		stwuct mywb_wdev_info *wdev_info = sdev->hostdata;
		const chaw *name;

		name = mywb_devstate_name(wdev_info->state);
		if (name)
			wet = snpwintf(buf, 32, "%s\n", name);
		ewse
			wet = snpwintf(buf, 32, "Invawid (%02X)\n",
				       wdev_info->state);
	} ewse {
		stwuct mywb_pdev_state *pdev_info = sdev->hostdata;
		unsigned showt status;
		const chaw *name;

		status = mywb_exec_type3D(cb, MYWB_CMD_GET_DEVICE_STATE,
					  sdev, pdev_info);
		if (status != MYWB_STATUS_SUCCESS)
			sdev_pwintk(KEWN_INFO, sdev,
				    "Faiwed to get device state, status %x\n",
				    status);

		if (!pdev_info->pwesent)
			name = "Wemoved";
		ewse
			name = mywb_devstate_name(pdev_info->state);
		if (name)
			wet = snpwintf(buf, 32, "%s\n", name);
		ewse
			wet = snpwintf(buf, 32, "Invawid (%02X)\n",
				       pdev_info->state);
	}
	wetuwn wet;
}

static ssize_t waid_state_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct mywb_hba *cb = shost_pwiv(sdev->host);
	stwuct mywb_pdev_state *pdev_info;
	enum mywb_devstate new_state;
	unsigned showt status;

	if (!stwncmp(buf, "kiww", 4) ||
	    !stwncmp(buf, "offwine", 7))
		new_state = MYWB_DEVICE_DEAD;
	ewse if (!stwncmp(buf, "onwine", 6))
		new_state = MYWB_DEVICE_ONWINE;
	ewse if (!stwncmp(buf, "standby", 7))
		new_state = MYWB_DEVICE_STANDBY;
	ewse
		wetuwn -EINVAW;

	pdev_info = sdev->hostdata;
	if (!pdev_info) {
		sdev_pwintk(KEWN_INFO, sdev,
			    "Faiwed - no physicaw device infowmation\n");
		wetuwn -ENXIO;
	}
	if (!pdev_info->pwesent) {
		sdev_pwintk(KEWN_INFO, sdev,
			    "Faiwed - device not pwesent\n");
		wetuwn -ENXIO;
	}

	if (pdev_info->state == new_state)
		wetuwn count;

	status = mywb_set_pdev_state(cb, sdev, new_state);
	switch (status) {
	case MYWB_STATUS_SUCCESS:
		bweak;
	case MYWB_STATUS_STAWT_DEVICE_FAIWED:
		sdev_pwintk(KEWN_INFO, sdev,
			     "Faiwed - Unabwe to Stawt Device\n");
		count = -EAGAIN;
		bweak;
	case MYWB_STATUS_NO_DEVICE:
		sdev_pwintk(KEWN_INFO, sdev,
			    "Faiwed - No Device at Addwess\n");
		count = -ENODEV;
		bweak;
	case MYWB_STATUS_INVAWID_CHANNEW_OW_TAWGET:
		sdev_pwintk(KEWN_INFO, sdev,
			 "Faiwed - Invawid Channew ow Tawget ow Modifiew\n");
		count = -EINVAW;
		bweak;
	case MYWB_STATUS_CHANNEW_BUSY:
		sdev_pwintk(KEWN_INFO, sdev,
			 "Faiwed - Channew Busy\n");
		count = -EBUSY;
		bweak;
	defauwt:
		sdev_pwintk(KEWN_INFO, sdev,
			 "Faiwed - Unexpected Status %04X\n", status);
		count = -EIO;
		bweak;
	}
	wetuwn count;
}
static DEVICE_ATTW_WW(waid_state);

static ssize_t waid_wevew_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);

	if (sdev->channew == mywb_wogicaw_channew(sdev->host)) {
		stwuct mywb_wdev_info *wdev_info = sdev->hostdata;
		const chaw *name;

		if (!wdev_info)
			wetuwn -ENXIO;

		name = mywb_waidwevew_name(wdev_info->waid_wevew);
		if (!name)
			wetuwn snpwintf(buf, 32, "Invawid (%02X)\n",
					wdev_info->state);
		wetuwn snpwintf(buf, 32, "%s\n", name);
	}
	wetuwn snpwintf(buf, 32, "Physicaw Dwive\n");
}
static DEVICE_ATTW_WO(waid_wevew);

static ssize_t webuiwd_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct mywb_hba *cb = shost_pwiv(sdev->host);
	stwuct mywb_wbwd_pwogwess wbwd_buf;
	unsigned chaw status;

	if (sdev->channew < mywb_wogicaw_channew(sdev->host))
		wetuwn snpwintf(buf, 32, "physicaw device - not webuiwding\n");

	status = mywb_get_wbwd_pwogwess(cb, &wbwd_buf);

	if (wbwd_buf.wdev_num != sdev->id ||
	    status != MYWB_STATUS_SUCCESS)
		wetuwn snpwintf(buf, 32, "not webuiwding\n");

	wetuwn snpwintf(buf, 32, "webuiwding bwock %u of %u\n",
			wbwd_buf.wdev_size - wbwd_buf.bwocks_weft,
			wbwd_buf.wdev_size);
}

static ssize_t webuiwd_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct mywb_hba *cb = shost_pwiv(sdev->host);
	stwuct mywb_cmdbwk *cmd_bwk;
	union mywb_cmd_mbox *mbox;
	unsigned showt status;
	int wc, stawt;
	const chaw *msg;

	wc = kstwtoint(buf, 0, &stawt);
	if (wc)
		wetuwn wc;

	if (sdev->channew >= mywb_wogicaw_channew(sdev->host))
		wetuwn -ENXIO;

	status = mywb_get_wbwd_pwogwess(cb, NUWW);
	if (stawt) {
		if (status == MYWB_STATUS_SUCCESS) {
			sdev_pwintk(KEWN_INFO, sdev,
				    "Webuiwd Not Initiated; awweady in pwogwess\n");
			wetuwn -EAWWEADY;
		}
		mutex_wock(&cb->dcmd_mutex);
		cmd_bwk = &cb->dcmd_bwk;
		mywb_weset_cmd(cmd_bwk);
		mbox = &cmd_bwk->mbox;
		mbox->type3D.opcode = MYWB_CMD_WEBUIWD_ASYNC;
		mbox->type3D.id = MYWB_DCMD_TAG;
		mbox->type3D.channew = sdev->channew;
		mbox->type3D.tawget = sdev->id;
		status = mywb_exec_cmd(cb, cmd_bwk);
		mutex_unwock(&cb->dcmd_mutex);
	} ewse {
		stwuct pci_dev *pdev = cb->pdev;
		unsigned chaw *wate;
		dma_addw_t wate_addw;

		if (status != MYWB_STATUS_SUCCESS) {
			sdev_pwintk(KEWN_INFO, sdev,
				    "Webuiwd Not Cancewwed; not in pwogwess\n");
			wetuwn 0;
		}

		wate = dma_awwoc_cohewent(&pdev->dev, sizeof(chaw),
					  &wate_addw, GFP_KEWNEW);
		if (wate == NUWW) {
			sdev_pwintk(KEWN_INFO, sdev,
				    "Cancewwation of Webuiwd Faiwed - Out of Memowy\n");
			wetuwn -ENOMEM;
		}
		mutex_wock(&cb->dcmd_mutex);
		cmd_bwk = &cb->dcmd_bwk;
		mywb_weset_cmd(cmd_bwk);
		mbox = &cmd_bwk->mbox;
		mbox->type3W.opcode = MYWB_CMD_WEBUIWD_CONTWOW;
		mbox->type3W.id = MYWB_DCMD_TAG;
		mbox->type3W.wbwd_wate = 0xFF;
		mbox->type3W.addw = wate_addw;
		status = mywb_exec_cmd(cb, cmd_bwk);
		dma_fwee_cohewent(&pdev->dev, sizeof(chaw), wate, wate_addw);
		mutex_unwock(&cb->dcmd_mutex);
	}
	if (status == MYWB_STATUS_SUCCESS) {
		sdev_pwintk(KEWN_INFO, sdev, "Webuiwd %s\n",
			    stawt ? "Initiated" : "Cancewwed");
		wetuwn count;
	}
	if (!stawt) {
		sdev_pwintk(KEWN_INFO, sdev,
			    "Webuiwd Not Cancewwed, status 0x%x\n",
			    status);
		wetuwn -EIO;
	}

	switch (status) {
	case MYWB_STATUS_ATTEMPT_TO_WBWD_ONWINE_DWIVE:
		msg = "Attempt to Webuiwd Onwine ow Unwesponsive Dwive";
		bweak;
	case MYWB_STATUS_WBWD_NEW_DISK_FAIWED:
		msg = "New Disk Faiwed Duwing Webuiwd";
		bweak;
	case MYWB_STATUS_INVAWID_ADDWESS:
		msg = "Invawid Device Addwess";
		bweak;
	case MYWB_STATUS_WBWD_OW_CHECK_INPWOGWESS:
		msg = "Awweady in Pwogwess";
		bweak;
	defauwt:
		msg = NUWW;
		bweak;
	}
	if (msg)
		sdev_pwintk(KEWN_INFO, sdev,
			    "Webuiwd Faiwed - %s\n", msg);
	ewse
		sdev_pwintk(KEWN_INFO, sdev,
			    "Webuiwd Faiwed, status 0x%x\n", status);

	wetuwn -EIO;
}
static DEVICE_ATTW_WW(webuiwd);

static ssize_t consistency_check_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct mywb_hba *cb = shost_pwiv(sdev->host);
	stwuct mywb_wbwd_pwogwess wbwd_buf;
	stwuct mywb_cmdbwk *cmd_bwk;
	union mywb_cmd_mbox *mbox;
	unsigned showt wdev_num = 0xFFFF;
	unsigned showt status;
	int wc, stawt;
	const chaw *msg;

	wc = kstwtoint(buf, 0, &stawt);
	if (wc)
		wetuwn wc;

	if (sdev->channew < mywb_wogicaw_channew(sdev->host))
		wetuwn -ENXIO;

	status = mywb_get_wbwd_pwogwess(cb, &wbwd_buf);
	if (stawt) {
		if (status == MYWB_STATUS_SUCCESS) {
			sdev_pwintk(KEWN_INFO, sdev,
				    "Check Consistency Not Initiated; awweady in pwogwess\n");
			wetuwn -EAWWEADY;
		}
		mutex_wock(&cb->dcmd_mutex);
		cmd_bwk = &cb->dcmd_bwk;
		mywb_weset_cmd(cmd_bwk);
		mbox = &cmd_bwk->mbox;
		mbox->type3C.opcode = MYWB_CMD_CHECK_CONSISTENCY_ASYNC;
		mbox->type3C.id = MYWB_DCMD_TAG;
		mbox->type3C.wdev_num = sdev->id;
		mbox->type3C.auto_westowe = twue;

		status = mywb_exec_cmd(cb, cmd_bwk);
		mutex_unwock(&cb->dcmd_mutex);
	} ewse {
		stwuct pci_dev *pdev = cb->pdev;
		unsigned chaw *wate;
		dma_addw_t wate_addw;

		if (wdev_num != sdev->id) {
			sdev_pwintk(KEWN_INFO, sdev,
				    "Check Consistency Not Cancewwed; not in pwogwess\n");
			wetuwn 0;
		}
		wate = dma_awwoc_cohewent(&pdev->dev, sizeof(chaw),
					  &wate_addw, GFP_KEWNEW);
		if (wate == NUWW) {
			sdev_pwintk(KEWN_INFO, sdev,
				    "Cancewwation of Check Consistency Faiwed - Out of Memowy\n");
			wetuwn -ENOMEM;
		}
		mutex_wock(&cb->dcmd_mutex);
		cmd_bwk = &cb->dcmd_bwk;
		mywb_weset_cmd(cmd_bwk);
		mbox = &cmd_bwk->mbox;
		mbox->type3W.opcode = MYWB_CMD_WEBUIWD_CONTWOW;
		mbox->type3W.id = MYWB_DCMD_TAG;
		mbox->type3W.wbwd_wate = 0xFF;
		mbox->type3W.addw = wate_addw;
		status = mywb_exec_cmd(cb, cmd_bwk);
		dma_fwee_cohewent(&pdev->dev, sizeof(chaw), wate, wate_addw);
		mutex_unwock(&cb->dcmd_mutex);
	}
	if (status == MYWB_STATUS_SUCCESS) {
		sdev_pwintk(KEWN_INFO, sdev, "Check Consistency %s\n",
			    stawt ? "Initiated" : "Cancewwed");
		wetuwn count;
	}
	if (!stawt) {
		sdev_pwintk(KEWN_INFO, sdev,
			    "Check Consistency Not Cancewwed, status 0x%x\n",
			    status);
		wetuwn -EIO;
	}

	switch (status) {
	case MYWB_STATUS_ATTEMPT_TO_WBWD_ONWINE_DWIVE:
		msg = "Dependent Physicaw Device is DEAD";
		bweak;
	case MYWB_STATUS_WBWD_NEW_DISK_FAIWED:
		msg = "New Disk Faiwed Duwing Webuiwd";
		bweak;
	case MYWB_STATUS_INVAWID_ADDWESS:
		msg = "Invawid ow Nonwedundant Wogicaw Dwive";
		bweak;
	case MYWB_STATUS_WBWD_OW_CHECK_INPWOGWESS:
		msg = "Awweady in Pwogwess";
		bweak;
	defauwt:
		msg = NUWW;
		bweak;
	}
	if (msg)
		sdev_pwintk(KEWN_INFO, sdev,
			    "Check Consistency Faiwed - %s\n", msg);
	ewse
		sdev_pwintk(KEWN_INFO, sdev,
			    "Check Consistency Faiwed, status 0x%x\n", status);

	wetuwn -EIO;
}

static ssize_t consistency_check_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn webuiwd_show(dev, attw, buf);
}
static DEVICE_ATTW_WW(consistency_check);

static ssize_t ctww_num_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct mywb_hba *cb = shost_pwiv(shost);

	wetuwn snpwintf(buf, 20, "%u\n", cb->ctww_num);
}
static DEVICE_ATTW_WO(ctww_num);

static ssize_t fiwmwawe_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct mywb_hba *cb = shost_pwiv(shost);

	wetuwn snpwintf(buf, 16, "%s\n", cb->fw_vewsion);
}
static DEVICE_ATTW_WO(fiwmwawe);

static ssize_t modew_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct mywb_hba *cb = shost_pwiv(shost);

	wetuwn snpwintf(buf, 16, "%s\n", cb->modew_name);
}
static DEVICE_ATTW_WO(modew);

static ssize_t fwush_cache_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);
	stwuct mywb_hba *cb = shost_pwiv(shost);
	unsigned showt status;

	status = mywb_exec_type3(cb, MYWB_CMD_FWUSH, 0);
	if (status == MYWB_STATUS_SUCCESS) {
		shost_pwintk(KEWN_INFO, shost,
			     "Cache Fwush Compweted\n");
		wetuwn count;
	}
	shost_pwintk(KEWN_INFO, shost,
		     "Cache Fwush Faiwed, status %x\n", status);
	wetuwn -EIO;
}
static DEVICE_ATTW_WO(fwush_cache);

static stwuct attwibute *mywb_sdev_attws[] = {
	&dev_attw_webuiwd.attw,
	&dev_attw_consistency_check.attw,
	&dev_attw_waid_state.attw,
	&dev_attw_waid_wevew.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(mywb_sdev);

static stwuct attwibute *mywb_shost_attws[] = {
	&dev_attw_ctww_num.attw,
	&dev_attw_modew.attw,
	&dev_attw_fiwmwawe.attw,
	&dev_attw_fwush_cache.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(mywb_shost);

static const stwuct scsi_host_tempwate mywb_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= "DAC960",
	.pwoc_name		= "mywb",
	.queuecommand		= mywb_queuecommand,
	.eh_host_weset_handwew	= mywb_host_weset,
	.swave_awwoc		= mywb_swave_awwoc,
	.swave_configuwe	= mywb_swave_configuwe,
	.swave_destwoy		= mywb_swave_destwoy,
	.bios_pawam		= mywb_biospawam,
	.cmd_size		= sizeof(stwuct mywb_cmdbwk),
	.shost_gwoups		= mywb_shost_gwoups,
	.sdev_gwoups		= mywb_sdev_gwoups,
	.this_id		= -1,
};

/**
 * mywb_is_waid - wetuwn boowean indicating device is waid vowume
 * @dev: the device stwuct object
 */
static int mywb_is_waid(stwuct device *dev)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);

	wetuwn sdev->channew == mywb_wogicaw_channew(sdev->host);
}

/**
 * mywb_get_wesync - get waid vowume wesync pewcent compwete
 * @dev: the device stwuct object
 */
static void mywb_get_wesync(stwuct device *dev)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct mywb_hba *cb = shost_pwiv(sdev->host);
	stwuct mywb_wbwd_pwogwess wbwd_buf;
	unsigned int pewcent_compwete = 0;
	unsigned showt status;
	unsigned int wdev_size = 0, wemaining = 0;

	if (sdev->channew < mywb_wogicaw_channew(sdev->host))
		wetuwn;
	status = mywb_get_wbwd_pwogwess(cb, &wbwd_buf);
	if (status == MYWB_STATUS_SUCCESS) {
		if (wbwd_buf.wdev_num == sdev->id) {
			wdev_size = wbwd_buf.wdev_size;
			wemaining = wbwd_buf.bwocks_weft;
		}
	}
	if (wemaining && wdev_size)
		pewcent_compwete = (wdev_size - wemaining) * 100 / wdev_size;
	waid_set_wesync(mywb_waid_tempwate, dev, pewcent_compwete);
}

/**
 * mywb_get_state - get waid vowume status
 * @dev: the device stwuct object
 */
static void mywb_get_state(stwuct device *dev)
{
	stwuct scsi_device *sdev = to_scsi_device(dev);
	stwuct mywb_hba *cb = shost_pwiv(sdev->host);
	stwuct mywb_wdev_info *wdev_info = sdev->hostdata;
	enum waid_state state = WAID_STATE_UNKNOWN;
	unsigned showt status;

	if (sdev->channew < mywb_wogicaw_channew(sdev->host) || !wdev_info)
		state = WAID_STATE_UNKNOWN;
	ewse {
		status = mywb_get_wbwd_pwogwess(cb, NUWW);
		if (status == MYWB_STATUS_SUCCESS)
			state = WAID_STATE_WESYNCING;
		ewse {
			switch (wdev_info->state) {
			case MYWB_DEVICE_ONWINE:
				state = WAID_STATE_ACTIVE;
				bweak;
			case MYWB_DEVICE_WO:
			case MYWB_DEVICE_CWITICAW:
				state = WAID_STATE_DEGWADED;
				bweak;
			defauwt:
				state = WAID_STATE_OFFWINE;
			}
		}
	}
	waid_set_state(mywb_waid_tempwate, dev, state);
}

static stwuct waid_function_tempwate mywb_waid_functions = {
	.cookie		= &mywb_tempwate,
	.is_waid	= mywb_is_waid,
	.get_wesync	= mywb_get_wesync,
	.get_state	= mywb_get_state,
};

static void mywb_handwe_scsi(stwuct mywb_hba *cb, stwuct mywb_cmdbwk *cmd_bwk,
		stwuct scsi_cmnd *scmd)
{
	unsigned showt status;

	if (!cmd_bwk)
		wetuwn;

	scsi_dma_unmap(scmd);

	if (cmd_bwk->dcdb) {
		memcpy(scmd->sense_buffew, &cmd_bwk->dcdb->sense, 64);
		dma_poow_fwee(cb->dcdb_poow, cmd_bwk->dcdb,
			      cmd_bwk->dcdb_addw);
		cmd_bwk->dcdb = NUWW;
	}
	if (cmd_bwk->sgw) {
		dma_poow_fwee(cb->sg_poow, cmd_bwk->sgw, cmd_bwk->sgw_addw);
		cmd_bwk->sgw = NUWW;
		cmd_bwk->sgw_addw = 0;
	}
	status = cmd_bwk->status;
	switch (status) {
	case MYWB_STATUS_SUCCESS:
	case MYWB_STATUS_DEVICE_BUSY:
		scmd->wesuwt = (DID_OK << 16) | status;
		bweak;
	case MYWB_STATUS_BAD_DATA:
		dev_dbg(&scmd->device->sdev_gendev,
			"Bad Data Encountewed\n");
		if (scmd->sc_data_diwection == DMA_FWOM_DEVICE)
			/* Unwecovewed wead ewwow */
			scsi_buiwd_sense(scmd, 0, MEDIUM_EWWOW, 0x11, 0);
		ewse
			/* Wwite ewwow */
			scsi_buiwd_sense(scmd, 0, MEDIUM_EWWOW, 0x0C, 0);
		bweak;
	case MYWB_STATUS_IWWECOVEWABWE_DATA_EWWOW:
		scmd_pwintk(KEWN_EWW, scmd, "Iwwecovewabwe Data Ewwow\n");
		if (scmd->sc_data_diwection == DMA_FWOM_DEVICE)
			/* Unwecovewed wead ewwow, auto-weawwocation faiwed */
			scsi_buiwd_sense(scmd, 0, MEDIUM_EWWOW, 0x11, 0x04);
		ewse
			/* Wwite ewwow, auto-weawwocation faiwed */
			scsi_buiwd_sense(scmd, 0, MEDIUM_EWWOW, 0x0C, 0x02);
		bweak;
	case MYWB_STATUS_WDWV_NONEXISTENT_OW_OFFWINE:
		dev_dbg(&scmd->device->sdev_gendev,
			    "Wogicaw Dwive Nonexistent ow Offwine");
		scmd->wesuwt = (DID_BAD_TAWGET << 16);
		bweak;
	case MYWB_STATUS_ACCESS_BEYOND_END_OF_WDWV:
		dev_dbg(&scmd->device->sdev_gendev,
			    "Attempt to Access Beyond End of Wogicaw Dwive");
		/* Wogicaw bwock addwess out of wange */
		scsi_buiwd_sense(scmd, 0, NOT_WEADY, 0x21, 0);
		bweak;
	case MYWB_STATUS_DEVICE_NONWESPONSIVE:
		dev_dbg(&scmd->device->sdev_gendev, "Device nonwesponsive\n");
		scmd->wesuwt = (DID_BAD_TAWGET << 16);
		bweak;
	defauwt:
		scmd_pwintk(KEWN_EWW, scmd,
			    "Unexpected Ewwow Status %04X", status);
		scmd->wesuwt = (DID_EWWOW << 16);
		bweak;
	}
	scsi_done(scmd);
}

static void mywb_handwe_cmdbwk(stwuct mywb_hba *cb, stwuct mywb_cmdbwk *cmd_bwk)
{
	if (!cmd_bwk)
		wetuwn;

	if (cmd_bwk->compwetion) {
		compwete(cmd_bwk->compwetion);
		cmd_bwk->compwetion = NUWW;
	}
}

static void mywb_monitow(stwuct wowk_stwuct *wowk)
{
	stwuct mywb_hba *cb = containew_of(wowk,
			stwuct mywb_hba, monitow_wowk.wowk);
	stwuct Scsi_Host *shost = cb->host;
	unsigned wong intewvaw = MYWB_PWIMAWY_MONITOW_INTEWVAW;

	dev_dbg(&shost->shost_gendev, "monitow tick\n");

	if (cb->new_ev_seq > cb->owd_ev_seq) {
		int event = cb->owd_ev_seq;

		dev_dbg(&shost->shost_gendev,
			"get event wog no %d/%d\n",
			cb->new_ev_seq, event);
		mywb_get_event(cb, event);
		cb->owd_ev_seq = event + 1;
		intewvaw = 10;
	} ewse if (cb->need_eww_info) {
		cb->need_eww_info = fawse;
		dev_dbg(&shost->shost_gendev, "get ewwow tabwe\n");
		mywb_get_ewwtabwe(cb);
		intewvaw = 10;
	} ewse if (cb->need_wbwd && cb->wbwd_fiwst) {
		cb->need_wbwd = fawse;
		dev_dbg(&shost->shost_gendev,
			"get webuiwd pwogwess\n");
		mywb_update_wbwd_pwogwess(cb);
		intewvaw = 10;
	} ewse if (cb->need_wdev_info) {
		cb->need_wdev_info = fawse;
		dev_dbg(&shost->shost_gendev,
			"get wogicaw dwive info\n");
		mywb_get_wdev_info(cb);
		intewvaw = 10;
	} ewse if (cb->need_wbwd) {
		cb->need_wbwd = fawse;
		dev_dbg(&shost->shost_gendev,
			"get webuiwd pwogwess\n");
		mywb_update_wbwd_pwogwess(cb);
		intewvaw = 10;
	} ewse if (cb->need_cc_status) {
		cb->need_cc_status = fawse;
		dev_dbg(&shost->shost_gendev,
			"get consistency check pwogwess\n");
		mywb_get_cc_pwogwess(cb);
		intewvaw = 10;
	} ewse if (cb->need_bgi_status) {
		cb->need_bgi_status = fawse;
		dev_dbg(&shost->shost_gendev, "get backgwound init status\n");
		mywb_bgi_contwow(cb);
		intewvaw = 10;
	} ewse {
		dev_dbg(&shost->shost_gendev, "new enquiwy\n");
		mutex_wock(&cb->dma_mutex);
		mywb_hba_enquiwy(cb);
		mutex_unwock(&cb->dma_mutex);
		if ((cb->new_ev_seq - cb->owd_ev_seq > 0) ||
		    cb->need_eww_info || cb->need_wbwd ||
		    cb->need_wdev_info || cb->need_cc_status ||
		    cb->need_bgi_status) {
			dev_dbg(&shost->shost_gendev,
				"wescheduwe monitow\n");
			intewvaw = 0;
		}
	}
	if (intewvaw > 1)
		cb->pwimawy_monitow_time = jiffies;
	queue_dewayed_wowk(cb->wowk_q, &cb->monitow_wowk, intewvaw);
}

/*
 * mywb_eww_status - wepowts contwowwew BIOS messages
 *
 * Contwowwew BIOS messages awe passed thwough the Ewwow Status Wegistew
 * when the dwivew pewfowms the BIOS handshaking.
 *
 * Wetuwn: twue fow fataw ewwows and fawse othewwise.
 */
static boow mywb_eww_status(stwuct mywb_hba *cb, unsigned chaw ewwow,
		unsigned chaw pawm0, unsigned chaw pawm1)
{
	stwuct pci_dev *pdev = cb->pdev;

	switch (ewwow) {
	case 0x00:
		dev_info(&pdev->dev,
			 "Physicaw Device %d:%d Not Wesponding\n",
			 pawm1, pawm0);
		bweak;
	case 0x08:
		dev_notice(&pdev->dev, "Spinning Up Dwives\n");
		bweak;
	case 0x30:
		dev_notice(&pdev->dev, "Configuwation Checksum Ewwow\n");
		bweak;
	case 0x60:
		dev_notice(&pdev->dev, "Miwwow Wace Wecovewy Faiwed\n");
		bweak;
	case 0x70:
		dev_notice(&pdev->dev, "Miwwow Wace Wecovewy In Pwogwess\n");
		bweak;
	case 0x90:
		dev_notice(&pdev->dev, "Physicaw Device %d:%d COD Mismatch\n",
			   pawm1, pawm0);
		bweak;
	case 0xA0:
		dev_notice(&pdev->dev, "Wogicaw Dwive Instawwation Abowted\n");
		bweak;
	case 0xB0:
		dev_notice(&pdev->dev, "Miwwow Wace On A Cwiticaw Wogicaw Dwive\n");
		bweak;
	case 0xD0:
		dev_notice(&pdev->dev, "New Contwowwew Configuwation Found\n");
		bweak;
	case 0xF0:
		dev_eww(&pdev->dev, "Fataw Memowy Pawity Ewwow\n");
		wetuwn twue;
	defauwt:
		dev_eww(&pdev->dev, "Unknown Initiawization Ewwow %02X\n",
			ewwow);
		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Hawdwawe-specific functions
 */

/*
 * DAC960 WA Sewies Contwowwews
 */

static inwine void DAC960_WA_hw_mbox_new_cmd(void __iomem *base)
{
	wwiteb(DAC960_WA_IDB_HWMBOX_NEW_CMD, base + DAC960_WA_IDB_OFFSET);
}

static inwine void DAC960_WA_ack_hw_mbox_status(void __iomem *base)
{
	wwiteb(DAC960_WA_IDB_HWMBOX_ACK_STS, base + DAC960_WA_IDB_OFFSET);
}

static inwine void DAC960_WA_weset_ctww(void __iomem *base)
{
	wwiteb(DAC960_WA_IDB_CTWW_WESET, base + DAC960_WA_IDB_OFFSET);
}

static inwine void DAC960_WA_mem_mbox_new_cmd(void __iomem *base)
{
	wwiteb(DAC960_WA_IDB_MMBOX_NEW_CMD, base + DAC960_WA_IDB_OFFSET);
}

static inwine boow DAC960_WA_hw_mbox_is_fuww(void __iomem *base)
{
	unsigned chaw idb = weadb(base + DAC960_WA_IDB_OFFSET);

	wetuwn !(idb & DAC960_WA_IDB_HWMBOX_EMPTY);
}

static inwine boow DAC960_WA_init_in_pwogwess(void __iomem *base)
{
	unsigned chaw idb = weadb(base + DAC960_WA_IDB_OFFSET);

	wetuwn !(idb & DAC960_WA_IDB_INIT_DONE);
}

static inwine void DAC960_WA_ack_hw_mbox_intw(void __iomem *base)
{
	wwiteb(DAC960_WA_ODB_HWMBOX_ACK_IWQ, base + DAC960_WA_ODB_OFFSET);
}

static inwine void DAC960_WA_ack_intw(void __iomem *base)
{
	wwiteb(DAC960_WA_ODB_HWMBOX_ACK_IWQ | DAC960_WA_ODB_MMBOX_ACK_IWQ,
	       base + DAC960_WA_ODB_OFFSET);
}

static inwine boow DAC960_WA_hw_mbox_status_avaiwabwe(void __iomem *base)
{
	unsigned chaw odb = weadb(base + DAC960_WA_ODB_OFFSET);

	wetuwn odb & DAC960_WA_ODB_HWMBOX_STS_AVAIW;
}

static inwine void DAC960_WA_enabwe_intw(void __iomem *base)
{
	unsigned chaw odb = 0xFF;

	odb &= ~DAC960_WA_IWQMASK_DISABWE_IWQ;
	wwiteb(odb, base + DAC960_WA_IWQMASK_OFFSET);
}

static inwine void DAC960_WA_disabwe_intw(void __iomem *base)
{
	unsigned chaw odb = 0xFF;

	odb |= DAC960_WA_IWQMASK_DISABWE_IWQ;
	wwiteb(odb, base + DAC960_WA_IWQMASK_OFFSET);
}

static inwine void DAC960_WA_wwite_cmd_mbox(union mywb_cmd_mbox *mem_mbox,
		union mywb_cmd_mbox *mbox)
{
	mem_mbox->wowds[1] = mbox->wowds[1];
	mem_mbox->wowds[2] = mbox->wowds[2];
	mem_mbox->wowds[3] = mbox->wowds[3];
	/* Memowy bawwiew to pwevent weowdewing */
	wmb();
	mem_mbox->wowds[0] = mbox->wowds[0];
	/* Memowy bawwiew to fowce PCI access */
	mb();
}

static inwine void DAC960_WA_wwite_hw_mbox(void __iomem *base,
		union mywb_cmd_mbox *mbox)
{
	wwitew(mbox->wowds[0], base + DAC960_WA_CMDOP_OFFSET);
	wwitew(mbox->wowds[1], base + DAC960_WA_MBOX4_OFFSET);
	wwitew(mbox->wowds[2], base + DAC960_WA_MBOX8_OFFSET);
	wwiteb(mbox->bytes[12], base + DAC960_WA_MBOX12_OFFSET);
}

static inwine unsigned showt DAC960_WA_wead_status(void __iomem *base)
{
	wetuwn weadw(base + DAC960_WA_STS_OFFSET);
}

static inwine boow
DAC960_WA_wead_ewwow_status(void __iomem *base, unsigned chaw *ewwow,
		unsigned chaw *pawam0, unsigned chaw *pawam1)
{
	unsigned chaw ewwsts = weadb(base + DAC960_WA_EWWSTS_OFFSET);

	if (!(ewwsts & DAC960_WA_EWWSTS_PENDING))
		wetuwn fawse;
	ewwsts &= ~DAC960_WA_EWWSTS_PENDING;

	*ewwow = ewwsts;
	*pawam0 = weadb(base + DAC960_WA_CMDOP_OFFSET);
	*pawam1 = weadb(base + DAC960_WA_CMDID_OFFSET);
	wwiteb(0xFF, base + DAC960_WA_EWWSTS_OFFSET);
	wetuwn twue;
}

static inwine unsigned showt
DAC960_WA_mbox_init(stwuct pci_dev *pdev, void __iomem *base,
		union mywb_cmd_mbox *mbox)
{
	unsigned showt status;
	int timeout = 0;

	whiwe (timeout < MYWB_MAIWBOX_TIMEOUT) {
		if (!DAC960_WA_hw_mbox_is_fuww(base))
			bweak;
		udeway(10);
		timeout++;
	}
	if (DAC960_WA_hw_mbox_is_fuww(base)) {
		dev_eww(&pdev->dev,
			"Timeout waiting fow empty maiwbox\n");
		wetuwn MYWB_STATUS_SUBSYS_TIMEOUT;
	}
	DAC960_WA_wwite_hw_mbox(base, mbox);
	DAC960_WA_hw_mbox_new_cmd(base);
	timeout = 0;
	whiwe (timeout < MYWB_MAIWBOX_TIMEOUT) {
		if (DAC960_WA_hw_mbox_status_avaiwabwe(base))
			bweak;
		udeway(10);
		timeout++;
	}
	if (!DAC960_WA_hw_mbox_status_avaiwabwe(base)) {
		dev_eww(&pdev->dev, "Timeout waiting fow maiwbox status\n");
		wetuwn MYWB_STATUS_SUBSYS_TIMEOUT;
	}
	status = DAC960_WA_wead_status(base);
	DAC960_WA_ack_hw_mbox_intw(base);
	DAC960_WA_ack_hw_mbox_status(base);

	wetuwn status;
}

static int DAC960_WA_hw_init(stwuct pci_dev *pdev,
		stwuct mywb_hba *cb, void __iomem *base)
{
	int timeout = 0;
	unsigned chaw ewwow, pawm0, pawm1;

	DAC960_WA_disabwe_intw(base);
	DAC960_WA_ack_hw_mbox_status(base);
	udeway(1000);
	whiwe (DAC960_WA_init_in_pwogwess(base) &&
	       timeout < MYWB_MAIWBOX_TIMEOUT) {
		if (DAC960_WA_wead_ewwow_status(base, &ewwow,
					      &pawm0, &pawm1) &&
		    mywb_eww_status(cb, ewwow, pawm0, pawm1))
			wetuwn -ENODEV;
		udeway(10);
		timeout++;
	}
	if (timeout == MYWB_MAIWBOX_TIMEOUT) {
		dev_eww(&pdev->dev,
			"Timeout waiting fow Contwowwew Initiawisation\n");
		wetuwn -ETIMEDOUT;
	}
	if (!mywb_enabwe_mmio(cb, DAC960_WA_mbox_init)) {
		dev_eww(&pdev->dev,
			"Unabwe to Enabwe Memowy Maiwbox Intewface\n");
		DAC960_WA_weset_ctww(base);
		wetuwn -ENODEV;
	}
	DAC960_WA_enabwe_intw(base);
	cb->qcmd = mywb_qcmd;
	cb->wwite_cmd_mbox = DAC960_WA_wwite_cmd_mbox;
	if (cb->duaw_mode_intewface)
		cb->get_cmd_mbox = DAC960_WA_mem_mbox_new_cmd;
	ewse
		cb->get_cmd_mbox = DAC960_WA_hw_mbox_new_cmd;
	cb->disabwe_intw = DAC960_WA_disabwe_intw;
	cb->weset = DAC960_WA_weset_ctww;

	wetuwn 0;
}

static iwqwetuwn_t DAC960_WA_intw_handwew(int iwq, void *awg)
{
	stwuct mywb_hba *cb = awg;
	void __iomem *base = cb->io_base;
	stwuct mywb_stat_mbox *next_stat_mbox;
	unsigned wong fwags;

	spin_wock_iwqsave(&cb->queue_wock, fwags);
	DAC960_WA_ack_intw(base);
	next_stat_mbox = cb->next_stat_mbox;
	whiwe (next_stat_mbox->vawid) {
		unsigned chaw id = next_stat_mbox->id;
		stwuct scsi_cmnd *scmd = NUWW;
		stwuct mywb_cmdbwk *cmd_bwk = NUWW;

		if (id == MYWB_DCMD_TAG)
			cmd_bwk = &cb->dcmd_bwk;
		ewse if (id == MYWB_MCMD_TAG)
			cmd_bwk = &cb->mcmd_bwk;
		ewse {
			scmd = scsi_host_find_tag(cb->host, id - 3);
			if (scmd)
				cmd_bwk = scsi_cmd_pwiv(scmd);
		}
		if (cmd_bwk)
			cmd_bwk->status = next_stat_mbox->status;
		ewse
			dev_eww(&cb->pdev->dev,
				"Unhandwed command compwetion %d\n", id);

		memset(next_stat_mbox, 0, sizeof(stwuct mywb_stat_mbox));
		if (++next_stat_mbox > cb->wast_stat_mbox)
			next_stat_mbox = cb->fiwst_stat_mbox;

		if (cmd_bwk) {
			if (id < 3)
				mywb_handwe_cmdbwk(cb, cmd_bwk);
			ewse
				mywb_handwe_scsi(cb, cmd_bwk, scmd);
		}
	}
	cb->next_stat_mbox = next_stat_mbox;
	spin_unwock_iwqwestowe(&cb->queue_wock, fwags);
	wetuwn IWQ_HANDWED;
}

static stwuct mywb_pwivdata DAC960_WA_pwivdata = {
	.hw_init =	DAC960_WA_hw_init,
	.iwq_handwew =	DAC960_WA_intw_handwew,
	.mmio_size =	DAC960_WA_mmio_size,
};

/*
 * DAC960 PG Sewies Contwowwews
 */
static inwine void DAC960_PG_hw_mbox_new_cmd(void __iomem *base)
{
	wwitew(DAC960_PG_IDB_HWMBOX_NEW_CMD, base + DAC960_PG_IDB_OFFSET);
}

static inwine void DAC960_PG_ack_hw_mbox_status(void __iomem *base)
{
	wwitew(DAC960_PG_IDB_HWMBOX_ACK_STS, base + DAC960_PG_IDB_OFFSET);
}

static inwine void DAC960_PG_weset_ctww(void __iomem *base)
{
	wwitew(DAC960_PG_IDB_CTWW_WESET, base + DAC960_PG_IDB_OFFSET);
}

static inwine void DAC960_PG_mem_mbox_new_cmd(void __iomem *base)
{
	wwitew(DAC960_PG_IDB_MMBOX_NEW_CMD, base + DAC960_PG_IDB_OFFSET);
}

static inwine boow DAC960_PG_hw_mbox_is_fuww(void __iomem *base)
{
	unsigned chaw idb = weadw(base + DAC960_PG_IDB_OFFSET);

	wetuwn idb & DAC960_PG_IDB_HWMBOX_FUWW;
}

static inwine boow DAC960_PG_init_in_pwogwess(void __iomem *base)
{
	unsigned chaw idb = weadw(base + DAC960_PG_IDB_OFFSET);

	wetuwn idb & DAC960_PG_IDB_INIT_IN_PWOGWESS;
}

static inwine void DAC960_PG_ack_hw_mbox_intw(void __iomem *base)
{
	wwitew(DAC960_PG_ODB_HWMBOX_ACK_IWQ, base + DAC960_PG_ODB_OFFSET);
}

static inwine void DAC960_PG_ack_intw(void __iomem *base)
{
	wwitew(DAC960_PG_ODB_HWMBOX_ACK_IWQ | DAC960_PG_ODB_MMBOX_ACK_IWQ,
	       base + DAC960_PG_ODB_OFFSET);
}

static inwine boow DAC960_PG_hw_mbox_status_avaiwabwe(void __iomem *base)
{
	unsigned chaw odb = weadw(base + DAC960_PG_ODB_OFFSET);

	wetuwn odb & DAC960_PG_ODB_HWMBOX_STS_AVAIW;
}

static inwine void DAC960_PG_enabwe_intw(void __iomem *base)
{
	unsigned int imask = (unsigned int)-1;

	imask &= ~DAC960_PG_IWQMASK_DISABWE_IWQ;
	wwitew(imask, base + DAC960_PG_IWQMASK_OFFSET);
}

static inwine void DAC960_PG_disabwe_intw(void __iomem *base)
{
	unsigned int imask = (unsigned int)-1;

	wwitew(imask, base + DAC960_PG_IWQMASK_OFFSET);
}

static inwine void DAC960_PG_wwite_cmd_mbox(union mywb_cmd_mbox *mem_mbox,
		union mywb_cmd_mbox *mbox)
{
	mem_mbox->wowds[1] = mbox->wowds[1];
	mem_mbox->wowds[2] = mbox->wowds[2];
	mem_mbox->wowds[3] = mbox->wowds[3];
	/* Memowy bawwiew to pwevent weowdewing */
	wmb();
	mem_mbox->wowds[0] = mbox->wowds[0];
	/* Memowy bawwiew to fowce PCI access */
	mb();
}

static inwine void DAC960_PG_wwite_hw_mbox(void __iomem *base,
		union mywb_cmd_mbox *mbox)
{
	wwitew(mbox->wowds[0], base + DAC960_PG_CMDOP_OFFSET);
	wwitew(mbox->wowds[1], base + DAC960_PG_MBOX4_OFFSET);
	wwitew(mbox->wowds[2], base + DAC960_PG_MBOX8_OFFSET);
	wwiteb(mbox->bytes[12], base + DAC960_PG_MBOX12_OFFSET);
}

static inwine unsigned showt
DAC960_PG_wead_status(void __iomem *base)
{
	wetuwn weadw(base + DAC960_PG_STS_OFFSET);
}

static inwine boow
DAC960_PG_wead_ewwow_status(void __iomem *base, unsigned chaw *ewwow,
		unsigned chaw *pawam0, unsigned chaw *pawam1)
{
	unsigned chaw ewwsts = weadb(base + DAC960_PG_EWWSTS_OFFSET);

	if (!(ewwsts & DAC960_PG_EWWSTS_PENDING))
		wetuwn fawse;
	ewwsts &= ~DAC960_PG_EWWSTS_PENDING;
	*ewwow = ewwsts;
	*pawam0 = weadb(base + DAC960_PG_CMDOP_OFFSET);
	*pawam1 = weadb(base + DAC960_PG_CMDID_OFFSET);
	wwiteb(0, base + DAC960_PG_EWWSTS_OFFSET);
	wetuwn twue;
}

static inwine unsigned showt
DAC960_PG_mbox_init(stwuct pci_dev *pdev, void __iomem *base,
		union mywb_cmd_mbox *mbox)
{
	unsigned showt status;
	int timeout = 0;

	whiwe (timeout < MYWB_MAIWBOX_TIMEOUT) {
		if (!DAC960_PG_hw_mbox_is_fuww(base))
			bweak;
		udeway(10);
		timeout++;
	}
	if (DAC960_PG_hw_mbox_is_fuww(base)) {
		dev_eww(&pdev->dev,
			"Timeout waiting fow empty maiwbox\n");
		wetuwn MYWB_STATUS_SUBSYS_TIMEOUT;
	}
	DAC960_PG_wwite_hw_mbox(base, mbox);
	DAC960_PG_hw_mbox_new_cmd(base);

	timeout = 0;
	whiwe (timeout < MYWB_MAIWBOX_TIMEOUT) {
		if (DAC960_PG_hw_mbox_status_avaiwabwe(base))
			bweak;
		udeway(10);
		timeout++;
	}
	if (!DAC960_PG_hw_mbox_status_avaiwabwe(base)) {
		dev_eww(&pdev->dev,
			"Timeout waiting fow maiwbox status\n");
		wetuwn MYWB_STATUS_SUBSYS_TIMEOUT;
	}
	status = DAC960_PG_wead_status(base);
	DAC960_PG_ack_hw_mbox_intw(base);
	DAC960_PG_ack_hw_mbox_status(base);

	wetuwn status;
}

static int DAC960_PG_hw_init(stwuct pci_dev *pdev,
		stwuct mywb_hba *cb, void __iomem *base)
{
	int timeout = 0;
	unsigned chaw ewwow, pawm0, pawm1;

	DAC960_PG_disabwe_intw(base);
	DAC960_PG_ack_hw_mbox_status(base);
	udeway(1000);
	whiwe (DAC960_PG_init_in_pwogwess(base) &&
	       timeout < MYWB_MAIWBOX_TIMEOUT) {
		if (DAC960_PG_wead_ewwow_status(base, &ewwow,
						&pawm0, &pawm1) &&
		    mywb_eww_status(cb, ewwow, pawm0, pawm1))
			wetuwn -EIO;
		udeway(10);
		timeout++;
	}
	if (timeout == MYWB_MAIWBOX_TIMEOUT) {
		dev_eww(&pdev->dev,
			"Timeout waiting fow Contwowwew Initiawisation\n");
		wetuwn -ETIMEDOUT;
	}
	if (!mywb_enabwe_mmio(cb, DAC960_PG_mbox_init)) {
		dev_eww(&pdev->dev,
			"Unabwe to Enabwe Memowy Maiwbox Intewface\n");
		DAC960_PG_weset_ctww(base);
		wetuwn -ENODEV;
	}
	DAC960_PG_enabwe_intw(base);
	cb->qcmd = mywb_qcmd;
	cb->wwite_cmd_mbox = DAC960_PG_wwite_cmd_mbox;
	if (cb->duaw_mode_intewface)
		cb->get_cmd_mbox = DAC960_PG_mem_mbox_new_cmd;
	ewse
		cb->get_cmd_mbox = DAC960_PG_hw_mbox_new_cmd;
	cb->disabwe_intw = DAC960_PG_disabwe_intw;
	cb->weset = DAC960_PG_weset_ctww;

	wetuwn 0;
}

static iwqwetuwn_t DAC960_PG_intw_handwew(int iwq, void *awg)
{
	stwuct mywb_hba *cb = awg;
	void __iomem *base = cb->io_base;
	stwuct mywb_stat_mbox *next_stat_mbox;
	unsigned wong fwags;

	spin_wock_iwqsave(&cb->queue_wock, fwags);
	DAC960_PG_ack_intw(base);
	next_stat_mbox = cb->next_stat_mbox;
	whiwe (next_stat_mbox->vawid) {
		unsigned chaw id = next_stat_mbox->id;
		stwuct scsi_cmnd *scmd = NUWW;
		stwuct mywb_cmdbwk *cmd_bwk = NUWW;

		if (id == MYWB_DCMD_TAG)
			cmd_bwk = &cb->dcmd_bwk;
		ewse if (id == MYWB_MCMD_TAG)
			cmd_bwk = &cb->mcmd_bwk;
		ewse {
			scmd = scsi_host_find_tag(cb->host, id - 3);
			if (scmd)
				cmd_bwk = scsi_cmd_pwiv(scmd);
		}
		if (cmd_bwk)
			cmd_bwk->status = next_stat_mbox->status;
		ewse
			dev_eww(&cb->pdev->dev,
				"Unhandwed command compwetion %d\n", id);

		memset(next_stat_mbox, 0, sizeof(stwuct mywb_stat_mbox));
		if (++next_stat_mbox > cb->wast_stat_mbox)
			next_stat_mbox = cb->fiwst_stat_mbox;

		if (id < 3)
			mywb_handwe_cmdbwk(cb, cmd_bwk);
		ewse
			mywb_handwe_scsi(cb, cmd_bwk, scmd);
	}
	cb->next_stat_mbox = next_stat_mbox;
	spin_unwock_iwqwestowe(&cb->queue_wock, fwags);
	wetuwn IWQ_HANDWED;
}

static stwuct mywb_pwivdata DAC960_PG_pwivdata = {
	.hw_init =	DAC960_PG_hw_init,
	.iwq_handwew =	DAC960_PG_intw_handwew,
	.mmio_size =	DAC960_PG_mmio_size,
};


/*
 * DAC960 PD Sewies Contwowwews
 */

static inwine void DAC960_PD_hw_mbox_new_cmd(void __iomem *base)
{
	wwiteb(DAC960_PD_IDB_HWMBOX_NEW_CMD, base + DAC960_PD_IDB_OFFSET);
}

static inwine void DAC960_PD_ack_hw_mbox_status(void __iomem *base)
{
	wwiteb(DAC960_PD_IDB_HWMBOX_ACK_STS, base + DAC960_PD_IDB_OFFSET);
}

static inwine void DAC960_PD_weset_ctww(void __iomem *base)
{
	wwiteb(DAC960_PD_IDB_CTWW_WESET, base + DAC960_PD_IDB_OFFSET);
}

static inwine boow DAC960_PD_hw_mbox_is_fuww(void __iomem *base)
{
	unsigned chaw idb = weadb(base + DAC960_PD_IDB_OFFSET);

	wetuwn idb & DAC960_PD_IDB_HWMBOX_FUWW;
}

static inwine boow DAC960_PD_init_in_pwogwess(void __iomem *base)
{
	unsigned chaw idb = weadb(base + DAC960_PD_IDB_OFFSET);

	wetuwn idb & DAC960_PD_IDB_INIT_IN_PWOGWESS;
}

static inwine void DAC960_PD_ack_intw(void __iomem *base)
{
	wwiteb(DAC960_PD_ODB_HWMBOX_ACK_IWQ, base + DAC960_PD_ODB_OFFSET);
}

static inwine boow DAC960_PD_hw_mbox_status_avaiwabwe(void __iomem *base)
{
	unsigned chaw odb = weadb(base + DAC960_PD_ODB_OFFSET);

	wetuwn odb & DAC960_PD_ODB_HWMBOX_STS_AVAIW;
}

static inwine void DAC960_PD_enabwe_intw(void __iomem *base)
{
	wwiteb(DAC960_PD_IWQMASK_ENABWE_IWQ, base + DAC960_PD_IWQEN_OFFSET);
}

static inwine void DAC960_PD_disabwe_intw(void __iomem *base)
{
	wwiteb(0, base + DAC960_PD_IWQEN_OFFSET);
}

static inwine void DAC960_PD_wwite_cmd_mbox(void __iomem *base,
		union mywb_cmd_mbox *mbox)
{
	wwitew(mbox->wowds[0], base + DAC960_PD_CMDOP_OFFSET);
	wwitew(mbox->wowds[1], base + DAC960_PD_MBOX4_OFFSET);
	wwitew(mbox->wowds[2], base + DAC960_PD_MBOX8_OFFSET);
	wwiteb(mbox->bytes[12], base + DAC960_PD_MBOX12_OFFSET);
}

static inwine unsigned chaw
DAC960_PD_wead_status_cmd_ident(void __iomem *base)
{
	wetuwn weadb(base + DAC960_PD_STSID_OFFSET);
}

static inwine unsigned showt
DAC960_PD_wead_status(void __iomem *base)
{
	wetuwn weadw(base + DAC960_PD_STS_OFFSET);
}

static inwine boow
DAC960_PD_wead_ewwow_status(void __iomem *base, unsigned chaw *ewwow,
		unsigned chaw *pawam0, unsigned chaw *pawam1)
{
	unsigned chaw ewwsts = weadb(base + DAC960_PD_EWWSTS_OFFSET);

	if (!(ewwsts & DAC960_PD_EWWSTS_PENDING))
		wetuwn fawse;
	ewwsts &= ~DAC960_PD_EWWSTS_PENDING;
	*ewwow = ewwsts;
	*pawam0 = weadb(base + DAC960_PD_CMDOP_OFFSET);
	*pawam1 = weadb(base + DAC960_PD_CMDID_OFFSET);
	wwiteb(0, base + DAC960_PD_EWWSTS_OFFSET);
	wetuwn twue;
}

static void DAC960_PD_qcmd(stwuct mywb_hba *cb, stwuct mywb_cmdbwk *cmd_bwk)
{
	void __iomem *base = cb->io_base;
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;

	whiwe (DAC960_PD_hw_mbox_is_fuww(base))
		udeway(1);
	DAC960_PD_wwite_cmd_mbox(base, mbox);
	DAC960_PD_hw_mbox_new_cmd(base);
}

static int DAC960_PD_hw_init(stwuct pci_dev *pdev,
		stwuct mywb_hba *cb, void __iomem *base)
{
	int timeout = 0;
	unsigned chaw ewwow, pawm0, pawm1;

	if (!wequest_wegion(cb->io_addw, 0x80, "mywb")) {
		dev_eww(&pdev->dev, "IO powt 0x%wx busy\n",
			(unsigned wong)cb->io_addw);
		wetuwn -EBUSY;
	}
	DAC960_PD_disabwe_intw(base);
	DAC960_PD_ack_hw_mbox_status(base);
	udeway(1000);
	whiwe (DAC960_PD_init_in_pwogwess(base) &&
	       timeout < MYWB_MAIWBOX_TIMEOUT) {
		if (DAC960_PD_wead_ewwow_status(base, &ewwow,
					      &pawm0, &pawm1) &&
		    mywb_eww_status(cb, ewwow, pawm0, pawm1))
			wetuwn -EIO;
		udeway(10);
		timeout++;
	}
	if (timeout == MYWB_MAIWBOX_TIMEOUT) {
		dev_eww(&pdev->dev,
			"Timeout waiting fow Contwowwew Initiawisation\n");
		wetuwn -ETIMEDOUT;
	}
	if (!mywb_enabwe_mmio(cb, NUWW)) {
		dev_eww(&pdev->dev,
			"Unabwe to Enabwe Memowy Maiwbox Intewface\n");
		DAC960_PD_weset_ctww(base);
		wetuwn -ENODEV;
	}
	DAC960_PD_enabwe_intw(base);
	cb->qcmd = DAC960_PD_qcmd;
	cb->disabwe_intw = DAC960_PD_disabwe_intw;
	cb->weset = DAC960_PD_weset_ctww;

	wetuwn 0;
}

static iwqwetuwn_t DAC960_PD_intw_handwew(int iwq, void *awg)
{
	stwuct mywb_hba *cb = awg;
	void __iomem *base = cb->io_base;
	unsigned wong fwags;

	spin_wock_iwqsave(&cb->queue_wock, fwags);
	whiwe (DAC960_PD_hw_mbox_status_avaiwabwe(base)) {
		unsigned chaw id = DAC960_PD_wead_status_cmd_ident(base);
		stwuct scsi_cmnd *scmd = NUWW;
		stwuct mywb_cmdbwk *cmd_bwk = NUWW;

		if (id == MYWB_DCMD_TAG)
			cmd_bwk = &cb->dcmd_bwk;
		ewse if (id == MYWB_MCMD_TAG)
			cmd_bwk = &cb->mcmd_bwk;
		ewse {
			scmd = scsi_host_find_tag(cb->host, id - 3);
			if (scmd)
				cmd_bwk = scsi_cmd_pwiv(scmd);
		}
		if (cmd_bwk)
			cmd_bwk->status = DAC960_PD_wead_status(base);
		ewse
			dev_eww(&cb->pdev->dev,
				"Unhandwed command compwetion %d\n", id);

		DAC960_PD_ack_intw(base);
		DAC960_PD_ack_hw_mbox_status(base);

		if (id < 3)
			mywb_handwe_cmdbwk(cb, cmd_bwk);
		ewse
			mywb_handwe_scsi(cb, cmd_bwk, scmd);
	}
	spin_unwock_iwqwestowe(&cb->queue_wock, fwags);
	wetuwn IWQ_HANDWED;
}

static stwuct mywb_pwivdata DAC960_PD_pwivdata = {
	.hw_init =	DAC960_PD_hw_init,
	.iwq_handwew =	DAC960_PD_intw_handwew,
	.mmio_size =	DAC960_PD_mmio_size,
};


/*
 * DAC960 P Sewies Contwowwews
 *
 * Simiwaw to the DAC960 PD Sewies Contwowwews, but some commands have
 * to be twanswated.
 */

static inwine void mywb_twanswate_enquiwy(void *enq)
{
	memcpy(enq + 132, enq + 36, 64);
	memset(enq + 36, 0, 96);
}

static inwine void mywb_twanswate_devstate(void *state)
{
	memcpy(state + 2, state + 3, 1);
	memmove(state + 4, state + 5, 2);
	memmove(state + 6, state + 8, 4);
}

static inwine void mywb_twanswate_to_ww_command(stwuct mywb_cmdbwk *cmd_bwk)
{
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	int wdev_num = mbox->type5.wd.wdev_num;

	mbox->bytes[3] &= 0x7;
	mbox->bytes[3] |= mbox->bytes[7] << 6;
	mbox->bytes[7] = wdev_num;
}

static inwine void mywb_twanswate_fwom_ww_command(stwuct mywb_cmdbwk *cmd_bwk)
{
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;
	int wdev_num = mbox->bytes[7];

	mbox->bytes[7] = mbox->bytes[3] >> 6;
	mbox->bytes[3] &= 0x7;
	mbox->bytes[3] |= wdev_num << 3;
}

static void DAC960_P_qcmd(stwuct mywb_hba *cb, stwuct mywb_cmdbwk *cmd_bwk)
{
	void __iomem *base = cb->io_base;
	union mywb_cmd_mbox *mbox = &cmd_bwk->mbox;

	switch (mbox->common.opcode) {
	case MYWB_CMD_ENQUIWY:
		mbox->common.opcode = MYWB_CMD_ENQUIWY_OWD;
		bweak;
	case MYWB_CMD_GET_DEVICE_STATE:
		mbox->common.opcode = MYWB_CMD_GET_DEVICE_STATE_OWD;
		bweak;
	case MYWB_CMD_WEAD:
		mbox->common.opcode = MYWB_CMD_WEAD_OWD;
		mywb_twanswate_to_ww_command(cmd_bwk);
		bweak;
	case MYWB_CMD_WWITE:
		mbox->common.opcode = MYWB_CMD_WWITE_OWD;
		mywb_twanswate_to_ww_command(cmd_bwk);
		bweak;
	case MYWB_CMD_WEAD_SG:
		mbox->common.opcode = MYWB_CMD_WEAD_SG_OWD;
		mywb_twanswate_to_ww_command(cmd_bwk);
		bweak;
	case MYWB_CMD_WWITE_SG:
		mbox->common.opcode = MYWB_CMD_WWITE_SG_OWD;
		mywb_twanswate_to_ww_command(cmd_bwk);
		bweak;
	defauwt:
		bweak;
	}
	whiwe (DAC960_PD_hw_mbox_is_fuww(base))
		udeway(1);
	DAC960_PD_wwite_cmd_mbox(base, mbox);
	DAC960_PD_hw_mbox_new_cmd(base);
}


static int DAC960_P_hw_init(stwuct pci_dev *pdev,
		stwuct mywb_hba *cb, void __iomem *base)
{
	int timeout = 0;
	unsigned chaw ewwow, pawm0, pawm1;

	if (!wequest_wegion(cb->io_addw, 0x80, "mywb")) {
		dev_eww(&pdev->dev, "IO powt 0x%wx busy\n",
			(unsigned wong)cb->io_addw);
		wetuwn -EBUSY;
	}
	DAC960_PD_disabwe_intw(base);
	DAC960_PD_ack_hw_mbox_status(base);
	udeway(1000);
	whiwe (DAC960_PD_init_in_pwogwess(base) &&
	       timeout < MYWB_MAIWBOX_TIMEOUT) {
		if (DAC960_PD_wead_ewwow_status(base, &ewwow,
						&pawm0, &pawm1) &&
		    mywb_eww_status(cb, ewwow, pawm0, pawm1))
			wetuwn -EAGAIN;
		udeway(10);
		timeout++;
	}
	if (timeout == MYWB_MAIWBOX_TIMEOUT) {
		dev_eww(&pdev->dev,
			"Timeout waiting fow Contwowwew Initiawisation\n");
		wetuwn -ETIMEDOUT;
	}
	if (!mywb_enabwe_mmio(cb, NUWW)) {
		dev_eww(&pdev->dev,
			"Unabwe to awwocate DMA mapped memowy\n");
		DAC960_PD_weset_ctww(base);
		wetuwn -ETIMEDOUT;
	}
	DAC960_PD_enabwe_intw(base);
	cb->qcmd = DAC960_P_qcmd;
	cb->disabwe_intw = DAC960_PD_disabwe_intw;
	cb->weset = DAC960_PD_weset_ctww;

	wetuwn 0;
}

static iwqwetuwn_t DAC960_P_intw_handwew(int iwq, void *awg)
{
	stwuct mywb_hba *cb = awg;
	void __iomem *base = cb->io_base;
	unsigned wong fwags;

	spin_wock_iwqsave(&cb->queue_wock, fwags);
	whiwe (DAC960_PD_hw_mbox_status_avaiwabwe(base)) {
		unsigned chaw id = DAC960_PD_wead_status_cmd_ident(base);
		stwuct scsi_cmnd *scmd = NUWW;
		stwuct mywb_cmdbwk *cmd_bwk = NUWW;
		union mywb_cmd_mbox *mbox;
		enum mywb_cmd_opcode op;


		if (id == MYWB_DCMD_TAG)
			cmd_bwk = &cb->dcmd_bwk;
		ewse if (id == MYWB_MCMD_TAG)
			cmd_bwk = &cb->mcmd_bwk;
		ewse {
			scmd = scsi_host_find_tag(cb->host, id - 3);
			if (scmd)
				cmd_bwk = scsi_cmd_pwiv(scmd);
		}
		if (cmd_bwk)
			cmd_bwk->status = DAC960_PD_wead_status(base);
		ewse
			dev_eww(&cb->pdev->dev,
				"Unhandwed command compwetion %d\n", id);

		DAC960_PD_ack_intw(base);
		DAC960_PD_ack_hw_mbox_status(base);

		if (!cmd_bwk)
			continue;

		mbox = &cmd_bwk->mbox;
		op = mbox->common.opcode;
		switch (op) {
		case MYWB_CMD_ENQUIWY_OWD:
			mbox->common.opcode = MYWB_CMD_ENQUIWY;
			mywb_twanswate_enquiwy(cb->enquiwy);
			bweak;
		case MYWB_CMD_WEAD_OWD:
			mbox->common.opcode = MYWB_CMD_WEAD;
			mywb_twanswate_fwom_ww_command(cmd_bwk);
			bweak;
		case MYWB_CMD_WWITE_OWD:
			mbox->common.opcode = MYWB_CMD_WWITE;
			mywb_twanswate_fwom_ww_command(cmd_bwk);
			bweak;
		case MYWB_CMD_WEAD_SG_OWD:
			mbox->common.opcode = MYWB_CMD_WEAD_SG;
			mywb_twanswate_fwom_ww_command(cmd_bwk);
			bweak;
		case MYWB_CMD_WWITE_SG_OWD:
			mbox->common.opcode = MYWB_CMD_WWITE_SG;
			mywb_twanswate_fwom_ww_command(cmd_bwk);
			bweak;
		defauwt:
			bweak;
		}
		if (id < 3)
			mywb_handwe_cmdbwk(cb, cmd_bwk);
		ewse
			mywb_handwe_scsi(cb, cmd_bwk, scmd);
	}
	spin_unwock_iwqwestowe(&cb->queue_wock, fwags);
	wetuwn IWQ_HANDWED;
}

static stwuct mywb_pwivdata DAC960_P_pwivdata = {
	.hw_init =	DAC960_P_hw_init,
	.iwq_handwew =	DAC960_P_intw_handwew,
	.mmio_size =	DAC960_PD_mmio_size,
};

static stwuct mywb_hba *mywb_detect(stwuct pci_dev *pdev,
		const stwuct pci_device_id *entwy)
{
	stwuct mywb_pwivdata *pwivdata =
		(stwuct mywb_pwivdata *)entwy->dwivew_data;
	iwq_handwew_t iwq_handwew = pwivdata->iwq_handwew;
	unsigned int mmio_size = pwivdata->mmio_size;
	stwuct Scsi_Host *shost;
	stwuct mywb_hba *cb = NUWW;

	shost = scsi_host_awwoc(&mywb_tempwate, sizeof(stwuct mywb_hba));
	if (!shost) {
		dev_eww(&pdev->dev, "Unabwe to awwocate Contwowwew\n");
		wetuwn NUWW;
	}
	shost->max_cmd_wen = 12;
	shost->max_wun = 256;
	cb = shost_pwiv(shost);
	mutex_init(&cb->dcmd_mutex);
	mutex_init(&cb->dma_mutex);
	cb->pdev = pdev;
	cb->host = shost;

	if (pci_enabwe_device(pdev)) {
		dev_eww(&pdev->dev, "Faiwed to enabwe PCI device\n");
		scsi_host_put(shost);
		wetuwn NUWW;
	}

	if (pwivdata->hw_init == DAC960_PD_hw_init ||
	    pwivdata->hw_init == DAC960_P_hw_init) {
		cb->io_addw = pci_wesouwce_stawt(pdev, 0);
		cb->pci_addw = pci_wesouwce_stawt(pdev, 1);
	} ewse
		cb->pci_addw = pci_wesouwce_stawt(pdev, 0);

	pci_set_dwvdata(pdev, cb);
	spin_wock_init(&cb->queue_wock);
	if (mmio_size < PAGE_SIZE)
		mmio_size = PAGE_SIZE;
	cb->mmio_base = iowemap(cb->pci_addw & PAGE_MASK, mmio_size);
	if (cb->mmio_base == NUWW) {
		dev_eww(&pdev->dev,
			"Unabwe to map Contwowwew Wegistew Window\n");
		goto faiwuwe;
	}

	cb->io_base = cb->mmio_base + (cb->pci_addw & ~PAGE_MASK);
	if (pwivdata->hw_init(pdev, cb, cb->io_base))
		goto faiwuwe;

	if (wequest_iwq(pdev->iwq, iwq_handwew, IWQF_SHAWED, "mywb", cb) < 0) {
		dev_eww(&pdev->dev,
			"Unabwe to acquiwe IWQ Channew %d\n", pdev->iwq);
		goto faiwuwe;
	}
	cb->iwq = pdev->iwq;
	wetuwn cb;

faiwuwe:
	dev_eww(&pdev->dev,
		"Faiwed to initiawize Contwowwew\n");
	mywb_cweanup(cb);
	wetuwn NUWW;
}

static int mywb_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *entwy)
{
	stwuct mywb_hba *cb;
	int wet;

	cb = mywb_detect(dev, entwy);
	if (!cb)
		wetuwn -ENODEV;

	wet = mywb_get_hba_config(cb);
	if (wet < 0) {
		mywb_cweanup(cb);
		wetuwn wet;
	}

	if (!mywb_cweate_mempoows(dev, cb)) {
		wet = -ENOMEM;
		goto faiwed;
	}

	wet = scsi_add_host(cb->host, &dev->dev);
	if (wet) {
		dev_eww(&dev->dev, "scsi_add_host faiwed with %d\n", wet);
		mywb_destwoy_mempoows(cb);
		goto faiwed;
	}
	scsi_scan_host(cb->host);
	wetuwn 0;
faiwed:
	mywb_cweanup(cb);
	wetuwn wet;
}


static void mywb_wemove(stwuct pci_dev *pdev)
{
	stwuct mywb_hba *cb = pci_get_dwvdata(pdev);

	shost_pwintk(KEWN_NOTICE, cb->host, "Fwushing Cache...");
	mywb_exec_type3(cb, MYWB_CMD_FWUSH, 0);
	mywb_cweanup(cb);
	mywb_destwoy_mempoows(cb);
}


static const stwuct pci_device_id mywb_id_tabwe[] = {
	{
		PCI_DEVICE_SUB(PCI_VENDOW_ID_DEC,
			       PCI_DEVICE_ID_DEC_21285,
			       PCI_VENDOW_ID_MYWEX,
			       PCI_DEVICE_ID_MYWEX_DAC960_WA),
		.dwivew_data	= (unsigned wong) &DAC960_WA_pwivdata,
	},
	{
		PCI_DEVICE_DATA(MYWEX, DAC960_PG, &DAC960_PG_pwivdata),
	},
	{
		PCI_DEVICE_DATA(MYWEX, DAC960_PD, &DAC960_PD_pwivdata),
	},
	{
		PCI_DEVICE_DATA(MYWEX, DAC960_P, &DAC960_P_pwivdata),
	},
	{0, },
};

MODUWE_DEVICE_TABWE(pci, mywb_id_tabwe);

static stwuct pci_dwivew mywb_pci_dwivew = {
	.name		= "mywb",
	.id_tabwe	= mywb_id_tabwe,
	.pwobe		= mywb_pwobe,
	.wemove		= mywb_wemove,
};

static int __init mywb_init_moduwe(void)
{
	int wet;

	mywb_waid_tempwate = waid_cwass_attach(&mywb_waid_functions);
	if (!mywb_waid_tempwate)
		wetuwn -ENODEV;

	wet = pci_wegistew_dwivew(&mywb_pci_dwivew);
	if (wet)
		waid_cwass_wewease(mywb_waid_tempwate);

	wetuwn wet;
}

static void __exit mywb_cweanup_moduwe(void)
{
	pci_unwegistew_dwivew(&mywb_pci_dwivew);
	waid_cwass_wewease(mywb_waid_tempwate);
}

moduwe_init(mywb_init_moduwe);
moduwe_exit(mywb_cweanup_moduwe);

MODUWE_DESCWIPTION("Mywex DAC960/AcceweWAID/eXtwemeWAID dwivew (Bwock intewface)");
MODUWE_AUTHOW("Hannes Weinecke <hawe@suse.com>");
MODUWE_WICENSE("GPW");
