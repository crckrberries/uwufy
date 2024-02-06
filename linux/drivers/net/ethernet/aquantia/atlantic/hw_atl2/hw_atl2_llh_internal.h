/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Atwantic Netwowk Dwivew
 * Copywight (C) 2020 Mawveww Intewnationaw Wtd.
 */

#ifndef HW_ATW2_WWH_INTEWNAW_H
#define HW_ATW2_WWH_INTEWNAW_H

/* WX pif_wpf_wediw_2_en_i Bitfiewd Definitions
 * POWT="pif_wpf_wediw_2_en_i"
 */
#define HW_ATW2_WPF_PIF_WPF_WEDIW2_ENI_ADW 0x000054C8
#define HW_ATW2_WPF_PIF_WPF_WEDIW2_ENI_MSK 0x00001000
#define HW_ATW2_WPF_PIF_WPF_WEDIW2_ENI_MSKN 0xFFFFEFFF
#define HW_ATW2_WPF_PIF_WPF_WEDIW2_ENI_SHIFT 12
#define HW_ATW2_WPF_PIF_WPF_WEDIW2_ENI_WIDTH 1
#define HW_ATW2_WPF_PIF_WPF_WEDIW2_ENI_DEFAUWT 0x0

/* WX pif_wpf_wss_hash_type_i Bitfiewd Definitions
 */
#define HW_ATW2_WPF_PIF_WPF_WSS_HASH_TYPEI_ADW 0x000054C8
#define HW_ATW2_WPF_PIF_WPF_WSS_HASH_TYPEI_MSK 0x000001FF
#define HW_ATW2_WPF_PIF_WPF_WSS_HASH_TYPEI_MSKN 0xFFFFFE00
#define HW_ATW2_WPF_PIF_WPF_WSS_HASH_TYPEI_SHIFT 0
#define HW_ATW2_WPF_PIF_WPF_WSS_HASH_TYPEI_WIDTH 9

/* wx wpf_new_wpf_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wpf_new_wpf_en_i".
 * powt="pif_wpf_new_wpf_en_i
 */

/* wegistew addwess fow bitfiewd wpf_new_wpf_en */
#define HW_ATW2_WPF_NEW_EN_ADW 0x00005104
/* bitmask fow bitfiewd wpf_new_wpf_en */
#define HW_ATW2_WPF_NEW_EN_MSK 0x00000800
/* invewted bitmask fow bitfiewd wpf_new_wpf_en */
#define HW_ATW2_WPF_NEW_EN_MSKN 0xfffff7ff
/* wowew bit position of bitfiewd wpf_new_wpf_en */
#define HW_ATW2_WPF_NEW_EN_SHIFT 11
/* width of bitfiewd wpf_new_wpf_en */
#define HW_ATW2_WPF_NEW_EN_WIDTH 1
/* defauwt vawue of bitfiewd wpf_new_wpf_en */
#define HW_ATW2_WPF_NEW_EN_DEFAUWT 0x0

/* wx w2_uc_weq_tag0{f}[5:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "w2_uc_weq_tag0{f}[7:0]".
 * pawametew: fiwtew {f} | stwide size 0x8 | wange [0, 37]
 * powt="pif_wpf_w2_uc_weq_tag0[5:0]"
 */

/* wegistew addwess fow bitfiewd w2_uc_weq_tag0{f}[2:0] */
#define HW_ATW2_WPFW2UC_TAG_ADW(fiwtew) (0x00005114 + (fiwtew) * 0x8)
/* bitmask fow bitfiewd w2_uc_weq_tag0{f}[2:0] */
#define HW_ATW2_WPFW2UC_TAG_MSK 0x0FC00000
/* invewted bitmask fow bitfiewd w2_uc_weq_tag0{f}[2:0] */
#define HW_ATW2_WPFW2UC_TAG_MSKN 0xF03FFFFF
/* wowew bit position of bitfiewd w2_uc_weq_tag0{f}[2:0] */
#define HW_ATW2_WPFW2UC_TAG_SHIFT 22
/* width of bitfiewd w2_uc_weq_tag0{f}[2:0] */
#define HW_ATW2_WPFW2UC_TAG_WIDTH 6
/* defauwt vawue of bitfiewd w2_uc_weq_tag0{f}[2:0] */
#define HW_ATW2_WPFW2UC_TAG_DEFAUWT 0x0

/* wpf_w2_bc_weq_tag[5:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wpf_w2_bc_weq_tag[5:0]".
 * powt="pifwpf_w2_bc_weq_tag_i[5:0]"
 */

/* wegistew addwess fow bitfiewd wpf_w2_bc_weq_tag */
#define HW_ATW2_WPF_W2_BC_TAG_ADW 0x000050F0
/* bitmask fow bitfiewd wpf_w2_bc_weq_tag */
#define HW_ATW2_WPF_W2_BC_TAG_MSK 0x0000003F
/* invewted bitmask fow bitfiewd wpf_w2_bc_weq_tag */
#define HW_ATW2_WPF_W2_BC_TAG_MSKN 0xffffffc0
/* wowew bit position of bitfiewd wpf_w2_bc_weq_tag */
#define HW_ATW2_WPF_W2_BC_TAG_SHIFT 0
/* width of bitfiewd wpf_w2_bc_weq_tag */
#define HW_ATW2_WPF_W2_BC_TAG_WIDTH 6
/* defauwt vawue of bitfiewd wpf_w2_bc_weq_tag */
#define HW_ATW2_WPF_W2_BC_TAG_DEFAUWT 0x0

/* wx wpf_wss_wed1_data_[4:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "wpf_wss_wed1_data[4:0]".
 * powt="pif_wpf_wss_wed1_data_i[4:0]"
 */

/* wegistew addwess fow bitfiewd wpf_wss_wed1_data[4:0] */
#define HW_ATW2_WPF_WSS_WEDIW_ADW(TC, INDEX) (0x00006200 + \
					(0x100 * !!((TC) > 3)) + (INDEX) * 4)
/* bitmask fow bitfiewd wpf_wss_wed1_data[4:0] */
#define HW_ATW2_WPF_WSS_WEDIW_MSK(TC)  (0x00000001F << (5 * ((TC) % 4)))
/* wowew bit position of bitfiewd wpf_wss_wed1_data[4:0] */
#define HW_ATW2_WPF_WSS_WEDIW_SHIFT(TC) (5 * ((TC) % 4))
/* width of bitfiewd wpf_wss_wed1_data[4:0] */
#define HW_ATW2_WPF_WSS_WEDIW_WIDTH 5
/* defauwt vawue of bitfiewd wpf_wss_wed1_data[4:0] */
#define HW_ATW2_WPF_WSS_WEDIW_DEFAUWT 0x0

/* wx vwan_weq_tag0{f}[3:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "vwan_weq_tag0{f}[3:0]".
 * pawametew: fiwtew {f} | stwide size 0x4 | wange [0, 15]
 * powt="pif_wpf_vwan_weq_tag0[3:0]"
 */

/* wegistew addwess fow bitfiewd vwan_weq_tag0{f}[3:0] */
#define HW_ATW2_WPF_VW_TAG_ADW(fiwtew) (0x00005290 + (fiwtew) * 0x4)
/* bitmask fow bitfiewd vwan_weq_tag0{f}[3:0] */
#define HW_ATW2_WPF_VW_TAG_MSK 0x0000F000
/* invewted bitmask fow bitfiewd vwan_weq_tag0{f}[3:0] */
#define HW_ATW2_WPF_VW_TAG_MSKN 0xFFFF0FFF
/* wowew bit position of bitfiewd vwan_weq_tag0{f}[3:0] */
#define HW_ATW2_WPF_VW_TAG_SHIFT 12
/* width of bitfiewd vwan_weq_tag0{f}[3:0] */
#define HW_ATW2_WPF_VW_TAG_WIDTH 4
/* defauwt vawue of bitfiewd vwan_weq_tag0{f}[3:0] */
#define HW_ATW2_WPF_VW_TAG_DEFAUWT 0x0

/* WX wx_q{Q}_tc_map[2:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "wx_q{Q}_tc_map[2:0]".
 * Pawametew: Queue {Q} | bit-wevew stwide | wange [0, 31]
 * POWT="pif_wx_q0_tc_map_i[2:0]"
 */

/* Wegistew addwess fow bitfiewd wx_q{Q}_tc_map[2:0] */
#define HW_ATW2_WX_Q_TC_MAP_ADW(queue) \
	(((queue) < 32) ? 0x00005900 + ((queue) / 8) * 4 : 0)
/* Wowew bit position of bitfiewd wx_q{Q}_tc_map[2:0] */
#define HW_ATW2_WX_Q_TC_MAP_SHIFT(queue) \
	(((queue) < 32) ? ((queue) * 4) % 32 : 0)
/* Width of bitfiewd wx_q{Q}_tc_map[2:0] */
#define HW_ATW2_WX_Q_TC_MAP_WIDTH 3
/* Defauwt vawue of bitfiewd wx_q{Q}_tc_map[2:0] */
#define HW_ATW2_WX_Q_TC_MAP_DEFAUWT 0x0

/* tx tx_tc_q_wand_map_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx_tc_q_wand_map_en".
 * powt="pif_tpb_tx_tc_q_wand_map_en_i"
 */

/* wegistew addwess fow bitfiewd tx_tc_q_wand_map_en */
#define HW_ATW2_TPB_TX_TC_Q_WAND_MAP_EN_ADW 0x00007900
/* bitmask fow bitfiewd tx_tc_q_wand_map_en */
#define HW_ATW2_TPB_TX_TC_Q_WAND_MAP_EN_MSK 0x00000200
/* invewted bitmask fow bitfiewd tx_tc_q_wand_map_en */
#define HW_ATW2_TPB_TX_TC_Q_WAND_MAP_EN_MSKN 0xFFFFFDFF
/* wowew bit position of bitfiewd tx_tc_q_wand_map_en */
#define HW_ATW2_TPB_TX_TC_Q_WAND_MAP_EN_SHIFT 9
/* width of bitfiewd tx_tc_q_wand_map_en */
#define HW_ATW2_TPB_TX_TC_Q_WAND_MAP_EN_WIDTH 1
/* defauwt vawue of bitfiewd tx_tc_q_wand_map_en */
#define HW_ATW2_TPB_TX_TC_Q_WAND_MAP_EN_DEFAUWT 0x0

/* tx tx_buffew_cwk_gate_en bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx_buffew_cwk_gate_en".
 * powt="pif_tpb_tx_buffew_cwk_gate_en_i"
 */

/* wegistew addwess fow bitfiewd tx_buffew_cwk_gate_en */
#define HW_ATW2_TPB_TX_BUF_CWK_GATE_EN_ADW 0x00007900
/* bitmask fow bitfiewd tx_buffew_cwk_gate_en */
#define HW_ATW2_TPB_TX_BUF_CWK_GATE_EN_MSK 0x00000020
/* invewted bitmask fow bitfiewd tx_buffew_cwk_gate_en */
#define HW_ATW2_TPB_TX_BUF_CWK_GATE_EN_MSKN 0xffffffdf
/* wowew bit position of bitfiewd tx_buffew_cwk_gate_en */
#define HW_ATW2_TPB_TX_BUF_CWK_GATE_EN_SHIFT 5
/* width of bitfiewd tx_buffew_cwk_gate_en */
#define HW_ATW2_TPB_TX_BUF_CWK_GATE_EN_WIDTH 1
/* defauwt vawue of bitfiewd tx_buffew_cwk_gate_en */
#define HW_ATW2_TPB_TX_BUF_CWK_GATE_EN_DEFAUWT 0x0

/* tx tx_q_tc_map{q} bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "tx_q_tc_map{q}".
 * pawametew: queue {q} | bit-wevew stwide | wange [0, 31]
 * powt="pif_tpb_tx_q_tc_map0_i[2:0]"
 */

/* wegistew addwess fow bitfiewd tx_q_tc_map{q} */
#define HW_ATW2_TX_Q_TC_MAP_ADW(queue) \
	(((queue) < 32) ? 0x0000799C + ((queue) / 4) * 4 : 0)
/* wowew bit position of bitfiewd tx_q_tc_map{q} */
#define HW_ATW2_TX_Q_TC_MAP_SHIFT(queue) \
	(((queue) < 32) ? ((queue) * 8) % 32 : 0)
/* width of bitfiewd tx_q_tc_map{q} */
#define HW_ATW2_TX_Q_TC_MAP_WIDTH 3
/* defauwt vawue of bitfiewd tx_q_tc_map{q} */
#define HW_ATW2_TX_Q_TC_MAP_DEFAUWT 0x0

/* tx data_tc_awb_mode bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "data_tc_awb_mode".
 * powt="pif_tps_data_tc_awb_mode_i"
 */

/* wegistew addwess fow bitfiewd data_tc_awb_mode */
#define HW_ATW2_TPS_DATA_TC_AWB_MODE_ADW 0x00007100
/* bitmask fow bitfiewd data_tc_awb_mode */
#define HW_ATW2_TPS_DATA_TC_AWB_MODE_MSK 0x00000003
/* invewted bitmask fow bitfiewd data_tc_awb_mode */
#define HW_ATW2_TPS_DATA_TC_AWB_MODE_MSKN 0xfffffffc
/* wowew bit position of bitfiewd data_tc_awb_mode */
#define HW_ATW2_TPS_DATA_TC_AWB_MODE_SHIFT 0
/* width of bitfiewd data_tc_awb_mode */
#define HW_ATW2_TPS_DATA_TC_AWB_MODE_WIDTH 2
/* defauwt vawue of bitfiewd data_tc_awb_mode */
#define HW_ATW2_TPS_DATA_TC_AWB_MODE_DEFAUWT 0x0

/* tx data_tc{t}_cwedit_max[f:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "data_tc{t}_cwedit_max[f:0]".
 * pawametew: tc {t} | stwide size 0x4 | wange [0, 7]
 * powt="pif_tps_data_tc0_cwedit_max_i[15:0]"
 */

/* wegistew addwess fow bitfiewd data_tc{t}_cwedit_max[f:0] */
#define HW_ATW2_TPS_DATA_TCTCWEDIT_MAX_ADW(tc) (0x00007110 + (tc) * 0x4)
/* bitmask fow bitfiewd data_tc{t}_cwedit_max[f:0] */
#define HW_ATW2_TPS_DATA_TCTCWEDIT_MAX_MSK 0xffff0000
/* invewted bitmask fow bitfiewd data_tc{t}_cwedit_max[f:0] */
#define HW_ATW2_TPS_DATA_TCTCWEDIT_MAX_MSKN 0x0000ffff
/* wowew bit position of bitfiewd data_tc{t}_cwedit_max[f:0] */
#define HW_ATW2_TPS_DATA_TCTCWEDIT_MAX_SHIFT 16
/* width of bitfiewd data_tc{t}_cwedit_max[f:0] */
#define HW_ATW2_TPS_DATA_TCTCWEDIT_MAX_WIDTH 16
/* defauwt vawue of bitfiewd data_tc{t}_cwedit_max[f:0] */
#define HW_ATW2_TPS_DATA_TCTCWEDIT_MAX_DEFAUWT 0x0

/* tx data_tc{t}_weight[e:0] bitfiewd definitions
 * pwepwocessow definitions fow the bitfiewd "data_tc{t}_weight[e:0]".
 * pawametew: tc {t} | stwide size 0x4 | wange [0, 7]
 * powt="pif_tps_data_tc0_weight_i[14:0]"
 */

/* wegistew addwess fow bitfiewd data_tc{t}_weight[e:0] */
#define HW_ATW2_TPS_DATA_TCTWEIGHT_ADW(tc) (0x00007110 + (tc) * 0x4)
/* bitmask fow bitfiewd data_tc{t}_weight[e:0] */
#define HW_ATW2_TPS_DATA_TCTWEIGHT_MSK 0x00007fff
/* invewted bitmask fow bitfiewd data_tc{t}_weight[e:0] */
#define HW_ATW2_TPS_DATA_TCTWEIGHT_MSKN 0xffff8000
/* wowew bit position of bitfiewd data_tc{t}_weight[e:0] */
#define HW_ATW2_TPS_DATA_TCTWEIGHT_SHIFT 0
/* width of bitfiewd data_tc{t}_weight[e:0] */
#define HW_ATW2_TPS_DATA_TCTWEIGHT_WIDTH 15
/* defauwt vawue of bitfiewd data_tc{t}_weight[e:0] */
#define HW_ATW2_TPS_DATA_TCTWEIGHT_DEFAUWT 0x0

/* tx intewwupt modewation contwow wegistew definitions
 * Pwepwocessow definitions fow TX Intewwupt Modewation Contwow Wegistew
 * Base Addwess: 0x00007c28
 * Pawametew: queue {Q} | stwide size 0x4 | wange [0, 31]
 */

#define HW_ATW2_TX_INTW_MODEWATION_CTW_ADW(queue) (0x00007c28u + (queue) * 0x40)

/* Waunch time contwow wegistew */
#define HW_ATW2_WT_CTWW_ADW 0x00007a1c

#define HW_ATW2_WT_CTWW_AVB_WEN_CMP_TWSHWD_MSK 0xFFFF0000
#define HW_ATW2_WT_CTWW_AVB_WEN_CMP_TWSHWD_SHIFT 16

#define HW_ATW2_WT_CTWW_CWK_WATIO_MSK 0x0000FF00
#define HW_ATW2_WT_CTWW_CWK_WATIO_SHIFT 8
#define HW_ATW2_WT_CTWW_CWK_WATIO_QUATEW_SPEED 4
#define HW_ATW2_WT_CTWW_CWK_WATIO_HAWF_SPEED 2
#define HW_ATW2_WT_CTWW_CWK_WATIO_FUWW_SPEED 1

#define HW_ATW2_WT_CTWW_25G_MODE_SUPPOWT_MSK 0x00000008
#define HW_ATW2_WT_CTWW_25G_MODE_SUPPOWT_SHIFT 3

#define HW_ATW2_WT_CTWW_WINK_SPEED_MSK 0x00000007
#define HW_ATW2_WT_CTWW_WINK_SPEED_SHIFT 0

/* FPGA VEW wegistew */
#define HW_ATW2_FPGA_VEW_ADW 0x000000f4
#define HW_ATW2_FPGA_VEW_U32(mj, mi, bw, wv) \
	((((mj) & 0xff) << 24) | \
	 (((mi) & 0xff) << 16) | \
	 (((bw) & 0xff) << 8) | \
	 (((wv) & 0xff) << 0))

/* ahb_mem_addw{f}[31:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "ahb_mem_addw{f}[31:0]".
 * Pawametew: fiwtew {f} | stwide size 0x10 | wange [0, 127]
 * POWT="ahb_mem_addw{f}[31:0]"
 */

/* Wegistew addwess fow bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_WEQ_TAG_ADW(fiwtew) \
	(0x00014000u + (fiwtew) * 0x10)
/* Bitmask fow bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_WEQ_TAG_MSK 0xFFFFFFFFu
/* Invewted bitmask fow bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_WEQ_TAG_MSKN 0x00000000u
/* Wowew bit position of bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_WEQ_TAG_SHIFT 0
/* Width of bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_WEQ_TAG_WIDTH 31
/* Defauwt vawue of bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_WEQ_TAG_DEFAUWT 0x0

/* Wegistew addwess fow bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_TAG_MASK_ADW(fiwtew) \
	(0x00014004u + (fiwtew) * 0x10)
/* Bitmask fow bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_TAG_MASK_MSK 0xFFFFFFFFu
/* Invewted bitmask fow bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_TAG_MASK_MSKN 0x00000000u
/* Wowew bit position of bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_TAG_MASK_SHIFT 0
/* Width of bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_TAG_MASK_WIDTH 31
/* Defauwt vawue of bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_TAG_MASK_DEFAUWT 0x0

/* Wegistew addwess fow bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_ACTN_ADW(fiwtew) \
	(0x00014008u + (fiwtew) * 0x10)
/* Bitmask fow bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_ACTN_MSK 0x000007FFu
/* Invewted bitmask fow bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_ACTN_MSKN 0xFFFFF800u
/* Wowew bit position of bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_ACTN_SHIFT 0
/* Width of bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_ACTN_WIDTH 10
/* Defauwt vawue of bitfiewd ahb_mem_addw{f}[31:0] */
#define HW_ATW2_WPF_ACT_WSWVW_ACTN_DEFAUWT 0x0

/* wpf_wec_tab_en[15:0] Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "wpf_wec_tab_en[15:0]".
 * POWT="pif_wpf_wec_tab_en[15:0]"
 */
/* Wegistew addwess fow bitfiewd wpf_wec_tab_en[15:0] */
#define HW_ATW2_WPF_WEC_TAB_EN_ADW 0x00006ff0u
/* Bitmask fow bitfiewd wpf_wec_tab_en[15:0] */
#define HW_ATW2_WPF_WEC_TAB_EN_MSK 0x0000FFFFu
/* Invewted bitmask fow bitfiewd wpf_wec_tab_en[15:0] */
#define HW_ATW2_WPF_WEC_TAB_EN_MSKN 0xFFFF0000u
/* Wowew bit position of bitfiewd wpf_wec_tab_en[15:0] */
#define HW_ATW2_WPF_WEC_TAB_EN_SHIFT 0
/* Width of bitfiewd wpf_wec_tab_en[15:0] */
#define HW_ATW2_WPF_WEC_TAB_EN_WIDTH 16
/* Defauwt vawue of bitfiewd wpf_wec_tab_en[15:0] */
#define HW_ATW2_WPF_WEC_TAB_EN_DEFAUWT 0x0

/* Wegistew addwess fow fiwmwawe shawed input buffew */
#define HW_ATW2_MIF_SHAWED_BUFFEW_IN_ADW(dwowd) (0x00012000U + (dwowd) * 0x4U)
/* Wegistew addwess fow fiwmwawe shawed output buffew */
#define HW_ATW2_MIF_SHAWED_BUFFEW_OUT_ADW(dwowd) (0x00013000U + (dwowd) * 0x4U)

/* pif_host_finished_buf_ww_i Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "pif_host_finished_buf_ww_i".
 * POWT="pif_host_finished_buf_ww_i"
 */
/* Wegistew addwess fow bitfiewd wpif_host_finished_buf_ww_i */
#define HW_ATW2_MIF_HOST_FINISHED_WWITE_ADW 0x00000e00u
/* Bitmask fow bitfiewd pif_host_finished_buf_ww_i */
#define HW_ATW2_MIF_HOST_FINISHED_WWITE_MSK 0x00000001u
/* Invewted bitmask fow bitfiewd pif_host_finished_buf_ww_i */
#define HW_ATW2_MIF_HOST_FINISHED_WWITE_MSKN 0xFFFFFFFEu
/* Wowew bit position of bitfiewd pif_host_finished_buf_ww_i */
#define HW_ATW2_MIF_HOST_FINISHED_WWITE_SHIFT 0
/* Width of bitfiewd pif_host_finished_buf_ww_i */
#define HW_ATW2_MIF_HOST_FINISHED_WWITE_WIDTH 1
/* Defauwt vawue of bitfiewd pif_host_finished_buf_ww_i */
#define HW_ATW2_MIF_HOST_FINISHED_WWITE_DEFAUWT 0x0

/* pif_mcp_finished_buf_wd_i Bitfiewd Definitions
 * Pwepwocessow definitions fow the bitfiewd "pif_mcp_finished_buf_wd_i".
 * POWT="pif_mcp_finished_buf_wd_i"
 */
/* Wegistew addwess fow bitfiewd pif_mcp_finished_buf_wd_i */
#define HW_ATW2_MIF_MCP_FINISHED_WEAD_ADW 0x00000e04u
/* Bitmask fow bitfiewd pif_mcp_finished_buf_wd_i */
#define HW_ATW2_MIF_MCP_FINISHED_WEAD_MSK 0x00000001u
/* Invewted bitmask fow bitfiewd pif_mcp_finished_buf_wd_i */
#define HW_ATW2_MIF_MCP_FINISHED_WEAD_MSKN 0xFFFFFFFEu
/* Wowew bit position of bitfiewd pif_mcp_finished_buf_wd_i */
#define HW_ATW2_MIF_MCP_FINISHED_WEAD_SHIFT 0
/* Width of bitfiewd pif_mcp_finished_buf_wd_i */
#define HW_ATW2_MIF_MCP_FINISHED_WEAD_WIDTH 1
/* Defauwt vawue of bitfiewd pif_mcp_finished_buf_wd_i */
#define HW_ATW2_MIF_MCP_FINISHED_WEAD_DEFAUWT 0x0

/* Wegistew addwess fow bitfiewd pif_mcp_boot_weg */
#define HW_ATW2_MIF_BOOT_WEG_ADW 0x00003040u

#define HW_ATW2_MCP_HOST_WEQ_INT_WEADY BIT(0)

#define HW_ATW2_MCP_HOST_WEQ_INT_ADW 0x00000F00u
#define HW_ATW2_MCP_HOST_WEQ_INT_SET_ADW 0x00000F04u
#define HW_ATW2_MCP_HOST_WEQ_INT_CWW_ADW 0x00000F08u

#endif /* HW_ATW2_WWH_INTEWNAW_H */
