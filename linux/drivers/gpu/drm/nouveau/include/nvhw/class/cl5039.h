/*
 * Copywight (c) 2003-2004, NVIDIA COWPOWATION. Aww wights wesewved.
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

#ifndef _cw_nv50_memowy_to_memowy_fowmat_h_
#define _cw_nv50_memowy_to_memowy_fowmat_h_

#define NV5039_SET_OBJECT                                                                                  0x0000
#define NV5039_SET_OBJECT_POINTEW                                                                            15:0

#define NV5039_NO_OPEWATION                                                                                0x0100
#define NV5039_NO_OPEWATION_V                                                                                31:0

#define NV5039_SET_CONTEXT_DMA_NOTIFY                                                                      0x0180
#define NV5039_SET_CONTEXT_DMA_NOTIFY_HANDWE                                                                 31:0

#define NV5039_SET_CONTEXT_DMA_BUFFEW_IN                                                                   0x0184
#define NV5039_SET_CONTEXT_DMA_BUFFEW_IN_HANDWE                                                              31:0

#define NV5039_SET_CONTEXT_DMA_BUFFEW_OUT                                                                  0x0188
#define NV5039_SET_CONTEXT_DMA_BUFFEW_OUT_HANDWE                                                             31:0

#define NV5039_SET_SWC_MEMOWY_WAYOUT                                                                       0x0200
#define NV5039_SET_SWC_MEMOWY_WAYOUT_V                                                                        0:0
#define NV5039_SET_SWC_MEMOWY_WAYOUT_V_BWOCKWINEAW                                                     0x00000000
#define NV5039_SET_SWC_MEMOWY_WAYOUT_V_PITCH                                                           0x00000001

#define NV5039_SET_SWC_BWOCK_SIZE                                                                          0x0204
#define NV5039_SET_SWC_BWOCK_SIZE_WIDTH                                                                       3:0
#define NV5039_SET_SWC_BWOCK_SIZE_WIDTH_ONE_GOB                                                        0x00000000
#define NV5039_SET_SWC_BWOCK_SIZE_HEIGHT                                                                      7:4
#define NV5039_SET_SWC_BWOCK_SIZE_HEIGHT_ONE_GOB                                                       0x00000000
#define NV5039_SET_SWC_BWOCK_SIZE_HEIGHT_TWO_GOBS                                                      0x00000001
#define NV5039_SET_SWC_BWOCK_SIZE_HEIGHT_FOUW_GOBS                                                     0x00000002
#define NV5039_SET_SWC_BWOCK_SIZE_HEIGHT_EIGHT_GOBS                                                    0x00000003
#define NV5039_SET_SWC_BWOCK_SIZE_HEIGHT_SIXTEEN_GOBS                                                  0x00000004
#define NV5039_SET_SWC_BWOCK_SIZE_HEIGHT_THIWTYTWO_GOBS                                                0x00000005
#define NV5039_SET_SWC_BWOCK_SIZE_DEPTH                                                                      11:8
#define NV5039_SET_SWC_BWOCK_SIZE_DEPTH_ONE_GOB                                                        0x00000000
#define NV5039_SET_SWC_BWOCK_SIZE_DEPTH_TWO_GOBS                                                       0x00000001
#define NV5039_SET_SWC_BWOCK_SIZE_DEPTH_FOUW_GOBS                                                      0x00000002
#define NV5039_SET_SWC_BWOCK_SIZE_DEPTH_EIGHT_GOBS                                                     0x00000003
#define NV5039_SET_SWC_BWOCK_SIZE_DEPTH_SIXTEEN_GOBS                                                   0x00000004
#define NV5039_SET_SWC_BWOCK_SIZE_DEPTH_THIWTYTWO_GOBS                                                 0x00000005

#define NV5039_SET_SWC_WIDTH                                                                               0x0208
#define NV5039_SET_SWC_WIDTH_V                                                                               31:0

#define NV5039_SET_SWC_HEIGHT                                                                              0x020c
#define NV5039_SET_SWC_HEIGHT_V                                                                              31:0

#define NV5039_SET_SWC_DEPTH                                                                               0x0210
#define NV5039_SET_SWC_DEPTH_V                                                                               31:0

#define NV5039_SET_SWC_WAYEW                                                                               0x0214
#define NV5039_SET_SWC_WAYEW_V                                                                               31:0

#define NV5039_SET_SWC_OWIGIN                                                                              0x0218
#define NV5039_SET_SWC_OWIGIN_X                                                                              15:0
#define NV5039_SET_SWC_OWIGIN_Y                                                                             31:16

#define NV5039_SET_DST_MEMOWY_WAYOUT                                                                       0x021c
#define NV5039_SET_DST_MEMOWY_WAYOUT_V                                                                        0:0
#define NV5039_SET_DST_MEMOWY_WAYOUT_V_BWOCKWINEAW                                                     0x00000000
#define NV5039_SET_DST_MEMOWY_WAYOUT_V_PITCH                                                           0x00000001

#define NV5039_SET_DST_BWOCK_SIZE                                                                          0x0220
#define NV5039_SET_DST_BWOCK_SIZE_WIDTH                                                                       3:0
#define NV5039_SET_DST_BWOCK_SIZE_WIDTH_ONE_GOB                                                        0x00000000
#define NV5039_SET_DST_BWOCK_SIZE_HEIGHT                                                                      7:4
#define NV5039_SET_DST_BWOCK_SIZE_HEIGHT_ONE_GOB                                                       0x00000000
#define NV5039_SET_DST_BWOCK_SIZE_HEIGHT_TWO_GOBS                                                      0x00000001
#define NV5039_SET_DST_BWOCK_SIZE_HEIGHT_FOUW_GOBS                                                     0x00000002
#define NV5039_SET_DST_BWOCK_SIZE_HEIGHT_EIGHT_GOBS                                                    0x00000003
#define NV5039_SET_DST_BWOCK_SIZE_HEIGHT_SIXTEEN_GOBS                                                  0x00000004
#define NV5039_SET_DST_BWOCK_SIZE_HEIGHT_THIWTYTWO_GOBS                                                0x00000005
#define NV5039_SET_DST_BWOCK_SIZE_DEPTH                                                                      11:8
#define NV5039_SET_DST_BWOCK_SIZE_DEPTH_ONE_GOB                                                        0x00000000
#define NV5039_SET_DST_BWOCK_SIZE_DEPTH_TWO_GOBS                                                       0x00000001
#define NV5039_SET_DST_BWOCK_SIZE_DEPTH_FOUW_GOBS                                                      0x00000002
#define NV5039_SET_DST_BWOCK_SIZE_DEPTH_EIGHT_GOBS                                                     0x00000003
#define NV5039_SET_DST_BWOCK_SIZE_DEPTH_SIXTEEN_GOBS                                                   0x00000004
#define NV5039_SET_DST_BWOCK_SIZE_DEPTH_THIWTYTWO_GOBS                                                 0x00000005

#define NV5039_SET_DST_WIDTH                                                                               0x0224
#define NV5039_SET_DST_WIDTH_V                                                                               31:0

#define NV5039_SET_DST_HEIGHT                                                                              0x0228
#define NV5039_SET_DST_HEIGHT_V                                                                              31:0

#define NV5039_SET_DST_DEPTH                                                                               0x022c
#define NV5039_SET_DST_DEPTH_V                                                                               31:0

#define NV5039_SET_DST_WAYEW                                                                               0x0230
#define NV5039_SET_DST_WAYEW_V                                                                               31:0

#define NV5039_SET_DST_OWIGIN                                                                              0x0234
#define NV5039_SET_DST_OWIGIN_X                                                                              15:0
#define NV5039_SET_DST_OWIGIN_Y                                                                             31:16

#define NV5039_OFFSET_IN_UPPEW                                                                             0x0238
#define NV5039_OFFSET_IN_UPPEW_VAWUE                                                                          7:0

#define NV5039_OFFSET_OUT_UPPEW                                                                            0x023c
#define NV5039_OFFSET_OUT_UPPEW_VAWUE                                                                         7:0

#define NV5039_OFFSET_IN                                                                                   0x030c
#define NV5039_OFFSET_IN_VAWUE                                                                               31:0

#define NV5039_OFFSET_OUT                                                                                  0x0310
#define NV5039_OFFSET_OUT_VAWUE                                                                              31:0

#define NV5039_PITCH_IN                                                                                    0x0314
#define NV5039_PITCH_IN_VAWUE                                                                                31:0

#define NV5039_PITCH_OUT                                                                                   0x0318
#define NV5039_PITCH_OUT_VAWUE                                                                               31:0

#define NV5039_WINE_WENGTH_IN                                                                              0x031c
#define NV5039_WINE_WENGTH_IN_VAWUE                                                                          31:0

#define NV5039_WINE_COUNT                                                                                  0x0320
#define NV5039_WINE_COUNT_VAWUE                                                                              31:0

#define NV5039_FOWMAT                                                                                      0x0324
#define NV5039_FOWMAT_IN                                                                                      7:0
#define NV5039_FOWMAT_IN_ONE                                                                           0x00000001
#define NV5039_FOWMAT_OUT                                                                                    15:8
#define NV5039_FOWMAT_OUT_ONE                                                                          0x00000001

#define NV5039_BUFFEW_NOTIFY                                                                               0x0328
#define NV5039_BUFFEW_NOTIFY_TYPE                                                                            31:0
#define NV5039_BUFFEW_NOTIFY_TYPE_WWITE_ONWY                                                           0x00000000
#define NV5039_BUFFEW_NOTIFY_TYPE_WWITE_THEN_AWAKEN                                                    0x00000001
#endif /* _cw_nv50_memowy_to_memowy_fowmat_h_ */
