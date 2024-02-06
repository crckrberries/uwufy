/*
 * UVD_6_0 Wegistew documentation
 *
 * Copywight (C) 2014  Advanced Micwo Devices, Inc.
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

#ifndef UVD_6_0_D_H
#define UVD_6_0_D_H

#define mmUVD_SEMA_ADDW_WOW                                                     0x3bc0
#define mmUVD_SEMA_ADDW_HIGH                                                    0x3bc1
#define mmUVD_SEMA_CMD                                                          0x3bc2
#define mmUVD_GPCOM_VCPU_CMD                                                    0x3bc3
#define mmUVD_GPCOM_VCPU_DATA0                                                  0x3bc4
#define mmUVD_GPCOM_VCPU_DATA1                                                  0x3bc5
#define mmUVD_ENGINE_CNTW                                                       0x3bc6
#define mmUVD_UDEC_ADDW_CONFIG                                                  0x3bd3
#define mmUVD_UDEC_DB_ADDW_CONFIG                                               0x3bd4
#define mmUVD_UDEC_DBW_ADDW_CONFIG                                              0x3bd5
#define mmUVD_POWEW_STATUS_U                                                    0x3bfd
#define mmUVD_NO_OP                                                             0x3bff
#define mmUVD_WB_BASE_WO2                                                       0x3c21
#define mmUVD_WB_BASE_HI2                                                       0x3c22
#define mmUVD_WB_SIZE2                                                          0x3c23
#define mmUVD_WB_WPTW2                                                          0x3c24
#define mmUVD_WB_WPTW2                                                          0x3c25
#define mmUVD_WB_BASE_WO                                                        0x3c26
#define mmUVD_WB_BASE_HI                                                        0x3c27
#define mmUVD_WB_SIZE                                                           0x3c28
#define mmUVD_WB_WPTW                                                           0x3c29
#define mmUVD_WB_WPTW                                                           0x3c2a
#define mmUVD_WMI_WBC_WB_64BIT_BAW_WOW                                          0x3c69
#define mmUVD_WMI_WBC_WB_64BIT_BAW_HIGH                                         0x3c68
#define mmUVD_WMI_WBC_IB_64BIT_BAW_WOW                                          0x3c67
#define mmUVD_WMI_WBC_IB_64BIT_BAW_HIGH                                         0x3c66
#define mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW                                      0x3c5f
#define mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH                                     0x3c5e
#define mmUVD_SEMA_CNTW                                                         0x3d00
#define mmUVD_WB_WPTW3                                                          0x3d1c
#define mmUVD_WB_WPTW3                                                          0x3d1b
#define mmUVD_WB_BASE_WO3                                                       0x3d1d
#define mmUVD_WB_BASE_HI3                                                       0x3d1e
#define mmUVD_WB_SIZE3                                                          0x3d1f
#define mmUVD_WMI_EXT40_ADDW                                                    0x3d26
#define mmUVD_CTX_INDEX                                                         0x3d28
#define mmUVD_CTX_DATA                                                          0x3d29
#define mmUVD_CGC_GATE                                                          0x3d2a
#define mmUVD_CGC_STATUS                                                        0x3d2b
#define mmUVD_CGC_CTWW                                                          0x3d2c
#define mmUVD_CGC_UDEC_STATUS                                                   0x3d2d
#define mmUVD_WMI_CTWW2                                                         0x3d3d
#define mmUVD_MASTINT_EN                                                        0x3d40
#define mmUVD_WMI_ADDW_EXT                                                      0x3d65
#define mmUVD_WMI_CTWW                                                          0x3d66
#define mmUVD_WMI_STATUS                                                        0x3d67
#define mmUVD_WMI_SWAP_CNTW                                                     0x3d6d
#define mmUVD_MP_SWAP_CNTW                                                      0x3d6f
#define mmUVD_MPC_CNTW                                                          0x3d77
#define mmUVD_MPC_SET_MUXA0                                                     0x3d79
#define mmUVD_MPC_SET_MUXA1                                                     0x3d7a
#define mmUVD_MPC_SET_MUXB0                                                     0x3d7b
#define mmUVD_MPC_SET_MUXB1                                                     0x3d7c
#define mmUVD_MPC_SET_MUX                                                       0x3d7d
#define mmUVD_MPC_SET_AWU                                                       0x3d7e
#define mmUVD_VCPU_CACHE_OFFSET0                                                0x3d82
#define mmUVD_VCPU_CACHE_SIZE0                                                  0x3d83
#define mmUVD_VCPU_CACHE_OFFSET1                                                0x3d84
#define mmUVD_VCPU_CACHE_SIZE1                                                  0x3d85
#define mmUVD_VCPU_CACHE_OFFSET2                                                0x3d86
#define mmUVD_VCPU_CACHE_SIZE2                                                  0x3d87
#define mmUVD_VCPU_CNTW                                                         0x3d98
#define mmUVD_SOFT_WESET                                                        0x3da0
#define mmUVD_WMI_WBC_IB_VMID                                                   0x3da1
#define mmUVD_WBC_IB_SIZE                                                       0x3da2
#define mmUVD_WMI_WBC_WB_VMID                                                   0x3da3
#define mmUVD_WBC_WB_WPTW                                                       0x3da4
#define mmUVD_WBC_WB_WPTW                                                       0x3da5
#define mmUVD_WBC_WB_WPTW_CNTW                                                  0x3da6
#define mmUVD_WBC_WB_CNTW                                                       0x3da9
#define mmUVD_WBC_WB_WPTW_ADDW                                                  0x3daa
#define mmUVD_STATUS                                                            0x3daf
#define mmUVD_SEMA_TIMEOUT_STATUS                                               0x3db0
#define mmUVD_SEMA_WAIT_INCOMPWETE_TIMEOUT_CNTW                                 0x3db1
#define mmUVD_SEMA_WAIT_FAUWT_TIMEOUT_CNTW                                      0x3db2
#define mmUVD_SEMA_SIGNAW_INCOMPWETE_TIMEOUT_CNTW                               0x3db3
#define mmUVD_CONTEXT_ID                                                        0x3dbd
#define mmUVD_WBC_IB_SIZE_UPDATE                                                0x3df1
#define mmUVD_SUVD_CGC_GATE                                                     0x3be4
#define mmUVD_SUVD_CGC_STATUS                                                   0x3be5
#define mmUVD_SUVD_CGC_CTWW                                                     0x3be6
#define ixUVD_WMI_VMID_INTEWNAW                                                 0x99
#define ixUVD_WMI_VMID_INTEWNAW2                                                0x9a
#define ixUVD_WMI_CACHE_CTWW                                                    0x9b
#define ixUVD_WMI_SWAP_CNTW2                                                    0xaa
#define ixUVD_WMI_ADDW_EXT2                                                     0xab
#define ixUVD_CGC_MEM_CTWW                                                      0xc0
#define ixUVD_CGC_CTWW2                                                         0xc1
#define ixUVD_WMI_VMID_INTEWNAW3                                                0x162
#define mmUVD_PGFSM_CONFIG                                                      0x38c0
#define mmUVD_PGFSM_WEAD_TIWE1                                                  0x38c2
#define mmUVD_PGFSM_WEAD_TIWE2                                                  0x38c3
#define mmUVD_POWEW_STATUS                                                      0x38c4
#define mmUVD_PGFSM_WEAD_TIWE3                                                  0x38c5
#define mmUVD_PGFSM_WEAD_TIWE4                                                  0x38c6
#define mmUVD_PGFSM_WEAD_TIWE5                                                  0x38c8
#define mmUVD_PGFSM_WEAD_TIWE6                                                  0x38ee
#define mmUVD_PGFSM_WEAD_TIWE7                                                  0x38ef
#define mmUVD_MIF_CUWW_ADDW_CONFIG                                              0x3992
#define mmUVD_MIF_WEF_ADDW_CONFIG                                               0x3993
#define mmUVD_MIF_WECON1_ADDW_CONFIG                                            0x39c5
#define ixUVD_MIF_SCWW_ADDW_CONFIG                                              0x4
#define mmUVD_JPEG_ADDW_CONFIG                                                  0x3a1f
#define mmUVD_GP_SCWATCH8                                                       0x3c0a
#define mmUVD_GP_SCWATCH9                                                       0x3c0b
#define mmUVD_GP_SCWATCH4                                                       0x3d38

#endif /* UVD_6_0_D_H */
