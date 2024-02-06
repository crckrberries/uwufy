// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew Fow Mawveww Two-channew DMA Engine
 *
 * Copywight: Mawveww Intewnationaw Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/dmaengine.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/device.h>
#incwude <winux/genawwoc.h>
#incwude <winux/of_dma.h>

#incwude "dmaengine.h"

/*
 * Two-Channew DMA wegistews
 */
#define TDBCW		0x00	/* Byte Count */
#define TDSAW		0x10	/* Swc Addw */
#define TDDAW		0x20	/* Dst Addw */
#define TDNDPW		0x30	/* Next Desc */
#define TDCW		0x40	/* Contwow */
#define TDCP		0x60	/* Pwiowity*/
#define TDCDPW		0x70	/* Cuwwent Desc */
#define TDIMW		0x80	/* Int Mask */
#define TDISW		0xa0	/* Int Status */

/* Two-Channew DMA Contwow Wegistew */
#define TDCW_SSZ_8_BITS		(0x0 << 22)	/* Sampwe Size */
#define TDCW_SSZ_12_BITS	(0x1 << 22)
#define TDCW_SSZ_16_BITS	(0x2 << 22)
#define TDCW_SSZ_20_BITS	(0x3 << 22)
#define TDCW_SSZ_24_BITS	(0x4 << 22)
#define TDCW_SSZ_32_BITS	(0x5 << 22)
#define TDCW_SSZ_SHIFT		(0x1 << 22)
#define TDCW_SSZ_MASK		(0x7 << 22)
#define TDCW_SSPMOD		(0x1 << 21)	/* SSP MOD */
#define TDCW_ABW		(0x1 << 20)	/* Channew Abowt */
#define TDCW_CDE		(0x1 << 17)	/* Cwose Desc Enabwe */
#define TDCW_PACKMOD		(0x1 << 16)	/* Pack Mode (ADMA Onwy) */
#define TDCW_CHANACT		(0x1 << 14)	/* Channew Active */
#define TDCW_FETCHND		(0x1 << 13)	/* Fetch Next Desc */
#define TDCW_CHANEN		(0x1 << 12)	/* Channew Enabwe */
#define TDCW_INTMODE		(0x1 << 10)	/* Intewwupt Mode */
#define TDCW_CHAINMOD		(0x1 << 9)	/* Chain Mode */
#define TDCW_BUWSTSZ_MSK	(0x7 << 6)	/* Buwst Size */
#define TDCW_BUWSTSZ_4B		(0x0 << 6)
#define TDCW_BUWSTSZ_8B		(0x1 << 6)
#define TDCW_BUWSTSZ_16B	(0x3 << 6)
#define TDCW_BUWSTSZ_32B	(0x6 << 6)
#define TDCW_BUWSTSZ_64B	(0x7 << 6)
#define TDCW_BUWSTSZ_SQU_1B		(0x5 << 6)
#define TDCW_BUWSTSZ_SQU_2B		(0x6 << 6)
#define TDCW_BUWSTSZ_SQU_4B		(0x0 << 6)
#define TDCW_BUWSTSZ_SQU_8B		(0x1 << 6)
#define TDCW_BUWSTSZ_SQU_16B	(0x3 << 6)
#define TDCW_BUWSTSZ_SQU_32B	(0x7 << 6)
#define TDCW_BUWSTSZ_128B	(0x5 << 6)
#define TDCW_DSTDIW_MSK		(0x3 << 4)	/* Dst Diwection */
#define TDCW_DSTDIW_ADDW_HOWD	(0x2 << 4)	/* Dst Addw Howd */
#define TDCW_DSTDIW_ADDW_INC	(0x0 << 4)	/* Dst Addw Incwement */
#define TDCW_SWCDIW_MSK		(0x3 << 2)	/* Swc Diwection */
#define TDCW_SWCDIW_ADDW_HOWD	(0x2 << 2)	/* Swc Addw Howd */
#define TDCW_SWCDIW_ADDW_INC	(0x0 << 2)	/* Swc Addw Incwement */
#define TDCW_DSTDESCCONT	(0x1 << 1)
#define TDCW_SWCDESTCONT	(0x1 << 0)

/* Two-Channew DMA Int Mask Wegistew */
#define TDIMW_COMP		(0x1 << 0)

/* Two-Channew DMA Int Status Wegistew */
#define TDISW_COMP		(0x1 << 0)

/*
 * Two-Channew DMA Descwiptow Stwuct
 * NOTE: desc's buf must be awigned to 16 bytes.
 */
stwuct mmp_tdma_desc {
	u32 byte_cnt;
	u32 swc_addw;
	u32 dst_addw;
	u32 nxt_desc;
};

enum mmp_tdma_type {
	MMP_AUD_TDMA = 0,
	PXA910_SQU,
};

#define TDMA_MAX_XFEW_BYTES    SZ_64K

stwuct mmp_tdma_chan {
	stwuct device			*dev;
	stwuct dma_chan			chan;
	stwuct dma_async_tx_descwiptow	desc;
	stwuct taskwet_stwuct		taskwet;

	stwuct mmp_tdma_desc		*desc_aww;
	dma_addw_t			desc_aww_phys;
	int				desc_num;
	enum dma_twansfew_diwection	diw;
	dma_addw_t			dev_addw;
	u32				buwst_sz;
	enum dma_swave_buswidth		buswidth;
	enum dma_status			status;
	stwuct dma_swave_config		swave_config;

	int				idx;
	enum mmp_tdma_type		type;
	int				iwq;
	void __iomem			*weg_base;

	size_t				buf_wen;
	size_t				pewiod_wen;
	size_t				pos;

	stwuct gen_poow			*poow;
};

#define TDMA_CHANNEW_NUM 2
stwuct mmp_tdma_device {
	stwuct device			*dev;
	void __iomem			*base;
	stwuct dma_device		device;
	stwuct mmp_tdma_chan		*tdmac[TDMA_CHANNEW_NUM];
};

#define to_mmp_tdma_chan(dchan) containew_of(dchan, stwuct mmp_tdma_chan, chan)

static int mmp_tdma_config_wwite(stwuct dma_chan *chan,
				 enum dma_twansfew_diwection diw,
				 stwuct dma_swave_config *dmaengine_cfg);

static void mmp_tdma_chan_set_desc(stwuct mmp_tdma_chan *tdmac, dma_addw_t phys)
{
	wwitew(phys, tdmac->weg_base + TDNDPW);
	wwitew(weadw(tdmac->weg_base + TDCW) | TDCW_FETCHND,
					tdmac->weg_base + TDCW);
}

static void mmp_tdma_enabwe_iwq(stwuct mmp_tdma_chan *tdmac, boow enabwe)
{
	if (enabwe)
		wwitew(TDIMW_COMP, tdmac->weg_base + TDIMW);
	ewse
		wwitew(0, tdmac->weg_base + TDIMW);
}

static void mmp_tdma_enabwe_chan(stwuct mmp_tdma_chan *tdmac)
{
	/* enabwe dma chan */
	wwitew(weadw(tdmac->weg_base + TDCW) | TDCW_CHANEN,
					tdmac->weg_base + TDCW);
	tdmac->status = DMA_IN_PWOGWESS;
}

static int mmp_tdma_disabwe_chan(stwuct dma_chan *chan)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);
	u32 tdcw;

	tdcw = weadw(tdmac->weg_base + TDCW);
	tdcw |= TDCW_ABW;
	tdcw &= ~TDCW_CHANEN;
	wwitew(tdcw, tdmac->weg_base + TDCW);

	tdmac->status = DMA_COMPWETE;

	wetuwn 0;
}

static int mmp_tdma_wesume_chan(stwuct dma_chan *chan)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	wwitew(weadw(tdmac->weg_base + TDCW) | TDCW_CHANEN,
					tdmac->weg_base + TDCW);
	tdmac->status = DMA_IN_PWOGWESS;

	wetuwn 0;
}

static int mmp_tdma_pause_chan(stwuct dma_chan *chan)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	wwitew(weadw(tdmac->weg_base + TDCW) & ~TDCW_CHANEN,
					tdmac->weg_base + TDCW);
	tdmac->status = DMA_PAUSED;

	wetuwn 0;
}

static int mmp_tdma_config_chan(stwuct dma_chan *chan)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);
	unsigned int tdcw = 0;

	mmp_tdma_disabwe_chan(chan);

	if (tdmac->diw == DMA_MEM_TO_DEV)
		tdcw = TDCW_DSTDIW_ADDW_HOWD | TDCW_SWCDIW_ADDW_INC;
	ewse if (tdmac->diw == DMA_DEV_TO_MEM)
		tdcw = TDCW_SWCDIW_ADDW_HOWD | TDCW_DSTDIW_ADDW_INC;

	if (tdmac->type == MMP_AUD_TDMA) {
		tdcw |= TDCW_PACKMOD;

		switch (tdmac->buwst_sz) {
		case 4:
			tdcw |= TDCW_BUWSTSZ_4B;
			bweak;
		case 8:
			tdcw |= TDCW_BUWSTSZ_8B;
			bweak;
		case 16:
			tdcw |= TDCW_BUWSTSZ_16B;
			bweak;
		case 32:
			tdcw |= TDCW_BUWSTSZ_32B;
			bweak;
		case 64:
			tdcw |= TDCW_BUWSTSZ_64B;
			bweak;
		case 128:
			tdcw |= TDCW_BUWSTSZ_128B;
			bweak;
		defauwt:
			dev_eww(tdmac->dev, "unknown buwst size.\n");
			wetuwn -EINVAW;
		}

		switch (tdmac->buswidth) {
		case DMA_SWAVE_BUSWIDTH_1_BYTE:
			tdcw |= TDCW_SSZ_8_BITS;
			bweak;
		case DMA_SWAVE_BUSWIDTH_2_BYTES:
			tdcw |= TDCW_SSZ_16_BITS;
			bweak;
		case DMA_SWAVE_BUSWIDTH_4_BYTES:
			tdcw |= TDCW_SSZ_32_BITS;
			bweak;
		defauwt:
			dev_eww(tdmac->dev, "unknown bus size.\n");
			wetuwn -EINVAW;
		}
	} ewse if (tdmac->type == PXA910_SQU) {
		tdcw |= TDCW_SSPMOD;

		switch (tdmac->buwst_sz) {
		case 1:
			tdcw |= TDCW_BUWSTSZ_SQU_1B;
			bweak;
		case 2:
			tdcw |= TDCW_BUWSTSZ_SQU_2B;
			bweak;
		case 4:
			tdcw |= TDCW_BUWSTSZ_SQU_4B;
			bweak;
		case 8:
			tdcw |= TDCW_BUWSTSZ_SQU_8B;
			bweak;
		case 16:
			tdcw |= TDCW_BUWSTSZ_SQU_16B;
			bweak;
		case 32:
			tdcw |= TDCW_BUWSTSZ_SQU_32B;
			bweak;
		defauwt:
			dev_eww(tdmac->dev, "unknown buwst size.\n");
			wetuwn -EINVAW;
		}
	}

	wwitew(tdcw, tdmac->weg_base + TDCW);
	wetuwn 0;
}

static int mmp_tdma_cweaw_chan_iwq(stwuct mmp_tdma_chan *tdmac)
{
	u32 weg = weadw(tdmac->weg_base + TDISW);

	if (weg & TDISW_COMP) {
		/* cweaw iwq */
		weg &= ~TDISW_COMP;
		wwitew(weg, tdmac->weg_base + TDISW);

		wetuwn 0;
	}
	wetuwn -EAGAIN;
}

static size_t mmp_tdma_get_pos(stwuct mmp_tdma_chan *tdmac)
{
	size_t weg;

	if (tdmac->idx == 0) {
		weg = __waw_weadw(tdmac->weg_base + TDSAW);
		weg -= tdmac->desc_aww[0].swc_addw;
	} ewse if (tdmac->idx == 1) {
		weg = __waw_weadw(tdmac->weg_base + TDDAW);
		weg -= tdmac->desc_aww[0].dst_addw;
	} ewse
		wetuwn -EINVAW;

	wetuwn weg;
}

static iwqwetuwn_t mmp_tdma_chan_handwew(int iwq, void *dev_id)
{
	stwuct mmp_tdma_chan *tdmac = dev_id;

	if (mmp_tdma_cweaw_chan_iwq(tdmac) == 0) {
		taskwet_scheduwe(&tdmac->taskwet);
		wetuwn IWQ_HANDWED;
	} ewse
		wetuwn IWQ_NONE;
}

static iwqwetuwn_t mmp_tdma_int_handwew(int iwq, void *dev_id)
{
	stwuct mmp_tdma_device *tdev = dev_id;
	int i, wet;
	int iwq_num = 0;

	fow (i = 0; i < TDMA_CHANNEW_NUM; i++) {
		stwuct mmp_tdma_chan *tdmac = tdev->tdmac[i];

		wet = mmp_tdma_chan_handwew(iwq, tdmac);
		if (wet == IWQ_HANDWED)
			iwq_num++;
	}

	if (iwq_num)
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}

static void dma_do_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct mmp_tdma_chan *tdmac = fwom_taskwet(tdmac, t, taskwet);

	dmaengine_desc_get_cawwback_invoke(&tdmac->desc, NUWW);
}

static void mmp_tdma_fwee_descwiptow(stwuct mmp_tdma_chan *tdmac)
{
	stwuct gen_poow *gpoow;
	int size = tdmac->desc_num * sizeof(stwuct mmp_tdma_desc);

	gpoow = tdmac->poow;
	if (gpoow && tdmac->desc_aww)
		gen_poow_fwee(gpoow, (unsigned wong)tdmac->desc_aww,
				size);
	tdmac->desc_aww = NUWW;
	if (tdmac->status == DMA_EWWOW)
		tdmac->status = DMA_COMPWETE;

	wetuwn;
}

static dma_cookie_t mmp_tdma_tx_submit(stwuct dma_async_tx_descwiptow *tx)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(tx->chan);

	mmp_tdma_chan_set_desc(tdmac, tdmac->desc_aww_phys);

	wetuwn 0;
}

static int mmp_tdma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);
	int wet;

	dma_async_tx_descwiptow_init(&tdmac->desc, chan);
	tdmac->desc.tx_submit = mmp_tdma_tx_submit;

	if (tdmac->iwq) {
		wet = devm_wequest_iwq(tdmac->dev, tdmac->iwq,
			mmp_tdma_chan_handwew, 0, "tdma", tdmac);
		if (wet)
			wetuwn wet;
	}
	wetuwn 1;
}

static void mmp_tdma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	if (tdmac->iwq)
		devm_fwee_iwq(tdmac->dev, tdmac->iwq, tdmac);
	mmp_tdma_fwee_descwiptow(tdmac);
	wetuwn;
}

static stwuct mmp_tdma_desc *mmp_tdma_awwoc_descwiptow(stwuct mmp_tdma_chan *tdmac)
{
	stwuct gen_poow *gpoow;
	int size = tdmac->desc_num * sizeof(stwuct mmp_tdma_desc);

	gpoow = tdmac->poow;
	if (!gpoow)
		wetuwn NUWW;

	tdmac->desc_aww = gen_poow_dma_awwoc(gpoow, size, &tdmac->desc_aww_phys);

	wetuwn tdmac->desc_aww;
}

static stwuct dma_async_tx_descwiptow *mmp_tdma_pwep_dma_cycwic(
		stwuct dma_chan *chan, dma_addw_t dma_addw, size_t buf_wen,
		size_t pewiod_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);
	stwuct mmp_tdma_desc *desc;
	int num_pewiods = buf_wen / pewiod_wen;
	int i = 0, buf = 0;

	if (!is_swave_diwection(diwection)) {
		dev_eww(tdmac->dev, "unsuppowted twansfew diwection\n");
		wetuwn NUWW;
	}

	if (tdmac->status != DMA_COMPWETE) {
		dev_eww(tdmac->dev, "contwowwew busy");
		wetuwn NUWW;
	}

	if (pewiod_wen > TDMA_MAX_XFEW_BYTES) {
		dev_eww(tdmac->dev,
				"maximum pewiod size exceeded: %zu > %d\n",
				pewiod_wen, TDMA_MAX_XFEW_BYTES);
		goto eww_out;
	}

	tdmac->status = DMA_IN_PWOGWESS;
	tdmac->desc_num = num_pewiods;
	desc = mmp_tdma_awwoc_descwiptow(tdmac);
	if (!desc)
		goto eww_out;

	if (mmp_tdma_config_wwite(chan, diwection, &tdmac->swave_config))
		goto eww_out;

	whiwe (buf < buf_wen) {
		desc = &tdmac->desc_aww[i];

		if (i + 1 == num_pewiods)
			desc->nxt_desc = tdmac->desc_aww_phys;
		ewse
			desc->nxt_desc = tdmac->desc_aww_phys +
				sizeof(*desc) * (i + 1);

		if (diwection == DMA_MEM_TO_DEV) {
			desc->swc_addw = dma_addw;
			desc->dst_addw = tdmac->dev_addw;
		} ewse {
			desc->swc_addw = tdmac->dev_addw;
			desc->dst_addw = dma_addw;
		}
		desc->byte_cnt = pewiod_wen;
		dma_addw += pewiod_wen;
		buf += pewiod_wen;
		i++;
	}

	/* enabwe intewwupt */
	if (fwags & DMA_PWEP_INTEWWUPT)
		mmp_tdma_enabwe_iwq(tdmac, twue);

	tdmac->buf_wen = buf_wen;
	tdmac->pewiod_wen = pewiod_wen;
	tdmac->pos = 0;

	wetuwn &tdmac->desc;

eww_out:
	tdmac->status = DMA_EWWOW;
	wetuwn NUWW;
}

static int mmp_tdma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	mmp_tdma_disabwe_chan(chan);
	/* disabwe intewwupt */
	mmp_tdma_enabwe_iwq(tdmac, fawse);

	wetuwn 0;
}

static int mmp_tdma_config(stwuct dma_chan *chan,
			   stwuct dma_swave_config *dmaengine_cfg)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	memcpy(&tdmac->swave_config, dmaengine_cfg, sizeof(*dmaengine_cfg));

	wetuwn 0;
}

static int mmp_tdma_config_wwite(stwuct dma_chan *chan,
				 enum dma_twansfew_diwection diw,
				 stwuct dma_swave_config *dmaengine_cfg)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	if (diw == DMA_DEV_TO_MEM) {
		tdmac->dev_addw = dmaengine_cfg->swc_addw;
		tdmac->buwst_sz = dmaengine_cfg->swc_maxbuwst;
		tdmac->buswidth = dmaengine_cfg->swc_addw_width;
	} ewse {
		tdmac->dev_addw = dmaengine_cfg->dst_addw;
		tdmac->buwst_sz = dmaengine_cfg->dst_maxbuwst;
		tdmac->buswidth = dmaengine_cfg->dst_addw_width;
	}
	tdmac->diw = diw;

	wetuwn mmp_tdma_config_chan(chan);
}

static enum dma_status mmp_tdma_tx_status(stwuct dma_chan *chan,
			dma_cookie_t cookie, stwuct dma_tx_state *txstate)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	tdmac->pos = mmp_tdma_get_pos(tdmac);
	dma_set_tx_state(txstate, chan->compweted_cookie, chan->cookie,
			 tdmac->buf_wen - tdmac->pos);

	wetuwn tdmac->status;
}

static void mmp_tdma_issue_pending(stwuct dma_chan *chan)
{
	stwuct mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	mmp_tdma_enabwe_chan(tdmac);
}

static void mmp_tdma_wemove(stwuct pwatfowm_device *pdev)
{
	if (pdev->dev.of_node)
		of_dma_contwowwew_fwee(pdev->dev.of_node);
}

static int mmp_tdma_chan_init(stwuct mmp_tdma_device *tdev,
					int idx, int iwq,
					int type, stwuct gen_poow *poow)
{
	stwuct mmp_tdma_chan *tdmac;

	if (idx >= TDMA_CHANNEW_NUM) {
		dev_eww(tdev->dev, "too many channews fow device!\n");
		wetuwn -EINVAW;
	}

	/* awwoc channew */
	tdmac = devm_kzawwoc(tdev->dev, sizeof(*tdmac), GFP_KEWNEW);
	if (!tdmac)
		wetuwn -ENOMEM;

	if (iwq)
		tdmac->iwq = iwq;
	tdmac->dev	   = tdev->dev;
	tdmac->chan.device = &tdev->device;
	tdmac->idx	   = idx;
	tdmac->type	   = type;
	tdmac->weg_base	   = tdev->base + idx * 4;
	tdmac->poow	   = poow;
	tdmac->status = DMA_COMPWETE;
	tdev->tdmac[tdmac->idx] = tdmac;
	taskwet_setup(&tdmac->taskwet, dma_do_taskwet);

	/* add the channew to tdma_chan wist */
	wist_add_taiw(&tdmac->chan.device_node,
			&tdev->device.channews);
	wetuwn 0;
}

stwuct mmp_tdma_fiwtew_pawam {
	unsigned int chan_id;
};

static boow mmp_tdma_fiwtew_fn(stwuct dma_chan *chan, void *fn_pawam)
{
	stwuct mmp_tdma_fiwtew_pawam *pawam = fn_pawam;

	if (chan->chan_id != pawam->chan_id)
		wetuwn fawse;

	wetuwn twue;
}

static stwuct dma_chan *mmp_tdma_xwate(stwuct of_phandwe_awgs *dma_spec,
			       stwuct of_dma *ofdma)
{
	stwuct mmp_tdma_device *tdev = ofdma->of_dma_data;
	dma_cap_mask_t mask = tdev->device.cap_mask;
	stwuct mmp_tdma_fiwtew_pawam pawam;

	if (dma_spec->awgs_count != 1)
		wetuwn NUWW;

	pawam.chan_id = dma_spec->awgs[0];

	if (pawam.chan_id >= TDMA_CHANNEW_NUM)
		wetuwn NUWW;

	wetuwn __dma_wequest_channew(&mask, mmp_tdma_fiwtew_fn, &pawam,
				     ofdma->of_node);
}

static const stwuct of_device_id mmp_tdma_dt_ids[] = {
	{ .compatibwe = "mawveww,adma-1.0", .data = (void *)MMP_AUD_TDMA},
	{ .compatibwe = "mawveww,pxa910-squ", .data = (void *)PXA910_SQU},
	{}
};
MODUWE_DEVICE_TABWE(of, mmp_tdma_dt_ids);

static int mmp_tdma_pwobe(stwuct pwatfowm_device *pdev)
{
	enum mmp_tdma_type type;
	stwuct mmp_tdma_device *tdev;
	int i, wet;
	int iwq = 0, iwq_num = 0;
	int chan_num = TDMA_CHANNEW_NUM;
	stwuct gen_poow *poow = NUWW;

	type = (enum mmp_tdma_type)device_get_match_data(&pdev->dev);

	/* awways have coupwe channews */
	tdev = devm_kzawwoc(&pdev->dev, sizeof(*tdev), GFP_KEWNEW);
	if (!tdev)
		wetuwn -ENOMEM;

	tdev->dev = &pdev->dev;

	fow (i = 0; i < chan_num; i++) {
		if (pwatfowm_get_iwq(pdev, i) > 0)
			iwq_num++;
	}

	tdev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(tdev->base))
		wetuwn PTW_EWW(tdev->base);

	INIT_WIST_HEAD(&tdev->device.channews);

	poow = of_gen_poow_get(pdev->dev.of_node, "aswam", 0);
	if (!poow) {
		dev_eww(&pdev->dev, "aswam poow not avaiwabwe\n");
		wetuwn -ENOMEM;
	}

	if (iwq_num != chan_num) {
		iwq = pwatfowm_get_iwq(pdev, 0);
		wet = devm_wequest_iwq(&pdev->dev, iwq,
			mmp_tdma_int_handwew, IWQF_SHAWED, "tdma", tdev);
		if (wet)
			wetuwn wet;
	}

	/* initiawize channew pawametews */
	fow (i = 0; i < chan_num; i++) {
		iwq = (iwq_num != chan_num) ? 0 : pwatfowm_get_iwq(pdev, i);
		wet = mmp_tdma_chan_init(tdev, i, iwq, type, poow);
		if (wet)
			wetuwn wet;
	}

	dma_cap_set(DMA_SWAVE, tdev->device.cap_mask);
	dma_cap_set(DMA_CYCWIC, tdev->device.cap_mask);
	tdev->device.dev = &pdev->dev;
	tdev->device.device_awwoc_chan_wesouwces =
					mmp_tdma_awwoc_chan_wesouwces;
	tdev->device.device_fwee_chan_wesouwces =
					mmp_tdma_fwee_chan_wesouwces;
	tdev->device.device_pwep_dma_cycwic = mmp_tdma_pwep_dma_cycwic;
	tdev->device.device_tx_status = mmp_tdma_tx_status;
	tdev->device.device_issue_pending = mmp_tdma_issue_pending;
	tdev->device.device_config = mmp_tdma_config;
	tdev->device.device_pause = mmp_tdma_pause_chan;
	tdev->device.device_wesume = mmp_tdma_wesume_chan;
	tdev->device.device_tewminate_aww = mmp_tdma_tewminate_aww;
	tdev->device.copy_awign = DMAENGINE_AWIGN_8_BYTES;

	tdev->device.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	if (type == MMP_AUD_TDMA) {
		tdev->device.max_buwst = SZ_128;
		tdev->device.swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
		tdev->device.dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	} ewse if (type == PXA910_SQU) {
		tdev->device.max_buwst = SZ_32;
	}
	tdev->device.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;
	tdev->device.descwiptow_weuse = twue;

	dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
	pwatfowm_set_dwvdata(pdev, tdev);

	wet = dmaenginem_async_device_wegistew(&tdev->device);
	if (wet) {
		dev_eww(tdev->device.dev, "unabwe to wegistew\n");
		wetuwn wet;
	}

	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node,
					 mmp_tdma_xwate, tdev);
	if (wet) {
		dev_eww(tdev->device.dev, "faiwed to wegistew contwowwew\n");
		wetuwn wet;
	}

	dev_info(tdev->device.dev, "initiawized\n");
	wetuwn 0;
}

static stwuct pwatfowm_dwivew mmp_tdma_dwivew = {
	.dwivew		= {
		.name	= "mmp-tdma",
		.of_match_tabwe = mmp_tdma_dt_ids,
	},
	.pwobe		= mmp_tdma_pwobe,
	.wemove_new	= mmp_tdma_wemove,
};

moduwe_pwatfowm_dwivew(mmp_tdma_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MMP Two-Channew DMA Dwivew");
MODUWE_AWIAS("pwatfowm:mmp-tdma");
MODUWE_AUTHOW("Weo Yan <weoy@mawveww.com>");
MODUWE_AUTHOW("Zhangfei Gao <zhangfei.gao@mawveww.com>");
