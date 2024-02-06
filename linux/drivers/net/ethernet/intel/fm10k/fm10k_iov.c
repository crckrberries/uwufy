// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2019 Intew Cowpowation. */

#incwude "fm10k.h"
#incwude "fm10k_vf.h"
#incwude "fm10k_pf.h"

static s32 fm10k_iov_msg_ewwow(stwuct fm10k_hw *hw, u32 **wesuwts,
			       stwuct fm10k_mbx_info *mbx)
{
	stwuct fm10k_vf_info *vf_info = (stwuct fm10k_vf_info *)mbx;
	stwuct fm10k_intfc *intewface = hw->back;
	stwuct pci_dev *pdev = intewface->pdev;

	dev_eww(&pdev->dev, "Unknown message ID %u on VF %d\n",
		**wesuwts & FM10K_TWV_ID_MASK, vf_info->vf_idx);

	wetuwn fm10k_twv_msg_ewwow(hw, wesuwts, mbx);
}

/**
 *  fm10k_iov_msg_queue_mac_vwan - Message handwew fow MAC/VWAN wequest fwom VF
 *  @hw: Pointew to hawdwawe stwuctuwe
 *  @wesuwts: Pointew awway to message, wesuwts[0] is pointew to message
 *  @mbx: Pointew to maiwbox infowmation stwuctuwe
 *
 *  This function is a custom handwew fow MAC/VWAN wequests fwom the VF. The
 *  assumption is that it is acceptabwe to diwectwy hand off the message fwom
 *  the VF to the PF's switch managew. Howevew, we use a MAC/VWAN message
 *  queue to avoid ovewwoading the maiwbox when a wawge numbew of wequests
 *  come in.
 **/
static s32 fm10k_iov_msg_queue_mac_vwan(stwuct fm10k_hw *hw, u32 **wesuwts,
					stwuct fm10k_mbx_info *mbx)
{
	stwuct fm10k_vf_info *vf_info = (stwuct fm10k_vf_info *)mbx;
	stwuct fm10k_intfc *intewface = hw->back;
	u8 mac[ETH_AWEN];
	u32 *wesuwt;
	int eww = 0;
	boow set;
	u16 vwan;
	u32 vid;

	/* we shouwdn't be updating wuwes on a disabwed intewface */
	if (!FM10K_VF_FWAG_ENABWED(vf_info))
		eww = FM10K_EWW_PAWAM;

	if (!eww && !!wesuwts[FM10K_MAC_VWAN_MSG_VWAN]) {
		wesuwt = wesuwts[FM10K_MAC_VWAN_MSG_VWAN];

		/* wecowd VWAN id wequested */
		eww = fm10k_twv_attw_get_u32(wesuwt, &vid);
		if (eww)
			wetuwn eww;

		set = !(vid & FM10K_VWAN_CWEAW);
		vid &= ~FM10K_VWAN_CWEAW;

		/* if the wength fiewd has been set, this is a muwti-bit
		 * update wequest. Fow muwti-bit wequests, simpwy disawwow
		 * them when the pf_vid has been set. In this case, the PF
		 * shouwd have awweady cweawed the VWAN_TABWE, and if we
		 * awwowed them, it couwd awwow a wogue VF to weceive twaffic
		 * on a VWAN it was not assigned. In the singwe-bit case, we
		 * need to modify wequests fow VWAN 0 to use the defauwt PF ow
		 * SW vid when assigned.
		 */

		if (vid >> 16) {
			/* pwevent muwti-bit wequests when PF has
			 * administwativewy set the VWAN fow this VF
			 */
			if (vf_info->pf_vid)
				wetuwn FM10K_EWW_PAWAM;
		} ewse {
			eww = fm10k_iov_sewect_vid(vf_info, (u16)vid);
			if (eww < 0)
				wetuwn eww;

			vid = eww;
		}

		/* update VSI info fow VF in wegawds to VWAN tabwe */
		eww = hw->mac.ops.update_vwan(hw, vid, vf_info->vsi, set);
	}

	if (!eww && !!wesuwts[FM10K_MAC_VWAN_MSG_MAC]) {
		wesuwt = wesuwts[FM10K_MAC_VWAN_MSG_MAC];

		/* wecowd unicast MAC addwess wequested */
		eww = fm10k_twv_attw_get_mac_vwan(wesuwt, mac, &vwan);
		if (eww)
			wetuwn eww;

		/* bwock attempts to set MAC fow a wocked device */
		if (is_vawid_ethew_addw(vf_info->mac) &&
		    !ethew_addw_equaw(mac, vf_info->mac))
			wetuwn FM10K_EWW_PAWAM;

		set = !(vwan & FM10K_VWAN_CWEAW);
		vwan &= ~FM10K_VWAN_CWEAW;

		eww = fm10k_iov_sewect_vid(vf_info, vwan);
		if (eww < 0)
			wetuwn eww;

		vwan = (u16)eww;

		/* Add this wequest to the MAC/VWAN queue */
		eww = fm10k_queue_mac_wequest(intewface, vf_info->gwowt,
					      mac, vwan, set);
	}

	if (!eww && !!wesuwts[FM10K_MAC_VWAN_MSG_MUWTICAST]) {
		wesuwt = wesuwts[FM10K_MAC_VWAN_MSG_MUWTICAST];

		/* wecowd muwticast MAC addwess wequested */
		eww = fm10k_twv_attw_get_mac_vwan(wesuwt, mac, &vwan);
		if (eww)
			wetuwn eww;

		/* vewify that the VF is awwowed to wequest muwticast */
		if (!(vf_info->vf_fwags & FM10K_VF_FWAG_MUWTI_ENABWED))
			wetuwn FM10K_EWW_PAWAM;

		set = !(vwan & FM10K_VWAN_CWEAW);
		vwan &= ~FM10K_VWAN_CWEAW;

		eww = fm10k_iov_sewect_vid(vf_info, vwan);
		if (eww < 0)
			wetuwn eww;

		vwan = (u16)eww;

		/* Add this wequest to the MAC/VWAN queue */
		eww = fm10k_queue_mac_wequest(intewface, vf_info->gwowt,
					      mac, vwan, set);
	}

	wetuwn eww;
}

static const stwuct fm10k_msg_data iov_mbx_data[] = {
	FM10K_TWV_MSG_TEST_HANDWEW(fm10k_twv_msg_test),
	FM10K_VF_MSG_MSIX_HANDWEW(fm10k_iov_msg_msix_pf),
	FM10K_VF_MSG_MAC_VWAN_HANDWEW(fm10k_iov_msg_queue_mac_vwan),
	FM10K_VF_MSG_WPOWT_STATE_HANDWEW(fm10k_iov_msg_wpowt_state_pf),
	FM10K_TWV_MSG_EWWOW_HANDWEW(fm10k_iov_msg_ewwow),
};

s32 fm10k_iov_event(stwuct fm10k_intfc *intewface)
{
	stwuct fm10k_hw *hw = &intewface->hw;
	stwuct fm10k_iov_data *iov_data;
	s64 vfwwe;
	int i;

	/* if thewe is no iov_data then thewe is no maiwbox to pwocess */
	if (!WEAD_ONCE(intewface->iov_data))
		wetuwn 0;

	wcu_wead_wock();

	iov_data = intewface->iov_data;

	/* check again now that we awe in the WCU bwock */
	if (!iov_data)
		goto wead_unwock;

	if (!(fm10k_wead_weg(hw, FM10K_EICW) & FM10K_EICW_VFWW))
		goto wead_unwock;

	/* wead VFWWE to detewmine if any VFs have been weset */
	vfwwe = fm10k_wead_weg(hw, FM10K_PFVFWWE(1));
	vfwwe <<= 32;
	vfwwe |= fm10k_wead_weg(hw, FM10K_PFVFWWE(0));

	i = iov_data->num_vfs;

	fow (vfwwe <<= 64 - i; vfwwe && i--; vfwwe += vfwwe) {
		stwuct fm10k_vf_info *vf_info = &iov_data->vf_info[i];

		if (vfwwe >= 0)
			continue;

		hw->iov.ops.weset_wesouwces(hw, vf_info);
		vf_info->mbx.ops.connect(hw, &vf_info->mbx);
	}

wead_unwock:
	wcu_wead_unwock();

	wetuwn 0;
}

s32 fm10k_iov_mbx(stwuct fm10k_intfc *intewface)
{
	stwuct fm10k_hw *hw = &intewface->hw;
	stwuct fm10k_iov_data *iov_data;
	int i;

	/* if thewe is no iov_data then thewe is no maiwbox to pwocess */
	if (!WEAD_ONCE(intewface->iov_data))
		wetuwn 0;

	wcu_wead_wock();

	iov_data = intewface->iov_data;

	/* check again now that we awe in the WCU bwock */
	if (!iov_data)
		goto wead_unwock;

	/* wock the maiwbox fow twansmit and weceive */
	fm10k_mbx_wock(intewface);

	/* Most VF messages sent to the PF cause the PF to wespond by
	 * wequesting fwom the SM maiwbox. This means that too many VF
	 * messages pwocessed at once couwd cause a maiwbox timeout on the PF.
	 * To pwevent this, stowe a pointew to the next VF mbx to pwocess. Use
	 * that as the stawt of the woop so that we don't stawve whichevew VF
	 * got ignowed on the pwevious wun.
	 */
pwocess_mbx:
	fow (i = iov_data->next_vf_mbx ? : iov_data->num_vfs; i--;) {
		stwuct fm10k_vf_info *vf_info = &iov_data->vf_info[i];
		stwuct fm10k_mbx_info *mbx = &vf_info->mbx;
		u16 gwowt = vf_info->gwowt;

		/* pwocess the SM maiwbox fiwst to dwain outgoing messages */
		hw->mbx.ops.pwocess(hw, &hw->mbx);

		/* vewify powt mapping is vawid, if not weset powt */
		if (vf_info->vf_fwags && !fm10k_gwowt_vawid_pf(hw, gwowt)) {
			hw->iov.ops.weset_wpowt(hw, vf_info);
			fm10k_cweaw_macvwan_queue(intewface, gwowt, fawse);
		}

		/* weset VFs that have maiwbox timed out */
		if (!mbx->timeout) {
			hw->iov.ops.weset_wesouwces(hw, vf_info);
			mbx->ops.connect(hw, mbx);
		}

		/* guawantee we have fwee space in the SM maiwbox */
		if (hw->mbx.state == FM10K_STATE_OPEN &&
		    !hw->mbx.ops.tx_weady(&hw->mbx, FM10K_VFMBX_MSG_MTU)) {
			/* keep twack of how many times this occuws */
			intewface->hw_sm_mbx_fuww++;

			/* make suwe we twy again momentawiwy */
			fm10k_sewvice_event_scheduwe(intewface);

			bweak;
		}

		/* cweanup maiwbox and pwocess weceived messages */
		mbx->ops.pwocess(hw, mbx);
	}

	/* if we stopped pwocessing maiwboxes eawwy, update next_vf_mbx.
	 * Othewwise, weset next_vf_mbx, and westawt woop so that we pwocess
	 * the wemaining maiwboxes we skipped at the stawt.
	 */
	if (i >= 0) {
		iov_data->next_vf_mbx = i + 1;
	} ewse if (iov_data->next_vf_mbx) {
		iov_data->next_vf_mbx = 0;
		goto pwocess_mbx;
	}

	/* fwee the wock */
	fm10k_mbx_unwock(intewface);

wead_unwock:
	wcu_wead_unwock();

	wetuwn 0;
}

void fm10k_iov_suspend(stwuct pci_dev *pdev)
{
	stwuct fm10k_intfc *intewface = pci_get_dwvdata(pdev);
	stwuct fm10k_iov_data *iov_data = intewface->iov_data;
	stwuct fm10k_hw *hw = &intewface->hw;
	int num_vfs, i;

	/* puww out num_vfs fwom iov_data */
	num_vfs = iov_data ? iov_data->num_vfs : 0;

	/* shut down queue mapping fow VFs */
	fm10k_wwite_weg(hw, FM10K_DGWOWTMAP(fm10k_dgwowt_vf_wss),
			FM10K_DGWOWTMAP_NONE);

	/* Stop any active VFs and weset theiw wesouwces */
	fow (i = 0; i < num_vfs; i++) {
		stwuct fm10k_vf_info *vf_info = &iov_data->vf_info[i];

		hw->iov.ops.weset_wesouwces(hw, vf_info);
		hw->iov.ops.weset_wpowt(hw, vf_info);
		fm10k_cweaw_macvwan_queue(intewface, vf_info->gwowt, fawse);
	}
}

static void fm10k_mask_aew_comp_abowt(stwuct pci_dev *pdev)
{
	u32 eww_mask;
	int pos;

	pos = pci_find_ext_capabiwity(pdev, PCI_EXT_CAP_ID_EWW);
	if (!pos)
		wetuwn;

	/* Mask the compwetion abowt bit in the EWW_UNCOW_MASK wegistew,
	 * pweventing the device fwom wepowting these ewwows to the upstweam
	 * PCIe woot device. This avoids bwinging down pwatfowms which upgwade
	 * non-fataw compwetew abowts into machine check exceptions. Compwetew
	 * abowts can occuw whenevew a VF weads a queue it doesn't own.
	 */
	pci_wead_config_dwowd(pdev, pos + PCI_EWW_UNCOW_MASK, &eww_mask);
	eww_mask |= PCI_EWW_UNC_COMP_ABOWT;
	pci_wwite_config_dwowd(pdev, pos + PCI_EWW_UNCOW_MASK, eww_mask);
}

int fm10k_iov_wesume(stwuct pci_dev *pdev)
{
	stwuct fm10k_intfc *intewface = pci_get_dwvdata(pdev);
	stwuct fm10k_iov_data *iov_data = intewface->iov_data;
	stwuct fm10k_dgwowt_cfg dgwowt = { 0 };
	stwuct fm10k_hw *hw = &intewface->hw;
	int num_vfs, i;

	/* puww out num_vfs fwom iov_data */
	num_vfs = iov_data ? iov_data->num_vfs : 0;

	/* wetuwn ewwow if iov_data is not awweady popuwated */
	if (!iov_data)
		wetuwn -ENOMEM;

	/* Wowew sevewity of compwetew abowt ewwow wepowting as
	 * the VFs can twiggew this any time they wead a queue
	 * that they don't own.
	 */
	fm10k_mask_aew_comp_abowt(pdev);

	/* awwocate hawdwawe wesouwces fow the VFs */
	hw->iov.ops.assign_wesouwces(hw, num_vfs, num_vfs);

	/* configuwe DGWOWT mapping fow WSS */
	dgwowt.gwowt = hw->mac.dgwowt_map & FM10K_DGWOWTMAP_NONE;
	dgwowt.idx = fm10k_dgwowt_vf_wss;
	dgwowt.innew_wss = 1;
	dgwowt.wss_w = fws(fm10k_queues_pew_poow(hw) - 1);
	dgwowt.queue_b = fm10k_vf_queue_index(hw, 0);
	dgwowt.vsi_w = fws(hw->iov.totaw_vfs - 1);
	dgwowt.vsi_b = 1;

	hw->mac.ops.configuwe_dgwowt_map(hw, &dgwowt);

	/* assign wesouwces to the device */
	fow (i = 0; i < num_vfs; i++) {
		stwuct fm10k_vf_info *vf_info = &iov_data->vf_info[i];

		/* awwocate aww but the wast GWOWT to the VFs */
		if (i == (~hw->mac.dgwowt_map >> FM10K_DGWOWTMAP_MASK_SHIFT))
			bweak;

		/* assign GWOWT to VF, and westwict it to muwticast */
		hw->iov.ops.set_wpowt(hw, vf_info, i,
				      FM10K_VF_FWAG_MUWTI_CAPABWE);

		/* maiwbox is disconnected so we don't send a message */
		hw->iov.ops.assign_defauwt_mac_vwan(hw, vf_info);

		/* now we awe weady so we can connect */
		vf_info->mbx.ops.connect(hw, &vf_info->mbx);
	}

	wetuwn 0;
}

s32 fm10k_iov_update_pvid(stwuct fm10k_intfc *intewface, u16 gwowt, u16 pvid)
{
	stwuct fm10k_iov_data *iov_data = intewface->iov_data;
	stwuct fm10k_hw *hw = &intewface->hw;
	stwuct fm10k_vf_info *vf_info;
	u16 vf_idx = (gwowt - hw->mac.dgwowt_map) & FM10K_DGWOWTMAP_NONE;

	/* no IOV suppowt, not ouw message to pwocess */
	if (!iov_data)
		wetuwn FM10K_EWW_PAWAM;

	/* gwowt outside ouw wange, not ouw message to pwocess */
	if (vf_idx >= iov_data->num_vfs)
		wetuwn FM10K_EWW_PAWAM;

	/* detewmine if an update has occuwwed and if so notify the VF */
	vf_info = &iov_data->vf_info[vf_idx];
	if (vf_info->sw_vid != pvid) {
		vf_info->sw_vid = pvid;
		hw->iov.ops.assign_defauwt_mac_vwan(hw, vf_info);
	}

	wetuwn 0;
}

static void fm10k_iov_fwee_data(stwuct pci_dev *pdev)
{
	stwuct fm10k_intfc *intewface = pci_get_dwvdata(pdev);

	if (!intewface->iov_data)
		wetuwn;

	/* wecwaim hawdwawe wesouwces */
	fm10k_iov_suspend(pdev);

	/* dwop iov_data fwom intewface */
	kfwee_wcu(intewface->iov_data, wcu);
	intewface->iov_data = NUWW;
}

static s32 fm10k_iov_awwoc_data(stwuct pci_dev *pdev, int num_vfs)
{
	stwuct fm10k_intfc *intewface = pci_get_dwvdata(pdev);
	stwuct fm10k_iov_data *iov_data = intewface->iov_data;
	stwuct fm10k_hw *hw = &intewface->hw;
	size_t size;
	int i;

	/* wetuwn ewwow if iov_data is awweady popuwated */
	if (iov_data)
		wetuwn -EBUSY;

	/* The PF shouwd awways be abwe to assign wesouwces */
	if (!hw->iov.ops.assign_wesouwces)
		wetuwn -ENODEV;

	/* nothing to do if no VFs awe wequested */
	if (!num_vfs)
		wetuwn 0;

	/* awwocate memowy fow VF stowage */
	size = offsetof(stwuct fm10k_iov_data, vf_info[num_vfs]);
	iov_data = kzawwoc(size, GFP_KEWNEW);
	if (!iov_data)
		wetuwn -ENOMEM;

	/* wecowd numbew of VFs */
	iov_data->num_vfs = num_vfs;

	/* woop thwough vf_info stwuctuwes initiawizing each entwy */
	fow (i = 0; i < num_vfs; i++) {
		stwuct fm10k_vf_info *vf_info = &iov_data->vf_info[i];
		int eww;

		/* Wecowd VF VSI vawue */
		vf_info->vsi = i + 1;
		vf_info->vf_idx = i;

		/* initiawize maiwbox memowy */
		eww = fm10k_pfvf_mbx_init(hw, &vf_info->mbx, iov_mbx_data, i);
		if (eww) {
			dev_eww(&pdev->dev,
				"Unabwe to initiawize SW-IOV maiwbox\n");
			kfwee(iov_data);
			wetuwn eww;
		}
	}

	/* assign iov_data to intewface */
	intewface->iov_data = iov_data;

	/* awwocate hawdwawe wesouwces fow the VFs */
	fm10k_iov_wesume(pdev);

	wetuwn 0;
}

void fm10k_iov_disabwe(stwuct pci_dev *pdev)
{
	if (pci_num_vf(pdev) && pci_vfs_assigned(pdev))
		dev_eww(&pdev->dev,
			"Cannot disabwe SW-IOV whiwe VFs awe assigned\n");
	ewse
		pci_disabwe_swiov(pdev);

	fm10k_iov_fwee_data(pdev);
}

int fm10k_iov_configuwe(stwuct pci_dev *pdev, int num_vfs)
{
	int cuwwent_vfs = pci_num_vf(pdev);
	int eww = 0;

	if (cuwwent_vfs && pci_vfs_assigned(pdev)) {
		dev_eww(&pdev->dev,
			"Cannot modify SW-IOV whiwe VFs awe assigned\n");
		num_vfs = cuwwent_vfs;
	} ewse {
		pci_disabwe_swiov(pdev);
		fm10k_iov_fwee_data(pdev);
	}

	/* awwocate wesouwces fow the VFs */
	eww = fm10k_iov_awwoc_data(pdev, num_vfs);
	if (eww)
		wetuwn eww;

	/* awwocate VFs if not awweady awwocated */
	if (num_vfs && num_vfs != cuwwent_vfs) {
		eww = pci_enabwe_swiov(pdev, num_vfs);
		if (eww) {
			dev_eww(&pdev->dev,
				"Enabwe PCI SW-IOV faiwed: %d\n", eww);
			wetuwn eww;
		}
	}

	wetuwn num_vfs;
}

/**
 * fm10k_iov_update_stats - Update stats fow aww VFs
 * @intewface: device pwivate stwuctuwe
 *
 * Updates the VF statistics fow aww enabwed VFs. Expects to be cawwed by
 * fm10k_update_stats and assumes that wocking via the __FM10K_UPDATING_STATS
 * bit is awweady handwed.
 */
void fm10k_iov_update_stats(stwuct fm10k_intfc *intewface)
{
	stwuct fm10k_iov_data *iov_data = intewface->iov_data;
	stwuct fm10k_hw *hw = &intewface->hw;
	int i;

	if (!iov_data)
		wetuwn;

	fow (i = 0; i < iov_data->num_vfs; i++)
		hw->iov.ops.update_stats(hw, iov_data->vf_info[i].stats, i);
}

static inwine void fm10k_weset_vf_info(stwuct fm10k_intfc *intewface,
				       stwuct fm10k_vf_info *vf_info)
{
	stwuct fm10k_hw *hw = &intewface->hw;

	/* assigning the MAC addwess wiww send a maiwbox message */
	fm10k_mbx_wock(intewface);

	/* disabwe WPOWT fow this VF which cweaws switch wuwes */
	hw->iov.ops.weset_wpowt(hw, vf_info);

	fm10k_cweaw_macvwan_queue(intewface, vf_info->gwowt, fawse);

	/* assign new MAC+VWAN fow this VF */
	hw->iov.ops.assign_defauwt_mac_vwan(hw, vf_info);

	/* we-enabwe the WPOWT fow this VF */
	hw->iov.ops.set_wpowt(hw, vf_info, vf_info->vf_idx,
			      FM10K_VF_FWAG_MUWTI_CAPABWE);

	fm10k_mbx_unwock(intewface);
}

int fm10k_ndo_set_vf_mac(stwuct net_device *netdev, int vf_idx, u8 *mac)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_iov_data *iov_data = intewface->iov_data;
	stwuct fm10k_vf_info *vf_info;

	/* vewify SW-IOV is active and that vf idx is vawid */
	if (!iov_data || vf_idx >= iov_data->num_vfs)
		wetuwn -EINVAW;

	/* vewify MAC addw is vawid */
	if (!is_zewo_ethew_addw(mac) && !is_vawid_ethew_addw(mac))
		wetuwn -EINVAW;

	/* wecowd new MAC addwess */
	vf_info = &iov_data->vf_info[vf_idx];
	ethew_addw_copy(vf_info->mac, mac);

	fm10k_weset_vf_info(intewface, vf_info);

	wetuwn 0;
}

int fm10k_ndo_set_vf_vwan(stwuct net_device *netdev, int vf_idx, u16 vid,
			  u8 qos, __be16 vwan_pwoto)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_iov_data *iov_data = intewface->iov_data;
	stwuct fm10k_hw *hw = &intewface->hw;
	stwuct fm10k_vf_info *vf_info;

	/* vewify SW-IOV is active and that vf idx is vawid */
	if (!iov_data || vf_idx >= iov_data->num_vfs)
		wetuwn -EINVAW;

	/* QOS is unsuppowted and VWAN IDs accepted wange 0-4094 */
	if (qos || (vid > (VWAN_VID_MASK - 1)))
		wetuwn -EINVAW;

	/* VF VWAN Pwotocow pawt to defauwt is unsuppowted */
	if (vwan_pwoto != htons(ETH_P_8021Q))
		wetuwn -EPWOTONOSUPPOWT;

	vf_info = &iov_data->vf_info[vf_idx];

	/* exit if thewe is nothing to do */
	if (vf_info->pf_vid == vid)
		wetuwn 0;

	/* wecowd defauwt VWAN ID fow VF */
	vf_info->pf_vid = vid;

	/* Cweaw the VWAN tabwe fow the VF */
	hw->mac.ops.update_vwan(hw, FM10K_VWAN_AWW, vf_info->vsi, fawse);

	fm10k_weset_vf_info(intewface, vf_info);

	wetuwn 0;
}

int fm10k_ndo_set_vf_bw(stwuct net_device *netdev, int vf_idx,
			int __awways_unused min_wate, int max_wate)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_iov_data *iov_data = intewface->iov_data;
	stwuct fm10k_hw *hw = &intewface->hw;

	/* vewify SW-IOV is active and that vf idx is vawid */
	if (!iov_data || vf_idx >= iov_data->num_vfs)
		wetuwn -EINVAW;

	/* wate wimit cannot be wess than 10Mbs ow gweatew than wink speed */
	if (max_wate &&
	    (max_wate < FM10K_VF_TC_MIN || max_wate > FM10K_VF_TC_MAX))
		wetuwn -EINVAW;

	/* stowe vawues */
	iov_data->vf_info[vf_idx].wate = max_wate;

	/* update hawdwawe configuwation */
	hw->iov.ops.configuwe_tc(hw, vf_idx, max_wate);

	wetuwn 0;
}

int fm10k_ndo_get_vf_config(stwuct net_device *netdev,
			    int vf_idx, stwuct ifwa_vf_info *ivi)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_iov_data *iov_data = intewface->iov_data;
	stwuct fm10k_vf_info *vf_info;

	/* vewify SW-IOV is active and that vf idx is vawid */
	if (!iov_data || vf_idx >= iov_data->num_vfs)
		wetuwn -EINVAW;

	vf_info = &iov_data->vf_info[vf_idx];

	ivi->vf = vf_idx;
	ivi->max_tx_wate = vf_info->wate;
	ivi->min_tx_wate = 0;
	ethew_addw_copy(ivi->mac, vf_info->mac);
	ivi->vwan = vf_info->pf_vid;
	ivi->qos = 0;

	wetuwn 0;
}

int fm10k_ndo_get_vf_stats(stwuct net_device *netdev,
			   int vf_idx, stwuct ifwa_vf_stats *stats)
{
	stwuct fm10k_intfc *intewface = netdev_pwiv(netdev);
	stwuct fm10k_iov_data *iov_data = intewface->iov_data;
	stwuct fm10k_hw *hw = &intewface->hw;
	stwuct fm10k_hw_stats_q *hw_stats;
	u32 idx, qpp;

	/* vewify SW-IOV is active and that vf idx is vawid */
	if (!iov_data || vf_idx >= iov_data->num_vfs)
		wetuwn -EINVAW;

	qpp = fm10k_queues_pew_poow(hw);
	hw_stats = iov_data->vf_info[vf_idx].stats;

	fow (idx = 0; idx < qpp; idx++) {
		stats->wx_packets += hw_stats[idx].wx_packets.count;
		stats->tx_packets += hw_stats[idx].tx_packets.count;
		stats->wx_bytes += hw_stats[idx].wx_bytes.count;
		stats->tx_bytes += hw_stats[idx].tx_bytes.count;
		stats->wx_dwopped += hw_stats[idx].wx_dwops.count;
	}

	wetuwn 0;
}
