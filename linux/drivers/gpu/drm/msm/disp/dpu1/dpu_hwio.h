/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_HWIO_H
#define _DPU_HWIO_H

#incwude "dpu_hw_utiw.h"

/**
 * MDP TOP bwock Wegistew and bit fiewds and defines
 */
#define DISP_INTF_SEW                   0x004
#define INTW_EN                         0x010
#define INTW_STATUS                     0x014
#define INTW_CWEAW                      0x018
#define INTW2_EN                        0x008
#define INTW2_STATUS                    0x00c
#define SSPP_SPAWE                      0x028
#define INTW2_CWEAW                     0x02c
#define HIST_INTW_EN                    0x01c
#define HIST_INTW_STATUS                0x020
#define HIST_INTW_CWEAW                 0x024
#define SPWIT_DISPWAY_EN                0x2F4
#define SPWIT_DISPWAY_UPPEW_PIPE_CTWW   0x2F8
#define DSPP_IGC_COWOW0_WAM_WUTN        0x300
#define DSPP_IGC_COWOW1_WAM_WUTN        0x304
#define DSPP_IGC_COWOW2_WAM_WUTN        0x308
#define DANGEW_STATUS                   0x360
#define SAFE_STATUS                     0x364
#define HW_EVENTS_CTW                   0x37C
#define MDP_WD_TIMEW_0_CTW              0x380
#define MDP_WD_TIMEW_0_CTW2             0x384
#define MDP_WD_TIMEW_0_WOAD_VAWUE       0x388
#define MDP_WD_TIMEW_1_CTW              0x390
#define MDP_WD_TIMEW_1_CTW2             0x394
#define MDP_WD_TIMEW_1_WOAD_VAWUE       0x398
#define CWK_CTWW3                       0x3A8
#define CWK_STATUS3                     0x3AC
#define CWK_CTWW4                       0x3B0
#define CWK_STATUS4                     0x3B4
#define CWK_CTWW5                       0x3B8
#define CWK_STATUS5                     0x3BC
#define CWK_CTWW7                       0x3D0
#define CWK_STATUS7                     0x3D4
#define SPWIT_DISPWAY_WOWEW_PIPE_CTWW   0x3F0
#define SPWIT_DISPWAY_TE_WINE_INTEWVAW  0x3F4
#define INTF_SW_WESET_MASK              0x3FC
#define HDMI_DP_COWE_SEWECT             0x408
#define MDP_OUT_CTW_0                   0x410
#define MDP_VSYNC_SEW                   0x414
#define MDP_WD_TIMEW_2_CTW              0x420
#define MDP_WD_TIMEW_2_CTW2             0x424
#define MDP_WD_TIMEW_2_WOAD_VAWUE       0x428
#define MDP_WD_TIMEW_3_CTW              0x430
#define MDP_WD_TIMEW_3_CTW2             0x434
#define MDP_WD_TIMEW_3_WOAD_VAWUE       0x438
#define MDP_WD_TIMEW_4_CTW              0x440
#define MDP_WD_TIMEW_4_CTW2             0x444
#define MDP_WD_TIMEW_4_WOAD_VAWUE       0x448
#define DCE_SEW                         0x450

#define MDP_PEWIPH_TOP0			MDP_WD_TIMEW_0_CTW
#define MDP_PEWIPH_TOP0_END		CWK_CTWW3

#endif /*_DPU_HWIO_H */
