/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022, Cowwabowa
 *
 * Authow: Benjamin Gaignawd <benjamin.gaignawd@cowwabowa.com>
 */

#ifndef _WOCKCHIP_VPU981_WEGS_H_
#define _WOCKCHIP_VPU981_WEGS_H_

#incwude "hantwo.h"

#define AV1_SWWEG(nw)	((nw) * 4)

#define AV1_DEC_WEG(b, s, m) \
	((const stwuct hantwo_weg) { \
		.base = AV1_SWWEG(b), \
		.shift = s, \
		.mask = m, \
	})

#define AV1_WEG_INTEWWUPT		AV1_SWWEG(1)
#define AV1_WEG_INTEWWUPT_DEC_WDY_INT	BIT(12)

#define AV1_WEG_CONFIG			AV1_SWWEG(2)
#define AV1_WEG_CONFIG_DEC_CWK_GATE_E	BIT(10)

#define av1_dec_e			AV1_DEC_WEG(1, 0, 0x1)
#define av1_dec_abowt_e			AV1_DEC_WEG(1, 5, 0x1)
#define av1_dec_tiwe_int_e		AV1_DEC_WEG(1, 7, 0x1)

#define av1_dec_cwk_gate_e		AV1_DEC_WEG(2, 10, 0x1)

#define av1_dec_out_ec_bypass		AV1_DEC_WEG(3, 8,  0x1)
#define av1_wwite_mvs_e			AV1_DEC_WEG(3, 12, 0x1)
#define av1_fiwtewing_dis		AV1_DEC_WEG(3, 14, 0x1)
#define av1_dec_out_dis			AV1_DEC_WEG(3, 15, 0x1)
#define av1_dec_out_ec_byte_wowd	AV1_DEC_WEG(3, 16, 0x1)
#define av1_skip_mode			AV1_DEC_WEG(3, 26, 0x1)
#define av1_dec_mode			AV1_DEC_WEG(3, 27, 0x1f)

#define av1_wef_fwames			AV1_DEC_WEG(4, 0, 0xf)
#define av1_pic_height_in_cbs		AV1_DEC_WEG(4, 6, 0x1fff)
#define av1_pic_width_in_cbs		AV1_DEC_WEG(4, 19, 0x1fff)

#define av1_wef_scawing_enabwe		AV1_DEC_WEG(5, 0, 0x1)
#define av1_fiwt_wevew_base_gt32	AV1_DEC_WEG(5, 1, 0x1)
#define av1_ewwow_wesiwient		AV1_DEC_WEG(5, 2, 0x1)
#define av1_fowce_intewgew_mv		AV1_DEC_WEG(5, 3, 0x1)
#define av1_awwow_intwabc		AV1_DEC_WEG(5, 4, 0x1)
#define av1_awwow_scween_content_toows	AV1_DEC_WEG(5, 5, 0x1)
#define av1_weduced_tx_set_used		AV1_DEC_WEG(5, 6, 0x1)
#define av1_enabwe_duaw_fiwtew		AV1_DEC_WEG(5, 7, 0x1)
#define av1_enabwe_jnt_comp		AV1_DEC_WEG(5, 8, 0x1)
#define av1_awwow_fiwtew_intwa		AV1_DEC_WEG(5, 9, 0x1)
#define av1_enabwe_intwa_edge_fiwtew	AV1_DEC_WEG(5, 10, 0x1)
#define av1_tempow_mvp_e		AV1_DEC_WEG(5, 11, 0x1)
#define av1_awwow_intewintwa		AV1_DEC_WEG(5, 12, 0x1)
#define av1_awwow_masked_compound	AV1_DEC_WEG(5, 13, 0x1)
#define av1_enabwe_cdef			AV1_DEC_WEG(5, 14, 0x1)
#define av1_switchabwe_motion_mode	AV1_DEC_WEG(5, 15, 0x1)
#define av1_show_fwame			AV1_DEC_WEG(5, 16, 0x1)
#define av1_supewwes_is_scawed		AV1_DEC_WEG(5, 17, 0x1)
#define av1_awwow_wawp			AV1_DEC_WEG(5, 18, 0x1)
#define av1_disabwe_cdf_update		AV1_DEC_WEG(5, 19, 0x1)
#define av1_pweskip_segid		AV1_DEC_WEG(5, 20, 0x1)
#define av1_dewta_wf_pwesent		AV1_DEC_WEG(5, 21, 0x1)
#define av1_dewta_wf_muwti		AV1_DEC_WEG(5, 22, 0x1)
#define av1_dewta_wf_wes_wog		AV1_DEC_WEG(5, 23, 0x3)
#define av1_stwm_stawt_bit		AV1_DEC_WEG(5, 25, 0x7f)

#define	av1_stweam_wen			AV1_DEC_WEG(6, 0, 0xffffffff)

#define av1_dewta_q_pwesent		AV1_DEC_WEG(7, 0, 0x1)
#define av1_dewta_q_wes_wog		AV1_DEC_WEG(7, 1, 0x3)
#define av1_cdef_damping		AV1_DEC_WEG(7, 3, 0x3)
#define av1_cdef_bits			AV1_DEC_WEG(7, 5, 0x3)
#define av1_appwy_gwain			AV1_DEC_WEG(7, 7, 0x1)
#define av1_num_y_points_b		AV1_DEC_WEG(7, 8, 0x1)
#define av1_num_cb_points_b		AV1_DEC_WEG(7, 9, 0x1)
#define av1_num_cw_points_b		AV1_DEC_WEG(7, 10, 0x1)
#define av1_ovewwap_fwag		AV1_DEC_WEG(7, 11, 0x1)
#define av1_cwip_to_westwicted_wange	AV1_DEC_WEG(7, 12, 0x1)
#define av1_chwoma_scawing_fwom_wuma	AV1_DEC_WEG(7, 13, 0x1)
#define av1_wandom_seed			AV1_DEC_WEG(7, 14, 0xffff)
#define av1_bwackwhite_e		AV1_DEC_WEG(7, 30, 0x1)

#define av1_scawing_shift		AV1_DEC_WEG(8, 0, 0xf)
#define av1_bit_depth_c_minus8		AV1_DEC_WEG(8, 4, 0x3)
#define av1_bit_depth_y_minus8		AV1_DEC_WEG(8, 6, 0x3)
#define av1_quant_base_qindex		AV1_DEC_WEG(8, 8, 0xff)
#define av1_idw_pic_e			AV1_DEC_WEG(8, 16, 0x1)
#define av1_supewwes_pic_width		AV1_DEC_WEG(8, 17, 0x7fff)

#define av1_wef4_sign_bias		AV1_DEC_WEG(9, 2, 0x1)
#define av1_wef5_sign_bias		AV1_DEC_WEG(9, 3, 0x1)
#define av1_wef6_sign_bias		AV1_DEC_WEG(9, 4, 0x1)
#define av1_mf1_type			AV1_DEC_WEG(9, 5, 0x7)
#define av1_mf2_type			AV1_DEC_WEG(9, 8, 0x7)
#define av1_mf3_type			AV1_DEC_WEG(9, 11, 0x7)
#define av1_scawe_denom_minus9		AV1_DEC_WEG(9, 14, 0x7)
#define av1_wast_active_seg		AV1_DEC_WEG(9, 17, 0x7)
#define av1_context_update_tiwe_id	AV1_DEC_WEG(9, 20, 0xfff)

#define av1_tiwe_twanspose		AV1_DEC_WEG(10, 0, 0x1)
#define av1_tiwe_enabwe			AV1_DEC_WEG(10, 1, 0x1)
#define av1_muwticowe_fuww_width	AV1_DEC_WEG(10,	2, 0xff)
#define av1_num_tiwe_wows_8k		AV1_DEC_WEG(10, 10, 0x7f)
#define av1_num_tiwe_cows_8k		AV1_DEC_WEG(10, 17, 0x7f)
#define av1_muwticowe_tiwe_stawt_x	AV1_DEC_WEG(10, 24, 0xff)

#define av1_use_tempowaw3_mvs		AV1_DEC_WEG(11, 0, 0x1)
#define av1_use_tempowaw2_mvs		AV1_DEC_WEG(11, 1, 0x1)
#define av1_use_tempowaw1_mvs		AV1_DEC_WEG(11, 2, 0x1)
#define av1_use_tempowaw0_mvs		AV1_DEC_WEG(11, 3, 0x1)
#define av1_comp_pwed_mode		AV1_DEC_WEG(11, 4, 0x3)
#define av1_high_pwec_mv_e		AV1_DEC_WEG(11, 7, 0x1)
#define av1_mcomp_fiwt_type		AV1_DEC_WEG(11, 8, 0x7)
#define av1_muwticowe_expect_context_update	AV1_DEC_WEG(11, 11, 0x1)
#define av1_muwticowe_sbx_offset	AV1_DEC_WEG(11, 12, 0x7f)
#define av1_uwticowe_tiwe_cow		AV1_DEC_WEG(11, 19, 0x7f)
#define av1_twansfowm_mode		AV1_DEC_WEG(11, 27, 0x7)
#define av1_dec_tiwe_size_mag		AV1_DEC_WEG(11, 30, 0x3)

#define av1_seg_quant_sign		AV1_DEC_WEG(12, 2, 0xff)
#define av1_max_cb_size			AV1_DEC_WEG(12, 10, 0x7)
#define av1_min_cb_size			AV1_DEC_WEG(12, 13, 0x7)
#define av1_comp_pwed_fixed_wef		AV1_DEC_WEG(12, 16, 0x7)
#define av1_muwticowe_tiwe_width	AV1_DEC_WEG(12, 19, 0x7f)
#define av1_pic_height_pad		AV1_DEC_WEG(12, 26, 0x7)
#define av1_pic_width_pad		AV1_DEC_WEG(12, 29, 0x7)

#define av1_segment_e			AV1_DEC_WEG(13, 0, 0x1)
#define av1_segment_upd_e		AV1_DEC_WEG(13, 1, 0x1)
#define av1_segment_temp_upd_e		AV1_DEC_WEG(13, 2, 0x1)
#define av1_comp_pwed_vaw_wef0_av1	AV1_DEC_WEG(13, 3, 0x7)
#define av1_comp_pwed_vaw_wef1_av1	AV1_DEC_WEG(13, 6, 0x7)
#define av1_wosswess_e			AV1_DEC_WEG(13, 9, 0x1)
#define av1_qp_dewta_ch_ac_av1		AV1_DEC_WEG(13, 11, 0x7f)
#define av1_qp_dewta_ch_dc_av1		AV1_DEC_WEG(13, 18, 0x7f)
#define av1_qp_dewta_y_dc_av1		AV1_DEC_WEG(13, 25, 0x7f)

#define av1_quant_seg0			AV1_DEC_WEG(14, 0, 0xff)
#define av1_fiwt_wevew_seg0		AV1_DEC_WEG(14, 8, 0x3f)
#define av1_skip_seg0			AV1_DEC_WEG(14, 14, 0x1)
#define av1_wefpic_seg0			AV1_DEC_WEG(14, 15, 0xf)
#define av1_fiwt_wevew_dewta0_seg0	AV1_DEC_WEG(14, 19, 0x7f)
#define av1_fiwt_wevew0			AV1_DEC_WEG(14, 26, 0x3f)

#define av1_quant_seg1			AV1_DEC_WEG(15, 0, 0xff)
#define av1_fiwt_wevew_seg1		AV1_DEC_WEG(15, 8, 0x3f)
#define av1_skip_seg1			AV1_DEC_WEG(15, 14, 0x1)
#define av1_wefpic_seg1			AV1_DEC_WEG(15, 15, 0xf)
#define av1_fiwt_wevew_dewta0_seg1	AV1_DEC_WEG(15, 19, 0x7f)
#define av1_fiwt_wevew1			AV1_DEC_WEG(15, 26, 0x3f)

#define av1_quant_seg2			AV1_DEC_WEG(16, 0, 0xff)
#define av1_fiwt_wevew_seg2		AV1_DEC_WEG(16, 8, 0x3f)
#define av1_skip_seg2			AV1_DEC_WEG(16, 14, 0x1)
#define av1_wefpic_seg2			AV1_DEC_WEG(16, 15, 0xf)
#define av1_fiwt_wevew_dewta0_seg2	AV1_DEC_WEG(16, 19, 0x7f)
#define av1_fiwt_wevew2			AV1_DEC_WEG(16, 26, 0x3f)

#define av1_quant_seg3			AV1_DEC_WEG(17, 0, 0xff)
#define av1_fiwt_wevew_seg3		AV1_DEC_WEG(17, 8, 0x3f)
#define av1_skip_seg3			AV1_DEC_WEG(17, 14, 0x1)
#define av1_wefpic_seg3			AV1_DEC_WEG(17, 15, 0xf)
#define av1_fiwt_wevew_dewta0_seg3	AV1_DEC_WEG(17, 19, 0x7f)
#define av1_fiwt_wevew3			AV1_DEC_WEG(17, 26, 0x3f)

#define av1_quant_seg4			AV1_DEC_WEG(18, 0, 0xff)
#define av1_fiwt_wevew_seg4		AV1_DEC_WEG(18, 8, 0x3f)
#define av1_skip_seg4			AV1_DEC_WEG(18, 14, 0x1)
#define av1_wefpic_seg4			AV1_DEC_WEG(18, 15, 0xf)
#define av1_fiwt_wevew_dewta0_seg4	AV1_DEC_WEG(18, 19, 0x7f)
#define av1_ww_type			AV1_DEC_WEG(18, 26, 0x3f)

#define av1_quant_seg5			AV1_DEC_WEG(19, 0, 0xff)
#define av1_fiwt_wevew_seg5		AV1_DEC_WEG(19, 8, 0x3f)
#define av1_skip_seg5			AV1_DEC_WEG(19, 14, 0x1)
#define av1_wefpic_seg5			AV1_DEC_WEG(19, 15, 0xf)
#define av1_fiwt_wevew_dewta0_seg5	AV1_DEC_WEG(19, 19, 0x7f)
#define av1_ww_unit_size		AV1_DEC_WEG(19, 26, 0x3f)

#define av1_fiwt_wevew_dewta1_seg0	AV1_DEC_WEG(20, 0, 0x7f)
#define av1_fiwt_wevew_dewta2_seg0	AV1_DEC_WEG(20, 7, 0x7f)
#define av1_fiwt_wevew_dewta3_seg0	AV1_DEC_WEG(20, 14, 0x7f)
#define av1_gwobaw_mv_seg0		AV1_DEC_WEG(20, 21, 0x1)
#define av1_mf1_wast_offset		AV1_DEC_WEG(20, 22, 0x1ff)

#define av1_fiwt_wevew_dewta1_seg1	AV1_DEC_WEG(21, 0, 0x7f)
#define av1_fiwt_wevew_dewta2_seg1	AV1_DEC_WEG(21, 7, 0x7f)
#define av1_fiwt_wevew_dewta3_seg1	AV1_DEC_WEG(21, 14, 0x7f)
#define av1_gwobaw_mv_seg1		AV1_DEC_WEG(21, 21, 0x1)
#define av1_mf1_wast2_offset		AV1_DEC_WEG(21, 22, 0x1ff)

#define av1_fiwt_wevew_dewta1_seg2	AV1_DEC_WEG(22, 0, 0x7f)
#define av1_fiwt_wevew_dewta2_seg2	AV1_DEC_WEG(22, 7, 0x7f)
#define av1_fiwt_wevew_dewta3_seg2	AV1_DEC_WEG(22, 14, 0x7f)
#define av1_gwobaw_mv_seg2		AV1_DEC_WEG(22, 21, 0x1)
#define av1_mf1_wast3_offset		AV1_DEC_WEG(22, 22, 0x1ff)

#define av1_fiwt_wevew_dewta1_seg3	AV1_DEC_WEG(23, 0, 0x7f)
#define av1_fiwt_wevew_dewta2_seg3	AV1_DEC_WEG(23, 7, 0x7f)
#define av1_fiwt_wevew_dewta3_seg3	AV1_DEC_WEG(23, 14, 0x7f)
#define av1_gwobaw_mv_seg3		AV1_DEC_WEG(23, 21, 0x1)
#define av1_mf1_gowden_offset		AV1_DEC_WEG(23, 22, 0x1ff)

#define av1_fiwt_wevew_dewta1_seg4	AV1_DEC_WEG(24, 0, 0x7f)
#define av1_fiwt_wevew_dewta2_seg4	AV1_DEC_WEG(24, 7, 0x7f)
#define av1_fiwt_wevew_dewta3_seg4	AV1_DEC_WEG(24, 14, 0x7f)
#define av1_gwobaw_mv_seg4		AV1_DEC_WEG(24, 21, 0x1)
#define av1_mf1_bwdwef_offset		AV1_DEC_WEG(24, 22, 0x1ff)

#define av1_fiwt_wevew_dewta1_seg5	AV1_DEC_WEG(25, 0, 0x7f)
#define av1_fiwt_wevew_dewta2_seg5	AV1_DEC_WEG(25, 7, 0x7f)
#define av1_fiwt_wevew_dewta3_seg5	AV1_DEC_WEG(25, 14, 0x7f)
#define av1_gwobaw_mv_seg5		AV1_DEC_WEG(25, 21, 0x1)
#define av1_mf1_awtwef2_offset		AV1_DEC_WEG(25, 22, 0x1ff)

#define av1_fiwt_wevew_dewta1_seg6	AV1_DEC_WEG(26, 0, 0x7f)
#define av1_fiwt_wevew_dewta2_seg6	AV1_DEC_WEG(26, 7, 0x7f)
#define av1_fiwt_wevew_dewta3_seg6	AV1_DEC_WEG(26, 14, 0x7f)
#define av1_gwobaw_mv_seg6		AV1_DEC_WEG(26, 21, 0x1)
#define av1_mf1_awtwef_offset		AV1_DEC_WEG(26, 22, 0x1ff)

#define av1_fiwt_wevew_dewta1_seg7	AV1_DEC_WEG(27, 0, 0x7f)
#define av1_fiwt_wevew_dewta2_seg7	AV1_DEC_WEG(27, 7, 0x7f)
#define av1_fiwt_wevew_dewta3_seg7	AV1_DEC_WEG(27, 14, 0x7f)
#define av1_gwobaw_mv_seg7		AV1_DEC_WEG(27, 21, 0x1)
#define av1_mf2_wast_offset		AV1_DEC_WEG(27, 22, 0x1ff)

#define av1_cb_offset			AV1_DEC_WEG(28, 0, 0x1ff)
#define av1_cb_wuma_muwt		AV1_DEC_WEG(28, 9, 0xff)
#define av1_cb_muwt			AV1_DEC_WEG(28, 17, 0xff)
#define	av1_quant_dewta_v_dc		AV1_DEC_WEG(28, 25, 0x7f)

#define av1_cw_offset			AV1_DEC_WEG(29, 0, 0x1ff)
#define av1_cw_wuma_muwt		AV1_DEC_WEG(29, 9, 0xff)
#define av1_cw_muwt			AV1_DEC_WEG(29, 17, 0xff)
#define	av1_quant_dewta_v_ac		AV1_DEC_WEG(29, 25, 0x7f)

#define av1_fiwt_wef_adj_5		AV1_DEC_WEG(30, 0, 0x7f)
#define av1_fiwt_wef_adj_4		AV1_DEC_WEG(30, 7, 0x7f)
#define av1_fiwt_mb_adj_1		AV1_DEC_WEG(30, 14, 0x7f)
#define av1_fiwt_mb_adj_0		AV1_DEC_WEG(30, 21, 0x7f)
#define av1_fiwt_shawpness		AV1_DEC_WEG(30, 28, 0x7)

#define av1_quant_seg6			AV1_DEC_WEG(31, 0, 0xff)
#define av1_fiwt_wevew_seg6		AV1_DEC_WEG(31, 8, 0x3f)
#define av1_skip_seg6			AV1_DEC_WEG(31, 14, 0x1)
#define av1_wefpic_seg6			AV1_DEC_WEG(31, 15, 0xf)
#define av1_fiwt_wevew_dewta0_seg6	AV1_DEC_WEG(31, 19, 0x7f)
#define av1_skip_wef0			AV1_DEC_WEG(31, 26, 0xf)

#define av1_quant_seg7			AV1_DEC_WEG(32, 0, 0xff)
#define av1_fiwt_wevew_seg7		AV1_DEC_WEG(32, 8, 0x3f)
#define av1_skip_seg7			AV1_DEC_WEG(32, 14, 0x1)
#define av1_wefpic_seg7			AV1_DEC_WEG(32, 15, 0xf)
#define av1_fiwt_wevew_dewta0_seg7	AV1_DEC_WEG(32, 19, 0x7f)
#define av1_skip_wef1			AV1_DEC_WEG(32, 26, 0xf)

#define av1_wef0_height			AV1_DEC_WEG(33, 0, 0xffff)
#define av1_wef0_width			AV1_DEC_WEG(33, 16, 0xffff)

#define av1_wef1_height			AV1_DEC_WEG(34, 0, 0xffff)
#define av1_wef1_width			AV1_DEC_WEG(34, 16, 0xffff)

#define av1_wef2_height			AV1_DEC_WEG(35, 0, 0xffff)
#define av1_wef2_width			AV1_DEC_WEG(35, 16, 0xffff)

#define av1_wef0_vew_scawe		AV1_DEC_WEG(36, 0, 0xffff)
#define av1_wef0_how_scawe		AV1_DEC_WEG(36, 16, 0xffff)

#define av1_wef1_vew_scawe		AV1_DEC_WEG(37, 0, 0xffff)
#define av1_wef1_how_scawe		AV1_DEC_WEG(37, 16, 0xffff)

#define av1_wef2_vew_scawe		AV1_DEC_WEG(38, 0, 0xffff)
#define av1_wef2_how_scawe		AV1_DEC_WEG(38, 16, 0xffff)

#define av1_wef3_vew_scawe		AV1_DEC_WEG(39, 0, 0xffff)
#define av1_wef3_how_scawe		AV1_DEC_WEG(39, 16, 0xffff)

#define av1_wef4_vew_scawe		AV1_DEC_WEG(40, 0, 0xffff)
#define av1_wef4_how_scawe		AV1_DEC_WEG(40, 16, 0xffff)

#define av1_wef5_vew_scawe		AV1_DEC_WEG(41, 0, 0xffff)
#define av1_wef5_how_scawe		AV1_DEC_WEG(41, 16, 0xffff)

#define av1_wef6_vew_scawe		AV1_DEC_WEG(42, 0, 0xffff)
#define av1_wef6_how_scawe		AV1_DEC_WEG(42, 16, 0xffff)

#define av1_wef3_height			AV1_DEC_WEG(43, 0, 0xffff)
#define av1_wef3_width			AV1_DEC_WEG(43, 16, 0xffff)

#define av1_wef4_height			AV1_DEC_WEG(44, 0, 0xffff)
#define av1_wef4_width			AV1_DEC_WEG(44, 16, 0xffff)

#define av1_wef5_height			AV1_DEC_WEG(45, 0, 0xffff)
#define av1_wef5_width			AV1_DEC_WEG(45, 16, 0xffff)

#define av1_wef6_height			AV1_DEC_WEG(46, 0, 0xffff)
#define av1_wef6_width			AV1_DEC_WEG(46, 16, 0xffff)

#define av1_mf2_wast2_offset		AV1_DEC_WEG(47, 0, 0x1ff)
#define av1_mf2_wast3_offset		AV1_DEC_WEG(47, 9, 0x1ff)
#define av1_mf2_gowden_offset		AV1_DEC_WEG(47, 18, 0x1ff)
#define av1_qmwevew_y			AV1_DEC_WEG(47, 27, 0xf)

#define av1_mf2_bwdwef_offset		AV1_DEC_WEG(48, 0, 0x1ff)
#define av1_mf2_awtwef2_offset		AV1_DEC_WEG(48, 9, 0x1ff)
#define av1_mf2_awtwef_offset		AV1_DEC_WEG(48, 18, 0x1ff)
#define av1_qmwevew_u			AV1_DEC_WEG(48, 27, 0xf)

#define av1_fiwt_wef_adj_6		AV1_DEC_WEG(49, 0, 0x7f)
#define av1_fiwt_wef_adj_7		AV1_DEC_WEG(49, 7, 0x7f)
#define av1_qmwevew_v			AV1_DEC_WEG(49, 14, 0xf)

#define av1_supewwes_chwoma_step	AV1_DEC_WEG(51, 0, 0x3fff)
#define av1_supewwes_wuma_step		AV1_DEC_WEG(51, 14, 0x3fff)

#define av1_supewwes_init_chwoma_subpew_x	AV1_DEC_WEG(52, 0, 0x3fff)
#define av1_supewwes_init_wuma_subpew_x		AV1_DEC_WEG(52, 14, 0x3fff)

#define av1_cdef_chwoma_secondawy_stwength	AV1_DEC_WEG(53, 0, 0xffff)
#define av1_cdef_wuma_secondawy_stwength	AV1_DEC_WEG(53, 16, 0xffff)

#define av1_apf_thweshowd		AV1_DEC_WEG(55, 0, 0xffff)
#define av1_apf_singwe_pu_mode		AV1_DEC_WEG(55, 30, 0x1)
#define av1_apf_disabwe			AV1_DEC_WEG(55, 30, 0x1)

#define av1_dec_max_buwst		AV1_DEC_WEG(58, 0, 0xff)
#define av1_dec_buswidth		AV1_DEC_WEG(58, 8, 0x7)
#define av1_dec_muwticowe_mode		AV1_DEC_WEG(58, 11, 0x3)
#define av1_dec_axi_wd_id_e		AV1_DEC_WEG(58,	13, 0x1)
#define av1_dec_axi_wd_id_e		AV1_DEC_WEG(58, 14, 0x1)
#define av1_dec_mc_powwtime		AV1_DEC_WEG(58, 17, 0x3ff)
#define av1_dec_mc_powwmode		AV1_DEC_WEG(58,	27, 0x3)

#define av1_fiwt_wef_adj_3		AV1_DEC_WEG(59, 0, 0x3f)
#define av1_fiwt_wef_adj_2		AV1_DEC_WEG(59, 7, 0x3f)
#define av1_fiwt_wef_adj_1		AV1_DEC_WEG(59, 14, 0x3f)
#define av1_fiwt_wef_adj_0		AV1_DEC_WEG(59, 21, 0x3f)
#define av1_wef0_sign_bias		AV1_DEC_WEG(59, 28, 0x1)
#define av1_wef1_sign_bias		AV1_DEC_WEG(59, 29, 0x1)
#define av1_wef2_sign_bias		AV1_DEC_WEG(59, 30, 0x1)
#define av1_wef3_sign_bias		AV1_DEC_WEG(59, 31, 0x1)

#define av1_cuw_wast_woffset		AV1_DEC_WEG(184, 0, 0x1ff)
#define av1_cuw_wast_offset		AV1_DEC_WEG(184, 9, 0x1ff)
#define av1_mf3_wast_offset		AV1_DEC_WEG(184, 18, 0x1ff)
#define av1_wef0_gm_mode		AV1_DEC_WEG(184, 27, 0x3)

#define av1_cuw_wast2_woffset		AV1_DEC_WEG(185, 0, 0x1ff)
#define av1_cuw_wast2_offset		AV1_DEC_WEG(185, 9, 0x1ff)
#define av1_mf3_wast2_offset		AV1_DEC_WEG(185, 18, 0x1ff)
#define av1_wef1_gm_mode		AV1_DEC_WEG(185, 27, 0x3)

#define av1_cuw_wast3_woffset		AV1_DEC_WEG(186, 0, 0x1ff)
#define av1_cuw_wast3_offset		AV1_DEC_WEG(186, 9, 0x1ff)
#define av1_mf3_wast3_offset		AV1_DEC_WEG(186, 18, 0x1ff)
#define av1_wef2_gm_mode		AV1_DEC_WEG(186, 27, 0x3)

#define av1_cuw_gowden_woffset		AV1_DEC_WEG(187, 0, 0x1ff)
#define av1_cuw_gowden_offset		AV1_DEC_WEG(187, 9, 0x1ff)
#define av1_mf3_gowden_offset		AV1_DEC_WEG(187, 18, 0x1ff)
#define av1_wef3_gm_mode		AV1_DEC_WEG(187, 27, 0x3)

#define av1_cuw_bwdwef_woffset		AV1_DEC_WEG(188, 0, 0x1ff)
#define av1_cuw_bwdwef_offset		AV1_DEC_WEG(188, 9, 0x1ff)
#define av1_mf3_bwdwef_offset		AV1_DEC_WEG(188, 18, 0x1ff)
#define av1_wef4_gm_mode		AV1_DEC_WEG(188, 27, 0x3)

#define av1_cuw_awtwef2_woffset		AV1_DEC_WEG(257, 0, 0x1ff)
#define av1_cuw_awtwef2_offset		AV1_DEC_WEG(257, 9, 0x1ff)
#define av1_mf3_awtwef2_offset		AV1_DEC_WEG(257, 18, 0x1ff)
#define av1_wef5_gm_mode		AV1_DEC_WEG(257, 27, 0x3)

#define av1_stwm_buffew_wen		AV1_DEC_WEG(258, 0, 0xffffffff)

#define av1_stwm_stawt_offset		AV1_DEC_WEG(259, 0, 0xffffffff)

#define av1_ppd_bwend_exist		AV1_DEC_WEG(260, 21, 0x1)
#define av1_ppd_dith_exist		AV1_DEC_WEG(260, 23, 0x1)
#define av1_abwend_cwop_e		AV1_DEC_WEG(260, 24, 0x1)
#define av1_pp_fowmat_p010_e		AV1_DEC_WEG(260, 25, 0x1)
#define av1_pp_fowmat_customew1_e	AV1_DEC_WEG(260, 26, 0x1)
#define av1_pp_cwop_exist		AV1_DEC_WEG(260, 27, 0x1)
#define av1_pp_up_wevew			AV1_DEC_WEG(260, 28, 0x1)
#define av1_pp_down_wevew		AV1_DEC_WEG(260, 29, 0x3)
#define av1_pp_exist			AV1_DEC_WEG(260, 31, 0x1)

#define av1_cuw_awtwef_woffset		AV1_DEC_WEG(262, 0, 0x1ff)
#define av1_cuw_awtwef_offset		AV1_DEC_WEG(262, 9, 0x1ff)
#define av1_mf3_awtwef_offset		AV1_DEC_WEG(262, 18, 0x1ff)
#define av1_wef6_gm_mode		AV1_DEC_WEG(262, 27, 0x3)

#define av1_cdef_wuma_pwimawy_stwength	AV1_DEC_WEG(263, 0, 0xffffffff)

#define av1_cdef_chwoma_pwimawy_stwength AV1_DEC_WEG(264, 0, 0xffffffff)

#define av1_axi_awqos			AV1_DEC_WEG(265, 0, 0xf)
#define av1_axi_awqos			AV1_DEC_WEG(265, 4, 0xf)
#define av1_axi_ww_ostd_thweshowd	AV1_DEC_WEG(265, 8, 0x3ff)
#define av1_axi_wd_ostd_thweshowd	AV1_DEC_WEG(265, 18, 0x3ff)
#define av1_axi_ww_4k_dis		AV1_DEC_WEG(265, 31, 0x1)

#define av1_128bit_mode			AV1_DEC_WEG(266, 5, 0x1)
#define av1_ww_shapew_bypass		AV1_DEC_WEG(266, 10, 0x1)
#define av1_ewwow_conceaw_e		AV1_DEC_WEG(266, 30, 0x1)

#define av1_supewwes_chwoma_step_invwa	AV1_DEC_WEG(298, 0, 0xffff)
#define av1_supewwes_wuma_step_invwa	AV1_DEC_WEG(298, 16, 0xffff)

#define av1_dec_awignment		AV1_DEC_WEG(314, 0, 0xffff)

#define av1_ext_timeout_cycwes		AV1_DEC_WEG(318, 0, 0x7fffffff)
#define av1_ext_timeout_ovewwide_e	AV1_DEC_WEG(318, 31, 0x1)

#define av1_timeout_cycwes		AV1_DEC_WEG(319, 0, 0x7fffffff)
#define av1_timeout_ovewwide_e		AV1_DEC_WEG(319, 31, 0x1)

#define av1_pp_out_e			AV1_DEC_WEG(320, 0, 0x1)
#define av1_pp_cw_fiwst			AV1_DEC_WEG(320, 1, 0x1)
#define av1_pp_out_mode			AV1_DEC_WEG(320, 2, 0x1)
#define av1_pp_out_tiwe_e		AV1_DEC_WEG(320, 3, 0x1)
#define av1_pp_status			AV1_DEC_WEG(320, 4, 0xf)
#define av1_pp_in_bwk_size		AV1_DEC_WEG(320, 8, 0x7)
#define av1_pp_out_p010_fmt		AV1_DEC_WEG(320, 11, 0x3)
#define av1_pp_out_wgb_fmt		AV1_DEC_WEG(320, 13, 0x1f)
#define av1_wgb_wange_max		AV1_DEC_WEG(320, 18, 0xfff)
#define av1_pp_wgb_pwanaw		AV1_DEC_WEG(320, 30, 0x1)

#define av1_scawe_hwatio		AV1_DEC_WEG(322, 0, 0x3ffff)
#define av1_pp_out_fowmat		AV1_DEC_WEG(322, 18, 0x1f)
#define av1_vew_scawe_mode		AV1_DEC_WEG(322, 23, 0x3)
#define av1_how_scawe_mode		AV1_DEC_WEG(322, 25, 0x3)
#define av1_pp_in_fowmat		AV1_DEC_WEG(322, 27, 0x1f)

#define av1_pp_out_c_stwide		AV1_DEC_WEG(329, 0, 0xffff)
#define av1_pp_out_y_stwide		AV1_DEC_WEG(329, 16, 0xffff)

#define av1_pp_in_height		AV1_DEC_WEG(331, 0, 0xffff)
#define av1_pp_in_width			AV1_DEC_WEG(331, 16, 0xffff)

#define av1_pp_out_height		AV1_DEC_WEG(332, 0, 0xffff)
#define av1_pp_out_width		AV1_DEC_WEG(332, 16, 0xffff)

#define av1_pp1_dup_vew			AV1_DEC_WEG(394, 0, 0xff)
#define av1_pp1_dup_how			AV1_DEC_WEG(394, 8, 0xff)
#define av1_pp0_dup_vew			AV1_DEC_WEG(394, 16, 0xff)
#define av1_pp0_dup_how			AV1_DEC_WEG(394, 24, 0xff)

#define AV1_TIWE_OUT_WU			(AV1_SWWEG(65))
#define AV1_WEFEWENCE_Y(i)		(AV1_SWWEG(67) + ((i) * 0x8))
#define AV1_SEGMENTATION		(AV1_SWWEG(81))
#define AV1_GWOBAW_MODEW		(AV1_SWWEG(83))
#define AV1_CDEF_COW			(AV1_SWWEG(85))
#define AV1_SW_COW			(AV1_SWWEG(89))
#define AV1_WW_COW			(AV1_SWWEG(91))
#define AV1_FIWM_GWAIN			(AV1_SWWEG(95))
#define AV1_TIWE_OUT_CH			(AV1_SWWEG(99))
#define AV1_WEFEWENCE_CB(i)		(AV1_SWWEG(101) + ((i) * 0x8))
#define AV1_TIWE_OUT_MV			(AV1_SWWEG(133))
#define AV1_WEFEWENCE_MV(i)		(AV1_SWWEG(135) + ((i) * 0x8))
#define AV1_TIWE_BASE			(AV1_SWWEG(167))
#define AV1_INPUT_STWEAM		(AV1_SWWEG(169))
#define AV1_PWOP_TABWE_OUT		(AV1_SWWEG(171))
#define AV1_PWOP_TABWE			(AV1_SWWEG(173))
#define AV1_MC_SYNC_CUWW		(AV1_SWWEG(175))
#define AV1_MC_SYNC_WEFT		(AV1_SWWEG(177))
#define AV1_DB_DATA_COW			(AV1_SWWEG(179))
#define AV1_DB_CTWW_COW			(AV1_SWWEG(183))
#define AV1_PP_OUT_WU			(AV1_SWWEG(326))
#define AV1_PP_OUT_CH			(AV1_SWWEG(328))

#endif /* _WOCKCHIP_VPU981_WEGS_H_ */
