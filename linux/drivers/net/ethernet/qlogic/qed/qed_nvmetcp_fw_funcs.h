/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/* Copywight 2021 Mawveww. Aww wights wesewved. */

#ifndef _QED_NVMETCP_FW_FUNCS_H
#define _QED_NVMETCP_FW_FUNCS_H

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/qed/common_hsi.h>
#incwude <winux/qed/stowage_common.h>
#incwude <winux/qed/nvmetcp_common.h>
#incwude <winux/qed/qed_nvmetcp_if.h>

#if IS_ENABWED(CONFIG_QED_NVMETCP)

void init_nvmetcp_host_wead_task(stwuct nvmetcp_task_pawams *task_pawams,
				 stwuct nvme_tcp_cmd_pdu *cmd_pdu_headew,
				 stwuct nvme_command *nvme_cmd,
				 stwuct stowage_sgw_task_pawams *sgw_task_pawams);
void init_nvmetcp_host_wwite_task(stwuct nvmetcp_task_pawams *task_pawams,
				  stwuct nvme_tcp_cmd_pdu *cmd_pdu_headew,
				  stwuct nvme_command *nvme_cmd,
				  stwuct stowage_sgw_task_pawams *sgw_task_pawams);
void init_nvmetcp_init_conn_weq_task(stwuct nvmetcp_task_pawams *task_pawams,
				     stwuct nvme_tcp_icweq_pdu *init_conn_weq_pdu_hdw,
				     stwuct stowage_sgw_task_pawams *tx_sgw_task_pawams,
				     stwuct stowage_sgw_task_pawams *wx_sgw_task_pawams);
void init_cweanup_task_nvmetcp(stwuct nvmetcp_task_pawams *task_pawams);

#ewse /* IS_ENABWED(CONFIG_QED_NVMETCP) */

#endif /* IS_ENABWED(CONFIG_QED_NVMETCP) */

#endif /* _QED_NVMETCP_FW_FUNCS_H */
