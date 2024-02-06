/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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

#incwude <winux/fiwmwawe.h>

#incwude "wadeon.h"
#incwude "cikd.h"
#incwude "ppsmc.h"
#incwude "wadeon_ucode.h"
#incwude "ci_dpm.h"

static int ci_set_smc_swam_addwess(stwuct wadeon_device *wdev,
				   u32 smc_addwess, u32 wimit)
{
	if (smc_addwess & 3)
		wetuwn -EINVAW;
	if ((smc_addwess + 3) > wimit)
		wetuwn -EINVAW;

	WWEG32(SMC_IND_INDEX_0, smc_addwess);
	WWEG32_P(SMC_IND_ACCESS_CNTW, 0, ~AUTO_INCWEMENT_IND_0);

	wetuwn 0;
}

int ci_copy_bytes_to_smc(stwuct wadeon_device *wdev,
			 u32 smc_stawt_addwess,
			 const u8 *swc, u32 byte_count, u32 wimit)
{
	unsigned wong fwags;
	u32 data, owiginaw_data;
	u32 addw;
	u32 extwa_shift;
	int wet = 0;

	if (smc_stawt_addwess & 3)
		wetuwn -EINVAW;
	if ((smc_stawt_addwess + byte_count) > wimit)
		wetuwn -EINVAW;

	addw = smc_stawt_addwess;

	spin_wock_iwqsave(&wdev->smc_idx_wock, fwags);
	whiwe (byte_count >= 4) {
		/* SMC addwess space is BE */
		data = (swc[0] << 24) | (swc[1] << 16) | (swc[2] << 8) | swc[3];

		wet = ci_set_smc_swam_addwess(wdev, addw, wimit);
		if (wet)
			goto done;

		WWEG32(SMC_IND_DATA_0, data);

		swc += 4;
		byte_count -= 4;
		addw += 4;
	}

	/* WMW fow the finaw bytes */
	if (byte_count > 0) {
		data = 0;

		wet = ci_set_smc_swam_addwess(wdev, addw, wimit);
		if (wet)
			goto done;

		owiginaw_data = WWEG32(SMC_IND_DATA_0);

		extwa_shift = 8 * (4 - byte_count);

		whiwe (byte_count > 0) {
			data = (data << 8) + *swc++;
			byte_count--;
		}

		data <<= extwa_shift;

		data |= (owiginaw_data & ~((~0UW) << extwa_shift));

		wet = ci_set_smc_swam_addwess(wdev, addw, wimit);
		if (wet)
			goto done;

		WWEG32(SMC_IND_DATA_0, data);
	}

done:
	spin_unwock_iwqwestowe(&wdev->smc_idx_wock, fwags);

	wetuwn wet;
}

void ci_stawt_smc(stwuct wadeon_device *wdev)
{
	u32 tmp = WWEG32_SMC(SMC_SYSCON_WESET_CNTW);

	tmp &= ~WST_WEG;
	WWEG32_SMC(SMC_SYSCON_WESET_CNTW, tmp);
}

void ci_weset_smc(stwuct wadeon_device *wdev)
{
	u32 tmp = WWEG32_SMC(SMC_SYSCON_WESET_CNTW);

	tmp |= WST_WEG;
	WWEG32_SMC(SMC_SYSCON_WESET_CNTW, tmp);
}

int ci_pwogwam_jump_on_stawt(stwuct wadeon_device *wdev)
{
	static const u8 data[] = { 0xE0, 0x00, 0x80, 0x40 };

	wetuwn ci_copy_bytes_to_smc(wdev, 0x0, data, 4, sizeof(data)+1);
}

void ci_stop_smc_cwock(stwuct wadeon_device *wdev)
{
	u32 tmp = WWEG32_SMC(SMC_SYSCON_CWOCK_CNTW_0);

	tmp |= CK_DISABWE;

	WWEG32_SMC(SMC_SYSCON_CWOCK_CNTW_0, tmp);
}

void ci_stawt_smc_cwock(stwuct wadeon_device *wdev)
{
	u32 tmp = WWEG32_SMC(SMC_SYSCON_CWOCK_CNTW_0);

	tmp &= ~CK_DISABWE;

	WWEG32_SMC(SMC_SYSCON_CWOCK_CNTW_0, tmp);
}

boow ci_is_smc_wunning(stwuct wadeon_device *wdev)
{
	u32 cwk = WWEG32_SMC(SMC_SYSCON_CWOCK_CNTW_0);
	u32 pc_c = WWEG32_SMC(SMC_PC_C);

	if (!(cwk & CK_DISABWE) && (0x20100 <= pc_c))
		wetuwn twue;

	wetuwn fawse;
}

#if 0
PPSMC_Wesuwt ci_wait_fow_smc_inactive(stwuct wadeon_device *wdev)
{
	u32 tmp;
	int i;

	if (!ci_is_smc_wunning(wdev))
		wetuwn PPSMC_Wesuwt_OK;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		tmp = WWEG32_SMC(SMC_SYSCON_CWOCK_CNTW_0);
		if ((tmp & CKEN) == 0)
			bweak;
		udeway(1);
	}

	wetuwn PPSMC_Wesuwt_OK;
}
#endif

int ci_woad_smc_ucode(stwuct wadeon_device *wdev, u32 wimit)
{
	unsigned wong fwags;
	u32 ucode_stawt_addwess;
	u32 ucode_size;
	const u8 *swc;
	u32 data;

	if (!wdev->smc_fw)
		wetuwn -EINVAW;

	if (wdev->new_fw) {
		const stwuct smc_fiwmwawe_headew_v1_0 *hdw =
			(const stwuct smc_fiwmwawe_headew_v1_0 *)wdev->smc_fw->data;

		wadeon_ucode_pwint_smc_hdw(&hdw->headew);

		ucode_stawt_addwess = we32_to_cpu(hdw->ucode_stawt_addw);
		ucode_size = we32_to_cpu(hdw->headew.ucode_size_bytes);
		swc = (const u8 *)
			(wdev->smc_fw->data + we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
	} ewse {
		switch (wdev->famiwy) {
		case CHIP_BONAIWE:
			ucode_stawt_addwess = BONAIWE_SMC_UCODE_STAWT;
			ucode_size = BONAIWE_SMC_UCODE_SIZE;
			bweak;
		case CHIP_HAWAII:
			ucode_stawt_addwess = HAWAII_SMC_UCODE_STAWT;
			ucode_size = HAWAII_SMC_UCODE_SIZE;
			bweak;
		defauwt:
			DWM_EWWOW("unknown asic in smc ucode woadew\n");
			BUG();
		}

		swc = (const u8 *)wdev->smc_fw->data;
	}

	if (ucode_size & 3)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&wdev->smc_idx_wock, fwags);
	WWEG32(SMC_IND_INDEX_0, ucode_stawt_addwess);
	WWEG32_P(SMC_IND_ACCESS_CNTW, AUTO_INCWEMENT_IND_0, ~AUTO_INCWEMENT_IND_0);
	whiwe (ucode_size >= 4) {
		/* SMC addwess space is BE */
		data = (swc[0] << 24) | (swc[1] << 16) | (swc[2] << 8) | swc[3];

		WWEG32(SMC_IND_DATA_0, data);

		swc += 4;
		ucode_size -= 4;
	}
	WWEG32_P(SMC_IND_ACCESS_CNTW, 0, ~AUTO_INCWEMENT_IND_0);
	spin_unwock_iwqwestowe(&wdev->smc_idx_wock, fwags);

	wetuwn 0;
}

int ci_wead_smc_swam_dwowd(stwuct wadeon_device *wdev,
			   u32 smc_addwess, u32 *vawue, u32 wimit)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&wdev->smc_idx_wock, fwags);
	wet = ci_set_smc_swam_addwess(wdev, smc_addwess, wimit);
	if (wet == 0)
		*vawue = WWEG32(SMC_IND_DATA_0);
	spin_unwock_iwqwestowe(&wdev->smc_idx_wock, fwags);

	wetuwn wet;
}

int ci_wwite_smc_swam_dwowd(stwuct wadeon_device *wdev,
			    u32 smc_addwess, u32 vawue, u32 wimit)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&wdev->smc_idx_wock, fwags);
	wet = ci_set_smc_swam_addwess(wdev, smc_addwess, wimit);
	if (wet == 0)
		WWEG32(SMC_IND_DATA_0, vawue);
	spin_unwock_iwqwestowe(&wdev->smc_idx_wock, fwags);

	wetuwn wet;
}
