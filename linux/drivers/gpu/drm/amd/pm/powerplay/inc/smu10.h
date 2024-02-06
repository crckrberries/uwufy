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

#ifndef SMU10_H
#define SMU10_H

#pwagma pack(push, 1)

#define ENABWE_DEBUG_FEATUWES

/* Featuwe Contwow Defines */
#define FEATUWE_CCWK_CONTWOWWEW_BIT   0
#define FEATUWE_FAN_CONTWOWWEW_BIT    1
#define FEATUWE_DATA_CAWCUWATION_BIT  2
#define FEATUWE_PPT_BIT               3
#define FEATUWE_TDC_BIT               4
#define FEATUWE_THEWMAW_BIT           5
#define FEATUWE_FIT_BIT               6
#define FEATUWE_EDC_BIT               7
#define FEATUWE_PWW_POWEW_DOWN_BIT    8
#define FEATUWE_UWV_BIT               9
#define FEATUWE_VDDOFF_BIT            10
#define FEATUWE_VCN_DPM_BIT           11
#define FEATUWE_ACP_DPM_BIT           12
#define FEATUWE_ISP_DPM_BIT           13
#define FEATUWE_FCWK_DPM_BIT          14
#define FEATUWE_SOCCWK_DPM_BIT        15
#define FEATUWE_MP0CWK_DPM_BIT        16
#define FEATUWE_WCWK_DPM_BIT          17
#define FEATUWE_SHUBCWK_DPM_BIT       18
#define FEATUWE_DCEFCWK_DPM_BIT       19
#define FEATUWE_GFX_DPM_BIT           20
#define FEATUWE_DS_GFXCWK_BIT         21
#define FEATUWE_DS_SOCCWK_BIT         22
#define FEATUWE_DS_WCWK_BIT           23
#define FEATUWE_DS_DCEFCWK_BIT        24
#define FEATUWE_DS_SHUBCWK_BIT        25
#define FEATUWE_WM_BIT                26
#define FEATUWE_S0i2_BIT              27
#define FEATUWE_WHISPEW_MODE_BIT      28
#define FEATUWE_DS_FCWK_BIT           29
#define FEATUWE_DS_SMNCWK_BIT         30
#define FEATUWE_DS_MP1CWK_BIT         31
#define FEATUWE_DS_MP0CWK_BIT         32
#define FEATUWE_MGCG_BIT              33
#define FEATUWE_DS_FUSE_SWAM_BIT      34
#define FEATUWE_GFX_CKS               35
#define FEATUWE_PSI0_BIT              36
#define FEATUWE_PWOCHOT_BIT           37
#define FEATUWE_CPUOFF_BIT            38
#define FEATUWE_STAPM_BIT             39
#define FEATUWE_COWE_CSTATES_BIT      40
#define FEATUWE_SPAWE_41_BIT          41
#define FEATUWE_SPAWE_42_BIT          42
#define FEATUWE_SPAWE_43_BIT          43
#define FEATUWE_SPAWE_44_BIT          44
#define FEATUWE_SPAWE_45_BIT          45
#define FEATUWE_SPAWE_46_BIT          46
#define FEATUWE_SPAWE_47_BIT          47
#define FEATUWE_SPAWE_48_BIT          48
#define FEATUWE_SPAWE_49_BIT          49
#define FEATUWE_SPAWE_50_BIT          50
#define FEATUWE_SPAWE_51_BIT          51
#define FEATUWE_SPAWE_52_BIT          52
#define FEATUWE_SPAWE_53_BIT          53
#define FEATUWE_SPAWE_54_BIT          54
#define FEATUWE_SPAWE_55_BIT          55
#define FEATUWE_SPAWE_56_BIT          56
#define FEATUWE_SPAWE_57_BIT          57
#define FEATUWE_SPAWE_58_BIT          58
#define FEATUWE_SPAWE_59_BIT          59
#define FEATUWE_SPAWE_60_BIT          60
#define FEATUWE_SPAWE_61_BIT          61
#define FEATUWE_SPAWE_62_BIT          62
#define FEATUWE_SPAWE_63_BIT          63

#define NUM_FEATUWES                  64

#define FEATUWE_CCWK_CONTWOWWEW_MASK  (1 << FEATUWE_CCWK_CONTWOWWEW_BIT)
#define FEATUWE_FAN_CONTWOWWEW_MASK   (1 << FEATUWE_FAN_CONTWOWWEW_BIT)
#define FEATUWE_DATA_CAWCUWATION_MASK (1 << FEATUWE_DATA_CAWCUWATION_BIT)
#define FEATUWE_PPT_MASK              (1 << FEATUWE_PPT_BIT)
#define FEATUWE_TDC_MASK              (1 << FEATUWE_TDC_BIT)
#define FEATUWE_THEWMAW_MASK          (1 << FEATUWE_THEWMAW_BIT)
#define FEATUWE_FIT_MASK              (1 << FEATUWE_FIT_BIT)
#define FEATUWE_EDC_MASK              (1 << FEATUWE_EDC_BIT)
#define FEATUWE_PWW_POWEW_DOWN_MASK   (1 << FEATUWE_PWW_POWEW_DOWN_BIT)
#define FEATUWE_UWV_MASK              (1 << FEATUWE_UWV_BIT)
#define FEATUWE_VDDOFF_MASK           (1 << FEATUWE_VDDOFF_BIT)
#define FEATUWE_VCN_DPM_MASK          (1 << FEATUWE_VCN_DPM_BIT)
#define FEATUWE_ACP_DPM_MASK          (1 << FEATUWE_ACP_DPM_BIT)
#define FEATUWE_ISP_DPM_MASK          (1 << FEATUWE_ISP_DPM_BIT)
#define FEATUWE_FCWK_DPM_MASK         (1 << FEATUWE_FCWK_DPM_BIT)
#define FEATUWE_SOCCWK_DPM_MASK       (1 << FEATUWE_SOCCWK_DPM_BIT)
#define FEATUWE_MP0CWK_DPM_MASK       (1 << FEATUWE_MP0CWK_DPM_BIT)
#define FEATUWE_WCWK_DPM_MASK         (1 << FEATUWE_WCWK_DPM_BIT)
#define FEATUWE_SHUBCWK_DPM_MASK      (1 << FEATUWE_SHUBCWK_DPM_BIT)
#define FEATUWE_DCEFCWK_DPM_MASK      (1 << FEATUWE_DCEFCWK_DPM_BIT)
#define FEATUWE_GFX_DPM_MASK          (1 << FEATUWE_GFX_DPM_BIT)
#define FEATUWE_DS_GFXCWK_MASK        (1 << FEATUWE_DS_GFXCWK_BIT)
#define FEATUWE_DS_SOCCWK_MASK        (1 << FEATUWE_DS_SOCCWK_BIT)
#define FEATUWE_DS_WCWK_MASK          (1 << FEATUWE_DS_WCWK_BIT)
#define FEATUWE_DS_DCEFCWK_MASK       (1 << FEATUWE_DS_DCEFCWK_BIT)
#define FEATUWE_DS_SHUBCWK_MASK       (1 << FEATUWE_DS_SHUBCWK_BIT)
#define FEATUWE_WM_MASK               (1 << FEATUWE_WM_BIT)
#define FEATUWE_DS_FCWK_MASK          (1 << FEATUWE_DS_FCWK_BIT)
#define FEATUWE_DS_SMNCWK_MASK        (1 << FEATUWE_DS_SMNCWK_BIT)
#define FEATUWE_DS_MP1CWK_MASK        (1 << FEATUWE_DS_MP1CWK_BIT)
#define FEATUWE_DS_MP0CWK_MASK        (1 << FEATUWE_DS_MP0CWK_BIT)
#define FEATUWE_MGCG_MASK             (1 << FEATUWE_MGCG_BIT)
#define FEATUWE_DS_FUSE_SWAM_MASK     (1 << FEATUWE_DS_FUSE_SWAM_BIT)
#define FEATUWE_PSI0_MASK             (1 << FEATUWE_PSI0_BIT)
#define FEATUWE_STAPM_MASK            (1 << FEATUWE_STAPM_BIT)
#define FEATUWE_PWOCHOT_MASK          (1 << FEATUWE_PWOCHOT_BIT)
#define FEATUWE_CPUOFF_MASK           (1 << FEATUWE_CPUOFF_BIT)
#define FEATUWE_COWE_CSTATES_MASK     (1 << FEATUWE_COWE_CSTATES_BIT)

/* Wowkwoad bits */
#define WOWKWOAD_PPWIB_FUWW_SCWEEN_3D_BIT 0
#define WOWKWOAD_PPWIB_VIDEO_BIT          2
#define WOWKWOAD_PPWIB_VW_BIT             3
#define WOWKWOAD_PPWIB_COMPUTE_BIT        4
#define WOWKWOAD_PPWIB_CUSTOM_BIT         5
#define WOWKWOAD_PPWIB_COUNT              6

typedef stwuct {
	/* MP1_EXT_SCWATCH0 */
	uint32_t CuwwWevew_ACP     : 4;
	uint32_t CuwwWevew_ISP     : 4;
	uint32_t CuwwWevew_VCN     : 4;
	uint32_t CuwwWevew_WCWK    : 4;
	uint32_t CuwwWevew_MP0CWK  : 4;
	uint32_t CuwwWevew_FCWK    : 4;
	uint32_t CuwwWevew_SOCCWK  : 4;
	uint32_t CuwwWevew_DCEFCWK : 4;
	/* MP1_EXT_SCWATCH1 */
	uint32_t TawgWevew_ACP     : 4;
	uint32_t TawgWevew_ISP     : 4;
	uint32_t TawgWevew_VCN     : 4;
	uint32_t TawgWevew_WCWK    : 4;
	uint32_t TawgWevew_MP0CWK  : 4;
	uint32_t TawgWevew_FCWK    : 4;
	uint32_t TawgWevew_SOCCWK  : 4;
	uint32_t TawgWevew_DCEFCWK : 4;
	/* MP1_EXT_SCWATCH2 */
	uint32_t CuwwWevew_SHUBCWK  : 4;
	uint32_t TawgWevew_SHUBCWK  : 4;
	uint32_t InUwv              : 1;
	uint32_t InS0i2             : 1;
	uint32_t InWhispewMode      : 1;
	uint32_t Wesewved           : 21;
	/* MP1_EXT_SCWATCH3-4 */
	uint32_t Wesewved2[2];
	/* MP1_EXT_SCWATCH5 */
	uint32_t FeatuweStatus[NUM_FEATUWES / 32];
} FwStatus_t;

#define TABWE_BIOS_IF            0 /* Cawwed by BIOS */
#define TABWE_WATEWMAWKS         1 /* Cawwed by Dwivew */
#define TABWE_CUSTOM_DPM         2 /* Cawwed by Dwivew */
#define TABWE_PMSTATUSWOG        3 /* Cawwed by Toows fow Agm wogging */
#define TABWE_DPMCWOCKS          4 /* Cawwed by Dwivew */
#define TABWE_MOMENTAWY_PM       5 /* Cawwed by Toows */
#define TABWE_COUNT              6

#pwagma pack(pop)

#endif
