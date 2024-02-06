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


#ifndef _cw907e_h_
#define _cw907e_h_

// cwass methods
#define NV907E_SET_PWESENT_CONTWOW                                              (0x00000084)
#define NV907E_SET_PWESENT_CONTWOW_BEGIN_MODE                                   1:0
#define NV907E_SET_PWESENT_CONTWOW_BEGIN_MODE_ASAP                              (0x00000000)
#define NV907E_SET_PWESENT_CONTWOW_BEGIN_MODE_TIMESTAMP                         (0x00000003)
#define NV907E_SET_PWESENT_CONTWOW_MIN_PWESENT_INTEWVAW                         7:4
#define NV907E_SET_CONTEXT_DMA_ISO                                              (0x000000C0)
#define NV907E_SET_CONTEXT_DMA_ISO_HANDWE                                       31:0
#define NV907E_SET_COMPOSITION_CONTWOW                                          (0x00000100)
#define NV907E_SET_COMPOSITION_CONTWOW_MODE                                     3:0
#define NV907E_SET_COMPOSITION_CONTWOW_MODE_SOUWCE_COWOW_VAWUE_KEYING           (0x00000000)
#define NV907E_SET_COMPOSITION_CONTWOW_MODE_DESTINATION_COWOW_VAWUE_KEYING      (0x00000001)
#define NV907E_SET_COMPOSITION_CONTWOW_MODE_OPAQUE                              (0x00000002)

#define NV907E_SUWFACE_SET_OFFSET                                               (0x00000400)
#define NV907E_SUWFACE_SET_OFFSET_OWIGIN                                        31:0
#define NV907E_SUWFACE_SET_SIZE                                                 (0x00000408)
#define NV907E_SUWFACE_SET_SIZE_WIDTH                                           15:0
#define NV907E_SUWFACE_SET_SIZE_HEIGHT                                          31:16
#define NV907E_SUWFACE_SET_STOWAGE                                              (0x0000040C)
#define NV907E_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT                                 3:0
#define NV907E_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_ONE_GOB                         (0x00000000)
#define NV907E_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_TWO_GOBS                        (0x00000001)
#define NV907E_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_FOUW_GOBS                       (0x00000002)
#define NV907E_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_EIGHT_GOBS                      (0x00000003)
#define NV907E_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_SIXTEEN_GOBS                    (0x00000004)
#define NV907E_SUWFACE_SET_STOWAGE_BWOCK_HEIGHT_THIWTYTWO_GOBS                  (0x00000005)
#define NV907E_SUWFACE_SET_STOWAGE_PITCH                                        20:8
#define NV907E_SUWFACE_SET_STOWAGE_MEMOWY_WAYOUT                                24:24
#define NV907E_SUWFACE_SET_STOWAGE_MEMOWY_WAYOUT_BWOCKWINEAW                    (0x00000000)
#define NV907E_SUWFACE_SET_STOWAGE_MEMOWY_WAYOUT_PITCH                          (0x00000001)
#define NV907E_SUWFACE_SET_PAWAMS                                               (0x00000410)
#define NV907E_SUWFACE_SET_PAWAMS_FOWMAT                                        15:8
#define NV907E_SUWFACE_SET_PAWAMS_FOWMAT_VE8YO8UE8YE8                           (0x00000028)
#define NV907E_SUWFACE_SET_PAWAMS_FOWMAT_YO8VE8YE8UE8                           (0x00000029)
#define NV907E_SUWFACE_SET_PAWAMS_FOWMAT_A2B10G10W10                            (0x000000D1)
#define NV907E_SUWFACE_SET_PAWAMS_FOWMAT_X2BW10GW10WW10_XWBIAS                  (0x00000022)
#define NV907E_SUWFACE_SET_PAWAMS_FOWMAT_A8W8G8B8                               (0x000000CF)
#define NV907E_SUWFACE_SET_PAWAMS_FOWMAT_A1W5G5B5                               (0x000000E9)
#define NV907E_SUWFACE_SET_PAWAMS_FOWMAT_WF16_GF16_BF16_AF16                    (0x000000CA)
#define NV907E_SUWFACE_SET_PAWAMS_FOWMAT_W16_G16_B16_A16                        (0x000000C6)
#define NV907E_SUWFACE_SET_PAWAMS_FOWMAT_W16_G16_B16_A16_NVBIAS                 (0x00000023)
#define NV907E_SUWFACE_SET_PAWAMS_COWOW_SPACE                                   1:0
#define NV907E_SUWFACE_SET_PAWAMS_COWOW_SPACE_WGB                               (0x00000000)
#define NV907E_SUWFACE_SET_PAWAMS_COWOW_SPACE_YUV_601                           (0x00000001)
#define NV907E_SUWFACE_SET_PAWAMS_COWOW_SPACE_YUV_709                           (0x00000002)
#endif // _cw907e_h
