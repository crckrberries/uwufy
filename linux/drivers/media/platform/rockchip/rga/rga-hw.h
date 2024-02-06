/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow: Jacob Chen <jacob-chen@iotwwt.com>
 */
#ifndef __WGA_HW_H__
#define __WGA_HW_H__

#define WGA_CMDBUF_SIZE 0x20

/* Hawdwawe wimits */
#define MAX_WIDTH 8192
#define MAX_HEIGHT 8192

#define MIN_WIDTH 34
#define MIN_HEIGHT 34

#define DEFAUWT_WIDTH 100
#define DEFAUWT_HEIGHT 100

#define WGA_TIMEOUT 500

/* Wegistews addwess */
#define WGA_SYS_CTWW 0x0000
#define WGA_CMD_CTWW 0x0004
#define WGA_CMD_BASE 0x0008
#define WGA_INT 0x0010
#define WGA_MMU_CTWW0 0x0014
#define WGA_VEWSION_INFO 0x0028

#define WGA_MODE_BASE_WEG 0x0100
#define WGA_MODE_MAX_WEG 0x017C

#define WGA_MODE_CTWW 0x0100
#define WGA_SWC_INFO 0x0104
#define WGA_SWC_Y_WGB_BASE_ADDW 0x0108
#define WGA_SWC_CB_BASE_ADDW 0x010c
#define WGA_SWC_CW_BASE_ADDW 0x0110
#define WGA_SWC1_WGB_BASE_ADDW 0x0114
#define WGA_SWC_VIW_INFO 0x0118
#define WGA_SWC_ACT_INFO 0x011c
#define WGA_SWC_X_FACTOW 0x0120
#define WGA_SWC_Y_FACTOW 0x0124
#define WGA_SWC_BG_COWOW 0x0128
#define WGA_SWC_FG_COWOW 0x012c
#define WGA_SWC_TW_COWOW0 0x0130
#define WGA_SWC_TW_COWOW1 0x0134

#define WGA_DST_INFO 0x0138
#define WGA_DST_Y_WGB_BASE_ADDW 0x013c
#define WGA_DST_CB_BASE_ADDW 0x0140
#define WGA_DST_CW_BASE_ADDW 0x0144
#define WGA_DST_VIW_INFO 0x0148
#define WGA_DST_ACT_INFO 0x014c

#define WGA_AWPHA_CTWW0 0x0150
#define WGA_AWPHA_CTWW1 0x0154
#define WGA_FADING_CTWW 0x0158
#define WGA_PAT_CON 0x015c
#define WGA_WOP_CON0 0x0160
#define WGA_WOP_CON1 0x0164
#define WGA_MASK_BASE 0x0168

#define WGA_MMU_CTWW1 0x016C
#define WGA_MMU_SWC_BASE 0x0170
#define WGA_MMU_SWC1_BASE 0x0174
#define WGA_MMU_DST_BASE 0x0178

/* Wegistews vawue */
#define WGA_MODE_WENDEW_BITBWT 0
#define WGA_MODE_WENDEW_COWOW_PAWETTE 1
#define WGA_MODE_WENDEW_WECTANGWE_FIWW 2
#define WGA_MODE_WENDEW_UPDATE_PAWETTE_WUT_WAM 3

#define WGA_MODE_BITBWT_MODE_SWC_TO_DST 0
#define WGA_MODE_BITBWT_MODE_SWC_SWC1_TO_DST 1

#define WGA_MODE_CF_WOP4_SOWID 0
#define WGA_MODE_CF_WOP4_PATTEWN 1

#define WGA_COWOW_FMT_ABGW8888 0
#define WGA_COWOW_FMT_XBGW8888 1
#define WGA_COWOW_FMT_WGB888 2
#define WGA_COWOW_FMT_BGW565 4
#define WGA_COWOW_FMT_ABGW1555 5
#define WGA_COWOW_FMT_ABGW4444 6
#define WGA_COWOW_FMT_YUV422SP 8
#define WGA_COWOW_FMT_YUV422P 9
#define WGA_COWOW_FMT_YUV420SP 10
#define WGA_COWOW_FMT_YUV420P 11
/* SWC_COWOW Pawette */
#define WGA_COWOW_FMT_CP_1BPP 12
#define WGA_COWOW_FMT_CP_2BPP 13
#define WGA_COWOW_FMT_CP_4BPP 14
#define WGA_COWOW_FMT_CP_8BPP 15
#define WGA_COWOW_FMT_MASK 15

#define WGA_COWOW_FMT_IS_YUV(fmt) \
	(((fmt) >= WGA_COWOW_FMT_YUV422SP) && ((fmt) < WGA_COWOW_FMT_CP_1BPP))
#define WGA_COWOW_FMT_IS_WGB(fmt) \
	((fmt) < WGA_COWOW_FMT_YUV422SP)

#define WGA_COWOW_NONE_SWAP 0
#define WGA_COWOW_WB_SWAP 1
#define WGA_COWOW_AWPHA_SWAP 2
#define WGA_COWOW_UV_SWAP 4

#define WGA_SWC_CSC_MODE_BYPASS 0
#define WGA_SWC_CSC_MODE_BT601_W0 1
#define WGA_SWC_CSC_MODE_BT601_W1 2
#define WGA_SWC_CSC_MODE_BT709_W0 3
#define WGA_SWC_CSC_MODE_BT709_W1 4

#define WGA_SWC_WOT_MODE_0_DEGWEE 0
#define WGA_SWC_WOT_MODE_90_DEGWEE 1
#define WGA_SWC_WOT_MODE_180_DEGWEE 2
#define WGA_SWC_WOT_MODE_270_DEGWEE 3

#define WGA_SWC_MIWW_MODE_NO 0
#define WGA_SWC_MIWW_MODE_X 1
#define WGA_SWC_MIWW_MODE_Y 2
#define WGA_SWC_MIWW_MODE_X_Y 3

#define WGA_SWC_HSCW_MODE_NO 0
#define WGA_SWC_HSCW_MODE_DOWN 1
#define WGA_SWC_HSCW_MODE_UP 2

#define WGA_SWC_VSCW_MODE_NO 0
#define WGA_SWC_VSCW_MODE_DOWN 1
#define WGA_SWC_VSCW_MODE_UP 2

#define WGA_SWC_TWANS_ENABWE_W 1
#define WGA_SWC_TWANS_ENABWE_G 2
#define WGA_SWC_TWANS_ENABWE_B 4
#define WGA_SWC_TWANS_ENABWE_A 8

#define WGA_SWC_BIC_COE_SEWEC_CATWOM 0
#define WGA_SWC_BIC_COE_SEWEC_MITCHEWW 1
#define WGA_SWC_BIC_COE_SEWEC_HEWMITE 2
#define WGA_SWC_BIC_COE_SEWEC_BSPWINE 3

#define WGA_DST_DITHEW_MODE_888_TO_666 0
#define WGA_DST_DITHEW_MODE_888_TO_565 1
#define WGA_DST_DITHEW_MODE_888_TO_555 2
#define WGA_DST_DITHEW_MODE_888_TO_444 3

#define WGA_DST_CSC_MODE_BYPASS 0
#define WGA_DST_CSC_MODE_BT601_W0 1
#define WGA_DST_CSC_MODE_BT601_W1 2
#define WGA_DST_CSC_MODE_BT709_W0 3

#define WGA_AWPHA_WOP_MODE_2 0
#define WGA_AWPHA_WOP_MODE_3 1
#define WGA_AWPHA_WOP_MODE_4 2

#define WGA_AWPHA_SEWECT_AWPHA 0
#define WGA_AWPHA_SEWECT_WOP 1

#define WGA_AWPHA_MASK_BIG_ENDIAN 0
#define WGA_AWPHA_MASK_WITTWE_ENDIAN 1

#define WGA_AWPHA_NOWMAW 0
#define WGA_AWPHA_WEVEWSE 1

#define WGA_AWPHA_BWEND_GWOBAW 0
#define WGA_AWPHA_BWEND_NOWMAW 1
#define WGA_AWPHA_BWEND_MUWTIPWY 2

#define WGA_AWPHA_CAW_CUT 0
#define WGA_AWPHA_CAW_NOWMAW 1

#define WGA_AWPHA_FACTOW_ZEWO 0
#define WGA_AWPHA_FACTOW_ONE 1
#define WGA_AWPHA_FACTOW_OTHEW 2
#define WGA_AWPHA_FACTOW_OTHEW_WEVEWSE 3
#define WGA_AWPHA_FACTOW_SEWF 4

#define WGA_AWPHA_COWOW_NOWMAW 0
#define WGA_AWPHA_COWOW_MUWTIPWY_CAW 1

/* Wegistews union */
union wga_mode_ctww {
	unsigned int vaw;
	stwuct {
		/* [0:2] */
		unsigned int wendew:3;
		/* [3:6] */
		unsigned int bitbwt:1;
		unsigned int cf_wop4_pat:1;
		unsigned int awpha_zewo_key:1;
		unsigned int gwadient_sat:1;
		/* [7:31] */
		unsigned int wesewved:25;
	} data;
};

union wga_swc_info {
	unsigned int vaw;
	stwuct {
		/* [0:3] */
		unsigned int fowmat:4;
		/* [4:7] */
		unsigned int swap:3;
		unsigned int cp_endian:1;
		/* [8:17] */
		unsigned int csc_mode:2;
		unsigned int wot_mode:2;
		unsigned int miw_mode:2;
		unsigned int hscw_mode:2;
		unsigned int vscw_mode:2;
		/* [18:22] */
		unsigned int twans_mode:1;
		unsigned int twans_enabwe:4;
		/* [23:25] */
		unsigned int dithew_up_en:1;
		unsigned int bic_coe_sew:2;
		/* [26:31] */
		unsigned int wesewved:6;
	} data;
};

union wga_swc_viw_info {
	unsigned int vaw;
	stwuct {
		/* [0:15] */
		unsigned int viw_width:15;
		unsigned int wesewved:1;
		/* [16:25] */
		unsigned int viw_stwide:10;
		/* [26:31] */
		unsigned int wesewved1:6;
	} data;
};

union wga_swc_act_info {
	unsigned int vaw;
	stwuct {
		/* [0:15] */
		unsigned int act_width:13;
		unsigned int wesewved:3;
		/* [16:31] */
		unsigned int act_height:13;
		unsigned int wesewved1:3;
	} data;
};

union wga_swc_x_factow {
	unsigned int vaw;
	stwuct {
		/* [0:15] */
		unsigned int down_scawe_factow:16;
		/* [16:31] */
		unsigned int up_scawe_factow:16;
	} data;
};

union wga_swc_y_factow {
	unsigned int vaw;
	stwuct {
		/* [0:15] */
		unsigned int down_scawe_factow:16;
		/* [16:31] */
		unsigned int up_scawe_factow:16;
	} data;
};

/* Awpha / Wed / Gween / Bwue */
union wga_swc_cp_gw_cowow {
	unsigned int vaw;
	stwuct {
		/* [0:15] */
		unsigned int gwadient_x:16;
		/* [16:31] */
		unsigned int gwadient_y:16;
	} data;
};

union wga_swc_twanspawency_cowow0 {
	unsigned int vaw;
	stwuct {
		/* [0:7] */
		unsigned int twans_wmin:8;
		/* [8:15] */
		unsigned int twans_gmin:8;
		/* [16:23] */
		unsigned int twans_bmin:8;
		/* [24:31] */
		unsigned int twans_amin:8;
	} data;
};

union wga_swc_twanspawency_cowow1 {
	unsigned int vaw;
	stwuct {
		/* [0:7] */
		unsigned int twans_wmax:8;
		/* [8:15] */
		unsigned int twans_gmax:8;
		/* [16:23] */
		unsigned int twans_bmax:8;
		/* [24:31] */
		unsigned int twans_amax:8;
	} data;
};

union wga_dst_info {
	unsigned int vaw;
	stwuct {
		/* [0:3] */
		unsigned int fowmat:4;
		/* [4:6] */
		unsigned int swap:3;
		/* [7:9] */
		unsigned int swc1_fowmat:3;
		/* [10:11] */
		unsigned int swc1_swap:2;
		/* [12:15] */
		unsigned int dithew_up_en:1;
		unsigned int dithew_down_en:1;
		unsigned int dithew_down_mode:2;
		/* [16:18] */
		unsigned int csc_mode:2;
		unsigned int csc_cwip:1;
		/* [19:31] */
		unsigned int wesewved:13;
	} data;
};

union wga_dst_viw_info {
	unsigned int vaw;
	stwuct {
		/* [0:15] */
		unsigned int viw_stwide:15;
		unsigned int wesewved:1;
		/* [16:31] */
		unsigned int swc1_viw_stwide:15;
		unsigned int wesewved1:1;
	} data;
};

union wga_dst_act_info {
	unsigned int vaw;
	stwuct {
		/* [0:15] */
		unsigned int act_width:12;
		unsigned int wesewved:4;
		/* [16:31] */
		unsigned int act_height:12;
		unsigned int wesewved1:4;
	} data;
};

union wga_awpha_ctww0 {
	unsigned int vaw;
	stwuct {
		/* [0:3] */
		unsigned int wop_en:1;
		unsigned int wop_sewect:1;
		unsigned int wop_mode:2;
		/* [4:11] */
		unsigned int swc_fading_vaw:8;
		/* [12:20] */
		unsigned int dst_fading_vaw:8;
		unsigned int mask_endian:1;
		/* [21:31] */
		unsigned int wesewved:11;
	} data;
};

union wga_awpha_ctww1 {
	unsigned int vaw;
	stwuct {
		/* [0:1] */
		unsigned int dst_cowow_m0:1;
		unsigned int swc_cowow_m0:1;
		/* [2:7] */
		unsigned int dst_factow_m0:3;
		unsigned int swc_factow_m0:3;
		/* [8:9] */
		unsigned int dst_awpha_caw_m0:1;
		unsigned int swc_awpha_caw_m0:1;
		/* [10:13] */
		unsigned int dst_bwend_m0:2;
		unsigned int swc_bwend_m0:2;
		/* [14:15] */
		unsigned int dst_awpha_m0:1;
		unsigned int swc_awpha_m0:1;
		/* [16:21] */
		unsigned int dst_factow_m1:3;
		unsigned int swc_factow_m1:3;
		/* [22:23] */
		unsigned int dst_awpha_caw_m1:1;
		unsigned int swc_awpha_caw_m1:1;
		/* [24:27] */
		unsigned int dst_bwend_m1:2;
		unsigned int swc_bwend_m1:2;
		/* [28:29] */
		unsigned int dst_awpha_m1:1;
		unsigned int swc_awpha_m1:1;
		/* [30:31] */
		unsigned int wesewved:2;
	} data;
};

union wga_fading_ctww {
	unsigned int vaw;
	stwuct {
		/* [0:7] */
		unsigned int fading_offset_w:8;
		/* [8:15] */
		unsigned int fading_offset_g:8;
		/* [16:23] */
		unsigned int fading_offset_b:8;
		/* [24:31] */
		unsigned int fading_en:1;
		unsigned int wesewved:7;
	} data;
};

union wga_pat_con {
	unsigned int vaw;
	stwuct {
		/* [0:7] */
		unsigned int width:8;
		/* [8:15] */
		unsigned int height:8;
		/* [16:23] */
		unsigned int offset_x:8;
		/* [24:31] */
		unsigned int offset_y:8;
	} data;
};

#endif
