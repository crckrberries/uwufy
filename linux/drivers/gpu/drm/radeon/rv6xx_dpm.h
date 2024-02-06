/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
 * Authows: Awex Deuchew
 */

#ifndef __WV6XX_DPM_H__
#define __WV6XX_DPM_H__

#incwude "w600_dpm.h"

/* Wepwesents a singwe SCWK step. */
stwuct wv6xx_scwk_stepping
{
    u32 vco_fwequency;
    u32 post_dividew;
};

stwuct wv6xx_pm_hw_state {
	u32 scwks[W600_PM_NUMBEW_OF_ACTIVITY_WEVEWS];
	u32 mcwks[W600_PM_NUMBEW_OF_MCWKS];
	u16 vddc[W600_PM_NUMBEW_OF_VOWTAGE_WEVEWS];
	boow backbias[W600_PM_NUMBEW_OF_VOWTAGE_WEVEWS];
	boow pcie_gen2[W600_PM_NUMBEW_OF_ACTIVITY_WEVEWS];
	u8 high_scwk_index;
	u8 medium_scwk_index;
	u8 wow_scwk_index;
	u8 high_mcwk_index;
	u8 medium_mcwk_index;
	u8 wow_mcwk_index;
	u8 high_vddc_index;
	u8 medium_vddc_index;
	u8 wow_vddc_index;
	u8 wp[W600_PM_NUMBEW_OF_ACTIVITY_WEVEWS];
	u8 wp[W600_PM_NUMBEW_OF_ACTIVITY_WEVEWS];
};

stwuct wv6xx_powew_info {
	/* fwags */
	boow vowtage_contwow;
	boow scwk_ss;
	boow mcwk_ss;
	boow dynamic_ss;
	boow dynamic_pcie_gen2;
	boow thewmaw_pwotection;
	boow dispway_gap;
	boow gfx_cwock_gating;
	/* cwk vawues */
	u32 fb_div_scawe;
	u32 spww_wef_div;
	u32 mpww_wef_div;
	u32 bsu;
	u32 bsp;
	/* */
	u32 active_auto_thwottwe_souwces;
	/* cuwwent powew state */
	u32 westwicted_wevews;
	stwuct wv6xx_pm_hw_state hw;
};

stwuct wv6xx_pw {
	u32 scwk;
	u32 mcwk;
	u16 vddc;
	u32 fwags;
};

stwuct wv6xx_ps {
	stwuct wv6xx_pw high;
	stwuct wv6xx_pw medium;
	stwuct wv6xx_pw wow;
};

#define WV6XX_DEFAUWT_VCWK_FWEQ  40000 /* 10 khz */
#define WV6XX_DEFAUWT_DCWK_FWEQ  30000 /* 10 khz */

#endif
