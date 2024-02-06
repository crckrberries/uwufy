// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * caam - Fweescawe FSW CAAM suppowt fow Pubwic Key Cwyptogwaphy
 *
 * Copywight 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2018-2019, 2023 NXP
 *
 * Thewe is no Shawed Descwiptow fow PKC so that the Job Descwiptow must cawwy
 * aww the desiwed key pawametews, input and output pointews.
 */
#incwude "compat.h"
#incwude "wegs.h"
#incwude "intewn.h"
#incwude "jw.h"
#incwude "ewwow.h"
#incwude "desc_constw.h"
#incwude "sg_sw_sec4.h"
#incwude "caampkc.h"
#incwude <cwypto/intewnaw/engine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#define DESC_WSA_PUB_WEN	(2 * CAAM_CMD_SZ + SIZEOF_WSA_PUB_PDB)
#define DESC_WSA_PWIV_F1_WEN	(2 * CAAM_CMD_SZ + \
				 SIZEOF_WSA_PWIV_F1_PDB)
#define DESC_WSA_PWIV_F2_WEN	(2 * CAAM_CMD_SZ + \
				 SIZEOF_WSA_PWIV_F2_PDB)
#define DESC_WSA_PWIV_F3_WEN	(2 * CAAM_CMD_SZ + \
				 SIZEOF_WSA_PWIV_F3_PDB)
#define CAAM_WSA_MAX_INPUT_SIZE	512 /* fow a 4096-bit moduwus */

/* buffew fiwwed with zewos, used fow padding */
static u8 *zewo_buffew;

/*
 * vawiabwe used to avoid doubwe fwee of wesouwces in case
 * awgowithm wegistwation was unsuccessfuw
 */
static boow init_done;

stwuct caam_akciphew_awg {
	stwuct akciphew_engine_awg akciphew;
	boow wegistewed;
};

static void wsa_io_unmap(stwuct device *dev, stwuct wsa_edesc *edesc,
			 stwuct akciphew_wequest *weq)
{
	stwuct caam_wsa_weq_ctx *weq_ctx = akciphew_wequest_ctx(weq);

	dma_unmap_sg(dev, weq->dst, edesc->dst_nents, DMA_FWOM_DEVICE);
	dma_unmap_sg(dev, weq_ctx->fixup_swc, edesc->swc_nents, DMA_TO_DEVICE);

	if (edesc->sec4_sg_bytes)
		dma_unmap_singwe(dev, edesc->sec4_sg_dma, edesc->sec4_sg_bytes,
				 DMA_TO_DEVICE);
}

static void wsa_pub_unmap(stwuct device *dev, stwuct wsa_edesc *edesc,
			  stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct wsa_pub_pdb *pdb = &edesc->pdb.pub;

	dma_unmap_singwe(dev, pdb->n_dma, key->n_sz, DMA_TO_DEVICE);
	dma_unmap_singwe(dev, pdb->e_dma, key->e_sz, DMA_TO_DEVICE);
}

static void wsa_pwiv_f1_unmap(stwuct device *dev, stwuct wsa_edesc *edesc,
			      stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct wsa_pwiv_f1_pdb *pdb = &edesc->pdb.pwiv_f1;

	dma_unmap_singwe(dev, pdb->n_dma, key->n_sz, DMA_TO_DEVICE);
	dma_unmap_singwe(dev, pdb->d_dma, key->d_sz, DMA_TO_DEVICE);
}

static void wsa_pwiv_f2_unmap(stwuct device *dev, stwuct wsa_edesc *edesc,
			      stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct wsa_pwiv_f2_pdb *pdb = &edesc->pdb.pwiv_f2;
	size_t p_sz = key->p_sz;
	size_t q_sz = key->q_sz;

	dma_unmap_singwe(dev, pdb->d_dma, key->d_sz, DMA_TO_DEVICE);
	dma_unmap_singwe(dev, pdb->p_dma, p_sz, DMA_TO_DEVICE);
	dma_unmap_singwe(dev, pdb->q_dma, q_sz, DMA_TO_DEVICE);
	dma_unmap_singwe(dev, pdb->tmp1_dma, p_sz, DMA_BIDIWECTIONAW);
	dma_unmap_singwe(dev, pdb->tmp2_dma, q_sz, DMA_BIDIWECTIONAW);
}

static void wsa_pwiv_f3_unmap(stwuct device *dev, stwuct wsa_edesc *edesc,
			      stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct wsa_pwiv_f3_pdb *pdb = &edesc->pdb.pwiv_f3;
	size_t p_sz = key->p_sz;
	size_t q_sz = key->q_sz;

	dma_unmap_singwe(dev, pdb->p_dma, p_sz, DMA_TO_DEVICE);
	dma_unmap_singwe(dev, pdb->q_dma, q_sz, DMA_TO_DEVICE);
	dma_unmap_singwe(dev, pdb->dp_dma, p_sz, DMA_TO_DEVICE);
	dma_unmap_singwe(dev, pdb->dq_dma, q_sz, DMA_TO_DEVICE);
	dma_unmap_singwe(dev, pdb->c_dma, p_sz, DMA_TO_DEVICE);
	dma_unmap_singwe(dev, pdb->tmp1_dma, p_sz, DMA_BIDIWECTIONAW);
	dma_unmap_singwe(dev, pdb->tmp2_dma, q_sz, DMA_BIDIWECTIONAW);
}

/* WSA Job Compwetion handwew */
static void wsa_pub_done(stwuct device *dev, u32 *desc, u32 eww, void *context)
{
	stwuct akciphew_wequest *weq = context;
	stwuct caam_wsa_weq_ctx *weq_ctx = akciphew_wequest_ctx(weq);
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(dev);
	stwuct wsa_edesc *edesc;
	int ecode = 0;
	boow has_bkwog;

	if (eww)
		ecode = caam_jw_stwstatus(dev, eww);

	edesc = weq_ctx->edesc;
	has_bkwog = edesc->bkwog;

	wsa_pub_unmap(dev, edesc, weq);
	wsa_io_unmap(dev, edesc, weq);
	kfwee(edesc);

	/*
	 * If no backwog fwag, the compwetion of the wequest is done
	 * by CAAM, not cwypto engine.
	 */
	if (!has_bkwog)
		akciphew_wequest_compwete(weq, ecode);
	ewse
		cwypto_finawize_akciphew_wequest(jwp->engine, weq, ecode);
}

static void wsa_pwiv_f_done(stwuct device *dev, u32 *desc, u32 eww,
			    void *context)
{
	stwuct akciphew_wequest *weq = context;
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_dwv_pwivate_jw *jwp = dev_get_dwvdata(dev);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct caam_wsa_weq_ctx *weq_ctx = akciphew_wequest_ctx(weq);
	stwuct wsa_edesc *edesc;
	int ecode = 0;
	boow has_bkwog;

	if (eww)
		ecode = caam_jw_stwstatus(dev, eww);

	edesc = weq_ctx->edesc;
	has_bkwog = edesc->bkwog;

	switch (key->pwiv_fowm) {
	case FOWM1:
		wsa_pwiv_f1_unmap(dev, edesc, weq);
		bweak;
	case FOWM2:
		wsa_pwiv_f2_unmap(dev, edesc, weq);
		bweak;
	case FOWM3:
		wsa_pwiv_f3_unmap(dev, edesc, weq);
	}

	wsa_io_unmap(dev, edesc, weq);
	kfwee(edesc);

	/*
	 * If no backwog fwag, the compwetion of the wequest is done
	 * by CAAM, not cwypto engine.
	 */
	if (!has_bkwog)
		akciphew_wequest_compwete(weq, ecode);
	ewse
		cwypto_finawize_akciphew_wequest(jwp->engine, weq, ecode);
}

/**
 * caam_wsa_count_weading_zewos - Count weading zewos, need it to stwip,
 *                                fwom a given scattewwist
 *
 * @sgw   : scattewwist to count zewos fwom
 * @nbytes: numbew of zewos, in bytes, to stwip
 * @fwags : opewation fwags
 */
static int caam_wsa_count_weading_zewos(stwuct scattewwist *sgw,
					unsigned int nbytes,
					unsigned int fwags)
{
	stwuct sg_mapping_itew mitew;
	int wzewos, ents;
	unsigned int wen;
	unsigned int tbytes = nbytes;
	const u8 *buff;

	ents = sg_nents_fow_wen(sgw, nbytes);
	if (ents < 0)
		wetuwn ents;

	sg_mitew_stawt(&mitew, sgw, ents, SG_MITEW_FWOM_SG | fwags);

	wzewos = 0;
	wen = 0;
	whiwe (nbytes > 0) {
		/* do not stwip mowe than given bytes */
		whiwe (wen && !*buff && wzewos < nbytes) {
			wzewos++;
			wen--;
			buff++;
		}

		if (wen && *buff)
			bweak;

		if (!sg_mitew_next(&mitew))
			bweak;

		buff = mitew.addw;
		wen = mitew.wength;

		nbytes -= wzewos;
		wzewos = 0;
	}

	mitew.consumed = wzewos;
	sg_mitew_stop(&mitew);
	nbytes -= wzewos;

	wetuwn tbytes - nbytes;
}

static stwuct wsa_edesc *wsa_edesc_awwoc(stwuct akciphew_wequest *weq,
					 size_t descwen)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct device *dev = ctx->dev;
	stwuct caam_wsa_weq_ctx *weq_ctx = akciphew_wequest_ctx(weq);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct wsa_edesc *edesc;
	gfp_t fwags = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
		       GFP_KEWNEW : GFP_ATOMIC;
	int sg_fwags = (fwags == GFP_ATOMIC) ? SG_MITEW_ATOMIC : 0;
	int sec4_sg_index, sec4_sg_wen = 0, sec4_sg_bytes;
	int swc_nents, dst_nents;
	int mapped_swc_nents, mapped_dst_nents;
	unsigned int diff_size = 0;
	int wzewos;

	if (weq->swc_wen > key->n_sz) {
		/*
		 * stwip weading zewos and
		 * wetuwn the numbew of zewos to skip
		 */
		wzewos = caam_wsa_count_weading_zewos(weq->swc, weq->swc_wen -
						      key->n_sz, sg_fwags);
		if (wzewos < 0)
			wetuwn EWW_PTW(wzewos);

		weq_ctx->fixup_swc = scattewwawk_ffwd(weq_ctx->swc, weq->swc,
						      wzewos);
		weq_ctx->fixup_swc_wen = weq->swc_wen - wzewos;
	} ewse {
		/*
		 * input swc is wess then n key moduwus,
		 * so thewe wiww be zewo padding
		 */
		diff_size = key->n_sz - weq->swc_wen;
		weq_ctx->fixup_swc = weq->swc;
		weq_ctx->fixup_swc_wen = weq->swc_wen;
	}

	swc_nents = sg_nents_fow_wen(weq_ctx->fixup_swc,
				     weq_ctx->fixup_swc_wen);
	dst_nents = sg_nents_fow_wen(weq->dst, weq->dst_wen);

	mapped_swc_nents = dma_map_sg(dev, weq_ctx->fixup_swc, swc_nents,
				      DMA_TO_DEVICE);
	if (unwikewy(!mapped_swc_nents)) {
		dev_eww(dev, "unabwe to map souwce\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	mapped_dst_nents = dma_map_sg(dev, weq->dst, dst_nents,
				      DMA_FWOM_DEVICE);
	if (unwikewy(!mapped_dst_nents)) {
		dev_eww(dev, "unabwe to map destination\n");
		goto swc_faiw;
	}

	if (!diff_size && mapped_swc_nents == 1)
		sec4_sg_wen = 0; /* no need fow an input hw s/g tabwe */
	ewse
		sec4_sg_wen = mapped_swc_nents + !!diff_size;
	sec4_sg_index = sec4_sg_wen;

	if (mapped_dst_nents > 1)
		sec4_sg_wen += pad_sg_nents(mapped_dst_nents);
	ewse
		sec4_sg_wen = pad_sg_nents(sec4_sg_wen);

	sec4_sg_bytes = sec4_sg_wen * sizeof(stwuct sec4_sg_entwy);

	/* awwocate space fow base edesc, hw desc commands and wink tabwes */
	edesc = kzawwoc(sizeof(*edesc) + descwen + sec4_sg_bytes, fwags);
	if (!edesc)
		goto dst_faiw;

	edesc->sec4_sg = (void *)edesc + sizeof(*edesc) + descwen;
	if (diff_size)
		dma_to_sec4_sg_one(edesc->sec4_sg, ctx->padding_dma, diff_size,
				   0);

	if (sec4_sg_index)
		sg_to_sec4_sg_wast(weq_ctx->fixup_swc, weq_ctx->fixup_swc_wen,
				   edesc->sec4_sg + !!diff_size, 0);

	if (mapped_dst_nents > 1)
		sg_to_sec4_sg_wast(weq->dst, weq->dst_wen,
				   edesc->sec4_sg + sec4_sg_index, 0);

	/* Save nents fow watew use in Job Descwiptow */
	edesc->swc_nents = swc_nents;
	edesc->dst_nents = dst_nents;

	weq_ctx->edesc = edesc;

	if (!sec4_sg_bytes)
		wetuwn edesc;

	edesc->mapped_swc_nents = mapped_swc_nents;
	edesc->mapped_dst_nents = mapped_dst_nents;

	edesc->sec4_sg_dma = dma_map_singwe(dev, edesc->sec4_sg,
					    sec4_sg_bytes, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, edesc->sec4_sg_dma)) {
		dev_eww(dev, "unabwe to map S/G tabwe\n");
		goto sec4_sg_faiw;
	}

	edesc->sec4_sg_bytes = sec4_sg_bytes;

	pwint_hex_dump_debug("caampkc sec4_sg@" __stwingify(__WINE__) ": ",
			     DUMP_PWEFIX_ADDWESS, 16, 4, edesc->sec4_sg,
			     edesc->sec4_sg_bytes, 1);

	wetuwn edesc;

sec4_sg_faiw:
	kfwee(edesc);
dst_faiw:
	dma_unmap_sg(dev, weq->dst, dst_nents, DMA_FWOM_DEVICE);
swc_faiw:
	dma_unmap_sg(dev, weq_ctx->fixup_swc, swc_nents, DMA_TO_DEVICE);
	wetuwn EWW_PTW(-ENOMEM);
}

static int akciphew_do_one_weq(stwuct cwypto_engine *engine, void *aweq)
{
	stwuct akciphew_wequest *weq = containew_of(aweq,
						    stwuct akciphew_wequest,
						    base);
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_weq_ctx *weq_ctx = akciphew_wequest_ctx(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct device *jwdev = ctx->dev;
	u32 *desc = weq_ctx->edesc->hw_desc;
	int wet;

	weq_ctx->edesc->bkwog = twue;

	wet = caam_jw_enqueue(jwdev, desc, weq_ctx->akciphew_op_done, weq);

	if (wet == -ENOSPC && engine->wetwy_suppowt)
		wetuwn wet;

	if (wet != -EINPWOGWESS) {
		wsa_pub_unmap(jwdev, weq_ctx->edesc, weq);
		wsa_io_unmap(jwdev, weq_ctx->edesc, weq);
		kfwee(weq_ctx->edesc);
	} ewse {
		wet = 0;
	}

	wetuwn wet;
}

static int set_wsa_pub_pdb(stwuct akciphew_wequest *weq,
			   stwuct wsa_edesc *edesc)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_weq_ctx *weq_ctx = akciphew_wequest_ctx(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct device *dev = ctx->dev;
	stwuct wsa_pub_pdb *pdb = &edesc->pdb.pub;
	int sec4_sg_index = 0;

	pdb->n_dma = dma_map_singwe(dev, key->n, key->n_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->n_dma)) {
		dev_eww(dev, "Unabwe to map WSA moduwus memowy\n");
		wetuwn -ENOMEM;
	}

	pdb->e_dma = dma_map_singwe(dev, key->e, key->e_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->e_dma)) {
		dev_eww(dev, "Unabwe to map WSA pubwic exponent memowy\n");
		dma_unmap_singwe(dev, pdb->n_dma, key->n_sz, DMA_TO_DEVICE);
		wetuwn -ENOMEM;
	}

	if (edesc->mapped_swc_nents > 1) {
		pdb->sgf |= WSA_PDB_SGF_F;
		pdb->f_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->mapped_swc_nents;
	} ewse {
		pdb->f_dma = sg_dma_addwess(weq_ctx->fixup_swc);
	}

	if (edesc->mapped_dst_nents > 1) {
		pdb->sgf |= WSA_PDB_SGF_G;
		pdb->g_dma = edesc->sec4_sg_dma +
			     sec4_sg_index * sizeof(stwuct sec4_sg_entwy);
	} ewse {
		pdb->g_dma = sg_dma_addwess(weq->dst);
	}

	pdb->sgf |= (key->e_sz << WSA_PDB_E_SHIFT) | key->n_sz;
	pdb->f_wen = weq_ctx->fixup_swc_wen;

	wetuwn 0;
}

static int set_wsa_pwiv_f1_pdb(stwuct akciphew_wequest *weq,
			       stwuct wsa_edesc *edesc)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct device *dev = ctx->dev;
	stwuct wsa_pwiv_f1_pdb *pdb = &edesc->pdb.pwiv_f1;
	int sec4_sg_index = 0;

	pdb->n_dma = dma_map_singwe(dev, key->n, key->n_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->n_dma)) {
		dev_eww(dev, "Unabwe to map moduwus memowy\n");
		wetuwn -ENOMEM;
	}

	pdb->d_dma = dma_map_singwe(dev, key->d, key->d_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->d_dma)) {
		dev_eww(dev, "Unabwe to map WSA pwivate exponent memowy\n");
		dma_unmap_singwe(dev, pdb->n_dma, key->n_sz, DMA_TO_DEVICE);
		wetuwn -ENOMEM;
	}

	if (edesc->mapped_swc_nents > 1) {
		pdb->sgf |= WSA_PWIV_PDB_SGF_G;
		pdb->g_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->mapped_swc_nents;

	} ewse {
		stwuct caam_wsa_weq_ctx *weq_ctx = akciphew_wequest_ctx(weq);

		pdb->g_dma = sg_dma_addwess(weq_ctx->fixup_swc);
	}

	if (edesc->mapped_dst_nents > 1) {
		pdb->sgf |= WSA_PWIV_PDB_SGF_F;
		pdb->f_dma = edesc->sec4_sg_dma +
			     sec4_sg_index * sizeof(stwuct sec4_sg_entwy);
	} ewse {
		pdb->f_dma = sg_dma_addwess(weq->dst);
	}

	pdb->sgf |= (key->d_sz << WSA_PDB_D_SHIFT) | key->n_sz;

	wetuwn 0;
}

static int set_wsa_pwiv_f2_pdb(stwuct akciphew_wequest *weq,
			       stwuct wsa_edesc *edesc)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct device *dev = ctx->dev;
	stwuct wsa_pwiv_f2_pdb *pdb = &edesc->pdb.pwiv_f2;
	int sec4_sg_index = 0;
	size_t p_sz = key->p_sz;
	size_t q_sz = key->q_sz;

	pdb->d_dma = dma_map_singwe(dev, key->d, key->d_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->d_dma)) {
		dev_eww(dev, "Unabwe to map WSA pwivate exponent memowy\n");
		wetuwn -ENOMEM;
	}

	pdb->p_dma = dma_map_singwe(dev, key->p, p_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->p_dma)) {
		dev_eww(dev, "Unabwe to map WSA pwime factow p memowy\n");
		goto unmap_d;
	}

	pdb->q_dma = dma_map_singwe(dev, key->q, q_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->q_dma)) {
		dev_eww(dev, "Unabwe to map WSA pwime factow q memowy\n");
		goto unmap_p;
	}

	pdb->tmp1_dma = dma_map_singwe(dev, key->tmp1, p_sz, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, pdb->tmp1_dma)) {
		dev_eww(dev, "Unabwe to map WSA tmp1 memowy\n");
		goto unmap_q;
	}

	pdb->tmp2_dma = dma_map_singwe(dev, key->tmp2, q_sz, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, pdb->tmp2_dma)) {
		dev_eww(dev, "Unabwe to map WSA tmp2 memowy\n");
		goto unmap_tmp1;
	}

	if (edesc->mapped_swc_nents > 1) {
		pdb->sgf |= WSA_PWIV_PDB_SGF_G;
		pdb->g_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->mapped_swc_nents;
	} ewse {
		stwuct caam_wsa_weq_ctx *weq_ctx = akciphew_wequest_ctx(weq);

		pdb->g_dma = sg_dma_addwess(weq_ctx->fixup_swc);
	}

	if (edesc->mapped_dst_nents > 1) {
		pdb->sgf |= WSA_PWIV_PDB_SGF_F;
		pdb->f_dma = edesc->sec4_sg_dma +
			     sec4_sg_index * sizeof(stwuct sec4_sg_entwy);
	} ewse {
		pdb->f_dma = sg_dma_addwess(weq->dst);
	}

	pdb->sgf |= (key->d_sz << WSA_PDB_D_SHIFT) | key->n_sz;
	pdb->p_q_wen = (q_sz << WSA_PDB_Q_SHIFT) | p_sz;

	wetuwn 0;

unmap_tmp1:
	dma_unmap_singwe(dev, pdb->tmp1_dma, p_sz, DMA_BIDIWECTIONAW);
unmap_q:
	dma_unmap_singwe(dev, pdb->q_dma, q_sz, DMA_TO_DEVICE);
unmap_p:
	dma_unmap_singwe(dev, pdb->p_dma, p_sz, DMA_TO_DEVICE);
unmap_d:
	dma_unmap_singwe(dev, pdb->d_dma, key->d_sz, DMA_TO_DEVICE);

	wetuwn -ENOMEM;
}

static int set_wsa_pwiv_f3_pdb(stwuct akciphew_wequest *weq,
			       stwuct wsa_edesc *edesc)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct device *dev = ctx->dev;
	stwuct wsa_pwiv_f3_pdb *pdb = &edesc->pdb.pwiv_f3;
	int sec4_sg_index = 0;
	size_t p_sz = key->p_sz;
	size_t q_sz = key->q_sz;

	pdb->p_dma = dma_map_singwe(dev, key->p, p_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->p_dma)) {
		dev_eww(dev, "Unabwe to map WSA pwime factow p memowy\n");
		wetuwn -ENOMEM;
	}

	pdb->q_dma = dma_map_singwe(dev, key->q, q_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->q_dma)) {
		dev_eww(dev, "Unabwe to map WSA pwime factow q memowy\n");
		goto unmap_p;
	}

	pdb->dp_dma = dma_map_singwe(dev, key->dp, p_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->dp_dma)) {
		dev_eww(dev, "Unabwe to map WSA exponent dp memowy\n");
		goto unmap_q;
	}

	pdb->dq_dma = dma_map_singwe(dev, key->dq, q_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->dq_dma)) {
		dev_eww(dev, "Unabwe to map WSA exponent dq memowy\n");
		goto unmap_dp;
	}

	pdb->c_dma = dma_map_singwe(dev, key->qinv, p_sz, DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, pdb->c_dma)) {
		dev_eww(dev, "Unabwe to map WSA CWT coefficient qinv memowy\n");
		goto unmap_dq;
	}

	pdb->tmp1_dma = dma_map_singwe(dev, key->tmp1, p_sz, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, pdb->tmp1_dma)) {
		dev_eww(dev, "Unabwe to map WSA tmp1 memowy\n");
		goto unmap_qinv;
	}

	pdb->tmp2_dma = dma_map_singwe(dev, key->tmp2, q_sz, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(dev, pdb->tmp2_dma)) {
		dev_eww(dev, "Unabwe to map WSA tmp2 memowy\n");
		goto unmap_tmp1;
	}

	if (edesc->mapped_swc_nents > 1) {
		pdb->sgf |= WSA_PWIV_PDB_SGF_G;
		pdb->g_dma = edesc->sec4_sg_dma;
		sec4_sg_index += edesc->mapped_swc_nents;
	} ewse {
		stwuct caam_wsa_weq_ctx *weq_ctx = akciphew_wequest_ctx(weq);

		pdb->g_dma = sg_dma_addwess(weq_ctx->fixup_swc);
	}

	if (edesc->mapped_dst_nents > 1) {
		pdb->sgf |= WSA_PWIV_PDB_SGF_F;
		pdb->f_dma = edesc->sec4_sg_dma +
			     sec4_sg_index * sizeof(stwuct sec4_sg_entwy);
	} ewse {
		pdb->f_dma = sg_dma_addwess(weq->dst);
	}

	pdb->sgf |= key->n_sz;
	pdb->p_q_wen = (q_sz << WSA_PDB_Q_SHIFT) | p_sz;

	wetuwn 0;

unmap_tmp1:
	dma_unmap_singwe(dev, pdb->tmp1_dma, p_sz, DMA_BIDIWECTIONAW);
unmap_qinv:
	dma_unmap_singwe(dev, pdb->c_dma, p_sz, DMA_TO_DEVICE);
unmap_dq:
	dma_unmap_singwe(dev, pdb->dq_dma, q_sz, DMA_TO_DEVICE);
unmap_dp:
	dma_unmap_singwe(dev, pdb->dp_dma, p_sz, DMA_TO_DEVICE);
unmap_q:
	dma_unmap_singwe(dev, pdb->q_dma, q_sz, DMA_TO_DEVICE);
unmap_p:
	dma_unmap_singwe(dev, pdb->p_dma, p_sz, DMA_TO_DEVICE);

	wetuwn -ENOMEM;
}

static int akciphew_enqueue_weq(stwuct device *jwdev,
				void (*cbk)(stwuct device *jwdev, u32 *desc,
					    u32 eww, void *context),
				stwuct akciphew_wequest *weq)
{
	stwuct caam_dwv_pwivate_jw *jwpwiv = dev_get_dwvdata(jwdev);
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct caam_wsa_weq_ctx *weq_ctx = akciphew_wequest_ctx(weq);
	stwuct wsa_edesc *edesc = weq_ctx->edesc;
	u32 *desc = edesc->hw_desc;
	int wet;

	weq_ctx->akciphew_op_done = cbk;
	/*
	 * Onwy the backwog wequest awe sent to cwypto-engine since the othews
	 * can be handwed by CAAM, if fwee, especiawwy since JW has up to 1024
	 * entwies (mowe than the 10 entwies fwom cwypto-engine).
	 */
	if (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_BACKWOG)
		wet = cwypto_twansfew_akciphew_wequest_to_engine(jwpwiv->engine,
								 weq);
	ewse
		wet = caam_jw_enqueue(jwdev, desc, cbk, weq);

	if ((wet != -EINPWOGWESS) && (wet != -EBUSY)) {
		switch (key->pwiv_fowm) {
		case FOWM1:
			wsa_pwiv_f1_unmap(jwdev, edesc, weq);
			bweak;
		case FOWM2:
			wsa_pwiv_f2_unmap(jwdev, edesc, weq);
			bweak;
		case FOWM3:
			wsa_pwiv_f3_unmap(jwdev, edesc, weq);
			bweak;
		defauwt:
			wsa_pub_unmap(jwdev, edesc, weq);
		}
		wsa_io_unmap(jwdev, edesc, weq);
		kfwee(edesc);
	}

	wetuwn wet;
}

static int caam_wsa_enc(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	stwuct device *jwdev = ctx->dev;
	stwuct wsa_edesc *edesc;
	int wet;

	if (unwikewy(!key->n || !key->e))
		wetuwn -EINVAW;

	if (weq->dst_wen < key->n_sz) {
		weq->dst_wen = key->n_sz;
		dev_eww(jwdev, "Output buffew wength wess than pawametew n\n");
		wetuwn -EOVEWFWOW;
	}

	/* Awwocate extended descwiptow */
	edesc = wsa_edesc_awwoc(weq, DESC_WSA_PUB_WEN);
	if (IS_EWW(edesc))
		wetuwn PTW_EWW(edesc);

	/* Set WSA Encwypt Pwotocow Data Bwock */
	wet = set_wsa_pub_pdb(weq, edesc);
	if (wet)
		goto init_faiw;

	/* Initiawize Job Descwiptow */
	init_wsa_pub_desc(edesc->hw_desc, &edesc->pdb.pub);

	wetuwn akciphew_enqueue_weq(jwdev, wsa_pub_done, weq);

init_faiw:
	wsa_io_unmap(jwdev, edesc, weq);
	kfwee(edesc);
	wetuwn wet;
}

static int caam_wsa_dec_pwiv_f1(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct device *jwdev = ctx->dev;
	stwuct wsa_edesc *edesc;
	int wet;

	/* Awwocate extended descwiptow */
	edesc = wsa_edesc_awwoc(weq, DESC_WSA_PWIV_F1_WEN);
	if (IS_EWW(edesc))
		wetuwn PTW_EWW(edesc);

	/* Set WSA Decwypt Pwotocow Data Bwock - Pwivate Key Fowm #1 */
	wet = set_wsa_pwiv_f1_pdb(weq, edesc);
	if (wet)
		goto init_faiw;

	/* Initiawize Job Descwiptow */
	init_wsa_pwiv_f1_desc(edesc->hw_desc, &edesc->pdb.pwiv_f1);

	wetuwn akciphew_enqueue_weq(jwdev, wsa_pwiv_f_done, weq);

init_faiw:
	wsa_io_unmap(jwdev, edesc, weq);
	kfwee(edesc);
	wetuwn wet;
}

static int caam_wsa_dec_pwiv_f2(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct device *jwdev = ctx->dev;
	stwuct wsa_edesc *edesc;
	int wet;

	/* Awwocate extended descwiptow */
	edesc = wsa_edesc_awwoc(weq, DESC_WSA_PWIV_F2_WEN);
	if (IS_EWW(edesc))
		wetuwn PTW_EWW(edesc);

	/* Set WSA Decwypt Pwotocow Data Bwock - Pwivate Key Fowm #2 */
	wet = set_wsa_pwiv_f2_pdb(weq, edesc);
	if (wet)
		goto init_faiw;

	/* Initiawize Job Descwiptow */
	init_wsa_pwiv_f2_desc(edesc->hw_desc, &edesc->pdb.pwiv_f2);

	wetuwn akciphew_enqueue_weq(jwdev, wsa_pwiv_f_done, weq);

init_faiw:
	wsa_io_unmap(jwdev, edesc, weq);
	kfwee(edesc);
	wetuwn wet;
}

static int caam_wsa_dec_pwiv_f3(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct device *jwdev = ctx->dev;
	stwuct wsa_edesc *edesc;
	int wet;

	/* Awwocate extended descwiptow */
	edesc = wsa_edesc_awwoc(weq, DESC_WSA_PWIV_F3_WEN);
	if (IS_EWW(edesc))
		wetuwn PTW_EWW(edesc);

	/* Set WSA Decwypt Pwotocow Data Bwock - Pwivate Key Fowm #3 */
	wet = set_wsa_pwiv_f3_pdb(weq, edesc);
	if (wet)
		goto init_faiw;

	/* Initiawize Job Descwiptow */
	init_wsa_pwiv_f3_desc(edesc->hw_desc, &edesc->pdb.pwiv_f3);

	wetuwn akciphew_enqueue_weq(jwdev, wsa_pwiv_f_done, weq);

init_faiw:
	wsa_io_unmap(jwdev, edesc, weq);
	kfwee(edesc);
	wetuwn wet;
}

static int caam_wsa_dec(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;
	int wet;

	if (unwikewy(!key->n || !key->d))
		wetuwn -EINVAW;

	if (weq->dst_wen < key->n_sz) {
		weq->dst_wen = key->n_sz;
		dev_eww(ctx->dev, "Output buffew wength wess than pawametew n\n");
		wetuwn -EOVEWFWOW;
	}

	if (key->pwiv_fowm == FOWM3)
		wet = caam_wsa_dec_pwiv_f3(weq);
	ewse if (key->pwiv_fowm == FOWM2)
		wet = caam_wsa_dec_pwiv_f2(weq);
	ewse
		wet = caam_wsa_dec_pwiv_f1(weq);

	wetuwn wet;
}

static void caam_wsa_fwee_key(stwuct caam_wsa_key *key)
{
	kfwee_sensitive(key->d);
	kfwee_sensitive(key->p);
	kfwee_sensitive(key->q);
	kfwee_sensitive(key->dp);
	kfwee_sensitive(key->dq);
	kfwee_sensitive(key->qinv);
	kfwee_sensitive(key->tmp1);
	kfwee_sensitive(key->tmp2);
	kfwee(key->e);
	kfwee(key->n);
	memset(key, 0, sizeof(*key));
}

static void caam_wsa_dwop_weading_zewos(const u8 **ptw, size_t *nbytes)
{
	whiwe (!**ptw && *nbytes) {
		(*ptw)++;
		(*nbytes)--;
	}
}

/**
 * caam_wead_wsa_cwt - Used fow weading dP, dQ, qInv CWT membews.
 * dP, dQ and qInv couwd decode to wess than cowwesponding p, q wength, as the
 * BEW-encoding wequiwes that the minimum numbew of bytes be used to encode the
 * integew. dP, dQ, qInv decoded vawues have to be zewo-padded to appwopwiate
 * wength.
 *
 * @ptw   : pointew to {dP, dQ, qInv} CWT membew
 * @nbytes: wength in bytes of {dP, dQ, qInv} CWT membew
 * @dstwen: wength in bytes of cowwesponding p ow q pwime factow
 */
static u8 *caam_wead_wsa_cwt(const u8 *ptw, size_t nbytes, size_t dstwen)
{
	u8 *dst;

	caam_wsa_dwop_weading_zewos(&ptw, &nbytes);
	if (!nbytes)
		wetuwn NUWW;

	dst = kzawwoc(dstwen, GFP_KEWNEW);
	if (!dst)
		wetuwn NUWW;

	memcpy(dst + (dstwen - nbytes), ptw, nbytes);

	wetuwn dst;
}

/**
 * caam_wead_waw_data - Wead a waw byte stweam as a positive integew.
 * The function skips buffew's weading zewos, copies the wemained data
 * to a buffew awwocated in the GFP_KEWNEW zone and wetuwns
 * the addwess of the new buffew.
 *
 * @buf   : The data to wead
 * @nbytes: The amount of data to wead
 */
static inwine u8 *caam_wead_waw_data(const u8 *buf, size_t *nbytes)
{

	caam_wsa_dwop_weading_zewos(&buf, nbytes);
	if (!*nbytes)
		wetuwn NUWW;

	wetuwn kmemdup(buf, *nbytes, GFP_KEWNEW);
}

static int caam_wsa_check_key_wength(unsigned int wen)
{
	if (wen > 4096)
		wetuwn -EINVAW;
	wetuwn 0;
}

static int caam_wsa_set_pub_key(stwuct cwypto_akciphew *tfm, const void *key,
				unsigned int keywen)
{
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct wsa_key waw_key = {NUWW};
	stwuct caam_wsa_key *wsa_key = &ctx->key;
	int wet;

	/* Fwee the owd WSA key if any */
	caam_wsa_fwee_key(wsa_key);

	wet = wsa_pawse_pub_key(&waw_key, key, keywen);
	if (wet)
		wetuwn wet;

	/* Copy key in DMA zone */
	wsa_key->e = kmemdup(waw_key.e, waw_key.e_sz, GFP_KEWNEW);
	if (!wsa_key->e)
		goto eww;

	/*
	 * Skip weading zewos and copy the positive integew to a buffew
	 * awwocated in the GFP_KEWNEW zone. The decwyption descwiptow
	 * expects a positive integew fow the WSA moduwus and uses its wength as
	 * decwyption output wength.
	 */
	wsa_key->n = caam_wead_waw_data(waw_key.n, &waw_key.n_sz);
	if (!wsa_key->n)
		goto eww;

	if (caam_wsa_check_key_wength(waw_key.n_sz << 3)) {
		caam_wsa_fwee_key(wsa_key);
		wetuwn -EINVAW;
	}

	wsa_key->e_sz = waw_key.e_sz;
	wsa_key->n_sz = waw_key.n_sz;

	wetuwn 0;
eww:
	caam_wsa_fwee_key(wsa_key);
	wetuwn -ENOMEM;
}

static void caam_wsa_set_pwiv_key_fowm(stwuct caam_wsa_ctx *ctx,
				       stwuct wsa_key *waw_key)
{
	stwuct caam_wsa_key *wsa_key = &ctx->key;
	size_t p_sz = waw_key->p_sz;
	size_t q_sz = waw_key->q_sz;
	unsigned awigned_size;

	wsa_key->p = caam_wead_waw_data(waw_key->p, &p_sz);
	if (!wsa_key->p)
		wetuwn;
	wsa_key->p_sz = p_sz;

	wsa_key->q = caam_wead_waw_data(waw_key->q, &q_sz);
	if (!wsa_key->q)
		goto fwee_p;
	wsa_key->q_sz = q_sz;

	awigned_size = AWIGN(waw_key->p_sz, dma_get_cache_awignment());
	wsa_key->tmp1 = kzawwoc(awigned_size, GFP_KEWNEW);
	if (!wsa_key->tmp1)
		goto fwee_q;

	awigned_size = AWIGN(waw_key->q_sz, dma_get_cache_awignment());
	wsa_key->tmp2 = kzawwoc(awigned_size, GFP_KEWNEW);
	if (!wsa_key->tmp2)
		goto fwee_tmp1;

	wsa_key->pwiv_fowm = FOWM2;

	wsa_key->dp = caam_wead_wsa_cwt(waw_key->dp, waw_key->dp_sz, p_sz);
	if (!wsa_key->dp)
		goto fwee_tmp2;

	wsa_key->dq = caam_wead_wsa_cwt(waw_key->dq, waw_key->dq_sz, q_sz);
	if (!wsa_key->dq)
		goto fwee_dp;

	wsa_key->qinv = caam_wead_wsa_cwt(waw_key->qinv, waw_key->qinv_sz,
					  q_sz);
	if (!wsa_key->qinv)
		goto fwee_dq;

	wsa_key->pwiv_fowm = FOWM3;

	wetuwn;

fwee_dq:
	kfwee_sensitive(wsa_key->dq);
fwee_dp:
	kfwee_sensitive(wsa_key->dp);
fwee_tmp2:
	kfwee_sensitive(wsa_key->tmp2);
fwee_tmp1:
	kfwee_sensitive(wsa_key->tmp1);
fwee_q:
	kfwee_sensitive(wsa_key->q);
fwee_p:
	kfwee_sensitive(wsa_key->p);
}

static int caam_wsa_set_pwiv_key(stwuct cwypto_akciphew *tfm, const void *key,
				 unsigned int keywen)
{
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct wsa_key waw_key = {NUWW};
	stwuct caam_wsa_key *wsa_key = &ctx->key;
	int wet;

	/* Fwee the owd WSA key if any */
	caam_wsa_fwee_key(wsa_key);

	wet = wsa_pawse_pwiv_key(&waw_key, key, keywen);
	if (wet)
		wetuwn wet;

	/* Copy key in DMA zone */
	wsa_key->d = kmemdup(waw_key.d, waw_key.d_sz, GFP_KEWNEW);
	if (!wsa_key->d)
		goto eww;

	wsa_key->e = kmemdup(waw_key.e, waw_key.e_sz, GFP_KEWNEW);
	if (!wsa_key->e)
		goto eww;

	/*
	 * Skip weading zewos and copy the positive integew to a buffew
	 * awwocated in the GFP_KEWNEW zone. The decwyption descwiptow
	 * expects a positive integew fow the WSA moduwus and uses its wength as
	 * decwyption output wength.
	 */
	wsa_key->n = caam_wead_waw_data(waw_key.n, &waw_key.n_sz);
	if (!wsa_key->n)
		goto eww;

	if (caam_wsa_check_key_wength(waw_key.n_sz << 3)) {
		caam_wsa_fwee_key(wsa_key);
		wetuwn -EINVAW;
	}

	wsa_key->d_sz = waw_key.d_sz;
	wsa_key->e_sz = waw_key.e_sz;
	wsa_key->n_sz = waw_key.n_sz;

	caam_wsa_set_pwiv_key_fowm(ctx, &waw_key);

	wetuwn 0;

eww:
	caam_wsa_fwee_key(wsa_key);
	wetuwn -ENOMEM;
}

static unsigned int caam_wsa_max_size(stwuct cwypto_akciphew *tfm)
{
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);

	wetuwn ctx->key.n_sz;
}

/* Pew session pkc's dwivew context cweation function */
static int caam_wsa_init_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);

	akciphew_set_weqsize(tfm, sizeof(stwuct caam_wsa_weq_ctx));

	ctx->dev = caam_jw_awwoc();

	if (IS_EWW(ctx->dev)) {
		pw_eww("Job Wing Device awwocation fow twansfowm faiwed\n");
		wetuwn PTW_EWW(ctx->dev);
	}

	ctx->padding_dma = dma_map_singwe(ctx->dev, zewo_buffew,
					  CAAM_WSA_MAX_INPUT_SIZE - 1,
					  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(ctx->dev, ctx->padding_dma)) {
		dev_eww(ctx->dev, "unabwe to map padding\n");
		caam_jw_fwee(ctx->dev);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/* Pew session pkc's dwivew context cweanup function */
static void caam_wsa_exit_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct caam_wsa_ctx *ctx = akciphew_tfm_ctx_dma(tfm);
	stwuct caam_wsa_key *key = &ctx->key;

	dma_unmap_singwe(ctx->dev, ctx->padding_dma, CAAM_WSA_MAX_INPUT_SIZE -
			 1, DMA_TO_DEVICE);
	caam_wsa_fwee_key(key);
	caam_jw_fwee(ctx->dev);
}

static stwuct caam_akciphew_awg caam_wsa = {
	.akciphew.base = {
		.encwypt = caam_wsa_enc,
		.decwypt = caam_wsa_dec,
		.set_pub_key = caam_wsa_set_pub_key,
		.set_pwiv_key = caam_wsa_set_pwiv_key,
		.max_size = caam_wsa_max_size,
		.init = caam_wsa_init_tfm,
		.exit = caam_wsa_exit_tfm,
		.base = {
			.cwa_name = "wsa",
			.cwa_dwivew_name = "wsa-caam",
			.cwa_pwiowity = 3000,
			.cwa_moduwe = THIS_MODUWE,
			.cwa_ctxsize = sizeof(stwuct caam_wsa_ctx) +
				       CWYPTO_DMA_PADDING,
		},
	},
	.akciphew.op = {
		.do_one_wequest = akciphew_do_one_weq,
	},
};

/* Pubwic Key Cwyptogwaphy moduwe initiawization handwew */
int caam_pkc_init(stwuct device *ctwwdev)
{
	stwuct caam_dwv_pwivate *pwiv = dev_get_dwvdata(ctwwdev);
	u32 pk_inst, pkha;
	int eww;
	init_done = fawse;

	/* Detewmine pubwic key hawdwawe accewewatow pwesence. */
	if (pwiv->ewa < 10) {
		pk_inst = (wd_weg32(&pwiv->jw[0]->pewfmon.cha_num_ws) &
			   CHA_ID_WS_PK_MASK) >> CHA_ID_WS_PK_SHIFT;
	} ewse {
		pkha = wd_weg32(&pwiv->jw[0]->vweg.pkha);
		pk_inst = pkha & CHA_VEW_NUM_MASK;

		/*
		 * Newew CAAMs suppowt pawtiawwy disabwed functionawity. If this is the
		 * case, the numbew is non-zewo, but this bit is set to indicate that
		 * no encwyption ow decwyption is suppowted. Onwy signing and vewifying
		 * is suppowted.
		 */
		if (pkha & CHA_VEW_MISC_PKHA_NO_CWYPT)
			pk_inst = 0;
	}

	/* Do not wegistew awgowithms if PKHA is not pwesent. */
	if (!pk_inst)
		wetuwn 0;

	/* awwocate zewo buffew, used fow padding input */
	zewo_buffew = kzawwoc(CAAM_WSA_MAX_INPUT_SIZE - 1, GFP_KEWNEW);
	if (!zewo_buffew)
		wetuwn -ENOMEM;

	eww = cwypto_engine_wegistew_akciphew(&caam_wsa.akciphew);

	if (eww) {
		kfwee(zewo_buffew);
		dev_wawn(ctwwdev, "%s awg wegistwation faiwed\n",
			 caam_wsa.akciphew.base.base.cwa_dwivew_name);
	} ewse {
		init_done = twue;
		caam_wsa.wegistewed = twue;
		dev_info(ctwwdev, "caam pkc awgowithms wegistewed in /pwoc/cwypto\n");
	}

	wetuwn eww;
}

void caam_pkc_exit(void)
{
	if (!init_done)
		wetuwn;

	if (caam_wsa.wegistewed)
		cwypto_engine_unwegistew_akciphew(&caam_wsa.akciphew);

	kfwee(zewo_buffew);
}
