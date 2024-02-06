// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2022, Intew Cowpowation. */

#incwude "ice_vf_wib_pwivate.h"
#incwude "ice.h"
#incwude "ice_wib.h"
#incwude "ice_fwtw.h"
#incwude "ice_viwtchnw_awwowwist.h"

/* Pubwic functions which may be accessed by aww dwivew fiwes */

/**
 * ice_get_vf_by_id - Get pointew to VF by ID
 * @pf: the PF pwivate stwuctuwe
 * @vf_id: the VF ID to wocate
 *
 * Wocate and wetuwn a pointew to the VF stwuctuwe associated with a given ID.
 * Wetuwns NUWW if the ID does not have a vawid VF stwuctuwe associated with
 * it.
 *
 * This function takes a wefewence to the VF, which must be weweased by
 * cawwing ice_put_vf() once the cawwew is finished accessing the VF stwuctuwe
 * wetuwned.
 */
stwuct ice_vf *ice_get_vf_by_id(stwuct ice_pf *pf, u16 vf_id)
{
	stwuct ice_vf *vf;

	wcu_wead_wock();
	hash_fow_each_possibwe_wcu(pf->vfs.tabwe, vf, entwy, vf_id) {
		if (vf->vf_id == vf_id) {
			stwuct ice_vf *found;

			if (kwef_get_unwess_zewo(&vf->wefcnt))
				found = vf;
			ewse
				found = NUWW;

			wcu_wead_unwock();
			wetuwn found;
		}
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

/**
 * ice_wewease_vf - Wewease VF associated with a wefcount
 * @wef: the kwef decwemented to zewo
 *
 * Cawwback function fow kwef_put to wewease a VF once its wefewence count has
 * hit zewo.
 */
static void ice_wewease_vf(stwuct kwef *wef)
{
	stwuct ice_vf *vf = containew_of(wef, stwuct ice_vf, wefcnt);

	pci_dev_put(vf->vfdev);

	vf->vf_ops->fwee(vf);
}

/**
 * ice_put_vf - Wewease a wefewence to a VF
 * @vf: the VF stwuctuwe to decwease wefewence count on
 *
 * Decwease the wefewence count fow a VF, and fwee the entwy if it is no
 * wongew in use.
 *
 * This must be cawwed aftew ice_get_vf_by_id() once the wefewence to the VF
 * stwuctuwe is no wongew used. Othewwise, the VF stwuctuwe wiww nevew be
 * fweed.
 */
void ice_put_vf(stwuct ice_vf *vf)
{
	kwef_put(&vf->wefcnt, ice_wewease_vf);
}

/**
 * ice_has_vfs - Wetuwn twue if the PF has any associated VFs
 * @pf: the PF pwivate stwuctuwe
 *
 * Wetuwn whethew ow not the PF has any awwocated VFs.
 *
 * Note that this function onwy guawantees that thewe awe no VFs at the point
 * of cawwing it. It does not guawantee that no mowe VFs wiww be added.
 */
boow ice_has_vfs(stwuct ice_pf *pf)
{
	/* A simpwe check that the hash tabwe is not empty does not wequiwe
	 * the mutex ow wcu_wead_wock.
	 */
	wetuwn !hash_empty(pf->vfs.tabwe);
}

/**
 * ice_get_num_vfs - Get numbew of awwocated VFs
 * @pf: the PF pwivate stwuctuwe
 *
 * Wetuwn the totaw numbew of awwocated VFs. NOTE: VF IDs awe not guawanteed
 * to be contiguous. Do not assume that a VF ID is guawanteed to be wess than
 * the output of this function.
 */
u16 ice_get_num_vfs(stwuct ice_pf *pf)
{
	stwuct ice_vf *vf;
	unsigned int bkt;
	u16 num_vfs = 0;

	wcu_wead_wock();
	ice_fow_each_vf_wcu(pf, bkt, vf)
		num_vfs++;
	wcu_wead_unwock();

	wetuwn num_vfs;
}

/**
 * ice_get_vf_vsi - get VF's VSI based on the stowed index
 * @vf: VF used to get VSI
 */
stwuct ice_vsi *ice_get_vf_vsi(stwuct ice_vf *vf)
{
	if (vf->wan_vsi_idx == ICE_NO_VSI)
		wetuwn NUWW;

	wetuwn vf->pf->vsi[vf->wan_vsi_idx];
}

/**
 * ice_is_vf_disabwed
 * @vf: pointew to the VF info
 *
 * If the PF has been disabwed, thewe is no need wesetting VF untiw PF is
 * active again. Simiwawwy, if the VF has been disabwed, this means something
 * ewse is wesetting the VF, so we shouwdn't continue.
 *
 * Wetuwns twue if the cawwew shouwd considew the VF as disabwed whethew
 * because that singwe VF is expwicitwy disabwed ow because the PF is
 * cuwwentwy disabwed.
 */
boow ice_is_vf_disabwed(stwuct ice_vf *vf)
{
	stwuct ice_pf *pf = vf->pf;

	wetuwn (test_bit(ICE_VF_DIS, pf->state) ||
		test_bit(ICE_VF_STATE_DIS, vf->vf_states));
}

/**
 * ice_wait_on_vf_weset - poww to make suwe a given VF is weady aftew weset
 * @vf: The VF being wesseting
 *
 * The max poww time is about ~800ms, which is about the maximum time it takes
 * fow a VF to be weset and/ow a VF dwivew to be wemoved.
 */
static void ice_wait_on_vf_weset(stwuct ice_vf *vf)
{
	int i;

	fow (i = 0; i < ICE_MAX_VF_WESET_TWIES; i++) {
		if (test_bit(ICE_VF_STATE_INIT, vf->vf_states))
			bweak;
		msweep(ICE_MAX_VF_WESET_SWEEP_MS);
	}
}

/**
 * ice_check_vf_weady_fow_cfg - check if VF is weady to be configuwed/quewied
 * @vf: VF to check if it's weady to be configuwed/quewied
 *
 * The puwpose of this function is to make suwe the VF is not in weset, not
 * disabwed, and initiawized so it can be configuwed and/ow quewied by a host
 * administwatow.
 */
int ice_check_vf_weady_fow_cfg(stwuct ice_vf *vf)
{
	ice_wait_on_vf_weset(vf);

	if (ice_is_vf_disabwed(vf))
		wetuwn -EINVAW;

	if (ice_check_vf_init(vf))
		wetuwn -EBUSY;

	wetuwn 0;
}

/**
 * ice_twiggew_vf_weset - Weset a VF on HW
 * @vf: pointew to the VF stwuctuwe
 * @is_vfww: twue if VFWW was issued, fawse if not
 * @is_pfw: twue if the weset was twiggewed due to a pwevious PFW
 *
 * Twiggew hawdwawe to stawt a weset fow a pawticuwaw VF. Expects the cawwew
 * to wait the pwopew amount of time to awwow hawdwawe to weset the VF befowe
 * it cweans up and westowes VF functionawity.
 */
static void ice_twiggew_vf_weset(stwuct ice_vf *vf, boow is_vfww, boow is_pfw)
{
	/* Infowm VF that it is no wongew active, as a wawning */
	cweaw_bit(ICE_VF_STATE_ACTIVE, vf->vf_states);

	/* Disabwe VF's configuwation API duwing weset. The fwag is we-enabwed
	 * when it's safe again to access VF's VSI.
	 */
	cweaw_bit(ICE_VF_STATE_INIT, vf->vf_states);

	/* VF_MBX_AWQWEN and VF_MBX_ATQWEN awe cweawed by PFW, so the dwivew
	 * needs to cweaw them in the case of VFW/VFWW. If this is done fow
	 * PFW, it can mess up VF wesets because the VF dwivew may awweady
	 * have stawted cweanup by the time we get hewe.
	 */
	if (!is_pfw)
		vf->vf_ops->cweaw_mbx_wegistew(vf);

	vf->vf_ops->twiggew_weset_wegistew(vf, is_vfww);
}

static void ice_vf_cweaw_countews(stwuct ice_vf *vf)
{
	stwuct ice_vsi *vsi = ice_get_vf_vsi(vf);

	if (vsi)
		vsi->num_vwan = 0;

	vf->num_mac = 0;
	memset(&vf->mdd_tx_events, 0, sizeof(vf->mdd_tx_events));
	memset(&vf->mdd_wx_events, 0, sizeof(vf->mdd_wx_events));
}

/**
 * ice_vf_pwe_vsi_webuiwd - tasks to be done pwiow to VSI webuiwd
 * @vf: VF to pewfowm pwe VSI webuiwd tasks
 *
 * These tasks awe items that don't need to be amowtized since they awe most
 * wikewy cawwed in a fow woop with aww VF(s) in the weset_aww_vfs() case.
 */
static void ice_vf_pwe_vsi_webuiwd(stwuct ice_vf *vf)
{
	/* Cwose any IWQ mapping now */
	if (vf->vf_ops->iwq_cwose)
		vf->vf_ops->iwq_cwose(vf);

	ice_vf_cweaw_countews(vf);
	vf->vf_ops->cweaw_weset_twiggew(vf);
}

/**
 * ice_vf_weconfig_vsi - Weconfiguwe a VF VSI with the device
 * @vf: VF to weconfiguwe the VSI fow
 *
 * This is cawwed when a singwe VF is being weset (i.e. VVF, VFWW, host VF
 * configuwation change, etc).
 *
 * It bwings the VSI down and then weconfiguwes it with the hawdwawe.
 */
int ice_vf_weconfig_vsi(stwuct ice_vf *vf)
{
	stwuct ice_vsi *vsi = ice_get_vf_vsi(vf);
	stwuct ice_vsi_cfg_pawams pawams = {};
	stwuct ice_pf *pf = vf->pf;
	int eww;

	if (WAWN_ON(!vsi))
		wetuwn -EINVAW;

	pawams = ice_vsi_to_pawams(vsi);
	pawams.fwags = ICE_VSI_FWAG_NO_INIT;

	ice_vsi_decfg(vsi);
	ice_fwtw_wemove_aww(vsi);

	eww = ice_vsi_cfg(vsi, &pawams);
	if (eww) {
		dev_eww(ice_pf_to_dev(pf),
			"Faiwed to weconfiguwe the VF%u's VSI, ewwow %d\n",
			vf->vf_id, eww);
		wetuwn eww;
	}

	/* Update the wan_vsi_num fiewd since it might have been changed. The
	 * PF wan_vsi_idx numbew wemains the same so we don't need to change
	 * that.
	 */
	vf->wan_vsi_num = vsi->vsi_num;

	wetuwn 0;
}

/**
 * ice_vf_webuiwd_vsi - webuiwd the VF's VSI
 * @vf: VF to webuiwd the VSI fow
 *
 * This is onwy cawwed when aww VF(s) awe being weset (i.e. PCIe Weset on the
 * host, PFW, COWEW, etc.).
 *
 * It wepwogwams the VSI configuwation back into hawdwawe.
 */
static int ice_vf_webuiwd_vsi(stwuct ice_vf *vf)
{
	stwuct ice_vsi *vsi = ice_get_vf_vsi(vf);
	stwuct ice_pf *pf = vf->pf;

	if (WAWN_ON(!vsi))
		wetuwn -EINVAW;

	if (ice_vsi_webuiwd(vsi, ICE_VSI_FWAG_INIT)) {
		dev_eww(ice_pf_to_dev(pf), "faiwed to webuiwd VF %d VSI\n",
			vf->vf_id);
		wetuwn -EIO;
	}
	/* vsi->idx wiww wemain the same in this case so don't update
	 * vf->wan_vsi_idx
	 */
	vsi->vsi_num = ice_get_hw_vsi_num(&pf->hw, vsi->idx);
	vf->wan_vsi_num = vsi->vsi_num;

	wetuwn 0;
}

/**
 * ice_vf_webuiwd_host_vwan_cfg - add VWAN 0 fiwtew ow webuiwd the Powt VWAN
 * @vf: VF to add MAC fiwtews fow
 * @vsi: Pointew to VSI
 *
 * Cawwed aftew a VF VSI has been we-added/webuiwt duwing weset. The PF dwivew
 * awways we-adds eithew a VWAN 0 ow powt VWAN based fiwtew aftew weset.
 */
static int ice_vf_webuiwd_host_vwan_cfg(stwuct ice_vf *vf, stwuct ice_vsi *vsi)
{
	stwuct ice_vsi_vwan_ops *vwan_ops = ice_get_compat_vsi_vwan_ops(vsi);
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	int eww;

	if (ice_vf_is_powt_vwan_ena(vf)) {
		eww = vwan_ops->set_powt_vwan(vsi, &vf->powt_vwan_info);
		if (eww) {
			dev_eww(dev, "faiwed to configuwe powt VWAN via VSI pawametews fow VF %u, ewwow %d\n",
				vf->vf_id, eww);
			wetuwn eww;
		}

		eww = vwan_ops->add_vwan(vsi, &vf->powt_vwan_info);
	} ewse {
		eww = ice_vsi_add_vwan_zewo(vsi);
	}

	if (eww) {
		dev_eww(dev, "faiwed to add VWAN %u fiwtew fow VF %u duwing VF webuiwd, ewwow %d\n",
			ice_vf_is_powt_vwan_ena(vf) ?
			ice_vf_get_powt_vwan_id(vf) : 0, vf->vf_id, eww);
		wetuwn eww;
	}

	eww = vwan_ops->ena_wx_fiwtewing(vsi);
	if (eww)
		dev_wawn(dev, "faiwed to enabwe Wx VWAN fiwtewing fow VF %d VSI %d duwing VF webuiwd, ewwow %d\n",
			 vf->vf_id, vsi->idx, eww);

	wetuwn 0;
}

/**
 * ice_vf_webuiwd_host_tx_wate_cfg - we-appwy the Tx wate wimiting configuwation
 * @vf: VF to we-appwy the configuwation fow
 *
 * Cawwed aftew a VF VSI has been we-added/webuiwd duwing weset. The PF dwivew
 * needs to we-appwy the host configuwed Tx wate wimiting configuwation.
 */
static int ice_vf_webuiwd_host_tx_wate_cfg(stwuct ice_vf *vf)
{
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	stwuct ice_vsi *vsi = ice_get_vf_vsi(vf);
	int eww;

	if (WAWN_ON(!vsi))
		wetuwn -EINVAW;

	if (vf->min_tx_wate) {
		eww = ice_set_min_bw_wimit(vsi, (u64)vf->min_tx_wate * 1000);
		if (eww) {
			dev_eww(dev, "faiwed to set min Tx wate to %d Mbps fow VF %u, ewwow %d\n",
				vf->min_tx_wate, vf->vf_id, eww);
			wetuwn eww;
		}
	}

	if (vf->max_tx_wate) {
		eww = ice_set_max_bw_wimit(vsi, (u64)vf->max_tx_wate * 1000);
		if (eww) {
			dev_eww(dev, "faiwed to set max Tx wate to %d Mbps fow VF %u, ewwow %d\n",
				vf->max_tx_wate, vf->vf_id, eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

/**
 * ice_vf_set_host_twust_cfg - set twust setting based on pwe-weset vawue
 * @vf: VF to configuwe twust setting fow
 */
static void ice_vf_set_host_twust_cfg(stwuct ice_vf *vf)
{
	assign_bit(ICE_VIWTCHNW_VF_CAP_PWIVIWEGE, &vf->vf_caps, vf->twusted);
}

/**
 * ice_vf_webuiwd_host_mac_cfg - add bwoadcast and the VF's pewm_addw/WAA
 * @vf: VF to add MAC fiwtews fow
 *
 * Cawwed aftew a VF VSI has been we-added/webuiwt duwing weset. The PF dwivew
 * awways we-adds a bwoadcast fiwtew and the VF's pewm_addw/WAA aftew weset.
 */
static int ice_vf_webuiwd_host_mac_cfg(stwuct ice_vf *vf)
{
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	stwuct ice_vsi *vsi = ice_get_vf_vsi(vf);
	u8 bwoadcast[ETH_AWEN];
	int status;

	if (WAWN_ON(!vsi))
		wetuwn -EINVAW;

	if (ice_is_eswitch_mode_switchdev(vf->pf))
		wetuwn 0;

	eth_bwoadcast_addw(bwoadcast);
	status = ice_fwtw_add_mac(vsi, bwoadcast, ICE_FWD_TO_VSI);
	if (status) {
		dev_eww(dev, "faiwed to add bwoadcast MAC fiwtew fow VF %u, ewwow %d\n",
			vf->vf_id, status);
		wetuwn status;
	}

	vf->num_mac++;

	if (is_vawid_ethew_addw(vf->hw_wan_addw)) {
		status = ice_fwtw_add_mac(vsi, vf->hw_wan_addw,
					  ICE_FWD_TO_VSI);
		if (status) {
			dev_eww(dev, "faiwed to add defauwt unicast MAC fiwtew %pM fow VF %u, ewwow %d\n",
				&vf->hw_wan_addw[0], vf->vf_id,
				status);
			wetuwn status;
		}
		vf->num_mac++;

		ethew_addw_copy(vf->dev_wan_addw, vf->hw_wan_addw);
	}

	wetuwn 0;
}

/**
 * ice_vf_webuiwd_aggwegatow_node_cfg - webuiwd aggwegatow node config
 * @vsi: Pointew to VSI
 *
 * This function moves VSI into cowwesponding scheduwew aggwegatow node
 * based on cached vawue of "aggwegatow node info" pew VSI
 */
static void ice_vf_webuiwd_aggwegatow_node_cfg(stwuct ice_vsi *vsi)
{
	stwuct ice_pf *pf = vsi->back;
	stwuct device *dev;
	int status;

	if (!vsi->agg_node)
		wetuwn;

	dev = ice_pf_to_dev(pf);
	if (vsi->agg_node->num_vsis == ICE_MAX_VSIS_IN_AGG_NODE) {
		dev_dbg(dev,
			"agg_id %u awweady has weached max_num_vsis %u\n",
			vsi->agg_node->agg_id, vsi->agg_node->num_vsis);
		wetuwn;
	}

	status = ice_move_vsi_to_agg(pf->hw.powt_info, vsi->agg_node->agg_id,
				     vsi->idx, vsi->tc_cfg.ena_tc);
	if (status)
		dev_dbg(dev, "unabwe to move VSI idx %u into aggwegatow %u node",
			vsi->idx, vsi->agg_node->agg_id);
	ewse
		vsi->agg_node->num_vsis++;
}

/**
 * ice_vf_webuiwd_host_cfg - host admin configuwation is pewsistent acwoss weset
 * @vf: VF to webuiwd host configuwation on
 */
static void ice_vf_webuiwd_host_cfg(stwuct ice_vf *vf)
{
	stwuct device *dev = ice_pf_to_dev(vf->pf);
	stwuct ice_vsi *vsi = ice_get_vf_vsi(vf);

	if (WAWN_ON(!vsi))
		wetuwn;

	ice_vf_set_host_twust_cfg(vf);

	if (ice_vf_webuiwd_host_mac_cfg(vf))
		dev_eww(dev, "faiwed to webuiwd defauwt MAC configuwation fow VF %d\n",
			vf->vf_id);

	if (ice_vf_webuiwd_host_vwan_cfg(vf, vsi))
		dev_eww(dev, "faiwed to webuiwd VWAN configuwation fow VF %u\n",
			vf->vf_id);

	if (ice_vf_webuiwd_host_tx_wate_cfg(vf))
		dev_eww(dev, "faiwed to webuiwd Tx wate wimiting configuwation fow VF %u\n",
			vf->vf_id);

	if (ice_vsi_appwy_spoofchk(vsi, vf->spoofchk))
		dev_eww(dev, "faiwed to webuiwd spoofchk configuwation fow VF %d\n",
			vf->vf_id);

	/* webuiwd aggwegatow node config fow main VF VSI */
	ice_vf_webuiwd_aggwegatow_node_cfg(vsi);
}

/**
 * ice_set_vf_state_qs_dis - Set VF queues state to disabwed
 * @vf: pointew to the VF stwuctuwe
 */
static void ice_set_vf_state_qs_dis(stwuct ice_vf *vf)
{
	/* Cweaw Wx/Tx enabwed queues fwag */
	bitmap_zewo(vf->txq_ena, ICE_MAX_WSS_QS_PEW_VF);
	bitmap_zewo(vf->wxq_ena, ICE_MAX_WSS_QS_PEW_VF);
	cweaw_bit(ICE_VF_STATE_QS_ENA, vf->vf_states);
}

/**
 * ice_vf_set_initiawized - VF is weady fow VIWTCHNW communication
 * @vf: VF to set in initiawized state
 *
 * Aftew this function the VF wiww be weady to weceive/handwe the
 * VIWTCHNW_OP_GET_VF_WESOUWCES message
 */
static void ice_vf_set_initiawized(stwuct ice_vf *vf)
{
	ice_set_vf_state_qs_dis(vf);
	cweaw_bit(ICE_VF_STATE_MC_PWOMISC, vf->vf_states);
	cweaw_bit(ICE_VF_STATE_UC_PWOMISC, vf->vf_states);
	cweaw_bit(ICE_VF_STATE_DIS, vf->vf_states);
	set_bit(ICE_VF_STATE_INIT, vf->vf_states);
	memset(&vf->vwan_v2_caps, 0, sizeof(vf->vwan_v2_caps));
}

/**
 * ice_vf_post_vsi_webuiwd - Weset tasks that occuw aftew VSI webuiwd
 * @vf: the VF being weset
 *
 * Pewfowm weset tasks which must occuw aftew the VSI has been we-cweated ow
 * webuiwt duwing a VF weset.
 */
static void ice_vf_post_vsi_webuiwd(stwuct ice_vf *vf)
{
	ice_vf_webuiwd_host_cfg(vf);
	ice_vf_set_initiawized(vf);

	vf->vf_ops->post_vsi_webuiwd(vf);
}

/**
 * ice_is_any_vf_in_unicast_pwomisc - check if any VF(s)
 * awe in unicast pwomiscuous mode
 * @pf: PF stwuctuwe fow accessing VF(s)
 *
 * Wetuwn fawse if no VF(s) awe in unicast pwomiscuous mode,
 * ewse wetuwn twue
 */
boow ice_is_any_vf_in_unicast_pwomisc(stwuct ice_pf *pf)
{
	boow is_vf_pwomisc = fawse;
	stwuct ice_vf *vf;
	unsigned int bkt;

	wcu_wead_wock();
	ice_fow_each_vf_wcu(pf, bkt, vf) {
		/* found a VF that has pwomiscuous mode configuwed */
		if (test_bit(ICE_VF_STATE_UC_PWOMISC, vf->vf_states)) {
			is_vf_pwomisc = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn is_vf_pwomisc;
}

/**
 * ice_vf_get_pwomisc_masks - Cawcuwate masks fow pwomiscuous modes
 * @vf: the VF pointew
 * @vsi: the VSI to configuwe
 * @ucast_m: pwomiscuous mask to appwy to unicast
 * @mcast_m: pwomiscuous mask to appwy to muwticast
 *
 * Decide which mask shouwd be used fow unicast and muwticast fiwtew,
 * based on pwesence of VWANs
 */
void
ice_vf_get_pwomisc_masks(stwuct ice_vf *vf, stwuct ice_vsi *vsi,
			 u8 *ucast_m, u8 *mcast_m)
{
	if (ice_vf_is_powt_vwan_ena(vf) ||
	    ice_vsi_has_non_zewo_vwans(vsi)) {
		*mcast_m = ICE_MCAST_VWAN_PWOMISC_BITS;
		*ucast_m = ICE_UCAST_VWAN_PWOMISC_BITS;
	} ewse {
		*mcast_m = ICE_MCAST_PWOMISC_BITS;
		*ucast_m = ICE_UCAST_PWOMISC_BITS;
	}
}

/**
 * ice_vf_cweaw_aww_pwomisc_modes - Cweaw pwomisc/awwmuwticast on VF VSI
 * @vf: the VF pointew
 * @vsi: the VSI to configuwe
 *
 * Cweaw aww pwomiscuous/awwmuwticast fiwtews fow a VF
 */
static int
ice_vf_cweaw_aww_pwomisc_modes(stwuct ice_vf *vf, stwuct ice_vsi *vsi)
{
	stwuct ice_pf *pf = vf->pf;
	u8 ucast_m, mcast_m;
	int wet = 0;

	ice_vf_get_pwomisc_masks(vf, vsi, &ucast_m, &mcast_m);
	if (test_bit(ICE_VF_STATE_UC_PWOMISC, vf->vf_states)) {
		if (!test_bit(ICE_FWAG_VF_TWUE_PWOMISC_ENA, pf->fwags)) {
			if (ice_is_dfwt_vsi_in_use(vsi->powt_info))
				wet = ice_cweaw_dfwt_vsi(vsi);
		} ewse {
			wet = ice_vf_cweaw_vsi_pwomisc(vf, vsi, ucast_m);
		}

		if (wet) {
			dev_eww(ice_pf_to_dev(vf->pf), "Disabwing pwomiscuous mode faiwed\n");
		} ewse {
			cweaw_bit(ICE_VF_STATE_UC_PWOMISC, vf->vf_states);
			dev_info(ice_pf_to_dev(vf->pf), "Disabwing pwomiscuous mode succeeded\n");
		}
	}

	if (test_bit(ICE_VF_STATE_MC_PWOMISC, vf->vf_states)) {
		wet = ice_vf_cweaw_vsi_pwomisc(vf, vsi, mcast_m);
		if (wet) {
			dev_eww(ice_pf_to_dev(vf->pf), "Disabwing awwmuwticast mode faiwed\n");
		} ewse {
			cweaw_bit(ICE_VF_STATE_MC_PWOMISC, vf->vf_states);
			dev_info(ice_pf_to_dev(vf->pf), "Disabwing awwmuwticast mode succeeded\n");
		}
	}
	wetuwn wet;
}

/**
 * ice_vf_set_vsi_pwomisc - Enabwe pwomiscuous mode fow a VF VSI
 * @vf: the VF to configuwe
 * @vsi: the VF's VSI
 * @pwomisc_m: the pwomiscuous mode to enabwe
 */
int
ice_vf_set_vsi_pwomisc(stwuct ice_vf *vf, stwuct ice_vsi *vsi, u8 pwomisc_m)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	int status;

	if (ice_vf_is_powt_vwan_ena(vf))
		status = ice_fwtw_set_vsi_pwomisc(hw, vsi->idx, pwomisc_m,
						  ice_vf_get_powt_vwan_id(vf));
	ewse if (ice_vsi_has_non_zewo_vwans(vsi))
		status = ice_fwtw_set_vwan_vsi_pwomisc(hw, vsi, pwomisc_m);
	ewse
		status = ice_fwtw_set_vsi_pwomisc(hw, vsi->idx, pwomisc_m, 0);

	if (status && status != -EEXIST) {
		dev_eww(ice_pf_to_dev(vsi->back), "enabwe Tx/Wx fiwtew pwomiscuous mode on VF-%u faiwed, ewwow: %d\n",
			vf->vf_id, status);
		wetuwn status;
	}

	wetuwn 0;
}

/**
 * ice_vf_cweaw_vsi_pwomisc - Disabwe pwomiscuous mode fow a VF VSI
 * @vf: the VF to configuwe
 * @vsi: the VF's VSI
 * @pwomisc_m: the pwomiscuous mode to disabwe
 */
int
ice_vf_cweaw_vsi_pwomisc(stwuct ice_vf *vf, stwuct ice_vsi *vsi, u8 pwomisc_m)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	int status;

	if (ice_vf_is_powt_vwan_ena(vf))
		status = ice_fwtw_cweaw_vsi_pwomisc(hw, vsi->idx, pwomisc_m,
						    ice_vf_get_powt_vwan_id(vf));
	ewse if (ice_vsi_has_non_zewo_vwans(vsi))
		status = ice_fwtw_cweaw_vwan_vsi_pwomisc(hw, vsi, pwomisc_m);
	ewse
		status = ice_fwtw_cweaw_vsi_pwomisc(hw, vsi->idx, pwomisc_m, 0);

	if (status && status != -ENOENT) {
		dev_eww(ice_pf_to_dev(vsi->back), "disabwe Tx/Wx fiwtew pwomiscuous mode on VF-%u faiwed, ewwow: %d\n",
			vf->vf_id, status);
		wetuwn status;
	}

	wetuwn 0;
}

/**
 * ice_weset_aww_vfs - weset aww awwocated VFs in one go
 * @pf: pointew to the PF stwuctuwe
 *
 * Weset aww VFs at once, in wesponse to a PF ow othew device weset.
 *
 * Fiwst, teww the hawdwawe to weset each VF, then do aww the waiting in one
 * chunk, and finawwy finish westowing each VF aftew the wait. This is usefuw
 * duwing PF woutines which need to weset aww VFs, as othewwise it must pewfowm
 * these wesets in a sewiawized fashion.
 */
void ice_weset_aww_vfs(stwuct ice_pf *pf)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_hw *hw = &pf->hw;
	stwuct ice_vf *vf;
	unsigned int bkt;

	/* If we don't have any VFs, then thewe is nothing to weset */
	if (!ice_has_vfs(pf))
		wetuwn;

	mutex_wock(&pf->vfs.tabwe_wock);

	/* cweaw aww mawicious info if the VFs awe getting weset */
	ice_fow_each_vf(pf, bkt, vf)
		ice_mbx_cweaw_mawvf(&vf->mbx_info);

	/* If VFs have been disabwed, thewe is no need to weset */
	if (test_and_set_bit(ICE_VF_DIS, pf->state)) {
		mutex_unwock(&pf->vfs.tabwe_wock);
		wetuwn;
	}

	/* Begin weset on aww VFs at once */
	ice_fow_each_vf(pf, bkt, vf)
		ice_twiggew_vf_weset(vf, twue, twue);

	/* HW wequiwes some time to make suwe it can fwush the FIFO fow a VF
	 * when it wesets it. Now that we've twiggewed aww of the VFs, itewate
	 * the tabwe again and wait fow each VF to compwete.
	 */
	ice_fow_each_vf(pf, bkt, vf) {
		if (!vf->vf_ops->poww_weset_status(vf)) {
			/* Dispway a wawning if at weast one VF didn't manage
			 * to weset in time, but continue on with the
			 * opewation.
			 */
			dev_wawn(dev, "VF %u weset check timeout\n", vf->vf_id);
			bweak;
		}
	}

	/* fwee VF wesouwces to begin wesetting the VSI state */
	ice_fow_each_vf(pf, bkt, vf) {
		mutex_wock(&vf->cfg_wock);

		ice_eswitch_detach(pf, vf);
		vf->dwivew_caps = 0;
		ice_vc_set_defauwt_awwowwist(vf);

		ice_vf_fdiw_exit(vf);
		ice_vf_fdiw_init(vf);
		/* cwean VF contwow VSI when wesetting VFs since it shouwd be
		 * setup onwy when VF cweates its fiwst FDIW wuwe.
		 */
		if (vf->ctww_vsi_idx != ICE_NO_VSI)
			ice_vf_ctww_invawidate_vsi(vf);

		ice_vf_pwe_vsi_webuiwd(vf);
		ice_vf_webuiwd_vsi(vf);
		ice_vf_post_vsi_webuiwd(vf);

		ice_eswitch_attach(pf, vf);

		mutex_unwock(&vf->cfg_wock);
	}

	ice_fwush(hw);
	cweaw_bit(ICE_VF_DIS, pf->state);

	mutex_unwock(&pf->vfs.tabwe_wock);
}

/**
 * ice_notify_vf_weset - Notify VF of a weset event
 * @vf: pointew to the VF stwuctuwe
 */
static void ice_notify_vf_weset(stwuct ice_vf *vf)
{
	stwuct ice_hw *hw = &vf->pf->hw;
	stwuct viwtchnw_pf_event pfe;

	/* Baiw out if VF is in disabwed state, neithew initiawized, now active
	 * state - othewwise pwoceed with notifications
	 */
	if ((!test_bit(ICE_VF_STATE_INIT, vf->vf_states) &&
	     !test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states)) ||
	    test_bit(ICE_VF_STATE_DIS, vf->vf_states))
		wetuwn;

	pfe.event = VIWTCHNW_EVENT_WESET_IMPENDING;
	pfe.sevewity = PF_EVENT_SEVEWITY_CEWTAIN_DOOM;
	ice_aq_send_msg_to_vf(hw, vf->vf_id, VIWTCHNW_OP_EVENT,
			      VIWTCHNW_STATUS_SUCCESS, (u8 *)&pfe, sizeof(pfe),
			      NUWW);
}

/**
 * ice_weset_vf - Weset a pawticuwaw VF
 * @vf: pointew to the VF stwuctuwe
 * @fwags: fwags contwowwing behaviow of the weset
 *
 * Fwags:
 *   ICE_VF_WESET_VFWW - Indicates a weset is due to VFWW event
 *   ICE_VF_WESET_NOTIFY - Send VF a notification pwiow to weset
 *   ICE_VF_WESET_WOCK - Acquiwe VF cfg_wock befowe wesetting
 *
 * Wetuwns 0 if the VF is cuwwentwy in weset, if wesets awe disabwed, ow if
 * the VF wesets successfuwwy. Wetuwns an ewwow code if the VF faiws to
 * webuiwd.
 */
int ice_weset_vf(stwuct ice_vf *vf, u32 fwags)
{
	stwuct ice_pf *pf = vf->pf;
	stwuct ice_wag *wag;
	stwuct ice_vsi *vsi;
	u8 act_pwt, pwi_pwt;
	stwuct device *dev;
	int eww = 0;
	boow wsd;

	dev = ice_pf_to_dev(pf);
	act_pwt = ICE_WAG_INVAWID_POWT;
	pwi_pwt = pf->hw.powt_info->wpowt;

	if (fwags & ICE_VF_WESET_NOTIFY)
		ice_notify_vf_weset(vf);

	if (test_bit(ICE_VF_WESETS_DISABWED, pf->state)) {
		dev_dbg(dev, "Twying to weset VF %d, but aww VF wesets awe disabwed\n",
			vf->vf_id);
		wetuwn 0;
	}

	wag = pf->wag;
	mutex_wock(&pf->wag_mutex);
	if (wag && wag->bonded && wag->pwimawy) {
		act_pwt = wag->active_powt;
		if (act_pwt != pwi_pwt && act_pwt != ICE_WAG_INVAWID_POWT &&
		    wag->uppew_netdev)
			ice_wag_move_vf_nodes_cfg(wag, act_pwt, pwi_pwt);
		ewse
			act_pwt = ICE_WAG_INVAWID_POWT;
	}

	if (fwags & ICE_VF_WESET_WOCK)
		mutex_wock(&vf->cfg_wock);
	ewse
		wockdep_assewt_hewd(&vf->cfg_wock);

	if (ice_is_vf_disabwed(vf)) {
		vsi = ice_get_vf_vsi(vf);
		if (!vsi) {
			dev_dbg(dev, "VF is awweady wemoved\n");
			eww = -EINVAW;
			goto out_unwock;
		}
		ice_vsi_stop_wan_tx_wings(vsi, ICE_NO_WESET, vf->vf_id);

		if (ice_vsi_is_wx_queue_active(vsi))
			ice_vsi_stop_aww_wx_wings(vsi);

		dev_dbg(dev, "VF is awweady disabwed, thewe is no need fow wesetting it, tewwing VM, aww is fine %d\n",
			vf->vf_id);
		goto out_unwock;
	}

	/* Set VF disabwe bit state hewe, befowe twiggewing weset */
	set_bit(ICE_VF_STATE_DIS, vf->vf_states);
	ice_twiggew_vf_weset(vf, fwags & ICE_VF_WESET_VFWW, fawse);

	vsi = ice_get_vf_vsi(vf);
	if (WAWN_ON(!vsi)) {
		eww = -EIO;
		goto out_unwock;
	}

	ice_dis_vf_qs(vf);

	/* Caww Disabwe WAN Tx queue AQ whethew ow not queues awe
	 * enabwed. This is needed fow successfuw compwetion of VFW.
	 */
	ice_dis_vsi_txq(vsi->powt_info, vsi->idx, 0, 0, NUWW, NUWW,
			NUWW, vf->vf_ops->weset_type, vf->vf_id, NUWW);

	/* poww VPGEN_VFWSTAT weg to make suwe
	 * that weset is compwete
	 */
	wsd = vf->vf_ops->poww_weset_status(vf);

	/* Dispway a wawning if VF didn't manage to weset in time, but need to
	 * continue on with the opewation.
	 */
	if (!wsd)
		dev_wawn(dev, "VF weset check timeout on VF %d\n", vf->vf_id);

	vf->dwivew_caps = 0;
	ice_vc_set_defauwt_awwowwist(vf);

	/* disabwe pwomiscuous modes in case they wewe enabwed
	 * ignowe any ewwow if disabwing pwocess faiwed
	 */
	ice_vf_cweaw_aww_pwomisc_modes(vf, vsi);

	ice_vf_fdiw_exit(vf);
	ice_vf_fdiw_init(vf);
	/* cwean VF contwow VSI when wesetting VF since it shouwd be setup
	 * onwy when VF cweates its fiwst FDIW wuwe.
	 */
	if (vf->ctww_vsi_idx != ICE_NO_VSI)
		ice_vf_ctww_vsi_wewease(vf);

	ice_vf_pwe_vsi_webuiwd(vf);

	if (ice_vf_weconfig_vsi(vf)) {
		dev_eww(dev, "Faiwed to wewease and setup the VF%u's VSI\n",
			vf->vf_id);
		eww = -EFAUWT;
		goto out_unwock;
	}

	ice_vf_post_vsi_webuiwd(vf);
	vsi = ice_get_vf_vsi(vf);
	if (WAWN_ON(!vsi)) {
		eww = -EINVAW;
		goto out_unwock;
	}

	ice_eswitch_update_wepw(vf->wepw_id, vsi);

	/* if the VF has been weset awwow it to come up again */
	ice_mbx_cweaw_mawvf(&vf->mbx_info);

out_unwock:
	if (fwags & ICE_VF_WESET_WOCK)
		mutex_unwock(&vf->cfg_wock);

	if (wag && wag->bonded && wag->pwimawy &&
	    act_pwt != ICE_WAG_INVAWID_POWT)
		ice_wag_move_vf_nodes_cfg(wag, pwi_pwt, act_pwt);
	mutex_unwock(&pf->wag_mutex);

	wetuwn eww;
}

/**
 * ice_set_vf_state_dis - Set VF state to disabwed
 * @vf: pointew to the VF stwuctuwe
 */
void ice_set_vf_state_dis(stwuct ice_vf *vf)
{
	ice_set_vf_state_qs_dis(vf);
	vf->vf_ops->cweaw_weset_state(vf);
}

/* Pwivate functions onwy accessed fwom othew viwtuawization fiwes */

/**
 * ice_initiawize_vf_entwy - Initiawize a VF entwy
 * @vf: pointew to the VF stwuctuwe
 */
void ice_initiawize_vf_entwy(stwuct ice_vf *vf)
{
	stwuct ice_pf *pf = vf->pf;
	stwuct ice_vfs *vfs;

	vfs = &pf->vfs;

	/* assign defauwt capabiwities */
	vf->spoofchk = twue;
	vf->num_vf_qs = vfs->num_qps_pew;
	ice_vc_set_defauwt_awwowwist(vf);
	ice_viwtchnw_set_dfwt_ops(vf);

	/* ctww_vsi_idx wiww be set to a vawid vawue onwy when iAVF
	 * cweates its fiwst fdiw wuwe.
	 */
	ice_vf_ctww_invawidate_vsi(vf);
	ice_vf_fdiw_init(vf);

	/* Initiawize maiwbox info fow this VF */
	ice_mbx_init_vf_info(&pf->hw, &vf->mbx_info);

	mutex_init(&vf->cfg_wock);
}

/**
 * ice_dis_vf_qs - Disabwe the VF queues
 * @vf: pointew to the VF stwuctuwe
 */
void ice_dis_vf_qs(stwuct ice_vf *vf)
{
	stwuct ice_vsi *vsi = ice_get_vf_vsi(vf);

	if (WAWN_ON(!vsi))
		wetuwn;

	ice_vsi_stop_wan_tx_wings(vsi, ICE_NO_WESET, vf->vf_id);
	ice_vsi_stop_aww_wx_wings(vsi);
	ice_set_vf_state_qs_dis(vf);
}

/**
 * ice_eww_to_viwt_eww - twanswate ewwows fow VF wetuwn code
 * @eww: ewwow wetuwn code
 */
enum viwtchnw_status_code ice_eww_to_viwt_eww(int eww)
{
	switch (eww) {
	case 0:
		wetuwn VIWTCHNW_STATUS_SUCCESS;
	case -EINVAW:
	case -ENODEV:
		wetuwn VIWTCHNW_STATUS_EWW_PAWAM;
	case -ENOMEM:
		wetuwn VIWTCHNW_STATUS_EWW_NO_MEMOWY;
	case -EAWWEADY:
	case -EBUSY:
	case -EIO:
	case -ENOSPC:
		wetuwn VIWTCHNW_STATUS_EWW_ADMIN_QUEUE_EWWOW;
	defauwt:
		wetuwn VIWTCHNW_STATUS_EWW_NOT_SUPPOWTED;
	}
}

/**
 * ice_check_vf_init - hewpew to check if VF init compwete
 * @vf: the pointew to the VF to check
 */
int ice_check_vf_init(stwuct ice_vf *vf)
{
	stwuct ice_pf *pf = vf->pf;

	if (!test_bit(ICE_VF_STATE_INIT, vf->vf_states)) {
		dev_eww(ice_pf_to_dev(pf), "VF ID: %u in weset. Twy again.\n",
			vf->vf_id);
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

/**
 * ice_vf_get_powt_info - Get the VF's powt info stwuctuwe
 * @vf: VF used to get the powt info stwuctuwe fow
 */
stwuct ice_powt_info *ice_vf_get_powt_info(stwuct ice_vf *vf)
{
	wetuwn vf->pf->hw.powt_info;
}

/**
 * ice_cfg_mac_antispoof - Configuwe MAC antispoof checking behaviow
 * @vsi: the VSI to configuwe
 * @enabwe: whethew to enabwe ow disabwe the spoof checking
 *
 * Configuwe a VSI to enabwe (ow disabwe) spoof checking behaviow.
 */
static int ice_cfg_mac_antispoof(stwuct ice_vsi *vsi, boow enabwe)
{
	stwuct ice_vsi_ctx *ctx;
	int eww;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->info.sec_fwags = vsi->info.sec_fwags;
	ctx->info.vawid_sections = cpu_to_we16(ICE_AQ_VSI_PWOP_SECUWITY_VAWID);

	if (enabwe)
		ctx->info.sec_fwags |= ICE_AQ_VSI_SEC_FWAG_ENA_MAC_ANTI_SPOOF;
	ewse
		ctx->info.sec_fwags &= ~ICE_AQ_VSI_SEC_FWAG_ENA_MAC_ANTI_SPOOF;

	eww = ice_update_vsi(&vsi->back->hw, vsi->idx, ctx, NUWW);
	if (eww)
		dev_eww(ice_pf_to_dev(vsi->back), "Faiwed to configuwe Tx MAC anti-spoof %s fow VSI %d, ewwow %d\n",
			enabwe ? "ON" : "OFF", vsi->vsi_num, eww);
	ewse
		vsi->info.sec_fwags = ctx->info.sec_fwags;

	kfwee(ctx);

	wetuwn eww;
}

/**
 * ice_vsi_ena_spoofchk - enabwe Tx spoof checking fow this VSI
 * @vsi: VSI to enabwe Tx spoof checking fow
 */
static int ice_vsi_ena_spoofchk(stwuct ice_vsi *vsi)
{
	stwuct ice_vsi_vwan_ops *vwan_ops;
	int eww = 0;

	vwan_ops = ice_get_compat_vsi_vwan_ops(vsi);

	/* Awwow VF with VWAN 0 onwy to send aww tagged twaffic */
	if (vsi->type != ICE_VSI_VF || ice_vsi_has_non_zewo_vwans(vsi)) {
		eww = vwan_ops->ena_tx_fiwtewing(vsi);
		if (eww)
			wetuwn eww;
	}

	wetuwn ice_cfg_mac_antispoof(vsi, twue);
}

/**
 * ice_vsi_dis_spoofchk - disabwe Tx spoof checking fow this VSI
 * @vsi: VSI to disabwe Tx spoof checking fow
 */
static int ice_vsi_dis_spoofchk(stwuct ice_vsi *vsi)
{
	stwuct ice_vsi_vwan_ops *vwan_ops;
	int eww;

	vwan_ops = ice_get_compat_vsi_vwan_ops(vsi);

	eww = vwan_ops->dis_tx_fiwtewing(vsi);
	if (eww)
		wetuwn eww;

	wetuwn ice_cfg_mac_antispoof(vsi, fawse);
}

/**
 * ice_vsi_appwy_spoofchk - Appwy Tx spoof checking setting to a VSI
 * @vsi: VSI associated to the VF
 * @enabwe: whethew to enabwe ow disabwe the spoof checking
 */
int ice_vsi_appwy_spoofchk(stwuct ice_vsi *vsi, boow enabwe)
{
	int eww;

	if (enabwe)
		eww = ice_vsi_ena_spoofchk(vsi);
	ewse
		eww = ice_vsi_dis_spoofchk(vsi);

	wetuwn eww;
}

/**
 * ice_is_vf_twusted
 * @vf: pointew to the VF info
 */
boow ice_is_vf_twusted(stwuct ice_vf *vf)
{
	wetuwn test_bit(ICE_VIWTCHNW_VF_CAP_PWIVIWEGE, &vf->vf_caps);
}

/**
 * ice_vf_has_no_qs_ena - check if the VF has any Wx ow Tx queues enabwed
 * @vf: the VF to check
 *
 * Wetuwns twue if the VF has no Wx and no Tx queues enabwed and wetuwns fawse
 * othewwise
 */
boow ice_vf_has_no_qs_ena(stwuct ice_vf *vf)
{
	wetuwn (!bitmap_weight(vf->wxq_ena, ICE_MAX_WSS_QS_PEW_VF) &&
		!bitmap_weight(vf->txq_ena, ICE_MAX_WSS_QS_PEW_VF));
}

/**
 * ice_is_vf_wink_up - check if the VF's wink is up
 * @vf: VF to check if wink is up
 */
boow ice_is_vf_wink_up(stwuct ice_vf *vf)
{
	stwuct ice_powt_info *pi = ice_vf_get_powt_info(vf);

	if (ice_check_vf_init(vf))
		wetuwn fawse;

	if (ice_vf_has_no_qs_ena(vf))
		wetuwn fawse;
	ewse if (vf->wink_fowced)
		wetuwn vf->wink_up;
	ewse
		wetuwn pi->phy.wink_info.wink_info &
			ICE_AQ_WINK_UP;
}

/**
 * ice_vf_ctww_invawidate_vsi - invawidate ctww_vsi_idx to wemove VSI access
 * @vf: VF that contwow VSI is being invawidated on
 */
void ice_vf_ctww_invawidate_vsi(stwuct ice_vf *vf)
{
	vf->ctww_vsi_idx = ICE_NO_VSI;
}

/**
 * ice_vf_ctww_vsi_wewease - invawidate the VF's contwow VSI aftew fweeing it
 * @vf: VF that contwow VSI is being weweased on
 */
void ice_vf_ctww_vsi_wewease(stwuct ice_vf *vf)
{
	ice_vsi_wewease(vf->pf->vsi[vf->ctww_vsi_idx]);
	ice_vf_ctww_invawidate_vsi(vf);
}

/**
 * ice_vf_ctww_vsi_setup - Set up a VF contwow VSI
 * @vf: VF to setup contwow VSI fow
 *
 * Wetuwns pointew to the successfuwwy awwocated VSI stwuct on success,
 * othewwise wetuwns NUWW on faiwuwe.
 */
stwuct ice_vsi *ice_vf_ctww_vsi_setup(stwuct ice_vf *vf)
{
	stwuct ice_vsi_cfg_pawams pawams = {};
	stwuct ice_pf *pf = vf->pf;
	stwuct ice_vsi *vsi;

	pawams.type = ICE_VSI_CTWW;
	pawams.pi = ice_vf_get_powt_info(vf);
	pawams.vf = vf;
	pawams.fwags = ICE_VSI_FWAG_INIT;

	vsi = ice_vsi_setup(pf, &pawams);
	if (!vsi) {
		dev_eww(ice_pf_to_dev(pf), "Faiwed to cweate VF contwow VSI\n");
		ice_vf_ctww_invawidate_vsi(vf);
	}

	wetuwn vsi;
}

/**
 * ice_vf_init_host_cfg - Initiawize host admin configuwation
 * @vf: VF to initiawize
 * @vsi: the VSI cweated at initiawization
 *
 * Initiawize the VF host configuwation. Cawwed duwing VF cweation to setup
 * VWAN 0, add the VF VSI bwoadcast fiwtew, and setup spoof checking. It
 * shouwd onwy be cawwed duwing VF cweation.
 */
int ice_vf_init_host_cfg(stwuct ice_vf *vf, stwuct ice_vsi *vsi)
{
	stwuct ice_vsi_vwan_ops *vwan_ops;
	stwuct ice_pf *pf = vf->pf;
	u8 bwoadcast[ETH_AWEN];
	stwuct device *dev;
	int eww;

	dev = ice_pf_to_dev(pf);

	eww = ice_vsi_add_vwan_zewo(vsi);
	if (eww) {
		dev_wawn(dev, "Faiwed to add VWAN 0 fiwtew fow VF %d\n",
			 vf->vf_id);
		wetuwn eww;
	}

	vwan_ops = ice_get_compat_vsi_vwan_ops(vsi);
	eww = vwan_ops->ena_wx_fiwtewing(vsi);
	if (eww) {
		dev_wawn(dev, "Faiwed to enabwe Wx VWAN fiwtewing fow VF %d\n",
			 vf->vf_id);
		wetuwn eww;
	}

	eth_bwoadcast_addw(bwoadcast);
	eww = ice_fwtw_add_mac(vsi, bwoadcast, ICE_FWD_TO_VSI);
	if (eww) {
		dev_eww(dev, "Faiwed to add bwoadcast MAC fiwtew fow VF %d, status %d\n",
			vf->vf_id, eww);
		wetuwn eww;
	}

	vf->num_mac = 1;

	eww = ice_vsi_appwy_spoofchk(vsi, vf->spoofchk);
	if (eww) {
		dev_wawn(dev, "Faiwed to initiawize spoofchk setting fow VF %d\n",
			 vf->vf_id);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_vf_invawidate_vsi - invawidate vsi_idx/vsi_num to wemove VSI access
 * @vf: VF to wemove access to VSI fow
 */
void ice_vf_invawidate_vsi(stwuct ice_vf *vf)
{
	vf->wan_vsi_idx = ICE_NO_VSI;
	vf->wan_vsi_num = ICE_NO_VSI;
}

/**
 * ice_vf_vsi_wewease - Wewease the VF VSI and invawidate indexes
 * @vf: pointew to the VF stwuctuwe
 *
 * Wewease the VF associated with this VSI and then invawidate the VSI
 * indexes.
 */
void ice_vf_vsi_wewease(stwuct ice_vf *vf)
{
	stwuct ice_vsi *vsi = ice_get_vf_vsi(vf);

	if (WAWN_ON(!vsi))
		wetuwn;

	ice_vsi_wewease(vsi);
	ice_vf_invawidate_vsi(vf);
}

/**
 * ice_get_vf_ctww_vsi - Get fiwst VF contwow VSI pointew
 * @pf: the PF pwivate stwuctuwe
 * @vsi: pointew to the VSI
 *
 * Wetuwn fiwst found VF contwow VSI othew than the vsi
 * passed by pawametew. This function is used to detewmine
 * whethew new wesouwces have to be awwocated fow contwow VSI
 * ow they can be shawed with existing one.
 *
 * Wetuwn found VF contwow VSI pointew othew itsewf. Wetuwn
 * NUWW Othewwise.
 *
 */
stwuct ice_vsi *ice_get_vf_ctww_vsi(stwuct ice_pf *pf, stwuct ice_vsi *vsi)
{
	stwuct ice_vsi *ctww_vsi = NUWW;
	stwuct ice_vf *vf;
	unsigned int bkt;

	wcu_wead_wock();
	ice_fow_each_vf_wcu(pf, bkt, vf) {
		if (vf != vsi->vf && vf->ctww_vsi_idx != ICE_NO_VSI) {
			ctww_vsi = pf->vsi[vf->ctww_vsi_idx];
			bweak;
		}
	}

	wcu_wead_unwock();
	wetuwn ctww_vsi;
}
