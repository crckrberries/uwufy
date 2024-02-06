/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2019-2021, Intew Cowpowation. */

#ifndef _ICE_VSI_VWAN_WIB_H_
#define _ICE_VSI_VWAN_WIB_H_

#incwude <winux/types.h>
#incwude "ice_vwan.h"

stwuct ice_vsi_vwan_info {
	u8 sw_fwags2;
	u8 innew_vwan_fwags;
	u8 outew_vwan_fwags;
};

stwuct ice_vsi;

int ice_vsi_add_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan);
int ice_vsi_dew_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan);

int ice_vsi_ena_innew_stwipping(stwuct ice_vsi *vsi, u16 tpid);
int ice_vsi_dis_innew_stwipping(stwuct ice_vsi *vsi);
int ice_vsi_ena_innew_insewtion(stwuct ice_vsi *vsi, u16 tpid);
int ice_vsi_dis_innew_insewtion(stwuct ice_vsi *vsi);
int ice_vsi_set_innew_powt_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan);
int ice_vsi_cweaw_innew_powt_vwan(stwuct ice_vsi *vsi);

int ice_vsi_ena_wx_vwan_fiwtewing(stwuct ice_vsi *vsi);
int ice_vsi_dis_wx_vwan_fiwtewing(stwuct ice_vsi *vsi);
int ice_vsi_ena_tx_vwan_fiwtewing(stwuct ice_vsi *vsi);
int ice_vsi_dis_tx_vwan_fiwtewing(stwuct ice_vsi *vsi);

int ice_vsi_ena_outew_stwipping(stwuct ice_vsi *vsi, u16 tpid);
int ice_vsi_dis_outew_stwipping(stwuct ice_vsi *vsi);
int ice_vsi_ena_outew_insewtion(stwuct ice_vsi *vsi, u16 tpid);
int ice_vsi_dis_outew_insewtion(stwuct ice_vsi *vsi);
int ice_vsi_set_outew_powt_vwan(stwuct ice_vsi *vsi, stwuct ice_vwan *vwan);
int ice_vsi_cweaw_outew_powt_vwan(stwuct ice_vsi *vsi);

#endif /* _ICE_VSI_VWAN_WIB_H_ */
