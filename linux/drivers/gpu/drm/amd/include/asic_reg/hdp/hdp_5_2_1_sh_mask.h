/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
#ifndef _hdp_5_2_1_SH_MASK_HEADEW
#define _hdp_5_2_1_SH_MASK_HEADEW


// addwessBwock: hdp_hdpdec
//HDP_MMHUB_TWVW
#define HDP_MMHUB_TWVW__HDP_WW_TWVW__SHIFT                                                                    0x0
#define HDP_MMHUB_TWVW__HDP_WD_TWVW__SHIFT                                                                    0x4
#define HDP_MMHUB_TWVW__XDP_WW_TWVW__SHIFT                                                                    0x8
#define HDP_MMHUB_TWVW__XDP_WD_TWVW__SHIFT                                                                    0xc
#define HDP_MMHUB_TWVW__XDP_MBX_WW_TWVW__SHIFT                                                                0x10
#define HDP_MMHUB_TWVW__HDP_WW_TWVW_MASK                                                                      0x0000000FW
#define HDP_MMHUB_TWVW__HDP_WD_TWVW_MASK                                                                      0x000000F0W
#define HDP_MMHUB_TWVW__XDP_WW_TWVW_MASK                                                                      0x00000F00W
#define HDP_MMHUB_TWVW__XDP_WD_TWVW_MASK                                                                      0x0000F000W
#define HDP_MMHUB_TWVW__XDP_MBX_WW_TWVW_MASK                                                                  0x000F0000W
//HDP_MMHUB_UNITID
#define HDP_MMHUB_UNITID__HDP_UNITID__SHIFT                                                                   0x0
#define HDP_MMHUB_UNITID__XDP_UNITID__SHIFT                                                                   0x8
#define HDP_MMHUB_UNITID__XDP_MBX_UNITID__SHIFT                                                               0x10
#define HDP_MMHUB_UNITID__HDP_UNITID_MASK                                                                     0x0000003FW
#define HDP_MMHUB_UNITID__XDP_UNITID_MASK                                                                     0x00003F00W
#define HDP_MMHUB_UNITID__XDP_MBX_UNITID_MASK                                                                 0x003F0000W
//HDP_NONSUWFACE_BASE
#define HDP_NONSUWFACE_BASE__NONSUWF_BASE_39_8__SHIFT                                                         0x0
#define HDP_NONSUWFACE_BASE__NONSUWF_BASE_39_8_MASK                                                           0xFFFFFFFFW
//HDP_NONSUWFACE_INFO
#define HDP_NONSUWFACE_INFO__NONSUWF_SWAP__SHIFT                                                              0x4
#define HDP_NONSUWFACE_INFO__NONSUWF_VMID__SHIFT                                                              0x8
#define HDP_NONSUWFACE_INFO__NONSUWF_SWAP_MASK                                                                0x00000030W
#define HDP_NONSUWFACE_INFO__NONSUWF_VMID_MASK                                                                0x00000F00W
//HDP_NONSUWFACE_BASE_HI
#define HDP_NONSUWFACE_BASE_HI__NONSUWF_BASE_47_40__SHIFT                                                     0x0
#define HDP_NONSUWFACE_BASE_HI__NONSUWF_BASE_47_40_MASK                                                       0x000000FFW
//HDP_SUWFACE_WWITE_FWAGS
#define HDP_SUWFACE_WWITE_FWAGS__SUWF0_WWITE_FWAG__SHIFT                                                      0x0
#define HDP_SUWFACE_WWITE_FWAGS__SUWF1_WWITE_FWAG__SHIFT                                                      0x1
#define HDP_SUWFACE_WWITE_FWAGS__SUWF0_WWITE_FWAG_MASK                                                        0x00000001W
#define HDP_SUWFACE_WWITE_FWAGS__SUWF1_WWITE_FWAG_MASK                                                        0x00000002W
//HDP_SUWFACE_WEAD_FWAGS
#define HDP_SUWFACE_WEAD_FWAGS__SUWF0_WEAD_FWAG__SHIFT                                                        0x0
#define HDP_SUWFACE_WEAD_FWAGS__SUWF1_WEAD_FWAG__SHIFT                                                        0x1
#define HDP_SUWFACE_WEAD_FWAGS__SUWF0_WEAD_FWAG_MASK                                                          0x00000001W
#define HDP_SUWFACE_WEAD_FWAGS__SUWF1_WEAD_FWAG_MASK                                                          0x00000002W
//HDP_SUWFACE_WWITE_FWAGS_CWW
#define HDP_SUWFACE_WWITE_FWAGS_CWW__SUWF0_WWITE_FWAG_CWW__SHIFT                                              0x0
#define HDP_SUWFACE_WWITE_FWAGS_CWW__SUWF1_WWITE_FWAG_CWW__SHIFT                                              0x1
#define HDP_SUWFACE_WWITE_FWAGS_CWW__SUWF0_WWITE_FWAG_CWW_MASK                                                0x00000001W
#define HDP_SUWFACE_WWITE_FWAGS_CWW__SUWF1_WWITE_FWAG_CWW_MASK                                                0x00000002W
//HDP_SUWFACE_WEAD_FWAGS_CWW
#define HDP_SUWFACE_WEAD_FWAGS_CWW__SUWF0_WEAD_FWAG_CWW__SHIFT                                                0x0
#define HDP_SUWFACE_WEAD_FWAGS_CWW__SUWF1_WEAD_FWAG_CWW__SHIFT                                                0x1
#define HDP_SUWFACE_WEAD_FWAGS_CWW__SUWF0_WEAD_FWAG_CWW_MASK                                                  0x00000001W
#define HDP_SUWFACE_WEAD_FWAGS_CWW__SUWF1_WEAD_FWAG_CWW_MASK                                                  0x00000002W
//HDP_NONSUWF_FWAGS
#define HDP_NONSUWF_FWAGS__NONSUWF_WWITE_FWAG__SHIFT                                                          0x0
#define HDP_NONSUWF_FWAGS__NONSUWF_WEAD_FWAG__SHIFT                                                           0x1
#define HDP_NONSUWF_FWAGS__NONSUWF_WWITE_FWAG_MASK                                                            0x00000001W
#define HDP_NONSUWF_FWAGS__NONSUWF_WEAD_FWAG_MASK                                                             0x00000002W
//HDP_NONSUWF_FWAGS_CWW
#define HDP_NONSUWF_FWAGS_CWW__NONSUWF_WWITE_FWAG_CWW__SHIFT                                                  0x0
#define HDP_NONSUWF_FWAGS_CWW__NONSUWF_WEAD_FWAG_CWW__SHIFT                                                   0x1
#define HDP_NONSUWF_FWAGS_CWW__NONSUWF_WWITE_FWAG_CWW_MASK                                                    0x00000001W
#define HDP_NONSUWF_FWAGS_CWW__NONSUWF_WEAD_FWAG_CWW_MASK                                                     0x00000002W
//HDP_HOST_PATH_CNTW
#define HDP_HOST_PATH_CNTW__WW_STAWW_TIMEW__SHIFT                                                             0x9
#define HDP_HOST_PATH_CNTW__WD_STAWW_TIMEW__SHIFT                                                             0xb
#define HDP_HOST_PATH_CNTW__WWITE_COMBINE_TIMEW_PWEWOAD_CFG__SHIFT                                            0x12
#define HDP_HOST_PATH_CNTW__WWITE_COMBINE_TIMEW__SHIFT                                                        0x13
#define HDP_HOST_PATH_CNTW__WWITE_COMBINE_EN__SHIFT                                                           0x15
#define HDP_HOST_PATH_CNTW__WWITE_COMBINE_64B_EN__SHIFT                                                       0x16
#define HDP_HOST_PATH_CNTW__AWW_SUWFACES_DIS__SHIFT                                                           0x1d
#define HDP_HOST_PATH_CNTW__WW_STAWW_TIMEW_MASK                                                               0x00000600W
#define HDP_HOST_PATH_CNTW__WD_STAWW_TIMEW_MASK                                                               0x00001800W
#define HDP_HOST_PATH_CNTW__WWITE_COMBINE_TIMEW_PWEWOAD_CFG_MASK                                              0x00040000W
#define HDP_HOST_PATH_CNTW__WWITE_COMBINE_TIMEW_MASK                                                          0x00180000W
#define HDP_HOST_PATH_CNTW__WWITE_COMBINE_EN_MASK                                                             0x00200000W
#define HDP_HOST_PATH_CNTW__WWITE_COMBINE_64B_EN_MASK                                                         0x00400000W
#define HDP_HOST_PATH_CNTW__AWW_SUWFACES_DIS_MASK                                                             0x20000000W
//HDP_SW_SEMAPHOWE
#define HDP_SW_SEMAPHOWE__SW_SEMAPHOWE__SHIFT                                                                 0x0
#define HDP_SW_SEMAPHOWE__SW_SEMAPHOWE_MASK                                                                   0xFFFFFFFFW
//HDP_DEBUG0
#define HDP_DEBUG0__HDP_DEBUG__SHIFT                                                                          0x0
#define HDP_DEBUG0__HDP_DEBUG_MASK                                                                            0xFFFFFFFFW
//HDP_WAST_SUWFACE_HIT
#define HDP_WAST_SUWFACE_HIT__WAST_SUWFACE_HIT__SHIFT                                                         0x0
#define HDP_WAST_SUWFACE_HIT__WAST_SUWFACE_HIT_MASK                                                           0x00000003W
//HDP_OUTSTANDING_WEQ
#define HDP_OUTSTANDING_WEQ__WWITE_WEQ__SHIFT                                                                 0x0
#define HDP_OUTSTANDING_WEQ__WEAD_WEQ__SHIFT                                                                  0x8
#define HDP_OUTSTANDING_WEQ__WWITE_WEQ_MASK                                                                   0x000000FFW
#define HDP_OUTSTANDING_WEQ__WEAD_WEQ_MASK                                                                    0x0000FF00W
//HDP_MISC_CNTW
#define HDP_MISC_CNTW__IDWE_HYSTEWESIS_CNTW__SHIFT                                                            0x2
#define HDP_MISC_CNTW__OUTSTANDING_WWITE_COUNT_1024__SHIFT                                                    0x5
#define HDP_MISC_CNTW__MMHUB_EAWWY_WWACK_ENABWE__SHIFT                                                        0x8
#define HDP_MISC_CNTW__EAWWY_WWACK_MISSING_PWOTECT_ENABWE__SHIFT                                              0x9
#define HDP_MISC_CNTW__SIMUWTANEOUS_WEADS_WWITES__SHIFT                                                       0xb
#define HDP_MISC_CNTW__WEAD_BUFFEW_WATEWMAWK__SHIFT                                                           0xe
#define HDP_MISC_CNTW__NACK_ENABWE__SHIFT                                                                     0x13
#define HDP_MISC_CNTW__ATOMIC_NACK_ENABWE__SHIFT                                                              0x14
#define HDP_MISC_CNTW__FED_ENABWE__SHIFT                                                                      0x15
#define HDP_MISC_CNTW__ATOMIC_FED_ENABWE__SHIFT                                                               0x16
#define HDP_MISC_CNTW__SYSHUB_CHANNEW_PWIOWITY__SHIFT                                                         0x17
#define HDP_MISC_CNTW__MMHUB_WWBUWST_ENABWE__SHIFT                                                            0x18
#define HDP_MISC_CNTW__MMHUB_WWBUWST_SIZE__SHIFT                                                              0x1e
#define HDP_MISC_CNTW__IDWE_HYSTEWESIS_CNTW_MASK                                                              0x0000000CW
#define HDP_MISC_CNTW__OUTSTANDING_WWITE_COUNT_1024_MASK                                                      0x00000020W
#define HDP_MISC_CNTW__MMHUB_EAWWY_WWACK_ENABWE_MASK                                                          0x00000100W
#define HDP_MISC_CNTW__EAWWY_WWACK_MISSING_PWOTECT_ENABWE_MASK                                                0x00000200W
#define HDP_MISC_CNTW__SIMUWTANEOUS_WEADS_WWITES_MASK                                                         0x00000800W
#define HDP_MISC_CNTW__WEAD_BUFFEW_WATEWMAWK_MASK                                                             0x0000C000W
#define HDP_MISC_CNTW__NACK_ENABWE_MASK                                                                       0x00080000W
#define HDP_MISC_CNTW__ATOMIC_NACK_ENABWE_MASK                                                                0x00100000W
#define HDP_MISC_CNTW__FED_ENABWE_MASK                                                                        0x00200000W
#define HDP_MISC_CNTW__ATOMIC_FED_ENABWE_MASK                                                                 0x00400000W
#define HDP_MISC_CNTW__SYSHUB_CHANNEW_PWIOWITY_MASK                                                           0x00800000W
#define HDP_MISC_CNTW__MMHUB_WWBUWST_ENABWE_MASK                                                              0x01000000W
#define HDP_MISC_CNTW__MMHUB_WWBUWST_SIZE_MASK                                                                0x40000000W
//HDP_MEM_POWEW_CTWW
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_CTWW_EN__SHIFT                                                   0x0
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_WS_EN__SHIFT                                                     0x1
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_DS_EN__SHIFT                                                     0x2
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_SD_EN__SHIFT                                                     0x3
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_IDWE_HYSTEWESIS__SHIFT                                                 0x4
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_UP_WECOVEW_DEWAY__SHIFT                                          0x8
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_DOWN_ENTEW_DEWAY__SHIFT                                          0xe
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_CTWW_EN__SHIFT                                                       0x10
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_WS_EN__SHIFT                                                         0x11
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_DS_EN__SHIFT                                                         0x12
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_SD_EN__SHIFT                                                         0x13
#define HDP_MEM_POWEW_CTWW__WC_MEM_IDWE_HYSTEWESIS__SHIFT                                                     0x14
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_UP_WECOVEW_DEWAY__SHIFT                                              0x18
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_DOWN_ENTEW_DEWAY__SHIFT                                              0x1e
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_CTWW_EN_MASK                                                     0x00000001W
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_WS_EN_MASK                                                       0x00000002W
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_DS_EN_MASK                                                       0x00000004W
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_SD_EN_MASK                                                       0x00000008W
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_IDWE_HYSTEWESIS_MASK                                                   0x00000070W
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_UP_WECOVEW_DEWAY_MASK                                            0x00003F00W
#define HDP_MEM_POWEW_CTWW__ATOMIC_MEM_POWEW_DOWN_ENTEW_DEWAY_MASK                                            0x0000C000W
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_CTWW_EN_MASK                                                         0x00010000W
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_WS_EN_MASK                                                           0x00020000W
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_DS_EN_MASK                                                           0x00040000W
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_SD_EN_MASK                                                           0x00080000W
#define HDP_MEM_POWEW_CTWW__WC_MEM_IDWE_HYSTEWESIS_MASK                                                       0x00700000W
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_UP_WECOVEW_DEWAY_MASK                                                0x3F000000W
#define HDP_MEM_POWEW_CTWW__WC_MEM_POWEW_DOWN_ENTEW_DEWAY_MASK                                                0xC0000000W
//HDP_MMHUB_CNTW
#define HDP_MMHUB_CNTW__HDP_MMHUB_WO__SHIFT                                                                   0x0
#define HDP_MMHUB_CNTW__HDP_MMHUB_GCC__SHIFT                                                                  0x1
#define HDP_MMHUB_CNTW__HDP_MMHUB_SNOOP__SHIFT                                                                0x2
#define HDP_MMHUB_CNTW__HDP_MMHUB_WO_MASK                                                                     0x00000001W
#define HDP_MMHUB_CNTW__HDP_MMHUB_GCC_MASK                                                                    0x00000002W
#define HDP_MMHUB_CNTW__HDP_MMHUB_SNOOP_MASK                                                                  0x00000004W
//HDP_VEWSION
#define HDP_VEWSION__MINVEW__SHIFT                                                                            0x0
#define HDP_VEWSION__MAJVEW__SHIFT                                                                            0x8
#define HDP_VEWSION__WEV__SHIFT                                                                               0x10
#define HDP_VEWSION__MINVEW_MASK                                                                              0x000000FFW
#define HDP_VEWSION__MAJVEW_MASK                                                                              0x0000FF00W
#define HDP_VEWSION__WEV_MASK                                                                                 0x00FF0000W
//HDP_CWK_CNTW
#define HDP_CWK_CNTW__WEG_CWK_ENABWE_COUNT__SHIFT                                                             0x0
#define HDP_CWK_CNTW__ATOMIC_MEM_CWK_SOFT_OVEWWIDE__SHIFT                                                     0x1a
#define HDP_CWK_CNTW__WC_MEM_CWK_SOFT_OVEWWIDE__SHIFT                                                         0x1b
#define HDP_CWK_CNTW__DBUS_CWK_SOFT_OVEWWIDE__SHIFT                                                           0x1c
#define HDP_CWK_CNTW__DYN_CWK_SOFT_OVEWWIDE__SHIFT                                                            0x1d
#define HDP_CWK_CNTW__XDP_WEG_CWK_SOFT_OVEWWIDE__SHIFT                                                        0x1e
#define HDP_CWK_CNTW__HDP_WEG_CWK_SOFT_OVEWWIDE__SHIFT                                                        0x1f
#define HDP_CWK_CNTW__WEG_CWK_ENABWE_COUNT_MASK                                                               0x0000000FW
#define HDP_CWK_CNTW__ATOMIC_MEM_CWK_SOFT_OVEWWIDE_MASK                                                       0x04000000W
#define HDP_CWK_CNTW__WC_MEM_CWK_SOFT_OVEWWIDE_MASK                                                           0x08000000W
#define HDP_CWK_CNTW__DBUS_CWK_SOFT_OVEWWIDE_MASK                                                             0x10000000W
#define HDP_CWK_CNTW__DYN_CWK_SOFT_OVEWWIDE_MASK                                                              0x20000000W
#define HDP_CWK_CNTW__XDP_WEG_CWK_SOFT_OVEWWIDE_MASK                                                          0x40000000W
#define HDP_CWK_CNTW__HDP_WEG_CWK_SOFT_OVEWWIDE_MASK                                                          0x80000000W
//HDP_MEMIO_CNTW
#define HDP_MEMIO_CNTW__MEMIO_SEND__SHIFT                                                                     0x0
#define HDP_MEMIO_CNTW__MEMIO_OP__SHIFT                                                                       0x1
#define HDP_MEMIO_CNTW__MEMIO_BE__SHIFT                                                                       0x2
#define HDP_MEMIO_CNTW__MEMIO_WW_STWOBE__SHIFT                                                                0x6
#define HDP_MEMIO_CNTW__MEMIO_WD_STWOBE__SHIFT                                                                0x7
#define HDP_MEMIO_CNTW__MEMIO_ADDW_UPPEW__SHIFT                                                               0x8
#define HDP_MEMIO_CNTW__MEMIO_CWW_WW_EWWOW__SHIFT                                                             0xe
#define HDP_MEMIO_CNTW__MEMIO_CWW_WD_EWWOW__SHIFT                                                             0xf
#define HDP_MEMIO_CNTW__MEMIO_VF__SHIFT                                                                       0x10
#define HDP_MEMIO_CNTW__MEMIO_VFID__SHIFT                                                                     0x11
#define HDP_MEMIO_CNTW__MEMIO_SEND_MASK                                                                       0x00000001W
#define HDP_MEMIO_CNTW__MEMIO_OP_MASK                                                                         0x00000002W
#define HDP_MEMIO_CNTW__MEMIO_BE_MASK                                                                         0x0000003CW
#define HDP_MEMIO_CNTW__MEMIO_WW_STWOBE_MASK                                                                  0x00000040W
#define HDP_MEMIO_CNTW__MEMIO_WD_STWOBE_MASK                                                                  0x00000080W
#define HDP_MEMIO_CNTW__MEMIO_ADDW_UPPEW_MASK                                                                 0x00003F00W
#define HDP_MEMIO_CNTW__MEMIO_CWW_WW_EWWOW_MASK                                                               0x00004000W
#define HDP_MEMIO_CNTW__MEMIO_CWW_WD_EWWOW_MASK                                                               0x00008000W
#define HDP_MEMIO_CNTW__MEMIO_VF_MASK                                                                         0x00010000W
#define HDP_MEMIO_CNTW__MEMIO_VFID_MASK                                                                       0x003E0000W
//HDP_MEMIO_ADDW
#define HDP_MEMIO_ADDW__MEMIO_ADDW_WOWEW__SHIFT                                                               0x0
#define HDP_MEMIO_ADDW__MEMIO_ADDW_WOWEW_MASK                                                                 0xFFFFFFFFW
//HDP_MEMIO_STATUS
#define HDP_MEMIO_STATUS__MEMIO_WW_STATUS__SHIFT                                                              0x0
#define HDP_MEMIO_STATUS__MEMIO_WD_STATUS__SHIFT                                                              0x1
#define HDP_MEMIO_STATUS__MEMIO_WW_EWWOW__SHIFT                                                               0x2
#define HDP_MEMIO_STATUS__MEMIO_WD_EWWOW__SHIFT                                                               0x3
#define HDP_MEMIO_STATUS__MEMIO_WW_STATUS_MASK                                                                0x00000001W
#define HDP_MEMIO_STATUS__MEMIO_WD_STATUS_MASK                                                                0x00000002W
#define HDP_MEMIO_STATUS__MEMIO_WW_EWWOW_MASK                                                                 0x00000004W
#define HDP_MEMIO_STATUS__MEMIO_WD_EWWOW_MASK                                                                 0x00000008W
//HDP_MEMIO_WW_DATA
#define HDP_MEMIO_WW_DATA__MEMIO_WW_DATA__SHIFT                                                               0x0
#define HDP_MEMIO_WW_DATA__MEMIO_WW_DATA_MASK                                                                 0xFFFFFFFFW
//HDP_MEMIO_WD_DATA
#define HDP_MEMIO_WD_DATA__MEMIO_WD_DATA__SHIFT                                                               0x0
#define HDP_MEMIO_WD_DATA__MEMIO_WD_DATA_MASK                                                                 0xFFFFFFFFW
//HDP_XDP_DIWECT2HDP_FIWST
#define HDP_XDP_DIWECT2HDP_FIWST__WESEWVED__SHIFT                                                             0x0
#define HDP_XDP_DIWECT2HDP_FIWST__WESEWVED_MASK                                                               0xFFFFFFFFW
//HDP_XDP_D2H_FWUSH
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_FWUSH_NUM__SHIFT                                                         0x0
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_MBX_ENC_DATA__SHIFT                                                      0x4
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_MBX_ADDW_SEW__SHIFT                                                      0x8
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_XPB_CWG__SHIFT                                                           0xb
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_SEND_HOST__SHIFT                                                         0x10
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_AWTEW_FWUSH_NUM__SHIFT                                                   0x12
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_WSVD_0__SHIFT                                                            0x13
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_WSVD_1__SHIFT                                                            0x14
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_FWUSH_NUM_MASK                                                           0x0000000FW
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_MBX_ENC_DATA_MASK                                                        0x000000F0W
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_MBX_ADDW_SEW_MASK                                                        0x00000700W
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_XPB_CWG_MASK                                                             0x0000F800W
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_SEND_HOST_MASK                                                           0x00010000W
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_AWTEW_FWUSH_NUM_MASK                                                     0x00040000W
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_WSVD_0_MASK                                                              0x00080000W
#define HDP_XDP_D2H_FWUSH__D2H_FWUSH_WSVD_1_MASK                                                              0x00100000W
//HDP_XDP_D2H_BAW_UPDATE
#define HDP_XDP_D2H_BAW_UPDATE__D2H_BAW_UPDATE_ADDW__SHIFT                                                    0x0
#define HDP_XDP_D2H_BAW_UPDATE__D2H_BAW_UPDATE_FWUSH_NUM__SHIFT                                               0x10
#define HDP_XDP_D2H_BAW_UPDATE__D2H_BAW_UPDATE_BAW_NUM__SHIFT                                                 0x14
#define HDP_XDP_D2H_BAW_UPDATE__D2H_BAW_UPDATE_ADDW_MASK                                                      0x0000FFFFW
#define HDP_XDP_D2H_BAW_UPDATE__D2H_BAW_UPDATE_FWUSH_NUM_MASK                                                 0x000F0000W
#define HDP_XDP_D2H_BAW_UPDATE__D2H_BAW_UPDATE_BAW_NUM_MASK                                                   0x00700000W
//HDP_XDP_D2H_WSVD_3
#define HDP_XDP_D2H_WSVD_3__WESEWVED__SHIFT                                                                   0x0
#define HDP_XDP_D2H_WSVD_3__WESEWVED_MASK                                                                     0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_4
#define HDP_XDP_D2H_WSVD_4__WESEWVED__SHIFT                                                                   0x0
#define HDP_XDP_D2H_WSVD_4__WESEWVED_MASK                                                                     0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_5
#define HDP_XDP_D2H_WSVD_5__WESEWVED__SHIFT                                                                   0x0
#define HDP_XDP_D2H_WSVD_5__WESEWVED_MASK                                                                     0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_6
#define HDP_XDP_D2H_WSVD_6__WESEWVED__SHIFT                                                                   0x0
#define HDP_XDP_D2H_WSVD_6__WESEWVED_MASK                                                                     0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_7
#define HDP_XDP_D2H_WSVD_7__WESEWVED__SHIFT                                                                   0x0
#define HDP_XDP_D2H_WSVD_7__WESEWVED_MASK                                                                     0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_8
#define HDP_XDP_D2H_WSVD_8__WESEWVED__SHIFT                                                                   0x0
#define HDP_XDP_D2H_WSVD_8__WESEWVED_MASK                                                                     0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_9
#define HDP_XDP_D2H_WSVD_9__WESEWVED__SHIFT                                                                   0x0
#define HDP_XDP_D2H_WSVD_9__WESEWVED_MASK                                                                     0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_10
#define HDP_XDP_D2H_WSVD_10__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_10__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_11
#define HDP_XDP_D2H_WSVD_11__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_11__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_12
#define HDP_XDP_D2H_WSVD_12__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_12__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_13
#define HDP_XDP_D2H_WSVD_13__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_13__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_14
#define HDP_XDP_D2H_WSVD_14__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_14__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_15
#define HDP_XDP_D2H_WSVD_15__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_15__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_16
#define HDP_XDP_D2H_WSVD_16__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_16__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_17
#define HDP_XDP_D2H_WSVD_17__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_17__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_18
#define HDP_XDP_D2H_WSVD_18__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_18__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_19
#define HDP_XDP_D2H_WSVD_19__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_19__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_20
#define HDP_XDP_D2H_WSVD_20__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_20__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_21
#define HDP_XDP_D2H_WSVD_21__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_21__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_22
#define HDP_XDP_D2H_WSVD_22__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_22__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_23
#define HDP_XDP_D2H_WSVD_23__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_23__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_24
#define HDP_XDP_D2H_WSVD_24__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_24__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_25
#define HDP_XDP_D2H_WSVD_25__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_25__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_26
#define HDP_XDP_D2H_WSVD_26__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_26__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_27
#define HDP_XDP_D2H_WSVD_27__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_27__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_28
#define HDP_XDP_D2H_WSVD_28__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_28__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_29
#define HDP_XDP_D2H_WSVD_29__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_29__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_30
#define HDP_XDP_D2H_WSVD_30__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_30__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_31
#define HDP_XDP_D2H_WSVD_31__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_31__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_32
#define HDP_XDP_D2H_WSVD_32__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_32__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_33
#define HDP_XDP_D2H_WSVD_33__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_33__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_D2H_WSVD_34
#define HDP_XDP_D2H_WSVD_34__WESEWVED__SHIFT                                                                  0x0
#define HDP_XDP_D2H_WSVD_34__WESEWVED_MASK                                                                    0xFFFFFFFFW
//HDP_XDP_DIWECT2HDP_WAST
#define HDP_XDP_DIWECT2HDP_WAST__WESEWVED__SHIFT                                                              0x0
#define HDP_XDP_DIWECT2HDP_WAST__WESEWVED_MASK                                                                0xFFFFFFFFW
//HDP_XDP_P2P_BAW_CFG
#define HDP_XDP_P2P_BAW_CFG__P2P_BAW_CFG_ADDW_SIZE__SHIFT                                                     0x0
#define HDP_XDP_P2P_BAW_CFG__P2P_BAW_CFG_BAW_FWOM__SHIFT                                                      0x4
#define HDP_XDP_P2P_BAW_CFG__P2P_BAW_CFG_ADDW_SIZE_MASK                                                       0x0000000FW
#define HDP_XDP_P2P_BAW_CFG__P2P_BAW_CFG_BAW_FWOM_MASK                                                        0x00000030W
//HDP_XDP_P2P_MBX_OFFSET
#define HDP_XDP_P2P_MBX_OFFSET__P2P_MBX_OFFSET__SHIFT                                                         0x0
#define HDP_XDP_P2P_MBX_OFFSET__P2P_MBX_OFFSET_MASK                                                           0x0001FFFFW
//HDP_XDP_P2P_MBX_ADDW0
#define HDP_XDP_P2P_MBX_ADDW0__VAWID__SHIFT                                                                   0x0
#define HDP_XDP_P2P_MBX_ADDW0__ADDW_35_19__SHIFT                                                              0x3
#define HDP_XDP_P2P_MBX_ADDW0__ADDW_39_36__SHIFT                                                              0x14
#define HDP_XDP_P2P_MBX_ADDW0__ADDW_47_40__SHIFT                                                              0x18
#define HDP_XDP_P2P_MBX_ADDW0__VAWID_MASK                                                                     0x00000001W
#define HDP_XDP_P2P_MBX_ADDW0__ADDW_35_19_MASK                                                                0x000FFFF8W
#define HDP_XDP_P2P_MBX_ADDW0__ADDW_39_36_MASK                                                                0x00F00000W
#define HDP_XDP_P2P_MBX_ADDW0__ADDW_47_40_MASK                                                                0xFF000000W
//HDP_XDP_P2P_MBX_ADDW1
#define HDP_XDP_P2P_MBX_ADDW1__VAWID__SHIFT                                                                   0x0
#define HDP_XDP_P2P_MBX_ADDW1__ADDW_35_19__SHIFT                                                              0x3
#define HDP_XDP_P2P_MBX_ADDW1__ADDW_39_36__SHIFT                                                              0x14
#define HDP_XDP_P2P_MBX_ADDW1__ADDW_47_40__SHIFT                                                              0x18
#define HDP_XDP_P2P_MBX_ADDW1__VAWID_MASK                                                                     0x00000001W
#define HDP_XDP_P2P_MBX_ADDW1__ADDW_35_19_MASK                                                                0x000FFFF8W
#define HDP_XDP_P2P_MBX_ADDW1__ADDW_39_36_MASK                                                                0x00F00000W
#define HDP_XDP_P2P_MBX_ADDW1__ADDW_47_40_MASK                                                                0xFF000000W
//HDP_XDP_P2P_MBX_ADDW2
#define HDP_XDP_P2P_MBX_ADDW2__VAWID__SHIFT                                                                   0x0
#define HDP_XDP_P2P_MBX_ADDW2__ADDW_35_19__SHIFT                                                              0x3
#define HDP_XDP_P2P_MBX_ADDW2__ADDW_39_36__SHIFT                                                              0x14
#define HDP_XDP_P2P_MBX_ADDW2__ADDW_47_40__SHIFT                                                              0x18
#define HDP_XDP_P2P_MBX_ADDW2__VAWID_MASK                                                                     0x00000001W
#define HDP_XDP_P2P_MBX_ADDW2__ADDW_35_19_MASK                                                                0x000FFFF8W
#define HDP_XDP_P2P_MBX_ADDW2__ADDW_39_36_MASK                                                                0x00F00000W
#define HDP_XDP_P2P_MBX_ADDW2__ADDW_47_40_MASK                                                                0xFF000000W
//HDP_XDP_P2P_MBX_ADDW3
#define HDP_XDP_P2P_MBX_ADDW3__VAWID__SHIFT                                                                   0x0
#define HDP_XDP_P2P_MBX_ADDW3__ADDW_35_19__SHIFT                                                              0x3
#define HDP_XDP_P2P_MBX_ADDW3__ADDW_39_36__SHIFT                                                              0x14
#define HDP_XDP_P2P_MBX_ADDW3__ADDW_47_40__SHIFT                                                              0x18
#define HDP_XDP_P2P_MBX_ADDW3__VAWID_MASK                                                                     0x00000001W
#define HDP_XDP_P2P_MBX_ADDW3__ADDW_35_19_MASK                                                                0x000FFFF8W
#define HDP_XDP_P2P_MBX_ADDW3__ADDW_39_36_MASK                                                                0x00F00000W
#define HDP_XDP_P2P_MBX_ADDW3__ADDW_47_40_MASK                                                                0xFF000000W
//HDP_XDP_P2P_MBX_ADDW4
#define HDP_XDP_P2P_MBX_ADDW4__VAWID__SHIFT                                                                   0x0
#define HDP_XDP_P2P_MBX_ADDW4__ADDW_35_19__SHIFT                                                              0x3
#define HDP_XDP_P2P_MBX_ADDW4__ADDW_39_36__SHIFT                                                              0x14
#define HDP_XDP_P2P_MBX_ADDW4__ADDW_47_40__SHIFT                                                              0x18
#define HDP_XDP_P2P_MBX_ADDW4__VAWID_MASK                                                                     0x00000001W
#define HDP_XDP_P2P_MBX_ADDW4__ADDW_35_19_MASK                                                                0x000FFFF8W
#define HDP_XDP_P2P_MBX_ADDW4__ADDW_39_36_MASK                                                                0x00F00000W
#define HDP_XDP_P2P_MBX_ADDW4__ADDW_47_40_MASK                                                                0xFF000000W
//HDP_XDP_P2P_MBX_ADDW5
#define HDP_XDP_P2P_MBX_ADDW5__VAWID__SHIFT                                                                   0x0
#define HDP_XDP_P2P_MBX_ADDW5__ADDW_35_19__SHIFT                                                              0x3
#define HDP_XDP_P2P_MBX_ADDW5__ADDW_39_36__SHIFT                                                              0x14
#define HDP_XDP_P2P_MBX_ADDW5__ADDW_47_40__SHIFT                                                              0x18
#define HDP_XDP_P2P_MBX_ADDW5__VAWID_MASK                                                                     0x00000001W
#define HDP_XDP_P2P_MBX_ADDW5__ADDW_35_19_MASK                                                                0x000FFFF8W
#define HDP_XDP_P2P_MBX_ADDW5__ADDW_39_36_MASK                                                                0x00F00000W
#define HDP_XDP_P2P_MBX_ADDW5__ADDW_47_40_MASK                                                                0xFF000000W
//HDP_XDP_P2P_MBX_ADDW6
#define HDP_XDP_P2P_MBX_ADDW6__VAWID__SHIFT                                                                   0x0
#define HDP_XDP_P2P_MBX_ADDW6__ADDW_35_19__SHIFT                                                              0x3
#define HDP_XDP_P2P_MBX_ADDW6__ADDW_39_36__SHIFT                                                              0x14
#define HDP_XDP_P2P_MBX_ADDW6__ADDW_47_40__SHIFT                                                              0x18
#define HDP_XDP_P2P_MBX_ADDW6__VAWID_MASK                                                                     0x00000001W
#define HDP_XDP_P2P_MBX_ADDW6__ADDW_35_19_MASK                                                                0x000FFFF8W
#define HDP_XDP_P2P_MBX_ADDW6__ADDW_39_36_MASK                                                                0x00F00000W
#define HDP_XDP_P2P_MBX_ADDW6__ADDW_47_40_MASK                                                                0xFF000000W
//HDP_XDP_HDP_MBX_MC_CFG
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_QOS__SHIFT                                           0x0
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_SWAP__SHIFT                                          0x4
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_VMID__SHIFT                                          0x8
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_WO__SHIFT                                            0xc
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_GCC__SHIFT                                           0xd
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_SNOOP__SHIFT                                         0xe
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_QOS_MASK                                             0x0000000FW
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_SWAP_MASK                                            0x00000030W
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_VMID_MASK                                            0x00000F00W
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_WO_MASK                                              0x00001000W
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_GCC_MASK                                             0x00002000W
#define HDP_XDP_HDP_MBX_MC_CFG__HDP_MBX_MC_CFG_TAP_WWWEQ_SNOOP_MASK                                           0x00004000W
//HDP_XDP_HDP_MC_CFG
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_HST_TAP_WEQ_SNOOP__SHIFT                                               0x3
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_HST_TAP_WEQ_SWAP__SHIFT                                                0x4
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_HST_TAP_WEQ_VMID__SHIFT                                                0x8
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_HST_TAP_WEQ_WO__SHIFT                                                  0xc
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_HST_TAP_WEQ_GCC__SHIFT                                                 0xd
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_XDP_HIGHEW_PWI_THWESH__SHIFT                                           0xe
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_HST_TAP_WEQ_SNOOP_MASK                                                 0x00000008W
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_HST_TAP_WEQ_SWAP_MASK                                                  0x00000030W
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_HST_TAP_WEQ_VMID_MASK                                                  0x00000F00W
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_HST_TAP_WEQ_WO_MASK                                                    0x00001000W
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_HST_TAP_WEQ_GCC_MASK                                                   0x00002000W
#define HDP_XDP_HDP_MC_CFG__HDP_MC_CFG_XDP_HIGHEW_PWI_THWESH_MASK                                             0x000FC000W
//HDP_XDP_HST_CFG
#define HDP_XDP_HST_CFG__HST_CFG_WW_COMBINE_EN__SHIFT                                                         0x0
#define HDP_XDP_HST_CFG__HST_CFG_WW_COMBINE_TIMEW__SHIFT                                                      0x1
#define HDP_XDP_HST_CFG__HST_CFG_WW_BUWST_EN__SHIFT                                                           0x3
#define HDP_XDP_HST_CFG__HST_CFG_WW_COMBINE_64B_EN__SHIFT                                                     0x4
#define HDP_XDP_HST_CFG__HST_CFG_WW_COMBINE_TIMEW_PWEWOAD_CFG__SHIFT                                          0x5
#define HDP_XDP_HST_CFG__HST_CFG_WW_COMBINE_EN_MASK                                                           0x00000001W
#define HDP_XDP_HST_CFG__HST_CFG_WW_COMBINE_TIMEW_MASK                                                        0x00000006W
#define HDP_XDP_HST_CFG__HST_CFG_WW_BUWST_EN_MASK                                                             0x00000008W
#define HDP_XDP_HST_CFG__HST_CFG_WW_COMBINE_64B_EN_MASK                                                       0x00000010W
#define HDP_XDP_HST_CFG__HST_CFG_WW_COMBINE_TIMEW_PWEWOAD_CFG_MASK                                            0x00000020W
//HDP_XDP_HDP_IPH_CFG
#define HDP_XDP_HDP_IPH_CFG__HDP_IPH_CFG_INVEWSE_PEEW_TAG_MATCHING__SHIFT                                     0xc
#define HDP_XDP_HDP_IPH_CFG__HDP_IPH_CFG_P2P_WD_EN__SHIFT                                                     0xd
#define HDP_XDP_HDP_IPH_CFG__HDP_IPH_CFG_INVEWSE_PEEW_TAG_MATCHING_MASK                                       0x00001000W
#define HDP_XDP_HDP_IPH_CFG__HDP_IPH_CFG_P2P_WD_EN_MASK                                                       0x00002000W
//HDP_XDP_P2P_BAW0
#define HDP_XDP_P2P_BAW0__ADDW__SHIFT                                                                         0x0
#define HDP_XDP_P2P_BAW0__FWUSH__SHIFT                                                                        0x10
#define HDP_XDP_P2P_BAW0__VAWID__SHIFT                                                                        0x14
#define HDP_XDP_P2P_BAW0__ADDW_MASK                                                                           0x0000FFFFW
#define HDP_XDP_P2P_BAW0__FWUSH_MASK                                                                          0x000F0000W
#define HDP_XDP_P2P_BAW0__VAWID_MASK                                                                          0x00100000W
//HDP_XDP_P2P_BAW1
#define HDP_XDP_P2P_BAW1__ADDW__SHIFT                                                                         0x0
#define HDP_XDP_P2P_BAW1__FWUSH__SHIFT                                                                        0x10
#define HDP_XDP_P2P_BAW1__VAWID__SHIFT                                                                        0x14
#define HDP_XDP_P2P_BAW1__ADDW_MASK                                                                           0x0000FFFFW
#define HDP_XDP_P2P_BAW1__FWUSH_MASK                                                                          0x000F0000W
#define HDP_XDP_P2P_BAW1__VAWID_MASK                                                                          0x00100000W
//HDP_XDP_P2P_BAW2
#define HDP_XDP_P2P_BAW2__ADDW__SHIFT                                                                         0x0
#define HDP_XDP_P2P_BAW2__FWUSH__SHIFT                                                                        0x10
#define HDP_XDP_P2P_BAW2__VAWID__SHIFT                                                                        0x14
#define HDP_XDP_P2P_BAW2__ADDW_MASK                                                                           0x0000FFFFW
#define HDP_XDP_P2P_BAW2__FWUSH_MASK                                                                          0x000F0000W
#define HDP_XDP_P2P_BAW2__VAWID_MASK                                                                          0x00100000W
//HDP_XDP_P2P_BAW3
#define HDP_XDP_P2P_BAW3__ADDW__SHIFT                                                                         0x0
#define HDP_XDP_P2P_BAW3__FWUSH__SHIFT                                                                        0x10
#define HDP_XDP_P2P_BAW3__VAWID__SHIFT                                                                        0x14
#define HDP_XDP_P2P_BAW3__ADDW_MASK                                                                           0x0000FFFFW
#define HDP_XDP_P2P_BAW3__FWUSH_MASK                                                                          0x000F0000W
#define HDP_XDP_P2P_BAW3__VAWID_MASK                                                                          0x00100000W
//HDP_XDP_P2P_BAW4
#define HDP_XDP_P2P_BAW4__ADDW__SHIFT                                                                         0x0
#define HDP_XDP_P2P_BAW4__FWUSH__SHIFT                                                                        0x10
#define HDP_XDP_P2P_BAW4__VAWID__SHIFT                                                                        0x14
#define HDP_XDP_P2P_BAW4__ADDW_MASK                                                                           0x0000FFFFW
#define HDP_XDP_P2P_BAW4__FWUSH_MASK                                                                          0x000F0000W
#define HDP_XDP_P2P_BAW4__VAWID_MASK                                                                          0x00100000W
//HDP_XDP_P2P_BAW5
#define HDP_XDP_P2P_BAW5__ADDW__SHIFT                                                                         0x0
#define HDP_XDP_P2P_BAW5__FWUSH__SHIFT                                                                        0x10
#define HDP_XDP_P2P_BAW5__VAWID__SHIFT                                                                        0x14
#define HDP_XDP_P2P_BAW5__ADDW_MASK                                                                           0x0000FFFFW
#define HDP_XDP_P2P_BAW5__FWUSH_MASK                                                                          0x000F0000W
#define HDP_XDP_P2P_BAW5__VAWID_MASK                                                                          0x00100000W
//HDP_XDP_P2P_BAW6
#define HDP_XDP_P2P_BAW6__ADDW__SHIFT                                                                         0x0
#define HDP_XDP_P2P_BAW6__FWUSH__SHIFT                                                                        0x10
#define HDP_XDP_P2P_BAW6__VAWID__SHIFT                                                                        0x14
#define HDP_XDP_P2P_BAW6__ADDW_MASK                                                                           0x0000FFFFW
#define HDP_XDP_P2P_BAW6__FWUSH_MASK                                                                          0x000F0000W
#define HDP_XDP_P2P_BAW6__VAWID_MASK                                                                          0x00100000W
//HDP_XDP_P2P_BAW7
#define HDP_XDP_P2P_BAW7__ADDW__SHIFT                                                                         0x0
#define HDP_XDP_P2P_BAW7__FWUSH__SHIFT                                                                        0x10
#define HDP_XDP_P2P_BAW7__VAWID__SHIFT                                                                        0x14
#define HDP_XDP_P2P_BAW7__ADDW_MASK                                                                           0x0000FFFFW
#define HDP_XDP_P2P_BAW7__FWUSH_MASK                                                                          0x000F0000W
#define HDP_XDP_P2P_BAW7__VAWID_MASK                                                                          0x00100000W
//HDP_XDP_FWUSH_AWMED_STS
#define HDP_XDP_FWUSH_AWMED_STS__FWUSH_AWMED_STS__SHIFT                                                       0x0
#define HDP_XDP_FWUSH_AWMED_STS__FWUSH_AWMED_STS_MASK                                                         0xFFFFFFFFW
//HDP_XDP_FWUSH_CNTW0_STS
#define HDP_XDP_FWUSH_CNTW0_STS__FWUSH_CNTW0_STS__SHIFT                                                       0x0
#define HDP_XDP_FWUSH_CNTW0_STS__FWUSH_CNTW0_STS_MASK                                                         0x03FFFFFFW
//HDP_XDP_BUSY_STS
#define HDP_XDP_BUSY_STS__BUSY_BITS_0__SHIFT                                                                  0x0
#define HDP_XDP_BUSY_STS__BUSY_BITS_1__SHIFT                                                                  0x1
#define HDP_XDP_BUSY_STS__BUSY_BITS_2__SHIFT                                                                  0x2
#define HDP_XDP_BUSY_STS__BUSY_BITS_3__SHIFT                                                                  0x3
#define HDP_XDP_BUSY_STS__BUSY_BITS_4__SHIFT                                                                  0x4
#define HDP_XDP_BUSY_STS__BUSY_BITS_5__SHIFT                                                                  0x5
#define HDP_XDP_BUSY_STS__BUSY_BITS_6__SHIFT                                                                  0x6
#define HDP_XDP_BUSY_STS__BUSY_BITS_7__SHIFT                                                                  0x7
#define HDP_XDP_BUSY_STS__BUSY_BITS_8__SHIFT                                                                  0x8
#define HDP_XDP_BUSY_STS__BUSY_BITS_9__SHIFT                                                                  0x9
#define HDP_XDP_BUSY_STS__BUSY_BITS_10__SHIFT                                                                 0xa
#define HDP_XDP_BUSY_STS__BUSY_BITS_11__SHIFT                                                                 0xb
#define HDP_XDP_BUSY_STS__BUSY_BITS_12__SHIFT                                                                 0xc
#define HDP_XDP_BUSY_STS__BUSY_BITS_13__SHIFT                                                                 0xd
#define HDP_XDP_BUSY_STS__BUSY_BITS_14__SHIFT                                                                 0xe
#define HDP_XDP_BUSY_STS__BUSY_BITS_15__SHIFT                                                                 0xf
#define HDP_XDP_BUSY_STS__BUSY_BITS_16__SHIFT                                                                 0x10
#define HDP_XDP_BUSY_STS__BUSY_BITS_17__SHIFT                                                                 0x11
#define HDP_XDP_BUSY_STS__BUSY_BITS_18__SHIFT                                                                 0x12
#define HDP_XDP_BUSY_STS__BUSY_BITS_19__SHIFT                                                                 0x13
#define HDP_XDP_BUSY_STS__BUSY_BITS_20__SHIFT                                                                 0x14
#define HDP_XDP_BUSY_STS__BUSY_BITS_21__SHIFT                                                                 0x15
#define HDP_XDP_BUSY_STS__BUSY_BITS_22__SHIFT                                                                 0x16
#define HDP_XDP_BUSY_STS__BUSY_BITS_23__SHIFT                                                                 0x17
#define HDP_XDP_BUSY_STS__Z_FENCE_BIT__SHIFT                                                                  0x18
#define HDP_XDP_BUSY_STS__BUSY_BITS_0_MASK                                                                    0x00000001W
#define HDP_XDP_BUSY_STS__BUSY_BITS_1_MASK                                                                    0x00000002W
#define HDP_XDP_BUSY_STS__BUSY_BITS_2_MASK                                                                    0x00000004W
#define HDP_XDP_BUSY_STS__BUSY_BITS_3_MASK                                                                    0x00000008W
#define HDP_XDP_BUSY_STS__BUSY_BITS_4_MASK                                                                    0x00000010W
#define HDP_XDP_BUSY_STS__BUSY_BITS_5_MASK                                                                    0x00000020W
#define HDP_XDP_BUSY_STS__BUSY_BITS_6_MASK                                                                    0x00000040W
#define HDP_XDP_BUSY_STS__BUSY_BITS_7_MASK                                                                    0x00000080W
#define HDP_XDP_BUSY_STS__BUSY_BITS_8_MASK                                                                    0x00000100W
#define HDP_XDP_BUSY_STS__BUSY_BITS_9_MASK                                                                    0x00000200W
#define HDP_XDP_BUSY_STS__BUSY_BITS_10_MASK                                                                   0x00000400W
#define HDP_XDP_BUSY_STS__BUSY_BITS_11_MASK                                                                   0x00000800W
#define HDP_XDP_BUSY_STS__BUSY_BITS_12_MASK                                                                   0x00001000W
#define HDP_XDP_BUSY_STS__BUSY_BITS_13_MASK                                                                   0x00002000W
#define HDP_XDP_BUSY_STS__BUSY_BITS_14_MASK                                                                   0x00004000W
#define HDP_XDP_BUSY_STS__BUSY_BITS_15_MASK                                                                   0x00008000W
#define HDP_XDP_BUSY_STS__BUSY_BITS_16_MASK                                                                   0x00010000W
#define HDP_XDP_BUSY_STS__BUSY_BITS_17_MASK                                                                   0x00020000W
#define HDP_XDP_BUSY_STS__BUSY_BITS_18_MASK                                                                   0x00040000W
#define HDP_XDP_BUSY_STS__BUSY_BITS_19_MASK                                                                   0x00080000W
#define HDP_XDP_BUSY_STS__BUSY_BITS_20_MASK                                                                   0x00100000W
#define HDP_XDP_BUSY_STS__BUSY_BITS_21_MASK                                                                   0x00200000W
#define HDP_XDP_BUSY_STS__BUSY_BITS_22_MASK                                                                   0x00400000W
#define HDP_XDP_BUSY_STS__BUSY_BITS_23_MASK                                                                   0x00800000W
#define HDP_XDP_BUSY_STS__Z_FENCE_BIT_MASK                                                                    0x01000000W
//HDP_XDP_STICKY
#define HDP_XDP_STICKY__STICKY_STS__SHIFT                                                                     0x0
#define HDP_XDP_STICKY__STICKY_W1C__SHIFT                                                                     0x10
#define HDP_XDP_STICKY__STICKY_STS_MASK                                                                       0x0000FFFFW
#define HDP_XDP_STICKY__STICKY_W1C_MASK                                                                       0xFFFF0000W
//HDP_XDP_CHKN
#define HDP_XDP_CHKN__CHKN_0_WSVD__SHIFT                                                                      0x0
#define HDP_XDP_CHKN__CHKN_1_WSVD__SHIFT                                                                      0x8
#define HDP_XDP_CHKN__CHKN_2_WSVD__SHIFT                                                                      0x10
#define HDP_XDP_CHKN__CHKN_3_WSVD__SHIFT                                                                      0x18
#define HDP_XDP_CHKN__CHKN_0_WSVD_MASK                                                                        0x000000FFW
#define HDP_XDP_CHKN__CHKN_1_WSVD_MASK                                                                        0x0000FF00W
#define HDP_XDP_CHKN__CHKN_2_WSVD_MASK                                                                        0x00FF0000W
#define HDP_XDP_CHKN__CHKN_3_WSVD_MASK                                                                        0xFF000000W
//HDP_XDP_BAWS_ADDW_39_36
#define HDP_XDP_BAWS_ADDW_39_36__BAW0_ADDW_39_36__SHIFT                                                       0x0
#define HDP_XDP_BAWS_ADDW_39_36__BAW1_ADDW_39_36__SHIFT                                                       0x4
#define HDP_XDP_BAWS_ADDW_39_36__BAW2_ADDW_39_36__SHIFT                                                       0x8
#define HDP_XDP_BAWS_ADDW_39_36__BAW3_ADDW_39_36__SHIFT                                                       0xc
#define HDP_XDP_BAWS_ADDW_39_36__BAW4_ADDW_39_36__SHIFT                                                       0x10
#define HDP_XDP_BAWS_ADDW_39_36__BAW5_ADDW_39_36__SHIFT                                                       0x14
#define HDP_XDP_BAWS_ADDW_39_36__BAW6_ADDW_39_36__SHIFT                                                       0x18
#define HDP_XDP_BAWS_ADDW_39_36__BAW7_ADDW_39_36__SHIFT                                                       0x1c
#define HDP_XDP_BAWS_ADDW_39_36__BAW0_ADDW_39_36_MASK                                                         0x0000000FW
#define HDP_XDP_BAWS_ADDW_39_36__BAW1_ADDW_39_36_MASK                                                         0x000000F0W
#define HDP_XDP_BAWS_ADDW_39_36__BAW2_ADDW_39_36_MASK                                                         0x00000F00W
#define HDP_XDP_BAWS_ADDW_39_36__BAW3_ADDW_39_36_MASK                                                         0x0000F000W
#define HDP_XDP_BAWS_ADDW_39_36__BAW4_ADDW_39_36_MASK                                                         0x000F0000W
#define HDP_XDP_BAWS_ADDW_39_36__BAW5_ADDW_39_36_MASK                                                         0x00F00000W
#define HDP_XDP_BAWS_ADDW_39_36__BAW6_ADDW_39_36_MASK                                                         0x0F000000W
#define HDP_XDP_BAWS_ADDW_39_36__BAW7_ADDW_39_36_MASK                                                         0xF0000000W
//HDP_XDP_MC_VM_FB_WOCATION_BASE
#define HDP_XDP_MC_VM_FB_WOCATION_BASE__FB_BASE__SHIFT                                                        0x0
#define HDP_XDP_MC_VM_FB_WOCATION_BASE__FB_BASE_MASK                                                          0x03FFFFFFW
//HDP_XDP_GPU_IOV_VIOWATION_WOG
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__VIOWATION_STATUS__SHIFT                                                0x0
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__MUWTIPWE_VIOWATION_STATUS__SHIFT                                       0x1
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__ADDWESS__SHIFT                                                         0x2
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__OPCODE__SHIFT                                                          0x12
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__VF__SHIFT                                                              0x13
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__VFID__SHIFT                                                            0x14
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__VIOWATION_STATUS_MASK                                                  0x00000001W
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__MUWTIPWE_VIOWATION_STATUS_MASK                                         0x00000002W
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__ADDWESS_MASK                                                           0x0003FFFCW
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__OPCODE_MASK                                                            0x00040000W
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__VF_MASK                                                                0x00080000W
#define HDP_XDP_GPU_IOV_VIOWATION_WOG__VFID_MASK                                                              0x00F00000W
//HDP_XDP_GPU_IOV_VIOWATION_WOG2
#define HDP_XDP_GPU_IOV_VIOWATION_WOG2__INITIATOW_ID__SHIFT                                                   0x0
#define HDP_XDP_GPU_IOV_VIOWATION_WOG2__INITIATOW_ID_MASK                                                     0x000003FFW
//HDP_XDP_MMHUB_EWWOW
#define HDP_XDP_MMHUB_EWWOW__HDP_BWESP_01__SHIFT                                                              0x1
#define HDP_XDP_MMHUB_EWWOW__HDP_BWESP_10__SHIFT                                                              0x2
#define HDP_XDP_MMHUB_EWWOW__HDP_BWESP_11__SHIFT                                                              0x3
#define HDP_XDP_MMHUB_EWWOW__HDP_BUSEW_FED__SHIFT                                                             0x4
#define HDP_XDP_MMHUB_EWWOW__HDP_BUSEW_NACK_01__SHIFT                                                         0x5
#define HDP_XDP_MMHUB_EWWOW__HDP_BUSEW_NACK_10__SHIFT                                                         0x6
#define HDP_XDP_MMHUB_EWWOW__HDP_BUSEW_NACK_11__SHIFT                                                         0x7
#define HDP_XDP_MMHUB_EWWOW__HDP_WWESP_01__SHIFT                                                              0x9
#define HDP_XDP_MMHUB_EWWOW__HDP_WWESP_10__SHIFT                                                              0xa
#define HDP_XDP_MMHUB_EWWOW__HDP_WWESP_11__SHIFT                                                              0xb
#define HDP_XDP_MMHUB_EWWOW__HDP_WUSEW_FED__SHIFT                                                             0xc
#define HDP_XDP_MMHUB_EWWOW__HDP_WUSEW_NACK_01__SHIFT                                                         0xd
#define HDP_XDP_MMHUB_EWWOW__HDP_WUSEW_NACK_10__SHIFT                                                         0xe
#define HDP_XDP_MMHUB_EWWOW__HDP_WUSEW_NACK_11__SHIFT                                                         0xf
#define HDP_XDP_MMHUB_EWWOW__XDP_BWESP_01__SHIFT                                                              0x11
#define HDP_XDP_MMHUB_EWWOW__XDP_BWESP_10__SHIFT                                                              0x12
#define HDP_XDP_MMHUB_EWWOW__XDP_BWESP_11__SHIFT                                                              0x13
#define HDP_XDP_MMHUB_EWWOW__XDP_BUSEW_NACK_01__SHIFT                                                         0x15
#define HDP_XDP_MMHUB_EWWOW__XDP_BUSEW_NACK_10__SHIFT                                                         0x16
#define HDP_XDP_MMHUB_EWWOW__XDP_BUSEW_NACK_11__SHIFT                                                         0x17
#define HDP_XDP_MMHUB_EWWOW__HDP_BWESP_01_MASK                                                                0x00000002W
#define HDP_XDP_MMHUB_EWWOW__HDP_BWESP_10_MASK                                                                0x00000004W
#define HDP_XDP_MMHUB_EWWOW__HDP_BWESP_11_MASK                                                                0x00000008W
#define HDP_XDP_MMHUB_EWWOW__HDP_BUSEW_FED_MASK                                                               0x00000010W
#define HDP_XDP_MMHUB_EWWOW__HDP_BUSEW_NACK_01_MASK                                                           0x00000020W
#define HDP_XDP_MMHUB_EWWOW__HDP_BUSEW_NACK_10_MASK                                                           0x00000040W
#define HDP_XDP_MMHUB_EWWOW__HDP_BUSEW_NACK_11_MASK                                                           0x00000080W
#define HDP_XDP_MMHUB_EWWOW__HDP_WWESP_01_MASK                                                                0x00000200W
#define HDP_XDP_MMHUB_EWWOW__HDP_WWESP_10_MASK                                                                0x00000400W
#define HDP_XDP_MMHUB_EWWOW__HDP_WWESP_11_MASK                                                                0x00000800W
#define HDP_XDP_MMHUB_EWWOW__HDP_WUSEW_FED_MASK                                                               0x00001000W
#define HDP_XDP_MMHUB_EWWOW__HDP_WUSEW_NACK_01_MASK                                                           0x00002000W
#define HDP_XDP_MMHUB_EWWOW__HDP_WUSEW_NACK_10_MASK                                                           0x00004000W
#define HDP_XDP_MMHUB_EWWOW__HDP_WUSEW_NACK_11_MASK                                                           0x00008000W
#define HDP_XDP_MMHUB_EWWOW__XDP_BWESP_01_MASK                                                                0x00020000W
#define HDP_XDP_MMHUB_EWWOW__XDP_BWESP_10_MASK                                                                0x00040000W
#define HDP_XDP_MMHUB_EWWOW__XDP_BWESP_11_MASK                                                                0x00080000W
#define HDP_XDP_MMHUB_EWWOW__XDP_BUSEW_NACK_01_MASK                                                           0x00200000W
#define HDP_XDP_MMHUB_EWWOW__XDP_BUSEW_NACK_10_MASK                                                           0x00400000W
#define HDP_XDP_MMHUB_EWWOW__XDP_BUSEW_NACK_11_MASK                                                           0x00800000W

#endif
