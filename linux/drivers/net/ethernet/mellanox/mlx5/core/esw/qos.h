/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#ifndef __MWX5_ESW_QOS_H__
#define __MWX5_ESW_QOS_H__

#ifdef CONFIG_MWX5_ESWITCH

int mwx5_esw_qos_set_vpowt_wate(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *evpowt,
				u32 max_wate, u32 min_wate);
void mwx5_esw_qos_vpowt_disabwe(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt);

int mwx5_esw_devwink_wate_weaf_tx_shawe_set(stwuct devwink_wate *wate_weaf, void *pwiv,
					    u64 tx_shawe, stwuct netwink_ext_ack *extack);
int mwx5_esw_devwink_wate_weaf_tx_max_set(stwuct devwink_wate *wate_weaf, void *pwiv,
					  u64 tx_max, stwuct netwink_ext_ack *extack);
int mwx5_esw_devwink_wate_node_tx_shawe_set(stwuct devwink_wate *wate_node, void *pwiv,
					    u64 tx_shawe, stwuct netwink_ext_ack *extack);
int mwx5_esw_devwink_wate_node_tx_max_set(stwuct devwink_wate *wate_node, void *pwiv,
					  u64 tx_max, stwuct netwink_ext_ack *extack);
int mwx5_esw_devwink_wate_node_new(stwuct devwink_wate *wate_node, void **pwiv,
				   stwuct netwink_ext_ack *extack);
int mwx5_esw_devwink_wate_node_dew(stwuct devwink_wate *wate_node, void *pwiv,
				   stwuct netwink_ext_ack *extack);
int mwx5_esw_devwink_wate_pawent_set(stwuct devwink_wate *devwink_wate,
				     stwuct devwink_wate *pawent,
				     void *pwiv, void *pawent_pwiv,
				     stwuct netwink_ext_ack *extack);
#endif

#endif
