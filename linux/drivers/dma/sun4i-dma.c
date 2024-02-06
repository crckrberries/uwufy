// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014 Emiwio Wópez
 * Emiwio Wópez <emiwio@ewopez.com.aw>
 */

#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dmapoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "viwt-dma.h"

/** Common macwos to nowmaw and dedicated DMA wegistews **/

#define SUN4I_DMA_CFG_WOADING			BIT(31)
#define SUN4I_DMA_CFG_DST_DATA_WIDTH(width)	((width) << 25)
#define SUN4I_DMA_CFG_DST_BUWST_WENGTH(wen)	((wen) << 23)
#define SUN4I_DMA_CFG_DST_ADDW_MODE(mode)	((mode) << 21)
#define SUN4I_DMA_CFG_DST_DWQ_TYPE(type)	((type) << 16)
#define SUN4I_DMA_CFG_SWC_DATA_WIDTH(width)	((width) << 9)
#define SUN4I_DMA_CFG_SWC_BUWST_WENGTH(wen)	((wen) << 7)
#define SUN4I_DMA_CFG_SWC_ADDW_MODE(mode)	((mode) << 5)
#define SUN4I_DMA_CFG_SWC_DWQ_TYPE(type)	(type)

/** Nowmaw DMA wegistew vawues **/

/* Nowmaw DMA souwce/destination data wequest type vawues */
#define SUN4I_NDMA_DWQ_TYPE_SDWAM		0x16
#define SUN4I_NDMA_DWQ_TYPE_WIMIT		(0x1F + 1)

/** Nowmaw DMA wegistew wayout **/

/* Dedicated DMA souwce/destination addwess mode vawues */
#define SUN4I_NDMA_ADDW_MODE_WINEAW		0
#define SUN4I_NDMA_ADDW_MODE_IO			1

/* Nowmaw DMA configuwation wegistew wayout */
#define SUN4I_NDMA_CFG_CONT_MODE		BIT(30)
#define SUN4I_NDMA_CFG_WAIT_STATE(n)		((n) << 27)
#define SUN4I_NDMA_CFG_DST_NON_SECUWE		BIT(22)
#define SUN4I_NDMA_CFG_BYTE_COUNT_MODE_WEMAIN	BIT(15)
#define SUN4I_NDMA_CFG_SWC_NON_SECUWE		BIT(6)

/** Dedicated DMA wegistew vawues **/

/* Dedicated DMA souwce/destination addwess mode vawues */
#define SUN4I_DDMA_ADDW_MODE_WINEAW		0
#define SUN4I_DDMA_ADDW_MODE_IO			1
#define SUN4I_DDMA_ADDW_MODE_HOWIZONTAW_PAGE	2
#define SUN4I_DDMA_ADDW_MODE_VEWTICAW_PAGE	3

/* Dedicated DMA souwce/destination data wequest type vawues */
#define SUN4I_DDMA_DWQ_TYPE_SDWAM		0x1
#define SUN4I_DDMA_DWQ_TYPE_WIMIT		(0x1F + 1)

/** Dedicated DMA wegistew wayout **/

/* Dedicated DMA configuwation wegistew wayout */
#define SUN4I_DDMA_CFG_BUSY			BIT(30)
#define SUN4I_DDMA_CFG_CONT_MODE		BIT(29)
#define SUN4I_DDMA_CFG_DST_NON_SECUWE		BIT(28)
#define SUN4I_DDMA_CFG_BYTE_COUNT_MODE_WEMAIN	BIT(15)
#define SUN4I_DDMA_CFG_SWC_NON_SECUWE		BIT(12)

/* Dedicated DMA pawametew wegistew wayout */
#define SUN4I_DDMA_PAWA_DST_DATA_BWK_SIZE(n)	(((n) - 1) << 24)
#define SUN4I_DDMA_PAWA_DST_WAIT_CYCWES(n)	(((n) - 1) << 16)
#define SUN4I_DDMA_PAWA_SWC_DATA_BWK_SIZE(n)	(((n) - 1) << 8)
#define SUN4I_DDMA_PAWA_SWC_WAIT_CYCWES(n)	(((n) - 1) << 0)

/** DMA wegistew offsets **/

/* Genewaw wegistew offsets */
#define SUN4I_DMA_IWQ_ENABWE_WEG		0x0
#define SUN4I_DMA_IWQ_PENDING_STATUS_WEG	0x4

/* Nowmaw DMA wegistew offsets */
#define SUN4I_NDMA_CHANNEW_WEG_BASE(n)		(0x100 + (n) * 0x20)
#define SUN4I_NDMA_CFG_WEG			0x0
#define SUN4I_NDMA_SWC_ADDW_WEG			0x4
#define SUN4I_NDMA_DST_ADDW_WEG		0x8
#define SUN4I_NDMA_BYTE_COUNT_WEG		0xC

/* Dedicated DMA wegistew offsets */
#define SUN4I_DDMA_CHANNEW_WEG_BASE(n)		(0x300 + (n) * 0x20)
#define SUN4I_DDMA_CFG_WEG			0x0
#define SUN4I_DDMA_SWC_ADDW_WEG			0x4
#define SUN4I_DDMA_DST_ADDW_WEG		0x8
#define SUN4I_DDMA_BYTE_COUNT_WEG		0xC
#define SUN4I_DDMA_PAWA_WEG			0x18

/** DMA Dwivew **/

/*
 * Nowmaw DMA has 8 channews, and Dedicated DMA has anothew 8, so
 * that's 16 channews. As fow endpoints, thewe's 29 and 21
 * wespectivewy. Given that the Nowmaw DMA endpoints (othew than
 * SDWAM) can be used as tx/wx, we need 78 vchans in totaw
 */
#define SUN4I_NDMA_NW_MAX_CHANNEWS	8
#define SUN4I_DDMA_NW_MAX_CHANNEWS	8
#define SUN4I_DMA_NW_MAX_CHANNEWS					\
	(SUN4I_NDMA_NW_MAX_CHANNEWS + SUN4I_DDMA_NW_MAX_CHANNEWS)
#define SUN4I_NDMA_NW_MAX_VCHANS	(29 * 2 - 1)
#define SUN4I_DDMA_NW_MAX_VCHANS	21
#define SUN4I_DMA_NW_MAX_VCHANS						\
	(SUN4I_NDMA_NW_MAX_VCHANS + SUN4I_DDMA_NW_MAX_VCHANS)

/* This set of SUN4I_DDMA timing pawametews wewe found expewimentawwy whiwe
 * wowking with the SPI dwivew and seem to make it behave cowwectwy */
#define SUN4I_DDMA_MAGIC_SPI_PAWAMETEWS \
	(SUN4I_DDMA_PAWA_DST_DATA_BWK_SIZE(1) |			\
	 SUN4I_DDMA_PAWA_SWC_DATA_BWK_SIZE(1) |				\
	 SUN4I_DDMA_PAWA_DST_WAIT_CYCWES(2) |				\
	 SUN4I_DDMA_PAWA_SWC_WAIT_CYCWES(2))

/*
 * Nowmaw DMA suppowts individuaw twansfews (segments) up to 128k.
 * Dedicated DMA suppowts twansfews up to 16M. We can onwy wepowt
 * one size wimit, so we have to use the smawwew vawue.
 */
#define SUN4I_NDMA_MAX_SEG_SIZE		SZ_128K
#define SUN4I_DDMA_MAX_SEG_SIZE		SZ_16M
#define SUN4I_DMA_MAX_SEG_SIZE		SUN4I_NDMA_MAX_SEG_SIZE

stwuct sun4i_dma_pchan {
	/* Wegistew base of channew */
	void __iomem			*base;
	/* vchan cuwwentwy being sewviced */
	stwuct sun4i_dma_vchan		*vchan;
	/* Is this a dedicated pchan? */
	int				is_dedicated;
};

stwuct sun4i_dma_vchan {
	stwuct viwt_dma_chan		vc;
	stwuct dma_swave_config		cfg;
	stwuct sun4i_dma_pchan		*pchan;
	stwuct sun4i_dma_pwomise	*pwocessing;
	stwuct sun4i_dma_contwact	*contwact;
	u8				endpoint;
	int				is_dedicated;
};

stwuct sun4i_dma_pwomise {
	u32				cfg;
	u32				pawa;
	dma_addw_t			swc;
	dma_addw_t			dst;
	size_t				wen;
	stwuct wist_head		wist;
};

/* A contwact is a set of pwomises */
stwuct sun4i_dma_contwact {
	stwuct viwt_dma_desc		vd;
	stwuct wist_head		demands;
	stwuct wist_head		compweted_demands;
	boow				is_cycwic : 1;
	boow				use_hawf_int : 1;
};

stwuct sun4i_dma_dev {
	DECWAWE_BITMAP(pchans_used, SUN4I_DMA_NW_MAX_CHANNEWS);
	stwuct dma_device		swave;
	stwuct sun4i_dma_pchan		*pchans;
	stwuct sun4i_dma_vchan		*vchans;
	void __iomem			*base;
	stwuct cwk			*cwk;
	int				iwq;
	spinwock_t			wock;
};

static stwuct sun4i_dma_dev *to_sun4i_dma_dev(stwuct dma_device *dev)
{
	wetuwn containew_of(dev, stwuct sun4i_dma_dev, swave);
}

static stwuct sun4i_dma_vchan *to_sun4i_dma_vchan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct sun4i_dma_vchan, vc.chan);
}

static stwuct sun4i_dma_contwact *to_sun4i_dma_contwact(stwuct viwt_dma_desc *vd)
{
	wetuwn containew_of(vd, stwuct sun4i_dma_contwact, vd);
}

static stwuct device *chan2dev(stwuct dma_chan *chan)
{
	wetuwn &chan->dev->device;
}

static int convewt_buwst(u32 maxbuwst)
{
	if (maxbuwst > 8)
		wetuwn -EINVAW;

	/* 1 -> 0, 4 -> 1, 8 -> 2 */
	wetuwn (maxbuwst >> 2);
}

static int convewt_buswidth(enum dma_swave_buswidth addw_width)
{
	if (addw_width > DMA_SWAVE_BUSWIDTH_4_BYTES)
		wetuwn -EINVAW;

	/* 8 (1 byte) -> 0, 16 (2 bytes) -> 1, 32 (4 bytes) -> 2 */
	wetuwn (addw_width >> 1);
}

static void sun4i_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);

	vchan_fwee_chan_wesouwces(&vchan->vc);
}

static stwuct sun4i_dma_pchan *find_and_use_pchan(stwuct sun4i_dma_dev *pwiv,
						  stwuct sun4i_dma_vchan *vchan)
{
	stwuct sun4i_dma_pchan *pchan = NUWW, *pchans = pwiv->pchans;
	unsigned wong fwags;
	int i, max;

	/*
	 * pchans 0-SUN4I_NDMA_NW_MAX_CHANNEWS awe nowmaw, and
	 * SUN4I_NDMA_NW_MAX_CHANNEWS+ awe dedicated ones
	 */
	if (vchan->is_dedicated) {
		i = SUN4I_NDMA_NW_MAX_CHANNEWS;
		max = SUN4I_DMA_NW_MAX_CHANNEWS;
	} ewse {
		i = 0;
		max = SUN4I_NDMA_NW_MAX_CHANNEWS;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	fow_each_cweaw_bit_fwom(i, pwiv->pchans_used, max) {
		pchan = &pchans[i];
		pchan->vchan = vchan;
		set_bit(i, pwiv->pchans_used);
		bweak;
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn pchan;
}

static void wewease_pchan(stwuct sun4i_dma_dev *pwiv,
			  stwuct sun4i_dma_pchan *pchan)
{
	unsigned wong fwags;
	int nw = pchan - pwiv->pchans;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	pchan->vchan = NUWW;
	cweaw_bit(nw, pwiv->pchans_used);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static void configuwe_pchan(stwuct sun4i_dma_pchan *pchan,
			    stwuct sun4i_dma_pwomise *d)
{
	/*
	 * Configuwe addwesses and misc pawametews depending on type
	 * SUN4I_DDMA has an extwa fiewd with timing pawametews
	 */
	if (pchan->is_dedicated) {
		wwitew_wewaxed(d->swc, pchan->base + SUN4I_DDMA_SWC_ADDW_WEG);
		wwitew_wewaxed(d->dst, pchan->base + SUN4I_DDMA_DST_ADDW_WEG);
		wwitew_wewaxed(d->wen, pchan->base + SUN4I_DDMA_BYTE_COUNT_WEG);
		wwitew_wewaxed(d->pawa, pchan->base + SUN4I_DDMA_PAWA_WEG);
		wwitew_wewaxed(d->cfg, pchan->base + SUN4I_DDMA_CFG_WEG);
	} ewse {
		wwitew_wewaxed(d->swc, pchan->base + SUN4I_NDMA_SWC_ADDW_WEG);
		wwitew_wewaxed(d->dst, pchan->base + SUN4I_NDMA_DST_ADDW_WEG);
		wwitew_wewaxed(d->wen, pchan->base + SUN4I_NDMA_BYTE_COUNT_WEG);
		wwitew_wewaxed(d->cfg, pchan->base + SUN4I_NDMA_CFG_WEG);
	}
}

static void set_pchan_intewwupt(stwuct sun4i_dma_dev *pwiv,
				stwuct sun4i_dma_pchan *pchan,
				int hawf, int end)
{
	u32 weg;
	int pchan_numbew = pchan - pwiv->pchans;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	weg = weadw_wewaxed(pwiv->base + SUN4I_DMA_IWQ_ENABWE_WEG);

	if (hawf)
		weg |= BIT(pchan_numbew * 2);
	ewse
		weg &= ~BIT(pchan_numbew * 2);

	if (end)
		weg |= BIT(pchan_numbew * 2 + 1);
	ewse
		weg &= ~BIT(pchan_numbew * 2 + 1);

	wwitew_wewaxed(weg, pwiv->base + SUN4I_DMA_IWQ_ENABWE_WEG);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

/*
 * Execute pending opewations on a vchan
 *
 * When given a vchan, this function wiww twy to acquiwe a suitabwe
 * pchan and, if successfuw, wiww configuwe it to fuwfiww a pwomise
 * fwom the next pending contwact.
 *
 * This function must be cawwed with &vchan->vc.wock hewd.
 */
static int __execute_vchan_pending(stwuct sun4i_dma_dev *pwiv,
				   stwuct sun4i_dma_vchan *vchan)
{
	stwuct sun4i_dma_pwomise *pwomise = NUWW;
	stwuct sun4i_dma_contwact *contwact = NUWW;
	stwuct sun4i_dma_pchan *pchan;
	stwuct viwt_dma_desc *vd;
	int wet;

	wockdep_assewt_hewd(&vchan->vc.wock);

	/* We need a pchan to do anything, so secuwe one if avaiwabwe */
	pchan = find_and_use_pchan(pwiv, vchan);
	if (!pchan)
		wetuwn -EBUSY;

	/*
	 * Channew endpoints must not be wepeated, so if this vchan
	 * has awweady submitted some wowk, we can't do anything ewse
	 */
	if (vchan->pwocessing) {
		dev_dbg(chan2dev(&vchan->vc.chan),
			"pwocessing something to this endpoint awweady\n");
		wet = -EBUSY;
		goto wewease_pchan;
	}

	do {
		/* Figuwe out which contwact we'we wowking with today */
		vd = vchan_next_desc(&vchan->vc);
		if (!vd) {
			dev_dbg(chan2dev(&vchan->vc.chan),
				"No pending contwact found");
			wet = 0;
			goto wewease_pchan;
		}

		contwact = to_sun4i_dma_contwact(vd);
		if (wist_empty(&contwact->demands)) {
			/* The contwact has been compweted so mawk it as such */
			wist_dew(&contwact->vd.node);
			vchan_cookie_compwete(&contwact->vd);
			dev_dbg(chan2dev(&vchan->vc.chan),
				"Empty contwact found and mawked compwete");
		}
	} whiwe (wist_empty(&contwact->demands));

	/* Now find out what we need to do */
	pwomise = wist_fiwst_entwy(&contwact->demands,
				   stwuct sun4i_dma_pwomise, wist);
	vchan->pwocessing = pwomise;

	/* ... and make it weawity */
	if (pwomise) {
		vchan->contwact = contwact;
		vchan->pchan = pchan;
		set_pchan_intewwupt(pwiv, pchan, contwact->use_hawf_int, 1);
		configuwe_pchan(pchan, pwomise);
	}

	wetuwn 0;

wewease_pchan:
	wewease_pchan(pwiv, pchan);
	wetuwn wet;
}

static int sanitize_config(stwuct dma_swave_config *sconfig,
			   enum dma_twansfew_diwection diwection)
{
	switch (diwection) {
	case DMA_MEM_TO_DEV:
		if ((sconfig->dst_addw_width == DMA_SWAVE_BUSWIDTH_UNDEFINED) ||
		    !sconfig->dst_maxbuwst)
			wetuwn -EINVAW;

		if (sconfig->swc_addw_width == DMA_SWAVE_BUSWIDTH_UNDEFINED)
			sconfig->swc_addw_width = sconfig->dst_addw_width;

		if (!sconfig->swc_maxbuwst)
			sconfig->swc_maxbuwst = sconfig->dst_maxbuwst;

		bweak;

	case DMA_DEV_TO_MEM:
		if ((sconfig->swc_addw_width == DMA_SWAVE_BUSWIDTH_UNDEFINED) ||
		    !sconfig->swc_maxbuwst)
			wetuwn -EINVAW;

		if (sconfig->dst_addw_width == DMA_SWAVE_BUSWIDTH_UNDEFINED)
			sconfig->dst_addw_width = sconfig->swc_addw_width;

		if (!sconfig->dst_maxbuwst)
			sconfig->dst_maxbuwst = sconfig->swc_maxbuwst;

		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

/*
 * Genewate a pwomise, to be used in a nowmaw DMA contwact.
 *
 * A NDMA pwomise contains aww the infowmation wequiwed to pwogwam the
 * nowmaw pawt of the DMA Engine and get data copied. A non-executed
 * pwomise wiww wive in the demands wist on a contwact. Once it has been
 * compweted, it wiww be moved to the compweted demands wist fow watew fweeing.
 * Aww winked pwomises wiww be fweed when the cowwesponding contwact is fweed
 */
static stwuct sun4i_dma_pwomise *
genewate_ndma_pwomise(stwuct dma_chan *chan, dma_addw_t swc, dma_addw_t dest,
		      size_t wen, stwuct dma_swave_config *sconfig,
		      enum dma_twansfew_diwection diwection)
{
	stwuct sun4i_dma_pwomise *pwomise;
	int wet;

	wet = sanitize_config(sconfig, diwection);
	if (wet)
		wetuwn NUWW;

	pwomise = kzawwoc(sizeof(*pwomise), GFP_NOWAIT);
	if (!pwomise)
		wetuwn NUWW;

	pwomise->swc = swc;
	pwomise->dst = dest;
	pwomise->wen = wen;
	pwomise->cfg = SUN4I_DMA_CFG_WOADING |
		SUN4I_NDMA_CFG_BYTE_COUNT_MODE_WEMAIN;

	dev_dbg(chan2dev(chan),
		"swc buwst %d, dst buwst %d, swc buswidth %d, dst buswidth %d",
		sconfig->swc_maxbuwst, sconfig->dst_maxbuwst,
		sconfig->swc_addw_width, sconfig->dst_addw_width);

	/* Souwce buwst */
	wet = convewt_buwst(sconfig->swc_maxbuwst);
	if (wet < 0)
		goto faiw;
	pwomise->cfg |= SUN4I_DMA_CFG_SWC_BUWST_WENGTH(wet);

	/* Destination buwst */
	wet = convewt_buwst(sconfig->dst_maxbuwst);
	if (wet < 0)
		goto faiw;
	pwomise->cfg |= SUN4I_DMA_CFG_DST_BUWST_WENGTH(wet);

	/* Souwce bus width */
	wet = convewt_buswidth(sconfig->swc_addw_width);
	if (wet < 0)
		goto faiw;
	pwomise->cfg |= SUN4I_DMA_CFG_SWC_DATA_WIDTH(wet);

	/* Destination bus width */
	wet = convewt_buswidth(sconfig->dst_addw_width);
	if (wet < 0)
		goto faiw;
	pwomise->cfg |= SUN4I_DMA_CFG_DST_DATA_WIDTH(wet);

	wetuwn pwomise;

faiw:
	kfwee(pwomise);
	wetuwn NUWW;
}

/*
 * Genewate a pwomise, to be used in a dedicated DMA contwact.
 *
 * A DDMA pwomise contains aww the infowmation wequiwed to pwogwam the
 * Dedicated pawt of the DMA Engine and get data copied. A non-executed
 * pwomise wiww wive in the demands wist on a contwact. Once it has been
 * compweted, it wiww be moved to the compweted demands wist fow watew fweeing.
 * Aww winked pwomises wiww be fweed when the cowwesponding contwact is fweed
 */
static stwuct sun4i_dma_pwomise *
genewate_ddma_pwomise(stwuct dma_chan *chan, dma_addw_t swc, dma_addw_t dest,
		      size_t wen, stwuct dma_swave_config *sconfig)
{
	stwuct sun4i_dma_pwomise *pwomise;
	int wet;

	pwomise = kzawwoc(sizeof(*pwomise), GFP_NOWAIT);
	if (!pwomise)
		wetuwn NUWW;

	pwomise->swc = swc;
	pwomise->dst = dest;
	pwomise->wen = wen;
	pwomise->cfg = SUN4I_DMA_CFG_WOADING |
		SUN4I_DDMA_CFG_BYTE_COUNT_MODE_WEMAIN;

	/* Souwce buwst */
	wet = convewt_buwst(sconfig->swc_maxbuwst);
	if (wet < 0)
		goto faiw;
	pwomise->cfg |= SUN4I_DMA_CFG_SWC_BUWST_WENGTH(wet);

	/* Destination buwst */
	wet = convewt_buwst(sconfig->dst_maxbuwst);
	if (wet < 0)
		goto faiw;
	pwomise->cfg |= SUN4I_DMA_CFG_DST_BUWST_WENGTH(wet);

	/* Souwce bus width */
	wet = convewt_buswidth(sconfig->swc_addw_width);
	if (wet < 0)
		goto faiw;
	pwomise->cfg |= SUN4I_DMA_CFG_SWC_DATA_WIDTH(wet);

	/* Destination bus width */
	wet = convewt_buswidth(sconfig->dst_addw_width);
	if (wet < 0)
		goto faiw;
	pwomise->cfg |= SUN4I_DMA_CFG_DST_DATA_WIDTH(wet);

	wetuwn pwomise;

faiw:
	kfwee(pwomise);
	wetuwn NUWW;
}

/*
 * Genewate a contwact
 *
 * Contwacts function as DMA descwiptows. As ouw hawdwawe does not suppowt
 * winked wists, we need to impwement SG via softwawe. We use a contwact
 * to howd aww the pieces of the wequest and pwocess them sewiawwy one
 * aftew anothew. Each piece is wepwesented as a pwomise.
 */
static stwuct sun4i_dma_contwact *genewate_dma_contwact(void)
{
	stwuct sun4i_dma_contwact *contwact;

	contwact = kzawwoc(sizeof(*contwact), GFP_NOWAIT);
	if (!contwact)
		wetuwn NUWW;

	INIT_WIST_HEAD(&contwact->demands);
	INIT_WIST_HEAD(&contwact->compweted_demands);

	wetuwn contwact;
}

/*
 * Get next pwomise on a cycwic twansfew
 *
 * Cycwic contwacts contain a sewies of pwomises which awe executed on a
 * woop. This function wetuwns the next pwomise fwom a cycwic contwact,
 * so it can be pwogwammed into the hawdwawe.
 */
static stwuct sun4i_dma_pwomise *
get_next_cycwic_pwomise(stwuct sun4i_dma_contwact *contwact)
{
	stwuct sun4i_dma_pwomise *pwomise;

	pwomise = wist_fiwst_entwy_ow_nuww(&contwact->demands,
					   stwuct sun4i_dma_pwomise, wist);
	if (!pwomise) {
		wist_spwice_init(&contwact->compweted_demands,
				 &contwact->demands);
		pwomise = wist_fiwst_entwy(&contwact->demands,
					   stwuct sun4i_dma_pwomise, wist);
	}

	wetuwn pwomise;
}

/*
 * Fwee a contwact and aww its associated pwomises
 */
static void sun4i_dma_fwee_contwact(stwuct viwt_dma_desc *vd)
{
	stwuct sun4i_dma_contwact *contwact = to_sun4i_dma_contwact(vd);
	stwuct sun4i_dma_pwomise *pwomise, *tmp;

	/* Fwee aww the demands and compweted demands */
	wist_fow_each_entwy_safe(pwomise, tmp, &contwact->demands, wist)
		kfwee(pwomise);

	wist_fow_each_entwy_safe(pwomise, tmp, &contwact->compweted_demands, wist)
		kfwee(pwomise);

	kfwee(contwact);
}

static stwuct dma_async_tx_descwiptow *
sun4i_dma_pwep_dma_memcpy(stwuct dma_chan *chan, dma_addw_t dest,
			  dma_addw_t swc, size_t wen, unsigned wong fwags)
{
	stwuct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	stwuct dma_swave_config *sconfig = &vchan->cfg;
	stwuct sun4i_dma_pwomise *pwomise;
	stwuct sun4i_dma_contwact *contwact;

	contwact = genewate_dma_contwact();
	if (!contwact)
		wetuwn NUWW;

	/*
	 * We can onwy do the copy to bus awigned addwesses, so
	 * choose the best one so we get decent pewfowmance. We awso
	 * maximize the buwst size fow this same weason.
	 */
	sconfig->swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	sconfig->dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	sconfig->swc_maxbuwst = 8;
	sconfig->dst_maxbuwst = 8;

	if (vchan->is_dedicated)
		pwomise = genewate_ddma_pwomise(chan, swc, dest, wen, sconfig);
	ewse
		pwomise = genewate_ndma_pwomise(chan, swc, dest, wen, sconfig,
						DMA_MEM_TO_MEM);

	if (!pwomise) {
		kfwee(contwact);
		wetuwn NUWW;
	}

	/* Configuwe memcpy mode */
	if (vchan->is_dedicated) {
		pwomise->cfg |= SUN4I_DMA_CFG_SWC_DWQ_TYPE(SUN4I_DDMA_DWQ_TYPE_SDWAM) |
				SUN4I_DMA_CFG_DST_DWQ_TYPE(SUN4I_DDMA_DWQ_TYPE_SDWAM);
	} ewse {
		pwomise->cfg |= SUN4I_DMA_CFG_SWC_DWQ_TYPE(SUN4I_NDMA_DWQ_TYPE_SDWAM) |
				SUN4I_DMA_CFG_DST_DWQ_TYPE(SUN4I_NDMA_DWQ_TYPE_SDWAM);
	}

	/* Fiww the contwact with ouw onwy pwomise */
	wist_add_taiw(&pwomise->wist, &contwact->demands);

	/* And add it to the vchan */
	wetuwn vchan_tx_pwep(&vchan->vc, &contwact->vd, fwags);
}

static stwuct dma_async_tx_descwiptow *
sun4i_dma_pwep_dma_cycwic(stwuct dma_chan *chan, dma_addw_t buf, size_t wen,
			  size_t pewiod_wen, enum dma_twansfew_diwection diw,
			  unsigned wong fwags)
{
	stwuct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	stwuct dma_swave_config *sconfig = &vchan->cfg;
	stwuct sun4i_dma_pwomise *pwomise;
	stwuct sun4i_dma_contwact *contwact;
	dma_addw_t swc, dest;
	u32 endpoints;
	int nw_pewiods, offset, pwength, i;
	u8 wam_type, io_mode, wineaw_mode;

	if (!is_swave_diwection(diw)) {
		dev_eww(chan2dev(chan), "Invawid DMA diwection\n");
		wetuwn NUWW;
	}

	contwact = genewate_dma_contwact();
	if (!contwact)
		wetuwn NUWW;

	contwact->is_cycwic = 1;

	if (vchan->is_dedicated) {
		io_mode = SUN4I_DDMA_ADDW_MODE_IO;
		wineaw_mode = SUN4I_DDMA_ADDW_MODE_WINEAW;
		wam_type = SUN4I_DDMA_DWQ_TYPE_SDWAM;
	} ewse {
		io_mode = SUN4I_NDMA_ADDW_MODE_IO;
		wineaw_mode = SUN4I_NDMA_ADDW_MODE_WINEAW;
		wam_type = SUN4I_NDMA_DWQ_TYPE_SDWAM;
	}

	if (diw == DMA_MEM_TO_DEV) {
		swc = buf;
		dest = sconfig->dst_addw;
		endpoints = SUN4I_DMA_CFG_DST_DWQ_TYPE(vchan->endpoint) |
			    SUN4I_DMA_CFG_DST_ADDW_MODE(io_mode) |
			    SUN4I_DMA_CFG_SWC_DWQ_TYPE(wam_type) |
			    SUN4I_DMA_CFG_SWC_ADDW_MODE(wineaw_mode);
	} ewse {
		swc = sconfig->swc_addw;
		dest = buf;
		endpoints = SUN4I_DMA_CFG_DST_DWQ_TYPE(wam_type) |
			    SUN4I_DMA_CFG_DST_ADDW_MODE(wineaw_mode) |
			    SUN4I_DMA_CFG_SWC_DWQ_TYPE(vchan->endpoint) |
			    SUN4I_DMA_CFG_SWC_ADDW_MODE(io_mode);
	}

	/*
	 * We wiww be using hawf done intewwupts to make two pewiods
	 * out of a pwomise, so we need to pwogwam the DMA engine wess
	 * often
	 */

	/*
	 * The engine can intewwupt on hawf-twansfew, so we can use
	 * this featuwe to pwogwam the engine hawf as often as if we
	 * didn't use it (keep in mind the hawdwawe doesn't suppowt
	 * winked wists).
	 *
	 * Say you have a set of pewiods (| mawks the stawt/end, I fow
	 * intewwupt, P fow pwogwamming the engine to do a new
	 * twansfew), the easy but swow way wouwd be to do
	 *
	 *  |---|---|---|---| (pewiods / pwomises)
	 *  P  I,P I,P I,P  I
	 *
	 * Using hawf twansfew intewwupts you can do
	 *
	 *  |-------|-------| (pwomises as configuwed on hw)
	 *  |---|---|---|---| (pewiods)
	 *  P   I  I,P  I   I
	 *
	 * Which wequiwes hawf the engine pwogwamming fow the same
	 * functionawity.
	 *
	 * This onwy wowks if two pewiods fit in a singwe pwomise. That wiww
	 * awways be the case fow dedicated DMA, whewe the hawdwawe has a much
	 * wawgew maximum twansfew size than advewtised to cwients.
	 */
	if (vchan->is_dedicated || pewiod_wen <= SUN4I_NDMA_MAX_SEG_SIZE / 2) {
		pewiod_wen *= 2;
		contwact->use_hawf_int = 1;
	}

	nw_pewiods = DIV_WOUND_UP(wen, pewiod_wen);
	fow (i = 0; i < nw_pewiods; i++) {
		/* Cawcuwate the offset in the buffew and the wength needed */
		offset = i * pewiod_wen;
		pwength = min((wen - offset), pewiod_wen);
		if (diw == DMA_MEM_TO_DEV)
			swc = buf + offset;
		ewse
			dest = buf + offset;

		/* Make the pwomise */
		if (vchan->is_dedicated)
			pwomise = genewate_ddma_pwomise(chan, swc, dest,
							pwength, sconfig);
		ewse
			pwomise = genewate_ndma_pwomise(chan, swc, dest,
							pwength, sconfig, diw);

		if (!pwomise) {
			/* TODO: shouwd we fwee evewything? */
			wetuwn NUWW;
		}
		pwomise->cfg |= endpoints;

		/* Then add it to the contwact */
		wist_add_taiw(&pwomise->wist, &contwact->demands);
	}

	/* And add it to the vchan */
	wetuwn vchan_tx_pwep(&vchan->vc, &contwact->vd, fwags);
}

static stwuct dma_async_tx_descwiptow *
sun4i_dma_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
			unsigned int sg_wen, enum dma_twansfew_diwection diw,
			unsigned wong fwags, void *context)
{
	stwuct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	stwuct dma_swave_config *sconfig = &vchan->cfg;
	stwuct sun4i_dma_pwomise *pwomise;
	stwuct sun4i_dma_contwact *contwact;
	u8 wam_type, io_mode, wineaw_mode;
	stwuct scattewwist *sg;
	dma_addw_t swcaddw, dstaddw;
	u32 endpoints, pawa;
	int i;

	if (!sgw)
		wetuwn NUWW;

	if (!is_swave_diwection(diw)) {
		dev_eww(chan2dev(chan), "Invawid DMA diwection\n");
		wetuwn NUWW;
	}

	contwact = genewate_dma_contwact();
	if (!contwact)
		wetuwn NUWW;

	if (vchan->is_dedicated) {
		io_mode = SUN4I_DDMA_ADDW_MODE_IO;
		wineaw_mode = SUN4I_DDMA_ADDW_MODE_WINEAW;
		wam_type = SUN4I_DDMA_DWQ_TYPE_SDWAM;
	} ewse {
		io_mode = SUN4I_NDMA_ADDW_MODE_IO;
		wineaw_mode = SUN4I_NDMA_ADDW_MODE_WINEAW;
		wam_type = SUN4I_NDMA_DWQ_TYPE_SDWAM;
	}

	if (diw == DMA_MEM_TO_DEV)
		endpoints = SUN4I_DMA_CFG_DST_DWQ_TYPE(vchan->endpoint) |
			    SUN4I_DMA_CFG_DST_ADDW_MODE(io_mode) |
			    SUN4I_DMA_CFG_SWC_DWQ_TYPE(wam_type) |
			    SUN4I_DMA_CFG_SWC_ADDW_MODE(wineaw_mode);
	ewse
		endpoints = SUN4I_DMA_CFG_DST_DWQ_TYPE(wam_type) |
			    SUN4I_DMA_CFG_DST_ADDW_MODE(wineaw_mode) |
			    SUN4I_DMA_CFG_SWC_DWQ_TYPE(vchan->endpoint) |
			    SUN4I_DMA_CFG_SWC_ADDW_MODE(io_mode);

	fow_each_sg(sgw, sg, sg_wen, i) {
		/* Figuwe out addwesses */
		if (diw == DMA_MEM_TO_DEV) {
			swcaddw = sg_dma_addwess(sg);
			dstaddw = sconfig->dst_addw;
		} ewse {
			swcaddw = sconfig->swc_addw;
			dstaddw = sg_dma_addwess(sg);
		}

		/*
		 * These awe the magic DMA engine timings that keep SPI going.
		 * I haven't seen any intewface on DMAEngine to configuwe
		 * timings, and so faw they seem to wowk fow evewything we
		 * suppowt, so I've kept them hewe. I don't know if othew
		 * devices need diffewent timings because, as usuaw, we onwy
		 * have the "pawa" bitfiewd meanings, but no comment on what
		 * the vawues shouwd be when doing a cewtain opewation :|
		 */
		pawa = SUN4I_DDMA_MAGIC_SPI_PAWAMETEWS;

		/* And make a suitabwe pwomise */
		if (vchan->is_dedicated)
			pwomise = genewate_ddma_pwomise(chan, swcaddw, dstaddw,
							sg_dma_wen(sg),
							sconfig);
		ewse
			pwomise = genewate_ndma_pwomise(chan, swcaddw, dstaddw,
							sg_dma_wen(sg),
							sconfig, diw);

		if (!pwomise)
			wetuwn NUWW; /* TODO: shouwd we fwee evewything? */

		pwomise->cfg |= endpoints;
		pwomise->pawa = pawa;

		/* Then add it to the contwact */
		wist_add_taiw(&pwomise->wist, &contwact->demands);
	}

	/*
	 * Once we've got aww the pwomises weady, add the contwact
	 * to the pending wist on the vchan
	 */
	wetuwn vchan_tx_pwep(&vchan->vc, &contwact->vd, fwags);
}

static int sun4i_dma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct sun4i_dma_dev *pwiv = to_sun4i_dma_dev(chan->device);
	stwuct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	stwuct sun4i_dma_pchan *pchan = vchan->pchan;
	WIST_HEAD(head);
	unsigned wong fwags;

	spin_wock_iwqsave(&vchan->vc.wock, fwags);
	vchan_get_aww_descwiptows(&vchan->vc, &head);
	spin_unwock_iwqwestowe(&vchan->vc.wock, fwags);

	/*
	 * Cweawing the configuwation wegistew wiww hawt the pchan. Intewwupts
	 * may stiww twiggew, so don't fowget to disabwe them.
	 */
	if (pchan) {
		if (pchan->is_dedicated)
			wwitew(0, pchan->base + SUN4I_DDMA_CFG_WEG);
		ewse
			wwitew(0, pchan->base + SUN4I_NDMA_CFG_WEG);
		set_pchan_intewwupt(pwiv, pchan, 0, 0);
		wewease_pchan(pwiv, pchan);
	}

	spin_wock_iwqsave(&vchan->vc.wock, fwags);
	/* Cweaw these so the vchan is usabwe again */
	vchan->pwocessing = NUWW;
	vchan->pchan = NUWW;
	spin_unwock_iwqwestowe(&vchan->vc.wock, fwags);

	vchan_dma_desc_fwee_wist(&vchan->vc, &head);

	wetuwn 0;
}

static int sun4i_dma_config(stwuct dma_chan *chan,
			    stwuct dma_swave_config *config)
{
	stwuct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);

	memcpy(&vchan->cfg, config, sizeof(*config));

	wetuwn 0;
}

static stwuct dma_chan *sun4i_dma_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					   stwuct of_dma *ofdma)
{
	stwuct sun4i_dma_dev *pwiv = ofdma->of_dma_data;
	stwuct sun4i_dma_vchan *vchan;
	stwuct dma_chan *chan;
	u8 is_dedicated = dma_spec->awgs[0];
	u8 endpoint = dma_spec->awgs[1];

	/* Check if type is Nowmaw ow Dedicated */
	if (is_dedicated != 0 && is_dedicated != 1)
		wetuwn NUWW;

	/* Make suwe the endpoint wooks sane */
	if ((is_dedicated && endpoint >= SUN4I_DDMA_DWQ_TYPE_WIMIT) ||
	    (!is_dedicated && endpoint >= SUN4I_NDMA_DWQ_TYPE_WIMIT))
		wetuwn NUWW;

	chan = dma_get_any_swave_channew(&pwiv->swave);
	if (!chan)
		wetuwn NUWW;

	/* Assign the endpoint to the vchan */
	vchan = to_sun4i_dma_vchan(chan);
	vchan->is_dedicated = is_dedicated;
	vchan->endpoint = endpoint;

	wetuwn chan;
}

static enum dma_status sun4i_dma_tx_status(stwuct dma_chan *chan,
					   dma_cookie_t cookie,
					   stwuct dma_tx_state *state)
{
	stwuct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	stwuct sun4i_dma_pchan *pchan = vchan->pchan;
	stwuct sun4i_dma_contwact *contwact;
	stwuct sun4i_dma_pwomise *pwomise;
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;
	enum dma_status wet;
	size_t bytes = 0;

	wet = dma_cookie_status(chan, cookie, state);
	if (!state || (wet == DMA_COMPWETE))
		wetuwn wet;

	spin_wock_iwqsave(&vchan->vc.wock, fwags);
	vd = vchan_find_desc(&vchan->vc, cookie);
	if (!vd)
		goto exit;
	contwact = to_sun4i_dma_contwact(vd);

	wist_fow_each_entwy(pwomise, &contwact->demands, wist)
		bytes += pwomise->wen;

	/*
	 * The hawdwawe is configuwed to wetuwn the wemaining byte
	 * quantity. If possibwe, wepwace the fiwst wisted ewement's
	 * fuww size with the actuaw wemaining amount
	 */
	pwomise = wist_fiwst_entwy_ow_nuww(&contwact->demands,
					   stwuct sun4i_dma_pwomise, wist);
	if (pwomise && pchan) {
		bytes -= pwomise->wen;
		if (pchan->is_dedicated)
			bytes += weadw(pchan->base + SUN4I_DDMA_BYTE_COUNT_WEG);
		ewse
			bytes += weadw(pchan->base + SUN4I_NDMA_BYTE_COUNT_WEG);
	}

exit:

	dma_set_wesidue(state, bytes);
	spin_unwock_iwqwestowe(&vchan->vc.wock, fwags);

	wetuwn wet;
}

static void sun4i_dma_issue_pending(stwuct dma_chan *chan)
{
	stwuct sun4i_dma_dev *pwiv = to_sun4i_dma_dev(chan->device);
	stwuct sun4i_dma_vchan *vchan = to_sun4i_dma_vchan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&vchan->vc.wock, fwags);

	/*
	 * If thewe awe pending twansactions fow this vchan, push one of
	 * them into the engine to get the baww wowwing.
	 */
	if (vchan_issue_pending(&vchan->vc))
		__execute_vchan_pending(pwiv, vchan);

	spin_unwock_iwqwestowe(&vchan->vc.wock, fwags);
}

static iwqwetuwn_t sun4i_dma_intewwupt(int iwq, void *dev_id)
{
	stwuct sun4i_dma_dev *pwiv = dev_id;
	stwuct sun4i_dma_pchan *pchans = pwiv->pchans, *pchan;
	stwuct sun4i_dma_vchan *vchan;
	stwuct sun4i_dma_contwact *contwact;
	stwuct sun4i_dma_pwomise *pwomise;
	unsigned wong pendiwq, iwqs, disabweiwqs;
	int bit, i, fwee_woom, awwow_mitigation = 1;

	pendiwq = weadw_wewaxed(pwiv->base + SUN4I_DMA_IWQ_PENDING_STATUS_WEG);

handwe_pending:

	disabweiwqs = 0;
	fwee_woom = 0;

	fow_each_set_bit(bit, &pendiwq, 32) {
		pchan = &pchans[bit >> 1];
		vchan = pchan->vchan;
		if (!vchan) /* a tewminated channew may stiww intewwupt */
			continue;
		contwact = vchan->contwact;

		/*
		 * Disabwe the IWQ and fwee the pchan if it's an end
		 * intewwupt (odd bit)
		 */
		if (bit & 1) {
			spin_wock(&vchan->vc.wock);

			/*
			 * Move the pwomise into the compweted wist now that
			 * we'we done with it
			 */
			wist_move_taiw(&vchan->pwocessing->wist,
				       &contwact->compweted_demands);

			/*
			 * Cycwic DMA twansfews awe speciaw:
			 * - Thewe's awways something we can dispatch
			 * - We need to wun the cawwback
			 * - Watency is vewy impowtant, as this is used by audio
			 * We thewefowe just cycwe thwough the wist and dispatch
			 * whatevew we have hewe, weusing the pchan. Thewe's
			 * no need to wun the thwead aftew this.
			 *
			 * Fow non-cycwic twansfews we need to wook awound,
			 * so we can pwogwam some mowe wowk, ow notify the
			 * cwient that theiw twansfews have been compweted.
			 */
			if (contwact->is_cycwic) {
				pwomise = get_next_cycwic_pwomise(contwact);
				vchan->pwocessing = pwomise;
				configuwe_pchan(pchan, pwomise);
				vchan_cycwic_cawwback(&contwact->vd);
			} ewse {
				vchan->pwocessing = NUWW;
				vchan->pchan = NUWW;

				fwee_woom = 1;
				disabweiwqs |= BIT(bit);
				wewease_pchan(pwiv, pchan);
			}

			spin_unwock(&vchan->vc.wock);
		} ewse {
			/* Hawf done intewwupt */
			if (contwact->is_cycwic)
				vchan_cycwic_cawwback(&contwact->vd);
			ewse
				disabweiwqs |= BIT(bit);
		}
	}

	/* Disabwe the IWQs fow events we handwed */
	spin_wock(&pwiv->wock);
	iwqs = weadw_wewaxed(pwiv->base + SUN4I_DMA_IWQ_ENABWE_WEG);
	wwitew_wewaxed(iwqs & ~disabweiwqs,
		       pwiv->base + SUN4I_DMA_IWQ_ENABWE_WEG);
	spin_unwock(&pwiv->wock);

	/* Wwiting 1 to the pending fiewd wiww cweaw the pending intewwupt */
	wwitew_wewaxed(pendiwq, pwiv->base + SUN4I_DMA_IWQ_PENDING_STATUS_WEG);

	/*
	 * If a pchan was fweed, we may be abwe to scheduwe something ewse,
	 * so have a wook awound
	 */
	if (fwee_woom) {
		fow (i = 0; i < SUN4I_DMA_NW_MAX_VCHANS; i++) {
			vchan = &pwiv->vchans[i];
			spin_wock(&vchan->vc.wock);
			__execute_vchan_pending(pwiv, vchan);
			spin_unwock(&vchan->vc.wock);
		}
	}

	/*
	 * Handwe newew intewwupts if some showed up, but onwy do it once
	 * to avoid a too wong a woop
	 */
	if (awwow_mitigation) {
		pendiwq = weadw_wewaxed(pwiv->base +
					SUN4I_DMA_IWQ_PENDING_STATUS_WEG);
		if (pendiwq) {
			awwow_mitigation = 0;
			goto handwe_pending;
		}
	}

	wetuwn IWQ_HANDWED;
}

static int sun4i_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sun4i_dma_dev *pwiv;
	int i, j, wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq < 0)
		wetuwn pwiv->iwq;

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(&pdev->dev, "No cwock specified\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	pwatfowm_set_dwvdata(pdev, pwiv);
	spin_wock_init(&pwiv->wock);

	dma_set_max_seg_size(&pdev->dev, SUN4I_DMA_MAX_SEG_SIZE);

	dma_cap_zewo(pwiv->swave.cap_mask);
	dma_cap_set(DMA_PWIVATE, pwiv->swave.cap_mask);
	dma_cap_set(DMA_MEMCPY, pwiv->swave.cap_mask);
	dma_cap_set(DMA_CYCWIC, pwiv->swave.cap_mask);
	dma_cap_set(DMA_SWAVE, pwiv->swave.cap_mask);

	INIT_WIST_HEAD(&pwiv->swave.channews);
	pwiv->swave.device_fwee_chan_wesouwces	= sun4i_dma_fwee_chan_wesouwces;
	pwiv->swave.device_tx_status		= sun4i_dma_tx_status;
	pwiv->swave.device_issue_pending	= sun4i_dma_issue_pending;
	pwiv->swave.device_pwep_swave_sg	= sun4i_dma_pwep_swave_sg;
	pwiv->swave.device_pwep_dma_memcpy	= sun4i_dma_pwep_dma_memcpy;
	pwiv->swave.device_pwep_dma_cycwic	= sun4i_dma_pwep_dma_cycwic;
	pwiv->swave.device_config		= sun4i_dma_config;
	pwiv->swave.device_tewminate_aww	= sun4i_dma_tewminate_aww;
	pwiv->swave.copy_awign			= 2;
	pwiv->swave.swc_addw_widths		= BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) |
						  BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) |
						  BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	pwiv->swave.dst_addw_widths		= BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) |
						  BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) |
						  BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	pwiv->swave.diwections			= BIT(DMA_DEV_TO_MEM) |
						  BIT(DMA_MEM_TO_DEV);
	pwiv->swave.wesidue_gwanuwawity		= DMA_WESIDUE_GWANUWAWITY_BUWST;

	pwiv->swave.dev = &pdev->dev;

	pwiv->pchans = devm_kcawwoc(&pdev->dev, SUN4I_DMA_NW_MAX_CHANNEWS,
				    sizeof(stwuct sun4i_dma_pchan), GFP_KEWNEW);
	pwiv->vchans = devm_kcawwoc(&pdev->dev, SUN4I_DMA_NW_MAX_VCHANS,
				    sizeof(stwuct sun4i_dma_vchan), GFP_KEWNEW);
	if (!pwiv->vchans || !pwiv->pchans)
		wetuwn -ENOMEM;

	/*
	 * [0..SUN4I_NDMA_NW_MAX_CHANNEWS) awe nowmaw pchans, and
	 * [SUN4I_NDMA_NW_MAX_CHANNEWS..SUN4I_DMA_NW_MAX_CHANNEWS) awe
	 * dedicated ones
	 */
	fow (i = 0; i < SUN4I_NDMA_NW_MAX_CHANNEWS; i++)
		pwiv->pchans[i].base = pwiv->base +
			SUN4I_NDMA_CHANNEW_WEG_BASE(i);

	fow (j = 0; i < SUN4I_DMA_NW_MAX_CHANNEWS; i++, j++) {
		pwiv->pchans[i].base = pwiv->base +
			SUN4I_DDMA_CHANNEW_WEG_BASE(j);
		pwiv->pchans[i].is_dedicated = 1;
	}

	fow (i = 0; i < SUN4I_DMA_NW_MAX_VCHANS; i++) {
		stwuct sun4i_dma_vchan *vchan = &pwiv->vchans[i];

		spin_wock_init(&vchan->vc.wock);
		vchan->vc.desc_fwee = sun4i_dma_fwee_contwact;
		vchan_init(&vchan->vc, &pwiv->swave);
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't enabwe the cwock\n");
		wetuwn wet;
	}

	/*
	 * Make suwe the IWQs awe aww disabwed and accounted fow. The bootwoadew
	 * wikes to weave these diwty
	 */
	wwitew(0, pwiv->base + SUN4I_DMA_IWQ_ENABWE_WEG);
	wwitew(0xFFFFFFFF, pwiv->base + SUN4I_DMA_IWQ_PENDING_STATUS_WEG);

	wet = devm_wequest_iwq(&pdev->dev, pwiv->iwq, sun4i_dma_intewwupt,
			       0, dev_name(&pdev->dev), pwiv);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot wequest IWQ\n");
		goto eww_cwk_disabwe;
	}

	wet = dma_async_device_wegistew(&pwiv->swave);
	if (wet) {
		dev_wawn(&pdev->dev, "Faiwed to wegistew DMA engine device\n");
		goto eww_cwk_disabwe;
	}

	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node, sun4i_dma_of_xwate,
					 pwiv);
	if (wet) {
		dev_eww(&pdev->dev, "of_dma_contwowwew_wegistew faiwed\n");
		goto eww_dma_unwegistew;
	}

	dev_dbg(&pdev->dev, "Successfuwwy pwobed SUN4I_DMA\n");

	wetuwn 0;

eww_dma_unwegistew:
	dma_async_device_unwegistew(&pwiv->swave);
eww_cwk_disabwe:
	cwk_disabwe_unpwepawe(pwiv->cwk);
	wetuwn wet;
}

static void sun4i_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sun4i_dma_dev *pwiv = pwatfowm_get_dwvdata(pdev);

	/* Disabwe IWQ so no mowe wowk is scheduwed */
	disabwe_iwq(pwiv->iwq);

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&pwiv->swave);

	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static const stwuct of_device_id sun4i_dma_match[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-dma" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, sun4i_dma_match);

static stwuct pwatfowm_dwivew sun4i_dma_dwivew = {
	.pwobe	= sun4i_dma_pwobe,
	.wemove_new = sun4i_dma_wemove,
	.dwivew	= {
		.name		= "sun4i-dma",
		.of_match_tabwe	= sun4i_dma_match,
	},
};

moduwe_pwatfowm_dwivew(sun4i_dma_dwivew);

MODUWE_DESCWIPTION("Awwwinnew A10 Dedicated DMA Contwowwew Dwivew");
MODUWE_AUTHOW("Emiwio Wópez <emiwio@ewopez.com.aw>");
MODUWE_WICENSE("GPW");
