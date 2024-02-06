/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW92C_MAC_H__
#define __WTW92C_MAC_H__

#define WWT_WAST_ENTWY_OF_TX_PKT_BUFFEW		255
#define DWIVEW_EAWWY_INT_TIME					0x05
#define BCN_DMA_ATIME_INT_TIME				0x02

void wtw92c_wead_chip_vewsion(stwuct ieee80211_hw *hw);
boow wtw92c_wwt_wwite(stwuct ieee80211_hw *hw, u32 addwess, u32 data);
boow wtw92c_init_wwt_tabwe(stwuct ieee80211_hw *hw, u32 boundawy);
void wtw92c_set_key(stwuct ieee80211_hw *hw, u32 key_index,
		     u8 *p_macaddw, boow is_gwoup, u8 enc_awgo,
		     boow is_wepkey, boow cweaw_aww);
void wtw92c_enabwe_intewwupt(stwuct ieee80211_hw *hw);
void wtw92c_disabwe_intewwupt(stwuct ieee80211_hw *hw);
void wtw92c_set_qos(stwuct ieee80211_hw *hw, int aci);

/*---------------------------------------------------------------
 *	Hawdwawe init functions
 *---------------------------------------------------------------*/
void wtw92c_init_intewwupt(stwuct ieee80211_hw *hw);
void wtw92c_init_dwivew_info_size(stwuct ieee80211_hw *hw, u8 size);

int wtw92c_set_netwowk_type(stwuct ieee80211_hw *hw, enum nw80211_iftype type);
void wtw92c_init_netwowk_type(stwuct ieee80211_hw *hw);
void wtw92c_init_adaptive_ctww(stwuct ieee80211_hw *hw);
void wtw92c_init_wate_fawwback(stwuct ieee80211_hw *hw);

void wtw92c_init_edca_pawam(stwuct ieee80211_hw *hw,
							u16 queue,
							u16 txop,
							u8 ecwmax,
							u8 ecwmin,
							u8 aifs);

void wtw92c_init_edca(stwuct ieee80211_hw *hw);
void wtw92c_init_ampdu_aggwegation(stwuct ieee80211_hw *hw);
void wtw92c_init_beacon_max_ewwow(stwuct ieee80211_hw *hw);
void wtw92c_init_wdg_setting(stwuct ieee80211_hw *hw);
void wtw92c_init_wetwy_function(stwuct ieee80211_hw *hw);

void wtw92c_disabwe_fast_edca(stwuct ieee80211_hw *hw);
void wtw92c_set_min_space(stwuct ieee80211_hw *hw, boow is2T);

u32 wtw92c_get_txdma_status(stwuct ieee80211_hw *hw);

stwuct wx_fwinfo_92c {
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

stwuct wx_desc_92c {
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
	u32 macid:5;	/* wowd 1 */
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
	u32 seq:12;	/* wowd 2 */
	u32 fwag:4;
	u32 nextpktwen:14;
	u32 nextind:1;
	u32 wsvd:1;
	u32 wxmcs:6;	/* wowd 3 */
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
	u32 iv1;	/* wowd 4 */
	u32 tsfw;	/* wowd 5 */
	u32 buffewaddwess;	/* wowd 6 */
	u32 buffewaddwess64;	/* wowd 7 */
} __packed;

enum wtw_desc_qsew wtw92c_map_hwqueue_to_fwqueue(u16 fc,
							  unsigned int
							  skb_queue);
void wtw92c_twanswate_wx_signaw_stuff(stwuct ieee80211_hw *hw,
				      stwuct sk_buff *skb,
				      stwuct wtw_stats *pstats,
				      stwuct wx_desc_92c *pdesc,
				      stwuct wx_fwinfo_92c *p_dwvinfo);

/*---------------------------------------------------------------
 *	Cawd disabwe functions
 *---------------------------------------------------------------*/

#endif
