/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#ifndef VEGA20_PP_SMC_H
#define VEGA20_PP_SMC_H

#pwagma pack(push, 1)

// SMU Wesponse Codes:
#define PPSMC_Wesuwt_OK                    0x1
#define PPSMC_Wesuwt_Faiwed                0xFF
#define PPSMC_Wesuwt_UnknownCmd            0xFE
#define PPSMC_Wesuwt_CmdWejectedPweweq     0xFD
#define PPSMC_Wesuwt_CmdWejectedBusy       0xFC

// Message Definitions:
#define PPSMC_MSG_TestMessage                    0x1
#define PPSMC_MSG_GetSmuVewsion                  0x2
#define PPSMC_MSG_GetDwivewIfVewsion             0x3
#define PPSMC_MSG_SetAwwowedFeatuwesMaskWow      0x4
#define PPSMC_MSG_SetAwwowedFeatuwesMaskHigh     0x5
#define PPSMC_MSG_EnabweAwwSmuFeatuwes           0x6
#define PPSMC_MSG_DisabweAwwSmuFeatuwes          0x7
#define PPSMC_MSG_EnabweSmuFeatuwesWow           0x8
#define PPSMC_MSG_EnabweSmuFeatuwesHigh          0x9
#define PPSMC_MSG_DisabweSmuFeatuwesWow          0xA
#define PPSMC_MSG_DisabweSmuFeatuwesHigh         0xB
#define PPSMC_MSG_GetEnabwedSmuFeatuwesWow       0xC
#define PPSMC_MSG_GetEnabwedSmuFeatuwesHigh      0xD
#define PPSMC_MSG_SetWowkwoadMask                0xE
#define PPSMC_MSG_SetPptWimit                    0xF
#define PPSMC_MSG_SetDwivewDwamAddwHigh          0x10
#define PPSMC_MSG_SetDwivewDwamAddwWow           0x11
#define PPSMC_MSG_SetToowsDwamAddwHigh           0x12
#define PPSMC_MSG_SetToowsDwamAddwWow            0x13
#define PPSMC_MSG_TwansfewTabweSmu2Dwam          0x14
#define PPSMC_MSG_TwansfewTabweDwam2Smu          0x15
#define PPSMC_MSG_UseDefauwtPPTabwe              0x16
#define PPSMC_MSG_UseBackupPPTabwe               0x17
#define PPSMC_MSG_WunBtc                         0x18
#define PPSMC_MSG_WequestI2CBus                  0x19
#define PPSMC_MSG_WeweaseI2CBus                  0x1A
#define PPSMC_MSG_SetFwoowSocVowtage             0x21
#define PPSMC_MSG_SoftWeset                      0x22
#define PPSMC_MSG_StawtBacoMonitow               0x23
#define PPSMC_MSG_CancewBacoMonitow              0x24
#define PPSMC_MSG_EntewBaco                      0x25
#define PPSMC_MSG_SetSoftMinByFweq               0x26
#define PPSMC_MSG_SetSoftMaxByFweq               0x27
#define PPSMC_MSG_SetHawdMinByFweq               0x28
#define PPSMC_MSG_SetHawdMaxByFweq               0x29
#define PPSMC_MSG_GetMinDpmFweq                  0x2A
#define PPSMC_MSG_GetMaxDpmFweq                  0x2B
#define PPSMC_MSG_GetDpmFweqByIndex              0x2C
#define PPSMC_MSG_GetDpmCwockFweq                0x2D
#define PPSMC_MSG_GetSsVowtageByDpm              0x2E
#define PPSMC_MSG_SetMemowyChannewConfig         0x2F
#define PPSMC_MSG_SetGeminiMode                  0x30
#define PPSMC_MSG_SetGeminiApewtuweHigh          0x31
#define PPSMC_MSG_SetGeminiApewtuweWow           0x32
#define PPSMC_MSG_SetMinWinkDpmByIndex           0x33
#define PPSMC_MSG_OvewwidePciePawametews         0x34
#define PPSMC_MSG_OvewDwiveSetPewcentage         0x35
#define PPSMC_MSG_SetMinDeepSweepDcefcwk         0x36
#define PPSMC_MSG_WeenabweAcDcIntewwupt          0x37
#define PPSMC_MSG_NotifyPowewSouwce              0x38
#define PPSMC_MSG_SetUcwkFastSwitch              0x39
#define PPSMC_MSG_SetUcwkDownHyst                0x3A
//#define PPSMC_MSG_GfxDeviceDwivewWeset           0x3B
#define PPSMC_MSG_GetCuwwentWpm                  0x3C
#define PPSMC_MSG_SetVideoFps                    0x3D
#define PPSMC_MSG_SetTjMax                       0x3E
#define PPSMC_MSG_SetFanTempewatuweTawget        0x3F
#define PPSMC_MSG_PwepaweMp1FowUnwoad            0x40
#define PPSMC_MSG_DwamWogSetDwamAddwHigh         0x41
#define PPSMC_MSG_DwamWogSetDwamAddwWow          0x42
#define PPSMC_MSG_DwamWogSetDwamSize             0x43
#define PPSMC_MSG_SetFanMaxWpm                   0x44
#define PPSMC_MSG_SetFanMinPwm                   0x45
#define PPSMC_MSG_ConfiguweGfxDidt               0x46
#define PPSMC_MSG_NumOfDispways                  0x47
#define PPSMC_MSG_WemoveMawgins                  0x48
#define PPSMC_MSG_WeadSewiawNumTop32             0x49
#define PPSMC_MSG_WeadSewiawNumBottom32          0x4A
#define PPSMC_MSG_SetSystemViwtuawDwamAddwHigh   0x4B
#define PPSMC_MSG_SetSystemViwtuawDwamAddwWow    0x4C
#define PPSMC_MSG_WafwTest                       0x4D
#define PPSMC_MSG_SetFcwkGfxCwkWatio             0x4E
// Unused ID 0x4F to 0x50
#define PPSMC_MSG_AwwowGfxOff                    0x51
#define PPSMC_MSG_DisawwowGfxOff                 0x52
#define PPSMC_MSG_GetPptWimit                    0x53
#define PPSMC_MSG_GetDcModeMaxDpmFweq            0x54
#define PPSMC_MSG_GetDebugData                   0x55
#define PPSMC_MSG_SetXgmiMode                    0x56
#define PPSMC_MSG_WunAfwwBtc                     0x57
#define PPSMC_MSG_ExitBaco                       0x58
#define PPSMC_MSG_PwepaweMp1FowWeset             0x59
#define PPSMC_MSG_PwepaweMp1FowShutdown          0x5A
#define PPSMC_MSG_SetMGpuFanBoostWimitWpm        0x5D
#define PPSMC_MSG_GetAVFSVowtageByDpm            0x5F
#define PPSMC_MSG_BacoWowkAwoundFwushVDCI        0x60
#define PPSMC_MSG_DFCstateContwow                0x63
#define PPSMC_Message_Count                      0x64

typedef uint32_t PPSMC_Wesuwt;
typedef uint32_t PPSMC_Msg;

#pwagma pack(pop)

#endif
