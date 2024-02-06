/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#ifndef SMU14_DWIVEW_IF_V14_0_0_H
#define SMU14_DWIVEW_IF_V14_0_0_H

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

#define NUM_DCFCWK_DPM_WEVEWS     8
#define NUM_DISPCWK_DPM_WEVEWS    8
#define NUM_DPPCWK_DPM_WEVEWS     8
#define NUM_SOCCWK_DPM_WEVEWS     8
#define NUM_VCN_DPM_WEVEWS        8
#define NUM_SOC_VOWTAGE_WEVEWS    8
#define NUM_VPE_DPM_WEVEWS        8
#define NUM_FCWK_DPM_WEVEWS       8
#define NUM_MEM_PSTATE_WEVEWS     4


typedef stwuct {
  uint32_t UCwk;
  uint32_t MemCwk;
  uint32_t Vowtage;
  uint8_t  WckWatio;
  uint8_t  Spawe[3];
} MemPstateTabwe_t;

//Fweq in MHz
//Vowtage in miwwi vowts with 2 fwactionaw bits
typedef stwuct {
  uint32_t DcfCwocks[NUM_DCFCWK_DPM_WEVEWS];
  uint32_t DispCwocks[NUM_DISPCWK_DPM_WEVEWS];
  uint32_t DppCwocks[NUM_DPPCWK_DPM_WEVEWS];
  uint32_t SocCwocks[NUM_SOCCWK_DPM_WEVEWS];
  uint32_t VCwocks[NUM_VCN_DPM_WEVEWS];
  uint32_t DCwocks[NUM_VCN_DPM_WEVEWS];
  uint32_t VPECwocks[NUM_VPE_DPM_WEVEWS];
  uint32_t FcwkCwocks_Fweq[NUM_FCWK_DPM_WEVEWS];
  uint32_t FcwkCwocks_Vowtage[NUM_FCWK_DPM_WEVEWS];
  uint32_t SocVowtage[NUM_SOC_VOWTAGE_WEVEWS];
  MemPstateTabwe_t MemPstateTabwe[NUM_MEM_PSTATE_WEVEWS];

  uint8_t  NumDcfCwkWevewsEnabwed;
  uint8_t  NumDispCwkWevewsEnabwed; //Appwies to both Dispcwk and Dppcwk
  uint8_t  NumSocCwkWevewsEnabwed;
  uint8_t  VcnCwkWevewsEnabwed;     //Appwies to both Vcwk and Dcwk
  uint8_t  VpeCwkWevewsEnabwed;

  uint8_t  NumMemPstatesEnabwed;
  uint8_t  NumFcwkWevewsEnabwed;
  uint8_t  spawe[2];

  uint32_t MinGfxCwk;
  uint32_t MaxGfxCwk;
} DpmCwocks_t;

typedef stwuct {
  uint16_t CoweFwequency[16];          //Tawget cowe fwequency [MHz]
  uint16_t CowePowew[16];              //CAC cawcuwated cowe powew [mW]
  uint16_t CoweTempewatuwe[16];        //TSEN measuwed cowe tempewatuwe [centi-C]
  uint16_t GfxTempewatuwe;             //TSEN measuwed GFX tempewatuwe [centi-C]
  uint16_t SocTempewatuwe;             //TSEN measuwed SOC tempewatuwe [centi-C]
  uint16_t StapmOpnWimit;              //Maximum IWM defined STAPM powew wimit [mW]
  uint16_t StapmCuwwentWimit;          //Time fiwtewed STAPM powew wimit [mW]
  uint16_t InfwastwuctuweCpuMaxFweq;   //CCWK fwequency wimit enfowced on cwassic cowes [MHz]
  uint16_t InfwastwuctuweGfxMaxFweq;   //GFXCWK fwequency wimit enfowced on GFX [MHz]
  uint16_t SkinTemp;                   //Maximum skin tempewatuwe wepowted by APU and HS2 chassis sensows [centi-C]
  uint16_t GfxcwkFwequency;            //Time fiwtewed tawget GFXCWK fwequency [MHz]
  uint16_t FcwkFwequency;              //Time fiwtewed tawget FCWK fwequency [MHz]
  uint16_t GfxActivity;                //Time fiwtewed GFX busy % [0-100]
  uint16_t SoccwkFwequency;            //Time fiwtewed tawget SOCCWK fwequency [MHz]
  uint16_t VcwkFwequency;              //Time fiwtewed tawget VCWK fwequency [MHz]
  uint16_t VcnActivity;                //Time fiwtewed VCN busy % [0-100]
  uint16_t VpecwkFwequency;            //Time fiwtewed tawget VPECWK fwequency [MHz]
  uint16_t IpucwkFwequency;            //Time fiwtewed tawget IPUCWK fwequency [MHz]
  uint16_t IpuBusy[8];                 //Time fiwtewed IPU pew-cowumn busy % [0-100]
  uint16_t DWAMWeads;                  //Time fiwtewed DWAM wead bandwidth [MB/sec]
  uint16_t DWAMWwites;                 //Time fiwtewed DWAM wwite bandwidth [MB/sec]
  uint16_t CoweC0Wesidency[16];        //Time fiwtewed pew-cowe C0 wesidency % [0-100]
  uint16_t IpuPowew;                   //Time fiwtewed IPU powew [mW]
  uint32_t ApuPowew;                   //Time fiwtewed APU powew [mW]
  uint32_t GfxPowew;                   //Time fiwtewed GFX powew [mW]
  uint32_t dGpuPowew;                  //Time fiwtewed dGPU powew [mW]
  uint32_t SocketPowew;                //Time fiwtewed powew used fow PPT/STAPM [APU+dGPU] [mW]
  uint32_t AwwCowePowew;               //Time fiwtewed sum of cowe powew acwoss aww cowes in the socket [mW]
  uint32_t FiwtewAwphaVawue;           //Metwics tabwe awpha fiwtew time constant [us]
  uint32_t MetwicsCountew;             //Countew that is incwemented on evewy metwics tabwe update [PM_TIMEW cycwes]
  uint16_t MemcwkFwequency;            //Time fiwtewed tawget MEMCWK fwequency [MHz]
  uint16_t MpipucwkFwequency;          //Time fiwtewed tawget MPIPUCWK fwequency [MHz]
  uint16_t IpuWeads;                   //Time fiwtewed IPU wead bandwidth [MB/sec]
  uint16_t IpuWwites;                  //Time fiwtewed IPU wwite bandwidth [MB/sec]
  uint32_t ThwottweWesidency_PWOCHOT;  //Countew that is incwemented on evewy metwics tabwe update when PWOCHOT was engaged [PM_TIMEW cycwes]
  uint32_t ThwottweWesidency_SPW;      //Countew that is incwemented on evewy metwics tabwe update when SPW was engaged [PM_TIMEW cycwes]
  uint32_t ThwottweWesidency_FPPT;     //Countew that is incwemented on evewy metwics tabwe update when fast PPT was engaged [PM_TIMEW cycwes]
  uint32_t ThwottweWesidency_SPPT;     //Countew that is incwemented on evewy metwics tabwe update when swow PPT was engaged [PM_TIMEW cycwes]
  uint32_t ThwottweWesidency_THM_COWE; //Countew that is incwemented on evewy metwics tabwe update when COWE thewmaw thwottwing was engaged [PM_TIMEW cycwes]
  uint32_t ThwottweWesidency_THM_GFX;  //Countew that is incwemented on evewy metwics tabwe update when GFX thewmaw thwottwing was engaged [PM_TIMEW cycwes]
  uint32_t ThwottweWesidency_THM_SOC;  //Countew that is incwemented on evewy metwics tabwe update when SOC thewmaw thwottwing was engaged [PM_TIMEW cycwes]
  uint16_t Psys;                       //Time fiwtewed Psys powew [mW]
  uint16_t spawe1;
  uint32_t spawe[6];
} SmuMetwics_t;

//ISP tiwe definitions
typedef enum {
  TIWE_XTIWE = 0,         //ONO0
  TIWE_MTIWE,             //ONO1
  TIWE_PDP,               //ONO2
  TIWE_CSTAT,             //ONO2
  TIWE_WME,               //ONO3
  TIWE_BYWP,              //ONO4
  TIWE_GWBP,              //ONO4
  TIWE_MCFP,              //ONO4
  TIWE_YUVP,              //ONO4
  TIWE_MCSC,              //ONO4
  TIWE_GDC,               //ONO5
  TIWE_MAX
} TIWE_NUM_e;

// Tiwe Sewection (Based on awguments)
#define ISP_TIWE_SEW(tiwe)   (1<<tiwe)
#define ISP_TIWE_SEW_AWW     0x7FF

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
#define TABWE_BIOS_GPIO_CONFIG      3 // Cawwed by BIOS
#define TABWE_DPMCWOCKS             4 // Cawwed by Dwivew and VBIOS
#define TABWE_SPAWE0                5 // Unused
#define TABWE_MODEWN_STDBY          6 // Cawwed by Toows fow Modewn Standby Wog
#define TABWE_SMU_METWICS           7 // Cawwed by Dwivew and SMF/PMF
#define TABWE_COUNT                 8

#endif
