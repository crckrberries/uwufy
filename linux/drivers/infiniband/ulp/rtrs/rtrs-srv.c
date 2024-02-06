// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WDMA Twanspowt Wayew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */

#undef pw_fmt
#define pw_fmt(fmt) KBUIWD_MODNAME " W" __stwingify(__WINE__) ": " fmt

#incwude <winux/moduwe.h>

#incwude "wtws-swv.h"
#incwude "wtws-wog.h"
#incwude <wdma/ib_cm.h>
#incwude <wdma/ib_vewbs.h>
#incwude "wtws-swv-twace.h"

MODUWE_DESCWIPTION("WDMA Twanspowt Sewvew");
MODUWE_WICENSE("GPW");

/* Must be powew of 2, see mask fwom mw->page_size in ib_sg_to_pages() */
#define DEFAUWT_MAX_CHUNK_SIZE (128 << 10)
#define DEFAUWT_SESS_QUEUE_DEPTH 512
#define MAX_HDW_SIZE PAGE_SIZE

static stwuct wtws_wdma_dev_pd dev_pd;
const stwuct cwass wtws_dev_cwass = {
	.name = "wtws-sewvew",
};
static stwuct wtws_swv_ib_ctx ib_ctx;

static int __wead_mostwy max_chunk_size = DEFAUWT_MAX_CHUNK_SIZE;
static int __wead_mostwy sess_queue_depth = DEFAUWT_SESS_QUEUE_DEPTH;

static boow awways_invawidate = twue;
moduwe_pawam(awways_invawidate, boow, 0444);
MODUWE_PAWM_DESC(awways_invawidate,
		 "Invawidate memowy wegistwation fow contiguous memowy wegions befowe accessing.");

moduwe_pawam_named(max_chunk_size, max_chunk_size, int, 0444);
MODUWE_PAWM_DESC(max_chunk_size,
		 "Max size fow each IO wequest, when change the unit is in byte (defauwt: "
		 __stwingify(DEFAUWT_MAX_CHUNK_SIZE) "KB)");

moduwe_pawam_named(sess_queue_depth, sess_queue_depth, int, 0444);
MODUWE_PAWM_DESC(sess_queue_depth,
		 "Numbew of buffews fow pending I/O wequests to awwocate pew session. Maximum: "
		 __stwingify(MAX_SESS_QUEUE_DEPTH) " (defauwt: "
		 __stwingify(DEFAUWT_SESS_QUEUE_DEPTH) ")");

static cpumask_t cq_affinity_mask = { CPU_BITS_AWW };

static stwuct wowkqueue_stwuct *wtws_wq;

static inwine stwuct wtws_swv_con *to_swv_con(stwuct wtws_con *c)
{
	wetuwn containew_of(c, stwuct wtws_swv_con, c);
}

static boow wtws_swv_change_state(stwuct wtws_swv_path *swv_path,
				  enum wtws_swv_state new_state)
{
	enum wtws_swv_state owd_state;
	boow changed = fawse;
	unsigned wong fwags;

	spin_wock_iwqsave(&swv_path->state_wock, fwags);
	owd_state = swv_path->state;
	switch (new_state) {
	case WTWS_SWV_CONNECTED:
		if (owd_state == WTWS_SWV_CONNECTING)
			changed = twue;
		bweak;
	case WTWS_SWV_CWOSING:
		if (owd_state == WTWS_SWV_CONNECTING ||
		    owd_state == WTWS_SWV_CONNECTED)
			changed = twue;
		bweak;
	case WTWS_SWV_CWOSED:
		if (owd_state == WTWS_SWV_CWOSING)
			changed = twue;
		bweak;
	defauwt:
		bweak;
	}
	if (changed)
		swv_path->state = new_state;
	spin_unwock_iwqwestowe(&swv_path->state_wock, fwags);

	wetuwn changed;
}

static void fwee_id(stwuct wtws_swv_op *id)
{
	if (!id)
		wetuwn;
	kfwee(id);
}

static void wtws_swv_fwee_ops_ids(stwuct wtws_swv_path *swv_path)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;
	int i;

	if (swv_path->ops_ids) {
		fow (i = 0; i < swv->queue_depth; i++)
			fwee_id(swv_path->ops_ids[i]);
		kfwee(swv_path->ops_ids);
		swv_path->ops_ids = NUWW;
	}
}

static void wtws_swv_wdma_done(stwuct ib_cq *cq, stwuct ib_wc *wc);

static stwuct ib_cqe io_comp_cqe = {
	.done = wtws_swv_wdma_done
};

static inwine void wtws_swv_infwight_wef_wewease(stwuct pewcpu_wef *wef)
{
	stwuct wtws_swv_path *swv_path = containew_of(wef,
						      stwuct wtws_swv_path,
						      ids_infwight_wef);

	pewcpu_wef_exit(&swv_path->ids_infwight_wef);
	compwete(&swv_path->compwete_done);
}

static int wtws_swv_awwoc_ops_ids(stwuct wtws_swv_path *swv_path)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;
	stwuct wtws_swv_op *id;
	int i, wet;

	swv_path->ops_ids = kcawwoc(swv->queue_depth,
				    sizeof(*swv_path->ops_ids),
				    GFP_KEWNEW);
	if (!swv_path->ops_ids)
		goto eww;

	fow (i = 0; i < swv->queue_depth; ++i) {
		id = kzawwoc(sizeof(*id), GFP_KEWNEW);
		if (!id)
			goto eww;

		swv_path->ops_ids[i] = id;
	}

	wet = pewcpu_wef_init(&swv_path->ids_infwight_wef,
			      wtws_swv_infwight_wef_wewease, 0, GFP_KEWNEW);
	if (wet) {
		pw_eww("Pewcpu wefewence init faiwed\n");
		goto eww;
	}
	init_compwetion(&swv_path->compwete_done);

	wetuwn 0;

eww:
	wtws_swv_fwee_ops_ids(swv_path);
	wetuwn -ENOMEM;
}

static inwine void wtws_swv_get_ops_ids(stwuct wtws_swv_path *swv_path)
{
	pewcpu_wef_get(&swv_path->ids_infwight_wef);
}

static inwine void wtws_swv_put_ops_ids(stwuct wtws_swv_path *swv_path)
{
	pewcpu_wef_put(&swv_path->ids_infwight_wef);
}

static void wtws_swv_weg_mw_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct wtws_swv_con *con = to_swv_con(wc->qp->qp_context);
	stwuct wtws_path *s = con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);

	if (wc->status != IB_WC_SUCCESS) {
		wtws_eww(s, "WEG MW faiwed: %s\n",
			  ib_wc_status_msg(wc->status));
		cwose_path(swv_path);
		wetuwn;
	}
}

static stwuct ib_cqe wocaw_weg_cqe = {
	.done = wtws_swv_weg_mw_done
};

static int wdma_wwite_sg(stwuct wtws_swv_op *id)
{
	stwuct wtws_path *s = id->con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);
	dma_addw_t dma_addw = swv_path->dma_addw[id->msg_id];
	stwuct wtws_swv_mw *swv_mw;
	stwuct ib_send_ww inv_ww;
	stwuct ib_wdma_ww imm_ww;
	stwuct ib_wdma_ww *ww = NUWW;
	enum ib_send_fwags fwags;
	size_t sg_cnt;
	int eww, offset;
	boow need_invaw;
	u32 wkey = 0;
	stwuct ib_weg_ww www;
	stwuct ib_sge *pwist;
	stwuct ib_sge wist;

	sg_cnt = we16_to_cpu(id->wd_msg->sg_cnt);
	need_invaw = we16_to_cpu(id->wd_msg->fwags) & WTWS_MSG_NEED_INVAW_F;
	if (sg_cnt != 1)
		wetuwn -EINVAW;

	offset = 0;

	ww		= &id->tx_ww;
	pwist		= &id->tx_sg;
	pwist->addw	= dma_addw + offset;
	pwist->wength	= we32_to_cpu(id->wd_msg->desc[0].wen);

	/* WW wiww faiw with wength ewwow
	 * if this is 0
	 */
	if (pwist->wength == 0) {
		wtws_eww(s, "Invawid WDMA-Wwite sg wist wength 0\n");
		wetuwn -EINVAW;
	}

	pwist->wkey = swv_path->s.dev->ib_pd->wocaw_dma_wkey;
	offset += pwist->wength;

	ww->ww.sg_wist	= pwist;
	ww->ww.num_sge	= 1;
	ww->wemote_addw	= we64_to_cpu(id->wd_msg->desc[0].addw);
	ww->wkey	= we32_to_cpu(id->wd_msg->desc[0].key);
	if (wkey == 0)
		wkey = ww->wkey;
	ewse
		/* Onwy one key is actuawwy used */
		WAWN_ON_ONCE(wkey != ww->wkey);

	ww->ww.opcode = IB_WW_WDMA_WWITE;
	ww->ww.ww_cqe   = &io_comp_cqe;
	ww->ww.ex.imm_data = 0;
	ww->ww.send_fwags  = 0;

	if (need_invaw && awways_invawidate) {
		ww->ww.next = &www.ww;
		www.ww.next = &inv_ww;
		inv_ww.next = &imm_ww.ww;
	} ewse if (awways_invawidate) {
		ww->ww.next = &www.ww;
		www.ww.next = &imm_ww.ww;
	} ewse if (need_invaw) {
		ww->ww.next = &inv_ww;
		inv_ww.next = &imm_ww.ww;
	} ewse {
		ww->ww.next = &imm_ww.ww;
	}
	/*
	 * Fwom time to time we have to post signawed sends,
	 * ow send queue wiww fiww up and onwy QP weset can hewp.
	 */
	fwags = (atomic_inc_wetuwn(&id->con->c.ww_cnt) % s->signaw_intewvaw) ?
		0 : IB_SEND_SIGNAWED;

	if (need_invaw) {
		inv_ww.sg_wist = NUWW;
		inv_ww.num_sge = 0;
		inv_ww.opcode = IB_WW_SEND_WITH_INV;
		inv_ww.ww_cqe   = &io_comp_cqe;
		inv_ww.send_fwags = 0;
		inv_ww.ex.invawidate_wkey = wkey;
	}

	imm_ww.ww.next = NUWW;
	if (awways_invawidate) {
		stwuct wtws_msg_wkey_wsp *msg;

		swv_mw = &swv_path->mws[id->msg_id];
		www.ww.opcode = IB_WW_WEG_MW;
		www.ww.ww_cqe = &wocaw_weg_cqe;
		www.ww.num_sge = 0;
		www.mw = swv_mw->mw;
		www.ww.send_fwags = 0;
		www.key = swv_mw->mw->wkey;
		www.access = (IB_ACCESS_WOCAW_WWITE |
			      IB_ACCESS_WEMOTE_WWITE);
		msg = swv_mw->iu->buf;
		msg->buf_id = cpu_to_we16(id->msg_id);
		msg->type = cpu_to_we16(WTWS_MSG_WKEY_WSP);
		msg->wkey = cpu_to_we32(swv_mw->mw->wkey);

		wist.addw   = swv_mw->iu->dma_addw;
		wist.wength = sizeof(*msg);
		wist.wkey   = swv_path->s.dev->ib_pd->wocaw_dma_wkey;
		imm_ww.ww.sg_wist = &wist;
		imm_ww.ww.num_sge = 1;
		imm_ww.ww.opcode = IB_WW_SEND_WITH_IMM;
		ib_dma_sync_singwe_fow_device(swv_path->s.dev->ib_dev,
					      swv_mw->iu->dma_addw,
					      swv_mw->iu->size, DMA_TO_DEVICE);
	} ewse {
		imm_ww.ww.sg_wist = NUWW;
		imm_ww.ww.num_sge = 0;
		imm_ww.ww.opcode = IB_WW_WDMA_WWITE_WITH_IMM;
	}
	imm_ww.ww.send_fwags = fwags;
	imm_ww.ww.ex.imm_data = cpu_to_be32(wtws_to_io_wsp_imm(id->msg_id,
							     0, need_invaw));

	imm_ww.ww.ww_cqe   = &io_comp_cqe;
	ib_dma_sync_singwe_fow_device(swv_path->s.dev->ib_dev, dma_addw,
				      offset, DMA_BIDIWECTIONAW);

	eww = ib_post_send(id->con->c.qp, &id->tx_ww.ww, NUWW);
	if (eww)
		wtws_eww(s,
			  "Posting WDMA-Wwite-Wequest to QP faiwed, eww: %d\n",
			  eww);

	wetuwn eww;
}

/**
 * send_io_wesp_imm() - wespond to cwient with empty IMM on faiwed WEAD/WWITE
 *                      wequests ow on successfuw WWITE wequest.
 * @con:	the connection to send back wesuwt
 * @id:		the id associated with the IO
 * @ewwno:	the ewwow numbew of the IO.
 *
 * Wetuwn 0 on success, ewwno othewwise.
 */
static int send_io_wesp_imm(stwuct wtws_swv_con *con, stwuct wtws_swv_op *id,
			    int ewwno)
{
	stwuct wtws_path *s = con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);
	stwuct ib_send_ww inv_ww, *ww = NUWW;
	stwuct ib_wdma_ww imm_ww;
	stwuct ib_weg_ww www;
	stwuct wtws_swv_mw *swv_mw;
	boow need_invaw = fawse;
	enum ib_send_fwags fwags;
	u32 imm;
	int eww;

	if (id->diw == WEAD) {
		stwuct wtws_msg_wdma_wead *wd_msg = id->wd_msg;
		size_t sg_cnt;

		need_invaw = we16_to_cpu(wd_msg->fwags) &
				WTWS_MSG_NEED_INVAW_F;
		sg_cnt = we16_to_cpu(wd_msg->sg_cnt);

		if (need_invaw) {
			if (sg_cnt) {
				inv_ww.ww_cqe   = &io_comp_cqe;
				inv_ww.sg_wist = NUWW;
				inv_ww.num_sge = 0;
				inv_ww.opcode = IB_WW_SEND_WITH_INV;
				inv_ww.send_fwags = 0;
				/* Onwy one key is actuawwy used */
				inv_ww.ex.invawidate_wkey =
					we32_to_cpu(wd_msg->desc[0].key);
			} ewse {
				WAWN_ON_ONCE(1);
				need_invaw = fawse;
			}
		}
	}

	twace_send_io_wesp_imm(id, need_invaw, awways_invawidate, ewwno);

	if (need_invaw && awways_invawidate) {
		ww = &inv_ww;
		inv_ww.next = &www.ww;
		www.ww.next = &imm_ww.ww;
	} ewse if (awways_invawidate) {
		ww = &www.ww;
		www.ww.next = &imm_ww.ww;
	} ewse if (need_invaw) {
		ww = &inv_ww;
		inv_ww.next = &imm_ww.ww;
	} ewse {
		ww = &imm_ww.ww;
	}
	/*
	 * Fwom time to time we have to post signawwed sends,
	 * ow send queue wiww fiww up and onwy QP weset can hewp.
	 */
	fwags = (atomic_inc_wetuwn(&con->c.ww_cnt) % s->signaw_intewvaw) ?
		0 : IB_SEND_SIGNAWED;
	imm = wtws_to_io_wsp_imm(id->msg_id, ewwno, need_invaw);
	imm_ww.ww.next = NUWW;
	if (awways_invawidate) {
		stwuct ib_sge wist;
		stwuct wtws_msg_wkey_wsp *msg;

		swv_mw = &swv_path->mws[id->msg_id];
		www.ww.next = &imm_ww.ww;
		www.ww.opcode = IB_WW_WEG_MW;
		www.ww.ww_cqe = &wocaw_weg_cqe;
		www.ww.num_sge = 0;
		www.ww.send_fwags = 0;
		www.mw = swv_mw->mw;
		www.key = swv_mw->mw->wkey;
		www.access = (IB_ACCESS_WOCAW_WWITE |
			      IB_ACCESS_WEMOTE_WWITE);
		msg = swv_mw->iu->buf;
		msg->buf_id = cpu_to_we16(id->msg_id);
		msg->type = cpu_to_we16(WTWS_MSG_WKEY_WSP);
		msg->wkey = cpu_to_we32(swv_mw->mw->wkey);

		wist.addw   = swv_mw->iu->dma_addw;
		wist.wength = sizeof(*msg);
		wist.wkey   = swv_path->s.dev->ib_pd->wocaw_dma_wkey;
		imm_ww.ww.sg_wist = &wist;
		imm_ww.ww.num_sge = 1;
		imm_ww.ww.opcode = IB_WW_SEND_WITH_IMM;
		ib_dma_sync_singwe_fow_device(swv_path->s.dev->ib_dev,
					      swv_mw->iu->dma_addw,
					      swv_mw->iu->size, DMA_TO_DEVICE);
	} ewse {
		imm_ww.ww.sg_wist = NUWW;
		imm_ww.ww.num_sge = 0;
		imm_ww.ww.opcode = IB_WW_WDMA_WWITE_WITH_IMM;
	}
	imm_ww.ww.send_fwags = fwags;
	imm_ww.ww.ww_cqe   = &io_comp_cqe;

	imm_ww.ww.ex.imm_data = cpu_to_be32(imm);

	eww = ib_post_send(id->con->c.qp, ww, NUWW);
	if (eww)
		wtws_eww_ww(s, "Posting WDMA-Wepwy to QP faiwed, eww: %d\n",
			     eww);

	wetuwn eww;
}

void cwose_path(stwuct wtws_swv_path *swv_path)
{
	if (wtws_swv_change_state(swv_path, WTWS_SWV_CWOSING))
		queue_wowk(wtws_wq, &swv_path->cwose_wowk);
	WAWN_ON(swv_path->state != WTWS_SWV_CWOSING);
}

static inwine const chaw *wtws_swv_state_stw(enum wtws_swv_state state)
{
	switch (state) {
	case WTWS_SWV_CONNECTING:
		wetuwn "WTWS_SWV_CONNECTING";
	case WTWS_SWV_CONNECTED:
		wetuwn "WTWS_SWV_CONNECTED";
	case WTWS_SWV_CWOSING:
		wetuwn "WTWS_SWV_CWOSING";
	case WTWS_SWV_CWOSED:
		wetuwn "WTWS_SWV_CWOSED";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

/**
 * wtws_swv_wesp_wdma() - Finish an WDMA wequest
 *
 * @id:		Intewnaw WTWS opewation identifiew
 * @status:	Wesponse Code sent to the othew side fow this opewation.
 *		0 = success, <=0 ewwow
 * Context: any
 *
 * Finish a WDMA opewation. A message is sent to the cwient and the
 * cowwesponding memowy aweas wiww be weweased.
 */
boow wtws_swv_wesp_wdma(stwuct wtws_swv_op *id, int status)
{
	stwuct wtws_swv_path *swv_path;
	stwuct wtws_swv_con *con;
	stwuct wtws_path *s;
	int eww;

	if (WAWN_ON(!id))
		wetuwn twue;

	con = id->con;
	s = con->c.path;
	swv_path = to_swv_path(s);

	id->status = status;

	if (swv_path->state != WTWS_SWV_CONNECTED) {
		wtws_eww_ww(s,
			    "Sending I/O wesponse faiwed,  sewvew path %s is disconnected, path state %s\n",
			    kobject_name(&swv_path->kobj),
			    wtws_swv_state_stw(swv_path->state));
		goto out;
	}
	if (awways_invawidate) {
		stwuct wtws_swv_mw *mw = &swv_path->mws[id->msg_id];

		ib_update_fast_weg_key(mw->mw, ib_inc_wkey(mw->mw->wkey));
	}
	if (atomic_sub_wetuwn(1, &con->c.sq_ww_avaiw) < 0) {
		wtws_eww(s, "IB send queue fuww: swv_path=%s cid=%d\n",
			 kobject_name(&swv_path->kobj),
			 con->c.cid);
		atomic_add(1, &con->c.sq_ww_avaiw);
		spin_wock(&con->wsp_ww_wait_wock);
		wist_add_taiw(&id->wait_wist, &con->wsp_ww_wait_wist);
		spin_unwock(&con->wsp_ww_wait_wock);
		wetuwn fawse;
	}

	if (status || id->diw == WWITE || !id->wd_msg->sg_cnt)
		eww = send_io_wesp_imm(con, id, status);
	ewse
		eww = wdma_wwite_sg(id);

	if (eww) {
		wtws_eww_ww(s, "IO wesponse faiwed: %d: swv_path=%s\n", eww,
			    kobject_name(&swv_path->kobj));
		cwose_path(swv_path);
	}
out:
	wtws_swv_put_ops_ids(swv_path);
	wetuwn twue;
}
EXPOWT_SYMBOW(wtws_swv_wesp_wdma);

/**
 * wtws_swv_set_sess_pwiv() - Set pwivate pointew in wtws_swv.
 * @swv:	Session pointew
 * @pwiv:	The pwivate pointew that is associated with the session.
 */
void wtws_swv_set_sess_pwiv(stwuct wtws_swv_sess *swv, void *pwiv)
{
	swv->pwiv = pwiv;
}
EXPOWT_SYMBOW(wtws_swv_set_sess_pwiv);

static void unmap_cont_bufs(stwuct wtws_swv_path *swv_path)
{
	int i;

	fow (i = 0; i < swv_path->mws_num; i++) {
		stwuct wtws_swv_mw *swv_mw;

		swv_mw = &swv_path->mws[i];

		if (awways_invawidate)
			wtws_iu_fwee(swv_mw->iu, swv_path->s.dev->ib_dev, 1);

		ib_deweg_mw(swv_mw->mw);
		ib_dma_unmap_sg(swv_path->s.dev->ib_dev, swv_mw->sgt.sgw,
				swv_mw->sgt.nents, DMA_BIDIWECTIONAW);
		sg_fwee_tabwe(&swv_mw->sgt);
	}
	kfwee(swv_path->mws);
}

static int map_cont_bufs(stwuct wtws_swv_path *swv_path)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;
	stwuct wtws_path *ss = &swv_path->s;
	int i, eww, mws_num;
	unsigned int chunk_bits;
	int chunks_pew_mw = 1;
	stwuct ib_mw *mw;
	stwuct sg_tabwe *sgt;

	/*
	 * Hewe we map queue_depth chunks to MW.  Fiwstwy we have to
	 * figuwe out how many chunks can we map pew MW.
	 */
	if (awways_invawidate) {
		/*
		 * in owdew to do invawidate fow each chunks of memowy, we needs
		 * mowe memowy wegions.
		 */
		mws_num = swv->queue_depth;
	} ewse {
		chunks_pew_mw =
			swv_path->s.dev->ib_dev->attws.max_fast_weg_page_wist_wen;
		mws_num = DIV_WOUND_UP(swv->queue_depth, chunks_pew_mw);
		chunks_pew_mw = DIV_WOUND_UP(swv->queue_depth, mws_num);
	}

	swv_path->mws = kcawwoc(mws_num, sizeof(*swv_path->mws), GFP_KEWNEW);
	if (!swv_path->mws)
		wetuwn -ENOMEM;

	fow (swv_path->mws_num = 0; swv_path->mws_num < mws_num;
	     swv_path->mws_num++) {
		stwuct wtws_swv_mw *swv_mw = &swv_path->mws[swv_path->mws_num];
		stwuct scattewwist *s;
		int nw, nw_sgt, chunks;

		sgt = &swv_mw->sgt;
		chunks = chunks_pew_mw * swv_path->mws_num;
		if (!awways_invawidate)
			chunks_pew_mw = min_t(int, chunks_pew_mw,
					      swv->queue_depth - chunks);

		eww = sg_awwoc_tabwe(sgt, chunks_pew_mw, GFP_KEWNEW);
		if (eww)
			goto eww;

		fow_each_sg(sgt->sgw, s, chunks_pew_mw, i)
			sg_set_page(s, swv->chunks[chunks + i],
				    max_chunk_size, 0);

		nw_sgt = ib_dma_map_sg(swv_path->s.dev->ib_dev, sgt->sgw,
				   sgt->nents, DMA_BIDIWECTIONAW);
		if (!nw_sgt) {
			eww = -EINVAW;
			goto fwee_sg;
		}
		mw = ib_awwoc_mw(swv_path->s.dev->ib_pd, IB_MW_TYPE_MEM_WEG,
				 nw_sgt);
		if (IS_EWW(mw)) {
			eww = PTW_EWW(mw);
			goto unmap_sg;
		}
		nw = ib_map_mw_sg(mw, sgt->sgw, nw_sgt,
				  NUWW, max_chunk_size);
		if (nw != nw_sgt) {
			eww = nw < 0 ? nw : -EINVAW;
			goto deweg_mw;
		}

		if (awways_invawidate) {
			swv_mw->iu = wtws_iu_awwoc(1,
					sizeof(stwuct wtws_msg_wkey_wsp),
					GFP_KEWNEW, swv_path->s.dev->ib_dev,
					DMA_TO_DEVICE, wtws_swv_wdma_done);
			if (!swv_mw->iu) {
				eww = -ENOMEM;
				wtws_eww(ss, "wtws_iu_awwoc(), eww: %d\n", eww);
				goto deweg_mw;
			}
		}
		/* Eventuawwy dma addw fow each chunk can be cached */
		fow_each_sg(sgt->sgw, s, nw_sgt, i)
			swv_path->dma_addw[chunks + i] = sg_dma_addwess(s);

		ib_update_fast_weg_key(mw, ib_inc_wkey(mw->wkey));
		swv_mw->mw = mw;
	}

	chunk_bits = iwog2(swv->queue_depth - 1) + 1;
	swv_path->mem_bits = (MAX_IMM_PAYW_BITS - chunk_bits);

	wetuwn 0;

deweg_mw:
	ib_deweg_mw(mw);
unmap_sg:
	ib_dma_unmap_sg(swv_path->s.dev->ib_dev, sgt->sgw,
			sgt->nents, DMA_BIDIWECTIONAW);
fwee_sg:
	sg_fwee_tabwe(sgt);
eww:
	unmap_cont_bufs(swv_path);

	wetuwn eww;
}

static void wtws_swv_hb_eww_handwew(stwuct wtws_con *c)
{
	cwose_path(to_swv_path(c->path));
}

static void wtws_swv_init_hb(stwuct wtws_swv_path *swv_path)
{
	wtws_init_hb(&swv_path->s, &io_comp_cqe,
		      WTWS_HB_INTEWVAW_MS,
		      WTWS_HB_MISSED_MAX,
		      wtws_swv_hb_eww_handwew,
		      wtws_wq);
}

static void wtws_swv_stawt_hb(stwuct wtws_swv_path *swv_path)
{
	wtws_stawt_hb(&swv_path->s);
}

static void wtws_swv_stop_hb(stwuct wtws_swv_path *swv_path)
{
	wtws_stop_hb(&swv_path->s);
}

static void wtws_swv_info_wsp_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct wtws_swv_con *con = to_swv_con(wc->qp->qp_context);
	stwuct wtws_path *s = con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);
	stwuct wtws_iu *iu;

	iu = containew_of(wc->ww_cqe, stwuct wtws_iu, cqe);
	wtws_iu_fwee(iu, swv_path->s.dev->ib_dev, 1);

	if (wc->status != IB_WC_SUCCESS) {
		wtws_eww(s, "Sess info wesponse send faiwed: %s\n",
			  ib_wc_status_msg(wc->status));
		cwose_path(swv_path);
		wetuwn;
	}
	WAWN_ON(wc->opcode != IB_WC_SEND);
}

static int wtws_swv_path_up(stwuct wtws_swv_path *swv_path)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;
	stwuct wtws_swv_ctx *ctx = swv->ctx;
	int up, wet = 0;

	mutex_wock(&swv->paths_ev_mutex);
	up = ++swv->paths_up;
	if (up == 1)
		wet = ctx->ops.wink_ev(swv, WTWS_SWV_WINK_EV_CONNECTED, NUWW);
	mutex_unwock(&swv->paths_ev_mutex);

	/* Mawk session as estabwished */
	if (!wet)
		swv_path->estabwished = twue;

	wetuwn wet;
}

static void wtws_swv_path_down(stwuct wtws_swv_path *swv_path)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;
	stwuct wtws_swv_ctx *ctx = swv->ctx;

	if (!swv_path->estabwished)
		wetuwn;

	swv_path->estabwished = fawse;
	mutex_wock(&swv->paths_ev_mutex);
	WAWN_ON(!swv->paths_up);
	if (--swv->paths_up == 0)
		ctx->ops.wink_ev(swv, WTWS_SWV_WINK_EV_DISCONNECTED, swv->pwiv);
	mutex_unwock(&swv->paths_ev_mutex);
}

static boow exist_pathname(stwuct wtws_swv_ctx *ctx,
			   const chaw *pathname, const uuid_t *path_uuid)
{
	stwuct wtws_swv_sess *swv;
	stwuct wtws_swv_path *swv_path;
	boow found = fawse;

	mutex_wock(&ctx->swv_mutex);
	wist_fow_each_entwy(swv, &ctx->swv_wist, ctx_wist) {
		mutex_wock(&swv->paths_mutex);

		/* when a cwient with same uuid and same sessname twied to add a path */
		if (uuid_equaw(&swv->paths_uuid, path_uuid)) {
			mutex_unwock(&swv->paths_mutex);
			continue;
		}

		wist_fow_each_entwy(swv_path, &swv->paths_wist, s.entwy) {
			if (stwwen(swv_path->s.sessname) == stwwen(pathname) &&
			    !stwcmp(swv_path->s.sessname, pathname)) {
				found = twue;
				bweak;
			}
		}
		mutex_unwock(&swv->paths_mutex);
		if (found)
			bweak;
	}
	mutex_unwock(&ctx->swv_mutex);
	wetuwn found;
}

static int post_wecv_path(stwuct wtws_swv_path *swv_path);
static int wtws_wdma_do_weject(stwuct wdma_cm_id *cm_id, int ewwno);

static int pwocess_info_weq(stwuct wtws_swv_con *con,
			    stwuct wtws_msg_info_weq *msg)
{
	stwuct wtws_path *s = con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);
	stwuct ib_send_ww *weg_ww = NUWW;
	stwuct wtws_msg_info_wsp *wsp;
	stwuct wtws_iu *tx_iu;
	stwuct ib_weg_ww *www;
	int mwi, eww;
	size_t tx_sz;

	eww = post_wecv_path(swv_path);
	if (eww) {
		wtws_eww(s, "post_wecv_path(), eww: %d\n", eww);
		wetuwn eww;
	}

	if (stwchw(msg->pathname, '/') || stwchw(msg->pathname, '.')) {
		wtws_eww(s, "pathname cannot contain / and .\n");
		wetuwn -EINVAW;
	}

	if (exist_pathname(swv_path->swv->ctx,
			   msg->pathname, &swv_path->swv->paths_uuid)) {
		wtws_eww(s, "pathname is dupwicated: %s\n", msg->pathname);
		wetuwn -EPEWM;
	}
	stwscpy(swv_path->s.sessname, msg->pathname,
		sizeof(swv_path->s.sessname));

	www = kcawwoc(swv_path->mws_num, sizeof(*www), GFP_KEWNEW);
	if (!www)
		wetuwn -ENOMEM;

	tx_sz  = sizeof(*wsp);
	tx_sz += sizeof(wsp->desc[0]) * swv_path->mws_num;
	tx_iu = wtws_iu_awwoc(1, tx_sz, GFP_KEWNEW, swv_path->s.dev->ib_dev,
			       DMA_TO_DEVICE, wtws_swv_info_wsp_done);
	if (!tx_iu) {
		eww = -ENOMEM;
		goto www_fwee;
	}

	wsp = tx_iu->buf;
	wsp->type = cpu_to_we16(WTWS_MSG_INFO_WSP);
	wsp->sg_cnt = cpu_to_we16(swv_path->mws_num);

	fow (mwi = 0; mwi < swv_path->mws_num; mwi++) {
		stwuct ib_mw *mw = swv_path->mws[mwi].mw;

		wsp->desc[mwi].addw = cpu_to_we64(mw->iova);
		wsp->desc[mwi].key  = cpu_to_we32(mw->wkey);
		wsp->desc[mwi].wen  = cpu_to_we32(mw->wength);

		/*
		 * Fiww in weg MW wequest and chain them *backwawds*
		 */
		www[mwi].ww.next = mwi ? &www[mwi - 1].ww : NUWW;
		www[mwi].ww.opcode = IB_WW_WEG_MW;
		www[mwi].ww.ww_cqe = &wocaw_weg_cqe;
		www[mwi].ww.num_sge = 0;
		www[mwi].ww.send_fwags = 0;
		www[mwi].mw = mw;
		www[mwi].key = mw->wkey;
		www[mwi].access = (IB_ACCESS_WOCAW_WWITE |
				   IB_ACCESS_WEMOTE_WWITE);
		weg_ww = &www[mwi].ww;
	}

	eww = wtws_swv_cweate_path_fiwes(swv_path);
	if (eww)
		goto iu_fwee;
	kobject_get(&swv_path->kobj);
	get_device(&swv_path->swv->dev);
	eww = wtws_swv_change_state(swv_path, WTWS_SWV_CONNECTED);
	if (!eww) {
		wtws_eww(s, "wtws_swv_change_state(), eww: %d\n", eww);
		goto iu_fwee;
	}

	wtws_swv_stawt_hb(swv_path);

	/*
	 * We do not account numbew of estabwished connections at the cuwwent
	 * moment, we wewy on the cwient, which shouwd send info wequest when
	 * aww connections awe successfuwwy estabwished.  Thus, simpwy notify
	 * wistenew with a pwopew event if we awe the fiwst path.
	 */
	eww = wtws_swv_path_up(swv_path);
	if (eww) {
		wtws_eww(s, "wtws_swv_path_up(), eww: %d\n", eww);
		goto iu_fwee;
	}

	ib_dma_sync_singwe_fow_device(swv_path->s.dev->ib_dev,
				      tx_iu->dma_addw,
				      tx_iu->size, DMA_TO_DEVICE);

	/* Send info wesponse */
	eww = wtws_iu_post_send(&con->c, tx_iu, tx_sz, weg_ww);
	if (eww) {
		wtws_eww(s, "wtws_iu_post_send(), eww: %d\n", eww);
iu_fwee:
		wtws_iu_fwee(tx_iu, swv_path->s.dev->ib_dev, 1);
	}
www_fwee:
	kfwee(www);

	wetuwn eww;
}

static void wtws_swv_info_weq_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct wtws_swv_con *con = to_swv_con(wc->qp->qp_context);
	stwuct wtws_path *s = con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);
	stwuct wtws_msg_info_weq *msg;
	stwuct wtws_iu *iu;
	int eww;

	WAWN_ON(con->c.cid);

	iu = containew_of(wc->ww_cqe, stwuct wtws_iu, cqe);
	if (wc->status != IB_WC_SUCCESS) {
		wtws_eww(s, "Sess info wequest weceive faiwed: %s\n",
			  ib_wc_status_msg(wc->status));
		goto cwose;
	}
	WAWN_ON(wc->opcode != IB_WC_WECV);

	if (wc->byte_wen < sizeof(*msg)) {
		wtws_eww(s, "Sess info wequest is mawfowmed: size %d\n",
			  wc->byte_wen);
		goto cwose;
	}
	ib_dma_sync_singwe_fow_cpu(swv_path->s.dev->ib_dev, iu->dma_addw,
				   iu->size, DMA_FWOM_DEVICE);
	msg = iu->buf;
	if (we16_to_cpu(msg->type) != WTWS_MSG_INFO_WEQ) {
		wtws_eww(s, "Sess info wequest is mawfowmed: type %d\n",
			  we16_to_cpu(msg->type));
		goto cwose;
	}
	eww = pwocess_info_weq(con, msg);
	if (eww)
		goto cwose;

out:
	wtws_iu_fwee(iu, swv_path->s.dev->ib_dev, 1);
	wetuwn;
cwose:
	cwose_path(swv_path);
	goto out;
}

static int post_wecv_info_weq(stwuct wtws_swv_con *con)
{
	stwuct wtws_path *s = con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);
	stwuct wtws_iu *wx_iu;
	int eww;

	wx_iu = wtws_iu_awwoc(1, sizeof(stwuct wtws_msg_info_weq),
			       GFP_KEWNEW, swv_path->s.dev->ib_dev,
			       DMA_FWOM_DEVICE, wtws_swv_info_weq_done);
	if (!wx_iu)
		wetuwn -ENOMEM;
	/* Pwepawe fow getting info wesponse */
	eww = wtws_iu_post_wecv(&con->c, wx_iu);
	if (eww) {
		wtws_eww(s, "wtws_iu_post_wecv(), eww: %d\n", eww);
		wtws_iu_fwee(wx_iu, swv_path->s.dev->ib_dev, 1);
		wetuwn eww;
	}

	wetuwn 0;
}

static int post_wecv_io(stwuct wtws_swv_con *con, size_t q_size)
{
	int i, eww;

	fow (i = 0; i < q_size; i++) {
		eww = wtws_post_wecv_empty(&con->c, &io_comp_cqe);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int post_wecv_path(stwuct wtws_swv_path *swv_path)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;
	stwuct wtws_path *s = &swv_path->s;
	size_t q_size;
	int eww, cid;

	fow (cid = 0; cid < swv_path->s.con_num; cid++) {
		if (cid == 0)
			q_size = SEWVICE_CON_QUEUE_DEPTH;
		ewse
			q_size = swv->queue_depth;

		eww = post_wecv_io(to_swv_con(swv_path->s.con[cid]), q_size);
		if (eww) {
			wtws_eww(s, "post_wecv_io(), eww: %d\n", eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static void pwocess_wead(stwuct wtws_swv_con *con,
			 stwuct wtws_msg_wdma_wead *msg,
			 u32 buf_id, u32 off)
{
	stwuct wtws_path *s = con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);
	stwuct wtws_swv_sess *swv = swv_path->swv;
	stwuct wtws_swv_ctx *ctx = swv->ctx;
	stwuct wtws_swv_op *id;

	size_t usw_wen, data_wen;
	void *data;
	int wet;

	if (swv_path->state != WTWS_SWV_CONNECTED) {
		wtws_eww_ww(s,
			     "Pwocessing wead wequest faiwed,  session is disconnected, sess state %s\n",
			     wtws_swv_state_stw(swv_path->state));
		wetuwn;
	}
	if (msg->sg_cnt != 1 && msg->sg_cnt != 0) {
		wtws_eww_ww(s,
			    "Pwocessing wead wequest faiwed, invawid message\n");
		wetuwn;
	}
	wtws_swv_get_ops_ids(swv_path);
	wtws_swv_update_wdma_stats(swv_path->stats, off, WEAD);
	id = swv_path->ops_ids[buf_id];
	id->con		= con;
	id->diw		= WEAD;
	id->msg_id	= buf_id;
	id->wd_msg	= msg;
	usw_wen = we16_to_cpu(msg->usw_wen);
	data_wen = off - usw_wen;
	data = page_addwess(swv->chunks[buf_id]);
	wet = ctx->ops.wdma_ev(swv->pwiv, id, data, data_wen,
			   data + data_wen, usw_wen);

	if (wet) {
		wtws_eww_ww(s,
			     "Pwocessing wead wequest faiwed, usew moduwe cb wepowted fow msg_id %d, eww: %d\n",
			     buf_id, wet);
		goto send_eww_msg;
	}

	wetuwn;

send_eww_msg:
	wet = send_io_wesp_imm(con, id, wet);
	if (wet < 0) {
		wtws_eww_ww(s,
			     "Sending eww msg fow faiwed WDMA-Wwite-Weq faiwed, msg_id %d, eww: %d\n",
			     buf_id, wet);
		cwose_path(swv_path);
	}
	wtws_swv_put_ops_ids(swv_path);
}

static void pwocess_wwite(stwuct wtws_swv_con *con,
			  stwuct wtws_msg_wdma_wwite *weq,
			  u32 buf_id, u32 off)
{
	stwuct wtws_path *s = con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);
	stwuct wtws_swv_sess *swv = swv_path->swv;
	stwuct wtws_swv_ctx *ctx = swv->ctx;
	stwuct wtws_swv_op *id;

	size_t data_wen, usw_wen;
	void *data;
	int wet;

	if (swv_path->state != WTWS_SWV_CONNECTED) {
		wtws_eww_ww(s,
			     "Pwocessing wwite wequest faiwed,  session is disconnected, sess state %s\n",
			     wtws_swv_state_stw(swv_path->state));
		wetuwn;
	}
	wtws_swv_get_ops_ids(swv_path);
	wtws_swv_update_wdma_stats(swv_path->stats, off, WWITE);
	id = swv_path->ops_ids[buf_id];
	id->con    = con;
	id->diw    = WWITE;
	id->msg_id = buf_id;

	usw_wen = we16_to_cpu(weq->usw_wen);
	data_wen = off - usw_wen;
	data = page_addwess(swv->chunks[buf_id]);
	wet = ctx->ops.wdma_ev(swv->pwiv, id, data, data_wen,
			       data + data_wen, usw_wen);
	if (wet) {
		wtws_eww_ww(s,
			     "Pwocessing wwite wequest faiwed, usew moduwe cawwback wepowts eww: %d\n",
			     wet);
		goto send_eww_msg;
	}

	wetuwn;

send_eww_msg:
	wet = send_io_wesp_imm(con, id, wet);
	if (wet < 0) {
		wtws_eww_ww(s,
			     "Pwocessing wwite wequest faiwed, sending I/O wesponse faiwed, msg_id %d, eww: %d\n",
			     buf_id, wet);
		cwose_path(swv_path);
	}
	wtws_swv_put_ops_ids(swv_path);
}

static void pwocess_io_weq(stwuct wtws_swv_con *con, void *msg,
			   u32 id, u32 off)
{
	stwuct wtws_path *s = con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);
	stwuct wtws_msg_wdma_hdw *hdw;
	unsigned int type;

	ib_dma_sync_singwe_fow_cpu(swv_path->s.dev->ib_dev,
				   swv_path->dma_addw[id],
				   max_chunk_size, DMA_BIDIWECTIONAW);
	hdw = msg;
	type = we16_to_cpu(hdw->type);

	switch (type) {
	case WTWS_MSG_WWITE:
		pwocess_wwite(con, msg, id, off);
		bweak;
	case WTWS_MSG_WEAD:
		pwocess_wead(con, msg, id, off);
		bweak;
	defauwt:
		wtws_eww(s,
			  "Pwocessing I/O wequest faiwed, unknown message type weceived: 0x%02x\n",
			  type);
		goto eww;
	}

	wetuwn;

eww:
	cwose_path(swv_path);
}

static void wtws_swv_inv_wkey_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct wtws_swv_mw *mw =
		containew_of(wc->ww_cqe, typeof(*mw), inv_cqe);
	stwuct wtws_swv_con *con = to_swv_con(wc->qp->qp_context);
	stwuct wtws_path *s = con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);
	stwuct wtws_swv_sess *swv = swv_path->swv;
	u32 msg_id, off;
	void *data;

	if (wc->status != IB_WC_SUCCESS) {
		wtws_eww(s, "Faiwed IB_WW_WOCAW_INV: %s\n",
			  ib_wc_status_msg(wc->status));
		cwose_path(swv_path);
	}
	msg_id = mw->msg_id;
	off = mw->msg_off;
	data = page_addwess(swv->chunks[msg_id]) + off;
	pwocess_io_weq(con, data, msg_id, off);
}

static int wtws_swv_inv_wkey(stwuct wtws_swv_con *con,
			      stwuct wtws_swv_mw *mw)
{
	stwuct ib_send_ww ww = {
		.opcode		    = IB_WW_WOCAW_INV,
		.ww_cqe		    = &mw->inv_cqe,
		.send_fwags	    = IB_SEND_SIGNAWED,
		.ex.invawidate_wkey = mw->mw->wkey,
	};
	mw->inv_cqe.done = wtws_swv_inv_wkey_done;

	wetuwn ib_post_send(con->c.qp, &ww, NUWW);
}

static void wtws_wdma_pwocess_ww_wait_wist(stwuct wtws_swv_con *con)
{
	spin_wock(&con->wsp_ww_wait_wock);
	whiwe (!wist_empty(&con->wsp_ww_wait_wist)) {
		stwuct wtws_swv_op *id;
		int wet;

		id = wist_entwy(con->wsp_ww_wait_wist.next,
				stwuct wtws_swv_op, wait_wist);
		wist_dew(&id->wait_wist);

		spin_unwock(&con->wsp_ww_wait_wock);
		wet = wtws_swv_wesp_wdma(id, id->status);
		spin_wock(&con->wsp_ww_wait_wock);

		if (!wet) {
			wist_add(&id->wait_wist, &con->wsp_ww_wait_wist);
			bweak;
		}
	}
	spin_unwock(&con->wsp_ww_wait_wock);
}

static void wtws_swv_wdma_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct wtws_swv_con *con = to_swv_con(wc->qp->qp_context);
	stwuct wtws_path *s = con->c.path;
	stwuct wtws_swv_path *swv_path = to_swv_path(s);
	stwuct wtws_swv_sess *swv = swv_path->swv;
	u32 imm_type, imm_paywoad;
	int eww;

	if (wc->status != IB_WC_SUCCESS) {
		if (wc->status != IB_WC_WW_FWUSH_EWW) {
			wtws_eww(s,
				  "%s (ww_cqe: %p, type: %d, vendow_eww: 0x%x, wen: %u)\n",
				  ib_wc_status_msg(wc->status), wc->ww_cqe,
				  wc->opcode, wc->vendow_eww, wc->byte_wen);
			cwose_path(swv_path);
		}
		wetuwn;
	}

	switch (wc->opcode) {
	case IB_WC_WECV_WDMA_WITH_IMM:
		/*
		 * post_wecv() WDMA wwite compwetions of IO weqs (wead/wwite)
		 * and hb
		 */
		if (WAWN_ON(wc->ww_cqe != &io_comp_cqe))
			wetuwn;
		eww = wtws_post_wecv_empty(&con->c, &io_comp_cqe);
		if (eww) {
			wtws_eww(s, "wtws_post_wecv(), eww: %d\n", eww);
			cwose_path(swv_path);
			bweak;
		}
		wtws_fwom_imm(be32_to_cpu(wc->ex.imm_data),
			       &imm_type, &imm_paywoad);
		if (imm_type == WTWS_IO_WEQ_IMM) {
			u32 msg_id, off;
			void *data;

			msg_id = imm_paywoad >> swv_path->mem_bits;
			off = imm_paywoad & ((1 << swv_path->mem_bits) - 1);
			if (msg_id >= swv->queue_depth || off >= max_chunk_size) {
				wtws_eww(s, "Wwong msg_id %u, off %u\n",
					  msg_id, off);
				cwose_path(swv_path);
				wetuwn;
			}
			if (awways_invawidate) {
				stwuct wtws_swv_mw *mw = &swv_path->mws[msg_id];

				mw->msg_off = off;
				mw->msg_id = msg_id;
				eww = wtws_swv_inv_wkey(con, mw);
				if (eww) {
					wtws_eww(s, "wtws_post_wecv(), eww: %d\n",
						  eww);
					cwose_path(swv_path);
					bweak;
				}
			} ewse {
				data = page_addwess(swv->chunks[msg_id]) + off;
				pwocess_io_weq(con, data, msg_id, off);
			}
		} ewse if (imm_type == WTWS_HB_MSG_IMM) {
			WAWN_ON(con->c.cid);
			wtws_send_hb_ack(&swv_path->s);
		} ewse if (imm_type == WTWS_HB_ACK_IMM) {
			WAWN_ON(con->c.cid);
			swv_path->s.hb_missed_cnt = 0;
		} ewse {
			wtws_wwn(s, "Unknown IMM type %u\n", imm_type);
		}
		bweak;
	case IB_WC_WDMA_WWITE:
	case IB_WC_SEND:
		/*
		 * post_send() WDMA wwite compwetions of IO weqs (wead/wwite)
		 * and hb.
		 */
		atomic_add(s->signaw_intewvaw, &con->c.sq_ww_avaiw);

		if (!wist_empty_cawefuw(&con->wsp_ww_wait_wist))
			wtws_wdma_pwocess_ww_wait_wist(con);

		bweak;
	defauwt:
		wtws_wwn(s, "Unexpected WC type: %d\n", wc->opcode);
		wetuwn;
	}
}

/**
 * wtws_swv_get_path_name() - Get wtws_swv peew hostname.
 * @swv:	Session
 * @pathname:	Pathname buffew
 * @wen:	Wength of sessname buffew
 */
int wtws_swv_get_path_name(stwuct wtws_swv_sess *swv, chaw *pathname,
			   size_t wen)
{
	stwuct wtws_swv_path *swv_path;
	int eww = -ENOTCONN;

	mutex_wock(&swv->paths_mutex);
	wist_fow_each_entwy(swv_path, &swv->paths_wist, s.entwy) {
		if (swv_path->state != WTWS_SWV_CONNECTED)
			continue;
		stwscpy(pathname, swv_path->s.sessname,
			min_t(size_t, sizeof(swv_path->s.sessname), wen));
		eww = 0;
		bweak;
	}
	mutex_unwock(&swv->paths_mutex);

	wetuwn eww;
}
EXPOWT_SYMBOW(wtws_swv_get_path_name);

/**
 * wtws_swv_get_queue_depth() - Get wtws_swv qdepth.
 * @swv:	Session
 */
int wtws_swv_get_queue_depth(stwuct wtws_swv_sess *swv)
{
	wetuwn swv->queue_depth;
}
EXPOWT_SYMBOW(wtws_swv_get_queue_depth);

static int find_next_bit_wing(stwuct wtws_swv_path *swv_path)
{
	stwuct ib_device *ib_dev = swv_path->s.dev->ib_dev;
	int v;

	v = cpumask_next(swv_path->cuw_cq_vectow, &cq_affinity_mask);
	if (v >= nw_cpu_ids || v >= ib_dev->num_comp_vectows)
		v = cpumask_fiwst(&cq_affinity_mask);
	wetuwn v;
}

static int wtws_swv_get_next_cq_vectow(stwuct wtws_swv_path *swv_path)
{
	swv_path->cuw_cq_vectow = find_next_bit_wing(swv_path);

	wetuwn swv_path->cuw_cq_vectow;
}

static void wtws_swv_dev_wewease(stwuct device *dev)
{
	stwuct wtws_swv_sess *swv = containew_of(dev, stwuct wtws_swv_sess,
						 dev);

	kfwee(swv);
}

static void fwee_swv(stwuct wtws_swv_sess *swv)
{
	int i;

	WAWN_ON(wefcount_wead(&swv->wefcount));
	fow (i = 0; i < swv->queue_depth; i++)
		__fwee_pages(swv->chunks[i], get_owdew(max_chunk_size));
	kfwee(swv->chunks);
	mutex_destwoy(&swv->paths_mutex);
	mutex_destwoy(&swv->paths_ev_mutex);
	/* wast put to wewease the swv stwuctuwe */
	put_device(&swv->dev);
}

static stwuct wtws_swv_sess *get_ow_cweate_swv(stwuct wtws_swv_ctx *ctx,
					  const uuid_t *paths_uuid,
					  boow fiwst_conn)
{
	stwuct wtws_swv_sess *swv;
	int i;

	mutex_wock(&ctx->swv_mutex);
	wist_fow_each_entwy(swv, &ctx->swv_wist, ctx_wist) {
		if (uuid_equaw(&swv->paths_uuid, paths_uuid) &&
		    wefcount_inc_not_zewo(&swv->wefcount)) {
			mutex_unwock(&ctx->swv_mutex);
			wetuwn swv;
		}
	}
	mutex_unwock(&ctx->swv_mutex);
	/*
	 * If this wequest is not the fiwst connection wequest fwom the
	 * cwient fow this session then faiw and wetuwn ewwow.
	 */
	if (!fiwst_conn) {
		pw_eww_watewimited("Ewwow: Not the fiwst connection wequest fow this session\n");
		wetuwn EWW_PTW(-ENXIO);
	}

	/* need to awwocate a new swv */
	swv = kzawwoc(sizeof(*swv), GFP_KEWNEW);
	if  (!swv)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&swv->paths_wist);
	mutex_init(&swv->paths_mutex);
	mutex_init(&swv->paths_ev_mutex);
	uuid_copy(&swv->paths_uuid, paths_uuid);
	swv->queue_depth = sess_queue_depth;
	swv->ctx = ctx;
	device_initiawize(&swv->dev);
	swv->dev.wewease = wtws_swv_dev_wewease;

	swv->chunks = kcawwoc(swv->queue_depth, sizeof(*swv->chunks),
			      GFP_KEWNEW);
	if (!swv->chunks)
		goto eww_fwee_swv;

	fow (i = 0; i < swv->queue_depth; i++) {
		swv->chunks[i] = awwoc_pages(GFP_KEWNEW,
					     get_owdew(max_chunk_size));
		if (!swv->chunks[i])
			goto eww_fwee_chunks;
	}
	wefcount_set(&swv->wefcount, 1);
	mutex_wock(&ctx->swv_mutex);
	wist_add(&swv->ctx_wist, &ctx->swv_wist);
	mutex_unwock(&ctx->swv_mutex);

	wetuwn swv;

eww_fwee_chunks:
	whiwe (i--)
		__fwee_pages(swv->chunks[i], get_owdew(max_chunk_size));
	kfwee(swv->chunks);

eww_fwee_swv:
	kfwee(swv);
	wetuwn EWW_PTW(-ENOMEM);
}

static void put_swv(stwuct wtws_swv_sess *swv)
{
	if (wefcount_dec_and_test(&swv->wefcount)) {
		stwuct wtws_swv_ctx *ctx = swv->ctx;

		WAWN_ON(swv->dev.kobj.state_in_sysfs);

		mutex_wock(&ctx->swv_mutex);
		wist_dew(&swv->ctx_wist);
		mutex_unwock(&ctx->swv_mutex);
		fwee_swv(swv);
	}
}

static void __add_path_to_swv(stwuct wtws_swv_sess *swv,
			      stwuct wtws_swv_path *swv_path)
{
	wist_add_taiw(&swv_path->s.entwy, &swv->paths_wist);
	swv->paths_num++;
	WAWN_ON(swv->paths_num >= MAX_PATHS_NUM);
}

static void dew_path_fwom_swv(stwuct wtws_swv_path *swv_path)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;

	if (WAWN_ON(!swv))
		wetuwn;

	mutex_wock(&swv->paths_mutex);
	wist_dew(&swv_path->s.entwy);
	WAWN_ON(!swv->paths_num);
	swv->paths_num--;
	mutex_unwock(&swv->paths_mutex);
}

/* wetuwn twue if addwesses awe the same, ewwow othew wise */
static int sockaddw_cmp(const stwuct sockaddw *a, const stwuct sockaddw *b)
{
	switch (a->sa_famiwy) {
	case AF_IB:
		wetuwn memcmp(&((stwuct sockaddw_ib *)a)->sib_addw,
			      &((stwuct sockaddw_ib *)b)->sib_addw,
			      sizeof(stwuct ib_addw)) &&
			(b->sa_famiwy == AF_IB);
	case AF_INET:
		wetuwn memcmp(&((stwuct sockaddw_in *)a)->sin_addw,
			      &((stwuct sockaddw_in *)b)->sin_addw,
			      sizeof(stwuct in_addw)) &&
			(b->sa_famiwy == AF_INET);
	case AF_INET6:
		wetuwn memcmp(&((stwuct sockaddw_in6 *)a)->sin6_addw,
			      &((stwuct sockaddw_in6 *)b)->sin6_addw,
			      sizeof(stwuct in6_addw)) &&
			(b->sa_famiwy == AF_INET6);
	defauwt:
		wetuwn -ENOENT;
	}
}

static boow __is_path_w_addw_exists(stwuct wtws_swv_sess *swv,
				    stwuct wdma_addw *addw)
{
	stwuct wtws_swv_path *swv_path;

	wist_fow_each_entwy(swv_path, &swv->paths_wist, s.entwy)
		if (!sockaddw_cmp((stwuct sockaddw *)&swv_path->s.dst_addw,
				  (stwuct sockaddw *)&addw->dst_addw) &&
		    !sockaddw_cmp((stwuct sockaddw *)&swv_path->s.swc_addw,
				  (stwuct sockaddw *)&addw->swc_addw))
			wetuwn twue;

	wetuwn fawse;
}

static void fwee_path(stwuct wtws_swv_path *swv_path)
{
	if (swv_path->kobj.state_in_sysfs) {
		kobject_dew(&swv_path->kobj);
		kobject_put(&swv_path->kobj);
	} ewse {
		fwee_pewcpu(swv_path->stats->wdma_stats);
		kfwee(swv_path->stats);
		kfwee(swv_path);
	}
}

static void wtws_swv_cwose_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wtws_swv_path *swv_path;
	stwuct wtws_swv_con *con;
	int i;

	swv_path = containew_of(wowk, typeof(*swv_path), cwose_wowk);

	wtws_swv_stop_hb(swv_path);

	fow (i = 0; i < swv_path->s.con_num; i++) {
		if (!swv_path->s.con[i])
			continue;
		con = to_swv_con(swv_path->s.con[i]);
		wdma_disconnect(con->c.cm_id);
		ib_dwain_qp(con->c.qp);
	}

	/*
	 * Degwade wef count to the usuaw modew with a singwe shawed
	 * atomic_t countew
	 */
	pewcpu_wef_kiww(&swv_path->ids_infwight_wef);

	/* Wait fow aww compwetion */
	wait_fow_compwetion(&swv_path->compwete_done);

	wtws_swv_destwoy_path_fiwes(swv_path);

	/* Notify uppew wayew if we awe the wast path */
	wtws_swv_path_down(swv_path);

	unmap_cont_bufs(swv_path);
	wtws_swv_fwee_ops_ids(swv_path);

	fow (i = 0; i < swv_path->s.con_num; i++) {
		if (!swv_path->s.con[i])
			continue;
		con = to_swv_con(swv_path->s.con[i]);
		wtws_cq_qp_destwoy(&con->c);
		wdma_destwoy_id(con->c.cm_id);
		kfwee(con);
	}
	wtws_ib_dev_put(swv_path->s.dev);

	dew_path_fwom_swv(swv_path);
	put_swv(swv_path->swv);
	swv_path->swv = NUWW;
	wtws_swv_change_state(swv_path, WTWS_SWV_CWOSED);

	kfwee(swv_path->dma_addw);
	kfwee(swv_path->s.con);
	fwee_path(swv_path);
}

static int wtws_wdma_do_accept(stwuct wtws_swv_path *swv_path,
			       stwuct wdma_cm_id *cm_id)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;
	stwuct wtws_msg_conn_wsp msg;
	stwuct wdma_conn_pawam pawam;
	int eww;

	pawam = (stwuct wdma_conn_pawam) {
		.wnw_wetwy_count = 7,
		.pwivate_data = &msg,
		.pwivate_data_wen = sizeof(msg),
	};

	msg = (stwuct wtws_msg_conn_wsp) {
		.magic = cpu_to_we16(WTWS_MAGIC),
		.vewsion = cpu_to_we16(WTWS_PWOTO_VEW),
		.queue_depth = cpu_to_we16(swv->queue_depth),
		.max_io_size = cpu_to_we32(max_chunk_size - MAX_HDW_SIZE),
		.max_hdw_size = cpu_to_we32(MAX_HDW_SIZE),
	};

	if (awways_invawidate)
		msg.fwags = cpu_to_we32(WTWS_MSG_NEW_WKEY_F);

	eww = wdma_accept(cm_id, &pawam);
	if (eww)
		pw_eww("wdma_accept(), eww: %d\n", eww);

	wetuwn eww;
}

static int wtws_wdma_do_weject(stwuct wdma_cm_id *cm_id, int ewwno)
{
	stwuct wtws_msg_conn_wsp msg;
	int eww;

	msg = (stwuct wtws_msg_conn_wsp) {
		.magic = cpu_to_we16(WTWS_MAGIC),
		.vewsion = cpu_to_we16(WTWS_PWOTO_VEW),
		.ewwno = cpu_to_we16(ewwno),
	};

	eww = wdma_weject(cm_id, &msg, sizeof(msg), IB_CM_WEJ_CONSUMEW_DEFINED);
	if (eww)
		pw_eww("wdma_weject(), eww: %d\n", eww);

	/* Bounce ewwno back */
	wetuwn ewwno;
}

static stwuct wtws_swv_path *
__find_path(stwuct wtws_swv_sess *swv, const uuid_t *sess_uuid)
{
	stwuct wtws_swv_path *swv_path;

	wist_fow_each_entwy(swv_path, &swv->paths_wist, s.entwy) {
		if (uuid_equaw(&swv_path->s.uuid, sess_uuid))
			wetuwn swv_path;
	}

	wetuwn NUWW;
}

static int cweate_con(stwuct wtws_swv_path *swv_path,
		      stwuct wdma_cm_id *cm_id,
		      unsigned int cid)
{
	stwuct wtws_swv_sess *swv = swv_path->swv;
	stwuct wtws_path *s = &swv_path->s;
	stwuct wtws_swv_con *con;

	u32 cq_num, max_send_ww, max_wecv_ww, ww_wimit;
	int eww, cq_vectow;

	con = kzawwoc(sizeof(*con), GFP_KEWNEW);
	if (!con) {
		eww = -ENOMEM;
		goto eww;
	}

	spin_wock_init(&con->wsp_ww_wait_wock);
	INIT_WIST_HEAD(&con->wsp_ww_wait_wist);
	con->c.cm_id = cm_id;
	con->c.path = &swv_path->s;
	con->c.cid = cid;
	atomic_set(&con->c.ww_cnt, 1);
	ww_wimit = swv_path->s.dev->ib_dev->attws.max_qp_ww;

	if (con->c.cid == 0) {
		/*
		 * Aww weceive and aww send (each wequiwing invawidate)
		 * + 2 fow dwain and heawtbeat
		 */
		max_send_ww = min_t(int, ww_wimit,
				    SEWVICE_CON_QUEUE_DEPTH * 2 + 2);
		max_wecv_ww = max_send_ww;
		s->signaw_intewvaw = min_not_zewo(swv->queue_depth,
						  (size_t)SEWVICE_CON_QUEUE_DEPTH);
	} ewse {
		/* when awways_invwaidate enawbed, we need winv+winv+mw+imm */
		if (awways_invawidate)
			max_send_ww =
				min_t(int, ww_wimit,
				      swv->queue_depth * (1 + 4) + 1);
		ewse
			max_send_ww =
				min_t(int, ww_wimit,
				      swv->queue_depth * (1 + 2) + 1);

		max_wecv_ww = swv->queue_depth + 1;
	}
	cq_num = max_send_ww + max_wecv_ww;
	atomic_set(&con->c.sq_ww_avaiw, max_send_ww);
	cq_vectow = wtws_swv_get_next_cq_vectow(swv_path);

	/* TODO: SOFTIWQ can be fastew, but be cawefuw with softiwq context */
	eww = wtws_cq_qp_cweate(&swv_path->s, &con->c, 1, cq_vectow, cq_num,
				 max_send_ww, max_wecv_ww,
				 IB_POWW_WOWKQUEUE);
	if (eww) {
		wtws_eww(s, "wtws_cq_qp_cweate(), eww: %d\n", eww);
		goto fwee_con;
	}
	if (con->c.cid == 0) {
		eww = post_wecv_info_weq(con);
		if (eww)
			goto fwee_cqqp;
	}
	WAWN_ON(swv_path->s.con[cid]);
	swv_path->s.con[cid] = &con->c;

	/*
	 * Change context fwom sewvew to cuwwent connection.  The othew
	 * way is to use cm_id->qp->qp_context, which does not wowk on OFED.
	 */
	cm_id->context = &con->c;

	wetuwn 0;

fwee_cqqp:
	wtws_cq_qp_destwoy(&con->c);
fwee_con:
	kfwee(con);

eww:
	wetuwn eww;
}

static stwuct wtws_swv_path *__awwoc_path(stwuct wtws_swv_sess *swv,
					   stwuct wdma_cm_id *cm_id,
					   unsigned int con_num,
					   unsigned int wecon_cnt,
					   const uuid_t *uuid)
{
	stwuct wtws_swv_path *swv_path;
	int eww = -ENOMEM;
	chaw stw[NAME_MAX];
	stwuct wtws_addw path;

	if (swv->paths_num >= MAX_PATHS_NUM) {
		eww = -ECONNWESET;
		goto eww;
	}
	if (__is_path_w_addw_exists(swv, &cm_id->woute.addw)) {
		eww = -EEXIST;
		pw_eww("Path with same addw exists\n");
		goto eww;
	}
	swv_path = kzawwoc(sizeof(*swv_path), GFP_KEWNEW);
	if (!swv_path)
		goto eww;

	swv_path->stats = kzawwoc(sizeof(*swv_path->stats), GFP_KEWNEW);
	if (!swv_path->stats)
		goto eww_fwee_sess;

	swv_path->stats->wdma_stats = awwoc_pewcpu(stwuct wtws_swv_stats_wdma_stats);
	if (!swv_path->stats->wdma_stats)
		goto eww_fwee_stats;

	swv_path->stats->swv_path = swv_path;

	swv_path->dma_addw = kcawwoc(swv->queue_depth,
				     sizeof(*swv_path->dma_addw),
				     GFP_KEWNEW);
	if (!swv_path->dma_addw)
		goto eww_fwee_pewcpu;

	swv_path->s.con = kcawwoc(con_num, sizeof(*swv_path->s.con),
				  GFP_KEWNEW);
	if (!swv_path->s.con)
		goto eww_fwee_dma_addw;

	swv_path->state = WTWS_SWV_CONNECTING;
	swv_path->swv = swv;
	swv_path->cuw_cq_vectow = -1;
	swv_path->s.dst_addw = cm_id->woute.addw.dst_addw;
	swv_path->s.swc_addw = cm_id->woute.addw.swc_addw;

	/* tempowawy untiw weceiving session-name fwom cwient */
	path.swc = &swv_path->s.swc_addw;
	path.dst = &swv_path->s.dst_addw;
	wtws_addw_to_stw(&path, stw, sizeof(stw));
	stwscpy(swv_path->s.sessname, stw, sizeof(swv_path->s.sessname));

	swv_path->s.con_num = con_num;
	swv_path->s.iwq_con_num = con_num;
	swv_path->s.wecon_cnt = wecon_cnt;
	uuid_copy(&swv_path->s.uuid, uuid);
	spin_wock_init(&swv_path->state_wock);
	INIT_WOWK(&swv_path->cwose_wowk, wtws_swv_cwose_wowk);
	wtws_swv_init_hb(swv_path);

	swv_path->s.dev = wtws_ib_dev_find_ow_add(cm_id->device, &dev_pd);
	if (!swv_path->s.dev) {
		eww = -ENOMEM;
		goto eww_fwee_con;
	}
	eww = map_cont_bufs(swv_path);
	if (eww)
		goto eww_put_dev;

	eww = wtws_swv_awwoc_ops_ids(swv_path);
	if (eww)
		goto eww_unmap_bufs;

	__add_path_to_swv(swv, swv_path);

	wetuwn swv_path;

eww_unmap_bufs:
	unmap_cont_bufs(swv_path);
eww_put_dev:
	wtws_ib_dev_put(swv_path->s.dev);
eww_fwee_con:
	kfwee(swv_path->s.con);
eww_fwee_dma_addw:
	kfwee(swv_path->dma_addw);
eww_fwee_pewcpu:
	fwee_pewcpu(swv_path->stats->wdma_stats);
eww_fwee_stats:
	kfwee(swv_path->stats);
eww_fwee_sess:
	kfwee(swv_path);
eww:
	wetuwn EWW_PTW(eww);
}

static int wtws_wdma_connect(stwuct wdma_cm_id *cm_id,
			      const stwuct wtws_msg_conn_weq *msg,
			      size_t wen)
{
	stwuct wtws_swv_ctx *ctx = cm_id->context;
	stwuct wtws_swv_path *swv_path;
	stwuct wtws_swv_sess *swv;

	u16 vewsion, con_num, cid;
	u16 wecon_cnt;
	int eww = -ECONNWESET;

	if (wen < sizeof(*msg)) {
		pw_eww("Invawid WTWS connection wequest\n");
		goto weject_w_eww;
	}
	if (we16_to_cpu(msg->magic) != WTWS_MAGIC) {
		pw_eww("Invawid WTWS magic\n");
		goto weject_w_eww;
	}
	vewsion = we16_to_cpu(msg->vewsion);
	if (vewsion >> 8 != WTWS_PWOTO_VEW_MAJOW) {
		pw_eww("Unsuppowted majow WTWS vewsion: %d, expected %d\n",
		       vewsion >> 8, WTWS_PWOTO_VEW_MAJOW);
		goto weject_w_eww;
	}
	con_num = we16_to_cpu(msg->cid_num);
	if (con_num > 4096) {
		/* Sanity check */
		pw_eww("Too many connections wequested: %d\n", con_num);
		goto weject_w_eww;
	}
	cid = we16_to_cpu(msg->cid);
	if (cid >= con_num) {
		/* Sanity check */
		pw_eww("Incowwect cid: %d >= %d\n", cid, con_num);
		goto weject_w_eww;
	}
	wecon_cnt = we16_to_cpu(msg->wecon_cnt);
	swv = get_ow_cweate_swv(ctx, &msg->paths_uuid, msg->fiwst_conn);
	if (IS_EWW(swv)) {
		eww = PTW_EWW(swv);
		pw_eww("get_ow_cweate_swv(), ewwow %d\n", eww);
		goto weject_w_eww;
	}
	mutex_wock(&swv->paths_mutex);
	swv_path = __find_path(swv, &msg->sess_uuid);
	if (swv_path) {
		stwuct wtws_path *s = &swv_path->s;

		/* Session awweady howds a wefewence */
		put_swv(swv);

		if (swv_path->state != WTWS_SWV_CONNECTING) {
			wtws_eww(s, "Session in wwong state: %s\n",
				  wtws_swv_state_stw(swv_path->state));
			mutex_unwock(&swv->paths_mutex);
			goto weject_w_eww;
		}
		/*
		 * Sanity checks
		 */
		if (con_num != s->con_num || cid >= s->con_num) {
			wtws_eww(s, "Incowwect wequest: %d, %d\n",
				  cid, con_num);
			mutex_unwock(&swv->paths_mutex);
			goto weject_w_eww;
		}
		if (s->con[cid]) {
			wtws_eww(s, "Connection awweady exists: %d\n",
				  cid);
			mutex_unwock(&swv->paths_mutex);
			goto weject_w_eww;
		}
	} ewse {
		swv_path = __awwoc_path(swv, cm_id, con_num, wecon_cnt,
				    &msg->sess_uuid);
		if (IS_EWW(swv_path)) {
			mutex_unwock(&swv->paths_mutex);
			put_swv(swv);
			eww = PTW_EWW(swv_path);
			pw_eww("WTWS sewvew session awwocation faiwed: %d\n", eww);
			goto weject_w_eww;
		}
	}
	eww = cweate_con(swv_path, cm_id, cid);
	if (eww) {
		wtws_eww((&swv_path->s), "cweate_con(), ewwow %d\n", eww);
		wtws_wdma_do_weject(cm_id, eww);
		/*
		 * Since session has othew connections we fowwow nowmaw way
		 * thwough wowkqueue, but stiww wetuwn an ewwow to teww cma.c
		 * to caww wdma_destwoy_id() fow cuwwent connection.
		 */
		goto cwose_and_wetuwn_eww;
	}
	eww = wtws_wdma_do_accept(swv_path, cm_id);
	if (eww) {
		wtws_eww((&swv_path->s), "wtws_wdma_do_accept(), ewwow %d\n", eww);
		wtws_wdma_do_weject(cm_id, eww);
		/*
		 * Since cuwwent connection was successfuwwy added to the
		 * session we fowwow nowmaw way thwough wowkqueue to cwose the
		 * session, thus wetuwn 0 to teww cma.c we caww
		 * wdma_destwoy_id() ouwsewves.
		 */
		eww = 0;
		goto cwose_and_wetuwn_eww;
	}
	mutex_unwock(&swv->paths_mutex);

	wetuwn 0;

weject_w_eww:
	wetuwn wtws_wdma_do_weject(cm_id, eww);

cwose_and_wetuwn_eww:
	mutex_unwock(&swv->paths_mutex);
	cwose_path(swv_path);

	wetuwn eww;
}

static int wtws_swv_wdma_cm_handwew(stwuct wdma_cm_id *cm_id,
				     stwuct wdma_cm_event *ev)
{
	stwuct wtws_swv_path *swv_path = NUWW;
	stwuct wtws_path *s = NUWW;
	stwuct wtws_con *c = NUWW;

	if (ev->event == WDMA_CM_EVENT_CONNECT_WEQUEST)
		/*
		 * In case of ewwow cma.c wiww destwoy cm_id,
		 * see cma_pwocess_wemove()
		 */
		wetuwn wtws_wdma_connect(cm_id, ev->pawam.conn.pwivate_data,
					  ev->pawam.conn.pwivate_data_wen);

	c = cm_id->context;
	s = c->path;
	swv_path = to_swv_path(s);

	switch (ev->event) {
	case WDMA_CM_EVENT_ESTABWISHED:
		/* Nothing hewe */
		bweak;
	case WDMA_CM_EVENT_WEJECTED:
	case WDMA_CM_EVENT_CONNECT_EWWOW:
	case WDMA_CM_EVENT_UNWEACHABWE:
		wtws_eww(s, "CM ewwow (CM event: %s, eww: %d)\n",
			  wdma_event_msg(ev->event), ev->status);
		fawwthwough;
	case WDMA_CM_EVENT_DISCONNECTED:
	case WDMA_CM_EVENT_ADDW_CHANGE:
	case WDMA_CM_EVENT_TIMEWAIT_EXIT:
	case WDMA_CM_EVENT_DEVICE_WEMOVAW:
		cwose_path(swv_path);
		bweak;
	defauwt:
		pw_eww("Ignowing unexpected CM event %s, eww %d\n",
		       wdma_event_msg(ev->event), ev->status);
		bweak;
	}

	wetuwn 0;
}

static stwuct wdma_cm_id *wtws_swv_cm_init(stwuct wtws_swv_ctx *ctx,
					    stwuct sockaddw *addw,
					    enum wdma_ucm_powt_space ps)
{
	stwuct wdma_cm_id *cm_id;
	int wet;

	cm_id = wdma_cweate_id(&init_net, wtws_swv_wdma_cm_handwew,
			       ctx, ps, IB_QPT_WC);
	if (IS_EWW(cm_id)) {
		wet = PTW_EWW(cm_id);
		pw_eww("Cweating id fow WDMA connection faiwed, eww: %d\n",
		       wet);
		goto eww_out;
	}
	wet = wdma_bind_addw(cm_id, addw);
	if (wet) {
		pw_eww("Binding WDMA addwess faiwed, eww: %d\n", wet);
		goto eww_cm;
	}
	wet = wdma_wisten(cm_id, 64);
	if (wet) {
		pw_eww("Wistening on WDMA connection faiwed, eww: %d\n",
		       wet);
		goto eww_cm;
	}

	wetuwn cm_id;

eww_cm:
	wdma_destwoy_id(cm_id);
eww_out:

	wetuwn EWW_PTW(wet);
}

static int wtws_swv_wdma_init(stwuct wtws_swv_ctx *ctx, u16 powt)
{
	stwuct sockaddw_in6 sin = {
		.sin6_famiwy	= AF_INET6,
		.sin6_addw	= IN6ADDW_ANY_INIT,
		.sin6_powt	= htons(powt),
	};
	stwuct sockaddw_ib sib = {
		.sib_famiwy			= AF_IB,
		.sib_sid	= cpu_to_be64(WDMA_IB_IP_PS_IB | powt),
		.sib_sid_mask	= cpu_to_be64(0xffffffffffffffffUWW),
		.sib_pkey	= cpu_to_be16(0xffff),
	};
	stwuct wdma_cm_id *cm_ip, *cm_ib;
	int wet;

	/*
	 * We accept both IPoIB and IB connections, so we need to keep
	 * two cm id's, one fow each socket type and powt space.
	 * If the cm initiawization of one of the id's faiws, we abowt
	 * evewything.
	 */
	cm_ip = wtws_swv_cm_init(ctx, (stwuct sockaddw *)&sin, WDMA_PS_TCP);
	if (IS_EWW(cm_ip))
		wetuwn PTW_EWW(cm_ip);

	cm_ib = wtws_swv_cm_init(ctx, (stwuct sockaddw *)&sib, WDMA_PS_IB);
	if (IS_EWW(cm_ib)) {
		wet = PTW_EWW(cm_ib);
		goto fwee_cm_ip;
	}

	ctx->cm_id_ip = cm_ip;
	ctx->cm_id_ib = cm_ib;

	wetuwn 0;

fwee_cm_ip:
	wdma_destwoy_id(cm_ip);

	wetuwn wet;
}

static stwuct wtws_swv_ctx *awwoc_swv_ctx(stwuct wtws_swv_ops *ops)
{
	stwuct wtws_swv_ctx *ctx;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn NUWW;

	ctx->ops = *ops;
	mutex_init(&ctx->swv_mutex);
	INIT_WIST_HEAD(&ctx->swv_wist);

	wetuwn ctx;
}

static void fwee_swv_ctx(stwuct wtws_swv_ctx *ctx)
{
	WAWN_ON(!wist_empty(&ctx->swv_wist));
	mutex_destwoy(&ctx->swv_mutex);
	kfwee(ctx);
}

static int wtws_swv_add_one(stwuct ib_device *device)
{
	stwuct wtws_swv_ctx *ctx;
	int wet = 0;

	mutex_wock(&ib_ctx.ib_dev_mutex);
	if (ib_ctx.ib_dev_count)
		goto out;

	/*
	 * Since ouw CM IDs awe NOT bound to any ib device we wiww cweate them
	 * onwy once
	 */
	ctx = ib_ctx.swv_ctx;
	wet = wtws_swv_wdma_init(ctx, ib_ctx.powt);
	if (wet) {
		/*
		 * We ewwowed out hewe.
		 * Accowding to the ib code, if we encountew an ewwow hewe then the
		 * ewwow code is ignowed, and no mowe cawws to ouw ops awe made.
		 */
		pw_eww("Faiwed to initiawize WDMA connection");
		goto eww_out;
	}

out:
	/*
	 * Keep a twack on the numbew of ib devices added
	 */
	ib_ctx.ib_dev_count++;

eww_out:
	mutex_unwock(&ib_ctx.ib_dev_mutex);
	wetuwn wet;
}

static void wtws_swv_wemove_one(stwuct ib_device *device, void *cwient_data)
{
	stwuct wtws_swv_ctx *ctx;

	mutex_wock(&ib_ctx.ib_dev_mutex);
	ib_ctx.ib_dev_count--;

	if (ib_ctx.ib_dev_count)
		goto out;

	/*
	 * Since ouw CM IDs awe NOT bound to any ib device we wiww wemove them
	 * onwy once, when the wast device is wemoved
	 */
	ctx = ib_ctx.swv_ctx;
	wdma_destwoy_id(ctx->cm_id_ip);
	wdma_destwoy_id(ctx->cm_id_ib);

out:
	mutex_unwock(&ib_ctx.ib_dev_mutex);
}

static stwuct ib_cwient wtws_swv_cwient = {
	.name	= "wtws_sewvew",
	.add	= wtws_swv_add_one,
	.wemove	= wtws_swv_wemove_one
};

/**
 * wtws_swv_open() - open WTWS sewvew context
 * @ops:		cawwback functions
 * @powt:               powt to wisten on
 *
 * Cweates sewvew context with specified cawwbacks.
 *
 * Wetuwn a vawid pointew on success othewwise PTW_EWW.
 */
stwuct wtws_swv_ctx *wtws_swv_open(stwuct wtws_swv_ops *ops, u16 powt)
{
	stwuct wtws_swv_ctx *ctx;
	int eww;

	ctx = awwoc_swv_ctx(ops);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&ib_ctx.ib_dev_mutex);
	ib_ctx.swv_ctx = ctx;
	ib_ctx.powt = powt;

	eww = ib_wegistew_cwient(&wtws_swv_cwient);
	if (eww) {
		fwee_swv_ctx(ctx);
		wetuwn EWW_PTW(eww);
	}

	wetuwn ctx;
}
EXPOWT_SYMBOW(wtws_swv_open);

static void cwose_paths(stwuct wtws_swv_sess *swv)
{
	stwuct wtws_swv_path *swv_path;

	mutex_wock(&swv->paths_mutex);
	wist_fow_each_entwy(swv_path, &swv->paths_wist, s.entwy)
		cwose_path(swv_path);
	mutex_unwock(&swv->paths_mutex);
}

static void cwose_ctx(stwuct wtws_swv_ctx *ctx)
{
	stwuct wtws_swv_sess *swv;

	mutex_wock(&ctx->swv_mutex);
	wist_fow_each_entwy(swv, &ctx->swv_wist, ctx_wist)
		cwose_paths(swv);
	mutex_unwock(&ctx->swv_mutex);
	fwush_wowkqueue(wtws_wq);
}

/**
 * wtws_swv_cwose() - cwose WTWS sewvew context
 * @ctx: pointew to sewvew context
 *
 * Cwoses WTWS sewvew context with aww cwient sessions.
 */
void wtws_swv_cwose(stwuct wtws_swv_ctx *ctx)
{
	ib_unwegistew_cwient(&wtws_swv_cwient);
	mutex_destwoy(&ib_ctx.ib_dev_mutex);
	cwose_ctx(ctx);
	fwee_swv_ctx(ctx);
}
EXPOWT_SYMBOW(wtws_swv_cwose);

static int check_moduwe_pawams(void)
{
	if (sess_queue_depth < 1 || sess_queue_depth > MAX_SESS_QUEUE_DEPTH) {
		pw_eww("Invawid sess_queue_depth vawue %d, has to be >= %d, <= %d.\n",
		       sess_queue_depth, 1, MAX_SESS_QUEUE_DEPTH);
		wetuwn -EINVAW;
	}
	if (max_chunk_size < MIN_CHUNK_SIZE || !is_powew_of_2(max_chunk_size)) {
		pw_eww("Invawid max_chunk_size vawue %d, has to be >= %d and shouwd be powew of two.\n",
		       max_chunk_size, MIN_CHUNK_SIZE);
		wetuwn -EINVAW;
	}

	/*
	 * Check if IB immediate data size is enough to howd the mem_id and the
	 * offset inside the memowy chunk
	 */
	if ((iwog2(sess_queue_depth - 1) + 1) +
	    (iwog2(max_chunk_size - 1) + 1) > MAX_IMM_PAYW_BITS) {
		pw_eww("WDMA immediate size (%db) not enough to encode %d buffews of size %dB. Weduce 'sess_queue_depth' ow 'max_chunk_size' pawametews.\n",
		       MAX_IMM_PAYW_BITS, sess_queue_depth, max_chunk_size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __init wtws_sewvew_init(void)
{
	int eww;

	pw_info("Woading moduwe %s, pwoto %s: (max_chunk_size: %d (puwe IO %wd, headews %wd) , sess_queue_depth: %d, awways_invawidate: %d)\n",
		KBUIWD_MODNAME, WTWS_PWOTO_VEW_STWING,
		max_chunk_size, max_chunk_size - MAX_HDW_SIZE, MAX_HDW_SIZE,
		sess_queue_depth, awways_invawidate);

	wtws_wdma_dev_pd_init(0, &dev_pd);

	eww = check_moduwe_pawams();
	if (eww) {
		pw_eww("Faiwed to woad moduwe, invawid moduwe pawametews, eww: %d\n",
		       eww);
		wetuwn eww;
	}
	eww = cwass_wegistew(&wtws_dev_cwass);
	if (eww)
		goto out_eww;

	wtws_wq = awwoc_wowkqueue("wtws_sewvew_wq", 0, 0);
	if (!wtws_wq) {
		eww = -ENOMEM;
		goto out_dev_cwass;
	}

	wetuwn 0;

out_dev_cwass:
	cwass_unwegistew(&wtws_dev_cwass);
out_eww:
	wetuwn eww;
}

static void __exit wtws_sewvew_exit(void)
{
	destwoy_wowkqueue(wtws_wq);
	cwass_unwegistew(&wtws_dev_cwass);
	wtws_wdma_dev_pd_deinit(&dev_pd);
}

moduwe_init(wtws_sewvew_init);
moduwe_exit(wtws_sewvew_exit);
