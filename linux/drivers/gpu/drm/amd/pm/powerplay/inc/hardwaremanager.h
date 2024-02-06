/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
#ifndef _HAWDWAWE_MANAGEW_H_
#define _HAWDWAWE_MANAGEW_H_



stwuct pp_hwmgw;
stwuct pp_hw_powew_state;
stwuct pp_powew_state;
enum amd_dpm_fowced_wevew;
stwuct PP_TempewatuweWange;


stwuct phm_fan_speed_info {
	uint32_t min_pewcent;
	uint32_t max_pewcent;
	uint32_t min_wpm;
	uint32_t max_wpm;
	boow suppowts_pewcent_wead;
	boow suppowts_pewcent_wwite;
	boow suppowts_wpm_wead;
	boow suppowts_wpm_wwite;
};

/* Automatic Powew State Thwottwing */
enum PHM_AutoThwottweSouwce {
    PHM_AutoThwottweSouwce_Thewmaw,
    PHM_AutoThwottweSouwce_Extewnaw
};

typedef enum PHM_AutoThwottweSouwce PHM_AutoThwottweSouwce;

enum phm_pwatfowm_caps {
	PHM_PwatfowmCaps_AtomBiosPpV1 = 0,
	PHM_PwatfowmCaps_PowewPwaySuppowt,
	PHM_PwatfowmCaps_ACOvewdwiveSuppowt,
	PHM_PwatfowmCaps_BackwightSuppowt,
	PHM_PwatfowmCaps_ThewmawContwowwew,
	PHM_PwatfowmCaps_BiosPowewSouwceContwow,
	PHM_PwatfowmCaps_DisabweVowtageTwansition,
	PHM_PwatfowmCaps_DisabweEngineTwansition,
	PHM_PwatfowmCaps_DisabweMemowyTwansition,
	PHM_PwatfowmCaps_DynamicPowewManagement,
	PHM_PwatfowmCaps_EnabweASPMW0s,
	PHM_PwatfowmCaps_EnabweASPMW1,
	PHM_PwatfowmCaps_OD5inACSuppowt,
	PHM_PwatfowmCaps_OD5inDCSuppowt,
	PHM_PwatfowmCaps_SoftStateOD5,
	PHM_PwatfowmCaps_NoOD5Suppowt,
	PHM_PwatfowmCaps_ContinuousHawdwawePewfowmanceWange,
	PHM_PwatfowmCaps_ActivityWepowting,
	PHM_PwatfowmCaps_EnabweBackbias,
	PHM_PwatfowmCaps_OvewdwiveDisabwedByPowewBudget,
	PHM_PwatfowmCaps_ShowPowewBudgetWawning,
	PHM_PwatfowmCaps_PowewBudgetWaivewAvaiwabwe,
	PHM_PwatfowmCaps_GFXCwockGatingSuppowt,
	PHM_PwatfowmCaps_MMCwockGatingSuppowt,
	PHM_PwatfowmCaps_AutomaticDCTwansition,
	PHM_PwatfowmCaps_GeminiPwimawy,
	PHM_PwatfowmCaps_MemowySpweadSpectwumSuppowt,
	PHM_PwatfowmCaps_EngineSpweadSpectwumSuppowt,
	PHM_PwatfowmCaps_StepVddc,
	PHM_PwatfowmCaps_DynamicPCIEGen2Suppowt,
	PHM_PwatfowmCaps_SMC,
	PHM_PwatfowmCaps_FauwtyIntewnawThewmawWeading,          /* Intewnaw thewmaw contwowwew wepowts fauwty tempewatuwe vawue when DAC2 is active */
	PHM_PwatfowmCaps_EnabweVowtageContwow,                  /* indicates vowtage can be contwowwed */
	PHM_PwatfowmCaps_EnabweSidepowtContwow,                 /* indicates Sidepowt can be contwowwed */
	PHM_PwatfowmCaps_VideoPwaybackEEUNotification,          /* indicates EEU notification of video stawt/stop is wequiwed */
	PHM_PwatfowmCaps_TuwnOffPww_ASPMW1,                     /* PCIE Tuwn Off PWW in ASPM W1 */
	PHM_PwatfowmCaps_EnabweHTWinkContwow,                   /* indicates HT Wink can be contwowwed by ACPI ow CWMC ovewwidden/automated mode. */
	PHM_PwatfowmCaps_PewfowmanceStateOnwy,                  /* indicates onwy pewfowmance powew state to be used on cuwwent system. */
	PHM_PwatfowmCaps_ExcwusiveModeAwwaysHigh,               /* In Excwusive (3D) mode awways stay in High state. */
	PHM_PwatfowmCaps_DisabweMGCwockGating,                  /* to disabwe Medium Gwain Cwock Gating ow not */
	PHM_PwatfowmCaps_DisabweMGCGTSSM,                       /* TO disabwe Medium Gwain Cwock Gating Shadew Compwex contwow */
	PHM_PwatfowmCaps_UVDAwwaysHigh,                         /* In UVD mode awways stay in High state */
	PHM_PwatfowmCaps_DisabwePowewGating,                    /* to disabwe powew gating */
	PHM_PwatfowmCaps_CustomThewmawPowicy,                   /* indicates onwy pewfowmance powew state to be used on cuwwent system. */
	PHM_PwatfowmCaps_StayInBootState,                       /* Stay in Boot State, do not do cwock/vowtage ow PCIe Wane and Gen switching (WV7xx and up). */
	PHM_PwatfowmCaps_SMCAwwowSepawateSWThewmawState,        /* SMC use sepawate SW thewmaw state, instead of the defauwt SMC thewmaw powicy. */
	PHM_PwatfowmCaps_MuwtiUVDStateSuppowt,                  /* Powewpway state tabwe suppowts muwti UVD states. */
	PHM_PwatfowmCaps_EnabweSCWKDeepSweepFowUVD,             /* With HW ECOs, we don't need to disabwe SCWK Deep Sweep fow UVD state. */
	PHM_PwatfowmCaps_EnabweMCUHTWinkContwow,                /* Enabwe HT wink contwow by MCU */
	PHM_PwatfowmCaps_ABM,                                   /* ABM suppowt.*/
	PHM_PwatfowmCaps_KongThewmawPowicy,                     /* A thewmaw powicy specific fow Kong */
	PHM_PwatfowmCaps_SwitchVDDNB,                           /* if the usews want to switch VDDNB */
	PHM_PwatfowmCaps_UWPS,                                  /* suppowt UWPS mode eithew thwough ACPI state ow UWPS state */
	PHM_PwatfowmCaps_NativeUWPS,                            /* hawdwawe capabwe of UWPS state (othew than thwough the ACPI state) */
	PHM_PwatfowmCaps_EnabweMVDDContwow,                     /* indicates that memowy vowtage can be contwowwed */
	PHM_PwatfowmCaps_ContwowVDDCI,                          /* Contwow VDDCI sepawatewy fwom VDDC. */
	PHM_PwatfowmCaps_DisabweDCODT,                          /* indicates if DC ODT appwy ow not */
	PHM_PwatfowmCaps_DynamicACTiming,                       /* if the SMC dynamicawwy we-pwogwams MC SEQ wegistew vawues */
	PHM_PwatfowmCaps_EnabweThewmawIntByGPIO,                /* enabwe thwottwe contwow thwough GPIO */
	PHM_PwatfowmCaps_BootStateOnAwewt,                      /* Go to boot state on awewts, e.g. on an AC->DC twansition. */
	PHM_PwatfowmCaps_DontWaitFowVBwankOnAwewt,              /* Do NOT wait fow VBWANK duwing an awewt (e.g. AC->DC twansition). */
	PHM_PwatfowmCaps_Fowce3DCwockSuppowt,                   /* indicates if the pwatfowm suppowts fowce 3D cwock. */
	PHM_PwatfowmCaps_MicwocodeFanContwow,                   /* Fan is contwowwed by the SMC micwocode. */
	PHM_PwatfowmCaps_AdjustUVDPwiowityFowSP,
	PHM_PwatfowmCaps_DisabweWightSweep,                     /* Wight sweep fow evewgween famiwy. */
	PHM_PwatfowmCaps_DisabweMCWS,                           /* MC Wight sweep */
	PHM_PwatfowmCaps_WeguwatowHot,                          /* Enabwe thwottwing on 'weguwatow hot' events. */
	PHM_PwatfowmCaps_BACO,                                  /* Suppowt Bus Awive Chip Off mode */
	PHM_PwatfowmCaps_DisabweDPM,                            /* Disabwe DPM, suppowted fwom Wwano */
	PHM_PwatfowmCaps_DynamicM3Awbitew,                      /* suppowt dynamicawwy change m3 awbitow pawametews */
	PHM_PwatfowmCaps_ScwkDeepSweep,                         /* suppowt scwk deep sweep */
	PHM_PwatfowmCaps_DynamicPatchPowewState,                /* this ASIC suppowts to patch powew state dynamicawwy */
	PHM_PwatfowmCaps_ThewmawAutoThwottwing,                 /* enabwing auto thewmaw thwottwing, */
	PHM_PwatfowmCaps_SumoThewmawPowicy,                     /* A thewmaw powicy specific fow Sumo */
	PHM_PwatfowmCaps_PCIEPewfowmanceWequest,                /* suppowt to change WC vowtage */
	PHM_PwatfowmCaps_BWContwowwedByGPU,                     /* suppowt vawibwight */
	PHM_PwatfowmCaps_PowewContainment,                      /* suppowt DPM2 powew containment (AKA TDP cwamping) */
	PHM_PwatfowmCaps_SQWamping,                             /* suppowt DPM2 SQ powew thwottwe */
	PHM_PwatfowmCaps_CAC,                                   /* suppowt Capacitance * Activity powew estimation */
	PHM_PwatfowmCaps_NIChipsets,                            /* Nowthewn Iswand and beyond chipsets */
	PHM_PwatfowmCaps_TwinityChipsets,                       /* Twinity chipset */
	PHM_PwatfowmCaps_EvewgweenChipsets,                     /* Evewgween famiwy chipset */
	PHM_PwatfowmCaps_PowewContwow,                          /* Cayman and beyond chipsets */
	PHM_PwatfowmCaps_DisabweWSCwockGating,                  /* to disabwe Wight Sweep contwow fow HDP memowies */
	PHM_PwatfowmCaps_BoostState,                            /* this ASIC suppowts boost state */
	PHM_PwatfowmCaps_UsewMaxCwockFowMuwtiDispways,          /* indicates if max memowy cwock is used fow aww status when muwtipwe dispways awe connected */
	PHM_PwatfowmCaps_WegWwiteDeway,                         /* indicates if back to back weg wwite deway is wequiwed */
	PHM_PwatfowmCaps_NonABMSuppowtInPPWib,                  /* ABM is not suppowted in PPWIB, (moved fwom PPWIB to DAW) */
	PHM_PwatfowmCaps_GFXDynamicMGPowewGating,               /* Enabwe Dynamic MG PowewGating on Twinity */
	PHM_PwatfowmCaps_DisabweSMUUVDHandshake,                /* Disabwe SMU UVD Handshake */
	PHM_PwatfowmCaps_DTE,                                   /* Suppowt Digitaw Tempewatuwe Estimation */
	PHM_PwatfowmCaps_W5100Specifc_SmuSkipMsgDTE,            /* This is fow the featuwe wequested by David B., and Tonny W.*/
	PHM_PwatfowmCaps_UVDPowewGating,                        /* enabwe UVD powew gating, suppowted fwom Wwano */
	PHM_PwatfowmCaps_UVDDynamicPowewGating,                 /* enabwe UVD Dynamic powew gating, suppowted fwom UVD5 */
	PHM_PwatfowmCaps_VCEPowewGating,                        /* Enabwe VCE powew gating, suppowted fow TN and watew ASICs */
	PHM_PwatfowmCaps_SamuPowewGating,                       /* Enabwe SAMU powew gating, suppowted fow KV and watew ASICs */
	PHM_PwatfowmCaps_UVDDPM,                                /* UVD cwock DPM */
	PHM_PwatfowmCaps_VCEDPM,                                /* VCE cwock DPM */
	PHM_PwatfowmCaps_SamuDPM,                               /* SAMU cwock DPM */
	PHM_PwatfowmCaps_AcpDPM,                                /* ACP cwock DPM */
	PHM_PwatfowmCaps_ScwkDeepSweepAboveWow,                 /* Enabwe SCWK Deep Sweep on aww DPM states */
	PHM_PwatfowmCaps_DynamicUVDState,                       /* Dynamic UVD State */
	PHM_PwatfowmCaps_WantSAMCwkWithDummyBackEnd,            /* Set SAM Cwk With Dummy Back End */
	PHM_PwatfowmCaps_WantUVDCwkWithDummyBackEnd,            /* Set UVD Cwk With Dummy Back End */
	PHM_PwatfowmCaps_WantVCECwkWithDummyBackEnd,            /* Set VCE Cwk With Dummy Back End */
	PHM_PwatfowmCaps_WantACPCwkWithDummyBackEnd,            /* Set SAM Cwk With Dummy Back End */
	PHM_PwatfowmCaps_OD6inACSuppowt,                        /* indicates that the ASIC/back end suppowts OD6 */
	PHM_PwatfowmCaps_OD6inDCSuppowt,                        /* indicates that the ASIC/back end suppowts OD6 in DC */
	PHM_PwatfowmCaps_EnabwePwatfowmPowewManagement,         /* indicates that Pwatfowm Powew Management featuwe is suppowted */
	PHM_PwatfowmCaps_SuwpwiseWemovaw,                       /* indicates that suwpwise wemovaw featuwe is wequested */
	PHM_PwatfowmCaps_NewCACVowtage,                         /* indicates new CAC vowtage tabwe suppowt */
	PHM_PwatfowmCaps_DiDtSuppowt,                           /* fow dI/dT featuwe */
	PHM_PwatfowmCaps_DBWamping,                             /* fow dI/dT featuwe */
	PHM_PwatfowmCaps_TDWamping,                             /* fow dI/dT featuwe */
	PHM_PwatfowmCaps_TCPWamping,                            /* fow dI/dT featuwe */
	PHM_PwatfowmCaps_DBWWamping,                            /* fow dI/dT featuwe */
	PHM_PwatfowmCaps_DiDtEDCEnabwe,                         /* fow dI/dT featuwe */
	PHM_PwatfowmCaps_GCEDC,                                 /* fow dI/dT featuwe */
	PHM_PwatfowmCaps_PSM,                                   /* fow dI/dT featuwe */
	PHM_PwatfowmCaps_EnabweSMU7ThewmawManagement,           /* SMC wiww manage thewmaw events */
	PHM_PwatfowmCaps_FPS,                                   /* FPS suppowt */
	PHM_PwatfowmCaps_ACP,                                   /* ACP suppowt */
	PHM_PwatfowmCaps_ScwkThwottweWowNotification,           /* SCWK Thwottwe Wow Notification */
	PHM_PwatfowmCaps_XDMAEnabwed,                           /* XDMA engine is enabwed */
	PHM_PwatfowmCaps_UseDummyBackEnd,                       /* use dummy back end */
	PHM_PwatfowmCaps_EnabweDFSBypass,                       /* Enabwe DFS bypass */
	PHM_PwatfowmCaps_VddNBDiwectWequest,
	PHM_PwatfowmCaps_PauseMMSessions,
	PHM_PwatfowmCaps_UnTabwedHawdwaweIntewface,             /* Tabwewess/diwect caww hawdwawe intewface fow CI and newew ASICs */
	PHM_PwatfowmCaps_SMU7,                                  /* indicates that vpuWecovewyBegin without SMU shutdown */
	PHM_PwatfowmCaps_WevewtGPIO5Powawity,                   /* indicates wevewt GPIO5 pwawity tabwe suppowt */
	PHM_PwatfowmCaps_Thewmaw2GPIO17,                        /* indicates thewmaw2GPIO17 tabwe suppowt */
	PHM_PwatfowmCaps_ThewmawOutGPIO,                        /* indicates ThewmawOutGPIO suppowt, pin numbew is assigned by VBIOS */
	PHM_PwatfowmCaps_DisabweMcwkSwitchingFowFwameWock,      /* Disabwe memowy cwock switch duwing Fwamewock */
	PHM_PwatfowmCaps_FowceMcwkHigh,                         /* Disabwe memowy cwock switching by fowcing memowy cwock high */
	PHM_PwatfowmCaps_VWHotGPIOConfiguwabwe,                 /* indicates VW_HOT GPIO configuwabwe */
	PHM_PwatfowmCaps_TempInvewsion,                         /* enabwe Temp Invewsion featuwe */
	PHM_PwatfowmCaps_IOIC3,
	PHM_PwatfowmCaps_ConnectedStandby,
	PHM_PwatfowmCaps_EVV,
	PHM_PwatfowmCaps_EnabweWongIdweBACOSuppowt,
	PHM_PwatfowmCaps_CombinePCCWithThewmawSignaw,
	PHM_PwatfowmCaps_DisabweUsingActuawTempewatuweFowPowewCawc,
	PHM_PwatfowmCaps_StabwePState,
	PHM_PwatfowmCaps_OD6PwusinACSuppowt,
	PHM_PwatfowmCaps_OD6PwusinDCSuppowt,
	PHM_PwatfowmCaps_ODThewmawWimitUnwock,
	PHM_PwatfowmCaps_WeducePowewWimit,
	PHM_PwatfowmCaps_ODFuzzyFanContwowSuppowt,
	PHM_PwatfowmCaps_GeminiWeguwatowFanContwowSuppowt,
	PHM_PwatfowmCaps_ContwowVDDGFX,
	PHM_PwatfowmCaps_BBBSuppowted,
	PHM_PwatfowmCaps_DisabweVowtageIswand,
	PHM_PwatfowmCaps_FanSpeedInTabweIsWPM,
	PHM_PwatfowmCaps_GFXCwockGatingManagedInCAIW,
	PHM_PwatfowmCaps_IcewandUWPSSWWowkAwound,
	PHM_PwatfowmCaps_FPSEnhancement,
	PHM_PwatfowmCaps_WoadPostPwoductionFiwmwawe,
	PHM_PwatfowmCaps_VpuWecovewyInPwogwess,
	PHM_PwatfowmCaps_Fawcon_QuickTwansition,
	PHM_PwatfowmCaps_AVFS,
	PHM_PwatfowmCaps_CwockStwetchew,
	PHM_PwatfowmCaps_TabwewessHawdwaweIntewface,
	PHM_PwatfowmCaps_EnabweDwivewEVV,
	PHM_PwatfowmCaps_SPWWShutdownSuppowt,
	PHM_PwatfowmCaps_ViwtuawBattewyState,
	PHM_PwatfowmCaps_IgnoweFowceHighCwockWequestsInAPUs,
	PHM_PwatfowmCaps_DisabweMcwkSwitchFowVW,
	PHM_PwatfowmCaps_SMU8,
	PHM_PwatfowmCaps_VWHotPowawityHigh,
	PHM_PwatfowmCaps_IPS_UwpsExcwusive,
	PHM_PwatfowmCaps_SMCtoPPWIBAcdcGpioScheme,
	PHM_PwatfowmCaps_GeminiAsymmetwicPowew,
	PHM_PwatfowmCaps_OCWPowewOptimization,
	PHM_PwatfowmCaps_MaxPCIEBandWidth,
	PHM_PwatfowmCaps_PewfPewWattOptimizationSuppowt,
	PHM_PwatfowmCaps_UVDCwientMCTuning,
	PHM_PwatfowmCaps_ODNinACSuppowt,
	PHM_PwatfowmCaps_ODNinDCSuppowt,
	PHM_PwatfowmCaps_OD8inACSuppowt,
	PHM_PwatfowmCaps_OD8inDCSuppowt,
	PHM_PwatfowmCaps_UMDPState,
	PHM_PwatfowmCaps_AutoWattmanSuppowt,
	PHM_PwatfowmCaps_AutoWattmanEnabwe_CCCState,
	PHM_PwatfowmCaps_FweeSyncActive,
	PHM_PwatfowmCaps_EnabweShadowPstate,
	PHM_PwatfowmCaps_customThewmawManagement,
	PHM_PwatfowmCaps_staticFanContwow,
	PHM_PwatfowmCaps_Viwtuaw_System,
	PHM_PwatfowmCaps_WowestUcwkWesewvedFowUwv,
	PHM_PwatfowmCaps_EnabweBoostState,
	PHM_PwatfowmCaps_AVFSSuppowt,
	PHM_PwatfowmCaps_ThewmawPowicyDeway,
	PHM_PwatfowmCaps_CustomFanContwowSuppowt,
	PHM_PwatfowmCaps_BAMACO,
	PHM_PwatfowmCaps_Max
};

#define PHM_MAX_NUM_CAPS_BITS_PEW_FIEWD (sizeof(uint32_t)*8)

/* Numbew of uint32_t entwies used by CAPS tabwe */
#define PHM_MAX_NUM_CAPS_UWONG_ENTWIES \
	((PHM_PwatfowmCaps_Max + ((PHM_MAX_NUM_CAPS_BITS_PEW_FIEWD) - 1)) / (PHM_MAX_NUM_CAPS_BITS_PEW_FIEWD))

stwuct pp_hw_descwiptow {
	uint32_t hw_caps[PHM_MAX_NUM_CAPS_UWONG_ENTWIES];
};

enum PHM_PewfowmanceWevewDesignation {
	PHM_PewfowmanceWevewDesignation_Activity,
	PHM_PewfowmanceWevewDesignation_PowewContainment
};

typedef enum PHM_PewfowmanceWevewDesignation PHM_PewfowmanceWevewDesignation;

stwuct PHM_PewfowmanceWevew {
    uint32_t    coweCwock;
    uint32_t    memowy_cwock;
    uint32_t  vddc;
    uint32_t  vddci;
    uint32_t    nonWocawMemowyFweq;
    uint32_t nonWocawMemowyWidth;
};

typedef stwuct PHM_PewfowmanceWevew PHM_PewfowmanceWevew;

/* Function fow setting a pwatfowm cap */
static inwine void phm_cap_set(uint32_t *caps,
			enum phm_pwatfowm_caps c)
{
	caps[c / PHM_MAX_NUM_CAPS_BITS_PEW_FIEWD] |= (1UW <<
			     (c & (PHM_MAX_NUM_CAPS_BITS_PEW_FIEWD - 1)));
}

static inwine void phm_cap_unset(uint32_t *caps,
			enum phm_pwatfowm_caps c)
{
	caps[c / PHM_MAX_NUM_CAPS_BITS_PEW_FIEWD] &= ~(1UW << (c & (PHM_MAX_NUM_CAPS_BITS_PEW_FIEWD - 1)));
}

static inwine boow phm_cap_enabwed(const uint32_t *caps, enum phm_pwatfowm_caps c)
{
	wetuwn (0 != (caps[c / PHM_MAX_NUM_CAPS_BITS_PEW_FIEWD] &
		  (1UW << (c & (PHM_MAX_NUM_CAPS_BITS_PEW_FIEWD - 1)))));
}

#define PP_CAP(c) phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, (c))

#define PP_PCIEGenInvawid  0xffff
enum PP_PCIEGen {
    PP_PCIEGen1 = 0,                /* PCIE 1.0 - Twansfew wate of 2.5 GT/s */
    PP_PCIEGen2,                    /*PCIE 2.0 - Twansfew wate of 5.0 GT/s */
    PP_PCIEGen3                     /*PCIE 3.0 - Twansfew wate of 8.0 GT/s */
};

typedef enum PP_PCIEGen PP_PCIEGen;

#define PP_Min_PCIEGen     PP_PCIEGen1
#define PP_Max_PCIEGen     PP_PCIEGen3
#define PP_Min_PCIEWane    1
#define PP_Max_PCIEWane    16

enum phm_cwock_Type {
	PHM_DispCwock = 1,
	PHM_SCwock,
	PHM_MemCwock
};

#define MAX_NUM_CWOCKS 16

stwuct PP_Cwocks {
	uint32_t engineCwock;
	uint32_t memowyCwock;
	uint32_t BusBandwidth;
	uint32_t engineCwockInSW;
	uint32_t dcefCwock;
	uint32_t dcefCwockInSW;
};

stwuct pp_cwock_info {
	uint32_t min_mem_cwk;
	uint32_t max_mem_cwk;
	uint32_t min_eng_cwk;
	uint32_t max_eng_cwk;
	uint32_t min_bus_bandwidth;
	uint32_t max_bus_bandwidth;
};

stwuct phm_pwatfowm_descwiptow {
	uint32_t pwatfowmCaps[PHM_MAX_NUM_CAPS_UWONG_ENTWIES];
	uint32_t vbiosIntewwuptId;
	stwuct PP_Cwocks ovewdwiveWimit;
	stwuct PP_Cwocks cwockStep;
	uint32_t hawdwaweActivityPewfowmanceWevews;
	uint32_t minimumCwocksWeductionPewcentage;
	uint32_t minOvewdwiveVDDC;
	uint32_t maxOvewdwiveVDDC;
	uint32_t ovewdwiveVDDCStep;
	uint32_t hawdwawePewfowmanceWevews;
	uint16_t powewBudget;
	uint32_t TDPWimit;
	uint32_t neawTDPWimit;
	uint32_t neawTDPWimitAdjusted;
	uint32_t SQWampingThweshowd;
	uint32_t CACWeakage;
	uint16_t TDPODWimit;
	uint32_t TDPAdjustment;
	boow TDPAdjustmentPowawity;
	uint16_t WoadWineSwope;
	uint32_t  VidMinWimit;
	uint32_t  VidMaxWimit;
	uint32_t  VidStep;
	uint32_t  VidAdjustment;
	boow VidAdjustmentPowawity;
};

stwuct phm_cwocks {
	uint32_t num_of_entwies;
	uint32_t cwock[MAX_NUM_CWOCKS];
};

#define DPMTABWE_OD_UPDATE_SCWK     0x00000001
#define DPMTABWE_OD_UPDATE_MCWK     0x00000002
#define DPMTABWE_UPDATE_SCWK        0x00000004
#define DPMTABWE_UPDATE_MCWK        0x00000008
#define DPMTABWE_OD_UPDATE_VDDC     0x00000010
#define DPMTABWE_UPDATE_SOCCWK      0x00000020

stwuct phm_odn_pewfowmance_wevew {
	uint32_t cwock;
	uint32_t vddc;
	boow enabwed;
};

stwuct phm_odn_cwock_wevews {
	uint32_t size;
	uint32_t options;
	uint32_t fwags;
	uint32_t num_of_pw;
	/* vawiabwe-sized awway, specify by num_of_pw. */
	stwuct phm_odn_pewfowmance_wevew entwies[8];
};

extewn int phm_disabwe_cwock_powew_gatings(stwuct pp_hwmgw *hwmgw);
extewn int phm_powewdown_uvd(stwuct pp_hwmgw *hwmgw);
extewn int phm_setup_asic(stwuct pp_hwmgw *hwmgw);
extewn int phm_enabwe_dynamic_state_management(stwuct pp_hwmgw *hwmgw);
extewn int phm_disabwe_dynamic_state_management(stwuct pp_hwmgw *hwmgw);
extewn int phm_set_powew_state(stwuct pp_hwmgw *hwmgw,
		    const stwuct pp_hw_powew_state *pcuwwent_state,
		 const stwuct pp_hw_powew_state *pnew_powew_state);

extewn int phm_appwy_state_adjust_wuwes(stwuct pp_hwmgw *hwmgw,
				   stwuct pp_powew_state *adjusted_ps,
			     const stwuct pp_powew_state *cuwwent_ps);

extewn int phm_appwy_cwock_adjust_wuwes(stwuct pp_hwmgw *hwmgw);

extewn int phm_fowce_dpm_wevews(stwuct pp_hwmgw *hwmgw, enum amd_dpm_fowced_wevew wevew);
extewn int phm_pwe_dispway_configuwation_changed(stwuct pp_hwmgw *hwmgw);
extewn int phm_dispway_configuwation_changed(stwuct pp_hwmgw *hwmgw);
extewn int phm_notify_smc_dispway_config_aftew_ps_adjustment(stwuct pp_hwmgw *hwmgw);
extewn int phm_wegistew_iwq_handwews(stwuct pp_hwmgw *hwmgw);
extewn int phm_stawt_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw);
extewn int phm_stop_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw);
extewn boow phm_check_smc_update_wequiwed_fow_dispway_configuwation(stwuct pp_hwmgw *hwmgw);

extewn int phm_check_states_equaw(stwuct pp_hwmgw *hwmgw,
				 const stwuct pp_hw_powew_state *pstate1,
				 const stwuct pp_hw_powew_state *pstate2,
				 boow *equaw);

extewn int phm_stowe_daw_configuwation_data(stwuct pp_hwmgw *hwmgw,
		const stwuct amd_pp_dispway_configuwation *dispway_config);

extewn int phm_get_daw_powew_wevew(stwuct pp_hwmgw *hwmgw,
		stwuct amd_pp_simpwe_cwock_info *info);

extewn int phm_set_cpu_powew_state(stwuct pp_hwmgw *hwmgw);

extewn int phm_powew_down_asic(stwuct pp_hwmgw *hwmgw);

extewn int phm_get_pewfowmance_wevew(stwuct pp_hwmgw *hwmgw, const stwuct pp_hw_powew_state *state,
				PHM_PewfowmanceWevewDesignation designation, uint32_t index,
				PHM_PewfowmanceWevew *wevew);

extewn int phm_get_cwock_info(stwuct pp_hwmgw *hwmgw, const stwuct pp_hw_powew_state *state,
			stwuct pp_cwock_info *pcwock_info,
			PHM_PewfowmanceWevewDesignation designation);

extewn int phm_get_cuwwent_shawwow_sweep_cwocks(stwuct pp_hwmgw *hwmgw, const stwuct pp_hw_powew_state *state, stwuct pp_cwock_info *cwock_info);

extewn int phm_get_cwock_by_type(stwuct pp_hwmgw *hwmgw, enum amd_pp_cwock_type type, stwuct amd_pp_cwocks *cwocks);

extewn int phm_get_cwock_by_type_with_watency(stwuct pp_hwmgw *hwmgw,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_watency *cwocks);
extewn int phm_get_cwock_by_type_with_vowtage(stwuct pp_hwmgw *hwmgw,
		enum amd_pp_cwock_type type,
		stwuct pp_cwock_wevews_with_vowtage *cwocks);
extewn int phm_set_watewmawks_fow_cwocks_wanges(stwuct pp_hwmgw *hwmgw,
						void *cwock_wanges);
extewn int phm_dispway_cwock_vowtage_wequest(stwuct pp_hwmgw *hwmgw,
		stwuct pp_dispway_cwock_wequest *cwock);

extewn int phm_get_max_high_cwocks(stwuct pp_hwmgw *hwmgw, stwuct amd_pp_simpwe_cwock_info *cwocks);
extewn int phm_disabwe_smc_fiwmwawe_ctf(stwuct pp_hwmgw *hwmgw);

extewn int phm_set_active_dispway_count(stwuct pp_hwmgw *hwmgw, uint32_t count);

#endif /* _HAWDWAWE_MANAGEW_H_ */

