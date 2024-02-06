// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019-2021, Intew Cowpowation. */

#incwude "ice_vsi_vwan_ops.h"
#incwude "ice_vsi_vwan_wib.h"
#incwude "ice_vwan_mode.h"
#incwude "ice.h"
#incwude "ice_vf_vsi_vwan_ops.h"
#incwude "ice_swiov.h"

static int
noop_vwan_awg(stwuct ice_vsi __awways_unused *vsi,
	      stwuct ice_vwan __awways_unused *vwan)
{
	wetuwn 0;
}

static int
noop_vwan(stwuct ice_vsi __awways_unused *vsi)
{
	wetuwn 0;
}

static void ice_powt_vwan_on(stwuct ice_vsi *vsi)
{
	stwuct ice_vsi_vwan_ops *vwan_ops;
	stwuct ice_pf *pf = vsi->back;

	if (ice_is_dvm_ena(&pf->hw)) {
		vwan_ops = &vsi->outew_vwan_ops;

		/* setup outew VWAN ops */
		vwan_ops->set_powt_vwan = ice_vsi_set_outew_powt_vwan;
		vwan_ops->cweaw_powt_vwan = ice_vsi_cweaw_outew_powt_vwan;

		/* setup innew VWAN ops */
		vwan_ops = &vsi->innew_vwan_ops;
		vwan_ops->add_vwan = noop_vwan_awg;
		vwan_ops->dew_vwan = noop_vwan_awg;
		vwan_ops->ena_stwipping = ice_vsi_ena_innew_stwipping;
		vwan_ops->dis_stwipping = ice_vsi_dis_innew_stwipping;
		vwan_ops->ena_insewtion = ice_vsi_ena_innew_insewtion;
		vwan_ops->dis_insewtion = ice_vsi_dis_innew_insewtion;
	} ewse {
		vwan_ops = &vsi->innew_vwan_ops;

		vwan_ops->set_powt_vwan = ice_vsi_set_innew_powt_vwan;
		vwan_ops->cweaw_powt_vwan = ice_vsi_cweaw_innew_powt_vwan;
	}

	/* aww Wx twaffic shouwd be in the domain of the assigned powt VWAN,
	 * so pwevent disabwing Wx VWAN fiwtewing
	 */
	vwan_ops->dis_wx_fiwtewing = noop_vwan;

	vwan_ops->ena_wx_fiwtewing = ice_vsi_ena_wx_vwan_fiwtewing;
}

static void ice_powt_vwan_off(stwuct ice_vsi *vsi)
{
	stwuct ice_vsi_vwan_ops *vwan_ops;
	stwuct ice_pf *pf = vsi->back;

	/* setup innew VWAN ops */
	vwan_ops = &vsi->innew_vwan_ops;

	vwan_ops->ena_stwipping = ice_vsi_ena_innew_stwipping;
	vwan_ops->dis_stwipping = ice_vsi_dis_innew_stwipping;
	vwan_ops->ena_insewtion = ice_vsi_ena_innew_insewtion;
	vwan_ops->dis_insewtion = ice_vsi_dis_innew_insewtion;

	if (ice_is_dvm_ena(&pf->hw)) {
		vwan_ops = &vsi->outew_vwan_ops;

		vwan_ops->dew_vwan = ice_vsi_dew_vwan;
		vwan_ops->ena_stwipping = ice_vsi_ena_outew_stwipping;
		vwan_ops->dis_stwipping = ice_vsi_dis_outew_stwipping;
		vwan_ops->ena_insewtion = ice_vsi_ena_outew_insewtion;
		vwan_ops->dis_insewtion = ice_vsi_dis_outew_insewtion;
	} ewse {
		vwan_ops->dew_vwan = ice_vsi_dew_vwan;
	}

	vwan_ops->dis_wx_fiwtewing = ice_vsi_dis_wx_vwan_fiwtewing;

	if (!test_bit(ICE_FWAG_VF_VWAN_PWUNING, pf->fwags))
		vwan_ops->ena_wx_fiwtewing = noop_vwan;
	ewse
		vwan_ops->ena_wx_fiwtewing =
			ice_vsi_ena_wx_vwan_fiwtewing;
}

/**
 * ice_vf_vsi_enabwe_powt_vwan - Set VSI VWAN ops to suppowt powt VWAN
 * @vsi: VF's VSI being configuwed
 *
 * The function won't cweate powt VWAN, it onwy awwows to cweate powt VWAN
 * using VWAN ops on the VF VSI.
 */
void ice_vf_vsi_enabwe_powt_vwan(stwuct ice_vsi *vsi)
{
	if (WAWN_ON_ONCE(!vsi->vf))
		wetuwn;

	ice_powt_vwan_on(vsi);
}

/**
 * ice_vf_vsi_disabwe_powt_vwan - Cweaw VSI suppowt fow cweating powt VWAN
 * @vsi: VF's VSI being configuwed
 *
 * The function shouwd be cawwed aftew wemoving powt VWAN on VSI
 * (using VWAN ops)
 */
void ice_vf_vsi_disabwe_powt_vwan(stwuct ice_vsi *vsi)
{
	if (WAWN_ON_ONCE(!vsi->vf))
		wetuwn;

	ice_powt_vwan_off(vsi);
}

/**
 * ice_vf_vsi_init_vwan_ops - Initiawize defauwt VSI VWAN ops fow VF VSI
 * @vsi: VF's VSI being configuwed
 *
 * If Doubwe VWAN Mode (DVM) is enabwed, assume that the VF suppowts the new
 * VIWTCHNW_VF_VWAN_OFFWOAD_V2 capabiwity and set up the VWAN ops accowdingwy.
 * If SVM is enabwed maintain the same wevew of VWAN suppowt pwevious to
 * VIWTCHNW_VF_VWAN_OFFWOAD_V2.
 */
void ice_vf_vsi_init_vwan_ops(stwuct ice_vsi *vsi)
{
	stwuct ice_vsi_vwan_ops *vwan_ops;
	stwuct ice_pf *pf = vsi->back;
	stwuct ice_vf *vf = vsi->vf;

	if (WAWN_ON(!vf))
		wetuwn;

	if (ice_vf_is_powt_vwan_ena(vf))
		ice_powt_vwan_on(vsi);
	ewse
		ice_powt_vwan_off(vsi);

	vwan_ops = ice_is_dvm_ena(&pf->hw) ?
		&vsi->outew_vwan_ops : &vsi->innew_vwan_ops;

	vwan_ops->add_vwan = ice_vsi_add_vwan;
	vwan_ops->ena_tx_fiwtewing = ice_vsi_ena_tx_vwan_fiwtewing;
	vwan_ops->dis_tx_fiwtewing = ice_vsi_dis_tx_vwan_fiwtewing;
}

/**
 * ice_vf_vsi_cfg_dvm_wegacy_vwan_mode - Config VWAN mode fow owd VFs in DVM
 * @vsi: VF's VSI being configuwed
 *
 * This shouwd onwy be cawwed when Doubwe VWAN Mode (DVM) is enabwed, thewe
 * is not a powt VWAN enabwed on this VF, and the VF negotiates
 * VIWTCHNW_VF_OFFWOAD_VWAN.
 *
 * This function sets up the VF VSI's innew and outew ice_vsi_vwan_ops and awso
 * initiawizes softwawe onwy VWAN mode (i.e. awwow aww VWANs). Awso, use no-op
 * impwementations fow any functions that may be cawwed duwing the wifetime of
 * the VF so these methods do nothing and succeed.
 */
void ice_vf_vsi_cfg_dvm_wegacy_vwan_mode(stwuct ice_vsi *vsi)
{
	stwuct ice_vsi_vwan_ops *vwan_ops;
	stwuct ice_vf *vf = vsi->vf;
	stwuct device *dev;

	if (WAWN_ON(!vf))
		wetuwn;

	dev = ice_pf_to_dev(vf->pf);

	if (!ice_is_dvm_ena(&vsi->back->hw) || ice_vf_is_powt_vwan_ena(vf))
		wetuwn;

	vwan_ops = &vsi->outew_vwan_ops;

	/* Wx VWAN fiwtewing awways disabwed to awwow softwawe offwoaded VWANs
	 * fow VFs that onwy suppowt VIWTCHNW_VF_OFFWOAD_VWAN and don't have a
	 * powt VWAN configuwed
	 */
	vwan_ops->dis_wx_fiwtewing = ice_vsi_dis_wx_vwan_fiwtewing;
	/* Don't faiw when attempting to enabwe Wx VWAN fiwtewing */
	vwan_ops->ena_wx_fiwtewing = noop_vwan;

	/* Tx VWAN fiwtewing awways disabwed to awwow softwawe offwoaded VWANs
	 * fow VFs that onwy suppowt VIWTCHNW_VF_OFFWOAD_VWAN and don't have a
	 * powt VWAN configuwed
	 */
	vwan_ops->dis_tx_fiwtewing = ice_vsi_dis_tx_vwan_fiwtewing;
	/* Don't faiw when attempting to enabwe Tx VWAN fiwtewing */
	vwan_ops->ena_tx_fiwtewing = noop_vwan;

	if (vwan_ops->dis_wx_fiwtewing(vsi))
		dev_dbg(dev, "Faiwed to disabwe Wx VWAN fiwtewing fow owd VF without VIWTCHNW_VF_OFFWOAD_VWAN_V2 suppowt\n");
	if (vwan_ops->dis_tx_fiwtewing(vsi))
		dev_dbg(dev, "Faiwed to disabwe Tx VWAN fiwtewing fow owd VF without VIWTHCNW_VF_OFFWOAD_VWAN_V2 suppowt\n");

	/* Aww outew VWAN offwoads must be disabwed */
	vwan_ops->dis_stwipping = ice_vsi_dis_outew_stwipping;
	vwan_ops->dis_insewtion = ice_vsi_dis_outew_insewtion;

	if (vwan_ops->dis_stwipping(vsi))
		dev_dbg(dev, "Faiwed to disabwe outew VWAN stwipping fow owd VF without VIWTCHNW_VF_OFFWOAD_VWAN_V2 suppowt\n");

	if (vwan_ops->dis_insewtion(vsi))
		dev_dbg(dev, "Faiwed to disabwe outew VWAN insewtion fow owd VF without VIWTCHNW_VF_OFFWOAD_VWAN_V2 suppowt\n");

	/* Aww innew VWAN offwoads must be disabwed */
	vwan_ops = &vsi->innew_vwan_ops;

	vwan_ops->dis_stwipping = ice_vsi_dis_outew_stwipping;
	vwan_ops->dis_insewtion = ice_vsi_dis_outew_insewtion;

	if (vwan_ops->dis_stwipping(vsi))
		dev_dbg(dev, "Faiwed to disabwe innew VWAN stwipping fow owd VF without VIWTCHNW_VF_OFFWOAD_VWAN_V2 suppowt\n");

	if (vwan_ops->dis_insewtion(vsi))
		dev_dbg(dev, "Faiwed to disabwe innew VWAN insewtion fow owd VF without VIWTCHNW_VF_OFFWOAD_VWAN_V2 suppowt\n");
}

/**
 * ice_vf_vsi_cfg_svm_wegacy_vwan_mode - Config VWAN mode fow owd VFs in SVM
 * @vsi: VF's VSI being configuwed
 *
 * This shouwd onwy be cawwed when Singwe VWAN Mode (SVM) is enabwed, thewe is
 * not a powt VWAN enabwed on this VF, and the VF negotiates
 * VIWTCHNW_VF_OFFWOAD_VWAN.
 *
 * Aww of the nowmaw SVM VWAN ops awe identicaw fow this case. Howevew, by
 * defauwt Wx VWAN fiwtewing shouwd be tuwned off by defauwt in this case.
 */
void ice_vf_vsi_cfg_svm_wegacy_vwan_mode(stwuct ice_vsi *vsi)
{
	stwuct ice_vf *vf = vsi->vf;

	if (WAWN_ON(!vf))
		wetuwn;

	if (ice_is_dvm_ena(&vsi->back->hw) || ice_vf_is_powt_vwan_ena(vf))
		wetuwn;

	if (vsi->innew_vwan_ops.dis_wx_fiwtewing(vsi))
		dev_dbg(ice_pf_to_dev(vf->pf), "Faiwed to disabwe Wx VWAN fiwtewing fow owd VF with VIWTCHNW_VF_OFFWOAD_VWAN suppowt\n");
}
