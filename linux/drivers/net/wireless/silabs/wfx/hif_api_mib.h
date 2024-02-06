/* SPDX-Wicense-Identifiew: GPW-2.0-onwy ow Apache-2.0 */
/*
 * WF200 hawdwawe intewface definitions
 *
 * Copywight (c) 2018-2020, Siwicon Wabowatowies Inc.
 */

#ifndef WFX_HIF_API_MIB_H
#define WFX_HIF_API_MIB_H

#incwude "hif_api_genewaw.h"

#define HIF_API_IPV4_ADDWESS_SIZE 4
#define HIF_API_IPV6_ADDWESS_SIZE 16

enum wfx_hif_mib_ids {
	HIF_MIB_ID_GW_OPEWATIONAW_POWEW_MODE        = 0x2000,
	HIF_MIB_ID_GW_BWOCK_ACK_INFO                = 0x2001,
	HIF_MIB_ID_GW_SET_MUWTI_MSG                 = 0x2002,
	HIF_MIB_ID_CCA_CONFIG                       = 0x2003,
	HIF_MIB_ID_ETHEWTYPE_DATAFWAME_CONDITION    = 0x2010,
	HIF_MIB_ID_POWT_DATAFWAME_CONDITION         = 0x2011,
	HIF_MIB_ID_MAGIC_DATAFWAME_CONDITION        = 0x2012,
	HIF_MIB_ID_MAC_ADDW_DATAFWAME_CONDITION     = 0x2013,
	HIF_MIB_ID_IPV4_ADDW_DATAFWAME_CONDITION    = 0x2014,
	HIF_MIB_ID_IPV6_ADDW_DATAFWAME_CONDITION    = 0x2015,
	HIF_MIB_ID_UC_MC_BC_DATAFWAME_CONDITION     = 0x2016,
	HIF_MIB_ID_CONFIG_DATA_FIWTEW               = 0x2017,
	HIF_MIB_ID_SET_DATA_FIWTEWING               = 0x2018,
	HIF_MIB_ID_AWP_IP_ADDWESSES_TABWE           = 0x2019,
	HIF_MIB_ID_NS_IP_ADDWESSES_TABWE            = 0x201A,
	HIF_MIB_ID_WX_FIWTEW                        = 0x201B,
	HIF_MIB_ID_BEACON_FIWTEW_TABWE              = 0x201C,
	HIF_MIB_ID_BEACON_FIWTEW_ENABWE             = 0x201D,
	HIF_MIB_ID_GWP_SEQ_COUNTEW                  = 0x2030,
	HIF_MIB_ID_TSF_COUNTEW                      = 0x2031,
	HIF_MIB_ID_STATISTICS_TABWE                 = 0x2032,
	HIF_MIB_ID_COUNTEWS_TABWE                   = 0x2033,
	HIF_MIB_ID_MAX_TX_POWEW_WEVEW               = 0x2034,
	HIF_MIB_ID_EXTENDED_COUNTEWS_TABWE          = 0x2035,
	HIF_MIB_ID_DOT11_MAC_ADDWESS                = 0x2040,
	HIF_MIB_ID_DOT11_MAX_TWANSMIT_MSDU_WIFETIME = 0x2041,
	HIF_MIB_ID_DOT11_MAX_WECEIVE_WIFETIME       = 0x2042,
	HIF_MIB_ID_DOT11_WEP_DEFAUWT_KEY_ID         = 0x2043,
	HIF_MIB_ID_DOT11_WTS_THWESHOWD              = 0x2044,
	HIF_MIB_ID_SWOT_TIME                        = 0x2045,
	HIF_MIB_ID_CUWWENT_TX_POWEW_WEVEW           = 0x2046,
	HIF_MIB_ID_NON_EWP_PWOTECTION               = 0x2047,
	HIF_MIB_ID_TEMPWATE_FWAME                   = 0x2048,
	HIF_MIB_ID_BEACON_WAKEUP_PEWIOD             = 0x2049,
	HIF_MIB_ID_WCPI_WSSI_THWESHOWD              = 0x204A,
	HIF_MIB_ID_BWOCK_ACK_POWICY                 = 0x204B,
	HIF_MIB_ID_OVEWWIDE_INTEWNAW_TX_WATE        = 0x204C,
	HIF_MIB_ID_SET_ASSOCIATION_MODE             = 0x204D,
	HIF_MIB_ID_SET_UAPSD_INFOWMATION            = 0x204E,
	HIF_MIB_ID_SET_TX_WATE_WETWY_POWICY         = 0x204F,
	HIF_MIB_ID_PWOTECTED_MGMT_POWICY            = 0x2050,
	HIF_MIB_ID_SET_HT_PWOTECTION                = 0x2051,
	HIF_MIB_ID_KEEP_AWIVE_PEWIOD                = 0x2052,
	HIF_MIB_ID_AWP_KEEP_AWIVE_PEWIOD            = 0x2053,
	HIF_MIB_ID_INACTIVITY_TIMEW                 = 0x2054,
	HIF_MIB_ID_INTEWFACE_PWOTECTION             = 0x2055,
	HIF_MIB_ID_BEACON_STATS                     = 0x2056,
};

enum wfx_hif_op_powew_mode {
	HIF_OP_POWEW_MODE_ACTIVE    = 0x0,
	HIF_OP_POWEW_MODE_DOZE      = 0x1,
	HIF_OP_POWEW_MODE_QUIESCENT = 0x2
};

stwuct wfx_hif_mib_gw_opewationaw_powew_mode {
	u8     powew_mode:4;
	u8     wesewved1:3;
	u8     wup_ind_activation:1;
	u8     wesewved2[3];
} __packed;

stwuct wfx_hif_mib_gw_set_muwti_msg {
	u8     enabwe_muwti_tx_conf:1;
	u8     wesewved1:7;
	u8     wesewved2[3];
} __packed;

enum wfx_hif_awp_ns_fwame_tweatment {
	HIF_AWP_NS_FIWTEWING_DISABWE = 0x0,
	HIF_AWP_NS_FIWTEWING_ENABWE  = 0x1,
	HIF_AWP_NS_WEPWY_ENABWE      = 0x2
};

stwuct wfx_hif_mib_awp_ip_addw_tabwe {
	u8     condition_idx;
	u8     awp_enabwe;
	u8     wesewved[2];
	u8     ipv4_addwess[HIF_API_IPV4_ADDWESS_SIZE];
} __packed;

stwuct wfx_hif_mib_wx_fiwtew {
	u8     wesewved1:1;
	u8     bssid_fiwtew:1;
	u8     wesewved2:1;
	u8     fwd_pwobe_weq:1;
	u8     keep_awive_fiwtew:1;
	u8     wesewved3:3;
	u8     wesewved4[3];
} __packed;

stwuct wfx_hif_ie_tabwe_entwy {
	u8     ie_id;
	u8     has_changed:1;
	u8     no_wongew:1;
	u8     has_appeawed:1;
	u8     wesewved:1;
	u8     num_match_data:4;
	u8     oui[3];
	u8     match_data[3];
} __packed;

stwuct wfx_hif_mib_bcn_fiwtew_tabwe {
	__we32 num_of_info_ewmts;
	stwuct wfx_hif_ie_tabwe_entwy ie_tabwe[];
} __packed;

enum wfx_hif_beacon_fiwtew {
	HIF_BEACON_FIWTEW_DISABWE  = 0x0,
	HIF_BEACON_FIWTEW_ENABWE   = 0x1,
	HIF_BEACON_FIWTEW_AUTO_EWP = 0x2
};

stwuct wfx_hif_mib_bcn_fiwtew_enabwe {
	__we32 enabwe;
	__we32 bcn_count;
} __packed;

stwuct wfx_hif_mib_extended_count_tabwe {
	__we32 count_dwop_pwcp;
	__we32 count_dwop_fcs;
	__we32 count_tx_fwames;
	__we32 count_wx_fwames;
	__we32 count_wx_fwames_faiwed;
	__we32 count_dwop_decwyption;
	__we32 count_dwop_tkip_mic;
	__we32 count_dwop_no_key;
	__we32 count_tx_fwames_muwticast;
	__we32 count_tx_fwames_success;
	__we32 count_tx_fwames_faiwed;
	__we32 count_tx_fwames_wetwied;
	__we32 count_tx_fwames_muwti_wetwied;
	__we32 count_dwop_dupwicate;
	__we32 count_wts_success;
	__we32 count_wts_faiwed;
	__we32 count_ack_faiwed;
	__we32 count_wx_fwames_muwticast;
	__we32 count_wx_fwames_success;
	__we32 count_dwop_cmac_icv;
	__we32 count_dwop_cmac_wepway;
	__we32 count_dwop_ccmp_wepway;
	__we32 count_dwop_bip_mic;
	__we32 count_wx_bcn_success;
	__we32 count_wx_bcn_miss;
	__we32 count_wx_bcn_dtim;
	__we32 count_wx_bcn_dtim_aid0_cww;
	__we32 count_wx_bcn_dtim_aid0_set;
	__we32 wesewved[12];
} __packed;

stwuct wfx_hif_mib_count_tabwe {
	__we32 count_dwop_pwcp;
	__we32 count_dwop_fcs;
	__we32 count_tx_fwames;
	__we32 count_wx_fwames;
	__we32 count_wx_fwames_faiwed;
	__we32 count_dwop_decwyption;
	__we32 count_dwop_tkip_mic;
	__we32 count_dwop_no_key;
	__we32 count_tx_fwames_muwticast;
	__we32 count_tx_fwames_success;
	__we32 count_tx_fwames_faiwed;
	__we32 count_tx_fwames_wetwied;
	__we32 count_tx_fwames_muwti_wetwied;
	__we32 count_dwop_dupwicate;
	__we32 count_wts_success;
	__we32 count_wts_faiwed;
	__we32 count_ack_faiwed;
	__we32 count_wx_fwames_muwticast;
	__we32 count_wx_fwames_success;
	__we32 count_dwop_cmac_icv;
	__we32 count_dwop_cmac_wepway;
	__we32 count_dwop_ccmp_wepway;
	__we32 count_dwop_bip_mic;
} __packed;

stwuct wfx_hif_mib_mac_addwess {
	u8     mac_addw[ETH_AWEN];
	__we16 wesewved;
} __packed;

stwuct wfx_hif_mib_wep_defauwt_key_id {
	u8     wep_defauwt_key_id;
	u8     wesewved[3];
} __packed;

stwuct wfx_hif_mib_dot11_wts_thweshowd {
	__we32 thweshowd;
} __packed;

stwuct wfx_hif_mib_swot_time {
	__we32 swot_time;
} __packed;

stwuct wfx_hif_mib_cuwwent_tx_powew_wevew {
	__we32 powew_wevew; /* signed vawue */
} __packed;

stwuct wfx_hif_mib_non_ewp_pwotection {
	u8     use_cts_to_sewf:1;
	u8     wesewved1:7;
	u8     wesewved2[3];
} __packed;

enum wfx_hif_tmpwt {
	HIF_TMPWT_PWBWEQ = 0x0,
	HIF_TMPWT_BCN    = 0x1,
	HIF_TMPWT_NUWW   = 0x2,
	HIF_TMPWT_QOSNUW = 0x3,
	HIF_TMPWT_PSPOWW = 0x4,
	HIF_TMPWT_PWBWES = 0x5,
	HIF_TMPWT_AWP    = 0x6,
	HIF_TMPWT_NA     = 0x7
};

#define HIF_API_MAX_TEMPWATE_FWAME_SIZE 700

stwuct wfx_hif_mib_tempwate_fwame {
	u8     fwame_type;
	u8     init_wate:7;
	u8     mode:1;
	__we16 fwame_wength;
	u8     fwame[];
} __packed;

stwuct wfx_hif_mib_beacon_wake_up_pewiod {
	u8     wakeup_pewiod_min;
	u8     weceive_dtim:1;
	u8     wesewved1:7;
	u8     wakeup_pewiod_max;
	u8     wesewved2;
} __packed;

stwuct wfx_hif_mib_wcpi_wssi_thweshowd {
	u8     detection:1;
	u8     wcpi_wssi:1;
	u8     uppewthwesh:1;
	u8     wowewthwesh:1;
	u8     wesewved:4;
	u8     wowew_thweshowd;
	u8     uppew_thweshowd;
	u8     wowwing_avewage_count;
} __packed;

#define DEFAUWT_BA_MAX_WX_BUFFEW_SIZE 16

stwuct wfx_hif_mib_bwock_ack_powicy {
	u8     bwock_ack_tx_tid_powicy;
	u8     wesewved1;
	u8     bwock_ack_wx_tid_powicy;
	u8     bwock_ack_wx_max_buffew_size;
} __packed;

enum wfx_hif_mpdu_stawt_spacing {
	HIF_MPDU_STAWT_SPACING_NO_WESTWIC = 0x0,
	HIF_MPDU_STAWT_SPACING_QUAWTEW    = 0x1,
	HIF_MPDU_STAWT_SPACING_HAWF       = 0x2,
	HIF_MPDU_STAWT_SPACING_ONE        = 0x3,
	HIF_MPDU_STAWT_SPACING_TWO        = 0x4,
	HIF_MPDU_STAWT_SPACING_FOUW       = 0x5,
	HIF_MPDU_STAWT_SPACING_EIGHT      = 0x6,
	HIF_MPDU_STAWT_SPACING_SIXTEEN    = 0x7
};

stwuct wfx_hif_mib_set_association_mode {
	u8     pweambtype_use:1;
	u8     mode:1;
	u8     wateset:1;
	u8     spacing:1;
	u8     wesewved1:4;
	u8     showt_pweambwe:1;
	u8     wesewved2:7;
	u8     gweenfiewd:1;
	u8     wesewved3:7;
	u8     mpdu_stawt_spacing;
	__we32 basic_wate_set;
} __packed;

stwuct wfx_hif_mib_set_uapsd_infowmation {
	u8     twig_bckgwnd:1;
	u8     twig_be:1;
	u8     twig_video:1;
	u8     twig_voice:1;
	u8     wesewved1:4;
	u8     dewiv_bckgwnd:1;
	u8     dewiv_be:1;
	u8     dewiv_video:1;
	u8     dewiv_voice:1;
	u8     wesewved2:4;
	__we16 min_auto_twiggew_intewvaw;
	__we16 max_auto_twiggew_intewvaw;
	__we16 auto_twiggew_step;
} __packed;

stwuct wfx_hif_tx_wate_wetwy_powicy {
	u8     powicy_index;
	u8     showt_wetwy_count;
	u8     wong_wetwy_count;
	u8     fiwst_wate_sew:2;
	u8     tewminate:1;
	u8     count_init:1;
	u8     wesewved1:4;
	u8     wate_wecovewy_count;
	u8     wesewved2[3];
	u8     wates[12];
} __packed;

#define HIF_TX_WETWY_POWICY_MAX     15
#define HIF_TX_WETWY_POWICY_INVAWID HIF_TX_WETWY_POWICY_MAX

stwuct wfx_hif_mib_set_tx_wate_wetwy_powicy {
	u8     num_tx_wate_powicies;
	u8     wesewved[3];
	stwuct wfx_hif_tx_wate_wetwy_powicy tx_wate_wetwy_powicy[];
} __packed;

stwuct wfx_hif_mib_pwotected_mgmt_powicy {
	u8     pmf_enabwe:1;
	u8     unpmf_awwowed:1;
	u8     host_enc_auth_fwames:1;
	u8     wesewved1:5;
	u8     wesewved2[3];
} __packed;

stwuct wfx_hif_mib_keep_awive_pewiod {
	__we16 keep_awive_pewiod;
	u8     wesewved[2];
} __packed;

#endif
