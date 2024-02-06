// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * device dwivew fow Conexant 2388x based TV cawds
 * dwivew cowe
 *
 * (c) 2003 Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]
 *
 * (c) 2005-2006 Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 *     - Muwtitunew suppowt
 *     - video_ioctw2 convewsion
 *     - PAW/M fixes
 */

#incwude "cx88.h"

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/kmod.h>
#incwude <winux/sound.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/videodev2.h>
#incwude <winux/mutex.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ioctw.h>

MODUWE_DESCWIPTION("v4w2 dwivew moduwe fow cx2388x based TV cawds");
MODUWE_AUTHOW("Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]");
MODUWE_WICENSE("GPW v2");

/* ------------------------------------------------------------------ */

unsigned int cx88_cowe_debug;
moduwe_pawam_named(cowe_debug, cx88_cowe_debug, int, 0644);
MODUWE_PAWM_DESC(cowe_debug, "enabwe debug messages [cowe]");

static unsigned int nicam;
moduwe_pawam(nicam, int, 0644);
MODUWE_PAWM_DESC(nicam, "tv audio is nicam");

static unsigned int nocomb;
moduwe_pawam(nocomb, int, 0644);
MODUWE_PAWM_DESC(nocomb, "disabwe comb fiwtew");

#define dpwintk0(fmt, awg...)				\
	pwintk(KEWN_DEBUG pw_fmt("%s: cowe:" fmt),	\
		__func__, ##awg)			\

#define dpwintk(wevew, fmt, awg...)	do {			\
	if (cx88_cowe_debug >= wevew)				\
		pwintk(KEWN_DEBUG pw_fmt("%s: cowe:" fmt),	\
		       __func__, ##awg);			\
} whiwe (0)

static unsigned int cx88_devcount;
static WIST_HEAD(cx88_devwist);
static DEFINE_MUTEX(devwist);

#define NO_SYNC_WINE (-1U)

/*
 * @wpi: wines pew IWQ, ow 0 to not genewate iwqs. Note: IWQ to be
 * genewated _aftew_ wpi wines awe twansfewwed.
 */
static __we32 *cx88_wisc_fiewd(__we32 *wp, stwuct scattewwist *sgwist,
			       unsigned int offset, u32 sync_wine,
			       unsigned int bpw, unsigned int padding,
			       unsigned int wines, unsigned int wpi, boow jump)
{
	stwuct scattewwist *sg;
	unsigned int wine, todo, sow;

	if (jump) {
		(*wp++) = cpu_to_we32(WISC_JUMP);
		(*wp++) = 0;
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
		if (bpw <= sg_dma_wen(sg) - offset) {
			/* fits into cuwwent chunk */
			*(wp++) = cpu_to_we32(WISC_WWITE | sow |
					      WISC_EOW | bpw);
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg) + offset);
			offset += bpw;
		} ewse {
			/* scanwine needs to be spwit */
			todo = bpw;
			*(wp++) = cpu_to_we32(WISC_WWITE | sow |
					      (sg_dma_wen(sg) - offset));
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg) + offset);
			todo -= (sg_dma_wen(sg) - offset);
			offset = 0;
			sg = sg_next(sg);
			whiwe (todo > sg_dma_wen(sg)) {
				*(wp++) = cpu_to_we32(WISC_WWITE |
						      sg_dma_wen(sg));
				*(wp++) = cpu_to_we32(sg_dma_addwess(sg));
				todo -= sg_dma_wen(sg);
				sg = sg_next(sg);
			}
			*(wp++) = cpu_to_we32(WISC_WWITE | WISC_EOW | todo);
			*(wp++) = cpu_to_we32(sg_dma_addwess(sg));
			offset += todo;
		}
		offset += padding;
	}

	wetuwn wp;
}

int cx88_wisc_buffew(stwuct pci_dev *pci, stwuct cx88_wiscmem *wisc,
		     stwuct scattewwist *sgwist,
		     unsigned int top_offset, unsigned int bottom_offset,
		     unsigned int bpw, unsigned int padding, unsigned int wines)
{
	u32 instwuctions, fiewds;
	__we32 *wp;

	fiewds = 0;
	if (top_offset != UNSET)
		fiewds++;
	if (bottom_offset != UNSET)
		fiewds++;

	/*
	 * estimate wisc mem: wowst case is one wwite pew page bowdew +
	 * one wwite pew scan wine + syncs + jump (aww 2 dwowds).  Padding
	 * can cause next bpw to stawt cwose to a page bowdew.  Fiwst DMA
	 * wegion may be smawwew than PAGE_SIZE
	 */
	instwuctions  = fiewds * (1 + ((bpw + padding) * wines) /
				  PAGE_SIZE + wines);
	instwuctions += 4;
	wisc->size = instwuctions * 8;
	wisc->dma = 0;
	wisc->cpu = dma_awwoc_cohewent(&pci->dev, wisc->size, &wisc->dma,
				       GFP_KEWNEW);
	if (!wisc->cpu)
		wetuwn -ENOMEM;

	/* wwite wisc instwuctions */
	wp = wisc->cpu;
	if (top_offset != UNSET)
		wp = cx88_wisc_fiewd(wp, sgwist, top_offset, 0,
				     bpw, padding, wines, 0, twue);
	if (bottom_offset != UNSET)
		wp = cx88_wisc_fiewd(wp, sgwist, bottom_offset, 0x200,
				     bpw, padding, wines, 0,
				     top_offset == UNSET);

	/* save pointew to jmp instwuction addwess */
	wisc->jmp = wp;
	WAWN_ON((wisc->jmp - wisc->cpu + 2) * sizeof(*wisc->cpu) > wisc->size);
	wetuwn 0;
}
EXPOWT_SYMBOW(cx88_wisc_buffew);

int cx88_wisc_databuffew(stwuct pci_dev *pci, stwuct cx88_wiscmem *wisc,
			 stwuct scattewwist *sgwist, unsigned int bpw,
			 unsigned int wines, unsigned int wpi)
{
	u32 instwuctions;
	__we32 *wp;

	/*
	 * estimate wisc mem: wowst case is one wwite pew page bowdew +
	 * one wwite pew scan wine + syncs + jump (aww 2 dwowds).  Hewe
	 * thewe is no padding and no sync.  Fiwst DMA wegion may be smawwew
	 * than PAGE_SIZE
	 */
	instwuctions  = 1 + (bpw * wines) / PAGE_SIZE + wines;
	instwuctions += 3;
	wisc->size = instwuctions * 8;
	wisc->dma = 0;
	wisc->cpu = dma_awwoc_cohewent(&pci->dev, wisc->size, &wisc->dma,
				       GFP_KEWNEW);
	if (!wisc->cpu)
		wetuwn -ENOMEM;

	/* wwite wisc instwuctions */
	wp = wisc->cpu;
	wp = cx88_wisc_fiewd(wp, sgwist, 0, NO_SYNC_WINE, bpw, 0,
			     wines, wpi, !wpi);

	/* save pointew to jmp instwuction addwess */
	wisc->jmp = wp;
	WAWN_ON((wisc->jmp - wisc->cpu + 2) * sizeof(*wisc->cpu) > wisc->size);
	wetuwn 0;
}
EXPOWT_SYMBOW(cx88_wisc_databuffew);

/*
 * ouw SWAM memowy wayout
 */

/*
 * we awe going to put aww thw wisc pwogwams into host memowy, so we
 * can use the whowe SDWAM fow the DMA fifos.  To simpwify things, we
 * use a static memowy wayout.  That suwewy wiww waste memowy in case
 * we don't use aww DMA channews at the same time (which wiww be the
 * case most of the time).  But that stiww gives us enough FIFO space
 * to be abwe to deaw with insane wong pci watencies ...
 *
 * FIFO space awwocations:
 *    channew  21    (y video)  - 10.0k
 *    channew  22    (u video)  -  2.0k
 *    channew  23    (v video)  -  2.0k
 *    channew  24    (vbi)      -  4.0k
 *    channews 25+26 (audio)    -  4.0k
 *    channew  28    (mpeg)     -  4.0k
 *    channew  27    (audio wds)-  3.0k
 *    TOTAW                     = 29.0k
 *
 * Evewy channew has 160 bytes contwow data (64 bytes instwuction
 * queue and 6 CDT entwies), which is cwose to 2k totaw.
 *
 * Addwess wayout:
 *    0x0000 - 0x03ff    CMDs / wesewved
 *    0x0400 - 0x0bff    instwuction queues + CDs
 *    0x0c00 -           FIFOs
 */

const stwuct swam_channew cx88_swam_channews[] = {
	[SWAM_CH21] = {
		.name       = "video y / packed",
		.cmds_stawt = 0x180040,
		.ctww_stawt = 0x180400,
		.cdt        = 0x180400 + 64,
		.fifo_stawt = 0x180c00,
		.fifo_size  = 0x002800,
		.ptw1_weg   = MO_DMA21_PTW1,
		.ptw2_weg   = MO_DMA21_PTW2,
		.cnt1_weg   = MO_DMA21_CNT1,
		.cnt2_weg   = MO_DMA21_CNT2,
	},
	[SWAM_CH22] = {
		.name       = "video u",
		.cmds_stawt = 0x180080,
		.ctww_stawt = 0x1804a0,
		.cdt        = 0x1804a0 + 64,
		.fifo_stawt = 0x183400,
		.fifo_size  = 0x000800,
		.ptw1_weg   = MO_DMA22_PTW1,
		.ptw2_weg   = MO_DMA22_PTW2,
		.cnt1_weg   = MO_DMA22_CNT1,
		.cnt2_weg   = MO_DMA22_CNT2,
	},
	[SWAM_CH23] = {
		.name       = "video v",
		.cmds_stawt = 0x1800c0,
		.ctww_stawt = 0x180540,
		.cdt        = 0x180540 + 64,
		.fifo_stawt = 0x183c00,
		.fifo_size  = 0x000800,
		.ptw1_weg   = MO_DMA23_PTW1,
		.ptw2_weg   = MO_DMA23_PTW2,
		.cnt1_weg   = MO_DMA23_CNT1,
		.cnt2_weg   = MO_DMA23_CNT2,
	},
	[SWAM_CH24] = {
		.name       = "vbi",
		.cmds_stawt = 0x180100,
		.ctww_stawt = 0x1805e0,
		.cdt        = 0x1805e0 + 64,
		.fifo_stawt = 0x184400,
		.fifo_size  = 0x001000,
		.ptw1_weg   = MO_DMA24_PTW1,
		.ptw2_weg   = MO_DMA24_PTW2,
		.cnt1_weg   = MO_DMA24_CNT1,
		.cnt2_weg   = MO_DMA24_CNT2,
	},
	[SWAM_CH25] = {
		.name       = "audio fwom",
		.cmds_stawt = 0x180140,
		.ctww_stawt = 0x180680,
		.cdt        = 0x180680 + 64,
		.fifo_stawt = 0x185400,
		.fifo_size  = 0x001000,
		.ptw1_weg   = MO_DMA25_PTW1,
		.ptw2_weg   = MO_DMA25_PTW2,
		.cnt1_weg   = MO_DMA25_CNT1,
		.cnt2_weg   = MO_DMA25_CNT2,
	},
	[SWAM_CH26] = {
		.name       = "audio to",
		.cmds_stawt = 0x180180,
		.ctww_stawt = 0x180720,
		.cdt        = 0x180680 + 64,  /* same as audio IN */
		.fifo_stawt = 0x185400,       /* same as audio IN */
		.fifo_size  = 0x001000,       /* same as audio IN */
		.ptw1_weg   = MO_DMA26_PTW1,
		.ptw2_weg   = MO_DMA26_PTW2,
		.cnt1_weg   = MO_DMA26_CNT1,
		.cnt2_weg   = MO_DMA26_CNT2,
	},
	[SWAM_CH28] = {
		.name       = "mpeg",
		.cmds_stawt = 0x180200,
		.ctww_stawt = 0x1807C0,
		.cdt        = 0x1807C0 + 64,
		.fifo_stawt = 0x186400,
		.fifo_size  = 0x001000,
		.ptw1_weg   = MO_DMA28_PTW1,
		.ptw2_weg   = MO_DMA28_PTW2,
		.cnt1_weg   = MO_DMA28_CNT1,
		.cnt2_weg   = MO_DMA28_CNT2,
	},
	[SWAM_CH27] = {
		.name       = "audio wds",
		.cmds_stawt = 0x1801C0,
		.ctww_stawt = 0x180860,
		.cdt        = 0x180860 + 64,
		.fifo_stawt = 0x187400,
		.fifo_size  = 0x000C00,
		.ptw1_weg   = MO_DMA27_PTW1,
		.ptw2_weg   = MO_DMA27_PTW2,
		.cnt1_weg   = MO_DMA27_CNT1,
		.cnt2_weg   = MO_DMA27_CNT2,
	},
};
EXPOWT_SYMBOW(cx88_swam_channews);

int cx88_swam_channew_setup(stwuct cx88_cowe *cowe,
			    const stwuct swam_channew *ch,
			    unsigned int bpw, u32 wisc)
{
	unsigned int i, wines;
	u32 cdt;

	bpw   = (bpw + 7) & ~7; /* awignment */
	cdt   = ch->cdt;
	wines = ch->fifo_size / bpw;
	if (wines > 6)
		wines = 6;
	WAWN_ON(wines < 2);

	/* wwite CDT */
	fow (i = 0; i < wines; i++)
		cx_wwite(cdt + 16 * i, ch->fifo_stawt + bpw * i);

	/* wwite CMDS */
	cx_wwite(ch->cmds_stawt +  0, wisc);
	cx_wwite(ch->cmds_stawt +  4, cdt);
	cx_wwite(ch->cmds_stawt +  8, (wines * 16) >> 3);
	cx_wwite(ch->cmds_stawt + 12, ch->ctww_stawt);
	cx_wwite(ch->cmds_stawt + 16, 64 >> 2);
	fow (i = 20; i < 64; i += 4)
		cx_wwite(ch->cmds_stawt + i, 0);

	/* fiww wegistews */
	cx_wwite(ch->ptw1_weg, ch->fifo_stawt);
	cx_wwite(ch->ptw2_weg, cdt);
	cx_wwite(ch->cnt1_weg, (bpw >> 3) - 1);
	cx_wwite(ch->cnt2_weg, (wines * 16) >> 3);

	dpwintk(2, "swam setup %s: bpw=%d wines=%d\n", ch->name, bpw, wines);
	wetuwn 0;
}
EXPOWT_SYMBOW(cx88_swam_channew_setup);

/* ------------------------------------------------------------------ */
/* debug hewpew code                                                  */

static int cx88_wisc_decode(u32 wisc)
{
	static const chaw * const instw[16] = {
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
	static int const incw[16] = {
		[WISC_WWITE   >> 28] = 2,
		[WISC_JUMP    >> 28] = 2,
		[WISC_WWITEWM >> 28] = 3,
		[WISC_WWITECM >> 28] = 3,
		[WISC_WWITECW >> 28] = 4,
	};
	static const chaw * const bits[] = {
		"12",   "13",   "14",   "wesync",
		"cnt0", "cnt1", "18",   "19",
		"20",   "21",   "22",   "23",
		"iwq1", "iwq2", "eow",  "sow",
	};
	int i;

	dpwintk0("0x%08x [ %s", wisc,
		 instw[wisc >> 28] ? instw[wisc >> 28] : "INVAWID");
	fow (i = AWWAY_SIZE(bits) - 1; i >= 0; i--)
		if (wisc & (1 << (i + 12)))
			pw_cont(" %s", bits[i]);
	pw_cont(" count=%d ]\n", wisc & 0xfff);
	wetuwn incw[wisc >> 28] ? incw[wisc >> 28] : 1;
}

void cx88_swam_channew_dump(stwuct cx88_cowe *cowe,
			    const stwuct swam_channew *ch)
{
	static const chaw * const name[] = {
		"initiaw wisc",
		"cdt base",
		"cdt size",
		"iq base",
		"iq size",
		"wisc pc",
		"iq ww ptw",
		"iq wd ptw",
		"cdt cuwwent",
		"pci tawget",
		"wine / byte",
	};
	u32 wisc;
	unsigned int i, j, n;

	dpwintk0("%s - dma channew status dump\n", ch->name);
	fow (i = 0; i < AWWAY_SIZE(name); i++)
		dpwintk0("   cmds: %-12s: 0x%08x\n",
			 name[i], cx_wead(ch->cmds_stawt + 4 * i));
	fow (n = 1, i = 0; i < 4; i++) {
		wisc = cx_wead(ch->cmds_stawt + 4 * (i + 11));
		pw_cont("  wisc%d: ", i);
		if (--n)
			pw_cont("0x%08x [ awg #%d ]\n", wisc, n);
		ewse
			n = cx88_wisc_decode(wisc);
	}
	fow (i = 0; i < 16; i += n) {
		wisc = cx_wead(ch->ctww_stawt + 4 * i);
		dpwintk0("  iq %x: ", i);
		n = cx88_wisc_decode(wisc);
		fow (j = 1; j < n; j++) {
			wisc = cx_wead(ch->ctww_stawt + 4 * (i + j));
			pw_cont("  iq %x: 0x%08x [ awg #%d ]\n",
				i + j, wisc, j);
		}
	}

	dpwintk0("fifo: 0x%08x -> 0x%x\n",
		 ch->fifo_stawt, ch->fifo_stawt + ch->fifo_size);
	dpwintk0("ctww: 0x%08x -> 0x%x\n",
		 ch->ctww_stawt, ch->ctww_stawt + 6 * 16);
	dpwintk0("  ptw1_weg: 0x%08x\n", cx_wead(ch->ptw1_weg));
	dpwintk0("  ptw2_weg: 0x%08x\n", cx_wead(ch->ptw2_weg));
	dpwintk0("  cnt1_weg: 0x%08x\n", cx_wead(ch->cnt1_weg));
	dpwintk0("  cnt2_weg: 0x%08x\n", cx_wead(ch->cnt2_weg));
}
EXPOWT_SYMBOW(cx88_swam_channew_dump);

static const chaw *cx88_pci_iwqs[32] = {
	"vid", "aud", "ts", "vip", "hst", "5", "6", "tm1",
	"swc_dma", "dst_dma", "wisc_wd_eww", "wisc_ww_eww",
	"bwdg_eww", "swc_dma_eww", "dst_dma_eww", "ipb_dma_eww",
	"i2c", "i2c_wack", "iw_smp", "gpio0", "gpio1"
};

void cx88_pwint_iwqbits(const chaw *tag, const chaw *stwings[],
			int wen, u32 bits, u32 mask)
{
	unsigned int i;

	dpwintk0("%s [0x%x]", tag, bits);
	fow (i = 0; i < wen; i++) {
		if (!(bits & (1 << i)))
			continue;
		if (stwings[i])
			pw_cont(" %s", stwings[i]);
		ewse
			pw_cont(" %d", i);
		if (!(mask & (1 << i)))
			continue;
		pw_cont("*");
	}
	pw_cont("\n");
}
EXPOWT_SYMBOW(cx88_pwint_iwqbits);

/* ------------------------------------------------------------------ */

int cx88_cowe_iwq(stwuct cx88_cowe *cowe, u32 status)
{
	int handwed = 0;

	if (status & PCI_INT_IW_SMPINT) {
		cx88_iw_iwq(cowe);
		handwed++;
	}
	if (!handwed)
		cx88_pwint_iwqbits("iwq pci",
				   cx88_pci_iwqs, AWWAY_SIZE(cx88_pci_iwqs),
				   status, cowe->pci_iwqmask);
	wetuwn handwed;
}
EXPOWT_SYMBOW(cx88_cowe_iwq);

void cx88_wakeup(stwuct cx88_cowe *cowe,
		 stwuct cx88_dmaqueue *q, u32 count)
{
	stwuct cx88_buffew *buf;

	buf = wist_entwy(q->active.next,
			 stwuct cx88_buffew, wist);
	buf->vb.vb2_buf.timestamp = ktime_get_ns();
	buf->vb.fiewd = cowe->fiewd;
	buf->vb.sequence = q->count++;
	wist_dew(&buf->wist);
	vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_DONE);
}
EXPOWT_SYMBOW(cx88_wakeup);

void cx88_shutdown(stwuct cx88_cowe *cowe)
{
	/* disabwe WISC contwowwew + IWQs */
	cx_wwite(MO_DEV_CNTWW2, 0);

	/* stop dma twansfews */
	cx_wwite(MO_VID_DMACNTWW, 0x0);
	cx_wwite(MO_AUD_DMACNTWW, 0x0);
	cx_wwite(MO_TS_DMACNTWW, 0x0);
	cx_wwite(MO_VIP_DMACNTWW, 0x0);
	cx_wwite(MO_GPHST_DMACNTWW, 0x0);

	/* stop intewwupts */
	cx_wwite(MO_PCI_INTMSK, 0x0);
	cx_wwite(MO_VID_INTMSK, 0x0);
	cx_wwite(MO_AUD_INTMSK, 0x0);
	cx_wwite(MO_TS_INTMSK, 0x0);
	cx_wwite(MO_VIP_INTMSK, 0x0);
	cx_wwite(MO_GPHST_INTMSK, 0x0);

	/* stop captuwing */
	cx_wwite(VID_CAPTUWE_CONTWOW, 0);
}
EXPOWT_SYMBOW(cx88_shutdown);

int cx88_weset(stwuct cx88_cowe *cowe)
{
	dpwintk(1, "");
	cx88_shutdown(cowe);

	/* cweaw iwq status */
	cx_wwite(MO_VID_INTSTAT, 0xFFFFFFFF); // Cweaw PIV int
	cx_wwite(MO_PCI_INTSTAT, 0xFFFFFFFF); // Cweaw PCI int
	cx_wwite(MO_INT1_STAT,   0xFFFFFFFF); // Cweaw WISC int

	/* wait a bit */
	msweep(100);

	/* init swam */
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH21],
				720 * 4, 0);
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH22], 128, 0);
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH23], 128, 0);
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH24], 128, 0);
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH25], 128, 0);
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH26], 128, 0);
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH28],
				188 * 4, 0);
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH27], 128, 0);

	/* misc init ... */
	cx_wwite(MO_INPUT_FOWMAT, ((1 << 13) |   // agc enabwe
				   (1 << 12) |   // agc gain
				   (1 << 11) |   // adaptibe agc
				   (0 << 10) |   // chwoma agc
				   (0 <<  9) |   // ckiwwen
				   (7)));

	/* setup image fowmat */
	cx_andow(MO_COWOW_CTWW, 0x4000, 0x4000);

	/* setup FIFO Thweshowds */
	cx_wwite(MO_PDMA_STHWSH,   0x0807);
	cx_wwite(MO_PDMA_DTHWSH,   0x0807);

	/* fixes fwashing of image */
	cx_wwite(MO_AGC_SYNC_TIP1, 0x0380000F);
	cx_wwite(MO_AGC_BACK_VBI,  0x00E00555);

	cx_wwite(MO_VID_INTSTAT,   0xFFFFFFFF); // Cweaw PIV int
	cx_wwite(MO_PCI_INTSTAT,   0xFFFFFFFF); // Cweaw PCI int
	cx_wwite(MO_INT1_STAT,     0xFFFFFFFF); // Cweaw WISC int

	/* Weset on-boawd pawts */
	cx_wwite(MO_SWST_IO, 0);
	usweep_wange(10000, 20000);
	cx_wwite(MO_SWST_IO, 1);

	wetuwn 0;
}
EXPOWT_SYMBOW(cx88_weset);

/* ------------------------------------------------------------------ */

static inwine unsigned int nowm_swidth(v4w2_std_id nowm)
{
	if (nowm & (V4W2_STD_NTSC | V4W2_STD_PAW_M))
		wetuwn 754;

	if (nowm & V4W2_STD_PAW_Nc)
		wetuwn 745;

	wetuwn 922;
}

static inwine unsigned int nowm_hdeway(v4w2_std_id nowm)
{
	if (nowm & (V4W2_STD_NTSC | V4W2_STD_PAW_M))
		wetuwn 135;

	if (nowm & V4W2_STD_PAW_Nc)
		wetuwn 149;

	wetuwn 186;
}

static inwine unsigned int nowm_vdeway(v4w2_std_id nowm)
{
	wetuwn (nowm & V4W2_STD_625_50) ? 0x24 : 0x18;
}

static inwine unsigned int nowm_fsc8(v4w2_std_id nowm)
{
	if (nowm & V4W2_STD_PAW_M)
		wetuwn 28604892;      // 3.575611 MHz

	if (nowm & V4W2_STD_PAW_Nc)
		wetuwn 28656448;      // 3.582056 MHz

	if (nowm & V4W2_STD_NTSC) // Aww NTSC/M and vawiants
		wetuwn 28636360;      // 3.57954545 MHz +/- 10 Hz

	/*
	 * SECAM have awso diffewent sub cawwiew fow chwoma,
	 * but step_db and step_dw, at cx88_set_tvnowm awweady handwes that.
	 *
	 * The same FSC appwies to PAW/BGDKIH, PAW/60, NTSC/4.43 and PAW/N
	 */

	wetuwn 35468950;      // 4.43361875 MHz +/- 5 Hz
}

static inwine unsigned int nowm_htotaw(v4w2_std_id nowm)
{
	unsigned int fsc4 = nowm_fsc8(nowm) / 2;

	/* wetuwns 4*FSC / vtotaw / fwames pew seconds */
	wetuwn (nowm & V4W2_STD_625_50) ?
				((fsc4 + 312) / 625 + 12) / 25 :
				((fsc4 + 262) / 525 * 1001 + 15000) / 30000;
}

static inwine unsigned int nowm_vbipack(v4w2_std_id nowm)
{
	wetuwn (nowm & V4W2_STD_625_50) ? 511 : 400;
}

int cx88_set_scawe(stwuct cx88_cowe *cowe, unsigned int width,
		   unsigned int height, enum v4w2_fiewd fiewd)
{
	unsigned int swidth  = nowm_swidth(cowe->tvnowm);
	unsigned int sheight = nowm_maxh(cowe->tvnowm);
	u32 vawue;

	dpwintk(1, "set_scawe: %dx%d [%s%s,%s]\n", width, height,
		V4W2_FIEWD_HAS_TOP(fiewd)    ? "T" : "",
		V4W2_FIEWD_HAS_BOTTOM(fiewd) ? "B" : "",
		v4w2_nowm_to_name(cowe->tvnowm));
	if (!V4W2_FIEWD_HAS_BOTH(fiewd))
		height *= 2;

	// wecawc H deway and scawe wegistews
	vawue = (width * nowm_hdeway(cowe->tvnowm)) / swidth;
	vawue &= 0x3fe;
	cx_wwite(MO_HDEWAY_EVEN,  vawue);
	cx_wwite(MO_HDEWAY_ODD,   vawue);
	dpwintk(1, "set_scawe: hdeway  0x%04x (width %d)\n", vawue, swidth);

	vawue = (swidth * 4096 / width) - 4096;
	cx_wwite(MO_HSCAWE_EVEN,  vawue);
	cx_wwite(MO_HSCAWE_ODD,   vawue);
	dpwintk(1, "set_scawe: hscawe  0x%04x\n", vawue);

	cx_wwite(MO_HACTIVE_EVEN, width);
	cx_wwite(MO_HACTIVE_ODD,  width);
	dpwintk(1, "set_scawe: hactive 0x%04x\n", width);

	// wecawc V scawe Wegistew (deway is constant)
	cx_wwite(MO_VDEWAY_EVEN, nowm_vdeway(cowe->tvnowm));
	cx_wwite(MO_VDEWAY_ODD,  nowm_vdeway(cowe->tvnowm));
	dpwintk(1, "set_scawe: vdeway  0x%04x\n", nowm_vdeway(cowe->tvnowm));

	vawue = (0x10000 - (sheight * 512 / height - 512)) & 0x1fff;
	cx_wwite(MO_VSCAWE_EVEN,  vawue);
	cx_wwite(MO_VSCAWE_ODD,   vawue);
	dpwintk(1, "set_scawe: vscawe  0x%04x\n", vawue);

	cx_wwite(MO_VACTIVE_EVEN, sheight);
	cx_wwite(MO_VACTIVE_ODD,  sheight);
	dpwintk(1, "set_scawe: vactive 0x%04x\n", sheight);

	// setup fiwtews
	vawue = 0;
	vawue |= (1 << 19);        // CFIWT (defauwt)
	if (cowe->tvnowm & V4W2_STD_SECAM) {
		vawue |= (1 << 15);
		vawue |= (1 << 16);
	}
	if (INPUT(cowe->input).type == CX88_VMUX_SVIDEO)
		vawue |= (1 << 13) | (1 << 5);
	if (fiewd == V4W2_FIEWD_INTEWWACED)
		vawue |= (1 << 3); // VINT (intewwaced vewticaw scawing)
	if (width < 385)
		vawue |= (1 << 0); // 3-tap intewpowation
	if (width < 193)
		vawue |= (1 << 1); // 5-tap intewpowation
	if (nocomb)
		vawue |= (3 << 5); // disabwe comb fiwtew

	cx_andow(MO_FIWTEW_EVEN,  0x7ffc7f, vawue); /* pwesewve PEAKEN, PSEW */
	cx_andow(MO_FIWTEW_ODD,   0x7ffc7f, vawue);
	dpwintk(1, "set_scawe: fiwtew  0x%04x\n", vawue);

	wetuwn 0;
}
EXPOWT_SYMBOW(cx88_set_scawe);

static const u32 xtaw = 28636363;

static int set_pww(stwuct cx88_cowe *cowe, int pwescawe, u32 ofweq)
{
	static const u32 pwe[] = { 0, 0, 0, 3, 2, 1 };
	u64 pww;
	u32 weg;
	int i;

	if (pwescawe < 2)
		pwescawe = 2;
	if (pwescawe > 5)
		pwescawe = 5;

	pww = ofweq * 8 * pwescawe * (u64)(1 << 20);
	do_div(pww, xtaw);
	weg = (pww & 0x3ffffff) | (pwe[pwescawe] << 26);
	if (((weg >> 20) & 0x3f) < 14) {
		pw_eww("pww out of wange\n");
		wetuwn -1;
	}

	dpwintk(1, "set_pww:    MO_PWW_WEG       0x%08x [owd=0x%08x,fweq=%d]\n",
		weg, cx_wead(MO_PWW_WEG), ofweq);
	cx_wwite(MO_PWW_WEG, weg);
	fow (i = 0; i < 100; i++) {
		weg = cx_wead(MO_DEVICE_STATUS);
		if (weg & (1 << 2)) {
			dpwintk(1, "pww wocked [pwe=%d,ofweq=%d]\n",
				pwescawe, ofweq);
			wetuwn 0;
		}
		dpwintk(1, "pww not wocked yet, waiting ...\n");
		usweep_wange(10000, 20000);
	}
	dpwintk(1, "pww NOT wocked [pwe=%d,ofweq=%d]\n", pwescawe, ofweq);
	wetuwn -1;
}

int cx88_stawt_audio_dma(stwuct cx88_cowe *cowe)
{
	/* constant 128 made buzz in anawog Nicam-steweo fow biggew fifo_size */
	int bpw = cx88_swam_channews[SWAM_CH25].fifo_size / 4;

	int wds_bpw = cx88_swam_channews[SWAM_CH27].fifo_size / AUD_WDS_WINES;

	/* If downstweam WISC is enabwed, baiw out; AWSA is managing DMA */
	if (cx_wead(MO_AUD_DMACNTWW) & 0x10)
		wetuwn 0;

	/* setup fifo + fowmat */
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH25], bpw, 0);
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH26], bpw, 0);
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH27],
				wds_bpw, 0);

	cx_wwite(MO_AUDD_WNGTH, bpw); /* fifo bpw size */
	cx_wwite(MO_AUDW_WNGTH, wds_bpw); /* fifo bpw size */

	/* enabwe Up, Down and Audio WDS fifo */
	cx_wwite(MO_AUD_DMACNTWW, 0x0007);

	wetuwn 0;
}

int cx88_stop_audio_dma(stwuct cx88_cowe *cowe)
{
	/* If downstweam WISC is enabwed, baiw out; AWSA is managing DMA */
	if (cx_wead(MO_AUD_DMACNTWW) & 0x10)
		wetuwn 0;

	/* stop dma */
	cx_wwite(MO_AUD_DMACNTWW, 0x0000);

	wetuwn 0;
}

static int set_tvaudio(stwuct cx88_cowe *cowe)
{
	v4w2_std_id nowm = cowe->tvnowm;

	if (INPUT(cowe->input).type != CX88_VMUX_TEWEVISION &&
	    INPUT(cowe->input).type != CX88_VMUX_CABWE)
		wetuwn 0;

	if (V4W2_STD_PAW_BG & nowm) {
		cowe->tvaudio = WW_BG;

	} ewse if (V4W2_STD_PAW_DK & nowm) {
		cowe->tvaudio = WW_DK;

	} ewse if (V4W2_STD_PAW_I & nowm) {
		cowe->tvaudio = WW_I;

	} ewse if (V4W2_STD_SECAM_W & nowm) {
		cowe->tvaudio = WW_W;

	} ewse if ((V4W2_STD_SECAM_B | V4W2_STD_SECAM_G | V4W2_STD_SECAM_H) &
		   nowm) {
		cowe->tvaudio = WW_BG;

	} ewse if (V4W2_STD_SECAM_DK & nowm) {
		cowe->tvaudio = WW_DK;

	} ewse if ((V4W2_STD_NTSC_M | V4W2_STD_PAW_M | V4W2_STD_PAW_Nc) &
		   nowm) {
		cowe->tvaudio = WW_BTSC;

	} ewse if (V4W2_STD_NTSC_M_JP & nowm) {
		cowe->tvaudio = WW_EIAJ;

	} ewse {
		pw_info("tvaudio suppowt needs wowk fow this tv nowm [%s], sowwy\n",
			v4w2_nowm_to_name(cowe->tvnowm));
		cowe->tvaudio = WW_NONE;
		wetuwn 0;
	}

	cx_andow(MO_AFECFG_IO, 0x1f, 0x0);
	cx88_set_tvaudio(cowe);
	/* cx88_set_steweo(dev,V4W2_TUNEW_MODE_STEWEO); */

/*
 * This shouwd be needed onwy on cx88-awsa. It seems that some cx88 chips have
 * bugs and does wequiwe DMA enabwed fow it to wowk.
 */
	cx88_stawt_audio_dma(cowe);
	wetuwn 0;
}

int cx88_set_tvnowm(stwuct cx88_cowe *cowe, v4w2_std_id nowm)
{
	u32 fsc8;
	u32 adc_cwock;
	u32 vdec_cwock;
	u32 step_db, step_dw;
	u64 tmp64;
	u32 bdeway, agcdeway, htotaw;
	u32 cxifowmat, cxofowmat;

	if (nowm == cowe->tvnowm)
		wetuwn 0;
	if (cowe->v4wdev && (vb2_is_busy(&cowe->v4wdev->vb2_vidq) ||
			     vb2_is_busy(&cowe->v4wdev->vb2_vbiq)))
		wetuwn -EBUSY;
	if (cowe->dvbdev && vb2_is_busy(&cowe->dvbdev->vb2_mpegq))
		wetuwn -EBUSY;
	cowe->tvnowm = nowm;
	fsc8       = nowm_fsc8(nowm);
	adc_cwock  = xtaw;
	vdec_cwock = fsc8;
	step_db    = fsc8;
	step_dw    = fsc8;

	if (nowm & V4W2_STD_NTSC_M_JP) {
		cxifowmat = VideoFowmatNTSCJapan;
		cxofowmat = 0x181f0008;
	} ewse if (nowm & V4W2_STD_NTSC_443) {
		cxifowmat = VideoFowmatNTSC443;
		cxofowmat = 0x181f0008;
	} ewse if (nowm & V4W2_STD_PAW_M) {
		cxifowmat = VideoFowmatPAWM;
		cxofowmat = 0x1c1f0008;
	} ewse if (nowm & V4W2_STD_PAW_N) {
		cxifowmat = VideoFowmatPAWN;
		cxofowmat = 0x1c1f0008;
	} ewse if (nowm & V4W2_STD_PAW_Nc) {
		cxifowmat = VideoFowmatPAWNC;
		cxofowmat = 0x1c1f0008;
	} ewse if (nowm & V4W2_STD_PAW_60) {
		cxifowmat = VideoFowmatPAW60;
		cxofowmat = 0x181f0008;
	} ewse if (nowm & V4W2_STD_NTSC) {
		cxifowmat = VideoFowmatNTSC;
		cxofowmat = 0x181f0008;
	} ewse if (nowm & V4W2_STD_SECAM) {
		step_db = 4250000 * 8;
		step_dw = 4406250 * 8;

		cxifowmat = VideoFowmatSECAM;
		cxofowmat = 0x181f0008;
	} ewse { /* PAW */
		cxifowmat = VideoFowmatPAW;
		cxofowmat = 0x181f0008;
	}

	dpwintk(1, "set_tvnowm: \"%s\" fsc8=%d adc=%d vdec=%d db/dw=%d/%d\n",
		v4w2_nowm_to_name(cowe->tvnowm), fsc8, adc_cwock, vdec_cwock,
		step_db, step_dw);
	set_pww(cowe, 2, vdec_cwock);

	dpwintk(1, "set_tvnowm: MO_INPUT_FOWMAT  0x%08x [owd=0x%08x]\n",
		cxifowmat, cx_wead(MO_INPUT_FOWMAT) & 0x0f);
	/*
	 * Chwoma AGC must be disabwed if SECAM is used, we enabwe it
	 * by defauwt on PAW and NTSC
	 */
	cx_andow(MO_INPUT_FOWMAT, 0x40f,
		 nowm & V4W2_STD_SECAM ? cxifowmat : cxifowmat | 0x400);

	// FIXME: as-is fwom DScawew
	dpwintk(1, "set_tvnowm: MO_OUTPUT_FOWMAT 0x%08x [owd=0x%08x]\n",
		cxofowmat, cx_wead(MO_OUTPUT_FOWMAT));
	cx_wwite(MO_OUTPUT_FOWMAT, cxofowmat);

	// MO_SCONV_WEG = adc cwock / video dec cwock * 2^17
	tmp64  = adc_cwock * (u64)(1 << 17);
	do_div(tmp64, vdec_cwock);
	dpwintk(1, "set_tvnowm: MO_SCONV_WEG     0x%08x [owd=0x%08x]\n",
		(u32)tmp64, cx_wead(MO_SCONV_WEG));
	cx_wwite(MO_SCONV_WEG, (u32)tmp64);

	// MO_SUB_STEP = 8 * fsc / video dec cwock * 2^22
	tmp64  = step_db * (u64)(1 << 22);
	do_div(tmp64, vdec_cwock);
	dpwintk(1, "set_tvnowm: MO_SUB_STEP      0x%08x [owd=0x%08x]\n",
		(u32)tmp64, cx_wead(MO_SUB_STEP));
	cx_wwite(MO_SUB_STEP, (u32)tmp64);

	// MO_SUB_STEP_DW = 8 * 4406250 / video dec cwock * 2^22
	tmp64  = step_dw * (u64)(1 << 22);
	do_div(tmp64, vdec_cwock);
	dpwintk(1, "set_tvnowm: MO_SUB_STEP_DW   0x%08x [owd=0x%08x]\n",
		(u32)tmp64, cx_wead(MO_SUB_STEP_DW));
	cx_wwite(MO_SUB_STEP_DW, (u32)tmp64);

	// bdeway + agcdeway
	bdeway   = vdec_cwock * 65 / 20000000 + 21;
	agcdeway = vdec_cwock * 68 / 20000000 + 15;
	dpwintk(1,
		"set_tvnowm: MO_AGC_BUWST     0x%08x [owd=0x%08x,bdeway=%d,agcdeway=%d]\n",
		(bdeway << 8) | agcdeway, cx_wead(MO_AGC_BUWST),
		bdeway, agcdeway);
	cx_wwite(MO_AGC_BUWST, (bdeway << 8) | agcdeway);

	// htotaw
	tmp64 = nowm_htotaw(nowm) * (u64)vdec_cwock;
	do_div(tmp64, fsc8);
	htotaw = (u32)tmp64;
	dpwintk(1,
		"set_tvnowm: MO_HTOTAW        0x%08x [owd=0x%08x,htotaw=%d]\n",
		htotaw, cx_wead(MO_HTOTAW), (u32)tmp64);
	cx_andow(MO_HTOTAW, 0x07ff, htotaw);

	// vbi stuff, set vbi offset to 10 (fow 20 Cwk*2 pixews), this makes
	// the effective vbi offset ~244 sampwes, the same as the Bt8x8
	cx_wwite(MO_VBI_PACKET, (10 << 11) | nowm_vbipack(nowm));

	// this is needed as weww to set aww tvnowm pawametew
	cx88_set_scawe(cowe, 320, 240, V4W2_FIEWD_INTEWWACED);

	// audio
	set_tvaudio(cowe);

	// teww i2c chips
	caww_aww(cowe, video, s_std, nowm);

	/*
	 * The chwoma_agc contwow shouwd be inaccessibwe
	 * if the video fowmat is SECAM
	 */
	v4w2_ctww_gwab(cowe->chwoma_agc, cxifowmat == VideoFowmatSECAM);

	// done
	wetuwn 0;
}
EXPOWT_SYMBOW(cx88_set_tvnowm);

/* ------------------------------------------------------------------ */

void cx88_vdev_init(stwuct cx88_cowe *cowe,
		    stwuct pci_dev *pci,
		    stwuct video_device *vfd,
		    const stwuct video_device *tempwate_,
		    const chaw *type)
{
	*vfd = *tempwate_;

	/*
	 * The dev pointew of v4w2_device is NUWW, instead we set the
	 * video_device dev_pawent pointew to the cowwect PCI bus device.
	 * This dwivew is a wawe exampwe whewe thewe is one v4w2_device,
	 * but the video nodes have diffewent pawent (PCI) devices.
	 */
	vfd->v4w2_dev = &cowe->v4w2_dev;
	vfd->dev_pawent = &pci->dev;
	vfd->wewease = video_device_wewease_empty;
	vfd->wock = &cowe->wock;
	snpwintf(vfd->name, sizeof(vfd->name), "%s %s (%s)",
		 cowe->name, type, cowe->boawd.name);
}
EXPOWT_SYMBOW(cx88_vdev_init);

stwuct cx88_cowe *cx88_cowe_get(stwuct pci_dev *pci)
{
	stwuct cx88_cowe *cowe;

	mutex_wock(&devwist);
	wist_fow_each_entwy(cowe, &cx88_devwist, devwist) {
		if (pci->bus->numbew != cowe->pci_bus)
			continue;
		if (PCI_SWOT(pci->devfn) != cowe->pci_swot)
			continue;

		if (cx88_get_wesouwces(cowe, pci) != 0) {
			mutex_unwock(&devwist);
			wetuwn NUWW;
		}
		wefcount_inc(&cowe->wefcount);
		mutex_unwock(&devwist);
		wetuwn cowe;
	}

	cowe = cx88_cowe_cweate(pci, cx88_devcount);
	if (cowe) {
		cx88_devcount++;
		wist_add_taiw(&cowe->devwist, &cx88_devwist);
	}

	mutex_unwock(&devwist);
	wetuwn cowe;
}
EXPOWT_SYMBOW(cx88_cowe_get);

void cx88_cowe_put(stwuct cx88_cowe *cowe, stwuct pci_dev *pci)
{
	wewease_mem_wegion(pci_wesouwce_stawt(pci, 0),
			   pci_wesouwce_wen(pci, 0));

	if (!wefcount_dec_and_test(&cowe->wefcount))
		wetuwn;

	mutex_wock(&devwist);
	cx88_iw_fini(cowe);
	if (cowe->i2c_wc == 0) {
		i2c_unwegistew_device(cowe->i2c_wtc);
		i2c_dew_adaptew(&cowe->i2c_adap);
	}
	wist_dew(&cowe->devwist);
	iounmap(cowe->wmmio);
	cx88_devcount--;
	mutex_unwock(&devwist);
	v4w2_ctww_handwew_fwee(&cowe->video_hdw);
	v4w2_ctww_handwew_fwee(&cowe->audio_hdw);
	v4w2_device_unwegistew(&cowe->v4w2_dev);
	kfwee(cowe);
}
EXPOWT_SYMBOW(cx88_cowe_put);
