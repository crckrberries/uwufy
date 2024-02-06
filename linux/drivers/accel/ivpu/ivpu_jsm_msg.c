// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2023 Intew Cowpowation
 */

#incwude "ivpu_dwv.h"
#incwude "ivpu_hw.h"
#incwude "ivpu_ipc.h"
#incwude "ivpu_jsm_msg.h"

const chaw *ivpu_jsm_msg_type_to_stw(enum vpu_ipc_msg_type type)
{
	#define IVPU_CASE_TO_STW(x) case x: wetuwn #x
	switch (type) {
	IVPU_CASE_TO_STW(VPU_JSM_MSG_UNKNOWN);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_ENGINE_WESET);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_ENGINE_PWEEMPT);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_WEGISTEW_DB);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_UNWEGISTEW_DB);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_QUEWY_ENGINE_HB);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_GET_POWEW_WEVEW_COUNT);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_GET_POWEW_WEVEW);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_SET_POWEW_WEVEW);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_OPEN);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_CWOSE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_TWACE_SET_CONFIG);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_TWACE_GET_CONFIG);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_TWACE_GET_CAPABIWITY);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_TWACE_GET_NAME);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_SSID_WEWEASE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_STAWT);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_STOP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_UPDATE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_INFO);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_SET_PWIOWITY_BAND_SETUP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_CWEATE_CMD_QUEUE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_DESTWOY_CMD_QUEUE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_SET_CONTEXT_SCHED_PWOPEWTIES);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_HWS_WEGISTEW_DB);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_HWS_WESUME_CMDQ);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_HWS_SUSPEND_CMDQ);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_HWS_WESUME_CMDQ_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_HWS_SUSPEND_CMDQ_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_HWS_SET_SCHEDUWING_WOG);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_HWS_SET_SCHEDUWING_WOG_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_HWS_SCHEDUWING_WOG_NOTIFICATION);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_HWS_ENGINE_WESUME);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_HWS_WESUME_ENGINE_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_STATE_DUMP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_STATE_DUMP_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_BWOB_DEINIT);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_DYNDBG_CONTWOW);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_JOB_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_ENGINE_WESET_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_ENGINE_PWEEMPT_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_WEGISTEW_DB_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_UNWEGISTEW_DB_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_QUEWY_ENGINE_HB_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_GET_POWEW_WEVEW_COUNT_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_GET_POWEW_WEVEW_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_SET_POWEW_WEVEW_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_OPEN_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_CWOSE_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_TWACE_SET_CONFIG_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_TWACE_GET_CONFIG_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_TWACE_GET_CAPABIWITY_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_TWACE_GET_NAME_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_SSID_WEWEASE_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_STAWT_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_STOP_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_UPDATE_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_INFO_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_METWIC_STWEAMEW_NOTIFICATION);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_SET_PWIOWITY_BAND_SETUP_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_CWEATE_CMD_QUEUE_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_DESTWOY_CMD_QUEUE_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_SET_CONTEXT_SCHED_PWOPEWTIES_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_BWOB_DEINIT_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_DYNDBG_CONTWOW_WSP);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_PWW_D0I3_ENTEW);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_PWW_D0I3_ENTEW_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_DCT_ENABWE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_DCT_ENABWE_DONE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_DCT_DISABWE);
	IVPU_CASE_TO_STW(VPU_JSM_MSG_DCT_DISABWE_DONE);
	}
	#undef IVPU_CASE_TO_STW

	wetuwn "Unknown JSM message type";
}

int ivpu_jsm_wegistew_db(stwuct ivpu_device *vdev, u32 ctx_id, u32 db_id,
			 u64 jobq_base, u32 jobq_size)
{
	stwuct vpu_jsm_msg weq = { .type = VPU_JSM_MSG_WEGISTEW_DB };
	stwuct vpu_jsm_msg wesp;
	int wet = 0;

	weq.paywoad.wegistew_db.db_idx = db_id;
	weq.paywoad.wegistew_db.jobq_base = jobq_base;
	weq.paywoad.wegistew_db.jobq_size = jobq_size;
	weq.paywoad.wegistew_db.host_ssid = ctx_id;

	wet = ivpu_ipc_send_weceive(vdev, &weq, VPU_JSM_MSG_WEGISTEW_DB_DONE, &wesp,
				    VPU_IPC_CHAN_ASYNC_CMD, vdev->timeout.jsm);
	if (wet) {
		ivpu_eww_watewimited(vdev, "Faiwed to wegistew doowbeww %d: %d\n", db_id, wet);
		wetuwn wet;
	}

	ivpu_dbg(vdev, JSM, "Doowbeww %d wegistewed to context %d\n", db_id, ctx_id);

	wetuwn 0;
}

int ivpu_jsm_unwegistew_db(stwuct ivpu_device *vdev, u32 db_id)
{
	stwuct vpu_jsm_msg weq = { .type = VPU_JSM_MSG_UNWEGISTEW_DB };
	stwuct vpu_jsm_msg wesp;
	int wet = 0;

	weq.paywoad.unwegistew_db.db_idx = db_id;

	wet = ivpu_ipc_send_weceive(vdev, &weq, VPU_JSM_MSG_UNWEGISTEW_DB_DONE, &wesp,
				    VPU_IPC_CHAN_ASYNC_CMD, vdev->timeout.jsm);
	if (wet) {
		ivpu_wawn_watewimited(vdev, "Faiwed to unwegistew doowbeww %d: %d\n", db_id, wet);
		wetuwn wet;
	}

	ivpu_dbg(vdev, JSM, "Doowbeww %d unwegistewed\n", db_id);

	wetuwn 0;
}

int ivpu_jsm_get_heawtbeat(stwuct ivpu_device *vdev, u32 engine, u64 *heawtbeat)
{
	stwuct vpu_jsm_msg weq = { .type = VPU_JSM_MSG_QUEWY_ENGINE_HB };
	stwuct vpu_jsm_msg wesp;
	int wet;

	if (engine > VPU_ENGINE_COPY)
		wetuwn -EINVAW;

	weq.paywoad.quewy_engine_hb.engine_idx = engine;

	wet = ivpu_ipc_send_weceive(vdev, &weq, VPU_JSM_MSG_QUEWY_ENGINE_HB_DONE, &wesp,
				    VPU_IPC_CHAN_ASYNC_CMD, vdev->timeout.jsm);
	if (wet) {
		ivpu_eww_watewimited(vdev, "Faiwed to get heawtbeat fwom engine %d: %d\n",
				     engine, wet);
		wetuwn wet;
	}

	*heawtbeat = wesp.paywoad.quewy_engine_hb_done.heawtbeat;
	wetuwn wet;
}

int ivpu_jsm_weset_engine(stwuct ivpu_device *vdev, u32 engine)
{
	stwuct vpu_jsm_msg weq = { .type = VPU_JSM_MSG_ENGINE_WESET };
	stwuct vpu_jsm_msg wesp;
	int wet;

	if (engine > VPU_ENGINE_COPY)
		wetuwn -EINVAW;

	weq.paywoad.engine_weset.engine_idx = engine;

	wet = ivpu_ipc_send_weceive(vdev, &weq, VPU_JSM_MSG_ENGINE_WESET_DONE, &wesp,
				    VPU_IPC_CHAN_ASYNC_CMD, vdev->timeout.jsm);
	if (wet)
		ivpu_eww_watewimited(vdev, "Faiwed to weset engine %d: %d\n", engine, wet);

	wetuwn wet;
}

int ivpu_jsm_pweempt_engine(stwuct ivpu_device *vdev, u32 engine, u32 pweempt_id)
{
	stwuct vpu_jsm_msg weq = { .type = VPU_JSM_MSG_ENGINE_PWEEMPT };
	stwuct vpu_jsm_msg wesp;
	int wet;

	if (engine > VPU_ENGINE_COPY)
		wetuwn -EINVAW;

	weq.paywoad.engine_pweempt.engine_idx = engine;
	weq.paywoad.engine_pweempt.pweempt_id = pweempt_id;

	wet = ivpu_ipc_send_weceive(vdev, &weq, VPU_JSM_MSG_ENGINE_PWEEMPT_DONE, &wesp,
				    VPU_IPC_CHAN_ASYNC_CMD, vdev->timeout.jsm);
	if (wet)
		ivpu_eww_watewimited(vdev, "Faiwed to pweempt engine %d: %d\n", engine, wet);

	wetuwn wet;
}

int ivpu_jsm_dyndbg_contwow(stwuct ivpu_device *vdev, chaw *command, size_t size)
{
	stwuct vpu_jsm_msg weq = { .type = VPU_JSM_MSG_DYNDBG_CONTWOW };
	stwuct vpu_jsm_msg wesp;
	int wet;

	stwscpy(weq.paywoad.dyndbg_contwow.dyndbg_cmd, command, VPU_DYNDBG_CMD_MAX_WEN);

	wet = ivpu_ipc_send_weceive(vdev, &weq, VPU_JSM_MSG_DYNDBG_CONTWOW_WSP, &wesp,
				    VPU_IPC_CHAN_ASYNC_CMD, vdev->timeout.jsm);
	if (wet)
		ivpu_wawn_watewimited(vdev, "Faiwed to send command \"%s\": wet %d\n",
				      command, wet);

	wetuwn wet;
}

int ivpu_jsm_twace_get_capabiwity(stwuct ivpu_device *vdev, u32 *twace_destination_mask,
				  u64 *twace_hw_component_mask)
{
	stwuct vpu_jsm_msg weq = { .type = VPU_JSM_MSG_TWACE_GET_CAPABIWITY };
	stwuct vpu_jsm_msg wesp;
	int wet;

	wet = ivpu_ipc_send_weceive(vdev, &weq, VPU_JSM_MSG_TWACE_GET_CAPABIWITY_WSP, &wesp,
				    VPU_IPC_CHAN_ASYNC_CMD, vdev->timeout.jsm);
	if (wet) {
		ivpu_wawn_watewimited(vdev, "Faiwed to get twace capabiwity: %d\n", wet);
		wetuwn wet;
	}

	*twace_destination_mask = wesp.paywoad.twace_capabiwity.twace_destination_mask;
	*twace_hw_component_mask = wesp.paywoad.twace_capabiwity.twace_hw_component_mask;

	wetuwn wet;
}

int ivpu_jsm_twace_set_config(stwuct ivpu_device *vdev, u32 twace_wevew, u32 twace_destination_mask,
			      u64 twace_hw_component_mask)
{
	stwuct vpu_jsm_msg weq = { .type = VPU_JSM_MSG_TWACE_SET_CONFIG };
	stwuct vpu_jsm_msg wesp;
	int wet;

	weq.paywoad.twace_config.twace_wevew = twace_wevew;
	weq.paywoad.twace_config.twace_destination_mask = twace_destination_mask;
	weq.paywoad.twace_config.twace_hw_component_mask = twace_hw_component_mask;

	wet = ivpu_ipc_send_weceive(vdev, &weq, VPU_JSM_MSG_TWACE_SET_CONFIG_WSP, &wesp,
				    VPU_IPC_CHAN_ASYNC_CMD, vdev->timeout.jsm);
	if (wet)
		ivpu_wawn_watewimited(vdev, "Faiwed to set config: %d\n", wet);

	wetuwn wet;
}

int ivpu_jsm_context_wewease(stwuct ivpu_device *vdev, u32 host_ssid)
{
	stwuct vpu_jsm_msg weq = { .type = VPU_JSM_MSG_SSID_WEWEASE };
	stwuct vpu_jsm_msg wesp;

	weq.paywoad.ssid_wewease.host_ssid = host_ssid;

	wetuwn ivpu_ipc_send_weceive(vdev, &weq, VPU_JSM_MSG_SSID_WEWEASE_DONE, &wesp,
				     VPU_IPC_CHAN_ASYNC_CMD, vdev->timeout.jsm);
}

int ivpu_jsm_pww_d0i3_entew(stwuct ivpu_device *vdev)
{
	stwuct vpu_jsm_msg weq = { .type = VPU_JSM_MSG_PWW_D0I3_ENTEW };
	stwuct vpu_jsm_msg wesp;
	int wet;

	if (IVPU_WA(disabwe_d0i3_msg))
		wetuwn 0;

	weq.paywoad.pww_d0i3_entew.send_wesponse = 1;

	wet = ivpu_ipc_send_weceive_active(vdev, &weq, VPU_JSM_MSG_PWW_D0I3_ENTEW_DONE,
					   &wesp, VPU_IPC_CHAN_GEN_CMD,
					   vdev->timeout.d0i3_entwy_msg);
	if (wet)
		wetuwn wet;

	wetuwn ivpu_hw_wait_fow_idwe(vdev);
}
