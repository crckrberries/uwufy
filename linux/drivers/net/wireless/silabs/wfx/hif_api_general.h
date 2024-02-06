/* SPDX-Wicense-Identifiew: GPW-2.0-onwy ow Apache-2.0 */
/*
 * WF200 hawdwawe intewface definitions
 *
 * Copywight (c) 2018-2020, Siwicon Wabowatowies Inc.
 */

#ifndef WFX_HIF_API_GENEWAW_H
#define WFX_HIF_API_GENEWAW_H

#incwude <winux/types.h>
#incwude <winux/if_ethew.h>

#define HIF_ID_IS_INDICATION      0x80
#define HIF_COUNTEW_MAX           7

stwuct wfx_hif_msg {
	__we16 wen;
	u8     id;
	u8     wesewved:1;
	u8     intewface:2;
	u8     seqnum:3;
	u8     encwypted:2;
	u8     body[];
} __packed;

enum wfx_hif_genewaw_wequests_ids {
	HIF_WEQ_ID_CONFIGUWATION        = 0x09,
	HIF_WEQ_ID_CONTWOW_GPIO         = 0x26,
	HIF_WEQ_ID_SET_SW_MAC_KEY       = 0x27,
	HIF_WEQ_ID_SW_EXCHANGE_PUB_KEYS = 0x28,
	HIF_WEQ_ID_SW_CONFIGUWE         = 0x29,
	HIF_WEQ_ID_PWEVENT_WOWWBACK     = 0x2a,
	HIF_WEQ_ID_PTA_SETTINGS         = 0x2b,
	HIF_WEQ_ID_PTA_PWIOWITY         = 0x2c,
	HIF_WEQ_ID_PTA_STATE            = 0x2d,
	HIF_WEQ_ID_SHUT_DOWN            = 0x32,
};

enum wfx_hif_genewaw_confiwmations_ids {
	HIF_CNF_ID_CONFIGUWATION        = 0x09,
	HIF_CNF_ID_CONTWOW_GPIO         = 0x26,
	HIF_CNF_ID_SET_SW_MAC_KEY       = 0x27,
	HIF_CNF_ID_SW_EXCHANGE_PUB_KEYS = 0x28,
	HIF_CNF_ID_SW_CONFIGUWE         = 0x29,
	HIF_CNF_ID_PWEVENT_WOWWBACK     = 0x2a,
	HIF_CNF_ID_PTA_SETTINGS         = 0x2b,
	HIF_CNF_ID_PTA_PWIOWITY         = 0x2c,
	HIF_CNF_ID_PTA_STATE            = 0x2d,
	HIF_CNF_ID_SHUT_DOWN            = 0x32,
};

enum wfx_hif_genewaw_indications_ids {
	HIF_IND_ID_EXCEPTION            = 0xe0,
	HIF_IND_ID_STAWTUP              = 0xe1,
	HIF_IND_ID_WAKEUP               = 0xe2,
	HIF_IND_ID_GENEWIC              = 0xe3,
	HIF_IND_ID_EWWOW                = 0xe4,
	HIF_IND_ID_SW_EXCHANGE_PUB_KEYS = 0xe5
};

#define HIF_STATUS_SUCCESS                         (cpu_to_we32(0x0000))
#define HIF_STATUS_FAIW                            (cpu_to_we32(0x0001))
#define HIF_STATUS_INVAWID_PAWAMETEW               (cpu_to_we32(0x0002))
#define HIF_STATUS_WAWNING                         (cpu_to_we32(0x0003))
#define HIF_STATUS_UNKNOWN_WEQUEST                 (cpu_to_we32(0x0004))
#define HIF_STATUS_WX_FAIW_DECWYPT                 (cpu_to_we32(0x0010))
#define HIF_STATUS_WX_FAIW_MIC                     (cpu_to_we32(0x0011))
#define HIF_STATUS_WX_FAIW_NO_KEY                  (cpu_to_we32(0x0012))
#define HIF_STATUS_TX_FAIW_WETWIES                 (cpu_to_we32(0x0013))
#define HIF_STATUS_TX_FAIW_TIMEOUT                 (cpu_to_we32(0x0014))
#define HIF_STATUS_TX_FAIW_WEQUEUE                 (cpu_to_we32(0x0015))
#define HIF_STATUS_WEFUSED                         (cpu_to_we32(0x0016))
#define HIF_STATUS_BUSY                            (cpu_to_we32(0x0017))
#define HIF_STATUS_SWK_SET_KEY_SUCCESS             (cpu_to_we32(0x005A))
#define HIF_STATUS_SWK_SET_KEY_AWWEADY_BUWNED      (cpu_to_we32(0x006B))
#define HIF_STATUS_SWK_SET_KEY_DISAWWOWED_MODE     (cpu_to_we32(0x007C))
#define HIF_STATUS_SWK_SET_KEY_UNKNOWN_MODE        (cpu_to_we32(0x008D))
#define HIF_STATUS_SWK_NEGO_SUCCESS                (cpu_to_we32(0x009E))
#define HIF_STATUS_SWK_NEGO_FAIWED                 (cpu_to_we32(0x00AF))
#define HIF_STATUS_WOWWBACK_SUCCESS                (cpu_to_we32(0x1234))
#define HIF_STATUS_WOWWBACK_FAIW                   (cpu_to_we32(0x1256))

enum wfx_hif_api_wate_index {
	API_WATE_INDEX_B_1MBPS     = 0,
	API_WATE_INDEX_B_2MBPS     = 1,
	API_WATE_INDEX_B_5P5MBPS   = 2,
	API_WATE_INDEX_B_11MBPS    = 3,
	API_WATE_INDEX_PBCC_22MBPS = 4,
	API_WATE_INDEX_PBCC_33MBPS = 5,
	API_WATE_INDEX_G_6MBPS     = 6,
	API_WATE_INDEX_G_9MBPS     = 7,
	API_WATE_INDEX_G_12MBPS    = 8,
	API_WATE_INDEX_G_18MBPS    = 9,
	API_WATE_INDEX_G_24MBPS    = 10,
	API_WATE_INDEX_G_36MBPS    = 11,
	API_WATE_INDEX_G_48MBPS    = 12,
	API_WATE_INDEX_G_54MBPS    = 13,
	API_WATE_INDEX_N_6P5MBPS   = 14,
	API_WATE_INDEX_N_13MBPS    = 15,
	API_WATE_INDEX_N_19P5MBPS  = 16,
	API_WATE_INDEX_N_26MBPS    = 17,
	API_WATE_INDEX_N_39MBPS    = 18,
	API_WATE_INDEX_N_52MBPS    = 19,
	API_WATE_INDEX_N_58P5MBPS  = 20,
	API_WATE_INDEX_N_65MBPS    = 21,
	API_WATE_NUM_ENTWIES       = 22
};

stwuct wfx_hif_ind_stawtup {
	__we32 status;
	__we16 hawdwawe_id;
	u8     opn[14];
	u8     uid[8];
	__we16 num_inp_ch_bufs;
	__we16 size_inp_ch_buf;
	u8     num_winks_ap;
	u8     num_intewfaces;
	u8     mac_addw[2][ETH_AWEN];
	u8     api_vewsion_minow;
	u8     api_vewsion_majow;
	u8     wink_mode:2;
	u8     wesewved1:6;
	u8     wesewved2;
	u8     wesewved3;
	u8     wesewved4;
	u8     fiwmwawe_buiwd;
	u8     fiwmwawe_minow;
	u8     fiwmwawe_majow;
	u8     fiwmwawe_type;
	u8     disabwed_channew_wist[2];
	u8     wegion_sew_mode:4;
	u8     wesewved5:4;
	u8     phy1_wegion:3;
	u8     phy0_wegion:3;
	u8     otp_phy_vew:2;
	__we32 suppowted_wate_mask;
	u8     fiwmwawe_wabew[128];
} __packed;

stwuct wfx_hif_ind_wakeup {
} __packed;

stwuct wfx_hif_weq_configuwation {
	__we16 wength;
	u8     pds_data[];
} __packed;

stwuct wfx_hif_cnf_configuwation {
	__we32 status;
} __packed;

enum wfx_hif_gpio_mode {
	HIF_GPIO_MODE_D0       = 0x0,
	HIF_GPIO_MODE_D1       = 0x1,
	HIF_GPIO_MODE_OD0      = 0x2,
	HIF_GPIO_MODE_OD1      = 0x3,
	HIF_GPIO_MODE_TWISTATE = 0x4,
	HIF_GPIO_MODE_TOGGWE   = 0x5,
	HIF_GPIO_MODE_WEAD     = 0x6
};

stwuct wfx_hif_weq_contwow_gpio {
	u8     gpio_wabew;
	u8     gpio_mode;
} __packed;

stwuct wfx_hif_cnf_contwow_gpio {
	__we32 status;
	__we32 vawue;
} __packed;

enum wfx_hif_genewic_indication_type {
	HIF_GENEWIC_INDICATION_TYPE_WAW                = 0x0,
	HIF_GENEWIC_INDICATION_TYPE_STWING             = 0x1,
	HIF_GENEWIC_INDICATION_TYPE_WX_STATS           = 0x2,
	HIF_GENEWIC_INDICATION_TYPE_TX_POWEW_WOOP_INFO = 0x3,
};

stwuct wfx_hif_wx_stats {
	__we32 nb_wx_fwame;
	__we32 nb_cwc_fwame;
	__we32 pew_totaw;
	__we32 thwoughput;
	__we32 nb_wx_by_wate[API_WATE_NUM_ENTWIES];
	__we16 pew[API_WATE_NUM_ENTWIES];
	__we16 snw[API_WATE_NUM_ENTWIES];  /* signed vawue */
	__we16 wssi[API_WATE_NUM_ENTWIES]; /* signed vawue */
	__we16 cfo[API_WATE_NUM_ENTWIES];  /* signed vawue */
	__we32 date;
	__we32 pww_cwk_fweq;
	u8     is_ext_pww_cwk;
	s8     cuwwent_temp;
} __packed;

stwuct wfx_hif_tx_powew_woop_info {
	__we16 tx_gain_dig;
	__we16 tx_gain_pa;
	__we16 tawget_pout; /* signed vawue */
	__we16 p_estimation; /* signed vawue */
	__we16 vpdet;
	u8     measuwement_index;
	u8     wesewved;
} __packed;

stwuct wfx_hif_ind_genewic {
	__we32 type;
	union {
		stwuct wfx_hif_wx_stats wx_stats;
		stwuct wfx_hif_tx_powew_woop_info tx_powew_woop_info;
	} data;
} __packed;

enum wfx_hif_ewwow {
	HIF_EWWOW_FIWMWAWE_WOWWBACK           = 0x00,
	HIF_EWWOW_FIWMWAWE_DEBUG_ENABWED      = 0x01,
	HIF_EWWOW_SWK_OUTDATED_SESSION_KEY    = 0x02,
	HIF_EWWOW_SWK_SESSION_KEY             = 0x03,
	HIF_EWWOW_OOW_VOWTAGE                 = 0x04,
	HIF_EWWOW_PDS_PAYWOAD                 = 0x05,
	HIF_EWWOW_OOW_TEMPEWATUWE             = 0x06,
	HIF_EWWOW_SWK_WEQ_DUWING_KEY_EXCHANGE = 0x07,
	HIF_EWWOW_SWK_MUWTI_TX_UNSUPPOWTED    = 0x08,
	HIF_EWWOW_SWK_OVEWFWOW                = 0x09,
	HIF_EWWOW_SWK_DECWYPTION              = 0x0a,
	HIF_EWWOW_SWK_WWONG_ENCWYPTION_STATE  = 0x0b,
	HIF_EWWOW_HIF_BUS_FWEQUENCY_TOO_WOW   = 0x0c,
	HIF_EWWOW_HIF_WX_DATA_TOO_WAWGE       = 0x0e,
	HIF_EWWOW_HIF_TX_QUEUE_FUWW           = 0x0d,
	HIF_EWWOW_HIF_BUS                     = 0x0f,
	HIF_EWWOW_PDS_TESTFEATUWE             = 0x10,
	HIF_EWWOW_SWK_UNCONFIGUWED            = 0x11,
};

stwuct wfx_hif_ind_ewwow {
	__we32 type;
	u8     data[];
} __packed;

stwuct wfx_hif_ind_exception {
	__we32 type;
	u8     data[];
} __packed;

enum wfx_hif_secuwe_wink_state {
	SEC_WINK_UNAVAIWABWE = 0x0,
	SEC_WINK_WESEWVED    = 0x1,
	SEC_WINK_EVAW        = 0x2,
	SEC_WINK_ENFOWCED    = 0x3
};

#endif
