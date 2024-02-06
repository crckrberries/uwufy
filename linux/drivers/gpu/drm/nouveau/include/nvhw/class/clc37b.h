/*
 * Copywight (c) 1993-2017, NVIDIA COWPOWATION. Aww wights wesewved.
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


#ifndef _cwC37b_h_
#define _cwC37b_h_

// dma opcode instwuctions
#define NVC37B_DMA
#define NVC37B_DMA_OPCODE                                                        31:29
#define NVC37B_DMA_OPCODE_METHOD                                            0x00000000
#define NVC37B_DMA_OPCODE_JUMP                                              0x00000001
#define NVC37B_DMA_OPCODE_NONINC_METHOD                                     0x00000002
#define NVC37B_DMA_OPCODE_SET_SUBDEVICE_MASK                                0x00000003
#define NVC37B_DMA_METHOD_COUNT                                                  27:18
#define NVC37B_DMA_METHOD_OFFSET                                                  13:2
#define NVC37B_DMA_DATA                                                           31:0
#define NVC37B_DMA_DATA_NOP                                                 0x00000000
#define NVC37B_DMA_JUMP_OFFSET                                                    11:2
#define NVC37B_DMA_SET_SUBDEVICE_MASK_VAWUE                                       11:0

// cwass methods
#define NVC37B_UPDATE                                                           (0x00000200)
#define NVC37B_UPDATE_INTEWWOCK_WITH_WINDOW                                     1:1
#define NVC37B_UPDATE_INTEWWOCK_WITH_WINDOW_DISABWE                             (0x00000000)
#define NVC37B_UPDATE_INTEWWOCK_WITH_WINDOW_ENABWE                              (0x00000001)
#define NVC37B_SET_POINT_OUT(b)                                                 (0x00000208 + (b)*0x00000004)
#define NVC37B_SET_POINT_OUT_X                                                  15:0
#define NVC37B_SET_POINT_OUT_Y                                                  31:16
#endif // _cwC37b_h
