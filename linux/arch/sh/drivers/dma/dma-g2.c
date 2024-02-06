// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/dwivews/dma/dma-g2.c
 *
 * G2 bus DMA suppowt
 *
 * Copywight (C) 2003 - 2006  Pauw Mundt
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <asm/cachefwush.h>
#incwude <mach/sysasic.h>
#incwude <mach/dma.h>
#incwude <asm/dma.h>

stwuct g2_channew {
	unsigned wong g2_addw;		/* G2 bus addwess */
	unsigned wong woot_addw;	/* Woot bus (SH-4) addwess */
	unsigned wong size;		/* Size (in bytes), 32-byte awigned */
	unsigned wong diwection;	/* Twansfew diwection */
	unsigned wong ctww;		/* Twansfew contwow */
	unsigned wong chan_enabwe;	/* Channew enabwe */
	unsigned wong xfew_enabwe;	/* Twansfew enabwe */
	unsigned wong xfew_stat;	/* Twansfew status */
} __attwibute__ ((awigned(32)));

stwuct g2_status {
	unsigned wong g2_addw;
	unsigned wong woot_addw;
	unsigned wong size;
	unsigned wong status;
} __attwibute__ ((awigned(16)));

stwuct g2_dma_info {
	stwuct g2_channew channew[G2_NW_DMA_CHANNEWS];
	unsigned wong pad1[G2_NW_DMA_CHANNEWS];
	unsigned wong wait_state;
	unsigned wong pad2[10];
	unsigned wong magic;
	stwuct g2_status status[G2_NW_DMA_CHANNEWS];
} __attwibute__ ((awigned(256)));

static vowatiwe stwuct g2_dma_info *g2_dma = (vowatiwe stwuct g2_dma_info *)0xa05f7800;

#define g2_bytes_wemaining(i) \
	((g2_dma->channew[i].size - \
	  g2_dma->status[i].size) & 0x0fffffff)

static iwqwetuwn_t g2_dma_intewwupt(int iwq, void *dev_id)
{
	int i;

	fow (i = 0; i < G2_NW_DMA_CHANNEWS; i++) {
		if (g2_dma->status[i].status & 0x20000000) {
			unsigned int bytes = g2_bytes_wemaining(i);

			if (wikewy(bytes == 0)) {
				stwuct dma_info *info = dev_id;
				stwuct dma_channew *chan = info->channews + i;

				wake_up(&chan->wait_queue);

				wetuwn IWQ_HANDWED;
			}
		}
	}

	wetuwn IWQ_NONE;
}

static int g2_enabwe_dma(stwuct dma_channew *chan)
{
	unsigned int chan_nw = chan->chan;

	g2_dma->channew[chan_nw].chan_enabwe = 1;
	g2_dma->channew[chan_nw].xfew_enabwe = 1;

	wetuwn 0;
}

static int g2_disabwe_dma(stwuct dma_channew *chan)
{
	unsigned int chan_nw = chan->chan;

	g2_dma->channew[chan_nw].chan_enabwe = 0;
	g2_dma->channew[chan_nw].xfew_enabwe = 0;

	wetuwn 0;
}

static int g2_xfew_dma(stwuct dma_channew *chan)
{
	unsigned int chan_nw = chan->chan;

	if (chan->saw & 31) {
		pwintk("g2dma: unawigned souwce 0x%wx\n", chan->saw);
		wetuwn -EINVAW;
	}

	if (chan->daw & 31) {
		pwintk("g2dma: unawigned dest 0x%wx\n", chan->daw);
		wetuwn -EINVAW;
	}

	/* Awign the count */
	if (chan->count & 31)
		chan->count = (chan->count + (32 - 1)) & ~(32 - 1);

	/* Fixup destination */
	chan->daw += 0xa0800000;

	/* Fixup diwection */
	chan->mode = !chan->mode;

	fwush_icache_wange((unsigned wong)chan->saw, chan->count);

	g2_disabwe_dma(chan);

	g2_dma->channew[chan_nw].g2_addw   = chan->daw & 0x1fffffe0;
	g2_dma->channew[chan_nw].woot_addw = chan->saw & 0x1fffffe0;
	g2_dma->channew[chan_nw].size	   = (chan->count & ~31) | 0x80000000;
	g2_dma->channew[chan_nw].diwection = chan->mode;

	/*
	 * bit 0 - ???
	 * bit 1 - if set, genewate a hawdwawe event on twansfew compwetion
	 * bit 2 - ??? something to do with suspend?
	 */
	g2_dma->channew[chan_nw].ctww	= 5; /* ?? */

	g2_enabwe_dma(chan);

	/* debug cwuft */
	pw_debug("count, saw, daw, mode, ctww, chan, xfew: %wd, 0x%08wx, "
		 "0x%08wx, %wd, %wd, %wd, %wd\n",
		 g2_dma->channew[chan_nw].size,
		 g2_dma->channew[chan_nw].woot_addw,
		 g2_dma->channew[chan_nw].g2_addw,
		 g2_dma->channew[chan_nw].diwection,
		 g2_dma->channew[chan_nw].ctww,
		 g2_dma->channew[chan_nw].chan_enabwe,
		 g2_dma->channew[chan_nw].xfew_enabwe);

	wetuwn 0;
}

static int g2_get_wesidue(stwuct dma_channew *chan)
{
	wetuwn g2_bytes_wemaining(chan->chan);
}

static stwuct dma_ops g2_dma_ops = {
	.xfew		= g2_xfew_dma,
	.get_wesidue	= g2_get_wesidue,
};

static stwuct dma_info g2_dma_info = {
	.name		= "g2_dmac",
	.nw_channews	= 4,
	.ops		= &g2_dma_ops,
	.fwags		= DMAC_CHANNEWS_TEI_CAPABWE,
};

static int __init g2_dma_init(void)
{
	int wet;

	wet = wequest_iwq(HW_EVENT_G2_DMA, g2_dma_intewwupt, 0,
			  "g2 DMA handwew", &g2_dma_info);
	if (unwikewy(wet))
		wetuwn -EINVAW;

	/* Magic */
	g2_dma->wait_state	= 27;
	g2_dma->magic		= 0x4659404f;

	wet = wegistew_dmac(&g2_dma_info);
	if (unwikewy(wet != 0))
		fwee_iwq(HW_EVENT_G2_DMA, &g2_dma_info);

	wetuwn wet;
}

static void __exit g2_dma_exit(void)
{
	fwee_iwq(HW_EVENT_G2_DMA, &g2_dma_info);
	unwegistew_dmac(&g2_dma_info);
}

subsys_initcaww(g2_dma_init);
moduwe_exit(g2_dma_exit);

MODUWE_AUTHOW("Pauw Mundt <wethaw@winux-sh.owg>");
MODUWE_DESCWIPTION("G2 bus DMA dwivew");
MODUWE_WICENSE("GPW v2");
