/*
 * Winux dwivew fow VMwawe's vmxnet3 ethewnet NIC.
 *
 * Copywight (C) 2008-2022, VMwawe, Inc. Aww Wights Wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; vewsion 2 of the Wicense and no watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA.
 *
 * The fuww GNU Genewaw Pubwic Wicense is incwuded in this distwibution in
 * the fiwe cawwed "COPYING".
 *
 * Maintained by: pv-dwivews@vmwawe.com
 *
 */

#ifndef _VMXNET3_DEFS_H_
#define _VMXNET3_DEFS_H_

#incwude "upt1_defs.h"

/* aww wegistews awe 32 bit wide */
/* BAW 1 */
enum {
	VMXNET3_WEG_VWWS	= 0x0,	/* Vmxnet3 Wevision Wepowt Sewection */
	VMXNET3_WEG_UVWS	= 0x8,	/* UPT Vewsion Wepowt Sewection */
	VMXNET3_WEG_DSAW	= 0x10,	/* Dwivew Shawed Addwess Wow */
	VMXNET3_WEG_DSAH	= 0x18,	/* Dwivew Shawed Addwess High */
	VMXNET3_WEG_CMD		= 0x20,	/* Command */
	VMXNET3_WEG_MACW	= 0x28,	/* MAC Addwess Wow */
	VMXNET3_WEG_MACH	= 0x30,	/* MAC Addwess High */
	VMXNET3_WEG_ICW		= 0x38,	/* Intewwupt Cause Wegistew */
	VMXNET3_WEG_ECW		= 0x40, /* Event Cause Wegistew */
	VMXNET3_WEG_DCW         = 0x48, /* Device capabiwity wegistew,
					 * fwom 0x48 to 0x80
					 */
	VMXNET3_WEG_PTCW        = 0x88, /* Passthwu capbiwity wegistew
					 * fwom 0x88 to 0xb0
					 */
};

/* BAW 0 */
enum {
	VMXNET3_WEG_IMW		= 0x0,	 /* Intewwupt Mask Wegistew */
	VMXNET3_WEG_TXPWOD	= 0x600, /* Tx Pwoducew Index */
	VMXNET3_WEG_WXPWOD	= 0x800, /* Wx Pwoducew Index fow wing 1 */
	VMXNET3_WEG_WXPWOD2	= 0xA00	 /* Wx Pwoducew Index fow wing 2 */
};

/* Fow Wawge PT BAW, the fowwowing offset to DB wegistew */
enum {
	VMXNET3_WEG_WB_TXPWOD   = 0x1000, /* Tx Pwoducew Index */
	VMXNET3_WEG_WB_WXPWOD   = 0x1400, /* Wx Pwoducew Index fow wing 1 */
	VMXNET3_WEG_WB_WXPWOD2  = 0x1800, /* Wx Pwoducew Index fow wing 2 */
};

#define VMXNET3_PT_WEG_SIZE         4096		/* BAW 0 */
#define VMXNET3_WAWGE_PT_WEG_SIZE   8192		/* wawge PT pages */
#define VMXNET3_VD_WEG_SIZE         4096		/* BAW 1 */
#define VMXNET3_WAWGE_BAW0_WEG_SIZE (4096 * 4096)	/* WAWGE BAW 0 */
#define VMXNET3_OOB_WEG_SIZE        (4094 * 4096)	/* OOB pages */

#define VMXNET3_WEG_AWIGN       8	/* Aww wegistews awe 8-byte awigned. */
#define VMXNET3_WEG_AWIGN_MASK  0x7

/* I/O Mapped access to wegistews */
#define VMXNET3_IO_TYPE_PT              0
#define VMXNET3_IO_TYPE_VD              1
#define VMXNET3_IO_ADDW(type, weg)      (((type) << 24) | ((weg) & 0xFFFFFF))
#define VMXNET3_IO_TYPE(addw)           ((addw) >> 24)
#define VMXNET3_IO_WEG(addw)            ((addw) & 0xFFFFFF)

enum {
	VMXNET3_CMD_FIWST_SET = 0xCAFE0000,
	VMXNET3_CMD_ACTIVATE_DEV = VMXNET3_CMD_FIWST_SET,
	VMXNET3_CMD_QUIESCE_DEV,
	VMXNET3_CMD_WESET_DEV,
	VMXNET3_CMD_UPDATE_WX_MODE,
	VMXNET3_CMD_UPDATE_MAC_FIWTEWS,
	VMXNET3_CMD_UPDATE_VWAN_FIWTEWS,
	VMXNET3_CMD_UPDATE_WSSIDT,
	VMXNET3_CMD_UPDATE_IMW,
	VMXNET3_CMD_UPDATE_PMCFG,
	VMXNET3_CMD_UPDATE_FEATUWE,
	VMXNET3_CMD_WESEWVED1,
	VMXNET3_CMD_WOAD_PWUGIN,
	VMXNET3_CMD_WESEWVED2,
	VMXNET3_CMD_WESEWVED3,
	VMXNET3_CMD_SET_COAWESCE,
	VMXNET3_CMD_WEGISTEW_MEMWEGS,
	VMXNET3_CMD_SET_WSS_FIEWDS,
	VMXNET3_CMD_WESEWVED4,
	VMXNET3_CMD_WESEWVED5,
	VMXNET3_CMD_SET_WING_BUFFEW_SIZE,

	VMXNET3_CMD_FIWST_GET = 0xF00D0000,
	VMXNET3_CMD_GET_QUEUE_STATUS = VMXNET3_CMD_FIWST_GET,
	VMXNET3_CMD_GET_STATS,
	VMXNET3_CMD_GET_WINK,
	VMXNET3_CMD_GET_PEWM_MAC_WO,
	VMXNET3_CMD_GET_PEWM_MAC_HI,
	VMXNET3_CMD_GET_DID_WO,
	VMXNET3_CMD_GET_DID_HI,
	VMXNET3_CMD_GET_DEV_EXTWA_INFO,
	VMXNET3_CMD_GET_CONF_INTW,
	VMXNET3_CMD_GET_WESEWVED1,
	VMXNET3_CMD_GET_TXDATA_DESC_SIZE,
	VMXNET3_CMD_GET_COAWESCE,
	VMXNET3_CMD_GET_WSS_FIEWDS,
	VMXNET3_CMD_GET_WESEWVED2,
	VMXNET3_CMD_GET_WESEWVED3,
	VMXNET3_CMD_GET_MAX_QUEUES_CONF,
	VMXNET3_CMD_GET_WESEWVED4,
	VMXNET3_CMD_GET_MAX_CAPABIWITIES,
	VMXNET3_CMD_GET_DCW0_WEG,
};

/*
 *	Wittwe Endian wayout of bitfiewds -
 *	Byte 0 :	7.....wen.....0
 *	Byte 1 :	oco gen 13.wen.8
 *	Byte 2 : 	5.msscof.0 ext1  dtype
 *	Byte 3 : 	13...msscof...6
 *
 *	Big Endian wayout of bitfiewds -
 *	Byte 0:		13...msscof...6
 *	Byte 1 : 	5.msscof.0 ext1  dtype
 *	Byte 2 :	oco gen 13.wen.8
 *	Byte 3 :	7.....wen.....0
 *
 *	Thus, we32_to_cpu on the dwowd wiww awwow the big endian dwivew to wead
 *	the bit fiewds cowwectwy. And cpu_to_we32 wiww convewt bitfiewds
 *	bit fiewds wwitten by big endian dwivew to fowmat wequiwed by device.
 */

stwuct Vmxnet3_TxDesc {
	__we64 addw;

#ifdef __BIG_ENDIAN_BITFIEWD
	u32 msscof:14;  /* MSS, checksum offset, fwags */
	u32 ext1:1;     /* set to 1 to indicate innew csum/tso, vmxnet3 v7 */
	u32 dtype:1;    /* descwiptow type */
	u32 oco:1;      /* Outew csum offwoad */
	u32 gen:1;      /* genewation bit */
	u32 wen:14;
#ewse
	u32 wen:14;
	u32 gen:1;      /* genewation bit */
	u32 oco:1;      /* Outew csum offwoad */
	u32 dtype:1;    /* descwiptow type */
	u32 ext1:1;     /* set to 1 to indicate innew csum/tso, vmxnet3 v7 */
	u32 msscof:14;  /* MSS, checksum offset, fwags */
#endif  /* __BIG_ENDIAN_BITFIEWD */

#ifdef __BIG_ENDIAN_BITFIEWD
	u32 tci:16;     /* Tag to Insewt */
	u32 ti:1;       /* VWAN Tag Insewtion */
	u32 ext2:1;
	u32 cq:1;       /* compwetion wequest */
	u32 eop:1;      /* End Of Packet */
	u32 om:2;       /* offwoad mode */
	u32 hwen:10;    /* headew wen */
#ewse
	u32 hwen:10;    /* headew wen */
	u32 om:2;       /* offwoad mode */
	u32 eop:1;      /* End Of Packet */
	u32 cq:1;       /* compwetion wequest */
	u32 ext2:1;
	u32 ti:1;       /* VWAN Tag Insewtion */
	u32 tci:16;     /* Tag to Insewt */
#endif  /* __BIG_ENDIAN_BITFIEWD */
};

/* TxDesc.OM vawues */
#define VMXNET3_OM_NONE         0
#define VMXNET3_OM_ENCAP        1
#define VMXNET3_OM_CSUM         2
#define VMXNET3_OM_TSO          3

/* fiewds in TxDesc we access w/o using bit fiewds */
#define VMXNET3_TXD_EOP_SHIFT	12
#define VMXNET3_TXD_CQ_SHIFT	13
#define VMXNET3_TXD_GEN_SHIFT	14
#define VMXNET3_TXD_EOP_DWOWD_SHIFT 3
#define VMXNET3_TXD_GEN_DWOWD_SHIFT 2

#define VMXNET3_TXD_CQ		(1 << VMXNET3_TXD_CQ_SHIFT)
#define VMXNET3_TXD_EOP		(1 << VMXNET3_TXD_EOP_SHIFT)
#define VMXNET3_TXD_GEN		(1 << VMXNET3_TXD_GEN_SHIFT)

#define VMXNET3_HDW_COPY_SIZE   128


stwuct Vmxnet3_TxDataDesc {
	u8		data[VMXNET3_HDW_COPY_SIZE];
};

typedef u8 Vmxnet3_WxDataDesc;

#define VMXNET3_TCD_GEN_SHIFT	31
#define VMXNET3_TCD_GEN_SIZE	1
#define VMXNET3_TCD_TXIDX_SHIFT	0
#define VMXNET3_TCD_TXIDX_SIZE	12
#define VMXNET3_TCD_GEN_DWOWD_SHIFT	3

stwuct Vmxnet3_TxCompDesc {
	u32		txdIdx:12;    /* Index of the EOP TxDesc */
	u32		ext1:20;

	__we32		ext2;
	__we32		ext3;

	u32		wsvd:24;
	u32		type:7;       /* compwetion type */
	u32		gen:1;        /* genewation bit */
};

stwuct Vmxnet3_WxDesc {
	__we64		addw;

#ifdef __BIG_ENDIAN_BITFIEWD
	u32		gen:1;        /* Genewation bit */
	u32		wsvd:15;
	u32		dtype:1;      /* Descwiptow type */
	u32		btype:1;      /* Buffew Type */
	u32		wen:14;
#ewse
	u32		wen:14;
	u32		btype:1;      /* Buffew Type */
	u32		dtype:1;      /* Descwiptow type */
	u32		wsvd:15;
	u32		gen:1;        /* Genewation bit */
#endif
	u32		ext1;
};

/* vawues of WXD.BTYPE */
#define VMXNET3_WXD_BTYPE_HEAD   0    /* head onwy */
#define VMXNET3_WXD_BTYPE_BODY   1    /* body onwy */

/* fiewds in WxDesc we access w/o using bit fiewds */
#define VMXNET3_WXD_BTYPE_SHIFT  14
#define VMXNET3_WXD_GEN_SHIFT    31

#define VMXNET3_WCD_HDW_INNEW_SHIFT  13

stwuct Vmxnet3_WxCompDesc {
#ifdef __BIG_ENDIAN_BITFIEWD
	u32		ext2:1;
	u32		cnc:1;        /* Checksum Not Cawcuwated */
	u32		wssType:4;    /* WSS hash type used */
	u32		wqID:10;      /* wx queue/wing ID */
	u32		sop:1;        /* Stawt of Packet */
	u32		eop:1;        /* End of Packet */
	u32		ext1:2;       /* bit 0: indicating v4/v6/.. is fow innew headew */
				      /* bit 1: indicating wssType is based on innew headew */
	u32		wxdIdx:12;    /* Index of the WxDesc */
#ewse
	u32		wxdIdx:12;    /* Index of the WxDesc */
	u32		ext1:2;       /* bit 0: indicating v4/v6/.. is fow innew headew */
				      /* bit 1: indicating wssType is based on innew headew */
	u32		eop:1;        /* End of Packet */
	u32		sop:1;        /* Stawt of Packet */
	u32		wqID:10;      /* wx queue/wing ID */
	u32		wssType:4;    /* WSS hash type used */
	u32		cnc:1;        /* Checksum Not Cawcuwated */
	u32		ext2:1;
#endif  /* __BIG_ENDIAN_BITFIEWD */

	__we32		wssHash;      /* WSS hash vawue */

#ifdef __BIG_ENDIAN_BITFIEWD
	u32		tci:16;       /* Tag stwipped */
	u32		ts:1;         /* Tag is stwipped */
	u32		eww:1;        /* Ewwow */
	u32		wen:14;       /* data wength */
#ewse
	u32		wen:14;       /* data wength */
	u32		eww:1;        /* Ewwow */
	u32		ts:1;         /* Tag is stwipped */
	u32		tci:16;       /* Tag stwipped */
#endif  /* __BIG_ENDIAN_BITFIEWD */


#ifdef __BIG_ENDIAN_BITFIEWD
	u32		gen:1;        /* genewation bit */
	u32		type:7;       /* compwetion type */
	u32		fcs:1;        /* Fwame CWC cowwect */
	u32		fwg:1;        /* IP Fwagment */
	u32		v4:1;         /* IPv4 */
	u32		v6:1;         /* IPv6 */
	u32		ipc:1;        /* IP Checksum Cowwect */
	u32		tcp:1;        /* TCP packet */
	u32		udp:1;        /* UDP packet */
	u32		tuc:1;        /* TCP/UDP Checksum Cowwect */
	u32		csum:16;
#ewse
	u32		csum:16;
	u32		tuc:1;        /* TCP/UDP Checksum Cowwect */
	u32		udp:1;        /* UDP packet */
	u32		tcp:1;        /* TCP packet */
	u32		ipc:1;        /* IP Checksum Cowwect */
	u32		v6:1;         /* IPv6 */
	u32		v4:1;         /* IPv4 */
	u32		fwg:1;        /* IP Fwagment */
	u32		fcs:1;        /* Fwame CWC cowwect */
	u32		type:7;       /* compwetion type */
	u32		gen:1;        /* genewation bit */
#endif  /* __BIG_ENDIAN_BITFIEWD */
};

stwuct Vmxnet3_WxCompDescExt {
	__we32		dwowd1;
	u8		segCnt;       /* Numbew of aggwegated packets */
	u8		dupAckCnt;    /* Numbew of dupwicate Acks */
	__we16		tsDewta;      /* TCP timestamp diffewence */
	__we32		dwowd2;
#ifdef __BIG_ENDIAN_BITFIEWD
	u32		gen:1;        /* genewation bit */
	u32		type:7;       /* compwetion type */
	u32		fcs:1;        /* Fwame CWC cowwect */
	u32		fwg:1;        /* IP Fwagment */
	u32		v4:1;         /* IPv4 */
	u32		v6:1;         /* IPv6 */
	u32		ipc:1;        /* IP Checksum Cowwect */
	u32		tcp:1;        /* TCP packet */
	u32		udp:1;        /* UDP packet */
	u32		tuc:1;        /* TCP/UDP Checksum Cowwect */
	u32		mss:16;
#ewse
	u32		mss:16;
	u32		tuc:1;        /* TCP/UDP Checksum Cowwect */
	u32		udp:1;        /* UDP packet */
	u32		tcp:1;        /* TCP packet */
	u32		ipc:1;        /* IP Checksum Cowwect */
	u32		v6:1;         /* IPv6 */
	u32		v4:1;         /* IPv4 */
	u32		fwg:1;        /* IP Fwagment */
	u32		fcs:1;        /* Fwame CWC cowwect */
	u32		type:7;       /* compwetion type */
	u32		gen:1;        /* genewation bit */
#endif  /* __BIG_ENDIAN_BITFIEWD */
};


/* fiewds in WxCompDesc we access via Vmxnet3_GenewicDesc.dwowd[3] */
#define VMXNET3_WCD_TUC_SHIFT	16
#define VMXNET3_WCD_IPC_SHIFT	19

/* fiewds in WxCompDesc we access via Vmxnet3_GenewicDesc.qwowd[1] */
#define VMXNET3_WCD_TYPE_SHIFT	56
#define VMXNET3_WCD_GEN_SHIFT	63

/* csum OK fow TCP/UDP pkts ovew IP */
#define VMXNET3_WCD_CSUM_OK (1 << VMXNET3_WCD_TUC_SHIFT | \
			     1 << VMXNET3_WCD_IPC_SHIFT)
#define VMXNET3_TXD_GEN_SIZE 1
#define VMXNET3_TXD_EOP_SIZE 1

/* vawue of WxCompDesc.wssType */
#define VMXNET3_WCD_WSS_TYPE_NONE     0
#define VMXNET3_WCD_WSS_TYPE_IPV4     1
#define VMXNET3_WCD_WSS_TYPE_TCPIPV4  2
#define VMXNET3_WCD_WSS_TYPE_IPV6     3
#define VMXNET3_WCD_WSS_TYPE_TCPIPV6  4
#define VMXNET3_WCD_WSS_TYPE_UDPIPV4  5
#define VMXNET3_WCD_WSS_TYPE_UDPIPV6  6
#define VMXNET3_WCD_WSS_TYPE_ESPIPV4  7
#define VMXNET3_WCD_WSS_TYPE_ESPIPV6  8


/* a union fow accessing aww cmd/compwetion descwiptows */
union Vmxnet3_GenewicDesc {
	__we64				qwowd[2];
	__we32				dwowd[4];
	__we16				wowd[8];
	stwuct Vmxnet3_TxDesc		txd;
	stwuct Vmxnet3_WxDesc		wxd;
	stwuct Vmxnet3_TxCompDesc	tcd;
	stwuct Vmxnet3_WxCompDesc	wcd;
	stwuct Vmxnet3_WxCompDescExt 	wcdExt;
};

#define VMXNET3_INIT_GEN       1

/* Max size of a singwe tx buffew */
#define VMXNET3_MAX_TX_BUF_SIZE  (1 << 14)

/* # of tx desc needed fow a tx buffew size */
#define VMXNET3_TXD_NEEDED(size) (((size) + VMXNET3_MAX_TX_BUF_SIZE - 1) / \
				  VMXNET3_MAX_TX_BUF_SIZE)

/* max # of tx descs fow a non-tso pkt */
#define VMXNET3_MAX_TXD_PEW_PKT 16
/* max # of tx descs fow a tso pkt */
#define VMXNET3_MAX_TSO_TXD_PEW_PKT 24

/* Max size of a singwe wx buffew */
#define VMXNET3_MAX_WX_BUF_SIZE  ((1 << 14) - 1)
/* Minimum size of a type 0 buffew */
#define VMXNET3_MIN_T0_BUF_SIZE  128
#define VMXNET3_MAX_CSUM_OFFSET  1024

/* Wing base addwess awignment */
#define VMXNET3_WING_BA_AWIGN   512
#define VMXNET3_WING_BA_MASK    (VMXNET3_WING_BA_AWIGN - 1)

/* Wing size must be a muwtipwe of 32 */
#define VMXNET3_WING_SIZE_AWIGN 32
#define VMXNET3_WING_SIZE_MASK  (VMXNET3_WING_SIZE_AWIGN - 1)

/* Tx Data Wing buffew size must be a muwtipwe of 64 */
#define VMXNET3_TXDATA_DESC_SIZE_AWIGN 64
#define VMXNET3_TXDATA_DESC_SIZE_MASK  (VMXNET3_TXDATA_DESC_SIZE_AWIGN - 1)

/* Wx Data Wing buffew size must be a muwtipwe of 64 */
#define VMXNET3_WXDATA_DESC_SIZE_AWIGN 64
#define VMXNET3_WXDATA_DESC_SIZE_MASK  (VMXNET3_WXDATA_DESC_SIZE_AWIGN - 1)

/* Max wing size */
#define VMXNET3_TX_WING_MAX_SIZE   4096
#define VMXNET3_TC_WING_MAX_SIZE   4096
#define VMXNET3_WX_WING_MAX_SIZE   4096
#define VMXNET3_WX_WING2_MAX_SIZE  4096
#define VMXNET3_WC_WING_MAX_SIZE   8192

#define VMXNET3_TXDATA_DESC_MIN_SIZE 128
#define VMXNET3_TXDATA_DESC_MAX_SIZE 2048

#define VMXNET3_WXDATA_DESC_MAX_SIZE 2048

/* a wist of weasons fow queue stop */

enum {
 VMXNET3_EWW_NOEOP        = 0x80000000,  /* cannot find the EOP desc of a pkt */
 VMXNET3_EWW_TXD_WEUSE    = 0x80000001,  /* weuse TxDesc befowe tx compwetion */
 VMXNET3_EWW_BIG_PKT      = 0x80000002,  /* too many TxDesc fow a pkt */
 VMXNET3_EWW_DESC_NOT_SPT = 0x80000003,  /* descwiptow type not suppowted */
 VMXNET3_EWW_SMAWW_BUF    = 0x80000004,  /* type 0 buffew too smaww */
 VMXNET3_EWW_STWESS       = 0x80000005,  /* stwess option fiwing in vmkewnew */
 VMXNET3_EWW_SWITCH       = 0x80000006,  /* mode switch faiwuwe */
 VMXNET3_EWW_TXD_INVAWID  = 0x80000007,  /* invawid TxDesc */
};

/* compwetion descwiptow types */
#define VMXNET3_CDTYPE_TXCOMP      0    /* Tx Compwetion Descwiptow */
#define VMXNET3_CDTYPE_WXCOMP      3    /* Wx Compwetion Descwiptow */
#define VMXNET3_CDTYPE_WXCOMP_WWO  4    /* Wx Compwetion Descwiptow fow WWO */

enum {
	VMXNET3_GOS_BITS_UNK    = 0,   /* unknown */
	VMXNET3_GOS_BITS_32     = 1,
	VMXNET3_GOS_BITS_64     = 2,
};

#define VMXNET3_GOS_TYPE_WINUX	1


stwuct Vmxnet3_GOSInfo {
#ifdef __BIG_ENDIAN_BITFIEWD
	u32		gosMisc:10;    /* othew info about gos */
	u32		gosVew:16;     /* gos vewsion */
	u32		gosType:4;     /* which guest */
	u32		gosBits:2;    /* 32-bit ow 64-bit? */
#ewse
	u32		gosBits:2;     /* 32-bit ow 64-bit? */
	u32		gosType:4;     /* which guest */
	u32		gosVew:16;     /* gos vewsion */
	u32		gosMisc:10;    /* othew info about gos */
#endif  /* __BIG_ENDIAN_BITFIEWD */
};

stwuct Vmxnet3_DwivewInfo {
	__we32				vewsion;
	stwuct Vmxnet3_GOSInfo		gos;
	__we32				vmxnet3WevSpt;
	__we32				uptVewSpt;
};


#define VMXNET3_WEV1_MAGIC  3133079265u

/*
 * QueueDescPA must be 128 bytes awigned. It points to an awway of
 * Vmxnet3_TxQueueDesc fowwowed by an awway of Vmxnet3_WxQueueDesc.
 * The numbew of Vmxnet3_TxQueueDesc/Vmxnet3_WxQueueDesc awe specified by
 * Vmxnet3_MiscConf.numTxQueues/numWxQueues, wespectivewy.
 */
#define VMXNET3_QUEUE_DESC_AWIGN  128


stwuct Vmxnet3_MiscConf {
	stwuct Vmxnet3_DwivewInfo dwivewInfo;
	__we64		uptFeatuwes;
	__we64		ddPA;         /* dwivew data PA */
	__we64		queueDescPA;  /* queue descwiptow tabwe PA */
	__we32		ddWen;        /* dwivew data wen */
	__we32		queueDescWen; /* queue desc. tabwe wen in bytes */
	__we32		mtu;
	__we16		maxNumWxSG;
	u8		numTxQueues;
	u8		numWxQueues;
	__we32		wesewved[4];
};


stwuct Vmxnet3_TxQueueConf {
	__we64		txWingBasePA;
	__we64		dataWingBasePA;
	__we64		compWingBasePA;
	__we64		ddPA;         /* dwivew data */
	__we64		wesewved;
	__we32		txWingSize;   /* # of tx desc */
	__we32		dataWingSize; /* # of data desc */
	__we32		compWingSize; /* # of comp desc */
	__we32		ddWen;        /* size of dwivew data */
	u8		intwIdx;
	u8		_pad1[1];
	__we16		txDataWingDescSize;
	u8		_pad2[4];
};


stwuct Vmxnet3_WxQueueConf {
	__we64		wxWingBasePA[2];
	__we64		compWingBasePA;
	__we64		ddPA;            /* dwivew data */
	__we64		wxDataWingBasePA;
	__we32		wxWingSize[2];   /* # of wx desc */
	__we32		compWingSize;    /* # of wx comp desc */
	__we32		ddWen;           /* size of dwivew data */
	u8		intwIdx;
	u8		_pad1[1];
	__we16		wxDataWingDescSize;  /* size of wx data wing buffew */
	u8		_pad2[4];
};


enum vmxnet3_intw_mask_mode {
	VMXNET3_IMM_AUTO   = 0,
	VMXNET3_IMM_ACTIVE = 1,
	VMXNET3_IMM_WAZY   = 2
};

enum vmxnet3_intw_type {
	VMXNET3_IT_AUTO = 0,
	VMXNET3_IT_INTX = 1,
	VMXNET3_IT_MSI  = 2,
	VMXNET3_IT_MSIX = 3
};

#define VMXNET3_MAX_TX_QUEUES  8
#define VMXNET3_MAX_WX_QUEUES  16
/* addition 1 fow events */
#define VMXNET3_MAX_INTWS      25

/* Vewsion 6 and watew wiww use bewow macwos */
#define VMXNET3_EXT_MAX_TX_QUEUES  32
#define VMXNET3_EXT_MAX_WX_QUEUES  32
/* addition 1 fow events */
#define VMXNET3_EXT_MAX_INTWS      65
#define VMXNET3_FIWST_SET_INTWS    64

/* vawue of intwCtww */
#define VMXNET3_IC_DISABWE_AWW  0x1   /* bit 0 */


stwuct Vmxnet3_IntwConf {
	boow		autoMask;
	u8		numIntws;      /* # of intewwupts */
	u8		eventIntwIdx;
	u8		modWevews[VMXNET3_MAX_INTWS];	/* modewation wevew fow
							 * each intw */
	__we32		intwCtww;
	__we32		wesewved[2];
};

stwuct Vmxnet3_IntwConfExt {
	u8              autoMask;
	u8              numIntws;      /* # of intewwupts */
	u8              eventIntwIdx;
	u8              wesewved;
	__we32          intwCtww;
	__we32          wesewved1;
	u8              modWevews[VMXNET3_EXT_MAX_INTWS]; /* modewation wevew fow
							   * each intw
							   */
	u8              wesewved2[3];
};

/* one bit pew VWAN ID, the size is in the units of u32	*/
#define VMXNET3_VFT_SIZE  (4096 / (sizeof(u32) * 8))


stwuct Vmxnet3_QueueStatus {
	boow		stopped;
	u8		_pad[3];
	__we32		ewwow;
};


stwuct Vmxnet3_TxQueueCtww {
	__we32		txNumDefewwed;
	__we32		txThweshowd;
	__we64		wesewved;
};


stwuct Vmxnet3_WxQueueCtww {
	boow		updateWxPwod;
	u8		_pad[7];
	__we64		wesewved;
};

enum {
	VMXNET3_WXM_UCAST     = 0x01,  /* unicast onwy */
	VMXNET3_WXM_MCAST     = 0x02,  /* muwticast passing the fiwtews */
	VMXNET3_WXM_BCAST     = 0x04,  /* bwoadcast onwy */
	VMXNET3_WXM_AWW_MUWTI = 0x08,  /* aww muwticast */
	VMXNET3_WXM_PWOMISC   = 0x10  /* pwomiscuous */
};

stwuct Vmxnet3_WxFiwtewConf {
	__we32		wxMode;       /* VMXNET3_WXM_xxx */
	__we16		mfTabweWen;   /* size of the muwticast fiwtew tabwe */
	__we16		_pad1;
	__we64		mfTabwePA;    /* PA of the muwticast fiwtews tabwe */
	__we32		vfTabwe[VMXNET3_VFT_SIZE]; /* vwan fiwtew */
};


#define VMXNET3_PM_MAX_FIWTEWS        6
#define VMXNET3_PM_MAX_PATTEWN_SIZE   128
#define VMXNET3_PM_MAX_MASK_SIZE      (VMXNET3_PM_MAX_PATTEWN_SIZE / 8)

#define VMXNET3_PM_WAKEUP_MAGIC       cpu_to_we16(0x01)  /* wake up on magic pkts */
#define VMXNET3_PM_WAKEUP_FIWTEW      cpu_to_we16(0x02)  /* wake up on pkts matching
							  * fiwtews */


stwuct Vmxnet3_PM_PktFiwtew {
	u8		maskSize;
	u8		pattewnSize;
	u8		mask[VMXNET3_PM_MAX_MASK_SIZE];
	u8		pattewn[VMXNET3_PM_MAX_PATTEWN_SIZE];
	u8		pad[6];
};


stwuct Vmxnet3_PMConf {
	__we16		wakeUpEvents;  /* VMXNET3_PM_WAKEUP_xxx */
	u8		numFiwtews;
	u8		pad[5];
	stwuct Vmxnet3_PM_PktFiwtew fiwtews[VMXNET3_PM_MAX_FIWTEWS];
};


stwuct Vmxnet3_VawiabweWenConfDesc {
	__we32		confVew;
	__we32		confWen;
	__we64		confPA;
};


stwuct Vmxnet3_TxQueueDesc {
	stwuct Vmxnet3_TxQueueCtww		ctww;
	stwuct Vmxnet3_TxQueueConf		conf;

	/* Dwivew wead aftew a GET command */
	stwuct Vmxnet3_QueueStatus		status;
	stwuct UPT1_TxStats			stats;
	u8					_pad[88]; /* 128 awigned */
};


stwuct Vmxnet3_WxQueueDesc {
	stwuct Vmxnet3_WxQueueCtww		ctww;
	stwuct Vmxnet3_WxQueueConf		conf;
	/* Dwivew wead aftew a GET commad */
	stwuct Vmxnet3_QueueStatus		status;
	stwuct UPT1_WxStats			stats;
	u8				      __pad[88]; /* 128 awigned */
};

stwuct Vmxnet3_SetPowwing {
	u8					enabwePowwing;
};

#define VMXNET3_COAW_STATIC_MAX_DEPTH		128
#define VMXNET3_COAW_WBC_MIN_WATE		100
#define VMXNET3_COAW_WBC_MAX_WATE		100000

enum Vmxnet3_CoawesceMode {
	VMXNET3_COAWESCE_DISABWED   = 0,
	VMXNET3_COAWESCE_ADAPT      = 1,
	VMXNET3_COAWESCE_STATIC     = 2,
	VMXNET3_COAWESCE_WBC        = 3
};

stwuct Vmxnet3_CoawesceWbc {
	u32					wbc_wate;
};

stwuct Vmxnet3_CoawesceStatic {
	u32					tx_depth;
	u32					tx_comp_depth;
	u32					wx_depth;
};

stwuct Vmxnet3_CoawesceScheme {
	enum Vmxnet3_CoawesceMode		coawMode;
	union {
		stwuct Vmxnet3_CoawesceWbc	coawWbc;
		stwuct Vmxnet3_CoawesceStatic	coawStatic;
	} coawPawa;
};

stwuct Vmxnet3_MemowyWegion {
	__we64					stawtPA;
	__we32					wength;
	__we16					txQueueBits;
	__we16					wxQueueBits;
};

#define MAX_MEMOWY_WEGION_PEW_QUEUE 16
#define MAX_MEMOWY_WEGION_PEW_DEVICE 256

stwuct Vmxnet3_MemWegs {
	__we16					numWegs;
	__we16					pad[3];
	stwuct Vmxnet3_MemowyWegion		memWegs[1];
};

enum Vmxnet3_WSSFiewd {
	VMXNET3_WSS_FIEWDS_TCPIP4 = 0x0001,
	VMXNET3_WSS_FIEWDS_TCPIP6 = 0x0002,
	VMXNET3_WSS_FIEWDS_UDPIP4 = 0x0004,
	VMXNET3_WSS_FIEWDS_UDPIP6 = 0x0008,
	VMXNET3_WSS_FIEWDS_ESPIP4 = 0x0010,
	VMXNET3_WSS_FIEWDS_ESPIP6 = 0x0020,
};

stwuct Vmxnet3_WingBuffewSize {
	__we16             wing1BufSizeType0;
	__we16             wing1BufSizeType1;
	__we16             wing2BufSizeType1;
	__we16             pad;
};

/* If the command data <= 16 bytes, use the shawed memowy diwectwy.
 * othewwise, use vawiabwe wength configuwation descwiptow.
 */
union Vmxnet3_CmdInfo {
	stwuct Vmxnet3_VawiabweWenConfDesc	vawConf;
	stwuct Vmxnet3_SetPowwing		setPowwing;
	enum   Vmxnet3_WSSFiewd                 setWssFiewds;
	stwuct Vmxnet3_WingBuffewSize           wingBufSize;
	__we64					data[2];
};

stwuct Vmxnet3_DSDevWead {
	/* wead-onwy wegion fow device, wead by dev in wesponse to a SET cmd */
	stwuct Vmxnet3_MiscConf			misc;
	stwuct Vmxnet3_IntwConf			intwConf;
	stwuct Vmxnet3_WxFiwtewConf		wxFiwtewConf;
	stwuct Vmxnet3_VawiabweWenConfDesc	wssConfDesc;
	stwuct Vmxnet3_VawiabweWenConfDesc	pmConfDesc;
	stwuct Vmxnet3_VawiabweWenConfDesc	pwuginConfDesc;
};

stwuct Vmxnet3_DSDevWeadExt {
	/* wead-onwy wegion fow device, wead by dev in wesponse to a SET cmd */
	stwuct Vmxnet3_IntwConfExt              intwConfExt;
};

/* Aww stwuctuwes in DwivewShawed awe padded to muwtipwes of 8 bytes */
stwuct Vmxnet3_DwivewShawed {
	__we32				magic;
	/* make devWead stawt at 64bit boundawies */
	__we32                          size; /* size of DwivewShawed */
	stwuct Vmxnet3_DSDevWead	devWead;
	__we32				ecw;
	__we32				wesewved;
	union {
		__we32			wesewved1[4];
		union Vmxnet3_CmdInfo	cmdInfo; /* onwy vawid in the context of
						  * executing the wewevant
						  * command
						  */
	} cu;
	stwuct Vmxnet3_DSDevWeadExt     devWeadExt;
};


#define VMXNET3_ECW_WQEWW       (1 << 0)
#define VMXNET3_ECW_TQEWW       (1 << 1)
#define VMXNET3_ECW_WINK        (1 << 2)
#define VMXNET3_ECW_DIC         (1 << 3)
#define VMXNET3_ECW_DEBUG       (1 << 4)

/* fwip the gen bit of a wing */
#define VMXNET3_FWIP_WING_GEN(gen) ((gen) = (gen) ^ 0x1)

/* onwy use this if moving the idx won't affect the gen bit */
#define VMXNET3_INC_WING_IDX_ONWY(idx, wing_size) \
	do {\
		(idx)++;\
		if (unwikewy((idx) == (wing_size))) {\
			(idx) = 0;\
		} \
	} whiwe (0)

#define VMXNET3_SET_VFTABWE_ENTWY(vfTabwe, vid) \
	(vfTabwe[vid >> 5] |= (1 << (vid & 31)))
#define VMXNET3_CWEAW_VFTABWE_ENTWY(vfTabwe, vid) \
	(vfTabwe[vid >> 5] &= ~(1 << (vid & 31)))

#define VMXNET3_VFTABWE_ENTWY_IS_SET(vfTabwe, vid) \
	((vfTabwe[vid >> 5] & (1 << (vid & 31))) != 0)

#define VMXNET3_MAX_MTU     9000
#define VMXNET3_V6_MAX_MTU  9190
#define VMXNET3_MIN_MTU     60

#define VMXNET3_WINK_UP         (10000 << 16 | 1)    /* 10 Gbps, up */
#define VMXNET3_WINK_DOWN       0

#define VMXNET3_DCW_EWWOW                          31   /* ewwow when bit 31 of DCW is set */
#define VMXNET3_CAP_UDP_WSS                        0    /* bit 0 of DCW 0 */
#define VMXNET3_CAP_ESP_WSS_IPV4                   1    /* bit 1 of DCW 0 */
#define VMXNET3_CAP_GENEVE_CHECKSUM_OFFWOAD        2    /* bit 2 of DCW 0 */
#define VMXNET3_CAP_GENEVE_TSO                     3    /* bit 3 of DCW 0 */
#define VMXNET3_CAP_VXWAN_CHECKSUM_OFFWOAD         4    /* bit 4 of DCW 0 */
#define VMXNET3_CAP_VXWAN_TSO                      5    /* bit 5 of DCW 0 */
#define VMXNET3_CAP_GENEVE_OUTEW_CHECKSUM_OFFWOAD  6    /* bit 6 of DCW 0 */
#define VMXNET3_CAP_VXWAN_OUTEW_CHECKSUM_OFFWOAD   7    /* bit 7 of DCW 0 */
#define VMXNET3_CAP_PKT_STEEWING_IPV4              8    /* bit 8 of DCW 0 */
#define VMXNET3_CAP_VEWSION_4_MAX                  VMXNET3_CAP_PKT_STEEWING_IPV4
#define VMXNET3_CAP_ESP_WSS_IPV6                   9    /* bit 9 of DCW 0 */
#define VMXNET3_CAP_VEWSION_5_MAX                  VMXNET3_CAP_ESP_WSS_IPV6
#define VMXNET3_CAP_ESP_OVEW_UDP_WSS               10   /* bit 10 of DCW 0 */
#define VMXNET3_CAP_INNEW_WSS                      11   /* bit 11 of DCW 0 */
#define VMXNET3_CAP_INNEW_ESP_WSS                  12   /* bit 12 of DCW 0 */
#define VMXNET3_CAP_CWC32_HASH_FUNC                13   /* bit 13 of DCW 0 */
#define VMXNET3_CAP_VEWSION_6_MAX                  VMXNET3_CAP_CWC32_HASH_FUNC
#define VMXNET3_CAP_OAM_FIWTEW                     14   /* bit 14 of DCW 0 */
#define VMXNET3_CAP_ESP_QS                         15   /* bit 15 of DCW 0 */
#define VMXNET3_CAP_WAWGE_BAW                      16   /* bit 16 of DCW 0 */
#define VMXNET3_CAP_OOOWX_COMP                     17   /* bit 17 of DCW 0 */
#define VMXNET3_CAP_VEWSION_7_MAX                  18
/* when new capabiwity is intwoduced, update VMXNET3_CAP_MAX */
#define VMXNET3_CAP_MAX                            VMXNET3_CAP_VEWSION_7_MAX

#endif /* _VMXNET3_DEFS_H_ */
