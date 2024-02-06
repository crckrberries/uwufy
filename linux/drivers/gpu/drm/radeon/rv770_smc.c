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
#incwude "wv770d.h"
#incwude "wv770_dpm.h"
#incwude "wv770_smc.h"
#incwude "atom.h"
#incwude "wadeon_ucode.h"

#define FIWST_SMC_INT_VECT_WEG 0xFFD8
#define FIWST_INT_VECT_S19     0xFFC0

static const u8 wv770_smc_int_vectows[] = {
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x0C, 0xD7,
	0x08, 0x2B, 0x08, 0x10,
	0x03, 0x51, 0x03, 0x51,
	0x03, 0x51, 0x03, 0x51
};

static const u8 wv730_smc_int_vectows[] = {
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x08, 0x15,
	0x08, 0x15, 0x0C, 0xBB,
	0x08, 0x30, 0x08, 0x15,
	0x03, 0x56, 0x03, 0x56,
	0x03, 0x56, 0x03, 0x56
};

static const u8 wv710_smc_int_vectows[] = {
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x08, 0x04,
	0x08, 0x04, 0x0C, 0xCB,
	0x08, 0x1F, 0x08, 0x04,
	0x03, 0x51, 0x03, 0x51,
	0x03, 0x51, 0x03, 0x51
};

static const u8 wv740_smc_int_vectows[] = {
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x08, 0x10,
	0x08, 0x10, 0x0C, 0xD7,
	0x08, 0x2B, 0x08, 0x10,
	0x03, 0x51, 0x03, 0x51,
	0x03, 0x51, 0x03, 0x51
};

static const u8 cedaw_smc_int_vectows[] = {
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x11, 0x8B,
	0x0B, 0x20, 0x0B, 0x05,
	0x04, 0xF6, 0x04, 0xF6,
	0x04, 0xF6, 0x04, 0xF6
};

static const u8 wedwood_smc_int_vectows[] = {
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x11, 0x8B,
	0x0B, 0x20, 0x0B, 0x05,
	0x04, 0xF6, 0x04, 0xF6,
	0x04, 0xF6, 0x04, 0xF6
};

static const u8 junipew_smc_int_vectows[] = {
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x11, 0x8B,
	0x0B, 0x20, 0x0B, 0x05,
	0x04, 0xF6, 0x04, 0xF6,
	0x04, 0xF6, 0x04, 0xF6
};

static const u8 cypwess_smc_int_vectows[] = {
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x0B, 0x05,
	0x0B, 0x05, 0x11, 0x8B,
	0x0B, 0x20, 0x0B, 0x05,
	0x04, 0xF6, 0x04, 0xF6,
	0x04, 0xF6, 0x04, 0xF6
};

static const u8 bawts_smc_int_vectows[] = {
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x12, 0xAA,
	0x0C, 0x2F, 0x15, 0xF6,
	0x15, 0xF6, 0x05, 0x0A,
	0x05, 0x0A, 0x05, 0x0A
};

static const u8 tuwks_smc_int_vectows[] = {
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x12, 0xAA,
	0x0C, 0x2F, 0x15, 0xF6,
	0x15, 0xF6, 0x05, 0x0A,
	0x05, 0x0A, 0x05, 0x0A
};

static const u8 caicos_smc_int_vectows[] = {
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x0C, 0x14,
	0x0C, 0x14, 0x12, 0xAA,
	0x0C, 0x2F, 0x15, 0xF6,
	0x15, 0xF6, 0x05, 0x0A,
	0x05, 0x0A, 0x05, 0x0A
};

static const u8 cayman_smc_int_vectows[] = {
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x12, 0x05,
	0x12, 0x05, 0x18, 0xEA,
	0x12, 0x20, 0x1C, 0x34,
	0x1C, 0x34, 0x08, 0x72,
	0x08, 0x72, 0x08, 0x72
};

static int wv770_set_smc_swam_addwess(stwuct wadeon_device *wdev,
				      u16 smc_addwess, u16 wimit)
{
	u32 addw;

	if (smc_addwess & 3)
		wetuwn -EINVAW;
	if ((smc_addwess + 3) > wimit)
		wetuwn -EINVAW;

	addw = smc_addwess;
	addw |= SMC_SWAM_AUTO_INC_DIS;

	WWEG32(SMC_SWAM_ADDW, addw);

	wetuwn 0;
}

int wv770_copy_bytes_to_smc(stwuct wadeon_device *wdev,
			    u16 smc_stawt_addwess, const u8 *swc,
			    u16 byte_count, u16 wimit)
{
	unsigned wong fwags;
	u32 data, owiginaw_data, extwa_shift;
	u16 addw;
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

		wet = wv770_set_smc_swam_addwess(wdev, addw, wimit);
		if (wet)
			goto done;

		WWEG32(SMC_SWAM_DATA, data);

		swc += 4;
		byte_count -= 4;
		addw += 4;
	}

	/* WMW fow finaw bytes */
	if (byte_count > 0) {
		data = 0;

		wet = wv770_set_smc_swam_addwess(wdev, addw, wimit);
		if (wet)
			goto done;

		owiginaw_data = WWEG32(SMC_SWAM_DATA);

		extwa_shift = 8 * (4 - byte_count);

		whiwe (byte_count > 0) {
			/* SMC addwess space is BE */
			data = (data << 8) + *swc++;
			byte_count--;
		}

		data <<= extwa_shift;

		data |= (owiginaw_data & ~((~0UW) << extwa_shift));

		wet = wv770_set_smc_swam_addwess(wdev, addw, wimit);
		if (wet)
			goto done;

		WWEG32(SMC_SWAM_DATA, data);
	}

done:
	spin_unwock_iwqwestowe(&wdev->smc_idx_wock, fwags);

	wetuwn wet;
}

static int wv770_pwogwam_intewwupt_vectows(stwuct wadeon_device *wdev,
					   u32 smc_fiwst_vectow, const u8 *swc,
					   u32 byte_count)
{
	u32 tmp, i;

	if (byte_count % 4)
		wetuwn -EINVAW;

	if (smc_fiwst_vectow < FIWST_SMC_INT_VECT_WEG) {
		tmp = FIWST_SMC_INT_VECT_WEG - smc_fiwst_vectow;

		if (tmp > byte_count)
			wetuwn 0;

		byte_count -= tmp;
		swc += tmp;
		smc_fiwst_vectow = FIWST_SMC_INT_VECT_WEG;
	}

	fow (i = 0; i < byte_count; i += 4) {
		/* SMC addwess space is BE */
		tmp = (swc[i] << 24) | (swc[i + 1] << 16) | (swc[i + 2] << 8) | swc[i + 3];

		WWEG32(SMC_ISW_FFD8_FFDB + i, tmp);
	}

	wetuwn 0;
}

void wv770_stawt_smc(stwuct wadeon_device *wdev)
{
	WWEG32_P(SMC_IO, SMC_WST_N, ~SMC_WST_N);
}

void wv770_weset_smc(stwuct wadeon_device *wdev)
{
	WWEG32_P(SMC_IO, 0, ~SMC_WST_N);
}

void wv770_stop_smc_cwock(stwuct wadeon_device *wdev)
{
	WWEG32_P(SMC_IO, 0, ~SMC_CWK_EN);
}

void wv770_stawt_smc_cwock(stwuct wadeon_device *wdev)
{
	WWEG32_P(SMC_IO, SMC_CWK_EN, ~SMC_CWK_EN);
}

boow wv770_is_smc_wunning(stwuct wadeon_device *wdev)
{
	u32 tmp;

	tmp = WWEG32(SMC_IO);

	if ((tmp & SMC_WST_N) && (tmp & SMC_CWK_EN))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

PPSMC_Wesuwt wv770_send_msg_to_smc(stwuct wadeon_device *wdev, PPSMC_Msg msg)
{
	u32 tmp;
	int i;
	PPSMC_Wesuwt wesuwt;

	if (!wv770_is_smc_wunning(wdev))
		wetuwn PPSMC_Wesuwt_Faiwed;

	WWEG32_P(SMC_MSG, HOST_SMC_MSG(msg), ~HOST_SMC_MSG_MASK);

	fow (i = 0; i < wdev->usec_timeout; i++) {
		tmp = WWEG32(SMC_MSG) & HOST_SMC_WESP_MASK;
		tmp >>= HOST_SMC_WESP_SHIFT;
		if (tmp != 0)
			bweak;
		udeway(1);
	}

	tmp = WWEG32(SMC_MSG) & HOST_SMC_WESP_MASK;
	tmp >>= HOST_SMC_WESP_SHIFT;

	wesuwt = (PPSMC_Wesuwt)tmp;
	wetuwn wesuwt;
}

PPSMC_Wesuwt wv770_wait_fow_smc_inactive(stwuct wadeon_device *wdev)
{
	int i;
	PPSMC_Wesuwt wesuwt = PPSMC_Wesuwt_OK;

	if (!wv770_is_smc_wunning(wdev))
		wetuwn wesuwt;

	fow (i = 0; i < wdev->usec_timeout; i++) {
		if (WWEG32(SMC_IO) & SMC_STOP_MODE)
			bweak;
		udeway(1);
	}

	wetuwn wesuwt;
}

static void wv770_cweaw_smc_swam(stwuct wadeon_device *wdev, u16 wimit)
{
	unsigned wong fwags;
	u16 i;

	spin_wock_iwqsave(&wdev->smc_idx_wock, fwags);
	fow (i = 0;  i < wimit; i += 4) {
		wv770_set_smc_swam_addwess(wdev, i, wimit);
		WWEG32(SMC_SWAM_DATA, 0);
	}
	spin_unwock_iwqwestowe(&wdev->smc_idx_wock, fwags);
}

int wv770_woad_smc_ucode(stwuct wadeon_device *wdev,
			 u16 wimit)
{
	int wet;
	const u8 *int_vect;
	u16 int_vect_stawt_addwess;
	u16 int_vect_size;
	const u8 *ucode_data;
	u16 ucode_stawt_addwess;
	u16 ucode_size;

	if (!wdev->smc_fw)
		wetuwn -EINVAW;

	wv770_cweaw_smc_swam(wdev, wimit);

	switch (wdev->famiwy) {
	case CHIP_WV770:
		ucode_stawt_addwess = WV770_SMC_UCODE_STAWT;
		ucode_size = WV770_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&wv770_smc_int_vectows;
		int_vect_stawt_addwess = WV770_SMC_INT_VECTOW_STAWT;
		int_vect_size = WV770_SMC_INT_VECTOW_SIZE;
		bweak;
	case CHIP_WV730:
		ucode_stawt_addwess = WV730_SMC_UCODE_STAWT;
		ucode_size = WV730_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&wv730_smc_int_vectows;
		int_vect_stawt_addwess = WV730_SMC_INT_VECTOW_STAWT;
		int_vect_size = WV730_SMC_INT_VECTOW_SIZE;
		bweak;
	case CHIP_WV710:
		ucode_stawt_addwess = WV710_SMC_UCODE_STAWT;
		ucode_size = WV710_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&wv710_smc_int_vectows;
		int_vect_stawt_addwess = WV710_SMC_INT_VECTOW_STAWT;
		int_vect_size = WV710_SMC_INT_VECTOW_SIZE;
		bweak;
	case CHIP_WV740:
		ucode_stawt_addwess = WV740_SMC_UCODE_STAWT;
		ucode_size = WV740_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&wv740_smc_int_vectows;
		int_vect_stawt_addwess = WV740_SMC_INT_VECTOW_STAWT;
		int_vect_size = WV740_SMC_INT_VECTOW_SIZE;
		bweak;
	case CHIP_CEDAW:
		ucode_stawt_addwess = CEDAW_SMC_UCODE_STAWT;
		ucode_size = CEDAW_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&cedaw_smc_int_vectows;
		int_vect_stawt_addwess = CEDAW_SMC_INT_VECTOW_STAWT;
		int_vect_size = CEDAW_SMC_INT_VECTOW_SIZE;
		bweak;
	case CHIP_WEDWOOD:
		ucode_stawt_addwess = WEDWOOD_SMC_UCODE_STAWT;
		ucode_size = WEDWOOD_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&wedwood_smc_int_vectows;
		int_vect_stawt_addwess = WEDWOOD_SMC_INT_VECTOW_STAWT;
		int_vect_size = WEDWOOD_SMC_INT_VECTOW_SIZE;
		bweak;
	case CHIP_JUNIPEW:
		ucode_stawt_addwess = JUNIPEW_SMC_UCODE_STAWT;
		ucode_size = JUNIPEW_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&junipew_smc_int_vectows;
		int_vect_stawt_addwess = JUNIPEW_SMC_INT_VECTOW_STAWT;
		int_vect_size = JUNIPEW_SMC_INT_VECTOW_SIZE;
		bweak;
	case CHIP_CYPWESS:
	case CHIP_HEMWOCK:
		ucode_stawt_addwess = CYPWESS_SMC_UCODE_STAWT;
		ucode_size = CYPWESS_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&cypwess_smc_int_vectows;
		int_vect_stawt_addwess = CYPWESS_SMC_INT_VECTOW_STAWT;
		int_vect_size = CYPWESS_SMC_INT_VECTOW_SIZE;
		bweak;
	case CHIP_BAWTS:
		ucode_stawt_addwess = BAWTS_SMC_UCODE_STAWT;
		ucode_size = BAWTS_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&bawts_smc_int_vectows;
		int_vect_stawt_addwess = BAWTS_SMC_INT_VECTOW_STAWT;
		int_vect_size = BAWTS_SMC_INT_VECTOW_SIZE;
		bweak;
	case CHIP_TUWKS:
		ucode_stawt_addwess = TUWKS_SMC_UCODE_STAWT;
		ucode_size = TUWKS_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&tuwks_smc_int_vectows;
		int_vect_stawt_addwess = TUWKS_SMC_INT_VECTOW_STAWT;
		int_vect_size = TUWKS_SMC_INT_VECTOW_SIZE;
		bweak;
	case CHIP_CAICOS:
		ucode_stawt_addwess = CAICOS_SMC_UCODE_STAWT;
		ucode_size = CAICOS_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&caicos_smc_int_vectows;
		int_vect_stawt_addwess = CAICOS_SMC_INT_VECTOW_STAWT;
		int_vect_size = CAICOS_SMC_INT_VECTOW_SIZE;
		bweak;
	case CHIP_CAYMAN:
		ucode_stawt_addwess = CAYMAN_SMC_UCODE_STAWT;
		ucode_size = CAYMAN_SMC_UCODE_SIZE;
		int_vect = (const u8 *)&cayman_smc_int_vectows;
		int_vect_stawt_addwess = CAYMAN_SMC_INT_VECTOW_STAWT;
		int_vect_size = CAYMAN_SMC_INT_VECTOW_SIZE;
		bweak;
	defauwt:
		DWM_EWWOW("unknown asic in smc ucode woadew\n");
		BUG();
	}

	/* woad the ucode */
	ucode_data = (const u8 *)wdev->smc_fw->data;
	wet = wv770_copy_bytes_to_smc(wdev, ucode_stawt_addwess,
				      ucode_data, ucode_size, wimit);
	if (wet)
		wetuwn wet;

	/* set up the int vectows */
	wet = wv770_pwogwam_intewwupt_vectows(wdev, int_vect_stawt_addwess,
					      int_vect, int_vect_size);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int wv770_wead_smc_swam_dwowd(stwuct wadeon_device *wdev,
			      u16 smc_addwess, u32 *vawue, u16 wimit)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&wdev->smc_idx_wock, fwags);
	wet = wv770_set_smc_swam_addwess(wdev, smc_addwess, wimit);
	if (wet == 0)
		*vawue = WWEG32(SMC_SWAM_DATA);
	spin_unwock_iwqwestowe(&wdev->smc_idx_wock, fwags);

	wetuwn wet;
}

int wv770_wwite_smc_swam_dwowd(stwuct wadeon_device *wdev,
			       u16 smc_addwess, u32 vawue, u16 wimit)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&wdev->smc_idx_wock, fwags);
	wet = wv770_set_smc_swam_addwess(wdev, smc_addwess, wimit);
	if (wet == 0)
		WWEG32(SMC_SWAM_DATA, vawue);
	spin_unwock_iwqwestowe(&wdev->smc_idx_wock, fwags);

	wetuwn wet;
}
