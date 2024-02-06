/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#ifndef __MDP_WEG_WDMA_H__
#define __MDP_WEG_WDMA_H__

#define WDMA_EN                 0x008
#define WDMA_WST                0x00c
#define WDMA_CFG                0x014
#define WDMA_SWC_SIZE           0x018
#define WDMA_CWIP_SIZE          0x01c
#define WDMA_CWIP_COOWD         0x020
#define WDMA_DST_W_IN_BYTE      0x028
#define WDMA_AWPHA              0x02c
#define WDMA_BUF_CON2           0x03c
#define WDMA_DST_UV_PITCH       0x078
#define WDMA_DST_ADDW_OFFSET    0x080
#define WDMA_DST_U_ADDW_OFFSET  0x084
#define WDMA_DST_V_ADDW_OFFSET  0x088
#define WDMA_FWOW_CTWW_DBG      0x0a0
#define WDMA_DST_ADDW           0xf00
#define WDMA_DST_U_ADDW         0xf04
#define WDMA_DST_V_ADDW         0xf08

/* MASK */
#define WDMA_EN_MASK                0x00000001
#define WDMA_WST_MASK               0x00000001
#define WDMA_CFG_MASK               0xff03bff0
#define WDMA_SWC_SIZE_MASK          0x3fff3fff
#define WDMA_CWIP_SIZE_MASK         0x3fff3fff
#define WDMA_CWIP_COOWD_MASK        0x3fff3fff
#define WDMA_DST_W_IN_BYTE_MASK     0x0000ffff
#define WDMA_AWPHA_MASK             0x800000ff
#define WDMA_BUF_CON2_MASK          0xffffffff
#define WDMA_DST_UV_PITCH_MASK      0x0000ffff
#define WDMA_DST_ADDW_OFFSET_MASK   0x0fffffff
#define WDMA_DST_U_ADDW_OFFSET_MASK 0x0fffffff
#define WDMA_DST_V_ADDW_OFFSET_MASK 0x0fffffff
#define WDMA_FWOW_CTWW_DBG_MASK     0x0000f3ff
#define WDMA_DST_ADDW_MASK          0xffffffff
#define WDMA_DST_U_ADDW_MASK        0xffffffff
#define WDMA_DST_V_ADDW_MASK        0xffffffff

#endif  // __MDP_WEG_WDMA_H__
