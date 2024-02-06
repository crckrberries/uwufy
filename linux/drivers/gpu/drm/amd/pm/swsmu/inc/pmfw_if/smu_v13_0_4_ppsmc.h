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

#ifndef __SMU_V13_0_4_PPSMC_H__
#define __SMU_V13_0_4_PPSMC_H__

/*! @mainpage PMFW-PPS (PPWib) Message Intewface
  This documentation contains the subsections:\n\n
  @wef WesponseCodes\n
  @wef definitions\n
  @wef enums\n
*/

/** @def PPS_PMFW_IF_VEW
* PPS (PPWib) to PMFW IF vewsion 1.0
*/
#define PPS_PMFW_IF_VEW "1.0" ///< Majow.Minow

/** @defgwoup WesponseCodes PMFW Wesponse Codes
*  @{
*/
// SMU Wesponse Codes:
#define PPSMC_Wesuwt_OK                    0x1  ///< Message Wesponse OK
#define PPSMC_Wesuwt_Faiwed                0xFF ///< Message Wesponse Faiwed
#define PPSMC_Wesuwt_UnknownCmd            0xFE ///< Message Wesponse Unknown Command
#define PPSMC_Wesuwt_CmdWejectedPweweq     0xFD ///< Message Wesponse Command Faiwed Pwewequisite
#define PPSMC_Wesuwt_CmdWejectedBusy       0xFC ///< Message Wesponse Command Wejected due to PMFW is busy. Sendew shouwd wetwy sending this message
/** @}*/

/** @defgwoup definitions Message definitions
*  @{
*/
// Message Definitions:
#define PPSMC_MSG_TestMessage                   0x01 ///< To check if PMFW is awive and wesponding. Wequiwement specified by PMFW team
#define PPSMC_MSG_GetPmfwVewsion                0x02 ///< Get PMFW vewsion
#define PPSMC_MSG_GetDwivewIfVewsion            0x03 ///< Get PMFW_DWIVEW_IF vewsion
#define PPSMC_MSG_SPAWE0                        0x04 ///< SPAWE
#define PPSMC_MSG_SPAWE1                        0x05 ///< SPAWE
#define PPSMC_MSG_PowewDownVcn                  0x06 ///< Powew down VCN
#define PPSMC_MSG_PowewUpVcn                    0x07 ///< Powew up VCN; VCN is powew gated by defauwt
#define PPSMC_MSG_SetHawdMinVcn                 0x08 ///< Fow wiwewess dispway
#define PPSMC_MSG_SetSoftMinGfxcwk              0x09 ///< Set SoftMin fow GFXCWK, awgument is fwequency in MHz
#define PPSMC_MSG_SPAWE2                        0x0A ///< SPAWE
#define PPSMC_MSG_SPAWE3                        0x0B ///< SPAWE
#define PPSMC_MSG_PwepaweMp1FowUnwoad           0x0C ///< Pwepawe PMFW fow GFX dwivew unwoad
#define PPSMC_MSG_SetDwivewDwamAddwHigh         0x0D ///< Set high 32 bits of DWAM addwess fow Dwivew tabwe twansfew
#define PPSMC_MSG_SetDwivewDwamAddwWow          0x0E ///< Set wow 32 bits of DWAM addwess fow Dwivew tabwe twansfew
#define PPSMC_MSG_TwansfewTabweSmu2Dwam         0x0F ///< Twansfew dwivew intewface tabwe fwom PMFW SWAM to DWAM
#define PPSMC_MSG_TwansfewTabweDwam2Smu         0x10 ///< Twansfew dwivew intewface tabwe fwom DWAM to PMFW SWAM
#define PPSMC_MSG_GfxDeviceDwivewWeset          0x11 ///< Wequest GFX mode 2 weset
#define PPSMC_MSG_GetEnabwedSmuFeatuwes         0x12 ///< Get enabwed featuwes in PMFW
#define PPSMC_MSG_SetHawdMinSoccwkByFweq        0x13 ///< Set hawd min fow SOC CWK
#define PPSMC_MSG_SetSoftMinFcwk                0x14 ///< Set hawd min fow FCWK
#define PPSMC_MSG_SetSoftMinVcn                 0x15 ///< Set soft min fow VCN cwocks (VCWK and DCWK)

#define PPSMC_MSG_EnabweGfxImu                  0x16 ///< Enabwe GFX IMU

#define PPSMC_MSG_GetGfxcwkFwequency            0x17 ///< Get GFX cwock fwequency
#define PPSMC_MSG_GetFcwkFwequency              0x18 ///< Get FCWK fwequency
#define PPSMC_MSG_AwwowGfxOff                   0x19 ///< Infowm PMFW of awwowing GFXOFF entwy
#define PPSMC_MSG_DisawwowGfxOff                0x1A ///< Infowm PMFW of disawwowing GFXOFF entwy
#define PPSMC_MSG_SetSoftMaxGfxCwk              0x1B ///< Set soft max fow GFX CWK
#define PPSMC_MSG_SetHawdMinGfxCwk              0x1C ///< Set hawd min fow GFX CWK

#define PPSMC_MSG_SetSoftMaxSoccwkByFweq        0x1D ///< Set soft max fow SOC CWK
#define PPSMC_MSG_SetSoftMaxFcwkByFweq          0x1E ///< Set soft max fow FCWK
#define PPSMC_MSG_SetSoftMaxVcn                 0x1F ///< Set soft max fow VCN cwocks (VCWK and DCWK)
#define PPSMC_MSG_SetPowewWimitPewcentage       0x20 ///< Set powew wimit pewcentage
#define PPSMC_MSG_PowewDownJpeg                 0x21 ///< Powew down Jpeg
#define PPSMC_MSG_PowewUpJpeg                   0x22 ///< Powew up Jpeg; VCN is powew gated by defauwt

#define PPSMC_MSG_SetHawdMinFcwkByFweq          0x23 ///< Set hawd min fow FCWK
#define PPSMC_MSG_SetSoftMinSoccwkByFweq        0x24 ///< Set soft min fow SOC CWK
#define PPSMC_MSG_AwwowZstates                  0x25 ///< Infowm PMFM of awwowing Zstate entwy, i.e. no Miwacast activity
#define PPSMC_MSG_Wesewved                      0x26 ///< Not used
#define PPSMC_MSG_Wesewved1                     0x27 ///< Not used, pweviouswy PPSMC_MSG_WequestActiveWgp
#define PPSMC_MSG_Wesewved2                     0x28 ///< Not used, pweviouswy PPSMC_MSG_QuewyActiveWgp
#define PPSMC_MSG_PowewDownIspByTiwe            0x29 ///< ISP is powew gated by defauwt
#define PPSMC_MSG_PowewUpIspByTiwe              0x2A ///< This message is used to powew up ISP tiwes and enabwe the ISP DPM
#define PPSMC_MSG_SetHawdMinIspicwkByFweq       0x2B ///< Set HawdMin by fwequency fow ISPICWK
#define PPSMC_MSG_SetHawdMinIspxcwkByFweq       0x2C ///< Set HawdMin by fwequency fow ISPXCWK
#define PPSMC_MSG_PowewDownUmsch                0x2D ///< Powew down VCN.UMSCH (aka VSCH) scheduwew
#define PPSMC_MSG_PowewUpUmsch                  0x2E ///< Powew up VCN.UMSCH (aka VSCH) scheduwew
#define PPSMC_MSG_IspStuttewOn_MmhubPgDis       0x2F ///< ISP StuttewOn mmHub PgDis
#define PPSMC_MSG_IspStuttewOff_MmhubPgEn       0x30 ///< ISP StuffewOff mmHub PgEn

#define PPSMC_Message_Count                     0x31 ///< Totaw numbew of PPSMC messages
/** @}*/

/**
* @defgwoup enums Enum Definitions
*  @{
*/

/** @enum Mode_Weset_e
* Mode weset type, awgument fow PPSMC_MSG_GfxDeviceDwivewWeset
*/
//awgument fow PPSMC_MSG_GfxDeviceDwivewWeset
typedef enum {
  MODE1_WESET = 1,  ///< Mode weset type 1
  MODE2_WESET = 2   ///< Mode weset type 2
} Mode_Weset_e;

/** @}*/

/** @enum ZStates_e
* Zstate types, awgument fow PPSMC_MSG_AwwowZstates
*/
//Awgument fow PPSMC_MSG_AwwowZstates
typedef enum  {
  DISAWWOW_ZSTATES = 0, ///< Disawwow Zstates
  AWWOW_ZSTATES_Z8 = 8, ///< Awwows Z8 onwy
  AWWOW_ZSTATES_Z9 = 9, ///< Awwows Z9 and Z8
} ZStates_e;

/** @}*/
#endif
