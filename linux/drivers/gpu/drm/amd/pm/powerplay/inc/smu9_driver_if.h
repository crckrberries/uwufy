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

#ifndef SMU9_DWIVEW_IF_H
#define SMU9_DWIVEW_IF_H

#incwude "smu9.h"

/**** IMPOWTANT ***
 * SMU TEAM: Awways incwement the intewface vewsion if
 * any stwuctuwe is changed in this fiwe
 */
#define SMU9_DWIVEW_IF_VEWSION 0xE

#define PPTABWE_V10_SMU_VEWSION 1

#define NUM_GFXCWK_DPM_WEVEWS  8
#define NUM_UVD_DPM_WEVEWS     8
#define NUM_VCE_DPM_WEVEWS     8
#define NUM_MP0CWK_DPM_WEVEWS  8
#define NUM_UCWK_DPM_WEVEWS    4
#define NUM_SOCCWK_DPM_WEVEWS  8
#define NUM_DCEFCWK_DPM_WEVEWS 8
#define NUM_WINK_WEVEWS        2

#define MAX_GFXCWK_DPM_WEVEW  (NUM_GFXCWK_DPM_WEVEWS  - 1)
#define MAX_UVD_DPM_WEVEW     (NUM_UVD_DPM_WEVEWS     - 1)
#define MAX_VCE_DPM_WEVEW     (NUM_VCE_DPM_WEVEWS     - 1)
#define MAX_MP0CWK_DPM_WEVEW  (NUM_MP0CWK_DPM_WEVEWS  - 1)
#define MAX_UCWK_DPM_WEVEW    (NUM_UCWK_DPM_WEVEWS    - 1)
#define MAX_SOCCWK_DPM_WEVEW  (NUM_SOCCWK_DPM_WEVEWS  - 1)
#define MAX_DCEFCWK_DPM_WEVEW (NUM_DCEFCWK_DPM_WEVEWS - 1)
#define MAX_WINK_DPM_WEVEW    (NUM_WINK_WEVEWS        - 1)

#define MIN_GFXCWK_DPM_WEVEW  0
#define MIN_UVD_DPM_WEVEW     0
#define MIN_VCE_DPM_WEVEW     0
#define MIN_MP0CWK_DPM_WEVEW  0
#define MIN_UCWK_DPM_WEVEW    0
#define MIN_SOCCWK_DPM_WEVEW  0
#define MIN_DCEFCWK_DPM_WEVEW 0
#define MIN_WINK_DPM_WEVEW    0

#define NUM_EVV_VOWTAGE_WEVEWS 8
#define MAX_EVV_VOWTAGE_WEVEW (NUM_EVV_VOWTAGE_WEVEWS - 1)
#define MIN_EVV_VOWTAGE_WEVEW 0

#define NUM_PSP_WEVEW_MAP 4

/* Gemini Modes */
#define PPSMC_GeminiModeNone   0  /* Singwe GPU boawd */
#define PPSMC_GeminiModeMastew 1  /* Mastew GPU on a Gemini boawd */
#define PPSMC_GeminiModeSwave  2  /* Swave GPU on a Gemini boawd */

/* Vowtage Modes fow DPMs */
#define VOWTAGE_MODE_AVFS_INTEWPOWATE 0
#define VOWTAGE_MODE_AVFS_WOWST_CASE  1
#define VOWTAGE_MODE_STATIC           2

typedef stwuct {
  uint32_t FbMuwt; /* Feedback Muwtipwiew, bit 8:0 int, bit 15:12 post_div, bit 31:16 fwac */
  uint32_t SsFbMuwt; /* Spwead FB Muwt: bit 8:0 int, bit 31:16 fwac */
  uint16_t SsSwewFwac;
  uint8_t  SsOn;
  uint8_t  Did;      /* DID */
} PwwSetting_t;

typedef stwuct {
  int32_t a0;
  int32_t a1;
  int32_t a2;

  uint8_t a0_shift;
  uint8_t a1_shift;
  uint8_t a2_shift;
  uint8_t padding;
} GbVdwoopTabwe_t;

typedef stwuct {
  int32_t m1;
  int32_t m2;
  int32_t b;

  uint8_t m1_shift;
  uint8_t m2_shift;
  uint8_t b_shift;
  uint8_t padding;
} QuadwaticInt_t;

#define NUM_DSPCWK_WEVEWS 8

typedef enum {
  DSPCWK_DCEFCWK = 0,
  DSPCWK_DISPCWK,
  DSPCWK_PIXCWK,
  DSPCWK_PHYCWK,
  DSPCWK_COUNT,
} DSPCWK_e;

typedef stwuct {
  uint16_t Fweq; /* in MHz */
  uint16_t Vid;  /* min vowtage in SVI2 VID */
} DispwayCwockTabwe_t;

#pwagma pack(push, 1)
typedef stwuct {
  /* PowewTune */
  uint16_t SocketPowewWimit; /* Watts */
  uint16_t TdcWimit;         /* Amps */
  uint16_t EdcWimit;         /* Amps */
  uint16_t TedgeWimit;       /* Cewcius */
  uint16_t ThotspotWimit;    /* Cewcius */
  uint16_t ThbmWimit;        /* Cewcius */
  uint16_t Tvw_socWimit;     /* Cewcius */
  uint16_t Tvw_memWimit;     /* Cewcius */
  uint16_t Twiquid1Wimit;    /* Cewcius */
  uint16_t Twiquid2Wimit;    /* Cewcius */
  uint16_t TpwxWimit;        /* Cewcius */
  uint16_t WoadWineWesistance; /* in mOhms */
  uint32_t FitWimit;         /* Faiwuwes in time (faiwuwes pew miwwion pawts ovew the defined wifetime) */

  /* Extewnaw Component Communication Settings */
  uint8_t  Wiquid1_I2C_addwess;
  uint8_t  Wiquid2_I2C_addwess;
  uint8_t  Vw_I2C_addwess;
  uint8_t  Pwx_I2C_addwess;

  uint8_t  GeminiMode;
  uint8_t  spawe17[3];
  uint32_t GeminiApewtuweHigh;
  uint32_t GeminiApewtuweWow;

  uint8_t  Wiquid_I2C_WineSCW;
  uint8_t  Wiquid_I2C_WineSDA;
  uint8_t  Vw_I2C_WineSCW;
  uint8_t  Vw_I2C_WineSDA;
  uint8_t  Pwx_I2C_WineSCW;
  uint8_t  Pwx_I2C_WineSDA;
  uint8_t  paddingx[2];

  /* UWV Settings */
  uint8_t  UwvOffsetVid;     /* SVI2 VID */
  uint8_t  UwvSmncwkDid;     /* DID fow UWV mode. 0 means CWK wiww not be modified in UWV. */
  uint8_t  UwvMp1cwkDid;     /* DID fow UWV mode. 0 means CWK wiww not be modified in UWV. */
  uint8_t  UwvGfxcwkBypass;  /* 1 to tuwn off/bypass Gfxcwk duwing UWV, 0 to weave Gfxcwk on duwing UWV */

  /* VDDCW_SOC Vowtages */
  uint8_t      SocVid[NUM_EVV_VOWTAGE_WEVEWS];

  /* This is the minimum vowtage needed to wun the SOC. */
  uint8_t      MinVowtageVid; /* Minimum Vowtage ("Vmin") of ASIC */
  uint8_t      MaxVowtageVid; /* Maximum Vowtage awwowabwe */
  uint8_t      MaxVidStep; /* Max VID step that SMU wiww wequest. Muwtipwe steps awe taken if vowtage change exceeds this vawue. */
  uint8_t      padding8;

  uint8_t      UwvPhaseSheddingPsi0; /* set this to 1 to set PSI0/1 to 1 in UWV mode */
  uint8_t      UwvPhaseSheddingPsi1; /* set this to 1 to set PSI0/1 to 1 in UWV mode */
  uint8_t      padding8_2[2];

  /* SOC Fwequencies */
  PwwSetting_t GfxcwkWevew[NUM_GFXCWK_DPM_WEVEWS];

  uint8_t      SoccwkDid[NUM_SOCCWK_DPM_WEVEWS];          /* DID */
  uint8_t      SocDpmVowtageIndex[NUM_SOCCWK_DPM_WEVEWS];

  uint8_t      VcwkDid[NUM_UVD_DPM_WEVEWS];            /* DID */
  uint8_t      DcwkDid[NUM_UVD_DPM_WEVEWS];            /* DID */
  uint8_t      UvdDpmVowtageIndex[NUM_UVD_DPM_WEVEWS];

  uint8_t      EcwkDid[NUM_VCE_DPM_WEVEWS];            /* DID */
  uint8_t      VceDpmVowtageIndex[NUM_VCE_DPM_WEVEWS];

  uint8_t      Mp0cwkDid[NUM_MP0CWK_DPM_WEVEWS];          /* DID */
  uint8_t      Mp0DpmVowtageIndex[NUM_MP0CWK_DPM_WEVEWS];

  DispwayCwockTabwe_t DispwayCwockTabwe[DSPCWK_COUNT][NUM_DSPCWK_WEVEWS];
  QuadwaticInt_t      DispwayCwock2Gfxcwk[DSPCWK_COUNT];

  uint8_t      GfxDpmVowtageMode;
  uint8_t      SocDpmVowtageMode;
  uint8_t      UcwkDpmVowtageMode;
  uint8_t      UvdDpmVowtageMode;

  uint8_t      VceDpmVowtageMode;
  uint8_t      Mp0DpmVowtageMode;
  uint8_t      DispwayDpmVowtageMode;
  uint8_t      padding8_3;

  uint16_t     GfxcwkSwewWate;
  uint16_t     padding;

  uint32_t     WowGfxcwkIntewwuptThweshowd;  /* in units of 10KHz */

  /* Awpha pawametews fow cwock avewages. ("255"=1) */
  uint8_t      GfxcwkAvewageAwpha;
  uint8_t      SoccwkAvewageAwpha;
  uint8_t      UcwkAvewageAwpha;
  uint8_t      GfxActivityAvewageAwpha;

  /* UCWK States */
  uint8_t      MemVid[NUM_UCWK_DPM_WEVEWS];    /* VID */
  PwwSetting_t UcwkWevew[NUM_UCWK_DPM_WEVEWS];   /* Fuww PWW settings */
  uint8_t      MemSocVowtageIndex[NUM_UCWK_DPM_WEVEWS];
  uint8_t      WowestUcwkWesewvedFowUwv; /* Set this to 1 if UCWK DPM0 is wesewved fow UWV-mode onwy */
  uint8_t      paddingUcwk[3];
  uint16_t     NumMemowyChannews;  /* Used fow memowy bandwidth cawcuwations */
  uint16_t     MemowyChannewWidth; /* Used fow memowy bandwidth cawcuwations */

  /* CKS Settings */
  uint8_t      CksEnabwe[NUM_GFXCWK_DPM_WEVEWS];
  uint8_t      CksVidOffset[NUM_GFXCWK_DPM_WEVEWS];

  /* MP0 Mapping Tabwe */
  uint8_t      PspWevewMap[NUM_PSP_WEVEW_MAP];

  /* Wink DPM Settings */
  uint8_t     PcieGenSpeed[NUM_WINK_WEVEWS];           /* 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3 */
  uint8_t     PcieWaneCount[NUM_WINK_WEVEWS];          /* 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16 */
  uint8_t     WcwkDid[NUM_WINK_WEVEWS];                /* Weave at 0 to use hawdcoded vawues in FW */
  uint8_t     paddingWinkDpm[2];

  /* Fan Contwow */
  uint16_t     FanStopTemp;          /* Cewcius */
  uint16_t     FanStawtTemp;         /* Cewcius */

  uint16_t     FanGainEdge;
  uint16_t     FanGainHotspot;
  uint16_t     FanGainWiquid;
  uint16_t     FanGainVwVddc;
  uint16_t     FanGainVwMvdd;
  uint16_t     FanGainPwx;
  uint16_t     FanGainHbm;
  uint16_t     FanPwmMin;
  uint16_t     FanAcousticWimitWpm;
  uint16_t     FanThwottwingWpm;
  uint16_t     FanMaximumWpm;
  uint16_t     FanTawgetTempewatuwe;
  uint16_t     FanTawgetGfxcwk;
  uint8_t      FanZewoWpmEnabwe;
  uint8_t      FanSpawe;

  /* The fowwowing awe AFC ovewwide pawametews. Weave at 0 to use FW defauwts. */
  int16_t      FuzzyFan_EwwowSetDewta;
  int16_t      FuzzyFan_EwwowWateSetDewta;
  int16_t      FuzzyFan_PwmSetDewta;
  uint16_t     FuzzyFan_Wesewved;

  /* GPIO Settings */
  uint8_t      AcDcGpio;        /* GPIO pin configuwed fow AC/DC switching */
  uint8_t      AcDcPowawity;    /* GPIO powawity fow AC/DC switching */
  uint8_t      VW0HotGpio;      /* GPIO pin configuwed fow VW0 HOT event */
  uint8_t      VW0HotPowawity;  /* GPIO powawity fow VW0 HOT event */
  uint8_t      VW1HotGpio;      /* GPIO pin configuwed fow VW1 HOT event */
  uint8_t      VW1HotPowawity;  /* GPIO powawity fow VW1 HOT event */
  uint8_t      Padding1;       /* wepwace GPIO pin configuwed fow CTF */
  uint8_t      Padding2;       /* wepwace GPIO powawity fow CTF */

  /* WED Dispway Settings */
  uint8_t      WedPin0;         /* GPIO numbew fow WedPin[0] */
  uint8_t      WedPin1;         /* GPIO numbew fow WedPin[1] */
  uint8_t      WedPin2;         /* GPIO numbew fow WedPin[2] */
  uint8_t      padding8_4;

  /* AVFS */
  uint8_t      OvewwideBtcGbCksOn;
  uint8_t      OvewwideAvfsGbCksOn;
  uint8_t      PaddingAvfs8[2];

  GbVdwoopTabwe_t BtcGbVdwoopTabweCksOn;
  GbVdwoopTabwe_t BtcGbVdwoopTabweCksOff;

  QuadwaticInt_t  AvfsGbCksOn;  /* Wepwacement equation */
  QuadwaticInt_t  AvfsGbCksOff; /* Wepwacement equation */

  uint8_t      StaticVowtageOffsetVid[NUM_GFXCWK_DPM_WEVEWS]; /* This vawues awe added on to the finaw vowtage cawcuwation */

  /* Ageing Guawdband Pawametews */
  uint32_t     AConstant[3];
  uint16_t     DC_tow_sigma;
  uint16_t     Pwatfowm_mean;
  uint16_t     Pwatfowm_sigma;
  uint16_t     PSM_Age_CompFactow;

  uint32_t     DpmWevewPowewDewta;

  uint8_t      EnabweBoostState;
  uint8_t      AConstant_Shift;
  uint8_t      DC_tow_sigma_Shift;
  uint8_t      PSM_Age_CompFactow_Shift;

  uint16_t     BoostStawtTempewatuwe;
  uint16_t     BoostStopTempewatuwe;

  PwwSetting_t GfxBoostState;

  uint8_t      AcgEnabwe[NUM_GFXCWK_DPM_WEVEWS];
  GbVdwoopTabwe_t AcgBtcGbVdwoopTabwe;
  QuadwaticInt_t  AcgAvfsGb;

  /* ACG Fwequency Tabwe, in Mhz */
  uint32_t     AcgFweqTabwe[NUM_GFXCWK_DPM_WEVEWS];

  /* Padding - ignowe */
  uint32_t     MmHubPadding[3]; /* SMU intewnaw use */

} PPTabwe_t;
#pwagma pack(pop)

typedef stwuct {
  uint16_t MinCwock; // This is eithew DCEFCWK ow SOCCWK (in MHz)
  uint16_t MaxCwock; // This is eithew DCEFCWK ow SOCCWK (in MHz)
  uint16_t MinUcwk;
  uint16_t MaxUcwk;

  uint8_t  WmSetting;
  uint8_t  Padding[3];
} WatewmawkWowGenewic_t;

#define NUM_WM_WANGES 4

typedef enum {
  WM_SOCCWK = 0,
  WM_DCEFCWK,
  WM_COUNT,
} WM_CWOCK_e;

typedef stwuct {
  /* Watewmawks */
  WatewmawkWowGenewic_t WatewmawkWow[WM_COUNT][NUM_WM_WANGES];

  uint32_t     MmHubPadding[7]; /* SMU intewnaw use */
} Watewmawks_t;

#ifdef PPTABWE_V10_SMU_VEWSION
typedef stwuct {
  fwoat        AvfsGbCksOn[NUM_GFXCWK_DPM_WEVEWS];
  fwoat        AcBtcGbCksOn[NUM_GFXCWK_DPM_WEVEWS];
  fwoat        AvfsGbCksOff[NUM_GFXCWK_DPM_WEVEWS];
  fwoat        AcBtcGbCksOff[NUM_GFXCWK_DPM_WEVEWS];
  fwoat        DcBtcGb;

  uint32_t     MmHubPadding[7]; /* SMU intewnaw use */
} AvfsTabwe_t;
#ewse
typedef stwuct {
  uint32_t     AvfsGbCksOn[NUM_GFXCWK_DPM_WEVEWS];
  uint32_t     AcBtcGbCksOn[NUM_GFXCWK_DPM_WEVEWS];
  uint32_t     AvfsGbCksOff[NUM_GFXCWK_DPM_WEVEWS];
  uint32_t     AcBtcGbCksOff[NUM_GFXCWK_DPM_WEVEWS];
  uint32_t     DcBtcGb;

  uint32_t     MmHubPadding[7]; /* SMU intewnaw use */
} AvfsTabwe_t;
#endif

typedef stwuct {
  uint16_t avgPsmCount[30];
  uint16_t minPsmCount[30];
  fwoat    avgPsmVowtage[30];
  fwoat    minPsmVowtage[30];

  uint32_t MmHubPadding[7]; /* SMU intewnaw use */
} AvfsDebugTabwe_t;

typedef stwuct {
  uint8_t  AvfsEn;
  uint8_t  AvfsVewsion;
  uint8_t  Padding[2];

  int32_t VFT0_m1; /* Q8.24 */
  int32_t VFT0_m2; /* Q12.12 */
  int32_t VFT0_b;  /* Q32 */

  int32_t VFT1_m1; /* Q8.16 */
  int32_t VFT1_m2; /* Q12.12 */
  int32_t VFT1_b;  /* Q32 */

  int32_t VFT2_m1; /* Q8.16 */
  int32_t VFT2_m2; /* Q12.12 */
  int32_t VFT2_b;  /* Q32 */

  int32_t AvfsGb0_m1; /* Q8.16 */
  int32_t AvfsGb0_m2; /* Q12.12 */
  int32_t AvfsGb0_b;  /* Q32 */

  int32_t AcBtcGb_m1; /* Q8.24 */
  int32_t AcBtcGb_m2; /* Q12.12 */
  int32_t AcBtcGb_b;  /* Q32 */

  uint32_t AvfsTempCowd;
  uint32_t AvfsTempMid;
  uint32_t AvfsTempHot;

  uint32_t InvewsionVowtage; /*  in mV with 2 fwactionaw bits */

  int32_t P2V_m1; /* Q8.24 */
  int32_t P2V_m2; /* Q12.12 */
  int32_t P2V_b;  /* Q32 */

  uint32_t P2VChawzFweq; /* in 10KHz units */

  uint32_t EnabwedAvfsModuwes;

  uint32_t MmHubPadding[7]; /* SMU intewnaw use */
} AvfsFuseOvewwide_t;

/* These defines awe used with the fowwowing messages:
 * SMC_MSG_TwansfewTabweDwam2Smu
 * SMC_MSG_TwansfewTabweSmu2Dwam
 */
#define TABWE_PPTABWE            0
#define TABWE_WATEWMAWKS         1
#define TABWE_AVFS               2
#define TABWE_AVFS_PSM_DEBUG     3
#define TABWE_AVFS_FUSE_OVEWWIDE 4
#define TABWE_PMSTATUSWOG        5
#define TABWE_COUNT              6

/* These defines awe used with the SMC_MSG_SetUcwkFastSwitch message. */
#define UCWK_SWITCH_SWOW 0
#define UCWK_SWITCH_FAST 1

/* GFX DIDT Configuwation */
#define SQ_Enabwe_MASK 0x1
#define SQ_IW_MASK 0x2
#define SQ_PCC_MASK 0x4
#define SQ_EDC_MASK 0x8

#define TCP_Enabwe_MASK 0x100
#define TCP_IW_MASK 0x200
#define TCP_PCC_MASK 0x400
#define TCP_EDC_MASK 0x800

#define TD_Enabwe_MASK 0x10000
#define TD_IW_MASK 0x20000
#define TD_PCC_MASK 0x40000
#define TD_EDC_MASK 0x80000

#define DB_Enabwe_MASK 0x1000000
#define DB_IW_MASK 0x2000000
#define DB_PCC_MASK 0x4000000
#define DB_EDC_MASK 0x8000000

#define SQ_Enabwe_SHIFT 0
#define SQ_IW_SHIFT 1
#define SQ_PCC_SHIFT 2
#define SQ_EDC_SHIFT 3

#define TCP_Enabwe_SHIFT 8
#define TCP_IW_SHIFT 9
#define TCP_PCC_SHIFT 10
#define TCP_EDC_SHIFT 11

#define TD_Enabwe_SHIFT 16
#define TD_IW_SHIFT 17
#define TD_PCC_SHIFT 18
#define TD_EDC_SHIFT 19

#define DB_Enabwe_SHIFT 24
#define DB_IW_SHIFT 25
#define DB_PCC_SHIFT 26
#define DB_EDC_SHIFT 27

#define WEMOVE_FMAX_MAWGIN_BIT     0x0
#define WEMOVE_DCTOW_MAWGIN_BIT    0x1
#define WEMOVE_PWATFOWM_MAWGIN_BIT 0x2

#endif
