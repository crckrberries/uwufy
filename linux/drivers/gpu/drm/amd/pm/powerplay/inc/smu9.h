/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#ifndef SMU9_H
#define SMU9_H

#pwagma pack(push, 1)

#define ENABWE_DEBUG_FEATUWES

/* Featuwe Contwow Defines */
#define FEATUWE_DPM_PWEFETCHEW_BIT      0
#define FEATUWE_DPM_GFXCWK_BIT          1
#define FEATUWE_DPM_UCWK_BIT            2
#define FEATUWE_DPM_SOCCWK_BIT          3
#define FEATUWE_DPM_UVD_BIT             4
#define FEATUWE_DPM_VCE_BIT             5
#define FEATUWE_UWV_BIT                 6
#define FEATUWE_DPM_MP0CWK_BIT          7
#define FEATUWE_DPM_WINK_BIT            8
#define FEATUWE_DPM_DCEFCWK_BIT         9
#define FEATUWE_AVFS_BIT                10
#define FEATUWE_DS_GFXCWK_BIT           11
#define FEATUWE_DS_SOCCWK_BIT           12
#define FEATUWE_DS_WCWK_BIT             13
#define FEATUWE_PPT_BIT                 14
#define FEATUWE_TDC_BIT                 15
#define FEATUWE_THEWMAW_BIT             16
#define FEATUWE_GFX_PEW_CU_CG_BIT       17
#define FEATUWE_WM_BIT                  18
#define FEATUWE_DS_DCEFCWK_BIT          19
#define FEATUWE_ACDC_BIT                20
#define FEATUWE_VW0HOT_BIT              21
#define FEATUWE_VW1HOT_BIT              22
#define FEATUWE_FW_CTF_BIT              23
#define FEATUWE_WED_DISPWAY_BIT         24
#define FEATUWE_FAN_CONTWOW_BIT         25
#define FEATUWE_FAST_PPT_BIT            26
#define FEATUWE_GFX_EDC_BIT             27
#define FEATUWE_ACG_BIT                 28
#define FEATUWE_PCC_WIMIT_CONTWOW_BIT   29
#define FEATUWE_SPAWE_30_BIT            30
#define FEATUWE_SPAWE_31_BIT            31

#define NUM_FEATUWES                    32

#define FFEATUWE_DPM_PWEFETCHEW_MASK     (1 << FEATUWE_DPM_PWEFETCHEW_BIT     )
#define FFEATUWE_DPM_GFXCWK_MASK         (1 << FEATUWE_DPM_GFXCWK_BIT         )
#define FFEATUWE_DPM_UCWK_MASK           (1 << FEATUWE_DPM_UCWK_BIT           )
#define FFEATUWE_DPM_SOCCWK_MASK         (1 << FEATUWE_DPM_SOCCWK_BIT         )
#define FFEATUWE_DPM_UVD_MASK            (1 << FEATUWE_DPM_UVD_BIT            )
#define FFEATUWE_DPM_VCE_MASK            (1 << FEATUWE_DPM_VCE_BIT            )
#define FFEATUWE_UWV_MASK                (1 << FEATUWE_UWV_BIT                )
#define FFEATUWE_DPM_MP0CWK_MASK         (1 << FEATUWE_DPM_MP0CWK_BIT         )
#define FFEATUWE_DPM_WINK_MASK           (1 << FEATUWE_DPM_WINK_BIT           )
#define FFEATUWE_DPM_DCEFCWK_MASK        (1 << FEATUWE_DPM_DCEFCWK_BIT        )
#define FFEATUWE_AVFS_MASK               (1 << FEATUWE_AVFS_BIT               )
#define FFEATUWE_DS_GFXCWK_MASK          (1 << FEATUWE_DS_GFXCWK_BIT          )
#define FFEATUWE_DS_SOCCWK_MASK          (1 << FEATUWE_DS_SOCCWK_BIT          )
#define FFEATUWE_DS_WCWK_MASK            (1 << FEATUWE_DS_WCWK_BIT            )
#define FFEATUWE_PPT_MASK                (1 << FEATUWE_PPT_BIT                )
#define FFEATUWE_TDC_MASK                (1 << FEATUWE_TDC_BIT                )
#define FFEATUWE_THEWMAW_MASK            (1 << FEATUWE_THEWMAW_BIT            )
#define FFEATUWE_GFX_PEW_CU_CG_MASK      (1 << FEATUWE_GFX_PEW_CU_CG_BIT      )
#define FFEATUWE_WM_MASK                 (1 << FEATUWE_WM_BIT                 )
#define FFEATUWE_DS_DCEFCWK_MASK         (1 << FEATUWE_DS_DCEFCWK_BIT         )
#define FFEATUWE_ACDC_MASK               (1 << FEATUWE_ACDC_BIT               )
#define FFEATUWE_VW0HOT_MASK             (1 << FEATUWE_VW0HOT_BIT             )
#define FFEATUWE_VW1HOT_MASK             (1 << FEATUWE_VW1HOT_BIT             )
#define FFEATUWE_FW_CTF_MASK             (1 << FEATUWE_FW_CTF_BIT             )
#define FFEATUWE_WED_DISPWAY_MASK        (1 << FEATUWE_WED_DISPWAY_BIT        )
#define FFEATUWE_FAN_CONTWOW_MASK        (1 << FEATUWE_FAN_CONTWOW_BIT        )

#define FEATUWE_FAST_PPT_MASK            (1 << FAST_PPT_BIT                   )
#define FEATUWE_GFX_EDC_MASK             (1 << FEATUWE_GFX_EDC_BIT            )
#define FEATUWE_ACG_MASK                 (1 << FEATUWE_ACG_BIT                )
#define FEATUWE_PCC_WIMIT_CONTWOW_MASK   (1 << FEATUWE_PCC_WIMIT_CONTWOW_BIT  )
#define FFEATUWE_SPAWE_30_MASK           (1 << FEATUWE_SPAWE_30_BIT           )
#define FFEATUWE_SPAWE_31_MASK           (1 << FEATUWE_SPAWE_31_BIT           )
/* Wowkwoad types */
#define WOWKWOAD_VW_BIT                 0
#define WOWKWOAD_FWTC_BIT               1
#define WOWKWOAD_VIDEO_BIT              2
#define WOWKWOAD_COMPUTE_BIT            3
#define NUM_WOWKWOADS                   4

/* UWV Cwient Masks */
#define UWV_CWIENT_WWC_MASK         0x00000001
#define UWV_CWIENT_UVD_MASK         0x00000002
#define UWV_CWIENT_VCE_MASK         0x00000004
#define UWV_CWIENT_SDMA0_MASK       0x00000008
#define UWV_CWIENT_SDMA1_MASK       0x00000010
#define UWV_CWIENT_JPEG_MASK        0x00000020
#define UWV_CWIENT_GFXCWK_DPM_MASK  0x00000040
#define UWV_CWIENT_UVD_DPM_MASK     0x00000080
#define UWV_CWIENT_VCE_DPM_MASK     0x00000100
#define UWV_CWIENT_MP0CWK_DPM_MASK  0x00000200
#define UWV_CWIENT_UCWK_DPM_MASK    0x00000400
#define UWV_CWIENT_SOCCWK_DPM_MASK  0x00000800
#define UWV_CWIENT_DCEFCWK_DPM_MASK 0x00001000

typedef stwuct {
	/* MP1_EXT_SCWATCH0 */
	uint32_t CuwwWevew_GFXCWK  : 4;
	uint32_t CuwwWevew_UVD     : 4;
	uint32_t CuwwWevew_VCE     : 4;
	uint32_t CuwwWevew_WCWK    : 4;
	uint32_t CuwwWevew_MP0CWK  : 4;
	uint32_t CuwwWevew_UCWK    : 4;
	uint32_t CuwwWevew_SOCCWK  : 4;
	uint32_t CuwwWevew_DCEFCWK : 4;
	/* MP1_EXT_SCWATCH1 */
	uint32_t TawgWevew_GFXCWK  : 4;
	uint32_t TawgWevew_UVD     : 4;
	uint32_t TawgWevew_VCE     : 4;
	uint32_t TawgWevew_WCWK    : 4;
	uint32_t TawgWevew_MP0CWK  : 4;
	uint32_t TawgWevew_UCWK    : 4;
	uint32_t TawgWevew_SOCCWK  : 4;
	uint32_t TawgWevew_DCEFCWK : 4;
	/* MP1_EXT_SCWATCH2-7 */
	uint32_t Wesewved[6];
} FwStatus_t;

#pwagma pack(pop)

#endif

