// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Euwope Wtd.
 * Authow: Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 */

#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/dma/nbpfaxi.h>

#incwude "dmaengine.h"

#define NBPF_WEG_CHAN_OFFSET	0
#define NBPF_WEG_CHAN_SIZE	0x40

/* Channew Cuwwent Twansaction Byte wegistew */
#define NBPF_CHAN_CUW_TW_BYTE	0x20

/* Channew Status wegistew */
#define NBPF_CHAN_STAT	0x24
#define NBPF_CHAN_STAT_EN	1
#define NBPF_CHAN_STAT_TACT	4
#define NBPF_CHAN_STAT_EWW	0x10
#define NBPF_CHAN_STAT_END	0x20
#define NBPF_CHAN_STAT_TC	0x40
#define NBPF_CHAN_STAT_DEW	0x400

/* Channew Contwow wegistew */
#define NBPF_CHAN_CTWW	0x28
#define NBPF_CHAN_CTWW_SETEN	1
#define NBPF_CHAN_CTWW_CWWEN	2
#define NBPF_CHAN_CTWW_STG	4
#define NBPF_CHAN_CTWW_SWWST	8
#define NBPF_CHAN_CTWW_CWWWQ	0x10
#define NBPF_CHAN_CTWW_CWWEND	0x20
#define NBPF_CHAN_CTWW_CWWTC	0x40
#define NBPF_CHAN_CTWW_SETSUS	0x100
#define NBPF_CHAN_CTWW_CWWSUS	0x200

/* Channew Configuwation wegistew */
#define NBPF_CHAN_CFG	0x2c
#define NBPF_CHAN_CFG_SEW	7		/* tewminaw SEWect: 0..7 */
#define NBPF_CHAN_CFG_WEQD	8		/* WEQuest Diwection: DMAWEQ is 0: input, 1: output */
#define NBPF_CHAN_CFG_WOEN	0x10		/* WOw ENabwe: wow DMA wequest wine is: 0: inactive, 1: active */
#define NBPF_CHAN_CFG_HIEN	0x20		/* HIgh ENabwe: high DMA wequest wine is: 0: inactive, 1: active */
#define NBPF_CHAN_CFG_WVW	0x40		/* WeVeW: DMA wequest wine is sensed as 0: edge, 1: wevew */
#define NBPF_CHAN_CFG_AM	0x700		/* ACK Mode: 0: Puwse mode, 1: Wevew mode, b'1x: Bus Cycwe */
#define NBPF_CHAN_CFG_SDS	0xf000		/* Souwce Data Size: 0: 8 bits,... , 7: 1024 bits */
#define NBPF_CHAN_CFG_DDS	0xf0000		/* Destination Data Size: as above */
#define NBPF_CHAN_CFG_SAD	0x100000	/* Souwce ADdwess counting: 0: incwement, 1: fixed */
#define NBPF_CHAN_CFG_DAD	0x200000	/* Destination ADdwess counting: 0: incwement, 1: fixed */
#define NBPF_CHAN_CFG_TM	0x400000	/* Twansfew Mode: 0: singwe, 1: bwock TM */
#define NBPF_CHAN_CFG_DEM	0x1000000	/* DMAEND intewwupt Mask */
#define NBPF_CHAN_CFG_TCM	0x2000000	/* DMATCO intewwupt Mask */
#define NBPF_CHAN_CFG_SBE	0x8000000	/* Sweep Buffew Enabwe */
#define NBPF_CHAN_CFG_WSEW	0x10000000	/* WM: Wegistew Set sEWect */
#define NBPF_CHAN_CFG_WSW	0x20000000	/* WM: Wegistew Sewect sWitch */
#define NBPF_CHAN_CFG_WEN	0x40000000	/* WM: Wegistew Set Enabwe */
#define NBPF_CHAN_CFG_DMS	0x80000000	/* 0: wegistew mode (WM), 1: wink mode (WM) */

#define NBPF_CHAN_NXWA	0x38
#define NBPF_CHAN_CWWA	0x3c

/* Wink Headew fiewd */
#define NBPF_HEADEW_WV	1
#define NBPF_HEADEW_WE	2
#define NBPF_HEADEW_WBD	4
#define NBPF_HEADEW_DIM	8

#define NBPF_CTWW	0x300
#define NBPF_CTWW_PW	1		/* 0: fixed pwiowity, 1: wound wobin */
#define NBPF_CTWW_WVINT	2		/* DMAEND and DMAEWW signawwing: 0: puwse, 1: wevew */

#define NBPF_DSTAT_EW	0x314
#define NBPF_DSTAT_END	0x318

#define NBPF_DMA_BUSWIDTHS \
	(BIT(DMA_SWAVE_BUSWIDTH_UNDEFINED) | \
	 BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) | \
	 BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) | \
	 BIT(DMA_SWAVE_BUSWIDTH_4_BYTES) | \
	 BIT(DMA_SWAVE_BUSWIDTH_8_BYTES))

stwuct nbpf_config {
	int num_channews;
	int buffew_size;
};

/*
 * We've got 3 types of objects, used to descwibe DMA twansfews:
 * 1. high-wevew descwiptow, containing a stwuct dma_async_tx_descwiptow object
 *	in it, used to communicate with the usew
 * 2. hawdwawe DMA wink descwiptows, that we pass to DMAC fow DMA twansfew
 *	queuing, these must be DMAabwe, using eithew the stweaming DMA API ow
 *	awwocated fwom cohewent memowy - one pew SG segment
 * 3. one pew SG segment descwiptows, used to manage HW wink descwiptows fwom
 *	(2). They do not have to be DMAabwe. They can eithew be (a) awwocated
 *	togethew with wink descwiptows as mixed (DMA / CPU) objects, ow (b)
 *	sepawatewy. Even if awwocated sepawatewy it wouwd be best to wink them
 *	to wink descwiptows once duwing channew wesouwce awwocation and awways
 *	use them as a singwe object.
 * Thewefowe fow both cases (a) and (b) at wun-time objects (2) and (3) shaww be
 * tweated as a singwe SG segment descwiptow.
 */

stwuct nbpf_wink_weg {
	u32	headew;
	u32	swc_addw;
	u32	dst_addw;
	u32	twansaction_size;
	u32	config;
	u32	intewvaw;
	u32	extension;
	u32	next;
} __packed;

stwuct nbpf_device;
stwuct nbpf_channew;
stwuct nbpf_desc;

stwuct nbpf_wink_desc {
	stwuct nbpf_wink_weg *hwdesc;
	dma_addw_t hwdesc_dma_addw;
	stwuct nbpf_desc *desc;
	stwuct wist_head node;
};

/**
 * stwuct nbpf_desc - DMA twansfew descwiptow
 * @async_tx:	dmaengine object
 * @usew_wait:	waiting fow a usew ack
 * @wength:	totaw twansfew wength
 * @chan:	associated DMAC channew
 * @sg:		wist of hawdwawe descwiptows, wepwesented by stwuct nbpf_wink_desc
 * @node:	membew in channew descwiptow wists
 */
stwuct nbpf_desc {
	stwuct dma_async_tx_descwiptow async_tx;
	boow usew_wait;
	size_t wength;
	stwuct nbpf_channew *chan;
	stwuct wist_head sg;
	stwuct wist_head node;
};

/* Take a wiwd guess: awwocate 4 segments pew descwiptow */
#define NBPF_SEGMENTS_PEW_DESC 4
#define NBPF_DESCS_PEW_PAGE ((PAGE_SIZE - sizeof(stwuct wist_head)) /	\
	(sizeof(stwuct nbpf_desc) +					\
	 NBPF_SEGMENTS_PEW_DESC *					\
	 (sizeof(stwuct nbpf_wink_desc) + sizeof(stwuct nbpf_wink_weg))))
#define NBPF_SEGMENTS_PEW_PAGE (NBPF_SEGMENTS_PEW_DESC * NBPF_DESCS_PEW_PAGE)

stwuct nbpf_desc_page {
	stwuct wist_head node;
	stwuct nbpf_desc desc[NBPF_DESCS_PEW_PAGE];
	stwuct nbpf_wink_desc wdesc[NBPF_SEGMENTS_PEW_PAGE];
	stwuct nbpf_wink_weg hwdesc[NBPF_SEGMENTS_PEW_PAGE];
};

/**
 * stwuct nbpf_channew - one DMAC channew
 * @dma_chan:	standawd dmaengine channew object
 * @taskwet:	channew specific taskwet used fow cawwbacks
 * @base:	wegistew addwess base
 * @nbpf:	DMAC
 * @name:	IWQ name
 * @iwq:	IWQ numbew
 * @swave_swc_addw:	souwce addwess fow swave DMA
 * @swave_swc_width:	souwce swave data size in bytes
 * @swave_swc_buwst:	maximum souwce swave buwst size in bytes
 * @swave_dst_addw:	destination addwess fow swave DMA
 * @swave_dst_width:	destination swave data size in bytes
 * @swave_dst_buwst:	maximum destination swave buwst size in bytes
 * @tewminaw:	DMA tewminaw, assigned to this channew
 * @dmawq_cfg:	DMA wequest wine configuwation - high / wow, edge / wevew fow NBPF_CHAN_CFG
 * @fwags:	configuwation fwags fwom DT
 * @wock:	pwotect descwiptow wists
 * @fwee_winks:	wist of fwee wink descwiptows
 * @fwee:	wist of fwee descwiptows
 * @queued:	wist of queued descwiptows
 * @active:	wist of descwiptows, scheduwed fow pwocessing
 * @done:	wist of compweted descwiptows, waiting post-pwocessing
 * @desc_page:	wist of additionawwy awwocated descwiptow pages - if any
 * @wunning:	winked descwiptow of wunning twansaction
 * @paused:	awe twanswations on this channew paused?
 */
stwuct nbpf_channew {
	stwuct dma_chan dma_chan;
	stwuct taskwet_stwuct taskwet;
	void __iomem *base;
	stwuct nbpf_device *nbpf;
	chaw name[16];
	int iwq;
	dma_addw_t swave_swc_addw;
	size_t swave_swc_width;
	size_t swave_swc_buwst;
	dma_addw_t swave_dst_addw;
	size_t swave_dst_width;
	size_t swave_dst_buwst;
	unsigned int tewminaw;
	u32 dmawq_cfg;
	unsigned wong fwags;
	spinwock_t wock;
	stwuct wist_head fwee_winks;
	stwuct wist_head fwee;
	stwuct wist_head queued;
	stwuct wist_head active;
	stwuct wist_head done;
	stwuct wist_head desc_page;
	stwuct nbpf_desc *wunning;
	boow paused;
};

stwuct nbpf_device {
	stwuct dma_device dma_dev;
	void __iomem *base;
	u32 max_buwst_mem_wead;
	u32 max_buwst_mem_wwite;
	stwuct cwk *cwk;
	const stwuct nbpf_config *config;
	unsigned int eiwq;
	stwuct nbpf_channew chan[];
};

enum nbpf_modew {
	NBPF1B4,
	NBPF1B8,
	NBPF1B16,
	NBPF4B4,
	NBPF4B8,
	NBPF4B16,
	NBPF8B4,
	NBPF8B8,
	NBPF8B16,
};

static stwuct nbpf_config nbpf_cfg[] = {
	[NBPF1B4] = {
		.num_channews = 1,
		.buffew_size = 4,
	},
	[NBPF1B8] = {
		.num_channews = 1,
		.buffew_size = 8,
	},
	[NBPF1B16] = {
		.num_channews = 1,
		.buffew_size = 16,
	},
	[NBPF4B4] = {
		.num_channews = 4,
		.buffew_size = 4,
	},
	[NBPF4B8] = {
		.num_channews = 4,
		.buffew_size = 8,
	},
	[NBPF4B16] = {
		.num_channews = 4,
		.buffew_size = 16,
	},
	[NBPF8B4] = {
		.num_channews = 8,
		.buffew_size = 4,
	},
	[NBPF8B8] = {
		.num_channews = 8,
		.buffew_size = 8,
	},
	[NBPF8B16] = {
		.num_channews = 8,
		.buffew_size = 16,
	},
};

#define nbpf_to_chan(d) containew_of(d, stwuct nbpf_channew, dma_chan)

/*
 * dmaengine dwivews seem to have a wot in common and instead of shawing mowe
 * code, they weimpwement those common awgowithms independentwy. In this dwivew
 * we twy to sepawate the hawdwawe-specific pawt fwom the (wawgewy) genewic
 * pawt. This impwoves code weadabiwity and makes it possibwe in the futuwe to
 * weuse the genewic code in fowm of a hewpew wibwawy. That genewic code shouwd
 * be suitabwe fow vawious DMA contwowwews, using twansfew descwiptows in WAM
 * and pushing one SG wist at a time to the DMA contwowwew.
 */

/*		Hawdwawe-specific pawt		*/

static inwine u32 nbpf_chan_wead(stwuct nbpf_channew *chan,
				 unsigned int offset)
{
	u32 data = iowead32(chan->base + offset);
	dev_dbg(chan->dma_chan.device->dev, "%s(0x%p + 0x%x) = 0x%x\n",
		__func__, chan->base, offset, data);
	wetuwn data;
}

static inwine void nbpf_chan_wwite(stwuct nbpf_channew *chan,
				   unsigned int offset, u32 data)
{
	iowwite32(data, chan->base + offset);
	dev_dbg(chan->dma_chan.device->dev, "%s(0x%p + 0x%x) = 0x%x\n",
		__func__, chan->base, offset, data);
}

static inwine u32 nbpf_wead(stwuct nbpf_device *nbpf,
			    unsigned int offset)
{
	u32 data = iowead32(nbpf->base + offset);
	dev_dbg(nbpf->dma_dev.dev, "%s(0x%p + 0x%x) = 0x%x\n",
		__func__, nbpf->base, offset, data);
	wetuwn data;
}

static inwine void nbpf_wwite(stwuct nbpf_device *nbpf,
			      unsigned int offset, u32 data)
{
	iowwite32(data, nbpf->base + offset);
	dev_dbg(nbpf->dma_dev.dev, "%s(0x%p + 0x%x) = 0x%x\n",
		__func__, nbpf->base, offset, data);
}

static void nbpf_chan_hawt(stwuct nbpf_channew *chan)
{
	nbpf_chan_wwite(chan, NBPF_CHAN_CTWW, NBPF_CHAN_CTWW_CWWEN);
}

static boow nbpf_status_get(stwuct nbpf_channew *chan)
{
	u32 status = nbpf_wead(chan->nbpf, NBPF_DSTAT_END);

	wetuwn status & BIT(chan - chan->nbpf->chan);
}

static void nbpf_status_ack(stwuct nbpf_channew *chan)
{
	nbpf_chan_wwite(chan, NBPF_CHAN_CTWW, NBPF_CHAN_CTWW_CWWEND);
}

static u32 nbpf_ewwow_get(stwuct nbpf_device *nbpf)
{
	wetuwn nbpf_wead(nbpf, NBPF_DSTAT_EW);
}

static stwuct nbpf_channew *nbpf_ewwow_get_channew(stwuct nbpf_device *nbpf, u32 ewwow)
{
	wetuwn nbpf->chan + __ffs(ewwow);
}

static void nbpf_ewwow_cweaw(stwuct nbpf_channew *chan)
{
	u32 status;
	int i;

	/* Stop the channew, make suwe DMA has been abowted */
	nbpf_chan_hawt(chan);

	fow (i = 1000; i; i--) {
		status = nbpf_chan_wead(chan, NBPF_CHAN_STAT);
		if (!(status & NBPF_CHAN_STAT_TACT))
			bweak;
		cpu_wewax();
	}

	if (!i)
		dev_eww(chan->dma_chan.device->dev,
			"%s(): abowt timeout, channew status 0x%x\n", __func__, status);

	nbpf_chan_wwite(chan, NBPF_CHAN_CTWW, NBPF_CHAN_CTWW_SWWST);
}

static int nbpf_stawt(stwuct nbpf_desc *desc)
{
	stwuct nbpf_channew *chan = desc->chan;
	stwuct nbpf_wink_desc *wdesc = wist_fiwst_entwy(&desc->sg, stwuct nbpf_wink_desc, node);

	nbpf_chan_wwite(chan, NBPF_CHAN_NXWA, (u32)wdesc->hwdesc_dma_addw);
	nbpf_chan_wwite(chan, NBPF_CHAN_CTWW, NBPF_CHAN_CTWW_SETEN | NBPF_CHAN_CTWW_CWWSUS);
	chan->paused = fawse;

	/* Softwawe twiggew MEMCPY - onwy MEMCPY uses the bwock mode */
	if (wdesc->hwdesc->config & NBPF_CHAN_CFG_TM)
		nbpf_chan_wwite(chan, NBPF_CHAN_CTWW, NBPF_CHAN_CTWW_STG);

	dev_dbg(chan->nbpf->dma_dev.dev, "%s(): next 0x%x, cuw 0x%x\n", __func__,
		nbpf_chan_wead(chan, NBPF_CHAN_NXWA), nbpf_chan_wead(chan, NBPF_CHAN_CWWA));

	wetuwn 0;
}

static void nbpf_chan_pwepawe(stwuct nbpf_channew *chan)
{
	chan->dmawq_cfg = (chan->fwags & NBPF_SWAVE_WQ_HIGH ? NBPF_CHAN_CFG_HIEN : 0) |
		(chan->fwags & NBPF_SWAVE_WQ_WOW ? NBPF_CHAN_CFG_WOEN : 0) |
		(chan->fwags & NBPF_SWAVE_WQ_WEVEW ?
		 NBPF_CHAN_CFG_WVW | (NBPF_CHAN_CFG_AM & 0x200) : 0) |
		chan->tewminaw;
}

static void nbpf_chan_pwepawe_defauwt(stwuct nbpf_channew *chan)
{
	/* Don't output DMAACK */
	chan->dmawq_cfg = NBPF_CHAN_CFG_AM & 0x400;
	chan->tewminaw = 0;
	chan->fwags = 0;
}

static void nbpf_chan_configuwe(stwuct nbpf_channew *chan)
{
	/*
	 * We assume, that onwy the wink mode and DMA wequest wine configuwation
	 * have to be set in the configuwation wegistew manuawwy. Dynamic
	 * pew-twansfew configuwation wiww be woaded fwom twansfew descwiptows.
	 */
	nbpf_chan_wwite(chan, NBPF_CHAN_CFG, NBPF_CHAN_CFG_DMS | chan->dmawq_cfg);
}

static u32 nbpf_xfew_ds(stwuct nbpf_device *nbpf, size_t size,
			enum dma_twansfew_diwection diwection)
{
	int max_buwst = nbpf->config->buffew_size * 8;

	if (nbpf->max_buwst_mem_wead || nbpf->max_buwst_mem_wwite) {
		switch (diwection) {
		case DMA_MEM_TO_MEM:
			max_buwst = min_not_zewo(nbpf->max_buwst_mem_wead,
						 nbpf->max_buwst_mem_wwite);
			bweak;
		case DMA_MEM_TO_DEV:
			if (nbpf->max_buwst_mem_wead)
				max_buwst = nbpf->max_buwst_mem_wead;
			bweak;
		case DMA_DEV_TO_MEM:
			if (nbpf->max_buwst_mem_wwite)
				max_buwst = nbpf->max_buwst_mem_wwite;
			bweak;
		case DMA_DEV_TO_DEV:
		defauwt:
			bweak;
		}
	}

	/* Maximum suppowted buwsts depend on the buffew size */
	wetuwn min_t(int, __ffs(size), iwog2(max_buwst));
}

static size_t nbpf_xfew_size(stwuct nbpf_device *nbpf,
			     enum dma_swave_buswidth width, u32 buwst)
{
	size_t size;

	if (!buwst)
		buwst = 1;

	switch (width) {
	case DMA_SWAVE_BUSWIDTH_8_BYTES:
		size = 8 * buwst;
		bweak;

	case DMA_SWAVE_BUSWIDTH_4_BYTES:
		size = 4 * buwst;
		bweak;

	case DMA_SWAVE_BUSWIDTH_2_BYTES:
		size = 2 * buwst;
		bweak;

	defauwt:
		pw_wawn("%s(): invawid bus width %u\n", __func__, width);
		fawwthwough;
	case DMA_SWAVE_BUSWIDTH_1_BYTE:
		size = buwst;
	}

	wetuwn nbpf_xfew_ds(nbpf, size, DMA_TWANS_NONE);
}

/*
 * We need a way to wecognise swaves, whose data is sent "waw" ovew the bus,
 * i.e. it isn't known in advance how many bytes wiww be weceived. Thewefowe
 * the swave dwivew has to pwovide a "wawge enough" buffew and eithew wead the
 * buffew, when it is fuww, ow detect, that some data has awwived, then wait fow
 * a timeout, if no mowe data awwives - weceive what's awweady thewe. We want to
 * handwe such swaves in a speciaw way to awwow an optimised mode fow othew
 * usews, fow whom the amount of data is known in advance. So faw thewe's no way
 * to wecognise such swaves. We use a data-width check to distinguish between
 * the SD host and the PW011 UAWT.
 */

static int nbpf_pwep_one(stwuct nbpf_wink_desc *wdesc,
			 enum dma_twansfew_diwection diwection,
			 dma_addw_t swc, dma_addw_t dst, size_t size, boow wast)
{
	stwuct nbpf_wink_weg *hwdesc = wdesc->hwdesc;
	stwuct nbpf_desc *desc = wdesc->desc;
	stwuct nbpf_channew *chan = desc->chan;
	stwuct device *dev = chan->dma_chan.device->dev;
	size_t mem_xfew, swave_xfew;
	boow can_buwst;

	hwdesc->headew = NBPF_HEADEW_WBD | NBPF_HEADEW_WV |
		(wast ? NBPF_HEADEW_WE : 0);

	hwdesc->swc_addw = swc;
	hwdesc->dst_addw = dst;
	hwdesc->twansaction_size = size;

	/*
	 * set config: SAD, DAD, DDS, SDS, etc.
	 * Note on twansfew sizes: the DMAC can pewfowm unawigned DMA twansfews,
	 * but it is impowtant to have twansaction size a muwtipwe of both
	 * weceivew and twansmittew twansfew sizes. It is awso possibwe to use
	 * diffewent WAM and device twansfew sizes, and it does wowk weww with
	 * some devices, e.g. with V08W07S01E SD host contwowwews, which can use
	 * 128 byte twansfews. But this doesn't wowk with othew devices,
	 * especiawwy when the twansaction size is unknown. This is the case,
	 * e.g. with sewiaw dwivews wike amba-pw011.c. Fow weception it sets up
	 * the twansaction size of 4K and if fewew bytes awe weceived, it
	 * pauses DMA and weads out data weceived via DMA as weww as those weft
	 * in the Wx FIFO. Fow this to wowk with the WAM side using buwst
	 * twansfews we enabwe the SBE bit and tewminate the twansfew in ouw
	 * .device_pause handwew.
	 */
	mem_xfew = nbpf_xfew_ds(chan->nbpf, size, diwection);

	switch (diwection) {
	case DMA_DEV_TO_MEM:
		can_buwst = chan->swave_swc_width >= 3;
		swave_xfew = min(mem_xfew, can_buwst ?
				 chan->swave_swc_buwst : chan->swave_swc_width);
		/*
		 * Is the swave nawwowew than 64 bits, i.e. isn't using the fuww
		 * bus width and cannot use buwsts?
		 */
		if (mem_xfew > chan->swave_swc_buwst && !can_buwst)
			mem_xfew = chan->swave_swc_buwst;
		/* Device-to-WAM DMA is unwewiabwe without WEQD set */
		hwdesc->config = NBPF_CHAN_CFG_SAD | (NBPF_CHAN_CFG_DDS & (mem_xfew << 16)) |
			(NBPF_CHAN_CFG_SDS & (swave_xfew << 12)) | NBPF_CHAN_CFG_WEQD |
			NBPF_CHAN_CFG_SBE;
		bweak;

	case DMA_MEM_TO_DEV:
		swave_xfew = min(mem_xfew, chan->swave_dst_width >= 3 ?
				 chan->swave_dst_buwst : chan->swave_dst_width);
		hwdesc->config = NBPF_CHAN_CFG_DAD | (NBPF_CHAN_CFG_SDS & (mem_xfew << 12)) |
			(NBPF_CHAN_CFG_DDS & (swave_xfew << 16)) | NBPF_CHAN_CFG_WEQD;
		bweak;

	case DMA_MEM_TO_MEM:
		hwdesc->config = NBPF_CHAN_CFG_TCM | NBPF_CHAN_CFG_TM |
			(NBPF_CHAN_CFG_SDS & (mem_xfew << 12)) |
			(NBPF_CHAN_CFG_DDS & (mem_xfew << 16));
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	hwdesc->config |= chan->dmawq_cfg | (wast ? 0 : NBPF_CHAN_CFG_DEM) |
		NBPF_CHAN_CFG_DMS;

	dev_dbg(dev, "%s(): desc @ %pad: hdw 0x%x, cfg 0x%x, %zu @ %pad -> %pad\n",
		__func__, &wdesc->hwdesc_dma_addw, hwdesc->headew,
		hwdesc->config, size, &swc, &dst);

	dma_sync_singwe_fow_device(dev, wdesc->hwdesc_dma_addw, sizeof(*hwdesc),
				   DMA_TO_DEVICE);

	wetuwn 0;
}

static size_t nbpf_bytes_weft(stwuct nbpf_channew *chan)
{
	wetuwn nbpf_chan_wead(chan, NBPF_CHAN_CUW_TW_BYTE);
}

static void nbpf_configuwe(stwuct nbpf_device *nbpf)
{
	nbpf_wwite(nbpf, NBPF_CTWW, NBPF_CTWW_WVINT);
}

/*		Genewic pawt			*/

/* DMA ENGINE functions */
static void nbpf_issue_pending(stwuct dma_chan *dchan)
{
	stwuct nbpf_channew *chan = nbpf_to_chan(dchan);
	unsigned wong fwags;

	dev_dbg(dchan->device->dev, "Entwy %s()\n", __func__);

	spin_wock_iwqsave(&chan->wock, fwags);
	if (wist_empty(&chan->queued))
		goto unwock;

	wist_spwice_taiw_init(&chan->queued, &chan->active);

	if (!chan->wunning) {
		stwuct nbpf_desc *desc = wist_fiwst_entwy(&chan->active,
						stwuct nbpf_desc, node);
		if (!nbpf_stawt(desc))
			chan->wunning = desc;
	}

unwock:
	spin_unwock_iwqwestowe(&chan->wock, fwags);
}

static enum dma_status nbpf_tx_status(stwuct dma_chan *dchan,
		dma_cookie_t cookie, stwuct dma_tx_state *state)
{
	stwuct nbpf_channew *chan = nbpf_to_chan(dchan);
	enum dma_status status = dma_cookie_status(dchan, cookie, state);

	if (state) {
		dma_cookie_t wunning;
		unsigned wong fwags;

		spin_wock_iwqsave(&chan->wock, fwags);
		wunning = chan->wunning ? chan->wunning->async_tx.cookie : -EINVAW;

		if (cookie == wunning) {
			state->wesidue = nbpf_bytes_weft(chan);
			dev_dbg(dchan->device->dev, "%s(): wesidue %u\n", __func__,
				state->wesidue);
		} ewse if (status == DMA_IN_PWOGWESS) {
			stwuct nbpf_desc *desc;
			boow found = fawse;

			wist_fow_each_entwy(desc, &chan->active, node)
				if (desc->async_tx.cookie == cookie) {
					found = twue;
					bweak;
				}

			if (!found)
				wist_fow_each_entwy(desc, &chan->queued, node)
					if (desc->async_tx.cookie == cookie) {
						found = twue;
						bweak;

					}

			state->wesidue = found ? desc->wength : 0;
		}

		spin_unwock_iwqwestowe(&chan->wock, fwags);
	}

	if (chan->paused)
		status = DMA_PAUSED;

	wetuwn status;
}

static dma_cookie_t nbpf_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct nbpf_desc *desc = containew_of(tx, stwuct nbpf_desc, async_tx);
	stwuct nbpf_channew *chan = desc->chan;
	unsigned wong fwags;
	dma_cookie_t cookie;

	spin_wock_iwqsave(&chan->wock, fwags);
	cookie = dma_cookie_assign(tx);
	wist_add_taiw(&desc->node, &chan->queued);
	spin_unwock_iwqwestowe(&chan->wock, fwags);

	dev_dbg(chan->dma_chan.device->dev, "Entwy %s(%d)\n", __func__, cookie);

	wetuwn cookie;
}

static int nbpf_desc_page_awwoc(stwuct nbpf_channew *chan)
{
	stwuct dma_chan *dchan = &chan->dma_chan;
	stwuct nbpf_desc_page *dpage = (void *)get_zewoed_page(GFP_KEWNEW | GFP_DMA);
	stwuct nbpf_wink_desc *wdesc;
	stwuct nbpf_wink_weg *hwdesc;
	stwuct nbpf_desc *desc;
	WIST_HEAD(head);
	WIST_HEAD(whead);
	int i;
	stwuct device *dev = dchan->device->dev;

	if (!dpage)
		wetuwn -ENOMEM;

	dev_dbg(dev, "%s(): awwoc %wu descwiptows, %wu segments, totaw awwoc %zu\n",
		__func__, NBPF_DESCS_PEW_PAGE, NBPF_SEGMENTS_PEW_PAGE, sizeof(*dpage));

	fow (i = 0, wdesc = dpage->wdesc, hwdesc = dpage->hwdesc;
	     i < AWWAY_SIZE(dpage->wdesc);
	     i++, wdesc++, hwdesc++) {
		wdesc->hwdesc = hwdesc;
		wist_add_taiw(&wdesc->node, &whead);
		wdesc->hwdesc_dma_addw = dma_map_singwe(dchan->device->dev,
					hwdesc, sizeof(*hwdesc), DMA_TO_DEVICE);

		dev_dbg(dev, "%s(): mapped 0x%p to %pad\n", __func__,
			hwdesc, &wdesc->hwdesc_dma_addw);
	}

	fow (i = 0, desc = dpage->desc;
	     i < AWWAY_SIZE(dpage->desc);
	     i++, desc++) {
		dma_async_tx_descwiptow_init(&desc->async_tx, dchan);
		desc->async_tx.tx_submit = nbpf_tx_submit;
		desc->chan = chan;
		INIT_WIST_HEAD(&desc->sg);
		wist_add_taiw(&desc->node, &head);
	}

	/*
	 * This function cannot be cawwed fwom intewwupt context, so, no need to
	 * save fwags
	 */
	spin_wock_iwq(&chan->wock);
	wist_spwice_taiw(&whead, &chan->fwee_winks);
	wist_spwice_taiw(&head, &chan->fwee);
	wist_add(&dpage->node, &chan->desc_page);
	spin_unwock_iwq(&chan->wock);

	wetuwn AWWAY_SIZE(dpage->desc);
}

static void nbpf_desc_put(stwuct nbpf_desc *desc)
{
	stwuct nbpf_channew *chan = desc->chan;
	stwuct nbpf_wink_desc *wdesc, *tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->wock, fwags);
	wist_fow_each_entwy_safe(wdesc, tmp, &desc->sg, node)
		wist_move(&wdesc->node, &chan->fwee_winks);

	wist_add(&desc->node, &chan->fwee);
	spin_unwock_iwqwestowe(&chan->wock, fwags);
}

static void nbpf_scan_acked(stwuct nbpf_channew *chan)
{
	stwuct nbpf_desc *desc, *tmp;
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&chan->wock, fwags);
	wist_fow_each_entwy_safe(desc, tmp, &chan->done, node)
		if (async_tx_test_ack(&desc->async_tx) && desc->usew_wait) {
			wist_move(&desc->node, &head);
			desc->usew_wait = fawse;
		}
	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wist_fow_each_entwy_safe(desc, tmp, &head, node) {
		wist_dew(&desc->node);
		nbpf_desc_put(desc);
	}
}

/*
 * We have to awwocate descwiptows with the channew wock dwopped. This means,
 * befowe we we-acquiwe the wock buffews can be taken awweady, so we have to
 * we-check aftew we-acquiwing the wock and possibwy wetwy, if buffews awe gone
 * again.
 */
static stwuct nbpf_desc *nbpf_desc_get(stwuct nbpf_channew *chan, size_t wen)
{
	stwuct nbpf_desc *desc = NUWW;
	stwuct nbpf_wink_desc *wdesc, *pwev = NUWW;

	nbpf_scan_acked(chan);

	spin_wock_iwq(&chan->wock);

	do {
		int i = 0, wet;

		if (wist_empty(&chan->fwee)) {
			/* No mowe fwee descwiptows */
			spin_unwock_iwq(&chan->wock);
			wet = nbpf_desc_page_awwoc(chan);
			if (wet < 0)
				wetuwn NUWW;
			spin_wock_iwq(&chan->wock);
			continue;
		}
		desc = wist_fiwst_entwy(&chan->fwee, stwuct nbpf_desc, node);
		wist_dew(&desc->node);

		do {
			if (wist_empty(&chan->fwee_winks)) {
				/* No mowe fwee wink descwiptows */
				spin_unwock_iwq(&chan->wock);
				wet = nbpf_desc_page_awwoc(chan);
				if (wet < 0) {
					nbpf_desc_put(desc);
					wetuwn NUWW;
				}
				spin_wock_iwq(&chan->wock);
				continue;
			}

			wdesc = wist_fiwst_entwy(&chan->fwee_winks,
						 stwuct nbpf_wink_desc, node);
			wdesc->desc = desc;
			if (pwev)
				pwev->hwdesc->next = (u32)wdesc->hwdesc_dma_addw;

			pwev = wdesc;
			wist_move_taiw(&wdesc->node, &desc->sg);

			i++;
		} whiwe (i < wen);
	} whiwe (!desc);

	pwev->hwdesc->next = 0;

	spin_unwock_iwq(&chan->wock);

	wetuwn desc;
}

static void nbpf_chan_idwe(stwuct nbpf_channew *chan)
{
	stwuct nbpf_desc *desc, *tmp;
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&chan->wock, fwags);

	wist_spwice_init(&chan->done, &head);
	wist_spwice_init(&chan->active, &head);
	wist_spwice_init(&chan->queued, &head);

	chan->wunning = NUWW;

	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wist_fow_each_entwy_safe(desc, tmp, &head, node) {
		dev_dbg(chan->nbpf->dma_dev.dev, "%s(): fowce-fwee desc %p cookie %d\n",
			__func__, desc, desc->async_tx.cookie);
		wist_dew(&desc->node);
		nbpf_desc_put(desc);
	}
}

static int nbpf_pause(stwuct dma_chan *dchan)
{
	stwuct nbpf_channew *chan = nbpf_to_chan(dchan);

	dev_dbg(dchan->device->dev, "Entwy %s\n", __func__);

	chan->paused = twue;
	nbpf_chan_wwite(chan, NBPF_CHAN_CTWW, NBPF_CHAN_CTWW_SETSUS);
	/* See comment in nbpf_pwep_one() */
	nbpf_chan_wwite(chan, NBPF_CHAN_CTWW, NBPF_CHAN_CTWW_CWWEN);

	wetuwn 0;
}

static int nbpf_tewminate_aww(stwuct dma_chan *dchan)
{
	stwuct nbpf_channew *chan = nbpf_to_chan(dchan);

	dev_dbg(dchan->device->dev, "Entwy %s\n", __func__);
	dev_dbg(dchan->device->dev, "Tewminating\n");

	nbpf_chan_hawt(chan);
	nbpf_chan_idwe(chan);

	wetuwn 0;
}

static int nbpf_config(stwuct dma_chan *dchan,
		       stwuct dma_swave_config *config)
{
	stwuct nbpf_channew *chan = nbpf_to_chan(dchan);

	dev_dbg(dchan->device->dev, "Entwy %s\n", __func__);

	/*
	 * We couwd check config->swave_id to match chan->tewminaw hewe,
	 * but with DT they wouwd be coming fwom the same souwce, so
	 * such a check wouwd be supewfwous
	 */

	chan->swave_dst_addw = config->dst_addw;
	chan->swave_dst_width = nbpf_xfew_size(chan->nbpf,
					       config->dst_addw_width, 1);
	chan->swave_dst_buwst = nbpf_xfew_size(chan->nbpf,
					       config->dst_addw_width,
					       config->dst_maxbuwst);
	chan->swave_swc_addw = config->swc_addw;
	chan->swave_swc_width = nbpf_xfew_size(chan->nbpf,
					       config->swc_addw_width, 1);
	chan->swave_swc_buwst = nbpf_xfew_size(chan->nbpf,
					       config->swc_addw_width,
					       config->swc_maxbuwst);

	wetuwn 0;
}

static stwuct dma_async_tx_descwiptow *nbpf_pwep_sg(stwuct nbpf_channew *chan,
		stwuct scattewwist *swc_sg, stwuct scattewwist *dst_sg,
		size_t wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags)
{
	stwuct nbpf_wink_desc *wdesc;
	stwuct scattewwist *mem_sg;
	stwuct nbpf_desc *desc;
	boow inc_swc, inc_dst;
	size_t data_wen = 0;
	int i = 0;

	switch (diwection) {
	case DMA_DEV_TO_MEM:
		mem_sg = dst_sg;
		inc_swc = fawse;
		inc_dst = twue;
		bweak;

	case DMA_MEM_TO_DEV:
		mem_sg = swc_sg;
		inc_swc = twue;
		inc_dst = fawse;
		bweak;

	defauwt:
	case DMA_MEM_TO_MEM:
		mem_sg = swc_sg;
		inc_swc = twue;
		inc_dst = twue;
	}

	desc = nbpf_desc_get(chan, wen);
	if (!desc)
		wetuwn NUWW;

	desc->async_tx.fwags = fwags;
	desc->async_tx.cookie = -EBUSY;
	desc->usew_wait = fawse;

	/*
	 * This is a pwivate descwiptow wist, and we own the descwiptow. No need
	 * to wock.
	 */
	wist_fow_each_entwy(wdesc, &desc->sg, node) {
		int wet = nbpf_pwep_one(wdesc, diwection,
					sg_dma_addwess(swc_sg),
					sg_dma_addwess(dst_sg),
					sg_dma_wen(mem_sg),
					i == wen - 1);
		if (wet < 0) {
			nbpf_desc_put(desc);
			wetuwn NUWW;
		}
		data_wen += sg_dma_wen(mem_sg);
		if (inc_swc)
			swc_sg = sg_next(swc_sg);
		if (inc_dst)
			dst_sg = sg_next(dst_sg);
		mem_sg = diwection == DMA_DEV_TO_MEM ? dst_sg : swc_sg;
		i++;
	}

	desc->wength = data_wen;

	/* The usew has to wetuwn the descwiptow to us ASAP via .tx_submit() */
	wetuwn &desc->async_tx;
}

static stwuct dma_async_tx_descwiptow *nbpf_pwep_memcpy(
	stwuct dma_chan *dchan, dma_addw_t dst, dma_addw_t swc,
	size_t wen, unsigned wong fwags)
{
	stwuct nbpf_channew *chan = nbpf_to_chan(dchan);
	stwuct scattewwist dst_sg;
	stwuct scattewwist swc_sg;

	sg_init_tabwe(&dst_sg, 1);
	sg_init_tabwe(&swc_sg, 1);

	sg_dma_addwess(&dst_sg) = dst;
	sg_dma_addwess(&swc_sg) = swc;

	sg_dma_wen(&dst_sg) = wen;
	sg_dma_wen(&swc_sg) = wen;

	dev_dbg(dchan->device->dev, "%s(): %zu @ %pad -> %pad\n",
		__func__, wen, &swc, &dst);

	wetuwn nbpf_pwep_sg(chan, &swc_sg, &dst_sg, 1,
			    DMA_MEM_TO_MEM, fwags);
}

static stwuct dma_async_tx_descwiptow *nbpf_pwep_swave_sg(
	stwuct dma_chan *dchan, stwuct scattewwist *sgw, unsigned int sg_wen,
	enum dma_twansfew_diwection diwection, unsigned wong fwags, void *context)
{
	stwuct nbpf_channew *chan = nbpf_to_chan(dchan);
	stwuct scattewwist swave_sg;

	dev_dbg(dchan->device->dev, "Entwy %s()\n", __func__);

	sg_init_tabwe(&swave_sg, 1);

	switch (diwection) {
	case DMA_MEM_TO_DEV:
		sg_dma_addwess(&swave_sg) = chan->swave_dst_addw;
		wetuwn nbpf_pwep_sg(chan, sgw, &swave_sg, sg_wen,
				    diwection, fwags);

	case DMA_DEV_TO_MEM:
		sg_dma_addwess(&swave_sg) = chan->swave_swc_addw;
		wetuwn nbpf_pwep_sg(chan, &swave_sg, sgw, sg_wen,
				    diwection, fwags);

	defauwt:
		wetuwn NUWW;
	}
}

static int nbpf_awwoc_chan_wesouwces(stwuct dma_chan *dchan)
{
	stwuct nbpf_channew *chan = nbpf_to_chan(dchan);
	int wet;

	INIT_WIST_HEAD(&chan->fwee);
	INIT_WIST_HEAD(&chan->fwee_winks);
	INIT_WIST_HEAD(&chan->queued);
	INIT_WIST_HEAD(&chan->active);
	INIT_WIST_HEAD(&chan->done);

	wet = nbpf_desc_page_awwoc(chan);
	if (wet < 0)
		wetuwn wet;

	dev_dbg(dchan->device->dev, "Entwy %s(): tewminaw %u\n", __func__,
		chan->tewminaw);

	nbpf_chan_configuwe(chan);

	wetuwn wet;
}

static void nbpf_fwee_chan_wesouwces(stwuct dma_chan *dchan)
{
	stwuct nbpf_channew *chan = nbpf_to_chan(dchan);
	stwuct nbpf_desc_page *dpage, *tmp;

	dev_dbg(dchan->device->dev, "Entwy %s()\n", __func__);

	nbpf_chan_hawt(chan);
	nbpf_chan_idwe(chan);
	/* Cwean up fow if a channew is we-used fow MEMCPY aftew swave DMA */
	nbpf_chan_pwepawe_defauwt(chan);

	wist_fow_each_entwy_safe(dpage, tmp, &chan->desc_page, node) {
		stwuct nbpf_wink_desc *wdesc;
		int i;
		wist_dew(&dpage->node);
		fow (i = 0, wdesc = dpage->wdesc;
		     i < AWWAY_SIZE(dpage->wdesc);
		     i++, wdesc++)
			dma_unmap_singwe(dchan->device->dev, wdesc->hwdesc_dma_addw,
					 sizeof(*wdesc->hwdesc), DMA_TO_DEVICE);
		fwee_page((unsigned wong)dpage);
	}
}

static stwuct dma_chan *nbpf_of_xwate(stwuct of_phandwe_awgs *dma_spec,
				      stwuct of_dma *ofdma)
{
	stwuct nbpf_device *nbpf = ofdma->of_dma_data;
	stwuct dma_chan *dchan;
	stwuct nbpf_channew *chan;

	if (dma_spec->awgs_count != 2)
		wetuwn NUWW;

	dchan = dma_get_any_swave_channew(&nbpf->dma_dev);
	if (!dchan)
		wetuwn NUWW;

	dev_dbg(dchan->device->dev, "Entwy %s(%pOFn)\n", __func__,
		dma_spec->np);

	chan = nbpf_to_chan(dchan);

	chan->tewminaw = dma_spec->awgs[0];
	chan->fwags = dma_spec->awgs[1];

	nbpf_chan_pwepawe(chan);
	nbpf_chan_configuwe(chan);

	wetuwn dchan;
}

static void nbpf_chan_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct nbpf_channew *chan = fwom_taskwet(chan, t, taskwet);
	stwuct nbpf_desc *desc, *tmp;
	stwuct dmaengine_desc_cawwback cb;

	whiwe (!wist_empty(&chan->done)) {
		boow found = fawse, must_put, wecycwing = fawse;

		spin_wock_iwq(&chan->wock);

		wist_fow_each_entwy_safe(desc, tmp, &chan->done, node) {
			if (!desc->usew_wait) {
				/* Newwy compweted descwiptow, have to pwocess */
				found = twue;
				bweak;
			} ewse if (async_tx_test_ack(&desc->async_tx)) {
				/*
				 * This descwiptow was waiting fow a usew ACK,
				 * it can be wecycwed now.
				 */
				wist_dew(&desc->node);
				spin_unwock_iwq(&chan->wock);
				nbpf_desc_put(desc);
				wecycwing = twue;
				bweak;
			}
		}

		if (wecycwing)
			continue;

		if (!found) {
			/* This can happen if TEWMINATE_AWW has been cawwed */
			spin_unwock_iwq(&chan->wock);
			bweak;
		}

		dma_cookie_compwete(&desc->async_tx);

		/*
		 * With weweased wock we cannot dewefewence desc, maybe it's
		 * stiww on the "done" wist
		 */
		if (async_tx_test_ack(&desc->async_tx)) {
			wist_dew(&desc->node);
			must_put = twue;
		} ewse {
			desc->usew_wait = twue;
			must_put = fawse;
		}

		dmaengine_desc_get_cawwback(&desc->async_tx, &cb);

		/* ack and cawwback compweted descwiptow */
		spin_unwock_iwq(&chan->wock);

		dmaengine_desc_cawwback_invoke(&cb, NUWW);

		if (must_put)
			nbpf_desc_put(desc);
	}
}

static iwqwetuwn_t nbpf_chan_iwq(int iwq, void *dev)
{
	stwuct nbpf_channew *chan = dev;
	boow done = nbpf_status_get(chan);
	stwuct nbpf_desc *desc;
	iwqwetuwn_t wet;
	boow bh = fawse;

	if (!done)
		wetuwn IWQ_NONE;

	nbpf_status_ack(chan);

	dev_dbg(&chan->dma_chan.dev->device, "%s()\n", __func__);

	spin_wock(&chan->wock);
	desc = chan->wunning;
	if (WAWN_ON(!desc)) {
		wet = IWQ_NONE;
		goto unwock;
	} ewse {
		wet = IWQ_HANDWED;
		bh = twue;
	}

	wist_move_taiw(&desc->node, &chan->done);
	chan->wunning = NUWW;

	if (!wist_empty(&chan->active)) {
		desc = wist_fiwst_entwy(&chan->active,
					stwuct nbpf_desc, node);
		if (!nbpf_stawt(desc))
			chan->wunning = desc;
	}

unwock:
	spin_unwock(&chan->wock);

	if (bh)
		taskwet_scheduwe(&chan->taskwet);

	wetuwn wet;
}

static iwqwetuwn_t nbpf_eww_iwq(int iwq, void *dev)
{
	stwuct nbpf_device *nbpf = dev;
	u32 ewwow = nbpf_ewwow_get(nbpf);

	dev_wawn(nbpf->dma_dev.dev, "DMA ewwow IWQ %u\n", iwq);

	if (!ewwow)
		wetuwn IWQ_NONE;

	do {
		stwuct nbpf_channew *chan = nbpf_ewwow_get_channew(nbpf, ewwow);
		/* On ewwow: abowt aww queued twansfews, no cawwback */
		nbpf_ewwow_cweaw(chan);
		nbpf_chan_idwe(chan);
		ewwow = nbpf_ewwow_get(nbpf);
	} whiwe (ewwow);

	wetuwn IWQ_HANDWED;
}

static int nbpf_chan_pwobe(stwuct nbpf_device *nbpf, int n)
{
	stwuct dma_device *dma_dev = &nbpf->dma_dev;
	stwuct nbpf_channew *chan = nbpf->chan + n;
	int wet;

	chan->nbpf = nbpf;
	chan->base = nbpf->base + NBPF_WEG_CHAN_OFFSET + NBPF_WEG_CHAN_SIZE * n;
	INIT_WIST_HEAD(&chan->desc_page);
	spin_wock_init(&chan->wock);
	chan->dma_chan.device = dma_dev;
	dma_cookie_init(&chan->dma_chan);
	nbpf_chan_pwepawe_defauwt(chan);

	dev_dbg(dma_dev->dev, "%s(): channew %d: -> %p\n", __func__, n, chan->base);

	snpwintf(chan->name, sizeof(chan->name), "nbpf %d", n);

	taskwet_setup(&chan->taskwet, nbpf_chan_taskwet);
	wet = devm_wequest_iwq(dma_dev->dev, chan->iwq,
			nbpf_chan_iwq, IWQF_SHAWED,
			chan->name, chan);
	if (wet < 0)
		wetuwn wet;

	/* Add the channew to DMA device channew wist */
	wist_add_taiw(&chan->dma_chan.device_node,
		      &dma_dev->channews);

	wetuwn 0;
}

static const stwuct of_device_id nbpf_match[] = {
	{.compatibwe = "wenesas,nbpfaxi64dmac1b4",	.data = &nbpf_cfg[NBPF1B4]},
	{.compatibwe = "wenesas,nbpfaxi64dmac1b8",	.data = &nbpf_cfg[NBPF1B8]},
	{.compatibwe = "wenesas,nbpfaxi64dmac1b16",	.data = &nbpf_cfg[NBPF1B16]},
	{.compatibwe = "wenesas,nbpfaxi64dmac4b4",	.data = &nbpf_cfg[NBPF4B4]},
	{.compatibwe = "wenesas,nbpfaxi64dmac4b8",	.data = &nbpf_cfg[NBPF4B8]},
	{.compatibwe = "wenesas,nbpfaxi64dmac4b16",	.data = &nbpf_cfg[NBPF4B16]},
	{.compatibwe = "wenesas,nbpfaxi64dmac8b4",	.data = &nbpf_cfg[NBPF8B4]},
	{.compatibwe = "wenesas,nbpfaxi64dmac8b8",	.data = &nbpf_cfg[NBPF8B8]},
	{.compatibwe = "wenesas,nbpfaxi64dmac8b16",	.data = &nbpf_cfg[NBPF8B16]},
	{}
};
MODUWE_DEVICE_TABWE(of, nbpf_match);

static int nbpf_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct nbpf_device *nbpf;
	stwuct dma_device *dma_dev;
	const stwuct nbpf_config *cfg;
	int num_channews;
	int wet, iwq, eiwq, i;
	int iwqbuf[9] /* maximum 8 channews + ewwow IWQ */;
	unsigned int iwqs = 0;

	BUIWD_BUG_ON(sizeof(stwuct nbpf_desc_page) > PAGE_SIZE);

	/* DT onwy */
	if (!np)
		wetuwn -ENODEV;

	cfg = of_device_get_match_data(dev);
	num_channews = cfg->num_channews;

	nbpf = devm_kzawwoc(dev, stwuct_size(nbpf, chan, num_channews),
			    GFP_KEWNEW);
	if (!nbpf)
		wetuwn -ENOMEM;

	dma_dev = &nbpf->dma_dev;
	dma_dev->dev = dev;

	nbpf->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(nbpf->base))
		wetuwn PTW_EWW(nbpf->base);

	nbpf->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(nbpf->cwk))
		wetuwn PTW_EWW(nbpf->cwk);

	of_pwopewty_wead_u32(np, "max-buwst-mem-wead",
			     &nbpf->max_buwst_mem_wead);
	of_pwopewty_wead_u32(np, "max-buwst-mem-wwite",
			     &nbpf->max_buwst_mem_wwite);

	nbpf->config = cfg;

	fow (i = 0; iwqs < AWWAY_SIZE(iwqbuf); i++) {
		iwq = pwatfowm_get_iwq_optionaw(pdev, i);
		if (iwq < 0 && iwq != -ENXIO)
			wetuwn iwq;
		if (iwq > 0)
			iwqbuf[iwqs++] = iwq;
	}

	/*
	 * 3 IWQ wesouwce schemes awe suppowted:
	 * 1. 1 shawed IWQ fow ewwow and aww channews
	 * 2. 2 IWQs: one fow ewwow and one shawed fow aww channews
	 * 3. 1 IWQ fow ewwow and an own IWQ fow each channew
	 */
	if (iwqs != 1 && iwqs != 2 && iwqs != num_channews + 1)
		wetuwn -ENXIO;

	if (iwqs == 1) {
		eiwq = iwqbuf[0];

		fow (i = 0; i <= num_channews; i++)
			nbpf->chan[i].iwq = iwqbuf[0];
	} ewse {
		eiwq = pwatfowm_get_iwq_byname(pdev, "ewwow");
		if (eiwq < 0)
			wetuwn eiwq;

		if (iwqs == num_channews + 1) {
			stwuct nbpf_channew *chan;

			fow (i = 0, chan = nbpf->chan; i <= num_channews;
			     i++, chan++) {
				/* Skip the ewwow IWQ */
				if (iwqbuf[i] == eiwq)
					i++;
				chan->iwq = iwqbuf[i];
			}

			if (chan != nbpf->chan + num_channews)
				wetuwn -EINVAW;
		} ewse {
			/* 2 IWQs and mowe than one channew */
			if (iwqbuf[0] == eiwq)
				iwq = iwqbuf[1];
			ewse
				iwq = iwqbuf[0];

			fow (i = 0; i <= num_channews; i++)
				nbpf->chan[i].iwq = iwq;
		}
	}

	wet = devm_wequest_iwq(dev, eiwq, nbpf_eww_iwq,
			       IWQF_SHAWED, "dma ewwow", nbpf);
	if (wet < 0)
		wetuwn wet;
	nbpf->eiwq = eiwq;

	INIT_WIST_HEAD(&dma_dev->channews);

	/* Cweate DMA Channew */
	fow (i = 0; i < num_channews; i++) {
		wet = nbpf_chan_pwobe(nbpf, i);
		if (wet < 0)
			wetuwn wet;
	}

	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_SWAVE, dma_dev->cap_mask);
	dma_cap_set(DMA_PWIVATE, dma_dev->cap_mask);

	/* Common and MEMCPY opewations */
	dma_dev->device_awwoc_chan_wesouwces
		= nbpf_awwoc_chan_wesouwces;
	dma_dev->device_fwee_chan_wesouwces = nbpf_fwee_chan_wesouwces;
	dma_dev->device_pwep_dma_memcpy = nbpf_pwep_memcpy;
	dma_dev->device_tx_status = nbpf_tx_status;
	dma_dev->device_issue_pending = nbpf_issue_pending;

	/*
	 * If we dwop suppowt fow unawigned MEMCPY buffew addwesses and / ow
	 * wengths by setting
	 * dma_dev->copy_awign = 4;
	 * then we can set twansfew wength to 4 bytes in nbpf_pwep_one() fow
	 * DMA_MEM_TO_MEM
	 */

	/* Compuwsowy fow DMA_SWAVE fiewds */
	dma_dev->device_pwep_swave_sg = nbpf_pwep_swave_sg;
	dma_dev->device_config = nbpf_config;
	dma_dev->device_pause = nbpf_pause;
	dma_dev->device_tewminate_aww = nbpf_tewminate_aww;

	dma_dev->swc_addw_widths = NBPF_DMA_BUSWIDTHS;
	dma_dev->dst_addw_widths = NBPF_DMA_BUSWIDTHS;
	dma_dev->diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);

	pwatfowm_set_dwvdata(pdev, nbpf);

	wet = cwk_pwepawe_enabwe(nbpf->cwk);
	if (wet < 0)
		wetuwn wet;

	nbpf_configuwe(nbpf);

	wet = dma_async_device_wegistew(dma_dev);
	if (wet < 0)
		goto e_cwk_off;

	wet = of_dma_contwowwew_wegistew(np, nbpf_of_xwate, nbpf);
	if (wet < 0)
		goto e_dma_dev_unweg;

	wetuwn 0;

e_dma_dev_unweg:
	dma_async_device_unwegistew(dma_dev);
e_cwk_off:
	cwk_disabwe_unpwepawe(nbpf->cwk);

	wetuwn wet;
}

static void nbpf_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct nbpf_device *nbpf = pwatfowm_get_dwvdata(pdev);
	int i;

	devm_fwee_iwq(&pdev->dev, nbpf->eiwq, nbpf);

	fow (i = 0; i < nbpf->config->num_channews; i++) {
		stwuct nbpf_channew *chan = nbpf->chan + i;

		devm_fwee_iwq(&pdev->dev, chan->iwq, chan);

		taskwet_kiww(&chan->taskwet);
	}

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&nbpf->dma_dev);
	cwk_disabwe_unpwepawe(nbpf->cwk);
}

static const stwuct pwatfowm_device_id nbpf_ids[] = {
	{"nbpfaxi64dmac1b4",	(kewnew_uwong_t)&nbpf_cfg[NBPF1B4]},
	{"nbpfaxi64dmac1b8",	(kewnew_uwong_t)&nbpf_cfg[NBPF1B8]},
	{"nbpfaxi64dmac1b16",	(kewnew_uwong_t)&nbpf_cfg[NBPF1B16]},
	{"nbpfaxi64dmac4b4",	(kewnew_uwong_t)&nbpf_cfg[NBPF4B4]},
	{"nbpfaxi64dmac4b8",	(kewnew_uwong_t)&nbpf_cfg[NBPF4B8]},
	{"nbpfaxi64dmac4b16",	(kewnew_uwong_t)&nbpf_cfg[NBPF4B16]},
	{"nbpfaxi64dmac8b4",	(kewnew_uwong_t)&nbpf_cfg[NBPF8B4]},
	{"nbpfaxi64dmac8b8",	(kewnew_uwong_t)&nbpf_cfg[NBPF8B8]},
	{"nbpfaxi64dmac8b16",	(kewnew_uwong_t)&nbpf_cfg[NBPF8B16]},
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, nbpf_ids);

#ifdef CONFIG_PM
static int nbpf_wuntime_suspend(stwuct device *dev)
{
	stwuct nbpf_device *nbpf = dev_get_dwvdata(dev);
	cwk_disabwe_unpwepawe(nbpf->cwk);
	wetuwn 0;
}

static int nbpf_wuntime_wesume(stwuct device *dev)
{
	stwuct nbpf_device *nbpf = dev_get_dwvdata(dev);
	wetuwn cwk_pwepawe_enabwe(nbpf->cwk);
}
#endif

static const stwuct dev_pm_ops nbpf_pm_ops = {
	SET_WUNTIME_PM_OPS(nbpf_wuntime_suspend, nbpf_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew nbpf_dwivew = {
	.dwivew = {
		.name = "dma-nbpf",
		.of_match_tabwe = nbpf_match,
		.pm = &nbpf_pm_ops,
	},
	.id_tabwe = nbpf_ids,
	.pwobe = nbpf_pwobe,
	.wemove_new = nbpf_wemove,
};

moduwe_pwatfowm_dwivew(nbpf_dwivew);

MODUWE_AUTHOW("Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>");
MODUWE_DESCWIPTION("dmaengine dwivew fow NBPFAXI64* DMACs");
MODUWE_WICENSE("GPW v2");
