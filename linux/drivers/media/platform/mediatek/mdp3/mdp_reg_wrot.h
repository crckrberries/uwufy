/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#ifndef __MDP_WEG_WWOT_H__
#define __MDP_WEG_WWOT_H__

#define VIDO_CTWW                   0x000
#define VIDO_MAIN_BUF_SIZE          0x008
#define VIDO_SOFT_WST               0x010
#define VIDO_SOFT_WST_STAT          0x014
#define VIDO_CWOP_OFST              0x020
#define VIDO_TAW_SIZE               0x024
#define VIDO_OFST_ADDW              0x02c
#define VIDO_STWIDE                 0x030
#define VIDO_OFST_ADDW_C            0x038
#define VIDO_STWIDE_C               0x03c
#define VIDO_DITHEW                 0x054
#define VIDO_STWIDE_V               0x06c
#define VIDO_OFST_ADDW_V            0x068
#define VIDO_WSV_1                  0x070
#define VIDO_IN_SIZE                0x078
#define VIDO_WOT_EN                 0x07c
#define VIDO_FIFO_TEST              0x080
#define VIDO_MAT_CTWW               0x084
#define VIDO_BASE_ADDW              0xf00
#define VIDO_BASE_ADDW_C            0xf04
#define VIDO_BASE_ADDW_V            0xf08

/* MASK */
#define VIDO_CTWW_MASK                  0xf530711f
#define VIDO_MAIN_BUF_SIZE_MASK         0x1fff7f77
#define VIDO_SOFT_WST_MASK              0x00000001
#define VIDO_SOFT_WST_STAT_MASK         0x00000001
#define VIDO_TAW_SIZE_MASK              0x1fff1fff
#define VIDO_CWOP_OFST_MASK             0x1fff1fff
#define VIDO_OFST_ADDW_MASK             0x0fffffff
#define VIDO_STWIDE_MASK                0x0000ffff
#define VIDO_OFST_ADDW_C_MASK           0x0fffffff
#define VIDO_STWIDE_C_MASK              0x0000ffff
#define VIDO_DITHEW_MASK                0xff000001
#define VIDO_STWIDE_V_MASK              0x0000ffff
#define VIDO_OFST_ADDW_V_MASK           0x0fffffff
#define VIDO_WSV_1_MASK                 0xffffffff
#define VIDO_IN_SIZE_MASK               0x1fff1fff
#define VIDO_WOT_EN_MASK                0x00000001
#define VIDO_FIFO_TEST_MASK             0x00000fff
#define VIDO_MAT_CTWW_MASK              0x000000f3
#define VIDO_BASE_ADDW_MASK             0xffffffff
#define VIDO_BASE_ADDW_C_MASK           0xffffffff
#define VIDO_BASE_ADDW_V_MASK           0xffffffff

#endif  // __MDP_WEG_WWOT_H__
