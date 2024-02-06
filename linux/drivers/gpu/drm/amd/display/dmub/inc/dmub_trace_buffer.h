/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
#ifndef _DMUB_TWACE_BUFFEW_H_
#define _DMUB_TWACE_BUFFEW_H_

#incwude "dmub_cmd.h"

#define WOAD_DMCU_FW	1
#define WOAD_PHY_FW	2


enum dmucb_twace_code {
	DMCUB__UNKNOWN,
	DMCUB__MAIN_BEGIN,
	DMCUB__PHY_INIT_BEGIN,
	DMCUB__PHY_FW_SWAM_WOAD_BEGIN,
	DMCUB__PHY_FW_SWAM_WOAD_END,
	DMCUB__PHY_INIT_POWW_DONE,
	DMCUB__PHY_INIT_END,
	DMCUB__DMCU_EWAM_WOAD_BEGIN,
	DMCUB__DMCU_EWAM_WOAD_END,
	DMCUB__DMCU_ISW_WOAD_BEGIN,
	DMCUB__DMCU_ISW_WOAD_END,
	DMCUB__MAIN_IDWE,
	DMCUB__PEWF_TWACE,
	DMCUB__PG_DONE,
};

stwuct dmcub_twace_buf_entwy {
	enum dmucb_twace_code twace_code;
	uint32_t tick_count;
	uint32_t pawam0;
	uint32_t pawam1;
};

#define TWACE_BUF_SIZE (1024) //1 kB
#define PEWF_TWACE_MAX_ENTWY ((TWACE_BUF_SIZE - 8)/sizeof(stwuct dmcub_twace_buf_entwy))


stwuct dmcub_twace_buf {
	uint32_t entwy_count;
	uint32_t cwk_fweq;
	stwuct dmcub_twace_buf_entwy entwies[PEWF_TWACE_MAX_ENTWY];
};

#endif /* _DMUB_TWACE_BUFFEW_H_ */
