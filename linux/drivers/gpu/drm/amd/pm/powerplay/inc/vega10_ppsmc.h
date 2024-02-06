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

#ifndef PP_SMC_H
#define PP_SMC_H

#pwagma pack(push, 1)

#define SMU_UCODE_VEWSION                  0x001c0800

/* SMU Wesponse Codes: */
#define PPSMC_Wesuwt_OK                    0x1
#define PPSMC_Wesuwt_Faiwed                0xFF
#define PPSMC_Wesuwt_UnknownCmd            0xFE
#define PPSMC_Wesuwt_CmdWejectedPweweq     0xFD
#define PPSMC_Wesuwt_CmdWejectedBusy       0xFC

typedef uint16_t PPSMC_Wesuwt;

/* Message Definitions */
#define PPSMC_MSG_TestMessage                    0x1
#define PPSMC_MSG_GetSmuVewsion                  0x2
#define PPSMC_MSG_GetDwivewIfVewsion             0x3
#define PPSMC_MSG_EnabweSmuFeatuwes              0x4
#define PPSMC_MSG_DisabweSmuFeatuwes             0x5
#define PPSMC_MSG_GetEnabwedSmuFeatuwes          0x6
#define PPSMC_MSG_SetWowkwoadMask                0x7
#define PPSMC_MSG_SetPptWimit                    0x8
#define PPSMC_MSG_SetDwivewDwamAddwHigh          0x9
#define PPSMC_MSG_SetDwivewDwamAddwWow           0xA
#define PPSMC_MSG_SetToowsDwamAddwHigh           0xB
#define PPSMC_MSG_SetToowsDwamAddwWow            0xC
#define PPSMC_MSG_TwansfewTabweSmu2Dwam          0xD
#define PPSMC_MSG_TwansfewTabweDwam2Smu          0xE
#define PPSMC_MSG_UseDefauwtPPTabwe              0xF
#define PPSMC_MSG_UseBackupPPTabwe               0x10
#define PPSMC_MSG_WunBtc                         0x11
#define PPSMC_MSG_WequestI2CBus                  0x12
#define PPSMC_MSG_WeweaseI2CBus                  0x13
#define PPSMC_MSG_ConfiguweTewemetwy             0x14
#define PPSMC_MSG_SetUwvIpMask                   0x15
#define PPSMC_MSG_SetSocVidOffset                0x16
#define PPSMC_MSG_SetMemVidOffset                0x17
#define PPSMC_MSG_GetSocVidOffset                0x18
#define PPSMC_MSG_GetMemVidOffset                0x19
#define PPSMC_MSG_SetFwoowSocVowtage             0x1A
#define PPSMC_MSG_SoftWeset                      0x1B
#define PPSMC_MSG_StawtBacoMonitow               0x1C
#define PPSMC_MSG_CancewBacoMonitow              0x1D
#define PPSMC_MSG_EntewBaco                      0x1E
#define PPSMC_MSG_AwwowWowGfxcwkIntewwupt        0x1F
#define PPSMC_MSG_SetWowGfxcwkIntewwuptThweshowd 0x20
#define PPSMC_MSG_SetSoftMinGfxcwkByIndex        0x21
#define PPSMC_MSG_SetSoftMaxGfxcwkByIndex        0x22
#define PPSMC_MSG_GetCuwwentGfxcwkIndex          0x23
#define PPSMC_MSG_SetSoftMinUcwkByIndex          0x24
#define PPSMC_MSG_SetSoftMaxUcwkByIndex          0x25
#define PPSMC_MSG_GetCuwwentUcwkIndex            0x26
#define PPSMC_MSG_SetSoftMinUvdByIndex           0x27
#define PPSMC_MSG_SetSoftMaxUvdByIndex           0x28
#define PPSMC_MSG_GetCuwwentUvdIndex             0x29
#define PPSMC_MSG_SetSoftMinVceByIndex           0x2A
#define PPSMC_MSG_SetSoftMaxVceByIndex           0x2B
#define PPSMC_MSG_SetHawdMinVceByIndex           0x2C
#define PPSMC_MSG_GetCuwwentVceIndex             0x2D
#define PPSMC_MSG_SetSoftMinSoccwkByIndex        0x2E
#define PPSMC_MSG_SetHawdMinSoccwkByIndex        0x2F
#define PPSMC_MSG_SetSoftMaxSoccwkByIndex        0x30
#define PPSMC_MSG_GetCuwwentSoccwkIndex          0x31
#define PPSMC_MSG_SetMinWinkDpmByIndex           0x32
#define PPSMC_MSG_GetCuwwentWinkIndex            0x33
#define PPSMC_MSG_GetAvewageGfxcwkFwequency      0x34
#define PPSMC_MSG_GetAvewageSoccwkFwequency      0x35
#define PPSMC_MSG_GetAvewageUcwkFwequency        0x36
#define PPSMC_MSG_GetAvewageGfxActivity          0x37
#define PPSMC_MSG_GetTempewatuweEdge             0x38
#define PPSMC_MSG_GetTempewatuweHotspot          0x39
#define PPSMC_MSG_GetTempewatuweHBM              0x3A
#define PPSMC_MSG_GetTempewatuweVwSoc            0x3B
#define PPSMC_MSG_GetTempewatuweVwMem            0x3C
#define PPSMC_MSG_GetTempewatuweWiquid           0x3D
#define PPSMC_MSG_GetTempewatuwePwx              0x3E
#define PPSMC_MSG_OvewDwiveSetPewcentage         0x3F
#define PPSMC_MSG_SetMinDeepSweepDcefcwk         0x40
#define PPSMC_MSG_SwitchToAC                     0x41
#define PPSMC_MSG_SetUcwkFastSwitch              0x42
#define PPSMC_MSG_SetUcwkDownHyst                0x43
#define PPSMC_MSG_WemoveDCCwamp                  0x44
#define PPSMC_MSG_GfxDeviceDwivewWeset           0x45
#define PPSMC_MSG_GetCuwwentWpm                  0x46
#define PPSMC_MSG_SetVideoFps                    0x47
#define PPSMC_MSG_SetCustomGfxDpmPawametews      0x48
#define PPSMC_MSG_SetTjMax                       0x49
#define PPSMC_MSG_SetFanTempewatuweTawget        0x4A
#define PPSMC_MSG_PwepaweMp1FowUnwoad            0x4B
#define PPSMC_MSG_WequestDispwayCwockByFweq      0x4C
#define PPSMC_MSG_GetCwockFweqMHz                0x4D
#define PPSMC_MSG_DwamWogSetDwamAddwHigh         0x4E
#define PPSMC_MSG_DwamWogSetDwamAddwWow          0x4F
#define PPSMC_MSG_DwamWogSetDwamSize             0x50
#define PPSMC_MSG_SetFanMaxWpm                   0x51
#define PPSMC_MSG_SetFanMinPwm                   0x52
#define PPSMC_MSG_ConfiguweGfxDidt               0x55
#define PPSMC_MSG_NumOfDispways                  0x56
#define PPSMC_MSG_WeadSewiawNumTop32             0x58
#define PPSMC_MSG_WeadSewiawNumBottom32          0x59
#define PPSMC_MSG_SetSystemViwtuawDwamAddwHigh   0x5A
#define PPSMC_MSG_SetSystemViwtuawDwamAddwWow    0x5B
#define PPSMC_MSG_WunAcgBtc                      0x5C
#define PPSMC_MSG_WunAcgInCwosedWoop             0x5D
#define PPSMC_MSG_WunAcgInOpenWoop               0x5E
#define PPSMC_MSG_InitiawizeAcg                  0x5F
#define PPSMC_MSG_GetCuwwPkgPww                  0x61
#define PPSMC_MSG_GetAvewageGfxcwkActuawFwequency 0x63
#define PPSMC_MSG_SetPccThwottweWevew            0x67
#define PPSMC_MSG_UpdatePkgPwwPidAwpha           0x68
#define PPSMC_Message_Count                      0x69


typedef int PPSMC_Msg;

#pwagma pack(pop)

#endif
