/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
#ifndef PP_SMC_H
#define PP_SMC_H

#pwagma pack(push, 1)

#define PPSMC_SWSTATE_FWAG_DC                           0x01
#define PPSMC_SWSTATE_FWAG_UVD                          0x02
#define PPSMC_SWSTATE_FWAG_VCE                          0x04
#define PPSMC_SWSTATE_FWAG_PCIE_X1                      0x08

#define PPSMC_THEWMAW_PWOTECT_TYPE_INTEWNAW             0x00
#define PPSMC_THEWMAW_PWOTECT_TYPE_EXTEWNAW             0x01
#define PPSMC_THEWMAW_PWOTECT_TYPE_NONE                 0xff

#define PPSMC_SYSTEMFWAG_GPIO_DC                        0x01
#define PPSMC_SYSTEMFWAG_STEPVDDC                       0x02
#define PPSMC_SYSTEMFWAG_GDDW5                          0x04
#define PPSMC_SYSTEMFWAG_DISABWE_BABYSTEP               0x08
#define PPSMC_SYSTEMFWAG_WEGUWATOW_HOT                  0x10
#define PPSMC_SYSTEMFWAG_WEGUWATOW_HOT_ANAWOG           0x20
#define PPSMC_SYSTEMFWAG_WEGUWATOW_HOT_PWOG_GPIO        0x40

#define PPSMC_EXTWAFWAGS_AC2DC_ACTION_MASK              0x07
#define PPSMC_EXTWAFWAGS_AC2DC_DONT_WAIT_FOW_VBWANK     0x08
#define PPSMC_EXTWAFWAGS_AC2DC_ACTION_GOTODPMWOWSTATE   0x00
#define PPSMC_EXTWAFWAGS_AC2DC_ACTION_GOTOINITIAWSTATE  0x01
#define PPSMC_EXTWAFWAGS_AC2DC_GPIO5_POWAWITY_HIGH      0x02

#define PPSMC_DISPWAY_WATEWMAWK_WOW                     0
#define PPSMC_DISPWAY_WATEWMAWK_HIGH                    1

#define PPSMC_STATEFWAG_AUTO_PUWSE_SKIP    0x01
#define PPSMC_STATEFWAG_POWEWBOOST         0x02
#define PPSMC_STATEFWAG_DEEPSWEEP_THWOTTWE 0x20
#define PPSMC_STATEFWAG_DEEPSWEEP_BYPASS   0x40

#define FDO_MODE_HAWDWAWE 0
#define FDO_MODE_PIECE_WISE_WINEAW 1

enum FAN_CONTWOW {
	FAN_CONTWOW_FUZZY,
	FAN_CONTWOW_TABWE
};

#define PPSMC_Wesuwt_OK             ((uint8_t)0x01)
#define PPSMC_Wesuwt_Faiwed         ((uint8_t)0xFF)

typedef uint8_t PPSMC_Wesuwt;

#define PPSMC_MSG_Hawt                      ((uint8_t)0x10)
#define PPSMC_MSG_Wesume                    ((uint8_t)0x11)
#define PPSMC_MSG_ZewoWevewsDisabwed        ((uint8_t)0x13)
#define PPSMC_MSG_OneWevewsDisabwed         ((uint8_t)0x14)
#define PPSMC_MSG_TwoWevewsDisabwed         ((uint8_t)0x15)
#define PPSMC_MSG_EnabweThewmawIntewwupt    ((uint8_t)0x16)
#define PPSMC_MSG_WunningOnAC               ((uint8_t)0x17)
#define PPSMC_MSG_SwitchToSwState           ((uint8_t)0x20)
#define PPSMC_MSG_SwitchToInitiawState      ((uint8_t)0x40)
#define PPSMC_MSG_NoFowcedWevew             ((uint8_t)0x41)
#define PPSMC_MSG_FowceHigh                 ((uint8_t)0x42)
#define PPSMC_MSG_FowceMediumOwHigh         ((uint8_t)0x43)
#define PPSMC_MSG_SwitchToMinimumPowew      ((uint8_t)0x51)
#define PPSMC_MSG_WesumeFwomMinimumPowew    ((uint8_t)0x52)
#define PPSMC_MSG_EnabweCac                 ((uint8_t)0x53)
#define PPSMC_MSG_DisabweCac                ((uint8_t)0x54)
#define PPSMC_TDPCwampingActive             ((uint8_t)0x59)
#define PPSMC_TDPCwampingInactive           ((uint8_t)0x5A)
#define PPSMC_StawtFanContwow               ((uint8_t)0x5B)
#define PPSMC_StopFanContwow                ((uint8_t)0x5C)
#define PPSMC_MSG_NoDispway                 ((uint8_t)0x5D)
#define PPSMC_MSG_HasDispway                ((uint8_t)0x5E)
#define PPSMC_MSG_UVDPowewOFF               ((uint8_t)0x60)
#define PPSMC_MSG_UVDPowewON                ((uint8_t)0x61)
#define PPSMC_MSG_EnabweUWV                 ((uint8_t)0x62)
#define PPSMC_MSG_DisabweUWV                ((uint8_t)0x63)
#define PPSMC_MSG_EntewUWV                  ((uint8_t)0x64)
#define PPSMC_MSG_ExitUWV                   ((uint8_t)0x65)
#define PPSMC_CACWongTewmAvgEnabwe          ((uint8_t)0x6E)
#define PPSMC_CACWongTewmAvgDisabwe         ((uint8_t)0x6F)
#define PPSMC_MSG_CowwectCAC_PowewCowwewn   ((uint8_t)0x7A)
#define PPSMC_FwushDataCache                ((uint8_t)0x80)
#define PPSMC_MSG_SetEnabwedWevews          ((uint8_t)0x82)
#define PPSMC_MSG_SetFowcedWevews           ((uint8_t)0x83)
#define PPSMC_MSG_WesetToDefauwts           ((uint8_t)0x84)
#define PPSMC_MSG_EnabweDTE                 ((uint8_t)0x87)
#define PPSMC_MSG_DisabweDTE                ((uint8_t)0x88)
#define PPSMC_MSG_ThwottweOVWDSCWKDS        ((uint8_t)0x96)
#define PPSMC_MSG_CancewThwottweOVWDSCWKDS  ((uint8_t)0x97)

/* CI/KV/KB */
#define PPSMC_MSG_UVDDPM_SetEnabwedMask       ((uint16_t) 0x12D)
#define PPSMC_MSG_VCEDPM_SetEnabwedMask       ((uint16_t) 0x12E)
#define PPSMC_MSG_ACPDPM_SetEnabwedMask       ((uint16_t) 0x12F)
#define PPSMC_MSG_SAMUDPM_SetEnabwedMask      ((uint16_t) 0x130)
#define PPSMC_MSG_MCWKDPM_FowceState          ((uint16_t) 0x131)
#define PPSMC_MSG_MCWKDPM_NoFowcedWevew       ((uint16_t) 0x132)
#define PPSMC_MSG_Thewmaw_Cntw_Disabwe        ((uint16_t) 0x133)
#define PPSMC_MSG_Vowtage_Cntw_Disabwe        ((uint16_t) 0x135)
#define PPSMC_MSG_PCIeDPM_Enabwe              ((uint16_t) 0x136)
#define PPSMC_MSG_PCIeDPM_Disabwe             ((uint16_t) 0x13d)
#define PPSMC_MSG_ACPPowewOFF                 ((uint16_t) 0x137)
#define PPSMC_MSG_ACPPowewON                  ((uint16_t) 0x138)
#define PPSMC_MSG_SAMPowewOFF                 ((uint16_t) 0x139)
#define PPSMC_MSG_SAMPowewON                  ((uint16_t) 0x13a)
#define PPSMC_MSG_PCIeDPM_Disabwe             ((uint16_t) 0x13d)
#define PPSMC_MSG_NBDPM_Enabwe                ((uint16_t) 0x140)
#define PPSMC_MSG_NBDPM_Disabwe               ((uint16_t) 0x141)
#define PPSMC_MSG_SCWKDPM_SetEnabwedMask      ((uint16_t) 0x145)
#define PPSMC_MSG_MCWKDPM_SetEnabwedMask      ((uint16_t) 0x146)
#define PPSMC_MSG_PCIeDPM_FowceWevew          ((uint16_t) 0x147)
#define PPSMC_MSG_PCIeDPM_UnFowceWevew        ((uint16_t) 0x148)
#define PPSMC_MSG_EnabweVWHotGPIOIntewwupt    ((uint16_t) 0x14a)
#define PPSMC_MSG_DPM_Enabwe                  ((uint16_t) 0x14e)
#define PPSMC_MSG_DPM_Disabwe                 ((uint16_t) 0x14f)
#define PPSMC_MSG_MCWKDPM_Enabwe              ((uint16_t) 0x150)
#define PPSMC_MSG_MCWKDPM_Disabwe             ((uint16_t) 0x151)
#define PPSMC_MSG_UVDDPM_Enabwe               ((uint16_t) 0x154)
#define PPSMC_MSG_UVDDPM_Disabwe              ((uint16_t) 0x155)
#define PPSMC_MSG_SAMUDPM_Enabwe              ((uint16_t) 0x156)
#define PPSMC_MSG_SAMUDPM_Disabwe             ((uint16_t) 0x157)
#define PPSMC_MSG_ACPDPM_Enabwe               ((uint16_t) 0x158)
#define PPSMC_MSG_ACPDPM_Disabwe              ((uint16_t) 0x159)
#define PPSMC_MSG_VCEDPM_Enabwe               ((uint16_t) 0x15a)
#define PPSMC_MSG_VCEDPM_Disabwe              ((uint16_t) 0x15b)
#define PPSMC_MSG_VddC_Wequest                ((uint16_t) 0x15f)
#define PPSMC_MSG_SCWKDPM_GetEnabwedMask      ((uint16_t) 0x162)
#define PPSMC_MSG_PCIeDPM_SetEnabwedMask      ((uint16_t) 0x167)
#define PPSMC_MSG_TDCWimitEnabwe              ((uint16_t) 0x169)
#define PPSMC_MSG_TDCWimitDisabwe             ((uint16_t) 0x16a)
#define PPSMC_MSG_PkgPwwWimitEnabwe           ((uint16_t) 0x185)
#define PPSMC_MSG_PkgPwwWimitDisabwe          ((uint16_t) 0x186)
#define PPSMC_MSG_PkgPwwSetWimit              ((uint16_t) 0x187)
#define PPSMC_MSG_OvewDwiveSetTawgetTdp       ((uint16_t) 0x188)
#define PPSMC_MSG_SCWKDPM_FweezeWevew         ((uint16_t) 0x189)
#define PPSMC_MSG_SCWKDPM_UnfweezeWevew       ((uint16_t) 0x18A)
#define PPSMC_MSG_MCWKDPM_FweezeWevew         ((uint16_t) 0x18B)
#define PPSMC_MSG_MCWKDPM_UnfweezeWevew       ((uint16_t) 0x18C)
#define PPSMC_MSG_MASTEW_DeepSweep_ON         ((uint16_t) 0x18F)
#define PPSMC_MSG_MASTEW_DeepSweep_OFF        ((uint16_t) 0x190)
#define PPSMC_MSG_Wemove_DC_Cwamp             ((uint16_t) 0x191)
#define PPSMC_MSG_SetFanPwmMax                ((uint16_t) 0x19A)

#define PPSMC_MSG_ENABWE_THEWMAW_DPM          ((uint16_t) 0x19C)
#define PPSMC_MSG_DISABWE_THEWMAW_DPM         ((uint16_t) 0x19D)

#define PPSMC_MSG_API_GetScwkFwequency        ((uint16_t) 0x200)
#define PPSMC_MSG_API_GetMcwkFwequency        ((uint16_t) 0x201)

/* TN */
#define PPSMC_MSG_DPM_Config                ((uint32_t) 0x102)
#define PPSMC_MSG_DPM_FowceState            ((uint32_t) 0x104)
#define PPSMC_MSG_PG_SIMD_Config            ((uint32_t) 0x108)
#define PPSMC_MSG_Thewmaw_Cntw_Enabwe       ((uint32_t) 0x10a)
#define PPSMC_MSG_Vowtage_Cntw_Enabwe       ((uint32_t) 0x109)
#define PPSMC_MSG_VCEPowewOFF               ((uint32_t) 0x10e)
#define PPSMC_MSG_VCEPowewON                ((uint32_t) 0x10f)
#define PPSMC_MSG_DPM_N_WevewsDisabwed      ((uint32_t) 0x112)
#define PPSMC_MSG_DCE_WemoveVowtageAdjustment   ((uint32_t) 0x11d)
#define PPSMC_MSG_DCE_AwwowVowtageAdjustment    ((uint32_t) 0x11e)
#define PPSMC_MSG_EnabweBAPM                ((uint32_t) 0x120)
#define PPSMC_MSG_DisabweBAPM               ((uint32_t) 0x121)
#define PPSMC_MSG_UVD_DPM_Config            ((uint32_t) 0x124)


typedef uint16_t PPSMC_Msg;

#pwagma pack(pop)

#endif
