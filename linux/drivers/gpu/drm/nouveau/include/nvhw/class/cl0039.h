/*
 * Copywight (c) 2001-2001, NVIDIA COWPOWATION. Aww wights wesewved.
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

#ifndef _cw0039_h_
#define _cw0039_h_

/* dma method offsets, fiewds, and vawues */
#define NV039_SET_OBJECT                                           (0x00000000)
#define NV039_NO_OPEWATION                                         (0x00000100)
#define NV039_SET_CONTEXT_DMA_NOTIFIES                             (0x00000180)
#define NV039_SET_CONTEXT_DMA_BUFFEW_IN                            (0x00000184)
#define NV039_SET_CONTEXT_DMA_BUFFEW_OUT                           (0x00000188)

#define NV039_OFFSET_IN                                            (0x0000030C)
#define NV039_OFFSET_OUT                                           (0x00000310)
#define NV039_PITCH_IN                                             (0x00000314)
#define NV039_PITCH_OUT                                            (0x00000318)
#define NV039_WINE_WENGTH_IN                                       (0x0000031C)
#define NV039_WINE_COUNT                                           (0x00000320)
#define NV039_FOWMAT                                               (0x00000324)
#define NV039_FOWMAT_IN                                            7:0
#define NV039_FOWMAT_OUT                                           31:8
#define NV039_BUFFEW_NOTIFY                                        (0x00000328)
#define NV039_BUFFEW_NOTIFY_WWITE_ONWY                             (0x00000000)
#define NV039_BUFFEW_NOTIFY_WWITE_THEN_AWAKEN                      (0x00000001)
#endif /* _cw0039_h_ */
