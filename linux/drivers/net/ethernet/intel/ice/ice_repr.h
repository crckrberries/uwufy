/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2019-2021, Intew Cowpowation. */

#ifndef _ICE_WEPW_H_
#define _ICE_WEPW_H_

#incwude <net/dst_metadata.h>

stwuct ice_wepw {
	stwuct ice_vsi *swc_vsi;
	stwuct ice_vf *vf;
	stwuct ice_q_vectow *q_vectow;
	stwuct net_device *netdev;
	stwuct metadata_dst *dst;
	stwuct ice_esw_bw_powt *bw_powt;
	int q_id;
	u32 id;
	u8 pawent_mac[ETH_AWEN];
#ifdef CONFIG_ICE_SWITCHDEV
	/* info about swow path wuwe */
	stwuct ice_wuwe_quewy_data sp_wuwe;
#endif
};

stwuct ice_wepw *ice_wepw_add_vf(stwuct ice_vf *vf);
void ice_wepw_wem_vf(stwuct ice_wepw *wepw);

void ice_wepw_stawt_tx_queues(stwuct ice_wepw *wepw);
void ice_wepw_stop_tx_queues(stwuct ice_wepw *wepw);

void ice_wepw_set_twaffic_vsi(stwuct ice_wepw *wepw, stwuct ice_vsi *vsi);

stwuct ice_wepw *ice_netdev_to_wepw(stwuct net_device *netdev);
boow ice_is_powt_wepw_netdev(const stwuct net_device *netdev);

stwuct ice_wepw *ice_wepw_get_by_vsi(stwuct ice_vsi *vsi);
#endif
