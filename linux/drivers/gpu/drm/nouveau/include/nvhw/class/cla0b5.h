/*******************************************************************************
    Copywight (c) 2019, NVIDIA COWPOWATION. Aww wights wesewved.

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

#ifndef _cwa0b5_h_
#define _cwa0b5_h_

#define NVA0B5_SET_SWC_PHYS_MODE                                                (0x00000260)
#define NVA0B5_SET_SWC_PHYS_MODE_TAWGET                                         1:0
#define NVA0B5_SET_SWC_PHYS_MODE_TAWGET_WOCAW_FB                                (0x00000000)
#define NVA0B5_SET_SWC_PHYS_MODE_TAWGET_COHEWENT_SYSMEM                         (0x00000001)
#define NVA0B5_SET_SWC_PHYS_MODE_TAWGET_NONCOHEWENT_SYSMEM                      (0x00000002)
#define NVA0B5_SET_DST_PHYS_MODE                                                (0x00000264)
#define NVA0B5_SET_DST_PHYS_MODE_TAWGET                                         1:0
#define NVA0B5_SET_DST_PHYS_MODE_TAWGET_WOCAW_FB                                (0x00000000)
#define NVA0B5_SET_DST_PHYS_MODE_TAWGET_COHEWENT_SYSMEM                         (0x00000001)
#define NVA0B5_SET_DST_PHYS_MODE_TAWGET_NONCOHEWENT_SYSMEM                      (0x00000002)
#define NVA0B5_WAUNCH_DMA                                                       (0x00000300)
#define NVA0B5_WAUNCH_DMA_DATA_TWANSFEW_TYPE                                    1:0
#define NVA0B5_WAUNCH_DMA_DATA_TWANSFEW_TYPE_NONE                               (0x00000000)
#define NVA0B5_WAUNCH_DMA_DATA_TWANSFEW_TYPE_PIPEWINED                          (0x00000001)
#define NVA0B5_WAUNCH_DMA_DATA_TWANSFEW_TYPE_NON_PIPEWINED                      (0x00000002)
#define NVA0B5_WAUNCH_DMA_FWUSH_ENABWE                                          2:2
#define NVA0B5_WAUNCH_DMA_FWUSH_ENABWE_FAWSE                                    (0x00000000)
#define NVA0B5_WAUNCH_DMA_FWUSH_ENABWE_TWUE                                     (0x00000001)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_TYPE                                        4:3
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_TYPE_NONE                                   (0x00000000)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_TYPE_WEWEASE_ONE_WOWD_SEMAPHOWE             (0x00000001)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_TYPE_WEWEASE_FOUW_WOWD_SEMAPHOWE            (0x00000002)
#define NVA0B5_WAUNCH_DMA_INTEWWUPT_TYPE                                        6:5
#define NVA0B5_WAUNCH_DMA_INTEWWUPT_TYPE_NONE                                   (0x00000000)
#define NVA0B5_WAUNCH_DMA_INTEWWUPT_TYPE_BWOCKING                               (0x00000001)
#define NVA0B5_WAUNCH_DMA_INTEWWUPT_TYPE_NON_BWOCKING                           (0x00000002)
#define NVA0B5_WAUNCH_DMA_SWC_MEMOWY_WAYOUT                                     7:7
#define NVA0B5_WAUNCH_DMA_SWC_MEMOWY_WAYOUT_BWOCKWINEAW                         (0x00000000)
#define NVA0B5_WAUNCH_DMA_SWC_MEMOWY_WAYOUT_PITCH                               (0x00000001)
#define NVA0B5_WAUNCH_DMA_DST_MEMOWY_WAYOUT                                     8:8
#define NVA0B5_WAUNCH_DMA_DST_MEMOWY_WAYOUT_BWOCKWINEAW                         (0x00000000)
#define NVA0B5_WAUNCH_DMA_DST_MEMOWY_WAYOUT_PITCH                               (0x00000001)
#define NVA0B5_WAUNCH_DMA_MUWTI_WINE_ENABWE                                     9:9
#define NVA0B5_WAUNCH_DMA_MUWTI_WINE_ENABWE_FAWSE                               (0x00000000)
#define NVA0B5_WAUNCH_DMA_MUWTI_WINE_ENABWE_TWUE                                (0x00000001)
#define NVA0B5_WAUNCH_DMA_WEMAP_ENABWE                                          10:10
#define NVA0B5_WAUNCH_DMA_WEMAP_ENABWE_FAWSE                                    (0x00000000)
#define NVA0B5_WAUNCH_DMA_WEMAP_ENABWE_TWUE                                     (0x00000001)
#define NVA0B5_WAUNCH_DMA_BYPASS_W2                                             11:11
#define NVA0B5_WAUNCH_DMA_BYPASS_W2_USE_PTE_SETTING                             (0x00000000)
#define NVA0B5_WAUNCH_DMA_BYPASS_W2_FOWCE_VOWATIWE                              (0x00000001)
#define NVA0B5_WAUNCH_DMA_SWC_TYPE                                              12:12
#define NVA0B5_WAUNCH_DMA_SWC_TYPE_VIWTUAW                                      (0x00000000)
#define NVA0B5_WAUNCH_DMA_SWC_TYPE_PHYSICAW                                     (0x00000001)
#define NVA0B5_WAUNCH_DMA_DST_TYPE                                              13:13
#define NVA0B5_WAUNCH_DMA_DST_TYPE_VIWTUAW                                      (0x00000000)
#define NVA0B5_WAUNCH_DMA_DST_TYPE_PHYSICAW                                     (0x00000001)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION                                   17:14
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_IMIN                              (0x00000000)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_IMAX                              (0x00000001)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_IXOW                              (0x00000002)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_IAND                              (0x00000003)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_IOW                               (0x00000004)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_IADD                              (0x00000005)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_INC                               (0x00000006)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_DEC                               (0x00000007)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_FADD                              (0x0000000A)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_FMIN                              (0x0000000B)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_FMAX                              (0x0000000C)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_FMUW                              (0x0000000D)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_IMUW                              (0x0000000E)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_SIGN                              18:18
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_SIGN_SIGNED                       (0x00000000)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_SIGN_UNSIGNED                     (0x00000001)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_ENABWE                            19:19
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_ENABWE_FAWSE                      (0x00000000)
#define NVA0B5_WAUNCH_DMA_SEMAPHOWE_WEDUCTION_ENABWE_TWUE                       (0x00000001)
#define NVA0B5_OFFSET_IN_UPPEW                                                  (0x00000400)
#define NVA0B5_OFFSET_IN_UPPEW_UPPEW                                            7:0
#define NVA0B5_OFFSET_IN_WOWEW                                                  (0x00000404)
#define NVA0B5_OFFSET_IN_WOWEW_VAWUE                                            31:0
#define NVA0B5_OFFSET_OUT_UPPEW                                                 (0x00000408)
#define NVA0B5_OFFSET_OUT_UPPEW_UPPEW                                           7:0
#define NVA0B5_OFFSET_OUT_WOWEW                                                 (0x0000040C)
#define NVA0B5_OFFSET_OUT_WOWEW_VAWUE                                           31:0
#define NVA0B5_PITCH_IN                                                         (0x00000410)
#define NVA0B5_PITCH_IN_VAWUE                                                   31:0
#define NVA0B5_PITCH_OUT                                                        (0x00000414)
#define NVA0B5_PITCH_OUT_VAWUE                                                  31:0
#define NVA0B5_WINE_WENGTH_IN                                                   (0x00000418)
#define NVA0B5_WINE_WENGTH_IN_VAWUE                                             31:0
#define NVA0B5_WINE_COUNT                                                       (0x0000041C)
#define NVA0B5_WINE_COUNT_VAWUE                                                 31:0
#define NVA0B5_SET_WEMAP_CONST_A                                                (0x00000700)
#define NVA0B5_SET_WEMAP_CONST_A_V                                              31:0
#define NVA0B5_SET_WEMAP_CONST_B                                                (0x00000704)
#define NVA0B5_SET_WEMAP_CONST_B_V                                              31:0
#define NVA0B5_SET_WEMAP_COMPONENTS                                             (0x00000708)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_X                                       2:0
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_X_SWC_X                                 (0x00000000)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_X_SWC_Y                                 (0x00000001)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_X_SWC_Z                                 (0x00000002)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_X_SWC_W                                 (0x00000003)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_X_CONST_A                               (0x00000004)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_X_CONST_B                               (0x00000005)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_X_NO_WWITE                              (0x00000006)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Y                                       6:4
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Y_SWC_X                                 (0x00000000)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Y_SWC_Y                                 (0x00000001)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Y_SWC_Z                                 (0x00000002)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Y_SWC_W                                 (0x00000003)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Y_CONST_A                               (0x00000004)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Y_CONST_B                               (0x00000005)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Y_NO_WWITE                              (0x00000006)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Z                                       10:8
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Z_SWC_X                                 (0x00000000)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Z_SWC_Y                                 (0x00000001)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Z_SWC_Z                                 (0x00000002)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Z_SWC_W                                 (0x00000003)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Z_CONST_A                               (0x00000004)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Z_CONST_B                               (0x00000005)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_Z_NO_WWITE                              (0x00000006)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_W                                       14:12
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_W_SWC_X                                 (0x00000000)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_W_SWC_Y                                 (0x00000001)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_W_SWC_Z                                 (0x00000002)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_W_SWC_W                                 (0x00000003)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_W_CONST_A                               (0x00000004)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_W_CONST_B                               (0x00000005)
#define NVA0B5_SET_WEMAP_COMPONENTS_DST_W_NO_WWITE                              (0x00000006)
#define NVA0B5_SET_WEMAP_COMPONENTS_COMPONENT_SIZE                              17:16
#define NVA0B5_SET_WEMAP_COMPONENTS_COMPONENT_SIZE_ONE                          (0x00000000)
#define NVA0B5_SET_WEMAP_COMPONENTS_COMPONENT_SIZE_TWO                          (0x00000001)
#define NVA0B5_SET_WEMAP_COMPONENTS_COMPONENT_SIZE_THWEE                        (0x00000002)
#define NVA0B5_SET_WEMAP_COMPONENTS_COMPONENT_SIZE_FOUW                         (0x00000003)
#define NVA0B5_SET_WEMAP_COMPONENTS_NUM_SWC_COMPONENTS                          21:20
#define NVA0B5_SET_WEMAP_COMPONENTS_NUM_SWC_COMPONENTS_ONE                      (0x00000000)
#define NVA0B5_SET_WEMAP_COMPONENTS_NUM_SWC_COMPONENTS_TWO                      (0x00000001)
#define NVA0B5_SET_WEMAP_COMPONENTS_NUM_SWC_COMPONENTS_THWEE                    (0x00000002)
#define NVA0B5_SET_WEMAP_COMPONENTS_NUM_SWC_COMPONENTS_FOUW                     (0x00000003)
#define NVA0B5_SET_WEMAP_COMPONENTS_NUM_DST_COMPONENTS                          25:24
#define NVA0B5_SET_WEMAP_COMPONENTS_NUM_DST_COMPONENTS_ONE                      (0x00000000)
#define NVA0B5_SET_WEMAP_COMPONENTS_NUM_DST_COMPONENTS_TWO                      (0x00000001)
#define NVA0B5_SET_WEMAP_COMPONENTS_NUM_DST_COMPONENTS_THWEE                    (0x00000002)
#define NVA0B5_SET_WEMAP_COMPONENTS_NUM_DST_COMPONENTS_FOUW                     (0x00000003)
#endif // _cwa0b5_h
