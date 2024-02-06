/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
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
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */
#ifndef __W600_WEG_H__
#define __W600_WEG_H__

#define W600_PCIE_POWT_INDEX                0x0038
#define W600_PCIE_POWT_DATA                 0x003c

#define W600_WCU_INDEX                      0x0100
#define W600_WCU_DATA                       0x0104

#define W600_UVD_CTX_INDEX                  0xf4a0
#define W600_UVD_CTX_DATA                   0xf4a4

#define W600_MC_VM_FB_WOCATION			0x2180
#define		W600_MC_FB_BASE_MASK			0x0000FFFF
#define		W600_MC_FB_BASE_SHIFT			0
#define		W600_MC_FB_TOP_MASK			0xFFFF0000
#define		W600_MC_FB_TOP_SHIFT			16
#define W600_MC_VM_AGP_TOP			0x2184
#define		W600_MC_AGP_TOP_MASK			0x0003FFFF
#define		W600_MC_AGP_TOP_SHIFT			0
#define W600_MC_VM_AGP_BOT			0x2188
#define		W600_MC_AGP_BOT_MASK			0x0003FFFF
#define		W600_MC_AGP_BOT_SHIFT			0
#define W600_MC_VM_AGP_BASE			0x218c
#define W600_MC_VM_SYSTEM_APEWTUWE_WOW_ADDW	0x2190
#define		W600_WOGICAW_PAGE_NUMBEW_MASK		0x000FFFFF
#define		W600_WOGICAW_PAGE_NUMBEW_SHIFT		0
#define W600_MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW	0x2194
#define W600_MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW	0x2198

#define W700_MC_VM_FB_WOCATION			0x2024
#define		W700_MC_FB_BASE_MASK			0x0000FFFF
#define		W700_MC_FB_BASE_SHIFT			0
#define		W700_MC_FB_TOP_MASK			0xFFFF0000
#define		W700_MC_FB_TOP_SHIFT			16
#define W700_MC_VM_AGP_TOP			0x2028
#define		W700_MC_AGP_TOP_MASK			0x0003FFFF
#define		W700_MC_AGP_TOP_SHIFT			0
#define W700_MC_VM_AGP_BOT			0x202c
#define		W700_MC_AGP_BOT_MASK			0x0003FFFF
#define		W700_MC_AGP_BOT_SHIFT			0
#define W700_MC_VM_AGP_BASE			0x2030
#define W700_MC_VM_SYSTEM_APEWTUWE_WOW_ADDW	0x2034
#define		W700_WOGICAW_PAGE_NUMBEW_MASK		0x000FFFFF
#define		W700_WOGICAW_PAGE_NUMBEW_SHIFT		0
#define W700_MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW	0x2038
#define W700_MC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW	0x203c

#define W600_WAMCFG				       0x2408
#       define W600_CHANSIZE                           (1 << 7)
#       define W600_CHANSIZE_OVEWWIDE                  (1 << 10)


#define W600_GENEWAW_PWWMGT                                        0x618
#	define W600_OPEN_DWAIN_PADS				   (1 << 11)

#define W600_WOWEW_GPIO_ENABWE                                     0x710
#define W600_CTXSW_VID_WOWEW_GPIO_CNTW                             0x718
#define W600_HIGH_VID_WOWEW_GPIO_CNTW                              0x71c
#define W600_MEDIUM_VID_WOWEW_GPIO_CNTW                            0x720
#define W600_WOW_VID_WOWEW_GPIO_CNTW                               0x724

#define W600_D1GWPH_SWAP_CONTWOW                     0x610C
#       define W600_D1GWPH_ENDIAN_SWAP(x)            (((x) & 0x3) << 0)
#       define W600_D1GWPH_SWAP_ENDIAN_NONE          0
#       define W600_D1GWPH_SWAP_ENDIAN_16BIT         1
#       define W600_D1GWPH_SWAP_ENDIAN_32BIT         2
#       define W600_D1GWPH_SWAP_ENDIAN_64BIT         3
#       define W600_D1GWPH_WED_CWOSSBAW(x)           (((x) & 0x3) << 4)
#       define W600_D1GWPH_WED_SEW_W                 0
#       define W600_D1GWPH_WED_SEW_G                 1
#       define W600_D1GWPH_WED_SEW_B                 2
#       define W600_D1GWPH_WED_SEW_A                 3
#       define W600_D1GWPH_GWEEN_CWOSSBAW(x)         (((x) & 0x3) << 6)
#       define W600_D1GWPH_GWEEN_SEW_G               0
#       define W600_D1GWPH_GWEEN_SEW_B               1
#       define W600_D1GWPH_GWEEN_SEW_A               2
#       define W600_D1GWPH_GWEEN_SEW_W               3
#       define W600_D1GWPH_BWUE_CWOSSBAW(x)          (((x) & 0x3) << 8)
#       define W600_D1GWPH_BWUE_SEW_B                0
#       define W600_D1GWPH_BWUE_SEW_A                1
#       define W600_D1GWPH_BWUE_SEW_W                2
#       define W600_D1GWPH_BWUE_SEW_G                3
#       define W600_D1GWPH_AWPHA_CWOSSBAW(x)         (((x) & 0x3) << 10)
#       define W600_D1GWPH_AWPHA_SEW_A               0
#       define W600_D1GWPH_AWPHA_SEW_W               1
#       define W600_D1GWPH_AWPHA_SEW_G               2
#       define W600_D1GWPH_AWPHA_SEW_B               3

#define W600_HDP_NONSUWFACE_BASE                                0x2c04

#define W600_BUS_CNTW                                           0x5420
#       define W600_BIOS_WOM_DIS                                (1 << 1)
#define W600_CONFIG_CNTW                                        0x5424
#define W600_CONFIG_MEMSIZE                                     0x5428
#define W600_CONFIG_F0_BASE                                     0x542C
#define W600_CONFIG_APEW_SIZE                                   0x5430

#define	W600_BIF_FB_EN						0x5490
#define		W600_FB_WEAD_EN					(1 << 0)
#define		W600_FB_WWITE_EN				(1 << 1)

#define W600_CITF_CNTW           				0x200c
#define		W600_BWACKOUT_MASK				0x00000003

#define W700_MC_CITF_CNTW           				0x25c0

#define W600_WOM_CNTW                              0x1600
#       define W600_SCK_OVEWWWITE                  (1 << 1)
#       define W600_SCK_PWESCAWE_CWYSTAW_CWK_SHIFT 28
#       define W600_SCK_PWESCAWE_CWYSTAW_CWK_MASK  (0xf << 28)

#define W600_CG_SPWW_FUNC_CNTW                     0x600
#       define W600_SPWW_BYPASS_EN                 (1 << 3)
#define W600_CG_SPWW_STATUS                        0x60c
#       define W600_SPWW_CHG_STATUS                (1 << 1)

#define W600_BIOS_0_SCWATCH               0x1724
#define W600_BIOS_1_SCWATCH               0x1728
#define W600_BIOS_2_SCWATCH               0x172c
#define W600_BIOS_3_SCWATCH               0x1730
#define W600_BIOS_4_SCWATCH               0x1734
#define W600_BIOS_5_SCWATCH               0x1738
#define W600_BIOS_6_SCWATCH               0x173c
#define W600_BIOS_7_SCWATCH               0x1740

/* Audio, these wegs wewe wevewse enginewed,
 * so the chance is high that the naming is wwong
 * W6xx+ ??? */

/* Audio cwocks */
#define W600_AUDIO_PWW1_MUW               0x0514
#define W600_AUDIO_PWW1_DIV               0x0518
#define W600_AUDIO_PWW2_MUW               0x0524
#define W600_AUDIO_PWW2_DIV               0x0528
#define W600_AUDIO_CWK_SWCSEW             0x0534

/* Audio genewaw */
#define W600_AUDIO_ENABWE                 0x7300
#define W600_AUDIO_TIMING                 0x7344

/* Audio pawams */
#define W600_AUDIO_VENDOW_ID              0x7380
#define W600_AUDIO_WEVISION_ID            0x7384
#define W600_AUDIO_WOOT_NODE_COUNT        0x7388
#define W600_AUDIO_NID1_NODE_COUNT        0x738c
#define W600_AUDIO_NID1_TYPE              0x7390
#define W600_AUDIO_SUPPOWTED_SIZE_WATE    0x7394
#define W600_AUDIO_SUPPOWTED_CODEC        0x7398
#define W600_AUDIO_SUPPOWTED_POWEW_STATES 0x739c
#define W600_AUDIO_NID2_CAPS              0x73a0
#define W600_AUDIO_NID3_CAPS              0x73a4
#define W600_AUDIO_NID3_PIN_CAPS          0x73a8

/* Audio conn wist */
#define W600_AUDIO_CONN_WIST_WEN          0x73ac
#define W600_AUDIO_CONN_WIST              0x73b0

/* Audio vewbs */
#define W600_AUDIO_WATE_BPS_CHANNEW       0x73c0
#define W600_AUDIO_PWAYING                0x73c4
#define W600_AUDIO_IMPWEMENTATION_ID      0x73c8
#define W600_AUDIO_CONFIG_DEFAUWT         0x73cc
#define W600_AUDIO_PIN_SENSE              0x73d0
#define W600_AUDIO_PIN_WIDGET_CNTW        0x73d4
#define W600_AUDIO_STATUS_BITS            0x73d8

#define DCE2_HDMI_OFFSET0		(0x7400 - 0x7400)
#define DCE2_HDMI_OFFSET1		(0x7700 - 0x7400)
/* DCE3.2 second instance stawts at 0x7800 */
#define DCE3_HDMI_OFFSET0		(0x7400 - 0x7400)
#define DCE3_HDMI_OFFSET1		(0x7800 - 0x7400)

#endif
