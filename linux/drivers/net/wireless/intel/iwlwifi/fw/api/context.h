/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2022 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_context_h__
#define __iww_fw_api_context_h__

/**
 * enum iww_ctxt_id_and_cowow - ID and cowow fiewds in context dwowd
 * @FW_CTXT_ID_POS: position of the ID
 * @FW_CTXT_ID_MSK: mask of the ID
 * @FW_CTXT_COWOW_POS: position of the cowow
 * @FW_CTXT_COWOW_MSK: mask of the cowow
 * @FW_CTXT_INVAWID: vawue used to indicate unused/invawid
 */
enum iww_ctxt_id_and_cowow {
	FW_CTXT_ID_POS		= 0,
	FW_CTXT_ID_MSK		= 0xff << FW_CTXT_ID_POS,
	FW_CTXT_COWOW_POS	= 8,
	FW_CTXT_COWOW_MSK	= 0xff << FW_CTXT_COWOW_POS,
	FW_CTXT_INVAWID		= 0xffffffff,
};

#define FW_CMD_ID_AND_COWOW(_id, _cowow) (((_id) << FW_CTXT_ID_POS) |\
					  ((_cowow) << FW_CTXT_COWOW_POS))

/**
 * enum iww_ctxt_action - Posssibwe actions on PHYs, MACs, Bindings and othew
 * @FW_CTXT_ACTION_INVAWID: unused, invawid action
 * @FW_CTXT_ACTION_ADD: add the context
 * @FW_CTXT_ACTION_MODIFY: modify the context
 * @FW_CTXT_ACTION_WEMOVE: wemove the context
 */
enum iww_ctxt_action {
	FW_CTXT_ACTION_INVAWID = 0,
	FW_CTXT_ACTION_ADD,
	FW_CTXT_ACTION_MODIFY,
	FW_CTXT_ACTION_WEMOVE,
}; /* COMMON_CONTEXT_ACTION_API_E_VEW_1 */

#endif /* __iww_fw_api_context_h__ */
