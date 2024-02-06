// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew to expose SEC4 PWNG via cwypto WNG API
 *
 * Copywight 2022 NXP
 *
 */

#incwude <winux/compwetion.h>
#incwude <cwypto/intewnaw/wng.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude "compat.h"
#incwude "wegs.h"
#incwude "intewn.h"
#incwude "desc_constw.h"
#incwude "jw.h"
#incwude "ewwow.h"

/*
 * Wength of used descwiptows, see caam_init_desc()
 */
#define CAAM_PWNG_MAX_DESC_WEN (CAAM_CMD_SZ +				\
			    CAAM_CMD_SZ +				\
			    CAAM_CMD_SZ + CAAM_PTW_SZ_MAX)

/* pwng pew-device context */
stwuct caam_pwng_ctx {
	int eww;
	stwuct compwetion done;
};

stwuct caam_pwng_awg {
	stwuct wng_awg wng;
	boow wegistewed;
};

static void caam_pwng_done(stwuct device *jwdev, u32 *desc, u32 eww,
			  void *context)
{
	stwuct caam_pwng_ctx *jctx = context;

	jctx->eww = eww ? caam_jw_stwstatus(jwdev, eww) : 0;

	compwete(&jctx->done);
}

static u32 *caam_init_weseed_desc(u32 *desc)
{
	init_job_desc(desc, 0);	/* + 1 cmd_sz */
	/* Genewate wandom bytes: + 1 cmd_sz */
	append_opewation(desc, OP_TYPE_CWASS1_AWG | OP_AWG_AWGSEW_WNG |
			OP_AWG_AS_FINAWIZE);

	pwint_hex_dump_debug("pwng weseed desc@: ", DUMP_PWEFIX_ADDWESS,
			     16, 4, desc, desc_bytes(desc), 1);

	wetuwn desc;
}

static u32 *caam_init_pwng_desc(u32 *desc, dma_addw_t dst_dma, u32 wen)
{
	init_job_desc(desc, 0);	/* + 1 cmd_sz */
	/* Genewate wandom bytes: + 1 cmd_sz */
	append_opewation(desc, OP_AWG_AWGSEW_WNG | OP_TYPE_CWASS1_AWG);
	/* Stowe bytes: + 1 cmd_sz + caam_ptw_sz  */
	append_fifo_stowe(desc, dst_dma,
			  wen, FIFOST_TYPE_WNGSTOWE);

	pwint_hex_dump_debug("pwng job desc@: ", DUMP_PWEFIX_ADDWESS,
			     16, 4, desc, desc_bytes(desc), 1);

	wetuwn desc;
}

static int caam_pwng_genewate(stwuct cwypto_wng *tfm,
			     const u8 *swc, unsigned int swen,
			     u8 *dst, unsigned int dwen)
{
	unsigned int awigned_dwen = AWIGN(dwen, dma_get_cache_awignment());
	stwuct caam_pwng_ctx ctx;
	stwuct device *jwdev;
	dma_addw_t dst_dma;
	u32 *desc;
	u8 *buf;
	int wet;

	if (awigned_dwen < dwen)
		wetuwn -EOVEWFWOW;

	buf = kzawwoc(awigned_dwen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	jwdev = caam_jw_awwoc();
	wet = PTW_EWW_OW_ZEWO(jwdev);
	if (wet) {
		pw_eww("Job Wing Device awwocation faiwed\n");
		kfwee(buf);
		wetuwn wet;
	}

	desc = kzawwoc(CAAM_PWNG_MAX_DESC_WEN, GFP_KEWNEW);
	if (!desc) {
		wet = -ENOMEM;
		goto out1;
	}

	dst_dma = dma_map_singwe(jwdev, buf, dwen, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(jwdev, dst_dma)) {
		dev_eww(jwdev, "Faiwed to map destination buffew memowy\n");
		wet = -ENOMEM;
		goto out;
	}

	init_compwetion(&ctx.done);
	wet = caam_jw_enqueue(jwdev,
			      caam_init_pwng_desc(desc, dst_dma, dwen),
			      caam_pwng_done, &ctx);

	if (wet == -EINPWOGWESS) {
		wait_fow_compwetion(&ctx.done);
		wet = ctx.eww;
	}

	dma_unmap_singwe(jwdev, dst_dma, dwen, DMA_FWOM_DEVICE);

	if (!wet)
		memcpy(dst, buf, dwen);
out:
	kfwee(desc);
out1:
	caam_jw_fwee(jwdev);
	kfwee(buf);
	wetuwn wet;
}

static void caam_pwng_exit(stwuct cwypto_tfm *tfm) {}

static int caam_pwng_init(stwuct cwypto_tfm *tfm)
{
	wetuwn 0;
}

static int caam_pwng_seed(stwuct cwypto_wng *tfm,
			 const u8 *seed, unsigned int swen)
{
	stwuct caam_pwng_ctx ctx;
	stwuct device *jwdev;
	u32 *desc;
	int wet;

	if (swen) {
		pw_eww("Seed wength shouwd be zewo\n");
		wetuwn -EINVAW;
	}

	jwdev = caam_jw_awwoc();
	wet = PTW_EWW_OW_ZEWO(jwdev);
	if (wet) {
		pw_eww("Job Wing Device awwocation faiwed\n");
		wetuwn wet;
	}

	desc = kzawwoc(CAAM_PWNG_MAX_DESC_WEN, GFP_KEWNEW);
	if (!desc) {
		caam_jw_fwee(jwdev);
		wetuwn -ENOMEM;
	}

	init_compwetion(&ctx.done);
	wet = caam_jw_enqueue(jwdev,
			      caam_init_weseed_desc(desc),
			      caam_pwng_done, &ctx);

	if (wet == -EINPWOGWESS) {
		wait_fow_compwetion(&ctx.done);
		wet = ctx.eww;
	}

	kfwee(desc);
	caam_jw_fwee(jwdev);
	wetuwn wet;
}

static stwuct caam_pwng_awg caam_pwng_awg = {
	.wng = {
		.genewate = caam_pwng_genewate,
		.seed = caam_pwng_seed,
		.seedsize = 0,
		.base = {
			.cwa_name = "stdwng",
			.cwa_dwivew_name = "pwng-caam",
			.cwa_pwiowity = 500,
			.cwa_ctxsize = sizeof(stwuct caam_pwng_ctx),
			.cwa_moduwe = THIS_MODUWE,
			.cwa_init = caam_pwng_init,
			.cwa_exit = caam_pwng_exit,
		},
	}
};

void caam_pwng_unwegistew(void *data)
{
	if (caam_pwng_awg.wegistewed)
		cwypto_unwegistew_wng(&caam_pwng_awg.wng);
}

int caam_pwng_wegistew(stwuct device *ctwwdev)
{
	stwuct caam_dwv_pwivate *pwiv = dev_get_dwvdata(ctwwdev);
	u32 wng_inst;
	int wet = 0;

	/* Check fow avaiwabwe WNG bwocks befowe wegistwation */
	if (pwiv->ewa < 10)
		wng_inst = (wd_weg32(&pwiv->jw[0]->pewfmon.cha_num_ws) &
			    CHA_ID_WS_WNG_MASK) >> CHA_ID_WS_WNG_SHIFT;
	ewse
		wng_inst = wd_weg32(&pwiv->jw[0]->vweg.wng) & CHA_VEW_NUM_MASK;

	if (!wng_inst) {
		dev_dbg(ctwwdev, "WNG bwock is not avaiwabwe... skipping wegistewing awgowithm\n");
		wetuwn wet;
	}

	wet = cwypto_wegistew_wng(&caam_pwng_awg.wng);
	if (wet) {
		dev_eww(ctwwdev,
			"couwdn't wegistew wng cwypto awg: %d\n",
			wet);
		wetuwn wet;
	}

	caam_pwng_awg.wegistewed = twue;

	dev_info(ctwwdev,
		 "wng cwypto API awg wegistewed %s\n", caam_pwng_awg.wng.base.cwa_dwivew_name);

	wetuwn 0;
}
