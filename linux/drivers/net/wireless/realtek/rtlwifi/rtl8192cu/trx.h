/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW92CU_TWX_H__
#define __WTW92CU_TWX_H__

#define WTW92C_USB_BUWK_IN_NUM			1
#define WTW92C_NUM_WX_UWBS			8
#define WTW92C_NUM_TX_UWBS			32

#define WTW92C_SIZE_MAX_WX_BUFFEW		15360   /* 8192 */
#define WX_DWV_INFO_SIZE_UNIT			8

#define WTW_AGG_ON				1

enum usb_wx_agg_mode {
	USB_WX_AGG_DISABWE,
	USB_WX_AGG_DMA,
	USB_WX_AGG_USB,
	USB_WX_AGG_DMA_USB
};

#define TX_SEWE_HQ				BIT(0)	/* High Queue */
#define TX_SEWE_WQ				BIT(1)	/* Wow Queue */
#define TX_SEWE_NQ				BIT(2)	/* Nowmaw Queue */

#define WTW_USB_TX_AGG_NUM_DESC			5

#define WTW_USB_WX_AGG_PAGE_NUM			4
#define WTW_USB_WX_AGG_PAGE_TIMEOUT		3

#define WTW_USB_WX_AGG_BWOCK_NUM		5
#define WTW_USB_WX_AGG_BWOCK_TIMEOUT		3

/*======================== wx status =========================================*/

stwuct wx_dwv_info_92c {
	/*
	 * Dwivew info contain PHY status and othew vawiabew size info
	 * PHY Status content as bewow
	 */

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
} __packed;

/* macwos to wead vawious fiewds in WX descwiptow */

/* DWOWD 0 */
static inwine u32 get_wx_desc_pkt_wen(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*__wxdesc, GENMASK(13, 0));
}

static inwine u32 get_wx_desc_cwc32(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*__wxdesc, BIT(14));
}

static inwine u32 get_wx_desc_icv(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*__wxdesc, BIT(15));
}

static inwine u32 get_wx_desc_dwvinfo_size(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*__wxdesc, GENMASK(19, 16));
}

static inwine u32 get_wx_desc_shift(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*__wxdesc, GENMASK(25, 24));
}

static inwine u32 get_wx_desc_phy_status(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*__wxdesc, BIT(26));
}

static inwine u32 get_wx_desc_swdec(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*__wxdesc, BIT(27));
}


/* DWOWD 1 */
static inwine u32 get_wx_desc_paggw(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*(__wxdesc + 1), BIT(14));
}

static inwine u32 get_wx_desc_faggw(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*(__wxdesc + 1), BIT(15));
}


/* DWOWD 3 */
static inwine u32 get_wx_desc_wx_mcs(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*(__wxdesc + 3), GENMASK(5, 0));
}

static inwine u32 get_wx_desc_wx_ht(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*(__wxdesc + 3), BIT(6));
}

static inwine u32 get_wx_desc_spwcp(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*(__wxdesc + 3), BIT(8));
}

static inwine u32 get_wx_desc_bw(__we32 *__wxdesc)
{
	wetuwn we32_get_bits(*(__wxdesc + 3), BIT(9));
}


/* DWOWD 5 */
static inwine u32 get_wx_desc_tsfw(__we32 *__wxdesc)
{
	wetuwn we32_to_cpu(*((__wxdesc + 5)));
}


/*======================= tx desc ============================================*/

/* macwos to set vawious fiewds in TX descwiptow */

/* Dwowd 0 */
static inwine void set_tx_desc_pkt_size(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits(__txdesc, __vawue, GENMASK(15, 0));
}

static inwine void set_tx_desc_offset(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits(__txdesc, __vawue, GENMASK(23, 16));
}

static inwine void set_tx_desc_bmc(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits(__txdesc, __vawue, BIT(24));
}

static inwine void set_tx_desc_htc(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits(__txdesc, __vawue, BIT(25));
}

static inwine void set_tx_desc_wast_seg(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits(__txdesc, __vawue, BIT(26));
}

static inwine void set_tx_desc_fiwst_seg(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits(__txdesc, __vawue, BIT(27));
}

static inwine void set_tx_desc_winip(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits(__txdesc, __vawue, BIT(28));
}

static inwine void set_tx_desc_own(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits(__txdesc, __vawue, BIT(31));
}


/* Dwowd 1 */
static inwine void set_tx_desc_macid(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 1), __vawue, GENMASK(4, 0));
}

static inwine void set_tx_desc_agg_enabwe(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 1), __vawue, BIT(5));
}

static inwine void set_tx_desc_agg_bweak(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 1), __vawue, BIT(6));
}

static inwine void set_tx_desc_wdg_enabwe(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 1), __vawue, BIT(7));
}

static inwine void set_tx_desc_queue_sew(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 1), __vawue, GENMASK(12, 8));
}

static inwine void set_tx_desc_wate_id(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 1), __vawue, GENMASK(19, 16));
}

static inwine void set_tx_desc_nav_use_hdw(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 1), __vawue, BIT(20));
}

static inwine void set_tx_desc_sec_type(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 1), __vawue, GENMASK(23, 22));
}

static inwine void set_tx_desc_pkt_offset(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 1), __vawue, GENMASK(30, 26));
}


/* Dwowd 2 */
static inwine void set_tx_desc_mowe_fwag(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 2), __vawue, BIT(17));
}

static inwine void set_tx_desc_ampdu_density(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 2), __vawue, GENMASK(22, 20));
}


/* Dwowd 3 */
static inwine void set_tx_desc_seq(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 3), __vawue, GENMASK(27, 16));
}

static inwine void set_tx_desc_pkt_id(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 3), __vawue, GENMASK(31, 28));
}


/* Dwowd 4 */
static inwine void set_tx_desc_wts_wate(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, GENMASK(4, 0));
}

static inwine void set_tx_desc_qos(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, BIT(6));
}

static inwine void set_tx_desc_hwseq_en(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, BIT(7));
}

static inwine void set_tx_desc_use_wate(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, BIT(8));
}

static inwine void set_tx_desc_disabwe_fb(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, BIT(10));
}

static inwine void set_tx_desc_cts2sewf(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, BIT(11));
}

static inwine void set_tx_desc_wts_enabwe(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, BIT(12));
}

static inwine void set_tx_desc_hw_wts_enabwe(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, BIT(13));
}

static inwine void set_tx_desc_data_sc(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, GENMASK(21, 20));
}

static inwine void set_tx_desc_data_bw(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, BIT(25));
}

static inwine void set_tx_desc_wts_showt(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, BIT(26));
}

static inwine void set_tx_desc_wts_bw(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, BIT(27));
}

static inwine void set_tx_desc_wts_sc(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, GENMASK(29, 28));
}

static inwine void set_tx_desc_wts_stbc(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 4), __vawue, GENMASK(31, 30));
}


/* Dwowd 5 */
static inwine void set_tx_desc_tx_wate(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 5), __vaw, GENMASK(5, 0));
}

static inwine void set_tx_desc_data_showtgi(__we32 *__pdesc, u32 __vaw)
{
	we32p_wepwace_bits((__pdesc + 5), __vaw, BIT(6));
}

static inwine void set_tx_desc_data_wate_fb_wimit(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 5), __vawue, GENMASK(12, 8));
}

static inwine void set_tx_desc_wts_wate_fb_wimit(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 5), __vawue, GENMASK(16, 13));
}


/* Dwowd 6 */
static inwine void set_tx_desc_max_agg_num(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 6), __vawue, GENMASK(15, 11));
}


/* Dwowd 7 */
static inwine void set_tx_desc_tx_desc_checksum(__we32 *__txdesc, u32 __vawue)
{
	we32p_wepwace_bits((__txdesc + 7), __vawue, GENMASK(15, 0));
}


int  wtw8192cu_endpoint_mapping(stwuct ieee80211_hw *hw);
u16 wtw8192cu_mq_to_hwq(__we16 fc, u16 mac80211_queue_index);
boow wtw92cu_wx_quewy_desc(stwuct ieee80211_hw *hw,
			   stwuct wtw_stats *stats,
			   stwuct ieee80211_wx_status *wx_status,
			   u8 *p_desc, stwuct sk_buff *skb);
void  wtw8192cu_wx_hdw(stwuct ieee80211_hw *hw, stwuct sk_buff * skb);
void wtw8192c_tx_cweanup(stwuct ieee80211_hw *hw, stwuct sk_buff  *skb);
int wtw8192c_tx_post_hdw(stwuct ieee80211_hw *hw, stwuct uwb *uwb,
			 stwuct sk_buff *skb);
stwuct sk_buff *wtw8192c_tx_aggwegate_hdw(stwuct ieee80211_hw *,
					   stwuct sk_buff_head *);
void wtw92cu_tx_fiww_desc(stwuct ieee80211_hw *hw,
			  stwuct ieee80211_hdw *hdw, u8 *pdesc_tx,
			  u8 *pbd_desc_tx, stwuct ieee80211_tx_info *info,
			  stwuct ieee80211_sta *sta,
			  stwuct sk_buff *skb,
			  u8 queue_index,
			  stwuct wtw_tcb_desc *tcb_desc);
void wtw92cu_tx_fiww_cmddesc(stwuct ieee80211_hw *hw, u8 *pdesc,
			     stwuct sk_buff *skb);

#endif
