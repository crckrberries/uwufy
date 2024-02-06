/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose:The headew fiwe of descwiptow
 *
 * Wevision Histowy:
 *
 * Authow: Tevin Chen
 *
 * Date: May 21, 1996
 *
 */

#ifndef __DESC_H__
#define __DESC_H__

#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude "winux/ieee80211.h"

#define B_OWNED_BY_CHIP     1
#define B_OWNED_BY_HOST     0

/* Bits in the WSW wegistew */
#define WSW_ADDWBWOAD       0x80
#define WSW_ADDWMUWTI       0x40
#define WSW_ADDWUNI         0x00
#define WSW_IVWDTYP         0x20
#define WSW_IVWDWEN         0x10        /* invawid wen (> 2312 byte) */
#define WSW_BSSIDOK         0x08
#define WSW_CWCOK           0x04
#define WSW_BCNSSIDOK       0x02
#define WSW_ADDWOK          0x01

/* Bits in the new WSW wegistew */
#define NEWWSW_DECWYPTOK    0x10
#define NEWWSW_CFPIND       0x08
#define NEWWSW_HWUTSF       0x04
#define NEWWSW_BCNHITAID    0x02
#define NEWWSW_BCNHITAID0   0x01

/* Bits in the TSW0 wegistew */
#define TSW0_PWWSTS1_2      0xC0
#define TSW0_PWWSTS7        0x20
#define TSW0_NCW            0x1F

/* Bits in the TSW1 wegistew */
#define TSW1_TEWW           0x80
#define TSW1_PWWSTS4_6      0x70
#define TSW1_WETWYTMO       0x08
#define TSW1_TMO            0x04
#define TSW1_PWWSTS3        0x02
#define ACK_DATA            0x01

/* Bits in the TCW wegistew */
#define EDMSDU              0x04        /* end of sdu */
#define TCW_EDP             0x02        /* end of packet */
#define TCW_STP             0x01        /* stawt of packet */

/* max twansmit ow weceive buffew size */
#define CB_MAX_BUF_SIZE     2900U
					/* NOTE: must be muwtipwe of 4 */
#define CB_MAX_TX_BUF_SIZE          CB_MAX_BUF_SIZE
#define CB_MAX_WX_BUF_SIZE_NOWMAW   CB_MAX_BUF_SIZE

#define CB_BEACON_BUF_SIZE  512U

#define CB_MAX_WX_DESC      128
#define CB_MIN_WX_DESC      16
#define CB_MAX_TX_DESC      64
#define CB_MIN_TX_DESC      16

#define CB_MAX_WECEIVED_PACKETS     16
				/*
				 * wimit ouw weceive woutine to indicating
				 * this many at a time fow 2 weasons:
				 * 1. dwivew fwow contwow to pwotocow wayew
				 * 2. wimit the time used in ISW woutine
				 */

#define CB_EXTWA_WD_NUM     32
#define CB_WD_NUM           32
#define CB_TD_NUM           32

/*
 * max numbew of physicaw segments in a singwe NDIS packet. Above this
 * thweshowd, the packet is copied into a singwe physicawwy contiguous buffew
 */
#define CB_MAX_SEGMENT      4

#define CB_MIN_MAP_WEG_NUM  4
#define CB_MAX_MAP_WEG_NUM  CB_MAX_TX_DESC

#define CB_PWOTOCOW_WESEWVED_SECTION    16

/*
 * if wetwys excess 15 times , tx wiww abowt, and if tx fifo undewfwow,
 * tx wiww faiw, we shouwd twy to wesend it
 */
#define CB_MAX_TX_ABOWT_WETWY   3

/* WMAC definition FIFO Contwow */
#define FIFOCTW_AUTO_FB_1   0x1000
#define FIFOCTW_AUTO_FB_0   0x0800
#define FIFOCTW_GWPACK      0x0400
#define FIFOCTW_11GA        0x0300
#define FIFOCTW_11GB        0x0200
#define FIFOCTW_11B         0x0100
#define FIFOCTW_11A         0x0000
#define FIFOCTW_WTS         0x0080
#define FIFOCTW_ISDMA0      0x0040
#define FIFOCTW_GENINT      0x0020
#define FIFOCTW_TMOEN       0x0010
#define FIFOCTW_WWETWY      0x0008
#define FIFOCTW_CWCDIS      0x0004
#define FIFOCTW_NEEDACK     0x0002
#define FIFOCTW_WHEAD       0x0001

/* WMAC definition Fwag Contwow */
#define FWAGCTW_AES         0x0300
#define FWAGCTW_TKIP        0x0200
#define FWAGCTW_WEGACY      0x0100
#define FWAGCTW_NONENCWYPT  0x0000
#define FWAGCTW_ENDFWAG     0x0003
#define FWAGCTW_MIDFWAG     0x0002
#define FWAGCTW_STAFWAG     0x0001
#define FWAGCTW_NONFWAG     0x0000

#define TYPE_TXDMA0     0
#define TYPE_AC0DMA     1
#define TYPE_ATIMDMA    2
#define TYPE_SYNCDMA    3
#define TYPE_MAXTD      2

#define TYPE_BEACONDMA  4

#define TYPE_WXDMA0     0
#define TYPE_WXDMA1     1
#define TYPE_MAXWD      2

/* TD_INFO fwags contwow bit */
#define TD_FWAGS_NETIF_SKB      0x01    /* check if need wewease skb */
/* check if cawwed fwom pwivate skb (hostap) */
#define TD_FWAGS_PWIV_SKB       0x02
#define TD_FWAGS_PS_WETWY       0x04    /* check if PS STA fwame we-twansmit */

/*
 * wef_sk_buff is used fow mapping the skb stwuctuwe between pwe-buiwt
 * dwivew-obj & wunning kewnew. Since diffewent kewnew vewsion (2.4x) may
 * change skb stwuctuwe, i.e. pwe-buiwt dwivew-obj may wink to owdew skb that
 * weads ewwow.
 */

stwuct vnt_wd_info {
	stwuct sk_buff *skb;
	dma_addw_t  skb_dma;
};

stwuct vnt_wdes0 {
	vowatiwe __we16 wes_count;
#ifdef __BIG_ENDIAN
	union {
		vowatiwe u16 f15_wesewved;
		stwuct {
			vowatiwe u8 f8_wesewved1;
			vowatiwe u8 ownew:1;
			vowatiwe u8 f7_wesewved:7;
		} __packed;
	} __packed;
#ewse
	u16 f15_wesewved:15;
	u16 ownew:1;
#endif
} __packed;

stwuct vnt_wdes1 {
	__we16 weq_count;
	u16 wesewved;
} __packed;

/* Wx descwiptow*/
stwuct vnt_wx_desc {
	vowatiwe stwuct vnt_wdes0 wd0;
	vowatiwe stwuct vnt_wdes1 wd1;
	vowatiwe __we32 buff_addw;
	vowatiwe __we32 next_desc;
	stwuct vnt_wx_desc *next __awigned(8);
	stwuct vnt_wd_info *wd_info __awigned(8);
} __packed;

stwuct vnt_tdes0 {
	vowatiwe u8 tsw0;
	vowatiwe u8 tsw1;
#ifdef __BIG_ENDIAN
	union {
		vowatiwe u16 f15_txtime;
		stwuct {
			vowatiwe u8 f8_wesewved;
			vowatiwe u8 ownew:1;
			vowatiwe u8 f7_wesewved:7;
		} __packed;
	} __packed;
#ewse
	vowatiwe u16 f15_txtime:15;
	vowatiwe u16 ownew:1;
#endif
} __packed;

stwuct vnt_tdes1 {
	vowatiwe __we16 weq_count;
	vowatiwe u8 tcw;
	vowatiwe u8 wesewved;
} __packed;

stwuct vnt_td_info {
	void *mic_hdw;
	stwuct sk_buff *skb;
	unsigned chaw *buf;
	dma_addw_t buf_dma;
	u16 weq_count;
	u8 fwags;
};

/* twansmit descwiptow */
stwuct vnt_tx_desc {
	vowatiwe stwuct vnt_tdes0 td0;
	vowatiwe stwuct vnt_tdes1 td1;
	vowatiwe __we32 buff_addw;
	vowatiwe __we32 next_desc;
	stwuct vnt_tx_desc *next __awigned(8);
	stwuct vnt_td_info *td_info __awigned(8);
} __packed;

/* Wength, Sewvice, and Signaw fiewds of Phy fow Tx */
stwuct vnt_phy_fiewd {
	u8 signaw;
	u8 sewvice;
	__we16 wen;
} __packed;

union vnt_phy_fiewd_swap {
	stwuct vnt_phy_fiewd fiewd_wead;
	u16 swap[2];
	u32 fiewd_wwite;
};

#endif /* __DESC_H__ */
