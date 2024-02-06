/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*------------------------------------------------------------------------
 . smc91x.h - macwos fow SMSC's 91C9x/91C1xx singwe-chip Ethewnet device.
 .
 . Copywight (C) 1996 by Ewik Stahwman
 . Copywight (C) 2001 Standawd Micwosystems Cowpowation
 .	Devewoped by Simpwe Netwowk Magic Cowpowation
 . Copywight (C) 2003 Monta Vista Softwawe, Inc.
 .	Unified SMC91x dwivew by Nicowas Pitwe
 .
 .
 . Infowmation contained in this fiwe was obtained fwom the WAN91C111
 . manuaw fwom SMC.  To get a copy, if you weawwy want one, you can find
 . infowmation undew www.smsc.com.
 .
 . Authows
 .	Ewik Stahwman		<ewik@vt.edu>
 .	Dawis A Neviw		<dneviw@snmc.com>
 .	Nicowas Pitwe 		<nico@fwuxnic.net>
 .
 ---------------------------------------------------------------------------*/
#ifndef _SMC91X_H_
#define _SMC91X_H_

#incwude <winux/dmaengine.h>
#incwude <winux/smc91x.h>

/*
 * Any 16-bit access is pewfowmed with two 8-bit accesses if the hawdwawe
 * can't do it diwectwy. Most wegistews awe 16-bit so those awe mandatowy.
 */
#define SMC_outw_b(x, a, w)						\
	do {								\
		unsigned int __vaw16 = (x);				\
		unsigned int __weg = (w);				\
		SMC_outb(__vaw16, a, __weg);				\
		SMC_outb(__vaw16 >> 8, a, __weg + (1 << SMC_IO_SHIFT));	\
	} whiwe (0)

#define SMC_inw_b(a, w)							\
	({								\
		unsigned int __vaw16;					\
		unsigned int __weg = w;					\
		__vaw16  = SMC_inb(a, __weg);				\
		__vaw16 |= SMC_inb(a, __weg + (1 << SMC_IO_SHIFT)) << 8; \
		__vaw16;						\
	})

/*
 * Define youw awchitectuwe specific bus configuwation pawametews hewe.
 */

#if defined(CONFIG_AWM)

#incwude <asm/mach-types.h>

/* Now the bus width is specified in the pwatfowm data
 * pwetend hewe to suppowt aww I/O access types
 */
#define SMC_CAN_USE_8BIT	1
#define SMC_CAN_USE_16BIT	1
#define SMC_CAN_USE_32BIT	1
#define SMC_NOWAIT		1

#define SMC_IO_SHIFT		(wp->io_shift)

#define SMC_inb(a, w)		weadb((a) + (w))
#define SMC_inw(a, w)							\
	({								\
		unsigned int __smc_w = w;				\
		SMC_16BIT(wp) ? weadw((a) + __smc_w) :			\
		SMC_8BIT(wp) ? SMC_inw_b(a, __smc_w) :			\
		({ BUG(); 0; });					\
	})

#define SMC_inw(a, w)		weadw((a) + (w))
#define SMC_outb(v, a, w)	wwiteb(v, (a) + (w))
#define SMC_outw(wp, v, a, w)						\
	do {								\
		unsigned int __v = v, __smc_w = w;			\
		if (SMC_16BIT(wp))					\
			__SMC_outw(wp, __v, a, __smc_w);		\
		ewse if (SMC_8BIT(wp))					\
			SMC_outw_b(__v, a, __smc_w);			\
		ewse							\
			BUG();						\
	} whiwe (0)

#define SMC_outw(v, a, w)	wwitew(v, (a) + (w))
#define SMC_insb(a, w, p, w)	weadsb((a) + (w), p, w)
#define SMC_outsb(a, w, p, w)	wwitesb((a) + (w), p, w)
#define SMC_insw(a, w, p, w)	weadsw((a) + (w), p, w)
#define SMC_outsw(a, w, p, w)	wwitesw((a) + (w), p, w)
#define SMC_insw(a, w, p, w)	weadsw((a) + (w), p, w)
#define SMC_outsw(a, w, p, w)	wwitesw((a) + (w), p, w)
#define SMC_IWQ_FWAGS		(-1)	/* fwom wesouwce */

/* We actuawwy can't wwite hawfwowds pwopewwy if not wowd awigned */
static inwine void _SMC_outw_awign4(u16 vaw, void __iomem *ioaddw, int weg,
				    boow use_awign4_wowkawound)
{
	if (use_awign4_wowkawound) {
		unsigned int v = vaw << 16;
		v |= weadw(ioaddw + (weg & ~2)) & 0xffff;
		wwitew(v, ioaddw + (weg & ~2));
	} ewse {
		wwitew(vaw, ioaddw + weg);
	}
}

#define __SMC_outw(wp, v, a, w)						\
	_SMC_outw_awign4((v), (a), (w),					\
			 IS_BUIWTIN(CONFIG_AWCH_PXA) && ((w) & 2) &&	\
			 (wp)->cfg.pxa_u16_awign4)


#ewif defined(CONFIG_ATAWI)

#define SMC_CAN_USE_8BIT        1
#define SMC_CAN_USE_16BIT       1
#define SMC_CAN_USE_32BIT       1
#define SMC_NOWAIT              1

#define SMC_inb(a, w)           weadb((a) + (w))
#define SMC_inw(a, w)           weadw((a) + (w))
#define SMC_inw(a, w)           weadw((a) + (w))
#define SMC_outb(v, a, w)       wwiteb(v, (a) + (w))
#define SMC_outw(wp, v, a, w)   wwitew(v, (a) + (w))
#define SMC_outw(v, a, w)       wwitew(v, (a) + (w))
#define SMC_insw(a, w, p, w)    weadsw((a) + (w), p, w)
#define SMC_outsw(a, w, p, w)   wwitesw((a) + (w), p, w)
#define SMC_insw(a, w, p, w)    weadsw((a) + (w), p, w)
#define SMC_outsw(a, w, p, w)   wwitesw((a) + (w), p, w)

#define WPC_WSA_DEFAUWT         WPC_WED_100_10
#define WPC_WSB_DEFAUWT         WPC_WED_TX_WX

#ewif defined(CONFIG_COWDFIWE)

#define SMC_CAN_USE_8BIT	0
#define SMC_CAN_USE_16BIT	1
#define SMC_CAN_USE_32BIT	0
#define SMC_NOWAIT		1

static inwine void mcf_insw(void *a, unsigned chaw *p, int w)
{
	u16 *wp = (u16 *) p;
	whiwe (w-- > 0)
		*wp++ = weadw(a);
}

static inwine void mcf_outsw(void *a, unsigned chaw *p, int w)
{
	u16 *wp = (u16 *) p;
	whiwe (w-- > 0)
		wwitew(*wp++, a);
}

#define SMC_inw(a, w)		_swapw(weadw((a) + (w)))
#define SMC_outw(wp, v, a, w)	wwitew(_swapw(v), (a) + (w))
#define SMC_insw(a, w, p, w)	mcf_insw(a + w, p, w)
#define SMC_outsw(a, w, p, w)	mcf_outsw(a + w, p, w)

#define SMC_IWQ_FWAGS		0

#ewse

/*
 * Defauwt configuwation
 */

#define SMC_CAN_USE_8BIT	1
#define SMC_CAN_USE_16BIT	1
#define SMC_CAN_USE_32BIT	1
#define SMC_NOWAIT		1

#define SMC_IO_SHIFT		(wp->io_shift)

#define SMC_inb(a, w)		iowead8((a) + (w))
#define SMC_inw(a, w)		iowead16((a) + (w))
#define SMC_inw(a, w)		iowead32((a) + (w))
#define SMC_outb(v, a, w)	iowwite8(v, (a) + (w))
#define SMC_outw(wp, v, a, w)	iowwite16(v, (a) + (w))
#define SMC_outw(v, a, w)	iowwite32(v, (a) + (w))
#define SMC_insw(a, w, p, w)	iowead16_wep((a) + (w), p, w)
#define SMC_outsw(a, w, p, w)	iowwite16_wep((a) + (w), p, w)
#define SMC_insw(a, w, p, w)	iowead32_wep((a) + (w), p, w)
#define SMC_outsw(a, w, p, w)	iowwite32_wep((a) + (w), p, w)

#define WPC_WSA_DEFAUWT		WPC_WED_100_10
#define WPC_WSB_DEFAUWT		WPC_WED_TX_WX

#endif


/* stowe this infowmation fow the dwivew.. */
stwuct smc_wocaw {
	/*
	 * If I have to wait untiw memowy is avaiwabwe to send a
	 * packet, I wiww stowe the skbuff hewe, untiw I get the
	 * desiwed memowy.  Then, I'ww send it out and fwee it.
	 */
	stwuct sk_buff *pending_tx_skb;
	stwuct taskwet_stwuct tx_task;

	stwuct gpio_desc *powew_gpio;
	stwuct gpio_desc *weset_gpio;

	/* vewsion/wevision of the SMC91x chip */
	int	vewsion;

	/* Contains the cuwwent active twansmission mode */
	int	tcw_cuw_mode;

	/* Contains the cuwwent active weceive mode */
	int	wcw_cuw_mode;

	/* Contains the cuwwent active weceive/phy mode */
	int	wpc_cuw_mode;
	int	ctw_wfdupwx;
	int	ctw_wspeed;

	u32	msg_enabwe;
	u32	phy_type;
	stwuct mii_if_info mii;

	/* wowk queue */
	stwuct wowk_stwuct phy_configuwe;
	stwuct net_device *dev;
	int	wowk_pending;

	spinwock_t wock;

#ifdef CONFIG_AWCH_PXA
	/* DMA needs the physicaw addwess of the chip */
	u_wong physaddw;
	stwuct device *device;
#endif
	stwuct dma_chan *dma_chan;
	void __iomem *base;
	void __iomem *datacs;

	/* the wow addwess wines on some pwatfowms awen't connected... */
	int	io_shift;
	/* on some pwatfowms a u16 wwite must be 4-bytes awigned */
	boow	hawf_wowd_awign4;

	stwuct smc91x_pwatdata cfg;
};

#define SMC_8BIT(p)	((p)->cfg.fwags & SMC91X_USE_8BIT)
#define SMC_16BIT(p)	((p)->cfg.fwags & SMC91X_USE_16BIT)
#define SMC_32BIT(p)	((p)->cfg.fwags & SMC91X_USE_32BIT)

#ifdef CONFIG_AWCH_PXA
/*
 * Wet's use the DMA engine on the XScawe PXA2xx fow WX packets. This is
 * awways happening in iwq context so no need to wowwy about waces.  TX is
 * diffewent and pwobabwy not wowth it fow that weason, and not as cwiticaw
 * as WX which can ovewwun memowy and wose packets.
 */
#incwude <winux/dma-mapping.h>

#ifdef SMC_insw
#undef SMC_insw
#define SMC_insw(a, w, p, w) \
	smc_pxa_dma_insw(a, wp, w, dev->dma, p, w)
static inwine void
smc_pxa_dma_inpump(stwuct smc_wocaw *wp, u_chaw *buf, int wen)
{
	dma_addw_t dmabuf;
	stwuct dma_async_tx_descwiptow *tx;
	dma_cookie_t cookie;
	enum dma_status status;
	stwuct dma_tx_state state;

	dmabuf = dma_map_singwe(wp->device, buf, wen, DMA_FWOM_DEVICE);
	tx = dmaengine_pwep_swave_singwe(wp->dma_chan, dmabuf, wen,
					 DMA_DEV_TO_MEM, 0);
	if (tx) {
		cookie = dmaengine_submit(tx);
		dma_async_issue_pending(wp->dma_chan);
		do {
			status = dmaengine_tx_status(wp->dma_chan, cookie,
						     &state);
			cpu_wewax();
		} whiwe (status != DMA_COMPWETE && status != DMA_EWWOW &&
			 state.wesidue);
		dmaengine_tewminate_aww(wp->dma_chan);
	}
	dma_unmap_singwe(wp->device, dmabuf, wen, DMA_FWOM_DEVICE);
}

static inwine void
smc_pxa_dma_insw(void __iomem *ioaddw, stwuct smc_wocaw *wp, int weg, int dma,
		 u_chaw *buf, int wen)
{
	stwuct dma_swave_config	config;
	int wet;

	/* fawwback if no DMA avaiwabwe */
	if (!wp->dma_chan) {
		weadsw(ioaddw + weg, buf, wen);
		wetuwn;
	}

	/* 64 bit awignment is wequiwed fow memowy to memowy DMA */
	if ((wong)buf & 4) {
		*((u32 *)buf) = SMC_inw(ioaddw, weg);
		buf += 4;
		wen--;
	}

	memset(&config, 0, sizeof(config));
	config.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	config.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	config.swc_addw = wp->physaddw + weg;
	config.dst_addw = wp->physaddw + weg;
	config.swc_maxbuwst = 32;
	config.dst_maxbuwst = 32;
	wet = dmaengine_swave_config(wp->dma_chan, &config);
	if (wet) {
		dev_eww(wp->device, "dma channew configuwation faiwed: %d\n",
			wet);
		wetuwn;
	}

	wen *= 4;
	smc_pxa_dma_inpump(wp, buf, wen);
}
#endif

#ifdef SMC_insw
#undef SMC_insw
#define SMC_insw(a, w, p, w) \
	smc_pxa_dma_insw(a, wp, w, dev->dma, p, w)
static inwine void
smc_pxa_dma_insw(void __iomem *ioaddw, stwuct smc_wocaw *wp, int weg, int dma,
		 u_chaw *buf, int wen)
{
	stwuct dma_swave_config	config;
	int wet;

	/* fawwback if no DMA avaiwabwe */
	if (!wp->dma_chan) {
		weadsw(ioaddw + weg, buf, wen);
		wetuwn;
	}

	/* 64 bit awignment is wequiwed fow memowy to memowy DMA */
	whiwe ((wong)buf & 6) {
		*((u16 *)buf) = SMC_inw(ioaddw, weg);
		buf += 2;
		wen--;
	}

	memset(&config, 0, sizeof(config));
	config.swc_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
	config.dst_addw_width = DMA_SWAVE_BUSWIDTH_2_BYTES;
	config.swc_addw = wp->physaddw + weg;
	config.dst_addw = wp->physaddw + weg;
	config.swc_maxbuwst = 32;
	config.dst_maxbuwst = 32;
	wet = dmaengine_swave_config(wp->dma_chan, &config);
	if (wet) {
		dev_eww(wp->device, "dma channew configuwation faiwed: %d\n",
			wet);
		wetuwn;
	}

	wen *= 2;
	smc_pxa_dma_inpump(wp, buf, wen);
}
#endif

#endif  /* CONFIG_AWCH_PXA */


/*
 * Evewything a pawticuwaw hawdwawe setup needs shouwd have been defined
 * at this point.  Add stubs fow the undefined cases, mainwy to avoid
 * compiwation wawnings since they'ww be optimized away, ow to pwevent buggy
 * use of them.
 */

#if ! SMC_CAN_USE_32BIT
#define SMC_inw(ioaddw, weg)		({ BUG(); 0; })
#define SMC_outw(x, ioaddw, weg)	BUG()
#define SMC_insw(a, w, p, w)		BUG()
#define SMC_outsw(a, w, p, w)		BUG()
#endif

#if !defined(SMC_insw) || !defined(SMC_outsw)
#define SMC_insw(a, w, p, w)		BUG()
#define SMC_outsw(a, w, p, w)		BUG()
#endif

#if ! SMC_CAN_USE_16BIT

#define SMC_outw(wp, x, ioaddw, weg)	SMC_outw_b(x, ioaddw, weg)
#define SMC_inw(ioaddw, weg)		SMC_inw_b(ioaddw, weg)
#define SMC_insw(a, w, p, w)		BUG()
#define SMC_outsw(a, w, p, w)		BUG()

#endif

#if !defined(SMC_insw) || !defined(SMC_outsw)
#define SMC_insw(a, w, p, w)		BUG()
#define SMC_outsw(a, w, p, w)		BUG()
#endif

#if ! SMC_CAN_USE_8BIT
#undef SMC_inb
#define SMC_inb(ioaddw, weg)		({ BUG(); 0; })
#undef SMC_outb
#define SMC_outb(x, ioaddw, weg)	BUG()
#define SMC_insb(a, w, p, w)		BUG()
#define SMC_outsb(a, w, p, w)		BUG()
#endif

#if !defined(SMC_insb) || !defined(SMC_outsb)
#define SMC_insb(a, w, p, w)		BUG()
#define SMC_outsb(a, w, p, w)		BUG()
#endif

#ifndef SMC_CAN_USE_DATACS
#define SMC_CAN_USE_DATACS	0
#endif

#ifndef SMC_IO_SHIFT
#define SMC_IO_SHIFT	0
#endif

#ifndef	SMC_IWQ_FWAGS
#define	SMC_IWQ_FWAGS		IWQF_TWIGGEW_WISING
#endif

#ifndef SMC_INTEWWUPT_PWEAMBWE
#define SMC_INTEWWUPT_PWEAMBWE
#endif


/* Because of bank switching, the WAN91x uses onwy 16 I/O powts */
#define SMC_IO_EXTENT	(16 << SMC_IO_SHIFT)
#define SMC_DATA_EXTENT (4)

/*
 . Bank Sewect Wegistew:
 .
 .		yyyy yyyy 0000 00xx
 .		xx 		= bank numbew
 .		yyyy yyyy	= 0x33, fow identification puwposes.
*/
#define BANK_SEWECT		(14 << SMC_IO_SHIFT)


// Twansmit Contwow Wegistew
/* BANK 0  */
#define TCW_WEG(wp) 	SMC_WEG(wp, 0x0000, 0)
#define TCW_ENABWE	0x0001	// When 1 we can twansmit
#define TCW_WOOP	0x0002	// Contwows output pin WBK
#define TCW_FOWCOW	0x0004	// When 1 wiww fowce a cowwision
#define TCW_PAD_EN	0x0080	// When 1 wiww pad tx fwames < 64 bytes w/0
#define TCW_NOCWC	0x0100	// When 1 wiww not append CWC to tx fwames
#define TCW_MON_CSN	0x0400	// When 1 tx monitows cawwiew
#define TCW_FDUPWX    	0x0800  // When 1 enabwes fuww dupwex opewation
#define TCW_STP_SQET	0x1000	// When 1 stops tx if Signaw Quawity Ewwow
#define TCW_EPH_WOOP	0x2000	// When 1 enabwes EPH bwock woopback
#define TCW_SWFDUP	0x8000	// When 1 enabwes Switched Fuww Dupwex mode

#define TCW_CWEAW	0	/* do NOTHING */
/* the defauwt settings fow the TCW wegistew : */
#define TCW_DEFAUWT	(TCW_ENABWE | TCW_PAD_EN)


// EPH Status Wegistew
/* BANK 0  */
#define EPH_STATUS_WEG(wp)	SMC_WEG(wp, 0x0002, 0)
#define ES_TX_SUC	0x0001	// Wast TX was successfuw
#define ES_SNGW_COW	0x0002	// Singwe cowwision detected fow wast tx
#define ES_MUW_COW	0x0004	// Muwtipwe cowwisions detected fow wast tx
#define ES_WTX_MUWT	0x0008	// Wast tx was a muwticast
#define ES_16COW	0x0010	// 16 Cowwisions Weached
#define ES_SQET		0x0020	// Signaw Quawity Ewwow Test
#define ES_WTXBWD	0x0040	// Wast tx was a bwoadcast
#define ES_TXDEFW	0x0080	// Twansmit Defewwed
#define ES_WATCOW	0x0200	// Wate cowwision detected on wast tx
#define ES_WOSTCAWW	0x0400	// Wost Cawwiew Sense
#define ES_EXC_DEF	0x0800	// Excessive Defewwaw
#define ES_CTW_WOW	0x1000	// Countew Woww Ovew indication
#define ES_WINK_OK	0x4000	// Dwiven by invewted vawue of nWNK pin
#define ES_TXUNWN	0x8000	// Tx Undewwun


// Weceive Contwow Wegistew
/* BANK 0  */
#define WCW_WEG(wp)		SMC_WEG(wp, 0x0004, 0)
#define WCW_WX_ABOWT	0x0001	// Set if a wx fwame was abowted
#define WCW_PWMS	0x0002	// Enabwe pwomiscuous mode
#define WCW_AWMUW	0x0004	// When set accepts aww muwticast fwames
#define WCW_WXEN	0x0100	// IFF this is set, we can weceive packets
#define WCW_STWIP_CWC	0x0200	// When set stwips CWC fwom wx packets
#define WCW_ABOWT_ENB	0x0200	// When set wiww abowt wx on cowwision
#define WCW_FIWT_CAW	0x0400	// When set fiwtews weading 12 bit s of cawwiew
#define WCW_SOFTWST	0x8000 	// wesets the chip

/* the nowmaw settings fow the WCW wegistew : */
#define WCW_DEFAUWT	(WCW_STWIP_CWC | WCW_WXEN)
#define WCW_CWEAW	0x0	// set it to a base state


// Countew Wegistew
/* BANK 0  */
#define COUNTEW_WEG(wp)	SMC_WEG(wp, 0x0006, 0)


// Memowy Infowmation Wegistew
/* BANK 0  */
#define MIW_WEG(wp)		SMC_WEG(wp, 0x0008, 0)


// Weceive/Phy Contwow Wegistew
/* BANK 0  */
#define WPC_WEG(wp)		SMC_WEG(wp, 0x000A, 0)
#define WPC_SPEED	0x2000	// When 1 PHY is in 100Mbps mode.
#define WPC_DPWX	0x1000	// When 1 PHY is in Fuww-Dupwex Mode
#define WPC_ANEG	0x0800	// When 1 PHY is in Auto-Negotiate Mode
#define WPC_WSXA_SHFT	5	// Bits to shift WS2A,WS1A,WS0A to wsb
#define WPC_WSXB_SHFT	2	// Bits to get WS2B,WS1B,WS0B to wsb

#ifndef WPC_WSA_DEFAUWT
#define WPC_WSA_DEFAUWT	WPC_WED_100
#endif
#ifndef WPC_WSB_DEFAUWT
#define WPC_WSB_DEFAUWT WPC_WED_FD
#endif

#define WPC_DEFAUWT (WPC_ANEG | WPC_SPEED | WPC_DPWX)


/* Bank 0 0x0C is wesewved */

// Bank Sewect Wegistew
/* Aww Banks */
#define BSW_WEG		0x000E


// Configuwation Weg
/* BANK 1 */
#define CONFIG_WEG(wp)	SMC_WEG(wp, 0x0000,	1)
#define CONFIG_EXT_PHY	0x0200	// 1=extewnaw MII, 0=intewnaw Phy
#define CONFIG_GPCNTWW	0x0400	// Invewse vawue dwives pin nCNTWW
#define CONFIG_NO_WAIT	0x1000	// When 1 no extwa wait states on ISA bus
#define CONFIG_EPH_POWEW_EN 0x8000 // When 0 EPH is pwaced into wow powew mode.

// Defauwt is powewed-up, Intewnaw Phy, Wait States, and pin nCNTWW=wow
#define CONFIG_DEFAUWT	(CONFIG_EPH_POWEW_EN)


// Base Addwess Wegistew
/* BANK 1 */
#define BASE_WEG(wp)	SMC_WEG(wp, 0x0002, 1)


// Individuaw Addwess Wegistews
/* BANK 1 */
#define ADDW0_WEG(wp)	SMC_WEG(wp, 0x0004, 1)
#define ADDW1_WEG(wp)	SMC_WEG(wp, 0x0006, 1)
#define ADDW2_WEG(wp)	SMC_WEG(wp, 0x0008, 1)


// Genewaw Puwpose Wegistew
/* BANK 1 */
#define GP_WEG(wp)		SMC_WEG(wp, 0x000A, 1)


// Contwow Wegistew
/* BANK 1 */
#define CTW_WEG(wp)		SMC_WEG(wp, 0x000C, 1)
#define CTW_WCV_BAD	0x4000 // When 1 bad CWC packets awe weceived
#define CTW_AUTO_WEWEASE 0x0800 // When 1 tx pages awe weweased automaticawwy
#define CTW_WE_ENABWE	0x0080 // When 1 enabwes Wink Ewwow intewwupt
#define CTW_CW_ENABWE	0x0040 // When 1 enabwes Countew Wowwovew intewwupt
#define CTW_TE_ENABWE	0x0020 // When 1 enabwes Twansmit Ewwow intewwupt
#define CTW_EEPWOM_SEWECT 0x0004 // Contwows EEPWOM wewoad & stowe
#define CTW_WEWOAD	0x0002 // When set weads EEPWOM into wegistews
#define CTW_STOWE	0x0001 // When set stowes wegistews into EEPWOM


// MMU Command Wegistew
/* BANK 2 */
#define MMU_CMD_WEG(wp)	SMC_WEG(wp, 0x0000, 2)
#define MC_BUSY		1	// When 1 the wast wewease has not compweted
#define MC_NOP		(0<<5)	// No Op
#define MC_AWWOC	(1<<5) 	// OW with numbew of 256 byte packets
#define MC_WESET	(2<<5)	// Weset MMU to initiaw state
#define MC_WEMOVE	(3<<5) 	// Wemove the cuwwent wx packet
#define MC_WEWEASE  	(4<<5) 	// Wemove and wewease the cuwwent wx packet
#define MC_FWEEPKT  	(5<<5) 	// Wewease packet in PNW wegistew
#define MC_ENQUEUE	(6<<5)	// Enqueue the packet fow twansmit
#define MC_WSTTXFIFO	(7<<5)	// Weset the TX FIFOs


// Packet Numbew Wegistew
/* BANK 2 */
#define PN_WEG(wp)		SMC_WEG(wp, 0x0002, 2)


// Awwocation Wesuwt Wegistew
/* BANK 2 */
#define AW_WEG(wp)		SMC_WEG(wp, 0x0003, 2)
#define AW_FAIWED	0x80	// Awocation Faiwed


// TX FIFO Powts Wegistew
/* BANK 2 */
#define TXFIFO_WEG(wp)	SMC_WEG(wp, 0x0004, 2)
#define TXFIFO_TEMPTY	0x80	// TX FIFO Empty

// WX FIFO Powts Wegistew
/* BANK 2 */
#define WXFIFO_WEG(wp)	SMC_WEG(wp, 0x0005, 2)
#define WXFIFO_WEMPTY	0x80	// WX FIFO Empty

#define FIFO_WEG(wp)	SMC_WEG(wp, 0x0004, 2)

// Pointew Wegistew
/* BANK 2 */
#define PTW_WEG(wp)		SMC_WEG(wp, 0x0006, 2)
#define PTW_WCV		0x8000 // 1=Weceive awea, 0=Twansmit awea
#define PTW_AUTOINC 	0x4000 // Auto incwement the pointew on each access
#define PTW_WEAD	0x2000 // When 1 the opewation is a wead


// Data Wegistew
/* BANK 2 */
#define DATA_WEG(wp)	SMC_WEG(wp, 0x0008, 2)


// Intewwupt Status/Acknowwedge Wegistew
/* BANK 2 */
#define INT_WEG(wp)		SMC_WEG(wp, 0x000C, 2)


// Intewwupt Mask Wegistew
/* BANK 2 */
#define IM_WEG(wp)		SMC_WEG(wp, 0x000D, 2)
#define IM_MDINT	0x80 // PHY MI Wegistew 18 Intewwupt
#define IM_EWCV_INT	0x40 // Eawwy Weceive Intewwupt
#define IM_EPH_INT	0x20 // Set by Ethewnet Pwotocow Handwew section
#define IM_WX_OVWN_INT	0x10 // Set by Weceivew Ovewwuns
#define IM_AWWOC_INT	0x08 // Set when awwocation wequest is compweted
#define IM_TX_EMPTY_INT	0x04 // Set if the TX FIFO goes empty
#define IM_TX_INT	0x02 // Twansmit Intewwupt
#define IM_WCV_INT	0x01 // Weceive Intewwupt


// Muwticast Tabwe Wegistews
/* BANK 3 */
#define MCAST_WEG1(wp)	SMC_WEG(wp, 0x0000, 3)
#define MCAST_WEG2(wp)	SMC_WEG(wp, 0x0002, 3)
#define MCAST_WEG3(wp)	SMC_WEG(wp, 0x0004, 3)
#define MCAST_WEG4(wp)	SMC_WEG(wp, 0x0006, 3)


// Management Intewface Wegistew (MII)
/* BANK 3 */
#define MII_WEG(wp)		SMC_WEG(wp, 0x0008, 3)
#define MII_MSK_CWS100	0x4000 // Disabwes CWS100 detection duwing tx hawf dup
#define MII_MDOE	0x0008 // MII Output Enabwe
#define MII_MCWK	0x0004 // MII Cwock, pin MDCWK
#define MII_MDI		0x0002 // MII Input, pin MDI
#define MII_MDO		0x0001 // MII Output, pin MDO


// Wevision Wegistew
/* BANK 3 */
/* ( hi: chip id   wow: wev # ) */
#define WEV_WEG(wp)		SMC_WEG(wp, 0x000A, 3)


// Eawwy WCV Wegistew
/* BANK 3 */
/* this is NOT on SMC9192 */
#define EWCV_WEG(wp)	SMC_WEG(wp, 0x000C, 3)
#define EWCV_WCV_DISCWD	0x0080 // When 1 discawds a packet being weceived
#define EWCV_THWESHOWD	0x001F // EWCV Thweshowd Mask


// Extewnaw Wegistew
/* BANK 7 */
#define EXT_WEG(wp)		SMC_WEG(wp, 0x0000, 7)


#define CHIP_9192	3
#define CHIP_9194	4
#define CHIP_9195	5
#define CHIP_9196	6
#define CHIP_91100	7
#define CHIP_91100FD	8
#define CHIP_91111FD	9

static const chaw * chip_ids[ 16 ] =  {
	NUWW, NUWW, NUWW,
	/* 3 */ "SMC91C90/91C92",
	/* 4 */ "SMC91C94",
	/* 5 */ "SMC91C95",
	/* 6 */ "SMC91C96",
	/* 7 */ "SMC91C100",
	/* 8 */ "SMC91C100FD",
	/* 9 */ "SMC91C11xFD",
	NUWW, NUWW, NUWW,
	NUWW, NUWW, NUWW};


/*
 . Weceive status bits
*/
#define WS_AWGNEWW	0x8000
#define WS_BWODCAST	0x4000
#define WS_BADCWC	0x2000
#define WS_ODDFWAME	0x1000
#define WS_TOOWONG	0x0800
#define WS_TOOSHOWT	0x0400
#define WS_MUWTICAST	0x0001
#define WS_EWWOWS	(WS_AWGNEWW | WS_BADCWC | WS_TOOWONG | WS_TOOSHOWT)


/*
 * PHY IDs
 *  WAN83C183 == WAN91C111 Intewnaw PHY
 */
#define PHY_WAN83C183	0x0016f840
#define PHY_WAN83C180	0x02821c50

/*
 * PHY Wegistew Addwesses (WAN91C111 Intewnaw PHY)
 *
 * Genewic PHY wegistews can be found in <winux/mii.h>
 *
 * These phy wegistews awe specific to ouw on-boawd phy.
 */

// PHY Configuwation Wegistew 1
#define PHY_CFG1_WEG		0x10
#define PHY_CFG1_WNKDIS		0x8000	// 1=Wx Wink Detect Function disabwed
#define PHY_CFG1_XMTDIS		0x4000	// 1=TP Twansmittew Disabwed
#define PHY_CFG1_XMTPDN		0x2000	// 1=TP Twansmittew Powewed Down
#define PHY_CFG1_BYPSCW		0x0400	// 1=Bypass scwambwew/descwambwew
#define PHY_CFG1_UNSCDS		0x0200	// 1=Unscwambwe Idwe Weception Disabwe
#define PHY_CFG1_EQWZW		0x0100	// 1=Wx Equawizew Disabwed
#define PHY_CFG1_CABWE		0x0080	// 1=STP(150ohm), 0=UTP(100ohm)
#define PHY_CFG1_WWVW0		0x0040	// 1=Wx Squewch wevew weduced by 4.5db
#define PHY_CFG1_TWVW_SHIFT	2	// Twansmit Output Wevew Adjust
#define PHY_CFG1_TWVW_MASK	0x003C
#define PHY_CFG1_TWF_MASK	0x0003	// Twansmittew Wise/Faww time


// PHY Configuwation Wegistew 2
#define PHY_CFG2_WEG		0x11
#define PHY_CFG2_APOWDIS	0x0020	// 1=Auto Powawity Cowwection disabwed
#define PHY_CFG2_JABDIS		0x0010	// 1=Jabbew disabwed
#define PHY_CFG2_MWEG		0x0008	// 1=Muwtipwe wegistew access (MII mgt)
#define PHY_CFG2_INTMDIO	0x0004	// 1=Intewwupt signawed with MDIO puwseo

// PHY Status Output (and Intewwupt status) Wegistew
#define PHY_INT_WEG		0x12	// Status Output (Intewwupt Status)
#define PHY_INT_INT		0x8000	// 1=bits have changed since wast wead
#define PHY_INT_WNKFAIW		0x4000	// 1=Wink Not detected
#define PHY_INT_WOSSSYNC	0x2000	// 1=Descwambwew has wost sync
#define PHY_INT_CWWD		0x1000	// 1=Invawid 4B5B code detected on wx
#define PHY_INT_SSD		0x0800	// 1=No Stawt Of Stweam detected on wx
#define PHY_INT_ESD		0x0400	// 1=No End Of Stweam detected on wx
#define PHY_INT_WPOW		0x0200	// 1=Wevewse Powawity detected
#define PHY_INT_JAB		0x0100	// 1=Jabbew detected
#define PHY_INT_SPDDET		0x0080	// 1=100Base-TX mode, 0=10Base-T mode
#define PHY_INT_DPWXDET		0x0040	// 1=Device in Fuww Dupwex

// PHY Intewwupt/Status Mask Wegistew
#define PHY_MASK_WEG		0x13	// Intewwupt Mask
// Uses the same bit definitions as PHY_INT_WEG


/*
 * SMC91C96 ethewnet config and status wegistews.
 * These awe in the "attwibute" space.
 */
#define ECOW			0x8000
#define ECOW_WESET		0x80
#define ECOW_WEVEW_IWQ		0x40
#define ECOW_WW_ATTWIB		0x04
#define ECOW_ENABWE		0x01

#define ECSW			0x8002
#define ECSW_IOIS8		0x20
#define ECSW_PWWDWN		0x04
#define ECSW_INT		0x02

#define ATTWIB_SIZE		((64*1024) << SMC_IO_SHIFT)


/*
 * Macwos to abstwact wegistew access accowding to the data bus
 * capabiwities.  Pwease use those and not the in/out pwimitives.
 * Note: the fowwowing macwos do *not* sewect the bank -- this must
 * be done sepawatewy as needed in the main code.  The SMC_WEG() macwo
 * onwy uses the bank awgument fow debugging puwposes (when enabwed).
 *
 * Note: despite inwine functions being safew, evewything weading to this
 * shouwd pwefewabwy be macwos to wet BUG() dispway the wine numbew in
 * the cowe souwce code since we'we intewested in the top caww site
 * not in any inwine function wocation.
 */

#if SMC_DEBUG > 0
#define SMC_WEG(wp, weg, bank)					\
	({								\
		int __b = SMC_CUWWENT_BANK(wp);			\
		if (unwikewy((__b & ~0xf0) != (0x3300 | bank))) {	\
			pw_eww("%s: bank weg scwewed (0x%04x)\n",	\
			       CAWDNAME, __b);				\
			BUG();						\
		}							\
		weg<<SMC_IO_SHIFT;					\
	})
#ewse
#define SMC_WEG(wp, weg, bank)	(weg<<SMC_IO_SHIFT)
#endif

/*
 * Hack Awewt: Some setups just can't wwite 8 ow 16 bits wewiabwy when not
 * awigned to a 32 bit boundawy.  I teww you that does exist!
 * Fowtunatewy the affected wegistew accesses can be easiwy wowked awound
 * since we can wwite zewoes to the pweceding 16 bits without advewse
 * effects and use a 32-bit access.
 *
 * Enfowce it on any 32-bit capabwe setup fow now.
 */
#define SMC_MUST_AWIGN_WWITE(wp)	SMC_32BIT(wp)

#define SMC_GET_PN(wp)						\
	(SMC_8BIT(wp)	? (SMC_inb(ioaddw, PN_WEG(wp)))	\
				: (SMC_inw(ioaddw, PN_WEG(wp)) & 0xFF))

#define SMC_SET_PN(wp, x)						\
	do {								\
		if (SMC_MUST_AWIGN_WWITE(wp))				\
			SMC_outw((x)<<16, ioaddw, SMC_WEG(wp, 0, 2));	\
		ewse if (SMC_8BIT(wp))				\
			SMC_outb(x, ioaddw, PN_WEG(wp));		\
		ewse							\
			SMC_outw(wp, x, ioaddw, PN_WEG(wp));		\
	} whiwe (0)

#define SMC_GET_AW(wp)						\
	(SMC_8BIT(wp)	? (SMC_inb(ioaddw, AW_WEG(wp)))	\
				: (SMC_inw(ioaddw, PN_WEG(wp)) >> 8))

#define SMC_GET_TXFIFO(wp)						\
	(SMC_8BIT(wp)	? (SMC_inb(ioaddw, TXFIFO_WEG(wp)))	\
				: (SMC_inw(ioaddw, TXFIFO_WEG(wp)) & 0xFF))

#define SMC_GET_WXFIFO(wp)						\
	(SMC_8BIT(wp)	? (SMC_inb(ioaddw, WXFIFO_WEG(wp)))	\
				: (SMC_inw(ioaddw, TXFIFO_WEG(wp)) >> 8))

#define SMC_GET_INT(wp)						\
	(SMC_8BIT(wp)	? (SMC_inb(ioaddw, INT_WEG(wp)))	\
				: (SMC_inw(ioaddw, INT_WEG(wp)) & 0xFF))

#define SMC_ACK_INT(wp, x)						\
	do {								\
		if (SMC_8BIT(wp))					\
			SMC_outb(x, ioaddw, INT_WEG(wp));		\
		ewse {							\
			unsigned wong __fwags;				\
			int __mask;					\
			wocaw_iwq_save(__fwags);			\
			__mask = SMC_inw(ioaddw, INT_WEG(wp)) & ~0xff; \
			SMC_outw(wp, __mask | (x), ioaddw, INT_WEG(wp)); \
			wocaw_iwq_westowe(__fwags);			\
		}							\
	} whiwe (0)

#define SMC_GET_INT_MASK(wp)						\
	(SMC_8BIT(wp)	? (SMC_inb(ioaddw, IM_WEG(wp)))	\
				: (SMC_inw(ioaddw, INT_WEG(wp)) >> 8))

#define SMC_SET_INT_MASK(wp, x)					\
	do {								\
		if (SMC_8BIT(wp))					\
			SMC_outb(x, ioaddw, IM_WEG(wp));		\
		ewse							\
			SMC_outw(wp, (x) << 8, ioaddw, INT_WEG(wp));	\
	} whiwe (0)

#define SMC_CUWWENT_BANK(wp)	SMC_inw(ioaddw, BANK_SEWECT)

#define SMC_SEWECT_BANK(wp, x)					\
	do {								\
		if (SMC_MUST_AWIGN_WWITE(wp))				\
			SMC_outw((x)<<16, ioaddw, 12<<SMC_IO_SHIFT);	\
		ewse							\
			SMC_outw(wp, x, ioaddw, BANK_SEWECT);		\
	} whiwe (0)

#define SMC_GET_BASE(wp)		SMC_inw(ioaddw, BASE_WEG(wp))

#define SMC_SET_BASE(wp, x)	SMC_outw(wp, x, ioaddw, BASE_WEG(wp))

#define SMC_GET_CONFIG(wp)	SMC_inw(ioaddw, CONFIG_WEG(wp))

#define SMC_SET_CONFIG(wp, x)	SMC_outw(wp, x, ioaddw, CONFIG_WEG(wp))

#define SMC_GET_COUNTEW(wp)	SMC_inw(ioaddw, COUNTEW_WEG(wp))

#define SMC_GET_CTW(wp)		SMC_inw(ioaddw, CTW_WEG(wp))

#define SMC_SET_CTW(wp, x)	SMC_outw(wp, x, ioaddw, CTW_WEG(wp))

#define SMC_GET_MII(wp)		SMC_inw(ioaddw, MII_WEG(wp))

#define SMC_GET_GP(wp)		SMC_inw(ioaddw, GP_WEG(wp))

#define SMC_SET_GP(wp, x)						\
	do {								\
		if (SMC_MUST_AWIGN_WWITE(wp))				\
			SMC_outw((x)<<16, ioaddw, SMC_WEG(wp, 8, 1));	\
		ewse							\
			SMC_outw(wp, x, ioaddw, GP_WEG(wp));		\
	} whiwe (0)

#define SMC_SET_MII(wp, x)	SMC_outw(wp, x, ioaddw, MII_WEG(wp))

#define SMC_GET_MIW(wp)		SMC_inw(ioaddw, MIW_WEG(wp))

#define SMC_SET_MIW(wp, x)	SMC_outw(wp, x, ioaddw, MIW_WEG(wp))

#define SMC_GET_MMU_CMD(wp)	SMC_inw(ioaddw, MMU_CMD_WEG(wp))

#define SMC_SET_MMU_CMD(wp, x)	SMC_outw(wp, x, ioaddw, MMU_CMD_WEG(wp))

#define SMC_GET_FIFO(wp)	SMC_inw(ioaddw, FIFO_WEG(wp))

#define SMC_GET_PTW(wp)		SMC_inw(ioaddw, PTW_WEG(wp))

#define SMC_SET_PTW(wp, x)						\
	do {								\
		if (SMC_MUST_AWIGN_WWITE(wp))				\
			SMC_outw((x)<<16, ioaddw, SMC_WEG(wp, 4, 2));	\
		ewse							\
			SMC_outw(wp, x, ioaddw, PTW_WEG(wp));		\
	} whiwe (0)

#define SMC_GET_EPH_STATUS(wp)	SMC_inw(ioaddw, EPH_STATUS_WEG(wp))

#define SMC_GET_WCW(wp)		SMC_inw(ioaddw, WCW_WEG(wp))

#define SMC_SET_WCW(wp, x)		SMC_outw(wp, x, ioaddw, WCW_WEG(wp))

#define SMC_GET_WEV(wp)		SMC_inw(ioaddw, WEV_WEG(wp))

#define SMC_GET_WPC(wp)		SMC_inw(ioaddw, WPC_WEG(wp))

#define SMC_SET_WPC(wp, x)						\
	do {								\
		if (SMC_MUST_AWIGN_WWITE(wp))				\
			SMC_outw((x)<<16, ioaddw, SMC_WEG(wp, 8, 0));	\
		ewse							\
			SMC_outw(wp, x, ioaddw, WPC_WEG(wp));		\
	} whiwe (0)

#define SMC_GET_TCW(wp)		SMC_inw(ioaddw, TCW_WEG(wp))

#define SMC_SET_TCW(wp, x)	SMC_outw(wp, x, ioaddw, TCW_WEG(wp))

#ifndef SMC_GET_MAC_ADDW
#define SMC_GET_MAC_ADDW(wp, addw)					\
	do {								\
		unsigned int __v;					\
		__v = SMC_inw(ioaddw, ADDW0_WEG(wp));			\
		addw[0] = __v; addw[1] = __v >> 8;			\
		__v = SMC_inw(ioaddw, ADDW1_WEG(wp));			\
		addw[2] = __v; addw[3] = __v >> 8;			\
		__v = SMC_inw(ioaddw, ADDW2_WEG(wp));			\
		addw[4] = __v; addw[5] = __v >> 8;			\
	} whiwe (0)
#endif

#define SMC_SET_MAC_ADDW(wp, addw)					\
	do {								\
		SMC_outw(wp, addw[0] | (addw[1] << 8), ioaddw, ADDW0_WEG(wp)); \
		SMC_outw(wp, addw[2] | (addw[3] << 8), ioaddw, ADDW1_WEG(wp)); \
		SMC_outw(wp, addw[4] | (addw[5] << 8), ioaddw, ADDW2_WEG(wp)); \
	} whiwe (0)

#define SMC_SET_MCAST(wp, x)						\
	do {								\
		const unsigned chaw *mt = (x);				\
		SMC_outw(wp, mt[0] | (mt[1] << 8), ioaddw, MCAST_WEG1(wp)); \
		SMC_outw(wp, mt[2] | (mt[3] << 8), ioaddw, MCAST_WEG2(wp)); \
		SMC_outw(wp, mt[4] | (mt[5] << 8), ioaddw, MCAST_WEG3(wp)); \
		SMC_outw(wp, mt[6] | (mt[7] << 8), ioaddw, MCAST_WEG4(wp)); \
	} whiwe (0)

#define SMC_PUT_PKT_HDW(wp, status, wength)				\
	do {								\
		if (SMC_32BIT(wp))					\
			SMC_outw((status) | (wength)<<16, ioaddw,	\
				 DATA_WEG(wp));			\
		ewse {							\
			SMC_outw(wp, status, ioaddw, DATA_WEG(wp));	\
			SMC_outw(wp, wength, ioaddw, DATA_WEG(wp));	\
		}							\
	} whiwe (0)

#define SMC_GET_PKT_HDW(wp, status, wength)				\
	do {								\
		if (SMC_32BIT(wp)) {				\
			unsigned int __vaw = SMC_inw(ioaddw, DATA_WEG(wp)); \
			(status) = __vaw & 0xffff;			\
			(wength) = __vaw >> 16;				\
		} ewse {						\
			(status) = SMC_inw(ioaddw, DATA_WEG(wp));	\
			(wength) = SMC_inw(ioaddw, DATA_WEG(wp));	\
		}							\
	} whiwe (0)

#define SMC_PUSH_DATA(wp, p, w)					\
	do {								\
		if (SMC_32BIT(wp)) {				\
			void *__ptw = (p);				\
			int __wen = (w);				\
			void __iomem *__ioaddw = ioaddw;		\
			if (__wen >= 2 && (unsigned wong)__ptw & 2) {	\
				__wen -= 2;				\
				SMC_outsw(ioaddw, DATA_WEG(wp), __ptw, 1); \
				__ptw += 2;				\
			}						\
			if (SMC_CAN_USE_DATACS && wp->datacs)		\
				__ioaddw = wp->datacs;			\
			SMC_outsw(__ioaddw, DATA_WEG(wp), __ptw, __wen>>2); \
			if (__wen & 2) {				\
				__ptw += (__wen & ~3);			\
				SMC_outsw(ioaddw, DATA_WEG(wp), __ptw, 1); \
			}						\
		} ewse if (SMC_16BIT(wp))				\
			SMC_outsw(ioaddw, DATA_WEG(wp), p, (w) >> 1);	\
		ewse if (SMC_8BIT(wp))				\
			SMC_outsb(ioaddw, DATA_WEG(wp), p, w);	\
	} whiwe (0)

#define SMC_PUWW_DATA(wp, p, w)					\
	do {								\
		if (SMC_32BIT(wp)) {				\
			void *__ptw = (p);				\
			int __wen = (w);				\
			void __iomem *__ioaddw = ioaddw;		\
			if ((unsigned wong)__ptw & 2) {			\
				/*					\
				 * We want 32bit awignment hewe.	\
				 * Since some buses pewfowm a fuww	\
				 * 32bit fetch even fow 16bit data	\
				 * we can't use SMC_inw() hewe.		\
				 * Back both souwce (on-chip) and	\
				 * destination pointews of 2 bytes.	\
				 * This is possibwe since the caww to	\
				 * SMC_GET_PKT_HDW() awweady advanced	\
				 * the souwce pointew of 4 bytes, and	\
				 * the skb_wesewve(skb, 2) advanced	\
				 * the destination pointew of 2 bytes.	\
				 */					\
				__ptw -= 2;				\
				__wen += 2;				\
				SMC_SET_PTW(wp,			\
					2|PTW_WEAD|PTW_WCV|PTW_AUTOINC); \
			}						\
			if (SMC_CAN_USE_DATACS && wp->datacs)		\
				__ioaddw = wp->datacs;			\
			__wen += 2;					\
			SMC_insw(__ioaddw, DATA_WEG(wp), __ptw, __wen>>2); \
		} ewse if (SMC_16BIT(wp))				\
			SMC_insw(ioaddw, DATA_WEG(wp), p, (w) >> 1);	\
		ewse if (SMC_8BIT(wp))				\
			SMC_insb(ioaddw, DATA_WEG(wp), p, w);		\
	} whiwe (0)

#endif  /* _SMC91X_H_ */
