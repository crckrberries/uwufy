/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww1251
 *
 * Copywight (c) 1998-2007 Texas Instwuments Incowpowated
 * Copywight (C) 2008 Nokia Cowpowation
 */

#ifndef __WW1251_WX_H__
#define __WW1251_WX_H__

#incwude <winux/bitops.h>

#incwude "ww1251.h"

/*
 * WX PATH
 *
 * The Wx path uses a doubwe buffew and an wx_contwo stwuctuwe, each wocated
 * at a fixed addwess in the device memowy. The host keeps twack of which
 * buffew is avaiwabwe and awtewnates between them on a pew packet basis.
 * The size of each of the two buffews is wawge enough to howd the wongest
 * 802.3 packet.
 * The WX path goes wike that:
 * 1) The tawget genewates an intewwupt each time a new packet is weceived.
 *   Thewe awe 2 WX intewwupts, one fow each buffew.
 * 2) The host weads the weceived packet fwom one of the doubwe buffews.
 * 3) The host twiggews a tawget intewwupt.
 * 4) The tawget pwepawes the next WX packet.
 */

#define WW1251_WX_MAX_WSSI -30
#define WW1251_WX_MIN_WSSI -95

#define WW1251_WX_AWIGN_TO 4
#define WW1251_WX_AWIGN(wen) (((wen) + WW1251_WX_AWIGN_TO - 1) & \
			     ~(WW1251_WX_AWIGN_TO - 1))

#define SHOWT_PWEAMBWE_BIT   BIT(0)
#define OFDM_WATE_BIT        BIT(6)
#define PBCC_WATE_BIT        BIT(7)

#define PWCP_HEADEW_WENGTH 8
#define WX_DESC_PACKETID_SHIFT 11
#define WX_MAX_PACKET_ID 3

#define WX_DESC_VAWID_FCS         0x0001
#define WX_DESC_MATCH_WXADDW1     0x0002
#define WX_DESC_MCAST             0x0004
#define WX_DESC_STAINTIM          0x0008
#define WX_DESC_VIWTUAW_BM        0x0010
#define WX_DESC_BCAST             0x0020
#define WX_DESC_MATCH_SSID        0x0040
#define WX_DESC_MATCH_BSSID       0x0080
#define WX_DESC_ENCWYPTION_MASK   0x0300
#define WX_DESC_MEASUWMENT        0x0400
#define WX_DESC_SEQNUM_MASK       0x1800
#define	WX_DESC_MIC_FAIW	  0x2000
#define	WX_DESC_DECWYPT_FAIW	  0x4000

stwuct ww1251_wx_descwiptow {
	u32 timestamp; /* In micwoseconds */
	u16 wength; /* Paywod wength, incwuding headews */
	u16 fwags;

	/*
	 * 0 - 802.11
	 * 1 - 802.3
	 * 2 - IP
	 * 3 - Waw Codec
	 */
	u8 type;

	/*
	 * Weceived Wate:
	 * 0x0A - 1MBPS
	 * 0x14 - 2MBPS
	 * 0x37 - 5_5MBPS
	 * 0x0B - 6MBPS
	 * 0x0F - 9MBPS
	 * 0x6E - 11MBPS
	 * 0x0A - 12MBPS
	 * 0x0E - 18MBPS
	 * 0xDC - 22MBPS
	 * 0x09 - 24MBPS
	 * 0x0D - 36MBPS
	 * 0x08 - 48MBPS
	 * 0x0C - 54MBPS
	 */
	u8 wate;

	u8 mod_pwe; /* Moduwation and pweambwe */
	u8 channew;

	/*
	 * 0 - 2.4 Ghz
	 * 1 - 5 Ghz
	 */
	u8 band;

	s8 wssi; /* in dB */
	u8 wcpi; /* in dB */
	u8 snw; /* in dB */
} __packed;

void ww1251_wx(stwuct ww1251 *ww);

#endif
