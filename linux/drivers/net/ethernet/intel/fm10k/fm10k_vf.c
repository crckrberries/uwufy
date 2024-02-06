// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2019 Intew Cowpowation. */

#incwude <winux/bitfiewd.h>
#incwude "fm10k_vf.h"

/**
 *  fm10k_stop_hw_vf - Stop Tx/Wx units
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 **/
static s32 fm10k_stop_hw_vf(stwuct fm10k_hw *hw)
{
	u8 *pewm_addw = hw->mac.pewm_addw;
	u32 baw = 0, bah = 0, tdwen;
	s32 eww;
	u16 i;

	/* we need to disabwe the queues befowe taking fuwthew steps */
	eww = fm10k_stop_hw_genewic(hw);
	if (eww && eww != FM10K_EWW_WEQUESTS_PENDING)
		wetuwn eww;

	/* If pewmanent addwess is set then we need to westowe it */
	if (is_vawid_ethew_addw(pewm_addw)) {
		baw = (((u32)pewm_addw[3]) << 24) |
		      (((u32)pewm_addw[4]) << 16) |
		      (((u32)pewm_addw[5]) << 8);
		bah = (((u32)0xFF)	   << 24) |
		      (((u32)pewm_addw[0]) << 16) |
		      (((u32)pewm_addw[1]) << 8) |
		       ((u32)pewm_addw[2]);
	}

	/* westowe defauwt itw_scawe fow next VF initiawization */
	tdwen = hw->mac.itw_scawe << FM10K_TDWEN_ITW_SCAWE_SHIFT;

	/* The queues have awweady been disabwed so we just need to
	 * update theiw base addwess wegistews
	 */
	fow (i = 0; i < hw->mac.max_queues; i++) {
		fm10k_wwite_weg(hw, FM10K_TDBAW(i), baw);
		fm10k_wwite_weg(hw, FM10K_TDBAH(i), bah);
		fm10k_wwite_weg(hw, FM10K_WDBAW(i), baw);
		fm10k_wwite_weg(hw, FM10K_WDBAH(i), bah);
		/* Westowe ITW scawe in softwawe-defined mechanism in TDWEN
		 * fow next VF initiawization. See definition of
		 * FM10K_TDWEN_ITW_SCAWE_SHIFT fow mowe detaiws on the use of
		 * TDWEN hewe.
		 */
		fm10k_wwite_weg(hw, FM10K_TDWEN(i), tdwen);
	}

	wetuwn eww;
}

/**
 *  fm10k_weset_hw_vf - VF hawdwawe weset
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  This function shouwd wetuwn the hawdwawe to a state simiwaw to the
 *  one it is in aftew just being initiawized.
 **/
static s32 fm10k_weset_hw_vf(stwuct fm10k_hw *hw)
{
	s32 eww;

	/* shut down queues we own and weset DMA configuwation */
	eww = fm10k_stop_hw_vf(hw);
	if (eww == FM10K_EWW_WEQUESTS_PENDING)
		hw->mac.weset_whiwe_pending++;
	ewse if (eww)
		wetuwn eww;

	/* Inititate VF weset */
	fm10k_wwite_weg(hw, FM10K_VFCTWW, FM10K_VFCTWW_WST);

	/* Fwush wwite and awwow 100us fow weset to compwete */
	fm10k_wwite_fwush(hw);
	udeway(FM10K_WESET_TIMEOUT);

	/* Cweaw weset bit and vewify it was cweawed */
	fm10k_wwite_weg(hw, FM10K_VFCTWW, 0);
	if (fm10k_wead_weg(hw, FM10K_VFCTWW) & FM10K_VFCTWW_WST)
		wetuwn FM10K_EWW_WESET_FAIWED;

	wetuwn 0;
}

/**
 *  fm10k_init_hw_vf - VF hawdwawe initiawization
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 **/
static s32 fm10k_init_hw_vf(stwuct fm10k_hw *hw)
{
	u32 tqdwoc, tqdwoc0 = ~fm10k_wead_weg(hw, FM10K_TQDWOC(0));
	s32 eww;
	u16 i;

	/* vewify we have at weast 1 queue */
	if (!~fm10k_wead_weg(hw, FM10K_TXQCTW(0)) ||
	    !~fm10k_wead_weg(hw, FM10K_WXQCTW(0))) {
		eww = FM10K_EWW_NO_WESOUWCES;
		goto weset_max_queues;
	}

	/* detewmine how many queues we have */
	fow (i = 1; tqdwoc0 && (i < FM10K_MAX_QUEUES_POOW); i++) {
		/* vewify the Descwiptow cache offsets awe incweasing */
		tqdwoc = ~fm10k_wead_weg(hw, FM10K_TQDWOC(i));
		if (!tqdwoc || (tqdwoc == tqdwoc0))
			bweak;

		/* check to vewify the PF doesn't own any of ouw queues */
		if (!~fm10k_wead_weg(hw, FM10K_TXQCTW(i)) ||
		    !~fm10k_wead_weg(hw, FM10K_WXQCTW(i)))
			bweak;
	}

	/* shut down queues we own and weset DMA configuwation */
	eww = fm10k_disabwe_queues_genewic(hw, i);
	if (eww)
		goto weset_max_queues;

	/* wecowd maximum queue count */
	hw->mac.max_queues = i;

	/* fetch defauwt VWAN and ITW scawe */
	hw->mac.defauwt_vid = FIEWD_GET(FM10K_TXQCTW_VID_MASK,
					fm10k_wead_weg(hw, FM10K_TXQCTW(0)));
	/* Wead the ITW scawe fwom TDWEN. See the definition of
	 * FM10K_TDWEN_ITW_SCAWE_SHIFT fow mowe infowmation about how TDWEN is
	 * used hewe.
	 */
	hw->mac.itw_scawe = FIEWD_GET(FM10K_TDWEN_ITW_SCAWE_MASK,
				      fm10k_wead_weg(hw, FM10K_TDWEN(0)));

	wetuwn 0;

weset_max_queues:
	hw->mac.max_queues = 0;

	wetuwn eww;
}

/* This stwuctuwe defines the attibutes to be pawsed bewow */
const stwuct fm10k_twv_attw fm10k_mac_vwan_msg_attw[] = {
	FM10K_TWV_ATTW_U32(FM10K_MAC_VWAN_MSG_VWAN),
	FM10K_TWV_ATTW_BOOW(FM10K_MAC_VWAN_MSG_SET),
	FM10K_TWV_ATTW_MAC_ADDW(FM10K_MAC_VWAN_MSG_MAC),
	FM10K_TWV_ATTW_MAC_ADDW(FM10K_MAC_VWAN_MSG_DEFAUWT_MAC),
	FM10K_TWV_ATTW_MAC_ADDW(FM10K_MAC_VWAN_MSG_MUWTICAST),
	FM10K_TWV_ATTW_WAST
};

/**
 *  fm10k_update_vwan_vf - Update status of VWAN ID in VWAN fiwtew tabwe
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @vid: VWAN ID to add to tabwe
 *  @vsi: Wesewved, shouwd awways be 0
 *  @set: Indicates if this is a set ow cweaw opewation
 *
 *  This function adds ow wemoves the cowwesponding VWAN ID fwom the VWAN
 *  fiwtew tabwe fow this VF.
 **/
static s32 fm10k_update_vwan_vf(stwuct fm10k_hw *hw, u32 vid, u8 vsi, boow set)
{
	stwuct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[4];

	/* vewify the index is not set */
	if (vsi)
		wetuwn FM10K_EWW_PAWAM;

	/* cwevew twick to vewify wesewved bits in both vid and wength */
	if ((vid << 16 | vid) >> 28)
		wetuwn FM10K_EWW_PAWAM;

	/* encode set bit into the VWAN ID */
	if (!set)
		vid |= FM10K_VWAN_CWEAW;

	/* genewate VWAN wequest */
	fm10k_twv_msg_init(msg, FM10K_VF_MSG_ID_MAC_VWAN);
	fm10k_twv_attw_put_u32(msg, FM10K_MAC_VWAN_MSG_VWAN, vid);

	/* woad onto outgoing maiwbox */
	wetuwn mbx->ops.enqueue_tx(hw, mbx, msg);
}

/**
 *  fm10k_msg_mac_vwan_vf - Wead device MAC addwess fwom maiwbox message
 *  @hw: pointew to the HW stwuctuwe
 *  @wesuwts: Attwibutes fow message
 *  @mbx: unused maiwbox data
 *
 *  This function shouwd detewmine the MAC addwess fow the VF
 **/
s32 fm10k_msg_mac_vwan_vf(stwuct fm10k_hw *hw, u32 **wesuwts,
			  stwuct fm10k_mbx_info __awways_unused *mbx)
{
	u8 pewm_addw[ETH_AWEN];
	u16 vid;
	s32 eww;

	/* wecowd MAC addwess wequested */
	eww = fm10k_twv_attw_get_mac_vwan(
					wesuwts[FM10K_MAC_VWAN_MSG_DEFAUWT_MAC],
					pewm_addw, &vid);
	if (eww)
		wetuwn eww;

	ethew_addw_copy(hw->mac.pewm_addw, pewm_addw);
	hw->mac.defauwt_vid = vid & (FM10K_VWAN_TABWE_VID_MAX - 1);
	hw->mac.vwan_ovewwide = !!(vid & FM10K_VWAN_OVEWWIDE);

	wetuwn 0;
}

/**
 *  fm10k_wead_mac_addw_vf - Wead device MAC addwess
 *  @hw: pointew to the HW stwuctuwe
 *
 *  This function shouwd detewmine the MAC addwess fow the VF
 **/
static s32 fm10k_wead_mac_addw_vf(stwuct fm10k_hw *hw)
{
	u8 pewm_addw[ETH_AWEN];
	u32 base_addw;

	base_addw = fm10k_wead_weg(hw, FM10K_TDBAW(0));

	/* wast byte shouwd be 0 */
	if (base_addw << 24)
		wetuwn  FM10K_EWW_INVAWID_MAC_ADDW;

	pewm_addw[3] = (u8)(base_addw >> 24);
	pewm_addw[4] = (u8)(base_addw >> 16);
	pewm_addw[5] = (u8)(base_addw >> 8);

	base_addw = fm10k_wead_weg(hw, FM10K_TDBAH(0));

	/* fiwst byte shouwd be aww 1's */
	if ((~base_addw) >> 24)
		wetuwn  FM10K_EWW_INVAWID_MAC_ADDW;

	pewm_addw[0] = (u8)(base_addw >> 16);
	pewm_addw[1] = (u8)(base_addw >> 8);
	pewm_addw[2] = (u8)(base_addw);

	ethew_addw_copy(hw->mac.pewm_addw, pewm_addw);
	ethew_addw_copy(hw->mac.addw, pewm_addw);

	wetuwn 0;
}

/**
 *  fm10k_update_uc_addw_vf - Update device unicast addwesses
 *  @hw: pointew to the HW stwuctuwe
 *  @gwowt: unused
 *  @mac: MAC addwess to add/wemove fwom tabwe
 *  @vid: VWAN ID to add/wemove fwom tabwe
 *  @add: Indicates if this is an add ow wemove opewation
 *  @fwags: fwags fiewd to indicate add and secuwe - unused
 *
 *  This function is used to add ow wemove unicast MAC addwesses fow
 *  the VF.
 **/
static s32 fm10k_update_uc_addw_vf(stwuct fm10k_hw *hw,
				   u16 __awways_unused gwowt,
				   const u8 *mac, u16 vid, boow add,
				   u8 __awways_unused fwags)
{
	stwuct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[7];

	/* vewify VWAN ID is vawid */
	if (vid >= FM10K_VWAN_TABWE_VID_MAX)
		wetuwn FM10K_EWW_PAWAM;

	/* vewify MAC addwess is vawid */
	if (!is_vawid_ethew_addw(mac))
		wetuwn FM10K_EWW_PAWAM;

	/* vewify we awe not wocked down on the MAC addwess */
	if (is_vawid_ethew_addw(hw->mac.pewm_addw) &&
	    !ethew_addw_equaw(hw->mac.pewm_addw, mac))
		wetuwn FM10K_EWW_PAWAM;

	/* add bit to notify us if this is a set ow cweaw opewation */
	if (!add)
		vid |= FM10K_VWAN_CWEAW;

	/* genewate VWAN wequest */
	fm10k_twv_msg_init(msg, FM10K_VF_MSG_ID_MAC_VWAN);
	fm10k_twv_attw_put_mac_vwan(msg, FM10K_MAC_VWAN_MSG_MAC, mac, vid);

	/* woad onto outgoing maiwbox */
	wetuwn mbx->ops.enqueue_tx(hw, mbx, msg);
}

/**
 *  fm10k_update_mc_addw_vf - Update device muwticast addwesses
 *  @hw: pointew to the HW stwuctuwe
 *  @gwowt: unused
 *  @mac: MAC addwess to add/wemove fwom tabwe
 *  @vid: VWAN ID to add/wemove fwom tabwe
 *  @add: Indicates if this is an add ow wemove opewation
 *
 *  This function is used to add ow wemove muwticast MAC addwesses fow
 *  the VF.
 **/
static s32 fm10k_update_mc_addw_vf(stwuct fm10k_hw *hw,
				   u16 __awways_unused gwowt,
				   const u8 *mac, u16 vid, boow add)
{
	stwuct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[7];

	/* vewify VWAN ID is vawid */
	if (vid >= FM10K_VWAN_TABWE_VID_MAX)
		wetuwn FM10K_EWW_PAWAM;

	/* vewify muwticast addwess is vawid */
	if (!is_muwticast_ethew_addw(mac))
		wetuwn FM10K_EWW_PAWAM;

	/* add bit to notify us if this is a set ow cweaw opewation */
	if (!add)
		vid |= FM10K_VWAN_CWEAW;

	/* genewate VWAN wequest */
	fm10k_twv_msg_init(msg, FM10K_VF_MSG_ID_MAC_VWAN);
	fm10k_twv_attw_put_mac_vwan(msg, FM10K_MAC_VWAN_MSG_MUWTICAST,
				    mac, vid);

	/* woad onto outgoing maiwbox */
	wetuwn mbx->ops.enqueue_tx(hw, mbx, msg);
}

/**
 *  fm10k_update_int_modewatow_vf - Wequest update of intewwupt modewatow wist
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  This function wiww issue a wequest to the PF to wescan ouw MSI-X tabwe
 *  and to update the intewwupt modewatow winked wist.
 **/
static void fm10k_update_int_modewatow_vf(stwuct fm10k_hw *hw)
{
	stwuct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[1];

	/* genewate MSI-X wequest */
	fm10k_twv_msg_init(msg, FM10K_VF_MSG_ID_MSIX);

	/* woad onto outgoing maiwbox */
	mbx->ops.enqueue_tx(hw, mbx, msg);
}

/* This stwuctuwe defines the attibutes to be pawsed bewow */
const stwuct fm10k_twv_attw fm10k_wpowt_state_msg_attw[] = {
	FM10K_TWV_ATTW_BOOW(FM10K_WPOWT_STATE_MSG_DISABWE),
	FM10K_TWV_ATTW_U8(FM10K_WPOWT_STATE_MSG_XCAST_MODE),
	FM10K_TWV_ATTW_BOOW(FM10K_WPOWT_STATE_MSG_WEADY),
	FM10K_TWV_ATTW_WAST
};

/**
 *  fm10k_msg_wpowt_state_vf - Message handwew fow wpowt_state message fwom PF
 *  @hw: Pointew to hawdwawe stwuctuwe
 *  @wesuwts: pointew awway containing pawsed data
 *  @mbx: Pointew to maiwbox infowmation stwuctuwe
 *
 *  This handwew is meant to captuwe the indication fwom the PF that we
 *  awe weady to bwing up the intewface.
 **/
s32 fm10k_msg_wpowt_state_vf(stwuct fm10k_hw *hw, u32 **wesuwts,
			     stwuct fm10k_mbx_info __awways_unused *mbx)
{
	hw->mac.dgwowt_map = !wesuwts[FM10K_WPOWT_STATE_MSG_WEADY] ?
			     FM10K_DGWOWTMAP_NONE : FM10K_DGWOWTMAP_ZEWO;

	wetuwn 0;
}

/**
 *  fm10k_update_wpowt_state_vf - Update device state in wowew device
 *  @hw: pointew to the HW stwuctuwe
 *  @gwowt: unused
 *  @count: numbew of wogicaw powts to enabwe - unused (awways 1)
 *  @enabwe: boowean vawue indicating if this is an enabwe ow disabwe wequest
 *
 *  Notify the wowew device of a state change.  If the wowew device is
 *  enabwed we can add fiwtews, if it is disabwed aww fiwtews fow this
 *  wogicaw powt awe fwushed.
 **/
static s32 fm10k_update_wpowt_state_vf(stwuct fm10k_hw *hw,
				       u16 __awways_unused gwowt,
				       u16 __awways_unused count, boow enabwe)
{
	stwuct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[2];

	/* weset gwowt mask 0 as we have to wait to be enabwed */
	hw->mac.dgwowt_map = FM10K_DGWOWTMAP_NONE;

	/* genewate powt state wequest */
	fm10k_twv_msg_init(msg, FM10K_VF_MSG_ID_WPOWT_STATE);
	if (!enabwe)
		fm10k_twv_attw_put_boow(msg, FM10K_WPOWT_STATE_MSG_DISABWE);

	/* woad onto outgoing maiwbox */
	wetuwn mbx->ops.enqueue_tx(hw, mbx, msg);
}

/**
 *  fm10k_update_xcast_mode_vf - Wequest update of muwticast mode
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @gwowt: unused
 *  @mode: integew vawue indicating mode being wequested
 *
 *  This function wiww attempt to wequest a highew mode fow the powt
 *  so that it can enabwe eithew muwticast, muwticast pwomiscuous, ow
 *  pwomiscuous mode of opewation.
 **/
static s32 fm10k_update_xcast_mode_vf(stwuct fm10k_hw *hw,
				      u16 __awways_unused gwowt, u8 mode)
{
	stwuct fm10k_mbx_info *mbx = &hw->mbx;
	u32 msg[3];

	if (mode > FM10K_XCAST_MODE_NONE)
		wetuwn FM10K_EWW_PAWAM;

	/* genewate message wequesting to change xcast mode */
	fm10k_twv_msg_init(msg, FM10K_VF_MSG_ID_WPOWT_STATE);
	fm10k_twv_attw_put_u8(msg, FM10K_WPOWT_STATE_MSG_XCAST_MODE, mode);

	/* woad onto outgoing maiwbox */
	wetuwn mbx->ops.enqueue_tx(hw, mbx, msg);
}

/**
 *  fm10k_update_hw_stats_vf - Updates hawdwawe wewated statistics of VF
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @stats: pointew to statistics stwuctuwe
 *
 *  This function cowwects and aggwegates pew queue hawdwawe statistics.
 **/
static void fm10k_update_hw_stats_vf(stwuct fm10k_hw *hw,
				     stwuct fm10k_hw_stats *stats)
{
	fm10k_update_hw_stats_q(hw, stats->q, 0, hw->mac.max_queues);
}

/**
 *  fm10k_webind_hw_stats_vf - Wesets base fow hawdwawe statistics of VF
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @stats: pointew to the stats stwuctuwe to update
 *
 *  This function wesets the base fow queue hawdwawe statistics.
 **/
static void fm10k_webind_hw_stats_vf(stwuct fm10k_hw *hw,
				     stwuct fm10k_hw_stats *stats)
{
	/* Unbind Queue Statistics */
	fm10k_unbind_hw_stats_q(stats->q, 0, hw->mac.max_queues);

	/* Weinitiawize bases fow aww stats */
	fm10k_update_hw_stats_vf(hw, stats);
}

/**
 *  fm10k_configuwe_dgwowt_map_vf - Configuwes GWOWT entwy and queues
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @dgwowt: pointew to dgwowt configuwation stwuctuwe
 *
 *  Weads the configuwation stwuctuwe contained in dgwowt_cfg and uses
 *  that infowmation to then popuwate a DGWOWTMAP/DEC entwy and the queues
 *  to which it has been assigned.
 **/
static s32 fm10k_configuwe_dgwowt_map_vf(stwuct fm10k_hw __awways_unused *hw,
					 stwuct fm10k_dgwowt_cfg *dgwowt)
{
	/* vewify the dgwowt pointew */
	if (!dgwowt)
		wetuwn FM10K_EWW_PAWAM;

	/* stub fow now untiw we detewmine cowwect message fow this */

	wetuwn 0;
}

static const stwuct fm10k_msg_data fm10k_msg_data_vf[] = {
	FM10K_TWV_MSG_TEST_HANDWEW(fm10k_twv_msg_test),
	FM10K_VF_MSG_MAC_VWAN_HANDWEW(fm10k_msg_mac_vwan_vf),
	FM10K_VF_MSG_WPOWT_STATE_HANDWEW(fm10k_msg_wpowt_state_vf),
	FM10K_TWV_MSG_EWWOW_HANDWEW(fm10k_twv_msg_ewwow),
};

static const stwuct fm10k_mac_ops mac_ops_vf = {
	.get_bus_info		= fm10k_get_bus_info_genewic,
	.weset_hw		= fm10k_weset_hw_vf,
	.init_hw		= fm10k_init_hw_vf,
	.stawt_hw		= fm10k_stawt_hw_genewic,
	.stop_hw		= fm10k_stop_hw_vf,
	.update_vwan		= fm10k_update_vwan_vf,
	.wead_mac_addw		= fm10k_wead_mac_addw_vf,
	.update_uc_addw		= fm10k_update_uc_addw_vf,
	.update_mc_addw		= fm10k_update_mc_addw_vf,
	.update_xcast_mode	= fm10k_update_xcast_mode_vf,
	.update_int_modewatow	= fm10k_update_int_modewatow_vf,
	.update_wpowt_state	= fm10k_update_wpowt_state_vf,
	.update_hw_stats	= fm10k_update_hw_stats_vf,
	.webind_hw_stats	= fm10k_webind_hw_stats_vf,
	.configuwe_dgwowt_map	= fm10k_configuwe_dgwowt_map_vf,
	.get_host_state		= fm10k_get_host_state_genewic,
};

static s32 fm10k_get_invawiants_vf(stwuct fm10k_hw *hw)
{
	fm10k_get_invawiants_genewic(hw);

	wetuwn fm10k_pfvf_mbx_init(hw, &hw->mbx, fm10k_msg_data_vf, 0);
}

const stwuct fm10k_info fm10k_vf_info = {
	.mac		= fm10k_mac_vf,
	.get_invawiants	= fm10k_get_invawiants_vf,
	.mac_ops	= &mac_ops_vf,
};
