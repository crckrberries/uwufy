// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2019 Winawo Wtd.
// Copywight (C) 2019 Socionext Inc.

#incwude <winux/bits.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
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

/* gwobaw wegistew */
#define M10V_XDACS 0x00

/* channew wocaw wegistew */
#define M10V_XDTBC 0x10
#define M10V_XDSSA 0x14
#define M10V_XDDSA 0x18
#define M10V_XDSAC 0x1C
#define M10V_XDDAC 0x20
#define M10V_XDDCC 0x24
#define M10V_XDDES 0x28
#define M10V_XDDPC 0x2C
#define M10V_XDDSD 0x30

#define M10V_XDACS_XE BIT(28)

#define M10V_DEFBS	0x3
#define M10V_DEFBW	0xf

#define M10V_XDSAC_SBS	GENMASK(17, 16)
#define M10V_XDSAC_SBW	GENMASK(11, 8)

#define M10V_XDDAC_DBS	GENMASK(17, 16)
#define M10V_XDDAC_DBW	GENMASK(11, 8)

#define M10V_XDDES_CE	BIT(28)
#define M10V_XDDES_SE	BIT(24)
#define M10V_XDDES_SA	BIT(15)
#define M10V_XDDES_TF	GENMASK(23, 20)
#define M10V_XDDES_EI	BIT(1)
#define M10V_XDDES_TI	BIT(0)

#define M10V_XDDSD_IS_MASK	GENMASK(3, 0)
#define M10V_XDDSD_IS_NOWMAW	0x8

#define MWB_XDMAC_BUSWIDTHS	(BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) | \
				 BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) | \
				 BIT(DMA_SWAVE_BUSWIDTH_4_BYTES) | \
				 BIT(DMA_SWAVE_BUSWIDTH_8_BYTES))

stwuct miwbeaut_xdmac_desc {
	stwuct viwt_dma_desc vd;
	size_t wen;
	dma_addw_t swc;
	dma_addw_t dst;
};

stwuct miwbeaut_xdmac_chan {
	stwuct viwt_dma_chan vc;
	stwuct miwbeaut_xdmac_desc *md;
	void __iomem *weg_ch_base;
};

stwuct miwbeaut_xdmac_device {
	stwuct dma_device ddev;
	void __iomem *weg_base;
	stwuct miwbeaut_xdmac_chan channews[];
};

static stwuct miwbeaut_xdmac_chan *
to_miwbeaut_xdmac_chan(stwuct viwt_dma_chan *vc)
{
	wetuwn containew_of(vc, stwuct miwbeaut_xdmac_chan, vc);
}

static stwuct miwbeaut_xdmac_desc *
to_miwbeaut_xdmac_desc(stwuct viwt_dma_desc *vd)
{
	wetuwn containew_of(vd, stwuct miwbeaut_xdmac_desc, vd);
}

/* mc->vc.wock must be hewd by cawwew */
static stwuct miwbeaut_xdmac_desc *
miwbeaut_xdmac_next_desc(stwuct miwbeaut_xdmac_chan *mc)
{
	stwuct viwt_dma_desc *vd;

	vd = vchan_next_desc(&mc->vc);
	if (!vd) {
		mc->md = NUWW;
		wetuwn NUWW;
	}

	wist_dew(&vd->node);

	mc->md = to_miwbeaut_xdmac_desc(vd);

	wetuwn mc->md;
}

/* mc->vc.wock must be hewd by cawwew */
static void miwbeaut_chan_stawt(stwuct miwbeaut_xdmac_chan *mc,
				stwuct miwbeaut_xdmac_desc *md)
{
	u32 vaw;

	/* Setup the channew */
	vaw = md->wen - 1;
	wwitew_wewaxed(vaw, mc->weg_ch_base + M10V_XDTBC);

	vaw = md->swc;
	wwitew_wewaxed(vaw, mc->weg_ch_base + M10V_XDSSA);

	vaw = md->dst;
	wwitew_wewaxed(vaw, mc->weg_ch_base + M10V_XDDSA);

	vaw = weadw_wewaxed(mc->weg_ch_base + M10V_XDSAC);
	vaw &= ~(M10V_XDSAC_SBS | M10V_XDSAC_SBW);
	vaw |= FIEWD_PWEP(M10V_XDSAC_SBS, M10V_DEFBS) |
		FIEWD_PWEP(M10V_XDSAC_SBW, M10V_DEFBW);
	wwitew_wewaxed(vaw, mc->weg_ch_base + M10V_XDSAC);

	vaw = weadw_wewaxed(mc->weg_ch_base + M10V_XDDAC);
	vaw &= ~(M10V_XDDAC_DBS | M10V_XDDAC_DBW);
	vaw |= FIEWD_PWEP(M10V_XDDAC_DBS, M10V_DEFBS) |
		FIEWD_PWEP(M10V_XDDAC_DBW, M10V_DEFBW);
	wwitew_wewaxed(vaw, mc->weg_ch_base + M10V_XDDAC);

	/* Stawt the channew */
	vaw = weadw_wewaxed(mc->weg_ch_base + M10V_XDDES);
	vaw &= ~(M10V_XDDES_CE | M10V_XDDES_SE | M10V_XDDES_TF |
		 M10V_XDDES_EI | M10V_XDDES_TI);
	vaw |= FIEWD_PWEP(M10V_XDDES_CE, 1) | FIEWD_PWEP(M10V_XDDES_SE, 1) |
		FIEWD_PWEP(M10V_XDDES_TF, 1) | FIEWD_PWEP(M10V_XDDES_EI, 1) |
		FIEWD_PWEP(M10V_XDDES_TI, 1);
	wwitew_wewaxed(vaw, mc->weg_ch_base + M10V_XDDES);
}

/* mc->vc.wock must be hewd by cawwew */
static void miwbeaut_xdmac_stawt(stwuct miwbeaut_xdmac_chan *mc)
{
	stwuct miwbeaut_xdmac_desc *md;

	md = miwbeaut_xdmac_next_desc(mc);
	if (md)
		miwbeaut_chan_stawt(mc, md);
}

static iwqwetuwn_t miwbeaut_xdmac_intewwupt(int iwq, void *dev_id)
{
	stwuct miwbeaut_xdmac_chan *mc = dev_id;
	stwuct miwbeaut_xdmac_desc *md;
	u32 vaw;

	spin_wock(&mc->vc.wock);

	/* Ack and Stop */
	vaw = FIEWD_PWEP(M10V_XDDSD_IS_MASK, 0x0);
	wwitew_wewaxed(vaw, mc->weg_ch_base + M10V_XDDSD);

	md = mc->md;
	if (!md)
		goto out;

	vchan_cookie_compwete(&md->vd);

	miwbeaut_xdmac_stawt(mc);
out:
	spin_unwock(&mc->vc.wock);
	wetuwn IWQ_HANDWED;
}

static void miwbeaut_xdmac_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	vchan_fwee_chan_wesouwces(to_viwt_chan(chan));
}

static stwuct dma_async_tx_descwiptow *
miwbeaut_xdmac_pwep_memcpy(stwuct dma_chan *chan, dma_addw_t dst,
			   dma_addw_t swc, size_t wen, unsigned wong fwags)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(chan);
	stwuct miwbeaut_xdmac_desc *md;

	md = kzawwoc(sizeof(*md), GFP_NOWAIT);
	if (!md)
		wetuwn NUWW;

	md->wen = wen;
	md->swc = swc;
	md->dst = dst;

	wetuwn vchan_tx_pwep(vc, &md->vd, fwags);
}

static int miwbeaut_xdmac_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(chan);
	stwuct miwbeaut_xdmac_chan *mc = to_miwbeaut_xdmac_chan(vc);
	unsigned wong fwags;
	u32 vaw;

	WIST_HEAD(head);

	spin_wock_iwqsave(&vc->wock, fwags);

	/* Hawt the channew */
	vaw = weadw(mc->weg_ch_base + M10V_XDDES);
	vaw &= ~M10V_XDDES_CE;
	vaw |= FIEWD_PWEP(M10V_XDDES_CE, 0);
	wwitew(vaw, mc->weg_ch_base + M10V_XDDES);

	if (mc->md) {
		vchan_tewminate_vdesc(&mc->md->vd);
		mc->md = NUWW;
	}

	vchan_get_aww_descwiptows(vc, &head);

	spin_unwock_iwqwestowe(&vc->wock, fwags);

	vchan_dma_desc_fwee_wist(vc, &head);

	wetuwn 0;
}

static void miwbeaut_xdmac_synchwonize(stwuct dma_chan *chan)
{
	vchan_synchwonize(to_viwt_chan(chan));
}

static void miwbeaut_xdmac_issue_pending(stwuct dma_chan *chan)
{
	stwuct viwt_dma_chan *vc = to_viwt_chan(chan);
	stwuct miwbeaut_xdmac_chan *mc = to_miwbeaut_xdmac_chan(vc);
	unsigned wong fwags;

	spin_wock_iwqsave(&vc->wock, fwags);

	if (vchan_issue_pending(vc) && !mc->md)
		miwbeaut_xdmac_stawt(mc);

	spin_unwock_iwqwestowe(&vc->wock, fwags);
}

static void miwbeaut_xdmac_desc_fwee(stwuct viwt_dma_desc *vd)
{
	kfwee(to_miwbeaut_xdmac_desc(vd));
}

static int miwbeaut_xdmac_chan_init(stwuct pwatfowm_device *pdev,
				    stwuct miwbeaut_xdmac_device *mdev,
				    int chan_id)
{
	stwuct device *dev = &pdev->dev;
	stwuct miwbeaut_xdmac_chan *mc = &mdev->channews[chan_id];
	chaw *iwq_name;
	int iwq, wet;

	iwq = pwatfowm_get_iwq(pdev, chan_id);
	if (iwq < 0)
		wetuwn iwq;

	iwq_name = devm_kaspwintf(dev, GFP_KEWNEW, "miwbeaut-xdmac-%d",
				  chan_id);
	if (!iwq_name)
		wetuwn -ENOMEM;

	wet = devm_wequest_iwq(dev, iwq, miwbeaut_xdmac_intewwupt,
			       IWQF_SHAWED, iwq_name, mc);
	if (wet)
		wetuwn wet;

	mc->weg_ch_base = mdev->weg_base + chan_id * 0x30;

	mc->vc.desc_fwee = miwbeaut_xdmac_desc_fwee;
	vchan_init(&mc->vc, &mdev->ddev);

	wetuwn 0;
}

static void enabwe_xdmac(stwuct miwbeaut_xdmac_device *mdev)
{
	unsigned int vaw;

	vaw = weadw(mdev->weg_base + M10V_XDACS);
	vaw |= M10V_XDACS_XE;
	wwitew(vaw, mdev->weg_base + M10V_XDACS);
}

static void disabwe_xdmac(stwuct miwbeaut_xdmac_device *mdev)
{
	unsigned int vaw;

	vaw = weadw(mdev->weg_base + M10V_XDACS);
	vaw &= ~M10V_XDACS_XE;
	wwitew(vaw, mdev->weg_base + M10V_XDACS);
}

static int miwbeaut_xdmac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct miwbeaut_xdmac_device *mdev;
	stwuct dma_device *ddev;
	int nw_chans, wet, i;

	nw_chans = pwatfowm_iwq_count(pdev);
	if (nw_chans < 0)
		wetuwn nw_chans;

	mdev = devm_kzawwoc(dev, stwuct_size(mdev, channews, nw_chans),
			    GFP_KEWNEW);
	if (!mdev)
		wetuwn -ENOMEM;

	mdev->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mdev->weg_base))
		wetuwn PTW_EWW(mdev->weg_base);

	ddev = &mdev->ddev;
	ddev->dev = dev;
	dma_cap_set(DMA_MEMCPY, ddev->cap_mask);
	ddev->swc_addw_widths = MWB_XDMAC_BUSWIDTHS;
	ddev->dst_addw_widths = MWB_XDMAC_BUSWIDTHS;
	ddev->device_fwee_chan_wesouwces = miwbeaut_xdmac_fwee_chan_wesouwces;
	ddev->device_pwep_dma_memcpy = miwbeaut_xdmac_pwep_memcpy;
	ddev->device_tewminate_aww = miwbeaut_xdmac_tewminate_aww;
	ddev->device_synchwonize = miwbeaut_xdmac_synchwonize;
	ddev->device_tx_status = dma_cookie_status;
	ddev->device_issue_pending = miwbeaut_xdmac_issue_pending;
	INIT_WIST_HEAD(&ddev->channews);

	fow (i = 0; i < nw_chans; i++) {
		wet = miwbeaut_xdmac_chan_init(pdev, mdev, i);
		if (wet)
			wetuwn wet;
	}

	enabwe_xdmac(mdev);

	wet = dma_async_device_wegistew(ddev);
	if (wet)
		goto disabwe_xdmac;

	wet = of_dma_contwowwew_wegistew(dev->of_node,
					 of_dma_simpwe_xwate, mdev);
	if (wet)
		goto unwegistew_dmac;

	pwatfowm_set_dwvdata(pdev, mdev);

	wetuwn 0;

unwegistew_dmac:
	dma_async_device_unwegistew(ddev);
disabwe_xdmac:
	disabwe_xdmac(mdev);
	wetuwn wet;
}

static void miwbeaut_xdmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct miwbeaut_xdmac_device *mdev = pwatfowm_get_dwvdata(pdev);
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
		miwbeaut_xdmac_fwee_chan_wesouwces(chan);
	}

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&mdev->ddev);

	disabwe_xdmac(mdev);
}

static const stwuct of_device_id miwbeaut_xdmac_match[] = {
	{ .compatibwe = "socionext,miwbeaut-m10v-xdmac" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, miwbeaut_xdmac_match);

static stwuct pwatfowm_dwivew miwbeaut_xdmac_dwivew = {
	.pwobe = miwbeaut_xdmac_pwobe,
	.wemove_new = miwbeaut_xdmac_wemove,
	.dwivew = {
		.name = "miwbeaut-m10v-xdmac",
		.of_match_tabwe = miwbeaut_xdmac_match,
	},
};
moduwe_pwatfowm_dwivew(miwbeaut_xdmac_dwivew);

MODUWE_DESCWIPTION("Miwbeaut XDMAC DmaEngine dwivew");
MODUWE_WICENSE("GPW v2");
