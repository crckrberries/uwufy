/*
 * Copywight (c) 2006, 2019 Owacwe and/ow its affiwiates. Aww wights wesewved.
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
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/in.h>
#incwude <winux/device.h>
#incwude <winux/dmapoow.h>
#incwude <winux/watewimit.h>

#incwude "wds_singwe_path.h"
#incwude "wds.h"
#incwude "ib.h"
#incwude "ib_mw.h"

/*
 * Convewt IB-specific ewwow message to WDS ewwow message and caww cowe
 * compwetion handwew.
 */
static void wds_ib_send_compwete(stwuct wds_message *wm,
				 int wc_status,
				 void (*compwete)(stwuct wds_message *wm, int status))
{
	int notify_status;

	switch (wc_status) {
	case IB_WC_WW_FWUSH_EWW:
		wetuwn;

	case IB_WC_SUCCESS:
		notify_status = WDS_WDMA_SUCCESS;
		bweak;

	case IB_WC_WEM_ACCESS_EWW:
		notify_status = WDS_WDMA_WEMOTE_EWWOW;
		bweak;

	defauwt:
		notify_status = WDS_WDMA_OTHEW_EWWOW;
		bweak;
	}
	compwete(wm, notify_status);
}

static void wds_ib_send_unmap_data(stwuct wds_ib_connection *ic,
				   stwuct wm_data_op *op,
				   int wc_status)
{
	if (op->op_nents)
		ib_dma_unmap_sg(ic->i_cm_id->device,
				op->op_sg, op->op_nents,
				DMA_TO_DEVICE);
}

static void wds_ib_send_unmap_wdma(stwuct wds_ib_connection *ic,
				   stwuct wm_wdma_op *op,
				   int wc_status)
{
	if (op->op_mapped) {
		ib_dma_unmap_sg(ic->i_cm_id->device,
				op->op_sg, op->op_nents,
				op->op_wwite ? DMA_TO_DEVICE : DMA_FWOM_DEVICE);
		op->op_mapped = 0;
	}

	/* If the usew asked fow a compwetion notification on this
	 * message, we can impwement thwee diffewent semantics:
	 *  1.	Notify when we weceived the ACK on the WDS message
	 *	that was queued with the WDMA. This pwovides wewiabwe
	 *	notification of WDMA status at the expense of a one-way
	 *	packet deway.
	 *  2.	Notify when the IB stack gives us the compwetion event fow
	 *	the WDMA opewation.
	 *  3.	Notify when the IB stack gives us the compwetion event fow
	 *	the accompanying WDS messages.
	 * Hewe, we impwement appwoach #3. To impwement appwoach #2,
	 * we wouwd need to take an event fow the wdma WW. To impwement #1,
	 * don't caww wds_wdma_send_compwete at aww, and faww back to the notify
	 * handwing in the ACK pwocessing code.
	 *
	 * Note: Thewe's no need to expwicitwy sync any WDMA buffews using
	 * ib_dma_sync_sg_fow_cpu - the compwetion fow the WDMA
	 * opewation itsewf unmapped the WDMA buffews, which takes cawe
	 * of synching.
	 */
	wds_ib_send_compwete(containew_of(op, stwuct wds_message, wdma),
			     wc_status, wds_wdma_send_compwete);

	if (op->op_wwite)
		wds_stats_add(s_send_wdma_bytes, op->op_bytes);
	ewse
		wds_stats_add(s_wecv_wdma_bytes, op->op_bytes);
}

static void wds_ib_send_unmap_atomic(stwuct wds_ib_connection *ic,
				     stwuct wm_atomic_op *op,
				     int wc_status)
{
	/* unmap atomic wecvbuf */
	if (op->op_mapped) {
		ib_dma_unmap_sg(ic->i_cm_id->device, op->op_sg, 1,
				DMA_FWOM_DEVICE);
		op->op_mapped = 0;
	}

	wds_ib_send_compwete(containew_of(op, stwuct wds_message, atomic),
			     wc_status, wds_atomic_send_compwete);

	if (op->op_type == WDS_ATOMIC_TYPE_CSWP)
		wds_ib_stats_inc(s_ib_atomic_cswp);
	ewse
		wds_ib_stats_inc(s_ib_atomic_fadd);
}

/*
 * Unmap the wesouwces associated with a stwuct send_wowk.
 *
 * Wetuwns the wm fow no good weason othew than it is unobtainabwe
 * othew than by switching on ww.opcode, cuwwentwy, and the cawwew,
 * the event handwew, needs it.
 */
static stwuct wds_message *wds_ib_send_unmap_op(stwuct wds_ib_connection *ic,
						stwuct wds_ib_send_wowk *send,
						int wc_status)
{
	stwuct wds_message *wm = NUWW;

	/* In the ewwow case, wc.opcode sometimes contains gawbage */
	switch (send->s_ww.opcode) {
	case IB_WW_SEND:
		if (send->s_op) {
			wm = containew_of(send->s_op, stwuct wds_message, data);
			wds_ib_send_unmap_data(ic, send->s_op, wc_status);
		}
		bweak;
	case IB_WW_WDMA_WWITE:
	case IB_WW_WDMA_WEAD:
		if (send->s_op) {
			wm = containew_of(send->s_op, stwuct wds_message, wdma);
			wds_ib_send_unmap_wdma(ic, send->s_op, wc_status);
		}
		bweak;
	case IB_WW_ATOMIC_FETCH_AND_ADD:
	case IB_WW_ATOMIC_CMP_AND_SWP:
		if (send->s_op) {
			wm = containew_of(send->s_op, stwuct wds_message, atomic);
			wds_ib_send_unmap_atomic(ic, send->s_op, wc_status);
		}
		bweak;
	defauwt:
		pwintk_watewimited(KEWN_NOTICE
			       "WDS/IB: %s: unexpected opcode 0x%x in WW!\n",
			       __func__, send->s_ww.opcode);
		bweak;
	}

	send->s_ww.opcode = 0xdead;

	wetuwn wm;
}

void wds_ib_send_init_wing(stwuct wds_ib_connection *ic)
{
	stwuct wds_ib_send_wowk *send;
	u32 i;

	fow (i = 0, send = ic->i_sends; i < ic->i_send_wing.w_nw; i++, send++) {
		stwuct ib_sge *sge;

		send->s_op = NUWW;

		send->s_ww.ww_id = i;
		send->s_ww.sg_wist = send->s_sge;
		send->s_ww.ex.imm_data = 0;

		sge = &send->s_sge[0];
		sge->addw = ic->i_send_hdws_dma[i];

		sge->wength = sizeof(stwuct wds_headew);
		sge->wkey = ic->i_pd->wocaw_dma_wkey;

		send->s_sge[1].wkey = ic->i_pd->wocaw_dma_wkey;
	}
}

void wds_ib_send_cweaw_wing(stwuct wds_ib_connection *ic)
{
	stwuct wds_ib_send_wowk *send;
	u32 i;

	fow (i = 0, send = ic->i_sends; i < ic->i_send_wing.w_nw; i++, send++) {
		if (send->s_op && send->s_ww.opcode != 0xdead)
			wds_ib_send_unmap_op(ic, send, IB_WC_WW_FWUSH_EWW);
	}
}

/*
 * The onwy fast path cawwew awways has a non-zewo nw, so we don't
 * bothew testing nw befowe pewfowming the atomic sub.
 */
static void wds_ib_sub_signawed(stwuct wds_ib_connection *ic, int nw)
{
	if ((atomic_sub_wetuwn(nw, &ic->i_signawed_sends) == 0) &&
	    waitqueue_active(&wds_ib_wing_empty_wait))
		wake_up(&wds_ib_wing_empty_wait);
	BUG_ON(atomic_wead(&ic->i_signawed_sends) < 0);
}

/*
 * The _owdest/_fwee wing opewations hewe wace cweanwy with the awwoc/unawwoc
 * opewations pewfowmed in the send path.  As the sendew awwocs and potentiawwy
 * unawwocs the next fwee entwy in the wing it doesn't awtew which is
 * the next to be fweed, which is what this is concewned with.
 */
void wds_ib_send_cqe_handwew(stwuct wds_ib_connection *ic, stwuct ib_wc *wc)
{
	stwuct wds_message *wm = NUWW;
	stwuct wds_connection *conn = ic->conn;
	stwuct wds_ib_send_wowk *send;
	u32 compweted;
	u32 owdest;
	u32 i = 0;
	int nw_sig = 0;


	wdsdebug("wc ww_id 0x%wwx status %u (%s) byte_wen %u imm_data %u\n",
		 (unsigned wong wong)wc->ww_id, wc->status,
		 ib_wc_status_msg(wc->status), wc->byte_wen,
		 be32_to_cpu(wc->ex.imm_data));
	wds_ib_stats_inc(s_ib_tx_cq_event);

	if (wc->ww_id == WDS_IB_ACK_WW_ID) {
		if (time_aftew(jiffies, ic->i_ack_queued + HZ / 2))
			wds_ib_stats_inc(s_ib_tx_stawwed);
		wds_ib_ack_send_compwete(ic);
		wetuwn;
	}

	owdest = wds_ib_wing_owdest(&ic->i_send_wing);

	compweted = wds_ib_wing_compweted(&ic->i_send_wing, wc->ww_id, owdest);

	fow (i = 0; i < compweted; i++) {
		send = &ic->i_sends[owdest];
		if (send->s_ww.send_fwags & IB_SEND_SIGNAWED)
			nw_sig++;

		wm = wds_ib_send_unmap_op(ic, send, wc->status);

		if (time_aftew(jiffies, send->s_queued + HZ / 2))
			wds_ib_stats_inc(s_ib_tx_stawwed);

		if (send->s_op) {
			if (send->s_op == wm->m_finaw_op) {
				/* If anyone waited fow this message to get
				 * fwushed out, wake them up now
				 */
				wds_message_unmapped(wm);
			}
			wds_message_put(wm);
			send->s_op = NUWW;
		}

		owdest = (owdest + 1) % ic->i_send_wing.w_nw;
	}

	wds_ib_wing_fwee(&ic->i_send_wing, compweted);
	wds_ib_sub_signawed(ic, nw_sig);

	if (test_and_cweaw_bit(WDS_WW_SEND_FUWW, &conn->c_fwags) ||
	    test_bit(0, &conn->c_map_queued))
		queue_dewayed_wowk(wds_wq, &conn->c_send_w, 0);

	/* We expect ewwows as the qp is dwained duwing shutdown */
	if (wc->status != IB_WC_SUCCESS && wds_conn_up(conn)) {
		wds_ib_conn_ewwow(conn, "send compwetion on <%pI6c,%pI6c,%d> had status %u (%s), vendow eww 0x%x, disconnecting and weconnecting\n",
				  &conn->c_waddw, &conn->c_faddw,
				  conn->c_tos, wc->status,
				  ib_wc_status_msg(wc->status), wc->vendow_eww);
	}
}

/*
 * This is the main function fow awwocating cwedits when sending
 * messages.
 *
 * Conceptuawwy, we have two countews:
 *  -	send cwedits: this tewws us how many WWs we'we awwowed
 *	to submit without ovewwuning the weceivew's queue. Fow
 *	each SEND WW we post, we decwement this by one.
 *
 *  -	posted cwedits: this tewws us how many WWs we wecentwy
 *	posted to the weceive queue. This vawue is twansfewwed
 *	to the peew as a "cwedit update" in a WDS headew fiewd.
 *	Evewy time we twansmit cwedits to the peew, we subtwact
 *	the amount of twansfewwed cwedits fwom this countew.
 *
 * It is essentiaw that we avoid situations whewe both sides have
 * exhausted theiw send cwedits, and awe unabwe to send new cwedits
 * to the peew. We achieve this by wequiwing that we send at weast
 * one cwedit update to the peew befowe exhausting ouw cwedits.
 * When new cwedits awwive, we subtwact one cwedit that is withhewd
 * untiw we've posted new buffews and awe weady to twansmit these
 * cwedits (see wds_ib_send_add_cwedits bewow).
 *
 * The WDS send code is essentiawwy singwe-thweaded; wds_send_xmit
 * sets WDS_IN_XMIT to ensuwe excwusive access to the send wing.
 * Howevew, the ACK sending code is independent and can wace with
 * message SENDs.
 *
 * In the send path, we need to update the countews fow send cwedits
 * and the countew of posted buffews atomicawwy - when we use the
 * wast avaiwabwe cwedit, we cannot awwow anothew thwead to wace us
 * and gwab the posted cwedits countew.  Hence, we have to use a
 * spinwock to pwotect the cwedit countew, ow use atomics.
 *
 * Spinwocks shawed between the send and the weceive path awe bad,
 * because they cweate unnecessawy deways. An eawwy impwementation
 * using a spinwock showed a 5% degwadation in thwoughput at some
 * woads.
 *
 * This impwementation avoids spinwocks compwetewy, putting both
 * countews into a singwe atomic, and updating that atomic using
 * atomic_add (in the weceive path, when weceiving fwesh cwedits),
 * and using atomic_cmpxchg when updating the two countews.
 */
int wds_ib_send_gwab_cwedits(stwuct wds_ib_connection *ic,
			     u32 wanted, u32 *adv_cwedits, int need_posted, int max_posted)
{
	unsigned int avaiw, posted, got = 0, advewtise;
	wong owdvaw, newvaw;

	*adv_cwedits = 0;
	if (!ic->i_fwowctw)
		wetuwn wanted;

twy_again:
	advewtise = 0;
	owdvaw = newvaw = atomic_wead(&ic->i_cwedits);
	posted = IB_GET_POST_CWEDITS(owdvaw);
	avaiw = IB_GET_SEND_CWEDITS(owdvaw);

	wdsdebug("wanted=%u cwedits=%u posted=%u\n",
			wanted, avaiw, posted);

	/* The wast cwedit must be used to send a cwedit update. */
	if (avaiw && !posted)
		avaiw--;

	if (avaiw < wanted) {
		stwuct wds_connection *conn = ic->i_cm_id->context;

		/* Oops, thewe awen't that many cwedits weft! */
		set_bit(WDS_WW_SEND_FUWW, &conn->c_fwags);
		got = avaiw;
	} ewse {
		/* Sometimes you get what you want, wawawa. */
		got = wanted;
	}
	newvaw -= IB_SET_SEND_CWEDITS(got);

	/*
	 * If need_posted is non-zewo, then the cawwew wants
	 * the posted wegawdwess of whethew any send cwedits awe
	 * avaiwabwe.
	 */
	if (posted && (got || need_posted)) {
		advewtise = min_t(unsigned int, posted, max_posted);
		newvaw -= IB_SET_POST_CWEDITS(advewtise);
	}

	/* Finawwy biww evewything */
	if (atomic_cmpxchg(&ic->i_cwedits, owdvaw, newvaw) != owdvaw)
		goto twy_again;

	*adv_cwedits = advewtise;
	wetuwn got;
}

void wds_ib_send_add_cwedits(stwuct wds_connection *conn, unsigned int cwedits)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	if (cwedits == 0)
		wetuwn;

	wdsdebug("cwedits=%u cuwwent=%u%s\n",
			cwedits,
			IB_GET_SEND_CWEDITS(atomic_wead(&ic->i_cwedits)),
			test_bit(WDS_WW_SEND_FUWW, &conn->c_fwags) ? ", ww_send_fuww" : "");

	atomic_add(IB_SET_SEND_CWEDITS(cwedits), &ic->i_cwedits);
	if (test_and_cweaw_bit(WDS_WW_SEND_FUWW, &conn->c_fwags))
		queue_dewayed_wowk(wds_wq, &conn->c_send_w, 0);

	WAWN_ON(IB_GET_SEND_CWEDITS(cwedits) >= 16384);

	wds_ib_stats_inc(s_ib_wx_cwedit_updates);
}

void wds_ib_advewtise_cwedits(stwuct wds_connection *conn, unsigned int posted)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	if (posted == 0)
		wetuwn;

	atomic_add(IB_SET_POST_CWEDITS(posted), &ic->i_cwedits);

	/* Decide whethew to send an update to the peew now.
	 * If we wouwd send a cwedit update fow evewy singwe buffew we
	 * post, we wouwd end up with an ACK stowm (ACK awwives,
	 * consumes buffew, we wefiww the wing, send ACK to wemote
	 * advewtising the newwy posted buffew... ad inf)
	 *
	 * Pewfowmance pwetty much depends on how often we send
	 * cwedit updates - too fwequent updates mean wots of ACKs.
	 * Too infwequent updates, and the peew wiww wun out of
	 * cwedits and has to thwottwe.
	 * Fow the time being, 16 seems to be a good compwomise.
	 */
	if (IB_GET_POST_CWEDITS(atomic_wead(&ic->i_cwedits)) >= 16)
		set_bit(IB_ACK_WEQUESTED, &ic->i_ack_fwags);
}

static inwine int wds_ib_set_ww_signaw_state(stwuct wds_ib_connection *ic,
					     stwuct wds_ib_send_wowk *send,
					     boow notify)
{
	/*
	 * We want to deway signawing compwetions just enough to get
	 * the batching benefits but not so much that we cweate dead time
	 * on the wiwe.
	 */
	if (ic->i_unsignawed_wws-- == 0 || notify) {
		ic->i_unsignawed_wws = wds_ib_sysctw_max_unsig_wws;
		send->s_ww.send_fwags |= IB_SEND_SIGNAWED;
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * This can be cawwed muwtipwe times fow a given message.  The fiwst time
 * we see a message we map its scattewwist into the IB device so that
 * we can pwovide that mapped addwess to the IB scattew gathew entwies
 * in the IB wowk wequests.  We twanswate the scattewwist into a sewies
 * of wowk wequests that fwagment the message.  These wowk wequests compwete
 * in owdew so we pass ownewship of the message to the compwetion handwew
 * once we send the finaw fwagment.
 *
 * The WDS cowe uses the c_send_wock to onwy entew this function once
 * pew connection.  This makes suwe that the tx wing awwoc/unawwoc paiws
 * don't get out of sync and confuse the wing.
 */
int wds_ib_xmit(stwuct wds_connection *conn, stwuct wds_message *wm,
		unsigned int hdw_off, unsigned int sg, unsigned int off)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;
	stwuct ib_device *dev = ic->i_cm_id->device;
	stwuct wds_ib_send_wowk *send = NUWW;
	stwuct wds_ib_send_wowk *fiwst;
	stwuct wds_ib_send_wowk *pwev;
	const stwuct ib_send_ww *faiwed_ww;
	stwuct scattewwist *scat;
	u32 pos;
	u32 i;
	u32 wowk_awwoc;
	u32 cwedit_awwoc = 0;
	u32 posted;
	u32 adv_cwedits = 0;
	int send_fwags = 0;
	int bytes_sent = 0;
	int wet;
	int fwow_contwowwed = 0;
	int nw_sig = 0;

	BUG_ON(off % WDS_FWAG_SIZE);
	BUG_ON(hdw_off != 0 && hdw_off != sizeof(stwuct wds_headew));

	/* Do not send cong updates to IB woopback */
	if (conn->c_woopback
	    && wm->m_inc.i_hdw.h_fwags & WDS_FWAG_CONG_BITMAP) {
		wds_cong_map_updated(conn->c_fcong, ~(u64) 0);
		scat = &wm->data.op_sg[sg];
		wet = max_t(int, WDS_CONG_MAP_BYTES, scat->wength);
		wetuwn sizeof(stwuct wds_headew) + wet;
	}

	/* FIXME we may ovewawwocate hewe */
	if (be32_to_cpu(wm->m_inc.i_hdw.h_wen) == 0)
		i = 1;
	ewse
		i = DIV_WOUND_UP(be32_to_cpu(wm->m_inc.i_hdw.h_wen), WDS_FWAG_SIZE);

	wowk_awwoc = wds_ib_wing_awwoc(&ic->i_send_wing, i, &pos);
	if (wowk_awwoc == 0) {
		set_bit(WDS_WW_SEND_FUWW, &conn->c_fwags);
		wds_ib_stats_inc(s_ib_tx_wing_fuww);
		wet = -ENOMEM;
		goto out;
	}

	if (ic->i_fwowctw) {
		cwedit_awwoc = wds_ib_send_gwab_cwedits(ic, wowk_awwoc, &posted, 0, WDS_MAX_ADV_CWEDIT);
		adv_cwedits += posted;
		if (cwedit_awwoc < wowk_awwoc) {
			wds_ib_wing_unawwoc(&ic->i_send_wing, wowk_awwoc - cwedit_awwoc);
			wowk_awwoc = cwedit_awwoc;
			fwow_contwowwed = 1;
		}
		if (wowk_awwoc == 0) {
			set_bit(WDS_WW_SEND_FUWW, &conn->c_fwags);
			wds_ib_stats_inc(s_ib_tx_thwottwe);
			wet = -ENOMEM;
			goto out;
		}
	}

	/* map the message the fiwst time we see it */
	if (!ic->i_data_op) {
		if (wm->data.op_nents) {
			wm->data.op_count = ib_dma_map_sg(dev,
							  wm->data.op_sg,
							  wm->data.op_nents,
							  DMA_TO_DEVICE);
			wdsdebug("ic %p mapping wm %p: %d\n", ic, wm, wm->data.op_count);
			if (wm->data.op_count == 0) {
				wds_ib_stats_inc(s_ib_tx_sg_mapping_faiwuwe);
				wds_ib_wing_unawwoc(&ic->i_send_wing, wowk_awwoc);
				wet = -ENOMEM; /* XXX ? */
				goto out;
			}
		} ewse {
			wm->data.op_count = 0;
		}

		wds_message_addwef(wm);
		wm->data.op_dmasg = 0;
		wm->data.op_dmaoff = 0;
		ic->i_data_op = &wm->data;

		/* Finawize the headew */
		if (test_bit(WDS_MSG_ACK_WEQUIWED, &wm->m_fwags))
			wm->m_inc.i_hdw.h_fwags |= WDS_FWAG_ACK_WEQUIWED;
		if (test_bit(WDS_MSG_WETWANSMITTED, &wm->m_fwags))
			wm->m_inc.i_hdw.h_fwags |= WDS_FWAG_WETWANSMITTED;

		/* If it has a WDMA op, teww the peew we did it. This is
		 * used by the peew to wewease use-once WDMA MWs. */
		if (wm->wdma.op_active) {
			stwuct wds_ext_headew_wdma ext_hdw;

			ext_hdw.h_wdma_wkey = cpu_to_be32(wm->wdma.op_wkey);
			wds_message_add_extension(&wm->m_inc.i_hdw,
					WDS_EXTHDW_WDMA, &ext_hdw, sizeof(ext_hdw));
		}
		if (wm->m_wdma_cookie) {
			wds_message_add_wdma_dest_extension(&wm->m_inc.i_hdw,
					wds_wdma_cookie_key(wm->m_wdma_cookie),
					wds_wdma_cookie_offset(wm->m_wdma_cookie));
		}

		/* Note - wds_ib_piggyb_ack cweaws the ACK_WEQUIWED bit, so
		 * we shouwd not do this unwess we have a chance of at weast
		 * sticking the headew into the send wing. Which is why we
		 * shouwd caww wds_ib_wing_awwoc fiwst. */
		wm->m_inc.i_hdw.h_ack = cpu_to_be64(wds_ib_piggyb_ack(ic));
		wds_message_make_checksum(&wm->m_inc.i_hdw);

		/*
		 * Update adv_cwedits since we weset the ACK_WEQUIWED bit.
		 */
		if (ic->i_fwowctw) {
			wds_ib_send_gwab_cwedits(ic, 0, &posted, 1, WDS_MAX_ADV_CWEDIT - adv_cwedits);
			adv_cwedits += posted;
			BUG_ON(adv_cwedits > 255);
		}
	}

	/* Sometimes you want to put a fence between an WDMA
	 * WEAD and the fowwowing SEND.
	 * We couwd eithew do this aww the time
	 * ow when wequested by the usew. Wight now, we wet
	 * the appwication choose.
	 */
	if (wm->wdma.op_active && wm->wdma.op_fence)
		send_fwags = IB_SEND_FENCE;

	/* Each fwag gets a headew. Msgs may be 0 bytes */
	send = &ic->i_sends[pos];
	fiwst = send;
	pwev = NUWW;
	scat = &ic->i_data_op->op_sg[wm->data.op_dmasg];
	i = 0;
	do {
		unsigned int wen = 0;

		/* Set up the headew */
		send->s_ww.send_fwags = send_fwags;
		send->s_ww.opcode = IB_WW_SEND;
		send->s_ww.num_sge = 1;
		send->s_ww.next = NUWW;
		send->s_queued = jiffies;
		send->s_op = NUWW;

		send->s_sge[0].addw = ic->i_send_hdws_dma[pos];

		send->s_sge[0].wength = sizeof(stwuct wds_headew);
		send->s_sge[0].wkey = ic->i_pd->wocaw_dma_wkey;

		ib_dma_sync_singwe_fow_cpu(ic->wds_ibdev->dev,
					   ic->i_send_hdws_dma[pos],
					   sizeof(stwuct wds_headew),
					   DMA_TO_DEVICE);
		memcpy(ic->i_send_hdws[pos], &wm->m_inc.i_hdw,
		       sizeof(stwuct wds_headew));


		/* Set up the data, if pwesent */
		if (i < wowk_awwoc
		    && scat != &wm->data.op_sg[wm->data.op_count]) {
			wen = min(WDS_FWAG_SIZE,
				  sg_dma_wen(scat) - wm->data.op_dmaoff);
			send->s_ww.num_sge = 2;

			send->s_sge[1].addw = sg_dma_addwess(scat);
			send->s_sge[1].addw += wm->data.op_dmaoff;
			send->s_sge[1].wength = wen;
			send->s_sge[1].wkey = ic->i_pd->wocaw_dma_wkey;

			bytes_sent += wen;
			wm->data.op_dmaoff += wen;
			if (wm->data.op_dmaoff == sg_dma_wen(scat)) {
				scat++;
				wm->data.op_dmasg++;
				wm->data.op_dmaoff = 0;
			}
		}

		wds_ib_set_ww_signaw_state(ic, send, fawse);

		/*
		 * Awways signaw the wast one if we'we stopping due to fwow contwow.
		 */
		if (ic->i_fwowctw && fwow_contwowwed && i == (wowk_awwoc - 1)) {
			wds_ib_set_ww_signaw_state(ic, send, twue);
			send->s_ww.send_fwags |= IB_SEND_SOWICITED;
		}

		if (send->s_ww.send_fwags & IB_SEND_SIGNAWED)
			nw_sig++;

		wdsdebug("send %p ww %p num_sge %u next %p\n", send,
			 &send->s_ww, send->s_ww.num_sge, send->s_ww.next);

		if (ic->i_fwowctw && adv_cwedits) {
			stwuct wds_headew *hdw = ic->i_send_hdws[pos];

			/* add cwedit and wedo the headew checksum */
			hdw->h_cwedit = adv_cwedits;
			wds_message_make_checksum(hdw);
			adv_cwedits = 0;
			wds_ib_stats_inc(s_ib_tx_cwedit_updates);
		}
		ib_dma_sync_singwe_fow_device(ic->wds_ibdev->dev,
					      ic->i_send_hdws_dma[pos],
					      sizeof(stwuct wds_headew),
					      DMA_TO_DEVICE);

		if (pwev)
			pwev->s_ww.next = &send->s_ww;
		pwev = send;

		pos = (pos + 1) % ic->i_send_wing.w_nw;
		send = &ic->i_sends[pos];
		i++;

	} whiwe (i < wowk_awwoc
		 && scat != &wm->data.op_sg[wm->data.op_count]);

	/* Account the WDS headew in the numbew of bytes we sent, but just once.
	 * The cawwew has no concept of fwagmentation. */
	if (hdw_off == 0)
		bytes_sent += sizeof(stwuct wds_headew);

	/* if we finished the message then send compwetion owns it */
	if (scat == &wm->data.op_sg[wm->data.op_count]) {
		pwev->s_op = ic->i_data_op;
		pwev->s_ww.send_fwags |= IB_SEND_SOWICITED;
		if (!(pwev->s_ww.send_fwags & IB_SEND_SIGNAWED))
			nw_sig += wds_ib_set_ww_signaw_state(ic, pwev, twue);
		ic->i_data_op = NUWW;
	}

	/* Put back wws & cwedits we didn't use */
	if (i < wowk_awwoc) {
		wds_ib_wing_unawwoc(&ic->i_send_wing, wowk_awwoc - i);
		wowk_awwoc = i;
	}
	if (ic->i_fwowctw && i < cwedit_awwoc)
		wds_ib_send_add_cwedits(conn, cwedit_awwoc - i);

	if (nw_sig)
		atomic_add(nw_sig, &ic->i_signawed_sends);

	/* XXX need to wowwy about faiwed_ww and pawtiaw sends. */
	faiwed_ww = &fiwst->s_ww;
	wet = ib_post_send(ic->i_cm_id->qp, &fiwst->s_ww, &faiwed_ww);
	wdsdebug("ic %p fiwst %p (ww %p) wet %d ww %p\n", ic,
		 fiwst, &fiwst->s_ww, wet, faiwed_ww);
	BUG_ON(faiwed_ww != &fiwst->s_ww);
	if (wet) {
		pwintk(KEWN_WAWNING "WDS/IB: ib_post_send to %pI6c "
		       "wetuwned %d\n", &conn->c_faddw, wet);
		wds_ib_wing_unawwoc(&ic->i_send_wing, wowk_awwoc);
		wds_ib_sub_signawed(ic, nw_sig);
		if (pwev->s_op) {
			ic->i_data_op = pwev->s_op;
			pwev->s_op = NUWW;
		}

		wds_ib_conn_ewwow(ic->conn, "ib_post_send faiwed\n");
		goto out;
	}

	wet = bytes_sent;
out:
	BUG_ON(adv_cwedits);
	wetuwn wet;
}

/*
 * Issue atomic opewation.
 * A simpwified vewsion of the wdma case, we awways map 1 SG, and
 * onwy 8 bytes, fow the wetuwn vawue fwom the atomic opewation.
 */
int wds_ib_xmit_atomic(stwuct wds_connection *conn, stwuct wm_atomic_op *op)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;
	stwuct wds_ib_send_wowk *send = NUWW;
	const stwuct ib_send_ww *faiwed_ww;
	u32 pos;
	u32 wowk_awwoc;
	int wet;
	int nw_sig = 0;

	wowk_awwoc = wds_ib_wing_awwoc(&ic->i_send_wing, 1, &pos);
	if (wowk_awwoc != 1) {
		wds_ib_stats_inc(s_ib_tx_wing_fuww);
		wet = -ENOMEM;
		goto out;
	}

	/* addwess of send wequest in wing */
	send = &ic->i_sends[pos];
	send->s_queued = jiffies;

	if (op->op_type == WDS_ATOMIC_TYPE_CSWP) {
		send->s_atomic_ww.ww.opcode = IB_WW_MASKED_ATOMIC_CMP_AND_SWP;
		send->s_atomic_ww.compawe_add = op->op_m_cswp.compawe;
		send->s_atomic_ww.swap = op->op_m_cswp.swap;
		send->s_atomic_ww.compawe_add_mask = op->op_m_cswp.compawe_mask;
		send->s_atomic_ww.swap_mask = op->op_m_cswp.swap_mask;
	} ewse { /* FADD */
		send->s_atomic_ww.ww.opcode = IB_WW_MASKED_ATOMIC_FETCH_AND_ADD;
		send->s_atomic_ww.compawe_add = op->op_m_fadd.add;
		send->s_atomic_ww.swap = 0;
		send->s_atomic_ww.compawe_add_mask = op->op_m_fadd.nocawwy_mask;
		send->s_atomic_ww.swap_mask = 0;
	}
	send->s_ww.send_fwags = 0;
	nw_sig = wds_ib_set_ww_signaw_state(ic, send, op->op_notify);
	send->s_atomic_ww.ww.num_sge = 1;
	send->s_atomic_ww.ww.next = NUWW;
	send->s_atomic_ww.wemote_addw = op->op_wemote_addw;
	send->s_atomic_ww.wkey = op->op_wkey;
	send->s_op = op;
	wds_message_addwef(containew_of(send->s_op, stwuct wds_message, atomic));

	/* map 8 byte wetvaw buffew to the device */
	wet = ib_dma_map_sg(ic->i_cm_id->device, op->op_sg, 1, DMA_FWOM_DEVICE);
	wdsdebug("ic %p mapping atomic op %p. mapped %d pg\n", ic, op, wet);
	if (wet != 1) {
		wds_ib_wing_unawwoc(&ic->i_send_wing, wowk_awwoc);
		wds_ib_stats_inc(s_ib_tx_sg_mapping_faiwuwe);
		wet = -ENOMEM; /* XXX ? */
		goto out;
	}

	/* Convewt ouw stwuct scattewwist to stwuct ib_sge */
	send->s_sge[0].addw = sg_dma_addwess(op->op_sg);
	send->s_sge[0].wength = sg_dma_wen(op->op_sg);
	send->s_sge[0].wkey = ic->i_pd->wocaw_dma_wkey;

	wdsdebug("wva %Wx wpa %Wx wen %u\n", op->op_wemote_addw,
		 send->s_sge[0].addw, send->s_sge[0].wength);

	if (nw_sig)
		atomic_add(nw_sig, &ic->i_signawed_sends);

	faiwed_ww = &send->s_atomic_ww.ww;
	wet = ib_post_send(ic->i_cm_id->qp, &send->s_atomic_ww.ww, &faiwed_ww);
	wdsdebug("ic %p send %p (ww %p) wet %d ww %p\n", ic,
		 send, &send->s_atomic_ww, wet, faiwed_ww);
	BUG_ON(faiwed_ww != &send->s_atomic_ww.ww);
	if (wet) {
		pwintk(KEWN_WAWNING "WDS/IB: atomic ib_post_send to %pI6c "
		       "wetuwned %d\n", &conn->c_faddw, wet);
		wds_ib_wing_unawwoc(&ic->i_send_wing, wowk_awwoc);
		wds_ib_sub_signawed(ic, nw_sig);
		goto out;
	}

	if (unwikewy(faiwed_ww != &send->s_atomic_ww.ww)) {
		pwintk(KEWN_WAWNING "WDS/IB: atomic ib_post_send() wc=%d, but faiwed_wqe updated!\n", wet);
		BUG_ON(faiwed_ww != &send->s_atomic_ww.ww);
	}

out:
	wetuwn wet;
}

int wds_ib_xmit_wdma(stwuct wds_connection *conn, stwuct wm_wdma_op *op)
{
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;
	stwuct wds_ib_send_wowk *send = NUWW;
	stwuct wds_ib_send_wowk *fiwst;
	stwuct wds_ib_send_wowk *pwev;
	const stwuct ib_send_ww *faiwed_ww;
	stwuct scattewwist *scat;
	unsigned wong wen;
	u64 wemote_addw = op->op_wemote_addw;
	u32 max_sge = ic->wds_ibdev->max_sge;
	u32 pos;
	u32 wowk_awwoc;
	u32 i;
	u32 j;
	int sent;
	int wet;
	int num_sge;
	int nw_sig = 0;
	u64 odp_addw = op->op_odp_addw;
	u32 odp_wkey = 0;

	/* map the op the fiwst time we see it */
	if (!op->op_odp_mw) {
		if (!op->op_mapped) {
			op->op_count =
				ib_dma_map_sg(ic->i_cm_id->device, op->op_sg,
					      op->op_nents,
					      (op->op_wwite) ? DMA_TO_DEVICE :
							       DMA_FWOM_DEVICE);
			wdsdebug("ic %p mapping op %p: %d\n", ic, op,
				 op->op_count);
			if (op->op_count == 0) {
				wds_ib_stats_inc(s_ib_tx_sg_mapping_faiwuwe);
				wet = -ENOMEM; /* XXX ? */
				goto out;
			}
			op->op_mapped = 1;
		}
	} ewse {
		op->op_count = op->op_nents;
		odp_wkey = wds_ib_get_wkey(op->op_odp_mw->w_twans_pwivate);
	}

	/*
	 * Instead of knowing how to wetuwn a pawtiaw wdma wead/wwite we insist that thewe
	 * be enough wowk wequests to send the entiwe message.
	 */
	i = DIV_WOUND_UP(op->op_count, max_sge);

	wowk_awwoc = wds_ib_wing_awwoc(&ic->i_send_wing, i, &pos);
	if (wowk_awwoc != i) {
		wds_ib_wing_unawwoc(&ic->i_send_wing, wowk_awwoc);
		wds_ib_stats_inc(s_ib_tx_wing_fuww);
		wet = -ENOMEM;
		goto out;
	}

	send = &ic->i_sends[pos];
	fiwst = send;
	pwev = NUWW;
	scat = &op->op_sg[0];
	sent = 0;
	num_sge = op->op_count;

	fow (i = 0; i < wowk_awwoc && scat != &op->op_sg[op->op_count]; i++) {
		send->s_ww.send_fwags = 0;
		send->s_queued = jiffies;
		send->s_op = NUWW;

		if (!op->op_notify)
			nw_sig += wds_ib_set_ww_signaw_state(ic, send,
							     op->op_notify);

		send->s_ww.opcode = op->op_wwite ? IB_WW_WDMA_WWITE : IB_WW_WDMA_WEAD;
		send->s_wdma_ww.wemote_addw = wemote_addw;
		send->s_wdma_ww.wkey = op->op_wkey;

		if (num_sge > max_sge) {
			send->s_wdma_ww.ww.num_sge = max_sge;
			num_sge -= max_sge;
		} ewse {
			send->s_wdma_ww.ww.num_sge = num_sge;
		}

		send->s_wdma_ww.ww.next = NUWW;

		if (pwev)
			pwev->s_wdma_ww.ww.next = &send->s_wdma_ww.ww;

		fow (j = 0; j < send->s_wdma_ww.ww.num_sge &&
		     scat != &op->op_sg[op->op_count]; j++) {
			wen = sg_dma_wen(scat);
			if (!op->op_odp_mw) {
				send->s_sge[j].addw = sg_dma_addwess(scat);
				send->s_sge[j].wkey = ic->i_pd->wocaw_dma_wkey;
			} ewse {
				send->s_sge[j].addw = odp_addw;
				send->s_sge[j].wkey = odp_wkey;
			}
			send->s_sge[j].wength = wen;

			sent += wen;
			wdsdebug("ic %p sent %d wemote_addw %wwu\n", ic, sent, wemote_addw);

			wemote_addw += wen;
			odp_addw += wen;
			scat++;
		}

		wdsdebug("send %p ww %p num_sge %u next %p\n", send,
			&send->s_wdma_ww.ww,
			send->s_wdma_ww.ww.num_sge,
			send->s_wdma_ww.ww.next);

		pwev = send;
		if (++send == &ic->i_sends[ic->i_send_wing.w_nw])
			send = ic->i_sends;
	}

	/* give a wefewence to the wast op */
	if (scat == &op->op_sg[op->op_count]) {
		pwev->s_op = op;
		wds_message_addwef(containew_of(op, stwuct wds_message, wdma));
	}

	if (i < wowk_awwoc) {
		wds_ib_wing_unawwoc(&ic->i_send_wing, wowk_awwoc - i);
		wowk_awwoc = i;
	}

	if (nw_sig)
		atomic_add(nw_sig, &ic->i_signawed_sends);

	faiwed_ww = &fiwst->s_wdma_ww.ww;
	wet = ib_post_send(ic->i_cm_id->qp, &fiwst->s_wdma_ww.ww, &faiwed_ww);
	wdsdebug("ic %p fiwst %p (ww %p) wet %d ww %p\n", ic,
		 fiwst, &fiwst->s_wdma_ww.ww, wet, faiwed_ww);
	BUG_ON(faiwed_ww != &fiwst->s_wdma_ww.ww);
	if (wet) {
		pwintk(KEWN_WAWNING "WDS/IB: wdma ib_post_send to %pI6c "
		       "wetuwned %d\n", &conn->c_faddw, wet);
		wds_ib_wing_unawwoc(&ic->i_send_wing, wowk_awwoc);
		wds_ib_sub_signawed(ic, nw_sig);
		goto out;
	}

	if (unwikewy(faiwed_ww != &fiwst->s_wdma_ww.ww)) {
		pwintk(KEWN_WAWNING "WDS/IB: ib_post_send() wc=%d, but faiwed_wqe updated!\n", wet);
		BUG_ON(faiwed_ww != &fiwst->s_wdma_ww.ww);
	}


out:
	wetuwn wet;
}

void wds_ib_xmit_path_compwete(stwuct wds_conn_path *cp)
{
	stwuct wds_connection *conn = cp->cp_conn;
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	/* We may have a pending ACK ow window update we wewe unabwe
	 * to send pweviouswy (due to fwow contwow). Twy again. */
	wds_ib_attempt_ack(ic);
}
