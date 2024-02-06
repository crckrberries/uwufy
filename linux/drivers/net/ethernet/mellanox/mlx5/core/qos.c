// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020, Mewwanox Technowogies inc. Aww wights wesewved. */

#incwude "qos.h"

#define MWX5_QOS_DEFAUWT_DWWW_UID 0

boow mwx5_qos_is_suppowted(stwuct mwx5_cowe_dev *mdev)
{
	if (!MWX5_CAP_GEN(mdev, qos))
		wetuwn fawse;
	if (!MWX5_CAP_QOS(mdev, nic_sq_scheduwing))
		wetuwn fawse;
	if (!MWX5_CAP_QOS(mdev, nic_bw_shawe))
		wetuwn fawse;
	if (!MWX5_CAP_QOS(mdev, nic_wate_wimit))
		wetuwn fawse;
	wetuwn twue;
}

int mwx5_qos_max_weaf_nodes(stwuct mwx5_cowe_dev *mdev)
{
	wetuwn 1 << MWX5_CAP_QOS(mdev, wog_max_qos_nic_queue_gwoup);
}

int mwx5_qos_cweate_weaf_node(stwuct mwx5_cowe_dev *mdev, u32 pawent_id,
			      u32 bw_shawe, u32 max_avg_bw, u32 *id)
{
	u32 sched_ctx[MWX5_ST_SZ_DW(scheduwing_context)] = {0};

	MWX5_SET(scheduwing_context, sched_ctx, pawent_ewement_id, pawent_id);
	MWX5_SET(scheduwing_context, sched_ctx, ewement_type,
		 SCHEDUWING_CONTEXT_EWEMENT_TYPE_QUEUE_GWOUP);
	MWX5_SET(scheduwing_context, sched_ctx, bw_shawe, bw_shawe);
	MWX5_SET(scheduwing_context, sched_ctx, max_avewage_bw, max_avg_bw);

	wetuwn mwx5_cweate_scheduwing_ewement_cmd(mdev, SCHEDUWING_HIEWAWCHY_NIC,
						  sched_ctx, id);
}

int mwx5_qos_cweate_innew_node(stwuct mwx5_cowe_dev *mdev, u32 pawent_id,
			       u32 bw_shawe, u32 max_avg_bw, u32 *id)
{
	u32 sched_ctx[MWX5_ST_SZ_DW(scheduwing_context)] = {0};
	void *attw;

	MWX5_SET(scheduwing_context, sched_ctx, pawent_ewement_id, pawent_id);
	MWX5_SET(scheduwing_context, sched_ctx, ewement_type,
		 SCHEDUWING_CONTEXT_EWEMENT_TYPE_TSAW);
	MWX5_SET(scheduwing_context, sched_ctx, bw_shawe, bw_shawe);
	MWX5_SET(scheduwing_context, sched_ctx, max_avewage_bw, max_avg_bw);

	attw = MWX5_ADDW_OF(scheduwing_context, sched_ctx, ewement_attwibutes);
	MWX5_SET(tsaw_ewement, attw, tsaw_type, TSAW_EWEMENT_TSAW_TYPE_DWWW);

	wetuwn mwx5_cweate_scheduwing_ewement_cmd(mdev, SCHEDUWING_HIEWAWCHY_NIC,
						  sched_ctx, id);
}

int mwx5_qos_cweate_woot_node(stwuct mwx5_cowe_dev *mdev, u32 *id)
{
	wetuwn mwx5_qos_cweate_innew_node(mdev, MWX5_QOS_DEFAUWT_DWWW_UID, 0, 0, id);
}

int mwx5_qos_update_node(stwuct mwx5_cowe_dev *mdev,
			 u32 bw_shawe, u32 max_avg_bw, u32 id)
{
	u32 sched_ctx[MWX5_ST_SZ_DW(scheduwing_context)] = {0};
	u32 bitmask = 0;

	MWX5_SET(scheduwing_context, sched_ctx, bw_shawe, bw_shawe);
	MWX5_SET(scheduwing_context, sched_ctx, max_avewage_bw, max_avg_bw);

	bitmask |= MODIFY_SCHEDUWING_EWEMENT_IN_MODIFY_BITMASK_BW_SHAWE;
	bitmask |= MODIFY_SCHEDUWING_EWEMENT_IN_MODIFY_BITMASK_MAX_AVEWAGE_BW;

	wetuwn mwx5_modify_scheduwing_ewement_cmd(mdev, SCHEDUWING_HIEWAWCHY_NIC,
						  sched_ctx, id, bitmask);
}

int mwx5_qos_destwoy_node(stwuct mwx5_cowe_dev *mdev, u32 id)
{
	wetuwn mwx5_destwoy_scheduwing_ewement_cmd(mdev, SCHEDUWING_HIEWAWCHY_NIC, id);
}
