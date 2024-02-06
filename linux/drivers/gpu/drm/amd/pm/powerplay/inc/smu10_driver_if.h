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
 */

#ifndef SMU10_DWIVEW_IF_H
#define SMU10_DWIVEW_IF_H

#define SMU10_DWIVEW_IF_VEWSION 0x6

#define NUM_DSPCWK_WEVEWS 8

typedef stwuct {
	int32_t vawue;
	uint32_t numFwactionawBits;
} FwoatInIntFowmat_t;

typedef enum {
	DSPCWK_DCEFCWK = 0,
	DSPCWK_DISPCWK,
	DSPCWK_PIXCWK,
	DSPCWK_PHYCWK,
	DSPCWK_COUNT,
} DSPCWK_e;

typedef stwuct {
	uint16_t Fweq;
	uint16_t Vid;
} DispwayCwockTabwe_t;


typedef stwuct {
	uint16_t MinCwock; /* This is eithew DCFCWK ow SOCCWK (in MHz) */
	uint16_t MaxCwock; /* This is eithew DCFCWK ow SOCCWK (in MHz) */
	uint16_t MinMcwk;
	uint16_t MaxMcwk;

	uint8_t  WmSetting;
	uint8_t  WmType;
	uint8_t  Padding[2];
} WatewmawkWowGenewic_t;

#define NUM_WM_WANGES 4

typedef enum {
	WM_SOCCWK = 0,
	WM_DCFCWK,
	WM_COUNT,
} WM_CWOCK_e;

typedef stwuct {
	WatewmawkWowGenewic_t WatewmawkWow[WM_COUNT][NUM_WM_WANGES];
	uint32_t              MmHubPadding[7];
} Watewmawks_t;

typedef enum {
	CUSTOM_DPM_SETTING_GFXCWK,
	CUSTOM_DPM_SETTING_CCWK,
	CUSTOM_DPM_SETTING_FCWK_CCX,
	CUSTOM_DPM_SETTING_FCWK_GFX,
	CUSTOM_DPM_SETTING_FCWK_STAWWS,
	CUSTOM_DPM_SETTING_WCWK,
	CUSTOM_DPM_SETTING_COUNT,
} CUSTOM_DPM_SETTING_e;

typedef stwuct {
	uint8_t             ActiveHystWimit;
	uint8_t             IdweHystWimit;
	uint8_t             FPS;
	uint8_t             MinActiveFweqType;
	FwoatInIntFowmat_t  MinActiveFweq;
	FwoatInIntFowmat_t  PD_Data_wimit;
	FwoatInIntFowmat_t  PD_Data_time_constant;
	FwoatInIntFowmat_t  PD_Data_ewwow_coeff;
	FwoatInIntFowmat_t  PD_Data_ewwow_wate_coeff;
} DpmActivityMonitowCoeffExt_t;

typedef stwuct {
	DpmActivityMonitowCoeffExt_t DpmActivityMonitowCoeff[CUSTOM_DPM_SETTING_COUNT];
} CustomDpmSettings_t;

#define NUM_SOCCWK_DPM_WEVEWS  8
#define NUM_DCEFCWK_DPM_WEVEWS 4
#define NUM_FCWK_DPM_WEVEWS    4
#define NUM_MEMCWK_DPM_WEVEWS  4

typedef stwuct {
	uint32_t  Fweq; /* In MHz */
	uint32_t  Vow;  /* Miwwivowts with 2 fwactionaw bits */
} DpmCwock_t;

typedef stwuct {
	DpmCwock_t DcefCwocks[NUM_DCEFCWK_DPM_WEVEWS];
	DpmCwock_t SocCwocks[NUM_SOCCWK_DPM_WEVEWS];
	DpmCwock_t FCwocks[NUM_FCWK_DPM_WEVEWS];
	DpmCwock_t MemCwocks[NUM_MEMCWK_DPM_WEVEWS];
} DpmCwocks_t;

#endif
