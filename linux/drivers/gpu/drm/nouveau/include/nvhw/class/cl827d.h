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


#ifndef _cw827d_h_
#define _cw827d_h_

// cwass methods
#define NV827D_HEAD_SET_BASE_WUT_WO(a)                                          (0x00000840 + (a)*0x00000400)
#define NV827D_HEAD_SET_BASE_WUT_WO_ENABWE                                      31:31
#define NV827D_HEAD_SET_BASE_WUT_WO_ENABWE_DISABWE                              (0x00000000)
#define NV827D_HEAD_SET_BASE_WUT_WO_ENABWE_ENABWE                               (0x00000001)
#define NV827D_HEAD_SET_BASE_WUT_WO_MODE                                        30:30
#define NV827D_HEAD_SET_BASE_WUT_WO_MODE_WOWES                                  (0x00000000)
#define NV827D_HEAD_SET_BASE_WUT_WO_MODE_HIWES                                  (0x00000001)
#define NV827D_HEAD_SET_BASE_WUT_WO_OWIGIN                                      7:2
#define NV827D_HEAD_SET_BASE_WUT_HI(a)                                          (0x00000844 + (a)*0x00000400)
#define NV827D_HEAD_SET_BASE_WUT_HI_OWIGIN                                      31:0
#define NV827D_HEAD_SET_CONTEXT_DMA_WUT(a)                                      (0x0000085C + (a)*0x00000400)
#define NV827D_HEAD_SET_CONTEXT_DMA_WUT_HANDWE                                  31:0
#define NV827D_HEAD_SET_OFFSET(a,b)                                             (0x00000860 + (a)*0x00000400 + (b)*0x00000004)
#define NV827D_HEAD_SET_OFFSET_OWIGIN                                           31:0
#define NV827D_HEAD_SET_SIZE(a)                                                 (0x00000868 + (a)*0x00000400)
#define NV827D_HEAD_SET_SIZE_WIDTH                                              14:0
#define NV827D_HEAD_SET_SIZE_HEIGHT                                             30:16
#define NV827D_HEAD_SET_STOWAGE(a)                                              (0x0000086C + (a)*0x00000400)
#define NV827D_HEAD_SET_STOWAGE_BWOCK_HEIGHT                                    3:0
#define NV827D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_ONE_GOB                            (0x00000000)
#define NV827D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_TWO_GOBS                           (0x00000001)
#define NV827D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_FOUW_GOBS                          (0x00000002)
#define NV827D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_EIGHT_GOBS                         (0x00000003)
#define NV827D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_SIXTEEN_GOBS                       (0x00000004)
#define NV827D_HEAD_SET_STOWAGE_BWOCK_HEIGHT_THIWTYTWO_GOBS                     (0x00000005)
#define NV827D_HEAD_SET_STOWAGE_PITCH                                           17:8
#define NV827D_HEAD_SET_STOWAGE_MEMOWY_WAYOUT                                   20:20
#define NV827D_HEAD_SET_STOWAGE_MEMOWY_WAYOUT_BWOCKWINEAW                       (0x00000000)
#define NV827D_HEAD_SET_STOWAGE_MEMOWY_WAYOUT_PITCH                             (0x00000001)
#define NV827D_HEAD_SET_PAWAMS(a)                                               (0x00000870 + (a)*0x00000400)
#define NV827D_HEAD_SET_PAWAMS_FOWMAT                                           15:8
#define NV827D_HEAD_SET_PAWAMS_FOWMAT_I8                                        (0x0000001E)
#define NV827D_HEAD_SET_PAWAMS_FOWMAT_VOID16                                    (0x0000001F)
#define NV827D_HEAD_SET_PAWAMS_FOWMAT_VOID32                                    (0x0000002E)
#define NV827D_HEAD_SET_PAWAMS_FOWMAT_WF16_GF16_BF16_AF16                       (0x000000CA)
#define NV827D_HEAD_SET_PAWAMS_FOWMAT_A8W8G8B8                                  (0x000000CF)
#define NV827D_HEAD_SET_PAWAMS_FOWMAT_A2B10G10W10                               (0x000000D1)
#define NV827D_HEAD_SET_PAWAMS_FOWMAT_A8B8G8W8                                  (0x000000D5)
#define NV827D_HEAD_SET_PAWAMS_FOWMAT_W5G6B5                                    (0x000000E8)
#define NV827D_HEAD_SET_PAWAMS_FOWMAT_A1W5G5B5                                  (0x000000E9)
#define NV827D_HEAD_SET_PAWAMS_SUPEW_SAMPWE                                     1:0
#define NV827D_HEAD_SET_PAWAMS_SUPEW_SAMPWE_X1_AA                               (0x00000000)
#define NV827D_HEAD_SET_PAWAMS_SUPEW_SAMPWE_X4_AA                               (0x00000002)
#define NV827D_HEAD_SET_PAWAMS_GAMMA                                            2:2
#define NV827D_HEAD_SET_PAWAMS_GAMMA_WINEAW                                     (0x00000000)
#define NV827D_HEAD_SET_PAWAMS_GAMMA_SWGB                                       (0x00000001)
#define NV827D_HEAD_SET_PAWAMS_WESEWVED0                                        22:16
#define NV827D_HEAD_SET_PAWAMS_WESEWVED1                                        24:24
#define NV827D_HEAD_SET_CONTEXT_DMAS_ISO(a,b)                                   (0x00000874 + (a)*0x00000400 + (b)*0x00000004)
#define NV827D_HEAD_SET_CONTEXT_DMAS_ISO_HANDWE                                 31:0
#define NV827D_HEAD_SET_CONTWOW_CUWSOW(a)                                       (0x00000880 + (a)*0x00000400)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_ENABWE                                   31:31
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_ENABWE_DISABWE                           (0x00000000)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_ENABWE_ENABWE                            (0x00000001)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_FOWMAT                                   25:24
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_FOWMAT_A1W5G5B5                          (0x00000000)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_FOWMAT_A8W8G8B8                          (0x00000001)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_SIZE                                     26:26
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_SIZE_W32_H32                             (0x00000000)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_SIZE_W64_H64                             (0x00000001)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_HOT_SPOT_X                               13:8
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_HOT_SPOT_Y                               21:16
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION                              29:28
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION_AWPHA_BWEND                  (0x00000000)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION_PWEMUWT_AWPHA_BWEND          (0x00000001)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_COMPOSITION_XOW                          (0x00000002)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_SUB_OWNEW                                5:4
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_SUB_OWNEW_NONE                           (0x00000000)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_SUB_OWNEW_SUBHEAD0                       (0x00000001)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_SUB_OWNEW_SUBHEAD1                       (0x00000002)
#define NV827D_HEAD_SET_CONTWOW_CUWSOW_SUB_OWNEW_BOTH                           (0x00000003)
#define NV827D_HEAD_SET_OFFSET_CUWSOW(a)                                        (0x00000884 + (a)*0x00000400)
#define NV827D_HEAD_SET_OFFSET_CUWSOW_OWIGIN                                    31:0
#define NV827D_HEAD_SET_CONTEXT_DMA_CUWSOW(a)                                   (0x0000089C + (a)*0x00000400)
#define NV827D_HEAD_SET_CONTEXT_DMA_CUWSOW_HANDWE                               31:0
#define NV827D_HEAD_SET_VIEWPOWT_POINT_IN(a,b)                                  (0x000008C0 + (a)*0x00000400 + (b)*0x00000004)
#define NV827D_HEAD_SET_VIEWPOWT_POINT_IN_X                                     14:0
#define NV827D_HEAD_SET_VIEWPOWT_POINT_IN_Y                                     30:16
#endif // _cw827d_h
