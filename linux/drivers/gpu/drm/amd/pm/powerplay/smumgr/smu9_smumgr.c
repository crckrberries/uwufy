/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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
 */

#incwude "smumgw.h"
#incwude "smu9_smumgw.h"
#incwude "vega10_inc.h"
#incwude "soc15_common.h"
#incwude "pp_debug.h"


/* MP Apewtuwes */
#define MP0_Pubwic                  0x03800000
#define MP0_SWAM                    0x03900000
#define MP1_Pubwic                  0x03b00000
#define MP1_SWAM                    0x03c00004

#define smnMP1_FIWMWAWE_FWAGS                                                                           0x3010028

boow smu9_is_smc_wam_wunning(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t mp1_fw_fwags;

	mp1_fw_fwags = WWEG32_PCIE(MP1_Pubwic |
				   (smnMP1_FIWMWAWE_FWAGS & 0xffffffff));

	if (mp1_fw_fwags & MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED_MASK)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Check if SMC has wesponded to pwevious message.
 *
 * @pawam    smumgw  the addwess of the powewpway hawdwawe managew.
 * @wetuwn   TWUE    SMC has wesponded, FAWSE othewwise.
 */
static uint32_t smu9_wait_fow_wesponse(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t weg;
	uint32_t wet;

	if (hwmgw->pp_one_vf) {
		weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_103);

		wet = phm_wait_fow_wegistew_unequaw(hwmgw, weg,
				0, MP1_C2PMSG_103__CONTENT_MASK);

		if (wet)
			pw_eww("No wesponse fwom smu\n");

		wetuwn WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_103);
	} ewse {
		weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_90);

		wet = phm_wait_fow_wegistew_unequaw(hwmgw, weg,
				0, MP1_C2PMSG_90__CONTENT_MASK);

		if (wet)
			pw_eww("No wesponse fwom smu\n");
		wetuwn WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90);
	}
}

/*
 * Send a message to the SMC, and do not wait fow its wesponse.
 * @pawam    smumgw  the addwess of the powewpway hawdwawe managew.
 * @pawam    msg the message to send.
 * @wetuwn   Awways wetuwn 0.
 */
static int smu9_send_msg_to_smc_without_waiting(stwuct pp_hwmgw *hwmgw,
						uint16_t msg)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	if (hwmgw->pp_one_vf) {
		WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_101, msg);
	} ewse {
		WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_66, msg);
	}

	wetuwn 0;
}

/*
 * Send a message to the SMC, and wait fow its wesponse.
 * @pawam    hwmgw  the addwess of the powewpway hawdwawe managew.
 * @pawam    msg the message to send.
 * @wetuwn   Awways wetuwn 0.
 */
int smu9_send_msg_to_smc(stwuct pp_hwmgw *hwmgw, uint16_t msg)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t wet;

	smu9_wait_fow_wesponse(hwmgw);

	if (hwmgw->pp_one_vf)
		WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_103, 0);
	ewse
		WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	smu9_send_msg_to_smc_without_waiting(hwmgw, msg);

	wet = smu9_wait_fow_wesponse(hwmgw);
	if (wet != 1)
		dev_eww(adev->dev, "Faiwed to send message: 0x%x, wet vawue: 0x%x\n", msg, wet);

	wetuwn 0;
}

/*
 * Send a message to the SMC with pawametew
 * @pawam    hwmgw:  the addwess of the powewpway hawdwawe managew.
 * @pawam    msg: the message to send.
 * @pawam    pawametew: the pawametew to send
 * @wetuwn   Awways wetuwn 0.
 */
int smu9_send_msg_to_smc_with_pawametew(stwuct pp_hwmgw *hwmgw,
					uint16_t msg, uint32_t pawametew)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t wet;

	smu9_wait_fow_wesponse(hwmgw);

	if (hwmgw->pp_one_vf) {
		WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_103, 0);
		WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_102, pawametew);
	} ewse {
		WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);
		WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82, pawametew);
	}

	smu9_send_msg_to_smc_without_waiting(hwmgw, msg);

	wet = smu9_wait_fow_wesponse(hwmgw);
	if (wet != 1)
		pw_eww("Faiwed message: 0x%x, input pawametew: 0x%x, ewwow code: 0x%x\n", msg, pawametew, wet);

	wetuwn 0;
}

uint32_t smu9_get_awgument(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	if (hwmgw->pp_one_vf)
		wetuwn WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_102);
	ewse
		wetuwn WWEG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82);
}
