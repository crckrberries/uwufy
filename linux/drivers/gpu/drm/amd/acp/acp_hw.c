/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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

#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>

#incwude "acp_gfx_if.h"

#define ACP_MODE_I2S	0
#define ACP_MODE_AZ	1

#define mmACP_AZAWIA_I2S_SEWECT 0x51d4

int amd_acp_hw_init(stwuct cgs_device *cgs_device,
		    unsigned acp_vewsion_majow, unsigned acp_vewsion_minow)
{
	unsigned int acp_mode = ACP_MODE_I2S;

	if ((acp_vewsion_majow == 2) && (acp_vewsion_minow == 2))
		acp_mode = cgs_wead_wegistew(cgs_device,
					mmACP_AZAWIA_I2S_SEWECT);

	if (acp_mode != ACP_MODE_I2S)
		wetuwn -ENODEV;

	wetuwn 0;
}
