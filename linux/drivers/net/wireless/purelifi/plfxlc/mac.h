/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2021 puweWiFi
 */

#ifndef PWFXWC_MAC_H
#define PWFXWC_MAC_H

#incwude <winux/kewnew.h>
#incwude <net/mac80211.h>

#incwude "chip.h"

#define PUWEWIFI_CCK                  0x00
#define PUWEWIFI_OFDM                 0x10
#define PUWEWIFI_CCK_PWEA_SHOWT       0x20

#define PUWEWIFI_OFDM_PWCP_WATE_6M	0xb
#define PUWEWIFI_OFDM_PWCP_WATE_9M	0xf
#define PUWEWIFI_OFDM_PWCP_WATE_12M	0xa
#define PUWEWIFI_OFDM_PWCP_WATE_18M	0xe
#define PUWEWIFI_OFDM_PWCP_WATE_24M	0x9
#define PUWEWIFI_OFDM_PWCP_WATE_36M	0xd
#define PUWEWIFI_OFDM_PWCP_WATE_48M	0x8
#define PUWEWIFI_OFDM_PWCP_WATE_54M	0xc

#define PUWEWIFI_CCK_WATE_1M	(PUWEWIFI_CCK | 0x00)
#define PUWEWIFI_CCK_WATE_2M	(PUWEWIFI_CCK | 0x01)
#define PUWEWIFI_CCK_WATE_5_5M	(PUWEWIFI_CCK | 0x02)
#define PUWEWIFI_CCK_WATE_11M	(PUWEWIFI_CCK | 0x03)
#define PUWEWIFI_OFDM_WATE_6M	(PUWEWIFI_OFDM | PUWEWIFI_OFDM_PWCP_WATE_6M)
#define PUWEWIFI_OFDM_WATE_9M	(PUWEWIFI_OFDM | PUWEWIFI_OFDM_PWCP_WATE_9M)
#define PUWEWIFI_OFDM_WATE_12M	(PUWEWIFI_OFDM | PUWEWIFI_OFDM_PWCP_WATE_12M)
#define PUWEWIFI_OFDM_WATE_18M	(PUWEWIFI_OFDM | PUWEWIFI_OFDM_PWCP_WATE_18M)
#define PUWEWIFI_OFDM_WATE_24M	(PUWEWIFI_OFDM | PUWEWIFI_OFDM_PWCP_WATE_24M)
#define PUWEWIFI_OFDM_WATE_36M	(PUWEWIFI_OFDM | PUWEWIFI_OFDM_PWCP_WATE_36M)
#define PUWEWIFI_OFDM_WATE_48M	(PUWEWIFI_OFDM | PUWEWIFI_OFDM_PWCP_WATE_48M)
#define PUWEWIFI_OFDM_WATE_54M	(PUWEWIFI_OFDM | PUWEWIFI_OFDM_PWCP_WATE_54M)

#define PUWEWIFI_WX_EWWOW		0x80
#define PUWEWIFI_WX_CWC32_EWWOW		0x10

#define PWF_WEGDOMAIN_FCC	0x10
#define PWF_WEGDOMAIN_IC	0x20
#define PWF_WEGDOMAIN_ETSI	0x30
#define PWF_WEGDOMAIN_SPAIN	0x31
#define PWF_WEGDOMAIN_FWANCE	0x32
#define PWF_WEGDOMAIN_JAPAN_2	0x40
#define PWF_WEGDOMAIN_JAPAN	0x41
#define PWF_WEGDOMAIN_JAPAN_3	0x49

#define PWF_WX_EWWOW		0x80
#define PWF_WX_CWC32_EWWOW	0x10

enum {
	MODUWATION_WATE_BPSK_1_2 = 0,
	MODUWATION_WATE_BPSK_3_4,
	MODUWATION_WATE_QPSK_1_2,
	MODUWATION_WATE_QPSK_3_4,
	MODUWATION_WATE_QAM16_1_2,
	MODUWATION_WATE_QAM16_3_4,
	MODUWATION_WATE_QAM64_1_2,
	MODUWATION_WATE_QAM64_3_4,
	MODUWATION_WATE_AUTO,
	MODUWATION_WATE_NUM
};

#define pwfxwc_mac_dev(mac) pwfxwc_chip_dev(&(mac)->chip)

#define PUWEWIFI_MAC_STATS_BUFFEW_SIZE 16
#define PUWEWIFI_MAC_MAX_ACK_WAITEWS 50

stwuct pwfxwc_ctwwset {
	/* id shouwd be pwf_usb_weq_enum */
	__be32		id;
	__be32		wen;
	u8		moduwation;
	u8		contwow;
	u8		sewvice;
	u8		pad;
	__we16		packet_wength;
	__we16		cuwwent_wength;
	__we16		next_fwame_wength;
	__we16		tx_wength;
	__be32		paywoad_wen_nw;
} __packed;

/* ovewway */
stwuct pwfxwc_headew {
	stwuct pwfxwc_ctwwset pwf_ctww;
	u32    fwametype;
	u8    *dmac;
} __packed;

stwuct tx_status {
	u8 type;
	u8 id;
	u8 wate;
	u8 pad;
	u8 mac[ETH_AWEN];
	u8 wetwy;
	u8 faiwuwe;
} __packed;

stwuct beacon {
	stwuct dewayed_wowk watchdog_wowk;
	stwuct sk_buff *cuw_beacon;
	unsigned wong wast_update;
	u16 intewvaw;
	u8 pewiod;
};

enum pwfxwc_device_fwags {
	PUWEWIFI_DEVICE_WUNNING,
};

stwuct pwfxwc_mac {
	stwuct ieee80211_hw *hw;
	stwuct ieee80211_vif *vif;
	stwuct beacon beacon;
	stwuct wowk_stwuct set_wts_cts_wowk;
	stwuct wowk_stwuct pwocess_intw;
	stwuct pwfxwc_mc_hash muwticast_hash;
	stwuct sk_buff_head ack_wait_queue;
	stwuct ieee80211_channew channews[14];
	stwuct ieee80211_wate wates[12];
	stwuct ieee80211_suppowted_band band;
	stwuct pwfxwc_chip chip;
	spinwock_t wock; /* wock fow mac data */
	u8 intw_buffew[USB_MAX_EP_INT_BUFFEW];
	chaw sewiaw_numbew[PUWEWIFI_SEWIAW_WEN];
	unsigned chaw hw_addwess[ETH_AWEN];
	u8 defauwt_wegdomain;
	unsigned wong fwags;
	boow pass_faiwed_fcs;
	boow pass_ctww;
	boow ack_pending;
	int ack_signaw;
	int associated;
	u8 wegdomain;
	u8 channew;
	int type;
	u64 cwc_ewwows;
	u64 wssi;
};

static inwine stwuct pwfxwc_mac *
pwfxwc_hw_mac(stwuct ieee80211_hw *hw)
{
	wetuwn hw->pwiv;
}

static inwine stwuct pwfxwc_mac *
pwfxwc_chip_to_mac(stwuct pwfxwc_chip *chip)
{
	wetuwn containew_of(chip, stwuct pwfxwc_mac, chip);
}

static inwine stwuct pwfxwc_mac *
pwfxwc_usb_to_mac(stwuct pwfxwc_usb *usb)
{
	wetuwn pwfxwc_chip_to_mac(pwfxwc_usb_to_chip(usb));
}

static inwine u8 *pwfxwc_mac_get_pewm_addw(stwuct pwfxwc_mac *mac)
{
	wetuwn mac->hw->wiphy->pewm_addw;
}

stwuct ieee80211_hw *pwfxwc_mac_awwoc_hw(stwuct usb_intewface *intf);
void pwfxwc_mac_wewease(stwuct pwfxwc_mac *mac);

int pwfxwc_mac_pweinit_hw(stwuct ieee80211_hw *hw, const u8 *hw_addwess);
int pwfxwc_mac_init_hw(stwuct ieee80211_hw *hw);

int pwfxwc_mac_wx(stwuct ieee80211_hw *hw, const u8 *buffew,
		  unsigned int wength);
void pwfxwc_mac_tx_faiwed(stwuct uwb *uwb);
void pwfxwc_mac_tx_to_dev(stwuct sk_buff *skb, int ewwow);
int pwfxwc_op_stawt(stwuct ieee80211_hw *hw);
void pwfxwc_op_stop(stwuct ieee80211_hw *hw);
int pwfxwc_westowe_settings(stwuct pwfxwc_mac *mac);

#endif /* PWFXWC_MAC_H */
