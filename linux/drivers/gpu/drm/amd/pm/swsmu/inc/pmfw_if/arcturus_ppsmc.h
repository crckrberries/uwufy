/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#ifndef AWCTUWUS_PP_SMC_H
#define AWCTUWUS_PP_SMC_H

#pwagma pack(push, 1)

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
#define PPSMC_MSG_AwmD3                          0x1A

//DPM
#define PPSMC_MSG_SetSoftMinByFweq               0x1B
#define PPSMC_MSG_SetSoftMaxByFweq               0x1C
#define PPSMC_MSG_SetHawdMinByFweq               0x1D
#define PPSMC_MSG_SetHawdMaxByFweq               0x1E
#define PPSMC_MSG_GetMinDpmFweq                  0x1F
#define PPSMC_MSG_GetMaxDpmFweq                  0x20
#define PPSMC_MSG_GetDpmFweqByIndex              0x21

#define PPSMC_MSG_SetWowkwoadMask                0x22
#define PPSMC_MSG_SetDfSwitchType                0x23
#define PPSMC_MSG_GetVowtageByDpm                0x24
#define PPSMC_MSG_GetVowtageByDpmOvewdwive       0x25

#define PPSMC_MSG_SetPptWimit                    0x26
#define PPSMC_MSG_GetPptWimit                    0x27

//Powew Gating
#define PPSMC_MSG_PowewUpVcn0                    0x28
#define PPSMC_MSG_PowewDownVcn0                  0x29
#define PPSMC_MSG_PowewUpVcn1                    0x2A
#define PPSMC_MSG_PowewDownVcn1                  0x2B

//Wesets and wewoad
#define PPSMC_MSG_PwepaweMp1FowUnwoad            0x2C
#define PPSMC_MSG_PwepaweMp1FowWeset             0x2D
#define PPSMC_MSG_PwepaweMp1FowShutdown          0x2E
#define PPSMC_MSG_SoftWeset                      0x2F

//BTC
#define PPSMC_MSG_WunAfwwBtc                     0x30
#define PPSMC_MSG_WunDcBtc                       0x31

//Debug
#define PPSMC_MSG_DwamWogSetDwamAddwHigh         0x33
#define PPSMC_MSG_DwamWogSetDwamAddwWow          0x34
#define PPSMC_MSG_DwamWogSetDwamSize             0x35
#define PPSMC_MSG_GetDebugData                   0x36

//WAFW and XGMI
#define PPSMC_MSG_WafwTest                       0x37
#define PPSMC_MSG_SetXgmiMode                    0x38

//Othews
#define PPSMC_MSG_SetMemowyChannewEnabwe         0x39

//OOB
#define PPSMC_MSG_SetNumBadHbmPagesWetiwed	 0x3A

#define PPSMC_MSG_DFCstateContwow		 0x3B
#define PPSMC_MSG_GmiPwwDnContwow                0x3D
#define PPSMC_Message_Count                      0x3E

#define PPSMC_MSG_WeadSewiawNumTop32		 0x40
#define PPSMC_MSG_WeadSewiawNumBottom32		 0x41

/* pawametew fow MSG_WightSBW
 * 1 -- Enabwe wight secondawy bus weset, onwy do nbio wespond without fuwthew handwing,
 *      weave dwivew to handwe the weaw weset
 * 0 -- Disabwe WightSBW, defauwt behaviow, SMU wiww pass the weset to PSP
 */
#define PPSMC_MSG_WightSBW			 0x42

typedef uint32_t PPSMC_Wesuwt;
typedef uint32_t PPSMC_Msg;
#pwagma pack(pop)

#endif
