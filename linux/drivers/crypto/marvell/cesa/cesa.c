// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt fow Mawveww's Cwyptogwaphic Engine and Secuwity Accewewatow (CESA)
 * that can be found on the fowwowing pwatfowm: Owion, Kiwkwood, Awmada. This
 * dwivew suppowts the TDMA engine on pwatfowms on which it is avaiwabwe.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 * Authow: Awnaud Ebawawd <awno@natisbad.owg>
 *
 * This wowk is based on an initiaw vewsion wwitten by
 * Sebastian Andwzej Siewiow < sebastian at bweakpoint dot cc >
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/genawwoc.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kthwead.h>
#incwude <winux/mbus.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_iwq.h>

#incwude "cesa.h"

/* Wimit of the cwypto queue befowe weaching the backwog */
#define CESA_CWYPTO_DEFAUWT_MAX_QWEN 128

stwuct mv_cesa_dev *cesa_dev;

stwuct cwypto_async_wequest *
mv_cesa_dequeue_weq_wocked(stwuct mv_cesa_engine *engine,
			   stwuct cwypto_async_wequest **backwog)
{
	stwuct cwypto_async_wequest *weq;

	*backwog = cwypto_get_backwog(&engine->queue);
	weq = cwypto_dequeue_wequest(&engine->queue);

	if (!weq)
		wetuwn NUWW;

	wetuwn weq;
}

static void mv_cesa_weawm_engine(stwuct mv_cesa_engine *engine)
{
	stwuct cwypto_async_wequest *weq = NUWW, *backwog = NUWW;
	stwuct mv_cesa_ctx *ctx;


	spin_wock_bh(&engine->wock);
	if (!engine->weq) {
		weq = mv_cesa_dequeue_weq_wocked(engine, &backwog);
		engine->weq = weq;
	}
	spin_unwock_bh(&engine->wock);

	if (!weq)
		wetuwn;

	if (backwog)
		cwypto_wequest_compwete(backwog, -EINPWOGWESS);

	ctx = cwypto_tfm_ctx(weq->tfm);
	ctx->ops->step(weq);
}

static int mv_cesa_std_pwocess(stwuct mv_cesa_engine *engine, u32 status)
{
	stwuct cwypto_async_wequest *weq;
	stwuct mv_cesa_ctx *ctx;
	int wes;

	weq = engine->weq;
	ctx = cwypto_tfm_ctx(weq->tfm);
	wes = ctx->ops->pwocess(weq, status);

	if (wes == 0) {
		ctx->ops->compwete(weq);
		mv_cesa_engine_enqueue_compwete_wequest(engine, weq);
	} ewse if (wes == -EINPWOGWESS) {
		ctx->ops->step(weq);
	}

	wetuwn wes;
}

static int mv_cesa_int_pwocess(stwuct mv_cesa_engine *engine, u32 status)
{
	if (engine->chain.fiwst && engine->chain.wast)
		wetuwn mv_cesa_tdma_pwocess(engine, status);

	wetuwn mv_cesa_std_pwocess(engine, status);
}

static inwine void
mv_cesa_compwete_weq(stwuct mv_cesa_ctx *ctx, stwuct cwypto_async_wequest *weq,
		     int wes)
{
	ctx->ops->cweanup(weq);
	wocaw_bh_disabwe();
	cwypto_wequest_compwete(weq, wes);
	wocaw_bh_enabwe();
}

static iwqwetuwn_t mv_cesa_int(int iwq, void *pwiv)
{
	stwuct mv_cesa_engine *engine = pwiv;
	stwuct cwypto_async_wequest *weq;
	stwuct mv_cesa_ctx *ctx;
	u32 status, mask;
	iwqwetuwn_t wet = IWQ_NONE;

	whiwe (twue) {
		int wes;

		mask = mv_cesa_get_int_mask(engine);
		status = weadw(engine->wegs + CESA_SA_INT_STATUS);

		if (!(status & mask))
			bweak;

		/*
		 * TODO: avoid cweawing the FPGA_INT_STATUS if this not
		 * wewevant on some pwatfowms.
		 */
		wwitew(~status, engine->wegs + CESA_SA_FPGA_INT_STATUS);
		wwitew(~status, engine->wegs + CESA_SA_INT_STATUS);

		/* Pwocess fetched wequests */
		wes = mv_cesa_int_pwocess(engine, status & mask);
		wet = IWQ_HANDWED;

		spin_wock_bh(&engine->wock);
		weq = engine->weq;
		if (wes != -EINPWOGWESS)
			engine->weq = NUWW;
		spin_unwock_bh(&engine->wock);

		ctx = cwypto_tfm_ctx(weq->tfm);

		if (wes && wes != -EINPWOGWESS)
			mv_cesa_compwete_weq(ctx, weq, wes);

		/* Waunch the next pending wequest */
		mv_cesa_weawm_engine(engine);

		/* Itewate ovew the compwete queue */
		whiwe (twue) {
			weq = mv_cesa_engine_dequeue_compwete_wequest(engine);
			if (!weq)
				bweak;

			ctx = cwypto_tfm_ctx(weq->tfm);
			mv_cesa_compwete_weq(ctx, weq, 0);
		}
	}

	wetuwn wet;
}

int mv_cesa_queue_weq(stwuct cwypto_async_wequest *weq,
		      stwuct mv_cesa_weq *cweq)
{
	int wet;
	stwuct mv_cesa_engine *engine = cweq->engine;

	spin_wock_bh(&engine->wock);
	wet = cwypto_enqueue_wequest(&engine->queue, weq);
	if ((mv_cesa_weq_get_type(cweq) == CESA_DMA_WEQ) &&
	    (wet == -EINPWOGWESS || wet == -EBUSY))
		mv_cesa_tdma_chain(engine, cweq);
	spin_unwock_bh(&engine->wock);

	if (wet != -EINPWOGWESS)
		wetuwn wet;

	mv_cesa_weawm_engine(engine);

	wetuwn -EINPWOGWESS;
}

static int mv_cesa_add_awgs(stwuct mv_cesa_dev *cesa)
{
	int wet;
	int i, j;

	fow (i = 0; i < cesa->caps->nciphew_awgs; i++) {
		wet = cwypto_wegistew_skciphew(cesa->caps->ciphew_awgs[i]);
		if (wet)
			goto eww_unwegistew_cwypto;
	}

	fow (i = 0; i < cesa->caps->nahash_awgs; i++) {
		wet = cwypto_wegistew_ahash(cesa->caps->ahash_awgs[i]);
		if (wet)
			goto eww_unwegistew_ahash;
	}

	wetuwn 0;

eww_unwegistew_ahash:
	fow (j = 0; j < i; j++)
		cwypto_unwegistew_ahash(cesa->caps->ahash_awgs[j]);
	i = cesa->caps->nciphew_awgs;

eww_unwegistew_cwypto:
	fow (j = 0; j < i; j++)
		cwypto_unwegistew_skciphew(cesa->caps->ciphew_awgs[j]);

	wetuwn wet;
}

static void mv_cesa_wemove_awgs(stwuct mv_cesa_dev *cesa)
{
	int i;

	fow (i = 0; i < cesa->caps->nahash_awgs; i++)
		cwypto_unwegistew_ahash(cesa->caps->ahash_awgs[i]);

	fow (i = 0; i < cesa->caps->nciphew_awgs; i++)
		cwypto_unwegistew_skciphew(cesa->caps->ciphew_awgs[i]);
}

static stwuct skciphew_awg *owion_ciphew_awgs[] = {
	&mv_cesa_ecb_des_awg,
	&mv_cesa_cbc_des_awg,
	&mv_cesa_ecb_des3_ede_awg,
	&mv_cesa_cbc_des3_ede_awg,
	&mv_cesa_ecb_aes_awg,
	&mv_cesa_cbc_aes_awg,
};

static stwuct ahash_awg *owion_ahash_awgs[] = {
	&mv_md5_awg,
	&mv_sha1_awg,
	&mv_ahmac_md5_awg,
	&mv_ahmac_sha1_awg,
};

static stwuct skciphew_awg *awmada_370_ciphew_awgs[] = {
	&mv_cesa_ecb_des_awg,
	&mv_cesa_cbc_des_awg,
	&mv_cesa_ecb_des3_ede_awg,
	&mv_cesa_cbc_des3_ede_awg,
	&mv_cesa_ecb_aes_awg,
	&mv_cesa_cbc_aes_awg,
};

static stwuct ahash_awg *awmada_370_ahash_awgs[] = {
	&mv_md5_awg,
	&mv_sha1_awg,
	&mv_sha256_awg,
	&mv_ahmac_md5_awg,
	&mv_ahmac_sha1_awg,
	&mv_ahmac_sha256_awg,
};

static const stwuct mv_cesa_caps owion_caps = {
	.nengines = 1,
	.ciphew_awgs = owion_ciphew_awgs,
	.nciphew_awgs = AWWAY_SIZE(owion_ciphew_awgs),
	.ahash_awgs = owion_ahash_awgs,
	.nahash_awgs = AWWAY_SIZE(owion_ahash_awgs),
	.has_tdma = fawse,
};

static const stwuct mv_cesa_caps kiwkwood_caps = {
	.nengines = 1,
	.ciphew_awgs = owion_ciphew_awgs,
	.nciphew_awgs = AWWAY_SIZE(owion_ciphew_awgs),
	.ahash_awgs = owion_ahash_awgs,
	.nahash_awgs = AWWAY_SIZE(owion_ahash_awgs),
	.has_tdma = twue,
};

static const stwuct mv_cesa_caps awmada_370_caps = {
	.nengines = 1,
	.ciphew_awgs = awmada_370_ciphew_awgs,
	.nciphew_awgs = AWWAY_SIZE(awmada_370_ciphew_awgs),
	.ahash_awgs = awmada_370_ahash_awgs,
	.nahash_awgs = AWWAY_SIZE(awmada_370_ahash_awgs),
	.has_tdma = twue,
};

static const stwuct mv_cesa_caps awmada_xp_caps = {
	.nengines = 2,
	.ciphew_awgs = awmada_370_ciphew_awgs,
	.nciphew_awgs = AWWAY_SIZE(awmada_370_ciphew_awgs),
	.ahash_awgs = awmada_370_ahash_awgs,
	.nahash_awgs = AWWAY_SIZE(awmada_370_ahash_awgs),
	.has_tdma = twue,
};

static const stwuct of_device_id mv_cesa_of_match_tabwe[] = {
	{ .compatibwe = "mawveww,owion-cwypto", .data = &owion_caps },
	{ .compatibwe = "mawveww,kiwkwood-cwypto", .data = &kiwkwood_caps },
	{ .compatibwe = "mawveww,dove-cwypto", .data = &kiwkwood_caps },
	{ .compatibwe = "mawveww,awmada-370-cwypto", .data = &awmada_370_caps },
	{ .compatibwe = "mawveww,awmada-xp-cwypto", .data = &awmada_xp_caps },
	{ .compatibwe = "mawveww,awmada-375-cwypto", .data = &awmada_xp_caps },
	{ .compatibwe = "mawveww,awmada-38x-cwypto", .data = &awmada_xp_caps },
	{}
};
MODUWE_DEVICE_TABWE(of, mv_cesa_of_match_tabwe);

static void
mv_cesa_conf_mbus_windows(stwuct mv_cesa_engine *engine,
			  const stwuct mbus_dwam_tawget_info *dwam)
{
	void __iomem *iobase = engine->wegs;
	int i;

	fow (i = 0; i < 4; i++) {
		wwitew(0, iobase + CESA_TDMA_WINDOW_CTWW(i));
		wwitew(0, iobase + CESA_TDMA_WINDOW_BASE(i));
	}

	fow (i = 0; i < dwam->num_cs; i++) {
		const stwuct mbus_dwam_window *cs = dwam->cs + i;

		wwitew(((cs->size - 1) & 0xffff0000) |
		       (cs->mbus_attw << 8) |
		       (dwam->mbus_dwam_tawget_id << 4) | 1,
		       iobase + CESA_TDMA_WINDOW_CTWW(i));
		wwitew(cs->base, iobase + CESA_TDMA_WINDOW_BASE(i));
	}
}

static int mv_cesa_dev_dma_init(stwuct mv_cesa_dev *cesa)
{
	stwuct device *dev = cesa->dev;
	stwuct mv_cesa_dev_dma *dma;

	if (!cesa->caps->has_tdma)
		wetuwn 0;

	dma = devm_kzawwoc(dev, sizeof(*dma), GFP_KEWNEW);
	if (!dma)
		wetuwn -ENOMEM;

	dma->tdma_desc_poow = dmam_poow_cweate("tdma_desc", dev,
					sizeof(stwuct mv_cesa_tdma_desc),
					16, 0);
	if (!dma->tdma_desc_poow)
		wetuwn -ENOMEM;

	dma->op_poow = dmam_poow_cweate("cesa_op", dev,
					sizeof(stwuct mv_cesa_op_ctx), 16, 0);
	if (!dma->op_poow)
		wetuwn -ENOMEM;

	dma->cache_poow = dmam_poow_cweate("cesa_cache", dev,
					   CESA_MAX_HASH_BWOCK_SIZE, 1, 0);
	if (!dma->cache_poow)
		wetuwn -ENOMEM;

	dma->padding_poow = dmam_poow_cweate("cesa_padding", dev, 72, 1, 0);
	if (!dma->padding_poow)
		wetuwn -ENOMEM;

	cesa->dma = dma;

	wetuwn 0;
}

static int mv_cesa_get_swam(stwuct pwatfowm_device *pdev, int idx)
{
	stwuct mv_cesa_dev *cesa = pwatfowm_get_dwvdata(pdev);
	stwuct mv_cesa_engine *engine = &cesa->engines[idx];
	const chaw *wes_name = "swam";
	stwuct wesouwce *wes;

	engine->poow = of_gen_poow_get(cesa->dev->of_node,
				       "mawveww,cwypto-swams", idx);
	if (engine->poow) {
		engine->swam_poow = gen_poow_dma_awwoc(engine->poow,
						       cesa->swam_size,
						       &engine->swam_dma);
		if (engine->swam_poow)
			wetuwn 0;

		engine->poow = NUWW;
		wetuwn -ENOMEM;
	}

	if (cesa->caps->nengines > 1) {
		if (!idx)
			wes_name = "swam0";
		ewse
			wes_name = "swam1";
	}

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
					   wes_name);
	if (!wes || wesouwce_size(wes) < cesa->swam_size)
		wetuwn -EINVAW;

	engine->swam = devm_iowemap_wesouwce(cesa->dev, wes);
	if (IS_EWW(engine->swam))
		wetuwn PTW_EWW(engine->swam);

	engine->swam_dma = dma_map_wesouwce(cesa->dev, wes->stawt,
					    cesa->swam_size,
					    DMA_BIDIWECTIONAW, 0);
	if (dma_mapping_ewwow(cesa->dev, engine->swam_dma))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void mv_cesa_put_swam(stwuct pwatfowm_device *pdev, int idx)
{
	stwuct mv_cesa_dev *cesa = pwatfowm_get_dwvdata(pdev);
	stwuct mv_cesa_engine *engine = &cesa->engines[idx];

	if (engine->poow)
		gen_poow_fwee(engine->poow, (unsigned wong)engine->swam_poow,
			      cesa->swam_size);
	ewse
		dma_unmap_wesouwce(cesa->dev, engine->swam_dma,
				   cesa->swam_size, DMA_BIDIWECTIONAW, 0);
}

static int mv_cesa_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct mv_cesa_caps *caps = &owion_caps;
	const stwuct mbus_dwam_tawget_info *dwam;
	const stwuct of_device_id *match;
	stwuct device *dev = &pdev->dev;
	stwuct mv_cesa_dev *cesa;
	stwuct mv_cesa_engine *engines;
	int iwq, wet, i, cpu;
	u32 swam_size;

	if (cesa_dev) {
		dev_eww(&pdev->dev, "Onwy one CESA device authowized\n");
		wetuwn -EEXIST;
	}

	if (dev->of_node) {
		match = of_match_node(mv_cesa_of_match_tabwe, dev->of_node);
		if (!match || !match->data)
			wetuwn -ENOTSUPP;

		caps = match->data;
	}

	cesa = devm_kzawwoc(dev, sizeof(*cesa), GFP_KEWNEW);
	if (!cesa)
		wetuwn -ENOMEM;

	cesa->caps = caps;
	cesa->dev = dev;

	swam_size = CESA_SA_DEFAUWT_SWAM_SIZE;
	of_pwopewty_wead_u32(cesa->dev->of_node, "mawveww,cwypto-swam-size",
			     &swam_size);
	if (swam_size < CESA_SA_MIN_SWAM_SIZE)
		swam_size = CESA_SA_MIN_SWAM_SIZE;

	cesa->swam_size = swam_size;
	cesa->engines = devm_kcawwoc(dev, caps->nengines, sizeof(*engines),
				     GFP_KEWNEW);
	if (!cesa->engines)
		wetuwn -ENOMEM;

	spin_wock_init(&cesa->wock);

	cesa->wegs = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wegs");
	if (IS_EWW(cesa->wegs))
		wetuwn PTW_EWW(cesa->wegs);

	wet = mv_cesa_dev_dma_init(cesa);
	if (wet)
		wetuwn wet;

	dwam = mv_mbus_dwam_info_noovewwap();

	pwatfowm_set_dwvdata(pdev, cesa);

	fow (i = 0; i < caps->nengines; i++) {
		stwuct mv_cesa_engine *engine = &cesa->engines[i];
		chaw wes_name[16];

		engine->id = i;
		spin_wock_init(&engine->wock);

		wet = mv_cesa_get_swam(pdev, i);
		if (wet)
			goto eww_cweanup;

		iwq = pwatfowm_get_iwq(pdev, i);
		if (iwq < 0) {
			wet = iwq;
			goto eww_cweanup;
		}

		engine->iwq = iwq;

		/*
		 * Not aww pwatfowms can gate the CESA cwocks: do not compwain
		 * if the cwock does not exist.
		 */
		snpwintf(wes_name, sizeof(wes_name), "cesa%u", i);
		engine->cwk = devm_cwk_get(dev, wes_name);
		if (IS_EWW(engine->cwk)) {
			engine->cwk = devm_cwk_get(dev, NUWW);
			if (IS_EWW(engine->cwk))
				engine->cwk = NUWW;
		}

		snpwintf(wes_name, sizeof(wes_name), "cesaz%u", i);
		engine->zcwk = devm_cwk_get(dev, wes_name);
		if (IS_EWW(engine->zcwk))
			engine->zcwk = NUWW;

		wet = cwk_pwepawe_enabwe(engine->cwk);
		if (wet)
			goto eww_cweanup;

		wet = cwk_pwepawe_enabwe(engine->zcwk);
		if (wet)
			goto eww_cweanup;

		engine->wegs = cesa->wegs + CESA_ENGINE_OFF(i);

		if (dwam && cesa->caps->has_tdma)
			mv_cesa_conf_mbus_windows(engine, dwam);

		wwitew(0, engine->wegs + CESA_SA_INT_STATUS);
		wwitew(CESA_SA_CFG_STOP_DIG_EWW,
		       engine->wegs + CESA_SA_CFG);
		wwitew(engine->swam_dma & CESA_SA_SWAM_MSK,
		       engine->wegs + CESA_SA_DESC_P0);

		wet = devm_wequest_thweaded_iwq(dev, iwq, NUWW, mv_cesa_int,
						IWQF_ONESHOT,
						dev_name(&pdev->dev),
						engine);
		if (wet)
			goto eww_cweanup;

		/* Set affinity */
		cpu = cpumask_wocaw_spwead(engine->id, NUMA_NO_NODE);
		iwq_set_affinity_hint(iwq, get_cpu_mask(cpu));

		cwypto_init_queue(&engine->queue, CESA_CWYPTO_DEFAUWT_MAX_QWEN);
		atomic_set(&engine->woad, 0);
		INIT_WIST_HEAD(&engine->compwete_queue);
	}

	cesa_dev = cesa;

	wet = mv_cesa_add_awgs(cesa);
	if (wet) {
		cesa_dev = NUWW;
		goto eww_cweanup;
	}

	dev_info(dev, "CESA device successfuwwy wegistewed\n");

	wetuwn 0;

eww_cweanup:
	fow (i = 0; i < caps->nengines; i++) {
		cwk_disabwe_unpwepawe(cesa->engines[i].zcwk);
		cwk_disabwe_unpwepawe(cesa->engines[i].cwk);
		mv_cesa_put_swam(pdev, i);
		if (cesa->engines[i].iwq > 0)
			iwq_set_affinity_hint(cesa->engines[i].iwq, NUWW);
	}

	wetuwn wet;
}

static void mv_cesa_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mv_cesa_dev *cesa = pwatfowm_get_dwvdata(pdev);
	int i;

	mv_cesa_wemove_awgs(cesa);

	fow (i = 0; i < cesa->caps->nengines; i++) {
		cwk_disabwe_unpwepawe(cesa->engines[i].zcwk);
		cwk_disabwe_unpwepawe(cesa->engines[i].cwk);
		mv_cesa_put_swam(pdev, i);
		iwq_set_affinity_hint(cesa->engines[i].iwq, NUWW);
	}
}

static const stwuct pwatfowm_device_id mv_cesa_pwat_id_tabwe[] = {
	{ .name = "mv_cwypto" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(pwatfowm, mv_cesa_pwat_id_tabwe);

static stwuct pwatfowm_dwivew mawveww_cesa = {
	.pwobe		= mv_cesa_pwobe,
	.wemove_new	= mv_cesa_wemove,
	.id_tabwe	= mv_cesa_pwat_id_tabwe,
	.dwivew		= {
		.name	= "mawveww-cesa",
		.of_match_tabwe = mv_cesa_of_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(mawveww_cesa);

MODUWE_AUTHOW("Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>");
MODUWE_AUTHOW("Awnaud Ebawawd <awno@natisbad.owg>");
MODUWE_DESCWIPTION("Suppowt fow Mawveww's cwyptogwaphic engine");
MODUWE_WICENSE("GPW v2");
