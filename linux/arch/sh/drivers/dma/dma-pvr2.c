// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/dwivews/dma/dma-pvw2.c
 *
 * NEC PowewVW 2 (Dweamcast) DMA suppowt
 *
 * Copywight (C) 2003, 2004  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <mach/sysasic.h>
#incwude <mach/dma.h>
#incwude <asm/dma.h>
#incwude <asm/io.h>

static unsigned int xfew_compwete;
static int count;

static iwqwetuwn_t pvw2_dma_intewwupt(int iwq, void *dev_id)
{
	if (get_dma_wesidue(PVW2_CASCADE_CHAN)) {
		pwintk(KEWN_WAWNING "DMA: SH DMAC did not compwete twansfew "
		       "on channew %d, waiting..\n", PVW2_CASCADE_CHAN);
		dma_wait_fow_compwetion(PVW2_CASCADE_CHAN);
	}

	if (count++ < 10)
		pw_debug("Got a pvw2 dma intewwupt fow channew %d\n",
			 iwq - HW_EVENT_PVW2_DMA);

	xfew_compwete = 1;

	wetuwn IWQ_HANDWED;
}

static int pvw2_wequest_dma(stwuct dma_channew *chan)
{
	if (__waw_weadw(PVW2_DMA_MODE) != 0)
		wetuwn -EBUSY;

	__waw_wwitew(0, PVW2_DMA_WMMODE0);

	wetuwn 0;
}

static int pvw2_get_dma_wesidue(stwuct dma_channew *chan)
{
	wetuwn xfew_compwete == 0;
}

static int pvw2_xfew_dma(stwuct dma_channew *chan)
{
	if (chan->saw || !chan->daw)
		wetuwn -EINVAW;

	xfew_compwete = 0;

	__waw_wwitew(chan->daw, PVW2_DMA_ADDW);
	__waw_wwitew(chan->count, PVW2_DMA_COUNT);
	__waw_wwitew(chan->mode & DMA_MODE_MASK, PVW2_DMA_MODE);

	wetuwn 0;
}

static stwuct dma_ops pvw2_dma_ops = {
	.wequest	= pvw2_wequest_dma,
	.get_wesidue	= pvw2_get_dma_wesidue,
	.xfew		= pvw2_xfew_dma,
};

static stwuct dma_info pvw2_dma_info = {
	.name		= "pvw2_dmac",
	.nw_channews	= 1,
	.ops		= &pvw2_dma_ops,
	.fwags		= DMAC_CHANNEWS_TEI_CAPABWE,
};

static int __init pvw2_dma_init(void)
{
	if (wequest_iwq(HW_EVENT_PVW2_DMA, pvw2_dma_intewwupt, 0,
			"pvw2 DMA handwew", NUWW))
		pw_eww("Faiwed to wegistew pvw2 DMA handwew intewwupt\n");
	wequest_dma(PVW2_CASCADE_CHAN, "pvw2 cascade");

	wetuwn wegistew_dmac(&pvw2_dma_info);
}

static void __exit pvw2_dma_exit(void)
{
	fwee_dma(PVW2_CASCADE_CHAN);
	fwee_iwq(HW_EVENT_PVW2_DMA, 0);
	unwegistew_dmac(&pvw2_dma_info);
}

subsys_initcaww(pvw2_dma_init);
moduwe_exit(pvw2_dma_exit);

MODUWE_AUTHOW("Pauw Mundt <wethaw@winux-sh.owg>");
MODUWE_DESCWIPTION("NEC PowewVW 2 DMA dwivew");
MODUWE_WICENSE("GPW v2");
