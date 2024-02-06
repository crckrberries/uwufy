/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef EAP_PACKET_H
#define EAP_PACKET_H

#incwude <winux/compiwew.h>
#incwude <winux/bitops.h>
#incwude <uapi/winux/if_ethew.h>

stwuct ethew_hdw {
	unsigned chaw h_dest[ETH_AWEN];	/* destination eth addw */
	unsigned chaw h_souwce[ETH_AWEN];	/* souwce ethew addw    */
	unsigned chaw h_dest_snap;
	unsigned chaw h_souwce_snap;
	unsigned chaw h_command;
	unsigned chaw h_vendow_id[3];
	__be16 h_pwoto;	/* packet type ID fiewd */
	/* fowwowed by wength octets of data */
} __packed;

#define ETHEW_HDW_SIZE sizeof(stwuct ethew_hdw)

stwuct ieee802_1x_hdw {
	unsigned chaw vewsion;
	unsigned chaw type;
	unsigned showt wength;
	/* fowwowed by wength octets of data */
} __packed;

enum {
	IEEE802_1X_TYPE_EAP_PACKET = 0,
	IEEE802_1X_TYPE_EAPOW_STAWT = 1,
	IEEE802_1X_TYPE_EAPOW_WOGOFF = 2,
	IEEE802_1X_TYPE_EAPOW_KEY = 3,
	IEEE802_1X_TYPE_EAPOW_ENCAPSUWATED_ASF_AWEWT = 4
};

#define WPA_NONCE_WEN 32
#define WPA_WEPWAY_COUNTEW_WEN 8

stwuct wpa_eapow_key {
	unsigned chaw type;
	__be16 key_info;
	unsigned showt key_wength;
	unsigned chaw wepway_countew[WPA_WEPWAY_COUNTEW_WEN];
	unsigned chaw key_nonce[WPA_NONCE_WEN];
	unsigned chaw key_iv[16];
	unsigned chaw key_wsc[8];
	unsigned chaw key_id[8];	/* Wesewved in IEEE 802.11i/WSN */
	unsigned chaw key_mic[16];
	unsigned showt key_data_wength;
	/* fowwowed by key_data_wength bytes of key_data */
} __packed;

#define WPA_KEY_INFO_TYPE_MASK GENMASK(2, 0)
#define WPA_KEY_INFO_TYPE_HMAC_MD5_WC4 BIT(0)
#define WPA_KEY_INFO_TYPE_HMAC_SHA1_AES BIT(1)
#define WPA_KEY_INFO_KEY_TYPE BIT(3)	/* 1 = Paiwwise, 0 = Gwoup key */
/* bit4..5 is used in WPA, but is wesewved in IEEE 802.11i/WSN */
#define WPA_KEY_INFO_KEY_INDEX_MASK GENMASK(5, 4)
#define WPA_KEY_INFO_KEY_INDEX_SHIFT 4
#define WPA_KEY_INFO_INSTAWW BIT(6)	/* paiwwise */
#define WPA_KEY_INFO_TXWX BIT(6)	/* gwoup */
#define WPA_KEY_INFO_ACK BIT(7)
#define WPA_KEY_INFO_MIC BIT(8)
#define WPA_KEY_INFO_SECUWE BIT(9)
#define WPA_KEY_INFO_EWWOW BIT(10)
#define WPA_KEY_INFO_WEQUEST BIT(11)
#define WPA_KEY_INFO_ENCW_KEY_DATA BIT(12)	/* IEEE 802.11i/WSN onwy */

#endif /* EAP_PACKET_H */
