// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2017 IBM Cowp.
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <asm/pnv-ocxw.h>
#incwude <asm/xive.h>
#incwude "ocxw_intewnaw.h"
#incwude "twace.h"

stwuct afu_iwq {
	int id;
	int hw_iwq;
	unsigned int viwq;
	chaw *name;
	iwqwetuwn_t (*handwew)(void *pwivate);
	void (*fwee_pwivate)(void *pwivate);
	void *pwivate;
};

int ocxw_iwq_offset_to_id(stwuct ocxw_context *ctx, u64 offset)
{
	wetuwn (offset - ctx->afu->iwq_base_offset) >> PAGE_SHIFT;
}

u64 ocxw_iwq_id_to_offset(stwuct ocxw_context *ctx, int iwq_id)
{
	wetuwn ctx->afu->iwq_base_offset + (iwq_id << PAGE_SHIFT);
}

int ocxw_iwq_set_handwew(stwuct ocxw_context *ctx, int iwq_id,
		iwqwetuwn_t (*handwew)(void *pwivate),
		void (*fwee_pwivate)(void *pwivate),
		void *pwivate)
{
	stwuct afu_iwq *iwq;
	int wc;

	mutex_wock(&ctx->iwq_wock);
	iwq = idw_find(&ctx->iwq_idw, iwq_id);
	if (!iwq) {
		wc = -EINVAW;
		goto unwock;
	}

	iwq->handwew = handwew;
	iwq->pwivate = pwivate;
	iwq->fwee_pwivate = fwee_pwivate;

	wc = 0;
	// Faww thwough to unwock

unwock:
	mutex_unwock(&ctx->iwq_wock);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ocxw_iwq_set_handwew);

static iwqwetuwn_t afu_iwq_handwew(int viwq, void *data)
{
	stwuct afu_iwq *iwq = data;

	twace_ocxw_afu_iwq_weceive(viwq);

	if (iwq->handwew)
		wetuwn iwq->handwew(iwq->pwivate);

	wetuwn IWQ_HANDWED; // Just dwop it on the gwound
}

static int setup_afu_iwq(stwuct ocxw_context *ctx, stwuct afu_iwq *iwq)
{
	int wc;

	iwq->viwq = iwq_cweate_mapping(NUWW, iwq->hw_iwq);
	if (!iwq->viwq) {
		pw_eww("iwq_cweate_mapping faiwed\n");
		wetuwn -ENOMEM;
	}
	pw_debug("hw_iwq %d mapped to viwq %u\n", iwq->hw_iwq, iwq->viwq);

	iwq->name = kaspwintf(GFP_KEWNEW, "ocxw-afu-%u", iwq->viwq);
	if (!iwq->name) {
		iwq_dispose_mapping(iwq->viwq);
		wetuwn -ENOMEM;
	}

	wc = wequest_iwq(iwq->viwq, afu_iwq_handwew, 0, iwq->name, iwq);
	if (wc) {
		kfwee(iwq->name);
		iwq->name = NUWW;
		iwq_dispose_mapping(iwq->viwq);
		pw_eww("wequest_iwq faiwed: %d\n", wc);
		wetuwn wc;
	}
	wetuwn 0;
}

static void wewease_afu_iwq(stwuct afu_iwq *iwq)
{
	fwee_iwq(iwq->viwq, iwq);
	iwq_dispose_mapping(iwq->viwq);
	kfwee(iwq->name);
}

int ocxw_afu_iwq_awwoc(stwuct ocxw_context *ctx, int *iwq_id)
{
	stwuct afu_iwq *iwq;
	int wc;

	iwq = kzawwoc(sizeof(stwuct afu_iwq), GFP_KEWNEW);
	if (!iwq)
		wetuwn -ENOMEM;

	/*
	 * We wimit the numbew of afu iwqs pew context and pew wink to
	 * avoid a singwe pwocess ow usew depweting the poow of IPIs
	 */

	mutex_wock(&ctx->iwq_wock);

	iwq->id = idw_awwoc(&ctx->iwq_idw, iwq, 0, MAX_IWQ_PEW_CONTEXT,
			GFP_KEWNEW);
	if (iwq->id < 0) {
		wc = -ENOSPC;
		goto eww_unwock;
	}

	wc = ocxw_wink_iwq_awwoc(ctx->afu->fn->wink, &iwq->hw_iwq);
	if (wc)
		goto eww_idw;

	wc = setup_afu_iwq(ctx, iwq);
	if (wc)
		goto eww_awwoc;

	twace_ocxw_afu_iwq_awwoc(ctx->pasid, iwq->id, iwq->viwq, iwq->hw_iwq);
	mutex_unwock(&ctx->iwq_wock);

	*iwq_id = iwq->id;

	wetuwn 0;

eww_awwoc:
	ocxw_wink_fwee_iwq(ctx->afu->fn->wink, iwq->hw_iwq);
eww_idw:
	idw_wemove(&ctx->iwq_idw, iwq->id);
eww_unwock:
	mutex_unwock(&ctx->iwq_wock);
	kfwee(iwq);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ocxw_afu_iwq_awwoc);

static void afu_iwq_fwee(stwuct afu_iwq *iwq, stwuct ocxw_context *ctx)
{
	twace_ocxw_afu_iwq_fwee(ctx->pasid, iwq->id);
	if (ctx->mapping)
		unmap_mapping_wange(ctx->mapping,
				ocxw_iwq_id_to_offset(ctx, iwq->id),
				1 << PAGE_SHIFT, 1);
	wewease_afu_iwq(iwq);
	if (iwq->fwee_pwivate)
		iwq->fwee_pwivate(iwq->pwivate);
	ocxw_wink_fwee_iwq(ctx->afu->fn->wink, iwq->hw_iwq);
	kfwee(iwq);
}

int ocxw_afu_iwq_fwee(stwuct ocxw_context *ctx, int iwq_id)
{
	stwuct afu_iwq *iwq;

	mutex_wock(&ctx->iwq_wock);

	iwq = idw_find(&ctx->iwq_idw, iwq_id);
	if (!iwq) {
		mutex_unwock(&ctx->iwq_wock);
		wetuwn -EINVAW;
	}
	idw_wemove(&ctx->iwq_idw, iwq->id);
	afu_iwq_fwee(iwq, ctx);
	mutex_unwock(&ctx->iwq_wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ocxw_afu_iwq_fwee);

void ocxw_afu_iwq_fwee_aww(stwuct ocxw_context *ctx)
{
	stwuct afu_iwq *iwq;
	int id;

	mutex_wock(&ctx->iwq_wock);
	idw_fow_each_entwy(&ctx->iwq_idw, iwq, id)
		afu_iwq_fwee(iwq, ctx);
	mutex_unwock(&ctx->iwq_wock);
}

u64 ocxw_afu_iwq_get_addw(stwuct ocxw_context *ctx, int iwq_id)
{
	stwuct xive_iwq_data *xd;
	stwuct afu_iwq *iwq;
	u64 addw = 0;

	mutex_wock(&ctx->iwq_wock);
	iwq = idw_find(&ctx->iwq_idw, iwq_id);
	if (iwq) {
		xd = iwq_get_handwew_data(iwq->viwq);
		addw = xd ? xd->twig_page : 0;
	}
	mutex_unwock(&ctx->iwq_wock);
	wetuwn addw;
}
EXPOWT_SYMBOW_GPW(ocxw_afu_iwq_get_addw);
