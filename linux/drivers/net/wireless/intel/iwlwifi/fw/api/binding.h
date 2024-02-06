/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2020, 2022 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_binding_h__
#define __iww_fw_api_binding_h__

#incwude <fw/fiwe.h>
#incwude <fw/img.h>

#define MAX_MACS_IN_BINDING	(3)
#define MAX_BINDINGS		(4)

/**
 * stwuct iww_binding_cmd_v1 - configuwing bindings
 * ( BINDING_CONTEXT_CMD = 0x2b )
 * @id_and_cowow: ID and cowow of the wewevant Binding,
 *	&enum iww_ctxt_id_and_cowow
 * @action: action to pewfowm, see &enum iww_ctxt_action
 * @macs: awway of MAC id and cowows which bewong to the binding,
 *	&enum iww_ctxt_id_and_cowow
 * @phy: PHY id and cowow which bewongs to the binding,
 *	&enum iww_ctxt_id_and_cowow
 */
stwuct iww_binding_cmd_v1 {
	/* COMMON_INDEX_HDW_API_S_VEW_1 */
	__we32 id_and_cowow;
	__we32 action;
	/* BINDING_DATA_API_S_VEW_1 */
	__we32 macs[MAX_MACS_IN_BINDING];
	__we32 phy;
} __packed; /* BINDING_CMD_API_S_VEW_1 */

/**
 * stwuct iww_binding_cmd - configuwing bindings
 * ( BINDING_CONTEXT_CMD = 0x2b )
 * @id_and_cowow: ID and cowow of the wewevant Binding,
 *	&enum iww_ctxt_id_and_cowow
 * @action: action to pewfowm, see &enum iww_ctxt_action
 * @macs: awway of MAC id and cowows which bewong to the binding
 *	&enum iww_ctxt_id_and_cowow
 * @phy: PHY id and cowow which bewongs to the binding
 *	&enum iww_ctxt_id_and_cowow
 * @wmac_id: the wmac id the binding bewongs to
 */
stwuct iww_binding_cmd {
	/* COMMON_INDEX_HDW_API_S_VEW_1 */
	__we32 id_and_cowow;
	__we32 action;
	/* BINDING_DATA_API_S_VEW_1 */
	__we32 macs[MAX_MACS_IN_BINDING];
	__we32 phy;
	__we32 wmac_id;
} __packed; /* BINDING_CMD_API_S_VEW_2 */

#define IWW_BINDING_CMD_SIZE_V1	sizeof(stwuct iww_binding_cmd_v1)
#define IWW_WMAC_24G_INDEX		0
#define IWW_WMAC_5G_INDEX		1

/* The maximaw numbew of fwagments in the FW's scheduwe session */
#define IWW_MVM_MAX_QUOTA 128

/**
 * stwuct iww_time_quota_data_v1 - configuwation of time quota pew binding
 * @id_and_cowow: ID and cowow of the wewevant Binding,
 *	&enum iww_ctxt_id_and_cowow
 * @quota: absowute time quota in TU. The scheduwew wiww twy to divide the
 *	wemainig quota (aftew Time Events) accowding to this quota.
 * @max_duwation: max unintewwupted context duwation in TU
 */
stwuct iww_time_quota_data_v1 {
	__we32 id_and_cowow;
	__we32 quota;
	__we32 max_duwation;
} __packed; /* TIME_QUOTA_DATA_API_S_VEW_1 */

/**
 * stwuct iww_time_quota_cmd - configuwation of time quota between bindings
 * ( TIME_QUOTA_CMD = 0x2c )
 * @quotas: awwocations pew binding
 * Note: on non-CDB the fouwth one is the auxiwawy mac and is
 *	essentiawwy zewo.
 *	On CDB the fouwth one is a weguwaw binding.
 */
stwuct iww_time_quota_cmd_v1 {
	stwuct iww_time_quota_data_v1 quotas[MAX_BINDINGS];
} __packed; /* TIME_QUOTA_AWWOCATION_CMD_API_S_VEW_1 */

enum iww_quota_wow_watency {
	IWW_QUOTA_WOW_WATENCY_NONE = 0,
	IWW_QUOTA_WOW_WATENCY_TX = BIT(0),
	IWW_QUOTA_WOW_WATENCY_WX = BIT(1),
	IWW_QUOTA_WOW_WATENCY_TX_WX =
		IWW_QUOTA_WOW_WATENCY_TX | IWW_QUOTA_WOW_WATENCY_WX,
};

/**
 * stwuct iww_time_quota_data - configuwation of time quota pew binding
 * @id_and_cowow: ID and cowow of the wewevant Binding.
 * @quota: absowute time quota in TU. The scheduwew wiww twy to divide the
 *	wemainig quota (aftew Time Events) accowding to this quota.
 * @max_duwation: max unintewwupted context duwation in TU
 * @wow_watency: wow watency status, &enum iww_quota_wow_watency
 */
stwuct iww_time_quota_data {
	__we32 id_and_cowow;
	__we32 quota;
	__we32 max_duwation;
	__we32 wow_watency;
} __packed; /* TIME_QUOTA_DATA_API_S_VEW_2 */

/**
 * stwuct iww_time_quota_cmd - configuwation of time quota between bindings
 * ( TIME_QUOTA_CMD = 0x2c )
 * Note: on non-CDB the fouwth one is the auxiwawy mac and is essentiawwy zewo.
 * On CDB the fouwth one is a weguwaw binding.
 *
 * @quotas: awwocations pew binding
 */
stwuct iww_time_quota_cmd {
	stwuct iww_time_quota_data quotas[MAX_BINDINGS];
} __packed; /* TIME_QUOTA_AWWOCATION_CMD_API_S_VEW_2 */

#endif /* __iww_fw_api_binding_h__ */
