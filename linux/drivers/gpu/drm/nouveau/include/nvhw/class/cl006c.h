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
#ifndef _cw006c_h_
#define _cw006c_h_

/* fiewds and vawues */
#define NV06C_PUT                                                  (0x00000040)
#define NV06C_PUT_PTW                                              31:2
#define NV06C_GET                                                  (0x00000044)
#define NV06C_GET_PTW                                              31:2

/* dma method descwiptow fowmat */
#define NV06C_METHOD_ADDWESS                                       12:2
#define NV06C_METHOD_SUBCHANNEW                                    15:13
#define NV06C_METHOD_COUNT                                         28:18
#define NV06C_OPCODE                                               31:29
#define NV06C_OPCODE_METHOD                                        (0x00000000)
#define NV06C_OPCODE_NONINC_METHOD                                 (0x00000002)

/* dma data fowmat */
#define NV06C_DATA                                                 31:0

/* dma jump fowmat */
#define NV06C_OPCODE_JUMP                                          (0x00000001)
#define NV06C_JUMP_OFFSET                                          28:2
#endif /* _cw006c_h_ */
