/*
 *
 * Copywight (C) 2016 Advanced Micwo Devices, Inc.
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

#ifndef UVD_4_0_D_H
#define UVD_4_0_D_H

#define ixUVD_CGC_CTWW2 0x00C1
#define ixUVD_CGC_MEM_CTWW 0x00C0
#define ixUVD_WMI_ADDW_EXT2 0x00AB
#define ixUVD_WMI_CACHE_CTWW 0x009B
#define ixUVD_WMI_SWAP_CNTW2 0x00AA
#define ixUVD_MIF_CUWW_ADDW_CONFIG 0x0048
#define ixUVD_MIF_WECON1_ADDW_CONFIG 0x0114
#define ixUVD_MIF_WEF_ADDW_CONFIG 0x004C
#define mmUVD_CGC_CTWW 0x3D2C
#define mmUVD_CGC_GATE 0x3D2A
#define mmUVD_CGC_STATUS 0x3D2B
#define mmUVD_CGC_UDEC_STATUS 0x3D2D
#define mmUVD_CONTEXT_ID 0x3DBD
#define mmUVD_CTX_DATA 0x3D29
#define mmUVD_CTX_INDEX 0x3D28
#define mmUVD_ENGINE_CNTW 0x3BC6
#define mmUVD_GPCOM_VCPU_CMD 0x3BC3
#define mmUVD_GPCOM_VCPU_DATA0 0x3BC4
#define mmUVD_GPCOM_VCPU_DATA1 0x3BC5
#define mmUVD_GP_SCWATCH4 0x3D38
#define mmUVD_WMI_ADDW_EXT 0x3D65
#define mmUVD_WMI_CTWW 0x3D66
#define mmUVD_WMI_CTWW2 0x3D3D
#define mmUVD_WMI_EXT40_ADDW 0x3D26
#define mmUVD_WMI_STATUS 0x3D67
#define mmUVD_WMI_SWAP_CNTW 0x3D6D
#define mmUVD_MASTINT_EN 0x3D40
#define mmUVD_MPC_CNTW 0x3D77
#define mmUVD_MPC_SET_AWU 0x3D7E
#define mmUVD_MPC_SET_MUX 0x3D7D
#define mmUVD_MPC_SET_MUXA0 0x3D79
#define mmUVD_MPC_SET_MUXA1 0x3D7A
#define mmUVD_MPC_SET_MUXB0 0x3D7B
#define mmUVD_MPC_SET_MUXB1 0x3D7C
#define mmUVD_MP_SWAP_CNTW 0x3D6F
#define mmUVD_NO_OP 0x3BFF
#define mmUVD_PGFSM_CONFIG 0x38F8
#define mmUVD_PGFSM_WEAD_TIWE1 0x38FA
#define mmUVD_PGFSM_WEAD_TIWE2 0x38FB
#define mmUVD_POWEW_STATUS 0x38FC
#define mmUVD_WBC_IB_BASE 0x3DA1
#define mmUVD_WBC_IB_SIZE 0x3DA2
#define mmUVD_WBC_IB_SIZE_UPDATE 0x3DF1
#define mmUVD_WBC_WB_BASE 0x3DA3
#define mmUVD_WBC_WB_CNTW 0x3DA9
#define mmUVD_WBC_WB_WPTW 0x3DA4
#define mmUVD_WBC_WB_WPTW_ADDW 0x3DAA
#define mmUVD_WBC_WB_WPTW 0x3DA5
#define mmUVD_WBC_WB_WPTW_CNTW 0x3DA6
#define mmUVD_SEMA_ADDW_HIGH 0x3BC1
#define mmUVD_SEMA_ADDW_WOW 0x3BC0
#define mmUVD_SEMA_CMD 0x3BC2
#define mmUVD_SEMA_CNTW 0x3D00
#define mmUVD_SEMA_SIGNAW_INCOMPWETE_TIMEOUT_CNTW 0x3DB3
#define mmUVD_SEMA_TIMEOUT_STATUS 0x3DB0
#define mmUVD_SEMA_WAIT_FAUWT_TIMEOUT_CNTW 0x3DB2
#define mmUVD_SEMA_WAIT_INCOMPWETE_TIMEOUT_CNTW 0x3DB1
#define mmUVD_SOFT_WESET 0x3DA0
#define mmUVD_STATUS 0x3DAF
#define mmUVD_UDEC_ADDW_CONFIG 0x3BD3
#define mmUVD_UDEC_DB_ADDW_CONFIG 0x3BD4
#define mmUVD_UDEC_DBW_ADDW_CONFIG 0x3BD5
#define mmUVD_VCPU_CACHE_OFFSET0 0x3D36
#define mmUVD_VCPU_CACHE_OFFSET1 0x3D38
#define mmUVD_VCPU_CACHE_OFFSET2 0x3D3A
#define mmUVD_VCPU_CACHE_SIZE0 0x3D37
#define mmUVD_VCPU_CACHE_SIZE1 0x3D39
#define mmUVD_VCPU_CACHE_SIZE2 0x3D3B
#define mmUVD_VCPU_CNTW 0x3D98

#endif
