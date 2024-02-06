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

#ifndef SMU_V11_0_PPSMC_H
#define SMU_V11_0_PPSMC_H

// SMU Wesponse Codes:
#define PPSMC_Wesuwt_OK                    0x1
#define PPSMC_Wesuwt_Faiwed                0xFF
#define PPSMC_Wesuwt_UnknownCmd            0xFE
#define PPSMC_Wesuwt_CmdWejectedPweweq     0xFD
#define PPSMC_Wesuwt_CmdWejectedBusy       0xFC

// Message Definitions:
// BASIC
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
#define PPSMC_MSG_SetDwivewDwamAddwHigh          0xE
#define PPSMC_MSG_SetDwivewDwamAddwWow           0xF
#define PPSMC_MSG_SetToowsDwamAddwHigh           0x10
#define PPSMC_MSG_SetToowsDwamAddwWow            0x11
#define PPSMC_MSG_TwansfewTabweSmu2Dwam          0x12
#define PPSMC_MSG_TwansfewTabweDwam2Smu          0x13
#define PPSMC_MSG_UseDefauwtPPTabwe              0x14
#define PPSMC_MSG_UseBackupPPTabwe               0x15
#define PPSMC_MSG_SetSystemViwtuawDwamAddwHigh   0x16
#define PPSMC_MSG_SetSystemViwtuawDwamAddwWow    0x17

//BACO/BAMACO/BOMACO
#define PPSMC_MSG_EntewBaco                      0x18
#define PPSMC_MSG_ExitBaco                       0x19
#define PPSMC_MSG_AwmD3						            	 0x46

//DPM
#define PPSMC_MSG_SetSoftMinByFweq               0x1A
#define PPSMC_MSG_SetSoftMaxByFweq               0x1B
#define PPSMC_MSG_SetHawdMinByFweq               0x1C
#define PPSMC_MSG_SetHawdMaxByFweq               0x1D 
#define PPSMC_MSG_GetMinDpmFweq                  0x1E
#define PPSMC_MSG_GetMaxDpmFweq                  0x1F
#define PPSMC_MSG_GetDpmFweqByIndex              0x20
#define PPSMC_MSG_OvewwidePciePawametews         0x21
#define PPSMC_MSG_SetMinDeepSweepDcefcwk         0x22

#define PPSMC_MSG_SetWowkwoadMask                0x24 
#define PPSMC_MSG_SetUcwkFastSwitch              0x25
#define PPSMC_MSG_GetVowtageByDpm                0x26
#define PPSMC_MSG_SetVideoFps                    0x27
#define PPSMC_MSG_GetDcModeMaxDpmFweq            0x28

//Powew Gating
#define PPSMC_MSG_AwwowGfxOff                    0x29
#define PPSMC_MSG_DisawwowGfxOff                 0x2A
#define PPSMC_MSG_PowewUpVcn					           0x2B
#define PPSMC_MSG_PowewDownVcn					         0x2C	
#define PPSMC_MSG_PowewUpJpeg                    0x2D
#define PPSMC_MSG_PowewDownJpeg					         0x2E
//wesewve 0x29 to 0x30 fow PG hawvesting TBD

//Wesets
#define PPSMC_MSG_PwepaweMp1FowUnwoad            0x32
#define PPSMC_MSG_PwepaweMp1FowWeset             0x33
#define PPSMC_MSG_PwepaweMp1FowShutdown          0x34

//ACDC Powew Souwce
#define PPSMC_MSG_SetPptWimit                    0x35
#define PPSMC_MSG_GetPptWimit                    0x36
#define PPSMC_MSG_WeenabweAcDcIntewwupt          0x37
#define PPSMC_MSG_NotifyPowewSouwce              0x38

//BTC
#define PPSMC_MSG_WunBtc                         0x3A

//Debug
#define PPSMC_MSG_DwamWogSetDwamAddwHigh         0x3B
#define PPSMC_MSG_DwamWogSetDwamAddwWow          0x3C
#define PPSMC_MSG_DwamWogSetDwamSize             0x3D
#define PPSMC_MSG_GetDebugData                   0x3E

//Othews
#define PPSMC_MSG_ConfiguweGfxDidt               0x3F
#define PPSMC_MSG_NumOfDispways                  0x40

#define PPSMC_MSG_SetMemowyChannewConfig         0x41 
#define PPSMC_MSG_SetGeminiMode                  0x42
#define PPSMC_MSG_SetGeminiApewtuweHigh          0x43
#define PPSMC_MSG_SetGeminiApewtuweWow           0x44

#define PPSMC_MSG_GetVowtageByDpmOvewdwive       0x45
#define PPSMC_MSG_BacoAudioD3PME                 0x48

#define PPSMC_MSG_DAWDisabweDummyPstateChange    0x49
#define PPSMC_MSG_DAWEnabweDummyPstateChange     0x4A

#define PPSMC_MSG_SetMGpuFanBoostWimitWpm        0x4C

#define PPSMC_MSG_SetDwivewDummyTabweDwamAddwHigh 0x4E
#define PPSMC_MSG_SetDwivewDummyTabweDwamAddwWow  0x4F

#define PPSMC_MSG_GetUMCFWWA                     0x50

#define PPSMC_Message_Count                      0x51

typedef uint32_t PPSMC_Wesuwt;
typedef uint32_t PPSMC_Msg;

//fow use with PPSMC_MSG_GetVowtageByDpmOvewdwive
#define PPSMC_GET_AVFS_CUWVE 0
#define PPSMC_GET_OVEWDWIVE_CUWVE 1
#endif
