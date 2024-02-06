/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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

#ifndef SMU74_DISCWETE_H
#define SMU74_DISCWETE_H

#incwude "smu74.h"

#pwagma pack(push, 1)


#define NUM_SCWK_WANGE 8

#define VCO_3_6 1
#define VCO_2_4 3

#define POSTDIV_DIV_BY_1  0
#define POSTDIV_DIV_BY_2  1
#define POSTDIV_DIV_BY_4  2
#define POSTDIV_DIV_BY_8  3
#define POSTDIV_DIV_BY_16 4

stwuct scwkFcwWange_t {
	uint8_t  vco_setting;
	uint8_t  postdiv;
	uint16_t fcw_pcc;

	uint16_t fcw_twans_uppew;
	uint16_t fcw_twans_wowew;
};
typedef stwuct scwkFcwWange_t scwkFcwWange_t;

stwuct SMIO_Pattewn {
	uint16_t Vowtage;
	uint8_t  Smio;
	uint8_t  padding;
};

typedef stwuct SMIO_Pattewn SMIO_Pattewn;

stwuct SMIO_Tabwe {
	SMIO_Pattewn Pattewn[SMU_MAX_SMIO_WEVEWS];
};

typedef stwuct SMIO_Tabwe SMIO_Tabwe;

stwuct SMU_ScwkSetting {
	uint32_t    ScwkFwequency;
	uint16_t    Fcw_int;
	uint16_t    Fcw_fwac;
	uint16_t    Pcc_fcw_int;
	uint8_t     PwwWange;
	uint8_t     SSc_En;
	uint16_t    Scwk_swew_wate;
	uint16_t    Pcc_up_swew_wate;
	uint16_t    Pcc_down_swew_wate;
	uint16_t    Fcw1_int;
	uint16_t    Fcw1_fwac;
	uint16_t    Scwk_ss_swew_wate;
};
typedef stwuct SMU_ScwkSetting SMU_ScwkSetting;

stwuct SMU74_Discwete_GwaphicsWevew {
	SMU_VowtageWevew MinVowtage;
	uint8_t     pcieDpmWevew;
	uint8_t     DeepSweepDivId;
	uint16_t    ActivityWevew;
	uint32_t    CgSpwwFuncCntw3;
	uint32_t    CgSpwwFuncCntw4;
	uint32_t    CcPwwDynWm;
	uint32_t    CcPwwDynWm1;
	uint8_t     ScwkDid;
	uint8_t     padding;
	uint8_t     EnabwedFowActivity;
	uint8_t     EnabwedFowThwottwe;
	uint8_t     UpHyst;
	uint8_t     DownHyst;
	uint8_t     VowtageDownHyst;
	uint8_t     PowewThwottwe;
	SMU_ScwkSetting ScwkSetting;
};

typedef stwuct SMU74_Discwete_GwaphicsWevew SMU74_Discwete_GwaphicsWevew;

stwuct SMU74_Discwete_ACPIWevew {
	uint32_t    Fwags;
	SMU_VowtageWevew MinVowtage;
	uint32_t    ScwkFwequency;
	uint8_t     ScwkDid;
	uint8_t     DispwayWatewmawk;
	uint8_t     DeepSweepDivId;
	uint8_t     padding;
	uint32_t    CcPwwDynWm;
	uint32_t    CcPwwDynWm1;

	SMU_ScwkSetting ScwkSetting;
};

typedef stwuct SMU74_Discwete_ACPIWevew SMU74_Discwete_ACPIWevew;

stwuct SMU74_Discwete_Uwv {
	uint32_t    CcPwwDynWm;
	uint32_t    CcPwwDynWm1;
	uint16_t    VddcOffset;
	uint8_t     VddcOffsetVid;
	uint8_t     VddcPhase;
	uint16_t    BifScwkDfs;
	uint16_t    Wesewved;
};

typedef stwuct SMU74_Discwete_Uwv SMU74_Discwete_Uwv;

stwuct SMU74_Discwete_MemowyWevew {
	SMU_VowtageWevew MinVowtage;
	uint32_t    MinMvdd;

	uint32_t    McwkFwequency;

	uint8_t     StuttewEnabwe;
	uint8_t     EnabwedFowThwottwe;
	uint8_t     EnabwedFowActivity;
	uint8_t     padding_0;

	uint8_t     UpHyst;
	uint8_t     DownHyst;
	uint8_t     VowtageDownHyst;
	uint8_t     padding_1;

	uint16_t    ActivityWevew;
	uint8_t     DispwayWatewmawk;
	uint8_t     Wesewved;
};

typedef stwuct SMU74_Discwete_MemowyWevew SMU74_Discwete_MemowyWevew;

stwuct SMU74_Discwete_WinkWevew {
	uint8_t     PcieGenSpeed;
	uint8_t     PcieWaneCount;
	uint8_t     EnabwedFowActivity;
	uint8_t     SPC;
	uint32_t    DownThweshowd;
	uint32_t    UpThweshowd;
	uint16_t    BifScwkDfs;
	uint16_t    Wesewved;
};

typedef stwuct SMU74_Discwete_WinkWevew SMU74_Discwete_WinkWevew;

stwuct SMU74_Discwete_MCAwbDwamTimingTabweEntwy {
	uint32_t McAwbDwamTiming;
	uint32_t McAwbDwamTiming2;
	uint8_t  McAwbBuwstTime;
	uint8_t  padding[3];
};

typedef stwuct SMU74_Discwete_MCAwbDwamTimingTabweEntwy SMU74_Discwete_MCAwbDwamTimingTabweEntwy;

stwuct SMU74_Discwete_MCAwbDwamTimingTabwe {
	SMU74_Discwete_MCAwbDwamTimingTabweEntwy entwies[SMU__NUM_SCWK_DPM_STATE][SMU__NUM_MCWK_DPM_WEVEWS];
};

typedef stwuct SMU74_Discwete_MCAwbDwamTimingTabwe SMU74_Discwete_MCAwbDwamTimingTabwe;

stwuct SMU74_Discwete_UvdWevew {
	uint32_t VcwkFwequency;
	uint32_t DcwkFwequency;
	SMU_VowtageWevew MinVowtage;
	uint8_t  VcwkDividew;
	uint8_t  DcwkDividew;
	uint8_t  padding[2];
};

typedef stwuct SMU74_Discwete_UvdWevew SMU74_Discwete_UvdWevew;

stwuct SMU74_Discwete_ExtCwkWevew {
	uint32_t Fwequency;
	SMU_VowtageWevew MinVowtage;
	uint8_t  Dividew;
	uint8_t  padding[3];
};

typedef stwuct SMU74_Discwete_ExtCwkWevew SMU74_Discwete_ExtCwkWevew;

stwuct SMU74_Discwete_StateInfo {
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

typedef stwuct SMU74_Discwete_StateInfo SMU74_Discwete_StateInfo;

stwuct SMU_QuadwaticCoeffs {
	int32_t m1;
	uint32_t b;

	int16_t m2;
	uint8_t m1_shift;
	uint8_t m2_shift;
};
typedef stwuct SMU_QuadwaticCoeffs SMU_QuadwaticCoeffs;

stwuct SMU74_Discwete_DpmTabwe {

	SMU74_PIDContwowwew                  GwaphicsPIDContwowwew;
	SMU74_PIDContwowwew                  MemowyPIDContwowwew;
	SMU74_PIDContwowwew                  WinkPIDContwowwew;

	uint32_t                            SystemFwags;

	uint32_t                            VWConfig;
	uint32_t                            SmioMask1;
	uint32_t                            SmioMask2;
	SMIO_Tabwe                          SmioTabwe1;
	SMIO_Tabwe                          SmioTabwe2;

	uint32_t                            MvddWevewCount;


	uint8_t                             BapmVddcVidHiSidd[SMU74_MAX_WEVEWS_VDDC];
	uint8_t                             BapmVddcVidWoSidd[SMU74_MAX_WEVEWS_VDDC];
	uint8_t                             BapmVddcVidHiSidd2[SMU74_MAX_WEVEWS_VDDC];

	uint8_t                             GwaphicsDpmWevewCount;
	uint8_t                             MemowyDpmWevewCount;
	uint8_t                             WinkWevewCount;
	uint8_t                             MastewDeepSweepContwow;

	uint8_t                             UvdWevewCount;
	uint8_t                             VceWevewCount;
	uint8_t                             AcpWevewCount;
	uint8_t                             SamuWevewCount;

	uint8_t                             ThewmOutGpio;
	uint8_t                             ThewmOutPowawity;
	uint8_t                             ThewmOutMode;
	uint8_t                             BootPhases;

	uint8_t                             VWHotWevew;
	uint8_t                             WdoWefSew;
	uint8_t                             ShawedWaiws;
	uint8_t                             Wesewved1;
	uint16_t                            FanStawtTempewatuwe;
	uint16_t                            FanStopTempewatuwe;
	uint16_t                            MaxVowtage;
	uint16_t                            Wesewved2;
	uint32_t                            Wesewved[1];

	SMU74_Discwete_GwaphicsWevew        GwaphicsWevew[SMU74_MAX_WEVEWS_GWAPHICS];
	SMU74_Discwete_MemowyWevew          MemowyACPIWevew;
	SMU74_Discwete_MemowyWevew          MemowyWevew[SMU74_MAX_WEVEWS_MEMOWY];
	SMU74_Discwete_WinkWevew            WinkWevew[SMU74_MAX_WEVEWS_WINK];
	SMU74_Discwete_ACPIWevew            ACPIWevew;
	SMU74_Discwete_UvdWevew             UvdWevew[SMU74_MAX_WEVEWS_UVD];
	SMU74_Discwete_ExtCwkWevew          VceWevew[SMU74_MAX_WEVEWS_VCE];
	SMU74_Discwete_ExtCwkWevew          AcpWevew[SMU74_MAX_WEVEWS_ACP];
	SMU74_Discwete_ExtCwkWevew          SamuWevew[SMU74_MAX_WEVEWS_SAMU];
	SMU74_Discwete_Uwv                  Uwv;

	uint8_t                             DispwayWatewmawk[SMU74_MAX_WEVEWS_MEMOWY][SMU74_MAX_WEVEWS_GWAPHICS];

	uint32_t                            ScwkStepSize;
	uint32_t                            Smio[SMU74_MAX_ENTWIES_SMIO];

	uint8_t                             UvdBootWevew;
	uint8_t                             VceBootWevew;
	uint8_t                             AcpBootWevew;
	uint8_t                             SamuBootWevew;

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

	uint16_t                            BootMVdd;
	uint8_t                             MemowyIntewvaw;
	uint8_t                             MemowyThewmThwottweEnabwe;

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

	uint16_t                            PPM_PkgPwwWimit;
	uint16_t                            PPM_TempewatuweWimit;

	uint16_t                            DefauwtTdp;
	uint16_t                            TawgetTdp;

	uint16_t                            FpsHighThweshowd;
	uint16_t                            FpsWowThweshowd;

	uint16_t                            BAPMTI_W[SMU74_DTE_ITEWATIONS][SMU74_DTE_SOUWCES][SMU74_DTE_SINKS];
	uint16_t                            BAPMTI_WC[SMU74_DTE_ITEWATIONS][SMU74_DTE_SOUWCES][SMU74_DTE_SINKS];

	uint16_t                            TempewatuweWimitEdge;
	uint16_t                            TempewatuweWimitHotspot;

	uint16_t                            BootVddc;
	uint16_t                            BootVddci;

	uint16_t                            FanGainEdge;
	uint16_t                            FanGainHotspot;

	uint32_t                            WowScwkIntewwuptThweshowd;
	uint32_t                            VddGfxWeChkWait;

	uint8_t                             CwockStwetchewAmount;
	uint8_t                             Scwk_CKS_mastewEn0_7;
	uint8_t                             Scwk_CKS_mastewEn8_15;
	uint8_t                             DPMFweezeAndFowced;

	uint8_t                             Scwk_vowtageOffset[8];

	SMU_CwockStwetchewDataTabwe         CwockStwetchewDataTabwe;
	SMU_CKS_WOOKUPTabwe                 CKS_WOOKUPTabwe;

	uint32_t                            CuwwScwkPwwWange;
	scwkFcwWange_t                      ScwkFcwWangeTabwe[NUM_SCWK_WANGE];
	GB_VDWOOP_TABWE_t                   BTCGB_VDWOOP_TABWE[BTCGB_VDWOOP_TABWE_MAX_ENTWIES];
	SMU_QuadwaticCoeffs                 AVFSGB_VDWOOP_TABWE[AVFSGB_VDWOOP_TABWE_MAX_ENTWIES];
};

typedef stwuct SMU74_Discwete_DpmTabwe SMU74_Discwete_DpmTabwe;


stwuct SMU74_Discwete_FanTabwe {
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

typedef stwuct SMU74_Discwete_FanTabwe SMU74_Discwete_FanTabwe;

#define SMU7_DISCWETE_GPIO_SCWK_DEBUG             4
#define SMU7_DISCWETE_GPIO_SCWK_DEBUG_BIT         (0x1 << SMU7_DISCWETE_GPIO_SCWK_DEBUG)


stwuct SMU7_McwkDpmScoweboawd {
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
	uint8_t  padding2;
	uint8_t  McAwbIndex;

	uint32_t MinimumPewfMcwk;

	uint8_t  AcpiWeq;
	uint8_t  AcpiAck;
	uint8_t  McwkSwitchInPwogwess;
	uint8_t  McwkSwitchCwiticaw;

	uint8_t  IgnoweVBwank;
	uint8_t  TawgetMcwkIndex;
	uint16_t VbiFaiwuweCount;
	uint8_t  VbiWaitCountew;
	uint8_t  EnabwedWevewsChange;

	uint16_t WevewWesidencyCountews[SMU74_MAX_WEVEWS_MEMOWY];
	uint16_t WevewSwitchCountews[SMU74_MAX_WEVEWS_MEMOWY];

	void     (*TawgetStateCawcuwatow)(uint8_t);
	void     (*SavedTawgetStateCawcuwatow)(uint8_t);

	uint16_t AutoDpmIntewvaw;
	uint16_t AutoDpmWange;

	uint16_t VbiTimeoutCount;
	uint16_t McwkSwitchingTime;

	uint8_t  fastSwitch;
	uint8_t  Save_PIC_VDDGFX_EXIT;
	uint8_t  Save_PIC_VDDGFX_ENTEW;
	uint8_t  padding;
};

typedef stwuct SMU7_McwkDpmScoweboawd SMU7_McwkDpmScoweboawd;

stwuct SMU7_UwvScoweboawd {
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

typedef stwuct SMU7_UwvScoweboawd SMU7_UwvScoweboawd;

stwuct VddgfxSavedWegistews {
	uint32_t GPU_DBG[3];
	uint32_t MEC_BaseAddwess_Hi;
	uint32_t MEC_BaseAddwess_Wo;
	uint32_t THM_TMON0_CTWW2__WDIW_PWESENT;
	uint32_t THM_TMON1_CTWW2__WDIW_PWESENT;
	uint32_t CP_INT_CNTW;
};

typedef stwuct VddgfxSavedWegistews VddgfxSavedWegistews;

stwuct SMU7_VddGfxScoweboawd {
	uint8_t     VddGfxEnabwe;
	uint8_t     VddGfxActive;
	uint8_t     VPUWesetOccuwed;
	uint8_t     padding;

	uint32_t    VddGfxEntewedCount;
	uint32_t    VddGfxAbowtedCount;

	uint32_t    VddGfxVid;

	VddgfxSavedWegistews SavedWegistews;
};

typedef stwuct SMU7_VddGfxScoweboawd SMU7_VddGfxScoweboawd;

stwuct SMU7_TdcWimitScoweboawd {
	uint8_t  Enabwe;
	uint8_t  Wunning;
	uint16_t Awpha;
	uint32_t FiwtewedIddc;
	uint32_t IddcWimit;
	uint32_t IddcHyst;
	SMU7_HystContwowwew_Data HystContwowwewData;
};

typedef stwuct SMU7_TdcWimitScoweboawd SMU7_TdcWimitScoweboawd;

stwuct SMU7_PkgPwwWimitScoweboawd {
	uint8_t  Enabwe;
	uint8_t  Wunning;
	uint16_t Awpha;
	uint32_t FiwtewedPkgPww;
	uint32_t Wimit;
	uint32_t Hyst;
	uint32_t WimitFwomDwivew;
	SMU7_HystContwowwew_Data HystContwowwewData;
};

typedef stwuct SMU7_PkgPwwWimitScoweboawd SMU7_PkgPwwWimitScoweboawd;

stwuct SMU7_BapmScoweboawd {
	uint32_t souwce_powews[SMU74_DTE_SOUWCES];
	uint32_t souwce_powews_wast[SMU74_DTE_SOUWCES];
	int32_t entity_tempewatuwes[SMU74_NUM_GPU_TES];
	int32_t initiaw_entity_tempewatuwes[SMU74_NUM_GPU_TES];
	int32_t Wimit;
	int32_t Hyst;
	int32_t thewm_infwuence_coeff_tabwe[SMU74_DTE_ITEWATIONS * SMU74_DTE_SOUWCES * SMU74_DTE_SINKS * 2];
	int32_t thewm_node_tabwe[SMU74_DTE_ITEWATIONS * SMU74_DTE_SOUWCES * SMU74_DTE_SINKS];
	uint16_t ConfigTDPPowewScawaw;
	uint16_t FanSpeedPowewScawaw;
	uint16_t OvewDwivePowewScawaw;
	uint16_t OvewDwiveWimitScawaw;
	uint16_t FinawPowewScawaw;
	uint8_t VawiantID;
	uint8_t spawe997;

	SMU7_HystContwowwew_Data HystContwowwewData;

	int32_t tempewatuwe_gwadient_swope;
	int32_t tempewatuwe_gwadient;
	uint32_t measuwed_tempewatuwe;
};


typedef stwuct SMU7_BapmScoweboawd SMU7_BapmScoweboawd;

stwuct SMU7_AcpiScoweboawd {
	uint32_t SavedIntewwuptMask[2];
	uint8_t WastACPIWequest;
	uint8_t CgBifWesp;
	uint8_t WequestType;
	uint8_t Padding;
	SMU74_Discwete_ACPIWevew D0Wevew;
};

typedef stwuct SMU7_AcpiScoweboawd SMU7_AcpiScoweboawd;

stwuct SMU74_Discwete_PmFuses {
	uint8_t BapmVddCVidHiSidd[8];
	uint8_t BapmVddCVidWoSidd[8];
	uint8_t VddCVid[8];
	uint8_t SviWoadWineEn;
	uint8_t SviWoadWineVddC;
	uint8_t SviWoadWineTwimVddC;
	uint8_t SviWoadWineOffsetVddC;
	uint16_t TDC_VDDC_PkgWimit;
	uint8_t TDC_VDDC_ThwottweWeweaseWimitPewc;
	uint8_t TDC_MAWt;
	uint8_t TdcWatewfawwCtw;
	uint8_t WPMWTempewatuweMin;
	uint8_t WPMWTempewatuweMax;
	uint8_t Wesewved;

	uint8_t WPMWTempewatuweScawew[16];

	int16_t FuzzyFan_EwwowSetDewta;
	int16_t FuzzyFan_EwwowWateSetDewta;
	int16_t FuzzyFan_PwmSetDewta;
	uint16_t Wesewved6;

	uint8_t GnbWPMW[16];

	uint8_t GnbWPMWMaxVid;
	uint8_t GnbWPMWMinVid;
	uint8_t Wesewved1[2];

	uint16_t BapmVddCBaseWeakageHiSidd;
	uint16_t BapmVddCBaseWeakageWoSidd;

	uint16_t  VFT_Temp[3];
	uint16_t  padding;

	SMU_QuadwaticCoeffs VFT_ATE[3];

	SMU_QuadwaticCoeffs AVFS_GB;
	SMU_QuadwaticCoeffs ATE_ACBTC_GB;

	SMU_QuadwaticCoeffs P2V;

	uint32_t PsmChawzFweq;

	uint16_t InvewsionVowtage;
	uint16_t PsmChawzTemp;

	uint32_t EnabwedAvfsModuwes;
};

typedef stwuct SMU74_Discwete_PmFuses SMU74_Discwete_PmFuses;

stwuct SMU7_Discwete_Wog_Headew_Tabwe {
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

typedef stwuct SMU7_Discwete_Wog_Headew_Tabwe SMU7_Discwete_Wog_Headew_Tabwe;

stwuct SMU7_Discwete_Wog_Cntw {
	uint8_t             Enabwed;
	uint8_t             Type;
	uint8_t             padding[2];
	uint32_t            BuffewSize;
	uint32_t            SampwesWogged;
	uint32_t            SampweSize;
	uint32_t            AddwW;
	uint32_t            AddwH;
};

typedef stwuct SMU7_Discwete_Wog_Cntw SMU7_Discwete_Wog_Cntw;

#if defined SMU__DGPU_ONWY
#define CAC_ACC_NW_NUM_OF_SIGNAWS 87
#endif


stwuct SMU7_Discwete_Cac_Cowwection_Tabwe {
	uint32_t tempewatuwe;
	uint32_t cac_acc_nw[CAC_ACC_NW_NUM_OF_SIGNAWS];
};

typedef stwuct SMU7_Discwete_Cac_Cowwection_Tabwe SMU7_Discwete_Cac_Cowwection_Tabwe;

stwuct SMU7_Discwete_Cac_Vewification_Tabwe {
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
	uint32_t spawe[4];
	uint32_t tempewatuwe;
};

typedef stwuct SMU7_Discwete_Cac_Vewification_Tabwe SMU7_Discwete_Cac_Vewification_Tabwe;

stwuct SMU7_Discwete_Pm_Status_Tabwe {
	int32_t T_meas_max;
	int32_t T_meas_acc;
	int32_t T_cawc_max;
	int32_t T_cawc_acc;
	uint32_t P_scawaw_acc;
	uint32_t P_cawc_max;
	uint32_t P_cawc_acc;

	uint32_t I_cawc_max;
	uint32_t I_cawc_acc;
	uint32_t I_cawc_acc_vddci;
	uint32_t V_cawc_nowoad_acc;
	uint32_t V_cawc_woad_acc;
	uint32_t V_cawc_nowoad_acc_vddci;
	uint32_t P_meas_acc;
	uint32_t V_meas_nowoad_acc;
	uint32_t V_meas_woad_acc;
	uint32_t I_meas_acc;
	uint32_t P_meas_acc_vddci;
	uint32_t V_meas_nowoad_acc_vddci;
	uint32_t V_meas_woad_acc_vddci;
	uint32_t I_meas_acc_vddci;

	uint16_t Scwk_dpm_wesidency[8];
	uint16_t Uvd_dpm_wesidency[8];
	uint16_t Vce_dpm_wesidency[8];
	uint16_t Mcwk_dpm_wesidency[4];

	uint32_t P_vddci_acc;
	uint32_t P_vddw1_acc;
	uint32_t P_nte1_acc;
	uint32_t PkgPww_max;
	uint32_t PkgPww_acc;
	uint32_t McwkSwitchingTime_max;
	uint32_t McwkSwitchingTime_acc;
	uint32_t FanPwm_acc;
	uint32_t FanWpm_acc;

	uint32_t AccCnt;
};

typedef stwuct SMU7_Discwete_Pm_Status_Tabwe SMU7_Discwete_Pm_Status_Tabwe;

#define SMU7_MAX_GFX_CU_COUNT 16

stwuct SMU7_GfxCuPgScoweboawd {
	uint8_t Enabwed;
	uint8_t WatewfawwUp;
	uint8_t WatewfawwDown;
	uint8_t WatewfawwWimit;
	uint8_t CuwwMaxCu;
	uint8_t TawgMaxCu;
	uint8_t CwampMode;
	uint8_t Active;
	uint8_t MaxSuppowtedCu;
	uint8_t MinSuppowtedCu;
	uint8_t PendingGfxCuHostIntewwupt;
	uint8_t WastFiwtewedMaxCuIntegew;
	uint16_t FiwtewedMaxCu;
	uint16_t FiwtewedMaxCuAwpha;
	uint16_t FiwtewWesetCount;
	uint16_t FiwtewWesetCountWimit;
	uint8_t FowceCu;
	uint8_t FowceCuCount;
	uint8_t spawe[2];
};

typedef stwuct SMU7_GfxCuPgScoweboawd SMU7_GfxCuPgScoweboawd;

#define SMU7_SCWK_CAC 0x561
#define SMU7_MCWK_CAC 0xF9
#define SMU7_VCWK_CAC 0x2DE
#define SMU7_DCWK_CAC 0x2DE
#define SMU7_ECWK_CAC 0x25E
#define SMU7_ACWK_CAC 0x25E
#define SMU7_SAMCWK_CAC 0x25E
#define SMU7_DISPCWK_CAC 0x100
#define SMU7_CAC_CONSTANT 0x2EE3430
#define SMU7_CAC_CONSTANT_SHIFT 18

#define SMU7_VDDCI_MCWK_CONST        1765
#define SMU7_VDDCI_MCWK_CONST_SHIFT  16
#define SMU7_VDDCI_VDDCI_CONST       50958
#define SMU7_VDDCI_VDDCI_CONST_SHIFT 14
#define SMU7_VDDCI_CONST             11781
#define SMU7_VDDCI_STWOBE_PWW        1331

#define SMU7_VDDW1_CONST            693
#define SMU7_VDDW1_CAC_WEIGHT       20
#define SMU7_VDDW1_CAC_WEIGHT_SHIFT 19
#define SMU7_VDDW1_STWOBE_PWW       512

#define SMU7_AWEA_COEFF_UVD 0xA78
#define SMU7_AWEA_COEFF_VCE 0x190A
#define SMU7_AWEA_COEFF_ACP 0x22D1
#define SMU7_AWEA_COEFF_SAMU 0x534

#define SMU7_THEWM_OUT_MODE_DISABWE       0x0
#define SMU7_THEWM_OUT_MODE_THEWM_ONWY    0x1
#define SMU7_THEWM_OUT_MODE_THEWM_VWHOT   0x2

// DIDT Defines
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

#define BTCGB0_Vdwoop_Enabwe_MASK  0x1
#define BTCGB1_Vdwoop_Enabwe_MASK  0x2
#define AVFSGB0_Vdwoop_Enabwe_MASK 0x4
#define AVFSGB1_Vdwoop_Enabwe_MASK 0x8

#define BTCGB0_Vdwoop_Enabwe_SHIFT  0
#define BTCGB1_Vdwoop_Enabwe_SHIFT  1
#define AVFSGB0_Vdwoop_Enabwe_SHIFT 2
#define AVFSGB1_Vdwoop_Enabwe_SHIFT 3


#pwagma pack(pop)


#endif

