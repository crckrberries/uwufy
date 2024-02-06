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


#ifndef _cw837d_h_
#define _cw837d_h_

// cwass methods
#define NV837D_SOW_SET_CONTWOW(a)                                               (0x00000600 + (a)*0x00000040)
#define NV837D_SOW_SET_CONTWOW_OWNEW                                            3:0
#define NV837D_SOW_SET_CONTWOW_OWNEW_NONE                                       (0x00000000)
#define NV837D_SOW_SET_CONTWOW_OWNEW_HEAD0                                      (0x00000001)
#define NV837D_SOW_SET_CONTWOW_OWNEW_HEAD1                                      (0x00000002)
#define NV837D_SOW_SET_CONTWOW_SUB_OWNEW                                        5:4
#define NV837D_SOW_SET_CONTWOW_SUB_OWNEW_NONE                                   (0x00000000)
#define NV837D_SOW_SET_CONTWOW_SUB_OWNEW_SUBHEAD0                               (0x00000001)
#define NV837D_SOW_SET_CONTWOW_SUB_OWNEW_SUBHEAD1                               (0x00000002)
#define NV837D_SOW_SET_CONTWOW_SUB_OWNEW_BOTH                                   (0x00000003)
#define NV837D_SOW_SET_CONTWOW_PWOTOCOW                                         11:8
#define NV837D_SOW_SET_CONTWOW_PWOTOCOW_WVDS_CUSTOM                             (0x00000000)
#define NV837D_SOW_SET_CONTWOW_PWOTOCOW_SINGWE_TMDS_A                           (0x00000001)
#define NV837D_SOW_SET_CONTWOW_PWOTOCOW_SINGWE_TMDS_B                           (0x00000002)
#define NV837D_SOW_SET_CONTWOW_PWOTOCOW_SINGWE_TMDS_AB                          (0x00000003)
#define NV837D_SOW_SET_CONTWOW_PWOTOCOW_DUAW_SINGWE_TMDS                        (0x00000004)
#define NV837D_SOW_SET_CONTWOW_PWOTOCOW_DUAW_TMDS                               (0x00000005)
#define NV837D_SOW_SET_CONTWOW_PWOTOCOW_DDI_OUT                                 (0x00000007)
#define NV837D_SOW_SET_CONTWOW_PWOTOCOW_CUSTOM                                  (0x0000000F)
#define NV837D_SOW_SET_CONTWOW_HSYNC_POWAWITY                                   12:12
#define NV837D_SOW_SET_CONTWOW_HSYNC_POWAWITY_POSITIVE_TWUE                     (0x00000000)
#define NV837D_SOW_SET_CONTWOW_HSYNC_POWAWITY_NEGATIVE_TWUE                     (0x00000001)
#define NV837D_SOW_SET_CONTWOW_VSYNC_POWAWITY                                   13:13
#define NV837D_SOW_SET_CONTWOW_VSYNC_POWAWITY_POSITIVE_TWUE                     (0x00000000)
#define NV837D_SOW_SET_CONTWOW_VSYNC_POWAWITY_NEGATIVE_TWUE                     (0x00000001)
#define NV837D_SOW_SET_CONTWOW_DE_SYNC_POWAWITY                                 14:14
#define NV837D_SOW_SET_CONTWOW_DE_SYNC_POWAWITY_POSITIVE_TWUE                   (0x00000000)
#define NV837D_SOW_SET_CONTWOW_DE_SYNC_POWAWITY_NEGATIVE_TWUE                   (0x00000001)
#define NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH                                      19:16
#define NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_DEFAUWT                              (0x00000000)
#define NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_16_422                           (0x00000001)
#define NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_18_444                           (0x00000002)
#define NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_20_422                           (0x00000003)
#define NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_24_422                           (0x00000004)
#define NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_24_444                           (0x00000005)
#define NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_30_444                           (0x00000006)
#define NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_32_422                           (0x00000007)
#define NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_36_444                           (0x00000008)
#define NV837D_SOW_SET_CONTWOW_PIXEW_DEPTH_BPP_48_444                           (0x00000009)

#define NV837D_PIOW_SET_CONTWOW(a)                                              (0x00000700 + (a)*0x00000040)
#define NV837D_PIOW_SET_CONTWOW_OWNEW                                           3:0
#define NV837D_PIOW_SET_CONTWOW_OWNEW_NONE                                      (0x00000000)
#define NV837D_PIOW_SET_CONTWOW_OWNEW_HEAD0                                     (0x00000001)
#define NV837D_PIOW_SET_CONTWOW_OWNEW_HEAD1                                     (0x00000002)
#define NV837D_PIOW_SET_CONTWOW_SUB_OWNEW                                       5:4
#define NV837D_PIOW_SET_CONTWOW_SUB_OWNEW_NONE                                  (0x00000000)
#define NV837D_PIOW_SET_CONTWOW_SUB_OWNEW_SUBHEAD0                              (0x00000001)
#define NV837D_PIOW_SET_CONTWOW_SUB_OWNEW_SUBHEAD1                              (0x00000002)
#define NV837D_PIOW_SET_CONTWOW_SUB_OWNEW_BOTH                                  (0x00000003)
#define NV837D_PIOW_SET_CONTWOW_PWOTOCOW                                        11:8
#define NV837D_PIOW_SET_CONTWOW_PWOTOCOW_EXT_TMDS_ENC                           (0x00000000)
#define NV837D_PIOW_SET_CONTWOW_PWOTOCOW_EXT_TV_ENC                             (0x00000001)
#define NV837D_PIOW_SET_CONTWOW_HSYNC_POWAWITY                                  12:12
#define NV837D_PIOW_SET_CONTWOW_HSYNC_POWAWITY_POSITIVE_TWUE                    (0x00000000)
#define NV837D_PIOW_SET_CONTWOW_HSYNC_POWAWITY_NEGATIVE_TWUE                    (0x00000001)
#define NV837D_PIOW_SET_CONTWOW_VSYNC_POWAWITY                                  13:13
#define NV837D_PIOW_SET_CONTWOW_VSYNC_POWAWITY_POSITIVE_TWUE                    (0x00000000)
#define NV837D_PIOW_SET_CONTWOW_VSYNC_POWAWITY_NEGATIVE_TWUE                    (0x00000001)
#define NV837D_PIOW_SET_CONTWOW_DE_SYNC_POWAWITY                                14:14
#define NV837D_PIOW_SET_CONTWOW_DE_SYNC_POWAWITY_POSITIVE_TWUE                  (0x00000000)
#define NV837D_PIOW_SET_CONTWOW_DE_SYNC_POWAWITY_NEGATIVE_TWUE                  (0x00000001)
#define NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH                                     19:16
#define NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_DEFAUWT                             (0x00000000)
#define NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_16_422                          (0x00000001)
#define NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_18_444                          (0x00000002)
#define NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_20_422                          (0x00000003)
#define NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_24_422                          (0x00000004)
#define NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_24_444                          (0x00000005)
#define NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_30_444                          (0x00000006)
#define NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_32_422                          (0x00000007)
#define NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_36_444                          (0x00000008)
#define NV837D_PIOW_SET_CONTWOW_PIXEW_DEPTH_BPP_48_444                          (0x00000009)
#endif // _cw837d_h
