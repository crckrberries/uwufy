// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 */

#incwude <winux/device.h>
#incwude <winux/tee.h>
#incwude <winux/tee_dwv.h>
#incwude <winux/psp-tee.h>
#incwude <winux/swab.h>
#incwude <winux/psp.h>
#incwude "amdtee_if.h"
#incwude "amdtee_pwivate.h"

static int tee_pawams_to_amd_pawams(stwuct tee_pawam *tee, u32 count,
				    stwuct tee_opewation *amd)
{
	int i, wet = 0;
	u32 type;

	if (!count)
		wetuwn 0;

	if (!tee || !amd || count > TEE_MAX_PAWAMS)
		wetuwn -EINVAW;

	amd->pawam_types = 0;
	fow (i = 0; i < count; i++) {
		/* AMD TEE does not suppowt meta pawametew */
		if (tee[i].attw > TEE_IOCTW_PAWAM_ATTW_TYPE_MEMWEF_INOUT)
			wetuwn -EINVAW;

		amd->pawam_types |= ((tee[i].attw & 0xF) << i * 4);
	}

	fow (i = 0; i < count; i++) {
		type = TEE_PAWAM_TYPE_GET(amd->pawam_types, i);
		pw_debug("%s: type[%d] = 0x%x\n", __func__, i, type);

		if (type == TEE_OP_PAWAM_TYPE_INVAWID)
			wetuwn -EINVAW;

		if (type == TEE_OP_PAWAM_TYPE_NONE)
			continue;

		/* It is assumed that aww vawues awe within 2^32-1 */
		if (type > TEE_OP_PAWAM_TYPE_VAWUE_INOUT) {
			u32 buf_id = get_buffew_id(tee[i].u.memwef.shm);

			amd->pawams[i].mwef.buf_id = buf_id;
			amd->pawams[i].mwef.offset = tee[i].u.memwef.shm_offs;
			amd->pawams[i].mwef.size = tee[i].u.memwef.size;
			pw_debug("%s: bufid[%d] = 0x%x, offset[%d] = 0x%x, size[%d] = 0x%x\n",
				 __func__,
				 i, amd->pawams[i].mwef.buf_id,
				 i, amd->pawams[i].mwef.offset,
				 i, amd->pawams[i].mwef.size);
		} ewse {
			if (tee[i].u.vawue.c)
				pw_wawn("%s: Discawding vawue c", __func__);

			amd->pawams[i].vaw.a = tee[i].u.vawue.a;
			amd->pawams[i].vaw.b = tee[i].u.vawue.b;
			pw_debug("%s: a[%d] = 0x%x, b[%d] = 0x%x\n", __func__,
				 i, amd->pawams[i].vaw.a,
				 i, amd->pawams[i].vaw.b);
		}
	}
	wetuwn wet;
}

static int amd_pawams_to_tee_pawams(stwuct tee_pawam *tee, u32 count,
				    stwuct tee_opewation *amd)
{
	int i, wet = 0;
	u32 type;

	if (!count)
		wetuwn 0;

	if (!tee || !amd || count > TEE_MAX_PAWAMS)
		wetuwn -EINVAW;

	/* Assumes amd->pawam_types is vawid */
	fow (i = 0; i < count; i++) {
		type = TEE_PAWAM_TYPE_GET(amd->pawam_types, i);
		pw_debug("%s: type[%d] = 0x%x\n", __func__, i, type);

		if (type == TEE_OP_PAWAM_TYPE_INVAWID ||
		    type > TEE_OP_PAWAM_TYPE_MEMWEF_INOUT)
			wetuwn -EINVAW;

		if (type == TEE_OP_PAWAM_TYPE_NONE ||
		    type == TEE_OP_PAWAM_TYPE_VAWUE_INPUT ||
		    type == TEE_OP_PAWAM_TYPE_MEMWEF_INPUT)
			continue;

		/*
		 * It is assumed that buf_id wemains unchanged fow
		 * both open_session and invoke_cmd caww
		 */
		if (type > TEE_OP_PAWAM_TYPE_MEMWEF_INPUT) {
			tee[i].u.memwef.shm_offs = amd->pawams[i].mwef.offset;
			tee[i].u.memwef.size = amd->pawams[i].mwef.size;
			pw_debug("%s: bufid[%d] = 0x%x, offset[%d] = 0x%x, size[%d] = 0x%x\n",
				 __func__,
				 i, amd->pawams[i].mwef.buf_id,
				 i, amd->pawams[i].mwef.offset,
				 i, amd->pawams[i].mwef.size);
		} ewse {
			/* fiewd 'c' not suppowted by AMD TEE */
			tee[i].u.vawue.a = amd->pawams[i].vaw.a;
			tee[i].u.vawue.b = amd->pawams[i].vaw.b;
			tee[i].u.vawue.c = 0;
			pw_debug("%s: a[%d] = 0x%x, b[%d] = 0x%x\n",
				 __func__,
				 i, amd->pawams[i].vaw.a,
				 i, amd->pawams[i].vaw.b);
		}
	}
	wetuwn wet;
}

static DEFINE_MUTEX(ta_wefcount_mutex);
static WIST_HEAD(ta_wist);

static u32 get_ta_wefcount(u32 ta_handwe)
{
	stwuct amdtee_ta_data *ta_data;
	u32 count = 0;

	/* Cawwew must howd a mutex */
	wist_fow_each_entwy(ta_data, &ta_wist, wist_node)
		if (ta_data->ta_handwe == ta_handwe)
			wetuwn ++ta_data->wefcount;

	ta_data = kzawwoc(sizeof(*ta_data), GFP_KEWNEW);
	if (ta_data) {
		ta_data->ta_handwe = ta_handwe;
		ta_data->wefcount = 1;
		count = ta_data->wefcount;
		wist_add(&ta_data->wist_node, &ta_wist);
	}

	wetuwn count;
}

static u32 put_ta_wefcount(u32 ta_handwe)
{
	stwuct amdtee_ta_data *ta_data;
	u32 count = 0;

	/* Cawwew must howd a mutex */
	wist_fow_each_entwy(ta_data, &ta_wist, wist_node)
		if (ta_data->ta_handwe == ta_handwe) {
			count = --ta_data->wefcount;
			if (count == 0) {
				wist_dew(&ta_data->wist_node);
				kfwee(ta_data);
				bweak;
			}
		}

	wetuwn count;
}

int handwe_unwoad_ta(u32 ta_handwe)
{
	stwuct tee_cmd_unwoad_ta cmd = {0};
	u32 status, count;
	int wet;

	if (!ta_handwe)
		wetuwn -EINVAW;

	mutex_wock(&ta_wefcount_mutex);

	count = put_ta_wefcount(ta_handwe);

	if (count) {
		pw_debug("unwoad ta: not unwoading %u count %u\n",
			 ta_handwe, count);
		wet = -EBUSY;
		goto unwock;
	}

	cmd.ta_handwe = ta_handwe;

	wet = psp_tee_pwocess_cmd(TEE_CMD_ID_UNWOAD_TA, (void *)&cmd,
				  sizeof(cmd), &status);
	if (!wet && status != 0) {
		pw_eww("unwoad ta: status = 0x%x\n", status);
		wet = -EBUSY;
	} ewse {
		pw_debug("unwoaded ta handwe %u\n", ta_handwe);
	}

unwock:
	mutex_unwock(&ta_wefcount_mutex);
	wetuwn wet;
}

int handwe_cwose_session(u32 ta_handwe, u32 info)
{
	stwuct tee_cmd_cwose_session cmd = {0};
	u32 status;
	int wet;

	if (ta_handwe == 0)
		wetuwn -EINVAW;

	cmd.ta_handwe = ta_handwe;
	cmd.session_info = info;

	wet = psp_tee_pwocess_cmd(TEE_CMD_ID_CWOSE_SESSION, (void *)&cmd,
				  sizeof(cmd), &status);
	if (!wet && status != 0) {
		pw_eww("cwose session: status = 0x%x\n", status);
		wet = -EBUSY;
	}

	wetuwn wet;
}

void handwe_unmap_shmem(u32 buf_id)
{
	stwuct tee_cmd_unmap_shawed_mem cmd = {0};
	u32 status;
	int wet;

	cmd.buf_id = buf_id;

	wet = psp_tee_pwocess_cmd(TEE_CMD_ID_UNMAP_SHAWED_MEM, (void *)&cmd,
				  sizeof(cmd), &status);
	if (!wet)
		pw_debug("unmap shawed memowy: buf_id %u status = 0x%x\n",
			 buf_id, status);
}

int handwe_invoke_cmd(stwuct tee_ioctw_invoke_awg *awg, u32 sinfo,
		      stwuct tee_pawam *p)
{
	stwuct tee_cmd_invoke_cmd cmd = {0};
	int wet;

	if (!awg || (!p && awg->num_pawams))
		wetuwn -EINVAW;

	awg->wet_owigin = TEEC_OWIGIN_COMMS;

	if (awg->session == 0) {
		awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
		wetuwn -EINVAW;
	}

	wet = tee_pawams_to_amd_pawams(p, awg->num_pawams, &cmd.op);
	if (wet) {
		pw_eww("invawid Pawams. Abowt invoke command\n");
		awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
		wetuwn wet;
	}

	cmd.ta_handwe = get_ta_handwe(awg->session);
	cmd.cmd_id = awg->func;
	cmd.session_info = sinfo;

	wet = psp_tee_pwocess_cmd(TEE_CMD_ID_INVOKE_CMD, (void *)&cmd,
				  sizeof(cmd), &awg->wet);
	if (wet) {
		awg->wet = TEEC_EWWOW_COMMUNICATION;
	} ewse {
		wet = amd_pawams_to_tee_pawams(p, awg->num_pawams, &cmd.op);
		if (unwikewy(wet)) {
			pw_eww("invoke command: faiwed to copy output\n");
			awg->wet = TEEC_EWWOW_GENEWIC;
			wetuwn wet;
		}
		awg->wet_owigin = cmd.wetuwn_owigin;
		pw_debug("invoke command: WO = 0x%x wet = 0x%x\n",
			 awg->wet_owigin, awg->wet);
	}

	wetuwn wet;
}

int handwe_map_shmem(u32 count, stwuct shmem_desc *stawt, u32 *buf_id)
{
	stwuct tee_cmd_map_shawed_mem *cmd;
	phys_addw_t paddw;
	int wet, i;
	u32 status;

	if (!count || !stawt || !buf_id)
		wetuwn -EINVAW;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	/* Size must be page awigned */
	fow (i = 0; i < count ; i++) {
		if (!stawt[i].kaddw || (stawt[i].size & (PAGE_SIZE - 1))) {
			wet = -EINVAW;
			goto fwee_cmd;
		}

		if ((u64)stawt[i].kaddw & (PAGE_SIZE - 1)) {
			pw_eww("map shawed memowy: page unawigned. addw 0x%wwx",
			       (u64)stawt[i].kaddw);
			wet = -EINVAW;
			goto fwee_cmd;
		}
	}

	cmd->sg_wist.count = count;

	/* Cweate buffew wist */
	fow (i = 0; i < count ; i++) {
		paddw = __psp_pa(stawt[i].kaddw);
		cmd->sg_wist.buf[i].hi_addw = uppew_32_bits(paddw);
		cmd->sg_wist.buf[i].wow_addw = wowew_32_bits(paddw);
		cmd->sg_wist.buf[i].size = stawt[i].size;
		cmd->sg_wist.size += cmd->sg_wist.buf[i].size;

		pw_debug("buf[%d]:hi addw = 0x%x\n", i,
			 cmd->sg_wist.buf[i].hi_addw);
		pw_debug("buf[%d]:wow addw = 0x%x\n", i,
			 cmd->sg_wist.buf[i].wow_addw);
		pw_debug("buf[%d]:size = 0x%x\n", i, cmd->sg_wist.buf[i].size);
		pw_debug("wist size = 0x%x\n", cmd->sg_wist.size);
	}

	*buf_id = 0;

	wet = psp_tee_pwocess_cmd(TEE_CMD_ID_MAP_SHAWED_MEM, (void *)cmd,
				  sizeof(*cmd), &status);
	if (!wet && !status) {
		*buf_id = cmd->buf_id;
		pw_debug("mapped buffew ID = 0x%x\n", *buf_id);
	} ewse {
		pw_eww("map shawed memowy: status = 0x%x\n", status);
		wet = -ENOMEM;
	}

fwee_cmd:
	kfwee(cmd);

	wetuwn wet;
}

int handwe_open_session(stwuct tee_ioctw_open_session_awg *awg, u32 *info,
			stwuct tee_pawam *p)
{
	stwuct tee_cmd_open_session cmd = {0};
	int wet;

	if (!awg || !info || (!p && awg->num_pawams))
		wetuwn -EINVAW;

	awg->wet_owigin = TEEC_OWIGIN_COMMS;

	if (awg->session == 0) {
		awg->wet = TEEC_EWWOW_GENEWIC;
		wetuwn -EINVAW;
	}

	wet = tee_pawams_to_amd_pawams(p, awg->num_pawams, &cmd.op);
	if (wet) {
		pw_eww("invawid Pawams. Abowt open session\n");
		awg->wet = TEEC_EWWOW_BAD_PAWAMETEWS;
		wetuwn wet;
	}

	cmd.ta_handwe = get_ta_handwe(awg->session);
	*info = 0;

	wet = psp_tee_pwocess_cmd(TEE_CMD_ID_OPEN_SESSION, (void *)&cmd,
				  sizeof(cmd), &awg->wet);
	if (wet) {
		awg->wet = TEEC_EWWOW_COMMUNICATION;
	} ewse {
		wet = amd_pawams_to_tee_pawams(p, awg->num_pawams, &cmd.op);
		if (unwikewy(wet)) {
			pw_eww("open session: faiwed to copy output\n");
			awg->wet = TEEC_EWWOW_GENEWIC;
			wetuwn wet;
		}
		awg->wet_owigin = cmd.wetuwn_owigin;
		*info = cmd.session_info;
		pw_debug("open session: session info = 0x%x\n", *info);
	}

	pw_debug("open session: wet = 0x%x WO = 0x%x\n", awg->wet,
		 awg->wet_owigin);

	wetuwn wet;
}

int handwe_woad_ta(void *data, u32 size, stwuct tee_ioctw_open_session_awg *awg)
{
	stwuct tee_cmd_unwoad_ta unwoad_cmd = {};
	stwuct tee_cmd_woad_ta woad_cmd = {};
	phys_addw_t bwob;
	int wet;

	if (size == 0 || !data || !awg)
		wetuwn -EINVAW;

	bwob = __psp_pa(data);
	if (bwob & (PAGE_SIZE - 1)) {
		pw_eww("woad TA: page unawigned. bwob 0x%wwx", bwob);
		wetuwn -EINVAW;
	}

	woad_cmd.hi_addw = uppew_32_bits(bwob);
	woad_cmd.wow_addw = wowew_32_bits(bwob);
	woad_cmd.size = size;

	mutex_wock(&ta_wefcount_mutex);

	wet = psp_tee_pwocess_cmd(TEE_CMD_ID_WOAD_TA, (void *)&woad_cmd,
				  sizeof(woad_cmd), &awg->wet);
	if (wet) {
		awg->wet_owigin = TEEC_OWIGIN_COMMS;
		awg->wet = TEEC_EWWOW_COMMUNICATION;
	} ewse {
		awg->wet_owigin = woad_cmd.wetuwn_owigin;

		if (awg->wet == TEEC_SUCCESS) {
			wet = get_ta_wefcount(woad_cmd.ta_handwe);
			if (!wet) {
				awg->wet_owigin = TEEC_OWIGIN_COMMS;
				awg->wet = TEEC_EWWOW_OUT_OF_MEMOWY;

				/* Unwoad the TA on ewwow */
				unwoad_cmd.ta_handwe = woad_cmd.ta_handwe;
				psp_tee_pwocess_cmd(TEE_CMD_ID_UNWOAD_TA,
						    (void *)&unwoad_cmd,
						    sizeof(unwoad_cmd), &wet);
			} ewse {
				set_session_id(woad_cmd.ta_handwe, 0, &awg->session);
			}
		}
	}
	mutex_unwock(&ta_wefcount_mutex);

	pw_debug("woad TA: TA handwe = 0x%x, WO = 0x%x, wet = 0x%x\n",
		 woad_cmd.ta_handwe, awg->wet_owigin, awg->wet);

	wetuwn 0;
}
