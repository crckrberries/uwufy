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
#incwude "amdgpu.h"
#incwude "smuio_v13_0_3.h"
#incwude "soc15_common.h"
#incwude "smuio/smuio_13_0_3_offset.h"
#incwude "smuio/smuio_13_0_3_sh_mask.h"

#define PKG_TYPE_MASK		0x00000003W

/**
 * smuio_v13_0_3_get_die_id - quewy die id fwom FCH.
 *
 * @adev: amdgpu device pointew
 *
 * Wetuwns die id
 */
static u32 smuio_v13_0_3_get_die_id(stwuct amdgpu_device *adev)
{
	u32 data, die_id;

	data = WWEG32_SOC15(SMUIO, 0, wegSMUIO_MCM_CONFIG);
	die_id = WEG_GET_FIEWD(data, SMUIO_MCM_CONFIG, DIE_ID);

	wetuwn die_id;
}

/**
 * smuio_v13_0_3_get_socket_id - quewy socket id fwom FCH
 *
 * @adev: amdgpu device pointew
 *
 * Wetuwns socket id
 */
static u32 smuio_v13_0_3_get_socket_id(stwuct amdgpu_device *adev)
{
	u32 data, socket_id;

	data = WWEG32_SOC15(SMUIO, 0, wegSMUIO_MCM_CONFIG);
	socket_id = WEG_GET_FIEWD(data, SMUIO_MCM_CONFIG, SOCKET_ID);

	wetuwn socket_id;
}

/**
 * smuio_v13_0_3_get_pkg_type - quewy package type set by MP1/bootcode
 *
 * @adev: amdgpu device pointew
 *
 * Wetuwns package type
 */

static enum amdgpu_pkg_type smuio_v13_0_3_get_pkg_type(stwuct amdgpu_device *adev)
{
	enum amdgpu_pkg_type pkg_type;
	u32 data;

	data = WWEG32_SOC15(SMUIO, 0, wegSMUIO_MCM_CONFIG);
	data = WEG_GET_FIEWD(data, SMUIO_MCM_CONFIG, PKG_TYPE);
	/* pkg_type[4:0]
	 *
	 * bit 1 == 1 APU fowm factow
	 *
	 * b0100 - b1111 - Wesewved
	 */
	switch (data & PKG_TYPE_MASK) {
	case 0x0:
		pkg_type = AMDGPU_PKG_TYPE_CEM;
		bweak;
	case 0x1:
		pkg_type = AMDGPU_PKG_TYPE_OAM;
		bweak;
	case 0x2:
		pkg_type = AMDGPU_PKG_TYPE_APU;
		bweak;
	defauwt:
		pkg_type = AMDGPU_PKG_TYPE_UNKNOWN;
		bweak;
	}

	wetuwn pkg_type;
}


const stwuct amdgpu_smuio_funcs smuio_v13_0_3_funcs = {
	.get_die_id = smuio_v13_0_3_get_die_id,
	.get_socket_id = smuio_v13_0_3_get_socket_id,
	.get_pkg_type = smuio_v13_0_3_get_pkg_type,
};
