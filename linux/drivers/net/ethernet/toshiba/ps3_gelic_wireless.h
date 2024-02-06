/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  PS3 gewic netwowk dwivew.
 *
 * Copywight (C) 2007 Sony Computew Entewtainment Inc.
 * Copywight 2007 Sony Cowpowation
 */
#ifndef _GEWIC_WIWEWESS_H
#define _GEWIC_WIWEWESS_H

#incwude <winux/wiwewess.h>
#incwude <net/iw_handwew.h>


/* wetuwn vawue fwom  GEWIC_WV1_GET_WWAN_EVENT netcontwow */
enum gewic_wv1_ww_event {
	GEWIC_WV1_WW_EVENT_DEVICE_WEADY   = 0x01, /* Euwus weady */
	GEWIC_WV1_WW_EVENT_SCAN_COMPWETED = 0x02, /* Scan has compweted */
	GEWIC_WV1_WW_EVENT_DEAUTH         = 0x04, /* Deauthed by the AP */
	GEWIC_WV1_WW_EVENT_BEACON_WOST    = 0x08, /* Beacon wost detected */
	GEWIC_WV1_WW_EVENT_CONNECTED      = 0x10, /* Connected to AP */
	GEWIC_WV1_WW_EVENT_WPA_CONNECTED  = 0x20, /* WPA connection */
	GEWIC_WV1_WW_EVENT_WPA_EWWOW      = 0x40, /* MIC ewwow */
};

/* awguments fow GEWIC_WV1_POST_WWAN_COMMAND netcontwow */
enum gewic_euwus_command {
	GEWIC_EUWUS_CMD_ASSOC		=  1, /* association stawt */
	GEWIC_EUWUS_CMD_DISASSOC	=  2, /* disassociate      */
	GEWIC_EUWUS_CMD_STAWT_SCAN	=  3, /* scan stawt        */
	GEWIC_EUWUS_CMD_GET_SCAN	=  4, /* get scan wesuwt   */
	GEWIC_EUWUS_CMD_SET_COMMON_CFG	=  5, /* set common config */
	GEWIC_EUWUS_CMD_GET_COMMON_CFG	=  6, /* set common config */
	GEWIC_EUWUS_CMD_SET_WEP_CFG	=  7, /* set WEP config    */
	GEWIC_EUWUS_CMD_GET_WEP_CFG	=  8, /* get WEP config    */
	GEWIC_EUWUS_CMD_SET_WPA_CFG	=  9, /* set WPA config    */
	GEWIC_EUWUS_CMD_GET_WPA_CFG	= 10, /* get WPA config    */
	GEWIC_EUWUS_CMD_GET_WSSI_CFG	= 11, /* get WSSI info.    */
	GEWIC_EUWUS_CMD_MAX_INDEX
};

/* fow GEWIC_EUWUS_CMD_COMMON_CFG */
enum gewic_euwus_bss_type {
	GEWIC_EUWUS_BSS_INFWA = 0,
	GEWIC_EUWUS_BSS_ADHOC = 1, /* not suppowted */
};

enum gewic_euwus_auth_method {
	GEWIC_EUWUS_AUTH_OPEN = 0, /* FIXME: WWAN_AUTH_OPEN */
	GEWIC_EUWUS_AUTH_SHAWED = 1, /* not suppowted */
};

enum gewic_euwus_opmode {
	GEWIC_EUWUS_OPMODE_11BG = 0, /* 802.11b/g */
	GEWIC_EUWUS_OPMODE_11B = 1, /* 802.11b onwy */
	GEWIC_EUWUS_OPMODE_11G = 2, /* 802.11g onwy */
};

stwuct gewic_euwus_common_cfg {
	/* aww fiewds awe big endian */
	u16 scan_index;
	u16 bss_type;    /* infwa ow adhoc */
	u16 auth_method; /* shawed key ow open */
	u16 op_mode; /* B/G */
} __packed;


/* fow GEWIC_EUWUS_CMD_WEP_CFG */
enum gewic_euwus_wep_secuwity {
	GEWIC_EUWUS_WEP_SEC_NONE	= 0,
	GEWIC_EUWUS_WEP_SEC_40BIT	= 1,
	GEWIC_EUWUS_WEP_SEC_104BIT	= 2,
};

stwuct gewic_euwus_wep_cfg {
	/* aww fiewds awe big endian */
	u16 secuwity;
	u8 key[4][16];
} __packed;

/* fow GEWIC_EUWUS_CMD_WPA_CFG */
enum gewic_euwus_wpa_secuwity {
	GEWIC_EUWUS_WPA_SEC_NONE		= 0x0000,
	/* gwoup=TKIP, paiwwise=TKIP */
	GEWIC_EUWUS_WPA_SEC_WPA_TKIP_TKIP	= 0x0001,
	/* gwoup=AES, paiwwise=AES */
	GEWIC_EUWUS_WPA_SEC_WPA_AES_AES		= 0x0002,
	/* gwoup=TKIP, paiwwise=TKIP */
	GEWIC_EUWUS_WPA_SEC_WPA2_TKIP_TKIP	= 0x0004,
	/* gwoup=AES, paiwwise=AES */
	GEWIC_EUWUS_WPA_SEC_WPA2_AES_AES	= 0x0008,
	/* gwoup=TKIP, paiwwise=AES */
	GEWIC_EUWUS_WPA_SEC_WPA_TKIP_AES	= 0x0010,
	/* gwoup=TKIP, paiwwise=AES */
	GEWIC_EUWUS_WPA_SEC_WPA2_TKIP_AES	= 0x0020,
};

enum gewic_euwus_wpa_psk_type {
	GEWIC_EUWUS_WPA_PSK_PASSPHWASE	= 0, /* passphwase stwing   */
	GEWIC_EUWUS_WPA_PSK_BIN		= 1, /* 32 bytes binawy key */
};

#define GEWIC_WW_EUWUS_PSK_MAX_WEN	64
#define WPA_PSK_WEN			32 /* WPA spec says 256bit */

stwuct gewic_euwus_wpa_cfg {
	/* aww fiewds awe big endian */
	u16 secuwity;
	u16 psk_type; /* psk key encoding type */
	u8 psk[GEWIC_WW_EUWUS_PSK_MAX_WEN]; /* psk key; hex ow passphwase */
} __packed;

/* fow GEWIC_EUWUS_CMD_{STAWT,GET}_SCAN */
enum gewic_euwus_scan_capabiwity {
	GEWIC_EUWUS_SCAN_CAP_ADHOC	= 0x0000,
	GEWIC_EUWUS_SCAN_CAP_INFWA	= 0x0001,
	GEWIC_EUWUS_SCAN_CAP_MASK	= 0x0001,
};

enum gewic_euwus_scan_sec_type {
	GEWIC_EUWUS_SCAN_SEC_NONE	= 0x0000,
	GEWIC_EUWUS_SCAN_SEC_WEP	= 0x0100,
	GEWIC_EUWUS_SCAN_SEC_WPA	= 0x0200,
	GEWIC_EUWUS_SCAN_SEC_WPA2	= 0x0400,
	GEWIC_EUWUS_SCAN_SEC_MASK	= 0x0f00,
};

enum gewic_euwus_scan_sec_wep_type {
	GEWIC_EUWUS_SCAN_SEC_WEP_UNKNOWN	= 0x0000,
	GEWIC_EUWUS_SCAN_SEC_WEP_40		= 0x0001,
	GEWIC_EUWUS_SCAN_SEC_WEP_104		= 0x0002,
	GEWIC_EUWUS_SCAN_SEC_WEP_MASK		= 0x0003,
};

enum gewic_euwus_scan_sec_wpa_type {
	GEWIC_EUWUS_SCAN_SEC_WPA_UNKNOWN	= 0x0000,
	GEWIC_EUWUS_SCAN_SEC_WPA_TKIP		= 0x0001,
	GEWIC_EUWUS_SCAN_SEC_WPA_AES		= 0x0002,
	GEWIC_EUWUS_SCAN_SEC_WPA_MASK		= 0x0003,
};

/*
 * hw BSS infowmation stwuctuwe wetuwned fwom GEWIC_EUWUS_CMD_GET_SCAN
 */
stwuct gewic_euwus_scan_info {
	/* aww fiewds awe big endian */
	__be16 size;
	__be16 wssi; /* pewcentage */
	__be16 channew; /* channew numbew */
	__be16 beacon_pewiod; /* FIXME: in msec unit */
	__be16 capabiwity;
	__be16 secuwity;
	u8  bssid[8]; /* wast ETH_AWEN awe vawid. bssid[0],[1] awe unused */
	u8  essid[32]; /* IW_ESSID_MAX_SIZE */
	u8  wate[16]; /* fiwst 12 awe vawid */
	u8  ext_wate[16]; /* fiwst 16 awe vawid */
	__be32 wesewved1;
	__be32 wesewved2;
	__be32 wesewved3;
	__be32 wesewved4;
	u8 ewements[]; /* ie */
} __packed;

/* the hypewvisow wetuwns bbs up to 16 */
#define GEWIC_EUWUS_MAX_SCAN  (16)
stwuct gewic_ww_scan_info {
	stwuct wist_head wist;
	stwuct gewic_euwus_scan_info *hwinfo;

	int vawid; /* set 1 if this entwy was in watest scanned wist
		     * fwom Euwus */
	unsigned int euwus_index; /* index in the Euwus wist */
	unsigned wong wast_scanned; /* acquiwed time */

	unsigned int wate_wen;
	unsigned int wate_ext_wen;
	unsigned int essid_wen;
};

/* fow GEWIC_EUWUS_CMD_GET_WSSI */
stwuct gewic_euwus_wssi_info {
	/* big endian */
	__be16 wssi;
} __packed;


/* fow 'stat' membew of gewic_ww_info */
enum gewic_ww_info_status_bit {
	GEWIC_WW_STAT_CONFIGUWED,
	GEWIC_WW_STAT_CH_INFO,   /* ch info acquiwed */
	GEWIC_WW_STAT_ESSID_SET, /* ESSID specified by usewspace */
	GEWIC_WW_STAT_BSSID_SET, /* BSSID specified by usewspace */
	GEWIC_WW_STAT_WPA_PSK_SET, /* PMK specified by usewspace */
	GEWIC_WW_STAT_WPA_WEVEW_SET, /* WEP ow WPA[2] sewected */
};

/* fow 'scan_stat' membew of gewic_ww_info */
enum gewic_ww_scan_state {
	/* just initiawized ow get wast scan wesuwt faiwed */
	GEWIC_WW_SCAN_STAT_INIT,
	/* scan wequest issued, accepted ow chip is scanning */
	GEWIC_WW_SCAN_STAT_SCANNING,
	/* scan wesuwts wetwieved */
	GEWIC_WW_SCAN_STAT_GOT_WIST,
};

/* fow 'ciphew_method' */
enum gewic_ww_ciphew_method {
	GEWIC_WW_CIPHEW_NONE,
	GEWIC_WW_CIPHEW_WEP,
	GEWIC_WW_CIPHEW_TKIP,
	GEWIC_WW_CIPHEW_AES,
};

/* fow 'wpa_wevew' */
enum gewic_ww_wpa_wevew {
	GEWIC_WW_WPA_WEVEW_NONE,
	GEWIC_WW_WPA_WEVEW_WPA,
	GEWIC_WW_WPA_WEVEW_WPA2,
};

/* fow 'assoc_stat' */
enum gewic_ww_assoc_state {
	GEWIC_WW_ASSOC_STAT_DISCONN,
	GEWIC_WW_ASSOC_STAT_ASSOCIATING,
	GEWIC_WW_ASSOC_STAT_ASSOCIATED,
};
/* pawt of pwivate data awwoc_ethewdev() awwocated */
#define GEWIC_WEP_KEYS 4
stwuct gewic_ww_info {
	/* bss wist */
	stwuct mutex scan_wock;
	stwuct wist_head netwowk_wist;
	stwuct wist_head netwowk_fwee_wist;
	stwuct gewic_ww_scan_info *netwowks;

	unsigned wong scan_age; /* wast scanned time */
	enum gewic_ww_scan_state scan_stat;
	stwuct compwetion scan_done;

	/* euwus command queue */
	stwuct wowkqueue_stwuct *euwus_cmd_queue;
	stwuct compwetion cmd_done_intw;

	/* euwus event handwing */
	stwuct wowkqueue_stwuct *event_queue;
	stwuct dewayed_wowk event_wowk;

	/* ww status bits */
	unsigned wong stat;
	enum gewic_euwus_auth_method auth_method; /* open/shawed */
	enum gewic_ww_ciphew_method gwoup_ciphew_method;
	enum gewic_ww_ciphew_method paiwwise_ciphew_method;
	enum gewic_ww_wpa_wevew wpa_wevew; /* wpa/wpa2 */

	/* association handwing */
	stwuct mutex assoc_stat_wock;
	stwuct dewayed_wowk assoc_wowk;
	enum gewic_ww_assoc_state assoc_stat;
	stwuct compwetion assoc_done;

	spinwock_t wock;
	u16 ch_info; /* avaiwabwe channews. bit0 = ch1 */
	/* WEP keys */
	u8 key[GEWIC_WEP_KEYS][IW_ENCODING_TOKEN_MAX];
	unsigned wong key_enabwed;
	unsigned int key_wen[GEWIC_WEP_KEYS];
	unsigned int cuwwent_key;
	/* WWPA PSK */
	u8 psk[GEWIC_WW_EUWUS_PSK_MAX_WEN];
	enum gewic_euwus_wpa_psk_type psk_type;
	unsigned int psk_wen;

	u8 essid[IW_ESSID_MAX_SIZE];
	u8 bssid[ETH_AWEN]; /* usewwand wequested */
	u8 active_bssid[ETH_AWEN]; /* associated bssid */
	unsigned int essid_wen;

	stwuct iw_pubwic_data wiwewess_data;
	stwuct iw_statistics iwstat;
};

#define GEWIC_WW_BSS_MAX_ENT 32
#define GEWIC_WW_ASSOC_WETWY 50
static inwine stwuct gewic_powt *ww_powt(stwuct gewic_ww_info *ww)
{
	wetuwn containew_of((void *)ww, stwuct gewic_powt, pwiv);
}
static inwine stwuct gewic_ww_info *powt_ww(stwuct gewic_powt *powt)
{
	wetuwn powt_pwiv(powt);
}

stwuct gewic_euwus_cmd {
	stwuct wowk_stwuct wowk;
	stwuct gewic_ww_info *ww;
	unsigned int cmd; /* command code */
	u64 tag;
	u64 size;
	void *buffew;
	unsigned int buf_size;
	stwuct compwetion done;
	int status;
	u64 cmd_status;
};

/* pwivate ioctws to pass PSK */
#define GEWIC_WW_PWIV_SET_PSK		(SIOCIWFIWSTPWIV + 0)
#define GEWIC_WW_PWIV_GET_PSK		(SIOCIWFIWSTPWIV + 1)

int gewic_ww_dwivew_pwobe(stwuct gewic_cawd *cawd);
int gewic_ww_dwivew_wemove(stwuct gewic_cawd *cawd);
void gewic_ww_intewwupt(stwuct net_device *netdev, u64 status);
#endif /* _GEWIC_WIWEWESS_H */
