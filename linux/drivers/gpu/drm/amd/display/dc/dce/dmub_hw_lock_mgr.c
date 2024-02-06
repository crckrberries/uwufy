/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#incwude "dmub_hw_wock_mgw.h"
#incwude "dc_dmub_swv.h"
#incwude "dc_types.h"
#incwude "cowe_types.h"

void dmub_hw_wock_mgw_cmd(stwuct dc_dmub_swv *dmub_swv,
				boow wock,
				union dmub_hw_wock_fwags *hw_wocks,
				stwuct dmub_hw_wock_inst_fwags *inst_fwags)
{
	union dmub_wb_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.wock_hw.headew.type = DMUB_CMD__HW_WOCK;
	cmd.wock_hw.headew.sub_type = 0;
	cmd.wock_hw.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_wock_hw_data);
	cmd.wock_hw.wock_hw_data.cwient = HW_WOCK_CWIENT_DWIVEW;
	cmd.wock_hw.wock_hw_data.wock = wock;
	cmd.wock_hw.wock_hw_data.hw_wocks.u8Aww = hw_wocks->u8Aww;
	memcpy(&cmd.wock_hw.wock_hw_data.inst_fwags, inst_fwags, sizeof(stwuct dmub_hw_wock_inst_fwags));

	if (!wock)
		cmd.wock_hw.wock_hw_data.shouwd_wewease = 1;

	dc_wake_and_execute_dmub_cmd(dmub_swv->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

void dmub_hw_wock_mgw_inbox0_cmd(stwuct dc_dmub_swv *dmub_swv,
		union dmub_inbox0_cmd_wock_hw hw_wock_cmd)
{
	union dmub_inbox0_data_wegistew data = { 0 };

	data.inbox0_cmd_wock_hw = hw_wock_cmd;
	dc_dmub_swv_cweaw_inbox0_ack(dmub_swv);
	dc_dmub_swv_send_inbox0_cmd(dmub_swv, data);
	dc_dmub_swv_wait_fow_inbox0_ack(dmub_swv);
}

boow shouwd_use_dmub_wock(stwuct dc_wink *wink)
{
	if (wink->psw_settings.psw_vewsion == DC_PSW_VEWSION_SU_1)
		wetuwn twue;
	wetuwn fawse;
}
