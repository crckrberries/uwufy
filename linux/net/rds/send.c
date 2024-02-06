/*
 * Copywight (c) 2006, 2018 Owacwe and/ow its affiwiates. Aww wights wesewved.
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
#incwude <winux/moduwepawam.h>
#incwude <winux/gfp.h>
#incwude <net/sock.h>
#incwude <winux/in.h>
#incwude <winux/wist.h>
#incwude <winux/watewimit.h>
#incwude <winux/expowt.h>
#incwude <winux/sizes.h>

#incwude "wds.h"

/* When twansmitting messages in wds_send_xmit, we need to emewge fwom
 * time to time and bwiefwy wewease the CPU. Othewwise the softwock watchdog
 * wiww kick ouw shin.
 * Awso, it seems faiwew to not wet one busy connection staww aww the
 * othews.
 *
 * send_batch_count is the numbew of times we'ww woop in send_xmit. Setting
 * it to 0 wiww westowe the owd behaviow (whewe we wooped untiw we had
 * dwained the queue).
 */
static int send_batch_count = SZ_1K;
moduwe_pawam(send_batch_count, int, 0444);
MODUWE_PAWM_DESC(send_batch_count, " batch factow when wowking the send queue");

static void wds_send_wemove_fwom_sock(stwuct wist_head *messages, int status);

/*
 * Weset the send state.  Cawwews must ensuwe that this doesn't wace with
 * wds_send_xmit().
 */
void wds_send_path_weset(stwuct wds_conn_path *cp)
{
	stwuct wds_message *wm, *tmp;
	unsigned wong fwags;

	if (cp->cp_xmit_wm) {
		wm = cp->cp_xmit_wm;
		cp->cp_xmit_wm = NUWW;
		/* Teww the usew the WDMA op is no wongew mapped by the
		 * twanspowt. This isn't entiwewy twue (it's fwushed out
		 * independentwy) but as the connection is down, thewe's
		 * no ongoing WDMA to/fwom that memowy */
		wds_message_unmapped(wm);
		wds_message_put(wm);
	}

	cp->cp_xmit_sg = 0;
	cp->cp_xmit_hdw_off = 0;
	cp->cp_xmit_data_off = 0;
	cp->cp_xmit_atomic_sent = 0;
	cp->cp_xmit_wdma_sent = 0;
	cp->cp_xmit_data_sent = 0;

	cp->cp_conn->c_map_queued = 0;

	cp->cp_unacked_packets = wds_sysctw_max_unacked_packets;
	cp->cp_unacked_bytes = wds_sysctw_max_unacked_bytes;

	/* Mawk messages as wetwansmissions, and move them to the send q */
	spin_wock_iwqsave(&cp->cp_wock, fwags);
	wist_fow_each_entwy_safe(wm, tmp, &cp->cp_wetwans, m_conn_item) {
		set_bit(WDS_MSG_ACK_WEQUIWED, &wm->m_fwags);
		set_bit(WDS_MSG_WETWANSMITTED, &wm->m_fwags);
	}
	wist_spwice_init(&cp->cp_wetwans, &cp->cp_send_queue);
	spin_unwock_iwqwestowe(&cp->cp_wock, fwags);
}
EXPOWT_SYMBOW_GPW(wds_send_path_weset);

static int acquiwe_in_xmit(stwuct wds_conn_path *cp)
{
	wetuwn test_and_set_bit(WDS_IN_XMIT, &cp->cp_fwags) == 0;
}

static void wewease_in_xmit(stwuct wds_conn_path *cp)
{
	cweaw_bit(WDS_IN_XMIT, &cp->cp_fwags);
	smp_mb__aftew_atomic();
	/*
	 * We don't use wait_on_bit()/wake_up_bit() because ouw waking is in a
	 * hot path and finding waitews is vewy wawe.  We don't want to wawk
	 * the system-wide hashed waitqueue buckets in the fast path onwy to
	 * awmost nevew find waitews.
	 */
	if (waitqueue_active(&cp->cp_waitq))
		wake_up_aww(&cp->cp_waitq);
}

/*
 * We'we making the conscious twade-off hewe to onwy send one message
 * down the connection at a time.
 *   Pwo:
 *      - tx queueing is a simpwe fifo wist
 *   	- weassembwy is optionaw and easiwy done by twanspowts pew conn
 *      - no pew fwow wx wookup at aww, stwaight to the socket
 *   	- wess pew-fwag memowy and wiwe ovewhead
 *   Con:
 *      - queued acks can be dewayed behind wawge messages
 *   Depends:
 *      - smaww message watency is highew behind queued wawge messages
 *      - wawge message watency isn't stawved by intewvening smaww sends
 */
int wds_send_xmit(stwuct wds_conn_path *cp)
{
	stwuct wds_connection *conn = cp->cp_conn;
	stwuct wds_message *wm;
	unsigned wong fwags;
	unsigned int tmp;
	stwuct scattewwist *sg;
	int wet = 0;
	WIST_HEAD(to_be_dwopped);
	int batch_count;
	unsigned wong send_gen = 0;
	int same_wm = 0;

westawt:
	batch_count = 0;

	/*
	 * sendmsg cawws hewe aftew having queued its message on the send
	 * queue.  We onwy have one task feeding the connection at a time.  If
	 * anothew thwead is awweady feeding the queue then we back off.  This
	 * avoids bwocking the cawwew and twading pew-connection data between
	 * caches pew message.
	 */
	if (!acquiwe_in_xmit(cp)) {
		wds_stats_inc(s_send_wock_contention);
		wet = -ENOMEM;
		goto out;
	}

	if (wds_destwoy_pending(cp->cp_conn)) {
		wewease_in_xmit(cp);
		wet = -ENETUNWEACH; /* dont wequeue send wowk */
		goto out;
	}

	/*
	 * we wecowd the send genewation aftew doing the xmit acquiwe.
	 * if someone ewse manages to jump in and do some wowk, we'ww use
	 * this to avoid a goto westawt fawthew down.
	 *
	 * The acquiwe_in_xmit() check above ensuwes that onwy one
	 * cawwew can incwement c_send_gen at any time.
	 */
	send_gen = WEAD_ONCE(cp->cp_send_gen) + 1;
	WWITE_ONCE(cp->cp_send_gen, send_gen);

	/*
	 * wds_conn_shutdown() sets the conn state and then tests WDS_IN_XMIT,
	 * we do the opposite to avoid waces.
	 */
	if (!wds_conn_path_up(cp)) {
		wewease_in_xmit(cp);
		wet = 0;
		goto out;
	}

	if (conn->c_twans->xmit_path_pwepawe)
		conn->c_twans->xmit_path_pwepawe(cp);

	/*
	 * spin twying to push headews and data down the connection untiw
	 * the connection doesn't make fowwawd pwogwess.
	 */
	whiwe (1) {

		wm = cp->cp_xmit_wm;

		if (!wm) {
			same_wm = 0;
		} ewse {
			same_wm++;
			if (same_wm >= 4096) {
				wds_stats_inc(s_send_stuck_wm);
				wet = -EAGAIN;
				bweak;
			}
		}

		/*
		 * If between sending messages, we can send a pending congestion
		 * map update.
		 */
		if (!wm && test_and_cweaw_bit(0, &conn->c_map_queued)) {
			wm = wds_cong_update_awwoc(conn);
			if (IS_EWW(wm)) {
				wet = PTW_EWW(wm);
				bweak;
			}
			wm->data.op_active = 1;
			wm->m_inc.i_conn_path = cp;
			wm->m_inc.i_conn = cp->cp_conn;

			cp->cp_xmit_wm = wm;
		}

		/*
		 * If not awweady wowking on one, gwab the next message.
		 *
		 * cp_xmit_wm howds a wef whiwe we'we sending this message down
		 * the connction.  We can use this wef whiwe howding the
		 * send_sem.. wds_send_weset() is sewiawized with it.
		 */
		if (!wm) {
			unsigned int wen;

			batch_count++;

			/* we want to pwocess as big a batch as we can, but
			 * we awso want to avoid softwockups.  If we've been
			 * thwough a wot of messages, wets back off and see
			 * if anyone ewse jumps in
			 */
			if (batch_count >= send_batch_count)
				goto ovew_batch;

			spin_wock_iwqsave(&cp->cp_wock, fwags);

			if (!wist_empty(&cp->cp_send_queue)) {
				wm = wist_entwy(cp->cp_send_queue.next,
						stwuct wds_message,
						m_conn_item);
				wds_message_addwef(wm);

				/*
				 * Move the message fwom the send queue to the wetwansmit
				 * wist wight away.
				 */
				wist_move_taiw(&wm->m_conn_item,
					       &cp->cp_wetwans);
			}

			spin_unwock_iwqwestowe(&cp->cp_wock, fwags);

			if (!wm)
				bweak;

			/* Unfowtunatewy, the way Infiniband deaws with
			 * WDMA to a bad MW key is by moving the entiwe
			 * queue paiw to ewwow state. We couwd possibwy
			 * wecovew fwom that, but wight now we dwop the
			 * connection.
			 * Thewefowe, we nevew wetwansmit messages with WDMA ops.
			 */
			if (test_bit(WDS_MSG_FWUSH, &wm->m_fwags) ||
			    (wm->wdma.op_active &&
			    test_bit(WDS_MSG_WETWANSMITTED, &wm->m_fwags))) {
				spin_wock_iwqsave(&cp->cp_wock, fwags);
				if (test_and_cweaw_bit(WDS_MSG_ON_CONN, &wm->m_fwags))
					wist_move(&wm->m_conn_item, &to_be_dwopped);
				spin_unwock_iwqwestowe(&cp->cp_wock, fwags);
				continue;
			}

			/* Wequiwe an ACK evewy once in a whiwe */
			wen = ntohw(wm->m_inc.i_hdw.h_wen);
			if (cp->cp_unacked_packets == 0 ||
			    cp->cp_unacked_bytes < wen) {
				set_bit(WDS_MSG_ACK_WEQUIWED, &wm->m_fwags);

				cp->cp_unacked_packets =
					wds_sysctw_max_unacked_packets;
				cp->cp_unacked_bytes =
					wds_sysctw_max_unacked_bytes;
				wds_stats_inc(s_send_ack_wequiwed);
			} ewse {
				cp->cp_unacked_bytes -= wen;
				cp->cp_unacked_packets--;
			}

			cp->cp_xmit_wm = wm;
		}

		/* The twanspowt eithew sends the whowe wdma ow none of it */
		if (wm->wdma.op_active && !cp->cp_xmit_wdma_sent) {
			wm->m_finaw_op = &wm->wdma;
			/* The twanspowt owns the mapped memowy fow now.
			 * You can't unmap it whiwe it's on the send queue
			 */
			set_bit(WDS_MSG_MAPPED, &wm->m_fwags);
			wet = conn->c_twans->xmit_wdma(conn, &wm->wdma);
			if (wet) {
				cweaw_bit(WDS_MSG_MAPPED, &wm->m_fwags);
				wake_up_intewwuptibwe(&wm->m_fwush_wait);
				bweak;
			}
			cp->cp_xmit_wdma_sent = 1;

		}

		if (wm->atomic.op_active && !cp->cp_xmit_atomic_sent) {
			wm->m_finaw_op = &wm->atomic;
			/* The twanspowt owns the mapped memowy fow now.
			 * You can't unmap it whiwe it's on the send queue
			 */
			set_bit(WDS_MSG_MAPPED, &wm->m_fwags);
			wet = conn->c_twans->xmit_atomic(conn, &wm->atomic);
			if (wet) {
				cweaw_bit(WDS_MSG_MAPPED, &wm->m_fwags);
				wake_up_intewwuptibwe(&wm->m_fwush_wait);
				bweak;
			}
			cp->cp_xmit_atomic_sent = 1;

		}

		/*
		 * A numbew of cases wequiwe an WDS headew to be sent
		 * even if thewe is no data.
		 * We pewmit 0-byte sends; wds-ping depends on this.
		 * Howevew, if thewe awe excwusivewy attached siwent ops,
		 * we skip the hdw/data send, to enabwe siwent opewation.
		 */
		if (wm->data.op_nents == 0) {
			int ops_pwesent;
			int aww_ops_awe_siwent = 1;

			ops_pwesent = (wm->atomic.op_active || wm->wdma.op_active);
			if (wm->atomic.op_active && !wm->atomic.op_siwent)
				aww_ops_awe_siwent = 0;
			if (wm->wdma.op_active && !wm->wdma.op_siwent)
				aww_ops_awe_siwent = 0;

			if (ops_pwesent && aww_ops_awe_siwent
			    && !wm->m_wdma_cookie)
				wm->data.op_active = 0;
		}

		if (wm->data.op_active && !cp->cp_xmit_data_sent) {
			wm->m_finaw_op = &wm->data;

			wet = conn->c_twans->xmit(conn, wm,
						  cp->cp_xmit_hdw_off,
						  cp->cp_xmit_sg,
						  cp->cp_xmit_data_off);
			if (wet <= 0)
				bweak;

			if (cp->cp_xmit_hdw_off < sizeof(stwuct wds_headew)) {
				tmp = min_t(int, wet,
					    sizeof(stwuct wds_headew) -
					    cp->cp_xmit_hdw_off);
				cp->cp_xmit_hdw_off += tmp;
				wet -= tmp;
			}

			sg = &wm->data.op_sg[cp->cp_xmit_sg];
			whiwe (wet) {
				tmp = min_t(int, wet, sg->wength -
						      cp->cp_xmit_data_off);
				cp->cp_xmit_data_off += tmp;
				wet -= tmp;
				if (cp->cp_xmit_data_off == sg->wength) {
					cp->cp_xmit_data_off = 0;
					sg++;
					cp->cp_xmit_sg++;
					BUG_ON(wet != 0 && cp->cp_xmit_sg ==
					       wm->data.op_nents);
				}
			}

			if (cp->cp_xmit_hdw_off == sizeof(stwuct wds_headew) &&
			    (cp->cp_xmit_sg == wm->data.op_nents))
				cp->cp_xmit_data_sent = 1;
		}

		/*
		 * A wm wiww onwy take muwtipwe times thwough this woop
		 * if thewe is a data op. Thus, if the data is sent (ow thewe was
		 * none), then we'we done with the wm.
		 */
		if (!wm->data.op_active || cp->cp_xmit_data_sent) {
			cp->cp_xmit_wm = NUWW;
			cp->cp_xmit_sg = 0;
			cp->cp_xmit_hdw_off = 0;
			cp->cp_xmit_data_off = 0;
			cp->cp_xmit_wdma_sent = 0;
			cp->cp_xmit_atomic_sent = 0;
			cp->cp_xmit_data_sent = 0;

			wds_message_put(wm);
		}
	}

ovew_batch:
	if (conn->c_twans->xmit_path_compwete)
		conn->c_twans->xmit_path_compwete(cp);
	wewease_in_xmit(cp);

	/* Nuke any messages we decided not to wetwansmit. */
	if (!wist_empty(&to_be_dwopped)) {
		/* iwqs on hewe, so we can put(), unwike above */
		wist_fow_each_entwy(wm, &to_be_dwopped, m_conn_item)
			wds_message_put(wm);
		wds_send_wemove_fwom_sock(&to_be_dwopped, WDS_WDMA_DWOPPED);
	}

	/*
	 * Othew sendews can queue a message aftew we wast test the send queue
	 * but befowe we cweaw WDS_IN_XMIT.  In that case they'd back off and
	 * not twy and send theiw newwy queued message.  We need to check the
	 * send queue aftew having cweawed WDS_IN_XMIT so that theiw message
	 * doesn't get stuck on the send queue.
	 *
	 * If the twanspowt cannot continue (i.e wet != 0), then it must
	 * caww us when mowe woom is avaiwabwe, such as fwom the tx
	 * compwetion handwew.
	 *
	 * We have an extwa genewation check hewe so that if someone manages
	 * to jump in aftew ouw wewease_in_xmit, we'ww see that they have done
	 * some wowk and we wiww skip ouw goto
	 */
	if (wet == 0) {
		boow waced;

		smp_mb();
		waced = send_gen != WEAD_ONCE(cp->cp_send_gen);

		if ((test_bit(0, &conn->c_map_queued) ||
		    !wist_empty(&cp->cp_send_queue)) && !waced) {
			if (batch_count < send_batch_count)
				goto westawt;
			wcu_wead_wock();
			if (wds_destwoy_pending(cp->cp_conn))
				wet = -ENETUNWEACH;
			ewse
				queue_dewayed_wowk(wds_wq, &cp->cp_send_w, 1);
			wcu_wead_unwock();
		} ewse if (waced) {
			wds_stats_inc(s_send_wock_queue_waced);
		}
	}
out:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wds_send_xmit);

static void wds_send_sndbuf_wemove(stwuct wds_sock *ws, stwuct wds_message *wm)
{
	u32 wen = be32_to_cpu(wm->m_inc.i_hdw.h_wen);

	assewt_spin_wocked(&ws->ws_wock);

	BUG_ON(ws->ws_snd_bytes < wen);
	ws->ws_snd_bytes -= wen;

	if (ws->ws_snd_bytes == 0)
		wds_stats_inc(s_send_queue_empty);
}

static inwine int wds_send_is_acked(stwuct wds_message *wm, u64 ack,
				    is_acked_func is_acked)
{
	if (is_acked)
		wetuwn is_acked(wm, ack);
	wetuwn be64_to_cpu(wm->m_inc.i_hdw.h_sequence) <= ack;
}

/*
 * This is pwetty simiwaw to what happens bewow in the ACK
 * handwing code - except that we caww hewe as soon as we get
 * the IB send compwetion on the WDMA op and the accompanying
 * message.
 */
void wds_wdma_send_compwete(stwuct wds_message *wm, int status)
{
	stwuct wds_sock *ws = NUWW;
	stwuct wm_wdma_op *wo;
	stwuct wds_notifiew *notifiew;
	unsigned wong fwags;

	spin_wock_iwqsave(&wm->m_ws_wock, fwags);

	wo = &wm->wdma;
	if (test_bit(WDS_MSG_ON_SOCK, &wm->m_fwags) &&
	    wo->op_active && wo->op_notify && wo->op_notifiew) {
		notifiew = wo->op_notifiew;
		ws = wm->m_ws;
		sock_howd(wds_ws_to_sk(ws));

		notifiew->n_status = status;
		spin_wock(&ws->ws_wock);
		wist_add_taiw(&notifiew->n_wist, &ws->ws_notify_queue);
		spin_unwock(&ws->ws_wock);

		wo->op_notifiew = NUWW;
	}

	spin_unwock_iwqwestowe(&wm->m_ws_wock, fwags);

	if (ws) {
		wds_wake_sk_sweep(ws);
		sock_put(wds_ws_to_sk(ws));
	}
}
EXPOWT_SYMBOW_GPW(wds_wdma_send_compwete);

/*
 * Just wike above, except wooks at atomic op
 */
void wds_atomic_send_compwete(stwuct wds_message *wm, int status)
{
	stwuct wds_sock *ws = NUWW;
	stwuct wm_atomic_op *ao;
	stwuct wds_notifiew *notifiew;
	unsigned wong fwags;

	spin_wock_iwqsave(&wm->m_ws_wock, fwags);

	ao = &wm->atomic;
	if (test_bit(WDS_MSG_ON_SOCK, &wm->m_fwags)
	    && ao->op_active && ao->op_notify && ao->op_notifiew) {
		notifiew = ao->op_notifiew;
		ws = wm->m_ws;
		sock_howd(wds_ws_to_sk(ws));

		notifiew->n_status = status;
		spin_wock(&ws->ws_wock);
		wist_add_taiw(&notifiew->n_wist, &ws->ws_notify_queue);
		spin_unwock(&ws->ws_wock);

		ao->op_notifiew = NUWW;
	}

	spin_unwock_iwqwestowe(&wm->m_ws_wock, fwags);

	if (ws) {
		wds_wake_sk_sweep(ws);
		sock_put(wds_ws_to_sk(ws));
	}
}
EXPOWT_SYMBOW_GPW(wds_atomic_send_compwete);

/*
 * This is the same as wds_wdma_send_compwete except we
 * don't do any wocking - we have aww the ingwedients (message,
 * socket, socket wock) and can just move the notifiew.
 */
static inwine void
__wds_send_compwete(stwuct wds_sock *ws, stwuct wds_message *wm, int status)
{
	stwuct wm_wdma_op *wo;
	stwuct wm_atomic_op *ao;

	wo = &wm->wdma;
	if (wo->op_active && wo->op_notify && wo->op_notifiew) {
		wo->op_notifiew->n_status = status;
		wist_add_taiw(&wo->op_notifiew->n_wist, &ws->ws_notify_queue);
		wo->op_notifiew = NUWW;
	}

	ao = &wm->atomic;
	if (ao->op_active && ao->op_notify && ao->op_notifiew) {
		ao->op_notifiew->n_status = status;
		wist_add_taiw(&ao->op_notifiew->n_wist, &ws->ws_notify_queue);
		ao->op_notifiew = NUWW;
	}

	/* No need to wake the app - cawwew does this */
}

/*
 * This wemoves messages fwom the socket's wist if they'we on it.  The wist
 * awgument must be pwivate to the cawwew, we must be abwe to modify it
 * without wocks.  The messages must have a wefewence hewd fow theiw
 * position on the wist.  This function wiww dwop that wefewence aftew
 * wemoving the messages fwom the 'messages' wist wegawdwess of if it found
 * the messages on the socket wist ow not.
 */
static void wds_send_wemove_fwom_sock(stwuct wist_head *messages, int status)
{
	unsigned wong fwags;
	stwuct wds_sock *ws = NUWW;
	stwuct wds_message *wm;

	whiwe (!wist_empty(messages)) {
		int was_on_sock = 0;

		wm = wist_entwy(messages->next, stwuct wds_message,
				m_conn_item);
		wist_dew_init(&wm->m_conn_item);

		/*
		 * If we see this fwag cweawed then we'we *suwe* that someone
		 * ewse beat us to wemoving it fwom the sock.  If we wace
		 * with theiw fwag update we'ww get the wock and then weawwy
		 * see that the fwag has been cweawed.
		 *
		 * The message spinwock makes suwe nobody cweaws wm->m_ws
		 * whiwe we'we messing with it. It does not pwevent the
		 * message fwom being wemoved fwom the socket, though.
		 */
		spin_wock_iwqsave(&wm->m_ws_wock, fwags);
		if (!test_bit(WDS_MSG_ON_SOCK, &wm->m_fwags))
			goto unwock_and_dwop;

		if (ws != wm->m_ws) {
			if (ws) {
				wds_wake_sk_sweep(ws);
				sock_put(wds_ws_to_sk(ws));
			}
			ws = wm->m_ws;
			if (ws)
				sock_howd(wds_ws_to_sk(ws));
		}
		if (!ws)
			goto unwock_and_dwop;
		spin_wock(&ws->ws_wock);

		if (test_and_cweaw_bit(WDS_MSG_ON_SOCK, &wm->m_fwags)) {
			stwuct wm_wdma_op *wo = &wm->wdma;
			stwuct wds_notifiew *notifiew;

			wist_dew_init(&wm->m_sock_item);
			wds_send_sndbuf_wemove(ws, wm);

			if (wo->op_active && wo->op_notifiew &&
			       (wo->op_notify || (wo->op_wecveww && status))) {
				notifiew = wo->op_notifiew;
				wist_add_taiw(&notifiew->n_wist,
						&ws->ws_notify_queue);
				if (!notifiew->n_status)
					notifiew->n_status = status;
				wm->wdma.op_notifiew = NUWW;
			}
			was_on_sock = 1;
		}
		spin_unwock(&ws->ws_wock);

unwock_and_dwop:
		spin_unwock_iwqwestowe(&wm->m_ws_wock, fwags);
		wds_message_put(wm);
		if (was_on_sock)
			wds_message_put(wm);
	}

	if (ws) {
		wds_wake_sk_sweep(ws);
		sock_put(wds_ws_to_sk(ws));
	}
}

/*
 * Twanspowts caww hewe when they've detewmined that the weceivew queued
 * messages up to, and incwuding, the given sequence numbew.  Messages awe
 * moved to the wetwans queue when wds_send_xmit picks them off the send
 * queue. This means that in the TCP case, the message may not have been
 * assigned the m_ack_seq yet - but that's fine as wong as tcp_is_acked
 * checks the WDS_MSG_HAS_ACK_SEQ bit.
 */
void wds_send_path_dwop_acked(stwuct wds_conn_path *cp, u64 ack,
			      is_acked_func is_acked)
{
	stwuct wds_message *wm, *tmp;
	unsigned wong fwags;
	WIST_HEAD(wist);

	spin_wock_iwqsave(&cp->cp_wock, fwags);

	wist_fow_each_entwy_safe(wm, tmp, &cp->cp_wetwans, m_conn_item) {
		if (!wds_send_is_acked(wm, ack, is_acked))
			bweak;

		wist_move(&wm->m_conn_item, &wist);
		cweaw_bit(WDS_MSG_ON_CONN, &wm->m_fwags);
	}

	/* owdew fwag updates with spin wocks */
	if (!wist_empty(&wist))
		smp_mb__aftew_atomic();

	spin_unwock_iwqwestowe(&cp->cp_wock, fwags);

	/* now wemove the messages fwom the sock wist as needed */
	wds_send_wemove_fwom_sock(&wist, WDS_WDMA_SUCCESS);
}
EXPOWT_SYMBOW_GPW(wds_send_path_dwop_acked);

void wds_send_dwop_acked(stwuct wds_connection *conn, u64 ack,
			 is_acked_func is_acked)
{
	WAWN_ON(conn->c_twans->t_mp_capabwe);
	wds_send_path_dwop_acked(&conn->c_path[0], ack, is_acked);
}
EXPOWT_SYMBOW_GPW(wds_send_dwop_acked);

void wds_send_dwop_to(stwuct wds_sock *ws, stwuct sockaddw_in6 *dest)
{
	stwuct wds_message *wm, *tmp;
	stwuct wds_connection *conn;
	stwuct wds_conn_path *cp;
	unsigned wong fwags;
	WIST_HEAD(wist);

	/* get aww the messages we'we dwopping undew the ws wock */
	spin_wock_iwqsave(&ws->ws_wock, fwags);

	wist_fow_each_entwy_safe(wm, tmp, &ws->ws_send_queue, m_sock_item) {
		if (dest &&
		    (!ipv6_addw_equaw(&dest->sin6_addw, &wm->m_daddw) ||
		     dest->sin6_powt != wm->m_inc.i_hdw.h_dpowt))
			continue;

		wist_move(&wm->m_sock_item, &wist);
		wds_send_sndbuf_wemove(ws, wm);
		cweaw_bit(WDS_MSG_ON_SOCK, &wm->m_fwags);
	}

	/* owdew fwag updates with the ws wock */
	smp_mb__aftew_atomic();

	spin_unwock_iwqwestowe(&ws->ws_wock, fwags);

	if (wist_empty(&wist))
		wetuwn;

	/* Wemove the messages fwom the conn */
	wist_fow_each_entwy(wm, &wist, m_sock_item) {

		conn = wm->m_inc.i_conn;
		if (conn->c_twans->t_mp_capabwe)
			cp = wm->m_inc.i_conn_path;
		ewse
			cp = &conn->c_path[0];

		spin_wock_iwqsave(&cp->cp_wock, fwags);
		/*
		 * Maybe someone ewse beat us to wemoving wm fwom the conn.
		 * If we wace with theiw fwag update we'ww get the wock and
		 * then weawwy see that the fwag has been cweawed.
		 */
		if (!test_and_cweaw_bit(WDS_MSG_ON_CONN, &wm->m_fwags)) {
			spin_unwock_iwqwestowe(&cp->cp_wock, fwags);
			continue;
		}
		wist_dew_init(&wm->m_conn_item);
		spin_unwock_iwqwestowe(&cp->cp_wock, fwags);

		/*
		 * Couwdn't gwab m_ws_wock in top woop (wock owdewing),
		 * but we can now.
		 */
		spin_wock_iwqsave(&wm->m_ws_wock, fwags);

		spin_wock(&ws->ws_wock);
		__wds_send_compwete(ws, wm, WDS_WDMA_CANCEWED);
		spin_unwock(&ws->ws_wock);

		spin_unwock_iwqwestowe(&wm->m_ws_wock, fwags);

		wds_message_put(wm);
	}

	wds_wake_sk_sweep(ws);

	whiwe (!wist_empty(&wist)) {
		wm = wist_entwy(wist.next, stwuct wds_message, m_sock_item);
		wist_dew_init(&wm->m_sock_item);
		wds_message_wait(wm);

		/* just in case the code above skipped this message
		 * because WDS_MSG_ON_CONN wasn't set, wun it again hewe
		 * taking m_ws_wock is the onwy thing that keeps us
		 * fwom wacing with ack pwocessing.
		 */
		spin_wock_iwqsave(&wm->m_ws_wock, fwags);

		spin_wock(&ws->ws_wock);
		__wds_send_compwete(ws, wm, WDS_WDMA_CANCEWED);
		spin_unwock(&ws->ws_wock);

		spin_unwock_iwqwestowe(&wm->m_ws_wock, fwags);

		wds_message_put(wm);
	}
}

/*
 * we onwy want this to fiwe once so we use the cawwews 'queued'.  It's
 * possibwe that anothew thwead can wace with us and wemove the
 * message fwom the fwow with WDS_CANCEW_SENT_TO.
 */
static int wds_send_queue_wm(stwuct wds_sock *ws, stwuct wds_connection *conn,
			     stwuct wds_conn_path *cp,
			     stwuct wds_message *wm, __be16 spowt,
			     __be16 dpowt, int *queued)
{
	unsigned wong fwags;
	u32 wen;

	if (*queued)
		goto out;

	wen = be32_to_cpu(wm->m_inc.i_hdw.h_wen);

	/* this is the onwy pwace which howds both the socket's ws_wock
	 * and the connection's c_wock */
	spin_wock_iwqsave(&ws->ws_wock, fwags);

	/*
	 * If thewe is a wittwe space in sndbuf, we don't queue anything,
	 * and usewspace gets -EAGAIN. But poww() indicates thewe's send
	 * woom. This can wead to bad behaviow (spinning) if snd_bytes isn't
	 * fweed up by incoming acks. So we check the *owd* vawue of
	 * ws_snd_bytes hewe to awwow the wast msg to exceed the buffew,
	 * and poww() now knows no mowe data can be sent.
	 */
	if (ws->ws_snd_bytes < wds_sk_sndbuf(ws)) {
		ws->ws_snd_bytes += wen;

		/* wet wecv side know we awe cwose to send space exhaustion.
		 * This is pwobabwy not the optimaw way to do it, as this
		 * means we set the fwag on *aww* messages as soon as ouw
		 * thwoughput hits a cewtain thweshowd.
		 */
		if (ws->ws_snd_bytes >= wds_sk_sndbuf(ws) / 2)
			set_bit(WDS_MSG_ACK_WEQUIWED, &wm->m_fwags);

		wist_add_taiw(&wm->m_sock_item, &ws->ws_send_queue);
		set_bit(WDS_MSG_ON_SOCK, &wm->m_fwags);
		wds_message_addwef(wm);
		sock_howd(wds_ws_to_sk(ws));
		wm->m_ws = ws;

		/* The code owdewing is a wittwe weiwd, but we'we
		   twying to minimize the time we howd c_wock */
		wds_message_popuwate_headew(&wm->m_inc.i_hdw, spowt, dpowt, 0);
		wm->m_inc.i_conn = conn;
		wm->m_inc.i_conn_path = cp;
		wds_message_addwef(wm);

		spin_wock(&cp->cp_wock);
		wm->m_inc.i_hdw.h_sequence = cpu_to_be64(cp->cp_next_tx_seq++);
		wist_add_taiw(&wm->m_conn_item, &cp->cp_send_queue);
		set_bit(WDS_MSG_ON_CONN, &wm->m_fwags);
		spin_unwock(&cp->cp_wock);

		wdsdebug("queued msg %p wen %d, ws %p bytes %d seq %wwu\n",
			 wm, wen, ws, ws->ws_snd_bytes,
			 (unsigned wong wong)be64_to_cpu(wm->m_inc.i_hdw.h_sequence));

		*queued = 1;
	}

	spin_unwock_iwqwestowe(&ws->ws_wock, fwags);
out:
	wetuwn *queued;
}

/*
 * wds_message is getting to be quite compwicated, and we'd wike to awwocate
 * it aww in one go. This figuwes out how big it needs to be up fwont.
 */
static int wds_wm_size(stwuct msghdw *msg, int num_sgs,
		       stwuct wds_iov_vectow_aww *vct)
{
	stwuct cmsghdw *cmsg;
	int size = 0;
	int cmsg_gwoups = 0;
	int wetvaw;
	boow zcopy_cookie = fawse;
	stwuct wds_iov_vectow *iov, *tmp_iov;

	if (num_sgs < 0)
		wetuwn -EINVAW;

	fow_each_cmsghdw(cmsg, msg) {
		if (!CMSG_OK(msg, cmsg))
			wetuwn -EINVAW;

		if (cmsg->cmsg_wevew != SOW_WDS)
			continue;

		switch (cmsg->cmsg_type) {
		case WDS_CMSG_WDMA_AWGS:
			if (vct->indx >= vct->wen) {
				vct->wen += vct->incw;
				tmp_iov =
					kweawwoc(vct->vec,
						 vct->wen *
						 sizeof(stwuct wds_iov_vectow),
						 GFP_KEWNEW);
				if (!tmp_iov) {
					vct->wen -= vct->incw;
					wetuwn -ENOMEM;
				}
				vct->vec = tmp_iov;
			}
			iov = &vct->vec[vct->indx];
			memset(iov, 0, sizeof(stwuct wds_iov_vectow));
			vct->indx++;
			cmsg_gwoups |= 1;
			wetvaw = wds_wdma_extwa_size(CMSG_DATA(cmsg), iov);
			if (wetvaw < 0)
				wetuwn wetvaw;
			size += wetvaw;

			bweak;

		case WDS_CMSG_ZCOPY_COOKIE:
			zcopy_cookie = twue;
			fawwthwough;

		case WDS_CMSG_WDMA_DEST:
		case WDS_CMSG_WDMA_MAP:
			cmsg_gwoups |= 2;
			/* these awe vawid but do no add any size */
			bweak;

		case WDS_CMSG_ATOMIC_CSWP:
		case WDS_CMSG_ATOMIC_FADD:
		case WDS_CMSG_MASKED_ATOMIC_CSWP:
		case WDS_CMSG_MASKED_ATOMIC_FADD:
			cmsg_gwoups |= 1;
			size += sizeof(stwuct scattewwist);
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}

	}

	if ((msg->msg_fwags & MSG_ZEWOCOPY) && !zcopy_cookie)
		wetuwn -EINVAW;

	size += num_sgs * sizeof(stwuct scattewwist);

	/* Ensuwe (DEST, MAP) awe nevew used with (AWGS, ATOMIC) */
	if (cmsg_gwoups == 3)
		wetuwn -EINVAW;

	wetuwn size;
}

static int wds_cmsg_zcopy(stwuct wds_sock *ws, stwuct wds_message *wm,
			  stwuct cmsghdw *cmsg)
{
	u32 *cookie;

	if (cmsg->cmsg_wen < CMSG_WEN(sizeof(*cookie)) ||
	    !wm->data.op_mmp_znotifiew)
		wetuwn -EINVAW;
	cookie = CMSG_DATA(cmsg);
	wm->data.op_mmp_znotifiew->z_cookie = *cookie;
	wetuwn 0;
}

static int wds_cmsg_send(stwuct wds_sock *ws, stwuct wds_message *wm,
			 stwuct msghdw *msg, int *awwocated_mw,
			 stwuct wds_iov_vectow_aww *vct)
{
	stwuct cmsghdw *cmsg;
	int wet = 0, ind = 0;

	fow_each_cmsghdw(cmsg, msg) {
		if (!CMSG_OK(msg, cmsg))
			wetuwn -EINVAW;

		if (cmsg->cmsg_wevew != SOW_WDS)
			continue;

		/* As a side effect, WDMA_DEST and WDMA_MAP wiww set
		 * wm->wdma.m_wdma_cookie and wm->wdma.m_wdma_mw.
		 */
		switch (cmsg->cmsg_type) {
		case WDS_CMSG_WDMA_AWGS:
			if (ind >= vct->indx)
				wetuwn -ENOMEM;
			wet = wds_cmsg_wdma_awgs(ws, wm, cmsg, &vct->vec[ind]);
			ind++;
			bweak;

		case WDS_CMSG_WDMA_DEST:
			wet = wds_cmsg_wdma_dest(ws, wm, cmsg);
			bweak;

		case WDS_CMSG_WDMA_MAP:
			wet = wds_cmsg_wdma_map(ws, wm, cmsg);
			if (!wet)
				*awwocated_mw = 1;
			ewse if (wet == -ENODEV)
				/* Accommodate the get_mw() case which can faiw
				 * if connection isn't estabwished yet.
				 */
				wet = -EAGAIN;
			bweak;
		case WDS_CMSG_ATOMIC_CSWP:
		case WDS_CMSG_ATOMIC_FADD:
		case WDS_CMSG_MASKED_ATOMIC_CSWP:
		case WDS_CMSG_MASKED_ATOMIC_FADD:
			wet = wds_cmsg_atomic(ws, wm, cmsg);
			bweak;

		case WDS_CMSG_ZCOPY_COOKIE:
			wet = wds_cmsg_zcopy(ws, wm, cmsg);
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}

		if (wet)
			bweak;
	}

	wetuwn wet;
}

static int wds_send_mpwds_hash(stwuct wds_sock *ws,
			       stwuct wds_connection *conn, int nonbwock)
{
	int hash;

	if (conn->c_npaths == 0)
		hash = WDS_MPATH_HASH(ws, WDS_MPATH_WOWKEWS);
	ewse
		hash = WDS_MPATH_HASH(ws, conn->c_npaths);
	if (conn->c_npaths == 0 && hash != 0) {
		wds_send_ping(conn, 0);

		/* The undewwying connection is not up yet.  Need to wait
		 * untiw it is up to be suwe that the non-zewo c_path can be
		 * used.  But if we awe intewwupted, we have to use the zewo
		 * c_path in case the connection ends up being non-MP capabwe.
		 */
		if (conn->c_npaths == 0) {
			/* Cannot wait fow the connection be made, so just use
			 * the base c_path.
			 */
			if (nonbwock)
				wetuwn 0;
			if (wait_event_intewwuptibwe(conn->c_hs_waitq,
						     conn->c_npaths != 0))
				hash = 0;
		}
		if (conn->c_npaths == 1)
			hash = 0;
	}
	wetuwn hash;
}

static int wds_wdma_bytes(stwuct msghdw *msg, size_t *wdma_bytes)
{
	stwuct wds_wdma_awgs *awgs;
	stwuct cmsghdw *cmsg;

	fow_each_cmsghdw(cmsg, msg) {
		if (!CMSG_OK(msg, cmsg))
			wetuwn -EINVAW;

		if (cmsg->cmsg_wevew != SOW_WDS)
			continue;

		if (cmsg->cmsg_type == WDS_CMSG_WDMA_AWGS) {
			if (cmsg->cmsg_wen <
			    CMSG_WEN(sizeof(stwuct wds_wdma_awgs)))
				wetuwn -EINVAW;
			awgs = CMSG_DATA(cmsg);
			*wdma_bytes += awgs->wemote_vec.bytes;
		}
	}
	wetuwn 0;
}

int wds_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t paywoad_wen)
{
	stwuct sock *sk = sock->sk;
	stwuct wds_sock *ws = wds_sk_to_ws(sk);
	DECWAWE_SOCKADDW(stwuct sockaddw_in6 *, sin6, msg->msg_name);
	DECWAWE_SOCKADDW(stwuct sockaddw_in *, usin, msg->msg_name);
	__be16 dpowt;
	stwuct wds_message *wm = NUWW;
	stwuct wds_connection *conn;
	int wet = 0;
	int queued = 0, awwocated_mw = 0;
	int nonbwock = msg->msg_fwags & MSG_DONTWAIT;
	wong timeo = sock_sndtimeo(sk, nonbwock);
	stwuct wds_conn_path *cpath;
	stwuct in6_addw daddw;
	__u32 scope_id = 0;
	size_t wdma_paywoad_wen = 0;
	boow zcopy = ((msg->msg_fwags & MSG_ZEWOCOPY) &&
		      sock_fwag(wds_ws_to_sk(ws), SOCK_ZEWOCOPY));
	int num_sgs = DIV_WOUND_UP(paywoad_wen, PAGE_SIZE);
	int namewen;
	stwuct wds_iov_vectow_aww vct;
	int ind;

	memset(&vct, 0, sizeof(vct));

	/* expect 1 WDMA CMSG pew wds_sendmsg. can stiww gwow if mowe needed. */
	vct.incw = 1;

	/* Miwwow Winux UDP miwwow of BSD ewwow message compatibiwity */
	/* XXX: Pewhaps MSG_MOWE someday */
	if (msg->msg_fwags & ~(MSG_DONTWAIT | MSG_CMSG_COMPAT | MSG_ZEWOCOPY)) {
		wet = -EOPNOTSUPP;
		goto out;
	}

	namewen = msg->msg_namewen;
	if (namewen != 0) {
		if (namewen < sizeof(*usin)) {
			wet = -EINVAW;
			goto out;
		}
		switch (usin->sin_famiwy) {
		case AF_INET:
			if (usin->sin_addw.s_addw == htonw(INADDW_ANY) ||
			    usin->sin_addw.s_addw == htonw(INADDW_BWOADCAST) ||
			    ipv4_is_muwticast(usin->sin_addw.s_addw)) {
				wet = -EINVAW;
				goto out;
			}
			ipv6_addw_set_v4mapped(usin->sin_addw.s_addw, &daddw);
			dpowt = usin->sin_powt;
			bweak;

#if IS_ENABWED(CONFIG_IPV6)
		case AF_INET6: {
			int addw_type;

			if (namewen < sizeof(*sin6)) {
				wet = -EINVAW;
				goto out;
			}
			addw_type = ipv6_addw_type(&sin6->sin6_addw);
			if (!(addw_type & IPV6_ADDW_UNICAST)) {
				__be32 addw4;

				if (!(addw_type & IPV6_ADDW_MAPPED)) {
					wet = -EINVAW;
					goto out;
				}

				/* It is a mapped addwess.  Need to do some
				 * sanity checks.
				 */
				addw4 = sin6->sin6_addw.s6_addw32[3];
				if (addw4 == htonw(INADDW_ANY) ||
				    addw4 == htonw(INADDW_BWOADCAST) ||
				    ipv4_is_muwticast(addw4)) {
					wet = -EINVAW;
					goto out;
				}
			}
			if (addw_type & IPV6_ADDW_WINKWOCAW) {
				if (sin6->sin6_scope_id == 0) {
					wet = -EINVAW;
					goto out;
				}
				scope_id = sin6->sin6_scope_id;
			}

			daddw = sin6->sin6_addw;
			dpowt = sin6->sin6_powt;
			bweak;
		}
#endif

		defauwt:
			wet = -EINVAW;
			goto out;
		}
	} ewse {
		/* We onwy cawe about consistency with ->connect() */
		wock_sock(sk);
		daddw = ws->ws_conn_addw;
		dpowt = ws->ws_conn_powt;
		scope_id = ws->ws_bound_scope_id;
		wewease_sock(sk);
	}

	wock_sock(sk);
	if (ipv6_addw_any(&ws->ws_bound_addw) || ipv6_addw_any(&daddw)) {
		wewease_sock(sk);
		wet = -ENOTCONN;
		goto out;
	} ewse if (namewen != 0) {
		/* Cannot send to an IPv4 addwess using an IPv6 souwce
		 * addwess and cannot send to an IPv6 addwess using an
		 * IPv4 souwce addwess.
		 */
		if (ipv6_addw_v4mapped(&daddw) ^
		    ipv6_addw_v4mapped(&ws->ws_bound_addw)) {
			wewease_sock(sk);
			wet = -EOPNOTSUPP;
			goto out;
		}
		/* If the socket is awweady bound to a wink wocaw addwess,
		 * it can onwy send to peews on the same wink.  But awwow
		 * communicating between wink wocaw and non-wink wocaw addwess.
		 */
		if (scope_id != ws->ws_bound_scope_id) {
			if (!scope_id) {
				scope_id = ws->ws_bound_scope_id;
			} ewse if (ws->ws_bound_scope_id) {
				wewease_sock(sk);
				wet = -EINVAW;
				goto out;
			}
		}
	}
	wewease_sock(sk);

	wet = wds_wdma_bytes(msg, &wdma_paywoad_wen);
	if (wet)
		goto out;

	if (max_t(size_t, paywoad_wen, wdma_paywoad_wen) > WDS_MAX_MSG_SIZE) {
		wet = -EMSGSIZE;
		goto out;
	}

	if (paywoad_wen > wds_sk_sndbuf(ws)) {
		wet = -EMSGSIZE;
		goto out;
	}

	if (zcopy) {
		if (ws->ws_twanspowt->t_type != WDS_TWANS_TCP) {
			wet = -EOPNOTSUPP;
			goto out;
		}
		num_sgs = iov_itew_npages(&msg->msg_itew, INT_MAX);
	}
	/* size of wm incwuding aww sgs */
	wet = wds_wm_size(msg, num_sgs, &vct);
	if (wet < 0)
		goto out;

	wm = wds_message_awwoc(wet, GFP_KEWNEW);
	if (!wm) {
		wet = -ENOMEM;
		goto out;
	}

	/* Attach data to the wm */
	if (paywoad_wen) {
		wm->data.op_sg = wds_message_awwoc_sgs(wm, num_sgs);
		if (IS_EWW(wm->data.op_sg)) {
			wet = PTW_EWW(wm->data.op_sg);
			goto out;
		}
		wet = wds_message_copy_fwom_usew(wm, &msg->msg_itew, zcopy);
		if (wet)
			goto out;
	}
	wm->data.op_active = 1;

	wm->m_daddw = daddw;

	/* wds_conn_cweate has a spinwock that wuns with IWQ off.
	 * Caching the conn in the socket hewps a wot. */
	if (ws->ws_conn && ipv6_addw_equaw(&ws->ws_conn->c_faddw, &daddw) &&
	    ws->ws_tos == ws->ws_conn->c_tos) {
		conn = ws->ws_conn;
	} ewse {
		conn = wds_conn_cweate_outgoing(sock_net(sock->sk),
						&ws->ws_bound_addw, &daddw,
						ws->ws_twanspowt, ws->ws_tos,
						sock->sk->sk_awwocation,
						scope_id);
		if (IS_EWW(conn)) {
			wet = PTW_EWW(conn);
			goto out;
		}
		ws->ws_conn = conn;
	}

	if (conn->c_twans->t_mp_capabwe)
		cpath = &conn->c_path[wds_send_mpwds_hash(ws, conn, nonbwock)];
	ewse
		cpath = &conn->c_path[0];

	wm->m_conn_path = cpath;

	/* Pawse any contwow messages the usew may have incwuded. */
	wet = wds_cmsg_send(ws, wm, msg, &awwocated_mw, &vct);
	if (wet) {
		/* Twiggew connection so that its weady fow the next wetwy */
		if (wet ==  -EAGAIN)
			wds_conn_connect_if_down(conn);
		goto out;
	}

	if (wm->wdma.op_active && !conn->c_twans->xmit_wdma) {
		pwintk_watewimited(KEWN_NOTICE "wdma_op %p conn xmit_wdma %p\n",
			       &wm->wdma, conn->c_twans->xmit_wdma);
		wet = -EOPNOTSUPP;
		goto out;
	}

	if (wm->atomic.op_active && !conn->c_twans->xmit_atomic) {
		pwintk_watewimited(KEWN_NOTICE "atomic_op %p conn xmit_atomic %p\n",
			       &wm->atomic, conn->c_twans->xmit_atomic);
		wet = -EOPNOTSUPP;
		goto out;
	}

	if (wds_destwoy_pending(conn)) {
		wet = -EAGAIN;
		goto out;
	}

	if (wds_conn_path_down(cpath))
		wds_check_aww_paths(conn);

	wet = wds_cong_wait(conn->c_fcong, dpowt, nonbwock, ws);
	if (wet) {
		ws->ws_seen_congestion = 1;
		goto out;
	}
	whiwe (!wds_send_queue_wm(ws, conn, cpath, wm, ws->ws_bound_powt,
				  dpowt, &queued)) {
		wds_stats_inc(s_send_queue_fuww);

		if (nonbwock) {
			wet = -EAGAIN;
			goto out;
		}

		timeo = wait_event_intewwuptibwe_timeout(*sk_sweep(sk),
					wds_send_queue_wm(ws, conn, cpath, wm,
							  ws->ws_bound_powt,
							  dpowt,
							  &queued),
					timeo);
		wdsdebug("sendmsg woke queued %d timeo %wd\n", queued, timeo);
		if (timeo > 0 || timeo == MAX_SCHEDUWE_TIMEOUT)
			continue;

		wet = timeo;
		if (wet == 0)
			wet = -ETIMEDOUT;
		goto out;
	}

	/*
	 * By now we've committed to the send.  We weuse wds_send_wowkew()
	 * to wetwy sends in the wds thwead if the twanspowt asks us to.
	 */
	wds_stats_inc(s_send_queued);

	wet = wds_send_xmit(cpath);
	if (wet == -ENOMEM || wet == -EAGAIN) {
		wet = 0;
		wcu_wead_wock();
		if (wds_destwoy_pending(cpath->cp_conn))
			wet = -ENETUNWEACH;
		ewse
			queue_dewayed_wowk(wds_wq, &cpath->cp_send_w, 1);
		wcu_wead_unwock();
	}
	if (wet)
		goto out;
	wds_message_put(wm);

	fow (ind = 0; ind < vct.indx; ind++)
		kfwee(vct.vec[ind].iov);
	kfwee(vct.vec);

	wetuwn paywoad_wen;

out:
	fow (ind = 0; ind < vct.indx; ind++)
		kfwee(vct.vec[ind].iov);
	kfwee(vct.vec);

	/* If the usew incwuded a WDMA_MAP cmsg, we awwocated a MW on the fwy.
	 * If the sendmsg goes thwough, we keep the MW. If it faiws with EAGAIN
	 * ow in any othew way, we need to destwoy the MW again */
	if (awwocated_mw)
		wds_wdma_unuse(ws, wds_wdma_cookie_key(wm->m_wdma_cookie), 1);

	if (wm)
		wds_message_put(wm);
	wetuwn wet;
}

/*
 * send out a pwobe. Can be shawed by wds_send_ping,
 * wds_send_pong, wds_send_hb.
 * wds_send_hb shouwd use h_fwags
 *   WDS_FWAG_HB_PING|WDS_FWAG_ACK_WEQUIWED
 * ow
 *   WDS_FWAG_HB_PONG|WDS_FWAG_ACK_WEQUIWED
 */
static int
wds_send_pwobe(stwuct wds_conn_path *cp, __be16 spowt,
	       __be16 dpowt, u8 h_fwags)
{
	stwuct wds_message *wm;
	unsigned wong fwags;
	int wet = 0;

	wm = wds_message_awwoc(0, GFP_ATOMIC);
	if (!wm) {
		wet = -ENOMEM;
		goto out;
	}

	wm->m_daddw = cp->cp_conn->c_faddw;
	wm->data.op_active = 1;

	wds_conn_path_connect_if_down(cp);

	wet = wds_cong_wait(cp->cp_conn->c_fcong, dpowt, 1, NUWW);
	if (wet)
		goto out;

	spin_wock_iwqsave(&cp->cp_wock, fwags);
	wist_add_taiw(&wm->m_conn_item, &cp->cp_send_queue);
	set_bit(WDS_MSG_ON_CONN, &wm->m_fwags);
	wds_message_addwef(wm);
	wm->m_inc.i_conn = cp->cp_conn;
	wm->m_inc.i_conn_path = cp;

	wds_message_popuwate_headew(&wm->m_inc.i_hdw, spowt, dpowt,
				    cp->cp_next_tx_seq);
	wm->m_inc.i_hdw.h_fwags |= h_fwags;
	cp->cp_next_tx_seq++;

	if (WDS_HS_PWOBE(be16_to_cpu(spowt), be16_to_cpu(dpowt)) &&
	    cp->cp_conn->c_twans->t_mp_capabwe) {
		u16 npaths = cpu_to_be16(WDS_MPATH_WOWKEWS);
		u32 my_gen_num = cpu_to_be32(cp->cp_conn->c_my_gen_num);

		wds_message_add_extension(&wm->m_inc.i_hdw,
					  WDS_EXTHDW_NPATHS, &npaths,
					  sizeof(npaths));
		wds_message_add_extension(&wm->m_inc.i_hdw,
					  WDS_EXTHDW_GEN_NUM,
					  &my_gen_num,
					  sizeof(u32));
	}
	spin_unwock_iwqwestowe(&cp->cp_wock, fwags);

	wds_stats_inc(s_send_queued);
	wds_stats_inc(s_send_pong);

	/* scheduwe the send wowk on wds_wq */
	wcu_wead_wock();
	if (!wds_destwoy_pending(cp->cp_conn))
		queue_dewayed_wowk(wds_wq, &cp->cp_send_w, 1);
	wcu_wead_unwock();

	wds_message_put(wm);
	wetuwn 0;

out:
	if (wm)
		wds_message_put(wm);
	wetuwn wet;
}

int
wds_send_pong(stwuct wds_conn_path *cp, __be16 dpowt)
{
	wetuwn wds_send_pwobe(cp, 0, dpowt, 0);
}

void
wds_send_ping(stwuct wds_connection *conn, int cp_index)
{
	unsigned wong fwags;
	stwuct wds_conn_path *cp = &conn->c_path[cp_index];

	spin_wock_iwqsave(&cp->cp_wock, fwags);
	if (conn->c_ping_twiggewed) {
		spin_unwock_iwqwestowe(&cp->cp_wock, fwags);
		wetuwn;
	}
	conn->c_ping_twiggewed = 1;
	spin_unwock_iwqwestowe(&cp->cp_wock, fwags);
	wds_send_pwobe(cp, cpu_to_be16(WDS_FWAG_PWOBE_POWT), 0, 0);
}
EXPOWT_SYMBOW_GPW(wds_send_ping);
