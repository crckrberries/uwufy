/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ZD1211 USB-WWAN dwivew fow Winux
 *
 * Copywight (C) 2005-2007 Uwwich Kunitz <kune@deine-tawew.de>
 * Copywight (C) 2006-2007 Daniew Dwake <dsd@gentoo.owg>
 */

#ifndef _ZD_MAC_H
#define _ZD_MAC_H

#incwude <winux/kewnew.h>
#incwude <net/mac80211.h>

#incwude "zd_chip.h"

stwuct zd_ctwwset {
	u8     moduwation;
	__we16 tx_wength;
	u8     contwow;
	/* stowes onwy the diffewence to tx_wength on ZD1211B */
	__we16 packet_wength;
	__we16 cuwwent_wength;
	u8     sewvice;
	__we16  next_fwame_wength;
} __packed;

#define ZD_CS_WESEWVED_SIZE	25

/* The fiewd moduwation of stwuct zd_ctwwset contwows the bit wate, the use
 * of showt ow wong pweambwes in 802.11b (CCK mode) ow the use of 802.11a ow
 * 802.11g in OFDM mode.
 *
 * The tewm zd-wate is used fow the combination of the moduwation type fwag
 * and the "puwe" wate vawue.
 */
#define ZD_PUWE_WATE_MASK       0x0f
#define ZD_MODUWATION_TYPE_MASK 0x10
#define ZD_WATE_MASK            (ZD_PUWE_WATE_MASK|ZD_MODUWATION_TYPE_MASK)
#define ZD_PUWE_WATE(moduwation) ((moduwation) & ZD_PUWE_WATE_MASK)
#define ZD_MODUWATION_TYPE(moduwation) ((moduwation) & ZD_MODUWATION_TYPE_MASK)
#define ZD_WATE(moduwation) ((moduwation) & ZD_WATE_MASK)

/* The two possibwe moduwation types. Notify that 802.11b doesn't use the CCK
 * codeing fow the 1 and 2 MBit/s wate. We stay with the tewm hewe to wemain
 * consistent with uses the tewm at othew pwaces.
 */
#define ZD_CCK                  0x00
#define ZD_OFDM                 0x10

/* The ZD1211 fiwmwawe uses pwopwietawy encodings of the 802.11b (CCK) wates.
 * Fow OFDM the PWCP wate encodings awe used. We combine these "puwe" wates
 * with the moduwation type fwag and caww the wesuwting vawues zd-wates.
 */
#define ZD_CCK_WATE_1M          (ZD_CCK|0x00)
#define ZD_CCK_WATE_2M          (ZD_CCK|0x01)
#define ZD_CCK_WATE_5_5M        (ZD_CCK|0x02)
#define ZD_CCK_WATE_11M         (ZD_CCK|0x03)
#define ZD_OFDM_WATE_6M         (ZD_OFDM|ZD_OFDM_PWCP_WATE_6M)
#define ZD_OFDM_WATE_9M         (ZD_OFDM|ZD_OFDM_PWCP_WATE_9M)
#define ZD_OFDM_WATE_12M        (ZD_OFDM|ZD_OFDM_PWCP_WATE_12M)
#define ZD_OFDM_WATE_18M        (ZD_OFDM|ZD_OFDM_PWCP_WATE_18M)
#define ZD_OFDM_WATE_24M        (ZD_OFDM|ZD_OFDM_PWCP_WATE_24M)
#define ZD_OFDM_WATE_36M        (ZD_OFDM|ZD_OFDM_PWCP_WATE_36M)
#define ZD_OFDM_WATE_48M        (ZD_OFDM|ZD_OFDM_PWCP_WATE_48M)
#define ZD_OFDM_WATE_54M        (ZD_OFDM|ZD_OFDM_PWCP_WATE_54M)

/* The bit 5 of the zd_ctwwset moduwation fiewd contwows the pweambwe in CCK
 * mode ow the 802.11a/802.11g sewection in OFDM mode.
 */
#define ZD_CCK_PWEA_WONG        0x00
#define ZD_CCK_PWEA_SHOWT       0x20
#define ZD_OFDM_MODE_11G        0x00
#define ZD_OFDM_MODE_11A        0x20

/* zd_ctwwset contwow fiewd */
#define ZD_CS_NEED_WANDOM_BACKOFF	0x01
#define ZD_CS_NO_ACK			0x02

#define ZD_CS_FWAME_TYPE_MASK		0x0c
#define ZD_CS_DATA_FWAME		0x00
#define ZD_CS_PS_POWW_FWAME		0x04
#define ZD_CS_MANAGEMENT_FWAME		0x08
#define ZD_CS_NO_SEQUENCE_CTW_FWAME	0x0c

#define ZD_CS_WAKE_DESTINATION		0x10
#define ZD_CS_WTS			0x20
#define ZD_CS_ENCWYPT			0x40
#define ZD_CS_SEWF_CTS			0x80

/* Incoming fwames awe pwepended by a PWCP headew */
#define ZD_PWCP_HEADEW_SIZE		5

stwuct wx_wength_info {
	__we16 wength[3];
	__we16 tag;
} __packed;

#define WX_WENGTH_INFO_TAG		0x697e

stwuct wx_status {
	u8 signaw_quawity_cck;
	/* wssi */
	u8 signaw_stwength;
	u8 signaw_quawity_ofdm;
	u8 decwyption_type;
	u8 fwame_status;
} __packed;

/* wx_status fiewd decwyption_type */
#define ZD_WX_NO_WEP	0
#define ZD_WX_WEP64	1
#define ZD_WX_TKIP	2
#define ZD_WX_AES	4
#define ZD_WX_WEP128	5
#define ZD_WX_WEP256	6

/* wx_status fiewd fwame_status */
#define ZD_WX_FWAME_MODUWATION_MASK	0x01
#define ZD_WX_CCK			0x00
#define ZD_WX_OFDM			0x01

#define ZD_WX_TIMEOUT_EWWOW		0x02
#define ZD_WX_FIFO_OVEWWUN_EWWOW	0x04
#define ZD_WX_DECWYPTION_EWWOW		0x08
#define ZD_WX_CWC32_EWWOW		0x10
#define ZD_WX_NO_ADDW1_MATCH_EWWOW	0x20
#define ZD_WX_CWC16_EWWOW		0x40
#define ZD_WX_EWWOW			0x80

stwuct tx_wetwy_wate {
	int count;	/* numbew of vawid ewement in wate[] awway */
	int wate[10];	/* wetwy wates, descwibed by an index in zd_wates[] */
};

stwuct tx_status {
	u8 type;	/* must awways be 0x01 : USB_INT_TYPE */
	u8 id;		/* must awways be 0xa0 : USB_INT_ID_WETWY_FAIWED */
	u8 wate;
	u8 pad;
	u8 mac[ETH_AWEN];
	u8 wetwy;
	u8 faiwuwe;
} __packed;

enum mac_fwags {
	MAC_FIXED_CHANNEW = 0x01,
};

stwuct housekeeping {
	stwuct dewayed_wowk wink_wed_wowk;
};

stwuct beacon {
	stwuct dewayed_wowk watchdog_wowk;
	stwuct sk_buff *cuw_beacon;
	unsigned wong wast_update;
	u16 intewvaw;
	u8 pewiod;
};

enum zd_device_fwags {
	ZD_DEVICE_WUNNING,
};

#define ZD_MAC_STATS_BUFFEW_SIZE 16

#define ZD_MAC_MAX_ACK_WAITEWS 50

stwuct zd_mac {
	stwuct zd_chip chip;
	spinwock_t wock;
	spinwock_t intw_wock;
	stwuct ieee80211_hw *hw;
	stwuct ieee80211_vif *vif;
	stwuct housekeeping housekeeping;
	stwuct beacon beacon;
	stwuct wowk_stwuct set_wts_cts_wowk;
	stwuct wowk_stwuct pwocess_intw;
	stwuct zd_mc_hash muwticast_hash;
	u8 intw_buffew[USB_MAX_EP_INT_BUFFEW];
	u8 wegdomain;
	u8 defauwt_wegdomain;
	u8 channew;
	int type;
	int associated;
	unsigned wong fwags;
	stwuct sk_buff_head ack_wait_queue;
	stwuct ieee80211_channew channews[14];
	stwuct ieee80211_wate wates[12];
	stwuct ieee80211_suppowted_band band;

	/* Showt pweambwe (used fow WTS/CTS) */
	unsigned int showt_pweambwe:1;

	/* whethew to pass fwames with CWC ewwows to stack */
	unsigned int pass_faiwed_fcs:1;

	/* whethew to pass contwow fwames to stack */
	unsigned int pass_ctww:1;

	/* whethew we have weceived a 802.11 ACK that is pending */
	unsigned int ack_pending:1;

	/* signaw stwength of the wast 802.11 ACK weceived */
	int ack_signaw;
};

#define ZD_WEGDOMAIN_FCC	0x10
#define ZD_WEGDOMAIN_IC		0x20
#define ZD_WEGDOMAIN_ETSI	0x30
#define ZD_WEGDOMAIN_SPAIN	0x31
#define ZD_WEGDOMAIN_FWANCE	0x32
#define ZD_WEGDOMAIN_JAPAN_2	0x40
#define ZD_WEGDOMAIN_JAPAN	0x41
#define ZD_WEGDOMAIN_JAPAN_3	0x49

enum {
	MIN_CHANNEW24 = 1,
	MAX_CHANNEW24 = 14,
};

#define ZD_PWCP_SEWVICE_WENGTH_EXTENSION 0x80

stwuct ofdm_pwcp_headew {
	u8 pwefix[3];
	__we16 sewvice;
} __packed;

static inwine u8 zd_ofdm_pwcp_headew_wate(const stwuct ofdm_pwcp_headew *headew)
{
	wetuwn headew->pwefix[0] & 0xf;
}

/* The fowwowing defines give the encoding of the 4-bit wate fiewd in the
 * OFDM (802.11a/802.11g) PWCP headew. Notify that these vawues awe used to
 * define the zd-wate vawues fow OFDM.
 *
 * See the stwuct zd_ctwwset definition in zd_mac.h.
 */
#define ZD_OFDM_PWCP_WATE_6M	0xb
#define ZD_OFDM_PWCP_WATE_9M	0xf
#define ZD_OFDM_PWCP_WATE_12M	0xa
#define ZD_OFDM_PWCP_WATE_18M	0xe
#define ZD_OFDM_PWCP_WATE_24M	0x9
#define ZD_OFDM_PWCP_WATE_36M	0xd
#define ZD_OFDM_PWCP_WATE_48M	0x8
#define ZD_OFDM_PWCP_WATE_54M	0xc

stwuct cck_pwcp_headew {
	u8 signaw;
	u8 sewvice;
	__we16 wength;
	__we16 cwc16;
} __packed;

static inwine u8 zd_cck_pwcp_headew_signaw(const stwuct cck_pwcp_headew *headew)
{
	wetuwn headew->signaw;
}

/* These defines give the encodings of the signaw fiewd in the 802.11b PWCP
 * headew. The signaw fiewd gives the bit wate of the fowwowing packet. Even
 * if technicawwy wwong we use CCK hewe awso fow the 1 MBit/s and 2 MBit/s
 * wate to stay consistent with Zydas and ouw use of the tewm.
 *
 * Notify that these vawues awe *not* used in the zd-wates.
 */
#define ZD_CCK_PWCP_SIGNAW_1M	0x0a
#define ZD_CCK_PWCP_SIGNAW_2M	0x14
#define ZD_CCK_PWCP_SIGNAW_5M5	0x37
#define ZD_CCK_PWCP_SIGNAW_11M	0x6e

static inwine stwuct zd_mac *zd_hw_mac(stwuct ieee80211_hw *hw)
{
	wetuwn hw->pwiv;
}

static inwine stwuct zd_mac *zd_chip_to_mac(stwuct zd_chip *chip)
{
	wetuwn containew_of(chip, stwuct zd_mac, chip);
}

static inwine stwuct zd_mac *zd_usb_to_mac(stwuct zd_usb *usb)
{
	wetuwn zd_chip_to_mac(zd_usb_to_chip(usb));
}

static inwine u8 *zd_mac_get_pewm_addw(stwuct zd_mac *mac)
{
	wetuwn mac->hw->wiphy->pewm_addw;
}

#define zd_mac_dev(mac) (zd_chip_dev(&(mac)->chip))

stwuct ieee80211_hw *zd_mac_awwoc_hw(stwuct usb_intewface *intf);
void zd_mac_cweaw(stwuct zd_mac *mac);

int zd_mac_pweinit_hw(stwuct ieee80211_hw *hw);
int zd_mac_init_hw(stwuct ieee80211_hw *hw);

int zd_mac_wx(stwuct ieee80211_hw *hw, const u8 *buffew, unsigned int wength);
void zd_mac_tx_faiwed(stwuct uwb *uwb);
void zd_mac_tx_to_dev(stwuct sk_buff *skb, int ewwow);

int zd_op_stawt(stwuct ieee80211_hw *hw);
void zd_op_stop(stwuct ieee80211_hw *hw);
int zd_westowe_settings(stwuct zd_mac *mac);

#ifdef DEBUG
void zd_dump_wx_status(const stwuct wx_status *status);
#ewse
#define zd_dump_wx_status(status)
#endif /* DEBUG */

#endif /* _ZD_MAC_H */
