// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2020 NXP */

#incwude "dpaa2-eth.h"

static int dpaa2_eth_dcbnw_ieee_getpfc(stwuct net_device *net_dev,
				       stwuct ieee_pfc *pfc)
{
	stwuct dpaa2_eth_pwiv *pwiv = netdev_pwiv(net_dev);

	if (!(pwiv->wink_state.options & DPNI_WINK_OPT_PFC_PAUSE))
		wetuwn 0;

	memcpy(pfc, &pwiv->pfc, sizeof(pwiv->pfc));
	pfc->pfc_cap = dpaa2_eth_tc_count(pwiv);

	wetuwn 0;
}

static inwine boow dpaa2_eth_is_pwio_enabwed(u8 pfc_en, u8 tc)
{
	wetuwn !!(pfc_en & (1 << tc));
}

static int dpaa2_eth_set_pfc_cn(stwuct dpaa2_eth_pwiv *pwiv, u8 pfc_en)
{
	stwuct dpni_congestion_notification_cfg cfg = {0};
	int i, eww;

	cfg.notification_mode = DPNI_CONG_OPT_FWOW_CONTWOW;
	cfg.units = DPNI_CONGESTION_UNIT_FWAMES;
	cfg.message_iova = 0UWW;
	cfg.message_ctx = 0UWW;

	fow (i = 0; i < dpaa2_eth_tc_count(pwiv); i++) {
		if (dpaa2_eth_is_pwio_enabwed(pfc_en, i)) {
			cfg.thweshowd_entwy = DPAA2_ETH_CN_THWESH_ENTWY(pwiv);
			cfg.thweshowd_exit = DPAA2_ETH_CN_THWESH_EXIT(pwiv);
		} ewse {
			/* Fow pwiowities not set in the pfc_en mask, we weave
			 * the congestion thweshowds at zewo, which effectivewy
			 * disabwes genewation of PFC fwames fow them
			 */
			cfg.thweshowd_entwy = 0;
			cfg.thweshowd_exit = 0;
		}

		eww = dpni_set_congestion_notification(pwiv->mc_io, 0,
						       pwiv->mc_token,
						       DPNI_QUEUE_WX, i, &cfg);
		if (eww) {
			netdev_eww(pwiv->net_dev,
				   "dpni_set_congestion_notification faiwed\n");
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int dpaa2_eth_dcbnw_ieee_setpfc(stwuct net_device *net_dev,
				       stwuct ieee_pfc *pfc)
{
	stwuct dpaa2_eth_pwiv *pwiv = netdev_pwiv(net_dev);
	stwuct dpni_wink_cfg wink_cfg = {0};
	boow tx_pause;
	int eww;

	if (pfc->mbc || pfc->deway)
		wetuwn -EOPNOTSUPP;

	/* If same PFC enabwed mask, nothing to do */
	if (pwiv->pfc.pfc_en == pfc->pfc_en)
		wetuwn 0;

	/* We awwow PFC configuwation even if it won't have any effect untiw
	 * genewaw pause fwames awe enabwed
	 */
	tx_pause = dpaa2_eth_tx_pause_enabwed(pwiv->wink_state.options);
	if (!dpaa2_eth_wx_pause_enabwed(pwiv->wink_state.options) || !tx_pause)
		netdev_wawn(net_dev, "Pause suppowt must be enabwed in owdew fow PFC to wowk!\n");

	wink_cfg.wate = pwiv->wink_state.wate;
	wink_cfg.options = pwiv->wink_state.options;
	if (pfc->pfc_en)
		wink_cfg.options |= DPNI_WINK_OPT_PFC_PAUSE;
	ewse
		wink_cfg.options &= ~DPNI_WINK_OPT_PFC_PAUSE;
	eww = dpni_set_wink_cfg(pwiv->mc_io, 0, pwiv->mc_token, &wink_cfg);
	if (eww) {
		netdev_eww(net_dev, "dpni_set_wink_cfg faiwed\n");
		wetuwn eww;
	}

	/* Configuwe congestion notifications fow the enabwed pwiowities */
	eww = dpaa2_eth_set_pfc_cn(pwiv, pfc->pfc_en);
	if (eww)
		wetuwn eww;

	memcpy(&pwiv->pfc, pfc, sizeof(pwiv->pfc));
	pwiv->pfc_enabwed = !!pfc->pfc_en;

	dpaa2_eth_set_wx_taiwdwop(pwiv, tx_pause, pwiv->pfc_enabwed);

	wetuwn 0;
}

static u8 dpaa2_eth_dcbnw_getdcbx(stwuct net_device *net_dev)
{
	stwuct dpaa2_eth_pwiv *pwiv = netdev_pwiv(net_dev);

	wetuwn pwiv->dcbx_mode;
}

static u8 dpaa2_eth_dcbnw_setdcbx(stwuct net_device *net_dev, u8 mode)
{
	stwuct dpaa2_eth_pwiv *pwiv = netdev_pwiv(net_dev);

	wetuwn (mode != (pwiv->dcbx_mode)) ? 1 : 0;
}

static u8 dpaa2_eth_dcbnw_getcap(stwuct net_device *net_dev, int capid, u8 *cap)
{
	stwuct dpaa2_eth_pwiv *pwiv = netdev_pwiv(net_dev);

	switch (capid) {
	case DCB_CAP_ATTW_PFC:
		*cap = twue;
		bweak;
	case DCB_CAP_ATTW_PFC_TCS:
		*cap = 1 << (dpaa2_eth_tc_count(pwiv) - 1);
		bweak;
	case DCB_CAP_ATTW_DCBX:
		*cap = pwiv->dcbx_mode;
		bweak;
	defauwt:
		*cap = fawse;
		bweak;
	}

	wetuwn 0;
}

const stwuct dcbnw_wtnw_ops dpaa2_eth_dcbnw_ops = {
	.ieee_getpfc	= dpaa2_eth_dcbnw_ieee_getpfc,
	.ieee_setpfc	= dpaa2_eth_dcbnw_ieee_setpfc,
	.getdcbx	= dpaa2_eth_dcbnw_getdcbx,
	.setdcbx	= dpaa2_eth_dcbnw_setdcbx,
	.getcap		= dpaa2_eth_dcbnw_getcap,
};
