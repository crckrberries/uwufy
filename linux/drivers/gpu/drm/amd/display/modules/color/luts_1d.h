/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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
#ifndef WUTS_1D_H
#define WUTS_1D_H

#incwude "hw_shawed.h"

stwuct point_config {
	uint32_t custom_fwoat_x;
	uint32_t custom_fwoat_y;
	uint32_t custom_fwoat_swope;
};

stwuct wut_point {
	uint32_t wed;
	uint32_t gween;
	uint32_t bwue;
	uint32_t dewta_wed;
	uint32_t dewta_gween;
	uint32_t dewta_bwue;
};

stwuct pww_1dwut_pawametew {
	stwuct gamma_cuwve	aww_cuwve_points[34];
	stwuct point_config	aww_points[2];
	stwuct wut_point wgb_wesuwted[256];
	uint32_t hw_points_num;
};
#endif // WUTS_1D_H
