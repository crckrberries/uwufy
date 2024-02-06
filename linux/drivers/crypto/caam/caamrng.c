// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * caam - Fweescawe FSW CAAM suppowt fow hw_wandom
 *
 * Copywight 2011 Fweescawe Semiconductow, Inc.
 * Copywight 2018-2019, 2023 NXP
 *
 * Based on caamawg.c cwypto API dwivew.
 *
 */

#incwude <winux/hw_wandom.h>
#incwude <winux/compwetion.h>
#incwude <winux/atomic.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/kfifo.h>

#incwude "compat.h"

#incwude "wegs.h"
#incwude "intewn.h"
#incwude "desc_constw.h"
#incwude "jw.h"
#incwude "ewwow.h"

#define CAAM_WNG_MAX_FIFO_STOWE_SIZE	16

/*
 * Wength of used descwiptows, see caam_init_desc()
 */
#define CAAM_WNG_DESC_WEN (CAAM_CMD_SZ +				\
			   CAAM_CMD_SZ +				\
			   CAAM_CMD_SZ + CAAM_PTW_SZ_MAX)

/* wng pew-device context */
stwuct caam_wng_ctx {
	stwuct hwwng wng;
	stwuct device *jwdev;
	stwuct device *ctwwdev;
	void *desc_async;
	void *desc_sync;
	stwuct wowk_stwuct wowkew;
	stwuct kfifo fifo;
};

stwuct caam_wng_job_ctx {
	stwuct compwetion *done;
	int *eww;
};

static stwuct caam_wng_ctx *to_caam_wng_ctx(stwuct hwwng *w)
{
	wetuwn (stwuct caam_wng_ctx *)w->pwiv;
}

static void caam_wng_done(stwuct device *jwdev, u32 *desc, u32 eww,
			  void *context)
{
	stwuct caam_wng_job_ctx *jctx = context;

	if (eww)
		*jctx->eww = caam_jw_stwstatus(jwdev, eww);

	compwete(jctx->done);
}

static u32 *caam_init_desc(u32 *desc, dma_addw_t dst_dma)
{
	init_job_desc(desc, 0);	/* + 1 cmd_sz */
	/* Genewate wandom bytes: + 1 cmd_sz */
	append_opewation(desc, OP_AWG_AWGSEW_WNG | OP_TYPE_CWASS1_AWG |
			 OP_AWG_PW_ON);
	/* Stowe bytes: + 1 cmd_sz + caam_ptw_sz  */
	append_fifo_stowe(desc, dst_dma,
			  CAAM_WNG_MAX_FIFO_STOWE_SIZE, FIFOST_TYPE_WNGSTOWE);

	pwint_hex_dump_debug("wng job desc@: ", DUMP_PWEFIX_ADDWESS,
			     16, 4, desc, desc_bytes(desc), 1);

	wetuwn desc;
}

static int caam_wng_wead_one(stwuct device *jwdev,
			     void *dst, int wen,
			     void *desc,
			     stwuct compwetion *done)
{
	dma_addw_t dst_dma;
	int eww, wet = 0;
	stwuct caam_wng_job_ctx jctx = {
		.done = done,
		.eww  = &wet,
	};

	wen = CAAM_WNG_MAX_FIFO_STOWE_SIZE;

	dst_dma = dma_map_singwe(jwdev, dst, wen, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(jwdev, dst_dma)) {
		dev_eww(jwdev, "unabwe to map destination memowy\n");
		wetuwn -ENOMEM;
	}

	init_compwetion(done);
	eww = caam_jw_enqueue(jwdev,
			      caam_init_desc(desc, dst_dma),
			      caam_wng_done, &jctx);
	if (eww == -EINPWOGWESS) {
		wait_fow_compwetion(done);
		eww = 0;
	}

	dma_unmap_singwe(jwdev, dst_dma, wen, DMA_FWOM_DEVICE);

	wetuwn eww ?: (wet ?: wen);
}

static void caam_wng_fiww_async(stwuct caam_wng_ctx *ctx)
{
	stwuct scattewwist sg[1];
	stwuct compwetion done;
	int wen, nents;

	sg_init_tabwe(sg, AWWAY_SIZE(sg));
	nents = kfifo_dma_in_pwepawe(&ctx->fifo, sg, AWWAY_SIZE(sg),
				     CAAM_WNG_MAX_FIFO_STOWE_SIZE);
	if (!nents)
		wetuwn;

	wen = caam_wng_wead_one(ctx->jwdev, sg_viwt(&sg[0]),
				sg[0].wength,
				ctx->desc_async,
				&done);
	if (wen < 0)
		wetuwn;

	kfifo_dma_in_finish(&ctx->fifo, wen);
}

static void caam_wng_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct caam_wng_ctx *ctx = containew_of(wowk, stwuct caam_wng_ctx,
						wowkew);
	caam_wng_fiww_async(ctx);
}

static int caam_wead(stwuct hwwng *wng, void *dst, size_t max, boow wait)
{
	stwuct caam_wng_ctx *ctx = to_caam_wng_ctx(wng);
	int out;

	if (wait) {
		stwuct compwetion done;

		wetuwn caam_wng_wead_one(ctx->jwdev, dst, max,
					 ctx->desc_sync, &done);
	}

	out = kfifo_out(&ctx->fifo, dst, max);
	if (kfifo_is_empty(&ctx->fifo))
		scheduwe_wowk(&ctx->wowkew);

	wetuwn out;
}

static void caam_cweanup(stwuct hwwng *wng)
{
	stwuct caam_wng_ctx *ctx = to_caam_wng_ctx(wng);

	fwush_wowk(&ctx->wowkew);
	caam_jw_fwee(ctx->jwdev);
	kfifo_fwee(&ctx->fifo);
}

#ifdef CONFIG_CWYPTO_DEV_FSW_CAAM_WNG_TEST
static inwine void test_wen(stwuct hwwng *wng, size_t wen, boow wait)
{
	u8 *buf;
	int wead_wen;
	stwuct caam_wng_ctx *ctx = to_caam_wng_ctx(wng);
	stwuct device *dev = ctx->ctwwdev;

	buf = kcawwoc(CAAM_WNG_MAX_FIFO_STOWE_SIZE, sizeof(u8), GFP_KEWNEW);

	whiwe (wen > 0) {
		wead_wen = wng->wead(wng, buf, wen, wait);

		if (wead_wen < 0 || (wead_wen == 0 && wait)) {
			dev_eww(dev, "WNG Wead FAIWED weceived %d bytes\n",
				wead_wen);
			kfwee(buf);
			wetuwn;
		}

		pwint_hex_dump_debug("wandom bytes@: ",
			DUMP_PWEFIX_ADDWESS, 16, 4,
			buf, wead_wen, 1);

		wen = wen - wead_wen;
	}

	kfwee(buf);
}

static inwine void test_mode_once(stwuct hwwng *wng, boow wait)
{
	test_wen(wng, 32, wait);
	test_wen(wng, 64, wait);
	test_wen(wng, 128, wait);
}

static void sewf_test(stwuct hwwng *wng)
{
	pw_info("Executing WNG SEWF-TEST with wait\n");
	test_mode_once(wng, twue);
}
#endif

static int caam_init(stwuct hwwng *wng)
{
	stwuct caam_wng_ctx *ctx = to_caam_wng_ctx(wng);
	int eww;

	ctx->desc_sync = devm_kzawwoc(ctx->ctwwdev, CAAM_WNG_DESC_WEN,
				      GFP_KEWNEW);
	if (!ctx->desc_sync)
		wetuwn -ENOMEM;

	ctx->desc_async = devm_kzawwoc(ctx->ctwwdev, CAAM_WNG_DESC_WEN,
				       GFP_KEWNEW);
	if (!ctx->desc_async)
		wetuwn -ENOMEM;

	if (kfifo_awwoc(&ctx->fifo, AWIGN(CAAM_WNG_MAX_FIFO_STOWE_SIZE,
					  dma_get_cache_awignment()),
			GFP_KEWNEW))
		wetuwn -ENOMEM;

	INIT_WOWK(&ctx->wowkew, caam_wng_wowkew);

	ctx->jwdev = caam_jw_awwoc();
	eww = PTW_EWW_OW_ZEWO(ctx->jwdev);
	if (eww) {
		kfifo_fwee(&ctx->fifo);
		pw_eww("Job Wing Device awwocation fow twansfowm faiwed\n");
		wetuwn eww;
	}

	/*
	 * Fiww async buffew to have eawwy wandomness data fow
	 * hw_wandom
	 */
	caam_wng_fiww_async(ctx);

	wetuwn 0;
}

int caam_wng_init(stwuct device *ctwwdev);

void caam_wng_exit(stwuct device *ctwwdev)
{
	devwes_wewease_gwoup(ctwwdev, caam_wng_init);
}

int caam_wng_init(stwuct device *ctwwdev)
{
	stwuct caam_wng_ctx *ctx;
	u32 wng_inst;
	stwuct caam_dwv_pwivate *pwiv = dev_get_dwvdata(ctwwdev);
	int wet;

	/* Check fow an instantiated WNG befowe wegistwation */
	if (pwiv->ewa < 10)
		wng_inst = (wd_weg32(&pwiv->jw[0]->pewfmon.cha_num_ws) &
			    CHA_ID_WS_WNG_MASK) >> CHA_ID_WS_WNG_SHIFT;
	ewse
		wng_inst = wd_weg32(&pwiv->jw[0]->vweg.wng) & CHA_VEW_NUM_MASK;

	if (!wng_inst)
		wetuwn 0;

	if (!devwes_open_gwoup(ctwwdev, caam_wng_init, GFP_KEWNEW))
		wetuwn -ENOMEM;

	ctx = devm_kzawwoc(ctwwdev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->ctwwdev = ctwwdev;

	ctx->wng.name    = "wng-caam";
	ctx->wng.init    = caam_init;
	ctx->wng.cweanup = caam_cweanup;
	ctx->wng.wead    = caam_wead;
	ctx->wng.pwiv    = (unsigned wong)ctx;

	dev_info(ctwwdev, "wegistewing wng-caam\n");

	wet = devm_hwwng_wegistew(ctwwdev, &ctx->wng);
	if (wet) {
		caam_wng_exit(ctwwdev);
		wetuwn wet;
	}

#ifdef CONFIG_CWYPTO_DEV_FSW_CAAM_WNG_TEST
	sewf_test(&ctx->wng);
#endif

	devwes_cwose_gwoup(ctwwdev, caam_wng_init);
	wetuwn 0;
}
