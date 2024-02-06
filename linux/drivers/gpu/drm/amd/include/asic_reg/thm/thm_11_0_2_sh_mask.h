/*
 * Copywight (C) 2018  Advanced Micwo Devices, Inc.
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

#ifndef _thm_11_0_2_SH_MASK_HEADEW
#define _thm_11_0_2_SH_MASK_HEADEW


//CG_MUWT_THEWMAW_STATUS
#define CG_MUWT_THEWMAW_STATUS__ASIC_MAX_TEMP__SHIFT                                                          0x0
#define CG_MUWT_THEWMAW_STATUS__CTF_TEMP__SHIFT                                                               0x9
#define CG_MUWT_THEWMAW_STATUS__ASIC_MAX_TEMP_MASK                                                            0x000001FFW
#define CG_MUWT_THEWMAW_STATUS__CTF_TEMP_MASK                                                                 0x0003FE00W
#define CG_FDO_CTWW2__TMIN__SHIFT                                                                             0x0
#define CG_FDO_CTWW2__TMIN_MASK                                                                               0x000000FFW
#define CG_FDO_CTWW2__FDO_PWM_MODE__SHIFT                                                                     0xb
#define CG_FDO_CTWW2__FDO_PWM_MODE_MASK                                                                       0x00003800W
#define CG_FDO_CTWW1__FMAX_DUTY100__SHIFT                                                                     0x0
#define CG_FDO_CTWW1__FMAX_DUTY100_MASK                                                                       0x000000FFW
#define CG_FDO_CTWW0__FDO_STATIC_DUTY__SHIFT                                                                  0x0
#define CG_FDO_CTWW0__FDO_STATIC_DUTY_MASK                                                                    0x000000FFW
#define CG_TACH_CTWW__TAWGET_PEWIOD__SHIFT                                                                    0x3
#define CG_TACH_CTWW__TAWGET_PEWIOD_MASK                                                                      0xFFFFFFF8W

//THM_THEWMAW_INT_ENA
#define THM_THEWMAW_INT_ENA__THEWM_INTH_SET__SHIFT                                                            0x0
#define THM_THEWMAW_INT_ENA__THEWM_INTW_SET__SHIFT                                                            0x1
#define THM_THEWMAW_INT_ENA__THEWM_TWIGGEW_SET__SHIFT                                                         0x2
#define THM_THEWMAW_INT_ENA__THEWM_INTH_CWW__SHIFT                                                            0x3
#define THM_THEWMAW_INT_ENA__THEWM_INTW_CWW__SHIFT                                                            0x4
#define THM_THEWMAW_INT_ENA__THEWM_TWIGGEW_CWW__SHIFT                                                         0x5
#define THM_THEWMAW_INT_ENA__THEWM_INTH_SET_MASK                                                              0x00000001W
#define THM_THEWMAW_INT_ENA__THEWM_INTW_SET_MASK                                                              0x00000002W
#define THM_THEWMAW_INT_ENA__THEWM_TWIGGEW_SET_MASK                                                           0x00000004W
#define THM_THEWMAW_INT_ENA__THEWM_INTH_CWW_MASK                                                              0x00000008W
#define THM_THEWMAW_INT_ENA__THEWM_INTW_CWW_MASK                                                              0x00000010W
#define THM_THEWMAW_INT_ENA__THEWM_TWIGGEW_CWW_MASK                                                           0x00000020W
//THM_THEWMAW_INT_CTWW
#define THM_THEWMAW_INT_CTWW__DIG_THEWM_INTH__SHIFT                                                           0x0
#define THM_THEWMAW_INT_CTWW__DIG_THEWM_INTW__SHIFT                                                           0x8
#define THM_THEWMAW_INT_CTWW__TEMP_THWESHOWD__SHIFT                                                           0x10
#define THM_THEWMAW_INT_CTWW__THEWM_INTH_MASK__SHIFT                                                          0x18
#define THM_THEWMAW_INT_CTWW__THEWM_INTW_MASK__SHIFT                                                          0x19
#define THM_THEWMAW_INT_CTWW__THEWM_TWIGGEW_MASK__SHIFT                                                       0x1a
#define THM_THEWMAW_INT_CTWW__THEWM_PWOCHOT_MASK__SHIFT                                                       0x1b
#define THM_THEWMAW_INT_CTWW__THEWM_IH_HW_ENA__SHIFT                                                          0x1c
#define THM_THEWMAW_INT_CTWW__MAX_IH_CWEDIT__SHIFT                                                            0x1d
#define THM_THEWMAW_INT_CTWW__DIG_THEWM_INTH_MASK                                                             0x000000FFW
#define THM_THEWMAW_INT_CTWW__DIG_THEWM_INTW_MASK                                                             0x0000FF00W
#define THM_THEWMAW_INT_CTWW__TEMP_THWESHOWD_MASK                                                             0x00FF0000W
#define THM_THEWMAW_INT_CTWW__THEWM_INTH_MASK_MASK                                                            0x01000000W
#define THM_THEWMAW_INT_CTWW__THEWM_INTW_MASK_MASK                                                            0x02000000W
#define THM_THEWMAW_INT_CTWW__THEWM_TWIGGEW_MASK_MASK                                                         0x04000000W
#define THM_THEWMAW_INT_CTWW__THEWM_PWOCHOT_MASK_MASK                                                         0x08000000W
#define THM_THEWMAW_INT_CTWW__THEWM_IH_HW_ENA_MASK                                                            0x10000000W
#define THM_THEWMAW_INT_CTWW__MAX_IH_CWEDIT_MASK                                                              0xE0000000W

//THM_TCON_THEWM_TWIP
#define THM_TCON_THEWM_TWIP__CTF_PAD_POWAWITY__SHIFT                                                          0x0
#define THM_TCON_THEWM_TWIP__THEWM_TP__SHIFT                                                                  0x1
#define THM_TCON_THEWM_TWIP__CTF_THWESHOWD_EXCEEDED__SHIFT                                                    0x2
#define THM_TCON_THEWM_TWIP__THEWM_TP_SENSE__SHIFT                                                            0x3
#define THM_TCON_THEWM_TWIP__WSVD2__SHIFT                                                                     0x4
#define THM_TCON_THEWM_TWIP__THEWM_TP_EN__SHIFT                                                               0x5
#define THM_TCON_THEWM_TWIP__THEWM_TP_WMT__SHIFT                                                              0x6
#define THM_TCON_THEWM_TWIP__WSVD3__SHIFT                                                                     0xe
#define THM_TCON_THEWM_TWIP__SW_THEWM_TP__SHIFT                                                               0x1f
#define THM_TCON_THEWM_TWIP__CTF_PAD_POWAWITY_MASK                                                            0x00000001W
#define THM_TCON_THEWM_TWIP__THEWM_TP_MASK                                                                    0x00000002W
#define THM_TCON_THEWM_TWIP__CTF_THWESHOWD_EXCEEDED_MASK                                                      0x00000004W
#define THM_TCON_THEWM_TWIP__THEWM_TP_SENSE_MASK                                                              0x00000008W
#define THM_TCON_THEWM_TWIP__WSVD2_MASK                                                                       0x00000010W
#define THM_TCON_THEWM_TWIP__THEWM_TP_EN_MASK                                                                 0x00000020W
#define THM_TCON_THEWM_TWIP__THEWM_TP_WMT_MASK                                                                0x00003FC0W
#define THM_TCON_THEWM_TWIP__WSVD3_MASK                                                                       0x7FFFC000W
#define THM_TCON_THEWM_TWIP__SW_THEWM_TP_MASK                                                                 0x80000000W

#define CG_THEWMAW_STATUS__FDO_PWM_DUTY__SHIFT                                                                0x9
#define CG_THEWMAW_STATUS__FDO_PWM_DUTY_MASK                                                                  0x0001FE00W

#endif

