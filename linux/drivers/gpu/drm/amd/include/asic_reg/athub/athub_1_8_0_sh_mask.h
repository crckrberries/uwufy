/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */
#ifndef _athub_1_8_0_SH_MASK_HEADEW
#define _athub_1_8_0_SH_MASK_HEADEW


// addwessBwock: aid_athub_atsdec
//ATC_ATS_CNTW
#define ATC_ATS_CNTW__DISABWE_ATC__SHIFT                                                                      0x0
#define ATC_ATS_CNTW__DISABWE_PWI__SHIFT                                                                      0x1
#define ATC_ATS_CNTW__DISABWE_PASID__SHIFT                                                                    0x2
#define ATC_ATS_CNTW__CWEDITS_ATS_WPB__SHIFT                                                                  0x8
#define ATC_ATS_CNTW__DEBUG_ECO__SHIFT                                                                        0x10
#define ATC_ATS_CNTW__TWANS_EXE_WETUWN__SHIFT                                                                 0x16
#define ATC_ATS_CNTW__DISABWE_ATC_MASK                                                                        0x00000001W
#define ATC_ATS_CNTW__DISABWE_PWI_MASK                                                                        0x00000002W
#define ATC_ATS_CNTW__DISABWE_PASID_MASK                                                                      0x00000004W
#define ATC_ATS_CNTW__CWEDITS_ATS_WPB_MASK                                                                    0x00003F00W
#define ATC_ATS_CNTW__DEBUG_ECO_MASK                                                                          0x000F0000W
#define ATC_ATS_CNTW__TWANS_EXE_WETUWN_MASK                                                                   0x00C00000W
//ATC_ATS_CNTW2
#define ATC_ATS_CNTW2__CWEDITS_ATS_WPB_VC5TW__SHIFT                                                           0x0
#define ATC_ATS_CNTW2__CWEDITS_ATS_WPB_VC0TW__SHIFT                                                           0x8
#define ATC_ATS_CNTW2__CWEDITS_ATS_WPB_PWINV__SHIFT                                                           0x10
#define ATC_ATS_CNTW2__TWANSWATION_STAWW__SHIFT                                                               0x18
#define ATC_ATS_CNTW2__GC_TWANS_VC5_ENABWE__SHIFT                                                             0x19
#define ATC_ATS_CNTW2__MM_TWANS_VC5_ENABWE__SHIFT                                                             0x1a
#define ATC_ATS_CNTW2__WESEWVED__SHIFT                                                                        0x1b
#define ATC_ATS_CNTW2__CWEDITS_ATS_WPB_VC5TW_MASK                                                             0x000000FFW
#define ATC_ATS_CNTW2__CWEDITS_ATS_WPB_VC0TW_MASK                                                             0x0000FF00W
#define ATC_ATS_CNTW2__CWEDITS_ATS_WPB_PWINV_MASK                                                             0x00FF0000W
#define ATC_ATS_CNTW2__TWANSWATION_STAWW_MASK                                                                 0x01000000W
#define ATC_ATS_CNTW2__GC_TWANS_VC5_ENABWE_MASK                                                               0x02000000W
#define ATC_ATS_CNTW2__MM_TWANS_VC5_ENABWE_MASK                                                               0x04000000W
#define ATC_ATS_CNTW2__WESEWVED_MASK                                                                          0xF8000000W
//ATC_ATS_CNTW3
#define ATC_ATS_CNTW3__WESEWVED__SHIFT                                                                        0x0
#define ATC_ATS_CNTW3__WESEWVED_MASK                                                                          0xFFFFFFFFW
//ATC_ATS_CNTW4
#define ATC_ATS_CNTW4__WESEWVED__SHIFT                                                                        0x0
#define ATC_ATS_CNTW4__WESEWVED_MASK                                                                          0xFFFFFFFFW
//ATC_ATS_MISC_CNTW
#define ATC_ATS_MISC_CNTW__TWANS_WESP_IN_INV_COWWISION_HOST__SHIFT                                            0x10
#define ATC_ATS_MISC_CNTW__TWANS_WESP_IN_INV_COWWISION_GUEST__SHIFT                                           0x11
#define ATC_ATS_MISC_CNTW__DEBUG_COWWISION__SHIFT                                                             0x12
#define ATC_ATS_MISC_CNTW__EFFECTIVE_TWANS_WOWK_QUEUE__SHIFT                                                  0x13
#define ATC_ATS_MISC_CNTW__TWANS_WESP_NUWW_PASID_SEW__SHIFT                                                   0x1d
#define ATC_ATS_MISC_CNTW__WESEWVED__SHIFT                                                                    0x1e
#define ATC_ATS_MISC_CNTW__TWANS_WESP_IN_INV_COWWISION_HOST_MASK                                              0x00010000W
#define ATC_ATS_MISC_CNTW__TWANS_WESP_IN_INV_COWWISION_GUEST_MASK                                             0x00020000W
#define ATC_ATS_MISC_CNTW__DEBUG_COWWISION_MASK                                                               0x00040000W
#define ATC_ATS_MISC_CNTW__EFFECTIVE_TWANS_WOWK_QUEUE_MASK                                                    0x1FF80000W
#define ATC_ATS_MISC_CNTW__TWANS_WESP_NUWW_PASID_SEW_MASK                                                     0x20000000W
#define ATC_ATS_MISC_CNTW__WESEWVED_MASK                                                                      0xC0000000W
//ATC_ATS_STATUS
#define ATC_ATS_STATUS__BUSY__SHIFT                                                                           0x0
#define ATC_ATS_STATUS__CWASHED__SHIFT                                                                        0x1
#define ATC_ATS_STATUS__DEADWOCK_DETECTION__SHIFT                                                             0x2
#define ATC_ATS_STATUS__FED_IND__SHIFT                                                                        0x3
#define ATC_ATS_STATUS__BUSY_MASK                                                                             0x00000001W
#define ATC_ATS_STATUS__CWASHED_MASK                                                                          0x00000002W
#define ATC_ATS_STATUS__DEADWOCK_DETECTION_MASK                                                               0x00000004W
#define ATC_ATS_STATUS__FED_IND_MASK                                                                          0x00000008W
//ATC_PEWFCOUNTEW0_CFG
#define ATC_PEWFCOUNTEW0_CFG__PEWF_SEW__SHIFT                                                                 0x0
#define ATC_PEWFCOUNTEW0_CFG__PEWF_SEW_END__SHIFT                                                             0x8
#define ATC_PEWFCOUNTEW0_CFG__PEWF_MODE__SHIFT                                                                0x18
#define ATC_PEWFCOUNTEW0_CFG__ENABWE__SHIFT                                                                   0x1c
#define ATC_PEWFCOUNTEW0_CFG__CWEAW__SHIFT                                                                    0x1d
#define ATC_PEWFCOUNTEW0_CFG__PEWF_SEW_MASK                                                                   0x000000FFW
#define ATC_PEWFCOUNTEW0_CFG__PEWF_SEW_END_MASK                                                               0x0000FF00W
#define ATC_PEWFCOUNTEW0_CFG__PEWF_MODE_MASK                                                                  0x0F000000W
#define ATC_PEWFCOUNTEW0_CFG__ENABWE_MASK                                                                     0x10000000W
#define ATC_PEWFCOUNTEW0_CFG__CWEAW_MASK                                                                      0x20000000W
//ATC_PEWFCOUNTEW1_CFG
#define ATC_PEWFCOUNTEW1_CFG__PEWF_SEW__SHIFT                                                                 0x0
#define ATC_PEWFCOUNTEW1_CFG__PEWF_SEW_END__SHIFT                                                             0x8
#define ATC_PEWFCOUNTEW1_CFG__PEWF_MODE__SHIFT                                                                0x18
#define ATC_PEWFCOUNTEW1_CFG__ENABWE__SHIFT                                                                   0x1c
#define ATC_PEWFCOUNTEW1_CFG__CWEAW__SHIFT                                                                    0x1d
#define ATC_PEWFCOUNTEW1_CFG__PEWF_SEW_MASK                                                                   0x000000FFW
#define ATC_PEWFCOUNTEW1_CFG__PEWF_SEW_END_MASK                                                               0x0000FF00W
#define ATC_PEWFCOUNTEW1_CFG__PEWF_MODE_MASK                                                                  0x0F000000W
#define ATC_PEWFCOUNTEW1_CFG__ENABWE_MASK                                                                     0x10000000W
#define ATC_PEWFCOUNTEW1_CFG__CWEAW_MASK                                                                      0x20000000W
//ATC_PEWFCOUNTEW2_CFG
#define ATC_PEWFCOUNTEW2_CFG__PEWF_SEW__SHIFT                                                                 0x0
#define ATC_PEWFCOUNTEW2_CFG__PEWF_SEW_END__SHIFT                                                             0x8
#define ATC_PEWFCOUNTEW2_CFG__PEWF_MODE__SHIFT                                                                0x18
#define ATC_PEWFCOUNTEW2_CFG__ENABWE__SHIFT                                                                   0x1c
#define ATC_PEWFCOUNTEW2_CFG__CWEAW__SHIFT                                                                    0x1d
#define ATC_PEWFCOUNTEW2_CFG__PEWF_SEW_MASK                                                                   0x000000FFW
#define ATC_PEWFCOUNTEW2_CFG__PEWF_SEW_END_MASK                                                               0x0000FF00W
#define ATC_PEWFCOUNTEW2_CFG__PEWF_MODE_MASK                                                                  0x0F000000W
#define ATC_PEWFCOUNTEW2_CFG__ENABWE_MASK                                                                     0x10000000W
#define ATC_PEWFCOUNTEW2_CFG__CWEAW_MASK                                                                      0x20000000W
//ATC_PEWFCOUNTEW3_CFG
#define ATC_PEWFCOUNTEW3_CFG__PEWF_SEW__SHIFT                                                                 0x0
#define ATC_PEWFCOUNTEW3_CFG__PEWF_SEW_END__SHIFT                                                             0x8
#define ATC_PEWFCOUNTEW3_CFG__PEWF_MODE__SHIFT                                                                0x18
#define ATC_PEWFCOUNTEW3_CFG__ENABWE__SHIFT                                                                   0x1c
#define ATC_PEWFCOUNTEW3_CFG__CWEAW__SHIFT                                                                    0x1d
#define ATC_PEWFCOUNTEW3_CFG__PEWF_SEW_MASK                                                                   0x000000FFW
#define ATC_PEWFCOUNTEW3_CFG__PEWF_SEW_END_MASK                                                               0x0000FF00W
#define ATC_PEWFCOUNTEW3_CFG__PEWF_MODE_MASK                                                                  0x0F000000W
#define ATC_PEWFCOUNTEW3_CFG__ENABWE_MASK                                                                     0x10000000W
#define ATC_PEWFCOUNTEW3_CFG__CWEAW_MASK                                                                      0x20000000W
//ATC_PEWFCOUNTEW_WSWT_CNTW
#define ATC_PEWFCOUNTEW_WSWT_CNTW__PEWF_COUNTEW_SEWECT__SHIFT                                                 0x0
#define ATC_PEWFCOUNTEW_WSWT_CNTW__STAWT_TWIGGEW__SHIFT                                                       0x8
#define ATC_PEWFCOUNTEW_WSWT_CNTW__STOP_TWIGGEW__SHIFT                                                        0x10
#define ATC_PEWFCOUNTEW_WSWT_CNTW__ENABWE_ANY__SHIFT                                                          0x18
#define ATC_PEWFCOUNTEW_WSWT_CNTW__CWEAW_AWW__SHIFT                                                           0x19
#define ATC_PEWFCOUNTEW_WSWT_CNTW__STOP_AWW_ON_SATUWATE__SHIFT                                                0x1a
#define ATC_PEWFCOUNTEW_WSWT_CNTW__PEWF_COUNTEW_SEWECT_MASK                                                   0x0000000FW
#define ATC_PEWFCOUNTEW_WSWT_CNTW__STAWT_TWIGGEW_MASK                                                         0x0000FF00W
#define ATC_PEWFCOUNTEW_WSWT_CNTW__STOP_TWIGGEW_MASK                                                          0x00FF0000W
#define ATC_PEWFCOUNTEW_WSWT_CNTW__ENABWE_ANY_MASK                                                            0x01000000W
#define ATC_PEWFCOUNTEW_WSWT_CNTW__CWEAW_AWW_MASK                                                             0x02000000W
#define ATC_PEWFCOUNTEW_WSWT_CNTW__STOP_AWW_ON_SATUWATE_MASK                                                  0x04000000W
//ATC_PEWFCOUNTEW_WO
#define ATC_PEWFCOUNTEW_WO__COUNTEW_WO__SHIFT                                                                 0x0
#define ATC_PEWFCOUNTEW_WO__COUNTEW_WO_MASK                                                                   0xFFFFFFFFW
//ATC_PEWFCOUNTEW_HI
#define ATC_PEWFCOUNTEW_HI__COUNTEW_HI__SHIFT                                                                 0x0
#define ATC_PEWFCOUNTEW_HI__COMPAWE_VAWUE__SHIFT                                                              0x10
#define ATC_PEWFCOUNTEW_HI__COUNTEW_HI_MASK                                                                   0x0000FFFFW
#define ATC_PEWFCOUNTEW_HI__COMPAWE_VAWUE_MASK                                                                0xFFFF0000W
//ATC_ATS_FAUWT_CNTW
#define ATC_ATS_FAUWT_CNTW__FAUWT_WEGISTEW_WOG__SHIFT                                                         0x0
#define ATC_ATS_FAUWT_CNTW__FAUWT_INTEWWUPT_TABWE__SHIFT                                                      0xa
#define ATC_ATS_FAUWT_CNTW__FAUWT_CWASH_TABWE__SHIFT                                                          0x14
#define ATC_ATS_FAUWT_CNTW__FAUWT_WEGISTEW_WOG_MASK                                                           0x000001FFW
#define ATC_ATS_FAUWT_CNTW__FAUWT_INTEWWUPT_TABWE_MASK                                                        0x0007FC00W
#define ATC_ATS_FAUWT_CNTW__FAUWT_CWASH_TABWE_MASK                                                            0x1FF00000W
//ATC_ATS_FAUWT_STATUS_INFO
#define ATC_ATS_FAUWT_STATUS_INFO__FAUWT_TYPE__SHIFT                                                          0x0
#define ATC_ATS_FAUWT_STATUS_INFO__VMID_AWW__SHIFT                                                            0x9
#define ATC_ATS_FAUWT_STATUS_INFO__VMID__SHIFT                                                                0xa
#define ATC_ATS_FAUWT_STATUS_INFO__EXTWA_INFO__SHIFT                                                          0xf
#define ATC_ATS_FAUWT_STATUS_INFO__EXTWA_INFO2__SHIFT                                                         0x10
#define ATC_ATS_FAUWT_STATUS_INFO__INVAWIDATION__SHIFT                                                        0x11
#define ATC_ATS_FAUWT_STATUS_INFO__PAGE_WEQUEST__SHIFT                                                        0x12
#define ATC_ATS_FAUWT_STATUS_INFO__STATUS__SHIFT                                                              0x13
#define ATC_ATS_FAUWT_STATUS_INFO__PAGE_ADDW_HIGH__SHIFT                                                      0x18
#define ATC_ATS_FAUWT_STATUS_INFO__PHYSICAW_ADDW_HIGH__SHIFT                                                  0x1c
#define ATC_ATS_FAUWT_STATUS_INFO__FAUWT_TYPE_MASK                                                            0x000001FFW
#define ATC_ATS_FAUWT_STATUS_INFO__VMID_AWW_MASK                                                              0x00000200W
#define ATC_ATS_FAUWT_STATUS_INFO__VMID_MASK                                                                  0x00007C00W
#define ATC_ATS_FAUWT_STATUS_INFO__EXTWA_INFO_MASK                                                            0x00008000W
#define ATC_ATS_FAUWT_STATUS_INFO__EXTWA_INFO2_MASK                                                           0x00010000W
#define ATC_ATS_FAUWT_STATUS_INFO__INVAWIDATION_MASK                                                          0x00020000W
#define ATC_ATS_FAUWT_STATUS_INFO__PAGE_WEQUEST_MASK                                                          0x00040000W
#define ATC_ATS_FAUWT_STATUS_INFO__STATUS_MASK                                                                0x00F80000W
#define ATC_ATS_FAUWT_STATUS_INFO__PAGE_ADDW_HIGH_MASK                                                        0x0F000000W
#define ATC_ATS_FAUWT_STATUS_INFO__PHYSICAW_ADDW_HIGH_MASK                                                    0xF0000000W
//ATC_ATS_FAUWT_STATUS_INFO2
#define ATC_ATS_FAUWT_STATUS_INFO2__VF__SHIFT                                                                 0x0
#define ATC_ATS_FAUWT_STATUS_INFO2__VFID__SHIFT                                                               0x1
#define ATC_ATS_FAUWT_STATUS_INFO2__W2NUM__SHIFT                                                              0x9
#define ATC_ATS_FAUWT_STATUS_INFO2__INV_VMID_GFX1__SHIFT                                                      0xd
#define ATC_ATS_FAUWT_STATUS_INFO2__INV_VMID_GFX2__SHIFT                                                      0x13
#define ATC_ATS_FAUWT_STATUS_INFO2__INV_VMID_GFX3__SHIFT                                                      0x19
#define ATC_ATS_FAUWT_STATUS_INFO2__VF_MASK                                                                   0x00000001W
#define ATC_ATS_FAUWT_STATUS_INFO2__VFID_MASK                                                                 0x0000001EW
#define ATC_ATS_FAUWT_STATUS_INFO2__W2NUM_MASK                                                                0x00001E00W
#define ATC_ATS_FAUWT_STATUS_INFO2__INV_VMID_GFX1_MASK                                                        0x0007E000W
#define ATC_ATS_FAUWT_STATUS_INFO2__INV_VMID_GFX2_MASK                                                        0x01F80000W
#define ATC_ATS_FAUWT_STATUS_INFO2__INV_VMID_GFX3_MASK                                                        0x7E000000W
//ATC_ATS_FAUWT_STATUS_INFO3
#define ATC_ATS_FAUWT_STATUS_INFO3__INV_VMID_GFX4__SHIFT                                                      0x0
#define ATC_ATS_FAUWT_STATUS_INFO3__INV_VMID_GFX5__SHIFT                                                      0x6
#define ATC_ATS_FAUWT_STATUS_INFO3__INV_VMID_GFX6__SHIFT                                                      0xc
#define ATC_ATS_FAUWT_STATUS_INFO3__INV_VMID_GFX7__SHIFT                                                      0x12
#define ATC_ATS_FAUWT_STATUS_INFO3__INV_VMID_MM0__SHIFT                                                       0x18
#define ATC_ATS_FAUWT_STATUS_INFO3__INV_VMID_GFX4_MASK                                                        0x0000003FW
#define ATC_ATS_FAUWT_STATUS_INFO3__INV_VMID_GFX5_MASK                                                        0x00000FC0W
#define ATC_ATS_FAUWT_STATUS_INFO3__INV_VMID_GFX6_MASK                                                        0x0003F000W
#define ATC_ATS_FAUWT_STATUS_INFO3__INV_VMID_GFX7_MASK                                                        0x00FC0000W
#define ATC_ATS_FAUWT_STATUS_INFO3__INV_VMID_MM0_MASK                                                         0x3F000000W
//ATC_ATS_FAUWT_STATUS_INFO4
#define ATC_ATS_FAUWT_STATUS_INFO4__INV_VMID_MM1__SHIFT                                                       0x0
#define ATC_ATS_FAUWT_STATUS_INFO4__INV_VMID_MM2__SHIFT                                                       0x6
#define ATC_ATS_FAUWT_STATUS_INFO4__INV_VMID_MM3__SHIFT                                                       0xc
#define ATC_ATS_FAUWT_STATUS_INFO4__INV_VMID_MM1_MASK                                                         0x0000003FW
#define ATC_ATS_FAUWT_STATUS_INFO4__INV_VMID_MM2_MASK                                                         0x00000FC0W
#define ATC_ATS_FAUWT_STATUS_INFO4__INV_VMID_MM3_MASK                                                         0x0003F000W
//ATC_ATS_FAUWT_STATUS_ADDW
#define ATC_ATS_FAUWT_STATUS_ADDW__PAGE_ADDW__SHIFT                                                           0x0
#define ATC_ATS_FAUWT_STATUS_ADDW__PAGE_ADDW_MASK                                                             0xFFFFFFFFW
//ATC_ATS_DEFAUWT_PAGE_WOW
#define ATC_ATS_DEFAUWT_PAGE_WOW__DEFAUWT_PAGE__SHIFT                                                         0x0
#define ATC_ATS_DEFAUWT_PAGE_WOW__DEFAUWT_PAGE_MASK                                                           0xFFFFFFFFW
//ATHUB_PCIE_ATS_CNTW
#define ATHUB_PCIE_ATS_CNTW__STU__SHIFT                                                                       0x10
#define ATHUB_PCIE_ATS_CNTW__ATC_ENABWE__SHIFT                                                                0x1f
#define ATHUB_PCIE_ATS_CNTW__STU_MASK                                                                         0x001F0000W
#define ATHUB_PCIE_ATS_CNTW__ATC_ENABWE_MASK                                                                  0x80000000W
//ATHUB_PCIE_PASID_CNTW
#define ATHUB_PCIE_PASID_CNTW__PASID_EN__SHIFT                                                                0x10
#define ATHUB_PCIE_PASID_CNTW__PASID_EXE_PEWMISSION_ENABWE__SHIFT                                             0x11
#define ATHUB_PCIE_PASID_CNTW__PASID_PWIV_MODE_SUPPOWTED_ENABWE__SHIFT                                        0x12
#define ATHUB_PCIE_PASID_CNTW__PASID_EN_MASK                                                                  0x00010000W
#define ATHUB_PCIE_PASID_CNTW__PASID_EXE_PEWMISSION_ENABWE_MASK                                               0x00020000W
#define ATHUB_PCIE_PASID_CNTW__PASID_PWIV_MODE_SUPPOWTED_ENABWE_MASK                                          0x00040000W
//ATHUB_PCIE_PAGE_WEQ_CNTW
#define ATHUB_PCIE_PAGE_WEQ_CNTW__PWI_ENABWE__SHIFT                                                           0x0
#define ATHUB_PCIE_PAGE_WEQ_CNTW__PWI_WESET__SHIFT                                                            0x1
#define ATHUB_PCIE_PAGE_WEQ_CNTW__PWI_ENABWE_MASK                                                             0x00000001W
#define ATHUB_PCIE_PAGE_WEQ_CNTW__PWI_WESET_MASK                                                              0x00000002W
//ATHUB_PCIE_OUTSTAND_PAGE_WEQ_AWWOC
#define ATHUB_PCIE_OUTSTAND_PAGE_WEQ_AWWOC__OUTSTAND_PAGE_WEQ_AWWOC__SHIFT                                    0x0
#define ATHUB_PCIE_OUTSTAND_PAGE_WEQ_AWWOC__OUTSTAND_PAGE_WEQ_AWWOC_MASK                                      0xFFFFFFFFW
//ATHUB_COMMAND
#define ATHUB_COMMAND__BUS_MASTEW_EN__SHIFT                                                                   0x2
#define ATHUB_COMMAND__BUS_MASTEW_EN_MASK                                                                     0x00000004W
//ATHUB_PCIE_ATS_CNTW_VF_0
#define ATHUB_PCIE_ATS_CNTW_VF_0__ATC_ENABWE__SHIFT                                                           0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_0__ATC_ENABWE_MASK                                                             0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_1
#define ATHUB_PCIE_ATS_CNTW_VF_1__ATC_ENABWE__SHIFT                                                           0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_1__ATC_ENABWE_MASK                                                             0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_2
#define ATHUB_PCIE_ATS_CNTW_VF_2__ATC_ENABWE__SHIFT                                                           0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_2__ATC_ENABWE_MASK                                                             0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_3
#define ATHUB_PCIE_ATS_CNTW_VF_3__ATC_ENABWE__SHIFT                                                           0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_3__ATC_ENABWE_MASK                                                             0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_4
#define ATHUB_PCIE_ATS_CNTW_VF_4__ATC_ENABWE__SHIFT                                                           0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_4__ATC_ENABWE_MASK                                                             0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_5
#define ATHUB_PCIE_ATS_CNTW_VF_5__ATC_ENABWE__SHIFT                                                           0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_5__ATC_ENABWE_MASK                                                             0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_6
#define ATHUB_PCIE_ATS_CNTW_VF_6__ATC_ENABWE__SHIFT                                                           0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_6__ATC_ENABWE_MASK                                                             0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_7
#define ATHUB_PCIE_ATS_CNTW_VF_7__ATC_ENABWE__SHIFT                                                           0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_7__ATC_ENABWE_MASK                                                             0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_8
#define ATHUB_PCIE_ATS_CNTW_VF_8__ATC_ENABWE__SHIFT                                                           0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_8__ATC_ENABWE_MASK                                                             0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_9
#define ATHUB_PCIE_ATS_CNTW_VF_9__ATC_ENABWE__SHIFT                                                           0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_9__ATC_ENABWE_MASK                                                             0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_10
#define ATHUB_PCIE_ATS_CNTW_VF_10__ATC_ENABWE__SHIFT                                                          0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_10__ATC_ENABWE_MASK                                                            0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_11
#define ATHUB_PCIE_ATS_CNTW_VF_11__ATC_ENABWE__SHIFT                                                          0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_11__ATC_ENABWE_MASK                                                            0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_12
#define ATHUB_PCIE_ATS_CNTW_VF_12__ATC_ENABWE__SHIFT                                                          0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_12__ATC_ENABWE_MASK                                                            0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_13
#define ATHUB_PCIE_ATS_CNTW_VF_13__ATC_ENABWE__SHIFT                                                          0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_13__ATC_ENABWE_MASK                                                            0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_14
#define ATHUB_PCIE_ATS_CNTW_VF_14__ATC_ENABWE__SHIFT                                                          0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_14__ATC_ENABWE_MASK                                                            0x80000000W
//ATHUB_PCIE_ATS_CNTW_VF_15
#define ATHUB_PCIE_ATS_CNTW_VF_15__ATC_ENABWE__SHIFT                                                          0x1f
#define ATHUB_PCIE_ATS_CNTW_VF_15__ATC_ENABWE_MASK                                                            0x80000000W
//ATHUB_SHAWED_VIWT_WESET_WEQ
#define ATHUB_SHAWED_VIWT_WESET_WEQ__VF__SHIFT                                                                0x0
#define ATHUB_SHAWED_VIWT_WESET_WEQ__PF__SHIFT                                                                0x1f
#define ATHUB_SHAWED_VIWT_WESET_WEQ__VF_MASK                                                                  0x0000FFFFW
#define ATHUB_SHAWED_VIWT_WESET_WEQ__PF_MASK                                                                  0x80000000W
//ATHUB_SHAWED_ACTIVE_FCN_ID
#define ATHUB_SHAWED_ACTIVE_FCN_ID__VFID__SHIFT                                                               0x0
#define ATHUB_SHAWED_ACTIVE_FCN_ID__VF__SHIFT                                                                 0x1f
#define ATHUB_SHAWED_ACTIVE_FCN_ID__VFID_MASK                                                                 0x0000000FW
#define ATHUB_SHAWED_ACTIVE_FCN_ID__VF_MASK                                                                   0x80000000W
//ATC_ATS_SDPPOWT_CNTW
#define ATC_ATS_SDPPOWT_CNTW__ATS_INV_SEWF_ACTIVATE__SHIFT                                                    0x0
#define ATC_ATS_SDPPOWT_CNTW__ATS_INV_CFG_MODE__SHIFT                                                         0x1
#define ATC_ATS_SDPPOWT_CNTW__ATS_INV_HAWT_THWESHOWD__SHIFT                                                   0x3
#define ATC_ATS_SDPPOWT_CNTW__ATS_INV_WEISSUE_CWEDIT__SHIFT                                                   0x7
#define ATC_ATS_SDPPOWT_CNTW__ATS_INV_ENABWE_DISWUPT_FUWWDIS__SHIFT                                           0x8
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_SEWF_ACTIVATE__SHIFT                                                0x9
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_QUICK_COMACK__SHIFT                                                 0xa
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_HAWT_THWESHOWD__SHIFT                                               0xb
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_PASSIVE_MODE__SHIFT                                                 0xf
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_WDY_MODE__SHIFT                                                           0x10
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_WEISSUE_CWEDIT__SHIFT                                               0x11
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_ENABWE_DISWUPT_FUWWDIS__SHIFT                                       0x12
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_INVAWWEQ_WDWSPSTATUS_CNTW__SHIFT                                    0x13
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WDWSPCKEN__SHIFT                                              0x16
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WDWSPCKENWCV__SHIFT                                           0x17
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WDWSPDATACKEN__SHIFT                                          0x18
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WDWSPDATACKENWCV__SHIFT                                       0x19
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WWWSPCKEN__SHIFT                                              0x1a
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WWWSPCKENWCV__SHIFT                                           0x1b
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WEQCKEN__SHIFT                                                0x1c
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WEQCKENWCV__SHIFT                                             0x1d
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_OWIGDATACKEN__SHIFT                                           0x1e
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_OWIGDATACKENWCV__SHIFT                                        0x1f
#define ATC_ATS_SDPPOWT_CNTW__ATS_INV_SEWF_ACTIVATE_MASK                                                      0x00000001W
#define ATC_ATS_SDPPOWT_CNTW__ATS_INV_CFG_MODE_MASK                                                           0x00000006W
#define ATC_ATS_SDPPOWT_CNTW__ATS_INV_HAWT_THWESHOWD_MASK                                                     0x00000078W
#define ATC_ATS_SDPPOWT_CNTW__ATS_INV_WEISSUE_CWEDIT_MASK                                                     0x00000080W
#define ATC_ATS_SDPPOWT_CNTW__ATS_INV_ENABWE_DISWUPT_FUWWDIS_MASK                                             0x00000100W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_SEWF_ACTIVATE_MASK                                                  0x00000200W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_QUICK_COMACK_MASK                                                   0x00000400W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_HAWT_THWESHOWD_MASK                                                 0x00007800W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_PASSIVE_MODE_MASK                                                   0x00008000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_WDY_MODE_MASK                                                             0x00010000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_WEISSUE_CWEDIT_MASK                                                 0x00020000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_ENABWE_DISWUPT_FUWWDIS_MASK                                         0x00040000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_TWANS_INVAWWEQ_WDWSPSTATUS_CNTW_MASK                                      0x00380000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WDWSPCKEN_MASK                                                0x00400000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WDWSPCKENWCV_MASK                                             0x00800000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WDWSPDATACKEN_MASK                                            0x01000000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WDWSPDATACKENWCV_MASK                                         0x02000000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WWWSPCKEN_MASK                                                0x04000000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WWWSPCKENWCV_MASK                                             0x08000000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WEQCKEN_MASK                                                  0x10000000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_WEQCKENWCV_MASK                                               0x20000000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_OWIGDATACKEN_MASK                                             0x40000000W
#define ATC_ATS_SDPPOWT_CNTW__UTCW2_GFX_SDPVDCI_OWIGDATACKENWCV_MASK                                          0x80000000W
//ATC_VMID_PASID_MAPPING_UPDATE_STATUS
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID0_WEMAPPING_FINISHED__SHIFT                                 0x0
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID1_WEMAPPING_FINISHED__SHIFT                                 0x1
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID2_WEMAPPING_FINISHED__SHIFT                                 0x2
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID3_WEMAPPING_FINISHED__SHIFT                                 0x3
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID4_WEMAPPING_FINISHED__SHIFT                                 0x4
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID5_WEMAPPING_FINISHED__SHIFT                                 0x5
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID6_WEMAPPING_FINISHED__SHIFT                                 0x6
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID7_WEMAPPING_FINISHED__SHIFT                                 0x7
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID8_WEMAPPING_FINISHED__SHIFT                                 0x8
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID9_WEMAPPING_FINISHED__SHIFT                                 0x9
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID10_WEMAPPING_FINISHED__SHIFT                                0xa
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID11_WEMAPPING_FINISHED__SHIFT                                0xb
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID12_WEMAPPING_FINISHED__SHIFT                                0xc
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID13_WEMAPPING_FINISHED__SHIFT                                0xd
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID14_WEMAPPING_FINISHED__SHIFT                                0xe
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID15_WEMAPPING_FINISHED__SHIFT                                0xf
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID0_WEMAPPING_FINISHED_MASK                                   0x00000001W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID1_WEMAPPING_FINISHED_MASK                                   0x00000002W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID2_WEMAPPING_FINISHED_MASK                                   0x00000004W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID3_WEMAPPING_FINISHED_MASK                                   0x00000008W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID4_WEMAPPING_FINISHED_MASK                                   0x00000010W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID5_WEMAPPING_FINISHED_MASK                                   0x00000020W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID6_WEMAPPING_FINISHED_MASK                                   0x00000040W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID7_WEMAPPING_FINISHED_MASK                                   0x00000080W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID8_WEMAPPING_FINISHED_MASK                                   0x00000100W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID9_WEMAPPING_FINISHED_MASK                                   0x00000200W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID10_WEMAPPING_FINISHED_MASK                                  0x00000400W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID11_WEMAPPING_FINISHED_MASK                                  0x00000800W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID12_WEMAPPING_FINISHED_MASK                                  0x00001000W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID13_WEMAPPING_FINISHED_MASK                                  0x00002000W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID14_WEMAPPING_FINISHED_MASK                                  0x00004000W
#define ATC_VMID_PASID_MAPPING_UPDATE_STATUS__VMID15_WEMAPPING_FINISHED_MASK                                  0x00008000W
//ATC_VMID0_PASID_MAPPING
#define ATC_VMID0_PASID_MAPPING__PASID__SHIFT                                                                 0x0
#define ATC_VMID0_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                       0x1e
#define ATC_VMID0_PASID_MAPPING__VAWID__SHIFT                                                                 0x1f
#define ATC_VMID0_PASID_MAPPING__PASID_MASK                                                                   0x0000FFFFW
#define ATC_VMID0_PASID_MAPPING__NO_INVAWIDATION_MASK                                                         0x40000000W
#define ATC_VMID0_PASID_MAPPING__VAWID_MASK                                                                   0x80000000W
//ATC_VMID1_PASID_MAPPING
#define ATC_VMID1_PASID_MAPPING__PASID__SHIFT                                                                 0x0
#define ATC_VMID1_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                       0x1e
#define ATC_VMID1_PASID_MAPPING__VAWID__SHIFT                                                                 0x1f
#define ATC_VMID1_PASID_MAPPING__PASID_MASK                                                                   0x0000FFFFW
#define ATC_VMID1_PASID_MAPPING__NO_INVAWIDATION_MASK                                                         0x40000000W
#define ATC_VMID1_PASID_MAPPING__VAWID_MASK                                                                   0x80000000W
//ATC_VMID2_PASID_MAPPING
#define ATC_VMID2_PASID_MAPPING__PASID__SHIFT                                                                 0x0
#define ATC_VMID2_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                       0x1e
#define ATC_VMID2_PASID_MAPPING__VAWID__SHIFT                                                                 0x1f
#define ATC_VMID2_PASID_MAPPING__PASID_MASK                                                                   0x0000FFFFW
#define ATC_VMID2_PASID_MAPPING__NO_INVAWIDATION_MASK                                                         0x40000000W
#define ATC_VMID2_PASID_MAPPING__VAWID_MASK                                                                   0x80000000W
//ATC_VMID3_PASID_MAPPING
#define ATC_VMID3_PASID_MAPPING__PASID__SHIFT                                                                 0x0
#define ATC_VMID3_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                       0x1e
#define ATC_VMID3_PASID_MAPPING__VAWID__SHIFT                                                                 0x1f
#define ATC_VMID3_PASID_MAPPING__PASID_MASK                                                                   0x0000FFFFW
#define ATC_VMID3_PASID_MAPPING__NO_INVAWIDATION_MASK                                                         0x40000000W
#define ATC_VMID3_PASID_MAPPING__VAWID_MASK                                                                   0x80000000W
//ATC_VMID4_PASID_MAPPING
#define ATC_VMID4_PASID_MAPPING__PASID__SHIFT                                                                 0x0
#define ATC_VMID4_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                       0x1e
#define ATC_VMID4_PASID_MAPPING__VAWID__SHIFT                                                                 0x1f
#define ATC_VMID4_PASID_MAPPING__PASID_MASK                                                                   0x0000FFFFW
#define ATC_VMID4_PASID_MAPPING__NO_INVAWIDATION_MASK                                                         0x40000000W
#define ATC_VMID4_PASID_MAPPING__VAWID_MASK                                                                   0x80000000W
//ATC_VMID5_PASID_MAPPING
#define ATC_VMID5_PASID_MAPPING__PASID__SHIFT                                                                 0x0
#define ATC_VMID5_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                       0x1e
#define ATC_VMID5_PASID_MAPPING__VAWID__SHIFT                                                                 0x1f
#define ATC_VMID5_PASID_MAPPING__PASID_MASK                                                                   0x0000FFFFW
#define ATC_VMID5_PASID_MAPPING__NO_INVAWIDATION_MASK                                                         0x40000000W
#define ATC_VMID5_PASID_MAPPING__VAWID_MASK                                                                   0x80000000W
//ATC_VMID6_PASID_MAPPING
#define ATC_VMID6_PASID_MAPPING__PASID__SHIFT                                                                 0x0
#define ATC_VMID6_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                       0x1e
#define ATC_VMID6_PASID_MAPPING__VAWID__SHIFT                                                                 0x1f
#define ATC_VMID6_PASID_MAPPING__PASID_MASK                                                                   0x0000FFFFW
#define ATC_VMID6_PASID_MAPPING__NO_INVAWIDATION_MASK                                                         0x40000000W
#define ATC_VMID6_PASID_MAPPING__VAWID_MASK                                                                   0x80000000W
//ATC_VMID7_PASID_MAPPING
#define ATC_VMID7_PASID_MAPPING__PASID__SHIFT                                                                 0x0
#define ATC_VMID7_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                       0x1e
#define ATC_VMID7_PASID_MAPPING__VAWID__SHIFT                                                                 0x1f
#define ATC_VMID7_PASID_MAPPING__PASID_MASK                                                                   0x0000FFFFW
#define ATC_VMID7_PASID_MAPPING__NO_INVAWIDATION_MASK                                                         0x40000000W
#define ATC_VMID7_PASID_MAPPING__VAWID_MASK                                                                   0x80000000W
//ATC_VMID8_PASID_MAPPING
#define ATC_VMID8_PASID_MAPPING__PASID__SHIFT                                                                 0x0
#define ATC_VMID8_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                       0x1e
#define ATC_VMID8_PASID_MAPPING__VAWID__SHIFT                                                                 0x1f
#define ATC_VMID8_PASID_MAPPING__PASID_MASK                                                                   0x0000FFFFW
#define ATC_VMID8_PASID_MAPPING__NO_INVAWIDATION_MASK                                                         0x40000000W
#define ATC_VMID8_PASID_MAPPING__VAWID_MASK                                                                   0x80000000W
//ATC_VMID9_PASID_MAPPING
#define ATC_VMID9_PASID_MAPPING__PASID__SHIFT                                                                 0x0
#define ATC_VMID9_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                       0x1e
#define ATC_VMID9_PASID_MAPPING__VAWID__SHIFT                                                                 0x1f
#define ATC_VMID9_PASID_MAPPING__PASID_MASK                                                                   0x0000FFFFW
#define ATC_VMID9_PASID_MAPPING__NO_INVAWIDATION_MASK                                                         0x40000000W
#define ATC_VMID9_PASID_MAPPING__VAWID_MASK                                                                   0x80000000W
//ATC_VMID10_PASID_MAPPING
#define ATC_VMID10_PASID_MAPPING__PASID__SHIFT                                                                0x0
#define ATC_VMID10_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                      0x1e
#define ATC_VMID10_PASID_MAPPING__VAWID__SHIFT                                                                0x1f
#define ATC_VMID10_PASID_MAPPING__PASID_MASK                                                                  0x0000FFFFW
#define ATC_VMID10_PASID_MAPPING__NO_INVAWIDATION_MASK                                                        0x40000000W
#define ATC_VMID10_PASID_MAPPING__VAWID_MASK                                                                  0x80000000W
//ATC_VMID11_PASID_MAPPING
#define ATC_VMID11_PASID_MAPPING__PASID__SHIFT                                                                0x0
#define ATC_VMID11_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                      0x1e
#define ATC_VMID11_PASID_MAPPING__VAWID__SHIFT                                                                0x1f
#define ATC_VMID11_PASID_MAPPING__PASID_MASK                                                                  0x0000FFFFW
#define ATC_VMID11_PASID_MAPPING__NO_INVAWIDATION_MASK                                                        0x40000000W
#define ATC_VMID11_PASID_MAPPING__VAWID_MASK                                                                  0x80000000W
//ATC_VMID12_PASID_MAPPING
#define ATC_VMID12_PASID_MAPPING__PASID__SHIFT                                                                0x0
#define ATC_VMID12_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                      0x1e
#define ATC_VMID12_PASID_MAPPING__VAWID__SHIFT                                                                0x1f
#define ATC_VMID12_PASID_MAPPING__PASID_MASK                                                                  0x0000FFFFW
#define ATC_VMID12_PASID_MAPPING__NO_INVAWIDATION_MASK                                                        0x40000000W
#define ATC_VMID12_PASID_MAPPING__VAWID_MASK                                                                  0x80000000W
//ATC_VMID13_PASID_MAPPING
#define ATC_VMID13_PASID_MAPPING__PASID__SHIFT                                                                0x0
#define ATC_VMID13_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                      0x1e
#define ATC_VMID13_PASID_MAPPING__VAWID__SHIFT                                                                0x1f
#define ATC_VMID13_PASID_MAPPING__PASID_MASK                                                                  0x0000FFFFW
#define ATC_VMID13_PASID_MAPPING__NO_INVAWIDATION_MASK                                                        0x40000000W
#define ATC_VMID13_PASID_MAPPING__VAWID_MASK                                                                  0x80000000W
//ATC_VMID14_PASID_MAPPING
#define ATC_VMID14_PASID_MAPPING__PASID__SHIFT                                                                0x0
#define ATC_VMID14_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                      0x1e
#define ATC_VMID14_PASID_MAPPING__VAWID__SHIFT                                                                0x1f
#define ATC_VMID14_PASID_MAPPING__PASID_MASK                                                                  0x0000FFFFW
#define ATC_VMID14_PASID_MAPPING__NO_INVAWIDATION_MASK                                                        0x40000000W
#define ATC_VMID14_PASID_MAPPING__VAWID_MASK                                                                  0x80000000W
//ATC_VMID15_PASID_MAPPING
#define ATC_VMID15_PASID_MAPPING__PASID__SHIFT                                                                0x0
#define ATC_VMID15_PASID_MAPPING__NO_INVAWIDATION__SHIFT                                                      0x1e
#define ATC_VMID15_PASID_MAPPING__VAWID__SHIFT                                                                0x1f
#define ATC_VMID15_PASID_MAPPING__PASID_MASK                                                                  0x0000FFFFW
#define ATC_VMID15_PASID_MAPPING__NO_INVAWIDATION_MASK                                                        0x40000000W
#define ATC_VMID15_PASID_MAPPING__VAWID_MASK                                                                  0x80000000W
//ATC_TWANS_FAUWT_WSPCNTWW
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID0__SHIFT                                                                0x0
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID1__SHIFT                                                                0x1
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID2__SHIFT                                                                0x2
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID3__SHIFT                                                                0x3
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID4__SHIFT                                                                0x4
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID5__SHIFT                                                                0x5
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID6__SHIFT                                                                0x6
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID7__SHIFT                                                                0x7
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID8__SHIFT                                                                0x8
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID9__SHIFT                                                                0x9
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID10__SHIFT                                                               0xa
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID11__SHIFT                                                               0xb
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID12__SHIFT                                                               0xc
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID13__SHIFT                                                               0xd
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID14__SHIFT                                                               0xe
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID15__SHIFT                                                               0xf
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID0_MASK                                                                  0x00000001W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID1_MASK                                                                  0x00000002W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID2_MASK                                                                  0x00000004W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID3_MASK                                                                  0x00000008W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID4_MASK                                                                  0x00000010W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID5_MASK                                                                  0x00000020W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID6_MASK                                                                  0x00000040W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID7_MASK                                                                  0x00000080W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID8_MASK                                                                  0x00000100W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID9_MASK                                                                  0x00000200W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID10_MASK                                                                 0x00000400W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID11_MASK                                                                 0x00000800W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID12_MASK                                                                 0x00001000W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID13_MASK                                                                 0x00002000W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID14_MASK                                                                 0x00004000W
#define ATC_TWANS_FAUWT_WSPCNTWW__VMID15_MASK                                                                 0x00008000W
//ATC_ATS_VMID_STATUS
#define ATC_ATS_VMID_STATUS__VMID0_OUTSTANDING__SHIFT                                                         0x0
#define ATC_ATS_VMID_STATUS__VMID1_OUTSTANDING__SHIFT                                                         0x1
#define ATC_ATS_VMID_STATUS__VMID2_OUTSTANDING__SHIFT                                                         0x2
#define ATC_ATS_VMID_STATUS__VMID3_OUTSTANDING__SHIFT                                                         0x3
#define ATC_ATS_VMID_STATUS__VMID4_OUTSTANDING__SHIFT                                                         0x4
#define ATC_ATS_VMID_STATUS__VMID5_OUTSTANDING__SHIFT                                                         0x5
#define ATC_ATS_VMID_STATUS__VMID6_OUTSTANDING__SHIFT                                                         0x6
#define ATC_ATS_VMID_STATUS__VMID7_OUTSTANDING__SHIFT                                                         0x7
#define ATC_ATS_VMID_STATUS__VMID8_OUTSTANDING__SHIFT                                                         0x8
#define ATC_ATS_VMID_STATUS__VMID9_OUTSTANDING__SHIFT                                                         0x9
#define ATC_ATS_VMID_STATUS__VMID10_OUTSTANDING__SHIFT                                                        0xa
#define ATC_ATS_VMID_STATUS__VMID11_OUTSTANDING__SHIFT                                                        0xb
#define ATC_ATS_VMID_STATUS__VMID12_OUTSTANDING__SHIFT                                                        0xc
#define ATC_ATS_VMID_STATUS__VMID13_OUTSTANDING__SHIFT                                                        0xd
#define ATC_ATS_VMID_STATUS__VMID14_OUTSTANDING__SHIFT                                                        0xe
#define ATC_ATS_VMID_STATUS__VMID15_OUTSTANDING__SHIFT                                                        0xf
#define ATC_ATS_VMID_STATUS__VMID0_OUTSTANDING_MASK                                                           0x00000001W
#define ATC_ATS_VMID_STATUS__VMID1_OUTSTANDING_MASK                                                           0x00000002W
#define ATC_ATS_VMID_STATUS__VMID2_OUTSTANDING_MASK                                                           0x00000004W
#define ATC_ATS_VMID_STATUS__VMID3_OUTSTANDING_MASK                                                           0x00000008W
#define ATC_ATS_VMID_STATUS__VMID4_OUTSTANDING_MASK                                                           0x00000010W
#define ATC_ATS_VMID_STATUS__VMID5_OUTSTANDING_MASK                                                           0x00000020W
#define ATC_ATS_VMID_STATUS__VMID6_OUTSTANDING_MASK                                                           0x00000040W
#define ATC_ATS_VMID_STATUS__VMID7_OUTSTANDING_MASK                                                           0x00000080W
#define ATC_ATS_VMID_STATUS__VMID8_OUTSTANDING_MASK                                                           0x00000100W
#define ATC_ATS_VMID_STATUS__VMID9_OUTSTANDING_MASK                                                           0x00000200W
#define ATC_ATS_VMID_STATUS__VMID10_OUTSTANDING_MASK                                                          0x00000400W
#define ATC_ATS_VMID_STATUS__VMID11_OUTSTANDING_MASK                                                          0x00000800W
#define ATC_ATS_VMID_STATUS__VMID12_OUTSTANDING_MASK                                                          0x00001000W
#define ATC_ATS_VMID_STATUS__VMID13_OUTSTANDING_MASK                                                          0x00002000W
#define ATC_ATS_VMID_STATUS__VMID14_OUTSTANDING_MASK                                                          0x00004000W
#define ATC_ATS_VMID_STATUS__VMID15_OUTSTANDING_MASK                                                          0x00008000W
//ATHUB_MISC_CNTW
#define ATHUB_MISC_CNTW__CG_OFFDWY__SHIFT                                                                     0x6
#define ATHUB_MISC_CNTW__CG_ENABWE__SHIFT                                                                     0x12
#define ATHUB_MISC_CNTW__CG_MEM_WS_ENABWE__SHIFT                                                              0x13
#define ATHUB_MISC_CNTW__PG_ENABWE__SHIFT                                                                     0x14
#define ATHUB_MISC_CNTW__PG_OFFDWY__SHIFT                                                                     0x15
#define ATHUB_MISC_CNTW__CG_STATUS__SHIFT                                                                     0x1b
#define ATHUB_MISC_CNTW__PG_STATUS__SHIFT                                                                     0x1c
#define ATHUB_MISC_CNTW__SWAM_FGCG_ENABWE__SHIFT                                                              0x1d
#define ATHUB_MISC_CNTW__CG_OFFDWY_MASK                                                                       0x00000FC0W
#define ATHUB_MISC_CNTW__CG_ENABWE_MASK                                                                       0x00040000W
#define ATHUB_MISC_CNTW__CG_MEM_WS_ENABWE_MASK                                                                0x00080000W
#define ATHUB_MISC_CNTW__PG_ENABWE_MASK                                                                       0x00100000W
#define ATHUB_MISC_CNTW__PG_OFFDWY_MASK                                                                       0x07E00000W
#define ATHUB_MISC_CNTW__CG_STATUS_MASK                                                                       0x08000000W
#define ATHUB_MISC_CNTW__PG_STATUS_MASK                                                                       0x10000000W
#define ATHUB_MISC_CNTW__SWAM_FGCG_ENABWE_MASK                                                                0x20000000W
//ATHUB_MEM_POWEW_WS
#define ATHUB_MEM_POWEW_WS__WS_SETUP__SHIFT                                                                   0x0
#define ATHUB_MEM_POWEW_WS__WS_HOWD__SHIFT                                                                    0x6
#define ATHUB_MEM_POWEW_WS__WS_DEWAY_ENABWE__SHIFT                                                            0x13
#define ATHUB_MEM_POWEW_WS__WS_DEWAY_TIME__SHIFT                                                              0x14
#define ATHUB_MEM_POWEW_WS__WS_SETUP_MASK                                                                     0x0000003FW
#define ATHUB_MEM_POWEW_WS__WS_HOWD_MASK                                                                      0x0007FFC0W
#define ATHUB_MEM_POWEW_WS__WS_DEWAY_ENABWE_MASK                                                              0x00080000W
#define ATHUB_MEM_POWEW_WS__WS_DEWAY_TIME_MASK                                                                0x03F00000W
//ATHUB_IH_CWEDIT
#define ATHUB_IH_CWEDIT__CWEDIT_VAWUE__SHIFT                                                                  0x0
#define ATHUB_IH_CWEDIT__IH_CWIENT_ID__SHIFT                                                                  0x10
#define ATHUB_IH_CWEDIT__CWEDIT_VAWUE_MASK                                                                    0x00000003W
#define ATHUB_IH_CWEDIT__IH_CWIENT_ID_MASK                                                                    0x00FF0000W


// addwessBwock: aid_athub_xpbdec
//XPB_WTW_SWC_APWTW0
#define XPB_WTW_SWC_APWTW0__BASE_ADDW__SHIFT                                                                  0x0
#define XPB_WTW_SWC_APWTW0__BASE_ADDW_MASK                                                                    0x7FFFFFFFW
//XPB_WTW_SWC_APWTW1
#define XPB_WTW_SWC_APWTW1__BASE_ADDW__SHIFT                                                                  0x0
#define XPB_WTW_SWC_APWTW1__BASE_ADDW_MASK                                                                    0x7FFFFFFFW
//XPB_WTW_SWC_APWTW2
#define XPB_WTW_SWC_APWTW2__BASE_ADDW__SHIFT                                                                  0x0
#define XPB_WTW_SWC_APWTW2__BASE_ADDW_MASK                                                                    0x7FFFFFFFW
//XPB_WTW_SWC_APWTW3
#define XPB_WTW_SWC_APWTW3__BASE_ADDW__SHIFT                                                                  0x0
#define XPB_WTW_SWC_APWTW3__BASE_ADDW_MASK                                                                    0x7FFFFFFFW
//XPB_WTW_SWC_APWTW4
#define XPB_WTW_SWC_APWTW4__BASE_ADDW__SHIFT                                                                  0x0
#define XPB_WTW_SWC_APWTW4__BASE_ADDW_MASK                                                                    0x7FFFFFFFW
//XPB_WTW_SWC_APWTW5
#define XPB_WTW_SWC_APWTW5__BASE_ADDW__SHIFT                                                                  0x0
#define XPB_WTW_SWC_APWTW5__BASE_ADDW_MASK                                                                    0x7FFFFFFFW
//XPB_WTW_SWC_APWTW6
#define XPB_WTW_SWC_APWTW6__BASE_ADDW__SHIFT                                                                  0x0
#define XPB_WTW_SWC_APWTW6__BASE_ADDW_MASK                                                                    0x7FFFFFFFW
//XPB_WTW_SWC_APWTW7
#define XPB_WTW_SWC_APWTW7__BASE_ADDW__SHIFT                                                                  0x0
#define XPB_WTW_SWC_APWTW7__BASE_ADDW_MASK                                                                    0x7FFFFFFFW
//XPB_WTW_SWC_APWTW8
#define XPB_WTW_SWC_APWTW8__BASE_ADDW__SHIFT                                                                  0x0
#define XPB_WTW_SWC_APWTW8__BASE_ADDW_MASK                                                                    0x7FFFFFFFW
//XPB_WTW_SWC_APWTW9
#define XPB_WTW_SWC_APWTW9__BASE_ADDW__SHIFT                                                                  0x0
#define XPB_WTW_SWC_APWTW9__BASE_ADDW_MASK                                                                    0x7FFFFFFFW
//XPB_XDMA_WTW_SWC_APWTW0
#define XPB_XDMA_WTW_SWC_APWTW0__BASE_ADDW__SHIFT                                                             0x0
#define XPB_XDMA_WTW_SWC_APWTW0__BASE_ADDW_MASK                                                               0x7FFFFFFFW
//XPB_XDMA_WTW_SWC_APWTW1
#define XPB_XDMA_WTW_SWC_APWTW1__BASE_ADDW__SHIFT                                                             0x0
#define XPB_XDMA_WTW_SWC_APWTW1__BASE_ADDW_MASK                                                               0x7FFFFFFFW
//XPB_XDMA_WTW_SWC_APWTW2
#define XPB_XDMA_WTW_SWC_APWTW2__BASE_ADDW__SHIFT                                                             0x0
#define XPB_XDMA_WTW_SWC_APWTW2__BASE_ADDW_MASK                                                               0x7FFFFFFFW
//XPB_XDMA_WTW_SWC_APWTW3
#define XPB_XDMA_WTW_SWC_APWTW3__BASE_ADDW__SHIFT                                                             0x0
#define XPB_XDMA_WTW_SWC_APWTW3__BASE_ADDW_MASK                                                               0x7FFFFFFFW
//XPB_WTW_DEST_MAP0
#define XPB_WTW_DEST_MAP0__NMW__SHIFT                                                                         0x0
#define XPB_WTW_DEST_MAP0__DEST_OFFSET__SHIFT                                                                 0x1
#define XPB_WTW_DEST_MAP0__DEST_SEW__SHIFT                                                                    0x14
#define XPB_WTW_DEST_MAP0__DEST_SEW_WPB__SHIFT                                                                0x18
#define XPB_WTW_DEST_MAP0__SIDE_OK__SHIFT                                                                     0x19
#define XPB_WTW_DEST_MAP0__APWTW_SIZE__SHIFT                                                                  0x1a
#define XPB_WTW_DEST_MAP0__NMW_MASK                                                                           0x00000001W
#define XPB_WTW_DEST_MAP0__DEST_OFFSET_MASK                                                                   0x000FFFFEW
#define XPB_WTW_DEST_MAP0__DEST_SEW_MASK                                                                      0x00F00000W
#define XPB_WTW_DEST_MAP0__DEST_SEW_WPB_MASK                                                                  0x01000000W
#define XPB_WTW_DEST_MAP0__SIDE_OK_MASK                                                                       0x02000000W
#define XPB_WTW_DEST_MAP0__APWTW_SIZE_MASK                                                                    0x7C000000W
//XPB_WTW_DEST_MAP1
#define XPB_WTW_DEST_MAP1__NMW__SHIFT                                                                         0x0
#define XPB_WTW_DEST_MAP1__DEST_OFFSET__SHIFT                                                                 0x1
#define XPB_WTW_DEST_MAP1__DEST_SEW__SHIFT                                                                    0x14
#define XPB_WTW_DEST_MAP1__DEST_SEW_WPB__SHIFT                                                                0x18
#define XPB_WTW_DEST_MAP1__SIDE_OK__SHIFT                                                                     0x19
#define XPB_WTW_DEST_MAP1__APWTW_SIZE__SHIFT                                                                  0x1a
#define XPB_WTW_DEST_MAP1__NMW_MASK                                                                           0x00000001W
#define XPB_WTW_DEST_MAP1__DEST_OFFSET_MASK                                                                   0x000FFFFEW
#define XPB_WTW_DEST_MAP1__DEST_SEW_MASK                                                                      0x00F00000W
#define XPB_WTW_DEST_MAP1__DEST_SEW_WPB_MASK                                                                  0x01000000W
#define XPB_WTW_DEST_MAP1__SIDE_OK_MASK                                                                       0x02000000W
#define XPB_WTW_DEST_MAP1__APWTW_SIZE_MASK                                                                    0x7C000000W
//XPB_WTW_DEST_MAP2
#define XPB_WTW_DEST_MAP2__NMW__SHIFT                                                                         0x0
#define XPB_WTW_DEST_MAP2__DEST_OFFSET__SHIFT                                                                 0x1
#define XPB_WTW_DEST_MAP2__DEST_SEW__SHIFT                                                                    0x14
#define XPB_WTW_DEST_MAP2__DEST_SEW_WPB__SHIFT                                                                0x18
#define XPB_WTW_DEST_MAP2__SIDE_OK__SHIFT                                                                     0x19
#define XPB_WTW_DEST_MAP2__APWTW_SIZE__SHIFT                                                                  0x1a
#define XPB_WTW_DEST_MAP2__NMW_MASK                                                                           0x00000001W
#define XPB_WTW_DEST_MAP2__DEST_OFFSET_MASK                                                                   0x000FFFFEW
#define XPB_WTW_DEST_MAP2__DEST_SEW_MASK                                                                      0x00F00000W
#define XPB_WTW_DEST_MAP2__DEST_SEW_WPB_MASK                                                                  0x01000000W
#define XPB_WTW_DEST_MAP2__SIDE_OK_MASK                                                                       0x02000000W
#define XPB_WTW_DEST_MAP2__APWTW_SIZE_MASK                                                                    0x7C000000W
//XPB_WTW_DEST_MAP3
#define XPB_WTW_DEST_MAP3__NMW__SHIFT                                                                         0x0
#define XPB_WTW_DEST_MAP3__DEST_OFFSET__SHIFT                                                                 0x1
#define XPB_WTW_DEST_MAP3__DEST_SEW__SHIFT                                                                    0x14
#define XPB_WTW_DEST_MAP3__DEST_SEW_WPB__SHIFT                                                                0x18
#define XPB_WTW_DEST_MAP3__SIDE_OK__SHIFT                                                                     0x19
#define XPB_WTW_DEST_MAP3__APWTW_SIZE__SHIFT                                                                  0x1a
#define XPB_WTW_DEST_MAP3__NMW_MASK                                                                           0x00000001W
#define XPB_WTW_DEST_MAP3__DEST_OFFSET_MASK                                                                   0x000FFFFEW
#define XPB_WTW_DEST_MAP3__DEST_SEW_MASK                                                                      0x00F00000W
#define XPB_WTW_DEST_MAP3__DEST_SEW_WPB_MASK                                                                  0x01000000W
#define XPB_WTW_DEST_MAP3__SIDE_OK_MASK                                                                       0x02000000W
#define XPB_WTW_DEST_MAP3__APWTW_SIZE_MASK                                                                    0x7C000000W
//XPB_WTW_DEST_MAP4
#define XPB_WTW_DEST_MAP4__NMW__SHIFT                                                                         0x0
#define XPB_WTW_DEST_MAP4__DEST_OFFSET__SHIFT                                                                 0x1
#define XPB_WTW_DEST_MAP4__DEST_SEW__SHIFT                                                                    0x14
#define XPB_WTW_DEST_MAP4__DEST_SEW_WPB__SHIFT                                                                0x18
#define XPB_WTW_DEST_MAP4__SIDE_OK__SHIFT                                                                     0x19
#define XPB_WTW_DEST_MAP4__APWTW_SIZE__SHIFT                                                                  0x1a
#define XPB_WTW_DEST_MAP4__NMW_MASK                                                                           0x00000001W
#define XPB_WTW_DEST_MAP4__DEST_OFFSET_MASK                                                                   0x000FFFFEW
#define XPB_WTW_DEST_MAP4__DEST_SEW_MASK                                                                      0x00F00000W
#define XPB_WTW_DEST_MAP4__DEST_SEW_WPB_MASK                                                                  0x01000000W
#define XPB_WTW_DEST_MAP4__SIDE_OK_MASK                                                                       0x02000000W
#define XPB_WTW_DEST_MAP4__APWTW_SIZE_MASK                                                                    0x7C000000W
//XPB_WTW_DEST_MAP5
#define XPB_WTW_DEST_MAP5__NMW__SHIFT                                                                         0x0
#define XPB_WTW_DEST_MAP5__DEST_OFFSET__SHIFT                                                                 0x1
#define XPB_WTW_DEST_MAP5__DEST_SEW__SHIFT                                                                    0x14
#define XPB_WTW_DEST_MAP5__DEST_SEW_WPB__SHIFT                                                                0x18
#define XPB_WTW_DEST_MAP5__SIDE_OK__SHIFT                                                                     0x19
#define XPB_WTW_DEST_MAP5__APWTW_SIZE__SHIFT                                                                  0x1a
#define XPB_WTW_DEST_MAP5__NMW_MASK                                                                           0x00000001W
#define XPB_WTW_DEST_MAP5__DEST_OFFSET_MASK                                                                   0x000FFFFEW
#define XPB_WTW_DEST_MAP5__DEST_SEW_MASK                                                                      0x00F00000W
#define XPB_WTW_DEST_MAP5__DEST_SEW_WPB_MASK                                                                  0x01000000W
#define XPB_WTW_DEST_MAP5__SIDE_OK_MASK                                                                       0x02000000W
#define XPB_WTW_DEST_MAP5__APWTW_SIZE_MASK                                                                    0x7C000000W
//XPB_WTW_DEST_MAP6
#define XPB_WTW_DEST_MAP6__NMW__SHIFT                                                                         0x0
#define XPB_WTW_DEST_MAP6__DEST_OFFSET__SHIFT                                                                 0x1
#define XPB_WTW_DEST_MAP6__DEST_SEW__SHIFT                                                                    0x14
#define XPB_WTW_DEST_MAP6__DEST_SEW_WPB__SHIFT                                                                0x18
#define XPB_WTW_DEST_MAP6__SIDE_OK__SHIFT                                                                     0x19
#define XPB_WTW_DEST_MAP6__APWTW_SIZE__SHIFT                                                                  0x1a
#define XPB_WTW_DEST_MAP6__NMW_MASK                                                                           0x00000001W
#define XPB_WTW_DEST_MAP6__DEST_OFFSET_MASK                                                                   0x000FFFFEW
#define XPB_WTW_DEST_MAP6__DEST_SEW_MASK                                                                      0x00F00000W
#define XPB_WTW_DEST_MAP6__DEST_SEW_WPB_MASK                                                                  0x01000000W
#define XPB_WTW_DEST_MAP6__SIDE_OK_MASK                                                                       0x02000000W
#define XPB_WTW_DEST_MAP6__APWTW_SIZE_MASK                                                                    0x7C000000W
//XPB_WTW_DEST_MAP7
#define XPB_WTW_DEST_MAP7__NMW__SHIFT                                                                         0x0
#define XPB_WTW_DEST_MAP7__DEST_OFFSET__SHIFT                                                                 0x1
#define XPB_WTW_DEST_MAP7__DEST_SEW__SHIFT                                                                    0x14
#define XPB_WTW_DEST_MAP7__DEST_SEW_WPB__SHIFT                                                                0x18
#define XPB_WTW_DEST_MAP7__SIDE_OK__SHIFT                                                                     0x19
#define XPB_WTW_DEST_MAP7__APWTW_SIZE__SHIFT                                                                  0x1a
#define XPB_WTW_DEST_MAP7__NMW_MASK                                                                           0x00000001W
#define XPB_WTW_DEST_MAP7__DEST_OFFSET_MASK                                                                   0x000FFFFEW
#define XPB_WTW_DEST_MAP7__DEST_SEW_MASK                                                                      0x00F00000W
#define XPB_WTW_DEST_MAP7__DEST_SEW_WPB_MASK                                                                  0x01000000W
#define XPB_WTW_DEST_MAP7__SIDE_OK_MASK                                                                       0x02000000W
#define XPB_WTW_DEST_MAP7__APWTW_SIZE_MASK                                                                    0x7C000000W
//XPB_WTW_DEST_MAP8
#define XPB_WTW_DEST_MAP8__NMW__SHIFT                                                                         0x0
#define XPB_WTW_DEST_MAP8__DEST_OFFSET__SHIFT                                                                 0x1
#define XPB_WTW_DEST_MAP8__DEST_SEW__SHIFT                                                                    0x14
#define XPB_WTW_DEST_MAP8__DEST_SEW_WPB__SHIFT                                                                0x18
#define XPB_WTW_DEST_MAP8__SIDE_OK__SHIFT                                                                     0x19
#define XPB_WTW_DEST_MAP8__APWTW_SIZE__SHIFT                                                                  0x1a
#define XPB_WTW_DEST_MAP8__NMW_MASK                                                                           0x00000001W
#define XPB_WTW_DEST_MAP8__DEST_OFFSET_MASK                                                                   0x000FFFFEW
#define XPB_WTW_DEST_MAP8__DEST_SEW_MASK                                                                      0x00F00000W
#define XPB_WTW_DEST_MAP8__DEST_SEW_WPB_MASK                                                                  0x01000000W
#define XPB_WTW_DEST_MAP8__SIDE_OK_MASK                                                                       0x02000000W
#define XPB_WTW_DEST_MAP8__APWTW_SIZE_MASK                                                                    0x7C000000W
//XPB_WTW_DEST_MAP9
#define XPB_WTW_DEST_MAP9__NMW__SHIFT                                                                         0x0
#define XPB_WTW_DEST_MAP9__DEST_OFFSET__SHIFT                                                                 0x1
#define XPB_WTW_DEST_MAP9__DEST_SEW__SHIFT                                                                    0x14
#define XPB_WTW_DEST_MAP9__DEST_SEW_WPB__SHIFT                                                                0x18
#define XPB_WTW_DEST_MAP9__SIDE_OK__SHIFT                                                                     0x19
#define XPB_WTW_DEST_MAP9__APWTW_SIZE__SHIFT                                                                  0x1a
#define XPB_WTW_DEST_MAP9__NMW_MASK                                                                           0x00000001W
#define XPB_WTW_DEST_MAP9__DEST_OFFSET_MASK                                                                   0x000FFFFEW
#define XPB_WTW_DEST_MAP9__DEST_SEW_MASK                                                                      0x00F00000W
#define XPB_WTW_DEST_MAP9__DEST_SEW_WPB_MASK                                                                  0x01000000W
#define XPB_WTW_DEST_MAP9__SIDE_OK_MASK                                                                       0x02000000W
#define XPB_WTW_DEST_MAP9__APWTW_SIZE_MASK                                                                    0x7C000000W
//XPB_XDMA_WTW_DEST_MAP0
#define XPB_XDMA_WTW_DEST_MAP0__NMW__SHIFT                                                                    0x0
#define XPB_XDMA_WTW_DEST_MAP0__DEST_OFFSET__SHIFT                                                            0x1
#define XPB_XDMA_WTW_DEST_MAP0__DEST_SEW__SHIFT                                                               0x14
#define XPB_XDMA_WTW_DEST_MAP0__DEST_SEW_WPB__SHIFT                                                           0x18
#define XPB_XDMA_WTW_DEST_MAP0__SIDE_OK__SHIFT                                                                0x19
#define XPB_XDMA_WTW_DEST_MAP0__APWTW_SIZE__SHIFT                                                             0x1a
#define XPB_XDMA_WTW_DEST_MAP0__NMW_MASK                                                                      0x00000001W
#define XPB_XDMA_WTW_DEST_MAP0__DEST_OFFSET_MASK                                                              0x000FFFFEW
#define XPB_XDMA_WTW_DEST_MAP0__DEST_SEW_MASK                                                                 0x00F00000W
#define XPB_XDMA_WTW_DEST_MAP0__DEST_SEW_WPB_MASK                                                             0x01000000W
#define XPB_XDMA_WTW_DEST_MAP0__SIDE_OK_MASK                                                                  0x02000000W
#define XPB_XDMA_WTW_DEST_MAP0__APWTW_SIZE_MASK                                                               0x7C000000W
//XPB_XDMA_WTW_DEST_MAP1
#define XPB_XDMA_WTW_DEST_MAP1__NMW__SHIFT                                                                    0x0
#define XPB_XDMA_WTW_DEST_MAP1__DEST_OFFSET__SHIFT                                                            0x1
#define XPB_XDMA_WTW_DEST_MAP1__DEST_SEW__SHIFT                                                               0x14
#define XPB_XDMA_WTW_DEST_MAP1__DEST_SEW_WPB__SHIFT                                                           0x18
#define XPB_XDMA_WTW_DEST_MAP1__SIDE_OK__SHIFT                                                                0x19
#define XPB_XDMA_WTW_DEST_MAP1__APWTW_SIZE__SHIFT                                                             0x1a
#define XPB_XDMA_WTW_DEST_MAP1__NMW_MASK                                                                      0x00000001W
#define XPB_XDMA_WTW_DEST_MAP1__DEST_OFFSET_MASK                                                              0x000FFFFEW
#define XPB_XDMA_WTW_DEST_MAP1__DEST_SEW_MASK                                                                 0x00F00000W
#define XPB_XDMA_WTW_DEST_MAP1__DEST_SEW_WPB_MASK                                                             0x01000000W
#define XPB_XDMA_WTW_DEST_MAP1__SIDE_OK_MASK                                                                  0x02000000W
#define XPB_XDMA_WTW_DEST_MAP1__APWTW_SIZE_MASK                                                               0x7C000000W
//XPB_XDMA_WTW_DEST_MAP2
#define XPB_XDMA_WTW_DEST_MAP2__NMW__SHIFT                                                                    0x0
#define XPB_XDMA_WTW_DEST_MAP2__DEST_OFFSET__SHIFT                                                            0x1
#define XPB_XDMA_WTW_DEST_MAP2__DEST_SEW__SHIFT                                                               0x14
#define XPB_XDMA_WTW_DEST_MAP2__DEST_SEW_WPB__SHIFT                                                           0x18
#define XPB_XDMA_WTW_DEST_MAP2__SIDE_OK__SHIFT                                                                0x19
#define XPB_XDMA_WTW_DEST_MAP2__APWTW_SIZE__SHIFT                                                             0x1a
#define XPB_XDMA_WTW_DEST_MAP2__NMW_MASK                                                                      0x00000001W
#define XPB_XDMA_WTW_DEST_MAP2__DEST_OFFSET_MASK                                                              0x000FFFFEW
#define XPB_XDMA_WTW_DEST_MAP2__DEST_SEW_MASK                                                                 0x00F00000W
#define XPB_XDMA_WTW_DEST_MAP2__DEST_SEW_WPB_MASK                                                             0x01000000W
#define XPB_XDMA_WTW_DEST_MAP2__SIDE_OK_MASK                                                                  0x02000000W
#define XPB_XDMA_WTW_DEST_MAP2__APWTW_SIZE_MASK                                                               0x7C000000W
//XPB_XDMA_WTW_DEST_MAP3
#define XPB_XDMA_WTW_DEST_MAP3__NMW__SHIFT                                                                    0x0
#define XPB_XDMA_WTW_DEST_MAP3__DEST_OFFSET__SHIFT                                                            0x1
#define XPB_XDMA_WTW_DEST_MAP3__DEST_SEW__SHIFT                                                               0x14
#define XPB_XDMA_WTW_DEST_MAP3__DEST_SEW_WPB__SHIFT                                                           0x18
#define XPB_XDMA_WTW_DEST_MAP3__SIDE_OK__SHIFT                                                                0x19
#define XPB_XDMA_WTW_DEST_MAP3__APWTW_SIZE__SHIFT                                                             0x1a
#define XPB_XDMA_WTW_DEST_MAP3__NMW_MASK                                                                      0x00000001W
#define XPB_XDMA_WTW_DEST_MAP3__DEST_OFFSET_MASK                                                              0x000FFFFEW
#define XPB_XDMA_WTW_DEST_MAP3__DEST_SEW_MASK                                                                 0x00F00000W
#define XPB_XDMA_WTW_DEST_MAP3__DEST_SEW_WPB_MASK                                                             0x01000000W
#define XPB_XDMA_WTW_DEST_MAP3__SIDE_OK_MASK                                                                  0x02000000W
#define XPB_XDMA_WTW_DEST_MAP3__APWTW_SIZE_MASK                                                               0x7C000000W
//XPB_CWG_CFG0
#define XPB_CWG_CFG0__WCB_NUM__SHIFT                                                                          0x0
#define XPB_CWG_CFG0__WB_TYPE__SHIFT                                                                          0x4
#define XPB_CWG_CFG0__P2P_BAW__SHIFT                                                                          0x7
#define XPB_CWG_CFG0__HOST_FWUSH__SHIFT                                                                       0xa
#define XPB_CWG_CFG0__SIDE_FWUSH__SHIFT                                                                       0xe
#define XPB_CWG_CFG0__WCB_NUM_MASK                                                                            0x0000000FW
#define XPB_CWG_CFG0__WB_TYPE_MASK                                                                            0x00000070W
#define XPB_CWG_CFG0__P2P_BAW_MASK                                                                            0x00000380W
#define XPB_CWG_CFG0__HOST_FWUSH_MASK                                                                         0x00003C00W
#define XPB_CWG_CFG0__SIDE_FWUSH_MASK                                                                         0x0003C000W
//XPB_CWG_CFG1
#define XPB_CWG_CFG1__WCB_NUM__SHIFT                                                                          0x0
#define XPB_CWG_CFG1__WB_TYPE__SHIFT                                                                          0x4
#define XPB_CWG_CFG1__P2P_BAW__SHIFT                                                                          0x7
#define XPB_CWG_CFG1__HOST_FWUSH__SHIFT                                                                       0xa
#define XPB_CWG_CFG1__SIDE_FWUSH__SHIFT                                                                       0xe
#define XPB_CWG_CFG1__WCB_NUM_MASK                                                                            0x0000000FW
#define XPB_CWG_CFG1__WB_TYPE_MASK                                                                            0x00000070W
#define XPB_CWG_CFG1__P2P_BAW_MASK                                                                            0x00000380W
#define XPB_CWG_CFG1__HOST_FWUSH_MASK                                                                         0x00003C00W
#define XPB_CWG_CFG1__SIDE_FWUSH_MASK                                                                         0x0003C000W
//XPB_CWG_CFG2
#define XPB_CWG_CFG2__WCB_NUM__SHIFT                                                                          0x0
#define XPB_CWG_CFG2__WB_TYPE__SHIFT                                                                          0x4
#define XPB_CWG_CFG2__P2P_BAW__SHIFT                                                                          0x7
#define XPB_CWG_CFG2__HOST_FWUSH__SHIFT                                                                       0xa
#define XPB_CWG_CFG2__SIDE_FWUSH__SHIFT                                                                       0xe
#define XPB_CWG_CFG2__WCB_NUM_MASK                                                                            0x0000000FW
#define XPB_CWG_CFG2__WB_TYPE_MASK                                                                            0x00000070W
#define XPB_CWG_CFG2__P2P_BAW_MASK                                                                            0x00000380W
#define XPB_CWG_CFG2__HOST_FWUSH_MASK                                                                         0x00003C00W
#define XPB_CWG_CFG2__SIDE_FWUSH_MASK                                                                         0x0003C000W
//XPB_CWG_CFG3
#define XPB_CWG_CFG3__WCB_NUM__SHIFT                                                                          0x0
#define XPB_CWG_CFG3__WB_TYPE__SHIFT                                                                          0x4
#define XPB_CWG_CFG3__P2P_BAW__SHIFT                                                                          0x7
#define XPB_CWG_CFG3__HOST_FWUSH__SHIFT                                                                       0xa
#define XPB_CWG_CFG3__SIDE_FWUSH__SHIFT                                                                       0xe
#define XPB_CWG_CFG3__WCB_NUM_MASK                                                                            0x0000000FW
#define XPB_CWG_CFG3__WB_TYPE_MASK                                                                            0x00000070W
#define XPB_CWG_CFG3__P2P_BAW_MASK                                                                            0x00000380W
#define XPB_CWG_CFG3__HOST_FWUSH_MASK                                                                         0x00003C00W
#define XPB_CWG_CFG3__SIDE_FWUSH_MASK                                                                         0x0003C000W
//XPB_CWG_CFG4
#define XPB_CWG_CFG4__WCB_NUM__SHIFT                                                                          0x0
#define XPB_CWG_CFG4__WB_TYPE__SHIFT                                                                          0x4
#define XPB_CWG_CFG4__P2P_BAW__SHIFT                                                                          0x7
#define XPB_CWG_CFG4__HOST_FWUSH__SHIFT                                                                       0xa
#define XPB_CWG_CFG4__SIDE_FWUSH__SHIFT                                                                       0xe
#define XPB_CWG_CFG4__WCB_NUM_MASK                                                                            0x0000000FW
#define XPB_CWG_CFG4__WB_TYPE_MASK                                                                            0x00000070W
#define XPB_CWG_CFG4__P2P_BAW_MASK                                                                            0x00000380W
#define XPB_CWG_CFG4__HOST_FWUSH_MASK                                                                         0x00003C00W
#define XPB_CWG_CFG4__SIDE_FWUSH_MASK                                                                         0x0003C000W
//XPB_CWG_CFG5
#define XPB_CWG_CFG5__WCB_NUM__SHIFT                                                                          0x0
#define XPB_CWG_CFG5__WB_TYPE__SHIFT                                                                          0x4
#define XPB_CWG_CFG5__P2P_BAW__SHIFT                                                                          0x7
#define XPB_CWG_CFG5__HOST_FWUSH__SHIFT                                                                       0xa
#define XPB_CWG_CFG5__SIDE_FWUSH__SHIFT                                                                       0xe
#define XPB_CWG_CFG5__WCB_NUM_MASK                                                                            0x0000000FW
#define XPB_CWG_CFG5__WB_TYPE_MASK                                                                            0x00000070W
#define XPB_CWG_CFG5__P2P_BAW_MASK                                                                            0x00000380W
#define XPB_CWG_CFG5__HOST_FWUSH_MASK                                                                         0x00003C00W
#define XPB_CWG_CFG5__SIDE_FWUSH_MASK                                                                         0x0003C000W
//XPB_CWG_CFG6
#define XPB_CWG_CFG6__WCB_NUM__SHIFT                                                                          0x0
#define XPB_CWG_CFG6__WB_TYPE__SHIFT                                                                          0x4
#define XPB_CWG_CFG6__P2P_BAW__SHIFT                                                                          0x7
#define XPB_CWG_CFG6__HOST_FWUSH__SHIFT                                                                       0xa
#define XPB_CWG_CFG6__SIDE_FWUSH__SHIFT                                                                       0xe
#define XPB_CWG_CFG6__WCB_NUM_MASK                                                                            0x0000000FW
#define XPB_CWG_CFG6__WB_TYPE_MASK                                                                            0x00000070W
#define XPB_CWG_CFG6__P2P_BAW_MASK                                                                            0x00000380W
#define XPB_CWG_CFG6__HOST_FWUSH_MASK                                                                         0x00003C00W
#define XPB_CWG_CFG6__SIDE_FWUSH_MASK                                                                         0x0003C000W
//XPB_CWG_CFG7
#define XPB_CWG_CFG7__WCB_NUM__SHIFT                                                                          0x0
#define XPB_CWG_CFG7__WB_TYPE__SHIFT                                                                          0x4
#define XPB_CWG_CFG7__P2P_BAW__SHIFT                                                                          0x7
#define XPB_CWG_CFG7__HOST_FWUSH__SHIFT                                                                       0xa
#define XPB_CWG_CFG7__SIDE_FWUSH__SHIFT                                                                       0xe
#define XPB_CWG_CFG7__WCB_NUM_MASK                                                                            0x0000000FW
#define XPB_CWG_CFG7__WB_TYPE_MASK                                                                            0x00000070W
#define XPB_CWG_CFG7__P2P_BAW_MASK                                                                            0x00000380W
#define XPB_CWG_CFG7__HOST_FWUSH_MASK                                                                         0x00003C00W
#define XPB_CWG_CFG7__SIDE_FWUSH_MASK                                                                         0x0003C000W
//XPB_CWG_EXTWA0
#define XPB_CWG_EXTWA0__CMP0_HIGH__SHIFT                                                                      0x0
#define XPB_CWG_EXTWA0__CMP0_WOW__SHIFT                                                                       0x8
#define XPB_CWG_EXTWA0__VWD0__SHIFT                                                                           0xd
#define XPB_CWG_EXTWA0__CWG0_NUM__SHIFT                                                                       0xe
#define XPB_CWG_EXTWA0__CMP0_HIGH_MASK                                                                        0x000000FFW
#define XPB_CWG_EXTWA0__CMP0_WOW_MASK                                                                         0x00001F00W
#define XPB_CWG_EXTWA0__VWD0_MASK                                                                             0x00002000W
#define XPB_CWG_EXTWA0__CWG0_NUM_MASK                                                                         0x0001C000W
//XPB_CWG_EXTWA1
#define XPB_CWG_EXTWA1__CMP1_HIGH__SHIFT                                                                      0x0
#define XPB_CWG_EXTWA1__CMP1_WOW__SHIFT                                                                       0x8
#define XPB_CWG_EXTWA1__VWD1__SHIFT                                                                           0xd
#define XPB_CWG_EXTWA1__CWG1_NUM__SHIFT                                                                       0xe
#define XPB_CWG_EXTWA1__CMP1_HIGH_MASK                                                                        0x000000FFW
#define XPB_CWG_EXTWA1__CMP1_WOW_MASK                                                                         0x00001F00W
#define XPB_CWG_EXTWA1__VWD1_MASK                                                                             0x00002000W
#define XPB_CWG_EXTWA1__CWG1_NUM_MASK                                                                         0x0001C000W
//XPB_CWG_EXTWA_MSK
#define XPB_CWG_EXTWA_MSK__MSK0_HIGH__SHIFT                                                                   0x0
#define XPB_CWG_EXTWA_MSK__MSK0_WOW__SHIFT                                                                    0x8
#define XPB_CWG_EXTWA_MSK__MSK1_HIGH__SHIFT                                                                   0xd
#define XPB_CWG_EXTWA_MSK__MSK1_WOW__SHIFT                                                                    0x15
#define XPB_CWG_EXTWA_MSK__MSK0_HIGH_MASK                                                                     0x000000FFW
#define XPB_CWG_EXTWA_MSK__MSK0_WOW_MASK                                                                      0x00001F00W
#define XPB_CWG_EXTWA_MSK__MSK1_HIGH_MASK                                                                     0x001FE000W
#define XPB_CWG_EXTWA_MSK__MSK1_WOW_MASK                                                                      0x03E00000W
//XPB_WB_ADDW
#define XPB_WB_ADDW__CMP0__SHIFT                                                                              0x0
#define XPB_WB_ADDW__MASK0__SHIFT                                                                             0xa
#define XPB_WB_ADDW__CMP1__SHIFT                                                                              0x14
#define XPB_WB_ADDW__MASK1__SHIFT                                                                             0x1a
#define XPB_WB_ADDW__CMP0_MASK                                                                                0x000003FFW
#define XPB_WB_ADDW__MASK0_MASK                                                                               0x000FFC00W
#define XPB_WB_ADDW__CMP1_MASK                                                                                0x03F00000W
#define XPB_WB_ADDW__MASK1_MASK                                                                               0xFC000000W
//XPB_WCB_STS
#define XPB_WCB_STS__PBUF_VWD__SHIFT                                                                          0x0
#define XPB_WCB_STS__WCB_HST_DATA_BUF_CNT__SHIFT                                                              0x10
#define XPB_WCB_STS__WCB_SID_DATA_BUF_CNT__SHIFT                                                              0x17
#define XPB_WCB_STS__PBUF_VWD_MASK                                                                            0x0000FFFFW
#define XPB_WCB_STS__WCB_HST_DATA_BUF_CNT_MASK                                                                0x007F0000W
#define XPB_WCB_STS__WCB_SID_DATA_BUF_CNT_MASK                                                                0x3F800000W
//XPB_HST_CFG
#define XPB_HST_CFG__BAW_UP_WW_CMD__SHIFT                                                                     0x0
#define XPB_HST_CFG__BAW_UP_WW_CMD_MASK                                                                       0x00000001W
//XPB_P2P_BAW_CFG
#define XPB_P2P_BAW_CFG__ADDW_SIZE__SHIFT                                                                     0x0
#define XPB_P2P_BAW_CFG__SEND_BAW__SHIFT                                                                      0x4
#define XPB_P2P_BAW_CFG__SNOOP__SHIFT                                                                         0x6
#define XPB_P2P_BAW_CFG__SEND_DIS__SHIFT                                                                      0x7
#define XPB_P2P_BAW_CFG__COMPWESS_DIS__SHIFT                                                                  0x8
#define XPB_P2P_BAW_CFG__UPDATE_DIS__SHIFT                                                                    0x9
#define XPB_P2P_BAW_CFG__WEGBAW_FWOM_SYSBAW__SHIFT                                                            0xa
#define XPB_P2P_BAW_CFG__WD_EN__SHIFT                                                                         0xb
#define XPB_P2P_BAW_CFG__ATC_TWANSWATED__SHIFT                                                                0xc
#define XPB_P2P_BAW_CFG__ADDW_SIZE_MASK                                                                       0x0000000FW
#define XPB_P2P_BAW_CFG__SEND_BAW_MASK                                                                        0x00000030W
#define XPB_P2P_BAW_CFG__SNOOP_MASK                                                                           0x00000040W
#define XPB_P2P_BAW_CFG__SEND_DIS_MASK                                                                        0x00000080W
#define XPB_P2P_BAW_CFG__COMPWESS_DIS_MASK                                                                    0x00000100W
#define XPB_P2P_BAW_CFG__UPDATE_DIS_MASK                                                                      0x00000200W
#define XPB_P2P_BAW_CFG__WEGBAW_FWOM_SYSBAW_MASK                                                              0x00000400W
#define XPB_P2P_BAW_CFG__WD_EN_MASK                                                                           0x00000800W
#define XPB_P2P_BAW_CFG__ATC_TWANSWATED_MASK                                                                  0x00001000W
//XPB_P2P_BAW0
#define XPB_P2P_BAW0__HOST_FWUSH__SHIFT                                                                       0x0
#define XPB_P2P_BAW0__WEG_SYS_BAW__SHIFT                                                                      0x4
#define XPB_P2P_BAW0__MEM_SYS_BAW__SHIFT                                                                      0x8
#define XPB_P2P_BAW0__VAWID__SHIFT                                                                            0xc
#define XPB_P2P_BAW0__SEND_DIS__SHIFT                                                                         0xd
#define XPB_P2P_BAW0__COMPWESS_DIS__SHIFT                                                                     0xe
#define XPB_P2P_BAW0__WESEWVED__SHIFT                                                                         0xf
#define XPB_P2P_BAW0__ADDWESS__SHIFT                                                                          0x10
#define XPB_P2P_BAW0__HOST_FWUSH_MASK                                                                         0x0000000FW
#define XPB_P2P_BAW0__WEG_SYS_BAW_MASK                                                                        0x000000F0W
#define XPB_P2P_BAW0__MEM_SYS_BAW_MASK                                                                        0x00000F00W
#define XPB_P2P_BAW0__VAWID_MASK                                                                              0x00001000W
#define XPB_P2P_BAW0__SEND_DIS_MASK                                                                           0x00002000W
#define XPB_P2P_BAW0__COMPWESS_DIS_MASK                                                                       0x00004000W
#define XPB_P2P_BAW0__WESEWVED_MASK                                                                           0x00008000W
#define XPB_P2P_BAW0__ADDWESS_MASK                                                                            0xFFFF0000W
//XPB_P2P_BAW1
#define XPB_P2P_BAW1__HOST_FWUSH__SHIFT                                                                       0x0
#define XPB_P2P_BAW1__WEG_SYS_BAW__SHIFT                                                                      0x4
#define XPB_P2P_BAW1__MEM_SYS_BAW__SHIFT                                                                      0x8
#define XPB_P2P_BAW1__VAWID__SHIFT                                                                            0xc
#define XPB_P2P_BAW1__SEND_DIS__SHIFT                                                                         0xd
#define XPB_P2P_BAW1__COMPWESS_DIS__SHIFT                                                                     0xe
#define XPB_P2P_BAW1__WESEWVED__SHIFT                                                                         0xf
#define XPB_P2P_BAW1__ADDWESS__SHIFT                                                                          0x10
#define XPB_P2P_BAW1__HOST_FWUSH_MASK                                                                         0x0000000FW
#define XPB_P2P_BAW1__WEG_SYS_BAW_MASK                                                                        0x000000F0W
#define XPB_P2P_BAW1__MEM_SYS_BAW_MASK                                                                        0x00000F00W
#define XPB_P2P_BAW1__VAWID_MASK                                                                              0x00001000W
#define XPB_P2P_BAW1__SEND_DIS_MASK                                                                           0x00002000W
#define XPB_P2P_BAW1__COMPWESS_DIS_MASK                                                                       0x00004000W
#define XPB_P2P_BAW1__WESEWVED_MASK                                                                           0x00008000W
#define XPB_P2P_BAW1__ADDWESS_MASK                                                                            0xFFFF0000W
//XPB_P2P_BAW2
#define XPB_P2P_BAW2__HOST_FWUSH__SHIFT                                                                       0x0
#define XPB_P2P_BAW2__WEG_SYS_BAW__SHIFT                                                                      0x4
#define XPB_P2P_BAW2__MEM_SYS_BAW__SHIFT                                                                      0x8
#define XPB_P2P_BAW2__VAWID__SHIFT                                                                            0xc
#define XPB_P2P_BAW2__SEND_DIS__SHIFT                                                                         0xd
#define XPB_P2P_BAW2__COMPWESS_DIS__SHIFT                                                                     0xe
#define XPB_P2P_BAW2__WESEWVED__SHIFT                                                                         0xf
#define XPB_P2P_BAW2__ADDWESS__SHIFT                                                                          0x10
#define XPB_P2P_BAW2__HOST_FWUSH_MASK                                                                         0x0000000FW
#define XPB_P2P_BAW2__WEG_SYS_BAW_MASK                                                                        0x000000F0W
#define XPB_P2P_BAW2__MEM_SYS_BAW_MASK                                                                        0x00000F00W
#define XPB_P2P_BAW2__VAWID_MASK                                                                              0x00001000W
#define XPB_P2P_BAW2__SEND_DIS_MASK                                                                           0x00002000W
#define XPB_P2P_BAW2__COMPWESS_DIS_MASK                                                                       0x00004000W
#define XPB_P2P_BAW2__WESEWVED_MASK                                                                           0x00008000W
#define XPB_P2P_BAW2__ADDWESS_MASK                                                                            0xFFFF0000W
//XPB_P2P_BAW3
#define XPB_P2P_BAW3__HOST_FWUSH__SHIFT                                                                       0x0
#define XPB_P2P_BAW3__WEG_SYS_BAW__SHIFT                                                                      0x4
#define XPB_P2P_BAW3__MEM_SYS_BAW__SHIFT                                                                      0x8
#define XPB_P2P_BAW3__VAWID__SHIFT                                                                            0xc
#define XPB_P2P_BAW3__SEND_DIS__SHIFT                                                                         0xd
#define XPB_P2P_BAW3__COMPWESS_DIS__SHIFT                                                                     0xe
#define XPB_P2P_BAW3__WESEWVED__SHIFT                                                                         0xf
#define XPB_P2P_BAW3__ADDWESS__SHIFT                                                                          0x10
#define XPB_P2P_BAW3__HOST_FWUSH_MASK                                                                         0x0000000FW
#define XPB_P2P_BAW3__WEG_SYS_BAW_MASK                                                                        0x000000F0W
#define XPB_P2P_BAW3__MEM_SYS_BAW_MASK                                                                        0x00000F00W
#define XPB_P2P_BAW3__VAWID_MASK                                                                              0x00001000W
#define XPB_P2P_BAW3__SEND_DIS_MASK                                                                           0x00002000W
#define XPB_P2P_BAW3__COMPWESS_DIS_MASK                                                                       0x00004000W
#define XPB_P2P_BAW3__WESEWVED_MASK                                                                           0x00008000W
#define XPB_P2P_BAW3__ADDWESS_MASK                                                                            0xFFFF0000W
//XPB_P2P_BAW4
#define XPB_P2P_BAW4__HOST_FWUSH__SHIFT                                                                       0x0
#define XPB_P2P_BAW4__WEG_SYS_BAW__SHIFT                                                                      0x4
#define XPB_P2P_BAW4__MEM_SYS_BAW__SHIFT                                                                      0x8
#define XPB_P2P_BAW4__VAWID__SHIFT                                                                            0xc
#define XPB_P2P_BAW4__SEND_DIS__SHIFT                                                                         0xd
#define XPB_P2P_BAW4__COMPWESS_DIS__SHIFT                                                                     0xe
#define XPB_P2P_BAW4__WESEWVED__SHIFT                                                                         0xf
#define XPB_P2P_BAW4__ADDWESS__SHIFT                                                                          0x10
#define XPB_P2P_BAW4__HOST_FWUSH_MASK                                                                         0x0000000FW
#define XPB_P2P_BAW4__WEG_SYS_BAW_MASK                                                                        0x000000F0W
#define XPB_P2P_BAW4__MEM_SYS_BAW_MASK                                                                        0x00000F00W
#define XPB_P2P_BAW4__VAWID_MASK                                                                              0x00001000W
#define XPB_P2P_BAW4__SEND_DIS_MASK                                                                           0x00002000W
#define XPB_P2P_BAW4__COMPWESS_DIS_MASK                                                                       0x00004000W
#define XPB_P2P_BAW4__WESEWVED_MASK                                                                           0x00008000W
#define XPB_P2P_BAW4__ADDWESS_MASK                                                                            0xFFFF0000W
//XPB_P2P_BAW5
#define XPB_P2P_BAW5__HOST_FWUSH__SHIFT                                                                       0x0
#define XPB_P2P_BAW5__WEG_SYS_BAW__SHIFT                                                                      0x4
#define XPB_P2P_BAW5__MEM_SYS_BAW__SHIFT                                                                      0x8
#define XPB_P2P_BAW5__VAWID__SHIFT                                                                            0xc
#define XPB_P2P_BAW5__SEND_DIS__SHIFT                                                                         0xd
#define XPB_P2P_BAW5__COMPWESS_DIS__SHIFT                                                                     0xe
#define XPB_P2P_BAW5__WESEWVED__SHIFT                                                                         0xf
#define XPB_P2P_BAW5__ADDWESS__SHIFT                                                                          0x10
#define XPB_P2P_BAW5__HOST_FWUSH_MASK                                                                         0x0000000FW
#define XPB_P2P_BAW5__WEG_SYS_BAW_MASK                                                                        0x000000F0W
#define XPB_P2P_BAW5__MEM_SYS_BAW_MASK                                                                        0x00000F00W
#define XPB_P2P_BAW5__VAWID_MASK                                                                              0x00001000W
#define XPB_P2P_BAW5__SEND_DIS_MASK                                                                           0x00002000W
#define XPB_P2P_BAW5__COMPWESS_DIS_MASK                                                                       0x00004000W
#define XPB_P2P_BAW5__WESEWVED_MASK                                                                           0x00008000W
#define XPB_P2P_BAW5__ADDWESS_MASK                                                                            0xFFFF0000W
//XPB_P2P_BAW6
#define XPB_P2P_BAW6__HOST_FWUSH__SHIFT                                                                       0x0
#define XPB_P2P_BAW6__WEG_SYS_BAW__SHIFT                                                                      0x4
#define XPB_P2P_BAW6__MEM_SYS_BAW__SHIFT                                                                      0x8
#define XPB_P2P_BAW6__VAWID__SHIFT                                                                            0xc
#define XPB_P2P_BAW6__SEND_DIS__SHIFT                                                                         0xd
#define XPB_P2P_BAW6__COMPWESS_DIS__SHIFT                                                                     0xe
#define XPB_P2P_BAW6__WESEWVED__SHIFT                                                                         0xf
#define XPB_P2P_BAW6__ADDWESS__SHIFT                                                                          0x10
#define XPB_P2P_BAW6__HOST_FWUSH_MASK                                                                         0x0000000FW
#define XPB_P2P_BAW6__WEG_SYS_BAW_MASK                                                                        0x000000F0W
#define XPB_P2P_BAW6__MEM_SYS_BAW_MASK                                                                        0x00000F00W
#define XPB_P2P_BAW6__VAWID_MASK                                                                              0x00001000W
#define XPB_P2P_BAW6__SEND_DIS_MASK                                                                           0x00002000W
#define XPB_P2P_BAW6__COMPWESS_DIS_MASK                                                                       0x00004000W
#define XPB_P2P_BAW6__WESEWVED_MASK                                                                           0x00008000W
#define XPB_P2P_BAW6__ADDWESS_MASK                                                                            0xFFFF0000W
//XPB_P2P_BAW7
#define XPB_P2P_BAW7__HOST_FWUSH__SHIFT                                                                       0x0
#define XPB_P2P_BAW7__WEG_SYS_BAW__SHIFT                                                                      0x4
#define XPB_P2P_BAW7__MEM_SYS_BAW__SHIFT                                                                      0x8
#define XPB_P2P_BAW7__VAWID__SHIFT                                                                            0xc
#define XPB_P2P_BAW7__SEND_DIS__SHIFT                                                                         0xd
#define XPB_P2P_BAW7__COMPWESS_DIS__SHIFT                                                                     0xe
#define XPB_P2P_BAW7__WESEWVED__SHIFT                                                                         0xf
#define XPB_P2P_BAW7__ADDWESS__SHIFT                                                                          0x10
#define XPB_P2P_BAW7__HOST_FWUSH_MASK                                                                         0x0000000FW
#define XPB_P2P_BAW7__WEG_SYS_BAW_MASK                                                                        0x000000F0W
#define XPB_P2P_BAW7__MEM_SYS_BAW_MASK                                                                        0x00000F00W
#define XPB_P2P_BAW7__VAWID_MASK                                                                              0x00001000W
#define XPB_P2P_BAW7__SEND_DIS_MASK                                                                           0x00002000W
#define XPB_P2P_BAW7__COMPWESS_DIS_MASK                                                                       0x00004000W
#define XPB_P2P_BAW7__WESEWVED_MASK                                                                           0x00008000W
#define XPB_P2P_BAW7__ADDWESS_MASK                                                                            0xFFFF0000W
//XPB_P2P_BAW_SETUP
#define XPB_P2P_BAW_SETUP__SEW__SHIFT                                                                         0x0
#define XPB_P2P_BAW_SETUP__WEG_SYS_BAW__SHIFT                                                                 0x8
#define XPB_P2P_BAW_SETUP__VAWID__SHIFT                                                                       0xc
#define XPB_P2P_BAW_SETUP__SEND_DIS__SHIFT                                                                    0xd
#define XPB_P2P_BAW_SETUP__COMPWESS_DIS__SHIFT                                                                0xe
#define XPB_P2P_BAW_SETUP__WESEWVED__SHIFT                                                                    0xf
#define XPB_P2P_BAW_SETUP__ADDWESS__SHIFT                                                                     0x10
#define XPB_P2P_BAW_SETUP__SEW_MASK                                                                           0x000000FFW
#define XPB_P2P_BAW_SETUP__WEG_SYS_BAW_MASK                                                                   0x00000F00W
#define XPB_P2P_BAW_SETUP__VAWID_MASK                                                                         0x00001000W
#define XPB_P2P_BAW_SETUP__SEND_DIS_MASK                                                                      0x00002000W
#define XPB_P2P_BAW_SETUP__COMPWESS_DIS_MASK                                                                  0x00004000W
#define XPB_P2P_BAW_SETUP__WESEWVED_MASK                                                                      0x00008000W
#define XPB_P2P_BAW_SETUP__ADDWESS_MASK                                                                       0xFFFF0000W
//XPB_P2P_BAW_DEWTA_ABOVE
#define XPB_P2P_BAW_DEWTA_ABOVE__EN__SHIFT                                                                    0x0
#define XPB_P2P_BAW_DEWTA_ABOVE__DEWTA__SHIFT                                                                 0x8
#define XPB_P2P_BAW_DEWTA_ABOVE__EN_MASK                                                                      0x000000FFW
#define XPB_P2P_BAW_DEWTA_ABOVE__DEWTA_MASK                                                                   0x0FFFFF00W
//XPB_P2P_BAW_DEWTA_BEWOW
#define XPB_P2P_BAW_DEWTA_BEWOW__EN__SHIFT                                                                    0x0
#define XPB_P2P_BAW_DEWTA_BEWOW__DEWTA__SHIFT                                                                 0x8
#define XPB_P2P_BAW_DEWTA_BEWOW__EN_MASK                                                                      0x000000FFW
#define XPB_P2P_BAW_DEWTA_BEWOW__DEWTA_MASK                                                                   0x0FFFFF00W
//XPB_PEEW_SYS_BAW0
#define XPB_PEEW_SYS_BAW0__VAWID__SHIFT                                                                       0x0
#define XPB_PEEW_SYS_BAW0__ADDW__SHIFT                                                                        0x1
#define XPB_PEEW_SYS_BAW0__VAWID_MASK                                                                         0x00000001W
#define XPB_PEEW_SYS_BAW0__ADDW_MASK                                                                          0xFFFFFFFEW
//XPB_PEEW_SYS_BAW1
#define XPB_PEEW_SYS_BAW1__VAWID__SHIFT                                                                       0x0
#define XPB_PEEW_SYS_BAW1__ADDW__SHIFT                                                                        0x1
#define XPB_PEEW_SYS_BAW1__VAWID_MASK                                                                         0x00000001W
#define XPB_PEEW_SYS_BAW1__ADDW_MASK                                                                          0xFFFFFFFEW
//XPB_PEEW_SYS_BAW2
#define XPB_PEEW_SYS_BAW2__VAWID__SHIFT                                                                       0x0
#define XPB_PEEW_SYS_BAW2__ADDW__SHIFT                                                                        0x1
#define XPB_PEEW_SYS_BAW2__VAWID_MASK                                                                         0x00000001W
#define XPB_PEEW_SYS_BAW2__ADDW_MASK                                                                          0xFFFFFFFEW
//XPB_PEEW_SYS_BAW3
#define XPB_PEEW_SYS_BAW3__VAWID__SHIFT                                                                       0x0
#define XPB_PEEW_SYS_BAW3__ADDW__SHIFT                                                                        0x1
#define XPB_PEEW_SYS_BAW3__VAWID_MASK                                                                         0x00000001W
#define XPB_PEEW_SYS_BAW3__ADDW_MASK                                                                          0xFFFFFFFEW
//XPB_PEEW_SYS_BAW4
#define XPB_PEEW_SYS_BAW4__VAWID__SHIFT                                                                       0x0
#define XPB_PEEW_SYS_BAW4__ADDW__SHIFT                                                                        0x1
#define XPB_PEEW_SYS_BAW4__VAWID_MASK                                                                         0x00000001W
#define XPB_PEEW_SYS_BAW4__ADDW_MASK                                                                          0xFFFFFFFEW
//XPB_PEEW_SYS_BAW5
#define XPB_PEEW_SYS_BAW5__VAWID__SHIFT                                                                       0x0
#define XPB_PEEW_SYS_BAW5__ADDW__SHIFT                                                                        0x1
#define XPB_PEEW_SYS_BAW5__VAWID_MASK                                                                         0x00000001W
#define XPB_PEEW_SYS_BAW5__ADDW_MASK                                                                          0xFFFFFFFEW
//XPB_PEEW_SYS_BAW6
#define XPB_PEEW_SYS_BAW6__VAWID__SHIFT                                                                       0x0
#define XPB_PEEW_SYS_BAW6__ADDW__SHIFT                                                                        0x1
#define XPB_PEEW_SYS_BAW6__VAWID_MASK                                                                         0x00000001W
#define XPB_PEEW_SYS_BAW6__ADDW_MASK                                                                          0xFFFFFFFEW
//XPB_PEEW_SYS_BAW7
#define XPB_PEEW_SYS_BAW7__VAWID__SHIFT                                                                       0x0
#define XPB_PEEW_SYS_BAW7__ADDW__SHIFT                                                                        0x1
#define XPB_PEEW_SYS_BAW7__VAWID_MASK                                                                         0x00000001W
#define XPB_PEEW_SYS_BAW7__ADDW_MASK                                                                          0xFFFFFFFEW
//XPB_PEEW_SYS_BAW8
#define XPB_PEEW_SYS_BAW8__VAWID__SHIFT                                                                       0x0
#define XPB_PEEW_SYS_BAW8__ADDW__SHIFT                                                                        0x1
#define XPB_PEEW_SYS_BAW8__VAWID_MASK                                                                         0x00000001W
#define XPB_PEEW_SYS_BAW8__ADDW_MASK                                                                          0xFFFFFFFEW
//XPB_PEEW_SYS_BAW9
#define XPB_PEEW_SYS_BAW9__VAWID__SHIFT                                                                       0x0
#define XPB_PEEW_SYS_BAW9__ADDW__SHIFT                                                                        0x1
#define XPB_PEEW_SYS_BAW9__VAWID_MASK                                                                         0x00000001W
#define XPB_PEEW_SYS_BAW9__ADDW_MASK                                                                          0xFFFFFFFEW
//XPB_XDMA_PEEW_SYS_BAW0
#define XPB_XDMA_PEEW_SYS_BAW0__VAWID__SHIFT                                                                  0x0
#define XPB_XDMA_PEEW_SYS_BAW0__ADDW__SHIFT                                                                   0x1
#define XPB_XDMA_PEEW_SYS_BAW0__VAWID_MASK                                                                    0x00000001W
#define XPB_XDMA_PEEW_SYS_BAW0__ADDW_MASK                                                                     0xFFFFFFFEW
//XPB_XDMA_PEEW_SYS_BAW1
#define XPB_XDMA_PEEW_SYS_BAW1__VAWID__SHIFT                                                                  0x0
#define XPB_XDMA_PEEW_SYS_BAW1__ADDW__SHIFT                                                                   0x1
#define XPB_XDMA_PEEW_SYS_BAW1__VAWID_MASK                                                                    0x00000001W
#define XPB_XDMA_PEEW_SYS_BAW1__ADDW_MASK                                                                     0xFFFFFFFEW
//XPB_XDMA_PEEW_SYS_BAW2
#define XPB_XDMA_PEEW_SYS_BAW2__VAWID__SHIFT                                                                  0x0
#define XPB_XDMA_PEEW_SYS_BAW2__ADDW__SHIFT                                                                   0x1
#define XPB_XDMA_PEEW_SYS_BAW2__VAWID_MASK                                                                    0x00000001W
#define XPB_XDMA_PEEW_SYS_BAW2__ADDW_MASK                                                                     0xFFFFFFFEW
//XPB_XDMA_PEEW_SYS_BAW3
#define XPB_XDMA_PEEW_SYS_BAW3__VAWID__SHIFT                                                                  0x0
#define XPB_XDMA_PEEW_SYS_BAW3__ADDW__SHIFT                                                                   0x1
#define XPB_XDMA_PEEW_SYS_BAW3__VAWID_MASK                                                                    0x00000001W
#define XPB_XDMA_PEEW_SYS_BAW3__ADDW_MASK                                                                     0xFFFFFFFEW
//XPB_CWK_GAT
#define XPB_CWK_GAT__ONDWY__SHIFT                                                                             0x0
#define XPB_CWK_GAT__OFFDWY__SHIFT                                                                            0x6
#define XPB_CWK_GAT__WDYDWY__SHIFT                                                                            0xc
#define XPB_CWK_GAT__ENABWE__SHIFT                                                                            0x12
#define XPB_CWK_GAT__MEM_WS_ENABWE__SHIFT                                                                     0x13
#define XPB_CWK_GAT__ONDWY_MASK                                                                               0x0000003FW
#define XPB_CWK_GAT__OFFDWY_MASK                                                                              0x00000FC0W
#define XPB_CWK_GAT__WDYDWY_MASK                                                                              0x0003F000W
#define XPB_CWK_GAT__ENABWE_MASK                                                                              0x00040000W
#define XPB_CWK_GAT__MEM_WS_ENABWE_MASK                                                                       0x00080000W
//XPB_INTF_CFG
#define XPB_INTF_CFG__WPB_WWWEQ_CWD__SHIFT                                                                    0x0
#define XPB_INTF_CFG__MC_WWWET_ASK__SHIFT                                                                     0x8
#define XPB_INTF_CFG__XSP_WEQ_CWD__SHIFT                                                                      0x10
#define XPB_INTF_CFG__BIF_WEG_SNOOP_SEW__SHIFT                                                                0x17
#define XPB_INTF_CFG__BIF_WEG_SNOOP_VAW__SHIFT                                                                0x18
#define XPB_INTF_CFG__BIF_MEM_SNOOP_SEW__SHIFT                                                                0x19
#define XPB_INTF_CFG__BIF_MEM_SNOOP_VAW__SHIFT                                                                0x1a
#define XPB_INTF_CFG__XSP_SNOOP_SEW__SHIFT                                                                    0x1b
#define XPB_INTF_CFG__XSP_SNOOP_VAW__SHIFT                                                                    0x1d
#define XPB_INTF_CFG__XSP_OWDEWING_SEW__SHIFT                                                                 0x1e
#define XPB_INTF_CFG__QUAWIFY_P2P_FOW_GPA__SHIFT                                                              0x1f
#define XPB_INTF_CFG__WPB_WWWEQ_CWD_MASK                                                                      0x000000FFW
#define XPB_INTF_CFG__MC_WWWET_ASK_MASK                                                                       0x0000FF00W
#define XPB_INTF_CFG__XSP_WEQ_CWD_MASK                                                                        0x007F0000W
#define XPB_INTF_CFG__BIF_WEG_SNOOP_SEW_MASK                                                                  0x00800000W
#define XPB_INTF_CFG__BIF_WEG_SNOOP_VAW_MASK                                                                  0x01000000W
#define XPB_INTF_CFG__BIF_MEM_SNOOP_SEW_MASK                                                                  0x02000000W
#define XPB_INTF_CFG__BIF_MEM_SNOOP_VAW_MASK                                                                  0x04000000W
#define XPB_INTF_CFG__XSP_SNOOP_SEW_MASK                                                                      0x18000000W
#define XPB_INTF_CFG__XSP_SNOOP_VAW_MASK                                                                      0x20000000W
#define XPB_INTF_CFG__XSP_OWDEWING_SEW_MASK                                                                   0x40000000W
#define XPB_INTF_CFG__QUAWIFY_P2P_FOW_GPA_MASK                                                                0x80000000W
//XPB_INTF_STS
#define XPB_INTF_STS__WPB_WWWEQ_CWD__SHIFT                                                                    0x0
#define XPB_INTF_STS__XSP_WEQ_CWD__SHIFT                                                                      0x8
#define XPB_INTF_STS__HOP_DATA_BUF_FUWW__SHIFT                                                                0xf
#define XPB_INTF_STS__HOP_ATTW_BUF_FUWW__SHIFT                                                                0x10
#define XPB_INTF_STS__CNS_BUF_FUWW__SHIFT                                                                     0x11
#define XPB_INTF_STS__CNS_BUF_BUSY__SHIFT                                                                     0x12
#define XPB_INTF_STS__WPB_WDWEQ_CWD__SHIFT                                                                    0x13
#define XPB_INTF_STS__WPB_WWWEQ_CWD_MASK                                                                      0x000000FFW
#define XPB_INTF_STS__XSP_WEQ_CWD_MASK                                                                        0x00007F00W
#define XPB_INTF_STS__HOP_DATA_BUF_FUWW_MASK                                                                  0x00008000W
#define XPB_INTF_STS__HOP_ATTW_BUF_FUWW_MASK                                                                  0x00010000W
#define XPB_INTF_STS__CNS_BUF_FUWW_MASK                                                                       0x00020000W
#define XPB_INTF_STS__CNS_BUF_BUSY_MASK                                                                       0x00040000W
#define XPB_INTF_STS__WPB_WDWEQ_CWD_MASK                                                                      0x07F80000W
//XPB_PIPE_STS
#define XPB_PIPE_STS__WCB_ANY_PBUF__SHIFT                                                                     0x0
#define XPB_PIPE_STS__WCB_HST_DATA_BUF_CNT__SHIFT                                                             0x1
#define XPB_PIPE_STS__WCB_SID_DATA_BUF_CNT__SHIFT                                                             0x8
#define XPB_PIPE_STS__WCB_HST_WD_PTW_BUF_FUWW__SHIFT                                                          0xf
#define XPB_PIPE_STS__WCB_SID_WD_PTW_BUF_FUWW__SHIFT                                                          0x10
#define XPB_PIPE_STS__WCB_HST_WEQ_FIFO_FUWW__SHIFT                                                            0x11
#define XPB_PIPE_STS__WCB_SID_WEQ_FIFO_FUWW__SHIFT                                                            0x12
#define XPB_PIPE_STS__WCB_HST_WEQ_OBUF_FUWW__SHIFT                                                            0x13
#define XPB_PIPE_STS__WCB_SID_WEQ_OBUF_FUWW__SHIFT                                                            0x14
#define XPB_PIPE_STS__WCB_HST_DATA_OBUF_FUWW__SHIFT                                                           0x15
#define XPB_PIPE_STS__WCB_SID_DATA_OBUF_FUWW__SHIFT                                                           0x16
#define XPB_PIPE_STS__WET_BUF_FUWW__SHIFT                                                                     0x17
#define XPB_PIPE_STS__XPB_CWK_BUSY_BITS__SHIFT                                                                0x18
#define XPB_PIPE_STS__WCB_ANY_PBUF_MASK                                                                       0x00000001W
#define XPB_PIPE_STS__WCB_HST_DATA_BUF_CNT_MASK                                                               0x000000FEW
#define XPB_PIPE_STS__WCB_SID_DATA_BUF_CNT_MASK                                                               0x00007F00W
#define XPB_PIPE_STS__WCB_HST_WD_PTW_BUF_FUWW_MASK                                                            0x00008000W
#define XPB_PIPE_STS__WCB_SID_WD_PTW_BUF_FUWW_MASK                                                            0x00010000W
#define XPB_PIPE_STS__WCB_HST_WEQ_FIFO_FUWW_MASK                                                              0x00020000W
#define XPB_PIPE_STS__WCB_SID_WEQ_FIFO_FUWW_MASK                                                              0x00040000W
#define XPB_PIPE_STS__WCB_HST_WEQ_OBUF_FUWW_MASK                                                              0x00080000W
#define XPB_PIPE_STS__WCB_SID_WEQ_OBUF_FUWW_MASK                                                              0x00100000W
#define XPB_PIPE_STS__WCB_HST_DATA_OBUF_FUWW_MASK                                                             0x00200000W
#define XPB_PIPE_STS__WCB_SID_DATA_OBUF_FUWW_MASK                                                             0x00400000W
#define XPB_PIPE_STS__WET_BUF_FUWW_MASK                                                                       0x00800000W
#define XPB_PIPE_STS__XPB_CWK_BUSY_BITS_MASK                                                                  0xFF000000W
//XPB_SUB_CTWW
#define XPB_SUB_CTWW__WWWEQ_BYPASS_XPB__SHIFT                                                                 0x0
#define XPB_SUB_CTWW__STAWW_CNS_WTW_WEQ__SHIFT                                                                0x1
#define XPB_SUB_CTWW__STAWW_WTW_WPB_WWWEQ__SHIFT                                                              0x2
#define XPB_SUB_CTWW__STAWW_WTW_MAP_WEQ__SHIFT                                                                0x3
#define XPB_SUB_CTWW__STAWW_MAP_WCB_WEQ__SHIFT                                                                0x4
#define XPB_SUB_CTWW__STAWW_WCB_SID_WEQ__SHIFT                                                                0x5
#define XPB_SUB_CTWW__STAWW_MC_XSP_WEQ_SEND__SHIFT                                                            0x6
#define XPB_SUB_CTWW__STAWW_WCB_HST_WEQ__SHIFT                                                                0x7
#define XPB_SUB_CTWW__STAWW_HST_HOP_WEQ__SHIFT                                                                0x8
#define XPB_SUB_CTWW__STAWW_XPB_WPB_WEQ_ATTW__SHIFT                                                           0x9
#define XPB_SUB_CTWW__WESET_CNS__SHIFT                                                                        0xa
#define XPB_SUB_CTWW__WESET_WTW__SHIFT                                                                        0xb
#define XPB_SUB_CTWW__WESET_WET__SHIFT                                                                        0xc
#define XPB_SUB_CTWW__WESET_MAP__SHIFT                                                                        0xd
#define XPB_SUB_CTWW__WESET_WCB__SHIFT                                                                        0xe
#define XPB_SUB_CTWW__WESET_HST__SHIFT                                                                        0xf
#define XPB_SUB_CTWW__WESET_HOP__SHIFT                                                                        0x10
#define XPB_SUB_CTWW__WESET_SID__SHIFT                                                                        0x11
#define XPB_SUB_CTWW__WESET_SWB__SHIFT                                                                        0x12
#define XPB_SUB_CTWW__WESET_CGW__SHIFT                                                                        0x13
#define XPB_SUB_CTWW__WWWEQ_BYPASS_XPB_MASK                                                                   0x00000001W
#define XPB_SUB_CTWW__STAWW_CNS_WTW_WEQ_MASK                                                                  0x00000002W
#define XPB_SUB_CTWW__STAWW_WTW_WPB_WWWEQ_MASK                                                                0x00000004W
#define XPB_SUB_CTWW__STAWW_WTW_MAP_WEQ_MASK                                                                  0x00000008W
#define XPB_SUB_CTWW__STAWW_MAP_WCB_WEQ_MASK                                                                  0x00000010W
#define XPB_SUB_CTWW__STAWW_WCB_SID_WEQ_MASK                                                                  0x00000020W
#define XPB_SUB_CTWW__STAWW_MC_XSP_WEQ_SEND_MASK                                                              0x00000040W
#define XPB_SUB_CTWW__STAWW_WCB_HST_WEQ_MASK                                                                  0x00000080W
#define XPB_SUB_CTWW__STAWW_HST_HOP_WEQ_MASK                                                                  0x00000100W
#define XPB_SUB_CTWW__STAWW_XPB_WPB_WEQ_ATTW_MASK                                                             0x00000200W
#define XPB_SUB_CTWW__WESET_CNS_MASK                                                                          0x00000400W
#define XPB_SUB_CTWW__WESET_WTW_MASK                                                                          0x00000800W
#define XPB_SUB_CTWW__WESET_WET_MASK                                                                          0x00001000W
#define XPB_SUB_CTWW__WESET_MAP_MASK                                                                          0x00002000W
#define XPB_SUB_CTWW__WESET_WCB_MASK                                                                          0x00004000W
#define XPB_SUB_CTWW__WESET_HST_MASK                                                                          0x00008000W
#define XPB_SUB_CTWW__WESET_HOP_MASK                                                                          0x00010000W
#define XPB_SUB_CTWW__WESET_SID_MASK                                                                          0x00020000W
#define XPB_SUB_CTWW__WESET_SWB_MASK                                                                          0x00040000W
#define XPB_SUB_CTWW__WESET_CGW_MASK                                                                          0x00080000W
//XPB_MAP_INVEWT_FWUSH_NUM_WSB
#define XPB_MAP_INVEWT_FWUSH_NUM_WSB__AWTEW_FWUSH_NUM__SHIFT                                                  0x0
#define XPB_MAP_INVEWT_FWUSH_NUM_WSB__AWTEW_FWUSH_NUM_MASK                                                    0x0000FFFFW
//XPB_PEWF_KNOBS
#define XPB_PEWF_KNOBS__CNS_FIFO_DEPTH__SHIFT                                                                 0x0
#define XPB_PEWF_KNOBS__WCB_HST_FIFO_DEPTH__SHIFT                                                             0x6
#define XPB_PEWF_KNOBS__WCB_SID_FIFO_DEPTH__SHIFT                                                             0xc
#define XPB_PEWF_KNOBS__CNS_FIFO_DEPTH_MASK                                                                   0x0000003FW
#define XPB_PEWF_KNOBS__WCB_HST_FIFO_DEPTH_MASK                                                               0x00000FC0W
#define XPB_PEWF_KNOBS__WCB_SID_FIFO_DEPTH_MASK                                                               0x0003F000W
//XPB_STICKY
#define XPB_STICKY__BITS__SHIFT                                                                               0x0
#define XPB_STICKY__BITS_MASK                                                                                 0xFFFFFFFFW
//XPB_STICKY_W1C
#define XPB_STICKY_W1C__BITS__SHIFT                                                                           0x0
#define XPB_STICKY_W1C__BITS_MASK                                                                             0xFFFFFFFFW
//XPB_MISC_CFG
#define XPB_MISC_CFG__FIEWDNAME0__SHIFT                                                                       0x0
#define XPB_MISC_CFG__FIEWDNAME1__SHIFT                                                                       0x8
#define XPB_MISC_CFG__FIEWDNAME2__SHIFT                                                                       0x10
#define XPB_MISC_CFG__FIEWDNAME3__SHIFT                                                                       0x18
#define XPB_MISC_CFG__TWIGGEWNAME__SHIFT                                                                      0x1f
#define XPB_MISC_CFG__FIEWDNAME0_MASK                                                                         0x000000FFW
#define XPB_MISC_CFG__FIEWDNAME1_MASK                                                                         0x0000FF00W
#define XPB_MISC_CFG__FIEWDNAME2_MASK                                                                         0x00FF0000W
#define XPB_MISC_CFG__FIEWDNAME3_MASK                                                                         0x7F000000W
#define XPB_MISC_CFG__TWIGGEWNAME_MASK                                                                        0x80000000W
//XPB_INTF_CFG2
#define XPB_INTF_CFG2__WPB_WDWEQ_CWD__SHIFT                                                                   0x0
#define XPB_INTF_CFG2__WPB_WDWEQ_CWD_MASK                                                                     0x000000FFW
//XPB_CWG_EXTWA_WD
#define XPB_CWG_EXTWA_WD__CMP0_HIGH__SHIFT                                                                    0x0
#define XPB_CWG_EXTWA_WD__CMP0_WOW__SHIFT                                                                     0x6
#define XPB_CWG_EXTWA_WD__VWD0__SHIFT                                                                         0xb
#define XPB_CWG_EXTWA_WD__CWG0_NUM__SHIFT                                                                     0xc
#define XPB_CWG_EXTWA_WD__CMP1_HIGH__SHIFT                                                                    0xf
#define XPB_CWG_EXTWA_WD__CMP1_WOW__SHIFT                                                                     0x15
#define XPB_CWG_EXTWA_WD__VWD1__SHIFT                                                                         0x1a
#define XPB_CWG_EXTWA_WD__CWG1_NUM__SHIFT                                                                     0x1b
#define XPB_CWG_EXTWA_WD__CMP0_HIGH_MASK                                                                      0x0000003FW
#define XPB_CWG_EXTWA_WD__CMP0_WOW_MASK                                                                       0x000007C0W
#define XPB_CWG_EXTWA_WD__VWD0_MASK                                                                           0x00000800W
#define XPB_CWG_EXTWA_WD__CWG0_NUM_MASK                                                                       0x00007000W
#define XPB_CWG_EXTWA_WD__CMP1_HIGH_MASK                                                                      0x001F8000W
#define XPB_CWG_EXTWA_WD__CMP1_WOW_MASK                                                                       0x03E00000W
#define XPB_CWG_EXTWA_WD__VWD1_MASK                                                                           0x04000000W
#define XPB_CWG_EXTWA_WD__CWG1_NUM_MASK                                                                       0x38000000W
//XPB_CWG_EXTWA_MSK_WD
#define XPB_CWG_EXTWA_MSK_WD__MSK0_HIGH__SHIFT                                                                0x0
#define XPB_CWG_EXTWA_MSK_WD__MSK0_WOW__SHIFT                                                                 0x6
#define XPB_CWG_EXTWA_MSK_WD__MSK1_HIGH__SHIFT                                                                0xb
#define XPB_CWG_EXTWA_MSK_WD__MSK1_WOW__SHIFT                                                                 0x11
#define XPB_CWG_EXTWA_MSK_WD__MSK0_HIGH_MASK                                                                  0x0000003FW
#define XPB_CWG_EXTWA_MSK_WD__MSK0_WOW_MASK                                                                   0x000007C0W
#define XPB_CWG_EXTWA_MSK_WD__MSK1_HIGH_MASK                                                                  0x0001F800W
#define XPB_CWG_EXTWA_MSK_WD__MSK1_WOW_MASK                                                                   0x003E0000W
//XPB_CWG_GFX_MATCH
#define XPB_CWG_GFX_MATCH__FAWBIWC0_ID__SHIFT                                                                 0x0
#define XPB_CWG_GFX_MATCH__FAWBIWC1_ID__SHIFT                                                                 0x8
#define XPB_CWG_GFX_MATCH__FAWBIWC2_ID__SHIFT                                                                 0x10
#define XPB_CWG_GFX_MATCH__FAWBIWC3_ID__SHIFT                                                                 0x18
#define XPB_CWG_GFX_MATCH__FAWBIWC0_ID_MASK                                                                   0x000000FFW
#define XPB_CWG_GFX_MATCH__FAWBIWC1_ID_MASK                                                                   0x0000FF00W
#define XPB_CWG_GFX_MATCH__FAWBIWC2_ID_MASK                                                                   0x00FF0000W
#define XPB_CWG_GFX_MATCH__FAWBIWC3_ID_MASK                                                                   0xFF000000W
//XPB_CWG_GFX_MATCH_VWD
#define XPB_CWG_GFX_MATCH_VWD__FAWBIWC0_VWD__SHIFT                                                            0x0
#define XPB_CWG_GFX_MATCH_VWD__FAWBIWC1_VWD__SHIFT                                                            0x1
#define XPB_CWG_GFX_MATCH_VWD__FAWBIWC2_VWD__SHIFT                                                            0x2
#define XPB_CWG_GFX_MATCH_VWD__FAWBIWC3_VWD__SHIFT                                                            0x3
#define XPB_CWG_GFX_MATCH_VWD__FAWBIWC0_VWD_MASK                                                              0x00000001W
#define XPB_CWG_GFX_MATCH_VWD__FAWBIWC1_VWD_MASK                                                              0x00000002W
#define XPB_CWG_GFX_MATCH_VWD__FAWBIWC2_VWD_MASK                                                              0x00000004W
#define XPB_CWG_GFX_MATCH_VWD__FAWBIWC3_VWD_MASK                                                              0x00000008W
//XPB_CWG_GFX_MATCH_MSK
#define XPB_CWG_GFX_MATCH_MSK__FAWBIWC0_ID_MSK__SHIFT                                                         0x0
#define XPB_CWG_GFX_MATCH_MSK__FAWBIWC1_ID_MSK__SHIFT                                                         0x8
#define XPB_CWG_GFX_MATCH_MSK__FAWBIWC2_ID_MSK__SHIFT                                                         0x10
#define XPB_CWG_GFX_MATCH_MSK__FAWBIWC3_ID_MSK__SHIFT                                                         0x18
#define XPB_CWG_GFX_MATCH_MSK__FAWBIWC0_ID_MSK_MASK                                                           0x000000FFW
#define XPB_CWG_GFX_MATCH_MSK__FAWBIWC1_ID_MSK_MASK                                                           0x0000FF00W
#define XPB_CWG_GFX_MATCH_MSK__FAWBIWC2_ID_MSK_MASK                                                           0x00FF0000W
#define XPB_CWG_GFX_MATCH_MSK__FAWBIWC3_ID_MSK_MASK                                                           0xFF000000W
//XPB_CWG_MM_MATCH
#define XPB_CWG_MM_MATCH__FAWBIWC0_ID__SHIFT                                                                  0x0
#define XPB_CWG_MM_MATCH__FAWBIWC1_ID__SHIFT                                                                  0x8
#define XPB_CWG_MM_MATCH__FAWBIWC2_ID__SHIFT                                                                  0x10
#define XPB_CWG_MM_MATCH__FAWBIWC3_ID__SHIFT                                                                  0x18
#define XPB_CWG_MM_MATCH__FAWBIWC0_ID_MASK                                                                    0x000000FFW
#define XPB_CWG_MM_MATCH__FAWBIWC1_ID_MASK                                                                    0x0000FF00W
#define XPB_CWG_MM_MATCH__FAWBIWC2_ID_MASK                                                                    0x00FF0000W
#define XPB_CWG_MM_MATCH__FAWBIWC3_ID_MASK                                                                    0xFF000000W
//XPB_CWG_MM_MATCH_VWD
#define XPB_CWG_MM_MATCH_VWD__FAWBIWC0_VWD__SHIFT                                                             0x0
#define XPB_CWG_MM_MATCH_VWD__FAWBIWC1_VWD__SHIFT                                                             0x1
#define XPB_CWG_MM_MATCH_VWD__FAWBIWC2_VWD__SHIFT                                                             0x2
#define XPB_CWG_MM_MATCH_VWD__FAWBIWC3_VWD__SHIFT                                                             0x3
#define XPB_CWG_MM_MATCH_VWD__FAWBIWC0_VWD_MASK                                                               0x00000001W
#define XPB_CWG_MM_MATCH_VWD__FAWBIWC1_VWD_MASK                                                               0x00000002W
#define XPB_CWG_MM_MATCH_VWD__FAWBIWC2_VWD_MASK                                                               0x00000004W
#define XPB_CWG_MM_MATCH_VWD__FAWBIWC3_VWD_MASK                                                               0x00000008W
//XPB_CWG_MM_MATCH_MSK
#define XPB_CWG_MM_MATCH_MSK__FAWBIWC0_ID_MSK__SHIFT                                                          0x0
#define XPB_CWG_MM_MATCH_MSK__FAWBIWC1_ID_MSK__SHIFT                                                          0x8
#define XPB_CWG_MM_MATCH_MSK__FAWBIWC2_ID_MSK__SHIFT                                                          0x10
#define XPB_CWG_MM_MATCH_MSK__FAWBIWC3_ID_MSK__SHIFT                                                          0x18
#define XPB_CWG_MM_MATCH_MSK__FAWBIWC0_ID_MSK_MASK                                                            0x000000FFW
#define XPB_CWG_MM_MATCH_MSK__FAWBIWC1_ID_MSK_MASK                                                            0x0000FF00W
#define XPB_CWG_MM_MATCH_MSK__FAWBIWC2_ID_MSK_MASK                                                            0x00FF0000W
#define XPB_CWG_MM_MATCH_MSK__FAWBIWC3_ID_MSK_MASK                                                            0xFF000000W
//XPB_CWG_GFX_UNITID_MAPPING0
#define XPB_CWG_GFX_UNITID_MAPPING0__UNITID_WOW__SHIFT                                                        0x0
#define XPB_CWG_GFX_UNITID_MAPPING0__UNITID_VWD__SHIFT                                                        0x5
#define XPB_CWG_GFX_UNITID_MAPPING0__DEST_CWG_NUM__SHIFT                                                      0x6
#define XPB_CWG_GFX_UNITID_MAPPING0__UNITID_WOW_MASK                                                          0x0000001FW
#define XPB_CWG_GFX_UNITID_MAPPING0__UNITID_VWD_MASK                                                          0x00000020W
#define XPB_CWG_GFX_UNITID_MAPPING0__DEST_CWG_NUM_MASK                                                        0x000001C0W
//XPB_CWG_GFX_UNITID_MAPPING1
#define XPB_CWG_GFX_UNITID_MAPPING1__UNITID_WOW__SHIFT                                                        0x0
#define XPB_CWG_GFX_UNITID_MAPPING1__UNITID_VWD__SHIFT                                                        0x5
#define XPB_CWG_GFX_UNITID_MAPPING1__DEST_CWG_NUM__SHIFT                                                      0x6
#define XPB_CWG_GFX_UNITID_MAPPING1__UNITID_WOW_MASK                                                          0x0000001FW
#define XPB_CWG_GFX_UNITID_MAPPING1__UNITID_VWD_MASK                                                          0x00000020W
#define XPB_CWG_GFX_UNITID_MAPPING1__DEST_CWG_NUM_MASK                                                        0x000001C0W
//XPB_CWG_GFX_UNITID_MAPPING2
#define XPB_CWG_GFX_UNITID_MAPPING2__UNITID_WOW__SHIFT                                                        0x0
#define XPB_CWG_GFX_UNITID_MAPPING2__UNITID_VWD__SHIFT                                                        0x5
#define XPB_CWG_GFX_UNITID_MAPPING2__DEST_CWG_NUM__SHIFT                                                      0x6
#define XPB_CWG_GFX_UNITID_MAPPING2__UNITID_WOW_MASK                                                          0x0000001FW
#define XPB_CWG_GFX_UNITID_MAPPING2__UNITID_VWD_MASK                                                          0x00000020W
#define XPB_CWG_GFX_UNITID_MAPPING2__DEST_CWG_NUM_MASK                                                        0x000001C0W
//XPB_CWG_GFX_UNITID_MAPPING3
#define XPB_CWG_GFX_UNITID_MAPPING3__UNITID_WOW__SHIFT                                                        0x0
#define XPB_CWG_GFX_UNITID_MAPPING3__UNITID_VWD__SHIFT                                                        0x5
#define XPB_CWG_GFX_UNITID_MAPPING3__DEST_CWG_NUM__SHIFT                                                      0x6
#define XPB_CWG_GFX_UNITID_MAPPING3__UNITID_WOW_MASK                                                          0x0000001FW
#define XPB_CWG_GFX_UNITID_MAPPING3__UNITID_VWD_MASK                                                          0x00000020W
#define XPB_CWG_GFX_UNITID_MAPPING3__DEST_CWG_NUM_MASK                                                        0x000001C0W
//XPB_CWG_GFX_UNITID_MAPPING4
#define XPB_CWG_GFX_UNITID_MAPPING4__UNITID_WOW__SHIFT                                                        0x0
#define XPB_CWG_GFX_UNITID_MAPPING4__UNITID_VWD__SHIFT                                                        0x5
#define XPB_CWG_GFX_UNITID_MAPPING4__DEST_CWG_NUM__SHIFT                                                      0x6
#define XPB_CWG_GFX_UNITID_MAPPING4__UNITID_WOW_MASK                                                          0x0000001FW
#define XPB_CWG_GFX_UNITID_MAPPING4__UNITID_VWD_MASK                                                          0x00000020W
#define XPB_CWG_GFX_UNITID_MAPPING4__DEST_CWG_NUM_MASK                                                        0x000001C0W
//XPB_CWG_GFX_UNITID_MAPPING5
#define XPB_CWG_GFX_UNITID_MAPPING5__UNITID_WOW__SHIFT                                                        0x0
#define XPB_CWG_GFX_UNITID_MAPPING5__UNITID_VWD__SHIFT                                                        0x5
#define XPB_CWG_GFX_UNITID_MAPPING5__DEST_CWG_NUM__SHIFT                                                      0x6
#define XPB_CWG_GFX_UNITID_MAPPING5__UNITID_WOW_MASK                                                          0x0000001FW
#define XPB_CWG_GFX_UNITID_MAPPING5__UNITID_VWD_MASK                                                          0x00000020W
#define XPB_CWG_GFX_UNITID_MAPPING5__DEST_CWG_NUM_MASK                                                        0x000001C0W
//XPB_CWG_GFX_UNITID_MAPPING6
#define XPB_CWG_GFX_UNITID_MAPPING6__UNITID_WOW__SHIFT                                                        0x0
#define XPB_CWG_GFX_UNITID_MAPPING6__UNITID_VWD__SHIFT                                                        0x5
#define XPB_CWG_GFX_UNITID_MAPPING6__DEST_CWG_NUM__SHIFT                                                      0x6
#define XPB_CWG_GFX_UNITID_MAPPING6__UNITID_WOW_MASK                                                          0x0000001FW
#define XPB_CWG_GFX_UNITID_MAPPING6__UNITID_VWD_MASK                                                          0x00000020W
#define XPB_CWG_GFX_UNITID_MAPPING6__DEST_CWG_NUM_MASK                                                        0x000001C0W
//XPB_CWG_GFX_UNITID_MAPPING7
#define XPB_CWG_GFX_UNITID_MAPPING7__UNITID_WOW__SHIFT                                                        0x0
#define XPB_CWG_GFX_UNITID_MAPPING7__UNITID_VWD__SHIFT                                                        0x5
#define XPB_CWG_GFX_UNITID_MAPPING7__DEST_CWG_NUM__SHIFT                                                      0x6
#define XPB_CWG_GFX_UNITID_MAPPING7__UNITID_WOW_MASK                                                          0x0000001FW
#define XPB_CWG_GFX_UNITID_MAPPING7__UNITID_VWD_MASK                                                          0x00000020W
#define XPB_CWG_GFX_UNITID_MAPPING7__DEST_CWG_NUM_MASK                                                        0x000001C0W
//XPB_CWG_MM_UNITID_MAPPING0
#define XPB_CWG_MM_UNITID_MAPPING0__UNITID_WOW__SHIFT                                                         0x0
#define XPB_CWG_MM_UNITID_MAPPING0__UNITID_VWD__SHIFT                                                         0x5
#define XPB_CWG_MM_UNITID_MAPPING0__DEST_CWG_NUM__SHIFT                                                       0x6
#define XPB_CWG_MM_UNITID_MAPPING0__UNITID_WOW_MASK                                                           0x0000001FW
#define XPB_CWG_MM_UNITID_MAPPING0__UNITID_VWD_MASK                                                           0x00000020W
#define XPB_CWG_MM_UNITID_MAPPING0__DEST_CWG_NUM_MASK                                                         0x000001C0W
//XPB_CWG_MM_UNITID_MAPPING1
#define XPB_CWG_MM_UNITID_MAPPING1__UNITID_WOW__SHIFT                                                         0x0
#define XPB_CWG_MM_UNITID_MAPPING1__UNITID_VWD__SHIFT                                                         0x5
#define XPB_CWG_MM_UNITID_MAPPING1__DEST_CWG_NUM__SHIFT                                                       0x6
#define XPB_CWG_MM_UNITID_MAPPING1__UNITID_WOW_MASK                                                           0x0000001FW
#define XPB_CWG_MM_UNITID_MAPPING1__UNITID_VWD_MASK                                                           0x00000020W
#define XPB_CWG_MM_UNITID_MAPPING1__DEST_CWG_NUM_MASK                                                         0x000001C0W
//XPB_CWG_MM_UNITID_MAPPING2
#define XPB_CWG_MM_UNITID_MAPPING2__UNITID_WOW__SHIFT                                                         0x0
#define XPB_CWG_MM_UNITID_MAPPING2__UNITID_VWD__SHIFT                                                         0x5
#define XPB_CWG_MM_UNITID_MAPPING2__DEST_CWG_NUM__SHIFT                                                       0x6
#define XPB_CWG_MM_UNITID_MAPPING2__UNITID_WOW_MASK                                                           0x0000001FW
#define XPB_CWG_MM_UNITID_MAPPING2__UNITID_VWD_MASK                                                           0x00000020W
#define XPB_CWG_MM_UNITID_MAPPING2__DEST_CWG_NUM_MASK                                                         0x000001C0W
//XPB_CWG_MM_UNITID_MAPPING3
#define XPB_CWG_MM_UNITID_MAPPING3__UNITID_WOW__SHIFT                                                         0x0
#define XPB_CWG_MM_UNITID_MAPPING3__UNITID_VWD__SHIFT                                                         0x5
#define XPB_CWG_MM_UNITID_MAPPING3__DEST_CWG_NUM__SHIFT                                                       0x6
#define XPB_CWG_MM_UNITID_MAPPING3__UNITID_WOW_MASK                                                           0x0000001FW
#define XPB_CWG_MM_UNITID_MAPPING3__UNITID_VWD_MASK                                                           0x00000020W
#define XPB_CWG_MM_UNITID_MAPPING3__DEST_CWG_NUM_MASK                                                         0x000001C0W


// addwessBwock: aid_athub_wpbdec
//WPB_PASSPW_CONF
#define WPB_PASSPW_CONF__XPB_PASSPW_OVEWWIDE__SHIFT                                                           0x0
#define WPB_PASSPW_CONF__XPB_WSPPASSPW_OVEWWIDE__SHIFT                                                        0x1
#define WPB_PASSPW_CONF__ATC_TW_PASSPW_OVEWWIDE__SHIFT                                                        0x2
#define WPB_PASSPW_CONF__ATC_PAGE_PASSPW_OVEWWIDE__SHIFT                                                      0x3
#define WPB_PASSPW_CONF__WW_PASSPW_OVEWWIDE__SHIFT                                                            0x4
#define WPB_PASSPW_CONF__WD_PASSPW_OVEWWIDE__SHIFT                                                            0x5
#define WPB_PASSPW_CONF__WW_WSPPASSPW_OVEWWIDE__SHIFT                                                         0x6
#define WPB_PASSPW_CONF__WD_WSPPASSPW_OVEWWIDE__SHIFT                                                         0x7
#define WPB_PASSPW_CONF__ATC_WSPPASSPW_OVEWWIDE__SHIFT                                                        0x8
#define WPB_PASSPW_CONF__ATOMIC_PASSPW_OVEWWIDE__SHIFT                                                        0x9
#define WPB_PASSPW_CONF__ATOMIC_WSPPASSPW_OVEWWIDE__SHIFT                                                     0xa
#define WPB_PASSPW_CONF__ATC_TW_PASSPW_OVEWWIDE_EN__SHIFT                                                     0xb
#define WPB_PASSPW_CONF__ATC_PAGE_PASSPW_OVEWWIDE_EN__SHIFT                                                   0xc
#define WPB_PASSPW_CONF__ATC_WSPPASSPW_OVEWWIDE_EN__SHIFT                                                     0xd
#define WPB_PASSPW_CONF__WWWSP_PASSPW_OVEWWIDE__SHIFT                                                         0xe
#define WPB_PASSPW_CONF__WWWSP_PASSPW_OVEWWIDE_EN__SHIFT                                                      0xf
#define WPB_PASSPW_CONF__WDWSP_PASSPW_OVEWWIDE__SHIFT                                                         0x10
#define WPB_PASSPW_CONF__WDWSP_PASSPW_OVEWWIDE_EN__SHIFT                                                      0x11
#define WPB_PASSPW_CONF__XPB_PASSPW_OVEWWIDE_MASK                                                             0x00000001W
#define WPB_PASSPW_CONF__XPB_WSPPASSPW_OVEWWIDE_MASK                                                          0x00000002W
#define WPB_PASSPW_CONF__ATC_TW_PASSPW_OVEWWIDE_MASK                                                          0x00000004W
#define WPB_PASSPW_CONF__ATC_PAGE_PASSPW_OVEWWIDE_MASK                                                        0x00000008W
#define WPB_PASSPW_CONF__WW_PASSPW_OVEWWIDE_MASK                                                              0x00000010W
#define WPB_PASSPW_CONF__WD_PASSPW_OVEWWIDE_MASK                                                              0x00000020W
#define WPB_PASSPW_CONF__WW_WSPPASSPW_OVEWWIDE_MASK                                                           0x00000040W
#define WPB_PASSPW_CONF__WD_WSPPASSPW_OVEWWIDE_MASK                                                           0x00000080W
#define WPB_PASSPW_CONF__ATC_WSPPASSPW_OVEWWIDE_MASK                                                          0x00000100W
#define WPB_PASSPW_CONF__ATOMIC_PASSPW_OVEWWIDE_MASK                                                          0x00000200W
#define WPB_PASSPW_CONF__ATOMIC_WSPPASSPW_OVEWWIDE_MASK                                                       0x00000400W
#define WPB_PASSPW_CONF__ATC_TW_PASSPW_OVEWWIDE_EN_MASK                                                       0x00000800W
#define WPB_PASSPW_CONF__ATC_PAGE_PASSPW_OVEWWIDE_EN_MASK                                                     0x00001000W
#define WPB_PASSPW_CONF__ATC_WSPPASSPW_OVEWWIDE_EN_MASK                                                       0x00002000W
#define WPB_PASSPW_CONF__WWWSP_PASSPW_OVEWWIDE_MASK                                                           0x00004000W
#define WPB_PASSPW_CONF__WWWSP_PASSPW_OVEWWIDE_EN_MASK                                                        0x00008000W
#define WPB_PASSPW_CONF__WDWSP_PASSPW_OVEWWIDE_MASK                                                           0x00010000W
#define WPB_PASSPW_CONF__WDWSP_PASSPW_OVEWWIDE_EN_MASK                                                        0x00020000W
//WPB_BWOCKWEVEW_CONF
#define WPB_BWOCKWEVEW_CONF__XPB_BWOCKWEVEW_OVEWWIDE__SHIFT                                                   0x0
#define WPB_BWOCKWEVEW_CONF__ATC_VC0_TW_BWOCKWEVEW__SHIFT                                                     0x2
#define WPB_BWOCKWEVEW_CONF__ATC_VC5_TW_BWOCKWEVEW__SHIFT                                                     0x4
#define WPB_BWOCKWEVEW_CONF__ATC_PAGE_BWOCKWEVEW__SHIFT                                                       0x6
#define WPB_BWOCKWEVEW_CONF__ATC_INV_BWOCKWEVEW__SHIFT                                                        0x8
#define WPB_BWOCKWEVEW_CONF__IO_WW_BWOCKWEVEW_OVEWWIDE__SHIFT                                                 0xa
#define WPB_BWOCKWEVEW_CONF__IO_WD_BWOCKWEVEW_OVEWWIDE__SHIFT                                                 0xc
#define WPB_BWOCKWEVEW_CONF__ATOMIC_BWOCKWEVEW_OVEWWIDE__SHIFT                                                0xe
#define WPB_BWOCKWEVEW_CONF__XPB_BWOCKWEVEW_OVEWWIDE_EN__SHIFT                                                0x10
#define WPB_BWOCKWEVEW_CONF__IO_WW_BWOCKWEVEW_OVEWWIDE_EN__SHIFT                                              0x11
#define WPB_BWOCKWEVEW_CONF__IO_WD_BWOCKWEVEW_OVEWWIDE_EN__SHIFT                                              0x12
#define WPB_BWOCKWEVEW_CONF__ATOMIC_BWOCKWEVEW_OVEWWIDE_EN__SHIFT                                             0x13
#define WPB_BWOCKWEVEW_CONF__XPB_BWOCKWEVEW_OVEWWIDE_MASK                                                     0x00000003W
#define WPB_BWOCKWEVEW_CONF__ATC_VC0_TW_BWOCKWEVEW_MASK                                                       0x0000000CW
#define WPB_BWOCKWEVEW_CONF__ATC_VC5_TW_BWOCKWEVEW_MASK                                                       0x00000030W
#define WPB_BWOCKWEVEW_CONF__ATC_PAGE_BWOCKWEVEW_MASK                                                         0x000000C0W
#define WPB_BWOCKWEVEW_CONF__ATC_INV_BWOCKWEVEW_MASK                                                          0x00000300W
#define WPB_BWOCKWEVEW_CONF__IO_WW_BWOCKWEVEW_OVEWWIDE_MASK                                                   0x00000C00W
#define WPB_BWOCKWEVEW_CONF__IO_WD_BWOCKWEVEW_OVEWWIDE_MASK                                                   0x00003000W
#define WPB_BWOCKWEVEW_CONF__ATOMIC_BWOCKWEVEW_OVEWWIDE_MASK                                                  0x0000C000W
#define WPB_BWOCKWEVEW_CONF__XPB_BWOCKWEVEW_OVEWWIDE_EN_MASK                                                  0x00010000W
#define WPB_BWOCKWEVEW_CONF__IO_WW_BWOCKWEVEW_OVEWWIDE_EN_MASK                                                0x00020000W
#define WPB_BWOCKWEVEW_CONF__IO_WD_BWOCKWEVEW_OVEWWIDE_EN_MASK                                                0x00040000W
#define WPB_BWOCKWEVEW_CONF__ATOMIC_BWOCKWEVEW_OVEWWIDE_EN_MASK                                               0x00080000W
//WPB_TAG_CONF
#define WPB_TAG_CONF__WPB_ATS_VC0_TW__SHIFT                                                                   0x0
#define WPB_TAG_CONF__WPB_ATS_VC5_TW__SHIFT                                                                   0xa
#define WPB_TAG_CONF__WPB_ATS_PW__SHIFT                                                                       0x14
#define WPB_TAG_CONF__WPB_ATS_VC0_TW_MASK                                                                     0x000003FFW
#define WPB_TAG_CONF__WPB_ATS_VC5_TW_MASK                                                                     0x000FFC00W
#define WPB_TAG_CONF__WPB_ATS_PW_MASK                                                                         0x3FF00000W
//WPB_TAG_CONF2
#define WPB_TAG_CONF2__WPB_IO_WW__SHIFT                                                                       0x0
#define WPB_TAG_CONF2__WPB_IO_MAX_WIMIT__SHIFT                                                                0xa
#define WPB_TAG_CONF2__WPB_IO_WD_MAWGIN__SHIFT                                                                0x15
#define WPB_TAG_CONF2__WPB_IO_WW_MASK                                                                         0x000003FFW
#define WPB_TAG_CONF2__WPB_IO_MAX_WIMIT_MASK                                                                  0x001FFC00W
#define WPB_TAG_CONF2__WPB_IO_WD_MAWGIN_MASK                                                                  0xFFE00000W
//WPB_AWB_CNTW
#define WPB_AWB_CNTW__WD_SWITCH_NUM__SHIFT                                                                    0x0
#define WPB_AWB_CNTW__WW_SWITCH_NUM__SHIFT                                                                    0x8
#define WPB_AWB_CNTW__ATC_TW_SWITCH_NUM__SHIFT                                                                0x10
#define WPB_AWB_CNTW__AWB_MODE__SHIFT                                                                         0x18
#define WPB_AWB_CNTW__SWITCH_NUM_MODE__SHIFT                                                                  0x19
#define WPB_AWB_CNTW__WD_SWITCH_NUM_MASK                                                                      0x000000FFW
#define WPB_AWB_CNTW__WW_SWITCH_NUM_MASK                                                                      0x0000FF00W
#define WPB_AWB_CNTW__ATC_TW_SWITCH_NUM_MASK                                                                  0x00FF0000W
#define WPB_AWB_CNTW__AWB_MODE_MASK                                                                           0x01000000W
#define WPB_AWB_CNTW__SWITCH_NUM_MODE_MASK                                                                    0x02000000W
//WPB_AWB_CNTW2
#define WPB_AWB_CNTW2__P2P_SWITCH_NUM__SHIFT                                                                  0x0
#define WPB_AWB_CNTW2__ATOMIC_SWITCH_NUM__SHIFT                                                               0x8
#define WPB_AWB_CNTW2__ATC_PAGE_SWITCH_NUM__SHIFT                                                             0x10
#define WPB_AWB_CNTW2__P2P_SWITCH_NUM_MASK                                                                    0x000000FFW
#define WPB_AWB_CNTW2__ATOMIC_SWITCH_NUM_MASK                                                                 0x0000FF00W
#define WPB_AWB_CNTW2__ATC_PAGE_SWITCH_NUM_MASK                                                               0x00FF0000W
//WPB_BIF_CNTW
#define WPB_BIF_CNTW__AWB_MODE__SHIFT                                                                         0x0
#define WPB_BIF_CNTW__DWAIN_VC_NUM__SHIFT                                                                     0x1
#define WPB_BIF_CNTW__SWITCH_ENABWE__SHIFT                                                                    0x3
#define WPB_BIF_CNTW__SWITCH_THWESHOWD__SHIFT                                                                 0x4
#define WPB_BIF_CNTW__PAGE_PWI_EN__SHIFT                                                                      0xc
#define WPB_BIF_CNTW__VC0TW_PWI_EN__SHIFT                                                                     0xd
#define WPB_BIF_CNTW__VC5TW_PWI_EN__SHIFT                                                                     0xe
#define WPB_BIF_CNTW__VC0_CHAINED_OVEWWIDE__SHIFT                                                             0xf
#define WPB_BIF_CNTW__AWB_MODE_MASK                                                                           0x00000001W
#define WPB_BIF_CNTW__DWAIN_VC_NUM_MASK                                                                       0x00000006W
#define WPB_BIF_CNTW__SWITCH_ENABWE_MASK                                                                      0x00000008W
#define WPB_BIF_CNTW__SWITCH_THWESHOWD_MASK                                                                   0x00000FF0W
#define WPB_BIF_CNTW__PAGE_PWI_EN_MASK                                                                        0x00001000W
#define WPB_BIF_CNTW__VC0TW_PWI_EN_MASK                                                                       0x00002000W
#define WPB_BIF_CNTW__VC5TW_PWI_EN_MASK                                                                       0x00004000W
#define WPB_BIF_CNTW__VC0_CHAINED_OVEWWIDE_MASK                                                               0x00008000W
//WPB_BIF_CNTW2
#define WPB_BIF_CNTW2__VC0_SWITCH_NUM__SHIFT                                                                  0x0
#define WPB_BIF_CNTW2__VC1_SWITCH_NUM__SHIFT                                                                  0x8
#define WPB_BIF_CNTW2__VC5_SWITCH_NUM__SHIFT                                                                  0x10
#define WPB_BIF_CNTW2__VC0_SWITCH_NUM_MASK                                                                    0x000000FFW
#define WPB_BIF_CNTW2__VC1_SWITCH_NUM_MASK                                                                    0x0000FF00W
#define WPB_BIF_CNTW2__VC5_SWITCH_NUM_MASK                                                                    0x00FF0000W
//WPB_PEWF_COUNTEW_CNTW
#define WPB_PEWF_COUNTEW_CNTW__PEWF_COUNTEW_SEWECT__SHIFT                                                     0x0
#define WPB_PEWF_COUNTEW_CNTW__CWEAW_SEWECTED_PEWF_COUNTEW__SHIFT                                             0x2
#define WPB_PEWF_COUNTEW_CNTW__CWEAW_AWW_PEWF_COUNTEWS__SHIFT                                                 0x3
#define WPB_PEWF_COUNTEW_CNTW__STOP_ON_COUNTEW_SATUWATION__SHIFT                                              0x4
#define WPB_PEWF_COUNTEW_CNTW__ENABWE_PEWF_COUNTEWS__SHIFT                                                    0x5
#define WPB_PEWF_COUNTEW_CNTW__PEWF_COUNTEW_ASSIGN_0__SHIFT                                                   0x9
#define WPB_PEWF_COUNTEW_CNTW__PEWF_COUNTEW_ASSIGN_1__SHIFT                                                   0xe
#define WPB_PEWF_COUNTEW_CNTW__PEWF_COUNTEW_ASSIGN_2__SHIFT                                                   0x13
#define WPB_PEWF_COUNTEW_CNTW__PEWF_COUNTEW_ASSIGN_3__SHIFT                                                   0x18
#define WPB_PEWF_COUNTEW_CNTW__PEWF_COUNTEW_SEWECT_MASK                                                       0x00000003W
#define WPB_PEWF_COUNTEW_CNTW__CWEAW_SEWECTED_PEWF_COUNTEW_MASK                                               0x00000004W
#define WPB_PEWF_COUNTEW_CNTW__CWEAW_AWW_PEWF_COUNTEWS_MASK                                                   0x00000008W
#define WPB_PEWF_COUNTEW_CNTW__STOP_ON_COUNTEW_SATUWATION_MASK                                                0x00000010W
#define WPB_PEWF_COUNTEW_CNTW__ENABWE_PEWF_COUNTEWS_MASK                                                      0x000001E0W
#define WPB_PEWF_COUNTEW_CNTW__PEWF_COUNTEW_ASSIGN_0_MASK                                                     0x00003E00W
#define WPB_PEWF_COUNTEW_CNTW__PEWF_COUNTEW_ASSIGN_1_MASK                                                     0x0007C000W
#define WPB_PEWF_COUNTEW_CNTW__PEWF_COUNTEW_ASSIGN_2_MASK                                                     0x00F80000W
#define WPB_PEWF_COUNTEW_CNTW__PEWF_COUNTEW_ASSIGN_3_MASK                                                     0x1F000000W
//WPB_DEINTWWV_COMBINE_CNTW
#define WPB_DEINTWWV_COMBINE_CNTW__WC_CHAINED_FWUSH_TIMEW__SHIFT                                              0x0
#define WPB_DEINTWWV_COMBINE_CNTW__WC_CHAINED_BWEAK_EN__SHIFT                                                 0x4
#define WPB_DEINTWWV_COMBINE_CNTW__WC_HANDWE_CHECK_DISABWE__SHIFT                                             0x5
#define WPB_DEINTWWV_COMBINE_CNTW__WC_CWI_INTWV_EN__SHIFT                                                     0x6
#define WPB_DEINTWWV_COMBINE_CNTW__WC_CHAINED_FWUSH_TIMEW_MASK                                                0x0000000FW
#define WPB_DEINTWWV_COMBINE_CNTW__WC_CHAINED_BWEAK_EN_MASK                                                   0x00000010W
#define WPB_DEINTWWV_COMBINE_CNTW__WC_HANDWE_CHECK_DISABWE_MASK                                               0x00000020W
#define WPB_DEINTWWV_COMBINE_CNTW__WC_CWI_INTWV_EN_MASK                                                       0x00000040W
//WPB_VC_SWITCH_WDWW
#define WPB_VC_SWITCH_WDWW__MODE__SHIFT                                                                       0x0
#define WPB_VC_SWITCH_WDWW__NUM_WD__SHIFT                                                                     0x2
#define WPB_VC_SWITCH_WDWW__NUM_WW__SHIFT                                                                     0xa
#define WPB_VC_SWITCH_WDWW__XPB_WDWEQ_CWD__SHIFT                                                              0x12
#define WPB_VC_SWITCH_WDWW__MODE_MASK                                                                         0x00000003W
#define WPB_VC_SWITCH_WDWW__NUM_WD_MASK                                                                       0x000003FCW
#define WPB_VC_SWITCH_WDWW__NUM_WW_MASK                                                                       0x0003FC00W
#define WPB_VC_SWITCH_WDWW__XPB_WDWEQ_CWD_MASK                                                                0x03FC0000W
//WPB_PEWFCOUNTEW_WO
#define WPB_PEWFCOUNTEW_WO__COUNTEW_WO__SHIFT                                                                 0x0
#define WPB_PEWFCOUNTEW_WO__COUNTEW_WO_MASK                                                                   0xFFFFFFFFW
//WPB_PEWFCOUNTEW_HI
#define WPB_PEWFCOUNTEW_HI__COUNTEW_HI__SHIFT                                                                 0x0
#define WPB_PEWFCOUNTEW_HI__COMPAWE_VAWUE__SHIFT                                                              0x10
#define WPB_PEWFCOUNTEW_HI__COUNTEW_HI_MASK                                                                   0x0000FFFFW
#define WPB_PEWFCOUNTEW_HI__COMPAWE_VAWUE_MASK                                                                0xFFFF0000W
//WPB_PEWFCOUNTEW0_CFG
#define WPB_PEWFCOUNTEW0_CFG__PEWF_SEW__SHIFT                                                                 0x0
#define WPB_PEWFCOUNTEW0_CFG__PEWF_SEW_END__SHIFT                                                             0x8
#define WPB_PEWFCOUNTEW0_CFG__PEWF_MODE__SHIFT                                                                0x18
#define WPB_PEWFCOUNTEW0_CFG__ENABWE__SHIFT                                                                   0x1c
#define WPB_PEWFCOUNTEW0_CFG__CWEAW__SHIFT                                                                    0x1d
#define WPB_PEWFCOUNTEW0_CFG__PEWF_SEW_MASK                                                                   0x000000FFW
#define WPB_PEWFCOUNTEW0_CFG__PEWF_SEW_END_MASK                                                               0x0000FF00W
#define WPB_PEWFCOUNTEW0_CFG__PEWF_MODE_MASK                                                                  0x0F000000W
#define WPB_PEWFCOUNTEW0_CFG__ENABWE_MASK                                                                     0x10000000W
#define WPB_PEWFCOUNTEW0_CFG__CWEAW_MASK                                                                      0x20000000W
//WPB_PEWFCOUNTEW1_CFG
#define WPB_PEWFCOUNTEW1_CFG__PEWF_SEW__SHIFT                                                                 0x0
#define WPB_PEWFCOUNTEW1_CFG__PEWF_SEW_END__SHIFT                                                             0x8
#define WPB_PEWFCOUNTEW1_CFG__PEWF_MODE__SHIFT                                                                0x18
#define WPB_PEWFCOUNTEW1_CFG__ENABWE__SHIFT                                                                   0x1c
#define WPB_PEWFCOUNTEW1_CFG__CWEAW__SHIFT                                                                    0x1d
#define WPB_PEWFCOUNTEW1_CFG__PEWF_SEW_MASK                                                                   0x000000FFW
#define WPB_PEWFCOUNTEW1_CFG__PEWF_SEW_END_MASK                                                               0x0000FF00W
#define WPB_PEWFCOUNTEW1_CFG__PEWF_MODE_MASK                                                                  0x0F000000W
#define WPB_PEWFCOUNTEW1_CFG__ENABWE_MASK                                                                     0x10000000W
#define WPB_PEWFCOUNTEW1_CFG__CWEAW_MASK                                                                      0x20000000W
//WPB_PEWFCOUNTEW2_CFG
#define WPB_PEWFCOUNTEW2_CFG__PEWF_SEW__SHIFT                                                                 0x0
#define WPB_PEWFCOUNTEW2_CFG__PEWF_SEW_END__SHIFT                                                             0x8
#define WPB_PEWFCOUNTEW2_CFG__PEWF_MODE__SHIFT                                                                0x18
#define WPB_PEWFCOUNTEW2_CFG__ENABWE__SHIFT                                                                   0x1c
#define WPB_PEWFCOUNTEW2_CFG__CWEAW__SHIFT                                                                    0x1d
#define WPB_PEWFCOUNTEW2_CFG__PEWF_SEW_MASK                                                                   0x000000FFW
#define WPB_PEWFCOUNTEW2_CFG__PEWF_SEW_END_MASK                                                               0x0000FF00W
#define WPB_PEWFCOUNTEW2_CFG__PEWF_MODE_MASK                                                                  0x0F000000W
#define WPB_PEWFCOUNTEW2_CFG__ENABWE_MASK                                                                     0x10000000W
#define WPB_PEWFCOUNTEW2_CFG__CWEAW_MASK                                                                      0x20000000W
//WPB_PEWFCOUNTEW3_CFG
#define WPB_PEWFCOUNTEW3_CFG__PEWF_SEW__SHIFT                                                                 0x0
#define WPB_PEWFCOUNTEW3_CFG__PEWF_SEW_END__SHIFT                                                             0x8
#define WPB_PEWFCOUNTEW3_CFG__PEWF_MODE__SHIFT                                                                0x18
#define WPB_PEWFCOUNTEW3_CFG__ENABWE__SHIFT                                                                   0x1c
#define WPB_PEWFCOUNTEW3_CFG__CWEAW__SHIFT                                                                    0x1d
#define WPB_PEWFCOUNTEW3_CFG__PEWF_SEW_MASK                                                                   0x000000FFW
#define WPB_PEWFCOUNTEW3_CFG__PEWF_SEW_END_MASK                                                               0x0000FF00W
#define WPB_PEWFCOUNTEW3_CFG__PEWF_MODE_MASK                                                                  0x0F000000W
#define WPB_PEWFCOUNTEW3_CFG__ENABWE_MASK                                                                     0x10000000W
#define WPB_PEWFCOUNTEW3_CFG__CWEAW_MASK                                                                      0x20000000W
//WPB_PEWFCOUNTEW_WSWT_CNTW
#define WPB_PEWFCOUNTEW_WSWT_CNTW__PEWF_COUNTEW_SEWECT__SHIFT                                                 0x0
#define WPB_PEWFCOUNTEW_WSWT_CNTW__STAWT_TWIGGEW__SHIFT                                                       0x8
#define WPB_PEWFCOUNTEW_WSWT_CNTW__STOP_TWIGGEW__SHIFT                                                        0x10
#define WPB_PEWFCOUNTEW_WSWT_CNTW__ENABWE_ANY__SHIFT                                                          0x18
#define WPB_PEWFCOUNTEW_WSWT_CNTW__CWEAW_AWW__SHIFT                                                           0x19
#define WPB_PEWFCOUNTEW_WSWT_CNTW__STOP_AWW_ON_SATUWATE__SHIFT                                                0x1a
#define WPB_PEWFCOUNTEW_WSWT_CNTW__PEWF_COUNTEW_SEWECT_MASK                                                   0x0000000FW
#define WPB_PEWFCOUNTEW_WSWT_CNTW__STAWT_TWIGGEW_MASK                                                         0x0000FF00W
#define WPB_PEWFCOUNTEW_WSWT_CNTW__STOP_TWIGGEW_MASK                                                          0x00FF0000W
#define WPB_PEWFCOUNTEW_WSWT_CNTW__ENABWE_ANY_MASK                                                            0x01000000W
#define WPB_PEWFCOUNTEW_WSWT_CNTW__CWEAW_AWW_MASK                                                             0x02000000W
#define WPB_PEWFCOUNTEW_WSWT_CNTW__STOP_AWW_ON_SATUWATE_MASK                                                  0x04000000W
//WPB_ATS_CNTW
#define WPB_ATS_CNTW__PAGE_MIN_WATENCY_ENABWE__SHIFT                                                          0x0
#define WPB_ATS_CNTW__TW_MIN_WATENCY_ENABWE__SHIFT                                                            0x1
#define WPB_ATS_CNTW__SWITCH_THWESHOWD__SHIFT                                                                 0x2
#define WPB_ATS_CNTW__TIME_SWICE__SHIFT                                                                       0x7
#define WPB_ATS_CNTW__ATCTW_SWITCH_NUM__SHIFT                                                                 0xf
#define WPB_ATS_CNTW__ATCPAGE_SWITCH_NUM__SHIFT                                                               0x13
#define WPB_ATS_CNTW__WW_AT__SHIFT                                                                            0x17
#define WPB_ATS_CNTW__INVAW_COM_CMD__SHIFT                                                                    0x19
#define WPB_ATS_CNTW__PAGE_MIN_WATENCY_ENABWE_MASK                                                            0x00000001W
#define WPB_ATS_CNTW__TW_MIN_WATENCY_ENABWE_MASK                                                              0x00000002W
#define WPB_ATS_CNTW__SWITCH_THWESHOWD_MASK                                                                   0x0000007CW
#define WPB_ATS_CNTW__TIME_SWICE_MASK                                                                         0x00007F80W
#define WPB_ATS_CNTW__ATCTW_SWITCH_NUM_MASK                                                                   0x00078000W
#define WPB_ATS_CNTW__ATCPAGE_SWITCH_NUM_MASK                                                                 0x00780000W
#define WPB_ATS_CNTW__WW_AT_MASK                                                                              0x01800000W
#define WPB_ATS_CNTW__INVAW_COM_CMD_MASK                                                                      0x7E000000W
//WPB_ATS_CNTW2
#define WPB_ATS_CNTW2__TWANS_CMD__SHIFT                                                                       0x0
#define WPB_ATS_CNTW2__PAGE_WEQ_CMD__SHIFT                                                                    0x6
#define WPB_ATS_CNTW2__PAGE_WOUTING_CODE__SHIFT                                                               0xc
#define WPB_ATS_CNTW2__INVAW_COM_WOUTING_CODE__SHIFT                                                          0xf
#define WPB_ATS_CNTW2__VENDOW_ID__SHIFT                                                                       0x12
#define WPB_ATS_CNTW2__MM_TWANS_VC5_ENABWE__SHIFT                                                             0x14
#define WPB_ATS_CNTW2__GC_TWANS_VC5_ENABWE__SHIFT                                                             0x15
#define WPB_ATS_CNTW2__WPB_VC5_CWD__SHIFT                                                                     0x16
#define WPB_ATS_CNTW2__TWANS_CMD_MASK                                                                         0x0000003FW
#define WPB_ATS_CNTW2__PAGE_WEQ_CMD_MASK                                                                      0x00000FC0W
#define WPB_ATS_CNTW2__PAGE_WOUTING_CODE_MASK                                                                 0x00007000W
#define WPB_ATS_CNTW2__INVAW_COM_WOUTING_CODE_MASK                                                            0x00038000W
#define WPB_ATS_CNTW2__VENDOW_ID_MASK                                                                         0x000C0000W
#define WPB_ATS_CNTW2__MM_TWANS_VC5_ENABWE_MASK                                                               0x00100000W
#define WPB_ATS_CNTW2__GC_TWANS_VC5_ENABWE_MASK                                                               0x00200000W
#define WPB_ATS_CNTW2__WPB_VC5_CWD_MASK                                                                       0x07C00000W
//WPB_SDPPOWT_CNTW
#define WPB_SDPPOWT_CNTW__NBIF_DMA_SEWF_ACTIVATE__SHIFT                                                       0x0
#define WPB_SDPPOWT_CNTW__NBIF_DMA_CFG_MODE__SHIFT                                                            0x1
#define WPB_SDPPOWT_CNTW__NBIF_DMA_ENABWE_WEISSUE_CWEDIT__SHIFT                                               0x3
#define WPB_SDPPOWT_CNTW__NBIF_DMA_ENABWE_SATUWATE_COUNTEW__SHIFT                                             0x4
#define WPB_SDPPOWT_CNTW__NBIF_DMA_ENABWE_DISWUPT_FUWWDIS__SHIFT                                              0x5
#define WPB_SDPPOWT_CNTW__NBIF_DMA_HAWT_THWESHOWD__SHIFT                                                      0x6
#define WPB_SDPPOWT_CNTW__NBIF_HST_SEWF_ACTIVATE__SHIFT                                                       0xa
#define WPB_SDPPOWT_CNTW__NBIF_HST_CFG_MODE__SHIFT                                                            0xb
#define WPB_SDPPOWT_CNTW__NBIF_HST_ENABWE_WEISSUE_CWEDIT__SHIFT                                               0xd
#define WPB_SDPPOWT_CNTW__NBIF_HST_ENABWE_SATUWATE_COUNTEW__SHIFT                                             0xe
#define WPB_SDPPOWT_CNTW__NBIF_HST_ENABWE_DISWUPT_FUWWDIS__SHIFT                                              0xf
#define WPB_SDPPOWT_CNTW__NBIF_HST_HAWT_THWESHOWD__SHIFT                                                      0x10
#define WPB_SDPPOWT_CNTW__NBIF_HST_PASSIVE_MODE__SHIFT                                                        0x14
#define WPB_SDPPOWT_CNTW__NBIF_HST_QUICK_COMACK__SHIFT                                                        0x15
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WDWSPCKEN__SHIFT                                                         0x16
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WDWSPCKENWCV__SHIFT                                                      0x17
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WDWSPDATACKEN__SHIFT                                                     0x18
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WDWSPDATACKENWCV__SHIFT                                                  0x19
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WWWSPCKEN__SHIFT                                                         0x1a
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WWWSPCKENWCV__SHIFT                                                      0x1b
#define WPB_SDPPOWT_CNTW__DF_HAWT_THWESHOWD__SHIFT                                                            0x1c
#define WPB_SDPPOWT_CNTW__NBIF_DMA_SEWF_ACTIVATE_MASK                                                         0x00000001W
#define WPB_SDPPOWT_CNTW__NBIF_DMA_CFG_MODE_MASK                                                              0x00000006W
#define WPB_SDPPOWT_CNTW__NBIF_DMA_ENABWE_WEISSUE_CWEDIT_MASK                                                 0x00000008W
#define WPB_SDPPOWT_CNTW__NBIF_DMA_ENABWE_SATUWATE_COUNTEW_MASK                                               0x00000010W
#define WPB_SDPPOWT_CNTW__NBIF_DMA_ENABWE_DISWUPT_FUWWDIS_MASK                                                0x00000020W
#define WPB_SDPPOWT_CNTW__NBIF_DMA_HAWT_THWESHOWD_MASK                                                        0x000003C0W
#define WPB_SDPPOWT_CNTW__NBIF_HST_SEWF_ACTIVATE_MASK                                                         0x00000400W
#define WPB_SDPPOWT_CNTW__NBIF_HST_CFG_MODE_MASK                                                              0x00001800W
#define WPB_SDPPOWT_CNTW__NBIF_HST_ENABWE_WEISSUE_CWEDIT_MASK                                                 0x00002000W
#define WPB_SDPPOWT_CNTW__NBIF_HST_ENABWE_SATUWATE_COUNTEW_MASK                                               0x00004000W
#define WPB_SDPPOWT_CNTW__NBIF_HST_ENABWE_DISWUPT_FUWWDIS_MASK                                                0x00008000W
#define WPB_SDPPOWT_CNTW__NBIF_HST_HAWT_THWESHOWD_MASK                                                        0x000F0000W
#define WPB_SDPPOWT_CNTW__NBIF_HST_PASSIVE_MODE_MASK                                                          0x00100000W
#define WPB_SDPPOWT_CNTW__NBIF_HST_QUICK_COMACK_MASK                                                          0x00200000W
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WDWSPCKEN_MASK                                                           0x00400000W
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WDWSPCKENWCV_MASK                                                        0x00800000W
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WDWSPDATACKEN_MASK                                                       0x01000000W
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WDWSPDATACKENWCV_MASK                                                    0x02000000W
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WWWSPCKEN_MASK                                                           0x04000000W
#define WPB_SDPPOWT_CNTW__DF_SDPVDCI_WWWSPCKENWCV_MASK                                                        0x08000000W
#define WPB_SDPPOWT_CNTW__DF_HAWT_THWESHOWD_MASK                                                              0xF0000000W

#endif
