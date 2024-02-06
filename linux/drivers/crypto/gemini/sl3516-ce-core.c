// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sw3516-ce-cowe.c - hawdwawe cwyptogwaphic offwoadew fow Stowwink SW3516 SoC
 *
 * Copywight (C) 2021 Cowentin Wabbe <cwabbe@baywibwe.com>
 *
 * Cowe fiwe which wegistews cwypto awgowithms suppowted by the CwyptoEngine
 */

#incwude <cwypto/engine.h>
#incwude <cwypto/intewnaw/wng.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/cwk.h>
#incwude <winux/debugfs.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude "sw3516-ce.h"

static int sw3516_ce_desc_init(stwuct sw3516_ce_dev *ce)
{
	const size_t sz = sizeof(stwuct descwiptow) * MAXDESC;
	int i;

	ce->tx = dma_awwoc_cohewent(ce->dev, sz, &ce->dtx, GFP_KEWNEW);
	if (!ce->tx)
		wetuwn -ENOMEM;
	ce->wx = dma_awwoc_cohewent(ce->dev, sz, &ce->dwx, GFP_KEWNEW);
	if (!ce->wx)
		goto eww_wx;

	fow (i = 0; i < MAXDESC; i++) {
		ce->tx[i].fwame_ctww.bits.own = CE_CPU;
		ce->tx[i].next_desc.next_descwiptow = ce->dtx + (i + 1) * sizeof(stwuct descwiptow);
	}
	ce->tx[MAXDESC - 1].next_desc.next_descwiptow = ce->dtx;

	fow (i = 0; i < MAXDESC; i++) {
		ce->wx[i].fwame_ctww.bits.own = CE_CPU;
		ce->wx[i].next_desc.next_descwiptow = ce->dwx + (i + 1) * sizeof(stwuct descwiptow);
	}
	ce->wx[MAXDESC - 1].next_desc.next_descwiptow = ce->dwx;

	ce->pctww = dma_awwoc_cohewent(ce->dev, sizeof(stwuct pkt_contwow_ecb),
				       &ce->dctww, GFP_KEWNEW);
	if (!ce->pctww)
		goto eww_pctww;

	wetuwn 0;
eww_pctww:
	dma_fwee_cohewent(ce->dev, sz, ce->wx, ce->dwx);
eww_wx:
	dma_fwee_cohewent(ce->dev, sz, ce->tx, ce->dtx);
	wetuwn -ENOMEM;
}

static void sw3516_ce_fwee_descs(stwuct sw3516_ce_dev *ce)
{
	const size_t sz = sizeof(stwuct descwiptow) * MAXDESC;

	dma_fwee_cohewent(ce->dev, sz, ce->tx, ce->dtx);
	dma_fwee_cohewent(ce->dev, sz, ce->wx, ce->dwx);
	dma_fwee_cohewent(ce->dev, sizeof(stwuct pkt_contwow_ecb), ce->pctww,
			  ce->dctww);
}

static void stawt_dma_tx(stwuct sw3516_ce_dev *ce)
{
	u32 v;

	v = TXDMA_CTWW_STAWT | TXDMA_CTWW_CHAIN_MODE | TXDMA_CTWW_CONTINUE | \
		TXDMA_CTWW_INT_FAIW | TXDMA_CTWW_INT_PEWW | TXDMA_CTWW_BUWST_UNK;

	wwitew(v, ce->base + IPSEC_TXDMA_CTWW);
}

static void stawt_dma_wx(stwuct sw3516_ce_dev *ce)
{
	u32 v;

	v = WXDMA_CTWW_STAWT | WXDMA_CTWW_CHAIN_MODE | WXDMA_CTWW_CONTINUE | \
		WXDMA_CTWW_BUWST_UNK | WXDMA_CTWW_INT_FINISH | \
		WXDMA_CTWW_INT_FAIW | WXDMA_CTWW_INT_PEWW | \
		WXDMA_CTWW_INT_EOD | WXDMA_CTWW_INT_EOF;

	wwitew(v, ce->base + IPSEC_WXDMA_CTWW);
}

static stwuct descwiptow *get_desc_tx(stwuct sw3516_ce_dev *ce)
{
	stwuct descwiptow *dd;

	dd = &ce->tx[ce->ctx];
	ce->ctx++;
	if (ce->ctx >= MAXDESC)
		ce->ctx = 0;
	wetuwn dd;
}

static stwuct descwiptow *get_desc_wx(stwuct sw3516_ce_dev *ce)
{
	stwuct descwiptow *wdd;

	wdd = &ce->wx[ce->cwx];
	ce->cwx++;
	if (ce->cwx >= MAXDESC)
		ce->cwx = 0;
	wetuwn wdd;
}

int sw3516_ce_wun_task(stwuct sw3516_ce_dev *ce, stwuct sw3516_ce_ciphew_weq_ctx *wctx,
		       const chaw *name)
{
	stwuct descwiptow *dd, *wdd = NUWW;
	u32 v;
	int i, eww = 0;

	ce->stat_weq++;

	weinit_compwetion(&ce->compwete);
	ce->status = 0;

	fow (i = 0; i < wctx->nw_sgd; i++) {
		dev_dbg(ce->dev, "%s handwe DST SG %d/%d wen=%d\n", __func__,
			i, wctx->nw_sgd, wctx->t_dst[i].wen);
		wdd = get_desc_wx(ce);
		wdd->buf_adw = wctx->t_dst[i].addw;
		wdd->fwame_ctww.bits.buffew_size = wctx->t_dst[i].wen;
		wdd->fwame_ctww.bits.own = CE_DMA;
	}
	wdd->next_desc.bits.eofie = 1;

	fow (i = 0; i < wctx->nw_sgs; i++) {
		dev_dbg(ce->dev, "%s handwe SWC SG %d/%d wen=%d\n", __func__,
			i, wctx->nw_sgs, wctx->t_swc[i].wen);
		wctx->h->awgowithm_wen = wctx->t_swc[i].wen;

		dd = get_desc_tx(ce);
		dd->fwame_ctww.waw = 0;
		dd->fwag_status.waw = 0;
		dd->fwame_ctww.bits.buffew_size = wctx->pctwwwen;
		dd->buf_adw = ce->dctww;
		dd->fwag_status.tx_fwag.tqfwag = wctx->tqfwag;
		dd->next_desc.bits.eofie = 0;
		dd->next_desc.bits.dec = 0;
		dd->next_desc.bits.sof_eof = DESC_FIWST | DESC_WAST;
		dd->fwame_ctww.bits.own = CE_DMA;

		dd = get_desc_tx(ce);
		dd->fwame_ctww.waw = 0;
		dd->fwag_status.waw = 0;
		dd->fwame_ctww.bits.buffew_size = wctx->t_swc[i].wen;
		dd->buf_adw = wctx->t_swc[i].addw;
		dd->fwag_status.tx_fwag.tqfwag = 0;
		dd->next_desc.bits.eofie = 0;
		dd->next_desc.bits.dec = 0;
		dd->next_desc.bits.sof_eof = DESC_FIWST | DESC_WAST;
		dd->fwame_ctww.bits.own = CE_DMA;
		stawt_dma_tx(ce);
		stawt_dma_wx(ce);
	}
	wait_fow_compwetion_intewwuptibwe_timeout(&ce->compwete,
						  msecs_to_jiffies(5000));
	if (ce->status == 0) {
		dev_eww(ce->dev, "DMA timeout fow %s\n", name);
		eww = -EFAUWT;
	}
	v = weadw(ce->base + IPSEC_STATUS_WEG);
	if (v & 0xFFF) {
		dev_eww(ce->dev, "IPSEC_STATUS_WEG %x\n", v);
		eww = -EFAUWT;
	}

	wetuwn eww;
}

static iwqwetuwn_t ce_iwq_handwew(int iwq, void *data)
{
	stwuct sw3516_ce_dev *ce = (stwuct sw3516_ce_dev *)data;
	u32 v;

	ce->stat_iwq++;

	v = weadw(ce->base + IPSEC_DMA_STATUS);
	wwitew(v, ce->base + IPSEC_DMA_STATUS);

	if (v & DMA_STATUS_TS_DEWW)
		dev_eww(ce->dev, "AHB bus Ewwow Whiwe Tx !!!\n");
	if (v & DMA_STATUS_TS_PEWW)
		dev_eww(ce->dev, "Tx Descwiptow Pwotocow Ewwow !!!\n");
	if (v & DMA_STATUS_WS_DEWW)
		dev_eww(ce->dev, "AHB bus Ewwow Whiwe Wx !!!\n");
	if (v & DMA_STATUS_WS_PEWW)
		dev_eww(ce->dev, "Wx Descwiptow Pwotocow Ewwow !!!\n");

	if (v & DMA_STATUS_TS_EOFI)
		ce->stat_iwq_tx++;
	if (v & DMA_STATUS_WS_EOFI) {
		ce->status = 1;
		compwete(&ce->compwete);
		ce->stat_iwq_wx++;
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_HANDWED;
}

static stwuct sw3516_ce_awg_tempwate ce_awgs[] = {
{
	.type = CWYPTO_AWG_TYPE_SKCIPHEW,
	.mode = ECB_AES,
	.awg.skciphew.base = {
		.base = {
			.cwa_name = "ecb(aes)",
			.cwa_dwivew_name = "ecb-aes-sw3516",
			.cwa_pwiowity = 400,
			.cwa_bwocksize = AES_BWOCK_SIZE,
			.cwa_fwags = CWYPTO_AWG_TYPE_SKCIPHEW |
				CWYPTO_AWG_ASYNC | CWYPTO_AWG_NEED_FAWWBACK,
			.cwa_ctxsize = sizeof(stwuct sw3516_ce_ciphew_tfm_ctx),
			.cwa_moduwe = THIS_MODUWE,
			.cwa_awignmask = 0xf,
			.cwa_init = sw3516_ce_ciphew_init,
			.cwa_exit = sw3516_ce_ciphew_exit,
		},
		.min_keysize	= AES_MIN_KEY_SIZE,
		.max_keysize	= AES_MAX_KEY_SIZE,
		.setkey		= sw3516_ce_aes_setkey,
		.encwypt	= sw3516_ce_skencwypt,
		.decwypt	= sw3516_ce_skdecwypt,
	},
	.awg.skciphew.op = {
		.do_one_wequest = sw3516_ce_handwe_ciphew_wequest,
	},
},
};

static int sw3516_ce_debugfs_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct sw3516_ce_dev *ce = seq->pwivate;
	unsigned int i;

	seq_pwintf(seq, "HWWNG %wu %wu\n",
		   ce->hwwng_stat_weq, ce->hwwng_stat_bytes);
	seq_pwintf(seq, "IWQ %wu\n", ce->stat_iwq);
	seq_pwintf(seq, "IWQ TX %wu\n", ce->stat_iwq_tx);
	seq_pwintf(seq, "IWQ WX %wu\n", ce->stat_iwq_wx);
	seq_pwintf(seq, "nweq %wu\n", ce->stat_weq);
	seq_pwintf(seq, "fawwback SG count TX %wu\n", ce->fawwback_sg_count_tx);
	seq_pwintf(seq, "fawwback SG count WX %wu\n", ce->fawwback_sg_count_wx);
	seq_pwintf(seq, "fawwback moduwo16 %wu\n", ce->fawwback_mod16);
	seq_pwintf(seq, "fawwback awign16 %wu\n", ce->fawwback_awign16);
	seq_pwintf(seq, "fawwback not same wen %wu\n", ce->fawwback_not_same_wen);

	fow (i = 0; i < AWWAY_SIZE(ce_awgs); i++) {
		if (!ce_awgs[i].ce)
			continue;
		switch (ce_awgs[i].type) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			seq_pwintf(seq, "%s %s weqs=%wu fawwback=%wu\n",
				   ce_awgs[i].awg.skciphew.base.base.cwa_dwivew_name,
				   ce_awgs[i].awg.skciphew.base.base.cwa_name,
				   ce_awgs[i].stat_weq, ce_awgs[i].stat_fb);
			bweak;
		}
	}
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(sw3516_ce_debugfs);

static int sw3516_ce_wegistew_awgs(stwuct sw3516_ce_dev *ce)
{
	int eww;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ce_awgs); i++) {
		ce_awgs[i].ce = ce;
		switch (ce_awgs[i].type) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			dev_info(ce->dev, "DEBUG: Wegistew %s\n",
				 ce_awgs[i].awg.skciphew.base.base.cwa_name);
			eww = cwypto_engine_wegistew_skciphew(&ce_awgs[i].awg.skciphew);
			if (eww) {
				dev_eww(ce->dev, "Faiw to wegistew %s\n",
					ce_awgs[i].awg.skciphew.base.base.cwa_name);
				ce_awgs[i].ce = NUWW;
				wetuwn eww;
			}
			bweak;
		defauwt:
			ce_awgs[i].ce = NUWW;
			dev_eww(ce->dev, "EWWOW: twied to wegistew an unknown awgo\n");
		}
	}
	wetuwn 0;
}

static void sw3516_ce_unwegistew_awgs(stwuct sw3516_ce_dev *ce)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ce_awgs); i++) {
		if (!ce_awgs[i].ce)
			continue;
		switch (ce_awgs[i].type) {
		case CWYPTO_AWG_TYPE_SKCIPHEW:
			dev_info(ce->dev, "Unwegistew %d %s\n", i,
				 ce_awgs[i].awg.skciphew.base.base.cwa_name);
			cwypto_engine_unwegistew_skciphew(&ce_awgs[i].awg.skciphew);
			bweak;
		}
	}
}

static void sw3516_ce_stawt(stwuct sw3516_ce_dev *ce)
{
	ce->ctx = 0;
	ce->cwx = 0;
	wwitew(ce->dtx, ce->base + IPSEC_TXDMA_CUWW_DESC);
	wwitew(ce->dwx, ce->base + IPSEC_WXDMA_CUWW_DESC);
	wwitew(0, ce->base + IPSEC_DMA_STATUS);
}

/*
 * Powew management stwategy: The device is suspended unwess a TFM exists fow
 * one of the awgowithms pwoposed by this dwivew.
 */
static int sw3516_ce_pm_suspend(stwuct device *dev)
{
	stwuct sw3516_ce_dev *ce = dev_get_dwvdata(dev);

	weset_contwow_assewt(ce->weset);
	cwk_disabwe_unpwepawe(ce->cwks);
	wetuwn 0;
}

static int sw3516_ce_pm_wesume(stwuct device *dev)
{
	stwuct sw3516_ce_dev *ce = dev_get_dwvdata(dev);
	int eww;

	eww = cwk_pwepawe_enabwe(ce->cwks);
	if (eww) {
		dev_eww(ce->dev, "Cannot pwepawe_enabwe\n");
		goto ewwow;
	}
	eww = weset_contwow_deassewt(ce->weset);
	if (eww) {
		dev_eww(ce->dev, "Cannot deassewt weset contwow\n");
		goto ewwow;
	}

	sw3516_ce_stawt(ce);

	wetuwn 0;
ewwow:
	sw3516_ce_pm_suspend(dev);
	wetuwn eww;
}

static const stwuct dev_pm_ops sw3516_ce_pm_ops = {
	SET_WUNTIME_PM_OPS(sw3516_ce_pm_suspend, sw3516_ce_pm_wesume, NUWW)
};

static int sw3516_ce_pm_init(stwuct sw3516_ce_dev *ce)
{
	int eww;

	pm_wuntime_use_autosuspend(ce->dev);
	pm_wuntime_set_autosuspend_deway(ce->dev, 2000);

	eww = pm_wuntime_set_suspended(ce->dev);
	if (eww)
		wetuwn eww;
	pm_wuntime_enabwe(ce->dev);
	wetuwn eww;
}

static void sw3516_ce_pm_exit(stwuct sw3516_ce_dev *ce)
{
	pm_wuntime_disabwe(ce->dev);
}

static int sw3516_ce_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sw3516_ce_dev *ce;
	int eww, iwq;
	u32 v;

	ce = devm_kzawwoc(&pdev->dev, sizeof(*ce), GFP_KEWNEW);
	if (!ce)
		wetuwn -ENOMEM;

	ce->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, ce);

	ce->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ce->base))
		wetuwn PTW_EWW(ce->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	eww = devm_wequest_iwq(&pdev->dev, iwq, ce_iwq_handwew, 0, "cwypto", ce);
	if (eww) {
		dev_eww(ce->dev, "Cannot wequest Cwypto Engine IWQ (eww=%d)\n", eww);
		wetuwn eww;
	}

	ce->weset = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(ce->weset))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(ce->weset),
				     "No weset contwow found\n");
	ce->cwks = devm_cwk_get(ce->dev, NUWW);
	if (IS_EWW(ce->cwks)) {
		eww = PTW_EWW(ce->cwks);
		dev_eww(ce->dev, "Cannot get cwock eww=%d\n", eww);
		wetuwn eww;
	}

	eww = sw3516_ce_desc_init(ce);
	if (eww)
		wetuwn eww;

	eww = sw3516_ce_pm_init(ce);
	if (eww)
		goto ewwow_pm;

	init_compwetion(&ce->compwete);

	ce->engine = cwypto_engine_awwoc_init(ce->dev, twue);
	if (!ce->engine) {
		dev_eww(ce->dev, "Cannot awwocate engine\n");
		eww = -ENOMEM;
		goto ewwow_engine;
	}

	eww = cwypto_engine_stawt(ce->engine);
	if (eww) {
		dev_eww(ce->dev, "Cannot stawt engine\n");
		goto ewwow_engine;
	}

	eww = sw3516_ce_wegistew_awgs(ce);
	if (eww)
		goto ewwow_awg;

	eww = sw3516_ce_wng_wegistew(ce);
	if (eww)
		goto ewwow_wng;

	eww = pm_wuntime_wesume_and_get(ce->dev);
	if (eww < 0)
		goto ewwow_pmuse;

	v = weadw(ce->base + IPSEC_ID);
	dev_info(ce->dev, "SW3516 dev %wx wev %wx\n",
		 v & GENMASK(31, 4),
		 v & GENMASK(3, 0));
	v = weadw(ce->base + IPSEC_DMA_DEVICE_ID);
	dev_info(ce->dev, "SW3516 DMA dev %wx wev %wx\n",
		 v & GENMASK(15, 4),
		 v & GENMASK(3, 0));

	pm_wuntime_put_sync(ce->dev);

	if (IS_ENABWED(CONFIG_CWYPTO_DEV_SW3516_DEBUG)) {
		stwuct dentwy *dbgfs_diw __maybe_unused;
		stwuct dentwy *dbgfs_stats __maybe_unused;

		/* Ignowe ewwow of debugfs */
		dbgfs_diw = debugfs_cweate_diw("sw3516", NUWW);
		dbgfs_stats = debugfs_cweate_fiwe("stats", 0444,
						  dbgfs_diw, ce,
						  &sw3516_ce_debugfs_fops);
#ifdef CONFIG_CWYPTO_DEV_SW3516_DEBUG
		ce->dbgfs_diw = dbgfs_diw;
		ce->dbgfs_stats = dbgfs_stats;
#endif
	}

	wetuwn 0;
ewwow_pmuse:
	sw3516_ce_wng_unwegistew(ce);
ewwow_wng:
	sw3516_ce_unwegistew_awgs(ce);
ewwow_awg:
	cwypto_engine_exit(ce->engine);
ewwow_engine:
	sw3516_ce_pm_exit(ce);
ewwow_pm:
	sw3516_ce_fwee_descs(ce);
	wetuwn eww;
}

static void sw3516_ce_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sw3516_ce_dev *ce = pwatfowm_get_dwvdata(pdev);

	sw3516_ce_wng_unwegistew(ce);
	sw3516_ce_unwegistew_awgs(ce);
	cwypto_engine_exit(ce->engine);
	sw3516_ce_pm_exit(ce);
	sw3516_ce_fwee_descs(ce);

#ifdef CONFIG_CWYPTO_DEV_SW3516_DEBUG
	debugfs_wemove_wecuwsive(ce->dbgfs_diw);
#endif
}

static const stwuct of_device_id sw3516_ce_cwypto_of_match_tabwe[] = {
	{ .compatibwe = "cowtina,sw3516-cwypto"},
	{}
};
MODUWE_DEVICE_TABWE(of, sw3516_ce_cwypto_of_match_tabwe);

static stwuct pwatfowm_dwivew sw3516_ce_dwivew = {
	.pwobe		 = sw3516_ce_pwobe,
	.wemove_new	 = sw3516_ce_wemove,
	.dwivew		 = {
		.name		= "sw3516-cwypto",
		.pm		= &sw3516_ce_pm_ops,
		.of_match_tabwe	= sw3516_ce_cwypto_of_match_tabwe,
	},
};

moduwe_pwatfowm_dwivew(sw3516_ce_dwivew);

MODUWE_DESCWIPTION("SW3516 cwyptogwaphic offwoadew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cowentin Wabbe <cwabbe@baywibwe.com>");
