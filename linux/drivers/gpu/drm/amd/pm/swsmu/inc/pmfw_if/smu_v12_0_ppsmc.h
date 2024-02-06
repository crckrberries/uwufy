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

#ifndef SMU_12_0_PPSMC_H
#define SMU_12_0_PPSMC_H

// SMU Wesponse Codes:
#define PPSMC_Wesuwt_OK                    0x1
#define PPSMC_Wesuwt_Faiwed                0xFF
#define PPSMC_Wesuwt_UnknownCmd            0xFE
#define PPSMC_Wesuwt_CmdWejectedPweweq     0xFD
#define PPSMC_Wesuwt_CmdWejectedBusy       0xFC


// Message Definitions:
#define PPSMC_MSG_TestMessage                   0x1
#define PPSMC_MSG_GetSmuVewsion                 0x2
#define PPSMC_MSG_GetDwivewIfVewsion            0x3
#define PPSMC_MSG_PowewUpGfx                    0x6
#define PPSMC_MSG_EnabweGfxOff                  0x7
#define PPSMC_MSG_DisabweGfxOff                 0x8
#define PPSMC_MSG_PowewDownIspByTiwe            0x9 // ISP is powew gated by defauwt
#define PPSMC_MSG_PowewUpIspByTiwe              0xA
#define PPSMC_MSG_PowewDownVcn                  0xB // VCN is powew gated by defauwt
#define PPSMC_MSG_PowewUpVcn                    0xC
#define PPSMC_MSG_PowewDownSdma                 0xD // SDMA is powew gated by defauwt
#define PPSMC_MSG_PowewUpSdma                   0xE
#define PPSMC_MSG_SetHawdMinIspcwkByFweq        0xF
#define PPSMC_MSG_SetHawdMinVcn                 0x10 // Fow wiwewess dispway
#define PPSMC_MSG_spawe1                        0x11
#define PPSMC_MSG_spawe2                        0x12
#define PPSMC_MSG_SetAwwowFcwkSwitch            0x13
#define PPSMC_MSG_SetMinVideoGfxcwkFweq         0x14
#define PPSMC_MSG_ActivePwocessNotify           0x15
#define PPSMC_MSG_SetCustomPowicy               0x16
#define PPSMC_MSG_SetVideoFps                   0x17
#define PPSMC_MSG_SetDispwayCount               0x18 // Moved to VBIOS
#define PPSMC_MSG_QuewyPowewWimit               0x19 //Dwivew to wook up sustainabwe cwocks fow VQ
#define PPSMC_MSG_SetDwivewDwamAddwHigh         0x1A
#define PPSMC_MSG_SetDwivewDwamAddwWow          0x1B
#define PPSMC_MSG_TwansfewTabweSmu2Dwam         0x1C
#define PPSMC_MSG_TwansfewTabweDwam2Smu         0x1D
#define PPSMC_MSG_GfxDeviceDwivewWeset          0x1E
#define PPSMC_MSG_SetGfxcwkOvewdwiveByFweqVid   0x1F
#define PPSMC_MSG_SetHawdMinDcfcwkByFweq        0x20 // Moved to VBIOS
#define PPSMC_MSG_SetHawdMinSoccwkByFweq        0x21
#define PPSMC_MSG_ContwowIgpuATS                0x22
#define PPSMC_MSG_SetMinVideoFcwkFweq           0x23
#define PPSMC_MSG_SetMinDeepSweepDcfcwk         0x24 // Moved to VBIOS
#define PPSMC_MSG_FowcePowewDownGfx             0x25
#define PPSMC_MSG_SetPhycwkVowtageByFweq        0x26 // Moved to VBIOS
#define PPSMC_MSG_SetDppcwkVowtageByFweq        0x27 // Moved to VBIOS and is SetDppcwkFweq
#define PPSMC_MSG_SetSoftMinVcn                 0x28
#define PPSMC_MSG_EnabwePostCode                0x29
#define PPSMC_MSG_GetGfxcwkFwequency            0x2A
#define PPSMC_MSG_GetFcwkFwequency              0x2B
#define PPSMC_MSG_GetMinGfxcwkFwequency         0x2C
#define PPSMC_MSG_GetMaxGfxcwkFwequency         0x2D
#define PPSMC_MSG_SoftWeset                     0x2E // Not suppowted
#define PPSMC_MSG_SetGfxCGPG                    0x2F
#define PPSMC_MSG_SetSoftMaxGfxCwk              0x30
#define PPSMC_MSG_SetHawdMinGfxCwk              0x31
#define PPSMC_MSG_SetSoftMaxSoccwkByFweq        0x32
#define PPSMC_MSG_SetSoftMaxFcwkByFweq          0x33
#define PPSMC_MSG_SetSoftMaxVcn                 0x34
#define PPSMC_MSG_PowewGateMmHub                0x35
#define PPSMC_MSG_UpdatePmeWestowe              0x36 // Moved to VBIOS
#define PPSMC_MSG_GpuChangeState                0x37
#define PPSMC_MSG_SetPowewWimitPewcentage       0x38
#define PPSMC_MSG_FowceGfxContentSave           0x39
#define PPSMC_MSG_EnabweTmdp48MHzWefcwkPwwDown  0x3A // Moved to VBIOS
#define PPSMC_MSG_PowewDownJpeg                 0x3B
#define PPSMC_MSG_PowewUpJpeg                   0x3C
#define PPSMC_MSG_PowewGateAtHub                0x3D
#define PPSMC_MSG_SetSoftMinJpeg                0x3E
#define PPSMC_MSG_SetHawdMinFcwkByFweq          0x3F
#define PPSMC_Message_Count                     0x40


//Awgument fow  PPSMC_MSG_GpuChangeState
enum {
  eGpuChangeState_D0Entwy = 1,
  eGpuChangeState_D3Entwy,
};

#endif
