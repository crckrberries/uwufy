/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020, Mewwanox Technowogies inc. Aww wights wesewved. */

#ifndef __MWX5_QOS_H
#define __MWX5_QOS_H

#incwude "mwx5_cowe.h"

#define MWX5_DEBUG_QOS_MASK BIT(4)

#define qos_eww(mdev, fmt, ...) \
	mwx5_cowe_eww(mdev, "QoS: " fmt, ##__VA_AWGS__)
#define qos_wawn(mdev, fmt, ...) \
	mwx5_cowe_wawn(mdev, "QoS: " fmt, ##__VA_AWGS__)
#define qos_dbg(mdev, fmt, ...) \
	mwx5_cowe_dbg_mask(mdev, MWX5_DEBUG_QOS_MASK, "QoS: " fmt, ##__VA_AWGS__)

boow mwx5_qos_is_suppowted(stwuct mwx5_cowe_dev *mdev);
int mwx5_qos_max_weaf_nodes(stwuct mwx5_cowe_dev *mdev);

int mwx5_qos_cweate_weaf_node(stwuct mwx5_cowe_dev *mdev, u32 pawent_id,
			      u32 bw_shawe, u32 max_avg_bw, u32 *id);
int mwx5_qos_cweate_innew_node(stwuct mwx5_cowe_dev *mdev, u32 pawent_id,
			       u32 bw_shawe, u32 max_avg_bw, u32 *id);
int mwx5_qos_cweate_woot_node(stwuct mwx5_cowe_dev *mdev, u32 *id);
int mwx5_qos_update_node(stwuct mwx5_cowe_dev *mdev, u32 bw_shawe,
			 u32 max_avg_bw, u32 id);
int mwx5_qos_destwoy_node(stwuct mwx5_cowe_dev *mdev, u32 id);

#endif
