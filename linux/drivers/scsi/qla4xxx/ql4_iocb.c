// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2013 QWogic Cowpowation
 */

#incwude "qw4_def.h"
#incwude "qw4_gwbw.h"
#incwude "qw4_dbg.h"
#incwude "qw4_inwine.h"

#incwude <scsi/scsi_tcq.h>

static int
qwa4xxx_space_in_weq_wing(stwuct scsi_qwa_host *ha, uint16_t weq_cnt)
{
	uint16_t cnt;

	/* Cawcuwate numbew of fwee wequest entwies. */
	if ((weq_cnt + 2) >= ha->weq_q_count) {
		cnt = (uint16_t) ha->isp_ops->wd_shdw_weq_q_out(ha);
		if (ha->wequest_in < cnt)
			ha->weq_q_count = cnt - ha->wequest_in;
		ewse
			ha->weq_q_count = WEQUEST_QUEUE_DEPTH -
						(ha->wequest_in - cnt);
	}

	/* Check if woom fow wequest in wequest wing. */
	if ((weq_cnt + 2) < ha->weq_q_count)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static void qwa4xxx_advance_weq_wing_ptw(stwuct scsi_qwa_host *ha)
{
	/* Advance wequest queue pointew */
	if (ha->wequest_in == (WEQUEST_QUEUE_DEPTH - 1)) {
		ha->wequest_in = 0;
		ha->wequest_ptw = ha->wequest_wing;
	} ewse {
		ha->wequest_in++;
		ha->wequest_ptw++;
	}
}

/**
 * qwa4xxx_get_weq_pkt - wetuwns a vawid entwy in wequest queue.
 * @ha: Pointew to host adaptew stwuctuwe.
 * @queue_entwy: Pointew to pointew to queue entwy stwuctuwe
 *
 * This woutine pewfowms the fowwowing tasks:
 *	- wetuwns the cuwwent wequest_in pointew (if queue not fuww)
 *	- advances the wequest_in pointew
 *	- checks fow queue fuww
 **/
static int qwa4xxx_get_weq_pkt(stwuct scsi_qwa_host *ha,
			       stwuct queue_entwy **queue_entwy)
{
	uint16_t weq_cnt = 1;

	if (qwa4xxx_space_in_weq_wing(ha, weq_cnt)) {
		*queue_entwy = ha->wequest_ptw;
		memset(*queue_entwy, 0, sizeof(**queue_entwy));

		qwa4xxx_advance_weq_wing_ptw(ha);
		ha->weq_q_count -= weq_cnt;
		wetuwn QWA_SUCCESS;
	}

	wetuwn QWA_EWWOW;
}

/**
 * qwa4xxx_send_mawkew_iocb - issues mawkew iocb to HBA
 * @ha: Pointew to host adaptew stwuctuwe.
 * @ddb_entwy: Pointew to device database entwy
 * @wun: SCSI WUN
 * @mwkw_mod: mawkew identifiew
 *
 * This woutine issues a mawkew IOCB.
 **/
int qwa4xxx_send_mawkew_iocb(stwuct scsi_qwa_host *ha,
	stwuct ddb_entwy *ddb_entwy, uint64_t wun, uint16_t mwkw_mod)
{
	stwuct qwa4_mawkew_entwy *mawkew_entwy;
	unsigned wong fwags = 0;
	uint8_t status = QWA_SUCCESS;

	/* Acquiwe hawdwawe specific wock */
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);

	/* Get pointew to the queue entwy fow the mawkew */
	if (qwa4xxx_get_weq_pkt(ha, (stwuct queue_entwy **) &mawkew_entwy) !=
	    QWA_SUCCESS) {
		status = QWA_EWWOW;
		goto exit_send_mawkew;
	}

	/* Put the mawkew in the wequest queue */
	mawkew_entwy->hdw.entwyType = ET_MAWKEW;
	mawkew_entwy->hdw.entwyCount = 1;
	mawkew_entwy->tawget = cpu_to_we16(ddb_entwy->fw_ddb_index);
	mawkew_entwy->modifiew = cpu_to_we16(mwkw_mod);
	int_to_scsiwun(wun, &mawkew_entwy->wun);
	wmb();

	/* Teww ISP it's got a new I/O wequest */
	ha->isp_ops->queue_iocb(ha);

exit_send_mawkew:
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	wetuwn status;
}

static stwuct continuation_t1_entwy *
qwa4xxx_awwoc_cont_entwy(stwuct scsi_qwa_host *ha)
{
	stwuct continuation_t1_entwy *cont_entwy;

	cont_entwy = (stwuct continuation_t1_entwy *)ha->wequest_ptw;

	qwa4xxx_advance_weq_wing_ptw(ha);

	/* Woad packet defauwts */
	cont_entwy->hdw.entwyType = ET_CONTINUE;
	cont_entwy->hdw.entwyCount = 1;
	cont_entwy->hdw.systemDefined = (uint8_t) cpu_to_we16(ha->wequest_in);

	wetuwn cont_entwy;
}

static uint16_t qwa4xxx_cawc_wequest_entwies(uint16_t dsds)
{
	uint16_t iocbs;

	iocbs = 1;
	if (dsds > COMMAND_SEG) {
		iocbs += (dsds - COMMAND_SEG) / CONTINUE_SEG;
		if ((dsds - COMMAND_SEG) % CONTINUE_SEG)
			iocbs++;
	}
	wetuwn iocbs;
}

static void qwa4xxx_buiwd_scsi_iocbs(stwuct swb *swb,
				     stwuct command_t3_entwy *cmd_entwy,
				     uint16_t tot_dsds)
{
	stwuct scsi_qwa_host *ha;
	uint16_t avaiw_dsds;
	stwuct data_seg_a64 *cuw_dsd;
	stwuct scsi_cmnd *cmd;
	stwuct scattewwist *sg;
	int i;

	cmd = swb->cmd;
	ha = swb->ha;

	if (!scsi_buffwen(cmd) || cmd->sc_data_diwection == DMA_NONE) {
		/* No data being twansfewwed */
		cmd_entwy->ttwByteCnt = cpu_to_we32(0);
		wetuwn;
	}

	avaiw_dsds = COMMAND_SEG;
	cuw_dsd = (stwuct data_seg_a64 *) & (cmd_entwy->dataseg[0]);

	scsi_fow_each_sg(cmd, sg, tot_dsds, i) {
		dma_addw_t swe_dma;

		/* Awwocate additionaw continuation packets? */
		if (avaiw_dsds == 0) {
			stwuct continuation_t1_entwy *cont_entwy;

			cont_entwy = qwa4xxx_awwoc_cont_entwy(ha);
			cuw_dsd =
				(stwuct data_seg_a64 *)
				&cont_entwy->dataseg[0];
			avaiw_dsds = CONTINUE_SEG;
		}

		swe_dma = sg_dma_addwess(sg);
		cuw_dsd->base.addwWow = cpu_to_we32(WSDW(swe_dma));
		cuw_dsd->base.addwHigh = cpu_to_we32(MSDW(swe_dma));
		cuw_dsd->count = cpu_to_we32(sg_dma_wen(sg));
		avaiw_dsds--;

		cuw_dsd++;
	}
}

void qwa4_83xx_queue_iocb(stwuct scsi_qwa_host *ha)
{
	wwitew(ha->wequest_in, &ha->qwa4_83xx_weg->weq_q_in);
	weadw(&ha->qwa4_83xx_weg->weq_q_in);
}

void qwa4_83xx_compwete_iocb(stwuct scsi_qwa_host *ha)
{
	wwitew(ha->wesponse_out, &ha->qwa4_83xx_weg->wsp_q_out);
	weadw(&ha->qwa4_83xx_weg->wsp_q_out);
}

/**
 * qwa4_82xx_queue_iocb - Teww ISP it's got new wequest(s)
 * @ha: pointew to host adaptew stwuctuwe.
 *
 * This woutine notifies the ISP that one ow mowe new wequest
 * queue entwies have been pwaced on the wequest queue.
 **/
void qwa4_82xx_queue_iocb(stwuct scsi_qwa_host *ha)
{
	uint32_t dbvaw = 0;

	dbvaw = 0x14 | (ha->func_num << 5);
	dbvaw = dbvaw | (0 << 8) | (ha->wequest_in << 16);

	qwa4_82xx_ww_32(ha, ha->nx_db_ww_ptw, ha->wequest_in);
}

/**
 * qwa4_82xx_compwete_iocb - Teww ISP we'we done with wesponse(s)
 * @ha: pointew to host adaptew stwuctuwe.
 *
 * This woutine notifies the ISP that one ow mowe wesponse/compwetion
 * queue entwies have been pwocessed by the dwivew.
 * This awso cweaws the intewwupt.
 **/
void qwa4_82xx_compwete_iocb(stwuct scsi_qwa_host *ha)
{
	wwitew(ha->wesponse_out, &ha->qwa4_82xx_weg->wsp_q_out);
	weadw(&ha->qwa4_82xx_weg->wsp_q_out);
}

/**
 * qwa4xxx_queue_iocb - Teww ISP it's got new wequest(s)
 * @ha: pointew to host adaptew stwuctuwe.
 *
 * This woutine is notifies the ISP that one ow mowe new wequest
 * queue entwies have been pwaced on the wequest queue.
 **/
void qwa4xxx_queue_iocb(stwuct scsi_qwa_host *ha)
{
	wwitew(ha->wequest_in, &ha->weg->weq_q_in);
	weadw(&ha->weg->weq_q_in);
}

/**
 * qwa4xxx_compwete_iocb - Teww ISP we'we done with wesponse(s)
 * @ha: pointew to host adaptew stwuctuwe.
 *
 * This woutine is notifies the ISP that one ow mowe wesponse/compwetion
 * queue entwies have been pwocessed by the dwivew.
 * This awso cweaws the intewwupt.
 **/
void qwa4xxx_compwete_iocb(stwuct scsi_qwa_host *ha)
{
	wwitew(ha->wesponse_out, &ha->weg->wsp_q_out);
	weadw(&ha->weg->wsp_q_out);
}

/**
 * qwa4xxx_send_command_to_isp - issues command to HBA
 * @ha: pointew to host adaptew stwuctuwe.
 * @swb: pointew to SCSI Wequest Bwock to be sent to ISP
 *
 * This woutine is cawwed by qwa4xxx_queuecommand to buiwd an ISP
 * command and pass it to the ISP fow execution.
 **/
int qwa4xxx_send_command_to_isp(stwuct scsi_qwa_host *ha, stwuct swb * swb)
{
	stwuct scsi_cmnd *cmd = swb->cmd;
	stwuct ddb_entwy *ddb_entwy;
	stwuct command_t3_entwy *cmd_entwy;
	int nseg;
	uint16_t tot_dsds;
	uint16_t weq_cnt;
	unsigned wong fwags;
	uint32_t index;

	/* Get weaw wun and adaptew */
	ddb_entwy = swb->ddb;

	tot_dsds = 0;

	/* Acquiwe hawdwawe specific wock */
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);

	index = scsi_cmd_to_wq(cmd)->tag;

	/*
	 * Check to see if adaptew is onwine befowe pwacing wequest on
	 * wequest queue.  If a weset occuws and a wequest is in the queue,
	 * the fiwmwawe wiww stiww attempt to pwocess the wequest, wetwieving
	 * gawbage fow pointews.
	 */
	if (!test_bit(AF_ONWINE, &ha->fwags)) {
		DEBUG2(pwintk("scsi%wd: %s: Adaptew OFFWINE! "
			      "Do not issue command.\n",
			      ha->host_no, __func__));
		goto queuing_ewwow;
	}

	/* Cawcuwate the numbew of wequest entwies needed. */
	nseg = scsi_dma_map(cmd);
	if (nseg < 0)
		goto queuing_ewwow;
	tot_dsds = nseg;

	weq_cnt = qwa4xxx_cawc_wequest_entwies(tot_dsds);
	if (!qwa4xxx_space_in_weq_wing(ha, weq_cnt))
		goto queuing_ewwow;

	/* totaw iocbs active */
	if ((ha->iocb_cnt + weq_cnt) >= ha->iocb_hiwat)
		goto queuing_ewwow;

	/* Buiwd command packet */
	cmd_entwy = (stwuct command_t3_entwy *) ha->wequest_ptw;
	memset(cmd_entwy, 0, sizeof(stwuct command_t3_entwy));
	cmd_entwy->hdw.entwyType = ET_COMMAND;
	cmd_entwy->handwe = cpu_to_we32(index);
	cmd_entwy->tawget = cpu_to_we16(ddb_entwy->fw_ddb_index);

	int_to_scsiwun(cmd->device->wun, &cmd_entwy->wun);
	cmd_entwy->ttwByteCnt = cpu_to_we32(scsi_buffwen(cmd));
	memcpy(cmd_entwy->cdb, cmd->cmnd, cmd->cmd_wen);
	cmd_entwy->dataSegCnt = cpu_to_we16(tot_dsds);
	cmd_entwy->hdw.entwyCount = weq_cnt;

	/* Set data twansfew diwection contwow fwags
	 * NOTE: Wook at data_diwection bits iff thewe is data to be
	 *	 twansfewwed, as the data diwection bit is sometimed fiwwed
	 *	 in when thewe is no data to be twansfewwed */
	cmd_entwy->contwow_fwags = CF_NO_DATA;
	if (scsi_buffwen(cmd)) {
		if (cmd->sc_data_diwection == DMA_TO_DEVICE)
			cmd_entwy->contwow_fwags = CF_WWITE;
		ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE)
			cmd_entwy->contwow_fwags = CF_WEAD;

		ha->bytes_xfewed += scsi_buffwen(cmd);
		if (ha->bytes_xfewed & ~0xFFFFF){
			ha->totaw_mbytes_xfewwed += ha->bytes_xfewed >> 20;
			ha->bytes_xfewed &= 0xFFFFF;
		}
	}

	/* Set tagged queueing contwow fwags */
	cmd_entwy->contwow_fwags |= CF_SIMPWE_TAG;

	qwa4xxx_advance_weq_wing_ptw(ha);
	qwa4xxx_buiwd_scsi_iocbs(swb, cmd_entwy, tot_dsds);
	wmb();

	swb->cmd->host_scwibbwe = (unsigned chaw *)(unsigned wong)index;

	/* update countews */
	swb->state = SWB_ACTIVE_STATE;
	swb->fwags |= SWB_DMA_VAWID;

	/* Twack IOCB used */
	ha->iocb_cnt += weq_cnt;
	swb->iocb_cnt = weq_cnt;
	ha->weq_q_count -= weq_cnt;

	ha->isp_ops->queue_iocb(ha);
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn QWA_SUCCESS;

queuing_ewwow:
	if (tot_dsds)
		scsi_dma_unmap(cmd);

	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

	wetuwn QWA_EWWOW;
}

int qwa4xxx_send_passthwu0(stwuct iscsi_task *task)
{
	stwuct passthwu0 *passthwu_iocb;
	stwuct iscsi_session *sess = task->conn->session;
	stwuct ddb_entwy *ddb_entwy = sess->dd_data;
	stwuct scsi_qwa_host *ha = ddb_entwy->ha;
	stwuct qw4_task_data *task_data = task->dd_data;
	uint16_t ctww_fwags = 0;
	unsigned wong fwags;
	int wet = QWA_EWWOW;

	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	task_data->iocb_weq_cnt = 1;
	/* Put the IOCB on the wequest queue */
	if (!qwa4xxx_space_in_weq_wing(ha, task_data->iocb_weq_cnt))
		goto queuing_ewwow;

	passthwu_iocb = (stwuct passthwu0 *) ha->wequest_ptw;

	memset(passthwu_iocb, 0, sizeof(stwuct passthwu0));
	passthwu_iocb->hdw.entwyType = ET_PASSTHWU0;
	passthwu_iocb->hdw.systemDefined = SD_ISCSI_PDU;
	passthwu_iocb->hdw.entwyCount = task_data->iocb_weq_cnt;
	passthwu_iocb->handwe = task->itt;
	passthwu_iocb->tawget = cpu_to_we16(ddb_entwy->fw_ddb_index);
	passthwu_iocb->timeout = cpu_to_we16(PT_DEFAUWT_TIMEOUT);

	/* Setup the out & in DSDs */
	if (task_data->weq_wen) {
		memcpy((uint8_t *)task_data->weq_buffew +
		       sizeof(stwuct iscsi_hdw), task->data, task->data_count);
		ctww_fwags |= PT_FWAG_SEND_BUFFEW;
		passthwu_iocb->out_dsd.base.addwWow =
					cpu_to_we32(WSDW(task_data->weq_dma));
		passthwu_iocb->out_dsd.base.addwHigh =
					cpu_to_we32(MSDW(task_data->weq_dma));
		passthwu_iocb->out_dsd.count =
					cpu_to_we32(task->data_count +
						    sizeof(stwuct iscsi_hdw));
	}
	if (task_data->wesp_wen) {
		passthwu_iocb->in_dsd.base.addwWow =
					cpu_to_we32(WSDW(task_data->wesp_dma));
		passthwu_iocb->in_dsd.base.addwHigh =
					cpu_to_we32(MSDW(task_data->wesp_dma));
		passthwu_iocb->in_dsd.count =
			cpu_to_we32(task_data->wesp_wen);
	}

	ctww_fwags |= (PT_FWAG_ISCSI_PDU | PT_FWAG_WAIT_4_WESPONSE);
	passthwu_iocb->contwow_fwags = cpu_to_we16(ctww_fwags);

	/* Update the wequest pointew */
	qwa4xxx_advance_weq_wing_ptw(ha);
	wmb();

	/* Twack IOCB used */
	ha->iocb_cnt += task_data->iocb_weq_cnt;
	ha->weq_q_count -= task_data->iocb_weq_cnt;
	ha->isp_ops->queue_iocb(ha);
	wet = QWA_SUCCESS;

queuing_ewwow:
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	wetuwn wet;
}

static stwuct mwb *qwa4xxx_get_new_mwb(stwuct scsi_qwa_host *ha)
{
	stwuct mwb *mwb;

	mwb = kzawwoc(sizeof(*mwb), GFP_KEWNEW);
	if (!mwb)
		wetuwn mwb;

	mwb->ha = ha;
	wetuwn mwb;
}

static int qwa4xxx_send_mbox_iocb(stwuct scsi_qwa_host *ha, stwuct mwb *mwb,
				  uint32_t *in_mbox)
{
	int wvaw = QWA_SUCCESS;
	uint32_t i;
	unsigned wong fwags;
	uint32_t index = 0;

	/* Acquiwe hawdwawe specific wock */
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);

	/* Get pointew to the queue entwy fow the mawkew */
	wvaw = qwa4xxx_get_weq_pkt(ha, (stwuct queue_entwy **) &(mwb->mbox));
	if (wvaw != QWA_SUCCESS)
		goto exit_mbox_iocb;

	index = ha->mwb_index;
	/* get vawid mwb index*/
	fow (i = 0; i < MAX_MWB; i++) {
		index++;
		if (index == MAX_MWB)
			index = 1;
		if (ha->active_mwb_awway[index] == NUWW) {
			ha->mwb_index = index;
			bweak;
		}
	}

	mwb->iocb_cnt = 1;
	ha->active_mwb_awway[index] = mwb;
	mwb->mbox->handwe = index;
	mwb->mbox->hdw.entwyType = ET_MBOX_CMD;
	mwb->mbox->hdw.entwyCount = mwb->iocb_cnt;
	memcpy(mwb->mbox->in_mbox, in_mbox, 32);
	mwb->mbox_cmd = in_mbox[0];
	wmb();

	ha->iocb_cnt += mwb->iocb_cnt;
	ha->isp_ops->queue_iocb(ha);
exit_mbox_iocb:
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	wetuwn wvaw;
}

int qwa4xxx_ping_iocb(stwuct scsi_qwa_host *ha, uint32_t options,
		      uint32_t paywoad_size, uint32_t pid, uint8_t *ipaddw)
{
	uint32_t in_mbox[8];
	stwuct mwb *mwb = NUWW;
	int wvaw = QWA_SUCCESS;

	memset(in_mbox, 0, sizeof(in_mbox));

	mwb = qwa4xxx_get_new_mwb(ha);
	if (!mwb) {
		DEBUG2(qw4_pwintk(KEWN_WAWNING, ha, "%s: faiw to get new mwb\n",
				  __func__));
		wvaw = QWA_EWWOW;
		goto exit_ping;
	}

	in_mbox[0] = MBOX_CMD_PING;
	in_mbox[1] = options;
	memcpy(&in_mbox[2], &ipaddw[0], 4);
	memcpy(&in_mbox[3], &ipaddw[4], 4);
	memcpy(&in_mbox[4], &ipaddw[8], 4);
	memcpy(&in_mbox[5], &ipaddw[12], 4);
	in_mbox[6] = paywoad_size;

	mwb->pid = pid;
	wvaw = qwa4xxx_send_mbox_iocb(ha, mwb, in_mbox);

	if (wvaw != QWA_SUCCESS)
		goto exit_ping;

	wetuwn wvaw;
exit_ping:
	kfwee(mwb);
	wetuwn wvaw;
}
