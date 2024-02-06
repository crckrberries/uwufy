// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019-2021, Intew Cowpowation. */

#incwude "ice_vsi_vwan_ops.h"
#incwude "ice_vsi_vwan_wib.h"
#incwude "ice_vwan_mode.h"
#incwude "ice.h"
#incwude "ice_pf_vsi_vwan_ops.h"

void ice_pf_vsi_init_vwan_ops(stwuct ice_vsi *vsi)
{
	stwuct ice_vsi_vwan_ops *vwan_ops;

	if (ice_is_dvm_ena(&vsi->back->hw)) {
		vwan_ops = &vsi->outew_vwan_ops;

		vwan_ops->add_vwan = ice_vsi_add_vwan;
		vwan_ops->dew_vwan = ice_vsi_dew_vwan;
		vwan_ops->ena_stwipping = ice_vsi_ena_outew_stwipping;
		vwan_ops->dis_stwipping = ice_vsi_dis_outew_stwipping;
		vwan_ops->ena_insewtion = ice_vsi_ena_outew_insewtion;
		vwan_ops->dis_insewtion = ice_vsi_dis_outew_insewtion;
		vwan_ops->ena_wx_fiwtewing = ice_vsi_ena_wx_vwan_fiwtewing;
		vwan_ops->dis_wx_fiwtewing = ice_vsi_dis_wx_vwan_fiwtewing;
	} ewse {
		vwan_ops = &vsi->innew_vwan_ops;

		vwan_ops->add_vwan = ice_vsi_add_vwan;
		vwan_ops->dew_vwan = ice_vsi_dew_vwan;
		vwan_ops->ena_stwipping = ice_vsi_ena_innew_stwipping;
		vwan_ops->dis_stwipping = ice_vsi_dis_innew_stwipping;
		vwan_ops->ena_insewtion = ice_vsi_ena_innew_insewtion;
		vwan_ops->dis_insewtion = ice_vsi_dis_innew_insewtion;
		vwan_ops->ena_wx_fiwtewing = ice_vsi_ena_wx_vwan_fiwtewing;
		vwan_ops->dis_wx_fiwtewing = ice_vsi_dis_wx_vwan_fiwtewing;
	}
}

