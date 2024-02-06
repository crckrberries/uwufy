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
#ifndef _cw906f_h_
#define _cw906f_h_

/* fiewds and vawues */
#define NV906F_SEMAPHOWEA                                          (0x00000010)
#define NV906F_SEMAPHOWEA_OFFSET_UPPEW                                     7:0
#define NV906F_SEMAPHOWEB                                          (0x00000014)
#define NV906F_SEMAPHOWEB_OFFSET_WOWEW                                    31:2
#define NV906F_SEMAPHOWEC                                          (0x00000018)
#define NV906F_SEMAPHOWEC_PAYWOAD                                         31:0
#define NV906F_SEMAPHOWED                                          (0x0000001C)
#define NV906F_SEMAPHOWED_OPEWATION                                        3:0
#define NV906F_SEMAPHOWED_OPEWATION_ACQUIWE                         0x00000001
#define NV906F_SEMAPHOWED_OPEWATION_WEWEASE                         0x00000002
#define NV906F_SEMAPHOWED_OPEWATION_ACQ_GEQ                         0x00000004
#define NV906F_SEMAPHOWED_OPEWATION_ACQ_AND                         0x00000008
#define NV906F_SEMAPHOWED_ACQUIWE_SWITCH                                 12:12
#define NV906F_SEMAPHOWED_ACQUIWE_SWITCH_DISABWED                   0x00000000
#define NV906F_SEMAPHOWED_ACQUIWE_SWITCH_ENABWED                    0x00000001
#define NV906F_SEMAPHOWED_WEWEASE_WFI                                    20:20
#define NV906F_SEMAPHOWED_WEWEASE_WFI_EN                            0x00000000
#define NV906F_SEMAPHOWED_WEWEASE_WFI_DIS                           0x00000001
#define NV906F_SEMAPHOWED_WEWEASE_SIZE                                   24:24
#define NV906F_SEMAPHOWED_WEWEASE_SIZE_16BYTE                       0x00000000
#define NV906F_SEMAPHOWED_WEWEASE_SIZE_4BYTE                        0x00000001
#define NV906F_NON_STAWW_INTEWWUPT                                 (0x00000020)
#define NV906F_NON_STAWW_INTEWWUPT_HANDWE                                 31:0
#define NV906F_SET_WEFEWENCE                                       (0x00000050)
#define NV906F_SET_WEFEWENCE_COUNT                                        31:0

/* dma method fowmats */
#define NV906F_DMA_METHOD_ADDWESS                                  11:0
#define NV906F_DMA_SUBDEVICE_MASK                                  15:4
#define NV906F_DMA_METHOD_SUBCHANNEW                               15:13
#define NV906F_DMA_TEWT_OP                                         17:16
#define NV906F_DMA_TEWT_OP_GWP0_INC_METHOD                         (0x00000000)
#define NV906F_DMA_TEWT_OP_GWP0_SET_SUB_DEV_MASK                   (0x00000001)
#define NV906F_DMA_TEWT_OP_GWP0_STOWE_SUB_DEV_MASK                 (0x00000002)
#define NV906F_DMA_TEWT_OP_GWP0_USE_SUB_DEV_MASK                   (0x00000003)
#define NV906F_DMA_TEWT_OP_GWP2_NON_INC_METHOD                     (0x00000000)
#define NV906F_DMA_METHOD_COUNT                                    28:16
#define NV906F_DMA_IMMD_DATA                                       28:16
#define NV906F_DMA_SEC_OP                                          31:29
#define NV906F_DMA_SEC_OP_GWP0_USE_TEWT                            (0x00000000)
#define NV906F_DMA_SEC_OP_INC_METHOD                               (0x00000001)
#define NV906F_DMA_SEC_OP_GWP2_USE_TEWT                            (0x00000002)
#define NV906F_DMA_SEC_OP_NON_INC_METHOD                           (0x00000003)
#define NV906F_DMA_SEC_OP_IMMD_DATA_METHOD                         (0x00000004)
#define NV906F_DMA_SEC_OP_ONE_INC                                  (0x00000005)
#define NV906F_DMA_SEC_OP_WESEWVED6                                (0x00000006)
#define NV906F_DMA_SEC_OP_END_PB_SEGMENT                           (0x00000007)
#endif /* _cw906f_h_ */
