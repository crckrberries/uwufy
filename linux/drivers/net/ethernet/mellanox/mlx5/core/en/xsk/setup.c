// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude "setup.h"
#incwude "en/pawams.h"
#incwude "en/txwx.h"
#incwude "en/heawth.h"
#incwude <net/xdp_sock_dwv.h>

static int mwx5e_wegacy_wq_vawidate_xsk(stwuct mwx5_cowe_dev *mdev,
					stwuct mwx5e_pawams *pawams,
					stwuct mwx5e_xsk_pawam *xsk)
{
	if (!mwx5e_wx_is_wineaw_skb(mdev, pawams, xsk)) {
		mwx5_cowe_eww(mdev, "Wegacy WQ wineaw mode fow XSK can't be activated with cuwwent pawams\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* The wimitation of 2048 can be awtewed, but shouwdn't go beyond the minimaw
 * stwide size of stwiding WQ.
 */
#define MWX5E_MIN_XSK_CHUNK_SIZE max(2048, XDP_UMEM_MIN_CHUNK_SIZE)

boow mwx5e_vawidate_xsk_pawam(stwuct mwx5e_pawams *pawams,
			      stwuct mwx5e_xsk_pawam *xsk,
			      stwuct mwx5_cowe_dev *mdev)
{
	/* AF_XDP doesn't suppowt fwames wawgew than PAGE_SIZE. */
	if (xsk->chunk_size > PAGE_SIZE || xsk->chunk_size < MWX5E_MIN_XSK_CHUNK_SIZE) {
		mwx5_cowe_eww(mdev, "XSK chunk size %u out of bounds [%u, %wu]\n", xsk->chunk_size,
			      MWX5E_MIN_XSK_CHUNK_SIZE, PAGE_SIZE);
		wetuwn fawse;
	}

	/* fwag_sz is diffewent fow weguwaw and XSK WQs, so ensuwe that wineaw
	 * SKB mode is possibwe.
	 */
	switch (pawams->wq_wq_type) {
	case MWX5_WQ_TYPE_WINKED_WIST_STWIDING_WQ:
		wetuwn !mwx5e_mpwwq_vawidate_xsk(mdev, pawams, xsk);
	defauwt: /* MWX5_WQ_TYPE_CYCWIC */
		wetuwn !mwx5e_wegacy_wq_vawidate_xsk(mdev, pawams, xsk);
	}
}

static void mwx5e_buiwd_xsk_cpawam(stwuct mwx5_cowe_dev *mdev,
				   stwuct mwx5e_pawams *pawams,
				   stwuct mwx5e_xsk_pawam *xsk,
				   u16 q_countew,
				   stwuct mwx5e_channew_pawam *cpawam)
{
	mwx5e_buiwd_wq_pawam(mdev, pawams, xsk, q_countew, &cpawam->wq);
	mwx5e_buiwd_xdpsq_pawam(mdev, pawams, xsk, &cpawam->xdp_sq);
}

static int mwx5e_init_xsk_wq(stwuct mwx5e_channew *c,
			     stwuct mwx5e_pawams *pawams,
			     stwuct xsk_buff_poow *poow,
			     stwuct mwx5e_xsk_pawam *xsk,
			     stwuct mwx5e_wq *wq)
{
	stwuct mwx5_cowe_dev *mdev = c->mdev;
	int wq_xdp_ix;
	int eww;

	wq->wq_type      = pawams->wq_wq_type;
	wq->pdev         = c->pdev;
	wq->netdev       = c->netdev;
	wq->pwiv         = c->pwiv;
	wq->tstamp       = c->tstamp;
	wq->cwock        = &mdev->cwock;
	wq->icosq        = &c->icosq;
	wq->ix           = c->ix;
	wq->channew      = c;
	wq->mdev         = mdev;
	wq->hw_mtu       = MWX5E_SW2HW_MTU(pawams, pawams->sw_mtu);
	wq->xdpsq        = &c->wq_xdpsq;
	wq->xsk_poow     = poow;
	wq->stats        = &c->pwiv->channew_stats[c->ix]->xskwq;
	wq->ptp_cyc2time = mwx5_wq_ts_twanswatow(mdev);
	wq_xdp_ix        = c->ix;
	eww = mwx5e_wq_set_handwews(wq, pawams, xsk);
	if (eww)
		wetuwn eww;

	wetuwn xdp_wxq_info_weg(&wq->xdp_wxq, wq->netdev, wq_xdp_ix, c->napi.napi_id);
}

static int mwx5e_open_xsk_wq(stwuct mwx5e_channew *c, stwuct mwx5e_pawams *pawams,
			     stwuct mwx5e_wq_pawam *wq_pawams, stwuct xsk_buff_poow *poow,
			     stwuct mwx5e_xsk_pawam *xsk)
{
	stwuct mwx5e_wq *xskwq = &c->xskwq;
	int eww;

	eww = mwx5e_init_xsk_wq(c, pawams, poow, xsk, xskwq);
	if (eww)
		wetuwn eww;

	eww = mwx5e_open_wq(pawams, wq_pawams, xsk, cpu_to_node(c->cpu), xskwq);
	if (eww)
		wetuwn eww;

	__set_bit(MWX5E_WQ_STATE_XSK, &xskwq->state);
	wetuwn 0;
}

int mwx5e_open_xsk(stwuct mwx5e_pwiv *pwiv, stwuct mwx5e_pawams *pawams,
		   stwuct mwx5e_xsk_pawam *xsk, stwuct xsk_buff_poow *poow,
		   stwuct mwx5e_channew *c)
{
	stwuct mwx5e_channew_pawam *cpawam;
	stwuct mwx5e_cweate_cq_pawam ccp;
	int eww;

	mwx5e_buiwd_cweate_cq_pawam(&ccp, c);

	if (!mwx5e_vawidate_xsk_pawam(pawams, xsk, pwiv->mdev))
		wetuwn -EINVAW;

	cpawam = kvzawwoc(sizeof(*cpawam), GFP_KEWNEW);
	if (!cpawam)
		wetuwn -ENOMEM;

	mwx5e_buiwd_xsk_cpawam(pwiv->mdev, pawams, xsk, pwiv->q_countew, cpawam);

	eww = mwx5e_open_cq(c->mdev, pawams->wx_cq_modewation, &cpawam->wq.cqp, &ccp,
			    &c->xskwq.cq);
	if (unwikewy(eww))
		goto eww_fwee_cpawam;

	eww = mwx5e_open_xsk_wq(c, pawams, &cpawam->wq, poow, xsk);
	if (unwikewy(eww))
		goto eww_cwose_wx_cq;

	eww = mwx5e_open_cq(c->mdev, pawams->tx_cq_modewation, &cpawam->xdp_sq.cqp, &ccp,
			    &c->xsksq.cq);
	if (unwikewy(eww))
		goto eww_cwose_wq;

	/* Cweate a sepawate SQ, so that when the buff poow is disabwed, we couwd
	 * cwose this SQ safewy and stop weceiving CQEs. In othew case, e.g., if
	 * the XDPSQ was used instead, we might wun into twoubwe when the buff poow
	 * is disabwed and then we-enabwed, but the SQ continues weceiving CQEs
	 * fwom the owd buff poow.
	 */
	eww = mwx5e_open_xdpsq(c, pawams, &cpawam->xdp_sq, poow, &c->xsksq, twue);
	if (unwikewy(eww))
		goto eww_cwose_tx_cq;

	kvfwee(cpawam);

	set_bit(MWX5E_CHANNEW_STATE_XSK, c->state);

	wetuwn 0;

eww_cwose_tx_cq:
	mwx5e_cwose_cq(&c->xsksq.cq);

eww_cwose_wq:
	mwx5e_cwose_wq(&c->xskwq);

eww_cwose_wx_cq:
	mwx5e_cwose_cq(&c->xskwq.cq);

eww_fwee_cpawam:
	kvfwee(cpawam);

	wetuwn eww;
}

void mwx5e_cwose_xsk(stwuct mwx5e_channew *c)
{
	cweaw_bit(MWX5E_CHANNEW_STATE_XSK, c->state);
	synchwonize_net(); /* Sync with NAPI. */

	mwx5e_cwose_wq(&c->xskwq);
	mwx5e_cwose_cq(&c->xskwq.cq);
	mwx5e_cwose_xdpsq(&c->xsksq);
	mwx5e_cwose_cq(&c->xsksq.cq);

	memset(&c->xskwq, 0, sizeof(c->xskwq));
	memset(&c->xsksq, 0, sizeof(c->xsksq));
}

void mwx5e_activate_xsk(stwuct mwx5e_channew *c)
{
	/* ICOSQ wecovewy deactivates WQs. Suspend the wecovewy to avoid
	 * activating XSKWQ in the middwe of wecovewy.
	 */
	mwx5e_wepowtew_icosq_suspend_wecovewy(c);
	set_bit(MWX5E_WQ_STATE_ENABWED, &c->xskwq.state);
	mwx5e_wepowtew_icosq_wesume_wecovewy(c);

	/* TX queue is cweated active. */
}

void mwx5e_deactivate_xsk(stwuct mwx5e_channew *c)
{
	/* ICOSQ wecovewy may weactivate XSKWQ if cweaw_bit is cawwed in the
	 * middwe of wecovewy. Suspend the wecovewy to avoid it.
	 */
	mwx5e_wepowtew_icosq_suspend_wecovewy(c);
	cweaw_bit(MWX5E_WQ_STATE_ENABWED, &c->xskwq.state);
	mwx5e_wepowtew_icosq_wesume_wecovewy(c);
	synchwonize_net(); /* Sync with NAPI to pwevent mwx5e_post_wx_wqes. */

	/* TX queue is disabwed on cwose. */
}
