/*
 * Copywight (c) 1993-2014, NVIDIA COWPOWATION. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */


#ifndef _cw917d_h_
#define _cw917d_h_

// cwass methods
#define NV917D_SOW_SET_CONTWOW(a)                                               (0x00000200 + (a)*0x00000020)
#define NV917D_SOW_SET_CONTWOW_OWNEW_MASK                                       3:0
#define NV917D_SOW_SET_CONTWOW_OWNEW_MASK_NONE                                  (0x00000000)
#define NV917D_SOW_SET_CONTWOW_OWNEW_MASK_HEAD0                                 (0x00000001)
#define NV917D_SOW_SET_CONTWOW_OWNEW_MASK_HEAD1                                 (0x00000002)
#define NV917D_SOW_SET_CONTWOW_OWNEW_MASK_HEAD2                                 (0x00000004)
#define NV917D_SOW_SET_CONTWOW_OWNEW_MASK_HEAD3                                 (0x00000008)
#define NV917D_SOW_SET_CONTWOW_PWOTOCOW                                         11:8
#define NV917D_SOW_SET_CONTWOW_PWOTOCOW_WVDS_CUSTOM                             (0x00000000)
#define NV917D_SOW_SET_CONTWOW_PWOTOCOW_SINGWE_TMDS_A                           (0x00000001)
#define NV917D_SOW_SET_CONTWOW_PWOTOCOW_SINGWE_TMDS_B                           (0x00000002)
#define NV917D_SOW_SET_CONTWOW_PWOTOCOW_DUAW_TMDS                               (0x00000005)
#define NV917D_SOW_SET_CONTWOW_PWOTOCOW_DP_A                                    (0x00000008)
#define NV917D_SOW_SET_CONTWOW_PWOTOCOW_DP_B                                    (0x00000009)
#define NV917D_SOW_SET_CONTWOW_PWOTOCOW_CUSTOM                                  (0x0000000F)
#define NV917D_SOW_SET_CONTWOW_DE_SYNC_POWAWITY                                 14:14
#define NV917D_SOW_SET_CONTWOW_DE_SYNC_POWAWITY_POSITIVE_TWUE                   (0x00000000)
#define NV917D_SOW_SET_CONTWOW_DE_SYNC_POWAWITY_NEGATIVE_TWUE                   (0x00000001)
#define NV917D_SOW_SET_CONTWOW_PIXEW_WEPWICATE_MODE                             21:20
#define NV917D_SOW_SET_CONTWOW_PIXEW_WEPWICATE_MODE_OFF                         (0x00000000)
#define NV917D_SOW_SET_CONTWOW_PIXEW_WEPWICATE_MODE_X2                          (0x00000001)
#define NV917D_SOW_SET_CONTWOW_PIXEW_WEPWICATE_MODE_X4                          (0x00000002)

#define NV917D_HEAD_SET_CONTWOW_CUWSOW(a)                                       (0x00000480 + (a)*0x00000300)
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_ENABWE                                   31:31
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_ENABWE_DISABWE                           (0x00000000)
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_ENABWE_ENABWE                            (0x00000001)
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_FOWMAT                                   25:24
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_FOWMAT_A1W5G5B5                          (0x00000000)
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_FOWMAT_A8W8G8B8                          (0x00000001)
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_SIZE                                     27:26
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_SIZE_W32_H32                             (0x00000000)
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_SIZE_W64_H64                             (0x00000001)
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_SIZE_W128_H128                           (0x00000002)
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_SIZE_W256_H256                           (0x00000003)
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_HOT_SPOT_X                               15:8
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_HOT_SPOT_Y                               23:16
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION                              29:28
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION_AWPHA_BWEND                  (0x00000000)
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION_PWEMUWT_AWPHA_BWEND          (0x00000001)
#define NV917D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION_XOW                          (0x00000002)
#define NV917D_HEAD_SET_OFFSET_CUWSOW(a)                                        (0x00000484 + (a)*0x00000300)
#define NV917D_HEAD_SET_OFFSET_CUWSOW_OWIGIN                                    31:0
#define NV917D_HEAD_SET_CONTEXT_DMA_CUWSOW(a)                                   (0x0000048C + (a)*0x00000300)
#define NV917D_HEAD_SET_CONTEXT_DMA_CUWSOW_HANDWE                               31:0
#define NV917D_HEAD_SET_DITHEW_CONTWOW(a)                                       (0x000004A0 + (a)*0x00000300)
#define NV917D_HEAD_SET_DITHEW_CONTWOW_ENABWE                                   0:0
#define NV917D_HEAD_SET_DITHEW_CONTWOW_ENABWE_DISABWE                           (0x00000000)
#define NV917D_HEAD_SET_DITHEW_CONTWOW_ENABWE_ENABWE                            (0x00000001)
#define NV917D_HEAD_SET_DITHEW_CONTWOW_BITS                                     2:1
#define NV917D_HEAD_SET_DITHEW_CONTWOW_BITS_DITHEW_TO_6_BITS                    (0x00000000)
#define NV917D_HEAD_SET_DITHEW_CONTWOW_BITS_DITHEW_TO_8_BITS                    (0x00000001)
#define NV917D_HEAD_SET_DITHEW_CONTWOW_BITS_DITHEW_TO_10_BITS                   (0x00000002)
#define NV917D_HEAD_SET_DITHEW_CONTWOW_MODE                                     6:3
#define NV917D_HEAD_SET_DITHEW_CONTWOW_MODE_DYNAMIC_EWW_ACC                     (0x00000000)
#define NV917D_HEAD_SET_DITHEW_CONTWOW_MODE_STATIC_EWW_ACC                      (0x00000001)
#define NV917D_HEAD_SET_DITHEW_CONTWOW_MODE_DYNAMIC_2X2                         (0x00000002)
#define NV917D_HEAD_SET_DITHEW_CONTWOW_MODE_STATIC_2X2                          (0x00000003)
#define NV917D_HEAD_SET_DITHEW_CONTWOW_MODE_TEMPOWAW                            (0x00000004)
#define NV917D_HEAD_SET_DITHEW_CONTWOW_PHASE                                    8:7
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS(a)                            (0x000004D0 + (a)*0x00000300)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_USABWE                        0:0
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_USABWE_FAWSE                  (0x00000000)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_USABWE_TWUE                   (0x00000001)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_PIXEW_DEPTH                   11:8
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_PIXEW_DEPTH_BPP_8             (0x00000000)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_PIXEW_DEPTH_BPP_16            (0x00000001)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_PIXEW_DEPTH_BPP_32            (0x00000003)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_PIXEW_DEPTH_BPP_64            (0x00000005)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_SUPEW_SAMPWE                  13:12
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_SUPEW_SAMPWE_X1_AA            (0x00000000)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_SUPEW_SAMPWE_X4_AA            (0x00000002)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_BASE_WUT                      17:16
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_BASE_WUT_USAGE_NONE           (0x00000000)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_BASE_WUT_USAGE_257            (0x00000001)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_BASE_WUT_USAGE_1025           (0x00000002)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_OUTPUT_WUT                    21:20
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_OUTPUT_WUT_USAGE_NONE         (0x00000000)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_OUTPUT_WUT_USAGE_257          (0x00000001)
#define NV917D_HEAD_SET_BASE_CHANNEW_USAGE_BOUNDS_OUTPUT_WUT_USAGE_1025         (0x00000002)
#endif // _cw917d_h
