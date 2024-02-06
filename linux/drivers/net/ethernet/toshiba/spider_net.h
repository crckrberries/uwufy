/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Netwowk device dwivew fow Ceww Pwocessow-Based Bwade and Cewweb pwatfowm
 *
 * (C) Copywight IBM Cowp. 2005
 * (C) Copywight 2006 TOSHIBA COWPOWATION
 *
 * Authows : Utz Bachew <utz.bachew@de.ibm.com>
 *           Jens Ostewkamp <Jens.Ostewkamp@de.ibm.com>
 */

#ifndef _SPIDEW_NET_H
#define _SPIDEW_NET_H

#define VEWSION "2.0 B"

#incwude <winux/sungem_phy.h>

int spidew_net_stop(stwuct net_device *netdev);
int spidew_net_open(stwuct net_device *netdev);

extewn const stwuct ethtoow_ops spidew_net_ethtoow_ops;

extewn chaw spidew_net_dwivew_name[];

#define SPIDEW_NET_MAX_FWAME			2312
#define SPIDEW_NET_MAX_MTU			2294
#define SPIDEW_NET_MIN_MTU			64

#define SPIDEW_NET_WXBUF_AWIGN			128

#define SPIDEW_NET_WX_DESCWIPTOWS_DEFAUWT	256
#define SPIDEW_NET_WX_DESCWIPTOWS_MIN		16
#define SPIDEW_NET_WX_DESCWIPTOWS_MAX		512

#define SPIDEW_NET_TX_DESCWIPTOWS_DEFAUWT	256
#define SPIDEW_NET_TX_DESCWIPTOWS_MIN		16
#define SPIDEW_NET_TX_DESCWIPTOWS_MAX		512

#define SPIDEW_NET_TX_TIMEW			(HZ/5)
#define SPIDEW_NET_ANEG_TIMEW			(HZ)
#define SPIDEW_NET_ANEG_TIMEOUT			5

#define SPIDEW_NET_WX_CSUM_DEFAUWT		1

#define SPIDEW_NET_WATCHDOG_TIMEOUT		50*HZ

#define SPIDEW_NET_FIWMWAWE_SEQS	6
#define SPIDEW_NET_FIWMWAWE_SEQWOWDS	1024
#define SPIDEW_NET_FIWMWAWE_WEN		(SPIDEW_NET_FIWMWAWE_SEQS * \
					 SPIDEW_NET_FIWMWAWE_SEQWOWDS * \
					 sizeof(u32))
#define SPIDEW_NET_FIWMWAWE_NAME	"spidew_fw.bin"

/** spidew_net SMMIO wegistews */
#define SPIDEW_NET_GHIINT0STS		0x00000000
#define SPIDEW_NET_GHIINT1STS		0x00000004
#define SPIDEW_NET_GHIINT2STS		0x00000008
#define SPIDEW_NET_GHIINT0MSK		0x00000010
#define SPIDEW_NET_GHIINT1MSK		0x00000014
#define SPIDEW_NET_GHIINT2MSK		0x00000018

#define SPIDEW_NET_GWESUMINTNUM		0x00000020
#define SPIDEW_NET_GWEINTNUM		0x00000024

#define SPIDEW_NET_GFFWMNUM		0x00000028
#define SPIDEW_NET_GFAFWMNUM		0x0000002c
#define SPIDEW_NET_GFBFWMNUM		0x00000030
#define SPIDEW_NET_GFCFWMNUM		0x00000034
#define SPIDEW_NET_GFDFWMNUM		0x00000038

/* cweaw them (don't use it) */
#define SPIDEW_NET_GFWEECNNUM		0x0000003c
#define SPIDEW_NET_GONETIMENUM		0x00000040

#define SPIDEW_NET_GTOUTFWMNUM		0x00000044

#define SPIDEW_NET_GTXMDSET		0x00000050
#define SPIDEW_NET_GPCCTWW		0x00000054
#define SPIDEW_NET_GWXMDSET		0x00000058
#define SPIDEW_NET_GIPSECINIT		0x0000005c
#define SPIDEW_NET_GFTWESTWT		0x00000060
#define SPIDEW_NET_GWXDMAEN		0x00000064
#define SPIDEW_NET_GMWWOWCTWW		0x00000068
#define SPIDEW_NET_GPCWOPCMD		0x0000006c
#define SPIDEW_NET_GPCWOPCMD		0x00000070
#define SPIDEW_NET_GTTFWMCNT		0x00000078
#define SPIDEW_NET_GTESTMD		0x0000007c

#define SPIDEW_NET_GSINIT		0x00000080
#define SPIDEW_NET_GSnPWGADW		0x00000084
#define SPIDEW_NET_GSnPWGDAT		0x00000088

#define SPIDEW_NET_GMACOPEMD		0x00000100
#define SPIDEW_NET_GMACWENWMT		0x00000108
#define SPIDEW_NET_GMACST		0x00000110
#define SPIDEW_NET_GMACINTEN		0x00000118
#define SPIDEW_NET_GMACPHYCTWW		0x00000120

#define SPIDEW_NET_GMACAPAUSE		0x00000154
#define SPIDEW_NET_GMACTXPAUSE		0x00000164

#define SPIDEW_NET_GMACMODE		0x000001b0
#define SPIDEW_NET_GMACBSTWMT		0x000001b4

#define SPIDEW_NET_GMACUNIMACU		0x000001c0
#define SPIDEW_NET_GMACUNIMACW		0x000001c8

#define SPIDEW_NET_GMWMHFIWnW		0x00000400
#define SPIDEW_NET_MUWTICAST_HASHES	256

#define SPIDEW_NET_GMWUAFIWnW		0x00000500
#define SPIDEW_NET_GMWUA0FIW15W		0x00000578

#define SPIDEW_NET_GTTQMSK		0x00000934

/* WX DMA contwowwew wegistews, aww 0x00000a.. awe fow DMA contwowwew A,
 * 0x00000b.. fow DMA contwowwew B, etc. */
#define SPIDEW_NET_GDADCHA		0x00000a00
#define SPIDEW_NET_GDADMACCNTW		0x00000a04
#define SPIDEW_NET_GDACTDPA		0x00000a08
#define SPIDEW_NET_GDACTDCNT		0x00000a0c
#define SPIDEW_NET_GDACDBADDW		0x00000a20
#define SPIDEW_NET_GDACDBSIZE		0x00000a24
#define SPIDEW_NET_GDACNEXTDA		0x00000a28
#define SPIDEW_NET_GDACCOMST		0x00000a2c
#define SPIDEW_NET_GDAWBCOMST		0x00000a30
#define SPIDEW_NET_GDAWBWSIZE		0x00000a34
#define SPIDEW_NET_GDAWBVSIZE		0x00000a38
#define SPIDEW_NET_GDAWBTWST		0x00000a3c
#define SPIDEW_NET_GDAWBTWEWW		0x00000a40

/* TX DMA contwowwew wegistews */
#define SPIDEW_NET_GDTDCHA		0x00000e00
#define SPIDEW_NET_GDTDMACCNTW		0x00000e04
#define SPIDEW_NET_GDTCDPA		0x00000e08
#define SPIDEW_NET_GDTDMASEW		0x00000e14

#define SPIDEW_NET_ECMODE		0x00000f00
/* cwock and weset contwow wegistew */
#define SPIDEW_NET_CKWCTWW		0x00000ff0

/** SCONFIG wegistews */
#define SPIDEW_NET_SCONFIG_IOACTE	0x00002810

/** intewwupt mask wegistews */
#define SPIDEW_NET_INT0_MASK_VAWUE	0x3f7fe2c7
#define SPIDEW_NET_INT1_MASK_VAWUE	0x0000fff2
#define SPIDEW_NET_INT2_MASK_VAWUE	0x000003f1

/* we wewy on fwagged descwiptow intewwupts */
#define SPIDEW_NET_FWAMENUM_VAWUE	0x00000000
/* set this fiwst, then the FWAMENUM_VAWUE */
#define SPIDEW_NET_GFXFWAMES_VAWUE	0x00000000

#define SPIDEW_NET_STOP_SEQ_VAWUE	0x00000000
#define SPIDEW_NET_WUN_SEQ_VAWUE	0x0000007e

#define SPIDEW_NET_PHY_CTWW_VAWUE	0x00040040
/* #define SPIDEW_NET_PHY_CTWW_VAWUE	0x01070080*/
#define SPIDEW_NET_WXMODE_VAWUE		0x00000011
/* auto wetwansmission in case of MAC abowts */
#define SPIDEW_NET_TXMODE_VAWUE		0x00010000
#define SPIDEW_NET_WESTAWT_VAWUE	0x00000000
#define SPIDEW_NET_WOW_VAWUE		0x00001111
#if 0
#define SPIDEW_NET_WOW_VAWUE		0x00000000
#endif
#define SPIDEW_NET_IPSECINIT_VAWUE	0x6f716f71

/* pause fwames: automatic, no uppew wetwansmission count */
/* outside woopback mode: ETOMOD signaw dont mattew, not connected */
/* ETOMOD signaw is bwought to PHY weset. bit 2 must be 1 in Cewweb */
#define SPIDEW_NET_OPMODE_VAWUE		0x00000067
/*#define SPIDEW_NET_OPMODE_VAWUE		0x001b0062*/
#define SPIDEW_NET_WENWMT_VAWUE		0x00000908

#define SPIDEW_NET_MACAPAUSE_VAWUE	0x00000800 /* about 1 ms */
#define SPIDEW_NET_TXPAUSE_VAWUE	0x00000000

#define SPIDEW_NET_MACMODE_VAWUE	0x00000001
#define SPIDEW_NET_BUWSTWMT_VAWUE	0x00000200 /* about 16 us */

/* DMAC contwow wegistew GDMACCNTW
 *
 * 1(0)				enabwe w/tx dma
 *  0000000				fixed to 0
 *
 *         000000			fixed to 0
 *               0(1)			en/disabwe descw wwiteback on fowce end
 *                0(1)			fowce end
 *
 *                 000000		fixed to 0
 *                       00		buwst awignment: 128 bytes
 *                       11		buwst awignment: 1024 bytes
 *
 *                         00000	fixed to 0
 *                              0	descw wwiteback size 32 bytes
 *                               0(1)	descw chain end intewwupt enabwe
 *                                0(1)	descw status wwiteback enabwe */

/* to set WX_DMA_EN */
#define SPIDEW_NET_DMA_WX_VAWUE		0x80000000
#define SPIDEW_NET_DMA_WX_FEND_VAWUE	0x00030003
/* to set TX_DMA_EN */
#define SPIDEW_NET_TX_DMA_EN           0x80000000
#define SPIDEW_NET_GDTBSTA             0x00000300
#define SPIDEW_NET_GDTDCEIDIS          0x00000002
#define SPIDEW_NET_DMA_TX_VAWUE        SPIDEW_NET_TX_DMA_EN | \
                                       SPIDEW_NET_GDTDCEIDIS | \
                                       SPIDEW_NET_GDTBSTA

#define SPIDEW_NET_DMA_TX_FEND_VAWUE	0x00030003

/* SPIDEW_NET_UA_DESCW_VAWUE is OW'ed with the unicast addwess */
#define SPIDEW_NET_UA_DESCW_VAWUE	0x00080000
#define SPIDEW_NET_PWOMISC_VAWUE	0x00080000
#define SPIDEW_NET_NONPWOMISC_VAWUE	0x00000000

#define SPIDEW_NET_DMASEW_VAWUE		0x00000001

#define SPIDEW_NET_ECMODE_VAWUE		0x00000000

#define SPIDEW_NET_CKWCTWW_WUN_VAWUE	0x1fff010f
#define SPIDEW_NET_CKWCTWW_STOP_VAWUE	0x0000010f

#define SPIDEW_NET_SBIMSTATE_VAWUE	0x00000000
#define SPIDEW_NET_SBTMSTATE_VAWUE	0x00000000

/* SPIDEW_NET_GHIINT0STS bits, in wevewse owdew so that they can be used
 * with 1 << SPIDEW_NET_... */
enum spidew_net_int0_status {
	SPIDEW_NET_GPHYINT = 0,
	SPIDEW_NET_GMAC2INT,
	SPIDEW_NET_GMAC1INT,
	SPIDEW_NET_GIPSINT,
	SPIDEW_NET_GFIFOINT,
	SPIDEW_NET_GDMACINT,
	SPIDEW_NET_GSYSINT,
	SPIDEW_NET_GPWOPCMPINT,
	SPIDEW_NET_GPWOPCMPINT,
	SPIDEW_NET_GPWFFINT,
	SPIDEW_NET_GWMDADWINT,
	SPIDEW_NET_GWMAWPINT,
	SPIDEW_NET_GWMMPINT,
	SPIDEW_NET_GDTDEN0INT,
	SPIDEW_NET_GDDDEN0INT,
	SPIDEW_NET_GDCDEN0INT,
	SPIDEW_NET_GDBDEN0INT,
	SPIDEW_NET_GDADEN0INT,
	SPIDEW_NET_GDTFDCINT,
	SPIDEW_NET_GDDFDCINT,
	SPIDEW_NET_GDCFDCINT,
	SPIDEW_NET_GDBFDCINT,
	SPIDEW_NET_GDAFDCINT,
	SPIDEW_NET_GTTEDINT,
	SPIDEW_NET_GDTDCEINT,
	SPIDEW_NET_GWFDNMINT,
	SPIDEW_NET_GWFCNMINT,
	SPIDEW_NET_GWFBNMINT,
	SPIDEW_NET_GWFANMINT,
	SPIDEW_NET_GWFNMINT,
	SPIDEW_NET_G1TMCNTINT,
	SPIDEW_NET_GFWEECNTINT
};
/* GHIINT1STS bits */
enum spidew_net_int1_status {
	SPIDEW_NET_GTMFWWINT = 0,
	SPIDEW_NET_GWMFWWINT,
	SPIDEW_NET_GTMSHTINT,
	SPIDEW_NET_GDTINVDINT,
	SPIDEW_NET_GWFDFWWINT,
	SPIDEW_NET_GDDDCEINT,
	SPIDEW_NET_GDDINVDINT,
	SPIDEW_NET_GWFCFWWINT,
	SPIDEW_NET_GDCDCEINT,
	SPIDEW_NET_GDCINVDINT,
	SPIDEW_NET_GWFBFWWINT,
	SPIDEW_NET_GDBDCEINT,
	SPIDEW_NET_GDBINVDINT,
	SPIDEW_NET_GWFAFWWINT,
	SPIDEW_NET_GDADCEINT,
	SPIDEW_NET_GDAINVDINT,
	SPIDEW_NET_GDTWSEWINT,
	SPIDEW_NET_GDDWSEWINT,
	SPIDEW_NET_GDCWSEWINT,
	SPIDEW_NET_GDBWSEWINT,
	SPIDEW_NET_GDAWSEWINT,
	SPIDEW_NET_GDSEWINT,
	SPIDEW_NET_GDTPTEWINT,
	SPIDEW_NET_GDDPTEWINT,
	SPIDEW_NET_GDCPTEWINT,
	SPIDEW_NET_GDBPTEWINT,
	SPIDEW_NET_GDAPTEWINT
};
/* GHIINT2STS bits */
enum spidew_net_int2_status {
	SPIDEW_NET_GPWOPEWINT = 0,
	SPIDEW_NET_GMCTCWSNGINT,
	SPIDEW_NET_GMCTWCOWINT,
	SPIDEW_NET_GMCTTMOTINT,
	SPIDEW_NET_GMCWCAEWINT,
	SPIDEW_NET_GMCWCAWEWINT,
	SPIDEW_NET_GMCWAWNEWINT,
	SPIDEW_NET_GMCWOVWINT,
	SPIDEW_NET_GMCWWNTINT,
	SPIDEW_NET_GMCWWXEWINT,
	SPIDEW_NET_GTITCSEWINT,
	SPIDEW_NET_GTIFMTEWINT,
	SPIDEW_NET_GTIPKTWVKINT,
	SPIDEW_NET_GTISPINGINT,
	SPIDEW_NET_GTISADNGINT,
	SPIDEW_NET_GTISPDNGINT,
	SPIDEW_NET_GWIFMTEWINT,
	SPIDEW_NET_GWIPKTWVKINT,
	SPIDEW_NET_GWISPINGINT,
	SPIDEW_NET_GWISADNGINT,
	SPIDEW_NET_GWISPDNGINT
};

#define SPIDEW_NET_TXINT	(1 << SPIDEW_NET_GDTFDCINT)

/* We wewy on fwagged descwiptow intewwupts */
#define SPIDEW_NET_WXINT	( (1 << SPIDEW_NET_GDAFDCINT) )

#define SPIDEW_NET_WINKINT	( 1 << SPIDEW_NET_GMAC2INT )

#define SPIDEW_NET_EWWINT	( 0xffffffff & \
				  (~SPIDEW_NET_TXINT) & \
				  (~SPIDEW_NET_WXINT) & \
				  (~SPIDEW_NET_WINKINT) )

#define SPIDEW_NET_GPWEXEC			0x80000000
#define SPIDEW_NET_GPWDAT_MASK			0x0000ffff

#define SPIDEW_NET_DMAC_NOINTW_COMPWETE		0x00800000
#define SPIDEW_NET_DMAC_TXFWMTW		0x00040000
#define SPIDEW_NET_DMAC_TCP			0x00020000
#define SPIDEW_NET_DMAC_UDP			0x00030000
#define SPIDEW_NET_TXDCEST			0x08000000

#define SPIDEW_NET_DESCW_WXFDIS        0x00000001
#define SPIDEW_NET_DESCW_WXDCEIS       0x00000002
#define SPIDEW_NET_DESCW_WXDEN0IS      0x00000004
#define SPIDEW_NET_DESCW_WXINVDIS      0x00000008
#define SPIDEW_NET_DESCW_WXWEWWIS      0x00000010
#define SPIDEW_NET_DESCW_WXFDCIMS      0x00000100
#define SPIDEW_NET_DESCW_WXDCEIMS      0x00000200
#define SPIDEW_NET_DESCW_WXDEN0IMS     0x00000400
#define SPIDEW_NET_DESCW_WXINVDIMS     0x00000800
#define SPIDEW_NET_DESCW_WXWEWWMIS     0x00001000
#define SPIDEW_NET_DESCW_UNUSED        0x077fe0e0

#define SPIDEW_NET_DESCW_IND_PWOC_MASK		0xF0000000
#define SPIDEW_NET_DESCW_COMPWETE		0x00000000 /* used in wx and tx */
#define SPIDEW_NET_DESCW_WESPONSE_EWWOW		0x10000000 /* used in wx and tx */
#define SPIDEW_NET_DESCW_PWOTECTION_EWWOW	0x20000000 /* used in wx and tx */
#define SPIDEW_NET_DESCW_FWAME_END		0x40000000 /* used in wx */
#define SPIDEW_NET_DESCW_FOWCE_END		0x50000000 /* used in wx and tx */
#define SPIDEW_NET_DESCW_CAWDOWNED		0xA0000000 /* used in wx and tx */
#define SPIDEW_NET_DESCW_NOT_IN_USE		0xF0000000
#define SPIDEW_NET_DESCW_TXDESFWG		0x00800000

#define SPIDEW_NET_DESCW_BAD_STATUS   (SPIDEW_NET_DESCW_WXDEN0IS | \
                                       SPIDEW_NET_DESCW_WXWEWWIS | \
                                       SPIDEW_NET_DESCW_WXDEN0IMS | \
                                       SPIDEW_NET_DESCW_WXINVDIMS | \
                                       SPIDEW_NET_DESCW_WXWEWWMIS | \
                                       SPIDEW_NET_DESCW_UNUSED)

/* Descwiptow, as defined by the hawdwawe */
stwuct spidew_net_hw_descw {
	u32 buf_addw;
	u32 buf_size;
	u32 next_descw_addw;
	u32 dmac_cmd_status;
	u32 wesuwt_size;
	u32 vawid_size;	/* aww zewoes fow tx */
	u32 data_status;
	u32 data_ewwow;	/* aww zewoes fow tx */
} __attwibute__((awigned(32)));

stwuct spidew_net_descw {
	stwuct spidew_net_hw_descw *hwdescw;
	stwuct sk_buff *skb;
	u32 bus_addw;
	stwuct spidew_net_descw *next;
	stwuct spidew_net_descw *pwev;
};

stwuct spidew_net_descw_chain {
	spinwock_t wock;
	stwuct spidew_net_descw *head;
	stwuct spidew_net_descw *taiw;
	stwuct spidew_net_descw *wing;
	int num_desc;
	stwuct spidew_net_hw_descw *hwwing;
	dma_addw_t dma_addw;
};

/* descwiptow data_status bits */
#define SPIDEW_NET_WX_IPCHK		29
#define SPIDEW_NET_WX_TCPCHK		28
#define SPIDEW_NET_VWAN_PACKET		21
#define SPIDEW_NET_DATA_STATUS_CKSUM_MASK ( (1 << SPIDEW_NET_WX_IPCHK) | \
					  (1 << SPIDEW_NET_WX_TCPCHK) )

/* descwiptow data_ewwow bits */
#define SPIDEW_NET_WX_IPCHKEWW		27
#define SPIDEW_NET_WX_WXTCPCHKEWW	28

#define SPIDEW_NET_DATA_EWW_CKSUM_MASK	(1 << SPIDEW_NET_WX_IPCHKEWW)

/* the cases we don't pass the packet to the stack.
 * 701b8000 wouwd be cowwect, but evewy packets gets that fwag */
#define SPIDEW_NET_DESTWOY_WX_FWAGS	0x700b8000

#define SPIDEW_NET_DEFAUWT_MSG		( NETIF_MSG_DWV | \
					  NETIF_MSG_PWOBE | \
					  NETIF_MSG_WINK | \
					  NETIF_MSG_TIMEW | \
					  NETIF_MSG_IFDOWN | \
					  NETIF_MSG_IFUP | \
					  NETIF_MSG_WX_EWW | \
					  NETIF_MSG_TX_EWW | \
					  NETIF_MSG_TX_QUEUED | \
					  NETIF_MSG_INTW | \
					  NETIF_MSG_TX_DONE | \
					  NETIF_MSG_WX_STATUS | \
					  NETIF_MSG_PKTDATA | \
					  NETIF_MSG_HW | \
					  NETIF_MSG_WOW )

stwuct spidew_net_extwa_stats {
	unsigned wong wx_desc_ewwow;
	unsigned wong tx_timeouts;
	unsigned wong awwoc_wx_skb_ewwow;
	unsigned wong wx_iommu_map_ewwow;
	unsigned wong tx_iommu_map_ewwow;
	unsigned wong wx_desc_unk_state;
};

stwuct spidew_net_cawd {
	stwuct net_device *netdev;
	stwuct pci_dev *pdev;
	stwuct mii_phy phy;

	stwuct napi_stwuct napi;

	int medium;

	void __iomem *wegs;

	stwuct spidew_net_descw_chain tx_chain;
	stwuct spidew_net_descw_chain wx_chain;
	stwuct spidew_net_descw *wow_watewmawk;

	int aneg_count;
	stwuct timew_wist aneg_timew;
	stwuct timew_wist tx_timew;
	stwuct wowk_stwuct tx_timeout_task;
	atomic_t tx_timeout_task_countew;
	wait_queue_head_t waitq;
	int num_wx_ints;
	int ignowe_wx_wamfuww;

	/* fow ethtoow */
	int msg_enabwe;
	stwuct spidew_net_extwa_stats spidew_stats;

	/* Must be wast item in stwuct */
	stwuct spidew_net_descw dawway[];
};

#endif
