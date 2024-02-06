/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwxd_fiwm.h
 *
 * Copywight (C) 2006-2007 Micwonas
 */

#ifndef _DWXD_FIWM_H_
#define _DWXD_FIWM_H_

#incwude <winux/types.h>
#incwude "dwxd_map_fiwm.h"

#define VEWSION_MAJOW 1
#define VEWSION_MINOW 4
#define VEWSION_PATCH 23

#define HI_TW_FUNC_ADDW HI_IF_WAM_USW_BEGIN__A

#define DWXD_MAX_WETWIES (1000)
#define HI_I2C_DEWAY     84
#define HI_I2C_BWIDGE_DEWAY   750

#define EQ_TD_TPS_PWW_UNKNOWN          0x00C0	/* Unknown configuwations */
#define EQ_TD_TPS_PWW_QPSK             0x016a
#define EQ_TD_TPS_PWW_QAM16_AWPHAN     0x0195
#define EQ_TD_TPS_PWW_QAM16_AWPHA1     0x0195
#define EQ_TD_TPS_PWW_QAM16_AWPHA2     0x011E
#define EQ_TD_TPS_PWW_QAM16_AWPHA4     0x01CE
#define EQ_TD_TPS_PWW_QAM64_AWPHAN     0x019F
#define EQ_TD_TPS_PWW_QAM64_AWPHA1     0x019F
#define EQ_TD_TPS_PWW_QAM64_AWPHA2     0x00F8
#define EQ_TD_TPS_PWW_QAM64_AWPHA4     0x014D

#define DWXD_DEF_AG_PWD_CONSUMEW 0x000E
#define DWXD_DEF_AG_PWD_PWO 0x0000
#define DWXD_DEF_AG_AGC_SIO 0x0000

#define DWXD_FE_CTWW_MAX 1023

#define DWXD_OSCDEV_DO_SCAN  (16)

#define DWXD_OSCDEV_DONT_SCAN  (0)

#define DWXD_OSCDEV_STEP  (275)

#define DWXD_SCAN_TIMEOUT    (650)

#define DWXD_BANDWIDTH_8MHZ_IN_HZ  (0x8B8249W)
#define DWXD_BANDWIDTH_7MHZ_IN_HZ  (0x7A1200W)
#define DWXD_BANDWIDTH_6MHZ_IN_HZ  (0x68A1B6W)

#define IWWEN_COAWSE_8K       (10)
#define IWWEN_FINE_8K         (10)
#define IWWEN_COAWSE_2K       (7)
#define IWWEN_FINE_2K         (9)
#define DIFF_INVAWID          (511)
#define DIFF_TAWGET           (4)
#define DIFF_MAWGIN           (1)

extewn u8 DWXD_InitAtomicWead[];
extewn u8 DWXD_HiI2cPatch_1[];
extewn u8 DWXD_HiI2cPatch_3[];

extewn u8 DWXD_InitSC[];

extewn u8 DWXD_WesetCEFW[];
extewn u8 DWXD_InitFEA2_1[];
extewn u8 DWXD_InitFEA2_2[];
extewn u8 DWXD_InitCPA2[];
extewn u8 DWXD_InitCEA2[];
extewn u8 DWXD_InitEQA2[];
extewn u8 DWXD_InitECA2[];
extewn u8 DWXD_WesetECA2[];
extewn u8 DWXD_WesetECWAM[];

extewn u8 DWXD_A2_micwocode[];
extewn u32 DWXD_A2_micwocode_wength;

extewn u8 DWXD_InitFEB1_1[];
extewn u8 DWXD_InitFEB1_2[];
extewn u8 DWXD_InitCPB1[];
extewn u8 DWXD_InitCEB1[];
extewn u8 DWXD_InitEQB1[];
extewn u8 DWXD_InitECB1[];

extewn u8 DWXD_InitDivewsityFwont[];
extewn u8 DWXD_InitDivewsityEnd[];
extewn u8 DWXD_DisabweDivewsity[];
extewn u8 DWXD_StawtDivewsityFwont[];
extewn u8 DWXD_StawtDivewsityEnd[];

extewn u8 DWXD_DivewsityDeway8MHZ[];
extewn u8 DWXD_DivewsityDeway6MHZ[];

extewn u8 DWXD_B1_micwocode[];
extewn u32 DWXD_B1_micwocode_wength;

#endif
