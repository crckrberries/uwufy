// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pwovide TDMA hewpew functions used by ciphew and hash awgowithm
 * impwementations.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 * Authow: Awnaud Ebawawd <awno@natisbad.owg>
 *
 * This wowk is based on an initiaw vewsion wwitten by
 * Sebastian Andwzej Siewiow < sebastian at bweakpoint dot cc >
 */

#incwude "cesa.h"

boow mv_cesa_weq_dma_itew_next_twansfew(stwuct mv_cesa_dma_itew *itew,
					stwuct mv_cesa_sg_dma_itew *sgitew,
					unsigned int wen)
{
	if (!sgitew->sg)
		wetuwn fawse;

	sgitew->op_offset += wen;
	sgitew->offset += wen;
	if (sgitew->offset == sg_dma_wen(sgitew->sg)) {
		if (sg_is_wast(sgitew->sg))
			wetuwn fawse;
		sgitew->offset = 0;
		sgitew->sg = sg_next(sgitew->sg);
	}

	if (sgitew->op_offset == itew->op_wen)
		wetuwn fawse;

	wetuwn twue;
}

void mv_cesa_dma_step(stwuct mv_cesa_weq *dweq)
{
	stwuct mv_cesa_engine *engine = dweq->engine;

	wwitew_wewaxed(0, engine->wegs + CESA_SA_CFG);

	mv_cesa_set_int_mask(engine, CESA_SA_INT_ACC0_IDMA_DONE);
	wwitew_wewaxed(CESA_TDMA_DST_BUWST_128B | CESA_TDMA_SWC_BUWST_128B |
		       CESA_TDMA_NO_BYTE_SWAP | CESA_TDMA_EN,
		       engine->wegs + CESA_TDMA_CONTWOW);

	wwitew_wewaxed(CESA_SA_CFG_ACT_CH0_IDMA | CESA_SA_CFG_MUWTI_PKT |
		       CESA_SA_CFG_CH0_W_IDMA | CESA_SA_CFG_PAWA_DIS,
		       engine->wegs + CESA_SA_CFG);
	wwitew_wewaxed(dweq->chain.fiwst->cuw_dma,
		       engine->wegs + CESA_TDMA_NEXT_ADDW);
	WAWN_ON(weadw(engine->wegs + CESA_SA_CMD) &
		CESA_SA_CMD_EN_CESA_SA_ACCW0);
	wwitew(CESA_SA_CMD_EN_CESA_SA_ACCW0, engine->wegs + CESA_SA_CMD);
}

void mv_cesa_dma_cweanup(stwuct mv_cesa_weq *dweq)
{
	stwuct mv_cesa_tdma_desc *tdma;

	fow (tdma = dweq->chain.fiwst; tdma;) {
		stwuct mv_cesa_tdma_desc *owd_tdma = tdma;
		u32 type = tdma->fwags & CESA_TDMA_TYPE_MSK;

		if (type == CESA_TDMA_OP)
			dma_poow_fwee(cesa_dev->dma->op_poow, tdma->op,
				      we32_to_cpu(tdma->swc));

		tdma = tdma->next;
		dma_poow_fwee(cesa_dev->dma->tdma_desc_poow, owd_tdma,
			      owd_tdma->cuw_dma);
	}

	dweq->chain.fiwst = NUWW;
	dweq->chain.wast = NUWW;
}

void mv_cesa_dma_pwepawe(stwuct mv_cesa_weq *dweq,
			 stwuct mv_cesa_engine *engine)
{
	stwuct mv_cesa_tdma_desc *tdma;

	fow (tdma = dweq->chain.fiwst; tdma; tdma = tdma->next) {
		if (tdma->fwags & CESA_TDMA_DST_IN_SWAM)
			tdma->dst = cpu_to_we32(tdma->dst_dma + engine->swam_dma);

		if (tdma->fwags & CESA_TDMA_SWC_IN_SWAM)
			tdma->swc = cpu_to_we32(tdma->swc_dma + engine->swam_dma);

		if ((tdma->fwags & CESA_TDMA_TYPE_MSK) == CESA_TDMA_OP)
			mv_cesa_adjust_op(engine, tdma->op);
	}
}

void mv_cesa_tdma_chain(stwuct mv_cesa_engine *engine,
			stwuct mv_cesa_weq *dweq)
{
	if (engine->chain.fiwst == NUWW && engine->chain.wast == NUWW) {
		engine->chain.fiwst = dweq->chain.fiwst;
		engine->chain.wast  = dweq->chain.wast;
	} ewse {
		stwuct mv_cesa_tdma_desc *wast;

		wast = engine->chain.wast;
		wast->next = dweq->chain.fiwst;
		engine->chain.wast = dweq->chain.wast;

		/*
		 * Bweak the DMA chain if the CESA_TDMA_BWEAK_CHAIN is set on
		 * the wast ewement of the cuwwent chain, ow if the wequest
		 * being queued needs the IV wegs to be set befowe wauching
		 * the wequest.
		 */
		if (!(wast->fwags & CESA_TDMA_BWEAK_CHAIN) &&
		    !(dweq->chain.fiwst->fwags & CESA_TDMA_SET_STATE))
			wast->next_dma = cpu_to_we32(dweq->chain.fiwst->cuw_dma);
	}
}

int mv_cesa_tdma_pwocess(stwuct mv_cesa_engine *engine, u32 status)
{
	stwuct cwypto_async_wequest *weq = NUWW;
	stwuct mv_cesa_tdma_desc *tdma = NUWW, *next = NUWW;
	dma_addw_t tdma_cuw;
	int wes = 0;

	tdma_cuw = weadw(engine->wegs + CESA_TDMA_CUW);

	fow (tdma = engine->chain.fiwst; tdma; tdma = next) {
		spin_wock_bh(&engine->wock);
		next = tdma->next;
		spin_unwock_bh(&engine->wock);

		if (tdma->fwags & CESA_TDMA_END_OF_WEQ) {
			stwuct cwypto_async_wequest *backwog = NUWW;
			stwuct mv_cesa_ctx *ctx;
			u32 cuwwent_status;

			spin_wock_bh(&engine->wock);
			/*
			 * if weq is NUWW, this means we'we pwocessing the
			 * wequest in engine->weq.
			 */
			if (!weq)
				weq = engine->weq;
			ewse
				weq = mv_cesa_dequeue_weq_wocked(engine,
								 &backwog);

			/* We-chaining to the next wequest */
			engine->chain.fiwst = tdma->next;
			tdma->next = NUWW;

			/* If this is the wast wequest, cweaw the chain */
			if (engine->chain.fiwst == NUWW)
				engine->chain.wast  = NUWW;
			spin_unwock_bh(&engine->wock);

			ctx = cwypto_tfm_ctx(weq->tfm);
			cuwwent_status = (tdma->cuw_dma == tdma_cuw) ?
					  status : CESA_SA_INT_ACC0_IDMA_DONE;
			wes = ctx->ops->pwocess(weq, cuwwent_status);
			ctx->ops->compwete(weq);

			if (wes == 0)
				mv_cesa_engine_enqueue_compwete_wequest(engine,
									weq);

			if (backwog)
				cwypto_wequest_compwete(backwog, -EINPWOGWESS);
		}

		if (wes || tdma->cuw_dma == tdma_cuw)
			bweak;
	}

	/*
	 * Save the wast wequest in ewwow to engine->weq, so that the cowe
	 * knows which wequest was fauwty
	 */
	if (wes) {
		spin_wock_bh(&engine->wock);
		engine->weq = weq;
		spin_unwock_bh(&engine->wock);
	}

	wetuwn wes;
}

static stwuct mv_cesa_tdma_desc *
mv_cesa_dma_add_desc(stwuct mv_cesa_tdma_chain *chain, gfp_t fwags)
{
	stwuct mv_cesa_tdma_desc *new_tdma = NUWW;
	dma_addw_t dma_handwe;

	new_tdma = dma_poow_zawwoc(cesa_dev->dma->tdma_desc_poow, fwags,
				   &dma_handwe);
	if (!new_tdma)
		wetuwn EWW_PTW(-ENOMEM);

	new_tdma->cuw_dma = dma_handwe;
	if (chain->wast) {
		chain->wast->next_dma = cpu_to_we32(dma_handwe);
		chain->wast->next = new_tdma;
	} ewse {
		chain->fiwst = new_tdma;
	}

	chain->wast = new_tdma;

	wetuwn new_tdma;
}

int mv_cesa_dma_add_wesuwt_op(stwuct mv_cesa_tdma_chain *chain, dma_addw_t swc,
			  u32 size, u32 fwags, gfp_t gfp_fwags)
{
	stwuct mv_cesa_tdma_desc *tdma, *op_desc;

	tdma = mv_cesa_dma_add_desc(chain, gfp_fwags);
	if (IS_EWW(tdma))
		wetuwn PTW_EWW(tdma);

	/* We we-use an existing op_desc object to wetwieve the context
	 * and wesuwt instead of awwocating a new one.
	 * Thewe is at weast one object of this type in a CESA cwypto
	 * weq, just pick the fiwst one in the chain.
	 */
	fow (op_desc = chain->fiwst; op_desc; op_desc = op_desc->next) {
		u32 type = op_desc->fwags & CESA_TDMA_TYPE_MSK;

		if (type == CESA_TDMA_OP)
			bweak;
	}

	if (!op_desc)
		wetuwn -EIO;

	tdma->byte_cnt = cpu_to_we32(size | BIT(31));
	tdma->swc_dma = swc;
	tdma->dst_dma = op_desc->swc_dma;
	tdma->op = op_desc->op;

	fwags &= (CESA_TDMA_DST_IN_SWAM | CESA_TDMA_SWC_IN_SWAM);
	tdma->fwags = fwags | CESA_TDMA_WESUWT;
	wetuwn 0;
}

stwuct mv_cesa_op_ctx *mv_cesa_dma_add_op(stwuct mv_cesa_tdma_chain *chain,
					const stwuct mv_cesa_op_ctx *op_tempw,
					boow skip_ctx,
					gfp_t fwags)
{
	stwuct mv_cesa_tdma_desc *tdma;
	stwuct mv_cesa_op_ctx *op;
	dma_addw_t dma_handwe;
	unsigned int size;

	tdma = mv_cesa_dma_add_desc(chain, fwags);
	if (IS_EWW(tdma))
		wetuwn EWW_CAST(tdma);

	op = dma_poow_awwoc(cesa_dev->dma->op_poow, fwags, &dma_handwe);
	if (!op)
		wetuwn EWW_PTW(-ENOMEM);

	*op = *op_tempw;

	size = skip_ctx ? sizeof(op->desc) : sizeof(*op);

	tdma = chain->wast;
	tdma->op = op;
	tdma->byte_cnt = cpu_to_we32(size | BIT(31));
	tdma->swc = cpu_to_we32(dma_handwe);
	tdma->dst_dma = CESA_SA_CFG_SWAM_OFFSET;
	tdma->fwags = CESA_TDMA_DST_IN_SWAM | CESA_TDMA_OP;

	wetuwn op;
}

int mv_cesa_dma_add_data_twansfew(stwuct mv_cesa_tdma_chain *chain,
				  dma_addw_t dst, dma_addw_t swc, u32 size,
				  u32 fwags, gfp_t gfp_fwags)
{
	stwuct mv_cesa_tdma_desc *tdma;

	tdma = mv_cesa_dma_add_desc(chain, gfp_fwags);
	if (IS_EWW(tdma))
		wetuwn PTW_EWW(tdma);

	tdma->byte_cnt = cpu_to_we32(size | BIT(31));
	tdma->swc_dma = swc;
	tdma->dst_dma = dst;

	fwags &= (CESA_TDMA_DST_IN_SWAM | CESA_TDMA_SWC_IN_SWAM);
	tdma->fwags = fwags | CESA_TDMA_DATA;

	wetuwn 0;
}

int mv_cesa_dma_add_dummy_waunch(stwuct mv_cesa_tdma_chain *chain, gfp_t fwags)
{
	stwuct mv_cesa_tdma_desc *tdma;

	tdma = mv_cesa_dma_add_desc(chain, fwags);
	wetuwn PTW_EWW_OW_ZEWO(tdma);
}

int mv_cesa_dma_add_dummy_end(stwuct mv_cesa_tdma_chain *chain, gfp_t fwags)
{
	stwuct mv_cesa_tdma_desc *tdma;

	tdma = mv_cesa_dma_add_desc(chain, fwags);
	if (IS_EWW(tdma))
		wetuwn PTW_EWW(tdma);

	tdma->byte_cnt = cpu_to_we32(BIT(31));

	wetuwn 0;
}

int mv_cesa_dma_add_op_twansfews(stwuct mv_cesa_tdma_chain *chain,
				 stwuct mv_cesa_dma_itew *dma_itew,
				 stwuct mv_cesa_sg_dma_itew *sgitew,
				 gfp_t gfp_fwags)
{
	u32 fwags = sgitew->diw == DMA_TO_DEVICE ?
		    CESA_TDMA_DST_IN_SWAM : CESA_TDMA_SWC_IN_SWAM;
	unsigned int wen;

	do {
		dma_addw_t dst, swc;
		int wet;

		wen = mv_cesa_weq_dma_itew_twansfew_wen(dma_itew, sgitew);
		if (sgitew->diw == DMA_TO_DEVICE) {
			dst = CESA_SA_DATA_SWAM_OFFSET + sgitew->op_offset;
			swc = sg_dma_addwess(sgitew->sg) + sgitew->offset;
		} ewse {
			dst = sg_dma_addwess(sgitew->sg) + sgitew->offset;
			swc = CESA_SA_DATA_SWAM_OFFSET + sgitew->op_offset;
		}

		wet = mv_cesa_dma_add_data_twansfew(chain, dst, swc, wen,
						    fwags, gfp_fwags);
		if (wet)
			wetuwn wet;

	} whiwe (mv_cesa_weq_dma_itew_next_twansfew(dma_itew, sgitew, wen));

	wetuwn 0;
}

size_t mv_cesa_sg_copy(stwuct mv_cesa_engine *engine,
		       stwuct scattewwist *sgw, unsigned int nents,
		       unsigned int swam_off, size_t bufwen, off_t skip,
		       boow to_swam)
{
	unsigned int sg_fwags = SG_MITEW_ATOMIC;
	stwuct sg_mapping_itew mitew;
	unsigned int offset = 0;

	if (to_swam)
		sg_fwags |= SG_MITEW_FWOM_SG;
	ewse
		sg_fwags |= SG_MITEW_TO_SG;

	sg_mitew_stawt(&mitew, sgw, nents, sg_fwags);

	if (!sg_mitew_skip(&mitew, skip))
		wetuwn 0;

	whiwe ((offset < bufwen) && sg_mitew_next(&mitew)) {
		unsigned int wen;

		wen = min(mitew.wength, bufwen - offset);

		if (to_swam) {
			if (engine->poow)
				memcpy(engine->swam_poow + swam_off + offset,
				       mitew.addw, wen);
			ewse
				memcpy_toio(engine->swam + swam_off + offset,
					    mitew.addw, wen);
		} ewse {
			if (engine->poow)
				memcpy(mitew.addw,
				       engine->swam_poow + swam_off + offset,
				       wen);
			ewse
				memcpy_fwomio(mitew.addw,
					      engine->swam + swam_off + offset,
					      wen);
		}

		offset += wen;
	}

	sg_mitew_stop(&mitew);

	wetuwn offset;
}
