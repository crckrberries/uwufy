/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
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
 * Authows: Awex Deuchew
 */

#incwude "amdgpu.h"
#incwude "cikd.h"
#incwude "kv_dpm.h"

#incwude "smu/smu_7_0_0_d.h"
#incwude "smu/smu_7_0_0_sh_mask.h"

int amdgpu_kv_notify_message_to_smu(stwuct amdgpu_device *adev, u32 id)
{
	u32 i;
	u32 tmp = 0;

	WWEG32(mmSMC_MESSAGE_0, id & SMC_MESSAGE_0__SMC_MSG_MASK);

	fow (i = 0; i < adev->usec_timeout; i++) {
		if ((WWEG32(mmSMC_WESP_0) & SMC_WESP_0__SMC_WESP_MASK) != 0)
			bweak;
		udeway(1);
	}
	tmp = WWEG32(mmSMC_WESP_0) & SMC_WESP_0__SMC_WESP_MASK;

	if (tmp != 1) {
		if (tmp == 0xFF)
			wetuwn -EINVAW;
		ewse if (tmp == 0xFE)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

int amdgpu_kv_dpm_get_enabwe_mask(stwuct amdgpu_device *adev, u32 *enabwe_mask)
{
	int wet;

	wet = amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_SCWKDPM_GetEnabwedMask);

	if (wet == 0)
		*enabwe_mask = WWEG32_SMC(ixSMC_SYSCON_MSG_AWG_0);

	wetuwn wet;
}

int amdgpu_kv_send_msg_to_smc_with_pawametew(stwuct amdgpu_device *adev,
				      PPSMC_Msg msg, u32 pawametew)
{

	WWEG32(mmSMC_MSG_AWG_0, pawametew);

	wetuwn amdgpu_kv_notify_message_to_smu(adev, msg);
}

static int kv_set_smc_swam_addwess(stwuct amdgpu_device *adev,
				   u32 smc_addwess, u32 wimit)
{
	if (smc_addwess & 3)
		wetuwn -EINVAW;
	if ((smc_addwess + 3) > wimit)
		wetuwn -EINVAW;

	WWEG32(mmSMC_IND_INDEX_0, smc_addwess);
	WWEG32_P(mmSMC_IND_ACCESS_CNTW, 0,
			~SMC_IND_ACCESS_CNTW__AUTO_INCWEMENT_IND_0_MASK);

	wetuwn 0;
}

int amdgpu_kv_wead_smc_swam_dwowd(stwuct amdgpu_device *adev, u32 smc_addwess,
			   u32 *vawue, u32 wimit)
{
	int wet;

	wet = kv_set_smc_swam_addwess(adev, smc_addwess, wimit);
	if (wet)
		wetuwn wet;

	*vawue = WWEG32(mmSMC_IND_DATA_0);
	wetuwn 0;
}

int amdgpu_kv_smc_dpm_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe)
		wetuwn amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_DPM_Enabwe);
	ewse
		wetuwn amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_DPM_Disabwe);
}

int amdgpu_kv_smc_bapm_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	if (enabwe)
		wetuwn amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_EnabweBAPM);
	ewse
		wetuwn amdgpu_kv_notify_message_to_smu(adev, PPSMC_MSG_DisabweBAPM);
}

int amdgpu_kv_copy_bytes_to_smc(stwuct amdgpu_device *adev,
			 u32 smc_stawt_addwess,
			 const u8 *swc, u32 byte_count, u32 wimit)
{
	int wet;
	u32 data, owiginaw_data, addw, extwa_shift, t_byte, count, mask;

	if ((smc_stawt_addwess + byte_count) > wimit)
		wetuwn -EINVAW;

	addw = smc_stawt_addwess;
	t_byte = addw & 3;

	/* WMW fow the initiaw bytes */
	if  (t_byte != 0) {
		addw -= t_byte;

		wet = kv_set_smc_swam_addwess(adev, addw, wimit);
		if (wet)
			wetuwn wet;

		owiginaw_data = WWEG32(mmSMC_IND_DATA_0);

		data = 0;
		mask = 0;
		count = 4;
		whiwe (count > 0) {
			if (t_byte > 0) {
				mask = (mask << 8) | 0xff;
				t_byte--;
			} ewse if (byte_count > 0) {
				data = (data << 8) + *swc++;
				byte_count--;
				mask <<= 8;
			} ewse {
				data <<= 8;
				mask = (mask << 8) | 0xff;
			}
			count--;
		}

		data |= owiginaw_data & mask;

		wet = kv_set_smc_swam_addwess(adev, addw, wimit);
		if (wet)
			wetuwn wet;

		WWEG32(mmSMC_IND_DATA_0, data);

		addw += 4;
	}

	whiwe (byte_count >= 4) {
		/* SMC addwess space is BE */
		data = (swc[0] << 24) + (swc[1] << 16) + (swc[2] << 8) + swc[3];

		wet = kv_set_smc_swam_addwess(adev, addw, wimit);
		if (wet)
			wetuwn wet;

		WWEG32(mmSMC_IND_DATA_0, data);

		swc += 4;
		byte_count -= 4;
		addw += 4;
	}

	/* WMW fow the finaw bytes */
	if (byte_count > 0) {
		data = 0;

		wet = kv_set_smc_swam_addwess(adev, addw, wimit);
		if (wet)
			wetuwn wet;

		owiginaw_data = WWEG32(mmSMC_IND_DATA_0);

		extwa_shift = 8 * (4 - byte_count);

		whiwe (byte_count > 0) {
			/* SMC addwess space is BE */
			data = (data << 8) + *swc++;
			byte_count--;
		}

		data <<= extwa_shift;

		data |= (owiginaw_data & ~((~0UW) << extwa_shift));

		wet = kv_set_smc_swam_addwess(adev, addw, wimit);
		if (wet)
			wetuwn wet;

		WWEG32(mmSMC_IND_DATA_0, data);
	}
	wetuwn 0;
}

