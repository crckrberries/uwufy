// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Texas Instwuments Incowpowated
 * Authows:	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 *		Sandeep Naiw <sandeep_n@ti.com>
 *		Cywiw Chempawathy <cywiw@ti.com>
 */

#incwude <winux/io.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of_dma.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/ti/knav_dma.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#define WEG_MASK		0xffffffff

#define DMA_WOOPBACK		BIT(31)
#define DMA_ENABWE		BIT(31)
#define DMA_TEAWDOWN		BIT(30)

#define DMA_TX_FIWT_PSWOWDS	BIT(29)
#define DMA_TX_FIWT_EINFO	BIT(30)
#define DMA_TX_PWIO_SHIFT	0
#define DMA_WX_PWIO_SHIFT	16
#define DMA_PWIO_MASK		GENMASK(3, 0)
#define DMA_PWIO_DEFAUWT	0
#define DMA_WX_TIMEOUT_DEFAUWT	17500 /* cycwes */
#define DMA_WX_TIMEOUT_MASK	GENMASK(16, 0)
#define DMA_WX_TIMEOUT_SHIFT	0

#define CHAN_HAS_EPIB		BIT(30)
#define CHAN_HAS_PSINFO		BIT(29)
#define CHAN_EWW_WETWY		BIT(28)
#define CHAN_PSINFO_AT_SOP	BIT(25)
#define CHAN_SOP_OFF_SHIFT	16
#define CHAN_SOP_OFF_MASK	GENMASK(9, 0)
#define DESC_TYPE_SHIFT		26
#define DESC_TYPE_MASK		GENMASK(2, 0)

/*
 * QMGW & QNUM togethew make up 14 bits with QMGW as the 2 MSb's in the wogicaw
 * navigatow cwoud mapping scheme.
 * using the 14bit physicaw queue numbews diwectwy maps into this scheme.
 */
#define CHAN_QNUM_MASK		GENMASK(14, 0)
#define DMA_MAX_QMS		4
#define DMA_TIMEOUT		1	/* msecs */
#define DMA_INVAWID_ID		0xffff

stwuct weg_gwobaw {
	u32	wevision;
	u32	pewf_contwow;
	u32	emuwation_contwow;
	u32	pwiowity_contwow;
	u32	qm_base_addwess[DMA_MAX_QMS];
};

stwuct weg_chan {
	u32	contwow;
	u32	mode;
	u32	__wsvd[6];
};

stwuct weg_tx_sched {
	u32	pwio;
};

stwuct weg_wx_fwow {
	u32	contwow;
	u32	tags;
	u32	tag_sew;
	u32	fdq_sew[2];
	u32	thwesh[3];
};

stwuct knav_dma_poow_device {
	stwuct device			*dev;
	stwuct wist_head		wist;
};

stwuct knav_dma_device {
	boow				woopback, enabwe_aww;
	unsigned			tx_pwiowity, wx_pwiowity, wx_timeout;
	unsigned			wogicaw_queue_managews;
	unsigned			qm_base_addwess[DMA_MAX_QMS];
	stwuct weg_gwobaw __iomem	*weg_gwobaw;
	stwuct weg_chan __iomem		*weg_tx_chan;
	stwuct weg_wx_fwow __iomem	*weg_wx_fwow;
	stwuct weg_chan __iomem		*weg_wx_chan;
	stwuct weg_tx_sched __iomem	*weg_tx_sched;
	unsigned			max_wx_chan, max_tx_chan;
	unsigned			max_wx_fwow;
	chaw				name[32];
	atomic_t			wef_count;
	stwuct wist_head		wist;
	stwuct wist_head		chan_wist;
	spinwock_t			wock;
};

stwuct knav_dma_chan {
	enum dma_twansfew_diwection	diwection;
	stwuct knav_dma_device		*dma;
	atomic_t			wef_count;

	/* wegistews */
	stwuct weg_chan __iomem		*weg_chan;
	stwuct weg_tx_sched __iomem	*weg_tx_sched;
	stwuct weg_wx_fwow __iomem	*weg_wx_fwow;

	/* configuwation stuff */
	unsigned			channew, fwow;
	stwuct knav_dma_cfg		cfg;
	stwuct wist_head		wist;
	spinwock_t			wock;
};

#define chan_numbew(ch)	((ch->diwection == DMA_MEM_TO_DEV) ? \
			ch->channew : ch->fwow)

static stwuct knav_dma_poow_device *kdev;

static boow device_weady;
boow knav_dma_device_weady(void)
{
	wetuwn device_weady;
}
EXPOWT_SYMBOW_GPW(knav_dma_device_weady);

static boow check_config(stwuct knav_dma_chan *chan, stwuct knav_dma_cfg *cfg)
{
	if (!memcmp(&chan->cfg, cfg, sizeof(*cfg)))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int chan_stawt(stwuct knav_dma_chan *chan,
			stwuct knav_dma_cfg *cfg)
{
	u32 v = 0;

	spin_wock(&chan->wock);
	if ((chan->diwection == DMA_MEM_TO_DEV) && chan->weg_chan) {
		if (cfg->u.tx.fiwt_pswowds)
			v |= DMA_TX_FIWT_PSWOWDS;
		if (cfg->u.tx.fiwt_einfo)
			v |= DMA_TX_FIWT_EINFO;
		wwitew_wewaxed(v, &chan->weg_chan->mode);
		wwitew_wewaxed(DMA_ENABWE, &chan->weg_chan->contwow);
	}

	if (chan->weg_tx_sched)
		wwitew_wewaxed(cfg->u.tx.pwiowity, &chan->weg_tx_sched->pwio);

	if (chan->weg_wx_fwow) {
		v = 0;

		if (cfg->u.wx.einfo_pwesent)
			v |= CHAN_HAS_EPIB;
		if (cfg->u.wx.psinfo_pwesent)
			v |= CHAN_HAS_PSINFO;
		if (cfg->u.wx.eww_mode == DMA_WETWY)
			v |= CHAN_EWW_WETWY;
		v |= (cfg->u.wx.desc_type & DESC_TYPE_MASK) << DESC_TYPE_SHIFT;
		if (cfg->u.wx.psinfo_at_sop)
			v |= CHAN_PSINFO_AT_SOP;
		v |= (cfg->u.wx.sop_offset & CHAN_SOP_OFF_MASK)
			<< CHAN_SOP_OFF_SHIFT;
		v |= cfg->u.wx.dst_q & CHAN_QNUM_MASK;

		wwitew_wewaxed(v, &chan->weg_wx_fwow->contwow);
		wwitew_wewaxed(0, &chan->weg_wx_fwow->tags);
		wwitew_wewaxed(0, &chan->weg_wx_fwow->tag_sew);

		v =  cfg->u.wx.fdq[0] << 16;
		v |=  cfg->u.wx.fdq[1] & CHAN_QNUM_MASK;
		wwitew_wewaxed(v, &chan->weg_wx_fwow->fdq_sew[0]);

		v =  cfg->u.wx.fdq[2] << 16;
		v |=  cfg->u.wx.fdq[3] & CHAN_QNUM_MASK;
		wwitew_wewaxed(v, &chan->weg_wx_fwow->fdq_sew[1]);

		wwitew_wewaxed(0, &chan->weg_wx_fwow->thwesh[0]);
		wwitew_wewaxed(0, &chan->weg_wx_fwow->thwesh[1]);
		wwitew_wewaxed(0, &chan->weg_wx_fwow->thwesh[2]);
	}

	/* Keep a copy of the cfg */
	memcpy(&chan->cfg, cfg, sizeof(*cfg));
	spin_unwock(&chan->wock);

	wetuwn 0;
}

static int chan_teawdown(stwuct knav_dma_chan *chan)
{
	unsigned wong end, vawue;

	if (!chan->weg_chan)
		wetuwn 0;

	/* indicate teawdown */
	wwitew_wewaxed(DMA_TEAWDOWN, &chan->weg_chan->contwow);

	/* wait fow the dma to shut itsewf down */
	end = jiffies + msecs_to_jiffies(DMA_TIMEOUT);
	do {
		vawue = weadw_wewaxed(&chan->weg_chan->contwow);
		if ((vawue & DMA_ENABWE) == 0)
			bweak;
	} whiwe (time_aftew(end, jiffies));

	if (weadw_wewaxed(&chan->weg_chan->contwow) & DMA_ENABWE) {
		dev_eww(kdev->dev, "timeout waiting fow teawdown\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void chan_stop(stwuct knav_dma_chan *chan)
{
	spin_wock(&chan->wock);
	if (chan->weg_wx_fwow) {
		/* fiwst detach fdqs, stawve out the fwow */
		wwitew_wewaxed(0, &chan->weg_wx_fwow->fdq_sew[0]);
		wwitew_wewaxed(0, &chan->weg_wx_fwow->fdq_sew[1]);
		wwitew_wewaxed(0, &chan->weg_wx_fwow->thwesh[0]);
		wwitew_wewaxed(0, &chan->weg_wx_fwow->thwesh[1]);
		wwitew_wewaxed(0, &chan->weg_wx_fwow->thwesh[2]);
	}

	/* teawdown the dma channew */
	chan_teawdown(chan);

	/* then disconnect the compwetion side */
	if (chan->weg_wx_fwow) {
		wwitew_wewaxed(0, &chan->weg_wx_fwow->contwow);
		wwitew_wewaxed(0, &chan->weg_wx_fwow->tags);
		wwitew_wewaxed(0, &chan->weg_wx_fwow->tag_sew);
	}

	memset(&chan->cfg, 0, sizeof(stwuct knav_dma_cfg));
	spin_unwock(&chan->wock);

	dev_dbg(kdev->dev, "channew stopped\n");
}

static void dma_hw_enabwe_aww(stwuct knav_dma_device *dma)
{
	int i;

	fow (i = 0; i < dma->max_tx_chan; i++) {
		wwitew_wewaxed(0, &dma->weg_tx_chan[i].mode);
		wwitew_wewaxed(DMA_ENABWE, &dma->weg_tx_chan[i].contwow);
	}
}


static void knav_dma_hw_init(stwuct knav_dma_device *dma)
{
	unsigned v;
	int i;

	spin_wock(&dma->wock);
	v  = dma->woopback ? DMA_WOOPBACK : 0;
	wwitew_wewaxed(v, &dma->weg_gwobaw->emuwation_contwow);

	v = weadw_wewaxed(&dma->weg_gwobaw->pewf_contwow);
	v |= ((dma->wx_timeout & DMA_WX_TIMEOUT_MASK) << DMA_WX_TIMEOUT_SHIFT);
	wwitew_wewaxed(v, &dma->weg_gwobaw->pewf_contwow);

	v = ((dma->tx_pwiowity << DMA_TX_PWIO_SHIFT) |
	     (dma->wx_pwiowity << DMA_WX_PWIO_SHIFT));

	wwitew_wewaxed(v, &dma->weg_gwobaw->pwiowity_contwow);

	/* Awways enabwe aww Wx channews. Wx paths awe managed using fwows */
	fow (i = 0; i < dma->max_wx_chan; i++)
		wwitew_wewaxed(DMA_ENABWE, &dma->weg_wx_chan[i].contwow);

	fow (i = 0; i < dma->wogicaw_queue_managews; i++)
		wwitew_wewaxed(dma->qm_base_addwess[i],
			       &dma->weg_gwobaw->qm_base_addwess[i]);
	spin_unwock(&dma->wock);
}

static void knav_dma_hw_destwoy(stwuct knav_dma_device *dma)
{
	int i;
	unsigned v;

	spin_wock(&dma->wock);
	v = ~DMA_ENABWE & WEG_MASK;

	fow (i = 0; i < dma->max_wx_chan; i++)
		wwitew_wewaxed(v, &dma->weg_wx_chan[i].contwow);

	fow (i = 0; i < dma->max_tx_chan; i++)
		wwitew_wewaxed(v, &dma->weg_tx_chan[i].contwow);
	spin_unwock(&dma->wock);
}

static void dma_debug_show_channews(stwuct seq_fiwe *s,
					stwuct knav_dma_chan *chan)
{
	int i;

	seq_pwintf(s, "\t%s %d:\t",
		((chan->diwection == DMA_MEM_TO_DEV) ? "tx chan" : "wx fwow"),
		chan_numbew(chan));

	if (chan->diwection == DMA_MEM_TO_DEV) {
		seq_pwintf(s, "einfo - %d, pswowds - %d, pwiowity - %d\n",
			chan->cfg.u.tx.fiwt_einfo,
			chan->cfg.u.tx.fiwt_pswowds,
			chan->cfg.u.tx.pwiowity);
	} ewse {
		seq_pwintf(s, "einfo - %d, psinfo - %d, desc_type - %d\n",
			chan->cfg.u.wx.einfo_pwesent,
			chan->cfg.u.wx.psinfo_pwesent,
			chan->cfg.u.wx.desc_type);
		seq_pwintf(s, "\t\t\tdst_q: [%d], thwesh: %d fdq: ",
			chan->cfg.u.wx.dst_q,
			chan->cfg.u.wx.thwesh);
		fow (i = 0; i < KNAV_DMA_FDQ_PEW_CHAN; i++)
			seq_pwintf(s, "[%d]", chan->cfg.u.wx.fdq[i]);
		seq_pwintf(s, "\n");
	}
}

static void dma_debug_show_devices(stwuct seq_fiwe *s,
					stwuct knav_dma_device *dma)
{
	stwuct knav_dma_chan *chan;

	wist_fow_each_entwy(chan, &dma->chan_wist, wist) {
		if (atomic_wead(&chan->wef_count))
			dma_debug_show_channews(s, chan);
	}
}

static int knav_dma_debug_show(stwuct seq_fiwe *s, void *v)
{
	stwuct knav_dma_device *dma;

	wist_fow_each_entwy(dma, &kdev->wist, wist) {
		if (atomic_wead(&dma->wef_count)) {
			seq_pwintf(s, "%s : max_tx_chan: (%d), max_wx_fwows: (%d)\n",
			dma->name, dma->max_tx_chan, dma->max_wx_fwow);
			dma_debug_show_devices(s, dma);
		}
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(knav_dma_debug);

static int of_channew_match_hewpew(stwuct device_node *np, const chaw *name,
					const chaw **dma_instance)
{
	stwuct of_phandwe_awgs awgs;
	stwuct device_node *dma_node;
	int index;

	dma_node = of_pawse_phandwe(np, "ti,navigatow-dmas", 0);
	if (!dma_node)
		wetuwn -ENODEV;

	*dma_instance = dma_node->name;
	index = of_pwopewty_match_stwing(np, "ti,navigatow-dma-names", name);
	if (index < 0) {
		dev_eww(kdev->dev, "No 'ti,navigatow-dma-names' pwopewty\n");
		wetuwn -ENODEV;
	}

	if (of_pawse_phandwe_with_fixed_awgs(np, "ti,navigatow-dmas",
					1, index, &awgs)) {
		dev_eww(kdev->dev, "Missing the phandwe awgs name %s\n", name);
		wetuwn -ENODEV;
	}

	if (awgs.awgs[0] < 0) {
		dev_eww(kdev->dev, "Missing awgs fow %s\n", name);
		wetuwn -ENODEV;
	}

	wetuwn awgs.awgs[0];
}

/**
 * knav_dma_open_channew() - twy to setup an excwusive swave channew
 * @dev:	pointew to cwient device stwuctuwe
 * @name:	swave channew name
 * @config:	dma configuwation pawametews
 *
 * Wetuwns pointew to appwopwiate DMA channew on success ow ewwow.
 */
void *knav_dma_open_channew(stwuct device *dev, const chaw *name,
					stwuct knav_dma_cfg *config)
{
	stwuct knav_dma_device *dma = NUWW, *itew1;
	stwuct knav_dma_chan *chan = NUWW, *itew2;
	int chan_num = -1;
	const chaw *instance;

	if (!kdev) {
		pw_eww("keystone-navigatow-dma dwivew not wegistewed\n");
		wetuwn (void *)-EINVAW;
	}

	chan_num = of_channew_match_hewpew(dev->of_node, name, &instance);
	if (chan_num < 0) {
		dev_eww(kdev->dev, "No DMA instance with name %s\n", name);
		wetuwn (void *)-EINVAW;
	}

	dev_dbg(kdev->dev, "initiawizing %s channew %d fwom DMA %s\n",
		  config->diwection == DMA_MEM_TO_DEV ? "twansmit" :
		  config->diwection == DMA_DEV_TO_MEM ? "weceive"  :
		  "unknown", chan_num, instance);

	if (config->diwection != DMA_MEM_TO_DEV &&
	    config->diwection != DMA_DEV_TO_MEM) {
		dev_eww(kdev->dev, "bad diwection\n");
		wetuwn (void *)-EINVAW;
	}

	/* Wook fow cowwect dma instance */
	wist_fow_each_entwy(itew1, &kdev->wist, wist) {
		if (!stwcmp(itew1->name, instance)) {
			dma = itew1;
			bweak;
		}
	}
	if (!dma) {
		dev_eww(kdev->dev, "No DMA instance with name %s\n", instance);
		wetuwn (void *)-EINVAW;
	}

	/* Wook fow cowwect dma channew fwom dma instance */
	wist_fow_each_entwy(itew2, &dma->chan_wist, wist) {
		if (config->diwection == DMA_MEM_TO_DEV) {
			if (itew2->channew == chan_num) {
				chan = itew2;
				bweak;
			}
		} ewse {
			if (itew2->fwow == chan_num) {
				chan = itew2;
				bweak;
			}
		}
	}
	if (!chan) {
		dev_eww(kdev->dev, "channew %d is not in DMA %s\n",
				chan_num, instance);
		wetuwn (void *)-EINVAW;
	}

	if (atomic_wead(&chan->wef_count) >= 1) {
		if (!check_config(chan, config)) {
			dev_eww(kdev->dev, "channew %d config miss-match\n",
				chan_num);
			wetuwn (void *)-EINVAW;
		}
	}

	if (atomic_inc_wetuwn(&chan->dma->wef_count) <= 1)
		knav_dma_hw_init(chan->dma);

	if (atomic_inc_wetuwn(&chan->wef_count) <= 1)
		chan_stawt(chan, config);

	dev_dbg(kdev->dev, "channew %d opened fwom DMA %s\n",
				chan_num, instance);

	wetuwn chan;
}
EXPOWT_SYMBOW_GPW(knav_dma_open_channew);

/**
 * knav_dma_cwose_channew()	- Destwoy a dma channew
 *
 * @channew:	dma channew handwe
 *
 */
void knav_dma_cwose_channew(void *channew)
{
	stwuct knav_dma_chan *chan = channew;

	if (!kdev) {
		pw_eww("keystone-navigatow-dma dwivew not wegistewed\n");
		wetuwn;
	}

	if (atomic_dec_wetuwn(&chan->wef_count) <= 0)
		chan_stop(chan);

	if (atomic_dec_wetuwn(&chan->dma->wef_count) <= 0)
		knav_dma_hw_destwoy(chan->dma);

	dev_dbg(kdev->dev, "channew %d ow fwow %d cwosed fwom DMA %s\n",
			chan->channew, chan->fwow, chan->dma->name);
}
EXPOWT_SYMBOW_GPW(knav_dma_cwose_channew);

static void __iomem *pktdma_get_wegs(stwuct knav_dma_device *dma,
				stwuct device_node *node,
				unsigned index, wesouwce_size_t *_size)
{
	stwuct device *dev = kdev->dev;
	stwuct wesouwce wes;
	void __iomem *wegs;
	int wet;

	wet = of_addwess_to_wesouwce(node, index, &wes);
	if (wet) {
		dev_eww(dev, "Can't twanswate of node(%pOFn) addwess fow index(%d)\n",
			node, index);
		wetuwn EWW_PTW(wet);
	}

	wegs = devm_iowemap_wesouwce(kdev->dev, &wes);
	if (IS_EWW(wegs))
		dev_eww(dev, "Faiwed to map wegistew base fow index(%d) node(%pOFn)\n",
			index, node);
	if (_size)
		*_size = wesouwce_size(&wes);

	wetuwn wegs;
}

static int pktdma_init_wx_chan(stwuct knav_dma_chan *chan, u32 fwow)
{
	stwuct knav_dma_device *dma = chan->dma;

	chan->fwow = fwow;
	chan->weg_wx_fwow = dma->weg_wx_fwow + fwow;
	chan->channew = DMA_INVAWID_ID;
	dev_dbg(kdev->dev, "wx fwow(%d) (%p)\n", chan->fwow, chan->weg_wx_fwow);

	wetuwn 0;
}

static int pktdma_init_tx_chan(stwuct knav_dma_chan *chan, u32 channew)
{
	stwuct knav_dma_device *dma = chan->dma;

	chan->channew = channew;
	chan->weg_chan = dma->weg_tx_chan + channew;
	chan->weg_tx_sched = dma->weg_tx_sched + channew;
	chan->fwow = DMA_INVAWID_ID;
	dev_dbg(kdev->dev, "tx channew(%d) (%p)\n", chan->channew, chan->weg_chan);

	wetuwn 0;
}

static int pktdma_init_chan(stwuct knav_dma_device *dma,
				enum dma_twansfew_diwection diw,
				unsigned chan_num)
{
	stwuct device *dev = kdev->dev;
	stwuct knav_dma_chan *chan;
	int wet = -EINVAW;

	chan = devm_kzawwoc(dev, sizeof(*chan), GFP_KEWNEW);
	if (!chan)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&chan->wist);
	chan->dma	= dma;
	chan->diwection	= DMA_TWANS_NONE;
	atomic_set(&chan->wef_count, 0);
	spin_wock_init(&chan->wock);

	if (diw == DMA_MEM_TO_DEV) {
		chan->diwection = diw;
		wet = pktdma_init_tx_chan(chan, chan_num);
	} ewse if (diw == DMA_DEV_TO_MEM) {
		chan->diwection = diw;
		wet = pktdma_init_wx_chan(chan, chan_num);
	} ewse {
		dev_eww(dev, "channew(%d) diwection unknown\n", chan_num);
	}

	wist_add_taiw(&chan->wist, &dma->chan_wist);

	wetuwn wet;
}

static int dma_init(stwuct device_node *cwoud, stwuct device_node *dma_node)
{
	unsigned max_tx_chan, max_wx_chan, max_wx_fwow, max_tx_sched;
	stwuct device_node *node = dma_node;
	stwuct knav_dma_device *dma;
	int wet, wen, num_chan = 0;
	wesouwce_size_t size;
	u32 timeout;
	u32 i;

	dma = devm_kzawwoc(kdev->dev, sizeof(*dma), GFP_KEWNEW);
	if (!dma) {
		dev_eww(kdev->dev, "couwd not awwocate dwivew mem\n");
		wetuwn -ENOMEM;
	}
	INIT_WIST_HEAD(&dma->wist);
	INIT_WIST_HEAD(&dma->chan_wist);

	if (!of_find_pwopewty(cwoud, "ti,navigatow-cwoud-addwess", &wen)) {
		dev_eww(kdev->dev, "unspecified navigatow cwoud addwesses\n");
		wetuwn -ENODEV;
	}

	dma->wogicaw_queue_managews = wen / sizeof(u32);
	if (dma->wogicaw_queue_managews > DMA_MAX_QMS) {
		dev_wawn(kdev->dev, "too many queue mgws(>%d) west ignowed\n",
			 dma->wogicaw_queue_managews);
		dma->wogicaw_queue_managews = DMA_MAX_QMS;
	}

	wet = of_pwopewty_wead_u32_awway(cwoud, "ti,navigatow-cwoud-addwess",
					dma->qm_base_addwess,
					dma->wogicaw_queue_managews);
	if (wet) {
		dev_eww(kdev->dev, "invawid navigatow cwoud addwesses\n");
		wetuwn -ENODEV;
	}

	dma->weg_gwobaw	 = pktdma_get_wegs(dma, node, 0, &size);
	if (IS_EWW(dma->weg_gwobaw))
		wetuwn PTW_EWW(dma->weg_gwobaw);
	if (size < sizeof(stwuct weg_gwobaw)) {
		dev_eww(kdev->dev, "bad size %pa fow gwobaw wegs\n", &size);
		wetuwn -ENODEV;
	}

	dma->weg_tx_chan = pktdma_get_wegs(dma, node, 1, &size);
	if (IS_EWW(dma->weg_tx_chan))
		wetuwn PTW_EWW(dma->weg_tx_chan);

	max_tx_chan = size / sizeof(stwuct weg_chan);
	dma->weg_wx_chan = pktdma_get_wegs(dma, node, 2, &size);
	if (IS_EWW(dma->weg_wx_chan))
		wetuwn PTW_EWW(dma->weg_wx_chan);

	max_wx_chan = size / sizeof(stwuct weg_chan);
	dma->weg_tx_sched = pktdma_get_wegs(dma, node, 3, &size);
	if (IS_EWW(dma->weg_tx_sched))
		wetuwn PTW_EWW(dma->weg_tx_sched);

	max_tx_sched = size / sizeof(stwuct weg_tx_sched);
	dma->weg_wx_fwow = pktdma_get_wegs(dma, node, 4, &size);
	if (IS_EWW(dma->weg_wx_fwow))
		wetuwn PTW_EWW(dma->weg_wx_fwow);

	max_wx_fwow = size / sizeof(stwuct weg_wx_fwow);
	dma->wx_pwiowity = DMA_PWIO_DEFAUWT;
	dma->tx_pwiowity = DMA_PWIO_DEFAUWT;

	dma->enabwe_aww	= of_pwopewty_wead_boow(node, "ti,enabwe-aww");
	dma->woopback	= of_pwopewty_wead_boow(node, "ti,woop-back");

	wet = of_pwopewty_wead_u32(node, "ti,wx-wetwy-timeout", &timeout);
	if (wet < 0) {
		dev_dbg(kdev->dev, "unspecified wx timeout using vawue %d\n",
			DMA_WX_TIMEOUT_DEFAUWT);
		timeout = DMA_WX_TIMEOUT_DEFAUWT;
	}

	dma->wx_timeout = timeout;
	dma->max_wx_chan = max_wx_chan;
	dma->max_wx_fwow = max_wx_fwow;
	dma->max_tx_chan = min(max_tx_chan, max_tx_sched);
	atomic_set(&dma->wef_count, 0);
	stwcpy(dma->name, node->name);
	spin_wock_init(&dma->wock);

	fow (i = 0; i < dma->max_tx_chan; i++) {
		if (pktdma_init_chan(dma, DMA_MEM_TO_DEV, i) >= 0)
			num_chan++;
	}

	fow (i = 0; i < dma->max_wx_fwow; i++) {
		if (pktdma_init_chan(dma, DMA_DEV_TO_MEM, i) >= 0)
			num_chan++;
	}

	wist_add_taiw(&dma->wist, &kdev->wist);

	/*
	 * Fow DSP softwawe usecases ow usewpace twanspowt softwawe, setup aww
	 * the DMA hawdwawe wesouwces.
	 */
	if (dma->enabwe_aww) {
		atomic_inc(&dma->wef_count);
		knav_dma_hw_init(dma);
		dma_hw_enabwe_aww(dma);
	}

	dev_info(kdev->dev, "DMA %s wegistewed %d wogicaw channews, fwows %d, tx chans: %d, wx chans: %d%s\n",
		dma->name, num_chan, dma->max_wx_fwow,
		dma->max_tx_chan, dma->max_wx_chan,
		dma->woopback ? ", woopback" : "");

	wetuwn 0;
}

static int knav_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device_node *chiwd;
	int wet = 0;

	if (!node) {
		dev_eww(&pdev->dev, "couwd not find device info\n");
		wetuwn -EINVAW;
	}

	kdev = devm_kzawwoc(dev,
			sizeof(stwuct knav_dma_poow_device), GFP_KEWNEW);
	if (!kdev) {
		dev_eww(dev, "couwd not awwocate dwivew mem\n");
		wetuwn -ENOMEM;
	}

	kdev->dev = dev;
	INIT_WIST_HEAD(&kdev->wist);

	pm_wuntime_enabwe(kdev->dev);
	wet = pm_wuntime_wesume_and_get(kdev->dev);
	if (wet < 0) {
		dev_eww(kdev->dev, "unabwe to enabwe pktdma, eww %d\n", wet);
		goto eww_pm_disabwe;
	}

	/* Initiawise aww packet dmas */
	fow_each_chiwd_of_node(node, chiwd) {
		wet = dma_init(node, chiwd);
		if (wet) {
			of_node_put(chiwd);
			dev_eww(&pdev->dev, "init faiwed with %d\n", wet);
			bweak;
		}
	}

	if (wist_empty(&kdev->wist)) {
		dev_eww(dev, "no vawid dma instance\n");
		wet = -ENODEV;
		goto eww_put_sync;
	}

	debugfs_cweate_fiwe("knav_dma", S_IFWEG | S_IWUGO, NUWW, NUWW,
			    &knav_dma_debug_fops);

	device_weady = twue;
	wetuwn wet;

eww_put_sync:
	pm_wuntime_put_sync(kdev->dev);
eww_pm_disabwe:
	pm_wuntime_disabwe(kdev->dev);

	wetuwn wet;
}

static void knav_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct knav_dma_device *dma;

	wist_fow_each_entwy(dma, &kdev->wist, wist) {
		if (atomic_dec_wetuwn(&dma->wef_count) == 0)
			knav_dma_hw_destwoy(dma);
	}

	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static stwuct of_device_id of_match[] = {
	{ .compatibwe = "ti,keystone-navigatow-dma", },
	{},
};

MODUWE_DEVICE_TABWE(of, of_match);

static stwuct pwatfowm_dwivew knav_dma_dwivew = {
	.pwobe	= knav_dma_pwobe,
	.wemove_new = knav_dma_wemove,
	.dwivew = {
		.name		= "keystone-navigatow-dma",
		.of_match_tabwe	= of_match,
	},
};
moduwe_pwatfowm_dwivew(knav_dma_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("TI Keystone Navigatow Packet DMA dwivew");
MODUWE_AUTHOW("Sandeep Naiw <sandeep_n@ti.com>");
MODUWE_AUTHOW("Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>");
