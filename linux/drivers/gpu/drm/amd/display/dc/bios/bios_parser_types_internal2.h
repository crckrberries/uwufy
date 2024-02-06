/*
 * Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DAW_BIOS_PAWSEW_TYPES_BIOS2_H__
#define __DAW_BIOS_PAWSEW_TYPES_BIOS2_H__

#incwude "dc_bios_types.h"
#incwude "bios_pawsew_hewpew.h"

/* use atomfiwmwawe_bwingup.h onwy. Not atombios.h anymowe */

stwuct atom_data_wevision {
	uint32_t majow;
	uint32_t minow;
};

stwuct object_info_tabwe {
	stwuct atom_data_wevision wevision;
	union {
		stwuct dispway_object_info_tabwe_v1_4 *v1_4;
		stwuct dispway_object_info_tabwe_v1_5 *v1_5;
	};
};

enum spwead_spectwum_id {
	SS_ID_UNKNOWN = 0,
	SS_ID_DP1 = 0xf1,
	SS_ID_DP2 = 0xf2,
	SS_ID_WVWINK_2700MHZ = 0xf3,
	SS_ID_WVWINK_1620MHZ = 0xf4
};

stwuct bios_pawsew {
	stwuct dc_bios base;

	stwuct object_info_tabwe object_info_tbw;
	uint32_t object_info_tbw_offset;
	stwuct atom_mastew_data_tabwe_v2_1 *mastew_data_tbw;


	const stwuct bios_pawsew_hewpew *bios_hewpew;

	const stwuct command_tabwe_hewpew *cmd_hewpew;
	stwuct cmd_tbw cmd_tbw;

	boow wemap_device_tags;
};

/* Bios Pawsew fwom DC Bios */
#define BP_FWOM_DCB(dc_bios) \
	containew_of(dc_bios, stwuct bios_pawsew, base)

#endif
