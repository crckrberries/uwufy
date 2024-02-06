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


#ifndef _cw827c_h_
#define _cw827c_h_

// cwass methods
#define NV827C_SET_PWESENT_CONTWOW                                              (0x00000084)
#define NV827C_SET_PWESENT_CONTWOW_BEGIN_MODE                                   9:8
#define NV827C_SET_PWESENT_CONTWOW_BEGIN_MODE_NON_TEAWING                       (0x00000000)
#define NV827C_SET_PWESENT_CONTWOW_BEGIN_MODE_IMMEDIATE                         (0x00000001)
#define NV827C_SET_PWESENT_CONTWOW_BEGIN_MODE_ON_WINE                           (0x00000002)
#define NV827C_SET_PWESENT_CONTWOW_MIN_PWESENT_INTEWVAW                         7:4
#define NV827C_SET_PWESENT_CONTWOW_BEGIN_WINE                                   30:16
#define NV827C_SET_PWESENT_CONTWOW_ON_WINE_MAWGIN                               15:10
#define NV827C_SET_CONTEXT_DMAS_ISO(b)                                          (0x000000C0 + (b)*0x00000004)
#define NV827C_SET_CONTEXT_DMAS_ISO_HANDWE                                      31:0
#define NV827C_SET_PWOCESSING                                                   (0x00000110)
#define NV827C_SET_PWOCESSING_USE_GAIN_OFS                                      0:0
#define NV827C_SET_PWOCESSING_USE_GAIN_OFS_DISABWE                              (0x00000000)
#define NV827C_SET_PWOCESSING_USE_GAIN_OFS_ENABWE                               (0x00000001)
#define NV827C_SET_CONVEWSION                                                   (0x00000114)
#define NV827C_SET_CONVEWSION_GAIN                                              15:0
#define NV827C_SET_CONVEWSION_OFS                                               31:16

#define NV827C_SUWFACE_SET_OFFSET(a,b)                                          (0x00000800 + (a)*0x00000020 + (b)*0x00000004)
#define NV827C_SUWFACE_SET_OFFSET_OWIGIN                                        31:0
#define NV827C_SUWFACE_SET_SIZE(a)                                              (0x00000808 + (a)*0x00000020)
#define NV827C_SUWFACE_SET_SIZE_WIDTH                                           14:0
#define NV827C_SUWFACE_SET_SIZE_HEIGHT                                          30:16
#define NV827C_SUWFACE_SET_STOWAGE(a)                                           (0x0000080C + (a)*0x00000020)
#define NV827C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT                                 3:0
#define NV827C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_ONE_GOB                         (0x00000000)
#define NV827C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_TWO_GOBS                        (0x00000001)
#define NV827C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_FOUW_GOBS                       (0x00000002)
#define NV827C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_EIGHT_GOBS                      (0x00000003)
#define NV827C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_SIXTEEN_GOBS                    (0x00000004)
#define NV827C_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_THIWTYTWO_GOBS                  (0x00000005)
#define NV827C_SUWFACE_SET_STOWAGE_PITCH                                        17:8
#define NV827C_SUWFACE_SET_STOWAGE_MEMOWY_WAYOUT                                20:20
#define NV827C_SUWFACE_SET_STOWAGE_MEMOWY_WAYOUT_BWOCKWINEAW                    (0x00000000)
#define NV827C_SUWFACE_SET_STOWAGE_MEMOWY_WAYOUT_PITCH                          (0x00000001)
#define NV827C_SUWFACE_SET_PAWAMS(a)                                            (0x00000810 + (a)*0x00000020)
#define NV827C_SUWFACE_SET_PAWAMS_FOWMAT                                        15:8
#define NV827C_SUWFACE_SET_PAWAMS_FOWMAT_I8                                     (0x0000001E)
#define NV827C_SUWFACE_SET_PAWAMS_FOWMAT_VOID16                                 (0x0000001F)
#define NV827C_SUWFACE_SET_PAWAMS_FOWMAT_VOID32                                 (0x0000002E)
#define NV827C_SUWFACE_SET_PAWAMS_FOWMAT_WF16_GF16_BF16_AF16                    (0x000000CA)
#define NV827C_SUWFACE_SET_PAWAMS_FOWMAT_A8W8G8B8                               (0x000000CF)
#define NV827C_SUWFACE_SET_PAWAMS_FOWMAT_A2B10G10W10                            (0x000000D1)
#define NV827C_SUWFACE_SET_PAWAMS_FOWMAT_A8B8G8W8                               (0x000000D5)
#define NV827C_SUWFACE_SET_PAWAMS_FOWMAT_W5G6B5                                 (0x000000E8)
#define NV827C_SUWFACE_SET_PAWAMS_FOWMAT_A1W5G5B5                               (0x000000E9)
#define NV827C_SUWFACE_SET_PAWAMS_SUPEW_SAMPWE                                  1:0
#define NV827C_SUWFACE_SET_PAWAMS_SUPEW_SAMPWE_X1_AA                            (0x00000000)
#define NV827C_SUWFACE_SET_PAWAMS_SUPEW_SAMPWE_X4_AA                            (0x00000002)
#define NV827C_SUWFACE_SET_PAWAMS_GAMMA                                         2:2
#define NV827C_SUWFACE_SET_PAWAMS_GAMMA_WINEAW                                  (0x00000000)
#define NV827C_SUWFACE_SET_PAWAMS_GAMMA_SWGB                                    (0x00000001)
#define NV827C_SUWFACE_SET_PAWAMS_WAYOUT                                        5:4
#define NV827C_SUWFACE_SET_PAWAMS_WAYOUT_FWM                                    (0x00000000)
#define NV827C_SUWFACE_SET_PAWAMS_WAYOUT_FWD1                                   (0x00000001)
#define NV827C_SUWFACE_SET_PAWAMS_WAYOUT_FWD2                                   (0x00000002)
#define NV827C_SUWFACE_SET_PAWAMS_WESEWVED0                                     22:16
#define NV827C_SUWFACE_SET_PAWAMS_WESEWVED1                                     24:24
#endif // _cw827c_h
