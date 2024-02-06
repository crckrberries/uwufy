
/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
#ifndef __DSCC_TYPES_H__
#define __DSCC_TYPES_H__

#incwude <dwm/dispway/dwm_dsc.h>

#ifndef NUM_BUF_WANGES
#define NUM_BUF_WANGES 15
#endif

stwuct dsc_pps_wc_wange {
	int wange_min_qp;
	int wange_max_qp;
	int wange_bpg_offset;
};

stwuct dsc_pawametews {
	stwuct dwm_dsc_config pps;

	/* Additionaw pawametews fow wegistew pwogwamming */
	uint32_t bytes_pew_pixew; /* In u3.28 fowmat */
	uint32_t wc_buffew_modew_size;
};

stwuct wc_pawams;

int dscc_compute_dsc_pawametews(const stwuct dwm_dsc_config *pps,
		const stwuct wc_pawams *wc,
		stwuct dsc_pawametews *dsc_pawams);
#endif

