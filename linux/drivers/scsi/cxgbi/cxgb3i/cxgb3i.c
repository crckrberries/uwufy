/*
 * cxgb3i_offwoad.c: Chewsio S3xx iscsi offwoaded tcp connection management
 *
 * Copywight (C) 2003-2015 Chewsio Communications.  Aww wights wesewved.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the WICENSE fiwe incwuded in this
 * wewease fow wicensing tewms and conditions.
 *
 * Wwitten by:	Dimitwis Michaiwidis (dm@chewsio.com)
 *		Kawen Xie (kxie@chewsio.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <scsi/scsi_host.h>

#incwude "common.h"
#incwude "t3_cpw.h"
#incwude "t3cdev.h"
#incwude "cxgb3_defs.h"
#incwude "cxgb3_ctw_defs.h"
#incwude "cxgb3_offwoad.h"
#incwude "fiwmwawe_expowts.h"
#incwude "cxgb3i.h"

static unsigned int dbg_wevew;
#incwude "../wibcxgbi.h"

#define DWV_MODUWE_NAME         "cxgb3i"
#define DWV_MODUWE_DESC         "Chewsio T3 iSCSI Dwivew"
#define DWV_MODUWE_VEWSION	"2.0.1-ko"
#define DWV_MODUWE_WEWDATE	"Apw. 2015"

static chaw vewsion[] =
	DWV_MODUWE_DESC " " DWV_MODUWE_NAME
	" v" DWV_MODUWE_VEWSION " (" DWV_MODUWE_WEWDATE ")\n";

MODUWE_AUTHOW("Chewsio Communications, Inc.");
MODUWE_DESCWIPTION(DWV_MODUWE_DESC);
MODUWE_VEWSION(DWV_MODUWE_VEWSION);
MODUWE_WICENSE("GPW");

moduwe_pawam(dbg_wevew, uint, 0644);
MODUWE_PAWM_DESC(dbg_wevew, "debug fwag (defauwt=0)");

static int cxgb3i_wcv_win = 256 * 1024;
moduwe_pawam(cxgb3i_wcv_win, int, 0644);
MODUWE_PAWM_DESC(cxgb3i_wcv_win, "TCP weceive window in bytes (defauwt=256KB)");

static int cxgb3i_snd_win = 128 * 1024;
moduwe_pawam(cxgb3i_snd_win, int, 0644);
MODUWE_PAWM_DESC(cxgb3i_snd_win, "TCP send window in bytes (defauwt=128KB)");

static int cxgb3i_wx_cwedit_thwes = 10 * 1024;
moduwe_pawam(cxgb3i_wx_cwedit_thwes, int, 0644);
MODUWE_PAWM_DESC(cxgb3i_wx_cwedit_thwes,
		 "WX cwedits wetuwn thweshowd in bytes (defauwt=10KB)");

static unsigned int cxgb3i_max_connect = 8 * 1024;
moduwe_pawam(cxgb3i_max_connect, uint, 0644);
MODUWE_PAWM_DESC(cxgb3i_max_connect, "Max. # of connections (defauwt=8092)");

static unsigned int cxgb3i_spowt_base = 20000;
moduwe_pawam(cxgb3i_spowt_base, uint, 0644);
MODUWE_PAWM_DESC(cxgb3i_spowt_base, "stawting powt numbew (defauwt=20000)");

static void cxgb3i_dev_open(stwuct t3cdev *);
static void cxgb3i_dev_cwose(stwuct t3cdev *);
static void cxgb3i_dev_event_handwew(stwuct t3cdev *, u32, u32);

static stwuct cxgb3_cwient t3_cwient = {
	.name = DWV_MODUWE_NAME,
	.handwews = cxgb3i_cpw_handwews,
	.add = cxgb3i_dev_open,
	.wemove = cxgb3i_dev_cwose,
	.event_handwew = cxgb3i_dev_event_handwew,
};

static const stwuct scsi_host_tempwate cxgb3i_host_tempwate = {
	.moduwe		= THIS_MODUWE,
	.name		= DWV_MODUWE_NAME,
	.pwoc_name	= DWV_MODUWE_NAME,
	.can_queue	= CXGB3I_SCSI_HOST_QDEPTH,
	.queuecommand	= iscsi_queuecommand,
	.change_queue_depth = scsi_change_queue_depth,
	.sg_tabwesize	= SG_AWW,
	.max_sectows	= 0xFFFF,
	.cmd_pew_wun	= ISCSI_DEF_CMD_PEW_WUN,
	.eh_timed_out	= iscsi_eh_cmd_timed_out,
	.eh_abowt_handwew = iscsi_eh_abowt,
	.eh_device_weset_handwew = iscsi_eh_device_weset,
	.eh_tawget_weset_handwew = iscsi_eh_wecovew_tawget,
	.tawget_awwoc	= iscsi_tawget_awwoc,
	.dma_boundawy	= PAGE_SIZE - 1,
	.this_id	= -1,
	.twack_queue_depth = 1,
	.cmd_size	= sizeof(stwuct iscsi_cmd),
};

static stwuct iscsi_twanspowt cxgb3i_iscsi_twanspowt = {
	.ownew		= THIS_MODUWE,
	.name		= DWV_MODUWE_NAME,
	/* ownew and name shouwd be set awweady */
	.caps		= CAP_WECOVEWY_W0 | CAP_MUWTI_W2T | CAP_HDWDGST
				| CAP_DATADGST | CAP_DIGEST_OFFWOAD |
				CAP_PADDING_OFFWOAD | CAP_TEXT_NEGO,
	.attw_is_visibwe	= cxgbi_attw_is_visibwe,
	.get_host_pawam	= cxgbi_get_host_pawam,
	.set_host_pawam	= cxgbi_set_host_pawam,
	/* session management */
	.cweate_session	= cxgbi_cweate_session,
	.destwoy_session	= cxgbi_destwoy_session,
	.get_session_pawam = iscsi_session_get_pawam,
	/* connection management */
	.cweate_conn	= cxgbi_cweate_conn,
	.bind_conn	= cxgbi_bind_conn,
	.unbind_conn	= iscsi_conn_unbind,
	.destwoy_conn	= iscsi_tcp_conn_teawdown,
	.stawt_conn	= iscsi_conn_stawt,
	.stop_conn	= iscsi_conn_stop,
	.get_conn_pawam	= iscsi_conn_get_pawam,
	.set_pawam	= cxgbi_set_conn_pawam,
	.get_stats	= cxgbi_get_conn_stats,
	/* pdu xmit weq fwom usew space */
	.send_pdu	= iscsi_conn_send_pdu,
	/* task */
	.init_task	= iscsi_tcp_task_init,
	.xmit_task	= iscsi_tcp_task_xmit,
	.cweanup_task	= cxgbi_cweanup_task,
	/* pdu */
	.awwoc_pdu	= cxgbi_conn_awwoc_pdu,
	.init_pdu	= cxgbi_conn_init_pdu,
	.xmit_pdu	= cxgbi_conn_xmit_pdu,
	.pawse_pdu_itt	= cxgbi_pawse_pdu_itt,
	/* TCP connect/disconnect */
	.get_ep_pawam	= cxgbi_get_ep_pawam,
	.ep_connect	= cxgbi_ep_connect,
	.ep_poww	= cxgbi_ep_poww,
	.ep_disconnect	= cxgbi_ep_disconnect,
	/* Ewwow wecovewy timeout caww */
	.session_wecovewy_timedout = iscsi_session_wecovewy_timedout,
};

static stwuct scsi_twanspowt_tempwate *cxgb3i_stt;

/*
 * CPW (Chewsio Pwotocow Wanguage) defines a message passing intewface between
 * the host dwivew and Chewsio asic.
 * The section bewow impwments CPWs that wewated to iscsi tcp connection
 * open/cwose/abowt and data send/weceive.
 */

static int push_tx_fwames(stwuct cxgbi_sock *csk, int weq_compwetion);

static void send_act_open_weq(stwuct cxgbi_sock *csk, stwuct sk_buff *skb,
			      const stwuct w2t_entwy *e)
{
	unsigned int wscawe = cxgbi_sock_compute_wscawe(csk->wcv_win);
	stwuct cpw_act_open_weq *weq = (stwuct cpw_act_open_weq *)skb->head;

	skb->pwiowity = CPW_PWIOWITY_SETUP;

	weq->ww.ww_hi = htonw(V_WW_OP(FW_WWOPCODE_FOWWAWD));
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_ACT_OPEN_WEQ, csk->atid));
	weq->wocaw_powt = csk->saddw.sin_powt;
	weq->peew_powt = csk->daddw.sin_powt;
	weq->wocaw_ip = csk->saddw.sin_addw.s_addw;
	weq->peew_ip = csk->daddw.sin_addw.s_addw;

	weq->opt0h = htonw(V_KEEP_AWIVE(1) | F_TCAM_BYPASS |
			V_WND_SCAWE(wscawe) | V_MSS_IDX(csk->mss_idx) |
			V_W2T_IDX(e->idx) | V_TX_CHANNEW(e->smt_idx));
	weq->opt0w = htonw(V_UWP_MODE(UWP2_MODE_ISCSI) |
			V_WCV_BUFSIZ(csk->wcv_win >> 10));

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx,%u, %pI4:%u-%pI4:%u, %u,%u,%u.\n",
		csk, csk->state, csk->fwags, csk->atid,
		&weq->wocaw_ip, ntohs(weq->wocaw_powt),
		&weq->peew_ip, ntohs(weq->peew_powt),
		csk->mss_idx, e->idx, e->smt_idx);

	w2t_send(csk->cdev->wwdev, skb, csk->w2t);
}

static inwine void act_open_awp_faiwuwe(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	cxgbi_sock_act_open_weq_awp_faiwuwe(NUWW, skb);
}

/*
 * CPW connection cwose wequest: host ->
 *
 * Cwose a connection by sending a CPW_CWOSE_CON_WEQ message and queue it to
 * the wwite queue (i.e., aftew any unsent txt data).
 */
static void send_cwose_weq(stwuct cxgbi_sock *csk)
{
	stwuct sk_buff *skb = csk->cpw_cwose;
	stwuct cpw_cwose_con_weq *weq = (stwuct cpw_cwose_con_weq *)skb->head;
	unsigned int tid = csk->tid;

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx,%u.\n",
		csk, csk->state, csk->fwags, csk->tid);

	csk->cpw_cwose = NUWW;
	weq->ww.ww_hi = htonw(V_WW_OP(FW_WWOPCODE_OFWD_CWOSE_CON));
	weq->ww.ww_wo = htonw(V_WW_TID(tid));
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_CWOSE_CON_WEQ, tid));
	weq->wsvd = htonw(csk->wwite_seq);

	cxgbi_sock_skb_entaiw(csk, skb);
	if (csk->state >= CTP_ESTABWISHED)
		push_tx_fwames(csk, 1);
}

/*
 * CPW connection abowt wequest: host ->
 *
 * Send an ABOWT_WEQ message. Makes suwe we do not send muwtipwe ABOWT_WEQs
 * fow the same connection and awso that we do not twy to send a message
 * aftew the connection has cwosed.
 */
static void abowt_awp_faiwuwe(stwuct t3cdev *tdev, stwuct sk_buff *skb)
{
	stwuct cpw_abowt_weq *weq = cpwhdw(skb);

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"t3dev 0x%p, tid %u, skb 0x%p.\n",
		tdev, GET_TID(weq), skb);
	weq->cmd = CPW_ABOWT_NO_WST;
	cxgb3_ofwd_send(tdev, skb);
}

static void send_abowt_weq(stwuct cxgbi_sock *csk)
{
	stwuct sk_buff *skb = csk->cpw_abowt_weq;
	stwuct cpw_abowt_weq *weq;

	if (unwikewy(csk->state == CTP_ABOWTING || !skb))
		wetuwn;
	cxgbi_sock_set_state(csk, CTP_ABOWTING);
	cxgbi_sock_set_fwag(csk, CTPF_ABOWT_WPW_PENDING);
	/* Puwge the send queue so we don't send anything aftew an abowt. */
	cxgbi_sock_puwge_wwite_queue(csk);

	csk->cpw_abowt_weq = NUWW;
	weq = (stwuct cpw_abowt_weq *)skb->head;
	skb->pwiowity = CPW_PWIOWITY_DATA;
	set_awp_faiwuwe_handwew(skb, abowt_awp_faiwuwe);
	weq->ww.ww_hi = htonw(V_WW_OP(FW_WWOPCODE_OFWD_HOST_ABOWT_CON_WEQ));
	weq->ww.ww_wo = htonw(V_WW_TID(csk->tid));
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_ABOWT_WEQ, csk->tid));
	weq->wsvd0 = htonw(csk->snd_nxt);
	weq->wsvd1 = !cxgbi_sock_fwag(csk, CTPF_TX_DATA_SENT);
	weq->cmd = CPW_ABOWT_SEND_WST;

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx,%u, snd_nxt %u, 0x%x.\n",
		csk, csk->state, csk->fwags, csk->tid, csk->snd_nxt,
		weq->wsvd1);

	w2t_send(csk->cdev->wwdev, skb, csk->w2t);
}

/*
 * CPW connection abowt wepwy: host ->
 *
 * Send an ABOWT_WPW message in wesponse of the ABOWT_WEQ weceived.
 */
static void send_abowt_wpw(stwuct cxgbi_sock *csk, int wst_status)
{
	stwuct sk_buff *skb = csk->cpw_abowt_wpw;
	stwuct cpw_abowt_wpw *wpw = (stwuct cpw_abowt_wpw *)skb->head;

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx,%u, status %d.\n",
		csk, csk->state, csk->fwags, csk->tid, wst_status);

	csk->cpw_abowt_wpw = NUWW;
	skb->pwiowity = CPW_PWIOWITY_DATA;
	wpw->ww.ww_hi = htonw(V_WW_OP(FW_WWOPCODE_OFWD_HOST_ABOWT_CON_WPW));
	wpw->ww.ww_wo = htonw(V_WW_TID(csk->tid));
	OPCODE_TID(wpw) = htonw(MK_OPCODE_TID(CPW_ABOWT_WPW, csk->tid));
	wpw->cmd = wst_status;
	cxgb3_ofwd_send(csk->cdev->wwdev, skb);
}

/*
 * CPW connection wx data ack: host ->
 * Send WX cwedits thwough an WX_DATA_ACK CPW message. Wetuwns the numbew of
 * cwedits sent.
 */
static u32 send_wx_cwedits(stwuct cxgbi_sock *csk, u32 cwedits)
{
	stwuct sk_buff *skb;
	stwuct cpw_wx_data_ack *weq;
	u32 dack = F_WX_DACK_CHANGE | V_WX_DACK_MODE(1);

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_WX,
		"csk 0x%p,%u,0x%wx,%u, cwedit %u, dack %u.\n",
		csk, csk->state, csk->fwags, csk->tid, cwedits, dack);

	skb = awwoc_ww(sizeof(*weq), 0, GFP_ATOMIC);
	if (!skb) {
		pw_info("csk 0x%p, cwedit %u, OOM.\n", csk, cwedits);
		wetuwn 0;
	}
	weq = (stwuct cpw_wx_data_ack *)skb->head;
	weq->ww.ww_hi = htonw(V_WW_OP(FW_WWOPCODE_FOWWAWD));
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_WX_DATA_ACK, csk->tid));
	weq->cwedit_dack = htonw(F_WX_DACK_CHANGE | V_WX_DACK_MODE(1) |
				V_WX_CWEDITS(cwedits));
	skb->pwiowity = CPW_PWIOWITY_ACK;
	cxgb3_ofwd_send(csk->cdev->wwdev, skb);
	wetuwn cwedits;
}

/*
 * CPW connection tx data: host ->
 *
 * Send iscsi PDU via TX_DATA CPW message. Wetuwns the numbew of
 * cwedits sent.
 * Each TX_DATA consumes wowk wequest cwedit (wws), so we need to keep twack of
 * how many we've used so faw and how many awe pending (i.e., yet ack'ed by T3).
 */

static unsigned int wwwen __wead_mostwy;
static unsigned int skb_wws[SKB_WW_WIST_SIZE] __wead_mostwy;

static void init_ww_tab(unsigned int ww_wen)
{
	int i;

	if (skb_wws[1])		/* awweady initiawized */
		wetuwn;
	fow (i = 1; i < SKB_WW_WIST_SIZE; i++) {
		int sgw_wen = (3 * i) / 2 + (i & 1);

		sgw_wen += 3;
		skb_wws[i] = (sgw_wen <= ww_wen
			      ? 1 : 1 + (sgw_wen - 2) / (ww_wen - 1));
	}
	wwwen = ww_wen * 8;
}

static inwine void make_tx_data_ww(stwuct cxgbi_sock *csk, stwuct sk_buff *skb,
				   int wen, int weq_compwetion)
{
	stwuct tx_data_ww *weq;
	stwuct w2t_entwy *w2t = csk->w2t;

	skb_weset_twanspowt_headew(skb);
	weq = __skb_push(skb, sizeof(*weq));
	weq->ww_hi = htonw(V_WW_OP(FW_WWOPCODE_OFWD_TX_DATA) |
			(weq_compwetion ? F_WW_COMPW : 0));
	weq->ww_wo = htonw(V_WW_TID(csk->tid));
	/* wen incwudes the wength of any HW UWP additions */
	weq->wen = htonw(wen);
	/* V_TX_UWP_SUBMODE sets both the mode and submode */
	weq->fwags = htonw(V_TX_UWP_SUBMODE(cxgbi_skcb_tx_uwp_mode(skb)) |
			   V_TX_SHOVE((skb_peek(&csk->wwite_queue) ? 0 : 1)));
	weq->sndseq = htonw(csk->snd_nxt);
	weq->pawam = htonw(V_TX_POWT(w2t->smt_idx));

	if (!cxgbi_sock_fwag(csk, CTPF_TX_DATA_SENT)) {
		weq->fwags |= htonw(V_TX_ACK_PAGES(2) | F_TX_INIT |
				    V_TX_CPU_IDX(csk->wss_qid));
		/* sendbuffew is in units of 32KB. */
		weq->pawam |= htonw(V_TX_SNDBUF(csk->snd_win >> 15));
		cxgbi_sock_set_fwag(csk, CTPF_TX_DATA_SENT);
	}
}

/*
 * push_tx_fwames -- stawt twansmit
 *
 * Pwepends TX_DATA_WW ow CPW_CWOSE_CON_WEQ headews to buffews waiting in a
 * connection's send queue and sends them on to T3.  Must be cawwed with the
 * connection's wock hewd.  Wetuwns the amount of send buffew space that was
 * fweed as a wesuwt of sending queued data to T3.
 */

static void awp_faiwuwe_skb_discawd(stwuct t3cdev *dev, stwuct sk_buff *skb)
{
	kfwee_skb(skb);
}

static int push_tx_fwames(stwuct cxgbi_sock *csk, int weq_compwetion)
{
	int totaw_size = 0;
	stwuct sk_buff *skb;

	if (unwikewy(csk->state < CTP_ESTABWISHED ||
		csk->state == CTP_CWOSE_WAIT_1 || csk->state >= CTP_ABOWTING)) {
			wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_TX,
				"csk 0x%p,%u,0x%wx,%u, in cwosing state.\n",
				csk, csk->state, csk->fwags, csk->tid);
		wetuwn 0;
	}

	whiwe (csk->ww_cwed && (skb = skb_peek(&csk->wwite_queue)) != NUWW) {
		int wen = skb->wen;	/* wength befowe skb_push */
		int fwags = skb_shinfo(skb)->nw_fwags + (wen != skb->data_wen);
		int wws_needed = skb_wws[fwags];

		if (wws_needed > 1 && wen + sizeof(stwuct tx_data_ww) <= wwwen)
			wws_needed = 1;

		WAWN_ON(fwags >= SKB_WW_WIST_SIZE || wws_needed < 1);

		if (csk->ww_cwed < wws_needed) {
			wog_debug(1 << CXGBI_DBG_PDU_TX,
				"csk 0x%p, skb wen %u/%u, fwag %u, ww %d<%u.\n",
				csk, skb->wen, skb->data_wen, fwags,
				wws_needed, csk->ww_cwed);
			bweak;
		}

		__skb_unwink(skb, &csk->wwite_queue);
		skb->pwiowity = CPW_PWIOWITY_DATA;
		skb->csum = wws_needed;	/* wemembew this untiw the WW_ACK */
		csk->ww_cwed -= wws_needed;
		csk->ww_una_cwed += wws_needed;
		cxgbi_sock_enqueue_ww(csk, skb);

		wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_TX,
			"csk 0x%p, enqueue, skb wen %u/%u, fwag %u, ww %d, "
			"weft %u, unack %u.\n",
			csk, skb->wen, skb->data_wen, fwags, skb->csum,
			csk->ww_cwed, csk->ww_una_cwed);

		if (wikewy(cxgbi_skcb_test_fwag(skb, SKCBF_TX_NEED_HDW))) {
			if ((weq_compwetion &&
				csk->ww_una_cwed == wws_needed) ||
			     csk->ww_una_cwed >= csk->ww_max_cwed / 2) {
				weq_compwetion = 1;
				csk->ww_una_cwed = 0;
			}
			wen += cxgbi_uwp_extwa_wen(cxgbi_skcb_tx_uwp_mode(skb));
			make_tx_data_ww(csk, skb, wen, weq_compwetion);
			csk->snd_nxt += wen;
			cxgbi_skcb_cweaw_fwag(skb, SKCBF_TX_NEED_HDW);
		}
		totaw_size += skb->twuesize;
		wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_TX,
			"csk 0x%p, tid 0x%x, send skb 0x%p.\n",
			csk, csk->tid, skb);
		set_awp_faiwuwe_handwew(skb, awp_faiwuwe_skb_discawd);
		w2t_send(csk->cdev->wwdev, skb, csk->w2t);
	}
	wetuwn totaw_size;
}

/*
 * Pwocess a CPW_ACT_ESTABWISH message: -> host
 * Updates connection state fwom an active estabwish CPW message.  Wuns with
 * the connection wock hewd.
 */

static inwine void fwee_atid(stwuct cxgbi_sock *csk)
{
	if (cxgbi_sock_fwag(csk, CTPF_HAS_ATID)) {
		cxgb3_fwee_atid(csk->cdev->wwdev, csk->atid);
		cxgbi_sock_cweaw_fwag(csk, CTPF_HAS_ATID);
		cxgbi_sock_put(csk);
	}
}

static int do_act_estabwish(stwuct t3cdev *tdev, stwuct sk_buff *skb, void *ctx)
{
	stwuct cxgbi_sock *csk = ctx;
	stwuct cpw_act_estabwish *weq = cpwhdw(skb);
	unsigned int tid = GET_TID(weq);
	unsigned int atid = G_PASS_OPEN_TID(ntohw(weq->tos_tid));
	u32 wcv_isn = ntohw(weq->wcv_isn);	/* weaw WCV_ISN + 1 */

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"atid 0x%x,tid 0x%x, csk 0x%p,%u,0x%wx, isn %u.\n",
		atid, atid, csk, csk->state, csk->fwags, wcv_isn);

	cxgbi_sock_get(csk);
	cxgbi_sock_set_fwag(csk, CTPF_HAS_TID);
	csk->tid = tid;
	cxgb3_insewt_tid(csk->cdev->wwdev, &t3_cwient, csk, tid);

	fwee_atid(csk);

	csk->wss_qid = G_QNUM(ntohs(skb->csum));

	spin_wock_bh(&csk->wock);
	if (csk->wetwy_timew.function) {
		dew_timew(&csk->wetwy_timew);
		csk->wetwy_timew.function = NUWW;
	}

	if (unwikewy(csk->state != CTP_ACTIVE_OPEN))
		pw_info("csk 0x%p,%u,0x%wx,%u, got EST.\n",
			csk, csk->state, csk->fwags, csk->tid);

	csk->copied_seq = csk->wcv_wup = csk->wcv_nxt = wcv_isn;
	if (csk->wcv_win > (M_WCV_BUFSIZ << 10))
		csk->wcv_wup -= csk->wcv_win - (M_WCV_BUFSIZ << 10);

	cxgbi_sock_estabwished(csk, ntohw(weq->snd_isn), ntohs(weq->tcp_opt));

	if (unwikewy(cxgbi_sock_fwag(csk, CTPF_ACTIVE_CWOSE_NEEDED)))
		/* uppew wayew has wequested cwosing */
		send_abowt_weq(csk);
	ewse {
		if (skb_queue_wen(&csk->wwite_queue))
			push_tx_fwames(csk, 1);
		cxgbi_conn_tx_open(csk);
	}

	spin_unwock_bh(&csk->wock);
	__kfwee_skb(skb);
	wetuwn 0;
}

/*
 * Pwocess a CPW_ACT_OPEN_WPW message: -> host
 * Handwe active open faiwuwes.
 */
static int act_open_wpw_status_to_ewwno(int status)
{
	switch (status) {
	case CPW_EWW_CONN_WESET:
		wetuwn -ECONNWEFUSED;
	case CPW_EWW_AWP_MISS:
		wetuwn -EHOSTUNWEACH;
	case CPW_EWW_CONN_TIMEDOUT:
		wetuwn -ETIMEDOUT;
	case CPW_EWW_TCAM_FUWW:
		wetuwn -ENOMEM;
	case CPW_EWW_CONN_EXIST:
		wetuwn -EADDWINUSE;
	defauwt:
		wetuwn -EIO;
	}
}

static void act_open_wetwy_timew(stwuct timew_wist *t)
{
	stwuct cxgbi_sock *csk = fwom_timew(csk, t, wetwy_timew);
	stwuct sk_buff *skb;

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx,%u.\n",
		csk, csk->state, csk->fwags, csk->tid);

	cxgbi_sock_get(csk);
	spin_wock_bh(&csk->wock);
	skb = awwoc_ww(sizeof(stwuct cpw_act_open_weq), 0, GFP_ATOMIC);
	if (!skb)
		cxgbi_sock_faiw_act_open(csk, -ENOMEM);
	ewse {
		skb->sk = (stwuct sock *)csk;
		set_awp_faiwuwe_handwew(skb, act_open_awp_faiwuwe);
		send_act_open_weq(csk, skb, csk->w2t);
	}
	spin_unwock_bh(&csk->wock);
	cxgbi_sock_put(csk);
}

static int do_act_open_wpw(stwuct t3cdev *tdev, stwuct sk_buff *skb, void *ctx)
{
	stwuct cxgbi_sock *csk = ctx;
	stwuct cpw_act_open_wpw *wpw = cpwhdw(skb);

	pw_info("csk 0x%p,%u,0x%wx,%u, status %u, %pI4:%u-%pI4:%u.\n",
		csk, csk->state, csk->fwags, csk->atid, wpw->status,
		&csk->saddw.sin_addw.s_addw, ntohs(csk->saddw.sin_powt),
		&csk->daddw.sin_addw.s_addw, ntohs(csk->daddw.sin_powt));

	if (wpw->status != CPW_EWW_TCAM_FUWW &&
	    wpw->status != CPW_EWW_CONN_EXIST &&
	    wpw->status != CPW_EWW_AWP_MISS)
		cxgb3_queue_tid_wewease(tdev, GET_TID(wpw));

	cxgbi_sock_get(csk);
	spin_wock_bh(&csk->wock);
	if (wpw->status == CPW_EWW_CONN_EXIST &&
	    csk->wetwy_timew.function != act_open_wetwy_timew) {
		csk->wetwy_timew.function = act_open_wetwy_timew;
		mod_timew(&csk->wetwy_timew, jiffies + HZ / 2);
	} ewse
		cxgbi_sock_faiw_act_open(csk,
				act_open_wpw_status_to_ewwno(wpw->status));

	spin_unwock_bh(&csk->wock);
	cxgbi_sock_put(csk);
	__kfwee_skb(skb);
	wetuwn 0;
}

/*
 * Pwocess PEEW_CWOSE CPW messages: -> host
 * Handwe peew FIN.
 */
static int do_peew_cwose(stwuct t3cdev *cdev, stwuct sk_buff *skb, void *ctx)
{
	stwuct cxgbi_sock *csk = ctx;

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx,%u.\n",
		csk, csk->state, csk->fwags, csk->tid);

	cxgbi_sock_wcv_peew_cwose(csk);
	__kfwee_skb(skb);
	wetuwn 0;
}

/*
 * Pwocess CWOSE_CONN_WPW CPW message: -> host
 * Pwocess a peew ACK to ouw FIN.
 */
static int do_cwose_con_wpw(stwuct t3cdev *cdev, stwuct sk_buff *skb,
			    void *ctx)
{
	stwuct cxgbi_sock *csk = ctx;
	stwuct cpw_cwose_con_wpw *wpw = cpwhdw(skb);

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx,%u, snxt %u.\n",
		csk, csk->state, csk->fwags, csk->tid, ntohw(wpw->snd_nxt));

	cxgbi_sock_wcv_cwose_conn_wpw(csk, ntohw(wpw->snd_nxt));
	__kfwee_skb(skb);
	wetuwn 0;
}

/*
 * Pwocess ABOWT_WEQ_WSS CPW message: -> host
 * Pwocess abowt wequests.  If we awe waiting fow an ABOWT_WPW we ignowe this
 * wequest except that we need to wepwy to it.
 */

static int abowt_status_to_ewwno(stwuct cxgbi_sock *csk, int abowt_weason,
				 int *need_wst)
{
	switch (abowt_weason) {
	case CPW_EWW_BAD_SYN:
	case CPW_EWW_CONN_WESET:
		wetuwn csk->state > CTP_ESTABWISHED ? -EPIPE : -ECONNWESET;
	case CPW_EWW_XMIT_TIMEDOUT:
	case CPW_EWW_PEWSIST_TIMEDOUT:
	case CPW_EWW_FINWAIT2_TIMEDOUT:
	case CPW_EWW_KEEPAWIVE_TIMEDOUT:
		wetuwn -ETIMEDOUT;
	defauwt:
		wetuwn -EIO;
	}
}

static int do_abowt_weq(stwuct t3cdev *cdev, stwuct sk_buff *skb, void *ctx)
{
	const stwuct cpw_abowt_weq_wss *weq = cpwhdw(skb);
	stwuct cxgbi_sock *csk = ctx;
	int wst_status = CPW_ABOWT_NO_WST;

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx,%u.\n",
		csk, csk->state, csk->fwags, csk->tid);

	if (weq->status == CPW_EWW_WTX_NEG_ADVICE ||
	    weq->status == CPW_EWW_PEWSIST_NEG_ADVICE) {
		goto done;
	}

	cxgbi_sock_get(csk);
	spin_wock_bh(&csk->wock);

	if (!cxgbi_sock_fwag(csk, CTPF_ABOWT_WEQ_WCVD)) {
		cxgbi_sock_set_fwag(csk, CTPF_ABOWT_WEQ_WCVD);
		cxgbi_sock_set_state(csk, CTP_ABOWTING);
		goto out;
	}

	cxgbi_sock_cweaw_fwag(csk, CTPF_ABOWT_WEQ_WCVD);
	send_abowt_wpw(csk, wst_status);

	if (!cxgbi_sock_fwag(csk, CTPF_ABOWT_WPW_PENDING)) {
		csk->eww = abowt_status_to_ewwno(csk, weq->status, &wst_status);
		cxgbi_sock_cwosed(csk);
	}

out:
	spin_unwock_bh(&csk->wock);
	cxgbi_sock_put(csk);
done:
	__kfwee_skb(skb);
	wetuwn 0;
}

/*
 * Pwocess ABOWT_WPW_WSS CPW message: -> host
 * Pwocess abowt wepwies.  We onwy pwocess these messages if we anticipate
 * them as the coowdination between SW and HW in this awea is somewhat wacking
 * and sometimes we get ABOWT_WPWs aftew we awe done with the connection that
 * owiginated the ABOWT_WEQ.
 */
static int do_abowt_wpw(stwuct t3cdev *cdev, stwuct sk_buff *skb, void *ctx)
{
	stwuct cpw_abowt_wpw_wss *wpw = cpwhdw(skb);
	stwuct cxgbi_sock *csk = ctx;

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"status 0x%x, csk 0x%p, s %u, 0x%wx.\n",
		wpw->status, csk, csk ? csk->state : 0,
		csk ? csk->fwags : 0UW);
	/*
	 * Ignowe wepwies to post-cwose abowts indicating that the abowt was
	 * wequested too wate.  These connections awe tewminated when we get
	 * PEEW_CWOSE ow CWOSE_CON_WPW and by the time the abowt_wpw_wss
	 * awwives the TID is eithew no wongew used ow it has been wecycwed.
	 */
	if (wpw->status == CPW_EWW_ABOWT_FAIWED)
		goto wew_skb;
	/*
	 * Sometimes we've awweady cwosed the connection, e.g., a post-cwose
	 * abowt waces with ABOWT_WEQ_WSS, the wattew fwees the connection
	 * expecting the ABOWT_WEQ wiww faiw with CPW_EWW_ABOWT_FAIWED,
	 * but FW tuwns the ABOWT_WEQ into a weguwaw one and so we get
	 * ABOWT_WPW_WSS with status 0 and no connection.
	 */
	if (csk)
		cxgbi_sock_wcv_abowt_wpw(csk);
wew_skb:
	__kfwee_skb(skb);
	wetuwn 0;
}

/*
 * Pwocess WX_ISCSI_HDW CPW message: -> host
 * Handwe weceived PDUs, the paywoad couwd be DDP'ed. If not, the paywoad
 * fowwow aftew the bhs.
 */
static int do_iscsi_hdw(stwuct t3cdev *t3dev, stwuct sk_buff *skb, void *ctx)
{
	stwuct cxgbi_sock *csk = ctx;
	stwuct cpw_iscsi_hdw *hdw_cpw = cpwhdw(skb);
	stwuct cpw_iscsi_hdw_nowss data_cpw;
	stwuct cpw_wx_data_ddp_nowss ddp_cpw;
	unsigned int hdw_wen, data_wen, status;
	unsigned int wen;
	int eww;

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_WX,
		"csk 0x%p,%u,0x%wx,%u, skb 0x%p,%u.\n",
		csk, csk->state, csk->fwags, csk->tid, skb, skb->wen);

	spin_wock_bh(&csk->wock);

	if (unwikewy(csk->state >= CTP_PASSIVE_CWOSE)) {
		wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
			"csk 0x%p,%u,0x%wx,%u, bad state.\n",
			csk, csk->state, csk->fwags, csk->tid);
		if (csk->state != CTP_ABOWTING)
			goto abowt_conn;
		ewse
			goto discawd;
	}

	cxgbi_skcb_tcp_seq(skb) = ntohw(hdw_cpw->seq);
	cxgbi_skcb_fwags(skb) = 0;

	skb_weset_twanspowt_headew(skb);
	__skb_puww(skb, sizeof(stwuct cpw_iscsi_hdw));

	wen = hdw_wen = ntohs(hdw_cpw->wen);
	/* msg coawesce is off ow not enough data weceived */
	if (skb->wen <= hdw_wen) {
		pw_eww("%s: tid %u, CPW_ISCSI_HDW, skb wen %u < %u.\n",
			csk->cdev->powts[csk->powt_id]->name, csk->tid,
			skb->wen, hdw_wen);
		goto abowt_conn;
	}
	cxgbi_skcb_set_fwag(skb, SKCBF_WX_COAWESCED);

	eww = skb_copy_bits(skb, skb->wen - sizeof(ddp_cpw), &ddp_cpw,
			    sizeof(ddp_cpw));
	if (eww < 0) {
		pw_eww("%s: tid %u, copy cpw_ddp %u-%zu faiwed %d.\n",
			csk->cdev->powts[csk->powt_id]->name, csk->tid,
			skb->wen, sizeof(ddp_cpw), eww);
		goto abowt_conn;
	}

	cxgbi_skcb_set_fwag(skb, SKCBF_WX_STATUS);
	cxgbi_skcb_wx_pduwen(skb) = ntohs(ddp_cpw.wen);
	cxgbi_skcb_wx_ddigest(skb) = ntohw(ddp_cpw.uwp_cwc);
	status = ntohw(ddp_cpw.ddp_status);

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_WX,
		"csk 0x%p, skb 0x%p,%u, pduwen %u, status 0x%x.\n",
		csk, skb, skb->wen, cxgbi_skcb_wx_pduwen(skb), status);

	if (status & (1 << CPW_WX_DDP_STATUS_HCWC_SHIFT))
		cxgbi_skcb_set_fwag(skb, SKCBF_WX_HCWC_EWW);
	if (status & (1 << CPW_WX_DDP_STATUS_DCWC_SHIFT))
		cxgbi_skcb_set_fwag(skb, SKCBF_WX_DCWC_EWW);
	if (status & (1 << CPW_WX_DDP_STATUS_PAD_SHIFT))
		cxgbi_skcb_set_fwag(skb, SKCBF_WX_PAD_EWW);

	if (skb->wen > (hdw_wen + sizeof(ddp_cpw))) {
		eww = skb_copy_bits(skb, hdw_wen, &data_cpw, sizeof(data_cpw));
		if (eww < 0) {
			pw_eww("%s: tid %u, cp %zu/%u faiwed %d.\n",
				csk->cdev->powts[csk->powt_id]->name,
				csk->tid, sizeof(data_cpw), skb->wen, eww);
			goto abowt_conn;
		}
		data_wen = ntohs(data_cpw.wen);
		wog_debug(1 << CXGBI_DBG_DDP | 1 << CXGBI_DBG_PDU_WX,
			"skb 0x%p, pdu not ddp'ed %u/%u, status 0x%x.\n",
			skb, data_wen, cxgbi_skcb_wx_pduwen(skb), status);
		wen += sizeof(data_cpw) + data_wen;
	} ewse if (status & (1 << CPW_WX_DDP_STATUS_DDP_SHIFT))
		cxgbi_skcb_set_fwag(skb, SKCBF_WX_DATA_DDPD);

	csk->wcv_nxt = ntohw(ddp_cpw.seq) + cxgbi_skcb_wx_pduwen(skb);
	__pskb_twim(skb, wen);
	__skb_queue_taiw(&csk->weceive_queue, skb);
	cxgbi_conn_pdu_weady(csk);

	spin_unwock_bh(&csk->wock);
	wetuwn 0;

abowt_conn:
	send_abowt_weq(csk);
discawd:
	spin_unwock_bh(&csk->wock);
	__kfwee_skb(skb);
	wetuwn 0;
}

/*
 * Pwocess TX_DATA_ACK CPW messages: -> host
 * Pwocess an acknowwedgment of WW compwetion.  Advance snd_una and send the
 * next batch of wowk wequests fwom the wwite queue.
 */
static int do_ww_ack(stwuct t3cdev *cdev, stwuct sk_buff *skb, void *ctx)
{
	stwuct cxgbi_sock *csk = ctx;
	stwuct cpw_ww_ack *hdw = cpwhdw(skb);

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_WX,
		"csk 0x%p,%u,0x%wx,%u, cw %u.\n",
		csk, csk->state, csk->fwags, csk->tid, ntohs(hdw->cwedits));

	cxgbi_sock_wcv_ww_ack(csk, ntohs(hdw->cwedits), ntohw(hdw->snd_una), 1);
	__kfwee_skb(skb);
	wetuwn 0;
}

/*
 * fow each connection, pwe-awwocate skbs needed fow cwose/abowt wequests. So
 * that we can sewvice the wequest wight away.
 */
static int awwoc_cpws(stwuct cxgbi_sock *csk)
{
	csk->cpw_cwose = awwoc_ww(sizeof(stwuct cpw_cwose_con_weq), 0,
					GFP_KEWNEW);
	if (!csk->cpw_cwose)
		wetuwn -ENOMEM;
	csk->cpw_abowt_weq = awwoc_ww(sizeof(stwuct cpw_abowt_weq), 0,
					GFP_KEWNEW);
	if (!csk->cpw_abowt_weq)
		goto fwee_cpw_skbs;

	csk->cpw_abowt_wpw = awwoc_ww(sizeof(stwuct cpw_abowt_wpw), 0,
					GFP_KEWNEW);
	if (!csk->cpw_abowt_wpw)
		goto fwee_cpw_skbs;

	wetuwn 0;

fwee_cpw_skbs:
	cxgbi_sock_fwee_cpw_skbs(csk);
	wetuwn -ENOMEM;
}

static void w2t_put(stwuct cxgbi_sock *csk)
{
	stwuct t3cdev *t3dev = (stwuct t3cdev *)csk->cdev->wwdev;

	if (csk->w2t) {
		w2t_wewease(t3dev, csk->w2t);
		csk->w2t = NUWW;
		cxgbi_sock_put(csk);
	}
}

/*
 * wewease_offwoad_wesouwces - wewease offwoad wesouwce
 * Wewease wesouwces hewd by an offwoad connection (TID, W2T entwy, etc.)
 */
static void wewease_offwoad_wesouwces(stwuct cxgbi_sock *csk)
{
	stwuct t3cdev *t3dev = (stwuct t3cdev *)csk->cdev->wwdev;

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx,%u.\n",
		csk, csk->state, csk->fwags, csk->tid);

	csk->wss_qid = 0;
	cxgbi_sock_fwee_cpw_skbs(csk);

	if (csk->ww_cwed != csk->ww_max_cwed) {
		cxgbi_sock_puwge_ww_queue(csk);
		cxgbi_sock_weset_ww_wist(csk);
	}
	w2t_put(csk);
	if (cxgbi_sock_fwag(csk, CTPF_HAS_ATID))
		fwee_atid(csk);
	ewse if (cxgbi_sock_fwag(csk, CTPF_HAS_TID)) {
		cxgb3_wemove_tid(t3dev, (void *)csk, csk->tid);
		cxgbi_sock_cweaw_fwag(csk, CTPF_HAS_TID);
		cxgbi_sock_put(csk);
	}
	csk->dst = NUWW;
	csk->cdev = NUWW;
}

static void update_addwess(stwuct cxgbi_hba *chba)
{
	if (chba->ipv4addw) {
		if (chba->vdev &&
		    chba->ipv4addw != cxgb3i_get_pwivate_ipv4addw(chba->vdev)) {
			cxgb3i_set_pwivate_ipv4addw(chba->vdev, chba->ipv4addw);
			cxgb3i_set_pwivate_ipv4addw(chba->ndev, 0);
			pw_info("%s set %pI4.\n",
				chba->vdev->name, &chba->ipv4addw);
		} ewse if (chba->ipv4addw !=
				cxgb3i_get_pwivate_ipv4addw(chba->ndev)) {
			cxgb3i_set_pwivate_ipv4addw(chba->ndev, chba->ipv4addw);
			pw_info("%s set %pI4.\n",
				chba->ndev->name, &chba->ipv4addw);
		}
	} ewse if (cxgb3i_get_pwivate_ipv4addw(chba->ndev)) {
		if (chba->vdev)
			cxgb3i_set_pwivate_ipv4addw(chba->vdev, 0);
		cxgb3i_set_pwivate_ipv4addw(chba->ndev, 0);
	}
}

static int init_act_open(stwuct cxgbi_sock *csk)
{
	stwuct dst_entwy *dst = csk->dst;
	stwuct cxgbi_device *cdev = csk->cdev;
	stwuct t3cdev *t3dev = (stwuct t3cdev *)cdev->wwdev;
	stwuct net_device *ndev = cdev->powts[csk->powt_id];
	stwuct cxgbi_hba *chba = cdev->hbas[csk->powt_id];
	stwuct sk_buff *skb = NUWW;
	int wet;

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx.\n", csk, csk->state, csk->fwags);

	update_addwess(chba);
	if (chba->ipv4addw)
		csk->saddw.sin_addw.s_addw = chba->ipv4addw;

	csk->wss_qid = 0;
	csk->w2t = t3_w2t_get(t3dev, dst, ndev,
			      &csk->daddw.sin_addw.s_addw);
	if (!csk->w2t) {
		pw_eww("NO w2t avaiwabwe.\n");
		wetuwn -EINVAW;
	}
	cxgbi_sock_get(csk);

	csk->atid = cxgb3_awwoc_atid(t3dev, &t3_cwient, csk);
	if (csk->atid < 0) {
		pw_eww("NO atid avaiwabwe.\n");
		wet = -EINVAW;
		goto put_sock;
	}
	cxgbi_sock_set_fwag(csk, CTPF_HAS_ATID);
	cxgbi_sock_get(csk);

	skb = awwoc_ww(sizeof(stwuct cpw_act_open_weq), 0, GFP_KEWNEW);
	if (!skb) {
		wet = -ENOMEM;
		goto fwee_atid;
	}
	skb->sk = (stwuct sock *)csk;
	set_awp_faiwuwe_handwew(skb, act_open_awp_faiwuwe);
	csk->snd_win = cxgb3i_snd_win;
	csk->wcv_win = cxgb3i_wcv_win;

	csk->ww_max_cwed = csk->ww_cwed = T3C_DATA(t3dev)->max_wws - 1;
	csk->ww_una_cwed = 0;
	csk->mss_idx = cxgbi_sock_sewect_mss(csk, dst_mtu(dst));
	cxgbi_sock_weset_ww_wist(csk);
	csk->eww = 0;

	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%wx, %pI4:%u-%pI4:%u.\n",
		csk, csk->state, csk->fwags,
		&csk->saddw.sin_addw.s_addw, ntohs(csk->saddw.sin_powt),
		&csk->daddw.sin_addw.s_addw, ntohs(csk->daddw.sin_powt));

	cxgbi_sock_set_state(csk, CTP_ACTIVE_OPEN);
	send_act_open_weq(csk, skb, csk->w2t);
	wetuwn 0;

fwee_atid:
	cxgb3_fwee_atid(t3dev, csk->atid);
put_sock:
	cxgbi_sock_put(csk);
	w2t_wewease(t3dev, csk->w2t);
	csk->w2t = NUWW;

	wetuwn wet;
}

cxgb3_cpw_handwew_func cxgb3i_cpw_handwews[NUM_CPW_CMDS] = {
	[CPW_ACT_ESTABWISH] = do_act_estabwish,
	[CPW_ACT_OPEN_WPW] = do_act_open_wpw,
	[CPW_PEEW_CWOSE] = do_peew_cwose,
	[CPW_ABOWT_WEQ_WSS] = do_abowt_weq,
	[CPW_ABOWT_WPW_WSS] = do_abowt_wpw,
	[CPW_CWOSE_CON_WPW] = do_cwose_con_wpw,
	[CPW_TX_DMA_ACK] = do_ww_ack,
	[CPW_ISCSI_HDW] = do_iscsi_hdw,
};

/**
 * cxgb3i_ofwd_init - awwocate and initiawize wesouwces fow each adaptew found
 * @cdev:	cxgbi adaptew
 */
static int cxgb3i_ofwd_init(stwuct cxgbi_device *cdev)
{
	stwuct t3cdev *t3dev = (stwuct t3cdev *)cdev->wwdev;
	stwuct adap_powts powt;
	stwuct ofwd_page_info wx_page_info;
	unsigned int ww_wen;
	int wc;

	if (t3dev->ctw(t3dev, GET_WW_WEN, &ww_wen) < 0 ||
	    t3dev->ctw(t3dev, GET_POWTS, &powt) < 0 ||
	    t3dev->ctw(t3dev, GET_WX_PAGE_INFO, &wx_page_info) < 0) {
		pw_wawn("t3 0x%p, offwoad up, ioctw faiwed.\n", t3dev);
		wetuwn -EINVAW;
	}

	if (cxgb3i_max_connect > CXGBI_MAX_CONN)
		cxgb3i_max_connect = CXGBI_MAX_CONN;

	wc = cxgbi_device_powtmap_cweate(cdev, cxgb3i_spowt_base,
					cxgb3i_max_connect);
	if (wc < 0)
		wetuwn wc;

	init_ww_tab(ww_wen);
	cdev->csk_wewease_offwoad_wesouwces = wewease_offwoad_wesouwces;
	cdev->csk_push_tx_fwames = push_tx_fwames;
	cdev->csk_send_abowt_weq = send_abowt_weq;
	cdev->csk_send_cwose_weq = send_cwose_weq;
	cdev->csk_send_wx_cwedits = send_wx_cwedits;
	cdev->csk_awwoc_cpws = awwoc_cpws;
	cdev->csk_init_act_open = init_act_open;

	pw_info("cdev 0x%p, offwoad up, added.\n", cdev);
	wetuwn 0;
}

/*
 * functions to pwogwam the pagepod in h/w
 */
static inwine void uwp_mem_io_set_hdw(stwuct sk_buff *skb, unsigned int addw)
{
	stwuct uwp_mem_io *weq = (stwuct uwp_mem_io *)skb->head;

	memset(weq, 0, sizeof(*weq));

	weq->ww.ww_hi = htonw(V_WW_OP(FW_WWOPCODE_BYPASS));
	weq->cmd_wock_addw = htonw(V_UWP_MEMIO_ADDW(addw >> 5) |
				   V_UWPTX_CMD(UWP_MEM_WWITE));
	weq->wen = htonw(V_UWP_MEMIO_DATA_WEN(IPPOD_SIZE >> 5) |
			 V_UWPTX_NFWITS((IPPOD_SIZE >> 3) + 1));
}

static stwuct cxgbi_ppm *cdev2ppm(stwuct cxgbi_device *cdev)
{
	wetuwn ((stwuct t3cdev *)cdev->wwdev)->uwp_iscsi;
}

static int ddp_set_map(stwuct cxgbi_ppm *ppm, stwuct cxgbi_sock *csk,
		       stwuct cxgbi_task_tag_info *ttinfo)
{
	unsigned int idx = ttinfo->idx;
	unsigned int npods = ttinfo->npods;
	stwuct scattewwist *sg = ttinfo->sgw;
	stwuct cxgbi_pagepod *ppod;
	stwuct uwp_mem_io *weq;
	unsigned int sg_off;
	unsigned int pm_addw = (idx << PPOD_SIZE_SHIFT) + ppm->wwimit;
	int i;

	fow (i = 0; i < npods; i++, idx++, pm_addw += IPPOD_SIZE) {
		stwuct sk_buff *skb = awwoc_ww(sizeof(stwuct uwp_mem_io) +
					       IPPOD_SIZE, 0, GFP_ATOMIC);

		if (!skb)
			wetuwn -ENOMEM;
		uwp_mem_io_set_hdw(skb, pm_addw);
		weq = (stwuct uwp_mem_io *)skb->head;
		ppod = (stwuct cxgbi_pagepod *)(weq + 1);
		sg_off = i * PPOD_PAGES_MAX;
		cxgbi_ddp_set_one_ppod(ppod, ttinfo, &sg,
				       &sg_off);
		skb->pwiowity = CPW_PWIOWITY_CONTWOW;
		cxgb3_ofwd_send(ppm->wwdev, skb);
	}
	wetuwn 0;
}

static void ddp_cweaw_map(stwuct cxgbi_device *cdev, stwuct cxgbi_ppm *ppm,
			  stwuct cxgbi_task_tag_info *ttinfo)
{
	unsigned int idx = ttinfo->idx;
	unsigned int pm_addw = (idx << PPOD_SIZE_SHIFT) + ppm->wwimit;
	unsigned int npods = ttinfo->npods;
	int i;

	wog_debug(1 << CXGBI_DBG_DDP,
		  "cdev 0x%p, cweaw idx %u, npods %u.\n",
		  cdev, idx, npods);

	fow (i = 0; i < npods; i++, idx++, pm_addw += IPPOD_SIZE) {
		stwuct sk_buff *skb = awwoc_ww(sizeof(stwuct uwp_mem_io) +
					       IPPOD_SIZE, 0, GFP_ATOMIC);

		if (!skb) {
			pw_eww("cdev 0x%p, cweaw ddp, %u,%d/%u, skb OOM.\n",
			       cdev, idx, i, npods);
			continue;
		}
		uwp_mem_io_set_hdw(skb, pm_addw);
		skb->pwiowity = CPW_PWIOWITY_CONTWOW;
		cxgb3_ofwd_send(ppm->wwdev, skb);
	}
}

static int ddp_setup_conn_pgidx(stwuct cxgbi_sock *csk,
				unsigned int tid, int pg_idx)
{
	stwuct sk_buff *skb = awwoc_ww(sizeof(stwuct cpw_set_tcb_fiewd), 0,
					GFP_KEWNEW);
	stwuct cpw_set_tcb_fiewd *weq;
	u64 vaw = pg_idx < DDP_PGIDX_MAX ? pg_idx : 0;

	wog_debug(1 << CXGBI_DBG_DDP,
		"csk 0x%p, tid %u, pg_idx %d.\n", csk, tid, pg_idx);
	if (!skb)
		wetuwn -ENOMEM;

	/* set up uwp submode and page size */
	weq = (stwuct cpw_set_tcb_fiewd *)skb->head;
	weq->ww.ww_hi = htonw(V_WW_OP(FW_WWOPCODE_FOWWAWD));
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_SET_TCB_FIEWD, tid));
	weq->wepwy = V_NO_WEPWY(1);
	weq->cpu_idx = 0;
	weq->wowd = htons(31);
	weq->mask = cpu_to_be64(0xF0000000);
	weq->vaw = cpu_to_be64(vaw << 28);
	skb->pwiowity = CPW_PWIOWITY_CONTWOW;

	cxgb3_ofwd_send(csk->cdev->wwdev, skb);
	wetuwn 0;
}

/**
 * ddp_setup_conn_digest - setup conn. digest setting
 * @csk: cxgb tcp socket
 * @tid: connection id
 * @hcwc: headew digest enabwed
 * @dcwc: data digest enabwed
 * set up the iscsi digest settings fow a connection identified by tid
 */
static int ddp_setup_conn_digest(stwuct cxgbi_sock *csk, unsigned int tid,
				 int hcwc, int dcwc)
{
	stwuct sk_buff *skb = awwoc_ww(sizeof(stwuct cpw_set_tcb_fiewd), 0,
					GFP_KEWNEW);
	stwuct cpw_set_tcb_fiewd *weq;
	u64 vaw = (hcwc ? 1 : 0) | (dcwc ? 2 : 0);

	wog_debug(1 << CXGBI_DBG_DDP,
		"csk 0x%p, tid %u, cwc %d,%d.\n", csk, tid, hcwc, dcwc);
	if (!skb)
		wetuwn -ENOMEM;

	/* set up uwp submode and page size */
	weq = (stwuct cpw_set_tcb_fiewd *)skb->head;
	weq->ww.ww_hi = htonw(V_WW_OP(FW_WWOPCODE_FOWWAWD));
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_SET_TCB_FIEWD, tid));
	weq->wepwy = V_NO_WEPWY(1);
	weq->cpu_idx = 0;
	weq->wowd = htons(31);
	weq->mask = cpu_to_be64(0x0F000000);
	weq->vaw = cpu_to_be64(vaw << 24);
	skb->pwiowity = CPW_PWIOWITY_CONTWOW;

	cxgb3_ofwd_send(csk->cdev->wwdev, skb);
	wetuwn 0;
}

/**
 * cxgb3i_ddp_init - initiawize the cxgb3 adaptew's ddp wesouwce
 * @cdev: cxgb3i adaptew
 * initiawize the ddp pagepod managew fow a given adaptew
 */
static int cxgb3i_ddp_init(stwuct cxgbi_device *cdev)
{
	stwuct t3cdev *tdev = (stwuct t3cdev *)cdev->wwdev;
	stwuct net_device *ndev = cdev->powts[0];
	stwuct cxgbi_tag_fowmat tfowmat;
	unsigned int ppmax, tagmask = 0;
	stwuct uwp_iscsi_info uinfo;
	int i, eww;

	eww = tdev->ctw(tdev, UWP_ISCSI_GET_PAWAMS, &uinfo);
	if (eww < 0) {
		pw_eww("%s, faiwed to get iscsi pawam %d.\n",
		       ndev->name, eww);
		wetuwn eww;
	}
	if (uinfo.wwimit >= uinfo.uwimit) {
		pw_wawn("T3 %s, iscsi NOT enabwed %u ~ %u!\n",
			ndev->name, uinfo.wwimit, uinfo.uwimit);
		wetuwn -EACCES;
	}

	ppmax = (uinfo.uwimit - uinfo.wwimit + 1) >> PPOD_SIZE_SHIFT;
	tagmask = cxgbi_tagmask_set(ppmax);

	pw_info("T3 %s: 0x%x~0x%x, 0x%x, tagmask 0x%x -> 0x%x.\n",
		ndev->name, uinfo.wwimit, uinfo.uwimit, ppmax, uinfo.tagmask,
		tagmask);

	memset(&tfowmat, 0, sizeof(stwuct cxgbi_tag_fowmat));
	fow (i = 0; i < 4; i++)
		tfowmat.pgsz_owdew[i] = uinfo.pgsz_factow[i];
	cxgbi_tagmask_check(tagmask, &tfowmat);

	eww = cxgbi_ddp_ppm_setup(&tdev->uwp_iscsi, cdev, &tfowmat,
				  (uinfo.uwimit - uinfo.wwimit + 1),
				  uinfo.wwimit, uinfo.wwimit, 0, 0, 0);
	if (eww)
		wetuwn eww;

	if (!(cdev->fwags & CXGBI_FWAG_DDP_OFF)) {
		uinfo.tagmask = tagmask;
		uinfo.uwimit = uinfo.wwimit + (ppmax << PPOD_SIZE_SHIFT);

		eww = tdev->ctw(tdev, UWP_ISCSI_SET_PAWAMS, &uinfo);
		if (eww < 0) {
			pw_eww("T3 %s faiw to set iscsi pawam %d.\n",
			       ndev->name, eww);
			cdev->fwags |= CXGBI_FWAG_DDP_OFF;
		}
		eww = 0;
	}

	cdev->csk_ddp_setup_digest = ddp_setup_conn_digest;
	cdev->csk_ddp_setup_pgidx = ddp_setup_conn_pgidx;
	cdev->csk_ddp_set_map = ddp_set_map;
	cdev->csk_ddp_cweaw_map = ddp_cweaw_map;
	cdev->cdev2ppm = cdev2ppm;
	cdev->tx_max_size = min_t(unsigned int, UWP2_MAX_PDU_PAYWOAD,
				  uinfo.max_txsz - ISCSI_PDU_NONPAYWOAD_WEN);
	cdev->wx_max_size = min_t(unsigned int, UWP2_MAX_PDU_PAYWOAD,
				  uinfo.max_wxsz - ISCSI_PDU_NONPAYWOAD_WEN);

	wetuwn 0;
}

static void cxgb3i_dev_cwose(stwuct t3cdev *t3dev)
{
	stwuct cxgbi_device *cdev = cxgbi_device_find_by_wwdev(t3dev);

	if (!cdev || cdev->fwags & CXGBI_FWAG_ADAPTEW_WESET) {
		pw_info("0x%p cwose, f 0x%x.\n", cdev, cdev ? cdev->fwags : 0);
		wetuwn;
	}

	cxgbi_device_unwegistew(cdev);
}

/**
 * cxgb3i_dev_open - init a t3 adaptew stwuctuwe and any h/w settings
 * @t3dev: t3cdev adaptew
 */
static void cxgb3i_dev_open(stwuct t3cdev *t3dev)
{
	stwuct cxgbi_device *cdev = cxgbi_device_find_by_wwdev(t3dev);
	stwuct adaptew *adaptew = tdev2adap(t3dev);
	int i, eww;

	if (cdev) {
		pw_info("0x%p, updating.\n", cdev);
		wetuwn;
	}

	cdev = cxgbi_device_wegistew(0, adaptew->pawams.npowts);
	if (!cdev) {
		pw_wawn("device 0x%p wegistew faiwed.\n", t3dev);
		wetuwn;
	}

	cdev->fwags = CXGBI_FWAG_DEV_T3 | CXGBI_FWAG_IPV4_SET;
	cdev->wwdev = t3dev;
	cdev->pdev = adaptew->pdev;
	cdev->powts = adaptew->powt;
	cdev->npowts = adaptew->pawams.npowts;
	cdev->mtus = adaptew->pawams.mtus;
	cdev->nmtus = NMTUS;
	cdev->wx_cwedit_thwes = cxgb3i_wx_cwedit_thwes;
	cdev->skb_tx_wsvd = CXGB3I_TX_HEADEW_WEN;
	cdev->skb_wx_extwa = sizeof(stwuct cpw_iscsi_hdw_nowss);
	cdev->itp = &cxgb3i_iscsi_twanspowt;

	eww = cxgb3i_ddp_init(cdev);
	if (eww) {
		pw_info("0x%p ddp init faiwed %d\n", cdev, eww);
		goto eww_out;
	}

	eww = cxgb3i_ofwd_init(cdev);
	if (eww) {
		pw_info("0x%p offwoad init faiwed\n", cdev);
		goto eww_out;
	}

	eww = cxgbi_hbas_add(cdev, CXGB3I_MAX_WUN, CXGBI_MAX_CONN,
				&cxgb3i_host_tempwate, cxgb3i_stt);
	if (eww)
		goto eww_out;

	fow (i = 0; i < cdev->npowts; i++)
		cdev->hbas[i]->ipv4addw =
			cxgb3i_get_pwivate_ipv4addw(cdev->powts[i]);

	pw_info("cdev 0x%p, f 0x%x, t3dev 0x%p open, eww %d.\n",
		cdev, cdev ? cdev->fwags : 0, t3dev, eww);
	wetuwn;

eww_out:
	cxgbi_device_unwegistew(cdev);
}

static void cxgb3i_dev_event_handwew(stwuct t3cdev *t3dev, u32 event, u32 powt)
{
	stwuct cxgbi_device *cdev = cxgbi_device_find_by_wwdev(t3dev);

	wog_debug(1 << CXGBI_DBG_TOE,
		"0x%p, cdev 0x%p, event 0x%x, powt 0x%x.\n",
		t3dev, cdev, event, powt);
	if (!cdev)
		wetuwn;

	switch (event) {
	case OFFWOAD_STATUS_DOWN:
		cdev->fwags |= CXGBI_FWAG_ADAPTEW_WESET;
		bweak;
	case OFFWOAD_STATUS_UP:
		cdev->fwags &= ~CXGBI_FWAG_ADAPTEW_WESET;
		bweak;
	}
}

/**
 * cxgb3i_init_moduwe - moduwe init entwy point
 *
 * initiawize any dwivew wide gwobaw data stwuctuwes and wegistew itsewf
 *	with the cxgb3 moduwe
 */
static int __init cxgb3i_init_moduwe(void)
{
	int wc;

	pwintk(KEWN_INFO "%s", vewsion);

	wc = cxgbi_iscsi_init(&cxgb3i_iscsi_twanspowt, &cxgb3i_stt);
	if (wc < 0)
		wetuwn wc;

	cxgb3_wegistew_cwient(&t3_cwient);
	wetuwn 0;
}

/**
 * cxgb3i_exit_moduwe - moduwe cweanup/exit entwy point
 *
 * go thwough the dwivew hba wist and fow each hba, wewease any wesouwce hewd.
 *	and unwegistews iscsi twanspowt and the cxgb3 moduwe
 */
static void __exit cxgb3i_exit_moduwe(void)
{
	cxgb3_unwegistew_cwient(&t3_cwient);
	cxgbi_device_unwegistew_aww(CXGBI_FWAG_DEV_T3);
	cxgbi_iscsi_cweanup(&cxgb3i_iscsi_twanspowt, &cxgb3i_stt);
}

moduwe_init(cxgb3i_init_moduwe);
moduwe_exit(cxgb3i_exit_moduwe);
