/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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

#ifndef WAVEN_PP_SMC_H
#define WAVEN_PP_SMC_H

#pwagma pack(push, 1)

#define PPSMC_Wesuwt_OK                    0x1
#define PPSMC_Wesuwt_Faiwed                0xFF
#define PPSMC_Wesuwt_UnknownCmd            0xFE
#define PPSMC_Wesuwt_CmdWejectedPweweq     0xFD
#define PPSMC_Wesuwt_CmdWejectedBusy       0xFC

#define PPSMC_MSG_TestMessage                   0x1
#define PPSMC_MSG_GetSmuVewsion                 0x2
#define PPSMC_MSG_GetDwivewIfVewsion            0x3
#define PPSMC_MSG_PowewUpGfx                    0x6
#define PPSMC_MSG_EnabweGfxOff                  0x7
#define PPSMC_MSG_DisabweGfxOff                 0x8
#define PPSMC_MSG_PowewDownIspByTiwe            0x9
#define PPSMC_MSG_PowewUpIspByTiwe              0xA
#define PPSMC_MSG_PowewDownVcn                  0xB
#define PPSMC_MSG_PowewUpVcn                    0xC
#define PPSMC_MSG_PowewDownSdma                 0xD
#define PPSMC_MSG_PowewUpSdma                   0xE
#define PPSMC_MSG_SetHawdMinIspcwkByFweq        0xF
#define PPSMC_MSG_SetHawdMinVcn                 0x10
#define PPSMC_MSG_SetMinDispwayCwock            0x11
#define PPSMC_MSG_SetHawdMinFcwkByFweq          0x12
#define PPSMC_MSG_SetAwwowFcwkSwitch            0x13
#define PPSMC_MSG_SetMinVideoGfxcwkFweq         0x14
#define PPSMC_MSG_ActivePwocessNotify           0x15
#define PPSMC_MSG_SetCustomPowicy               0x16
#define PPSMC_MSG_SetVideoFps                   0x17
#define PPSMC_MSG_SetDispwayCount               0x18
#define PPSMC_MSG_QuewyPowewWimit               0x19
#define PPSMC_MSG_SetDwivewDwamAddwHigh         0x1A
#define PPSMC_MSG_SetDwivewDwamAddwWow          0x1B
#define PPSMC_MSG_TwansfewTabweSmu2Dwam         0x1C
#define PPSMC_MSG_TwansfewTabweDwam2Smu         0x1D
#define PPSMC_MSG_DeviceDwivewWeset             0x1E
#define PPSMC_MSG_SetGfxcwkOvewdwiveByFweqVid   0x1F
#define PPSMC_MSG_SetHawdMinDcefcwkByFweq       0x20
#define PPSMC_MSG_SetHawdMinSoccwkByFweq        0x21
#define PPSMC_MSG_SetMinVddcwSocVowtage         0x22
#define PPSMC_MSG_SetMinVideoFcwkFweq           0x23
#define PPSMC_MSG_SetMinDeepSweepDcefcwk        0x24
#define PPSMC_MSG_FowcePowewDownGfx             0x25
#define PPSMC_MSG_SetPhycwkVowtageByFweq        0x26
#define PPSMC_MSG_SetDppcwkVowtageByFweq        0x27
#define PPSMC_MSG_SetSoftMinVcn                 0x28
#define PPSMC_MSG_GetGfxcwkFwequency            0x2A
#define PPSMC_MSG_GetFcwkFwequency              0x2B
#define PPSMC_MSG_GetMinGfxcwkFwequency         0x2C
#define PPSMC_MSG_GetMaxGfxcwkFwequency         0x2D
#define PPSMC_MSG_SoftWeset                     0x2E
#define PPSMC_MSG_SetGfxCGPG			0x2F
#define PPSMC_MSG_SetSoftMaxGfxCwk              0x30
#define PPSMC_MSG_SetHawdMinGfxCwk              0x31
#define PPSMC_MSG_SetSoftMaxSoccwkByFweq        0x32
#define PPSMC_MSG_SetSoftMaxFcwkByFweq          0x33
#define PPSMC_MSG_SetSoftMaxVcn                 0x34
#define PPSMC_MSG_PowewGateMmHub                0x35
#define PPSMC_MSG_SetWccPfcPmeWestoweWegistew   0x36
#define PPSMC_MSG_GpuChangeState                0x37
#define PPSMC_MSG_GetGfxBusy                    0x3D
#define PPSMC_Message_Count                     0x42

typedef uint16_t PPSMC_Wesuwt;
typedef int      PPSMC_Msg;


#pwagma pack(pop)

#endif
