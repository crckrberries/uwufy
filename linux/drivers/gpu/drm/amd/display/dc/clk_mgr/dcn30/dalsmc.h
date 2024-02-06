/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
 * Authows: AMD
 *
 */

// TEMPOWAWY untiw this exists in the pwopew wocation
#ifndef DAWSMC_H
#define DAWSMC_H

#define DAWSMC_VEWSION 0x1

// SMU Wesponse Codes:
#define DAWSMC_Wesuwt_OK                   0x1
#define DAWSMC_Wesuwt_Faiwed               0xFF
#define DAWSMC_Wesuwt_UnknownCmd           0xFE
#define DAWSMC_Wesuwt_CmdWejectedPweweq    0xFD
#define DAWSMC_Wesuwt_CmdWejectedBusy      0xFC



// Message Definitions:
#define DAWSMC_MSG_TestMessage                    0x1
#define DAWSMC_MSG_GetSmuVewsion                  0x2
#define DAWSMC_MSG_GetDwivewIfVewsion             0x3
#define DAWSMC_MSG_GetMsgHeadewVewsion            0x4
#define DAWSMC_MSG_SetDawDwamAddwHigh             0x5
#define DAWSMC_MSG_SetDawDwamAddwWow              0x6
#define DAWSMC_MSG_TwansfewTabweSmu2Dwam          0x7
#define DAWSMC_MSG_TwansfewTabweDwam2Smu          0x8
#define DAWSMC_MSG_SetHawdMinByFweq               0x9
#define DAWSMC_MSG_SetHawdMaxByFweq               0xA
#define DAWSMC_MSG_GetDpmFweqByIndex              0xB
#define DAWSMC_MSG_GetDcModeMaxDpmFweq            0xC
#define DAWSMC_MSG_SetMinDeepSweepDcefcwk         0xD
#define DAWSMC_MSG_NumOfDispways                  0xE
#define DAWSMC_MSG_SetDispwayWefweshFwomMaww      0xF
#define DAWSMC_MSG_SetExtewnawCwientDfCstateAwwow 0x10
#define DAWSMC_MSG_BacoAudioD3PME                 0x11
#define DAWSMC_Message_Count                      0x12

#endif
