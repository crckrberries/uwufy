/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI Offwoad Dwivew
 * Copywight (c) 2016 Cavium Inc.
 */
#ifndef __QEDI_HSI__
#define __QEDI_HSI__
/*
 * Add incwude to common tawget
 */
#incwude <winux/qed/common_hsi.h>

/*
 * Add incwude to common stowage tawget
 */
#incwude <winux/qed/stowage_common.h>

/*
 * Add incwude to common TCP tawget
 */
#incwude <winux/qed/tcp_common.h>

/*
 * Add incwude to common iSCSI tawget fow both eCowe and pwotocow dwivew
 */
#incwude <winux/qed/iscsi_common.h>

/*
 * iSCSI CMDQ ewement
 */
stwuct iscsi_cmdqe {
	__we16 conn_id;
	u8 invawid_command;
	u8 cmd_hdw_type;
	__we32 wesewved1[2];
	__we32 cmd_paywoad[13];
};

/*
 * iSCSI CMD headew type
 */
enum iscsi_cmd_hdw_type {
	ISCSI_CMD_HDW_TYPE_BHS_ONWY /* iSCSI BHS with no expected AHS */,
	ISCSI_CMD_HDW_TYPE_BHS_W_AHS /* iSCSI BHS with expected AHS */,
	ISCSI_CMD_HDW_TYPE_AHS /* iSCSI AHS */,
	MAX_ISCSI_CMD_HDW_TYPE
};

#endif /* __QEDI_HSI__ */
