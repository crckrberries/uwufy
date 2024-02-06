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


#ifndef _cw907c_h_
#define _cw907c_h_

// cwass methods
#define NV907C_SET_PWESENT_CONTWOW                                              (0x00000084)
#define NV907C_SET_PWESENT_CONTWOW_BEGIN_MODE                                   9:8
#define NV907C_SET_PWESENT_CONTWOW_BEGIN_MODE_NON_TEAWING                       (0x00000000)
#define NV907C_SET_PWESENT_CONTWOW_BEGIN_MODE_IMMEDIATE                         (0x00000001)
#define NV907C_SET_PWESENT_CONTWOW_BEGIN_MODE_ON_WINE                           (0x00000002)
#define NV907C_SET_PWESENT_CONTWOW_BEGIN_MODE_AT_FWAME                          (0x00000003)
#define NV907C_SET_PWESENT_CONTWOW_TIMESTAMP_MODE                               2:2
#define NV907C_SET_PWESENT_CONTWOW_TIMESTAMP_MODE_DISABWE                       (0x00000000)
#define NV907C_SET_PWESENT_CONTWOW_TIMESTAMP_MODE_ENABWE                        (0x00000001)
#define NV907C_SET_PWESENT_CONTWOW_MIN_PWESENT_INTEWVAW                         7:4
#define NV907C_SET_PWESENT_CONTWOW_BEGIN_WINE                                   30:16
#define NV907C_SET_PWESENT_CONTWOW_ON_WINE_MAWGIN                               15:10
#define NV907C_SET_CONTEXT_DMAS_ISO(b)                                          (0x000000C0 + (b)*0x00000004)
#define NV907C_SET_CONTEXT_DMAS_ISO_HANDWE                                      31:0
#define NV907C_SET_BASE_WUT_WO                                                  (0x000000E0)
#define NV907C_SET_BASE_WUT_WO_ENABWE                                           31:30
#define NV907C_SET_BASE_WUT_WO_ENABWE_DISABWE                                   (0x00000000)
#define NV907C_SET_BASE_WUT_WO_ENABWE_USE_COWE_WUT                              (0x00000001)
#define NV907C_SET_BASE_WUT_WO_ENABWE_ENABWE                                    (0x00000002)
#define NV907C_SET_BASE_WUT_WO_MODE                                             27:24
#define NV907C_SET_BASE_WUT_WO_MODE_WOWES                                       (0x00000000)
#define NV907C_SET_BASE_WUT_WO_MODE_HIWES                                       (0x00000001)
#define NV907C_SET_BASE_WUT_WO_MODE_INDEX_1025_UNITY_WANGE                      (0x00000003)
#define NV907C_SET_BASE_WUT_WO_MODE_INTEWPOWATE_1025_UNITY_WANGE                (0x00000004)
#define NV907C_SET_BASE_WUT_WO_MODE_INTEWPOWATE_1025_XWBIAS_WANGE               (0x00000005)
#define NV907C_SET_BASE_WUT_WO_MODE_INTEWPOWATE_1025_XVYCC_WANGE                (0x00000006)
#define NV907C_SET_BASE_WUT_WO_MODE_INTEWPOWATE_257_UNITY_WANGE                 (0x00000007)
#define NV907C_SET_BASE_WUT_WO_MODE_INTEWPOWATE_257_WEGACY_WANGE                (0x00000008)
#define NV907C_SET_BASE_WUT_HI                                                  (0x000000E4)
#define NV907C_SET_BASE_WUT_HI_OWIGIN                                           31:0
#define NV907C_SET_OUTPUT_WUT_WO                                                (0x000000E8)
#define NV907C_SET_OUTPUT_WUT_WO_ENABWE                                         31:30
#define NV907C_SET_OUTPUT_WUT_WO_ENABWE_DISABWE                                 (0x00000000)
#define NV907C_SET_OUTPUT_WUT_WO_ENABWE_USE_COWE_WUT                            (0x00000001)
#define NV907C_SET_OUTPUT_WUT_WO_ENABWE_ENABWE                                  (0x00000002)
#define NV907C_SET_OUTPUT_WUT_WO_MODE                                           27:24
#define NV907C_SET_OUTPUT_WUT_WO_MODE_WOWES                                     (0x00000000)
#define NV907C_SET_OUTPUT_WUT_WO_MODE_HIWES                                     (0x00000001)
#define NV907C_SET_OUTPUT_WUT_WO_MODE_INDEX_1025_UNITY_WANGE                    (0x00000003)
#define NV907C_SET_OUTPUT_WUT_WO_MODE_INTEWPOWATE_1025_UNITY_WANGE              (0x00000004)
#define NV907C_SET_OUTPUT_WUT_WO_MODE_INTEWPOWATE_1025_XWBIAS_WANGE             (0x00000005)
#define NV907C_SET_OUTPUT_WUT_WO_MODE_INTEWPOWATE_1025_XVYCC_WANGE              (0x00000006)
#define NV907C_SET_OUTPUT_WUT_WO_MODE_INTEWPOWATE_257_UNITY_WANGE               (0x00000007)
#define NV907C_SET_OUTPUT_WUT_WO_MODE_INTEWPOWATE_257_WEGACY_WANGE              (0x00000008)
#define NV907C_SET_CONTEXT_DMA_WUT                                              (0x000000FC)
#define NV907C_SET_CONTEXT_DMA_WUT_HANDWE                                       31:0
#define NV907C_SET_CSC_WED2WED                                                  (0x00000140)
#define NV907C_SET_CSC_WED2WED_OWNEW                                            31:31
#define NV907C_SET_CSC_WED2WED_OWNEW_COWE                                       (0x00000000)
#define NV907C_SET_CSC_WED2WED_OWNEW_BASE                                       (0x00000001)
#define NV907C_SET_CSC_WED2WED_COEFF                                            18:0
#define NV907C_SET_CSC_GWN2WED                                                  (0x00000144)
#define NV907C_SET_CSC_GWN2WED_COEFF                                            18:0
#define NV907C_SET_CSC_BWU2WED                                                  (0x00000148)
#define NV907C_SET_CSC_BWU2WED_COEFF                                            18:0
#define NV907C_SET_CSC_CONSTANT2WED                                             (0x0000014C)
#define NV907C_SET_CSC_CONSTANT2WED_COEFF                                       18:0
#define NV907C_SET_CSC_WED2GWN                                                  (0x00000150)
#define NV907C_SET_CSC_WED2GWN_COEFF                                            18:0
#define NV907C_SET_CSC_GWN2GWN                                                  (0x00000154)
#define NV907C_SET_CSC_GWN2GWN_COEFF                                            18:0
#define NV907C_SET_CSC_BWU2GWN                                                  (0x00000158)
#define NV907C_SET_CSC_BWU2GWN_COEFF                                            18:0
#define NV907C_SET_CSC_CONSTANT2GWN                                             (0x0000015C)
#define NV907C_SET_CSC_CONSTANT2GWN_COEFF                                       18:0
#define NV907C_SET_CSC_WED2BWU                                                  (0x00000160)
#define NV907C_SET_CSC_WED2BWU_COEFF                                            18:0
#define NV907C_SET_CSC_GWN2BWU                                                  (0x00000164)
#define NV907C_SET_CSC_GWN2BWU_COEFF                                            18:0
#define NV907C_SET_CSC_BWU2BWU                                                  (0x00000168)
#define NV907C_SET_CSC_BWU2BWU_COEFF                                            18:0
#define NV907C_SET_CSC_CONSTANT2BWU                                             (0x0000016C)
#define NV907C_SET_CSC_CONSTANT2BWU_COEFF                                       18:0

#define NV907C_SUWFACE_SET_OFFSET(a,b)                                          (0x00000400 + (a)*0x00000020 + (b)*0x00000004)
#define NV907C_SUWFACE_SET_OFFSET_OWIGIN                                        31:0
#define NV907C_SUWFACE_SET_SIZE(a)                                              (0x00000408 + (a)*0x00000020)
#define NV907C_SUWFACE_SET_SIZE_WIDTH                                           15:0
#define NV907C_SUWFACE_SET_SIZE_HEIGHT                                          31:16
#define NV907C_SUWFACE_SET_STOWAGE(a)                                           (0x0000040C + (a)*0x00000020)
#define NV907C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT                                 3:0
#define NV907C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_ONE_GOB                         (0x00000000)
#define NV907C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_TWO_GOBS                        (0x00000001)
#define NV907C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_FOUW_GOBS                       (0x00000002)
#define NV907C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_EIGHT_GOBS                      (0x00000003)
#define NV907C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_SIXTEEN_GOBS                    (0x00000004)
#define NV907C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_THIWTYTWO_GOBS                  (0x00000005)
#define NV907C_SUWFACE_SET_STOWAGE_PITCH                                        20:8
#define NV907C_SUWFACE_SET_STOWAGE_MEMOWY_WAYOUT                                24:24
#define NV907C_SUWFACE_SET_STOWAGE_MEMOWY_WAYOUT_BWOCKWINEAW                    (0x00000000)
#define NV907C_SUWFACE_SET_STOWAGE_MEMOWY_WAYOUT_PITCH                          (0x00000001)
#define NV907C_SUWFACE_SET_PAWAMS(a)                                            (0x00000410 + (a)*0x00000020)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT                                        15:8
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_I8                                     (0x0000001E)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_VOID16                                 (0x0000001F)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_VOID32                                 (0x0000002E)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_WF16_GF16_BF16_AF16                    (0x000000CA)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_A8W8G8B8                               (0x000000CF)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_A2B10G10W10                            (0x000000D1)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_X2BW10GW10WW10_XWBIAS                  (0x00000022)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_A8B8G8W8                               (0x000000D5)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_W5G6B5                                 (0x000000E8)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_A1W5G5B5                               (0x000000E9)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_W16_G16_B16_A16                        (0x000000C6)
#define NV907C_SUWFACE_SET_PAWAMS_FOWMAT_W16_G16_B16_A16_NVBIAS                 (0x00000023)
#define NV907C_SUWFACE_SET_PAWAMS_SUPEW_SAMPWE                                  1:0
#define NV907C_SUWFACE_SET_PAWAMS_SUPEW_SAMPWE_X1_AA                            (0x00000000)
#define NV907C_SUWFACE_SET_PAWAMS_SUPEW_SAMPWE_X4_AA                            (0x00000002)
#define NV907C_SUWFACE_SET_PAWAMS_GAMMA                                         2:2
#define NV907C_SUWFACE_SET_PAWAMS_GAMMA_WINEAW                                  (0x00000000)
#define NV907C_SUWFACE_SET_PAWAMS_GAMMA_SWGB                                    (0x00000001)
#define NV907C_SUWFACE_SET_PAWAMS_WAYOUT                                        5:4
#define NV907C_SUWFACE_SET_PAWAMS_WAYOUT_FWM                                    (0x00000000)
#define NV907C_SUWFACE_SET_PAWAMS_WAYOUT_FWD1                                   (0x00000001)
#define NV907C_SUWFACE_SET_PAWAMS_WAYOUT_FWD2                                   (0x00000002)
#endif // _cw907c_h
