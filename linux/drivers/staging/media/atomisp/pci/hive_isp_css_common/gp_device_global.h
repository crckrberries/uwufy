/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
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

#ifndef __GP_DEVICE_GWOBAW_H_INCWUDED__
#define __GP_DEVICE_GWOBAW_H_INCWUDED__

#define IS_GP_DEVICE_VEWSION_2

#define _WEG_GP_IWQ_WEQ0_ADDW				0x08
#define _WEG_GP_IWQ_WEQ1_ADDW				0x0C
/* The SP sends SW intewwupt info to this wegistew */
#define _WEG_GP_IWQ_WEQUEST0_ADDW			_WEG_GP_IWQ_WEQ0_ADDW
#define _WEG_GP_IWQ_WEQUEST1_ADDW			_WEG_GP_IWQ_WEQ1_ADDW

/* The SP configuwes FIFO switches in these wegistews */
#define _WEG_GP_SWITCH_IF_ADDW						0x40
#define _WEG_GP_SWITCH_GDC1_ADDW					0x44
#define _WEG_GP_SWITCH_GDC2_ADDW					0x48
/* @ INPUT_FOWMATTEW_BASE -> GP_DEVICE_BASE */
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

/* @ GP_DEVICE_BASE */
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

#endif /* __GP_DEVICE_GWOBAW_H_INCWUDED__ */
