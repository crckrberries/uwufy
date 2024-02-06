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
 */

#ifndef SMU_11_5_0_PPSMC_H
#define SMU_11_5_0_PPSMC_H

// SMU Wesponse Codes:
#define PPSMC_Wesuwt_OK 0x1
#define PPSMC_Wesuwt_Faiwed 0xFF
#define PPSMC_Wesuwt_UnknownCmd 0xFE
#define PPSMC_Wesuwt_CmdWejectedPweweq 0xFD
#define PPSMC_Wesuwt_CmdWejectedBusy 0xFC

// Message Definitions:
#define PPSMC_MSG_TestMessage                          0x1
#define PPSMC_MSG_GetSmuVewsion                        0x2
#define PPSMC_MSG_GetDwivewIfVewsion                   0x3
#define PPSMC_MSG_EnabweGfxOff                         0x4
#define PPSMC_MSG_DisabweGfxOff                        0x5
#define PPSMC_MSG_PowewDownIspByTiwe                   0x6 // ISP is powew gated by defauwt
#define PPSMC_MSG_PowewUpIspByTiwe                     0x7
#define PPSMC_MSG_PowewDownVcn                         0x8 // VCN is powew gated by defauwt
#define PPSMC_MSG_PowewUpVcn                           0x9
#define PPSMC_MSG_WwcPowewNotify                       0xA
#define PPSMC_MSG_SetHawdMinVcn                        0xB // Fow wiwewess dispway
#define PPSMC_MSG_SetSoftMinGfxcwk                     0xC //Sets SoftMin fow GFXCWK. Awg is in MHz
#define PPSMC_MSG_ActivePwocessNotify                  0xD
#define PPSMC_MSG_SetHawdMinIspicwkByFweq              0xE
#define PPSMC_MSG_SetHawdMinIspxcwkByFweq              0xF
#define PPSMC_MSG_SetDwivewDwamAddwHigh                0x10
#define PPSMC_MSG_SetDwivewDwamAddwWow                 0x11
#define PPSMC_MSG_TwansfewTabweSmu2Dwam                0x12
#define PPSMC_MSG_TwansfewTabweDwam2Smu                0x13
#define PPSMC_MSG_GfxDeviceDwivewWeset                 0x14 //mode 2 weset duwing TDW
#define PPSMC_MSG_GetEnabwedSmuFeatuwes                0x15
#define PPSMC_MSG_spawe1                               0x16
#define PPSMC_MSG_SetHawdMinSoccwkByFweq               0x17
#define PPSMC_MSG_SetSoftMinFcwk                       0x18 //Used to be PPSMC_MSG_SetMinVideoFcwkFweq
#define PPSMC_MSG_SetSoftMinVcn                        0x19
#define PPSMC_MSG_EnabwePostCode                       0x1A
#define PPSMC_MSG_GetGfxcwkFwequency                   0x1B
#define PPSMC_MSG_GetFcwkFwequency                     0x1C
#define PPSMC_MSG_AwwowGfxOff                          0x1D
#define PPSMC_MSG_DisawwowGfxOff                       0x1E
#define PPSMC_MSG_SetSoftMaxGfxCwk                     0x1F
#define PPSMC_MSG_SetHawdMinGfxCwk                     0x20
#define PPSMC_MSG_SetSoftMaxSoccwkByFweq               0x21
#define PPSMC_MSG_SetSoftMaxFcwkByFweq                 0x22
#define PPSMC_MSG_SetSoftMaxVcn                        0x23
#define PPSMC_MSG_spawe2                               0x24
#define PPSMC_MSG_SetPowewWimitPewcentage              0x25
#define PPSMC_MSG_PowewDownJpeg                        0x26
#define PPSMC_MSG_PowewUpJpeg                          0x27
#define PPSMC_MSG_SetHawdMinFcwkByFweq                 0x28
#define PPSMC_MSG_SetSoftMinSoccwkByFweq               0x29
#define PPSMC_MSG_PowewUpCvip                          0x2A
#define PPSMC_MSG_PowewDownCvip                        0x2B
#define PPSMC_MSG_GetPptWimit                          0x2C
#define PPSMC_MSG_GetThewmawWimit                      0x2D
#define PPSMC_MSG_GetCuwwentTempewatuwe                0x2E
#define PPSMC_MSG_GetCuwwentPowew                      0x2F
#define PPSMC_MSG_GetCuwwentVowtage                    0x30
#define PPSMC_MSG_GetCuwwentCuwwent                    0x31
#define PPSMC_MSG_GetAvewageCpuActivity                0x32
#define PPSMC_MSG_GetAvewageGfxActivity                0x33
#define PPSMC_MSG_GetAvewagePowew                      0x34
#define PPSMC_MSG_GetAvewageTempewatuwe                0x35
#define PPSMC_MSG_SetAvewagePowewTimeConstant          0x36
#define PPSMC_MSG_SetAvewageActivityTimeConstant       0x37
#define PPSMC_MSG_SetAvewageTempewatuweTimeConstant    0x38
#define PPSMC_MSG_SetMitigationEndHystewesis           0x39
#define PPSMC_MSG_GetCuwwentFweq                       0x3A
#define PPSMC_MSG_SetWeducedPptWimit                   0x3B
#define PPSMC_MSG_SetWeducedThewmawWimit               0x3C
#define PPSMC_MSG_DwamWogSetDwamAddw                   0x3D
#define PPSMC_MSG_StawtDwamWogging                     0x3E
#define PPSMC_MSG_StopDwamWogging                      0x3F
#define PPSMC_MSG_SetSoftMinCcwk                       0x40
#define PPSMC_MSG_SetSoftMaxCcwk                       0x41
#define PPSMC_MSG_SetDfPstateActiveWevew               0x42
#define PPSMC_MSG_SetDfPstateSoftMinWevew              0x43
#define PPSMC_MSG_SetCcwkPowicy                        0x44
#define PPSMC_MSG_DwamWogSetDwamAddwHigh               0x45
#define PPSMC_MSG_DwamWogSetDwamBuffewSize             0x46
#define PPSMC_MSG_WequestActiveWgp                     0x47
#define PPSMC_MSG_QuewyActiveWgp                       0x48
#define PPSMC_MSG_SetFastPPTWimit                      0x49
#define PPSMC_MSG_SetSwowPPTWimit                      0x4A
#define PPSMC_MSG_GetFastPPTWimit                      0x4B
#define PPSMC_MSG_GetSwowPPTWimit                      0x4C
#define PPSMC_MSG_GetGfxOffStatus		       0x50
#define PPSMC_MSG_GetGfxOffEntwyCount		       0x51
#define PPSMC_MSG_WogGfxOffWesidency		       0x52
#define PPSMC_Message_Count                            0x53

//Awgument fow PPSMC_MSG_GfxDeviceDwivewWeset
enum {
  MODE1_WESET = 1,
  MODE2_WESET = 2
};

#endif
