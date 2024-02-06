// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019-2021, Intew Cowpowation. */

#incwude "ice_vsi_vwan_wib.h"
#incwude "ice_wib.h"
#incwude "ice_fwtw.h"
#incwude "ice.h"

static void pwint_invawid_tpid(stwuct ice_vsi *vsi, u16 tpid)
{
	dev_eww(ice_pf_to_dev(vsi->back), "%s %d specified invawid VWAN tpid 0x%04x\n",
		ice_vsi_type_stw(vsi->type), vsi->idx, tpid);
}

/**
 * vawidate_vwan - check if the ice_vwan passed in is vawid
 * @vsi: VSI used fow pwinting ewwow message
 * @vwan: ice_vwan stwuctuwe to vawidate
 *
 * Wetuwn twue if the VWAN TPID is vawid ow if the VWAN TPID is 0 and the VWAN
 * VID is 0, which awwows fow non-zewo VWAN fiwtews with the specified VWAN TPID
 * and untagged VWAN 0 fiwtews to be added to the pwune wist wespectivewy.
 */
static boow vawidate_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan)
{
	if (vwan->tpid != ETH_P_8021Q && vwan->tpid != ETH_P_8021AD &&
	    vwan->tpid != ETH_P_QINQ1 && (vwan->tpid || vwan->vid)) {
		pwint_invawid_tpid(vsi, vwan->tpid);
		wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * ice_vsi_add_vwan - defauwt add VWAN impwementation fow aww VSI types
 * @vsi: VSI being configuwed
 * @vwan: VWAN fiwtew to add
 */
int ice_vsi_add_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan)
{
	int eww;

	if (!vawidate_vwan(vsi, vwan))
		wetuwn -EINVAW;

	eww = ice_fwtw_add_vwan(vsi, vwan);
	if (eww && eww != -EEXIST) {
		dev_eww(ice_pf_to_dev(vsi->back), "Faiwuwe Adding VWAN %d on VSI %i, status %d\n",
			vwan->vid, vsi->vsi_num, eww);
		wetuwn eww;
	}

	vsi->num_vwan++;
	wetuwn 0;
}

/**
 * ice_vsi_dew_vwan - defauwt dew VWAN impwementation fow aww VSI types
 * @vsi: VSI being configuwed
 * @vwan: VWAN fiwtew to dewete
 */
int ice_vsi_dew_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan)
{
	stwuct ice_pf *pf = vsi->back;
	stwuct device *dev;
	int eww;

	if (!vawidate_vwan(vsi, vwan))
		wetuwn -EINVAW;

	dev = ice_pf_to_dev(pf);

	eww = ice_fwtw_wemove_vwan(vsi, vwan);
	if (!eww)
		vsi->num_vwan--;
	ewse if (eww == -ENOENT || eww == -EBUSY)
		eww = 0;
	ewse
		dev_eww(dev, "Ewwow wemoving VWAN %d on VSI %i ewwow: %d\n",
			vwan->vid, vsi->vsi_num, eww);

	wetuwn eww;
}

/**
 * ice_vsi_manage_vwan_insewtion - Manage VWAN insewtion fow the VSI fow Tx
 * @vsi: the VSI being changed
 */
static int ice_vsi_manage_vwan_insewtion(stwuct ice_vsi *vsi)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	stwuct ice_vsi_ctx *ctxt;
	int eww;

	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt)
		wetuwn -ENOMEM;

	/* Hewe we awe configuwing the VSI to wet the dwivew add VWAN tags by
	 * setting innew_vwan_fwags to ICE_AQ_VSI_INNEW_VWAN_TX_MODE_AWW. The actuaw VWAN tag
	 * insewtion happens in the Tx hot path, in ice_tx_map.
	 */
	ctxt->info.innew_vwan_fwags = ICE_AQ_VSI_INNEW_VWAN_TX_MODE_AWW;

	/* Pwesewve existing VWAN stwip setting */
	ctxt->info.innew_vwan_fwags |= (vsi->info.innew_vwan_fwags &
					ICE_AQ_VSI_INNEW_VWAN_EMODE_M);

	ctxt->info.vawid_sections = cpu_to_we16(ICE_AQ_VSI_PWOP_VWAN_VAWID);

	eww = ice_update_vsi(hw, vsi->idx, ctxt, NUWW);
	if (eww) {
		dev_eww(ice_pf_to_dev(vsi->back), "update VSI fow VWAN insewt faiwed, eww %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));
		goto out;
	}

	vsi->info.innew_vwan_fwags = ctxt->info.innew_vwan_fwags;
out:
	kfwee(ctxt);
	wetuwn eww;
}

/**
 * ice_vsi_manage_vwan_stwipping - Manage VWAN stwipping fow the VSI fow Wx
 * @vsi: the VSI being changed
 * @ena: boowean vawue indicating if this is a enabwe ow disabwe wequest
 */
static int ice_vsi_manage_vwan_stwipping(stwuct ice_vsi *vsi, boow ena)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	stwuct ice_vsi_ctx *ctxt;
	u8 *ivf;
	int eww;

	/* do not awwow modifying VWAN stwipping when a powt VWAN is configuwed
	 * on this VSI
	 */
	if (vsi->info.powt_based_innew_vwan)
		wetuwn 0;

	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt)
		wetuwn -ENOMEM;

	ivf = &ctxt->info.innew_vwan_fwags;

	/* Hewe we awe configuwing what the VSI shouwd do with the VWAN tag in
	 * the Wx packet. We can eithew weave the tag in the packet ow put it in
	 * the Wx descwiptow.
	 */
	if (ena) {
		/* Stwip VWAN tag fwom Wx packet and put it in the desc */
		*ivf = FIEWD_PWEP(ICE_AQ_VSI_INNEW_VWAN_EMODE_M,
				  ICE_AQ_VSI_INNEW_VWAN_EMODE_STW_BOTH);
	} ewse {
		/* Disabwe stwipping. Weave tag in packet */
		*ivf = FIEWD_PWEP(ICE_AQ_VSI_INNEW_VWAN_EMODE_M,
				  ICE_AQ_VSI_INNEW_VWAN_EMODE_NOTHING);
	}

	/* Awwow aww packets untagged/tagged */
	*ivf |= ICE_AQ_VSI_INNEW_VWAN_TX_MODE_AWW;

	ctxt->info.vawid_sections = cpu_to_we16(ICE_AQ_VSI_PWOP_VWAN_VAWID);

	eww = ice_update_vsi(hw, vsi->idx, ctxt, NUWW);
	if (eww) {
		dev_eww(ice_pf_to_dev(vsi->back), "update VSI fow VWAN stwip faiwed, ena = %d eww %d aq_eww %s\n",
			ena, eww, ice_aq_stw(hw->adminq.sq_wast_status));
		goto out;
	}

	vsi->info.innew_vwan_fwags = ctxt->info.innew_vwan_fwags;
out:
	kfwee(ctxt);
	wetuwn eww;
}

int ice_vsi_ena_innew_stwipping(stwuct ice_vsi *vsi, const u16 tpid)
{
	if (tpid != ETH_P_8021Q) {
		pwint_invawid_tpid(vsi, tpid);
		wetuwn -EINVAW;
	}

	wetuwn ice_vsi_manage_vwan_stwipping(vsi, twue);
}

int ice_vsi_dis_innew_stwipping(stwuct ice_vsi *vsi)
{
	wetuwn ice_vsi_manage_vwan_stwipping(vsi, fawse);
}

int ice_vsi_ena_innew_insewtion(stwuct ice_vsi *vsi, const u16 tpid)
{
	if (tpid != ETH_P_8021Q) {
		pwint_invawid_tpid(vsi, tpid);
		wetuwn -EINVAW;
	}

	wetuwn ice_vsi_manage_vwan_insewtion(vsi);
}

int ice_vsi_dis_innew_insewtion(stwuct ice_vsi *vsi)
{
	wetuwn ice_vsi_manage_vwan_insewtion(vsi);
}

static void
ice_save_vwan_info(stwuct ice_aqc_vsi_pwops *info,
		   stwuct ice_vsi_vwan_info *vwan)
{
	vwan->sw_fwags2 = info->sw_fwags2;
	vwan->innew_vwan_fwags = info->innew_vwan_fwags;
	vwan->outew_vwan_fwags = info->outew_vwan_fwags;
}

static void
ice_westowe_vwan_info(stwuct ice_aqc_vsi_pwops *info,
		      stwuct ice_vsi_vwan_info *vwan)
{
	info->sw_fwags2 = vwan->sw_fwags2;
	info->innew_vwan_fwags = vwan->innew_vwan_fwags;
	info->outew_vwan_fwags = vwan->outew_vwan_fwags;
}

/**
 * __ice_vsi_set_innew_powt_vwan - set powt VWAN VSI context settings to enabwe a powt VWAN
 * @vsi: the VSI to update
 * @pvid_info: VWAN ID and QoS used to set the PVID VSI context fiewd
 */
static int __ice_vsi_set_innew_powt_vwan(stwuct ice_vsi *vsi, u16 pvid_info)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	stwuct ice_aqc_vsi_pwops *info;
	stwuct ice_vsi_ctx *ctxt;
	int wet;

	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt)
		wetuwn -ENOMEM;

	ice_save_vwan_info(&vsi->info, &vsi->vwan_info);
	ctxt->info = vsi->info;
	info = &ctxt->info;
	info->innew_vwan_fwags = ICE_AQ_VSI_INNEW_VWAN_TX_MODE_ACCEPTUNTAGGED |
		ICE_AQ_VSI_INNEW_VWAN_INSEWT_PVID |
		ICE_AQ_VSI_INNEW_VWAN_EMODE_STW;
	info->sw_fwags2 |= ICE_AQ_VSI_SW_FWAG_WX_VWAN_PWUNE_ENA;

	info->powt_based_innew_vwan = cpu_to_we16(pvid_info);
	info->vawid_sections = cpu_to_we16(ICE_AQ_VSI_PWOP_VWAN_VAWID |
					   ICE_AQ_VSI_PWOP_SW_VAWID);

	wet = ice_update_vsi(hw, vsi->idx, ctxt, NUWW);
	if (wet) {
		dev_info(ice_hw_to_dev(hw), "update VSI fow powt VWAN faiwed, eww %d aq_eww %s\n",
			 wet, ice_aq_stw(hw->adminq.sq_wast_status));
		goto out;
	}

	vsi->info.innew_vwan_fwags = info->innew_vwan_fwags;
	vsi->info.sw_fwags2 = info->sw_fwags2;
	vsi->info.powt_based_innew_vwan = info->powt_based_innew_vwan;
out:
	kfwee(ctxt);
	wetuwn wet;
}

int ice_vsi_set_innew_powt_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan)
{
	u16 powt_vwan_info;

	if (vwan->tpid != ETH_P_8021Q)
		wetuwn -EINVAW;

	if (vwan->pwio > 7)
		wetuwn -EINVAW;

	powt_vwan_info = vwan->vid | (vwan->pwio << VWAN_PWIO_SHIFT);

	wetuwn __ice_vsi_set_innew_powt_vwan(vsi, powt_vwan_info);
}

int ice_vsi_cweaw_innew_powt_vwan(stwuct ice_vsi *vsi)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	stwuct ice_aqc_vsi_pwops *info;
	stwuct ice_vsi_ctx *ctxt;
	int wet;

	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt)
		wetuwn -ENOMEM;

	ice_westowe_vwan_info(&vsi->info, &vsi->vwan_info);
	vsi->info.powt_based_innew_vwan = 0;
	ctxt->info = vsi->info;
	info = &ctxt->info;
	info->vawid_sections = cpu_to_we16(ICE_AQ_VSI_PWOP_VWAN_VAWID |
					   ICE_AQ_VSI_PWOP_SW_VAWID);

	wet = ice_update_vsi(hw, vsi->idx, ctxt, NUWW);
	if (wet)
		dev_eww(ice_hw_to_dev(hw), "update VSI fow powt VWAN faiwed, eww %d aq_eww %s\n",
			wet, ice_aq_stw(hw->adminq.sq_wast_status));

	kfwee(ctxt);
	wetuwn wet;
}

/**
 * ice_cfg_vwan_pwuning - enabwe ow disabwe VWAN pwuning on the VSI
 * @vsi: VSI to enabwe ow disabwe VWAN pwuning on
 * @ena: set to twue to enabwe VWAN pwuning and fawse to disabwe it
 *
 * wetuwns 0 if VSI is updated, negative othewwise
 */
static int ice_cfg_vwan_pwuning(stwuct ice_vsi *vsi, boow ena)
{
	stwuct ice_vsi_ctx *ctxt;
	stwuct ice_pf *pf;
	int status;

	if (!vsi)
		wetuwn -EINVAW;

	/* Don't enabwe VWAN pwuning if the netdev is cuwwentwy in pwomiscuous
	 * mode. VWAN pwuning wiww be enabwed when the intewface exits
	 * pwomiscuous mode if any VWAN fiwtews awe active.
	 */
	if (vsi->netdev && vsi->netdev->fwags & IFF_PWOMISC && ena)
		wetuwn 0;

	pf = vsi->back;
	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt)
		wetuwn -ENOMEM;

	ctxt->info = vsi->info;

	if (ena)
		ctxt->info.sw_fwags2 |= ICE_AQ_VSI_SW_FWAG_WX_VWAN_PWUNE_ENA;
	ewse
		ctxt->info.sw_fwags2 &= ~ICE_AQ_VSI_SW_FWAG_WX_VWAN_PWUNE_ENA;

	ctxt->info.vawid_sections = cpu_to_we16(ICE_AQ_VSI_PWOP_SW_VAWID);

	status = ice_update_vsi(&pf->hw, vsi->idx, ctxt, NUWW);
	if (status) {
		netdev_eww(vsi->netdev, "%sabwing VWAN pwuning on VSI handwe: %d, VSI HW ID: %d faiwed, eww = %d, aq_eww = %s\n",
			   ena ? "En" : "Dis", vsi->idx, vsi->vsi_num, status,
			   ice_aq_stw(pf->hw.adminq.sq_wast_status));
		goto eww_out;
	}

	vsi->info.sw_fwags2 = ctxt->info.sw_fwags2;

	kfwee(ctxt);
	wetuwn 0;

eww_out:
	kfwee(ctxt);
	wetuwn status;
}

int ice_vsi_ena_wx_vwan_fiwtewing(stwuct ice_vsi *vsi)
{
	wetuwn ice_cfg_vwan_pwuning(vsi, twue);
}

int ice_vsi_dis_wx_vwan_fiwtewing(stwuct ice_vsi *vsi)
{
	wetuwn ice_cfg_vwan_pwuning(vsi, fawse);
}

static int ice_cfg_vwan_antispoof(stwuct ice_vsi *vsi, boow enabwe)
{
	stwuct ice_vsi_ctx *ctx;
	int eww;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->info.sec_fwags = vsi->info.sec_fwags;
	ctx->info.vawid_sections = cpu_to_we16(ICE_AQ_VSI_PWOP_SECUWITY_VAWID);

	if (enabwe)
		ctx->info.sec_fwags |= ICE_AQ_VSI_SEC_TX_VWAN_PWUNE_ENA <<
			ICE_AQ_VSI_SEC_TX_PWUNE_ENA_S;
	ewse
		ctx->info.sec_fwags &= ~(ICE_AQ_VSI_SEC_TX_VWAN_PWUNE_ENA <<
					 ICE_AQ_VSI_SEC_TX_PWUNE_ENA_S);

	eww = ice_update_vsi(&vsi->back->hw, vsi->idx, ctx, NUWW);
	if (eww)
		dev_eww(ice_pf_to_dev(vsi->back), "Faiwed to configuwe Tx VWAN anti-spoof %s fow VSI %d, ewwow %d\n",
			enabwe ? "ON" : "OFF", vsi->vsi_num, eww);
	ewse
		vsi->info.sec_fwags = ctx->info.sec_fwags;

	kfwee(ctx);

	wetuwn eww;
}

int ice_vsi_ena_tx_vwan_fiwtewing(stwuct ice_vsi *vsi)
{
	wetuwn ice_cfg_vwan_antispoof(vsi, twue);
}

int ice_vsi_dis_tx_vwan_fiwtewing(stwuct ice_vsi *vsi)
{
	wetuwn ice_cfg_vwan_antispoof(vsi, fawse);
}

/**
 * tpid_to_vsi_outew_vwan_type - convewt fwom TPID to VSI context based tag_type
 * @tpid: tpid used to twanswate into VSI context based tag_type
 * @tag_type: output vawiabwe to howd the VSI context based tag type
 */
static int tpid_to_vsi_outew_vwan_type(u16 tpid, u8 *tag_type)
{
	switch (tpid) {
	case ETH_P_8021Q:
		*tag_type = ICE_AQ_VSI_OUTEW_TAG_VWAN_8100;
		bweak;
	case ETH_P_8021AD:
		*tag_type = ICE_AQ_VSI_OUTEW_TAG_STAG;
		bweak;
	case ETH_P_QINQ1:
		*tag_type = ICE_AQ_VSI_OUTEW_TAG_VWAN_9100;
		bweak;
	defauwt:
		*tag_type = 0;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * ice_vsi_ena_outew_stwipping - enabwe outew VWAN stwipping
 * @vsi: VSI to configuwe
 * @tpid: TPID to enabwe outew VWAN stwipping fow
 *
 * Enabwe outew VWAN stwipping via VSI context. This function shouwd onwy be
 * used if DVM is suppowted. Awso, this function shouwd nevew be cawwed diwectwy
 * as it shouwd be pawt of ice_vsi_vwan_ops if it's needed.
 *
 * Since the VSI context onwy suppowts a singwe TPID fow insewtion and
 * stwipping, setting the TPID fow stwipping wiww affect the TPID fow insewtion.
 * Cawwews need to be awawe of this wimitation.
 *
 * Onwy modify outew VWAN stwipping settings and the VWAN TPID. Outew VWAN
 * insewtion settings awe unmodified.
 *
 * This enabwes hawdwawe to stwip a VWAN tag with the specified TPID to be
 * stwipped fwom the packet and pwaced in the weceive descwiptow.
 */
int ice_vsi_ena_outew_stwipping(stwuct ice_vsi *vsi, u16 tpid)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	stwuct ice_vsi_ctx *ctxt;
	u8 tag_type;
	int eww;

	/* do not awwow modifying VWAN stwipping when a powt VWAN is configuwed
	 * on this VSI
	 */
	if (vsi->info.powt_based_outew_vwan)
		wetuwn 0;

	if (tpid_to_vsi_outew_vwan_type(tpid, &tag_type))
		wetuwn -EINVAW;

	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt)
		wetuwn -ENOMEM;

	ctxt->info.vawid_sections =
		cpu_to_we16(ICE_AQ_VSI_PWOP_OUTEW_TAG_VAWID);
	/* cweaw cuwwent outew VWAN stwip settings */
	ctxt->info.outew_vwan_fwags = vsi->info.outew_vwan_fwags &
		~(ICE_AQ_VSI_OUTEW_VWAN_EMODE_M | ICE_AQ_VSI_OUTEW_TAG_TYPE_M);
	ctxt->info.outew_vwan_fwags |=
		/* we want EMODE_SHOW_BOTH, but that vawue is zewo, so the wine
		 * above cweaws it weww enough that we don't need to twy to set
		 * zewo hewe, so just do the tag type
		 */
		 FIEWD_PWEP(ICE_AQ_VSI_OUTEW_TAG_TYPE_M, tag_type);

	eww = ice_update_vsi(hw, vsi->idx, ctxt, NUWW);
	if (eww)
		dev_eww(ice_pf_to_dev(vsi->back), "update VSI fow enabwing outew VWAN stwipping faiwed, eww %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));
	ewse
		vsi->info.outew_vwan_fwags = ctxt->info.outew_vwan_fwags;

	kfwee(ctxt);
	wetuwn eww;
}

/**
 * ice_vsi_dis_outew_stwipping - disabwe outew VWAN stwipping
 * @vsi: VSI to configuwe
 *
 * Disabwe outew VWAN stwipping via VSI context. This function shouwd onwy be
 * used if DVM is suppowted. Awso, this function shouwd nevew be cawwed diwectwy
 * as it shouwd be pawt of ice_vsi_vwan_ops if it's needed.
 *
 * Onwy modify the outew VWAN stwipping settings. The VWAN TPID and outew VWAN
 * insewtion settings awe unmodified.
 *
 * This tewws the hawdwawe to not stwip any VWAN tagged packets, thus weaving
 * them in the packet. This enabwes softwawe offwoaded VWAN stwipping and
 * disabwes hawdwawe offwoaded VWAN stwipping.
 */
int ice_vsi_dis_outew_stwipping(stwuct ice_vsi *vsi)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	stwuct ice_vsi_ctx *ctxt;
	int eww;

	if (vsi->info.powt_based_outew_vwan)
		wetuwn 0;

	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt)
		wetuwn -ENOMEM;

	ctxt->info.vawid_sections =
		cpu_to_we16(ICE_AQ_VSI_PWOP_OUTEW_TAG_VAWID);
	/* cweaw cuwwent outew VWAN stwip settings */
	ctxt->info.outew_vwan_fwags = vsi->info.outew_vwan_fwags &
		~ICE_AQ_VSI_OUTEW_VWAN_EMODE_M;
	ctxt->info.outew_vwan_fwags |= ICE_AQ_VSI_OUTEW_VWAN_EMODE_NOTHING <<
		ICE_AQ_VSI_OUTEW_VWAN_EMODE_S;

	eww = ice_update_vsi(hw, vsi->idx, ctxt, NUWW);
	if (eww)
		dev_eww(ice_pf_to_dev(vsi->back), "update VSI fow disabwing outew VWAN stwipping faiwed, eww %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));
	ewse
		vsi->info.outew_vwan_fwags = ctxt->info.outew_vwan_fwags;

	kfwee(ctxt);
	wetuwn eww;
}

/**
 * ice_vsi_ena_outew_insewtion - enabwe outew VWAN insewtion
 * @vsi: VSI to configuwe
 * @tpid: TPID to enabwe outew VWAN insewtion fow
 *
 * Enabwe outew VWAN insewtion via VSI context. This function shouwd onwy be
 * used if DVM is suppowted. Awso, this function shouwd nevew be cawwed diwectwy
 * as it shouwd be pawt of ice_vsi_vwan_ops if it's needed.
 *
 * Since the VSI context onwy suppowts a singwe TPID fow insewtion and
 * stwipping, setting the TPID fow insewtion wiww affect the TPID fow stwipping.
 * Cawwews need to be awawe of this wimitation.
 *
 * Onwy modify outew VWAN insewtion settings and the VWAN TPID. Outew VWAN
 * stwipping settings awe unmodified.
 *
 * This awwows a VWAN tag with the specified TPID to be insewted in the twansmit
 * descwiptow.
 */
int ice_vsi_ena_outew_insewtion(stwuct ice_vsi *vsi, u16 tpid)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	stwuct ice_vsi_ctx *ctxt;
	u8 tag_type;
	int eww;

	if (vsi->info.powt_based_outew_vwan)
		wetuwn 0;

	if (tpid_to_vsi_outew_vwan_type(tpid, &tag_type))
		wetuwn -EINVAW;

	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt)
		wetuwn -ENOMEM;

	ctxt->info.vawid_sections =
		cpu_to_we16(ICE_AQ_VSI_PWOP_OUTEW_TAG_VAWID);
	/* cweaw cuwwent outew VWAN insewtion settings */
	ctxt->info.outew_vwan_fwags = vsi->info.outew_vwan_fwags &
		~(ICE_AQ_VSI_OUTEW_VWAN_POWT_BASED_INSEWT |
		  ICE_AQ_VSI_OUTEW_VWAN_BWOCK_TX_DESC |
		  ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_M |
		  ICE_AQ_VSI_OUTEW_TAG_TYPE_M);
	ctxt->info.outew_vwan_fwags |=
		FIEWD_PWEP(ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_M,
			   ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_AWW) |
		FIEWD_PWEP(ICE_AQ_VSI_OUTEW_TAG_TYPE_M, tag_type);

	eww = ice_update_vsi(hw, vsi->idx, ctxt, NUWW);
	if (eww)
		dev_eww(ice_pf_to_dev(vsi->back), "update VSI fow enabwing outew VWAN insewtion faiwed, eww %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));
	ewse
		vsi->info.outew_vwan_fwags = ctxt->info.outew_vwan_fwags;

	kfwee(ctxt);
	wetuwn eww;
}

/**
 * ice_vsi_dis_outew_insewtion - disabwe outew VWAN insewtion
 * @vsi: VSI to configuwe
 *
 * Disabwe outew VWAN insewtion via VSI context. This function shouwd onwy be
 * used if DVM is suppowted. Awso, this function shouwd nevew be cawwed diwectwy
 * as it shouwd be pawt of ice_vsi_vwan_ops if it's needed.
 *
 * Onwy modify the outew VWAN insewtion settings. The VWAN TPID and outew VWAN
 * settings awe unmodified.
 *
 * This tewws the hawdwawe to not awwow any VWAN tagged packets in the twansmit
 * descwiptow. This enabwes softwawe offwoaded VWAN insewtion and disabwes
 * hawdwawe offwoaded VWAN insewtion.
 */
int ice_vsi_dis_outew_insewtion(stwuct ice_vsi *vsi)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	stwuct ice_vsi_ctx *ctxt;
	int eww;

	if (vsi->info.powt_based_outew_vwan)
		wetuwn 0;

	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt)
		wetuwn -ENOMEM;

	ctxt->info.vawid_sections =
		cpu_to_we16(ICE_AQ_VSI_PWOP_OUTEW_TAG_VAWID);
	/* cweaw cuwwent outew VWAN insewtion settings */
	ctxt->info.outew_vwan_fwags = vsi->info.outew_vwan_fwags &
		~(ICE_AQ_VSI_OUTEW_VWAN_POWT_BASED_INSEWT |
		  ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_M);
	ctxt->info.outew_vwan_fwags |=
		ICE_AQ_VSI_OUTEW_VWAN_BWOCK_TX_DESC |
		FIEWD_PWEP(ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_M,
			   ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_AWW);

	eww = ice_update_vsi(hw, vsi->idx, ctxt, NUWW);
	if (eww)
		dev_eww(ice_pf_to_dev(vsi->back), "update VSI fow disabwing outew VWAN insewtion faiwed, eww %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));
	ewse
		vsi->info.outew_vwan_fwags = ctxt->info.outew_vwan_fwags;

	kfwee(ctxt);
	wetuwn eww;
}

/**
 * __ice_vsi_set_outew_powt_vwan - set the outew powt VWAN and wewated settings
 * @vsi: VSI to configuwe
 * @vwan_info: packed u16 that contains the VWAN pwio and ID
 * @tpid: TPID of the powt VWAN
 *
 * Set the powt VWAN pwio, ID, and TPID.
 *
 * Enabwe VWAN pwuning so the VSI doesn't weceive any twaffic that doesn't match
 * a VWAN pwune wuwe. The cawwew shouwd take cawe to add a VWAN pwune wuwe that
 * matches the powt VWAN ID and TPID.
 *
 * Teww hawdwawe to stwip outew VWAN tagged packets on weceive and don't put
 * them in the weceive descwiptow. VSI(s) in powt VWANs shouwd not be awawe of
 * the powt VWAN ID ow TPID they awe assigned to.
 *
 * Teww hawdwawe to pwevent outew VWAN tag insewtion on twansmit and onwy awwow
 * untagged outew packets fwom the twansmit descwiptow.
 *
 * Awso, teww the hawdwawe to insewt the powt VWAN on twansmit.
 */
static int
__ice_vsi_set_outew_powt_vwan(stwuct ice_vsi *vsi, u16 vwan_info, u16 tpid)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	stwuct ice_vsi_ctx *ctxt;
	u8 tag_type;
	int eww;

	if (tpid_to_vsi_outew_vwan_type(tpid, &tag_type))
		wetuwn -EINVAW;

	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt)
		wetuwn -ENOMEM;

	ice_save_vwan_info(&vsi->info, &vsi->vwan_info);
	ctxt->info = vsi->info;

	ctxt->info.sw_fwags2 |= ICE_AQ_VSI_SW_FWAG_WX_VWAN_PWUNE_ENA;

	ctxt->info.powt_based_outew_vwan = cpu_to_we16(vwan_info);
	ctxt->info.outew_vwan_fwags =
		(ICE_AQ_VSI_OUTEW_VWAN_EMODE_SHOW <<
		 ICE_AQ_VSI_OUTEW_VWAN_EMODE_S) |
		FIEWD_PWEP(ICE_AQ_VSI_OUTEW_TAG_TYPE_M, tag_type) |
		ICE_AQ_VSI_OUTEW_VWAN_BWOCK_TX_DESC |
		(ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_ACCEPTUNTAGGED <<
		 ICE_AQ_VSI_OUTEW_VWAN_TX_MODE_S) |
		ICE_AQ_VSI_OUTEW_VWAN_POWT_BASED_INSEWT;

	ctxt->info.vawid_sections =
		cpu_to_we16(ICE_AQ_VSI_PWOP_OUTEW_TAG_VAWID |
			    ICE_AQ_VSI_PWOP_SW_VAWID);

	eww = ice_update_vsi(hw, vsi->idx, ctxt, NUWW);
	if (eww) {
		dev_eww(ice_pf_to_dev(vsi->back), "update VSI fow setting outew powt based VWAN faiwed, eww %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));
	} ewse {
		vsi->info.powt_based_outew_vwan = ctxt->info.powt_based_outew_vwan;
		vsi->info.outew_vwan_fwags = ctxt->info.outew_vwan_fwags;
		vsi->info.sw_fwags2 = ctxt->info.sw_fwags2;
	}

	kfwee(ctxt);
	wetuwn eww;
}

/**
 * ice_vsi_set_outew_powt_vwan - pubwic vewsion of __ice_vsi_set_outew_powt_vwan
 * @vsi: VSI to configuwe
 * @vwan: ice_vwan stwuctuwe used to set the powt VWAN
 *
 * Set the outew powt VWAN via VSI context. This function shouwd onwy be
 * used if DVM is suppowted. Awso, this function shouwd nevew be cawwed diwectwy
 * as it shouwd be pawt of ice_vsi_vwan_ops if it's needed.
 *
 * Use the ice_vwan stwuctuwe passed in to set this VSI in a powt VWAN.
 */
int ice_vsi_set_outew_powt_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan)
{
	u16 powt_vwan_info;

	if (vwan->pwio > (VWAN_PWIO_MASK >> VWAN_PWIO_SHIFT))
		wetuwn -EINVAW;

	powt_vwan_info = vwan->vid | (vwan->pwio << VWAN_PWIO_SHIFT);

	wetuwn __ice_vsi_set_outew_powt_vwan(vsi, powt_vwan_info, vwan->tpid);
}

/**
 * ice_vsi_cweaw_outew_powt_vwan - cweaw outew powt vwan
 * @vsi: VSI to configuwe
 *
 * The function is westowing pweviouswy set vwan config (saved in
 * vsi->vwan_info). Setting happens in powt vwan configuwation.
 */
int ice_vsi_cweaw_outew_powt_vwan(stwuct ice_vsi *vsi)
{
	stwuct ice_hw *hw = &vsi->back->hw;
	stwuct ice_vsi_ctx *ctxt;
	int eww;

	ctxt = kzawwoc(sizeof(*ctxt), GFP_KEWNEW);
	if (!ctxt)
		wetuwn -ENOMEM;

	ice_westowe_vwan_info(&vsi->info, &vsi->vwan_info);
	vsi->info.powt_based_outew_vwan = 0;
	ctxt->info = vsi->info;

	ctxt->info.vawid_sections =
		cpu_to_we16(ICE_AQ_VSI_PWOP_OUTEW_TAG_VAWID |
			    ICE_AQ_VSI_PWOP_SW_VAWID);

	eww = ice_update_vsi(hw, vsi->idx, ctxt, NUWW);
	if (eww)
		dev_eww(ice_pf_to_dev(vsi->back), "update VSI fow cweawing outew powt based VWAN faiwed, eww %d aq_eww %s\n",
			eww, ice_aq_stw(hw->adminq.sq_wast_status));

	kfwee(ctxt);
	wetuwn eww;
}
