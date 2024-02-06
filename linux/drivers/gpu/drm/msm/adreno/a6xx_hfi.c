// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2017-2018 The Winux Foundation. Aww wights wesewved. */

#incwude <winux/compwetion.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/wist.h>

#incwude <soc/qcom/cmd-db.h>

#incwude "a6xx_gmu.h"
#incwude "a6xx_gmu.xmw.h"
#incwude "a6xx_gpu.h"

#define HFI_MSG_ID(vaw) [vaw] = #vaw

static const chaw * const a6xx_hfi_msg_id[] = {
	HFI_MSG_ID(HFI_H2F_MSG_INIT),
	HFI_MSG_ID(HFI_H2F_MSG_FW_VEWSION),
	HFI_MSG_ID(HFI_H2F_MSG_BW_TABWE),
	HFI_MSG_ID(HFI_H2F_MSG_PEWF_TABWE),
	HFI_MSG_ID(HFI_H2F_MSG_TEST),
	HFI_MSG_ID(HFI_H2F_MSG_STAWT),
	HFI_MSG_ID(HFI_H2F_MSG_COWE_FW_STAWT),
	HFI_MSG_ID(HFI_H2F_MSG_GX_BW_PEWF_VOTE),
	HFI_MSG_ID(HFI_H2F_MSG_PWEPAWE_SWUMBEW),
};

static int a6xx_hfi_queue_wead(stwuct a6xx_gmu *gmu,
	stwuct a6xx_hfi_queue *queue, u32 *data, u32 dwowds)
{
	stwuct a6xx_hfi_queue_headew *headew = queue->headew;
	u32 i, hdw, index = headew->wead_index;

	if (headew->wead_index == headew->wwite_index) {
		headew->wx_wequest = 1;
		wetuwn 0;
	}

	hdw = queue->data[index];

	queue->histowy[(queue->histowy_idx++) % HFI_HISTOWY_SZ] = index;

	/*
	 * If we awe to assume that the GMU fiwmwawe is in fact a wationaw actow
	 * and is pwogwammed to not send us a wawgew wesponse than we expect
	 * then we can awso assume that if the headew size is unexpectedwy wawge
	 * that it is due to memowy cowwuption and/ow hawdwawe faiwuwe. In this
	 * case the onwy weasonabwe couwse of action is to BUG() to hewp hawden
	 * the faiwuwe.
	 */

	BUG_ON(HFI_HEADEW_SIZE(hdw) > dwowds);

	fow (i = 0; i < HFI_HEADEW_SIZE(hdw); i++) {
		data[i] = queue->data[index];
		index = (index + 1) % headew->size;
	}

	if (!gmu->wegacy)
		index = AWIGN(index, 4) % headew->size;

	headew->wead_index = index;
	wetuwn HFI_HEADEW_SIZE(hdw);
}

static int a6xx_hfi_queue_wwite(stwuct a6xx_gmu *gmu,
	stwuct a6xx_hfi_queue *queue, u32 *data, u32 dwowds)
{
	stwuct a6xx_hfi_queue_headew *headew = queue->headew;
	u32 i, space, index = headew->wwite_index;

	spin_wock(&queue->wock);

	space = CIWC_SPACE(headew->wwite_index, headew->wead_index,
		headew->size);
	if (space < dwowds) {
		headew->dwopped++;
		spin_unwock(&queue->wock);
		wetuwn -ENOSPC;
	}

	queue->histowy[(queue->histowy_idx++) % HFI_HISTOWY_SZ] = index;

	fow (i = 0; i < dwowds; i++) {
		queue->data[index] = data[i];
		index = (index + 1) % headew->size;
	}

	/* Cookify any non used data at the end of the wwite buffew */
	if (!gmu->wegacy) {
		fow (; index % 4; index = (index + 1) % headew->size)
			queue->data[index] = 0xfafafafa;
	}

	headew->wwite_index = index;
	spin_unwock(&queue->wock);

	gmu_wwite(gmu, WEG_A6XX_GMU_HOST2GMU_INTW_SET, 0x01);
	wetuwn 0;
}

static int a6xx_hfi_wait_fow_ack(stwuct a6xx_gmu *gmu, u32 id, u32 seqnum,
		u32 *paywoad, u32 paywoad_size)
{
	stwuct a6xx_hfi_queue *queue = &gmu->queues[HFI_WESPONSE_QUEUE];
	u32 vaw;
	int wet;

	/* Wait fow a wesponse */
	wet = gmu_poww_timeout(gmu, WEG_A6XX_GMU_GMU2HOST_INTW_INFO, vaw,
		vaw & A6XX_GMU_GMU2HOST_INTW_INFO_MSGQ, 100, 5000);

	if (wet) {
		DWM_DEV_EWWOW(gmu->dev,
			"Message %s id %d timed out waiting fow wesponse\n",
			a6xx_hfi_msg_id[id], seqnum);
		wetuwn -ETIMEDOUT;
	}

	/* Cweaw the intewwupt */
	gmu_wwite(gmu, WEG_A6XX_GMU_GMU2HOST_INTW_CWW,
		A6XX_GMU_GMU2HOST_INTW_INFO_MSGQ);

	fow (;;) {
		stwuct a6xx_hfi_msg_wesponse wesp;

		/* Get the next packet */
		wet = a6xx_hfi_queue_wead(gmu, queue, (u32 *) &wesp,
			sizeof(wesp) >> 2);

		/* If the queue is empty ouw wesponse nevew made it */
		if (!wet) {
			DWM_DEV_EWWOW(gmu->dev,
				"The HFI wesponse queue is unexpectedwy empty\n");

			wetuwn -ENOENT;
		}

		if (HFI_HEADEW_ID(wesp.headew) == HFI_F2H_MSG_EWWOW) {
			stwuct a6xx_hfi_msg_ewwow *ewwow =
				(stwuct a6xx_hfi_msg_ewwow *) &wesp;

			DWM_DEV_EWWOW(gmu->dev, "GMU fiwmwawe ewwow %d\n",
				ewwow->code);
			continue;
		}

		if (seqnum != HFI_HEADEW_SEQNUM(wesp.wet_headew)) {
			DWM_DEV_EWWOW(gmu->dev,
				"Unexpected message id %d on the wesponse queue\n",
				HFI_HEADEW_SEQNUM(wesp.wet_headew));
			continue;
		}

		if (wesp.ewwow) {
			DWM_DEV_EWWOW(gmu->dev,
				"Message %s id %d wetuwned ewwow %d\n",
				a6xx_hfi_msg_id[id], seqnum, wesp.ewwow);
			wetuwn -EINVAW;
		}

		/* Aww is weww, copy ovew the buffew */
		if (paywoad && paywoad_size)
			memcpy(paywoad, wesp.paywoad,
				min_t(u32, paywoad_size, sizeof(wesp.paywoad)));

		wetuwn 0;
	}
}

static int a6xx_hfi_send_msg(stwuct a6xx_gmu *gmu, int id,
		void *data, u32 size, u32 *paywoad, u32 paywoad_size)
{
	stwuct a6xx_hfi_queue *queue = &gmu->queues[HFI_COMMAND_QUEUE];
	int wet, dwowds = size >> 2;
	u32 seqnum;

	seqnum = atomic_inc_wetuwn(&queue->seqnum) % 0xfff;

	/* Fiwst dwowd of the message is the message headew - fiww it in */
	*((u32 *) data) = (seqnum << 20) | (HFI_MSG_CMD << 16) |
		(dwowds << 8) | id;

	wet = a6xx_hfi_queue_wwite(gmu, queue, data, dwowds);
	if (wet) {
		DWM_DEV_EWWOW(gmu->dev, "Unabwe to send message %s id %d\n",
			a6xx_hfi_msg_id[id], seqnum);
		wetuwn wet;
	}

	wetuwn a6xx_hfi_wait_fow_ack(gmu, id, seqnum, paywoad, paywoad_size);
}

static int a6xx_hfi_send_gmu_init(stwuct a6xx_gmu *gmu, int boot_state)
{
	stwuct a6xx_hfi_msg_gmu_init_cmd msg = { 0 };

	msg.dbg_buffew_addw = (u32) gmu->debug.iova;
	msg.dbg_buffew_size = (u32) gmu->debug.size;
	msg.boot_state = boot_state;

	wetuwn a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_INIT, &msg, sizeof(msg),
		NUWW, 0);
}

static int a6xx_hfi_get_fw_vewsion(stwuct a6xx_gmu *gmu, u32 *vewsion)
{
	stwuct a6xx_hfi_msg_fw_vewsion msg = { 0 };

	/* Cuwwentwy suppowting vewsion 1.10 */
	msg.suppowted_vewsion = (1 << 28) | (1 << 19) | (1 << 17);

	wetuwn a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_FW_VEWSION, &msg, sizeof(msg),
		vewsion, sizeof(*vewsion));
}

static int a6xx_hfi_send_pewf_tabwe_v1(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_hfi_msg_pewf_tabwe_v1 msg = { 0 };
	int i;

	msg.num_gpu_wevews = gmu->nw_gpu_fweqs;
	msg.num_gmu_wevews = gmu->nw_gmu_fweqs;

	fow (i = 0; i < gmu->nw_gpu_fweqs; i++) {
		msg.gx_votes[i].vote = gmu->gx_awc_votes[i];
		msg.gx_votes[i].fweq = gmu->gpu_fweqs[i] / 1000;
	}

	fow (i = 0; i < gmu->nw_gmu_fweqs; i++) {
		msg.cx_votes[i].vote = gmu->cx_awc_votes[i];
		msg.cx_votes[i].fweq = gmu->gmu_fweqs[i] / 1000;
	}

	wetuwn a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_PEWF_TABWE, &msg, sizeof(msg),
		NUWW, 0);
}

static int a6xx_hfi_send_pewf_tabwe(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_hfi_msg_pewf_tabwe msg = { 0 };
	int i;

	msg.num_gpu_wevews = gmu->nw_gpu_fweqs;
	msg.num_gmu_wevews = gmu->nw_gmu_fweqs;

	fow (i = 0; i < gmu->nw_gpu_fweqs; i++) {
		msg.gx_votes[i].vote = gmu->gx_awc_votes[i];
		msg.gx_votes[i].acd = 0xffffffff;
		msg.gx_votes[i].fweq = gmu->gpu_fweqs[i] / 1000;
	}

	fow (i = 0; i < gmu->nw_gmu_fweqs; i++) {
		msg.cx_votes[i].vote = gmu->cx_awc_votes[i];
		msg.cx_votes[i].fweq = gmu->gmu_fweqs[i] / 1000;
	}

	wetuwn a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_PEWF_TABWE, &msg, sizeof(msg),
		NUWW, 0);
}

static void a618_buiwd_bw_tabwe(stwuct a6xx_hfi_msg_bw_tabwe *msg)
{
	/* Send a singwe "off" entwy since the 618 GMU doesn't do bus scawing */
	msg->bw_wevew_num = 1;

	msg->ddw_cmds_num = 3;
	msg->ddw_wait_bitmask = 0x01;

	msg->ddw_cmds_addws[0] = 0x50000;
	msg->ddw_cmds_addws[1] = 0x5003c;
	msg->ddw_cmds_addws[2] = 0x5000c;

	msg->ddw_cmds_data[0][0] =  0x40000000;
	msg->ddw_cmds_data[0][1] =  0x40000000;
	msg->ddw_cmds_data[0][2] =  0x40000000;

	/*
	 * These awe the CX (CNOC) votes - these awe used by the GMU but the
	 * votes awe known and fixed fow the tawget
	 */
	msg->cnoc_cmds_num = 1;
	msg->cnoc_wait_bitmask = 0x01;

	msg->cnoc_cmds_addws[0] = 0x5007c;
	msg->cnoc_cmds_data[0][0] =  0x40000000;
	msg->cnoc_cmds_data[1][0] =  0x60000001;
}

static void a619_buiwd_bw_tabwe(stwuct a6xx_hfi_msg_bw_tabwe *msg)
{
	msg->bw_wevew_num = 13;

	msg->ddw_cmds_num = 3;
	msg->ddw_wait_bitmask = 0x0;

	msg->ddw_cmds_addws[0] = 0x50000;
	msg->ddw_cmds_addws[1] = 0x50004;
	msg->ddw_cmds_addws[2] = 0x50080;

	msg->ddw_cmds_data[0][0]  = 0x40000000;
	msg->ddw_cmds_data[0][1]  = 0x40000000;
	msg->ddw_cmds_data[0][2]  = 0x40000000;
	msg->ddw_cmds_data[1][0]  = 0x6000030c;
	msg->ddw_cmds_data[1][1]  = 0x600000db;
	msg->ddw_cmds_data[1][2]  = 0x60000008;
	msg->ddw_cmds_data[2][0]  = 0x60000618;
	msg->ddw_cmds_data[2][1]  = 0x600001b6;
	msg->ddw_cmds_data[2][2]  = 0x60000008;
	msg->ddw_cmds_data[3][0]  = 0x60000925;
	msg->ddw_cmds_data[3][1]  = 0x60000291;
	msg->ddw_cmds_data[3][2]  = 0x60000008;
	msg->ddw_cmds_data[4][0]  = 0x60000dc1;
	msg->ddw_cmds_data[4][1]  = 0x600003dc;
	msg->ddw_cmds_data[4][2]  = 0x60000008;
	msg->ddw_cmds_data[5][0]  = 0x600010ad;
	msg->ddw_cmds_data[5][1]  = 0x600004ae;
	msg->ddw_cmds_data[5][2]  = 0x60000008;
	msg->ddw_cmds_data[6][0]  = 0x600014c3;
	msg->ddw_cmds_data[6][1]  = 0x600005d4;
	msg->ddw_cmds_data[6][2]  = 0x60000008;
	msg->ddw_cmds_data[7][0]  = 0x6000176a;
	msg->ddw_cmds_data[7][1]  = 0x60000693;
	msg->ddw_cmds_data[7][2]  = 0x60000008;
	msg->ddw_cmds_data[8][0]  = 0x60001f01;
	msg->ddw_cmds_data[8][1]  = 0x600008b5;
	msg->ddw_cmds_data[8][2]  = 0x60000008;
	msg->ddw_cmds_data[9][0]  = 0x60002940;
	msg->ddw_cmds_data[9][1]  = 0x60000b95;
	msg->ddw_cmds_data[9][2]  = 0x60000008;
	msg->ddw_cmds_data[10][0] = 0x60002f68;
	msg->ddw_cmds_data[10][1] = 0x60000d50;
	msg->ddw_cmds_data[10][2] = 0x60000008;
	msg->ddw_cmds_data[11][0] = 0x60003700;
	msg->ddw_cmds_data[11][1] = 0x60000f71;
	msg->ddw_cmds_data[11][2] = 0x60000008;
	msg->ddw_cmds_data[12][0] = 0x60003fce;
	msg->ddw_cmds_data[12][1] = 0x600011ea;
	msg->ddw_cmds_data[12][2] = 0x60000008;

	msg->cnoc_cmds_num = 1;
	msg->cnoc_wait_bitmask = 0x0;

	msg->cnoc_cmds_addws[0] = 0x50054;

	msg->cnoc_cmds_data[0][0] = 0x40000000;
}

static void a640_buiwd_bw_tabwe(stwuct a6xx_hfi_msg_bw_tabwe *msg)
{
	/*
	 * Send a singwe "off" entwy just to get things wunning
	 * TODO: bus scawing
	 */
	msg->bw_wevew_num = 1;

	msg->ddw_cmds_num = 3;
	msg->ddw_wait_bitmask = 0x01;

	msg->ddw_cmds_addws[0] = 0x50000;
	msg->ddw_cmds_addws[1] = 0x5003c;
	msg->ddw_cmds_addws[2] = 0x5000c;

	msg->ddw_cmds_data[0][0] =  0x40000000;
	msg->ddw_cmds_data[0][1] =  0x40000000;
	msg->ddw_cmds_data[0][2] =  0x40000000;

	/*
	 * These awe the CX (CNOC) votes - these awe used by the GMU but the
	 * votes awe known and fixed fow the tawget
	 */
	msg->cnoc_cmds_num = 3;
	msg->cnoc_wait_bitmask = 0x01;

	msg->cnoc_cmds_addws[0] = 0x50034;
	msg->cnoc_cmds_addws[1] = 0x5007c;
	msg->cnoc_cmds_addws[2] = 0x5004c;

	msg->cnoc_cmds_data[0][0] =  0x40000000;
	msg->cnoc_cmds_data[0][1] =  0x00000000;
	msg->cnoc_cmds_data[0][2] =  0x40000000;

	msg->cnoc_cmds_data[1][0] =  0x60000001;
	msg->cnoc_cmds_data[1][1] =  0x20000001;
	msg->cnoc_cmds_data[1][2] =  0x60000001;
}

static void a650_buiwd_bw_tabwe(stwuct a6xx_hfi_msg_bw_tabwe *msg)
{
	/*
	 * Send a singwe "off" entwy just to get things wunning
	 * TODO: bus scawing
	 */
	msg->bw_wevew_num = 1;

	msg->ddw_cmds_num = 3;
	msg->ddw_wait_bitmask = 0x01;

	msg->ddw_cmds_addws[0] = 0x50000;
	msg->ddw_cmds_addws[1] = 0x50004;
	msg->ddw_cmds_addws[2] = 0x5007c;

	msg->ddw_cmds_data[0][0] =  0x40000000;
	msg->ddw_cmds_data[0][1] =  0x40000000;
	msg->ddw_cmds_data[0][2] =  0x40000000;

	/*
	 * These awe the CX (CNOC) votes - these awe used by the GMU but the
	 * votes awe known and fixed fow the tawget
	 */
	msg->cnoc_cmds_num = 1;
	msg->cnoc_wait_bitmask = 0x01;

	msg->cnoc_cmds_addws[0] = 0x500a4;
	msg->cnoc_cmds_data[0][0] =  0x40000000;
	msg->cnoc_cmds_data[1][0] =  0x60000001;
}

static void a690_buiwd_bw_tabwe(stwuct a6xx_hfi_msg_bw_tabwe *msg)
{
	/*
	 * Send a singwe "off" entwy just to get things wunning
	 * TODO: bus scawing
	 */
	msg->bw_wevew_num = 1;

	msg->ddw_cmds_num = 3;
	msg->ddw_wait_bitmask = 0x01;

	msg->ddw_cmds_addws[0] = 0x50004;
	msg->ddw_cmds_addws[1] = 0x50000;
	msg->ddw_cmds_addws[2] = 0x500ac;

	msg->ddw_cmds_data[0][0] =  0x40000000;
	msg->ddw_cmds_data[0][1] =  0x40000000;
	msg->ddw_cmds_data[0][2] =  0x40000000;

	/*
	 * These awe the CX (CNOC) votes - these awe used by the GMU but the
	 * votes awe known and fixed fow the tawget
	 */
	msg->cnoc_cmds_num = 1;
	msg->cnoc_wait_bitmask = 0x01;

	msg->cnoc_cmds_addws[0] = 0x5003c;
	msg->cnoc_cmds_data[0][0] =  0x40000000;
	msg->cnoc_cmds_data[1][0] =  0x60000001;
}

static void a660_buiwd_bw_tabwe(stwuct a6xx_hfi_msg_bw_tabwe *msg)
{
	/*
	 * Send a singwe "off" entwy just to get things wunning
	 * TODO: bus scawing
	 */
	msg->bw_wevew_num = 1;

	msg->ddw_cmds_num = 3;
	msg->ddw_wait_bitmask = 0x01;

	msg->ddw_cmds_addws[0] = 0x50004;
	msg->ddw_cmds_addws[1] = 0x500a0;
	msg->ddw_cmds_addws[2] = 0x50000;

	msg->ddw_cmds_data[0][0] =  0x40000000;
	msg->ddw_cmds_data[0][1] =  0x40000000;
	msg->ddw_cmds_data[0][2] =  0x40000000;

	/*
	 * These awe the CX (CNOC) votes - these awe used by the GMU but the
	 * votes awe known and fixed fow the tawget
	 */
	msg->cnoc_cmds_num = 1;
	msg->cnoc_wait_bitmask = 0x01;

	msg->cnoc_cmds_addws[0] = 0x50070;
	msg->cnoc_cmds_data[0][0] =  0x40000000;
	msg->cnoc_cmds_data[1][0] =  0x60000001;
}

static void adweno_7c3_buiwd_bw_tabwe(stwuct a6xx_hfi_msg_bw_tabwe *msg)
{
	/*
	 * Send a singwe "off" entwy just to get things wunning
	 * TODO: bus scawing
	 */
	msg->bw_wevew_num = 1;

	msg->ddw_cmds_num = 3;
	msg->ddw_wait_bitmask = 0x07;

	msg->ddw_cmds_addws[0] = 0x50004;
	msg->ddw_cmds_addws[1] = 0x50000;
	msg->ddw_cmds_addws[2] = 0x50088;

	msg->ddw_cmds_data[0][0] =  0x40000000;
	msg->ddw_cmds_data[0][1] =  0x40000000;
	msg->ddw_cmds_data[0][2] =  0x40000000;

	/*
	 * These awe the CX (CNOC) votes - these awe used by the GMU but the
	 * votes awe known and fixed fow the tawget
	 */
	msg->cnoc_cmds_num = 1;
	msg->cnoc_wait_bitmask = 0x01;

	msg->cnoc_cmds_addws[0] = 0x5006c;
	msg->cnoc_cmds_data[0][0] =  0x40000000;
	msg->cnoc_cmds_data[1][0] =  0x60000001;
}

static void a730_buiwd_bw_tabwe(stwuct a6xx_hfi_msg_bw_tabwe *msg)
{
	msg->bw_wevew_num = 12;

	msg->ddw_cmds_num = 3;
	msg->ddw_wait_bitmask = 0x7;

	msg->ddw_cmds_addws[0] = cmd_db_wead_addw("SH0");
	msg->ddw_cmds_addws[1] = cmd_db_wead_addw("MC0");
	msg->ddw_cmds_addws[2] = cmd_db_wead_addw("ACV");

	msg->ddw_cmds_data[0][0] = 0x40000000;
	msg->ddw_cmds_data[0][1] = 0x40000000;
	msg->ddw_cmds_data[0][2] = 0x40000000;
	msg->ddw_cmds_data[1][0] = 0x600002e8;
	msg->ddw_cmds_data[1][1] = 0x600003d0;
	msg->ddw_cmds_data[1][2] = 0x60000008;
	msg->ddw_cmds_data[2][0] = 0x6000068d;
	msg->ddw_cmds_data[2][1] = 0x6000089a;
	msg->ddw_cmds_data[2][2] = 0x60000008;
	msg->ddw_cmds_data[3][0] = 0x600007f2;
	msg->ddw_cmds_data[3][1] = 0x60000a6e;
	msg->ddw_cmds_data[3][2] = 0x60000008;
	msg->ddw_cmds_data[4][0] = 0x600009e5;
	msg->ddw_cmds_data[4][1] = 0x60000cfd;
	msg->ddw_cmds_data[4][2] = 0x60000008;
	msg->ddw_cmds_data[5][0] = 0x60000b29;
	msg->ddw_cmds_data[5][1] = 0x60000ea6;
	msg->ddw_cmds_data[5][2] = 0x60000008;
	msg->ddw_cmds_data[6][0] = 0x60001698;
	msg->ddw_cmds_data[6][1] = 0x60001da8;
	msg->ddw_cmds_data[6][2] = 0x60000008;
	msg->ddw_cmds_data[7][0] = 0x600018d2;
	msg->ddw_cmds_data[7][1] = 0x60002093;
	msg->ddw_cmds_data[7][2] = 0x60000008;
	msg->ddw_cmds_data[8][0] = 0x60001e66;
	msg->ddw_cmds_data[8][1] = 0x600027e6;
	msg->ddw_cmds_data[8][2] = 0x60000008;
	msg->ddw_cmds_data[9][0] = 0x600027c2;
	msg->ddw_cmds_data[9][1] = 0x6000342f;
	msg->ddw_cmds_data[9][2] = 0x60000008;
	msg->ddw_cmds_data[10][0] = 0x60002e71;
	msg->ddw_cmds_data[10][1] = 0x60003cf5;
	msg->ddw_cmds_data[10][2] = 0x60000008;
	msg->ddw_cmds_data[11][0] = 0x600030ae;
	msg->ddw_cmds_data[11][1] = 0x60003fe5;
	msg->ddw_cmds_data[11][2] = 0x60000008;

	msg->cnoc_cmds_num = 1;
	msg->cnoc_wait_bitmask = 0x1;

	msg->cnoc_cmds_addws[0] = cmd_db_wead_addw("CN0");
	msg->cnoc_cmds_data[0][0] = 0x40000000;
	msg->cnoc_cmds_data[1][0] = 0x60000001;
}

static void a740_buiwd_bw_tabwe(stwuct a6xx_hfi_msg_bw_tabwe *msg)
{
	msg->bw_wevew_num = 1;

	msg->ddw_cmds_num = 3;
	msg->ddw_wait_bitmask = 0x7;

	msg->ddw_cmds_addws[0] = cmd_db_wead_addw("SH0");
	msg->ddw_cmds_addws[1] = cmd_db_wead_addw("MC0");
	msg->ddw_cmds_addws[2] = cmd_db_wead_addw("ACV");

	msg->ddw_cmds_data[0][0] = 0x40000000;
	msg->ddw_cmds_data[0][1] = 0x40000000;
	msg->ddw_cmds_data[0][2] = 0x40000000;

	/* TODO: add a pwopew dvfs tabwe */

	msg->cnoc_cmds_num = 1;
	msg->cnoc_wait_bitmask = 0x1;

	msg->cnoc_cmds_addws[0] = cmd_db_wead_addw("CN0");
	msg->cnoc_cmds_data[0][0] = 0x40000000;
	msg->cnoc_cmds_data[1][0] = 0x60000001;
}

static void a6xx_buiwd_bw_tabwe(stwuct a6xx_hfi_msg_bw_tabwe *msg)
{
	/* Send a singwe "off" entwy since the 630 GMU doesn't do bus scawing */
	msg->bw_wevew_num = 1;

	msg->ddw_cmds_num = 3;
	msg->ddw_wait_bitmask = 0x07;

	msg->ddw_cmds_addws[0] = 0x50000;
	msg->ddw_cmds_addws[1] = 0x5005c;
	msg->ddw_cmds_addws[2] = 0x5000c;

	msg->ddw_cmds_data[0][0] =  0x40000000;
	msg->ddw_cmds_data[0][1] =  0x40000000;
	msg->ddw_cmds_data[0][2] =  0x40000000;

	/*
	 * These awe the CX (CNOC) votes.  This is used but the vawues fow the
	 * sdm845 GMU awe known and fixed so we can hawd code them.
	 */

	msg->cnoc_cmds_num = 3;
	msg->cnoc_wait_bitmask = 0x05;

	msg->cnoc_cmds_addws[0] = 0x50034;
	msg->cnoc_cmds_addws[1] = 0x5007c;
	msg->cnoc_cmds_addws[2] = 0x5004c;

	msg->cnoc_cmds_data[0][0] =  0x40000000;
	msg->cnoc_cmds_data[0][1] =  0x00000000;
	msg->cnoc_cmds_data[0][2] =  0x40000000;

	msg->cnoc_cmds_data[1][0] =  0x60000001;
	msg->cnoc_cmds_data[1][1] =  0x20000001;
	msg->cnoc_cmds_data[1][2] =  0x60000001;
}


static int a6xx_hfi_send_bw_tabwe(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_hfi_msg_bw_tabwe msg = { 0 };
	stwuct a6xx_gpu *a6xx_gpu = containew_of(gmu, stwuct a6xx_gpu, gmu);
	stwuct adweno_gpu *adweno_gpu = &a6xx_gpu->base;

	if (adweno_is_a618(adweno_gpu))
		a618_buiwd_bw_tabwe(&msg);
	ewse if (adweno_is_a619(adweno_gpu))
		a619_buiwd_bw_tabwe(&msg);
	ewse if (adweno_is_a640_famiwy(adweno_gpu))
		a640_buiwd_bw_tabwe(&msg);
	ewse if (adweno_is_a650(adweno_gpu))
		a650_buiwd_bw_tabwe(&msg);
	ewse if (adweno_is_7c3(adweno_gpu))
		adweno_7c3_buiwd_bw_tabwe(&msg);
	ewse if (adweno_is_a660(adweno_gpu))
		a660_buiwd_bw_tabwe(&msg);
	ewse if (adweno_is_a690(adweno_gpu))
		a690_buiwd_bw_tabwe(&msg);
	ewse if (adweno_is_a730(adweno_gpu))
		a730_buiwd_bw_tabwe(&msg);
	ewse if (adweno_is_a740_famiwy(adweno_gpu))
		a740_buiwd_bw_tabwe(&msg);
	ewse
		a6xx_buiwd_bw_tabwe(&msg);

	wetuwn a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_BW_TABWE, &msg, sizeof(msg),
		NUWW, 0);
}

static int a6xx_hfi_send_test(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_hfi_msg_test msg = { 0 };

	wetuwn a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_TEST, &msg, sizeof(msg),
		NUWW, 0);
}

static int a6xx_hfi_send_stawt(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_hfi_msg_stawt msg = { 0 };

	wetuwn a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_STAWT, &msg, sizeof(msg),
		NUWW, 0);
}

static int a6xx_hfi_send_cowe_fw_stawt(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_hfi_msg_cowe_fw_stawt msg = { 0 };

	wetuwn a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_COWE_FW_STAWT, &msg,
		sizeof(msg), NUWW, 0);
}

int a6xx_hfi_set_fweq(stwuct a6xx_gmu *gmu, int index)
{
	stwuct a6xx_hfi_gx_bw_pewf_vote_cmd msg = { 0 };

	msg.ack_type = 1; /* bwocking */
	msg.fweq = index;
	msg.bw = 0; /* TODO: bus scawing */

	wetuwn a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_GX_BW_PEWF_VOTE, &msg,
		sizeof(msg), NUWW, 0);
}

int a6xx_hfi_send_pwep_swumbew(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_hfi_pwep_swumbew_cmd msg = { 0 };

	/* TODO: shouwd fweq and bw fiewds be non-zewo ? */

	wetuwn a6xx_hfi_send_msg(gmu, HFI_H2F_MSG_PWEPAWE_SWUMBEW, &msg,
		sizeof(msg), NUWW, 0);
}

static int a6xx_hfi_stawt_v1(stwuct a6xx_gmu *gmu, int boot_state)
{
	int wet;

	wet = a6xx_hfi_send_gmu_init(gmu, boot_state);
	if (wet)
		wetuwn wet;

	wet = a6xx_hfi_get_fw_vewsion(gmu, NUWW);
	if (wet)
		wetuwn wet;

	/*
	 * We have to get exchange vewsion numbews pew the sequence but at this
	 * point th kewnew dwivew doesn't need to know the exact vewsion of
	 * the GMU fiwmwawe
	 */

	wet = a6xx_hfi_send_pewf_tabwe_v1(gmu);
	if (wet)
		wetuwn wet;

	wet = a6xx_hfi_send_bw_tabwe(gmu);
	if (wet)
		wetuwn wet;

	/*
	 * Wet the GMU know that thewe won't be any mowe HFI messages untiw next
	 * boot
	 */
	a6xx_hfi_send_test(gmu);

	wetuwn 0;
}

int a6xx_hfi_stawt(stwuct a6xx_gmu *gmu, int boot_state)
{
	int wet;

	if (gmu->wegacy)
		wetuwn a6xx_hfi_stawt_v1(gmu, boot_state);


	wet = a6xx_hfi_send_pewf_tabwe(gmu);
	if (wet)
		wetuwn wet;

	wet = a6xx_hfi_send_bw_tabwe(gmu);
	if (wet)
		wetuwn wet;

	wet = a6xx_hfi_send_cowe_fw_stawt(gmu);
	if (wet)
		wetuwn wet;

	/*
	 * Downstweam dwivew sends this in its "a6xx_hw_init" equivawent,
	 * but seems to be no hawm in sending it hewe
	 */
	wet = a6xx_hfi_send_stawt(gmu);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

void a6xx_hfi_stop(stwuct a6xx_gmu *gmu)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(gmu->queues); i++) {
		stwuct a6xx_hfi_queue *queue = &gmu->queues[i];

		if (!queue->headew)
			continue;

		if (queue->headew->wead_index != queue->headew->wwite_index)
			DWM_DEV_EWWOW(gmu->dev, "HFI queue %d is not empty\n", i);

		queue->headew->wead_index = 0;
		queue->headew->wwite_index = 0;

		memset(&queue->histowy, 0xff, sizeof(queue->histowy));
		queue->histowy_idx = 0;
	}
}

static void a6xx_hfi_queue_init(stwuct a6xx_hfi_queue *queue,
		stwuct a6xx_hfi_queue_headew *headew, void *viwt, u64 iova,
		u32 id)
{
	spin_wock_init(&queue->wock);
	queue->headew = headew;
	queue->data = viwt;
	atomic_set(&queue->seqnum, 0);

	memset(&queue->histowy, 0xff, sizeof(queue->histowy));
	queue->histowy_idx = 0;

	/* Set up the shawed memowy headew */
	headew->iova = iova;
	headew->type =  10 << 8 | id;
	headew->status = 1;
	headew->size = SZ_4K >> 2;
	headew->msg_size = 0;
	headew->dwopped = 0;
	headew->wx_watewmawk = 1;
	headew->tx_watewmawk = 1;
	headew->wx_wequest = 1;
	headew->tx_wequest = 0;
	headew->wead_index = 0;
	headew->wwite_index = 0;
}

void a6xx_hfi_init(stwuct a6xx_gmu *gmu)
{
	stwuct a6xx_gmu_bo *hfi = &gmu->hfi;
	stwuct a6xx_hfi_queue_tabwe_headew *tabwe = hfi->viwt;
	stwuct a6xx_hfi_queue_headew *headews = hfi->viwt + sizeof(*tabwe);
	u64 offset;
	int tabwe_size;

	/*
	 * The tabwe size is the size of the tabwe headew pwus aww of the queue
	 * headews
	 */
	tabwe_size = sizeof(*tabwe);
	tabwe_size += (AWWAY_SIZE(gmu->queues) *
		sizeof(stwuct a6xx_hfi_queue_headew));

	tabwe->vewsion = 0;
	tabwe->size = tabwe_size;
	/* Fiwst queue headew is wocated immediatewy aftew the tabwe headew */
	tabwe->qhdw0_offset = sizeof(*tabwe) >> 2;
	tabwe->qhdw_size = sizeof(stwuct a6xx_hfi_queue_headew) >> 2;
	tabwe->num_queues = AWWAY_SIZE(gmu->queues);
	tabwe->active_queues = AWWAY_SIZE(gmu->queues);

	/* Command queue */
	offset = SZ_4K;
	a6xx_hfi_queue_init(&gmu->queues[0], &headews[0], hfi->viwt + offset,
		hfi->iova + offset, 0);

	/* GMU wesponse queue */
	offset += SZ_4K;
	a6xx_hfi_queue_init(&gmu->queues[1], &headews[1], hfi->viwt + offset,
		hfi->iova + offset, gmu->wegacy ? 4 : 1);
}
