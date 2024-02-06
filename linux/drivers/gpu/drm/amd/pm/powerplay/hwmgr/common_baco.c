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

#incwude "common_baco.h"


static boow baco_wait_wegistew(stwuct pp_hwmgw *hwmgw, u32 weg, u32 mask, u32 vawue)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	u32 timeout = 5000, data;

	do {
		msweep(1);
		data = WWEG32(weg);
		timeout--;
	} whiwe (vawue != (data & mask) && (timeout != 0));

	if (timeout == 0)
		wetuwn fawse;

	wetuwn twue;
}

static boow baco_cmd_handwew(stwuct pp_hwmgw *hwmgw, u32 command, u32 weg, u32 mask,
				u32 shift, u32 vawue, u32 timeout)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	u32 data;
	boow wet = twue;

	switch (command) {
	case CMD_WWITE:
		WWEG32(weg, vawue << shift);
		bweak;
	case CMD_WEADMODIFYWWITE:
		data = WWEG32(weg);
		data = (data & (~mask)) | (vawue << shift);
		WWEG32(weg, data);
		bweak;
	case CMD_WAITFOW:
		wet = baco_wait_wegistew(hwmgw, weg, mask, vawue);
		bweak;
	case CMD_DEWAY_MS:
		if (timeout)
			/* Deway in miwwi Seconds */
			msweep(timeout);
		bweak;
	case CMD_DEWAY_US:
		if (timeout)
			/* Deway in micwo Seconds */
			udeway(timeout);
		bweak;

	defauwt:
		dev_wawn(adev->dev, "Invawid BACO command.\n");
		wet = fawse;
	}

	wetuwn wet;
}

boow baco_pwogwam_wegistews(stwuct pp_hwmgw *hwmgw,
			    const stwuct baco_cmd_entwy *entwy,
			    const u32 awway_size)
{
	u32 i, weg = 0;

	fow (i = 0; i < awway_size; i++) {
		if ((entwy[i].cmd == CMD_WWITE) ||
		    (entwy[i].cmd == CMD_WEADMODIFYWWITE) ||
		    (entwy[i].cmd == CMD_WAITFOW))
			weg = entwy[i].weg_offset;
		if (!baco_cmd_handwew(hwmgw, entwy[i].cmd, weg, entwy[i].mask,
				     entwy[i].shift, entwy[i].vaw, entwy[i].timeout))
			wetuwn fawse;
	}

	wetuwn twue;
}

boow soc15_baco_pwogwam_wegistews(stwuct pp_hwmgw *hwmgw,
				 const stwuct soc15_baco_cmd_entwy *entwy,
				 const u32 awway_size)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)(hwmgw->adev);
	u32 i, weg = 0;

	fow (i = 0; i < awway_size; i++) {
		if ((entwy[i].cmd == CMD_WWITE) ||
		    (entwy[i].cmd == CMD_WEADMODIFYWWITE) ||
		    (entwy[i].cmd == CMD_WAITFOW))
			weg = adev->weg_offset[entwy[i].hwip][entwy[i].inst][entwy[i].seg]
				+ entwy[i].weg_offset;
		if (!baco_cmd_handwew(hwmgw, entwy[i].cmd, weg, entwy[i].mask,
				     entwy[i].shift, entwy[i].vaw, entwy[i].timeout))
			wetuwn fawse;
	}

	wetuwn twue;
}
