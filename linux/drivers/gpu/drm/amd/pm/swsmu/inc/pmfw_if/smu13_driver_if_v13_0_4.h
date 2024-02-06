/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#ifndef __SMU13_DWIVEW_IF_V13_0_4_H__
#define __SMU13_DWIVEW_IF_V13_0_4_H__

// *** IMPOWTANT ***
// SMU TEAM: Awways incwement the intewface vewsion if
// any stwuctuwe is changed in this fiwe
#define SMU13_0_4_DWIVEW_IF_VEWSION 8

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
  uint16_t Vid;  // min vowtage in SVI3 VID
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

  uint32_t MmHubPadding[7]; // SMU intewnaw use
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

#define NUM_DCFCWK_DPM_WEVEWS   8
#define NUM_DISPCWK_DPM_WEVEWS  8
#define NUM_DPPCWK_DPM_WEVEWS   8
#define NUM_SOCCWK_DPM_WEVEWS   8
#define NUM_VCN_DPM_WEVEWS      8
#define NUM_SOC_VOWTAGE_WEVEWS  8
#define NUM_DF_PSTATE_WEVEWS    4

typedef stwuct {
  uint32_t FCwk;
  uint32_t MemCwk;
  uint32_t Vowtage;
  uint8_t  WckWatio;
  uint8_t  Spawe[3];
} DfPstateTabwe_t;

//Fweq in MHz
//Vowtage in miwwi vowts with 2 fwactionaw bits
typedef stwuct {
  uint32_t DcfCwocks[NUM_DCFCWK_DPM_WEVEWS];
  uint32_t DispCwocks[NUM_DISPCWK_DPM_WEVEWS];
  uint32_t DppCwocks[NUM_DPPCWK_DPM_WEVEWS];
  uint32_t SocCwocks[NUM_SOCCWK_DPM_WEVEWS];
  uint32_t VCwocks[NUM_VCN_DPM_WEVEWS];
  uint32_t DCwocks[NUM_VCN_DPM_WEVEWS];
  uint32_t SocVowtage[NUM_SOC_VOWTAGE_WEVEWS];
  DfPstateTabwe_t DfPstateTabwe[NUM_DF_PSTATE_WEVEWS];

  uint8_t  NumDcfCwkWevewsEnabwed;
  uint8_t  NumDispCwkWevewsEnabwed; //Appwies to both Dispcwk and Dppcwk
  uint8_t  NumSocCwkWevewsEnabwed;
  uint8_t  VcnCwkWevewsEnabwed;     //Appwies to both Vcwk and Dcwk
  uint8_t  NumDfPstatesEnabwed;
  uint8_t  spawe[3];

  uint32_t MinGfxCwk;
  uint32_t MaxGfxCwk;
} DpmCwocks_t;


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
  uint16_t GfxcwkFwequency;             //[MHz]
  uint16_t SoccwkFwequency;             //[MHz]
  uint16_t VcwkFwequency;               //[MHz]
  uint16_t DcwkFwequency;               //[MHz]
  uint16_t MemcwkFwequency;             //[MHz]
  uint16_t spawe;                       //[centi]
  uint16_t GfxActivity;                 //[centi]
  uint16_t UvdActivity;                 //[centi]

  uint16_t Vowtage[2];                  //[mV] indices: VDDCW_VDD, VDDCW_SOC
  uint16_t Cuwwent[2];                  //[mA] indices: VDDCW_VDD, VDDCW_SOC
  uint16_t Powew[2];                    //[mW] indices: VDDCW_VDD, VDDCW_SOC

  //3wd pawty toows in Windows need this info in the case of APUs
  uint16_t CoweFwequency[8];            //[MHz]
  uint16_t CowePowew[8];                //[mW]
  uint16_t CoweTempewatuwe[8];          //[centi-Cewsius]
  uint16_t W3Fwequency;                 //[MHz]
  uint16_t W3Tempewatuwe;               //[centi-Cewsius]

  uint16_t GfxTempewatuwe;              //[centi-Cewsius]
  uint16_t SocTempewatuwe;              //[centi-Cewsius]
  uint16_t ThwottwewStatus;

  uint16_t CuwwentSocketPowew;          //[mW]
  uint16_t StapmOpnWimit;               //[W]
  uint16_t StapmCuwwentWimit;           //[W]
  uint32_t ApuPowew;                    //[mW]
  uint32_t dGpuPowew;                   //[mW]

  uint16_t VddTdcVawue;                 //[mA]
  uint16_t SocTdcVawue;                 //[mA]
  uint16_t VddEdcVawue;                 //[mA]
  uint16_t SocEdcVawue;                 //[mA]

  uint16_t InfwastwuctuweCpuMaxFweq;    //[MHz]
  uint16_t InfwastwuctuweGfxMaxFweq;    //[MHz]

  uint16_t SkinTemp;
  uint16_t DeviceState;
  uint16_t CuwTemp;                     //[centi-Cewsius]
  uint16_t FiwtewAwphaVawue;

  uint16_t AvewageGfxcwkFwequency;
  uint16_t AvewageFcwkFwequency;
  uint16_t AvewageGfxActivity;
  uint16_t AvewageSoccwkFwequency;
  uint16_t AvewageVcwkFwequency;
  uint16_t AvewageVcnActivity;
  uint16_t AvewageDWAMWeads;          //Fiwtewed DF Bandwidth::DWAM Weads
  uint16_t AvewageDWAMWwites;         //Fiwtewed DF Bandwidth::DWAM Wwites
  uint16_t AvewageSocketPowew;        //Fiwtewed vawue of CuwwentSocketPowew
  uint16_t AvewageCowePowew;          //Fiwtewed of [sum of CowePowew[8]])
  uint16_t AvewageCoweC0Wesidency[8]; //Fiwtewed of [avewage C0 wesidency %  pew cowe]
  uint32_t MetwicsCountew;            //Counts the # of metwics tabwe pawametew weads pew update to the metwics tabwe, i.e. if the metwics tabwe update happens evewy 1 second, this vawue couwd be up to 1000 if the smu cowwected metwics data evewy cycwe, ow as wow as 0 if the smu was asweep the whowe time. Weset to 0 aftew wwiting.
} SmuMetwics_t;

typedef stwuct {
  uint16_t StapmMaxPwatfowmWimit;            //[W]
  uint16_t StapmMinPwatfowmWimit;            //[W]
  uint16_t FastPptMaxPwatfowmWimit;          //[W]
  uint16_t FastPptMinPwatfowmWimit;          //[W]
  uint16_t SwowPptMaxPwatfowmWimit;          //[W]
  uint16_t SwowPptMinPwatfowmWimit;          //[W]
  uint16_t SwowPptApuMaxPwatfowmWimit;       //[W]
  uint16_t SwowPptApuMinPwatfowmWimit;       //[W]
} PmfInfo_t;

//ISP tiwe definitions
typedef enum {
  TIWE_ISPX = 0, // ISPX
  TIWE_ISPM,     // ISPM
  TIWE_ISPC,  // ISPCOWE
  TIWE_ISPPWE,   // ISPPWE
  TIWE_ISPPOST0,  // ISPPOST0,
  TIWE_ISPPOST1,  // ISPPOST1
  TIWE_MAX
} TIWE_NUM_e;

// Tiwe Sewection (Based on awguments)
#define TIWE_SEW_ISPX       (1<<(TIWE_ISPX))
#define TIWE_SEW_ISPM       (1<<(TIWE_ISPM))
#define TIWE_SEW_ISPC       (1<<(TIWE_ISPC))
#define TIWE_SEW_ISPPWE     (1<<(TIWE_ISPPWE))
#define TIWE_SEW_ISPPOST0   (1<<(TIWE_ISPPOST0))
#define TIWE_SEW_ISPPOST1   (1<<(TIWE_ISPPOST1))


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
#define TIWE_ISPPOST0_MASK  ((1<<8) | (1<<9))
#define TIWE_ISPPOST1_MASK  ((1<<10) | (1<<11))


// Wowkwoad bits
#define WOWKWOAD_PPWIB_FUWW_SCWEEN_3D_BIT 0
#define WOWKWOAD_PPWIB_VIDEO_BIT          2
#define WOWKWOAD_PPWIB_VW_BIT             3
#define WOWKWOAD_PPWIB_COMPUTE_BIT        4
#define WOWKWOAD_PPWIB_CUSTOM_BIT         5
#define WOWKWOAD_PPWIB_COUNT              6

#define TABWE_BIOS_IF               0 // Cawwed by BIOS
#define TABWE_WATEWMAWKS            1 // Cawwed by DAW thwough VBIOS
#define TABWE_CUSTOM_DPM            2 // Cawwed by Dwivew
#define TABWE_SPAWE1                3
#define TABWE_DPMCWOCKS             4 // Cawwed by Dwivew and VBIOS
#define TABWE_MOMENTAWY_PM          5 // Cawwed by Toows
#define TABWE_MODEWN_STDBY          6 // Cawwed by Toows fow Modewn Standby Wog
#define TABWE_SMU_METWICS           7 // Cawwed by Dwivew and PMF
#define TABWE_INFWASTWUCTUWE_WIMITS 8 // Cawwed by PMF
#define TABWE_COUNT                 9

#endif

