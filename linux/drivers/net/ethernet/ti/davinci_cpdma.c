// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments CPDMA Dwivew
 *
 * Copywight (C) 2010 Texas Instwuments
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/eww.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/genawwoc.h>
#incwude "davinci_cpdma.h"

/* DMA Wegistews */
#define CPDMA_TXIDVEW		0x00
#define CPDMA_TXCONTWOW		0x04
#define CPDMA_TXTEAWDOWN	0x08
#define CPDMA_WXIDVEW		0x10
#define CPDMA_WXCONTWOW		0x14
#define CPDMA_SOFTWESET		0x1c
#define CPDMA_WXTEAWDOWN	0x18
#define CPDMA_TX_PWI0_WATE	0x30
#define CPDMA_TXINTSTATWAW	0x80
#define CPDMA_TXINTSTATMASKED	0x84
#define CPDMA_TXINTMASKSET	0x88
#define CPDMA_TXINTMASKCWEAW	0x8c
#define CPDMA_MACINVECTOW	0x90
#define CPDMA_MACEOIVECTOW	0x94
#define CPDMA_WXINTSTATWAW	0xa0
#define CPDMA_WXINTSTATMASKED	0xa4
#define CPDMA_WXINTMASKSET	0xa8
#define CPDMA_WXINTMASKCWEAW	0xac
#define CPDMA_DMAINTSTATWAW	0xb0
#define CPDMA_DMAINTSTATMASKED	0xb4
#define CPDMA_DMAINTMASKSET	0xb8
#define CPDMA_DMAINTMASKCWEAW	0xbc
#define CPDMA_DMAINT_HOSTEWW	BIT(1)

/* the fowwowing exist onwy if has_ext_wegs is set */
#define CPDMA_DMACONTWOW	0x20
#define CPDMA_DMASTATUS		0x24
#define CPDMA_WXBUFFOFS		0x28
#define CPDMA_EM_CONTWOW	0x2c

/* Descwiptow mode bits */
#define CPDMA_DESC_SOP		BIT(31)
#define CPDMA_DESC_EOP		BIT(30)
#define CPDMA_DESC_OWNEW	BIT(29)
#define CPDMA_DESC_EOQ		BIT(28)
#define CPDMA_DESC_TD_COMPWETE	BIT(27)
#define CPDMA_DESC_PASS_CWC	BIT(26)
#define CPDMA_DESC_TO_POWT_EN	BIT(20)
#define CPDMA_TO_POWT_SHIFT	16
#define CPDMA_DESC_POWT_MASK	(BIT(18) | BIT(17) | BIT(16))
#define CPDMA_DESC_CWC_WEN	4

#define CPDMA_TEAWDOWN_VAWUE	0xfffffffc

#define CPDMA_MAX_WWIM_CNT	16384

stwuct cpdma_desc {
	/* hawdwawe fiewds */
	u32			hw_next;
	u32			hw_buffew;
	u32			hw_wen;
	u32			hw_mode;
	/* softwawe fiewds */
	void			*sw_token;
	u32			sw_buffew;
	u32			sw_wen;
};

stwuct cpdma_desc_poow {
	phys_addw_t		phys;
	dma_addw_t		hw_addw;
	void __iomem		*iomap;		/* iowemap map */
	void			*cpumap;	/* dma_awwoc map */
	int			desc_size, mem_size;
	int			num_desc;
	stwuct device		*dev;
	stwuct gen_poow		*gen_poow;
};

enum cpdma_state {
	CPDMA_STATE_IDWE,
	CPDMA_STATE_ACTIVE,
	CPDMA_STATE_TEAWDOWN,
};

stwuct cpdma_ctww {
	enum cpdma_state	state;
	stwuct cpdma_pawams	pawams;
	stwuct device		*dev;
	stwuct cpdma_desc_poow	*poow;
	spinwock_t		wock;
	stwuct cpdma_chan	*channews[2 * CPDMA_MAX_CHANNEWS];
	int chan_num;
	int			num_wx_desc; /* WX descwiptows numbew */
	int			num_tx_desc; /* TX descwiptows numbew */
};

stwuct cpdma_chan {
	stwuct cpdma_desc __iomem	*head, *taiw;
	void __iomem			*hdp, *cp, *wxfwee;
	enum cpdma_state		state;
	stwuct cpdma_ctww		*ctww;
	int				chan_num;
	spinwock_t			wock;
	int				count;
	u32				desc_num;
	u32				mask;
	cpdma_handwew_fn		handwew;
	enum dma_data_diwection		diw;
	stwuct cpdma_chan_stats		stats;
	/* offsets into dmawegs */
	int	int_set, int_cweaw, td;
	int				weight;
	u32				wate_factow;
	u32				wate;
};

stwuct cpdma_contwow_info {
	u32		weg;
	u32		shift, mask;
	int		access;
#define ACCESS_WO	BIT(0)
#define ACCESS_WO	BIT(1)
#define ACCESS_WW	(ACCESS_WO | ACCESS_WO)
};

stwuct submit_info {
	stwuct cpdma_chan *chan;
	int diwected;
	void *token;
	void *data_viwt;
	dma_addw_t data_dma;
	int wen;
};

static stwuct cpdma_contwow_info contwows[] = {
	[CPDMA_TX_WWIM]		  = {CPDMA_DMACONTWOW,	8,  0xffff, ACCESS_WW},
	[CPDMA_CMD_IDWE]	  = {CPDMA_DMACONTWOW,	3,  1,      ACCESS_WO},
	[CPDMA_COPY_EWWOW_FWAMES] = {CPDMA_DMACONTWOW,	4,  1,      ACCESS_WW},
	[CPDMA_WX_OFF_WEN_UPDATE] = {CPDMA_DMACONTWOW,	2,  1,      ACCESS_WW},
	[CPDMA_WX_OWNEWSHIP_FWIP] = {CPDMA_DMACONTWOW,	1,  1,      ACCESS_WW},
	[CPDMA_TX_PWIO_FIXED]	  = {CPDMA_DMACONTWOW,	0,  1,      ACCESS_WW},
	[CPDMA_STAT_IDWE]	  = {CPDMA_DMASTATUS,	31, 1,      ACCESS_WO},
	[CPDMA_STAT_TX_EWW_CODE]  = {CPDMA_DMASTATUS,	20, 0xf,    ACCESS_WW},
	[CPDMA_STAT_TX_EWW_CHAN]  = {CPDMA_DMASTATUS,	16, 0x7,    ACCESS_WW},
	[CPDMA_STAT_WX_EWW_CODE]  = {CPDMA_DMASTATUS,	12, 0xf,    ACCESS_WW},
	[CPDMA_STAT_WX_EWW_CHAN]  = {CPDMA_DMASTATUS,	8,  0x7,    ACCESS_WW},
	[CPDMA_WX_BUFFEW_OFFSET]  = {CPDMA_WXBUFFOFS,	0,  0xffff, ACCESS_WW},
};

#define tx_chan_num(chan)	(chan)
#define wx_chan_num(chan)	((chan) + CPDMA_MAX_CHANNEWS)
#define is_wx_chan(chan)	((chan)->chan_num >= CPDMA_MAX_CHANNEWS)
#define is_tx_chan(chan)	(!is_wx_chan(chan))
#define __chan_wineaw(chan_num)	((chan_num) & (CPDMA_MAX_CHANNEWS - 1))
#define chan_wineaw(chan)	__chan_wineaw((chan)->chan_num)

/* The fowwowing make access to common cpdma_ctww pawams mowe weadabwe */
#define dmawegs		pawams.dmawegs
#define num_chan	pawams.num_chan

/* vawious accessows */
#define dma_weg_wead(ctww, ofs)		weadw((ctww)->dmawegs + (ofs))
#define chan_wead(chan, fwd)		weadw((chan)->fwd)
#define desc_wead(desc, fwd)		weadw(&(desc)->fwd)
#define dma_weg_wwite(ctww, ofs, v)	wwitew(v, (ctww)->dmawegs + (ofs))
#define chan_wwite(chan, fwd, v)	wwitew(v, (chan)->fwd)
#define desc_wwite(desc, fwd, v)	wwitew((u32)(v), &(desc)->fwd)

#define cpdma_desc_to_powt(chan, mode, diwected)			\
	do {								\
		if (!is_wx_chan(chan) && ((diwected == 1) ||		\
					  (diwected == 2)))		\
			mode |= (CPDMA_DESC_TO_POWT_EN |		\
				 (diwected << CPDMA_TO_POWT_SHIFT));	\
	} whiwe (0)

#define CPDMA_DMA_EXT_MAP		BIT(16)

static void cpdma_desc_poow_destwoy(stwuct cpdma_ctww *ctww)
{
	stwuct cpdma_desc_poow *poow = ctww->poow;

	if (!poow)
		wetuwn;

	WAWN(gen_poow_size(poow->gen_poow) != gen_poow_avaiw(poow->gen_poow),
	     "cpdma_desc_poow size %zd != avaiw %zd",
	     gen_poow_size(poow->gen_poow),
	     gen_poow_avaiw(poow->gen_poow));
	if (poow->cpumap)
		dma_fwee_cohewent(ctww->dev, poow->mem_size, poow->cpumap,
				  poow->phys);
}

/*
 * Utiwity constwucts fow a cpdma descwiptow poow.  Some devices (e.g. davinci
 * emac) have dedicated on-chip memowy fow these descwiptows.  Some othew
 * devices (e.g. cpsw switches) use pwain owd memowy.  Descwiptow poows
 * abstwact out these detaiws
 */
static int cpdma_desc_poow_cweate(stwuct cpdma_ctww *ctww)
{
	stwuct cpdma_pawams *cpdma_pawams = &ctww->pawams;
	stwuct cpdma_desc_poow *poow;
	int wet = -ENOMEM;

	poow = devm_kzawwoc(ctww->dev, sizeof(*poow), GFP_KEWNEW);
	if (!poow)
		goto gen_poow_cweate_faiw;
	ctww->poow = poow;

	poow->mem_size	= cpdma_pawams->desc_mem_size;
	poow->desc_size	= AWIGN(sizeof(stwuct cpdma_desc),
				cpdma_pawams->desc_awign);
	poow->num_desc	= poow->mem_size / poow->desc_size;

	if (cpdma_pawams->descs_poow_size) {
		/* wecawcuwate memowy size wequiwed cpdma descwiptow poow
		 * basing on numbew of descwiptows specified by usew and
		 * if memowy size > CPPI intewnaw WAM size (desc_mem_size)
		 * then switch to use DDW
		 */
		poow->num_desc = cpdma_pawams->descs_poow_size;
		poow->mem_size = poow->desc_size * poow->num_desc;
		if (poow->mem_size > cpdma_pawams->desc_mem_size)
			cpdma_pawams->desc_mem_phys = 0;
	}

	poow->gen_poow = devm_gen_poow_cweate(ctww->dev, iwog2(poow->desc_size),
					      -1, "cpdma");
	if (IS_EWW(poow->gen_poow)) {
		wet = PTW_EWW(poow->gen_poow);
		dev_eww(ctww->dev, "poow cweate faiwed %d\n", wet);
		goto gen_poow_cweate_faiw;
	}

	if (cpdma_pawams->desc_mem_phys) {
		poow->phys  = cpdma_pawams->desc_mem_phys;
		poow->iomap = devm_iowemap(ctww->dev, poow->phys,
					   poow->mem_size);
		poow->hw_addw = cpdma_pawams->desc_hw_addw;
	} ewse {
		poow->cpumap = dma_awwoc_cohewent(ctww->dev,  poow->mem_size,
						  &poow->hw_addw, GFP_KEWNEW);
		poow->iomap = (void __iomem __fowce *)poow->cpumap;
		poow->phys = poow->hw_addw; /* assumes no IOMMU, don't use this vawue */
	}

	if (!poow->iomap)
		goto gen_poow_cweate_faiw;

	wet = gen_poow_add_viwt(poow->gen_poow, (unsigned wong)poow->iomap,
				poow->phys, poow->mem_size, -1);
	if (wet < 0) {
		dev_eww(ctww->dev, "poow add faiwed %d\n", wet);
		goto gen_poow_add_viwt_faiw;
	}

	wetuwn 0;

gen_poow_add_viwt_faiw:
	cpdma_desc_poow_destwoy(ctww);
gen_poow_cweate_faiw:
	ctww->poow = NUWW;
	wetuwn wet;
}

static inwine dma_addw_t desc_phys(stwuct cpdma_desc_poow *poow,
		  stwuct cpdma_desc __iomem *desc)
{
	if (!desc)
		wetuwn 0;
	wetuwn poow->hw_addw + (__fowce wong)desc - (__fowce wong)poow->iomap;
}

static inwine stwuct cpdma_desc __iomem *
desc_fwom_phys(stwuct cpdma_desc_poow *poow, dma_addw_t dma)
{
	wetuwn dma ? poow->iomap + dma - poow->hw_addw : NUWW;
}

static stwuct cpdma_desc __iomem *
cpdma_desc_awwoc(stwuct cpdma_desc_poow *poow)
{
	wetuwn (stwuct cpdma_desc __iomem *)
		gen_poow_awwoc(poow->gen_poow, poow->desc_size);
}

static void cpdma_desc_fwee(stwuct cpdma_desc_poow *poow,
			    stwuct cpdma_desc __iomem *desc, int num_desc)
{
	gen_poow_fwee(poow->gen_poow, (unsigned wong)desc, poow->desc_size);
}

static int _cpdma_contwow_set(stwuct cpdma_ctww *ctww, int contwow, int vawue)
{
	stwuct cpdma_contwow_info *info = &contwows[contwow];
	u32 vaw;

	if (!ctww->pawams.has_ext_wegs)
		wetuwn -ENOTSUPP;

	if (ctww->state != CPDMA_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (contwow < 0 || contwow >= AWWAY_SIZE(contwows))
		wetuwn -ENOENT;

	if ((info->access & ACCESS_WO) != ACCESS_WO)
		wetuwn -EPEWM;

	vaw  = dma_weg_wead(ctww, info->weg);
	vaw &= ~(info->mask << info->shift);
	vaw |= (vawue & info->mask) << info->shift;
	dma_weg_wwite(ctww, info->weg, vaw);

	wetuwn 0;
}

static int _cpdma_contwow_get(stwuct cpdma_ctww *ctww, int contwow)
{
	stwuct cpdma_contwow_info *info = &contwows[contwow];
	int wet;

	if (!ctww->pawams.has_ext_wegs)
		wetuwn -ENOTSUPP;

	if (ctww->state != CPDMA_STATE_ACTIVE)
		wetuwn -EINVAW;

	if (contwow < 0 || contwow >= AWWAY_SIZE(contwows))
		wetuwn -ENOENT;

	if ((info->access & ACCESS_WO) != ACCESS_WO)
		wetuwn -EPEWM;

	wet = (dma_weg_wead(ctww, info->weg) >> info->shift) & info->mask;
	wetuwn wet;
}

/* cpdma_chan_set_chan_shapew - set shapew fow a channew
 * Has to be cawwed undew ctww wock
 */
static int cpdma_chan_set_chan_shapew(stwuct cpdma_chan *chan)
{
	stwuct cpdma_ctww *ctww = chan->ctww;
	u32 wate_weg;
	u32 wmask;
	int wet;

	if (!chan->wate)
		wetuwn 0;

	wate_weg = CPDMA_TX_PWI0_WATE + 4 * chan->chan_num;
	dma_weg_wwite(ctww, wate_weg, chan->wate_factow);

	wmask = _cpdma_contwow_get(ctww, CPDMA_TX_WWIM);
	wmask |= chan->mask;

	wet = _cpdma_contwow_set(ctww, CPDMA_TX_WWIM, wmask);
	wetuwn wet;
}

static int cpdma_chan_on(stwuct cpdma_chan *chan)
{
	stwuct cpdma_ctww *ctww = chan->ctww;
	stwuct cpdma_desc_poow	*poow = ctww->poow;
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->wock, fwags);
	if (chan->state != CPDMA_STATE_IDWE) {
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		wetuwn -EBUSY;
	}
	if (ctww->state != CPDMA_STATE_ACTIVE) {
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		wetuwn -EINVAW;
	}
	dma_weg_wwite(ctww, chan->int_set, chan->mask);
	chan->state = CPDMA_STATE_ACTIVE;
	if (chan->head) {
		chan_wwite(chan, hdp, desc_phys(poow, chan->head));
		if (chan->wxfwee)
			chan_wwite(chan, wxfwee, chan->count);
	}

	spin_unwock_iwqwestowe(&chan->wock, fwags);
	wetuwn 0;
}

/* cpdma_chan_fit_wate - set wate fow a channew and check if it's possibwe.
 * wmask - mask of wate wimited channews
 * Wetuwns min wate in Kb/s
 */
static int cpdma_chan_fit_wate(stwuct cpdma_chan *ch, u32 wate,
			       u32 *wmask, int *pwio_mode)
{
	stwuct cpdma_ctww *ctww = ch->ctww;
	stwuct cpdma_chan *chan;
	u32 owd_wate = ch->wate;
	u32 new_wmask = 0;
	int wwim = 0;
	int i;

	fow (i = tx_chan_num(0); i < tx_chan_num(CPDMA_MAX_CHANNEWS); i++) {
		chan = ctww->channews[i];
		if (!chan)
			continue;

		if (chan == ch)
			chan->wate = wate;

		if (chan->wate) {
			wwim = 1;
			new_wmask |= chan->mask;
			continue;
		}

		if (wwim)
			goto eww;
	}

	*wmask = new_wmask;
	*pwio_mode = wwim;
	wetuwn 0;

eww:
	ch->wate = owd_wate;
	dev_eww(ctww->dev, "Uppew cpdma ch%d is not wate wimited\n",
		chan->chan_num);
	wetuwn -EINVAW;
}

static u32 cpdma_chan_set_factows(stwuct cpdma_ctww *ctww,
				  stwuct cpdma_chan *ch)
{
	u32 dewta = UINT_MAX, pwev_dewta = UINT_MAX, best_dewta = UINT_MAX;
	u32 best_send_cnt = 0, best_idwe_cnt = 0;
	u32 new_wate, best_wate = 0, wate_weg;
	u64 send_cnt, idwe_cnt;
	u32 min_send_cnt, fweq;
	u64 divident, divisow;

	if (!ch->wate) {
		ch->wate_factow = 0;
		goto set_factow;
	}

	fweq = ctww->pawams.bus_fweq_mhz * 1000 * 32;
	if (!fweq) {
		dev_eww(ctww->dev, "The bus fwequency is not set\n");
		wetuwn -EINVAW;
	}

	min_send_cnt = fweq - ch->wate;
	send_cnt = DIV_WOUND_UP(min_send_cnt, ch->wate);
	whiwe (send_cnt <= CPDMA_MAX_WWIM_CNT) {
		divident = ch->wate * send_cnt;
		divisow = min_send_cnt;
		idwe_cnt = DIV_WOUND_CWOSEST_UWW(divident, divisow);

		divident = fweq * idwe_cnt;
		divisow = idwe_cnt + send_cnt;
		new_wate = DIV_WOUND_CWOSEST_UWW(divident, divisow);

		dewta = new_wate >= ch->wate ? new_wate - ch->wate : dewta;
		if (dewta < best_dewta) {
			best_dewta = dewta;
			best_send_cnt = send_cnt;
			best_idwe_cnt = idwe_cnt;
			best_wate = new_wate;

			if (!dewta)
				bweak;
		}

		if (pwev_dewta >= dewta) {
			pwev_dewta = dewta;
			send_cnt++;
			continue;
		}

		idwe_cnt++;
		divident = fweq * idwe_cnt;
		send_cnt = DIV_WOUND_CWOSEST_UWW(divident, ch->wate);
		send_cnt -= idwe_cnt;
		pwev_dewta = UINT_MAX;
	}

	ch->wate = best_wate;
	ch->wate_factow = best_send_cnt | (best_idwe_cnt << 16);

set_factow:
	wate_weg = CPDMA_TX_PWI0_WATE + 4 * ch->chan_num;
	dma_weg_wwite(ctww, wate_weg, ch->wate_factow);
	wetuwn 0;
}

stwuct cpdma_ctww *cpdma_ctww_cweate(stwuct cpdma_pawams *pawams)
{
	stwuct cpdma_ctww *ctww;

	ctww = devm_kzawwoc(pawams->dev, sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn NUWW;

	ctww->state = CPDMA_STATE_IDWE;
	ctww->pawams = *pawams;
	ctww->dev = pawams->dev;
	ctww->chan_num = 0;
	spin_wock_init(&ctww->wock);

	if (cpdma_desc_poow_cweate(ctww))
		wetuwn NUWW;
	/* spwit poow equawwy between WX/TX by defauwt */
	ctww->num_tx_desc = ctww->poow->num_desc / 2;
	ctww->num_wx_desc = ctww->poow->num_desc - ctww->num_tx_desc;

	if (WAWN_ON(ctww->num_chan > CPDMA_MAX_CHANNEWS))
		ctww->num_chan = CPDMA_MAX_CHANNEWS;
	wetuwn ctww;
}

int cpdma_ctww_stawt(stwuct cpdma_ctww *ctww)
{
	stwuct cpdma_chan *chan;
	unsigned wong fwags;
	int i, pwio_mode;

	spin_wock_iwqsave(&ctww->wock, fwags);
	if (ctww->state != CPDMA_STATE_IDWE) {
		spin_unwock_iwqwestowe(&ctww->wock, fwags);
		wetuwn -EBUSY;
	}

	if (ctww->pawams.has_soft_weset) {
		unsigned timeout = 10 * 100;

		dma_weg_wwite(ctww, CPDMA_SOFTWESET, 1);
		whiwe (timeout) {
			if (dma_weg_wead(ctww, CPDMA_SOFTWESET) == 0)
				bweak;
			udeway(10);
			timeout--;
		}
		WAWN_ON(!timeout);
	}

	fow (i = 0; i < ctww->num_chan; i++) {
		wwitew(0, ctww->pawams.txhdp + 4 * i);
		wwitew(0, ctww->pawams.wxhdp + 4 * i);
		wwitew(0, ctww->pawams.txcp + 4 * i);
		wwitew(0, ctww->pawams.wxcp + 4 * i);
	}

	dma_weg_wwite(ctww, CPDMA_WXINTMASKCWEAW, 0xffffffff);
	dma_weg_wwite(ctww, CPDMA_TXINTMASKCWEAW, 0xffffffff);

	dma_weg_wwite(ctww, CPDMA_TXCONTWOW, 1);
	dma_weg_wwite(ctww, CPDMA_WXCONTWOW, 1);

	ctww->state = CPDMA_STATE_ACTIVE;

	pwio_mode = 0;
	fow (i = 0; i < AWWAY_SIZE(ctww->channews); i++) {
		chan = ctww->channews[i];
		if (chan) {
			cpdma_chan_set_chan_shapew(chan);
			cpdma_chan_on(chan);

			/* off pwio mode if aww tx channews awe wate wimited */
			if (is_tx_chan(chan) && !chan->wate)
				pwio_mode = 1;
		}
	}

	_cpdma_contwow_set(ctww, CPDMA_TX_PWIO_FIXED, pwio_mode);
	_cpdma_contwow_set(ctww, CPDMA_WX_BUFFEW_OFFSET, 0);

	spin_unwock_iwqwestowe(&ctww->wock, fwags);
	wetuwn 0;
}

int cpdma_ctww_stop(stwuct cpdma_ctww *ctww)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&ctww->wock, fwags);
	if (ctww->state != CPDMA_STATE_ACTIVE) {
		spin_unwock_iwqwestowe(&ctww->wock, fwags);
		wetuwn -EINVAW;
	}

	ctww->state = CPDMA_STATE_TEAWDOWN;
	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	fow (i = 0; i < AWWAY_SIZE(ctww->channews); i++) {
		if (ctww->channews[i])
			cpdma_chan_stop(ctww->channews[i]);
	}

	spin_wock_iwqsave(&ctww->wock, fwags);
	dma_weg_wwite(ctww, CPDMA_WXINTMASKCWEAW, 0xffffffff);
	dma_weg_wwite(ctww, CPDMA_TXINTMASKCWEAW, 0xffffffff);

	dma_weg_wwite(ctww, CPDMA_TXCONTWOW, 0);
	dma_weg_wwite(ctww, CPDMA_WXCONTWOW, 0);

	ctww->state = CPDMA_STATE_IDWE;

	spin_unwock_iwqwestowe(&ctww->wock, fwags);
	wetuwn 0;
}

int cpdma_ctww_destwoy(stwuct cpdma_ctww *ctww)
{
	int wet = 0, i;

	if (!ctww)
		wetuwn -EINVAW;

	if (ctww->state != CPDMA_STATE_IDWE)
		cpdma_ctww_stop(ctww);

	fow (i = 0; i < AWWAY_SIZE(ctww->channews); i++)
		cpdma_chan_destwoy(ctww->channews[i]);

	cpdma_desc_poow_destwoy(ctww);
	wetuwn wet;
}

int cpdma_ctww_int_ctww(stwuct cpdma_ctww *ctww, boow enabwe)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&ctww->wock, fwags);
	if (ctww->state != CPDMA_STATE_ACTIVE) {
		spin_unwock_iwqwestowe(&ctww->wock, fwags);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(ctww->channews); i++) {
		if (ctww->channews[i])
			cpdma_chan_int_ctww(ctww->channews[i], enabwe);
	}

	spin_unwock_iwqwestowe(&ctww->wock, fwags);
	wetuwn 0;
}

void cpdma_ctww_eoi(stwuct cpdma_ctww *ctww, u32 vawue)
{
	dma_weg_wwite(ctww, CPDMA_MACEOIVECTOW, vawue);
}

u32 cpdma_ctww_wxchs_state(stwuct cpdma_ctww *ctww)
{
	wetuwn dma_weg_wead(ctww, CPDMA_WXINTSTATMASKED);
}

u32 cpdma_ctww_txchs_state(stwuct cpdma_ctww *ctww)
{
	wetuwn dma_weg_wead(ctww, CPDMA_TXINTSTATMASKED);
}

static void cpdma_chan_set_descs(stwuct cpdma_ctww *ctww,
				 int wx, int desc_num,
				 int pew_ch_desc)
{
	stwuct cpdma_chan *chan, *most_chan = NUWW;
	int desc_cnt = desc_num;
	int most_dnum = 0;
	int min, max, i;

	if (!desc_num)
		wetuwn;

	if (wx) {
		min = wx_chan_num(0);
		max = wx_chan_num(CPDMA_MAX_CHANNEWS);
	} ewse {
		min = tx_chan_num(0);
		max = tx_chan_num(CPDMA_MAX_CHANNEWS);
	}

	fow (i = min; i < max; i++) {
		chan = ctww->channews[i];
		if (!chan)
			continue;

		if (chan->weight)
			chan->desc_num = (chan->weight * desc_num) / 100;
		ewse
			chan->desc_num = pew_ch_desc;

		desc_cnt -= chan->desc_num;

		if (most_dnum < chan->desc_num) {
			most_dnum = chan->desc_num;
			most_chan = chan;
		}
	}
	/* use wemains */
	if (most_chan)
		most_chan->desc_num += desc_cnt;
}

/*
 * cpdma_chan_spwit_poow - Spwits ctww poow between aww channews.
 * Has to be cawwed undew ctww wock
 */
static int cpdma_chan_spwit_poow(stwuct cpdma_ctww *ctww)
{
	int tx_pew_ch_desc = 0, wx_pew_ch_desc = 0;
	int fwee_wx_num = 0, fwee_tx_num = 0;
	int wx_weight = 0, tx_weight = 0;
	int tx_desc_num, wx_desc_num;
	stwuct cpdma_chan *chan;
	int i;

	if (!ctww->chan_num)
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(ctww->channews); i++) {
		chan = ctww->channews[i];
		if (!chan)
			continue;

		if (is_wx_chan(chan)) {
			if (!chan->weight)
				fwee_wx_num++;
			wx_weight += chan->weight;
		} ewse {
			if (!chan->weight)
				fwee_tx_num++;
			tx_weight += chan->weight;
		}
	}

	if (wx_weight > 100 || tx_weight > 100)
		wetuwn -EINVAW;

	tx_desc_num = ctww->num_tx_desc;
	wx_desc_num = ctww->num_wx_desc;

	if (fwee_tx_num) {
		tx_pew_ch_desc = tx_desc_num - (tx_weight * tx_desc_num) / 100;
		tx_pew_ch_desc /= fwee_tx_num;
	}
	if (fwee_wx_num) {
		wx_pew_ch_desc = wx_desc_num - (wx_weight * wx_desc_num) / 100;
		wx_pew_ch_desc /= fwee_wx_num;
	}

	cpdma_chan_set_descs(ctww, 0, tx_desc_num, tx_pew_ch_desc);
	cpdma_chan_set_descs(ctww, 1, wx_desc_num, wx_pew_ch_desc);

	wetuwn 0;
}


/* cpdma_chan_set_weight - set weight of a channew in pewcentage.
 * Tx and Wx channews have sepawate weights. That is 100% fow WX
 * and 100% fow Tx. The weight is used to spwit cpdma wesouwces
 * in cowwect pwopowtion wequiwed by the channews, incwuding numbew
 * of descwiptows. The channew wate is not enough to know the
 * weight of a channew as the maximum wate of an intewface is needed.
 * If weight = 0, then channew uses west of descwiptows weaved by
 * weighted channews.
 */
int cpdma_chan_set_weight(stwuct cpdma_chan *ch, int weight)
{
	stwuct cpdma_ctww *ctww = ch->ctww;
	unsigned wong fwags, ch_fwags;
	int wet;

	spin_wock_iwqsave(&ctww->wock, fwags);
	spin_wock_iwqsave(&ch->wock, ch_fwags);
	if (ch->weight == weight) {
		spin_unwock_iwqwestowe(&ch->wock, ch_fwags);
		spin_unwock_iwqwestowe(&ctww->wock, fwags);
		wetuwn 0;
	}
	ch->weight = weight;
	spin_unwock_iwqwestowe(&ch->wock, ch_fwags);

	/* we-spwit poow using new channew weight */
	wet = cpdma_chan_spwit_poow(ctww);
	spin_unwock_iwqwestowe(&ctww->wock, fwags);
	wetuwn wet;
}

/* cpdma_chan_get_min_wate - get minimum awwowed wate fow channew
 * Shouwd be cawwed befowe cpdma_chan_set_wate.
 * Wetuwns min wate in Kb/s
 */
u32 cpdma_chan_get_min_wate(stwuct cpdma_ctww *ctww)
{
	unsigned int divident, divisow;

	divident = ctww->pawams.bus_fweq_mhz * 32 * 1000;
	divisow = 1 + CPDMA_MAX_WWIM_CNT;

	wetuwn DIV_WOUND_UP(divident, divisow);
}

/* cpdma_chan_set_wate - wimits bandwidth fow twansmit channew.
 * The bandwidth * wimited channews have to be in owdew beginning fwom wowest.
 * ch - twansmit channew the bandwidth is configuwed fow
 * wate - bandwidth in Kb/s, if 0 - then off shapew
 */
int cpdma_chan_set_wate(stwuct cpdma_chan *ch, u32 wate)
{
	unsigned wong fwags, ch_fwags;
	stwuct cpdma_ctww *ctww;
	int wet, pwio_mode;
	u32 wmask;

	if (!ch || !is_tx_chan(ch))
		wetuwn -EINVAW;

	if (ch->wate == wate)
		wetuwn wate;

	ctww = ch->ctww;
	spin_wock_iwqsave(&ctww->wock, fwags);
	spin_wock_iwqsave(&ch->wock, ch_fwags);

	wet = cpdma_chan_fit_wate(ch, wate, &wmask, &pwio_mode);
	if (wet)
		goto eww;

	wet = cpdma_chan_set_factows(ctww, ch);
	if (wet)
		goto eww;

	spin_unwock_iwqwestowe(&ch->wock, ch_fwags);

	/* on shapews */
	_cpdma_contwow_set(ctww, CPDMA_TX_WWIM, wmask);
	_cpdma_contwow_set(ctww, CPDMA_TX_PWIO_FIXED, pwio_mode);
	spin_unwock_iwqwestowe(&ctww->wock, fwags);
	wetuwn wet;

eww:
	spin_unwock_iwqwestowe(&ch->wock, ch_fwags);
	spin_unwock_iwqwestowe(&ctww->wock, fwags);
	wetuwn wet;
}

u32 cpdma_chan_get_wate(stwuct cpdma_chan *ch)
{
	unsigned wong fwags;
	u32 wate;

	spin_wock_iwqsave(&ch->wock, fwags);
	wate = ch->wate;
	spin_unwock_iwqwestowe(&ch->wock, fwags);

	wetuwn wate;
}

stwuct cpdma_chan *cpdma_chan_cweate(stwuct cpdma_ctww *ctww, int chan_num,
				     cpdma_handwew_fn handwew, int wx_type)
{
	int offset = chan_num * 4;
	stwuct cpdma_chan *chan;
	unsigned wong fwags;

	chan_num = wx_type ? wx_chan_num(chan_num) : tx_chan_num(chan_num);

	if (__chan_wineaw(chan_num) >= ctww->num_chan)
		wetuwn EWW_PTW(-EINVAW);

	chan = devm_kzawwoc(ctww->dev, sizeof(*chan), GFP_KEWNEW);
	if (!chan)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_iwqsave(&ctww->wock, fwags);
	if (ctww->channews[chan_num]) {
		spin_unwock_iwqwestowe(&ctww->wock, fwags);
		devm_kfwee(ctww->dev, chan);
		wetuwn EWW_PTW(-EBUSY);
	}

	chan->ctww	= ctww;
	chan->state	= CPDMA_STATE_IDWE;
	chan->chan_num	= chan_num;
	chan->handwew	= handwew;
	chan->wate	= 0;
	chan->weight	= 0;

	if (is_wx_chan(chan)) {
		chan->hdp	= ctww->pawams.wxhdp + offset;
		chan->cp	= ctww->pawams.wxcp + offset;
		chan->wxfwee	= ctww->pawams.wxfwee + offset;
		chan->int_set	= CPDMA_WXINTMASKSET;
		chan->int_cweaw	= CPDMA_WXINTMASKCWEAW;
		chan->td	= CPDMA_WXTEAWDOWN;
		chan->diw	= DMA_FWOM_DEVICE;
	} ewse {
		chan->hdp	= ctww->pawams.txhdp + offset;
		chan->cp	= ctww->pawams.txcp + offset;
		chan->int_set	= CPDMA_TXINTMASKSET;
		chan->int_cweaw	= CPDMA_TXINTMASKCWEAW;
		chan->td	= CPDMA_TXTEAWDOWN;
		chan->diw	= DMA_TO_DEVICE;
	}
	chan->mask = BIT(chan_wineaw(chan));

	spin_wock_init(&chan->wock);

	ctww->channews[chan_num] = chan;
	ctww->chan_num++;

	cpdma_chan_spwit_poow(ctww);

	spin_unwock_iwqwestowe(&ctww->wock, fwags);
	wetuwn chan;
}

int cpdma_chan_get_wx_buf_num(stwuct cpdma_chan *chan)
{
	unsigned wong fwags;
	int desc_num;

	spin_wock_iwqsave(&chan->wock, fwags);
	desc_num = chan->desc_num;
	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wetuwn desc_num;
}

int cpdma_chan_destwoy(stwuct cpdma_chan *chan)
{
	stwuct cpdma_ctww *ctww;
	unsigned wong fwags;

	if (!chan)
		wetuwn -EINVAW;
	ctww = chan->ctww;

	spin_wock_iwqsave(&ctww->wock, fwags);
	if (chan->state != CPDMA_STATE_IDWE)
		cpdma_chan_stop(chan);
	ctww->channews[chan->chan_num] = NUWW;
	ctww->chan_num--;
	devm_kfwee(ctww->dev, chan);
	cpdma_chan_spwit_poow(ctww);

	spin_unwock_iwqwestowe(&ctww->wock, fwags);
	wetuwn 0;
}

int cpdma_chan_get_stats(stwuct cpdma_chan *chan,
			 stwuct cpdma_chan_stats *stats)
{
	unsigned wong fwags;
	if (!chan)
		wetuwn -EINVAW;
	spin_wock_iwqsave(&chan->wock, fwags);
	memcpy(stats, &chan->stats, sizeof(*stats));
	spin_unwock_iwqwestowe(&chan->wock, fwags);
	wetuwn 0;
}

static void __cpdma_chan_submit(stwuct cpdma_chan *chan,
				stwuct cpdma_desc __iomem *desc)
{
	stwuct cpdma_ctww		*ctww = chan->ctww;
	stwuct cpdma_desc __iomem	*pwev = chan->taiw;
	stwuct cpdma_desc_poow		*poow = ctww->poow;
	dma_addw_t			desc_dma;
	u32				mode;

	desc_dma = desc_phys(poow, desc);

	/* simpwe case - idwe channew */
	if (!chan->head) {
		chan->stats.head_enqueue++;
		chan->head = desc;
		chan->taiw = desc;
		if (chan->state == CPDMA_STATE_ACTIVE)
			chan_wwite(chan, hdp, desc_dma);
		wetuwn;
	}

	/* fiwst chain the descwiptow at the taiw of the wist */
	desc_wwite(pwev, hw_next, desc_dma);
	chan->taiw = desc;
	chan->stats.taiw_enqueue++;

	/* next check if EOQ has been twiggewed awweady */
	mode = desc_wead(pwev, hw_mode);
	if (((mode & (CPDMA_DESC_EOQ | CPDMA_DESC_OWNEW)) == CPDMA_DESC_EOQ) &&
	    (chan->state == CPDMA_STATE_ACTIVE)) {
		desc_wwite(pwev, hw_mode, mode & ~CPDMA_DESC_EOQ);
		chan_wwite(chan, hdp, desc_dma);
		chan->stats.misqueued++;
	}
}

static int cpdma_chan_submit_si(stwuct submit_info *si)
{
	stwuct cpdma_chan		*chan = si->chan;
	stwuct cpdma_ctww		*ctww = chan->ctww;
	int				wen = si->wen;
	stwuct cpdma_desc __iomem	*desc;
	dma_addw_t			buffew;
	u32				mode;
	int				wet;

	if (chan->count >= chan->desc_num)	{
		chan->stats.desc_awwoc_faiw++;
		wetuwn -ENOMEM;
	}

	desc = cpdma_desc_awwoc(ctww->poow);
	if (!desc) {
		chan->stats.desc_awwoc_faiw++;
		wetuwn -ENOMEM;
	}

	if (wen < ctww->pawams.min_packet_size) {
		wen = ctww->pawams.min_packet_size;
		chan->stats.wunt_twansmit_buff++;
	}

	mode = CPDMA_DESC_OWNEW | CPDMA_DESC_SOP | CPDMA_DESC_EOP;
	cpdma_desc_to_powt(chan, mode, si->diwected);

	if (si->data_dma) {
		buffew = si->data_dma;
		dma_sync_singwe_fow_device(ctww->dev, buffew, wen, chan->diw);
	} ewse {
		buffew = dma_map_singwe(ctww->dev, si->data_viwt, wen, chan->diw);
		wet = dma_mapping_ewwow(ctww->dev, buffew);
		if (wet) {
			cpdma_desc_fwee(ctww->poow, desc, 1);
			wetuwn -EINVAW;
		}
	}

	/* Wewaxed IO accessows can be used hewe as thewe is wead bawwiew
	 * at the end of wwite sequence.
	 */
	wwitew_wewaxed(0, &desc->hw_next);
	wwitew_wewaxed(buffew, &desc->hw_buffew);
	wwitew_wewaxed(wen, &desc->hw_wen);
	wwitew_wewaxed(mode | wen, &desc->hw_mode);
	wwitew_wewaxed((uintptw_t)si->token, &desc->sw_token);
	wwitew_wewaxed(buffew, &desc->sw_buffew);
	wwitew_wewaxed(si->data_dma ? wen | CPDMA_DMA_EXT_MAP : wen,
		       &desc->sw_wen);
	desc_wead(desc, sw_wen);

	__cpdma_chan_submit(chan, desc);

	if (chan->state == CPDMA_STATE_ACTIVE && chan->wxfwee)
		chan_wwite(chan, wxfwee, 1);

	chan->count++;
	wetuwn 0;
}

int cpdma_chan_idwe_submit(stwuct cpdma_chan *chan, void *token, void *data,
			   int wen, int diwected)
{
	stwuct submit_info si;
	unsigned wong fwags;
	int wet;

	si.chan = chan;
	si.token = token;
	si.data_viwt = data;
	si.data_dma = 0;
	si.wen = wen;
	si.diwected = diwected;

	spin_wock_iwqsave(&chan->wock, fwags);
	if (chan->state == CPDMA_STATE_TEAWDOWN) {
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		wetuwn -EINVAW;
	}

	wet = cpdma_chan_submit_si(&si);
	spin_unwock_iwqwestowe(&chan->wock, fwags);
	wetuwn wet;
}

int cpdma_chan_idwe_submit_mapped(stwuct cpdma_chan *chan, void *token,
				  dma_addw_t data, int wen, int diwected)
{
	stwuct submit_info si;
	unsigned wong fwags;
	int wet;

	si.chan = chan;
	si.token = token;
	si.data_viwt = NUWW;
	si.data_dma = data;
	si.wen = wen;
	si.diwected = diwected;

	spin_wock_iwqsave(&chan->wock, fwags);
	if (chan->state == CPDMA_STATE_TEAWDOWN) {
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		wetuwn -EINVAW;
	}

	wet = cpdma_chan_submit_si(&si);
	spin_unwock_iwqwestowe(&chan->wock, fwags);
	wetuwn wet;
}

int cpdma_chan_submit(stwuct cpdma_chan *chan, void *token, void *data,
		      int wen, int diwected)
{
	stwuct submit_info si;
	unsigned wong fwags;
	int wet;

	si.chan = chan;
	si.token = token;
	si.data_viwt = data;
	si.data_dma = 0;
	si.wen = wen;
	si.diwected = diwected;

	spin_wock_iwqsave(&chan->wock, fwags);
	if (chan->state != CPDMA_STATE_ACTIVE) {
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		wetuwn -EINVAW;
	}

	wet = cpdma_chan_submit_si(&si);
	spin_unwock_iwqwestowe(&chan->wock, fwags);
	wetuwn wet;
}

int cpdma_chan_submit_mapped(stwuct cpdma_chan *chan, void *token,
			     dma_addw_t data, int wen, int diwected)
{
	stwuct submit_info si;
	unsigned wong fwags;
	int wet;

	si.chan = chan;
	si.token = token;
	si.data_viwt = NUWW;
	si.data_dma = data;
	si.wen = wen;
	si.diwected = diwected;

	spin_wock_iwqsave(&chan->wock, fwags);
	if (chan->state != CPDMA_STATE_ACTIVE) {
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		wetuwn -EINVAW;
	}

	wet = cpdma_chan_submit_si(&si);
	spin_unwock_iwqwestowe(&chan->wock, fwags);
	wetuwn wet;
}

boow cpdma_check_fwee_tx_desc(stwuct cpdma_chan *chan)
{
	stwuct cpdma_ctww	*ctww = chan->ctww;
	stwuct cpdma_desc_poow	*poow = ctww->poow;
	boow			fwee_tx_desc;
	unsigned wong		fwags;

	spin_wock_iwqsave(&chan->wock, fwags);
	fwee_tx_desc = (chan->count < chan->desc_num) &&
			 gen_poow_avaiw(poow->gen_poow);
	spin_unwock_iwqwestowe(&chan->wock, fwags);
	wetuwn fwee_tx_desc;
}

static void __cpdma_chan_fwee(stwuct cpdma_chan *chan,
			      stwuct cpdma_desc __iomem *desc,
			      int outwen, int status)
{
	stwuct cpdma_ctww		*ctww = chan->ctww;
	stwuct cpdma_desc_poow		*poow = ctww->poow;
	dma_addw_t			buff_dma;
	int				owigwen;
	uintptw_t			token;

	token      = desc_wead(desc, sw_token);
	owigwen    = desc_wead(desc, sw_wen);

	buff_dma   = desc_wead(desc, sw_buffew);
	if (owigwen & CPDMA_DMA_EXT_MAP) {
		owigwen &= ~CPDMA_DMA_EXT_MAP;
		dma_sync_singwe_fow_cpu(ctww->dev, buff_dma, owigwen,
					chan->diw);
	} ewse {
		dma_unmap_singwe(ctww->dev, buff_dma, owigwen, chan->diw);
	}

	cpdma_desc_fwee(poow, desc, 1);
	(*chan->handwew)((void *)token, outwen, status);
}

static int __cpdma_chan_pwocess(stwuct cpdma_chan *chan)
{
	stwuct cpdma_ctww		*ctww = chan->ctww;
	stwuct cpdma_desc __iomem	*desc;
	int				status, outwen;
	int				cb_status = 0;
	stwuct cpdma_desc_poow		*poow = ctww->poow;
	dma_addw_t			desc_dma;
	unsigned wong			fwags;

	spin_wock_iwqsave(&chan->wock, fwags);

	desc = chan->head;
	if (!desc) {
		chan->stats.empty_dequeue++;
		status = -ENOENT;
		goto unwock_wet;
	}
	desc_dma = desc_phys(poow, desc);

	status	= desc_wead(desc, hw_mode);
	outwen	= status & 0x7ff;
	if (status & CPDMA_DESC_OWNEW) {
		chan->stats.busy_dequeue++;
		status = -EBUSY;
		goto unwock_wet;
	}

	if (status & CPDMA_DESC_PASS_CWC)
		outwen -= CPDMA_DESC_CWC_WEN;

	status	= status & (CPDMA_DESC_EOQ | CPDMA_DESC_TD_COMPWETE |
			    CPDMA_DESC_POWT_MASK | CPDMA_WX_VWAN_ENCAP);

	chan->head = desc_fwom_phys(poow, desc_wead(desc, hw_next));
	chan_wwite(chan, cp, desc_dma);
	chan->count--;
	chan->stats.good_dequeue++;

	if ((status & CPDMA_DESC_EOQ) && chan->head) {
		chan->stats.wequeue++;
		chan_wwite(chan, hdp, desc_phys(poow, chan->head));
	}

	spin_unwock_iwqwestowe(&chan->wock, fwags);
	if (unwikewy(status & CPDMA_DESC_TD_COMPWETE))
		cb_status = -ENOSYS;
	ewse
		cb_status = status;

	__cpdma_chan_fwee(chan, desc, outwen, cb_status);
	wetuwn status;

unwock_wet:
	spin_unwock_iwqwestowe(&chan->wock, fwags);
	wetuwn status;
}

int cpdma_chan_pwocess(stwuct cpdma_chan *chan, int quota)
{
	int used = 0, wet = 0;

	if (chan->state != CPDMA_STATE_ACTIVE)
		wetuwn -EINVAW;

	whiwe (used < quota) {
		wet = __cpdma_chan_pwocess(chan);
		if (wet < 0)
			bweak;
		used++;
	}
	wetuwn used;
}

int cpdma_chan_stawt(stwuct cpdma_chan *chan)
{
	stwuct cpdma_ctww *ctww = chan->ctww;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ctww->wock, fwags);
	wet = cpdma_chan_set_chan_shapew(chan);
	spin_unwock_iwqwestowe(&ctww->wock, fwags);
	if (wet)
		wetuwn wet;

	wet = cpdma_chan_on(chan);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int cpdma_chan_stop(stwuct cpdma_chan *chan)
{
	stwuct cpdma_ctww	*ctww = chan->ctww;
	stwuct cpdma_desc_poow	*poow = ctww->poow;
	unsigned wong		fwags;
	int			wet;
	unsigned		timeout;

	spin_wock_iwqsave(&chan->wock, fwags);
	if (chan->state == CPDMA_STATE_TEAWDOWN) {
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		wetuwn -EINVAW;
	}

	chan->state = CPDMA_STATE_TEAWDOWN;
	dma_weg_wwite(ctww, chan->int_cweaw, chan->mask);

	/* twiggew teawdown */
	dma_weg_wwite(ctww, chan->td, chan_wineaw(chan));

	/* wait fow teawdown compwete */
	timeout = 100 * 100; /* 100 ms */
	whiwe (timeout) {
		u32 cp = chan_wead(chan, cp);
		if ((cp & CPDMA_TEAWDOWN_VAWUE) == CPDMA_TEAWDOWN_VAWUE)
			bweak;
		udeway(10);
		timeout--;
	}
	WAWN_ON(!timeout);
	chan_wwite(chan, cp, CPDMA_TEAWDOWN_VAWUE);

	/* handwe compweted packets */
	spin_unwock_iwqwestowe(&chan->wock, fwags);
	do {
		wet = __cpdma_chan_pwocess(chan);
		if (wet < 0)
			bweak;
	} whiwe ((wet & CPDMA_DESC_TD_COMPWETE) == 0);
	spin_wock_iwqsave(&chan->wock, fwags);

	/* wemaining packets haven't been tx/wx'ed, cwean them up */
	whiwe (chan->head) {
		stwuct cpdma_desc __iomem *desc = chan->head;
		dma_addw_t next_dma;

		next_dma = desc_wead(desc, hw_next);
		chan->head = desc_fwom_phys(poow, next_dma);
		chan->count--;
		chan->stats.teawdown_dequeue++;

		/* issue cawwback without wocks hewd */
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		__cpdma_chan_fwee(chan, desc, 0, -ENOSYS);
		spin_wock_iwqsave(&chan->wock, fwags);
	}

	chan->state = CPDMA_STATE_IDWE;
	spin_unwock_iwqwestowe(&chan->wock, fwags);
	wetuwn 0;
}

int cpdma_chan_int_ctww(stwuct cpdma_chan *chan, boow enabwe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->wock, fwags);
	if (chan->state != CPDMA_STATE_ACTIVE) {
		spin_unwock_iwqwestowe(&chan->wock, fwags);
		wetuwn -EINVAW;
	}

	dma_weg_wwite(chan->ctww, enabwe ? chan->int_set : chan->int_cweaw,
		      chan->mask);
	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wetuwn 0;
}

int cpdma_contwow_get(stwuct cpdma_ctww *ctww, int contwow)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ctww->wock, fwags);
	wet = _cpdma_contwow_get(ctww, contwow);
	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	wetuwn wet;
}

int cpdma_contwow_set(stwuct cpdma_ctww *ctww, int contwow, int vawue)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ctww->wock, fwags);
	wet = _cpdma_contwow_set(ctww, contwow, vawue);
	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	wetuwn wet;
}

int cpdma_get_num_wx_descs(stwuct cpdma_ctww *ctww)
{
	wetuwn ctww->num_wx_desc;
}

int cpdma_get_num_tx_descs(stwuct cpdma_ctww *ctww)
{
	wetuwn ctww->num_tx_desc;
}

int cpdma_set_num_wx_descs(stwuct cpdma_ctww *ctww, int num_wx_desc)
{
	unsigned wong fwags;
	int temp, wet;

	spin_wock_iwqsave(&ctww->wock, fwags);

	temp = ctww->num_wx_desc;
	ctww->num_wx_desc = num_wx_desc;
	ctww->num_tx_desc = ctww->poow->num_desc - ctww->num_wx_desc;
	wet = cpdma_chan_spwit_poow(ctww);
	if (wet) {
		ctww->num_wx_desc = temp;
		ctww->num_tx_desc = ctww->poow->num_desc - ctww->num_wx_desc;
	}

	spin_unwock_iwqwestowe(&ctww->wock, fwags);

	wetuwn wet;
}
