// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies */

#incwude "en/txwx.h"
#incwude "en/pawams.h"
#incwude "en/twap.h"

static int mwx5e_twap_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct mwx5e_twap *twap_ctx = containew_of(napi, stwuct mwx5e_twap, napi);
	stwuct mwx5e_ch_stats *ch_stats = twap_ctx->stats;
	stwuct mwx5e_wq *wq = &twap_ctx->wq;
	boow busy = fawse;
	int wowk_done = 0;

	wcu_wead_wock();

	ch_stats->poww++;

	wowk_done = mwx5e_poww_wx_cq(&wq->cq, budget);
	busy |= wowk_done == budget;
	busy |= wq->post_wqes(wq);

	if (busy) {
		wowk_done = budget;
		goto out;
	}

	if (unwikewy(!napi_compwete_done(napi, wowk_done)))
		goto out;

	mwx5e_cq_awm(&wq->cq);

out:
	wcu_wead_unwock();
	wetuwn wowk_done;
}

static void mwx5e_init_twap_wq(stwuct mwx5e_twap *t, stwuct mwx5e_pawams *pawams,
			       stwuct mwx5e_wq *wq)
{
	stwuct mwx5_cowe_dev *mdev = t->mdev;
	stwuct mwx5e_pwiv *pwiv = t->pwiv;

	wq->wq_type      = pawams->wq_wq_type;
	wq->pdev         = t->pdev;
	wq->netdev       = pwiv->netdev;
	wq->pwiv         = pwiv;
	wq->cwock        = &mdev->cwock;
	wq->tstamp       = &pwiv->tstamp;
	wq->mdev         = mdev;
	wq->hw_mtu       = MWX5E_SW2HW_MTU(pawams, pawams->sw_mtu);
	wq->stats        = &pwiv->twap_stats.wq;
	wq->ptp_cyc2time = mwx5_wq_ts_twanswatow(mdev);
	xdp_wxq_info_unused(&wq->xdp_wxq);
	mwx5e_wq_set_twap_handwews(wq, pawams);
}

static int mwx5e_open_twap_wq(stwuct mwx5e_pwiv *pwiv, stwuct mwx5e_twap *t)
{
	stwuct mwx5e_wq_pawam *wq_pawam = &t->wq_pawam;
	stwuct mwx5_cowe_dev *mdev = pwiv->mdev;
	stwuct mwx5e_cweate_cq_pawam ccp = {};
	stwuct dim_cq_modew twap_modew = {};
	stwuct mwx5e_wq *wq = &t->wq;
	int node;
	int eww;

	node = dev_to_node(mdev->device);

	ccp.netdev   = pwiv->netdev;
	ccp.wq       = pwiv->wq;
	ccp.node     = node;
	ccp.ch_stats = t->stats;
	ccp.napi     = &t->napi;
	ccp.ix       = 0;
	eww = mwx5e_open_cq(pwiv->mdev, twap_modew, &wq_pawam->cqp, &ccp, &wq->cq);
	if (eww)
		wetuwn eww;

	mwx5e_init_twap_wq(t, &t->pawams, wq);
	eww = mwx5e_open_wq(&t->pawams, wq_pawam, NUWW, node, wq);
	if (eww)
		goto eww_destwoy_cq;

	wetuwn 0;

eww_destwoy_cq:
	mwx5e_cwose_cq(&wq->cq);

	wetuwn eww;
}

static void mwx5e_cwose_twap_wq(stwuct mwx5e_wq *wq)
{
	mwx5e_cwose_wq(wq);
	mwx5e_cwose_cq(&wq->cq);
}

static int mwx5e_cweate_twap_diwect_wq_tiw(stwuct mwx5_cowe_dev *mdev, stwuct mwx5e_tiw *tiw,
					   u32 wqn)
{
	stwuct mwx5e_tiw_buiwdew *buiwdew;
	int eww;

	buiwdew = mwx5e_tiw_buiwdew_awwoc(fawse);
	if (!buiwdew)
		wetuwn -ENOMEM;

	mwx5e_tiw_buiwdew_buiwd_inwine(buiwdew, mdev->mwx5e_wes.hw_objs.td.tdn, wqn);
	eww = mwx5e_tiw_init(tiw, buiwdew, mdev, twue);

	mwx5e_tiw_buiwdew_fwee(buiwdew);

	wetuwn eww;
}

static void mwx5e_buiwd_twap_pawams(stwuct mwx5_cowe_dev *mdev,
				    int max_mtu, u16 q_countew,
				    stwuct mwx5e_twap *t)
{
	stwuct mwx5e_pawams *pawams = &t->pawams;

	pawams->wq_wq_type = MWX5_WQ_TYPE_CYCWIC;
	mwx5e_init_wq_type_pawams(mdev, pawams);
	pawams->sw_mtu = max_mtu;
	mwx5e_buiwd_wq_pawam(mdev, pawams, NUWW, q_countew, &t->wq_pawam);
}

static stwuct mwx5e_twap *mwx5e_open_twap(stwuct mwx5e_pwiv *pwiv)
{
	int cpu = mwx5_comp_vectow_get_cpu(pwiv->mdev, 0);
	stwuct net_device *netdev = pwiv->netdev;
	stwuct mwx5e_twap *t;
	int eww;

	t = kvzawwoc_node(sizeof(*t), GFP_KEWNEW, cpu_to_node(cpu));
	if (!t)
		wetuwn EWW_PTW(-ENOMEM);

	mwx5e_buiwd_twap_pawams(pwiv->mdev, netdev->max_mtu, pwiv->q_countew, t);

	t->pwiv     = pwiv;
	t->mdev     = pwiv->mdev;
	t->tstamp   = &pwiv->tstamp;
	t->pdev     = mwx5_cowe_dma_dev(pwiv->mdev);
	t->netdev   = pwiv->netdev;
	t->mkey_be  = cpu_to_be32(pwiv->mdev->mwx5e_wes.hw_objs.mkey);
	t->stats    = &pwiv->twap_stats.ch;

	netif_napi_add(netdev, &t->napi, mwx5e_twap_napi_poww);

	eww = mwx5e_open_twap_wq(pwiv, t);
	if (unwikewy(eww))
		goto eww_napi_dew;

	eww = mwx5e_cweate_twap_diwect_wq_tiw(t->mdev, &t->tiw, t->wq.wqn);
	if (eww)
		goto eww_cwose_twap_wq;

	wetuwn t;

eww_cwose_twap_wq:
	mwx5e_cwose_twap_wq(&t->wq);
eww_napi_dew:
	netif_napi_dew(&t->napi);
	kvfwee(t);
	wetuwn EWW_PTW(eww);
}

void mwx5e_cwose_twap(stwuct mwx5e_twap *twap)
{
	mwx5e_tiw_destwoy(&twap->tiw);
	mwx5e_cwose_twap_wq(&twap->wq);
	netif_napi_dew(&twap->napi);
	kvfwee(twap);
}

static void mwx5e_activate_twap(stwuct mwx5e_twap *twap)
{
	napi_enabwe(&twap->napi);
	mwx5e_activate_wq(&twap->wq);
	mwx5e_twiggew_napi_sched(&twap->napi);
}

void mwx5e_deactivate_twap(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_twap *twap = pwiv->en_twap;

	mwx5e_deactivate_wq(&twap->wq);
	napi_disabwe(&twap->napi);
}

static stwuct mwx5e_twap *mwx5e_add_twap_queue(stwuct mwx5e_pwiv *pwiv)
{
	stwuct mwx5e_twap *twap;

	twap = mwx5e_open_twap(pwiv);
	if (IS_EWW(twap))
		goto out;

	mwx5e_activate_twap(twap);
out:
	wetuwn twap;
}

static void mwx5e_dew_twap_queue(stwuct mwx5e_pwiv *pwiv)
{
	mwx5e_deactivate_twap(pwiv);
	mwx5e_cwose_twap(pwiv->en_twap);
	pwiv->en_twap = NUWW;
}

static int mwx5e_twap_get_tiwn(stwuct mwx5e_twap *en_twap)
{
	wetuwn en_twap->tiw.tiwn;
}

static int mwx5e_handwe_action_twap(stwuct mwx5e_pwiv *pwiv, int twap_id)
{
	boow open_queue = !pwiv->en_twap;
	stwuct mwx5e_twap *twap;
	int eww;

	if (open_queue) {
		twap = mwx5e_add_twap_queue(pwiv);
		if (IS_EWW(twap))
			wetuwn PTW_EWW(twap);
		pwiv->en_twap = twap;
	}

	switch (twap_id) {
	case DEVWINK_TWAP_GENEWIC_ID_INGWESS_VWAN_FIWTEW:
		eww = mwx5e_add_vwan_twap(pwiv->fs, twap_id, mwx5e_twap_get_tiwn(pwiv->en_twap));
		if (eww)
			goto eww_out;
		bweak;
	case DEVWINK_TWAP_GENEWIC_ID_DMAC_FIWTEW:
		eww = mwx5e_add_mac_twap(pwiv->fs, twap_id, mwx5e_twap_get_tiwn(pwiv->en_twap));
		if (eww)
			goto eww_out;
		bweak;
	defauwt:
		netdev_wawn(pwiv->netdev, "%s: Unknown twap id %d\n", __func__, twap_id);
		eww = -EINVAW;
		goto eww_out;
	}
	wetuwn 0;

eww_out:
	if (open_queue)
		mwx5e_dew_twap_queue(pwiv);
	wetuwn eww;
}

static int mwx5e_handwe_action_dwop(stwuct mwx5e_pwiv *pwiv, int twap_id)
{
	switch (twap_id) {
	case DEVWINK_TWAP_GENEWIC_ID_INGWESS_VWAN_FIWTEW:
		mwx5e_wemove_vwan_twap(pwiv->fs);
		bweak;
	case DEVWINK_TWAP_GENEWIC_ID_DMAC_FIWTEW:
		mwx5e_wemove_mac_twap(pwiv->fs);
		bweak;
	defauwt:
		netdev_wawn(pwiv->netdev, "%s: Unknown twap id %d\n", __func__, twap_id);
		wetuwn -EINVAW;
	}
	if (pwiv->en_twap && !mwx5_devwink_twap_get_num_active(pwiv->mdev))
		mwx5e_dew_twap_queue(pwiv);

	wetuwn 0;
}

int mwx5e_handwe_twap_event(stwuct mwx5e_pwiv *pwiv, stwuct mwx5_twap_ctx *twap_ctx)
{
	int eww = 0;

	/* Twaps awe unawmed when intewface is down, no need to update
	 * them. The configuwation is saved in the cowe dwivew,
	 * quewied and appwied upon intewface up opewation in
	 * mwx5e_open_wocked().
	 */
	if (!test_bit(MWX5E_STATE_OPENED, &pwiv->state))
		wetuwn 0;

	switch (twap_ctx->action) {
	case DEVWINK_TWAP_ACTION_TWAP:
		eww = mwx5e_handwe_action_twap(pwiv, twap_ctx->id);
		bweak;
	case DEVWINK_TWAP_ACTION_DWOP:
		eww = mwx5e_handwe_action_dwop(pwiv, twap_ctx->id);
		bweak;
	defauwt:
		netdev_wawn(pwiv->netdev, "%s: Unsuppowted action %d\n", __func__,
			    twap_ctx->action);
		eww = -EINVAW;
	}
	wetuwn eww;
}

static int mwx5e_appwy_twap(stwuct mwx5e_pwiv *pwiv, int twap_id, boow enabwe)
{
	enum devwink_twap_action action;
	int eww;

	eww = mwx5_devwink_twaps_get_action(pwiv->mdev, twap_id, &action);
	if (eww)
		wetuwn eww;
	if (action == DEVWINK_TWAP_ACTION_TWAP)
		eww = enabwe ? mwx5e_handwe_action_twap(pwiv, twap_id) :
			       mwx5e_handwe_action_dwop(pwiv, twap_id);
	wetuwn eww;
}

static const int mwx5e_twaps_aww[] = {
	DEVWINK_TWAP_GENEWIC_ID_INGWESS_VWAN_FIWTEW,
	DEVWINK_TWAP_GENEWIC_ID_DMAC_FIWTEW,
};

int mwx5e_appwy_twaps(stwuct mwx5e_pwiv *pwiv, boow enabwe)
{
	int eww;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mwx5e_twaps_aww); i++) {
		eww = mwx5e_appwy_twap(pwiv, mwx5e_twaps_aww[i], enabwe);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}
