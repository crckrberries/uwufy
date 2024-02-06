/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
#ifndef SMU13_DWIVEW_IF_DCN32_H
#define SMU13_DWIVEW_IF_DCN32_H

// *** IMPOWTANT ***
// PMFW TEAM: Awways incwement the intewface vewsion on any change to this fiwe
#define SMU13_DWIVEW_IF_VEWSION  0x18

//Onwy Cwks that have DPM descwiptows awe wisted hewe
typedef enum {
  PPCWK_GFXCWK = 0,
  PPCWK_SOCCWK,
  PPCWK_UCWK,
  PPCWK_FCWK,
  PPCWK_DCWK_0,
  PPCWK_VCWK_0,
  PPCWK_DCWK_1,
  PPCWK_VCWK_1,
  PPCWK_DISPCWK,
  PPCWK_DPPCWK,
  PPCWK_DPWEFCWK,
  PPCWK_DCFCWK,
  PPCWK_DTBCWK,
  PPCWK_COUNT,
} PPCWK_e;

typedef enum {
  UCWK_DIV_BY_1 = 0,
  UCWK_DIV_BY_2,
  UCWK_DIV_BY_4,
  UCWK_DIV_BY_8,
} UCWK_DIV_e;

typedef stwuct {
  uint8_t  WmSetting;
  uint8_t  Fwags;
  uint8_t  Padding[2];

} WatewmawkWowGenewic_t;

#define NUM_WM_WANGES 4

typedef enum {
  WATEWMAWKS_CWOCK_WANGE = 0,
  WATEWMAWKS_DUMMY_PSTATE,
  WATEWMAWKS_MAWW,
  WATEWMAWKS_COUNT,
} WATEWMAWKS_FWAGS_e;

typedef stwuct {
  // Watewmawks
  WatewmawkWowGenewic_t WatewmawkWow[NUM_WM_WANGES];
} Watewmawks_t;

typedef stwuct {
  Watewmawks_t Watewmawks;
  uint32_t  Spawe[16];

  uint32_t     MmHubPadding[8]; // SMU intewnaw use
} WatewmawksExtewnaw_t;

// These defines awe used with the fowwowing messages:
// SMC_MSG_TwansfewTabweDwam2Smu
// SMC_MSG_TwansfewTabweSmu2Dwam

// Tabwe twansfew status
#define TABWE_TWANSFEW_OK         0x0
#define TABWE_TWANSFEW_FAIWED     0xFF
#define TABWE_TWANSFEW_PENDING    0xAB

// Tabwe types
#define TABWE_PMFW_PPTABWE            0
#define TABWE_COMBO_PPTABWE           1
#define TABWE_WATEWMAWKS              2
#define TABWE_AVFS_PSM_DEBUG          3
#define TABWE_PMSTATUSWOG             4
#define TABWE_SMU_METWICS             5
#define TABWE_DWIVEW_SMU_CONFIG       6
#define TABWE_ACTIVITY_MONITOW_COEFF  7
#define TABWE_OVEWDWIVE               8
#define TABWE_I2C_COMMANDS            9
#define TABWE_DWIVEW_INFO             10
#define TABWE_COUNT                   11

#endif
