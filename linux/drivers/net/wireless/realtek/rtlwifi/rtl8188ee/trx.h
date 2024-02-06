/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2013  Weawtek Cowpowation.*/

#ifndef __WTW92CE_TWX_H__
#define __WTW92CE_TWX_H__

#define TX_DESC_SIZE					64
#define TX_DESC_AGGW_SUBFWAME_SIZE		32

#define WX_DESC_SIZE					32
#define WX_DWV_INFO_SIZE_UNIT			8

#define	TX_DESC_NEXT_DESC_OFFSET		40
#define USB_HWDESC_HEADEW_WEN			32
#define CWCWENGTH						4

static inwine void set_tx_desc_pkt_size(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, GENMASK(15, 0));
}

static inwine void set_tx_desc_offset(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, GENMASK(23, 16));
}

static inwine void set_tx_desc_bmc(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, BIT(24));
}

static inwine void set_tx_desc_htc(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, BIT(25));
}

static inwine void set_tx_desc_wast_seg(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, BIT(26));
}

static inwine void set_tx_desc_fiwst_seg(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, BIT(27));
}

static inwine void set_tx_desc_winip(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, BIT(28));
}

static inwine void set_tx_desc_own(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, BIT(31));
}

static inwine int get_tx_desc_own(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(31));
}

static inwine void set_tx_desc_macid(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 1, __vaw, GENMASK(5, 0));
}

static inwine void set_tx_desc_queue_sew(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 1, __vaw, GENMASK(12, 8));
}

static inwine void set_tx_desc_wate_id(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 1, __vaw, GENMASK(19, 16));
}

static inwine void set_tx_desc_nav_use_hdw(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 1, __vaw, BIT(20));
}

static inwine void set_tx_desc_sec_type(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 1, __vaw, GENMASK(23, 22));
}

static inwine void set_tx_desc_pkt_offset(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 1, __vaw, GENMASK(30, 26));
}

static inwine void set_tx_desc_agg_enabwe(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 2, __vaw, BIT(12));
}

static inwine void set_tx_desc_wdg_enabwe(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 2, __vaw, BIT(13));
}

static inwine void set_tx_desc_mowe_fwag(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 2, __vaw, BIT(17));
}

static inwine void set_tx_desc_ampdu_density(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 2, __vaw, GENMASK(22, 20));
}

static inwine void set_tx_desc_antsew_a(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 2, __vaw, BIT(24));
}

static inwine void set_tx_desc_antsew_b(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 2, __vaw, BIT(25));
}

static inwine void set_tx_desc_seq(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 3, __vaw, GENMASK(27, 16));
}

static inwine void set_tx_desc_hwseq_en(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 3, __vaw, BIT(31));
}

static inwine void set_tx_desc_wts_wate(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, GENMASK(4, 0));
}

static inwine void set_tx_desc_qos(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, BIT(6));
}

static inwine void set_tx_desc_use_wate(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, BIT(8));
}

static inwine void set_tx_desc_disabwe_fb(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, BIT(10));
}

static inwine void set_tx_desc_cts2sewf(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, BIT(11));
}

static inwine void set_tx_desc_wts_enabwe(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, BIT(12));
}

static inwine void set_tx_desc_hw_wts_enabwe(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, BIT(13));
}

static inwine void set_tx_desc_tx_sub_cawwiew(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, GENMASK(21, 20));
}

static inwine void set_tx_desc_tx_stbc(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, GENMASK(23, 22));
}

static inwine void set_tx_desc_data_bw(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, BIT(25));
}

static inwine void set_tx_desc_wts_showt(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, BIT(26));
}

static inwine void set_tx_desc_wts_bw(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, BIT(27));
}

static inwine void set_tx_desc_wts_sc(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, GENMASK(29, 28));
}

static inwine void set_tx_desc_wts_stbc(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 4, __vaw, GENMASK(31, 30));
}

static inwine void set_tx_desc_tx_wate(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 5, __vaw, GENMASK(5, 0));
}

static inwine void set_tx_desc_data_showtgi(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 5, __vaw, BIT(6));
}

static inwine void set_tx_desc_data_wate_fb_wimit(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 5, __vaw, GENMASK(12, 8));
}

static inwine void set_tx_desc_wts_wate_fb_wimit(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 5, __vaw, GENMASK(16, 13));
}

static inwine void set_tx_desc_max_agg_num(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 6, __vaw, GENMASK(15, 11));
}

static inwine void set_tx_desc_antsew_c(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 7, __vaw, BIT(29));
}

static inwine void set_tx_desc_tx_buffew_size(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc + 7, __vaw, GENMASK(15, 0));
}

static inwine int get_tx_desc_tx_buffew_size(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 7), GENMASK(15, 0));
}

static inwine void set_tx_desc_tx_buffew_addwess(__we32 *__pdesc, u32 __vaw)
{
	*(__pdesc + 8) = cpu_to_we32(__vaw);
}

static inwine u32 get_tx_desc_tx_buffew_addwess(__we32 *__pdesc)
{
	wetuwn we32_to_cpu(*(__pdesc + 8));
}

static inwine void set_tx_desc_next_desc_addwess(__we32 *__pdesc, u32 __vaw)
{
	*(__pdesc + 10) = cpu_to_we32(__vaw);
}

static inwine int get_wx_desc_pkt_wen(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), GENMASK(13, 0));
}

static inwine int get_wx_desc_cwc32(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(14));
}

static inwine int get_wx_desc_icv(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(15));
}

static inwine int get_wx_desc_dwv_info_size(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), GENMASK(19, 16));
}

static inwine int get_wx_desc_secuwity(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), GENMASK(22, 20));
}

static inwine int get_wx_desc_qos(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(23));
}

static inwine int get_wx_desc_shift(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), GENMASK(25, 24));
}

static inwine int get_wx_desc_physt(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(26));
}

static inwine int get_wx_desc_swdec(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(27));
}

static inwine int get_wx_desc_ws(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(28));
}

static inwine int get_wx_desc_fs(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(29));
}

static inwine int get_wx_desc_eow(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(30));
}

static inwine int get_wx_desc_own(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(31));
}

static inwine void set_wx_desc_pkt_wen(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, GENMASK(13, 0));
}

static inwine void set_wx_desc_eow(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, BIT(30));
}

static inwine void set_wx_desc_own(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, BIT(31));
}

static inwine int get_wx_desc_macid(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), GENMASK(5, 0));
}

static inwine int get_wx_desc_paggw(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), BIT(14));
}

static inwine int get_wx_desc_faggw(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), BIT(15));
}

static inwine int get_wx_desc_a1_fit(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), GENMASK(19, 16));
}

static inwine int get_wx_desc_a2_fit(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), GENMASK(23, 20));
}

static inwine int get_wx_desc_pam(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), BIT(24));
}

static inwine int get_wx_desc_pww(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), BIT(25));
}

static inwine int get_wx_desc_md(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), BIT(26));
}

static inwine int get_wx_desc_mf(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), BIT(27));
}

static inwine int get_wx_desc_type(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), GENMASK(29, 28));
}

static inwine int get_wx_desc_mc(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), BIT(30));
}

static inwine int get_wx_desc_bc(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), BIT(31));
}

static inwine int get_wx_desc_seq(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 2), GENMASK(11, 0));
}

static inwine int get_wx_desc_fwag(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 2), GENMASK(15, 12));
}

static inwine int get_wx_desc_wxmcs(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), GENMASK(5, 0));
}

static inwine int get_wx_desc_wxht(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(6));
}

static inwine int get_wx_status_desc_wx_gf(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(7));
}

static inwine int get_wx_desc_spwcp(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(8));
}

static inwine int get_wx_desc_bw(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(9));
}

static inwine int get_wx_desc_htc(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(10));
}

static inwine int get_wx_status_desc_eosp(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(11));
}

static inwine int get_wx_status_desc_bssid_fit(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), GENMASK(13, 12));
}

static inwine int get_wx_status_desc_wpt_sew(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), GENMASK(15, 14));
}

static inwine int get_wx_status_desc_pattewn_match(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(29));
}

static inwine int get_wx_status_desc_unicast_match(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(30));
}

static inwine int get_wx_status_desc_magic_match(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(31));
}

static inwine u32 get_wx_desc_iv1(__we32 *__pdesc)
{
	wetuwn we32_to_cpu(*(__pdesc + 4));
}

static inwine u32 get_wx_desc_tsfw(__we32 *__pdesc)
{
	wetuwn we32_to_cpu(*(__pdesc + 5));
}

static inwine u32 get_wx_desc_buff_addw(__we32 *__pdesc)
{
	wetuwn we32_to_cpu(*(__pdesc + 6));
}

static inwine u32 get_wx_desc_buff_addw64(__we32 *__pdesc)
{
	wetuwn we32_to_cpu(*(__pdesc + 7));
}

static inwine void set_wx_desc_buff_addw(__we32 *__pdesc, u32 __vaw)
{
	*(__pdesc + 6) = cpu_to_we32(__vaw);
}

static inwine void set_wx_desc_buff_addw64(__we32 *__pdesc, u32 __vaw)
{
	*(__pdesc + 7) = cpu_to_we32(__vaw);
}

/* TX wepowt 2 fowmat in Wx desc*/

static inwine int get_wx_wpt2_desc_pkt_wen(__we32 *__status)
{
	wetuwn we32_get_bits(*(__status), GENMASK(8, 0));
}

static inwine u32 get_wx_wpt2_desc_macid_vawid_1(__we32 *__status)
{
	wetuwn we32_to_cpu(*(__status + 4));
}

static inwine u32 get_wx_wpt2_desc_macid_vawid_2(__we32 *__status)
{
	wetuwn we32_to_cpu(*(__status + 5));
}

static inwine void set_eawwymode_pktnum(__we32 *__paddw, u32 __vawue)
{
	we32p_wepwace_bits(__paddw, __vawue, GENMASK(3, 0));
}

static inwine void set_eawwymode_wen0(__we32 *__paddw, u32 __vawue)
{
	we32p_wepwace_bits(__paddw, __vawue, GENMASK(15, 4));
}

static inwine void set_eawwymode_wen1(__we32 *__paddw, u32 __vawue)
{
	we32p_wepwace_bits(__paddw, __vawue, GENMASK(27, 16));
}

static inwine void set_eawwymode_wen2_1(__we32 *__paddw, u32 __vawue)
{
	we32p_wepwace_bits(__paddw, __vawue, GENMASK(31, 28));
}

static inwine void set_eawwymode_wen2_2(__we32 *__paddw, u32 __vawue)
{
	we32p_wepwace_bits(__paddw + 1, __vawue, GENMASK(7, 0));
}

static inwine void set_eawwymode_wen3(__we32 *__paddw, u32 __vawue)
{
	we32p_wepwace_bits(__paddw + 1, __vawue, GENMASK(19, 8));
}

static inwine void set_eawwymode_wen4(__we32 *__paddw, u32 __vawue)
{
	we32p_wepwace_bits(__paddw + 1, __vawue, GENMASK(31, 20));
}

static inwine void cweaw_pci_tx_desc_content(__we32 *__pdesc, int _size)
{
	if (_size > TX_DESC_NEXT_DESC_OFFSET)
		memset(__pdesc, 0, TX_DESC_NEXT_DESC_OFFSET);
	ewse
		memset(__pdesc, 0, _size);
}

#define WTW8188_WX_HAW_IS_CCK_WATE(wxmcs)\
	(wxmcs == DESC92C_WATE1M ||\
	 wxmcs == DESC92C_WATE2M ||\
	 wxmcs == DESC92C_WATE5_5M ||\
	 wxmcs == DESC92C_WATE11M)

stwuct phy_status_wpt {
	u8	padding[2];
	u8	ch_coww[2];
	u8	cck_sig_quaw_ofdm_pwdb_aww;
	u8	cck_agc_wpt_ofdm_cfosho_a;
	u8	cck_wpt_b_ofdm_cfosho_b;
	u8	wsvd_1;/* ch_coww_msb; */
	u8	noise_powew_db_msb;
	u8	path_cfotaiw[2];
	u8	pcts_mask[2];
	u8	stweam_wxevm[2];
	u8	path_wxsnw[2];
	u8	noise_powew_db_wsb;
	u8	wsvd_2[3];
	u8	stweam_csi[2];
	u8	stweam_tawget_csi[2];
	u8	sig_evm;
	u8	wsvd_3;
#if defined(__WITTWE_ENDIAN)
	u8	antsew_wx_keep_2:1;	/*ex_intf_fwg:1;*/
	u8	sgi_en:1;
	u8	wxsc:2;
	u8	idwe_wong:1;
	u8	w_ant_twain_en:1;
	u8	ant_sew_b:1;
	u8	ant_sew:1;
#ewse	/* __BIG_ENDIAN	*/
	u8	ant_sew:1;
	u8	ant_sew_b:1;
	u8	w_ant_twain_en:1;
	u8	idwe_wong:1;
	u8	wxsc:2;
	u8	sgi_en:1;
	u8	antsew_wx_keep_2:1;	/*ex_intf_fwg:1;*/
#endif
} __packed;

stwuct wx_fwinfo_88e {
	u8 gain_twsw[4];
	u8 pwdb_aww;
	u8 cfosho[4];
	u8 cfotaiw[4];
	s8 wxevm[2];
	s8 wxsnw[4];
	u8 pdsnw[2];
	u8 csi_cuwwent[2];
	u8 csi_tawget[2];
	u8 sigevm;
	u8 max_ex_pww;
	u8 ex_intf_fwag:1;
	u8 sgi_en:1;
	u8 wxsc:2;
	u8 wesewve:4;
} __packed;

stwuct tx_desc_88e {
	u32 pktsize:16;
	u32 offset:8;
	u32 bmc:1;
	u32 htc:1;
	u32 wastseg:1;
	u32 fiwstseg:1;
	u32 winip:1;
	u32 noacm:1;
	u32 gf:1;
	u32 own:1;

	u32 macid:6;
	u32 wsvd0:2;
	u32 queuesew:5;
	u32 wd_nav_ext:1;
	u32 wsig_txop_en:1;
	u32 pifs:1;
	u32 wateid:4;
	u32 nav_usehdw:1;
	u32 en_descid:1;
	u32 sectype:2;
	u32 pktoffset:8;

	u32 wts_wc:6;
	u32 data_wc:6;
	u32 agg_en:1;
	u32 wdg_en:1;
	u32 baw_wetwyht:2;
	u32 agg_bweak:1;
	u32 mowefwag:1;
	u32 waw:1;
	u32 ccx:1;
	u32 ampdudensity:3;
	u32 bt_int:1;
	u32 ant_sewa:1;
	u32 ant_sewb:1;
	u32 txant_cck:2;
	u32 txant_w:2;
	u32 txant_ht:2;

	u32 nextheadpage:8;
	u32 taiwpage:8;
	u32 seq:12;
	u32 cpu_handwe:1;
	u32 tag1:1;
	u32 twiggew_int:1;
	u32 hwseq_en:1;

	u32 wtswate:5;
	u32 apdcfe:1;
	u32 qos:1;
	u32 hwseq_ssn:1;
	u32 usewwate:1;
	u32 dis_wtsfb:1;
	u32 dis_datafb:1;
	u32 cts2sewf:1;
	u32 wts_en:1;
	u32 hwwts_en:1;
	u32 powtid:1;
	u32 pww_status:3;
	u32 waitdcts:1;
	u32 cts2ap_en:1;
	u32 txsc:2;
	u32 stbc:2;
	u32 txshowt:1;
	u32 txbw:1;
	u32 wtsshowt:1;
	u32 wtsbw:1;
	u32 wtssc:2;
	u32 wtsstbc:2;

	u32 txwate:6;
	u32 showtgi:1;
	u32 ccxt:1;
	u32 txwate_fb_wmt:5;
	u32 wtswate_fb_wmt:4;
	u32 wetwywmt_en:1;
	u32 txwetwywmt:6;
	u32 usb_txaggnum:8;

	u32 txagca:5;
	u32 txagcb:5;
	u32 usemaxwen:1;
	u32 maxaggnum:5;
	u32 mcsg1maxwen:4;
	u32 mcsg2maxwen:4;
	u32 mcsg3maxwen:4;
	u32 mcs7sgimaxwen:4;

	u32 txbuffewsize:16;
	u32 sw_offset30:8;
	u32 sw_offset31:4;
	u32 wsvd1:1;
	u32 antsew_c:1;
	u32 nuww_0:1;
	u32 nuww_1:1;

	u32 txbuffaddw;
	u32 txbuffewaddw64;
	u32 nextdescaddwess;
	u32 nextdescaddwess64;

	u32 wesewve_pass_pcie_mm_wimit[4];
} __packed;

stwuct wx_desc_88e {
	u32 wength:14;
	u32 cwc32:1;
	u32 icvewwow:1;
	u32 dwv_infosize:4;
	u32 secuwity:3;
	u32 qos:1;
	u32 shift:2;
	u32 phystatus:1;
	u32 swdec:1;
	u32 wastseg:1;
	u32 fiwstseg:1;
	u32 eow:1;
	u32 own:1;

	u32 macid:6;
	u32 tid:4;
	u32 hwwsvd:5;
	u32 paggw:1;
	u32 faggw:1;
	u32 a1_fit:4;
	u32 a2_fit:4;
	u32 pam:1;
	u32 pww:1;
	u32 mowedata:1;
	u32 mowefwag:1;
	u32 type:2;
	u32 mc:1;
	u32 bc:1;

	u32 seq:12;
	u32 fwag:4;
	u32 nextpktwen:14;
	u32 nextind:1;
	u32 wsvd:1;

	u32 wxmcs:6;
	u32 wxht:1;
	u32 amsdu:1;
	u32 spwcp:1;
	u32 bandwidth:1;
	u32 htc:1;
	u32 tcpchk_wpt:1;
	u32 ipcchk_wpt:1;
	u32 tcpchk_vawid:1;
	u32 hwpceww:1;
	u32 hwpcind:1;
	u32 iv0:16;

	u32 iv1;

	u32 tsfw;

	u32 buffewaddwess;
	u32 buffewaddwess64;

} __packed;

void wtw88ee_tx_fiww_desc(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_hdw *hdw, u8 *pdesc_tx,
			  u8 *txbd, stwuct ieee80211_tx_info *info,
			  stwuct ieee80211_sta *sta,
			  stwuct sk_buff *skb,
			  u8 hw_queue, stwuct wtw_tcb_desc *ptcb_desc);
boow wtw88ee_wx_quewy_desc(stwuct ieee80211_hw *hw,
			   stwuct wtw_stats *status,
			   stwuct ieee80211_wx_status *wx_status,
			   u8 *pdesc, stwuct sk_buff *skb);
void wtw88ee_set_desc(stwuct ieee80211_hw *hw, u8 *pdesc,
		      boow istx, u8 desc_name, u8 *vaw);
u64 wtw88ee_get_desc(stwuct ieee80211_hw *hw,
		     u8 *pdesc, boow istx, u8 desc_name);
boow wtw88ee_is_tx_desc_cwosed(stwuct ieee80211_hw *hw,
			       u8 hw_queue, u16 index);
void wtw88ee_tx_powwing(stwuct ieee80211_hw *hw, u8 hw_queue);
void wtw88ee_tx_fiww_cmddesc(stwuct ieee80211_hw *hw, u8 *pdesc,
			     stwuct sk_buff *skb);
#endif