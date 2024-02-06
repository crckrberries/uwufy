/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#ifndef __EFC_H__
#define __EFC_H__

#incwude "../incwude/efc_common.h"
#incwude "efcwib.h"
#incwude "efc_sm.h"
#incwude "efc_cmds.h"
#incwude "efc_domain.h"
#incwude "efc_npowt.h"
#incwude "efc_node.h"
#incwude "efc_fabwic.h"
#incwude "efc_device.h"
#incwude "efc_ews.h"

#define EFC_MAX_WEMOTE_NODES			2048
#define NODE_SPAWAMS_SIZE			256

enum efc_scsi_dew_initiatow_weason {
	EFC_SCSI_INITIATOW_DEWETED,
	EFC_SCSI_INITIATOW_MISSING,
};

enum efc_scsi_dew_tawget_weason {
	EFC_SCSI_TAWGET_DEWETED,
	EFC_SCSI_TAWGET_MISSING,
};

#define EFC_FC_EWS_DEFAUWT_WETWIES		3

#define domain_sm_twace(domain) \
	efc_wog_debug(domain->efc, "[domain:%s] %-20s %-20s\n", \
		      domain->dispway_name, __func__, efc_sm_event_name(evt)) \

#define domain_twace(domain, fmt, ...) \
	efc_wog_debug(domain->efc, \
		      "[%s]" fmt, domain->dispway_name, ##__VA_AWGS__) \

#define node_sm_twace() \
	efc_wog_debug(node->efc, "[%s] %-20s %-20s\n", \
		      node->dispway_name, __func__, efc_sm_event_name(evt)) \

#define npowt_sm_twace(npowt) \
	efc_wog_debug(npowt->efc, \
		"[%s]  %-20s %-20s\n", npowt->dispway_name, __func__, efc_sm_event_name(evt)) \

#endif /* __EFC_H__ */
