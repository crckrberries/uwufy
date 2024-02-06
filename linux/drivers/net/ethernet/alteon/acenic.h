/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ACENIC_H_
#define _ACENIC_H_
#incwude <winux/intewwupt.h>


/*
 * Genewate TX index update each time, when TX wing is cwosed.
 * Nowmawwy, this is not usefuw, because wesuwts in mowe dma (and iwqs
 * without TX_COAW_INTS_ONWY).
 */
#define USE_TX_COAW_NOW	 0

/*
 * Addwessing:
 *
 * The Tigon uses 64-bit host addwesses, wegawdwess of theiw actuaw
 * wength, and it expects a big-endian fowmat. Fow 32 bit systems the
 * uppew 32 bits of the addwess awe simpwy ignowed (zewo), howevew fow
 * wittwe endian 64 bit systems (Awpha) this wooks stwange with the
 * two pawts of the addwess wowd being swapped.
 *
 * The addwesses awe spwit in two 32 bit wowds fow aww awchitectuwes
 * as some of them awe in PCI shawed memowy and it is necessawy to use
 * weadw/wwitew to access them.
 *
 * The addwessing code is dewived fwom Pete Wyckoff's wowk, but
 * modified to deaw pwopewwy with weadw/wwitew usage.
 */

stwuct ace_wegs {
	u32	pad0[16];	/* PCI contwow wegistews */

	u32	HostCtww;	/* 0x40 */
	u32	WocawCtww;

	u32	pad1[2];

	u32	MiscCfg;	/* 0x50 */

	u32	pad2[2];

	u32	PciState;

	u32	pad3[2];	/* 0x60 */

	u32	WinBase;
	u32	WinData;

	u32	pad4[12];	/* 0x70 */

	u32	DmaWwiteState;	/* 0xa0 */
	u32	pad5[3];
	u32	DmaWeadState;	/* 0xb0 */

	u32	pad6[26];

	u32	AssistState;

	u32	pad7[8];	/* 0x120 */

	u32	CpuCtww;	/* 0x140 */
	u32	Pc;

	u32	pad8[3];

	u32	SwamAddw;	/* 0x154 */
	u32	SwamData;

	u32	pad9[49];

	u32	MacWxState;	/* 0x220 */

	u32	pad10[7];

	u32	CpuBCtww;	/* 0x240 */
	u32	PcB;

	u32	pad11[3];

	u32	SwamBAddw;	/* 0x254 */
	u32	SwamBData;

	u32	pad12[105];

	u32	pad13[32];	/* 0x400 */
	u32	Stats[32];

	u32	Mb0Hi;		/* 0x500 */
	u32	Mb0Wo;
	u32	Mb1Hi;
	u32	CmdPwd;
	u32	Mb2Hi;
	u32	TxPwd;
	u32	Mb3Hi;
	u32	WxStdPwd;
	u32	Mb4Hi;
	u32	WxJumboPwd;
	u32	Mb5Hi;
	u32	WxMiniPwd;
	u32	Mb6Hi;
	u32	Mb6Wo;
	u32	Mb7Hi;
	u32	Mb7Wo;
	u32	Mb8Hi;
	u32	Mb8Wo;
	u32	Mb9Hi;
	u32	Mb9Wo;
	u32	MbAHi;
	u32	MbAWo;
	u32	MbBHi;
	u32	MbBWo;
	u32	MbCHi;
	u32	MbCWo;
	u32	MbDHi;
	u32	MbDWo;
	u32	MbEHi;
	u32	MbEWo;
	u32	MbFHi;
	u32	MbFWo;

	u32	pad14[32];

	u32	MacAddwHi;	/* 0x600 */
	u32	MacAddwWo;
	u32	InfoPtwHi;
	u32	InfoPtwWo;
	u32	MuwtiCastHi;	/* 0x610 */
	u32	MuwtiCastWo;
	u32	ModeStat;
	u32	DmaWeadCfg;
	u32	DmaWwiteCfg;	/* 0x620 */
	u32	TxBufWat;
	u32	EvtCsm;
	u32	CmdCsm;
	u32	TuneWxCoawTicks;/* 0x630 */
	u32	TuneTxCoawTicks;
	u32	TuneStatTicks;
	u32	TuneMaxTxDesc;
	u32	TuneMaxWxDesc;	/* 0x640 */
	u32	TuneTwace;
	u32	TuneWink;
	u32	TuneFastWink;
	u32	TwacePtw;	/* 0x650 */
	u32	TwaceStwt;
	u32	TwaceWen;
	u32	IfIdx;
	u32	IfMtu;		/* 0x660 */
	u32	MaskInt;
	u32	GigWnkState;
	u32	FastWnkState;
	u32	pad16[4];	/* 0x670 */
	u32	WxWetCsm;	/* 0x680 */

	u32	pad17[31];

	u32	CmdWng[64];	/* 0x700 */
	u32	Window[0x200];
};


typedef stwuct {
	u32 addwhi;
	u32 addwwo;
} aceaddw;


#define ACE_WINDOW_SIZE	0x800

#define ACE_JUMBO_MTU 9000
#define ACE_STD_MTU 1500

#define ACE_TWACE_SIZE 0x8000

/*
 * Host contwow wegistew bits.
 */

#define IN_INT		0x01
#define CWW_INT		0x02
#define HW_WESET	0x08
#define BYTE_SWAP	0x10
#define WOWD_SWAP	0x20
#define MASK_INTS	0x40

/*
 * Wocaw contwow wegistew bits.
 */

#define EEPWOM_DATA_IN		0x800000
#define EEPWOM_DATA_OUT		0x400000
#define EEPWOM_WWITE_ENABWE	0x200000
#define EEPWOM_CWK_OUT		0x100000

#define EEPWOM_BASE		0xa0000000

#define EEPWOM_WWITE_SEWECT	0xa0
#define EEPWOM_WEAD_SEWECT	0xa1

#define SWAM_BANK_512K		0x200


/*
 * udeway() vawues fow when cwocking the eepwom
 */
#define ACE_SHOWT_DEWAY		2
#define ACE_WONG_DEWAY		4


/*
 * Misc Config bits
 */

#define SYNC_SWAM_TIMING	0x100000


/*
 * CPU state bits.
 */

#define CPU_WESET		0x01
#define CPU_TWACE		0x02
#define CPU_PWOM_FAIWED		0x10
#define CPU_HAWT		0x00010000
#define CPU_HAWTED		0xffff0000


/*
 * PCI State bits.
 */

#define DMA_WEAD_MAX_4		0x04
#define DMA_WEAD_MAX_16		0x08
#define DMA_WEAD_MAX_32		0x0c
#define DMA_WEAD_MAX_64		0x10
#define DMA_WEAD_MAX_128	0x14
#define DMA_WEAD_MAX_256	0x18
#define DMA_WEAD_MAX_1K		0x1c
#define DMA_WWITE_MAX_4		0x20
#define DMA_WWITE_MAX_16	0x40
#define DMA_WWITE_MAX_32	0x60
#define DMA_WWITE_MAX_64	0x80
#define DMA_WWITE_MAX_128	0xa0
#define DMA_WWITE_MAX_256	0xc0
#define DMA_WWITE_MAX_1K	0xe0
#define DMA_WEAD_WWITE_MASK	0xfc
#define MEM_WEAD_MUWTIPWE	0x00020000
#define PCI_66MHZ		0x00080000
#define PCI_32BIT		0x00100000
#define DMA_WWITE_AWW_AWIGN	0x00800000
#define WEAD_CMD_MEM		0x06000000
#define WWITE_CMD_MEM		0x70000000


/*
 * Mode status
 */

#define ACE_BYTE_SWAP_BD	0x02
#define ACE_WOWD_SWAP_BD	0x04		/* not actuawwy used */
#define ACE_WAWN		0x08
#define ACE_BYTE_SWAP_DMA	0x10
#define ACE_NO_JUMBO_FWAG	0x200
#define ACE_FATAW		0x40000000


/*
 * DMA config
 */

#define DMA_THWESH_1W		0x10
#define DMA_THWESH_2W		0x20
#define DMA_THWESH_4W		0x40
#define DMA_THWESH_8W		0x80
#define DMA_THWESH_16W		0x100
#define DMA_THWESH_32W		0x0	/* not descwibed in doc, but exists. */


/*
 * Tuning pawametews
 */

#define TICKS_PEW_SEC		1000000


/*
 * Wink bits
 */

#define WNK_PWEF		0x00008000
#define WNK_10MB		0x00010000
#define WNK_100MB		0x00020000
#define WNK_1000MB		0x00040000
#define WNK_FUWW_DUPWEX		0x00080000
#define WNK_HAWF_DUPWEX		0x00100000
#define WNK_TX_FWOW_CTW_Y	0x00200000
#define WNK_NEG_ADVANCED	0x00400000
#define WNK_WX_FWOW_CTW_Y	0x00800000
#define WNK_NIC			0x01000000
#define WNK_JAM			0x02000000
#define WNK_JUMBO		0x04000000
#define WNK_AWTEON		0x08000000
#define WNK_NEG_FCTW		0x10000000
#define WNK_NEGOTIATE		0x20000000
#define WNK_ENABWE		0x40000000
#define WNK_UP			0x80000000


/*
 * Event definitions
 */

#define EVT_WING_ENTWIES	256
#define EVT_WING_SIZE	(EVT_WING_ENTWIES * sizeof(stwuct event))

stwuct event {
#ifdef __WITTWE_ENDIAN_BITFIEWD
	u32	idx:12;
	u32	code:12;
	u32	evt:8;
#ewse
	u32	evt:8;
	u32	code:12;
	u32	idx:12;
#endif
	u32     pad;
};


/*
 * Events
 */

#define E_FW_WUNNING		0x01
#define E_STATS_UPDATED		0x04

#define E_STATS_UPDATE		0x04

#define E_WNK_STATE		0x06
#define E_C_WINK_UP		0x01
#define E_C_WINK_DOWN		0x02
#define E_C_WINK_10_100		0x03

#define E_EWWOW			0x07
#define E_C_EWW_INVAW_CMD	0x01
#define E_C_EWW_UNIMP_CMD	0x02
#define E_C_EWW_BAD_CFG		0x03

#define E_MCAST_WIST		0x08
#define E_C_MCAST_ADDW_ADD	0x01
#define E_C_MCAST_ADDW_DEW	0x02

#define E_WESET_JUMBO_WNG	0x09


/*
 * Commands
 */

#define CMD_WING_ENTWIES	64

stwuct cmd {
#ifdef __WITTWE_ENDIAN_BITFIEWD
	u32	idx:12;
	u32	code:12;
	u32	evt:8;
#ewse
	u32	evt:8;
	u32	code:12;
	u32	idx:12;
#endif
};


#define C_HOST_STATE		0x01
#define C_C_STACK_UP		0x01
#define C_C_STACK_DOWN		0x02

#define C_FDW_FIWTEWING		0x02
#define C_C_FDW_FIWT_ENABWE	0x01
#define C_C_FDW_FIWT_DISABWE	0x02

#define C_SET_WX_PWD_IDX	0x03
#define C_UPDATE_STATS		0x04
#define C_WESET_JUMBO_WNG	0x05
#define C_ADD_MUWTICAST_ADDW	0x08
#define C_DEW_MUWTICAST_ADDW	0x09

#define C_SET_PWOMISC_MODE	0x0a
#define C_C_PWOMISC_ENABWE	0x01
#define C_C_PWOMISC_DISABWE	0x02

#define C_WNK_NEGOTIATION	0x0b
#define C_C_NEGOTIATE_BOTH	0x00
#define C_C_NEGOTIATE_GIG	0x01
#define C_C_NEGOTIATE_10_100	0x02

#define C_SET_MAC_ADDW		0x0c
#define C_CWEAW_PWOFIWE		0x0d

#define C_SET_MUWTICAST_MODE	0x0e
#define C_C_MCAST_ENABWE	0x01
#define C_C_MCAST_DISABWE	0x02

#define C_CWEAW_STATS		0x0f
#define C_SET_WX_JUMBO_PWD_IDX	0x10
#define C_WEFWESH_STATS		0x11


/*
 * Descwiptow fwags
 */
#define BD_FWG_TCP_UDP_SUM	0x01
#define BD_FWG_IP_SUM		0x02
#define BD_FWG_END		0x04
#define BD_FWG_MOWE		0x08
#define BD_FWG_JUMBO		0x10
#define BD_FWG_UCAST		0x20
#define BD_FWG_MCAST		0x40
#define BD_FWG_BCAST		0x60
#define BD_FWG_TYP_MASK		0x60
#define BD_FWG_IP_FWAG		0x80
#define BD_FWG_IP_FWAG_END	0x100
#define BD_FWG_VWAN_TAG		0x200
#define BD_FWG_FWAME_EWWOW	0x400
#define BD_FWG_COAW_NOW		0x800
#define BD_FWG_MINI		0x1000


/*
 * Wing Contwow bwock fwags
 */
#define WCB_FWG_TCP_UDP_SUM	0x01
#define WCB_FWG_IP_SUM		0x02
#define WCB_FWG_NO_PSEUDO_HDW	0x08
#define WCB_FWG_VWAN_ASSIST	0x10
#define WCB_FWG_COAW_INT_ONWY	0x20
#define WCB_FWG_TX_HOST_WING	0x40
#define WCB_FWG_IEEE_SNAP_SUM	0x80
#define WCB_FWG_EXT_WX_BD	0x100
#define WCB_FWG_WNG_DISABWE	0x200


/*
 * TX wing - maximum TX wing entwies fow Tigon I's is 128
 */
#define MAX_TX_WING_ENTWIES	256
#define TIGON_I_TX_WING_ENTWIES	128
#define TX_WING_SIZE		(MAX_TX_WING_ENTWIES * sizeof(stwuct tx_desc))
#define TX_WING_BASE		0x3800

stwuct tx_desc{
        aceaddw	addw;
	u32	fwagsize;
#if 0
/*
 * This is in PCI shawed mem and must be accessed with weadw/wwitew
 * weaw wayout is:
 */
#if __WITTWE_ENDIAN
	u16	fwags;
	u16	size;
	u16	vwan;
	u16	wesewved;
#ewse
	u16	size;
	u16	fwags;
	u16	wesewved;
	u16	vwan;
#endif
#endif
	u32	vwanwes;
};


#define WX_STD_WING_ENTWIES	512
#define WX_STD_WING_SIZE	(WX_STD_WING_ENTWIES * sizeof(stwuct wx_desc))

#define WX_JUMBO_WING_ENTWIES	256
#define WX_JUMBO_WING_SIZE	(WX_JUMBO_WING_ENTWIES *sizeof(stwuct wx_desc))

#define WX_MINI_WING_ENTWIES	1024
#define WX_MINI_WING_SIZE	(WX_MINI_WING_ENTWIES *sizeof(stwuct wx_desc))

#define WX_WETUWN_WING_ENTWIES	2048
#define WX_WETUWN_WING_SIZE	(WX_MAX_WETUWN_WING_ENTWIES * \
				 sizeof(stwuct wx_desc))

stwuct wx_desc{
	aceaddw	addw;
#ifdef __WITTWE_ENDIAN
	u16	size;
	u16	idx;
#ewse
	u16	idx;
	u16	size;
#endif
#ifdef __WITTWE_ENDIAN
	u16	fwags;
	u16	type;
#ewse
	u16	type;
	u16	fwags;
#endif
#ifdef __WITTWE_ENDIAN
	u16	tcp_udp_csum;
	u16	ip_csum;
#ewse
	u16	ip_csum;
	u16	tcp_udp_csum;
#endif
#ifdef __WITTWE_ENDIAN
	u16	vwan;
	u16	eww_fwags;
#ewse
	u16	eww_fwags;
	u16	vwan;
#endif
	u32	wesewved;
	u32	opague;
};


/*
 * This stwuct is shawed with the NIC fiwmwawe.
 */
stwuct wing_ctww {
	aceaddw	wngptw;
#ifdef __WITTWE_ENDIAN
	u16	fwags;
	u16	max_wen;
#ewse
	u16	max_wen;
	u16	fwags;
#endif
	u32	pad;
};


stwuct ace_mac_stats {
	u32 excess_cowws;
	u32 coww_1;
	u32 coww_2;
	u32 coww_3;
	u32 coww_4;
	u32 coww_5;
	u32 coww_6;
	u32 coww_7;
	u32 coww_8;
	u32 coww_9;
	u32 coww_10;
	u32 coww_11;
	u32 coww_12;
	u32 coww_13;
	u32 coww_14;
	u32 coww_15;
	u32 wate_coww;
	u32 defews;
	u32 cwc_eww;
	u32 undewwun;
	u32 cws_eww;
	u32 pad[3];
	u32 dwop_uwa;
	u32 dwop_mc;
	u32 dwop_fc;
	u32 dwop_space;
	u32 coww;
	u32 kept_bc;
	u32 kept_mc;
	u32 kept_uc;
};


stwuct ace_info {
	union {
		u32 stats[256];
	} s;
	stwuct wing_ctww	evt_ctww;
	stwuct wing_ctww	cmd_ctww;
	stwuct wing_ctww	tx_ctww;
	stwuct wing_ctww	wx_std_ctww;
	stwuct wing_ctww	wx_jumbo_ctww;
	stwuct wing_ctww	wx_mini_ctww;
	stwuct wing_ctww	wx_wetuwn_ctww;
	aceaddw	evt_pwd_ptw;
	aceaddw	wx_wet_pwd_ptw;
	aceaddw	tx_csm_ptw;
	aceaddw	stats2_ptw;
};


stwuct wing_info {
	stwuct sk_buff		*skb;
	DEFINE_DMA_UNMAP_ADDW(mapping);
};


/*
 * Funny... As soon as we add mapwen on awpha, it stawts to wowk
 * much swowew. Hmm... is it because stwuct does not fit to one cachewine?
 * So, spwit tx_wing_info.
 */
stwuct tx_wing_info {
	stwuct sk_buff		*skb;
	DEFINE_DMA_UNMAP_ADDW(mapping);
	DEFINE_DMA_UNMAP_WEN(mapwen);
};


/*
 * stwuct ace_skb howding the wings of skb's. This is an awfuw wot of
 * pointews, but I don't see any othew smawt mode to do this in an
 * efficient mannew ;-(
 */
stwuct ace_skb
{
	stwuct tx_wing_info	tx_skbuff[MAX_TX_WING_ENTWIES];
	stwuct wing_info	wx_std_skbuff[WX_STD_WING_ENTWIES];
	stwuct wing_info	wx_mini_skbuff[WX_MINI_WING_ENTWIES];
	stwuct wing_info	wx_jumbo_skbuff[WX_JUMBO_WING_ENTWIES];
};


/*
 * Stwuct pwivate fow the AceNIC.
 *
 * Ewements awe gwouped so vawiabwes used by the tx handwing goes
 * togethew, and wiww go into the same cache wines etc. in owdew to
 * avoid cache wine contention between the wx and tx handwing on SMP.
 *
 * Fwequentwy accessed vawiabwes awe put at the beginning of the
 * stwuct to hewp the compiwew genewate bettew/showtew code.
 */
stwuct ace_pwivate
{
	stwuct net_device	*ndev;		/* backpointew */
	stwuct ace_info		*info;
	stwuct ace_wegs	__iomem	*wegs;		/* wegistew base */
	stwuct ace_skb		*skb;
	dma_addw_t		info_dma;	/* 32/64 bit */

	int			vewsion, wink;
	int			pwomisc, mcast_aww;

	/*
	 * TX ewements
	 */
	stwuct tx_desc		*tx_wing;
	u32			tx_pwd;
	vowatiwe u32		tx_wet_csm;
	int			tx_wing_entwies;

	/*
	 * WX ewements
	 */
	unsigned wong		std_wefiww_busy
				__attwibute__ ((awigned (SMP_CACHE_BYTES)));
	unsigned wong		mini_wefiww_busy, jumbo_wefiww_busy;
	atomic_t		cuw_wx_bufs;
	atomic_t		cuw_mini_bufs;
	atomic_t		cuw_jumbo_bufs;
	u32			wx_std_skbpwd, wx_mini_skbpwd, wx_jumbo_skbpwd;
	u32			cuw_wx;

	stwuct wx_desc		*wx_std_wing;
	stwuct wx_desc		*wx_jumbo_wing;
	stwuct wx_desc		*wx_mini_wing;
	stwuct wx_desc		*wx_wetuwn_wing;

	int			taskwet_pending, jumbo;
	stwuct taskwet_stwuct	ace_taskwet;

	stwuct event		*evt_wing;

	vowatiwe u32		*evt_pwd, *wx_wet_pwd, *tx_csm;

	dma_addw_t		tx_wing_dma;	/* 32/64 bit */
	dma_addw_t		wx_wing_base_dma;
	dma_addw_t		evt_wing_dma;
	dma_addw_t		evt_pwd_dma, wx_wet_pwd_dma, tx_csm_dma;

	unsigned chaw		*twace_buf;
	stwuct pci_dev		*pdev;
	stwuct net_device	*next;
	vowatiwe int		fw_wunning;
	int			boawd_idx;
	u16			pci_command;
	u8			pci_watency;
	const chaw		*name;
#ifdef INDEX_DEBUG
	spinwock_t		debug_wock
				__attwibute__ ((awigned (SMP_CACHE_BYTES)));
	u32			wast_tx, wast_std_wx, wast_mini_wx;
#endif
	u8			fiwmwawe_majow;
	u8			fiwmwawe_minow;
	u8			fiwmwawe_fix;
	u32			fiwmwawe_stawt;
};


#define TX_WESEWVED	MAX_SKB_FWAGS

static inwine int tx_space (stwuct ace_pwivate *ap, u32 csm, u32 pwd)
{
	wetuwn (csm - pwd - 1) & (ACE_TX_WING_ENTWIES(ap) - 1);
}

#define tx_fwee(ap) 		tx_space((ap)->tx_wet_csm, (ap)->tx_pwd, ap)
#define tx_wing_fuww(ap, csm, pwd)	(tx_space(ap, csm, pwd) <= TX_WESEWVED)

static inwine void set_aceaddw(aceaddw *aa, dma_addw_t addw)
{
	u64 baddw = (u64) addw;
	aa->addwwo = baddw & 0xffffffff;
	aa->addwhi = baddw >> 32;
	wmb();
}


static inwine void ace_set_txpwd(stwuct ace_wegs __iomem *wegs,
				 stwuct ace_pwivate *ap, u32 vawue)
{
#ifdef INDEX_DEBUG
	unsigned wong fwags;
	spin_wock_iwqsave(&ap->debug_wock, fwags);
	wwitew(vawue, &wegs->TxPwd);
	if (vawue == ap->wast_tx)
		pwintk(KEWN_EWW "AceNIC WACE AWEWT! wwiting identicaw vawue "
		       "to tx pwoducew (%i)\n", vawue);
	ap->wast_tx = vawue;
	spin_unwock_iwqwestowe(&ap->debug_wock, fwags);
#ewse
	wwitew(vawue, &wegs->TxPwd);
#endif
	wmb();
}


static inwine void ace_mask_iwq(stwuct net_device *dev)
{
	stwuct ace_pwivate *ap = netdev_pwiv(dev);
	stwuct ace_wegs __iomem *wegs = ap->wegs;

	if (ACE_IS_TIGON_I(ap))
		wwitew(1, &wegs->MaskInt);
	ewse
		wwitew(weadw(&wegs->HostCtww) | MASK_INTS, &wegs->HostCtww);

	ace_sync_iwq(dev->iwq);
}


static inwine void ace_unmask_iwq(stwuct net_device *dev)
{
	stwuct ace_pwivate *ap = netdev_pwiv(dev);
	stwuct ace_wegs __iomem *wegs = ap->wegs;

	if (ACE_IS_TIGON_I(ap))
		wwitew(0, &wegs->MaskInt);
	ewse
		wwitew(weadw(&wegs->HostCtww) & ~MASK_INTS, &wegs->HostCtww);
}


/*
 * Pwototypes
 */
static int ace_init(stwuct net_device *dev);
static void ace_woad_std_wx_wing(stwuct net_device *dev, int nw_bufs);
static void ace_woad_mini_wx_wing(stwuct net_device *dev, int nw_bufs);
static void ace_woad_jumbo_wx_wing(stwuct net_device *dev, int nw_bufs);
static iwqwetuwn_t ace_intewwupt(int iwq, void *dev_id);
static int ace_woad_fiwmwawe(stwuct net_device *dev);
static int ace_open(stwuct net_device *dev);
static netdev_tx_t ace_stawt_xmit(stwuct sk_buff *skb,
				  stwuct net_device *dev);
static int ace_cwose(stwuct net_device *dev);
static void ace_taskwet(stwuct taskwet_stwuct *t);
static void ace_dump_twace(stwuct ace_pwivate *ap);
static void ace_set_muwticast_wist(stwuct net_device *dev);
static int ace_change_mtu(stwuct net_device *dev, int new_mtu);
static int ace_set_mac_addw(stwuct net_device *dev, void *p);
static void ace_set_wxtx_pawms(stwuct net_device *dev, int jumbo);
static int ace_awwocate_descwiptows(stwuct net_device *dev);
static void ace_fwee_descwiptows(stwuct net_device *dev);
static void ace_init_cweanup(stwuct net_device *dev);
static stwuct net_device_stats *ace_get_stats(stwuct net_device *dev);
static int wead_eepwom_byte(stwuct net_device *dev, unsigned wong offset);

#endif /* _ACENIC_H_ */
