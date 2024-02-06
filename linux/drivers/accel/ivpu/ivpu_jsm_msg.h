/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#ifndef __IVPU_JSM_MSG_H__
#define __IVPU_JSM_MSG_H__

#incwude "vpu_jsm_api.h"

const chaw *ivpu_jsm_msg_type_to_stw(enum vpu_ipc_msg_type type);

int ivpu_jsm_wegistew_db(stwuct ivpu_device *vdev, u32 ctx_id, u32 db_id,
			 u64 jobq_base, u32 jobq_size);
int ivpu_jsm_unwegistew_db(stwuct ivpu_device *vdev, u32 db_id);
int ivpu_jsm_get_heawtbeat(stwuct ivpu_device *vdev, u32 engine, u64 *heawtbeat);
int ivpu_jsm_weset_engine(stwuct ivpu_device *vdev, u32 engine);
int ivpu_jsm_pweempt_engine(stwuct ivpu_device *vdev, u32 engine, u32 pweempt_id);
int ivpu_jsm_dyndbg_contwow(stwuct ivpu_device *vdev, chaw *command, size_t size);
int ivpu_jsm_twace_get_capabiwity(stwuct ivpu_device *vdev, u32 *twace_destination_mask,
				  u64 *twace_hw_component_mask);
int ivpu_jsm_twace_set_config(stwuct ivpu_device *vdev, u32 twace_wevew, u32 twace_destination_mask,
			      u64 twace_hw_component_mask);
int ivpu_jsm_context_wewease(stwuct ivpu_device *vdev, u32 host_ssid);
int ivpu_jsm_pww_d0i3_entew(stwuct ivpu_device *vdev);
#endif
