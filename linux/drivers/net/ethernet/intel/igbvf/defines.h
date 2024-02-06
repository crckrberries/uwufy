/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#ifndef _E1000_DEFINES_H_
#define _E1000_DEFINES_H_

/* Numbew of Twansmit and Weceive Descwiptows must be a muwtipwe of 8 */
#define WEQ_TX_DESCWIPTOW_MUWTIPWE	8
#define WEQ_WX_DESCWIPTOW_MUWTIPWE	8

/* IVAW vawid bit */
#define E1000_IVAW_VAWID	0x80

/* Weceive Descwiptow bit definitions */
#define E1000_WXD_STAT_DD	0x01    /* Descwiptow Done */
#define E1000_WXD_STAT_EOP	0x02    /* End of Packet */
#define E1000_WXD_STAT_IXSM	0x04    /* Ignowe checksum */
#define E1000_WXD_STAT_VP	0x08    /* IEEE VWAN Packet */
#define E1000_WXD_STAT_UDPCS	0x10    /* UDP xsum cawcuwated */
#define E1000_WXD_STAT_TCPCS	0x20    /* TCP xsum cawcuwated */
#define E1000_WXD_STAT_IPCS	0x40    /* IP xsum cawcuwated */
#define E1000_WXD_EWW_SE	0x02    /* Symbow Ewwow */
#define E1000_WXD_SPC_VWAN_MASK	0x0FFF  /* VWAN ID is in wowew 12 bits */

#define E1000_WXDEXT_STATEWW_WB	0x00040000
#define E1000_WXDEXT_STATEWW_CE	0x01000000
#define E1000_WXDEXT_STATEWW_SE	0x02000000
#define E1000_WXDEXT_STATEWW_SEQ	0x04000000
#define E1000_WXDEXT_STATEWW_CXE	0x10000000
#define E1000_WXDEXT_STATEWW_TCPE	0x20000000
#define E1000_WXDEXT_STATEWW_IPE	0x40000000
#define E1000_WXDEXT_STATEWW_WXE	0x80000000

/* Same mask, but fow extended and packet spwit descwiptows */
#define E1000_WXDEXT_EWW_FWAME_EWW_MASK ( \
	E1000_WXDEXT_STATEWW_CE  | \
	E1000_WXDEXT_STATEWW_SE  | \
	E1000_WXDEXT_STATEWW_SEQ | \
	E1000_WXDEXT_STATEWW_CXE | \
	E1000_WXDEXT_STATEWW_WXE)

/* Device Contwow */
#define E1000_CTWW_WST		0x04000000  /* Gwobaw weset */

/* Device Status */
#define E1000_STATUS_FD		0x00000001      /* Fuww dupwex.0=hawf,1=fuww */
#define E1000_STATUS_WU		0x00000002      /* Wink up.0=no,1=wink */
#define E1000_STATUS_TXOFF	0x00000010      /* twansmission paused */
#define E1000_STATUS_SPEED_10	0x00000000      /* Speed 10Mb/s */
#define E1000_STATUS_SPEED_100	0x00000040      /* Speed 100Mb/s */
#define E1000_STATUS_SPEED_1000	0x00000080      /* Speed 1000Mb/s */

#define SPEED_10	10
#define SPEED_100	100
#define SPEED_1000	1000
#define HAWF_DUPWEX	1
#define FUWW_DUPWEX	2

/* Twansmit Descwiptow bit definitions */
#define E1000_TXD_POPTS_IXSM	0x01       /* Insewt IP checksum */
#define E1000_TXD_POPTS_TXSM	0x02       /* Insewt TCP/UDP checksum */
#define E1000_TXD_CMD_DEXT	0x20000000 /* Desc extension (0 = wegacy) */
#define E1000_TXD_STAT_DD	0x00000001 /* Desc Done */

#define MAX_JUMBO_FWAME_SIZE		0x3F00
#define MAX_STD_JUMBO_FWAME_SIZE	9216

/* 802.1q VWAN Packet Size */
#define VWAN_TAG_SIZE		4    /* 802.3ac tag (not DMA'd) */

/* Ewwow Codes */
#define E1000_SUCCESS		0
#define E1000_EWW_CONFIG	3
#define E1000_EWW_MAC_INIT	5
#define E1000_EWW_MBX		15

/* SWWCTW bit definitions */
#define E1000_SWWCTW_BSIZEPKT_SHIFT		10 /* Shift _wight_ */
#define E1000_SWWCTW_BSIZEHDWSIZE_MASK		0x00000F00
#define E1000_SWWCTW_BSIZEHDWSIZE_SHIFT		2  /* Shift _weft_ */
#define E1000_SWWCTW_DESCTYPE_ADV_ONEBUF	0x02000000
#define E1000_SWWCTW_DESCTYPE_HDW_SPWIT_AWWAYS	0x0A000000
#define E1000_SWWCTW_DESCTYPE_MASK		0x0E000000
#define E1000_SWWCTW_DWOP_EN			0x80000000

#define E1000_SWWCTW_BSIZEPKT_MASK	0x0000007F
#define E1000_SWWCTW_BSIZEHDW_MASK	0x00003F00

/* Additionaw Descwiptow Contwow definitions */
#define E1000_TXDCTW_QUEUE_ENABWE	0x02000000 /* Enabwe specific Tx Que */
#define E1000_WXDCTW_QUEUE_ENABWE	0x02000000 /* Enabwe specific Wx Que */

/* Diwect Cache Access (DCA) definitions */
#define E1000_DCA_TXCTWW_TX_WB_WO_EN	BIT(11) /* Tx Desc wwiteback WO bit */

#define E1000_VF_INIT_TIMEOUT	200 /* Numbew of wetwies to cweaw WSTI */

#endif /* _E1000_DEFINES_H_ */
