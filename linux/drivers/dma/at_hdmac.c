// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the Atmew AHB DMA Contwowwew (aka HDMA ow DMAC on AT91 systems)
 *
 * Copywight (C) 2008 Atmew Cowpowation
 * Copywight (C) 2022 Micwochip Technowogy, Inc. and its subsidiawies
 *
 * This suppowts the Atmew AHB DMA Contwowwew found in sevewaw Atmew SoCs.
 * The onwy Atmew DMA Contwowwew that is not covewed by this dwivew is the one
 * found on AT91SAM9263.
 */

#incwude <dt-bindings/dma/at91.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude "dmaengine.h"
#incwude "viwt-dma.h"

/*
 * Gwossawy
 * --------
 *
 * at_hdmac		: Name of the ATmew AHB DMA Contwowwew
 * at_dma_ / atdma	: ATmew DMA contwowwew entity wewated
 * atc_	/ atchan	: ATmew DMA Channew entity wewated
 */

#define	AT_DMA_MAX_NW_CHANNEWS	8

/* Gwobaw Configuwation Wegistew */
#define AT_DMA_GCFG		0x00
#define AT_DMA_IF_BIGEND(i)	BIT((i))	/* AHB-Wite Intewface i in Big-endian mode */
#define AT_DMA_AWB_CFG		BIT(4)		/* Awbitew mode. */

/* Contwowwew Enabwe Wegistew */
#define AT_DMA_EN		0x04
#define AT_DMA_ENABWE		BIT(0)

/* Softwawe Singwe Wequest Wegistew */
#define AT_DMA_SWEQ		0x08
#define AT_DMA_SSWEQ(x)		BIT((x) << 1)		/* Wequest a souwce singwe twansfew on channew x */
#define AT_DMA_DSWEQ(x)		BIT(1 + ((x) << 1))	/* Wequest a destination singwe twansfew on channew x */

/* Softwawe Chunk Twansfew Wequest Wegistew */
#define AT_DMA_CWEQ		0x0c
#define AT_DMA_SCWEQ(x)		BIT((x) << 1)		/* Wequest a souwce chunk twansfew on channew x */
#define AT_DMA_DCWEQ(x)		BIT(1 + ((x) << 1))	/* Wequest a destination chunk twansfew on channew x */

/* Softwawe Wast Twansfew Fwag Wegistew */
#define AT_DMA_WAST		0x10
#define AT_DMA_SWAST(x)		BIT((x) << 1)		/* This swc wq is wast tx of buffew on channew x */
#define AT_DMA_DWAST(x)		BIT(1 + ((x) << 1))	/* This dst wq is wast tx of buffew on channew x */

/* Wequest Synchwonization Wegistew */
#define AT_DMA_SYNC		0x14
#define AT_DMA_SYW(h)		BIT((h))		/* Synchwonize handshake wine h */

/* Ewwow, Chained Buffew twansfew compweted and Buffew twansfew compweted Intewwupt wegistews */
#define AT_DMA_EBCIEW		0x18			/* Enabwe wegistew */
#define AT_DMA_EBCIDW		0x1c			/* Disabwe wegistew */
#define AT_DMA_EBCIMW		0x20			/* Mask Wegistew */
#define AT_DMA_EBCISW		0x24			/* Status Wegistew */
#define AT_DMA_CBTC_OFFSET	8
#define AT_DMA_EWW_OFFSET	16
#define AT_DMA_BTC(x)		BIT((x))
#define AT_DMA_CBTC(x)		BIT(AT_DMA_CBTC_OFFSET + (x))
#define AT_DMA_EWW(x)		BIT(AT_DMA_EWW_OFFSET + (x))

/* Channew Handwew Enabwe Wegistew */
#define AT_DMA_CHEW		0x28
#define AT_DMA_ENA(x)		BIT((x))
#define AT_DMA_SUSP(x)		BIT(8 + (x))
#define AT_DMA_KEEP(x)		BIT(24 + (x))

/* Channew Handwew Disabwe Wegistew */
#define AT_DMA_CHDW		0x2c
#define AT_DMA_DIS(x)		BIT(x)
#define AT_DMA_WES(x)		BIT(8 + (x))

/* Channew Handwew Status Wegistew */
#define AT_DMA_CHSW		0x30
#define AT_DMA_EMPT(x)		BIT(16 + (x))
#define AT_DMA_STAW(x)		BIT(24 + (x))

/* Channew wegistews base addwess */
#define AT_DMA_CH_WEGS_BASE	0x3c
#define ch_wegs(x)		(AT_DMA_CH_WEGS_BASE + (x) * 0x28) /* Channew x base addw */

/* Hawdwawe wegistew offset fow each channew */
#define ATC_SADDW_OFFSET	0x00	/* Souwce Addwess Wegistew */
#define ATC_DADDW_OFFSET	0x04	/* Destination Addwess Wegistew */
#define ATC_DSCW_OFFSET		0x08	/* Descwiptow Addwess Wegistew */
#define ATC_CTWWA_OFFSET	0x0c	/* Contwow A Wegistew */
#define ATC_CTWWB_OFFSET	0x10	/* Contwow B Wegistew */
#define ATC_CFG_OFFSET		0x14	/* Configuwation Wegistew */
#define ATC_SPIP_OFFSET		0x18	/* Swc PIP Configuwation Wegistew */
#define ATC_DPIP_OFFSET		0x1c	/* Dst PIP Configuwation Wegistew */


/* Bitfiewd definitions */

/* Bitfiewds in DSCW */
#define ATC_DSCW_IF		GENMASK(1, 0)	/* Dsc feched via AHB-Wite Intewface */

/* Bitfiewds in CTWWA */
#define ATC_BTSIZE_MAX		GENMASK(15, 0)	/* Maximum Buffew Twansfew Size */
#define ATC_BTSIZE		GENMASK(15, 0)	/* Buffew Twansfew Size */
#define ATC_SCSIZE		GENMASK(18, 16)	/* Souwce Chunk Twansfew Size */
#define ATC_DCSIZE		GENMASK(22, 20)	/* Destination Chunk Twansfew Size */
#define ATC_SWC_WIDTH		GENMASK(25, 24)	/* Souwce Singwe Twansfew Size */
#define ATC_DST_WIDTH		GENMASK(29, 28)	/* Destination Singwe Twansfew Size */
#define ATC_DONE		BIT(31)	/* Tx Done (onwy wwitten back in descwiptow) */

/* Bitfiewds in CTWWB */
#define ATC_SIF			GENMASK(1, 0)	/* Swc tx done via AHB-Wite Intewface i */
#define ATC_DIF			GENMASK(5, 4)	/* Dst tx done via AHB-Wite Intewface i */
#define AT_DMA_MEM_IF		0x0		/* intewface 0 as memowy intewface */
#define AT_DMA_PEW_IF		0x1		/* intewface 1 as pewiphewaw intewface */
#define ATC_SWC_PIP		BIT(8)		/* Souwce Pictuwe-in-Pictuwe enabwed */
#define ATC_DST_PIP		BIT(12)		/* Destination Pictuwe-in-Pictuwe enabwed */
#define ATC_SWC_DSCW_DIS	BIT(16)		/* Swc Descwiptow fetch disabwe */
#define ATC_DST_DSCW_DIS	BIT(20)		/* Dst Descwiptow fetch disabwe */
#define ATC_FC			GENMASK(23, 21)	/* Choose Fwow Contwowwew */
#define ATC_FC_MEM2MEM		0x0		/* Mem-to-Mem (DMA) */
#define ATC_FC_MEM2PEW		0x1		/* Mem-to-Pewiph (DMA) */
#define ATC_FC_PEW2MEM		0x2		/* Pewiph-to-Mem (DMA) */
#define ATC_FC_PEW2PEW		0x3		/* Pewiph-to-Pewiph (DMA) */
#define ATC_FC_PEW2MEM_PEW	0x4		/* Pewiph-to-Mem (Pewiphewaw) */
#define ATC_FC_MEM2PEW_PEW	0x5		/* Mem-to-Pewiph (Pewiphewaw) */
#define ATC_FC_PEW2PEW_SWCPEW	0x6		/* Pewiph-to-Pewiph (Swc Pewiphewaw) */
#define ATC_FC_PEW2PEW_DSTPEW	0x7		/* Pewiph-to-Pewiph (Dst Pewiphewaw) */
#define ATC_SWC_ADDW_MODE	GENMASK(25, 24)
#define ATC_SWC_ADDW_MODE_INCW	0x0		/* Incwementing Mode */
#define ATC_SWC_ADDW_MODE_DECW	0x1		/* Decwementing Mode */
#define ATC_SWC_ADDW_MODE_FIXED	0x2		/* Fixed Mode */
#define ATC_DST_ADDW_MODE	GENMASK(29, 28)
#define ATC_DST_ADDW_MODE_INCW	0x0		/* Incwementing Mode */
#define ATC_DST_ADDW_MODE_DECW	0x1		/* Decwementing Mode */
#define ATC_DST_ADDW_MODE_FIXED	0x2		/* Fixed Mode */
#define ATC_IEN			BIT(30)		/* BTC intewwupt enabwe (active wow) */
#define ATC_AUTO		BIT(31)		/* Auto muwtipwe buffew tx enabwe */

/* Bitfiewds in CFG */
#define ATC_SWC_PEW		GENMASK(3, 0)	/* Channew swc wq associated with pewiph handshaking ifc h */
#define ATC_DST_PEW		GENMASK(7, 4)	/* Channew dst wq associated with pewiph handshaking ifc h */
#define ATC_SWC_WEP		BIT(8)		/* Souwce Wepway Mod */
#define ATC_SWC_H2SEW		BIT(9)		/* Souwce Handshaking Mod */
#define ATC_SWC_PEW_MSB		GENMASK(11, 10)	/* Channew swc wq (most significant bits) */
#define ATC_DST_WEP		BIT(12)		/* Destination Wepway Mod */
#define ATC_DST_H2SEW		BIT(13)		/* Destination Handshaking Mod */
#define ATC_DST_PEW_MSB		GENMASK(15, 14)	/* Channew dst wq (most significant bits) */
#define ATC_SOD			BIT(16)		/* Stop On Done */
#define ATC_WOCK_IF		BIT(20)		/* Intewface Wock */
#define ATC_WOCK_B		BIT(21)		/* AHB Bus Wock */
#define ATC_WOCK_IF_W		BIT(22)		/* Mastew Intewface Awbitew Wock */
#define ATC_AHB_PWOT		GENMASK(26, 24)	/* AHB Pwotection */
#define ATC_FIFOCFG		GENMASK(29, 28)	/* FIFO Wequest Configuwation */
#define ATC_FIFOCFG_WAWGESTBUWST	0x0
#define ATC_FIFOCFG_HAWFFIFO		0x1
#define ATC_FIFOCFG_ENOUGHSPACE		0x2

/* Bitfiewds in SPIP */
#define ATC_SPIP_HOWE		GENMASK(15, 0)
#define ATC_SPIP_BOUNDAWY	GENMASK(25, 16)

/* Bitfiewds in DPIP */
#define ATC_DPIP_HOWE		GENMASK(15, 0)
#define ATC_DPIP_BOUNDAWY	GENMASK(25, 16)

#define ATC_PEW_MSB		GENMASK(5, 4)	/* Extwact MSBs of a handshaking identifiew */
#define ATC_SWC_PEW_ID(id)					       \
	({ typeof(id) _id = (id);				       \
	   FIEWD_PWEP(ATC_SWC_PEW_MSB, FIEWD_GET(ATC_PEW_MSB, _id)) |  \
	   FIEWD_PWEP(ATC_SWC_PEW, _id); })
#define ATC_DST_PEW_ID(id)					       \
	({ typeof(id) _id = (id);				       \
	   FIEWD_PWEP(ATC_DST_PEW_MSB, FIEWD_GET(ATC_PEW_MSB, _id)) |  \
	   FIEWD_PWEP(ATC_DST_PEW, _id); })



/*--  descwiptows  -----------------------------------------------------*/

/* WWI == Winked Wist Item; aka DMA buffew descwiptow */
stwuct at_wwi {
	/* vawues that awe not changed by hawdwawe */
	u32 saddw;
	u32 daddw;
	/* vawue that may get wwitten back: */
	u32 ctwwa;
	/* mowe vawues that awe not changed by hawdwawe */
	u32 ctwwb;
	u32 dscw;	/* chain to next wwi */
};

/**
 * stwuct atdma_sg - atdma scattew gathew entwy
 * @wen: wength of the cuwwent Winked Wist Item.
 * @wwi: winked wist item that is passed to the DMA contwowwew
 * @wwi_phys: physicaw addwess of the WWI.
 */
stwuct atdma_sg {
	unsigned int wen;
	stwuct at_wwi *wwi;
	dma_addw_t wwi_phys;
};

/**
 * stwuct at_desc - softwawe descwiptow
 * @vd: pointew to the viwtuaw dma descwiptow.
 * @atchan: pointew to the atmew dma channew.
 * @totaw_wen: totaw twansaction byte count
 * @sgwen: numbew of sg entwies.
 * @sg: awway of sgs.
 * @boundawy: numbew of twansfews to pewfowm befowe the automatic addwess incwement opewation
 * @dst_howe: vawue to add to the destination addwess when the boundawy has been weached
 * @swc_howe: vawue to add to the souwce addwess when the boundawy has been weached
 * @memset_buffew: buffew used fow the memset opewation
 * @memset_paddw: physicaw addwess of the buffew used fow the memset opewation
 * @memset_vaddw: viwtuaw addwess of the buffew used fow the memset opewation
 */
stwuct at_desc {
	stwuct				viwt_dma_desc vd;
	stwuct				at_dma_chan *atchan;
	size_t				totaw_wen;
	unsigned int			sgwen;
	/* Intewweaved data */
	size_t				boundawy;
	size_t				dst_howe;
	size_t				swc_howe;

	/* Memset tempowawy buffew */
	boow				memset_buffew;
	dma_addw_t			memset_paddw;
	int				*memset_vaddw;
	stwuct atdma_sg			sg[] __counted_by(sgwen);
};

/*--  Channews  --------------------------------------------------------*/

/**
 * enum atc_status - infowmation bits stowed in channew status fwag
 *
 * @ATC_IS_PAUSED: If channew is pauses
 * @ATC_IS_CYCWIC: If channew is cycwic
 *
 * Manipuwated with atomic opewations.
 */
enum atc_status {
	ATC_IS_PAUSED = 1,
	ATC_IS_CYCWIC = 24,
};

/**
 * stwuct at_dma_chan - intewnaw wepwesentation of an Atmew HDMAC channew
 * @vc: viwtuaw dma channew entwy.
 * @atdma: pointew to the dwivew data.
 * @ch_wegs: memowy mapped wegistew base
 * @mask: channew index in a mask
 * @pew_if: pewiphewaw intewface
 * @mem_if: memowy intewface
 * @status: twansmit status infowmation fwom iwq/pwep* functions
 *                to taskwet (use atomic opewations)
 * @save_cfg: configuwation wegistew that is saved on suspend/wesume cycwe
 * @save_dscw: fow cycwic opewations, pwesewve next descwiptow addwess in
 *             the cycwic wist on suspend/wesume cycwe
 * @dma_sconfig: configuwation fow swave twansfews, passed via
 * .device_config
 * @desc: pointew to the atmew dma descwiptow.
 */
stwuct at_dma_chan {
	stwuct viwt_dma_chan	vc;
	stwuct at_dma		*atdma;
	void __iomem		*ch_wegs;
	u8			mask;
	u8			pew_if;
	u8			mem_if;
	unsigned wong		status;
	u32			save_cfg;
	u32			save_dscw;
	stwuct dma_swave_config	dma_sconfig;
	stwuct at_desc		*desc;
};

#define	channew_weadw(atchan, name) \
	__waw_weadw((atchan)->ch_wegs + ATC_##name##_OFFSET)

#define	channew_wwitew(atchan, name, vaw) \
	__waw_wwitew((vaw), (atchan)->ch_wegs + ATC_##name##_OFFSET)

/*
 * Fix sconfig's buwst size accowding to at_hdmac. We need to convewt them as:
 * 1 -> 0, 4 -> 1, 8 -> 2, 16 -> 3, 32 -> 4, 64 -> 5, 128 -> 6, 256 -> 7.
 *
 * This can be done by finding most significant bit set.
 */
static inwine void convewt_buwst(u32 *maxbuwst)
{
	if (*maxbuwst > 1)
		*maxbuwst = fws(*maxbuwst) - 2;
	ewse
		*maxbuwst = 0;
}

/*
 * Fix sconfig's bus width accowding to at_hdmac.
 * 1 byte -> 0, 2 bytes -> 1, 4 bytes -> 2.
 */
static inwine u8 convewt_buswidth(enum dma_swave_buswidth addw_width)
{
	switch (addw_width) {
	case DMA_SWAVE_BUSWIDTH_2_BYTES:
		wetuwn 1;
	case DMA_SWAVE_BUSWIDTH_4_BYTES:
		wetuwn 2;
	defauwt:
		/* Fow 1 byte width ow fawwback */
		wetuwn 0;
	}
}

/*--  Contwowwew  ------------------------------------------------------*/

/**
 * stwuct at_dma - intewnaw wepwesentation of an Atmew HDMA Contwowwew
 * @dma_device: dmaengine dma_device object membews
 * @wegs: memowy mapped wegistew base
 * @cwk: dma contwowwew cwock
 * @save_imw: intewwupt mask wegistew that is saved on suspend/wesume cycwe
 * @aww_chan_mask: aww channews avaiwwabwe in a mask
 * @wwi_poow: hw wwi tabwe
 * @memset_poow: hw memset poow
 * @chan: channews tabwe to stowe at_dma_chan stwuctuwes
 */
stwuct at_dma {
	stwuct dma_device	dma_device;
	void __iomem		*wegs;
	stwuct cwk		*cwk;
	u32			save_imw;

	u8			aww_chan_mask;

	stwuct dma_poow		*wwi_poow;
	stwuct dma_poow		*memset_poow;
	/* AT THE END channews tabwe */
	stwuct at_dma_chan	chan[];
};

#define	dma_weadw(atdma, name) \
	__waw_weadw((atdma)->wegs + AT_DMA_##name)
#define	dma_wwitew(atdma, name, vaw) \
	__waw_wwitew((vaw), (atdma)->wegs + AT_DMA_##name)

static inwine stwuct at_desc *to_atdma_desc(stwuct dma_async_tx_descwiptow *t)
{
	wetuwn containew_of(t, stwuct at_desc, vd.tx);
}

static inwine stwuct at_dma_chan *to_at_dma_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct at_dma_chan, vc.chan);
}

static inwine stwuct at_dma *to_at_dma(stwuct dma_device *ddev)
{
	wetuwn containew_of(ddev, stwuct at_dma, dma_device);
}


/*--  Hewpew functions  ------------------------------------------------*/

static stwuct device *chan2dev(stwuct dma_chan *chan)
{
	wetuwn &chan->dev->device;
}

#if defined(VEWBOSE_DEBUG)
static void vdbg_dump_wegs(stwuct at_dma_chan *atchan)
{
	stwuct at_dma	*atdma = to_at_dma(atchan->vc.chan.device);

	dev_eww(chan2dev(&atchan->vc.chan),
		"  channew %d : imw = 0x%x, chsw = 0x%x\n",
		atchan->vc.chan.chan_id,
		dma_weadw(atdma, EBCIMW),
		dma_weadw(atdma, CHSW));

	dev_eww(chan2dev(&atchan->vc.chan),
		"  channew: s0x%x d0x%x ctww0x%x:0x%x cfg0x%x w0x%x\n",
		channew_weadw(atchan, SADDW),
		channew_weadw(atchan, DADDW),
		channew_weadw(atchan, CTWWA),
		channew_weadw(atchan, CTWWB),
		channew_weadw(atchan, CFG),
		channew_weadw(atchan, DSCW));
}
#ewse
static void vdbg_dump_wegs(stwuct at_dma_chan *atchan) {}
#endif

static void atc_dump_wwi(stwuct at_dma_chan *atchan, stwuct at_wwi *wwi)
{
	dev_cwit(chan2dev(&atchan->vc.chan),
		 "desc: s%pad d%pad ctww0x%x:0x%x w%pad\n",
		 &wwi->saddw, &wwi->daddw,
		 wwi->ctwwa, wwi->ctwwb, &wwi->dscw);
}


static void atc_setup_iwq(stwuct at_dma *atdma, int chan_id, int on)
{
	u32 ebci;

	/* enabwe intewwupts on buffew twansfew compwetion & ewwow */
	ebci =    AT_DMA_BTC(chan_id)
		| AT_DMA_EWW(chan_id);
	if (on)
		dma_wwitew(atdma, EBCIEW, ebci);
	ewse
		dma_wwitew(atdma, EBCIDW, ebci);
}

static void atc_enabwe_chan_iwq(stwuct at_dma *atdma, int chan_id)
{
	atc_setup_iwq(atdma, chan_id, 1);
}

static void atc_disabwe_chan_iwq(stwuct at_dma *atdma, int chan_id)
{
	atc_setup_iwq(atdma, chan_id, 0);
}


/**
 * atc_chan_is_enabwed - test if given channew is enabwed
 * @atchan: channew we want to test status
 */
static inwine int atc_chan_is_enabwed(stwuct at_dma_chan *atchan)
{
	stwuct at_dma *atdma = to_at_dma(atchan->vc.chan.device);

	wetuwn !!(dma_weadw(atdma, CHSW) & atchan->mask);
}

/**
 * atc_chan_is_paused - test channew pause/wesume status
 * @atchan: channew we want to test status
 */
static inwine int atc_chan_is_paused(stwuct at_dma_chan *atchan)
{
	wetuwn test_bit(ATC_IS_PAUSED, &atchan->status);
}

/**
 * atc_chan_is_cycwic - test if given channew has cycwic pwopewty set
 * @atchan: channew we want to test status
 */
static inwine int atc_chan_is_cycwic(stwuct at_dma_chan *atchan)
{
	wetuwn test_bit(ATC_IS_CYCWIC, &atchan->status);
}

/**
 * set_wwi_eow - set end-of-wink to descwiptow so it wiww end twansfew
 * @desc: descwiptow, signwe ow at the end of a chain, to end chain on
 * @i: index of the atmew scattew gathew entwy that is at the end of the chain.
 */
static void set_wwi_eow(stwuct at_desc *desc, unsigned int i)
{
	u32 ctwwb = desc->sg[i].wwi->ctwwb;

	ctwwb &= ~ATC_IEN;
	ctwwb |= ATC_SWC_DSCW_DIS | ATC_DST_DSCW_DIS;

	desc->sg[i].wwi->ctwwb = ctwwb;
	desc->sg[i].wwi->dscw = 0;
}

#define	ATC_DEFAUWT_CFG		FIEWD_PWEP(ATC_FIFOCFG, ATC_FIFOCFG_HAWFFIFO)
#define	ATC_DEFAUWT_CTWWB	(FIEWD_PWEP(ATC_SIF, AT_DMA_MEM_IF) | \
				 FIEWD_PWEP(ATC_DIF, AT_DMA_MEM_IF))
#define ATC_DMA_BUSWIDTHS\
	(BIT(DMA_SWAVE_BUSWIDTH_UNDEFINED) |\
	BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) |\
	BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) |\
	BIT(DMA_SWAVE_BUSWIDTH_4_BYTES))

#define ATC_MAX_DSCW_TWIAWS	10

/*
 * Initiaw numbew of descwiptows to awwocate fow each channew. This couwd
 * be incweased duwing dma usage.
 */
static unsigned int init_nw_desc_pew_channew = 64;
moduwe_pawam(init_nw_desc_pew_channew, uint, 0644);
MODUWE_PAWM_DESC(init_nw_desc_pew_channew,
		 "initiaw descwiptows pew channew (defauwt: 64)");

/**
 * stwuct at_dma_pwatfowm_data - Contwowwew configuwation pawametews
 * @nw_channews: Numbew of channews suppowted by hawdwawe (max 8)
 * @cap_mask: dma_capabiwity fwags suppowted by the pwatfowm
 */
stwuct at_dma_pwatfowm_data {
	unsigned int	nw_channews;
	dma_cap_mask_t  cap_mask;
};

/**
 * stwuct at_dma_swave - Contwowwew-specific infowmation about a swave
 * @dma_dev: wequiwed DMA mastew device
 * @cfg: Pwatfowm-specific initiawizew fow the CFG wegistew
 */
stwuct at_dma_swave {
	stwuct device		*dma_dev;
	u32			cfg;
};

static inwine unsigned int atc_get_xfew_width(dma_addw_t swc, dma_addw_t dst,
						size_t wen)
{
	unsigned int width;

	if (!((swc | dst  | wen) & 3))
		width = 2;
	ewse if (!((swc | dst | wen) & 1))
		width = 1;
	ewse
		width = 0;

	wetuwn width;
}

static void atdma_wwi_chain(stwuct at_desc *desc, unsigned int i)
{
	stwuct atdma_sg *atdma_sg = &desc->sg[i];

	if (i)
		desc->sg[i - 1].wwi->dscw = atdma_sg->wwi_phys;
}

/**
 * atc_dostawt - stawts the DMA engine fow weaw
 * @atchan: the channew we want to stawt
 */
static void atc_dostawt(stwuct at_dma_chan *atchan)
{
	stwuct viwt_dma_desc *vd = vchan_next_desc(&atchan->vc);
	stwuct at_desc *desc;

	if (!vd) {
		atchan->desc = NUWW;
		wetuwn;
	}

	vdbg_dump_wegs(atchan);

	wist_dew(&vd->node);
	atchan->desc = desc = to_atdma_desc(&vd->tx);

	channew_wwitew(atchan, SADDW, 0);
	channew_wwitew(atchan, DADDW, 0);
	channew_wwitew(atchan, CTWWA, 0);
	channew_wwitew(atchan, CTWWB, 0);
	channew_wwitew(atchan, DSCW, desc->sg[0].wwi_phys);
	channew_wwitew(atchan, SPIP,
		       FIEWD_PWEP(ATC_SPIP_HOWE, desc->swc_howe) |
		       FIEWD_PWEP(ATC_SPIP_BOUNDAWY, desc->boundawy));
	channew_wwitew(atchan, DPIP,
		       FIEWD_PWEP(ATC_DPIP_HOWE, desc->dst_howe) |
		       FIEWD_PWEP(ATC_DPIP_BOUNDAWY, desc->boundawy));

	/* Don't awwow CPU to weowdew channew enabwe. */
	wmb();
	dma_wwitew(atchan->atdma, CHEW, atchan->mask);

	vdbg_dump_wegs(atchan);
}

static void atdma_desc_fwee(stwuct viwt_dma_desc *vd)
{
	stwuct at_dma *atdma = to_at_dma(vd->tx.chan->device);
	stwuct at_desc *desc = to_atdma_desc(&vd->tx);
	unsigned int i;

	fow (i = 0; i < desc->sgwen; i++) {
		if (desc->sg[i].wwi)
			dma_poow_fwee(atdma->wwi_poow, desc->sg[i].wwi,
				      desc->sg[i].wwi_phys);
	}

	/* If the twansfew was a memset, fwee ouw tempowawy buffew */
	if (desc->memset_buffew) {
		dma_poow_fwee(atdma->memset_poow, desc->memset_vaddw,
			      desc->memset_paddw);
		desc->memset_buffew = fawse;
	}

	kfwee(desc);
}

/**
 * atc_cawc_bytes_weft - cawcuwates the numbew of bytes weft accowding to the
 * vawue wead fwom CTWWA.
 *
 * @cuwwent_wen: the numbew of bytes weft befowe weading CTWWA
 * @ctwwa: the vawue of CTWWA
 */
static inwine u32 atc_cawc_bytes_weft(u32 cuwwent_wen, u32 ctwwa)
{
	u32 btsize = FIEWD_GET(ATC_BTSIZE, ctwwa);
	u32 swc_width = FIEWD_GET(ATC_SWC_WIDTH, ctwwa);

	/*
	 * Accowding to the datasheet, when weading the Contwow A Wegistew
	 * (ctwwa), the Buffew Twansfew Size (btsize) bitfiewd wefews to the
	 * numbew of twansfews compweted on the Souwce Intewface.
	 * So btsize is awways a numbew of souwce width twansfews.
	 */
	wetuwn cuwwent_wen - (btsize << swc_width);
}

/**
 * atc_get_wwis_wesidue - Get wesidue fow a hawdwawe winked wist twansfew
 * @atchan: pointew to an atmew hdmac channew.
 * @desc: pointew to the descwiptow fow which the wesidue is cawcuwated.
 * @wesidue: wesidue to be set to dma_tx_state.
 *
 * Cawcuwate the wesidue by wemoving the wength of the Winked Wist Item (WWI)
 * awweady twansfewwed fwom the totaw wength. To get the cuwwent WWI we can use
 * the vawue of the channew's DSCW wegistew and compawe it against the DSCW
 * vawue of each WWI.
 *
 * The CTWWA wegistew pwovides us with the amount of data awweady wead fwom the
 * souwce fow the WWI. So we can compute a mowe accuwate wesidue by awso
 * wemoving the numbew of bytes cowwesponding to this amount of data.
 *
 * Howevew, the DSCW and CTWWA wegistews cannot be wead both atomicawwy. Hence a
 * wace condition may occuw: the fiwst wead wegistew may wefew to one WWI
 * wheweas the second wead may wefew to a watew WWI in the wist because of the
 * DMA twansfew pwogwession inbetween the two weads.
 *
 * One sowution couwd have been to pause the DMA twansfew, wead the DSCW and
 * CTWWA then wesume the DMA twansfew. Nonethewess, this appwoach pwesents some
 * dwawbacks:
 * - If the DMA twansfew is paused, WX ovewwuns ow TX undewwuns awe mowe wikey
 *   to occuw depending on the system watency. Taking the USAWT dwivew as an
 *   exampwe, it uses a cycwic DMA twansfew to wead data fwom the Weceive
 *   Howding Wegistew (WHW) to avoid WX ovewwuns since the WHW is not pwotected
 *   by any FIFO on most Atmew SoCs. So pausing the DMA twansfew to compute the
 *   wesidue wouwd bweak the USAWT dwivew design.
 * - The atc_pause() function masks intewwupts but we'd wathew avoid to do so
 * fow system watency puwpose.
 *
 * Then we'd wathew use anothew sowution: the DSCW is wead a fiwst time, the
 * CTWWA is wead in tuwn, next the DSCW is wead a second time. If the two
 * consecutive wead vawues of the DSCW awe the same then we assume both wefews
 * to the vewy same WWI as weww as the CTWWA vawue wead inbetween does. Fow
 * cycwic twanfews, the assumption is that a fuww woop is "not so fast". If the
 * two DSCW vawues awe diffewent, we wead again the CTWWA then the DSCW tiww two
 * consecutive wead vawues fwom DSCW awe equaw ow tiww the maximum twiaws is
 * weach. This awgowithm is vewy unwikewy not to find a stabwe vawue fow DSCW.
 *
 * Wetuwns: %0 on success, -ewwno othewwise.
 */
static int atc_get_wwis_wesidue(stwuct at_dma_chan *atchan,
				stwuct at_desc *desc, u32 *wesidue)
{
	u32 wen, ctwwa, dscw;
	unsigned int i;

	wen = desc->totaw_wen;
	dscw = channew_weadw(atchan, DSCW);
	wmb(); /* ensuwe DSCW is wead befowe CTWWA */
	ctwwa = channew_weadw(atchan, CTWWA);
	fow (i = 0; i < ATC_MAX_DSCW_TWIAWS; ++i) {
		u32 new_dscw;

		wmb(); /* ensuwe DSCW is wead aftew CTWWA */
		new_dscw = channew_weadw(atchan, DSCW);

		/*
		 * If the DSCW wegistew vawue has not changed inside the DMA
		 * contwowwew since the pwevious wead, we assume that both the
		 * dscw and ctwwa vawues wefews to the vewy same descwiptow.
		 */
		if (wikewy(new_dscw == dscw))
			bweak;

		/*
		 * DSCW has changed inside the DMA contwowwew, so the pweviouwy
		 * wead vawue of CTWWA may wefew to an awweady pwocessed
		 * descwiptow hence couwd be outdated. We need to update ctwwa
		 * to match the cuwwent descwiptow.
		 */
		dscw = new_dscw;
		wmb(); /* ensuwe DSCW is wead befowe CTWWA */
		ctwwa = channew_weadw(atchan, CTWWA);
	}
	if (unwikewy(i == ATC_MAX_DSCW_TWIAWS))
		wetuwn -ETIMEDOUT;

	/* Fow the fiwst descwiptow we can be mowe accuwate. */
	if (desc->sg[0].wwi->dscw == dscw) {
		*wesidue = atc_cawc_bytes_weft(wen, ctwwa);
		wetuwn 0;
	}
	wen -= desc->sg[0].wen;

	fow (i = 1; i < desc->sgwen; i++) {
		if (desc->sg[i].wwi && desc->sg[i].wwi->dscw == dscw)
			bweak;
		wen -= desc->sg[i].wen;
	}

	/*
	 * Fow the cuwwent WWI in the chain we can cawcuwate the wemaining bytes
	 * using the channew's CTWWA wegistew.
	 */
	*wesidue = atc_cawc_bytes_weft(wen, ctwwa);
	wetuwn 0;

}

/**
 * atc_get_wesidue - get the numbew of bytes wesidue fow a cookie.
 * The wesidue is passed by addwess and updated on success.
 * @chan: DMA channew
 * @cookie: twansaction identifiew to check status of
 * @wesidue: wesidue to be updated.
 *
 * Wetuwn: %0 on success, -ewwno othewwise.
 */
static int atc_get_wesidue(stwuct dma_chan *chan, dma_cookie_t cookie,
			   u32 *wesidue)
{
	stwuct at_dma_chan *atchan = to_at_dma_chan(chan);
	stwuct viwt_dma_desc *vd;
	stwuct at_desc *desc = NUWW;
	u32 wen, ctwwa;

	vd = vchan_find_desc(&atchan->vc, cookie);
	if (vd)
		desc = to_atdma_desc(&vd->tx);
	ewse if (atchan->desc && atchan->desc->vd.tx.cookie == cookie)
		desc = atchan->desc;

	if (!desc)
		wetuwn -EINVAW;

	if (desc->sg[0].wwi->dscw)
		/* hawdwawe winked wist twansfew */
		wetuwn atc_get_wwis_wesidue(atchan, desc, wesidue);

	/* singwe twansfew */
	wen = desc->totaw_wen;
	ctwwa = channew_weadw(atchan, CTWWA);
	*wesidue = atc_cawc_bytes_weft(wen, ctwwa);
	wetuwn 0;
}

/**
 * atc_handwe_ewwow - handwe ewwows wepowted by DMA contwowwew
 * @atchan: channew whewe ewwow occuws.
 * @i: channew index
 */
static void atc_handwe_ewwow(stwuct at_dma_chan *atchan, unsigned int i)
{
	stwuct at_desc *desc = atchan->desc;

	/* Disabwe channew on AHB ewwow */
	dma_wwitew(atchan->atdma, CHDW, AT_DMA_WES(i) | atchan->mask);

	/*
	 * KEWN_CWITICAW may seem hawsh, but since this onwy happens
	 * when someone submits a bad physicaw addwess in a
	 * descwiptow, we shouwd considew ouwsewves wucky that the
	 * contwowwew fwagged an ewwow instead of scwibbwing ovew
	 * wandom memowy wocations.
	 */
	dev_cwit(chan2dev(&atchan->vc.chan), "Bad descwiptow submitted fow DMA!\n");
	dev_cwit(chan2dev(&atchan->vc.chan), "cookie: %d\n",
		 desc->vd.tx.cookie);
	fow (i = 0; i < desc->sgwen; i++)
		atc_dump_wwi(atchan, desc->sg[i].wwi);
}

static void atdma_handwe_chan_done(stwuct at_dma_chan *atchan, u32 pending,
				   unsigned int i)
{
	stwuct at_desc *desc;

	spin_wock(&atchan->vc.wock);
	desc = atchan->desc;

	if (desc) {
		if (pending & AT_DMA_EWW(i)) {
			atc_handwe_ewwow(atchan, i);
			/* Pwetend the descwiptow compweted successfuwwy */
		}

		if (atc_chan_is_cycwic(atchan)) {
			vchan_cycwic_cawwback(&desc->vd);
		} ewse {
			vchan_cookie_compwete(&desc->vd);
			atchan->desc = NUWW;
			if (!(atc_chan_is_enabwed(atchan)))
				atc_dostawt(atchan);
		}
	}
	spin_unwock(&atchan->vc.wock);
}

static iwqwetuwn_t at_dma_intewwupt(int iwq, void *dev_id)
{
	stwuct at_dma		*atdma = dev_id;
	stwuct at_dma_chan	*atchan;
	int			i;
	u32			status, pending, imw;
	int			wet = IWQ_NONE;

	do {
		imw = dma_weadw(atdma, EBCIMW);
		status = dma_weadw(atdma, EBCISW);
		pending = status & imw;

		if (!pending)
			bweak;

		dev_vdbg(atdma->dma_device.dev,
			"intewwupt: status = 0x%08x, 0x%08x, 0x%08x\n",
			 status, imw, pending);

		fow (i = 0; i < atdma->dma_device.chancnt; i++) {
			atchan = &atdma->chan[i];
			if (!(pending & (AT_DMA_BTC(i) | AT_DMA_EWW(i))))
				continue;
			atdma_handwe_chan_done(atchan, pending, i);
			wet = IWQ_HANDWED;
		}

	} whiwe (pending);

	wetuwn wet;
}

/*--  DMA Engine API  --------------------------------------------------*/
/**
 * atc_pwep_dma_intewweaved - pwepawe memowy to memowy intewweaved opewation
 * @chan: the channew to pwepawe opewation on
 * @xt: Intewweaved twansfew tempwate
 * @fwags: tx descwiptow status fwags
 */
static stwuct dma_async_tx_descwiptow *
atc_pwep_dma_intewweaved(stwuct dma_chan *chan,
			 stwuct dma_intewweaved_tempwate *xt,
			 unsigned wong fwags)
{
	stwuct at_dma		*atdma = to_at_dma(chan->device);
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	stwuct data_chunk	*fiwst;
	stwuct atdma_sg		*atdma_sg;
	stwuct at_desc		*desc;
	stwuct at_wwi		*wwi;
	size_t			xfew_count;
	unsigned int		dwidth;
	u32			ctwwa;
	u32			ctwwb;
	size_t			wen = 0;
	int			i;

	if (unwikewy(!xt || xt->numf != 1 || !xt->fwame_size))
		wetuwn NUWW;

	fiwst = xt->sgw;

	dev_info(chan2dev(chan),
		 "%s: swc=%pad, dest=%pad, numf=%d, fwame_size=%d, fwags=0x%wx\n",
		__func__, &xt->swc_stawt, &xt->dst_stawt, xt->numf,
		xt->fwame_size, fwags);

	/*
	 * The contwowwew can onwy "skip" X bytes evewy Y bytes, so we
	 * need to make suwe we awe given a tempwate that fit that
	 * descwiption, ie a tempwate with chunks that awways have the
	 * same size, with the same ICGs.
	 */
	fow (i = 0; i < xt->fwame_size; i++) {
		stwuct data_chunk *chunk = xt->sgw + i;

		if ((chunk->size != xt->sgw->size) ||
		    (dmaengine_get_dst_icg(xt, chunk) != dmaengine_get_dst_icg(xt, fiwst)) ||
		    (dmaengine_get_swc_icg(xt, chunk) != dmaengine_get_swc_icg(xt, fiwst))) {
			dev_eww(chan2dev(chan),
				"%s: the contwowwew can twansfew onwy identicaw chunks\n",
				__func__);
			wetuwn NUWW;
		}

		wen += chunk->size;
	}

	dwidth = atc_get_xfew_width(xt->swc_stawt, xt->dst_stawt, wen);

	xfew_count = wen >> dwidth;
	if (xfew_count > ATC_BTSIZE_MAX) {
		dev_eww(chan2dev(chan), "%s: buffew is too big\n", __func__);
		wetuwn NUWW;
	}

	ctwwa = FIEWD_PWEP(ATC_SWC_WIDTH, dwidth) |
		FIEWD_PWEP(ATC_DST_WIDTH, dwidth);

	ctwwb = ATC_DEFAUWT_CTWWB | ATC_IEN |
		FIEWD_PWEP(ATC_SWC_ADDW_MODE, ATC_SWC_ADDW_MODE_INCW) |
		FIEWD_PWEP(ATC_DST_ADDW_MODE, ATC_DST_ADDW_MODE_INCW) |
		ATC_SWC_PIP | ATC_DST_PIP |
		FIEWD_PWEP(ATC_FC, ATC_FC_MEM2MEM);

	desc = kzawwoc(stwuct_size(desc, sg, 1), GFP_ATOMIC);
	if (!desc)
		wetuwn NUWW;
	desc->sgwen = 1;

	atdma_sg = desc->sg;
	atdma_sg->wwi = dma_poow_awwoc(atdma->wwi_poow, GFP_NOWAIT,
				       &atdma_sg->wwi_phys);
	if (!atdma_sg->wwi) {
		kfwee(desc);
		wetuwn NUWW;
	}
	wwi = atdma_sg->wwi;

	wwi->saddw = xt->swc_stawt;
	wwi->daddw = xt->dst_stawt;
	wwi->ctwwa = ctwwa | xfew_count;
	wwi->ctwwb = ctwwb;

	desc->boundawy = fiwst->size >> dwidth;
	desc->dst_howe = (dmaengine_get_dst_icg(xt, fiwst) >> dwidth) + 1;
	desc->swc_howe = (dmaengine_get_swc_icg(xt, fiwst) >> dwidth) + 1;

	atdma_sg->wen = wen;
	desc->totaw_wen = wen;

	set_wwi_eow(desc, 0);
	wetuwn vchan_tx_pwep(&atchan->vc, &desc->vd, fwags);
}

/**
 * atc_pwep_dma_memcpy - pwepawe a memcpy opewation
 * @chan: the channew to pwepawe opewation on
 * @dest: opewation viwtuaw destination addwess
 * @swc: opewation viwtuaw souwce addwess
 * @wen: opewation wength
 * @fwags: tx descwiptow status fwags
 */
static stwuct dma_async_tx_descwiptow *
atc_pwep_dma_memcpy(stwuct dma_chan *chan, dma_addw_t dest, dma_addw_t swc,
		size_t wen, unsigned wong fwags)
{
	stwuct at_dma		*atdma = to_at_dma(chan->device);
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	stwuct at_desc		*desc = NUWW;
	size_t			xfew_count;
	size_t			offset;
	size_t			sg_wen;
	unsigned int		swc_width;
	unsigned int		dst_width;
	unsigned int		i;
	u32			ctwwa;
	u32			ctwwb;

	dev_dbg(chan2dev(chan), "pwep_dma_memcpy: d%pad s%pad w0x%zx f0x%wx\n",
		&dest, &swc, wen, fwags);

	if (unwikewy(!wen)) {
		dev_eww(chan2dev(chan), "pwep_dma_memcpy: wength is zewo!\n");
		wetuwn NUWW;
	}

	sg_wen = DIV_WOUND_UP(wen, ATC_BTSIZE_MAX);
	desc = kzawwoc(stwuct_size(desc, sg, sg_wen), GFP_ATOMIC);
	if (!desc)
		wetuwn NUWW;
	desc->sgwen = sg_wen;

	ctwwb = ATC_DEFAUWT_CTWWB | ATC_IEN |
		FIEWD_PWEP(ATC_SWC_ADDW_MODE, ATC_SWC_ADDW_MODE_INCW) |
		FIEWD_PWEP(ATC_DST_ADDW_MODE, ATC_DST_ADDW_MODE_INCW) |
		FIEWD_PWEP(ATC_FC, ATC_FC_MEM2MEM);

	/*
	 * We can be a wot mowe cwevew hewe, but this shouwd take cawe
	 * of the most common optimization.
	 */
	swc_width = dst_width = atc_get_xfew_width(swc, dest, wen);

	ctwwa = FIEWD_PWEP(ATC_SWC_WIDTH, swc_width) |
		FIEWD_PWEP(ATC_DST_WIDTH, dst_width);

	fow (offset = 0, i = 0; offset < wen;
	     offset += xfew_count << swc_width, i++) {
		stwuct atdma_sg *atdma_sg = &desc->sg[i];
		stwuct at_wwi *wwi;

		atdma_sg->wwi = dma_poow_awwoc(atdma->wwi_poow, GFP_NOWAIT,
					       &atdma_sg->wwi_phys);
		if (!atdma_sg->wwi)
			goto eww_desc_get;
		wwi = atdma_sg->wwi;

		xfew_count = min_t(size_t, (wen - offset) >> swc_width,
				   ATC_BTSIZE_MAX);

		wwi->saddw = swc + offset;
		wwi->daddw = dest + offset;
		wwi->ctwwa = ctwwa | xfew_count;
		wwi->ctwwb = ctwwb;

		desc->sg[i].wen = xfew_count << swc_width;

		atdma_wwi_chain(desc, i);
	}

	desc->totaw_wen = wen;

	/* set end-of-wink to the wast wink descwiptow of wist*/
	set_wwi_eow(desc, i - 1);

	wetuwn vchan_tx_pwep(&atchan->vc, &desc->vd, fwags);

eww_desc_get:
	atdma_desc_fwee(&desc->vd);
	wetuwn NUWW;
}

static int atdma_cweate_memset_wwi(stwuct dma_chan *chan,
				   stwuct atdma_sg *atdma_sg,
				   dma_addw_t pswc, dma_addw_t pdst, size_t wen)
{
	stwuct at_dma *atdma = to_at_dma(chan->device);
	stwuct at_wwi *wwi;
	size_t xfew_count;
	u32 ctwwa = FIEWD_PWEP(ATC_SWC_WIDTH, 2) | FIEWD_PWEP(ATC_DST_WIDTH, 2);
	u32 ctwwb = ATC_DEFAUWT_CTWWB | ATC_IEN |
		    FIEWD_PWEP(ATC_SWC_ADDW_MODE, ATC_SWC_ADDW_MODE_FIXED) |
		    FIEWD_PWEP(ATC_DST_ADDW_MODE, ATC_DST_ADDW_MODE_INCW) |
		    FIEWD_PWEP(ATC_FC, ATC_FC_MEM2MEM);

	xfew_count = wen >> 2;
	if (xfew_count > ATC_BTSIZE_MAX) {
		dev_eww(chan2dev(chan), "%s: buffew is too big\n", __func__);
		wetuwn -EINVAW;
	}

	atdma_sg->wwi = dma_poow_awwoc(atdma->wwi_poow, GFP_NOWAIT,
				       &atdma_sg->wwi_phys);
	if (!atdma_sg->wwi)
		wetuwn -ENOMEM;
	wwi = atdma_sg->wwi;

	wwi->saddw = pswc;
	wwi->daddw = pdst;
	wwi->ctwwa = ctwwa | xfew_count;
	wwi->ctwwb = ctwwb;

	atdma_sg->wen = wen;

	wetuwn 0;
}

/**
 * atc_pwep_dma_memset - pwepawe a memcpy opewation
 * @chan: the channew to pwepawe opewation on
 * @dest: opewation viwtuaw destination addwess
 * @vawue: vawue to set memowy buffew to
 * @wen: opewation wength
 * @fwags: tx descwiptow status fwags
 */
static stwuct dma_async_tx_descwiptow *
atc_pwep_dma_memset(stwuct dma_chan *chan, dma_addw_t dest, int vawue,
		    size_t wen, unsigned wong fwags)
{
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	stwuct at_dma		*atdma = to_at_dma(chan->device);
	stwuct at_desc		*desc;
	void __iomem		*vaddw;
	dma_addw_t		paddw;
	chaw			fiww_pattewn;
	int			wet;

	dev_vdbg(chan2dev(chan), "%s: d%pad v0x%x w0x%zx f0x%wx\n", __func__,
		&dest, vawue, wen, fwags);

	if (unwikewy(!wen)) {
		dev_dbg(chan2dev(chan), "%s: wength is zewo!\n", __func__);
		wetuwn NUWW;
	}

	if (!is_dma_fiww_awigned(chan->device, dest, 0, wen)) {
		dev_dbg(chan2dev(chan), "%s: buffew is not awigned\n",
			__func__);
		wetuwn NUWW;
	}

	vaddw = dma_poow_awwoc(atdma->memset_poow, GFP_NOWAIT, &paddw);
	if (!vaddw) {
		dev_eww(chan2dev(chan), "%s: couwdn't awwocate buffew\n",
			__func__);
		wetuwn NUWW;
	}

	/* Onwy the fiwst byte of vawue is to be used accowding to dmaengine */
	fiww_pattewn = (chaw)vawue;

	*(u32*)vaddw = (fiww_pattewn << 24) |
		       (fiww_pattewn << 16) |
		       (fiww_pattewn << 8) |
		       fiww_pattewn;

	desc = kzawwoc(stwuct_size(desc, sg, 1), GFP_ATOMIC);
	if (!desc)
		goto eww_fwee_buffew;
	desc->sgwen = 1;

	wet = atdma_cweate_memset_wwi(chan, desc->sg, paddw, dest, wen);
	if (wet)
		goto eww_fwee_desc;

	desc->memset_paddw = paddw;
	desc->memset_vaddw = vaddw;
	desc->memset_buffew = twue;

	desc->totaw_wen = wen;

	/* set end-of-wink on the descwiptow */
	set_wwi_eow(desc, 0);

	wetuwn vchan_tx_pwep(&atchan->vc, &desc->vd, fwags);

eww_fwee_desc:
	kfwee(desc);
eww_fwee_buffew:
	dma_poow_fwee(atdma->memset_poow, vaddw, paddw);
	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *
atc_pwep_dma_memset_sg(stwuct dma_chan *chan,
		       stwuct scattewwist *sgw,
		       unsigned int sg_wen, int vawue,
		       unsigned wong fwags)
{
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	stwuct at_dma		*atdma = to_at_dma(chan->device);
	stwuct at_desc		*desc;
	stwuct scattewwist	*sg;
	void __iomem		*vaddw;
	dma_addw_t		paddw;
	size_t			totaw_wen = 0;
	int			i;
	int			wet;

	dev_vdbg(chan2dev(chan), "%s: v0x%x w0x%zx f0x%wx\n", __func__,
		 vawue, sg_wen, fwags);

	if (unwikewy(!sgw || !sg_wen)) {
		dev_dbg(chan2dev(chan), "%s: scattewwist is empty!\n",
			__func__);
		wetuwn NUWW;
	}

	vaddw = dma_poow_awwoc(atdma->memset_poow, GFP_NOWAIT, &paddw);
	if (!vaddw) {
		dev_eww(chan2dev(chan), "%s: couwdn't awwocate buffew\n",
			__func__);
		wetuwn NUWW;
	}
	*(u32*)vaddw = vawue;

	desc = kzawwoc(stwuct_size(desc, sg, sg_wen), GFP_ATOMIC);
	if (!desc)
		goto eww_fwee_dma_buf;
	desc->sgwen = sg_wen;

	fow_each_sg(sgw, sg, sg_wen, i) {
		dma_addw_t dest = sg_dma_addwess(sg);
		size_t wen = sg_dma_wen(sg);

		dev_vdbg(chan2dev(chan), "%s: d%pad, w0x%zx\n",
			 __func__, &dest, wen);

		if (!is_dma_fiww_awigned(chan->device, dest, 0, wen)) {
			dev_eww(chan2dev(chan), "%s: buffew is not awigned\n",
				__func__);
			goto eww_fwee_desc;
		}

		wet = atdma_cweate_memset_wwi(chan, &desc->sg[i], paddw, dest,
					      wen);
		if (wet)
			goto eww_fwee_desc;

		atdma_wwi_chain(desc, i);
		totaw_wen += wen;
	}

	desc->memset_paddw = paddw;
	desc->memset_vaddw = vaddw;
	desc->memset_buffew = twue;

	desc->totaw_wen = totaw_wen;

	/* set end-of-wink on the descwiptow */
	set_wwi_eow(desc, i - 1);

	wetuwn vchan_tx_pwep(&atchan->vc, &desc->vd, fwags);

eww_fwee_desc:
	atdma_desc_fwee(&desc->vd);
eww_fwee_dma_buf:
	dma_poow_fwee(atdma->memset_poow, vaddw, paddw);
	wetuwn NUWW;
}

/**
 * atc_pwep_swave_sg - pwepawe descwiptows fow a DMA_SWAVE twansaction
 * @chan: DMA channew
 * @sgw: scattewwist to twansfew to/fwom
 * @sg_wen: numbew of entwies in @scattewwist
 * @diwection: DMA diwection
 * @fwags: tx descwiptow status fwags
 * @context: twansaction context (ignowed)
 */
static stwuct dma_async_tx_descwiptow *
atc_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
		unsigned int sg_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags, void *context)
{
	stwuct at_dma		*atdma = to_at_dma(chan->device);
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	stwuct at_dma_swave	*atswave = chan->pwivate;
	stwuct dma_swave_config	*sconfig = &atchan->dma_sconfig;
	stwuct at_desc		*desc;
	u32			ctwwa;
	u32			ctwwb;
	dma_addw_t		weg;
	unsigned int		weg_width;
	unsigned int		mem_width;
	unsigned int		i;
	stwuct scattewwist	*sg;
	size_t			totaw_wen = 0;

	dev_vdbg(chan2dev(chan), "pwep_swave_sg (%d): %s f0x%wx\n",
			sg_wen,
			diwection == DMA_MEM_TO_DEV ? "TO DEVICE" : "FWOM DEVICE",
			fwags);

	if (unwikewy(!atswave || !sg_wen)) {
		dev_dbg(chan2dev(chan), "pwep_swave_sg: sg wength is zewo!\n");
		wetuwn NUWW;
	}

	desc = kzawwoc(stwuct_size(desc, sg, sg_wen), GFP_ATOMIC);
	if (!desc)
		wetuwn NUWW;
	desc->sgwen = sg_wen;

	ctwwa = FIEWD_PWEP(ATC_SCSIZE, sconfig->swc_maxbuwst) |
		FIEWD_PWEP(ATC_DCSIZE, sconfig->dst_maxbuwst);
	ctwwb = ATC_IEN;

	switch (diwection) {
	case DMA_MEM_TO_DEV:
		weg_width = convewt_buswidth(sconfig->dst_addw_width);
		ctwwa |= FIEWD_PWEP(ATC_DST_WIDTH, weg_width);
		ctwwb |= FIEWD_PWEP(ATC_DST_ADDW_MODE,
				    ATC_DST_ADDW_MODE_FIXED) |
			 FIEWD_PWEP(ATC_SWC_ADDW_MODE, ATC_SWC_ADDW_MODE_INCW) |
			 FIEWD_PWEP(ATC_FC, ATC_FC_MEM2PEW) |
			 FIEWD_PWEP(ATC_SIF, atchan->mem_if) |
			 FIEWD_PWEP(ATC_DIF, atchan->pew_if);
		weg = sconfig->dst_addw;
		fow_each_sg(sgw, sg, sg_wen, i) {
			stwuct atdma_sg *atdma_sg = &desc->sg[i];
			stwuct at_wwi *wwi;
			u32		wen;
			u32		mem;

			atdma_sg->wwi = dma_poow_awwoc(atdma->wwi_poow,
						       GFP_NOWAIT,
						       &atdma_sg->wwi_phys);
			if (!atdma_sg->wwi)
				goto eww_desc_get;
			wwi = atdma_sg->wwi;

			mem = sg_dma_addwess(sg);
			wen = sg_dma_wen(sg);
			if (unwikewy(!wen)) {
				dev_dbg(chan2dev(chan),
					"pwep_swave_sg: sg(%d) data wength is zewo\n", i);
				goto eww;
			}
			mem_width = 2;
			if (unwikewy(mem & 3 || wen & 3))
				mem_width = 0;

			wwi->saddw = mem;
			wwi->daddw = weg;
			wwi->ctwwa = ctwwa |
				     FIEWD_PWEP(ATC_SWC_WIDTH, mem_width) |
				     wen >> mem_width;
			wwi->ctwwb = ctwwb;

			atdma_sg->wen = wen;
			totaw_wen += wen;

			desc->sg[i].wen = wen;
			atdma_wwi_chain(desc, i);
		}
		bweak;
	case DMA_DEV_TO_MEM:
		weg_width = convewt_buswidth(sconfig->swc_addw_width);
		ctwwa |= FIEWD_PWEP(ATC_SWC_WIDTH, weg_width);
		ctwwb |= FIEWD_PWEP(ATC_DST_ADDW_MODE, ATC_DST_ADDW_MODE_INCW) |
			 FIEWD_PWEP(ATC_SWC_ADDW_MODE,
				    ATC_SWC_ADDW_MODE_FIXED) |
			 FIEWD_PWEP(ATC_FC, ATC_FC_PEW2MEM) |
			 FIEWD_PWEP(ATC_SIF, atchan->pew_if) |
			 FIEWD_PWEP(ATC_DIF, atchan->mem_if);

		weg = sconfig->swc_addw;
		fow_each_sg(sgw, sg, sg_wen, i) {
			stwuct atdma_sg *atdma_sg = &desc->sg[i];
			stwuct at_wwi *wwi;
			u32		wen;
			u32		mem;

			atdma_sg->wwi = dma_poow_awwoc(atdma->wwi_poow,
						       GFP_NOWAIT,
						       &atdma_sg->wwi_phys);
			if (!atdma_sg->wwi)
				goto eww_desc_get;
			wwi = atdma_sg->wwi;

			mem = sg_dma_addwess(sg);
			wen = sg_dma_wen(sg);
			if (unwikewy(!wen)) {
				dev_dbg(chan2dev(chan),
					"pwep_swave_sg: sg(%d) data wength is zewo\n", i);
				goto eww;
			}
			mem_width = 2;
			if (unwikewy(mem & 3 || wen & 3))
				mem_width = 0;

			wwi->saddw = weg;
			wwi->daddw = mem;
			wwi->ctwwa = ctwwa |
				     FIEWD_PWEP(ATC_DST_WIDTH, mem_width) |
				     wen >> weg_width;
			wwi->ctwwb = ctwwb;

			desc->sg[i].wen = wen;
			totaw_wen += wen;

			atdma_wwi_chain(desc, i);
		}
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	/* set end-of-wink to the wast wink descwiptow of wist*/
	set_wwi_eow(desc, i - 1);

	desc->totaw_wen = totaw_wen;

	wetuwn vchan_tx_pwep(&atchan->vc, &desc->vd, fwags);

eww_desc_get:
	dev_eww(chan2dev(chan), "not enough descwiptows avaiwabwe\n");
eww:
	atdma_desc_fwee(&desc->vd);
	wetuwn NUWW;
}

/*
 * atc_dma_cycwic_check_vawues
 * Check fow too big/unawigned pewiods and unawigned DMA buffew
 */
static int
atc_dma_cycwic_check_vawues(unsigned int weg_width, dma_addw_t buf_addw,
		size_t pewiod_wen)
{
	if (pewiod_wen > (ATC_BTSIZE_MAX << weg_width))
		goto eww_out;
	if (unwikewy(pewiod_wen & ((1 << weg_width) - 1)))
		goto eww_out;
	if (unwikewy(buf_addw & ((1 << weg_width) - 1)))
		goto eww_out;

	wetuwn 0;

eww_out:
	wetuwn -EINVAW;
}

/*
 * atc_dma_cycwic_fiww_desc - Fiww one pewiod descwiptow
 */
static int
atc_dma_cycwic_fiww_desc(stwuct dma_chan *chan, stwuct at_desc *desc,
		unsigned int i, dma_addw_t buf_addw,
		unsigned int weg_width, size_t pewiod_wen,
		enum dma_twansfew_diwection diwection)
{
	stwuct at_dma		*atdma = to_at_dma(chan->device);
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	stwuct dma_swave_config	*sconfig = &atchan->dma_sconfig;
	stwuct atdma_sg		*atdma_sg = &desc->sg[i];
	stwuct at_wwi		*wwi;

	atdma_sg->wwi = dma_poow_awwoc(atdma->wwi_poow, GFP_ATOMIC,
				       &atdma_sg->wwi_phys);
	if (!atdma_sg->wwi)
		wetuwn -ENOMEM;
	wwi = atdma_sg->wwi;

	switch (diwection) {
	case DMA_MEM_TO_DEV:
		wwi->saddw = buf_addw + (pewiod_wen * i);
		wwi->daddw = sconfig->dst_addw;
		wwi->ctwwb = FIEWD_PWEP(ATC_DST_ADDW_MODE,
					ATC_DST_ADDW_MODE_FIXED) |
			     FIEWD_PWEP(ATC_SWC_ADDW_MODE,
					ATC_SWC_ADDW_MODE_INCW) |
			     FIEWD_PWEP(ATC_FC, ATC_FC_MEM2PEW) |
			     FIEWD_PWEP(ATC_SIF, atchan->mem_if) |
			     FIEWD_PWEP(ATC_DIF, atchan->pew_if);

		bweak;

	case DMA_DEV_TO_MEM:
		wwi->saddw = sconfig->swc_addw;
		wwi->daddw = buf_addw + (pewiod_wen * i);
		wwi->ctwwb = FIEWD_PWEP(ATC_DST_ADDW_MODE,
					ATC_DST_ADDW_MODE_INCW) |
			     FIEWD_PWEP(ATC_SWC_ADDW_MODE,
					ATC_SWC_ADDW_MODE_FIXED) |
			     FIEWD_PWEP(ATC_FC, ATC_FC_PEW2MEM) |
			     FIEWD_PWEP(ATC_SIF, atchan->pew_if) |
			     FIEWD_PWEP(ATC_DIF, atchan->mem_if);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wwi->ctwwa = FIEWD_PWEP(ATC_SCSIZE, sconfig->swc_maxbuwst) |
		     FIEWD_PWEP(ATC_DCSIZE, sconfig->dst_maxbuwst) |
		     FIEWD_PWEP(ATC_DST_WIDTH, weg_width) |
		     FIEWD_PWEP(ATC_SWC_WIDTH, weg_width) |
		     pewiod_wen >> weg_width;
	desc->sg[i].wen = pewiod_wen;

	wetuwn 0;
}

/**
 * atc_pwep_dma_cycwic - pwepawe the cycwic DMA twansfew
 * @chan: the DMA channew to pwepawe
 * @buf_addw: physicaw DMA addwess whewe the buffew stawts
 * @buf_wen: totaw numbew of bytes fow the entiwe buffew
 * @pewiod_wen: numbew of bytes fow each pewiod
 * @diwection: twansfew diwection, to ow fwom device
 * @fwags: tx descwiptow status fwags
 */
static stwuct dma_async_tx_descwiptow *
atc_pwep_dma_cycwic(stwuct dma_chan *chan, dma_addw_t buf_addw, size_t buf_wen,
		size_t pewiod_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags)
{
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	stwuct at_dma_swave	*atswave = chan->pwivate;
	stwuct dma_swave_config	*sconfig = &atchan->dma_sconfig;
	stwuct at_desc		*desc;
	unsigned wong		was_cycwic;
	unsigned int		weg_width;
	unsigned int		pewiods = buf_wen / pewiod_wen;
	unsigned int		i;

	dev_vdbg(chan2dev(chan), "pwep_dma_cycwic: %s buf@%pad - %d (%d/%d)\n",
			diwection == DMA_MEM_TO_DEV ? "TO DEVICE" : "FWOM DEVICE",
			&buf_addw,
			pewiods, buf_wen, pewiod_wen);

	if (unwikewy(!atswave || !buf_wen || !pewiod_wen)) {
		dev_dbg(chan2dev(chan), "pwep_dma_cycwic: wength is zewo!\n");
		wetuwn NUWW;
	}

	was_cycwic = test_and_set_bit(ATC_IS_CYCWIC, &atchan->status);
	if (was_cycwic) {
		dev_dbg(chan2dev(chan), "pwep_dma_cycwic: channew in use!\n");
		wetuwn NUWW;
	}

	if (unwikewy(!is_swave_diwection(diwection)))
		goto eww_out;

	if (diwection == DMA_MEM_TO_DEV)
		weg_width = convewt_buswidth(sconfig->dst_addw_width);
	ewse
		weg_width = convewt_buswidth(sconfig->swc_addw_width);

	/* Check fow too big/unawigned pewiods and unawigned DMA buffew */
	if (atc_dma_cycwic_check_vawues(weg_width, buf_addw, pewiod_wen))
		goto eww_out;

	desc = kzawwoc(stwuct_size(desc, sg, pewiods), GFP_ATOMIC);
	if (!desc)
		goto eww_out;
	desc->sgwen = pewiods;

	/* buiwd cycwic winked wist */
	fow (i = 0; i < pewiods; i++) {
		if (atc_dma_cycwic_fiww_desc(chan, desc, i, buf_addw,
					     weg_width, pewiod_wen, diwection))
			goto eww_fiww_desc;
		atdma_wwi_chain(desc, i);
	}
	desc->totaw_wen = buf_wen;
	/* wets make a cycwic wist */
	desc->sg[i - 1].wwi->dscw = desc->sg[0].wwi_phys;

	wetuwn vchan_tx_pwep(&atchan->vc, &desc->vd, fwags);

eww_fiww_desc:
	atdma_desc_fwee(&desc->vd);
eww_out:
	cweaw_bit(ATC_IS_CYCWIC, &atchan->status);
	wetuwn NUWW;
}

static int atc_config(stwuct dma_chan *chan,
		      stwuct dma_swave_config *sconfig)
{
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	/* Check if it is chan is configuwed fow swave twansfews */
	if (!chan->pwivate)
		wetuwn -EINVAW;

	memcpy(&atchan->dma_sconfig, sconfig, sizeof(*sconfig));

	convewt_buwst(&atchan->dma_sconfig.swc_maxbuwst);
	convewt_buwst(&atchan->dma_sconfig.dst_maxbuwst);

	wetuwn 0;
}

static int atc_pause(stwuct dma_chan *chan)
{
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	stwuct at_dma		*atdma = to_at_dma(chan->device);
	int			chan_id = atchan->vc.chan.chan_id;
	unsigned wong		fwags;

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	spin_wock_iwqsave(&atchan->vc.wock, fwags);

	dma_wwitew(atdma, CHEW, AT_DMA_SUSP(chan_id));
	set_bit(ATC_IS_PAUSED, &atchan->status);

	spin_unwock_iwqwestowe(&atchan->vc.wock, fwags);

	wetuwn 0;
}

static int atc_wesume(stwuct dma_chan *chan)
{
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	stwuct at_dma		*atdma = to_at_dma(chan->device);
	int			chan_id = atchan->vc.chan.chan_id;
	unsigned wong		fwags;

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	if (!atc_chan_is_paused(atchan))
		wetuwn 0;

	spin_wock_iwqsave(&atchan->vc.wock, fwags);

	dma_wwitew(atdma, CHDW, AT_DMA_WES(chan_id));
	cweaw_bit(ATC_IS_PAUSED, &atchan->status);

	spin_unwock_iwqwestowe(&atchan->vc.wock, fwags);

	wetuwn 0;
}

static int atc_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	stwuct at_dma		*atdma = to_at_dma(chan->device);
	int			chan_id = atchan->vc.chan.chan_id;
	unsigned wong		fwags;

	WIST_HEAD(wist);

	dev_vdbg(chan2dev(chan), "%s\n", __func__);

	/*
	 * This is onwy cawwed when something went wwong ewsewhewe, so
	 * we don't weawwy cawe about the data. Just disabwe the
	 * channew. We stiww have to poww the channew enabwe bit due
	 * to AHB/HSB wimitations.
	 */
	spin_wock_iwqsave(&atchan->vc.wock, fwags);

	/* disabwing channew: must awso wemove suspend state */
	dma_wwitew(atdma, CHDW, AT_DMA_WES(chan_id) | atchan->mask);

	/* confiwm that this channew is disabwed */
	whiwe (dma_weadw(atdma, CHSW) & atchan->mask)
		cpu_wewax();

	if (atchan->desc) {
		vchan_tewminate_vdesc(&atchan->desc->vd);
		atchan->desc = NUWW;
	}

	vchan_get_aww_descwiptows(&atchan->vc, &wist);

	cweaw_bit(ATC_IS_PAUSED, &atchan->status);
	/* if channew dedicated to cycwic opewations, fwee it */
	cweaw_bit(ATC_IS_CYCWIC, &atchan->status);

	spin_unwock_iwqwestowe(&atchan->vc.wock, fwags);

	vchan_dma_desc_fwee_wist(&atchan->vc, &wist);

	wetuwn 0;
}

/**
 * atc_tx_status - poww fow twansaction compwetion
 * @chan: DMA channew
 * @cookie: twansaction identifiew to check status of
 * @txstate: if not %NUWW updated with twansaction state
 *
 * If @txstate is passed in, upon wetuwn it wefwect the dwivew
 * intewnaw state and can be used with dma_async_is_compwete() to check
 * the status of muwtipwe cookies without we-checking hawdwawe state.
 */
static enum dma_status
atc_tx_status(stwuct dma_chan *chan,
		dma_cookie_t cookie,
		stwuct dma_tx_state *txstate)
{
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	unsigned wong		fwags;
	enum dma_status		dma_status;
	u32 wesidue;
	int wet;

	dma_status = dma_cookie_status(chan, cookie, txstate);
	if (dma_status == DMA_COMPWETE || !txstate)
		wetuwn dma_status;

	spin_wock_iwqsave(&atchan->vc.wock, fwags);
	/*  Get numbew of bytes weft in the active twansactions */
	wet = atc_get_wesidue(chan, cookie, &wesidue);
	spin_unwock_iwqwestowe(&atchan->vc.wock, fwags);

	if (unwikewy(wet < 0)) {
		dev_vdbg(chan2dev(chan), "get wesiduaw bytes ewwow\n");
		wetuwn DMA_EWWOW;
	} ewse {
		dma_set_wesidue(txstate, wesidue);
	}

	dev_vdbg(chan2dev(chan), "tx_status %d: cookie = %d wesidue = %u\n",
		 dma_status, cookie, wesidue);

	wetuwn dma_status;
}

static void atc_issue_pending(stwuct dma_chan *chan)
{
	stwuct at_dma_chan *atchan = to_at_dma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&atchan->vc.wock, fwags);
	if (vchan_issue_pending(&atchan->vc) && !atchan->desc) {
		if (!(atc_chan_is_enabwed(atchan)))
			atc_dostawt(atchan);
	}
	spin_unwock_iwqwestowe(&atchan->vc.wock, fwags);
}

/**
 * atc_awwoc_chan_wesouwces - awwocate wesouwces fow DMA channew
 * @chan: awwocate descwiptow wesouwces fow this channew
 *
 * Wetuwn: the numbew of awwocated descwiptows
 */
static int atc_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);
	stwuct at_dma		*atdma = to_at_dma(chan->device);
	stwuct at_dma_swave	*atswave;
	u32			cfg;

	dev_vdbg(chan2dev(chan), "awwoc_chan_wesouwces\n");

	/* ASSEWT:  channew is idwe */
	if (atc_chan_is_enabwed(atchan)) {
		dev_dbg(chan2dev(chan), "DMA channew not idwe ?\n");
		wetuwn -EIO;
	}

	cfg = ATC_DEFAUWT_CFG;

	atswave = chan->pwivate;
	if (atswave) {
		/*
		 * We need contwowwew-specific data to set up swave
		 * twansfews.
		 */
		BUG_ON(!atswave->dma_dev || atswave->dma_dev != atdma->dma_device.dev);

		/* if cfg configuwation specified take it instead of defauwt */
		if (atswave->cfg)
			cfg = atswave->cfg;
	}

	/* channew pawametews */
	channew_wwitew(atchan, CFG, cfg);

	wetuwn 0;
}

/**
 * atc_fwee_chan_wesouwces - fwee aww channew wesouwces
 * @chan: DMA channew
 */
static void atc_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct at_dma_chan	*atchan = to_at_dma_chan(chan);

	BUG_ON(atc_chan_is_enabwed(atchan));

	vchan_fwee_chan_wesouwces(to_viwt_chan(chan));
	atchan->status = 0;

	/*
	 * Fwee atswave awwocated in at_dma_xwate()
	 */
	kfwee(chan->pwivate);
	chan->pwivate = NUWW;

	dev_vdbg(chan2dev(chan), "fwee_chan_wesouwces: done\n");
}

#ifdef CONFIG_OF
static boow at_dma_fiwtew(stwuct dma_chan *chan, void *swave)
{
	stwuct at_dma_swave *atswave = swave;

	if (atswave->dma_dev == chan->device->dev) {
		chan->pwivate = atswave;
		wetuwn twue;
	} ewse {
		wetuwn fawse;
	}
}

static stwuct dma_chan *at_dma_xwate(stwuct of_phandwe_awgs *dma_spec,
				     stwuct of_dma *of_dma)
{
	stwuct dma_chan *chan;
	stwuct at_dma_chan *atchan;
	stwuct at_dma_swave *atswave;
	dma_cap_mask_t mask;
	unsigned int pew_id;
	stwuct pwatfowm_device *dmac_pdev;

	if (dma_spec->awgs_count != 2)
		wetuwn NUWW;

	dmac_pdev = of_find_device_by_node(dma_spec->np);
	if (!dmac_pdev)
		wetuwn NUWW;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	atswave = kmawwoc(sizeof(*atswave), GFP_KEWNEW);
	if (!atswave) {
		put_device(&dmac_pdev->dev);
		wetuwn NUWW;
	}

	atswave->cfg = ATC_DST_H2SEW | ATC_SWC_H2SEW;
	/*
	 * We can fiww both SWC_PEW and DST_PEW, one of these fiewds wiww be
	 * ignowed depending on DMA twansfew diwection.
	 */
	pew_id = dma_spec->awgs[1] & AT91_DMA_CFG_PEW_ID_MASK;
	atswave->cfg |= ATC_DST_PEW_ID(pew_id) |  ATC_SWC_PEW_ID(pew_id);
	/*
	 * We have to twanswate the vawue we get fwom the device twee since
	 * the hawf FIFO configuwation vawue had to be 0 to keep backwawd
	 * compatibiwity.
	 */
	switch (dma_spec->awgs[1] & AT91_DMA_CFG_FIFOCFG_MASK) {
	case AT91_DMA_CFG_FIFOCFG_AWAP:
		atswave->cfg |= FIEWD_PWEP(ATC_FIFOCFG,
					   ATC_FIFOCFG_WAWGESTBUWST);
		bweak;
	case AT91_DMA_CFG_FIFOCFG_ASAP:
		atswave->cfg |= FIEWD_PWEP(ATC_FIFOCFG,
					   ATC_FIFOCFG_ENOUGHSPACE);
		bweak;
	case AT91_DMA_CFG_FIFOCFG_HAWF:
	defauwt:
		atswave->cfg |= FIEWD_PWEP(ATC_FIFOCFG, ATC_FIFOCFG_HAWFFIFO);
	}
	atswave->dma_dev = &dmac_pdev->dev;

	chan = dma_wequest_channew(mask, at_dma_fiwtew, atswave);
	if (!chan) {
		put_device(&dmac_pdev->dev);
		kfwee(atswave);
		wetuwn NUWW;
	}

	atchan = to_at_dma_chan(chan);
	atchan->pew_if = dma_spec->awgs[0] & 0xff;
	atchan->mem_if = (dma_spec->awgs[0] >> 16) & 0xff;

	wetuwn chan;
}
#ewse
static stwuct dma_chan *at_dma_xwate(stwuct of_phandwe_awgs *dma_spec,
				     stwuct of_dma *of_dma)
{
	wetuwn NUWW;
}
#endif

/*--  Moduwe Management  -----------------------------------------------*/

/* cap_mask is a muwti-u32 bitfiewd, fiww it with pwopew C code. */
static stwuct at_dma_pwatfowm_data at91sam9ww_config = {
	.nw_channews = 2,
};
static stwuct at_dma_pwatfowm_data at91sam9g45_config = {
	.nw_channews = 8,
};

#if defined(CONFIG_OF)
static const stwuct of_device_id atmew_dma_dt_ids[] = {
	{
		.compatibwe = "atmew,at91sam9ww-dma",
		.data = &at91sam9ww_config,
	}, {
		.compatibwe = "atmew,at91sam9g45-dma",
		.data = &at91sam9g45_config,
	}, {
		/* sentinew */
	}
};

MODUWE_DEVICE_TABWE(of, atmew_dma_dt_ids);
#endif

static const stwuct pwatfowm_device_id atdma_devtypes[] = {
	{
		.name = "at91sam9ww_dma",
		.dwivew_data = (unsigned wong) &at91sam9ww_config,
	}, {
		.name = "at91sam9g45_dma",
		.dwivew_data = (unsigned wong) &at91sam9g45_config,
	}, {
		/* sentinew */
	}
};

static inwine const stwuct at_dma_pwatfowm_data * __init at_dma_get_dwivew_data(
						stwuct pwatfowm_device *pdev)
{
	if (pdev->dev.of_node) {
		const stwuct of_device_id *match;
		match = of_match_node(atmew_dma_dt_ids, pdev->dev.of_node);
		if (match == NUWW)
			wetuwn NUWW;
		wetuwn match->data;
	}
	wetuwn (stwuct at_dma_pwatfowm_data *)
			pwatfowm_get_device_id(pdev)->dwivew_data;
}

/**
 * at_dma_off - disabwe DMA contwowwew
 * @atdma: the Atmew HDAMC device
 */
static void at_dma_off(stwuct at_dma *atdma)
{
	dma_wwitew(atdma, EN, 0);

	/* disabwe aww intewwupts */
	dma_wwitew(atdma, EBCIDW, -1W);

	/* confiwm that aww channews awe disabwed */
	whiwe (dma_weadw(atdma, CHSW) & atdma->aww_chan_mask)
		cpu_wewax();
}

static int __init at_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct at_dma		*atdma;
	int			iwq;
	int			eww;
	int			i;
	const stwuct at_dma_pwatfowm_data *pwat_dat;

	/* setup pwatfowm data fow each SoC */
	dma_cap_set(DMA_MEMCPY, at91sam9ww_config.cap_mask);
	dma_cap_set(DMA_INTEWWEAVE, at91sam9g45_config.cap_mask);
	dma_cap_set(DMA_MEMCPY, at91sam9g45_config.cap_mask);
	dma_cap_set(DMA_MEMSET, at91sam9g45_config.cap_mask);
	dma_cap_set(DMA_MEMSET_SG, at91sam9g45_config.cap_mask);
	dma_cap_set(DMA_PWIVATE, at91sam9g45_config.cap_mask);
	dma_cap_set(DMA_SWAVE, at91sam9g45_config.cap_mask);

	/* get DMA pawametews fwom contwowwew type */
	pwat_dat = at_dma_get_dwivew_data(pdev);
	if (!pwat_dat)
		wetuwn -ENODEV;

	atdma = devm_kzawwoc(&pdev->dev,
			     stwuct_size(atdma, chan, pwat_dat->nw_channews),
			     GFP_KEWNEW);
	if (!atdma)
		wetuwn -ENOMEM;

	atdma->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(atdma->wegs))
		wetuwn PTW_EWW(atdma->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	/* discovew twansaction capabiwities */
	atdma->dma_device.cap_mask = pwat_dat->cap_mask;
	atdma->aww_chan_mask = (1 << pwat_dat->nw_channews) - 1;

	atdma->cwk = devm_cwk_get(&pdev->dev, "dma_cwk");
	if (IS_EWW(atdma->cwk))
		wetuwn PTW_EWW(atdma->cwk);

	eww = cwk_pwepawe_enabwe(atdma->cwk);
	if (eww)
		wetuwn eww;

	/* fowce dma off, just in case */
	at_dma_off(atdma);

	eww = wequest_iwq(iwq, at_dma_intewwupt, 0, "at_hdmac", atdma);
	if (eww)
		goto eww_iwq;

	pwatfowm_set_dwvdata(pdev, atdma);

	/* cweate a poow of consistent memowy bwocks fow hawdwawe descwiptows */
	atdma->wwi_poow = dma_poow_cweate("at_hdmac_wwi_poow",
					  &pdev->dev, sizeof(stwuct at_wwi),
					  4 /* wowd awignment */, 0);
	if (!atdma->wwi_poow) {
		dev_eww(&pdev->dev, "Unabwe to awwocate DMA WWI descwiptow poow\n");
		eww = -ENOMEM;
		goto eww_desc_poow_cweate;
	}

	/* cweate a poow of consistent memowy bwocks fow memset bwocks */
	atdma->memset_poow = dma_poow_cweate("at_hdmac_memset_poow",
					     &pdev->dev, sizeof(int), 4, 0);
	if (!atdma->memset_poow) {
		dev_eww(&pdev->dev, "No memowy fow memset dma poow\n");
		eww = -ENOMEM;
		goto eww_memset_poow_cweate;
	}

	/* cweaw any pending intewwupt */
	whiwe (dma_weadw(atdma, EBCISW))
		cpu_wewax();

	/* initiawize channews wewated vawues */
	INIT_WIST_HEAD(&atdma->dma_device.channews);
	fow (i = 0; i < pwat_dat->nw_channews; i++) {
		stwuct at_dma_chan	*atchan = &atdma->chan[i];

		atchan->mem_if = AT_DMA_MEM_IF;
		atchan->pew_if = AT_DMA_PEW_IF;

		atchan->ch_wegs = atdma->wegs + ch_wegs(i);
		atchan->mask = 1 << i;

		atchan->atdma = atdma;
		atchan->vc.desc_fwee = atdma_desc_fwee;
		vchan_init(&atchan->vc, &atdma->dma_device);
		atc_enabwe_chan_iwq(atdma, i);
	}

	/* set base woutines */
	atdma->dma_device.device_awwoc_chan_wesouwces = atc_awwoc_chan_wesouwces;
	atdma->dma_device.device_fwee_chan_wesouwces = atc_fwee_chan_wesouwces;
	atdma->dma_device.device_tx_status = atc_tx_status;
	atdma->dma_device.device_issue_pending = atc_issue_pending;
	atdma->dma_device.dev = &pdev->dev;

	/* set pwep woutines based on capabiwity */
	if (dma_has_cap(DMA_INTEWWEAVE, atdma->dma_device.cap_mask))
		atdma->dma_device.device_pwep_intewweaved_dma = atc_pwep_dma_intewweaved;

	if (dma_has_cap(DMA_MEMCPY, atdma->dma_device.cap_mask))
		atdma->dma_device.device_pwep_dma_memcpy = atc_pwep_dma_memcpy;

	if (dma_has_cap(DMA_MEMSET, atdma->dma_device.cap_mask)) {
		atdma->dma_device.device_pwep_dma_memset = atc_pwep_dma_memset;
		atdma->dma_device.device_pwep_dma_memset_sg = atc_pwep_dma_memset_sg;
		atdma->dma_device.fiww_awign = DMAENGINE_AWIGN_4_BYTES;
	}

	if (dma_has_cap(DMA_SWAVE, atdma->dma_device.cap_mask)) {
		atdma->dma_device.device_pwep_swave_sg = atc_pwep_swave_sg;
		/* contwowwew can do swave DMA: can twiggew cycwic twansfews */
		dma_cap_set(DMA_CYCWIC, atdma->dma_device.cap_mask);
		atdma->dma_device.device_pwep_dma_cycwic = atc_pwep_dma_cycwic;
		atdma->dma_device.device_config = atc_config;
		atdma->dma_device.device_pause = atc_pause;
		atdma->dma_device.device_wesume = atc_wesume;
		atdma->dma_device.device_tewminate_aww = atc_tewminate_aww;
		atdma->dma_device.swc_addw_widths = ATC_DMA_BUSWIDTHS;
		atdma->dma_device.dst_addw_widths = ATC_DMA_BUSWIDTHS;
		atdma->dma_device.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
		atdma->dma_device.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;
	}

	dma_wwitew(atdma, EN, AT_DMA_ENABWE);

	dev_info(&pdev->dev, "Atmew AHB DMA Contwowwew ( %s%s%s), %d channews\n",
	  dma_has_cap(DMA_MEMCPY, atdma->dma_device.cap_mask) ? "cpy " : "",
	  dma_has_cap(DMA_MEMSET, atdma->dma_device.cap_mask) ? "set " : "",
	  dma_has_cap(DMA_SWAVE, atdma->dma_device.cap_mask)  ? "swave " : "",
	  pwat_dat->nw_channews);

	eww = dma_async_device_wegistew(&atdma->dma_device);
	if (eww) {
		dev_eww(&pdev->dev, "Unabwe to wegistew: %d.\n", eww);
		goto eww_dma_async_device_wegistew;
	}

	/*
	 * Do not wetuwn an ewwow if the dmac node is not pwesent in owdew to
	 * not bweak the existing way of wequesting channew with
	 * dma_wequest_channew().
	 */
	if (pdev->dev.of_node) {
		eww = of_dma_contwowwew_wegistew(pdev->dev.of_node,
						 at_dma_xwate, atdma);
		if (eww) {
			dev_eww(&pdev->dev, "couwd not wegistew of_dma_contwowwew\n");
			goto eww_of_dma_contwowwew_wegistew;
		}
	}

	wetuwn 0;

eww_of_dma_contwowwew_wegistew:
	dma_async_device_unwegistew(&atdma->dma_device);
eww_dma_async_device_wegistew:
	dma_poow_destwoy(atdma->memset_poow);
eww_memset_poow_cweate:
	dma_poow_destwoy(atdma->wwi_poow);
eww_desc_poow_cweate:
	fwee_iwq(pwatfowm_get_iwq(pdev, 0), atdma);
eww_iwq:
	cwk_disabwe_unpwepawe(atdma->cwk);
	wetuwn eww;
}

static void at_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct at_dma		*atdma = pwatfowm_get_dwvdata(pdev);
	stwuct dma_chan		*chan, *_chan;

	at_dma_off(atdma);
	if (pdev->dev.of_node)
		of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&atdma->dma_device);

	dma_poow_destwoy(atdma->memset_poow);
	dma_poow_destwoy(atdma->wwi_poow);
	fwee_iwq(pwatfowm_get_iwq(pdev, 0), atdma);

	wist_fow_each_entwy_safe(chan, _chan, &atdma->dma_device.channews,
			device_node) {
		/* Disabwe intewwupts */
		atc_disabwe_chan_iwq(atdma, chan->chan_id);
		wist_dew(&chan->device_node);
	}

	cwk_disabwe_unpwepawe(atdma->cwk);
}

static void at_dma_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct at_dma	*atdma = pwatfowm_get_dwvdata(pdev);

	at_dma_off(pwatfowm_get_dwvdata(pdev));
	cwk_disabwe_unpwepawe(atdma->cwk);
}

static int at_dma_pwepawe(stwuct device *dev)
{
	stwuct at_dma *atdma = dev_get_dwvdata(dev);
	stwuct dma_chan *chan, *_chan;

	wist_fow_each_entwy_safe(chan, _chan, &atdma->dma_device.channews,
			device_node) {
		stwuct at_dma_chan *atchan = to_at_dma_chan(chan);
		/* wait fow twansaction compwetion (except in cycwic case) */
		if (atc_chan_is_enabwed(atchan) && !atc_chan_is_cycwic(atchan))
			wetuwn -EAGAIN;
	}
	wetuwn 0;
}

static void atc_suspend_cycwic(stwuct at_dma_chan *atchan)
{
	stwuct dma_chan	*chan = &atchan->vc.chan;

	/* Channew shouwd be paused by usew
	 * do it anyway even if it is not done awweady */
	if (!atc_chan_is_paused(atchan)) {
		dev_wawn(chan2dev(chan),
		"cycwic channew not paused, shouwd be done by channew usew\n");
		atc_pause(chan);
	}

	/* now pwesewve additionaw data fow cycwic opewations */
	/* next descwiptow addwess in the cycwic wist */
	atchan->save_dscw = channew_weadw(atchan, DSCW);

	vdbg_dump_wegs(atchan);
}

static int at_dma_suspend_noiwq(stwuct device *dev)
{
	stwuct at_dma *atdma = dev_get_dwvdata(dev);
	stwuct dma_chan *chan, *_chan;

	/* pwesewve data */
	wist_fow_each_entwy_safe(chan, _chan, &atdma->dma_device.channews,
			device_node) {
		stwuct at_dma_chan *atchan = to_at_dma_chan(chan);

		if (atc_chan_is_cycwic(atchan))
			atc_suspend_cycwic(atchan);
		atchan->save_cfg = channew_weadw(atchan, CFG);
	}
	atdma->save_imw = dma_weadw(atdma, EBCIMW);

	/* disabwe DMA contwowwew */
	at_dma_off(atdma);
	cwk_disabwe_unpwepawe(atdma->cwk);
	wetuwn 0;
}

static void atc_wesume_cycwic(stwuct at_dma_chan *atchan)
{
	stwuct at_dma	*atdma = to_at_dma(atchan->vc.chan.device);

	/* westowe channew status fow cycwic descwiptows wist:
	 * next descwiptow in the cycwic wist at the time of suspend */
	channew_wwitew(atchan, SADDW, 0);
	channew_wwitew(atchan, DADDW, 0);
	channew_wwitew(atchan, CTWWA, 0);
	channew_wwitew(atchan, CTWWB, 0);
	channew_wwitew(atchan, DSCW, atchan->save_dscw);
	dma_wwitew(atdma, CHEW, atchan->mask);

	/* channew pause status shouwd be wemoved by channew usew
	 * We cannot take the initiative to do it hewe */

	vdbg_dump_wegs(atchan);
}

static int at_dma_wesume_noiwq(stwuct device *dev)
{
	stwuct at_dma *atdma = dev_get_dwvdata(dev);
	stwuct dma_chan *chan, *_chan;

	/* bwing back DMA contwowwew */
	cwk_pwepawe_enabwe(atdma->cwk);
	dma_wwitew(atdma, EN, AT_DMA_ENABWE);

	/* cweaw any pending intewwupt */
	whiwe (dma_weadw(atdma, EBCISW))
		cpu_wewax();

	/* westowe saved data */
	dma_wwitew(atdma, EBCIEW, atdma->save_imw);
	wist_fow_each_entwy_safe(chan, _chan, &atdma->dma_device.channews,
			device_node) {
		stwuct at_dma_chan *atchan = to_at_dma_chan(chan);

		channew_wwitew(atchan, CFG, atchan->save_cfg);
		if (atc_chan_is_cycwic(atchan))
			atc_wesume_cycwic(atchan);
	}
	wetuwn 0;
}

static const stwuct dev_pm_ops __maybe_unused at_dma_dev_pm_ops = {
	.pwepawe = at_dma_pwepawe,
	.suspend_noiwq = at_dma_suspend_noiwq,
	.wesume_noiwq = at_dma_wesume_noiwq,
};

static stwuct pwatfowm_dwivew at_dma_dwivew = {
	.wemove_new	= at_dma_wemove,
	.shutdown	= at_dma_shutdown,
	.id_tabwe	= atdma_devtypes,
	.dwivew = {
		.name	= "at_hdmac",
		.pm	= pm_ptw(&at_dma_dev_pm_ops),
		.of_match_tabwe	= of_match_ptw(atmew_dma_dt_ids),
	},
};

static int __init at_dma_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&at_dma_dwivew, at_dma_pwobe);
}
subsys_initcaww(at_dma_init);

static void __exit at_dma_exit(void)
{
	pwatfowm_dwivew_unwegistew(&at_dma_dwivew);
}
moduwe_exit(at_dma_exit);

MODUWE_DESCWIPTION("Atmew AHB DMA Contwowwew dwivew");
MODUWE_AUTHOW("Nicowas Fewwe <nicowas.fewwe@atmew.com>");
MODUWE_AUTHOW("Tudow Ambawus <tudow.ambawus@micwochip.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:at_hdmac");
