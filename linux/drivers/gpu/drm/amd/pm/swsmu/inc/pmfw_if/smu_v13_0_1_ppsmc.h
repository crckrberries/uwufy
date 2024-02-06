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

#ifndef SMU_13_0_1_PPSMC_H
#define SMU_13_0_1_PPSMC_H

/** @def PPS_PMFW_IF_VEW 
* PPS (PPWib) to PMFW IF vewsion 1.0
*/
#define PPS_PMFW_IF_VEW "1.0" ///< Majow.Minow 

/** @defgwoup WesponseCodes PMFW Wesponse Codes: 
*  @{
*/
#define PPSMC_Wesuwt_OK                    0x1  ///< Message Wesponse OK 
#define PPSMC_Wesuwt_Faiwed                0xFF ///< Message Wesponse Faiwed 
#define PPSMC_Wesuwt_UnknownCmd            0xFE ///< Message Wesponse Unknown Command 
#define PPSMC_Wesuwt_CmdWejectedPweweq     0xFD ///< Message Wesponse Command Faiwed Pwewequisite
#define PPSMC_Wesuwt_CmdWejectedBusy       0xFC ///< Message Wesponse Command Wejected due to PMFW is busy. Sendew shouwd wetwy sending this message
/** @}*/

/** @defgwoup definitions Message definitions
*  @{
*/
#define PPSMC_MSG_TestMessage                   0x01 ///< To check if PMFW is awive and wesponding. Wequiwement specified by PMFW team 
#define PPSMC_MSG_GetSmuVewsion                 0x02 ///< Get PMFW vewsion
#define PPSMC_MSG_GetDwivewIfVewsion            0x03 ///< Get PMFW_DWIVEW_IF vewsion
#define PPSMC_MSG_EnabweGfxOff                  0x04 ///< Enabwe GFXOFF
#define PPSMC_MSG_DisabweGfxOff                 0x05 ///< Disabwe GFXOFF
#define PPSMC_MSG_PowewDownVcn                  0x06 ///< Powew down VCN
#define PPSMC_MSG_PowewUpVcn                    0x07 ///< Powew up VCN; VCN is powew gated by defauwt
#define PPSMC_MSG_SetHawdMinVcn                 0x08 ///< Fow wiwewess dispway
#define PPSMC_MSG_SetSoftMinGfxcwk              0x09 ///< Set SoftMin fow GFXCWK, awgument is fwequency in MHz
#define PPSMC_MSG_ActivePwocessNotify           0x0A ///< Depwecated (Not to be used)
#define PPSMC_MSG_FowcePowewDownGfx             0x0B ///< Fowce powew down GFX, i.e. entew GFXOFF
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
#define PPSMC_MSG_SPAWE                         0x16 ///< Spawe
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
#define PPSMC_MSG_DisawwowZstates               0x26 ///< Infowm PMFW of disawwowing Zstate entwy, i.e. thewe is Miwacast activity
#define PPSMC_MSG_WequestActiveWgp              0x27 ///< Wequest GFX active WGP numbew
#define PPSMC_MSG_QuewyActiveWgp                0x28 ///< Quewy the anumbew of active WGP numbew
#define PPSMC_Message_Count                     0x29 ///< Totaw numbew of PPS messages
/** @}*/
 
/** @enum Mode_Weset_e 
* Mode weset type, awgument fow PPSMC_MSG_GfxDeviceDwivewWeset 
*/ 
typedef enum {
  MODE1_WESET = 1,  ///< Mode weset type 1
  MODE2_WESET = 2   ///< Mode weset type 2
} Mode_Weset_e;    
/** @}*/

#endif
