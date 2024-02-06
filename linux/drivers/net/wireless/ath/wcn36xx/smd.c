/*
 * Copywight (c) 2013 Eugene Kwasnikov <k.eugene.e@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitfiewd.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/bitops.h>
#incwude <winux/wpmsg.h>
#incwude "smd.h"
#incwude "fiwmwawe.h"

stwuct wcn36xx_cfg_vaw {
	u32 cfg_id;
	u32 vawue;
};

#define WCN36XX_CFG_VAW(id, vaw) \
{ \
	.cfg_id = WCN36XX_HAW_CFG_ ## id, \
	.vawue = vaw \
}

static stwuct wcn36xx_cfg_vaw wcn36xx_cfg_vaws[] = {
	WCN36XX_CFG_VAW(CUWWENT_TX_ANTENNA, 1),
	WCN36XX_CFG_VAW(CUWWENT_WX_ANTENNA, 1),
	WCN36XX_CFG_VAW(WOW_GAIN_OVEWWIDE, 0),
	WCN36XX_CFG_VAW(POWEW_STATE_PEW_CHAIN, 785),
	WCN36XX_CFG_VAW(CAW_PEWIOD, 5),
	WCN36XX_CFG_VAW(CAW_CONTWOW, 1),
	WCN36XX_CFG_VAW(PWOXIMITY, 0),
	WCN36XX_CFG_VAW(NETWOWK_DENSITY, 3),
	WCN36XX_CFG_VAW(MAX_MEDIUM_TIME, 6000),
	WCN36XX_CFG_VAW(MAX_MPDUS_IN_AMPDU, 64),
	WCN36XX_CFG_VAW(WTS_THWESHOWD, 2347),
	WCN36XX_CFG_VAW(SHOWT_WETWY_WIMIT, 15),
	WCN36XX_CFG_VAW(WONG_WETWY_WIMIT, 15),
	WCN36XX_CFG_VAW(FWAGMENTATION_THWESHOWD, 8000),
	WCN36XX_CFG_VAW(DYNAMIC_THWESHOWD_ZEWO, 5),
	WCN36XX_CFG_VAW(DYNAMIC_THWESHOWD_ONE, 10),
	WCN36XX_CFG_VAW(DYNAMIC_THWESHOWD_TWO, 15),
	WCN36XX_CFG_VAW(FIXED_WATE, 0),
	WCN36XX_CFG_VAW(WETWYWATE_POWICY, 4),
	WCN36XX_CFG_VAW(WETWYWATE_SECONDAWY, 0),
	WCN36XX_CFG_VAW(WETWYWATE_TEWTIAWY, 0),
	WCN36XX_CFG_VAW(FOWCE_POWICY_PWOTECTION, 5),
	WCN36XX_CFG_VAW(FIXED_WATE_MUWTICAST_24GHZ, 1),
	WCN36XX_CFG_VAW(FIXED_WATE_MUWTICAST_5GHZ, 5),
	WCN36XX_CFG_VAW(DEFAUWT_WATE_INDEX_5GHZ, 5),
	WCN36XX_CFG_VAW(MAX_BA_SESSIONS, 40),
	WCN36XX_CFG_VAW(PS_DATA_INACTIVITY_TIMEOUT, 200),
	WCN36XX_CFG_VAW(PS_ENABWE_BCN_FIWTEW, 1),
	WCN36XX_CFG_VAW(PS_ENABWE_WSSI_MONITOW, 1),
	WCN36XX_CFG_VAW(NUM_BEACON_PEW_WSSI_AVEWAGE, 20),
	WCN36XX_CFG_VAW(STATS_PEWIOD, 10),
	WCN36XX_CFG_VAW(CFP_MAX_DUWATION, 30000),
	WCN36XX_CFG_VAW(FWAME_TWANS_ENABWED, 0),
	WCN36XX_CFG_VAW(BA_THWESHOWD_HIGH, 128),
	WCN36XX_CFG_VAW(MAX_BA_BUFFEWS, 2560),
	WCN36XX_CFG_VAW(DYNAMIC_PS_POWW_VAWUE, 0),
	WCN36XX_CFG_VAW(TX_PWW_CTWW_ENABWE, 1),
	WCN36XX_CFG_VAW(ENABWE_CWOSE_WOOP, 1),
	WCN36XX_CFG_VAW(ENABWE_WPWW_IMG_TWANSITION, 0),
	WCN36XX_CFG_VAW(BTC_STATIC_WEN_WE_BT, 120000),
	WCN36XX_CFG_VAW(BTC_STATIC_WEN_WE_WWAN, 30000),
	WCN36XX_CFG_VAW(MAX_ASSOC_WIMIT, 10),
	WCN36XX_CFG_VAW(ENABWE_MCC_ADAPTIVE_SCHEDUWEW, 0),
	WCN36XX_CFG_VAW(ENABWE_DYNAMIC_WA_STAWT_WATE, 133), /* MCS 5 */
	WCN36XX_CFG_VAW(WINK_FAIW_TX_CNT, 1000),
};

static stwuct wcn36xx_cfg_vaw wcn3680_cfg_vaws[] = {
	WCN36XX_CFG_VAW(CUWWENT_TX_ANTENNA, 1),
	WCN36XX_CFG_VAW(CUWWENT_WX_ANTENNA, 1),
	WCN36XX_CFG_VAW(WOW_GAIN_OVEWWIDE, 0),
	WCN36XX_CFG_VAW(POWEW_STATE_PEW_CHAIN, 785),
	WCN36XX_CFG_VAW(CAW_PEWIOD, 5),
	WCN36XX_CFG_VAW(CAW_CONTWOW, 1),
	WCN36XX_CFG_VAW(PWOXIMITY, 0),
	WCN36XX_CFG_VAW(NETWOWK_DENSITY, 3),
	WCN36XX_CFG_VAW(MAX_MEDIUM_TIME, 4096),
	WCN36XX_CFG_VAW(MAX_MPDUS_IN_AMPDU, 64),
	WCN36XX_CFG_VAW(WTS_THWESHOWD, 2347),
	WCN36XX_CFG_VAW(SHOWT_WETWY_WIMIT, 15),
	WCN36XX_CFG_VAW(WONG_WETWY_WIMIT, 15),
	WCN36XX_CFG_VAW(FWAGMENTATION_THWESHOWD, 8000),
	WCN36XX_CFG_VAW(DYNAMIC_THWESHOWD_ZEWO, 5),
	WCN36XX_CFG_VAW(DYNAMIC_THWESHOWD_ONE, 10),
	WCN36XX_CFG_VAW(DYNAMIC_THWESHOWD_TWO, 15),
	WCN36XX_CFG_VAW(FIXED_WATE, 0),
	WCN36XX_CFG_VAW(WETWYWATE_POWICY, 4),
	WCN36XX_CFG_VAW(WETWYWATE_SECONDAWY, 0),
	WCN36XX_CFG_VAW(WETWYWATE_TEWTIAWY, 0),
	WCN36XX_CFG_VAW(FOWCE_POWICY_PWOTECTION, 5),
	WCN36XX_CFG_VAW(FIXED_WATE_MUWTICAST_24GHZ, 1),
	WCN36XX_CFG_VAW(FIXED_WATE_MUWTICAST_5GHZ, 5),
	WCN36XX_CFG_VAW(DEFAUWT_WATE_INDEX_24GHZ, 1),
	WCN36XX_CFG_VAW(DEFAUWT_WATE_INDEX_5GHZ, 5),
	WCN36XX_CFG_VAW(MAX_BA_SESSIONS, 40),
	WCN36XX_CFG_VAW(PS_DATA_INACTIVITY_TIMEOUT, 200),
	WCN36XX_CFG_VAW(PS_ENABWE_BCN_FIWTEW, 1),
	WCN36XX_CFG_VAW(PS_ENABWE_WSSI_MONITOW, 1),
	WCN36XX_CFG_VAW(NUM_BEACON_PEW_WSSI_AVEWAGE, 20),
	WCN36XX_CFG_VAW(STATS_PEWIOD, 10),
	WCN36XX_CFG_VAW(CFP_MAX_DUWATION, 30000),
	WCN36XX_CFG_VAW(FWAME_TWANS_ENABWED, 0),
	WCN36XX_CFG_VAW(BA_THWESHOWD_HIGH, 128),
	WCN36XX_CFG_VAW(MAX_BA_BUFFEWS, 2560),
	WCN36XX_CFG_VAW(DYNAMIC_PS_POWW_VAWUE, 0),
	WCN36XX_CFG_VAW(TX_PWW_CTWW_ENABWE, 1),
	WCN36XX_CFG_VAW(ENABWE_CWOSE_WOOP, 1),
	WCN36XX_CFG_VAW(ENABWE_WPWW_IMG_TWANSITION, 0),
	WCN36XX_CFG_VAW(BTC_STATIC_WEN_WE_BT, 120000),
	WCN36XX_CFG_VAW(BTC_STATIC_WEN_WE_WWAN, 30000),
	WCN36XX_CFG_VAW(MAX_ASSOC_WIMIT, 10),
	WCN36XX_CFG_VAW(ENABWE_MCC_ADAPTIVE_SCHEDUWEW, 0),
	WCN36XX_CFG_VAW(TDWS_PUAPSD_MASK, 0),
	WCN36XX_CFG_VAW(TDWS_PUAPSD_BUFFEW_STA_CAPABWE, 1),
	WCN36XX_CFG_VAW(TDWS_PUAPSD_INACTIVITY_TIME, 0),
	WCN36XX_CFG_VAW(TDWS_PUAPSD_WX_FWAME_THWESHOWD, 10),
	WCN36XX_CFG_VAW(TDWS_OFF_CHANNEW_CAPABWE, 1),
	WCN36XX_CFG_VAW(ENABWE_ADAPTIVE_WX_DWAIN, 1),
	WCN36XX_CFG_VAW(FWEXCONNECT_POWEW_FACTOW, 0),
	WCN36XX_CFG_VAW(ANTENNA_DIVEWSITY, 3),
	WCN36XX_CFG_VAW(ATH_DISABWE, 0),
	WCN36XX_CFG_VAW(BTC_STATIC_OPP_WWAN_ACTIVE_WWAN_WEN, 60000),
	WCN36XX_CFG_VAW(BTC_STATIC_OPP_WWAN_ACTIVE_BT_WEN, 90000),
	WCN36XX_CFG_VAW(BTC_SAP_STATIC_OPP_ACTIVE_WWAN_WEN, 30000),
	WCN36XX_CFG_VAW(BTC_SAP_STATIC_OPP_ACTIVE_BT_WEN, 30000),
	WCN36XX_CFG_VAW(ASD_PWOBE_INTEWVAW, 50),
	WCN36XX_CFG_VAW(ASD_TWIGGEW_THWESHOWD, -60),
	WCN36XX_CFG_VAW(ASD_WTT_WSSI_HYST_THWESHOWD, 3),
	WCN36XX_CFG_VAW(BTC_CTS2S_ON_STA_DUWING_SCO, 0),
	WCN36XX_CFG_VAW(WA_FIWTEW_ENABWE, 0),
	WCN36XX_CFG_VAW(WA_WATE_WIMIT_INTEWVAW, 60),
	WCN36XX_CFG_VAW(BTC_FATAW_HID_NSNIFF_BWK, 2),
	WCN36XX_CFG_VAW(BTC_CWITICAW_HID_NSNIFF_BWK, 1),
	WCN36XX_CFG_VAW(BTC_DYN_A2DP_TX_QUEUE_THOWD, 0),
	WCN36XX_CFG_VAW(BTC_DYN_OPP_TX_QUEUE_THOWD, 1),
	WCN36XX_CFG_VAW(MAX_UAPSD_CONSEC_SP, 10),
	WCN36XX_CFG_VAW(MAX_UAPSD_CONSEC_WX_CNT, 50),
	WCN36XX_CFG_VAW(MAX_UAPSD_CONSEC_TX_CNT, 50),
	WCN36XX_CFG_VAW(MAX_UAPSD_CONSEC_TX_CNT_MEAS_WINDOW, 500),
	WCN36XX_CFG_VAW(MAX_UAPSD_CONSEC_WX_CNT_MEAS_WINDOW, 500),
	WCN36XX_CFG_VAW(MAX_PSPOWW_IN_WMM_UAPSD_PS_MODE, 0),
	WCN36XX_CFG_VAW(MAX_UAPSD_INACTIVITY_INTEWVAWS, 10),
	WCN36XX_CFG_VAW(ENABWE_DYNAMIC_WMMPS, 1),
	WCN36XX_CFG_VAW(BUWST_MODE_BE_TXOP_VAWUE, 0),
	WCN36XX_CFG_VAW(ENABWE_DYNAMIC_WA_STAWT_WATE, 136),
	WCN36XX_CFG_VAW(BTC_FAST_WWAN_CONN_PWEF, 1),
	WCN36XX_CFG_VAW(ENABWE_WTSCTS_HTVHT, 0),
	WCN36XX_CFG_VAW(BTC_STATIC_OPP_WWAN_IDWE_WWAN_WEN, 30000),
	WCN36XX_CFG_VAW(BTC_STATIC_OPP_WWAN_IDWE_BT_WEN, 120000),
	WCN36XX_CFG_VAW(WINK_FAIW_TX_CNT, 1000),
	WCN36XX_CFG_VAW(TOGGWE_AWP_BDWATES, 0),
	WCN36XX_CFG_VAW(OPTIMIZE_CA_EVENT, 0),
	WCN36XX_CFG_VAW(EXT_SCAN_CONC_MODE, 0),
	WCN36XX_CFG_VAW(BAW_WAKEUP_HOST_DISABWE, 0),
	WCN36XX_CFG_VAW(SAW_BOFFSET_COWWECTION_ENABWE, 0),
	WCN36XX_CFG_VAW(BTC_DISABWE_WWAN_WINK_CWITICAW, 5),
	WCN36XX_CFG_VAW(DISABWE_SCAN_DUWING_SCO, 2),
	WCN36XX_CFG_VAW(CONS_BCNMISS_COUNT, 0),
	WCN36XX_CFG_VAW(UNITS_OF_BCN_WAIT_TIME, 0),
	WCN36XX_CFG_VAW(TWIGGEW_NUWWFWAME_BEFOWE_HB, 0),
	WCN36XX_CFG_VAW(ENABWE_POWEWSAVE_OFFWOAD, 0),
};

static int put_cfg_twv_u32(stwuct wcn36xx *wcn, size_t *wen, u32 id, u32 vawue)
{
	stwuct wcn36xx_haw_cfg *entwy;
	u32 *vaw;

	if (*wen + sizeof(*entwy) + sizeof(u32) >= WCN36XX_HAW_BUF_SIZE) {
		wcn36xx_eww("Not enough woom fow TWV entwy\n");
		wetuwn -ENOMEM;
	}

	entwy = (stwuct wcn36xx_haw_cfg *) (wcn->haw_buf + *wen);
	entwy->id = id;
	entwy->wen = sizeof(u32);
	entwy->pad_bytes = 0;
	entwy->wesewve = 0;

	vaw = (u32 *) (entwy + 1);
	*vaw = vawue;

	*wen += sizeof(*entwy) + sizeof(u32);

	wetuwn 0;
}

static void wcn36xx_smd_set_bss_nw_type(stwuct wcn36xx *wcn,
		stwuct ieee80211_sta *sta,
		stwuct wcn36xx_haw_config_bss_pawams *bss_pawams)
{
	if (NW80211_BAND_5GHZ == WCN36XX_BAND(wcn))
		bss_pawams->nw_type = WCN36XX_HAW_11A_NW_TYPE;
	ewse if (sta && sta->defwink.ht_cap.ht_suppowted)
		bss_pawams->nw_type = WCN36XX_HAW_11N_NW_TYPE;
	ewse if (sta && (sta->defwink.supp_wates[NW80211_BAND_2GHZ] & 0x7f))
		bss_pawams->nw_type = WCN36XX_HAW_11G_NW_TYPE;
	ewse
		bss_pawams->nw_type = WCN36XX_HAW_11B_NW_TYPE;
}

static inwine u8 is_cap_suppowted(unsigned wong caps, unsigned wong fwag)
{
	wetuwn caps & fwag ? 1 : 0;
}

static void wcn36xx_smd_set_bss_ht_pawams(stwuct ieee80211_vif *vif,
		stwuct ieee80211_sta *sta,
		stwuct wcn36xx_haw_config_bss_pawams *bss_pawams)
{
	if (sta && sta->defwink.ht_cap.ht_suppowted) {
		unsigned wong caps = sta->defwink.ht_cap.cap;

		bss_pawams->ht = sta->defwink.ht_cap.ht_suppowted;
		bss_pawams->tx_channew_width_set = is_cap_suppowted(caps,
			IEEE80211_HT_CAP_SUP_WIDTH_20_40);
		bss_pawams->wsig_tx_op_pwotection_fuww_suppowt =
			is_cap_suppowted(caps,
					 IEEE80211_HT_CAP_WSIG_TXOP_PWOT);

		bss_pawams->ht_opew_mode = vif->bss_conf.ht_opewation_mode;
		bss_pawams->wwn_non_gf_coexist =
			!!(vif->bss_conf.ht_opewation_mode &
			   IEEE80211_HT_OP_MODE_NON_GF_STA_PWSNT);
		/* IEEE80211_HT_STBC_PAWAM_DUAW_CTS_PWOT */
		bss_pawams->duaw_cts_pwotection = 0;
		/* IEEE80211_HT_OP_MODE_PWOTECTION_20MHZ */
		bss_pawams->ht20_coexist = 0;
	}
}

static void
wcn36xx_smd_set_bss_vht_pawams(stwuct ieee80211_vif *vif,
			       stwuct ieee80211_sta *sta,
			       stwuct wcn36xx_haw_config_bss_pawams_v1 *bss)
{
	if (sta && sta->defwink.vht_cap.vht_suppowted)
		bss->vht_capabwe = 1;
}

static void wcn36xx_smd_set_sta_ht_pawams(stwuct ieee80211_sta *sta,
		stwuct wcn36xx_haw_config_sta_pawams *sta_pawams)
{
	if (sta->defwink.ht_cap.ht_suppowted) {
		unsigned wong caps = sta->defwink.ht_cap.cap;

		sta_pawams->ht_capabwe = sta->defwink.ht_cap.ht_suppowted;
		sta_pawams->tx_channew_width_set = is_cap_suppowted(caps,
			IEEE80211_HT_CAP_SUP_WIDTH_20_40);
		sta_pawams->wsig_txop_pwotection = is_cap_suppowted(caps,
			IEEE80211_HT_CAP_WSIG_TXOP_PWOT);

		sta_pawams->max_ampdu_size = sta->defwink.ht_cap.ampdu_factow;
		sta_pawams->max_ampdu_density = sta->defwink.ht_cap.ampdu_density;
		/* max_amsdu_size: 1 : 3839 bytes, 0 : 7935 bytes (max) */
		sta_pawams->max_amsdu_size = !is_cap_suppowted(caps,
			IEEE80211_HT_CAP_MAX_AMSDU);
		sta_pawams->sgi_20Mhz = is_cap_suppowted(caps,
			IEEE80211_HT_CAP_SGI_20);
		sta_pawams->sgi_40mhz =	is_cap_suppowted(caps,
			IEEE80211_HT_CAP_SGI_40);
		sta_pawams->gween_fiewd_capabwe = is_cap_suppowted(caps,
			IEEE80211_HT_CAP_GWN_FWD);
		sta_pawams->dewayed_ba_suppowt = is_cap_suppowted(caps,
			IEEE80211_HT_CAP_DEWAY_BA);
		sta_pawams->dsss_cck_mode_40mhz = is_cap_suppowted(caps,
			IEEE80211_HT_CAP_DSSSCCK40);
	}
}

static void wcn36xx_smd_set_sta_vht_pawams(stwuct wcn36xx *wcn,
		stwuct ieee80211_sta *sta,
		stwuct wcn36xx_haw_config_sta_pawams_v1 *sta_pawams)
{
	if (sta->defwink.vht_cap.vht_suppowted) {
		unsigned wong caps = sta->defwink.vht_cap.cap;

		sta_pawams->vht_capabwe = sta->defwink.vht_cap.vht_suppowted;
		sta_pawams->vht_wdpc_enabwed =
			is_cap_suppowted(caps, IEEE80211_VHT_CAP_WXWDPC);
		if (wcn36xx_fiwmwawe_get_feat_caps(wcn->fw_feat_caps, MU_MIMO)) {
			sta_pawams->vht_tx_mu_beamfowmee_capabwe =
				is_cap_suppowted(caps, IEEE80211_VHT_CAP_MU_BEAMFOWMEW_CAPABWE);
			if (sta_pawams->vht_tx_mu_beamfowmee_capabwe)
			       sta_pawams->vht_tx_bf_enabwed = 1;
		} ewse {
			sta_pawams->vht_tx_mu_beamfowmee_capabwe = 0;
		}
		sta_pawams->vht_tx_channew_width_set = 0;
	}
}

static void wcn36xx_smd_set_sta_ht_wdpc_pawams(stwuct ieee80211_sta *sta,
		stwuct wcn36xx_haw_config_sta_pawams_v1 *sta_pawams)
{
	if (sta->defwink.ht_cap.ht_suppowted) {
		sta_pawams->ht_wdpc_enabwed =
			is_cap_suppowted(sta->defwink.ht_cap.cap,
					 IEEE80211_HT_CAP_WDPC_CODING);
	}
}

static void wcn36xx_smd_set_sta_defauwt_ht_pawams(
		stwuct wcn36xx_haw_config_sta_pawams *sta_pawams)
{
	sta_pawams->ht_capabwe = 1;
	sta_pawams->tx_channew_width_set = 1;
	sta_pawams->wsig_txop_pwotection = 1;
	sta_pawams->max_ampdu_size = 3;
	sta_pawams->max_ampdu_density = 5;
	sta_pawams->max_amsdu_size = 0;
	sta_pawams->sgi_20Mhz = 1;
	sta_pawams->sgi_40mhz = 1;
	sta_pawams->gween_fiewd_capabwe = 1;
	sta_pawams->dewayed_ba_suppowt = 0;
	sta_pawams->dsss_cck_mode_40mhz = 1;
}

static void wcn36xx_smd_set_sta_defauwt_vht_pawams(stwuct wcn36xx *wcn,
		stwuct wcn36xx_haw_config_sta_pawams_v1 *sta_pawams)
{
	if (wcn->wf_id == WF_IWIS_WCN3680) {
		sta_pawams->vht_capabwe = 1;
		sta_pawams->vht_tx_mu_beamfowmee_capabwe = 1;
	} ewse {
		sta_pawams->vht_capabwe = 0;
		sta_pawams->vht_tx_mu_beamfowmee_capabwe = 0;
	}

	sta_pawams->vht_wdpc_enabwed = 0;
	sta_pawams->vht_tx_channew_width_set = 0;
	sta_pawams->vht_tx_bf_enabwed = 0;
}

static void wcn36xx_smd_set_sta_defauwt_ht_wdpc_pawams(stwuct wcn36xx *wcn,
		stwuct wcn36xx_haw_config_sta_pawams_v1 *sta_pawams)
{
	if (wcn->wf_id == WF_IWIS_WCN3680)
		sta_pawams->ht_wdpc_enabwed = 1;
	ewse
		sta_pawams->ht_wdpc_enabwed = 0;
}

static void wcn36xx_smd_set_sta_pawams(stwuct wcn36xx *wcn,
		stwuct ieee80211_vif *vif,
		stwuct ieee80211_sta *sta,
		stwuct wcn36xx_haw_config_sta_pawams *sta_pawams)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_sta *sta_pwiv = NUWW;
	if (vif->type == NW80211_IFTYPE_ADHOC ||
	    vif->type == NW80211_IFTYPE_AP ||
	    vif->type == NW80211_IFTYPE_MESH_POINT) {
		sta_pawams->type = 1;
		sta_pawams->sta_index = WCN36XX_HAW_STA_INVAWID_IDX;
	} ewse {
		sta_pawams->type = 0;
		sta_pawams->sta_index = vif_pwiv->sewf_sta_index;
	}

	sta_pawams->wisten_intewvaw = WCN36XX_WISTEN_INTEWVAW(wcn);

	/*
	 * In STA mode ieee80211_sta contains bssid and ieee80211_vif
	 * contains ouw mac addwess. In  AP mode we awe bssid so vif
	 * contains bssid and ieee80211_sta contains mac.
	 */
	if (NW80211_IFTYPE_STATION == vif->type)
		memcpy(&sta_pawams->mac, vif->addw, ETH_AWEN);
	ewse
		memcpy(&sta_pawams->bssid, vif->addw, ETH_AWEN);

	sta_pawams->encwypt_type = vif_pwiv->encwypt_type;
	sta_pawams->showt_pweambwe_suppowted = twue;

	sta_pawams->wifs_mode = 0;
	sta_pawams->wmf = 0;
	sta_pawams->action = 0;
	sta_pawams->uapsd = 0;
	sta_pawams->mimo_ps = WCN36XX_HAW_HT_MIMO_PS_STATIC;
	sta_pawams->max_ampdu_duwation = 0;
	sta_pawams->bssid_index = vif_pwiv->bss_index;
	sta_pawams->p2p = 0;

	if (sta) {
		sta_pwiv = wcn36xx_sta_to_pwiv(sta);
		if (NW80211_IFTYPE_STATION == vif->type)
			memcpy(&sta_pawams->bssid, sta->addw, ETH_AWEN);
		ewse
			memcpy(&sta_pawams->mac, sta->addw, ETH_AWEN);
		sta_pawams->wmm_enabwed = sta->wme;
		sta_pawams->max_sp_wen = sta->max_sp;
		sta_pawams->aid = sta_pwiv->aid;
		wcn36xx_smd_set_sta_ht_pawams(sta, sta_pawams);
		memcpy(&sta_pawams->suppowted_wates, &sta_pwiv->suppowted_wates,
			sizeof(stwuct wcn36xx_haw_suppowted_wates));
	} ewse {
		wcn36xx_set_defauwt_wates((stwuct wcn36xx_haw_suppowted_wates *)
					  &sta_pawams->suppowted_wates);
		wcn36xx_smd_set_sta_defauwt_ht_pawams(sta_pawams);
	}
}

static int wcn36xx_smd_send_and_wait(stwuct wcn36xx *wcn, size_t wen)
{
	int wet;
	unsigned wong stawt;
	stwuct wcn36xx_haw_msg_headew *hdw =
		(stwuct wcn36xx_haw_msg_headew *)wcn->haw_buf;
	u16 weq_type = hdw->msg_type;

	wcn36xx_dbg_dump(WCN36XX_DBG_SMD_DUMP, "HAW >>> ", wcn->haw_buf, wen);

	init_compwetion(&wcn->haw_wsp_compw);
	stawt = jiffies;
	wet = wpmsg_send(wcn->smd_channew, wcn->haw_buf, wen);
	if (wet) {
		wcn36xx_eww("HAW TX faiwed fow weq %d\n", weq_type);
		goto out;
	}
	if (wait_fow_compwetion_timeout(&wcn->haw_wsp_compw,
		msecs_to_jiffies(HAW_MSG_TIMEOUT)) <= 0) {
		wcn36xx_eww("Timeout! No SMD wesponse to weq %d in %dms\n",
			    weq_type, HAW_MSG_TIMEOUT);
		wet = -ETIME;
		goto out;
	}
	wcn36xx_dbg(WCN36XX_DBG_SMD,
		    "SMD command (weq %d, wsp %d) compweted in %dms\n",
		    weq_type, hdw->msg_type,
		    jiffies_to_msecs(jiffies - stawt));
out:
	wetuwn wet;
}

#define __INIT_HAW_MSG(msg_body, type, vewsion) \
	do {								\
		memset(&(msg_body), 0, sizeof(msg_body));		\
		(msg_body).headew.msg_type = type;			\
		(msg_body).headew.msg_vewsion = vewsion;		\
		(msg_body).headew.wen = sizeof(msg_body);		\
	} whiwe (0)							\

#define INIT_HAW_MSG(msg_body, type)	\
	__INIT_HAW_MSG(msg_body, type, WCN36XX_HAW_MSG_VEWSION0)

#define INIT_HAW_MSG_V1(msg_body, type) \
	__INIT_HAW_MSG(msg_body, type, WCN36XX_HAW_MSG_VEWSION1)

#define INIT_HAW_PTT_MSG(p_msg_body, ppt_msg_wen) \
	do { \
		memset(p_msg_body, 0, sizeof(*p_msg_body) + ppt_msg_wen); \
		p_msg_body->headew.msg_type = WCN36XX_HAW_PWOCESS_PTT_WEQ; \
		p_msg_body->headew.msg_vewsion = WCN36XX_HAW_MSG_VEWSION0; \
		p_msg_body->headew.wen = sizeof(*p_msg_body) + ppt_msg_wen; \
	} whiwe (0)

#define PWEPAWE_HAW_BUF(send_buf, msg_body) \
	do {							\
		memcpy_and_pad(send_buf, msg_body.headew.wen,	\
			       &msg_body, sizeof(msg_body), 0);	\
	} whiwe (0)						\

#define PWEPAWE_HAW_PTT_MSG_BUF(send_buf, p_msg_body) \
	do {							\
		memcpy(send_buf, p_msg_body, p_msg_body->headew.wen); \
	} whiwe (0)

static int wcn36xx_smd_wsp_status_check(void *buf, size_t wen)
{
	stwuct wcn36xx_fw_msg_status_wsp *wsp;

	if (wen < sizeof(stwuct wcn36xx_haw_msg_headew) +
	    sizeof(stwuct wcn36xx_fw_msg_status_wsp))
		wetuwn -EIO;

	wsp = (stwuct wcn36xx_fw_msg_status_wsp *)
		(buf + sizeof(stwuct wcn36xx_haw_msg_headew));

	if (WCN36XX_FW_MSG_WESUWT_SUCCESS != wsp->status)
		wetuwn wsp->status;

	wetuwn 0;
}

int wcn36xx_smd_woad_nv(stwuct wcn36xx *wcn)
{
	stwuct nv_data *nv_d;
	stwuct wcn36xx_haw_nv_img_downwoad_weq_msg msg_body;
	int fw_bytes_weft;
	int wet;
	u16 fm_offset = 0;

	if (!wcn->nv) {
		wet = wequest_fiwmwawe(&wcn->nv, wcn->nv_fiwe, wcn->dev);
		if (wet) {
			wcn36xx_eww("Faiwed to woad nv fiwe %s: %d\n",
				    wcn->nv_fiwe, wet);
			goto out;
		}
	}

	nv_d = (stwuct nv_data *)wcn->nv->data;
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_DOWNWOAD_NV_WEQ);

	msg_body.headew.wen += WCN36XX_NV_FWAGMENT_SIZE;

	msg_body.fwag_numbew = 0;
	/* haw_buf must be pwotected with  mutex */
	mutex_wock(&wcn->haw_mutex);

	do {
		fw_bytes_weft = wcn->nv->size - fm_offset - 4;
		if (fw_bytes_weft > WCN36XX_NV_FWAGMENT_SIZE) {
			msg_body.wast_fwagment = 0;
			msg_body.nv_img_buffew_size = WCN36XX_NV_FWAGMENT_SIZE;
		} ewse {
			msg_body.wast_fwagment = 1;
			msg_body.nv_img_buffew_size = fw_bytes_weft;

			/* Do not fowget update genewaw message wen */
			msg_body.headew.wen = sizeof(msg_body) + fw_bytes_weft;

		}

		/* Add woad NV wequest message headew */
		memcpy(wcn->haw_buf, &msg_body,	sizeof(msg_body));

		/* Add NV body itsewf */
		memcpy(wcn->haw_buf + sizeof(msg_body),
		       &nv_d->tabwe + fm_offset,
		       msg_body.nv_img_buffew_size);

		wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
		if (wet)
			goto out_unwock;
		wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf,
						   wcn->haw_wsp_wen);
		if (wet) {
			wcn36xx_eww("haw_woad_nv wesponse faiwed eww=%d\n",
				    wet);
			goto out_unwock;
		}
		msg_body.fwag_numbew++;
		fm_offset += WCN36XX_NV_FWAGMENT_SIZE;

	} whiwe (msg_body.wast_fwagment != 1);

out_unwock:
	mutex_unwock(&wcn->haw_mutex);
out:	wetuwn wet;
}

static int wcn36xx_smd_stawt_wsp(stwuct wcn36xx *wcn, void *buf, size_t wen)
{
	stwuct wcn36xx_haw_mac_stawt_wsp_msg *wsp;

	if (wen < sizeof(*wsp))
		wetuwn -EIO;

	wsp = buf;

	if (WCN36XX_FW_MSG_WESUWT_SUCCESS != wsp->stawt_wsp_pawams.status)
		wetuwn -EIO;

	memcpy(wcn->cwm_vewsion, wsp->stawt_wsp_pawams.cwm_vewsion,
	       WCN36XX_HAW_VEWSION_WENGTH);
	memcpy(wcn->wwan_vewsion, wsp->stawt_wsp_pawams.wwan_vewsion,
	       WCN36XX_HAW_VEWSION_WENGTH);

	/* nuww tewminate the stwings, just in case */
	wcn->cwm_vewsion[WCN36XX_HAW_VEWSION_WENGTH] = '\0';
	wcn->wwan_vewsion[WCN36XX_HAW_VEWSION_WENGTH] = '\0';

	wcn->fw_wevision = wsp->stawt_wsp_pawams.vewsion.wevision;
	wcn->fw_vewsion = wsp->stawt_wsp_pawams.vewsion.vewsion;
	wcn->fw_minow = wsp->stawt_wsp_pawams.vewsion.minow;
	wcn->fw_majow = wsp->stawt_wsp_pawams.vewsion.majow;

	if (wcn->fiwst_boot) {
		wcn->fiwst_boot = fawse;
		wcn36xx_info("fiwmwawe WWAN vewsion '%s' and CWM vewsion '%s'\n",
			     wcn->wwan_vewsion, wcn->cwm_vewsion);

		wcn36xx_info("fiwmwawe API %u.%u.%u.%u, %u stations, %u bssids\n",
			     wcn->fw_majow, wcn->fw_minow,
			     wcn->fw_vewsion, wcn->fw_wevision,
			     wsp->stawt_wsp_pawams.stations,
			     wsp->stawt_wsp_pawams.bssids);
	}
	wetuwn 0;
}

int wcn36xx_smd_stawt(stwuct wcn36xx *wcn)
{
	stwuct wcn36xx_haw_mac_stawt_weq_msg msg_body, *body;
	int wet;
	int i;
	size_t wen;
	int cfg_ewements;
	static stwuct wcn36xx_cfg_vaw *cfg_vaws;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_STAWT_WEQ);

	msg_body.pawams.type = DWIVEW_TYPE_PWODUCTION;
	msg_body.pawams.wen = 0;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	body = (stwuct wcn36xx_haw_mac_stawt_weq_msg *)wcn->haw_buf;
	wen = body->headew.wen;

	if (wcn->wf_id == WF_IWIS_WCN3680) {
		cfg_vaws = wcn3680_cfg_vaws;
		cfg_ewements = AWWAY_SIZE(wcn3680_cfg_vaws);
	} ewse {
		cfg_vaws = wcn36xx_cfg_vaws;
		cfg_ewements = AWWAY_SIZE(wcn36xx_cfg_vaws);
	}

	fow (i = 0; i < cfg_ewements; i++) {
		wet = put_cfg_twv_u32(wcn, &wen, cfg_vaws[i].cfg_id,
				      cfg_vaws[i].vawue);
		if (wet)
			goto out;
	}
	body->headew.wen = wen;
	body->pawams.wen = wen - sizeof(*body);

	wcn36xx_dbg(WCN36XX_DBG_HAW, "haw stawt type %d\n",
		    msg_body.pawams.type);

	wet = wcn36xx_smd_send_and_wait(wcn, body->headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_stawt faiwed\n");
		goto out;
	}

	wet = wcn36xx_smd_stawt_wsp(wcn, wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_stawt wesponse faiwed eww=%d\n", wet);
		goto out;
	}

out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_stop(stwuct wcn36xx *wcn)
{
	stwuct wcn36xx_haw_mac_stop_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_STOP_WEQ);

	msg_body.stop_weq_pawams.weason = HAW_STOP_TYPE_WF_KIWW;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_stop faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_stop wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_init_scan(stwuct wcn36xx *wcn, enum wcn36xx_haw_sys_mode mode,
			  stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_haw_init_scan_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_INIT_SCAN_WEQ);

	msg_body.mode = mode;
	if (vif_pwiv->bss_index != WCN36XX_HAW_BSS_INVAWID_IDX) {
		/* Notify BSSID with nuww DATA packet */
		msg_body.fwame_type = 2;
		msg_body.notify = 1;
		msg_body.scan_entwy.bss_index[0] = vif_pwiv->bss_index;
		msg_body.scan_entwy.active_bss_count = 1;
	}

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW, "haw init scan mode %d\n", msg_body.mode);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_init_scan faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_init_scan wesponse faiwed eww=%d\n", wet);
		goto out;
	}
	wcn->sw_scan_init = twue;
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_stawt_scan(stwuct wcn36xx *wcn, u8 scan_channew)
{
	stwuct wcn36xx_haw_stawt_scan_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_STAWT_SCAN_WEQ);

	msg_body.scan_channew = scan_channew;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW, "haw stawt scan channew %d\n",
		    msg_body.scan_channew);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_stawt_scan faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_stawt_scan wesponse faiwed eww=%d\n", wet);
		goto out;
	}
	wcn->sw_scan_channew = scan_channew;
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_end_scan(stwuct wcn36xx *wcn, u8 scan_channew)
{
	stwuct wcn36xx_haw_end_scan_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_END_SCAN_WEQ);

	msg_body.scan_channew = scan_channew;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW, "haw end scan channew %d\n",
		    msg_body.scan_channew);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_end_scan faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_end_scan wesponse faiwed eww=%d\n", wet);
		goto out;
	}
	wcn->sw_scan_channew = 0;
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_finish_scan(stwuct wcn36xx *wcn,
			    enum wcn36xx_haw_sys_mode mode,
			    stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_haw_finish_scan_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_FINISH_SCAN_WEQ);

	msg_body.mode = mode;
	msg_body.opew_channew = WCN36XX_HW_CHANNEW(wcn);
	if (vif_pwiv->bss_index != WCN36XX_HAW_BSS_INVAWID_IDX) {
		/* Notify BSSID with nuww data packet */
		msg_body.notify = 1;
		msg_body.fwame_type = 2;
		msg_body.scan_entwy.bss_index[0] = vif_pwiv->bss_index;
		msg_body.scan_entwy.active_bss_count = 1;
	}

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW, "haw finish scan mode %d\n",
		    msg_body.mode);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_finish_scan faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_finish_scan wesponse faiwed eww=%d\n", wet);
		goto out;
	}
	wcn->sw_scan_init = fawse;
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_stawt_hw_scan(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			      stwuct cfg80211_scan_wequest *weq)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_haw_stawt_scan_offwoad_weq_msg *msg_body;
	int wet, i;

	if (weq->ie_wen > WCN36XX_MAX_SCAN_IE_WEN)
		wetuwn -EINVAW;

	mutex_wock(&wcn->haw_mutex);
	msg_body = kzawwoc(sizeof(*msg_body), GFP_KEWNEW);
	if (!msg_body) {
		wet = -ENOMEM;
		goto out;
	}

	INIT_HAW_MSG((*msg_body), WCN36XX_HAW_STAWT_SCAN_OFFWOAD_WEQ);

	msg_body->scan_type = WCN36XX_HAW_SCAN_TYPE_ACTIVE;
	msg_body->min_ch_time = 30;
	msg_body->max_ch_time = 100;
	msg_body->scan_hidden = 1;
	memcpy(msg_body->mac, vif->addw, ETH_AWEN);
	msg_body->bss_type = vif_pwiv->bss_type;
	msg_body->p2p_seawch = vif->p2p;

	msg_body->num_ssid = min_t(u8, weq->n_ssids, AWWAY_SIZE(msg_body->ssids));
	fow (i = 0; i < msg_body->num_ssid; i++) {
		msg_body->ssids[i].wength = min_t(u8, weq->ssids[i].ssid_wen,
						sizeof(msg_body->ssids[i].ssid));
		memcpy(msg_body->ssids[i].ssid, weq->ssids[i].ssid,
		       msg_body->ssids[i].wength);
	}

	msg_body->num_channew = min_t(u8, weq->n_channews,
				     sizeof(msg_body->channews));
	fow (i = 0; i < msg_body->num_channew; i++) {
		msg_body->channews[i] =
			HW_VAWUE_CHANNEW(weq->channews[i]->hw_vawue);
	}

	msg_body->headew.wen -= WCN36XX_MAX_SCAN_IE_WEN;

	if (weq->ie_wen > 0) {
		msg_body->ie_wen = weq->ie_wen;
		msg_body->headew.wen += weq->ie_wen;
		memcpy(msg_body->ie, weq->ie, weq->ie_wen);
	}

	PWEPAWE_HAW_BUF(wcn->haw_buf, (*msg_body));

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw stawt hw-scan (channews: %u; ssids: %u; p2p: %s)\n",
		    msg_body->num_channew, msg_body->num_ssid,
		    msg_body->p2p_seawch ? "yes" : "no");

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body->headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_stawt_scan_offwoad faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_stawt_scan_offwoad wesponse faiwed eww=%d\n",
			    wet);
		goto out;
	}
out:
	kfwee(msg_body);
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_stop_hw_scan(stwuct wcn36xx *wcn)
{
	stwuct wcn36xx_haw_stop_scan_offwoad_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_STOP_SCAN_OFFWOAD_WEQ);
	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW, "haw stop hw-scan\n");

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_stop_scan_offwoad faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_stop_scan_offwoad wesponse faiwed eww=%d\n",
			    wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_update_channew_wist(stwuct wcn36xx *wcn, stwuct cfg80211_scan_wequest *weq)
{
	stwuct wcn36xx_haw_update_channew_wist_weq_msg *msg_body;
	int wet, i;

	msg_body = kzawwoc(sizeof(*msg_body), GFP_KEWNEW);
	if (!msg_body)
		wetuwn -ENOMEM;

	INIT_HAW_MSG((*msg_body), WCN36XX_HAW_UPDATE_CHANNEW_WIST_WEQ);

	msg_body->num_channew = min_t(u8, weq->n_channews, AWWAY_SIZE(msg_body->channews));
	fow (i = 0; i < msg_body->num_channew; i++) {
		stwuct wcn36xx_haw_channew_pawam *pawam = &msg_body->channews[i];
		u32 min_powew = WCN36XX_HAW_DEFAUWT_MIN_POWEW;
		u32 ant_gain = WCN36XX_HAW_DEFAUWT_ANT_GAIN;

		pawam->mhz = weq->channews[i]->centew_fweq;
		pawam->band_centew_fweq1 = weq->channews[i]->centew_fweq;
		pawam->band_centew_fweq2 = 0;

		if (weq->channews[i]->fwags & IEEE80211_CHAN_NO_IW)
			pawam->channew_info |= WCN36XX_HAW_CHAN_INFO_FWAG_PASSIVE;

		if (weq->channews[i]->fwags & IEEE80211_CHAN_WADAW)
			pawam->channew_info |= WCN36XX_HAW_CHAN_INFO_FWAG_DFS;

		if (weq->channews[i]->band == NW80211_BAND_5GHZ) {
			pawam->channew_info |= WCN36XX_HAW_CHAN_INFO_FWAG_HT;
			pawam->channew_info |= WCN36XX_HAW_CHAN_INFO_FWAG_VHT;
			pawam->channew_info |= WCN36XX_HAW_CHAN_INFO_PHY_11A;
		} ewse {
			pawam->channew_info |= WCN36XX_HAW_CHAN_INFO_PHY_11BG;
		}

		if (min_powew > weq->channews[i]->max_powew)
			min_powew = weq->channews[i]->max_powew;

		if (weq->channews[i]->max_antenna_gain)
			ant_gain = weq->channews[i]->max_antenna_gain;

		u32p_wepwace_bits(&pawam->weg_info_1, min_powew,
				  WCN36XX_HAW_CHAN_WEG1_MIN_PWW_MASK);
		u32p_wepwace_bits(&pawam->weg_info_1, weq->channews[i]->max_powew,
				  WCN36XX_HAW_CHAN_WEG1_MAX_PWW_MASK);
		u32p_wepwace_bits(&pawam->weg_info_1, weq->channews[i]->max_weg_powew,
				  WCN36XX_HAW_CHAN_WEG1_WEG_PWW_MASK);
		u32p_wepwace_bits(&pawam->weg_info_1, 0,
				  WCN36XX_HAW_CHAN_WEG1_CWASS_ID_MASK);
		u32p_wepwace_bits(&pawam->weg_info_2, ant_gain,
				  WCN36XX_HAW_CHAN_WEG2_ANT_GAIN_MASK);

		wcn36xx_dbg(WCN36XX_DBG_HAW,
			    "%s: fweq=%u, channew_info=%08x, weg_info1=%08x, weg_info2=%08x\n",
			    __func__, pawam->mhz, pawam->channew_info, pawam->weg_info_1,
			    pawam->weg_info_2);
	}

	mutex_wock(&wcn->haw_mutex);

	PWEPAWE_HAW_BUF(wcn->haw_buf, (*msg_body));

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body->headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_update_channew_wist faiwed\n");
		goto out;
	}

	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_update_channew_wist wesponse faiwed eww=%d\n", wet);
		goto out;
	}

out:
	kfwee(msg_body);
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

static int wcn36xx_smd_switch_channew_wsp(void *buf, size_t wen)
{
	stwuct wcn36xx_haw_switch_channew_wsp_msg *wsp;
	int wet;

	wet = wcn36xx_smd_wsp_status_check(buf, wen);
	if (wet)
		wetuwn wet;
	wsp = buf;
	wcn36xx_dbg(WCN36XX_DBG_HAW, "channew switched to: %d, status: %d\n",
		    wsp->channew_numbew, wsp->status);
	wetuwn wet;
}

int wcn36xx_smd_switch_channew(stwuct wcn36xx *wcn,
			       stwuct ieee80211_vif *vif, int ch)
{
	stwuct wcn36xx_haw_switch_channew_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_CH_SWITCH_WEQ);

	msg_body.channew_numbew = (u8)ch;
	msg_body.tx_mgmt_powew = 0xbf;
	msg_body.max_tx_powew = 0xbf;
	memcpy(msg_body.sewf_sta_mac_addw, vif->addw, ETH_AWEN);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_switch_channew faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_switch_channew_wsp(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_switch_channew wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

static int wcn36xx_smd_pwocess_ptt_msg_wsp(void *buf, size_t wen,
					   void **p_ptt_wsp_msg)
{
	stwuct wcn36xx_haw_pwocess_ptt_msg_wsp_msg *wsp;
	int wet;

	wet = wcn36xx_smd_wsp_status_check(buf, wen);
	if (wet)
		wetuwn wet;

	wsp = buf;

	wcn36xx_dbg(WCN36XX_DBG_HAW, "pwocess ptt msg wesponded with wength %d\n",
		    wsp->headew.wen);
	wcn36xx_dbg_dump(WCN36XX_DBG_HAW_DUMP, "HAW_PTT_MSG_WSP:", wsp->ptt_msg,
			 wsp->headew.wen - sizeof(wsp->ptt_msg_wesp_status));

	if (wsp->headew.wen > 0) {
		*p_ptt_wsp_msg = kmemdup(wsp->ptt_msg, wsp->headew.wen,
					 GFP_ATOMIC);
		if (!*p_ptt_wsp_msg)
			wetuwn -ENOMEM;
	}
	wetuwn wet;
}

int wcn36xx_smd_pwocess_ptt_msg(stwuct wcn36xx *wcn,
				stwuct ieee80211_vif *vif, void *ptt_msg, size_t wen,
		void **ptt_wsp_msg)
{
	stwuct wcn36xx_haw_pwocess_ptt_msg_weq_msg *p_msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	p_msg_body = kmawwoc(
		sizeof(stwuct wcn36xx_haw_pwocess_ptt_msg_weq_msg) + wen,
		GFP_ATOMIC);
	if (!p_msg_body) {
		wet = -ENOMEM;
		goto out_nomem;
	}
	INIT_HAW_PTT_MSG(p_msg_body, wen);

	memcpy(&p_msg_body->ptt_msg, ptt_msg, wen);

	PWEPAWE_HAW_PTT_MSG_BUF(wcn->haw_buf, p_msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, p_msg_body->headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_pwocess_ptt_msg faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_pwocess_ptt_msg_wsp(wcn->haw_buf, wcn->haw_wsp_wen,
					      ptt_wsp_msg);
	if (wet) {
		wcn36xx_eww("pwocess_ptt_msg wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	kfwee(p_msg_body);
out_nomem:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

static int wcn36xx_smd_update_scan_pawams_wsp(void *buf, size_t wen)
{
	stwuct wcn36xx_haw_update_scan_pawams_wesp *wsp;

	wsp = buf;

	/* Wemove the PNO vewsion bit */
	wsp->status &= (~(WCN36XX_FW_MSG_PNO_VEWSION_MASK));

	if (WCN36XX_FW_MSG_WESUWT_SUCCESS != wsp->status) {
		wcn36xx_wawn("ewwow wesponse fwom update scan\n");
		wetuwn wsp->status;
	}

	wetuwn 0;
}

int wcn36xx_smd_update_scan_pawams(stwuct wcn36xx *wcn,
				   u8 *channews, size_t channew_count)
{
	stwuct wcn36xx_haw_update_scan_pawams_weq_ex msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_UPDATE_SCAN_PAWAM_WEQ);

	msg_body.dot11d_enabwed	= fawse;
	msg_body.dot11d_wesowved = twue;

	msg_body.channew_count = channew_count;
	memcpy(msg_body.channews, channews, channew_count);
	msg_body.active_min_ch_time = 60;
	msg_body.active_max_ch_time = 120;
	msg_body.passive_min_ch_time = 60;
	msg_body.passive_max_ch_time = 110;
	msg_body.state = PHY_SINGWE_CHANNEW_CENTEWED;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw update scan pawams channew_count %d\n",
		    msg_body.channew_count);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_update_scan_pawams faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_update_scan_pawams_wsp(wcn->haw_buf,
						 wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_update_scan_pawams wesponse faiwed eww=%d\n",
			    wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

static int wcn36xx_smd_add_sta_sewf_wsp(stwuct wcn36xx *wcn,
					stwuct ieee80211_vif *vif,
					void *buf,
					size_t wen)
{
	stwuct wcn36xx_haw_add_sta_sewf_wsp_msg *wsp;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);

	if (wen < sizeof(*wsp))
		wetuwn -EINVAW;

	wsp = buf;

	if (wsp->status != WCN36XX_FW_MSG_WESUWT_SUCCESS) {
		wcn36xx_wawn("haw add sta sewf faiwuwe: %d\n",
			     wsp->status);
		wetuwn wsp->status;
	}

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw add sta sewf status %d sewf_sta_index %d dpu_index %d\n",
		    wsp->status, wsp->sewf_sta_index, wsp->dpu_index);

	vif_pwiv->sewf_sta_index = wsp->sewf_sta_index;
	vif_pwiv->sewf_dpu_desc_index = wsp->dpu_index;

	wetuwn 0;
}

int wcn36xx_smd_add_sta_sewf(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx_haw_add_sta_sewf_weq msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_ADD_STA_SEWF_WEQ);

	memcpy(&msg_body.sewf_addw, vif->addw, ETH_AWEN);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw add sta sewf sewf_addw %pM status %d\n",
		    msg_body.sewf_addw, msg_body.status);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_add_sta_sewf faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_add_sta_sewf_wsp(wcn,
					   vif,
					   wcn->haw_buf,
					   wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_add_sta_sewf wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_dewete_sta_sewf(stwuct wcn36xx *wcn, u8 *addw)
{
	stwuct wcn36xx_haw_dew_sta_sewf_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_DEW_STA_SEWF_WEQ);

	memcpy(&msg_body.sewf_addw, addw, ETH_AWEN);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_dewete_sta_sewf faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_dewete_sta_sewf wesponse faiwed eww=%d\n",
			    wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_dewete_sta(stwuct wcn36xx *wcn, u8 sta_index)
{
	stwuct wcn36xx_haw_dewete_sta_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_DEWETE_STA_WEQ);

	msg_body.sta_index = sta_index;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw dewete sta sta_index %d\n",
		    msg_body.sta_index);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_dewete_sta faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_dewete_sta wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

static int wcn36xx_smd_join_wsp(void *buf, size_t wen)
{
	stwuct wcn36xx_haw_join_wsp_msg *wsp;

	if (wcn36xx_smd_wsp_status_check(buf, wen))
		wetuwn -EIO;

	wsp = buf;

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw wsp join status %d tx_mgmt_powew %d\n",
		    wsp->status, wsp->tx_mgmt_powew);

	wetuwn 0;
}

int wcn36xx_smd_join(stwuct wcn36xx *wcn, const u8 *bssid, u8 *vif, u8 ch)
{
	stwuct wcn36xx_haw_join_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_JOIN_WEQ);

	memcpy(&msg_body.bssid, bssid, ETH_AWEN);
	memcpy(&msg_body.sewf_sta_mac_addw, vif, ETH_AWEN);
	msg_body.channew = ch;

	if (conf_is_ht40_minus(&wcn->hw->conf))
		msg_body.secondawy_channew_offset =
			PHY_DOUBWE_CHANNEW_HIGH_PWIMAWY;
	ewse if (conf_is_ht40_pwus(&wcn->hw->conf))
		msg_body.secondawy_channew_offset =
			PHY_DOUBWE_CHANNEW_WOW_PWIMAWY;
	ewse
		msg_body.secondawy_channew_offset =
			PHY_SINGWE_CHANNEW_CENTEWED;

	msg_body.wink_state = WCN36XX_HAW_WINK_PWEASSOC_STATE;

	msg_body.max_tx_powew = 0xbf;
	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw join weq bssid %pM sewf_sta_mac_addw %pM channew %d wink_state %d\n",
		    msg_body.bssid, msg_body.sewf_sta_mac_addw,
		    msg_body.channew, msg_body.wink_state);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_join faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_join_wsp(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_join wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_set_wink_st(stwuct wcn36xx *wcn, const u8 *bssid,
			    const u8 *sta_mac,
			    enum wcn36xx_haw_wink_state state)
{
	stwuct wcn36xx_haw_set_wink_state_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_SET_WINK_ST_WEQ);

	memcpy(&msg_body.bssid, bssid, ETH_AWEN);
	memcpy(&msg_body.sewf_mac_addw, sta_mac, ETH_AWEN);
	msg_body.state = state;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw set wink state bssid %pM sewf_mac_addw %pM state %d\n",
		    msg_body.bssid, msg_body.sewf_mac_addw, msg_body.state);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_set_wink_st faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_set_wink_st wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

static void wcn36xx_smd_convewt_sta_to_v1(stwuct wcn36xx *wcn,
			const stwuct wcn36xx_haw_config_sta_pawams *owig,
			stwuct wcn36xx_haw_config_sta_pawams_v1 *v1)
{
	/* convewt owig to v1 fowmat */
	memcpy(&v1->bssid, owig->bssid, ETH_AWEN);
	memcpy(&v1->mac, owig->mac, ETH_AWEN);
	v1->aid = owig->aid;
	v1->type = owig->type;
	v1->showt_pweambwe_suppowted = owig->showt_pweambwe_suppowted;
	v1->wisten_intewvaw = owig->wisten_intewvaw;
	v1->wmm_enabwed = owig->wmm_enabwed;
	v1->ht_capabwe = owig->ht_capabwe;
	v1->tx_channew_width_set = owig->tx_channew_width_set;
	v1->wifs_mode = owig->wifs_mode;
	v1->wsig_txop_pwotection = owig->wsig_txop_pwotection;
	v1->max_ampdu_size = owig->max_ampdu_size;
	v1->max_ampdu_density = owig->max_ampdu_density;
	v1->sgi_40mhz = owig->sgi_40mhz;
	v1->sgi_20Mhz = owig->sgi_20Mhz;
	v1->wmf = owig->wmf;
	v1->encwypt_type = owig->encwypt_type;
	v1->action = owig->action;
	v1->uapsd = owig->uapsd;
	v1->max_sp_wen = owig->max_sp_wen;
	v1->gween_fiewd_capabwe = owig->gween_fiewd_capabwe;
	v1->mimo_ps = owig->mimo_ps;
	v1->dewayed_ba_suppowt = owig->dewayed_ba_suppowt;
	v1->max_ampdu_duwation = owig->max_ampdu_duwation;
	v1->dsss_cck_mode_40mhz = owig->dsss_cck_mode_40mhz;
	memcpy(&v1->suppowted_wates, &owig->suppowted_wates,
	       sizeof(owig->suppowted_wates));
	v1->sta_index = owig->sta_index;
	v1->bssid_index = owig->bssid_index;
	v1->p2p = owig->p2p;
}

static void
wcn36xx_smd_set_sta_pawams_v1(stwuct wcn36xx *wcn,
			      stwuct ieee80211_vif *vif,
			      stwuct ieee80211_sta *sta,
			      stwuct wcn36xx_haw_config_sta_pawams_v1 *sta_paw)
{
	stwuct wcn36xx_sta *sta_pwiv = NUWW;
	stwuct wcn36xx_haw_config_sta_pawams sta_paw_v0;

	wcn36xx_smd_set_sta_pawams(wcn, vif, sta, &sta_paw_v0);
	wcn36xx_smd_convewt_sta_to_v1(wcn, &sta_paw_v0, sta_paw);

	if (sta) {
		sta_pwiv = wcn36xx_sta_to_pwiv(sta);
		wcn36xx_smd_set_sta_vht_pawams(wcn, sta, sta_paw);
		wcn36xx_smd_set_sta_ht_wdpc_pawams(sta, sta_paw);
		memcpy(&sta_paw->suppowted_wates, &sta_pwiv->suppowted_wates,
		       sizeof(sta_paw->suppowted_wates));
	} ewse {
		wcn36xx_set_defauwt_wates_v1(&sta_paw->suppowted_wates);
		wcn36xx_smd_set_sta_defauwt_vht_pawams(wcn, sta_paw);
		wcn36xx_smd_set_sta_defauwt_ht_wdpc_pawams(wcn, sta_paw);
	}
}

static int wcn36xx_smd_config_sta_wsp(stwuct wcn36xx *wcn,
				      stwuct ieee80211_sta *sta,
				      void *buf,
				      size_t wen)
{
	stwuct wcn36xx_haw_config_sta_wsp_msg *wsp;
	stwuct config_sta_wsp_pawams *pawams;
	stwuct wcn36xx_sta *sta_pwiv = wcn36xx_sta_to_pwiv(sta);

	if (wen < sizeof(*wsp))
		wetuwn -EINVAW;

	wsp = buf;
	pawams = &wsp->pawams;

	if (pawams->status != WCN36XX_FW_MSG_WESUWT_SUCCESS) {
		wcn36xx_wawn("haw config sta wesponse faiwuwe: %d\n",
			     pawams->status);
		wetuwn -EIO;
	}

	sta_pwiv->sta_index = pawams->sta_index;
	sta_pwiv->dpu_desc_index = pawams->dpu_index;
	sta_pwiv->ucast_dpu_sign = pawams->uc_ucast_sig;

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw config sta wsp status %d sta_index %d bssid_index %d uc_ucast_sig %d p2p %d\n",
		    pawams->status, pawams->sta_index, pawams->bssid_index,
		    pawams->uc_ucast_sig, pawams->p2p);

	wetuwn 0;
}

static int wcn36xx_smd_config_sta_v1(stwuct wcn36xx *wcn,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta)
{
	stwuct wcn36xx_haw_config_sta_weq_msg_v1 msg_body;
	stwuct wcn36xx_haw_config_sta_pawams_v1 *sta_pawams;

	if (wcn->wf_id == WF_IWIS_WCN3680) {
		INIT_HAW_MSG_V1(msg_body, WCN36XX_HAW_CONFIG_STA_WEQ);
	} ewse {
		INIT_HAW_MSG(msg_body, WCN36XX_HAW_CONFIG_STA_WEQ);
		msg_body.headew.wen -= WCN36XX_DIFF_STA_PAWAMS_V1_NOVHT;
	}

	sta_pawams = &msg_body.sta_pawams;

	wcn36xx_smd_set_sta_pawams_v1(wcn, vif, sta, sta_pawams);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw config sta v1 action %d sta_index %d bssid_index %d bssid %pM type %d mac %pM aid %d\n",
		    sta_pawams->action, sta_pawams->sta_index, sta_pawams->bssid_index,
		    sta_pawams->bssid, sta_pawams->type, sta_pawams->mac, sta_pawams->aid);

	wetuwn wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
}

static int wcn36xx_smd_config_sta_v0(stwuct wcn36xx *wcn,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta)
{
	stwuct wcn36xx_haw_config_sta_weq_msg msg;
	stwuct wcn36xx_haw_config_sta_pawams *sta_pawams;

	INIT_HAW_MSG(msg, WCN36XX_HAW_CONFIG_STA_WEQ);

	sta_pawams = &msg.sta_pawams;

	wcn36xx_smd_set_sta_pawams(wcn, vif, sta, sta_pawams);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg);

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw config sta action %d sta_index %d bssid_index %d bssid %pM type %d mac %pM aid %d\n",
		    sta_pawams->action, sta_pawams->sta_index,
		    sta_pawams->bssid_index, sta_pawams->bssid,
		    sta_pawams->type, sta_pawams->mac, sta_pawams->aid);

	wetuwn wcn36xx_smd_send_and_wait(wcn, msg.headew.wen);
}

int wcn36xx_smd_config_sta(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta)
{
	int wet;

	mutex_wock(&wcn->haw_mutex);

	if (!wcn36xx_is_fw_vewsion(wcn, 1, 2, 2, 24))
		wet = wcn36xx_smd_config_sta_v1(wcn, vif, sta);
	ewse
		wet = wcn36xx_smd_config_sta_v0(wcn, vif, sta);

	if (wet) {
		wcn36xx_eww("Sending haw_config_sta faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_config_sta_wsp(wcn,
					 sta,
					 wcn->haw_buf,
					 wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_config_sta wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

static void wcn36xx_smd_set_bss_pawams(stwuct wcn36xx *wcn,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_sta *sta,
				       const u8 *bssid,
				       boow update,
				       stwuct wcn36xx_haw_config_bss_pawams *bss)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);

	WAWN_ON(is_zewo_ethew_addw(bssid));

	memcpy(&bss->bssid, bssid, ETH_AWEN);

	memcpy(bss->sewf_mac_addw, vif->addw, ETH_AWEN);

	if (vif->type == NW80211_IFTYPE_STATION) {
		bss->bss_type = WCN36XX_HAW_INFWASTWUCTUWE_MODE;

		/* STA */
		bss->opew_mode = 1;
		bss->wcn36xx_haw_pewsona = WCN36XX_HAW_STA_MODE;
	} ewse if (vif->type == NW80211_IFTYPE_AP ||
		   vif->type == NW80211_IFTYPE_MESH_POINT) {
		bss->bss_type = WCN36XX_HAW_INFWA_AP_MODE;

		/* AP */
		bss->opew_mode = 0;
		bss->wcn36xx_haw_pewsona = WCN36XX_HAW_STA_SAP_MODE;
	} ewse if (vif->type == NW80211_IFTYPE_ADHOC) {
		bss->bss_type = WCN36XX_HAW_IBSS_MODE;

		/* STA */
		bss->opew_mode = 1;
	} ewse {
		wcn36xx_wawn("Unknown type fow bss config: %d\n", vif->type);
	}

	if (vif->type == NW80211_IFTYPE_STATION)
		wcn36xx_smd_set_bss_nw_type(wcn, sta, bss);
	ewse
		bss->nw_type = WCN36XX_HAW_11N_NW_TYPE;

	bss->showt_swot_time_suppowted = vif->bss_conf.use_showt_swot;
	bss->wwa_coexist = 0;
	bss->wwb_coexist = 0;
	bss->wwg_coexist = 0;
	bss->wifs_mode = 0;
	bss->beacon_intewvaw = vif->bss_conf.beacon_int;
	bss->dtim_pewiod = vif_pwiv->dtim_pewiod;

	wcn36xx_smd_set_bss_ht_pawams(vif, sta, bss);

	bss->opew_channew = WCN36XX_HW_CHANNEW(wcn);

	if (conf_is_ht40_minus(&wcn->hw->conf))
		bss->ext_channew = IEEE80211_HT_PAWAM_CHA_SEC_BEWOW;
	ewse if (conf_is_ht40_pwus(&wcn->hw->conf))
		bss->ext_channew = IEEE80211_HT_PAWAM_CHA_SEC_ABOVE;
	ewse
		bss->ext_channew = IEEE80211_HT_PAWAM_CHA_SEC_NONE;

	bss->wesewved = 0;

	/* wcn->ssid is onwy vawid in AP and IBSS mode */
	bss->ssid.wength = vif_pwiv->ssid.wength;
	memcpy(bss->ssid.ssid, vif_pwiv->ssid.ssid, vif_pwiv->ssid.wength);

	bss->obss_pwot_enabwed = 0;
	bss->wmf = 0;
	bss->max_pwobe_wesp_wetwy_wimit = 0;
	bss->hidden_ssid = vif->bss_conf.hidden_ssid;
	bss->pwoxy_pwobe_wesp = 0;
	bss->edca_pawams_vawid = 0;

	/* FIXME: set acbe, acbk, acvi and acvo */

	bss->ext_set_sta_key_pawam_vawid = 0;

	/* FIXME: set ext_set_sta_key_pawam */

	bss->spectwum_mgt_enabwe = 0;
	bss->tx_mgmt_powew = 0;
	bss->max_tx_powew = WCN36XX_MAX_POWEW(wcn);
	bss->action = update;

	vif_pwiv->bss_type = bss->bss_type;
}

static int wcn36xx_smd_config_bss_v1(stwuct wcn36xx *wcn,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta_80211,
				     const u8 *bssid,
				     boow update)
{
	stwuct wcn36xx_haw_config_bss_weq_msg_v1 *msg_body;
	stwuct wcn36xx_haw_config_bss_pawams_v1 *bss;
	stwuct wcn36xx_haw_config_bss_pawams bss_v0;
	stwuct wcn36xx_haw_config_sta_pawams_v1 *sta;
	stwuct cfg80211_chan_def *chandef;
	int wet;

	msg_body = kzawwoc(sizeof(*msg_body), GFP_KEWNEW);
	if (!msg_body)
		wetuwn -ENOMEM;

	if (wcn->wf_id == WF_IWIS_WCN3680) {
		INIT_HAW_MSG_V1((*msg_body), WCN36XX_HAW_CONFIG_BSS_WEQ);
	} ewse {
		INIT_HAW_MSG((*msg_body), WCN36XX_HAW_CONFIG_BSS_WEQ);
		msg_body->headew.wen -= WCN36XX_DIFF_BSS_PAWAMS_V1_NOVHT;
	}

	bss = &msg_body->bss_pawams;
	sta = &bss->sta;

	memset(&bss_v0, 0x00, sizeof(bss_v0));
	wcn36xx_smd_set_bss_pawams(wcn, vif, sta_80211, bssid, update, &bss_v0);
	wcn36xx_smd_set_sta_pawams_v1(wcn, vif, sta_80211, sta);

	/* convewt owig to v1 */
	memcpy(bss->bssid, &bss_v0.bssid, ETH_AWEN);
	memcpy(bss->sewf_mac_addw, &bss_v0.sewf_mac_addw, ETH_AWEN);

	bss->bss_type = bss_v0.bss_type;
	bss->opew_mode = bss_v0.opew_mode;
	bss->nw_type = bss_v0.nw_type;

	bss->showt_swot_time_suppowted =
		bss_v0.showt_swot_time_suppowted;
	bss->wwa_coexist = bss_v0.wwa_coexist;
	bss->wwb_coexist = bss_v0.wwb_coexist;
	bss->wwg_coexist = bss_v0.wwg_coexist;
	bss->ht20_coexist = bss_v0.ht20_coexist;
	bss->wwn_non_gf_coexist = bss_v0.wwn_non_gf_coexist;

	bss->wsig_tx_op_pwotection_fuww_suppowt =
		bss_v0.wsig_tx_op_pwotection_fuww_suppowt;
	bss->wifs_mode = bss_v0.wifs_mode;
	bss->beacon_intewvaw = bss_v0.beacon_intewvaw;
	bss->dtim_pewiod = bss_v0.dtim_pewiod;
	bss->tx_channew_width_set = bss_v0.tx_channew_width_set;
	bss->opew_channew = bss_v0.opew_channew;

	if (wcn->hw->conf.chandef.width == NW80211_CHAN_WIDTH_80) {
		chandef = &wcn->hw->conf.chandef;
		bss->ext_channew = HW_VAWUE_PHY(chandef->chan->hw_vawue);
	} ewse {
		bss->ext_channew = bss_v0.ext_channew;
	}

	bss->wesewved = bss_v0.wesewved;

	memcpy(&bss->ssid, &bss_v0.ssid,
	       sizeof(bss_v0.ssid));

	bss->action = bss_v0.action;
	bss->wateset = bss_v0.wateset;
	bss->ht = bss_v0.ht;
	bss->obss_pwot_enabwed = bss_v0.obss_pwot_enabwed;
	bss->wmf = bss_v0.wmf;
	bss->ht_opew_mode = bss_v0.ht_opew_mode;
	bss->duaw_cts_pwotection = bss_v0.duaw_cts_pwotection;

	bss->max_pwobe_wesp_wetwy_wimit =
		bss_v0.max_pwobe_wesp_wetwy_wimit;
	bss->hidden_ssid = bss_v0.hidden_ssid;
	bss->pwoxy_pwobe_wesp =	bss_v0.pwoxy_pwobe_wesp;
	bss->edca_pawams_vawid = bss_v0.edca_pawams_vawid;

	memcpy(&bss->acbe, &bss_v0.acbe,
	       sizeof(bss_v0.acbe));
	memcpy(&bss->acbk, &bss_v0.acbk,
	       sizeof(bss_v0.acbk));
	memcpy(&bss->acvi, &bss_v0.acvi,
	       sizeof(bss_v0.acvi));
	memcpy(&bss->acvo, &bss_v0.acvo,
	       sizeof(bss_v0.acvo));

	bss->ext_set_sta_key_pawam_vawid =
		bss_v0.ext_set_sta_key_pawam_vawid;

	memcpy(&bss->ext_set_sta_key_pawam,
	       &bss_v0.ext_set_sta_key_pawam,
	       sizeof(bss_v0.acvo));

	bss->wcn36xx_haw_pewsona = bss_v0.wcn36xx_haw_pewsona;
	bss->spectwum_mgt_enabwe = bss_v0.spectwum_mgt_enabwe;
	bss->tx_mgmt_powew = bss_v0.tx_mgmt_powew;
	bss->max_tx_powew = bss_v0.max_tx_powew;

	wcn36xx_smd_set_bss_vht_pawams(vif, sta_80211, bss);

	PWEPAWE_HAW_BUF(wcn->haw_buf, (*msg_body));

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw config bss v1 bssid %pM sewf_mac_addw %pM bss_type %d opew_mode %d nw_type %d\n",
		    bss->bssid, bss->sewf_mac_addw, bss->bss_type,
		    bss->opew_mode, bss->nw_type);

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "- sta bssid %pM action %d sta_index %d bssid_index %d aid %d type %d mac %pM\n",
		    sta->bssid, sta->action, sta->sta_index,
		    sta->bssid_index, sta->aid, sta->type, sta->mac);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body->headew.wen);
	kfwee(msg_body);

	wetuwn wet;
}

static int wcn36xx_smd_config_bss_v0(stwuct wcn36xx *wcn,
				     stwuct ieee80211_vif *vif,
				     stwuct ieee80211_sta *sta,
				     const u8 *bssid,
				     boow update)
{
	stwuct wcn36xx_haw_config_bss_weq_msg *msg;
	stwuct wcn36xx_haw_config_bss_pawams *bss;
	stwuct wcn36xx_haw_config_sta_pawams *sta_pawams;
	int wet;

	msg = kzawwoc(sizeof(*msg), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	INIT_HAW_MSG((*msg), WCN36XX_HAW_CONFIG_BSS_WEQ);

	bss = &msg->bss_pawams;
	sta_pawams = &bss->sta;

	wcn36xx_smd_set_bss_pawams(wcn, vif, sta, bssid, update, bss);
	wcn36xx_smd_set_sta_pawams(wcn, vif, sta, sta_pawams);

	PWEPAWE_HAW_BUF(wcn->haw_buf, (*msg));

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw config bss bssid %pM sewf_mac_addw %pM bss_type %d opew_mode %d nw_type %d\n",
		    bss->bssid, bss->sewf_mac_addw, bss->bss_type,
		    bss->opew_mode, bss->nw_type);

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "- sta bssid %pM action %d sta_index %d bssid_index %d aid %d type %d mac %pM\n",
		    sta_pawams->bssid, sta_pawams->action,
		    sta_pawams->sta_index, sta_pawams->bssid_index,
		    sta_pawams->aid, sta_pawams->type,
		    sta_pawams->mac);

	wet = wcn36xx_smd_send_and_wait(wcn, msg->headew.wen);
	kfwee(msg);

	wetuwn wet;
}

static int wcn36xx_smd_config_bss_wsp(stwuct wcn36xx *wcn,
				      stwuct ieee80211_vif *vif,
				      stwuct ieee80211_sta *sta,
				      void *buf,
				      size_t wen)
{
	stwuct wcn36xx_haw_config_bss_wsp_msg *wsp;
	stwuct wcn36xx_haw_config_bss_wsp_pawams *pawams;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);

	if (wen < sizeof(*wsp))
		wetuwn -EINVAW;

	wsp = buf;
	pawams = &wsp->bss_wsp_pawams;

	if (pawams->status != WCN36XX_FW_MSG_WESUWT_SUCCESS) {
		wcn36xx_wawn("haw config bss wesponse faiwuwe: %d\n",
			     pawams->status);
		wetuwn -EIO;
	}

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw config bss wsp status %d bss_idx %d dpu_desc_index %d"
		    " sta_idx %d sewf_idx %d bcast_idx %d mac %pM"
		    " powew %d ucast_dpu_signatuwe %d\n",
		    pawams->status, pawams->bss_index, pawams->dpu_desc_index,
		    pawams->bss_sta_index, pawams->bss_sewf_sta_index,
		    pawams->bss_bcast_sta_idx, pawams->mac,
		    pawams->tx_mgmt_powew, pawams->ucast_dpu_signatuwe);

	vif_pwiv->bss_index = pawams->bss_index;

	if (sta) {
		stwuct wcn36xx_sta *sta_pwiv = wcn36xx_sta_to_pwiv(sta);
		sta_pwiv->bss_sta_index = pawams->bss_sta_index;
		sta_pwiv->bss_dpu_desc_index = pawams->dpu_desc_index;
	}

	vif_pwiv->sewf_ucast_dpu_sign = pawams->ucast_dpu_signatuwe;

	wetuwn 0;
}

int wcn36xx_smd_config_bss(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta, const u8 *bssid,
			   boow update)
{
	int wet;

	mutex_wock(&wcn->haw_mutex);

	if (!wcn36xx_is_fw_vewsion(wcn, 1, 2, 2, 24))
		wet = wcn36xx_smd_config_bss_v1(wcn, vif, sta, bssid, update);
	ewse
		wet = wcn36xx_smd_config_bss_v0(wcn, vif, sta, bssid, update);

	if (wet) {
		wcn36xx_eww("Sending haw_config_bss faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_config_bss_wsp(wcn,
					 vif,
					 sta,
					 wcn->haw_buf,
					 wcn->haw_wsp_wen);
	if (wet)
		wcn36xx_eww("haw_config_bss wesponse faiwed eww=%d\n", wet);

out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_dewete_bss(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx_haw_dewete_bss_weq_msg msg_body;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	int wet = 0;

	mutex_wock(&wcn->haw_mutex);

	if (vif_pwiv->bss_index == WCN36XX_HAW_BSS_INVAWID_IDX)
		goto out;

	INIT_HAW_MSG(msg_body, WCN36XX_HAW_DEWETE_BSS_WEQ);

	msg_body.bss_index = vif_pwiv->bss_index;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW, "haw dewete bss %d\n", msg_body.bss_index);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_dewete_bss faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_dewete_bss wesponse faiwed eww=%d\n", wet);
		goto out;
	}

	vif_pwiv->bss_index = WCN36XX_HAW_BSS_INVAWID_IDX;
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_send_beacon(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			    stwuct sk_buff *skb_beacon, u16 tim_off,
			    u16 p2p_off)
{
	stwuct wcn36xx_haw_send_beacon_weq_msg msg_body;
	int wet, pad, pvm_wen;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_SEND_BEACON_WEQ);

	pvm_wen = skb_beacon->data[tim_off + 1] - 3;
	pad = TIM_MIN_PVM_SIZE - pvm_wen;

	/* Padding is iwwewevant to mesh mode since tim_off is awways 0. */
	if (vif->type == NW80211_IFTYPE_MESH_POINT)
		pad = 0;

	msg_body.beacon_wength = skb_beacon->wen + pad;
	/* TODO need to find out why + 6 is needed */
	msg_body.beacon_wength6 = msg_body.beacon_wength + 6;

	if (msg_body.beacon_wength > BEACON_TEMPWATE_SIZE) {
		wcn36xx_eww("Beacon is too big: beacon size=%d\n",
			      msg_body.beacon_wength);
		wet = -ENOMEM;
		goto out;
	}
	memcpy(msg_body.beacon, skb_beacon->data, skb_beacon->wen);
	memcpy(msg_body.bssid, vif->addw, ETH_AWEN);

	if (pad > 0) {
		/*
		 * The wcn36xx FW has a fixed size fow the PVM in the TIM. If
		 * given the beacon tempwate fwom mac80211 with a PVM showtew
		 * than the FW expectes it wiww ovewwwite the data aftew the
		 * TIM.
		 */
		wcn36xx_dbg(WCN36XX_DBG_HAW, "Pad TIM PVM. %d bytes at %d\n",
			    pad, pvm_wen);
		memmove(&msg_body.beacon[tim_off + 5 + pvm_wen + pad],
			&msg_body.beacon[tim_off + 5 + pvm_wen],
			skb_beacon->wen - (tim_off + 5 + pvm_wen));
		memset(&msg_body.beacon[tim_off + 5 + pvm_wen], 0, pad);
		msg_body.beacon[tim_off + 1] += pad;
	}

	/* TODO need to find out why this is needed? */
	if (vif->type == NW80211_IFTYPE_MESH_POINT)
		/* mesh beacon don't need this, so push fuwthew down */
		msg_body.tim_ie_offset = 256;
	ewse
		msg_body.tim_ie_offset = tim_off+4;
	msg_body.p2p_ie_offset = p2p_off;
	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw send beacon beacon_wength %d\n",
		    msg_body.beacon_wength);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_send_beacon faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_send_beacon wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_update_pwobewesp_tmpw(stwuct wcn36xx *wcn,
				      stwuct ieee80211_vif *vif,
				      stwuct sk_buff *skb)
{
	stwuct wcn36xx_haw_send_pwobe_wesp_weq_msg msg;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg, WCN36XX_HAW_UPDATE_PWOBE_WSP_TEMPWATE_WEQ);

	if (skb->wen > BEACON_TEMPWATE_SIZE) {
		wcn36xx_wawn("pwobe wesponse tempwate is too big: %d\n",
			     skb->wen);
		wet = -E2BIG;
		goto out;
	}

	msg.pwobe_wesp_tempwate_wen = skb->wen;
	memcpy(&msg.pwobe_wesp_tempwate, skb->data, skb->wen);

	memcpy(msg.bssid, vif->addw, ETH_AWEN);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg);

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "haw update pwobe wsp wen %d bssid %pM\n",
		    msg.pwobe_wesp_tempwate_wen, msg.bssid);

	wet = wcn36xx_smd_send_and_wait(wcn, msg.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_update_pwobewesp_tmpw faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_update_pwobewesp_tmpw wesponse faiwed eww=%d\n",
			    wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_set_stakey(stwuct wcn36xx *wcn,
			   enum ani_ed_type enc_type,
			   u8 keyidx,
			   u8 keywen,
			   u8 *key,
			   u8 sta_index)
{
	stwuct wcn36xx_haw_set_sta_key_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_SET_STAKEY_WEQ);

	msg_body.set_sta_key_pawams.sta_index = sta_index;
	msg_body.set_sta_key_pawams.enc_type = enc_type;

	if (enc_type == WCN36XX_HAW_ED_WEP104 ||
	    enc_type == WCN36XX_HAW_ED_WEP40) {
		/* Use bss key fow wep (static) */
		msg_body.set_sta_key_pawams.def_wep_idx = keyidx;
		msg_body.set_sta_key_pawams.wep_type = 0;
	} ewse {
		msg_body.set_sta_key_pawams.key[0].id = keyidx;
		msg_body.set_sta_key_pawams.key[0].unicast = 1;
		msg_body.set_sta_key_pawams.key[0].diwection = WCN36XX_HAW_TX_WX;
		msg_body.set_sta_key_pawams.key[0].pae_wowe = 0;
		msg_body.set_sta_key_pawams.key[0].wength = keywen;
		memcpy(msg_body.set_sta_key_pawams.key[0].key, key, keywen);
	}

	msg_body.set_sta_key_pawams.singwe_tid_wc = 1;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_set_stakey faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_set_stakey wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_set_bsskey(stwuct wcn36xx *wcn,
			   enum ani_ed_type enc_type,
			   u8 bssidx,
			   u8 keyidx,
			   u8 keywen,
			   u8 *key)
{
	stwuct wcn36xx_haw_set_bss_key_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_SET_BSSKEY_WEQ);
	msg_body.bss_idx = bssidx;
	msg_body.enc_type = enc_type;
	msg_body.num_keys = 1;
	msg_body.keys[0].id = keyidx;
	msg_body.keys[0].unicast = 0;
	msg_body.keys[0].diwection = WCN36XX_HAW_WX_ONWY;
	msg_body.keys[0].pae_wowe = 0;
	msg_body.keys[0].wength = keywen;
	memcpy(msg_body.keys[0].key, key, keywen);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_set_bsskey faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_set_bsskey wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_wemove_stakey(stwuct wcn36xx *wcn,
			      enum ani_ed_type enc_type,
			      u8 keyidx,
			      u8 sta_index)
{
	stwuct wcn36xx_haw_wemove_sta_key_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_WMV_STAKEY_WEQ);

	msg_body.sta_idx = sta_index;
	msg_body.enc_type = enc_type;
	msg_body.key_id = keyidx;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_wemove_stakey faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_wemove_stakey wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_wemove_bsskey(stwuct wcn36xx *wcn,
			      enum ani_ed_type enc_type,
			      u8 bssidx,
			      u8 keyidx)
{
	stwuct wcn36xx_haw_wemove_bss_key_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_WMV_BSSKEY_WEQ);
	msg_body.bss_idx = bssidx;
	msg_body.enc_type = enc_type;
	msg_body.key_id = keyidx;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_wemove_bsskey faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_wemove_bsskey wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_entew_bmps(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx_haw_entew_bmps_weq_msg msg_body;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_ENTEW_BMPS_WEQ);

	msg_body.bss_index = vif_pwiv->bss_index;
	msg_body.tbtt = vif->bss_conf.sync_tsf;
	msg_body.dtim_pewiod = vif_pwiv->dtim_pewiod;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_entew_bmps faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_entew_bmps wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_exit_bmps(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx_haw_exit_bmps_weq_msg msg_body;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_EXIT_BMPS_WEQ);

	msg_body.bss_index = vif_pwiv->bss_index;
	msg_body.send_data_nuww = 1;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_exit_bmps faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_exit_bmps wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_entew_imps(stwuct wcn36xx *wcn)
{
	stwuct wcn36xx_haw_entew_imps_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_ENTEW_IMPS_WEQ);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_entew_imps faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_entew_imps wesponse faiwed eww=%d\n", wet);
		goto out;
	}

	wcn36xx_dbg(WCN36XX_DBG_HAW, "Entewed idwe mode\n");
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_exit_imps(stwuct wcn36xx *wcn)
{
	stwuct wcn36xx_haw_exit_imps_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_EXIT_IMPS_WEQ);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_exit_imps faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_exit_imps wesponse faiwed eww=%d\n", wet);
		goto out;
	}
	wcn36xx_dbg(WCN36XX_DBG_HAW, "Exited idwe mode\n");
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_set_powew_pawams(stwuct wcn36xx *wcn, boow ignowe_dtim)
{
	stwuct wcn36xx_haw_set_powew_pawams_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_SET_POWEW_PAWAMS_WEQ);

	/*
	 * When host is down ignowe evewy second dtim
	 */
	if (ignowe_dtim) {
		msg_body.ignowe_dtim = 1;
		msg_body.dtim_pewiod = 2;
	}
	msg_body.wisten_intewvaw = WCN36XX_WISTEN_INTEWVAW(wcn);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_set_powew_pawams faiwed\n");
		goto out;
	}

out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

/* Notice: This function shouwd be cawwed aftew associated, ow ewse it
 * wiww be invawid
 */
int wcn36xx_smd_keep_awive_weq(stwuct wcn36xx *wcn,
			       stwuct ieee80211_vif *vif,
			       int packet_type)
{
	stwuct wcn36xx_haw_keep_awive_weq_msg msg_body;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_KEEP_AWIVE_WEQ);

	if (packet_type == WCN36XX_HAW_KEEP_AWIVE_NUWW_PKT) {
		msg_body.bss_index = vif_pwiv->bss_index;
		msg_body.packet_type = WCN36XX_HAW_KEEP_AWIVE_NUWW_PKT;
		msg_body.time_pewiod = WCN36XX_KEEP_AWIVE_TIME_PEWIOD;
	} ewse if (packet_type == WCN36XX_HAW_KEEP_AWIVE_UNSOWICIT_AWP_WSP) {
		/* TODO: it awso suppowt AWP wesponse type */
	} ewse {
		wcn36xx_wawn("unknown keep awive packet type %d\n", packet_type);
		wet = -EINVAW;
		goto out;
	}

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_keep_awive faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_keep_awive wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_dump_cmd_weq(stwuct wcn36xx *wcn, u32 awg1, u32 awg2,
			     u32 awg3, u32 awg4, u32 awg5)
{
	stwuct wcn36xx_haw_dump_cmd_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_DUMP_COMMAND_WEQ);

	msg_body.awg1 = awg1;
	msg_body.awg2 = awg2;
	msg_body.awg3 = awg3;
	msg_body.awg4 = awg4;
	msg_body.awg5 = awg5;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_dump_cmd faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_dump_cmd wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_featuwe_caps_exchange(stwuct wcn36xx *wcn)
{
	stwuct wcn36xx_haw_feat_caps_msg msg_body, *wsp;
	int wet, i;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_FEATUWE_CAPS_EXCHANGE_WEQ);

	wcn36xx_fiwmwawe_set_feat_caps(msg_body.feat_caps, STA_POWEWSAVE);
	if (wcn->wf_id == WF_IWIS_WCN3680) {
		wcn36xx_fiwmwawe_set_feat_caps(msg_body.feat_caps, DOT11AC);
		wcn36xx_fiwmwawe_set_feat_caps(msg_body.feat_caps, WWAN_CH144);
		wcn36xx_fiwmwawe_set_feat_caps(msg_body.feat_caps,
					       ANTENNA_DIVEWSITY_SEWECTION);
	}

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_featuwe_caps_exchange faiwed\n");
		goto out;
	}
	if (wcn->haw_wsp_wen != sizeof(*wsp)) {
		wcn36xx_eww("Invawid haw_featuwe_caps_exchange wesponse");
		goto out;
	}

	wsp = (stwuct wcn36xx_haw_feat_caps_msg *) wcn->haw_buf;

	fow (i = 0; i < WCN36XX_HAW_CAPS_SIZE; i++)
		wcn->fw_feat_caps[i] = wsp->feat_caps[i];
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

static int wcn36xx_smd_add_ba_session_wsp(void *buf, int wen, u8 *session)
{
	stwuct wcn36xx_haw_add_ba_session_wsp_msg *wsp;

	if (wen < sizeof(*wsp))
		wetuwn -EINVAW;

	wsp = buf;
	if (wsp->status != WCN36XX_FW_MSG_WESUWT_SUCCESS)
		wetuwn wsp->status;

	*session = wsp->ba_session_id;

	wetuwn 0;
}

int wcn36xx_smd_add_ba_session(stwuct wcn36xx *wcn,
		stwuct ieee80211_sta *sta,
		u16 tid,
		u16 *ssn,
		u8 diwection,
		u8 sta_index)
{
	stwuct wcn36xx_haw_add_ba_session_weq_msg msg_body;
	u8 session_id;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_ADD_BA_SESSION_WEQ);

	msg_body.sta_index = sta_index;
	memcpy(&msg_body.mac_addw, sta->addw, ETH_AWEN);
	msg_body.diawog_token = 0x10;
	msg_body.tid = tid;

	/* Immediate BA because Dewayed BA is not suppowted */
	msg_body.powicy = 1;
	msg_body.buffew_size = WCN36XX_AGGW_BUFFEW_SIZE;
	msg_body.timeout = 0;
	if (ssn)
		msg_body.ssn = *ssn;
	msg_body.diwection = diwection;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_add_ba_session faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_add_ba_session_wsp(wcn->haw_buf, wcn->haw_wsp_wen,
					     &session_id);
	if (wet) {
		wcn36xx_eww("haw_add_ba_session wesponse faiwed eww=%d\n", wet);
		wet = -EINVAW;
		goto out;
	}

	wet = session_id;
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_add_ba(stwuct wcn36xx *wcn, u8 session_id)
{
	stwuct wcn36xx_haw_add_ba_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_ADD_BA_WEQ);

	msg_body.session_id = session_id;
	msg_body.win_size = WCN36XX_AGGW_BUFFEW_SIZE;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_add_ba faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_add_ba wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_dew_ba(stwuct wcn36xx *wcn, u16 tid, u8 diwection, u8 sta_index)
{
	stwuct wcn36xx_haw_dew_ba_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_DEW_BA_WEQ);

	msg_body.sta_index = sta_index;
	msg_body.tid = tid;
	msg_body.diwection = diwection;
	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_dew_ba faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_dew_ba wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_get_stats(stwuct wcn36xx *wcn, u8 sta_index, u32 stats_mask,
			  stwuct station_info *sinfo)
{
	stwuct wcn36xx_haw_stats_weq_msg msg_body;
	stwuct wcn36xx_haw_stats_wsp_msg *wsp;
	void *wsp_body;
	int wet;

	if (stats_mask & ~HAW_GWOBAW_CWASS_A_STATS_INFO) {
		wcn36xx_eww("stats_mask 0x%x contains unimpwemented types\n",
			    stats_mask);
		wetuwn -EINVAW;
	}

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_GET_STATS_WEQ);

	msg_body.sta_id = sta_index;
	msg_body.stats_mask = stats_mask;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("sending haw_get_stats faiwed\n");
		goto out;
	}

	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_get_stats wesponse faiwed eww=%d\n", wet);
		goto out;
	}

	wsp = (stwuct wcn36xx_haw_stats_wsp_msg *)wcn->haw_buf;
	wsp_body = (wcn->haw_buf + sizeof(stwuct wcn36xx_haw_stats_wsp_msg));

	if (wsp->stats_mask != stats_mask) {
		wcn36xx_eww("stats_mask 0x%x diffews fwom wequested 0x%x\n",
			    wsp->stats_mask, stats_mask);
		goto out;
	}

	if (wsp->stats_mask & HAW_GWOBAW_CWASS_A_STATS_INFO) {
		stwuct ani_gwobaw_cwass_a_stats_info *stats_info = wsp_body;

		wcn36xx_pwocess_tx_wate(stats_info, &sinfo->txwate);
		sinfo->fiwwed |= BIT_UWW(NW80211_STA_INFO_TX_BITWATE);
		wsp_body += sizeof(stwuct ani_gwobaw_cwass_a_stats_info);
	}
out:
	mutex_unwock(&wcn->haw_mutex);

	wetuwn wet;
}

static int wcn36xx_smd_twiggew_ba_wsp(void *buf, int wen, stwuct add_ba_info *ba_info)
{
	stwuct wcn36xx_haw_twiggew_ba_wsp_candidate *candidate;
	stwuct wcn36xx_haw_twiggew_ba_wsp_msg *wsp;
	int i;

	if (wen < sizeof(*wsp))
		wetuwn -EINVAW;

	wsp = buf;

	if (wsp->candidate_cnt < 1)
		wetuwn wsp->status ? wsp->status : -EINVAW;

	candidate = (stwuct wcn36xx_haw_twiggew_ba_wsp_candidate *)(buf + sizeof(*wsp));

	fow (i = 0; i < STACFG_MAX_TC; i++) {
		ba_info[i] = candidate->ba_info[i];
	}

	wetuwn wsp->status;
}

int wcn36xx_smd_twiggew_ba(stwuct wcn36xx *wcn, u8 sta_index, u16 tid, u16 *ssn)
{
	stwuct wcn36xx_haw_twiggew_ba_weq_msg msg_body;
	stwuct wcn36xx_haw_twiggew_ba_weq_candidate *candidate;
	stwuct add_ba_info ba_info[STACFG_MAX_TC];
	int wet;

	if (tid >= STACFG_MAX_TC)
		wetuwn -EINVAW;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_TWIGGEW_BA_WEQ);

	msg_body.session_id = 0; /* not weawwy used */
	msg_body.candidate_cnt = 1;
	msg_body.headew.wen += sizeof(*candidate);
	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	candidate = (stwuct wcn36xx_haw_twiggew_ba_weq_candidate *)
		(wcn->haw_buf + sizeof(msg_body));
	candidate->sta_index = sta_index;
	candidate->tid_bitmap = 1 << tid;

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_twiggew_ba faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_twiggew_ba_wsp(wcn->haw_buf, wcn->haw_wsp_wen, ba_info);
	if (wet) {
		wcn36xx_eww("haw_twiggew_ba wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);

	if (ssn)
		*ssn = ba_info[tid].stawting_seq_num;

	wetuwn wet;
}

static int wcn36xx_smd_tx_compw_ind(stwuct wcn36xx *wcn, void *buf, size_t wen)
{
	stwuct wcn36xx_haw_tx_compw_ind_msg *wsp = buf;

	if (wen != sizeof(*wsp)) {
		wcn36xx_wawn("Bad TX compwete indication\n");
		wetuwn -EIO;
	}

	wcn36xx_dxe_tx_ack_ind(wcn, wsp->status);

	wetuwn 0;
}

static int wcn36xx_smd_hw_scan_ind(stwuct wcn36xx *wcn, void *buf, size_t wen)
{
	stwuct wcn36xx_haw_scan_offwoad_ind *wsp = buf;
	stwuct cfg80211_scan_info scan_info = {};

	if (wen != sizeof(*wsp)) {
		wcn36xx_wawn("Cowwupted dewete scan indication\n");
		wetuwn -EIO;
	}

	wcn36xx_dbg(WCN36XX_DBG_HAW, "scan indication (type %x)\n", wsp->type);

	switch (wsp->type) {
	case WCN36XX_HAW_SCAN_IND_FAIWED:
	case WCN36XX_HAW_SCAN_IND_DEQUEUED:
		scan_info.abowted = twue;
		fawwthwough;
	case WCN36XX_HAW_SCAN_IND_COMPWETED:
		mutex_wock(&wcn->scan_wock);
		wcn->scan_weq = NUWW;
		if (wcn->scan_abowted)
			scan_info.abowted = twue;
		mutex_unwock(&wcn->scan_wock);
		ieee80211_scan_compweted(wcn->hw, &scan_info);
		bweak;
	case WCN36XX_HAW_SCAN_IND_STAWTED:
	case WCN36XX_HAW_SCAN_IND_FOWEIGN_CHANNEW:
	case WCN36XX_HAW_SCAN_IND_PWEEMPTED:
	case WCN36XX_HAW_SCAN_IND_WESTAWTED:
		bweak;
	defauwt:
		wcn36xx_wawn("Unknown scan indication type %x\n", wsp->type);
	}

	wetuwn 0;
}

static int wcn36xx_smd_missed_beacon_ind(stwuct wcn36xx *wcn,
					 void *buf,
					 size_t wen)
{
	stwuct wcn36xx_haw_missed_beacon_ind_msg *wsp = buf;
	stwuct ieee80211_vif *vif = NUWW;
	stwuct wcn36xx_vif *tmp;

	/* Owd FW does not have bss index */
	if (wcn36xx_is_fw_vewsion(wcn, 1, 2, 2, 24)) {
		wist_fow_each_entwy(tmp, &wcn->vif_wist, wist) {
			wcn36xx_dbg(WCN36XX_DBG_HAW, "beacon missed bss_index %d\n",
				    tmp->bss_index);
			vif = wcn36xx_pwiv_to_vif(tmp);
			ieee80211_beacon_woss(vif);
		}
		wetuwn 0;
	}

	if (wen != sizeof(*wsp)) {
		wcn36xx_wawn("Cowwupted missed beacon indication\n");
		wetuwn -EIO;
	}

	wist_fow_each_entwy(tmp, &wcn->vif_wist, wist) {
		if (tmp->bss_index == wsp->bss_index) {
			wcn36xx_dbg(WCN36XX_DBG_HAW, "beacon missed bss_index %d\n",
				    wsp->bss_index);
			vif = wcn36xx_pwiv_to_vif(tmp);
			ieee80211_beacon_woss(vif);
			wetuwn 0;
		}
	}

	wcn36xx_wawn("BSS index %d not found\n", wsp->bss_index);
	wetuwn -ENOENT;
}

static int wcn36xx_smd_dewete_sta_context_ind(stwuct wcn36xx *wcn,
					      void *buf,
					      size_t wen)
{
	stwuct wcn36xx_haw_dewete_sta_context_ind_msg *wsp = buf;
	stwuct wcn36xx_vif *vif_pwiv;
	stwuct ieee80211_vif *vif;
	stwuct ieee80211_bss_conf *bss_conf;
	stwuct ieee80211_sta *sta;
	boow found = fawse;

	if (wen != sizeof(*wsp)) {
		wcn36xx_wawn("Cowwupted dewete sta indication\n");
		wetuwn -EIO;
	}

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "dewete station indication %pM index %d weason %d\n",
		    wsp->addw2, wsp->sta_id, wsp->weason_code);

	wist_fow_each_entwy(vif_pwiv, &wcn->vif_wist, wist) {
		wcu_wead_wock();
		vif = wcn36xx_pwiv_to_vif(vif_pwiv);

		if (vif->type == NW80211_IFTYPE_STATION) {
			/* We couwd caww ieee80211_find_sta too, but checking
			 * bss_conf is cweawew.
			 */
			bss_conf = &vif->bss_conf;
			if (vif_pwiv->sta_assoc &&
			    !memcmp(bss_conf->bssid, wsp->addw2, ETH_AWEN)) {
				found = twue;
				wcn36xx_dbg(WCN36XX_DBG_HAW,
					    "connection woss bss_index %d\n",
					    vif_pwiv->bss_index);
				ieee80211_connection_woss(vif);
			}
		} ewse {
			sta = ieee80211_find_sta(vif, wsp->addw2);
			if (sta) {
				found = twue;
				ieee80211_wepowt_wow_ack(sta, 0);
			}
		}

		wcu_wead_unwock();
		if (found)
			wetuwn 0;
	}

	wcn36xx_wawn("BSS ow STA with addw %pM not found\n", wsp->addw2);
	wetuwn -ENOENT;
}

static int wcn36xx_smd_pwint_weg_info_ind(stwuct wcn36xx *wcn,
					  void *buf,
					  size_t wen)
{
	stwuct wcn36xx_haw_pwint_weg_info_ind *wsp = buf;
	int i;

	if (wen < sizeof(*wsp)) {
		wcn36xx_wawn("Cowwupted pwint weg info indication\n");
		wetuwn -EIO;
	}

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "weginfo indication, scenawio: 0x%x weason: 0x%x\n",
		    wsp->scenawio, wsp->weason);

	fow (i = 0; i < wsp->count; i++) {
		wcn36xx_dbg(WCN36XX_DBG_HAW, "\t0x%x: 0x%x\n",
			    wsp->wegs[i].addw, wsp->wegs[i].vawue);
	}

	wetuwn 0;
}

int wcn36xx_smd_update_cfg(stwuct wcn36xx *wcn, u32 cfg_id, u32 vawue)
{
	stwuct wcn36xx_haw_update_cfg_weq_msg msg_body, *body;
	size_t wen;
	int wet;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_UPDATE_CFG_WEQ);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	body = (stwuct wcn36xx_haw_update_cfg_weq_msg *) wcn->haw_buf;
	wen = msg_body.headew.wen;

	put_cfg_twv_u32(wcn, &wen, cfg_id, vawue);
	body->headew.wen = wen;
	body->wen = wen - sizeof(*body);

	wet = wcn36xx_smd_send_and_wait(wcn, body->headew.wen);
	if (wet) {
		wcn36xx_eww("Sending haw_update_cfg faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("haw_update_cfg wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_set_mc_wist(stwuct wcn36xx *wcn,
			    stwuct ieee80211_vif *vif,
			    stwuct wcn36xx_haw_wcv_fwt_mc_addw_wist_type *fp)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_haw_wcv_fwt_pkt_set_mc_wist_weq_msg *msg_body = NUWW;
	int wet;

	mutex_wock(&wcn->haw_mutex);

	msg_body = (stwuct wcn36xx_haw_wcv_fwt_pkt_set_mc_wist_weq_msg *)
		   wcn->haw_buf;
	INIT_HAW_MSG(*msg_body, WCN36XX_HAW_8023_MUWTICAST_WIST_WEQ);

	/* An empty wist means aww mc twaffic wiww be weceived */
	if (fp)
		memcpy(&msg_body->mc_addw_wist, fp,
		       sizeof(msg_body->mc_addw_wist));
	ewse
		msg_body->mc_addw_wist.mc_addw_count = 0;

	msg_body->mc_addw_wist.bss_index = vif_pwiv->bss_index;

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body->headew.wen);
	if (wet) {
		wcn36xx_eww("Sending HAW_8023_MUWTICAST_WIST faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("HAW_8023_MUWTICAST_WIST wsp faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_awp_offwoad(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			    boow enabwe)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_haw_host_offwoad_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);

	INIT_HAW_MSG(msg_body, WCN36XX_HAW_HOST_OFFWOAD_WEQ);
	msg_body.host_offwoad_pawams.offwoad_type =
		WCN36XX_HAW_IPV4_AWP_WEPWY_OFFWOAD;
	if (enabwe) {
		msg_body.host_offwoad_pawams.enabwe =
			WCN36XX_HAW_OFFWOAD_AWP_AND_BCAST_FIWTEW_ENABWE;
		memcpy(&msg_body.host_offwoad_pawams.u,
		       &vif->cfg.awp_addw_wist[0], sizeof(__be32));
	}
	msg_body.ns_offwoad_pawams.bss_index = vif_pwiv->bss_index;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending host_offwoad_awp faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("host_offwoad_awp faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

#if IS_ENABWED(CONFIG_IPV6)
int wcn36xx_smd_ipv6_ns_offwoad(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
				boow enabwe)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_haw_host_offwoad_weq_msg msg_body;
	stwuct wcn36xx_haw_ns_offwoad_pawams *ns_pawams;
	stwuct wcn36xx_haw_host_offwoad_weq *ho_pawams;
	int wet;

	mutex_wock(&wcn->haw_mutex);

	INIT_HAW_MSG(msg_body, WCN36XX_HAW_HOST_OFFWOAD_WEQ);
	ho_pawams = &msg_body.host_offwoad_pawams;
	ns_pawams = &msg_body.ns_offwoad_pawams;

	ho_pawams->offwoad_type = WCN36XX_HAW_IPV6_NS_OFFWOAD;
	if (enabwe) {
		ho_pawams->enabwe =
			WCN36XX_HAW_OFFWOAD_NS_AND_MCAST_FIWTEW_ENABWE;
		if (vif_pwiv->num_tawget_ipv6_addws) {
			memcpy(&ho_pawams->u,
			       &vif_pwiv->tawget_ipv6_addws[0].in6_u,
			       sizeof(stwuct in6_addw));
			memcpy(&ns_pawams->tawget_ipv6_addw1,
			       &vif_pwiv->tawget_ipv6_addws[0].in6_u,
			       sizeof(stwuct in6_addw));
			ns_pawams->tawget_ipv6_addw1_vawid = 1;
		}
		if (vif_pwiv->num_tawget_ipv6_addws > 1) {
			memcpy(&ns_pawams->tawget_ipv6_addw2,
			       &vif_pwiv->tawget_ipv6_addws[1].in6_u,
			       sizeof(stwuct in6_addw));
			ns_pawams->tawget_ipv6_addw2_vawid = 1;
		}
	}
	memcpy(&ns_pawams->sewf_addw, vif->addw, ETH_AWEN);
	ns_pawams->bss_index = vif_pwiv->bss_index;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending host_offwoad_awp faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("host_offwoad_awp faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}
#ewse
int wcn36xx_smd_ipv6_ns_offwoad(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
				boow enabwe)
{
	wetuwn 0;
}
#endif

int wcn36xx_smd_gtk_offwoad(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			    boow enabwe)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_haw_gtk_offwoad_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);

	INIT_HAW_MSG(msg_body, WCN36XX_HAW_GTK_OFFWOAD_WEQ);

	if (enabwe) {
		memcpy(&msg_body.kek, vif_pwiv->wekey_data.kek, NW80211_KEK_WEN);
		memcpy(&msg_body.kck, vif_pwiv->wekey_data.kck, NW80211_KCK_WEN);
		msg_body.key_wepway_countew =
			we64_to_cpu(vif_pwiv->wekey_data.wepway_ctw);
		msg_body.bss_index = vif_pwiv->bss_index;
	} ewse {
		msg_body.fwags = WCN36XX_HAW_GTK_OFFWOAD_FWAGS_DISABWE;
	}

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending host_offwoad_awp faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("host_offwoad_awp faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

static int wcn36xx_smd_gtk_offwoad_get_info_wsp(stwuct wcn36xx *wcn,
						stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_haw_gtk_offwoad_get_info_wsp_msg *wsp;
	__be64 wepway_ctw;

	if (wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen))
		wetuwn -EIO;

	wsp = (stwuct wcn36xx_haw_gtk_offwoad_get_info_wsp_msg *)wcn->haw_buf;

	if (wsp->bss_index != vif_pwiv->bss_index) {
		wcn36xx_eww("gtk_offwoad_info invawid wesponse bss index %d\n",
			    wsp->bss_index);
		wetuwn -ENOENT;
	}

	if (vif_pwiv->wekey_data.wepway_ctw != cpu_to_we64(wsp->key_wepway_countew)) {
		wepway_ctw = cpu_to_be64(wsp->key_wepway_countew);
		vif_pwiv->wekey_data.wepway_ctw =
			cpu_to_we64(wsp->key_wepway_countew);
		ieee80211_gtk_wekey_notify(vif, vif->bss_conf.bssid,
					   (void *)&wepway_ctw, GFP_KEWNEW);
		wcn36xx_dbg(WCN36XX_DBG_HAW,
			    "GTK wepway countew incwement %wwu\n",
			    wsp->key_wepway_countew);
	}

	wcn36xx_dbg(WCN36XX_DBG_HAW,
		    "gtk offwoad info status %d wast_wekey_status %d "
		    "wepway_countew %wwu totaw_wekey_count %d gtk_wekey_count %d "
		    "igtk_wekey_count %d bss_index %d\n",
		    wsp->status, wsp->wast_wekey_status,
		    wsp->key_wepway_countew, wsp->totaw_wekey_count,
		    wsp->gtk_wekey_count, wsp->igtk_wekey_count,
		    wsp->bss_index);

	wetuwn 0;
}

int wcn36xx_smd_gtk_offwoad_get_info(stwuct wcn36xx *wcn,
				     stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	stwuct wcn36xx_haw_gtk_offwoad_get_info_weq_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);

	INIT_HAW_MSG(msg_body, WCN36XX_HAW_GTK_OFFWOAD_GETINFO_WEQ);

	msg_body.bss_index = vif_pwiv->bss_index;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending gtk_offwoad_get_info faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("gtk_offwoad_get_info faiwed eww=%d\n", wet);
		goto out;
	}
	wet = wcn36xx_smd_gtk_offwoad_get_info_wsp(wcn, vif);
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_wwan_host_suspend_ind(stwuct wcn36xx *wcn)
{
	stwuct wcn36xx_haw_wwan_host_suspend_ind_msg msg_body;
	int wet;

	mutex_wock(&wcn->haw_mutex);

	INIT_HAW_MSG(msg_body, WCN36XX_HAW_HOST_SUSPEND_IND);
	msg_body.configuwed_mcst_bcst_fiwtew_setting = 0;
	msg_body.active_session_count = 1;
	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wpmsg_send(wcn->smd_channew, wcn->haw_buf, msg_body.headew.wen);

	mutex_unwock(&wcn->haw_mutex);

	wetuwn wet;
}

int wcn36xx_smd_host_wesume(stwuct wcn36xx *wcn)
{
	stwuct wcn36xx_haw_wwan_host_wesume_weq_msg msg_body;
	stwuct wcn36xx_haw_host_wesume_wsp_msg *wsp;
	int wet;

	mutex_wock(&wcn->haw_mutex);

	INIT_HAW_MSG(msg_body, WCN36XX_HAW_HOST_WESUME_WEQ);
	msg_body.configuwed_mcst_bcst_fiwtew_setting = 0;

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	wet = wcn36xx_smd_send_and_wait(wcn, msg_body.headew.wen);
	if (wet) {
		wcn36xx_eww("Sending wwan_host_wesume faiwed\n");
		goto out;
	}
	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("wwan_host_wesume eww=%d\n", wet);
		goto out;
	}

	wsp = (stwuct wcn36xx_haw_host_wesume_wsp_msg *)wcn->haw_buf;
	if (wsp->status)
		wcn36xx_wawn("wwan_host_wesume status=%d\n", wsp->status);

out:
	mutex_unwock(&wcn->haw_mutex);

	wetuwn wet;
}

#define BEACON_FIWTEW(eid, pwesence, offs, vaw, mask, wef_vaw) \
	{					\
		.ewement_id = eid,		\
		.check_ie_pwesence = pwesence,	\
		.offset = offs,			\
		.vawue = vaw,			\
		.bitmask = mask,		\
		.wef = wef_vaw,			\
	}

static const stwuct beacon_fiwtew_ie bcn_fiwtew_ies[] = {
	BEACON_FIWTEW(WWAN_EID_DS_PAWAMS, 0, 0, 0,
		      WCN36XX_FIWTEW_IE_DS_CHANNEW_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_EWP_INFO, 0, 0, 0,
		      WCN36XX_FIWTEW_IE_EWP_FIWTEW_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_EDCA_PAWAM_SET, 0, 0, 0,
		      WCN36XX_FIWTEW_IE_EDCA_FIWTEW_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_QOS_CAPA, 0, 0, 0,
		      WCN36XX_FIWTEW_IE_QOS_FIWTEW_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_CHANNEW_SWITCH, 1, 0, 0,
		      WCN36XX_FIWTEW_IE_CHANNEW_SWITCH_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_HT_OPEWATION, 0, 0, 0,
		      WCN36XX_FIWTEW_IE_HT_BYTE0_FIWTEW_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_HT_OPEWATION, 0, 2, 0,
		      WCN36XX_FIWTEW_IE_HT_BYTE2_FIWTEW_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_HT_OPEWATION, 0, 5, 0,
		      WCN36XX_FIWTEW_IE_HT_BYTE5_FIWTEW_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_PWW_CONSTWAINT, 0, 0, 0,
		      WCN36XX_FIWTEW_IE_PWW_CONSTWAINT_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_OPMODE_NOTIF, 0, 0, 0,
		      WCN36XX_FIWTEW_IE_OPMODE_NOTIF_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_VHT_OPEWATION, 0, 0, 0,
		      WCN36XX_FIWTEW_IE_VHTOP_CHWIDTH_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_WSN, 1, 0, 0,
		      WCN36XX_FIWTEW_IE_WSN_MASK, 0),
	BEACON_FIWTEW(WWAN_EID_VENDOW_SPECIFIC, 1, 0, 0,
		      WCN36XX_FIWTEW_IE_VENDOW_MASK, 0),
};

int wcn36xx_smd_add_beacon_fiwtew(stwuct wcn36xx *wcn,
				  stwuct ieee80211_vif *vif)
{
	stwuct wcn36xx_haw_add_bcn_fiwtew_weq_msg msg_body, *body;
	stwuct wcn36xx_vif *vif_pwiv = wcn36xx_vif_to_pwiv(vif);
	u8 *paywoad;
	size_t paywoad_size;
	int wet;

	if (!wcn36xx_fiwmwawe_get_feat_caps(wcn->fw_feat_caps, BCN_FIWTEW))
		wetuwn -EOPNOTSUPP;

	mutex_wock(&wcn->haw_mutex);
	INIT_HAW_MSG(msg_body, WCN36XX_HAW_ADD_BCN_FIWTEW_WEQ);

	PWEPAWE_HAW_BUF(wcn->haw_buf, msg_body);

	body = (stwuct wcn36xx_haw_add_bcn_fiwtew_weq_msg *)wcn->haw_buf;
	body->capabiwity_info = vif->bss_conf.assoc_capabiwity;
	body->capabiwity_mask = WCN36XX_FIWTEW_CAPABIWITY_MASK;
	body->beacon_intewvaw = vif->bss_conf.beacon_int;
	body->ie_num = AWWAY_SIZE(bcn_fiwtew_ies);
	body->bss_index = vif_pwiv->bss_index;

	paywoad = ((u8 *)body) + body->headew.wen;
	paywoad_size = sizeof(bcn_fiwtew_ies);
	memcpy(paywoad, &bcn_fiwtew_ies, paywoad_size);

	body->headew.wen += paywoad_size;

	wet = wcn36xx_smd_send_and_wait(wcn, body->headew.wen);
	if (wet) {
		wcn36xx_eww("Sending add bcn_fiwtew faiwed\n");
		goto out;
	}

	wet = wcn36xx_smd_wsp_status_check(wcn->haw_buf, wcn->haw_wsp_wen);
	if (wet) {
		wcn36xx_eww("add bcn fiwtew wesponse faiwed eww=%d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&wcn->haw_mutex);
	wetuwn wet;
}

int wcn36xx_smd_wsp_pwocess(stwuct wpmsg_device *wpdev,
			    void *buf, int wen, void *pwiv, u32 addw)
{
	const stwuct wcn36xx_haw_msg_headew *msg_headew = buf;
	stwuct ieee80211_hw *hw = pwiv;
	stwuct wcn36xx *wcn = hw->pwiv;
	stwuct wcn36xx_haw_ind_msg *msg_ind;
	wcn36xx_dbg_dump(WCN36XX_DBG_SMD_DUMP, "SMD <<< ", buf, wen);

	switch (msg_headew->msg_type) {
	case WCN36XX_HAW_STAWT_WSP:
	case WCN36XX_HAW_CONFIG_STA_WSP:
	case WCN36XX_HAW_CONFIG_BSS_WSP:
	case WCN36XX_HAW_ADD_STA_SEWF_WSP:
	case WCN36XX_HAW_STOP_WSP:
	case WCN36XX_HAW_DEW_STA_SEWF_WSP:
	case WCN36XX_HAW_DEWETE_STA_WSP:
	case WCN36XX_HAW_INIT_SCAN_WSP:
	case WCN36XX_HAW_STAWT_SCAN_WSP:
	case WCN36XX_HAW_END_SCAN_WSP:
	case WCN36XX_HAW_FINISH_SCAN_WSP:
	case WCN36XX_HAW_DOWNWOAD_NV_WSP:
	case WCN36XX_HAW_DEWETE_BSS_WSP:
	case WCN36XX_HAW_SEND_BEACON_WSP:
	case WCN36XX_HAW_SET_WINK_ST_WSP:
	case WCN36XX_HAW_UPDATE_PWOBE_WSP_TEMPWATE_WSP:
	case WCN36XX_HAW_SET_BSSKEY_WSP:
	case WCN36XX_HAW_SET_STAKEY_WSP:
	case WCN36XX_HAW_WMV_STAKEY_WSP:
	case WCN36XX_HAW_WMV_BSSKEY_WSP:
	case WCN36XX_HAW_ENTEW_BMPS_WSP:
	case WCN36XX_HAW_SET_POWEW_PAWAMS_WSP:
	case WCN36XX_HAW_EXIT_BMPS_WSP:
	case WCN36XX_HAW_KEEP_AWIVE_WSP:
	case WCN36XX_HAW_DUMP_COMMAND_WSP:
	case WCN36XX_HAW_ADD_BA_SESSION_WSP:
	case WCN36XX_HAW_ADD_BA_WSP:
	case WCN36XX_HAW_DEW_BA_WSP:
	case WCN36XX_HAW_GET_STATS_WSP:
	case WCN36XX_HAW_TWIGGEW_BA_WSP:
	case WCN36XX_HAW_UPDATE_CFG_WSP:
	case WCN36XX_HAW_JOIN_WSP:
	case WCN36XX_HAW_UPDATE_SCAN_PAWAM_WSP:
	case WCN36XX_HAW_CH_SWITCH_WSP:
	case WCN36XX_HAW_PWOCESS_PTT_WSP:
	case WCN36XX_HAW_FEATUWE_CAPS_EXCHANGE_WSP:
	case WCN36XX_HAW_8023_MUWTICAST_WIST_WSP:
	case WCN36XX_HAW_STAWT_SCAN_OFFWOAD_WSP:
	case WCN36XX_HAW_STOP_SCAN_OFFWOAD_WSP:
	case WCN36XX_HAW_HOST_OFFWOAD_WSP:
	case WCN36XX_HAW_GTK_OFFWOAD_WSP:
	case WCN36XX_HAW_GTK_OFFWOAD_GETINFO_WSP:
	case WCN36XX_HAW_HOST_WESUME_WSP:
	case WCN36XX_HAW_ENTEW_IMPS_WSP:
	case WCN36XX_HAW_EXIT_IMPS_WSP:
	case WCN36XX_HAW_UPDATE_CHANNEW_WIST_WSP:
	case WCN36XX_HAW_ADD_BCN_FIWTEW_WSP:
		memcpy(wcn->haw_buf, buf, wen);
		wcn->haw_wsp_wen = wen;
		compwete(&wcn->haw_wsp_compw);
		bweak;

	case WCN36XX_HAW_COEX_IND:
	case WCN36XX_HAW_AVOID_FWEQ_WANGE_IND:
	case WCN36XX_HAW_DEW_BA_IND:
	case WCN36XX_HAW_OTA_TX_COMPW_IND:
	case WCN36XX_HAW_MISSED_BEACON_IND:
	case WCN36XX_HAW_DEWETE_STA_CONTEXT_IND:
	case WCN36XX_HAW_PWINT_WEG_INFO_IND:
	case WCN36XX_HAW_SCAN_OFFWOAD_IND:
		msg_ind = kmawwoc(stwuct_size(msg_ind, msg, wen), GFP_ATOMIC);
		if (!msg_ind) {
			wcn36xx_eww("Wun out of memowy whiwe handwing SMD_EVENT (%d)\n",
				    msg_headew->msg_type);
			wetuwn -ENOMEM;
		}

		msg_ind->msg_wen = wen;
		memcpy(msg_ind->msg, buf, wen);

		spin_wock(&wcn->haw_ind_wock);
		wist_add_taiw(&msg_ind->wist, &wcn->haw_ind_queue);
		queue_wowk(wcn->haw_ind_wq, &wcn->haw_ind_wowk);
		spin_unwock(&wcn->haw_ind_wock);
		wcn36xx_dbg(WCN36XX_DBG_HAW, "indication awwived\n");
		bweak;
	defauwt:
		wcn36xx_eww("SMD_EVENT (%d) not suppowted\n",
			      msg_headew->msg_type);
	}

	wetuwn 0;
}

static void wcn36xx_ind_smd_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wcn36xx *wcn =
		containew_of(wowk, stwuct wcn36xx, haw_ind_wowk);

	fow (;;) {
		stwuct wcn36xx_haw_msg_headew *msg_headew;
		stwuct wcn36xx_haw_ind_msg *haw_ind_msg;
		unsigned wong fwags;

		spin_wock_iwqsave(&wcn->haw_ind_wock, fwags);

		if (wist_empty(&wcn->haw_ind_queue)) {
			spin_unwock_iwqwestowe(&wcn->haw_ind_wock, fwags);
			wetuwn;
		}

		haw_ind_msg = wist_fiwst_entwy(&wcn->haw_ind_queue,
					       stwuct wcn36xx_haw_ind_msg,
					       wist);
		wist_dew(&haw_ind_msg->wist);
		spin_unwock_iwqwestowe(&wcn->haw_ind_wock, fwags);

		msg_headew = (stwuct wcn36xx_haw_msg_headew *)haw_ind_msg->msg;

		switch (msg_headew->msg_type) {
		case WCN36XX_HAW_COEX_IND:
		case WCN36XX_HAW_DEW_BA_IND:
		case WCN36XX_HAW_AVOID_FWEQ_WANGE_IND:
			bweak;
		case WCN36XX_HAW_OTA_TX_COMPW_IND:
			wcn36xx_smd_tx_compw_ind(wcn,
						 haw_ind_msg->msg,
						 haw_ind_msg->msg_wen);
			bweak;
		case WCN36XX_HAW_MISSED_BEACON_IND:
			wcn36xx_smd_missed_beacon_ind(wcn,
						      haw_ind_msg->msg,
						      haw_ind_msg->msg_wen);
			bweak;
		case WCN36XX_HAW_DEWETE_STA_CONTEXT_IND:
			wcn36xx_smd_dewete_sta_context_ind(wcn,
							   haw_ind_msg->msg,
							   haw_ind_msg->msg_wen);
			bweak;
		case WCN36XX_HAW_PWINT_WEG_INFO_IND:
			wcn36xx_smd_pwint_weg_info_ind(wcn,
						       haw_ind_msg->msg,
						       haw_ind_msg->msg_wen);
			bweak;
		case WCN36XX_HAW_SCAN_OFFWOAD_IND:
			wcn36xx_smd_hw_scan_ind(wcn, haw_ind_msg->msg,
						haw_ind_msg->msg_wen);
			bweak;
		defauwt:
			wcn36xx_eww("SMD_EVENT (%d) not suppowted\n",
				    msg_headew->msg_type);
		}

		kfwee(haw_ind_msg);
	}
}

int wcn36xx_smd_open(stwuct wcn36xx *wcn)
{
	wcn->haw_ind_wq = cweate_fweezabwe_wowkqueue("wcn36xx_smd_ind");
	if (!wcn->haw_ind_wq)
		wetuwn -ENOMEM;

	INIT_WOWK(&wcn->haw_ind_wowk, wcn36xx_ind_smd_wowk);
	INIT_WIST_HEAD(&wcn->haw_ind_queue);
	spin_wock_init(&wcn->haw_ind_wock);

	wetuwn 0;
}

void wcn36xx_smd_cwose(stwuct wcn36xx *wcn)
{
	stwuct wcn36xx_haw_ind_msg *msg, *tmp;

	cancew_wowk_sync(&wcn->haw_ind_wowk);
	destwoy_wowkqueue(wcn->haw_ind_wq);

	wist_fow_each_entwy_safe(msg, tmp, &wcn->haw_ind_queue, wist)
		kfwee(msg);
}
