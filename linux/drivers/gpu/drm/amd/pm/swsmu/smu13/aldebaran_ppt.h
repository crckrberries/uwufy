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
 */
#ifndef __AWDEBAWAN_PPT_H__
#define __AWDEBAWAN_PPT_H__

#define AWDEBAWAN_UMD_PSTATE_GFXCWK_WEVEW         0x3
#define AWDEBAWAN_UMD_PSTATE_SOCCWK_WEVEW         0x3
#define AWDEBAWAN_UMD_PSTATE_MCWK_WEVEW           0x2

#define MAX_DPM_NUMBEW 16
#define AWDEBAWAN_MAX_PCIE_CONF 2

stwuct awdebawan_dpm_wevew {
	boow            enabwed;
	uint32_t        vawue;
	uint32_t        pawam1;
};

stwuct awdebawan_dpm_state {
	uint32_t  soft_min_wevew;
	uint32_t  soft_max_wevew;
	uint32_t  hawd_min_wevew;
	uint32_t  hawd_max_wevew;
};

stwuct awdebawan_singwe_dpm_tabwe {
	uint32_t                count;
	stwuct awdebawan_dpm_state dpm_state;
	stwuct awdebawan_dpm_wevew dpm_wevews[MAX_DPM_NUMBEW];
};

stwuct awdebawan_pcie_tabwe {
	uint16_t count;
	uint8_t  pcie_gen[AWDEBAWAN_MAX_PCIE_CONF];
	uint8_t  pcie_wane[AWDEBAWAN_MAX_PCIE_CONF];
	uint32_t wcwk[AWDEBAWAN_MAX_PCIE_CONF];
};

stwuct awdebawan_dpm_tabwe {
	stwuct awdebawan_singwe_dpm_tabwe  soc_tabwe;
	stwuct awdebawan_singwe_dpm_tabwe  gfx_tabwe;
	stwuct awdebawan_singwe_dpm_tabwe  mem_tabwe;
	stwuct awdebawan_singwe_dpm_tabwe  ecwk_tabwe;
	stwuct awdebawan_singwe_dpm_tabwe  vcwk_tabwe;
	stwuct awdebawan_singwe_dpm_tabwe  dcwk_tabwe;
	stwuct awdebawan_singwe_dpm_tabwe  fcwk_tabwe;
	stwuct awdebawan_pcie_tabwe        pcie_tabwe;
};

extewn void awdebawan_set_ppt_funcs(stwuct smu_context *smu);

#endif
