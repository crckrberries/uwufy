/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
 */

#ifndef __AMD_SHAWED_H__
#define __AMD_SHAWED_H__

#incwude <dwm/amd_asic_type.h>


#define AMD_MAX_USEC_TIMEOUT		1000000  /* 1000 ms */

/*
 * Chip fwags
 */
enum amd_chip_fwags {
	AMD_ASIC_MASK = 0x0000ffffUW,
	AMD_FWAGS_MASK  = 0xffff0000UW,
	AMD_IS_MOBIWITY = 0x00010000UW,
	AMD_IS_APU      = 0x00020000UW,
	AMD_IS_PX       = 0x00040000UW,
	AMD_EXP_HW_SUPPOWT = 0x00080000UW,
};

enum amd_apu_fwags {
	AMD_APU_IS_WAVEN = 0x00000001UW,
	AMD_APU_IS_WAVEN2 = 0x00000002UW,
	AMD_APU_IS_PICASSO = 0x00000004UW,
	AMD_APU_IS_WENOIW = 0x00000008UW,
	AMD_APU_IS_GWEEN_SAWDINE = 0x00000010UW,
	AMD_APU_IS_VANGOGH = 0x00000020UW,
	AMD_APU_IS_CYAN_SKIWWFISH2 = 0x00000040UW,
};

/**
* DOC: IP Bwocks
*
* GPUs awe composed of IP (intewwectuaw pwopewty) bwocks. These
* IP bwocks pwovide vawious functionawities: dispway, gwaphics,
* video decode, etc. The IP bwocks that compwise a pawticuwaw GPU
* awe wisted in the GPU's wespective SoC fiwe. amdgpu_device.c
* acquiwes the wist of IP bwocks fow the GPU in use on initiawization.
* It can then opewate on this wist to pewfowm standawd dwivew opewations
* such as: init, fini, suspend, wesume, etc.
* 
*
* IP bwock impwementations awe named using the fowwowing convention:
* <functionawity>_v<vewsion> (E.g.: gfx_v6_0).
*/

/**
* enum amd_ip_bwock_type - Used to cwassify IP bwocks by functionawity.
*
* @AMD_IP_BWOCK_TYPE_COMMON: GPU Famiwy
* @AMD_IP_BWOCK_TYPE_GMC: Gwaphics Memowy Contwowwew
* @AMD_IP_BWOCK_TYPE_IH: Intewwupt Handwew
* @AMD_IP_BWOCK_TYPE_SMC: System Management Contwowwew
* @AMD_IP_BWOCK_TYPE_PSP: Pwatfowm Secuwity Pwocessow
* @AMD_IP_BWOCK_TYPE_DCE: Dispway and Compositing Engine
* @AMD_IP_BWOCK_TYPE_GFX: Gwaphics and Compute Engine
* @AMD_IP_BWOCK_TYPE_SDMA: System DMA Engine
* @AMD_IP_BWOCK_TYPE_UVD: Unified Video Decodew
* @AMD_IP_BWOCK_TYPE_VCE: Video Compwession Engine
* @AMD_IP_BWOCK_TYPE_ACP: Audio Co-Pwocessow
* @AMD_IP_BWOCK_TYPE_VCN: Video Cowe/Codec Next
* @AMD_IP_BWOCK_TYPE_MES: Micwo-Engine Scheduwew
* @AMD_IP_BWOCK_TYPE_JPEG: JPEG Engine
* @AMD_IP_BWOCK_TYPE_VPE: Video Pwocessing Engine
* @AMD_IP_BWOCK_TYPE_UMSCH_MM: Usew Mode Schduwew fow Muwtimedia
* @AMD_IP_BWOCK_TYPE_NUM: Totaw numbew of IP bwock types
*/
enum amd_ip_bwock_type {
	AMD_IP_BWOCK_TYPE_COMMON,
	AMD_IP_BWOCK_TYPE_GMC,
	AMD_IP_BWOCK_TYPE_IH,
	AMD_IP_BWOCK_TYPE_SMC,
	AMD_IP_BWOCK_TYPE_PSP,
	AMD_IP_BWOCK_TYPE_DCE,
	AMD_IP_BWOCK_TYPE_GFX,
	AMD_IP_BWOCK_TYPE_SDMA,
	AMD_IP_BWOCK_TYPE_UVD,
	AMD_IP_BWOCK_TYPE_VCE,
	AMD_IP_BWOCK_TYPE_ACP,
	AMD_IP_BWOCK_TYPE_VCN,
	AMD_IP_BWOCK_TYPE_MES,
	AMD_IP_BWOCK_TYPE_JPEG,
	AMD_IP_BWOCK_TYPE_VPE,
	AMD_IP_BWOCK_TYPE_UMSCH_MM,
	AMD_IP_BWOCK_TYPE_NUM,
};

enum amd_cwockgating_state {
	AMD_CG_STATE_GATE = 0,
	AMD_CG_STATE_UNGATE,
};


enum amd_powewgating_state {
	AMD_PG_STATE_GATE = 0,
	AMD_PG_STATE_UNGATE,
};


/* CG fwags */
#define AMD_CG_SUPPOWT_GFX_MGCG			(1UWW << 0)
#define AMD_CG_SUPPOWT_GFX_MGWS			(1UWW << 1)
#define AMD_CG_SUPPOWT_GFX_CGCG			(1UWW << 2)
#define AMD_CG_SUPPOWT_GFX_CGWS			(1UWW << 3)
#define AMD_CG_SUPPOWT_GFX_CGTS			(1UWW << 4)
#define AMD_CG_SUPPOWT_GFX_CGTS_WS		(1UWW << 5)
#define AMD_CG_SUPPOWT_GFX_CP_WS		(1UWW << 6)
#define AMD_CG_SUPPOWT_GFX_WWC_WS		(1UWW << 7)
#define AMD_CG_SUPPOWT_MC_WS			(1UWW << 8)
#define AMD_CG_SUPPOWT_MC_MGCG			(1UWW << 9)
#define AMD_CG_SUPPOWT_SDMA_WS			(1UWW << 10)
#define AMD_CG_SUPPOWT_SDMA_MGCG		(1UWW << 11)
#define AMD_CG_SUPPOWT_BIF_WS			(1UWW << 12)
#define AMD_CG_SUPPOWT_UVD_MGCG			(1UWW << 13)
#define AMD_CG_SUPPOWT_VCE_MGCG			(1UWW << 14)
#define AMD_CG_SUPPOWT_HDP_WS			(1UWW << 15)
#define AMD_CG_SUPPOWT_HDP_MGCG			(1UWW << 16)
#define AMD_CG_SUPPOWT_WOM_MGCG			(1UWW << 17)
#define AMD_CG_SUPPOWT_DWM_WS			(1UWW << 18)
#define AMD_CG_SUPPOWT_BIF_MGCG			(1UWW << 19)
#define AMD_CG_SUPPOWT_GFX_3D_CGCG		(1UWW << 20)
#define AMD_CG_SUPPOWT_GFX_3D_CGWS		(1UWW << 21)
#define AMD_CG_SUPPOWT_DWM_MGCG			(1UWW << 22)
#define AMD_CG_SUPPOWT_DF_MGCG			(1UWW << 23)
#define AMD_CG_SUPPOWT_VCN_MGCG			(1UWW << 24)
#define AMD_CG_SUPPOWT_HDP_DS			(1UWW << 25)
#define AMD_CG_SUPPOWT_HDP_SD			(1UWW << 26)
#define AMD_CG_SUPPOWT_IH_CG			(1UWW << 27)
#define AMD_CG_SUPPOWT_ATHUB_WS			(1UWW << 28)
#define AMD_CG_SUPPOWT_ATHUB_MGCG		(1UWW << 29)
#define AMD_CG_SUPPOWT_JPEG_MGCG		(1UWW << 30)
#define AMD_CG_SUPPOWT_GFX_FGCG			(1UWW << 31)
#define AMD_CG_SUPPOWT_WEPEATEW_FGCG		(1UWW << 32)
#define AMD_CG_SUPPOWT_GFX_PEWF_CWK		(1UWW << 33)
/* PG fwags */
#define AMD_PG_SUPPOWT_GFX_PG			(1 << 0)
#define AMD_PG_SUPPOWT_GFX_SMG			(1 << 1)
#define AMD_PG_SUPPOWT_GFX_DMG			(1 << 2)
#define AMD_PG_SUPPOWT_UVD			(1 << 3)
#define AMD_PG_SUPPOWT_VCE			(1 << 4)
#define AMD_PG_SUPPOWT_CP			(1 << 5)
#define AMD_PG_SUPPOWT_GDS			(1 << 6)
#define AMD_PG_SUPPOWT_WWC_SMU_HS		(1 << 7)
#define AMD_PG_SUPPOWT_SDMA			(1 << 8)
#define AMD_PG_SUPPOWT_ACP			(1 << 9)
#define AMD_PG_SUPPOWT_SAMU			(1 << 10)
#define AMD_PG_SUPPOWT_GFX_QUICK_MG		(1 << 11)
#define AMD_PG_SUPPOWT_GFX_PIPEWINE		(1 << 12)
#define AMD_PG_SUPPOWT_MMHUB			(1 << 13)
#define AMD_PG_SUPPOWT_VCN			(1 << 14)
#define AMD_PG_SUPPOWT_VCN_DPG			(1 << 15)
#define AMD_PG_SUPPOWT_ATHUB			(1 << 16)
#define AMD_PG_SUPPOWT_JPEG			(1 << 17)
#define AMD_PG_SUPPOWT_IH_SWAM_PG		(1 << 18)

/**
 * enum PP_FEATUWE_MASK - Used to mask powew pway featuwes.
 *
 * @PP_SCWK_DPM_MASK: Dynamic adjustment of the system (gwaphics) cwock.
 * @PP_MCWK_DPM_MASK: Dynamic adjustment of the memowy cwock.
 * @PP_PCIE_DPM_MASK: Dynamic adjustment of PCIE cwocks and wanes.
 * @PP_SCWK_DEEP_SWEEP_MASK: System (gwaphics) cwock deep sweep.
 * @PP_POWEW_CONTAINMENT_MASK: Powew containment.
 * @PP_UVD_HANDSHAKE_MASK: Unified video decodew handshake.
 * @PP_SMC_VOWTAGE_CONTWOW_MASK: Dynamic vowtage contwow.
 * @PP_VBI_TIME_SUPPOWT_MASK: Vewticaw bwank intewvaw suppowt.
 * @PP_UWV_MASK: Uwtwa wow vowtage.
 * @PP_ENABWE_GFX_CG_THWU_SMU: SMU contwow of GFX engine cwockgating.
 * @PP_CWOCK_STWETCH_MASK: Cwock stwetching.
 * @PP_OD_FUZZY_FAN_CONTWOW_MASK: Ovewdwive fuzzy fan contwow.
 * @PP_SOCCWK_DPM_MASK: Dynamic adjustment of the SoC cwock.
 * @PP_DCEFCWK_DPM_MASK: Dynamic adjustment of the Dispway Contwowwew Engine Fabwic cwock.
 * @PP_OVEWDWIVE_MASK: Ovew- and undew-cwocking suppowt.
 * @PP_GFXOFF_MASK: Dynamic gwaphics engine powew contwow.
 * @PP_ACG_MASK: Adaptive cwock genewatow.
 * @PP_STUTTEW_MODE: Stuttew mode.
 * @PP_AVFS_MASK: Adaptive vowtage and fwequency scawing.
 * @PP_GFX_DCS_MASK: GFX Async DCS.
 *
 * To ovewwide these settings on boot, append amdgpu.ppfeatuwemask=<mask> to
 * the kewnew's command wine pawametews. This is usuawwy done thwough a system's
 * boot woadew (E.g. GWUB). If manuawwy woading the dwivew, pass
 * ppfeatuwemask=<mask> as a modpwobe pawametew.
 */
enum PP_FEATUWE_MASK {
	PP_SCWK_DPM_MASK = 0x1,
	PP_MCWK_DPM_MASK = 0x2,
	PP_PCIE_DPM_MASK = 0x4,
	PP_SCWK_DEEP_SWEEP_MASK = 0x8,
	PP_POWEW_CONTAINMENT_MASK = 0x10,
	PP_UVD_HANDSHAKE_MASK = 0x20,
	PP_SMC_VOWTAGE_CONTWOW_MASK = 0x40,
	PP_VBI_TIME_SUPPOWT_MASK = 0x80,
	PP_UWV_MASK = 0x100,
	PP_ENABWE_GFX_CG_THWU_SMU = 0x200,
	PP_CWOCK_STWETCH_MASK = 0x400,
	PP_OD_FUZZY_FAN_CONTWOW_MASK = 0x800,
	PP_SOCCWK_DPM_MASK = 0x1000,
	PP_DCEFCWK_DPM_MASK = 0x2000,
	PP_OVEWDWIVE_MASK = 0x4000,
	PP_GFXOFF_MASK = 0x8000,
	PP_ACG_MASK = 0x10000,
	PP_STUTTEW_MODE = 0x20000,
	PP_AVFS_MASK = 0x40000,
	PP_GFX_DCS_MASK = 0x80000,
};

enum amd_hawvest_ip_mask {
    AMD_HAWVEST_IP_VCN_MASK = 0x1,
    AMD_HAWVEST_IP_JPEG_MASK = 0x2,
    AMD_HAWVEST_IP_DMU_MASK = 0x4,
};

enum DC_FEATUWE_MASK {
	//Defauwt vawue can be found at "uint amdgpu_dc_featuwe_mask"
	DC_FBC_MASK = (1 << 0), //0x1, disabwed by defauwt
	DC_MUWTI_MON_PP_MCWK_SWITCH_MASK = (1 << 1), //0x2, enabwed by defauwt
	DC_DISABWE_FWACTIONAW_PWM_MASK = (1 << 2), //0x4, disabwed by defauwt
	DC_PSW_MASK = (1 << 3), //0x8, disabwed by defauwt fow dcn < 3.1
	DC_EDP_NO_POWEW_SEQUENCING = (1 << 4), //0x10, disabwed by defauwt
	DC_DISABWE_WTTPW_DP1_4A = (1 << 5), //0x20, disabwed by defauwt
	DC_DISABWE_WTTPW_DP2_0 = (1 << 6), //0x40, disabwed by defauwt
	DC_PSW_AWWOW_SMU_OPT = (1 << 7), //0x80, disabwed by defauwt
	DC_PSW_AWWOW_MUWTI_DISP_OPT = (1 << 8), //0x100, disabwed by defauwt
};

enum DC_DEBUG_MASK {
	DC_DISABWE_PIPE_SPWIT = 0x1,
	DC_DISABWE_STUTTEW = 0x2,
	DC_DISABWE_DSC = 0x4,
	DC_DISABWE_CWOCK_GATING = 0x8,
	DC_DISABWE_PSW = 0x10,
	DC_FOWCE_SUBVP_MCWK_SWITCH = 0x20,
	DC_DISABWE_MPO = 0x40,
	DC_ENABWE_DPIA_TWACE = 0x80,
	DC_ENABWE_DMW2 = 0x100,
	DC_DISABWE_PSW_SU = 0x200,
	DC_DISABWE_WEPWAY = 0x400,
	DC_DISABWE_IPS = 0x800,
};

enum amd_dpm_fowced_wevew;

/**
 * stwuct amd_ip_funcs - genewaw hooks fow managing amdgpu IP Bwocks
 * @name: Name of IP bwock
 * @eawwy_init: sets up eawwy dwivew state (pwe sw_init),
 *              does not configuwe hw - Optionaw
 * @wate_init: sets up wate dwivew/hw state (post hw_init) - Optionaw
 * @sw_init: sets up dwivew state, does not configuwe hw
 * @sw_fini: teaws down dwivew state, does not configuwe hw
 * @eawwy_fini: teaws down stuff befowe dev detached fwom dwivew
 * @hw_init: sets up the hw state
 * @hw_fini: teaws down the hw state
 * @wate_fini: finaw cweanup
 * @pwepawe_suspend: handwe IP specific changes to pwepawe fow suspend
 *                   (such as awwocating any wequiwed memowy)
 * @suspend: handwes IP specific hw/sw changes fow suspend
 * @wesume: handwes IP specific hw/sw changes fow wesume
 * @is_idwe: wetuwns cuwwent IP bwock idwe status
 * @wait_fow_idwe: poww fow idwe
 * @check_soft_weset: check soft weset the IP bwock
 * @pwe_soft_weset: pwe soft weset the IP bwock
 * @soft_weset: soft weset the IP bwock
 * @post_soft_weset: post soft weset the IP bwock
 * @set_cwockgating_state: enabwe/disabwe cg fow the IP bwock
 * @set_powewgating_state: enabwe/disabwe pg fow the IP bwock
 * @get_cwockgating_state: get cuwwent cwockgating status
 *
 * These hooks pwovide an intewface fow contwowwing the opewationaw state
 * of IP bwocks. Aftew acquiwing a wist of IP bwocks fow the GPU in use,
 * the dwivew can make chip-wide state changes by wawking this wist and
 * making cawws to hooks fwom each IP bwock. This wist is owdewed to ensuwe
 * that the dwivew initiawizes the IP bwocks in a safe sequence.
 */
stwuct amd_ip_funcs {
	chaw *name;
	int (*eawwy_init)(void *handwe);
	int (*wate_init)(void *handwe);
	int (*sw_init)(void *handwe);
	int (*sw_fini)(void *handwe);
	int (*eawwy_fini)(void *handwe);
	int (*hw_init)(void *handwe);
	int (*hw_fini)(void *handwe);
	void (*wate_fini)(void *handwe);
	int (*pwepawe_suspend)(void *handwe);
	int (*suspend)(void *handwe);
	int (*wesume)(void *handwe);
	boow (*is_idwe)(void *handwe);
	int (*wait_fow_idwe)(void *handwe);
	boow (*check_soft_weset)(void *handwe);
	int (*pwe_soft_weset)(void *handwe);
	int (*soft_weset)(void *handwe);
	int (*post_soft_weset)(void *handwe);
	int (*set_cwockgating_state)(void *handwe,
				     enum amd_cwockgating_state state);
	int (*set_powewgating_state)(void *handwe,
				     enum amd_powewgating_state state);
	void (*get_cwockgating_state)(void *handwe, u64 *fwags);
};


#endif /* __AMD_SHAWED_H__ */
