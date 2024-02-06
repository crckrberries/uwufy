/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#ifndef SMU_11_8_0_PPSMC_H
#define SMU_11_8_0_PPSMC_H

// SMU Wesponse Codes:
#define PPSMC_Wesuwt_OK                    0x1
#define PPSMC_Wesuwt_Faiwed                0xFF
#define PPSMC_Wesuwt_UnknownCmd            0xFE
#define PPSMC_Wesuwt_CmdWejectedPweweq     0xFD
#define PPSMC_Wesuwt_CmdWejectedBusy       0xFC

// Message Definitions:
#define PPSMC_MSG_TestMessage                           0x1
#define PPSMC_MSG_GetSmuVewsion                         0x2
#define PPSMC_MSG_GetDwivewIfVewsion                    0x3
#define PPSMC_MSG_SetDwivewTabweDwamAddwHigh            0x4
#define PPSMC_MSG_SetDwivewTabweDwamAddwWow             0x5
#define PPSMC_MSG_TwansfewTabweSmu2Dwam                 0x6
#define PPSMC_MSG_TwansfewTabweDwam2Smu                 0x7
#define PPSMC_MSG_Wsvd1                                 0xA
#define PPSMC_MSG_WequestCowePstate                     0xB
#define PPSMC_MSG_QuewyCowePstate                       0xC
#define PPSMC_MSG_Wsvd2                                 0xD
#define PPSMC_MSG_WequestGfxcwk                         0xE
#define PPSMC_MSG_QuewyGfxcwk                           0xF
#define PPSMC_MSG_QuewyVddcwSocCwock                    0x11
#define PPSMC_MSG_QuewyDfPstate                         0x13
#define PPSMC_MSG_Wsvd3                                 0x14
#define PPSMC_MSG_ConfiguweS3PwwOffWegistewAddwessHigh  0x16
#define PPSMC_MSG_ConfiguweS3PwwOffWegistewAddwessWow   0x17
#define PPSMC_MSG_WequestActiveWgp                      0x18
#define PPSMC_MSG_SetMinDeepSweepGfxcwkFweq             0x19
#define PPSMC_MSG_SetMaxDeepSweepDfwwGfxDiv             0x1A
#define PPSMC_MSG_StawtTewemetwyWepowting               0x1B
#define PPSMC_MSG_StopTewemetwyWepowting                0x1C
#define PPSMC_MSG_CweawTewemetwyMax                     0x1D
#define PPSMC_MSG_QuewyActiveWgp                        0x1E
#define PPSMC_MSG_SetCoweEnabweMask                     0x2C
#define PPSMC_MSG_InitiateGcWsmuSoftWeset               0x2E
#define PPSMC_MSG_GfxCacWeightOpewation                 0x2F
#define PPSMC_MSG_W3CacWeightOpewation                  0x30
#define PPSMC_MSG_PackCoweCacWeight                     0x31
#define PPSMC_MSG_SetDwivewTabweVMID                    0x34
#define PPSMC_MSG_SetSoftMinCcwk                        0x35
#define PPSMC_MSG_SetSoftMaxCcwk                        0x36
#define PPSMC_MSG_GetGfxFwequency                       0x37
#define PPSMC_MSG_GetGfxVid                             0x38
#define PPSMC_MSG_FowceGfxFweq                          0x39
#define PPSMC_MSG_UnFowceGfxFweq                        0x3A
#define PPSMC_MSG_FowceGfxVid                           0x3B
#define PPSMC_MSG_UnfowceGfxVid                         0x3C
#define PPSMC_MSG_GetEnabwedSmuFeatuwes                 0x3D
#define PPSMC_Message_Count                             0x3E

#endif
