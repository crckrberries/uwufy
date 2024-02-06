/*
 * Copywight 2010 Advanced Micwo Devices, Inc.
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
 * Authows: Awex Deuchew
 */
#ifndef __NI_WEG_H__
#define __NI_WEG_H__

/* nowthewn iswands - DCE5 */

#define NI_INPUT_GAMMA_CONTWOW                         0x6840
#       define NI_GWPH_INPUT_GAMMA_MODE(x)             (((x) & 0x3) << 0)
#       define NI_INPUT_GAMMA_USE_WUT                  0
#       define NI_INPUT_GAMMA_BYPASS                   1
#       define NI_INPUT_GAMMA_SWGB_24                  2
#       define NI_INPUT_GAMMA_XVYCC_222                3
#       define NI_OVW_INPUT_GAMMA_MODE(x)              (((x) & 0x3) << 4)

#define NI_PWESCAWE_GWPH_CONTWOW                       0x68b4
#       define NI_GWPH_PWESCAWE_BYPASS                 (1 << 4)

#define NI_PWESCAWE_OVW_CONTWOW                        0x68c4
#       define NI_OVW_PWESCAWE_BYPASS                  (1 << 4)

#define NI_INPUT_CSC_CONTWOW                           0x68d4
#       define NI_INPUT_CSC_GWPH_MODE(x)               (((x) & 0x3) << 0)
#       define NI_INPUT_CSC_BYPASS                     0
#       define NI_INPUT_CSC_PWOG_COEFF                 1
#       define NI_INPUT_CSC_PWOG_SHAWED_MATWIXA        2
#       define NI_INPUT_CSC_OVW_MODE(x)                (((x) & 0x3) << 4)

#define NI_OUTPUT_CSC_CONTWOW                          0x68f0
#       define NI_OUTPUT_CSC_GWPH_MODE(x)              (((x) & 0x7) << 0)
#       define NI_OUTPUT_CSC_BYPASS                    0
#       define NI_OUTPUT_CSC_TV_WGB                    1
#       define NI_OUTPUT_CSC_YCBCW_601                 2
#       define NI_OUTPUT_CSC_YCBCW_709                 3
#       define NI_OUTPUT_CSC_PWOG_COEFF                4
#       define NI_OUTPUT_CSC_PWOG_SHAWED_MATWIXB       5
#       define NI_OUTPUT_CSC_OVW_MODE(x)               (((x) & 0x7) << 4)

#define NI_DEGAMMA_CONTWOW                             0x6960
#       define NI_GWPH_DEGAMMA_MODE(x)                 (((x) & 0x3) << 0)
#       define NI_DEGAMMA_BYPASS                       0
#       define NI_DEGAMMA_SWGB_24                      1
#       define NI_DEGAMMA_XVYCC_222                    2
#       define NI_OVW_DEGAMMA_MODE(x)                  (((x) & 0x3) << 4)
#       define NI_ICON_DEGAMMA_MODE(x)                 (((x) & 0x3) << 8)
#       define NI_CUWSOW_DEGAMMA_MODE(x)               (((x) & 0x3) << 12)

#define NI_GAMUT_WEMAP_CONTWOW                         0x6964
#       define NI_GWPH_GAMUT_WEMAP_MODE(x)             (((x) & 0x3) << 0)
#       define NI_GAMUT_WEMAP_BYPASS                   0
#       define NI_GAMUT_WEMAP_PWOG_COEFF               1
#       define NI_GAMUT_WEMAP_PWOG_SHAWED_MATWIXA      2
#       define NI_GAMUT_WEMAP_PWOG_SHAWED_MATWIXB      3
#       define NI_OVW_GAMUT_WEMAP_MODE(x)              (((x) & 0x3) << 4)

#define NI_WEGAMMA_CONTWOW                             0x6a80
#       define NI_GWPH_WEGAMMA_MODE(x)                 (((x) & 0x7) << 0)
#       define NI_WEGAMMA_BYPASS                       0
#       define NI_WEGAMMA_SWGB_24                      1
#       define NI_WEGAMMA_XVYCC_222                    2
#       define NI_WEGAMMA_PWOG_A                       3
#       define NI_WEGAMMA_PWOG_B                       4
#       define NI_OVW_WEGAMMA_MODE(x)                  (((x) & 0x7) << 4)

#define NI_DP_MSE_WINK_TIMING                          0x73a0
#	define NI_DP_MSE_WINK_FWAME			(((x) & 0x3ff) << 0)
#	define NI_DP_MSE_WINK_WINE                      (((x) & 0x3) << 16)

#define NI_DP_MSE_MISC_CNTW                            0x736c
#       define NI_DP_MSE_BWANK_CODE                    (((x) & 0x1) << 0)
#       define NI_DP_MSE_TIMESTAMP_MODE                (((x) & 0x1) << 4)
#       define NI_DP_MSE_ZEWO_ENCODEW                  (((x) & 0x1) << 8)

#define NI_DP_MSE_WATE_CNTW                            0x7384
#       define NI_DP_MSE_WATE_Y(x)                   (((x) & 0x3ffffff) << 0)
#       define NI_DP_MSE_WATE_X(x)                   (((x) & 0x3f) << 26)

#define NI_DP_MSE_WATE_UPDATE                          0x738c

#define NI_DP_MSE_SAT0                                 0x7390
#       define NI_DP_MSE_SAT_SWC0(x)                   (((x) & 0x7) << 0)
#       define NI_DP_MSE_SAT_SWOT_COUNT0(x)            (((x) & 0x3f) << 8)
#       define NI_DP_MSE_SAT_SWC1(x)                   (((x) & 0x7) << 16)
#       define NI_DP_MSE_SAT_SWOT_COUNT1(x)            (((x) & 0x3f) << 24)

#define NI_DP_MSE_SAT1                                 0x7394

#define NI_DP_MSE_SAT2                                 0x7398

#define NI_DP_MSE_SAT_UPDATE                           0x739c
#       define NI_DP_MSE_SAT_UPDATE_MASK               0x3
#       define NI_DP_MSE_16_MTP_KEEPOUT                0x100

#define NI_DIG_BE_CNTW                                 0x7140
#       define NI_DIG_FE_SOUWCE_SEWECT(x)              (((x) & 0x7f) << 8)
#       define NI_DIG_FE_DIG_MODE(x)                   (((x) & 0x7) << 16)
#       define NI_DIG_MODE_DP_SST                      0
#       define NI_DIG_MODE_WVDS                        1
#       define NI_DIG_MODE_TMDS_DVI                    2
#       define NI_DIG_MODE_TMDS_HDMI                   3
#       define NI_DIG_MODE_DP_MST                      5
#       define NI_DIG_HPD_SEWECT(x)                    (((x) & 0x7) << 28)

#define NI_DIG_FE_CNTW                                 0x7000
#       define NI_DIG_SOUWCE_SEWECT(x)                 (((x) & 0x3) << 0)
#       define NI_DIG_STEWEOSYNC_SEWECT(x)             (((x) & 0x3) << 4)
#       define NI_DIG_STEWEOSYNC_GATE_EN(x)            (((x) & 0x1) << 8)
#       define NI_DIG_DUAW_WINK_ENABWE(x)              (((x) & 0x1) << 16)
#       define NI_DIG_SWAP(x)                          (((x) & 0x1) << 18)
#       define NI_DIG_SYMCWK_FE_ON                     (0x1 << 24)
#endif
