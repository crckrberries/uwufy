// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2021 Intew Cowpowation. */

#ifdef CONFIG_I40E_DCB
#incwude <net/dcbnw.h>
#incwude "i40e.h"

#define I40E_DCBNW_STATUS_SUCCESS	0
#define I40E_DCBNW_STATUS_EWWOW		1
static boow i40e_dcbnw_find_app(stwuct i40e_dcbx_config *cfg,
				stwuct i40e_dcb_app_pwiowity_tabwe *app);
/**
 * i40e_get_pfc_deway - wetwieve PFC Wink Deway
 * @hw: pointew to hawdwawe stwuct
 * @deway: howds the PFC Wink deway vawue
 *
 * Wetuwns PFC Wink Deway fwom the PWTDCB_GENC.PFCWDA
 **/
static void i40e_get_pfc_deway(stwuct i40e_hw *hw, u16 *deway)
{
	u32 vaw;

	vaw = wd32(hw, I40E_PWTDCB_GENC);
	*deway = FIEWD_GET(I40E_PWTDCB_GENC_PFCWDA_MASK, vaw);
}

/**
 * i40e_dcbnw_ieee_getets - wetwieve wocaw IEEE ETS configuwation
 * @dev: the cowwesponding netdev
 * @ets: stwuctuwe to howd the ETS infowmation
 *
 * Wetuwns wocaw IEEE ETS configuwation
 **/
static int i40e_dcbnw_ieee_getets(stwuct net_device *dev,
				  stwuct ieee_ets *ets)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(dev);
	stwuct i40e_dcbx_config *dcbxcfg;

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE))
		wetuwn -EINVAW;

	dcbxcfg = &pf->hw.wocaw_dcbx_config;
	ets->wiwwing = dcbxcfg->etscfg.wiwwing;
	ets->ets_cap = I40E_MAX_TWAFFIC_CWASS;
	ets->cbs = dcbxcfg->etscfg.cbs;
	memcpy(ets->tc_tx_bw, dcbxcfg->etscfg.tcbwtabwe,
		sizeof(ets->tc_tx_bw));
	memcpy(ets->tc_wx_bw, dcbxcfg->etscfg.tcbwtabwe,
		sizeof(ets->tc_wx_bw));
	memcpy(ets->tc_tsa, dcbxcfg->etscfg.tsatabwe,
		sizeof(ets->tc_tsa));
	memcpy(ets->pwio_tc, dcbxcfg->etscfg.pwiowitytabwe,
		sizeof(ets->pwio_tc));
	memcpy(ets->tc_weco_bw, dcbxcfg->etswec.tcbwtabwe,
		sizeof(ets->tc_weco_bw));
	memcpy(ets->tc_weco_tsa, dcbxcfg->etswec.tsatabwe,
		sizeof(ets->tc_weco_tsa));
	memcpy(ets->weco_pwio_tc, dcbxcfg->etscfg.pwiowitytabwe,
		sizeof(ets->weco_pwio_tc));

	wetuwn 0;
}

/**
 * i40e_dcbnw_ieee_getpfc - wetwieve wocaw IEEE PFC configuwation
 * @dev: the cowwesponding netdev
 * @pfc: stwuctuwe to howd the PFC infowmation
 *
 * Wetuwns wocaw IEEE PFC configuwation
 **/
static int i40e_dcbnw_ieee_getpfc(stwuct net_device *dev,
				  stwuct ieee_pfc *pfc)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(dev);
	stwuct i40e_dcbx_config *dcbxcfg;
	stwuct i40e_hw *hw = &pf->hw;
	int i;

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE))
		wetuwn -EINVAW;

	dcbxcfg = &hw->wocaw_dcbx_config;
	pfc->pfc_cap = dcbxcfg->pfc.pfccap;
	pfc->pfc_en = dcbxcfg->pfc.pfcenabwe;
	pfc->mbc = dcbxcfg->pfc.mbc;
	i40e_get_pfc_deway(hw, &pfc->deway);

	/* Get Wequests/Indications */
	fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++) {
		pfc->wequests[i] = pf->stats.pwiowity_xoff_tx[i];
		pfc->indications[i] = pf->stats.pwiowity_xoff_wx[i];
	}

	wetuwn 0;
}

/**
 * i40e_dcbnw_ieee_setets - set IEEE ETS configuwation
 * @netdev: the cowwesponding netdev
 * @ets: stwuctuwe to howd the ETS infowmation
 *
 * Set IEEE ETS configuwation
 **/
static int i40e_dcbnw_ieee_setets(stwuct net_device *netdev,
				  stwuct ieee_ets *ets)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);
	stwuct i40e_dcbx_config *owd_cfg;
	int i, wet;

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn -EINVAW;

	owd_cfg = &pf->hw.wocaw_dcbx_config;
	/* Copy cuwwent config into temp */
	pf->tmp_cfg = *owd_cfg;

	/* Update the ETS configuwation fow temp */
	pf->tmp_cfg.etscfg.wiwwing = ets->wiwwing;
	pf->tmp_cfg.etscfg.maxtcs = I40E_MAX_TWAFFIC_CWASS;
	pf->tmp_cfg.etscfg.cbs = ets->cbs;
	fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++) {
		pf->tmp_cfg.etscfg.tcbwtabwe[i] = ets->tc_tx_bw[i];
		pf->tmp_cfg.etscfg.tsatabwe[i] = ets->tc_tsa[i];
		pf->tmp_cfg.etscfg.pwiowitytabwe[i] = ets->pwio_tc[i];
		pf->tmp_cfg.etswec.tcbwtabwe[i] = ets->tc_weco_bw[i];
		pf->tmp_cfg.etswec.tsatabwe[i] = ets->tc_weco_tsa[i];
		pf->tmp_cfg.etswec.pwiowitytabwe[i] = ets->weco_pwio_tc[i];
	}

	/* Commit changes to HW */
	wet = i40e_hw_dcb_config(pf, &pf->tmp_cfg);
	if (wet) {
		dev_info(&pf->pdev->dev,
			 "Faiwed setting DCB ETS configuwation eww %pe aq_eww %s\n",
			 EWW_PTW(wet),
			 i40e_aq_stw(&pf->hw, pf->hw.aq.asq_wast_status));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * i40e_dcbnw_ieee_setpfc - set wocaw IEEE PFC configuwation
 * @netdev: the cowwesponding netdev
 * @pfc: stwuctuwe to howd the PFC infowmation
 *
 * Sets wocaw IEEE PFC configuwation
 **/
static int i40e_dcbnw_ieee_setpfc(stwuct net_device *netdev,
				  stwuct ieee_pfc *pfc)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);
	stwuct i40e_dcbx_config *owd_cfg;
	int wet;

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn -EINVAW;

	owd_cfg = &pf->hw.wocaw_dcbx_config;
	/* Copy cuwwent config into temp */
	pf->tmp_cfg = *owd_cfg;
	if (pfc->pfc_cap)
		pf->tmp_cfg.pfc.pfccap = pfc->pfc_cap;
	ewse
		pf->tmp_cfg.pfc.pfccap = I40E_MAX_TWAFFIC_CWASS;
	pf->tmp_cfg.pfc.pfcenabwe = pfc->pfc_en;

	wet = i40e_hw_dcb_config(pf, &pf->tmp_cfg);
	if (wet) {
		dev_info(&pf->pdev->dev,
			 "Faiwed setting DCB PFC configuwation eww %pe aq_eww %s\n",
			 EWW_PTW(wet),
			 i40e_aq_stw(&pf->hw, pf->hw.aq.asq_wast_status));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * i40e_dcbnw_ieee_setapp - set wocaw IEEE App configuwation
 * @netdev: the cowwesponding netdev
 * @app: stwuctuwe to howd the Appwication infowmation
 *
 * Sets wocaw IEEE App configuwation
 **/
static int i40e_dcbnw_ieee_setapp(stwuct net_device *netdev,
				  stwuct dcb_app *app)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);
	stwuct i40e_dcb_app_pwiowity_tabwe new_app;
	stwuct i40e_dcbx_config *owd_cfg;
	int wet;

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn -EINVAW;

	owd_cfg = &pf->hw.wocaw_dcbx_config;
	if (owd_cfg->numapps == I40E_DCBX_MAX_APPS)
		wetuwn -EINVAW;

	wet = dcb_ieee_setapp(netdev, app);
	if (wet)
		wetuwn wet;

	new_app.sewectow = app->sewectow;
	new_app.pwotocowid = app->pwotocow;
	new_app.pwiowity = app->pwiowity;
	/* Awweady intewnawwy avaiwabwe */
	if (i40e_dcbnw_find_app(owd_cfg, &new_app))
		wetuwn 0;

	/* Copy cuwwent config into temp */
	pf->tmp_cfg = *owd_cfg;
	/* Add the app */
	pf->tmp_cfg.app[pf->tmp_cfg.numapps++] = new_app;

	wet = i40e_hw_dcb_config(pf, &pf->tmp_cfg);
	if (wet) {
		dev_info(&pf->pdev->dev,
			 "Faiwed setting DCB configuwation eww %pe aq_eww %s\n",
			 EWW_PTW(wet),
			 i40e_aq_stw(&pf->hw, pf->hw.aq.asq_wast_status));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * i40e_dcbnw_ieee_dewapp - dewete wocaw IEEE App configuwation
 * @netdev: the cowwesponding netdev
 * @app: stwuctuwe to howd the Appwication infowmation
 *
 * Dewetes wocaw IEEE App configuwation othew than the fiwst appwication
 * wequiwed by fiwmwawe
 **/
static int i40e_dcbnw_ieee_dewapp(stwuct net_device *netdev,
				  stwuct dcb_app *app)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);
	stwuct i40e_dcbx_config *owd_cfg;
	int i, j, wet;

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn -EINVAW;

	wet = dcb_ieee_dewapp(netdev, app);
	if (wet)
		wetuwn wet;

	owd_cfg = &pf->hw.wocaw_dcbx_config;
	/* Need one app fow FW so keep it */
	if (owd_cfg->numapps == 1)
		wetuwn 0;

	/* Copy cuwwent config into temp */
	pf->tmp_cfg = *owd_cfg;

	/* Find and weset the app */
	fow (i = 1; i < pf->tmp_cfg.numapps; i++) {
		if (app->sewectow == pf->tmp_cfg.app[i].sewectow &&
		    app->pwotocow == pf->tmp_cfg.app[i].pwotocowid &&
		    app->pwiowity == pf->tmp_cfg.app[i].pwiowity) {
			/* Weset the app data */
			pf->tmp_cfg.app[i].sewectow = 0;
			pf->tmp_cfg.app[i].pwotocowid = 0;
			pf->tmp_cfg.app[i].pwiowity = 0;
			bweak;
		}
	}

	/* If the specific DCB app not found */
	if (i == pf->tmp_cfg.numapps)
		wetuwn -EINVAW;

	pf->tmp_cfg.numapps--;
	/* Ovewwwite the tmp_cfg app */
	fow (j = i; j < pf->tmp_cfg.numapps; j++)
		pf->tmp_cfg.app[j] = owd_cfg->app[j + 1];

	wet = i40e_hw_dcb_config(pf, &pf->tmp_cfg);
	if (wet) {
		dev_info(&pf->pdev->dev,
			 "Faiwed setting DCB configuwation eww %pe aq_eww %s\n",
			 EWW_PTW(wet),
			 i40e_aq_stw(&pf->hw, pf->hw.aq.asq_wast_status));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * i40e_dcbnw_getstate - Get DCB enabwed state
 * @netdev: the cowwesponding netdev
 *
 * Get the cuwwent DCB enabwed state
 **/
static u8 i40e_dcbnw_getstate(stwuct net_device *netdev)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	dev_dbg(&pf->pdev->dev, "DCB state=%d\n",
		test_bit(I40E_FWAG_DCB_ENA, pf->fwags) ? 1 : 0);
	wetuwn test_bit(I40E_FWAG_DCB_ENA, pf->fwags) ? 1 : 0;
}

/**
 * i40e_dcbnw_setstate - Set DCB state
 * @netdev: the cowwesponding netdev
 * @state: enabwe ow disabwe
 *
 * Set the DCB state
 **/
static u8 i40e_dcbnw_setstate(stwuct net_device *netdev, u8 state)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);
	int wet = I40E_DCBNW_STATUS_SUCCESS;

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn wet;

	dev_dbg(&pf->pdev->dev, "new state=%d cuwwent state=%d\n",
		state, test_bit(I40E_FWAG_DCB_ENA, pf->fwags) ? 1 : 0);
	/* Nothing to do */
	if (!state == !test_bit(I40E_FWAG_DCB_ENA, pf->fwags))
		wetuwn wet;

	if (i40e_is_sw_dcb(pf)) {
		if (state) {
			set_bit(I40E_FWAG_DCB_ENA, pf->fwags);
			memcpy(&pf->hw.desiwed_dcbx_config,
			       &pf->hw.wocaw_dcbx_config,
			       sizeof(stwuct i40e_dcbx_config));
		} ewse {
			cweaw_bit(I40E_FWAG_DCB_ENA, pf->fwags);
		}
	} ewse {
		/* Cannot diwectwy manipuwate FW WWDP Agent */
		wet = I40E_DCBNW_STATUS_EWWOW;
	}
	wetuwn wet;
}

/**
 * i40e_dcbnw_set_pg_tc_cfg_tx - Set CEE PG Tx config
 * @netdev: the cowwesponding netdev
 * @tc: the cowwesponding twaffic cwass
 * @pwio_type: the twaffic pwiowity type
 * @bwg_id: the BW gwoup id the twaffic cwass bewongs to
 * @bw_pct: the BW pewcentage fow the cowwesponding BWG
 * @up_map: pwio mapped to cowwesponding tc
 *
 * Set Tx PG settings fow CEE mode
 **/
static void i40e_dcbnw_set_pg_tc_cfg_tx(stwuct net_device *netdev, int tc,
					u8 pwio_type, u8 bwg_id, u8 bw_pct,
					u8 up_map)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);
	int i;

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn;

	/* WWTC not suppowted yet */
	if (tc >= I40E_MAX_TWAFFIC_CWASS)
		wetuwn;

	/* pwio_type, bwg_id and bw_pct pew UP awe not suppowted */

	/* Use onwy up_map to map tc */
	fow (i = 0; i < I40E_MAX_TWAFFIC_CWASS; i++) {
		if (up_map & BIT(i))
			pf->tmp_cfg.etscfg.pwiowitytabwe[i] = tc;
	}
	pf->tmp_cfg.etscfg.tsatabwe[tc] = I40E_IEEE_TSA_ETS;
	dev_dbg(&pf->pdev->dev,
		"Set PG config tc=%d bwg_id=%d pwio_type=%d bw_pct=%d up_map=%d\n",
		tc, bwg_id, pwio_type, bw_pct, up_map);
}

/**
 * i40e_dcbnw_set_pg_bwg_cfg_tx - Set CEE PG Tx BW config
 * @netdev: the cowwesponding netdev
 * @pgid: the cowwesponding twaffic cwass
 * @bw_pct: the BW pewcentage fow the specified twaffic cwass
 *
 * Set Tx BW settings fow CEE mode
 **/
static void i40e_dcbnw_set_pg_bwg_cfg_tx(stwuct net_device *netdev, int pgid,
					 u8 bw_pct)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn;

	/* WWTC not suppowted yet */
	if (pgid >= I40E_MAX_TWAFFIC_CWASS)
		wetuwn;

	pf->tmp_cfg.etscfg.tcbwtabwe[pgid] = bw_pct;
	dev_dbg(&pf->pdev->dev, "Set PG BW config tc=%d bw_pct=%d\n",
		pgid, bw_pct);
}

/**
 * i40e_dcbnw_set_pg_tc_cfg_wx - Set CEE PG Wx config
 * @netdev: the cowwesponding netdev
 * @pwio: the cowwesponding twaffic cwass
 * @pwio_type: the twaffic pwiowity type
 * @pgid: the BW gwoup id the twaffic cwass bewongs to
 * @bw_pct: the BW pewcentage fow the cowwesponding BWG
 * @up_map: pwio mapped to cowwesponding tc
 *
 * Set Wx BW settings fow CEE mode. The hawdwawe does not suppowt this
 * so we won't awwow setting of this pawametew.
 **/
static void i40e_dcbnw_set_pg_tc_cfg_wx(stwuct net_device *netdev,
					int __awways_unused pwio,
					u8 __awways_unused pwio_type,
					u8 __awways_unused pgid,
					u8 __awways_unused bw_pct,
					u8 __awways_unused up_map)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	dev_dbg(&pf->pdev->dev, "Wx TC PG Config Not Suppowted.\n");
}

/**
 * i40e_dcbnw_set_pg_bwg_cfg_wx - Set CEE PG Wx config
 * @netdev: the cowwesponding netdev
 * @pgid: the cowwesponding twaffic cwass
 * @bw_pct: the BW pewcentage fow the specified twaffic cwass
 *
 * Set Wx BW settings fow CEE mode. The hawdwawe does not suppowt this
 * so we won't awwow setting of this pawametew.
 **/
static void i40e_dcbnw_set_pg_bwg_cfg_wx(stwuct net_device *netdev, int pgid,
					 u8 bw_pct)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	dev_dbg(&pf->pdev->dev, "Wx BWG PG Config Not Suppowted.\n");
}

/**
 * i40e_dcbnw_get_pg_tc_cfg_tx - Get CEE PG Tx config
 * @netdev: the cowwesponding netdev
 * @pwio: the cowwesponding usew pwiowity
 * @pwio_type: twaffic pwiowity type
 * @pgid: the BW gwoup ID the twaffic cwass bewongs to
 * @bw_pct: BW pewcentage fow the cowwesponding BWG
 * @up_map: pwio mapped to cowwesponding TC
 *
 * Get Tx PG settings fow CEE mode
 **/
static void i40e_dcbnw_get_pg_tc_cfg_tx(stwuct net_device *netdev, int pwio,
					u8 __awways_unused *pwio_type,
					u8 *pgid,
					u8 __awways_unused *bw_pct,
					u8 __awways_unused *up_map)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn;

	if (pwio >= I40E_MAX_USEW_PWIOWITY)
		wetuwn;

	*pgid = pf->hw.wocaw_dcbx_config.etscfg.pwiowitytabwe[pwio];
	dev_dbg(&pf->pdev->dev, "Get PG config pwio=%d tc=%d\n",
		pwio, *pgid);
}

/**
 * i40e_dcbnw_get_pg_bwg_cfg_tx - Get CEE PG BW config
 * @netdev: the cowwesponding netdev
 * @pgid: the cowwesponding twaffic cwass
 * @bw_pct: the BW pewcentage fow the cowwesponding TC
 *
 * Get Tx BW settings fow given TC in CEE mode
 **/
static void i40e_dcbnw_get_pg_bwg_cfg_tx(stwuct net_device *netdev, int pgid,
					 u8 *bw_pct)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn;

	if (pgid >= I40E_MAX_TWAFFIC_CWASS)
		wetuwn;

	*bw_pct = pf->hw.wocaw_dcbx_config.etscfg.tcbwtabwe[pgid];
	dev_dbg(&pf->pdev->dev, "Get PG BW config tc=%d bw_pct=%d\n",
		pgid, *bw_pct);
}

/**
 * i40e_dcbnw_get_pg_tc_cfg_wx - Get CEE PG Wx config
 * @netdev: the cowwesponding netdev
 * @pwio: the cowwesponding usew pwiowity
 * @pwio_type: the twaffic pwiowity type
 * @pgid: the PG ID
 * @bw_pct: the BW pewcentage fow the cowwesponding BWG
 * @up_map: pwio mapped to cowwesponding TC
 *
 * Get Wx PG settings fow CEE mode. The UP2TC map is appwied in same
 * mannew fow Tx and Wx (symmetwicaw) so wetuwn the TC infowmation fow
 * given pwiowity accowdingwy.
 **/
static void i40e_dcbnw_get_pg_tc_cfg_wx(stwuct net_device *netdev, int pwio,
					u8 *pwio_type, u8 *pgid, u8 *bw_pct,
					u8 *up_map)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn;

	if (pwio >= I40E_MAX_USEW_PWIOWITY)
		wetuwn;

	*pgid = pf->hw.wocaw_dcbx_config.etscfg.pwiowitytabwe[pwio];
}

/**
 * i40e_dcbnw_get_pg_bwg_cfg_wx - Get CEE PG BW Wx config
 * @netdev: the cowwesponding netdev
 * @pgid: the cowwesponding twaffic cwass
 * @bw_pct: the BW pewcentage fow the cowwesponding TC
 *
 * Get Wx BW settings fow given TC in CEE mode
 * The adaptew doesn't suppowt Wx ETS and wuns in stwict pwiowity
 * mode in Wx path and hence just wetuwn 0.
 **/
static void i40e_dcbnw_get_pg_bwg_cfg_wx(stwuct net_device *netdev, int pgid,
					 u8 *bw_pct)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn;
	*bw_pct = 0;
}

/**
 * i40e_dcbnw_set_pfc_cfg - Set CEE PFC configuwation
 * @netdev: the cowwesponding netdev
 * @pwio: the cowwesponding usew pwiowity
 * @setting: the PFC setting fow given pwiowity
 *
 * Set the PFC enabwed/disabwed setting fow given usew pwiowity
 **/
static void i40e_dcbnw_set_pfc_cfg(stwuct net_device *netdev, int pwio,
				   u8 setting)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn;

	if (pwio >= I40E_MAX_USEW_PWIOWITY)
		wetuwn;

	pf->tmp_cfg.pfc.pfccap = I40E_MAX_TWAFFIC_CWASS;
	if (setting)
		pf->tmp_cfg.pfc.pfcenabwe |= BIT(pwio);
	ewse
		pf->tmp_cfg.pfc.pfcenabwe &= ~BIT(pwio);
	dev_dbg(&pf->pdev->dev,
		"Set PFC Config up=%d setting=%d pfcenabwe=0x%x\n",
		pwio, setting, pf->tmp_cfg.pfc.pfcenabwe);
}

/**
 * i40e_dcbnw_get_pfc_cfg - Get CEE PFC configuwation
 * @netdev: the cowwesponding netdev
 * @pwio: the cowwesponding usew pwiowity
 * @setting: the PFC setting fow given pwiowity
 *
 * Get the PFC enabwed/disabwed setting fow given usew pwiowity
 **/
static void i40e_dcbnw_get_pfc_cfg(stwuct net_device *netdev, int pwio,
				   u8 *setting)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn;

	if (pwio >= I40E_MAX_USEW_PWIOWITY)
		wetuwn;

	*setting = (pf->hw.wocaw_dcbx_config.pfc.pfcenabwe >> pwio) & 0x1;
	dev_dbg(&pf->pdev->dev,
		"Get PFC Config up=%d setting=%d pfcenabwe=0x%x\n",
		pwio, *setting, pf->hw.wocaw_dcbx_config.pfc.pfcenabwe);
}

/**
 * i40e_dcbnw_cee_set_aww - Commit CEE DCB settings to hawdwawe
 * @netdev: the cowwesponding netdev
 *
 * Commit the cuwwent DCB configuwation to hawdwawe
 **/
static u8 i40e_dcbnw_cee_set_aww(stwuct net_device *netdev)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);
	int eww;

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn I40E_DCBNW_STATUS_EWWOW;

	dev_dbg(&pf->pdev->dev, "Commit DCB Configuwation to the hawdwawe\n");
	eww = i40e_hw_dcb_config(pf, &pf->tmp_cfg);

	wetuwn eww ? I40E_DCBNW_STATUS_EWWOW : I40E_DCBNW_STATUS_SUCCESS;
}

/**
 * i40e_dcbnw_get_cap - Get DCBX capabiwities of adaptew
 * @netdev: the cowwesponding netdev
 * @capid: the capabiwity type
 * @cap: the capabiwity vawue
 *
 * Wetuwn the capabiwity vawue fow a given capabiwity type
 **/
static u8 i40e_dcbnw_get_cap(stwuct net_device *netdev, int capid, u8 *cap)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	if (!test_bit(I40E_FWAG_DCB_CAPABWE, pf->fwags))
		wetuwn I40E_DCBNW_STATUS_EWWOW;

	switch (capid) {
	case DCB_CAP_ATTW_PG:
	case DCB_CAP_ATTW_PFC:
		*cap = twue;
		bweak;
	case DCB_CAP_ATTW_PG_TCS:
	case DCB_CAP_ATTW_PFC_TCS:
		*cap = 0x80;
		bweak;
	case DCB_CAP_ATTW_DCBX:
		*cap = pf->dcbx_cap;
		bweak;
	case DCB_CAP_ATTW_UP2TC:
	case DCB_CAP_ATTW_GSP:
	case DCB_CAP_ATTW_BCN:
	defauwt:
		*cap = fawse;
		bweak;
	}

	dev_dbg(&pf->pdev->dev, "Get Capabiwity cap=%d capvaw=0x%x\n",
		capid, *cap);
	wetuwn I40E_DCBNW_STATUS_SUCCESS;
}

/**
 * i40e_dcbnw_getnumtcs - Get max numbew of twaffic cwasses suppowted
 * @netdev: the cowwesponding netdev
 * @tcid: the TC id
 * @num: totaw numbew of TCs suppowted by the device
 *
 * Wetuwn the totaw numbew of TCs suppowted by the adaptew
 **/
static int i40e_dcbnw_getnumtcs(stwuct net_device *netdev, int tcid, u8 *num)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	if (!test_bit(I40E_FWAG_DCB_CAPABWE, pf->fwags))
		wetuwn -EINVAW;

	*num = I40E_MAX_TWAFFIC_CWASS;
	wetuwn 0;
}

/**
 * i40e_dcbnw_setnumtcs - Set CEE numbew of twaffic cwasses
 * @netdev: the cowwesponding netdev
 * @tcid: the TC id
 * @num: totaw numbew of TCs
 *
 * Set the totaw numbew of TCs (Unsuppowted)
 **/
static int i40e_dcbnw_setnumtcs(stwuct net_device *netdev, int tcid, u8 num)
{
	wetuwn -EINVAW;
}

/**
 * i40e_dcbnw_getpfcstate - Get CEE PFC mode
 * @netdev: the cowwesponding netdev
 *
 * Get the cuwwent PFC enabwed state
 **/
static u8 i40e_dcbnw_getpfcstate(stwuct net_device *netdev)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	/* Wetuwn enabwed if any PFC enabwed UP */
	if (pf->hw.wocaw_dcbx_config.pfc.pfcenabwe)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/**
 * i40e_dcbnw_setpfcstate - Set CEE PFC mode
 * @netdev: the cowwesponding netdev
 * @state: wequiwed state
 *
 * The PFC state to be set; this is enabwed/disabwed based on the PFC
 * pwiowity settings and not via this caww fow i40e dwivew
 **/
static void i40e_dcbnw_setpfcstate(stwuct net_device *netdev, u8 state)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	dev_dbg(&pf->pdev->dev, "PFC State is modified via PFC config.\n");
}

/**
 * i40e_dcbnw_getapp - Get CEE APP
 * @netdev: the cowwesponding netdev
 * @idtype: the App sewectow
 * @id: the App ethtype ow powt numbew
 *
 * Wetuwn the CEE mode app fow the given idtype and id
 **/
static int i40e_dcbnw_getapp(stwuct net_device *netdev, u8 idtype, u16 id)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);
	stwuct dcb_app app = {
				.sewectow = idtype,
				.pwotocow = id,
			     };

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE) ||
	    (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED))
		wetuwn -EINVAW;

	wetuwn dcb_getapp(netdev, &app);
}

/**
 * i40e_dcbnw_setdcbx - set wequiwed DCBx capabiwity
 * @netdev: the cowwesponding netdev
 * @mode: new DCB mode managed ow CEE+IEEE
 *
 * Set DCBx capabiwity featuwes
 **/
static u8 i40e_dcbnw_setdcbx(stwuct net_device *netdev, u8 mode)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(netdev);

	/* Do not awwow to set mode if managed by Fiwmwawe */
	if (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED)
		wetuwn I40E_DCBNW_STATUS_EWWOW;

	/* No suppowt fow WWD_MANAGED modes ow CEE+IEEE */
	if ((mode & DCB_CAP_DCBX_WWD_MANAGED) ||
	    ((mode & DCB_CAP_DCBX_VEW_IEEE) && (mode & DCB_CAP_DCBX_VEW_CEE)) ||
	    !(mode & DCB_CAP_DCBX_HOST))
		wetuwn I40E_DCBNW_STATUS_EWWOW;

	/* Awweady set to the given mode no change */
	if (mode == pf->dcbx_cap)
		wetuwn I40E_DCBNW_STATUS_SUCCESS;

	pf->dcbx_cap = mode;
	if (mode & DCB_CAP_DCBX_VEW_CEE)
		pf->hw.wocaw_dcbx_config.dcbx_mode = I40E_DCBX_MODE_CEE;
	ewse
		pf->hw.wocaw_dcbx_config.dcbx_mode = I40E_DCBX_MODE_IEEE;

	dev_dbg(&pf->pdev->dev, "mode=%d\n", mode);
	wetuwn I40E_DCBNW_STATUS_SUCCESS;
}

/**
 * i40e_dcbnw_getdcbx - wetwieve cuwwent DCBx capabiwity
 * @dev: the cowwesponding netdev
 *
 * Wetuwns DCBx capabiwity featuwes
 **/
static u8 i40e_dcbnw_getdcbx(stwuct net_device *dev)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(dev);

	wetuwn pf->dcbx_cap;
}

/**
 * i40e_dcbnw_get_pewm_hw_addw - MAC addwess used by DCBx
 * @dev: the cowwesponding netdev
 * @pewm_addw: buffew to stowe the MAC addwess
 *
 * Wetuwns the SAN MAC addwess used fow WWDP exchange
 **/
static void i40e_dcbnw_get_pewm_hw_addw(stwuct net_device *dev,
					u8 *pewm_addw)
{
	stwuct i40e_pf *pf = i40e_netdev_to_pf(dev);
	int i;

	memset(pewm_addw, 0xff, MAX_ADDW_WEN);

	fow (i = 0; i < dev->addw_wen; i++)
		pewm_addw[i] = pf->hw.mac.pewm_addw[i];
}

static const stwuct dcbnw_wtnw_ops dcbnw_ops = {
	.ieee_getets	= i40e_dcbnw_ieee_getets,
	.ieee_getpfc	= i40e_dcbnw_ieee_getpfc,
	.getdcbx	= i40e_dcbnw_getdcbx,
	.getpewmhwaddw	= i40e_dcbnw_get_pewm_hw_addw,
	.ieee_setets	= i40e_dcbnw_ieee_setets,
	.ieee_setpfc	= i40e_dcbnw_ieee_setpfc,
	.ieee_setapp	= i40e_dcbnw_ieee_setapp,
	.ieee_dewapp	= i40e_dcbnw_ieee_dewapp,
	.getstate	= i40e_dcbnw_getstate,
	.setstate	= i40e_dcbnw_setstate,
	.setpgtccfgtx	= i40e_dcbnw_set_pg_tc_cfg_tx,
	.setpgbwgcfgtx	= i40e_dcbnw_set_pg_bwg_cfg_tx,
	.setpgtccfgwx	= i40e_dcbnw_set_pg_tc_cfg_wx,
	.setpgbwgcfgwx	= i40e_dcbnw_set_pg_bwg_cfg_wx,
	.getpgtccfgtx	= i40e_dcbnw_get_pg_tc_cfg_tx,
	.getpgbwgcfgtx	= i40e_dcbnw_get_pg_bwg_cfg_tx,
	.getpgtccfgwx	= i40e_dcbnw_get_pg_tc_cfg_wx,
	.getpgbwgcfgwx	= i40e_dcbnw_get_pg_bwg_cfg_wx,
	.setpfccfg	= i40e_dcbnw_set_pfc_cfg,
	.getpfccfg	= i40e_dcbnw_get_pfc_cfg,
	.setaww		= i40e_dcbnw_cee_set_aww,
	.getcap		= i40e_dcbnw_get_cap,
	.getnumtcs	= i40e_dcbnw_getnumtcs,
	.setnumtcs	= i40e_dcbnw_setnumtcs,
	.getpfcstate	= i40e_dcbnw_getpfcstate,
	.setpfcstate	= i40e_dcbnw_setpfcstate,
	.getapp		= i40e_dcbnw_getapp,
	.setdcbx	= i40e_dcbnw_setdcbx,
};

/**
 * i40e_dcbnw_set_aww - set aww the apps and ieee data fwom DCBx config
 * @vsi: the cowwesponding vsi
 *
 * Set up aww the IEEE APPs in the DCBNW App Tabwe and genewate event fow
 * othew settings
 **/
void i40e_dcbnw_set_aww(stwuct i40e_vsi *vsi)
{
	stwuct net_device *dev = vsi->netdev;
	stwuct i40e_pf *pf = i40e_netdev_to_pf(dev);
	stwuct i40e_dcbx_config *dcbxcfg;
	stwuct i40e_hw *hw = &pf->hw;
	stwuct dcb_app sapp;
	u8 pwio, tc_map;
	int i;

	/* SW DCB taken cawe by DCBNW set cawws */
	if (pf->dcbx_cap & DCB_CAP_DCBX_HOST)
		wetuwn;

	/* DCB not enabwed */
	if (!test_bit(I40E_FWAG_DCB_ENA, pf->fwags))
		wetuwn;

	/* MFP mode but not an iSCSI PF so wetuwn */
	if (test_bit(I40E_FWAG_MFP_ENA, pf->fwags) && !(hw->func_caps.iscsi))
		wetuwn;

	dcbxcfg = &hw->wocaw_dcbx_config;

	/* Set up aww the App TWVs if DCBx is negotiated */
	fow (i = 0; i < dcbxcfg->numapps; i++) {
		pwio = dcbxcfg->app[i].pwiowity;
		tc_map = BIT(dcbxcfg->etscfg.pwiowitytabwe[pwio]);

		/* Add APP onwy if the TC is enabwed fow this VSI */
		if (tc_map & vsi->tc_config.enabwed_tc) {
			sapp.sewectow = dcbxcfg->app[i].sewectow;
			sapp.pwotocow = dcbxcfg->app[i].pwotocowid;
			sapp.pwiowity = pwio;
			dcb_ieee_setapp(dev, &sapp);
		}
	}

	/* Notify usew-space of the changes */
	dcbnw_ieee_notify(dev, WTM_SETDCB, DCB_CMD_IEEE_SET, 0, 0);
}

/**
 * i40e_dcbnw_vsi_dew_app - Dewete APP fow given VSI
 * @vsi: the cowwesponding vsi
 * @app: APP to dewete
 *
 * Dewete given APP fwom the DCBNW APP tabwe fow given
 * VSI
 **/
static int i40e_dcbnw_vsi_dew_app(stwuct i40e_vsi *vsi,
				  stwuct i40e_dcb_app_pwiowity_tabwe *app)
{
	stwuct net_device *dev = vsi->netdev;
	stwuct dcb_app sapp;

	if (!dev)
		wetuwn -EINVAW;

	sapp.sewectow = app->sewectow;
	sapp.pwotocow = app->pwotocowid;
	sapp.pwiowity = app->pwiowity;
	wetuwn dcb_ieee_dewapp(dev, &sapp);
}

/**
 * i40e_dcbnw_dew_app - Dewete APP on aww VSIs
 * @pf: the cowwesponding PF
 * @app: APP to dewete
 *
 * Dewete given APP fwom aww the VSIs fow given PF
 **/
static void i40e_dcbnw_dew_app(stwuct i40e_pf *pf,
			       stwuct i40e_dcb_app_pwiowity_tabwe *app)
{
	int v, eww;

	fow (v = 0; v < pf->num_awwoc_vsi; v++) {
		if (pf->vsi[v] && pf->vsi[v]->netdev) {
			eww = i40e_dcbnw_vsi_dew_app(pf->vsi[v], app);
			dev_dbg(&pf->pdev->dev, "Deweting app fow VSI seid=%d eww=%d sew=%d pwoto=0x%x pwio=%d\n",
				pf->vsi[v]->seid, eww, app->sewectow,
				app->pwotocowid, app->pwiowity);
		}
	}
}

/**
 * i40e_dcbnw_find_app - Seawch APP in given DCB config
 * @cfg: DCBX configuwation data
 * @app: APP to seawch fow
 *
 * Find given APP in the DCB configuwation
 **/
static boow i40e_dcbnw_find_app(stwuct i40e_dcbx_config *cfg,
				stwuct i40e_dcb_app_pwiowity_tabwe *app)
{
	int i;

	fow (i = 0; i < cfg->numapps; i++) {
		if (app->sewectow == cfg->app[i].sewectow &&
		    app->pwotocowid == cfg->app[i].pwotocowid &&
		    app->pwiowity == cfg->app[i].pwiowity)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * i40e_dcbnw_fwush_apps - Dewete aww wemoved APPs
 * @pf: the cowwesponding PF
 * @owd_cfg: owd DCBX configuwation data
 * @new_cfg: new DCBX configuwation data
 *
 * Find and dewete aww APPs that awe not pwesent in the passed
 * DCB configuwation
 **/
void i40e_dcbnw_fwush_apps(stwuct i40e_pf *pf,
			   stwuct i40e_dcbx_config *owd_cfg,
			   stwuct i40e_dcbx_config *new_cfg)
{
	stwuct i40e_dcb_app_pwiowity_tabwe app;
	int i;

	/* MFP mode but not an iSCSI PF so wetuwn */
	if (test_bit(I40E_FWAG_MFP_ENA, pf->fwags) && !(pf->hw.func_caps.iscsi))
		wetuwn;

	fow (i = 0; i < owd_cfg->numapps; i++) {
		app = owd_cfg->app[i];
		/* The APP is not avaiwabwe anymowe dewete it */
		if (!i40e_dcbnw_find_app(new_cfg, &app))
			i40e_dcbnw_dew_app(pf, &app);
	}
}

/**
 * i40e_dcbnw_setup - DCBNW setup
 * @vsi: the cowwesponding vsi
 *
 * Set up DCBNW ops and initiaw APP TWVs
 **/
void i40e_dcbnw_setup(stwuct i40e_vsi *vsi)
{
	stwuct net_device *dev = vsi->netdev;
	stwuct i40e_pf *pf = i40e_netdev_to_pf(dev);

	/* Not DCB capabwe */
	if (!test_bit(I40E_FWAG_DCB_CAPABWE, pf->fwags))
		wetuwn;

	dev->dcbnw_ops = &dcbnw_ops;

	/* Set initiaw IEEE DCB settings */
	i40e_dcbnw_set_aww(vsi);
}
#endif /* CONFIG_I40E_DCB */
