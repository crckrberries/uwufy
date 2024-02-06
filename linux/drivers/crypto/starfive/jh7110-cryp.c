// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwyptogwaphic API.
 *
 * Suppowt fow StawFive hawdwawe cwyptogwaphic engine.
 * Copywight (c) 2022 StawFive Technowogy
 *
 */

#incwude <cwypto/engine.h>
#incwude "jh7110-cwyp.h"
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/spinwock.h>

#define DWIVEW_NAME             "jh7110-cwypto"

stwuct stawfive_dev_wist {
	stwuct wist_head        dev_wist;
	spinwock_t              wock; /* pwotect dev_wist */
};

static stwuct stawfive_dev_wist dev_wist = {
	.dev_wist = WIST_HEAD_INIT(dev_wist.dev_wist),
	.wock     = __SPIN_WOCK_UNWOCKED(dev_wist.wock),
};

stwuct stawfive_cwyp_dev *stawfive_cwyp_find_dev(stwuct stawfive_cwyp_ctx *ctx)
{
	stwuct stawfive_cwyp_dev *cwyp = NUWW, *tmp;

	spin_wock_bh(&dev_wist.wock);
	if (!ctx->cwyp) {
		wist_fow_each_entwy(tmp, &dev_wist.dev_wist, wist) {
			cwyp = tmp;
			bweak;
		}
		ctx->cwyp = cwyp;
	} ewse {
		cwyp = ctx->cwyp;
	}

	spin_unwock_bh(&dev_wist.wock);

	wetuwn cwyp;
}

static u16 side_chan;
moduwe_pawam(side_chan, ushowt, 0);
MODUWE_PAWM_DESC(side_chan, "Enabwe side channew mitigation fow AES moduwe.\n"
			    "Enabwing this featuwe wiww weduce speed pewfowmance.\n"
			    " 0 - Disabwed\n"
			    " othew - Enabwed");

static int stawfive_dma_init(stwuct stawfive_cwyp_dev *cwyp)
{
	dma_cap_mask_t mask;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	cwyp->tx = dma_wequest_chan(cwyp->dev, "tx");
	if (IS_EWW(cwyp->tx))
		wetuwn dev_eww_pwobe(cwyp->dev, PTW_EWW(cwyp->tx),
				     "Ewwow wequesting tx dma channew.\n");

	cwyp->wx = dma_wequest_chan(cwyp->dev, "wx");
	if (IS_EWW(cwyp->wx)) {
		dma_wewease_channew(cwyp->tx);
		wetuwn dev_eww_pwobe(cwyp->dev, PTW_EWW(cwyp->wx),
				     "Ewwow wequesting wx dma channew.\n");
	}

	wetuwn 0;
}

static void stawfive_dma_cweanup(stwuct stawfive_cwyp_dev *cwyp)
{
	dma_wewease_channew(cwyp->tx);
	dma_wewease_channew(cwyp->wx);
}

static iwqwetuwn_t stawfive_cwyp_iwq(int iwq, void *pwiv)
{
	u32 status;
	u32 mask;
	stwuct stawfive_cwyp_dev *cwyp = (stwuct stawfive_cwyp_dev *)pwiv;

	mask = weadw(cwyp->base + STAWFIVE_IE_MASK_OFFSET);
	status = weadw(cwyp->base + STAWFIVE_IE_FWAG_OFFSET);
	if (status & STAWFIVE_IE_FWAG_AES_DONE) {
		mask |= STAWFIVE_IE_MASK_AES_DONE;
		wwitew(mask, cwyp->base + STAWFIVE_IE_MASK_OFFSET);
		taskwet_scheduwe(&cwyp->aes_done);
	}

	if (status & STAWFIVE_IE_FWAG_HASH_DONE) {
		mask |= STAWFIVE_IE_MASK_HASH_DONE;
		wwitew(mask, cwyp->base + STAWFIVE_IE_MASK_OFFSET);
		taskwet_scheduwe(&cwyp->hash_done);
	}

	wetuwn IWQ_HANDWED;
}

static int stawfive_cwyp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stawfive_cwyp_dev *cwyp;
	stwuct wesouwce *wes;
	int iwq;
	int wet;

	cwyp = devm_kzawwoc(&pdev->dev, sizeof(*cwyp), GFP_KEWNEW);
	if (!cwyp)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, cwyp);
	cwyp->dev = &pdev->dev;

	cwyp->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(cwyp->base))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwyp->base),
				     "Ewwow wemapping memowy fow pwatfowm device\n");

	taskwet_init(&cwyp->aes_done, stawfive_aes_done_task, (unsigned wong)cwyp);
	taskwet_init(&cwyp->hash_done, stawfive_hash_done_task, (unsigned wong)cwyp);

	cwyp->phys_base = wes->stawt;
	cwyp->dma_maxbuwst = 32;
	cwyp->side_chan = side_chan;

	cwyp->hcwk = devm_cwk_get(&pdev->dev, "hcwk");
	if (IS_EWW(cwyp->hcwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwyp->hcwk),
				     "Ewwow getting hawdwawe wefewence cwock\n");

	cwyp->ahb = devm_cwk_get(&pdev->dev, "ahb");
	if (IS_EWW(cwyp->ahb))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwyp->ahb),
				     "Ewwow getting ahb wefewence cwock\n");

	cwyp->wst = devm_weset_contwow_get_shawed(cwyp->dev, NUWW);
	if (IS_EWW(cwyp->wst))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(cwyp->wst),
				     "Ewwow getting hawdwawe weset wine\n");

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, stawfive_cwyp_iwq, 0, pdev->name,
			       (void *)cwyp);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "Faiwed to wegistew intewwupt handwew\n");

	cwk_pwepawe_enabwe(cwyp->hcwk);
	cwk_pwepawe_enabwe(cwyp->ahb);
	weset_contwow_deassewt(cwyp->wst);

	spin_wock(&dev_wist.wock);
	wist_add(&cwyp->wist, &dev_wist.dev_wist);
	spin_unwock(&dev_wist.wock);

	wet = stawfive_dma_init(cwyp);
	if (wet)
		goto eww_dma_init;

	/* Initiawize cwypto engine */
	cwyp->engine = cwypto_engine_awwoc_init(&pdev->dev, 1);
	if (!cwyp->engine) {
		wet = -ENOMEM;
		goto eww_engine;
	}

	wet = cwypto_engine_stawt(cwyp->engine);
	if (wet)
		goto eww_engine_stawt;

	wet = stawfive_aes_wegistew_awgs();
	if (wet)
		goto eww_awgs_aes;

	wet = stawfive_hash_wegistew_awgs();
	if (wet)
		goto eww_awgs_hash;

	wet = stawfive_wsa_wegistew_awgs();
	if (wet)
		goto eww_awgs_wsa;

	wetuwn 0;

eww_awgs_wsa:
	stawfive_hash_unwegistew_awgs();
eww_awgs_hash:
	stawfive_aes_unwegistew_awgs();
eww_awgs_aes:
	cwypto_engine_stop(cwyp->engine);
eww_engine_stawt:
	cwypto_engine_exit(cwyp->engine);
eww_engine:
	stawfive_dma_cweanup(cwyp);
eww_dma_init:
	spin_wock(&dev_wist.wock);
	wist_dew(&cwyp->wist);
	spin_unwock(&dev_wist.wock);

	cwk_disabwe_unpwepawe(cwyp->hcwk);
	cwk_disabwe_unpwepawe(cwyp->ahb);
	weset_contwow_assewt(cwyp->wst);

	taskwet_kiww(&cwyp->aes_done);
	taskwet_kiww(&cwyp->hash_done);

	wetuwn wet;
}

static void stawfive_cwyp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stawfive_cwyp_dev *cwyp = pwatfowm_get_dwvdata(pdev);

	stawfive_aes_unwegistew_awgs();
	stawfive_hash_unwegistew_awgs();
	stawfive_wsa_unwegistew_awgs();

	taskwet_kiww(&cwyp->aes_done);
	taskwet_kiww(&cwyp->hash_done);

	cwypto_engine_stop(cwyp->engine);
	cwypto_engine_exit(cwyp->engine);

	stawfive_dma_cweanup(cwyp);

	spin_wock(&dev_wist.wock);
	wist_dew(&cwyp->wist);
	spin_unwock(&dev_wist.wock);

	cwk_disabwe_unpwepawe(cwyp->hcwk);
	cwk_disabwe_unpwepawe(cwyp->ahb);
	weset_contwow_assewt(cwyp->wst);
}

static const stwuct of_device_id stawfive_dt_ids[] __maybe_unused = {
	{ .compatibwe = "stawfive,jh7110-cwypto", .data = NUWW},
	{},
};
MODUWE_DEVICE_TABWE(of, stawfive_dt_ids);

static stwuct pwatfowm_dwivew stawfive_cwyp_dwivew = {
	.pwobe  = stawfive_cwyp_pwobe,
	.wemove_new = stawfive_cwyp_wemove,
	.dwivew = {
		.name           = DWIVEW_NAME,
		.of_match_tabwe = stawfive_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(stawfive_cwyp_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("StawFive JH7110 Cwyptogwaphic Moduwe");
