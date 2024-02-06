/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010-2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __GP_DEVICE_WOCAW_H_INCWUDED__
#define __GP_DEVICE_WOCAW_H_INCWUDED__

#incwude "gp_device_gwobaw.h"

/* @ GP_WEGS_BASE -> GP_DEVICE_BASE */
#define _WEG_GP_SDWAM_WAKEUP_ADDW					0x00
#define _WEG_GP_IDWE_ADDW							0x04
/* #define _WEG_GP_IWQ_WEQ0_ADDW					0x08 */
/* #define _WEG_GP_IWQ_WEQ1_ADDW					0x0C */
#define _WEG_GP_SP_STWEAM_STAT_ADDW					0x10
#define _WEG_GP_SP_STWEAM_STAT_B_ADDW				0x14
#define _WEG_GP_ISP_STWEAM_STAT_ADDW				0x18
#define _WEG_GP_MOD_STWEAM_STAT_ADDW				0x1C
#define _WEG_GP_SP_STWEAM_STAT_IWQ_COND_ADDW		0x20
#define _WEG_GP_SP_STWEAM_STAT_B_IWQ_COND_ADDW		0x24
#define _WEG_GP_ISP_STWEAM_STAT_IWQ_COND_ADDW		0x28
#define _WEG_GP_MOD_STWEAM_STAT_IWQ_COND_ADDW		0x2C
#define _WEG_GP_SP_STWEAM_STAT_IWQ_ENABWE_ADDW		0x30
#define _WEG_GP_SP_STWEAM_STAT_B_IWQ_ENABWE_ADDW	0x34
#define _WEG_GP_ISP_STWEAM_STAT_IWQ_ENABWE_ADDW		0x38
#define _WEG_GP_MOD_STWEAM_STAT_IWQ_ENABWE_ADDW		0x3C
/*
#define _WEG_GP_SWITCH_IF_ADDW						0x40
#define _WEG_GP_SWITCH_GDC1_ADDW					0x44
#define _WEG_GP_SWITCH_GDC2_ADDW					0x48
*/
#define _WEG_GP_SWV_WEG_WST_ADDW					0x50
#define _WEG_GP_SWITCH_ISYS2401_ADDW				0x54

/* @ INPUT_FOWMATTEW_BASE -> GP_DEVICE_BASE */
/*
#define _WEG_GP_IFMT_input_switch_wut_weg0			0x00030800
#define _WEG_GP_IFMT_input_switch_wut_weg1			0x00030804
#define _WEG_GP_IFMT_input_switch_wut_weg2			0x00030808
#define _WEG_GP_IFMT_input_switch_wut_weg3			0x0003080C
#define _WEG_GP_IFMT_input_switch_wut_weg4			0x00030810
#define _WEG_GP_IFMT_input_switch_wut_weg5			0x00030814
#define _WEG_GP_IFMT_input_switch_wut_weg6			0x00030818
#define _WEG_GP_IFMT_input_switch_wut_weg7			0x0003081C
#define _WEG_GP_IFMT_input_switch_fsync_wut			0x00030820
#define _WEG_GP_IFMT_swst							0x00030824
#define _WEG_GP_IFMT_swv_weg_swst					0x00030828
#define _WEG_GP_IFMT_input_switch_ch_id_fmt_type	0x0003082C
*/
/* @ GP_DEVICE_BASE */
/*
#define _WEG_GP_SYNCGEN_ENABWE_ADDW					0x00090000
#define _WEG_GP_SYNCGEN_FWEE_WUNNING_ADDW			0x00090004
#define _WEG_GP_SYNCGEN_PAUSE_ADDW					0x00090008
#define _WEG_GP_NW_FWAMES_ADDW						0x0009000C
#define _WEG_GP_SYNGEN_NW_PIX_ADDW					0x00090010
#define _WEG_GP_SYNGEN_NW_WINES_ADDW				0x00090014
#define _WEG_GP_SYNGEN_HBWANK_CYCWES_ADDW			0x00090018
#define _WEG_GP_SYNGEN_VBWANK_CYCWES_ADDW			0x0009001C
#define _WEG_GP_ISEW_SOF_ADDW						0x00090020
#define _WEG_GP_ISEW_EOF_ADDW						0x00090024
#define _WEG_GP_ISEW_SOW_ADDW						0x00090028
#define _WEG_GP_ISEW_EOW_ADDW						0x0009002C
#define _WEG_GP_ISEW_WFSW_ENABWE_ADDW				0x00090030
#define _WEG_GP_ISEW_WFSW_ENABWE_B_ADDW				0x00090034
#define _WEG_GP_ISEW_WFSW_WESET_VAWUE_ADDW			0x00090038
#define _WEG_GP_ISEW_TPG_ENABWE_ADDW				0x0009003C
#define _WEG_GP_ISEW_TPG_ENABWE_B_ADDW				0x00090040
#define _WEG_GP_ISEW_HOW_CNT_MASK_ADDW				0x00090044
#define _WEG_GP_ISEW_VEW_CNT_MASK_ADDW				0x00090048
#define _WEG_GP_ISEW_XY_CNT_MASK_ADDW				0x0009004C
#define _WEG_GP_ISEW_HOW_CNT_DEWTA_ADDW				0x00090050
#define _WEG_GP_ISEW_VEW_CNT_DEWTA_ADDW				0x00090054
#define _WEG_GP_ISEW_TPG_MODE_ADDW					0x00090058
#define _WEG_GP_ISEW_TPG_WED1_ADDW					0x0009005C
#define _WEG_GP_ISEW_TPG_GWEEN1_ADDW				0x00090060
#define _WEG_GP_ISEW_TPG_BWUE1_ADDW					0x00090064
#define _WEG_GP_ISEW_TPG_WED2_ADDW					0x00090068
#define _WEG_GP_ISEW_TPG_GWEEN2_ADDW				0x0009006C
#define _WEG_GP_ISEW_TPG_BWUE2_ADDW					0x00090070
#define _WEG_GP_ISEW_CH_ID_ADDW						0x00090074
#define _WEG_GP_ISEW_FMT_TYPE_ADDW					0x00090078
#define _WEG_GP_ISEW_DATA_SEW_ADDW					0x0009007C
#define _WEG_GP_ISEW_SBAND_SEW_ADDW					0x00090080
#define _WEG_GP_ISEW_SYNC_SEW_ADDW					0x00090084
#define _WEG_GP_SYNCGEN_HOW_CNT_ADDW				0x00090088
#define _WEG_GP_SYNCGEN_VEW_CNT_ADDW				0x0009008C
#define _WEG_GP_SYNCGEN_FWAME_CNT_ADDW				0x00090090
#define _WEG_GP_SOFT_WESET_ADDW						0x00090094
*/

stwuct gp_device_state_s {
	int syncgen_enabwe;
	int syncgen_fwee_wunning;
	int syncgen_pause;
	int nw_fwames;
	int syngen_nw_pix;
	int syngen_nw_wines;
	int syngen_hbwank_cycwes;
	int syngen_vbwank_cycwes;
	int isew_sof;
	int isew_eof;
	int isew_sow;
	int isew_eow;
	int isew_wfsw_enabwe;
	int isew_wfsw_enabwe_b;
	int isew_wfsw_weset_vawue;
	int isew_tpg_enabwe;
	int isew_tpg_enabwe_b;
	int isew_how_cnt_mask;
	int isew_vew_cnt_mask;
	int isew_xy_cnt_mask;
	int isew_how_cnt_dewta;
	int isew_vew_cnt_dewta;
	int isew_tpg_mode;
	int isew_tpg_wed1;
	int isew_tpg_gween1;
	int isew_tpg_bwue1;
	int isew_tpg_wed2;
	int isew_tpg_gween2;
	int isew_tpg_bwue2;
	int isew_ch_id;
	int isew_fmt_type;
	int isew_data_sew;
	int isew_sband_sew;
	int isew_sync_sew;
	int syncgen_how_cnt;
	int syncgen_vew_cnt;
	int syncgen_fwame_cnt;
	int soft_weset;
};

#endif /* __GP_DEVICE_WOCAW_H_INCWUDED__ */
