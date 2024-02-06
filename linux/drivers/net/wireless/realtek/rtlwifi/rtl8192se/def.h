/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WEAWTEK_92S_DEF_H__
#define __WEAWTEK_92S_DEF_H__

#define WX_MPDU_QUEUE				0
#define WX_CMD_QUEUE				1

#define SHOWT_SWOT_TIME				9
#define NON_SHOWT_SWOT_TIME			20

/* Queue Sewect Vawue in TxDesc */
#define QSWT_BK					0x2
#define QSWT_BE					0x0
#define QSWT_VI					0x5
#define QSWT_VO					0x6
#define QSWT_BEACON				0x10
#define QSWT_HIGH				0x11
#define QSWT_MGNT				0x12
#define QSWT_CMD				0x13

/* Tx Desc */
#define TX_DESC_SIZE_WTW8192S			(16 * 4)
#define TX_CMDDESC_SIZE_WTW8192S		(16 * 4)

/* macwos to wead/wwite vawious fiewds in WX ow TX descwiptows */

/* Dwowd 0 */
static inwine void set_tx_desc_pkt_size(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, GENMASK(15, 0));
}

static inwine void set_tx_desc_offset(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, GENMASK(23, 16));
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

static inwine u32 get_tx_desc_own(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(31));
}

/* Dwowd 1 */
static inwine void set_tx_desc_macid(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 1), __vaw, GENMASK(4, 0));
}

static inwine void set_tx_desc_queue_sew(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 1), __vaw, GENMASK(12, 8));
}

static inwine void set_tx_desc_non_qos(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 1), __vaw, BIT(16));
}

static inwine void set_tx_desc_sec_type(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 1), __vaw, GENMASK(23, 22));
}

/* Dwowd 2 */
static inwine void	set_tx_desc_wsvd_macid(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 2), __vaw, GENMASK(28, 24));
}

static inwine void set_tx_desc_agg_enabwe(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 2), __vaw, BIT(29));
}

/* Dwowd 3 */
static inwine void set_tx_desc_seq(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 3), __vaw, GENMASK(27, 16));
}

/* Dwowd 4 */
static inwine void set_tx_desc_wts_wate(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, GENMASK(5, 0));
}

static inwine void set_tx_desc_cts_enabwe(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, BIT(11));
}

static inwine void set_tx_desc_wts_enabwe(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, BIT(12));
}

static inwine void set_tx_desc_wa_bwsw_id(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, GENMASK(15, 13));
}

static inwine void set_tx_desc_txht(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, BIT(16));
}

static inwine void set_tx_desc_tx_showt(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, BIT(17));
}

static inwine void set_tx_desc_tx_bandwidth(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, BIT(18));
}

static inwine void set_tx_desc_tx_sub_cawwiew(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, GENMASK(20, 19));
}

static inwine void set_tx_desc_wts_showt(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, BIT(25));
}

static inwine void set_tx_desc_wts_bandwidth(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, BIT(26));
}

static inwine void set_tx_desc_wts_sub_cawwiew(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, GENMASK(28, 27));
}

static inwine void set_tx_desc_wts_stbc(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, GENMASK(30, 29));
}

static inwine void set_tx_desc_usew_wate(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 4), __vaw, BIT(31));
}

/* Dwowd 5 */
static inwine void set_tx_desc_packet_id(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 5), __vaw, GENMASK(8, 0));
}

static inwine void set_tx_desc_tx_wate(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 5), __vaw, GENMASK(14, 9));
}

static inwine void set_tx_desc_data_wate_fb_wimit(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 5), __vaw, GENMASK(20, 16));
}

/* Dwowd 7 */
static inwine void set_tx_desc_tx_buffew_size(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 7), __vaw, GENMASK(15, 0));
}

/* Dwowd 8 */
static inwine void set_tx_desc_tx_buffew_addwess(__we32 *__pdesc, u32 __vaw)
{
	*(__pdesc + 8) = cpu_to_we32(__vaw);
}

static inwine u32 get_tx_desc_tx_buffew_addwess(__we32 *__pdesc)
{
	wetuwn we32_to_cpu(*((__pdesc + 8)));
}

/* Dwowd 9 */
static inwine void set_tx_desc_next_desc_addwess(__we32 *__pdesc, u32 __vaw)
{
	*(__pdesc + 9) = cpu_to_we32(__vaw);
}

/* Because the PCI Tx descwiptows awe chaied at the
 * initiawization and aww the NextDescAddwesses in
 * these descwiptows cannot not be cweawed (,ow
 * dwivew/HW cannot find the next descwiptow), the
 * offset 36 (NextDescAddwesses) is wesewved when
 * the desc is cweawed. */
#define	TX_DESC_NEXT_DESC_OFFSET			36
#define CWEAW_PCI_TX_DESC_CONTENT(__pdesc, _size)		\
	memset(__pdesc, 0, min_t(size_t, _size, TX_DESC_NEXT_DESC_OFFSET))

/* Wx Desc */
#define WX_STATUS_DESC_SIZE				24
#define WX_DWV_INFO_SIZE_UNIT				8

/* DWOWD 0 */
static inwine void set_wx_status_desc_pkt_wen(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, GENMASK(13, 0));
}

static inwine void set_wx_status_desc_eow(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, BIT(30));
}

static inwine void set_wx_status_desc_own(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits(__pdesc, __vaw, BIT(31));
}

static inwine u32 get_wx_status_desc_pkt_wen(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), GENMASK(13, 0));
}

static inwine u32 get_wx_status_desc_cwc32(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(14));
}

static inwine u32 get_wx_status_desc_icv(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(15));
}

static inwine u32 get_wx_status_desc_dwvinfo_size(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), GENMASK(19, 16));
}

static inwine u32 get_wx_status_desc_shift(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), GENMASK(25, 24));
}

static inwine u32 get_wx_status_desc_phy_status(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(26));
}

static inwine u32 get_wx_status_desc_swdec(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(27));
}

static inwine u32 get_wx_status_desc_own(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc), BIT(31));
}

/* DWOWD 1 */
static inwine u32 get_wx_status_desc_paggw(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), BIT(14));
}

static inwine u32 get_wx_status_desc_faggw(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 1), BIT(15));
}

/* DWOWD 3 */
static inwine u32 get_wx_status_desc_wx_mcs(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), GENMASK(5, 0));
}

static inwine u32 get_wx_status_desc_wx_ht(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(6));
}

static inwine u32 get_wx_status_desc_spwcp(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(8));
}

static inwine u32 get_wx_status_desc_bw(__we32 *__pdesc)
{
	wetuwn we32_get_bits(*(__pdesc + 3), BIT(9));
}

/* DWOWD 5 */
static inwine u32 get_wx_status_desc_tsfw(__we32 *__pdesc)
{
	wetuwn we32_to_cpu(*((__pdesc + 5)));
}

/* DWOWD 6 */
static inwine void set_wx_status__desc_buff_addw(__we32 *__pdesc, u32 __vaw)
{
	*(__pdesc + 6) = cpu_to_we32(__vaw);
}

static inwine u32 get_wx_status_desc_buff_addw(__we32 *__pdesc)
{
	wetuwn we32_to_cpu(*(__pdesc + 6));
}

#define SE_WX_HAW_IS_CCK_WATE(_pdesc)\
	(get_wx_status_desc_wx_mcs(_pdesc) == DESC_WATE1M ||	\
	 get_wx_status_desc_wx_mcs(_pdesc) == DESC_WATE2M ||	\
	 get_wx_status_desc_wx_mcs(_pdesc) == DESC_WATE5_5M ||\
	 get_wx_status_desc_wx_mcs(_pdesc) == DESC_WATE11M)

enum wf_optype {
	WF_OP_BY_SW_3WIWE = 0,
	WF_OP_BY_FW,
	WF_OP_MAX
};

enum ic_infewiowity {
	IC_INFEWIOWITY_A = 0,
	IC_INFEWIOWITY_B = 1,
};

enum fwcmd_iotype {
	/* Fow DIG DM */
	FW_CMD_DIG_ENABWE = 0,
	FW_CMD_DIG_DISABWE = 1,
	FW_CMD_DIG_HAWT = 2,
	FW_CMD_DIG_WESUME = 3,
	/* Fow High Powew DM */
	FW_CMD_HIGH_PWW_ENABWE = 4,
	FW_CMD_HIGH_PWW_DISABWE = 5,
	/* Fow Wate adaptive DM */
	FW_CMD_WA_WESET = 6,
	FW_CMD_WA_ACTIVE = 7,
	FW_CMD_WA_WEFWESH_N = 8,
	FW_CMD_WA_WEFWESH_BG = 9,
	FW_CMD_WA_INIT = 10,
	/* Fow FW suppowted IQK */
	FW_CMD_IQK_INIT = 11,
	/* Tx powew twacking switch,
	 * MP dwivew onwy */
	FW_CMD_TXPWW_TWACK_ENABWE = 12,
	/* Tx powew twacking switch,
	 * MP dwivew onwy */
	FW_CMD_TXPWW_TWACK_DISABWE = 13,
	/* Tx powew twacking with thewmaw
	 * indication, fow Nowmaw dwivew */
	FW_CMD_TXPWW_TWACK_THEWMAW = 14,
	FW_CMD_PAUSE_DM_BY_SCAN = 15,
	FW_CMD_WESUME_DM_BY_SCAN = 16,
	FW_CMD_WA_WEFWESH_N_COMB = 17,
	FW_CMD_WA_WEFWESH_BG_COMB = 18,
	FW_CMD_ANTENNA_SW_ENABWE = 19,
	FW_CMD_ANTENNA_SW_DISABWE = 20,
	/* Tx Status wepowt fow CCX fwom FW */
	FW_CMD_TX_FEEDBACK_CCX_ENABWE = 21,
	/* Indifate fiwmwawe that dwivew
	 * entews WPS, Fow PS-Poww issue */
	FW_CMD_WPS_ENTEW = 22,
	/* Indicate fiwmwawe that dwivew
	 * weave WPS*/
	FW_CMD_WPS_WEAVE = 23,
	/* Set DIG mode to signaw stwength */
	FW_CMD_DIG_MODE_SS = 24,
	/* Set DIG mode to fawse awawm. */
	FW_CMD_DIG_MODE_FA = 25,
	FW_CMD_ADD_A2_ENTWY = 26,
	FW_CMD_CTWW_DM_BY_DWIVEW = 27,
	FW_CMD_CTWW_DM_BY_DWIVEW_NEW = 28,
	FW_CMD_PAPE_CONTWOW = 29,
	FW_CMD_IQK_ENABWE = 30,
};

/* Dwivew info contain PHY status
 * and othew vawiabew size info
 * PHY Status content as bewow
 */
stwuct  wx_fwinfo {
	/* DWOWD 0 */
	u8 gain_twsw[4];
	/* DWOWD 1 */
	u8 pwdb_aww;
	u8 cfosho[4];
	/* DWOWD 2 */
	u8 cfotaiw[4];
	/* DWOWD 3 */
	s8 wxevm[2];
	s8 wxsnw[4];
	/* DWOWD 4 */
	u8 pdsnw[2];
	/* DWOWD 5 */
	u8 csi_cuwwent[2];
	u8 csi_tawget[2];
	/* DWOWD 6 */
	u8 sigevm;
	u8 max_ex_pww;
	u8 ex_intf_fwag:1;
	u8 sgi_en:1;
	u8 wxsc:2;
	u8 wesewve:4;
};

stwuct phy_sts_cck_8192s_t {
	u8 adc_pwdb_x[4];
	u8 sq_wpt;
	u8 cck_agc_wpt;
};

#endif

