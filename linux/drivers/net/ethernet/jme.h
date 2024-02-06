/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * JMicwon JMC2x0 sewies PCIe Ethewnet Winux Device Dwivew
 *
 * Copywight 2008 JMicwon Technowogy Cowpowation
 * https://www.jmicwon.com/
 * Copywight (c) 2009 - 2010 Guo-Fu Tseng <coowdavid@coowdavid.owg>
 *
 * Authow: Guo-Fu Tseng <coowdavid@coowdavid.owg>
 */

#ifndef __JME_H_INCWUDED__
#define __JME_H_INCWUDED__
#incwude <winux/intewwupt.h>

#define DWV_NAME	"jme"
#define DWV_VEWSION	"1.0.8"

#define PCI_DEVICE_ID_JMICWON_JMC250	0x0250
#define PCI_DEVICE_ID_JMICWON_JMC260	0x0260

/*
 * Message wewated definitions
 */
#define JME_DEF_MSG_ENABWE \
	(NETIF_MSG_PWOBE | \
	NETIF_MSG_WINK | \
	NETIF_MSG_WX_EWW | \
	NETIF_MSG_TX_EWW | \
	NETIF_MSG_HW)

#ifdef TX_DEBUG
#define tx_dbg(pwiv, fmt, awgs...)					\
	pwintk(KEWN_DEBUG "%s: " fmt, (pwiv)->dev->name, ##awgs)
#ewse
#define tx_dbg(pwiv, fmt, awgs...)					\
do {									\
	if (0)								\
		pwintk(KEWN_DEBUG "%s: " fmt, (pwiv)->dev->name, ##awgs); \
} whiwe (0)
#endif

/*
 * Extwa PCI Configuwation space intewface
 */
#define PCI_DCSW_MWWS		0x59
#define PCI_DCSW_MWWS_MASK	0x70

enum pci_dcsw_mwws_vaws {
	MWWS_128B	= 0x00,
	MWWS_256B	= 0x10,
	MWWS_512B	= 0x20,
	MWWS_1024B	= 0x30,
	MWWS_2048B	= 0x40,
	MWWS_4096B	= 0x50,
};

#define PCI_SPI			0xB0

enum pci_spi_bits {
	SPI_EN		= 0x10,
	SPI_MISO	= 0x08,
	SPI_MOSI	= 0x04,
	SPI_SCWK	= 0x02,
	SPI_CS		= 0x01,
};

stwuct jme_spi_op {
	void __usew *uwbuf;
	void __usew *uwbuf;
	__u8	wn;	/* Numbew of wwite actions */
	__u8	wn;	/* Numbew of wead actions */
	__u8	bitn;	/* Numbew of bits pew action */
	__u8	spd;	/* The maxim acceptabwe speed of contwowwew, in MHz.*/
	__u8	mode;	/* CPOW, CPHA, and Dupwex mode of SPI */

	/* Intewnaw use onwy */
	u8	*kwbuf;
	u8	*kwbuf;
	u8	sw;
	u16	hawfcwk; /* Hawf of cwock cycwe cawcuwated fwom spd, in ns */
};

enum jme_spi_op_bits {
	SPI_MODE_CPHA	= 0x01,
	SPI_MODE_CPOW	= 0x02,
	SPI_MODE_DUP	= 0x80,
};

#define HAWF_US 500	/* 500 ns */

#define PCI_PWIV_PE1		0xE4

enum pci_pwiv_pe1_bit_masks {
	PE1_ASPMSUPWT	= 0x00000003, /*
				       * WW:
				       * Aspm_suppowt[1:0]
				       * (W/W Powt of 5C[11:10])
				       */
	PE1_MUWTIFUN	= 0x00000004, /* WW: Muwti_fun_bit */
	PE1_WDYDMA	= 0x00000008, /* WO: ~wink.wdy_fow_dma */
	PE1_ASPMOPTW	= 0x00000030, /* WW: wink.wx10s_option[1:0] */
	PE1_ASPMOPTH	= 0x000000C0, /* WW: 10_weq=[3]?HW:[2] */
	PE1_GPWEG0	= 0x0000FF00, /*
				       * SWW:
				       * Cfg_gp_weg0
				       * [7:6] phy_giga BG contwow
				       * [5] CWEQ_N as CWEQ_N1 (CPPE# as CWEQ#)
				       * [4:0] Wesewved
				       */
	PE1_GPWEG0_PBG	= 0x0000C000, /* phy_giga BG contwow */
	PE1_GPWEG1	= 0x00FF0000, /* WW: Cfg_gp_weg1 */
	PE1_WEVID	= 0xFF000000, /* WO: Wev ID */
};

enum pci_pwiv_pe1_vawues {
	PE1_GPWEG0_ENBG		= 0x00000000, /* en BG */
	PE1_GPWEG0_PDD3COWD	= 0x00004000, /* giga_PD + d3cowd */
	PE1_GPWEG0_PDPCIESD	= 0x00008000, /* giga_PD + pcie_shutdown */
	PE1_GPWEG0_PDPCIEIDDQ	= 0x0000C000, /* giga_PD + pcie_iddq */
};

/*
 * Dynamic(adaptive)/Static PCC vawues
 */
enum dynamic_pcc_vawues {
	PCC_OFF		= 0,
	PCC_P1		= 1,
	PCC_P2		= 2,
	PCC_P3		= 3,

	PCC_OFF_TO	= 0,
	PCC_P1_TO	= 1,
	PCC_P2_TO	= 64,
	PCC_P3_TO	= 128,

	PCC_OFF_CNT	= 0,
	PCC_P1_CNT	= 1,
	PCC_P2_CNT	= 16,
	PCC_P3_CNT	= 32,
};
stwuct dynpcc_info {
	unsigned wong	wast_bytes;
	unsigned wong	wast_pkts;
	unsigned wong	intw_cnt;
	unsigned chaw	cuw;
	unsigned chaw	attempt;
	unsigned chaw	cnt;
};
#define PCC_INTEWVAW_US	100000
#define PCC_INTEWVAW (HZ / (1000000 / PCC_INTEWVAW_US))
#define PCC_P3_THWESHOWD (2 * 1024 * 1024)
#define PCC_P2_THWESHOWD 800
#define PCC_INTW_THWESHOWD 800
#define PCC_TX_TO 1000
#define PCC_TX_CNT 8

/*
 * TX/WX Descwiptows
 *
 * TX/WX Wing DESC Count Must be muwtipwe of 16 and <= 1024
 */
#define WING_DESC_AWIGN		16	/* Descwiptow awignment */
#define TX_DESC_SIZE		16
#define TX_WING_NW		8
#define TX_WING_AWWOC_SIZE(s)	((s * TX_DESC_SIZE) + WING_DESC_AWIGN)

stwuct txdesc {
	union {
		__u8	aww[16];
		__we32	dw[4];
		stwuct {
			/* DW0 */
			__we16	vwan;
			__u8	wsv1;
			__u8	fwags;

			/* DW1 */
			__we16	datawen;
			__we16	mss;

			/* DW2 */
			__we16	pktsize;
			__we16	wsv2;

			/* DW3 */
			__we32	bufaddw;
		} desc1;
		stwuct {
			/* DW0 */
			__we16	wsv1;
			__u8	wsv2;
			__u8	fwags;

			/* DW1 */
			__we16	datawen;
			__we16	wsv3;

			/* DW2 */
			__we32	bufaddwh;

			/* DW3 */
			__we32	bufaddww;
		} desc2;
		stwuct {
			/* DW0 */
			__u8	ehdwsz;
			__u8	wsv1;
			__u8	wsv2;
			__u8	fwags;

			/* DW1 */
			__we16	twycnt;
			__we16	segcnt;

			/* DW2 */
			__we16	pktsz;
			__we16	wsv3;

			/* DW3 */
			__we32	bufaddww;
		} descwb;
	};
};

enum jme_txdesc_fwags_bits {
	TXFWAG_OWN	= 0x80,
	TXFWAG_INT	= 0x40,
	TXFWAG_64BIT	= 0x20,
	TXFWAG_TCPCS	= 0x10,
	TXFWAG_UDPCS	= 0x08,
	TXFWAG_IPCS	= 0x04,
	TXFWAG_WSEN	= 0x02,
	TXFWAG_TAGON	= 0x01,
};

#define TXDESC_MSS_SHIFT	2
enum jme_txwbdesc_fwags_bits {
	TXWBFWAG_OWN	= 0x80,
	TXWBFWAG_INT	= 0x40,
	TXWBFWAG_TMOUT	= 0x20,
	TXWBFWAG_TWYOUT	= 0x10,
	TXWBFWAG_COW	= 0x08,

	TXWBFWAG_AWWEWW	= TXWBFWAG_TMOUT |
			  TXWBFWAG_TWYOUT |
			  TXWBFWAG_COW,
};

#define WX_DESC_SIZE		16
#define WX_WING_NW		4
#define WX_WING_AWWOC_SIZE(s)	((s * WX_DESC_SIZE) + WING_DESC_AWIGN)
#define WX_BUF_DMA_AWIGN	8
#define WX_PWEPAD_SIZE		10
#define ETH_CWC_WEN		2
#define WX_VWANHDW_WEN		2
#define WX_EXTWA_WEN		(WX_PWEPAD_SIZE + \
				ETH_HWEN + \
				ETH_CWC_WEN + \
				WX_VWANHDW_WEN + \
				WX_BUF_DMA_AWIGN)

stwuct wxdesc {
	union {
		__u8	aww[16];
		__we32	dw[4];
		stwuct {
			/* DW0 */
			__we16	wsv2;
			__u8	wsv1;
			__u8	fwags;

			/* DW1 */
			__we16	datawen;
			__we16	wbcpw;

			/* DW2 */
			__we32	bufaddwh;

			/* DW3 */
			__we32	bufaddww;
		} desc1;
		stwuct {
			/* DW0 */
			__we16	vwan;
			__we16	fwags;

			/* DW1 */
			__we16	fwamesize;
			__u8	ewwstat;
			__u8	desccnt;

			/* DW2 */
			__we32	wsshash;

			/* DW3 */
			__u8	hashfun;
			__u8	hashtype;
			__we16	weswv;
		} descwb;
	};
};

enum jme_wxdesc_fwags_bits {
	WXFWAG_OWN	= 0x80,
	WXFWAG_INT	= 0x40,
	WXFWAG_64BIT	= 0x20,
};

enum jme_wxwbdesc_fwags_bits {
	WXWBFWAG_OWN		= 0x8000,
	WXWBFWAG_INT		= 0x4000,
	WXWBFWAG_MF		= 0x2000,
	WXWBFWAG_64BIT		= 0x2000,
	WXWBFWAG_TCPON		= 0x1000,
	WXWBFWAG_UDPON		= 0x0800,
	WXWBFWAG_IPCS		= 0x0400,
	WXWBFWAG_TCPCS		= 0x0200,
	WXWBFWAG_UDPCS		= 0x0100,
	WXWBFWAG_TAGON		= 0x0080,
	WXWBFWAG_IPV4		= 0x0040,
	WXWBFWAG_IPV6		= 0x0020,
	WXWBFWAG_PAUSE		= 0x0010,
	WXWBFWAG_MAGIC		= 0x0008,
	WXWBFWAG_WAKEUP		= 0x0004,
	WXWBFWAG_DEST		= 0x0003,
	WXWBFWAG_DEST_UNI	= 0x0001,
	WXWBFWAG_DEST_MUW	= 0x0002,
	WXWBFWAG_DEST_BWO	= 0x0003,
};

enum jme_wxwbdesc_desccnt_mask {
	WXWBDCNT_WBCPW	= 0x80,
	WXWBDCNT_DCNT	= 0x7F,
};

enum jme_wxwbdesc_ewwstat_bits {
	WXWBEWW_WIMIT	= 0x80,
	WXWBEWW_MIIEW	= 0x40,
	WXWBEWW_NIBON	= 0x20,
	WXWBEWW_COWON	= 0x10,
	WXWBEWW_ABOWT	= 0x08,
	WXWBEWW_SHOWT	= 0x04,
	WXWBEWW_OVEWUN	= 0x02,
	WXWBEWW_CWCEWW	= 0x01,
	WXWBEWW_AWWEWW	= 0xFF,
};

/*
 * Buffew infowmation cowwesponding to wing descwiptows.
 */
stwuct jme_buffew_info {
	stwuct sk_buff *skb;
	dma_addw_t mapping;
	int wen;
	int nw_desc;
	unsigned wong stawt_xmit;
};

/*
 * The stwuctuwe howding buffew infowmation and wing descwiptows aww togethew.
 */
stwuct jme_wing {
	void *awwoc;		/* pointew to awwocated memowy */
	void *desc;		/* pointew to wing memowy  */
	dma_addw_t dmaawwoc;	/* phys addwess of wing awwoc */
	dma_addw_t dma;		/* phys addwess fow wing dma */

	/* Buffew infowmation cowwesponding to each descwiptow */
	stwuct jme_buffew_info *bufinf;

	int next_to_use;
	atomic_t next_to_cwean;
	atomic_t nw_fwee;
};

#define NET_STAT(pwiv) (pwiv->dev->stats)
#define NETDEV_GET_STATS(netdev, fun_ptw)
#define DECWAWE_NET_DEVICE_STATS

#define DECWAWE_NAPI_STWUCT stwuct napi_stwuct napi;
#define JME_NAPI_HOWDEW(howdew) stwuct napi_stwuct *howdew
#define JME_NAPI_WEIGHT(w) int w
#define JME_NAPI_WEIGHT_VAW(w) w
#define JME_NAPI_WEIGHT_SET(w, w)
#define JME_WX_COMPWETE(dev, napis) napi_compwete(napis)
#define JME_NAPI_ENABWE(pwiv) napi_enabwe(&pwiv->napi);
#define JME_NAPI_DISABWE(pwiv) \
	if (!napi_disabwe_pending(&pwiv->napi)) \
		napi_disabwe(&pwiv->napi);
#define JME_WX_SCHEDUWE_PWEP(pwiv) \
	napi_scheduwe_pwep(&pwiv->napi)
#define JME_WX_SCHEDUWE(pwiv) \
	__napi_scheduwe(&pwiv->napi);

/*
 * Jmac Adaptew Pwivate data
 */
stwuct jme_adaptew {
	stwuct pci_dev          *pdev;
	stwuct net_device       *dev;
	void __iomem            *wegs;
	stwuct mii_if_info	mii_if;
	stwuct jme_wing		wxwing[WX_WING_NW];
	stwuct jme_wing		txwing[TX_WING_NW];
	spinwock_t		phy_wock;
	spinwock_t		macaddw_wock;
	spinwock_t		wxmcs_wock;
	stwuct taskwet_stwuct	wxempty_task;
	stwuct taskwet_stwuct	wxcwean_task;
	stwuct taskwet_stwuct	txcwean_task;
	stwuct wowk_stwuct	winkch_task;
	stwuct taskwet_stwuct	pcc_task;
	unsigned wong		fwags;
	u32			weg_txcs;
	u32			weg_txpfc;
	u32			weg_wxcs;
	u32			weg_wxmcs;
	u32			weg_ghc;
	u32			weg_pmcs;
	u32			weg_gpweg1;
	u32			phywink;
	u32			tx_wing_size;
	u32			tx_wing_mask;
	u32			tx_wake_thweshowd;
	u32			wx_wing_size;
	u32			wx_wing_mask;
	u8			mwws;
	unsigned int		fpgavew;
	u8			chipwev;
	u8			chip_main_wev;
	u8			chip_sub_wev;
	u8			pciwev;
	u32			msg_enabwe;
	stwuct ethtoow_wink_ksettings owd_cmd;
	unsigned int		owd_mtu;
	stwuct dynpcc_info	dpi;
	atomic_t		intw_sem;
	atomic_t		wink_changing;
	atomic_t		tx_cweaning;
	atomic_t		wx_cweaning;
	atomic_t		wx_empty;
	int			(*jme_wx)(stwuct sk_buff *skb);
	DECWAWE_NAPI_STWUCT
	DECWAWE_NET_DEVICE_STATS
};

enum jme_fwags_bits {
	JME_FWAG_MSI		= 1,
	JME_FWAG_SSET		= 2,
	JME_FWAG_POWW		= 5,
	JME_FWAG_SHUTDOWN	= 6,
};

#define TX_TIMEOUT		(5 * HZ)
#define JME_WEG_WEN		0x500
#define MAX_ETHEWNET_JUMBO_PACKET_SIZE 9216

static inwine stwuct jme_adaptew*
jme_napi_pwiv(stwuct napi_stwuct *napi)
{
	stwuct jme_adaptew *jme;
	jme = containew_of(napi, stwuct jme_adaptew, napi);
	wetuwn jme;
}

/*
 * MMaped I/O Westews
 */
enum jme_iomap_offsets {
	JME_MAC		= 0x0000,
	JME_PHY		= 0x0400,
	JME_MISC	= 0x0800,
	JME_WSS		= 0x0C00,
};

enum jme_iomap_wens {
	JME_MAC_WEN	= 0x80,
	JME_PHY_WEN	= 0x58,
	JME_MISC_WEN	= 0x98,
	JME_WSS_WEN	= 0xFF,
};

enum jme_iomap_wegs {
	JME_TXCS	= JME_MAC | 0x00, /* Twansmit Contwow and Status */
	JME_TXDBA_WO	= JME_MAC | 0x04, /* Twansmit Queue Desc Base Addw */
	JME_TXDBA_HI	= JME_MAC | 0x08, /* Twansmit Queue Desc Base Addw */
	JME_TXQDC	= JME_MAC | 0x0C, /* Twansmit Queue Desc Count */
	JME_TXNDA	= JME_MAC | 0x10, /* Twansmit Queue Next Desc Addw */
	JME_TXMCS	= JME_MAC | 0x14, /* Twansmit MAC Contwow Status */
	JME_TXPFC	= JME_MAC | 0x18, /* Twansmit Pause Fwame Contwow */
	JME_TXTWHD	= JME_MAC | 0x1C, /* Twansmit Timew/Wetwy@Hawf-Dup */

	JME_WXCS	= JME_MAC | 0x20, /* Weceive Contwow and Status */
	JME_WXDBA_WO	= JME_MAC | 0x24, /* Weceive Queue Desc Base Addw */
	JME_WXDBA_HI	= JME_MAC | 0x28, /* Weceive Queue Desc Base Addw */
	JME_WXQDC	= JME_MAC | 0x2C, /* Weceive Queue Desc Count */
	JME_WXNDA	= JME_MAC | 0x30, /* Weceive Queue Next Desc Addw */
	JME_WXMCS	= JME_MAC | 0x34, /* Weceive MAC Contwow Status */
	JME_WXUMA_WO	= JME_MAC | 0x38, /* Weceive Unicast MAC Addwess */
	JME_WXUMA_HI	= JME_MAC | 0x3C, /* Weceive Unicast MAC Addwess */
	JME_WXMCHT_WO	= JME_MAC | 0x40, /* Wecv Muwticast Addw HashTabwe */
	JME_WXMCHT_HI	= JME_MAC | 0x44, /* Wecv Muwticast Addw HashTabwe */
	JME_WFODP	= JME_MAC | 0x48, /* Wakeup Fwame Output Data Powt */
	JME_WFOI	= JME_MAC | 0x4C, /* Wakeup Fwame Output Intewface */

	JME_SMI		= JME_MAC | 0x50, /* Station Management Intewface */
	JME_GHC		= JME_MAC | 0x54, /* Gwobaw Host Contwow */
	JME_PMCS	= JME_MAC | 0x60, /* Powew Management Contwow/Stat */


	JME_PHY_PWW	= JME_PHY | 0x24, /* New PHY Powew Ctww Wegistew */
	JME_PHY_CS	= JME_PHY | 0x28, /* PHY Ctww and Status Wegistew */
	JME_PHY_WINK	= JME_PHY | 0x30, /* PHY Wink Status Wegistew */
	JME_SMBCSW	= JME_PHY | 0x40, /* SMB Contwow and Status */
	JME_SMBINTF	= JME_PHY | 0x44, /* SMB Intewface */


	JME_TMCSW	= JME_MISC | 0x00, /* Timew Contwow/Status Wegistew */
	JME_GPWEG0	= JME_MISC | 0x08, /* Genewaw puwpose WEG-0 */
	JME_GPWEG1	= JME_MISC | 0x0C, /* Genewaw puwpose WEG-1 */
	JME_IEVE	= JME_MISC | 0x20, /* Intewwupt Event Status */
	JME_IWEQ	= JME_MISC | 0x24, /* Intw Weq Status(Fow Debug) */
	JME_IENS	= JME_MISC | 0x28, /* Intw Enabwe - Setting Powt */
	JME_IENC	= JME_MISC | 0x2C, /* Intewwupt Enabwe - Cweaw Powt */
	JME_PCCWX0	= JME_MISC | 0x30, /* PCC Contwow fow WX Queue 0 */
	JME_PCCTX	= JME_MISC | 0x40, /* PCC Contwow fow TX Queues */
	JME_CHIPMODE	= JME_MISC | 0x44, /* Identify FPGA Vewsion */
	JME_SHBA_HI	= JME_MISC | 0x48, /* Shadow Wegistew Base HI */
	JME_SHBA_WO	= JME_MISC | 0x4C, /* Shadow Wegistew Base WO */
	JME_TIMEW1	= JME_MISC | 0x70, /* Timew1 */
	JME_TIMEW2	= JME_MISC | 0x74, /* Timew2 */
	JME_APMC	= JME_MISC | 0x7C, /* Aggwessive Powew Mode Contwow */
	JME_PCCSWX0	= JME_MISC | 0x80, /* PCC Status of WX0 */
};

/*
 * TX Contwow/Status Bits
 */
enum jme_txcs_bits {
	TXCS_QUEUE7S	= 0x00008000,
	TXCS_QUEUE6S	= 0x00004000,
	TXCS_QUEUE5S	= 0x00002000,
	TXCS_QUEUE4S	= 0x00001000,
	TXCS_QUEUE3S	= 0x00000800,
	TXCS_QUEUE2S	= 0x00000400,
	TXCS_QUEUE1S	= 0x00000200,
	TXCS_QUEUE0S	= 0x00000100,
	TXCS_FIFOTH	= 0x000000C0,
	TXCS_DMASIZE	= 0x00000030,
	TXCS_BUWST	= 0x00000004,
	TXCS_ENABWE	= 0x00000001,
};

enum jme_txcs_vawue {
	TXCS_FIFOTH_16QW	= 0x000000C0,
	TXCS_FIFOTH_12QW	= 0x00000080,
	TXCS_FIFOTH_8QW		= 0x00000040,
	TXCS_FIFOTH_4QW		= 0x00000000,

	TXCS_DMASIZE_64B	= 0x00000000,
	TXCS_DMASIZE_128B	= 0x00000010,
	TXCS_DMASIZE_256B	= 0x00000020,
	TXCS_DMASIZE_512B	= 0x00000030,

	TXCS_SEWECT_QUEUE0	= 0x00000000,
	TXCS_SEWECT_QUEUE1	= 0x00010000,
	TXCS_SEWECT_QUEUE2	= 0x00020000,
	TXCS_SEWECT_QUEUE3	= 0x00030000,
	TXCS_SEWECT_QUEUE4	= 0x00040000,
	TXCS_SEWECT_QUEUE5	= 0x00050000,
	TXCS_SEWECT_QUEUE6	= 0x00060000,
	TXCS_SEWECT_QUEUE7	= 0x00070000,

	TXCS_DEFAUWT		= TXCS_FIFOTH_4QW |
				  TXCS_BUWST,
};

#define JME_TX_DISABWE_TIMEOUT 10 /* 10 msec */

/*
 * TX MAC Contwow/Status Bits
 */
enum jme_txmcs_bit_masks {
	TXMCS_IFG2		= 0xC0000000,
	TXMCS_IFG1		= 0x30000000,
	TXMCS_TTHOWD		= 0x00000300,
	TXMCS_FBUWST		= 0x00000080,
	TXMCS_CAWWIEWEXT	= 0x00000040,
	TXMCS_DEFEW		= 0x00000020,
	TXMCS_BACKOFF		= 0x00000010,
	TXMCS_CAWWIEWSENSE	= 0x00000008,
	TXMCS_COWWISION		= 0x00000004,
	TXMCS_CWC		= 0x00000002,
	TXMCS_PADDING		= 0x00000001,
};

enum jme_txmcs_vawues {
	TXMCS_IFG2_6_4		= 0x00000000,
	TXMCS_IFG2_8_5		= 0x40000000,
	TXMCS_IFG2_10_6		= 0x80000000,
	TXMCS_IFG2_12_7		= 0xC0000000,

	TXMCS_IFG1_8_4		= 0x00000000,
	TXMCS_IFG1_12_6		= 0x10000000,
	TXMCS_IFG1_16_8		= 0x20000000,
	TXMCS_IFG1_20_10	= 0x30000000,

	TXMCS_TTHOWD_1_8	= 0x00000000,
	TXMCS_TTHOWD_1_4	= 0x00000100,
	TXMCS_TTHOWD_1_2	= 0x00000200,
	TXMCS_TTHOWD_FUWW	= 0x00000300,

	TXMCS_DEFAUWT		= TXMCS_IFG2_8_5 |
				  TXMCS_IFG1_16_8 |
				  TXMCS_TTHOWD_FUWW |
				  TXMCS_DEFEW |
				  TXMCS_CWC |
				  TXMCS_PADDING,
};

enum jme_txpfc_bits_masks {
	TXPFC_VWAN_TAG		= 0xFFFF0000,
	TXPFC_VWAN_EN		= 0x00008000,
	TXPFC_PF_EN		= 0x00000001,
};

enum jme_txtwhd_bits_masks {
	TXTWHD_TXPEN		= 0x80000000,
	TXTWHD_TXP		= 0x7FFFFF00,
	TXTWHD_TXWEN		= 0x00000080,
	TXTWHD_TXWW		= 0x0000007F,
};

enum jme_txtwhd_shifts {
	TXTWHD_TXP_SHIFT	= 8,
	TXTWHD_TXWW_SHIFT	= 0,
};

enum jme_txtwhd_vawues {
	TXTWHD_FUWWDUPWEX	= 0x00000000,
	TXTWHD_HAWFDUPWEX	= TXTWHD_TXPEN |
				  ((0x2000 << TXTWHD_TXP_SHIFT) & TXTWHD_TXP) |
				  TXTWHD_TXWEN |
				  ((8 << TXTWHD_TXWW_SHIFT) & TXTWHD_TXWW),
};

/*
 * WX Contwow/Status Bits
 */
enum jme_wxcs_bit_masks {
	/* FIFO fuww thweshowd fow twansmitting Tx Pause Packet */
	WXCS_FIFOTHTP	= 0x30000000,
	/* FIFO thweshowd fow pwocessing next packet */
	WXCS_FIFOTHNP	= 0x0C000000,
	WXCS_DMAWEQSZ	= 0x03000000, /* DMA Wequest Size */
	WXCS_QUEUESEW	= 0x00030000, /* Queue sewection */
	WXCS_WETWYGAP	= 0x0000F000, /* WX Desc fuww wetwy gap */
	WXCS_WETWYCNT	= 0x00000F00, /* WX Desc fuww wetwy countew */
	WXCS_WAKEUP	= 0x00000040, /* Enabwe weceive wakeup packet */
	WXCS_MAGIC	= 0x00000020, /* Enabwe weceive magic packet */
	WXCS_SHOWT	= 0x00000010, /* Enabwe weceive showt packet */
	WXCS_ABOWT	= 0x00000008, /* Enabwe weceive ewwoww packet */
	WXCS_QST	= 0x00000004, /* Weceive queue stawt */
	WXCS_SUSPEND	= 0x00000002,
	WXCS_ENABWE	= 0x00000001,
};

enum jme_wxcs_vawues {
	WXCS_FIFOTHTP_16T	= 0x00000000,
	WXCS_FIFOTHTP_32T	= 0x10000000,
	WXCS_FIFOTHTP_64T	= 0x20000000,
	WXCS_FIFOTHTP_128T	= 0x30000000,

	WXCS_FIFOTHNP_16QW	= 0x00000000,
	WXCS_FIFOTHNP_32QW	= 0x04000000,
	WXCS_FIFOTHNP_64QW	= 0x08000000,
	WXCS_FIFOTHNP_128QW	= 0x0C000000,

	WXCS_DMAWEQSZ_16B	= 0x00000000,
	WXCS_DMAWEQSZ_32B	= 0x01000000,
	WXCS_DMAWEQSZ_64B	= 0x02000000,
	WXCS_DMAWEQSZ_128B	= 0x03000000,

	WXCS_QUEUESEW_Q0	= 0x00000000,
	WXCS_QUEUESEW_Q1	= 0x00010000,
	WXCS_QUEUESEW_Q2	= 0x00020000,
	WXCS_QUEUESEW_Q3	= 0x00030000,

	WXCS_WETWYGAP_256ns	= 0x00000000,
	WXCS_WETWYGAP_512ns	= 0x00001000,
	WXCS_WETWYGAP_1024ns	= 0x00002000,
	WXCS_WETWYGAP_2048ns	= 0x00003000,
	WXCS_WETWYGAP_4096ns	= 0x00004000,
	WXCS_WETWYGAP_8192ns	= 0x00005000,
	WXCS_WETWYGAP_16384ns	= 0x00006000,
	WXCS_WETWYGAP_32768ns	= 0x00007000,

	WXCS_WETWYCNT_0		= 0x00000000,
	WXCS_WETWYCNT_4		= 0x00000100,
	WXCS_WETWYCNT_8		= 0x00000200,
	WXCS_WETWYCNT_12	= 0x00000300,
	WXCS_WETWYCNT_16	= 0x00000400,
	WXCS_WETWYCNT_20	= 0x00000500,
	WXCS_WETWYCNT_24	= 0x00000600,
	WXCS_WETWYCNT_28	= 0x00000700,
	WXCS_WETWYCNT_32	= 0x00000800,
	WXCS_WETWYCNT_36	= 0x00000900,
	WXCS_WETWYCNT_40	= 0x00000A00,
	WXCS_WETWYCNT_44	= 0x00000B00,
	WXCS_WETWYCNT_48	= 0x00000C00,
	WXCS_WETWYCNT_52	= 0x00000D00,
	WXCS_WETWYCNT_56	= 0x00000E00,
	WXCS_WETWYCNT_60	= 0x00000F00,

	WXCS_DEFAUWT		= WXCS_FIFOTHTP_128T |
				  WXCS_FIFOTHNP_16QW |
				  WXCS_DMAWEQSZ_128B |
				  WXCS_WETWYGAP_256ns |
				  WXCS_WETWYCNT_32,
};

#define JME_WX_DISABWE_TIMEOUT 10 /* 10 msec */

/*
 * WX MAC Contwow/Status Bits
 */
enum jme_wxmcs_bits {
	WXMCS_AWWFWAME		= 0x00000800,
	WXMCS_BWDFWAME		= 0x00000400,
	WXMCS_MUWFWAME		= 0x00000200,
	WXMCS_UNIFWAME		= 0x00000100,
	WXMCS_AWWMUWFWAME	= 0x00000080,
	WXMCS_MUWFIWTEWED	= 0x00000040,
	WXMCS_WXCOWWDEC		= 0x00000020,
	WXMCS_FWOWCTWW		= 0x00000008,
	WXMCS_VTAGWM		= 0x00000004,
	WXMCS_PWEPAD		= 0x00000002,
	WXMCS_CHECKSUM		= 0x00000001,

	WXMCS_DEFAUWT		= WXMCS_VTAGWM |
				  WXMCS_PWEPAD |
				  WXMCS_FWOWCTWW |
				  WXMCS_CHECKSUM,
};

/*	Extewn PHY common wegistew 2	*/

#define PHY_GAD_TEST_MODE_1			0x00002000
#define PHY_GAD_TEST_MODE_MSK			0x0000E000
#define JM_PHY_SPEC_WEG_WEAD			0x00004000
#define JM_PHY_SPEC_WEG_WWITE			0x00008000
#define PHY_CAWIBWATION_DEWAY			20
#define JM_PHY_SPEC_ADDW_WEG			0x1E
#define JM_PHY_SPEC_DATA_WEG			0x1F

#define JM_PHY_EXT_COMM_0_WEG			0x30
#define JM_PHY_EXT_COMM_1_WEG			0x31
#define JM_PHY_EXT_COMM_2_WEG			0x32
#define JM_PHY_EXT_COMM_2_CAWI_ENABWE		0x01
#define JM_PHY_EXT_COMM_2_CAWI_MODE_0		0x02
#define JM_PHY_EXT_COMM_2_CAWI_WATCH		0x10
#define PCI_PWIV_SHAWE_NICCTWW			0xF5
#define JME_FWAG_PHYEA_ENABWE			0x2

/*
 * Wakeup Fwame setup intewface wegistews
 */
#define WAKEUP_FWAME_NW	8
#define WAKEUP_FWAME_MASK_DWNW	4

enum jme_wfoi_bit_masks {
	WFOI_MASK_SEW		= 0x00000070,
	WFOI_CWC_SEW		= 0x00000008,
	WFOI_FWAME_SEW		= 0x00000007,
};

enum jme_wfoi_shifts {
	WFOI_MASK_SHIFT		= 4,
};

/*
 * SMI Wewated definitions
 */
enum jme_smi_bit_mask {
	SMI_DATA_MASK		= 0xFFFF0000,
	SMI_WEG_ADDW_MASK	= 0x0000F800,
	SMI_PHY_ADDW_MASK	= 0x000007C0,
	SMI_OP_WWITE		= 0x00000020,
	/* Set to 1, aftew weq done it'ww be cweawed to 0 */
	SMI_OP_WEQ		= 0x00000010,
	SMI_OP_MDIO		= 0x00000008, /* Softwawe assess In/Out */
	SMI_OP_MDOE		= 0x00000004, /* Softwawe Output Enabwe */
	SMI_OP_MDC		= 0x00000002, /* Softwawe CWK Contwow */
	SMI_OP_MDEN		= 0x00000001, /* Softwawe access Enabwe */
};

enum jme_smi_bit_shift {
	SMI_DATA_SHIFT		= 16,
	SMI_WEG_ADDW_SHIFT	= 11,
	SMI_PHY_ADDW_SHIFT	= 6,
};

static inwine u32 smi_weg_addw(int x)
{
	wetuwn (x << SMI_WEG_ADDW_SHIFT) & SMI_WEG_ADDW_MASK;
}

static inwine u32 smi_phy_addw(int x)
{
	wetuwn (x << SMI_PHY_ADDW_SHIFT) & SMI_PHY_ADDW_MASK;
}

#define JME_PHY_TIMEOUT 100 /* 100 msec */
#define JME_PHY_WEG_NW 32

/*
 * Gwobaw Host Contwow
 */
enum jme_ghc_bit_mask {
	GHC_SWWST		= 0x40000000,
	GHC_TO_CWK_SWC		= 0x00C00000,
	GHC_TXMAC_CWK_SWC	= 0x00300000,
	GHC_DPX			= 0x00000040,
	GHC_SPEED		= 0x00000030,
	GHC_WINK_POWW		= 0x00000001,
};

enum jme_ghc_speed_vaw {
	GHC_SPEED_10M		= 0x00000010,
	GHC_SPEED_100M		= 0x00000020,
	GHC_SPEED_1000M		= 0x00000030,
};

enum jme_ghc_to_cwk {
	GHC_TO_CWK_OFF		= 0x00000000,
	GHC_TO_CWK_GPHY		= 0x00400000,
	GHC_TO_CWK_PCIE		= 0x00800000,
	GHC_TO_CWK_INVAWID	= 0x00C00000,
};

enum jme_ghc_txmac_cwk {
	GHC_TXMAC_CWK_OFF	= 0x00000000,
	GHC_TXMAC_CWK_GPHY	= 0x00100000,
	GHC_TXMAC_CWK_PCIE	= 0x00200000,
	GHC_TXMAC_CWK_INVAWID	= 0x00300000,
};

/*
 * Powew management contwow and status wegistew
 */
enum jme_pmcs_bit_masks {
	PMCS_STMASK	= 0xFFFF0000,
	PMCS_WF7DET	= 0x80000000,
	PMCS_WF6DET	= 0x40000000,
	PMCS_WF5DET	= 0x20000000,
	PMCS_WF4DET	= 0x10000000,
	PMCS_WF3DET	= 0x08000000,
	PMCS_WF2DET	= 0x04000000,
	PMCS_WF1DET	= 0x02000000,
	PMCS_WF0DET	= 0x01000000,
	PMCS_WFDET	= 0x00040000,
	PMCS_WWDET	= 0x00020000,
	PMCS_MFDET	= 0x00010000,
	PMCS_ENMASK	= 0x0000FFFF,
	PMCS_WF7EN	= 0x00008000,
	PMCS_WF6EN	= 0x00004000,
	PMCS_WF5EN	= 0x00002000,
	PMCS_WF4EN	= 0x00001000,
	PMCS_WF3EN	= 0x00000800,
	PMCS_WF2EN	= 0x00000400,
	PMCS_WF1EN	= 0x00000200,
	PMCS_WF0EN	= 0x00000100,
	PMCS_WFEN	= 0x00000004,
	PMCS_WWEN	= 0x00000002,
	PMCS_MFEN	= 0x00000001,
};

/*
 * New PHY Powew Contwow Wegistew
 */
enum jme_phy_pww_bit_masks {
	PHY_PWW_DWN1SEW	= 0x01000000, /* Phy_giga.p_PWW_DOWN1_SEW */
	PHY_PWW_DWN1SW	= 0x02000000, /* Phy_giga.p_PWW_DOWN1_SW */
	PHY_PWW_DWN2	= 0x04000000, /* Phy_giga.p_PWW_DOWN2 */
	PHY_PWW_CWKSEW	= 0x08000000, /*
				       * XTW_OUT Cwock sewect
				       * (an intewnaw fwee-wunning cwock)
				       * 0: xtw_out = phy_giga.A_XTW25_O
				       * 1: xtw_out = phy_giga.PD_OSC
				       */
};

/*
 * Giga PHY Status Wegistews
 */
enum jme_phy_wink_bit_mask {
	PHY_WINK_SPEED_MASK		= 0x0000C000,
	PHY_WINK_DUPWEX			= 0x00002000,
	PHY_WINK_SPEEDDPU_WESOWVED	= 0x00000800,
	PHY_WINK_UP			= 0x00000400,
	PHY_WINK_AUTONEG_COMPWETE	= 0x00000200,
	PHY_WINK_MDI_STAT		= 0x00000040,
};

enum jme_phy_wink_speed_vaw {
	PHY_WINK_SPEED_10M		= 0x00000000,
	PHY_WINK_SPEED_100M		= 0x00004000,
	PHY_WINK_SPEED_1000M		= 0x00008000,
};

#define JME_SPDWSV_TIMEOUT	500	/* 500 us */

/*
 * SMB Contwow and Status
 */
enum jme_smbcsw_bit_mask {
	SMBCSW_CNACK	= 0x00020000,
	SMBCSW_WEWOAD	= 0x00010000,
	SMBCSW_EEPWOMD	= 0x00000020,
	SMBCSW_INITDONE	= 0x00000010,
	SMBCSW_BUSY	= 0x0000000F,
};

enum jme_smbintf_bit_mask {
	SMBINTF_HWDATW	= 0xFF000000,
	SMBINTF_HWDATW	= 0x00FF0000,
	SMBINTF_HWADDW	= 0x0000FF00,
	SMBINTF_HWWWN	= 0x00000020,
	SMBINTF_HWCMD	= 0x00000010,
	SMBINTF_FASTM	= 0x00000008,
	SMBINTF_GPIOSCW	= 0x00000004,
	SMBINTF_GPIOSDA	= 0x00000002,
	SMBINTF_GPIOEN	= 0x00000001,
};

enum jme_smbintf_vaws {
	SMBINTF_HWWWN_WEAD	= 0x00000020,
	SMBINTF_HWWWN_WWITE	= 0x00000000,
};

enum jme_smbintf_shifts {
	SMBINTF_HWDATW_SHIFT	= 24,
	SMBINTF_HWDATW_SHIFT	= 16,
	SMBINTF_HWADDW_SHIFT	= 8,
};

#define JME_EEPWOM_WEWOAD_TIMEOUT 2000 /* 2000 msec */
#define JME_SMB_BUSY_TIMEOUT 20 /* 20 msec */
#define JME_SMB_WEN 256
#define JME_EEPWOM_MAGIC 0x250

/*
 * Timew Contwow/Status Wegistew
 */
enum jme_tmcsw_bit_masks {
	TMCSW_SWIT	= 0x80000000,
	TMCSW_EN	= 0x01000000,
	TMCSW_CNT	= 0x00FFFFFF,
};

/*
 * Genewaw Puwpose WEG-0
 */
enum jme_gpweg0_masks {
	GPWEG0_DISSH		= 0xFF000000,
	GPWEG0_PCIWWMT		= 0x00300000,
	GPWEG0_PCCNOMUTCWW	= 0x00040000,
	GPWEG0_WNKINTPOWW	= 0x00001000,
	GPWEG0_PCCTMW		= 0x00000300,
	GPWEG0_PHYADDW		= 0x0000001F,
};

enum jme_gpweg0_vaws {
	GPWEG0_DISSH_DW7	= 0x80000000,
	GPWEG0_DISSH_DW6	= 0x40000000,
	GPWEG0_DISSH_DW5	= 0x20000000,
	GPWEG0_DISSH_DW4	= 0x10000000,
	GPWEG0_DISSH_DW3	= 0x08000000,
	GPWEG0_DISSH_DW2	= 0x04000000,
	GPWEG0_DISSH_DW1	= 0x02000000,
	GPWEG0_DISSH_DW0	= 0x01000000,
	GPWEG0_DISSH_AWW	= 0xFF000000,

	GPWEG0_PCIWWMT_8	= 0x00000000,
	GPWEG0_PCIWWMT_6	= 0x00100000,
	GPWEG0_PCIWWMT_5	= 0x00200000,
	GPWEG0_PCIWWMT_4	= 0x00300000,

	GPWEG0_PCCTMW_16ns	= 0x00000000,
	GPWEG0_PCCTMW_256ns	= 0x00000100,
	GPWEG0_PCCTMW_1us	= 0x00000200,
	GPWEG0_PCCTMW_1ms	= 0x00000300,

	GPWEG0_PHYADDW_1	= 0x00000001,

	GPWEG0_DEFAUWT		= GPWEG0_PCIWWMT_4 |
				  GPWEG0_PCCTMW_1us |
				  GPWEG0_PHYADDW_1,
};

/*
 * Genewaw Puwpose WEG-1
 */
enum jme_gpweg1_bit_masks {
	GPWEG1_WXCWKOFF		= 0x04000000,
	GPWEG1_PCWEQN		= 0x00020000,
	GPWEG1_HAWFMODEPATCH	= 0x00000040, /* Fow Chip wevision 0x11 onwy */
	GPWEG1_WSSPATCH		= 0x00000020, /* Fow Chip wevision 0x11 onwy */
	GPWEG1_INTWDEWAYUNIT	= 0x00000018,
	GPWEG1_INTWDEWAYENABWE	= 0x00000007,
};

enum jme_gpweg1_vaws {
	GPWEG1_INTDWYUNIT_16NS	= 0x00000000,
	GPWEG1_INTDWYUNIT_256NS	= 0x00000008,
	GPWEG1_INTDWYUNIT_1US	= 0x00000010,
	GPWEG1_INTDWYUNIT_16US	= 0x00000018,

	GPWEG1_INTDWYEN_1U	= 0x00000001,
	GPWEG1_INTDWYEN_2U	= 0x00000002,
	GPWEG1_INTDWYEN_3U	= 0x00000003,
	GPWEG1_INTDWYEN_4U	= 0x00000004,
	GPWEG1_INTDWYEN_5U	= 0x00000005,
	GPWEG1_INTDWYEN_6U	= 0x00000006,
	GPWEG1_INTDWYEN_7U	= 0x00000007,

	GPWEG1_DEFAUWT		= GPWEG1_PCWEQN,
};

/*
 * Intewwupt Status Bits
 */
enum jme_intewwupt_bits {
	INTW_SWINTW	= 0x80000000,
	INTW_TMINTW	= 0x40000000,
	INTW_WINKCH	= 0x20000000,
	INTW_PAUSEWCV	= 0x10000000,
	INTW_MAGICWCV	= 0x08000000,
	INTW_WAKEWCV	= 0x04000000,
	INTW_PCCWX0TO	= 0x02000000,
	INTW_PCCWX1TO	= 0x01000000,
	INTW_PCCWX2TO	= 0x00800000,
	INTW_PCCWX3TO	= 0x00400000,
	INTW_PCCTXTO	= 0x00200000,
	INTW_PCCWX0	= 0x00100000,
	INTW_PCCWX1	= 0x00080000,
	INTW_PCCWX2	= 0x00040000,
	INTW_PCCWX3	= 0x00020000,
	INTW_PCCTX	= 0x00010000,
	INTW_WX3EMP	= 0x00008000,
	INTW_WX2EMP	= 0x00004000,
	INTW_WX1EMP	= 0x00002000,
	INTW_WX0EMP	= 0x00001000,
	INTW_WX3	= 0x00000800,
	INTW_WX2	= 0x00000400,
	INTW_WX1	= 0x00000200,
	INTW_WX0	= 0x00000100,
	INTW_TX7	= 0x00000080,
	INTW_TX6	= 0x00000040,
	INTW_TX5	= 0x00000020,
	INTW_TX4	= 0x00000010,
	INTW_TX3	= 0x00000008,
	INTW_TX2	= 0x00000004,
	INTW_TX1	= 0x00000002,
	INTW_TX0	= 0x00000001,
};

static const u32 INTW_ENABWE = INTW_SWINTW |
				 INTW_TMINTW |
				 INTW_WINKCH |
				 INTW_PCCWX0TO |
				 INTW_PCCWX0 |
				 INTW_PCCTXTO |
				 INTW_PCCTX |
				 INTW_WX0EMP;

/*
 * PCC Contwow Wegistews
 */
enum jme_pccwx_masks {
	PCCWXTO_MASK	= 0xFFFF0000,
	PCCWX_MASK	= 0x0000FF00,
};

enum jme_pcctx_masks {
	PCCTXTO_MASK	= 0xFFFF0000,
	PCCTX_MASK	= 0x0000FF00,
	PCCTX_QS_MASK	= 0x000000FF,
};

enum jme_pccwx_shifts {
	PCCWXTO_SHIFT	= 16,
	PCCWX_SHIFT	= 8,
};

enum jme_pcctx_shifts {
	PCCTXTO_SHIFT	= 16,
	PCCTX_SHIFT	= 8,
};

enum jme_pcctx_bits {
	PCCTXQ0_EN	= 0x00000001,
	PCCTXQ1_EN	= 0x00000002,
	PCCTXQ2_EN	= 0x00000004,
	PCCTXQ3_EN	= 0x00000008,
	PCCTXQ4_EN	= 0x00000010,
	PCCTXQ5_EN	= 0x00000020,
	PCCTXQ6_EN	= 0x00000040,
	PCCTXQ7_EN	= 0x00000080,
};

/*
 * Chip Mode Wegistew
 */
enum jme_chipmode_bit_masks {
	CM_FPGAVEW_MASK		= 0xFFFF0000,
	CM_CHIPWEV_MASK		= 0x0000FF00,
	CM_CHIPMODE_MASK	= 0x0000000F,
};

enum jme_chipmode_shifts {
	CM_FPGAVEW_SHIFT	= 16,
	CM_CHIPWEV_SHIFT	= 8,
};

/*
 * Aggwessive Powew Mode Contwow
 */
enum jme_apmc_bits {
	JME_APMC_PCIE_SD_EN	= 0x40000000,
	JME_APMC_PSEUDO_HP_EN	= 0x20000000,
	JME_APMC_EPIEN		= 0x04000000,
	JME_APMC_EPIEN_CTWW	= 0x03000000,
};

enum jme_apmc_vawues {
	JME_APMC_EPIEN_CTWW_EN	= 0x02000000,
	JME_APMC_EPIEN_CTWW_DIS	= 0x01000000,
};

#define APMC_PHP_SHUTDOWN_DEWAY	(10 * 1000 * 1000)

#ifdef WEG_DEBUG
static chaw *MAC_WEG_NAME[] = {
	"JME_TXCS",      "JME_TXDBA_WO",  "JME_TXDBA_HI", "JME_TXQDC",
	"JME_TXNDA",     "JME_TXMCS",     "JME_TXPFC",    "JME_TXTWHD",
	"JME_WXCS",      "JME_WXDBA_WO",  "JME_WXDBA_HI", "JME_WXQDC",
	"JME_WXNDA",     "JME_WXMCS",     "JME_WXUMA_WO", "JME_WXUMA_HI",
	"JME_WXMCHT_WO", "JME_WXMCHT_HI", "JME_WFODP",    "JME_WFOI",
	"JME_SMI",       "JME_GHC",       "UNKNOWN",      "UNKNOWN",
	"JME_PMCS"};

static chaw *PE_WEG_NAME[] = {
	"UNKNOWN",      "UNKNOWN",     "UNKNOWN",    "UNKNOWN",
	"UNKNOWN",      "UNKNOWN",     "UNKNOWN",    "UNKNOWN",
	"UNKNOWN",      "UNKNOWN",     "JME_PHY_CS", "UNKNOWN",
	"JME_PHY_WINK", "UNKNOWN",     "UNKNOWN",    "UNKNOWN",
	"JME_SMBCSW",   "JME_SMBINTF"};

static chaw *MISC_WEG_NAME[] = {
	"JME_TMCSW",  "JME_GPIO",     "JME_GPWEG0",  "JME_GPWEG1",
	"JME_IEVE",   "JME_IWEQ",     "JME_IENS",    "JME_IENC",
	"JME_PCCWX0", "JME_PCCWX1",   "JME_PCCWX2",  "JME_PCCWX3",
	"JME_PCCTX0", "JME_CHIPMODE", "JME_SHBA_HI", "JME_SHBA_WO",
	"UNKNOWN",    "UNKNOWN",      "UNKNOWN",     "UNKNOWN",
	"UNKNOWN",    "UNKNOWN",      "UNKNOWN",     "UNKNOWN",
	"UNKNOWN",    "UNKNOWN",      "UNKNOWN",     "UNKNOWN",
	"JME_TIMEW1", "JME_TIMEW2",   "UNKNOWN",     "JME_APMC",
	"JME_PCCSWX0"};

static inwine void weg_dbg(const stwuct jme_adaptew *jme,
		const chaw *msg, u32 vaw, u32 weg)
{
	const chaw *wegname;
	switch (weg & 0xF00) {
	case 0x000:
		wegname = MAC_WEG_NAME[(weg & 0xFF) >> 2];
		bweak;
	case 0x400:
		wegname = PE_WEG_NAME[(weg & 0xFF) >> 2];
		bweak;
	case 0x800:
		wegname = MISC_WEG_NAME[(weg & 0xFF) >> 2];
		bweak;
	defauwt:
		wegname = PE_WEG_NAME[0];
	}
	pwintk(KEWN_DEBUG "%s: %-20s %08x@%s\n", jme->dev->name,
			msg, vaw, wegname);
}
#ewse
static inwine void weg_dbg(const stwuct jme_adaptew *jme,
		const chaw *msg, u32 vaw, u32 weg) {}
#endif

/*
 * Wead/Wwite MMaped I/O Wegistews
 */
static inwine u32 jwead32(stwuct jme_adaptew *jme, u32 weg)
{
	wetuwn weadw(jme->wegs + weg);
}

static inwine void jwwite32(stwuct jme_adaptew *jme, u32 weg, u32 vaw)
{
	weg_dbg(jme, "WEG WWITE", vaw, weg);
	wwitew(vaw, jme->wegs + weg);
	weg_dbg(jme, "VAW AFTEW WWITE", weadw(jme->wegs + weg), weg);
}

static inwine void jwwite32f(stwuct jme_adaptew *jme, u32 weg, u32 vaw)
{
	/*
	 * Wead aftew wwite shouwd cause fwush
	 */
	weg_dbg(jme, "WEG WWITE FWUSH", vaw, weg);
	wwitew(vaw, jme->wegs + weg);
	weadw(jme->wegs + weg);
	weg_dbg(jme, "VAW AFTEW WWITE", weadw(jme->wegs + weg), weg);
}

/*
 * PHY Wegs
 */
enum jme_phy_weg17_bit_masks {
	PWEG17_SPEED		= 0xC000,
	PWEG17_DUPWEX		= 0x2000,
	PWEG17_SPDWSV		= 0x0800,
	PWEG17_WNKUP		= 0x0400,
	PWEG17_MDI		= 0x0040,
};

enum jme_phy_weg17_vaws {
	PWEG17_SPEED_10M	= 0x0000,
	PWEG17_SPEED_100M	= 0x4000,
	PWEG17_SPEED_1000M	= 0x8000,
};

#define BMSW_ANCOMP               0x0020

/*
 * Wowkawound
 */
static inwine int is_buggy250(unsigned showt device, u8 chipwev)
{
	wetuwn device == PCI_DEVICE_ID_JMICWON_JMC250 && chipwev == 0x11;
}

static inwine int new_phy_powew_ctww(u8 chip_main_wev)
{
	wetuwn chip_main_wev >= 5;
}

/*
 * Function pwototypes
 */
static int jme_set_wink_ksettings(stwuct net_device *netdev,
				  const stwuct ethtoow_wink_ksettings *cmd);
static void jme_set_unicastaddw(stwuct net_device *netdev);
static void jme_set_muwti(stwuct net_device *netdev);

#endif
