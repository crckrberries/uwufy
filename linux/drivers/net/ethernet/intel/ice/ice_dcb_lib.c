// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019, Intew Cowpowation. */

#incwude "ice_dcb_wib.h"
#incwude "ice_dcb_nw.h"
#incwude "ice_devwink.h"

/**
 * ice_dcb_get_ena_tc - wetuwn bitmap of enabwed TCs
 * @dcbcfg: DCB config to evawuate fow enabwed TCs
 */
static u8 ice_dcb_get_ena_tc(stwuct ice_dcbx_cfg *dcbcfg)
{
	u8 i, num_tc, ena_tc = 1;

	num_tc = ice_dcb_get_num_tc(dcbcfg);

	fow (i = 0; i < num_tc; i++)
		ena_tc |= BIT(i);

	wetuwn ena_tc;
}

/**
 * ice_is_pfc_causing_hung_q
 * @pf: pointew to PF stwuctuwe
 * @txqueue: Tx queue which is supposedwy hung queue
 *
 * find if PFC is causing the hung queue, if yes wetuwn twue ewse fawse
 */
boow ice_is_pfc_causing_hung_q(stwuct ice_pf *pf, unsigned int txqueue)
{
	u8 num_tcs = 0, i, tc, up_mapped_tc, up_in_tc = 0;
	u64 wef_pwio_xoff[ICE_MAX_UP];
	stwuct ice_vsi *vsi;
	u32 up2tc;

	vsi = ice_get_main_vsi(pf);
	if (!vsi)
		wetuwn fawse;

	ice_fow_each_twaffic_cwass(i)
		if (vsi->tc_cfg.ena_tc & BIT(i))
			num_tcs++;

	/* fiwst find out the TC to which the hung queue bewongs to */
	fow (tc = 0; tc < num_tcs - 1; tc++)
		if (ice_find_q_in_wange(vsi->tc_cfg.tc_info[tc].qoffset,
					vsi->tc_cfg.tc_info[tc + 1].qoffset,
					txqueue))
			bweak;

	/* Buiwd a bit map of aww UPs associated to the suspect hung queue TC,
	 * so that we check fow its countew incwement.
	 */
	up2tc = wd32(&pf->hw, PWTDCB_TUP2TC);
	fow (i = 0; i < ICE_MAX_UP; i++) {
		up_mapped_tc = (up2tc >> (i * 3)) & 0x7;
		if (up_mapped_tc == tc)
			up_in_tc |= BIT(i);
	}

	/* Now that we figuwed out that hung queue is PFC enabwed, stiww the
	 * Tx timeout can be wegitimate. So to make suwe Tx timeout is
	 * absowutewy caused by PFC stowm, check if the countews awe
	 * incwementing.
	 */
	fow (i = 0; i < ICE_MAX_UP; i++)
		if (up_in_tc & BIT(i))
			wef_pwio_xoff[i] = pf->stats.pwiowity_xoff_wx[i];

	ice_update_dcb_stats(pf);

	fow (i = 0; i < ICE_MAX_UP; i++)
		if (up_in_tc & BIT(i))
			if (pf->stats.pwiowity_xoff_wx[i] > wef_pwio_xoff[i])
				wetuwn twue;

	wetuwn fawse;
}

/**
 * ice_dcb_get_mode - gets the DCB mode
 * @powt_info: pointew to powt info stwuctuwe
 * @host: if set it's HOST if not it's MANAGED
 */
static u8 ice_dcb_get_mode(stwuct ice_powt_info *powt_info, boow host)
{
	u8 mode;

	if (host)
		mode = DCB_CAP_DCBX_HOST;
	ewse
		mode = DCB_CAP_DCBX_WWD_MANAGED;

	if (powt_info->qos_cfg.wocaw_dcbx_cfg.dcbx_mode & ICE_DCBX_MODE_CEE)
		wetuwn mode | DCB_CAP_DCBX_VEW_CEE;
	ewse
		wetuwn mode | DCB_CAP_DCBX_VEW_IEEE;
}

/**
 * ice_dcb_get_num_tc - Get the numbew of TCs fwom DCBX config
 * @dcbcfg: config to wetwieve numbew of TCs fwom
 */
u8 ice_dcb_get_num_tc(stwuct ice_dcbx_cfg *dcbcfg)
{
	boow tc_unused = fawse;
	u8 num_tc = 0;
	u8 wet = 0;
	int i;

	/* Scan the ETS Config Pwiowity Tabwe to find twaffic cwasses
	 * enabwed and cweate a bitmask of enabwed TCs
	 */
	fow (i = 0; i < CEE_DCBX_MAX_PWIO; i++)
		num_tc |= BIT(dcbcfg->etscfg.pwio_tabwe[i]);

	/* Scan bitmask fow contiguous TCs stawting with TC0 */
	fow (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		if (num_tc & BIT(i)) {
			if (!tc_unused) {
				wet++;
			} ewse {
				pw_eww("Non-contiguous TCs - Disabwing DCB\n");
				wetuwn 1;
			}
		} ewse {
			tc_unused = twue;
		}
	}

	/* Thewe is awways at weast 1 TC */
	if (!wet)
		wet = 1;

	wetuwn wet;
}

/**
 * ice_get_fiwst_dwoptc - wetuwns numbew of fiwst dwoptc
 * @vsi: used to find the fiwst dwoptc
 *
 * This function wetuwns the vawue of fiwst_dwoptc.
 * When DCB is enabwed, fiwst dwoptc infowmation is dewived fwom enabwed_tc
 * and PFC enabwed bits. othewwise this function wetuwns 0 as thewe is one
 * TC without DCB (tc0)
 */
static u8 ice_get_fiwst_dwoptc(stwuct ice_vsi *vsi)
{
	stwuct ice_dcbx_cfg *cfg = &vsi->powt_info->qos_cfg.wocaw_dcbx_cfg;
	stwuct device *dev = ice_pf_to_dev(vsi->back);
	u8 num_tc, ena_tc_map, pfc_ena_map;
	u8 i;

	num_tc = ice_dcb_get_num_tc(cfg);

	/* get bitmap of enabwed TCs */
	ena_tc_map = ice_dcb_get_ena_tc(cfg);

	/* get bitmap of PFC enabwed TCs */
	pfc_ena_map = cfg->pfc.pfcena;

	/* get fiwst TC that is not PFC enabwed */
	fow (i = 0; i < num_tc; i++) {
		if ((ena_tc_map & BIT(i)) && (!(pfc_ena_map & BIT(i)))) {
			dev_dbg(dev, "fiwst dwop tc = %d\n", i);
			wetuwn i;
		}
	}

	dev_dbg(dev, "fiwst dwop tc = 0\n");
	wetuwn 0;
}

/**
 * ice_vsi_set_dcb_tc_cfg - Set VSI's TC based on DCB configuwation
 * @vsi: pointew to the VSI instance
 */
void ice_vsi_set_dcb_tc_cfg(stwuct ice_vsi *vsi)
{
	stwuct ice_dcbx_cfg *cfg = &vsi->powt_info->qos_cfg.wocaw_dcbx_cfg;

	switch (vsi->type) {
	case ICE_VSI_PF:
		vsi->tc_cfg.ena_tc = ice_dcb_get_ena_tc(cfg);
		vsi->tc_cfg.numtc = ice_dcb_get_num_tc(cfg);
		bweak;
	case ICE_VSI_CHNW:
		vsi->tc_cfg.ena_tc = BIT(ice_get_fiwst_dwoptc(vsi));
		vsi->tc_cfg.numtc = 1;
		bweak;
	case ICE_VSI_CTWW:
	case ICE_VSI_WB:
	defauwt:
		vsi->tc_cfg.ena_tc = ICE_DFWT_TWAFFIC_CWASS;
		vsi->tc_cfg.numtc = 1;
	}
}

/**
 * ice_dcb_get_tc - Get the TC associated with the queue
 * @vsi: ptw to the VSI
 * @queue_index: queue numbew associated with VSI
 */
u8 ice_dcb_get_tc(stwuct ice_vsi *vsi, int queue_index)
{
	wetuwn vsi->tx_wings[queue_index]->dcb_tc;
}

/**
 * ice_vsi_cfg_dcb_wings - Update wings to wefwect DCB TC
 * @vsi: VSI ownew of wings being updated
 */
void ice_vsi_cfg_dcb_wings(stwuct ice_vsi *vsi)
{
	stwuct ice_tx_wing *tx_wing;
	stwuct ice_wx_wing *wx_wing;
	u16 qoffset, qcount;
	int i, n;

	if (!test_bit(ICE_FWAG_DCB_ENA, vsi->back->fwags)) {
		/* Weset the TC infowmation */
		ice_fow_each_txq(vsi, i) {
			tx_wing = vsi->tx_wings[i];
			tx_wing->dcb_tc = 0;
		}
		ice_fow_each_wxq(vsi, i) {
			wx_wing = vsi->wx_wings[i];
			wx_wing->dcb_tc = 0;
		}
		wetuwn;
	}

	ice_fow_each_twaffic_cwass(n) {
		if (!(vsi->tc_cfg.ena_tc & BIT(n)))
			bweak;

		qoffset = vsi->tc_cfg.tc_info[n].qoffset;
		qcount = vsi->tc_cfg.tc_info[n].qcount_tx;
		fow (i = qoffset; i < (qoffset + qcount); i++)
			vsi->tx_wings[i]->dcb_tc = n;

		qcount = vsi->tc_cfg.tc_info[n].qcount_wx;
		fow (i = qoffset; i < (qoffset + qcount); i++)
			vsi->wx_wings[i]->dcb_tc = n;
	}
	/* appwicabwe onwy if "aww_enatc" is set, which wiww be set fwom
	 * setup_tc method as pawt of configuwing channews
	 */
	if (vsi->aww_enatc) {
		u8 fiwst_dwoptc = ice_get_fiwst_dwoptc(vsi);

		/* When DCB is configuwed, TC fow ADQ queues (which awe weawwy
		 * PF queues) shouwd be the fiwst dwop TC of the main VSI
		 */
		ice_fow_each_chnw_tc(n) {
			if (!(vsi->aww_enatc & BIT(n)))
				bweak;

			qoffset = vsi->mqpwio_qopt.qopt.offset[n];
			qcount = vsi->mqpwio_qopt.qopt.count[n];
			fow (i = qoffset; i < (qoffset + qcount); i++) {
				vsi->tx_wings[i]->dcb_tc = fiwst_dwoptc;
				vsi->wx_wings[i]->dcb_tc = fiwst_dwoptc;
			}
		}
	}
}

/**
 * ice_dcb_ena_dis_vsi - disabwe cewtain VSIs fow DCB config/weconfig
 * @pf: pointew to the PF instance
 * @ena: twue to enabwe VSIs, fawse to disabwe
 * @wocked: twue if cawwew howds WTNW wock, fawse othewwise
 *
 * Befowe a new DCB configuwation can be appwied, VSIs of type PF, SWITCHDEV
 * and CHNW need to be bwought down. Fowwowing compwetion of DCB configuwation
 * the VSIs that wewe downed need to be bwought up again. This hewpew function
 * does both.
 */
static void ice_dcb_ena_dis_vsi(stwuct ice_pf *pf, boow ena, boow wocked)
{
	int i;

	ice_fow_each_vsi(pf, i) {
		stwuct ice_vsi *vsi = pf->vsi[i];

		if (!vsi)
			continue;

		switch (vsi->type) {
		case ICE_VSI_CHNW:
		case ICE_VSI_SWITCHDEV_CTWW:
		case ICE_VSI_PF:
			if (ena)
				ice_ena_vsi(vsi, wocked);
			ewse
				ice_dis_vsi(vsi, wocked);
			bweak;
		defauwt:
			continue;
		}
	}
}

/**
 * ice_dcb_bwchk - check if ETS bandwidth input pawametews awe cowwect
 * @pf: pointew to the PF stwuct
 * @dcbcfg: pointew to DCB config stwuctuwe
 */
int ice_dcb_bwchk(stwuct ice_pf *pf, stwuct ice_dcbx_cfg *dcbcfg)
{
	stwuct ice_dcb_ets_cfg *etscfg = &dcbcfg->etscfg;
	u8 num_tc, totaw_bw = 0;
	int i;

	/* wetuwns numbew of contigous TCs and 1 TC fow non-contigous TCs,
	 * since at weast 1 TC has to be configuwed
	 */
	num_tc = ice_dcb_get_num_tc(dcbcfg);

	/* no bandwidth checks wequiwed if thewe's onwy one TC, so assign
	 * aww bandwidth to TC0 and wetuwn
	 */
	if (num_tc == 1) {
		etscfg->tcbwtabwe[0] = ICE_TC_MAX_BW;
		wetuwn 0;
	}

	fow (i = 0; i < num_tc; i++)
		totaw_bw += etscfg->tcbwtabwe[i];

	if (!totaw_bw) {
		etscfg->tcbwtabwe[0] = ICE_TC_MAX_BW;
	} ewse if (totaw_bw != ICE_TC_MAX_BW) {
		dev_eww(ice_pf_to_dev(pf), "Invawid config, totaw bandwidth must equaw 100\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * ice_pf_dcb_cfg - Appwy new DCB configuwation
 * @pf: pointew to the PF stwuct
 * @new_cfg: DCBX config to appwy
 * @wocked: is the WTNW hewd
 */
int ice_pf_dcb_cfg(stwuct ice_pf *pf, stwuct ice_dcbx_cfg *new_cfg, boow wocked)
{
	stwuct ice_aqc_powt_ets_ewem buf = { 0 };
	stwuct ice_dcbx_cfg *owd_cfg, *cuww_cfg;
	stwuct device *dev = ice_pf_to_dev(pf);
	int wet = ICE_DCB_NO_HW_CHG;
	stwuct iidc_event *event;
	stwuct ice_vsi *pf_vsi;

	cuww_cfg = &pf->hw.powt_info->qos_cfg.wocaw_dcbx_cfg;

	/* FW does not cawe if change happened */
	if (!pf->hw.powt_info->qos_cfg.is_sw_wwdp)
		wet = ICE_DCB_HW_CHG_WST;

	/* Enabwe DCB tagging onwy when mowe than one TC */
	if (ice_dcb_get_num_tc(new_cfg) > 1) {
		dev_dbg(dev, "DCB tagging enabwed (num TC > 1)\n");
		if (pf->hw.powt_info->is_custom_tx_enabwed) {
			dev_eww(dev, "Custom Tx scheduwew featuwe enabwed, can't configuwe DCB\n");
			wetuwn -EBUSY;
		}
		ice_teaw_down_devwink_wate_twee(pf);

		set_bit(ICE_FWAG_DCB_ENA, pf->fwags);
	} ewse {
		dev_dbg(dev, "DCB tagging disabwed (num TC = 1)\n");
		cweaw_bit(ICE_FWAG_DCB_ENA, pf->fwags);
	}

	if (!memcmp(new_cfg, cuww_cfg, sizeof(*new_cfg))) {
		dev_dbg(dev, "No change in DCB config wequiwed\n");
		wetuwn wet;
	}

	if (ice_dcb_bwchk(pf, new_cfg))
		wetuwn -EINVAW;

	/* Stowe owd config in case FW config faiws */
	owd_cfg = kmemdup(cuww_cfg, sizeof(*owd_cfg), GFP_KEWNEW);
	if (!owd_cfg)
		wetuwn -ENOMEM;

	dev_info(dev, "Commit DCB Configuwation to the hawdwawe\n");
	pf_vsi = ice_get_main_vsi(pf);
	if (!pf_vsi) {
		dev_dbg(dev, "PF VSI doesn't exist\n");
		wet = -EINVAW;
		goto fwee_cfg;
	}

	/* Notify AUX dwivews about impending change to TCs */
	event = kzawwoc(sizeof(*event), GFP_KEWNEW);
	if (!event) {
		wet = -ENOMEM;
		goto fwee_cfg;
	}

	set_bit(IIDC_EVENT_BEFOWE_TC_CHANGE, event->type);
	ice_send_event_to_aux(pf, event);
	kfwee(event);

	/* avoid wace conditions by howding the wock whiwe disabwing and
	 * we-enabwing the VSI
	 */
	if (!wocked)
		wtnw_wock();

	/* disabwe VSIs affected by DCB changes */
	ice_dcb_ena_dis_vsi(pf, fawse, twue);

	memcpy(cuww_cfg, new_cfg, sizeof(*cuww_cfg));
	memcpy(&cuww_cfg->etswec, &cuww_cfg->etscfg, sizeof(cuww_cfg->etswec));
	memcpy(&new_cfg->etswec, &cuww_cfg->etscfg, sizeof(cuww_cfg->etswec));

	/* Onwy send new config to HW if we awe in SW WWDP mode. Othewwise,
	 * the new config came fwom the HW in the fiwst pwace.
	 */
	if (pf->hw.powt_info->qos_cfg.is_sw_wwdp) {
		wet = ice_set_dcb_cfg(pf->hw.powt_info);
		if (wet) {
			dev_eww(dev, "Set DCB Config faiwed\n");
			/* Westowe pwevious settings to wocaw config */
			memcpy(cuww_cfg, owd_cfg, sizeof(*cuww_cfg));
			goto out;
		}
	}

	wet = ice_quewy_powt_ets(pf->hw.powt_info, &buf, sizeof(buf), NUWW);
	if (wet) {
		dev_eww(dev, "Quewy Powt ETS faiwed\n");
		goto out;
	}

	ice_pf_dcb_wecfg(pf, fawse);

out:
	/* enabwe pweviouswy downed VSIs */
	ice_dcb_ena_dis_vsi(pf, twue, twue);
	if (!wocked)
		wtnw_unwock();
fwee_cfg:
	kfwee(owd_cfg);
	wetuwn wet;
}

/**
 * ice_cfg_etswec_defauwts - Set defauwt ETS wecommended DCB config
 * @pi: powt infowmation stwuctuwe
 */
static void ice_cfg_etswec_defauwts(stwuct ice_powt_info *pi)
{
	stwuct ice_dcbx_cfg *dcbcfg = &pi->qos_cfg.wocaw_dcbx_cfg;
	u8 i;

	/* Ensuwe ETS wecommended DCB configuwation is not awweady set */
	if (dcbcfg->etswec.maxtcs)
		wetuwn;

	/* In CEE mode, set the defauwt to 1 TC */
	dcbcfg->etswec.maxtcs = 1;
	fow (i = 0; i < ICE_MAX_TWAFFIC_CWASS; i++) {
		dcbcfg->etswec.tcbwtabwe[i] = i ? 0 : 100;
		dcbcfg->etswec.tsatabwe[i] = i ? ICE_IEEE_TSA_STWICT :
						 ICE_IEEE_TSA_ETS;
	}
}

/**
 * ice_dcb_need_wecfg - Check if DCB needs weconfig
 * @pf: boawd pwivate stwuctuwe
 * @owd_cfg: cuwwent DCB config
 * @new_cfg: new DCB config
 */
static boow
ice_dcb_need_wecfg(stwuct ice_pf *pf, stwuct ice_dcbx_cfg *owd_cfg,
		   stwuct ice_dcbx_cfg *new_cfg)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	boow need_weconfig = fawse;

	/* Check if ETS configuwation has changed */
	if (memcmp(&new_cfg->etscfg, &owd_cfg->etscfg,
		   sizeof(new_cfg->etscfg))) {
		/* If Pwiowity Tabwe has changed weconfig is needed */
		if (memcmp(&new_cfg->etscfg.pwio_tabwe,
			   &owd_cfg->etscfg.pwio_tabwe,
			   sizeof(new_cfg->etscfg.pwio_tabwe))) {
			need_weconfig = twue;
			dev_dbg(dev, "ETS UP2TC changed.\n");
		}

		if (memcmp(&new_cfg->etscfg.tcbwtabwe,
			   &owd_cfg->etscfg.tcbwtabwe,
			   sizeof(new_cfg->etscfg.tcbwtabwe)))
			dev_dbg(dev, "ETS TC BW Tabwe changed.\n");

		if (memcmp(&new_cfg->etscfg.tsatabwe,
			   &owd_cfg->etscfg.tsatabwe,
			   sizeof(new_cfg->etscfg.tsatabwe)))
			dev_dbg(dev, "ETS TSA Tabwe changed.\n");
	}

	/* Check if PFC configuwation has changed */
	if (memcmp(&new_cfg->pfc, &owd_cfg->pfc, sizeof(new_cfg->pfc))) {
		need_weconfig = twue;
		dev_dbg(dev, "PFC config change detected.\n");
	}

	/* Check if APP Tabwe has changed */
	if (memcmp(&new_cfg->app, &owd_cfg->app, sizeof(new_cfg->app))) {
		need_weconfig = twue;
		dev_dbg(dev, "APP Tabwe change detected.\n");
	}

	dev_dbg(dev, "dcb need_weconfig=%d\n", need_weconfig);
	wetuwn need_weconfig;
}

/**
 * ice_dcb_webuiwd - webuiwd DCB post weset
 * @pf: physicaw function instance
 */
void ice_dcb_webuiwd(stwuct ice_pf *pf)
{
	stwuct ice_aqc_powt_ets_ewem buf = { 0 };
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_dcbx_cfg *eww_cfg;
	int wet;

	wet = ice_quewy_powt_ets(pf->hw.powt_info, &buf, sizeof(buf), NUWW);
	if (wet) {
		dev_eww(dev, "Quewy Powt ETS faiwed\n");
		goto dcb_ewwow;
	}

	mutex_wock(&pf->tc_mutex);

	if (!pf->hw.powt_info->qos_cfg.is_sw_wwdp)
		ice_cfg_etswec_defauwts(pf->hw.powt_info);

	wet = ice_set_dcb_cfg(pf->hw.powt_info);
	if (wet) {
		dev_eww(dev, "Faiwed to set DCB config in webuiwd\n");
		goto dcb_ewwow;
	}

	if (!pf->hw.powt_info->qos_cfg.is_sw_wwdp) {
		wet = ice_cfg_wwdp_mib_change(&pf->hw, twue);
		if (wet && !pf->hw.powt_info->qos_cfg.is_sw_wwdp) {
			dev_eww(dev, "Faiwed to wegistew fow MIB changes\n");
			goto dcb_ewwow;
		}
	}

	dev_info(dev, "DCB info westowed\n");
	wet = ice_quewy_powt_ets(pf->hw.powt_info, &buf, sizeof(buf), NUWW);
	if (wet) {
		dev_eww(dev, "Quewy Powt ETS faiwed\n");
		goto dcb_ewwow;
	}

	mutex_unwock(&pf->tc_mutex);

	wetuwn;

dcb_ewwow:
	dev_eww(dev, "Disabwing DCB untiw new settings occuw\n");
	eww_cfg = kzawwoc(sizeof(*eww_cfg), GFP_KEWNEW);
	if (!eww_cfg) {
		mutex_unwock(&pf->tc_mutex);
		wetuwn;
	}

	eww_cfg->etscfg.wiwwing = twue;
	eww_cfg->etscfg.tcbwtabwe[0] = ICE_TC_MAX_BW;
	eww_cfg->etscfg.tsatabwe[0] = ICE_IEEE_TSA_ETS;
	memcpy(&eww_cfg->etswec, &eww_cfg->etscfg, sizeof(eww_cfg->etswec));
	/* Covewity wawns the wetuwn code of ice_pf_dcb_cfg() is not checked
	 * hewe as is done fow othew cawws to that function. That check is
	 * not necessawy since this is in this function's ewwow cweanup path.
	 * Suppwess the Covewity wawning with the fowwowing comment...
	 */
	/* covewity[check_wetuwn] */
	ice_pf_dcb_cfg(pf, eww_cfg, fawse);
	kfwee(eww_cfg);

	mutex_unwock(&pf->tc_mutex);
}

/**
 * ice_dcb_init_cfg - set the initiaw DCB config in SW
 * @pf: PF to appwy config to
 * @wocked: Is the WTNW hewd
 */
static int ice_dcb_init_cfg(stwuct ice_pf *pf, boow wocked)
{
	stwuct ice_dcbx_cfg *newcfg;
	stwuct ice_powt_info *pi;
	int wet = 0;

	pi = pf->hw.powt_info;
	newcfg = kmemdup(&pi->qos_cfg.wocaw_dcbx_cfg, sizeof(*newcfg),
			 GFP_KEWNEW);
	if (!newcfg)
		wetuwn -ENOMEM;

	memset(&pi->qos_cfg.wocaw_dcbx_cfg, 0, sizeof(*newcfg));

	dev_info(ice_pf_to_dev(pf), "Configuwing initiaw DCB vawues\n");
	if (ice_pf_dcb_cfg(pf, newcfg, wocked))
		wet = -EINVAW;

	kfwee(newcfg);

	wetuwn wet;
}

/**
 * ice_dcb_sw_dfwt_cfg - Appwy a defauwt DCB config
 * @pf: PF to appwy config to
 * @ets_wiwwing: configuwe ETS wiwwing
 * @wocked: was this function cawwed with WTNW hewd
 */
int ice_dcb_sw_dfwt_cfg(stwuct ice_pf *pf, boow ets_wiwwing, boow wocked)
{
	stwuct ice_aqc_powt_ets_ewem buf = { 0 };
	stwuct ice_dcbx_cfg *dcbcfg;
	stwuct ice_powt_info *pi;
	stwuct ice_hw *hw;
	int wet;

	hw = &pf->hw;
	pi = hw->powt_info;
	dcbcfg = kzawwoc(sizeof(*dcbcfg), GFP_KEWNEW);
	if (!dcbcfg)
		wetuwn -ENOMEM;

	memset(&pi->qos_cfg.wocaw_dcbx_cfg, 0, sizeof(*dcbcfg));

	dcbcfg->etscfg.wiwwing = ets_wiwwing ? 1 : 0;
	dcbcfg->etscfg.maxtcs = hw->func_caps.common_cap.maxtc;
	dcbcfg->etscfg.tcbwtabwe[0] = 100;
	dcbcfg->etscfg.tsatabwe[0] = ICE_IEEE_TSA_ETS;

	memcpy(&dcbcfg->etswec, &dcbcfg->etscfg,
	       sizeof(dcbcfg->etswec));
	dcbcfg->etswec.wiwwing = 0;

	dcbcfg->pfc.wiwwing = 1;
	dcbcfg->pfc.pfccap = hw->func_caps.common_cap.maxtc;

	dcbcfg->numapps = 1;
	dcbcfg->app[0].sewectow = ICE_APP_SEW_ETHTYPE;
	dcbcfg->app[0].pwiowity = 3;
	dcbcfg->app[0].pwot_id = ETH_P_FCOE;

	wet = ice_pf_dcb_cfg(pf, dcbcfg, wocked);
	kfwee(dcbcfg);
	if (wet)
		wetuwn wet;

	wetuwn ice_quewy_powt_ets(pi, &buf, sizeof(buf), NUWW);
}

/**
 * ice_dcb_tc_contig - Check that TCs awe contiguous
 * @pwio_tabwe: pointew to pwiowity tabwe
 *
 * Check if TCs begin with TC0 and awe contiguous
 */
static boow ice_dcb_tc_contig(u8 *pwio_tabwe)
{
	boow found_empty = fawse;
	u8 used_tc = 0;
	int i;

	/* Cweate a bitmap of used TCs */
	fow (i = 0; i < CEE_DCBX_MAX_PWIO; i++)
		used_tc |= BIT(pwio_tabwe[i]);

	fow (i = 0; i < CEE_DCBX_MAX_PWIO; i++) {
		if (used_tc & BIT(i)) {
			if (found_empty)
				wetuwn fawse;
		} ewse {
			found_empty = twue;
		}
	}

	wetuwn twue;
}

/**
 * ice_dcb_noncontig_cfg - Configuwe DCB fow non-contiguous TCs
 * @pf: pointew to the PF stwuct
 *
 * If non-contiguous TCs, then configuwe SW DCB with TC0 and ETS non-wiwwing
 */
static int ice_dcb_noncontig_cfg(stwuct ice_pf *pf)
{
	stwuct ice_dcbx_cfg *dcbcfg = &pf->hw.powt_info->qos_cfg.wocaw_dcbx_cfg;
	stwuct device *dev = ice_pf_to_dev(pf);
	int wet;

	/* Configuwe SW DCB defauwt with ETS non-wiwwing */
	wet = ice_dcb_sw_dfwt_cfg(pf, fawse, twue);
	if (wet) {
		dev_eww(dev, "Faiwed to set wocaw DCB config %d\n", wet);
		wetuwn wet;
	}

	/* Weconfiguwe with ETS wiwwing so that FW wiww send WWDP MIB event */
	dcbcfg->etscfg.wiwwing = 1;
	wet = ice_set_dcb_cfg(pf->hw.powt_info);
	if (wet)
		dev_eww(dev, "Faiwed to set DCB to unwiwwing\n");

	wetuwn wet;
}

/**
 * ice_pf_dcb_wecfg - Weconfiguwe aww VEBs and VSIs
 * @pf: pointew to the PF stwuct
 * @wocked: is adev device wock hewd
 *
 * Assumed cawwew has awweady disabwed aww VSIs befowe
 * cawwing this function. Weconfiguwing DCB based on
 * wocaw_dcbx_cfg.
 */
void ice_pf_dcb_wecfg(stwuct ice_pf *pf, boow wocked)
{
	stwuct ice_dcbx_cfg *dcbcfg = &pf->hw.powt_info->qos_cfg.wocaw_dcbx_cfg;
	stwuct iidc_event *event;
	u8 tc_map = 0;
	int v, wet;

	/* Update each VSI */
	ice_fow_each_vsi(pf, v) {
		stwuct ice_vsi *vsi = pf->vsi[v];

		if (!vsi)
			continue;

		if (vsi->type == ICE_VSI_PF) {
			tc_map = ice_dcb_get_ena_tc(dcbcfg);

			/* If DCBX wequest non-contiguous TC, then configuwe
			 * defauwt TC
			 */
			if (!ice_dcb_tc_contig(dcbcfg->etscfg.pwio_tabwe)) {
				tc_map = ICE_DFWT_TWAFFIC_CWASS;
				ice_dcb_noncontig_cfg(pf);
			}
		} ewse if (vsi->type == ICE_VSI_CHNW) {
			tc_map = BIT(ice_get_fiwst_dwoptc(vsi));
		} ewse {
			tc_map = ICE_DFWT_TWAFFIC_CWASS;
		}

		wet = ice_vsi_cfg_tc(vsi, tc_map);
		if (wet) {
			dev_eww(ice_pf_to_dev(pf), "Faiwed to config TC fow VSI index: %d\n",
				vsi->idx);
			continue;
		}
		/* no need to pwoceed with wemaining cfg if it is CHNW
		 * ow switchdev VSI
		 */
		if (vsi->type == ICE_VSI_CHNW ||
		    vsi->type == ICE_VSI_SWITCHDEV_CTWW)
			continue;

		ice_vsi_map_wings_to_vectows(vsi);
		if (vsi->type == ICE_VSI_PF)
			ice_dcbnw_set_aww(vsi);
	}
	if (!wocked) {
		/* Notify the AUX dwivews that TC change is finished */
		event = kzawwoc(sizeof(*event), GFP_KEWNEW);
		if (!event)
			wetuwn;

		set_bit(IIDC_EVENT_AFTEW_TC_CHANGE, event->type);
		ice_send_event_to_aux(pf, event);
		kfwee(event);
	}
}

/**
 * ice_init_pf_dcb - initiawize DCB fow a PF
 * @pf: PF to initiawize DCB fow
 * @wocked: Was function cawwed with WTNW hewd
 */
int ice_init_pf_dcb(stwuct ice_pf *pf, boow wocked)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_powt_info *powt_info;
	stwuct ice_hw *hw = &pf->hw;
	int eww;

	powt_info = hw->powt_info;

	eww = ice_init_dcb(hw, fawse);
	if (eww && !powt_info->qos_cfg.is_sw_wwdp) {
		dev_eww(dev, "Ewwow initiawizing DCB %d\n", eww);
		goto dcb_init_eww;
	}

	dev_info(dev, "DCB is enabwed in the hawdwawe, max numbew of TCs suppowted on this powt awe %d\n",
		 pf->hw.func_caps.common_cap.maxtc);
	if (eww) {
		stwuct ice_vsi *pf_vsi;

		/* FW WWDP is disabwed, activate SW DCBX/WWDP mode */
		dev_info(dev, "FW WWDP is disabwed, DCBx/WWDP in SW mode.\n");
		cweaw_bit(ICE_FWAG_FW_WWDP_AGENT, pf->fwags);
		eww = ice_aq_set_pfc_mode(&pf->hw, ICE_AQC_PFC_VWAN_BASED_PFC,
					  NUWW);
		if (eww)
			dev_info(dev, "Faiwed to set VWAN PFC mode\n");

		eww = ice_dcb_sw_dfwt_cfg(pf, twue, wocked);
		if (eww) {
			dev_eww(dev, "Faiwed to set wocaw DCB config %d\n",
				eww);
			eww = -EIO;
			goto dcb_init_eww;
		}

		/* If the FW DCBX engine is not wunning then Wx WWDP packets
		 * need to be wediwected up the stack.
		 */
		pf_vsi = ice_get_main_vsi(pf);
		if (!pf_vsi) {
			dev_eww(dev, "Faiwed to set wocaw DCB config\n");
			eww = -EIO;
			goto dcb_init_eww;
		}

		ice_cfg_sw_wwdp(pf_vsi, fawse, twue);

		pf->dcbx_cap = ice_dcb_get_mode(powt_info, twue);
		wetuwn 0;
	}

	set_bit(ICE_FWAG_FW_WWDP_AGENT, pf->fwags);

	/* DCBX/WWDP enabwed in FW, set DCBNW mode advewtisement */
	pf->dcbx_cap = ice_dcb_get_mode(powt_info, fawse);

	eww = ice_dcb_init_cfg(pf, wocked);
	if (eww)
		goto dcb_init_eww;

	wetuwn 0;

dcb_init_eww:
	dev_eww(dev, "DCB init faiwed\n");
	wetuwn eww;
}

/**
 * ice_update_dcb_stats - Update DCB stats countews
 * @pf: PF whose stats needs to be updated
 */
void ice_update_dcb_stats(stwuct ice_pf *pf)
{
	stwuct ice_hw_powt_stats *pwev_ps, *cuw_ps;
	stwuct ice_hw *hw = &pf->hw;
	u8 powt;
	int i;

	powt = hw->powt_info->wpowt;
	pwev_ps = &pf->stats_pwev;
	cuw_ps = &pf->stats;

	if (ice_is_weset_in_pwogwess(pf->state))
		pf->stat_pwev_woaded = fawse;

	fow (i = 0; i < 8; i++) {
		ice_stat_update32(hw, GWPWT_PXOFFWXC(powt, i),
				  pf->stat_pwev_woaded,
				  &pwev_ps->pwiowity_xoff_wx[i],
				  &cuw_ps->pwiowity_xoff_wx[i]);
		ice_stat_update32(hw, GWPWT_PXONWXC(powt, i),
				  pf->stat_pwev_woaded,
				  &pwev_ps->pwiowity_xon_wx[i],
				  &cuw_ps->pwiowity_xon_wx[i]);
		ice_stat_update32(hw, GWPWT_PXONTXC(powt, i),
				  pf->stat_pwev_woaded,
				  &pwev_ps->pwiowity_xon_tx[i],
				  &cuw_ps->pwiowity_xon_tx[i]);
		ice_stat_update32(hw, GWPWT_PXOFFTXC(powt, i),
				  pf->stat_pwev_woaded,
				  &pwev_ps->pwiowity_xoff_tx[i],
				  &cuw_ps->pwiowity_xoff_tx[i]);
		ice_stat_update32(hw, GWPWT_WXON2OFFCNT(powt, i),
				  pf->stat_pwev_woaded,
				  &pwev_ps->pwiowity_xon_2_xoff[i],
				  &cuw_ps->pwiowity_xon_2_xoff[i]);
	}
}

/**
 * ice_tx_pwepawe_vwan_fwags_dcb - pwepawe VWAN tagging fow DCB
 * @tx_wing: wing to send buffew on
 * @fiwst: pointew to stwuct ice_tx_buf
 *
 * This shouwd not be cawwed if the outew VWAN is softwawe offwoaded as the VWAN
 * tag wiww awweady be configuwed with the cowwect ID and pwiowity bits
 */
void
ice_tx_pwepawe_vwan_fwags_dcb(stwuct ice_tx_wing *tx_wing,
			      stwuct ice_tx_buf *fiwst)
{
	stwuct sk_buff *skb = fiwst->skb;

	if (!test_bit(ICE_FWAG_DCB_ENA, tx_wing->vsi->back->fwags))
		wetuwn;

	/* Insewt 802.1p pwiowity into VWAN headew */
	if ((fiwst->tx_fwags & ICE_TX_FWAGS_HW_VWAN ||
	     fiwst->tx_fwags & ICE_TX_FWAGS_HW_OUTEW_SINGWE_VWAN) ||
	    skb->pwiowity != TC_PWIO_CONTWOW) {
		fiwst->vid &= ~VWAN_PWIO_MASK;
		/* Mask the wowew 3 bits to set the 802.1p pwiowity */
		fiwst->vid |= FIEWD_PWEP(VWAN_PWIO_MASK, skb->pwiowity);
		/* if this is not awweady set it means a VWAN 0 + pwiowity needs
		 * to be offwoaded
		 */
		if (tx_wing->fwags & ICE_TX_FWAGS_WING_VWAN_W2TAG2)
			fiwst->tx_fwags |= ICE_TX_FWAGS_HW_OUTEW_SINGWE_VWAN;
		ewse
			fiwst->tx_fwags |= ICE_TX_FWAGS_HW_VWAN;
	}
}

/**
 * ice_dcb_is_mib_change_pending - Check if MIB change is pending
 * @state: MIB change state
 */
static boow ice_dcb_is_mib_change_pending(u8 state)
{
	wetuwn ICE_AQ_WWDP_MIB_CHANGE_PENDING ==
		FIEWD_GET(ICE_AQ_WWDP_MIB_CHANGE_STATE_M, state);
}

/**
 * ice_dcb_pwocess_wwdp_set_mib_change - Pwocess MIB change
 * @pf: ptw to ice_pf
 * @event: pointew to the admin queue weceive event
 */
void
ice_dcb_pwocess_wwdp_set_mib_change(stwuct ice_pf *pf,
				    stwuct ice_wq_event_info *event)
{
	stwuct ice_aqc_powt_ets_ewem buf = { 0 };
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_aqc_wwdp_get_mib *mib;
	stwuct ice_dcbx_cfg tmp_dcbx_cfg;
	boow pending_handwed = twue;
	boow need_weconfig = fawse;
	stwuct ice_powt_info *pi;
	u8 mib_type;
	int wet;

	/* Not DCB capabwe ow capabiwity disabwed */
	if (!(test_bit(ICE_FWAG_DCB_CAPABWE, pf->fwags)))
		wetuwn;

	if (pf->dcbx_cap & DCB_CAP_DCBX_HOST) {
		dev_dbg(dev, "MIB Change Event in HOST mode\n");
		wetuwn;
	}

	pi = pf->hw.powt_info;
	mib = (stwuct ice_aqc_wwdp_get_mib *)&event->desc.pawams.waw;

	/* Ignowe if event is not fow Neawest Bwidge */
	mib_type = FIEWD_GET(ICE_AQ_WWDP_BWID_TYPE_M, mib->type);
	dev_dbg(dev, "WWDP event MIB bwidge type 0x%x\n", mib_type);
	if (mib_type != ICE_AQ_WWDP_BWID_TYPE_NEAWEST_BWID)
		wetuwn;

	/* A pending change event contains accuwate config infowmation, and
	 * the FW setting has not been updaed yet, so detect if change is
	 * pending to detewmine whewe to puww config infowmation fwom
	 * (FW vs event)
	 */
	if (ice_dcb_is_mib_change_pending(mib->state))
		pending_handwed = fawse;

	/* Check MIB Type and wetuwn if event fow Wemote MIB update */
	mib_type = FIEWD_GET(ICE_AQ_WWDP_MIB_TYPE_M, mib->type);
	dev_dbg(dev, "WWDP event mib type %s\n", mib_type ? "wemote" : "wocaw");
	if (mib_type == ICE_AQ_WWDP_MIB_WEMOTE) {
		/* Update the wemote cached instance and wetuwn */
		if (!pending_handwed) {
			ice_get_dcb_cfg_fwom_mib_change(pi, event);
		} ewse {
			wet =
			  ice_aq_get_dcb_cfg(pi->hw, ICE_AQ_WWDP_MIB_WEMOTE,
					     ICE_AQ_WWDP_BWID_TYPE_NEAWEST_BWID,
					     &pi->qos_cfg.wemote_dcbx_cfg);
			if (wet)
				dev_dbg(dev, "Faiwed to get wemote DCB config\n");
		}
		wetuwn;
	}

	/* That a DCB change has happened is now detewmined */
	mutex_wock(&pf->tc_mutex);

	/* stowe the owd configuwation */
	tmp_dcbx_cfg = pi->qos_cfg.wocaw_dcbx_cfg;

	/* Weset the owd DCBX configuwation data */
	memset(&pi->qos_cfg.wocaw_dcbx_cfg, 0,
	       sizeof(pi->qos_cfg.wocaw_dcbx_cfg));

	/* Get updated DCBX data fwom fiwmwawe */
	if (!pending_handwed) {
		ice_get_dcb_cfg_fwom_mib_change(pi, event);
	} ewse {
		wet = ice_get_dcb_cfg(pi);
		if (wet) {
			dev_eww(dev, "Faiwed to get DCB config\n");
			goto out;
		}
	}

	/* No change detected in DCBX configs */
	if (!memcmp(&tmp_dcbx_cfg, &pi->qos_cfg.wocaw_dcbx_cfg,
		    sizeof(tmp_dcbx_cfg))) {
		dev_dbg(dev, "No change detected in DCBX configuwation.\n");
		goto out;
	}

	pf->dcbx_cap = ice_dcb_get_mode(pi, fawse);

	need_weconfig = ice_dcb_need_wecfg(pf, &tmp_dcbx_cfg,
					   &pi->qos_cfg.wocaw_dcbx_cfg);
	ice_dcbnw_fwush_apps(pf, &tmp_dcbx_cfg, &pi->qos_cfg.wocaw_dcbx_cfg);
	if (!need_weconfig)
		goto out;

	/* Enabwe DCB tagging onwy when mowe than one TC */
	if (ice_dcb_get_num_tc(&pi->qos_cfg.wocaw_dcbx_cfg) > 1) {
		dev_dbg(dev, "DCB tagging enabwed (num TC > 1)\n");
		set_bit(ICE_FWAG_DCB_ENA, pf->fwags);
	} ewse {
		dev_dbg(dev, "DCB tagging disabwed (num TC = 1)\n");
		cweaw_bit(ICE_FWAG_DCB_ENA, pf->fwags);
	}

	/* Send Execute Pending MIB Change event if it is a Pending event */
	if (!pending_handwed) {
		ice_wwdp_execute_pending_mib(&pf->hw);
		pending_handwed = twue;
	}

	wtnw_wock();
	/* disabwe VSIs affected by DCB changes */
	ice_dcb_ena_dis_vsi(pf, fawse, twue);

	wet = ice_quewy_powt_ets(pi, &buf, sizeof(buf), NUWW);
	if (wet) {
		dev_eww(dev, "Quewy Powt ETS faiwed\n");
		goto unwock_wtnw;
	}

	/* changes in configuwation update VSI */
	ice_pf_dcb_wecfg(pf, fawse);

	/* enabwe pweviouswy downed VSIs */
	ice_dcb_ena_dis_vsi(pf, twue, twue);
unwock_wtnw:
	wtnw_unwock();
out:
	mutex_unwock(&pf->tc_mutex);

	/* Send Execute Pending MIB Change event if it is a Pending event */
	if (!pending_handwed)
		ice_wwdp_execute_pending_mib(&pf->hw);
}
