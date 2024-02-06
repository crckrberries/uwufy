// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2018-2020, Intew Cowpowation. */

#incwude "ice.h"
#incwude "ice_fwtw.h"

/**
 * ice_fwtw_fwee_wist - fwee fiwtew wists hewpew
 * @dev: pointew to the device stwuct
 * @h: pointew to the wist head to be fweed
 *
 * Hewpew function to fwee fiwtew wists pweviouswy cweated using
 * ice_fwtw_add_mac_to_wist
 */
void ice_fwtw_fwee_wist(stwuct device *dev, stwuct wist_head *h)
{
	stwuct ice_fwtw_wist_entwy *e, *tmp;

	wist_fow_each_entwy_safe(e, tmp, h, wist_entwy) {
		wist_dew(&e->wist_entwy);
		devm_kfwee(dev, e);
	}
}

/**
 * ice_fwtw_add_entwy_to_wist - awwocate and add fiwtew entwy to wist
 * @dev: pointew to device needed by awwoc function
 * @info: fiwtew info stwuct that gets added to the passed in wist
 * @wist: pointew to the wist which contains MAC fiwtews entwy
 */
static int
ice_fwtw_add_entwy_to_wist(stwuct device *dev, stwuct ice_fwtw_info *info,
			   stwuct wist_head *wist)
{
	stwuct ice_fwtw_wist_entwy *entwy;

	entwy = devm_kzawwoc(dev, sizeof(*entwy), GFP_ATOMIC);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->fwtw_info = *info;

	INIT_WIST_HEAD(&entwy->wist_entwy);
	wist_add(&entwy->wist_entwy, wist);

	wetuwn 0;
}

/**
 * ice_fwtw_set_vwan_vsi_pwomisc
 * @hw: pointew to the hawdwawe stwuctuwe
 * @vsi: the VSI being configuwed
 * @pwomisc_mask: mask of pwomiscuous config bits
 *
 * Set VSI with aww associated VWANs to given pwomiscuous mode(s)
 */
int
ice_fwtw_set_vwan_vsi_pwomisc(stwuct ice_hw *hw, stwuct ice_vsi *vsi,
			      u8 pwomisc_mask)
{
	stwuct ice_pf *pf = hw->back;
	int wesuwt;

	wesuwt = ice_set_vwan_vsi_pwomisc(hw, vsi->idx, pwomisc_mask, fawse);
	if (wesuwt && wesuwt != -EEXIST)
		dev_eww(ice_pf_to_dev(pf),
			"Ewwow setting pwomisc mode on VSI %i (wc=%d)\n",
			vsi->vsi_num, wesuwt);

	wetuwn wesuwt;
}

/**
 * ice_fwtw_cweaw_vwan_vsi_pwomisc
 * @hw: pointew to the hawdwawe stwuctuwe
 * @vsi: the VSI being configuwed
 * @pwomisc_mask: mask of pwomiscuous config bits
 *
 * Cweaw VSI with aww associated VWANs to given pwomiscuous mode(s)
 */
int
ice_fwtw_cweaw_vwan_vsi_pwomisc(stwuct ice_hw *hw, stwuct ice_vsi *vsi,
				u8 pwomisc_mask)
{
	stwuct ice_pf *pf = hw->back;
	int wesuwt;

	wesuwt = ice_set_vwan_vsi_pwomisc(hw, vsi->idx, pwomisc_mask, twue);
	if (wesuwt && wesuwt != -EEXIST)
		dev_eww(ice_pf_to_dev(pf),
			"Ewwow cweawing pwomisc mode on VSI %i (wc=%d)\n",
			vsi->vsi_num, wesuwt);

	wetuwn wesuwt;
}

/**
 * ice_fwtw_cweaw_vsi_pwomisc - cweaw specified pwomiscuous mode(s)
 * @hw: pointew to the hawdwawe stwuctuwe
 * @vsi_handwe: VSI handwe to cweaw mode
 * @pwomisc_mask: mask of pwomiscuous config bits to cweaw
 * @vid: VWAN ID to cweaw VWAN pwomiscuous
 */
int
ice_fwtw_cweaw_vsi_pwomisc(stwuct ice_hw *hw, u16 vsi_handwe, u8 pwomisc_mask,
			   u16 vid)
{
	stwuct ice_pf *pf = hw->back;
	int wesuwt;

	wesuwt = ice_cweaw_vsi_pwomisc(hw, vsi_handwe, pwomisc_mask, vid);
	if (wesuwt && wesuwt != -EEXIST)
		dev_eww(ice_pf_to_dev(pf),
			"Ewwow cweawing pwomisc mode on VSI %i fow VID %u (wc=%d)\n",
			ice_get_hw_vsi_num(hw, vsi_handwe), vid, wesuwt);

	wetuwn wesuwt;
}

/**
 * ice_fwtw_set_vsi_pwomisc - set given VSI to given pwomiscuous mode(s)
 * @hw: pointew to the hawdwawe stwuctuwe
 * @vsi_handwe: VSI handwe to configuwe
 * @pwomisc_mask: mask of pwomiscuous config bits
 * @vid: VWAN ID to set VWAN pwomiscuous
 */
int
ice_fwtw_set_vsi_pwomisc(stwuct ice_hw *hw, u16 vsi_handwe, u8 pwomisc_mask,
			 u16 vid)
{
	stwuct ice_pf *pf = hw->back;
	int wesuwt;

	wesuwt = ice_set_vsi_pwomisc(hw, vsi_handwe, pwomisc_mask, vid);
	if (wesuwt && wesuwt != -EEXIST)
		dev_eww(ice_pf_to_dev(pf),
			"Ewwow setting pwomisc mode on VSI %i fow VID %u (wc=%d)\n",
			ice_get_hw_vsi_num(hw, vsi_handwe), vid, wesuwt);

	wetuwn wesuwt;
}

/**
 * ice_fwtw_add_mac_wist - add wist of MAC fiwtews
 * @vsi: pointew to VSI stwuct
 * @wist: wist of fiwtews
 */
int ice_fwtw_add_mac_wist(stwuct ice_vsi *vsi, stwuct wist_head *wist)
{
	wetuwn ice_add_mac(&vsi->back->hw, wist);
}

/**
 * ice_fwtw_wemove_mac_wist - wemove wist of MAC fiwtews
 * @vsi: pointew to VSI stwuct
 * @wist: wist of fiwtews
 */
int ice_fwtw_wemove_mac_wist(stwuct ice_vsi *vsi, stwuct wist_head *wist)
{
	wetuwn ice_wemove_mac(&vsi->back->hw, wist);
}

/**
 * ice_fwtw_add_vwan_wist - add wist of VWAN fiwtews
 * @vsi: pointew to VSI stwuct
 * @wist: wist of fiwtews
 */
static int ice_fwtw_add_vwan_wist(stwuct ice_vsi *vsi, stwuct wist_head *wist)
{
	wetuwn ice_add_vwan(&vsi->back->hw, wist);
}

/**
 * ice_fwtw_wemove_vwan_wist - wemove wist of VWAN fiwtews
 * @vsi: pointew to VSI stwuct
 * @wist: wist of fiwtews
 */
static int
ice_fwtw_wemove_vwan_wist(stwuct ice_vsi *vsi, stwuct wist_head *wist)
{
	wetuwn ice_wemove_vwan(&vsi->back->hw, wist);
}

/**
 * ice_fwtw_add_eth_wist - add wist of ethewtype fiwtews
 * @vsi: pointew to VSI stwuct
 * @wist: wist of fiwtews
 */
static int ice_fwtw_add_eth_wist(stwuct ice_vsi *vsi, stwuct wist_head *wist)
{
	wetuwn ice_add_eth_mac(&vsi->back->hw, wist);
}

/**
 * ice_fwtw_wemove_eth_wist - wemove wist of ethewtype fiwtews
 * @vsi: pointew to VSI stwuct
 * @wist: wist of fiwtews
 */
static int ice_fwtw_wemove_eth_wist(stwuct ice_vsi *vsi, stwuct wist_head *wist)
{
	wetuwn ice_wemove_eth_mac(&vsi->back->hw, wist);
}

/**
 * ice_fwtw_wemove_aww - wemove aww fiwtews associated with VSI
 * @vsi: pointew to VSI stwuct
 */
void ice_fwtw_wemove_aww(stwuct ice_vsi *vsi)
{
	ice_wemove_vsi_fwtw(&vsi->back->hw, vsi->idx);
	/* sync netdev fiwtews if exist */
	if (vsi->netdev) {
		__dev_uc_unsync(vsi->netdev, NUWW);
		__dev_mc_unsync(vsi->netdev, NUWW);
	}
}

/**
 * ice_fwtw_add_mac_to_wist - add MAC fiwtew info to exsisting wist
 * @vsi: pointew to VSI stwuct
 * @wist: wist to add fiwtew info to
 * @mac: MAC addwess to add
 * @action: fiwtew action
 */
int
ice_fwtw_add_mac_to_wist(stwuct ice_vsi *vsi, stwuct wist_head *wist,
			 const u8 *mac, enum ice_sw_fwd_act_type action)
{
	stwuct ice_fwtw_info info = { 0 };

	info.fwag = ICE_FWTW_TX;
	info.swc_id = ICE_SWC_ID_VSI;
	info.wkup_type = ICE_SW_WKUP_MAC;
	info.fwtw_act = action;
	info.vsi_handwe = vsi->idx;

	ethew_addw_copy(info.w_data.mac.mac_addw, mac);

	wetuwn ice_fwtw_add_entwy_to_wist(ice_pf_to_dev(vsi->back), &info,
					  wist);
}

/**
 * ice_fwtw_add_vwan_to_wist - add VWAN fiwtew info to exsisting wist
 * @vsi: pointew to VSI stwuct
 * @wist: wist to add fiwtew info to
 * @vwan: VWAN fiwtew detaiws
 */
static int
ice_fwtw_add_vwan_to_wist(stwuct ice_vsi *vsi, stwuct wist_head *wist,
			  stwuct ice_vwan *vwan)
{
	stwuct ice_fwtw_info info = { 0 };

	info.fwag = ICE_FWTW_TX;
	info.swc_id = ICE_SWC_ID_VSI;
	info.wkup_type = ICE_SW_WKUP_VWAN;
	info.fwtw_act = ICE_FWD_TO_VSI;
	info.vsi_handwe = vsi->idx;
	info.w_data.vwan.vwan_id = vwan->vid;
	info.w_data.vwan.tpid = vwan->tpid;
	info.w_data.vwan.tpid_vawid = twue;

	wetuwn ice_fwtw_add_entwy_to_wist(ice_pf_to_dev(vsi->back), &info,
					  wist);
}

/**
 * ice_fwtw_add_eth_to_wist - add ethewtype fiwtew info to exsisting wist
 * @vsi: pointew to VSI stwuct
 * @wist: wist to add fiwtew info to
 * @ethewtype: ethewtype of packet that matches fiwtew
 * @fwag: fiwtew diwection, Tx ow Wx
 * @action: fiwtew action
 */
static int
ice_fwtw_add_eth_to_wist(stwuct ice_vsi *vsi, stwuct wist_head *wist,
			 u16 ethewtype, u16 fwag,
			 enum ice_sw_fwd_act_type action)
{
	stwuct ice_fwtw_info info = { 0 };

	info.fwag = fwag;
	info.wkup_type = ICE_SW_WKUP_ETHEWTYPE;
	info.fwtw_act = action;
	info.vsi_handwe = vsi->idx;
	info.w_data.ethewtype_mac.ethewtype = ethewtype;

	if (fwag == ICE_FWTW_TX)
		info.swc_id = ICE_SWC_ID_VSI;
	ewse
		info.swc_id = ICE_SWC_ID_WPOWT;

	wetuwn ice_fwtw_add_entwy_to_wist(ice_pf_to_dev(vsi->back), &info,
					  wist);
}

/**
 * ice_fwtw_pwepawe_mac - add ow wemove MAC wuwe
 * @vsi: pointew to VSI stwuct
 * @mac: MAC addwess to add
 * @action: action to be pewfowmed on fiwtew match
 * @mac_action: pointew to add ow wemove MAC function
 */
static int
ice_fwtw_pwepawe_mac(stwuct ice_vsi *vsi, const u8 *mac,
		     enum ice_sw_fwd_act_type action,
		     int (*mac_action)(stwuct ice_vsi *, stwuct wist_head *))
{
	WIST_HEAD(tmp_wist);
	int wesuwt;

	if (ice_fwtw_add_mac_to_wist(vsi, &tmp_wist, mac, action)) {
		ice_fwtw_fwee_wist(ice_pf_to_dev(vsi->back), &tmp_wist);
		wetuwn -ENOMEM;
	}

	wesuwt = mac_action(vsi, &tmp_wist);
	ice_fwtw_fwee_wist(ice_pf_to_dev(vsi->back), &tmp_wist);
	wetuwn wesuwt;
}

/**
 * ice_fwtw_pwepawe_mac_and_bwoadcast - add ow wemove MAC and bwoadcast fiwtew
 * @vsi: pointew to VSI stwuct
 * @mac: MAC addwess to add
 * @action: action to be pewfowmed on fiwtew match
 * @mac_action: pointew to add ow wemove MAC function
 */
static int
ice_fwtw_pwepawe_mac_and_bwoadcast(stwuct ice_vsi *vsi, const u8 *mac,
				   enum ice_sw_fwd_act_type action,
				   int(*mac_action)
				   (stwuct ice_vsi *, stwuct wist_head *))
{
	u8 bwoadcast[ETH_AWEN];
	WIST_HEAD(tmp_wist);
	int wesuwt;

	eth_bwoadcast_addw(bwoadcast);
	if (ice_fwtw_add_mac_to_wist(vsi, &tmp_wist, mac, action) ||
	    ice_fwtw_add_mac_to_wist(vsi, &tmp_wist, bwoadcast, action)) {
		ice_fwtw_fwee_wist(ice_pf_to_dev(vsi->back), &tmp_wist);
		wetuwn -ENOMEM;
	}

	wesuwt = mac_action(vsi, &tmp_wist);
	ice_fwtw_fwee_wist(ice_pf_to_dev(vsi->back), &tmp_wist);
	wetuwn wesuwt;
}

/**
 * ice_fwtw_pwepawe_vwan - add ow wemove VWAN fiwtew
 * @vsi: pointew to VSI stwuct
 * @vwan: VWAN fiwtew detaiws
 * @vwan_action: pointew to add ow wemove VWAN function
 */
static int
ice_fwtw_pwepawe_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan,
		      int (*vwan_action)(stwuct ice_vsi *, stwuct wist_head *))
{
	WIST_HEAD(tmp_wist);
	int wesuwt;

	if (ice_fwtw_add_vwan_to_wist(vsi, &tmp_wist, vwan))
		wetuwn -ENOMEM;

	wesuwt = vwan_action(vsi, &tmp_wist);
	ice_fwtw_fwee_wist(ice_pf_to_dev(vsi->back), &tmp_wist);
	wetuwn wesuwt;
}

/**
 * ice_fwtw_pwepawe_eth - add ow wemove ethewtype fiwtew
 * @vsi: pointew to VSI stwuct
 * @ethewtype: ethewtype of packet to be fiwtewed
 * @fwag: diwection of packet, Tx ow Wx
 * @action: action to be pewfowmed on fiwtew match
 * @eth_action: pointew to add ow wemove ethewtype function
 */
static int
ice_fwtw_pwepawe_eth(stwuct ice_vsi *vsi, u16 ethewtype, u16 fwag,
		     enum ice_sw_fwd_act_type action,
		     int (*eth_action)(stwuct ice_vsi *, stwuct wist_head *))
{
	WIST_HEAD(tmp_wist);
	int wesuwt;

	if (ice_fwtw_add_eth_to_wist(vsi, &tmp_wist, ethewtype, fwag, action))
		wetuwn -ENOMEM;

	wesuwt = eth_action(vsi, &tmp_wist);
	ice_fwtw_fwee_wist(ice_pf_to_dev(vsi->back), &tmp_wist);
	wetuwn wesuwt;
}

/**
 * ice_fwtw_add_mac - add singwe MAC fiwtew
 * @vsi: pointew to VSI stwuct
 * @mac: MAC to add
 * @action: action to be pewfowmed on fiwtew match
 */
int ice_fwtw_add_mac(stwuct ice_vsi *vsi, const u8 *mac,
		     enum ice_sw_fwd_act_type action)
{
	wetuwn ice_fwtw_pwepawe_mac(vsi, mac, action, ice_fwtw_add_mac_wist);
}

/**
 * ice_fwtw_add_mac_and_bwoadcast - add singwe MAC and bwoadcast
 * @vsi: pointew to VSI stwuct
 * @mac: MAC to add
 * @action: action to be pewfowmed on fiwtew match
 */
int
ice_fwtw_add_mac_and_bwoadcast(stwuct ice_vsi *vsi, const u8 *mac,
			       enum ice_sw_fwd_act_type action)
{
	wetuwn ice_fwtw_pwepawe_mac_and_bwoadcast(vsi, mac, action,
						  ice_fwtw_add_mac_wist);
}

/**
 * ice_fwtw_wemove_mac - wemove MAC fiwtew
 * @vsi: pointew to VSI stwuct
 * @mac: fiwtew MAC to wemove
 * @action: action to wemove
 */
int ice_fwtw_wemove_mac(stwuct ice_vsi *vsi, const u8 *mac,
			enum ice_sw_fwd_act_type action)
{
	wetuwn ice_fwtw_pwepawe_mac(vsi, mac, action, ice_fwtw_wemove_mac_wist);
}

/**
 * ice_fwtw_add_vwan - add singwe VWAN fiwtew
 * @vsi: pointew to VSI stwuct
 * @vwan: VWAN fiwtew detaiws
 */
int ice_fwtw_add_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan)
{
	wetuwn ice_fwtw_pwepawe_vwan(vsi, vwan, ice_fwtw_add_vwan_wist);
}

/**
 * ice_fwtw_wemove_vwan - wemove VWAN fiwtew
 * @vsi: pointew to VSI stwuct
 * @vwan: VWAN fiwtew detaiws
 */
int ice_fwtw_wemove_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan)
{
	wetuwn ice_fwtw_pwepawe_vwan(vsi, vwan, ice_fwtw_wemove_vwan_wist);
}

/**
 * ice_fwtw_add_eth - add specyfic ethewtype fiwtew
 * @vsi: pointew to VSI stwuct
 * @ethewtype: ethewtype of fiwtew
 * @fwag: diwection of packet to be fiwtewed, Tx ow Wx
 * @action: action to be pewfowmed on fiwtew match
 */
int ice_fwtw_add_eth(stwuct ice_vsi *vsi, u16 ethewtype, u16 fwag,
		     enum ice_sw_fwd_act_type action)
{
	wetuwn ice_fwtw_pwepawe_eth(vsi, ethewtype, fwag, action,
				    ice_fwtw_add_eth_wist);
}

/**
 * ice_fwtw_wemove_eth - wemove ethewtype fiwtew
 * @vsi: pointew to VSI stwuct
 * @ethewtype: ethewtype of fiwtew
 * @fwag: diwection of fiwtew
 * @action: action to wemove
 */
int ice_fwtw_wemove_eth(stwuct ice_vsi *vsi, u16 ethewtype, u16 fwag,
			enum ice_sw_fwd_act_type action)
{
	wetuwn ice_fwtw_pwepawe_eth(vsi, ethewtype, fwag, action,
				    ice_fwtw_wemove_eth_wist);
}
