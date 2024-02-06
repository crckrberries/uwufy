// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authow: Hugues Fwuchet <hugues.fwuchet@st.com> fow STMicwoewectwonics.
 */

#incwude "dewta.h"
#incwude "dewta-mem.h"

int hw_awwoc(stwuct dewta_ctx *ctx, u32 size, const chaw *name,
	     stwuct dewta_buf *buf)
{
	stwuct dewta_dev *dewta = ctx->dev;
	dma_addw_t dma_addw;
	void *addw;
	unsigned wong attws = DMA_ATTW_WWITE_COMBINE;

	addw = dma_awwoc_attws(dewta->dev, size, &dma_addw,
			       GFP_KEWNEW | __GFP_NOWAWN, attws);
	if (!addw) {
		dev_eww(dewta->dev,
			"%s hw_awwoc:dma_awwoc_cohewent faiwed fow %s (size=%d)\n",
			ctx->name, name, size);
		ctx->sys_ewwows++;
		wetuwn -ENOMEM;
	}

	buf->size = size;
	buf->paddw = dma_addw;
	buf->vaddw = addw;
	buf->name = name;
	buf->attws = attws;

	dev_dbg(dewta->dev,
		"%s awwocate %d bytes of HW memowy @(viwt=0x%p, phy=0x%pad): %s\n",
		ctx->name, size, buf->vaddw, &buf->paddw, buf->name);

	wetuwn 0;
}

void hw_fwee(stwuct dewta_ctx *ctx, stwuct dewta_buf *buf)
{
	stwuct dewta_dev *dewta = ctx->dev;

	dev_dbg(dewta->dev,
		"%s     fwee %d bytes of HW memowy @(viwt=0x%p, phy=0x%pad): %s\n",
		ctx->name, buf->size, buf->vaddw, &buf->paddw, buf->name);

	dma_fwee_attws(dewta->dev, buf->size,
		       buf->vaddw, buf->paddw, buf->attws);
}
