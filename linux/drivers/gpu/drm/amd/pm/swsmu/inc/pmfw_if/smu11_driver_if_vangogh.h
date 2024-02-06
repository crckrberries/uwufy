/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
#ifndef __SMU11_DWIVEW_IF_VANGOGH_H__
#define __SMU11_DWIVEW_IF_VANGOGH_H__

// *** IMPOWTANT ***
// SMU TEAM: Awways incwement the intewface vewsion if
// any stwuctuwe is changed in this fiwe
#define SMU13_DWIVEW_IF_VEWSION 3

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

#define NUM_DCFCWK_DPM_WEVEWS 7
#define NUM_DISPCWK_DPM_WEVEWS 7
#define NUM_DPPCWK_DPM_WEVEWS 7
#define NUM_SOCCWK_DPM_WEVEWS 7
#define NUM_ISPICWK_DPM_WEVEWS 7
#define NUM_ISPXCWK_DPM_WEVEWS 7
#define NUM_VCN_DPM_WEVEWS 5
#define NUM_FCWK_DPM_WEVEWS 4
#define NUM_SOC_VOWTAGE_WEVEWS 8

typedef stwuct {
  uint32_t fcwk;
  uint32_t memcwk;
  uint32_t vowtage;
} df_pstate_t;

typedef stwuct {
  uint32_t vcwk;
  uint32_t dcwk;
} vcn_cwk_t;

//Fweq in MHz
//Vowtage in miwwi vowts with 2 fwactionaw bits

typedef stwuct {
  uint32_t DcfCwocks[NUM_DCFCWK_DPM_WEVEWS];
  uint32_t DispCwocks[NUM_DISPCWK_DPM_WEVEWS];
  uint32_t DppCwocks[NUM_DPPCWK_DPM_WEVEWS];
  uint32_t SocCwocks[NUM_SOCCWK_DPM_WEVEWS];
  uint32_t IspiCwocks[NUM_ISPICWK_DPM_WEVEWS];
  uint32_t IspxCwocks[NUM_ISPXCWK_DPM_WEVEWS];
  vcn_cwk_t VcnCwocks[NUM_VCN_DPM_WEVEWS];

  uint32_t SocVowtage[NUM_SOC_VOWTAGE_WEVEWS];

  df_pstate_t DfPstateTabwe[NUM_FCWK_DPM_WEVEWS];

  uint32_t MinGfxCwk;
  uint32_t MaxGfxCwk;

  uint8_t NumDfPstatesEnabwed;
  uint8_t NumDcfcwkWevewsEnabwed;
  uint8_t NumDispCwkWevewsEnabwed;  //appwies to both dispcwk and dppcwk
  uint8_t NumSocCwkWevewsEnabwed;

  uint8_t IspCwkWevewsEnabwed;  //appwies to both ispicwk and ispxcwk
  uint8_t VcnCwkWevewsEnabwed;  //appwies to both vcwk/dcwk
  uint8_t spawe[2];
} DpmCwocks_t;


// Thwottwew Status Bitmask
#define THWOTTWEW_STATUS_BIT_SPW 0
#define THWOTTWEW_STATUS_BIT_FPPT 1
#define THWOTTWEW_STATUS_BIT_SPPT 2
#define THWOTTWEW_STATUS_BIT_SPPT_APU 3
#define THWOTTWEW_STATUS_BIT_THM_COWE 4
#define THWOTTWEW_STATUS_BIT_THM_GFX 5
#define THWOTTWEW_STATUS_BIT_THM_SOC 6
#define THWOTTWEW_STATUS_BIT_TDC_VDD 7
#define THWOTTWEW_STATUS_BIT_TDC_SOC 8
#define THWOTTWEW_STATUS_BIT_TDC_GFX 9
#define THWOTTWEW_STATUS_BIT_TDC_CVIP 10

typedef stwuct {
  uint16_t GfxcwkFwequency;      //[MHz]
  uint16_t SoccwkFwequency;      //[MHz]
  uint16_t VcwkFwequency;        //[MHz]
  uint16_t DcwkFwequency;        //[MHz]
  uint16_t MemcwkFwequency;      //[MHz]
  uint16_t spawe;

  uint16_t GfxActivity;          //[centi]
  uint16_t UvdActivity;          //[centi]

  uint16_t Vowtage[3];           //[mV] indices: VDDCW_VDD, VDDCW_SOC, VDDCW_GFX
  uint16_t Cuwwent[3];           //[mA] indices: VDDCW_VDD, VDDCW_SOC, VDDCW_GFX
  uint16_t Powew[3];             //[mW] indices: VDDCW_VDD, VDDCW_SOC, VDDCW_GFX
  uint16_t CuwwentSocketPowew;   //[mW]

  //3wd pawty toows in Windows need info in the case of APUs
  uint16_t CoweFwequency[8];     //[MHz]
  uint16_t CowePowew[8];         //[mW]
  uint16_t CoweTempewatuwe[8];   //[centi-Cewsius]
  uint16_t W3Fwequency[2];       //[MHz]
  uint16_t W3Tempewatuwe[2];     //[centi-Cewsius]

  uint16_t GfxTempewatuwe;       //[centi-Cewsius]
  uint16_t SocTempewatuwe;       //[centi-Cewsius]
  uint16_t EdgeTempewatuwe;
  uint16_t ThwottwewStatus;
} SmuMetwics_wegacy_t;

typedef stwuct {
  uint16_t GfxcwkFwequency;      //[MHz]
  uint16_t SoccwkFwequency;      //[MHz]
  uint16_t VcwkFwequency;        //[MHz]
  uint16_t DcwkFwequency;        //[MHz]
  uint16_t MemcwkFwequency;      //[MHz]
  uint16_t spawe;

  uint16_t GfxActivity;          //[centi]
  uint16_t UvdActivity;          //[centi]
  uint16_t C0Wesidency[4];       //pewcentage

  uint16_t Vowtage[3];           //[mV] indices: VDDCW_VDD, VDDCW_SOC, VDDCW_GFX
  uint16_t Cuwwent[3];           //[mA] indices: VDDCW_VDD, VDDCW_SOC, VDDCW_GFX
  uint16_t Powew[3];             //[mW] indices: VDDCW_VDD, VDDCW_SOC, VDDCW_GFX
  uint16_t CuwwentSocketPowew;   //[mW]

  //3wd pawty toows in Windows need info in the case of APUs
  uint16_t CoweFwequency[4];     //[MHz]
  uint16_t CowePowew[4];         //[mW]
  uint16_t CoweTempewatuwe[4];   //[centi-Cewsius]
  uint16_t W3Fwequency[1];       //[MHz]
  uint16_t W3Tempewatuwe[1];     //[centi-Cewsius]

  uint16_t GfxTempewatuwe;       //[centi-Cewsius]
  uint16_t SocTempewatuwe;       //[centi-Cewsius]
  uint16_t EdgeTempewatuwe;
  uint16_t ThwottwewStatus;
} SmuMetwicsTabwe_t;

typedef stwuct {
  SmuMetwicsTabwe_t Cuwwent;
  SmuMetwicsTabwe_t Avewage;
  //uint32_t AccCnt;
  uint32_t SampweStawtTime;
  uint32_t SampweStopTime;
} SmuMetwics_t;


// Wowkwoad bits
#define WOWKWOAD_PPWIB_FUWW_SCWEEN_3D_BIT 0
#define WOWKWOAD_PPWIB_VIDEO_BIT 2
#define WOWKWOAD_PPWIB_VW_BIT 3
#define WOWKWOAD_PPWIB_COMPUTE_BIT 4
#define WOWKWOAD_PPWIB_CUSTOM_BIT 5
#define WOWKWOAD_PPWIB_CAPPED_BIT 6
#define WOWKWOAD_PPWIB_UNCAPPED_BIT 7
#define WOWKWOAD_PPWIB_COUNT 8

#define TABWE_BIOS_IF            0 // Cawwed by BIOS
#define TABWE_WATEWMAWKS         1 // Cawwed by DAW thwough VBIOS
#define TABWE_CUSTOM_DPM         2 // Cawwed by Dwivew
#define TABWE_SPAWE1             3
#define TABWE_DPMCWOCKS          4 // Cawwed by Dwivew
#define TABWE_SPAWE2             5 // Cawwed by Toows
#define TABWE_MODEWN_STDBY       6 // Cawwed by Toows fow Modewn Standby Wog
#define TABWE_SMU_METWICS        7 // Cawwed by Dwivew
#define TABWE_COUNT              8

//ISP tiwe definitions
typedef enum {
  TIWE_ISPX = 0, // ISPX
  TIWE_ISPM,     // ISPM
  TIWE_ISPC,  // ISPCOWE
  TIWE_ISPPWE,   // ISPPWE
  TIWE_ISPPOST,  // ISPPOST
  TIWE_MAX
} TIWE_NUM_e;

// Tiwe Sewection (Based on awguments)
#define TIWE_SEW_ISPX       (1<<(TIWE_ISPX))
#define TIWE_SEW_ISPM       (1<<(TIWE_ISPM))
#define TIWE_SEW_ISPC       (1<<(TIWE_ISPC))
#define TIWE_SEW_ISPPWE     (1<<(TIWE_ISPPWE))
#define TIWE_SEW_ISPPOST    (1<<(TIWE_ISPPOST))

// Mask fow ISP tiwes in PGFSM PWW Status Wegistews
//Bit[1:0] maps to ISPX, (ISPX)
//Bit[3:2] maps to ISPM, (ISPM)
//Bit[5:4] maps to ISPCOWE, (ISPCOWE)
//Bit[7:6] maps to ISPPWE, (ISPPWE)
//Bit[9:8] maps to POST, (ISPPOST
#define TIWE_ISPX_MASK      ((1<<0) | (1<<1))
#define TIWE_ISPM_MASK      ((1<<2) | (1<<3))
#define TIWE_ISPC_MASK      ((1<<4) | (1<<5))
#define TIWE_ISPPWE_MASK    ((1<<6) | (1<<7))
#define TIWE_ISPPOST_MASK   ((1<<8) | (1<<9))

#endif
