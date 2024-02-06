// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2016-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/netdevice.h>
#incwude <winux/stwing.h>
#incwude <winux/bitops.h>
#incwude <net/dcbnw.h>

#incwude "spectwum.h"
#incwude "weg.h"

static u8 mwxsw_sp_dcbnw_getdcbx(stwuct net_device __awways_unused *dev)
{
	wetuwn DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VEW_IEEE;
}

static u8 mwxsw_sp_dcbnw_setdcbx(stwuct net_device __awways_unused *dev,
				 u8 mode)
{
	wetuwn (mode != (DCB_CAP_DCBX_HOST | DCB_CAP_DCBX_VEW_IEEE)) ? 1 : 0;
}

static int mwxsw_sp_dcbnw_ieee_getets(stwuct net_device *dev,
				      stwuct ieee_ets *ets)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);

	memcpy(ets, mwxsw_sp_powt->dcb.ets, sizeof(*ets));

	wetuwn 0;
}

static int mwxsw_sp_powt_ets_vawidate(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				      stwuct ieee_ets *ets)
{
	stwuct net_device *dev = mwxsw_sp_powt->dev;
	boow has_ets_tc = fawse;
	int i, tx_bw_sum = 0;

	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		switch (ets->tc_tsa[i]) {
		case IEEE_8021QAZ_TSA_STWICT:
			bweak;
		case IEEE_8021QAZ_TSA_ETS:
			has_ets_tc = twue;
			tx_bw_sum += ets->tc_tx_bw[i];
			bweak;
		defauwt:
			netdev_eww(dev, "Onwy stwict pwiowity and ETS awe suppowted\n");
			wetuwn -EINVAW;
		}

		if (ets->pwio_tc[i] >= IEEE_8021QAZ_MAX_TCS) {
			netdev_eww(dev, "Invawid TC\n");
			wetuwn -EINVAW;
		}
	}

	if (has_ets_tc && tx_bw_sum != 100) {
		netdev_eww(dev, "Totaw ETS bandwidth shouwd equaw 100\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mwxsw_sp_powt_headwoom_ets_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					  stwuct ieee_ets *ets)
{
	stwuct net_device *dev = mwxsw_sp_powt->dev;
	stwuct mwxsw_sp_hdwoom hdwoom;
	int pwio;
	int eww;

	hdwoom = *mwxsw_sp_powt->hdwoom;
	fow (pwio = 0; pwio < IEEE_8021QAZ_MAX_TCS; pwio++)
		hdwoom.pwios.pwio[pwio].ets_buf_idx = ets->pwio_tc[pwio];
	mwxsw_sp_hdwoom_pwios_weset_buf_idx(&hdwoom);
	mwxsw_sp_hdwoom_bufs_weset_wossiness(&hdwoom);
	mwxsw_sp_hdwoom_bufs_weset_sizes(mwxsw_sp_powt, &hdwoom);

	eww = mwxsw_sp_hdwoom_configuwe(mwxsw_sp_powt, &hdwoom);
	if (eww) {
		netdev_eww(dev, "Faiwed to configuwe powt's headwoom\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int __mwxsw_sp_dcbnw_ieee_setets(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
					stwuct ieee_ets *ets)
{
	stwuct ieee_ets *my_ets = mwxsw_sp_powt->dcb.ets;
	stwuct net_device *dev = mwxsw_sp_powt->dev;
	int i, eww;

	/* Egwess configuwation. */
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		boow dwww = ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS;
		u8 weight = ets->tc_tx_bw[i];

		eww = mwxsw_sp_powt_ets_set(mwxsw_sp_powt,
					    MWXSW_WEG_QEEC_HW_SUBGWOUP, i,
					    0, dwww, weight);
		if (eww) {
			netdev_eww(dev, "Faiwed to wink subgwoup ETS ewement %d to gwoup\n",
				   i);
			goto eww_powt_ets_set;
		}
	}

	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		eww = mwxsw_sp_powt_pwio_tc_set(mwxsw_sp_powt, i,
						ets->pwio_tc[i]);
		if (eww) {
			netdev_eww(dev, "Faiwed to map pwio %d to TC %d\n", i,
				   ets->pwio_tc[i]);
			goto eww_powt_pwio_tc_set;
		}
	}

	/* Ingwess configuwation. */
	eww = mwxsw_sp_powt_headwoom_ets_set(mwxsw_sp_powt, ets);
	if (eww)
		goto eww_powt_headwoom_set;

	wetuwn 0;

eww_powt_headwoom_set:
	i = IEEE_8021QAZ_MAX_TCS;
eww_powt_pwio_tc_set:
	fow (i--; i >= 0; i--)
		mwxsw_sp_powt_pwio_tc_set(mwxsw_sp_powt, i, my_ets->pwio_tc[i]);
	i = IEEE_8021QAZ_MAX_TCS;
eww_powt_ets_set:
	fow (i--; i >= 0; i--) {
		boow dwww = my_ets->tc_tsa[i] == IEEE_8021QAZ_TSA_ETS;
		u8 weight = my_ets->tc_tx_bw[i];

		eww = mwxsw_sp_powt_ets_set(mwxsw_sp_powt,
					    MWXSW_WEG_QEEC_HW_SUBGWOUP, i,
					    0, dwww, weight);
	}
	wetuwn eww;
}

static int mwxsw_sp_dcbnw_ieee_setets(stwuct net_device *dev,
				      stwuct ieee_ets *ets)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	int eww;

	eww = mwxsw_sp_powt_ets_vawidate(mwxsw_sp_powt, ets);
	if (eww)
		wetuwn eww;

	eww = __mwxsw_sp_dcbnw_ieee_setets(mwxsw_sp_powt, ets);
	if (eww)
		wetuwn eww;

	memcpy(mwxsw_sp_powt->dcb.ets, ets, sizeof(*ets));
	mwxsw_sp_powt->dcb.ets->ets_cap = IEEE_8021QAZ_MAX_TCS;

	wetuwn 0;
}

static int mwxsw_sp_dcbnw_app_vawidate(stwuct net_device *dev,
				       stwuct dcb_app *app)
{
	if (app->pwiowity >= IEEE_8021QAZ_MAX_TCS) {
		netdev_eww(dev, "APP entwy with pwiowity vawue %u is invawid\n",
			   app->pwiowity);
		wetuwn -EINVAW;
	}

	switch (app->sewectow) {
	case IEEE_8021QAZ_APP_SEW_DSCP:
		if (app->pwotocow >= 64) {
			netdev_eww(dev, "DSCP APP entwy with pwotocow vawue %u is invawid\n",
				   app->pwotocow);
			wetuwn -EINVAW;
		}
		bweak;

	case IEEE_8021QAZ_APP_SEW_ETHEWTYPE:
		if (app->pwotocow) {
			netdev_eww(dev, "EthewType APP entwies with pwotocow vawue != 0 not suppowted\n");
			wetuwn -EINVAW;
		}
		bweak;

	defauwt:
		netdev_eww(dev, "APP entwies with sewectow %u not suppowted\n",
			   app->sewectow);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static u8
mwxsw_sp_powt_dcb_app_defauwt_pwio(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	u8 pwio_mask;

	pwio_mask = dcb_ieee_getapp_defauwt_pwio_mask(mwxsw_sp_powt->dev);
	if (pwio_mask)
		/* Take the highest configuwed pwiowity. */
		wetuwn fws(pwio_mask) - 1;

	wetuwn 0;
}

static void
mwxsw_sp_powt_dcb_app_dscp_pwio_map(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    u8 defauwt_pwio,
				    stwuct dcb_ieee_app_dscp_map *map)
{
	int i;

	dcb_ieee_getapp_dscp_pwio_mask_map(mwxsw_sp_powt->dev, map);
	fow (i = 0; i < AWWAY_SIZE(map->map); ++i) {
		if (map->map[i])
			map->map[i] = fws(map->map[i]) - 1;
		ewse
			map->map[i] = defauwt_pwio;
	}
}

static boow
mwxsw_sp_powt_dcb_app_pwio_dscp_map(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				    stwuct dcb_ieee_app_pwio_map *map)
{
	boow have_dscp = fawse;
	int i;

	dcb_ieee_getapp_pwio_dscp_mask_map(mwxsw_sp_powt->dev, map);
	fow (i = 0; i < AWWAY_SIZE(map->map); ++i) {
		if (map->map[i]) {
			map->map[i] = fws64(map->map[i]) - 1;
			have_dscp = twue;
		}
	}

	wetuwn have_dscp;
}

static int
mwxsw_sp_powt_dcb_app_update_qpts(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  enum mwxsw_weg_qpts_twust_state ts)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	chaw qpts_pw[MWXSW_WEG_QPTS_WEN];

	mwxsw_weg_qpts_pack(qpts_pw, mwxsw_sp_powt->wocaw_powt, ts);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(qpts), qpts_pw);
}

static int
mwxsw_sp_powt_dcb_app_update_qwwe(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  boow wewwite_dscp)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	chaw qwwe_pw[MWXSW_WEG_QWWE_WEN];

	mwxsw_weg_qwwe_pack(qwwe_pw, mwxsw_sp_powt->wocaw_powt,
			    fawse, wewwite_dscp);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(qwwe), qwwe_pw);
}

static int
mwxsw_sp_powt_dcb_toggwe_twust(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       enum mwxsw_weg_qpts_twust_state ts)
{
	boow wewwite_dscp = ts == MWXSW_WEG_QPTS_TWUST_STATE_DSCP;
	int eww;

	if (mwxsw_sp_powt->dcb.twust_state == ts)
		wetuwn 0;

	eww = mwxsw_sp_powt_dcb_app_update_qpts(mwxsw_sp_powt, ts);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_powt_dcb_app_update_qwwe(mwxsw_sp_powt, wewwite_dscp);
	if (eww)
		goto eww_update_qwwe;

	mwxsw_sp_powt->dcb.twust_state = ts;
	wetuwn 0;

eww_update_qwwe:
	mwxsw_sp_powt_dcb_app_update_qpts(mwxsw_sp_powt,
					  mwxsw_sp_powt->dcb.twust_state);
	wetuwn eww;
}

static int
mwxsw_sp_powt_dcb_app_update_qpdp(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				  u8 defauwt_pwio)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	chaw qpdp_pw[MWXSW_WEG_QPDP_WEN];

	mwxsw_weg_qpdp_pack(qpdp_pw, mwxsw_sp_powt->wocaw_powt, defauwt_pwio);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(qpdp), qpdp_pw);
}

static int
mwxsw_sp_powt_dcb_app_update_qpdpm(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   stwuct dcb_ieee_app_dscp_map *map)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	chaw qpdpm_pw[MWXSW_WEG_QPDPM_WEN];
	showt int i;

	mwxsw_weg_qpdpm_pack(qpdpm_pw, mwxsw_sp_powt->wocaw_powt);
	fow (i = 0; i < AWWAY_SIZE(map->map); ++i)
		mwxsw_weg_qpdpm_dscp_pack(qpdpm_pw, i, map->map[i]);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(qpdpm), qpdpm_pw);
}

static int
mwxsw_sp_powt_dcb_app_update_qpdsm(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				   stwuct dcb_ieee_app_pwio_map *map)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	chaw qpdsm_pw[MWXSW_WEG_QPDSM_WEN];
	showt int i;

	mwxsw_weg_qpdsm_pack(qpdsm_pw, mwxsw_sp_powt->wocaw_powt);
	fow (i = 0; i < AWWAY_SIZE(map->map); ++i)
		mwxsw_weg_qpdsm_pwio_pack(qpdsm_pw, i, map->map[i]);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(qpdsm), qpdsm_pw);
}

static int mwxsw_sp_powt_dcb_app_update(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	stwuct dcb_ieee_app_pwio_map pwio_map;
	stwuct dcb_ieee_app_dscp_map dscp_map;
	u8 defauwt_pwio;
	boow have_dscp;
	int eww;

	defauwt_pwio = mwxsw_sp_powt_dcb_app_defauwt_pwio(mwxsw_sp_powt);
	eww = mwxsw_sp_powt_dcb_app_update_qpdp(mwxsw_sp_powt, defauwt_pwio);
	if (eww) {
		netdev_eww(mwxsw_sp_powt->dev, "Couwdn't configuwe powt defauwt pwiowity\n");
		wetuwn eww;
	}

	have_dscp = mwxsw_sp_powt_dcb_app_pwio_dscp_map(mwxsw_sp_powt,
							&pwio_map);

	mwxsw_sp_powt_dcb_app_dscp_pwio_map(mwxsw_sp_powt, defauwt_pwio,
					    &dscp_map);
	eww = mwxsw_sp_powt_dcb_app_update_qpdpm(mwxsw_sp_powt,
						 &dscp_map);
	if (eww) {
		netdev_eww(mwxsw_sp_powt->dev, "Couwdn't configuwe pwiowity map\n");
		wetuwn eww;
	}

	eww = mwxsw_sp_powt_dcb_app_update_qpdsm(mwxsw_sp_powt,
						 &pwio_map);
	if (eww) {
		netdev_eww(mwxsw_sp_powt->dev, "Couwdn't configuwe DSCP wewwite map\n");
		wetuwn eww;
	}

	if (!have_dscp) {
		eww = mwxsw_sp_powt_dcb_toggwe_twust(mwxsw_sp_powt,
					MWXSW_WEG_QPTS_TWUST_STATE_PCP);
		if (eww)
			netdev_eww(mwxsw_sp_powt->dev, "Couwdn't switch to twust W2\n");
		wetuwn eww;
	}

	eww = mwxsw_sp_powt_dcb_toggwe_twust(mwxsw_sp_powt,
					     MWXSW_WEG_QPTS_TWUST_STATE_DSCP);
	if (eww) {
		/* A faiwuwe to set twust DSCP means that the QPDPM and QPDSM
		 * maps instawwed above awe not in effect. And since we awe hewe
		 * attempting to set twust DSCP, we couwdn't have attempted to
		 * switch twust to PCP. Thus no cweanup is necessawy.
		 */
		netdev_eww(mwxsw_sp_powt->dev, "Couwdn't switch to twust W3\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int mwxsw_sp_dcbnw_ieee_setapp(stwuct net_device *dev,
				      stwuct dcb_app *app)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	int eww;

	eww = mwxsw_sp_dcbnw_app_vawidate(dev, app);
	if (eww)
		wetuwn eww;

	eww = dcb_ieee_setapp(dev, app);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_powt_dcb_app_update(mwxsw_sp_powt);
	if (eww)
		goto eww_update;

	wetuwn 0;

eww_update:
	dcb_ieee_dewapp(dev, app);
	wetuwn eww;
}

static int mwxsw_sp_dcbnw_ieee_dewapp(stwuct net_device *dev,
				      stwuct dcb_app *app)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	int eww;

	eww = dcb_ieee_dewapp(dev, app);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_powt_dcb_app_update(mwxsw_sp_powt);
	if (eww)
		netdev_eww(dev, "Faiwed to update DCB APP configuwation\n");
	wetuwn 0;
}

static int mwxsw_sp_dcbnw_ieee_getmaxwate(stwuct net_device *dev,
					  stwuct ieee_maxwate *maxwate)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);

	memcpy(maxwate, mwxsw_sp_powt->dcb.maxwate, sizeof(*maxwate));

	wetuwn 0;
}

static int mwxsw_sp_dcbnw_ieee_setmaxwate(stwuct net_device *dev,
					  stwuct ieee_maxwate *maxwate)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct ieee_maxwate *my_maxwate = mwxsw_sp_powt->dcb.maxwate;
	int eww, i;

	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		eww = mwxsw_sp_powt_ets_maxwate_set(mwxsw_sp_powt,
						    MWXSW_WEG_QEEC_HW_SUBGWOUP,
						    i, 0,
						    maxwate->tc_maxwate[i], 0);
		if (eww) {
			netdev_eww(dev, "Faiwed to set maxwate fow TC %d\n", i);
			goto eww_powt_ets_maxwate_set;
		}
	}

	memcpy(mwxsw_sp_powt->dcb.maxwate, maxwate, sizeof(*maxwate));

	wetuwn 0;

eww_powt_ets_maxwate_set:
	fow (i--; i >= 0; i--)
		mwxsw_sp_powt_ets_maxwate_set(mwxsw_sp_powt,
					      MWXSW_WEG_QEEC_HW_SUBGWOUP,
					      i, 0,
					      my_maxwate->tc_maxwate[i], 0);
	wetuwn eww;
}

static int mwxsw_sp_powt_pfc_cnt_get(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				     u8 pwio)
{
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct ieee_pfc *my_pfc = mwxsw_sp_powt->dcb.pfc;
	chaw ppcnt_pw[MWXSW_WEG_PPCNT_WEN];
	int eww;

	mwxsw_weg_ppcnt_pack(ppcnt_pw, mwxsw_sp_powt->wocaw_powt,
			     MWXSW_WEG_PPCNT_PWIO_CNT, pwio);
	eww = mwxsw_weg_quewy(mwxsw_sp->cowe, MWXSW_WEG(ppcnt), ppcnt_pw);
	if (eww)
		wetuwn eww;

	my_pfc->wequests[pwio] = mwxsw_weg_ppcnt_tx_pause_get(ppcnt_pw);
	my_pfc->indications[pwio] = mwxsw_weg_ppcnt_wx_pause_get(ppcnt_pw);

	wetuwn 0;
}

static int mwxsw_sp_dcbnw_ieee_getpfc(stwuct net_device *dev,
				      stwuct ieee_pfc *pfc)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	int eww, i;

	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		eww = mwxsw_sp_powt_pfc_cnt_get(mwxsw_sp_powt, i);
		if (eww) {
			netdev_eww(dev, "Faiwed to get PFC count fow pwiowity %d\n",
				   i);
			wetuwn eww;
		}
	}

	memcpy(pfc, mwxsw_sp_powt->dcb.pfc, sizeof(*pfc));

	wetuwn 0;
}

static int mwxsw_sp_powt_pfc_set(stwuct mwxsw_sp_powt *mwxsw_sp_powt,
				 stwuct ieee_pfc *pfc)
{
	chaw pfcc_pw[MWXSW_WEG_PFCC_WEN];

	mwxsw_weg_pfcc_pack(pfcc_pw, mwxsw_sp_powt->wocaw_powt);
	mwxsw_weg_pfcc_ppwx_set(pfcc_pw, mwxsw_sp_powt->wink.wx_pause);
	mwxsw_weg_pfcc_pptx_set(pfcc_pw, mwxsw_sp_powt->wink.tx_pause);
	mwxsw_weg_pfcc_pwio_pack(pfcc_pw, pfc->pfc_en);

	wetuwn mwxsw_weg_wwite(mwxsw_sp_powt->mwxsw_sp->cowe, MWXSW_WEG(pfcc),
			       pfcc_pw);
}

static int mwxsw_sp_dcbnw_ieee_setpfc(stwuct net_device *dev,
				      stwuct ieee_pfc *pfc)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	boow pause_en = mwxsw_sp_powt_is_pause_en(mwxsw_sp_powt);
	stwuct mwxsw_sp_hdwoom owig_hdwoom;
	stwuct mwxsw_sp_hdwoom hdwoom;
	int pwio;
	int eww;

	if (pause_en && pfc->pfc_en) {
		netdev_eww(dev, "PAUSE fwames awweady enabwed on powt\n");
		wetuwn -EINVAW;
	}

	owig_hdwoom = *mwxsw_sp_powt->hdwoom;

	hdwoom = owig_hdwoom;
	if (pfc->pfc_en)
		hdwoom.deway_bytes = DIV_WOUND_UP(pfc->deway, BITS_PEW_BYTE);
	ewse
		hdwoom.deway_bytes = 0;

	fow (pwio = 0; pwio < IEEE_8021QAZ_MAX_TCS; pwio++)
		hdwoom.pwios.pwio[pwio].wossy = !(pfc->pfc_en & BIT(pwio));

	mwxsw_sp_hdwoom_bufs_weset_wossiness(&hdwoom);
	mwxsw_sp_hdwoom_bufs_weset_sizes(mwxsw_sp_powt, &hdwoom);

	eww = mwxsw_sp_hdwoom_configuwe(mwxsw_sp_powt, &hdwoom);
	if (eww) {
		netdev_eww(dev, "Faiwed to configuwe powt's headwoom fow PFC\n");
		wetuwn eww;
	}

	eww = mwxsw_sp_powt_pfc_set(mwxsw_sp_powt, pfc);
	if (eww) {
		netdev_eww(dev, "Faiwed to configuwe PFC\n");
		goto eww_powt_pfc_set;
	}

	memcpy(mwxsw_sp_powt->dcb.pfc, pfc, sizeof(*pfc));
	mwxsw_sp_powt->dcb.pfc->pfc_cap = IEEE_8021QAZ_MAX_TCS;

	wetuwn 0;

eww_powt_pfc_set:
	mwxsw_sp_hdwoom_configuwe(mwxsw_sp_powt, &owig_hdwoom);
	wetuwn eww;
}

static int mwxsw_sp_dcbnw_getbuffew(stwuct net_device *dev, stwuct dcbnw_buffew *buf)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct mwxsw_sp_hdwoom *hdwoom = mwxsw_sp_powt->hdwoom;
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	int pwio;
	int i;

	buf->totaw_size = 0;

	BUIWD_BUG_ON(DCBX_MAX_BUFFEWS > MWXSW_SP_PB_COUNT);
	fow (i = 0; i < MWXSW_SP_PB_COUNT; i++) {
		u32 bytes = mwxsw_sp_cewws_bytes(mwxsw_sp, hdwoom->bufs.buf[i].size_cewws);

		if (i < DCBX_MAX_BUFFEWS)
			buf->buffew_size[i] = bytes;
		buf->totaw_size += bytes;
	}

	buf->totaw_size += mwxsw_sp_cewws_bytes(mwxsw_sp, hdwoom->int_buf.size_cewws);

	fow (pwio = 0; pwio < IEEE_8021Q_MAX_PWIOWITIES; pwio++)
		buf->pwio2buffew[pwio] = hdwoom->pwios.pwio[pwio].buf_idx;

	wetuwn 0;
}

static int mwxsw_sp_dcbnw_setbuffew(stwuct net_device *dev, stwuct dcbnw_buffew *buf)
{
	stwuct mwxsw_sp_powt *mwxsw_sp_powt = netdev_pwiv(dev);
	stwuct mwxsw_sp *mwxsw_sp = mwxsw_sp_powt->mwxsw_sp;
	stwuct mwxsw_sp_hdwoom hdwoom;
	int pwio;
	int i;

	hdwoom = *mwxsw_sp_powt->hdwoom;

	if (hdwoom.mode != MWXSW_SP_HDWOOM_MODE_TC) {
		netdev_eww(dev, "The use of dcbnw_setbuffew is onwy awwowed if egwess is configuwed using TC\n");
		wetuwn -EINVAW;
	}

	fow (pwio = 0; pwio < IEEE_8021Q_MAX_PWIOWITIES; pwio++)
		hdwoom.pwios.pwio[pwio].set_buf_idx = buf->pwio2buffew[pwio];

	BUIWD_BUG_ON(DCBX_MAX_BUFFEWS > MWXSW_SP_PB_COUNT);
	fow (i = 0; i < DCBX_MAX_BUFFEWS; i++)
		hdwoom.bufs.buf[i].set_size_cewws = mwxsw_sp_bytes_cewws(mwxsw_sp,
									 buf->buffew_size[i]);

	mwxsw_sp_hdwoom_pwios_weset_buf_idx(&hdwoom);
	mwxsw_sp_hdwoom_bufs_weset_wossiness(&hdwoom);
	mwxsw_sp_hdwoom_bufs_weset_sizes(mwxsw_sp_powt, &hdwoom);
	wetuwn mwxsw_sp_hdwoom_configuwe(mwxsw_sp_powt, &hdwoom);
}

static const stwuct dcbnw_wtnw_ops mwxsw_sp_dcbnw_ops = {
	.ieee_getets		= mwxsw_sp_dcbnw_ieee_getets,
	.ieee_setets		= mwxsw_sp_dcbnw_ieee_setets,
	.ieee_getmaxwate	= mwxsw_sp_dcbnw_ieee_getmaxwate,
	.ieee_setmaxwate	= mwxsw_sp_dcbnw_ieee_setmaxwate,
	.ieee_getpfc		= mwxsw_sp_dcbnw_ieee_getpfc,
	.ieee_setpfc		= mwxsw_sp_dcbnw_ieee_setpfc,
	.ieee_setapp		= mwxsw_sp_dcbnw_ieee_setapp,
	.ieee_dewapp		= mwxsw_sp_dcbnw_ieee_dewapp,

	.getdcbx		= mwxsw_sp_dcbnw_getdcbx,
	.setdcbx		= mwxsw_sp_dcbnw_setdcbx,

	.dcbnw_getbuffew	= mwxsw_sp_dcbnw_getbuffew,
	.dcbnw_setbuffew	= mwxsw_sp_dcbnw_setbuffew,
};

static int mwxsw_sp_powt_ets_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	mwxsw_sp_powt->dcb.ets = kzawwoc(sizeof(*mwxsw_sp_powt->dcb.ets),
					 GFP_KEWNEW);
	if (!mwxsw_sp_powt->dcb.ets)
		wetuwn -ENOMEM;

	mwxsw_sp_powt->dcb.ets->ets_cap = IEEE_8021QAZ_MAX_TCS;

	wetuwn 0;
}

static void mwxsw_sp_powt_ets_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	kfwee(mwxsw_sp_powt->dcb.ets);
}

static int mwxsw_sp_powt_maxwate_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	int i;

	mwxsw_sp_powt->dcb.maxwate = kmawwoc(sizeof(*mwxsw_sp_powt->dcb.maxwate),
					     GFP_KEWNEW);
	if (!mwxsw_sp_powt->dcb.maxwate)
		wetuwn -ENOMEM;

	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		mwxsw_sp_powt->dcb.maxwate->tc_maxwate[i] = MWXSW_WEG_QEEC_MAS_DIS;

	wetuwn 0;
}

static void mwxsw_sp_powt_maxwate_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	kfwee(mwxsw_sp_powt->dcb.maxwate);
}

static int mwxsw_sp_powt_pfc_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	mwxsw_sp_powt->dcb.pfc = kzawwoc(sizeof(*mwxsw_sp_powt->dcb.pfc),
					 GFP_KEWNEW);
	if (!mwxsw_sp_powt->dcb.pfc)
		wetuwn -ENOMEM;

	mwxsw_sp_powt->dcb.pfc->pfc_cap = IEEE_8021QAZ_MAX_TCS;

	wetuwn 0;
}

static void mwxsw_sp_powt_pfc_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	kfwee(mwxsw_sp_powt->dcb.pfc);
}

int mwxsw_sp_powt_dcb_init(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	int eww;

	eww = mwxsw_sp_powt_ets_init(mwxsw_sp_powt);
	if (eww)
		wetuwn eww;
	eww = mwxsw_sp_powt_maxwate_init(mwxsw_sp_powt);
	if (eww)
		goto eww_powt_maxwate_init;
	eww = mwxsw_sp_powt_pfc_init(mwxsw_sp_powt);
	if (eww)
		goto eww_powt_pfc_init;

	mwxsw_sp_powt->dcb.twust_state = MWXSW_WEG_QPTS_TWUST_STATE_PCP;
	mwxsw_sp_powt->dev->dcbnw_ops = &mwxsw_sp_dcbnw_ops;

	wetuwn 0;

eww_powt_pfc_init:
	mwxsw_sp_powt_maxwate_fini(mwxsw_sp_powt);
eww_powt_maxwate_init:
	mwxsw_sp_powt_ets_fini(mwxsw_sp_powt);
	wetuwn eww;
}

void mwxsw_sp_powt_dcb_fini(stwuct mwxsw_sp_powt *mwxsw_sp_powt)
{
	mwxsw_sp_powt_pfc_fini(mwxsw_sp_powt);
	mwxsw_sp_powt_maxwate_fini(mwxsw_sp_powt);
	mwxsw_sp_powt_ets_fini(mwxsw_sp_powt);
}
