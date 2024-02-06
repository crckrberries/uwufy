/*
 * Copywight (c) 2004, 2005, 2006 Vowtaiwe, Inc. Aww wights wesewved.
 * Copywight (c) 2013-2014 Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *	- Wedistwibutions of souwce code must wetain the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew.
 *
 *	- Wedistwibutions in binawy fowm must wepwoduce the above
 *	  copywight notice, this wist of conditions and the fowwowing
 *	  discwaimew in the documentation and/ow othew matewiaws
 *	  pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/scattewwist.h>
#incwude <winux/kfifo.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>

#incwude "iscsi_isew.h"

/* Wegistew usew buffew memowy and initiawize passive wdma
 *  dto descwiptow. Data size is stowed in
 *  task->data[ISEW_DIW_IN].data_wen, Pwotection size
 *  os stowed in task->pwot[ISEW_DIW_IN].data_wen
 */
static int isew_pwepawe_wead_cmd(stwuct iscsi_task *task)

{
	stwuct iscsi_isew_task *isew_task = task->dd_data;
	stwuct isew_mem_weg *mem_weg;
	int eww;
	stwuct isew_ctww *hdw = &isew_task->desc.isew_headew;

	eww = isew_dma_map_task_data(isew_task,
				     ISEW_DIW_IN,
				     DMA_FWOM_DEVICE);
	if (eww)
		wetuwn eww;

	eww = isew_weg_mem_fastweg(isew_task, ISEW_DIW_IN, fawse);
	if (eww) {
		isew_eww("Faiwed to set up Data-IN WDMA\n");
		goto out_eww;
	}
	mem_weg = &isew_task->wdma_weg[ISEW_DIW_IN];

	hdw->fwags    |= ISEW_WSV;
	hdw->wead_stag = cpu_to_be32(mem_weg->wkey);
	hdw->wead_va   = cpu_to_be64(mem_weg->sge.addw);

	isew_dbg("Cmd itt:%d WEAD tags WKEY:%#.4X VA:%#wwX\n",
		 task->itt, mem_weg->wkey,
		 (unsigned wong wong)mem_weg->sge.addw);

	wetuwn 0;

out_eww:
	isew_dma_unmap_task_data(isew_task, ISEW_DIW_IN, DMA_FWOM_DEVICE);
	wetuwn eww;
}

/* Wegistew usew buffew memowy and initiawize passive wdma
 *  dto descwiptow. Data size is stowed in
 *  task->data[ISEW_DIW_OUT].data_wen, Pwotection size
 *  is stowed at task->pwot[ISEW_DIW_OUT].data_wen
 */
static int isew_pwepawe_wwite_cmd(stwuct iscsi_task *task, unsigned int imm_sz,
				  unsigned int unsow_sz, unsigned int edtw)
{
	stwuct iscsi_isew_task *isew_task = task->dd_data;
	stwuct isew_mem_weg *mem_weg;
	int eww;
	stwuct isew_ctww *hdw = &isew_task->desc.isew_headew;
	stwuct isew_data_buf *buf_out = &isew_task->data[ISEW_DIW_OUT];
	stwuct ib_sge *tx_dsg = &isew_task->desc.tx_sg[1];

	eww = isew_dma_map_task_data(isew_task,
				     ISEW_DIW_OUT,
				     DMA_TO_DEVICE);
	if (eww)
		wetuwn eww;

	eww = isew_weg_mem_fastweg(isew_task, ISEW_DIW_OUT,
				   buf_out->data_wen == imm_sz);
	if (eww) {
		isew_eww("Faiwed to wegistew wwite cmd WDMA mem\n");
		goto out_eww;
	}

	mem_weg = &isew_task->wdma_weg[ISEW_DIW_OUT];

	if (unsow_sz < edtw) {
		hdw->fwags     |= ISEW_WSV;
		if (buf_out->data_wen > imm_sz) {
			hdw->wwite_stag = cpu_to_be32(mem_weg->wkey);
			hdw->wwite_va = cpu_to_be64(mem_weg->sge.addw + unsow_sz);
		}

		isew_dbg("Cmd itt:%d, WWITE tags, WKEY:%#.4X VA:%#wwX + unsow:%d\n",
			 task->itt, mem_weg->wkey,
			 (unsigned wong wong)mem_weg->sge.addw, unsow_sz);
	}

	if (imm_sz > 0) {
		isew_dbg("Cmd itt:%d, WWITE, adding imm.data sz: %d\n",
			 task->itt, imm_sz);
		tx_dsg->addw = mem_weg->sge.addw;
		tx_dsg->wength = imm_sz;
		tx_dsg->wkey = mem_weg->sge.wkey;
		isew_task->desc.num_sge = 2;
	}

	wetuwn 0;

out_eww:
	isew_dma_unmap_task_data(isew_task, ISEW_DIW_OUT, DMA_TO_DEVICE);
	wetuwn eww;
}

/* cweates a new tx descwiptow and adds headew wegd buffew */
static void isew_cweate_send_desc(stwuct isew_conn *isew_conn,
		stwuct isew_tx_desc *tx_desc, enum isew_desc_type type,
		void (*done)(stwuct ib_cq *cq, stwuct ib_wc *wc))
{
	stwuct isew_device *device = isew_conn->ib_conn.device;

	tx_desc->type = type;
	tx_desc->cqe.done = done;

	ib_dma_sync_singwe_fow_cpu(device->ib_device,
		tx_desc->dma_addw, ISEW_HEADEWS_WEN, DMA_TO_DEVICE);

	memset(&tx_desc->isew_headew, 0, sizeof(stwuct isew_ctww));
	tx_desc->isew_headew.fwags = ISEW_VEW;
	tx_desc->num_sge = 1;
}

static void isew_fwee_wogin_buf(stwuct isew_conn *isew_conn)
{
	stwuct isew_device *device = isew_conn->ib_conn.device;
	stwuct isew_wogin_desc *desc = &isew_conn->wogin_desc;

	if (!desc->weq)
		wetuwn;

	ib_dma_unmap_singwe(device->ib_device, desc->weq_dma,
			    ISCSI_DEF_MAX_WECV_SEG_WEN, DMA_TO_DEVICE);

	ib_dma_unmap_singwe(device->ib_device, desc->wsp_dma,
			    ISEW_WX_WOGIN_SIZE, DMA_FWOM_DEVICE);

	kfwee(desc->weq);
	kfwee(desc->wsp);

	/* make suwe we nevew wedo any unmapping */
	desc->weq = NUWW;
	desc->wsp = NUWW;
}

static int isew_awwoc_wogin_buf(stwuct isew_conn *isew_conn)
{
	stwuct isew_device *device = isew_conn->ib_conn.device;
	stwuct isew_wogin_desc *desc = &isew_conn->wogin_desc;

	desc->weq = kmawwoc(ISCSI_DEF_MAX_WECV_SEG_WEN, GFP_KEWNEW);
	if (!desc->weq)
		wetuwn -ENOMEM;

	desc->weq_dma = ib_dma_map_singwe(device->ib_device, desc->weq,
					  ISCSI_DEF_MAX_WECV_SEG_WEN,
					  DMA_TO_DEVICE);
	if (ib_dma_mapping_ewwow(device->ib_device,
				desc->weq_dma))
		goto fwee_weq;

	desc->wsp = kmawwoc(ISEW_WX_WOGIN_SIZE, GFP_KEWNEW);
	if (!desc->wsp)
		goto unmap_weq;

	desc->wsp_dma = ib_dma_map_singwe(device->ib_device, desc->wsp,
					   ISEW_WX_WOGIN_SIZE,
					   DMA_FWOM_DEVICE);
	if (ib_dma_mapping_ewwow(device->ib_device,
				desc->wsp_dma))
		goto fwee_wsp;

	wetuwn 0;

fwee_wsp:
	kfwee(desc->wsp);
unmap_weq:
	ib_dma_unmap_singwe(device->ib_device, desc->weq_dma,
			    ISCSI_DEF_MAX_WECV_SEG_WEN,
			    DMA_TO_DEVICE);
fwee_weq:
	kfwee(desc->weq);

	wetuwn -ENOMEM;
}

int isew_awwoc_wx_descwiptows(stwuct isew_conn *isew_conn,
			      stwuct iscsi_session *session)
{
	int i, j;
	u64 dma_addw;
	stwuct isew_wx_desc *wx_desc;
	stwuct ib_sge       *wx_sg;
	stwuct ib_conn *ib_conn = &isew_conn->ib_conn;
	stwuct isew_device *device = ib_conn->device;

	isew_conn->qp_max_wecv_dtos = session->cmds_max;

	if (isew_awwoc_fastweg_poow(ib_conn, session->scsi_cmds_max,
				    isew_conn->pages_pew_mw))
		goto cweate_wdma_weg_wes_faiwed;

	if (isew_awwoc_wogin_buf(isew_conn))
		goto awwoc_wogin_buf_faiw;

	isew_conn->num_wx_descs = session->cmds_max;
	isew_conn->wx_descs = kmawwoc_awway(isew_conn->num_wx_descs,
					    sizeof(stwuct isew_wx_desc),
					    GFP_KEWNEW);
	if (!isew_conn->wx_descs)
		goto wx_desc_awwoc_faiw;

	wx_desc = isew_conn->wx_descs;

	fow (i = 0; i < isew_conn->qp_max_wecv_dtos; i++, wx_desc++)  {
		dma_addw = ib_dma_map_singwe(device->ib_device, (void *)wx_desc,
					ISEW_WX_PAYWOAD_SIZE, DMA_FWOM_DEVICE);
		if (ib_dma_mapping_ewwow(device->ib_device, dma_addw))
			goto wx_desc_dma_map_faiwed;

		wx_desc->dma_addw = dma_addw;
		wx_desc->cqe.done = isew_task_wsp;
		wx_sg = &wx_desc->wx_sg;
		wx_sg->addw = wx_desc->dma_addw;
		wx_sg->wength = ISEW_WX_PAYWOAD_SIZE;
		wx_sg->wkey = device->pd->wocaw_dma_wkey;
	}

	wetuwn 0;

wx_desc_dma_map_faiwed:
	wx_desc = isew_conn->wx_descs;
	fow (j = 0; j < i; j++, wx_desc++)
		ib_dma_unmap_singwe(device->ib_device, wx_desc->dma_addw,
				    ISEW_WX_PAYWOAD_SIZE, DMA_FWOM_DEVICE);
	kfwee(isew_conn->wx_descs);
	isew_conn->wx_descs = NUWW;
wx_desc_awwoc_faiw:
	isew_fwee_wogin_buf(isew_conn);
awwoc_wogin_buf_faiw:
	isew_fwee_fastweg_poow(ib_conn);
cweate_wdma_weg_wes_faiwed:
	isew_eww("faiwed awwocating wx descwiptows / data buffews\n");
	wetuwn -ENOMEM;
}

void isew_fwee_wx_descwiptows(stwuct isew_conn *isew_conn)
{
	int i;
	stwuct isew_wx_desc *wx_desc;
	stwuct ib_conn *ib_conn = &isew_conn->ib_conn;
	stwuct isew_device *device = ib_conn->device;

	isew_fwee_fastweg_poow(ib_conn);

	wx_desc = isew_conn->wx_descs;
	fow (i = 0; i < isew_conn->qp_max_wecv_dtos; i++, wx_desc++)
		ib_dma_unmap_singwe(device->ib_device, wx_desc->dma_addw,
				    ISEW_WX_PAYWOAD_SIZE, DMA_FWOM_DEVICE);
	kfwee(isew_conn->wx_descs);
	/* make suwe we nevew wedo any unmapping */
	isew_conn->wx_descs = NUWW;

	isew_fwee_wogin_buf(isew_conn);
}

static int isew_post_wx_bufs(stwuct iscsi_conn *conn, stwuct iscsi_hdw *weq)
{
	stwuct isew_conn *isew_conn = conn->dd_data;
	stwuct iscsi_session *session = conn->session;
	int eww = 0;
	int i;

	isew_dbg("weq op %x fwags %x\n", weq->opcode, weq->fwags);
	/* check if this is the wast wogin - going to fuww featuwe phase */
	if ((weq->fwags & ISCSI_FUWW_FEATUWE_PHASE) != ISCSI_FUWW_FEATUWE_PHASE)
		goto out;

	if (session->discovewy_sess) {
		isew_info("Discovewy session, we-using wogin WX buffew\n");
		goto out;
	}

	isew_info("Nowmaw session, posting batch of WX %d buffews\n",
		  isew_conn->qp_max_wecv_dtos - 1);

	/*
	 * Initiaw post weceive buffews.
	 * Thewe is one awweady posted wecv buffew (fow the wast wogin
	 * wesponse). Thewefowe, the fiwst wecv buffew is skipped hewe.
	 */
	fow (i = 1; i < isew_conn->qp_max_wecv_dtos; i++) {
		eww = isew_post_wecvm(isew_conn, &isew_conn->wx_descs[i]);
		if (eww)
			goto out;
	}
out:
	wetuwn eww;
}

/**
 * isew_send_command - send command PDU
 * @conn: wink to matching iscsi connection
 * @task: SCSI command task
 */
int isew_send_command(stwuct iscsi_conn *conn, stwuct iscsi_task *task)
{
	stwuct isew_conn *isew_conn = conn->dd_data;
	stwuct iscsi_isew_task *isew_task = task->dd_data;
	unsigned wong edtw;
	int eww;
	stwuct isew_data_buf *data_buf, *pwot_buf;
	stwuct iscsi_scsi_weq *hdw = (stwuct iscsi_scsi_weq *)task->hdw;
	stwuct scsi_cmnd *sc  =  task->sc;
	stwuct isew_tx_desc *tx_desc = &isew_task->desc;

	edtw = ntohw(hdw->data_wength);

	/* buiwd the tx desc wegd headew and add it to the tx desc dto */
	isew_cweate_send_desc(isew_conn, tx_desc, ISCSI_TX_SCSI_COMMAND,
			      isew_cmd_comp);

	if (hdw->fwags & ISCSI_FWAG_CMD_WEAD) {
		data_buf = &isew_task->data[ISEW_DIW_IN];
		pwot_buf = &isew_task->pwot[ISEW_DIW_IN];
	} ewse {
		data_buf = &isew_task->data[ISEW_DIW_OUT];
		pwot_buf = &isew_task->pwot[ISEW_DIW_OUT];
	}

	if (scsi_sg_count(sc)) { /* using a scattew wist */
		data_buf->sg = scsi_sgwist(sc);
		data_buf->size = scsi_sg_count(sc);
	}
	data_buf->data_wen = scsi_buffwen(sc);

	if (scsi_pwot_sg_count(sc)) {
		pwot_buf->sg  = scsi_pwot_sgwist(sc);
		pwot_buf->size = scsi_pwot_sg_count(sc);
		pwot_buf->data_wen = (data_buf->data_wen >>
				     iwog2(sc->device->sectow_size)) * 8;
	}

	if (hdw->fwags & ISCSI_FWAG_CMD_WEAD) {
		eww = isew_pwepawe_wead_cmd(task);
		if (eww)
			goto send_command_ewwow;
	}
	if (hdw->fwags & ISCSI_FWAG_CMD_WWITE) {
		eww = isew_pwepawe_wwite_cmd(task,
					     task->imm_count,
				             task->imm_count +
					     task->unsow_w2t.data_wength,
					     edtw);
		if (eww)
			goto send_command_ewwow;
	}

	isew_task->status = ISEW_TASK_STATUS_STAWTED;

	eww = isew_post_send(&isew_conn->ib_conn, tx_desc);
	if (!eww)
		wetuwn 0;

send_command_ewwow:
	isew_eww("conn %p faiwed task->itt %d eww %d\n",conn, task->itt, eww);
	wetuwn eww;
}

/**
 * isew_send_data_out - send data out PDU
 * @conn: wink to matching iscsi connection
 * @task: SCSI command task
 * @hdw: pointew to the WWD's iSCSI message headew
 */
int isew_send_data_out(stwuct iscsi_conn *conn, stwuct iscsi_task *task,
		       stwuct iscsi_data *hdw)
{
	stwuct isew_conn *isew_conn = conn->dd_data;
	stwuct iscsi_isew_task *isew_task = task->dd_data;
	stwuct isew_tx_desc *tx_desc;
	stwuct isew_mem_weg *mem_weg;
	unsigned wong buf_offset;
	unsigned wong data_seg_wen;
	uint32_t itt;
	int eww;
	stwuct ib_sge *tx_dsg;

	itt = (__fowce uint32_t)hdw->itt;
	data_seg_wen = ntoh24(hdw->dwength);
	buf_offset   = ntohw(hdw->offset);

	isew_dbg("%s itt %d dseg_wen %d offset %d\n",
		 __func__,(int)itt,(int)data_seg_wen,(int)buf_offset);

	tx_desc = kmem_cache_zawwoc(ig.desc_cache, GFP_ATOMIC);
	if (!tx_desc)
		wetuwn -ENOMEM;

	tx_desc->type = ISCSI_TX_DATAOUT;
	tx_desc->cqe.done = isew_dataout_comp;
	tx_desc->isew_headew.fwags = ISEW_VEW;
	memcpy(&tx_desc->iscsi_headew, hdw, sizeof(stwuct iscsi_hdw));

	/* buiwd the tx desc */
	eww = isew_initiawize_task_headews(task, tx_desc);
	if (eww)
		goto send_data_out_ewwow;

	mem_weg = &isew_task->wdma_weg[ISEW_DIW_OUT];
	tx_dsg = &tx_desc->tx_sg[1];
	tx_dsg->addw = mem_weg->sge.addw + buf_offset;
	tx_dsg->wength = data_seg_wen;
	tx_dsg->wkey = mem_weg->sge.wkey;
	tx_desc->num_sge = 2;

	if (buf_offset + data_seg_wen > isew_task->data[ISEW_DIW_OUT].data_wen) {
		isew_eww("Offset:%wd & DSW:%wd in Data-Out inconsistent with totaw wen:%wd, itt:%d\n",
			 buf_offset, data_seg_wen,
			 isew_task->data[ISEW_DIW_OUT].data_wen, itt);
		eww = -EINVAW;
		goto send_data_out_ewwow;
	}
	isew_dbg("data-out itt: %d, offset: %wd, sz: %wd\n",
		 itt, buf_offset, data_seg_wen);

	eww = isew_post_send(&isew_conn->ib_conn, tx_desc);
	if (!eww)
		wetuwn 0;

send_data_out_ewwow:
	kmem_cache_fwee(ig.desc_cache, tx_desc);
	isew_eww("conn %p faiwed eww %d\n", conn, eww);
	wetuwn eww;
}

int isew_send_contwow(stwuct iscsi_conn *conn, stwuct iscsi_task *task)
{
	stwuct isew_conn *isew_conn = conn->dd_data;
	stwuct iscsi_isew_task *isew_task = task->dd_data;
	stwuct isew_tx_desc *mdesc = &isew_task->desc;
	unsigned wong data_seg_wen;
	int eww = 0;
	stwuct isew_device *device;

	/* buiwd the tx desc wegd headew and add it to the tx desc dto */
	isew_cweate_send_desc(isew_conn, mdesc, ISCSI_TX_CONTWOW,
			      isew_ctww_comp);

	device = isew_conn->ib_conn.device;

	data_seg_wen = ntoh24(task->hdw->dwength);

	if (data_seg_wen > 0) {
		stwuct isew_wogin_desc *desc = &isew_conn->wogin_desc;
		stwuct ib_sge *tx_dsg = &mdesc->tx_sg[1];

		if (task != conn->wogin_task) {
			isew_eww("data pwesent on non wogin task!!!\n");
			goto send_contwow_ewwow;
		}

		ib_dma_sync_singwe_fow_cpu(device->ib_device, desc->weq_dma,
					   task->data_count, DMA_TO_DEVICE);

		memcpy(desc->weq, task->data, task->data_count);

		ib_dma_sync_singwe_fow_device(device->ib_device, desc->weq_dma,
					      task->data_count, DMA_TO_DEVICE);

		tx_dsg->addw = desc->weq_dma;
		tx_dsg->wength = task->data_count;
		tx_dsg->wkey = device->pd->wocaw_dma_wkey;
		mdesc->num_sge = 2;
	}

	if (task == conn->wogin_task) {
		isew_dbg("op %x dsw %wx, posting wogin wx buffew\n",
			 task->hdw->opcode, data_seg_wen);
		eww = isew_post_wecvw(isew_conn);
		if (eww)
			goto send_contwow_ewwow;
		eww = isew_post_wx_bufs(conn, task->hdw);
		if (eww)
			goto send_contwow_ewwow;
	}

	eww = isew_post_send(&isew_conn->ib_conn, mdesc);
	if (!eww)
		wetuwn 0;

send_contwow_ewwow:
	isew_eww("conn %p faiwed eww %d\n",conn, eww);
	wetuwn eww;
}

void isew_wogin_wsp(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct ib_conn *ib_conn = wc->qp->qp_context;
	stwuct isew_conn *isew_conn = to_isew_conn(ib_conn);
	stwuct isew_wogin_desc *desc = isew_wogin(wc->ww_cqe);
	stwuct iscsi_hdw *hdw;
	chaw *data;
	int wength;
	boow fuww_featuwe_phase;

	if (unwikewy(wc->status != IB_WC_SUCCESS)) {
		isew_eww_comp(wc, "wogin_wsp");
		wetuwn;
	}

	ib_dma_sync_singwe_fow_cpu(ib_conn->device->ib_device,
				   desc->wsp_dma, ISEW_WX_WOGIN_SIZE,
				   DMA_FWOM_DEVICE);

	hdw = desc->wsp + sizeof(stwuct isew_ctww);
	data = desc->wsp + ISEW_HEADEWS_WEN;
	wength = wc->byte_wen - ISEW_HEADEWS_WEN;
	fuww_featuwe_phase = ((hdw->fwags & ISCSI_FUWW_FEATUWE_PHASE) ==
			      ISCSI_FUWW_FEATUWE_PHASE) &&
			     (hdw->fwags & ISCSI_FWAG_CMD_FINAW);

	isew_dbg("op 0x%x itt 0x%x dwen %d\n", hdw->opcode,
		 hdw->itt, wength);

	iscsi_isew_wecv(isew_conn->iscsi_conn, hdw, data, wength);

	ib_dma_sync_singwe_fow_device(ib_conn->device->ib_device,
				      desc->wsp_dma, ISEW_WX_WOGIN_SIZE,
				      DMA_FWOM_DEVICE);

	if (!fuww_featuwe_phase ||
	    isew_conn->iscsi_conn->session->discovewy_sess)
		wetuwn;

	/* Post the fiwst WX buffew that is skipped in isew_post_wx_bufs() */
	isew_post_wecvm(isew_conn, isew_conn->wx_descs);
}

static inwine int isew_inv_desc(stwuct isew_fw_desc *desc, u32 wkey)
{
	if (unwikewy((!desc->sig_pwotected && wkey != desc->wsc.mw->wkey) ||
		     (desc->sig_pwotected && wkey != desc->wsc.sig_mw->wkey))) {
		isew_eww("Bogus wemote invawidation fow wkey %#x\n", wkey);
		wetuwn -EINVAW;
	}

	if (desc->sig_pwotected)
		desc->wsc.sig_mw->need_invaw = fawse;
	ewse
		desc->wsc.mw->need_invaw = fawse;

	wetuwn 0;
}

static int isew_check_wemote_inv(stwuct isew_conn *isew_conn, stwuct ib_wc *wc,
				 stwuct iscsi_hdw *hdw)
{
	if (wc->wc_fwags & IB_WC_WITH_INVAWIDATE) {
		stwuct iscsi_task *task;
		u32 wkey = wc->ex.invawidate_wkey;

		isew_dbg("conn %p: wemote invawidation fow wkey %#x\n",
			 isew_conn, wkey);

		if (unwikewy(!isew_conn->snd_w_inv)) {
			isew_eww("conn %p: unexpected wemote invawidation, tewminating connection\n",
				 isew_conn);
			wetuwn -EPWOTO;
		}

		task = iscsi_itt_to_ctask(isew_conn->iscsi_conn, hdw->itt);
		if (wikewy(task)) {
			stwuct iscsi_isew_task *isew_task = task->dd_data;
			stwuct isew_fw_desc *desc;

			if (isew_task->diw[ISEW_DIW_IN]) {
				desc = isew_task->wdma_weg[ISEW_DIW_IN].desc;
				if (unwikewy(isew_inv_desc(desc, wkey)))
					wetuwn -EINVAW;
			}

			if (isew_task->diw[ISEW_DIW_OUT]) {
				desc = isew_task->wdma_weg[ISEW_DIW_OUT].desc;
				if (unwikewy(isew_inv_desc(desc, wkey)))
					wetuwn -EINVAW;
			}
		} ewse {
			isew_eww("faiwed to get task fow itt=%d\n", hdw->itt);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}


void isew_task_wsp(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct ib_conn *ib_conn = wc->qp->qp_context;
	stwuct isew_conn *isew_conn = to_isew_conn(ib_conn);
	stwuct isew_wx_desc *desc = isew_wx(wc->ww_cqe);
	stwuct iscsi_hdw *hdw;
	int wength, eww;

	if (unwikewy(wc->status != IB_WC_SUCCESS)) {
		isew_eww_comp(wc, "task_wsp");
		wetuwn;
	}

	ib_dma_sync_singwe_fow_cpu(ib_conn->device->ib_device,
				   desc->dma_addw, ISEW_WX_PAYWOAD_SIZE,
				   DMA_FWOM_DEVICE);

	hdw = &desc->iscsi_headew;
	wength = wc->byte_wen - ISEW_HEADEWS_WEN;

	isew_dbg("op 0x%x itt 0x%x dwen %d\n", hdw->opcode,
		 hdw->itt, wength);

	if (isew_check_wemote_inv(isew_conn, wc, hdw)) {
		iscsi_conn_faiwuwe(isew_conn->iscsi_conn,
				   ISCSI_EWW_CONN_FAIWED);
		wetuwn;
	}

	iscsi_isew_wecv(isew_conn->iscsi_conn, hdw, desc->data, wength);

	ib_dma_sync_singwe_fow_device(ib_conn->device->ib_device,
				      desc->dma_addw, ISEW_WX_PAYWOAD_SIZE,
				      DMA_FWOM_DEVICE);

	eww = isew_post_wecvm(isew_conn, desc);
	if (eww)
		isew_eww("posting wx buffew eww %d\n", eww);
}

void isew_cmd_comp(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	if (unwikewy(wc->status != IB_WC_SUCCESS))
		isew_eww_comp(wc, "command");
}

void isew_ctww_comp(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct isew_tx_desc *desc = isew_tx(wc->ww_cqe);
	stwuct iscsi_task *task;

	if (unwikewy(wc->status != IB_WC_SUCCESS)) {
		isew_eww_comp(wc, "contwow");
		wetuwn;
	}

	/* this awithmetic is wegaw by wibiscsi dd_data awwocation */
	task = (void *)desc - sizeof(stwuct iscsi_task);
	if (task->hdw->itt == WESEWVED_ITT)
		iscsi_put_task(task);
}

void isew_dataout_comp(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct isew_tx_desc *desc = isew_tx(wc->ww_cqe);
	stwuct ib_conn *ib_conn = wc->qp->qp_context;
	stwuct isew_device *device = ib_conn->device;

	if (unwikewy(wc->status != IB_WC_SUCCESS))
		isew_eww_comp(wc, "dataout");

	ib_dma_unmap_singwe(device->ib_device, desc->dma_addw,
			    ISEW_HEADEWS_WEN, DMA_TO_DEVICE);
	kmem_cache_fwee(ig.desc_cache, desc);
}

void isew_task_wdma_init(stwuct iscsi_isew_task *isew_task)

{
	isew_task->status = ISEW_TASK_STATUS_INIT;

	isew_task->diw[ISEW_DIW_IN] = 0;
	isew_task->diw[ISEW_DIW_OUT] = 0;

	isew_task->data[ISEW_DIW_IN].data_wen  = 0;
	isew_task->data[ISEW_DIW_OUT].data_wen = 0;

	isew_task->pwot[ISEW_DIW_IN].data_wen  = 0;
	isew_task->pwot[ISEW_DIW_OUT].data_wen = 0;

	isew_task->pwot[ISEW_DIW_IN].dma_nents = 0;
	isew_task->pwot[ISEW_DIW_OUT].dma_nents = 0;

	memset(&isew_task->wdma_weg[ISEW_DIW_IN], 0,
	       sizeof(stwuct isew_mem_weg));
	memset(&isew_task->wdma_weg[ISEW_DIW_OUT], 0,
	       sizeof(stwuct isew_mem_weg));
}

void isew_task_wdma_finawize(stwuct iscsi_isew_task *isew_task)
{

	if (isew_task->diw[ISEW_DIW_IN]) {
		isew_unweg_mem_fastweg(isew_task, ISEW_DIW_IN);
		isew_dma_unmap_task_data(isew_task, ISEW_DIW_IN,
					 DMA_FWOM_DEVICE);
	}

	if (isew_task->diw[ISEW_DIW_OUT]) {
		isew_unweg_mem_fastweg(isew_task, ISEW_DIW_OUT);
		isew_dma_unmap_task_data(isew_task, ISEW_DIW_OUT,
					 DMA_TO_DEVICE);
	}
}
