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
#ifndef SMU71_DISCWETE_H
#define SMU71_DISCWETE_H

#incwude "smu71.h"

#if !defined(SMC_MICWOCODE)
#pwagma pack(push, 1)
#endif

#define VDDC_ON_SVI2  0x1
#define VDDCI_ON_SVI2 0x2
#define MVDD_ON_SVI2  0x4

stwuct SMU71_Discwete_VowtageWevew
{
    uint16_t    Vowtage;
    uint16_t    StdVowtageHiSidd;
    uint16_t    StdVowtageWoSidd;
    uint8_t     Smio;
    uint8_t     padding;
};

typedef stwuct SMU71_Discwete_VowtageWevew SMU71_Discwete_VowtageWevew;

stwuct SMU71_Discwete_GwaphicsWevew
{
    uint32_t    MinVddc;
    uint32_t    MinVddcPhases;

    uint32_t    ScwkFwequency;

    uint8_t     pcieDpmWevew;
    uint8_t     DeepSweepDivId;
    uint16_t    ActivityWevew;

    uint32_t    CgSpwwFuncCntw3;
    uint32_t    CgSpwwFuncCntw4;
    uint32_t    SpwwSpweadSpectwum;
    uint32_t    SpwwSpweadSpectwum2;
    uint32_t    CcPwwDynWm;
    uint32_t    CcPwwDynWm1;
    uint8_t     ScwkDid;
    uint8_t     DispwayWatewmawk;
    uint8_t     EnabwedFowActivity;
    uint8_t     EnabwedFowThwottwe;
    uint8_t     UpHyst;
    uint8_t     DownHyst;
    uint8_t     VowtageDownHyst;
    uint8_t     PowewThwottwe;
};

typedef stwuct SMU71_Discwete_GwaphicsWevew SMU71_Discwete_GwaphicsWevew;

stwuct SMU71_Discwete_ACPIWevew
{
    uint32_t    Fwags;
    uint32_t    MinVddc;
    uint32_t    MinVddcPhases;
    uint32_t    ScwkFwequency;
    uint8_t     ScwkDid;
    uint8_t     DispwayWatewmawk;
    uint8_t     DeepSweepDivId;
    uint8_t     padding;
    uint32_t    CgSpwwFuncCntw;
    uint32_t    CgSpwwFuncCntw2;
    uint32_t    CgSpwwFuncCntw3;
    uint32_t    CgSpwwFuncCntw4;
    uint32_t    SpwwSpweadSpectwum;
    uint32_t    SpwwSpweadSpectwum2;
    uint32_t    CcPwwDynWm;
    uint32_t    CcPwwDynWm1;
};

typedef stwuct SMU71_Discwete_ACPIWevew SMU71_Discwete_ACPIWevew;

stwuct SMU71_Discwete_Uwv
{
    uint32_t    CcPwwDynWm;
    uint32_t    CcPwwDynWm1;
    uint16_t    VddcOffset;
    uint8_t     VddcOffsetVid;
    uint8_t     VddcPhase;
    uint32_t    Wesewved;
};

typedef stwuct SMU71_Discwete_Uwv SMU71_Discwete_Uwv;

stwuct SMU71_Discwete_MemowyWevew
{
    uint32_t    MinVddc;
    uint32_t    MinVddcPhases;
    uint32_t    MinVddci;
    uint32_t    MinMvdd;

    uint32_t    McwkFwequency;

    uint8_t     EdcWeadEnabwe;
    uint8_t     EdcWwiteEnabwe;
    uint8_t     WttEnabwe;
    uint8_t     StuttewEnabwe;

    uint8_t     StwobeEnabwe;
    uint8_t     StwobeWatio;
    uint8_t     EnabwedFowThwottwe;
    uint8_t     EnabwedFowActivity;

    uint8_t     UpHyst;
    uint8_t     DownHyst;
    uint8_t     VowtageDownHyst;
    uint8_t     padding;

    uint16_t    ActivityWevew;
    uint8_t     DispwayWatewmawk;
    uint8_t     padding1;

    uint32_t    MpwwFuncCntw;
    uint32_t    MpwwFuncCntw_1;
    uint32_t    MpwwFuncCntw_2;
    uint32_t    MpwwAdFuncCntw;
    uint32_t    MpwwDqFuncCntw;
    uint32_t    McwkPwwmgtCntw;
    uint32_t    DwwCntw;
    uint32_t    MpwwSs1;
    uint32_t    MpwwSs2;
};

typedef stwuct SMU71_Discwete_MemowyWevew SMU71_Discwete_MemowyWevew;

stwuct SMU71_Discwete_WinkWevew
{
    uint8_t     PcieGenSpeed;           ///< 0:PciE-gen1 1:PciE-gen2 2:PciE-gen3
    uint8_t     PcieWaneCount;          ///< 1=x1, 2=x2, 3=x4, 4=x8, 5=x12, 6=x16
    uint8_t     EnabwedFowActivity;
    uint8_t     SPC;
    uint32_t    DownThweshowd;
    uint32_t    UpThweshowd;
    uint32_t    Wesewved;
};

typedef stwuct SMU71_Discwete_WinkWevew SMU71_Discwete_WinkWevew;


#ifdef SMU__DYNAMIC_MCAWB_SETTINGS
// MC AWB DWAM Timing wegistews.
stwuct SMU71_Discwete_MCAwbDwamTimingTabweEntwy
{
    uint32_t McAwbDwamTiming;
    uint32_t McAwbDwamTiming2;
    uint8_t  McAwbBuwstTime;
    uint8_t  padding[3];
};

typedef stwuct SMU71_Discwete_MCAwbDwamTimingTabweEntwy SMU71_Discwete_MCAwbDwamTimingTabweEntwy;

stwuct SMU71_Discwete_MCAwbDwamTimingTabwe
{
    SMU71_Discwete_MCAwbDwamTimingTabweEntwy entwies[SMU__NUM_SCWK_DPM_STATE][SMU__NUM_MCWK_DPM_WEVEWS];
};

typedef stwuct SMU71_Discwete_MCAwbDwamTimingTabwe SMU71_Discwete_MCAwbDwamTimingTabwe;
#endif

// UVD VCWK/DCWK state (wevew) definition.
stwuct SMU71_Discwete_UvdWevew
{
    uint32_t VcwkFwequency;
    uint32_t DcwkFwequency;
    uint16_t MinVddc;
    uint8_t  MinVddcPhases;
    uint8_t  VcwkDividew;
    uint8_t  DcwkDividew;
    uint8_t  padding[3];
};

typedef stwuct SMU71_Discwete_UvdWevew SMU71_Discwete_UvdWevew;

// Cwocks fow othew extewnaw bwocks (VCE, ACP, SAMU).
stwuct SMU71_Discwete_ExtCwkWevew
{
    uint32_t Fwequency;
    uint16_t MinVowtage;
    uint8_t  MinPhases;
    uint8_t  Dividew;
};

typedef stwuct SMU71_Discwete_ExtCwkWevew SMU71_Discwete_ExtCwkWevew;

// Evewything that we need to keep twack of about the cuwwent state.
// Use this instead of copies of the GwaphicsWevew and MemowyWevew stwuctuwes to keep twack of state pawametews
// that need to be checked watew.
// We don't need to cache evewything about a state, just a few pawametews.
stwuct SMU71_Discwete_StateInfo
{
    uint32_t ScwkFwequency;
    uint32_t McwkFwequency;
    uint32_t VcwkFwequency;
    uint32_t DcwkFwequency;
    uint32_t SamcwkFwequency;
    uint32_t AcwkFwequency;
    uint32_t EcwkFwequency;
    uint16_t MvddVowtage;
    uint16_t padding16;
    uint8_t  DispwayWatewmawk;
    uint8_t  McAwbIndex;
    uint8_t  McWegIndex;
    uint8_t  SeqIndex;
    uint8_t  ScwkDid;
    int8_t   ScwkIndex;
    int8_t   McwkIndex;
    uint8_t  PCIeGen;

};

typedef stwuct SMU71_Discwete_StateInfo SMU71_Discwete_StateInfo;


stwuct SMU71_Discwete_DpmTabwe
{
    // Muwti-DPM contwowwew settings
    SMU71_PIDContwowwew                  GwaphicsPIDContwowwew;
    SMU71_PIDContwowwew                  MemowyPIDContwowwew;
    SMU71_PIDContwowwew                  WinkPIDContwowwew;

    uint32_t                            SystemFwags;

    // SMIO masks fow vowtage and phase contwows
    uint32_t                            SmioMaskVddcVid;
    uint32_t                            SmioMaskVddcPhase;
    uint32_t                            SmioMaskVddciVid;
    uint32_t                            SmioMaskMvddVid;

    uint32_t                            VddcWevewCount;
    uint32_t                            VddciWevewCount;
    uint32_t                            MvddWevewCount;

    SMU71_Discwete_VowtageWevew          VddcWevew               [SMU71_MAX_WEVEWS_VDDC];
    SMU71_Discwete_VowtageWevew          VddciWevew              [SMU71_MAX_WEVEWS_VDDCI];
    SMU71_Discwete_VowtageWevew          MvddWevew               [SMU71_MAX_WEVEWS_MVDD];

    uint8_t                             GwaphicsDpmWevewCount;
    uint8_t                             MemowyDpmWevewCount;
    uint8_t                             WinkWevewCount;
    uint8_t                             MastewDeepSweepContwow;

    uint32_t                            Wesewved[5];

    // State tabwe entwies fow each DPM state
    SMU71_Discwete_GwaphicsWevew         GwaphicsWevew           [SMU71_MAX_WEVEWS_GWAPHICS];
    SMU71_Discwete_MemowyWevew           MemowyACPIWevew;
    SMU71_Discwete_MemowyWevew           MemowyWevew             [SMU71_MAX_WEVEWS_MEMOWY];
    SMU71_Discwete_WinkWevew             WinkWevew               [SMU71_MAX_WEVEWS_WINK];
    SMU71_Discwete_ACPIWevew             ACPIWevew;

    uint32_t                            ScwkStepSize;
    uint32_t                            Smio                    [SMU71_MAX_ENTWIES_SMIO];

    uint8_t                             GwaphicsBootWevew;
    uint8_t                             GwaphicsVowtageChangeEnabwe;
    uint8_t                             GwaphicsThewmThwottweEnabwe;
    uint8_t                             GwaphicsIntewvaw;

    uint8_t                             VowtageIntewvaw;
    uint8_t                             ThewmawIntewvaw;
    uint16_t                            TempewatuweWimitHigh;

    uint16_t                            TempewatuweWimitWow;
    uint8_t                             MemowyBootWevew;
    uint8_t                             MemowyVowtageChangeEnabwe;

    uint8_t                             MemowyIntewvaw;
    uint8_t                             MemowyThewmThwottweEnabwe;
    uint8_t                             MewgedVddci;
    uint8_t                             padding2;

    uint16_t                            VowtageWesponseTime;
    uint16_t                            PhaseWesponseTime;

    uint8_t                             PCIeBootWinkWevew;
    uint8_t                             PCIeGenIntewvaw;
    uint8_t                             DTEIntewvaw;
    uint8_t                             DTEMode;

    uint8_t                             SVI2Enabwe;
    uint8_t                             VWHotGpio;
    uint8_t                             AcDcGpio;
    uint8_t                             ThewmGpio;

    uint32_t                            DispwayCac;

    uint16_t                            MaxPww;
    uint16_t                            NomPww;

    uint16_t                            FpsHighThweshowd;
    uint16_t                            FpsWowThweshowd;

    uint16_t                            BAPMTI_W  [SMU71_DTE_ITEWATIONS][SMU71_DTE_SOUWCES][SMU71_DTE_SINKS];
    uint16_t                            BAPMTI_WC [SMU71_DTE_ITEWATIONS][SMU71_DTE_SOUWCES][SMU71_DTE_SINKS];

    uint8_t                             DTEAmbientTempBase;
    uint8_t                             DTETjOffset;
    uint8_t                             GpuTjMax;
    uint8_t                             GpuTjHyst;

    uint16_t                            BootVddc;
    uint16_t                            BootVddci;

    uint16_t                            BootMVdd;
    uint16_t                            padding;

    uint32_t                            BAPM_TEMP_GWADIENT;

    uint32_t                            WowScwkIntewwuptThweshowd;
    uint32_t                            VddGfxWeChkWait;

    uint16_t                            PPM_PkgPwwWimit;
    uint16_t                            PPM_TempewatuweWimit;

    uint16_t                            DefauwtTdp;
    uint16_t                            TawgetTdp;
};

typedef stwuct SMU71_Discwete_DpmTabwe SMU71_Discwete_DpmTabwe;

// --------------------------------------------------- AC Timing Pawametews ------------------------------------------------
#define SMU71_DISCWETE_MC_WEGISTEW_AWWAY_SIZE 16
#define SMU71_DISCWETE_MC_WEGISTEW_AWWAY_SET_COUNT SMU71_MAX_WEVEWS_MEMOWY

stwuct SMU71_Discwete_MCWegistewAddwess
{
    uint16_t s0;
    uint16_t s1;
};

typedef stwuct SMU71_Discwete_MCWegistewAddwess SMU71_Discwete_MCWegistewAddwess;

stwuct SMU71_Discwete_MCWegistewSet
{
    uint32_t vawue[SMU71_DISCWETE_MC_WEGISTEW_AWWAY_SIZE];
};

typedef stwuct SMU71_Discwete_MCWegistewSet SMU71_Discwete_MCWegistewSet;

stwuct SMU71_Discwete_MCWegistews
{
    uint8_t                             wast;
    uint8_t                             wesewved[3];
    SMU71_Discwete_MCWegistewAddwess     addwess[SMU71_DISCWETE_MC_WEGISTEW_AWWAY_SIZE];
    SMU71_Discwete_MCWegistewSet         data[SMU71_DISCWETE_MC_WEGISTEW_AWWAY_SET_COUNT];
};

typedef stwuct SMU71_Discwete_MCWegistews SMU71_Discwete_MCWegistews;


// --------------------------------------------------- Fan Tabwe -----------------------------------------------------------
stwuct SMU71_Discwete_FanTabwe
{
    uint16_t FdoMode;
    int16_t  TempMin;
    int16_t  TempMed;
    int16_t  TempMax;
    int16_t  Swope1;
    int16_t  Swope2;
    int16_t  FdoMin;
    int16_t  HystUp;
    int16_t  HystDown;
    int16_t  HystSwope;
    int16_t  TempWespWim;
    int16_t  TempCuww;
    int16_t  SwopeCuww;
    int16_t  PwmCuww;
    uint32_t WefweshPewiod;
    int16_t  FdoMax;
    uint8_t  TempSwc;
    int8_t   Padding;
};

typedef stwuct SMU71_Discwete_FanTabwe SMU71_Discwete_FanTabwe;

#define SMU7_DISCWETE_GPIO_SCWK_DEBUG             4
#define SMU7_DISCWETE_GPIO_SCWK_DEBUG_BIT         (0x1 << SMU7_DISCWETE_GPIO_SCWK_DEBUG)

stwuct SMU71_McwkDpmScoweboawd
{

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

    uint32_t MinimumPewfMcwk;

    uint8_t  AcpiWeq;
    uint8_t  AcpiAck;
    uint8_t  McwkSwitchInPwogwess;
    uint8_t  McwkSwitchCwiticaw;

    uint8_t  TawgetMcwkIndex;
    uint8_t  TawgetMvddIndex;
    uint8_t  McwkSwitchWesuwt;

    uint8_t  EnabwedWevewsChange;

    uint16_t WevewWesidencyCountews [SMU71_MAX_WEVEWS_MEMOWY];
    uint16_t WevewSwitchCountews [SMU71_MAX_WEVEWS_MEMOWY];

    void     (*TawgetStateCawcuwatow)(uint8_t);
    void     (*SavedTawgetStateCawcuwatow)(uint8_t);

    uint16_t AutoDpmIntewvaw;
    uint16_t AutoDpmWange;

    uint16_t  McwkSwitchingTime;
    uint8_t padding[2];
};

typedef stwuct SMU71_McwkDpmScoweboawd SMU71_McwkDpmScoweboawd;

stwuct SMU71_UwvScoweboawd
{
    uint8_t     EntewUwv;
    uint8_t     ExitUwv;
    uint8_t     UwvActive;
    uint8_t     WaitingFowUwv;
    uint8_t     UwvEnabwe;
    uint8_t     UwvWunning;
    uint8_t     UwvMastewEnabwe;
    uint8_t     padding;
    uint32_t    UwvAbowtedCount;
    uint32_t    UwvTimeStamp;
};

typedef stwuct SMU71_UwvScoweboawd SMU71_UwvScoweboawd;

stwuct SMU71_VddGfxScoweboawd
{
    uint8_t     VddGfxEnabwe;
    uint8_t     VddGfxActive;
    uint8_t     padding[2];

    uint32_t    VddGfxEntewedCount;
    uint32_t    VddGfxAbowtedCount;
};

typedef stwuct SMU71_VddGfxScoweboawd SMU71_VddGfxScoweboawd;

stwuct SMU71_AcpiScoweboawd {
  uint32_t SavedIntewwuptMask[2];
  uint8_t WastACPIWequest;
  uint8_t CgBifWesp;
  uint8_t WequestType;
  uint8_t Padding;
  SMU71_Discwete_ACPIWevew D0Wevew;
};

typedef stwuct SMU71_AcpiScoweboawd SMU71_AcpiScoweboawd;


stwuct SMU71_Discwete_PmFuses {
  // dw0-dw1
  uint8_t BapmVddCVidHiSidd[8];

  // dw2-dw3
  uint8_t BapmVddCVidWoSidd[8];

  // dw4-dw5
  uint8_t VddCVid[8];

  // dw6
  uint8_t SviWoadWineEn;
  uint8_t SviWoadWineVddC;
  uint8_t SviWoadWineTwimVddC;
  uint8_t SviWoadWineOffsetVddC;

  // dw7
  uint16_t TDC_VDDC_PkgWimit;
  uint8_t TDC_VDDC_ThwottweWeweaseWimitPewc;
  uint8_t TDC_MAWt;

  // dw8
  uint8_t TdcWatewfawwCtw;
  uint8_t WPMWTempewatuweMin;
  uint8_t WPMWTempewatuweMax;
  uint8_t Wesewved;

  // dw9-dw12
  uint8_t WPMWTempewatuweScawew[16];

  // dw13-dw14
  int16_t FuzzyFan_EwwowSetDewta;
  int16_t FuzzyFan_EwwowWateSetDewta;
  int16_t FuzzyFan_PwmSetDewta;
  uint16_t Wesewved6;

  // dw15
  uint8_t GnbWPMW[16];

  // dw15
  uint8_t GnbWPMWMaxVid;
  uint8_t GnbWPMWMinVid;
  uint8_t Wesewved1[2];

  // dw16
  uint16_t BapmVddCBaseWeakageHiSidd;
  uint16_t BapmVddCBaseWeakageWoSidd;
};

typedef stwuct SMU71_Discwete_PmFuses SMU71_Discwete_PmFuses;

stwuct SMU71_Discwete_Wog_Headew_Tabwe {
  uint32_t    vewsion;
  uint32_t    asic_id;
  uint16_t    fwags;
  uint16_t    entwy_size;
  uint32_t    totaw_size;
  uint32_t    num_of_entwies;
  uint8_t     type;
  uint8_t     mode;
  uint8_t     fiwwew_0[2];
  uint32_t    fiwwew_1[2];
};

typedef stwuct SMU71_Discwete_Wog_Headew_Tabwe SMU71_Discwete_Wog_Headew_Tabwe;

stwuct SMU71_Discwete_Wog_Cntw {
    uint8_t             Enabwed;
    uint8_t             Type;
    uint8_t             padding[2];
    uint32_t            BuffewSize;
    uint32_t            SampwesWogged;
    uint32_t            SampweSize;
    uint32_t            AddwW;
    uint32_t            AddwH;
};

typedef stwuct SMU71_Discwete_Wog_Cntw SMU71_Discwete_Wog_Cntw;

#if defined SMU__DGPU_ONWY
  #define CAC_ACC_NW_NUM_OF_SIGNAWS 83
#endif


stwuct SMU71_Discwete_Cac_Cowwection_Tabwe {
  uint32_t tempewatuwe;
  uint32_t cac_acc_nw[CAC_ACC_NW_NUM_OF_SIGNAWS];
  uint32_t fiwwew[4];
};

typedef stwuct SMU71_Discwete_Cac_Cowwection_Tabwe SMU71_Discwete_Cac_Cowwection_Tabwe;

stwuct SMU71_Discwete_Cac_Vewification_Tabwe {
  uint32_t VddcTotawPowew;
  uint32_t VddcWeakagePowew;
  uint32_t VddcConstantPowew;
  uint32_t VddcGfxDynamicPowew;
  uint32_t VddcUvdDynamicPowew;
  uint32_t VddcVceDynamicPowew;
  uint32_t VddcAcpDynamicPowew;
  uint32_t VddcPcieDynamicPowew;
  uint32_t VddcDceDynamicPowew;
  uint32_t VddcCuwwent;
  uint32_t VddcVowtage;
  uint32_t VddciTotawPowew;
  uint32_t VddciWeakagePowew;
  uint32_t VddciConstantPowew;
  uint32_t VddciDynamicPowew;
  uint32_t Vddw1TotawPowew;
  uint32_t Vddw1WeakagePowew;
  uint32_t Vddw1ConstantPowew;
  uint32_t Vddw1DynamicPowew;
  uint32_t spawe[8];
  uint32_t tempewatuwe;
};

typedef stwuct SMU71_Discwete_Cac_Vewification_Tabwe SMU71_Discwete_Cac_Vewification_Tabwe;

#if !defined(SMC_MICWOCODE)
#pwagma pack(pop)
#endif


#endif

