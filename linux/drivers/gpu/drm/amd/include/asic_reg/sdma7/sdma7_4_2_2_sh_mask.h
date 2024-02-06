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
#ifndef _sdma7_4_2_2_SH_MASK_HEADEW
#define _sdma7_4_2_2_SH_MASK_HEADEW


// addwessBwock: sdma7_sdma7dec
//SDMA7_UCODE_ADDW
#define SDMA7_UCODE_ADDW__VAWUE__SHIFT                                                                        0x0
#define SDMA7_UCODE_ADDW__VAWUE_MASK                                                                          0x00001FFFW
//SDMA7_UCODE_DATA
#define SDMA7_UCODE_DATA__VAWUE__SHIFT                                                                        0x0
#define SDMA7_UCODE_DATA__VAWUE_MASK                                                                          0xFFFFFFFFW
//SDMA7_VM_CNTW
#define SDMA7_VM_CNTW__CMD__SHIFT                                                                             0x0
#define SDMA7_VM_CNTW__CMD_MASK                                                                               0x0000000FW
//SDMA7_VM_CTX_WO
#define SDMA7_VM_CTX_WO__ADDW__SHIFT                                                                          0x2
#define SDMA7_VM_CTX_WO__ADDW_MASK                                                                            0xFFFFFFFCW
//SDMA7_VM_CTX_HI
#define SDMA7_VM_CTX_HI__ADDW__SHIFT                                                                          0x0
#define SDMA7_VM_CTX_HI__ADDW_MASK                                                                            0xFFFFFFFFW
//SDMA7_ACTIVE_FCN_ID
#define SDMA7_ACTIVE_FCN_ID__VFID__SHIFT                                                                      0x0
#define SDMA7_ACTIVE_FCN_ID__WESEWVED__SHIFT                                                                  0x4
#define SDMA7_ACTIVE_FCN_ID__VF__SHIFT                                                                        0x1f
#define SDMA7_ACTIVE_FCN_ID__VFID_MASK                                                                        0x0000000FW
#define SDMA7_ACTIVE_FCN_ID__WESEWVED_MASK                                                                    0x7FFFFFF0W
#define SDMA7_ACTIVE_FCN_ID__VF_MASK                                                                          0x80000000W
//SDMA7_VM_CTX_CNTW
#define SDMA7_VM_CTX_CNTW__PWIV__SHIFT                                                                        0x0
#define SDMA7_VM_CTX_CNTW__VMID__SHIFT                                                                        0x4
#define SDMA7_VM_CTX_CNTW__PWIV_MASK                                                                          0x00000001W
#define SDMA7_VM_CTX_CNTW__VMID_MASK                                                                          0x000000F0W
//SDMA7_VIWT_WESET_WEQ
#define SDMA7_VIWT_WESET_WEQ__VF__SHIFT                                                                       0x0
#define SDMA7_VIWT_WESET_WEQ__PF__SHIFT                                                                       0x1f
#define SDMA7_VIWT_WESET_WEQ__VF_MASK                                                                         0x0000FFFFW
#define SDMA7_VIWT_WESET_WEQ__PF_MASK                                                                         0x80000000W
//SDMA7_VF_ENABWE
#define SDMA7_VF_ENABWE__VF_ENABWE__SHIFT                                                                     0x0
#define SDMA7_VF_ENABWE__VF_ENABWE_MASK                                                                       0x00000001W
//SDMA7_CONTEXT_WEG_TYPE0
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_CNTW__SHIFT                                                     0x0
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_BASE__SHIFT                                                     0x1
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_BASE_HI__SHIFT                                                  0x2
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW__SHIFT                                                     0x3
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_HI__SHIFT                                                  0x4
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW__SHIFT                                                     0x5
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_HI__SHIFT                                                  0x6
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_POWW_CNTW__SHIFT                                           0x7
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_ADDW_HI__SHIFT                                             0x8
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_ADDW_WO__SHIFT                                             0x9
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_CNTW__SHIFT                                                     0xa
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_WPTW__SHIFT                                                     0xb
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_OFFSET__SHIFT                                                   0xc
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_BASE_WO__SHIFT                                                  0xd
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_BASE_HI__SHIFT                                                  0xe
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_SIZE__SHIFT                                                     0xf
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_SKIP_CNTW__SHIFT                                                   0x10
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_CONTEXT_STATUS__SHIFT                                              0x11
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_DOOWBEWW__SHIFT                                                    0x12
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_CONTEXT_CNTW__SHIFT                                                0x13
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_CNTW_MASK                                                       0x00000001W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_BASE_MASK                                                       0x00000002W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_BASE_HI_MASK                                                    0x00000004W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_MASK                                                       0x00000008W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_HI_MASK                                                    0x00000010W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_MASK                                                       0x00000020W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_HI_MASK                                                    0x00000040W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_POWW_CNTW_MASK                                             0x00000080W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_ADDW_HI_MASK                                               0x00000100W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_WB_WPTW_ADDW_WO_MASK                                               0x00000200W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_CNTW_MASK                                                       0x00000400W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_WPTW_MASK                                                       0x00000800W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_OFFSET_MASK                                                     0x00001000W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_BASE_WO_MASK                                                    0x00002000W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_BASE_HI_MASK                                                    0x00004000W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_IB_SIZE_MASK                                                       0x00008000W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_SKIP_CNTW_MASK                                                     0x00010000W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_CONTEXT_STATUS_MASK                                                0x00020000W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_DOOWBEWW_MASK                                                      0x00040000W
#define SDMA7_CONTEXT_WEG_TYPE0__SDMA7_GFX_CONTEXT_CNTW_MASK                                                  0x00080000W
//SDMA7_CONTEXT_WEG_TYPE1
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_STATUS__SHIFT                                                      0x8
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_DOOWBEWW_WOG__SHIFT                                                0x9
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_WATEWMAWK__SHIFT                                                   0xa
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_DOOWBEWW_OFFSET__SHIFT                                             0xb
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_CSA_ADDW_WO__SHIFT                                                 0xc
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_CSA_ADDW_HI__SHIFT                                                 0xd
#define SDMA7_CONTEXT_WEG_TYPE1__VOID_WEG2__SHIFT                                                             0xe
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_IB_SUB_WEMAIN__SHIFT                                               0xf
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_PWEEMPT__SHIFT                                                     0x10
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_DUMMY_WEG__SHIFT                                                   0x11
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_WB_WPTW_POWW_ADDW_HI__SHIFT                                        0x12
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_WB_WPTW_POWW_ADDW_WO__SHIFT                                        0x13
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_WB_AQW_CNTW__SHIFT                                                 0x14
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_MINOW_PTW_UPDATE__SHIFT                                            0x15
#define SDMA7_CONTEXT_WEG_TYPE1__WESEWVED__SHIFT                                                              0x16
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_STATUS_MASK                                                        0x00000100W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_DOOWBEWW_WOG_MASK                                                  0x00000200W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_WATEWMAWK_MASK                                                     0x00000400W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_DOOWBEWW_OFFSET_MASK                                               0x00000800W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_CSA_ADDW_WO_MASK                                                   0x00001000W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_CSA_ADDW_HI_MASK                                                   0x00002000W
#define SDMA7_CONTEXT_WEG_TYPE1__VOID_WEG2_MASK                                                               0x00004000W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_IB_SUB_WEMAIN_MASK                                                 0x00008000W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_PWEEMPT_MASK                                                       0x00010000W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_DUMMY_WEG_MASK                                                     0x00020000W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_WB_WPTW_POWW_ADDW_HI_MASK                                          0x00040000W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_WB_WPTW_POWW_ADDW_WO_MASK                                          0x00080000W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_WB_AQW_CNTW_MASK                                                   0x00100000W
#define SDMA7_CONTEXT_WEG_TYPE1__SDMA7_GFX_MINOW_PTW_UPDATE_MASK                                              0x00200000W
#define SDMA7_CONTEXT_WEG_TYPE1__WESEWVED_MASK                                                                0xFFC00000W
//SDMA7_CONTEXT_WEG_TYPE2
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA0__SHIFT                                                0x0
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA1__SHIFT                                                0x1
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA2__SHIFT                                                0x2
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA3__SHIFT                                                0x3
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA4__SHIFT                                                0x4
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA5__SHIFT                                                0x5
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA6__SHIFT                                                0x6
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA7__SHIFT                                                0x7
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA8__SHIFT                                                0x8
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_CNTW__SHIFT                                                 0x9
#define SDMA7_CONTEXT_WEG_TYPE2__WESEWVED__SHIFT                                                              0xa
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA0_MASK                                                  0x00000001W
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA1_MASK                                                  0x00000002W
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA2_MASK                                                  0x00000004W
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA3_MASK                                                  0x00000008W
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA4_MASK                                                  0x00000010W
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA5_MASK                                                  0x00000020W
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA6_MASK                                                  0x00000040W
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA7_MASK                                                  0x00000080W
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_DATA8_MASK                                                  0x00000100W
#define SDMA7_CONTEXT_WEG_TYPE2__SDMA7_GFX_MIDCMD_CNTW_MASK                                                   0x00000200W
#define SDMA7_CONTEXT_WEG_TYPE2__WESEWVED_MASK                                                                0xFFFFFC00W
//SDMA7_CONTEXT_WEG_TYPE3
#define SDMA7_CONTEXT_WEG_TYPE3__WESEWVED__SHIFT                                                              0x0
#define SDMA7_CONTEXT_WEG_TYPE3__WESEWVED_MASK                                                                0xFFFFFFFFW
//SDMA7_PUB_WEG_TYPE0
#define SDMA7_PUB_WEG_TYPE0__SDMA7_UCODE_ADDW__SHIFT                                                          0x0
#define SDMA7_PUB_WEG_TYPE0__SDMA7_UCODE_DATA__SHIFT                                                          0x1
#define SDMA7_PUB_WEG_TYPE0__WESEWVED3__SHIFT                                                                 0x3
#define SDMA7_PUB_WEG_TYPE0__SDMA7_VM_CNTW__SHIFT                                                             0x4
#define SDMA7_PUB_WEG_TYPE0__SDMA7_VM_CTX_WO__SHIFT                                                           0x5
#define SDMA7_PUB_WEG_TYPE0__SDMA7_VM_CTX_HI__SHIFT                                                           0x6
#define SDMA7_PUB_WEG_TYPE0__SDMA7_ACTIVE_FCN_ID__SHIFT                                                       0x7
#define SDMA7_PUB_WEG_TYPE0__SDMA7_VM_CTX_CNTW__SHIFT                                                         0x8
#define SDMA7_PUB_WEG_TYPE0__SDMA7_VIWT_WESET_WEQ__SHIFT                                                      0x9
#define SDMA7_PUB_WEG_TYPE0__WESEWVED10__SHIFT                                                                0xa
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CONTEXT_WEG_TYPE0__SHIFT                                                   0xb
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CONTEXT_WEG_TYPE1__SHIFT                                                   0xc
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CONTEXT_WEG_TYPE2__SHIFT                                                   0xd
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CONTEXT_WEG_TYPE3__SHIFT                                                   0xe
#define SDMA7_PUB_WEG_TYPE0__SDMA7_PUB_WEG_TYPE0__SHIFT                                                       0xf
#define SDMA7_PUB_WEG_TYPE0__SDMA7_PUB_WEG_TYPE1__SHIFT                                                       0x10
#define SDMA7_PUB_WEG_TYPE0__SDMA7_PUB_WEG_TYPE2__SHIFT                                                       0x11
#define SDMA7_PUB_WEG_TYPE0__SDMA7_PUB_WEG_TYPE3__SHIFT                                                       0x12
#define SDMA7_PUB_WEG_TYPE0__SDMA7_MMHUB_CNTW__SHIFT                                                          0x13
#define SDMA7_PUB_WEG_TYPE0__WESEWVED_FOW_PSPSMU_ACCESS_ONWY__SHIFT                                           0x15
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CONTEXT_GWOUP_BOUNDAWY__SHIFT                                              0x19
#define SDMA7_PUB_WEG_TYPE0__SDMA7_POWEW_CNTW__SHIFT                                                          0x1a
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CWK_CTWW__SHIFT                                                            0x1b
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CNTW__SHIFT                                                                0x1c
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CHICKEN_BITS__SHIFT                                                        0x1d
#define SDMA7_PUB_WEG_TYPE0__SDMA7_GB_ADDW_CONFIG__SHIFT                                                      0x1e
#define SDMA7_PUB_WEG_TYPE0__SDMA7_GB_ADDW_CONFIG_WEAD__SHIFT                                                 0x1f
#define SDMA7_PUB_WEG_TYPE0__SDMA7_UCODE_ADDW_MASK                                                            0x00000001W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_UCODE_DATA_MASK                                                            0x00000002W
#define SDMA7_PUB_WEG_TYPE0__WESEWVED3_MASK                                                                   0x00000008W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_VM_CNTW_MASK                                                               0x00000010W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_VM_CTX_WO_MASK                                                             0x00000020W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_VM_CTX_HI_MASK                                                             0x00000040W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_ACTIVE_FCN_ID_MASK                                                         0x00000080W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_VM_CTX_CNTW_MASK                                                           0x00000100W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_VIWT_WESET_WEQ_MASK                                                        0x00000200W
#define SDMA7_PUB_WEG_TYPE0__WESEWVED10_MASK                                                                  0x00000400W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CONTEXT_WEG_TYPE0_MASK                                                     0x00000800W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CONTEXT_WEG_TYPE1_MASK                                                     0x00001000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CONTEXT_WEG_TYPE2_MASK                                                     0x00002000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CONTEXT_WEG_TYPE3_MASK                                                     0x00004000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_PUB_WEG_TYPE0_MASK                                                         0x00008000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_PUB_WEG_TYPE1_MASK                                                         0x00010000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_PUB_WEG_TYPE2_MASK                                                         0x00020000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_PUB_WEG_TYPE3_MASK                                                         0x00040000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_MMHUB_CNTW_MASK                                                            0x00080000W
#define SDMA7_PUB_WEG_TYPE0__WESEWVED_FOW_PSPSMU_ACCESS_ONWY_MASK                                             0x01E00000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CONTEXT_GWOUP_BOUNDAWY_MASK                                                0x02000000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_POWEW_CNTW_MASK                                                            0x04000000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CWK_CTWW_MASK                                                              0x08000000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CNTW_MASK                                                                  0x10000000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_CHICKEN_BITS_MASK                                                          0x20000000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_GB_ADDW_CONFIG_MASK                                                        0x40000000W
#define SDMA7_PUB_WEG_TYPE0__SDMA7_GB_ADDW_CONFIG_WEAD_MASK                                                   0x80000000W
//SDMA7_PUB_WEG_TYPE1
#define SDMA7_PUB_WEG_TYPE1__SDMA7_WB_WPTW_FETCH_HI__SHIFT                                                    0x0
#define SDMA7_PUB_WEG_TYPE1__SDMA7_SEM_WAIT_FAIW_TIMEW_CNTW__SHIFT                                            0x1
#define SDMA7_PUB_WEG_TYPE1__SDMA7_WB_WPTW_FETCH__SHIFT                                                       0x2
#define SDMA7_PUB_WEG_TYPE1__SDMA7_IB_OFFSET_FETCH__SHIFT                                                     0x3
#define SDMA7_PUB_WEG_TYPE1__SDMA7_PWOGWAM__SHIFT                                                             0x4
#define SDMA7_PUB_WEG_TYPE1__SDMA7_STATUS_WEG__SHIFT                                                          0x5
#define SDMA7_PUB_WEG_TYPE1__SDMA7_STATUS1_WEG__SHIFT                                                         0x6
#define SDMA7_PUB_WEG_TYPE1__SDMA7_WD_BUWST_CNTW__SHIFT                                                       0x7
#define SDMA7_PUB_WEG_TYPE1__SDMA7_HBM_PAGE_CONFIG__SHIFT                                                     0x8
#define SDMA7_PUB_WEG_TYPE1__SDMA7_UCODE_CHECKSUM__SHIFT                                                      0x9
#define SDMA7_PUB_WEG_TYPE1__SDMA7_F32_CNTW__SHIFT                                                            0xa
#define SDMA7_PUB_WEG_TYPE1__SDMA7_FWEEZE__SHIFT                                                              0xb
#define SDMA7_PUB_WEG_TYPE1__SDMA7_PHASE0_QUANTUM__SHIFT                                                      0xc
#define SDMA7_PUB_WEG_TYPE1__SDMA7_PHASE1_QUANTUM__SHIFT                                                      0xd
#define SDMA7_PUB_WEG_TYPE1__SDMA_POWEW_GATING__SHIFT                                                         0xe
#define SDMA7_PUB_WEG_TYPE1__SDMA_PGFSM_CONFIG__SHIFT                                                         0xf
#define SDMA7_PUB_WEG_TYPE1__SDMA_PGFSM_WWITE__SHIFT                                                          0x10
#define SDMA7_PUB_WEG_TYPE1__SDMA_PGFSM_WEAD__SHIFT                                                           0x11
#define SDMA7_PUB_WEG_TYPE1__SDMA7_EDC_CONFIG__SHIFT                                                          0x12
#define SDMA7_PUB_WEG_TYPE1__SDMA7_BA_THWESHOWD__SHIFT                                                        0x13
#define SDMA7_PUB_WEG_TYPE1__SDMA7_ID__SHIFT                                                                  0x14
#define SDMA7_PUB_WEG_TYPE1__SDMA7_VEWSION__SHIFT                                                             0x15
#define SDMA7_PUB_WEG_TYPE1__SDMA7_EDC_COUNTEW__SHIFT                                                         0x16
#define SDMA7_PUB_WEG_TYPE1__SDMA7_EDC_COUNTEW_CWEAW__SHIFT                                                   0x17
#define SDMA7_PUB_WEG_TYPE1__SDMA7_STATUS2_WEG__SHIFT                                                         0x18
#define SDMA7_PUB_WEG_TYPE1__SDMA7_ATOMIC_CNTW__SHIFT                                                         0x19
#define SDMA7_PUB_WEG_TYPE1__SDMA7_ATOMIC_PWEOP_WO__SHIFT                                                     0x1a
#define SDMA7_PUB_WEG_TYPE1__SDMA7_ATOMIC_PWEOP_HI__SHIFT                                                     0x1b
#define SDMA7_PUB_WEG_TYPE1__SDMA7_UTCW1_CNTW__SHIFT                                                          0x1c
#define SDMA7_PUB_WEG_TYPE1__SDMA7_UTCW1_WATEWMK__SHIFT                                                       0x1d
#define SDMA7_PUB_WEG_TYPE1__SDMA7_UTCW1_WD_STATUS__SHIFT                                                     0x1e
#define SDMA7_PUB_WEG_TYPE1__SDMA7_UTCW1_WW_STATUS__SHIFT                                                     0x1f
#define SDMA7_PUB_WEG_TYPE1__SDMA7_WB_WPTW_FETCH_HI_MASK                                                      0x00000001W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_SEM_WAIT_FAIW_TIMEW_CNTW_MASK                                              0x00000002W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_WB_WPTW_FETCH_MASK                                                         0x00000004W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_IB_OFFSET_FETCH_MASK                                                       0x00000008W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_PWOGWAM_MASK                                                               0x00000010W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_STATUS_WEG_MASK                                                            0x00000020W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_STATUS1_WEG_MASK                                                           0x00000040W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_WD_BUWST_CNTW_MASK                                                         0x00000080W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_HBM_PAGE_CONFIG_MASK                                                       0x00000100W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_UCODE_CHECKSUM_MASK                                                        0x00000200W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_F32_CNTW_MASK                                                              0x00000400W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_FWEEZE_MASK                                                                0x00000800W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_PHASE0_QUANTUM_MASK                                                        0x00001000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_PHASE1_QUANTUM_MASK                                                        0x00002000W
#define SDMA7_PUB_WEG_TYPE1__SDMA_POWEW_GATING_MASK                                                           0x00004000W
#define SDMA7_PUB_WEG_TYPE1__SDMA_PGFSM_CONFIG_MASK                                                           0x00008000W
#define SDMA7_PUB_WEG_TYPE1__SDMA_PGFSM_WWITE_MASK                                                            0x00010000W
#define SDMA7_PUB_WEG_TYPE1__SDMA_PGFSM_WEAD_MASK                                                             0x00020000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_EDC_CONFIG_MASK                                                            0x00040000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_BA_THWESHOWD_MASK                                                          0x00080000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_ID_MASK                                                                    0x00100000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_VEWSION_MASK                                                               0x00200000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_EDC_COUNTEW_MASK                                                           0x00400000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_EDC_COUNTEW_CWEAW_MASK                                                     0x00800000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_STATUS2_WEG_MASK                                                           0x01000000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_ATOMIC_CNTW_MASK                                                           0x02000000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_ATOMIC_PWEOP_WO_MASK                                                       0x04000000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_ATOMIC_PWEOP_HI_MASK                                                       0x08000000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_UTCW1_CNTW_MASK                                                            0x10000000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_UTCW1_WATEWMK_MASK                                                         0x20000000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_UTCW1_WD_STATUS_MASK                                                       0x40000000W
#define SDMA7_PUB_WEG_TYPE1__SDMA7_UTCW1_WW_STATUS_MASK                                                       0x80000000W
//SDMA7_PUB_WEG_TYPE2
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_INV0__SHIFT                                                          0x0
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_INV1__SHIFT                                                          0x1
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_INV2__SHIFT                                                          0x2
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_WD_XNACK0__SHIFT                                                     0x3
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_WD_XNACK1__SHIFT                                                     0x4
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_WW_XNACK0__SHIFT                                                     0x5
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_WW_XNACK1__SHIFT                                                     0x6
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_TIMEOUT__SHIFT                                                       0x7
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_PAGE__SHIFT                                                          0x8
#define SDMA7_PUB_WEG_TYPE2__SDMA7_POWEW_CNTW_IDWE__SHIFT                                                     0x9
#define SDMA7_PUB_WEG_TYPE2__SDMA7_WEWAX_OWDEWING_WUT__SHIFT                                                  0xa
#define SDMA7_PUB_WEG_TYPE2__SDMA7_CHICKEN_BITS_2__SHIFT                                                      0xb
#define SDMA7_PUB_WEG_TYPE2__SDMA7_STATUS3_WEG__SHIFT                                                         0xc
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PHYSICAW_ADDW_WO__SHIFT                                                    0xd
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PHYSICAW_ADDW_HI__SHIFT                                                    0xe
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PHASE2_QUANTUM__SHIFT                                                      0xf
#define SDMA7_PUB_WEG_TYPE2__SDMA7_EWWOW_WOG__SHIFT                                                           0x10
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PUB_DUMMY_WEG0__SHIFT                                                      0x11
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PUB_DUMMY_WEG1__SHIFT                                                      0x12
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PUB_DUMMY_WEG2__SHIFT                                                      0x13
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PUB_DUMMY_WEG3__SHIFT                                                      0x14
#define SDMA7_PUB_WEG_TYPE2__SDMA7_F32_COUNTEW__SHIFT                                                         0x15
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UNBWEAKABWE__SHIFT                                                         0x16
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PEWFMON_CNTW__SHIFT                                                        0x17
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PEWFCOUNTEW0_WESUWT__SHIFT                                                 0x18
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PEWFCOUNTEW1_WESUWT__SHIFT                                                 0x19
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PEWFCOUNTEW_TAG_DEWAY_WANGE__SHIFT                                         0x1a
#define SDMA7_PUB_WEG_TYPE2__SDMA7_CWD_CNTW__SHIFT                                                            0x1b
#define SDMA7_PUB_WEG_TYPE2__WESEWVED28__SHIFT                                                                0x1c
#define SDMA7_PUB_WEG_TYPE2__SDMA7_GPU_IOV_VIOWATION_WOG__SHIFT                                               0x1d
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UWV_CNTW__SHIFT                                                            0x1e
#define SDMA7_PUB_WEG_TYPE2__WESEWVED__SHIFT                                                                  0x1f
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_INV0_MASK                                                            0x00000001W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_INV1_MASK                                                            0x00000002W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_INV2_MASK                                                            0x00000004W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_WD_XNACK0_MASK                                                       0x00000008W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_WD_XNACK1_MASK                                                       0x00000010W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_WW_XNACK0_MASK                                                       0x00000020W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_WW_XNACK1_MASK                                                       0x00000040W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_TIMEOUT_MASK                                                         0x00000080W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UTCW1_PAGE_MASK                                                            0x00000100W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_POWEW_CNTW_IDWE_MASK                                                       0x00000200W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_WEWAX_OWDEWING_WUT_MASK                                                    0x00000400W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_CHICKEN_BITS_2_MASK                                                        0x00000800W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_STATUS3_WEG_MASK                                                           0x00001000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PHYSICAW_ADDW_WO_MASK                                                      0x00002000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PHYSICAW_ADDW_HI_MASK                                                      0x00004000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PHASE2_QUANTUM_MASK                                                        0x00008000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_EWWOW_WOG_MASK                                                             0x00010000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PUB_DUMMY_WEG0_MASK                                                        0x00020000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PUB_DUMMY_WEG1_MASK                                                        0x00040000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PUB_DUMMY_WEG2_MASK                                                        0x00080000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PUB_DUMMY_WEG3_MASK                                                        0x00100000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_F32_COUNTEW_MASK                                                           0x00200000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UNBWEAKABWE_MASK                                                           0x00400000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PEWFMON_CNTW_MASK                                                          0x00800000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PEWFCOUNTEW0_WESUWT_MASK                                                   0x01000000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PEWFCOUNTEW1_WESUWT_MASK                                                   0x02000000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_PEWFCOUNTEW_TAG_DEWAY_WANGE_MASK                                           0x04000000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_CWD_CNTW_MASK                                                              0x08000000W
#define SDMA7_PUB_WEG_TYPE2__WESEWVED28_MASK                                                                  0x10000000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_GPU_IOV_VIOWATION_WOG_MASK                                                 0x20000000W
#define SDMA7_PUB_WEG_TYPE2__SDMA7_UWV_CNTW_MASK                                                              0x40000000W
#define SDMA7_PUB_WEG_TYPE2__WESEWVED_MASK                                                                    0x80000000W
//SDMA7_PUB_WEG_TYPE3
#define SDMA7_PUB_WEG_TYPE3__SDMA7_EA_DBIT_ADDW_DATA__SHIFT                                                   0x0
#define SDMA7_PUB_WEG_TYPE3__SDMA7_EA_DBIT_ADDW_INDEX__SHIFT                                                  0x1
#define SDMA7_PUB_WEG_TYPE3__SDMA7_GPU_IOV_VIOWATION_WOG2__SHIFT                                              0x2
#define SDMA7_PUB_WEG_TYPE3__WESEWVED__SHIFT                                                                  0x3
#define SDMA7_PUB_WEG_TYPE3__SDMA7_EA_DBIT_ADDW_DATA_MASK                                                     0x00000001W
#define SDMA7_PUB_WEG_TYPE3__SDMA7_EA_DBIT_ADDW_INDEX_MASK                                                    0x00000002W
#define SDMA7_PUB_WEG_TYPE3__SDMA7_GPU_IOV_VIOWATION_WOG2_MASK                                                0x00000004W
#define SDMA7_PUB_WEG_TYPE3__WESEWVED_MASK                                                                    0xFFFFFFF8W
//SDMA7_MMHUB_CNTW
#define SDMA7_MMHUB_CNTW__UNIT_ID__SHIFT                                                                      0x0
#define SDMA7_MMHUB_CNTW__UNIT_ID_MASK                                                                        0x0000003FW
//SDMA7_CONTEXT_GWOUP_BOUNDAWY
#define SDMA7_CONTEXT_GWOUP_BOUNDAWY__WESEWVED__SHIFT                                                         0x0
#define SDMA7_CONTEXT_GWOUP_BOUNDAWY__WESEWVED_MASK                                                           0xFFFFFFFFW
//SDMA7_POWEW_CNTW
#define SDMA7_POWEW_CNTW__MEM_POWEW_OVEWWIDE__SHIFT                                                           0x8
#define SDMA7_POWEW_CNTW__MEM_POWEW_WS_EN__SHIFT                                                              0x9
#define SDMA7_POWEW_CNTW__MEM_POWEW_DS_EN__SHIFT                                                              0xa
#define SDMA7_POWEW_CNTW__MEM_POWEW_SD_EN__SHIFT                                                              0xb
#define SDMA7_POWEW_CNTW__MEM_POWEW_DEWAY__SHIFT                                                              0xc
#define SDMA7_POWEW_CNTW__MEM_POWEW_OVEWWIDE_MASK                                                             0x00000100W
#define SDMA7_POWEW_CNTW__MEM_POWEW_WS_EN_MASK                                                                0x00000200W
#define SDMA7_POWEW_CNTW__MEM_POWEW_DS_EN_MASK                                                                0x00000400W
#define SDMA7_POWEW_CNTW__MEM_POWEW_SD_EN_MASK                                                                0x00000800W
#define SDMA7_POWEW_CNTW__MEM_POWEW_DEWAY_MASK                                                                0x003FF000W
//SDMA7_CWK_CTWW
#define SDMA7_CWK_CTWW__ON_DEWAY__SHIFT                                                                       0x0
#define SDMA7_CWK_CTWW__OFF_HYSTEWESIS__SHIFT                                                                 0x4
#define SDMA7_CWK_CTWW__WESEWVED__SHIFT                                                                       0xc
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE7__SHIFT                                                                 0x18
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE6__SHIFT                                                                 0x19
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE5__SHIFT                                                                 0x1a
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE4__SHIFT                                                                 0x1b
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE3__SHIFT                                                                 0x1c
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE2__SHIFT                                                                 0x1d
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE1__SHIFT                                                                 0x1e
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE0__SHIFT                                                                 0x1f
#define SDMA7_CWK_CTWW__ON_DEWAY_MASK                                                                         0x0000000FW
#define SDMA7_CWK_CTWW__OFF_HYSTEWESIS_MASK                                                                   0x00000FF0W
#define SDMA7_CWK_CTWW__WESEWVED_MASK                                                                         0x00FFF000W
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE7_MASK                                                                   0x01000000W
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE6_MASK                                                                   0x02000000W
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE5_MASK                                                                   0x04000000W
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE4_MASK                                                                   0x08000000W
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE3_MASK                                                                   0x10000000W
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE2_MASK                                                                   0x20000000W
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE1_MASK                                                                   0x40000000W
#define SDMA7_CWK_CTWW__SOFT_OVEWWIDE0_MASK                                                                   0x80000000W
//SDMA7_CNTW
#define SDMA7_CNTW__TWAP_ENABWE__SHIFT                                                                        0x0
#define SDMA7_CNTW__UTC_W1_ENABWE__SHIFT                                                                      0x1
#define SDMA7_CNTW__SEM_WAIT_INT_ENABWE__SHIFT                                                                0x2
#define SDMA7_CNTW__DATA_SWAP_ENABWE__SHIFT                                                                   0x3
#define SDMA7_CNTW__FENCE_SWAP_ENABWE__SHIFT                                                                  0x4
#define SDMA7_CNTW__MIDCMD_PWEEMPT_ENABWE__SHIFT                                                              0x5
#define SDMA7_CNTW__MIDCMD_WOWWDSWITCH_ENABWE__SHIFT                                                          0x11
#define SDMA7_CNTW__AUTO_CTXSW_ENABWE__SHIFT                                                                  0x12
#define SDMA7_CNTW__CTXEMPTY_INT_ENABWE__SHIFT                                                                0x1c
#define SDMA7_CNTW__FWOZEN_INT_ENABWE__SHIFT                                                                  0x1d
#define SDMA7_CNTW__IB_PWEEMPT_INT_ENABWE__SHIFT                                                              0x1e
#define SDMA7_CNTW__TWAP_ENABWE_MASK                                                                          0x00000001W
#define SDMA7_CNTW__UTC_W1_ENABWE_MASK                                                                        0x00000002W
#define SDMA7_CNTW__SEM_WAIT_INT_ENABWE_MASK                                                                  0x00000004W
#define SDMA7_CNTW__DATA_SWAP_ENABWE_MASK                                                                     0x00000008W
#define SDMA7_CNTW__FENCE_SWAP_ENABWE_MASK                                                                    0x00000010W
#define SDMA7_CNTW__MIDCMD_PWEEMPT_ENABWE_MASK                                                                0x00000020W
#define SDMA7_CNTW__MIDCMD_WOWWDSWITCH_ENABWE_MASK                                                            0x00020000W
#define SDMA7_CNTW__AUTO_CTXSW_ENABWE_MASK                                                                    0x00040000W
#define SDMA7_CNTW__CTXEMPTY_INT_ENABWE_MASK                                                                  0x10000000W
#define SDMA7_CNTW__FWOZEN_INT_ENABWE_MASK                                                                    0x20000000W
#define SDMA7_CNTW__IB_PWEEMPT_INT_ENABWE_MASK                                                                0x40000000W
//SDMA7_CHICKEN_BITS
#define SDMA7_CHICKEN_BITS__COPY_EFFICIENCY_ENABWE__SHIFT                                                     0x0
#define SDMA7_CHICKEN_BITS__STAWW_ON_TWANS_FUWW_ENABWE__SHIFT                                                 0x1
#define SDMA7_CHICKEN_BITS__STAWW_ON_NO_FWEE_DATA_BUFFEW_ENABWE__SHIFT                                        0x2
#define SDMA7_CHICKEN_BITS__WWITE_BUWST_WENGTH__SHIFT                                                         0x8
#define SDMA7_CHICKEN_BITS__WWITE_BUWST_WAIT_CYCWE__SHIFT                                                     0xa
#define SDMA7_CHICKEN_BITS__COPY_OVEWWAP_ENABWE__SHIFT                                                        0x10
#define SDMA7_CHICKEN_BITS__WAW_CHECK_ENABWE__SHIFT                                                           0x11
#define SDMA7_CHICKEN_BITS__SWBM_POWW_WETWYING__SHIFT                                                         0x14
#define SDMA7_CHICKEN_BITS__CG_STATUS_OUTPUT__SHIFT                                                           0x17
#define SDMA7_CHICKEN_BITS__TIME_BASED_QOS__SHIFT                                                             0x19
#define SDMA7_CHICKEN_BITS__CE_AFIFO_WATEWMAWK__SHIFT                                                         0x1a
#define SDMA7_CHICKEN_BITS__CE_DFIFO_WATEWMAWK__SHIFT                                                         0x1c
#define SDMA7_CHICKEN_BITS__CE_WFIFO_WATEWMAWK__SHIFT                                                         0x1e
#define SDMA7_CHICKEN_BITS__COPY_EFFICIENCY_ENABWE_MASK                                                       0x00000001W
#define SDMA7_CHICKEN_BITS__STAWW_ON_TWANS_FUWW_ENABWE_MASK                                                   0x00000002W
#define SDMA7_CHICKEN_BITS__STAWW_ON_NO_FWEE_DATA_BUFFEW_ENABWE_MASK                                          0x00000004W
#define SDMA7_CHICKEN_BITS__WWITE_BUWST_WENGTH_MASK                                                           0x00000300W
#define SDMA7_CHICKEN_BITS__WWITE_BUWST_WAIT_CYCWE_MASK                                                       0x00001C00W
#define SDMA7_CHICKEN_BITS__COPY_OVEWWAP_ENABWE_MASK                                                          0x00010000W
#define SDMA7_CHICKEN_BITS__WAW_CHECK_ENABWE_MASK                                                             0x00020000W
#define SDMA7_CHICKEN_BITS__SWBM_POWW_WETWYING_MASK                                                           0x00100000W
#define SDMA7_CHICKEN_BITS__CG_STATUS_OUTPUT_MASK                                                             0x00800000W
#define SDMA7_CHICKEN_BITS__TIME_BASED_QOS_MASK                                                               0x02000000W
#define SDMA7_CHICKEN_BITS__CE_AFIFO_WATEWMAWK_MASK                                                           0x0C000000W
#define SDMA7_CHICKEN_BITS__CE_DFIFO_WATEWMAWK_MASK                                                           0x30000000W
#define SDMA7_CHICKEN_BITS__CE_WFIFO_WATEWMAWK_MASK                                                           0xC0000000W
//SDMA7_GB_ADDW_CONFIG
#define SDMA7_GB_ADDW_CONFIG__NUM_PIPES__SHIFT                                                                0x0
#define SDMA7_GB_ADDW_CONFIG__PIPE_INTEWWEAVE_SIZE__SHIFT                                                     0x3
#define SDMA7_GB_ADDW_CONFIG__BANK_INTEWWEAVE_SIZE__SHIFT                                                     0x8
#define SDMA7_GB_ADDW_CONFIG__NUM_BANKS__SHIFT                                                                0xc
#define SDMA7_GB_ADDW_CONFIG__NUM_SHADEW_ENGINES__SHIFT                                                       0x13
#define SDMA7_GB_ADDW_CONFIG__NUM_PIPES_MASK                                                                  0x00000007W
#define SDMA7_GB_ADDW_CONFIG__PIPE_INTEWWEAVE_SIZE_MASK                                                       0x00000038W
#define SDMA7_GB_ADDW_CONFIG__BANK_INTEWWEAVE_SIZE_MASK                                                       0x00000700W
#define SDMA7_GB_ADDW_CONFIG__NUM_BANKS_MASK                                                                  0x00007000W
#define SDMA7_GB_ADDW_CONFIG__NUM_SHADEW_ENGINES_MASK                                                         0x00180000W
//SDMA7_GB_ADDW_CONFIG_WEAD
#define SDMA7_GB_ADDW_CONFIG_WEAD__NUM_PIPES__SHIFT                                                           0x0
#define SDMA7_GB_ADDW_CONFIG_WEAD__PIPE_INTEWWEAVE_SIZE__SHIFT                                                0x3
#define SDMA7_GB_ADDW_CONFIG_WEAD__BANK_INTEWWEAVE_SIZE__SHIFT                                                0x8
#define SDMA7_GB_ADDW_CONFIG_WEAD__NUM_BANKS__SHIFT                                                           0xc
#define SDMA7_GB_ADDW_CONFIG_WEAD__NUM_SHADEW_ENGINES__SHIFT                                                  0x13
#define SDMA7_GB_ADDW_CONFIG_WEAD__NUM_PIPES_MASK                                                             0x00000007W
#define SDMA7_GB_ADDW_CONFIG_WEAD__PIPE_INTEWWEAVE_SIZE_MASK                                                  0x00000038W
#define SDMA7_GB_ADDW_CONFIG_WEAD__BANK_INTEWWEAVE_SIZE_MASK                                                  0x00000700W
#define SDMA7_GB_ADDW_CONFIG_WEAD__NUM_BANKS_MASK                                                             0x00007000W
#define SDMA7_GB_ADDW_CONFIG_WEAD__NUM_SHADEW_ENGINES_MASK                                                    0x00180000W
//SDMA7_WB_WPTW_FETCH_HI
#define SDMA7_WB_WPTW_FETCH_HI__OFFSET__SHIFT                                                                 0x0
#define SDMA7_WB_WPTW_FETCH_HI__OFFSET_MASK                                                                   0xFFFFFFFFW
//SDMA7_SEM_WAIT_FAIW_TIMEW_CNTW
#define SDMA7_SEM_WAIT_FAIW_TIMEW_CNTW__TIMEW__SHIFT                                                          0x0
#define SDMA7_SEM_WAIT_FAIW_TIMEW_CNTW__TIMEW_MASK                                                            0xFFFFFFFFW
//SDMA7_WB_WPTW_FETCH
#define SDMA7_WB_WPTW_FETCH__OFFSET__SHIFT                                                                    0x2
#define SDMA7_WB_WPTW_FETCH__OFFSET_MASK                                                                      0xFFFFFFFCW
//SDMA7_IB_OFFSET_FETCH
#define SDMA7_IB_OFFSET_FETCH__OFFSET__SHIFT                                                                  0x2
#define SDMA7_IB_OFFSET_FETCH__OFFSET_MASK                                                                    0x003FFFFCW
//SDMA7_PWOGWAM
#define SDMA7_PWOGWAM__STWEAM__SHIFT                                                                          0x0
#define SDMA7_PWOGWAM__STWEAM_MASK                                                                            0xFFFFFFFFW
//SDMA7_STATUS_WEG
#define SDMA7_STATUS_WEG__IDWE__SHIFT                                                                         0x0
#define SDMA7_STATUS_WEG__WEG_IDWE__SHIFT                                                                     0x1
#define SDMA7_STATUS_WEG__WB_EMPTY__SHIFT                                                                     0x2
#define SDMA7_STATUS_WEG__WB_FUWW__SHIFT                                                                      0x3
#define SDMA7_STATUS_WEG__WB_CMD_IDWE__SHIFT                                                                  0x4
#define SDMA7_STATUS_WEG__WB_CMD_FUWW__SHIFT                                                                  0x5
#define SDMA7_STATUS_WEG__IB_CMD_IDWE__SHIFT                                                                  0x6
#define SDMA7_STATUS_WEG__IB_CMD_FUWW__SHIFT                                                                  0x7
#define SDMA7_STATUS_WEG__BWOCK_IDWE__SHIFT                                                                   0x8
#define SDMA7_STATUS_WEG__INSIDE_IB__SHIFT                                                                    0x9
#define SDMA7_STATUS_WEG__EX_IDWE__SHIFT                                                                      0xa
#define SDMA7_STATUS_WEG__EX_IDWE_POWW_TIMEW_EXPIWE__SHIFT                                                    0xb
#define SDMA7_STATUS_WEG__PACKET_WEADY__SHIFT                                                                 0xc
#define SDMA7_STATUS_WEG__MC_WW_IDWE__SHIFT                                                                   0xd
#define SDMA7_STATUS_WEG__SWBM_IDWE__SHIFT                                                                    0xe
#define SDMA7_STATUS_WEG__CONTEXT_EMPTY__SHIFT                                                                0xf
#define SDMA7_STATUS_WEG__DEWTA_WPTW_FUWW__SHIFT                                                              0x10
#define SDMA7_STATUS_WEG__WB_MC_WWEQ_IDWE__SHIFT                                                              0x11
#define SDMA7_STATUS_WEG__IB_MC_WWEQ_IDWE__SHIFT                                                              0x12
#define SDMA7_STATUS_WEG__MC_WD_IDWE__SHIFT                                                                   0x13
#define SDMA7_STATUS_WEG__DEWTA_WPTW_EMPTY__SHIFT                                                             0x14
#define SDMA7_STATUS_WEG__MC_WD_WET_STAWW__SHIFT                                                              0x15
#define SDMA7_STATUS_WEG__MC_WD_NO_POWW_IDWE__SHIFT                                                           0x16
#define SDMA7_STATUS_WEG__PWEV_CMD_IDWE__SHIFT                                                                0x19
#define SDMA7_STATUS_WEG__SEM_IDWE__SHIFT                                                                     0x1a
#define SDMA7_STATUS_WEG__SEM_WEQ_STAWW__SHIFT                                                                0x1b
#define SDMA7_STATUS_WEG__SEM_WESP_STATE__SHIFT                                                               0x1c
#define SDMA7_STATUS_WEG__INT_IDWE__SHIFT                                                                     0x1e
#define SDMA7_STATUS_WEG__INT_WEQ_STAWW__SHIFT                                                                0x1f
#define SDMA7_STATUS_WEG__IDWE_MASK                                                                           0x00000001W
#define SDMA7_STATUS_WEG__WEG_IDWE_MASK                                                                       0x00000002W
#define SDMA7_STATUS_WEG__WB_EMPTY_MASK                                                                       0x00000004W
#define SDMA7_STATUS_WEG__WB_FUWW_MASK                                                                        0x00000008W
#define SDMA7_STATUS_WEG__WB_CMD_IDWE_MASK                                                                    0x00000010W
#define SDMA7_STATUS_WEG__WB_CMD_FUWW_MASK                                                                    0x00000020W
#define SDMA7_STATUS_WEG__IB_CMD_IDWE_MASK                                                                    0x00000040W
#define SDMA7_STATUS_WEG__IB_CMD_FUWW_MASK                                                                    0x00000080W
#define SDMA7_STATUS_WEG__BWOCK_IDWE_MASK                                                                     0x00000100W
#define SDMA7_STATUS_WEG__INSIDE_IB_MASK                                                                      0x00000200W
#define SDMA7_STATUS_WEG__EX_IDWE_MASK                                                                        0x00000400W
#define SDMA7_STATUS_WEG__EX_IDWE_POWW_TIMEW_EXPIWE_MASK                                                      0x00000800W
#define SDMA7_STATUS_WEG__PACKET_WEADY_MASK                                                                   0x00001000W
#define SDMA7_STATUS_WEG__MC_WW_IDWE_MASK                                                                     0x00002000W
#define SDMA7_STATUS_WEG__SWBM_IDWE_MASK                                                                      0x00004000W
#define SDMA7_STATUS_WEG__CONTEXT_EMPTY_MASK                                                                  0x00008000W
#define SDMA7_STATUS_WEG__DEWTA_WPTW_FUWW_MASK                                                                0x00010000W
#define SDMA7_STATUS_WEG__WB_MC_WWEQ_IDWE_MASK                                                                0x00020000W
#define SDMA7_STATUS_WEG__IB_MC_WWEQ_IDWE_MASK                                                                0x00040000W
#define SDMA7_STATUS_WEG__MC_WD_IDWE_MASK                                                                     0x00080000W
#define SDMA7_STATUS_WEG__DEWTA_WPTW_EMPTY_MASK                                                               0x00100000W
#define SDMA7_STATUS_WEG__MC_WD_WET_STAWW_MASK                                                                0x00200000W
#define SDMA7_STATUS_WEG__MC_WD_NO_POWW_IDWE_MASK                                                             0x00400000W
#define SDMA7_STATUS_WEG__PWEV_CMD_IDWE_MASK                                                                  0x02000000W
#define SDMA7_STATUS_WEG__SEM_IDWE_MASK                                                                       0x04000000W
#define SDMA7_STATUS_WEG__SEM_WEQ_STAWW_MASK                                                                  0x08000000W
#define SDMA7_STATUS_WEG__SEM_WESP_STATE_MASK                                                                 0x30000000W
#define SDMA7_STATUS_WEG__INT_IDWE_MASK                                                                       0x40000000W
#define SDMA7_STATUS_WEG__INT_WEQ_STAWW_MASK                                                                  0x80000000W
//SDMA7_STATUS1_WEG
#define SDMA7_STATUS1_WEG__CE_WWEQ_IDWE__SHIFT                                                                0x0
#define SDMA7_STATUS1_WEG__CE_WW_IDWE__SHIFT                                                                  0x1
#define SDMA7_STATUS1_WEG__CE_SPWIT_IDWE__SHIFT                                                               0x2
#define SDMA7_STATUS1_WEG__CE_WWEQ_IDWE__SHIFT                                                                0x3
#define SDMA7_STATUS1_WEG__CE_OUT_IDWE__SHIFT                                                                 0x4
#define SDMA7_STATUS1_WEG__CE_IN_IDWE__SHIFT                                                                  0x5
#define SDMA7_STATUS1_WEG__CE_DST_IDWE__SHIFT                                                                 0x6
#define SDMA7_STATUS1_WEG__CE_CMD_IDWE__SHIFT                                                                 0x9
#define SDMA7_STATUS1_WEG__CE_AFIFO_FUWW__SHIFT                                                               0xa
#define SDMA7_STATUS1_WEG__CE_INFO_FUWW__SHIFT                                                                0xd
#define SDMA7_STATUS1_WEG__CE_INFO1_FUWW__SHIFT                                                               0xe
#define SDMA7_STATUS1_WEG__EX_STAWT__SHIFT                                                                    0xf
#define SDMA7_STATUS1_WEG__CE_WD_STAWW__SHIFT                                                                 0x11
#define SDMA7_STATUS1_WEG__CE_WW_STAWW__SHIFT                                                                 0x12
#define SDMA7_STATUS1_WEG__CE_WWEQ_IDWE_MASK                                                                  0x00000001W
#define SDMA7_STATUS1_WEG__CE_WW_IDWE_MASK                                                                    0x00000002W
#define SDMA7_STATUS1_WEG__CE_SPWIT_IDWE_MASK                                                                 0x00000004W
#define SDMA7_STATUS1_WEG__CE_WWEQ_IDWE_MASK                                                                  0x00000008W
#define SDMA7_STATUS1_WEG__CE_OUT_IDWE_MASK                                                                   0x00000010W
#define SDMA7_STATUS1_WEG__CE_IN_IDWE_MASK                                                                    0x00000020W
#define SDMA7_STATUS1_WEG__CE_DST_IDWE_MASK                                                                   0x00000040W
#define SDMA7_STATUS1_WEG__CE_CMD_IDWE_MASK                                                                   0x00000200W
#define SDMA7_STATUS1_WEG__CE_AFIFO_FUWW_MASK                                                                 0x00000400W
#define SDMA7_STATUS1_WEG__CE_INFO_FUWW_MASK                                                                  0x00002000W
#define SDMA7_STATUS1_WEG__CE_INFO1_FUWW_MASK                                                                 0x00004000W
#define SDMA7_STATUS1_WEG__EX_STAWT_MASK                                                                      0x00008000W
#define SDMA7_STATUS1_WEG__CE_WD_STAWW_MASK                                                                   0x00020000W
#define SDMA7_STATUS1_WEG__CE_WW_STAWW_MASK                                                                   0x00040000W
//SDMA7_WD_BUWST_CNTW
#define SDMA7_WD_BUWST_CNTW__WD_BUWST__SHIFT                                                                  0x0
#define SDMA7_WD_BUWST_CNTW__CMD_BUFFEW_WD_BUWST__SHIFT                                                       0x2
#define SDMA7_WD_BUWST_CNTW__WD_BUWST_MASK                                                                    0x00000003W
#define SDMA7_WD_BUWST_CNTW__CMD_BUFFEW_WD_BUWST_MASK                                                         0x0000000CW
//SDMA7_HBM_PAGE_CONFIG
#define SDMA7_HBM_PAGE_CONFIG__PAGE_SIZE_EXPONENT__SHIFT                                                      0x0
#define SDMA7_HBM_PAGE_CONFIG__PAGE_SIZE_EXPONENT_MASK                                                        0x00000001W
//SDMA7_UCODE_CHECKSUM
#define SDMA7_UCODE_CHECKSUM__DATA__SHIFT                                                                     0x0
#define SDMA7_UCODE_CHECKSUM__DATA_MASK                                                                       0xFFFFFFFFW
//SDMA7_F32_CNTW
#define SDMA7_F32_CNTW__HAWT__SHIFT                                                                           0x0
#define SDMA7_F32_CNTW__STEP__SHIFT                                                                           0x1
#define SDMA7_F32_CNTW__HAWT_MASK                                                                             0x00000001W
#define SDMA7_F32_CNTW__STEP_MASK                                                                             0x00000002W
//SDMA7_FWEEZE
#define SDMA7_FWEEZE__PWEEMPT__SHIFT                                                                          0x0
#define SDMA7_FWEEZE__FWEEZE__SHIFT                                                                           0x4
#define SDMA7_FWEEZE__FWOZEN__SHIFT                                                                           0x5
#define SDMA7_FWEEZE__F32_FWEEZE__SHIFT                                                                       0x6
#define SDMA7_FWEEZE__PWEEMPT_MASK                                                                            0x00000001W
#define SDMA7_FWEEZE__FWEEZE_MASK                                                                             0x00000010W
#define SDMA7_FWEEZE__FWOZEN_MASK                                                                             0x00000020W
#define SDMA7_FWEEZE__F32_FWEEZE_MASK                                                                         0x00000040W
//SDMA7_PHASE0_QUANTUM
#define SDMA7_PHASE0_QUANTUM__UNIT__SHIFT                                                                     0x0
#define SDMA7_PHASE0_QUANTUM__VAWUE__SHIFT                                                                    0x8
#define SDMA7_PHASE0_QUANTUM__PWEFEW__SHIFT                                                                   0x1e
#define SDMA7_PHASE0_QUANTUM__UNIT_MASK                                                                       0x0000000FW
#define SDMA7_PHASE0_QUANTUM__VAWUE_MASK                                                                      0x00FFFF00W
#define SDMA7_PHASE0_QUANTUM__PWEFEW_MASK                                                                     0x40000000W
//SDMA7_PHASE1_QUANTUM
#define SDMA7_PHASE1_QUANTUM__UNIT__SHIFT                                                                     0x0
#define SDMA7_PHASE1_QUANTUM__VAWUE__SHIFT                                                                    0x8
#define SDMA7_PHASE1_QUANTUM__PWEFEW__SHIFT                                                                   0x1e
#define SDMA7_PHASE1_QUANTUM__UNIT_MASK                                                                       0x0000000FW
#define SDMA7_PHASE1_QUANTUM__VAWUE_MASK                                                                      0x00FFFF00W
#define SDMA7_PHASE1_QUANTUM__PWEFEW_MASK                                                                     0x40000000W
//SDMA7_EDC_CONFIG
#define SDMA7_EDC_CONFIG__DIS_EDC__SHIFT                                                                      0x1
#define SDMA7_EDC_CONFIG__ECC_INT_ENABWE__SHIFT                                                               0x2
#define SDMA7_EDC_CONFIG__DIS_EDC_MASK                                                                        0x00000002W
#define SDMA7_EDC_CONFIG__ECC_INT_ENABWE_MASK                                                                 0x00000004W
//SDMA7_BA_THWESHOWD
#define SDMA7_BA_THWESHOWD__WEAD_THWES__SHIFT                                                                 0x0
#define SDMA7_BA_THWESHOWD__WWITE_THWES__SHIFT                                                                0x10
#define SDMA7_BA_THWESHOWD__WEAD_THWES_MASK                                                                   0x000003FFW
#define SDMA7_BA_THWESHOWD__WWITE_THWES_MASK                                                                  0x03FF0000W
//SDMA7_ID
#define SDMA7_ID__DEVICE_ID__SHIFT                                                                            0x0
#define SDMA7_ID__DEVICE_ID_MASK                                                                              0x000000FFW
//SDMA7_VEWSION
#define SDMA7_VEWSION__MINVEW__SHIFT                                                                          0x0
#define SDMA7_VEWSION__MAJVEW__SHIFT                                                                          0x8
#define SDMA7_VEWSION__WEV__SHIFT                                                                             0x10
#define SDMA7_VEWSION__MINVEW_MASK                                                                            0x0000007FW
#define SDMA7_VEWSION__MAJVEW_MASK                                                                            0x00007F00W
#define SDMA7_VEWSION__WEV_MASK                                                                               0x003F0000W
//SDMA7_EDC_COUNTEW
#define SDMA7_EDC_COUNTEW__SDMA_UCODE_BUF_SED__SHIFT                                                          0x0
#define SDMA7_EDC_COUNTEW__SDMA_WB_CMD_BUF_SED__SHIFT                                                         0x2
#define SDMA7_EDC_COUNTEW__SDMA_IB_CMD_BUF_SED__SHIFT                                                         0x3
#define SDMA7_EDC_COUNTEW__SDMA_UTCW1_WD_FIFO_SED__SHIFT                                                      0x4
#define SDMA7_EDC_COUNTEW__SDMA_UTCW1_WDBST_FIFO_SED__SHIFT                                                   0x5
#define SDMA7_EDC_COUNTEW__SDMA_DATA_WUT_FIFO_SED__SHIFT                                                      0x6
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF0_SED__SHIFT                                                    0x7
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF1_SED__SHIFT                                                    0x8
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF2_SED__SHIFT                                                    0x9
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF3_SED__SHIFT                                                    0xa
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF4_SED__SHIFT                                                    0xb
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF5_SED__SHIFT                                                    0xc
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF6_SED__SHIFT                                                    0xd
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF7_SED__SHIFT                                                    0xe
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF8_SED__SHIFT                                                    0xf
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF9_SED__SHIFT                                                    0x10
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF10_SED__SHIFT                                                   0x11
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF11_SED__SHIFT                                                   0x12
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF12_SED__SHIFT                                                   0x13
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF13_SED__SHIFT                                                   0x14
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF14_SED__SHIFT                                                   0x15
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF15_SED__SHIFT                                                   0x16
#define SDMA7_EDC_COUNTEW__SDMA_SPWIT_DAT_BUF_SED__SHIFT                                                      0x17
#define SDMA7_EDC_COUNTEW__SDMA_MC_WW_ADDW_FIFO_SED__SHIFT                                                    0x18
#define SDMA7_EDC_COUNTEW__SDMA_UCODE_BUF_SED_MASK                                                            0x00000001W
#define SDMA7_EDC_COUNTEW__SDMA_WB_CMD_BUF_SED_MASK                                                           0x00000004W
#define SDMA7_EDC_COUNTEW__SDMA_IB_CMD_BUF_SED_MASK                                                           0x00000008W
#define SDMA7_EDC_COUNTEW__SDMA_UTCW1_WD_FIFO_SED_MASK                                                        0x00000010W
#define SDMA7_EDC_COUNTEW__SDMA_UTCW1_WDBST_FIFO_SED_MASK                                                     0x00000020W
#define SDMA7_EDC_COUNTEW__SDMA_DATA_WUT_FIFO_SED_MASK                                                        0x00000040W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF0_SED_MASK                                                      0x00000080W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF1_SED_MASK                                                      0x00000100W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF2_SED_MASK                                                      0x00000200W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF3_SED_MASK                                                      0x00000400W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF4_SED_MASK                                                      0x00000800W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF5_SED_MASK                                                      0x00001000W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF6_SED_MASK                                                      0x00002000W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF7_SED_MASK                                                      0x00004000W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF8_SED_MASK                                                      0x00008000W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF9_SED_MASK                                                      0x00010000W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF10_SED_MASK                                                     0x00020000W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF11_SED_MASK                                                     0x00040000W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF12_SED_MASK                                                     0x00080000W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF13_SED_MASK                                                     0x00100000W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF14_SED_MASK                                                     0x00200000W
#define SDMA7_EDC_COUNTEW__SDMA_MBANK_DATA_BUF15_SED_MASK                                                     0x00400000W
#define SDMA7_EDC_COUNTEW__SDMA_SPWIT_DAT_BUF_SED_MASK                                                        0x00800000W
#define SDMA7_EDC_COUNTEW__SDMA_MC_WW_ADDW_FIFO_SED_MASK                                                      0x01000000W
//SDMA7_EDC_COUNTEW_CWEAW
#define SDMA7_EDC_COUNTEW_CWEAW__DUMMY__SHIFT                                                                 0x0
#define SDMA7_EDC_COUNTEW_CWEAW__DUMMY_MASK                                                                   0x00000001W
//SDMA7_STATUS2_WEG
#define SDMA7_STATUS2_WEG__ID__SHIFT                                                                          0x0
#define SDMA7_STATUS2_WEG__F32_INSTW_PTW__SHIFT                                                               0x3
#define SDMA7_STATUS2_WEG__CMD_OP__SHIFT                                                                      0x10
#define SDMA7_STATUS2_WEG__ID_MASK                                                                            0x00000007W
#define SDMA7_STATUS2_WEG__F32_INSTW_PTW_MASK                                                                 0x0000FFF8W
#define SDMA7_STATUS2_WEG__CMD_OP_MASK                                                                        0xFFFF0000W
//SDMA7_ATOMIC_CNTW
#define SDMA7_ATOMIC_CNTW__WOOP_TIMEW__SHIFT                                                                  0x0
#define SDMA7_ATOMIC_CNTW__ATOMIC_WTN_INT_ENABWE__SHIFT                                                       0x1f
#define SDMA7_ATOMIC_CNTW__WOOP_TIMEW_MASK                                                                    0x7FFFFFFFW
#define SDMA7_ATOMIC_CNTW__ATOMIC_WTN_INT_ENABWE_MASK                                                         0x80000000W
//SDMA7_ATOMIC_PWEOP_WO
#define SDMA7_ATOMIC_PWEOP_WO__DATA__SHIFT                                                                    0x0
#define SDMA7_ATOMIC_PWEOP_WO__DATA_MASK                                                                      0xFFFFFFFFW
//SDMA7_ATOMIC_PWEOP_HI
#define SDMA7_ATOMIC_PWEOP_HI__DATA__SHIFT                                                                    0x0
#define SDMA7_ATOMIC_PWEOP_HI__DATA_MASK                                                                      0xFFFFFFFFW
//SDMA7_UTCW1_CNTW
#define SDMA7_UTCW1_CNTW__WEDO_ENABWE__SHIFT                                                                  0x0
#define SDMA7_UTCW1_CNTW__WEDO_DEWAY__SHIFT                                                                   0x1
#define SDMA7_UTCW1_CNTW__WEDO_WATEWMK__SHIFT                                                                 0xb
#define SDMA7_UTCW1_CNTW__INVACK_DEWAY__SHIFT                                                                 0xe
#define SDMA7_UTCW1_CNTW__WEQW2_CWEDIT__SHIFT                                                                 0x18
#define SDMA7_UTCW1_CNTW__VADDW_WATEWMK__SHIFT                                                                0x1d
#define SDMA7_UTCW1_CNTW__WEDO_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_UTCW1_CNTW__WEDO_DEWAY_MASK                                                                     0x000007FEW
#define SDMA7_UTCW1_CNTW__WEDO_WATEWMK_MASK                                                                   0x00003800W
#define SDMA7_UTCW1_CNTW__INVACK_DEWAY_MASK                                                                   0x00FFC000W
#define SDMA7_UTCW1_CNTW__WEQW2_CWEDIT_MASK                                                                   0x1F000000W
#define SDMA7_UTCW1_CNTW__VADDW_WATEWMK_MASK                                                                  0xE0000000W
//SDMA7_UTCW1_WATEWMK
#define SDMA7_UTCW1_WATEWMK__WEQMC_WATEWMK__SHIFT                                                             0x0
#define SDMA7_UTCW1_WATEWMK__WEQPG_WATEWMK__SHIFT                                                             0x9
#define SDMA7_UTCW1_WATEWMK__INVWEQ_WATEWMK__SHIFT                                                            0x11
#define SDMA7_UTCW1_WATEWMK__XNACK_WATEWMK__SHIFT                                                             0x19
#define SDMA7_UTCW1_WATEWMK__WEQMC_WATEWMK_MASK                                                               0x000001FFW
#define SDMA7_UTCW1_WATEWMK__WEQPG_WATEWMK_MASK                                                               0x0001FE00W
#define SDMA7_UTCW1_WATEWMK__INVWEQ_WATEWMK_MASK                                                              0x01FE0000W
#define SDMA7_UTCW1_WATEWMK__XNACK_WATEWMK_MASK                                                               0xFE000000W
//SDMA7_UTCW1_WD_STATUS
#define SDMA7_UTCW1_WD_STATUS__WQMC_WET_ADDW_FIFO_EMPTY__SHIFT                                                0x0
#define SDMA7_UTCW1_WD_STATUS__WQMC_WEQ_FIFO_EMPTY__SHIFT                                                     0x1
#define SDMA7_UTCW1_WD_STATUS__WTPG_WET_BUF_EMPTY__SHIFT                                                      0x2
#define SDMA7_UTCW1_WD_STATUS__WTPG_VADDW_FIFO_EMPTY__SHIFT                                                   0x3
#define SDMA7_UTCW1_WD_STATUS__WQPG_HEAD_VIWT_FIFO_EMPTY__SHIFT                                               0x4
#define SDMA7_UTCW1_WD_STATUS__WQPG_WEDO_FIFO_EMPTY__SHIFT                                                    0x5
#define SDMA7_UTCW1_WD_STATUS__WQPG_WEQPAGE_FIFO_EMPTY__SHIFT                                                 0x6
#define SDMA7_UTCW1_WD_STATUS__WQPG_XNACK_FIFO_EMPTY__SHIFT                                                   0x7
#define SDMA7_UTCW1_WD_STATUS__WQPG_INVWEQ_FIFO_EMPTY__SHIFT                                                  0x8
#define SDMA7_UTCW1_WD_STATUS__WQMC_WET_ADDW_FIFO_FUWW__SHIFT                                                 0x9
#define SDMA7_UTCW1_WD_STATUS__WQMC_WEQ_FIFO_FUWW__SHIFT                                                      0xa
#define SDMA7_UTCW1_WD_STATUS__WTPG_WET_BUF_FUWW__SHIFT                                                       0xb
#define SDMA7_UTCW1_WD_STATUS__WTPG_VADDW_FIFO_FUWW__SHIFT                                                    0xc
#define SDMA7_UTCW1_WD_STATUS__WQPG_HEAD_VIWT_FIFO_FUWW__SHIFT                                                0xd
#define SDMA7_UTCW1_WD_STATUS__WQPG_WEDO_FIFO_FUWW__SHIFT                                                     0xe
#define SDMA7_UTCW1_WD_STATUS__WQPG_WEQPAGE_FIFO_FUWW__SHIFT                                                  0xf
#define SDMA7_UTCW1_WD_STATUS__WQPG_XNACK_FIFO_FUWW__SHIFT                                                    0x10
#define SDMA7_UTCW1_WD_STATUS__WQPG_INVWEQ_FIFO_FUWW__SHIFT                                                   0x11
#define SDMA7_UTCW1_WD_STATUS__PAGE_FAUWT__SHIFT                                                              0x12
#define SDMA7_UTCW1_WD_STATUS__PAGE_NUWW__SHIFT                                                               0x13
#define SDMA7_UTCW1_WD_STATUS__WEQW2_IDWE__SHIFT                                                              0x14
#define SDMA7_UTCW1_WD_STATUS__CE_W1_STAWW__SHIFT                                                             0x15
#define SDMA7_UTCW1_WD_STATUS__NEXT_WD_VECTOW__SHIFT                                                          0x16
#define SDMA7_UTCW1_WD_STATUS__MEWGE_STATE__SHIFT                                                             0x1a
#define SDMA7_UTCW1_WD_STATUS__ADDW_WD_WTW__SHIFT                                                             0x1d
#define SDMA7_UTCW1_WD_STATUS__WPTW_POWWING__SHIFT                                                            0x1e
#define SDMA7_UTCW1_WD_STATUS__INVWEQ_SIZE__SHIFT                                                             0x1f
#define SDMA7_UTCW1_WD_STATUS__WQMC_WET_ADDW_FIFO_EMPTY_MASK                                                  0x00000001W
#define SDMA7_UTCW1_WD_STATUS__WQMC_WEQ_FIFO_EMPTY_MASK                                                       0x00000002W
#define SDMA7_UTCW1_WD_STATUS__WTPG_WET_BUF_EMPTY_MASK                                                        0x00000004W
#define SDMA7_UTCW1_WD_STATUS__WTPG_VADDW_FIFO_EMPTY_MASK                                                     0x00000008W
#define SDMA7_UTCW1_WD_STATUS__WQPG_HEAD_VIWT_FIFO_EMPTY_MASK                                                 0x00000010W
#define SDMA7_UTCW1_WD_STATUS__WQPG_WEDO_FIFO_EMPTY_MASK                                                      0x00000020W
#define SDMA7_UTCW1_WD_STATUS__WQPG_WEQPAGE_FIFO_EMPTY_MASK                                                   0x00000040W
#define SDMA7_UTCW1_WD_STATUS__WQPG_XNACK_FIFO_EMPTY_MASK                                                     0x00000080W
#define SDMA7_UTCW1_WD_STATUS__WQPG_INVWEQ_FIFO_EMPTY_MASK                                                    0x00000100W
#define SDMA7_UTCW1_WD_STATUS__WQMC_WET_ADDW_FIFO_FUWW_MASK                                                   0x00000200W
#define SDMA7_UTCW1_WD_STATUS__WQMC_WEQ_FIFO_FUWW_MASK                                                        0x00000400W
#define SDMA7_UTCW1_WD_STATUS__WTPG_WET_BUF_FUWW_MASK                                                         0x00000800W
#define SDMA7_UTCW1_WD_STATUS__WTPG_VADDW_FIFO_FUWW_MASK                                                      0x00001000W
#define SDMA7_UTCW1_WD_STATUS__WQPG_HEAD_VIWT_FIFO_FUWW_MASK                                                  0x00002000W
#define SDMA7_UTCW1_WD_STATUS__WQPG_WEDO_FIFO_FUWW_MASK                                                       0x00004000W
#define SDMA7_UTCW1_WD_STATUS__WQPG_WEQPAGE_FIFO_FUWW_MASK                                                    0x00008000W
#define SDMA7_UTCW1_WD_STATUS__WQPG_XNACK_FIFO_FUWW_MASK                                                      0x00010000W
#define SDMA7_UTCW1_WD_STATUS__WQPG_INVWEQ_FIFO_FUWW_MASK                                                     0x00020000W
#define SDMA7_UTCW1_WD_STATUS__PAGE_FAUWT_MASK                                                                0x00040000W
#define SDMA7_UTCW1_WD_STATUS__PAGE_NUWW_MASK                                                                 0x00080000W
#define SDMA7_UTCW1_WD_STATUS__WEQW2_IDWE_MASK                                                                0x00100000W
#define SDMA7_UTCW1_WD_STATUS__CE_W1_STAWW_MASK                                                               0x00200000W
#define SDMA7_UTCW1_WD_STATUS__NEXT_WD_VECTOW_MASK                                                            0x03C00000W
#define SDMA7_UTCW1_WD_STATUS__MEWGE_STATE_MASK                                                               0x1C000000W
#define SDMA7_UTCW1_WD_STATUS__ADDW_WD_WTW_MASK                                                               0x20000000W
#define SDMA7_UTCW1_WD_STATUS__WPTW_POWWING_MASK                                                              0x40000000W
#define SDMA7_UTCW1_WD_STATUS__INVWEQ_SIZE_MASK                                                               0x80000000W
//SDMA7_UTCW1_WW_STATUS
#define SDMA7_UTCW1_WW_STATUS__WQMC_WET_ADDW_FIFO_EMPTY__SHIFT                                                0x0
#define SDMA7_UTCW1_WW_STATUS__WQMC_WEQ_FIFO_EMPTY__SHIFT                                                     0x1
#define SDMA7_UTCW1_WW_STATUS__WTPG_WET_BUF_EMPTY__SHIFT                                                      0x2
#define SDMA7_UTCW1_WW_STATUS__WTPG_VADDW_FIFO_EMPTY__SHIFT                                                   0x3
#define SDMA7_UTCW1_WW_STATUS__WQPG_HEAD_VIWT_FIFO_EMPTY__SHIFT                                               0x4
#define SDMA7_UTCW1_WW_STATUS__WQPG_WEDO_FIFO_EMPTY__SHIFT                                                    0x5
#define SDMA7_UTCW1_WW_STATUS__WQPG_WEQPAGE_FIFO_EMPTY__SHIFT                                                 0x6
#define SDMA7_UTCW1_WW_STATUS__WQPG_XNACK_FIFO_EMPTY__SHIFT                                                   0x7
#define SDMA7_UTCW1_WW_STATUS__WQPG_INVWEQ_FIFO_EMPTY__SHIFT                                                  0x8
#define SDMA7_UTCW1_WW_STATUS__WQMC_WET_ADDW_FIFO_FUWW__SHIFT                                                 0x9
#define SDMA7_UTCW1_WW_STATUS__WQMC_WEQ_FIFO_FUWW__SHIFT                                                      0xa
#define SDMA7_UTCW1_WW_STATUS__WTPG_WET_BUF_FUWW__SHIFT                                                       0xb
#define SDMA7_UTCW1_WW_STATUS__WTPG_VADDW_FIFO_FUWW__SHIFT                                                    0xc
#define SDMA7_UTCW1_WW_STATUS__WQPG_HEAD_VIWT_FIFO_FUWW__SHIFT                                                0xd
#define SDMA7_UTCW1_WW_STATUS__WQPG_WEDO_FIFO_FUWW__SHIFT                                                     0xe
#define SDMA7_UTCW1_WW_STATUS__WQPG_WEQPAGE_FIFO_FUWW__SHIFT                                                  0xf
#define SDMA7_UTCW1_WW_STATUS__WQPG_XNACK_FIFO_FUWW__SHIFT                                                    0x10
#define SDMA7_UTCW1_WW_STATUS__WQPG_INVWEQ_FIFO_FUWW__SHIFT                                                   0x11
#define SDMA7_UTCW1_WW_STATUS__PAGE_FAUWT__SHIFT                                                              0x12
#define SDMA7_UTCW1_WW_STATUS__PAGE_NUWW__SHIFT                                                               0x13
#define SDMA7_UTCW1_WW_STATUS__WEQW2_IDWE__SHIFT                                                              0x14
#define SDMA7_UTCW1_WW_STATUS__F32_WW_WTW__SHIFT                                                              0x15
#define SDMA7_UTCW1_WW_STATUS__NEXT_WW_VECTOW__SHIFT                                                          0x16
#define SDMA7_UTCW1_WW_STATUS__MEWGE_STATE__SHIFT                                                             0x19
#define SDMA7_UTCW1_WW_STATUS__WPTW_DATA_FIFO_EMPTY__SHIFT                                                    0x1c
#define SDMA7_UTCW1_WW_STATUS__WPTW_DATA_FIFO_FUWW__SHIFT                                                     0x1d
#define SDMA7_UTCW1_WW_STATUS__WWWEQ_DATA_FIFO_EMPTY__SHIFT                                                   0x1e
#define SDMA7_UTCW1_WW_STATUS__WWWEQ_DATA_FIFO_FUWW__SHIFT                                                    0x1f
#define SDMA7_UTCW1_WW_STATUS__WQMC_WET_ADDW_FIFO_EMPTY_MASK                                                  0x00000001W
#define SDMA7_UTCW1_WW_STATUS__WQMC_WEQ_FIFO_EMPTY_MASK                                                       0x00000002W
#define SDMA7_UTCW1_WW_STATUS__WTPG_WET_BUF_EMPTY_MASK                                                        0x00000004W
#define SDMA7_UTCW1_WW_STATUS__WTPG_VADDW_FIFO_EMPTY_MASK                                                     0x00000008W
#define SDMA7_UTCW1_WW_STATUS__WQPG_HEAD_VIWT_FIFO_EMPTY_MASK                                                 0x00000010W
#define SDMA7_UTCW1_WW_STATUS__WQPG_WEDO_FIFO_EMPTY_MASK                                                      0x00000020W
#define SDMA7_UTCW1_WW_STATUS__WQPG_WEQPAGE_FIFO_EMPTY_MASK                                                   0x00000040W
#define SDMA7_UTCW1_WW_STATUS__WQPG_XNACK_FIFO_EMPTY_MASK                                                     0x00000080W
#define SDMA7_UTCW1_WW_STATUS__WQPG_INVWEQ_FIFO_EMPTY_MASK                                                    0x00000100W
#define SDMA7_UTCW1_WW_STATUS__WQMC_WET_ADDW_FIFO_FUWW_MASK                                                   0x00000200W
#define SDMA7_UTCW1_WW_STATUS__WQMC_WEQ_FIFO_FUWW_MASK                                                        0x00000400W
#define SDMA7_UTCW1_WW_STATUS__WTPG_WET_BUF_FUWW_MASK                                                         0x00000800W
#define SDMA7_UTCW1_WW_STATUS__WTPG_VADDW_FIFO_FUWW_MASK                                                      0x00001000W
#define SDMA7_UTCW1_WW_STATUS__WQPG_HEAD_VIWT_FIFO_FUWW_MASK                                                  0x00002000W
#define SDMA7_UTCW1_WW_STATUS__WQPG_WEDO_FIFO_FUWW_MASK                                                       0x00004000W
#define SDMA7_UTCW1_WW_STATUS__WQPG_WEQPAGE_FIFO_FUWW_MASK                                                    0x00008000W
#define SDMA7_UTCW1_WW_STATUS__WQPG_XNACK_FIFO_FUWW_MASK                                                      0x00010000W
#define SDMA7_UTCW1_WW_STATUS__WQPG_INVWEQ_FIFO_FUWW_MASK                                                     0x00020000W
#define SDMA7_UTCW1_WW_STATUS__PAGE_FAUWT_MASK                                                                0x00040000W
#define SDMA7_UTCW1_WW_STATUS__PAGE_NUWW_MASK                                                                 0x00080000W
#define SDMA7_UTCW1_WW_STATUS__WEQW2_IDWE_MASK                                                                0x00100000W
#define SDMA7_UTCW1_WW_STATUS__F32_WW_WTW_MASK                                                                0x00200000W
#define SDMA7_UTCW1_WW_STATUS__NEXT_WW_VECTOW_MASK                                                            0x01C00000W
#define SDMA7_UTCW1_WW_STATUS__MEWGE_STATE_MASK                                                               0x0E000000W
#define SDMA7_UTCW1_WW_STATUS__WPTW_DATA_FIFO_EMPTY_MASK                                                      0x10000000W
#define SDMA7_UTCW1_WW_STATUS__WPTW_DATA_FIFO_FUWW_MASK                                                       0x20000000W
#define SDMA7_UTCW1_WW_STATUS__WWWEQ_DATA_FIFO_EMPTY_MASK                                                     0x40000000W
#define SDMA7_UTCW1_WW_STATUS__WWWEQ_DATA_FIFO_FUWW_MASK                                                      0x80000000W
//SDMA7_UTCW1_INV0
#define SDMA7_UTCW1_INV0__INV_MIDDWE__SHIFT                                                                   0x0
#define SDMA7_UTCW1_INV0__WD_TIMEOUT__SHIFT                                                                   0x1
#define SDMA7_UTCW1_INV0__WW_TIMEOUT__SHIFT                                                                   0x2
#define SDMA7_UTCW1_INV0__WD_IN_INVADW__SHIFT                                                                 0x3
#define SDMA7_UTCW1_INV0__WW_IN_INVADW__SHIFT                                                                 0x4
#define SDMA7_UTCW1_INV0__PAGE_NUWW_SW__SHIFT                                                                 0x5
#define SDMA7_UTCW1_INV0__XNACK_IS_INVADW__SHIFT                                                              0x6
#define SDMA7_UTCW1_INV0__INVWEQ_ENABWE__SHIFT                                                                0x7
#define SDMA7_UTCW1_INV0__NACK_TIMEOUT_SW__SHIFT                                                              0x8
#define SDMA7_UTCW1_INV0__NFWUSH_INV_IDWE__SHIFT                                                              0x9
#define SDMA7_UTCW1_INV0__FWUSH_INV_IDWE__SHIFT                                                               0xa
#define SDMA7_UTCW1_INV0__INV_FWUSHTYPE__SHIFT                                                                0xb
#define SDMA7_UTCW1_INV0__INV_VMID_VEC__SHIFT                                                                 0xc
#define SDMA7_UTCW1_INV0__INV_ADDW_HI__SHIFT                                                                  0x1c
#define SDMA7_UTCW1_INV0__INV_MIDDWE_MASK                                                                     0x00000001W
#define SDMA7_UTCW1_INV0__WD_TIMEOUT_MASK                                                                     0x00000002W
#define SDMA7_UTCW1_INV0__WW_TIMEOUT_MASK                                                                     0x00000004W
#define SDMA7_UTCW1_INV0__WD_IN_INVADW_MASK                                                                   0x00000008W
#define SDMA7_UTCW1_INV0__WW_IN_INVADW_MASK                                                                   0x00000010W
#define SDMA7_UTCW1_INV0__PAGE_NUWW_SW_MASK                                                                   0x00000020W
#define SDMA7_UTCW1_INV0__XNACK_IS_INVADW_MASK                                                                0x00000040W
#define SDMA7_UTCW1_INV0__INVWEQ_ENABWE_MASK                                                                  0x00000080W
#define SDMA7_UTCW1_INV0__NACK_TIMEOUT_SW_MASK                                                                0x00000100W
#define SDMA7_UTCW1_INV0__NFWUSH_INV_IDWE_MASK                                                                0x00000200W
#define SDMA7_UTCW1_INV0__FWUSH_INV_IDWE_MASK                                                                 0x00000400W
#define SDMA7_UTCW1_INV0__INV_FWUSHTYPE_MASK                                                                  0x00000800W
#define SDMA7_UTCW1_INV0__INV_VMID_VEC_MASK                                                                   0x0FFFF000W
#define SDMA7_UTCW1_INV0__INV_ADDW_HI_MASK                                                                    0xF0000000W
//SDMA7_UTCW1_INV1
#define SDMA7_UTCW1_INV1__INV_ADDW_WO__SHIFT                                                                  0x0
#define SDMA7_UTCW1_INV1__INV_ADDW_WO_MASK                                                                    0xFFFFFFFFW
//SDMA7_UTCW1_INV2
#define SDMA7_UTCW1_INV2__INV_NFWUSH_VMID_VEC__SHIFT                                                          0x0
#define SDMA7_UTCW1_INV2__INV_NFWUSH_VMID_VEC_MASK                                                            0xFFFFFFFFW
//SDMA7_UTCW1_WD_XNACK0
#define SDMA7_UTCW1_WD_XNACK0__XNACK_ADDW_WO__SHIFT                                                           0x0
#define SDMA7_UTCW1_WD_XNACK0__XNACK_ADDW_WO_MASK                                                             0xFFFFFFFFW
//SDMA7_UTCW1_WD_XNACK1
#define SDMA7_UTCW1_WD_XNACK1__XNACK_ADDW_HI__SHIFT                                                           0x0
#define SDMA7_UTCW1_WD_XNACK1__XNACK_VMID__SHIFT                                                              0x4
#define SDMA7_UTCW1_WD_XNACK1__XNACK_VECTOW__SHIFT                                                            0x8
#define SDMA7_UTCW1_WD_XNACK1__IS_XNACK__SHIFT                                                                0x1a
#define SDMA7_UTCW1_WD_XNACK1__XNACK_ADDW_HI_MASK                                                             0x0000000FW
#define SDMA7_UTCW1_WD_XNACK1__XNACK_VMID_MASK                                                                0x000000F0W
#define SDMA7_UTCW1_WD_XNACK1__XNACK_VECTOW_MASK                                                              0x03FFFF00W
#define SDMA7_UTCW1_WD_XNACK1__IS_XNACK_MASK                                                                  0x0C000000W
//SDMA7_UTCW1_WW_XNACK0
#define SDMA7_UTCW1_WW_XNACK0__XNACK_ADDW_WO__SHIFT                                                           0x0
#define SDMA7_UTCW1_WW_XNACK0__XNACK_ADDW_WO_MASK                                                             0xFFFFFFFFW
//SDMA7_UTCW1_WW_XNACK1
#define SDMA7_UTCW1_WW_XNACK1__XNACK_ADDW_HI__SHIFT                                                           0x0
#define SDMA7_UTCW1_WW_XNACK1__XNACK_VMID__SHIFT                                                              0x4
#define SDMA7_UTCW1_WW_XNACK1__XNACK_VECTOW__SHIFT                                                            0x8
#define SDMA7_UTCW1_WW_XNACK1__IS_XNACK__SHIFT                                                                0x1a
#define SDMA7_UTCW1_WW_XNACK1__XNACK_ADDW_HI_MASK                                                             0x0000000FW
#define SDMA7_UTCW1_WW_XNACK1__XNACK_VMID_MASK                                                                0x000000F0W
#define SDMA7_UTCW1_WW_XNACK1__XNACK_VECTOW_MASK                                                              0x03FFFF00W
#define SDMA7_UTCW1_WW_XNACK1__IS_XNACK_MASK                                                                  0x0C000000W
//SDMA7_UTCW1_TIMEOUT
#define SDMA7_UTCW1_TIMEOUT__WD_XNACK_WIMIT__SHIFT                                                            0x0
#define SDMA7_UTCW1_TIMEOUT__WW_XNACK_WIMIT__SHIFT                                                            0x10
#define SDMA7_UTCW1_TIMEOUT__WD_XNACK_WIMIT_MASK                                                              0x0000FFFFW
#define SDMA7_UTCW1_TIMEOUT__WW_XNACK_WIMIT_MASK                                                              0xFFFF0000W
//SDMA7_UTCW1_PAGE
#define SDMA7_UTCW1_PAGE__VM_HOWE__SHIFT                                                                      0x0
#define SDMA7_UTCW1_PAGE__WEQ_TYPE__SHIFT                                                                     0x1
#define SDMA7_UTCW1_PAGE__USE_MTYPE__SHIFT                                                                    0x6
#define SDMA7_UTCW1_PAGE__USE_PT_SNOOP__SHIFT                                                                 0x9
#define SDMA7_UTCW1_PAGE__VM_HOWE_MASK                                                                        0x00000001W
#define SDMA7_UTCW1_PAGE__WEQ_TYPE_MASK                                                                       0x0000001EW
#define SDMA7_UTCW1_PAGE__USE_MTYPE_MASK                                                                      0x000001C0W
#define SDMA7_UTCW1_PAGE__USE_PT_SNOOP_MASK                                                                   0x00000200W
//SDMA7_POWEW_CNTW_IDWE
#define SDMA7_POWEW_CNTW_IDWE__DEWAY0__SHIFT                                                                  0x0
#define SDMA7_POWEW_CNTW_IDWE__DEWAY1__SHIFT                                                                  0x10
#define SDMA7_POWEW_CNTW_IDWE__DEWAY2__SHIFT                                                                  0x18
#define SDMA7_POWEW_CNTW_IDWE__DEWAY0_MASK                                                                    0x0000FFFFW
#define SDMA7_POWEW_CNTW_IDWE__DEWAY1_MASK                                                                    0x00FF0000W
#define SDMA7_POWEW_CNTW_IDWE__DEWAY2_MASK                                                                    0xFF000000W
//SDMA7_WEWAX_OWDEWING_WUT
#define SDMA7_WEWAX_OWDEWING_WUT__WESEWVED0__SHIFT                                                            0x0
#define SDMA7_WEWAX_OWDEWING_WUT__COPY__SHIFT                                                                 0x1
#define SDMA7_WEWAX_OWDEWING_WUT__WWITE__SHIFT                                                                0x2
#define SDMA7_WEWAX_OWDEWING_WUT__WESEWVED3__SHIFT                                                            0x3
#define SDMA7_WEWAX_OWDEWING_WUT__WESEWVED4__SHIFT                                                            0x4
#define SDMA7_WEWAX_OWDEWING_WUT__FENCE__SHIFT                                                                0x5
#define SDMA7_WEWAX_OWDEWING_WUT__WESEWVED76__SHIFT                                                           0x6
#define SDMA7_WEWAX_OWDEWING_WUT__POWW_MEM__SHIFT                                                             0x8
#define SDMA7_WEWAX_OWDEWING_WUT__COND_EXE__SHIFT                                                             0x9
#define SDMA7_WEWAX_OWDEWING_WUT__ATOMIC__SHIFT                                                               0xa
#define SDMA7_WEWAX_OWDEWING_WUT__CONST_FIWW__SHIFT                                                           0xb
#define SDMA7_WEWAX_OWDEWING_WUT__PTEPDE__SHIFT                                                               0xc
#define SDMA7_WEWAX_OWDEWING_WUT__TIMESTAMP__SHIFT                                                            0xd
#define SDMA7_WEWAX_OWDEWING_WUT__WESEWVED__SHIFT                                                             0xe
#define SDMA7_WEWAX_OWDEWING_WUT__WOWWD_SWITCH__SHIFT                                                         0x1b
#define SDMA7_WEWAX_OWDEWING_WUT__WPTW_WWB__SHIFT                                                             0x1c
#define SDMA7_WEWAX_OWDEWING_WUT__WPTW_POWW__SHIFT                                                            0x1d
#define SDMA7_WEWAX_OWDEWING_WUT__IB_FETCH__SHIFT                                                             0x1e
#define SDMA7_WEWAX_OWDEWING_WUT__WB_FETCH__SHIFT                                                             0x1f
#define SDMA7_WEWAX_OWDEWING_WUT__WESEWVED0_MASK                                                              0x00000001W
#define SDMA7_WEWAX_OWDEWING_WUT__COPY_MASK                                                                   0x00000002W
#define SDMA7_WEWAX_OWDEWING_WUT__WWITE_MASK                                                                  0x00000004W
#define SDMA7_WEWAX_OWDEWING_WUT__WESEWVED3_MASK                                                              0x00000008W
#define SDMA7_WEWAX_OWDEWING_WUT__WESEWVED4_MASK                                                              0x00000010W
#define SDMA7_WEWAX_OWDEWING_WUT__FENCE_MASK                                                                  0x00000020W
#define SDMA7_WEWAX_OWDEWING_WUT__WESEWVED76_MASK                                                             0x000000C0W
#define SDMA7_WEWAX_OWDEWING_WUT__POWW_MEM_MASK                                                               0x00000100W
#define SDMA7_WEWAX_OWDEWING_WUT__COND_EXE_MASK                                                               0x00000200W
#define SDMA7_WEWAX_OWDEWING_WUT__ATOMIC_MASK                                                                 0x00000400W
#define SDMA7_WEWAX_OWDEWING_WUT__CONST_FIWW_MASK                                                             0x00000800W
#define SDMA7_WEWAX_OWDEWING_WUT__PTEPDE_MASK                                                                 0x00001000W
#define SDMA7_WEWAX_OWDEWING_WUT__TIMESTAMP_MASK                                                              0x00002000W
#define SDMA7_WEWAX_OWDEWING_WUT__WESEWVED_MASK                                                               0x07FFC000W
#define SDMA7_WEWAX_OWDEWING_WUT__WOWWD_SWITCH_MASK                                                           0x08000000W
#define SDMA7_WEWAX_OWDEWING_WUT__WPTW_WWB_MASK                                                               0x10000000W
#define SDMA7_WEWAX_OWDEWING_WUT__WPTW_POWW_MASK                                                              0x20000000W
#define SDMA7_WEWAX_OWDEWING_WUT__IB_FETCH_MASK                                                               0x40000000W
#define SDMA7_WEWAX_OWDEWING_WUT__WB_FETCH_MASK                                                               0x80000000W
//SDMA7_CHICKEN_BITS_2
#define SDMA7_CHICKEN_BITS_2__F32_CMD_PWOC_DEWAY__SHIFT                                                       0x0
#define SDMA7_CHICKEN_BITS_2__F32_CMD_PWOC_DEWAY_MASK                                                         0x0000000FW
//SDMA7_STATUS3_WEG
#define SDMA7_STATUS3_WEG__CMD_OP_STATUS__SHIFT                                                               0x0
#define SDMA7_STATUS3_WEG__PWEV_VM_CMD__SHIFT                                                                 0x10
#define SDMA7_STATUS3_WEG__EXCEPTION_IDWE__SHIFT                                                              0x14
#define SDMA7_STATUS3_WEG__QUEUE_ID_MATCH__SHIFT                                                              0x15
#define SDMA7_STATUS3_WEG__INT_QUEUE_ID__SHIFT                                                                0x16
#define SDMA7_STATUS3_WEG__CMD_OP_STATUS_MASK                                                                 0x0000FFFFW
#define SDMA7_STATUS3_WEG__PWEV_VM_CMD_MASK                                                                   0x000F0000W
#define SDMA7_STATUS3_WEG__EXCEPTION_IDWE_MASK                                                                0x00100000W
#define SDMA7_STATUS3_WEG__QUEUE_ID_MATCH_MASK                                                                0x00200000W
#define SDMA7_STATUS3_WEG__INT_QUEUE_ID_MASK                                                                  0x03C00000W
//SDMA7_PHYSICAW_ADDW_WO
#define SDMA7_PHYSICAW_ADDW_WO__D_VAWID__SHIFT                                                                0x0
#define SDMA7_PHYSICAW_ADDW_WO__DIWTY__SHIFT                                                                  0x1
#define SDMA7_PHYSICAW_ADDW_WO__PHY_VAWID__SHIFT                                                              0x2
#define SDMA7_PHYSICAW_ADDW_WO__ADDW__SHIFT                                                                   0xc
#define SDMA7_PHYSICAW_ADDW_WO__D_VAWID_MASK                                                                  0x00000001W
#define SDMA7_PHYSICAW_ADDW_WO__DIWTY_MASK                                                                    0x00000002W
#define SDMA7_PHYSICAW_ADDW_WO__PHY_VAWID_MASK                                                                0x00000004W
#define SDMA7_PHYSICAW_ADDW_WO__ADDW_MASK                                                                     0xFFFFF000W
//SDMA7_PHYSICAW_ADDW_HI
#define SDMA7_PHYSICAW_ADDW_HI__ADDW__SHIFT                                                                   0x0
#define SDMA7_PHYSICAW_ADDW_HI__ADDW_MASK                                                                     0x0000FFFFW
//SDMA7_PHASE2_QUANTUM
#define SDMA7_PHASE2_QUANTUM__UNIT__SHIFT                                                                     0x0
#define SDMA7_PHASE2_QUANTUM__VAWUE__SHIFT                                                                    0x8
#define SDMA7_PHASE2_QUANTUM__PWEFEW__SHIFT                                                                   0x1e
#define SDMA7_PHASE2_QUANTUM__UNIT_MASK                                                                       0x0000000FW
#define SDMA7_PHASE2_QUANTUM__VAWUE_MASK                                                                      0x00FFFF00W
#define SDMA7_PHASE2_QUANTUM__PWEFEW_MASK                                                                     0x40000000W
//SDMA7_EWWOW_WOG
#define SDMA7_EWWOW_WOG__OVEWWIDE__SHIFT                                                                      0x0
#define SDMA7_EWWOW_WOG__STATUS__SHIFT                                                                        0x10
#define SDMA7_EWWOW_WOG__OVEWWIDE_MASK                                                                        0x0000FFFFW
#define SDMA7_EWWOW_WOG__STATUS_MASK                                                                          0xFFFF0000W
//SDMA7_PUB_DUMMY_WEG0
#define SDMA7_PUB_DUMMY_WEG0__VAWUE__SHIFT                                                                    0x0
#define SDMA7_PUB_DUMMY_WEG0__VAWUE_MASK                                                                      0xFFFFFFFFW
//SDMA7_PUB_DUMMY_WEG1
#define SDMA7_PUB_DUMMY_WEG1__VAWUE__SHIFT                                                                    0x0
#define SDMA7_PUB_DUMMY_WEG1__VAWUE_MASK                                                                      0xFFFFFFFFW
//SDMA7_PUB_DUMMY_WEG2
#define SDMA7_PUB_DUMMY_WEG2__VAWUE__SHIFT                                                                    0x0
#define SDMA7_PUB_DUMMY_WEG2__VAWUE_MASK                                                                      0xFFFFFFFFW
//SDMA7_PUB_DUMMY_WEG3
#define SDMA7_PUB_DUMMY_WEG3__VAWUE__SHIFT                                                                    0x0
#define SDMA7_PUB_DUMMY_WEG3__VAWUE_MASK                                                                      0xFFFFFFFFW
//SDMA7_F32_COUNTEW
#define SDMA7_F32_COUNTEW__VAWUE__SHIFT                                                                       0x0
#define SDMA7_F32_COUNTEW__VAWUE_MASK                                                                         0xFFFFFFFFW
//SDMA7_UNBWEAKABWE
#define SDMA7_UNBWEAKABWE__VAWUE__SHIFT                                                                       0x0
#define SDMA7_UNBWEAKABWE__VAWUE_MASK                                                                         0x00000001W
//SDMA7_PEWFMON_CNTW
#define SDMA7_PEWFMON_CNTW__PEWF_ENABWE0__SHIFT                                                               0x0
#define SDMA7_PEWFMON_CNTW__PEWF_CWEAW0__SHIFT                                                                0x1
#define SDMA7_PEWFMON_CNTW__PEWF_SEW0__SHIFT                                                                  0x2
#define SDMA7_PEWFMON_CNTW__PEWF_ENABWE1__SHIFT                                                               0xa
#define SDMA7_PEWFMON_CNTW__PEWF_CWEAW1__SHIFT                                                                0xb
#define SDMA7_PEWFMON_CNTW__PEWF_SEW1__SHIFT                                                                  0xc
#define SDMA7_PEWFMON_CNTW__PEWF_ENABWE0_MASK                                                                 0x00000001W
#define SDMA7_PEWFMON_CNTW__PEWF_CWEAW0_MASK                                                                  0x00000002W
#define SDMA7_PEWFMON_CNTW__PEWF_SEW0_MASK                                                                    0x000003FCW
#define SDMA7_PEWFMON_CNTW__PEWF_ENABWE1_MASK                                                                 0x00000400W
#define SDMA7_PEWFMON_CNTW__PEWF_CWEAW1_MASK                                                                  0x00000800W
#define SDMA7_PEWFMON_CNTW__PEWF_SEW1_MASK                                                                    0x000FF000W
//SDMA7_PEWFCOUNTEW0_WESUWT
#define SDMA7_PEWFCOUNTEW0_WESUWT__PEWF_COUNT__SHIFT                                                          0x0
#define SDMA7_PEWFCOUNTEW0_WESUWT__PEWF_COUNT_MASK                                                            0xFFFFFFFFW
//SDMA7_PEWFCOUNTEW1_WESUWT
#define SDMA7_PEWFCOUNTEW1_WESUWT__PEWF_COUNT__SHIFT                                                          0x0
#define SDMA7_PEWFCOUNTEW1_WESUWT__PEWF_COUNT_MASK                                                            0xFFFFFFFFW
//SDMA7_PEWFCOUNTEW_TAG_DEWAY_WANGE
#define SDMA7_PEWFCOUNTEW_TAG_DEWAY_WANGE__WANGE_WOW__SHIFT                                                   0x0
#define SDMA7_PEWFCOUNTEW_TAG_DEWAY_WANGE__WANGE_HIGH__SHIFT                                                  0xe
#define SDMA7_PEWFCOUNTEW_TAG_DEWAY_WANGE__SEWECT_WW__SHIFT                                                   0x1c
#define SDMA7_PEWFCOUNTEW_TAG_DEWAY_WANGE__WANGE_WOW_MASK                                                     0x00003FFFW
#define SDMA7_PEWFCOUNTEW_TAG_DEWAY_WANGE__WANGE_HIGH_MASK                                                    0x0FFFC000W
#define SDMA7_PEWFCOUNTEW_TAG_DEWAY_WANGE__SEWECT_WW_MASK                                                     0x10000000W
//SDMA7_CWD_CNTW
#define SDMA7_CWD_CNTW__MC_WWWEQ_CWEDIT__SHIFT                                                                0x7
#define SDMA7_CWD_CNTW__MC_WDWEQ_CWEDIT__SHIFT                                                                0xd
#define SDMA7_CWD_CNTW__MC_WWWEQ_CWEDIT_MASK                                                                  0x00001F80W
#define SDMA7_CWD_CNTW__MC_WDWEQ_CWEDIT_MASK                                                                  0x0007E000W
//SDMA7_GPU_IOV_VIOWATION_WOG
#define SDMA7_GPU_IOV_VIOWATION_WOG__VIOWATION_STATUS__SHIFT                                                  0x0
#define SDMA7_GPU_IOV_VIOWATION_WOG__MUWTIPWE_VIOWATION_STATUS__SHIFT                                         0x1
#define SDMA7_GPU_IOV_VIOWATION_WOG__ADDWESS__SHIFT                                                           0x2
#define SDMA7_GPU_IOV_VIOWATION_WOG__WWITE_OPEWATION__SHIFT                                                   0x14
#define SDMA7_GPU_IOV_VIOWATION_WOG__VF__SHIFT                                                                0x15
#define SDMA7_GPU_IOV_VIOWATION_WOG__VFID__SHIFT                                                              0x16
#define SDMA7_GPU_IOV_VIOWATION_WOG__VIOWATION_STATUS_MASK                                                    0x00000001W
#define SDMA7_GPU_IOV_VIOWATION_WOG__MUWTIPWE_VIOWATION_STATUS_MASK                                           0x00000002W
#define SDMA7_GPU_IOV_VIOWATION_WOG__ADDWESS_MASK                                                             0x000FFFFCW
#define SDMA7_GPU_IOV_VIOWATION_WOG__WWITE_OPEWATION_MASK                                                     0x00100000W
#define SDMA7_GPU_IOV_VIOWATION_WOG__VF_MASK                                                                  0x00200000W
#define SDMA7_GPU_IOV_VIOWATION_WOG__VFID_MASK                                                                0x03C00000W
//SDMA7_UWV_CNTW
#define SDMA7_UWV_CNTW__HYSTEWESIS__SHIFT                                                                     0x0
#define SDMA7_UWV_CNTW__ENTEW_UWV_INT_CWW__SHIFT                                                              0x1b
#define SDMA7_UWV_CNTW__EXIT_UWV_INT_CWW__SHIFT                                                               0x1c
#define SDMA7_UWV_CNTW__ENTEW_UWV_INT__SHIFT                                                                  0x1d
#define SDMA7_UWV_CNTW__EXIT_UWV_INT__SHIFT                                                                   0x1e
#define SDMA7_UWV_CNTW__UWV_STATUS__SHIFT                                                                     0x1f
#define SDMA7_UWV_CNTW__HYSTEWESIS_MASK                                                                       0x0000001FW
#define SDMA7_UWV_CNTW__ENTEW_UWV_INT_CWW_MASK                                                                0x08000000W
#define SDMA7_UWV_CNTW__EXIT_UWV_INT_CWW_MASK                                                                 0x10000000W
#define SDMA7_UWV_CNTW__ENTEW_UWV_INT_MASK                                                                    0x20000000W
#define SDMA7_UWV_CNTW__EXIT_UWV_INT_MASK                                                                     0x40000000W
#define SDMA7_UWV_CNTW__UWV_STATUS_MASK                                                                       0x80000000W
//SDMA7_EA_DBIT_ADDW_DATA
#define SDMA7_EA_DBIT_ADDW_DATA__VAWUE__SHIFT                                                                 0x0
#define SDMA7_EA_DBIT_ADDW_DATA__VAWUE_MASK                                                                   0xFFFFFFFFW
//SDMA7_EA_DBIT_ADDW_INDEX
#define SDMA7_EA_DBIT_ADDW_INDEX__VAWUE__SHIFT                                                                0x0
#define SDMA7_EA_DBIT_ADDW_INDEX__VAWUE_MASK                                                                  0x00000007W
//SDMA7_GPU_IOV_VIOWATION_WOG2
#define SDMA7_GPU_IOV_VIOWATION_WOG2__INITIATOW_ID__SHIFT                                                     0x0
#define SDMA7_GPU_IOV_VIOWATION_WOG2__INITIATOW_ID_MASK                                                       0x000000FFW
//SDMA7_GFX_WB_CNTW
#define SDMA7_GFX_WB_CNTW__WB_ENABWE__SHIFT                                                                   0x0
#define SDMA7_GFX_WB_CNTW__WB_SIZE__SHIFT                                                                     0x1
#define SDMA7_GFX_WB_CNTW__WB_SWAP_ENABWE__SHIFT                                                              0x9
#define SDMA7_GFX_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT                                                       0xc
#define SDMA7_GFX_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE__SHIFT                                                  0xd
#define SDMA7_GFX_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT                                                        0x10
#define SDMA7_GFX_WB_CNTW__WB_PWIV__SHIFT                                                                     0x17
#define SDMA7_GFX_WB_CNTW__WB_VMID__SHIFT                                                                     0x18
#define SDMA7_GFX_WB_CNTW__WB_ENABWE_MASK                                                                     0x00000001W
#define SDMA7_GFX_WB_CNTW__WB_SIZE_MASK                                                                       0x0000003EW
#define SDMA7_GFX_WB_CNTW__WB_SWAP_ENABWE_MASK                                                                0x00000200W
#define SDMA7_GFX_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK                                                         0x00001000W
#define SDMA7_GFX_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE_MASK                                                    0x00002000W
#define SDMA7_GFX_WB_CNTW__WPTW_WWITEBACK_TIMEW_MASK                                                          0x001F0000W
#define SDMA7_GFX_WB_CNTW__WB_PWIV_MASK                                                                       0x00800000W
#define SDMA7_GFX_WB_CNTW__WB_VMID_MASK                                                                       0x0F000000W
//SDMA7_GFX_WB_BASE
#define SDMA7_GFX_WB_BASE__ADDW__SHIFT                                                                        0x0
#define SDMA7_GFX_WB_BASE__ADDW_MASK                                                                          0xFFFFFFFFW
//SDMA7_GFX_WB_BASE_HI
#define SDMA7_GFX_WB_BASE_HI__ADDW__SHIFT                                                                     0x0
#define SDMA7_GFX_WB_BASE_HI__ADDW_MASK                                                                       0x00FFFFFFW
//SDMA7_GFX_WB_WPTW
#define SDMA7_GFX_WB_WPTW__OFFSET__SHIFT                                                                      0x0
#define SDMA7_GFX_WB_WPTW__OFFSET_MASK                                                                        0xFFFFFFFFW
//SDMA7_GFX_WB_WPTW_HI
#define SDMA7_GFX_WB_WPTW_HI__OFFSET__SHIFT                                                                   0x0
#define SDMA7_GFX_WB_WPTW_HI__OFFSET_MASK                                                                     0xFFFFFFFFW
//SDMA7_GFX_WB_WPTW
#define SDMA7_GFX_WB_WPTW__OFFSET__SHIFT                                                                      0x0
#define SDMA7_GFX_WB_WPTW__OFFSET_MASK                                                                        0xFFFFFFFFW
//SDMA7_GFX_WB_WPTW_HI
#define SDMA7_GFX_WB_WPTW_HI__OFFSET__SHIFT                                                                   0x0
#define SDMA7_GFX_WB_WPTW_HI__OFFSET_MASK                                                                     0xFFFFFFFFW
//SDMA7_GFX_WB_WPTW_POWW_CNTW
#define SDMA7_GFX_WB_WPTW_POWW_CNTW__ENABWE__SHIFT                                                            0x0
#define SDMA7_GFX_WB_WPTW_POWW_CNTW__SWAP_ENABWE__SHIFT                                                       0x1
#define SDMA7_GFX_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE__SHIFT                                                   0x2
#define SDMA7_GFX_WB_WPTW_POWW_CNTW__FWEQUENCY__SHIFT                                                         0x4
#define SDMA7_GFX_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT                                                   0x10
#define SDMA7_GFX_WB_WPTW_POWW_CNTW__ENABWE_MASK                                                              0x00000001W
#define SDMA7_GFX_WB_WPTW_POWW_CNTW__SWAP_ENABWE_MASK                                                         0x00000002W
#define SDMA7_GFX_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE_MASK                                                     0x00000004W
#define SDMA7_GFX_WB_WPTW_POWW_CNTW__FWEQUENCY_MASK                                                           0x0000FFF0W
#define SDMA7_GFX_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT_MASK                                                     0xFFFF0000W
//SDMA7_GFX_WB_WPTW_ADDW_HI
#define SDMA7_GFX_WB_WPTW_ADDW_HI__ADDW__SHIFT                                                                0x0
#define SDMA7_GFX_WB_WPTW_ADDW_HI__ADDW_MASK                                                                  0xFFFFFFFFW
//SDMA7_GFX_WB_WPTW_ADDW_WO
#define SDMA7_GFX_WB_WPTW_ADDW_WO__WPTW_WB_IDWE__SHIFT                                                        0x0
#define SDMA7_GFX_WB_WPTW_ADDW_WO__ADDW__SHIFT                                                                0x2
#define SDMA7_GFX_WB_WPTW_ADDW_WO__WPTW_WB_IDWE_MASK                                                          0x00000001W
#define SDMA7_GFX_WB_WPTW_ADDW_WO__ADDW_MASK                                                                  0xFFFFFFFCW
//SDMA7_GFX_IB_CNTW
#define SDMA7_GFX_IB_CNTW__IB_ENABWE__SHIFT                                                                   0x0
#define SDMA7_GFX_IB_CNTW__IB_SWAP_ENABWE__SHIFT                                                              0x4
#define SDMA7_GFX_IB_CNTW__SWITCH_INSIDE_IB__SHIFT                                                            0x8
#define SDMA7_GFX_IB_CNTW__CMD_VMID__SHIFT                                                                    0x10
#define SDMA7_GFX_IB_CNTW__IB_ENABWE_MASK                                                                     0x00000001W
#define SDMA7_GFX_IB_CNTW__IB_SWAP_ENABWE_MASK                                                                0x00000010W
#define SDMA7_GFX_IB_CNTW__SWITCH_INSIDE_IB_MASK                                                              0x00000100W
#define SDMA7_GFX_IB_CNTW__CMD_VMID_MASK                                                                      0x000F0000W
//SDMA7_GFX_IB_WPTW
#define SDMA7_GFX_IB_WPTW__OFFSET__SHIFT                                                                      0x2
#define SDMA7_GFX_IB_WPTW__OFFSET_MASK                                                                        0x003FFFFCW
//SDMA7_GFX_IB_OFFSET
#define SDMA7_GFX_IB_OFFSET__OFFSET__SHIFT                                                                    0x2
#define SDMA7_GFX_IB_OFFSET__OFFSET_MASK                                                                      0x003FFFFCW
//SDMA7_GFX_IB_BASE_WO
#define SDMA7_GFX_IB_BASE_WO__ADDW__SHIFT                                                                     0x5
#define SDMA7_GFX_IB_BASE_WO__ADDW_MASK                                                                       0xFFFFFFE0W
//SDMA7_GFX_IB_BASE_HI
#define SDMA7_GFX_IB_BASE_HI__ADDW__SHIFT                                                                     0x0
#define SDMA7_GFX_IB_BASE_HI__ADDW_MASK                                                                       0xFFFFFFFFW
//SDMA7_GFX_IB_SIZE
#define SDMA7_GFX_IB_SIZE__SIZE__SHIFT                                                                        0x0
#define SDMA7_GFX_IB_SIZE__SIZE_MASK                                                                          0x000FFFFFW
//SDMA7_GFX_SKIP_CNTW
#define SDMA7_GFX_SKIP_CNTW__SKIP_COUNT__SHIFT                                                                0x0
#define SDMA7_GFX_SKIP_CNTW__SKIP_COUNT_MASK                                                                  0x000FFFFFW
//SDMA7_GFX_CONTEXT_STATUS
#define SDMA7_GFX_CONTEXT_STATUS__SEWECTED__SHIFT                                                             0x0
#define SDMA7_GFX_CONTEXT_STATUS__IDWE__SHIFT                                                                 0x2
#define SDMA7_GFX_CONTEXT_STATUS__EXPIWED__SHIFT                                                              0x3
#define SDMA7_GFX_CONTEXT_STATUS__EXCEPTION__SHIFT                                                            0x4
#define SDMA7_GFX_CONTEXT_STATUS__CTXSW_ABWE__SHIFT                                                           0x7
#define SDMA7_GFX_CONTEXT_STATUS__CTXSW_WEADY__SHIFT                                                          0x8
#define SDMA7_GFX_CONTEXT_STATUS__PWEEMPTED__SHIFT                                                            0x9
#define SDMA7_GFX_CONTEXT_STATUS__PWEEMPT_DISABWE__SHIFT                                                      0xa
#define SDMA7_GFX_CONTEXT_STATUS__SEWECTED_MASK                                                               0x00000001W
#define SDMA7_GFX_CONTEXT_STATUS__IDWE_MASK                                                                   0x00000004W
#define SDMA7_GFX_CONTEXT_STATUS__EXPIWED_MASK                                                                0x00000008W
#define SDMA7_GFX_CONTEXT_STATUS__EXCEPTION_MASK                                                              0x00000070W
#define SDMA7_GFX_CONTEXT_STATUS__CTXSW_ABWE_MASK                                                             0x00000080W
#define SDMA7_GFX_CONTEXT_STATUS__CTXSW_WEADY_MASK                                                            0x00000100W
#define SDMA7_GFX_CONTEXT_STATUS__PWEEMPTED_MASK                                                              0x00000200W
#define SDMA7_GFX_CONTEXT_STATUS__PWEEMPT_DISABWE_MASK                                                        0x00000400W
//SDMA7_GFX_DOOWBEWW
#define SDMA7_GFX_DOOWBEWW__ENABWE__SHIFT                                                                     0x1c
#define SDMA7_GFX_DOOWBEWW__CAPTUWED__SHIFT                                                                   0x1e
#define SDMA7_GFX_DOOWBEWW__ENABWE_MASK                                                                       0x10000000W
#define SDMA7_GFX_DOOWBEWW__CAPTUWED_MASK                                                                     0x40000000W
//SDMA7_GFX_CONTEXT_CNTW
#define SDMA7_GFX_CONTEXT_CNTW__WESUME_CTX__SHIFT                                                             0x10
#define SDMA7_GFX_CONTEXT_CNTW__WESUME_CTX_MASK                                                               0x00010000W
//SDMA7_GFX_STATUS
#define SDMA7_GFX_STATUS__WPTW_UPDATE_FAIW_COUNT__SHIFT                                                       0x0
#define SDMA7_GFX_STATUS__WPTW_UPDATE_PENDING__SHIFT                                                          0x8
#define SDMA7_GFX_STATUS__WPTW_UPDATE_FAIW_COUNT_MASK                                                         0x000000FFW
#define SDMA7_GFX_STATUS__WPTW_UPDATE_PENDING_MASK                                                            0x00000100W
//SDMA7_GFX_DOOWBEWW_WOG
#define SDMA7_GFX_DOOWBEWW_WOG__BE_EWWOW__SHIFT                                                               0x0
#define SDMA7_GFX_DOOWBEWW_WOG__DATA__SHIFT                                                                   0x2
#define SDMA7_GFX_DOOWBEWW_WOG__BE_EWWOW_MASK                                                                 0x00000001W
#define SDMA7_GFX_DOOWBEWW_WOG__DATA_MASK                                                                     0xFFFFFFFCW
//SDMA7_GFX_WATEWMAWK
#define SDMA7_GFX_WATEWMAWK__WD_OUTSTANDING__SHIFT                                                            0x0
#define SDMA7_GFX_WATEWMAWK__WW_OUTSTANDING__SHIFT                                                            0x10
#define SDMA7_GFX_WATEWMAWK__WD_OUTSTANDING_MASK                                                              0x00000FFFW
#define SDMA7_GFX_WATEWMAWK__WW_OUTSTANDING_MASK                                                              0x03FF0000W
//SDMA7_GFX_DOOWBEWW_OFFSET
#define SDMA7_GFX_DOOWBEWW_OFFSET__OFFSET__SHIFT                                                              0x2
#define SDMA7_GFX_DOOWBEWW_OFFSET__OFFSET_MASK                                                                0x0FFFFFFCW
//SDMA7_GFX_CSA_ADDW_WO
#define SDMA7_GFX_CSA_ADDW_WO__ADDW__SHIFT                                                                    0x2
#define SDMA7_GFX_CSA_ADDW_WO__ADDW_MASK                                                                      0xFFFFFFFCW
//SDMA7_GFX_CSA_ADDW_HI
#define SDMA7_GFX_CSA_ADDW_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_GFX_CSA_ADDW_HI__ADDW_MASK                                                                      0xFFFFFFFFW
//SDMA7_GFX_IB_SUB_WEMAIN
#define SDMA7_GFX_IB_SUB_WEMAIN__SIZE__SHIFT                                                                  0x0
#define SDMA7_GFX_IB_SUB_WEMAIN__SIZE_MASK                                                                    0x000FFFFFW
//SDMA7_GFX_PWEEMPT
#define SDMA7_GFX_PWEEMPT__IB_PWEEMPT__SHIFT                                                                  0x0
#define SDMA7_GFX_PWEEMPT__IB_PWEEMPT_MASK                                                                    0x00000001W
//SDMA7_GFX_DUMMY_WEG
#define SDMA7_GFX_DUMMY_WEG__DUMMY__SHIFT                                                                     0x0
#define SDMA7_GFX_DUMMY_WEG__DUMMY_MASK                                                                       0xFFFFFFFFW
//SDMA7_GFX_WB_WPTW_POWW_ADDW_HI
#define SDMA7_GFX_WB_WPTW_POWW_ADDW_HI__ADDW__SHIFT                                                           0x0
#define SDMA7_GFX_WB_WPTW_POWW_ADDW_HI__ADDW_MASK                                                             0xFFFFFFFFW
//SDMA7_GFX_WB_WPTW_POWW_ADDW_WO
#define SDMA7_GFX_WB_WPTW_POWW_ADDW_WO__ADDW__SHIFT                                                           0x2
#define SDMA7_GFX_WB_WPTW_POWW_ADDW_WO__ADDW_MASK                                                             0xFFFFFFFCW
//SDMA7_GFX_WB_AQW_CNTW
#define SDMA7_GFX_WB_AQW_CNTW__AQW_ENABWE__SHIFT                                                              0x0
#define SDMA7_GFX_WB_AQW_CNTW__AQW_PACKET_SIZE__SHIFT                                                         0x1
#define SDMA7_GFX_WB_AQW_CNTW__PACKET_STEP__SHIFT                                                             0x8
#define SDMA7_GFX_WB_AQW_CNTW__AQW_ENABWE_MASK                                                                0x00000001W
#define SDMA7_GFX_WB_AQW_CNTW__AQW_PACKET_SIZE_MASK                                                           0x000000FEW
#define SDMA7_GFX_WB_AQW_CNTW__PACKET_STEP_MASK                                                               0x0000FF00W
//SDMA7_GFX_MINOW_PTW_UPDATE
#define SDMA7_GFX_MINOW_PTW_UPDATE__ENABWE__SHIFT                                                             0x0
#define SDMA7_GFX_MINOW_PTW_UPDATE__ENABWE_MASK                                                               0x00000001W
//SDMA7_GFX_MIDCMD_DATA0
#define SDMA7_GFX_MIDCMD_DATA0__DATA0__SHIFT                                                                  0x0
#define SDMA7_GFX_MIDCMD_DATA0__DATA0_MASK                                                                    0xFFFFFFFFW
//SDMA7_GFX_MIDCMD_DATA1
#define SDMA7_GFX_MIDCMD_DATA1__DATA1__SHIFT                                                                  0x0
#define SDMA7_GFX_MIDCMD_DATA1__DATA1_MASK                                                                    0xFFFFFFFFW
//SDMA7_GFX_MIDCMD_DATA2
#define SDMA7_GFX_MIDCMD_DATA2__DATA2__SHIFT                                                                  0x0
#define SDMA7_GFX_MIDCMD_DATA2__DATA2_MASK                                                                    0xFFFFFFFFW
//SDMA7_GFX_MIDCMD_DATA3
#define SDMA7_GFX_MIDCMD_DATA3__DATA3__SHIFT                                                                  0x0
#define SDMA7_GFX_MIDCMD_DATA3__DATA3_MASK                                                                    0xFFFFFFFFW
//SDMA7_GFX_MIDCMD_DATA4
#define SDMA7_GFX_MIDCMD_DATA4__DATA4__SHIFT                                                                  0x0
#define SDMA7_GFX_MIDCMD_DATA4__DATA4_MASK                                                                    0xFFFFFFFFW
//SDMA7_GFX_MIDCMD_DATA5
#define SDMA7_GFX_MIDCMD_DATA5__DATA5__SHIFT                                                                  0x0
#define SDMA7_GFX_MIDCMD_DATA5__DATA5_MASK                                                                    0xFFFFFFFFW
//SDMA7_GFX_MIDCMD_DATA6
#define SDMA7_GFX_MIDCMD_DATA6__DATA6__SHIFT                                                                  0x0
#define SDMA7_GFX_MIDCMD_DATA6__DATA6_MASK                                                                    0xFFFFFFFFW
//SDMA7_GFX_MIDCMD_DATA7
#define SDMA7_GFX_MIDCMD_DATA7__DATA7__SHIFT                                                                  0x0
#define SDMA7_GFX_MIDCMD_DATA7__DATA7_MASK                                                                    0xFFFFFFFFW
//SDMA7_GFX_MIDCMD_DATA8
#define SDMA7_GFX_MIDCMD_DATA8__DATA8__SHIFT                                                                  0x0
#define SDMA7_GFX_MIDCMD_DATA8__DATA8_MASK                                                                    0xFFFFFFFFW
//SDMA7_GFX_MIDCMD_CNTW
#define SDMA7_GFX_MIDCMD_CNTW__DATA_VAWID__SHIFT                                                              0x0
#define SDMA7_GFX_MIDCMD_CNTW__COPY_MODE__SHIFT                                                               0x1
#define SDMA7_GFX_MIDCMD_CNTW__SPWIT_STATE__SHIFT                                                             0x4
#define SDMA7_GFX_MIDCMD_CNTW__AWWOW_PWEEMPT__SHIFT                                                           0x8
#define SDMA7_GFX_MIDCMD_CNTW__DATA_VAWID_MASK                                                                0x00000001W
#define SDMA7_GFX_MIDCMD_CNTW__COPY_MODE_MASK                                                                 0x00000002W
#define SDMA7_GFX_MIDCMD_CNTW__SPWIT_STATE_MASK                                                               0x000000F0W
#define SDMA7_GFX_MIDCMD_CNTW__AWWOW_PWEEMPT_MASK                                                             0x00000100W
//SDMA7_PAGE_WB_CNTW
#define SDMA7_PAGE_WB_CNTW__WB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_PAGE_WB_CNTW__WB_SIZE__SHIFT                                                                    0x1
#define SDMA7_PAGE_WB_CNTW__WB_SWAP_ENABWE__SHIFT                                                             0x9
#define SDMA7_PAGE_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT                                                      0xc
#define SDMA7_PAGE_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE__SHIFT                                                 0xd
#define SDMA7_PAGE_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT                                                       0x10
#define SDMA7_PAGE_WB_CNTW__WB_PWIV__SHIFT                                                                    0x17
#define SDMA7_PAGE_WB_CNTW__WB_VMID__SHIFT                                                                    0x18
#define SDMA7_PAGE_WB_CNTW__WB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_PAGE_WB_CNTW__WB_SIZE_MASK                                                                      0x0000003EW
#define SDMA7_PAGE_WB_CNTW__WB_SWAP_ENABWE_MASK                                                               0x00000200W
#define SDMA7_PAGE_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK                                                        0x00001000W
#define SDMA7_PAGE_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE_MASK                                                   0x00002000W
#define SDMA7_PAGE_WB_CNTW__WPTW_WWITEBACK_TIMEW_MASK                                                         0x001F0000W
#define SDMA7_PAGE_WB_CNTW__WB_PWIV_MASK                                                                      0x00800000W
#define SDMA7_PAGE_WB_CNTW__WB_VMID_MASK                                                                      0x0F000000W
//SDMA7_PAGE_WB_BASE
#define SDMA7_PAGE_WB_BASE__ADDW__SHIFT                                                                       0x0
#define SDMA7_PAGE_WB_BASE__ADDW_MASK                                                                         0xFFFFFFFFW
//SDMA7_PAGE_WB_BASE_HI
#define SDMA7_PAGE_WB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_PAGE_WB_BASE_HI__ADDW_MASK                                                                      0x00FFFFFFW
//SDMA7_PAGE_WB_WPTW
#define SDMA7_PAGE_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_PAGE_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_PAGE_WB_WPTW_HI
#define SDMA7_PAGE_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_PAGE_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_PAGE_WB_WPTW
#define SDMA7_PAGE_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_PAGE_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_PAGE_WB_WPTW_HI
#define SDMA7_PAGE_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_PAGE_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_PAGE_WB_WPTW_POWW_CNTW
#define SDMA7_PAGE_WB_WPTW_POWW_CNTW__ENABWE__SHIFT                                                           0x0
#define SDMA7_PAGE_WB_WPTW_POWW_CNTW__SWAP_ENABWE__SHIFT                                                      0x1
#define SDMA7_PAGE_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE__SHIFT                                                  0x2
#define SDMA7_PAGE_WB_WPTW_POWW_CNTW__FWEQUENCY__SHIFT                                                        0x4
#define SDMA7_PAGE_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT                                                  0x10
#define SDMA7_PAGE_WB_WPTW_POWW_CNTW__ENABWE_MASK                                                             0x00000001W
#define SDMA7_PAGE_WB_WPTW_POWW_CNTW__SWAP_ENABWE_MASK                                                        0x00000002W
#define SDMA7_PAGE_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE_MASK                                                    0x00000004W
#define SDMA7_PAGE_WB_WPTW_POWW_CNTW__FWEQUENCY_MASK                                                          0x0000FFF0W
#define SDMA7_PAGE_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT_MASK                                                    0xFFFF0000W
//SDMA7_PAGE_WB_WPTW_ADDW_HI
#define SDMA7_PAGE_WB_WPTW_ADDW_HI__ADDW__SHIFT                                                               0x0
#define SDMA7_PAGE_WB_WPTW_ADDW_HI__ADDW_MASK                                                                 0xFFFFFFFFW
//SDMA7_PAGE_WB_WPTW_ADDW_WO
#define SDMA7_PAGE_WB_WPTW_ADDW_WO__WPTW_WB_IDWE__SHIFT                                                       0x0
#define SDMA7_PAGE_WB_WPTW_ADDW_WO__ADDW__SHIFT                                                               0x2
#define SDMA7_PAGE_WB_WPTW_ADDW_WO__WPTW_WB_IDWE_MASK                                                         0x00000001W
#define SDMA7_PAGE_WB_WPTW_ADDW_WO__ADDW_MASK                                                                 0xFFFFFFFCW
//SDMA7_PAGE_IB_CNTW
#define SDMA7_PAGE_IB_CNTW__IB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_PAGE_IB_CNTW__IB_SWAP_ENABWE__SHIFT                                                             0x4
#define SDMA7_PAGE_IB_CNTW__SWITCH_INSIDE_IB__SHIFT                                                           0x8
#define SDMA7_PAGE_IB_CNTW__CMD_VMID__SHIFT                                                                   0x10
#define SDMA7_PAGE_IB_CNTW__IB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_PAGE_IB_CNTW__IB_SWAP_ENABWE_MASK                                                               0x00000010W
#define SDMA7_PAGE_IB_CNTW__SWITCH_INSIDE_IB_MASK                                                             0x00000100W
#define SDMA7_PAGE_IB_CNTW__CMD_VMID_MASK                                                                     0x000F0000W
//SDMA7_PAGE_IB_WPTW
#define SDMA7_PAGE_IB_WPTW__OFFSET__SHIFT                                                                     0x2
#define SDMA7_PAGE_IB_WPTW__OFFSET_MASK                                                                       0x003FFFFCW
//SDMA7_PAGE_IB_OFFSET
#define SDMA7_PAGE_IB_OFFSET__OFFSET__SHIFT                                                                   0x2
#define SDMA7_PAGE_IB_OFFSET__OFFSET_MASK                                                                     0x003FFFFCW
//SDMA7_PAGE_IB_BASE_WO
#define SDMA7_PAGE_IB_BASE_WO__ADDW__SHIFT                                                                    0x5
#define SDMA7_PAGE_IB_BASE_WO__ADDW_MASK                                                                      0xFFFFFFE0W
//SDMA7_PAGE_IB_BASE_HI
#define SDMA7_PAGE_IB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_PAGE_IB_BASE_HI__ADDW_MASK                                                                      0xFFFFFFFFW
//SDMA7_PAGE_IB_SIZE
#define SDMA7_PAGE_IB_SIZE__SIZE__SHIFT                                                                       0x0
#define SDMA7_PAGE_IB_SIZE__SIZE_MASK                                                                         0x000FFFFFW
//SDMA7_PAGE_SKIP_CNTW
#define SDMA7_PAGE_SKIP_CNTW__SKIP_COUNT__SHIFT                                                               0x0
#define SDMA7_PAGE_SKIP_CNTW__SKIP_COUNT_MASK                                                                 0x000FFFFFW
//SDMA7_PAGE_CONTEXT_STATUS
#define SDMA7_PAGE_CONTEXT_STATUS__SEWECTED__SHIFT                                                            0x0
#define SDMA7_PAGE_CONTEXT_STATUS__IDWE__SHIFT                                                                0x2
#define SDMA7_PAGE_CONTEXT_STATUS__EXPIWED__SHIFT                                                             0x3
#define SDMA7_PAGE_CONTEXT_STATUS__EXCEPTION__SHIFT                                                           0x4
#define SDMA7_PAGE_CONTEXT_STATUS__CTXSW_ABWE__SHIFT                                                          0x7
#define SDMA7_PAGE_CONTEXT_STATUS__CTXSW_WEADY__SHIFT                                                         0x8
#define SDMA7_PAGE_CONTEXT_STATUS__PWEEMPTED__SHIFT                                                           0x9
#define SDMA7_PAGE_CONTEXT_STATUS__PWEEMPT_DISABWE__SHIFT                                                     0xa
#define SDMA7_PAGE_CONTEXT_STATUS__SEWECTED_MASK                                                              0x00000001W
#define SDMA7_PAGE_CONTEXT_STATUS__IDWE_MASK                                                                  0x00000004W
#define SDMA7_PAGE_CONTEXT_STATUS__EXPIWED_MASK                                                               0x00000008W
#define SDMA7_PAGE_CONTEXT_STATUS__EXCEPTION_MASK                                                             0x00000070W
#define SDMA7_PAGE_CONTEXT_STATUS__CTXSW_ABWE_MASK                                                            0x00000080W
#define SDMA7_PAGE_CONTEXT_STATUS__CTXSW_WEADY_MASK                                                           0x00000100W
#define SDMA7_PAGE_CONTEXT_STATUS__PWEEMPTED_MASK                                                             0x00000200W
#define SDMA7_PAGE_CONTEXT_STATUS__PWEEMPT_DISABWE_MASK                                                       0x00000400W
//SDMA7_PAGE_DOOWBEWW
#define SDMA7_PAGE_DOOWBEWW__ENABWE__SHIFT                                                                    0x1c
#define SDMA7_PAGE_DOOWBEWW__CAPTUWED__SHIFT                                                                  0x1e
#define SDMA7_PAGE_DOOWBEWW__ENABWE_MASK                                                                      0x10000000W
#define SDMA7_PAGE_DOOWBEWW__CAPTUWED_MASK                                                                    0x40000000W
//SDMA7_PAGE_STATUS
#define SDMA7_PAGE_STATUS__WPTW_UPDATE_FAIW_COUNT__SHIFT                                                      0x0
#define SDMA7_PAGE_STATUS__WPTW_UPDATE_PENDING__SHIFT                                                         0x8
#define SDMA7_PAGE_STATUS__WPTW_UPDATE_FAIW_COUNT_MASK                                                        0x000000FFW
#define SDMA7_PAGE_STATUS__WPTW_UPDATE_PENDING_MASK                                                           0x00000100W
//SDMA7_PAGE_DOOWBEWW_WOG
#define SDMA7_PAGE_DOOWBEWW_WOG__BE_EWWOW__SHIFT                                                              0x0
#define SDMA7_PAGE_DOOWBEWW_WOG__DATA__SHIFT                                                                  0x2
#define SDMA7_PAGE_DOOWBEWW_WOG__BE_EWWOW_MASK                                                                0x00000001W
#define SDMA7_PAGE_DOOWBEWW_WOG__DATA_MASK                                                                    0xFFFFFFFCW
//SDMA7_PAGE_WATEWMAWK
#define SDMA7_PAGE_WATEWMAWK__WD_OUTSTANDING__SHIFT                                                           0x0
#define SDMA7_PAGE_WATEWMAWK__WW_OUTSTANDING__SHIFT                                                           0x10
#define SDMA7_PAGE_WATEWMAWK__WD_OUTSTANDING_MASK                                                             0x00000FFFW
#define SDMA7_PAGE_WATEWMAWK__WW_OUTSTANDING_MASK                                                             0x03FF0000W
//SDMA7_PAGE_DOOWBEWW_OFFSET
#define SDMA7_PAGE_DOOWBEWW_OFFSET__OFFSET__SHIFT                                                             0x2
#define SDMA7_PAGE_DOOWBEWW_OFFSET__OFFSET_MASK                                                               0x0FFFFFFCW
//SDMA7_PAGE_CSA_ADDW_WO
#define SDMA7_PAGE_CSA_ADDW_WO__ADDW__SHIFT                                                                   0x2
#define SDMA7_PAGE_CSA_ADDW_WO__ADDW_MASK                                                                     0xFFFFFFFCW
//SDMA7_PAGE_CSA_ADDW_HI
#define SDMA7_PAGE_CSA_ADDW_HI__ADDW__SHIFT                                                                   0x0
#define SDMA7_PAGE_CSA_ADDW_HI__ADDW_MASK                                                                     0xFFFFFFFFW
//SDMA7_PAGE_IB_SUB_WEMAIN
#define SDMA7_PAGE_IB_SUB_WEMAIN__SIZE__SHIFT                                                                 0x0
#define SDMA7_PAGE_IB_SUB_WEMAIN__SIZE_MASK                                                                   0x000FFFFFW
//SDMA7_PAGE_PWEEMPT
#define SDMA7_PAGE_PWEEMPT__IB_PWEEMPT__SHIFT                                                                 0x0
#define SDMA7_PAGE_PWEEMPT__IB_PWEEMPT_MASK                                                                   0x00000001W
//SDMA7_PAGE_DUMMY_WEG
#define SDMA7_PAGE_DUMMY_WEG__DUMMY__SHIFT                                                                    0x0
#define SDMA7_PAGE_DUMMY_WEG__DUMMY_MASK                                                                      0xFFFFFFFFW
//SDMA7_PAGE_WB_WPTW_POWW_ADDW_HI
#define SDMA7_PAGE_WB_WPTW_POWW_ADDW_HI__ADDW__SHIFT                                                          0x0
#define SDMA7_PAGE_WB_WPTW_POWW_ADDW_HI__ADDW_MASK                                                            0xFFFFFFFFW
//SDMA7_PAGE_WB_WPTW_POWW_ADDW_WO
#define SDMA7_PAGE_WB_WPTW_POWW_ADDW_WO__ADDW__SHIFT                                                          0x2
#define SDMA7_PAGE_WB_WPTW_POWW_ADDW_WO__ADDW_MASK                                                            0xFFFFFFFCW
//SDMA7_PAGE_WB_AQW_CNTW
#define SDMA7_PAGE_WB_AQW_CNTW__AQW_ENABWE__SHIFT                                                             0x0
#define SDMA7_PAGE_WB_AQW_CNTW__AQW_PACKET_SIZE__SHIFT                                                        0x1
#define SDMA7_PAGE_WB_AQW_CNTW__PACKET_STEP__SHIFT                                                            0x8
#define SDMA7_PAGE_WB_AQW_CNTW__AQW_ENABWE_MASK                                                               0x00000001W
#define SDMA7_PAGE_WB_AQW_CNTW__AQW_PACKET_SIZE_MASK                                                          0x000000FEW
#define SDMA7_PAGE_WB_AQW_CNTW__PACKET_STEP_MASK                                                              0x0000FF00W
//SDMA7_PAGE_MINOW_PTW_UPDATE
#define SDMA7_PAGE_MINOW_PTW_UPDATE__ENABWE__SHIFT                                                            0x0
#define SDMA7_PAGE_MINOW_PTW_UPDATE__ENABWE_MASK                                                              0x00000001W
//SDMA7_PAGE_MIDCMD_DATA0
#define SDMA7_PAGE_MIDCMD_DATA0__DATA0__SHIFT                                                                 0x0
#define SDMA7_PAGE_MIDCMD_DATA0__DATA0_MASK                                                                   0xFFFFFFFFW
//SDMA7_PAGE_MIDCMD_DATA1
#define SDMA7_PAGE_MIDCMD_DATA1__DATA1__SHIFT                                                                 0x0
#define SDMA7_PAGE_MIDCMD_DATA1__DATA1_MASK                                                                   0xFFFFFFFFW
//SDMA7_PAGE_MIDCMD_DATA2
#define SDMA7_PAGE_MIDCMD_DATA2__DATA2__SHIFT                                                                 0x0
#define SDMA7_PAGE_MIDCMD_DATA2__DATA2_MASK                                                                   0xFFFFFFFFW
//SDMA7_PAGE_MIDCMD_DATA3
#define SDMA7_PAGE_MIDCMD_DATA3__DATA3__SHIFT                                                                 0x0
#define SDMA7_PAGE_MIDCMD_DATA3__DATA3_MASK                                                                   0xFFFFFFFFW
//SDMA7_PAGE_MIDCMD_DATA4
#define SDMA7_PAGE_MIDCMD_DATA4__DATA4__SHIFT                                                                 0x0
#define SDMA7_PAGE_MIDCMD_DATA4__DATA4_MASK                                                                   0xFFFFFFFFW
//SDMA7_PAGE_MIDCMD_DATA5
#define SDMA7_PAGE_MIDCMD_DATA5__DATA5__SHIFT                                                                 0x0
#define SDMA7_PAGE_MIDCMD_DATA5__DATA5_MASK                                                                   0xFFFFFFFFW
//SDMA7_PAGE_MIDCMD_DATA6
#define SDMA7_PAGE_MIDCMD_DATA6__DATA6__SHIFT                                                                 0x0
#define SDMA7_PAGE_MIDCMD_DATA6__DATA6_MASK                                                                   0xFFFFFFFFW
//SDMA7_PAGE_MIDCMD_DATA7
#define SDMA7_PAGE_MIDCMD_DATA7__DATA7__SHIFT                                                                 0x0
#define SDMA7_PAGE_MIDCMD_DATA7__DATA7_MASK                                                                   0xFFFFFFFFW
//SDMA7_PAGE_MIDCMD_DATA8
#define SDMA7_PAGE_MIDCMD_DATA8__DATA8__SHIFT                                                                 0x0
#define SDMA7_PAGE_MIDCMD_DATA8__DATA8_MASK                                                                   0xFFFFFFFFW
//SDMA7_PAGE_MIDCMD_CNTW
#define SDMA7_PAGE_MIDCMD_CNTW__DATA_VAWID__SHIFT                                                             0x0
#define SDMA7_PAGE_MIDCMD_CNTW__COPY_MODE__SHIFT                                                              0x1
#define SDMA7_PAGE_MIDCMD_CNTW__SPWIT_STATE__SHIFT                                                            0x4
#define SDMA7_PAGE_MIDCMD_CNTW__AWWOW_PWEEMPT__SHIFT                                                          0x8
#define SDMA7_PAGE_MIDCMD_CNTW__DATA_VAWID_MASK                                                               0x00000001W
#define SDMA7_PAGE_MIDCMD_CNTW__COPY_MODE_MASK                                                                0x00000002W
#define SDMA7_PAGE_MIDCMD_CNTW__SPWIT_STATE_MASK                                                              0x000000F0W
#define SDMA7_PAGE_MIDCMD_CNTW__AWWOW_PWEEMPT_MASK                                                            0x00000100W
//SDMA7_WWC0_WB_CNTW
#define SDMA7_WWC0_WB_CNTW__WB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC0_WB_CNTW__WB_SIZE__SHIFT                                                                    0x1
#define SDMA7_WWC0_WB_CNTW__WB_SWAP_ENABWE__SHIFT                                                             0x9
#define SDMA7_WWC0_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT                                                      0xc
#define SDMA7_WWC0_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE__SHIFT                                                 0xd
#define SDMA7_WWC0_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT                                                       0x10
#define SDMA7_WWC0_WB_CNTW__WB_PWIV__SHIFT                                                                    0x17
#define SDMA7_WWC0_WB_CNTW__WB_VMID__SHIFT                                                                    0x18
#define SDMA7_WWC0_WB_CNTW__WB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC0_WB_CNTW__WB_SIZE_MASK                                                                      0x0000003EW
#define SDMA7_WWC0_WB_CNTW__WB_SWAP_ENABWE_MASK                                                               0x00000200W
#define SDMA7_WWC0_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK                                                        0x00001000W
#define SDMA7_WWC0_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE_MASK                                                   0x00002000W
#define SDMA7_WWC0_WB_CNTW__WPTW_WWITEBACK_TIMEW_MASK                                                         0x001F0000W
#define SDMA7_WWC0_WB_CNTW__WB_PWIV_MASK                                                                      0x00800000W
#define SDMA7_WWC0_WB_CNTW__WB_VMID_MASK                                                                      0x0F000000W
//SDMA7_WWC0_WB_BASE
#define SDMA7_WWC0_WB_BASE__ADDW__SHIFT                                                                       0x0
#define SDMA7_WWC0_WB_BASE__ADDW_MASK                                                                         0xFFFFFFFFW
//SDMA7_WWC0_WB_BASE_HI
#define SDMA7_WWC0_WB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC0_WB_BASE_HI__ADDW_MASK                                                                      0x00FFFFFFW
//SDMA7_WWC0_WB_WPTW
#define SDMA7_WWC0_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC0_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC0_WB_WPTW_HI
#define SDMA7_WWC0_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC0_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC0_WB_WPTW
#define SDMA7_WWC0_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC0_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC0_WB_WPTW_HI
#define SDMA7_WWC0_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC0_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC0_WB_WPTW_POWW_CNTW
#define SDMA7_WWC0_WB_WPTW_POWW_CNTW__ENABWE__SHIFT                                                           0x0
#define SDMA7_WWC0_WB_WPTW_POWW_CNTW__SWAP_ENABWE__SHIFT                                                      0x1
#define SDMA7_WWC0_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE__SHIFT                                                  0x2
#define SDMA7_WWC0_WB_WPTW_POWW_CNTW__FWEQUENCY__SHIFT                                                        0x4
#define SDMA7_WWC0_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT                                                  0x10
#define SDMA7_WWC0_WB_WPTW_POWW_CNTW__ENABWE_MASK                                                             0x00000001W
#define SDMA7_WWC0_WB_WPTW_POWW_CNTW__SWAP_ENABWE_MASK                                                        0x00000002W
#define SDMA7_WWC0_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE_MASK                                                    0x00000004W
#define SDMA7_WWC0_WB_WPTW_POWW_CNTW__FWEQUENCY_MASK                                                          0x0000FFF0W
#define SDMA7_WWC0_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT_MASK                                                    0xFFFF0000W
//SDMA7_WWC0_WB_WPTW_ADDW_HI
#define SDMA7_WWC0_WB_WPTW_ADDW_HI__ADDW__SHIFT                                                               0x0
#define SDMA7_WWC0_WB_WPTW_ADDW_HI__ADDW_MASK                                                                 0xFFFFFFFFW
//SDMA7_WWC0_WB_WPTW_ADDW_WO
#define SDMA7_WWC0_WB_WPTW_ADDW_WO__WPTW_WB_IDWE__SHIFT                                                       0x0
#define SDMA7_WWC0_WB_WPTW_ADDW_WO__ADDW__SHIFT                                                               0x2
#define SDMA7_WWC0_WB_WPTW_ADDW_WO__WPTW_WB_IDWE_MASK                                                         0x00000001W
#define SDMA7_WWC0_WB_WPTW_ADDW_WO__ADDW_MASK                                                                 0xFFFFFFFCW
//SDMA7_WWC0_IB_CNTW
#define SDMA7_WWC0_IB_CNTW__IB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC0_IB_CNTW__IB_SWAP_ENABWE__SHIFT                                                             0x4
#define SDMA7_WWC0_IB_CNTW__SWITCH_INSIDE_IB__SHIFT                                                           0x8
#define SDMA7_WWC0_IB_CNTW__CMD_VMID__SHIFT                                                                   0x10
#define SDMA7_WWC0_IB_CNTW__IB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC0_IB_CNTW__IB_SWAP_ENABWE_MASK                                                               0x00000010W
#define SDMA7_WWC0_IB_CNTW__SWITCH_INSIDE_IB_MASK                                                             0x00000100W
#define SDMA7_WWC0_IB_CNTW__CMD_VMID_MASK                                                                     0x000F0000W
//SDMA7_WWC0_IB_WPTW
#define SDMA7_WWC0_IB_WPTW__OFFSET__SHIFT                                                                     0x2
#define SDMA7_WWC0_IB_WPTW__OFFSET_MASK                                                                       0x003FFFFCW
//SDMA7_WWC0_IB_OFFSET
#define SDMA7_WWC0_IB_OFFSET__OFFSET__SHIFT                                                                   0x2
#define SDMA7_WWC0_IB_OFFSET__OFFSET_MASK                                                                     0x003FFFFCW
//SDMA7_WWC0_IB_BASE_WO
#define SDMA7_WWC0_IB_BASE_WO__ADDW__SHIFT                                                                    0x5
#define SDMA7_WWC0_IB_BASE_WO__ADDW_MASK                                                                      0xFFFFFFE0W
//SDMA7_WWC0_IB_BASE_HI
#define SDMA7_WWC0_IB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC0_IB_BASE_HI__ADDW_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC0_IB_SIZE
#define SDMA7_WWC0_IB_SIZE__SIZE__SHIFT                                                                       0x0
#define SDMA7_WWC0_IB_SIZE__SIZE_MASK                                                                         0x000FFFFFW
//SDMA7_WWC0_SKIP_CNTW
#define SDMA7_WWC0_SKIP_CNTW__SKIP_COUNT__SHIFT                                                               0x0
#define SDMA7_WWC0_SKIP_CNTW__SKIP_COUNT_MASK                                                                 0x000FFFFFW
//SDMA7_WWC0_CONTEXT_STATUS
#define SDMA7_WWC0_CONTEXT_STATUS__SEWECTED__SHIFT                                                            0x0
#define SDMA7_WWC0_CONTEXT_STATUS__IDWE__SHIFT                                                                0x2
#define SDMA7_WWC0_CONTEXT_STATUS__EXPIWED__SHIFT                                                             0x3
#define SDMA7_WWC0_CONTEXT_STATUS__EXCEPTION__SHIFT                                                           0x4
#define SDMA7_WWC0_CONTEXT_STATUS__CTXSW_ABWE__SHIFT                                                          0x7
#define SDMA7_WWC0_CONTEXT_STATUS__CTXSW_WEADY__SHIFT                                                         0x8
#define SDMA7_WWC0_CONTEXT_STATUS__PWEEMPTED__SHIFT                                                           0x9
#define SDMA7_WWC0_CONTEXT_STATUS__PWEEMPT_DISABWE__SHIFT                                                     0xa
#define SDMA7_WWC0_CONTEXT_STATUS__SEWECTED_MASK                                                              0x00000001W
#define SDMA7_WWC0_CONTEXT_STATUS__IDWE_MASK                                                                  0x00000004W
#define SDMA7_WWC0_CONTEXT_STATUS__EXPIWED_MASK                                                               0x00000008W
#define SDMA7_WWC0_CONTEXT_STATUS__EXCEPTION_MASK                                                             0x00000070W
#define SDMA7_WWC0_CONTEXT_STATUS__CTXSW_ABWE_MASK                                                            0x00000080W
#define SDMA7_WWC0_CONTEXT_STATUS__CTXSW_WEADY_MASK                                                           0x00000100W
#define SDMA7_WWC0_CONTEXT_STATUS__PWEEMPTED_MASK                                                             0x00000200W
#define SDMA7_WWC0_CONTEXT_STATUS__PWEEMPT_DISABWE_MASK                                                       0x00000400W
//SDMA7_WWC0_DOOWBEWW
#define SDMA7_WWC0_DOOWBEWW__ENABWE__SHIFT                                                                    0x1c
#define SDMA7_WWC0_DOOWBEWW__CAPTUWED__SHIFT                                                                  0x1e
#define SDMA7_WWC0_DOOWBEWW__ENABWE_MASK                                                                      0x10000000W
#define SDMA7_WWC0_DOOWBEWW__CAPTUWED_MASK                                                                    0x40000000W
//SDMA7_WWC0_STATUS
#define SDMA7_WWC0_STATUS__WPTW_UPDATE_FAIW_COUNT__SHIFT                                                      0x0
#define SDMA7_WWC0_STATUS__WPTW_UPDATE_PENDING__SHIFT                                                         0x8
#define SDMA7_WWC0_STATUS__WPTW_UPDATE_FAIW_COUNT_MASK                                                        0x000000FFW
#define SDMA7_WWC0_STATUS__WPTW_UPDATE_PENDING_MASK                                                           0x00000100W
//SDMA7_WWC0_DOOWBEWW_WOG
#define SDMA7_WWC0_DOOWBEWW_WOG__BE_EWWOW__SHIFT                                                              0x0
#define SDMA7_WWC0_DOOWBEWW_WOG__DATA__SHIFT                                                                  0x2
#define SDMA7_WWC0_DOOWBEWW_WOG__BE_EWWOW_MASK                                                                0x00000001W
#define SDMA7_WWC0_DOOWBEWW_WOG__DATA_MASK                                                                    0xFFFFFFFCW
//SDMA7_WWC0_WATEWMAWK
#define SDMA7_WWC0_WATEWMAWK__WD_OUTSTANDING__SHIFT                                                           0x0
#define SDMA7_WWC0_WATEWMAWK__WW_OUTSTANDING__SHIFT                                                           0x10
#define SDMA7_WWC0_WATEWMAWK__WD_OUTSTANDING_MASK                                                             0x00000FFFW
#define SDMA7_WWC0_WATEWMAWK__WW_OUTSTANDING_MASK                                                             0x03FF0000W
//SDMA7_WWC0_DOOWBEWW_OFFSET
#define SDMA7_WWC0_DOOWBEWW_OFFSET__OFFSET__SHIFT                                                             0x2
#define SDMA7_WWC0_DOOWBEWW_OFFSET__OFFSET_MASK                                                               0x0FFFFFFCW
//SDMA7_WWC0_CSA_ADDW_WO
#define SDMA7_WWC0_CSA_ADDW_WO__ADDW__SHIFT                                                                   0x2
#define SDMA7_WWC0_CSA_ADDW_WO__ADDW_MASK                                                                     0xFFFFFFFCW
//SDMA7_WWC0_CSA_ADDW_HI
#define SDMA7_WWC0_CSA_ADDW_HI__ADDW__SHIFT                                                                   0x0
#define SDMA7_WWC0_CSA_ADDW_HI__ADDW_MASK                                                                     0xFFFFFFFFW
//SDMA7_WWC0_IB_SUB_WEMAIN
#define SDMA7_WWC0_IB_SUB_WEMAIN__SIZE__SHIFT                                                                 0x0
#define SDMA7_WWC0_IB_SUB_WEMAIN__SIZE_MASK                                                                   0x000FFFFFW
//SDMA7_WWC0_PWEEMPT
#define SDMA7_WWC0_PWEEMPT__IB_PWEEMPT__SHIFT                                                                 0x0
#define SDMA7_WWC0_PWEEMPT__IB_PWEEMPT_MASK                                                                   0x00000001W
//SDMA7_WWC0_DUMMY_WEG
#define SDMA7_WWC0_DUMMY_WEG__DUMMY__SHIFT                                                                    0x0
#define SDMA7_WWC0_DUMMY_WEG__DUMMY_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC0_WB_WPTW_POWW_ADDW_HI
#define SDMA7_WWC0_WB_WPTW_POWW_ADDW_HI__ADDW__SHIFT                                                          0x0
#define SDMA7_WWC0_WB_WPTW_POWW_ADDW_HI__ADDW_MASK                                                            0xFFFFFFFFW
//SDMA7_WWC0_WB_WPTW_POWW_ADDW_WO
#define SDMA7_WWC0_WB_WPTW_POWW_ADDW_WO__ADDW__SHIFT                                                          0x2
#define SDMA7_WWC0_WB_WPTW_POWW_ADDW_WO__ADDW_MASK                                                            0xFFFFFFFCW
//SDMA7_WWC0_WB_AQW_CNTW
#define SDMA7_WWC0_WB_AQW_CNTW__AQW_ENABWE__SHIFT                                                             0x0
#define SDMA7_WWC0_WB_AQW_CNTW__AQW_PACKET_SIZE__SHIFT                                                        0x1
#define SDMA7_WWC0_WB_AQW_CNTW__PACKET_STEP__SHIFT                                                            0x8
#define SDMA7_WWC0_WB_AQW_CNTW__AQW_ENABWE_MASK                                                               0x00000001W
#define SDMA7_WWC0_WB_AQW_CNTW__AQW_PACKET_SIZE_MASK                                                          0x000000FEW
#define SDMA7_WWC0_WB_AQW_CNTW__PACKET_STEP_MASK                                                              0x0000FF00W
//SDMA7_WWC0_MINOW_PTW_UPDATE
#define SDMA7_WWC0_MINOW_PTW_UPDATE__ENABWE__SHIFT                                                            0x0
#define SDMA7_WWC0_MINOW_PTW_UPDATE__ENABWE_MASK                                                              0x00000001W
//SDMA7_WWC0_MIDCMD_DATA0
#define SDMA7_WWC0_MIDCMD_DATA0__DATA0__SHIFT                                                                 0x0
#define SDMA7_WWC0_MIDCMD_DATA0__DATA0_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC0_MIDCMD_DATA1
#define SDMA7_WWC0_MIDCMD_DATA1__DATA1__SHIFT                                                                 0x0
#define SDMA7_WWC0_MIDCMD_DATA1__DATA1_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC0_MIDCMD_DATA2
#define SDMA7_WWC0_MIDCMD_DATA2__DATA2__SHIFT                                                                 0x0
#define SDMA7_WWC0_MIDCMD_DATA2__DATA2_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC0_MIDCMD_DATA3
#define SDMA7_WWC0_MIDCMD_DATA3__DATA3__SHIFT                                                                 0x0
#define SDMA7_WWC0_MIDCMD_DATA3__DATA3_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC0_MIDCMD_DATA4
#define SDMA7_WWC0_MIDCMD_DATA4__DATA4__SHIFT                                                                 0x0
#define SDMA7_WWC0_MIDCMD_DATA4__DATA4_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC0_MIDCMD_DATA5
#define SDMA7_WWC0_MIDCMD_DATA5__DATA5__SHIFT                                                                 0x0
#define SDMA7_WWC0_MIDCMD_DATA5__DATA5_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC0_MIDCMD_DATA6
#define SDMA7_WWC0_MIDCMD_DATA6__DATA6__SHIFT                                                                 0x0
#define SDMA7_WWC0_MIDCMD_DATA6__DATA6_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC0_MIDCMD_DATA7
#define SDMA7_WWC0_MIDCMD_DATA7__DATA7__SHIFT                                                                 0x0
#define SDMA7_WWC0_MIDCMD_DATA7__DATA7_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC0_MIDCMD_DATA8
#define SDMA7_WWC0_MIDCMD_DATA8__DATA8__SHIFT                                                                 0x0
#define SDMA7_WWC0_MIDCMD_DATA8__DATA8_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC0_MIDCMD_CNTW
#define SDMA7_WWC0_MIDCMD_CNTW__DATA_VAWID__SHIFT                                                             0x0
#define SDMA7_WWC0_MIDCMD_CNTW__COPY_MODE__SHIFT                                                              0x1
#define SDMA7_WWC0_MIDCMD_CNTW__SPWIT_STATE__SHIFT                                                            0x4
#define SDMA7_WWC0_MIDCMD_CNTW__AWWOW_PWEEMPT__SHIFT                                                          0x8
#define SDMA7_WWC0_MIDCMD_CNTW__DATA_VAWID_MASK                                                               0x00000001W
#define SDMA7_WWC0_MIDCMD_CNTW__COPY_MODE_MASK                                                                0x00000002W
#define SDMA7_WWC0_MIDCMD_CNTW__SPWIT_STATE_MASK                                                              0x000000F0W
#define SDMA7_WWC0_MIDCMD_CNTW__AWWOW_PWEEMPT_MASK                                                            0x00000100W
//SDMA7_WWC1_WB_CNTW
#define SDMA7_WWC1_WB_CNTW__WB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC1_WB_CNTW__WB_SIZE__SHIFT                                                                    0x1
#define SDMA7_WWC1_WB_CNTW__WB_SWAP_ENABWE__SHIFT                                                             0x9
#define SDMA7_WWC1_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT                                                      0xc
#define SDMA7_WWC1_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE__SHIFT                                                 0xd
#define SDMA7_WWC1_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT                                                       0x10
#define SDMA7_WWC1_WB_CNTW__WB_PWIV__SHIFT                                                                    0x17
#define SDMA7_WWC1_WB_CNTW__WB_VMID__SHIFT                                                                    0x18
#define SDMA7_WWC1_WB_CNTW__WB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC1_WB_CNTW__WB_SIZE_MASK                                                                      0x0000003EW
#define SDMA7_WWC1_WB_CNTW__WB_SWAP_ENABWE_MASK                                                               0x00000200W
#define SDMA7_WWC1_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK                                                        0x00001000W
#define SDMA7_WWC1_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE_MASK                                                   0x00002000W
#define SDMA7_WWC1_WB_CNTW__WPTW_WWITEBACK_TIMEW_MASK                                                         0x001F0000W
#define SDMA7_WWC1_WB_CNTW__WB_PWIV_MASK                                                                      0x00800000W
#define SDMA7_WWC1_WB_CNTW__WB_VMID_MASK                                                                      0x0F000000W
//SDMA7_WWC1_WB_BASE
#define SDMA7_WWC1_WB_BASE__ADDW__SHIFT                                                                       0x0
#define SDMA7_WWC1_WB_BASE__ADDW_MASK                                                                         0xFFFFFFFFW
//SDMA7_WWC1_WB_BASE_HI
#define SDMA7_WWC1_WB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC1_WB_BASE_HI__ADDW_MASK                                                                      0x00FFFFFFW
//SDMA7_WWC1_WB_WPTW
#define SDMA7_WWC1_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC1_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC1_WB_WPTW_HI
#define SDMA7_WWC1_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC1_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC1_WB_WPTW
#define SDMA7_WWC1_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC1_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC1_WB_WPTW_HI
#define SDMA7_WWC1_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC1_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC1_WB_WPTW_POWW_CNTW
#define SDMA7_WWC1_WB_WPTW_POWW_CNTW__ENABWE__SHIFT                                                           0x0
#define SDMA7_WWC1_WB_WPTW_POWW_CNTW__SWAP_ENABWE__SHIFT                                                      0x1
#define SDMA7_WWC1_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE__SHIFT                                                  0x2
#define SDMA7_WWC1_WB_WPTW_POWW_CNTW__FWEQUENCY__SHIFT                                                        0x4
#define SDMA7_WWC1_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT                                                  0x10
#define SDMA7_WWC1_WB_WPTW_POWW_CNTW__ENABWE_MASK                                                             0x00000001W
#define SDMA7_WWC1_WB_WPTW_POWW_CNTW__SWAP_ENABWE_MASK                                                        0x00000002W
#define SDMA7_WWC1_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE_MASK                                                    0x00000004W
#define SDMA7_WWC1_WB_WPTW_POWW_CNTW__FWEQUENCY_MASK                                                          0x0000FFF0W
#define SDMA7_WWC1_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT_MASK                                                    0xFFFF0000W
//SDMA7_WWC1_WB_WPTW_ADDW_HI
#define SDMA7_WWC1_WB_WPTW_ADDW_HI__ADDW__SHIFT                                                               0x0
#define SDMA7_WWC1_WB_WPTW_ADDW_HI__ADDW_MASK                                                                 0xFFFFFFFFW
//SDMA7_WWC1_WB_WPTW_ADDW_WO
#define SDMA7_WWC1_WB_WPTW_ADDW_WO__WPTW_WB_IDWE__SHIFT                                                       0x0
#define SDMA7_WWC1_WB_WPTW_ADDW_WO__ADDW__SHIFT                                                               0x2
#define SDMA7_WWC1_WB_WPTW_ADDW_WO__WPTW_WB_IDWE_MASK                                                         0x00000001W
#define SDMA7_WWC1_WB_WPTW_ADDW_WO__ADDW_MASK                                                                 0xFFFFFFFCW
//SDMA7_WWC1_IB_CNTW
#define SDMA7_WWC1_IB_CNTW__IB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC1_IB_CNTW__IB_SWAP_ENABWE__SHIFT                                                             0x4
#define SDMA7_WWC1_IB_CNTW__SWITCH_INSIDE_IB__SHIFT                                                           0x8
#define SDMA7_WWC1_IB_CNTW__CMD_VMID__SHIFT                                                                   0x10
#define SDMA7_WWC1_IB_CNTW__IB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC1_IB_CNTW__IB_SWAP_ENABWE_MASK                                                               0x00000010W
#define SDMA7_WWC1_IB_CNTW__SWITCH_INSIDE_IB_MASK                                                             0x00000100W
#define SDMA7_WWC1_IB_CNTW__CMD_VMID_MASK                                                                     0x000F0000W
//SDMA7_WWC1_IB_WPTW
#define SDMA7_WWC1_IB_WPTW__OFFSET__SHIFT                                                                     0x2
#define SDMA7_WWC1_IB_WPTW__OFFSET_MASK                                                                       0x003FFFFCW
//SDMA7_WWC1_IB_OFFSET
#define SDMA7_WWC1_IB_OFFSET__OFFSET__SHIFT                                                                   0x2
#define SDMA7_WWC1_IB_OFFSET__OFFSET_MASK                                                                     0x003FFFFCW
//SDMA7_WWC1_IB_BASE_WO
#define SDMA7_WWC1_IB_BASE_WO__ADDW__SHIFT                                                                    0x5
#define SDMA7_WWC1_IB_BASE_WO__ADDW_MASK                                                                      0xFFFFFFE0W
//SDMA7_WWC1_IB_BASE_HI
#define SDMA7_WWC1_IB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC1_IB_BASE_HI__ADDW_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC1_IB_SIZE
#define SDMA7_WWC1_IB_SIZE__SIZE__SHIFT                                                                       0x0
#define SDMA7_WWC1_IB_SIZE__SIZE_MASK                                                                         0x000FFFFFW
//SDMA7_WWC1_SKIP_CNTW
#define SDMA7_WWC1_SKIP_CNTW__SKIP_COUNT__SHIFT                                                               0x0
#define SDMA7_WWC1_SKIP_CNTW__SKIP_COUNT_MASK                                                                 0x000FFFFFW
//SDMA7_WWC1_CONTEXT_STATUS
#define SDMA7_WWC1_CONTEXT_STATUS__SEWECTED__SHIFT                                                            0x0
#define SDMA7_WWC1_CONTEXT_STATUS__IDWE__SHIFT                                                                0x2
#define SDMA7_WWC1_CONTEXT_STATUS__EXPIWED__SHIFT                                                             0x3
#define SDMA7_WWC1_CONTEXT_STATUS__EXCEPTION__SHIFT                                                           0x4
#define SDMA7_WWC1_CONTEXT_STATUS__CTXSW_ABWE__SHIFT                                                          0x7
#define SDMA7_WWC1_CONTEXT_STATUS__CTXSW_WEADY__SHIFT                                                         0x8
#define SDMA7_WWC1_CONTEXT_STATUS__PWEEMPTED__SHIFT                                                           0x9
#define SDMA7_WWC1_CONTEXT_STATUS__PWEEMPT_DISABWE__SHIFT                                                     0xa
#define SDMA7_WWC1_CONTEXT_STATUS__SEWECTED_MASK                                                              0x00000001W
#define SDMA7_WWC1_CONTEXT_STATUS__IDWE_MASK                                                                  0x00000004W
#define SDMA7_WWC1_CONTEXT_STATUS__EXPIWED_MASK                                                               0x00000008W
#define SDMA7_WWC1_CONTEXT_STATUS__EXCEPTION_MASK                                                             0x00000070W
#define SDMA7_WWC1_CONTEXT_STATUS__CTXSW_ABWE_MASK                                                            0x00000080W
#define SDMA7_WWC1_CONTEXT_STATUS__CTXSW_WEADY_MASK                                                           0x00000100W
#define SDMA7_WWC1_CONTEXT_STATUS__PWEEMPTED_MASK                                                             0x00000200W
#define SDMA7_WWC1_CONTEXT_STATUS__PWEEMPT_DISABWE_MASK                                                       0x00000400W
//SDMA7_WWC1_DOOWBEWW
#define SDMA7_WWC1_DOOWBEWW__ENABWE__SHIFT                                                                    0x1c
#define SDMA7_WWC1_DOOWBEWW__CAPTUWED__SHIFT                                                                  0x1e
#define SDMA7_WWC1_DOOWBEWW__ENABWE_MASK                                                                      0x10000000W
#define SDMA7_WWC1_DOOWBEWW__CAPTUWED_MASK                                                                    0x40000000W
//SDMA7_WWC1_STATUS
#define SDMA7_WWC1_STATUS__WPTW_UPDATE_FAIW_COUNT__SHIFT                                                      0x0
#define SDMA7_WWC1_STATUS__WPTW_UPDATE_PENDING__SHIFT                                                         0x8
#define SDMA7_WWC1_STATUS__WPTW_UPDATE_FAIW_COUNT_MASK                                                        0x000000FFW
#define SDMA7_WWC1_STATUS__WPTW_UPDATE_PENDING_MASK                                                           0x00000100W
//SDMA7_WWC1_DOOWBEWW_WOG
#define SDMA7_WWC1_DOOWBEWW_WOG__BE_EWWOW__SHIFT                                                              0x0
#define SDMA7_WWC1_DOOWBEWW_WOG__DATA__SHIFT                                                                  0x2
#define SDMA7_WWC1_DOOWBEWW_WOG__BE_EWWOW_MASK                                                                0x00000001W
#define SDMA7_WWC1_DOOWBEWW_WOG__DATA_MASK                                                                    0xFFFFFFFCW
//SDMA7_WWC1_WATEWMAWK
#define SDMA7_WWC1_WATEWMAWK__WD_OUTSTANDING__SHIFT                                                           0x0
#define SDMA7_WWC1_WATEWMAWK__WW_OUTSTANDING__SHIFT                                                           0x10
#define SDMA7_WWC1_WATEWMAWK__WD_OUTSTANDING_MASK                                                             0x00000FFFW
#define SDMA7_WWC1_WATEWMAWK__WW_OUTSTANDING_MASK                                                             0x03FF0000W
//SDMA7_WWC1_DOOWBEWW_OFFSET
#define SDMA7_WWC1_DOOWBEWW_OFFSET__OFFSET__SHIFT                                                             0x2
#define SDMA7_WWC1_DOOWBEWW_OFFSET__OFFSET_MASK                                                               0x0FFFFFFCW
//SDMA7_WWC1_CSA_ADDW_WO
#define SDMA7_WWC1_CSA_ADDW_WO__ADDW__SHIFT                                                                   0x2
#define SDMA7_WWC1_CSA_ADDW_WO__ADDW_MASK                                                                     0xFFFFFFFCW
//SDMA7_WWC1_CSA_ADDW_HI
#define SDMA7_WWC1_CSA_ADDW_HI__ADDW__SHIFT                                                                   0x0
#define SDMA7_WWC1_CSA_ADDW_HI__ADDW_MASK                                                                     0xFFFFFFFFW
//SDMA7_WWC1_IB_SUB_WEMAIN
#define SDMA7_WWC1_IB_SUB_WEMAIN__SIZE__SHIFT                                                                 0x0
#define SDMA7_WWC1_IB_SUB_WEMAIN__SIZE_MASK                                                                   0x000FFFFFW
//SDMA7_WWC1_PWEEMPT
#define SDMA7_WWC1_PWEEMPT__IB_PWEEMPT__SHIFT                                                                 0x0
#define SDMA7_WWC1_PWEEMPT__IB_PWEEMPT_MASK                                                                   0x00000001W
//SDMA7_WWC1_DUMMY_WEG
#define SDMA7_WWC1_DUMMY_WEG__DUMMY__SHIFT                                                                    0x0
#define SDMA7_WWC1_DUMMY_WEG__DUMMY_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC1_WB_WPTW_POWW_ADDW_HI
#define SDMA7_WWC1_WB_WPTW_POWW_ADDW_HI__ADDW__SHIFT                                                          0x0
#define SDMA7_WWC1_WB_WPTW_POWW_ADDW_HI__ADDW_MASK                                                            0xFFFFFFFFW
//SDMA7_WWC1_WB_WPTW_POWW_ADDW_WO
#define SDMA7_WWC1_WB_WPTW_POWW_ADDW_WO__ADDW__SHIFT                                                          0x2
#define SDMA7_WWC1_WB_WPTW_POWW_ADDW_WO__ADDW_MASK                                                            0xFFFFFFFCW
//SDMA7_WWC1_WB_AQW_CNTW
#define SDMA7_WWC1_WB_AQW_CNTW__AQW_ENABWE__SHIFT                                                             0x0
#define SDMA7_WWC1_WB_AQW_CNTW__AQW_PACKET_SIZE__SHIFT                                                        0x1
#define SDMA7_WWC1_WB_AQW_CNTW__PACKET_STEP__SHIFT                                                            0x8
#define SDMA7_WWC1_WB_AQW_CNTW__AQW_ENABWE_MASK                                                               0x00000001W
#define SDMA7_WWC1_WB_AQW_CNTW__AQW_PACKET_SIZE_MASK                                                          0x000000FEW
#define SDMA7_WWC1_WB_AQW_CNTW__PACKET_STEP_MASK                                                              0x0000FF00W
//SDMA7_WWC1_MINOW_PTW_UPDATE
#define SDMA7_WWC1_MINOW_PTW_UPDATE__ENABWE__SHIFT                                                            0x0
#define SDMA7_WWC1_MINOW_PTW_UPDATE__ENABWE_MASK                                                              0x00000001W
//SDMA7_WWC1_MIDCMD_DATA0
#define SDMA7_WWC1_MIDCMD_DATA0__DATA0__SHIFT                                                                 0x0
#define SDMA7_WWC1_MIDCMD_DATA0__DATA0_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC1_MIDCMD_DATA1
#define SDMA7_WWC1_MIDCMD_DATA1__DATA1__SHIFT                                                                 0x0
#define SDMA7_WWC1_MIDCMD_DATA1__DATA1_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC1_MIDCMD_DATA2
#define SDMA7_WWC1_MIDCMD_DATA2__DATA2__SHIFT                                                                 0x0
#define SDMA7_WWC1_MIDCMD_DATA2__DATA2_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC1_MIDCMD_DATA3
#define SDMA7_WWC1_MIDCMD_DATA3__DATA3__SHIFT                                                                 0x0
#define SDMA7_WWC1_MIDCMD_DATA3__DATA3_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC1_MIDCMD_DATA4
#define SDMA7_WWC1_MIDCMD_DATA4__DATA4__SHIFT                                                                 0x0
#define SDMA7_WWC1_MIDCMD_DATA4__DATA4_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC1_MIDCMD_DATA5
#define SDMA7_WWC1_MIDCMD_DATA5__DATA5__SHIFT                                                                 0x0
#define SDMA7_WWC1_MIDCMD_DATA5__DATA5_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC1_MIDCMD_DATA6
#define SDMA7_WWC1_MIDCMD_DATA6__DATA6__SHIFT                                                                 0x0
#define SDMA7_WWC1_MIDCMD_DATA6__DATA6_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC1_MIDCMD_DATA7
#define SDMA7_WWC1_MIDCMD_DATA7__DATA7__SHIFT                                                                 0x0
#define SDMA7_WWC1_MIDCMD_DATA7__DATA7_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC1_MIDCMD_DATA8
#define SDMA7_WWC1_MIDCMD_DATA8__DATA8__SHIFT                                                                 0x0
#define SDMA7_WWC1_MIDCMD_DATA8__DATA8_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC1_MIDCMD_CNTW
#define SDMA7_WWC1_MIDCMD_CNTW__DATA_VAWID__SHIFT                                                             0x0
#define SDMA7_WWC1_MIDCMD_CNTW__COPY_MODE__SHIFT                                                              0x1
#define SDMA7_WWC1_MIDCMD_CNTW__SPWIT_STATE__SHIFT                                                            0x4
#define SDMA7_WWC1_MIDCMD_CNTW__AWWOW_PWEEMPT__SHIFT                                                          0x8
#define SDMA7_WWC1_MIDCMD_CNTW__DATA_VAWID_MASK                                                               0x00000001W
#define SDMA7_WWC1_MIDCMD_CNTW__COPY_MODE_MASK                                                                0x00000002W
#define SDMA7_WWC1_MIDCMD_CNTW__SPWIT_STATE_MASK                                                              0x000000F0W
#define SDMA7_WWC1_MIDCMD_CNTW__AWWOW_PWEEMPT_MASK                                                            0x00000100W
//SDMA7_WWC2_WB_CNTW
#define SDMA7_WWC2_WB_CNTW__WB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC2_WB_CNTW__WB_SIZE__SHIFT                                                                    0x1
#define SDMA7_WWC2_WB_CNTW__WB_SWAP_ENABWE__SHIFT                                                             0x9
#define SDMA7_WWC2_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT                                                      0xc
#define SDMA7_WWC2_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE__SHIFT                                                 0xd
#define SDMA7_WWC2_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT                                                       0x10
#define SDMA7_WWC2_WB_CNTW__WB_PWIV__SHIFT                                                                    0x17
#define SDMA7_WWC2_WB_CNTW__WB_VMID__SHIFT                                                                    0x18
#define SDMA7_WWC2_WB_CNTW__WB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC2_WB_CNTW__WB_SIZE_MASK                                                                      0x0000003EW
#define SDMA7_WWC2_WB_CNTW__WB_SWAP_ENABWE_MASK                                                               0x00000200W
#define SDMA7_WWC2_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK                                                        0x00001000W
#define SDMA7_WWC2_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE_MASK                                                   0x00002000W
#define SDMA7_WWC2_WB_CNTW__WPTW_WWITEBACK_TIMEW_MASK                                                         0x001F0000W
#define SDMA7_WWC2_WB_CNTW__WB_PWIV_MASK                                                                      0x00800000W
#define SDMA7_WWC2_WB_CNTW__WB_VMID_MASK                                                                      0x0F000000W
//SDMA7_WWC2_WB_BASE
#define SDMA7_WWC2_WB_BASE__ADDW__SHIFT                                                                       0x0
#define SDMA7_WWC2_WB_BASE__ADDW_MASK                                                                         0xFFFFFFFFW
//SDMA7_WWC2_WB_BASE_HI
#define SDMA7_WWC2_WB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC2_WB_BASE_HI__ADDW_MASK                                                                      0x00FFFFFFW
//SDMA7_WWC2_WB_WPTW
#define SDMA7_WWC2_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC2_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC2_WB_WPTW_HI
#define SDMA7_WWC2_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC2_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC2_WB_WPTW
#define SDMA7_WWC2_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC2_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC2_WB_WPTW_HI
#define SDMA7_WWC2_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC2_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC2_WB_WPTW_POWW_CNTW
#define SDMA7_WWC2_WB_WPTW_POWW_CNTW__ENABWE__SHIFT                                                           0x0
#define SDMA7_WWC2_WB_WPTW_POWW_CNTW__SWAP_ENABWE__SHIFT                                                      0x1
#define SDMA7_WWC2_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE__SHIFT                                                  0x2
#define SDMA7_WWC2_WB_WPTW_POWW_CNTW__FWEQUENCY__SHIFT                                                        0x4
#define SDMA7_WWC2_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT                                                  0x10
#define SDMA7_WWC2_WB_WPTW_POWW_CNTW__ENABWE_MASK                                                             0x00000001W
#define SDMA7_WWC2_WB_WPTW_POWW_CNTW__SWAP_ENABWE_MASK                                                        0x00000002W
#define SDMA7_WWC2_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE_MASK                                                    0x00000004W
#define SDMA7_WWC2_WB_WPTW_POWW_CNTW__FWEQUENCY_MASK                                                          0x0000FFF0W
#define SDMA7_WWC2_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT_MASK                                                    0xFFFF0000W
//SDMA7_WWC2_WB_WPTW_ADDW_HI
#define SDMA7_WWC2_WB_WPTW_ADDW_HI__ADDW__SHIFT                                                               0x0
#define SDMA7_WWC2_WB_WPTW_ADDW_HI__ADDW_MASK                                                                 0xFFFFFFFFW
//SDMA7_WWC2_WB_WPTW_ADDW_WO
#define SDMA7_WWC2_WB_WPTW_ADDW_WO__WPTW_WB_IDWE__SHIFT                                                       0x0
#define SDMA7_WWC2_WB_WPTW_ADDW_WO__ADDW__SHIFT                                                               0x2
#define SDMA7_WWC2_WB_WPTW_ADDW_WO__WPTW_WB_IDWE_MASK                                                         0x00000001W
#define SDMA7_WWC2_WB_WPTW_ADDW_WO__ADDW_MASK                                                                 0xFFFFFFFCW
//SDMA7_WWC2_IB_CNTW
#define SDMA7_WWC2_IB_CNTW__IB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC2_IB_CNTW__IB_SWAP_ENABWE__SHIFT                                                             0x4
#define SDMA7_WWC2_IB_CNTW__SWITCH_INSIDE_IB__SHIFT                                                           0x8
#define SDMA7_WWC2_IB_CNTW__CMD_VMID__SHIFT                                                                   0x10
#define SDMA7_WWC2_IB_CNTW__IB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC2_IB_CNTW__IB_SWAP_ENABWE_MASK                                                               0x00000010W
#define SDMA7_WWC2_IB_CNTW__SWITCH_INSIDE_IB_MASK                                                             0x00000100W
#define SDMA7_WWC2_IB_CNTW__CMD_VMID_MASK                                                                     0x000F0000W
//SDMA7_WWC2_IB_WPTW
#define SDMA7_WWC2_IB_WPTW__OFFSET__SHIFT                                                                     0x2
#define SDMA7_WWC2_IB_WPTW__OFFSET_MASK                                                                       0x003FFFFCW
//SDMA7_WWC2_IB_OFFSET
#define SDMA7_WWC2_IB_OFFSET__OFFSET__SHIFT                                                                   0x2
#define SDMA7_WWC2_IB_OFFSET__OFFSET_MASK                                                                     0x003FFFFCW
//SDMA7_WWC2_IB_BASE_WO
#define SDMA7_WWC2_IB_BASE_WO__ADDW__SHIFT                                                                    0x5
#define SDMA7_WWC2_IB_BASE_WO__ADDW_MASK                                                                      0xFFFFFFE0W
//SDMA7_WWC2_IB_BASE_HI
#define SDMA7_WWC2_IB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC2_IB_BASE_HI__ADDW_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC2_IB_SIZE
#define SDMA7_WWC2_IB_SIZE__SIZE__SHIFT                                                                       0x0
#define SDMA7_WWC2_IB_SIZE__SIZE_MASK                                                                         0x000FFFFFW
//SDMA7_WWC2_SKIP_CNTW
#define SDMA7_WWC2_SKIP_CNTW__SKIP_COUNT__SHIFT                                                               0x0
#define SDMA7_WWC2_SKIP_CNTW__SKIP_COUNT_MASK                                                                 0x000FFFFFW
//SDMA7_WWC2_CONTEXT_STATUS
#define SDMA7_WWC2_CONTEXT_STATUS__SEWECTED__SHIFT                                                            0x0
#define SDMA7_WWC2_CONTEXT_STATUS__IDWE__SHIFT                                                                0x2
#define SDMA7_WWC2_CONTEXT_STATUS__EXPIWED__SHIFT                                                             0x3
#define SDMA7_WWC2_CONTEXT_STATUS__EXCEPTION__SHIFT                                                           0x4
#define SDMA7_WWC2_CONTEXT_STATUS__CTXSW_ABWE__SHIFT                                                          0x7
#define SDMA7_WWC2_CONTEXT_STATUS__CTXSW_WEADY__SHIFT                                                         0x8
#define SDMA7_WWC2_CONTEXT_STATUS__PWEEMPTED__SHIFT                                                           0x9
#define SDMA7_WWC2_CONTEXT_STATUS__PWEEMPT_DISABWE__SHIFT                                                     0xa
#define SDMA7_WWC2_CONTEXT_STATUS__SEWECTED_MASK                                                              0x00000001W
#define SDMA7_WWC2_CONTEXT_STATUS__IDWE_MASK                                                                  0x00000004W
#define SDMA7_WWC2_CONTEXT_STATUS__EXPIWED_MASK                                                               0x00000008W
#define SDMA7_WWC2_CONTEXT_STATUS__EXCEPTION_MASK                                                             0x00000070W
#define SDMA7_WWC2_CONTEXT_STATUS__CTXSW_ABWE_MASK                                                            0x00000080W
#define SDMA7_WWC2_CONTEXT_STATUS__CTXSW_WEADY_MASK                                                           0x00000100W
#define SDMA7_WWC2_CONTEXT_STATUS__PWEEMPTED_MASK                                                             0x00000200W
#define SDMA7_WWC2_CONTEXT_STATUS__PWEEMPT_DISABWE_MASK                                                       0x00000400W
//SDMA7_WWC2_DOOWBEWW
#define SDMA7_WWC2_DOOWBEWW__ENABWE__SHIFT                                                                    0x1c
#define SDMA7_WWC2_DOOWBEWW__CAPTUWED__SHIFT                                                                  0x1e
#define SDMA7_WWC2_DOOWBEWW__ENABWE_MASK                                                                      0x10000000W
#define SDMA7_WWC2_DOOWBEWW__CAPTUWED_MASK                                                                    0x40000000W
//SDMA7_WWC2_STATUS
#define SDMA7_WWC2_STATUS__WPTW_UPDATE_FAIW_COUNT__SHIFT                                                      0x0
#define SDMA7_WWC2_STATUS__WPTW_UPDATE_PENDING__SHIFT                                                         0x8
#define SDMA7_WWC2_STATUS__WPTW_UPDATE_FAIW_COUNT_MASK                                                        0x000000FFW
#define SDMA7_WWC2_STATUS__WPTW_UPDATE_PENDING_MASK                                                           0x00000100W
//SDMA7_WWC2_DOOWBEWW_WOG
#define SDMA7_WWC2_DOOWBEWW_WOG__BE_EWWOW__SHIFT                                                              0x0
#define SDMA7_WWC2_DOOWBEWW_WOG__DATA__SHIFT                                                                  0x2
#define SDMA7_WWC2_DOOWBEWW_WOG__BE_EWWOW_MASK                                                                0x00000001W
#define SDMA7_WWC2_DOOWBEWW_WOG__DATA_MASK                                                                    0xFFFFFFFCW
//SDMA7_WWC2_WATEWMAWK
#define SDMA7_WWC2_WATEWMAWK__WD_OUTSTANDING__SHIFT                                                           0x0
#define SDMA7_WWC2_WATEWMAWK__WW_OUTSTANDING__SHIFT                                                           0x10
#define SDMA7_WWC2_WATEWMAWK__WD_OUTSTANDING_MASK                                                             0x00000FFFW
#define SDMA7_WWC2_WATEWMAWK__WW_OUTSTANDING_MASK                                                             0x03FF0000W
//SDMA7_WWC2_DOOWBEWW_OFFSET
#define SDMA7_WWC2_DOOWBEWW_OFFSET__OFFSET__SHIFT                                                             0x2
#define SDMA7_WWC2_DOOWBEWW_OFFSET__OFFSET_MASK                                                               0x0FFFFFFCW
//SDMA7_WWC2_CSA_ADDW_WO
#define SDMA7_WWC2_CSA_ADDW_WO__ADDW__SHIFT                                                                   0x2
#define SDMA7_WWC2_CSA_ADDW_WO__ADDW_MASK                                                                     0xFFFFFFFCW
//SDMA7_WWC2_CSA_ADDW_HI
#define SDMA7_WWC2_CSA_ADDW_HI__ADDW__SHIFT                                                                   0x0
#define SDMA7_WWC2_CSA_ADDW_HI__ADDW_MASK                                                                     0xFFFFFFFFW
//SDMA7_WWC2_IB_SUB_WEMAIN
#define SDMA7_WWC2_IB_SUB_WEMAIN__SIZE__SHIFT                                                                 0x0
#define SDMA7_WWC2_IB_SUB_WEMAIN__SIZE_MASK                                                                   0x000FFFFFW
//SDMA7_WWC2_PWEEMPT
#define SDMA7_WWC2_PWEEMPT__IB_PWEEMPT__SHIFT                                                                 0x0
#define SDMA7_WWC2_PWEEMPT__IB_PWEEMPT_MASK                                                                   0x00000001W
//SDMA7_WWC2_DUMMY_WEG
#define SDMA7_WWC2_DUMMY_WEG__DUMMY__SHIFT                                                                    0x0
#define SDMA7_WWC2_DUMMY_WEG__DUMMY_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC2_WB_WPTW_POWW_ADDW_HI
#define SDMA7_WWC2_WB_WPTW_POWW_ADDW_HI__ADDW__SHIFT                                                          0x0
#define SDMA7_WWC2_WB_WPTW_POWW_ADDW_HI__ADDW_MASK                                                            0xFFFFFFFFW
//SDMA7_WWC2_WB_WPTW_POWW_ADDW_WO
#define SDMA7_WWC2_WB_WPTW_POWW_ADDW_WO__ADDW__SHIFT                                                          0x2
#define SDMA7_WWC2_WB_WPTW_POWW_ADDW_WO__ADDW_MASK                                                            0xFFFFFFFCW
//SDMA7_WWC2_WB_AQW_CNTW
#define SDMA7_WWC2_WB_AQW_CNTW__AQW_ENABWE__SHIFT                                                             0x0
#define SDMA7_WWC2_WB_AQW_CNTW__AQW_PACKET_SIZE__SHIFT                                                        0x1
#define SDMA7_WWC2_WB_AQW_CNTW__PACKET_STEP__SHIFT                                                            0x8
#define SDMA7_WWC2_WB_AQW_CNTW__AQW_ENABWE_MASK                                                               0x00000001W
#define SDMA7_WWC2_WB_AQW_CNTW__AQW_PACKET_SIZE_MASK                                                          0x000000FEW
#define SDMA7_WWC2_WB_AQW_CNTW__PACKET_STEP_MASK                                                              0x0000FF00W
//SDMA7_WWC2_MINOW_PTW_UPDATE
#define SDMA7_WWC2_MINOW_PTW_UPDATE__ENABWE__SHIFT                                                            0x0
#define SDMA7_WWC2_MINOW_PTW_UPDATE__ENABWE_MASK                                                              0x00000001W
//SDMA7_WWC2_MIDCMD_DATA0
#define SDMA7_WWC2_MIDCMD_DATA0__DATA0__SHIFT                                                                 0x0
#define SDMA7_WWC2_MIDCMD_DATA0__DATA0_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC2_MIDCMD_DATA1
#define SDMA7_WWC2_MIDCMD_DATA1__DATA1__SHIFT                                                                 0x0
#define SDMA7_WWC2_MIDCMD_DATA1__DATA1_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC2_MIDCMD_DATA2
#define SDMA7_WWC2_MIDCMD_DATA2__DATA2__SHIFT                                                                 0x0
#define SDMA7_WWC2_MIDCMD_DATA2__DATA2_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC2_MIDCMD_DATA3
#define SDMA7_WWC2_MIDCMD_DATA3__DATA3__SHIFT                                                                 0x0
#define SDMA7_WWC2_MIDCMD_DATA3__DATA3_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC2_MIDCMD_DATA4
#define SDMA7_WWC2_MIDCMD_DATA4__DATA4__SHIFT                                                                 0x0
#define SDMA7_WWC2_MIDCMD_DATA4__DATA4_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC2_MIDCMD_DATA5
#define SDMA7_WWC2_MIDCMD_DATA5__DATA5__SHIFT                                                                 0x0
#define SDMA7_WWC2_MIDCMD_DATA5__DATA5_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC2_MIDCMD_DATA6
#define SDMA7_WWC2_MIDCMD_DATA6__DATA6__SHIFT                                                                 0x0
#define SDMA7_WWC2_MIDCMD_DATA6__DATA6_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC2_MIDCMD_DATA7
#define SDMA7_WWC2_MIDCMD_DATA7__DATA7__SHIFT                                                                 0x0
#define SDMA7_WWC2_MIDCMD_DATA7__DATA7_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC2_MIDCMD_DATA8
#define SDMA7_WWC2_MIDCMD_DATA8__DATA8__SHIFT                                                                 0x0
#define SDMA7_WWC2_MIDCMD_DATA8__DATA8_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC2_MIDCMD_CNTW
#define SDMA7_WWC2_MIDCMD_CNTW__DATA_VAWID__SHIFT                                                             0x0
#define SDMA7_WWC2_MIDCMD_CNTW__COPY_MODE__SHIFT                                                              0x1
#define SDMA7_WWC2_MIDCMD_CNTW__SPWIT_STATE__SHIFT                                                            0x4
#define SDMA7_WWC2_MIDCMD_CNTW__AWWOW_PWEEMPT__SHIFT                                                          0x8
#define SDMA7_WWC2_MIDCMD_CNTW__DATA_VAWID_MASK                                                               0x00000001W
#define SDMA7_WWC2_MIDCMD_CNTW__COPY_MODE_MASK                                                                0x00000002W
#define SDMA7_WWC2_MIDCMD_CNTW__SPWIT_STATE_MASK                                                              0x000000F0W
#define SDMA7_WWC2_MIDCMD_CNTW__AWWOW_PWEEMPT_MASK                                                            0x00000100W
//SDMA7_WWC3_WB_CNTW
#define SDMA7_WWC3_WB_CNTW__WB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC3_WB_CNTW__WB_SIZE__SHIFT                                                                    0x1
#define SDMA7_WWC3_WB_CNTW__WB_SWAP_ENABWE__SHIFT                                                             0x9
#define SDMA7_WWC3_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT                                                      0xc
#define SDMA7_WWC3_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE__SHIFT                                                 0xd
#define SDMA7_WWC3_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT                                                       0x10
#define SDMA7_WWC3_WB_CNTW__WB_PWIV__SHIFT                                                                    0x17
#define SDMA7_WWC3_WB_CNTW__WB_VMID__SHIFT                                                                    0x18
#define SDMA7_WWC3_WB_CNTW__WB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC3_WB_CNTW__WB_SIZE_MASK                                                                      0x0000003EW
#define SDMA7_WWC3_WB_CNTW__WB_SWAP_ENABWE_MASK                                                               0x00000200W
#define SDMA7_WWC3_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK                                                        0x00001000W
#define SDMA7_WWC3_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE_MASK                                                   0x00002000W
#define SDMA7_WWC3_WB_CNTW__WPTW_WWITEBACK_TIMEW_MASK                                                         0x001F0000W
#define SDMA7_WWC3_WB_CNTW__WB_PWIV_MASK                                                                      0x00800000W
#define SDMA7_WWC3_WB_CNTW__WB_VMID_MASK                                                                      0x0F000000W
//SDMA7_WWC3_WB_BASE
#define SDMA7_WWC3_WB_BASE__ADDW__SHIFT                                                                       0x0
#define SDMA7_WWC3_WB_BASE__ADDW_MASK                                                                         0xFFFFFFFFW
//SDMA7_WWC3_WB_BASE_HI
#define SDMA7_WWC3_WB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC3_WB_BASE_HI__ADDW_MASK                                                                      0x00FFFFFFW
//SDMA7_WWC3_WB_WPTW
#define SDMA7_WWC3_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC3_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC3_WB_WPTW_HI
#define SDMA7_WWC3_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC3_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC3_WB_WPTW
#define SDMA7_WWC3_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC3_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC3_WB_WPTW_HI
#define SDMA7_WWC3_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC3_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC3_WB_WPTW_POWW_CNTW
#define SDMA7_WWC3_WB_WPTW_POWW_CNTW__ENABWE__SHIFT                                                           0x0
#define SDMA7_WWC3_WB_WPTW_POWW_CNTW__SWAP_ENABWE__SHIFT                                                      0x1
#define SDMA7_WWC3_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE__SHIFT                                                  0x2
#define SDMA7_WWC3_WB_WPTW_POWW_CNTW__FWEQUENCY__SHIFT                                                        0x4
#define SDMA7_WWC3_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT                                                  0x10
#define SDMA7_WWC3_WB_WPTW_POWW_CNTW__ENABWE_MASK                                                             0x00000001W
#define SDMA7_WWC3_WB_WPTW_POWW_CNTW__SWAP_ENABWE_MASK                                                        0x00000002W
#define SDMA7_WWC3_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE_MASK                                                    0x00000004W
#define SDMA7_WWC3_WB_WPTW_POWW_CNTW__FWEQUENCY_MASK                                                          0x0000FFF0W
#define SDMA7_WWC3_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT_MASK                                                    0xFFFF0000W
//SDMA7_WWC3_WB_WPTW_ADDW_HI
#define SDMA7_WWC3_WB_WPTW_ADDW_HI__ADDW__SHIFT                                                               0x0
#define SDMA7_WWC3_WB_WPTW_ADDW_HI__ADDW_MASK                                                                 0xFFFFFFFFW
//SDMA7_WWC3_WB_WPTW_ADDW_WO
#define SDMA7_WWC3_WB_WPTW_ADDW_WO__WPTW_WB_IDWE__SHIFT                                                       0x0
#define SDMA7_WWC3_WB_WPTW_ADDW_WO__ADDW__SHIFT                                                               0x2
#define SDMA7_WWC3_WB_WPTW_ADDW_WO__WPTW_WB_IDWE_MASK                                                         0x00000001W
#define SDMA7_WWC3_WB_WPTW_ADDW_WO__ADDW_MASK                                                                 0xFFFFFFFCW
//SDMA7_WWC3_IB_CNTW
#define SDMA7_WWC3_IB_CNTW__IB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC3_IB_CNTW__IB_SWAP_ENABWE__SHIFT                                                             0x4
#define SDMA7_WWC3_IB_CNTW__SWITCH_INSIDE_IB__SHIFT                                                           0x8
#define SDMA7_WWC3_IB_CNTW__CMD_VMID__SHIFT                                                                   0x10
#define SDMA7_WWC3_IB_CNTW__IB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC3_IB_CNTW__IB_SWAP_ENABWE_MASK                                                               0x00000010W
#define SDMA7_WWC3_IB_CNTW__SWITCH_INSIDE_IB_MASK                                                             0x00000100W
#define SDMA7_WWC3_IB_CNTW__CMD_VMID_MASK                                                                     0x000F0000W
//SDMA7_WWC3_IB_WPTW
#define SDMA7_WWC3_IB_WPTW__OFFSET__SHIFT                                                                     0x2
#define SDMA7_WWC3_IB_WPTW__OFFSET_MASK                                                                       0x003FFFFCW
//SDMA7_WWC3_IB_OFFSET
#define SDMA7_WWC3_IB_OFFSET__OFFSET__SHIFT                                                                   0x2
#define SDMA7_WWC3_IB_OFFSET__OFFSET_MASK                                                                     0x003FFFFCW
//SDMA7_WWC3_IB_BASE_WO
#define SDMA7_WWC3_IB_BASE_WO__ADDW__SHIFT                                                                    0x5
#define SDMA7_WWC3_IB_BASE_WO__ADDW_MASK                                                                      0xFFFFFFE0W
//SDMA7_WWC3_IB_BASE_HI
#define SDMA7_WWC3_IB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC3_IB_BASE_HI__ADDW_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC3_IB_SIZE
#define SDMA7_WWC3_IB_SIZE__SIZE__SHIFT                                                                       0x0
#define SDMA7_WWC3_IB_SIZE__SIZE_MASK                                                                         0x000FFFFFW
//SDMA7_WWC3_SKIP_CNTW
#define SDMA7_WWC3_SKIP_CNTW__SKIP_COUNT__SHIFT                                                               0x0
#define SDMA7_WWC3_SKIP_CNTW__SKIP_COUNT_MASK                                                                 0x000FFFFFW
//SDMA7_WWC3_CONTEXT_STATUS
#define SDMA7_WWC3_CONTEXT_STATUS__SEWECTED__SHIFT                                                            0x0
#define SDMA7_WWC3_CONTEXT_STATUS__IDWE__SHIFT                                                                0x2
#define SDMA7_WWC3_CONTEXT_STATUS__EXPIWED__SHIFT                                                             0x3
#define SDMA7_WWC3_CONTEXT_STATUS__EXCEPTION__SHIFT                                                           0x4
#define SDMA7_WWC3_CONTEXT_STATUS__CTXSW_ABWE__SHIFT                                                          0x7
#define SDMA7_WWC3_CONTEXT_STATUS__CTXSW_WEADY__SHIFT                                                         0x8
#define SDMA7_WWC3_CONTEXT_STATUS__PWEEMPTED__SHIFT                                                           0x9
#define SDMA7_WWC3_CONTEXT_STATUS__PWEEMPT_DISABWE__SHIFT                                                     0xa
#define SDMA7_WWC3_CONTEXT_STATUS__SEWECTED_MASK                                                              0x00000001W
#define SDMA7_WWC3_CONTEXT_STATUS__IDWE_MASK                                                                  0x00000004W
#define SDMA7_WWC3_CONTEXT_STATUS__EXPIWED_MASK                                                               0x00000008W
#define SDMA7_WWC3_CONTEXT_STATUS__EXCEPTION_MASK                                                             0x00000070W
#define SDMA7_WWC3_CONTEXT_STATUS__CTXSW_ABWE_MASK                                                            0x00000080W
#define SDMA7_WWC3_CONTEXT_STATUS__CTXSW_WEADY_MASK                                                           0x00000100W
#define SDMA7_WWC3_CONTEXT_STATUS__PWEEMPTED_MASK                                                             0x00000200W
#define SDMA7_WWC3_CONTEXT_STATUS__PWEEMPT_DISABWE_MASK                                                       0x00000400W
//SDMA7_WWC3_DOOWBEWW
#define SDMA7_WWC3_DOOWBEWW__ENABWE__SHIFT                                                                    0x1c
#define SDMA7_WWC3_DOOWBEWW__CAPTUWED__SHIFT                                                                  0x1e
#define SDMA7_WWC3_DOOWBEWW__ENABWE_MASK                                                                      0x10000000W
#define SDMA7_WWC3_DOOWBEWW__CAPTUWED_MASK                                                                    0x40000000W
//SDMA7_WWC3_STATUS
#define SDMA7_WWC3_STATUS__WPTW_UPDATE_FAIW_COUNT__SHIFT                                                      0x0
#define SDMA7_WWC3_STATUS__WPTW_UPDATE_PENDING__SHIFT                                                         0x8
#define SDMA7_WWC3_STATUS__WPTW_UPDATE_FAIW_COUNT_MASK                                                        0x000000FFW
#define SDMA7_WWC3_STATUS__WPTW_UPDATE_PENDING_MASK                                                           0x00000100W
//SDMA7_WWC3_DOOWBEWW_WOG
#define SDMA7_WWC3_DOOWBEWW_WOG__BE_EWWOW__SHIFT                                                              0x0
#define SDMA7_WWC3_DOOWBEWW_WOG__DATA__SHIFT                                                                  0x2
#define SDMA7_WWC3_DOOWBEWW_WOG__BE_EWWOW_MASK                                                                0x00000001W
#define SDMA7_WWC3_DOOWBEWW_WOG__DATA_MASK                                                                    0xFFFFFFFCW
//SDMA7_WWC3_WATEWMAWK
#define SDMA7_WWC3_WATEWMAWK__WD_OUTSTANDING__SHIFT                                                           0x0
#define SDMA7_WWC3_WATEWMAWK__WW_OUTSTANDING__SHIFT                                                           0x10
#define SDMA7_WWC3_WATEWMAWK__WD_OUTSTANDING_MASK                                                             0x00000FFFW
#define SDMA7_WWC3_WATEWMAWK__WW_OUTSTANDING_MASK                                                             0x03FF0000W
//SDMA7_WWC3_DOOWBEWW_OFFSET
#define SDMA7_WWC3_DOOWBEWW_OFFSET__OFFSET__SHIFT                                                             0x2
#define SDMA7_WWC3_DOOWBEWW_OFFSET__OFFSET_MASK                                                               0x0FFFFFFCW
//SDMA7_WWC3_CSA_ADDW_WO
#define SDMA7_WWC3_CSA_ADDW_WO__ADDW__SHIFT                                                                   0x2
#define SDMA7_WWC3_CSA_ADDW_WO__ADDW_MASK                                                                     0xFFFFFFFCW
//SDMA7_WWC3_CSA_ADDW_HI
#define SDMA7_WWC3_CSA_ADDW_HI__ADDW__SHIFT                                                                   0x0
#define SDMA7_WWC3_CSA_ADDW_HI__ADDW_MASK                                                                     0xFFFFFFFFW
//SDMA7_WWC3_IB_SUB_WEMAIN
#define SDMA7_WWC3_IB_SUB_WEMAIN__SIZE__SHIFT                                                                 0x0
#define SDMA7_WWC3_IB_SUB_WEMAIN__SIZE_MASK                                                                   0x000FFFFFW
//SDMA7_WWC3_PWEEMPT
#define SDMA7_WWC3_PWEEMPT__IB_PWEEMPT__SHIFT                                                                 0x0
#define SDMA7_WWC3_PWEEMPT__IB_PWEEMPT_MASK                                                                   0x00000001W
//SDMA7_WWC3_DUMMY_WEG
#define SDMA7_WWC3_DUMMY_WEG__DUMMY__SHIFT                                                                    0x0
#define SDMA7_WWC3_DUMMY_WEG__DUMMY_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC3_WB_WPTW_POWW_ADDW_HI
#define SDMA7_WWC3_WB_WPTW_POWW_ADDW_HI__ADDW__SHIFT                                                          0x0
#define SDMA7_WWC3_WB_WPTW_POWW_ADDW_HI__ADDW_MASK                                                            0xFFFFFFFFW
//SDMA7_WWC3_WB_WPTW_POWW_ADDW_WO
#define SDMA7_WWC3_WB_WPTW_POWW_ADDW_WO__ADDW__SHIFT                                                          0x2
#define SDMA7_WWC3_WB_WPTW_POWW_ADDW_WO__ADDW_MASK                                                            0xFFFFFFFCW
//SDMA7_WWC3_WB_AQW_CNTW
#define SDMA7_WWC3_WB_AQW_CNTW__AQW_ENABWE__SHIFT                                                             0x0
#define SDMA7_WWC3_WB_AQW_CNTW__AQW_PACKET_SIZE__SHIFT                                                        0x1
#define SDMA7_WWC3_WB_AQW_CNTW__PACKET_STEP__SHIFT                                                            0x8
#define SDMA7_WWC3_WB_AQW_CNTW__AQW_ENABWE_MASK                                                               0x00000001W
#define SDMA7_WWC3_WB_AQW_CNTW__AQW_PACKET_SIZE_MASK                                                          0x000000FEW
#define SDMA7_WWC3_WB_AQW_CNTW__PACKET_STEP_MASK                                                              0x0000FF00W
//SDMA7_WWC3_MINOW_PTW_UPDATE
#define SDMA7_WWC3_MINOW_PTW_UPDATE__ENABWE__SHIFT                                                            0x0
#define SDMA7_WWC3_MINOW_PTW_UPDATE__ENABWE_MASK                                                              0x00000001W
//SDMA7_WWC3_MIDCMD_DATA0
#define SDMA7_WWC3_MIDCMD_DATA0__DATA0__SHIFT                                                                 0x0
#define SDMA7_WWC3_MIDCMD_DATA0__DATA0_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC3_MIDCMD_DATA1
#define SDMA7_WWC3_MIDCMD_DATA1__DATA1__SHIFT                                                                 0x0
#define SDMA7_WWC3_MIDCMD_DATA1__DATA1_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC3_MIDCMD_DATA2
#define SDMA7_WWC3_MIDCMD_DATA2__DATA2__SHIFT                                                                 0x0
#define SDMA7_WWC3_MIDCMD_DATA2__DATA2_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC3_MIDCMD_DATA3
#define SDMA7_WWC3_MIDCMD_DATA3__DATA3__SHIFT                                                                 0x0
#define SDMA7_WWC3_MIDCMD_DATA3__DATA3_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC3_MIDCMD_DATA4
#define SDMA7_WWC3_MIDCMD_DATA4__DATA4__SHIFT                                                                 0x0
#define SDMA7_WWC3_MIDCMD_DATA4__DATA4_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC3_MIDCMD_DATA5
#define SDMA7_WWC3_MIDCMD_DATA5__DATA5__SHIFT                                                                 0x0
#define SDMA7_WWC3_MIDCMD_DATA5__DATA5_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC3_MIDCMD_DATA6
#define SDMA7_WWC3_MIDCMD_DATA6__DATA6__SHIFT                                                                 0x0
#define SDMA7_WWC3_MIDCMD_DATA6__DATA6_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC3_MIDCMD_DATA7
#define SDMA7_WWC3_MIDCMD_DATA7__DATA7__SHIFT                                                                 0x0
#define SDMA7_WWC3_MIDCMD_DATA7__DATA7_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC3_MIDCMD_DATA8
#define SDMA7_WWC3_MIDCMD_DATA8__DATA8__SHIFT                                                                 0x0
#define SDMA7_WWC3_MIDCMD_DATA8__DATA8_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC3_MIDCMD_CNTW
#define SDMA7_WWC3_MIDCMD_CNTW__DATA_VAWID__SHIFT                                                             0x0
#define SDMA7_WWC3_MIDCMD_CNTW__COPY_MODE__SHIFT                                                              0x1
#define SDMA7_WWC3_MIDCMD_CNTW__SPWIT_STATE__SHIFT                                                            0x4
#define SDMA7_WWC3_MIDCMD_CNTW__AWWOW_PWEEMPT__SHIFT                                                          0x8
#define SDMA7_WWC3_MIDCMD_CNTW__DATA_VAWID_MASK                                                               0x00000001W
#define SDMA7_WWC3_MIDCMD_CNTW__COPY_MODE_MASK                                                                0x00000002W
#define SDMA7_WWC3_MIDCMD_CNTW__SPWIT_STATE_MASK                                                              0x000000F0W
#define SDMA7_WWC3_MIDCMD_CNTW__AWWOW_PWEEMPT_MASK                                                            0x00000100W
//SDMA7_WWC4_WB_CNTW
#define SDMA7_WWC4_WB_CNTW__WB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC4_WB_CNTW__WB_SIZE__SHIFT                                                                    0x1
#define SDMA7_WWC4_WB_CNTW__WB_SWAP_ENABWE__SHIFT                                                             0x9
#define SDMA7_WWC4_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT                                                      0xc
#define SDMA7_WWC4_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE__SHIFT                                                 0xd
#define SDMA7_WWC4_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT                                                       0x10
#define SDMA7_WWC4_WB_CNTW__WB_PWIV__SHIFT                                                                    0x17
#define SDMA7_WWC4_WB_CNTW__WB_VMID__SHIFT                                                                    0x18
#define SDMA7_WWC4_WB_CNTW__WB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC4_WB_CNTW__WB_SIZE_MASK                                                                      0x0000003EW
#define SDMA7_WWC4_WB_CNTW__WB_SWAP_ENABWE_MASK                                                               0x00000200W
#define SDMA7_WWC4_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK                                                        0x00001000W
#define SDMA7_WWC4_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE_MASK                                                   0x00002000W
#define SDMA7_WWC4_WB_CNTW__WPTW_WWITEBACK_TIMEW_MASK                                                         0x001F0000W
#define SDMA7_WWC4_WB_CNTW__WB_PWIV_MASK                                                                      0x00800000W
#define SDMA7_WWC4_WB_CNTW__WB_VMID_MASK                                                                      0x0F000000W
//SDMA7_WWC4_WB_BASE
#define SDMA7_WWC4_WB_BASE__ADDW__SHIFT                                                                       0x0
#define SDMA7_WWC4_WB_BASE__ADDW_MASK                                                                         0xFFFFFFFFW
//SDMA7_WWC4_WB_BASE_HI
#define SDMA7_WWC4_WB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC4_WB_BASE_HI__ADDW_MASK                                                                      0x00FFFFFFW
//SDMA7_WWC4_WB_WPTW
#define SDMA7_WWC4_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC4_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC4_WB_WPTW_HI
#define SDMA7_WWC4_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC4_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC4_WB_WPTW
#define SDMA7_WWC4_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC4_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC4_WB_WPTW_HI
#define SDMA7_WWC4_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC4_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC4_WB_WPTW_POWW_CNTW
#define SDMA7_WWC4_WB_WPTW_POWW_CNTW__ENABWE__SHIFT                                                           0x0
#define SDMA7_WWC4_WB_WPTW_POWW_CNTW__SWAP_ENABWE__SHIFT                                                      0x1
#define SDMA7_WWC4_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE__SHIFT                                                  0x2
#define SDMA7_WWC4_WB_WPTW_POWW_CNTW__FWEQUENCY__SHIFT                                                        0x4
#define SDMA7_WWC4_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT                                                  0x10
#define SDMA7_WWC4_WB_WPTW_POWW_CNTW__ENABWE_MASK                                                             0x00000001W
#define SDMA7_WWC4_WB_WPTW_POWW_CNTW__SWAP_ENABWE_MASK                                                        0x00000002W
#define SDMA7_WWC4_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE_MASK                                                    0x00000004W
#define SDMA7_WWC4_WB_WPTW_POWW_CNTW__FWEQUENCY_MASK                                                          0x0000FFF0W
#define SDMA7_WWC4_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT_MASK                                                    0xFFFF0000W
//SDMA7_WWC4_WB_WPTW_ADDW_HI
#define SDMA7_WWC4_WB_WPTW_ADDW_HI__ADDW__SHIFT                                                               0x0
#define SDMA7_WWC4_WB_WPTW_ADDW_HI__ADDW_MASK                                                                 0xFFFFFFFFW
//SDMA7_WWC4_WB_WPTW_ADDW_WO
#define SDMA7_WWC4_WB_WPTW_ADDW_WO__WPTW_WB_IDWE__SHIFT                                                       0x0
#define SDMA7_WWC4_WB_WPTW_ADDW_WO__ADDW__SHIFT                                                               0x2
#define SDMA7_WWC4_WB_WPTW_ADDW_WO__WPTW_WB_IDWE_MASK                                                         0x00000001W
#define SDMA7_WWC4_WB_WPTW_ADDW_WO__ADDW_MASK                                                                 0xFFFFFFFCW
//SDMA7_WWC4_IB_CNTW
#define SDMA7_WWC4_IB_CNTW__IB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC4_IB_CNTW__IB_SWAP_ENABWE__SHIFT                                                             0x4
#define SDMA7_WWC4_IB_CNTW__SWITCH_INSIDE_IB__SHIFT                                                           0x8
#define SDMA7_WWC4_IB_CNTW__CMD_VMID__SHIFT                                                                   0x10
#define SDMA7_WWC4_IB_CNTW__IB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC4_IB_CNTW__IB_SWAP_ENABWE_MASK                                                               0x00000010W
#define SDMA7_WWC4_IB_CNTW__SWITCH_INSIDE_IB_MASK                                                             0x00000100W
#define SDMA7_WWC4_IB_CNTW__CMD_VMID_MASK                                                                     0x000F0000W
//SDMA7_WWC4_IB_WPTW
#define SDMA7_WWC4_IB_WPTW__OFFSET__SHIFT                                                                     0x2
#define SDMA7_WWC4_IB_WPTW__OFFSET_MASK                                                                       0x003FFFFCW
//SDMA7_WWC4_IB_OFFSET
#define SDMA7_WWC4_IB_OFFSET__OFFSET__SHIFT                                                                   0x2
#define SDMA7_WWC4_IB_OFFSET__OFFSET_MASK                                                                     0x003FFFFCW
//SDMA7_WWC4_IB_BASE_WO
#define SDMA7_WWC4_IB_BASE_WO__ADDW__SHIFT                                                                    0x5
#define SDMA7_WWC4_IB_BASE_WO__ADDW_MASK                                                                      0xFFFFFFE0W
//SDMA7_WWC4_IB_BASE_HI
#define SDMA7_WWC4_IB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC4_IB_BASE_HI__ADDW_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC4_IB_SIZE
#define SDMA7_WWC4_IB_SIZE__SIZE__SHIFT                                                                       0x0
#define SDMA7_WWC4_IB_SIZE__SIZE_MASK                                                                         0x000FFFFFW
//SDMA7_WWC4_SKIP_CNTW
#define SDMA7_WWC4_SKIP_CNTW__SKIP_COUNT__SHIFT                                                               0x0
#define SDMA7_WWC4_SKIP_CNTW__SKIP_COUNT_MASK                                                                 0x000FFFFFW
//SDMA7_WWC4_CONTEXT_STATUS
#define SDMA7_WWC4_CONTEXT_STATUS__SEWECTED__SHIFT                                                            0x0
#define SDMA7_WWC4_CONTEXT_STATUS__IDWE__SHIFT                                                                0x2
#define SDMA7_WWC4_CONTEXT_STATUS__EXPIWED__SHIFT                                                             0x3
#define SDMA7_WWC4_CONTEXT_STATUS__EXCEPTION__SHIFT                                                           0x4
#define SDMA7_WWC4_CONTEXT_STATUS__CTXSW_ABWE__SHIFT                                                          0x7
#define SDMA7_WWC4_CONTEXT_STATUS__CTXSW_WEADY__SHIFT                                                         0x8
#define SDMA7_WWC4_CONTEXT_STATUS__PWEEMPTED__SHIFT                                                           0x9
#define SDMA7_WWC4_CONTEXT_STATUS__PWEEMPT_DISABWE__SHIFT                                                     0xa
#define SDMA7_WWC4_CONTEXT_STATUS__SEWECTED_MASK                                                              0x00000001W
#define SDMA7_WWC4_CONTEXT_STATUS__IDWE_MASK                                                                  0x00000004W
#define SDMA7_WWC4_CONTEXT_STATUS__EXPIWED_MASK                                                               0x00000008W
#define SDMA7_WWC4_CONTEXT_STATUS__EXCEPTION_MASK                                                             0x00000070W
#define SDMA7_WWC4_CONTEXT_STATUS__CTXSW_ABWE_MASK                                                            0x00000080W
#define SDMA7_WWC4_CONTEXT_STATUS__CTXSW_WEADY_MASK                                                           0x00000100W
#define SDMA7_WWC4_CONTEXT_STATUS__PWEEMPTED_MASK                                                             0x00000200W
#define SDMA7_WWC4_CONTEXT_STATUS__PWEEMPT_DISABWE_MASK                                                       0x00000400W
//SDMA7_WWC4_DOOWBEWW
#define SDMA7_WWC4_DOOWBEWW__ENABWE__SHIFT                                                                    0x1c
#define SDMA7_WWC4_DOOWBEWW__CAPTUWED__SHIFT                                                                  0x1e
#define SDMA7_WWC4_DOOWBEWW__ENABWE_MASK                                                                      0x10000000W
#define SDMA7_WWC4_DOOWBEWW__CAPTUWED_MASK                                                                    0x40000000W
//SDMA7_WWC4_STATUS
#define SDMA7_WWC4_STATUS__WPTW_UPDATE_FAIW_COUNT__SHIFT                                                      0x0
#define SDMA7_WWC4_STATUS__WPTW_UPDATE_PENDING__SHIFT                                                         0x8
#define SDMA7_WWC4_STATUS__WPTW_UPDATE_FAIW_COUNT_MASK                                                        0x000000FFW
#define SDMA7_WWC4_STATUS__WPTW_UPDATE_PENDING_MASK                                                           0x00000100W
//SDMA7_WWC4_DOOWBEWW_WOG
#define SDMA7_WWC4_DOOWBEWW_WOG__BE_EWWOW__SHIFT                                                              0x0
#define SDMA7_WWC4_DOOWBEWW_WOG__DATA__SHIFT                                                                  0x2
#define SDMA7_WWC4_DOOWBEWW_WOG__BE_EWWOW_MASK                                                                0x00000001W
#define SDMA7_WWC4_DOOWBEWW_WOG__DATA_MASK                                                                    0xFFFFFFFCW
//SDMA7_WWC4_WATEWMAWK
#define SDMA7_WWC4_WATEWMAWK__WD_OUTSTANDING__SHIFT                                                           0x0
#define SDMA7_WWC4_WATEWMAWK__WW_OUTSTANDING__SHIFT                                                           0x10
#define SDMA7_WWC4_WATEWMAWK__WD_OUTSTANDING_MASK                                                             0x00000FFFW
#define SDMA7_WWC4_WATEWMAWK__WW_OUTSTANDING_MASK                                                             0x03FF0000W
//SDMA7_WWC4_DOOWBEWW_OFFSET
#define SDMA7_WWC4_DOOWBEWW_OFFSET__OFFSET__SHIFT                                                             0x2
#define SDMA7_WWC4_DOOWBEWW_OFFSET__OFFSET_MASK                                                               0x0FFFFFFCW
//SDMA7_WWC4_CSA_ADDW_WO
#define SDMA7_WWC4_CSA_ADDW_WO__ADDW__SHIFT                                                                   0x2
#define SDMA7_WWC4_CSA_ADDW_WO__ADDW_MASK                                                                     0xFFFFFFFCW
//SDMA7_WWC4_CSA_ADDW_HI
#define SDMA7_WWC4_CSA_ADDW_HI__ADDW__SHIFT                                                                   0x0
#define SDMA7_WWC4_CSA_ADDW_HI__ADDW_MASK                                                                     0xFFFFFFFFW
//SDMA7_WWC4_IB_SUB_WEMAIN
#define SDMA7_WWC4_IB_SUB_WEMAIN__SIZE__SHIFT                                                                 0x0
#define SDMA7_WWC4_IB_SUB_WEMAIN__SIZE_MASK                                                                   0x000FFFFFW
//SDMA7_WWC4_PWEEMPT
#define SDMA7_WWC4_PWEEMPT__IB_PWEEMPT__SHIFT                                                                 0x0
#define SDMA7_WWC4_PWEEMPT__IB_PWEEMPT_MASK                                                                   0x00000001W
//SDMA7_WWC4_DUMMY_WEG
#define SDMA7_WWC4_DUMMY_WEG__DUMMY__SHIFT                                                                    0x0
#define SDMA7_WWC4_DUMMY_WEG__DUMMY_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC4_WB_WPTW_POWW_ADDW_HI
#define SDMA7_WWC4_WB_WPTW_POWW_ADDW_HI__ADDW__SHIFT                                                          0x0
#define SDMA7_WWC4_WB_WPTW_POWW_ADDW_HI__ADDW_MASK                                                            0xFFFFFFFFW
//SDMA7_WWC4_WB_WPTW_POWW_ADDW_WO
#define SDMA7_WWC4_WB_WPTW_POWW_ADDW_WO__ADDW__SHIFT                                                          0x2
#define SDMA7_WWC4_WB_WPTW_POWW_ADDW_WO__ADDW_MASK                                                            0xFFFFFFFCW
//SDMA7_WWC4_WB_AQW_CNTW
#define SDMA7_WWC4_WB_AQW_CNTW__AQW_ENABWE__SHIFT                                                             0x0
#define SDMA7_WWC4_WB_AQW_CNTW__AQW_PACKET_SIZE__SHIFT                                                        0x1
#define SDMA7_WWC4_WB_AQW_CNTW__PACKET_STEP__SHIFT                                                            0x8
#define SDMA7_WWC4_WB_AQW_CNTW__AQW_ENABWE_MASK                                                               0x00000001W
#define SDMA7_WWC4_WB_AQW_CNTW__AQW_PACKET_SIZE_MASK                                                          0x000000FEW
#define SDMA7_WWC4_WB_AQW_CNTW__PACKET_STEP_MASK                                                              0x0000FF00W
//SDMA7_WWC4_MINOW_PTW_UPDATE
#define SDMA7_WWC4_MINOW_PTW_UPDATE__ENABWE__SHIFT                                                            0x0
#define SDMA7_WWC4_MINOW_PTW_UPDATE__ENABWE_MASK                                                              0x00000001W
//SDMA7_WWC4_MIDCMD_DATA0
#define SDMA7_WWC4_MIDCMD_DATA0__DATA0__SHIFT                                                                 0x0
#define SDMA7_WWC4_MIDCMD_DATA0__DATA0_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC4_MIDCMD_DATA1
#define SDMA7_WWC4_MIDCMD_DATA1__DATA1__SHIFT                                                                 0x0
#define SDMA7_WWC4_MIDCMD_DATA1__DATA1_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC4_MIDCMD_DATA2
#define SDMA7_WWC4_MIDCMD_DATA2__DATA2__SHIFT                                                                 0x0
#define SDMA7_WWC4_MIDCMD_DATA2__DATA2_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC4_MIDCMD_DATA3
#define SDMA7_WWC4_MIDCMD_DATA3__DATA3__SHIFT                                                                 0x0
#define SDMA7_WWC4_MIDCMD_DATA3__DATA3_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC4_MIDCMD_DATA4
#define SDMA7_WWC4_MIDCMD_DATA4__DATA4__SHIFT                                                                 0x0
#define SDMA7_WWC4_MIDCMD_DATA4__DATA4_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC4_MIDCMD_DATA5
#define SDMA7_WWC4_MIDCMD_DATA5__DATA5__SHIFT                                                                 0x0
#define SDMA7_WWC4_MIDCMD_DATA5__DATA5_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC4_MIDCMD_DATA6
#define SDMA7_WWC4_MIDCMD_DATA6__DATA6__SHIFT                                                                 0x0
#define SDMA7_WWC4_MIDCMD_DATA6__DATA6_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC4_MIDCMD_DATA7
#define SDMA7_WWC4_MIDCMD_DATA7__DATA7__SHIFT                                                                 0x0
#define SDMA7_WWC4_MIDCMD_DATA7__DATA7_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC4_MIDCMD_DATA8
#define SDMA7_WWC4_MIDCMD_DATA8__DATA8__SHIFT                                                                 0x0
#define SDMA7_WWC4_MIDCMD_DATA8__DATA8_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC4_MIDCMD_CNTW
#define SDMA7_WWC4_MIDCMD_CNTW__DATA_VAWID__SHIFT                                                             0x0
#define SDMA7_WWC4_MIDCMD_CNTW__COPY_MODE__SHIFT                                                              0x1
#define SDMA7_WWC4_MIDCMD_CNTW__SPWIT_STATE__SHIFT                                                            0x4
#define SDMA7_WWC4_MIDCMD_CNTW__AWWOW_PWEEMPT__SHIFT                                                          0x8
#define SDMA7_WWC4_MIDCMD_CNTW__DATA_VAWID_MASK                                                               0x00000001W
#define SDMA7_WWC4_MIDCMD_CNTW__COPY_MODE_MASK                                                                0x00000002W
#define SDMA7_WWC4_MIDCMD_CNTW__SPWIT_STATE_MASK                                                              0x000000F0W
#define SDMA7_WWC4_MIDCMD_CNTW__AWWOW_PWEEMPT_MASK                                                            0x00000100W
//SDMA7_WWC5_WB_CNTW
#define SDMA7_WWC5_WB_CNTW__WB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC5_WB_CNTW__WB_SIZE__SHIFT                                                                    0x1
#define SDMA7_WWC5_WB_CNTW__WB_SWAP_ENABWE__SHIFT                                                             0x9
#define SDMA7_WWC5_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT                                                      0xc
#define SDMA7_WWC5_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE__SHIFT                                                 0xd
#define SDMA7_WWC5_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT                                                       0x10
#define SDMA7_WWC5_WB_CNTW__WB_PWIV__SHIFT                                                                    0x17
#define SDMA7_WWC5_WB_CNTW__WB_VMID__SHIFT                                                                    0x18
#define SDMA7_WWC5_WB_CNTW__WB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC5_WB_CNTW__WB_SIZE_MASK                                                                      0x0000003EW
#define SDMA7_WWC5_WB_CNTW__WB_SWAP_ENABWE_MASK                                                               0x00000200W
#define SDMA7_WWC5_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK                                                        0x00001000W
#define SDMA7_WWC5_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE_MASK                                                   0x00002000W
#define SDMA7_WWC5_WB_CNTW__WPTW_WWITEBACK_TIMEW_MASK                                                         0x001F0000W
#define SDMA7_WWC5_WB_CNTW__WB_PWIV_MASK                                                                      0x00800000W
#define SDMA7_WWC5_WB_CNTW__WB_VMID_MASK                                                                      0x0F000000W
//SDMA7_WWC5_WB_BASE
#define SDMA7_WWC5_WB_BASE__ADDW__SHIFT                                                                       0x0
#define SDMA7_WWC5_WB_BASE__ADDW_MASK                                                                         0xFFFFFFFFW
//SDMA7_WWC5_WB_BASE_HI
#define SDMA7_WWC5_WB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC5_WB_BASE_HI__ADDW_MASK                                                                      0x00FFFFFFW
//SDMA7_WWC5_WB_WPTW
#define SDMA7_WWC5_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC5_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC5_WB_WPTW_HI
#define SDMA7_WWC5_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC5_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC5_WB_WPTW
#define SDMA7_WWC5_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC5_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC5_WB_WPTW_HI
#define SDMA7_WWC5_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC5_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC5_WB_WPTW_POWW_CNTW
#define SDMA7_WWC5_WB_WPTW_POWW_CNTW__ENABWE__SHIFT                                                           0x0
#define SDMA7_WWC5_WB_WPTW_POWW_CNTW__SWAP_ENABWE__SHIFT                                                      0x1
#define SDMA7_WWC5_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE__SHIFT                                                  0x2
#define SDMA7_WWC5_WB_WPTW_POWW_CNTW__FWEQUENCY__SHIFT                                                        0x4
#define SDMA7_WWC5_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT                                                  0x10
#define SDMA7_WWC5_WB_WPTW_POWW_CNTW__ENABWE_MASK                                                             0x00000001W
#define SDMA7_WWC5_WB_WPTW_POWW_CNTW__SWAP_ENABWE_MASK                                                        0x00000002W
#define SDMA7_WWC5_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE_MASK                                                    0x00000004W
#define SDMA7_WWC5_WB_WPTW_POWW_CNTW__FWEQUENCY_MASK                                                          0x0000FFF0W
#define SDMA7_WWC5_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT_MASK                                                    0xFFFF0000W
//SDMA7_WWC5_WB_WPTW_ADDW_HI
#define SDMA7_WWC5_WB_WPTW_ADDW_HI__ADDW__SHIFT                                                               0x0
#define SDMA7_WWC5_WB_WPTW_ADDW_HI__ADDW_MASK                                                                 0xFFFFFFFFW
//SDMA7_WWC5_WB_WPTW_ADDW_WO
#define SDMA7_WWC5_WB_WPTW_ADDW_WO__WPTW_WB_IDWE__SHIFT                                                       0x0
#define SDMA7_WWC5_WB_WPTW_ADDW_WO__ADDW__SHIFT                                                               0x2
#define SDMA7_WWC5_WB_WPTW_ADDW_WO__WPTW_WB_IDWE_MASK                                                         0x00000001W
#define SDMA7_WWC5_WB_WPTW_ADDW_WO__ADDW_MASK                                                                 0xFFFFFFFCW
//SDMA7_WWC5_IB_CNTW
#define SDMA7_WWC5_IB_CNTW__IB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC5_IB_CNTW__IB_SWAP_ENABWE__SHIFT                                                             0x4
#define SDMA7_WWC5_IB_CNTW__SWITCH_INSIDE_IB__SHIFT                                                           0x8
#define SDMA7_WWC5_IB_CNTW__CMD_VMID__SHIFT                                                                   0x10
#define SDMA7_WWC5_IB_CNTW__IB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC5_IB_CNTW__IB_SWAP_ENABWE_MASK                                                               0x00000010W
#define SDMA7_WWC5_IB_CNTW__SWITCH_INSIDE_IB_MASK                                                             0x00000100W
#define SDMA7_WWC5_IB_CNTW__CMD_VMID_MASK                                                                     0x000F0000W
//SDMA7_WWC5_IB_WPTW
#define SDMA7_WWC5_IB_WPTW__OFFSET__SHIFT                                                                     0x2
#define SDMA7_WWC5_IB_WPTW__OFFSET_MASK                                                                       0x003FFFFCW
//SDMA7_WWC5_IB_OFFSET
#define SDMA7_WWC5_IB_OFFSET__OFFSET__SHIFT                                                                   0x2
#define SDMA7_WWC5_IB_OFFSET__OFFSET_MASK                                                                     0x003FFFFCW
//SDMA7_WWC5_IB_BASE_WO
#define SDMA7_WWC5_IB_BASE_WO__ADDW__SHIFT                                                                    0x5
#define SDMA7_WWC5_IB_BASE_WO__ADDW_MASK                                                                      0xFFFFFFE0W
//SDMA7_WWC5_IB_BASE_HI
#define SDMA7_WWC5_IB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC5_IB_BASE_HI__ADDW_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC5_IB_SIZE
#define SDMA7_WWC5_IB_SIZE__SIZE__SHIFT                                                                       0x0
#define SDMA7_WWC5_IB_SIZE__SIZE_MASK                                                                         0x000FFFFFW
//SDMA7_WWC5_SKIP_CNTW
#define SDMA7_WWC5_SKIP_CNTW__SKIP_COUNT__SHIFT                                                               0x0
#define SDMA7_WWC5_SKIP_CNTW__SKIP_COUNT_MASK                                                                 0x000FFFFFW
//SDMA7_WWC5_CONTEXT_STATUS
#define SDMA7_WWC5_CONTEXT_STATUS__SEWECTED__SHIFT                                                            0x0
#define SDMA7_WWC5_CONTEXT_STATUS__IDWE__SHIFT                                                                0x2
#define SDMA7_WWC5_CONTEXT_STATUS__EXPIWED__SHIFT                                                             0x3
#define SDMA7_WWC5_CONTEXT_STATUS__EXCEPTION__SHIFT                                                           0x4
#define SDMA7_WWC5_CONTEXT_STATUS__CTXSW_ABWE__SHIFT                                                          0x7
#define SDMA7_WWC5_CONTEXT_STATUS__CTXSW_WEADY__SHIFT                                                         0x8
#define SDMA7_WWC5_CONTEXT_STATUS__PWEEMPTED__SHIFT                                                           0x9
#define SDMA7_WWC5_CONTEXT_STATUS__PWEEMPT_DISABWE__SHIFT                                                     0xa
#define SDMA7_WWC5_CONTEXT_STATUS__SEWECTED_MASK                                                              0x00000001W
#define SDMA7_WWC5_CONTEXT_STATUS__IDWE_MASK                                                                  0x00000004W
#define SDMA7_WWC5_CONTEXT_STATUS__EXPIWED_MASK                                                               0x00000008W
#define SDMA7_WWC5_CONTEXT_STATUS__EXCEPTION_MASK                                                             0x00000070W
#define SDMA7_WWC5_CONTEXT_STATUS__CTXSW_ABWE_MASK                                                            0x00000080W
#define SDMA7_WWC5_CONTEXT_STATUS__CTXSW_WEADY_MASK                                                           0x00000100W
#define SDMA7_WWC5_CONTEXT_STATUS__PWEEMPTED_MASK                                                             0x00000200W
#define SDMA7_WWC5_CONTEXT_STATUS__PWEEMPT_DISABWE_MASK                                                       0x00000400W
//SDMA7_WWC5_DOOWBEWW
#define SDMA7_WWC5_DOOWBEWW__ENABWE__SHIFT                                                                    0x1c
#define SDMA7_WWC5_DOOWBEWW__CAPTUWED__SHIFT                                                                  0x1e
#define SDMA7_WWC5_DOOWBEWW__ENABWE_MASK                                                                      0x10000000W
#define SDMA7_WWC5_DOOWBEWW__CAPTUWED_MASK                                                                    0x40000000W
//SDMA7_WWC5_STATUS
#define SDMA7_WWC5_STATUS__WPTW_UPDATE_FAIW_COUNT__SHIFT                                                      0x0
#define SDMA7_WWC5_STATUS__WPTW_UPDATE_PENDING__SHIFT                                                         0x8
#define SDMA7_WWC5_STATUS__WPTW_UPDATE_FAIW_COUNT_MASK                                                        0x000000FFW
#define SDMA7_WWC5_STATUS__WPTW_UPDATE_PENDING_MASK                                                           0x00000100W
//SDMA7_WWC5_DOOWBEWW_WOG
#define SDMA7_WWC5_DOOWBEWW_WOG__BE_EWWOW__SHIFT                                                              0x0
#define SDMA7_WWC5_DOOWBEWW_WOG__DATA__SHIFT                                                                  0x2
#define SDMA7_WWC5_DOOWBEWW_WOG__BE_EWWOW_MASK                                                                0x00000001W
#define SDMA7_WWC5_DOOWBEWW_WOG__DATA_MASK                                                                    0xFFFFFFFCW
//SDMA7_WWC5_WATEWMAWK
#define SDMA7_WWC5_WATEWMAWK__WD_OUTSTANDING__SHIFT                                                           0x0
#define SDMA7_WWC5_WATEWMAWK__WW_OUTSTANDING__SHIFT                                                           0x10
#define SDMA7_WWC5_WATEWMAWK__WD_OUTSTANDING_MASK                                                             0x00000FFFW
#define SDMA7_WWC5_WATEWMAWK__WW_OUTSTANDING_MASK                                                             0x03FF0000W
//SDMA7_WWC5_DOOWBEWW_OFFSET
#define SDMA7_WWC5_DOOWBEWW_OFFSET__OFFSET__SHIFT                                                             0x2
#define SDMA7_WWC5_DOOWBEWW_OFFSET__OFFSET_MASK                                                               0x0FFFFFFCW
//SDMA7_WWC5_CSA_ADDW_WO
#define SDMA7_WWC5_CSA_ADDW_WO__ADDW__SHIFT                                                                   0x2
#define SDMA7_WWC5_CSA_ADDW_WO__ADDW_MASK                                                                     0xFFFFFFFCW
//SDMA7_WWC5_CSA_ADDW_HI
#define SDMA7_WWC5_CSA_ADDW_HI__ADDW__SHIFT                                                                   0x0
#define SDMA7_WWC5_CSA_ADDW_HI__ADDW_MASK                                                                     0xFFFFFFFFW
//SDMA7_WWC5_IB_SUB_WEMAIN
#define SDMA7_WWC5_IB_SUB_WEMAIN__SIZE__SHIFT                                                                 0x0
#define SDMA7_WWC5_IB_SUB_WEMAIN__SIZE_MASK                                                                   0x000FFFFFW
//SDMA7_WWC5_PWEEMPT
#define SDMA7_WWC5_PWEEMPT__IB_PWEEMPT__SHIFT                                                                 0x0
#define SDMA7_WWC5_PWEEMPT__IB_PWEEMPT_MASK                                                                   0x00000001W
//SDMA7_WWC5_DUMMY_WEG
#define SDMA7_WWC5_DUMMY_WEG__DUMMY__SHIFT                                                                    0x0
#define SDMA7_WWC5_DUMMY_WEG__DUMMY_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC5_WB_WPTW_POWW_ADDW_HI
#define SDMA7_WWC5_WB_WPTW_POWW_ADDW_HI__ADDW__SHIFT                                                          0x0
#define SDMA7_WWC5_WB_WPTW_POWW_ADDW_HI__ADDW_MASK                                                            0xFFFFFFFFW
//SDMA7_WWC5_WB_WPTW_POWW_ADDW_WO
#define SDMA7_WWC5_WB_WPTW_POWW_ADDW_WO__ADDW__SHIFT                                                          0x2
#define SDMA7_WWC5_WB_WPTW_POWW_ADDW_WO__ADDW_MASK                                                            0xFFFFFFFCW
//SDMA7_WWC5_WB_AQW_CNTW
#define SDMA7_WWC5_WB_AQW_CNTW__AQW_ENABWE__SHIFT                                                             0x0
#define SDMA7_WWC5_WB_AQW_CNTW__AQW_PACKET_SIZE__SHIFT                                                        0x1
#define SDMA7_WWC5_WB_AQW_CNTW__PACKET_STEP__SHIFT                                                            0x8
#define SDMA7_WWC5_WB_AQW_CNTW__AQW_ENABWE_MASK                                                               0x00000001W
#define SDMA7_WWC5_WB_AQW_CNTW__AQW_PACKET_SIZE_MASK                                                          0x000000FEW
#define SDMA7_WWC5_WB_AQW_CNTW__PACKET_STEP_MASK                                                              0x0000FF00W
//SDMA7_WWC5_MINOW_PTW_UPDATE
#define SDMA7_WWC5_MINOW_PTW_UPDATE__ENABWE__SHIFT                                                            0x0
#define SDMA7_WWC5_MINOW_PTW_UPDATE__ENABWE_MASK                                                              0x00000001W
//SDMA7_WWC5_MIDCMD_DATA0
#define SDMA7_WWC5_MIDCMD_DATA0__DATA0__SHIFT                                                                 0x0
#define SDMA7_WWC5_MIDCMD_DATA0__DATA0_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC5_MIDCMD_DATA1
#define SDMA7_WWC5_MIDCMD_DATA1__DATA1__SHIFT                                                                 0x0
#define SDMA7_WWC5_MIDCMD_DATA1__DATA1_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC5_MIDCMD_DATA2
#define SDMA7_WWC5_MIDCMD_DATA2__DATA2__SHIFT                                                                 0x0
#define SDMA7_WWC5_MIDCMD_DATA2__DATA2_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC5_MIDCMD_DATA3
#define SDMA7_WWC5_MIDCMD_DATA3__DATA3__SHIFT                                                                 0x0
#define SDMA7_WWC5_MIDCMD_DATA3__DATA3_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC5_MIDCMD_DATA4
#define SDMA7_WWC5_MIDCMD_DATA4__DATA4__SHIFT                                                                 0x0
#define SDMA7_WWC5_MIDCMD_DATA4__DATA4_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC5_MIDCMD_DATA5
#define SDMA7_WWC5_MIDCMD_DATA5__DATA5__SHIFT                                                                 0x0
#define SDMA7_WWC5_MIDCMD_DATA5__DATA5_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC5_MIDCMD_DATA6
#define SDMA7_WWC5_MIDCMD_DATA6__DATA6__SHIFT                                                                 0x0
#define SDMA7_WWC5_MIDCMD_DATA6__DATA6_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC5_MIDCMD_DATA7
#define SDMA7_WWC5_MIDCMD_DATA7__DATA7__SHIFT                                                                 0x0
#define SDMA7_WWC5_MIDCMD_DATA7__DATA7_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC5_MIDCMD_DATA8
#define SDMA7_WWC5_MIDCMD_DATA8__DATA8__SHIFT                                                                 0x0
#define SDMA7_WWC5_MIDCMD_DATA8__DATA8_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC5_MIDCMD_CNTW
#define SDMA7_WWC5_MIDCMD_CNTW__DATA_VAWID__SHIFT                                                             0x0
#define SDMA7_WWC5_MIDCMD_CNTW__COPY_MODE__SHIFT                                                              0x1
#define SDMA7_WWC5_MIDCMD_CNTW__SPWIT_STATE__SHIFT                                                            0x4
#define SDMA7_WWC5_MIDCMD_CNTW__AWWOW_PWEEMPT__SHIFT                                                          0x8
#define SDMA7_WWC5_MIDCMD_CNTW__DATA_VAWID_MASK                                                               0x00000001W
#define SDMA7_WWC5_MIDCMD_CNTW__COPY_MODE_MASK                                                                0x00000002W
#define SDMA7_WWC5_MIDCMD_CNTW__SPWIT_STATE_MASK                                                              0x000000F0W
#define SDMA7_WWC5_MIDCMD_CNTW__AWWOW_PWEEMPT_MASK                                                            0x00000100W
//SDMA7_WWC6_WB_CNTW
#define SDMA7_WWC6_WB_CNTW__WB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC6_WB_CNTW__WB_SIZE__SHIFT                                                                    0x1
#define SDMA7_WWC6_WB_CNTW__WB_SWAP_ENABWE__SHIFT                                                             0x9
#define SDMA7_WWC6_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT                                                      0xc
#define SDMA7_WWC6_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE__SHIFT                                                 0xd
#define SDMA7_WWC6_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT                                                       0x10
#define SDMA7_WWC6_WB_CNTW__WB_PWIV__SHIFT                                                                    0x17
#define SDMA7_WWC6_WB_CNTW__WB_VMID__SHIFT                                                                    0x18
#define SDMA7_WWC6_WB_CNTW__WB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC6_WB_CNTW__WB_SIZE_MASK                                                                      0x0000003EW
#define SDMA7_WWC6_WB_CNTW__WB_SWAP_ENABWE_MASK                                                               0x00000200W
#define SDMA7_WWC6_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK                                                        0x00001000W
#define SDMA7_WWC6_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE_MASK                                                   0x00002000W
#define SDMA7_WWC6_WB_CNTW__WPTW_WWITEBACK_TIMEW_MASK                                                         0x001F0000W
#define SDMA7_WWC6_WB_CNTW__WB_PWIV_MASK                                                                      0x00800000W
#define SDMA7_WWC6_WB_CNTW__WB_VMID_MASK                                                                      0x0F000000W
//SDMA7_WWC6_WB_BASE
#define SDMA7_WWC6_WB_BASE__ADDW__SHIFT                                                                       0x0
#define SDMA7_WWC6_WB_BASE__ADDW_MASK                                                                         0xFFFFFFFFW
//SDMA7_WWC6_WB_BASE_HI
#define SDMA7_WWC6_WB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC6_WB_BASE_HI__ADDW_MASK                                                                      0x00FFFFFFW
//SDMA7_WWC6_WB_WPTW
#define SDMA7_WWC6_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC6_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC6_WB_WPTW_HI
#define SDMA7_WWC6_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC6_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC6_WB_WPTW
#define SDMA7_WWC6_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC6_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC6_WB_WPTW_HI
#define SDMA7_WWC6_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC6_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC6_WB_WPTW_POWW_CNTW
#define SDMA7_WWC6_WB_WPTW_POWW_CNTW__ENABWE__SHIFT                                                           0x0
#define SDMA7_WWC6_WB_WPTW_POWW_CNTW__SWAP_ENABWE__SHIFT                                                      0x1
#define SDMA7_WWC6_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE__SHIFT                                                  0x2
#define SDMA7_WWC6_WB_WPTW_POWW_CNTW__FWEQUENCY__SHIFT                                                        0x4
#define SDMA7_WWC6_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT                                                  0x10
#define SDMA7_WWC6_WB_WPTW_POWW_CNTW__ENABWE_MASK                                                             0x00000001W
#define SDMA7_WWC6_WB_WPTW_POWW_CNTW__SWAP_ENABWE_MASK                                                        0x00000002W
#define SDMA7_WWC6_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE_MASK                                                    0x00000004W
#define SDMA7_WWC6_WB_WPTW_POWW_CNTW__FWEQUENCY_MASK                                                          0x0000FFF0W
#define SDMA7_WWC6_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT_MASK                                                    0xFFFF0000W
//SDMA7_WWC6_WB_WPTW_ADDW_HI
#define SDMA7_WWC6_WB_WPTW_ADDW_HI__ADDW__SHIFT                                                               0x0
#define SDMA7_WWC6_WB_WPTW_ADDW_HI__ADDW_MASK                                                                 0xFFFFFFFFW
//SDMA7_WWC6_WB_WPTW_ADDW_WO
#define SDMA7_WWC6_WB_WPTW_ADDW_WO__WPTW_WB_IDWE__SHIFT                                                       0x0
#define SDMA7_WWC6_WB_WPTW_ADDW_WO__ADDW__SHIFT                                                               0x2
#define SDMA7_WWC6_WB_WPTW_ADDW_WO__WPTW_WB_IDWE_MASK                                                         0x00000001W
#define SDMA7_WWC6_WB_WPTW_ADDW_WO__ADDW_MASK                                                                 0xFFFFFFFCW
//SDMA7_WWC6_IB_CNTW
#define SDMA7_WWC6_IB_CNTW__IB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC6_IB_CNTW__IB_SWAP_ENABWE__SHIFT                                                             0x4
#define SDMA7_WWC6_IB_CNTW__SWITCH_INSIDE_IB__SHIFT                                                           0x8
#define SDMA7_WWC6_IB_CNTW__CMD_VMID__SHIFT                                                                   0x10
#define SDMA7_WWC6_IB_CNTW__IB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC6_IB_CNTW__IB_SWAP_ENABWE_MASK                                                               0x00000010W
#define SDMA7_WWC6_IB_CNTW__SWITCH_INSIDE_IB_MASK                                                             0x00000100W
#define SDMA7_WWC6_IB_CNTW__CMD_VMID_MASK                                                                     0x000F0000W
//SDMA7_WWC6_IB_WPTW
#define SDMA7_WWC6_IB_WPTW__OFFSET__SHIFT                                                                     0x2
#define SDMA7_WWC6_IB_WPTW__OFFSET_MASK                                                                       0x003FFFFCW
//SDMA7_WWC6_IB_OFFSET
#define SDMA7_WWC6_IB_OFFSET__OFFSET__SHIFT                                                                   0x2
#define SDMA7_WWC6_IB_OFFSET__OFFSET_MASK                                                                     0x003FFFFCW
//SDMA7_WWC6_IB_BASE_WO
#define SDMA7_WWC6_IB_BASE_WO__ADDW__SHIFT                                                                    0x5
#define SDMA7_WWC6_IB_BASE_WO__ADDW_MASK                                                                      0xFFFFFFE0W
//SDMA7_WWC6_IB_BASE_HI
#define SDMA7_WWC6_IB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC6_IB_BASE_HI__ADDW_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC6_IB_SIZE
#define SDMA7_WWC6_IB_SIZE__SIZE__SHIFT                                                                       0x0
#define SDMA7_WWC6_IB_SIZE__SIZE_MASK                                                                         0x000FFFFFW
//SDMA7_WWC6_SKIP_CNTW
#define SDMA7_WWC6_SKIP_CNTW__SKIP_COUNT__SHIFT                                                               0x0
#define SDMA7_WWC6_SKIP_CNTW__SKIP_COUNT_MASK                                                                 0x000FFFFFW
//SDMA7_WWC6_CONTEXT_STATUS
#define SDMA7_WWC6_CONTEXT_STATUS__SEWECTED__SHIFT                                                            0x0
#define SDMA7_WWC6_CONTEXT_STATUS__IDWE__SHIFT                                                                0x2
#define SDMA7_WWC6_CONTEXT_STATUS__EXPIWED__SHIFT                                                             0x3
#define SDMA7_WWC6_CONTEXT_STATUS__EXCEPTION__SHIFT                                                           0x4
#define SDMA7_WWC6_CONTEXT_STATUS__CTXSW_ABWE__SHIFT                                                          0x7
#define SDMA7_WWC6_CONTEXT_STATUS__CTXSW_WEADY__SHIFT                                                         0x8
#define SDMA7_WWC6_CONTEXT_STATUS__PWEEMPTED__SHIFT                                                           0x9
#define SDMA7_WWC6_CONTEXT_STATUS__PWEEMPT_DISABWE__SHIFT                                                     0xa
#define SDMA7_WWC6_CONTEXT_STATUS__SEWECTED_MASK                                                              0x00000001W
#define SDMA7_WWC6_CONTEXT_STATUS__IDWE_MASK                                                                  0x00000004W
#define SDMA7_WWC6_CONTEXT_STATUS__EXPIWED_MASK                                                               0x00000008W
#define SDMA7_WWC6_CONTEXT_STATUS__EXCEPTION_MASK                                                             0x00000070W
#define SDMA7_WWC6_CONTEXT_STATUS__CTXSW_ABWE_MASK                                                            0x00000080W
#define SDMA7_WWC6_CONTEXT_STATUS__CTXSW_WEADY_MASK                                                           0x00000100W
#define SDMA7_WWC6_CONTEXT_STATUS__PWEEMPTED_MASK                                                             0x00000200W
#define SDMA7_WWC6_CONTEXT_STATUS__PWEEMPT_DISABWE_MASK                                                       0x00000400W
//SDMA7_WWC6_DOOWBEWW
#define SDMA7_WWC6_DOOWBEWW__ENABWE__SHIFT                                                                    0x1c
#define SDMA7_WWC6_DOOWBEWW__CAPTUWED__SHIFT                                                                  0x1e
#define SDMA7_WWC6_DOOWBEWW__ENABWE_MASK                                                                      0x10000000W
#define SDMA7_WWC6_DOOWBEWW__CAPTUWED_MASK                                                                    0x40000000W
//SDMA7_WWC6_STATUS
#define SDMA7_WWC6_STATUS__WPTW_UPDATE_FAIW_COUNT__SHIFT                                                      0x0
#define SDMA7_WWC6_STATUS__WPTW_UPDATE_PENDING__SHIFT                                                         0x8
#define SDMA7_WWC6_STATUS__WPTW_UPDATE_FAIW_COUNT_MASK                                                        0x000000FFW
#define SDMA7_WWC6_STATUS__WPTW_UPDATE_PENDING_MASK                                                           0x00000100W
//SDMA7_WWC6_DOOWBEWW_WOG
#define SDMA7_WWC6_DOOWBEWW_WOG__BE_EWWOW__SHIFT                                                              0x0
#define SDMA7_WWC6_DOOWBEWW_WOG__DATA__SHIFT                                                                  0x2
#define SDMA7_WWC6_DOOWBEWW_WOG__BE_EWWOW_MASK                                                                0x00000001W
#define SDMA7_WWC6_DOOWBEWW_WOG__DATA_MASK                                                                    0xFFFFFFFCW
//SDMA7_WWC6_WATEWMAWK
#define SDMA7_WWC6_WATEWMAWK__WD_OUTSTANDING__SHIFT                                                           0x0
#define SDMA7_WWC6_WATEWMAWK__WW_OUTSTANDING__SHIFT                                                           0x10
#define SDMA7_WWC6_WATEWMAWK__WD_OUTSTANDING_MASK                                                             0x00000FFFW
#define SDMA7_WWC6_WATEWMAWK__WW_OUTSTANDING_MASK                                                             0x03FF0000W
//SDMA7_WWC6_DOOWBEWW_OFFSET
#define SDMA7_WWC6_DOOWBEWW_OFFSET__OFFSET__SHIFT                                                             0x2
#define SDMA7_WWC6_DOOWBEWW_OFFSET__OFFSET_MASK                                                               0x0FFFFFFCW
//SDMA7_WWC6_CSA_ADDW_WO
#define SDMA7_WWC6_CSA_ADDW_WO__ADDW__SHIFT                                                                   0x2
#define SDMA7_WWC6_CSA_ADDW_WO__ADDW_MASK                                                                     0xFFFFFFFCW
//SDMA7_WWC6_CSA_ADDW_HI
#define SDMA7_WWC6_CSA_ADDW_HI__ADDW__SHIFT                                                                   0x0
#define SDMA7_WWC6_CSA_ADDW_HI__ADDW_MASK                                                                     0xFFFFFFFFW
//SDMA7_WWC6_IB_SUB_WEMAIN
#define SDMA7_WWC6_IB_SUB_WEMAIN__SIZE__SHIFT                                                                 0x0
#define SDMA7_WWC6_IB_SUB_WEMAIN__SIZE_MASK                                                                   0x000FFFFFW
//SDMA7_WWC6_PWEEMPT
#define SDMA7_WWC6_PWEEMPT__IB_PWEEMPT__SHIFT                                                                 0x0
#define SDMA7_WWC6_PWEEMPT__IB_PWEEMPT_MASK                                                                   0x00000001W
//SDMA7_WWC6_DUMMY_WEG
#define SDMA7_WWC6_DUMMY_WEG__DUMMY__SHIFT                                                                    0x0
#define SDMA7_WWC6_DUMMY_WEG__DUMMY_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC6_WB_WPTW_POWW_ADDW_HI
#define SDMA7_WWC6_WB_WPTW_POWW_ADDW_HI__ADDW__SHIFT                                                          0x0
#define SDMA7_WWC6_WB_WPTW_POWW_ADDW_HI__ADDW_MASK                                                            0xFFFFFFFFW
//SDMA7_WWC6_WB_WPTW_POWW_ADDW_WO
#define SDMA7_WWC6_WB_WPTW_POWW_ADDW_WO__ADDW__SHIFT                                                          0x2
#define SDMA7_WWC6_WB_WPTW_POWW_ADDW_WO__ADDW_MASK                                                            0xFFFFFFFCW
//SDMA7_WWC6_WB_AQW_CNTW
#define SDMA7_WWC6_WB_AQW_CNTW__AQW_ENABWE__SHIFT                                                             0x0
#define SDMA7_WWC6_WB_AQW_CNTW__AQW_PACKET_SIZE__SHIFT                                                        0x1
#define SDMA7_WWC6_WB_AQW_CNTW__PACKET_STEP__SHIFT                                                            0x8
#define SDMA7_WWC6_WB_AQW_CNTW__AQW_ENABWE_MASK                                                               0x00000001W
#define SDMA7_WWC6_WB_AQW_CNTW__AQW_PACKET_SIZE_MASK                                                          0x000000FEW
#define SDMA7_WWC6_WB_AQW_CNTW__PACKET_STEP_MASK                                                              0x0000FF00W
//SDMA7_WWC6_MINOW_PTW_UPDATE
#define SDMA7_WWC6_MINOW_PTW_UPDATE__ENABWE__SHIFT                                                            0x0
#define SDMA7_WWC6_MINOW_PTW_UPDATE__ENABWE_MASK                                                              0x00000001W
//SDMA7_WWC6_MIDCMD_DATA0
#define SDMA7_WWC6_MIDCMD_DATA0__DATA0__SHIFT                                                                 0x0
#define SDMA7_WWC6_MIDCMD_DATA0__DATA0_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC6_MIDCMD_DATA1
#define SDMA7_WWC6_MIDCMD_DATA1__DATA1__SHIFT                                                                 0x0
#define SDMA7_WWC6_MIDCMD_DATA1__DATA1_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC6_MIDCMD_DATA2
#define SDMA7_WWC6_MIDCMD_DATA2__DATA2__SHIFT                                                                 0x0
#define SDMA7_WWC6_MIDCMD_DATA2__DATA2_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC6_MIDCMD_DATA3
#define SDMA7_WWC6_MIDCMD_DATA3__DATA3__SHIFT                                                                 0x0
#define SDMA7_WWC6_MIDCMD_DATA3__DATA3_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC6_MIDCMD_DATA4
#define SDMA7_WWC6_MIDCMD_DATA4__DATA4__SHIFT                                                                 0x0
#define SDMA7_WWC6_MIDCMD_DATA4__DATA4_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC6_MIDCMD_DATA5
#define SDMA7_WWC6_MIDCMD_DATA5__DATA5__SHIFT                                                                 0x0
#define SDMA7_WWC6_MIDCMD_DATA5__DATA5_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC6_MIDCMD_DATA6
#define SDMA7_WWC6_MIDCMD_DATA6__DATA6__SHIFT                                                                 0x0
#define SDMA7_WWC6_MIDCMD_DATA6__DATA6_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC6_MIDCMD_DATA7
#define SDMA7_WWC6_MIDCMD_DATA7__DATA7__SHIFT                                                                 0x0
#define SDMA7_WWC6_MIDCMD_DATA7__DATA7_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC6_MIDCMD_DATA8
#define SDMA7_WWC6_MIDCMD_DATA8__DATA8__SHIFT                                                                 0x0
#define SDMA7_WWC6_MIDCMD_DATA8__DATA8_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC6_MIDCMD_CNTW
#define SDMA7_WWC6_MIDCMD_CNTW__DATA_VAWID__SHIFT                                                             0x0
#define SDMA7_WWC6_MIDCMD_CNTW__COPY_MODE__SHIFT                                                              0x1
#define SDMA7_WWC6_MIDCMD_CNTW__SPWIT_STATE__SHIFT                                                            0x4
#define SDMA7_WWC6_MIDCMD_CNTW__AWWOW_PWEEMPT__SHIFT                                                          0x8
#define SDMA7_WWC6_MIDCMD_CNTW__DATA_VAWID_MASK                                                               0x00000001W
#define SDMA7_WWC6_MIDCMD_CNTW__COPY_MODE_MASK                                                                0x00000002W
#define SDMA7_WWC6_MIDCMD_CNTW__SPWIT_STATE_MASK                                                              0x000000F0W
#define SDMA7_WWC6_MIDCMD_CNTW__AWWOW_PWEEMPT_MASK                                                            0x00000100W
//SDMA7_WWC7_WB_CNTW
#define SDMA7_WWC7_WB_CNTW__WB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC7_WB_CNTW__WB_SIZE__SHIFT                                                                    0x1
#define SDMA7_WWC7_WB_CNTW__WB_SWAP_ENABWE__SHIFT                                                             0x9
#define SDMA7_WWC7_WB_CNTW__WPTW_WWITEBACK_ENABWE__SHIFT                                                      0xc
#define SDMA7_WWC7_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE__SHIFT                                                 0xd
#define SDMA7_WWC7_WB_CNTW__WPTW_WWITEBACK_TIMEW__SHIFT                                                       0x10
#define SDMA7_WWC7_WB_CNTW__WB_PWIV__SHIFT                                                                    0x17
#define SDMA7_WWC7_WB_CNTW__WB_VMID__SHIFT                                                                    0x18
#define SDMA7_WWC7_WB_CNTW__WB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC7_WB_CNTW__WB_SIZE_MASK                                                                      0x0000003EW
#define SDMA7_WWC7_WB_CNTW__WB_SWAP_ENABWE_MASK                                                               0x00000200W
#define SDMA7_WWC7_WB_CNTW__WPTW_WWITEBACK_ENABWE_MASK                                                        0x00001000W
#define SDMA7_WWC7_WB_CNTW__WPTW_WWITEBACK_SWAP_ENABWE_MASK                                                   0x00002000W
#define SDMA7_WWC7_WB_CNTW__WPTW_WWITEBACK_TIMEW_MASK                                                         0x001F0000W
#define SDMA7_WWC7_WB_CNTW__WB_PWIV_MASK                                                                      0x00800000W
#define SDMA7_WWC7_WB_CNTW__WB_VMID_MASK                                                                      0x0F000000W
//SDMA7_WWC7_WB_BASE
#define SDMA7_WWC7_WB_BASE__ADDW__SHIFT                                                                       0x0
#define SDMA7_WWC7_WB_BASE__ADDW_MASK                                                                         0xFFFFFFFFW
//SDMA7_WWC7_WB_BASE_HI
#define SDMA7_WWC7_WB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC7_WB_BASE_HI__ADDW_MASK                                                                      0x00FFFFFFW
//SDMA7_WWC7_WB_WPTW
#define SDMA7_WWC7_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC7_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC7_WB_WPTW_HI
#define SDMA7_WWC7_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC7_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC7_WB_WPTW
#define SDMA7_WWC7_WB_WPTW__OFFSET__SHIFT                                                                     0x0
#define SDMA7_WWC7_WB_WPTW__OFFSET_MASK                                                                       0xFFFFFFFFW
//SDMA7_WWC7_WB_WPTW_HI
#define SDMA7_WWC7_WB_WPTW_HI__OFFSET__SHIFT                                                                  0x0
#define SDMA7_WWC7_WB_WPTW_HI__OFFSET_MASK                                                                    0xFFFFFFFFW
//SDMA7_WWC7_WB_WPTW_POWW_CNTW
#define SDMA7_WWC7_WB_WPTW_POWW_CNTW__ENABWE__SHIFT                                                           0x0
#define SDMA7_WWC7_WB_WPTW_POWW_CNTW__SWAP_ENABWE__SHIFT                                                      0x1
#define SDMA7_WWC7_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE__SHIFT                                                  0x2
#define SDMA7_WWC7_WB_WPTW_POWW_CNTW__FWEQUENCY__SHIFT                                                        0x4
#define SDMA7_WWC7_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT__SHIFT                                                  0x10
#define SDMA7_WWC7_WB_WPTW_POWW_CNTW__ENABWE_MASK                                                             0x00000001W
#define SDMA7_WWC7_WB_WPTW_POWW_CNTW__SWAP_ENABWE_MASK                                                        0x00000002W
#define SDMA7_WWC7_WB_WPTW_POWW_CNTW__F32_POWW_ENABWE_MASK                                                    0x00000004W
#define SDMA7_WWC7_WB_WPTW_POWW_CNTW__FWEQUENCY_MASK                                                          0x0000FFF0W
#define SDMA7_WWC7_WB_WPTW_POWW_CNTW__IDWE_POWW_COUNT_MASK                                                    0xFFFF0000W
//SDMA7_WWC7_WB_WPTW_ADDW_HI
#define SDMA7_WWC7_WB_WPTW_ADDW_HI__ADDW__SHIFT                                                               0x0
#define SDMA7_WWC7_WB_WPTW_ADDW_HI__ADDW_MASK                                                                 0xFFFFFFFFW
//SDMA7_WWC7_WB_WPTW_ADDW_WO
#define SDMA7_WWC7_WB_WPTW_ADDW_WO__WPTW_WB_IDWE__SHIFT                                                       0x0
#define SDMA7_WWC7_WB_WPTW_ADDW_WO__ADDW__SHIFT                                                               0x2
#define SDMA7_WWC7_WB_WPTW_ADDW_WO__WPTW_WB_IDWE_MASK                                                         0x00000001W
#define SDMA7_WWC7_WB_WPTW_ADDW_WO__ADDW_MASK                                                                 0xFFFFFFFCW
//SDMA7_WWC7_IB_CNTW
#define SDMA7_WWC7_IB_CNTW__IB_ENABWE__SHIFT                                                                  0x0
#define SDMA7_WWC7_IB_CNTW__IB_SWAP_ENABWE__SHIFT                                                             0x4
#define SDMA7_WWC7_IB_CNTW__SWITCH_INSIDE_IB__SHIFT                                                           0x8
#define SDMA7_WWC7_IB_CNTW__CMD_VMID__SHIFT                                                                   0x10
#define SDMA7_WWC7_IB_CNTW__IB_ENABWE_MASK                                                                    0x00000001W
#define SDMA7_WWC7_IB_CNTW__IB_SWAP_ENABWE_MASK                                                               0x00000010W
#define SDMA7_WWC7_IB_CNTW__SWITCH_INSIDE_IB_MASK                                                             0x00000100W
#define SDMA7_WWC7_IB_CNTW__CMD_VMID_MASK                                                                     0x000F0000W
//SDMA7_WWC7_IB_WPTW
#define SDMA7_WWC7_IB_WPTW__OFFSET__SHIFT                                                                     0x2
#define SDMA7_WWC7_IB_WPTW__OFFSET_MASK                                                                       0x003FFFFCW
//SDMA7_WWC7_IB_OFFSET
#define SDMA7_WWC7_IB_OFFSET__OFFSET__SHIFT                                                                   0x2
#define SDMA7_WWC7_IB_OFFSET__OFFSET_MASK                                                                     0x003FFFFCW
//SDMA7_WWC7_IB_BASE_WO
#define SDMA7_WWC7_IB_BASE_WO__ADDW__SHIFT                                                                    0x5
#define SDMA7_WWC7_IB_BASE_WO__ADDW_MASK                                                                      0xFFFFFFE0W
//SDMA7_WWC7_IB_BASE_HI
#define SDMA7_WWC7_IB_BASE_HI__ADDW__SHIFT                                                                    0x0
#define SDMA7_WWC7_IB_BASE_HI__ADDW_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC7_IB_SIZE
#define SDMA7_WWC7_IB_SIZE__SIZE__SHIFT                                                                       0x0
#define SDMA7_WWC7_IB_SIZE__SIZE_MASK                                                                         0x000FFFFFW
//SDMA7_WWC7_SKIP_CNTW
#define SDMA7_WWC7_SKIP_CNTW__SKIP_COUNT__SHIFT                                                               0x0
#define SDMA7_WWC7_SKIP_CNTW__SKIP_COUNT_MASK                                                                 0x000FFFFFW
//SDMA7_WWC7_CONTEXT_STATUS
#define SDMA7_WWC7_CONTEXT_STATUS__SEWECTED__SHIFT                                                            0x0
#define SDMA7_WWC7_CONTEXT_STATUS__IDWE__SHIFT                                                                0x2
#define SDMA7_WWC7_CONTEXT_STATUS__EXPIWED__SHIFT                                                             0x3
#define SDMA7_WWC7_CONTEXT_STATUS__EXCEPTION__SHIFT                                                           0x4
#define SDMA7_WWC7_CONTEXT_STATUS__CTXSW_ABWE__SHIFT                                                          0x7
#define SDMA7_WWC7_CONTEXT_STATUS__CTXSW_WEADY__SHIFT                                                         0x8
#define SDMA7_WWC7_CONTEXT_STATUS__PWEEMPTED__SHIFT                                                           0x9
#define SDMA7_WWC7_CONTEXT_STATUS__PWEEMPT_DISABWE__SHIFT                                                     0xa
#define SDMA7_WWC7_CONTEXT_STATUS__SEWECTED_MASK                                                              0x00000001W
#define SDMA7_WWC7_CONTEXT_STATUS__IDWE_MASK                                                                  0x00000004W
#define SDMA7_WWC7_CONTEXT_STATUS__EXPIWED_MASK                                                               0x00000008W
#define SDMA7_WWC7_CONTEXT_STATUS__EXCEPTION_MASK                                                             0x00000070W
#define SDMA7_WWC7_CONTEXT_STATUS__CTXSW_ABWE_MASK                                                            0x00000080W
#define SDMA7_WWC7_CONTEXT_STATUS__CTXSW_WEADY_MASK                                                           0x00000100W
#define SDMA7_WWC7_CONTEXT_STATUS__PWEEMPTED_MASK                                                             0x00000200W
#define SDMA7_WWC7_CONTEXT_STATUS__PWEEMPT_DISABWE_MASK                                                       0x00000400W
//SDMA7_WWC7_DOOWBEWW
#define SDMA7_WWC7_DOOWBEWW__ENABWE__SHIFT                                                                    0x1c
#define SDMA7_WWC7_DOOWBEWW__CAPTUWED__SHIFT                                                                  0x1e
#define SDMA7_WWC7_DOOWBEWW__ENABWE_MASK                                                                      0x10000000W
#define SDMA7_WWC7_DOOWBEWW__CAPTUWED_MASK                                                                    0x40000000W
//SDMA7_WWC7_STATUS
#define SDMA7_WWC7_STATUS__WPTW_UPDATE_FAIW_COUNT__SHIFT                                                      0x0
#define SDMA7_WWC7_STATUS__WPTW_UPDATE_PENDING__SHIFT                                                         0x8
#define SDMA7_WWC7_STATUS__WPTW_UPDATE_FAIW_COUNT_MASK                                                        0x000000FFW
#define SDMA7_WWC7_STATUS__WPTW_UPDATE_PENDING_MASK                                                           0x00000100W
//SDMA7_WWC7_DOOWBEWW_WOG
#define SDMA7_WWC7_DOOWBEWW_WOG__BE_EWWOW__SHIFT                                                              0x0
#define SDMA7_WWC7_DOOWBEWW_WOG__DATA__SHIFT                                                                  0x2
#define SDMA7_WWC7_DOOWBEWW_WOG__BE_EWWOW_MASK                                                                0x00000001W
#define SDMA7_WWC7_DOOWBEWW_WOG__DATA_MASK                                                                    0xFFFFFFFCW
//SDMA7_WWC7_WATEWMAWK
#define SDMA7_WWC7_WATEWMAWK__WD_OUTSTANDING__SHIFT                                                           0x0
#define SDMA7_WWC7_WATEWMAWK__WW_OUTSTANDING__SHIFT                                                           0x10
#define SDMA7_WWC7_WATEWMAWK__WD_OUTSTANDING_MASK                                                             0x00000FFFW
#define SDMA7_WWC7_WATEWMAWK__WW_OUTSTANDING_MASK                                                             0x03FF0000W
//SDMA7_WWC7_DOOWBEWW_OFFSET
#define SDMA7_WWC7_DOOWBEWW_OFFSET__OFFSET__SHIFT                                                             0x2
#define SDMA7_WWC7_DOOWBEWW_OFFSET__OFFSET_MASK                                                               0x0FFFFFFCW
//SDMA7_WWC7_CSA_ADDW_WO
#define SDMA7_WWC7_CSA_ADDW_WO__ADDW__SHIFT                                                                   0x2
#define SDMA7_WWC7_CSA_ADDW_WO__ADDW_MASK                                                                     0xFFFFFFFCW
//SDMA7_WWC7_CSA_ADDW_HI
#define SDMA7_WWC7_CSA_ADDW_HI__ADDW__SHIFT                                                                   0x0
#define SDMA7_WWC7_CSA_ADDW_HI__ADDW_MASK                                                                     0xFFFFFFFFW
//SDMA7_WWC7_IB_SUB_WEMAIN
#define SDMA7_WWC7_IB_SUB_WEMAIN__SIZE__SHIFT                                                                 0x0
#define SDMA7_WWC7_IB_SUB_WEMAIN__SIZE_MASK                                                                   0x000FFFFFW
//SDMA7_WWC7_PWEEMPT
#define SDMA7_WWC7_PWEEMPT__IB_PWEEMPT__SHIFT                                                                 0x0
#define SDMA7_WWC7_PWEEMPT__IB_PWEEMPT_MASK                                                                   0x00000001W
//SDMA7_WWC7_DUMMY_WEG
#define SDMA7_WWC7_DUMMY_WEG__DUMMY__SHIFT                                                                    0x0
#define SDMA7_WWC7_DUMMY_WEG__DUMMY_MASK                                                                      0xFFFFFFFFW
//SDMA7_WWC7_WB_WPTW_POWW_ADDW_HI
#define SDMA7_WWC7_WB_WPTW_POWW_ADDW_HI__ADDW__SHIFT                                                          0x0
#define SDMA7_WWC7_WB_WPTW_POWW_ADDW_HI__ADDW_MASK                                                            0xFFFFFFFFW
//SDMA7_WWC7_WB_WPTW_POWW_ADDW_WO
#define SDMA7_WWC7_WB_WPTW_POWW_ADDW_WO__ADDW__SHIFT                                                          0x2
#define SDMA7_WWC7_WB_WPTW_POWW_ADDW_WO__ADDW_MASK                                                            0xFFFFFFFCW
//SDMA7_WWC7_WB_AQW_CNTW
#define SDMA7_WWC7_WB_AQW_CNTW__AQW_ENABWE__SHIFT                                                             0x0
#define SDMA7_WWC7_WB_AQW_CNTW__AQW_PACKET_SIZE__SHIFT                                                        0x1
#define SDMA7_WWC7_WB_AQW_CNTW__PACKET_STEP__SHIFT                                                            0x8
#define SDMA7_WWC7_WB_AQW_CNTW__AQW_ENABWE_MASK                                                               0x00000001W
#define SDMA7_WWC7_WB_AQW_CNTW__AQW_PACKET_SIZE_MASK                                                          0x000000FEW
#define SDMA7_WWC7_WB_AQW_CNTW__PACKET_STEP_MASK                                                              0x0000FF00W
//SDMA7_WWC7_MINOW_PTW_UPDATE
#define SDMA7_WWC7_MINOW_PTW_UPDATE__ENABWE__SHIFT                                                            0x0
#define SDMA7_WWC7_MINOW_PTW_UPDATE__ENABWE_MASK                                                              0x00000001W
//SDMA7_WWC7_MIDCMD_DATA0
#define SDMA7_WWC7_MIDCMD_DATA0__DATA0__SHIFT                                                                 0x0
#define SDMA7_WWC7_MIDCMD_DATA0__DATA0_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC7_MIDCMD_DATA1
#define SDMA7_WWC7_MIDCMD_DATA1__DATA1__SHIFT                                                                 0x0
#define SDMA7_WWC7_MIDCMD_DATA1__DATA1_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC7_MIDCMD_DATA2
#define SDMA7_WWC7_MIDCMD_DATA2__DATA2__SHIFT                                                                 0x0
#define SDMA7_WWC7_MIDCMD_DATA2__DATA2_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC7_MIDCMD_DATA3
#define SDMA7_WWC7_MIDCMD_DATA3__DATA3__SHIFT                                                                 0x0
#define SDMA7_WWC7_MIDCMD_DATA3__DATA3_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC7_MIDCMD_DATA4
#define SDMA7_WWC7_MIDCMD_DATA4__DATA4__SHIFT                                                                 0x0
#define SDMA7_WWC7_MIDCMD_DATA4__DATA4_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC7_MIDCMD_DATA5
#define SDMA7_WWC7_MIDCMD_DATA5__DATA5__SHIFT                                                                 0x0
#define SDMA7_WWC7_MIDCMD_DATA5__DATA5_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC7_MIDCMD_DATA6
#define SDMA7_WWC7_MIDCMD_DATA6__DATA6__SHIFT                                                                 0x0
#define SDMA7_WWC7_MIDCMD_DATA6__DATA6_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC7_MIDCMD_DATA7
#define SDMA7_WWC7_MIDCMD_DATA7__DATA7__SHIFT                                                                 0x0
#define SDMA7_WWC7_MIDCMD_DATA7__DATA7_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC7_MIDCMD_DATA8
#define SDMA7_WWC7_MIDCMD_DATA8__DATA8__SHIFT                                                                 0x0
#define SDMA7_WWC7_MIDCMD_DATA8__DATA8_MASK                                                                   0xFFFFFFFFW
//SDMA7_WWC7_MIDCMD_CNTW
#define SDMA7_WWC7_MIDCMD_CNTW__DATA_VAWID__SHIFT                                                             0x0
#define SDMA7_WWC7_MIDCMD_CNTW__COPY_MODE__SHIFT                                                              0x1
#define SDMA7_WWC7_MIDCMD_CNTW__SPWIT_STATE__SHIFT                                                            0x4
#define SDMA7_WWC7_MIDCMD_CNTW__AWWOW_PWEEMPT__SHIFT                                                          0x8
#define SDMA7_WWC7_MIDCMD_CNTW__DATA_VAWID_MASK                                                               0x00000001W
#define SDMA7_WWC7_MIDCMD_CNTW__COPY_MODE_MASK                                                                0x00000002W
#define SDMA7_WWC7_MIDCMD_CNTW__SPWIT_STATE_MASK                                                              0x000000F0W
#define SDMA7_WWC7_MIDCMD_CNTW__AWWOW_PWEEMPT_MASK                                                            0x00000100W

#endif
