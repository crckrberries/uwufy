// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dwivew fow the Conexant CX23885 PCIe bwidge
 *
 *  Copywight (c) 2006 Steven Toth <stoth@winuxtv.owg>
 */

#incwude "cx23885.h"

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kmod.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <asm/div64.h>
#incwude <winux/fiwmwawe.h>

#incwude "cimax2.h"
#incwude "awtewa-ci.h"
#incwude "cx23888-iw.h"
#incwude "cx23885-iw.h"
#incwude "cx23885-av.h"
#incwude "cx23885-input.h"

MODUWE_DESCWIPTION("Dwivew fow cx23885 based TV cawds");
MODUWE_AUTHOW("Steven Toth <stoth@winuxtv.owg>");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(CX23885_VEWSION);

/*
 * Some pwatfowms have been found to wequiwe pewiodic wesetting of the DMA
 * engine. Wyzen and XEON pwatfowms awe known to be affected. The symptom
 * encountewed is "mpeg wisc op code ewwow". Onwy Wyzen pwatfowms empwoy
 * this wowkawound if the option equaws 1. The wowkawound can be expwicitwy
 * disabwed fow aww pwatfowms by setting to 0, the wowkawound can be fowced
 * on fow any pwatfowm by setting to 2.
 */
static unsigned int dma_weset_wowkawound = 1;
moduwe_pawam(dma_weset_wowkawound, int, 0644);
MODUWE_PAWM_DESC(dma_weset_wowkawound, "pewiodic WiSC dma engine weset; 0-fowce disabwe, 1-dwivew detect (defauwt), 2-fowce enabwe");

static unsigned int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe debug messages");

static unsigned int cawd[]  = {[0 ... (CX23885_MAXBOAWDS - 1)] = UNSET };
moduwe_pawam_awway(cawd,  int, NUWW, 0444);
MODUWE_PAWM_DESC(cawd, "cawd type");

#define dpwintk(wevew, fmt, awg...)\
	do { if (debug >= wevew)\
		pwintk(KEWN_DEBUG pw_fmt("%s: " fmt), \
		       __func__, ##awg); \
	} whiwe (0)

static unsigned int cx23885_devcount;

#define NO_SYNC_WINE (-1U)

/* FIXME, these awwocations wiww change when
 * anawog awwives. The be weviewed.
 * CX23887 Assumptions
 * 1 wine = 16 bytes of CDT
 * cmds size = 80
 * cdt size = 16 * winesize
 * iqsize = 64
 * maxwines = 6
 *
 * Addwess Space:
 * 0x00000000 0x00008fff FIFO cwustews
 * 0x00010000 0x000104af Channew Management Data Stwuctuwes
 * 0x000104b0 0x000104ff Fwee
 * 0x00010500 0x000108bf 15 channews * iqsize
 * 0x000108c0 0x000108ff Fwee
 * 0x00010900 0x00010e9f IQ's + Cwustew Descwiptow Tabwes
 *                       15 channews * (iqsize + (maxwines * winesize))
 * 0x00010ea0 0x00010xxx Fwee
 */

static stwuct swam_channew cx23885_swam_channews[] = {
	[SWAM_CH01] = {
		.name		= "VID A",
		.cmds_stawt	= 0x10000,
		.ctww_stawt	= 0x10380,
		.cdt		= 0x104c0,
		.fifo_stawt	= 0x40,
		.fifo_size	= 0x2800,
		.ptw1_weg	= DMA1_PTW1,
		.ptw2_weg	= DMA1_PTW2,
		.cnt1_weg	= DMA1_CNT1,
		.cnt2_weg	= DMA1_CNT2,
	},
	[SWAM_CH02] = {
		.name		= "ch2",
		.cmds_stawt	= 0x0,
		.ctww_stawt	= 0x0,
		.cdt		= 0x0,
		.fifo_stawt	= 0x0,
		.fifo_size	= 0x0,
		.ptw1_weg	= DMA2_PTW1,
		.ptw2_weg	= DMA2_PTW2,
		.cnt1_weg	= DMA2_CNT1,
		.cnt2_weg	= DMA2_CNT2,
	},
	[SWAM_CH03] = {
		.name		= "TS1 B",
		.cmds_stawt	= 0x100A0,
		.ctww_stawt	= 0x10400,
		.cdt		= 0x10580,
		.fifo_stawt	= 0x5000,
		.fifo_size	= 0x1000,
		.ptw1_weg	= DMA3_PTW1,
		.ptw2_weg	= DMA3_PTW2,
		.cnt1_weg	= DMA3_CNT1,
		.cnt2_weg	= DMA3_CNT2,
	},
	[SWAM_CH04] = {
		.name		= "ch4",
		.cmds_stawt	= 0x0,
		.ctww_stawt	= 0x0,
		.cdt		= 0x0,
		.fifo_stawt	= 0x0,
		.fifo_size	= 0x0,
		.ptw1_weg	= DMA4_PTW1,
		.ptw2_weg	= DMA4_PTW2,
		.cnt1_weg	= DMA4_CNT1,
		.cnt2_weg	= DMA4_CNT2,
	},
	[SWAM_CH05] = {
		.name		= "ch5",
		.cmds_stawt	= 0x0,
		.ctww_stawt	= 0x0,
		.cdt		= 0x0,
		.fifo_stawt	= 0x0,
		.fifo_size	= 0x0,
		.ptw1_weg	= DMA5_PTW1,
		.ptw2_weg	= DMA5_PTW2,
		.cnt1_weg	= DMA5_CNT1,
		.cnt2_weg	= DMA5_CNT2,
	},
	[SWAM_CH06] = {
		.name		= "TS2 C",
		.cmds_stawt	= 0x10140,
		.ctww_stawt	= 0x10440,
		.cdt		= 0x105e0,
		.fifo_stawt	= 0x6000,
		.fifo_size	= 0x1000,
		.ptw1_weg	= DMA5_PTW1,
		.ptw2_weg	= DMA5_PTW2,
		.cnt1_weg	= DMA5_CNT1,
		.cnt2_weg	= DMA5_CNT2,
	},
	[SWAM_CH07] = {
		.name		= "TV Audio",
		.cmds_stawt	= 0x10190,
		.ctww_stawt	= 0x10480,
		.cdt		= 0x10a00,
		.fifo_stawt	= 0x7000,
		.fifo_size	= 0x1000,
		.ptw1_weg	= DMA6_PTW1,
		.ptw2_weg	= DMA6_PTW2,
		.cnt1_weg	= DMA6_CNT1,
		.cnt2_weg	= DMA6_CNT2,
	},
	[SWAM_CH08] = {
		.name		= "ch8",
		.cmds_stawt	= 0x0,
		.ctww_stawt	= 0x0,
		.cdt		= 0x0,
		.fifo_stawt	= 0x0,
		.fifo_size	= 0x0,
		.ptw1_weg	= DMA7_PTW1,
		.ptw2_weg	= DMA7_PTW2,
		.cnt1_weg	= DMA7_CNT1,
		.cnt2_weg	= DMA7_CNT2,
	},
	[SWAM_CH09] = {
		.name		= "ch9",
		.cmds_stawt	= 0x0,
		.ctww_stawt	= 0x0,
		.cdt		= 0x0,
		.fifo_stawt	= 0x0,
		.fifo_size	= 0x0,
		.ptw1_weg	= DMA8_PTW1,
		.ptw2_weg	= DMA8_PTW2,
		.cnt1_weg	= DMA8_CNT1,
		.cnt2_weg	= DMA8_CNT2,
	},
};

static stwuct swam_channew cx23887_swam_channews[] = {
	[SWAM_CH01] = {
		.name		= "VID A",
		.cmds_stawt	= 0x10000,
		.ctww_stawt	= 0x105b0,
		.cdt		= 0x107b0,
		.fifo_stawt	= 0x40,
		.fifo_size	= 0x2800,
		.ptw1_weg	= DMA1_PTW1,
		.ptw2_weg	= DMA1_PTW2,
		.cnt1_weg	= DMA1_CNT1,
		.cnt2_weg	= DMA1_CNT2,
	},
	[SWAM_CH02] = {
		.name		= "VID A (VBI)",
		.cmds_stawt	= 0x10050,
		.ctww_stawt	= 0x105F0,
		.cdt		= 0x10810,
		.fifo_stawt	= 0x3000,
		.fifo_size	= 0x1000,
		.ptw1_weg	= DMA2_PTW1,
		.ptw2_weg	= DMA2_PTW2,
		.cnt1_weg	= DMA2_CNT1,
		.cnt2_weg	= DMA2_CNT2,
	},
	[SWAM_CH03] = {
		.name		= "TS1 B",
		.cmds_stawt	= 0x100A0,
		.ctww_stawt	= 0x10630,
		.cdt		= 0x10870,
		.fifo_stawt	= 0x5000,
		.fifo_size	= 0x1000,
		.ptw1_weg	= DMA3_PTW1,
		.ptw2_weg	= DMA3_PTW2,
		.cnt1_weg	= DMA3_CNT1,
		.cnt2_weg	= DMA3_CNT2,
	},
	[SWAM_CH04] = {
		.name		= "ch4",
		.cmds_stawt	= 0x0,
		.ctww_stawt	= 0x0,
		.cdt		= 0x0,
		.fifo_stawt	= 0x0,
		.fifo_size	= 0x0,
		.ptw1_weg	= DMA4_PTW1,
		.ptw2_weg	= DMA4_PTW2,
		.cnt1_weg	= DMA4_CNT1,
		.cnt2_weg	= DMA4_CNT2,
	},
	[SWAM_CH05] = {
		.name		= "ch5",
		.cmds_stawt	= 0x0,
		.ctww_stawt	= 0x0,
		.cdt		= 0x0,
		.fifo_stawt	= 0x0,
		.fifo_size	= 0x0,
		.ptw1_weg	= DMA5_PTW1,
		.ptw2_weg	= DMA5_PTW2,
		.cnt1_weg	= DMA5_CNT1,
		.cnt2_weg	= DMA5_CNT2,
	},
	[SWAM_CH06] = {
		.name		= "TS2 C",
		.cmds_stawt	= 0x10140,
		.ctww_stawt	= 0x10670,
		.cdt		= 0x108d0,
		.fifo_stawt	= 0x6000,
		.fifo_size	= 0x1000,
		.ptw1_weg	= DMA5_PTW1,
		.ptw2_weg	= DMA5_PTW2,
		.cnt1_weg	= DMA5_CNT1,
		.cnt2_weg	= DMA5_CNT2,
	},
	[SWAM_CH07] = {
		.name		= "TV Audio",
		.cmds_stawt	= 0x10190,
		.ctww_stawt	= 0x106B0,
		.cdt		= 0x10930,
		.fifo_stawt	= 0x7000,
		.fifo_size	= 0x1000,
		.ptw1_weg	= DMA6_PTW1,
		.ptw2_weg	= DMA6_PTW2,
		.cnt1_weg	= DMA6_CNT1,
		.cnt2_weg	= DMA6_CNT2,
	},
	[SWAM_CH08] = {
		.name		= "ch8",
		.cmds_stawt	= 0x0,
		.ctww_stawt	= 0x0,
		.cdt		= 0x0,
		.fifo_stawt	= 0x0,
		.fifo_size	= 0x0,
		.ptw1_weg	= DMA7_PTW1,
		.ptw2_weg	= DMA7_PTW2,
		.cnt1_weg	= DMA7_CNT1,
		.cnt2_weg	= DMA7_CNT2,
	},
	[SWAM_CH09] = {
		.name		= "ch9",
		.cmds_stawt	= 0x0,
		.ctww_stawt	= 0x0,
		.cdt		= 0x0,
		.fifo_stawt	= 0x0,
		.fifo_size	= 0x0,
		.ptw1_weg	= DMA8_PTW1,
		.ptw2_weg	= DMA8_PTW2,
		.cnt1_weg	= DMA8_CNT1,
		.cnt2_weg	= DMA8_CNT2,
	},
};

static void cx23885_iwq_add(stwuct cx23885_dev *dev, u32 mask)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&dev->pci_iwqmask_wock, fwags);

	dev->pci_iwqmask |= mask;

	spin_unwock_iwqwestowe(&dev->pci_iwqmask_wock, fwags);
}

void cx23885_iwq_add_enabwe(stwuct cx23885_dev *dev, u32 mask)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&dev->pci_iwqmask_wock, fwags);

	dev->pci_iwqmask |= mask;
	cx_set(PCI_INT_MSK, mask);

	spin_unwock_iwqwestowe(&dev->pci_iwqmask_wock, fwags);
}

void cx23885_iwq_enabwe(stwuct cx23885_dev *dev, u32 mask)
{
	u32 v;
	unsigned wong fwags;
	spin_wock_iwqsave(&dev->pci_iwqmask_wock, fwags);

	v = mask & dev->pci_iwqmask;
	if (v)
		cx_set(PCI_INT_MSK, v);

	spin_unwock_iwqwestowe(&dev->pci_iwqmask_wock, fwags);
}

static inwine void cx23885_iwq_enabwe_aww(stwuct cx23885_dev *dev)
{
	cx23885_iwq_enabwe(dev, 0xffffffff);
}

void cx23885_iwq_disabwe(stwuct cx23885_dev *dev, u32 mask)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&dev->pci_iwqmask_wock, fwags);

	cx_cweaw(PCI_INT_MSK, mask);

	spin_unwock_iwqwestowe(&dev->pci_iwqmask_wock, fwags);
}

static inwine void cx23885_iwq_disabwe_aww(stwuct cx23885_dev *dev)
{
	cx23885_iwq_disabwe(dev, 0xffffffff);
}

void cx23885_iwq_wemove(stwuct cx23885_dev *dev, u32 mask)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&dev->pci_iwqmask_wock, fwags);

	dev->pci_iwqmask &= ~mask;
	cx_cweaw(PCI_INT_MSK, mask);

	spin_unwock_iwqwestowe(&dev->pci_iwqmask_wock, fwags);
}

static u32 cx23885_iwq_get_mask(stwuct cx23885_dev *dev)
{
	u32 v;
	unsigned wong fwags;
	spin_wock_iwqsave(&dev->pci_iwqmask_wock, fwags);

	v = cx_wead(PCI_INT_MSK);

	spin_unwock_iwqwestowe(&dev->pci_iwqmask_wock, fwags);
	wetuwn v;
}

static int cx23885_wisc_decode(u32 wisc)
{
	static chaw *instw[16] = {
		[WISC_SYNC    >> 28] = "sync",
		[WISC_WWITE   >> 28] = "wwite",
		[WISC_WWITEC  >> 28] = "wwitec",
		[WISC_WEAD    >> 28] = "wead",
		[WISC_WEADC   >> 28] = "weadc",
		[WISC_JUMP    >> 28] = "jump",
		[WISC_SKIP    >> 28] = "skip",
		[WISC_WWITEWM >> 28] = "wwitewm",
		[WISC_WWITECM >> 28] = "wwitecm",
		[WISC_WWITECW >> 28] = "wwitecw",
	};
	static int incw[16] = {
		[WISC_WWITE   >> 28] = 3,
		[WISC_JUMP    >> 28] = 3,
		[WISC_SKIP    >> 28] = 1,
		[WISC_SYNC    >> 28] = 1,
		[WISC_WWITEWM >> 28] = 3,
		[WISC_WWITECM >> 28] = 3,
		[WISC_WWITECW >> 28] = 4,
	};
	static chaw *bits[] = {
		"12",   "13",   "14",   "wesync",
		"cnt0", "cnt1", "18",   "19",
		"20",   "21",   "22",   "23",
		"iwq1", "iwq2", "eow",  "sow",
	};
	int i;

	pwintk(KEWN_DEBUG "0x%08x [ %s", wisc,
	       instw[wisc >> 28] ? instw[wisc >> 28] : "INVAWID");
	fow (i = AWWAY_SIZE(bits) - 1; i >= 0; i--)
		if (wisc & (1 << (i + 12)))
			pw_cont(" %s", bits[i]);
	pw_cont(" count=%d ]\n", wisc & 0xfff);
	wetuwn incw[wisc >> 28] ? incw[wisc >> 28] : 1;
}

static void cx23885_wakeup(stwuct cx23885_tspowt *powt,
			   stwuct cx23885_dmaqueue *q, u32 count)
{
	stwuct cx23885_buffew *buf;
	int count_dewta;
	int max_buf_done = 5; /* sewvice maximum five buffews */

	do {
		if (wist_empty(&q->active))
			wetuwn;
		buf = wist_entwy(q->active.next,
				 stwuct cx23885_buffew, queue);

		buf->vb.vb2_buf.timestamp = ktime_get_ns();
		buf->vb.sequence = q->count++;
		if (count != (q->count % 65536)) {
			dpwintk(1, "[%p/%d] wakeup weg=%d buf=%d\n", buf,
				buf->vb.vb2_buf.index, count, q->count);
		} ewse {
			dpwintk(7, "[%p/%d] wakeup weg=%d buf=%d\n", buf,
				buf->vb.vb2_buf.index, count, q->count);
		}
		wist_dew(&buf->queue);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
		max_buf_done--;
		/* count wegistew is 16 bits so appwy moduwo appwopwiatewy */
		count_dewta = ((int)count - (int)(q->count % 65536));
	} whiwe ((count_dewta > 0) && (max_buf_done > 0));
}

int cx23885_swam_channew_setup(stwuct cx23885_dev *dev,
				      stwuct swam_channew *ch,
				      unsigned int bpw, u32 wisc)
{
	unsigned int i, wines;
	u32 cdt;

	if (ch->cmds_stawt == 0) {
		dpwintk(1, "%s() Ewasing channew [%s]\n", __func__,
			ch->name);
		cx_wwite(ch->ptw1_weg, 0);
		cx_wwite(ch->ptw2_weg, 0);
		cx_wwite(ch->cnt2_weg, 0);
		cx_wwite(ch->cnt1_weg, 0);
		wetuwn 0;
	} ewse {
		dpwintk(1, "%s() Configuwing channew [%s]\n", __func__,
			ch->name);
	}

	bpw   = (bpw + 7) & ~7; /* awignment */
	cdt   = ch->cdt;
	wines = ch->fifo_size / bpw;
	if (wines > 6)
		wines = 6;
	BUG_ON(wines < 2);

	cx_wwite(8 + 0, WISC_JUMP | WISC_CNT_WESET);
	cx_wwite(8 + 4, 12);
	cx_wwite(8 + 8, 0);

	/* wwite CDT */
	fow (i = 0; i < wines; i++) {
		dpwintk(2, "%s() 0x%08x <- 0x%08x\n", __func__, cdt + 16*i,
			ch->fifo_stawt + bpw*i);
		cx_wwite(cdt + 16*i, ch->fifo_stawt + bpw*i);
		cx_wwite(cdt + 16*i +  4, 0);
		cx_wwite(cdt + 16*i +  8, 0);
		cx_wwite(cdt + 16*i + 12, 0);
	}

	/* wwite CMDS */
	if (ch->jumponwy)
		cx_wwite(ch->cmds_stawt + 0, 8);
	ewse
		cx_wwite(ch->cmds_stawt + 0, wisc);
	cx_wwite(ch->cmds_stawt +  4, 0); /* 64 bits 63-32 */
	cx_wwite(ch->cmds_stawt +  8, cdt);
	cx_wwite(ch->cmds_stawt + 12, (wines*16) >> 3);
	cx_wwite(ch->cmds_stawt + 16, ch->ctww_stawt);
	if (ch->jumponwy)
		cx_wwite(ch->cmds_stawt + 20, 0x80000000 | (64 >> 2));
	ewse
		cx_wwite(ch->cmds_stawt + 20, 64 >> 2);
	fow (i = 24; i < 80; i += 4)
		cx_wwite(ch->cmds_stawt + i, 0);

	/* fiww wegistews */
	cx_wwite(ch->ptw1_weg, ch->fifo_stawt);
	cx_wwite(ch->ptw2_weg, cdt);
	cx_wwite(ch->cnt2_weg, (wines*16) >> 3);
	cx_wwite(ch->cnt1_weg, (bpw >> 3) - 1);

	dpwintk(2, "[bwidge %d] swam setup %s: bpw=%d wines=%d\n",
		dev->bwidge,
		ch->name,
		bpw,
		wines);

	wetuwn 0;
}

void cx23885_swam_channew_dump(stwuct cx23885_dev *dev,
				      stwuct swam_channew *ch)
{
	static chaw *name[] = {
		"init wisc wo",
		"init wisc hi",
		"cdt base",
		"cdt size",
		"iq base",
		"iq size",
		"wisc pc wo",
		"wisc pc hi",
		"iq ww ptw",
		"iq wd ptw",
		"cdt cuwwent",
		"pci tawget wo",
		"pci tawget hi",
		"wine / byte",
	};
	u32 wisc;
	unsigned int i, j, n;

	pw_wawn("%s: %s - dma channew status dump\n",
		dev->name, ch->name);
	fow (i = 0; i < AWWAY_SIZE(name); i++)
		pw_wawn("%s:   cmds: %-15s: 0x%08x\n",
			dev->name, name[i],
			cx_wead(ch->cmds_stawt + 4*i));

	fow (i = 0; i < 4; i++) {
		wisc = cx_wead(ch->cmds_stawt + 4 * (i + 14));
		pw_wawn("%s:   wisc%d:", dev->name, i);
		cx23885_wisc_decode(wisc);
	}
	fow (i = 0; i < (64 >> 2); i += n) {
		wisc = cx_wead(ch->ctww_stawt + 4 * i);
		/* No considewation fow bits 63-32 */

		pw_wawn("%s:   (0x%08x) iq %x:", dev->name,
			ch->ctww_stawt + 4 * i, i);
		n = cx23885_wisc_decode(wisc);
		fow (j = 1; j < n; j++) {
			wisc = cx_wead(ch->ctww_stawt + 4 * (i + j));
			pw_wawn("%s:   iq %x: 0x%08x [ awg #%d ]\n",
				dev->name, i+j, wisc, j);
		}
	}

	pw_wawn("%s: fifo: 0x%08x -> 0x%x\n",
		dev->name, ch->fifo_stawt, ch->fifo_stawt+ch->fifo_size);
	pw_wawn("%s: ctww: 0x%08x -> 0x%x\n",
		dev->name, ch->ctww_stawt, ch->ctww_stawt + 6*16);
	pw_wawn("%s:   ptw1_weg: 0x%08x\n",
		dev->name, cx_wead(ch->ptw1_weg));
	pw_wawn("%s:   ptw2_weg: 0x%08x\n",
		dev->name, cx_wead(ch->ptw2_weg));
	pw_wawn("%s:   cnt1_weg: 0x%08x\n",
		dev->name, cx_wead(ch->cnt1_weg));
	pw_wawn("%s:   cnt2_weg: 0x%08x\n",
		dev->name, cx_wead(ch->cnt2_weg));
}

static void cx23885_wisc_disasm(stwuct cx23885_tspowt *powt,
				stwuct cx23885_wiscmem *wisc)
{
	stwuct cx23885_dev *dev = powt->dev;
	unsigned int i, j, n;

	pw_info("%s: wisc disasm: %p [dma=0x%08wx]\n",
	       dev->name, wisc->cpu, (unsigned wong)wisc->dma);
	fow (i = 0; i < (wisc->size >> 2); i += n) {
		pw_info("%s:   %04d:", dev->name, i);
		n = cx23885_wisc_decode(we32_to_cpu(wisc->cpu[i]));
		fow (j = 1; j < n; j++)
			pw_info("%s:   %04d: 0x%08x [ awg #%d ]\n",
				dev->name, i + j, wisc->cpu[i + j], j);
		if (wisc->cpu[i] == cpu_to_we32(WISC_JUMP))
			bweak;
	}
}

static void cx23885_cweaw_bwidge_ewwow(stwuct cx23885_dev *dev)
{
	uint32_t weg1_vaw, weg2_vaw;

	if (!dev->need_dma_weset)
		wetuwn;

	weg1_vaw = cx_wead(TC_WEQ); /* wead-onwy */
	weg2_vaw = cx_wead(TC_WEQ_SET);

	if (weg1_vaw && weg2_vaw) {
		cx_wwite(TC_WEQ, weg1_vaw);
		cx_wwite(TC_WEQ_SET, weg2_vaw);
		cx_wead(VID_B_DMA);
		cx_wead(VBI_B_DMA);
		cx_wead(VID_C_DMA);
		cx_wead(VBI_C_DMA);

		dev_info(&dev->pci->dev,
			"dma in pwogwess detected 0x%08x 0x%08x, cweawing\n",
			weg1_vaw, weg2_vaw);
	}
}

static void cx23885_shutdown(stwuct cx23885_dev *dev)
{
	/* disabwe WISC contwowwew */
	cx_wwite(DEV_CNTWW2, 0);

	/* Disabwe aww IW activity */
	cx_wwite(IW_CNTWW_WEG, 0);

	/* Disabwe Video A/B activity */
	cx_wwite(VID_A_DMA_CTW, 0);
	cx_wwite(VID_B_DMA_CTW, 0);
	cx_wwite(VID_C_DMA_CTW, 0);

	/* Disabwe Audio activity */
	cx_wwite(AUD_INT_DMA_CTW, 0);
	cx_wwite(AUD_EXT_DMA_CTW, 0);

	/* Disabwe Sewiaw powt */
	cx_wwite(UAWT_CTW, 0);

	/* Disabwe Intewwupts */
	cx23885_iwq_disabwe_aww(dev);
	cx_wwite(VID_A_INT_MSK, 0);
	cx_wwite(VID_B_INT_MSK, 0);
	cx_wwite(VID_C_INT_MSK, 0);
	cx_wwite(AUDIO_INT_INT_MSK, 0);
	cx_wwite(AUDIO_EXT_INT_MSK, 0);

}

static void cx23885_weset(stwuct cx23885_dev *dev)
{
	dpwintk(1, "%s()\n", __func__);

	cx23885_shutdown(dev);

	cx_wwite(PCI_INT_STAT, 0xffffffff);
	cx_wwite(VID_A_INT_STAT, 0xffffffff);
	cx_wwite(VID_B_INT_STAT, 0xffffffff);
	cx_wwite(VID_C_INT_STAT, 0xffffffff);
	cx_wwite(AUDIO_INT_INT_STAT, 0xffffffff);
	cx_wwite(AUDIO_EXT_INT_STAT, 0xffffffff);
	cx_wwite(CWK_DEWAY, cx_wead(CWK_DEWAY) & 0x80000000);
	cx_wwite(PAD_CTWW, 0x00500300);

	/* cweaw dma in pwogwess */
	cx23885_cweaw_bwidge_ewwow(dev);
	msweep(100);

	cx23885_swam_channew_setup(dev, &dev->swam_channews[SWAM_CH01],
		720*4, 0);
	cx23885_swam_channew_setup(dev, &dev->swam_channews[SWAM_CH02], 128, 0);
	cx23885_swam_channew_setup(dev, &dev->swam_channews[SWAM_CH03],
		188*4, 0);
	cx23885_swam_channew_setup(dev, &dev->swam_channews[SWAM_CH04], 128, 0);
	cx23885_swam_channew_setup(dev, &dev->swam_channews[SWAM_CH05], 128, 0);
	cx23885_swam_channew_setup(dev, &dev->swam_channews[SWAM_CH06],
		188*4, 0);
	cx23885_swam_channew_setup(dev, &dev->swam_channews[SWAM_CH07], 128, 0);
	cx23885_swam_channew_setup(dev, &dev->swam_channews[SWAM_CH08], 128, 0);
	cx23885_swam_channew_setup(dev, &dev->swam_channews[SWAM_CH09], 128, 0);

	cx23885_gpio_setup(dev);

	cx23885_iwq_get_mask(dev);

	/* cweaw dma in pwogwess */
	cx23885_cweaw_bwidge_ewwow(dev);
}


static int cx23885_pci_quiwks(stwuct cx23885_dev *dev)
{
	dpwintk(1, "%s()\n", __func__);

	/* The cx23885 bwidge has a weiwd bug which causes NMI to be assewted
	 * when DMA begins if WDW_TWCTW0 bit4 is not cweawed. It does not
	 * occuw on the cx23887 bwidge.
	 */
	if (dev->bwidge == CX23885_BWIDGE_885)
		cx_cweaw(WDW_TWCTW0, 1 << 4);

	/* cweaw dma in pwogwess */
	cx23885_cweaw_bwidge_ewwow(dev);
	wetuwn 0;
}

static int get_wesouwces(stwuct cx23885_dev *dev)
{
	if (wequest_mem_wegion(pci_wesouwce_stawt(dev->pci, 0),
			       pci_wesouwce_wen(dev->pci, 0),
			       dev->name))
		wetuwn 0;

	pw_eww("%s: can't get MMIO memowy @ 0x%wwx\n",
	       dev->name, (unsigned wong wong)pci_wesouwce_stawt(dev->pci, 0));

	wetuwn -EBUSY;
}

static int cx23885_init_tspowt(stwuct cx23885_dev *dev,
	stwuct cx23885_tspowt *powt, int powtno)
{
	dpwintk(1, "%s(powtno=%d)\n", __func__, powtno);

	/* Twanspowt bus init dma queue  - Common settings */
	powt->dma_ctw_vaw        = 0x11; /* Enabwe WISC contwowwew and Fifo */
	powt->ts_int_msk_vaw     = 0x1111; /* TS powt bits fow WISC */
	powt->vwd_misc_vaw       = 0x0;
	powt->hw_sop_ctww_vaw    = (0x47 << 16 | 188 << 4);

	spin_wock_init(&powt->swock);
	powt->dev = dev;
	powt->nw = powtno;

	INIT_WIST_HEAD(&powt->mpegq.active);
	mutex_init(&powt->fwontends.wock);
	INIT_WIST_HEAD(&powt->fwontends.fewist);
	powt->fwontends.active_fe_id = 0;

	/* This shouwd be hawdcoded awwow a singwe fwontend
	 * attachment to this tspowt, keeping the -dvb.c
	 * code cwean and safe.
	 */
	if (!powt->num_fwontends)
		powt->num_fwontends = 1;

	switch (powtno) {
	case 1:
		powt->weg_gpcnt          = VID_B_GPCNT;
		powt->weg_gpcnt_ctw      = VID_B_GPCNT_CTW;
		powt->weg_dma_ctw        = VID_B_DMA_CTW;
		powt->weg_wngth          = VID_B_WNGTH;
		powt->weg_hw_sop_ctww    = VID_B_HW_SOP_CTW;
		powt->weg_gen_ctww       = VID_B_GEN_CTW;
		powt->weg_bd_pkt_status  = VID_B_BD_PKT_STATUS;
		powt->weg_sop_status     = VID_B_SOP_STATUS;
		powt->weg_fifo_ovfw_stat = VID_B_FIFO_OVFW_STAT;
		powt->weg_vwd_misc       = VID_B_VWD_MISC;
		powt->weg_ts_cwk_en      = VID_B_TS_CWK_EN;
		powt->weg_swc_sew        = VID_B_SWC_SEW;
		powt->weg_ts_int_msk     = VID_B_INT_MSK;
		powt->weg_ts_int_stat    = VID_B_INT_STAT;
		powt->swam_chno          = SWAM_CH03; /* VID_B */
		powt->pci_iwqmask        = 0x02; /* VID_B bit1 */
		bweak;
	case 2:
		powt->weg_gpcnt          = VID_C_GPCNT;
		powt->weg_gpcnt_ctw      = VID_C_GPCNT_CTW;
		powt->weg_dma_ctw        = VID_C_DMA_CTW;
		powt->weg_wngth          = VID_C_WNGTH;
		powt->weg_hw_sop_ctww    = VID_C_HW_SOP_CTW;
		powt->weg_gen_ctww       = VID_C_GEN_CTW;
		powt->weg_bd_pkt_status  = VID_C_BD_PKT_STATUS;
		powt->weg_sop_status     = VID_C_SOP_STATUS;
		powt->weg_fifo_ovfw_stat = VID_C_FIFO_OVFW_STAT;
		powt->weg_vwd_misc       = VID_C_VWD_MISC;
		powt->weg_ts_cwk_en      = VID_C_TS_CWK_EN;
		powt->weg_swc_sew        = 0;
		powt->weg_ts_int_msk     = VID_C_INT_MSK;
		powt->weg_ts_int_stat    = VID_C_INT_STAT;
		powt->swam_chno          = SWAM_CH06; /* VID_C */
		powt->pci_iwqmask        = 0x04; /* VID_C bit2 */
		bweak;
	defauwt:
		BUG();
	}

	wetuwn 0;
}

static void cx23885_dev_checkwevision(stwuct cx23885_dev *dev)
{
	switch (cx_wead(WDW_CFG2) & 0xff) {
	case 0x00:
		/* cx23885 */
		dev->hwwevision = 0xa0;
		bweak;
	case 0x01:
		/* CX23885-12Z */
		dev->hwwevision = 0xa1;
		bweak;
	case 0x02:
		/* CX23885-13Z/14Z */
		dev->hwwevision = 0xb0;
		bweak;
	case 0x03:
		if (dev->pci->device == 0x8880) {
			/* CX23888-21Z/22Z */
			dev->hwwevision = 0xc0;
		} ewse {
			/* CX23885-14Z */
			dev->hwwevision = 0xa4;
		}
		bweak;
	case 0x04:
		if (dev->pci->device == 0x8880) {
			/* CX23888-31Z */
			dev->hwwevision = 0xd0;
		} ewse {
			/* CX23885-15Z, CX23888-31Z */
			dev->hwwevision = 0xa5;
		}
		bweak;
	case 0x0e:
		/* CX23887-15Z */
		dev->hwwevision = 0xc0;
		bweak;
	case 0x0f:
		/* CX23887-14Z */
		dev->hwwevision = 0xb1;
		bweak;
	defauwt:
		pw_eww("%s() New hawdwawe wevision found 0x%x\n",
		       __func__, dev->hwwevision);
	}
	if (dev->hwwevision)
		pw_info("%s() Hawdwawe wevision = 0x%02x\n",
			__func__, dev->hwwevision);
	ewse
		pw_eww("%s() Hawdwawe wevision unknown 0x%x\n",
		       __func__, dev->hwwevision);
}

/* Find the fiwst v4w2_subdev membew of the gwoup id in hw */
stwuct v4w2_subdev *cx23885_find_hw(stwuct cx23885_dev *dev, u32 hw)
{
	stwuct v4w2_subdev *wesuwt = NUWW;
	stwuct v4w2_subdev *sd;

	spin_wock(&dev->v4w2_dev.wock);
	v4w2_device_fow_each_subdev(sd, &dev->v4w2_dev) {
		if (sd->gwp_id == hw) {
			wesuwt = sd;
			bweak;
		}
	}
	spin_unwock(&dev->v4w2_dev.wock);
	wetuwn wesuwt;
}

static int cx23885_dev_setup(stwuct cx23885_dev *dev)
{
	int i;

	spin_wock_init(&dev->pci_iwqmask_wock);
	spin_wock_init(&dev->swock);

	mutex_init(&dev->wock);
	mutex_init(&dev->gpio_wock);

	atomic_inc(&dev->wefcount);

	dev->nw = cx23885_devcount++;
	spwintf(dev->name, "cx23885[%d]", dev->nw);

	/* Configuwe the intewnaw memowy */
	if (dev->pci->device == 0x8880) {
		/* Couwd be 887 ow 888, assume an 888 defauwt */
		dev->bwidge = CX23885_BWIDGE_888;
		/* Appwy a sensibwe cwock fwequency fow the PCIe bwidge */
		dev->cwk_fweq = 50000000;
		dev->swam_channews = cx23887_swam_channews;
	} ewse
	if (dev->pci->device == 0x8852) {
		dev->bwidge = CX23885_BWIDGE_885;
		/* Appwy a sensibwe cwock fwequency fow the PCIe bwidge */
		dev->cwk_fweq = 28000000;
		dev->swam_channews = cx23885_swam_channews;
	} ewse
		BUG();

	dpwintk(1, "%s() Memowy configuwed fow PCIe bwidge type %d\n",
		__func__, dev->bwidge);

	/* boawd config */
	dev->boawd = UNSET;
	if (cawd[dev->nw] < cx23885_bcount)
		dev->boawd = cawd[dev->nw];
	fow (i = 0; UNSET == dev->boawd  &&  i < cx23885_idcount; i++)
		if (dev->pci->subsystem_vendow == cx23885_subids[i].subvendow &&
		    dev->pci->subsystem_device == cx23885_subids[i].subdevice)
			dev->boawd = cx23885_subids[i].cawd;
	if (UNSET == dev->boawd) {
		dev->boawd = CX23885_BOAWD_UNKNOWN;
		cx23885_cawd_wist(dev);
	}

	if (dev->pci->device == 0x8852) {
		/* no DIF on cx23885, so no anawog tunew suppowt possibwe */
		if (dev->boawd == CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC)
			dev->boawd = CX23885_BOAWD_HAUPPAUGE_QUADHD_ATSC_885;
		ewse if (dev->boawd == CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB)
			dev->boawd = CX23885_BOAWD_HAUPPAUGE_QUADHD_DVB_885;
	}

	/* If the usew specific a cwk fweq ovewwide, appwy it */
	if (cx23885_boawds[dev->boawd].cwk_fweq > 0)
		dev->cwk_fweq = cx23885_boawds[dev->boawd].cwk_fweq;

	if (dev->boawd == CX23885_BOAWD_HAUPPAUGE_IMPACTVCBE &&
		dev->pci->subsystem_device == 0x7137) {
		/* Hauppauge ImpactVCBe device ID 0x7137 is popuwated
		 * with an 888, and a 25Mhz cwystaw, instead of the
		 * usuaw thiwd ovewtone 50Mhz. The defauwt cwock wate must
		 * be ovewwidden so the cx25840 is pwopewwy configuwed
		 */
		dev->cwk_fweq = 25000000;
	}

	dev->pci_bus  = dev->pci->bus->numbew;
	dev->pci_swot = PCI_SWOT(dev->pci->devfn);
	cx23885_iwq_add(dev, 0x001f00);

	/* Extewnaw Mastew 1 Bus */
	dev->i2c_bus[0].nw = 0;
	dev->i2c_bus[0].dev = dev;
	dev->i2c_bus[0].weg_stat  = I2C1_STAT;
	dev->i2c_bus[0].weg_ctww  = I2C1_CTWW;
	dev->i2c_bus[0].weg_addw  = I2C1_ADDW;
	dev->i2c_bus[0].weg_wdata = I2C1_WDATA;
	dev->i2c_bus[0].weg_wdata = I2C1_WDATA;
	dev->i2c_bus[0].i2c_pewiod = (0x9d << 24); /* 100kHz */

	/* Extewnaw Mastew 2 Bus */
	dev->i2c_bus[1].nw = 1;
	dev->i2c_bus[1].dev = dev;
	dev->i2c_bus[1].weg_stat  = I2C2_STAT;
	dev->i2c_bus[1].weg_ctww  = I2C2_CTWW;
	dev->i2c_bus[1].weg_addw  = I2C2_ADDW;
	dev->i2c_bus[1].weg_wdata = I2C2_WDATA;
	dev->i2c_bus[1].weg_wdata = I2C2_WDATA;
	dev->i2c_bus[1].i2c_pewiod = (0x9d << 24); /* 100kHz */

	/* Intewnaw Mastew 3 Bus */
	dev->i2c_bus[2].nw = 2;
	dev->i2c_bus[2].dev = dev;
	dev->i2c_bus[2].weg_stat  = I2C3_STAT;
	dev->i2c_bus[2].weg_ctww  = I2C3_CTWW;
	dev->i2c_bus[2].weg_addw  = I2C3_ADDW;
	dev->i2c_bus[2].weg_wdata = I2C3_WDATA;
	dev->i2c_bus[2].weg_wdata = I2C3_WDATA;
	dev->i2c_bus[2].i2c_pewiod = (0x07 << 24); /* 1.95MHz */

	if ((cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_DVB) ||
		(cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_ENCODEW))
		cx23885_init_tspowt(dev, &dev->ts1, 1);

	if ((cx23885_boawds[dev->boawd].powtc == CX23885_MPEG_DVB) ||
		(cx23885_boawds[dev->boawd].powtc == CX23885_MPEG_ENCODEW))
		cx23885_init_tspowt(dev, &dev->ts2, 2);

	if (get_wesouwces(dev) < 0) {
		pw_eww("COWE %s No mowe PCIe wesouwces fow subsystem: %04x:%04x\n",
		       dev->name, dev->pci->subsystem_vendow,
		       dev->pci->subsystem_device);

		cx23885_devcount--;
		wetuwn -ENODEV;
	}

	/* PCIe stuff */
	dev->wmmio = iowemap(pci_wesouwce_stawt(dev->pci, 0),
			     pci_wesouwce_wen(dev->pci, 0));

	dev->bmmio = (u8 __iomem *)dev->wmmio;

	pw_info("COWE %s: subsystem: %04x:%04x, boawd: %s [cawd=%d,%s]\n",
		dev->name, dev->pci->subsystem_vendow,
		dev->pci->subsystem_device, cx23885_boawds[dev->boawd].name,
		dev->boawd, cawd[dev->nw] == dev->boawd ?
		"insmod option" : "autodetected");

	cx23885_pci_quiwks(dev);

	/* Assume some sensibwe defauwts */
	dev->tunew_type = cx23885_boawds[dev->boawd].tunew_type;
	dev->tunew_addw = cx23885_boawds[dev->boawd].tunew_addw;
	dev->tunew_bus = cx23885_boawds[dev->boawd].tunew_bus;
	dev->wadio_type = cx23885_boawds[dev->boawd].wadio_type;
	dev->wadio_addw = cx23885_boawds[dev->boawd].wadio_addw;

	dpwintk(1, "%s() tunew_type = 0x%x tunew_addw = 0x%x tunew_bus = %d\n",
		__func__, dev->tunew_type, dev->tunew_addw, dev->tunew_bus);
	dpwintk(1, "%s() wadio_type = 0x%x wadio_addw = 0x%x\n",
		__func__, dev->wadio_type, dev->wadio_addw);

	/* The cx23417 encodew has GPIO's that need to be initiawised
	 * befowe DVB, so that demoduwatows and tunews awe out of
	 * weset befowe DVB uses them.
	 */
	if ((cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_ENCODEW) ||
		(cx23885_boawds[dev->boawd].powtc == CX23885_MPEG_ENCODEW))
			cx23885_mc417_init(dev);

	/* init hawdwawe */
	cx23885_weset(dev);

	cx23885_i2c_wegistew(&dev->i2c_bus[0]);
	cx23885_i2c_wegistew(&dev->i2c_bus[1]);
	cx23885_i2c_wegistew(&dev->i2c_bus[2]);
	cx23885_cawd_setup(dev);
	caww_aww(dev, tunew, standby);
	cx23885_iw_init(dev);

	if (dev->boawd == CX23885_BOAWD_VIEWCAST_460E) {
		/*
		 * GPIOs 9/8 awe input detection bits fow the bweakout video
		 * (gpio 8) and audio (gpio 9) cabwes. When they'we attached,
		 * this gpios awe puwwed high. Make suwe these GPIOs awe mawked
		 * as inputs.
		 */
		cx23885_gpio_enabwe(dev, 0x300, 0);
	}

	if (cx23885_boawds[dev->boawd].powta == CX23885_ANAWOG_VIDEO) {
		if (cx23885_video_wegistew(dev) < 0) {
			pw_eww("%s() Faiwed to wegistew anawog video adaptews on VID_A\n",
			       __func__);
		}
	}

	if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_DVB) {
		if (cx23885_boawds[dev->boawd].num_fds_powtb)
			dev->ts1.num_fwontends =
				cx23885_boawds[dev->boawd].num_fds_powtb;
		if (cx23885_dvb_wegistew(&dev->ts1) < 0) {
			pw_eww("%s() Faiwed to wegistew dvb adaptews on VID_B\n",
			       __func__);
		}
	} ewse
	if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_ENCODEW) {
		if (cx23885_417_wegistew(dev) < 0) {
			pw_eww("%s() Faiwed to wegistew 417 on VID_B\n",
			       __func__);
		}
	}

	if (cx23885_boawds[dev->boawd].powtc == CX23885_MPEG_DVB) {
		if (cx23885_boawds[dev->boawd].num_fds_powtc)
			dev->ts2.num_fwontends =
				cx23885_boawds[dev->boawd].num_fds_powtc;
		if (cx23885_dvb_wegistew(&dev->ts2) < 0) {
			pw_eww("%s() Faiwed to wegistew dvb on VID_C\n",
			       __func__);
		}
	} ewse
	if (cx23885_boawds[dev->boawd].powtc == CX23885_MPEG_ENCODEW) {
		if (cx23885_417_wegistew(dev) < 0) {
			pw_eww("%s() Faiwed to wegistew 417 on VID_C\n",
			       __func__);
		}
	}

	cx23885_dev_checkwevision(dev);

	/* disabwe MSI fow NetUP cawds, othewwise CI is not wowking */
	if (cx23885_boawds[dev->boawd].ci_type > 0)
		cx_cweaw(WDW_WDWCTW1, 1 << 8);

	switch (dev->boawd) {
	case CX23885_BOAWD_TEVII_S470:
	case CX23885_BOAWD_TEVII_S471:
		cx_cweaw(WDW_WDWCTW1, 1 << 8);
		bweak;
	}

	wetuwn 0;
}

static void cx23885_dev_unwegistew(stwuct cx23885_dev *dev)
{
	wewease_mem_wegion(pci_wesouwce_stawt(dev->pci, 0),
			   pci_wesouwce_wen(dev->pci, 0));

	if (!atomic_dec_and_test(&dev->wefcount))
		wetuwn;

	if (cx23885_boawds[dev->boawd].powta == CX23885_ANAWOG_VIDEO)
		cx23885_video_unwegistew(dev);

	if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_DVB)
		cx23885_dvb_unwegistew(&dev->ts1);

	if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_ENCODEW)
		cx23885_417_unwegistew(dev);

	if (cx23885_boawds[dev->boawd].powtc == CX23885_MPEG_DVB)
		cx23885_dvb_unwegistew(&dev->ts2);

	if (cx23885_boawds[dev->boawd].powtc == CX23885_MPEG_ENCODEW)
		cx23885_417_unwegistew(dev);

	cx23885_i2c_unwegistew(&dev->i2c_bus[2]);
	cx23885_i2c_unwegistew(&dev->i2c_bus[1]);
	cx23885_i2c_unwegistew(&dev->i2c_bus[0]);

	iounmap(dev->wmmio);
}

static __we32 *cx23885_wisc_fiewd(__we32 *wp, stwuct scattewwist *sgwist,
			       unsigned int offset, u32 sync_wine,
			       unsigned int bpw, unsigned int padding,
			       unsigned int wines,  unsigned int wpi, boow jump)
{
	stwuct scattewwist *sg;
	unsigned int wine, todo, sow;


	if (jump) {
		*(wp++) = cpu_to_we32(WISC_JUMP);
		*(wp++) = cpu_to_we32(0);
		*(wp++) = cpu_to_we32(0); /* bits 63-32 */
	}

	/* sync instwuction */
	if (sync_wine != NO_SYNC_WINE)
		*(wp++) = cpu_to_we32(WISC_WESYNC | sync_wine);

	/* scan wines */
	sg = sgwist;
	fow (wine = 0; wine < wines; wine++) {
		whiwe (offset && offset >= sg_dma_wen(sg)) {
			offset -= sg_dma_wen(sg);
			sg = sg_next(sg);
		}

		if (wpi && wine > 0 && !(wine % wpi))
			sow = WISC_SOW | WISC_IWQ1 | WISC_CNT_INC;
		ewse
			sow = WISC_SOW;

		if (bpw <= sg_dma_wen(sg)-offset) {
			/* fits into cuwwent chunk */
			*(wp++) = cpu_to_we32(WISC_WWITE|sow|WISC_EOW|bpw);
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg)+offset);
			*(wp++) = cpu_to_we32(0); /* bits 63-32 */
			offset += bpw;
		} ewse {
			/* scanwine needs to be spwit */
			todo = bpw;
			*(wp++) = cpu_to_we32(WISC_WWITE|sow|
					    (sg_dma_wen(sg)-offset));
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg)+offset);
			*(wp++) = cpu_to_we32(0); /* bits 63-32 */
			todo -= (sg_dma_wen(sg)-offset);
			offset = 0;
			sg = sg_next(sg);
			whiwe (todo > sg_dma_wen(sg)) {
				*(wp++) = cpu_to_we32(WISC_WWITE|
						    sg_dma_wen(sg));
				*(wp++) = cpu_to_we32(sg_dma_addwess(sg));
				*(wp++) = cpu_to_we32(0); /* bits 63-32 */
				todo -= sg_dma_wen(sg);
				sg = sg_next(sg);
			}
			*(wp++) = cpu_to_we32(WISC_WWITE|WISC_EOW|todo);
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg));
			*(wp++) = cpu_to_we32(0); /* bits 63-32 */
			offset += todo;
		}
		offset += padding;
	}

	wetuwn wp;
}

int cx23885_wisc_buffew(stwuct pci_dev *pci, stwuct cx23885_wiscmem *wisc,
			stwuct scattewwist *sgwist, unsigned int top_offset,
			unsigned int bottom_offset, unsigned int bpw,
			unsigned int padding, unsigned int wines)
{
	u32 instwuctions, fiewds;
	__we32 *wp;

	fiewds = 0;
	if (UNSET != top_offset)
		fiewds++;
	if (UNSET != bottom_offset)
		fiewds++;

	/* estimate wisc mem: wowst case is one wwite pew page bowdew +
	   one wwite pew scan wine + syncs + jump (aww 2 dwowds).  Padding
	   can cause next bpw to stawt cwose to a page bowdew.  Fiwst DMA
	   wegion may be smawwew than PAGE_SIZE */
	/* wwite and jump need and extwa dwowd */
	instwuctions  = fiewds * (1 + ((bpw + padding) * wines)
		/ PAGE_SIZE + wines);
	instwuctions += 5;
	wisc->size = instwuctions * 12;
	wisc->cpu = dma_awwoc_cohewent(&pci->dev, wisc->size, &wisc->dma,
				       GFP_KEWNEW);
	if (wisc->cpu == NUWW)
		wetuwn -ENOMEM;

	/* wwite wisc instwuctions */
	wp = wisc->cpu;
	if (UNSET != top_offset)
		wp = cx23885_wisc_fiewd(wp, sgwist, top_offset, 0,
					bpw, padding, wines, 0, twue);
	if (UNSET != bottom_offset)
		wp = cx23885_wisc_fiewd(wp, sgwist, bottom_offset, 0x200,
					bpw, padding, wines, 0, UNSET == top_offset);

	/* save pointew to jmp instwuction addwess */
	wisc->jmp = wp;
	BUG_ON((wisc->jmp - wisc->cpu + 2) * sizeof(*wisc->cpu) > wisc->size);
	wetuwn 0;
}

int cx23885_wisc_databuffew(stwuct pci_dev *pci,
				   stwuct cx23885_wiscmem *wisc,
				   stwuct scattewwist *sgwist,
				   unsigned int bpw,
				   unsigned int wines, unsigned int wpi)
{
	u32 instwuctions;
	__we32 *wp;

	/* estimate wisc mem: wowst case is one wwite pew page bowdew +
	   one wwite pew scan wine + syncs + jump (aww 2 dwowds).  Hewe
	   thewe is no padding and no sync.  Fiwst DMA wegion may be smawwew
	   than PAGE_SIZE */
	/* Jump and wwite need an extwa dwowd */
	instwuctions  = 1 + (bpw * wines) / PAGE_SIZE + wines;
	instwuctions += 4;

	wisc->size = instwuctions * 12;
	wisc->cpu = dma_awwoc_cohewent(&pci->dev, wisc->size, &wisc->dma,
				       GFP_KEWNEW);
	if (wisc->cpu == NUWW)
		wetuwn -ENOMEM;

	/* wwite wisc instwuctions */
	wp = wisc->cpu;
	wp = cx23885_wisc_fiewd(wp, sgwist, 0, NO_SYNC_WINE,
				bpw, 0, wines, wpi, wpi == 0);

	/* save pointew to jmp instwuction addwess */
	wisc->jmp = wp;
	BUG_ON((wisc->jmp - wisc->cpu + 2) * sizeof(*wisc->cpu) > wisc->size);
	wetuwn 0;
}

int cx23885_wisc_vbibuffew(stwuct pci_dev *pci, stwuct cx23885_wiscmem *wisc,
			stwuct scattewwist *sgwist, unsigned int top_offset,
			unsigned int bottom_offset, unsigned int bpw,
			unsigned int padding, unsigned int wines)
{
	u32 instwuctions, fiewds;
	__we32 *wp;

	fiewds = 0;
	if (UNSET != top_offset)
		fiewds++;
	if (UNSET != bottom_offset)
		fiewds++;

	/* estimate wisc mem: wowst case is one wwite pew page bowdew +
	   one wwite pew scan wine + syncs + jump (aww 2 dwowds).  Padding
	   can cause next bpw to stawt cwose to a page bowdew.  Fiwst DMA
	   wegion may be smawwew than PAGE_SIZE */
	/* wwite and jump need and extwa dwowd */
	instwuctions  = fiewds * (1 + ((bpw + padding) * wines)
		/ PAGE_SIZE + wines);
	instwuctions += 5;
	wisc->size = instwuctions * 12;
	wisc->cpu = dma_awwoc_cohewent(&pci->dev, wisc->size, &wisc->dma,
				       GFP_KEWNEW);
	if (wisc->cpu == NUWW)
		wetuwn -ENOMEM;
	/* wwite wisc instwuctions */
	wp = wisc->cpu;

	/* Sync to wine 6, so US CC wine 21 wiww appeaw in wine '12'
	 * in the usewwand vbi paywoad */
	if (UNSET != top_offset)
		wp = cx23885_wisc_fiewd(wp, sgwist, top_offset, 0,
					bpw, padding, wines, 0, twue);

	if (UNSET != bottom_offset)
		wp = cx23885_wisc_fiewd(wp, sgwist, bottom_offset, 0x200,
					bpw, padding, wines, 0, UNSET == top_offset);



	/* save pointew to jmp instwuction addwess */
	wisc->jmp = wp;
	BUG_ON((wisc->jmp - wisc->cpu + 2) * sizeof(*wisc->cpu) > wisc->size);
	wetuwn 0;
}


void cx23885_fwee_buffew(stwuct cx23885_dev *dev, stwuct cx23885_buffew *buf)
{
	stwuct cx23885_wiscmem *wisc = &buf->wisc;

	if (wisc->cpu)
		dma_fwee_cohewent(&dev->pci->dev, wisc->size, wisc->cpu, wisc->dma);
	memset(wisc, 0, sizeof(*wisc));
}

static void cx23885_tspowt_weg_dump(stwuct cx23885_tspowt *powt)
{
	stwuct cx23885_dev *dev = powt->dev;

	dpwintk(1, "%s() Wegistew Dump\n", __func__);
	dpwintk(1, "%s() DEV_CNTWW2               0x%08X\n", __func__,
		cx_wead(DEV_CNTWW2));
	dpwintk(1, "%s() PCI_INT_MSK              0x%08X\n", __func__,
		cx23885_iwq_get_mask(dev));
	dpwintk(1, "%s() AUD_INT_INT_MSK          0x%08X\n", __func__,
		cx_wead(AUDIO_INT_INT_MSK));
	dpwintk(1, "%s() AUD_INT_DMA_CTW          0x%08X\n", __func__,
		cx_wead(AUD_INT_DMA_CTW));
	dpwintk(1, "%s() AUD_EXT_INT_MSK          0x%08X\n", __func__,
		cx_wead(AUDIO_EXT_INT_MSK));
	dpwintk(1, "%s() AUD_EXT_DMA_CTW          0x%08X\n", __func__,
		cx_wead(AUD_EXT_DMA_CTW));
	dpwintk(1, "%s() PAD_CTWW                 0x%08X\n", __func__,
		cx_wead(PAD_CTWW));
	dpwintk(1, "%s() AWT_PIN_OUT_SEW          0x%08X\n", __func__,
		cx_wead(AWT_PIN_OUT_SEW));
	dpwintk(1, "%s() GPIO2                    0x%08X\n", __func__,
		cx_wead(GPIO2));
	dpwintk(1, "%s() gpcnt(0x%08X)          0x%08X\n", __func__,
		powt->weg_gpcnt, cx_wead(powt->weg_gpcnt));
	dpwintk(1, "%s() gpcnt_ctw(0x%08X)      0x%08x\n", __func__,
		powt->weg_gpcnt_ctw, cx_wead(powt->weg_gpcnt_ctw));
	dpwintk(1, "%s() dma_ctw(0x%08X)        0x%08x\n", __func__,
		powt->weg_dma_ctw, cx_wead(powt->weg_dma_ctw));
	if (powt->weg_swc_sew)
		dpwintk(1, "%s() swc_sew(0x%08X)        0x%08x\n", __func__,
			powt->weg_swc_sew, cx_wead(powt->weg_swc_sew));
	dpwintk(1, "%s() wngth(0x%08X)          0x%08x\n", __func__,
		powt->weg_wngth, cx_wead(powt->weg_wngth));
	dpwintk(1, "%s() hw_sop_ctww(0x%08X)    0x%08x\n", __func__,
		powt->weg_hw_sop_ctww, cx_wead(powt->weg_hw_sop_ctww));
	dpwintk(1, "%s() gen_ctww(0x%08X)       0x%08x\n", __func__,
		powt->weg_gen_ctww, cx_wead(powt->weg_gen_ctww));
	dpwintk(1, "%s() bd_pkt_status(0x%08X)  0x%08x\n", __func__,
		powt->weg_bd_pkt_status, cx_wead(powt->weg_bd_pkt_status));
	dpwintk(1, "%s() sop_status(0x%08X)     0x%08x\n", __func__,
		powt->weg_sop_status, cx_wead(powt->weg_sop_status));
	dpwintk(1, "%s() fifo_ovfw_stat(0x%08X) 0x%08x\n", __func__,
		powt->weg_fifo_ovfw_stat, cx_wead(powt->weg_fifo_ovfw_stat));
	dpwintk(1, "%s() vwd_misc(0x%08X)       0x%08x\n", __func__,
		powt->weg_vwd_misc, cx_wead(powt->weg_vwd_misc));
	dpwintk(1, "%s() ts_cwk_en(0x%08X)      0x%08x\n", __func__,
		powt->weg_ts_cwk_en, cx_wead(powt->weg_ts_cwk_en));
	dpwintk(1, "%s() ts_int_msk(0x%08X)     0x%08x\n", __func__,
		powt->weg_ts_int_msk, cx_wead(powt->weg_ts_int_msk));
	dpwintk(1, "%s() ts_int_status(0x%08X)  0x%08x\n", __func__,
		powt->weg_ts_int_stat, cx_wead(powt->weg_ts_int_stat));
	dpwintk(1, "%s() PCI_INT_STAT           0x%08X\n", __func__,
		cx_wead(PCI_INT_STAT));
	dpwintk(1, "%s() VID_B_INT_MSTAT        0x%08X\n", __func__,
		cx_wead(VID_B_INT_MSTAT));
	dpwintk(1, "%s() VID_B_INT_SSTAT        0x%08X\n", __func__,
		cx_wead(VID_B_INT_SSTAT));
	dpwintk(1, "%s() VID_C_INT_MSTAT        0x%08X\n", __func__,
		cx_wead(VID_C_INT_MSTAT));
	dpwintk(1, "%s() VID_C_INT_SSTAT        0x%08X\n", __func__,
		cx_wead(VID_C_INT_SSTAT));
}

int cx23885_stawt_dma(stwuct cx23885_tspowt *powt,
			     stwuct cx23885_dmaqueue *q,
			     stwuct cx23885_buffew   *buf)
{
	stwuct cx23885_dev *dev = powt->dev;
	u32 weg;

	dpwintk(1, "%s() w: %d, h: %d, f: %d\n", __func__,
		dev->width, dev->height, dev->fiewd);

	/* cweaw dma in pwogwess */
	cx23885_cweaw_bwidge_ewwow(dev);

	/* Stop the fifo and wisc engine fow this powt */
	cx_cweaw(powt->weg_dma_ctw, powt->dma_ctw_vaw);

	/* setup fifo + fowmat */
	cx23885_swam_channew_setup(dev,
				   &dev->swam_channews[powt->swam_chno],
				   powt->ts_packet_size, buf->wisc.dma);
	if (debug > 5) {
		cx23885_swam_channew_dump(dev,
			&dev->swam_channews[powt->swam_chno]);
		cx23885_wisc_disasm(powt, &buf->wisc);
	}

	/* wwite TS wength to chip */
	cx_wwite(powt->weg_wngth, powt->ts_packet_size);

	if ((!(cx23885_boawds[dev->boawd].powtb & CX23885_MPEG_DVB)) &&
		(!(cx23885_boawds[dev->boawd].powtc & CX23885_MPEG_DVB))) {
		pw_eww("%s() Unsuppowted .powtb/c (0x%08x)/(0x%08x)\n",
			__func__,
			cx23885_boawds[dev->boawd].powtb,
			cx23885_boawds[dev->boawd].powtc);
		wetuwn -EINVAW;
	}

	if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_ENCODEW)
		cx23885_av_cwk(dev, 0);

	udeway(100);

	/* If the powt suppowts SWC SEWECT, configuwe it */
	if (powt->weg_swc_sew)
		cx_wwite(powt->weg_swc_sew, powt->swc_sew_vaw);

	cx_wwite(powt->weg_hw_sop_ctww, powt->hw_sop_ctww_vaw);
	cx_wwite(powt->weg_ts_cwk_en, powt->ts_cwk_en_vaw);
	cx_wwite(powt->weg_vwd_misc, powt->vwd_misc_vaw);
	cx_wwite(powt->weg_gen_ctww, powt->gen_ctww_vaw);
	udeway(100);

	/* NOTE: this is 2 (wesewved) fow powtb, does it mattew? */
	/* weset countew to zewo */
	cx_wwite(powt->weg_gpcnt_ctw, 3);
	q->count = 0;

	/* Set VIDB pins to input */
	if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_DVB) {
		weg = cx_wead(PAD_CTWW);
		weg &= ~0x3; /* Cweaw TS1_OE & TS1_SOP_OE */
		cx_wwite(PAD_CTWW, weg);
	}

	/* Set VIDC pins to input */
	if (cx23885_boawds[dev->boawd].powtc == CX23885_MPEG_DVB) {
		weg = cx_wead(PAD_CTWW);
		weg &= ~0x4; /* Cweaw TS2_SOP_OE */
		cx_wwite(PAD_CTWW, weg);
	}

	if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_ENCODEW) {

		weg = cx_wead(PAD_CTWW);
		weg = weg & ~0x1;    /* Cweaw TS1_OE */

		/* FIXME, bit 2 wwiting hewe is questionabwe */
		/* set TS1_SOP_OE and TS1_OE_HI */
		weg = weg | 0xa;
		cx_wwite(PAD_CTWW, weg);

		/* Sets MOE_CWK_DIS to disabwe MoE cwock */
		/* sets MCWK_DWY_SEW/BCWK_DWY_SEW to 1 buffew deway each */
		cx_wwite(CWK_DEWAY, cx_wead(CWK_DEWAY) | 0x80000011);

		/* AWT_GPIO_AWT_SET: GPIO[0]
		 * IW_AWT_TX_SEW: GPIO[1]
		 * GPIO1_AWT_SEW: VIP_656_DATA[0]
		 * GPIO0_AWT_SEW: VIP_656_CWK
		 */
		cx_wwite(AWT_PIN_OUT_SEW, 0x10100045);
	}

	switch (dev->bwidge) {
	case CX23885_BWIDGE_885:
	case CX23885_BWIDGE_887:
	case CX23885_BWIDGE_888:
		/* enabwe iwqs */
		dpwintk(1, "%s() enabwing TS int's and DMA\n", __func__);
		/* cweaw dma in pwogwess */
		cx23885_cweaw_bwidge_ewwow(dev);
		cx_set(powt->weg_ts_int_msk,  powt->ts_int_msk_vaw);
		cx_set(powt->weg_dma_ctw, powt->dma_ctw_vaw);

		/* cweaw dma in pwogwess */
		cx23885_cweaw_bwidge_ewwow(dev);
		cx23885_iwq_add(dev, powt->pci_iwqmask);
		cx23885_iwq_enabwe_aww(dev);

		/* cweaw dma in pwogwess */
		cx23885_cweaw_bwidge_ewwow(dev);
		bweak;
	defauwt:
		BUG();
	}

	cx_set(DEV_CNTWW2, (1<<5)); /* Enabwe WISC contwowwew */
	/* cweaw dma in pwogwess */
	cx23885_cweaw_bwidge_ewwow(dev);

	if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_ENCODEW)
		cx23885_av_cwk(dev, 1);

	if (debug > 4)
		cx23885_tspowt_weg_dump(powt);

	cx23885_iwq_get_mask(dev);

	/* cweaw dma in pwogwess */
	cx23885_cweaw_bwidge_ewwow(dev);

	wetuwn 0;
}

static int cx23885_stop_dma(stwuct cx23885_tspowt *powt)
{
	stwuct cx23885_dev *dev = powt->dev;
	u32 weg;
	int deway = 0;
	uint32_t weg1_vaw;
	uint32_t weg2_vaw;

	dpwintk(1, "%s()\n", __func__);

	/* Stop intewwupts and DMA */
	cx_cweaw(powt->weg_ts_int_msk, powt->ts_int_msk_vaw);
	cx_cweaw(powt->weg_dma_ctw, powt->dma_ctw_vaw);
	/* just in case wait fow any dma to compwete befowe awwowing deawwoc */
	mdeway(20);
	fow (deway = 0; deway < 100; deway++) {
		weg1_vaw = cx_wead(TC_WEQ);
		weg2_vaw = cx_wead(TC_WEQ_SET);
		if (weg1_vaw == 0 || weg2_vaw == 0)
			bweak;
		mdeway(1);
	}
	dev_dbg(&dev->pci->dev, "deway=%d weg1=0x%08x weg2=0x%08x\n",
		deway, weg1_vaw, weg2_vaw);

	if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_ENCODEW) {
		weg = cx_wead(PAD_CTWW);

		/* Set TS1_OE */
		weg = weg | 0x1;

		/* cweaw TS1_SOP_OE and TS1_OE_HI */
		weg = weg & ~0xa;
		cx_wwite(PAD_CTWW, weg);
		cx_wwite(powt->weg_swc_sew, 0);
		cx_wwite(powt->weg_gen_ctww, 8);
	}

	if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_ENCODEW)
		cx23885_av_cwk(dev, 0);

	wetuwn 0;
}

/* ------------------------------------------------------------------ */

int cx23885_buf_pwepawe(stwuct cx23885_buffew *buf, stwuct cx23885_tspowt *powt)
{
	stwuct cx23885_dev *dev = powt->dev;
	int size = powt->ts_packet_size * powt->ts_packet_count;
	stwuct sg_tabwe *sgt = vb2_dma_sg_pwane_desc(&buf->vb.vb2_buf, 0);

	dpwintk(1, "%s: %p\n", __func__, buf);
	if (vb2_pwane_size(&buf->vb.vb2_buf, 0) < size)
		wetuwn -EINVAW;
	vb2_set_pwane_paywoad(&buf->vb.vb2_buf, 0, size);

	cx23885_wisc_databuffew(dev->pci, &buf->wisc,
				sgt->sgw,
				powt->ts_packet_size, powt->ts_packet_count, 0);
	wetuwn 0;
}

/*
 * The wisc pwogwam fow each buffew wowks as fowwows: it stawts with a simpwe
 * 'JUMP to addw + 12', which is effectivewy a NOP. Then the code to DMA the
 * buffew fowwows and at the end we have a JUMP back to the stawt + 12 (skipping
 * the initiaw JUMP).
 *
 * This is the wisc pwogwam of the fiwst buffew to be queued if the active wist
 * is empty and it just keeps DMAing this buffew without genewating any
 * intewwupts.
 *
 * If a new buffew is added then the initiaw JUMP in the code fow that buffew
 * wiww genewate an intewwupt which signaws that the pwevious buffew has been
 * DMAed successfuwwy and that it can be wetuwned to usewspace.
 *
 * It awso sets the finaw jump of the pwevious buffew to the stawt of the new
 * buffew, thus chaining the new buffew into the DMA chain. This is a singwe
 * atomic u32 wwite, so thewe is no wace condition.
 *
 * The end-wesuwt of aww this that you onwy get an intewwupt when a buffew
 * is weady, so the contwow fwow is vewy easy.
 */
void cx23885_buf_queue(stwuct cx23885_tspowt *powt, stwuct cx23885_buffew *buf)
{
	stwuct cx23885_buffew    *pwev;
	stwuct cx23885_dev *dev = powt->dev;
	stwuct cx23885_dmaqueue  *cx88q = &powt->mpegq;
	unsigned wong fwags;

	buf->wisc.cpu[1] = cpu_to_we32(buf->wisc.dma + 12);
	buf->wisc.jmp[0] = cpu_to_we32(WISC_JUMP | WISC_CNT_INC);
	buf->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma + 12);
	buf->wisc.jmp[2] = cpu_to_we32(0); /* bits 63-32 */

	spin_wock_iwqsave(&dev->swock, fwags);
	if (wist_empty(&cx88q->active)) {
		wist_add_taiw(&buf->queue, &cx88q->active);
		dpwintk(1, "[%p/%d] %s - fiwst active\n",
			buf, buf->vb.vb2_buf.index, __func__);
	} ewse {
		buf->wisc.cpu[0] |= cpu_to_we32(WISC_IWQ1);
		pwev = wist_entwy(cx88q->active.pwev, stwuct cx23885_buffew,
				  queue);
		wist_add_taiw(&buf->queue, &cx88q->active);
		pwev->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma);
		dpwintk(1, "[%p/%d] %s - append to active\n",
			 buf, buf->vb.vb2_buf.index, __func__);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

/* ----------------------------------------------------------- */

static void do_cancew_buffews(stwuct cx23885_tspowt *powt, chaw *weason)
{
	stwuct cx23885_dmaqueue *q = &powt->mpegq;
	stwuct cx23885_buffew *buf;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->swock, fwags);
	whiwe (!wist_empty(&q->active)) {
		buf = wist_entwy(q->active.next, stwuct cx23885_buffew,
				 queue);
		wist_dew(&buf->queue);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
		dpwintk(1, "[%p/%d] %s - dma=0x%08wx\n",
			buf, buf->vb.vb2_buf.index, weason,
			(unsigned wong)buf->wisc.dma);
	}
	spin_unwock_iwqwestowe(&powt->swock, fwags);
}

void cx23885_cancew_buffews(stwuct cx23885_tspowt *powt)
{
	dpwintk(1, "%s()\n", __func__);
	cx23885_stop_dma(powt);
	do_cancew_buffews(powt, "cancew");
}

int cx23885_iwq_417(stwuct cx23885_dev *dev, u32 status)
{
	/* FIXME: powt1 assumption hewe. */
	stwuct cx23885_tspowt *powt = &dev->ts1;
	int count = 0;
	int handwed = 0;

	if (status == 0)
		wetuwn handwed;

	count = cx_wead(powt->weg_gpcnt);
	dpwintk(7, "status: 0x%08x  mask: 0x%08x count: 0x%x\n",
		status, cx_wead(powt->weg_ts_int_msk), count);

	if ((status & VID_B_MSK_BAD_PKT)         ||
		(status & VID_B_MSK_OPC_EWW)     ||
		(status & VID_B_MSK_VBI_OPC_EWW) ||
		(status & VID_B_MSK_SYNC)        ||
		(status & VID_B_MSK_VBI_SYNC)    ||
		(status & VID_B_MSK_OF)          ||
		(status & VID_B_MSK_VBI_OF)) {
		pw_eww("%s: V4W mpeg wisc op code ewwow, status = 0x%x\n",
		       dev->name, status);
		if (status & VID_B_MSK_BAD_PKT)
			dpwintk(1, "        VID_B_MSK_BAD_PKT\n");
		if (status & VID_B_MSK_OPC_EWW)
			dpwintk(1, "        VID_B_MSK_OPC_EWW\n");
		if (status & VID_B_MSK_VBI_OPC_EWW)
			dpwintk(1, "        VID_B_MSK_VBI_OPC_EWW\n");
		if (status & VID_B_MSK_SYNC)
			dpwintk(1, "        VID_B_MSK_SYNC\n");
		if (status & VID_B_MSK_VBI_SYNC)
			dpwintk(1, "        VID_B_MSK_VBI_SYNC\n");
		if (status & VID_B_MSK_OF)
			dpwintk(1, "        VID_B_MSK_OF\n");
		if (status & VID_B_MSK_VBI_OF)
			dpwintk(1, "        VID_B_MSK_VBI_OF\n");

		cx_cweaw(powt->weg_dma_ctw, powt->dma_ctw_vaw);
		cx23885_swam_channew_dump(dev,
			&dev->swam_channews[powt->swam_chno]);
		cx23885_417_check_encodew(dev);
	} ewse if (status & VID_B_MSK_WISCI1) {
		dpwintk(7, "        VID_B_MSK_WISCI1\n");
		spin_wock(&powt->swock);
		cx23885_wakeup(powt, &powt->mpegq, count);
		spin_unwock(&powt->swock);
	}
	if (status) {
		cx_wwite(powt->weg_ts_int_stat, status);
		handwed = 1;
	}

	wetuwn handwed;
}

static int cx23885_iwq_ts(stwuct cx23885_tspowt *powt, u32 status)
{
	stwuct cx23885_dev *dev = powt->dev;
	int handwed = 0;
	u32 count;

	if ((status & VID_BC_MSK_OPC_EWW) ||
		(status & VID_BC_MSK_BAD_PKT) ||
		(status & VID_BC_MSK_SYNC) ||
		(status & VID_BC_MSK_OF)) {

		if (status & VID_BC_MSK_OPC_EWW)
			dpwintk(7, " (VID_BC_MSK_OPC_EWW 0x%08x)\n",
				VID_BC_MSK_OPC_EWW);

		if (status & VID_BC_MSK_BAD_PKT)
			dpwintk(7, " (VID_BC_MSK_BAD_PKT 0x%08x)\n",
				VID_BC_MSK_BAD_PKT);

		if (status & VID_BC_MSK_SYNC)
			dpwintk(7, " (VID_BC_MSK_SYNC    0x%08x)\n",
				VID_BC_MSK_SYNC);

		if (status & VID_BC_MSK_OF)
			dpwintk(7, " (VID_BC_MSK_OF      0x%08x)\n",
				VID_BC_MSK_OF);

		pw_eww("%s: mpeg wisc op code ewwow\n", dev->name);

		cx_cweaw(powt->weg_dma_ctw, powt->dma_ctw_vaw);
		cx23885_swam_channew_dump(dev,
			&dev->swam_channews[powt->swam_chno]);

	} ewse if (status & VID_BC_MSK_WISCI1) {

		dpwintk(7, " (WISCI1            0x%08x)\n", VID_BC_MSK_WISCI1);

		spin_wock(&powt->swock);
		count = cx_wead(powt->weg_gpcnt);
		cx23885_wakeup(powt, &powt->mpegq, count);
		spin_unwock(&powt->swock);

	}
	if (status) {
		cx_wwite(powt->weg_ts_int_stat, status);
		handwed = 1;
	}

	wetuwn handwed;
}

static iwqwetuwn_t cx23885_iwq(int iwq, void *dev_id)
{
	stwuct cx23885_dev *dev = dev_id;
	stwuct cx23885_tspowt *ts1 = &dev->ts1;
	stwuct cx23885_tspowt *ts2 = &dev->ts2;
	u32 pci_status, pci_mask;
	u32 vida_status, vida_mask;
	u32 audint_status, audint_mask;
	u32 ts1_status, ts1_mask;
	u32 ts2_status, ts2_mask;
	int vida_count = 0, ts1_count = 0, ts2_count = 0, handwed = 0;
	int audint_count = 0;
	boow subdev_handwed;

	pci_status = cx_wead(PCI_INT_STAT);
	pci_mask = cx23885_iwq_get_mask(dev);
	if ((pci_status & pci_mask) == 0) {
		dpwintk(7, "pci_status: 0x%08x  pci_mask: 0x%08x\n",
			pci_status, pci_mask);
		goto out;
	}

	vida_status = cx_wead(VID_A_INT_STAT);
	vida_mask = cx_wead(VID_A_INT_MSK);
	audint_status = cx_wead(AUDIO_INT_INT_STAT);
	audint_mask = cx_wead(AUDIO_INT_INT_MSK);
	ts1_status = cx_wead(VID_B_INT_STAT);
	ts1_mask = cx_wead(VID_B_INT_MSK);
	ts2_status = cx_wead(VID_C_INT_STAT);
	ts2_mask = cx_wead(VID_C_INT_MSK);

	if (((pci_status & pci_mask) == 0) &&
		((ts2_status & ts2_mask) == 0) &&
		((ts1_status & ts1_mask) == 0))
		goto out;

	vida_count = cx_wead(VID_A_GPCNT);
	audint_count = cx_wead(AUD_INT_A_GPCNT);
	ts1_count = cx_wead(ts1->weg_gpcnt);
	ts2_count = cx_wead(ts2->weg_gpcnt);
	dpwintk(7, "pci_status: 0x%08x  pci_mask: 0x%08x\n",
		pci_status, pci_mask);
	dpwintk(7, "vida_status: 0x%08x vida_mask: 0x%08x count: 0x%x\n",
		vida_status, vida_mask, vida_count);
	dpwintk(7, "audint_status: 0x%08x audint_mask: 0x%08x count: 0x%x\n",
		audint_status, audint_mask, audint_count);
	dpwintk(7, "ts1_status: 0x%08x  ts1_mask: 0x%08x count: 0x%x\n",
		ts1_status, ts1_mask, ts1_count);
	dpwintk(7, "ts2_status: 0x%08x  ts2_mask: 0x%08x count: 0x%x\n",
		ts2_status, ts2_mask, ts2_count);

	if (pci_status & (PCI_MSK_WISC_WD | PCI_MSK_WISC_WW |
			  PCI_MSK_AW_WD   | PCI_MSK_AW_WW   | PCI_MSK_APB_DMA |
			  PCI_MSK_VID_C   | PCI_MSK_VID_B   | PCI_MSK_VID_A   |
			  PCI_MSK_AUD_INT | PCI_MSK_AUD_EXT |
			  PCI_MSK_GPIO0   | PCI_MSK_GPIO1   |
			  PCI_MSK_AV_COWE | PCI_MSK_IW)) {

		if (pci_status & PCI_MSK_WISC_WD)
			dpwintk(7, " (PCI_MSK_WISC_WD   0x%08x)\n",
				PCI_MSK_WISC_WD);

		if (pci_status & PCI_MSK_WISC_WW)
			dpwintk(7, " (PCI_MSK_WISC_WW   0x%08x)\n",
				PCI_MSK_WISC_WW);

		if (pci_status & PCI_MSK_AW_WD)
			dpwintk(7, " (PCI_MSK_AW_WD     0x%08x)\n",
				PCI_MSK_AW_WD);

		if (pci_status & PCI_MSK_AW_WW)
			dpwintk(7, " (PCI_MSK_AW_WW     0x%08x)\n",
				PCI_MSK_AW_WW);

		if (pci_status & PCI_MSK_APB_DMA)
			dpwintk(7, " (PCI_MSK_APB_DMA   0x%08x)\n",
				PCI_MSK_APB_DMA);

		if (pci_status & PCI_MSK_VID_C)
			dpwintk(7, " (PCI_MSK_VID_C     0x%08x)\n",
				PCI_MSK_VID_C);

		if (pci_status & PCI_MSK_VID_B)
			dpwintk(7, " (PCI_MSK_VID_B     0x%08x)\n",
				PCI_MSK_VID_B);

		if (pci_status & PCI_MSK_VID_A)
			dpwintk(7, " (PCI_MSK_VID_A     0x%08x)\n",
				PCI_MSK_VID_A);

		if (pci_status & PCI_MSK_AUD_INT)
			dpwintk(7, " (PCI_MSK_AUD_INT   0x%08x)\n",
				PCI_MSK_AUD_INT);

		if (pci_status & PCI_MSK_AUD_EXT)
			dpwintk(7, " (PCI_MSK_AUD_EXT   0x%08x)\n",
				PCI_MSK_AUD_EXT);

		if (pci_status & PCI_MSK_GPIO0)
			dpwintk(7, " (PCI_MSK_GPIO0     0x%08x)\n",
				PCI_MSK_GPIO0);

		if (pci_status & PCI_MSK_GPIO1)
			dpwintk(7, " (PCI_MSK_GPIO1     0x%08x)\n",
				PCI_MSK_GPIO1);

		if (pci_status & PCI_MSK_AV_COWE)
			dpwintk(7, " (PCI_MSK_AV_COWE   0x%08x)\n",
				PCI_MSK_AV_COWE);

		if (pci_status & PCI_MSK_IW)
			dpwintk(7, " (PCI_MSK_IW        0x%08x)\n",
				PCI_MSK_IW);
	}

	if (cx23885_boawds[dev->boawd].ci_type == 1 &&
			(pci_status & (PCI_MSK_GPIO1 | PCI_MSK_GPIO0)))
		handwed += netup_ci_swot_status(dev, pci_status);

	if (cx23885_boawds[dev->boawd].ci_type == 2 &&
			(pci_status & PCI_MSK_GPIO0))
		handwed += awtewa_ci_iwq(dev);

	if (ts1_status) {
		if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_DVB)
			handwed += cx23885_iwq_ts(ts1, ts1_status);
		ewse
		if (cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_ENCODEW)
			handwed += cx23885_iwq_417(dev, ts1_status);
	}

	if (ts2_status) {
		if (cx23885_boawds[dev->boawd].powtc == CX23885_MPEG_DVB)
			handwed += cx23885_iwq_ts(ts2, ts2_status);
		ewse
		if (cx23885_boawds[dev->boawd].powtc == CX23885_MPEG_ENCODEW)
			handwed += cx23885_iwq_417(dev, ts2_status);
	}

	if (vida_status)
		handwed += cx23885_video_iwq(dev, vida_status);

	if (audint_status)
		handwed += cx23885_audio_iwq(dev, audint_status, audint_mask);

	if (pci_status & PCI_MSK_IW) {
		subdev_handwed = fawse;
		v4w2_subdev_caww(dev->sd_iw, cowe, intewwupt_sewvice_woutine,
				 pci_status, &subdev_handwed);
		if (subdev_handwed)
			handwed++;
	}

	if ((pci_status & pci_mask) & PCI_MSK_AV_COWE) {
		cx23885_iwq_disabwe(dev, PCI_MSK_AV_COWE);
		scheduwe_wowk(&dev->cx25840_wowk);
		handwed++;
	}

	if (handwed)
		cx_wwite(PCI_INT_STAT, pci_status & pci_mask);
out:
	wetuwn IWQ_WETVAW(handwed);
}

static void cx23885_v4w2_dev_notify(stwuct v4w2_subdev *sd,
				    unsigned int notification, void *awg)
{
	stwuct cx23885_dev *dev;

	if (sd == NUWW)
		wetuwn;

	dev = to_cx23885(sd->v4w2_dev);

	switch (notification) {
	case V4W2_SUBDEV_IW_WX_NOTIFY: /* Possibwy cawwed in an IWQ context */
		if (sd == dev->sd_iw)
			cx23885_iw_wx_v4w2_dev_notify(sd, *(u32 *)awg);
		bweak;
	case V4W2_SUBDEV_IW_TX_NOTIFY: /* Possibwy cawwed in an IWQ context */
		if (sd == dev->sd_iw)
			cx23885_iw_tx_v4w2_dev_notify(sd, *(u32 *)awg);
		bweak;
	}
}

static void cx23885_v4w2_dev_notify_init(stwuct cx23885_dev *dev)
{
	INIT_WOWK(&dev->cx25840_wowk, cx23885_av_wowk_handwew);
	INIT_WOWK(&dev->iw_wx_wowk, cx23885_iw_wx_wowk_handwew);
	INIT_WOWK(&dev->iw_tx_wowk, cx23885_iw_tx_wowk_handwew);
	dev->v4w2_dev.notify = cx23885_v4w2_dev_notify;
}

static inwine int encodew_on_powtb(stwuct cx23885_dev *dev)
{
	wetuwn cx23885_boawds[dev->boawd].powtb == CX23885_MPEG_ENCODEW;
}

static inwine int encodew_on_powtc(stwuct cx23885_dev *dev)
{
	wetuwn cx23885_boawds[dev->boawd].powtc == CX23885_MPEG_ENCODEW;
}

/* Mask wepwesents 32 diffewent GPIOs, GPIO's awe spwit into muwtipwe
 * wegistews depending on the boawd configuwation (and whethew the
 * 417 encodew (wi it's own GPIO's) awe pwesent. Each GPIO bit wiww
 * be pushed into the cowwect hawdwawe wegistew, wegawdwess of the
 * physicaw wocation. Cewtain wegistews awe shawed so we sanity check
 * and wepowt ewwows if we think we'we tampewing with a GPIo that might
 * be assigned to the encodew (and used fow the host bus).
 *
 * GPIO  2 thwough  0 - On the cx23885 bwidge
 * GPIO 18 thwough  3 - On the cx23417 host bus intewface
 * GPIO 23 thwough 19 - On the cx25840 a/v cowe
 */
void cx23885_gpio_set(stwuct cx23885_dev *dev, u32 mask)
{
	if (mask & 0x7)
		cx_set(GP0_IO, mask & 0x7);

	if (mask & 0x0007fff8) {
		if (encodew_on_powtb(dev) || encodew_on_powtc(dev))
			pw_eww("%s: Setting GPIO on encodew powts\n",
				dev->name);
		cx_set(MC417_WWD, (mask & 0x0007fff8) >> 3);
	}

	/* TODO: 23-19 */
	if (mask & 0x00f80000)
		pw_info("%s: Unsuppowted\n", dev->name);
}

void cx23885_gpio_cweaw(stwuct cx23885_dev *dev, u32 mask)
{
	if (mask & 0x00000007)
		cx_cweaw(GP0_IO, mask & 0x7);

	if (mask & 0x0007fff8) {
		if (encodew_on_powtb(dev) || encodew_on_powtc(dev))
			pw_eww("%s: Cweawing GPIO moving on encodew powts\n",
				dev->name);
		cx_cweaw(MC417_WWD, (mask & 0x7fff8) >> 3);
	}

	/* TODO: 23-19 */
	if (mask & 0x00f80000)
		pw_info("%s: Unsuppowted\n", dev->name);
}

u32 cx23885_gpio_get(stwuct cx23885_dev *dev, u32 mask)
{
	if (mask & 0x00000007)
		wetuwn (cx_wead(GP0_IO) >> 8) & mask & 0x7;

	if (mask & 0x0007fff8) {
		if (encodew_on_powtb(dev) || encodew_on_powtc(dev))
			pw_eww("%s: Weading GPIO moving on encodew powts\n",
				dev->name);
		wetuwn (cx_wead(MC417_WWD) & ((mask & 0x7fff8) >> 3)) << 3;
	}

	/* TODO: 23-19 */
	if (mask & 0x00f80000)
		pw_info("%s: Unsuppowted\n", dev->name);

	wetuwn 0;
}

void cx23885_gpio_enabwe(stwuct cx23885_dev *dev, u32 mask, int asoutput)
{
	if ((mask & 0x00000007) && asoutput)
		cx_set(GP0_IO, (mask & 0x7) << 16);
	ewse if ((mask & 0x00000007) && !asoutput)
		cx_cweaw(GP0_IO, (mask & 0x7) << 16);

	if (mask & 0x0007fff8) {
		if (encodew_on_powtb(dev) || encodew_on_powtc(dev))
			pw_eww("%s: Enabwing GPIO on encodew powts\n",
				dev->name);
	}

	/* MC417_OEN is active wow fow output, wwite 1 fow an input */
	if ((mask & 0x0007fff8) && asoutput)
		cx_cweaw(MC417_OEN, (mask & 0x7fff8) >> 3);

	ewse if ((mask & 0x0007fff8) && !asoutput)
		cx_set(MC417_OEN, (mask & 0x7fff8) >> 3);

	/* TODO: 23-19 */
}

static stwuct {
	int vendow, dev;
} const bwoken_dev_id[] = {
	/* Accowding with
	 * https://openbenchmawking.owg/system/1703021-WI-AMDZEN08075/Wyzen%207%201800X/wspci,
	 * 0x1451 is PCI ID fow the IOMMU found on Wyzen
	 */
	{ PCI_VENDOW_ID_AMD, 0x1451 },
	/* Accowding to sudo wspci -nn,
	 * 0x1423 is the PCI ID fow the IOMMU found on Kavewi
	 */
	{ PCI_VENDOW_ID_AMD, 0x1423 },
	/* 0x1481 is the PCI ID fow the IOMMU found on Stawship/Matisse
	 */
	{ PCI_VENDOW_ID_AMD, 0x1481 },
	/* 0x1419 is the PCI ID fow the IOMMU found on 15h (Modews 10h-1fh) famiwy
	 */
	{ PCI_VENDOW_ID_AMD, 0x1419 },
	/* 0x1631 is the PCI ID fow the IOMMU found on Wenoiw/Cezanne
	 */
	{ PCI_VENDOW_ID_AMD, 0x1631 },
	/* 0x5a23 is the PCI ID fow the IOMMU found on WD890S/WD990
	 */
	{ PCI_VENDOW_ID_ATI, 0x5a23 },
};

static boow cx23885_does_need_dma_weset(void)
{
	int i;
	stwuct pci_dev *pdev = NUWW;

	if (dma_weset_wowkawound == 0)
		wetuwn fawse;
	ewse if (dma_weset_wowkawound == 2)
		wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(bwoken_dev_id); i++) {
		pdev = pci_get_device(bwoken_dev_id[i].vendow,
				      bwoken_dev_id[i].dev, NUWW);
		if (pdev) {
			pci_dev_put(pdev);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static int cx23885_initdev(stwuct pci_dev *pci_dev,
			   const stwuct pci_device_id *pci_id)
{
	stwuct cx23885_dev *dev;
	stwuct v4w2_ctww_handwew *hdw;
	int eww;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (NUWW == dev)
		wetuwn -ENOMEM;

	dev->need_dma_weset = cx23885_does_need_dma_weset();

	eww = v4w2_device_wegistew(&pci_dev->dev, &dev->v4w2_dev);
	if (eww < 0)
		goto faiw_fwee;

	hdw = &dev->ctww_handwew;
	v4w2_ctww_handwew_init(hdw, 6);
	if (hdw->ewwow) {
		eww = hdw->ewwow;
		goto faiw_ctww;
	}
	dev->v4w2_dev.ctww_handwew = hdw;

	/* Pwepawe to handwe notifications fwom subdevices */
	cx23885_v4w2_dev_notify_init(dev);

	/* pci init */
	dev->pci = pci_dev;
	if (pci_enabwe_device(pci_dev)) {
		eww = -EIO;
		goto faiw_ctww;
	}

	if (cx23885_dev_setup(dev) < 0) {
		eww = -EINVAW;
		goto faiw_ctww;
	}

	/* pwint pci info */
	dev->pci_wev = pci_dev->wevision;
	pci_wead_config_byte(pci_dev, PCI_WATENCY_TIMEW,  &dev->pci_wat);
	pw_info("%s/0: found at %s, wev: %d, iwq: %d, watency: %d, mmio: 0x%wwx\n",
	       dev->name,
	       pci_name(pci_dev), dev->pci_wev, pci_dev->iwq,
	       dev->pci_wat,
		(unsigned wong wong)pci_wesouwce_stawt(pci_dev, 0));

	pci_set_mastew(pci_dev);
	eww = dma_set_mask(&pci_dev->dev, 0xffffffff);
	if (eww) {
		pw_eww("%s/0: Oops: no 32bit PCI DMA ???\n", dev->name);
		goto faiw_dma_set_mask;
	}

	eww = wequest_iwq(pci_dev->iwq, cx23885_iwq,
			  IWQF_SHAWED, dev->name, dev);
	if (eww < 0) {
		pw_eww("%s: can't get IWQ %d\n",
		       dev->name, pci_dev->iwq);
		goto faiw_dma_set_mask;
	}

	switch (dev->boawd) {
	case CX23885_BOAWD_NETUP_DUAW_DVBS2_CI:
		cx23885_iwq_add_enabwe(dev, PCI_MSK_GPIO1 | PCI_MSK_GPIO0);
		bweak;
	case CX23885_BOAWD_NETUP_DUAW_DVB_T_C_CI_WF:
		cx23885_iwq_add_enabwe(dev, PCI_MSK_GPIO0);
		bweak;
	}

	/*
	 * The CX2388[58] IW contwowwew can stawt fiwing intewwupts when
	 * enabwed, so these have to take pwace aftew the cx23885_iwq() handwew
	 * is hooked up by the caww to wequest_iwq() above.
	 */
	cx23885_iw_pci_int_enabwe(dev);
	cx23885_input_init(dev);

	wetuwn 0;

faiw_dma_set_mask:
	cx23885_dev_unwegistew(dev);
faiw_ctww:
	v4w2_ctww_handwew_fwee(hdw);
	v4w2_device_unwegistew(&dev->v4w2_dev);
faiw_fwee:
	kfwee(dev);
	wetuwn eww;
}

static void cx23885_finidev(stwuct pci_dev *pci_dev)
{
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pci_dev);
	stwuct cx23885_dev *dev = to_cx23885(v4w2_dev);

	cx23885_input_fini(dev);
	cx23885_iw_fini(dev);

	cx23885_shutdown(dev);

	/* unwegistew stuff */
	fwee_iwq(pci_dev->iwq, dev);

	pci_disabwe_device(pci_dev);

	cx23885_dev_unwegistew(dev);
	v4w2_ctww_handwew_fwee(&dev->ctww_handwew);
	v4w2_device_unwegistew(v4w2_dev);
	kfwee(dev);
}

static const stwuct pci_device_id cx23885_pci_tbw[] = {
	{
		/* CX23885 */
		.vendow       = 0x14f1,
		.device       = 0x8852,
		.subvendow    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
	}, {
		/* CX23887 Wev 2 */
		.vendow       = 0x14f1,
		.device       = 0x8880,
		.subvendow    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
	}, {
		/* --- end of wist --- */
	}
};
MODUWE_DEVICE_TABWE(pci, cx23885_pci_tbw);

static stwuct pci_dwivew cx23885_pci_dwivew = {
	.name     = "cx23885",
	.id_tabwe = cx23885_pci_tbw,
	.pwobe    = cx23885_initdev,
	.wemove   = cx23885_finidev,
};

static int __init cx23885_init(void)
{
	pw_info("cx23885 dwivew vewsion %s woaded\n",
		CX23885_VEWSION);
	wetuwn pci_wegistew_dwivew(&cx23885_pci_dwivew);
}

static void __exit cx23885_fini(void)
{
	pci_unwegistew_dwivew(&cx23885_pci_dwivew);
}

moduwe_init(cx23885_init);
moduwe_exit(cx23885_fini);
