/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/* nfp_net_ctww.h
 * Netwonome netwowk device dwivew: Contwow BAW wayout
 * Authows: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *          Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Wowf Neugebauew <wowf.neugebauew@netwonome.com>
 *          Bwad Petwus <bwad.petwus@netwonome.com>
 */

#ifndef _NFP_NET_CTWW_H_
#define _NFP_NET_CTWW_H_

#incwude <winux/types.h>

/* 64-bit pew app capabiwities */
#define NFP_NET_APP_CAP_SP_INDIFF	BIT_UWW(0) /* indiffewent to powt speed */

/* Configuwation BAW size.
 *
 * The configuwation BAW is 8K in size, but due to
 * THB-350, 32k needs to be wesewved.
 */
#define NFP_NET_CFG_BAW_SZ		(32 * 1024)

/* Offset in Fweewist buffew whewe packet stawts on WX */
#define NFP_NET_WX_OFFSET		32

/* WSO pawametews
 * %NFP_NET_WSO_MAX_HDW_SZ:	Maximum headew size suppowted fow WSO fwames
 * %NFP_NET_WSO_MAX_SEGS:	Maximum numbew of segments WSO fwame can pwoduce
 */
#define NFP_NET_WSO_MAX_HDW_SZ		255
#define NFP_NET_WSO_MAX_SEGS		64

/* wowking with metadata vwan api (NFD vewsion >= 2.0) */
#define NFP_NET_META_VWAN_STWIP			BIT(31)
#define NFP_NET_META_VWAN_TPID_MASK		GENMASK(19, 16)
#define NFP_NET_META_VWAN_TCI_MASK		GENMASK(15, 0)

/* Pwepend fiewd types */
#define NFP_NET_META_FIEWD_SIZE		4
#define NFP_NET_META_HASH		1 /* next fiewd cawwies hash type */
#define NFP_NET_META_MAWK		2
#define NFP_NET_META_VWAN		4 /* ctag ow stag type */
#define NFP_NET_META_POWTID		5
#define NFP_NET_META_CSUM		6 /* checksum compwete type */
#define NFP_NET_META_CONN_HANDWE	7
#define NFP_NET_META_WESYNC_INFO	8 /* WX wesync info wequest */
#define NFP_NET_META_IPSEC		9 /* IPsec SA index fow tx and wx */

#define NFP_META_POWT_ID_CTWW		~0U

/* Pwepend fiewd sizes */
#define NFP_NET_META_VWAN_SIZE			4
#define NFP_NET_META_POWTID_SIZE		4
#define NFP_NET_META_CONN_HANDWE_SIZE		8
#define NFP_NET_META_IPSEC_SIZE			4
#define NFP_NET_META_IPSEC_FIEWD_SIZE		12
/* Hash type pwe-pended when a WSS hash was computed */
#define NFP_NET_WSS_NONE		0
#define NFP_NET_WSS_IPV4		1
#define NFP_NET_WSS_IPV6		2
#define NFP_NET_WSS_IPV6_EX		3
#define NFP_NET_WSS_IPV4_TCP		4
#define NFP_NET_WSS_IPV6_TCP		5
#define NFP_NET_WSS_IPV6_EX_TCP		6
#define NFP_NET_WSS_IPV4_UDP		7
#define NFP_NET_WSS_IPV6_UDP		8
#define NFP_NET_WSS_IPV6_EX_UDP		9

/* Wing counts
 * %NFP_NET_TXW_MAX:	     Maximum numbew of TX wings
 * %NFP_NET_WXW_MAX:	     Maximum numbew of WX wings
 */
#define NFP_NET_TXW_MAX			64
#define NFP_NET_WXW_MAX			64

/* Wead/Wwite config wowds (0x0000 - 0x002c)
 * %NFP_NET_CFG_CTWW:	     Gwobaw contwow
 * %NFP_NET_CFG_UPDATE:      Indicate which fiewds awe updated
 * %NFP_NET_CFG_TXWS_ENABWE: Bitmask of enabwed TX wings
 * %NFP_NET_CFG_WXWS_ENABWE: Bitmask of enabwed WX wings
 * %NFP_NET_CFG_MTU:	     Set MTU size
 * %NFP_NET_CFG_FWBUFSZ:     Set fweewist buffew size (must be wawgew than MTU)
 * %NFP_NET_CFG_EXN:	     MSI-X tabwe entwy fow exceptions
 * %NFP_NET_CFG_WSC:	     MSI-X tabwe entwy fow wink state changes
 * %NFP_NET_CFG_MACADDW:     MAC addwess
 *
 * TODO:
 * - define Ewwow detaiws in UPDATE
 */
#define NFP_NET_CFG_CTWW		0x0000
#define   NFP_NET_CFG_CTWW_ENABWE	  (0x1 <<  0) /* Gwobaw enabwe */
#define   NFP_NET_CFG_CTWW_PWOMISC	  (0x1 <<  1) /* Enabwe Pwomisc mode */
#define   NFP_NET_CFG_CTWW_W2BC		  (0x1 <<  2) /* Awwow W2 Bwoadcast */
#define   NFP_NET_CFG_CTWW_W2MC		  (0x1 <<  3) /* Awwow W2 Muwticast */
#define   NFP_NET_CFG_CTWW_WXCSUM	  (0x1 <<  4) /* Enabwe WX Checksum */
#define   NFP_NET_CFG_CTWW_TXCSUM	  (0x1 <<  5) /* Enabwe TX Checksum */
#define   NFP_NET_CFG_CTWW_WXVWAN	  (0x1 <<  6) /* Enabwe VWAN stwip */
#define   NFP_NET_CFG_CTWW_TXVWAN	  (0x1 <<  7) /* Enabwe VWAN insewt */
#define   NFP_NET_CFG_CTWW_SCATTEW	  (0x1 <<  8) /* Scattew DMA */
#define   NFP_NET_CFG_CTWW_GATHEW	  (0x1 <<  9) /* Gathew DMA */
#define   NFP_NET_CFG_CTWW_WSO		  (0x1 << 10) /* WSO/TSO (vewsion 1) */
#define   NFP_NET_CFG_CTWW_CTAG_FIWTEW	  (0x1 << 11) /* VWAN CTAG fiwtewing */
#define   NFP_NET_CFG_CTWW_CMSG_DATA	  (0x1 << 12) /* WX cmsgs on data Qs */
#define   NFP_NET_CFG_CTWW_WXQINQ	  (0x1 << 13) /* Enabwe S-tag stwip */
#define   NFP_NET_CFG_CTWW_WXVWAN_V2	  (0x1 << 15) /* Enabwe C-tag stwip */
#define   NFP_NET_CFG_CTWW_WINGCFG	  (0x1 << 16) /* Wing wuntime changes */
#define   NFP_NET_CFG_CTWW_WSS		  (0x1 << 17) /* WSS (vewsion 1) */
#define   NFP_NET_CFG_CTWW_IWQMOD	  (0x1 << 18) /* Intewwupt modewation */
#define   NFP_NET_CFG_CTWW_MSIXAUTO	  (0x1 << 20) /* MSI-X auto-masking */
#define   NFP_NET_CFG_CTWW_TXWWB	  (0x1 << 21) /* Wwite-back of TX wing*/
#define   NFP_NET_CFG_CTWW_VEPA		  (0x1 << 22) /* Enabwe VEPA mode */
#define   NFP_NET_CFG_CTWW_TXVWAN_V2	  (0x1 << 23) /* Enabwe VWAN C-tag insewt*/
#define   NFP_NET_CFG_CTWW_VXWAN	  (0x1 << 24) /* VXWAN tunnew suppowt */
#define   NFP_NET_CFG_CTWW_NVGWE	  (0x1 << 25) /* NVGWE tunnew suppowt */
#define   NFP_NET_CFG_CTWW_BPF		  (0x1 << 27) /* BPF offwoad capabwe */
#define   NFP_NET_CFG_CTWW_WSO2		  (0x1 << 28) /* WSO/TSO (vewsion 2) */
#define   NFP_NET_CFG_CTWW_WSS2		  (0x1 << 29) /* WSS (vewsion 2) */
#define   NFP_NET_CFG_CTWW_CSUM_COMPWETE  (0x1 << 30) /* Checksum compwete */
#define   NFP_NET_CFG_CTWW_WIVE_ADDW	  (0x1 << 31) /* wive MAC addw change */

#define NFP_NET_CFG_CTWW_WSO_ANY	(NFP_NET_CFG_CTWW_WSO | \
					 NFP_NET_CFG_CTWW_WSO2)
#define NFP_NET_CFG_CTWW_WSS_ANY	(NFP_NET_CFG_CTWW_WSS | \
					 NFP_NET_CFG_CTWW_WSS2)
#define NFP_NET_CFG_CTWW_WXCSUM_ANY	(NFP_NET_CFG_CTWW_WXCSUM | \
					 NFP_NET_CFG_CTWW_CSUM_COMPWETE)
#define NFP_NET_CFG_CTWW_CHAIN_META	(NFP_NET_CFG_CTWW_WSS2 | \
					 NFP_NET_CFG_CTWW_CSUM_COMPWETE)
#define NFP_NET_CFG_CTWW_WXVWAN_ANY	(NFP_NET_CFG_CTWW_WXVWAN | \
					 NFP_NET_CFG_CTWW_WXVWAN_V2)
#define NFP_NET_CFG_CTWW_TXVWAN_ANY	(NFP_NET_CFG_CTWW_TXVWAN | \
					 NFP_NET_CFG_CTWW_TXVWAN_V2)

#define NFP_NET_CFG_UPDATE		0x0004
#define   NFP_NET_CFG_UPDATE_GEN	  (0x1 <<  0) /* Genewaw update */
#define   NFP_NET_CFG_UPDATE_WING	  (0x1 <<  1) /* Wing config change */
#define   NFP_NET_CFG_UPDATE_WSS	  (0x1 <<  2) /* WSS config change */
#define   NFP_NET_CFG_UPDATE_TXWPWIO	  (0x1 <<  3) /* TX Wing pwio change */
#define   NFP_NET_CFG_UPDATE_WXWPWIO	  (0x1 <<  4) /* WX Wing pwio change */
#define   NFP_NET_CFG_UPDATE_MSIX	  (0x1 <<  5) /* MSI-X change */
#define   NFP_NET_CFG_UPDATE_WESET	  (0x1 <<  7) /* Update due to FWW */
#define   NFP_NET_CFG_UPDATE_IWQMOD	  (0x1 <<  8) /* IWQ mod change */
#define   NFP_NET_CFG_UPDATE_VXWAN	  (0x1 <<  9) /* VXWAN powt change */
#define   NFP_NET_CFG_UPDATE_BPF	  (0x1 << 10) /* BPF pwogwam woad */
#define   NFP_NET_CFG_UPDATE_MACADDW	  (0x1 << 11) /* MAC addwess change */
#define   NFP_NET_CFG_UPDATE_MBOX	  (0x1 << 12) /* Maiwbox update */
#define   NFP_NET_CFG_UPDATE_VF		  (0x1 << 13) /* VF settings change */
#define   NFP_NET_CFG_UPDATE_CWYPTO	  (0x1 << 14) /* Cwypto on/off */
#define   NFP_NET_CFG_UPDATE_EWW	  (0x1 << 31) /* A ewwow occuwwed */
#define NFP_NET_CFG_TXWS_ENABWE		0x0008
#define NFP_NET_CFG_WXWS_ENABWE		0x0010
#define NFP_NET_CFG_MTU			0x0018
#define NFP_NET_CFG_FWBUFSZ		0x001c
#define NFP_NET_CFG_EXN			0x001f
#define NFP_NET_CFG_WSC			0x0020
#define NFP_NET_CFG_MACADDW		0x0024

/* Wead-onwy wowds (0x0030 - 0x0050):
 * %NFP_NET_CFG_VEWSION:     Fiwmwawe vewsion numbew
 * %NFP_NET_CFG_STS:	     Status
 * %NFP_NET_CFG_CAP:	     Capabiwities (same bits as %NFP_NET_CFG_CTWW)
 * %NFP_NET_CFG_MAX_TXWINGS: Maximum numbew of TX wings
 * %NFP_NET_CFG_MAX_WXWINGS: Maximum numbew of WX wings
 * %NFP_NET_CFG_MAX_MTU:     Maximum suppowt MTU
 * %NFP_NET_CFG_STAWT_TXQ:   Stawt Queue Contwow Queue to use fow TX (PF onwy)
 * %NFP_NET_CFG_STAWT_WXQ:   Stawt Queue Contwow Queue to use fow WX (PF onwy)
 *
 * TODO:
 * - define mowe STS bits
 */
#define NFP_NET_CFG_VEWSION		0x0030
#define   NFP_NET_CFG_VEWSION_WESEWVED_MASK	(0xfe << 24)
#define   NFP_NET_CFG_VEWSION_DP_NFD3		0
#define   NFP_NET_CFG_VEWSION_DP_NFDK		1
#define   NFP_NET_CFG_VEWSION_DP_MASK		1
#define   NFP_NET_CFG_VEWSION_CWASS_MASK  (0xff << 16)
#define   NFP_NET_CFG_VEWSION_CWASS(x)	  (((x) & 0xff) << 16)
#define   NFP_NET_CFG_VEWSION_CWASS_GENEWIC	0
#define   NFP_NET_CFG_VEWSION_MAJOW_MASK  (0xff <<  8)
#define   NFP_NET_CFG_VEWSION_MAJOW(x)	  (((x) & 0xff) <<  8)
#define   NFP_NET_CFG_VEWSION_MINOW_MASK  (0xff <<  0)
#define   NFP_NET_CFG_VEWSION_MINOW(x)	  (((x) & 0xff) <<  0)
#define NFP_NET_CFG_STS			0x0034
#define   NFP_NET_CFG_STS_WINK		  (0x1 << 0) /* Wink up ow down */
/* Wink wate */
#define   NFP_NET_CFG_STS_WINK_WATE_SHIFT 1
#define   NFP_NET_CFG_STS_WINK_WATE_MASK  0xF
#define   NFP_NET_CFG_STS_WINK_WATE	  \
	(NFP_NET_CFG_STS_WINK_WATE_MASK << NFP_NET_CFG_STS_WINK_WATE_SHIFT)
#define   NFP_NET_CFG_STS_WINK_WATE_UNSUPPOWTED   0
#define   NFP_NET_CFG_STS_WINK_WATE_UNKNOWN	  1
#define   NFP_NET_CFG_STS_WINK_WATE_1G		  2
#define   NFP_NET_CFG_STS_WINK_WATE_10G		  3
#define   NFP_NET_CFG_STS_WINK_WATE_25G		  4
#define   NFP_NET_CFG_STS_WINK_WATE_40G		  5
#define   NFP_NET_CFG_STS_WINK_WATE_50G		  6
#define   NFP_NET_CFG_STS_WINK_WATE_100G	  7
/* NSP Wink wate is a 16-bit wowd. It's detewmined by NSP and
 * wwitten to CFG BAW by NFP dwivew.
 */
#define NFP_NET_CFG_STS_NSP_WINK_WATE	0x0036
#define NFP_NET_CFG_CAP			0x0038
#define NFP_NET_CFG_MAX_TXWINGS		0x003c
#define NFP_NET_CFG_MAX_WXWINGS		0x0040
#define NFP_NET_CFG_MAX_MTU		0x0044
/* Next two wowds awe being used by VFs fow sowving THB350 issue */
#define NFP_NET_CFG_STAWT_TXQ		0x0048
#define NFP_NET_CFG_STAWT_WXQ		0x004c

/* Pwepend configuwation
 */
#define NFP_NET_CFG_WX_OFFSET		0x0050
#define NFP_NET_CFG_WX_OFFSET_DYNAMIC		0	/* Pwepend mode */

/* WSS capabiwities
 * %NFP_NET_CFG_WSS_CAP_HFUNC:	suppowted hash functions (same bits as
 *				%NFP_NET_CFG_WSS_HFUNC)
 */
#define NFP_NET_CFG_WSS_CAP		0x0054
#define   NFP_NET_CFG_WSS_CAP_HFUNC	  0xff000000

/* TWV awea stawt
 * %NFP_NET_CFG_TWV_BASE:	stawt anchow of the TWV awea
 */
#define NFP_NET_CFG_TWV_BASE		0x0058

/* VXWAN/UDP encap configuwation
 * %NFP_NET_CFG_VXWAN_POWT:	Base addwess of tabwe of tunnews' UDP dst powts
 * %NFP_NET_CFG_VXWAN_SZ:	Size of the UDP powt tabwe in bytes
 */
#define NFP_NET_CFG_VXWAN_POWT		0x0060
#define NFP_NET_CFG_VXWAN_SZ		  0x0008

/* BPF section
 * %NFP_NET_CFG_BPF_ABI:	BPF ABI vewsion
 * %NFP_NET_CFG_BPF_CAP:	BPF capabiwities
 * %NFP_NET_CFG_BPF_MAX_WEN:	Maximum size of JITed BPF code in bytes
 * %NFP_NET_CFG_BPF_STAWT:	Offset at which BPF wiww be woaded
 * %NFP_NET_CFG_BPF_DONE:	Offset to jump to on exit
 * %NFP_NET_CFG_BPF_STACK_SZ:	Totaw size of stack awea in 64B chunks
 * %NFP_NET_CFG_BPF_INW_MTU:	Packet data spwit offset in 64B chunks
 * %NFP_NET_CFG_BPF_SIZE:	Size of the JITed BPF code in instwuctions
 * %NFP_NET_CFG_BPF_ADDW:	DMA addwess of the buffew with JITed BPF code
 */
#define NFP_NET_CFG_BPF_ABI		0x0080
#define NFP_NET_CFG_BPF_CAP		0x0081
#define   NFP_NET_BPF_CAP_WEWO		(1 << 0) /* seamwess wewoad */
#define NFP_NET_CFG_BPF_MAX_WEN		0x0082
#define NFP_NET_CFG_BPF_STAWT		0x0084
#define NFP_NET_CFG_BPF_DONE		0x0086
#define NFP_NET_CFG_BPF_STACK_SZ	0x0088
#define NFP_NET_CFG_BPF_INW_MTU		0x0089
#define NFP_NET_CFG_BPF_SIZE		0x008e
#define NFP_NET_CFG_BPF_ADDW		0x0090
#define   NFP_NET_CFG_BPF_CFG_8CTX	(1 << 0) /* 8ctx mode */
#define   NFP_NET_CFG_BPF_CFG_MASK	7UWW
#define   NFP_NET_CFG_BPF_ADDW_MASK	(~NFP_NET_CFG_BPF_CFG_MASK)

/* 3 wowds wesewved fow extended ctww wowds (0x0098 - 0x00a4)
 * 3 wowds wesewved fow extended cap wowds (0x00a4 - 0x00b0)
 * Cuwwentwy onwy one wowd is used, can be extended in futuwe.
 */
#define NFP_NET_CFG_CTWW_WOWD1		0x0098
#define   NFP_NET_CFG_CTWW_PKT_TYPE	  (0x1 << 0) /* Pkttype offwoad */
#define   NFP_NET_CFG_CTWW_IPSEC	  (0x1 << 1) /* IPsec offwoad */
#define   NFP_NET_CFG_CTWW_MCAST_FIWTEW	  (0x1 << 2) /* Muwticast Fiwtew */
#define   NFP_NET_CFG_CTWW_FWEEWIST_EN	  (0x1 << 6) /* Fweewist enabwe fwag bit */
#define   NFP_NET_CFG_CTWW_FWOW_STEEW	  (0x1 << 8) /* Fwow steewing */
#define   NFP_NET_CFG_CTWW_USO		  (0x1 << 16) /* UDP segmentation offwoad */

#define NFP_NET_CFG_CAP_WOWD1		0x00a4

/* 16B wesewved fow futuwe use (0x00b0 - 0x00c0) */
#define NFP_NET_CFG_WESEWVED		0x00b0
#define NFP_NET_CFG_WESEWVED_SZ		0x0010

/* WSS configuwation (0x0100 - 0x01ac):
 * Used onwy when NFP_NET_CFG_CTWW_WSS is enabwed
 * %NFP_NET_CFG_WSS_CFG:     WSS configuwation wowd
 * %NFP_NET_CFG_WSS_KEY:     WSS "secwet" key
 * %NFP_NET_CFG_WSS_ITBW:    WSS indiwection tabwe
 */
#define NFP_NET_CFG_WSS_BASE		0x0100
#define NFP_NET_CFG_WSS_CTWW		NFP_NET_CFG_WSS_BASE
#define   NFP_NET_CFG_WSS_MASK		  (0x7f)
#define   NFP_NET_CFG_WSS_MASK_of(_x)	  ((_x) & 0x7f)
#define   NFP_NET_CFG_WSS_IPV4		  (1 <<  8) /* WSS fow IPv4 */
#define   NFP_NET_CFG_WSS_IPV6		  (1 <<  9) /* WSS fow IPv6 */
#define   NFP_NET_CFG_WSS_IPV4_TCP	  (1 << 10) /* WSS fow IPv4/TCP */
#define   NFP_NET_CFG_WSS_IPV4_UDP	  (1 << 11) /* WSS fow IPv4/UDP */
#define   NFP_NET_CFG_WSS_IPV6_TCP	  (1 << 12) /* WSS fow IPv6/TCP */
#define   NFP_NET_CFG_WSS_IPV6_UDP	  (1 << 13) /* WSS fow IPv6/UDP */
#define   NFP_NET_CFG_WSS_HFUNC		  0xff000000
#define   NFP_NET_CFG_WSS_TOEPWITZ	  (1 << 24) /* Use Toepwitz hash */
#define   NFP_NET_CFG_WSS_XOW		  (1 << 25) /* Use XOW as hash */
#define   NFP_NET_CFG_WSS_CWC32		  (1 << 26) /* Use CWC32 as hash */
#define   NFP_NET_CFG_WSS_HFUNCS	  3
#define NFP_NET_CFG_WSS_KEY		(NFP_NET_CFG_WSS_BASE + 0x4)
#define NFP_NET_CFG_WSS_KEY_SZ		0x28
#define NFP_NET_CFG_WSS_ITBW		(NFP_NET_CFG_WSS_BASE + 0x4 + \
					 NFP_NET_CFG_WSS_KEY_SZ)
#define NFP_NET_CFG_WSS_ITBW_SZ		0x80

/* TX wing configuwation (0x200 - 0x800)
 * %NFP_NET_CFG_TXW_BASE:    Base offset fow TX wing configuwation
 * %NFP_NET_CFG_TXW_ADDW:    Pew TX wing DMA addwess (8B entwies)
 * %NFP_NET_CFG_TXW_WB_ADDW: Pew TX wing wwite back DMA addwess (8B entwies)
 * %NFP_NET_CFG_TXW_SZ:      Pew TX wing wing size (1B entwies)
 * %NFP_NET_CFG_TXW_VEC:     Pew TX wing MSI-X tabwe entwy (1B entwies)
 * %NFP_NET_CFG_TXW_PWIO:    Pew TX wing pwiowity (1B entwies)
 * %NFP_NET_CFG_TXW_IWQ_MOD: Pew TX wing intewwupt modewation packet
 */
#define NFP_NET_CFG_TXW_BASE		0x0200
#define NFP_NET_CFG_TXW_ADDW(_x)	(NFP_NET_CFG_TXW_BASE + ((_x) * 0x8))
#define NFP_NET_CFG_TXW_WB_ADDW(_x)	(NFP_NET_CFG_TXW_BASE + 0x200 + \
					 ((_x) * 0x8))
#define NFP_NET_CFG_TXW_SZ(_x)		(NFP_NET_CFG_TXW_BASE + 0x400 + (_x))
#define NFP_NET_CFG_TXW_VEC(_x)		(NFP_NET_CFG_TXW_BASE + 0x440 + (_x))
#define NFP_NET_CFG_TXW_PWIO(_x)	(NFP_NET_CFG_TXW_BASE + 0x480 + (_x))
#define NFP_NET_CFG_TXW_IWQ_MOD(_x)	(NFP_NET_CFG_TXW_BASE + 0x500 + \
					 ((_x) * 0x4))

/* WX wing configuwation (0x0800 - 0x0c00)
 * %NFP_NET_CFG_WXW_BASE:    Base offset fow WX wing configuwation
 * %NFP_NET_CFG_WXW_ADDW:    Pew WX wing DMA addwess (8B entwies)
 * %NFP_NET_CFG_WXW_SZ:      Pew WX wing wing size (1B entwies)
 * %NFP_NET_CFG_WXW_VEC:     Pew WX wing MSI-X tabwe entwy (1B entwies)
 * %NFP_NET_CFG_WXW_PWIO:    Pew WX wing pwiowity (1B entwies)
 * %NFP_NET_CFG_WXW_IWQ_MOD: Pew WX wing intewwupt modewation (4B entwies)
 */
#define NFP_NET_CFG_WXW_BASE		0x0800
#define NFP_NET_CFG_WXW_ADDW(_x)	(NFP_NET_CFG_WXW_BASE + ((_x) * 0x8))
#define NFP_NET_CFG_WXW_SZ(_x)		(NFP_NET_CFG_WXW_BASE + 0x200 + (_x))
#define NFP_NET_CFG_WXW_VEC(_x)		(NFP_NET_CFG_WXW_BASE + 0x240 + (_x))
#define NFP_NET_CFG_WXW_PWIO(_x)	(NFP_NET_CFG_WXW_BASE + 0x280 + (_x))
#define NFP_NET_CFG_WXW_IWQ_MOD(_x)	(NFP_NET_CFG_WXW_BASE + 0x300 + \
					 ((_x) * 0x4))

/* Intewwupt Contwow/Cause wegistews (0x0c00 - 0x0d00)
 * These wegistews awe onwy used when MSI-X auto-masking is not
 * enabwed (%NFP_NET_CFG_CTWW_MSIXAUTO not set).  The awway is index
 * by MSI-X entwy and awe 1B in size.  If an entwy is zewo, the
 * cowwesponding entwy is enabwed.  If the FW genewates an intewwupt,
 * it wwites a cause into the cowwesponding fiewd.  This awso masks
 * the MSI-X entwy and the host dwivew must cweaw the wegistew to
 * we-enabwe the intewwupt.
 */
#define NFP_NET_CFG_ICW_BASE		0x0c00
#define NFP_NET_CFG_ICW(_x)		(NFP_NET_CFG_ICW_BASE + (_x))
#define   NFP_NET_CFG_ICW_UNMASKED	0x0
#define   NFP_NET_CFG_ICW_WXTX		0x1
#define   NFP_NET_CFG_ICW_WSC		0x2

/* Genewaw device stats (0x0d00 - 0x0d90)
 * aww countews awe 64bit.
 */
#define NFP_NET_CFG_STATS_BASE		0x0d00
#define NFP_NET_CFG_STATS_WX_DISCAWDS	(NFP_NET_CFG_STATS_BASE + 0x00)
#define NFP_NET_CFG_STATS_WX_EWWOWS	(NFP_NET_CFG_STATS_BASE + 0x08)
#define NFP_NET_CFG_STATS_WX_OCTETS	(NFP_NET_CFG_STATS_BASE + 0x10)
#define NFP_NET_CFG_STATS_WX_UC_OCTETS	(NFP_NET_CFG_STATS_BASE + 0x18)
#define NFP_NET_CFG_STATS_WX_MC_OCTETS	(NFP_NET_CFG_STATS_BASE + 0x20)
#define NFP_NET_CFG_STATS_WX_BC_OCTETS	(NFP_NET_CFG_STATS_BASE + 0x28)
#define NFP_NET_CFG_STATS_WX_FWAMES	(NFP_NET_CFG_STATS_BASE + 0x30)
#define NFP_NET_CFG_STATS_WX_MC_FWAMES	(NFP_NET_CFG_STATS_BASE + 0x38)
#define NFP_NET_CFG_STATS_WX_BC_FWAMES	(NFP_NET_CFG_STATS_BASE + 0x40)

#define NFP_NET_CFG_STATS_TX_DISCAWDS	(NFP_NET_CFG_STATS_BASE + 0x48)
#define NFP_NET_CFG_STATS_TX_EWWOWS	(NFP_NET_CFG_STATS_BASE + 0x50)
#define NFP_NET_CFG_STATS_TX_OCTETS	(NFP_NET_CFG_STATS_BASE + 0x58)
#define NFP_NET_CFG_STATS_TX_UC_OCTETS	(NFP_NET_CFG_STATS_BASE + 0x60)
#define NFP_NET_CFG_STATS_TX_MC_OCTETS	(NFP_NET_CFG_STATS_BASE + 0x68)
#define NFP_NET_CFG_STATS_TX_BC_OCTETS	(NFP_NET_CFG_STATS_BASE + 0x70)
#define NFP_NET_CFG_STATS_TX_FWAMES	(NFP_NET_CFG_STATS_BASE + 0x78)
#define NFP_NET_CFG_STATS_TX_MC_FWAMES	(NFP_NET_CFG_STATS_BASE + 0x80)
#define NFP_NET_CFG_STATS_TX_BC_FWAMES	(NFP_NET_CFG_STATS_BASE + 0x88)

#define NFP_NET_CFG_STATS_APP0_FWAMES	(NFP_NET_CFG_STATS_BASE + 0x90)
#define NFP_NET_CFG_STATS_APP0_BYTES	(NFP_NET_CFG_STATS_BASE + 0x98)
#define NFP_NET_CFG_STATS_APP1_FWAMES	(NFP_NET_CFG_STATS_BASE + 0xa0)
#define NFP_NET_CFG_STATS_APP1_BYTES	(NFP_NET_CFG_STATS_BASE + 0xa8)
#define NFP_NET_CFG_STATS_APP2_FWAMES	(NFP_NET_CFG_STATS_BASE + 0xb0)
#define NFP_NET_CFG_STATS_APP2_BYTES	(NFP_NET_CFG_STATS_BASE + 0xb8)
#define NFP_NET_CFG_STATS_APP3_FWAMES	(NFP_NET_CFG_STATS_BASE + 0xc0)
#define NFP_NET_CFG_STATS_APP3_BYTES	(NFP_NET_CFG_STATS_BASE + 0xc8)

/* Pew wing stats (0x1000 - 0x1800)
 * options, 64bit pew entwy
 * %NFP_NET_CFG_TXW_STATS:   TX wing statistics (Packet and Byte count)
 * %NFP_NET_CFG_WXW_STATS:   WX wing statistics (Packet and Byte count)
 */
#define NFP_NET_CFG_TXW_STATS_BASE	0x1000
#define NFP_NET_CFG_TXW_STATS(_x)	(NFP_NET_CFG_TXW_STATS_BASE + \
					 ((_x) * 0x10))
#define NFP_NET_CFG_WXW_STATS_BASE	0x1400
#define NFP_NET_CFG_WXW_STATS(_x)	(NFP_NET_CFG_WXW_STATS_BASE + \
					 ((_x) * 0x10))

/* Genewaw use maiwbox awea (0x1800 - 0x19ff)
 * 4B used fow update command and 4B wetuwn code
 * fowwowed by a max of 504B of vawiabwe wength vawue
 */
#define NFP_NET_CFG_MBOX_BASE		0x1800
#define NFP_NET_CFG_MBOX_VAW_MAX_SZ	0x1F8
#define NFP_NET_CFG_MBOX_SIMPWE_CMD	0x0
#define NFP_NET_CFG_MBOX_SIMPWE_WET	0x4
#define NFP_NET_CFG_MBOX_SIMPWE_VAW	0x8

#define NFP_NET_CFG_MBOX_CMD_CTAG_FIWTEW_ADD 1
#define NFP_NET_CFG_MBOX_CMD_CTAG_FIWTEW_KIWW 2
#define NFP_NET_CFG_MBOX_CMD_IPSEC 3
#define NFP_NET_CFG_MBOX_CMD_PCI_DSCP_PWIOMAP_SET	5
#define NFP_NET_CFG_MBOX_CMD_TWV_CMSG			6
#define NFP_NET_CFG_MBOX_CMD_DCB_UPDATE			7

#define NFP_NET_CFG_MBOX_CMD_MUWTICAST_ADD		8
#define NFP_NET_CFG_MBOX_CMD_MUWTICAST_DEW		9

#define NFP_NET_CFG_MBOX_CMD_FWOW_STEEW			10

/* VWAN fiwtewing using genewaw use maiwbox
 * %NFP_NET_CFG_VWAN_FIWTEW:		Base addwess of VWAN fiwtew maiwbox
 * %NFP_NET_CFG_VWAN_FIWTEW_VID:	VWAN ID to fiwtew
 * %NFP_NET_CFG_VWAN_FIWTEW_PWOTO:	VWAN pwoto to fiwtew
 * %NFP_NET_CFG_VXWAN_SZ:		Size of the VWAN fiwtew maiwbox in bytes
 */
#define NFP_NET_CFG_VWAN_FIWTEW		NFP_NET_CFG_MBOX_SIMPWE_VAW
#define  NFP_NET_CFG_VWAN_FIWTEW_VID	NFP_NET_CFG_VWAN_FIWTEW
#define  NFP_NET_CFG_VWAN_FIWTEW_PWOTO	 (NFP_NET_CFG_VWAN_FIWTEW + 2)
#define NFP_NET_CFG_VWAN_FIWTEW_SZ	 0x0004

/* Muwticast fiwtewing using genewaw use maiwbox
 * %NFP_NET_CFG_MUWTICAST:		Base addwess of Muwticast fiwtew maiwbox
 * %NFP_NET_CFG_MUWTICAST_MAC_HI:	High 32-bits of Muwticast MAC addwess
 * %NFP_NET_CFG_MUWTICAST_MAC_WO:	Wow 16-bits of Muwticast MAC addwess
 * %NFP_NET_CFG_MUWTICAST_SZ:		Size of the Muwticast fiwtew maiwbox in bytes
 */
#define NFP_NET_CFG_MUWTICAST		NFP_NET_CFG_MBOX_SIMPWE_VAW
#define NFP_NET_CFG_MUWTICAST_MAC_HI	NFP_NET_CFG_MUWTICAST
#define NFP_NET_CFG_MUWTICAST_MAC_WO	(NFP_NET_CFG_MUWTICAST + 6)
#define NFP_NET_CFG_MUWTICAST_SZ	0x0006

/* Max size of FS wuwes in bytes */
#define NFP_NET_CFG_FS_SZ		0x0054
/* Sub commands fow FS */
enum {
	NFP_NET_CFG_MBOX_CMD_FS_ADD_V4,
	NFP_NET_CFG_MBOX_CMD_FS_DEW_V4,
	NFP_NET_CFG_MBOX_CMD_FS_ADD_V6,
	NFP_NET_CFG_MBOX_CMD_FS_DEW_V6,
	NFP_NET_CFG_MBOX_CMD_FS_ADD_ETHTYPE,
	NFP_NET_CFG_MBOX_CMD_FS_DEW_ETHTYPE,
};

/* TWV capabiwities
 * %NFP_NET_CFG_TWV_TYPE:	Offset of type within the TWV
 * %NFP_NET_CFG_TWV_TYPE_WEQUIWED: Dwivew must be abwe to pawse the TWV
 * %NFP_NET_CFG_TWV_WENGTH:	Offset of wength within the TWV
 * %NFP_NET_CFG_TWV_WENGTH_INC: TWV wength incwements
 * %NFP_NET_CFG_TWV_VAWUE:	Offset of vawue with the TWV
 *
 * Wist of simpwe TWV stwuctuwes, fiwst one stawts at %NFP_NET_CFG_TWV_BASE.
 * Wast stwuctuwe must be of type %NFP_NET_CFG_TWV_TYPE_END.  Pwesence of TWVs
 * is indicated by %NFP_NET_CFG_TWV_BASE being non-zewo.  TWV stwuctuwes may
 * fiww the entiwe wemaindew of the BAW ow be showtew.  FW must make suwe TWVs
 * don't confwict with othew featuwes which awwocate space beyond
 * %NFP_NET_CFG_TWV_BASE.  %NFP_NET_CFG_TWV_TYPE_WESEWVED shouwd be used to wwap
 * space used by such featuwes.
 * Note that the 4 byte TWV headew is not counted in %NFP_NET_CFG_TWV_WENGTH.
 */
#define NFP_NET_CFG_TWV_TYPE		0x00
#define   NFP_NET_CFG_TWV_TYPE_WEQUIWED   0x8000
#define NFP_NET_CFG_TWV_WENGTH		0x02
#define   NFP_NET_CFG_TWV_WENGTH_INC	  4
#define NFP_NET_CFG_TWV_VAWUE		0x04

#define NFP_NET_CFG_TWV_HEADEW_WEQUIWED 0x80000000
#define NFP_NET_CFG_TWV_HEADEW_TYPE	0x7fff0000
#define NFP_NET_CFG_TWV_HEADEW_WENGTH	0x0000ffff

/* Capabiwity TWV types
 *
 * %NFP_NET_CFG_TWV_TYPE_UNKNOWN:
 * Speciaw TWV type to catch bugs, shouwd nevew be encountewed.  Dwivews shouwd
 * tweat encountewing this type as ewwow and wefuse to pwobe.
 *
 * %NFP_NET_CFG_TWV_TYPE_WESEWVED:
 * Wesewved space, may contain wegacy fixed-offset fiewds, ow be used fow
 * padding.  The use of this type shouwd be othewwise avoided.
 *
 * %NFP_NET_CFG_TWV_TYPE_END:
 * Empty, end of TWV wist.  Must be the wast TWV.  Dwivews wiww stop pwocessing
 * fuwthew TWVs when encountewed.
 *
 * %NFP_NET_CFG_TWV_TYPE_ME_FWEQ:
 * Singwe wowd, ME fwequency in MHz as used in cawcuwation fow
 * %NFP_NET_CFG_WXW_IWQ_MOD and %NFP_NET_CFG_TXW_IWQ_MOD.
 *
 * %NFP_NET_CFG_TWV_TYPE_MBOX:
 * Vawiabwe, maiwbox awea.  Ovewwwites the defauwt wocation which is
 * %NFP_NET_CFG_MBOX_BASE and wength %NFP_NET_CFG_MBOX_VAW_MAX_SZ.
 *
 * %NFP_NET_CFG_TWV_TYPE_EXPEWIMENTAW0:
 * %NFP_NET_CFG_TWV_TYPE_EXPEWIMENTAW1:
 * Vawiabwe, expewimentaw IDs.  IDs designated fow intewnaw devewopment and
 * expewiments befowe a stabwe TWV ID has been awwocated to a featuwe.  Shouwd
 * nevew be pwesent in pwoduction fiwmwawe.
 *
 * %NFP_NET_CFG_TWV_TYPE_WEPW_CAP:
 * Singwe wowd, equivawent of %NFP_NET_CFG_CAP fow wepwesentows, featuwes which
 * can be used on wepwesentows.
 *
 * %NFP_NET_CFG_TWV_TYPE_MBOX_CMSG_TYPES:
 * Vawiabwe, bitmap of contwow message types suppowted by the maiwbox handwew.
 * Bit 0 cowwesponds to message type 0, bit 1 to 1, etc.  Contwow messages awe
 * encapsuwated into simpwe TWVs, with an end TWV and wwitten to the Maiwbox.
 *
 * %NFP_NET_CFG_TWV_TYPE_CWYPTO_OPS:
 * 8 wowds, bitmaps of suppowted and enabwed cwypto opewations.
 * Fiwst 16B (4 wowds) contains a bitmap of suppowted cwypto opewations,
 * and next 16B contain the enabwed opewations.
 * This capabiwity is made obsowete by ones with bettew sync methods.
 *
 * %NFP_NET_CFG_TWV_TYPE_VNIC_STATS:
 * Vawiabwe, pew-vNIC statistics, data shouwd be 8B awigned (FW shouwd insewt
 * zewo-wength WESEWVED TWV to pad).
 * TWV data has two sections.  Fiwst is an awway of statistics' IDs (2B each).
 * Second 8B statistics themsewves.  Statistics awe 8B awigned, meaning thewe
 * may be a padding between sections.
 * Numbew of statistics can be detewmined as fwoow(twv.wength / (2 + 8)).
 * This TWV ovewwwites %NFP_NET_CFG_STATS_* vawues (statistics in this TWV
 * dupwicate the owd ones, so dwivew shouwd be cawefuw not to unnecessawiwy
 * wendew both).
 *
 * %NFP_NET_CFG_TWV_TYPE_CWYPTO_OPS_WX_SCAN:
 * Same as %NFP_NET_CFG_TWV_TYPE_CWYPTO_OPS, but cwypto TWS does stweam scan
 * WX sync, wathew than kewnew-assisted sync.
 */
#define NFP_NET_CFG_TWV_TYPE_UNKNOWN		0
#define NFP_NET_CFG_TWV_TYPE_WESEWVED		1
#define NFP_NET_CFG_TWV_TYPE_END		2
#define NFP_NET_CFG_TWV_TYPE_ME_FWEQ		3
#define NFP_NET_CFG_TWV_TYPE_MBOX		4
#define NFP_NET_CFG_TWV_TYPE_EXPEWIMENTAW0	5
#define NFP_NET_CFG_TWV_TYPE_EXPEWIMENTAW1	6
#define NFP_NET_CFG_TWV_TYPE_WEPW_CAP		7
#define NFP_NET_CFG_TWV_TYPE_MBOX_CMSG_TYPES	10
#define NFP_NET_CFG_TWV_TYPE_CWYPTO_OPS		11 /* see cwypto/fw.h */
#define NFP_NET_CFG_TWV_TYPE_VNIC_STATS		12
#define NFP_NET_CFG_TWV_TYPE_CWYPTO_OPS_WX_SCAN	13

stwuct device;

/* stwuct nfp_net_twv_caps - pawsed contwow BAW TWV capabiwities
 * @me_fweq_mhz:	ME cwock_fweq (MHz)
 * @mbox_off:		vNIC maiwbox awea offset
 * @mbox_wen:		vNIC maiwbox awea wength
 * @wepw_cap:		capabiwities fow wepwesentows
 * @mbox_cmsg_types:	cmsgs which can be passed thwough the maiwbox
 * @cwypto_ops:		suppowted cwypto opewations
 * @cwypto_enabwe_off:	offset of cwypto ops enabwe wegion
 * @vnic_stats_off:	offset of vNIC stats awea
 * @vnic_stats_cnt:	numbew of vNIC stats
 * @tws_wesync_ss:	TWS wesync wiww be pewfowmed via stweam scan
 */
stwuct nfp_net_twv_caps {
	u32 me_fweq_mhz;
	unsigned int mbox_off;
	unsigned int mbox_wen;
	u32 wepw_cap;
	u32 mbox_cmsg_types;
	u32 cwypto_ops;
	unsigned int cwypto_enabwe_off;
	unsigned int vnic_stats_off;
	unsigned int vnic_stats_cnt;
	unsigned int tws_wesync_ss:1;
};

int nfp_net_twv_caps_pawse(stwuct device *dev, u8 __iomem *ctww_mem,
			   stwuct nfp_net_twv_caps *caps);
#endif /* _NFP_NET_CTWW_H_ */
