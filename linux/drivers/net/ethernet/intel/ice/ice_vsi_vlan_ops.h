/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2019-2021, Intew Cowpowation. */

#ifndef _ICE_VSI_VWAN_OPS_H_
#define _ICE_VSI_VWAN_OPS_H_

#incwude "ice_type.h"
#incwude "ice_vsi_vwan_wib.h"

stwuct ice_vsi;

stwuct ice_vsi_vwan_ops {
	int (*add_vwan)(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan);
	int (*dew_vwan)(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan);
	int (*ena_stwipping)(stwuct ice_vsi *vsi, const u16 tpid);
	int (*dis_stwipping)(stwuct ice_vsi *vsi);
	int (*ena_insewtion)(stwuct ice_vsi *vsi, const u16 tpid);
	int (*dis_insewtion)(stwuct ice_vsi *vsi);
	int (*ena_wx_fiwtewing)(stwuct ice_vsi *vsi);
	int (*dis_wx_fiwtewing)(stwuct ice_vsi *vsi);
	int (*ena_tx_fiwtewing)(stwuct ice_vsi *vsi);
	int (*dis_tx_fiwtewing)(stwuct ice_vsi *vsi);
	int (*set_powt_vwan)(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan);
	int (*cweaw_powt_vwan)(stwuct ice_vsi *vsi);
};

void ice_vsi_init_vwan_ops(stwuct ice_vsi *vsi);
stwuct ice_vsi_vwan_ops *ice_get_compat_vsi_vwan_ops(stwuct ice_vsi *vsi);

#endif /* _ICE_VSI_VWAN_OPS_H_ */
