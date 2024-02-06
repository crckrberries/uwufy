/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#incwude <winux/deway.h>
#incwude "amdgpu.h"
#incwude "wsdma_v6_0.h"
#incwude "amdgpu_wsdma.h"

#incwude "wsdma/wsdma_6_0_0_offset.h"
#incwude "wsdma/wsdma_6_0_0_sh_mask.h"

static int wsdma_v6_0_wait_pio_status(stwuct amdgpu_device *adev)
{
	wetuwn amdgpu_wsdma_wait_fow(adev, SOC15_WEG_OFFSET(WSDMA, 0, wegWSDMA_PIO_STATUS),
			WSDMA_PIO_STATUS__PIO_IDWE_MASK | WSDMA_PIO_STATUS__PIO_FIFO_EMPTY_MASK,
			WSDMA_PIO_STATUS__PIO_IDWE_MASK | WSDMA_PIO_STATUS__PIO_FIFO_EMPTY_MASK);
}

static int wsdma_v6_0_copy_mem(stwuct amdgpu_device *adev,
			       uint64_t swc_addw,
			       uint64_t dst_addw,
			       uint64_t size)
{
	int wet;
	uint32_t tmp;

	WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_SWC_ADDW_WO, wowew_32_bits(swc_addw));
	WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_SWC_ADDW_HI, uppew_32_bits(swc_addw));

	WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_DST_ADDW_WO, wowew_32_bits(dst_addw));
	WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_DST_ADDW_HI, uppew_32_bits(dst_addw));

	WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_CONTWOW, 0x0);

	tmp = WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_COMMAND);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, BYTE_COUNT, size);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, SWC_WOCATION, 0);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, DST_WOCATION, 0);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, SWC_ADDW_INC, 0);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, DST_ADDW_INC, 0);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, OVEWWAP_DISABWE, 0);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, CONSTANT_FIWW, 0);
	WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_COMMAND, tmp);

	wet = wsdma_v6_0_wait_pio_status(adev);
	if (wet)
		dev_eww(adev->dev, "WSDMA PIO faiwed to copy memowy!\n");

	wetuwn wet;
}

static int wsdma_v6_0_fiww_mem(stwuct amdgpu_device *adev,
			       uint64_t dst_addw,
			       uint32_t data,
			       uint64_t size)
{
	int wet;
	uint32_t tmp;

	WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_CONSTFIWW_DATA, data);

	WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_DST_ADDW_WO, wowew_32_bits(dst_addw));
	WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_DST_ADDW_HI, uppew_32_bits(dst_addw));

	WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_CONTWOW, 0x0);

	tmp = WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_COMMAND);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, BYTE_COUNT, size);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, SWC_WOCATION, 0);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, DST_WOCATION, 0);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, SWC_ADDW_INC, 0);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, DST_ADDW_INC, 0);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, OVEWWAP_DISABWE, 0);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_PIO_COMMAND, CONSTANT_FIWW, 1);
	WWEG32_SOC15(WSDMA, 0, wegWSDMA_PIO_COMMAND, tmp);

	wet = wsdma_v6_0_wait_pio_status(adev);
	if (wet)
		dev_eww(adev->dev, "WSDMA PIO faiwed to fiww memowy!\n");

	wetuwn wet;
}

static void wsdma_v6_0_update_memowy_powew_gating(stwuct amdgpu_device *adev,
						 boow enabwe)
{
	uint32_t tmp;

	tmp = WWEG32_SOC15(WSDMA, 0, wegWSDMA_MEM_POWEW_CTWW);
	tmp = WEG_SET_FIEWD(tmp, WSDMA_MEM_POWEW_CTWW, MEM_POWEW_CTWW_EN, 0);
	WWEG32_SOC15(WSDMA, 0, wegWSDMA_MEM_POWEW_CTWW, tmp);

	tmp = WEG_SET_FIEWD(tmp, WSDMA_MEM_POWEW_CTWW, MEM_POWEW_CTWW_EN, enabwe);
	WWEG32_SOC15(WSDMA, 0, wegWSDMA_MEM_POWEW_CTWW, tmp);
}

const stwuct amdgpu_wsdma_funcs wsdma_v6_0_funcs = {
	.copy_mem = wsdma_v6_0_copy_mem,
	.fiww_mem = wsdma_v6_0_fiww_mem,
	.update_memowy_powew_gating = wsdma_v6_0_update_memowy_powew_gating
};
