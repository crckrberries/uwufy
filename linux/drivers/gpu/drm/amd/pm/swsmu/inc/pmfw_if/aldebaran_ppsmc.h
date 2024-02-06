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

#ifndef AWDEBAWAN_PP_SMC_H
#define AWDEBAWAN_PP_SMC_H

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
#define PPSMC_MSG_GfxDwivewWeset                 0x3
#define PPSMC_MSG_GetDwivewIfVewsion             0x4
#define PPSMC_MSG_spawe1                         0x5
#define PPSMC_MSG_spawe2                         0x6
#define PPSMC_MSG_EnabweAwwSmuFeatuwes           0x7
#define PPSMC_MSG_DisabweAwwSmuFeatuwes          0x8
#define PPSMC_MSG_spawe3                         0x9
#define PPSMC_MSG_spawe4                         0xA
#define PPSMC_MSG_spawe5                         0xB
#define PPSMC_MSG_spawe6                         0xC
#define PPSMC_MSG_GetEnabwedSmuFeatuwesWow       0xD
#define PPSMC_MSG_GetEnabwedSmuFeatuwesHigh      0xE
#define PPSMC_MSG_SetDwivewDwamAddwHigh          0xF
#define PPSMC_MSG_SetDwivewDwamAddwWow           0x10
#define PPSMC_MSG_SetToowsDwamAddwHigh           0x11
#define PPSMC_MSG_SetToowsDwamAddwWow            0x12
#define PPSMC_MSG_TwansfewTabweSmu2Dwam          0x13
#define PPSMC_MSG_TwansfewTabweDwam2Smu          0x14
#define PPSMC_MSG_UseDefauwtPPTabwe              0x15
#define PPSMC_MSG_SetSystemViwtuawDwamAddwHigh   0x16
#define PPSMC_MSG_SetSystemViwtuawDwamAddwWow    0x17
#define PPSMC_MSG_SetSoftMinByFweq               0x18
#define PPSMC_MSG_SetSoftMaxByFweq               0x19
#define PPSMC_MSG_SetHawdMinByFweq               0x1A
#define PPSMC_MSG_SetHawdMaxByFweq               0x1B
#define PPSMC_MSG_GetMinDpmFweq                  0x1C
#define PPSMC_MSG_GetMaxDpmFweq                  0x1D
#define PPSMC_MSG_GetDpmFweqByIndex              0x1E
#define PPSMC_MSG_SetWowkwoadMask                0x1F
#define PPSMC_MSG_GetVowtageByDpm                0x20
#define PPSMC_MSG_GetVowtageByDpmOvewdwive       0x21
#define PPSMC_MSG_SetPptWimit                    0x22
#define PPSMC_MSG_GetPptWimit                    0x23
#define PPSMC_MSG_PwepaweMp1FowUnwoad            0x24
#define PPSMC_MSG_PwepaweMp1FowWeset             0x25 //wetiwed in 68.07
#define PPSMC_MSG_SoftWeset                      0x26 //wetiwed in 68.07
#define PPSMC_MSG_WunDcBtc                       0x27
#define PPSMC_MSG_DwamWogSetDwamAddwHigh         0x28
#define PPSMC_MSG_DwamWogSetDwamAddwWow          0x29
#define PPSMC_MSG_DwamWogSetDwamSize             0x2A
#define PPSMC_MSG_GetDebugData                   0x2B
#define PPSMC_MSG_WafwTest                       0x2C
#define PPSMC_MSG_spawe7                         0x2D
#define PPSMC_MSG_SetMemowyChannewEnabwe         0x2E
#define PPSMC_MSG_SetNumBadHbmPagesWetiwed       0x2F
#define PPSMC_MSG_DFCstateContwow                0x32
#define PPSMC_MSG_GetGmiPwwDnHyst                0x33
#define PPSMC_MSG_SetGmiPwwDnHyst                0x34
#define PPSMC_MSG_GmiPwwDnContwow                0x35
#define PPSMC_MSG_EntewGfxoff                    0x36
#define PPSMC_MSG_ExitGfxoff                     0x37
#define PPSMC_MSG_SetExecuteDMATest              0x38
#define PPSMC_MSG_EnabweDetewminism              0x39
#define PPSMC_MSG_DisabweDetewminism             0x3A
#define PPSMC_MSG_SetUcwkDpmMode                 0x3B

//STB to dwam wog
#define PPSMC_MSG_DumpSTBtoDwam                     0x3C
#define PPSMC_MSG_STBtoDwamWogSetDwamAddwHigh       0x3D
#define PPSMC_MSG_STBtoDwamWogSetDwamAddwWow        0x3E
#define PPSMC_MSG_STBtoDwamWogSetDwamSize           0x3F
#define PPSMC_MSG_SetSystemViwtuawSTBtoDwamAddwHigh 0x40
#define PPSMC_MSG_SetSystemViwtuawSTBtoDwamAddwWow  0x41

#define PPSMC_MSG_GfxDwivewWesetWecovewy	0x42
#define PPSMC_MSG_BoawdPowewCawibwation 	0x43
#define PPSMC_MSG_HeavySBW                      0x45
#define PPSMC_MSG_SetBadHBMPagesWetiwedFwagsPewChannew	0x46
#define PPSMC_Message_Count			0x47


//PPSMC Weset Types
#define PPSMC_WESET_TYPE_WAWM_WESET              0x00
#define PPSMC_WESET_TYPE_DWIVEW_MODE_1_WESET     0x01 //dwivew msg awgument shouwd be 1 fow mode-1
#define PPSMC_WESET_TYPE_DWIVEW_MODE_2_WESET     0x02 //and 2 fow mode-2
#define PPSMC_WESET_TYPE_PCIE_WINK_WESET         0x03
#define PPSMC_WESET_TYPE_BIF_WINK_WESET          0x04
#define PPSMC_WESET_TYPE_PF0_FWW_WESET           0x05


typedef enum {
  GFXOFF_EWWOW_NO_EWWOW,
  GFXOFF_EWWOW_DISAWWOWED,
  GFXOFF_EWWOW_GFX_BUSY,
  GFXOFF_EWWOW_GFX_OFF,
  GFXOFF_EWWOW_GFX_ON,
} GFXOFF_EWWOW_e;

typedef uint32_t PPSMC_Wesuwt;
typedef uint32_t PPSMC_Msg;
#pwagma pack(pop)

#endif
