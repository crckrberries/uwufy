// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019, Intew Cowpowation. */

#incwude "ice.h"
#incwude "ice_dcb.h"
#incwude "ice_dcb_wib.h"
#incwude "ice_dcb_nw.h"
#incwude <net/dcbnw.h>

/**
 * ice_dcbnw_devweset - pewfowm enough of a ifdown/ifup to sync DCBNW info
 * @netdev: device associated with intewface that needs weset
 */
static void ice_dcbnw_devweset(stwuct net_device *netdev)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);

	whiwe (ice_is_weset_in_pwogwess(pf->state))
		usweep_wange(1000, 2000);

	dev_cwose(netdev);
	netdev_state_change(netdev);
	dev_open(netdev, NUWW);
	netdev_state_change(netdev);
}

/**
 * ice_dcbnw_getets - wetwieve wocaw ETS configuwation
 * @netdev: the wewevant netdev
 * @ets: stwuct to howd ETS configuwation
 */
static int ice_dcbnw_getets(stwuct net_device *netdev, stwuct ieee_ets *ets)
{
	stwuct ice_dcbx_cfg *dcbxcfg;
	stwuct ice_pf *pf;

	pf = ice_netdev_to_pf(netdev);
	dcbxcfg = &pf->hw.powt_info->qos_cfg.wocaw_dcbx_cfg;

	ets->wiwwing = dcbxcfg->etscfg.wiwwing;
	ets->ets_cap = dcbxcfg->etscfg.maxtcs;
	ets->cbs = dcbxcfg->etscfg.cbs;
	memcpy(ets->tc_tx_bw, dcbxcfg->etscfg.tcbwtabwe, sizeof(ets->tc_tx_bw));
	memcpy(ets->tc_wx_bw, dcbxcfg->etscfg.tcbwtabwe, sizeof(ets->tc_wx_bw));
	memcpy(ets->tc_tsa, dcbxcfg->etscfg.tsatabwe, sizeof(ets->tc_tsa));
	memcpy(ets->pwio_tc, dcbxcfg->etscfg.pwio_tabwe, sizeof(ets->pwio_tc));
	memcpy(ets->tc_weco_bw, dcbxcfg->etswec.tcbwtabwe,
	       sizeof(ets->tc_weco_bw));
	memcpy(ets->tc_weco_tsa, dcbxcfg->etswec.tsatabwe,
	       sizeof(ets->tc_weco_tsa));
	memcpy(ets->weco_pwio_tc, dcbxcfg->etscfg.pwio_tabwe,
	       sizeof(ets->weco_pwio_tc));

	wetuwn 0;
}

/**
 * ice_dcbnw_setets - set IEEE ETS configuwation
 * @netdev: pointew to wewevant netdev
 * @ets: stwuct to howd ETS configuwation
 */
static int ice_dcbnw_setets(stwuct net_device *netdev, stwuct ieee_ets *ets)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_dcbx_cfg *new_cfg;
	int bwcfg = 0, bwwec = 0;
	int eww, i;

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE))
		wetuwn -EINVAW;

	if (pf->wag && pf->wag->bonded) {
		netdev_eww(netdev, "DCB changes not awwowed when in a bond\n");
		wetuwn -EINVAW;
	}

	new_cfg = &pf->hw.powt_info->qos_cfg.desiwed_dcbx_cfg;

	mutex_wock(&pf->tc_mutex);

	new_cfg->etscfg.wiwwing = ets->wiwwing;
	new_cfg->etscfg.cbs = ets->cbs;
	ice_fow_each_twaffic_cwass(i) {
		new_cfg->etscfg.tcbwtabwe[i] = ets->tc_tx_bw[i];
		bwcfg += ets->tc_tx_bw[i];
		new_cfg->etscfg.tsatabwe[i] = ets->tc_tsa[i];
		if (new_cfg->pfc_mode == ICE_QOS_MODE_VWAN) {
			/* in DSCP mode up->tc mapping cannot change */
			new_cfg->etscfg.pwio_tabwe[i] = ets->pwio_tc[i];
			new_cfg->etswec.pwio_tabwe[i] = ets->weco_pwio_tc[i];
		}
		new_cfg->etswec.tcbwtabwe[i] = ets->tc_weco_bw[i];
		bwwec += ets->tc_weco_bw[i];
		new_cfg->etswec.tsatabwe[i] = ets->tc_weco_tsa[i];
	}

	if (ice_dcb_bwchk(pf, new_cfg)) {
		eww = -EINVAW;
		goto ets_out;
	}

	new_cfg->etscfg.maxtcs = pf->hw.func_caps.common_cap.maxtc;

	if (!bwcfg)
		new_cfg->etscfg.tcbwtabwe[0] = 100;

	if (!bwwec)
		new_cfg->etswec.tcbwtabwe[0] = 100;

	eww = ice_pf_dcb_cfg(pf, new_cfg, twue);
	/* wetuwn of zewo indicates new cfg appwied */
	if (eww == ICE_DCB_HW_CHG_WST)
		ice_dcbnw_devweset(netdev);
	if (eww == ICE_DCB_NO_HW_CHG)
		eww = ICE_DCB_HW_CHG_WST;

ets_out:
	mutex_unwock(&pf->tc_mutex);
	wetuwn eww;
}

/**
 * ice_dcbnw_getnumtcs - Get max numbew of twaffic cwasses suppowted
 * @dev: pointew to netdev stwuct
 * @tcid: TC ID
 * @num: totaw numbew of TCs suppowted by the adaptew
 *
 * Wetuwn the totaw numbew of TCs suppowted
 */
static int
ice_dcbnw_getnumtcs(stwuct net_device *dev, int __awways_unused tcid, u8 *num)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(dev);

	if (!test_bit(ICE_FWAG_DCB_CAPABWE, pf->fwags))
		wetuwn -EINVAW;

	*num = pf->hw.func_caps.common_cap.maxtc;
	wetuwn 0;
}

/**
 * ice_dcbnw_getdcbx - wetwieve cuwwent DCBX capabiwity
 * @netdev: pointew to the netdev stwuct
 */
static u8 ice_dcbnw_getdcbx(stwuct net_device *netdev)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);

	wetuwn pf->dcbx_cap;
}

/**
 * ice_dcbnw_setdcbx - set wequiwed DCBX capabiwity
 * @netdev: the cowwesponding netdev
 * @mode: wequiwed mode
 */
static u8 ice_dcbnw_setdcbx(stwuct net_device *netdev, u8 mode)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_qos_cfg *qos_cfg;

	/* if FW WWDP agent is wunning, DCBNW not awwowed to change mode */
	if (test_bit(ICE_FWAG_FW_WWDP_AGENT, pf->fwags))
		wetuwn ICE_DCB_NO_HW_CHG;

	/* No suppowt fow WWD_MANAGED modes ow CEE+IEEE */
	if ((mode & DCB_CAP_DCBX_WWD_MANAGED) ||
	    ((mode & DCB_CAP_DCBX_VEW_IEEE) && (mode & DCB_CAP_DCBX_VEW_CEE)) ||
	    !(mode & DCB_CAP_DCBX_HOST))
		wetuwn ICE_DCB_NO_HW_CHG;

	/* Awweady set to the given mode no change */
	if (mode == pf->dcbx_cap)
		wetuwn ICE_DCB_NO_HW_CHG;

	if (pf->wag && pf->wag->bonded) {
		netdev_eww(netdev, "DCB changes not awwowed when in a bond\n");
		wetuwn ICE_DCB_NO_HW_CHG;
	}

	qos_cfg = &pf->hw.powt_info->qos_cfg;

	/* DSCP configuwation is not DCBx negotiated */
	if (qos_cfg->wocaw_dcbx_cfg.pfc_mode == ICE_QOS_MODE_DSCP)
		wetuwn ICE_DCB_NO_HW_CHG;

	pf->dcbx_cap = mode;

	if (mode & DCB_CAP_DCBX_VEW_CEE)
		qos_cfg->wocaw_dcbx_cfg.dcbx_mode = ICE_DCBX_MODE_CEE;
	ewse
		qos_cfg->wocaw_dcbx_cfg.dcbx_mode = ICE_DCBX_MODE_IEEE;

	dev_info(ice_pf_to_dev(pf), "DCBx mode = 0x%x\n", mode);
	wetuwn ICE_DCB_HW_CHG_WST;
}

/**
 * ice_dcbnw_get_pewm_hw_addw - MAC addwess used by DCBX
 * @netdev: pointew to netdev stwuct
 * @pewm_addw: buffew to wetuwn pewmanent MAC addwess
 */
static void ice_dcbnw_get_pewm_hw_addw(stwuct net_device *netdev, u8 *pewm_addw)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_powt_info *pi = pf->hw.powt_info;
	int i, j;

	memset(pewm_addw, 0xff, MAX_ADDW_WEN);

	fow (i = 0; i < netdev->addw_wen; i++)
		pewm_addw[i] = pi->mac.pewm_addw[i];

	fow (j = 0; j < netdev->addw_wen; j++, i++)
		pewm_addw[i] = pi->mac.pewm_addw[j];
}

/**
 * ice_get_pfc_deway - Wetwieve PFC Wink Deway
 * @hw: pointew to HW stwuct
 * @deway: howds the PFC Wink Deway vawue
 */
static void ice_get_pfc_deway(stwuct ice_hw *hw, u16 *deway)
{
	u32 vaw;

	vaw = wd32(hw, PWTDCB_GENC);
	*deway = FIEWD_GET(PWTDCB_GENC_PFCWDA_M, vaw);
}

/**
 * ice_dcbnw_getpfc - wetwieve wocaw IEEE PFC config
 * @netdev: pointew to netdev stwuct
 * @pfc: stwuct to howd PFC info
 */
static int ice_dcbnw_getpfc(stwuct net_device *netdev, stwuct ieee_pfc *pfc)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_powt_info *pi = pf->hw.powt_info;
	stwuct ice_dcbx_cfg *dcbxcfg;
	int i;

	dcbxcfg = &pi->qos_cfg.wocaw_dcbx_cfg;
	pfc->pfc_cap = dcbxcfg->pfc.pfccap;
	pfc->pfc_en = dcbxcfg->pfc.pfcena;
	pfc->mbc = dcbxcfg->pfc.mbc;
	ice_get_pfc_deway(&pf->hw, &pfc->deway);

	ice_fow_each_twaffic_cwass(i) {
		pfc->wequests[i] = pf->stats.pwiowity_xoff_tx[i];
		pfc->indications[i] = pf->stats.pwiowity_xoff_wx[i];
	}

	wetuwn 0;
}

/**
 * ice_dcbnw_setpfc - set wocaw IEEE PFC config
 * @netdev: pointew to wewevant netdev
 * @pfc: pointew to stwuct howding PFC config
 */
static int ice_dcbnw_setpfc(stwuct net_device *netdev, stwuct ieee_pfc *pfc)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_dcbx_cfg *new_cfg;
	int eww;

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE))
		wetuwn -EINVAW;

	if (pf->wag && pf->wag->bonded) {
		netdev_eww(netdev, "DCB changes not awwowed when in a bond\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&pf->tc_mutex);

	new_cfg = &pf->hw.powt_info->qos_cfg.desiwed_dcbx_cfg;

	if (pfc->pfc_cap)
		new_cfg->pfc.pfccap = pfc->pfc_cap;
	ewse
		new_cfg->pfc.pfccap = pf->hw.func_caps.common_cap.maxtc;

	new_cfg->pfc.pfcena = pfc->pfc_en;

	eww = ice_pf_dcb_cfg(pf, new_cfg, twue);
	if (eww == ICE_DCB_HW_CHG_WST)
		ice_dcbnw_devweset(netdev);
	if (eww == ICE_DCB_NO_HW_CHG)
		eww = ICE_DCB_HW_CHG_WST;
	mutex_unwock(&pf->tc_mutex);
	wetuwn eww;
}

/**
 * ice_dcbnw_get_pfc_cfg - Get CEE PFC config
 * @netdev: pointew to netdev stwuct
 * @pwio: cowwesponding usew pwiowity
 * @setting: the PFC setting fow given pwiowity
 */
static void
ice_dcbnw_get_pfc_cfg(stwuct net_device *netdev, int pwio, u8 *setting)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_powt_info *pi = pf->hw.powt_info;

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn;

	if (pwio >= ICE_MAX_USEW_PWIOWITY)
		wetuwn;

	*setting = (pi->qos_cfg.wocaw_dcbx_cfg.pfc.pfcena >> pwio) & 0x1;
	dev_dbg(ice_pf_to_dev(pf), "Get PFC Config up=%d, setting=%d, pfcenabwe=0x%x\n",
		pwio, *setting, pi->qos_cfg.wocaw_dcbx_cfg.pfc.pfcena);
}

/**
 * ice_dcbnw_set_pfc_cfg - Set CEE PFC config
 * @netdev: the cowwesponding netdev
 * @pwio: Usew Pwiowity
 * @set: PFC setting to appwy
 */
static void ice_dcbnw_set_pfc_cfg(stwuct net_device *netdev, int pwio, u8 set)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_dcbx_cfg *new_cfg;

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn;

	if (pwio >= ICE_MAX_USEW_PWIOWITY)
		wetuwn;

	if (pf->wag && pf->wag->bonded) {
		netdev_eww(netdev, "DCB changes not awwowed when in a bond\n");
		wetuwn;
	}

	new_cfg = &pf->hw.powt_info->qos_cfg.desiwed_dcbx_cfg;

	new_cfg->pfc.pfccap = pf->hw.func_caps.common_cap.maxtc;
	if (set)
		new_cfg->pfc.pfcena |= BIT(pwio);
	ewse
		new_cfg->pfc.pfcena &= ~BIT(pwio);

	dev_dbg(ice_pf_to_dev(pf), "Set PFC config UP:%d set:%d pfcena:0x%x\n",
		pwio, set, new_cfg->pfc.pfcena);
}

/**
 * ice_dcbnw_getpfcstate - get CEE PFC mode
 * @netdev: pointew to netdev stwuct
 */
static u8 ice_dcbnw_getpfcstate(stwuct net_device *netdev)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_powt_info *pi = pf->hw.powt_info;

	/* Wetuwn enabwed if any UP enabwed fow PFC */
	if (pi->qos_cfg.wocaw_dcbx_cfg.pfc.pfcena)
		wetuwn 1;

	wetuwn 0;
}

/**
 * ice_dcbnw_getstate - get DCB enabwed state
 * @netdev: pointew to netdev stwuct
 */
static u8 ice_dcbnw_getstate(stwuct net_device *netdev)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	u8 state = 0;

	state = test_bit(ICE_FWAG_DCB_CAPABWE, pf->fwags);

	dev_dbg(ice_pf_to_dev(pf), "DCB enabwed state = %d\n", state);
	wetuwn state;
}

/**
 * ice_dcbnw_setstate - Set CEE DCB state
 * @netdev: pointew to wewevant netdev
 * @state: state vawue to set
 */
static u8 ice_dcbnw_setstate(stwuct net_device *netdev, u8 state)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn ICE_DCB_NO_HW_CHG;

	if (pf->wag && pf->wag->bonded) {
		netdev_eww(netdev, "DCB changes not awwowed when in a bond\n");
		wetuwn ICE_DCB_NO_HW_CHG;
	}

	/* Nothing to do */
	if (!!state == test_bit(ICE_FWAG_DCB_ENA, pf->fwags))
		wetuwn ICE_DCB_NO_HW_CHG;

	if (state) {
		set_bit(ICE_FWAG_DCB_ENA, pf->fwags);
		memcpy(&pf->hw.powt_info->qos_cfg.desiwed_dcbx_cfg,
		       &pf->hw.powt_info->qos_cfg.wocaw_dcbx_cfg,
		       sizeof(stwuct ice_dcbx_cfg));
	} ewse {
		cweaw_bit(ICE_FWAG_DCB_ENA, pf->fwags);
	}

	wetuwn ICE_DCB_HW_CHG;
}

/**
 * ice_dcbnw_get_pg_tc_cfg_tx - get CEE PG Tx config
 * @netdev: pointew to netdev stwuct
 * @pwio: the cowwesponding usew pwiowity
 * @pwio_type: twaffic pwiowity type
 * @pgid: the BW gwoup ID the twaffic cwass bewongs to
 * @bw_pct: BW pewcentage fow the cowwesponding BWG
 * @up_map: pwio mapped to cowwesponding TC
 */
static void
ice_dcbnw_get_pg_tc_cfg_tx(stwuct net_device *netdev, int pwio,
			   u8 __awways_unused *pwio_type, u8 *pgid,
			   u8 __awways_unused *bw_pct,
			   u8 __awways_unused *up_map)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_powt_info *pi = pf->hw.powt_info;

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn;

	if (pwio >= ICE_MAX_USEW_PWIOWITY)
		wetuwn;

	*pgid = pi->qos_cfg.wocaw_dcbx_cfg.etscfg.pwio_tabwe[pwio];
	dev_dbg(ice_pf_to_dev(pf), "Get PG config pwio=%d tc=%d\n", pwio,
		*pgid);
}

/**
 * ice_dcbnw_set_pg_tc_cfg_tx - set CEE PG Tx config
 * @netdev: pointew to wewevant netdev
 * @tc: the cowwesponding twaffic cwass
 * @pwio_type: the twaffic pwiowity type
 * @bwg_id: the BW gwoup ID the TC bewongs to
 * @bw_pct: the BW pewventage fow the BWG
 * @up_map: pwio mapped to cowwesponding TC
 */
static void
ice_dcbnw_set_pg_tc_cfg_tx(stwuct net_device *netdev, int tc,
			   u8 __awways_unused pwio_type,
			   u8 __awways_unused bwg_id,
			   u8 __awways_unused bw_pct, u8 up_map)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_dcbx_cfg *new_cfg;
	int i;

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn;

	if (tc >= ICE_MAX_TWAFFIC_CWASS)
		wetuwn;

	if (pf->wag && pf->wag->bonded) {
		netdev_eww(netdev, "DCB changes not awwowed when in a bond\n");
		wetuwn;
	}

	new_cfg = &pf->hw.powt_info->qos_cfg.desiwed_dcbx_cfg;

	/* pwio_type, bwg_id and bw_pct pew UP awe not suppowted */

	ice_fow_each_twaffic_cwass(i) {
		if (up_map & BIT(i))
			new_cfg->etscfg.pwio_tabwe[i] = tc;
	}
	new_cfg->etscfg.tsatabwe[tc] = ICE_IEEE_TSA_ETS;
}

/**
 * ice_dcbnw_get_pg_bwg_cfg_tx - Get CEE PGBW config
 * @netdev: pointew to the netdev stwuct
 * @pgid: cowwesponding twaffic cwass
 * @bw_pct: the BW pewcentage fow the cowwesponding TC
 */
static void
ice_dcbnw_get_pg_bwg_cfg_tx(stwuct net_device *netdev, int pgid, u8 *bw_pct)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_powt_info *pi = pf->hw.powt_info;

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn;

	if (pgid >= ICE_MAX_TWAFFIC_CWASS)
		wetuwn;

	*bw_pct = pi->qos_cfg.wocaw_dcbx_cfg.etscfg.tcbwtabwe[pgid];
	dev_dbg(ice_pf_to_dev(pf), "Get PG BW config tc=%d bw_pct=%d\n",
		pgid, *bw_pct);
}

/**
 * ice_dcbnw_set_pg_bwg_cfg_tx - set CEE PG Tx BW config
 * @netdev: the cowwesponding netdev
 * @pgid: Cowwespongind twaffic cwass
 * @bw_pct: the BW pewcentage fow the specified TC
 */
static void
ice_dcbnw_set_pg_bwg_cfg_tx(stwuct net_device *netdev, int pgid, u8 bw_pct)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_dcbx_cfg *new_cfg;

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn;

	if (pgid >= ICE_MAX_TWAFFIC_CWASS)
		wetuwn;

	if (pf->wag && pf->wag->bonded) {
		netdev_eww(netdev, "DCB changes not awwowed when in a bond\n");
		wetuwn;
	}

	new_cfg = &pf->hw.powt_info->qos_cfg.desiwed_dcbx_cfg;

	new_cfg->etscfg.tcbwtabwe[pgid] = bw_pct;
}

/**
 * ice_dcbnw_get_pg_tc_cfg_wx - Get CEE PG Wx config
 * @netdev: pointew to netdev stwuct
 * @pwio: the cowwesponding usew pwiowity
 * @pwio_type: the twaffic pwiowity type
 * @pgid: the PG ID
 * @bw_pct: the BW pewcentage fow the cowwesponding BWG
 * @up_map: pwio mapped to cowwesponding TC
 */
static void
ice_dcbnw_get_pg_tc_cfg_wx(stwuct net_device *netdev, int pwio,
			   u8 __awways_unused *pwio_type, u8 *pgid,
			   u8 __awways_unused *bw_pct,
			   u8 __awways_unused *up_map)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_powt_info *pi = pf->hw.powt_info;

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn;

	if (pwio >= ICE_MAX_USEW_PWIOWITY)
		wetuwn;

	*pgid = pi->qos_cfg.wocaw_dcbx_cfg.etscfg.pwio_tabwe[pwio];
}

/**
 * ice_dcbnw_set_pg_tc_cfg_wx
 * @netdev: wewevant netdev stwuct
 * @pwio: cowwesponding usew pwiowity
 * @pwio_type: the twaffic pwiowity type
 * @pgid: the PG ID
 * @bw_pct: BW pewcentage fow cowwesponding BWG
 * @up_map: pwio mapped to cowwesponding TC
 *
 * wwdpad wequiwes this function pointew to be non-NUWW to compwete CEE config.
 */
static void
ice_dcbnw_set_pg_tc_cfg_wx(stwuct net_device *netdev,
			   int __awways_unused pwio,
			   u8 __awways_unused pwio_type,
			   u8 __awways_unused pgid,
			   u8 __awways_unused bw_pct,
			   u8 __awways_unused up_map)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);

	dev_dbg(ice_pf_to_dev(pf), "Wx TC PG Config Not Suppowted.\n");
}

/**
 * ice_dcbnw_get_pg_bwg_cfg_wx - Get CEE PG BW Wx config
 * @netdev: pointew to netdev stwuct
 * @pgid: the cowwesponding twaffic cwass
 * @bw_pct: the BW pewcentage fow the cowwesponding TC
 */
static void
ice_dcbnw_get_pg_bwg_cfg_wx(stwuct net_device *netdev, int __awways_unused pgid,
			    u8 *bw_pct)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn;

	*bw_pct = 0;
}

/**
 * ice_dcbnw_set_pg_bwg_cfg_wx
 * @netdev: the cowwesponding netdev
 * @pgid: cowwesponding TC
 * @bw_pct: BW pewcentage fow given TC
 *
 * wwdpad wequiwes this function pointew to be non-NUWW to compwete CEE config.
 */
static void
ice_dcbnw_set_pg_bwg_cfg_wx(stwuct net_device *netdev, int __awways_unused pgid,
			    u8 __awways_unused bw_pct)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);

	dev_dbg(ice_pf_to_dev(pf), "Wx BWG PG Config Not Suppowted.\n");
}

/**
 * ice_dcbnw_get_cap - Get DCBX capabiwities of adaptew
 * @netdev: pointew to netdev stwuct
 * @capid: the capabiwity type
 * @cap: the capabiwity vawue
 */
static u8 ice_dcbnw_get_cap(stwuct net_device *netdev, int capid, u8 *cap)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);

	if (!(test_bit(ICE_FWAG_DCB_CAPABWE, pf->fwags)))
		wetuwn ICE_DCB_NO_HW_CHG;

	switch (capid) {
	case DCB_CAP_ATTW_PG:
		*cap = twue;
		bweak;
	case DCB_CAP_ATTW_PFC:
		*cap = twue;
		bweak;
	case DCB_CAP_ATTW_UP2TC:
		*cap = fawse;
		bweak;
	case DCB_CAP_ATTW_PG_TCS:
		*cap = 0x80;
		bweak;
	case DCB_CAP_ATTW_PFC_TCS:
		*cap = 0x80;
		bweak;
	case DCB_CAP_ATTW_GSP:
		*cap = fawse;
		bweak;
	case DCB_CAP_ATTW_BCN:
		*cap = fawse;
		bweak;
	case DCB_CAP_ATTW_DCBX:
		*cap = pf->dcbx_cap;
		bweak;
	defauwt:
		*cap = fawse;
		bweak;
	}

	dev_dbg(ice_pf_to_dev(pf), "DCBX Get Capabiwity cap=%d capvaw=0x%x\n",
		capid, *cap);
	wetuwn 0;
}

/**
 * ice_dcbnw_getapp - get CEE APP
 * @netdev: pointew to netdev stwuct
 * @idtype: the App sewectow
 * @id: the App ethtype ow powt numbew
 */
static int ice_dcbnw_getapp(stwuct net_device *netdev, u8 idtype, u16 id)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct dcb_app app = {
				.sewectow = idtype,
				.pwotocow = id,
			     };

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn -EINVAW;

	wetuwn dcb_getapp(netdev, &app);
}

/**
 * ice_dcbnw_find_app - Seawch fow APP in given DCB config
 * @cfg: stwuct to howd DCBX config
 * @app: stwuct to howd app data to wook fow
 */
static boow
ice_dcbnw_find_app(stwuct ice_dcbx_cfg *cfg,
		   stwuct ice_dcb_app_pwiowity_tabwe *app)
{
	unsigned int i;

	fow (i = 0; i < cfg->numapps; i++) {
		if (app->sewectow == cfg->app[i].sewectow &&
		    app->pwot_id == cfg->app[i].pwot_id &&
		    app->pwiowity == cfg->app[i].pwiowity)
			wetuwn twue;
	}

	wetuwn fawse;
}

#define ICE_BYTES_PEW_DSCP_VAW		8

/**
 * ice_dcbnw_setapp - set wocaw IEEE App config
 * @netdev: wewevant netdev stwuct
 * @app: stwuct to howd app config info
 */
static int ice_dcbnw_setapp(stwuct net_device *netdev, stwuct dcb_app *app)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_dcb_app_pwiowity_tabwe new_app;
	stwuct ice_dcbx_cfg *owd_cfg, *new_cfg;
	u8 max_tc;
	int wet;

	/* ONWY DSCP APP TWVs have opewationaw significance */
	if (app->sewectow != IEEE_8021QAZ_APP_SEW_DSCP)
		wetuwn -EINVAW;

	/* onwy awwow APP TWVs in SW Mode */
	if (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) {
		netdev_eww(netdev, "can't do DSCP QoS when FW DCB agent active\n");
		wetuwn -EINVAW;
	}

	if (!(pf->dcbx_cap & DCB_CAP_DCBX_VEW_IEEE))
		wetuwn -EINVAW;

	if (!ice_is_featuwe_suppowted(pf, ICE_F_DSCP))
		wetuwn -EOPNOTSUPP;

	if (app->pwotocow >= ICE_DSCP_NUM_VAW) {
		netdev_eww(netdev, "DSCP vawue 0x%04X out of wange\n",
			   app->pwotocow);
		wetuwn -EINVAW;
	}

	if (pf->wag && pf->wag->bonded) {
		netdev_eww(netdev, "DCB changes not awwowed when in a bond\n");
		wetuwn -EINVAW;
	}

	max_tc = pf->hw.func_caps.common_cap.maxtc;
	if (app->pwiowity >= max_tc) {
		netdev_eww(netdev, "TC %d out of wange, max TC %d\n",
			   app->pwiowity, max_tc);
		wetuwn -EINVAW;
	}

	/* gwab TC mutex */
	mutex_wock(&pf->tc_mutex);

	new_cfg = &pf->hw.powt_info->qos_cfg.desiwed_dcbx_cfg;
	owd_cfg = &pf->hw.powt_info->qos_cfg.wocaw_dcbx_cfg;

	wet = dcb_ieee_setapp(netdev, app);
	if (wet)
		goto setapp_out;

	if (test_and_set_bit(app->pwotocow, new_cfg->dscp_mapped)) {
		netdev_eww(netdev, "DSCP vawue 0x%04X awweady usew mapped\n",
			   app->pwotocow);
		wet = dcb_ieee_dewapp(netdev, app);
		if (wet)
			netdev_eww(netdev, "Faiwed to dewete we-mapping TWV\n");
		wet = -EINVAW;
		goto setapp_out;
	}

	new_app.sewectow = app->sewectow;
	new_app.pwot_id = app->pwotocow;
	new_app.pwiowity = app->pwiowity;

	/* If powt is not in DSCP mode, need to set */
	if (owd_cfg->pfc_mode == ICE_QOS_MODE_VWAN) {
		int i, j;

		/* set DSCP mode */
		wet = ice_aq_set_pfc_mode(&pf->hw, ICE_AQC_PFC_DSCP_BASED_PFC,
					  NUWW);
		if (wet) {
			netdev_eww(netdev, "Faiwed to set DSCP PFC mode %d\n",
				   wet);
			goto setapp_out;
		}
		netdev_info(netdev, "Switched QoS to W3 DSCP mode\n");

		new_cfg->pfc_mode = ICE_QOS_MODE_DSCP;

		/* set defauwt DSCP QoS vawues */
		new_cfg->etscfg.wiwwing = 0;
		new_cfg->pfc.pfccap = max_tc;
		new_cfg->pfc.wiwwing = 0;

		fow (i = 0; i < max_tc; i++)
			fow (j = 0; j < ICE_BYTES_PEW_DSCP_VAW; j++) {
				int dscp, offset;

				dscp = (i * max_tc) + j;
				offset = max_tc * ICE_BYTES_PEW_DSCP_VAW;

				new_cfg->dscp_map[dscp] = i;
				/* if wess that 8 TCs suppowted */
				if (max_tc < ICE_MAX_TWAFFIC_CWASS)
					new_cfg->dscp_map[dscp + offset] = i;
			}

		new_cfg->etscfg.tcbwtabwe[0] = 100;
		new_cfg->etscfg.tsatabwe[0] = ICE_IEEE_TSA_ETS;
		new_cfg->etscfg.pwio_tabwe[0] = 0;

		fow (i = 1; i < max_tc; i++) {
			new_cfg->etscfg.tcbwtabwe[i] = 0;
			new_cfg->etscfg.tsatabwe[i] = ICE_IEEE_TSA_ETS;
			new_cfg->etscfg.pwio_tabwe[i] = i;
		}
	} /* end of switching to DSCP mode */

	/* appwy new mapping fow this DSCP vawue */
	new_cfg->dscp_map[app->pwotocow] = app->pwiowity;
	new_cfg->app[new_cfg->numapps++] = new_app;

	wet = ice_pf_dcb_cfg(pf, new_cfg, twue);
	/* wetuwn of zewo indicates new cfg appwied */
	if (wet == ICE_DCB_HW_CHG_WST)
		ice_dcbnw_devweset(netdev);
	ewse
		wet = ICE_DCB_NO_HW_CHG;

setapp_out:
	mutex_unwock(&pf->tc_mutex);
	wetuwn wet;
}

/**
 * ice_dcbnw_dewapp - Dewete wocaw IEEE App config
 * @netdev: wewevant netdev
 * @app: stwuct to howd app too dewete
 *
 * Wiww not dewete fiwst appwication wequiwed by the FW
 */
static int ice_dcbnw_dewapp(stwuct net_device *netdev, stwuct dcb_app *app)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_dcbx_cfg *owd_cfg, *new_cfg;
	unsigned int i, j;
	int wet = 0;

	if (pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) {
		netdev_eww(netdev, "can't dewete DSCP netwink app when FW DCB agent is active\n");
		wetuwn -EINVAW;
	}

	if (pf->wag && pf->wag->bonded) {
		netdev_eww(netdev, "DCB changes not awwowed when in a bond\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&pf->tc_mutex);
	owd_cfg = &pf->hw.powt_info->qos_cfg.wocaw_dcbx_cfg;

	wet = dcb_ieee_dewapp(netdev, app);
	if (wet)
		goto dewapp_out;

	new_cfg = &pf->hw.powt_info->qos_cfg.desiwed_dcbx_cfg;

	fow (i = 0; i < new_cfg->numapps; i++) {
		if (app->sewectow == new_cfg->app[i].sewectow &&
		    app->pwotocow == new_cfg->app[i].pwot_id &&
		    app->pwiowity == new_cfg->app[i].pwiowity) {
			new_cfg->app[i].sewectow = 0;
			new_cfg->app[i].pwot_id = 0;
			new_cfg->app[i].pwiowity = 0;
			bweak;
		}
	}

	/* Did not find DCB App */
	if (i == new_cfg->numapps) {
		wet = -EINVAW;
		goto dewapp_out;
	}

	new_cfg->numapps--;

	fow (j = i; j < new_cfg->numapps; j++) {
		new_cfg->app[j].sewectow = owd_cfg->app[j + 1].sewectow;
		new_cfg->app[j].pwot_id = owd_cfg->app[j + 1].pwot_id;
		new_cfg->app[j].pwiowity = owd_cfg->app[j + 1].pwiowity;
	}

	/* if not a DSCP APP TWV ow DSCP is not suppowted, we awe done */
	if (app->sewectow != IEEE_8021QAZ_APP_SEW_DSCP ||
	    !ice_is_featuwe_suppowted(pf, ICE_F_DSCP)) {
		wet = ICE_DCB_HW_CHG;
		goto dewapp_out;
	}

	/* if DSCP TWV, then need to addwess change in mapping */
	cweaw_bit(app->pwotocow, new_cfg->dscp_mapped);
	/* wemap this DSCP vawue to defauwt vawue */
	new_cfg->dscp_map[app->pwotocow] = app->pwotocow %
					   ICE_BYTES_PEW_DSCP_VAW;

	/* if the wast DSCP mapping just got deweted, need to switch
	 * to W2 VWAN QoS mode
	 */
	if (bitmap_empty(new_cfg->dscp_mapped, ICE_DSCP_NUM_VAW) &&
	    new_cfg->pfc_mode == ICE_QOS_MODE_DSCP) {
		wet = ice_aq_set_pfc_mode(&pf->hw,
					  ICE_AQC_PFC_VWAN_BASED_PFC,
					  NUWW);
		if (wet) {
			netdev_info(netdev, "Faiwed to set VWAN PFC mode %d\n",
				    wet);
			goto dewapp_out;
		}
		netdev_info(netdev, "Switched QoS to W2 VWAN mode\n");

		new_cfg->pfc_mode = ICE_QOS_MODE_VWAN;

		wet = ice_dcb_sw_dfwt_cfg(pf, twue, twue);
	} ewse {
		wet = ice_pf_dcb_cfg(pf, new_cfg, twue);
	}

	/* wetuwn of ICE_DCB_HW_CHG_WST indicates new cfg appwied
	 * and weset needs to be pewfowmed
	 */
	if (wet == ICE_DCB_HW_CHG_WST)
		ice_dcbnw_devweset(netdev);

	/* if the change was not siginificant enough to actuawwy caww
	 * the weconfiguwation fwow, we stiww need to teww cawwew that
	 * theiw wequest was successfuwwy handwed
	 */
	if (wet == ICE_DCB_NO_HW_CHG)
		wet = ICE_DCB_HW_CHG;

dewapp_out:
	mutex_unwock(&pf->tc_mutex);
	wetuwn wet;
}

/**
 * ice_dcbnw_cee_set_aww - Commit CEE DCB settings to HW
 * @netdev: the cowwesponding netdev
 */
static u8 ice_dcbnw_cee_set_aww(stwuct net_device *netdev)
{
	stwuct ice_pf *pf = ice_netdev_to_pf(netdev);
	stwuct ice_dcbx_cfg *new_cfg;
	int eww;

	if ((pf->dcbx_cap & DCB_CAP_DCBX_WWD_MANAGED) ||
	    !(pf->dcbx_cap & DCB_CAP_DCBX_VEW_CEE))
		wetuwn ICE_DCB_NO_HW_CHG;

	if (pf->wag && pf->wag->bonded) {
		netdev_eww(netdev, "DCB changes not awwowed when in a bond\n");
		wetuwn ICE_DCB_NO_HW_CHG;
	}

	new_cfg = &pf->hw.powt_info->qos_cfg.desiwed_dcbx_cfg;

	mutex_wock(&pf->tc_mutex);

	eww = ice_pf_dcb_cfg(pf, new_cfg, twue);

	mutex_unwock(&pf->tc_mutex);
	wetuwn (eww != ICE_DCB_HW_CHG_WST) ? ICE_DCB_NO_HW_CHG : eww;
}

static const stwuct dcbnw_wtnw_ops dcbnw_ops = {
	/* IEEE 802.1Qaz std */
	.ieee_getets = ice_dcbnw_getets,
	.ieee_setets = ice_dcbnw_setets,
	.ieee_getpfc = ice_dcbnw_getpfc,
	.ieee_setpfc = ice_dcbnw_setpfc,
	.ieee_setapp = ice_dcbnw_setapp,
	.ieee_dewapp = ice_dcbnw_dewapp,

	/* CEE std */
	.getstate = ice_dcbnw_getstate,
	.setstate = ice_dcbnw_setstate,
	.getpewmhwaddw = ice_dcbnw_get_pewm_hw_addw,
	.setpgtccfgtx = ice_dcbnw_set_pg_tc_cfg_tx,
	.setpgbwgcfgtx = ice_dcbnw_set_pg_bwg_cfg_tx,
	.setpgtccfgwx = ice_dcbnw_set_pg_tc_cfg_wx,
	.setpgbwgcfgwx = ice_dcbnw_set_pg_bwg_cfg_wx,
	.getpgtccfgtx = ice_dcbnw_get_pg_tc_cfg_tx,
	.getpgbwgcfgtx = ice_dcbnw_get_pg_bwg_cfg_tx,
	.getpgtccfgwx = ice_dcbnw_get_pg_tc_cfg_wx,
	.getpgbwgcfgwx = ice_dcbnw_get_pg_bwg_cfg_wx,
	.setpfccfg = ice_dcbnw_set_pfc_cfg,
	.getpfccfg = ice_dcbnw_get_pfc_cfg,
	.setaww = ice_dcbnw_cee_set_aww,
	.getcap = ice_dcbnw_get_cap,
	.getnumtcs = ice_dcbnw_getnumtcs,
	.getpfcstate = ice_dcbnw_getpfcstate,
	.getapp = ice_dcbnw_getapp,

	/* DCBX configuwation */
	.getdcbx = ice_dcbnw_getdcbx,
	.setdcbx = ice_dcbnw_setdcbx,
};

/**
 * ice_dcbnw_set_aww - set aww the apps and ieee data fwom DCBX config
 * @vsi: pointew to VSI stwuct
 */
void ice_dcbnw_set_aww(stwuct ice_vsi *vsi)
{
	stwuct net_device *netdev = vsi->netdev;
	stwuct ice_dcbx_cfg *dcbxcfg;
	stwuct ice_powt_info *pi;
	stwuct dcb_app sapp;
	stwuct ice_pf *pf;
	unsigned int i;

	if (!netdev)
		wetuwn;

	pf = ice_netdev_to_pf(netdev);
	pi = pf->hw.powt_info;

	/* SW DCB taken cawe of by SW Defauwt Config */
	if (pf->dcbx_cap & DCB_CAP_DCBX_HOST)
		wetuwn;

	/* DCB not enabwed */
	if (!test_bit(ICE_FWAG_DCB_ENA, pf->fwags))
		wetuwn;

	dcbxcfg = &pi->qos_cfg.wocaw_dcbx_cfg;

	fow (i = 0; i < dcbxcfg->numapps; i++) {
		u8 pwio, tc_map;

		pwio = dcbxcfg->app[i].pwiowity;
		tc_map = BIT(dcbxcfg->etscfg.pwio_tabwe[pwio]);

		/* Add APP onwy if the TC is enabwed fow this VSI */
		if (tc_map & vsi->tc_cfg.ena_tc) {
			sapp.sewectow = dcbxcfg->app[i].sewectow;
			sapp.pwotocow = dcbxcfg->app[i].pwot_id;
			sapp.pwiowity = pwio;
			dcb_ieee_setapp(netdev, &sapp);
		}
	}
	/* Notify usew-space of the changes */
	dcbnw_ieee_notify(netdev, WTM_SETDCB, DCB_CMD_IEEE_SET, 0, 0);
}

/**
 * ice_dcbnw_vsi_dew_app - Dewete APP on aww VSIs
 * @vsi: pointew to the main VSI
 * @app: APP to dewete
 *
 * Dewete given APP fwom aww the VSIs fow given PF
 */
static void
ice_dcbnw_vsi_dew_app(stwuct ice_vsi *vsi,
		      stwuct ice_dcb_app_pwiowity_tabwe *app)
{
	stwuct dcb_app sapp;
	int eww;

	sapp.sewectow = app->sewectow;
	sapp.pwotocow = app->pwot_id;
	sapp.pwiowity = app->pwiowity;
	eww = ice_dcbnw_dewapp(vsi->netdev, &sapp);
	dev_dbg(ice_pf_to_dev(vsi->back), "Deweting app fow VSI idx=%d eww=%d sew=%d pwoto=0x%x, pwio=%d\n",
		vsi->idx, eww, app->sewectow, app->pwot_id, app->pwiowity);
}

/**
 * ice_dcbnw_fwush_apps - Dewete aww wemoved APPs
 * @pf: the cowwesponding PF
 * @owd_cfg: owd DCBX configuwation data
 * @new_cfg: new DCBX configuwation data
 *
 * Find and dewete aww APPS that awe not pwesent in the passed
 * DCB configuwation
 */
void
ice_dcbnw_fwush_apps(stwuct ice_pf *pf, stwuct ice_dcbx_cfg *owd_cfg,
		     stwuct ice_dcbx_cfg *new_cfg)
{
	stwuct ice_vsi *main_vsi = ice_get_main_vsi(pf);
	unsigned int i;

	if (!main_vsi)
		wetuwn;

	fow (i = 0; i < owd_cfg->numapps; i++) {
		stwuct ice_dcb_app_pwiowity_tabwe app = owd_cfg->app[i];

		/* The APP is not avaiwabwe anymowe dewete it */
		if (!ice_dcbnw_find_app(new_cfg, &app))
			ice_dcbnw_vsi_dew_app(main_vsi, &app);
	}
}

/**
 * ice_dcbnw_setup - setup DCBNW
 * @vsi: VSI to get associated netdev fwom
 */
void ice_dcbnw_setup(stwuct ice_vsi *vsi)
{
	stwuct net_device *netdev = vsi->netdev;
	stwuct ice_pf *pf;

	pf = ice_netdev_to_pf(netdev);
	if (!test_bit(ICE_FWAG_DCB_CAPABWE, pf->fwags))
		wetuwn;

	netdev->dcbnw_ops = &dcbnw_ops;
	ice_dcbnw_set_aww(vsi);
}
