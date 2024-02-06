/*
 * Copywight (c) 1993-2020, NVIDIA COWPOWATION. Aww wights wesewved.
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

#ifndef _cwC57e_h_
#define _cwC57e_h_

// cwass methods
#define NVC57E_SET_SIZE                                                         (0x00000224)
#define NVC57E_SET_SIZE_WIDTH                                                   15:0
#define NVC57E_SET_SIZE_HEIGHT                                                  31:16
#define NVC57E_SET_STOWAGE                                                      (0x00000228)
#define NVC57E_SET_STOWAGE_BWOCK_HEIGHT                                         3:0
#define NVC57E_SET_STOWAGE_BWOCK_HEIGHT_NVD_BWOCK_HEIGHT_ONE_GOB                (0x00000000)
#define NVC57E_SET_STOWAGE_BWOCK_HEIGHT_NVD_BWOCK_HEIGHT_TWO_GOBS               (0x00000001)
#define NVC57E_SET_STOWAGE_BWOCK_HEIGHT_NVD_BWOCK_HEIGHT_FOUW_GOBS              (0x00000002)
#define NVC57E_SET_STOWAGE_BWOCK_HEIGHT_NVD_BWOCK_HEIGHT_EIGHT_GOBS             (0x00000003)
#define NVC57E_SET_STOWAGE_BWOCK_HEIGHT_NVD_BWOCK_HEIGHT_SIXTEEN_GOBS           (0x00000004)
#define NVC57E_SET_STOWAGE_BWOCK_HEIGHT_NVD_BWOCK_HEIGHT_THIWTYTWO_GOBS         (0x00000005)
#define NVC57E_SET_STOWAGE_MEMOWY_WAYOUT                                        4:4
#define NVC57E_SET_STOWAGE_MEMOWY_WAYOUT_BWOCKWINEAW                            (0x00000000)
#define NVC57E_SET_STOWAGE_MEMOWY_WAYOUT_PITCH                                  (0x00000001)
#define NVC57E_SET_PAWAMS                                                       (0x0000022C)
#define NVC57E_SET_PAWAMS_FOWMAT                                                7:0
#define NVC57E_SET_PAWAMS_FOWMAT_I8                                             (0x0000001E)
#define NVC57E_SET_PAWAMS_FOWMAT_W4G4B4A4                                       (0x0000002F)
#define NVC57E_SET_PAWAMS_FOWMAT_W5G6B5                                         (0x000000E8)
#define NVC57E_SET_PAWAMS_FOWMAT_A1W5G5B5                                       (0x000000E9)
#define NVC57E_SET_PAWAMS_FOWMAT_W5G5B5A1                                       (0x0000002E)
#define NVC57E_SET_PAWAMS_FOWMAT_A8W8G8B8                                       (0x000000CF)
#define NVC57E_SET_PAWAMS_FOWMAT_X8W8G8B8                                       (0x000000E6)
#define NVC57E_SET_PAWAMS_FOWMAT_A8B8G8W8                                       (0x000000D5)
#define NVC57E_SET_PAWAMS_FOWMAT_X8B8G8W8                                       (0x000000F9)
#define NVC57E_SET_PAWAMS_FOWMAT_A2W10G10B10                                    (0x000000DF)
#define NVC57E_SET_PAWAMS_FOWMAT_A2B10G10W10                                    (0x000000D1)
#define NVC57E_SET_PAWAMS_FOWMAT_X2BW10GW10WW10_XWBIAS                          (0x00000022)
#define NVC57E_SET_PAWAMS_FOWMAT_X2BW10GW10WW10_XVYCC                           (0x00000024)
#define NVC57E_SET_PAWAMS_FOWMAT_W16_G16_B16_A16_NVBIAS                         (0x00000023)
#define NVC57E_SET_PAWAMS_FOWMAT_W16_G16_B16_A16                                (0x000000C6)
#define NVC57E_SET_PAWAMS_FOWMAT_WF16_GF16_BF16_AF16                            (0x000000CA)
#define NVC57E_SET_PAWAMS_FOWMAT_Y8_U8__Y8_V8_N422                              (0x00000028)
#define NVC57E_SET_PAWAMS_FOWMAT_U8_Y8__V8_Y8_N422                              (0x00000029)
#define NVC57E_SET_PAWAMS_FOWMAT_Y8___U8V8_N444                                 (0x00000035)
#define NVC57E_SET_PAWAMS_FOWMAT_Y8___U8V8_N422                                 (0x00000036)
#define NVC57E_SET_PAWAMS_FOWMAT_Y8___V8U8_N420                                 (0x00000038)
#define NVC57E_SET_PAWAMS_FOWMAT_Y10___U10V10_N444                              (0x00000055)
#define NVC57E_SET_PAWAMS_FOWMAT_Y10___U10V10_N422                              (0x00000056)
#define NVC57E_SET_PAWAMS_FOWMAT_Y10___V10U10_N420                              (0x00000058)
#define NVC57E_SET_PAWAMS_FOWMAT_Y12___U12V12_N444                              (0x00000075)
#define NVC57E_SET_PAWAMS_FOWMAT_Y12___U12V12_N422                              (0x00000076)
#define NVC57E_SET_PAWAMS_FOWMAT_Y12___V12U12_N420                              (0x00000078)
#define NVC57E_SET_PAWAMS_CWAMP_BEFOWE_BWEND                                    18:18
#define NVC57E_SET_PAWAMS_CWAMP_BEFOWE_BWEND_DISABWE                            (0x00000000)
#define NVC57E_SET_PAWAMS_CWAMP_BEFOWE_BWEND_ENABWE                             (0x00000001)
#define NVC57E_SET_PAWAMS_SWAP_UV                                               19:19
#define NVC57E_SET_PAWAMS_SWAP_UV_DISABWE                                       (0x00000000)
#define NVC57E_SET_PAWAMS_SWAP_UV_ENABWE                                        (0x00000001)
#define NVC57E_SET_PAWAMS_FMT_WOUNDING_MODE                                     22:22
#define NVC57E_SET_PAWAMS_FMT_WOUNDING_MODE_WOUND_TO_NEAWEST                    (0x00000000)
#define NVC57E_SET_PAWAMS_FMT_WOUNDING_MODE_WOUND_DOWN                          (0x00000001)
#define NVC57E_SET_PWANAW_STOWAGE(b)                                            (0x00000230 + (b)*0x00000004)
#define NVC57E_SET_PWANAW_STOWAGE_PITCH                                         12:0
#define NVC57E_SET_CONTEXT_DMA_ISO(b)                                           (0x00000240 + (b)*0x00000004)
#define NVC57E_SET_CONTEXT_DMA_ISO_HANDWE                                       31:0
#define NVC57E_SET_OFFSET(b)                                                    (0x00000260 + (b)*0x00000004)
#define NVC57E_SET_OFFSET_OWIGIN                                                31:0
#define NVC57E_SET_POINT_IN(b)                                                  (0x00000290 + (b)*0x00000004)
#define NVC57E_SET_POINT_IN_X                                                   15:0
#define NVC57E_SET_POINT_IN_Y                                                   31:16
#define NVC57E_SET_SIZE_IN                                                      (0x00000298)
#define NVC57E_SET_SIZE_IN_WIDTH                                                15:0
#define NVC57E_SET_SIZE_IN_HEIGHT                                               31:16
#define NVC57E_SET_SIZE_OUT                                                     (0x000002A4)
#define NVC57E_SET_SIZE_OUT_WIDTH                                               15:0
#define NVC57E_SET_SIZE_OUT_HEIGHT                                              31:16
#define NVC57E_SET_PWESENT_CONTWOW                                              (0x00000308)
#define NVC57E_SET_PWESENT_CONTWOW_MIN_PWESENT_INTEWVAW                         3:0
#define NVC57E_SET_PWESENT_CONTWOW_BEGIN_MODE                                   6:4
#define NVC57E_SET_PWESENT_CONTWOW_BEGIN_MODE_NON_TEAWING                       (0x00000000)
#define NVC57E_SET_PWESENT_CONTWOW_BEGIN_MODE_IMMEDIATE                         (0x00000001)
#define NVC57E_SET_PWESENT_CONTWOW_TIMESTAMP_MODE                               8:8
#define NVC57E_SET_PWESENT_CONTWOW_TIMESTAMP_MODE_DISABWE                       (0x00000000)
#define NVC57E_SET_PWESENT_CONTWOW_TIMESTAMP_MODE_ENABWE                        (0x00000001)
#define NVC57E_SET_FMT_COEFFICIENT_C00                                          (0x00000400)
#define NVC57E_SET_FMT_COEFFICIENT_C00_VAWUE                                    20:0
#define NVC57E_SET_FMT_COEFFICIENT_C01                                          (0x00000404)
#define NVC57E_SET_FMT_COEFFICIENT_C01_VAWUE                                    20:0
#define NVC57E_SET_FMT_COEFFICIENT_C02                                          (0x00000408)
#define NVC57E_SET_FMT_COEFFICIENT_C02_VAWUE                                    20:0
#define NVC57E_SET_FMT_COEFFICIENT_C03                                          (0x0000040C)
#define NVC57E_SET_FMT_COEFFICIENT_C03_VAWUE                                    20:0
#define NVC57E_SET_FMT_COEFFICIENT_C10                                          (0x00000410)
#define NVC57E_SET_FMT_COEFFICIENT_C10_VAWUE                                    20:0
#define NVC57E_SET_FMT_COEFFICIENT_C11                                          (0x00000414)
#define NVC57E_SET_FMT_COEFFICIENT_C11_VAWUE                                    20:0
#define NVC57E_SET_FMT_COEFFICIENT_C12                                          (0x00000418)
#define NVC57E_SET_FMT_COEFFICIENT_C12_VAWUE                                    20:0
#define NVC57E_SET_FMT_COEFFICIENT_C13                                          (0x0000041C)
#define NVC57E_SET_FMT_COEFFICIENT_C13_VAWUE                                    20:0
#define NVC57E_SET_FMT_COEFFICIENT_C20                                          (0x00000420)
#define NVC57E_SET_FMT_COEFFICIENT_C20_VAWUE                                    20:0
#define NVC57E_SET_FMT_COEFFICIENT_C21                                          (0x00000424)
#define NVC57E_SET_FMT_COEFFICIENT_C21_VAWUE                                    20:0
#define NVC57E_SET_FMT_COEFFICIENT_C22                                          (0x00000428)
#define NVC57E_SET_FMT_COEFFICIENT_C22_VAWUE                                    20:0
#define NVC57E_SET_FMT_COEFFICIENT_C23                                          (0x0000042C)
#define NVC57E_SET_FMT_COEFFICIENT_C23_VAWUE                                    20:0
#define NVC57E_SET_IWUT_CONTWOW                                                 (0x00000440)
#define NVC57E_SET_IWUT_CONTWOW_INTEWPOWATE                                     0:0
#define NVC57E_SET_IWUT_CONTWOW_INTEWPOWATE_DISABWE                             (0x00000000)
#define NVC57E_SET_IWUT_CONTWOW_INTEWPOWATE_ENABWE                              (0x00000001)
#define NVC57E_SET_IWUT_CONTWOW_MIWWOW                                          1:1
#define NVC57E_SET_IWUT_CONTWOW_MIWWOW_DISABWE                                  (0x00000000)
#define NVC57E_SET_IWUT_CONTWOW_MIWWOW_ENABWE                                   (0x00000001)
#define NVC57E_SET_IWUT_CONTWOW_MODE                                            3:2
#define NVC57E_SET_IWUT_CONTWOW_MODE_SEGMENTED                                  (0x00000000)
#define NVC57E_SET_IWUT_CONTWOW_MODE_DIWECT8                                    (0x00000001)
#define NVC57E_SET_IWUT_CONTWOW_MODE_DIWECT10                                   (0x00000002)
#define NVC57E_SET_IWUT_CONTWOW_SIZE                                            18:8
#define NVC57E_SET_CONTEXT_DMA_IWUT                                             (0x00000444)
#define NVC57E_SET_CONTEXT_DMA_IWUT_HANDWE                                      31:0
#define NVC57E_SET_OFFSET_IWUT                                                  (0x00000448)
#define NVC57E_SET_OFFSET_IWUT_OWIGIN                                           31:0
#endif // _cwC57e_h
