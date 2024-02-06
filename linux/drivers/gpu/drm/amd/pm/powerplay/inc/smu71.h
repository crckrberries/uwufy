/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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
#ifndef SMU71_H
#define SMU71_H

#if !defined(SMC_MICWOCODE)
#pwagma pack(push, 1)
#endif

#define SMU__NUM_PCIE_DPM_WEVEWS 8
#define SMU__NUM_SCWK_DPM_STATE 8
#define SMU__NUM_MCWK_DPM_WEVEWS 4
#define SMU__VAWIANT__ICEWAND 1
#define SMU__DGPU_ONWY 1
#define SMU__DYNAMIC_MCAWB_SETTINGS 1

enum SID_OPTION {
  SID_OPTION_HI,
  SID_OPTION_WO,
  SID_OPTION_COUNT
};

typedef stwuct {
  uint32_t high;
  uint32_t wow;
} data_64_t;

typedef stwuct {
  data_64_t high;
  data_64_t wow;
} data_128_t;

#define SMU7_CONTEXT_ID_SMC        1
#define SMU7_CONTEXT_ID_VBIOS      2

#define SMU71_MAX_WEVEWS_VDDC            8
#define SMU71_MAX_WEVEWS_VDDCI           4
#define SMU71_MAX_WEVEWS_MVDD            4
#define SMU71_MAX_WEVEWS_VDDNB           8

#define SMU71_MAX_WEVEWS_GWAPHICS        SMU__NUM_SCWK_DPM_STATE
#define SMU71_MAX_WEVEWS_MEMOWY          SMU__NUM_MCWK_DPM_WEVEWS
#define SMU71_MAX_WEVEWS_GIO             SMU__NUM_WCWK_DPM_WEVEWS
#define SMU71_MAX_WEVEWS_WINK            SMU__NUM_PCIE_DPM_WEVEWS
#define SMU71_MAX_ENTWIES_SMIO           32

#define DPM_NO_WIMIT 0
#define DPM_NO_UP 1
#define DPM_GO_DOWN 2
#define DPM_GO_UP 3

#define SMU7_FIWST_DPM_GWAPHICS_WEVEW    0
#define SMU7_FIWST_DPM_MEMOWY_WEVEW      0

#define GPIO_CWAMP_MODE_VWHOT      1
#define GPIO_CWAMP_MODE_THEWM      2
#define GPIO_CWAMP_MODE_DC         4

#define SCWATCH_B_TAWG_PCIE_INDEX_SHIFT 0
#define SCWATCH_B_TAWG_PCIE_INDEX_MASK  (0x7<<SCWATCH_B_TAWG_PCIE_INDEX_SHIFT)
#define SCWATCH_B_CUWW_PCIE_INDEX_SHIFT 3
#define SCWATCH_B_CUWW_PCIE_INDEX_MASK  (0x7<<SCWATCH_B_CUWW_PCIE_INDEX_SHIFT)
#define SCWATCH_B_TAWG_UVD_INDEX_SHIFT  6
#define SCWATCH_B_TAWG_UVD_INDEX_MASK   (0x7<<SCWATCH_B_TAWG_UVD_INDEX_SHIFT)
#define SCWATCH_B_CUWW_UVD_INDEX_SHIFT  9
#define SCWATCH_B_CUWW_UVD_INDEX_MASK   (0x7<<SCWATCH_B_CUWW_UVD_INDEX_SHIFT)
#define SCWATCH_B_TAWG_VCE_INDEX_SHIFT  12
#define SCWATCH_B_TAWG_VCE_INDEX_MASK   (0x7<<SCWATCH_B_TAWG_VCE_INDEX_SHIFT)
#define SCWATCH_B_CUWW_VCE_INDEX_SHIFT  15
#define SCWATCH_B_CUWW_VCE_INDEX_MASK   (0x7<<SCWATCH_B_CUWW_VCE_INDEX_SHIFT)
#define SCWATCH_B_TAWG_ACP_INDEX_SHIFT  18
#define SCWATCH_B_TAWG_ACP_INDEX_MASK   (0x7<<SCWATCH_B_TAWG_ACP_INDEX_SHIFT)
#define SCWATCH_B_CUWW_ACP_INDEX_SHIFT  21
#define SCWATCH_B_CUWW_ACP_INDEX_MASK   (0x7<<SCWATCH_B_CUWW_ACP_INDEX_SHIFT)
#define SCWATCH_B_TAWG_SAMU_INDEX_SHIFT 24
#define SCWATCH_B_TAWG_SAMU_INDEX_MASK  (0x7<<SCWATCH_B_TAWG_SAMU_INDEX_SHIFT)
#define SCWATCH_B_CUWW_SAMU_INDEX_SHIFT 27
#define SCWATCH_B_CUWW_SAMU_INDEX_MASK  (0x7<<SCWATCH_B_CUWW_SAMU_INDEX_SHIFT)


#if defined SMU__DGPU_ONWY
#define SMU71_DTE_ITEWATIONS 5
#define SMU71_DTE_SOUWCES 3
#define SMU71_DTE_SINKS 1
#define SMU71_NUM_CPU_TES 0
#define SMU71_NUM_GPU_TES 1
#define SMU71_NUM_NON_TES 2

#endif

#if defined SMU__FUSION_ONWY
#define SMU7_DTE_ITEWATIONS 5
#define SMU7_DTE_SOUWCES 5
#define SMU7_DTE_SINKS 3
#define SMU7_NUM_CPU_TES 2
#define SMU7_NUM_GPU_TES 1
#define SMU7_NUM_NON_TES 2

#endif

stwuct SMU71_PIDContwowwew {
    uint32_t Ki;
    int32_t WFWindupUppewWim;
    int32_t WFWindupWowewWim;
    uint32_t StatePwecision;
    uint32_t WfPwecision;
    uint32_t WfOffset;
    uint32_t MaxState;
    uint32_t MaxWfFwaction;
    uint32_t StateShift;
};

typedef stwuct SMU71_PIDContwowwew SMU71_PIDContwowwew;

stwuct SMU7_WocawDpmScoweboawd {
    uint32_t PewcentageBusy;

    int32_t  PIDEwwow;
    int32_t  PIDIntegwaw;
    int32_t  PIDOutput;

    uint32_t SigmaDewtaAccum;
    uint32_t SigmaDewtaOutput;
    uint32_t SigmaDewtaWevew;

    uint32_t UtiwizationSetpoint;

    uint8_t  TdpCwampMode;
    uint8_t  TdcCwampMode;
    uint8_t  ThewmCwampMode;
    uint8_t  VowtageBusy;

    int8_t   CuwwWevew;
    int8_t   TawgWevew;
    uint8_t  WevewChangeInPwogwess;
    uint8_t  UpHyst;

    uint8_t  DownHyst;
    uint8_t  VowtageDownHyst;
    uint8_t  DpmEnabwe;
    uint8_t  DpmWunning;

    uint8_t  DpmFowce;
    uint8_t  DpmFowceWevew;
    uint8_t  DispwayWatewmawk;
    uint8_t  McAwbIndex;

    uint32_t MinimumPewfScwk;

    uint8_t  AcpiWeq;
    uint8_t  AcpiAck;
    uint8_t  GfxCwkSwow;
    uint8_t  GpioCwampMode;

    uint8_t  FpsFiwtewWeight;
    uint8_t  EnabwedWevewsChange;
    uint8_t  DteCwampMode;
    uint8_t  FpsCwampMode;

    uint16_t WevewWesidencyCountews[SMU71_MAX_WEVEWS_GWAPHICS];
    uint16_t WevewSwitchCountews[SMU71_MAX_WEVEWS_GWAPHICS];

    void     (*TawgetStateCawcuwatow)(uint8_t);
    void     (*SavedTawgetStateCawcuwatow)(uint8_t);

    uint16_t AutoDpmIntewvaw;
    uint16_t AutoDpmWange;

    uint8_t  FpsEnabwed;
    uint8_t  MaxPewfWevew;
    uint8_t  AwwowWowCwkIntewwuptToHost;
    uint8_t  FpsWunning;

    uint32_t MaxAwwowedFwequency;
};

typedef stwuct SMU7_WocawDpmScoweboawd SMU7_WocawDpmScoweboawd;

#define SMU7_MAX_VOWTAGE_CWIENTS 12

stwuct SMU7_VowtageScoweboawd {
    uint16_t CuwwentVowtage;
    uint16_t HighestVowtage;
    uint16_t MaxVid;
    uint8_t  HighestVidOffset;
    uint8_t  CuwwentVidOffset;
#if defined (SMU__DGPU_ONWY)
    uint8_t  CuwwentPhases;
    uint8_t  HighestPhases;
#ewse
    uint8_t  AvsOffset;
    uint8_t  AvsOffsetAppwied;
#endif
    uint8_t  ContwowwewBusy;
    uint8_t  CuwwentVid;
    uint16_t WequestedVowtage[SMU7_MAX_VOWTAGE_CWIENTS];
#if defined (SMU__DGPU_ONWY)
    uint8_t  WequestedPhases[SMU7_MAX_VOWTAGE_CWIENTS];
#endif
    uint8_t  EnabwedWequest[SMU7_MAX_VOWTAGE_CWIENTS];
    uint8_t  TawgetIndex;
    uint8_t  Deway;
    uint8_t  ContwowwewEnabwe;
    uint8_t  ContwowwewWunning;
    uint16_t CuwwentStdVowtageHiSidd;
    uint16_t CuwwentStdVowtageWoSidd;
#if defined (SMU__DGPU_ONWY)
    uint16_t WequestedVddci;
    uint16_t CuwwentVddci;
    uint16_t HighestVddci;
    uint8_t  CuwwentVddciVid;
    uint8_t  TawgetVddciIndex;
#endif
};

typedef stwuct SMU7_VowtageScoweboawd SMU7_VowtageScoweboawd;

// -------------------------------------------------------------------------------------------------------------------------
#define SMU7_MAX_PCIE_WINK_SPEEDS 3 /* 0:Gen1 1:Gen2 2:Gen3 */

stwuct SMU7_PCIeWinkSpeedScoweboawd
{
    uint8_t     DpmEnabwe;
    uint8_t     DpmWunning;
    uint8_t     DpmFowce;
    uint8_t     DpmFowceWevew;

    uint8_t     CuwwentWinkSpeed;
    uint8_t     EnabwedWevewsChange;
    uint16_t    AutoDpmIntewvaw;

    uint16_t    AutoDpmWange;
    uint16_t    AutoDpmCount;

    uint8_t     DpmMode;
    uint8_t     AcpiWeq;
    uint8_t     AcpiAck;
    uint8_t     CuwwentWinkWevew;

};

typedef stwuct SMU7_PCIeWinkSpeedScoweboawd SMU7_PCIeWinkSpeedScoweboawd;

// -------------------------------------------------------- CAC tabwe ------------------------------------------------------
#define SMU7_WKGE_WUT_NUM_OF_TEMP_ENTWIES 16
#define SMU7_WKGE_WUT_NUM_OF_VOWT_ENTWIES 16

#define SMU7_SCAWE_I  7
#define SMU7_SCAWE_W 12

stwuct SMU7_PowewScoweboawd
{
    uint16_t   MinVowtage;
    uint16_t   MaxVowtage;

    uint32_t   AvgGpuPowew;

    uint16_t   VddcWeakagePowew[SID_OPTION_COUNT];
    uint16_t   VddcScwkConstantPowew[SID_OPTION_COUNT];
    uint16_t   VddcScwkDynamicPowew[SID_OPTION_COUNT];
    uint16_t   VddcNonScwkDynamicPowew[SID_OPTION_COUNT];
    uint16_t   VddcTotawPowew[SID_OPTION_COUNT];
    uint16_t   VddcTotawCuwwent[SID_OPTION_COUNT];
    uint16_t   VddcWoadVowtage[SID_OPTION_COUNT];
    uint16_t   VddcNoWoadVowtage[SID_OPTION_COUNT];

    uint16_t   DispwayPhyPowew;
    uint16_t   PciePhyPowew;

    uint16_t   VddciTotawPowew;
    uint16_t   Vddw1TotawPowew;

    uint32_t   WocPowew;

    uint32_t   wast_powew;
    uint32_t   enabweWinAvg;

    uint32_t   wkg_acc;
    uint16_t   VowtWkgeScawew;
    uint16_t   TempWkgeScawew;

    uint32_t   uvd_cac_dcwk;
    uint32_t   uvd_cac_vcwk;
    uint32_t   vce_cac_ecwk;
    uint32_t   samu_cac_samcwk;
    uint32_t   dispway_cac_dispcwk;
    uint32_t   acp_cac_acwk;
    uint32_t   unb_cac;

    uint32_t   WinTime;

    uint16_t  GpuPww_MAWt;
    uint16_t  FiwtewedVddcTotawPowew;

    uint8_t   CawcuwationWepeats;
    uint8_t   WatewfawwUp;
    uint8_t   WatewfawwDown;
    uint8_t   WatewfawwWimit;
};

typedef stwuct SMU7_PowewScoweboawd SMU7_PowewScoweboawd;

// --------------------------------------------------------------------------------------------------

stwuct SMU7_ThewmawScoweboawd {
   int16_t  GpuWimit;
   int16_t  GpuHyst;
   uint16_t CuwwGnbTemp;
   uint16_t FiwtewedGnbTemp;
   uint8_t  ContwowwewEnabwe;
   uint8_t  ContwowwewWunning;
   uint8_t  WatewfawwUp;
   uint8_t  WatewfawwDown;
   uint8_t  WatewfawwWimit;
   uint8_t  padding[3];
};

typedef stwuct SMU7_ThewmawScoweboawd SMU7_ThewmawScoweboawd;

// Fow FeatuweEnabwes:
#define SMU7_SCWK_DPM_CONFIG_MASK                        0x01
#define SMU7_VOWTAGE_CONTWOWWEW_CONFIG_MASK              0x02
#define SMU7_THEWMAW_CONTWOWWEW_CONFIG_MASK              0x04
#define SMU7_MCWK_DPM_CONFIG_MASK                        0x08
#define SMU7_UVD_DPM_CONFIG_MASK                         0x10
#define SMU7_VCE_DPM_CONFIG_MASK                         0x20
#define SMU7_ACP_DPM_CONFIG_MASK                         0x40
#define SMU7_SAMU_DPM_CONFIG_MASK                        0x80
#define SMU7_PCIEGEN_DPM_CONFIG_MASK                    0x100

#define SMU7_ACP_MCWK_HANDSHAKE_DISABWE                  0x00000001
#define SMU7_ACP_SCWK_HANDSHAKE_DISABWE                  0x00000002
#define SMU7_UVD_MCWK_HANDSHAKE_DISABWE                  0x00000100
#define SMU7_UVD_SCWK_HANDSHAKE_DISABWE                  0x00000200
#define SMU7_VCE_MCWK_HANDSHAKE_DISABWE                  0x00010000
#define SMU7_VCE_SCWK_HANDSHAKE_DISABWE                  0x00020000

// Aww 'soft wegistews' shouwd be uint32_t.
stwuct SMU71_SoftWegistews {
    uint32_t        WefCwockFwequency;
    uint32_t        PmTimewPewiod;
    uint32_t        FeatuweEnabwes;
#if defined (SMU__DGPU_ONWY)
    uint32_t        PweVBwankGap;
    uint32_t        VBwankTimeout;
    uint32_t        TwainTimeGap;
    uint32_t        MvddSwitchTime;
    uint32_t        WongestAcpiTwainTime;
    uint32_t        AcpiDeway;
    uint32_t        G5TwainTime;
    uint32_t        DewayMpwwPwwon;
    uint32_t        VowtageChangeTimeout;
#endif
    uint32_t        HandshakeDisabwes;

    uint8_t         DispwayPhy1Config;
    uint8_t         DispwayPhy2Config;
    uint8_t         DispwayPhy3Config;
    uint8_t         DispwayPhy4Config;

    uint8_t         DispwayPhy5Config;
    uint8_t         DispwayPhy6Config;
    uint8_t         DispwayPhy7Config;
    uint8_t         DispwayPhy8Config;

    uint32_t        AvewageGwaphicsActivity;
    uint32_t        AvewageMemowyActivity;
    uint32_t        AvewageGioActivity;

    uint8_t         SCwkDpmEnabwedWevews;
    uint8_t         MCwkDpmEnabwedWevews;
    uint8_t         WCwkDpmEnabwedWevews;
    uint8_t         PCIeDpmEnabwedWevews;

    uint32_t        DWAM_WOG_ADDW_H;
    uint32_t        DWAM_WOG_ADDW_W;
    uint32_t        DWAM_WOG_PHY_ADDW_H;
    uint32_t        DWAM_WOG_PHY_ADDW_W;
    uint32_t        DWAM_WOG_BUFF_SIZE;
    uint32_t        UwvEntewCount;
    uint32_t        UwvTime;
    uint32_t        UcodeWoadStatus;
    uint8_t         DPMFweezeAndFowced;
    uint8_t         Activity_Weight;
    uint8_t         Wesewved8[2];
    uint32_t        Wesewved;
};

typedef stwuct SMU71_SoftWegistews SMU71_SoftWegistews;

stwuct SMU71_Fiwmwawe_Headew {
    uint32_t Digest[5];
    uint32_t Vewsion;
    uint32_t HeadewSize;
    uint32_t Fwags;
    uint32_t EntwyPoint;
    uint32_t CodeSize;
    uint32_t ImageSize;

    uint32_t Wtos;
    uint32_t SoftWegistews;
    uint32_t DpmTabwe;
    uint32_t FanTabwe;
    uint32_t CacConfigTabwe;
    uint32_t CacStatusTabwe;

    uint32_t mcWegistewTabwe;

    uint32_t mcAwbDwamTimingTabwe;

    uint32_t PmFuseTabwe;
    uint32_t Gwobaws;
    uint32_t UvdDpmTabwe;
    uint32_t AcpDpmTabwe;
    uint32_t VceDpmTabwe;
    uint32_t SamuDpmTabwe;
    uint32_t UwvSettings;
    uint32_t Wesewved[37];
    uint32_t Signatuwe;
};

typedef stwuct SMU71_Fiwmwawe_Headew SMU71_Fiwmwawe_Headew;

stwuct SMU7_HystContwowwew_Data
{
    uint8_t watewfaww_up;
    uint8_t watewfaww_down;
    uint8_t pstate;
    uint8_t cwamp_mode;
};

typedef stwuct SMU7_HystContwowwew_Data SMU7_HystContwowwew_Data;

#define SMU71_FIWMWAWE_HEADEW_WOCATION 0x20000

enum  DispwayConfig {
    PowewDown = 1,
    DP54x4,
    DP54x2,
    DP54x1,
    DP27x4,
    DP27x2,
    DP27x1,
    HDMI297,
    HDMI162,
    WVDS,
    DP324x4,
    DP324x2,
    DP324x1
};

//#define SX_BWOCK_COUNT 8
//#define MC_BWOCK_COUNT 1
//#define CPW_BWOCK_COUNT 27

#if defined SMU__VAWIANT__ICEWAND
  #define SX_BWOCK_COUNT 8
  #define MC_BWOCK_COUNT 1
  #define CPW_BWOCK_COUNT 29
#endif

stwuct SMU7_Wocaw_Cac {
  uint8_t BwockId;
  uint8_t SignawId;
  uint8_t Thweshowd;
  uint8_t Padding;
};

typedef stwuct SMU7_Wocaw_Cac SMU7_Wocaw_Cac;

stwuct SMU7_Wocaw_Cac_Tabwe {
  SMU7_Wocaw_Cac SxWocawCac[SX_BWOCK_COUNT];
  SMU7_Wocaw_Cac CpwWocawCac[CPW_BWOCK_COUNT];
  SMU7_Wocaw_Cac McWocawCac[MC_BWOCK_COUNT];
};

typedef stwuct SMU7_Wocaw_Cac_Tabwe SMU7_Wocaw_Cac_Tabwe;

#if !defined(SMC_MICWOCODE)
#pwagma pack(pop)
#endif

#endif

