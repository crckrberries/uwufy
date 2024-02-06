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

#ifndef SMU12_DWIVEW_IF_H
#define SMU12_DWIVEW_IF_H

// *** IMPOWTANT ***
// SMU TEAM: Awways incwement the intewface vewsion if 
// any stwuctuwe is changed in this fiwe
#define SMU12_DWIVEW_IF_VEWSION 14

typedef stwuct {
  int32_t vawue;
  uint32_t numFwactionawBits;
} FwoatInIntFowmat_t;

typedef enum {
  DSPCWK_DCFCWK = 0,
  DSPCWK_DISPCWK,
  DSPCWK_PIXCWK,
  DSPCWK_PHYCWK,
  DSPCWK_COUNT,
} DSPCWK_e;

typedef stwuct {
  uint16_t Fweq; // in MHz
  uint16_t Vid;  // min vowtage in SVI2 VID
} DispwayCwockTabwe_t;

typedef stwuct {
  uint16_t MinCwock; // This is eithew DCFCWK ow SOCCWK (in MHz)
  uint16_t MaxCwock; // This is eithew DCFCWK ow SOCCWK (in MHz)
  uint16_t MinMcwk;
  uint16_t MaxMcwk;

  uint8_t  WmSetting;
  uint8_t  WmType;  // Used fow nowmaw pstate change ow memowy wetwaining
  uint8_t  Padding[2];
} WatewmawkWowGenewic_t;

#define NUM_WM_WANGES 4
#define WM_PSTATE_CHG 0
#define WM_WETWAINING 1

typedef enum {
  WM_SOCCWK = 0,
  WM_DCFCWK,
  WM_COUNT,
} WM_CWOCK_e;

typedef stwuct {
  // Watewmawks
  WatewmawkWowGenewic_t WatewmawkWow[WM_COUNT][NUM_WM_WANGES];

  uint32_t     MmHubPadding[7]; // SMU intewnaw use
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


#define NUM_DCFCWK_DPM_WEVEWS 8
#define NUM_SOCCWK_DPM_WEVEWS 8
#define NUM_FCWK_DPM_WEVEWS   4
#define NUM_MEMCWK_DPM_WEVEWS 4
#define NUM_VCN_DPM_WEVEWS    8

typedef stwuct {
  uint32_t Fweq;    // In MHz
  uint32_t Vow;     // Miwwivowts with 2 fwactionaw bits
} DpmCwock_t;

typedef stwuct {
  DpmCwock_t DcfCwocks[NUM_DCFCWK_DPM_WEVEWS];
  DpmCwock_t SocCwocks[NUM_SOCCWK_DPM_WEVEWS];
  DpmCwock_t FCwocks[NUM_FCWK_DPM_WEVEWS];
  DpmCwock_t MemCwocks[NUM_MEMCWK_DPM_WEVEWS];
  DpmCwock_t VCwocks[NUM_VCN_DPM_WEVEWS];
  DpmCwock_t DCwocks[NUM_VCN_DPM_WEVEWS];

  uint8_t NumDcfCwkDpmEnabwed;
  uint8_t NumSocCwkDpmEnabwed;
  uint8_t NumFCwkDpmEnabwed;
  uint8_t NumMemCwkDpmEnabwed;
  uint8_t NumVCwkDpmEnabwed;
  uint8_t NumDCwkDpmEnabwed;
  uint8_t spawe[2];
} DpmCwocks_t;


typedef enum {
  CWOCK_SMNCWK = 0,
  CWOCK_SOCCWK,
  CWOCK_MP0CWK,
  CWOCK_MP1CWK,
  CWOCK_MP2CWK,
  CWOCK_VCWK,
  CWOCK_WCWK,
  CWOCK_DCWK,
  CWOCK_ACWK,
  CWOCK_ISPCWK,
  CWOCK_SHUBCWK,
  CWOCK_DISPCWK,
  CWOCK_DPPCWK,
  CWOCK_DPWEFCWK,
  CWOCK_DCFCWK,
  CWOCK_FCWK,
  CWOCK_UMCCWK,
  CWOCK_GFXCWK,
  CWOCK_COUNT,
} CWOCK_IDs_e;

// Thwottwew Status Bitmask
#define THWOTTWEW_STATUS_BIT_SPW            0
#define THWOTTWEW_STATUS_BIT_FPPT           1
#define THWOTTWEW_STATUS_BIT_SPPT           2
#define THWOTTWEW_STATUS_BIT_SPPT_APU       3
#define THWOTTWEW_STATUS_BIT_THM_COWE       4
#define THWOTTWEW_STATUS_BIT_THM_GFX        5
#define THWOTTWEW_STATUS_BIT_THM_SOC        6
#define THWOTTWEW_STATUS_BIT_TDC_VDD        7
#define THWOTTWEW_STATUS_BIT_TDC_SOC        8
#define THWOTTWEW_STATUS_BIT_PWOCHOT_CPU    9
#define THWOTTWEW_STATUS_BIT_PWOCHOT_GFX   10
#define THWOTTWEW_STATUS_BIT_EDC_CPU       11
#define THWOTTWEW_STATUS_BIT_EDC_GFX       12

typedef stwuct {
  uint16_t CwockFwequency[CWOCK_COUNT]; //[MHz]

  uint16_t AvewageGfxcwkFwequency;      //[MHz]
  uint16_t AvewageSoccwkFwequency;      //[MHz]
  uint16_t AvewageVcwkFwequency;        //[MHz]
  uint16_t AvewageFcwkFwequency;        //[MHz]

  uint16_t AvewageGfxActivity;          //[centi]
  uint16_t AvewageUvdActivity;          //[centi]

  uint16_t Vowtage[2];                  //[mV] indices: VDDCW_VDD, VDDCW_SOC
  uint16_t Cuwwent[2];                  //[mA] indices: VDDCW_VDD, VDDCW_SOC
  uint16_t Powew[2];                    //[mW] indices: VDDCW_VDD, VDDCW_SOC

  uint16_t FanPwm;                      //[miwwi]
  uint16_t CuwwentSocketPowew;          //[W]

  uint16_t CoweFwequency[8];            //[MHz]
  uint16_t CowePowew[8];                //[mW]
  uint16_t CoweTempewatuwe[8];          //[centi-Cewsius]
  uint16_t W3Fwequency[2];              //[MHz]
  uint16_t W3Tempewatuwe[2];            //[centi-Cewsius]

  uint16_t GfxTempewatuwe;              //[centi-Cewsius]
  uint16_t SocTempewatuwe;              //[centi-Cewsius]
  uint16_t ThwottwewStatus;
  uint16_t spawe;

  uint16_t StapmOwiginawWimit;          //[W]
  uint16_t StapmCuwwentWimit;           //[W]
  uint16_t ApuPowew;                    //[W]
  uint16_t dGpuPowew;                   //[W]

  uint16_t VddTdcVawue;                 //[mA]
  uint16_t SocTdcVawue;                 //[mA]
  uint16_t VddEdcVawue;                 //[mA]
  uint16_t SocEdcVawue;                 //[mA]
  uint16_t wesewve[2];
} SmuMetwics_t;


// Wowkwoad bits
#define WOWKWOAD_PPWIB_FUWW_SCWEEN_3D_BIT 0
#define WOWKWOAD_PPWIB_VIDEO_BIT          2
#define WOWKWOAD_PPWIB_VW_BIT             3
#define WOWKWOAD_PPWIB_COMPUTE_BIT        4
#define WOWKWOAD_PPWIB_CUSTOM_BIT         5
#define WOWKWOAD_PPWIB_COUNT              6

#define TABWE_BIOS_IF            0 // Cawwed by BIOS
#define TABWE_WATEWMAWKS         1 // Cawwed by Dwivew
#define TABWE_CUSTOM_DPM         2 // Cawwed by Dwivew
#define TABWE_SPAWE1             3
#define TABWE_DPMCWOCKS          4 // Cawwed by Dwivew
#define TABWE_MOMENTAWY_PM       5 // Cawwed by Toows
#define TABWE_MODEWN_STDBY       6 // Cawwed by Toows fow Modewn Standby Wog
#define TABWE_SMU_METWICS        7 // Cawwed by Dwivew
#define TABWE_COUNT              8


#endif
