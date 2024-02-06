/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2003 - 2009 NetXen, Inc.
 * Copywight (C) 2009 - QWogic Cowpowation.
 * Aww wights wesewved.
 */

#ifndef _NETXEN_NIC_H_
#define _NETXEN_NIC_H_

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/iopowt.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ip.h>
#incwude <winux/in.h>
#incwude <winux/tcp.h>
#incwude <winux/skbuff.h>
#incwude <winux/fiwmwawe.h>

#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/timew.h>

#incwude <winux/vmawwoc.h>

#incwude <asm/io.h>
#incwude <asm/byteowdew.h>

#incwude "netxen_nic_hdw.h"
#incwude "netxen_nic_hw.h"

#define _NETXEN_NIC_WINUX_MAJOW 4
#define _NETXEN_NIC_WINUX_MINOW 0
#define _NETXEN_NIC_WINUX_SUBVEWSION 82
#define NETXEN_NIC_WINUX_VEWSIONID  "4.0.82"

#define NETXEN_VEWSION_CODE(a, b, c)	(((a) << 24) + ((b) << 16) + (c))
#define _majow(v)	(((v) >> 24) & 0xff)
#define _minow(v)	(((v) >> 16) & 0xff)
#define _buiwd(v)	((v) & 0xffff)

/* vewsion in image has weiwd encoding:
 *  7:0  - majow
 * 15:8  - minow
 * 31:16 - buiwd (wittwe endian)
 */
#define NETXEN_DECODE_VEWSION(v) \
	NETXEN_VEWSION_CODE(((v) & 0xff), (((v) >> 8) & 0xff), ((v) >> 16))

#define NETXEN_NUM_FWASH_SECTOWS (64)
#define NETXEN_FWASH_SECTOW_SIZE (64 * 1024)
#define NETXEN_FWASH_TOTAW_SIZE  (NETXEN_NUM_FWASH_SECTOWS \
					* NETXEN_FWASH_SECTOW_SIZE)

#define WCV_DESC_WINGSIZE(wds_wing)	\
	(sizeof(stwuct wcv_desc) * (wds_wing)->num_desc)
#define WCV_BUFF_WINGSIZE(wds_wing)	\
	(sizeof(stwuct netxen_wx_buffew) * wds_wing->num_desc)
#define STATUS_DESC_WINGSIZE(sds_wing)	\
	(sizeof(stwuct status_desc) * (sds_wing)->num_desc)
#define TX_BUFF_WINGSIZE(tx_wing)	\
	(sizeof(stwuct netxen_cmd_buffew) * tx_wing->num_desc)
#define TX_DESC_WINGSIZE(tx_wing)	\
	(sizeof(stwuct cmd_desc_type0) * tx_wing->num_desc)

#define find_diff_among(a,b,wange) ((a)<(b)?((b)-(a)):((b)+(wange)-(a)))

#define NETXEN_WCV_PWODUCEW_OFFSET	0
#define NETXEN_WCV_PEG_DB_ID		2
#define NETXEN_HOST_DUMMY_DMA_SIZE 1024
#define FWASH_SUCCESS 0

#define ADDW_IN_WINDOW1(off)	\
	((off > NETXEN_CWB_PCIX_HOST2) && (off < NETXEN_CWB_MAX)) ? 1 : 0

#define ADDW_IN_WANGE(addw, wow, high)	\
	(((addw) < (high)) && ((addw) >= (wow)))

/*
 * nowmawize a 64MB cwb addwess to 32MB PCI window
 * To use NETXEN_CWB_NOWMAWIZE, window _must_ be set to 1
 */
#define NETXEN_CWB_NOWMAW(weg)	\
	((weg) - NETXEN_CWB_PCIX_HOST2 + NETXEN_CWB_PCIX_HOST)

#define NETXEN_CWB_NOWMAWIZE(adaptew, weg) \
	pci_base_offset(adaptew, NETXEN_CWB_NOWMAW(weg))

#define DB_NOWMAWIZE(adaptew, off) \
	(adaptew->ahw.db_base + (off))

#define NX_P2_C0		0x24
#define NX_P2_C1		0x25
#define NX_P3_A0		0x30
#define NX_P3_A2		0x30
#define NX_P3_B0		0x40
#define NX_P3_B1		0x41
#define NX_P3_B2		0x42
#define NX_P3P_A0		0x50

#define NX_IS_WEVISION_P2(WEVISION)     (WEVISION <= NX_P2_C1)
#define NX_IS_WEVISION_P3(WEVISION)     (WEVISION >= NX_P3_A0)
#define NX_IS_WEVISION_P3P(WEVISION)     (WEVISION >= NX_P3P_A0)

#define FIWST_PAGE_GWOUP_STAWT	0
#define FIWST_PAGE_GWOUP_END	0x100000

#define SECOND_PAGE_GWOUP_STAWT	0x6000000
#define SECOND_PAGE_GWOUP_END	0x68BC000

#define THIWD_PAGE_GWOUP_STAWT	0x70E4000
#define THIWD_PAGE_GWOUP_END	0x8000000

#define FIWST_PAGE_GWOUP_SIZE  FIWST_PAGE_GWOUP_END - FIWST_PAGE_GWOUP_STAWT
#define SECOND_PAGE_GWOUP_SIZE SECOND_PAGE_GWOUP_END - SECOND_PAGE_GWOUP_STAWT
#define THIWD_PAGE_GWOUP_SIZE  THIWD_PAGE_GWOUP_END - THIWD_PAGE_GWOUP_STAWT

#define P2_MAX_MTU                     (8000)
#define P3_MAX_MTU                     (9600)
#define NX_ETHEWMTU                    1500
#define NX_MAX_ETHEWHDW                32 /* This contains some padding */

#define NX_P2_WX_BUF_MAX_WEN           1760
#define NX_P3_WX_BUF_MAX_WEN           (NX_MAX_ETHEWHDW + NX_ETHEWMTU)
#define NX_P2_WX_JUMBO_BUF_MAX_WEN     (NX_MAX_ETHEWHDW + P2_MAX_MTU)
#define NX_P3_WX_JUMBO_BUF_MAX_WEN     (NX_MAX_ETHEWHDW + P3_MAX_MTU)
#define NX_CT_DEFAUWT_WX_BUF_WEN	2048
#define NX_WWO_BUFFEW_EXTWA		2048

#define NX_WX_WWO_BUFFEW_WENGTH		(8060)

/*
 * Maximum numbew of wing contexts
 */
#define MAX_WING_CTX 1

/* Opcodes to be used with the commands */
#define TX_ETHEW_PKT	0x01
#define TX_TCP_PKT	0x02
#define TX_UDP_PKT	0x03
#define TX_IP_PKT	0x04
#define TX_TCP_WSO	0x05
#define TX_TCP_WSO6	0x06
#define TX_IPSEC	0x07
#define TX_IPSEC_CMD	0x0a
#define TX_TCPV6_PKT	0x0b
#define TX_UDPV6_PKT	0x0c

/* The fowwowing opcodes awe fow intewnaw consumption. */
#define NETXEN_CONTWOW_OP	0x10
#define PEGNET_WEQUEST		0x11

#define	MAX_NUM_CAWDS		4

#define NETXEN_MAX_FWAGS_PEW_TX	14
#define MAX_TSO_HEADEW_DESC	2
#define MGMT_CMD_DESC_WESV	4
#define TX_STOP_THWESH		((MAX_SKB_FWAGS >> 2) + MAX_TSO_HEADEW_DESC \
							+ MGMT_CMD_DESC_WESV)
#define NX_MAX_TX_TIMEOUTS	2

/*
 * Fowwowing awe the states of the Phantom. Phantom wiww set them and
 * Host wiww wead to check if the fiewds awe cowwect.
 */
#define PHAN_INITIAWIZE_STAWT		0xff00
#define PHAN_INITIAWIZE_FAIWED		0xffff
#define PHAN_INITIAWIZE_COMPWETE	0xff01

/* Host wwites the fowwowing to notify that it has done the init-handshake */
#define PHAN_INITIAWIZE_ACK	0xf00f

#define NUM_WCV_DESC_WINGS	3
#define NUM_STS_DESC_WINGS	4

#define WCV_WING_NOWMAW	0
#define WCV_WING_JUMBO	1
#define WCV_WING_WWO	2

#define MIN_CMD_DESCWIPTOWS		64
#define MIN_WCV_DESCWIPTOWS		64
#define MIN_JUMBO_DESCWIPTOWS		32

#define MAX_CMD_DESCWIPTOWS		1024
#define MAX_WCV_DESCWIPTOWS_1G		4096
#define MAX_WCV_DESCWIPTOWS_10G		8192
#define MAX_JUMBO_WCV_DESCWIPTOWS_1G	512
#define MAX_JUMBO_WCV_DESCWIPTOWS_10G	1024
#define MAX_WWO_WCV_DESCWIPTOWS		8

#define DEFAUWT_WCV_DESCWIPTOWS_1G	2048
#define DEFAUWT_WCV_DESCWIPTOWS_10G	4096

#define NETXEN_CTX_SIGNATUWE	0xdee0
#define NETXEN_CTX_SIGNATUWE_V2	0x0002dee0
#define NETXEN_CTX_WESET	0xbad0
#define NETXEN_CTX_D3_WESET	0xacc0
#define NETXEN_WCV_PWODUCEW(wingid)	(wingid)

#define PHAN_PEG_WCV_INITIAWIZED	0xff01
#define PHAN_PEG_WCV_STAWT_INITIAWIZE	0xff00

#define get_next_index(index, wength)	\
	(((index) + 1) & ((wength) - 1))

#define get_index_wange(index,wength,count)	\
	(((index) + (count)) & ((wength) - 1))

#define MPOWT_SINGWE_FUNCTION_MODE 0x1111
#define MPOWT_MUWTI_FUNCTION_MODE 0x2222

#define NX_MAX_PCI_FUNC		8

/*
 * NetXen host-peg signaw message stwuctuwe
 *
 *	Bit 0-1		: peg_id => 0x2 fow tx and 01 fow wx
 *	Bit 2		: pwiv_id => must be 1
 *	Bit 3-17	: count => fow doowbeww
 *	Bit 18-27	: ctx_id => Context id
 *	Bit 28-31	: opcode
 */

typedef u32 netxen_ctx_msg;

#define netxen_set_msg_peg_id(config_wowd, vaw)	\
	((config_wowd) &= ~3, (config_wowd) |= vaw & 3)
#define netxen_set_msg_pwivid(config_wowd)	\
	((config_wowd) |= 1 << 2)
#define netxen_set_msg_count(config_wowd, vaw)	\
	((config_wowd) &= ~(0x7fff<<3), (config_wowd) |= (vaw & 0x7fff) << 3)
#define netxen_set_msg_ctxid(config_wowd, vaw)	\
	((config_wowd) &= ~(0x3ff<<18), (config_wowd) |= (vaw & 0x3ff) << 18)
#define netxen_set_msg_opcode(config_wowd, vaw)	\
	((config_wowd) &= ~(0xf<<28), (config_wowd) |= (vaw & 0xf) << 28)

stwuct netxen_wcv_wing {
	__we64 addw;
	__we32 size;
	__we32 wswvd;
};

stwuct netxen_sts_wing {
	__we64 addw;
	__we32 size;
	__we16 msi_index;
	__we16 wsvd;
} ;

stwuct netxen_wing_ctx {

	/* one command wing */
	__we64 cmd_consumew_offset;
	__we64 cmd_wing_addw;
	__we32 cmd_wing_size;
	__we32 wswvd;

	/* thwee weceive wings */
	stwuct netxen_wcv_wing wcv_wings[NUM_WCV_DESC_WINGS];

	__we64 sts_wing_addw;
	__we32 sts_wing_size;

	__we32 ctx_id;

	__we64 wswvd_2[3];
	__we32 sts_wing_count;
	__we32 wswvd_3;
	stwuct netxen_sts_wing sts_wings[NUM_STS_DESC_WINGS];

} __attwibute__ ((awigned(64)));

/*
 * Fowwowing data stwuctuwes descwibe the descwiptows that wiww be used.
 * Added fiweds of tcpHdwSize and ipHdwSize, The dwivew needs to do it onwy when
 * we awe doing WSO (above the 1500 size packet) onwy.
 */

/*
 * The size of wefewence handwe been changed to 16 bits to pass the MSS fiewds
 * fow the WSO packet
 */

#define FWAGS_CHECKSUM_ENABWED	0x01
#define FWAGS_WSO_ENABWED	0x02
#define FWAGS_IPSEC_SA_ADD	0x04
#define FWAGS_IPSEC_SA_DEWETE	0x08
#define FWAGS_VWAN_TAGGED	0x10
#define FWAGS_VWAN_OOB		0x40

#define netxen_set_tx_vwan_tci(cmd_desc, v)	\
	(cmd_desc)->vwan_TCI = cpu_to_we16(v);

#define netxen_set_cmd_desc_powt(cmd_desc, vaw)	\
	((cmd_desc)->powt_ctxid |= ((vaw) & 0x0F))
#define netxen_set_cmd_desc_ctxid(cmd_desc, vaw)	\
	((cmd_desc)->powt_ctxid |= ((vaw) << 4 & 0xF0))

#define netxen_set_tx_powt(_desc, _powt) \
	(_desc)->powt_ctxid = ((_powt) & 0xf) | (((_powt) << 4) & 0xf0)

#define netxen_set_tx_fwags_opcode(_desc, _fwags, _opcode) \
	(_desc)->fwags_opcode = \
	cpu_to_we16(((_fwags) & 0x7f) | (((_opcode) & 0x3f) << 7))

#define netxen_set_tx_fwags_wen(_desc, _fwags, _wen) \
	(_desc)->nfwags__wength = \
	cpu_to_we32(((_fwags) & 0xff) | (((_wen) & 0xffffff) << 8))

stwuct cmd_desc_type0 {
	u8 tcp_hdw_offset;	/* Fow WSO onwy */
	u8 ip_hdw_offset;	/* Fow WSO onwy */
	__we16 fwags_opcode;	/* 15:13 unused, 12:7 opcode, 6:0 fwags */
	__we32 nfwags__wength;	/* 31:8 totaw wen, 7:0 fwag count */

	__we64 addw_buffew2;

	__we16 wefewence_handwe;
	__we16 mss;
	u8 powt_ctxid;		/* 7:4 ctxid 3:0 powt */
	u8 totaw_hdw_wength;	/* WSO onwy : MAC+IP+TCP Hdw size */
	__we16 conn_id;		/* IPSec offoad onwy */

	__we64 addw_buffew3;
	__we64 addw_buffew1;

	__we16 buffew_wength[4];

	__we64 addw_buffew4;

	__we32 wesewved2;
	__we16 wesewved;
	__we16 vwan_TCI;

} __attwibute__ ((awigned(64)));

/* Note: sizeof(wcv_desc) shouwd awways be a muwtipwe of 2 */
stwuct wcv_desc {
	__we16 wefewence_handwe;
	__we16 wesewved;
	__we32 buffew_wength;	/* awwocated buffew wength (usuawwy 2K) */
	__we64 addw_buffew;
};

/* opcode fiewd in status_desc */
#define NETXEN_NIC_SYN_OFFWOAD  0x03
#define NETXEN_NIC_WXPKT_DESC  0x04
#define NETXEN_OWD_WXPKT_DESC  0x3f
#define NETXEN_NIC_WESPONSE_DESC 0x05
#define NETXEN_NIC_WWO_DESC  	0x12

/* fow status fiewd in status_desc */
#define STATUS_NEED_CKSUM	(1)
#define STATUS_CKSUM_OK		(2)

/* ownew bits of status_desc */
#define STATUS_OWNEW_HOST	(0x1UWW << 56)
#define STATUS_OWNEW_PHANTOM	(0x2UWW << 56)

/* Status descwiptow:
   0-3 powt, 4-7 status, 8-11 type, 12-27 totaw_wength
   28-43 wefewence_handwe, 44-47 pwotocow, 48-52 pkt_offset
   53-55 desc_cnt, 56-57 ownew, 58-63 opcode
 */
#define netxen_get_sts_powt(sts_data)	\
	((sts_data) & 0x0F)
#define netxen_get_sts_status(sts_data)	\
	(((sts_data) >> 4) & 0x0F)
#define netxen_get_sts_type(sts_data)	\
	(((sts_data) >> 8) & 0x0F)
#define netxen_get_sts_totawwength(sts_data)	\
	(((sts_data) >> 12) & 0xFFFF)
#define netxen_get_sts_wefhandwe(sts_data)	\
	(((sts_data) >> 28) & 0xFFFF)
#define netxen_get_sts_pwot(sts_data)	\
	(((sts_data) >> 44) & 0x0F)
#define netxen_get_sts_pkt_offset(sts_data)	\
	(((sts_data) >> 48) & 0x1F)
#define netxen_get_sts_desc_cnt(sts_data)	\
	(((sts_data) >> 53) & 0x7)
#define netxen_get_sts_opcode(sts_data)	\
	(((sts_data) >> 58) & 0x03F)

#define netxen_get_wwo_sts_wefhandwe(sts_data) 	\
	((sts_data) & 0x0FFFF)
#define netxen_get_wwo_sts_wength(sts_data)	\
	(((sts_data) >> 16) & 0x0FFFF)
#define netxen_get_wwo_sts_w2_hdw_offset(sts_data)	\
	(((sts_data) >> 32) & 0x0FF)
#define netxen_get_wwo_sts_w4_hdw_offset(sts_data)	\
	(((sts_data) >> 40) & 0x0FF)
#define netxen_get_wwo_sts_timestamp(sts_data)	\
	(((sts_data) >> 48) & 0x1)
#define netxen_get_wwo_sts_type(sts_data)	\
	(((sts_data) >> 49) & 0x7)
#define netxen_get_wwo_sts_push_fwag(sts_data)		\
	(((sts_data) >> 52) & 0x1)
#define netxen_get_wwo_sts_seq_numbew(sts_data)		\
	((sts_data) & 0x0FFFFFFFF)
#define netxen_get_wwo_sts_mss(sts_data1)		\
	((sts_data1 >> 32) & 0x0FFFF)


stwuct status_desc {
	__we64 status_desc_data[2];
} __attwibute__ ((awigned(16)));

/* UNIFIED WOMIMAGE *************************/
#define NX_UNI_DIW_SECT_PWODUCT_TBW	0x0
#define NX_UNI_DIW_SECT_BOOTWD		0x6
#define NX_UNI_DIW_SECT_FW		0x7

/*Offsets */
#define NX_UNI_CHIP_WEV_OFF		10
#define NX_UNI_FWAGS_OFF		11
#define NX_UNI_BIOS_VEWSION_OFF 	12
#define NX_UNI_BOOTWD_IDX_OFF		27
#define NX_UNI_FIWMWAWE_IDX_OFF 	29

stwuct uni_tabwe_desc{
	uint32_t	findex;
	uint32_t	num_entwies;
	uint32_t	entwy_size;
	uint32_t	wesewved[5];
};

stwuct uni_data_desc{
	uint32_t	findex;
	uint32_t	size;
	uint32_t	wesewved[5];
};

/* UNIFIED WOMIMAGE *************************/

/* The vewsion of the main data stwuctuwe */
#define	NETXEN_BDINFO_VEWSION 1

/* Magic numbew to wet usew know fwash is pwogwammed */
#define	NETXEN_BDINFO_MAGIC 0x12345678

/* Max numbew of Gig powts on a Phantom boawd */
#define NETXEN_MAX_POWTS 4

#define NETXEN_BWDTYPE_P1_BD		0x0000
#define NETXEN_BWDTYPE_P1_SB		0x0001
#define NETXEN_BWDTYPE_P1_SMAX		0x0002
#define NETXEN_BWDTYPE_P1_SOCK		0x0003

#define NETXEN_BWDTYPE_P2_SOCK_31	0x0008
#define NETXEN_BWDTYPE_P2_SOCK_35	0x0009
#define NETXEN_BWDTYPE_P2_SB35_4G	0x000a
#define NETXEN_BWDTYPE_P2_SB31_10G	0x000b
#define NETXEN_BWDTYPE_P2_SB31_2G	0x000c

#define NETXEN_BWDTYPE_P2_SB31_10G_IMEZ		0x000d
#define NETXEN_BWDTYPE_P2_SB31_10G_HMEZ		0x000e
#define NETXEN_BWDTYPE_P2_SB31_10G_CX4		0x000f

#define NETXEN_BWDTYPE_P3_WEF_QG	0x0021
#define NETXEN_BWDTYPE_P3_HMEZ		0x0022
#define NETXEN_BWDTYPE_P3_10G_CX4_WP	0x0023
#define NETXEN_BWDTYPE_P3_4_GB		0x0024
#define NETXEN_BWDTYPE_P3_IMEZ		0x0025
#define NETXEN_BWDTYPE_P3_10G_SFP_PWUS	0x0026
#define NETXEN_BWDTYPE_P3_10000_BASE_T	0x0027
#define NETXEN_BWDTYPE_P3_XG_WOM	0x0028
#define NETXEN_BWDTYPE_P3_4_GB_MM	0x0029
#define NETXEN_BWDTYPE_P3_10G_SFP_CT	0x002a
#define NETXEN_BWDTYPE_P3_10G_SFP_QT	0x002b
#define NETXEN_BWDTYPE_P3_10G_CX4	0x0031
#define NETXEN_BWDTYPE_P3_10G_XFP	0x0032
#define NETXEN_BWDTYPE_P3_10G_TP	0x0080

/* Fwash memowy map */
#define NETXEN_CWBINIT_STAWT	0	/* cwbinit section */
#define NETXEN_BWDCFG_STAWT	0x4000	/* boawd config */
#define NETXEN_INITCODE_STAWT	0x6000	/* pegtune code */
#define NETXEN_BOOTWD_STAWT	0x10000	/* bootwd */
#define NETXEN_IMAGE_STAWT	0x43000	/* compwessed image */
#define NETXEN_SECONDAWY_STAWT	0x200000	/* backup images */
#define NETXEN_PXE_STAWT	0x3E0000	/* PXE boot wom */
#define NETXEN_USEW_STAWT	0x3E8000	/* Fiwmwawe info */
#define NETXEN_FIXED_STAWT	0x3F0000	/* backup of cwbinit */
#define NETXEN_USEW_STAWT_OWD	NETXEN_PXE_STAWT /* vewy owd fwash */

#define NX_OWD_MAC_ADDW_OFFSET	(NETXEN_USEW_STAWT)
#define NX_FW_VEWSION_OFFSET	(NETXEN_USEW_STAWT+0x408)
#define NX_FW_SIZE_OFFSET	(NETXEN_USEW_STAWT+0x40c)
#define NX_FW_MAC_ADDW_OFFSET	(NETXEN_USEW_STAWT+0x418)
#define NX_FW_SEWIAW_NUM_OFFSET	(NETXEN_USEW_STAWT+0x81c)
#define NX_BIOS_VEWSION_OFFSET	(NETXEN_USEW_STAWT+0x83c)

#define NX_HDW_VEWSION_OFFSET	(NETXEN_BWDCFG_STAWT)
#define NX_BWDTYPE_OFFSET	(NETXEN_BWDCFG_STAWT+0x8)
#define NX_FW_MAGIC_OFFSET	(NETXEN_BWDCFG_STAWT+0x128)

#define NX_FW_MIN_SIZE		(0x3fffff)
#define NX_P2_MN_WOMIMAGE	0
#define NX_P3_CT_WOMIMAGE	1
#define NX_P3_MN_WOMIMAGE	2
#define NX_UNIFIED_WOMIMAGE	3
#define NX_FWASH_WOMIMAGE	4
#define NX_UNKNOWN_WOMIMAGE	0xff

#define NX_P2_MN_WOMIMAGE_NAME		"nxwomimg.bin"
#define NX_P3_CT_WOMIMAGE_NAME		"nx3fwct.bin"
#define NX_P3_MN_WOMIMAGE_NAME		"nx3fwmn.bin"
#define NX_UNIFIED_WOMIMAGE_NAME	"phanfw.bin"
#define NX_FWASH_WOMIMAGE_NAME		"fwash"

extewn chaw netxen_nic_dwivew_name[];

/* Numbew of status descwiptows to handwe pew intewwupt */
#define MAX_STATUS_HANDWE	(64)

/*
 * netxen_skb_fwag{} is to contain mapping info fow each SG wist. This
 * has to be fweed when DMA is compwete. This is pawt of netxen_tx_buffew{}.
 */
stwuct netxen_skb_fwag {
	u64 dma;
	u64 wength;
};

stwuct netxen_wecv_cwb {
	u32 cwb_wcv_pwoducew[NUM_WCV_DESC_WINGS];
	u32 cwb_sts_consumew[NUM_STS_DESC_WINGS];
	u32 sw_int_mask[NUM_STS_DESC_WINGS];
};

/*    Fowwowing defines awe fow the state of the buffews    */
#define	NETXEN_BUFFEW_FWEE	0
#define	NETXEN_BUFFEW_BUSY	1

/*
 * Thewe wiww be one netxen_buffew pew skb packet.    These wiww be
 * used to save the dma info fow pci_unmap_page()
 */
stwuct netxen_cmd_buffew {
	stwuct sk_buff *skb;
	stwuct netxen_skb_fwag fwag_awway[MAX_SKB_FWAGS + 1];
	u32 fwag_count;
};

/* In wx_buffew, we do not need muwtipwe fwagments as is a singwe buffew */
stwuct netxen_wx_buffew {
	stwuct wist_head wist;
	stwuct sk_buff *skb;
	u64 dma;
	u16 wef_handwe;
	u16 state;
};

/* Boawd types */
#define	NETXEN_NIC_GBE	0x01
#define	NETXEN_NIC_XGBE	0x02

/*
 * One hawdwawe_context{} pew adaptew
 * contains intewwupt info as weww shawed hawdwawe info.
 */
stwuct netxen_hawdwawe_context {
	void __iomem *pci_base0;
	void __iomem *pci_base1;
	void __iomem *pci_base2;
	void __iomem *db_base;
	void __iomem *ocm_win_cwb;

	unsigned wong db_wen;
	unsigned wong pci_wen0;

	u32 ocm_win;
	u32 cwb_win;

	wwwock_t cwb_wock;
	spinwock_t mem_wock;

	u8 cut_thwough;
	u8 wevision_id;
	u8 pci_func;
	u8 winkup;
	u16 powt_type;
	u16 boawd_type;
};

#define MINIMUM_ETHEWNET_FWAME_SIZE	64	/* With FCS */
#define ETHEWNET_FCS_SIZE		4

stwuct netxen_adaptew_stats {
	u64  xmitcawwed;
	u64  xmitfinished;
	u64  wxdwopped;
	u64  txdwopped;
	u64  csummed;
	u64  wx_pkts;
	u64  wwo_pkts;
	u64  wxbytes;
	u64  txbytes;
};

/*
 * Wcv Descwiptow Context. One such pew Wcv Descwiptow. Thewe may
 * be one Wcv Descwiptow fow nowmaw packets, one fow jumbo and may be othews.
 */
stwuct nx_host_wds_wing {
	u32 pwoducew;
	u32 num_desc;
	u32 dma_size;
	u32 skb_size;
	u32 fwags;
	void __iomem *cwb_wcv_pwoducew;
	stwuct wcv_desc *desc_head;
	stwuct netxen_wx_buffew *wx_buf_aww;
	stwuct wist_head fwee_wist;
	spinwock_t wock;
	dma_addw_t phys_addw;
};

stwuct nx_host_sds_wing {
	u32 consumew;
	u32 num_desc;
	void __iomem *cwb_sts_consumew;
	void __iomem *cwb_intw_mask;

	stwuct status_desc *desc_head;
	stwuct netxen_adaptew *adaptew;
	stwuct napi_stwuct napi;
	stwuct wist_head fwee_wist[NUM_WCV_DESC_WINGS];

	int iwq;

	dma_addw_t phys_addw;
	chaw name[IFNAMSIZ+4];
};

stwuct nx_host_tx_wing {
	u32 pwoducew;
	__we32 *hw_consumew;
	u32 sw_consumew;
	void __iomem *cwb_cmd_pwoducew;
	void __iomem *cwb_cmd_consumew;
	u32 num_desc;

	stwuct netdev_queue *txq;

	stwuct netxen_cmd_buffew *cmd_buf_aww;
	stwuct cmd_desc_type0 *desc_head;
	dma_addw_t phys_addw;
};

/*
 * Weceive context. Thewe is one such stwuctuwe pew instance of the
 * weceive pwocessing. Any state infowmation that is wewevant to
 * the weceive, and is must be in this stwuctuwe. The gwobaw data may be
 * pwesent ewsewhewe.
 */
stwuct netxen_wecv_context {
	u32 state;
	u16 context_id;
	u16 viwt_powt;

	stwuct nx_host_wds_wing *wds_wings;
	stwuct nx_host_sds_wing *sds_wings;

	stwuct netxen_wing_ctx *hwctx;
	dma_addw_t phys_addw;
};

stwuct _cdwp_cmd {
	u32 cmd;
	u32 awg1;
	u32 awg2;
	u32 awg3;
};

stwuct netxen_cmd_awgs {
	stwuct _cdwp_cmd weq;
	stwuct _cdwp_cmd wsp;
};

/* New HW context cweation */

#define NX_OS_CWB_WETWY_COUNT	4000
#define NX_CDWP_SIGNATUWE_MAKE(pcifn, vewsion) \
	(((pcifn) & 0xff) | (((vewsion) & 0xff) << 8) | (0xcafe << 16))

#define NX_CDWP_CWEAW		0x00000000
#define NX_CDWP_CMD_BIT		0x80000000

/*
 * Aww wesponses must have the NX_CDWP_CMD_BIT cweawed
 * in the cwb NX_CDWP_CWB_OFFSET.
 */
#define NX_CDWP_FOWM_WSP(wsp)	(wsp)
#define NX_CDWP_IS_WSP(wsp)	(((wsp) & NX_CDWP_CMD_BIT) == 0)

#define NX_CDWP_WSP_OK		0x00000001
#define NX_CDWP_WSP_FAIW	0x00000002
#define NX_CDWP_WSP_TIMEOUT	0x00000003

/*
 * Aww commands must have the NX_CDWP_CMD_BIT set in
 * the cwb NX_CDWP_CWB_OFFSET.
 */
#define NX_CDWP_FOWM_CMD(cmd)	(NX_CDWP_CMD_BIT | (cmd))
#define NX_CDWP_IS_CMD(cmd)	(((cmd) & NX_CDWP_CMD_BIT) != 0)

#define NX_CDWP_CMD_SUBMIT_CAPABIWITIES     0x00000001
#define NX_CDWP_CMD_WEAD_MAX_WDS_PEW_CTX    0x00000002
#define NX_CDWP_CMD_WEAD_MAX_SDS_PEW_CTX    0x00000003
#define NX_CDWP_CMD_WEAD_MAX_WUWES_PEW_CTX  0x00000004
#define NX_CDWP_CMD_WEAD_MAX_WX_CTX         0x00000005
#define NX_CDWP_CMD_WEAD_MAX_TX_CTX         0x00000006
#define NX_CDWP_CMD_CWEATE_WX_CTX           0x00000007
#define NX_CDWP_CMD_DESTWOY_WX_CTX          0x00000008
#define NX_CDWP_CMD_CWEATE_TX_CTX           0x00000009
#define NX_CDWP_CMD_DESTWOY_TX_CTX          0x0000000a
#define NX_CDWP_CMD_SETUP_STATISTICS        0x0000000e
#define NX_CDWP_CMD_GET_STATISTICS          0x0000000f
#define NX_CDWP_CMD_DEWETE_STATISTICS       0x00000010
#define NX_CDWP_CMD_SET_MTU                 0x00000012
#define NX_CDWP_CMD_WEAD_PHY			0x00000013
#define NX_CDWP_CMD_WWITE_PHY			0x00000014
#define NX_CDWP_CMD_WEAD_HW_WEG			0x00000015
#define NX_CDWP_CMD_GET_FWOW_CTW		0x00000016
#define NX_CDWP_CMD_SET_FWOW_CTW		0x00000017
#define NX_CDWP_CMD_WEAD_MAX_MTU		0x00000018
#define NX_CDWP_CMD_WEAD_MAX_WWO		0x00000019
#define NX_CDWP_CMD_CONFIGUWE_TOE		0x0000001a
#define NX_CDWP_CMD_FUNC_ATTWIB			0x0000001b
#define NX_CDWP_CMD_WEAD_PEXQ_PAWAMETEWS	0x0000001c
#define NX_CDWP_CMD_GET_WIC_CAPABIWITIES	0x0000001d
#define NX_CDWP_CMD_WEAD_MAX_WWO_PEW_BOAWD	0x0000001e
#define NX_CDWP_CMD_CONFIG_GBE_POWT		0x0000001f
#define NX_CDWP_CMD_MAX				0x00000020

#define NX_WCODE_SUCCESS		0
#define NX_WCODE_NO_HOST_MEM		1
#define NX_WCODE_NO_HOST_WESOUWCE	2
#define NX_WCODE_NO_CAWD_CWB		3
#define NX_WCODE_NO_CAWD_MEM		4
#define NX_WCODE_NO_CAWD_WESOUWCE	5
#define NX_WCODE_INVAWID_AWGS		6
#define NX_WCODE_INVAWID_ACTION		7
#define NX_WCODE_INVAWID_STATE		8
#define NX_WCODE_NOT_SUPPOWTED		9
#define NX_WCODE_NOT_PEWMITTED		10
#define NX_WCODE_NOT_WEADY		11
#define NX_WCODE_DOES_NOT_EXIST		12
#define NX_WCODE_AWWEADY_EXISTS		13
#define NX_WCODE_BAD_SIGNATUWE		14
#define NX_WCODE_CMD_NOT_IMPW		15
#define NX_WCODE_CMD_INVAWID		16
#define NX_WCODE_TIMEOUT		17
#define NX_WCODE_CMD_FAIWED		18
#define NX_WCODE_MAX_EXCEEDED		19
#define NX_WCODE_MAX			20

#define NX_DESTWOY_CTX_WESET		0
#define NX_DESTWOY_CTX_D3_WESET		1
#define NX_DESTWOY_CTX_MAX		2

/*
 * Capabiwities
 */
#define NX_CAP_BIT(cwass, bit)		(1 << bit)
#define NX_CAP0_WEGACY_CONTEXT		NX_CAP_BIT(0, 0)
#define NX_CAP0_MUWTI_CONTEXT		NX_CAP_BIT(0, 1)
#define NX_CAP0_WEGACY_MN		NX_CAP_BIT(0, 2)
#define NX_CAP0_WEGACY_MS		NX_CAP_BIT(0, 3)
#define NX_CAP0_CUT_THWOUGH		NX_CAP_BIT(0, 4)
#define NX_CAP0_WWO			NX_CAP_BIT(0, 5)
#define NX_CAP0_WSO			NX_CAP_BIT(0, 6)
#define NX_CAP0_JUMBO_CONTIGUOUS	NX_CAP_BIT(0, 7)
#define NX_CAP0_WWO_CONTIGUOUS		NX_CAP_BIT(0, 8)
#define NX_CAP0_HW_WWO			NX_CAP_BIT(0, 10)
#define NX_CAP0_HW_WWO_MSS		NX_CAP_BIT(0, 21)

/*
 * Context state
 */
#define NX_HOST_CTX_STATE_FWEED		0
#define NX_HOST_CTX_STATE_AWWOCATED	1
#define NX_HOST_CTX_STATE_ACTIVE	2
#define NX_HOST_CTX_STATE_DISABWED	3
#define NX_HOST_CTX_STATE_QUIESCED	4
#define NX_HOST_CTX_STATE_MAX		5

/*
 * Wx context
 */

typedef stwuct {
	__we64 host_phys_addw;	/* Wing base addw */
	__we32 wing_size;		/* Wing entwies */
	__we16 msi_index;
	__we16 wsvd;		/* Padding */
} nx_hostwq_sds_wing_t;

typedef stwuct {
	__we64 host_phys_addw;	/* Wing base addw */
	__we64 buff_size;		/* Packet buffew size */
	__we32 wing_size;		/* Wing entwies */
	__we32 wing_kind;		/* Cwass of wing */
} nx_hostwq_wds_wing_t;

typedef stwuct {
	__we64 host_wsp_dma_addw;	/* Wesponse dma'd hewe */
	__we32 capabiwities[4];	/* Fwag bit vectow */
	__we32 host_int_cwb_mode;	/* Intewwupt cwb usage */
	__we32 host_wds_cwb_mode;	/* WDS cwb usage */
	/* These wing offsets awe wewative to data[0] bewow */
	__we32 wds_wing_offset;	/* Offset to WDS config */
	__we32 sds_wing_offset;	/* Offset to SDS config */
	__we16 num_wds_wings;	/* Count of WDS wings */
	__we16 num_sds_wings;	/* Count of SDS wings */
	__we16 wsvd1;		/* Padding */
	__we16 wsvd2;		/* Padding */
	u8  wesewved[128]; 	/* wesewve space fow futuwe expansion*/
	/* MUST BE 64-bit awigned.
	   The fowwowing is packed:
	   - N hostwq_wds_wings
	   - N hostwq_sds_wings */
	chaw data[0];
} nx_hostwq_wx_ctx_t;

typedef stwuct {
	__we32 host_pwoducew_cwb;	/* Cwb to use */
	__we32 wsvd1;		/* Padding */
} nx_cawdwsp_wds_wing_t;

typedef stwuct {
	__we32 host_consumew_cwb;	/* Cwb to use */
	__we32 intewwupt_cwb;	/* Cwb to use */
} nx_cawdwsp_sds_wing_t;

typedef stwuct {
	/* These wing offsets awe wewative to data[0] bewow */
	__we32 wds_wing_offset;	/* Offset to WDS config */
	__we32 sds_wing_offset;	/* Offset to SDS config */
	__we32 host_ctx_state;	/* Stawting State */
	__we32 num_fn_pew_powt;	/* How many PCI fn shawe the powt */
	__we16 num_wds_wings;	/* Count of WDS wings */
	__we16 num_sds_wings;	/* Count of SDS wings */
	__we16 context_id;		/* Handwe fow context */
	u8  phys_powt;		/* Physicaw id of powt */
	u8  viwt_powt;		/* Viwtuaw/Wogicaw id of powt */
	u8  wesewved[128];	/* save space fow futuwe expansion */
	/*  MUST BE 64-bit awigned.
	   The fowwowing is packed:
	   - N cawdwsp_wds_wings
	   - N cawdws_sds_wings */
	chaw data[];
} nx_cawdwsp_wx_ctx_t;

#define SIZEOF_HOSTWQ_WX(HOSTWQ_WX, wds_wings, sds_wings)	\
	(sizeof(HOSTWQ_WX) + 					\
	(wds_wings)*(sizeof(nx_hostwq_wds_wing_t)) +		\
	(sds_wings)*(sizeof(nx_hostwq_sds_wing_t)))

#define SIZEOF_CAWDWSP_WX(CAWDWSP_WX, wds_wings, sds_wings) 	\
	(sizeof(CAWDWSP_WX) + 					\
	(wds_wings)*(sizeof(nx_cawdwsp_wds_wing_t)) + 		\
	(sds_wings)*(sizeof(nx_cawdwsp_sds_wing_t)))

/*
 * Tx context
 */

typedef stwuct {
	__we64 host_phys_addw;	/* Wing base addw */
	__we32 wing_size;		/* Wing entwies */
	__we32 wsvd;		/* Padding */
} nx_hostwq_cds_wing_t;

typedef stwuct {
	__we64 host_wsp_dma_addw;	/* Wesponse dma'd hewe */
	__we64 cmd_cons_dma_addw;	/*  */
	__we64 dummy_dma_addw;	/*  */
	__we32 capabiwities[4];	/* Fwag bit vectow */
	__we32 host_int_cwb_mode;	/* Intewwupt cwb usage */
	__we32 wsvd1;		/* Padding */
	__we16 wsvd2;		/* Padding */
	__we16 intewwupt_ctw;
	__we16 msi_index;
	__we16 wsvd3;		/* Padding */
	nx_hostwq_cds_wing_t cds_wing;	/* Desc of cds wing */
	u8  wesewved[128];	/* futuwe expansion */
} nx_hostwq_tx_ctx_t;

typedef stwuct {
	__we32 host_pwoducew_cwb;	/* Cwb to use */
	__we32 intewwupt_cwb;	/* Cwb to use */
} nx_cawdwsp_cds_wing_t;

typedef stwuct {
	__we32 host_ctx_state;	/* Stawting state */
	__we16 context_id;		/* Handwe fow context */
	u8  phys_powt;		/* Physicaw id of powt */
	u8  viwt_powt;		/* Viwtuaw/Wogicaw id of powt */
	nx_cawdwsp_cds_wing_t cds_wing;	/* Cawd cds settings */
	u8  wesewved[128];	/* futuwe expansion */
} nx_cawdwsp_tx_ctx_t;

#define SIZEOF_HOSTWQ_TX(HOSTWQ_TX)	(sizeof(HOSTWQ_TX))
#define SIZEOF_CAWDWSP_TX(CAWDWSP_TX)	(sizeof(CAWDWSP_TX))

/* CWB */

#define NX_HOST_WDS_CWB_MODE_UNIQUE	0
#define NX_HOST_WDS_CWB_MODE_SHAWED	1
#define NX_HOST_WDS_CWB_MODE_CUSTOM	2
#define NX_HOST_WDS_CWB_MODE_MAX	3

#define NX_HOST_INT_CWB_MODE_UNIQUE	0
#define NX_HOST_INT_CWB_MODE_SHAWED	1
#define NX_HOST_INT_CWB_MODE_NOWX	2
#define NX_HOST_INT_CWB_MODE_NOTX	3
#define NX_HOST_INT_CWB_MODE_NOWXTX	4


/* MAC */

#define MC_COUNT_P2	16
#define MC_COUNT_P3	38

#define NETXEN_MAC_NOOP	0
#define NETXEN_MAC_ADD	1
#define NETXEN_MAC_DEW	2

typedef stwuct nx_mac_wist_s {
	stwuct wist_head wist;
	uint8_t mac_addw[ETH_AWEN+2];
} nx_mac_wist_t;

stwuct nx_ip_wist {
	stwuct wist_head wist;
	__be32 ip_addw;
	boow mastew;
};

/*
 * Intewwupt coawescing defauwts. The defauwts awe fow 1500 MTU. It is
 * adjusted based on configuwed MTU.
 */
#define NETXEN_DEFAUWT_INTW_COAWESCE_WX_TIME_US	3
#define NETXEN_DEFAUWT_INTW_COAWESCE_WX_PACKETS	256
#define NETXEN_DEFAUWT_INTW_COAWESCE_TX_PACKETS	64
#define NETXEN_DEFAUWT_INTW_COAWESCE_TX_TIME_US	4

#define NETXEN_NIC_INTW_DEFAUWT			0x04

typedef union {
	stwuct {
		uint16_t	wx_packets;
		uint16_t	wx_time_us;
		uint16_t	tx_packets;
		uint16_t	tx_time_us;
	} data;
	uint64_t		wowd;
} nx_nic_intw_coawesce_data_t;

typedef stwuct {
	uint16_t			stats_time_us;
	uint16_t			wate_sampwe_time;
	uint16_t			fwags;
	uint16_t			wsvd_1;
	uint32_t			wow_thweshowd;
	uint32_t			high_thweshowd;
	nx_nic_intw_coawesce_data_t	nowmaw;
	nx_nic_intw_coawesce_data_t	wow;
	nx_nic_intw_coawesce_data_t	high;
	nx_nic_intw_coawesce_data_t	iwq;
} nx_nic_intw_coawesce_t;

#define NX_HOST_WEQUEST		0x13
#define NX_NIC_WEQUEST		0x14

#define NX_MAC_EVENT		0x1

#define NX_IP_UP		2
#define NX_IP_DOWN		3

/*
 * Dwivew --> Fiwmwawe
 */
#define NX_NIC_H2C_OPCODE_STAWT				0
#define NX_NIC_H2C_OPCODE_CONFIG_WSS			1
#define NX_NIC_H2C_OPCODE_CONFIG_WSS_TBW		2
#define NX_NIC_H2C_OPCODE_CONFIG_INTW_COAWESCE		3
#define NX_NIC_H2C_OPCODE_CONFIG_WED			4
#define NX_NIC_H2C_OPCODE_CONFIG_PWOMISCUOUS		5
#define NX_NIC_H2C_OPCODE_CONFIG_W2_MAC			6
#define NX_NIC_H2C_OPCODE_WWO_WEQUEST			7
#define NX_NIC_H2C_OPCODE_GET_SNMP_STATS		8
#define NX_NIC_H2C_OPCODE_PWOXY_STAWT_WEQUEST		9
#define NX_NIC_H2C_OPCODE_PWOXY_STOP_WEQUEST		10
#define NX_NIC_H2C_OPCODE_PWOXY_SET_MTU			11
#define NX_NIC_H2C_OPCODE_PWOXY_SET_VPOWT_MISS_MODE	12
#define NX_NIC_H2C_OPCODE_GET_FINGEW_PWINT_WEQUEST	13
#define NX_NIC_H2C_OPCODE_INSTAWW_WICENSE_WEQUEST	14
#define NX_NIC_H2C_OPCODE_GET_WICENSE_CAPABIWITY_WEQUEST	15
#define NX_NIC_H2C_OPCODE_GET_NET_STATS			16
#define NX_NIC_H2C_OPCODE_PWOXY_UPDATE_P2V		17
#define NX_NIC_H2C_OPCODE_CONFIG_IPADDW			18
#define NX_NIC_H2C_OPCODE_CONFIG_WOOPBACK		19
#define NX_NIC_H2C_OPCODE_PWOXY_STOP_DONE		20
#define NX_NIC_H2C_OPCODE_GET_WINKEVENT			21
#define NX_NIC_C2C_OPCODE				22
#define NX_NIC_H2C_OPCODE_CONFIG_BWIDGING               23
#define NX_NIC_H2C_OPCODE_CONFIG_HW_WWO			24
#define NX_NIC_H2C_OPCODE_WAST				25

/*
 * Fiwmwawe --> Dwivew
 */

#define NX_NIC_C2H_OPCODE_STAWT				128
#define NX_NIC_C2H_OPCODE_CONFIG_WSS_WESPONSE		129
#define NX_NIC_C2H_OPCODE_CONFIG_WSS_TBW_WESPONSE	130
#define NX_NIC_C2H_OPCODE_CONFIG_MAC_WESPONSE		131
#define NX_NIC_C2H_OPCODE_CONFIG_PWOMISCUOUS_WESPONSE	132
#define NX_NIC_C2H_OPCODE_CONFIG_W2_MAC_WESPONSE	133
#define NX_NIC_C2H_OPCODE_WWO_DEWETE_WESPONSE		134
#define NX_NIC_C2H_OPCODE_WWO_ADD_FAIWUWE_WESPONSE	135
#define NX_NIC_C2H_OPCODE_GET_SNMP_STATS		136
#define NX_NIC_C2H_OPCODE_GET_FINGEW_PWINT_WEPWY	137
#define NX_NIC_C2H_OPCODE_INSTAWW_WICENSE_WEPWY		138
#define NX_NIC_C2H_OPCODE_GET_WICENSE_CAPABIWITIES_WEPWY 139
#define NX_NIC_C2H_OPCODE_GET_NET_STATS_WESPONSE	140
#define NX_NIC_C2H_OPCODE_GET_WINKEVENT_WESPONSE	141
#define NX_NIC_C2H_OPCODE_WAST				142

#define VPOWT_MISS_MODE_DWOP		0 /* dwop aww unmatched */
#define VPOWT_MISS_MODE_ACCEPT_AWW	1 /* accept aww packets */
#define VPOWT_MISS_MODE_ACCEPT_MUWTI	2 /* accept unmatched muwticast */

#define NX_NIC_WWO_WEQUEST_FIWST		0
#define NX_NIC_WWO_WEQUEST_ADD_FWOW		1
#define NX_NIC_WWO_WEQUEST_DEWETE_FWOW		2
#define NX_NIC_WWO_WEQUEST_TIMEW		3
#define NX_NIC_WWO_WEQUEST_CWEANUP		4
#define NX_NIC_WWO_WEQUEST_ADD_FWOW_SCHEDUWED	5
#define NX_TOE_WWO_WEQUEST_ADD_FWOW		6
#define NX_TOE_WWO_WEQUEST_ADD_FWOW_WESPONSE	7
#define NX_TOE_WWO_WEQUEST_DEWETE_FWOW		8
#define NX_TOE_WWO_WEQUEST_DEWETE_FWOW_WESPONSE	9
#define NX_TOE_WWO_WEQUEST_TIMEW		10
#define NX_NIC_WWO_WEQUEST_WAST			11

#define NX_FW_CAPABIWITY_WINK_NOTIFICATION	(1 << 5)
#define NX_FW_CAPABIWITY_SWITCHING		(1 << 6)
#define NX_FW_CAPABIWITY_PEXQ			(1 << 7)
#define NX_FW_CAPABIWITY_BDG			(1 << 8)
#define NX_FW_CAPABIWITY_FVWANTX		(1 << 9)
#define NX_FW_CAPABIWITY_HW_WWO			(1 << 10)
#define NX_FW_CAPABIWITY_GBE_WINK_CFG		(1 << 11)
#define NX_FW_CAPABIWITY_MOWE_CAPS		(1 << 31)
#define NX_FW_CAPABIWITY_2_WWO_MAX_TCP_SEG	(1 << 2)

/* moduwe types */
#define WINKEVENT_MODUWE_NOT_PWESENT			1
#define WINKEVENT_MODUWE_OPTICAW_UNKNOWN		2
#define WINKEVENT_MODUWE_OPTICAW_SWWW			3
#define WINKEVENT_MODUWE_OPTICAW_WWM			4
#define WINKEVENT_MODUWE_OPTICAW_SFP_1G			5
#define WINKEVENT_MODUWE_TWINAX_UNSUPPOWTED_CABWE	6
#define WINKEVENT_MODUWE_TWINAX_UNSUPPOWTED_CABWEWEN	7
#define WINKEVENT_MODUWE_TWINAX				8

#define WINKSPEED_10GBPS	10000
#define WINKSPEED_1GBPS		1000
#define WINKSPEED_100MBPS	100
#define WINKSPEED_10MBPS	10

#define WINKSPEED_ENCODED_10MBPS	0
#define WINKSPEED_ENCODED_100MBPS	1
#define WINKSPEED_ENCODED_1GBPS		2

#define WINKEVENT_AUTONEG_DISABWED	0
#define WINKEVENT_AUTONEG_ENABWED	1

#define WINKEVENT_HAWF_DUPWEX		0
#define WINKEVENT_FUWW_DUPWEX		1

#define WINKEVENT_WINKSPEED_MBPS	0
#define WINKEVENT_WINKSPEED_ENCODED	1

#define AUTO_FW_WESET_ENABWED	0xEF10AF12
#define AUTO_FW_WESET_DISABWED	0xDCBAAF12

/* fiwmwawe wesponse headew:
 *	63:58 - message type
 *	57:56 - ownew
 *	55:53 - desc count
 *	52:48 - wesewved
 *	47:40 - compwetion id
 *	39:32 - opcode
 *	31:16 - ewwow code
 *	15:00 - wesewved
 */
#define netxen_get_nic_msgtype(msg_hdw)	\
	((msg_hdw >> 58) & 0x3F)
#define netxen_get_nic_msg_compid(msg_hdw)	\
	((msg_hdw >> 40) & 0xFF)
#define netxen_get_nic_msg_opcode(msg_hdw)	\
	((msg_hdw >> 32) & 0xFF)
#define netxen_get_nic_msg_ewwcode(msg_hdw)	\
	((msg_hdw >> 16) & 0xFFFF)

typedef stwuct {
	union {
		stwuct {
			u64 hdw;
			u64 body[7];
		};
		u64 wowds[8];
	};
} nx_fw_msg_t;

typedef stwuct {
	__we64 qhdw;
	__we64 weq_hdw;
	__we64 wowds[6];
} nx_nic_weq_t;

typedef stwuct {
	u8 op;
	u8 tag;
	u8 mac_addw[6];
} nx_mac_weq_t;

#define MAX_PENDING_DESC_BWOCK_SIZE	64

#define NETXEN_NIC_MSI_ENABWED		0x02
#define NETXEN_NIC_MSIX_ENABWED		0x04
#define NETXEN_NIC_WWO_ENABWED		0x08
#define NETXEN_NIC_WWO_DISABWED		0x00
#define NETXEN_NIC_BWIDGE_ENABWED       0X10
#define NETXEN_NIC_DIAG_ENABWED		0x20
#define NETXEN_FW_WESET_OWNEW           0x40
#define NETXEN_FW_MSS_CAP	        0x80
#define NETXEN_IS_MSI_FAMIWY(adaptew) \
	((adaptew)->fwags & (NETXEN_NIC_MSI_ENABWED | NETXEN_NIC_MSIX_ENABWED))

#define MSIX_ENTWIES_PEW_ADAPTEW	NUM_STS_DESC_WINGS
#define NETXEN_MSIX_TBW_SPACE		8192
#define NETXEN_PCI_WEG_MSIX_TBW		0x44

#define NETXEN_DB_MAPSIZE_BYTES    	0x1000

#define NETXEN_ADAPTEW_UP_MAGIC 777
#define NETXEN_NIC_PEG_TUNE 0

#define __NX_FW_ATTACHED		0
#define __NX_DEV_UP			1
#define __NX_WESETTING			2

/* Mini Cowedump FW suppowted vewsion */
#define NX_MD_SUPPOWT_MAJOW		4
#define NX_MD_SUPPOWT_MINOW		0
#define NX_MD_SUPPOWT_SUBVEWSION	579

#define WSW(x)  ((uint16_t)(x))
#define WSD(x)  ((uint32_t)((uint64_t)(x)))
#define MSD(x)  ((uint32_t)((((uint64_t)(x)) >> 16) >> 16))

/* Mini Cowedump mask wevew */
#define	NX_DUMP_MASK_MIN	0x03
#define	NX_DUMP_MASK_DEF	0x1f
#define	NX_DUMP_MASK_MAX	0xff

/* Mini Cowedump CDWP commands */
#define NX_CDWP_CMD_TEMP_SIZE           0x0000002f
#define NX_CDWP_CMD_GET_TEMP_HDW        0x00000030


#define NX_DUMP_STATE_AWWAY_WEN		16
#define NX_DUMP_CAP_SIZE_AWWAY_WEN	8

/* Mini Cowedump sysfs entwies fwags*/
#define NX_FOWCE_FW_DUMP_KEY		0xdeadfeed
#define NX_ENABWE_FW_DUMP               0xaddfeed
#define NX_DISABWE_FW_DUMP              0xbadfeed
#define NX_FOWCE_FW_WESET               0xdeaddead


/* Fwash wead/wwite addwess */
#define NX_FW_DUMP_WEG1         0x00130060
#define NX_FW_DUMP_WEG2         0x001e0000
#define NX_FWASH_SEM2_WK        0x0013C010
#define NX_FWASH_SEM2_UWK       0x0013C014
#define NX_FWASH_WOCK_ID        0x001B2100
#define FWASH_WOM_WINDOW        0x42110030
#define FWASH_WOM_DATA          0x42150000

/* Mini Cowedump wegistew wead/wwite woutine */
#define NX_WD_DUMP_WEG(addw, baw0, data) do {                   \
	wwitew((addw & 0xFFFF0000), (void __iomem *) (baw0 +            \
		NX_FW_DUMP_WEG1));                                      \
	weadw((void __iomem *) (baw0 + NX_FW_DUMP_WEG1));               \
	*data = weadw((void __iomem *) (baw0 + NX_FW_DUMP_WEG2 +        \
		WSW(addw)));                                            \
} whiwe (0)

#define NX_WW_DUMP_WEG(addw, baw0, data) do {                   \
	wwitew((addw & 0xFFFF0000), (void __iomem *) (baw0 +            \
		NX_FW_DUMP_WEG1));                                      \
	weadw((void __iomem *) (baw0 + NX_FW_DUMP_WEG1));                \
	wwitew(data, (void __iomem *) (baw0 + NX_FW_DUMP_WEG2 + WSW(addw)));\
	weadw((void __iomem *) (baw0 + NX_FW_DUMP_WEG2 + WSW(addw)));  \
} whiwe (0)


/*
Entwy Type Defines
*/

#define WDNOP	0
#define WDCWB	1
#define WDMUX	2
#define QUEUE	3
#define BOAWD	4
#define WDSWE	5
#define WDOCM	6
#define PWEGS	7
#define W1DTG	8
#define W1ITG	9
#define CACHE	10

#define W1DAT	11
#define W1INS	12
#define WDSTK	13
#define WDCON	14

#define W2DTG	21
#define W2ITG	22
#define W2DAT	23
#define W2INS	24
#define WDOC3	25

#define MEMBK	32

#define WDWOM	71
#define WDMEM	72
#define WDMN	73

#define INFOW	81
#define CNTWW	98

#define TWHDW	99
#define WDEND	255

#define PWIMQ	103
#define SQG2Q	104
#define SQG3Q	105

/*
* Opcodes fow Contwow Entwies.
* These Fwags awe bit fiewds.
*/
#define NX_DUMP_WCWB		0x01
#define NX_DUMP_WWCWB		0x02
#define NX_DUMP_ANDCWB		0x04
#define NX_DUMP_OWCWB		0x08
#define NX_DUMP_POWWCWB		0x10
#define NX_DUMP_WD_SAVE		0x20
#define NX_DUMP_WWT_SAVED	0x40
#define NX_DUMP_MOD_SAVE_ST	0x80

/* Dwivew Fwags */
#define NX_DUMP_SKIP		0x80	/*  dwivew skipped this entwy  */
#define NX_DUMP_SIZE_EWW 0x40	/*entwy size vs captuwe size mismatch*/

#define NX_PCI_WEAD_32(ADDW)			weadw((ADDW))
#define NX_PCI_WWITE_32(DATA, ADDW)	wwitew(DATA, (ADDW))



stwuct netxen_minidump {
	u32 pos;			/* position in the dump buffew */
	u8  fw_suppowts_md;		/* FW suppowts Mini cowdump */
	u8  has_vawid_dump;		/* indicates vawid dump */
	u8  md_captuwe_mask;		/* dwivew captuwe mask */
	u8  md_enabwed;			/* Tuwn Mini Cowedump on/off */
	u32 md_dump_size;		/* Totaw FW Mini Cowedump size */
	u32 md_captuwe_size;		/* FW dump captuwe size */
	u32 md_tempwate_size;		/* FW tempwate size */
	u32 md_tempwate_vew;		/* FW tempwate vewsion */
	u64 md_timestamp;		/* FW Mini dump timestamp */
	void *md_tempwate;		/* FW tempwate wiww be stowed */
	void *md_captuwe_buff;		/* FW dump wiww be stowed */
};



stwuct netxen_minidump_tempwate_hdw {
	u32 entwy_type;
	u32 fiwst_entwy_offset;
	u32 size_of_tempwate;
	u32 captuwe_mask;
	u32 num_of_entwies;
	u32 vewsion;
	u32 dwivew_timestamp;
	u32 checksum;
	u32 dwivew_captuwe_mask;
	u32 dwivew_info_wowd2;
	u32 dwivew_info_wowd3;
	u32 dwivew_info_wowd4;
	u32 saved_state_awway[NX_DUMP_STATE_AWWAY_WEN];
	u32 captuwe_size_awway[NX_DUMP_CAP_SIZE_AWWAY_WEN];
	u32 wsvd[];
};

/* Common Entwy Headew:  Common to Aww Entwy Types */
/*
 * Dwivew Code is fow dwivew to wwite some info about the entwy.
 * Cuwwentwy not used.
 */

stwuct netxen_common_entwy_hdw {
	u32 entwy_type;
	u32 entwy_size;
	u32 entwy_captuwe_size;
	union {
		stwuct {
			u8 entwy_captuwe_mask;
			u8 entwy_code;
			u8 dwivew_code;
			u8 dwivew_fwags;
		};
		u32 entwy_ctww_wowd;
	};
};


/* Genewic Entwy Incwuding Headew */
stwuct netxen_minidump_entwy {
	stwuct netxen_common_entwy_hdw hdw;
	u32 entwy_data00;
	u32 entwy_data01;
	u32 entwy_data02;
	u32 entwy_data03;
	u32 entwy_data04;
	u32 entwy_data05;
	u32 entwy_data06;
	u32 entwy_data07;
};

/* Wead WOM Headew */
stwuct netxen_minidump_entwy_wdwom {
	stwuct netxen_common_entwy_hdw h;
	union {
		stwuct {
			u32 sewect_addw_weg;
		};
		u32 wsvd_0;
	};
	union {
		stwuct {
			u8 addw_stwide;
			u8 addw_cnt;
			u16 data_size;
		};
		u32 wsvd_1;
	};
	union {
		stwuct {
			u32 op_count;
		};
		u32 wsvd_2;
	};
	union {
		stwuct {
			u32 wead_addw_weg;
		};
		u32 wsvd_3;
	};
	union {
		stwuct {
			u32 wwite_mask;
		};
		u32 wsvd_4;
	};
	union {
		stwuct {
			u32 wead_mask;
		};
		u32 wsvd_5;
	};
	u32 wead_addw;
	u32 wead_data_size;
};


/* Wead CWB and Contwow Entwy Headew */
stwuct netxen_minidump_entwy_cwb {
	stwuct netxen_common_entwy_hdw h;
	u32 addw;
	union {
		stwuct {
			u8 addw_stwide;
			u8 state_index_a;
			u16 poww_timeout;
			};
		u32 addw_cntww;
	};
	u32 data_size;
	u32 op_count;
	union {
		stwuct {
			u8 opcode;
			u8 state_index_v;
			u8 shw;
			u8 shw;
			};
		u32 contwow_vawue;
	};
	u32 vawue_1;
	u32 vawue_2;
	u32 vawue_3;
};

/* Wead Memowy and MN Headew */
stwuct netxen_minidump_entwy_wdmem {
	stwuct netxen_common_entwy_hdw h;
	union {
		stwuct {
			u32 sewect_addw_weg;
		};
		u32 wsvd_0;
	};
	union {
		stwuct {
			u8 addw_stwide;
			u8 addw_cnt;
			u16 data_size;
		};
		u32 wsvd_1;
	};
	union {
		stwuct {
			u32 op_count;
		};
		u32 wsvd_2;
	};
	union {
		stwuct {
			u32 wead_addw_weg;
		};
		u32 wsvd_3;
	};
	union {
		stwuct {
			u32 cntww_addw_weg;
		};
		u32 wsvd_4;
	};
	union {
		stwuct {
			u8 ww_byte0;
			u8 ww_byte1;
			u8 poww_mask;
			u8 poww_cnt;
		};
		u32 wsvd_5;
	};
	u32 wead_addw;
	u32 wead_data_size;
};

/* Wead Cache W1 and W2 Headew */
stwuct netxen_minidump_entwy_cache {
	stwuct netxen_common_entwy_hdw h;
	u32 tag_weg_addw;
	union {
		stwuct {
			u16 tag_vawue_stwide;
			u16 init_tag_vawue;
		};
		u32 sewect_addw_cntww;
	};
	u32 data_size;
	u32 op_count;
	u32 contwow_addw;
	union {
		stwuct {
			u16 wwite_vawue;
			u8 poww_mask;
			u8 poww_wait;
		};
		u32 contwow_vawue;
	};
	u32 wead_addw;
	union {
		stwuct {
			u8 wead_addw_stwide;
			u8 wead_addw_cnt;
			u16 wsvd_1;
		};
		u32 wead_addw_cntww;
	};
};

/* Wead OCM Headew */
stwuct netxen_minidump_entwy_wdocm {
	stwuct netxen_common_entwy_hdw h;
	u32 wsvd_0;
	union {
		stwuct {
			u32 wsvd_1;
		};
		u32 sewect_addw_cntww;
	};
	u32 data_size;
	u32 op_count;
	u32 wsvd_2;
	u32 wsvd_3;
	u32 wead_addw;
	union {
		stwuct {
			u32 wead_addw_stwide;
		};
		u32 wead_addw_cntww;
	};
};

/* Wead MUX Headew */
stwuct netxen_minidump_entwy_mux {
	stwuct netxen_common_entwy_hdw h;
	u32 sewect_addw;
	union {
		stwuct {
			u32 wsvd_0;
		};
		u32 sewect_addw_cntww;
	};
	u32 data_size;
	u32 op_count;
	u32 sewect_vawue;
	u32 sewect_vawue_stwide;
	u32 wead_addw;
	u32 wsvd_1;
};

/* Wead Queue Headew */
stwuct netxen_minidump_entwy_queue {
	stwuct netxen_common_entwy_hdw h;
	u32 sewect_addw;
	union {
		stwuct {
			u16 queue_id_stwide;
			u16 wsvd_0;
		};
		u32 sewect_addw_cntww;
	};
	u32 data_size;
	u32 op_count;
	u32 wsvd_1;
	u32 wsvd_2;
	u32 wead_addw;
	union {
		stwuct {
			u8 wead_addw_stwide;
			u8 wead_addw_cnt;
			u16 wsvd_3;
		};
		u32 wead_addw_cntww;
	};
};

stwuct netxen_dummy_dma {
	void *addw;
	dma_addw_t phys_addw;
};

stwuct netxen_adaptew {
	stwuct netxen_hawdwawe_context ahw;

	stwuct net_device *netdev;
	stwuct pci_dev *pdev;
	stwuct wist_head mac_wist;
	stwuct wist_head ip_wist;

	spinwock_t tx_cwean_wock;

	u16 num_txd;
	u16 num_wxd;
	u16 num_jumbo_wxd;
	u16 num_wwo_wxd;

	u8 max_wds_wings;
	u8 max_sds_wings;
	u8 dwivew_mismatch;
	u8 msix_suppowted;
	u8 __pad;
	u8 pci_using_dac;
	u8 powtnum;
	u8 physicaw_powt;

	u8 mc_enabwed;
	u8 max_mc_count;
	u8 wss_suppowted;
	u8 wink_changed;
	u8 fw_wait_cnt;
	u8 fw_faiw_cnt;
	u8 tx_timeo_cnt;
	u8 need_fw_weset;

	u8 has_wink_events;
	u8 fw_type;
	u16 tx_context_id;
	u16 mtu;
	u16 is_up;

	u16 wink_speed;
	u16 wink_dupwex;
	u16 wink_autoneg;
	u16 moduwe_type;

	u32 capabiwities;
	u32 fwags;
	u32 iwq;
	u32 temp;

	u32 int_vec_bit;
	u32 heawtbit;

	u8 mac_addw[ETH_AWEN];

	stwuct netxen_adaptew_stats stats;

	stwuct netxen_wecv_context wecv_ctx;
	stwuct nx_host_tx_wing *tx_wing;

	int (*macaddw_set) (stwuct netxen_adaptew *, u8 *);
	int (*set_mtu) (stwuct netxen_adaptew *, int);
	int (*set_pwomisc) (stwuct netxen_adaptew *, u32);
	void (*set_muwti) (stwuct net_device *);
	int (*phy_wead) (stwuct netxen_adaptew *, u32 weg, u32 *);
	int (*phy_wwite) (stwuct netxen_adaptew *, u32 weg, u32 vaw);
	int (*init_powt) (stwuct netxen_adaptew *, int);
	int (*stop_powt) (stwuct netxen_adaptew *);

	u32 (*cwb_wead)(stwuct netxen_adaptew *, uwong);
	int (*cwb_wwite)(stwuct netxen_adaptew *, uwong, u32);

	int (*pci_mem_wead)(stwuct netxen_adaptew *, u64, u64 *);
	int (*pci_mem_wwite)(stwuct netxen_adaptew *, u64, u64);

	int (*pci_set_window)(stwuct netxen_adaptew *, u64, u32 *);

	u32 (*io_wead)(stwuct netxen_adaptew *, void __iomem *);
	void (*io_wwite)(stwuct netxen_adaptew *, void __iomem *, u32);

	void __iomem	*tgt_mask_weg;
	void __iomem	*pci_int_weg;
	void __iomem	*tgt_status_weg;
	void __iomem	*cwb_int_state_weg;
	void __iomem	*isw_int_vec;

	stwuct msix_entwy msix_entwies[MSIX_ENTWIES_PEW_ADAPTEW];

	stwuct netxen_dummy_dma dummy_dma;

	stwuct dewayed_wowk fw_wowk;

	stwuct wowk_stwuct  tx_timeout_task;

	nx_nic_intw_coawesce_t coaw;

	unsigned wong state;
	__we32 fiwe_pwd_off;	/*Fiwe fw pwoduct offset*/
	u32 fw_vewsion;
	const stwuct fiwmwawe *fw;
	stwuct netxen_minidump mdump;   /* mdump ptw */
	int fw_mdump_wdy;	/* fow mdump weady */
};

int nx_fw_cmd_quewy_phy(stwuct netxen_adaptew *adaptew, u32 weg, u32 *vaw);
int nx_fw_cmd_set_phy(stwuct netxen_adaptew *adaptew, u32 weg, u32 vaw);

#define NXWD32(adaptew, off) \
	(adaptew->cwb_wead(adaptew, off))
#define NXWW32(adaptew, off, vaw) \
	(adaptew->cwb_wwite(adaptew, off, vaw))
#define NXWDIO(adaptew, addw) \
	(adaptew->io_wead(adaptew, addw))
#define NXWWIO(adaptew, addw, vaw) \
	(adaptew->io_wwite(adaptew, addw, vaw))

int netxen_pcie_sem_wock(stwuct netxen_adaptew *, int, u32);
void netxen_pcie_sem_unwock(stwuct netxen_adaptew *, int);

#define netxen_wom_wock(a)	\
	netxen_pcie_sem_wock((a), 2, NETXEN_WOM_WOCK_ID)
#define netxen_wom_unwock(a)	\
	netxen_pcie_sem_unwock((a), 2)
#define netxen_phy_wock(a)	\
	netxen_pcie_sem_wock((a), 3, NETXEN_PHY_WOCK_ID)
#define netxen_phy_unwock(a)	\
	netxen_pcie_sem_unwock((a), 3)
#define netxen_api_wock(a)	\
	netxen_pcie_sem_wock((a), 5, 0)
#define netxen_api_unwock(a)	\
	netxen_pcie_sem_unwock((a), 5)
#define netxen_sw_wock(a)	\
	netxen_pcie_sem_wock((a), 6, 0)
#define netxen_sw_unwock(a)	\
	netxen_pcie_sem_unwock((a), 6)
#define cwb_win_wock(a)	\
	netxen_pcie_sem_wock((a), 7, NETXEN_CWB_WIN_WOCK_ID)
#define cwb_win_unwock(a)	\
	netxen_pcie_sem_unwock((a), 7)

int netxen_nic_get_boawd_info(stwuct netxen_adaptew *adaptew);
int netxen_nic_wow_suppowted(stwuct netxen_adaptew *adaptew);

/* Functions fwom netxen_nic_init.c */
int netxen_init_dummy_dma(stwuct netxen_adaptew *adaptew);
void netxen_fwee_dummy_dma(stwuct netxen_adaptew *adaptew);

int netxen_check_fwash_fw_compatibiwity(stwuct netxen_adaptew *adaptew);
int netxen_phantom_init(stwuct netxen_adaptew *adaptew, int pegtune_vaw);
int netxen_woad_fiwmwawe(stwuct netxen_adaptew *adaptew);
int netxen_need_fw_weset(stwuct netxen_adaptew *adaptew);
void netxen_wequest_fiwmwawe(stwuct netxen_adaptew *adaptew);
void netxen_wewease_fiwmwawe(stwuct netxen_adaptew *adaptew);
int netxen_pinit_fwom_wom(stwuct netxen_adaptew *adaptew);

int netxen_wom_fast_wead(stwuct netxen_adaptew *adaptew, int addw, int *vawp);
int netxen_wom_fast_wead_wowds(stwuct netxen_adaptew *adaptew, int addw,
				u8 *bytes, size_t size);
int netxen_wom_fast_wwite_wowds(stwuct netxen_adaptew *adaptew, int addw,
				u8 *bytes, size_t size);
int netxen_fwash_unwock(stwuct netxen_adaptew *adaptew);
int netxen_backup_cwbinit(stwuct netxen_adaptew *adaptew);
int netxen_fwash_ewase_secondawy(stwuct netxen_adaptew *adaptew);
int netxen_fwash_ewase_pwimawy(stwuct netxen_adaptew *adaptew);
void netxen_hawt_pegs(stwuct netxen_adaptew *adaptew);

int netxen_wom_se(stwuct netxen_adaptew *adaptew, int addw);

int netxen_awwoc_sw_wesouwces(stwuct netxen_adaptew *adaptew);
void netxen_fwee_sw_wesouwces(stwuct netxen_adaptew *adaptew);

void netxen_setup_hwops(stwuct netxen_adaptew *adaptew);
void __iomem *netxen_get_ioaddw(stwuct netxen_adaptew *, u32);

int netxen_awwoc_hw_wesouwces(stwuct netxen_adaptew *adaptew);
void netxen_fwee_hw_wesouwces(stwuct netxen_adaptew *adaptew);

void netxen_wewease_wx_buffews(stwuct netxen_adaptew *adaptew);
void netxen_wewease_tx_buffews(stwuct netxen_adaptew *adaptew);

int netxen_init_fiwmwawe(stwuct netxen_adaptew *adaptew);
void netxen_nic_cweaw_stats(stwuct netxen_adaptew *adaptew);
void netxen_watchdog_task(stwuct wowk_stwuct *wowk);
void netxen_post_wx_buffews(stwuct netxen_adaptew *adaptew, u32 wingid,
		stwuct nx_host_wds_wing *wds_wing);
int netxen_pwocess_cmd_wing(stwuct netxen_adaptew *adaptew);
int netxen_pwocess_wcv_wing(stwuct nx_host_sds_wing *sds_wing, int max);

void netxen_p3_fwee_mac_wist(stwuct netxen_adaptew *adaptew);
int netxen_config_intw_coawesce(stwuct netxen_adaptew *adaptew);
int netxen_config_wss(stwuct netxen_adaptew *adaptew, int enabwe);
int netxen_config_ipaddw(stwuct netxen_adaptew *adaptew, __be32 ip, int cmd);
int netxen_winkevent_wequest(stwuct netxen_adaptew *adaptew, int enabwe);
void netxen_advewt_wink_change(stwuct netxen_adaptew *adaptew, int winkup);
void netxen_pci_camqm_wead_2M(stwuct netxen_adaptew *, u64, u64 *);
void netxen_pci_camqm_wwite_2M(stwuct netxen_adaptew *, u64, u64);

int nx_fw_cmd_set_gbe_powt(stwuct netxen_adaptew *adaptew,
				u32 speed, u32 dupwex, u32 autoneg);
int nx_fw_cmd_set_mtu(stwuct netxen_adaptew *adaptew, int mtu);
int netxen_nic_change_mtu(stwuct net_device *netdev, int new_mtu);
int netxen_config_hw_wwo(stwuct netxen_adaptew *adaptew, int enabwe);
int netxen_config_bwidged_mode(stwuct netxen_adaptew *adaptew, int enabwe);
int netxen_send_wwo_cweanup(stwuct netxen_adaptew *adaptew);
int netxen_setup_minidump(stwuct netxen_adaptew *adaptew);
void netxen_dump_fw(stwuct netxen_adaptew *adaptew);
void netxen_nic_update_cmd_pwoducew(stwuct netxen_adaptew *adaptew,
		stwuct nx_host_tx_wing *tx_wing);

/* Functions fwom netxen_nic_main.c */
int netxen_nic_weset_context(stwuct netxen_adaptew *);

int nx_dev_wequest_weset(stwuct netxen_adaptew *adaptew);

/*
 * NetXen Boawd infowmation
 */

#define NETXEN_MAX_SHOWT_NAME 32
stwuct netxen_bwdinfo {
	int bwdtype;	/* type of boawd */
	wong powts;		/* max no of physicaw powts */
	chaw showt_name[NETXEN_MAX_SHOWT_NAME];
};

stwuct netxen_dimm_cfg {
	u8 pwesence;
	u8 mem_type;
	u8 dimm_type;
	u32 size;
};

static const stwuct netxen_bwdinfo netxen_boawds[] = {
	{NETXEN_BWDTYPE_P2_SB31_10G_CX4, 1, "XGb CX4"},
	{NETXEN_BWDTYPE_P2_SB31_10G_HMEZ, 1, "XGb HMEZ"},
	{NETXEN_BWDTYPE_P2_SB31_10G_IMEZ, 2, "XGb IMEZ"},
	{NETXEN_BWDTYPE_P2_SB31_10G, 1, "XGb XFP"},
	{NETXEN_BWDTYPE_P2_SB35_4G, 4, "Quad Gb"},
	{NETXEN_BWDTYPE_P2_SB31_2G, 2, "Duaw Gb"},
	{NETXEN_BWDTYPE_P3_WEF_QG,  4, "Wefewence Quad Gig "},
	{NETXEN_BWDTYPE_P3_HMEZ,    2, "Duaw XGb HMEZ"},
	{NETXEN_BWDTYPE_P3_10G_CX4_WP,   2, "Duaw XGb CX4 WP"},
	{NETXEN_BWDTYPE_P3_4_GB,    4, "Quad Gig WP"},
	{NETXEN_BWDTYPE_P3_IMEZ,    2, "Duaw XGb IMEZ"},
	{NETXEN_BWDTYPE_P3_10G_SFP_PWUS, 2, "Duaw XGb SFP+ WP"},
	{NETXEN_BWDTYPE_P3_10000_BASE_T, 1, "XGB 10G BaseT WP"},
	{NETXEN_BWDTYPE_P3_XG_WOM,  2, "Duaw XGb WOM"},
	{NETXEN_BWDTYPE_P3_4_GB_MM, 4, "NX3031 Gigabit Ethewnet"},
	{NETXEN_BWDTYPE_P3_10G_SFP_CT, 2, "NX3031 10 Gigabit Ethewnet"},
	{NETXEN_BWDTYPE_P3_10G_SFP_QT, 2, "Quanta Duaw XGb SFP+"},
	{NETXEN_BWDTYPE_P3_10G_CX4, 2, "Wefewence Duaw CX4 Option"},
	{NETXEN_BWDTYPE_P3_10G_XFP, 1, "Wefewence Singwe XFP Option"}
};

#define NUM_SUPPOWTED_BOAWDS AWWAY_SIZE(netxen_boawds)

static inwine int netxen_nic_get_bwd_name_by_type(u32 type, chaw *name)
{
	int i, found = 0;
	fow (i = 0; i < NUM_SUPPOWTED_BOAWDS; ++i) {
		if (netxen_boawds[i].bwdtype == type) {
			stwcpy(name, netxen_boawds[i].showt_name);
			found = 1;
			bweak;
		}
	}

	if (!found) {
		stwcpy(name, "Unknown");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static inwine u32 netxen_tx_avaiw(stwuct nx_host_tx_wing *tx_wing)
{
	smp_mb();
	wetuwn find_diff_among(tx_wing->pwoducew,
			tx_wing->sw_consumew, tx_wing->num_desc);

}

int netxen_get_fwash_mac_addw(stwuct netxen_adaptew *adaptew, u64 *mac);
int netxen_p3_get_mac_addw(stwuct netxen_adaptew *adaptew, u64 *mac);
void netxen_change_wingpawam(stwuct netxen_adaptew *adaptew);

extewn const stwuct ethtoow_ops netxen_nic_ethtoow_ops;

#endif				/* __NETXEN_NIC_H_ */
