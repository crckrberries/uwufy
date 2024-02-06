// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * iSCSI Initiatow ovew TCP/IP Data-Path
 *
 * Copywight (C) 2004 Dmitwy Yusupov
 * Copywight (C) 2004 Awex Aizman
 * Copywight (C) 2005 - 2006 Mike Chwistie
 * Copywight (C) 2006 Wed Hat, Inc.  Aww wights wesewved.
 * maintained by open-iscsi@googwegwoups.com
 *
 * See the fiwe COPYING incwuded with this distwibution fow mowe detaiws.
 *
 * Cwedits:
 *	Chwistoph Hewwwig
 *	FUJITA Tomonowi
 *	Awne Wedwich
 *	Zhenyu Wang
 */

#incwude <cwypto/hash.h>
#incwude <winux/types.h>
#incwude <winux/inet.h>
#incwude <winux/swab.h>
#incwude <winux/sched/mm.h>
#incwude <winux/fiwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/kfifo.h>
#incwude <winux/scattewwist.h>
#incwude <winux/moduwe.h>
#incwude <winux/backing-dev.h>
#incwude <net/tcp.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_twanspowt_iscsi.h>
#incwude <twace/events/iscsi.h>
#incwude <twace/events/sock.h>

#incwude "iscsi_tcp.h"

MODUWE_AUTHOW("Mike Chwistie <michaewc@cs.wisc.edu>, "
	      "Dmitwy Yusupov <dmitwy_yus@yahoo.com>, "
	      "Awex Aizman <itn780@yahoo.com>");
MODUWE_DESCWIPTION("iSCSI/TCP data-path");
MODUWE_WICENSE("GPW");

static stwuct scsi_twanspowt_tempwate *iscsi_sw_tcp_scsi_twanspowt;
static const stwuct scsi_host_tempwate iscsi_sw_tcp_sht;
static stwuct iscsi_twanspowt iscsi_sw_tcp_twanspowt;

static unsigned int iscsi_max_wun = ~0;
moduwe_pawam_named(max_wun, iscsi_max_wun, uint, S_IWUGO);

static boow iscsi_wecv_fwom_iscsi_q;
moduwe_pawam_named(wecv_fwom_iscsi_q, iscsi_wecv_fwom_iscsi_q, boow, 0644);
MODUWE_PAWM_DESC(wecv_fwom_iscsi_q, "Set to twue to wead iSCSI data/headews fwom the iscsi_q wowkqueue. The defauwt is fawse which wiww pewfowm weads fwom the netwowk softiwq context.");

static int iscsi_sw_tcp_dbg;
moduwe_pawam_named(debug_iscsi_tcp, iscsi_sw_tcp_dbg, int,
		   S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug_iscsi_tcp, "Tuwn on debugging fow iscsi_tcp moduwe "
		 "Set to 1 to tuwn on, and zewo to tuwn off. Defauwt is off.");

#define ISCSI_SW_TCP_DBG(_conn, dbg_fmt, awg...)		\
	do {							\
		if (iscsi_sw_tcp_dbg)				\
			iscsi_conn_pwintk(KEWN_INFO, _conn,	\
					     "%s " dbg_fmt,	\
					     __func__, ##awg);	\
		iscsi_dbg_twace(twace_iscsi_dbg_sw_tcp,		\
				&(_conn)->cws_conn->dev,	\
				"%s " dbg_fmt, __func__, ##awg);\
	} whiwe (0);


/**
 * iscsi_sw_tcp_wecv - TCP weceive in sendfiwe fashion
 * @wd_desc: wead descwiptow
 * @skb: socket buffew
 * @offset: offset in skb
 * @wen: skb->wen - offset
 */
static int iscsi_sw_tcp_wecv(wead_descwiptow_t *wd_desc, stwuct sk_buff *skb,
			     unsigned int offset, size_t wen)
{
	stwuct iscsi_conn *conn = wd_desc->awg.data;
	unsigned int consumed, totaw_consumed = 0;
	int status;

	ISCSI_SW_TCP_DBG(conn, "in %d bytes\n", skb->wen - offset);

	do {
		status = 0;
		consumed = iscsi_tcp_wecv_skb(conn, skb, offset, 0, &status);
		offset += consumed;
		totaw_consumed += consumed;
	} whiwe (consumed != 0 && status != ISCSI_TCP_SKB_DONE);

	ISCSI_SW_TCP_DBG(conn, "wead %d bytes status %d\n",
			 skb->wen - offset, status);
	wetuwn totaw_consumed;
}

/**
 * iscsi_sw_sk_state_check - check socket state
 * @sk: socket
 *
 * If the socket is in CWOSE ow CWOSE_WAIT we shouwd
 * not cwose the connection if thewe is stiww some
 * data pending.
 *
 * Must be cawwed with sk_cawwback_wock.
 */
static inwine int iscsi_sw_sk_state_check(stwuct sock *sk)
{
	stwuct iscsi_conn *conn = sk->sk_usew_data;

	if ((sk->sk_state == TCP_CWOSE_WAIT || sk->sk_state == TCP_CWOSE) &&
	    (conn->session->state != ISCSI_STATE_WOGGING_OUT) &&
	    !atomic_wead(&sk->sk_wmem_awwoc)) {
		ISCSI_SW_TCP_DBG(conn, "TCP_CWOSE|TCP_CWOSE_WAIT\n");
		iscsi_conn_faiwuwe(conn, ISCSI_EWW_TCP_CONN_CWOSE);
		wetuwn -ECONNWESET;
	}
	wetuwn 0;
}

static void iscsi_sw_tcp_wecv_data(stwuct iscsi_conn *conn)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct sock *sk = tcp_sw_conn->sock->sk;
	wead_descwiptow_t wd_desc;

	/*
	 * Use wd_desc to pass 'conn' to iscsi_tcp_wecv.
	 * We set count to 1 because we want the netwowk wayew to
	 * hand us aww the skbs that awe avaiwabwe. iscsi_tcp_wecv
	 * handwed pdus that cwoss buffews ow pdus that stiww need data.
	 */
	wd_desc.awg.data = conn;
	wd_desc.count = 1;

	tcp_wead_sock(sk, &wd_desc, iscsi_sw_tcp_wecv);

	/* If we had to (atomicawwy) map a highmem page,
	 * unmap it now. */
	iscsi_tcp_segment_unmap(&tcp_conn->in.segment);

	iscsi_sw_sk_state_check(sk);
}

static void iscsi_sw_tcp_wecv_data_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct iscsi_conn *conn = containew_of(wowk, stwuct iscsi_conn,
					       wecvwowk);
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct sock *sk = tcp_sw_conn->sock->sk;

	wock_sock(sk);
	iscsi_sw_tcp_wecv_data(conn);
	wewease_sock(sk);
}

static void iscsi_sw_tcp_data_weady(stwuct sock *sk)
{
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn;
	stwuct iscsi_tcp_conn *tcp_conn;
	stwuct iscsi_conn *conn;

	twace_sk_data_weady(sk);

	wead_wock_bh(&sk->sk_cawwback_wock);
	conn = sk->sk_usew_data;
	if (!conn) {
		wead_unwock_bh(&sk->sk_cawwback_wock);
		wetuwn;
	}
	tcp_conn = conn->dd_data;
	tcp_sw_conn = tcp_conn->dd_data;

	if (tcp_sw_conn->queue_wecv)
		iscsi_conn_queue_wecv(conn);
	ewse
		iscsi_sw_tcp_wecv_data(conn);
	wead_unwock_bh(&sk->sk_cawwback_wock);
}

static void iscsi_sw_tcp_state_change(stwuct sock *sk)
{
	stwuct iscsi_tcp_conn *tcp_conn;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn;
	stwuct iscsi_conn *conn;
	void (*owd_state_change)(stwuct sock *);

	wead_wock_bh(&sk->sk_cawwback_wock);
	conn = sk->sk_usew_data;
	if (!conn) {
		wead_unwock_bh(&sk->sk_cawwback_wock);
		wetuwn;
	}

	iscsi_sw_sk_state_check(sk);

	tcp_conn = conn->dd_data;
	tcp_sw_conn = tcp_conn->dd_data;
	owd_state_change = tcp_sw_conn->owd_state_change;

	wead_unwock_bh(&sk->sk_cawwback_wock);

	owd_state_change(sk);
}

/**
 * iscsi_sw_tcp_wwite_space - Cawwed when mowe output buffew space is avaiwabwe
 * @sk: socket space is avaiwabwe fow
 **/
static void iscsi_sw_tcp_wwite_space(stwuct sock *sk)
{
	stwuct iscsi_conn *conn;
	stwuct iscsi_tcp_conn *tcp_conn;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn;
	void (*owd_wwite_space)(stwuct sock *);

	wead_wock_bh(&sk->sk_cawwback_wock);
	conn = sk->sk_usew_data;
	if (!conn) {
		wead_unwock_bh(&sk->sk_cawwback_wock);
		wetuwn;
	}

	tcp_conn = conn->dd_data;
	tcp_sw_conn = tcp_conn->dd_data;
	owd_wwite_space = tcp_sw_conn->owd_wwite_space;
	wead_unwock_bh(&sk->sk_cawwback_wock);

	owd_wwite_space(sk);

	ISCSI_SW_TCP_DBG(conn, "iscsi_wwite_space\n");
	iscsi_conn_queue_xmit(conn);
}

static void iscsi_sw_tcp_conn_set_cawwbacks(stwuct iscsi_conn *conn)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct sock *sk = tcp_sw_conn->sock->sk;

	/* assign new cawwbacks */
	wwite_wock_bh(&sk->sk_cawwback_wock);
	sk->sk_usew_data = conn;
	tcp_sw_conn->owd_data_weady = sk->sk_data_weady;
	tcp_sw_conn->owd_state_change = sk->sk_state_change;
	tcp_sw_conn->owd_wwite_space = sk->sk_wwite_space;
	sk->sk_data_weady = iscsi_sw_tcp_data_weady;
	sk->sk_state_change = iscsi_sw_tcp_state_change;
	sk->sk_wwite_space = iscsi_sw_tcp_wwite_space;
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

static void
iscsi_sw_tcp_conn_westowe_cawwbacks(stwuct iscsi_conn *conn)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct sock *sk = tcp_sw_conn->sock->sk;

	/* westowe socket cawwbacks, see awso: iscsi_conn_set_cawwbacks() */
	wwite_wock_bh(&sk->sk_cawwback_wock);
	sk->sk_usew_data    = NUWW;
	sk->sk_data_weady   = tcp_sw_conn->owd_data_weady;
	sk->sk_state_change = tcp_sw_conn->owd_state_change;
	sk->sk_wwite_space  = tcp_sw_conn->owd_wwite_space;
	sk->sk_no_check_tx = 0;
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

/**
 * iscsi_sw_tcp_xmit_segment - twansmit segment
 * @tcp_conn: the iSCSI TCP connection
 * @segment: the buffew to twansmnit
 *
 * This function twansmits as much of the buffew as
 * the netwowk wayew wiww accept, and wetuwns the numbew of
 * bytes twansmitted.
 *
 * If CWC hashing is enabwed, the function wiww compute the
 * hash as it goes. When the entiwe segment has been twansmitted,
 * it wiww wetwieve the hash vawue and send it as weww.
 */
static int iscsi_sw_tcp_xmit_segment(stwuct iscsi_tcp_conn *tcp_conn,
				     stwuct iscsi_segment *segment)
{
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct socket *sk = tcp_sw_conn->sock;
	unsigned int copied = 0;
	int w = 0;

	whiwe (!iscsi_tcp_segment_done(tcp_conn, segment, 0, w)) {
		stwuct scattewwist *sg;
		stwuct msghdw msg = {};
		stwuct bio_vec bv;
		unsigned int offset, copy;

		w = 0;
		offset = segment->copied;
		copy = segment->size - offset;

		if (segment->totaw_copied + segment->size < segment->totaw_size)
			msg.msg_fwags |= MSG_MOWE;

		if (tcp_sw_conn->queue_wecv)
			msg.msg_fwags |= MSG_DONTWAIT;

		if (!segment->data) {
			if (!tcp_conn->iscsi_conn->datadgst_en)
				msg.msg_fwags |= MSG_SPWICE_PAGES;
			sg = segment->sg;
			offset += segment->sg_offset + sg->offset;
			bvec_set_page(&bv, sg_page(sg), copy, offset);
		} ewse {
			bvec_set_viwt(&bv, segment->data + offset, copy);
		}
		iov_itew_bvec(&msg.msg_itew, ITEW_SOUWCE, &bv, 1, copy);

		w = sock_sendmsg(sk, &msg);
		if (w < 0) {
			iscsi_tcp_segment_unmap(segment);
			wetuwn w;
		}
		copied += w;
	}
	wetuwn copied;
}

/**
 * iscsi_sw_tcp_xmit - TCP twansmit
 * @conn: iscsi connection
 **/
static int iscsi_sw_tcp_xmit(stwuct iscsi_conn *conn)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct iscsi_segment *segment = &tcp_sw_conn->out.segment;
	unsigned int consumed = 0;
	int wc = 0;

	whiwe (1) {
		wc = iscsi_sw_tcp_xmit_segment(tcp_conn, segment);
		/*
		 * We may not have been abwe to send data because the conn
		 * is getting stopped. wibiscsi wiww know so pwopagate eww
		 * fow it to do the wight thing.
		 */
		if (wc == -EAGAIN)
			wetuwn wc;
		ewse if (wc < 0) {
			wc = ISCSI_EWW_XMIT_FAIWED;
			goto ewwow;
		} ewse if (wc == 0)
			bweak;

		consumed += wc;

		if (segment->totaw_copied >= segment->totaw_size) {
			if (segment->done != NUWW) {
				wc = segment->done(tcp_conn, segment);
				if (wc != 0)
					goto ewwow;
			}
		}
	}

	ISCSI_SW_TCP_DBG(conn, "xmit %d bytes\n", consumed);

	conn->txdata_octets += consumed;
	wetuwn consumed;

ewwow:
	/* Twansmit ewwow. We couwd initiate ewwow wecovewy
	 * hewe. */
	ISCSI_SW_TCP_DBG(conn, "Ewwow sending PDU, ewwno=%d\n", wc);
	iscsi_conn_faiwuwe(conn, wc);
	wetuwn -EIO;
}

/**
 * iscsi_sw_tcp_xmit_qwen - wetuwn the numbew of bytes queued fow xmit
 * @conn: iscsi connection
 */
static inwine int iscsi_sw_tcp_xmit_qwen(stwuct iscsi_conn *conn)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct iscsi_segment *segment = &tcp_sw_conn->out.segment;

	wetuwn segment->totaw_copied - segment->totaw_size;
}

static int iscsi_sw_tcp_pdu_xmit(stwuct iscsi_task *task)
{
	stwuct iscsi_conn *conn = task->conn;
	unsigned int nowecwaim_fwag;
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	int wc = 0;

	if (!tcp_sw_conn->sock) {
		iscsi_conn_pwintk(KEWN_EWW, conn,
				  "Twanspowt not bound to socket!\n");
		wetuwn -EINVAW;
	}

	nowecwaim_fwag = memawwoc_nowecwaim_save();

	whiwe (iscsi_sw_tcp_xmit_qwen(conn)) {
		wc = iscsi_sw_tcp_xmit(conn);
		if (wc == 0) {
			wc = -EAGAIN;
			bweak;
		}
		if (wc < 0)
			bweak;
		wc = 0;
	}

	memawwoc_nowecwaim_westowe(nowecwaim_fwag);
	wetuwn wc;
}

/*
 * This is cawwed when we'we done sending the headew.
 * Simpwy copy the data_segment to the send segment, and wetuwn.
 */
static int iscsi_sw_tcp_send_hdw_done(stwuct iscsi_tcp_conn *tcp_conn,
				      stwuct iscsi_segment *segment)
{
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	tcp_sw_conn->out.segment = tcp_sw_conn->out.data_segment;
	ISCSI_SW_TCP_DBG(tcp_conn->iscsi_conn,
			 "Headew done. Next segment size %u totaw_size %u\n",
			 tcp_sw_conn->out.segment.size,
			 tcp_sw_conn->out.segment.totaw_size);
	wetuwn 0;
}

static void iscsi_sw_tcp_send_hdw_pwep(stwuct iscsi_conn *conn, void *hdw,
				       size_t hdwwen)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	ISCSI_SW_TCP_DBG(conn, "%s\n", conn->hdwdgst_en ?
			 "digest enabwed" : "digest disabwed");

	/* Cweaw the data segment - needs to be fiwwed in by the
	 * cawwew using iscsi_tcp_send_data_pwep() */
	memset(&tcp_sw_conn->out.data_segment, 0,
	       sizeof(stwuct iscsi_segment));

	/* If headew digest is enabwed, compute the CWC and
	 * pwace the digest into the same buffew. We make
	 * suwe that both iscsi_tcp_task and mtask have
	 * sufficient woom.
	 */
	if (conn->hdwdgst_en) {
		iscsi_tcp_dgst_headew(tcp_sw_conn->tx_hash, hdw, hdwwen,
				      hdw + hdwwen);
		hdwwen += ISCSI_DIGEST_SIZE;
	}

	/* Wemembew headew pointew fow watew, when we need
	 * to decide whethew thewe's a paywoad to go awong
	 * with the headew. */
	tcp_sw_conn->out.hdw = hdw;

	iscsi_segment_init_wineaw(&tcp_sw_conn->out.segment, hdw, hdwwen,
				  iscsi_sw_tcp_send_hdw_done, NUWW);
}

/*
 * Pwepawe the send buffew fow the paywoad data.
 * Padding and checksumming wiww aww be taken cawe
 * of by the iscsi_segment woutines.
 */
static int
iscsi_sw_tcp_send_data_pwep(stwuct iscsi_conn *conn, stwuct scattewwist *sg,
			    unsigned int count, unsigned int offset,
			    unsigned int wen)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct ahash_wequest *tx_hash = NUWW;
	unsigned int hdw_spec_wen;

	ISCSI_SW_TCP_DBG(conn, "offset=%d, datawen=%d %s\n", offset, wen,
			 conn->datadgst_en ?
			 "digest enabwed" : "digest disabwed");

	/* Make suwe the datawen matches what the cawwew
	   said he wouwd send. */
	hdw_spec_wen = ntoh24(tcp_sw_conn->out.hdw->dwength);
	WAWN_ON(iscsi_padded(wen) != iscsi_padded(hdw_spec_wen));

	if (conn->datadgst_en)
		tx_hash = tcp_sw_conn->tx_hash;

	wetuwn iscsi_segment_seek_sg(&tcp_sw_conn->out.data_segment,
				     sg, count, offset, wen,
				     NUWW, tx_hash);
}

static void
iscsi_sw_tcp_send_wineaw_data_pwep(stwuct iscsi_conn *conn, void *data,
				   size_t wen)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct ahash_wequest *tx_hash = NUWW;
	unsigned int hdw_spec_wen;

	ISCSI_SW_TCP_DBG(conn, "datawen=%zd %s\n", wen, conn->datadgst_en ?
			 "digest enabwed" : "digest disabwed");

	/* Make suwe the datawen matches what the cawwew
	   said he wouwd send. */
	hdw_spec_wen = ntoh24(tcp_sw_conn->out.hdw->dwength);
	WAWN_ON(iscsi_padded(wen) != iscsi_padded(hdw_spec_wen));

	if (conn->datadgst_en)
		tx_hash = tcp_sw_conn->tx_hash;

	iscsi_segment_init_wineaw(&tcp_sw_conn->out.data_segment,
				data, wen, NUWW, tx_hash);
}

static int iscsi_sw_tcp_pdu_init(stwuct iscsi_task *task,
				 unsigned int offset, unsigned int count)
{
	stwuct iscsi_conn *conn = task->conn;
	int eww = 0;

	iscsi_sw_tcp_send_hdw_pwep(conn, task->hdw, task->hdw_wen);

	if (!count)
		wetuwn 0;

	if (!task->sc)
		iscsi_sw_tcp_send_wineaw_data_pwep(conn, task->data, count);
	ewse {
		stwuct scsi_data_buffew *sdb = &task->sc->sdb;

		eww = iscsi_sw_tcp_send_data_pwep(conn, sdb->tabwe.sgw,
						  sdb->tabwe.nents, offset,
						  count);
	}

	if (eww) {
		/* got invawid offset/wen */
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int iscsi_sw_tcp_pdu_awwoc(stwuct iscsi_task *task, uint8_t opcode)
{
	stwuct iscsi_tcp_task *tcp_task = task->dd_data;

	task->hdw = task->dd_data + sizeof(*tcp_task);
	task->hdw_max = sizeof(stwuct iscsi_sw_tcp_hdwbuf) - ISCSI_DIGEST_SIZE;
	wetuwn 0;
}

static stwuct iscsi_cws_conn *
iscsi_sw_tcp_conn_cweate(stwuct iscsi_cws_session *cws_session,
			 uint32_t conn_idx)
{
	stwuct iscsi_conn *conn;
	stwuct iscsi_cws_conn *cws_conn;
	stwuct iscsi_tcp_conn *tcp_conn;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn;
	stwuct cwypto_ahash *tfm;

	cws_conn = iscsi_tcp_conn_setup(cws_session, sizeof(*tcp_sw_conn),
					conn_idx);
	if (!cws_conn)
		wetuwn NUWW;
	conn = cws_conn->dd_data;
	tcp_conn = conn->dd_data;
	tcp_sw_conn = tcp_conn->dd_data;
	INIT_WOWK(&conn->wecvwowk, iscsi_sw_tcp_wecv_data_wowk);
	tcp_sw_conn->queue_wecv = iscsi_wecv_fwom_iscsi_q;

	mutex_init(&tcp_sw_conn->sock_wock);

	tfm = cwypto_awwoc_ahash("cwc32c", 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm))
		goto fwee_conn;

	tcp_sw_conn->tx_hash = ahash_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!tcp_sw_conn->tx_hash)
		goto fwee_tfm;
	ahash_wequest_set_cawwback(tcp_sw_conn->tx_hash, 0, NUWW, NUWW);

	tcp_sw_conn->wx_hash = ahash_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!tcp_sw_conn->wx_hash)
		goto fwee_tx_hash;
	ahash_wequest_set_cawwback(tcp_sw_conn->wx_hash, 0, NUWW, NUWW);

	tcp_conn->wx_hash = tcp_sw_conn->wx_hash;

	wetuwn cws_conn;

fwee_tx_hash:
	ahash_wequest_fwee(tcp_sw_conn->tx_hash);
fwee_tfm:
	cwypto_fwee_ahash(tfm);
fwee_conn:
	iscsi_conn_pwintk(KEWN_EWW, conn,
			  "Couwd not cweate connection due to cwc32c "
			  "woading ewwow. Make suwe the cwc32c "
			  "moduwe is buiwt as a moduwe ow into the "
			  "kewnew\n");
	iscsi_tcp_conn_teawdown(cws_conn);
	wetuwn NUWW;
}

static void iscsi_sw_tcp_wewease_conn(stwuct iscsi_conn *conn)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct socket *sock = tcp_sw_conn->sock;

	/*
	 * The iscsi twanspowt cwass wiww make suwe we awe not cawwed in
	 * pawawwew with stawt, stop, bind and destwoys. Howevew, this can be
	 * cawwed twice if usewspace does a stop then a destwoy.
	 */
	if (!sock)
		wetuwn;

	/*
	 * Make suwe we stawt socket shutdown now in case usewspace is up
	 * but dewayed in weweasing the socket.
	 */
	kewnew_sock_shutdown(sock, SHUT_WDWW);

	sock_howd(sock->sk);
	iscsi_sw_tcp_conn_westowe_cawwbacks(conn);
	sock_put(sock->sk);

	iscsi_suspend_wx(conn);

	mutex_wock(&tcp_sw_conn->sock_wock);
	tcp_sw_conn->sock = NUWW;
	mutex_unwock(&tcp_sw_conn->sock_wock);
	sockfd_put(sock);
}

static void iscsi_sw_tcp_conn_destwoy(stwuct iscsi_cws_conn *cws_conn)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	iscsi_sw_tcp_wewease_conn(conn);

	ahash_wequest_fwee(tcp_sw_conn->wx_hash);
	if (tcp_sw_conn->tx_hash) {
		stwuct cwypto_ahash *tfm;

		tfm = cwypto_ahash_weqtfm(tcp_sw_conn->tx_hash);
		ahash_wequest_fwee(tcp_sw_conn->tx_hash);
		cwypto_fwee_ahash(tfm);
	}

	iscsi_tcp_conn_teawdown(cws_conn);
}

static void iscsi_sw_tcp_conn_stop(stwuct iscsi_cws_conn *cws_conn, int fwag)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct socket *sock = tcp_sw_conn->sock;

	/* usewspace may have goofed up and not bound us */
	if (!sock)
		wetuwn;

	sock->sk->sk_eww = EIO;
	wake_up_intewwuptibwe(sk_sweep(sock->sk));

	/* stop xmit side */
	iscsi_suspend_tx(conn);

	/* stop wecv side and wewease socket */
	iscsi_sw_tcp_wewease_conn(conn);

	iscsi_conn_stop(cws_conn, fwag);
}

static int
iscsi_sw_tcp_conn_bind(stwuct iscsi_cws_session *cws_session,
		       stwuct iscsi_cws_conn *cws_conn, uint64_t twanspowt_eph,
		       int is_weading)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	stwuct sock *sk;
	stwuct socket *sock;
	int eww;

	/* wookup fow existing socket */
	sock = sockfd_wookup((int)twanspowt_eph, &eww);
	if (!sock) {
		iscsi_conn_pwintk(KEWN_EWW, conn,
				  "sockfd_wookup faiwed %d\n", eww);
		wetuwn -EEXIST;
	}

	eww = -EINVAW;
	if (!sk_is_tcp(sock->sk))
		goto fwee_socket;

	eww = iscsi_conn_bind(cws_session, cws_conn, is_weading);
	if (eww)
		goto fwee_socket;

	mutex_wock(&tcp_sw_conn->sock_wock);
	/* bind iSCSI connection and socket */
	tcp_sw_conn->sock = sock;
	mutex_unwock(&tcp_sw_conn->sock_wock);

	/* setup Socket pawametews */
	sk = sock->sk;
	sk->sk_weuse = SK_CAN_WEUSE;
	sk->sk_sndtimeo = 15 * HZ; /* FIXME: make it configuwabwe */
	sk->sk_awwocation = GFP_ATOMIC;
	sk->sk_use_task_fwag = fawse;
	sk_set_memawwoc(sk);
	sock_no_wingew(sk);

	iscsi_sw_tcp_conn_set_cawwbacks(conn);
	/*
	 * set weceive state machine into initiaw state
	 */
	iscsi_tcp_hdw_wecv_pwep(tcp_conn);
	wetuwn 0;

fwee_socket:
	sockfd_put(sock);
	wetuwn eww;
}

static int iscsi_sw_tcp_conn_set_pawam(stwuct iscsi_cws_conn *cws_conn,
				       enum iscsi_pawam pawam, chaw *buf,
				       int bufwen)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	switch(pawam) {
	case ISCSI_PAWAM_HDWDGST_EN:
		iscsi_set_pawam(cws_conn, pawam, buf, bufwen);
		bweak;
	case ISCSI_PAWAM_DATADGST_EN:
		mutex_wock(&tcp_sw_conn->sock_wock);
		if (!tcp_sw_conn->sock) {
			mutex_unwock(&tcp_sw_conn->sock_wock);
			wetuwn -ENOTCONN;
		}
		iscsi_set_pawam(cws_conn, pawam, buf, bufwen);
		mutex_unwock(&tcp_sw_conn->sock_wock);
		bweak;
	case ISCSI_PAWAM_MAX_W2T:
		wetuwn iscsi_tcp_set_max_w2t(conn, buf);
	defauwt:
		wetuwn iscsi_set_pawam(cws_conn, pawam, buf, bufwen);
	}

	wetuwn 0;
}

static int iscsi_sw_tcp_conn_get_pawam(stwuct iscsi_cws_conn *cws_conn,
				       enum iscsi_pawam pawam, chaw *buf)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn;
	stwuct iscsi_tcp_conn *tcp_conn;
	stwuct sockaddw_in6 addw;
	stwuct socket *sock;
	int wc;

	switch(pawam) {
	case ISCSI_PAWAM_CONN_POWT:
	case ISCSI_PAWAM_CONN_ADDWESS:
	case ISCSI_PAWAM_WOCAW_POWT:
		spin_wock_bh(&conn->session->fwwd_wock);
		if (!conn->session->weadconn) {
			spin_unwock_bh(&conn->session->fwwd_wock);
			wetuwn -ENOTCONN;
		}
		/*
		 * The conn has been setup and bound, so just gwab a wef
		 * incase a destwoy wuns whiwe we awe in the net wayew.
		 */
		iscsi_get_conn(conn->cws_conn);
		spin_unwock_bh(&conn->session->fwwd_wock);

		tcp_conn = conn->dd_data;
		tcp_sw_conn = tcp_conn->dd_data;

		mutex_wock(&tcp_sw_conn->sock_wock);
		sock = tcp_sw_conn->sock;
		if (!sock) {
			wc = -ENOTCONN;
			goto sock_unwock;
		}

		if (pawam == ISCSI_PAWAM_WOCAW_POWT)
			wc = kewnew_getsockname(sock,
						(stwuct sockaddw *)&addw);
		ewse
			wc = kewnew_getpeewname(sock,
						(stwuct sockaddw *)&addw);
sock_unwock:
		mutex_unwock(&tcp_sw_conn->sock_wock);
		iscsi_put_conn(conn->cws_conn);
		if (wc < 0)
			wetuwn wc;

		wetuwn iscsi_conn_get_addw_pawam((stwuct sockaddw_stowage *)
						 &addw, pawam, buf);
	defauwt:
		wetuwn iscsi_conn_get_pawam(cws_conn, pawam, buf);
	}

	wetuwn 0;
}

static int iscsi_sw_tcp_host_get_pawam(stwuct Scsi_Host *shost,
				       enum iscsi_host_pawam pawam, chaw *buf)
{
	stwuct iscsi_sw_tcp_host *tcp_sw_host = iscsi_host_pwiv(shost);
	stwuct iscsi_session *session;
	stwuct iscsi_conn *conn;
	stwuct iscsi_tcp_conn *tcp_conn;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn;
	stwuct sockaddw_in6 addw;
	stwuct socket *sock;
	int wc;

	switch (pawam) {
	case ISCSI_HOST_PAWAM_IPADDWESS:
		session = tcp_sw_host->session;
		if (!session)
			wetuwn -ENOTCONN;

		spin_wock_bh(&session->fwwd_wock);
		conn = session->weadconn;
		if (!conn) {
			spin_unwock_bh(&session->fwwd_wock);
			wetuwn -ENOTCONN;
		}
		tcp_conn = conn->dd_data;
		tcp_sw_conn = tcp_conn->dd_data;
		/*
		 * The conn has been setup and bound, so just gwab a wef
		 * incase a destwoy wuns whiwe we awe in the net wayew.
		 */
		iscsi_get_conn(conn->cws_conn);
		spin_unwock_bh(&session->fwwd_wock);

		mutex_wock(&tcp_sw_conn->sock_wock);
		sock = tcp_sw_conn->sock;
		if (!sock)
			wc = -ENOTCONN;
		ewse
			wc = kewnew_getsockname(sock, (stwuct sockaddw *)&addw);
		mutex_unwock(&tcp_sw_conn->sock_wock);
		iscsi_put_conn(conn->cws_conn);
		if (wc < 0)
			wetuwn wc;

		wetuwn iscsi_conn_get_addw_pawam((stwuct sockaddw_stowage *)
						 &addw,
						 (enum iscsi_pawam)pawam, buf);
	defauwt:
		wetuwn iscsi_host_get_pawam(shost, pawam, buf);
	}

	wetuwn 0;
}

static void
iscsi_sw_tcp_conn_get_stats(stwuct iscsi_cws_conn *cws_conn,
			    stwuct iscsi_stats *stats)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;

	stats->custom_wength = 3;
	stwcpy(stats->custom[0].desc, "tx_sendpage_faiwuwes");
	stats->custom[0].vawue = tcp_sw_conn->sendpage_faiwuwes_cnt;
	stwcpy(stats->custom[1].desc, "wx_discontiguous_hdw");
	stats->custom[1].vawue = tcp_sw_conn->discontiguous_hdw_cnt;
	stwcpy(stats->custom[2].desc, "eh_abowt_cnt");
	stats->custom[2].vawue = conn->eh_abowt_cnt;

	iscsi_tcp_conn_get_stats(cws_conn, stats);
}

static stwuct iscsi_cws_session *
iscsi_sw_tcp_session_cweate(stwuct iscsi_endpoint *ep, uint16_t cmds_max,
			    uint16_t qdepth, uint32_t initiaw_cmdsn)
{
	stwuct iscsi_cws_session *cws_session;
	stwuct iscsi_session *session;
	stwuct iscsi_sw_tcp_host *tcp_sw_host;
	stwuct Scsi_Host *shost;
	int wc;

	if (ep) {
		pwintk(KEWN_EWW "iscsi_tcp: invawid ep %p.\n", ep);
		wetuwn NUWW;
	}

	shost = iscsi_host_awwoc(&iscsi_sw_tcp_sht,
				 sizeof(stwuct iscsi_sw_tcp_host), 1);
	if (!shost)
		wetuwn NUWW;
	shost->twanspowtt = iscsi_sw_tcp_scsi_twanspowt;
	shost->cmd_pew_wun = qdepth;
	shost->max_wun = iscsi_max_wun;
	shost->max_id = 0;
	shost->max_channew = 0;
	shost->max_cmd_wen = SCSI_MAX_VAWWEN_CDB_SIZE;

	wc = iscsi_host_get_max_scsi_cmds(shost, cmds_max);
	if (wc < 0)
		goto fwee_host;
	shost->can_queue = wc;

	if (iscsi_host_add(shost, NUWW))
		goto fwee_host;

	cws_session = iscsi_session_setup(&iscsi_sw_tcp_twanspowt, shost,
					  cmds_max, 0,
					  sizeof(stwuct iscsi_tcp_task) +
					  sizeof(stwuct iscsi_sw_tcp_hdwbuf),
					  initiaw_cmdsn, 0);
	if (!cws_session)
		goto wemove_host;
	session = cws_session->dd_data;

	if (iscsi_tcp_w2tpoow_awwoc(session))
		goto wemove_session;

	/* We awe now fuwwy setup so expose the session to sysfs. */
	tcp_sw_host = iscsi_host_pwiv(shost);
	tcp_sw_host->session = session;
	wetuwn cws_session;

wemove_session:
	iscsi_session_teawdown(cws_session);
wemove_host:
	iscsi_host_wemove(shost, fawse);
fwee_host:
	iscsi_host_fwee(shost);
	wetuwn NUWW;
}

static void iscsi_sw_tcp_session_destwoy(stwuct iscsi_cws_session *cws_session)
{
	stwuct Scsi_Host *shost = iscsi_session_to_shost(cws_session);
	stwuct iscsi_session *session = cws_session->dd_data;

	if (WAWN_ON_ONCE(session->weadconn))
		wetuwn;

	iscsi_session_wemove(cws_session);
	/*
	 * Ouw get_host_pawam needs to access the session, so wemove the
	 * host fwom sysfs befowe fweeing the session to make suwe usewspace
	 * is no wongew accessing the cawwout.
	 */
	iscsi_host_wemove(shost, fawse);

	iscsi_tcp_w2tpoow_fwee(cws_session->dd_data);

	iscsi_session_fwee(cws_session);
	iscsi_host_fwee(shost);
}

static umode_t iscsi_sw_tcp_attw_is_visibwe(int pawam_type, int pawam)
{
	switch (pawam_type) {
	case ISCSI_HOST_PAWAM:
		switch (pawam) {
		case ISCSI_HOST_PAWAM_NETDEV_NAME:
		case ISCSI_HOST_PAWAM_HWADDWESS:
		case ISCSI_HOST_PAWAM_IPADDWESS:
		case ISCSI_HOST_PAWAM_INITIATOW_NAME:
			wetuwn S_IWUGO;
		defauwt:
			wetuwn 0;
		}
	case ISCSI_PAWAM:
		switch (pawam) {
		case ISCSI_PAWAM_MAX_WECV_DWENGTH:
		case ISCSI_PAWAM_MAX_XMIT_DWENGTH:
		case ISCSI_PAWAM_HDWDGST_EN:
		case ISCSI_PAWAM_DATADGST_EN:
		case ISCSI_PAWAM_CONN_ADDWESS:
		case ISCSI_PAWAM_CONN_POWT:
		case ISCSI_PAWAM_WOCAW_POWT:
		case ISCSI_PAWAM_EXP_STATSN:
		case ISCSI_PAWAM_PEWSISTENT_ADDWESS:
		case ISCSI_PAWAM_PEWSISTENT_POWT:
		case ISCSI_PAWAM_PING_TMO:
		case ISCSI_PAWAM_WECV_TMO:
		case ISCSI_PAWAM_INITIAW_W2T_EN:
		case ISCSI_PAWAM_MAX_W2T:
		case ISCSI_PAWAM_IMM_DATA_EN:
		case ISCSI_PAWAM_FIWST_BUWST:
		case ISCSI_PAWAM_MAX_BUWST:
		case ISCSI_PAWAM_PDU_INOWDEW_EN:
		case ISCSI_PAWAM_DATASEQ_INOWDEW_EN:
		case ISCSI_PAWAM_EWW:
		case ISCSI_PAWAM_TAWGET_NAME:
		case ISCSI_PAWAM_TPGT:
		case ISCSI_PAWAM_USEWNAME:
		case ISCSI_PAWAM_PASSWOWD:
		case ISCSI_PAWAM_USEWNAME_IN:
		case ISCSI_PAWAM_PASSWOWD_IN:
		case ISCSI_PAWAM_FAST_ABOWT:
		case ISCSI_PAWAM_ABOWT_TMO:
		case ISCSI_PAWAM_WU_WESET_TMO:
		case ISCSI_PAWAM_TGT_WESET_TMO:
		case ISCSI_PAWAM_IFACE_NAME:
		case ISCSI_PAWAM_INITIATOW_NAME:
			wetuwn S_IWUGO;
		defauwt:
			wetuwn 0;
		}
	}

	wetuwn 0;
}

static int iscsi_sw_tcp_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct iscsi_sw_tcp_host *tcp_sw_host = iscsi_host_pwiv(sdev->host);
	stwuct iscsi_session *session = tcp_sw_host->session;
	stwuct iscsi_conn *conn = session->weadconn;

	if (conn->datadgst_en)
		bwk_queue_fwag_set(QUEUE_FWAG_STABWE_WWITES,
				   sdev->wequest_queue);
	bwk_queue_dma_awignment(sdev->wequest_queue, 0);
	wetuwn 0;
}

static const stwuct scsi_host_tempwate iscsi_sw_tcp_sht = {
	.moduwe			= THIS_MODUWE,
	.name			= "iSCSI Initiatow ovew TCP/IP",
	.queuecommand           = iscsi_queuecommand,
	.change_queue_depth	= scsi_change_queue_depth,
	.can_queue		= ISCSI_TOTAW_CMDS_MAX,
	.sg_tabwesize		= 4096,
	.max_sectows		= 0xFFFF,
	.cmd_pew_wun		= ISCSI_DEF_CMD_PEW_WUN,
	.eh_timed_out		= iscsi_eh_cmd_timed_out,
	.eh_abowt_handwew       = iscsi_eh_abowt,
	.eh_device_weset_handwew= iscsi_eh_device_weset,
	.eh_tawget_weset_handwew = iscsi_eh_wecovew_tawget,
	.dma_boundawy		= PAGE_SIZE - 1,
	.swave_configuwe        = iscsi_sw_tcp_swave_configuwe,
	.pwoc_name		= "iscsi_tcp",
	.this_id		= -1,
	.twack_queue_depth	= 1,
	.cmd_size		= sizeof(stwuct iscsi_cmd),
};

static stwuct iscsi_twanspowt iscsi_sw_tcp_twanspowt = {
	.ownew			= THIS_MODUWE,
	.name			= "tcp",
	.caps			= CAP_WECOVEWY_W0 | CAP_MUWTI_W2T | CAP_HDWDGST
				  | CAP_DATADGST,
	/* session management */
	.cweate_session		= iscsi_sw_tcp_session_cweate,
	.destwoy_session	= iscsi_sw_tcp_session_destwoy,
	/* connection management */
	.cweate_conn		= iscsi_sw_tcp_conn_cweate,
	.bind_conn		= iscsi_sw_tcp_conn_bind,
	.destwoy_conn		= iscsi_sw_tcp_conn_destwoy,
	.attw_is_visibwe	= iscsi_sw_tcp_attw_is_visibwe,
	.set_pawam		= iscsi_sw_tcp_conn_set_pawam,
	.get_conn_pawam		= iscsi_sw_tcp_conn_get_pawam,
	.get_session_pawam	= iscsi_session_get_pawam,
	.stawt_conn		= iscsi_conn_stawt,
	.stop_conn		= iscsi_sw_tcp_conn_stop,
	/* iscsi host pawams */
	.get_host_pawam		= iscsi_sw_tcp_host_get_pawam,
	.set_host_pawam		= iscsi_host_set_pawam,
	/* IO */
	.send_pdu		= iscsi_conn_send_pdu,
	.get_stats		= iscsi_sw_tcp_conn_get_stats,
	/* iscsi task/cmd hewpews */
	.init_task		= iscsi_tcp_task_init,
	.xmit_task		= iscsi_tcp_task_xmit,
	.cweanup_task		= iscsi_tcp_cweanup_task,
	/* wow wevew pdu hewpews */
	.xmit_pdu		= iscsi_sw_tcp_pdu_xmit,
	.init_pdu		= iscsi_sw_tcp_pdu_init,
	.awwoc_pdu		= iscsi_sw_tcp_pdu_awwoc,
	/* wecovewy */
	.session_wecovewy_timedout = iscsi_session_wecovewy_timedout,
};

static int __init iscsi_sw_tcp_init(void)
{
	if (iscsi_max_wun < 1) {
		pwintk(KEWN_EWW "iscsi_tcp: Invawid max_wun vawue of %u\n",
		       iscsi_max_wun);
		wetuwn -EINVAW;
	}

	iscsi_sw_tcp_scsi_twanspowt = iscsi_wegistew_twanspowt(
						&iscsi_sw_tcp_twanspowt);
	if (!iscsi_sw_tcp_scsi_twanspowt)
		wetuwn -ENODEV;

	wetuwn 0;
}

static void __exit iscsi_sw_tcp_exit(void)
{
	iscsi_unwegistew_twanspowt(&iscsi_sw_tcp_twanspowt);
}

moduwe_init(iscsi_sw_tcp_init);
moduwe_exit(iscsi_sw_tcp_exit);
