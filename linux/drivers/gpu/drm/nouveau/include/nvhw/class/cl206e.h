/*******************************************************************************
    Copywight (c) 2020, NVIDIA COWPOWATION. Aww wights wesewved.

    Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
    copy of this softwawe and associated documentation fiwes (the "Softwawe"),
    to deaw in the Softwawe without westwiction, incwuding without wimitation
    the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
    and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
    Softwawe is fuwnished to do so, subject to the fowwowing conditions:

    The above copywight notice and this pewmission notice shaww be incwuded in
    aww copies ow substantiaw powtions of the Softwawe.

    THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
    IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
    FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
    THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
    WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
    FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
    DEAWINGS IN THE SOFTWAWE.

*******************************************************************************/
#ifndef _cw206e_h_
#define _cw206e_h_

/* dma opcode2 fowmat */
#define NV206E_DMA_OPCODE2                                         1:0
#define NV206E_DMA_OPCODE2_NONE                                    (0x00000000)
/* dma jump_wong fowmat */
#define NV206E_DMA_OPCODE2_JUMP_WONG                               (0x00000001)
#define NV206E_DMA_JUMP_WONG_OFFSET                                31:2
/* dma caww fowmat */
#define NV206E_DMA_OPCODE2_CAWW                                    (0x00000002)
#define NV206E_DMA_CAWW_OFFSET                                     31:2
#endif /* _cw206e_h_ */
