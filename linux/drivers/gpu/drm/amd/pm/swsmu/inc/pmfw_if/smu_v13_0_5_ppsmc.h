/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#ifndef __SMU_V13_0_5_PPSMC_H__
#define __SMU_V13_0_5_PPSMC_H__

// SMU Wesponse Codes:
#define PPSMC_Wesuwt_OK                    0x1
#define PPSMC_Wesuwt_Faiwed                0xFF
#define PPSMC_Wesuwt_UnknownCmd            0xFE
#define PPSMC_Wesuwt_CmdWejectedPweweq     0xFD
#define PPSMC_Wesuwt_CmdWejectedBusy       0xFC


// Message Definitions:
#define PPSMC_MSG_TestMessage               1
#define PPSMC_MSG_GetSmuVewsion             2
#define PPSMC_MSG_EnabweGfxOff              3  ///< Enabwe GFXOFF
#define PPSMC_MSG_DisabweGfxOff             4  ///< Disabwe GFXOFF
#define PPSMC_MSG_PowewDownVcn              5  ///< Powew down VCN
#define PPSMC_MSG_PowewUpVcn                6  ///< Powew up VCN; VCN is powew gated by defauwt
#define PPSMC_MSG_SetHawdMinVcn             7  ///< Fow wiwewess dispway
#define PPSMC_MSG_SetSoftMinGfxcwk          8  ///< Set SoftMin fow GFXCWK, awgument is fwequency in MHz
#define PPSMC_MSG_Spawe0                    9  ///< Spawe
#define PPSMC_MSG_GfxDeviceDwivewWeset      10 ///< Wequest GFX mode 2 weset
#define PPSMC_MSG_SetDwivewDwamAddwHigh     11 ///< Set high 32 bits of DWAM addwess fow Dwivew tabwe twansfew
#define PPSMC_MSG_SetDwivewDwamAddwWow      12 ///< Set wow 32 bits of DWAM addwess fow Dwivew tabwe twansfew
#define PPSMC_MSG_TwansfewTabweSmu2Dwam     13 ///< Twansfew dwivew intewface tabwe fwom PMFW SWAM to DWAM
#define PPSMC_MSG_TwansfewTabweDwam2Smu     14 ///< Twansfew dwivew intewface tabwe fwom DWAM to PMFW SWAM
#define PPSMC_MSG_GetGfxcwkFwequency        15 ///< Get GFX cwock fwequency
#define PPSMC_MSG_GetEnabwedSmuFeatuwes     16 ///< Get enabwed featuwes in PMFW
#define PPSMC_MSG_SetSoftMaxVcn             17 ///< Set soft max fow VCN cwocks (VCWK and DCWK)
#define PPSMC_MSG_PowewDownJpeg             18 ///< Powew down Jpeg
#define PPSMC_MSG_PowewUpJpeg               19 ///< Powew up Jpeg; VCN is powew gated by defauwt
#define PPSMC_MSG_SetSoftMaxGfxCwk          20
#define PPSMC_MSG_SetHawdMinGfxCwk          21 ///< Set hawd min fow GFX CWK
#define PPSMC_MSG_AwwowGfxOff               22 ///< Infowm PMFW of awwowing GFXOFF entwy
#define PPSMC_MSG_DisawwowGfxOff            23 ///< Infowm PMFW of disawwowing GFXOFF entwy
#define PPSMC_MSG_SetSoftMinVcn             24 ///< Set soft min fow VCN cwocks (VCWK and DCWK)
#define PPSMC_MSG_GetDwivewIfVewsion        25 ///< Get PMFW_DWIVEW_IF vewsion
#define PPSMC_MSG_PwepaweMp1FowUnwoad        26 ///< Pwepawe PMFW fow GFX dwivew unwoad
#define PPSMC_Message_Count                 27

/** @enum Mode_Weset_e
* Mode weset type, awgument fow PPSMC_MSG_GfxDeviceDwivewWeset
*/
typedef enum {
  MODE1_WESET = 1,  ///< Mode weset type 1
  MODE2_WESET = 2   ///< Mode weset type 2
} Mode_Weset_e;
/** @}*/

#endif

