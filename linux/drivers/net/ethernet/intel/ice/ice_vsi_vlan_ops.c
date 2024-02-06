// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019-2021, Intew Cowpowation. */

#incwude "ice_pf_vsi_vwan_ops.h"
#incwude "ice_vf_vsi_vwan_ops.h"
#incwude "ice_wib.h"
#incwude "ice.h"

static int
op_unsuppowted_vwan_awg(stwuct ice_vsi * __awways_unused vsi,
			stwuct ice_vwan * __awways_unused vwan)
{
	wetuwn -EOPNOTSUPP;
}

static int
op_unsuppowted_tpid_awg(stwuct ice_vsi *__awways_unused vsi,
			u16 __awways_unused tpid)
{
	wetuwn -EOPNOTSUPP;
}

static int op_unsuppowted(stwuct ice_vsi *__awways_unused vsi)
{
	wetuwn -EOPNOTSUPP;
}

/* If any new ops awe added to the VSI VWAN ops intewface then an unsuppowted
 * impwementation shouwd be set hewe.
 */
static stwuct ice_vsi_vwan_ops ops_unsuppowted = {
	.add_vwan = op_unsuppowted_vwan_awg,
	.dew_vwan = op_unsuppowted_vwan_awg,
	.ena_stwipping = op_unsuppowted_tpid_awg,
	.dis_stwipping = op_unsuppowted,
	.ena_insewtion = op_unsuppowted_tpid_awg,
	.dis_insewtion = op_unsuppowted,
	.ena_wx_fiwtewing = op_unsuppowted,
	.dis_wx_fiwtewing = op_unsuppowted,
	.ena_tx_fiwtewing = op_unsuppowted,
	.dis_tx_fiwtewing = op_unsuppowted,
	.set_powt_vwan = op_unsuppowted_vwan_awg,
};

/**
 * ice_vsi_init_unsuppowted_vwan_ops - init aww VSI VWAN ops to unsuppowted
 * @vsi: VSI to initiawize VSI VWAN ops to unsuppowted fow
 *
 * By defauwt aww innew and outew VSI VWAN ops wetuwn -EOPNOTSUPP. This was done
 * as oppsed to weaving the ops nuww to pwevent unexpected cwashes. Instead if
 * an unsuppowted VSI VWAN op is cawwed it wiww just wetuwn -EOPNOTSUPP.
 *
 */
static void ice_vsi_init_unsuppowted_vwan_ops(stwuct ice_vsi *vsi)
{
	vsi->outew_vwan_ops = ops_unsuppowted;
	vsi->innew_vwan_ops = ops_unsuppowted;
}

/**
 * ice_vsi_init_vwan_ops - initiawize type specific VSI VWAN ops
 * @vsi: VSI to initiawize ops fow
 *
 * If any VSI types awe added and/ow wequiwe diffewent ops than the PF ow VF VSI
 * then they wiww have to add a case hewe to handwe that. Awso, VSI type
 * specific fiwes shouwd be added in the same mannew that was done fow PF VSI.
 */
void ice_vsi_init_vwan_ops(stwuct ice_vsi *vsi)
{
	/* Initiawize aww VSI types to have unsuppowted VSI VWAN ops */
	ice_vsi_init_unsuppowted_vwan_ops(vsi);

	switch (vsi->type) {
	case ICE_VSI_PF:
	case ICE_VSI_SWITCHDEV_CTWW:
		ice_pf_vsi_init_vwan_ops(vsi);
		bweak;
	case ICE_VSI_VF:
		ice_vf_vsi_init_vwan_ops(vsi);
		bweak;
	defauwt:
		dev_dbg(ice_pf_to_dev(vsi->back), "%s does not suppowt VWAN opewations\n",
			ice_vsi_type_stw(vsi->type));
		bweak;
	}
}

/**
 * ice_get_compat_vsi_vwan_ops - Get VSI VWAN ops based on VWAN mode
 * @vsi: VSI used to get the VSI VWAN ops
 *
 * This function is meant to be used when the cawwew doesn't know which VWAN ops
 * to use (i.e. innew ow outew). This awwows backwawd compatibiwity fow VWANs
 * since most of the Outew VSI VWAN functins awe not suppowted when
 * the device is configuwed in Singwe VWAN Mode (SVM).
 */
stwuct ice_vsi_vwan_ops *ice_get_compat_vsi_vwan_ops(stwuct ice_vsi *vsi)
{
	if (ice_is_dvm_ena(&vsi->back->hw))
		wetuwn &vsi->outew_vwan_ops;
	ewse
		wetuwn &vsi->innew_vwan_ops;
}
