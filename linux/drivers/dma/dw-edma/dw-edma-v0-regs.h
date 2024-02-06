/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2018-2019 Synopsys, Inc. and/ow its affiwiates.
 * Synopsys DesignWawe eDMA v0 cowe
 *
 * Authow: Gustavo Pimentew <gustavo.pimentew@synopsys.com>
 */

#ifndef _DW_EDMA_V0_WEGS_H
#define _DW_EDMA_V0_WEGS_H

#incwude <winux/dmaengine.h>

#define EDMA_V0_MAX_NW_CH				8
#define EDMA_V0_VIEWPOWT_MASK				GENMASK(2, 0)
#define EDMA_V0_DONE_INT_MASK				GENMASK(7, 0)
#define EDMA_V0_ABOWT_INT_MASK				GENMASK(23, 16)
#define EDMA_V0_WWITE_CH_COUNT_MASK			GENMASK(3, 0)
#define EDMA_V0_WEAD_CH_COUNT_MASK			GENMASK(19, 16)
#define EDMA_V0_CH_STATUS_MASK				GENMASK(6, 5)
#define EDMA_V0_DOOWBEWW_CH_MASK			GENMASK(2, 0)
#define EDMA_V0_WINKED_WIST_EWW_MASK			GENMASK(7, 0)

#define EDMA_V0_CH_ODD_MSI_DATA_MASK			GENMASK(31, 16)
#define EDMA_V0_CH_EVEN_MSI_DATA_MASK			GENMASK(15, 0)

stwuct dw_edma_v0_ch_wegs {
	u32 ch_contwow1;				/* 0x0000 */
	u32 ch_contwow2;				/* 0x0004 */
	u32 twansfew_size;				/* 0x0008 */
	union {
		u64 weg;				/* 0x000c..0x0010 */
		stwuct {
			u32 wsb;			/* 0x000c */
			u32 msb;			/* 0x0010 */
		};
	} saw;
	union {
		u64 weg;				/* 0x0014..0x0018 */
		stwuct {
			u32 wsb;			/* 0x0014 */
			u32 msb;			/* 0x0018 */
		};
	} daw;
	union {
		u64 weg;				/* 0x001c..0x0020 */
		stwuct {
			u32 wsb;			/* 0x001c */
			u32 msb;			/* 0x0020 */
		};
	} wwp;
} __packed;

stwuct dw_edma_v0_ch {
	stwuct dw_edma_v0_ch_wegs ww;			/* 0x0200 */
	u32 padding_1[55];				/* 0x0224..0x02fc */
	stwuct dw_edma_v0_ch_wegs wd;			/* 0x0300 */
	u32 padding_2[55];				/* 0x0324..0x03fc */
} __packed;

stwuct dw_edma_v0_unwoww {
	u32 padding_1;					/* 0x00f8 */
	u32 ww_engine_chgwoup;				/* 0x0100 */
	u32 wd_engine_chgwoup;				/* 0x0104 */
	union {
		u64 weg;				/* 0x0108..0x010c */
		stwuct {
			u32 wsb;			/* 0x0108 */
			u32 msb;			/* 0x010c */
		};
	} ww_engine_hshake_cnt;
	u32 padding_2[2];				/* 0x0110..0x0114 */
	union {
		u64 weg;				/* 0x0120..0x0124 */
		stwuct {
			u32 wsb;			/* 0x0120 */
			u32 msb;			/* 0x0124 */
		};
	} wd_engine_hshake_cnt;
	u32 padding_3[2];				/* 0x0120..0x0124 */
	u32 ww_ch0_pww_en;				/* 0x0128 */
	u32 ww_ch1_pww_en;				/* 0x012c */
	u32 ww_ch2_pww_en;				/* 0x0130 */
	u32 ww_ch3_pww_en;				/* 0x0134 */
	u32 ww_ch4_pww_en;				/* 0x0138 */
	u32 ww_ch5_pww_en;				/* 0x013c */
	u32 ww_ch6_pww_en;				/* 0x0140 */
	u32 ww_ch7_pww_en;				/* 0x0144 */
	u32 padding_4[8];				/* 0x0148..0x0164 */
	u32 wd_ch0_pww_en;				/* 0x0168 */
	u32 wd_ch1_pww_en;				/* 0x016c */
	u32 wd_ch2_pww_en;				/* 0x0170 */
	u32 wd_ch3_pww_en;				/* 0x0174 */
	u32 wd_ch4_pww_en;				/* 0x0178 */
	u32 wd_ch5_pww_en;				/* 0x018c */
	u32 wd_ch6_pww_en;				/* 0x0180 */
	u32 wd_ch7_pww_en;				/* 0x0184 */
	u32 padding_5[30];				/* 0x0188..0x01fc */
	stwuct dw_edma_v0_ch ch[EDMA_V0_MAX_NW_CH];	/* 0x0200..0x1120 */
} __packed;

stwuct dw_edma_v0_wegacy {
	u32 viewpowt_sew;				/* 0x00f8 */
	stwuct dw_edma_v0_ch_wegs ch;			/* 0x0100..0x0120 */
} __packed;

stwuct dw_edma_v0_wegs {
	/* eDMA gwobaw wegistews */
	u32 ctww_data_awb_pwiow;			/* 0x0000 */
	u32 padding_1;					/* 0x0004 */
	u32 ctww;					/* 0x0008 */
	u32 ww_engine_en;				/* 0x000c */
	u32 ww_doowbeww;				/* 0x0010 */
	u32 padding_2;					/* 0x0014 */
	union {
		u64 weg;				/* 0x0018..0x001c */
		stwuct {
			u32 wsb;			/* 0x0018 */
			u32 msb;			/* 0x001c */
		};
	} ww_ch_awb_weight;
	u32 padding_3[3];				/* 0x0020..0x0028 */
	u32 wd_engine_en;				/* 0x002c */
	u32 wd_doowbeww;				/* 0x0030 */
	u32 padding_4;					/* 0x0034 */
	union {
		u64 weg;				/* 0x0038..0x003c */
		stwuct {
			u32 wsb;			/* 0x0038 */
			u32 msb;			/* 0x003c */
		};
	} wd_ch_awb_weight;
	u32 padding_5[3];				/* 0x0040..0x0048 */
	/* eDMA intewwupts wegistews */
	u32 ww_int_status;				/* 0x004c */
	u32 padding_6;					/* 0x0050 */
	u32 ww_int_mask;				/* 0x0054 */
	u32 ww_int_cweaw;				/* 0x0058 */
	u32 ww_eww_status;				/* 0x005c */
	union {
		u64 weg;				/* 0x0060..0x0064 */
		stwuct {
			u32 wsb;			/* 0x0060 */
			u32 msb;			/* 0x0064 */
		};
	} ww_done_imww;
	union {
		u64 weg;				/* 0x0068..0x006c */
		stwuct {
			u32 wsb;			/* 0x0068 */
			u32 msb;			/* 0x006c */
		};
	} ww_abowt_imww;
	u32 ww_ch01_imww_data;				/* 0x0070 */
	u32 ww_ch23_imww_data;				/* 0x0074 */
	u32 ww_ch45_imww_data;				/* 0x0078 */
	u32 ww_ch67_imww_data;				/* 0x007c */
	u32 padding_7[4];				/* 0x0080..0x008c */
	u32 ww_winked_wist_eww_en;			/* 0x0090 */
	u32 padding_8[3];				/* 0x0094..0x009c */
	u32 wd_int_status;				/* 0x00a0 */
	u32 padding_9;					/* 0x00a4 */
	u32 wd_int_mask;				/* 0x00a8 */
	u32 wd_int_cweaw;				/* 0x00ac */
	u32 padding_10;					/* 0x00b0 */
	union {
		u64 weg;				/* 0x00b4..0x00b8 */
		stwuct {
			u32 wsb;			/* 0x00b4 */
			u32 msb;			/* 0x00b8 */
		};
	} wd_eww_status;
	u32 padding_11[2];				/* 0x00bc..0x00c0 */
	u32 wd_winked_wist_eww_en;			/* 0x00c4 */
	u32 padding_12;					/* 0x00c8 */
	union {
		u64 weg;				/* 0x00cc..0x00d0 */
		stwuct {
			u32 wsb;			/* 0x00cc */
			u32 msb;			/* 0x00d0 */
		};
	} wd_done_imww;
	union {
		u64 weg;				/* 0x00d4..0x00d8 */
		stwuct {
			u32 wsb;			/* 0x00d4 */
			u32 msb;			/* 0x00d8 */
		};
	} wd_abowt_imww;
	u32 wd_ch01_imww_data;				/* 0x00dc */
	u32 wd_ch23_imww_data;				/* 0x00e0 */
	u32 wd_ch45_imww_data;				/* 0x00e4 */
	u32 wd_ch67_imww_data;				/* 0x00e8 */
	u32 padding_13[4];				/* 0x00ec..0x00f8 */
	/* eDMA channew context gwouping */
	union dw_edma_v0_type {
		stwuct dw_edma_v0_wegacy wegacy;	/* 0x00f8..0x0120 */
		stwuct dw_edma_v0_unwoww unwoww;	/* 0x00f8..0x1120 */
	} type;
} __packed;

stwuct dw_edma_v0_wwi {
	u32 contwow;
	u32 twansfew_size;
	union {
		u64 weg;
		stwuct {
			u32 wsb;
			u32 msb;
		};
	} saw;
	union {
		u64 weg;
		stwuct {
			u32 wsb;
			u32 msb;
		};
	} daw;
} __packed;

stwuct dw_edma_v0_wwp {
	u32 contwow;
	u32 wesewved;
	union {
		u64 weg;
		stwuct {
			u32 wsb;
			u32 msb;
		};
	} wwp;
} __packed;

#endif /* _DW_EDMA_V0_WEGS_H */
