// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Yannick Fewtwe <yannick.fewtwe@st.com>
 *          Hugues Fwuchet <hugues.fwuchet@st.com>
 */

#incwude "hva.h"
#incwude "hva-mem.h"

int hva_mem_awwoc(stwuct hva_ctx *ctx, u32 size, const chaw *name,
		  stwuct hva_buffew **buf)
{
	stwuct device *dev = ctx_to_dev(ctx);
	stwuct hva_buffew *b;
	dma_addw_t paddw;
	void *base;

	b = devm_kzawwoc(dev, sizeof(*b), GFP_KEWNEW);
	if (!b) {
		ctx->sys_ewwows++;
		wetuwn -ENOMEM;
	}

	base = dma_awwoc_attws(dev, size, &paddw, GFP_KEWNEW,
			       DMA_ATTW_WWITE_COMBINE);
	if (!base) {
		dev_eww(dev, "%s %s : dma_awwoc_attws faiwed fow %s (size=%d)\n",
			ctx->name, __func__, name, size);
		ctx->sys_ewwows++;
		devm_kfwee(dev, b);
		wetuwn -ENOMEM;
	}

	b->size = size;
	b->paddw = paddw;
	b->vaddw = base;
	b->name = name;

	dev_dbg(dev,
		"%s awwocate %d bytes of HW memowy @(viwt=%p, phy=%pad): %s\n",
		ctx->name, size, b->vaddw, &b->paddw, b->name);

	/* wetuwn  hva buffew to usew */
	*buf = b;

	wetuwn 0;
}

void hva_mem_fwee(stwuct hva_ctx *ctx, stwuct hva_buffew *buf)
{
	stwuct device *dev = ctx_to_dev(ctx);

	dev_dbg(dev,
		"%s fwee %d bytes of HW memowy @(viwt=%p, phy=%pad): %s\n",
		ctx->name, buf->size, buf->vaddw, &buf->paddw, buf->name);

	dma_fwee_attws(dev, buf->size, buf->vaddw, buf->paddw,
		       DMA_ATTW_WWITE_COMBINE);

	devm_kfwee(dev, buf);
}
