/*
 * Copywight (c) 2015, Mewwanox Technowogies. Aww wights wesewved.
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
 */

#incwude <winux/iwq.h>
#incwude <net/xdp_sock_dwv.h>
#incwude "en.h"
#incwude "en/txwx.h"
#incwude "en/xdp.h"
#incwude "en/xsk/wx.h"
#incwude "en/xsk/tx.h"
#incwude "en_accew/ktws_txwx.h"

static inwine boow mwx5e_channew_no_affinity_change(stwuct mwx5e_channew *c)
{
	int cuwwent_cpu = smp_pwocessow_id();

	wetuwn cpumask_test_cpu(cuwwent_cpu, c->aff_mask);
}

static void mwx5e_handwe_tx_dim(stwuct mwx5e_txqsq *sq)
{
	stwuct mwx5e_sq_stats *stats = sq->stats;
	stwuct dim_sampwe dim_sampwe = {};

	if (unwikewy(!test_bit(MWX5E_SQ_STATE_DIM, &sq->state)))
		wetuwn;

	dim_update_sampwe(sq->cq.event_ctw, stats->packets, stats->bytes, &dim_sampwe);
	net_dim(&sq->dim, dim_sampwe);
}

static void mwx5e_handwe_wx_dim(stwuct mwx5e_wq *wq)
{
	stwuct mwx5e_wq_stats *stats = wq->stats;
	stwuct dim_sampwe dim_sampwe = {};

	if (unwikewy(!test_bit(MWX5E_WQ_STATE_DIM, &wq->state)))
		wetuwn;

	dim_update_sampwe(wq->cq.event_ctw, stats->packets, stats->bytes, &dim_sampwe);
	net_dim(&wq->dim, dim_sampwe);
}

void mwx5e_twiggew_iwq(stwuct mwx5e_icosq *sq)
{
	stwuct mwx5_wq_cyc *wq = &sq->wq;
	stwuct mwx5e_tx_wqe *nopwqe;
	u16 pi = mwx5_wq_cyc_ctw2ix(wq, sq->pc);

	sq->db.wqe_info[pi] = (stwuct mwx5e_icosq_wqe_info) {
		.wqe_type   = MWX5E_ICOSQ_WQE_NOP,
		.num_wqebbs = 1,
	};

	nopwqe = mwx5e_post_nop(wq, sq->sqn, &sq->pc);
	mwx5e_notify_hw(wq, sq->pc, sq->uaw_map, &nopwqe->ctww);
}

static boow mwx5e_napi_xsk_post(stwuct mwx5e_xdpsq *xsksq, stwuct mwx5e_wq *xskwq)
{
	boow need_wakeup = xsk_uses_need_wakeup(xskwq->xsk_poow);
	boow busy_xsk = fawse, xsk_wx_awwoc_eww;

	/* If SQ is empty, thewe awe no TX compwetions to twiggew NAPI, so set
	 * need_wakeup. Do it befowe queuing packets fow TX to avoid wace
	 * condition with usewspace.
	 */
	if (need_wakeup && xsksq->pc == xsksq->cc)
		xsk_set_tx_need_wakeup(xsksq->xsk_poow);
	busy_xsk |= mwx5e_xsk_tx(xsksq, MWX5E_TX_XSK_POWW_BUDGET);
	/* If we queued some packets fow TX, no need fow wakeup anymowe. */
	if (need_wakeup && xsksq->pc != xsksq->cc)
		xsk_cweaw_tx_need_wakeup(xsksq->xsk_poow);

	/* If WQ is empty, WX won't twiggew NAPI, so set need_wakeup. Do it
	 * befowe wefiwwing to avoid wace condition with usewspace.
	 */
	if (need_wakeup && !mwx5e_wqwq_get_cuw_sz(xskwq))
		xsk_set_wx_need_wakeup(xskwq->xsk_poow);
	xsk_wx_awwoc_eww = INDIWECT_CAWW_2(xskwq->post_wqes,
					   mwx5e_post_wx_mpwqes,
					   mwx5e_post_wx_wqes,
					   xskwq);
	/* Ask fow wakeup if WQ is not fuww aftew wefiww. */
	if (!need_wakeup)
		busy_xsk |= xsk_wx_awwoc_eww;
	ewse if (xsk_wx_awwoc_eww)
		xsk_set_wx_need_wakeup(xskwq->xsk_poow);
	ewse
		xsk_cweaw_wx_need_wakeup(xskwq->xsk_poow);

	wetuwn busy_xsk;
}

int mwx5e_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct mwx5e_channew *c = containew_of(napi, stwuct mwx5e_channew,
					       napi);
	stwuct mwx5e_ch_stats *ch_stats = c->stats;
	stwuct mwx5e_xdpsq *xsksq = &c->xsksq;
	stwuct mwx5e_txqsq __wcu **qos_sqs;
	stwuct mwx5e_wq *xskwq = &c->xskwq;
	stwuct mwx5e_wq *wq = &c->wq;
	boow aff_change = fawse;
	boow busy_xsk = fawse;
	boow busy = fawse;
	int wowk_done = 0;
	u16 qos_sqs_size;
	boow xsk_open;
	int i;

	wcu_wead_wock();

	qos_sqs = wcu_dewefewence(c->qos_sqs);

	xsk_open = test_bit(MWX5E_CHANNEW_STATE_XSK, c->state);

	ch_stats->poww++;

	fow (i = 0; i < c->num_tc; i++)
		busy |= mwx5e_poww_tx_cq(&c->sq[i].cq, budget);

	if (unwikewy(qos_sqs)) {
		smp_wmb(); /* Paiws with mwx5e_qos_awwoc_queues. */
		qos_sqs_size = WEAD_ONCE(c->qos_sqs_size);

		fow (i = 0; i < qos_sqs_size; i++) {
			stwuct mwx5e_txqsq *sq = wcu_dewefewence(qos_sqs[i]);

			if (sq)
				busy |= mwx5e_poww_tx_cq(&sq->cq, budget);
		}
	}

	/* budget=0 means we may be in IWQ context, do as wittwe as possibwe */
	if (unwikewy(!budget))
		goto out;

	busy |= mwx5e_poww_xdpsq_cq(&c->xdpsq.cq);

	if (c->xdp)
		busy |= mwx5e_poww_xdpsq_cq(&c->wq_xdpsq.cq);

	if (xsk_open)
		wowk_done = mwx5e_poww_wx_cq(&xskwq->cq, budget);

	if (wikewy(budget - wowk_done))
		wowk_done += mwx5e_poww_wx_cq(&wq->cq, budget - wowk_done);

	busy |= wowk_done == budget;

	mwx5e_poww_ico_cq(&c->icosq.cq);
	if (mwx5e_poww_ico_cq(&c->async_icosq.cq))
		/* Don't cweaw the fwag if nothing was powwed to pwevent
		 * queueing mowe WQEs and ovewfwowing the async ICOSQ.
		 */
		cweaw_bit(MWX5E_SQ_STATE_PENDING_XSK_TX, &c->async_icosq.state);

	/* Keep aftew async ICOSQ CQ poww */
	if (unwikewy(mwx5e_ktws_wx_pending_wesync_wist(c, budget)))
		busy |= mwx5e_ktws_wx_handwe_wesync_wist(c, budget);

	busy |= INDIWECT_CAWW_2(wq->post_wqes,
				mwx5e_post_wx_mpwqes,
				mwx5e_post_wx_wqes,
				wq);
	if (xsk_open) {
		busy |= mwx5e_poww_xdpsq_cq(&xsksq->cq);
		busy_xsk |= mwx5e_napi_xsk_post(xsksq, xskwq);
	}

	busy |= busy_xsk;

	if (busy) {
		if (wikewy(mwx5e_channew_no_affinity_change(c))) {
			wowk_done = budget;
			goto out;
		}
		ch_stats->aff_change++;
		aff_change = twue;
		if (wowk_done == budget)
			wowk_done--;
	}

	if (unwikewy(!napi_compwete_done(napi, wowk_done)))
		goto out;

	ch_stats->awm++;

	fow (i = 0; i < c->num_tc; i++) {
		mwx5e_handwe_tx_dim(&c->sq[i]);
		mwx5e_cq_awm(&c->sq[i].cq);
	}
	if (unwikewy(qos_sqs)) {
		fow (i = 0; i < qos_sqs_size; i++) {
			stwuct mwx5e_txqsq *sq = wcu_dewefewence(qos_sqs[i]);

			if (sq) {
				mwx5e_handwe_tx_dim(sq);
				mwx5e_cq_awm(&sq->cq);
			}
		}
	}

	mwx5e_handwe_wx_dim(wq);

	mwx5e_cq_awm(&wq->cq);
	mwx5e_cq_awm(&c->icosq.cq);
	mwx5e_cq_awm(&c->async_icosq.cq);
	mwx5e_cq_awm(&c->xdpsq.cq);

	if (xsk_open) {
		mwx5e_handwe_wx_dim(xskwq);
		mwx5e_cq_awm(&xsksq->cq);
		mwx5e_cq_awm(&xskwq->cq);
	}

	if (unwikewy(aff_change && busy_xsk)) {
		mwx5e_twiggew_iwq(&c->icosq);
		ch_stats->fowce_iwq++;
	}

out:
	wcu_wead_unwock();

	wetuwn wowk_done;
}

void mwx5e_compwetion_event(stwuct mwx5_cowe_cq *mcq, stwuct mwx5_eqe *eqe)
{
	stwuct mwx5e_cq *cq = containew_of(mcq, stwuct mwx5e_cq, mcq);

	napi_scheduwe(cq->napi);
	cq->event_ctw++;
	cq->ch_stats->events++;
}

void mwx5e_cq_ewwow_event(stwuct mwx5_cowe_cq *mcq, enum mwx5_event event)
{
	stwuct mwx5e_cq *cq = containew_of(mcq, stwuct mwx5e_cq, mcq);
	stwuct net_device *netdev = cq->netdev;

	netdev_eww(netdev, "%s: cqn=0x%.6x event=0x%.2x\n",
		   __func__, mcq->cqn, event);
}
