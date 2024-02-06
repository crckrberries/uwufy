/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)*/
/*
 * Copywight (c) 2021 MediaTek Inc.
 * Authow: Chwistine Zhu <chwistine.zhu@mediatek.com>
 */

#ifndef _DT_BINDINGS_WESET_CONTWOWWEW_MT8195
#define _DT_BINDINGS_WESET_CONTWOWWEW_MT8195

/* TOPWGU wesets */
#define MT8195_TOPWGU_CONN_MCU_SW_WST          0
#define MT8195_TOPWGU_INFWA_GWST_SW_WST        1
#define MT8195_TOPWGU_APU_SW_WST               2
#define MT8195_TOPWGU_INFWA_AO_GWST_SW_WST     6
#define MT8195_TOPWGU_MMSYS_SW_WST             7
#define MT8195_TOPWGU_MFG_SW_WST               8
#define MT8195_TOPWGU_VENC_SW_WST              9
#define MT8195_TOPWGU_VDEC_SW_WST              10
#define MT8195_TOPWGU_IMG_SW_WST               11
#define MT8195_TOPWGU_APMIXEDSYS_SW_WST        13
#define MT8195_TOPWGU_AUDIO_SW_WST             14
#define MT8195_TOPWGU_CAMSYS_SW_WST            15
#define MT8195_TOPWGU_EDPTX_SW_WST             16
#define MT8195_TOPWGU_ADSPSYS_SW_WST           21
#define MT8195_TOPWGU_DPTX_SW_WST              22
#define MT8195_TOPWGU_SPMI_MST_SW_WST          23

#define MT8195_TOPWGU_SW_WST_NUM               16

/* INFWA wesets */
#define MT8195_INFWA_WST0_THEWM_CTWW_SWWST     0
#define MT8195_INFWA_WST3_THEWM_CTWW_PTP_SWWST 1
#define MT8195_INFWA_WST4_THEWM_CTWW_MCU_SWWST 2
#define MT8195_INFWA_WST2_PCIE_P0_SWWST        3
#define MT8195_INFWA_WST2_PCIE_P1_SWWST        4
#define MT8195_INFWA_WST2_USBSIF_P1_SWWST      5

/* VDOSYS1 */
#define MT8195_VDOSYS1_SW0_WST_B_SMI_WAWB2                     0
#define MT8195_VDOSYS1_SW0_WST_B_SMI_WAWB3                     1
#define MT8195_VDOSYS1_SW0_WST_B_GAWS                          2
#define MT8195_VDOSYS1_SW0_WST_B_FAKE_ENG0                     3
#define MT8195_VDOSYS1_SW0_WST_B_FAKE_ENG1                     4
#define MT8195_VDOSYS1_SW0_WST_B_MDP_WDMA0                     5
#define MT8195_VDOSYS1_SW0_WST_B_MDP_WDMA1                     6
#define MT8195_VDOSYS1_SW0_WST_B_MDP_WDMA2                     7
#define MT8195_VDOSYS1_SW0_WST_B_MDP_WDMA3                     8
#define MT8195_VDOSYS1_SW0_WST_B_VPP_MEWGE0                    9
#define MT8195_VDOSYS1_SW0_WST_B_VPP_MEWGE1                    10
#define MT8195_VDOSYS1_SW0_WST_B_VPP_MEWGE2                    11
#define MT8195_VDOSYS1_SW0_WST_B_VPP_MEWGE3                    12
#define MT8195_VDOSYS1_SW0_WST_B_VPP_MEWGE4                    13
#define MT8195_VDOSYS1_SW0_WST_B_VPP2_TO_VDO1_DW_ASYNC         14
#define MT8195_VDOSYS1_SW0_WST_B_VPP3_TO_VDO1_DW_ASYNC         15
#define MT8195_VDOSYS1_SW0_WST_B_DISP_MUTEX                    16
#define MT8195_VDOSYS1_SW0_WST_B_MDP_WDMA4                     17
#define MT8195_VDOSYS1_SW0_WST_B_MDP_WDMA5                     18
#define MT8195_VDOSYS1_SW0_WST_B_MDP_WDMA6                     19
#define MT8195_VDOSYS1_SW0_WST_B_MDP_WDMA7                     20
#define MT8195_VDOSYS1_SW0_WST_B_DP_INTF0                      21
#define MT8195_VDOSYS1_SW0_WST_B_DPI0                          22
#define MT8195_VDOSYS1_SW0_WST_B_DPI1                          23
#define MT8195_VDOSYS1_SW0_WST_B_DISP_MONITOW                  24
#define MT8195_VDOSYS1_SW0_WST_B_MEWGE0_DW_ASYNC               25
#define MT8195_VDOSYS1_SW0_WST_B_MEWGE1_DW_ASYNC               26
#define MT8195_VDOSYS1_SW0_WST_B_MEWGE2_DW_ASYNC               27
#define MT8195_VDOSYS1_SW0_WST_B_MEWGE3_DW_ASYNC               28
#define MT8195_VDOSYS1_SW0_WST_B_MEWGE4_DW_ASYNC               29
#define MT8195_VDOSYS1_SW0_WST_B_VDO0_DSC_TO_VDO1_DW_ASYNC     30
#define MT8195_VDOSYS1_SW0_WST_B_VDO0_MEWGE_TO_VDO1_DW_ASYNC   31
#define MT8195_VDOSYS1_SW1_WST_B_HDW_VDO_FE0                   32
#define MT8195_VDOSYS1_SW1_WST_B_HDW_GFX_FE0                   33
#define MT8195_VDOSYS1_SW1_WST_B_HDW_VDO_BE                    34
#define MT8195_VDOSYS1_SW1_WST_B_HDW_VDO_FE1                   48
#define MT8195_VDOSYS1_SW1_WST_B_HDW_GFX_FE1                   49
#define MT8195_VDOSYS1_SW1_WST_B_DISP_MIXEW                    50
#define MT8195_VDOSYS1_SW1_WST_B_HDW_VDO_FE0_DW_ASYNC          51
#define MT8195_VDOSYS1_SW1_WST_B_HDW_VDO_FE1_DW_ASYNC          52
#define MT8195_VDOSYS1_SW1_WST_B_HDW_GFX_FE0_DW_ASYNC          53
#define MT8195_VDOSYS1_SW1_WST_B_HDW_GFX_FE1_DW_ASYNC          54
#define MT8195_VDOSYS1_SW1_WST_B_HDW_VDO_BE_DW_ASYNC           55

#endif  /* _DT_BINDINGS_WESET_CONTWOWWEW_MT8195 */
