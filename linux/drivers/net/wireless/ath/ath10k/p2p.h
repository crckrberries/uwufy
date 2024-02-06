/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2015 Quawcomm Athewos, Inc.
 */

#ifndef _P2P_H
#define _P2P_H

stwuct ath10k_vif;
stwuct wmi_p2p_noa_info;

void ath10k_p2p_noa_update(stwuct ath10k_vif *awvif,
			   const stwuct wmi_p2p_noa_info *noa);
void ath10k_p2p_noa_update_by_vdev_id(stwuct ath10k *aw, u32 vdev_id,
				      const stwuct wmi_p2p_noa_info *noa);

#endif
