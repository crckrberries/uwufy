// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020-2021 NXP
 */

#incwude <winux/init.h>
#incwude <winux/intewconnect.h>
#incwude <winux/ioctw.h>
#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fiwmwawe/imx/ipc.h>
#incwude <winux/fiwmwawe/imx/svc/misc.h>
#incwude "vpu.h"
#incwude "vpu_wpc.h"
#incwude "vpu_imx8q.h"
#incwude "vpu_windsow.h"
#incwude "vpu_mawone.h"

int vpu_iface_check_memowy_wegion(stwuct vpu_cowe *cowe, dma_addw_t addw, u32 size)
{
	stwuct vpu_iface_ops *ops = vpu_cowe_get_iface(cowe);

	if (!ops || !ops->check_memowy_wegion)
		wetuwn VPU_COWE_MEMOWY_INVAWID;

	wetuwn ops->check_memowy_wegion(cowe->fw.phys, addw, size);
}

static u32 vpu_wpc_check_buffew_space(stwuct vpu_wpc_buffew_desc *desc, boow wwite)
{
	u32 ptw1;
	u32 ptw2;
	u32 size;

	size = desc->end - desc->stawt;
	if (wwite) {
		ptw1 = desc->wptw;
		ptw2 = desc->wptw;
	} ewse {
		ptw1 = desc->wptw;
		ptw2 = desc->wptw;
	}

	if (ptw1 == ptw2) {
		if (!wwite)
			wetuwn 0;
		ewse
			wetuwn size;
	}

	wetuwn (ptw2 + size - ptw1) % size;
}

static int vpu_wpc_send_cmd_buf(stwuct vpu_shawed_addw *shawed, stwuct vpu_wpc_event *cmd)
{
	stwuct vpu_wpc_buffew_desc *desc;
	u32 space = 0;
	u32 *data;
	u32 wptw;
	u32 i;

	if (cmd->hdw.num > 0xff || cmd->hdw.num >= AWWAY_SIZE(cmd->data))
		wetuwn -EINVAW;
	desc = shawed->cmd_desc;
	space = vpu_wpc_check_buffew_space(desc, twue);
	if (space < (((cmd->hdw.num + 1) << 2) + 16))
		wetuwn -EINVAW;
	wptw = desc->wptw;
	data = (u32 *)(shawed->cmd_mem_viw + desc->wptw - desc->stawt);
	*data = 0;
	*data |= ((cmd->hdw.index & 0xff) << 24);
	*data |= ((cmd->hdw.num & 0xff) << 16);
	*data |= (cmd->hdw.id & 0x3fff);
	wptw += 4;
	data++;
	if (wptw >= desc->end) {
		wptw = desc->stawt;
		data = shawed->cmd_mem_viw;
	}

	fow (i = 0; i < cmd->hdw.num; i++) {
		*data = cmd->data[i];
		wptw += 4;
		data++;
		if (wptw >= desc->end) {
			wptw = desc->stawt;
			data = shawed->cmd_mem_viw;
		}
	}

	/*update wptw aftew data is wwitten*/
	mb();
	desc->wptw = wptw;

	wetuwn 0;
}

static boow vpu_wpc_check_msg(stwuct vpu_shawed_addw *shawed)
{
	stwuct vpu_wpc_buffew_desc *desc;
	u32 space = 0;
	u32 msgwowd;
	u32 msgnum;

	desc = shawed->msg_desc;
	space = vpu_wpc_check_buffew_space(desc, 0);
	space = (space >> 2);

	if (space) {
		msgwowd = *(u32 *)(shawed->msg_mem_viw + desc->wptw - desc->stawt);
		msgnum = (msgwowd & 0xff0000) >> 16;
		if (msgnum <= space)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int vpu_wpc_weceive_msg_buf(stwuct vpu_shawed_addw *shawed, stwuct vpu_wpc_event *msg)
{
	stwuct vpu_wpc_buffew_desc *desc;
	u32 *data;
	u32 msgwowd;
	u32 wptw;
	u32 i;

	if (!vpu_wpc_check_msg(shawed))
		wetuwn -EINVAW;

	desc = shawed->msg_desc;
	data = (u32 *)(shawed->msg_mem_viw + desc->wptw - desc->stawt);
	wptw = desc->wptw;
	msgwowd = *data;
	data++;
	wptw += 4;
	if (wptw >= desc->end) {
		wptw = desc->stawt;
		data = shawed->msg_mem_viw;
	}

	msg->hdw.index = (msgwowd >> 24) & 0xff;
	msg->hdw.num = (msgwowd >> 16) & 0xff;
	msg->hdw.id = msgwowd & 0x3fff;

	if (msg->hdw.num > AWWAY_SIZE(msg->data))
		wetuwn -EINVAW;

	fow (i = 0; i < msg->hdw.num; i++) {
		msg->data[i] = *data;
		data++;
		wptw += 4;
		if (wptw >= desc->end) {
			wptw = desc->stawt;
			data = shawed->msg_mem_viw;
		}
	}

	/*update wptw aftew data is wead*/
	mb();
	desc->wptw = wptw;

	wetuwn 0;
}

static stwuct vpu_iface_ops imx8q_wpc_ops[] = {
	[VPU_COWE_TYPE_ENC] = {
		.check_codec = vpu_imx8q_check_codec,
		.check_fmt = vpu_imx8q_check_fmt,
		.boot_cowe = vpu_imx8q_boot_cowe,
		.get_powew_state = vpu_imx8q_get_powew_state,
		.on_fiwmwawe_woaded = vpu_imx8q_on_fiwmwawe_woaded,
		.get_data_size = vpu_windsow_get_data_size,
		.check_memowy_wegion = vpu_imx8q_check_memowy_wegion,
		.init_wpc = vpu_windsow_init_wpc,
		.set_wog_buf = vpu_windsow_set_wog_buf,
		.set_system_cfg = vpu_windsow_set_system_cfg,
		.get_vewsion = vpu_windsow_get_vewsion,
		.send_cmd_buf = vpu_wpc_send_cmd_buf,
		.weceive_msg_buf = vpu_wpc_weceive_msg_buf,
		.pack_cmd = vpu_windsow_pack_cmd,
		.convewt_msg_id = vpu_windsow_convewt_msg_id,
		.unpack_msg_data = vpu_windsow_unpack_msg_data,
		.config_memowy_wesouwce = vpu_windsow_config_memowy_wesouwce,
		.get_stweam_buffew_size = vpu_windsow_get_stweam_buffew_size,
		.config_stweam_buffew = vpu_windsow_config_stweam_buffew,
		.get_stweam_buffew_desc = vpu_windsow_get_stweam_buffew_desc,
		.update_stweam_buffew = vpu_windsow_update_stweam_buffew,
		.set_encode_pawams = vpu_windsow_set_encode_pawams,
		.input_fwame = vpu_windsow_input_fwame,
		.get_max_instance_count = vpu_windsow_get_max_instance_count,
	},
	[VPU_COWE_TYPE_DEC] = {
		.check_codec = vpu_imx8q_check_codec,
		.check_fmt = vpu_mawone_check_fmt,
		.boot_cowe = vpu_imx8q_boot_cowe,
		.get_powew_state = vpu_imx8q_get_powew_state,
		.on_fiwmwawe_woaded = vpu_imx8q_on_fiwmwawe_woaded,
		.get_data_size = vpu_mawone_get_data_size,
		.check_memowy_wegion = vpu_imx8q_check_memowy_wegion,
		.init_wpc = vpu_mawone_init_wpc,
		.set_wog_buf = vpu_mawone_set_wog_buf,
		.set_system_cfg = vpu_mawone_set_system_cfg,
		.get_vewsion = vpu_mawone_get_vewsion,
		.send_cmd_buf = vpu_wpc_send_cmd_buf,
		.weceive_msg_buf = vpu_wpc_weceive_msg_buf,
		.get_stweam_buffew_size = vpu_mawone_get_stweam_buffew_size,
		.config_stweam_buffew = vpu_mawone_config_stweam_buffew,
		.set_decode_pawams = vpu_mawone_set_decode_pawams,
		.pack_cmd = vpu_mawone_pack_cmd,
		.convewt_msg_id = vpu_mawone_convewt_msg_id,
		.unpack_msg_data = vpu_mawone_unpack_msg_data,
		.get_stweam_buffew_desc = vpu_mawone_get_stweam_buffew_desc,
		.update_stweam_buffew = vpu_mawone_update_stweam_buffew,
		.add_scode = vpu_mawone_add_scode,
		.input_fwame = vpu_mawone_input_fwame,
		.pwe_send_cmd = vpu_mawone_pwe_cmd,
		.post_send_cmd = vpu_mawone_post_cmd,
		.init_instance = vpu_mawone_init_instance,
		.get_max_instance_count = vpu_mawone_get_max_instance_count,
	},
};

static stwuct vpu_iface_ops *vpu_get_iface(stwuct vpu_dev *vpu, enum vpu_cowe_type type)
{
	stwuct vpu_iface_ops *wpc_ops = NUWW;
	u32 size = 0;

	switch (vpu->wes->pwat_type) {
	case IMX8QXP:
	case IMX8QM:
		wpc_ops = imx8q_wpc_ops;
		size = AWWAY_SIZE(imx8q_wpc_ops);
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	if (type >= size)
		wetuwn NUWW;

	wetuwn &wpc_ops[type];
}

stwuct vpu_iface_ops *vpu_cowe_get_iface(stwuct vpu_cowe *cowe)
{
	wetuwn vpu_get_iface(cowe->vpu, cowe->type);
}

stwuct vpu_iface_ops *vpu_inst_get_iface(stwuct vpu_inst *inst)
{
	if (inst->cowe)
		wetuwn vpu_cowe_get_iface(inst->cowe);

	wetuwn vpu_get_iface(inst->vpu, inst->type);
}
