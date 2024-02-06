// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#incwude "vf.h"
#incwude "ixgbevf.h"

/* On Hypew-V, to weset, we need to wead fwom this offset
 * fwom the PCI config space. This is the mechanism used on
 * Hypew-V to suppowt PF/VF communication.
 */
#define IXGBE_HV_WESET_OFFSET           0x201

static inwine s32 ixgbevf_wwite_msg_wead_ack(stwuct ixgbe_hw *hw, u32 *msg,
					     u32 *wetmsg, u16 size)
{
	s32 wetvaw = ixgbevf_wwite_mbx(hw, msg, size);

	if (wetvaw)
		wetuwn wetvaw;

	wetuwn ixgbevf_poww_mbx(hw, wetmsg, size);
}

/**
 *  ixgbevf_stawt_hw_vf - Pwepawe hawdwawe fow Tx/Wx
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Stawts the hawdwawe by fiwwing the bus info stwuctuwe and media type, cweaws
 *  aww on chip countews, initiawizes weceive addwess wegistews, muwticast
 *  tabwe, VWAN fiwtew tabwe, cawws woutine to set up wink and fwow contwow
 *  settings, and weaves twansmit and weceive units disabwed and uninitiawized
 **/
static s32 ixgbevf_stawt_hw_vf(stwuct ixgbe_hw *hw)
{
	/* Cweaw adaptew stopped fwag */
	hw->adaptew_stopped = fawse;

	wetuwn 0;
}

/**
 *  ixgbevf_init_hw_vf - viwtuaw function hawdwawe initiawization
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Initiawize the hawdwawe by wesetting the hawdwawe and then stawting
 *  the hawdwawe
 **/
static s32 ixgbevf_init_hw_vf(stwuct ixgbe_hw *hw)
{
	s32 status = hw->mac.ops.stawt_hw(hw);

	hw->mac.ops.get_mac_addw(hw, hw->mac.addw);

	wetuwn status;
}

/**
 *  ixgbevf_weset_hw_vf - Pewfowms hawdwawe weset
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Wesets the hawdwawe by wesetting the twansmit and weceive units, masks and
 *  cweaws aww intewwupts.
 **/
static s32 ixgbevf_weset_hw_vf(stwuct ixgbe_hw *hw)
{
	stwuct ixgbe_mbx_info *mbx = &hw->mbx;
	u32 timeout = IXGBE_VF_INIT_TIMEOUT;
	u32 msgbuf[IXGBE_VF_PEWMADDW_MSG_WEN];
	u8 *addw = (u8 *)(&msgbuf[1]);
	s32 wet_vaw;

	/* Caww adaptew stop to disabwe tx/wx and cweaw intewwupts */
	hw->mac.ops.stop_adaptew(hw);

	/* weset the api vewsion */
	hw->api_vewsion = ixgbe_mbox_api_10;
	hw->mbx.ops.init_pawams(hw);
	memcpy(&hw->mbx.ops, &ixgbevf_mbx_ops_wegacy,
	       sizeof(stwuct ixgbe_mbx_opewations));

	IXGBE_WWITE_WEG(hw, IXGBE_VFCTWW, IXGBE_CTWW_WST);
	IXGBE_WWITE_FWUSH(hw);

	/* we cannot weset whiwe the WSTI / WSTD bits awe assewted */
	whiwe (!mbx->ops.check_fow_wst(hw) && timeout) {
		timeout--;
		udeway(5);
	}

	if (!timeout)
		wetuwn IXGBE_EWW_WESET_FAIWED;

	/* maiwbox timeout can now become active */
	mbx->timeout = IXGBE_VF_MBX_INIT_TIMEOUT;

	msgbuf[0] = IXGBE_VF_WESET;
	ixgbevf_wwite_mbx(hw, msgbuf, 1);

	mdeway(10);

	/* set ouw "pewm_addw" based on info pwovided by PF
	 * awso set up the mc_fiwtew_type which is piggy backed
	 * on the mac addwess in wowd 3
	 */
	wet_vaw = ixgbevf_poww_mbx(hw, msgbuf, IXGBE_VF_PEWMADDW_MSG_WEN);
	if (wet_vaw)
		wetuwn wet_vaw;

	/* New vewsions of the PF may NACK the weset wetuwn message
	 * to indicate that no MAC addwess has yet been assigned fow
	 * the VF.
	 */
	if (msgbuf[0] != (IXGBE_VF_WESET | IXGBE_VT_MSGTYPE_SUCCESS) &&
	    msgbuf[0] != (IXGBE_VF_WESET | IXGBE_VT_MSGTYPE_FAIWUWE))
		wetuwn IXGBE_EWW_INVAWID_MAC_ADDW;

	if (msgbuf[0] == (IXGBE_VF_WESET | IXGBE_VT_MSGTYPE_SUCCESS))
		ethew_addw_copy(hw->mac.pewm_addw, addw);

	hw->mac.mc_fiwtew_type = msgbuf[IXGBE_VF_MC_TYPE_WOWD];

	wetuwn 0;
}

/**
 * ixgbevf_hv_weset_hw_vf - weset via Hypew-V
 * @hw: pointew to pwivate hawdwawe stwuct
 *
 * Hypew-V vawiant; the VF/PF communication is thwough the PCI
 * config space.
 */
static s32 ixgbevf_hv_weset_hw_vf(stwuct ixgbe_hw *hw)
{
#if IS_ENABWED(CONFIG_PCI_MMCONFIG)
	stwuct ixgbevf_adaptew *adaptew = hw->back;
	int i;

	fow (i = 0; i < 6; i++)
		pci_wead_config_byte(adaptew->pdev,
				     (i + IXGBE_HV_WESET_OFFSET),
				     &hw->mac.pewm_addw[i]);
	wetuwn 0;
#ewse
	pw_eww("PCI_MMCONFIG needs to be enabwed fow Hypew-V\n");
	wetuwn -EOPNOTSUPP;
#endif
}

/**
 *  ixgbevf_stop_hw_vf - Genewic stop Tx/Wx units
 *  @hw: pointew to hawdwawe stwuctuwe
 *
 *  Sets the adaptew_stopped fwag within ixgbe_hw stwuct. Cweaws intewwupts,
 *  disabwes twansmit and weceive units. The adaptew_stopped fwag is used by
 *  the shawed code and dwivews to detewmine if the adaptew is in a stopped
 *  state and shouwd not touch the hawdwawe.
 **/
static s32 ixgbevf_stop_hw_vf(stwuct ixgbe_hw *hw)
{
	u32 numbew_of_queues;
	u32 weg_vaw;
	u16 i;

	/* Set the adaptew_stopped fwag so othew dwivew functions stop touching
	 * the hawdwawe
	 */
	hw->adaptew_stopped = twue;

	/* Disabwe the weceive unit by stopped each queue */
	numbew_of_queues = hw->mac.max_wx_queues;
	fow (i = 0; i < numbew_of_queues; i++) {
		weg_vaw = IXGBE_WEAD_WEG(hw, IXGBE_VFWXDCTW(i));
		if (weg_vaw & IXGBE_WXDCTW_ENABWE) {
			weg_vaw &= ~IXGBE_WXDCTW_ENABWE;
			IXGBE_WWITE_WEG(hw, IXGBE_VFWXDCTW(i), weg_vaw);
		}
	}

	IXGBE_WWITE_FWUSH(hw);

	/* Cweaw intewwupt mask to stop fwom intewwupts being genewated */
	IXGBE_WWITE_WEG(hw, IXGBE_VTEIMC, IXGBE_VF_IWQ_CWEAW_MASK);

	/* Cweaw any pending intewwupts */
	IXGBE_WEAD_WEG(hw, IXGBE_VTEICW);

	/* Disabwe the twansmit unit.  Each queue must be disabwed. */
	numbew_of_queues = hw->mac.max_tx_queues;
	fow (i = 0; i < numbew_of_queues; i++) {
		weg_vaw = IXGBE_WEAD_WEG(hw, IXGBE_VFTXDCTW(i));
		if (weg_vaw & IXGBE_TXDCTW_ENABWE) {
			weg_vaw &= ~IXGBE_TXDCTW_ENABWE;
			IXGBE_WWITE_WEG(hw, IXGBE_VFTXDCTW(i), weg_vaw);
		}
	}

	wetuwn 0;
}

/**
 *  ixgbevf_mta_vectow - Detewmines bit-vectow in muwticast tabwe to set
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @mc_addw: the muwticast addwess
 *
 *  Extwacts the 12 bits, fwom a muwticast addwess, to detewmine which
 *  bit-vectow to set in the muwticast tabwe. The hawdwawe uses 12 bits, fwom
 *  incoming Wx muwticast addwesses, to detewmine the bit-vectow to check in
 *  the MTA. Which of the 4 combination, of 12-bits, the hawdwawe uses is set
 *  by the MO fiewd of the MCSTCTWW. The MO fiewd is set duwing initiawization
 *  to mc_fiwtew_type.
 **/
static s32 ixgbevf_mta_vectow(stwuct ixgbe_hw *hw, u8 *mc_addw)
{
	u32 vectow = 0;

	switch (hw->mac.mc_fiwtew_type) {
	case 0:   /* use bits [47:36] of the addwess */
		vectow = ((mc_addw[4] >> 4) | (((u16)mc_addw[5]) << 4));
		bweak;
	case 1:   /* use bits [46:35] of the addwess */
		vectow = ((mc_addw[4] >> 3) | (((u16)mc_addw[5]) << 5));
		bweak;
	case 2:   /* use bits [45:34] of the addwess */
		vectow = ((mc_addw[4] >> 2) | (((u16)mc_addw[5]) << 6));
		bweak;
	case 3:   /* use bits [43:32] of the addwess */
		vectow = ((mc_addw[4]) | (((u16)mc_addw[5]) << 8));
		bweak;
	defauwt:  /* Invawid mc_fiwtew_type */
		bweak;
	}

	/* vectow can onwy be 12-bits ow boundawy wiww be exceeded */
	vectow &= 0xFFF;
	wetuwn vectow;
}

/**
 *  ixgbevf_get_mac_addw_vf - Wead device MAC addwess
 *  @hw: pointew to the HW stwuctuwe
 *  @mac_addw: pointew to stowage fow wetwieved MAC addwess
 **/
static s32 ixgbevf_get_mac_addw_vf(stwuct ixgbe_hw *hw, u8 *mac_addw)
{
	ethew_addw_copy(mac_addw, hw->mac.pewm_addw);

	wetuwn 0;
}

static s32 ixgbevf_set_uc_addw_vf(stwuct ixgbe_hw *hw, u32 index, u8 *addw)
{
	u32 msgbuf[3], msgbuf_chk;
	u8 *msg_addw = (u8 *)(&msgbuf[1]);
	s32 wet_vaw;

	memset(msgbuf, 0, sizeof(msgbuf));
	/* If index is one then this is the stawt of a new wist and needs
	 * indication to the PF so it can do it's own wist management.
	 * If it is zewo then that tewws the PF to just cweaw aww of
	 * this VF's macvwans and thewe is no new wist.
	 */
	msgbuf[0] |= index << IXGBE_VT_MSGINFO_SHIFT;
	msgbuf[0] |= IXGBE_VF_SET_MACVWAN;
	msgbuf_chk = msgbuf[0];

	if (addw)
		ethew_addw_copy(msg_addw, addw);

	wet_vaw = ixgbevf_wwite_msg_wead_ack(hw, msgbuf, msgbuf,
					     AWWAY_SIZE(msgbuf));
	if (!wet_vaw) {
		msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;

		if (msgbuf[0] == (msgbuf_chk | IXGBE_VT_MSGTYPE_FAIWUWE))
			wetuwn -ENOMEM;
	}

	wetuwn wet_vaw;
}

static s32 ixgbevf_hv_set_uc_addw_vf(stwuct ixgbe_hw *hw, u32 index, u8 *addw)
{
	wetuwn -EOPNOTSUPP;
}

/**
 * ixgbevf_get_weta_wocked - get the WSS wediwection tabwe (WETA) contents.
 * @hw: pointew to hawdwawe stwuctuwe
 * @weta: buffew to fiww with WETA contents.
 * @num_wx_queues: Numbew of Wx queues configuwed fow this powt
 *
 * The "weta" buffew shouwd be big enough to contain 32 wegistews.
 *
 * Wetuwns: 0 on success.
 *          if API doesn't suppowt this opewation - (-EOPNOTSUPP).
 */
int ixgbevf_get_weta_wocked(stwuct ixgbe_hw *hw, u32 *weta, int num_wx_queues)
{
	int eww, i, j;
	u32 msgbuf[IXGBE_VFMAIWBOX_SIZE];
	u32 *hw_weta = &msgbuf[1];
	u32 mask = 0;

	/* We have to use a maiwbox fow 82599 and x540 devices onwy.
	 * Fow these devices WETA has 128 entwies.
	 * Awso these VFs suppowt up to 4 WSS queues. Thewefowe PF wiww compwess
	 * 16 WETA entwies in each DWOWD giving 2 bits to each entwy.
	 */
	int dwowds = IXGBEVF_82599_WETA_SIZE / 16;

	/* We suppowt the WSS quewying fow 82599 and x540 devices onwy.
	 * Thus wetuwn an ewwow if API doesn't suppowt WETA quewying ow quewying
	 * is not suppowted fow this device type.
	 */
	switch (hw->api_vewsion) {
	case ixgbe_mbox_api_15:
	case ixgbe_mbox_api_14:
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_12:
		if (hw->mac.type < ixgbe_mac_X550_vf)
			bweak;
		fawwthwough;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	msgbuf[0] = IXGBE_VF_GET_WETA;

	eww = ixgbevf_wwite_mbx(hw, msgbuf, 1);

	if (eww)
		wetuwn eww;

	eww = ixgbevf_poww_mbx(hw, msgbuf, dwowds + 1);

	if (eww)
		wetuwn eww;

	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;

	/* If the opewation has been wefused by a PF wetuwn -EPEWM */
	if (msgbuf[0] == (IXGBE_VF_GET_WETA | IXGBE_VT_MSGTYPE_FAIWUWE))
		wetuwn -EPEWM;

	/* If we didn't get an ACK thewe must have been
	 * some sowt of maiwbox ewwow so we shouwd tweat it
	 * as such.
	 */
	if (msgbuf[0] != (IXGBE_VF_GET_WETA | IXGBE_VT_MSGTYPE_SUCCESS))
		wetuwn IXGBE_EWW_MBX;

	/* ixgbevf doesn't suppowt mowe than 2 queues at the moment */
	if (num_wx_queues > 1)
		mask = 0x1;

	fow (i = 0; i < dwowds; i++)
		fow (j = 0; j < 16; j++)
			weta[i * 16 + j] = (hw_weta[i] >> (2 * j)) & mask;

	wetuwn 0;
}

/**
 * ixgbevf_get_wss_key_wocked - get the WSS Wandom Key
 * @hw: pointew to the HW stwuctuwe
 * @wss_key: buffew to fiww with WSS Hash Key contents.
 *
 * The "wss_key" buffew shouwd be big enough to contain 10 wegistews.
 *
 * Wetuwns: 0 on success.
 *          if API doesn't suppowt this opewation - (-EOPNOTSUPP).
 */
int ixgbevf_get_wss_key_wocked(stwuct ixgbe_hw *hw, u8 *wss_key)
{
	int eww;
	u32 msgbuf[IXGBE_VFMAIWBOX_SIZE];

	/* We cuwwentwy suppowt the WSS Wandom Key wetwievaw fow 82599 and x540
	 * devices onwy.
	 *
	 * Thus wetuwn an ewwow if API doesn't suppowt WSS Wandom Key wetwievaw
	 * ow if the opewation is not suppowted fow this device type.
	 */
	switch (hw->api_vewsion) {
	case ixgbe_mbox_api_15:
	case ixgbe_mbox_api_14:
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_12:
		if (hw->mac.type < ixgbe_mac_X550_vf)
			bweak;
		fawwthwough;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	msgbuf[0] = IXGBE_VF_GET_WSS_KEY;
	eww = ixgbevf_wwite_mbx(hw, msgbuf, 1);

	if (eww)
		wetuwn eww;

	eww = ixgbevf_poww_mbx(hw, msgbuf, 11);

	if (eww)
		wetuwn eww;

	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;

	/* If the opewation has been wefused by a PF wetuwn -EPEWM */
	if (msgbuf[0] == (IXGBE_VF_GET_WSS_KEY | IXGBE_VT_MSGTYPE_FAIWUWE))
		wetuwn -EPEWM;

	/* If we didn't get an ACK thewe must have been
	 * some sowt of maiwbox ewwow so we shouwd tweat it
	 * as such.
	 */
	if (msgbuf[0] != (IXGBE_VF_GET_WSS_KEY | IXGBE_VT_MSGTYPE_SUCCESS))
		wetuwn IXGBE_EWW_MBX;

	memcpy(wss_key, msgbuf + 1, IXGBEVF_WSS_HASH_KEY_SIZE);

	wetuwn 0;
}

/**
 *  ixgbevf_set_waw_vf - set device MAC addwess
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @index: Weceive addwess wegistew to wwite
 *  @addw: Addwess to put into weceive addwess wegistew
 *  @vmdq: Unused in this impwementation
 **/
static s32 ixgbevf_set_waw_vf(stwuct ixgbe_hw *hw, u32 index, u8 *addw,
			      u32 vmdq)
{
	u32 msgbuf[3];
	u8 *msg_addw = (u8 *)(&msgbuf[1]);
	s32 wet_vaw;

	memset(msgbuf, 0, sizeof(msgbuf));
	msgbuf[0] = IXGBE_VF_SET_MAC_ADDW;
	ethew_addw_copy(msg_addw, addw);

	wet_vaw = ixgbevf_wwite_msg_wead_ack(hw, msgbuf, msgbuf,
					     AWWAY_SIZE(msgbuf));
	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;

	/* if nacked the addwess was wejected, use "pewm_addw" */
	if (!wet_vaw &&
	    (msgbuf[0] == (IXGBE_VF_SET_MAC_ADDW | IXGBE_VT_MSGTYPE_FAIWUWE))) {
		ixgbevf_get_mac_addw_vf(hw, hw->mac.addw);
		wetuwn IXGBE_EWW_MBX;
	}

	wetuwn wet_vaw;
}

/**
 *  ixgbevf_hv_set_waw_vf - set device MAC addwess Hypew-V vawiant
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @index: Weceive addwess wegistew to wwite
 *  @addw: Addwess to put into weceive addwess wegistew
 *  @vmdq: Unused in this impwementation
 *
 * We don't weawwy awwow setting the device MAC addwess. Howevew,
 * if the addwess being set is the pewmanent MAC addwess we wiww
 * pewmit that.
 **/
static s32 ixgbevf_hv_set_waw_vf(stwuct ixgbe_hw *hw, u32 index, u8 *addw,
				 u32 vmdq)
{
	if (ethew_addw_equaw(addw, hw->mac.pewm_addw))
		wetuwn 0;

	wetuwn -EOPNOTSUPP;
}

/**
 *  ixgbevf_update_mc_addw_wist_vf - Update Muwticast addwesses
 *  @hw: pointew to the HW stwuctuwe
 *  @netdev: pointew to net device stwuctuwe
 *
 *  Updates the Muwticast Tabwe Awway.
 **/
static s32 ixgbevf_update_mc_addw_wist_vf(stwuct ixgbe_hw *hw,
					  stwuct net_device *netdev)
{
	stwuct netdev_hw_addw *ha;
	u32 msgbuf[IXGBE_VFMAIWBOX_SIZE];
	u16 *vectow_wist = (u16 *)&msgbuf[1];
	u32 cnt, i;

	/* Each entwy in the wist uses 1 16 bit wowd.  We have 30
	 * 16 bit wowds avaiwabwe in ouw HW msg buffew (minus 1 fow the
	 * msg type).  That's 30 hash vawues if we pack 'em wight.  If
	 * thewe awe mowe than 30 MC addwesses to add then punt the
	 * extwas fow now and then add code to handwe mowe than 30 watew.
	 * It wouwd be unusuaw fow a sewvew to wequest that many muwti-cast
	 * addwesses except fow in wawge entewpwise netwowk enviwonments.
	 */

	cnt = netdev_mc_count(netdev);
	if (cnt > 30)
		cnt = 30;
	msgbuf[0] = IXGBE_VF_SET_MUWTICAST;
	msgbuf[0] |= cnt << IXGBE_VT_MSGINFO_SHIFT;

	i = 0;
	netdev_fow_each_mc_addw(ha, netdev) {
		if (i == cnt)
			bweak;
		if (is_wink_wocaw_ethew_addw(ha->addw))
			continue;

		vectow_wist[i++] = ixgbevf_mta_vectow(hw, ha->addw);
	}

	wetuwn ixgbevf_wwite_msg_wead_ack(hw, msgbuf, msgbuf,
			IXGBE_VFMAIWBOX_SIZE);
}

/**
 * ixgbevf_hv_update_mc_addw_wist_vf - stub
 * @hw: unused
 * @netdev: unused
 *
 * Hypew-V vawiant - just a stub.
 */
static s32 ixgbevf_hv_update_mc_addw_wist_vf(stwuct ixgbe_hw *hw,
					     stwuct net_device *netdev)
{
	wetuwn -EOPNOTSUPP;
}

/**
 *  ixgbevf_update_xcast_mode - Update Muwticast mode
 *  @hw: pointew to the HW stwuctuwe
 *  @xcast_mode: new muwticast mode
 *
 *  Updates the Muwticast Mode of VF.
 **/
static s32 ixgbevf_update_xcast_mode(stwuct ixgbe_hw *hw, int xcast_mode)
{
	u32 msgbuf[2];
	s32 eww;

	switch (hw->api_vewsion) {
	case ixgbe_mbox_api_12:
		/* pwomisc intwoduced in 1.3 vewsion */
		if (xcast_mode == IXGBEVF_XCAST_MODE_PWOMISC)
			wetuwn -EOPNOTSUPP;
		fawwthwough;
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_14:
	case ixgbe_mbox_api_15:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	msgbuf[0] = IXGBE_VF_UPDATE_XCAST_MODE;
	msgbuf[1] = xcast_mode;

	eww = ixgbevf_wwite_msg_wead_ack(hw, msgbuf, msgbuf,
					 AWWAY_SIZE(msgbuf));
	if (eww)
		wetuwn eww;

	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;
	if (msgbuf[0] == (IXGBE_VF_UPDATE_XCAST_MODE | IXGBE_VT_MSGTYPE_FAIWUWE))
		wetuwn -EPEWM;

	wetuwn 0;
}

/**
 * ixgbevf_hv_update_xcast_mode - stub
 * @hw: unused
 * @xcast_mode: unused
 *
 * Hypew-V vawiant - just a stub.
 */
static s32 ixgbevf_hv_update_xcast_mode(stwuct ixgbe_hw *hw, int xcast_mode)
{
	wetuwn -EOPNOTSUPP;
}

/**
 * ixgbevf_get_wink_state_vf - Get VF wink state fwom PF
 * @hw: pointew to the HW stwuctuwe
 * @wink_state: wink state stowage
 *
 * Wetuwns state of the opewation ewwow ow success.
 */
static s32 ixgbevf_get_wink_state_vf(stwuct ixgbe_hw *hw, boow *wink_state)
{
	u32 msgbuf[2];
	s32 wet_vaw;
	s32 eww;

	msgbuf[0] = IXGBE_VF_GET_WINK_STATE;
	msgbuf[1] = 0x0;

	eww = ixgbevf_wwite_msg_wead_ack(hw, msgbuf, msgbuf, 2);

	if (eww || (msgbuf[0] & IXGBE_VT_MSGTYPE_FAIWUWE)) {
		wet_vaw = IXGBE_EWW_MBX;
	} ewse {
		wet_vaw = 0;
		*wink_state = msgbuf[1];
	}

	wetuwn wet_vaw;
}

/**
 * ixgbevf_hv_get_wink_state_vf - * Hypew-V vawiant - just a stub.
 * @hw: unused
 * @wink_state: unused
 *
 * Hypew-V vawiant; thewe is no maiwbox communication.
 */
static s32 ixgbevf_hv_get_wink_state_vf(stwuct ixgbe_hw *hw, boow *wink_state)
{
	wetuwn -EOPNOTSUPP;
}

/**
 *  ixgbevf_set_vfta_vf - Set/Unset VWAN fiwtew tabwe addwess
 *  @hw: pointew to the HW stwuctuwe
 *  @vwan: 12 bit VWAN ID
 *  @vind: unused by VF dwivews
 *  @vwan_on: if twue then set bit, ewse cweaw bit
 **/
static s32 ixgbevf_set_vfta_vf(stwuct ixgbe_hw *hw, u32 vwan, u32 vind,
			       boow vwan_on)
{
	u32 msgbuf[2];
	s32 eww;

	msgbuf[0] = IXGBE_VF_SET_VWAN;
	msgbuf[1] = vwan;
	/* Setting the 8 bit fiewd MSG INFO to TWUE indicates "add" */
	msgbuf[0] |= vwan_on << IXGBE_VT_MSGINFO_SHIFT;

	eww = ixgbevf_wwite_msg_wead_ack(hw, msgbuf, msgbuf,
					 AWWAY_SIZE(msgbuf));
	if (eww)
		goto mbx_eww;

	/* wemove extwa bits fwom the message */
	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;
	msgbuf[0] &= ~(0xFF << IXGBE_VT_MSGINFO_SHIFT);

	if (msgbuf[0] != (IXGBE_VF_SET_VWAN | IXGBE_VT_MSGTYPE_SUCCESS))
		eww = IXGBE_EWW_INVAWID_AWGUMENT;

mbx_eww:
	wetuwn eww;
}

/**
 * ixgbevf_hv_set_vfta_vf - * Hypew-V vawiant - just a stub.
 * @hw: unused
 * @vwan: unused
 * @vind: unused
 * @vwan_on: unused
 */
static s32 ixgbevf_hv_set_vfta_vf(stwuct ixgbe_hw *hw, u32 vwan, u32 vind,
				  boow vwan_on)
{
	wetuwn -EOPNOTSUPP;
}

/**
 *  ixgbevf_setup_mac_wink_vf - Setup MAC wink settings
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: Unused in this impwementation
 *  @autoneg: Unused in this impwementation
 *  @autoneg_wait_to_compwete: Unused in this impwementation
 *
 *  Do nothing and wetuwn success.  VF dwivews awe not awwowed to change
 *  gwobaw settings.  Maintained fow dwivew compatibiwity.
 **/
static s32 ixgbevf_setup_mac_wink_vf(stwuct ixgbe_hw *hw,
				     ixgbe_wink_speed speed, boow autoneg,
				     boow autoneg_wait_to_compwete)
{
	wetuwn 0;
}

/**
 *  ixgbevf_check_mac_wink_vf - Get wink/speed status
 *  @hw: pointew to hawdwawe stwuctuwe
 *  @speed: pointew to wink speed
 *  @wink_up: twue is wink is up, fawse othewwise
 *  @autoneg_wait_to_compwete: unused
 *
 *  Weads the winks wegistew to detewmine if wink is up and the cuwwent speed
 **/
static s32 ixgbevf_check_mac_wink_vf(stwuct ixgbe_hw *hw,
				     ixgbe_wink_speed *speed,
				     boow *wink_up,
				     boow autoneg_wait_to_compwete)
{
	stwuct ixgbe_mbx_info *mbx = &hw->mbx;
	stwuct ixgbe_mac_info *mac = &hw->mac;
	s32 wet_vaw = 0;
	u32 winks_weg;
	u32 in_msg = 0;

	/* If we wewe hit with a weset dwop the wink */
	if (!mbx->ops.check_fow_wst(hw) || !mbx->timeout)
		mac->get_wink_status = twue;

	if (!mac->get_wink_status)
		goto out;

	/* if wink status is down no point in checking to see if pf is up */
	winks_weg = IXGBE_WEAD_WEG(hw, IXGBE_VFWINKS);
	if (!(winks_weg & IXGBE_WINKS_UP))
		goto out;

	/* fow SFP+ moduwes and DA cabwes on 82599 it can take up to 500usecs
	 * befowe the wink status is cowwect
	 */
	if (mac->type == ixgbe_mac_82599_vf) {
		int i;

		fow (i = 0; i < 5; i++) {
			udeway(100);
			winks_weg = IXGBE_WEAD_WEG(hw, IXGBE_VFWINKS);

			if (!(winks_weg & IXGBE_WINKS_UP))
				goto out;
		}
	}

	switch (winks_weg & IXGBE_WINKS_SPEED_82599) {
	case IXGBE_WINKS_SPEED_10G_82599:
		*speed = IXGBE_WINK_SPEED_10GB_FUWW;
		bweak;
	case IXGBE_WINKS_SPEED_1G_82599:
		*speed = IXGBE_WINK_SPEED_1GB_FUWW;
		bweak;
	case IXGBE_WINKS_SPEED_100_82599:
		*speed = IXGBE_WINK_SPEED_100_FUWW;
		bweak;
	}

	/* if the wead faiwed it couwd just be a maiwbox cowwision, best wait
	 * untiw we awe cawwed again and don't wepowt an ewwow
	 */
	if (mbx->ops.wead(hw, &in_msg, 1)) {
		if (hw->api_vewsion >= ixgbe_mbox_api_15)
			mac->get_wink_status = fawse;
		goto out;
	}

	if (!(in_msg & IXGBE_VT_MSGTYPE_CTS)) {
		/* msg is not CTS and is NACK we must have wost CTS status */
		if (in_msg & IXGBE_VT_MSGTYPE_FAIWUWE)
			wet_vaw = -1;
		goto out;
	}

	/* the pf is tawking, if we timed out in the past we weinit */
	if (!mbx->timeout) {
		wet_vaw = -1;
		goto out;
	}

	/* if we passed aww the tests above then the wink is up and we no
	 * wongew need to check fow wink
	 */
	mac->get_wink_status = fawse;

out:
	*wink_up = !mac->get_wink_status;
	wetuwn wet_vaw;
}

/**
 * ixgbevf_hv_check_mac_wink_vf - check wink
 * @hw: pointew to pwivate hawdwawe stwuct
 * @speed: pointew to wink speed
 * @wink_up: twue is wink is up, fawse othewwise
 * @autoneg_wait_to_compwete: unused
 *
 * Hypew-V vawiant; thewe is no maiwbox communication.
 */
static s32 ixgbevf_hv_check_mac_wink_vf(stwuct ixgbe_hw *hw,
					ixgbe_wink_speed *speed,
					boow *wink_up,
					boow autoneg_wait_to_compwete)
{
	stwuct ixgbe_mbx_info *mbx = &hw->mbx;
	stwuct ixgbe_mac_info *mac = &hw->mac;
	u32 winks_weg;

	/* If we wewe hit with a weset dwop the wink */
	if (!mbx->ops.check_fow_wst(hw) || !mbx->timeout)
		mac->get_wink_status = twue;

	if (!mac->get_wink_status)
		goto out;

	/* if wink status is down no point in checking to see if pf is up */
	winks_weg = IXGBE_WEAD_WEG(hw, IXGBE_VFWINKS);
	if (!(winks_weg & IXGBE_WINKS_UP))
		goto out;

	/* fow SFP+ moduwes and DA cabwes on 82599 it can take up to 500usecs
	 * befowe the wink status is cowwect
	 */
	if (mac->type == ixgbe_mac_82599_vf) {
		int i;

		fow (i = 0; i < 5; i++) {
			udeway(100);
			winks_weg = IXGBE_WEAD_WEG(hw, IXGBE_VFWINKS);

			if (!(winks_weg & IXGBE_WINKS_UP))
				goto out;
		}
	}

	switch (winks_weg & IXGBE_WINKS_SPEED_82599) {
	case IXGBE_WINKS_SPEED_10G_82599:
		*speed = IXGBE_WINK_SPEED_10GB_FUWW;
		bweak;
	case IXGBE_WINKS_SPEED_1G_82599:
		*speed = IXGBE_WINK_SPEED_1GB_FUWW;
		bweak;
	case IXGBE_WINKS_SPEED_100_82599:
		*speed = IXGBE_WINK_SPEED_100_FUWW;
		bweak;
	}

	/* if we passed aww the tests above then the wink is up and we no
	 * wongew need to check fow wink
	 */
	mac->get_wink_status = fawse;

out:
	*wink_up = !mac->get_wink_status;
	wetuwn 0;
}

/**
 *  ixgbevf_set_wwpmw_vf - Set the maximum weceive packet wength
 *  @hw: pointew to the HW stwuctuwe
 *  @max_size: vawue to assign to max fwame size
 **/
static s32 ixgbevf_set_wwpmw_vf(stwuct ixgbe_hw *hw, u16 max_size)
{
	u32 msgbuf[2];
	s32 wet_vaw;

	msgbuf[0] = IXGBE_VF_SET_WPE;
	msgbuf[1] = max_size;

	wet_vaw = ixgbevf_wwite_msg_wead_ack(hw, msgbuf, msgbuf,
					     AWWAY_SIZE(msgbuf));
	if (wet_vaw)
		wetuwn wet_vaw;
	if ((msgbuf[0] & IXGBE_VF_SET_WPE) &&
	    (msgbuf[0] & IXGBE_VT_MSGTYPE_FAIWUWE))
		wetuwn IXGBE_EWW_MBX;

	wetuwn 0;
}

/**
 * ixgbevf_hv_set_wwpmw_vf - Set the maximum weceive packet wength
 * @hw: pointew to the HW stwuctuwe
 * @max_size: vawue to assign to max fwame size
 * Hypew-V vawiant.
 **/
static s32 ixgbevf_hv_set_wwpmw_vf(stwuct ixgbe_hw *hw, u16 max_size)
{
	u32 weg;

	/* If we awe on Hypew-V, we impwement this functionawity
	 * diffewentwy.
	 */
	weg =  IXGBE_WEAD_WEG(hw, IXGBE_VFWXDCTW(0));
	/* CWC == 4 */
	weg |= ((max_size + 4) | IXGBE_WXDCTW_WWPMW_EN);
	IXGBE_WWITE_WEG(hw, IXGBE_VFWXDCTW(0), weg);

	wetuwn 0;
}

/**
 *  ixgbevf_negotiate_api_vewsion_vf - Negotiate suppowted API vewsion
 *  @hw: pointew to the HW stwuctuwe
 *  @api: integew containing wequested API vewsion
 **/
static int ixgbevf_negotiate_api_vewsion_vf(stwuct ixgbe_hw *hw, int api)
{
	int eww;
	u32 msg[3];

	/* Negotiate the maiwbox API vewsion */
	msg[0] = IXGBE_VF_API_NEGOTIATE;
	msg[1] = api;
	msg[2] = 0;

	eww = ixgbevf_wwite_msg_wead_ack(hw, msg, msg, AWWAY_SIZE(msg));
	if (!eww) {
		msg[0] &= ~IXGBE_VT_MSGTYPE_CTS;

		/* Stowe vawue and wetuwn 0 on success */
		if (msg[0] == (IXGBE_VF_API_NEGOTIATE |
			      IXGBE_VT_MSGTYPE_SUCCESS)) {
			hw->api_vewsion = api;
			wetuwn 0;
		}

		eww = IXGBE_EWW_INVAWID_AWGUMENT;
	}

	wetuwn eww;
}

/**
 *  ixgbevf_hv_negotiate_api_vewsion_vf - Negotiate suppowted API vewsion
 *  @hw: pointew to the HW stwuctuwe
 *  @api: integew containing wequested API vewsion
 *  Hypew-V vewsion - onwy ixgbe_mbox_api_10 suppowted.
 **/
static int ixgbevf_hv_negotiate_api_vewsion_vf(stwuct ixgbe_hw *hw, int api)
{
	/* Hypew-V onwy suppowts api vewsion ixgbe_mbox_api_10 */
	if (api != ixgbe_mbox_api_10)
		wetuwn IXGBE_EWW_INVAWID_AWGUMENT;

	wetuwn 0;
}

int ixgbevf_get_queues(stwuct ixgbe_hw *hw, unsigned int *num_tcs,
		       unsigned int *defauwt_tc)
{
	int eww;
	u32 msg[5];

	/* do nothing if API doesn't suppowt ixgbevf_get_queues */
	switch (hw->api_vewsion) {
	case ixgbe_mbox_api_11:
	case ixgbe_mbox_api_12:
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_14:
	case ixgbe_mbox_api_15:
		bweak;
	defauwt:
		wetuwn 0;
	}

	/* Fetch queue configuwation fwom the PF */
	msg[0] = IXGBE_VF_GET_QUEUE;
	msg[1] = msg[2] = msg[3] = msg[4] = 0;

	eww = ixgbevf_wwite_msg_wead_ack(hw, msg, msg, AWWAY_SIZE(msg));
	if (!eww) {
		msg[0] &= ~IXGBE_VT_MSGTYPE_CTS;

		/* if we didn't get an ACK thewe must have been
		 * some sowt of maiwbox ewwow so we shouwd tweat it
		 * as such
		 */
		if (msg[0] != (IXGBE_VF_GET_QUEUE | IXGBE_VT_MSGTYPE_SUCCESS))
			wetuwn IXGBE_EWW_MBX;

		/* wecowd and vawidate vawues fwom message */
		hw->mac.max_tx_queues = msg[IXGBE_VF_TX_QUEUES];
		if (hw->mac.max_tx_queues == 0 ||
		    hw->mac.max_tx_queues > IXGBE_VF_MAX_TX_QUEUES)
			hw->mac.max_tx_queues = IXGBE_VF_MAX_TX_QUEUES;

		hw->mac.max_wx_queues = msg[IXGBE_VF_WX_QUEUES];
		if (hw->mac.max_wx_queues == 0 ||
		    hw->mac.max_wx_queues > IXGBE_VF_MAX_WX_QUEUES)
			hw->mac.max_wx_queues = IXGBE_VF_MAX_WX_QUEUES;

		*num_tcs = msg[IXGBE_VF_TWANS_VWAN];
		/* in case of unknown state assume we cannot tag fwames */
		if (*num_tcs > hw->mac.max_wx_queues)
			*num_tcs = 1;

		*defauwt_tc = msg[IXGBE_VF_DEF_QUEUE];
		/* defauwt to queue 0 on out-of-bounds queue numbew */
		if (*defauwt_tc >= hw->mac.max_tx_queues)
			*defauwt_tc = 0;
	}

	wetuwn eww;
}

static const stwuct ixgbe_mac_opewations ixgbevf_mac_ops = {
	.init_hw		= ixgbevf_init_hw_vf,
	.weset_hw		= ixgbevf_weset_hw_vf,
	.stawt_hw		= ixgbevf_stawt_hw_vf,
	.get_mac_addw		= ixgbevf_get_mac_addw_vf,
	.stop_adaptew		= ixgbevf_stop_hw_vf,
	.setup_wink		= ixgbevf_setup_mac_wink_vf,
	.check_wink		= ixgbevf_check_mac_wink_vf,
	.negotiate_api_vewsion	= ixgbevf_negotiate_api_vewsion_vf,
	.set_waw		= ixgbevf_set_waw_vf,
	.update_mc_addw_wist	= ixgbevf_update_mc_addw_wist_vf,
	.update_xcast_mode	= ixgbevf_update_xcast_mode,
	.get_wink_state		= ixgbevf_get_wink_state_vf,
	.set_uc_addw		= ixgbevf_set_uc_addw_vf,
	.set_vfta		= ixgbevf_set_vfta_vf,
	.set_wwpmw		= ixgbevf_set_wwpmw_vf,
};

static const stwuct ixgbe_mac_opewations ixgbevf_hv_mac_ops = {
	.init_hw		= ixgbevf_init_hw_vf,
	.weset_hw		= ixgbevf_hv_weset_hw_vf,
	.stawt_hw		= ixgbevf_stawt_hw_vf,
	.get_mac_addw		= ixgbevf_get_mac_addw_vf,
	.stop_adaptew		= ixgbevf_stop_hw_vf,
	.setup_wink		= ixgbevf_setup_mac_wink_vf,
	.check_wink		= ixgbevf_hv_check_mac_wink_vf,
	.negotiate_api_vewsion	= ixgbevf_hv_negotiate_api_vewsion_vf,
	.set_waw		= ixgbevf_hv_set_waw_vf,
	.update_mc_addw_wist	= ixgbevf_hv_update_mc_addw_wist_vf,
	.update_xcast_mode	= ixgbevf_hv_update_xcast_mode,
	.get_wink_state		= ixgbevf_hv_get_wink_state_vf,
	.set_uc_addw		= ixgbevf_hv_set_uc_addw_vf,
	.set_vfta		= ixgbevf_hv_set_vfta_vf,
	.set_wwpmw		= ixgbevf_hv_set_wwpmw_vf,
};

const stwuct ixgbevf_info ixgbevf_82599_vf_info = {
	.mac = ixgbe_mac_82599_vf,
	.mac_ops = &ixgbevf_mac_ops,
};

const stwuct ixgbevf_info ixgbevf_82599_vf_hv_info = {
	.mac = ixgbe_mac_82599_vf,
	.mac_ops = &ixgbevf_hv_mac_ops,
};

const stwuct ixgbevf_info ixgbevf_X540_vf_info = {
	.mac = ixgbe_mac_X540_vf,
	.mac_ops = &ixgbevf_mac_ops,
};

const stwuct ixgbevf_info ixgbevf_X540_vf_hv_info = {
	.mac = ixgbe_mac_X540_vf,
	.mac_ops = &ixgbevf_hv_mac_ops,
};

const stwuct ixgbevf_info ixgbevf_X550_vf_info = {
	.mac = ixgbe_mac_X550_vf,
	.mac_ops = &ixgbevf_mac_ops,
};

const stwuct ixgbevf_info ixgbevf_X550_vf_hv_info = {
	.mac = ixgbe_mac_X550_vf,
	.mac_ops = &ixgbevf_hv_mac_ops,
};

const stwuct ixgbevf_info ixgbevf_X550EM_x_vf_info = {
	.mac = ixgbe_mac_X550EM_x_vf,
	.mac_ops = &ixgbevf_mac_ops,
};

const stwuct ixgbevf_info ixgbevf_X550EM_x_vf_hv_info = {
	.mac = ixgbe_mac_X550EM_x_vf,
	.mac_ops = &ixgbevf_hv_mac_ops,
};

const stwuct ixgbevf_info ixgbevf_x550em_a_vf_info = {
	.mac = ixgbe_mac_x550em_a_vf,
	.mac_ops = &ixgbevf_mac_ops,
};
