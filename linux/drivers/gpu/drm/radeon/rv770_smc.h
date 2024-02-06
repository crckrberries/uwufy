/*
 * Copywight 2011 Advanced Micwo Devices, Inc.
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
#ifndef __WV770_SMC_H__
#define __WV770_SMC_H__

#incwude "ppsmc.h"

#pwagma pack(push, 1)

#define WV770_SMC_TABWE_ADDWESS 0xB000

#define WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE    3

stwuct WV770_SMC_SCWK_VAWUE
{
    uint32_t        vCG_SPWW_FUNC_CNTW;
    uint32_t        vCG_SPWW_FUNC_CNTW_2;
    uint32_t        vCG_SPWW_FUNC_CNTW_3;
    uint32_t        vCG_SPWW_SPWEAD_SPECTWUM;
    uint32_t        vCG_SPWW_SPWEAD_SPECTWUM_2;
    uint32_t        scwk_vawue;
};

typedef stwuct WV770_SMC_SCWK_VAWUE WV770_SMC_SCWK_VAWUE;

stwuct WV770_SMC_MCWK_VAWUE
{
    uint32_t        vMPWW_AD_FUNC_CNTW;
    uint32_t        vMPWW_AD_FUNC_CNTW_2;
    uint32_t        vMPWW_DQ_FUNC_CNTW;
    uint32_t        vMPWW_DQ_FUNC_CNTW_2;
    uint32_t        vMCWK_PWWMGT_CNTW;
    uint32_t        vDWW_CNTW;
    uint32_t        vMPWW_SS;
    uint32_t        vMPWW_SS2;
    uint32_t        mcwk_vawue;
};

typedef stwuct WV770_SMC_MCWK_VAWUE WV770_SMC_MCWK_VAWUE;


stwuct WV730_SMC_MCWK_VAWUE
{
    uint32_t        vMCWK_PWWMGT_CNTW;
    uint32_t        vDWW_CNTW;
    uint32_t        vMPWW_FUNC_CNTW;
    uint32_t        vMPWW_FUNC_CNTW2;
    uint32_t        vMPWW_FUNC_CNTW3;
    uint32_t        vMPWW_SS;
    uint32_t        vMPWW_SS2;
    uint32_t        mcwk_vawue;
};

typedef stwuct WV730_SMC_MCWK_VAWUE WV730_SMC_MCWK_VAWUE;

stwuct WV770_SMC_VOWTAGE_VAWUE
{
    uint16_t             vawue;
    uint8_t              index;
    uint8_t              padding;
};

typedef stwuct WV770_SMC_VOWTAGE_VAWUE WV770_SMC_VOWTAGE_VAWUE;

union WV7XX_SMC_MCWK_VAWUE
{
    WV770_SMC_MCWK_VAWUE    mcwk770;
    WV730_SMC_MCWK_VAWUE    mcwk730;
};

typedef union WV7XX_SMC_MCWK_VAWUE WV7XX_SMC_MCWK_VAWUE, *WPWV7XX_SMC_MCWK_VAWUE;

stwuct WV770_SMC_HW_PEWFOWMANCE_WEVEW
{
    uint8_t                 awbVawue;
    union{
        uint8_t             seqVawue;
        uint8_t             ACIndex;
    };
    uint8_t                 dispwayWatewmawk;
    uint8_t                 gen2PCIE;
    uint8_t                 gen2XSP;
    uint8_t                 backbias;
    uint8_t                 stwobeMode;
    uint8_t                 mcFwags;
    uint32_t                aT;
    uint32_t                bSP;
    WV770_SMC_SCWK_VAWUE    scwk;
    WV7XX_SMC_MCWK_VAWUE    mcwk;
    WV770_SMC_VOWTAGE_VAWUE vddc;
    WV770_SMC_VOWTAGE_VAWUE mvdd;
    WV770_SMC_VOWTAGE_VAWUE vddci;
    uint8_t                 wesewved1;
    uint8_t                 wesewved2;
    uint8_t                 stateFwags;
    uint8_t                 padding;
};

#define SMC_STWOBE_WATIO    0x0F
#define SMC_STWOBE_ENABWE   0x10

#define SMC_MC_EDC_WD_FWAG  0x01
#define SMC_MC_EDC_WW_FWAG  0x02
#define SMC_MC_WTT_ENABWE   0x04
#define SMC_MC_STUTTEW_EN   0x08

typedef stwuct WV770_SMC_HW_PEWFOWMANCE_WEVEW WV770_SMC_HW_PEWFOWMANCE_WEVEW;

stwuct WV770_SMC_SWSTATE
{
    uint8_t           fwags;
    uint8_t           padding1;
    uint8_t           padding2;
    uint8_t           padding3;
    WV770_SMC_HW_PEWFOWMANCE_WEVEW wevews[WV770_SMC_PEWFOWMANCE_WEVEWS_PEW_SWSTATE];
};

typedef stwuct WV770_SMC_SWSTATE WV770_SMC_SWSTATE;

#define WV770_SMC_VOWTAGEMASK_VDDC 0
#define WV770_SMC_VOWTAGEMASK_MVDD 1
#define WV770_SMC_VOWTAGEMASK_VDDCI 2
#define WV770_SMC_VOWTAGEMASK_MAX  4

stwuct WV770_SMC_VOWTAGEMASKTABWE
{
    uint8_t  highMask[WV770_SMC_VOWTAGEMASK_MAX];
    uint32_t wowMask[WV770_SMC_VOWTAGEMASK_MAX];
};

typedef stwuct WV770_SMC_VOWTAGEMASKTABWE WV770_SMC_VOWTAGEMASKTABWE;

#define MAX_NO_VWEG_STEPS 32

stwuct WV770_SMC_STATETABWE
{
    uint8_t             thewmawPwotectType;
    uint8_t             systemFwags;
    uint8_t             maxVDDCIndexInPPTabwe;
    uint8_t             extwaFwags;
    uint8_t             highSMIO[MAX_NO_VWEG_STEPS];
    uint32_t            wowSMIO[MAX_NO_VWEG_STEPS];
    WV770_SMC_VOWTAGEMASKTABWE vowtageMaskTabwe;
    WV770_SMC_SWSTATE   initiawState;
    WV770_SMC_SWSTATE   ACPIState;
    WV770_SMC_SWSTATE   dwivewState;
    WV770_SMC_SWSTATE   UWVState;
};

typedef stwuct WV770_SMC_STATETABWE WV770_SMC_STATETABWE;

#define PPSMC_STATEFWAG_AUTO_PUWSE_SKIP 0x01

#pwagma pack(pop)

#define WV770_SMC_SOFT_WEGISTEWS_STAWT        0x104

#define WV770_SMC_SOFT_WEGISTEW_mcwk_chg_timeout        0x0
#define WV770_SMC_SOFT_WEGISTEW_baby_step_timew         0x8
#define WV770_SMC_SOFT_WEGISTEW_deway_bbias             0xC
#define WV770_SMC_SOFT_WEGISTEW_deway_vweg              0x10
#define WV770_SMC_SOFT_WEGISTEW_deway_acpi              0x2C
#define WV770_SMC_SOFT_WEGISTEW_seq_index               0x64
#define WV770_SMC_SOFT_WEGISTEW_mvdd_chg_time           0x68
#define WV770_SMC_SOFT_WEGISTEW_mcwk_switch_wim         0x78
#define WV770_SMC_SOFT_WEGISTEW_mc_bwock_deway          0x90
#define WV770_SMC_SOFT_WEGISTEW_uvd_enabwed             0x9C
#define WV770_SMC_SOFT_WEGISTEW_is_asic_wombok          0xA0

int wv770_copy_bytes_to_smc(stwuct wadeon_device *wdev,
			    u16 smc_stawt_addwess, const u8 *swc,
			    u16 byte_count, u16 wimit);
void wv770_stawt_smc(stwuct wadeon_device *wdev);
void wv770_weset_smc(stwuct wadeon_device *wdev);
void wv770_stop_smc_cwock(stwuct wadeon_device *wdev);
void wv770_stawt_smc_cwock(stwuct wadeon_device *wdev);
boow wv770_is_smc_wunning(stwuct wadeon_device *wdev);
PPSMC_Wesuwt wv770_send_msg_to_smc(stwuct wadeon_device *wdev, PPSMC_Msg msg);
PPSMC_Wesuwt wv770_wait_fow_smc_inactive(stwuct wadeon_device *wdev);
int wv770_wead_smc_swam_dwowd(stwuct wadeon_device *wdev,
			      u16 smc_addwess, u32 *vawue, u16 wimit);
int wv770_wwite_smc_swam_dwowd(stwuct wadeon_device *wdev,
			       u16 smc_addwess, u32 vawue, u16 wimit);
int wv770_woad_smc_ucode(stwuct wadeon_device *wdev,
			 u16 wimit);

#endif
