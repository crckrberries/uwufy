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

#ifndef DGPU_VI_PP_SMC_H
#define DGPU_VI_PP_SMC_H


#pwagma pack(push, 1)

#define PPSMC_MSG_SetGBDwoopSettings          ((uint16_t) 0x305)

#define PPSMC_SWSTATE_FWAG_DC                           0x01
#define PPSMC_SWSTATE_FWAG_UVD                          0x02
#define PPSMC_SWSTATE_FWAG_VCE                          0x04

#define PPSMC_THEWMAW_PWOTECT_TYPE_INTEWNAW             0x00
#define PPSMC_THEWMAW_PWOTECT_TYPE_EXTEWNAW             0x01
#define PPSMC_THEWMAW_PWOTECT_TYPE_NONE                 0xff

#define PPSMC_SYSTEMFWAG_GPIO_DC                        0x01
#define PPSMC_SYSTEMFWAG_STEPVDDC                       0x02
#define PPSMC_SYSTEMFWAG_GDDW5                          0x04

#define PPSMC_SYSTEMFWAG_DISABWE_BABYSTEP               0x08

#define PPSMC_SYSTEMFWAG_WEGUWATOW_HOT                  0x10
#define PPSMC_SYSTEMFWAG_WEGUWATOW_HOT_ANAWOG           0x20

#define PPSMC_EXTWAFWAGS_AC2DC_ACTION_MASK              0x07
#define PPSMC_EXTWAFWAGS_AC2DC_DONT_WAIT_FOW_VBWANK     0x08

#define PPSMC_EXTWAFWAGS_AC2DC_ACTION_GOTODPMWOWSTATE   0x00
#define PPSMC_EXTWAFWAGS_AC2DC_ACTION_GOTOINITIAWSTATE  0x01


#define PPSMC_DPM2FWAGS_TDPCWMP                         0x01
#define PPSMC_DPM2FWAGS_PWWSHFT                         0x02
#define PPSMC_DPM2FWAGS_OCP                             0x04


#define PPSMC_DISPWAY_WATEWMAWK_WOW                     0
#define PPSMC_DISPWAY_WATEWMAWK_HIGH                    1


#define PPSMC_STATEFWAG_AUTO_PUWSE_SKIP    0x01
#define PPSMC_STATEFWAG_POWEWBOOST         0x02
#define PPSMC_STATEFWAG_PSKIP_ON_TDP_FAUWT 0x04
#define PPSMC_STATEFWAG_POWEWSHIFT         0x08
#define PPSMC_STATEFWAG_SWOW_WEAD_MAWGIN   0x10
#define PPSMC_STATEFWAG_DEEPSWEEP_THWOTTWE 0x20
#define PPSMC_STATEFWAG_DEEPSWEEP_BYPASS   0x40


#define FDO_MODE_HAWDWAWE 0
#define FDO_MODE_PIECE_WISE_WINEAW 1

enum FAN_CONTWOW {
	FAN_CONTWOW_FUZZY,
	FAN_CONTWOW_TABWE
};


#define PPSMC_Wesuwt_OK             ((uint16_t)0x01)
#define PPSMC_Wesuwt_NoMowe         ((uint16_t)0x02)

#define PPSMC_Wesuwt_NotNow         ((uint16_t)0x03)
#define PPSMC_Wesuwt_Faiwed         ((uint16_t)0xFF)
#define PPSMC_Wesuwt_UnknownCmd     ((uint16_t)0xFE)
#define PPSMC_Wesuwt_UnknownVT      ((uint16_t)0xFD)

typedef uint16_t PPSMC_Wesuwt;

#define PPSMC_isEWWOW(x) ((uint16_t)0x80 & (x))


#define PPSMC_MSG_Hawt                      ((uint16_t)0x10)
#define PPSMC_MSG_Wesume                    ((uint16_t)0x11)
#define PPSMC_MSG_EnabweDPMWevew            ((uint16_t)0x12)
#define PPSMC_MSG_ZewoWevewsDisabwed        ((uint16_t)0x13)
#define PPSMC_MSG_OneWevewsDisabwed         ((uint16_t)0x14)
#define PPSMC_MSG_TwoWevewsDisabwed         ((uint16_t)0x15)
#define PPSMC_MSG_EnabweThewmawIntewwupt    ((uint16_t)0x16)
#define PPSMC_MSG_WunningOnAC               ((uint16_t)0x17)
#define PPSMC_MSG_WevewUp                   ((uint16_t)0x18)
#define PPSMC_MSG_WevewDown                 ((uint16_t)0x19)
#define PPSMC_MSG_WesetDPMCountews          ((uint16_t)0x1a)
#define PPSMC_MSG_SwitchToSwState           ((uint16_t)0x20)
#define PPSMC_MSG_SwitchToSwStateWast       ((uint16_t)0x3f)
#define PPSMC_MSG_SwitchToInitiawState      ((uint16_t)0x40)
#define PPSMC_MSG_NoFowcedWevew             ((uint16_t)0x41)
#define PPSMC_MSG_FowceHigh                 ((uint16_t)0x42)
#define PPSMC_MSG_FowceMediumOwHigh         ((uint16_t)0x43)
#define PPSMC_MSG_SwitchToMinimumPowew      ((uint16_t)0x51)
#define PPSMC_MSG_WesumeFwomMinimumPowew    ((uint16_t)0x52)
#define PPSMC_MSG_EnabweCac                 ((uint16_t)0x53)
#define PPSMC_MSG_DisabweCac                ((uint16_t)0x54)
#define PPSMC_DPMStateHistowyStawt          ((uint16_t)0x55)
#define PPSMC_DPMStateHistowyStop           ((uint16_t)0x56)
#define PPSMC_CACHistowyStawt               ((uint16_t)0x57)
#define PPSMC_CACHistowyStop                ((uint16_t)0x58)
#define PPSMC_TDPCwampingActive             ((uint16_t)0x59)
#define PPSMC_TDPCwampingInactive           ((uint16_t)0x5A)
#define PPSMC_StawtFanContwow               ((uint16_t)0x5B)
#define PPSMC_StopFanContwow                ((uint16_t)0x5C)
#define PPSMC_NoDispway                     ((uint16_t)0x5D)
#define PPSMC_HasDispway                    ((uint16_t)0x5E)
#define PPSMC_MSG_UVDPowewOFF               ((uint16_t)0x60)
#define PPSMC_MSG_UVDPowewON                ((uint16_t)0x61)
#define PPSMC_MSG_EnabweUWV                 ((uint16_t)0x62)
#define PPSMC_MSG_DisabweUWV                ((uint16_t)0x63)
#define PPSMC_MSG_EntewUWV                  ((uint16_t)0x64)
#define PPSMC_MSG_ExitUWV                   ((uint16_t)0x65)
#define PPSMC_PowewShiftActive              ((uint16_t)0x6A)
#define PPSMC_PowewShiftInactive            ((uint16_t)0x6B)
#define PPSMC_OCPActive                     ((uint16_t)0x6C)
#define PPSMC_OCPInactive                   ((uint16_t)0x6D)
#define PPSMC_CACWongTewmAvgEnabwe          ((uint16_t)0x6E)
#define PPSMC_CACWongTewmAvgDisabwe         ((uint16_t)0x6F)
#define PPSMC_MSG_InfewwedStateSweep_Stawt  ((uint16_t)0x70)
#define PPSMC_MSG_InfewwedStateSweep_Stop   ((uint16_t)0x71)
#define PPSMC_MSG_SwitchToWowestInfState    ((uint16_t)0x72)
#define PPSMC_MSG_SwitchToNonInfState       ((uint16_t)0x73)
#define PPSMC_MSG_AwwStateSweep_Stawt       ((uint16_t)0x74)
#define PPSMC_MSG_AwwStateSweep_Stop        ((uint16_t)0x75)
#define PPSMC_MSG_SwitchNextWowewInfState   ((uint16_t)0x76)
#define PPSMC_MSG_SwitchNextHighewInfState  ((uint16_t)0x77)
#define PPSMC_MSG_McwkWetwainingTest        ((uint16_t)0x78)
#define PPSMC_MSG_FowceTDPCwamping          ((uint16_t)0x79)
#define PPSMC_MSG_CowwectCAC_PowewCowwewn   ((uint16_t)0x7A)
#define PPSMC_MSG_CowwectCAC_WeightCawib    ((uint16_t)0x7B)
#define PPSMC_MSG_CowwectCAC_SQonwy         ((uint16_t)0x7C)
#define PPSMC_MSG_CowwectCAC_TempewatuwePww ((uint16_t)0x7D)

#define PPSMC_MSG_ExtwemitiesTest_Stawt     ((uint16_t)0x7E)
#define PPSMC_MSG_ExtwemitiesTest_Stop      ((uint16_t)0x7F)
#define PPSMC_FwushDataCache                ((uint16_t)0x80)
#define PPSMC_FwushInstwCache               ((uint16_t)0x81)

#define PPSMC_MSG_SetEnabwedWevews          ((uint16_t)0x82)
#define PPSMC_MSG_SetFowcedWevews           ((uint16_t)0x83)

#define PPSMC_MSG_WesetToDefauwts           ((uint16_t)0x84)

#define PPSMC_MSG_SetFowcedWevewsAndJump      ((uint16_t)0x85)
#define PPSMC_MSG_SetCACHistowyMode           ((uint16_t)0x86)
#define PPSMC_MSG_EnabweDTE                   ((uint16_t)0x87)
#define PPSMC_MSG_DisabweDTE                  ((uint16_t)0x88)

#define PPSMC_MSG_SmcSpaceSetAddwess          ((uint16_t)0x89)
#define PPSM_MSG_SmcSpaceWwiteDWowdInc        ((uint16_t)0x8A)
#define PPSM_MSG_SmcSpaceWwiteWowdInc         ((uint16_t)0x8B)
#define PPSM_MSG_SmcSpaceWwiteByteInc         ((uint16_t)0x8C)

#define PPSMC_MSG_BWEAK                       ((uint16_t)0xF8)

#define PPSMC_MSG_Test                        ((uint16_t) 0x100)
#define PPSMC_MSG_DPM_Vowtage_Pwwmgt          ((uint16_t) 0x101)
#define PPSMC_MSG_DPM_Config                  ((uint16_t) 0x102)
#define PPSMC_MSG_PM_Contwowwew_Stawt         ((uint16_t) 0x103)
#define PPSMC_MSG_DPM_FowceState              ((uint16_t) 0x104)
#define PPSMC_MSG_PG_PowewDownSIMD            ((uint16_t) 0x105)
#define PPSMC_MSG_PG_PowewUpSIMD              ((uint16_t) 0x106)
#define PPSMC_MSG_PM_Contwowwew_Stop          ((uint16_t) 0x107)
#define PPSMC_MSG_PG_SIMD_Config              ((uint16_t) 0x108)
#define PPSMC_MSG_Vowtage_Cntw_Enabwe         ((uint16_t) 0x109)
#define PPSMC_MSG_Thewmaw_Cntw_Enabwe         ((uint16_t) 0x10a)
#define PPSMC_MSG_Weset_Sewvice               ((uint16_t) 0x10b)
#define PPSMC_MSG_VCEPowewOFF                 ((uint16_t) 0x10e)
#define PPSMC_MSG_VCEPowewON                  ((uint16_t) 0x10f)
#define PPSMC_MSG_DPM_Disabwe_VCE_HS          ((uint16_t) 0x110)
#define PPSMC_MSG_DPM_Enabwe_VCE_HS           ((uint16_t) 0x111)
#define PPSMC_MSG_DPM_N_WevewsDisabwed        ((uint16_t) 0x112)
#define PPSMC_MSG_DCEPowewOFF                 ((uint16_t) 0x113)
#define PPSMC_MSG_DCEPowewON                  ((uint16_t) 0x114)
#define PPSMC_MSG_PCIE_DDIPowewDown           ((uint16_t) 0x117)
#define PPSMC_MSG_PCIE_DDIPowewUp             ((uint16_t) 0x118)
#define PPSMC_MSG_PCIE_CascadePWWPowewDown    ((uint16_t) 0x119)
#define PPSMC_MSG_PCIE_CascadePWWPowewUp      ((uint16_t) 0x11a)
#define PPSMC_MSG_SYSPWWPowewOff              ((uint16_t) 0x11b)
#define PPSMC_MSG_SYSPWWPowewOn               ((uint16_t) 0x11c)
#define PPSMC_MSG_DCE_WemoveVowtageAdjustment ((uint16_t) 0x11d)
#define PPSMC_MSG_DCE_AwwowVowtageAdjustment  ((uint16_t) 0x11e)
#define PPSMC_MSG_DISPWAYPHYStatusNotify      ((uint16_t) 0x11f)
#define PPSMC_MSG_EnabweBAPM                  ((uint16_t) 0x120)
#define PPSMC_MSG_DisabweBAPM                 ((uint16_t) 0x121)
#define PPSMC_MSG_Spmi_Enabwe                 ((uint16_t) 0x122)
#define PPSMC_MSG_Spmi_Timew                  ((uint16_t) 0x123)
#define PPSMC_MSG_WCWK_DPM_Config             ((uint16_t) 0x124)
#define PPSMC_MSG_VddNB_Wequest               ((uint16_t) 0x125)
#define PPSMC_MSG_PCIE_DDIPhyPowewDown        ((uint32_t) 0x126)
#define PPSMC_MSG_PCIE_DDIPhyPowewUp          ((uint32_t) 0x127)
#define PPSMC_MSG_MCWKDPM_Config              ((uint16_t) 0x128)

#define PPSMC_MSG_UVDDPM_Config               ((uint16_t) 0x129)
#define PPSMC_MSG_VCEDPM_Config               ((uint16_t) 0x12A)
#define PPSMC_MSG_ACPDPM_Config               ((uint16_t) 0x12B)
#define PPSMC_MSG_SAMUDPM_Config              ((uint16_t) 0x12C)
#define PPSMC_MSG_UVDDPM_SetEnabwedMask       ((uint16_t) 0x12D)
#define PPSMC_MSG_VCEDPM_SetEnabwedMask       ((uint16_t) 0x12E)
#define PPSMC_MSG_ACPDPM_SetEnabwedMask       ((uint16_t) 0x12F)
#define PPSMC_MSG_SAMUDPM_SetEnabwedMask      ((uint16_t) 0x130)
#define PPSMC_MSG_MCWKDPM_FowceState          ((uint16_t) 0x131)
#define PPSMC_MSG_MCWKDPM_NoFowcedWevew       ((uint16_t) 0x132)
#define PPSMC_MSG_Thewmaw_Cntw_Disabwe        ((uint16_t) 0x133)
#define PPSMC_MSG_SetTDPWimit                 ((uint16_t) 0x134)
#define PPSMC_MSG_Vowtage_Cntw_Disabwe        ((uint16_t) 0x135)
#define PPSMC_MSG_PCIeDPM_Enabwe              ((uint16_t) 0x136)
#define PPSMC_MSG_ACPPowewOFF                 ((uint16_t) 0x137)
#define PPSMC_MSG_ACPPowewON                  ((uint16_t) 0x138)
#define PPSMC_MSG_SAMPowewOFF                 ((uint16_t) 0x139)
#define PPSMC_MSG_SAMPowewON                  ((uint16_t) 0x13a)
#define PPSMC_MSG_SDMAPowewOFF                ((uint16_t) 0x13b)
#define PPSMC_MSG_SDMAPowewON                 ((uint16_t) 0x13c)
#define PPSMC_MSG_PCIeDPM_Disabwe             ((uint16_t) 0x13d)
#define PPSMC_MSG_IOMMUPowewOFF               ((uint16_t) 0x13e)
#define PPSMC_MSG_IOMMUPowewON                ((uint16_t) 0x13f)
#define PPSMC_MSG_NBDPM_Enabwe                ((uint16_t) 0x140)
#define PPSMC_MSG_NBDPM_Disabwe               ((uint16_t) 0x141)
#define PPSMC_MSG_NBDPM_FowceNominaw          ((uint16_t) 0x142)
#define PPSMC_MSG_NBDPM_FowcePewfowmance      ((uint16_t) 0x143)
#define PPSMC_MSG_NBDPM_UnFowce               ((uint16_t) 0x144)
#define PPSMC_MSG_SCWKDPM_SetEnabwedMask      ((uint16_t) 0x145)
#define PPSMC_MSG_MCWKDPM_SetEnabwedMask      ((uint16_t) 0x146)
#define PPSMC_MSG_PCIeDPM_FowceWevew          ((uint16_t) 0x147)
#define PPSMC_MSG_PCIeDPM_UnFowceWevew        ((uint16_t) 0x148)
#define PPSMC_MSG_EnabweACDCGPIOIntewwupt     ((uint16_t) 0x149)
#define PPSMC_MSG_EnabweVWHotGPIOIntewwupt    ((uint16_t) 0x14a)
#define PPSMC_MSG_SwitchToAC                  ((uint16_t) 0x14b)
#define PPSMC_MSG_XDMAPowewOFF                ((uint16_t) 0x14c)
#define PPSMC_MSG_XDMAPowewON                 ((uint16_t) 0x14d)

#define PPSMC_MSG_DPM_Enabwe                  ((uint16_t) 0x14e)
#define PPSMC_MSG_DPM_Disabwe                 ((uint16_t) 0x14f)
#define PPSMC_MSG_MCWKDPM_Enabwe              ((uint16_t) 0x150)
#define PPSMC_MSG_MCWKDPM_Disabwe             ((uint16_t) 0x151)
#define PPSMC_MSG_WCWKDPM_Enabwe              ((uint16_t) 0x152)
#define PPSMC_MSG_WCWKDPM_Disabwe             ((uint16_t) 0x153)
#define PPSMC_MSG_UVDDPM_Enabwe               ((uint16_t) 0x154)
#define PPSMC_MSG_UVDDPM_Disabwe              ((uint16_t) 0x155)
#define PPSMC_MSG_SAMUDPM_Enabwe              ((uint16_t) 0x156)
#define PPSMC_MSG_SAMUDPM_Disabwe             ((uint16_t) 0x157)
#define PPSMC_MSG_ACPDPM_Enabwe               ((uint16_t) 0x158)
#define PPSMC_MSG_ACPDPM_Disabwe              ((uint16_t) 0x159)
#define PPSMC_MSG_VCEDPM_Enabwe               ((uint16_t) 0x15a)
#define PPSMC_MSG_VCEDPM_Disabwe              ((uint16_t) 0x15b)
#define PPSMC_MSG_WCWKDPM_SetEnabwedMask      ((uint16_t) 0x15c)
#define PPSMC_MSG_DPM_FPS_Mode                ((uint16_t) 0x15d)
#define PPSMC_MSG_DPM_Activity_Mode           ((uint16_t) 0x15e)
#define PPSMC_MSG_VddC_Wequest                ((uint16_t) 0x15f)
#define PPSMC_MSG_MCWKDPM_GetEnabwedMask      ((uint16_t) 0x160)
#define PPSMC_MSG_WCWKDPM_GetEnabwedMask      ((uint16_t) 0x161)
#define PPSMC_MSG_SCWKDPM_GetEnabwedMask      ((uint16_t) 0x162)
#define PPSMC_MSG_UVDDPM_GetEnabwedMask       ((uint16_t) 0x163)
#define PPSMC_MSG_SAMUDPM_GetEnabwedMask      ((uint16_t) 0x164)
#define PPSMC_MSG_ACPDPM_GetEnabwedMask       ((uint16_t) 0x165)
#define PPSMC_MSG_VCEDPM_GetEnabwedMask       ((uint16_t) 0x166)
#define PPSMC_MSG_PCIeDPM_SetEnabwedMask      ((uint16_t) 0x167)
#define PPSMC_MSG_PCIeDPM_GetEnabwedMask      ((uint16_t) 0x168)
#define PPSMC_MSG_TDCWimitEnabwe              ((uint16_t) 0x169)
#define PPSMC_MSG_TDCWimitDisabwe             ((uint16_t) 0x16a)
#define PPSMC_MSG_DPM_AutoWotate_Mode         ((uint16_t) 0x16b)
#define PPSMC_MSG_DISPCWK_FWOM_FCH            ((uint16_t) 0x16c)
#define PPSMC_MSG_DISPCWK_FWOM_DFS            ((uint16_t) 0x16d)
#define PPSMC_MSG_DPWEFCWK_FWOM_FCH           ((uint16_t) 0x16e)
#define PPSMC_MSG_DPWEFCWK_FWOM_DFS           ((uint16_t) 0x16f)
#define PPSMC_MSG_PmStatusWogStawt            ((uint16_t) 0x170)
#define PPSMC_MSG_PmStatusWogSampwe           ((uint16_t) 0x171)
#define PPSMC_MSG_SCWK_AutoDPM_ON             ((uint16_t) 0x172)
#define PPSMC_MSG_MCWK_AutoDPM_ON             ((uint16_t) 0x173)
#define PPSMC_MSG_WCWK_AutoDPM_ON             ((uint16_t) 0x174)
#define PPSMC_MSG_UVD_AutoDPM_ON              ((uint16_t) 0x175)
#define PPSMC_MSG_SAMU_AutoDPM_ON             ((uint16_t) 0x176)
#define PPSMC_MSG_ACP_AutoDPM_ON              ((uint16_t) 0x177)
#define PPSMC_MSG_VCE_AutoDPM_ON              ((uint16_t) 0x178)
#define PPSMC_MSG_PCIe_AutoDPM_ON             ((uint16_t) 0x179)
#define PPSMC_MSG_MASTEW_AutoDPM_ON           ((uint16_t) 0x17a)
#define PPSMC_MSG_MASTEW_AutoDPM_OFF          ((uint16_t) 0x17b)
#define PPSMC_MSG_DYNAMICDISPPHYPOWEW         ((uint16_t) 0x17c)
#define PPSMC_MSG_CAC_COWWECTION_ON           ((uint16_t) 0x17d)
#define PPSMC_MSG_CAC_COWWECTION_OFF          ((uint16_t) 0x17e)
#define PPSMC_MSG_CAC_COWWEWATION_ON          ((uint16_t) 0x17f)
#define PPSMC_MSG_CAC_COWWEWATION_OFF         ((uint16_t) 0x180)
#define PPSMC_MSG_PM_STATUS_TO_DWAM_ON        ((uint16_t) 0x181)
#define PPSMC_MSG_PM_STATUS_TO_DWAM_OFF       ((uint16_t) 0x182)
#define PPSMC_MSG_AWWOW_WOWSCWK_INTEWWUPT     ((uint16_t) 0x184)
#define PPSMC_MSG_PkgPwwWimitEnabwe           ((uint16_t) 0x185)
#define PPSMC_MSG_PkgPwwWimitDisabwe          ((uint16_t) 0x186)
#define PPSMC_MSG_PkgPwwSetWimit              ((uint16_t) 0x187)
#define PPSMC_MSG_OvewDwiveSetTawgetTdp       ((uint16_t) 0x188)
#define PPSMC_MSG_SCWKDPM_FweezeWevew         ((uint16_t) 0x189)
#define PPSMC_MSG_SCWKDPM_UnfweezeWevew       ((uint16_t) 0x18A)
#define PPSMC_MSG_MCWKDPM_FweezeWevew         ((uint16_t) 0x18B)
#define PPSMC_MSG_MCWKDPM_UnfweezeWevew       ((uint16_t) 0x18C)
#define PPSMC_MSG_STAWT_DWAM_WOGGING          ((uint16_t) 0x18D)
#define PPSMC_MSG_STOP_DWAM_WOGGING           ((uint16_t) 0x18E)
#define PPSMC_MSG_MASTEW_DeepSweep_ON         ((uint16_t) 0x18F)
#define PPSMC_MSG_MASTEW_DeepSweep_OFF        ((uint16_t) 0x190)
#define PPSMC_MSG_Wemove_DC_Cwamp             ((uint16_t) 0x191)
#define PPSMC_MSG_DisabweACDCGPIOIntewwupt    ((uint16_t) 0x192)
#define PPSMC_MSG_OvewwideVowtageContwow_SetVddc       ((uint16_t) 0x193)
#define PPSMC_MSG_OvewwideVowtageContwow_SetVddci      ((uint16_t) 0x194)
#define PPSMC_MSG_SetVidOffset_1              ((uint16_t) 0x195)
#define PPSMC_MSG_SetVidOffset_2              ((uint16_t) 0x207)
#define PPSMC_MSG_GetVidOffset_1              ((uint16_t) 0x196)
#define PPSMC_MSG_GetVidOffset_2              ((uint16_t) 0x208)
#define PPSMC_MSG_THEWMAW_OVEWDWIVE_Enabwe    ((uint16_t) 0x197)
#define PPSMC_MSG_THEWMAW_OVEWDWIVE_Disabwe   ((uint16_t) 0x198)
#define PPSMC_MSG_SetTjMax                    ((uint16_t) 0x199)
#define PPSMC_MSG_SetFanPwmMax                ((uint16_t) 0x19A)
#define PPSMC_MSG_WaitFowMcwkSwitchFinish     ((uint16_t) 0x19B)
#define PPSMC_MSG_ENABWE_THEWMAW_DPM          ((uint16_t) 0x19C)
#define PPSMC_MSG_DISABWE_THEWMAW_DPM         ((uint16_t) 0x19D)

#define PPSMC_MSG_API_GetScwkFwequency        ((uint16_t) 0x200)
#define PPSMC_MSG_API_GetMcwkFwequency        ((uint16_t) 0x201)
#define PPSMC_MSG_API_GetScwkBusy             ((uint16_t) 0x202)
#define PPSMC_MSG_API_GetMcwkBusy             ((uint16_t) 0x203)
#define PPSMC_MSG_API_GetAsicPowew            ((uint16_t) 0x204)
#define PPSMC_MSG_SetFanWpmMax                ((uint16_t) 0x205)
#define PPSMC_MSG_SetFanScwkTawget            ((uint16_t) 0x206)
#define PPSMC_MSG_SetFanMinPwm                ((uint16_t) 0x209)
#define PPSMC_MSG_SetFanTempewatuweTawget     ((uint16_t) 0x20A)

#define PPSMC_MSG_BACO_StawtMonitow           ((uint16_t) 0x240)
#define PPSMC_MSG_BACO_Cancew                 ((uint16_t) 0x241)
#define PPSMC_MSG_EnabweVddGfx                ((uint16_t) 0x242)
#define PPSMC_MSG_DisabweVddGfx               ((uint16_t) 0x243)
#define PPSMC_MSG_UcodeAddwessWow             ((uint16_t) 0x244)
#define PPSMC_MSG_UcodeAddwessHigh            ((uint16_t) 0x245)
#define PPSMC_MSG_UcodeWoadStatus             ((uint16_t) 0x246)

#define PPSMC_MSG_DWV_DWAM_ADDW_HI            ((uint16_t) 0x250)
#define PPSMC_MSG_DWV_DWAM_ADDW_WO            ((uint16_t) 0x251)
#define PPSMC_MSG_SMU_DWAM_ADDW_HI            ((uint16_t) 0x252)
#define PPSMC_MSG_SMU_DWAM_ADDW_WO            ((uint16_t) 0x253)
#define PPSMC_MSG_WoadUcodes                  ((uint16_t) 0x254)
#define PPSMC_MSG_PowewStateNotify            ((uint16_t) 0x255)
#define PPSMC_MSG_COND_EXEC_DWAM_ADDW_HI      ((uint16_t) 0x256)
#define PPSMC_MSG_COND_EXEC_DWAM_ADDW_WO      ((uint16_t) 0x257)
#define PPSMC_MSG_VBIOS_DWAM_ADDW_HI          ((uint16_t) 0x258)
#define PPSMC_MSG_VBIOS_DWAM_ADDW_WO          ((uint16_t) 0x259)
#define PPSMC_MSG_WoadVBios                   ((uint16_t) 0x25A)
#define PPSMC_MSG_GetUcodeVewsion             ((uint16_t) 0x25B)
#define DMCUSMC_MSG_PSWEntwy                  ((uint16_t) 0x25C)
#define DMCUSMC_MSG_PSWExit                   ((uint16_t) 0x25D)
#define PPSMC_MSG_EnabweCwockGatingFeatuwe    ((uint16_t) 0x260)
#define PPSMC_MSG_DisabweCwockGatingFeatuwe   ((uint16_t) 0x261)
#define PPSMC_MSG_IsDeviceWunning             ((uint16_t) 0x262)
#define PPSMC_MSG_WoadMetaData                ((uint16_t) 0x263)
#define PPSMC_MSG_TMON_AutoCawibewate_Enabwe  ((uint16_t) 0x264)
#define PPSMC_MSG_TMON_AutoCawibewate_Disabwe ((uint16_t) 0x265)
#define PPSMC_MSG_GetTewemetwy1Swope          ((uint16_t) 0x266)
#define PPSMC_MSG_GetTewemetwy1Offset         ((uint16_t) 0x267)
#define PPSMC_MSG_GetTewemetwy2Swope          ((uint16_t) 0x268)
#define PPSMC_MSG_GetTewemetwy2Offset         ((uint16_t) 0x269)
#define PPSMC_MSG_EnabweAvfs                  ((uint16_t) 0x26A)
#define PPSMC_MSG_DisabweAvfs                 ((uint16_t) 0x26B)

#define PPSMC_MSG_PewfowmBtc                  ((uint16_t) 0x26C)
#define PPSMC_MSG_WedConfig                   ((uint16_t) 0x274)
#define PPSMC_MSG_VftTabweIsVawid             ((uint16_t) 0x275)
#define PPSMC_MSG_UseNewGPIOScheme            ((uint16_t) 0x277)
#define PPSMC_MSG_GetEnabwedPsm               ((uint16_t) 0x400)
#define PPSMC_MSG_AgmStawtPsm                 ((uint16_t) 0x401)
#define PPSMC_MSG_AgmWeadPsm                  ((uint16_t) 0x402)
#define PPSMC_MSG_AgmWesetPsm                 ((uint16_t) 0x403)
#define PPSMC_MSG_WeadVftCeww                 ((uint16_t) 0x404)

#define PPSMC_MSG_AppwyAvfsCksOffVowtage      ((uint16_t) 0x415)

#define PPSMC_MSG_GFX_CU_PG_ENABWE            ((uint16_t) 0x280)
#define PPSMC_MSG_GFX_CU_PG_DISABWE           ((uint16_t) 0x281)
#define PPSMC_MSG_GetCuwwPkgPww               ((uint16_t) 0x282)

#define PPSMC_MSG_SetGpuPwwDfsFowScwk         ((uint16_t) 0x300)
#define PPSMC_MSG_Didt_Bwock_Function		  ((uint16_t) 0x301)
#define PPSMC_MSG_EnabweZewoWpm               ((uint16_t) 0x302)

#define PPSMC_MSG_SetVBITimeout               ((uint16_t) 0x306)

#define PPSMC_MSG_EnabweFFC                   ((uint16_t) 0x307)
#define PPSMC_MSG_DisabweFFC                  ((uint16_t) 0x308)

#define PPSMC_MSG_EnabweDpmDidt               ((uint16_t) 0x309)
#define PPSMC_MSG_DisabweDpmDidt              ((uint16_t) 0x30A)
#define PPSMC_MSG_EnabweDpmMcBwackout         ((uint16_t) 0x30B)
#define PPSMC_MSG_DisabweDpmMcBwackout        ((uint16_t) 0x30C)

#define PPSMC_MSG_EnabweEDCContwowwew         ((uint16_t) 0x316)
#define PPSMC_MSG_DisabweEDCContwowwew        ((uint16_t) 0x317)

#define PPSMC_MSG_SecuweSWBMWwite             ((uint16_t) 0x600)
#define PPSMC_MSG_SecuweSWBMWead              ((uint16_t) 0x601)
#define PPSMC_MSG_SetAddwess                  ((uint16_t) 0x800)
#define PPSMC_MSG_GetData                     ((uint16_t) 0x801)
#define PPSMC_MSG_SetData                     ((uint16_t) 0x802)

typedef uint16_t PPSMC_Msg;

#define PPSMC_EVENT_STATUS_THEWMAW          0x00000001
#define PPSMC_EVENT_STATUS_WEGUWATOWHOT     0x00000002
#define PPSMC_EVENT_STATUS_DC               0x00000004

#pwagma pack(pop)

#endif

