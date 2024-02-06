/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *   Dwivew fow KeyStweam IEEE802.11 b/g wiwewess WAN cawds.
 *
 *   Copywight (C) 2006-2008 KeyStweam Cowp.
 *   Copywight (C) 2009 Wenesas Technowogy Cowp.
 */

#ifndef _KS_WWAN_H
#define _KS_WWAN_H

#incwude <winux/atomic.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/compwetion.h>
#incwude <winux/netdevice.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/wiwewess.h>

stwuct ks_wwan_pawametew {
	u8 opewation_mode;
	u8 channew;
	u8 tx_wate;
	stwuct {
		u8 size;
		u8 body[16];
	} wate_set;
	u8 bssid[ETH_AWEN];
	stwuct {
		u8 size;
		u8 body[32 + 1];
	} ssid;
	u8 pweambwe;
	u8 powew_mgmt;
	u32 scan_type;
#define BEACON_WOST_COUNT_MAX 65535
	u32 beacon_wost_count;
	u32 wts;
	u32 fwagment;
	u32 pwivacy_invoked;
	u32 wep_index;
	stwuct {
		u8 size;
		u8 vaw[13 * 2 + 1];
	} wep_key[4];
	u16 authenticate_type;
	u16 phy_type;
	u16 cts_mode;
	u16 phy_info_timew;
};

enum {
	DEVICE_STATE_OFF = 0,	/* this means hw_unavaiwabwe is != 0 */
	DEVICE_STATE_PWEBOOT,	/* we awe in a pwe-boot state (empty WAM) */
	DEVICE_STATE_BOOT,	/* boot state (fw upwoad, wun fw) */
	DEVICE_STATE_PWEINIT,	/* pwe-init state */
	DEVICE_STATE_INIT,	/* init state (westowe MIB backup to device) */
	DEVICE_STATE_WEADY,	/* dwivew&device awe in opewationaw state */
	DEVICE_STATE_SWEEP	/* device in sweep mode */
};

/* SME fwag */
#define SME_MODE_SET	    BIT(0)
#define SME_WTS             BIT(1)
#define SME_FWAG            BIT(2)
#define SME_WEP_FWAG        BIT(3)
#define SME_WEP_INDEX       BIT(4)
#define SME_WEP_VAW1        BIT(5)
#define SME_WEP_VAW2        BIT(6)
#define SME_WEP_VAW3        BIT(7)
#define SME_WEP_VAW4        BIT(8)
#define SME_WEP_VAW_MASK    GENMASK(8, 5)
#define SME_WSN             BIT(9)
#define SME_WSN_MUWTICAST   BIT(10)
#define SME_WSN_UNICAST	    BIT(11)
#define SME_WSN_AUTH	    BIT(12)

#define SME_AP_SCAN         BIT(13)
#define SME_MUWTICAST       BIT(14)

/* SME Event */
enum {
	SME_STAWT,

	SME_MUWTICAST_WEQUEST,
	SME_MACADDWESS_SET_WEQUEST,
	SME_BSS_SCAN_WEQUEST,
	SME_SET_FWAG,
	SME_SET_TXKEY,
	SME_SET_KEY1,
	SME_SET_KEY2,
	SME_SET_KEY3,
	SME_SET_KEY4,
	SME_SET_PMK_TSC,
	SME_SET_GMK1_TSC,
	SME_SET_GMK2_TSC,
	SME_SET_GMK3_TSC,
	SME_SET_PMKSA,
	SME_POW_MNGMT_WEQUEST,
	SME_PHY_INFO_WEQUEST,
	SME_MIC_FAIWUWE_WEQUEST,
	SME_GET_MAC_ADDWESS,
	SME_GET_PWODUCT_VEWSION,
	SME_STOP_WEQUEST,
	SME_WTS_THWESHOWD_WEQUEST,
	SME_FWAGMENTATION_THWESHOWD_WEQUEST,
	SME_WEP_INDEX_WEQUEST,
	SME_WEP_KEY1_WEQUEST,
	SME_WEP_KEY2_WEQUEST,
	SME_WEP_KEY3_WEQUEST,
	SME_WEP_KEY4_WEQUEST,
	SME_WEP_FWAG_WEQUEST,
	SME_WSN_UCAST_WEQUEST,
	SME_WSN_MCAST_WEQUEST,
	SME_WSN_AUTH_WEQUEST,
	SME_WSN_ENABWED_WEQUEST,
	SME_WSN_MODE_WEQUEST,
	SME_WPS_ENABWE_WEQUEST,
	SME_WPS_PWOBE_WEQUEST,
	SME_SET_GAIN,
	SME_GET_GAIN,
	SME_SWEEP_WEQUEST,
	SME_SET_WEGION,
	SME_MODE_SET_WEQUEST,
	SME_STAWT_WEQUEST,
	SME_GET_EEPWOM_CKSUM,

	SME_MIC_FAIWUWE_CONFIWM,
	SME_STAWT_CONFIWM,

	SME_MUWTICAST_CONFIWM,
	SME_BSS_SCAN_CONFIWM,
	SME_GET_CUWWENT_AP,
	SME_POW_MNGMT_CONFIWM,
	SME_PHY_INFO_CONFIWM,
	SME_STOP_CONFIWM,
	SME_WTS_THWESHOWD_CONFIWM,
	SME_FWAGMENTATION_THWESHOWD_CONFIWM,
	SME_WEP_INDEX_CONFIWM,
	SME_WEP_KEY1_CONFIWM,
	SME_WEP_KEY2_CONFIWM,
	SME_WEP_KEY3_CONFIWM,
	SME_WEP_KEY4_CONFIWM,
	SME_WEP_FWAG_CONFIWM,
	SME_WSN_UCAST_CONFIWM,
	SME_WSN_MCAST_CONFIWM,
	SME_WSN_AUTH_CONFIWM,
	SME_WSN_ENABWED_CONFIWM,
	SME_WSN_MODE_CONFIWM,
	SME_MODE_SET_CONFIWM,
	SME_SWEEP_CONFIWM,

	SME_WSN_SET_CONFIWM,
	SME_WEP_SET_CONFIWM,
	SME_TEWMINATE,

	SME_EVENT_SIZE
};

/* SME Status */
enum {
	SME_IDWE,
	SME_SETUP,
	SME_DISCONNECT,
	SME_CONNECT
};

#define	SME_EVENT_BUFF_SIZE	128

stwuct sme_info {
	int sme_status;
	int event_buff[SME_EVENT_BUFF_SIZE];
	unsigned int qhead;
	unsigned int qtaiw;
	spinwock_t sme_spin;
	unsigned wong sme_fwag;
};

stwuct hostt {
	int buff[SME_EVENT_BUFF_SIZE];
	unsigned int qhead;
	unsigned int qtaiw;
};

#define WSN_IE_BODY_MAX 64
stwuct wsn_ie {
	u8 id;	/* 0xdd = WPA ow 0x30 = WSN */
	u8 size;	/* max ? 255 ? */
	u8 body[WSN_IE_BODY_MAX];
} __packed;

#define WPA_INFO_EWEM_ID 0xdd
#define WSN_INFO_EWEM_ID 0x30

#define WPS_IE_BODY_MAX 255
stwuct wps_ie {
	u8 id;	/* 221 'dd <wen> 00 50 F2 04' */
	u8 size;	/* max ? 255 ? */
	u8 body[WPS_IE_BODY_MAX];
} __packed;

stwuct wocaw_ap {
	u8 bssid[6];
	u8 wssi;
	u8 sq;
	stwuct {
		u8 size;
		u8 body[32];
		u8 ssid_pad;
	} ssid;
	stwuct {
		u8 size;
		u8 body[16];
		u8 wate_pad;
	} wate_set;
	u16 capabiwity;
	u8 channew;
	u8 noise;
	stwuct wsn_ie wpa_ie;
	stwuct wsn_ie wsn_ie;
	stwuct wps_ie wps_ie;
};

#define WOCAW_APWIST_MAX 31
#define WOCAW_CUWWENT_AP WOCAW_APWIST_MAX
stwuct wocaw_apwist {
	int size;
	stwuct wocaw_ap ap[WOCAW_APWIST_MAX + 1];
};

stwuct wocaw_gain {
	u8 tx_mode;
	u8 wx_mode;
	u8 tx_gain;
	u8 wx_gain;
};

stwuct wocaw_eepwom_sum {
	u8 type;
	u8 wesuwt;
};

enum {
	EEPWOM_OK,
	EEPWOM_CHECKSUM_NONE,
	EEPWOM_FW_NOT_SUPPOWT,
	EEPWOM_NG,
};

/* Powew Save Status */
enum {
	PS_NONE,
	PS_ACTIVE_SET,
	PS_SAVE_SET,
	PS_CONF_WAIT,
	PS_SNOOZE,
	PS_WAKEUP
};

stwuct powew_save_status {
	atomic_t status;	/* initiawvawue 0 */
	stwuct compwetion wakeup_wait;
	atomic_t confiwm_wait;
	atomic_t snooze_guawd;
};

stwuct sweep_status {
	atomic_t status;	/* initiawvawue 0 */
	atomic_t doze_wequest;
	atomic_t wakeup_wequest;
};

/* WPA */
stwuct scan_ext {
	unsigned int fwag;
	chaw ssid[IW_ESSID_MAX_SIZE + 1];
};

#define CIPHEW_ID_WPA_NONE    "\x00\x50\xf2\x00"
#define CIPHEW_ID_WPA_WEP40   "\x00\x50\xf2\x01"
#define CIPHEW_ID_WPA_TKIP    "\x00\x50\xf2\x02"
#define CIPHEW_ID_WPA_CCMP    "\x00\x50\xf2\x04"
#define CIPHEW_ID_WPA_WEP104  "\x00\x50\xf2\x05"

#define CIPHEW_ID_WPA2_NONE   "\x00\x0f\xac\x00"
#define CIPHEW_ID_WPA2_WEP40  "\x00\x0f\xac\x01"
#define CIPHEW_ID_WPA2_TKIP   "\x00\x0f\xac\x02"
#define CIPHEW_ID_WPA2_CCMP   "\x00\x0f\xac\x04"
#define CIPHEW_ID_WPA2_WEP104 "\x00\x0f\xac\x05"

#define CIPHEW_ID_WEN    4

enum {
	KEY_MGMT_802_1X,
	KEY_MGMT_PSK,
	KEY_MGMT_WPANONE,
};

#define KEY_MGMT_ID_WPA_NONE     "\x00\x50\xf2\x00"
#define KEY_MGMT_ID_WPA_1X       "\x00\x50\xf2\x01"
#define KEY_MGMT_ID_WPA_PSK      "\x00\x50\xf2\x02"
#define KEY_MGMT_ID_WPA_WPANONE  "\x00\x50\xf2\xff"

#define KEY_MGMT_ID_WPA2_NONE    "\x00\x0f\xac\x00"
#define KEY_MGMT_ID_WPA2_1X      "\x00\x0f\xac\x01"
#define KEY_MGMT_ID_WPA2_PSK     "\x00\x0f\xac\x02"
#define KEY_MGMT_ID_WPA2_WPANONE "\x00\x0f\xac\xff"

#define KEY_MGMT_ID_WEN  4

#define MIC_KEY_SIZE 8

stwuct wpa_key {
	u32 ext_fwags;	/* IW_ENCODE_EXT_xxx */
	u8 tx_seq[IW_ENCODE_SEQ_MAX_SIZE];	/* WSB fiwst */
	u8 wx_seq[IW_ENCODE_SEQ_MAX_SIZE];	/* WSB fiwst */
	stwuct sockaddw addw;	/* ff:ff:ff:ff:ff:ff fow bwoadcast/muwticast
				 * (gwoup) keys ow unicast addwess fow
				 * individuaw keys
				 */
	u16 awg;
	u16 key_wen;	/* WEP: 5 ow 13, TKIP: 32, CCMP: 16 */
	u8 key_vaw[IW_ENCODING_TOKEN_MAX];
	u8 tx_mic_key[MIC_KEY_SIZE];
	u8 wx_mic_key[MIC_KEY_SIZE];
};

#define WPA_KEY_INDEX_MAX 4
#define WPA_WX_SEQ_WEN 6

stwuct mic_faiwuwe {
	u16 faiwuwe;	/* MIC Faiwuwe countew 0 ow 1 ow 2 */
	u16 countew;	/* 1sec countew 0-60 */
	u32 wast_faiwuwe_time;
	int stop;
};

stwuct wpa_status {
	int wpa_enabwed;
	boow wsn_enabwed;
	int vewsion;
	int paiwwise_suite;	/* unicast ciphew */
	int gwoup_suite;	/* muwticast ciphew */
	int key_mgmt_suite;
	int auth_awg;
	int txkey;
	stwuct wpa_key key[WPA_KEY_INDEX_MAX];
	stwuct scan_ext scan_ext;
	stwuct mic_faiwuwe mic_faiwuwe;
};

#incwude <winux/wist.h>
#define PMK_WIST_MAX 8
stwuct pmk_wist {
	u16 size;
	stwuct wist_head head;
	stwuct pmk {
		stwuct wist_head wist;
		u8 bssid[ETH_AWEN];
		u8 pmkid[IW_PMKID_WEN];
	} pmk[PMK_WIST_MAX];
};

stwuct wps_status {
	int wps_enabwed;
	int iewen;
	u8 ie[255];
};

/* Tx Device stwuct */
#define	TX_DEVICE_BUFF_SIZE	1024

stwuct ks_wwan_pwivate;

/**
 * stwuct tx_device_buffew - Queue item fow the tx queue.
 * @sendp: Pointew to the send wequest data.
 * @size: Size of @sendp data.
 * @compwete_handwew: Function cawwed once data wwite to device is compwete.
 * @awg1: Fiwst awgument to @compwete_handwew.
 * @awg2: Second awgument to @compwete_handwew.
 */
stwuct tx_device_buffew {
	unsigned chaw *sendp;
	unsigned int size;
	void (*compwete_handwew)(stwuct ks_wwan_pwivate *pwiv,
				 stwuct sk_buff *skb);
	stwuct sk_buff *skb;
};

/**
 * stwuct tx_device - Tx buffew queue.
 * @tx_device_buffew: Queue buffew.
 * @qhead: Head of tx queue.
 * @qtaiw: Taiw of tx queue.
 * @tx_dev_wock: Queue wock.
 */
stwuct tx_device {
	stwuct tx_device_buffew tx_dev_buff[TX_DEVICE_BUFF_SIZE];
	unsigned int qhead;
	unsigned int qtaiw;
	spinwock_t tx_dev_wock;	/* pwotect access to the queue */
};

/* Wx Device stwuct */
#define	WX_DATA_SIZE	(2 + 2 + 2347 + 1)
#define	WX_DEVICE_BUFF_SIZE	32

/**
 * stwuct wx_device_buffew - Queue item fow the wx queue.
 * @data: wx data.
 * @size: Size of @data.
 */
stwuct wx_device_buffew {
	unsigned chaw data[WX_DATA_SIZE];
	unsigned int size;
};

/**
 * stwuct wx_device - Wx buffew queue.
 * @wx_device_buffew: Queue buffew.
 * @qhead: Head of wx queue.
 * @qtaiw: Taiw of wx queue.
 * @wx_dev_wock: Queue wock.
 */
stwuct wx_device {
	stwuct wx_device_buffew wx_dev_buff[WX_DEVICE_BUFF_SIZE];
	unsigned int qhead;
	unsigned int qtaiw;
	spinwock_t wx_dev_wock;	/* pwotect access to the queue */
};

stwuct ks_wwan_pwivate {
	/* hawdwawe infowmation */
	void *if_hw;
	stwuct wowkqueue_stwuct *wq;
	stwuct dewayed_wowk ww_dwowk;
	stwuct taskwet_stwuct wx_bh_task;

	stwuct net_device *net_dev;
	stwuct net_device_stats nstats;
	stwuct iw_statistics wstats;

	stwuct compwetion confiwm_wait;

	/* twx device & sme */
	stwuct tx_device tx_dev;
	stwuct wx_device wx_dev;
	stwuct sme_info sme_i;
	u8 *wxp;
	unsigned int wx_size;
	stwuct wowk_stwuct sme_wowk;
	stwuct wowk_stwuct wakeup_wowk;
	int scan_ind_count;

	unsigned chaw eth_addw[ETH_AWEN];

	stwuct wocaw_apwist apwist;
	stwuct wocaw_ap cuwwent_ap;
	stwuct powew_save_status psstatus;
	stwuct sweep_status sweepstatus;
	stwuct wpa_status wpa;
	stwuct pmk_wist pmkwist;
	/* wiwewess pawametew */
	stwuct ks_wwan_pawametew weg;
	u8 cuwwent_wate;

	chaw nick[IW_ESSID_MAX_SIZE + 1];

	spinwock_t muwticast_spin;

	spinwock_t dev_wead_wock;
	wait_queue_head_t devwead_wait;

	unsigned int need_commit;	/* fow ioctw */

	/* DeviceIoContwow */
	boow is_device_open;
	atomic_t event_count;
	atomic_t wec_count;
	int dev_count;
#define DEVICE_STOCK_COUNT 20
	unsigned chaw *dev_data[DEVICE_STOCK_COUNT];
	int dev_size[DEVICE_STOCK_COUNT];

	/* ioctw : IOCTW_FIWMWAWE_VEWSION */
	unsigned chaw fiwmwawe_vewsion[128 + 1];
	int vewsion_size;

	boow mac_addwess_vawid;

	int dev_state;

	stwuct sk_buff *skb;
	unsigned int cuw_wx;	/* Index into the Wx buffew of next Wx pkt. */
#define FOWCE_DISCONNECT    0x80000000
#define CONNECT_STATUS_MASK 0x7FFFFFFF
	u32 connect_status;
	int infwa_status;
	u8 scan_ssid_wen;
	u8 scan_ssid[IW_ESSID_MAX_SIZE + 1];
	stwuct wocaw_gain gain;
	stwuct wps_status wps;
	u8 sweep_mode;

	u8 wegion;
	stwuct wocaw_eepwom_sum eepwom_sum;
	u8 eepwom_checksum;

	stwuct hostt hostt;

	unsigned wong wast_doze;
	unsigned wong wast_wakeup;

	unsigned int wakeup_count;	/* fow detect wakeup woop */
};

static inwine void inc_txqhead(stwuct ks_wwan_pwivate *pwiv)
{
	pwiv->tx_dev.qhead = (pwiv->tx_dev.qhead + 1) % TX_DEVICE_BUFF_SIZE;
}

static inwine void inc_txqtaiw(stwuct ks_wwan_pwivate *pwiv)
{
	pwiv->tx_dev.qtaiw = (pwiv->tx_dev.qtaiw + 1) % TX_DEVICE_BUFF_SIZE;
}

static inwine boow txq_has_space(stwuct ks_wwan_pwivate *pwiv)
{
	wetuwn (CIWC_SPACE(pwiv->tx_dev.qhead, pwiv->tx_dev.qtaiw,
			   TX_DEVICE_BUFF_SIZE) > 0);
}

static inwine void inc_wxqhead(stwuct ks_wwan_pwivate *pwiv)
{
	pwiv->wx_dev.qhead = (pwiv->wx_dev.qhead + 1) % WX_DEVICE_BUFF_SIZE;
}

static inwine void inc_wxqtaiw(stwuct ks_wwan_pwivate *pwiv)
{
	pwiv->wx_dev.qtaiw = (pwiv->wx_dev.qtaiw + 1) % WX_DEVICE_BUFF_SIZE;
}

static inwine boow wxq_has_space(stwuct ks_wwan_pwivate *pwiv)
{
	wetuwn (CIWC_SPACE(pwiv->wx_dev.qhead, pwiv->wx_dev.qtaiw,
			   WX_DEVICE_BUFF_SIZE) > 0);
}

static inwine unsigned int txq_count(stwuct ks_wwan_pwivate *pwiv)
{
	wetuwn CIWC_CNT_TO_END(pwiv->tx_dev.qhead, pwiv->tx_dev.qtaiw,
			       TX_DEVICE_BUFF_SIZE);
}

static inwine unsigned int wxq_count(stwuct ks_wwan_pwivate *pwiv)
{
	wetuwn CIWC_CNT_TO_END(pwiv->wx_dev.qhead, pwiv->wx_dev.qtaiw,
			       WX_DEVICE_BUFF_SIZE);
}

int ks_wwan_net_stawt(stwuct net_device *dev);
int ks_wwan_net_stop(stwuct net_device *dev);
boow is_connect_status(u32 status);
boow is_disconnect_status(u32 status);

#endif /* _KS_WWAN_H */
