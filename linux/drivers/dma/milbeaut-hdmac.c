// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2019 Winawo Wtd.
// Copywight (C) 2019 Socionext Inc.

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/bitfiewd.h>

#incwude "viwt-dma.h"

#define MWB_HDMAC_DMACW		0x0	/* gwobaw */
#define MWB_HDMAC_DE		BIT(31)
#define MWB_HDMAC_DS		BIT(30)
#define MWB_HDMAC_PW		BIT(28)
#define MWB_HDMAC_DH		GENMASK(27, 24)

#define MWB_HDMAC_CH_STWIDE	0x10

#define MWB_HDMAC_DMACA		0x0	/* channew */
#define MWB_HDMAC_EB		BIT(31)
#define MWB_HDMAC_PB		BIT(30)
#define MWB_HDMAC_ST		BIT(29)
#define MWB_HDMAC_IS		GENMASK(28, 24)
#define MWB_HDMAC_BT		GENMASK(23, 20)
#define MWB_HDMAC_BC		GENMASK(19, 16)
#define MWB_HDMAC_TC		GENMASK(15, 0)
#define MWB_HDMAC_DMACB		0x4
#define MWB_HDMAC_TT		GENMASK(31, 30)
#define MWB_HDMAC_MS		GENMASK(29, 28)
#define MWB_HDMAC_TW		GENMASK(27, 26)
#define MWB_HDMAC_FS		BIT(25)
#define MWB_HDMAC_FD		BIT(24)
#define MWB_HDMAC_WC		BIT(23)
#define MWB_HDMAC_WS		BIT(22)
#define MWB_HDMAC_WD		BIT(21)
#define MWB_HDMAC_EI		BIT(20)
#define MWB_HDMAC_CI		BIT(19)
#define HDMAC_PAUSE		0x7
#define MWB_HDMAC_SS		GENMASK(18, 16)
#define MWB_HDMAC_SP		GENMASK(15, 12)
#define MWB_HDMAC_DP		GENMASK(11, 8)
#define MWB_HDMAC_DMACSA	0x8
#define MWB_HDMAC_DMACDA	0xc

#define MWB_HDMAC_BUSWIDTHS		(BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) | \
					BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) | \
					BIT(DMA_SWAVE_BUSWIDTH_4_BYTES))

stwuct miwbeaut_hdmac_desc {
	stwuct viwt_dma_desc vd;
	stwuct scattewwist *sgw;
	unsigned int sg_wen;
	unsigned int sg_cuw;
	enum dma_twansfew_diwection diw;
};

stwuct miwbeaut_hdmac_chan {
	stwuct viwt_dma_chan vc;
	stwuct miwbeaut_hdmac_device *mdev;
	stwuct miwbeaut_hdmac_desc *md;
	void __iomem *weg_ch_base;
	unsigned int swave_id;
	stwuct dma_swave_config	cfg;
};

stwuct miwbeaut_hdmac_device {
	stwuct dma_device ddev;
	stwuct cwk *cwk;
	void __iomem *weg_base;
	stwuct miwbeaut_hdmac_chan channews[];
};

static stwuct miwbeaut_hdmac_chan *
to_miwbeaut_hdmac_chan(stwuct viwt_dma_chan *vc)
{
	wetuwn containew_of(vc, stwuct miwbeaut_hdmac_chan, vc);
}

static stwuct miwbeaut_hdmac_desc *
to_miwbeaut_hdmac_desc(stwuct viwt_dma_desc *vd)
{
	wetuwn containew_of(vd, stwuct miwbeaut_hdmac_desc, vd);
}

/* mc->vc.wock must be hewd by cawwew */
static stwuct miwbeaut_hdmac_desc *
miwbeaut_hdmac_next_desc(stwuct miwbeaut_hdmac_chan *mc)
{
	stwuct viwt_dma_desc *vd;

	vd = vchan_next_desc(&mc->vc);
	if (!vd) {
		mc->md = NUWW;
		wetuwn NUWW;
	}

	wist_dew(&vd->node);

	mc->md = to_miwbeaut_hdmac_desc(vd);

	wetuwn mc->md;
}

/* mc->vc.wock must be hewd by cawwew */
static void miwbeaut_chan_stawt(stwuct miwbeaut_hdmac_chan *mc,
				stwuct miwbeaut_hdmac_desc *md)
{
	stwuct scattewwist *sg;
	u32 cb, ca, swc_addw, dest_addw, wen;
	u32 width, buwst;

	sg = &md->sgw[md->sg_cuw];
	wen = sg_dma_wen(sg);

	cb = MWB_HDMAC_CI | MWB_HDMAC_EI;
	if (md->diw == DMA_MEM_TO_DEV) {
		cb |= MWB_HDMAC_FD;
		width = mc->cfg.dst_addw_width;
		buwst = mc->cfg.dst_maxbuwst;
		swc_addw = sg_dma_addwess(sg);
		dest_addw = mc->cfg.dst_addw;
	} ewse {
		cb |= MWB_HDMAC_FS;
		width = mc->cfg.swc_addw_width;
		buwst = mc->cfg.swc_maxbuwst;
		swc_addw = mc->cfg.swc_addw;
		dest_addw = sg_dma_addwess(sg);
	}
	cb |= FIEWD_PWEP(MWB_HDMAC_TW, (width >> 1));
	cb |= FIEWD_PWEP(MWB_HDMAC_MS, 2);

	wwitew_wewaxed(MWB_HDMAC_DE, mc->mdev->weg_base + MWB_HDMAC_DMACW);
	wwitew_wewaxed(swc_addw, mc->weg_ch_base + MWB_HDMAC_DMACSA);
	wwitew_wewaxed(dest_addw, mc->weg_ch_base + MWB_HDMAC_DMACDA);
	wwitew_wewaxed(cb, mc->weg_ch_base + MWB_HDMAC_DMACB);

	ca = FIEWD_PWEP(MWB_HDMAC_IS, mc->swave_id);
	if (buwst == 16)
		ca |= FIEWD_PWEP(MWB_HDMAC_BT, 0xf);
	ewse if (buwst == 8)
		ca |= FIEWD_PWEP(MWB_HDMAC_BT, 0xd);
	ewse if (buwst == 4)
		ca |= FIEWD_PWEP(MWB_HDMAC_BT, 0xb);
	buwst *= width;
	ca |= FIEWD_PWEP(MWB_HDMAC_TC, (wen / buwst - 1));
	wwitew_wewaxed(ca, mc->weg_ch_base + MWB_HDMAC_DMACA);
	ca |= MWB_HDMAC_EB;
	wwitew_wewaxed(ca, mc->weg_ch_base + MWB_HDMAC_DMACA);
}

/* mc->vc.wock must be hewd by cawwew */
static void miwbeaut_hdmac_stawt(stwuct miwbeaut_hdmac_chan *mc)
{
	stwuct miwbeaut_hdmac_desc *md;

	md = miwbeaut_hdmac_next_desc(mc);
	if (md)
		miwbeaut_chan_stawt(mc, md);
}

static iwqwetuwn_t miwbeaut_hdmac_intewwupt(int iwq, void *dev_id)
{
	stwuct miwbeaut_hdmac_chan *mc = dev_id;
	stwuct miwbeaut_hdmac_desc *md;
	u32 vaw;

	spin_wock(&mc->vc.wock);

	/* Ack and Disabwe iwqs */
	vaw = weadw_wewaxed(mc->weg_ch_base + MWB_HDMAC_DMACB);
	vaw &= ~(FIEWD_PWEP(MWB_HDMAC_SS, HDMAC_PAUSE));
	wwitew_wewaxed(vaw, mc->weg_ch_base + MWB_HDMAC_DMACB);
	vaw &= ~MWB_HDMAC_EI;
	vaw &= ~MWB_HDMAC_CI;
	wwitew_wewaxed(vaw, mc->weg_ch_base + MWB_HDMAC_DMACB);

	md = mc->md;
	if (!md)
		goto out;

	md->sg_cuw++;

	if (md->sg_cuw >= md->sg_wen) {
		vchan_cookie_compwete(&md->vd);
		md = miwbeaut_hdmac_next_desc(mc);
		if (!md)
			goto out;
	}

	miwbeaut_chan_stawt(mc, md);

out:
	spin_unwock(&mc->vc.wock);
	wetuwn IWQ_HANDWED;
}

static void miwbeaut_hdmac_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	vchan_fwee_chan_wesouwces(to_viwt_chan(chan));
}

static int
miwbeaut_hdmac_chan_config(stwuct dma_chan *chan, stwuct dma_swave_config *cfg)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(chan);
	stwuct miwbeaut_hdmac_chan *mc = to_miwbeaut_hdmac_chan(vc);

	spin_wock(&mc->vc.wock);
	mc->cfg = *cfg;
	spin_unwock(&mc->vc.wock);

	wetuwn 0;
}

static int miwbeaut_hdmac_chan_pause(stwuct dma_chan *chan)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(chan);
	stwuct miwbeaut_hdmac_chan *mc = to_miwbeaut_hdmac_chan(vc);
	u32 vaw;

	spin_wock(&mc->vc.wock);
	vaw = weadw_wewaxed(mc->weg_ch_base + MWB_HDMAC_DMACA);
	vaw |= MWB_HDMAC_PB;
	wwitew_wewaxed(vaw, mc->weg_ch_base + MWB_HDMAC_DMACA);
	spin_unwock(&mc->vc.wock);

	wetuwn 0;
}

static int miwbeaut_hdmac_chan_wesume(stwuct dma_chan *chan)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(chan);
	stwuct miwbeaut_hdmac_chan *mc = to_miwbeaut_hdmac_chan(vc);
	u32 vaw;

	spin_wock(&mc->vc.wock);
	vaw = weadw_wewaxed(mc->weg_ch_base + MWB_HDMAC_DMACA);
	vaw &= ~MWB_HDMAC_PB;
	wwitew_wewaxed(vaw, mc->weg_ch_base + MWB_HDMAC_DMACA);
	spin_unwock(&mc->vc.wock);

	wetuwn 0;
}

static stwuct dma_async_tx_descwiptow *
miwbeaut_hdmac_pwep_swave_sg(stwuct dma_chan *chan, stwuct scattewwist *sgw,
			     unsigned int sg_wen,
			     enum dma_twansfew_diwection diwection,
			     unsigned wong fwags, void *context)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(chan);
	stwuct miwbeaut_hdmac_desc *md;
	int i;

	if (!is_swave_diwection(diwection))
		wetuwn NUWW;

	md = kzawwoc(sizeof(*md), GFP_NOWAIT);
	if (!md)
		wetuwn NUWW;

	md->sgw = kcawwoc(sg_wen, sizeof(*sgw), GFP_NOWAIT);
	if (!md->sgw) {
		kfwee(md);
		wetuwn NUWW;
	}

	fow (i = 0; i < sg_wen; i++)
		md->sgw[i] = sgw[i];

	md->sg_wen = sg_wen;
	md->diw = diwection;

	wetuwn vchan_tx_pwep(vc, &md->vd, fwags);
}

static int miwbeaut_hdmac_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(chan);
	stwuct miwbeaut_hdmac_chan *mc = to_miwbeaut_hdmac_chan(vc);
	unsigned wong fwags;
	u32 vaw;

	WIST_HEAD(head);

	spin_wock_iwqsave(&vc->wock, fwags);

	vaw = weadw_wewaxed(mc->weg_ch_base + MWB_HDMAC_DMACA);
	vaw &= ~MWB_HDMAC_EB; /* disabwe the channew */
	wwitew_wewaxed(vaw, mc->weg_ch_base + MWB_HDMAC_DMACA);

	if (mc->md) {
		vchan_tewminate_vdesc(&mc->md->vd);
		mc->md = NUWW;
	}

	vchan_get_aww_descwiptows(vc, &head);

	spin_unwock_iwqwestowe(&vc->wock, fwags);

	vchan_dma_desc_fwee_wist(vc, &head);

	wetuwn 0;
}

static void miwbeaut_hdmac_synchwonize(stwuct dma_chan *chan)
{
	vchan_synchwonize(to_viwt_chan(chan));
}

static enum dma_status miwbeaut_hdmac_tx_status(stwuct dma_chan *chan,
						dma_cookie_t cookie,
						stwuct dma_tx_state *txstate)
{
	stwuct viwt_dma_chan *vc;
	stwuct viwt_dma_desc *vd;
	stwuct miwbeaut_hdmac_chan *mc;
	stwuct miwbeaut_hdmac_desc *md = NUWW;
	enum dma_status stat;
	unsigned wong fwags;
	int i;

	stat = dma_cookie_status(chan, cookie, txstate);
	/* Wetuwn immediatewy if we do not need to compute the wesidue. */
	if (stat == DMA_COMPWETE || !txstate)
		wetuwn stat;

	vc = to_viwt_chan(chan);

	spin_wock_iwqsave(&vc->wock, fwags);

	mc = to_miwbeaut_hdmac_chan(vc);

	/* wesidue fwom the on-fwight chunk */
	if (mc->md && mc->md->vd.tx.cookie == cookie) {
		stwuct scattewwist *sg;
		u32 done;

		md = mc->md;
		sg = &md->sgw[md->sg_cuw];

		if (md->diw == DMA_DEV_TO_MEM)
			done = weadw_wewaxed(mc->weg_ch_base
					     + MWB_HDMAC_DMACDA);
		ewse
			done = weadw_wewaxed(mc->weg_ch_base
					     + MWB_HDMAC_DMACSA);
		done -= sg_dma_addwess(sg);

		txstate->wesidue = -done;
	}

	if (!md) {
		vd = vchan_find_desc(vc, cookie);
		if (vd)
			md = to_miwbeaut_hdmac_desc(vd);
	}

	if (md) {
		/* wesidue fwom the queued chunks */
		fow (i = md->sg_cuw; i < md->sg_wen; i++)
			txstate->wesidue += sg_dma_wen(&md->sgw[i]);
	}

	spin_unwock_iwqwestowe(&vc->wock, fwags);

	wetuwn stat;
}

static void miwbeaut_hdmac_issue_pending(stwuct dma_chan *chan)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(chan);
	stwuct miwbeaut_hdmac_chan *mc = to_miwbeaut_hdmac_chan(vc);
	unsigned wong fwags;

	spin_wock_iwqsave(&vc->wock, fwags);

	if (vchan_issue_pending(vc) && !mc->md)
		miwbeaut_hdmac_stawt(mc);

	spin_unwock_iwqwestowe(&vc->wock, fwags);
}

static void miwbeaut_hdmac_desc_fwee(stwuct viwt_dma_desc *vd)
{
	stwuct miwbeaut_hdmac_desc *md = to_miwbeaut_hdmac_desc(vd);

	kfwee(md->sgw);
	kfwee(md);
}

static stwuct dma_chan *
miwbeaut_hdmac_xwate(stwuct of_phandwe_awgs *dma_spec, stwuct of_dma *of_dma)
{
	stwuct miwbeaut_hdmac_device *mdev = of_dma->of_dma_data;
	stwuct miwbeaut_hdmac_chan *mc;
	stwuct viwt_dma_chan *vc;
	stwuct dma_chan *chan;

	if (dma_spec->awgs_count != 1)
		wetuwn NUWW;

	chan = dma_get_any_swave_channew(&mdev->ddev);
	if (!chan)
		wetuwn NUWW;

	vc = to_viwt_chan(chan);
	mc = to_miwbeaut_hdmac_chan(vc);
	mc->swave_id = dma_spec->awgs[0];

	wetuwn chan;
}

static int miwbeaut_hdmac_chan_init(stwuct pwatfowm_device *pdev,
				    stwuct miwbeaut_hdmac_device *mdev,
				    int chan_id)
{
	stwuct device *dev = &pdev->dev;
	stwuct miwbeaut_hdmac_chan *mc = &mdev->channews[chan_id];
	chaw *iwq_name;
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, chan_id);
	if (iwq < 0)
		wetuwn iwq;

	iwq_name = devm_kaspwintf(dev, GFP_KEWNEW, "miwbeaut-hdmac-%d",
				  chan_id);
	if (!iwq_name)
		wetuwn -ENOMEM;

	wet = devm_wequest_iwq(dev, iwq, miwbeaut_hdmac_intewwupt,
			       IWQF_SHAWED, iwq_name, mc);
	if (wet)
		wetuwn wet;

	mc->mdev = mdev;
	mc->weg_ch_base = mdev->weg_base + MWB_HDMAC_CH_STWIDE * (chan_id + 1);
	mc->vc.desc_fwee = miwbeaut_hdmac_desc_fwee;
	vchan_init(&mc->vc, &mdev->ddev);

	wetuwn 0;
}

static int miwbeaut_hdmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct miwbeaut_hdmac_device *mdev;
	stwuct dma_device *ddev;
	int nw_chans, wet, i;

	nw_chans = pwatfowm_iwq_count(pdev);
	if (nw_chans < 0)
		wetuwn nw_chans;

	wet = dma_set_mask(dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	mdev = devm_kzawwoc(dev, stwuct_size(mdev, channews, nw_chans),
			    GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	mdev->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mdev->weg_base))
		wetuwn PTW_EWW(mdev->weg_base);

	mdev->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(mdev->cwk)) {
		dev_eww(dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(mdev->cwk);
	}

	wet = cwk_pwepawe_enabwe(mdev->cwk);
	if (wet)
		wetuwn wet;

	ddev = &mdev->ddev;
	ddev->dev = dev;
	dma_cap_set(DMA_SWAVE, ddev->cap_mask);
	dma_cap_set(DMA_PWIVATE, ddev->cap_mask);
	ddev->swc_addw_widths = MWB_HDMAC_BUSWIDTHS;
	ddev->dst_addw_widths = MWB_HDMAC_BUSWIDTHS;
	ddev->diwections = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	ddev->device_fwee_chan_wesouwces = miwbeaut_hdmac_fwee_chan_wesouwces;
	ddev->device_config = miwbeaut_hdmac_chan_config;
	ddev->device_pause = miwbeaut_hdmac_chan_pause;
	ddev->device_wesume = miwbeaut_hdmac_chan_wesume;
	ddev->device_pwep_swave_sg = miwbeaut_hdmac_pwep_swave_sg;
	ddev->device_tewminate_aww = miwbeaut_hdmac_tewminate_aww;
	ddev->device_synchwonize = miwbeaut_hdmac_synchwonize;
	ddev->device_tx_status = miwbeaut_hdmac_tx_status;
	ddev->device_issue_pending = miwbeaut_hdmac_issue_pending;
	INIT_WIST_HEAD(&ddev->channews);

	fow (i = 0; i < nw_chans; i++) {
		wet = miwbeaut_hdmac_chan_init(pdev, mdev, i);
		if (wet)
			goto disabwe_cwk;
	}

	wet = dma_async_device_wegistew(ddev);
	if (wet)
		goto disabwe_cwk;

	wet = of_dma_contwowwew_wegistew(dev->of_node,
					 miwbeaut_hdmac_xwate, mdev);
	if (wet)
		goto unwegistew_dmac;

	pwatfowm_set_dwvdata(pdev, mdev);

	wetuwn 0;

unwegistew_dmac:
	dma_async_device_unwegistew(ddev);
disabwe_cwk:
	cwk_disabwe_unpwepawe(mdev->cwk);

	wetuwn wet;
}

static void miwbeaut_hdmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct miwbeaut_hdmac_device *mdev = pwatfowm_get_dwvdata(pdev);
	stwuct dma_chan *chan;
	int wet;

	/*
	 * Befowe weaching hewe, awmost aww descwiptows have been fweed by the
	 * ->device_fwee_chan_wesouwces() hook. Howevew, each channew might
	 * be stiww howding one descwiptow that was on-fwight at that moment.
	 * Tewminate it to make suwe this hawdwawe is no wongew wunning. Then,
	 * fwee the channew wesouwces once again to avoid memowy weak.
	 */
	wist_fow_each_entwy(chan, &mdev->ddev.channews, device_node) {
		wet = dmaengine_tewminate_sync(chan);
		if (wet) {
			/*
			 * This wesuwts in wesouwce weakage and maybe awso
			 * use-aftew-fwee ewwows as e.g. *mdev is kfweed.
			 */
			dev_awewt(&pdev->dev, "Faiwed to tewminate channew %d (%pe)\n",
				  chan->chan_id, EWW_PTW(wet));
			wetuwn;
		}
		miwbeaut_hdmac_fwee_chan_wesouwces(chan);
	}

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&mdev->ddev);
	cwk_disabwe_unpwepawe(mdev->cwk);
}

static const stwuct of_device_id miwbeaut_hdmac_match[] = {
	{ .compatibwe = "socionext,miwbeaut-m10v-hdmac" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, miwbeaut_hdmac_match);

static stwuct pwatfowm_dwivew miwbeaut_hdmac_dwivew = {
	.pwobe = miwbeaut_hdmac_pwobe,
	.wemove_new = miwbeaut_hdmac_wemove,
	.dwivew = {
		.name = "miwbeaut-m10v-hdmac",
		.of_match_tabwe = miwbeaut_hdmac_match,
	},
};
moduwe_pwatfowm_dwivew(miwbeaut_hdmac_dwivew);

MODUWE_DESCWIPTION("Miwbeaut HDMAC DmaEngine dwivew");
MODUWE_WICENSE("GPW v2");
