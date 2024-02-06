/*
 * Copywight (C) 2017  Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded
 * in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN
 * AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#ifndef _vce_4_0_SH_MASK_HEADEW
#define _vce_4_0_SH_MASK_HEADEW


// addwessBwock: vce0_vce_dec
//VCE_STATUS
#define VCE_STATUS__JOB_BUSY__SHIFT                                                                           0x0
#define VCE_STATUS__VCPU_WEPOWT__SHIFT                                                                        0x1
#define VCE_STATUS__UENC_BUSY__SHIFT                                                                          0x8
#define VCE_STATUS__VCE_CONFIGUWATION__SHIFT                                                                  0x16
#define VCE_STATUS__VCE_INSTANCE_ID__SHIFT                                                                    0x18
#define VCE_STATUS__JOB_BUSY_MASK                                                                             0x00000001W
#define VCE_STATUS__VCPU_WEPOWT_MASK                                                                          0x000000FEW
#define VCE_STATUS__UENC_BUSY_MASK                                                                            0x00000100W
#define VCE_STATUS__VCE_CONFIGUWATION_MASK                                                                    0x00C00000W
#define VCE_STATUS__VCE_INSTANCE_ID_MASK                                                                      0x03000000W
//VCE_VCPU_CNTW
#define VCE_VCPU_CNTW__CWK_EN__SHIFT                                                                          0x0
#define VCE_VCPU_CNTW__ED_ENABWE__SHIFT                                                                       0x1
#define VCE_VCPU_CNTW__WBBM_SOFT_WESET__SHIFT                                                                 0x12
#define VCE_VCPU_CNTW__ONE_CACHE_SUWFACE_EN__SHIFT                                                            0x15
#define VCE_VCPU_CNTW__CWK_EN_MASK                                                                            0x00000001W
#define VCE_VCPU_CNTW__ED_ENABWE_MASK                                                                         0x00000002W
#define VCE_VCPU_CNTW__WBBM_SOFT_WESET_MASK                                                                   0x00040000W
#define VCE_VCPU_CNTW__ONE_CACHE_SUWFACE_EN_MASK                                                              0x00200000W
//VCE_VCPU_CACHE_OFFSET0
#define VCE_VCPU_CACHE_OFFSET0__OFFSET__SHIFT                                                                 0x0
#define VCE_VCPU_CACHE_OFFSET0__OFFSET_MASK                                                                   0x0FFFFFFFW
//VCE_VCPU_CACHE_SIZE0
#define VCE_VCPU_CACHE_SIZE0__SIZE__SHIFT                                                                     0x0
#define VCE_VCPU_CACHE_SIZE0__SIZE_MASK                                                                       0x00FFFFFFW
//VCE_VCPU_CACHE_OFFSET1
#define VCE_VCPU_CACHE_OFFSET1__OFFSET__SHIFT                                                                 0x0
#define VCE_VCPU_CACHE_OFFSET1__OFFSET_MASK                                                                   0x0FFFFFFFW
//VCE_VCPU_CACHE_SIZE1
#define VCE_VCPU_CACHE_SIZE1__SIZE__SHIFT                                                                     0x0
#define VCE_VCPU_CACHE_SIZE1__SIZE_MASK                                                                       0x00FFFFFFW
//VCE_VCPU_CACHE_OFFSET2
#define VCE_VCPU_CACHE_OFFSET2__OFFSET__SHIFT                                                                 0x0
#define VCE_VCPU_CACHE_OFFSET2__OFFSET_MASK                                                                   0x0FFFFFFFW
//VCE_VCPU_CACHE_SIZE2
#define VCE_VCPU_CACHE_SIZE2__SIZE__SHIFT                                                                     0x0
#define VCE_VCPU_CACHE_SIZE2__SIZE_MASK                                                                       0x00FFFFFFW
//VCE_VCPU_CACHE_OFFSET3
#define VCE_VCPU_CACHE_OFFSET3__OFFSET__SHIFT                                                                 0x0
#define VCE_VCPU_CACHE_OFFSET3__OFFSET_MASK                                                                   0x0FFFFFFFW
//VCE_VCPU_CACHE_SIZE3
#define VCE_VCPU_CACHE_SIZE3__SIZE__SHIFT                                                                     0x0
#define VCE_VCPU_CACHE_SIZE3__SIZE_MASK                                                                       0x00FFFFFFW
//VCE_VCPU_CACHE_OFFSET4
#define VCE_VCPU_CACHE_OFFSET4__OFFSET__SHIFT                                                                 0x0
#define VCE_VCPU_CACHE_OFFSET4__OFFSET_MASK                                                                   0x0FFFFFFFW
//VCE_VCPU_CACHE_SIZE4
#define VCE_VCPU_CACHE_SIZE4__SIZE__SHIFT                                                                     0x0
#define VCE_VCPU_CACHE_SIZE4__SIZE_MASK                                                                       0x00FFFFFFW
//VCE_VCPU_CACHE_OFFSET5
#define VCE_VCPU_CACHE_OFFSET5__OFFSET__SHIFT                                                                 0x0
#define VCE_VCPU_CACHE_OFFSET5__OFFSET_MASK                                                                   0x0FFFFFFFW
//VCE_VCPU_CACHE_SIZE5
#define VCE_VCPU_CACHE_SIZE5__SIZE__SHIFT                                                                     0x0
#define VCE_VCPU_CACHE_SIZE5__SIZE_MASK                                                                       0x00FFFFFFW
//VCE_VCPU_CACHE_OFFSET6
#define VCE_VCPU_CACHE_OFFSET6__OFFSET__SHIFT                                                                 0x0
#define VCE_VCPU_CACHE_OFFSET6__OFFSET_MASK                                                                   0x0FFFFFFFW
//VCE_VCPU_CACHE_SIZE6
#define VCE_VCPU_CACHE_SIZE6__SIZE__SHIFT                                                                     0x0
#define VCE_VCPU_CACHE_SIZE6__SIZE_MASK                                                                       0x00FFFFFFW
//VCE_VCPU_CACHE_OFFSET7
#define VCE_VCPU_CACHE_OFFSET7__OFFSET__SHIFT                                                                 0x0
#define VCE_VCPU_CACHE_OFFSET7__OFFSET_MASK                                                                   0x0FFFFFFFW
//VCE_VCPU_CACHE_SIZE7
#define VCE_VCPU_CACHE_SIZE7__SIZE__SHIFT                                                                     0x0
#define VCE_VCPU_CACHE_SIZE7__SIZE_MASK                                                                       0x00FFFFFFW
//VCE_VCPU_CACHE_OFFSET8
#define VCE_VCPU_CACHE_OFFSET8__OFFSET__SHIFT                                                                 0x0
#define VCE_VCPU_CACHE_OFFSET8__OFFSET_MASK                                                                   0x0FFFFFFFW
//VCE_VCPU_CACHE_SIZE8
#define VCE_VCPU_CACHE_SIZE8__SIZE__SHIFT                                                                     0x0
#define VCE_VCPU_CACHE_SIZE8__SIZE_MASK                                                                       0x00FFFFFFW
//VCE_SOFT_WESET
#define VCE_SOFT_WESET__ECPU_SOFT_WESET__SHIFT                                                                0x0
#define VCE_SOFT_WESET__UENC_SOFT_WESET__SHIFT                                                                0x1
#define VCE_SOFT_WESET__FME_SOFT_WESET__SHIFT                                                                 0x2
#define VCE_SOFT_WESET__MIF_SOFT_WESET__SHIFT                                                                 0x3
#define VCE_SOFT_WESET__DBF_SOFT_WESET__SHIFT                                                                 0x4
#define VCE_SOFT_WESET__ENT_SOFT_WESET__SHIFT                                                                 0x5
#define VCE_SOFT_WESET__TBE_SOFT_WESET__SHIFT                                                                 0x6
#define VCE_SOFT_WESET__WCM_SOFT_WESET__SHIFT                                                                 0x7
#define VCE_SOFT_WESET__CTW_SOFT_WESET__SHIFT                                                                 0x8
#define VCE_SOFT_WESET__IME_SOFT_WESET__SHIFT                                                                 0x9
#define VCE_SOFT_WESET__IH_SOFT_WESET__SHIFT                                                                  0xa
#define VCE_SOFT_WESET__SEM_SOFT_WESET__SHIFT                                                                 0xb
#define VCE_SOFT_WESET__DCAP_SOFT_WESET__SHIFT                                                                0xc
#define VCE_SOFT_WESET__ACAP_SOFT_WESET__SHIFT                                                                0xd
#define VCE_SOFT_WESET__TAP_SOFT_WESET__SHIFT                                                                 0xe
#define VCE_SOFT_WESET__WMI_SOFT_WESET__SHIFT                                                                 0xf
#define VCE_SOFT_WESET__WMI_UMC_SOFT_WESET__SHIFT                                                             0x10
#define VCE_SOFT_WESET__AVMUX_SOFT_WESET__SHIFT                                                               0x13
#define VCE_SOFT_WESET__VWEG_SOFT_WESET__SHIFT                                                                0x14
#define VCE_SOFT_WESET__DCAP_FSM_SOFT_WESET__SHIFT                                                            0x15
#define VCE_SOFT_WESET__VEP_SOFT_WESET__SHIFT                                                                 0x16
#define VCE_SOFT_WESET__ECPU_SOFT_WESET_MASK                                                                  0x00000001W
#define VCE_SOFT_WESET__UENC_SOFT_WESET_MASK                                                                  0x00000002W
#define VCE_SOFT_WESET__FME_SOFT_WESET_MASK                                                                   0x00000004W
#define VCE_SOFT_WESET__MIF_SOFT_WESET_MASK                                                                   0x00000008W
#define VCE_SOFT_WESET__DBF_SOFT_WESET_MASK                                                                   0x00000010W
#define VCE_SOFT_WESET__ENT_SOFT_WESET_MASK                                                                   0x00000020W
#define VCE_SOFT_WESET__TBE_SOFT_WESET_MASK                                                                   0x00000040W
#define VCE_SOFT_WESET__WCM_SOFT_WESET_MASK                                                                   0x00000080W
#define VCE_SOFT_WESET__CTW_SOFT_WESET_MASK                                                                   0x00000100W
#define VCE_SOFT_WESET__IME_SOFT_WESET_MASK                                                                   0x00000200W
#define VCE_SOFT_WESET__IH_SOFT_WESET_MASK                                                                    0x00000400W
#define VCE_SOFT_WESET__SEM_SOFT_WESET_MASK                                                                   0x00000800W
#define VCE_SOFT_WESET__DCAP_SOFT_WESET_MASK                                                                  0x00001000W
#define VCE_SOFT_WESET__ACAP_SOFT_WESET_MASK                                                                  0x00002000W
#define VCE_SOFT_WESET__TAP_SOFT_WESET_MASK                                                                   0x00004000W
#define VCE_SOFT_WESET__WMI_SOFT_WESET_MASK                                                                   0x00008000W
#define VCE_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK                                                               0x00010000W
#define VCE_SOFT_WESET__AVMUX_SOFT_WESET_MASK                                                                 0x00080000W
#define VCE_SOFT_WESET__VWEG_SOFT_WESET_MASK                                                                  0x00100000W
#define VCE_SOFT_WESET__DCAP_FSM_SOFT_WESET_MASK                                                              0x00200000W
#define VCE_SOFT_WESET__VEP_SOFT_WESET_MASK                                                                   0x00400000W
//VCE_WB_BASE_WO2
#define VCE_WB_BASE_WO2__WB_BASE_WO__SHIFT                                                                    0x6
#define VCE_WB_BASE_WO2__WB_BASE_WO_MASK                                                                      0xFFFFFFC0W
//VCE_WB_BASE_HI2
#define VCE_WB_BASE_HI2__WB_BASE_HI__SHIFT                                                                    0x0
#define VCE_WB_BASE_HI2__WB_BASE_HI_MASK                                                                      0xFFFFFFFFW
//VCE_WB_SIZE2
#define VCE_WB_SIZE2__WB_SIZE__SHIFT                                                                          0x4
#define VCE_WB_SIZE2__WB_SIZE_MASK                                                                            0x007FFFF0W
//VCE_WB_WPTW2
#define VCE_WB_WPTW2__WB_WPTW__SHIFT                                                                          0x4
#define VCE_WB_WPTW2__WB_WPTW_MASK                                                                            0x007FFFF0W
//VCE_WB_WPTW2
#define VCE_WB_WPTW2__WB_WPTW__SHIFT                                                                          0x4
#define VCE_WB_WPTW2__WB_WPTW_MASK                                                                            0x007FFFF0W
//VCE_WB_BASE_WO
#define VCE_WB_BASE_WO__WB_BASE_WO__SHIFT                                                                     0x6
#define VCE_WB_BASE_WO__WB_BASE_WO_MASK                                                                       0xFFFFFFC0W
//VCE_WB_BASE_HI
#define VCE_WB_BASE_HI__WB_BASE_HI__SHIFT                                                                     0x0
#define VCE_WB_BASE_HI__WB_BASE_HI_MASK                                                                       0xFFFFFFFFW
//VCE_WB_SIZE
#define VCE_WB_SIZE__WB_SIZE__SHIFT                                                                           0x4
#define VCE_WB_SIZE__WB_SIZE_MASK                                                                             0x007FFFF0W
//VCE_WB_WPTW
#define VCE_WB_WPTW__WB_WPTW__SHIFT                                                                           0x4
#define VCE_WB_WPTW__WB_WPTW_MASK                                                                             0x007FFFF0W
//VCE_WB_WPTW
#define VCE_WB_WPTW__WB_WPTW__SHIFT                                                                           0x4
#define VCE_WB_WPTW__WB_WPTW_MASK                                                                             0x007FFFF0W
//VCE_WB_AWB_CTWW
#define VCE_WB_AWB_CTWW__WB_AWB_CTWW__SHIFT                                                                   0x0
#define VCE_WB_AWB_CTWW__VCE_CGTT_OVEWWIDE__SHIFT                                                             0x10
#define VCE_WB_AWB_CTWW__WB_AWB_CTWW_MASK                                                                     0x000001FFW
#define VCE_WB_AWB_CTWW__VCE_CGTT_OVEWWIDE_MASK                                                               0x00010000W
//VCE_CWOCK_GATING_A
#define VCE_CWOCK_GATING_A__CGC_CWK_ON_DEWAY__SHIFT                                                           0x0
#define VCE_CWOCK_GATING_A__CGC_CWK_OFF_DEWAY__SHIFT                                                          0x4
#define VCE_CWOCK_GATING_A__CGC_WEG_AWAKE__SHIFT                                                              0x11
#define VCE_CWOCK_GATING_A__CGC_CWK_ON_DEWAY_MASK                                                             0x0000000FW
#define VCE_CWOCK_GATING_A__CGC_CWK_OFF_DEWAY_MASK                                                            0x00000FF0W
#define VCE_CWOCK_GATING_A__CGC_WEG_AWAKE_MASK                                                                0x00020000W
//VCE_CWOCK_GATING_B
#define VCE_CWOCK_GATING_B__CGC_SYS_CWK_FOWCE_ON__SHIFT                                                       0x0
#define VCE_CWOCK_GATING_B__CGC_WMI_MC_CWK_FOWCE_ON__SHIFT                                                    0x1
#define VCE_CWOCK_GATING_B__CGC_WMI_UMC_CWK_FOWCE_ON__SHIFT                                                   0x2
#define VCE_CWOCK_GATING_B__CGC_UENC_CWK_FOWCE_ON__SHIFT                                                      0x3
#define VCE_CWOCK_GATING_B__CGC_VWEG_CWK_FOWCE_ON__SHIFT                                                      0x4
#define VCE_CWOCK_GATING_B__CGC_ECPU_CWK_FOWCE_ON__SHIFT                                                      0x5
#define VCE_CWOCK_GATING_B__CGC_IH_CWK_FOWCE_ON__SHIFT                                                        0x6
#define VCE_CWOCK_GATING_B__CGC_SEM_CWK_FOWCE_ON__SHIFT                                                       0x7
#define VCE_CWOCK_GATING_B__CGC_CTWWEG_CWK_FOWCE_ON__SHIFT                                                    0x8
#define VCE_CWOCK_GATING_B__CGC_MMSCH_CWK_FOWCE_ON__SHIFT                                                     0x9
#define VCE_CWOCK_GATING_B__CGC_SYS_CWK_FOWCE_OFF__SHIFT                                                      0x10
#define VCE_CWOCK_GATING_B__CGC_WMI_MC_CWK_FOWCE_OFF__SHIFT                                                   0x11
#define VCE_CWOCK_GATING_B__CGC_WMI_UMC_CWK_FOWCE_OFF__SHIFT                                                  0x12
#define VCE_CWOCK_GATING_B__CGC_UENC_CWK_FOWCE_OFF__SHIFT                                                     0x13
#define VCE_CWOCK_GATING_B__CGC_ECPU_CWK_FOWCE_OFF__SHIFT                                                     0x15
#define VCE_CWOCK_GATING_B__CGC_IH_CWK_FOWCE_OFF__SHIFT                                                       0x16
#define VCE_CWOCK_GATING_B__CGC_SEM_CWK_FOWCE_OFF__SHIFT                                                      0x17
#define VCE_CWOCK_GATING_B__CGC_MMSCH_CWK_FOWCE_OFF__SHIFT                                                    0x18
#define VCE_CWOCK_GATING_B__CGC_SYS_CWK_FOWCE_ON_MASK                                                         0x00000001W
#define VCE_CWOCK_GATING_B__CGC_WMI_MC_CWK_FOWCE_ON_MASK                                                      0x00000002W
#define VCE_CWOCK_GATING_B__CGC_WMI_UMC_CWK_FOWCE_ON_MASK                                                     0x00000004W
#define VCE_CWOCK_GATING_B__CGC_UENC_CWK_FOWCE_ON_MASK                                                        0x00000008W
#define VCE_CWOCK_GATING_B__CGC_VWEG_CWK_FOWCE_ON_MASK                                                        0x00000010W
#define VCE_CWOCK_GATING_B__CGC_ECPU_CWK_FOWCE_ON_MASK                                                        0x00000020W
#define VCE_CWOCK_GATING_B__CGC_IH_CWK_FOWCE_ON_MASK                                                          0x00000040W
#define VCE_CWOCK_GATING_B__CGC_SEM_CWK_FOWCE_ON_MASK                                                         0x00000080W
#define VCE_CWOCK_GATING_B__CGC_CTWWEG_CWK_FOWCE_ON_MASK                                                      0x00000100W
#define VCE_CWOCK_GATING_B__CGC_MMSCH_CWK_FOWCE_ON_MASK                                                       0x00000200W
#define VCE_CWOCK_GATING_B__CGC_SYS_CWK_FOWCE_OFF_MASK                                                        0x00010000W
#define VCE_CWOCK_GATING_B__CGC_WMI_MC_CWK_FOWCE_OFF_MASK                                                     0x00020000W
#define VCE_CWOCK_GATING_B__CGC_WMI_UMC_CWK_FOWCE_OFF_MASK                                                    0x00040000W
#define VCE_CWOCK_GATING_B__CGC_UENC_CWK_FOWCE_OFF_MASK                                                       0x00080000W
#define VCE_CWOCK_GATING_B__CGC_ECPU_CWK_FOWCE_OFF_MASK                                                       0x00200000W
#define VCE_CWOCK_GATING_B__CGC_IH_CWK_FOWCE_OFF_MASK                                                         0x00400000W
#define VCE_CWOCK_GATING_B__CGC_SEM_CWK_FOWCE_OFF_MASK                                                        0x00800000W
#define VCE_CWOCK_GATING_B__CGC_MMSCH_CWK_FOWCE_OFF_MASK                                                      0x01000000W
//VCE_WB_BASE_WO3
#define VCE_WB_BASE_WO3__WB_BASE_WO__SHIFT                                                                    0x6
#define VCE_WB_BASE_WO3__WB_BASE_WO_MASK                                                                      0xFFFFFFC0W
//VCE_WB_BASE_HI3
#define VCE_WB_BASE_HI3__WB_BASE_HI__SHIFT                                                                    0x0
#define VCE_WB_BASE_HI3__WB_BASE_HI_MASK                                                                      0xFFFFFFFFW
//VCE_WB_SIZE3
#define VCE_WB_SIZE3__WB_SIZE__SHIFT                                                                          0x4
#define VCE_WB_SIZE3__WB_SIZE_MASK                                                                            0x007FFFF0W
//VCE_WB_WPTW3
#define VCE_WB_WPTW3__WB_WPTW__SHIFT                                                                          0x4
#define VCE_WB_WPTW3__WB_WPTW_MASK                                                                            0x007FFFF0W
//VCE_WB_WPTW3
#define VCE_WB_WPTW3__WB_WPTW__SHIFT                                                                          0x4
#define VCE_WB_WPTW3__WB_WPTW_MASK                                                                            0x007FFFF0W
//VCE_SYS_INT_EN
#define VCE_SYS_INT_EN__VCE_SYS_INT_SEMA_WAIT_FAIW_TIMEOUT_EN__SHIFT                                          0x0
#define VCE_SYS_INT_EN__VCE_SYS_INT_TWAP_INTEWWUPT_EN__SHIFT                                                  0x3
#define VCE_SYS_INT_EN__VCE_SYS_INT_SEMA_WAIT_FAIW_TIMEOUT_EN_MASK                                            0x00000001W
#define VCE_SYS_INT_EN__VCE_SYS_INT_TWAP_INTEWWUPT_EN_MASK                                                    0x00000008W
//VCE_SYS_INT_ACK
#define VCE_SYS_INT_ACK__VCE_SYS_INT_SEMA_WAIT_FAIW_TIMEOUT_ACK__SHIFT                                        0x0
#define VCE_SYS_INT_ACK__VCE_SYS_INT_TWAP_INTEWWUPT_ACK__SHIFT                                                0x3
#define VCE_SYS_INT_ACK__VCE_SYS_INT_SEMA_WAIT_FAIW_TIMEOUT_ACK_MASK                                          0x00000001W
#define VCE_SYS_INT_ACK__VCE_SYS_INT_TWAP_INTEWWUPT_ACK_MASK                                                  0x00000008W
//VCE_SYS_INT_STATUS
#define VCE_SYS_INT_STATUS__VCE_SYS_INT_SEMA_WAIT_FAIW_TIMEOUT_INT__SHIFT                                     0x0
#define VCE_SYS_INT_STATUS__VCE_SYS_INT_TWAP_INTEWWUPT_INT__SHIFT                                             0x3
#define VCE_SYS_INT_STATUS__VCE_SYS_INT_SEMA_WAIT_FAIW_TIMEOUT_INT_MASK                                       0x00000001W
#define VCE_SYS_INT_STATUS__VCE_SYS_INT_TWAP_INTEWWUPT_INT_MASK                                               0x00000008W


// addwessBwock: vce0_ctw_dec
//VCE_UENC_CWOCK_GATING
#define VCE_UENC_CWOCK_GATING__CWOCK_ON_DEWAY__SHIFT                                                          0x0
#define VCE_UENC_CWOCK_GATING__CWOCK_OFF_DEWAY__SHIFT                                                         0x4
#define VCE_UENC_CWOCK_GATING__VEPCWK_FOWCE_ON__SHIFT                                                         0xc
#define VCE_UENC_CWOCK_GATING__IMECWK_FOWCE_ON__SHIFT                                                         0xd
#define VCE_UENC_CWOCK_GATING__FMECWK_FOWCE_ON__SHIFT                                                         0xe
#define VCE_UENC_CWOCK_GATING__TBECWK_FOWCE_ON__SHIFT                                                         0xf
#define VCE_UENC_CWOCK_GATING__DBFCWK_FOWCE_ON__SHIFT                                                         0x10
#define VCE_UENC_CWOCK_GATING__ENTCWK_FOWCE_ON__SHIFT                                                         0x11
#define VCE_UENC_CWOCK_GATING__WCMCWK_FOWCE_ON__SHIFT                                                         0x12
#define VCE_UENC_CWOCK_GATING__AVMCWK_FOWCE_ON__SHIFT                                                         0x13
#define VCE_UENC_CWOCK_GATING__DCAPCWK_FOWCE_ON__SHIFT                                                        0x14
#define VCE_UENC_CWOCK_GATING__ACAPCWK_FOWCE_ON__SHIFT                                                        0x15
#define VCE_UENC_CWOCK_GATING__ACAPCWK_FOWCE_OFF__SHIFT                                                       0x16
#define VCE_UENC_CWOCK_GATING__VEPCWK_FOWCE_OFF__SHIFT                                                        0x17
#define VCE_UENC_CWOCK_GATING__IMECWK_FOWCE_OFF__SHIFT                                                        0x18
#define VCE_UENC_CWOCK_GATING__FMECWK_FOWCE_OFF__SHIFT                                                        0x19
#define VCE_UENC_CWOCK_GATING__TBECWK_FOWCE_OFF__SHIFT                                                        0x1a
#define VCE_UENC_CWOCK_GATING__DBFCWK_FOWCE_OFF__SHIFT                                                        0x1b
#define VCE_UENC_CWOCK_GATING__ENTCWK_FOWCE_OFF__SHIFT                                                        0x1c
#define VCE_UENC_CWOCK_GATING__WCMCWK_FOWCE_OFF__SHIFT                                                        0x1d
#define VCE_UENC_CWOCK_GATING__AVMCWK_FOWCE_OFF__SHIFT                                                        0x1e
#define VCE_UENC_CWOCK_GATING__DCAPCWK_FOWCE_OFF__SHIFT                                                       0x1f
#define VCE_UENC_CWOCK_GATING__CWOCK_ON_DEWAY_MASK                                                            0x0000000FW
#define VCE_UENC_CWOCK_GATING__CWOCK_OFF_DEWAY_MASK                                                           0x00000FF0W
#define VCE_UENC_CWOCK_GATING__VEPCWK_FOWCE_ON_MASK                                                           0x00001000W
#define VCE_UENC_CWOCK_GATING__IMECWK_FOWCE_ON_MASK                                                           0x00002000W
#define VCE_UENC_CWOCK_GATING__FMECWK_FOWCE_ON_MASK                                                           0x00004000W
#define VCE_UENC_CWOCK_GATING__TBECWK_FOWCE_ON_MASK                                                           0x00008000W
#define VCE_UENC_CWOCK_GATING__DBFCWK_FOWCE_ON_MASK                                                           0x00010000W
#define VCE_UENC_CWOCK_GATING__ENTCWK_FOWCE_ON_MASK                                                           0x00020000W
#define VCE_UENC_CWOCK_GATING__WCMCWK_FOWCE_ON_MASK                                                           0x00040000W
#define VCE_UENC_CWOCK_GATING__AVMCWK_FOWCE_ON_MASK                                                           0x00080000W
#define VCE_UENC_CWOCK_GATING__DCAPCWK_FOWCE_ON_MASK                                                          0x00100000W
#define VCE_UENC_CWOCK_GATING__ACAPCWK_FOWCE_ON_MASK                                                          0x00200000W
#define VCE_UENC_CWOCK_GATING__ACAPCWK_FOWCE_OFF_MASK                                                         0x00400000W
#define VCE_UENC_CWOCK_GATING__VEPCWK_FOWCE_OFF_MASK                                                          0x00800000W
#define VCE_UENC_CWOCK_GATING__IMECWK_FOWCE_OFF_MASK                                                          0x01000000W
#define VCE_UENC_CWOCK_GATING__FMECWK_FOWCE_OFF_MASK                                                          0x02000000W
#define VCE_UENC_CWOCK_GATING__TBECWK_FOWCE_OFF_MASK                                                          0x04000000W
#define VCE_UENC_CWOCK_GATING__DBFCWK_FOWCE_OFF_MASK                                                          0x08000000W
#define VCE_UENC_CWOCK_GATING__ENTCWK_FOWCE_OFF_MASK                                                          0x10000000W
#define VCE_UENC_CWOCK_GATING__WCMCWK_FOWCE_OFF_MASK                                                          0x20000000W
#define VCE_UENC_CWOCK_GATING__AVMCWK_FOWCE_OFF_MASK                                                          0x40000000W
#define VCE_UENC_CWOCK_GATING__DCAPCWK_FOWCE_OFF_MASK                                                         0x80000000W
//VCE_UENC_WEG_CWOCK_GATING
#define VCE_UENC_WEG_CWOCK_GATING__MIFWEGCWK_FOWCE_ON__SHIFT                                                  0x0
#define VCE_UENC_WEG_CWOCK_GATING__IMEWEGCWK_FOWCE_ON__SHIFT                                                  0x1
#define VCE_UENC_WEG_CWOCK_GATING__FMEWEGCWK_FOWCE_ON__SHIFT                                                  0x2
#define VCE_UENC_WEG_CWOCK_GATING__TBEWEGCWK_FOWCE_ON__SHIFT                                                  0x3
#define VCE_UENC_WEG_CWOCK_GATING__DBFWEGCWK_FOWCE_ON__SHIFT                                                  0x4
#define VCE_UENC_WEG_CWOCK_GATING__ENTWEGCWK_FOWCE_ON__SHIFT                                                  0x5
#define VCE_UENC_WEG_CWOCK_GATING__WCMWEGCWK_FOWCE_ON__SHIFT                                                  0x6
#define VCE_UENC_WEG_CWOCK_GATING__WESEWVED__SHIFT                                                            0x7
#define VCE_UENC_WEG_CWOCK_GATING__AVMWEGCWK_FOWCE_ON__SHIFT                                                  0x8
#define VCE_UENC_WEG_CWOCK_GATING__DCAPWEGCWK_FOWCE_ON__SHIFT                                                 0x9
#define VCE_UENC_WEG_CWOCK_GATING__VEPWEGCWK_FOWCE_ON__SHIFT                                                  0xa
#define VCE_UENC_WEG_CWOCK_GATING__MIFWEGCWK_FOWCE_ON_MASK                                                    0x00000001W
#define VCE_UENC_WEG_CWOCK_GATING__IMEWEGCWK_FOWCE_ON_MASK                                                    0x00000002W
#define VCE_UENC_WEG_CWOCK_GATING__FMEWEGCWK_FOWCE_ON_MASK                                                    0x00000004W
#define VCE_UENC_WEG_CWOCK_GATING__TBEWEGCWK_FOWCE_ON_MASK                                                    0x00000008W
#define VCE_UENC_WEG_CWOCK_GATING__DBFWEGCWK_FOWCE_ON_MASK                                                    0x00000010W
#define VCE_UENC_WEG_CWOCK_GATING__ENTWEGCWK_FOWCE_ON_MASK                                                    0x00000020W
#define VCE_UENC_WEG_CWOCK_GATING__WCMWEGCWK_FOWCE_ON_MASK                                                    0x00000040W
#define VCE_UENC_WEG_CWOCK_GATING__WESEWVED_MASK                                                              0x00000080W
#define VCE_UENC_WEG_CWOCK_GATING__AVMWEGCWK_FOWCE_ON_MASK                                                    0x00000100W
#define VCE_UENC_WEG_CWOCK_GATING__DCAPWEGCWK_FOWCE_ON_MASK                                                   0x00000200W
#define VCE_UENC_WEG_CWOCK_GATING__VEPWEGCWK_FOWCE_ON_MASK                                                    0x00000400W
//VCE_UENC_CWOCK_GATING_2
#define VCE_UENC_CWOCK_GATING_2__DBF2CWK_FOWCE_ON__SHIFT                                                      0x1
#define VCE_UENC_CWOCK_GATING_2__DBF2CWK_FOWCE_OFF__SHIFT                                                     0x10
#define VCE_UENC_CWOCK_GATING_2__DBF2CWK_FOWCE_ON_MASK                                                        0x00000002W
#define VCE_UENC_CWOCK_GATING_2__DBF2CWK_FOWCE_OFF_MASK                                                       0x00010000W


// addwessBwock: vce0_vce_scwk_dec
//VCE_WMI_VCPU_CACHE_40BIT_BAW
#define VCE_WMI_VCPU_CACHE_40BIT_BAW__BAW__SHIFT                                                              0x0
#define VCE_WMI_VCPU_CACHE_40BIT_BAW__BAW_MASK                                                                0xFFFFFFFFW
//VCE_WMI_CTWW2
#define VCE_WMI_CTWW2__STAWW_AWB__SHIFT                                                                       0x1
#define VCE_WMI_CTWW2__ASSEWT_UMC_UWGENT__SHIFT                                                               0x2
#define VCE_WMI_CTWW2__MASK_UMC_UWGENT__SHIFT                                                                 0x3
#define VCE_WMI_CTWW2__STAWW_AWB_UMC__SHIFT                                                                   0x8
#define VCE_WMI_CTWW2__STAWW_AWB_MASK                                                                         0x00000002W
#define VCE_WMI_CTWW2__ASSEWT_UMC_UWGENT_MASK                                                                 0x00000004W
#define VCE_WMI_CTWW2__MASK_UMC_UWGENT_MASK                                                                   0x00000008W
#define VCE_WMI_CTWW2__STAWW_AWB_UMC_MASK                                                                     0x00000100W
//VCE_WMI_SWAP_CNTW3
#define VCE_WMI_SWAP_CNTW3__WD_MC_CID_SWAP__SHIFT                                                             0x0
#define VCE_WMI_SWAP_CNTW3__WD_MC_CID_TWAN__SHIFT                                                             0x14
#define VCE_WMI_SWAP_CNTW3__WD_MC_CID_UWG__SHIFT                                                              0x1a
#define VCE_WMI_SWAP_CNTW3__WD_MC_CID_SWAP_MASK                                                               0x00000003W
#define VCE_WMI_SWAP_CNTW3__WD_MC_CID_TWAN_MASK                                                               0x00100000W
#define VCE_WMI_SWAP_CNTW3__WD_MC_CID_UWG_MASK                                                                0x04000000W
//VCE_WMI_CTWW
#define VCE_WMI_CTWW__ASSEWT_MC_UWGENT__SHIFT                                                                 0xb
#define VCE_WMI_CTWW__MASK_MC_UWGENT__SHIFT                                                                   0xc
#define VCE_WMI_CTWW__DATA_COHEWENCY_EN__SHIFT                                                                0xd
#define VCE_WMI_CTWW__VCPU_DATA_COHEWENCY_EN__SHIFT                                                           0x15
#define VCE_WMI_CTWW__MIF_DATA_COHEWENCY_EN__SHIFT                                                            0x16
#define VCE_WMI_CTWW__VCPU_WD_CACHE_MISS_COUNT_EN__SHIFT                                                      0x17
#define VCE_WMI_CTWW__VCPU_WD_CACHE_MISS_COUNT_WESET__SHIFT                                                   0x18
#define VCE_WMI_CTWW__ASSEWT_MC_UWGENT_MASK                                                                   0x00000800W
#define VCE_WMI_CTWW__MASK_MC_UWGENT_MASK                                                                     0x00001000W
#define VCE_WMI_CTWW__DATA_COHEWENCY_EN_MASK                                                                  0x00002000W
#define VCE_WMI_CTWW__VCPU_DATA_COHEWENCY_EN_MASK                                                             0x00200000W
#define VCE_WMI_CTWW__MIF_DATA_COHEWENCY_EN_MASK                                                              0x00400000W
#define VCE_WMI_CTWW__VCPU_WD_CACHE_MISS_COUNT_EN_MASK                                                        0x00800000W
#define VCE_WMI_CTWW__VCPU_WD_CACHE_MISS_COUNT_WESET_MASK                                                     0x01000000W
//VCE_WMI_SWAP_CNTW
#define VCE_WMI_SWAP_CNTW__VCPU_W_MC_SWAP__SHIFT                                                              0x0
#define VCE_WMI_SWAP_CNTW__WW_MC_CID_SWAP__SHIFT                                                              0x2
#define VCE_WMI_SWAP_CNTW__WW_MC_CID_TWAN__SHIFT                                                              0x14
#define VCE_WMI_SWAP_CNTW__WW_MC_CID_UWG__SHIFT                                                               0x1a
#define VCE_WMI_SWAP_CNTW__VCPU_W_MC_SWAP_MASK                                                                0x00000003W
#define VCE_WMI_SWAP_CNTW__WW_MC_CID_SWAP_MASK                                                                0x00003FFCW
#define VCE_WMI_SWAP_CNTW__WW_MC_CID_TWAN_MASK                                                                0x03F00000W
#define VCE_WMI_SWAP_CNTW__WW_MC_CID_UWG_MASK                                                                 0xFC000000W
//VCE_WMI_SWAP_CNTW1
#define VCE_WMI_SWAP_CNTW1__VCPU_W_MC_SWAP__SHIFT                                                             0x0
#define VCE_WMI_SWAP_CNTW1__WD_MC_CID_SWAP__SHIFT                                                             0x2
#define VCE_WMI_SWAP_CNTW1__WD_MC_CID_TWAN__SHIFT                                                             0x14
#define VCE_WMI_SWAP_CNTW1__WD_MC_CID_UWG__SHIFT                                                              0x1a
#define VCE_WMI_SWAP_CNTW1__VCPU_W_MC_SWAP_MASK                                                               0x00000003W
#define VCE_WMI_SWAP_CNTW1__WD_MC_CID_SWAP_MASK                                                               0x00003FFCW
#define VCE_WMI_SWAP_CNTW1__WD_MC_CID_TWAN_MASK                                                               0x03F00000W
#define VCE_WMI_SWAP_CNTW1__WD_MC_CID_UWG_MASK                                                                0xFC000000W
//VCE_WMI_SWAP_CNTW2
#define VCE_WMI_SWAP_CNTW2__WW_MC_CID_SWAP__SHIFT                                                             0x0
#define VCE_WMI_SWAP_CNTW2__WW_MC_CID_TWAN__SHIFT                                                             0x14
#define VCE_WMI_SWAP_CNTW2__WW_MC_CID_UWG__SHIFT                                                              0x1a
#define VCE_WMI_SWAP_CNTW2__WW_MC_CID_SWAP_MASK                                                               0x000000FFW
#define VCE_WMI_SWAP_CNTW2__WW_MC_CID_TWAN_MASK                                                               0x00F00000W
#define VCE_WMI_SWAP_CNTW2__WW_MC_CID_UWG_MASK                                                                0x3C000000W
//VCE_WMI_CACHE_CTWW
#define VCE_WMI_CACHE_CTWW__VCPU_EN__SHIFT                                                                    0x0
#define VCE_WMI_CACHE_CTWW__VCPU_FWUSH__SHIFT                                                                 0x1
#define VCE_WMI_CACHE_CTWW__VCPU_EN_MASK                                                                      0x00000001W
#define VCE_WMI_CACHE_CTWW__VCPU_FWUSH_MASK                                                                   0x00000002W
//VCE_WMI_VCPU_CACHE_64BIT_BAW0
#define VCE_WMI_VCPU_CACHE_64BIT_BAW0__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_64BIT_BAW0__BAW_MASK                                                               0x000000FFW
//VCE_WMI_VCPU_CACHE_64BIT_BAW1
#define VCE_WMI_VCPU_CACHE_64BIT_BAW1__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_64BIT_BAW1__BAW_MASK                                                               0x000000FFW
//VCE_WMI_VCPU_CACHE_64BIT_BAW2
#define VCE_WMI_VCPU_CACHE_64BIT_BAW2__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_64BIT_BAW2__BAW_MASK                                                               0x000000FFW
//VCE_WMI_VCPU_CACHE_64BIT_BAW3
#define VCE_WMI_VCPU_CACHE_64BIT_BAW3__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_64BIT_BAW3__BAW_MASK                                                               0x000000FFW
//VCE_WMI_VCPU_CACHE_64BIT_BAW4
#define VCE_WMI_VCPU_CACHE_64BIT_BAW4__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_64BIT_BAW4__BAW_MASK                                                               0x000000FFW
//VCE_WMI_VCPU_CACHE_64BIT_BAW5
#define VCE_WMI_VCPU_CACHE_64BIT_BAW5__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_64BIT_BAW5__BAW_MASK                                                               0x000000FFW
//VCE_WMI_VCPU_CACHE_64BIT_BAW6
#define VCE_WMI_VCPU_CACHE_64BIT_BAW6__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_64BIT_BAW6__BAW_MASK                                                               0x000000FFW
//VCE_WMI_VCPU_CACHE_64BIT_BAW7
#define VCE_WMI_VCPU_CACHE_64BIT_BAW7__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_64BIT_BAW7__BAW_MASK                                                               0x000000FFW
//VCE_WMI_VCPU_CACHE_40BIT_BAW0
#define VCE_WMI_VCPU_CACHE_40BIT_BAW0__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_40BIT_BAW0__BAW_MASK                                                               0xFFFFFFFFW
//VCE_WMI_VCPU_CACHE_40BIT_BAW1
#define VCE_WMI_VCPU_CACHE_40BIT_BAW1__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_40BIT_BAW1__BAW_MASK                                                               0xFFFFFFFFW
//VCE_WMI_VCPU_CACHE_40BIT_BAW2
#define VCE_WMI_VCPU_CACHE_40BIT_BAW2__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_40BIT_BAW2__BAW_MASK                                                               0xFFFFFFFFW
//VCE_WMI_VCPU_CACHE_40BIT_BAW3
#define VCE_WMI_VCPU_CACHE_40BIT_BAW3__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_40BIT_BAW3__BAW_MASK                                                               0xFFFFFFFFW
//VCE_WMI_VCPU_CACHE_40BIT_BAW4
#define VCE_WMI_VCPU_CACHE_40BIT_BAW4__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_40BIT_BAW4__BAW_MASK                                                               0xFFFFFFFFW
//VCE_WMI_VCPU_CACHE_40BIT_BAW5
#define VCE_WMI_VCPU_CACHE_40BIT_BAW5__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_40BIT_BAW5__BAW_MASK                                                               0xFFFFFFFFW
//VCE_WMI_VCPU_CACHE_40BIT_BAW6
#define VCE_WMI_VCPU_CACHE_40BIT_BAW6__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_40BIT_BAW6__BAW_MASK                                                               0xFFFFFFFFW
//VCE_WMI_VCPU_CACHE_40BIT_BAW7
#define VCE_WMI_VCPU_CACHE_40BIT_BAW7__BAW__SHIFT                                                             0x0
#define VCE_WMI_VCPU_CACHE_40BIT_BAW7__BAW_MASK                                                               0xFFFFFFFFW


// addwessBwock: vce0_mmsch_dec
//VCE_MMSCH_VF_VMID
#define VCE_MMSCH_VF_VMID__VF_CTX_VMID__SHIFT                                                                 0x0
#define VCE_MMSCH_VF_VMID__VF_GPCOM_VMID__SHIFT                                                               0x4
#define VCE_MMSCH_VF_VMID__VF_CTX_VMID_MASK                                                                   0x0000000FW
#define VCE_MMSCH_VF_VMID__VF_GPCOM_VMID_MASK                                                                 0x000000F0W
//VCE_MMSCH_VF_CTX_ADDW_WO
#define VCE_MMSCH_VF_CTX_ADDW_WO__VF_CTX_ADDW_WO__SHIFT                                                       0x6
#define VCE_MMSCH_VF_CTX_ADDW_WO__VF_CTX_ADDW_WO_MASK                                                         0xFFFFFFC0W
//VCE_MMSCH_VF_CTX_ADDW_HI
#define VCE_MMSCH_VF_CTX_ADDW_HI__VF_CTX_ADDW_HI__SHIFT                                                       0x0
#define VCE_MMSCH_VF_CTX_ADDW_HI__VF_CTX_ADDW_HI_MASK                                                         0xFFFFFFFFW
//VCE_MMSCH_VF_CTX_SIZE
#define VCE_MMSCH_VF_CTX_SIZE__VF_CTX_SIZE__SHIFT                                                             0x0
#define VCE_MMSCH_VF_CTX_SIZE__VF_CTX_SIZE_MASK                                                               0xFFFFFFFFW
//VCE_MMSCH_VF_GPCOM_ADDW_WO
#define VCE_MMSCH_VF_GPCOM_ADDW_WO__VF_GPCOM_ADDW_WO__SHIFT                                                   0x6
#define VCE_MMSCH_VF_GPCOM_ADDW_WO__VF_GPCOM_ADDW_WO_MASK                                                     0xFFFFFFC0W
//VCE_MMSCH_VF_GPCOM_ADDW_HI
#define VCE_MMSCH_VF_GPCOM_ADDW_HI__VF_GPCOM_ADDW_HI__SHIFT                                                   0x0
#define VCE_MMSCH_VF_GPCOM_ADDW_HI__VF_GPCOM_ADDW_HI_MASK                                                     0xFFFFFFFFW
//VCE_MMSCH_VF_GPCOM_SIZE
#define VCE_MMSCH_VF_GPCOM_SIZE__VF_GPCOM_SIZE__SHIFT                                                         0x0
#define VCE_MMSCH_VF_GPCOM_SIZE__VF_GPCOM_SIZE_MASK                                                           0xFFFFFFFFW
//VCE_MMSCH_VF_MAIWBOX_HOST
#define VCE_MMSCH_VF_MAIWBOX_HOST__DATA__SHIFT                                                                0x0
#define VCE_MMSCH_VF_MAIWBOX_HOST__DATA_MASK                                                                  0xFFFFFFFFW
//VCE_MMSCH_VF_MAIWBOX_WESP
#define VCE_MMSCH_VF_MAIWBOX_WESP__WESP__SHIFT                                                                0x0
#define VCE_MMSCH_VF_MAIWBOX_WESP__WESP_MASK                                                                  0xFFFFFFFFW


// addwessBwock: vce0_vce_wb_pg_dec
//VCE_HW_VEWSION
#define VCE_HW_VEWSION__VCE_VEWSION__SHIFT                                                                    0x0
#define VCE_HW_VEWSION__VCE_CONFIGUWATION__SHIFT                                                              0x8
#define VCE_HW_VEWSION__VCE_INSTANCE_ID__SHIFT                                                                0xa
#define VCE_HW_VEWSION__VCE_VEWSION_MASK                                                                      0x000000FFW
#define VCE_HW_VEWSION__VCE_CONFIGUWATION_MASK                                                                0x00000300W
#define VCE_HW_VEWSION__VCE_INSTANCE_ID_MASK                                                                  0x00000C00W



#endif
