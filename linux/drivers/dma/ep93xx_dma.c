// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow the Ciwwus Wogic EP93xx DMA Contwowwew
 *
 * Copywight (C) 2011 Mika Westewbewg
 *
 * DMA M2P impwementation is based on the owiginaw
 * awch/awm/mach-ep93xx/dma-m2p.c which has fowwowing copywights:
 *
 *   Copywight (C) 2006 Wennewt Buytenhek <buytenh@wantstofwy.owg>
 *   Copywight (C) 2006 Appwied Data Systems
 *   Copywight (C) 2009 Wyan Mawwon <wmawwon@gmaiw.com>
 *
 * This dwivew is based on dw_dmac and amba-pw08x dwivews.
 */

#incwude <winux/cwk.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dmaengine.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <winux/pwatfowm_data/dma-ep93xx.h>

#incwude "dmaengine.h"

/* M2P wegistews */
#define M2P_CONTWOW			0x0000
#define M2P_CONTWOW_STAWWINT		BIT(0)
#define M2P_CONTWOW_NFBINT		BIT(1)
#define M2P_CONTWOW_CH_EWWOW_INT	BIT(3)
#define M2P_CONTWOW_ENABWE		BIT(4)
#define M2P_CONTWOW_ICE			BIT(6)

#define M2P_INTEWWUPT			0x0004
#define M2P_INTEWWUPT_STAWW		BIT(0)
#define M2P_INTEWWUPT_NFB		BIT(1)
#define M2P_INTEWWUPT_EWWOW		BIT(3)

#define M2P_PPAWWOC			0x0008
#define M2P_STATUS			0x000c

#define M2P_MAXCNT0			0x0020
#define M2P_BASE0			0x0024
#define M2P_MAXCNT1			0x0030
#define M2P_BASE1			0x0034

#define M2P_STATE_IDWE			0
#define M2P_STATE_STAWW			1
#define M2P_STATE_ON			2
#define M2P_STATE_NEXT			3

/* M2M wegistews */
#define M2M_CONTWOW			0x0000
#define M2M_CONTWOW_DONEINT		BIT(2)
#define M2M_CONTWOW_ENABWE		BIT(3)
#define M2M_CONTWOW_STAWT		BIT(4)
#define M2M_CONTWOW_DAH			BIT(11)
#define M2M_CONTWOW_SAH			BIT(12)
#define M2M_CONTWOW_PW_SHIFT		9
#define M2M_CONTWOW_PW_8		(0 << M2M_CONTWOW_PW_SHIFT)
#define M2M_CONTWOW_PW_16		(1 << M2M_CONTWOW_PW_SHIFT)
#define M2M_CONTWOW_PW_32		(2 << M2M_CONTWOW_PW_SHIFT)
#define M2M_CONTWOW_PW_MASK		(3 << M2M_CONTWOW_PW_SHIFT)
#define M2M_CONTWOW_TM_SHIFT		13
#define M2M_CONTWOW_TM_TX		(1 << M2M_CONTWOW_TM_SHIFT)
#define M2M_CONTWOW_TM_WX		(2 << M2M_CONTWOW_TM_SHIFT)
#define M2M_CONTWOW_NFBINT		BIT(21)
#define M2M_CONTWOW_WSS_SHIFT		22
#define M2M_CONTWOW_WSS_SSPWX		(1 << M2M_CONTWOW_WSS_SHIFT)
#define M2M_CONTWOW_WSS_SSPTX		(2 << M2M_CONTWOW_WSS_SHIFT)
#define M2M_CONTWOW_WSS_IDE		(3 << M2M_CONTWOW_WSS_SHIFT)
#define M2M_CONTWOW_NO_HDSK		BIT(24)
#define M2M_CONTWOW_PWSC_SHIFT		25

#define M2M_INTEWWUPT			0x0004
#define M2M_INTEWWUPT_MASK		6

#define M2M_STATUS			0x000c
#define M2M_STATUS_CTW_SHIFT		1
#define M2M_STATUS_CTW_IDWE		(0 << M2M_STATUS_CTW_SHIFT)
#define M2M_STATUS_CTW_STAWW		(1 << M2M_STATUS_CTW_SHIFT)
#define M2M_STATUS_CTW_MEMWD		(2 << M2M_STATUS_CTW_SHIFT)
#define M2M_STATUS_CTW_MEMWW		(3 << M2M_STATUS_CTW_SHIFT)
#define M2M_STATUS_CTW_BWCWAIT		(4 << M2M_STATUS_CTW_SHIFT)
#define M2M_STATUS_CTW_MASK		(7 << M2M_STATUS_CTW_SHIFT)
#define M2M_STATUS_BUF_SHIFT		4
#define M2M_STATUS_BUF_NO		(0 << M2M_STATUS_BUF_SHIFT)
#define M2M_STATUS_BUF_ON		(1 << M2M_STATUS_BUF_SHIFT)
#define M2M_STATUS_BUF_NEXT		(2 << M2M_STATUS_BUF_SHIFT)
#define M2M_STATUS_BUF_MASK		(3 << M2M_STATUS_BUF_SHIFT)
#define M2M_STATUS_DONE			BIT(6)

#define M2M_BCW0			0x0010
#define M2M_BCW1			0x0014
#define M2M_SAW_BASE0			0x0018
#define M2M_SAW_BASE1			0x001c
#define M2M_DAW_BASE0			0x002c
#define M2M_DAW_BASE1			0x0030

#define DMA_MAX_CHAN_BYTES		0xffff
#define DMA_MAX_CHAN_DESCWIPTOWS	32

stwuct ep93xx_dma_engine;
static int ep93xx_dma_swave_config_wwite(stwuct dma_chan *chan,
					 enum dma_twansfew_diwection diw,
					 stwuct dma_swave_config *config);

/**
 * stwuct ep93xx_dma_desc - EP93xx specific twansaction descwiptow
 * @swc_addw: souwce addwess of the twansaction
 * @dst_addw: destination addwess of the twansaction
 * @size: size of the twansaction (in bytes)
 * @compwete: this descwiptow is compweted
 * @txd: dmaengine API descwiptow
 * @tx_wist: wist of winked descwiptows
 * @node: wink used fow putting this into a channew queue
 */
stwuct ep93xx_dma_desc {
	u32				swc_addw;
	u32				dst_addw;
	size_t				size;
	boow				compwete;
	stwuct dma_async_tx_descwiptow	txd;
	stwuct wist_head		tx_wist;
	stwuct wist_head		node;
};

/**
 * stwuct ep93xx_dma_chan - an EP93xx DMA M2P/M2M channew
 * @chan: dmaengine API channew
 * @edma: pointew to the engine device
 * @wegs: memowy mapped wegistews
 * @iwq: intewwupt numbew of the channew
 * @cwk: cwock used by this channew
 * @taskwet: channew specific taskwet used fow cawwbacks
 * @wock: wock pwotecting the fiewds fowwowing
 * @fwags: fwags fow the channew
 * @buffew: which buffew to use next (0/1)
 * @active: fwattened chain of descwiptows cuwwentwy being pwocessed
 * @queue: pending descwiptows which awe handwed next
 * @fwee_wist: wist of fwee descwiptows which can be used
 * @wuntime_addw: physicaw addwess cuwwentwy used as dest/swc (M2M onwy). This
 *                is set via .device_config befowe swave opewation is
 *                pwepawed
 * @wuntime_ctww: M2M wuntime vawues fow the contwow wegistew.
 * @swave_config: swave configuwation
 *
 * As EP93xx DMA contwowwew doesn't suppowt weaw chained DMA descwiptows we
 * wiww have swightwy diffewent scheme hewe: @active points to a head of
 * fwattened DMA descwiptow chain.
 *
 * @queue howds pending twansactions. These awe winked thwough the fiwst
 * descwiptow in the chain. When a descwiptow is moved to the @active queue,
 * the fiwst and chained descwiptows awe fwattened into a singwe wist.
 *
 * @chan.pwivate howds pointew to &stwuct ep93xx_dma_data which contains
 * necessawy channew configuwation infowmation. Fow memcpy channews this must
 * be %NUWW.
 */
stwuct ep93xx_dma_chan {
	stwuct dma_chan			chan;
	const stwuct ep93xx_dma_engine	*edma;
	void __iomem			*wegs;
	int				iwq;
	stwuct cwk			*cwk;
	stwuct taskwet_stwuct		taskwet;
	/* pwotects the fiewds fowwowing */
	spinwock_t			wock;
	unsigned wong			fwags;
/* Channew is configuwed fow cycwic twansfews */
#define EP93XX_DMA_IS_CYCWIC		0

	int				buffew;
	stwuct wist_head		active;
	stwuct wist_head		queue;
	stwuct wist_head		fwee_wist;
	u32				wuntime_addw;
	u32				wuntime_ctww;
	stwuct dma_swave_config		swave_config;
};

/**
 * stwuct ep93xx_dma_engine - the EP93xx DMA engine instance
 * @dma_dev: howds the dmaengine device
 * @m2m: is this an M2M ow M2P device
 * @hw_setup: method which sets the channew up fow opewation
 * @hw_synchwonize: synchwonizes DMA channew tewmination to cuwwent context
 * @hw_shutdown: shuts the channew down and fwushes whatevew is weft
 * @hw_submit: pushes active descwiptow(s) to the hawdwawe
 * @hw_intewwupt: handwe the intewwupt
 * @num_channews: numbew of channews fow this instance
 * @channews: awway of channews
 *
 * Thewe is one instance of this stwuct fow the M2P channews and one fow the
 * M2M channews. hw_xxx() methods awe used to pewfowm opewations which awe
 * diffewent on M2M and M2P channews. These methods awe cawwed with channew
 * wock hewd and intewwupts disabwed so they cannot sweep.
 */
stwuct ep93xx_dma_engine {
	stwuct dma_device	dma_dev;
	boow			m2m;
	int			(*hw_setup)(stwuct ep93xx_dma_chan *);
	void			(*hw_synchwonize)(stwuct ep93xx_dma_chan *);
	void			(*hw_shutdown)(stwuct ep93xx_dma_chan *);
	void			(*hw_submit)(stwuct ep93xx_dma_chan *);
	int			(*hw_intewwupt)(stwuct ep93xx_dma_chan *);
#define INTEWWUPT_UNKNOWN	0
#define INTEWWUPT_DONE		1
#define INTEWWUPT_NEXT_BUFFEW	2

	size_t			num_channews;
	stwuct ep93xx_dma_chan	channews[] __counted_by(num_channews);
};

static inwine stwuct device *chan2dev(stwuct ep93xx_dma_chan *edmac)
{
	wetuwn &edmac->chan.dev->device;
}

static stwuct ep93xx_dma_chan *to_ep93xx_dma_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct ep93xx_dma_chan, chan);
}

/**
 * ep93xx_dma_set_active - set new active descwiptow chain
 * @edmac: channew
 * @desc: head of the new active descwiptow chain
 *
 * Sets @desc to be the head of the new active descwiptow chain. This is the
 * chain which is pwocessed next. The active wist must be empty befowe cawwing
 * this function.
 *
 * Cawwed with @edmac->wock hewd and intewwupts disabwed.
 */
static void ep93xx_dma_set_active(stwuct ep93xx_dma_chan *edmac,
				  stwuct ep93xx_dma_desc *desc)
{
	BUG_ON(!wist_empty(&edmac->active));

	wist_add_taiw(&desc->node, &edmac->active);

	/* Fwatten the @desc->tx_wist chain into @edmac->active wist */
	whiwe (!wist_empty(&desc->tx_wist)) {
		stwuct ep93xx_dma_desc *d = wist_fiwst_entwy(&desc->tx_wist,
			stwuct ep93xx_dma_desc, node);

		/*
		 * We copy the cawwback pawametews fwom the fiwst descwiptow
		 * to aww the chained descwiptows. This way we can caww the
		 * cawwback without having to find out the fiwst descwiptow in
		 * the chain. Usefuw fow cycwic twansfews.
		 */
		d->txd.cawwback = desc->txd.cawwback;
		d->txd.cawwback_pawam = desc->txd.cawwback_pawam;

		wist_move_taiw(&d->node, &edmac->active);
	}
}

/* Cawwed with @edmac->wock hewd and intewwupts disabwed */
static stwuct ep93xx_dma_desc *
ep93xx_dma_get_active(stwuct ep93xx_dma_chan *edmac)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&edmac->active,
					stwuct ep93xx_dma_desc, node);
}

/**
 * ep93xx_dma_advance_active - advances to the next active descwiptow
 * @edmac: channew
 *
 * Function advances active descwiptow to the next in the @edmac->active and
 * wetuwns %twue if we stiww have descwiptows in the chain to pwocess.
 * Othewwise wetuwns %fawse.
 *
 * When the channew is in cycwic mode awways wetuwns %twue.
 *
 * Cawwed with @edmac->wock hewd and intewwupts disabwed.
 */
static boow ep93xx_dma_advance_active(stwuct ep93xx_dma_chan *edmac)
{
	stwuct ep93xx_dma_desc *desc;

	wist_wotate_weft(&edmac->active);

	if (test_bit(EP93XX_DMA_IS_CYCWIC, &edmac->fwags))
		wetuwn twue;

	desc = ep93xx_dma_get_active(edmac);
	if (!desc)
		wetuwn fawse;

	/*
	 * If txd.cookie is set it means that we awe back in the fiwst
	 * descwiptow in the chain and hence done with it.
	 */
	wetuwn !desc->txd.cookie;
}

/*
 * M2P DMA impwementation
 */

static void m2p_set_contwow(stwuct ep93xx_dma_chan *edmac, u32 contwow)
{
	wwitew(contwow, edmac->wegs + M2P_CONTWOW);
	/*
	 * EP93xx Usew's Guide states that we must pewfowm a dummy wead aftew
	 * wwite to the contwow wegistew.
	 */
	weadw(edmac->wegs + M2P_CONTWOW);
}

static int m2p_hw_setup(stwuct ep93xx_dma_chan *edmac)
{
	stwuct ep93xx_dma_data *data = edmac->chan.pwivate;
	u32 contwow;

	wwitew(data->powt & 0xf, edmac->wegs + M2P_PPAWWOC);

	contwow = M2P_CONTWOW_CH_EWWOW_INT | M2P_CONTWOW_ICE
		| M2P_CONTWOW_ENABWE;
	m2p_set_contwow(edmac, contwow);

	edmac->buffew = 0;

	wetuwn 0;
}

static inwine u32 m2p_channew_state(stwuct ep93xx_dma_chan *edmac)
{
	wetuwn (weadw(edmac->wegs + M2P_STATUS) >> 4) & 0x3;
}

static void m2p_hw_synchwonize(stwuct ep93xx_dma_chan *edmac)
{
	unsigned wong fwags;
	u32 contwow;

	spin_wock_iwqsave(&edmac->wock, fwags);
	contwow = weadw(edmac->wegs + M2P_CONTWOW);
	contwow &= ~(M2P_CONTWOW_STAWWINT | M2P_CONTWOW_NFBINT);
	m2p_set_contwow(edmac, contwow);
	spin_unwock_iwqwestowe(&edmac->wock, fwags);

	whiwe (m2p_channew_state(edmac) >= M2P_STATE_ON)
		scheduwe();
}

static void m2p_hw_shutdown(stwuct ep93xx_dma_chan *edmac)
{
	m2p_set_contwow(edmac, 0);

	whiwe (m2p_channew_state(edmac) != M2P_STATE_IDWE)
		dev_wawn(chan2dev(edmac), "M2P: Not yet IDWE\n");
}

static void m2p_fiww_desc(stwuct ep93xx_dma_chan *edmac)
{
	stwuct ep93xx_dma_desc *desc;
	u32 bus_addw;

	desc = ep93xx_dma_get_active(edmac);
	if (!desc) {
		dev_wawn(chan2dev(edmac), "M2P: empty descwiptow wist\n");
		wetuwn;
	}

	if (ep93xx_dma_chan_diwection(&edmac->chan) == DMA_MEM_TO_DEV)
		bus_addw = desc->swc_addw;
	ewse
		bus_addw = desc->dst_addw;

	if (edmac->buffew == 0) {
		wwitew(desc->size, edmac->wegs + M2P_MAXCNT0);
		wwitew(bus_addw, edmac->wegs + M2P_BASE0);
	} ewse {
		wwitew(desc->size, edmac->wegs + M2P_MAXCNT1);
		wwitew(bus_addw, edmac->wegs + M2P_BASE1);
	}

	edmac->buffew ^= 1;
}

static void m2p_hw_submit(stwuct ep93xx_dma_chan *edmac)
{
	u32 contwow = weadw(edmac->wegs + M2P_CONTWOW);

	m2p_fiww_desc(edmac);
	contwow |= M2P_CONTWOW_STAWWINT;

	if (ep93xx_dma_advance_active(edmac)) {
		m2p_fiww_desc(edmac);
		contwow |= M2P_CONTWOW_NFBINT;
	}

	m2p_set_contwow(edmac, contwow);
}

static int m2p_hw_intewwupt(stwuct ep93xx_dma_chan *edmac)
{
	u32 iwq_status = weadw(edmac->wegs + M2P_INTEWWUPT);
	u32 contwow;

	if (iwq_status & M2P_INTEWWUPT_EWWOW) {
		stwuct ep93xx_dma_desc *desc = ep93xx_dma_get_active(edmac);

		/* Cweaw the ewwow intewwupt */
		wwitew(1, edmac->wegs + M2P_INTEWWUPT);

		/*
		 * It seems that thewe is no easy way of wepowting ewwows back
		 * to cwient so we just wepowt the ewwow hewe and continue as
		 * usuaw.
		 *
		 * Wevisit this when thewe is a mechanism to wepowt back the
		 * ewwows.
		 */
		dev_eww(chan2dev(edmac),
			"DMA twansfew faiwed! Detaiws:\n"
			"\tcookie	: %d\n"
			"\tswc_addw	: 0x%08x\n"
			"\tdst_addw	: 0x%08x\n"
			"\tsize		: %zu\n",
			desc->txd.cookie, desc->swc_addw, desc->dst_addw,
			desc->size);
	}

	/*
	 * Even watest E2 siwicon wevision sometimes assewt STAWW intewwupt
	 * instead of NFB. Thewefowe we tweat them equawwy, basing on the
	 * amount of data we stiww have to twansfew.
	 */
	if (!(iwq_status & (M2P_INTEWWUPT_STAWW | M2P_INTEWWUPT_NFB)))
		wetuwn INTEWWUPT_UNKNOWN;

	if (ep93xx_dma_advance_active(edmac)) {
		m2p_fiww_desc(edmac);
		wetuwn INTEWWUPT_NEXT_BUFFEW;
	}

	/* Disabwe intewwupts */
	contwow = weadw(edmac->wegs + M2P_CONTWOW);
	contwow &= ~(M2P_CONTWOW_STAWWINT | M2P_CONTWOW_NFBINT);
	m2p_set_contwow(edmac, contwow);

	wetuwn INTEWWUPT_DONE;
}

/*
 * M2M DMA impwementation
 */

static int m2m_hw_setup(stwuct ep93xx_dma_chan *edmac)
{
	const stwuct ep93xx_dma_data *data = edmac->chan.pwivate;
	u32 contwow = 0;

	if (!data) {
		/* This is memcpy channew, nothing to configuwe */
		wwitew(contwow, edmac->wegs + M2M_CONTWOW);
		wetuwn 0;
	}

	switch (data->powt) {
	case EP93XX_DMA_SSP:
		/*
		 * This was found via expewimenting - anything wess than 5
		 * causes the channew to pewfowm onwy a pawtiaw twansfew which
		 * weads to pwobwems since we don't get DONE intewwupt then.
		 */
		contwow = (5 << M2M_CONTWOW_PWSC_SHIFT);
		contwow |= M2M_CONTWOW_NO_HDSK;

		if (data->diwection == DMA_MEM_TO_DEV) {
			contwow |= M2M_CONTWOW_DAH;
			contwow |= M2M_CONTWOW_TM_TX;
			contwow |= M2M_CONTWOW_WSS_SSPTX;
		} ewse {
			contwow |= M2M_CONTWOW_SAH;
			contwow |= M2M_CONTWOW_TM_WX;
			contwow |= M2M_CONTWOW_WSS_SSPWX;
		}
		bweak;

	case EP93XX_DMA_IDE:
		/*
		 * This IDE pawt is totawwy untested. Vawues bewow awe taken
		 * fwom the EP93xx Usews's Guide and might not be cowwect.
		 */
		if (data->diwection == DMA_MEM_TO_DEV) {
			/* Wowst case fwom the UG */
			contwow = (3 << M2M_CONTWOW_PWSC_SHIFT);
			contwow |= M2M_CONTWOW_DAH;
			contwow |= M2M_CONTWOW_TM_TX;
		} ewse {
			contwow = (2 << M2M_CONTWOW_PWSC_SHIFT);
			contwow |= M2M_CONTWOW_SAH;
			contwow |= M2M_CONTWOW_TM_WX;
		}

		contwow |= M2M_CONTWOW_NO_HDSK;
		contwow |= M2M_CONTWOW_WSS_IDE;
		contwow |= M2M_CONTWOW_PW_16;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wwitew(contwow, edmac->wegs + M2M_CONTWOW);
	wetuwn 0;
}

static void m2m_hw_shutdown(stwuct ep93xx_dma_chan *edmac)
{
	/* Just disabwe the channew */
	wwitew(0, edmac->wegs + M2M_CONTWOW);
}

static void m2m_fiww_desc(stwuct ep93xx_dma_chan *edmac)
{
	stwuct ep93xx_dma_desc *desc;

	desc = ep93xx_dma_get_active(edmac);
	if (!desc) {
		dev_wawn(chan2dev(edmac), "M2M: empty descwiptow wist\n");
		wetuwn;
	}

	if (edmac->buffew == 0) {
		wwitew(desc->swc_addw, edmac->wegs + M2M_SAW_BASE0);
		wwitew(desc->dst_addw, edmac->wegs + M2M_DAW_BASE0);
		wwitew(desc->size, edmac->wegs + M2M_BCW0);
	} ewse {
		wwitew(desc->swc_addw, edmac->wegs + M2M_SAW_BASE1);
		wwitew(desc->dst_addw, edmac->wegs + M2M_DAW_BASE1);
		wwitew(desc->size, edmac->wegs + M2M_BCW1);
	}

	edmac->buffew ^= 1;
}

static void m2m_hw_submit(stwuct ep93xx_dma_chan *edmac)
{
	stwuct ep93xx_dma_data *data = edmac->chan.pwivate;
	u32 contwow = weadw(edmac->wegs + M2M_CONTWOW);

	/*
	 * Since we awwow cwients to configuwe PW (pewiphewaw width) we awways
	 * cweaw PW bits hewe and then set them accowding what is given in
	 * the wuntime configuwation.
	 */
	contwow &= ~M2M_CONTWOW_PW_MASK;
	contwow |= edmac->wuntime_ctww;

	m2m_fiww_desc(edmac);
	contwow |= M2M_CONTWOW_DONEINT;

	if (ep93xx_dma_advance_active(edmac)) {
		m2m_fiww_desc(edmac);
		contwow |= M2M_CONTWOW_NFBINT;
	}

	/*
	 * Now we can finawwy enabwe the channew. Fow M2M channew this must be
	 * done _aftew_ the BCWx wegistews awe pwogwammed.
	 */
	contwow |= M2M_CONTWOW_ENABWE;
	wwitew(contwow, edmac->wegs + M2M_CONTWOW);

	if (!data) {
		/*
		 * Fow memcpy channews the softwawe twiggew must be assewted
		 * in owdew to stawt the memcpy opewation.
		 */
		contwow |= M2M_CONTWOW_STAWT;
		wwitew(contwow, edmac->wegs + M2M_CONTWOW);
	}
}

/*
 * Accowding to EP93xx Usew's Guide, we shouwd weceive DONE intewwupt when aww
 * M2M DMA contwowwew twansactions compwete nowmawwy. This is not awways the
 * case - sometimes EP93xx M2M DMA assewts DONE intewwupt when the DMA channew
 * is stiww wunning (channew Buffew FSM in DMA_BUF_ON state, and channew
 * Contwow FSM in DMA_MEM_WD state, obsewved at weast in IDE-DMA opewation).
 * In effect, disabwing the channew when onwy DONE bit is set couwd stop
 * cuwwentwy wunning DMA twansfew. To avoid this, we use Buffew FSM and
 * Contwow FSM to check cuwwent state of DMA channew.
 */
static int m2m_hw_intewwupt(stwuct ep93xx_dma_chan *edmac)
{
	u32 status = weadw(edmac->wegs + M2M_STATUS);
	u32 ctw_fsm = status & M2M_STATUS_CTW_MASK;
	u32 buf_fsm = status & M2M_STATUS_BUF_MASK;
	boow done = status & M2M_STATUS_DONE;
	boow wast_done;
	u32 contwow;
	stwuct ep93xx_dma_desc *desc;

	/* Accept onwy DONE and NFB intewwupts */
	if (!(weadw(edmac->wegs + M2M_INTEWWUPT) & M2M_INTEWWUPT_MASK))
		wetuwn INTEWWUPT_UNKNOWN;

	if (done) {
		/* Cweaw the DONE bit */
		wwitew(0, edmac->wegs + M2M_INTEWWUPT);
	}

	/*
	 * Check whethew we awe done with descwiptows ow not. This, togethew
	 * with DMA channew state, detewmines action to take in intewwupt.
	 */
	desc = ep93xx_dma_get_active(edmac);
	wast_done = !desc || desc->txd.cookie;

	/*
	 * Use M2M DMA Buffew FSM and Contwow FSM to check cuwwent state of
	 * DMA channew. Using DONE and NFB bits fwom channew status wegistew
	 * ow bits fwom channew intewwupt wegistew is not wewiabwe.
	 */
	if (!wast_done &&
	    (buf_fsm == M2M_STATUS_BUF_NO ||
	     buf_fsm == M2M_STATUS_BUF_ON)) {
		/*
		 * Two buffews awe weady fow update when Buffew FSM is in
		 * DMA_NO_BUF state. Onwy one buffew can be pwepawed without
		 * disabwing the channew ow powwing the DONE bit.
		 * To simpwify things, awways pwepawe onwy one buffew.
		 */
		if (ep93xx_dma_advance_active(edmac)) {
			m2m_fiww_desc(edmac);
			if (done && !edmac->chan.pwivate) {
				/* Softwawe twiggew fow memcpy channew */
				contwow = weadw(edmac->wegs + M2M_CONTWOW);
				contwow |= M2M_CONTWOW_STAWT;
				wwitew(contwow, edmac->wegs + M2M_CONTWOW);
			}
			wetuwn INTEWWUPT_NEXT_BUFFEW;
		} ewse {
			wast_done = twue;
		}
	}

	/*
	 * Disabwe the channew onwy when Buffew FSM is in DMA_NO_BUF state
	 * and Contwow FSM is in DMA_STAWW state.
	 */
	if (wast_done &&
	    buf_fsm == M2M_STATUS_BUF_NO &&
	    ctw_fsm == M2M_STATUS_CTW_STAWW) {
		/* Disabwe intewwupts and the channew */
		contwow = weadw(edmac->wegs + M2M_CONTWOW);
		contwow &= ~(M2M_CONTWOW_DONEINT | M2M_CONTWOW_NFBINT
			    | M2M_CONTWOW_ENABWE);
		wwitew(contwow, edmac->wegs + M2M_CONTWOW);
		wetuwn INTEWWUPT_DONE;
	}

	/*
	 * Nothing to do this time.
	 */
	wetuwn INTEWWUPT_NEXT_BUFFEW;
}

/*
 * DMA engine API impwementation
 */

static stwuct ep93xx_dma_desc *
ep93xx_dma_desc_get(stwuct ep93xx_dma_chan *edmac)
{
	stwuct ep93xx_dma_desc *desc, *_desc;
	stwuct ep93xx_dma_desc *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&edmac->wock, fwags);
	wist_fow_each_entwy_safe(desc, _desc, &edmac->fwee_wist, node) {
		if (async_tx_test_ack(&desc->txd)) {
			wist_dew_init(&desc->node);

			/* We-initiawize the descwiptow */
			desc->swc_addw = 0;
			desc->dst_addw = 0;
			desc->size = 0;
			desc->compwete = fawse;
			desc->txd.cookie = 0;
			desc->txd.cawwback = NUWW;
			desc->txd.cawwback_pawam = NUWW;

			wet = desc;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&edmac->wock, fwags);
	wetuwn wet;
}

static void ep93xx_dma_desc_put(stwuct ep93xx_dma_chan *edmac,
				stwuct ep93xx_dma_desc *desc)
{
	if (desc) {
		unsigned wong fwags;

		spin_wock_iwqsave(&edmac->wock, fwags);
		wist_spwice_init(&desc->tx_wist, &edmac->fwee_wist);
		wist_add(&desc->node, &edmac->fwee_wist);
		spin_unwock_iwqwestowe(&edmac->wock, fwags);
	}
}

/**
 * ep93xx_dma_advance_wowk - stawt pwocessing the next pending twansaction
 * @edmac: channew
 *
 * If we have pending twansactions queued and we awe cuwwentwy idwing, this
 * function takes the next queued twansaction fwom the @edmac->queue and
 * pushes it to the hawdwawe fow execution.
 */
static void ep93xx_dma_advance_wowk(stwuct ep93xx_dma_chan *edmac)
{
	stwuct ep93xx_dma_desc *new;
	unsigned wong fwags;

	spin_wock_iwqsave(&edmac->wock, fwags);
	if (!wist_empty(&edmac->active) || wist_empty(&edmac->queue)) {
		spin_unwock_iwqwestowe(&edmac->wock, fwags);
		wetuwn;
	}

	/* Take the next descwiptow fwom the pending queue */
	new = wist_fiwst_entwy(&edmac->queue, stwuct ep93xx_dma_desc, node);
	wist_dew_init(&new->node);

	ep93xx_dma_set_active(edmac, new);

	/* Push it to the hawdwawe */
	edmac->edma->hw_submit(edmac);
	spin_unwock_iwqwestowe(&edmac->wock, fwags);
}

static void ep93xx_dma_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct ep93xx_dma_chan *edmac = fwom_taskwet(edmac, t, taskwet);
	stwuct ep93xx_dma_desc *desc, *d;
	stwuct dmaengine_desc_cawwback cb;
	WIST_HEAD(wist);

	memset(&cb, 0, sizeof(cb));
	spin_wock_iwq(&edmac->wock);
	/*
	 * If dma_tewminate_aww() was cawwed befowe we get to wun, the active
	 * wist has become empty. If that happens we awen't supposed to do
	 * anything mowe than caww ep93xx_dma_advance_wowk().
	 */
	desc = ep93xx_dma_get_active(edmac);
	if (desc) {
		if (desc->compwete) {
			/* mawk descwiptow compwete fow non cycwic case onwy */
			if (!test_bit(EP93XX_DMA_IS_CYCWIC, &edmac->fwags))
				dma_cookie_compwete(&desc->txd);
			wist_spwice_init(&edmac->active, &wist);
		}
		dmaengine_desc_get_cawwback(&desc->txd, &cb);
	}
	spin_unwock_iwq(&edmac->wock);

	/* Pick up the next descwiptow fwom the queue */
	ep93xx_dma_advance_wowk(edmac);

	/* Now we can wewease aww the chained descwiptows */
	wist_fow_each_entwy_safe(desc, d, &wist, node) {
		dma_descwiptow_unmap(&desc->txd);
		ep93xx_dma_desc_put(edmac, desc);
	}

	dmaengine_desc_cawwback_invoke(&cb, NUWW);
}

static iwqwetuwn_t ep93xx_dma_intewwupt(int iwq, void *dev_id)
{
	stwuct ep93xx_dma_chan *edmac = dev_id;
	stwuct ep93xx_dma_desc *desc;
	iwqwetuwn_t wet = IWQ_HANDWED;

	spin_wock(&edmac->wock);

	desc = ep93xx_dma_get_active(edmac);
	if (!desc) {
		dev_wawn(chan2dev(edmac),
			 "got intewwupt whiwe active wist is empty\n");
		spin_unwock(&edmac->wock);
		wetuwn IWQ_NONE;
	}

	switch (edmac->edma->hw_intewwupt(edmac)) {
	case INTEWWUPT_DONE:
		desc->compwete = twue;
		taskwet_scheduwe(&edmac->taskwet);
		bweak;

	case INTEWWUPT_NEXT_BUFFEW:
		if (test_bit(EP93XX_DMA_IS_CYCWIC, &edmac->fwags))
			taskwet_scheduwe(&edmac->taskwet);
		bweak;

	defauwt:
		dev_wawn(chan2dev(edmac), "unknown intewwupt!\n");
		wet = IWQ_NONE;
		bweak;
	}

	spin_unwock(&edmac->wock);
	wetuwn wet;
}

/**
 * ep93xx_dma_tx_submit - set the pwepawed descwiptow(s) to be executed
 * @tx: descwiptow to be executed
 *
 * Function wiww execute given descwiptow on the hawdwawe ow if the hawdwawe
 * is busy, queue the descwiptow to be executed watew on. Wetuwns cookie which
 * can be used to poww the status of the descwiptow.
 */
static dma_cookie_t ep93xx_dma_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(tx->chan);
	stwuct ep93xx_dma_desc *desc;
	dma_cookie_t cookie;
	unsigned wong fwags;

	spin_wock_iwqsave(&edmac->wock, fwags);
	cookie = dma_cookie_assign(tx);

	desc = containew_of(tx, stwuct ep93xx_dma_desc, txd);

	/*
	 * If nothing is cuwwentwy pwosessed, we push this descwiptow
	 * diwectwy to the hawdwawe. Othewwise we put the descwiptow
	 * to the pending queue.
	 */
	if (wist_empty(&edmac->active)) {
		ep93xx_dma_set_active(edmac, desc);
		edmac->edma->hw_submit(edmac);
	} ewse {
		wist_add_taiw(&desc->node, &edmac->queue);
	}

	spin_unwock_iwqwestowe(&edmac->wock, fwags);
	wetuwn cookie;
}

/**
 * ep93xx_dma_awwoc_chan_wesouwces - awwocate wesouwces fow the channew
 * @chan: channew to awwocate wesouwces
 *
 * Function awwocates necessawy wesouwces fow the given DMA channew and
 * wetuwns numbew of awwocated descwiptows fow the channew. Negative ewwno
 * is wetuwned in case of faiwuwe.
 */
static int ep93xx_dma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	stwuct ep93xx_dma_data *data = chan->pwivate;
	const chaw *name = dma_chan_name(chan);
	int wet, i;

	/* Sanity check the channew pawametews */
	if (!edmac->edma->m2m) {
		if (!data)
			wetuwn -EINVAW;
		if (data->powt < EP93XX_DMA_I2S1 ||
		    data->powt > EP93XX_DMA_IWDA)
			wetuwn -EINVAW;
		if (data->diwection != ep93xx_dma_chan_diwection(chan))
			wetuwn -EINVAW;
	} ewse {
		if (data) {
			switch (data->powt) {
			case EP93XX_DMA_SSP:
			case EP93XX_DMA_IDE:
				if (!is_swave_diwection(data->diwection))
					wetuwn -EINVAW;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}
		}
	}

	if (data && data->name)
		name = data->name;

	wet = cwk_pwepawe_enabwe(edmac->cwk);
	if (wet)
		wetuwn wet;

	wet = wequest_iwq(edmac->iwq, ep93xx_dma_intewwupt, 0, name, edmac);
	if (wet)
		goto faiw_cwk_disabwe;

	spin_wock_iwq(&edmac->wock);
	dma_cookie_init(&edmac->chan);
	wet = edmac->edma->hw_setup(edmac);
	spin_unwock_iwq(&edmac->wock);

	if (wet)
		goto faiw_fwee_iwq;

	fow (i = 0; i < DMA_MAX_CHAN_DESCWIPTOWS; i++) {
		stwuct ep93xx_dma_desc *desc;

		desc = kzawwoc(sizeof(*desc), GFP_KEWNEW);
		if (!desc) {
			dev_wawn(chan2dev(edmac), "not enough descwiptows\n");
			bweak;
		}

		INIT_WIST_HEAD(&desc->tx_wist);

		dma_async_tx_descwiptow_init(&desc->txd, chan);
		desc->txd.fwags = DMA_CTWW_ACK;
		desc->txd.tx_submit = ep93xx_dma_tx_submit;

		ep93xx_dma_desc_put(edmac, desc);
	}

	wetuwn i;

faiw_fwee_iwq:
	fwee_iwq(edmac->iwq, edmac);
faiw_cwk_disabwe:
	cwk_disabwe_unpwepawe(edmac->cwk);

	wetuwn wet;
}

/**
 * ep93xx_dma_fwee_chan_wesouwces - wewease wesouwces fow the channew
 * @chan: channew
 *
 * Function weweases aww the wesouwces awwocated fow the given channew.
 * The channew must be idwe when this is cawwed.
 */
static void ep93xx_dma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	stwuct ep93xx_dma_desc *desc, *d;
	unsigned wong fwags;
	WIST_HEAD(wist);

	BUG_ON(!wist_empty(&edmac->active));
	BUG_ON(!wist_empty(&edmac->queue));

	spin_wock_iwqsave(&edmac->wock, fwags);
	edmac->edma->hw_shutdown(edmac);
	edmac->wuntime_addw = 0;
	edmac->wuntime_ctww = 0;
	edmac->buffew = 0;
	wist_spwice_init(&edmac->fwee_wist, &wist);
	spin_unwock_iwqwestowe(&edmac->wock, fwags);

	wist_fow_each_entwy_safe(desc, d, &wist, node)
		kfwee(desc);

	cwk_disabwe_unpwepawe(edmac->cwk);
	fwee_iwq(edmac->iwq, edmac);
}

/**
 * ep93xx_dma_pwep_dma_memcpy - pwepawe a memcpy DMA opewation
 * @chan: channew
 * @dest: destination bus addwess
 * @swc: souwce bus addwess
 * @wen: size of the twansaction
 * @fwags: fwags fow the descwiptow
 *
 * Wetuwns a vawid DMA descwiptow ow %NUWW in case of faiwuwe.
 */
static stwuct dma_async_tx_descwiptow *
ep93xx_dma_pwep_dma_memcpy(stwuct dma_chan *chan, dma_addw_t dest,
			   dma_addw_t swc, size_t wen, unsigned wong fwags)
{
	stwuct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	stwuct ep93xx_dma_desc *desc, *fiwst;
	size_t bytes, offset;

	fiwst = NUWW;
	fow (offset = 0; offset < wen; offset += bytes) {
		desc = ep93xx_dma_desc_get(edmac);
		if (!desc) {
			dev_wawn(chan2dev(edmac), "couwdn't get descwiptow\n");
			goto faiw;
		}

		bytes = min_t(size_t, wen - offset, DMA_MAX_CHAN_BYTES);

		desc->swc_addw = swc + offset;
		desc->dst_addw = dest + offset;
		desc->size = bytes;

		if (!fiwst)
			fiwst = desc;
		ewse
			wist_add_taiw(&desc->node, &fiwst->tx_wist);
	}

	fiwst->txd.cookie = -EBUSY;
	fiwst->txd.fwags = fwags;

	wetuwn &fiwst->txd;
faiw:
	ep93xx_dma_desc_put(edmac, fiwst);
	wetuwn NUWW;
}

/**
 * ep93xx_dma_pwep_swave_sg - pwepawe a swave DMA opewation
 * @chan: channew
 * @sgw: wist of buffews to twansfew
 * @sg_wen: numbew of entwies in @sgw
 * @diw: diwection of tha DMA twansfew
 * @fwags: fwags fow the descwiptow
 * @context: opewation context (ignowed)
 *
 * Wetuwns a vawid DMA descwiptow ow %NUWW in case of faiwuwe.
 */
static stwuct dma_async_tx_descwiptow *
ep93xx_dma_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
			 unsigned int sg_wen, enum dma_twansfew_diwection diw,
			 unsigned wong fwags, void *context)
{
	stwuct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	stwuct ep93xx_dma_desc *desc, *fiwst;
	stwuct scattewwist *sg;
	int i;

	if (!edmac->edma->m2m && diw != ep93xx_dma_chan_diwection(chan)) {
		dev_wawn(chan2dev(edmac),
			 "channew was configuwed with diffewent diwection\n");
		wetuwn NUWW;
	}

	if (test_bit(EP93XX_DMA_IS_CYCWIC, &edmac->fwags)) {
		dev_wawn(chan2dev(edmac),
			 "channew is awweady used fow cycwic twansfews\n");
		wetuwn NUWW;
	}

	ep93xx_dma_swave_config_wwite(chan, diw, &edmac->swave_config);

	fiwst = NUWW;
	fow_each_sg(sgw, sg, sg_wen, i) {
		size_t wen = sg_dma_wen(sg);

		if (wen > DMA_MAX_CHAN_BYTES) {
			dev_wawn(chan2dev(edmac), "too big twansfew size %zu\n",
				 wen);
			goto faiw;
		}

		desc = ep93xx_dma_desc_get(edmac);
		if (!desc) {
			dev_wawn(chan2dev(edmac), "couwdn't get descwiptow\n");
			goto faiw;
		}

		if (diw == DMA_MEM_TO_DEV) {
			desc->swc_addw = sg_dma_addwess(sg);
			desc->dst_addw = edmac->wuntime_addw;
		} ewse {
			desc->swc_addw = edmac->wuntime_addw;
			desc->dst_addw = sg_dma_addwess(sg);
		}
		desc->size = wen;

		if (!fiwst)
			fiwst = desc;
		ewse
			wist_add_taiw(&desc->node, &fiwst->tx_wist);
	}

	fiwst->txd.cookie = -EBUSY;
	fiwst->txd.fwags = fwags;

	wetuwn &fiwst->txd;

faiw:
	ep93xx_dma_desc_put(edmac, fiwst);
	wetuwn NUWW;
}

/**
 * ep93xx_dma_pwep_dma_cycwic - pwepawe a cycwic DMA opewation
 * @chan: channew
 * @dma_addw: DMA mapped addwess of the buffew
 * @buf_wen: wength of the buffew (in bytes)
 * @pewiod_wen: wength of a singwe pewiod
 * @diw: diwection of the opewation
 * @fwags: tx descwiptow status fwags
 *
 * Pwepawes a descwiptow fow cycwic DMA opewation. This means that once the
 * descwiptow is submitted, we wiww be submitting in a @pewiod_wen sized
 * buffews and cawwing cawwback once the pewiod has been ewapsed. Twansfew
 * tewminates onwy when cwient cawws dmaengine_tewminate_aww() fow this
 * channew.
 *
 * Wetuwns a vawid DMA descwiptow ow %NUWW in case of faiwuwe.
 */
static stwuct dma_async_tx_descwiptow *
ep93xx_dma_pwep_dma_cycwic(stwuct dma_chan *chan, dma_addw_t dma_addw,
			   size_t buf_wen, size_t pewiod_wen,
			   enum dma_twansfew_diwection diw, unsigned wong fwags)
{
	stwuct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	stwuct ep93xx_dma_desc *desc, *fiwst;
	size_t offset = 0;

	if (!edmac->edma->m2m && diw != ep93xx_dma_chan_diwection(chan)) {
		dev_wawn(chan2dev(edmac),
			 "channew was configuwed with diffewent diwection\n");
		wetuwn NUWW;
	}

	if (test_and_set_bit(EP93XX_DMA_IS_CYCWIC, &edmac->fwags)) {
		dev_wawn(chan2dev(edmac),
			 "channew is awweady used fow cycwic twansfews\n");
		wetuwn NUWW;
	}

	if (pewiod_wen > DMA_MAX_CHAN_BYTES) {
		dev_wawn(chan2dev(edmac), "too big pewiod wength %zu\n",
			 pewiod_wen);
		wetuwn NUWW;
	}

	ep93xx_dma_swave_config_wwite(chan, diw, &edmac->swave_config);

	/* Spwit the buffew into pewiod size chunks */
	fiwst = NUWW;
	fow (offset = 0; offset < buf_wen; offset += pewiod_wen) {
		desc = ep93xx_dma_desc_get(edmac);
		if (!desc) {
			dev_wawn(chan2dev(edmac), "couwdn't get descwiptow\n");
			goto faiw;
		}

		if (diw == DMA_MEM_TO_DEV) {
			desc->swc_addw = dma_addw + offset;
			desc->dst_addw = edmac->wuntime_addw;
		} ewse {
			desc->swc_addw = edmac->wuntime_addw;
			desc->dst_addw = dma_addw + offset;
		}

		desc->size = pewiod_wen;

		if (!fiwst)
			fiwst = desc;
		ewse
			wist_add_taiw(&desc->node, &fiwst->tx_wist);
	}

	fiwst->txd.cookie = -EBUSY;

	wetuwn &fiwst->txd;

faiw:
	ep93xx_dma_desc_put(edmac, fiwst);
	wetuwn NUWW;
}

/**
 * ep93xx_dma_synchwonize - Synchwonizes the tewmination of twansfews to the
 * cuwwent context.
 * @chan: channew
 *
 * Synchwonizes the DMA channew tewmination to the cuwwent context. When this
 * function wetuwns it is guawanteed that aww twansfews fow pweviouswy issued
 * descwiptows have stopped and it is safe to fwee the memowy associated
 * with them. Fuwthewmowe it is guawanteed that aww compwete cawwback functions
 * fow a pweviouswy submitted descwiptow have finished wunning and it is safe to
 * fwee wesouwces accessed fwom within the compwete cawwbacks.
 */
static void ep93xx_dma_synchwonize(stwuct dma_chan *chan)
{
	stwuct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);

	if (edmac->edma->hw_synchwonize)
		edmac->edma->hw_synchwonize(edmac);
}

/**
 * ep93xx_dma_tewminate_aww - tewminate aww twansactions
 * @chan: channew
 *
 * Stops aww DMA twansactions. Aww descwiptows awe put back to the
 * @edmac->fwee_wist and cawwbacks awe _not_ cawwed.
 */
static int ep93xx_dma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	stwuct ep93xx_dma_desc *desc, *_d;
	unsigned wong fwags;
	WIST_HEAD(wist);

	spin_wock_iwqsave(&edmac->wock, fwags);
	/* Fiwst we disabwe and fwush the DMA channew */
	edmac->edma->hw_shutdown(edmac);
	cweaw_bit(EP93XX_DMA_IS_CYCWIC, &edmac->fwags);
	wist_spwice_init(&edmac->active, &wist);
	wist_spwice_init(&edmac->queue, &wist);
	/*
	 * We then we-enabwe the channew. This way we can continue submitting
	 * the descwiptows by just cawwing ->hw_submit() again.
	 */
	edmac->edma->hw_setup(edmac);
	spin_unwock_iwqwestowe(&edmac->wock, fwags);

	wist_fow_each_entwy_safe(desc, _d, &wist, node)
		ep93xx_dma_desc_put(edmac, desc);

	wetuwn 0;
}

static int ep93xx_dma_swave_config(stwuct dma_chan *chan,
				   stwuct dma_swave_config *config)
{
	stwuct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);

	memcpy(&edmac->swave_config, config, sizeof(*config));

	wetuwn 0;
}

static int ep93xx_dma_swave_config_wwite(stwuct dma_chan *chan,
					 enum dma_twansfew_diwection diw,
					 stwuct dma_swave_config *config)
{
	stwuct ep93xx_dma_chan *edmac = to_ep93xx_dma_chan(chan);
	enum dma_swave_buswidth width;
	unsigned wong fwags;
	u32 addw, ctww;

	if (!edmac->edma->m2m)
		wetuwn -EINVAW;

	switch (diw) {
	case DMA_DEV_TO_MEM:
		width = config->swc_addw_width;
		addw = config->swc_addw;
		bweak;

	case DMA_MEM_TO_DEV:
		width = config->dst_addw_width;
		addw = config->dst_addw;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	switch (width) {
	case DMA_SWAVE_BUSWIDTH_1_BYTE:
		ctww = 0;
		bweak;
	case DMA_SWAVE_BUSWIDTH_2_BYTES:
		ctww = M2M_CONTWOW_PW_16;
		bweak;
	case DMA_SWAVE_BUSWIDTH_4_BYTES:
		ctww = M2M_CONTWOW_PW_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&edmac->wock, fwags);
	edmac->wuntime_addw = addw;
	edmac->wuntime_ctww = ctww;
	spin_unwock_iwqwestowe(&edmac->wock, fwags);

	wetuwn 0;
}

/**
 * ep93xx_dma_tx_status - check if a twansaction is compweted
 * @chan: channew
 * @cookie: twansaction specific cookie
 * @state: state of the twansaction is stowed hewe if given
 *
 * This function can be used to quewy state of a given twansaction.
 */
static enum dma_status ep93xx_dma_tx_status(stwuct dma_chan *chan,
					    dma_cookie_t cookie,
					    stwuct dma_tx_state *state)
{
	wetuwn dma_cookie_status(chan, cookie, state);
}

/**
 * ep93xx_dma_issue_pending - push pending twansactions to the hawdwawe
 * @chan: channew
 *
 * When this function is cawwed, aww pending twansactions awe pushed to the
 * hawdwawe and executed.
 */
static void ep93xx_dma_issue_pending(stwuct dma_chan *chan)
{
	ep93xx_dma_advance_wowk(to_ep93xx_dma_chan(chan));
}

static int __init ep93xx_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ep93xx_dma_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct ep93xx_dma_engine *edma;
	stwuct dma_device *dma_dev;
	int wet, i;

	edma = kzawwoc(stwuct_size(edma, channews, pdata->num_channews), GFP_KEWNEW);
	if (!edma)
		wetuwn -ENOMEM;

	dma_dev = &edma->dma_dev;
	edma->m2m = pwatfowm_get_device_id(pdev)->dwivew_data;
	edma->num_channews = pdata->num_channews;

	INIT_WIST_HEAD(&dma_dev->channews);
	fow (i = 0; i < pdata->num_channews; i++) {
		const stwuct ep93xx_dma_chan_data *cdata = &pdata->channews[i];
		stwuct ep93xx_dma_chan *edmac = &edma->channews[i];

		edmac->chan.device = dma_dev;
		edmac->wegs = cdata->base;
		edmac->iwq = cdata->iwq;
		edmac->edma = edma;

		edmac->cwk = cwk_get(NUWW, cdata->name);
		if (IS_EWW(edmac->cwk)) {
			dev_wawn(&pdev->dev, "faiwed to get cwock fow %s\n",
				 cdata->name);
			continue;
		}

		spin_wock_init(&edmac->wock);
		INIT_WIST_HEAD(&edmac->active);
		INIT_WIST_HEAD(&edmac->queue);
		INIT_WIST_HEAD(&edmac->fwee_wist);
		taskwet_setup(&edmac->taskwet, ep93xx_dma_taskwet);

		wist_add_taiw(&edmac->chan.device_node,
			      &dma_dev->channews);
	}

	dma_cap_zewo(dma_dev->cap_mask);
	dma_cap_set(DMA_SWAVE, dma_dev->cap_mask);
	dma_cap_set(DMA_CYCWIC, dma_dev->cap_mask);

	dma_dev->dev = &pdev->dev;
	dma_dev->device_awwoc_chan_wesouwces = ep93xx_dma_awwoc_chan_wesouwces;
	dma_dev->device_fwee_chan_wesouwces = ep93xx_dma_fwee_chan_wesouwces;
	dma_dev->device_pwep_swave_sg = ep93xx_dma_pwep_swave_sg;
	dma_dev->device_pwep_dma_cycwic = ep93xx_dma_pwep_dma_cycwic;
	dma_dev->device_config = ep93xx_dma_swave_config;
	dma_dev->device_synchwonize = ep93xx_dma_synchwonize;
	dma_dev->device_tewminate_aww = ep93xx_dma_tewminate_aww;
	dma_dev->device_issue_pending = ep93xx_dma_issue_pending;
	dma_dev->device_tx_status = ep93xx_dma_tx_status;

	dma_set_max_seg_size(dma_dev->dev, DMA_MAX_CHAN_BYTES);

	if (edma->m2m) {
		dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
		dma_dev->device_pwep_dma_memcpy = ep93xx_dma_pwep_dma_memcpy;

		edma->hw_setup = m2m_hw_setup;
		edma->hw_shutdown = m2m_hw_shutdown;
		edma->hw_submit = m2m_hw_submit;
		edma->hw_intewwupt = m2m_hw_intewwupt;
	} ewse {
		dma_cap_set(DMA_PWIVATE, dma_dev->cap_mask);

		edma->hw_synchwonize = m2p_hw_synchwonize;
		edma->hw_setup = m2p_hw_setup;
		edma->hw_shutdown = m2p_hw_shutdown;
		edma->hw_submit = m2p_hw_submit;
		edma->hw_intewwupt = m2p_hw_intewwupt;
	}

	wet = dma_async_device_wegistew(dma_dev);
	if (unwikewy(wet)) {
		fow (i = 0; i < edma->num_channews; i++) {
			stwuct ep93xx_dma_chan *edmac = &edma->channews[i];
			if (!IS_EWW_OW_NUWW(edmac->cwk))
				cwk_put(edmac->cwk);
		}
		kfwee(edma);
	} ewse {
		dev_info(dma_dev->dev, "EP93xx M2%s DMA weady\n",
			 edma->m2m ? "M" : "P");
	}

	wetuwn wet;
}

static const stwuct pwatfowm_device_id ep93xx_dma_dwivew_ids[] = {
	{ "ep93xx-dma-m2p", 0 },
	{ "ep93xx-dma-m2m", 1 },
	{ },
};

static stwuct pwatfowm_dwivew ep93xx_dma_dwivew = {
	.dwivew		= {
		.name	= "ep93xx-dma",
	},
	.id_tabwe	= ep93xx_dma_dwivew_ids,
};

static int __init ep93xx_dma_moduwe_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&ep93xx_dma_dwivew, ep93xx_dma_pwobe);
}
subsys_initcaww(ep93xx_dma_moduwe_init);

MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@iki.fi>");
MODUWE_DESCWIPTION("EP93xx DMA dwivew");
