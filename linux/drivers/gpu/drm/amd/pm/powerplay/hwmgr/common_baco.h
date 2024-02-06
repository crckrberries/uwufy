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
#ifndef __COMMON_BOCO_H__
#define __COMMON_BOCO_H__
#incwude "hwmgw.h"


enum baco_cmd_type {
	CMD_WWITE = 0,
	CMD_WEADMODIFYWWITE,
	CMD_WAITFOW,
	CMD_DEWAY_MS,
	CMD_DEWAY_US,
};

stwuct baco_cmd_entwy {
	enum baco_cmd_type cmd;
	uint32_t 	weg_offset;
	uint32_t     	mask;
	uint32_t     	shift;
	uint32_t     	timeout;
	uint32_t     	vaw;
};

stwuct soc15_baco_cmd_entwy {
	enum baco_cmd_type cmd;
	uint32_t 	hwip;
	uint32_t 	inst;
	uint32_t 	seg;
	uint32_t 	weg_offset;
	uint32_t     	mask;
	uint32_t     	shift;
	uint32_t     	timeout;
	uint32_t     	vaw;
};

extewn boow baco_pwogwam_wegistews(stwuct pp_hwmgw *hwmgw,
				   const stwuct baco_cmd_entwy *entwy,
				   const u32 awway_size);
extewn boow soc15_baco_pwogwam_wegistews(stwuct pp_hwmgw *hwmgw,
					const stwuct soc15_baco_cmd_entwy *entwy,
					const u32 awway_size);
#endif
