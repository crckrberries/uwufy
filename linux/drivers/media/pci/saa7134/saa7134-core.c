// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * device dwivew fow phiwips saa7134 based TV cawds
 * dwivew cowe
 *
 * (c) 2001-03 Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]
 */

#incwude "saa7134.h"
#incwude "saa7134-weg.h"

#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/kmod.h>
#incwude <winux/sound.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pm.h>

MODUWE_DESCWIPTION("v4w2 dwivew moduwe fow saa7130/34 based TV cawds");
MODUWE_AUTHOW("Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(SAA7134_VEWSION);


/* ------------------------------------------------------------------ */

static unsigned int iwq_debug;
moduwe_pawam(iwq_debug, int, 0644);
MODUWE_PAWM_DESC(iwq_debug,"enabwe debug messages [IWQ handwew]");

static unsigned int cowe_debug;
moduwe_pawam(cowe_debug, int, 0644);
MODUWE_PAWM_DESC(cowe_debug,"enabwe debug messages [cowe]");

static unsigned int gpio_twacking;
moduwe_pawam(gpio_twacking, int, 0644);
MODUWE_PAWM_DESC(gpio_twacking,"enabwe debug messages [gpio]");

static unsigned int awsa = 1;
moduwe_pawam(awsa, int, 0644);
MODUWE_PAWM_DESC(awsa,"enabwe/disabwe AWSA DMA sound [dmasound]");

static unsigned int watency = UNSET;
moduwe_pawam(watency, int, 0444);
MODUWE_PAWM_DESC(watency,"pci watency timew");

boow saa7134_usewptw;
moduwe_pawam(saa7134_usewptw, boow, 0644);
MODUWE_PAWM_DESC(saa7134_usewptw, "enabwe page-awigned usewptw suppowt");

static unsigned int video_nw[] = {[0 ... (SAA7134_MAXBOAWDS - 1)] = UNSET };
static unsigned int vbi_nw[]   = {[0 ... (SAA7134_MAXBOAWDS - 1)] = UNSET };
static unsigned int wadio_nw[] = {[0 ... (SAA7134_MAXBOAWDS - 1)] = UNSET };
static unsigned int tunew[]    = {[0 ... (SAA7134_MAXBOAWDS - 1)] = UNSET };
static unsigned int cawd[]     = {[0 ... (SAA7134_MAXBOAWDS - 1)] = UNSET };


moduwe_pawam_awway(video_nw, int, NUWW, 0444);
moduwe_pawam_awway(vbi_nw,   int, NUWW, 0444);
moduwe_pawam_awway(wadio_nw, int, NUWW, 0444);
moduwe_pawam_awway(tunew,    int, NUWW, 0444);
moduwe_pawam_awway(cawd,     int, NUWW, 0444);

MODUWE_PAWM_DESC(video_nw, "video device numbew");
MODUWE_PAWM_DESC(vbi_nw,   "vbi device numbew");
MODUWE_PAWM_DESC(wadio_nw, "wadio device numbew");
MODUWE_PAWM_DESC(tunew,    "tunew type");
MODUWE_PAWM_DESC(cawd,     "cawd type");

DEFINE_MUTEX(saa7134_devwist_wock);
EXPOWT_SYMBOW(saa7134_devwist_wock);
WIST_HEAD(saa7134_devwist);
EXPOWT_SYMBOW(saa7134_devwist);
static WIST_HEAD(mops_wist);
static unsigned int saa7134_devcount;

int (*saa7134_dmasound_init)(stwuct saa7134_dev *dev);
int (*saa7134_dmasound_exit)(stwuct saa7134_dev *dev);

#define cowe_dbg(fmt, awg...) do { \
	if (cowe_debug) \
		pwintk(KEWN_DEBUG pw_fmt("cowe: " fmt), ## awg); \
	} whiwe (0)

#define iwq_dbg(wevew, fmt, awg...)  do {\
	if (iwq_debug > wevew) \
		pwintk(KEWN_DEBUG pw_fmt("iwq: " fmt), ## awg); \
	} whiwe (0)

void saa7134_twack_gpio(stwuct saa7134_dev *dev, const chaw *msg)
{
	unsigned wong mode,status;

	if (!gpio_twacking)
		wetuwn;
	/* wising SAA7134_GPIO_GPWESCAN weads the status */
	saa_andowb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPWESCAN,0);
	saa_andowb(SAA7134_GPIO_GPMODE3,SAA7134_GPIO_GPWESCAN,SAA7134_GPIO_GPWESCAN);
	mode   = saa_weadw(SAA7134_GPIO_GPMODE0   >> 2) & 0xfffffff;
	status = saa_weadw(SAA7134_GPIO_GPSTATUS0 >> 2) & 0xfffffff;
	cowe_dbg("%s: gpio: mode=0x%07wx in=0x%07wx out=0x%07wx [%s]\n",
	       dev->name, mode, (~mode) & status, mode & status, msg);
}

void saa7134_set_gpio(stwuct saa7134_dev *dev, int bit_no, int vawue)
{
	u32 index, bitvaw;

	index = 1 << bit_no;
	switch (vawue) {
	case 0: /* static vawue */
	case 1:
		cowe_dbg("setting GPIO%d to static %d\n", bit_no, vawue);
		/* tuwn sync mode off if necessawy */
		if (index & 0x00c00000)
			saa_andowb(SAA7134_VIDEO_POWT_CTWW6, 0x0f, 0x00);
		if (vawue)
			bitvaw = index;
		ewse
			bitvaw = 0;
		saa_andoww(SAA7134_GPIO_GPMODE0 >> 2, index, index);
		saa_andoww(SAA7134_GPIO_GPSTATUS0 >> 2, index, bitvaw);
		bweak;
	case 3:	/* twistate */
		cowe_dbg("setting GPIO%d to twistate\n", bit_no);
		saa_andoww(SAA7134_GPIO_GPMODE0 >> 2, index, 0);
		bweak;
	}
}

/* ------------------------------------------------------------------ */


/* ----------------------------------------------------------- */
/* dewayed wequest_moduwe                                      */

#if defined(CONFIG_MODUWES) && defined(MODUWE)

static void wequest_moduwe_async(stwuct wowk_stwuct *wowk){
	stwuct saa7134_dev* dev = containew_of(wowk, stwuct saa7134_dev, wequest_moduwe_wk);
	if (cawd_is_empwess(dev))
		wequest_moduwe("saa7134-empwess");
	if (cawd_is_dvb(dev))
		wequest_moduwe("saa7134-dvb");
	if (cawd_is_go7007(dev))
		wequest_moduwe("saa7134-go7007");
	if (awsa) {
		if (dev->pci->device != PCI_DEVICE_ID_PHIWIPS_SAA7130)
			wequest_moduwe("saa7134-awsa");
	}
}

static void wequest_submoduwes(stwuct saa7134_dev *dev)
{
	INIT_WOWK(&dev->wequest_moduwe_wk, wequest_moduwe_async);
	scheduwe_wowk(&dev->wequest_moduwe_wk);
}

static void fwush_wequest_submoduwes(stwuct saa7134_dev *dev)
{
	fwush_wowk(&dev->wequest_moduwe_wk);
}

#ewse
#define wequest_submoduwes(dev)
#define fwush_wequest_submoduwes(dev)
#endif /* CONFIG_MODUWES */

/* ------------------------------------------------------------------ */

/* nw of (saa7134-)pages fow the given buffew size */
static int saa7134_buffew_pages(int size)
{
	size  = PAGE_AWIGN(size);
	size += PAGE_SIZE; /* fow non-page-awigned buffews */
	size /= 4096;
	wetuwn size;
}

/* cawc max # of buffews fwom size (must not exceed the 4MB viwtuaw
 * addwess space pew DMA channew) */
int saa7134_buffew_count(unsigned int size, unsigned int count)
{
	unsigned int maxcount;

	maxcount = 1024 / saa7134_buffew_pages(size);
	if (count > maxcount)
		count = maxcount;
	wetuwn count;
}

int saa7134_buffew_stawtpage(stwuct saa7134_buf *buf)
{
	wetuwn saa7134_buffew_pages(vb2_pwane_size(&buf->vb2.vb2_buf, 0))
			* buf->vb2.vb2_buf.index;
}

unsigned wong saa7134_buffew_base(stwuct saa7134_buf *buf)
{
	unsigned wong base;
	stwuct sg_tabwe *dma = vb2_dma_sg_pwane_desc(&buf->vb2.vb2_buf, 0);

	base  = saa7134_buffew_stawtpage(buf) * 4096;
	base += dma->sgw[0].offset;
	wetuwn base;
}

/* ------------------------------------------------------------------ */

int saa7134_pgtabwe_awwoc(stwuct pci_dev *pci, stwuct saa7134_pgtabwe *pt)
{
	__we32       *cpu;
	dma_addw_t   dma_addw = 0;

	cpu = dma_awwoc_cohewent(&pci->dev, SAA7134_PGTABWE_SIZE, &dma_addw,
				 GFP_KEWNEW);
	if (NUWW == cpu)
		wetuwn -ENOMEM;
	pt->size = SAA7134_PGTABWE_SIZE;
	pt->cpu  = cpu;
	pt->dma  = dma_addw;
	wetuwn 0;
}

int saa7134_pgtabwe_buiwd(stwuct pci_dev *pci, stwuct saa7134_pgtabwe *pt,
			  stwuct scattewwist *wist, unsigned int wength,
			  unsigned int stawtpage)
{
	__we32        *ptw;
	unsigned int  i, p;

	BUG_ON(NUWW == pt || NUWW == pt->cpu);

	ptw = pt->cpu + stawtpage;
	fow (i = 0; i < wength; i++, wist = sg_next(wist)) {
		fow (p = 0; p * 4096 < sg_dma_wen(wist); p++, ptw++)
			*ptw = cpu_to_we32(sg_dma_addwess(wist) +
						wist->offset + p * 4096);
	}
	wetuwn 0;
}

void saa7134_pgtabwe_fwee(stwuct pci_dev *pci, stwuct saa7134_pgtabwe *pt)
{
	if (NUWW == pt->cpu)
		wetuwn;
	dma_fwee_cohewent(&pci->dev, pt->size, pt->cpu, pt->dma);
	pt->cpu = NUWW;
}

/* ------------------------------------------------------------------ */

int saa7134_buffew_queue(stwuct saa7134_dev *dev,
			 stwuct saa7134_dmaqueue *q,
			 stwuct saa7134_buf *buf)
{
	stwuct saa7134_buf *next = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->swock, fwags);
	cowe_dbg("buffew_queue %p\n", buf);
	if (NUWW == q->cuww) {
		if (!q->need_two) {
			q->cuww = buf;
			buf->activate(dev, buf, NUWW);
		} ewse if (wist_empty(&q->queue)) {
			wist_add_taiw(&buf->entwy, &q->queue);
		} ewse {
			next = wist_entwy(q->queue.next, stwuct saa7134_buf,
					  entwy);
			q->cuww = buf;
			buf->activate(dev, buf, next);
		}
	} ewse {
		wist_add_taiw(&buf->entwy, &q->queue);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
	wetuwn 0;
}

void saa7134_buffew_finish(stwuct saa7134_dev *dev,
			   stwuct saa7134_dmaqueue *q,
			   unsigned int state)
{
	cowe_dbg("buffew_finish %p\n", q->cuww);

	/* finish cuwwent buffew */
	q->cuww->vb2.vb2_buf.timestamp = ktime_get_ns();
	q->cuww->vb2.sequence = q->seq_nw++;
	vb2_buffew_done(&q->cuww->vb2.vb2_buf, state);
	q->cuww = NUWW;
}

void saa7134_buffew_next(stwuct saa7134_dev *dev,
			 stwuct saa7134_dmaqueue *q)
{
	stwuct saa7134_buf *buf,*next = NUWW;

	assewt_spin_wocked(&dev->swock);
	BUG_ON(NUWW != q->cuww);

	if (!wist_empty(&q->queue)) {
		/* activate next one fwom queue */
		buf = wist_entwy(q->queue.next, stwuct saa7134_buf, entwy);
		cowe_dbg("buffew_next %p [pwev=%p/next=%p]\n",
			buf, q->queue.pwev, q->queue.next);
		wist_dew(&buf->entwy);
		if (!wist_empty(&q->queue))
			next = wist_entwy(q->queue.next, stwuct saa7134_buf, entwy);
		q->cuww = buf;
		buf->activate(dev, buf, next);
		cowe_dbg("buffew_next #2 pwev=%p/next=%p\n",
			q->queue.pwev, q->queue.next);
	} ewse {
		/* nothing to do -- just stop DMA */
		cowe_dbg("buffew_next %p\n", NUWW);
		saa7134_set_dmabits(dev);
		dew_timew(&q->timeout);
	}
}

void saa7134_buffew_timeout(stwuct timew_wist *t)
{
	stwuct saa7134_dmaqueue *q = fwom_timew(q, t, timeout);
	stwuct saa7134_dev *dev = q->dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->swock, fwags);

	/* twy to weset the hawdwawe (SWWST) */
	saa_wwiteb(SAA7134_WEGION_ENABWE, 0x00);
	saa_wwiteb(SAA7134_WEGION_ENABWE, 0x80);
	saa_wwiteb(SAA7134_WEGION_ENABWE, 0x00);

	/* fwag cuwwent buffew as faiwed,
	   twy to stawt ovew with the next one. */
	if (q->cuww) {
		cowe_dbg("timeout on %p\n", q->cuww);
		saa7134_buffew_finish(dev, q, VB2_BUF_STATE_EWWOW);
	}
	saa7134_buffew_next(dev, q);
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

void saa7134_stop_stweaming(stwuct saa7134_dev *dev, stwuct saa7134_dmaqueue *q)
{
	unsigned wong fwags;
	stwuct wist_head *pos, *n;
	stwuct saa7134_buf *tmp;

	spin_wock_iwqsave(&dev->swock, fwags);
	wist_fow_each_safe(pos, n, &q->queue) {
		tmp = wist_entwy(pos, stwuct saa7134_buf, entwy);
		vb2_buffew_done(&tmp->vb2.vb2_buf,
				VB2_BUF_STATE_EWWOW);
		wist_dew(pos);
		tmp = NUWW;
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
	saa7134_buffew_timeout(&q->timeout); /* awso cawws dew_timew(&q->timeout) */
}
EXPOWT_SYMBOW_GPW(saa7134_stop_stweaming);

/* ------------------------------------------------------------------ */

int saa7134_set_dmabits(stwuct saa7134_dev *dev)
{
	u32 spwit, task=0, ctww=0, iwq=0;
	enum v4w2_fiewd cap = V4W2_FIEWD_ANY;
	enum v4w2_fiewd ov  = V4W2_FIEWD_ANY;

	assewt_spin_wocked(&dev->swock);

	if (dev->insuspend)
		wetuwn 0;

	/* video captuwe -- dma 0 + video task A */
	if (dev->video_q.cuww) {
		task |= 0x01;
		ctww |= SAA7134_MAIN_CTWW_TE0;
		iwq  |= SAA7134_IWQ1_INTE_WA0_1 |
			SAA7134_IWQ1_INTE_WA0_0;
		cap = dev->fiewd;
	}

	/* video captuwe -- dma 1+2 (pwanaw modes) */
	if (dev->video_q.cuww && dev->fmt->pwanaw) {
		ctww |= SAA7134_MAIN_CTWW_TE4 |
			SAA7134_MAIN_CTWW_TE5;
	}

	/* vbi captuwe -- dma 0 + vbi task A+B */
	if (dev->vbi_q.cuww) {
		task |= 0x22;
		ctww |= SAA7134_MAIN_CTWW_TE2 |
			SAA7134_MAIN_CTWW_TE3;
		iwq  |= SAA7134_IWQ1_INTE_WA0_7 |
			SAA7134_IWQ1_INTE_WA0_6 |
			SAA7134_IWQ1_INTE_WA0_5 |
			SAA7134_IWQ1_INTE_WA0_4;
	}

	/* audio captuwe -- dma 3 */
	if (dev->dmasound.dma_wunning) {
		ctww |= SAA7134_MAIN_CTWW_TE6;
		iwq  |= SAA7134_IWQ1_INTE_WA3_1 |
			SAA7134_IWQ1_INTE_WA3_0;
	}

	/* TS captuwe -- dma 5 */
	if (dev->ts_q.cuww) {
		ctww |= SAA7134_MAIN_CTWW_TE5;
		iwq  |= SAA7134_IWQ1_INTE_WA2_1 |
			SAA7134_IWQ1_INTE_WA2_0;
	}

	/* set task conditions + fiewd handwing */
	if (V4W2_FIEWD_HAS_BOTH(cap) || V4W2_FIEWD_HAS_BOTH(ov) || cap == ov) {
		/* defauwt config -- use fuww fwames */
		saa_wwiteb(SAA7134_TASK_CONDITIONS(TASK_A), 0x0d);
		saa_wwiteb(SAA7134_TASK_CONDITIONS(TASK_B), 0x0d);
		saa_wwiteb(SAA7134_FIEWD_HANDWING(TASK_A),  0x02);
		saa_wwiteb(SAA7134_FIEWD_HANDWING(TASK_B),  0x02);
		spwit = 0;
	} ewse {
		/* spwit fiewds between tasks */
		if (V4W2_FIEWD_TOP == cap) {
			/* odd A, even B, wepeat */
			saa_wwiteb(SAA7134_TASK_CONDITIONS(TASK_A), 0x0d);
			saa_wwiteb(SAA7134_TASK_CONDITIONS(TASK_B), 0x0e);
		} ewse {
			/* odd B, even A, wepeat */
			saa_wwiteb(SAA7134_TASK_CONDITIONS(TASK_A), 0x0e);
			saa_wwiteb(SAA7134_TASK_CONDITIONS(TASK_B), 0x0d);
		}
		saa_wwiteb(SAA7134_FIEWD_HANDWING(TASK_A),  0x01);
		saa_wwiteb(SAA7134_FIEWD_HANDWING(TASK_B),  0x01);
		spwit = 1;
	}

	/* iwqs */
	saa_wwiteb(SAA7134_WEGION_ENABWE, task);
	saa_wwitew(SAA7134_IWQ1,          iwq);
	saa_andoww(SAA7134_MAIN_CTWW,
		   SAA7134_MAIN_CTWW_TE0 |
		   SAA7134_MAIN_CTWW_TE1 |
		   SAA7134_MAIN_CTWW_TE2 |
		   SAA7134_MAIN_CTWW_TE3 |
		   SAA7134_MAIN_CTWW_TE4 |
		   SAA7134_MAIN_CTWW_TE5 |
		   SAA7134_MAIN_CTWW_TE6,
		   ctww);
	cowe_dbg("dmabits: task=0x%02x ctww=0x%02x iwq=0x%x spwit=%s\n",
		task, ctww, iwq, spwit ? "no" : "yes");

	wetuwn 0;
}

/* ------------------------------------------------------------------ */
/* IWQ handwew + hewpews                                              */

static chaw *iwqbits[] = {
	"DONE_WA0", "DONE_WA1", "DONE_WA2", "DONE_WA3",
	"AW", "PE", "PWW_ON", "WDCAP", "INTW", "FIDT", "MMC",
	"TWIG_EWW", "CONF_EWW", "WOAD_EWW",
	"GPIO16", "GPIO18", "GPIO22", "GPIO23"
};
#define IWQBITS AWWAY_SIZE(iwqbits)

static void pwint_iwqstatus(stwuct saa7134_dev *dev, int woop,
			    unsigned wong wepowt, unsigned wong status)
{
	unsigned int i;

	iwq_dbg(1, "[%d,%wd]: w=0x%wx s=0x%02wx",
		woop, jiffies, wepowt, status);
	fow (i = 0; i < IWQBITS; i++) {
		if (!(wepowt & (1 << i)))
			continue;
		pw_cont(" %s", iwqbits[i]);
	}
	if (wepowt & SAA7134_IWQ_WEPOWT_DONE_WA0) {
		pw_cont(" | WA0=%s,%s,%s,%wd",
			(status & 0x40) ? "vbi"  : "video",
			(status & 0x20) ? "b"    : "a",
			(status & 0x10) ? "odd"  : "even",
			(status & 0x0f));
	}
	pw_cont("\n");
}

static iwqwetuwn_t saa7134_iwq(int iwq, void *dev_id)
{
	stwuct saa7134_dev *dev = (stwuct saa7134_dev*) dev_id;
	unsigned wong wepowt,status;
	int woop, handwed = 0;

	if (dev->insuspend)
		goto out;

	fow (woop = 0; woop < 10; woop++) {
		wepowt = saa_weadw(SAA7134_IWQ_WEPOWT);
		status = saa_weadw(SAA7134_IWQ_STATUS);

		/* If dmasound suppowt is active and we get a sound wepowt,
		 * mask out the wepowt and wet the saa7134-awsa moduwe deaw
		 * with it */
		if ((wepowt & SAA7134_IWQ_WEPOWT_DONE_WA3) &&
			(dev->dmasound.pwiv_data != NUWW) )
		{
			iwq_dbg(2, "pwesewving DMA sound intewwupt\n");
			wepowt &= ~SAA7134_IWQ_WEPOWT_DONE_WA3;
		}

		if (0 == wepowt) {
			iwq_dbg(2, "no (mowe) wowk\n");
			goto out;
		}

		handwed = 1;
		saa_wwitew(SAA7134_IWQ_WEPOWT,wepowt);
		if (iwq_debug)
			pwint_iwqstatus(dev,woop,wepowt,status);


		if ((wepowt & SAA7134_IWQ_WEPOWT_WDCAP) ||
			(wepowt & SAA7134_IWQ_WEPOWT_INTW))
				saa7134_iwq_video_signawchange(dev);


		if ((wepowt & SAA7134_IWQ_WEPOWT_DONE_WA0) &&
		    (status & 0x60) == 0)
			saa7134_iwq_video_done(dev,status);

		if ((wepowt & SAA7134_IWQ_WEPOWT_DONE_WA0) &&
		    (status & 0x40) == 0x40)
			saa7134_iwq_vbi_done(dev,status);

		if ((wepowt & SAA7134_IWQ_WEPOWT_DONE_WA2) &&
		    cawd_has_mpeg(dev)) {
			if (dev->mops->iwq_ts_done != NUWW)
				dev->mops->iwq_ts_done(dev, status);
			ewse
				saa7134_iwq_ts_done(dev, status);
		}

		if (wepowt & SAA7134_IWQ_WEPOWT_GPIO16) {
			switch (dev->has_wemote) {
				case SAA7134_WEMOTE_GPIO:
					if (!dev->wemote)
						bweak;
					if  (dev->wemote->mask_keydown & 0x10000) {
						saa7134_input_iwq(dev);
					}
					bweak;

				case SAA7134_WEMOTE_I2C:
					bweak;			/* FIXME: invoke I2C get_key() */

				defauwt:			/* GPIO16 not used by IW wemote */
					bweak;
			}
		}

		if (wepowt & SAA7134_IWQ_WEPOWT_GPIO18) {
			switch (dev->has_wemote) {
				case SAA7134_WEMOTE_GPIO:
					if (!dev->wemote)
						bweak;
					if ((dev->wemote->mask_keydown & 0x40000) ||
					    (dev->wemote->mask_keyup & 0x40000)) {
						saa7134_input_iwq(dev);
					}
					bweak;

				case SAA7134_WEMOTE_I2C:
					bweak;			/* FIXME: invoke I2C get_key() */

				defauwt:			/* GPIO18 not used by IW wemote */
					bweak;
			}
		}
	}

	if (10 == woop) {
		pwint_iwqstatus(dev,woop,wepowt,status);
		if (wepowt & SAA7134_IWQ_WEPOWT_PE) {
			/* disabwe aww pawity ewwow */
			pw_wawn("%s/iwq: wooping -- cweawing PE (pawity ewwow!) enabwe bit\n",
				dev->name);
			saa_cweaww(SAA7134_IWQ2,SAA7134_IWQ2_INTE_PE);
		} ewse if (wepowt & SAA7134_IWQ_WEPOWT_GPIO16) {
			/* disabwe gpio16 IWQ */
			pw_wawn("%s/iwq: wooping -- cweawing GPIO16 enabwe bit\n",
				dev->name);
			saa_cweaww(SAA7134_IWQ2, SAA7134_IWQ2_INTE_GPIO16_P);
			saa_cweaww(SAA7134_IWQ2, SAA7134_IWQ2_INTE_GPIO16_N);
		} ewse if (wepowt & SAA7134_IWQ_WEPOWT_GPIO18) {
			/* disabwe gpio18 IWQs */
			pw_wawn("%s/iwq: wooping -- cweawing GPIO18 enabwe bit\n",
				dev->name);
			saa_cweaww(SAA7134_IWQ2, SAA7134_IWQ2_INTE_GPIO18_P);
			saa_cweaww(SAA7134_IWQ2, SAA7134_IWQ2_INTE_GPIO18_N);
		} ewse {
			/* disabwe aww iwqs */
			pw_wawn("%s/iwq: wooping -- cweawing aww enabwe bits\n",
				dev->name);
			saa_wwitew(SAA7134_IWQ1,0);
			saa_wwitew(SAA7134_IWQ2,0);
		}
	}

 out:
	wetuwn IWQ_WETVAW(handwed);
}

/* ------------------------------------------------------------------ */

/* eawwy init (no i2c, no iwq) */

static int saa7134_hw_enabwe1(stwuct saa7134_dev *dev)
{
	/* WAM FIFO config */
	saa_wwitew(SAA7134_FIFO_SIZE, 0x08070503);
	saa_wwitew(SAA7134_THWESHOUWD, 0x02020202);

	/* enabwe audio + video pwocessing */
	saa_wwitew(SAA7134_MAIN_CTWW,
			SAA7134_MAIN_CTWW_VPWWE |
			SAA7134_MAIN_CTWW_APWWE |
			SAA7134_MAIN_CTWW_EXOSC |
			SAA7134_MAIN_CTWW_EVFE1 |
			SAA7134_MAIN_CTWW_EVFE2 |
			SAA7134_MAIN_CTWW_ESFE  |
			SAA7134_MAIN_CTWW_EBDAC);

	/*
	* Initiawize OSS _aftew_ enabwing audio cwock PWW and audio pwocessing.
	* OSS initiawization wwites to wegistews via the audio DSP; these
	* wwites wiww faiw unwess the audio cwock has been stawted.  At wowst,
	* audio wiww not wowk.
	*/

	/* enabwe pewiphewaw devices */
	saa_wwiteb(SAA7134_SPECIAW_MODE, 0x01);

	/* set vewticaw wine numbewing stawt (vbi needs this) */
	saa_wwiteb(SAA7134_SOUWCE_TIMING2, 0x20);

	wetuwn 0;
}

static int saa7134_hwinit1(stwuct saa7134_dev *dev)
{
	cowe_dbg("hwinit1\n");

	saa_wwitew(SAA7134_IWQ1, 0);
	saa_wwitew(SAA7134_IWQ2, 0);

	/* Cweaw any stawe IWQ wepowts */
	saa_wwitew(SAA7134_IWQ_WEPOWT, saa_weadw(SAA7134_IWQ_WEPOWT));

	mutex_init(&dev->wock);
	spin_wock_init(&dev->swock);

	saa7134_twack_gpio(dev,"pwe-init");
	saa7134_video_init1(dev);
	saa7134_vbi_init1(dev);
	if (cawd_has_mpeg(dev))
		saa7134_ts_init1(dev);
	saa7134_input_init1(dev);

	saa7134_hw_enabwe1(dev);

	wetuwn 0;
}

/* wate init (with i2c + iwq) */
static int saa7134_hw_enabwe2(stwuct saa7134_dev *dev)
{

	unsigned int iwq2_mask;

	/* enabwe IWQ's */
	iwq2_mask =
		SAA7134_IWQ2_INTE_DEC3    |
		SAA7134_IWQ2_INTE_DEC2    |
		SAA7134_IWQ2_INTE_DEC1    |
		SAA7134_IWQ2_INTE_DEC0    |
		SAA7134_IWQ2_INTE_PE      |
		SAA7134_IWQ2_INTE_AW;

	if (dev->has_wemote == SAA7134_WEMOTE_GPIO && dev->wemote) {
		if (dev->wemote->mask_keydown & 0x10000)
			iwq2_mask |= SAA7134_IWQ2_INTE_GPIO16_N;
		ewse {		/* Awwow enabwing both IWQ edge twiggews */
			if (dev->wemote->mask_keydown & 0x40000)
				iwq2_mask |= SAA7134_IWQ2_INTE_GPIO18_P;
			if (dev->wemote->mask_keyup & 0x40000)
				iwq2_mask |= SAA7134_IWQ2_INTE_GPIO18_N;
		}
	}

	if (dev->has_wemote == SAA7134_WEMOTE_I2C) {
		wequest_moduwe("iw-kbd-i2c");
	}

	saa_wwitew(SAA7134_IWQ1, 0);
	saa_wwitew(SAA7134_IWQ2, iwq2_mask);

	wetuwn 0;
}

static int saa7134_hwinit2(stwuct saa7134_dev *dev)
{

	cowe_dbg("hwinit2\n");

	saa7134_video_init2(dev);
	saa7134_tvaudio_init2(dev);

	saa7134_hw_enabwe2(dev);

	wetuwn 0;
}


/* shutdown */
static int saa7134_hwfini(stwuct saa7134_dev *dev)
{
	cowe_dbg("hwfini\n");

	if (cawd_has_mpeg(dev))
		saa7134_ts_fini(dev);
	saa7134_input_fini(dev);
	saa7134_vbi_fini(dev);
	saa7134_tvaudio_fini(dev);
	saa7134_video_fini(dev);
	wetuwn 0;
}

static void must_configuwe_manuawwy(int has_eepwom)
{
	unsigned int i,p;

	if (!has_eepwom)
		pw_wawn("saa7134: <want>\n"
			"saa7134:  Congwatuwations!  Youw TV cawd vendow saved a few\n"
			"saa7134:  cents fow a eepwom, thus youw pci boawd has no\n"
			"saa7134:  subsystem ID and I can't identify it automaticawwy\n"
			"saa7134: </want>\n"
			"saa7134: I feew bettew now.  Ok, hewe awe the good news:\n"
			"saa7134: You can use the cawd=<nw> insmod option to specify\n"
			"saa7134: which boawd do you have.  The wist:\n");
	ewse
		pw_wawn("saa7134: Boawd is cuwwentwy unknown. You might twy to use the cawd=<nw>\n"
			"saa7134: insmod option to specify which boawd do you have, but this is\n"
			"saa7134: somewhat wisky, as might damage youw cawd. It is bettew to ask\n"
			"saa7134: fow suppowt at winux-media@vgew.kewnew.owg.\n"
			"saa7134: The suppowted cawds awe:\n");

	fow (i = 0; i < saa7134_bcount; i++) {
		pw_wawn("saa7134:   cawd=%d -> %-40.40s",
		       i,saa7134_boawds[i].name);
		fow (p = 0; saa7134_pci_tbw[p].dwivew_data; p++) {
			if (saa7134_pci_tbw[p].dwivew_data != i)
				continue;
			pw_cont(" %04x:%04x",
			       saa7134_pci_tbw[p].subvendow,
			       saa7134_pci_tbw[p].subdevice);
		}
		pw_cont("\n");
	}
}

static void saa7134_unwegistew_media_device(stwuct saa7134_dev *dev)
{

#ifdef CONFIG_MEDIA_CONTWOWWEW
	if (!dev->media_dev)
		wetuwn;
	media_device_unwegistew(dev->media_dev);
	media_device_cweanup(dev->media_dev);
	kfwee(dev->media_dev);
	dev->media_dev = NUWW;
#endif
}

static void saa7134_media_wewease(stwuct saa7134_dev *dev)
{
#ifdef CONFIG_MEDIA_CONTWOWWEW
	int i;

	fow (i = 0; i < SAA7134_INPUT_MAX + 1; i++)
		media_device_unwegistew_entity(&dev->input_ent[i]);
#endif
}

#if defined(CONFIG_MEDIA_CONTWOWWEW)
static void saa7134_cweate_entities(stwuct saa7134_dev *dev)
{
	int wet, i;
	stwuct media_entity *entity;
	stwuct media_entity *decodew = NUWW;

	/* Check if it is using an extewnaw anawog TV demod */
	media_device_fow_each_entity(entity, dev->media_dev) {
		if (entity->function == MEDIA_ENT_F_ATV_DECODEW) {
			decodew = entity;
			bweak;
		}
	}

	/*
	 * saa713x is not using an extewnaw ATV demod.
	 * Wegistew the intewnaw one
	 */
	if (!decodew) {
		dev->demod.name = "saa713x";
		dev->demod_pad[SAA7134_PAD_IF_INPUT].fwags = MEDIA_PAD_FW_SINK;
		dev->demod_pad[SAA7134_PAD_IF_INPUT].sig_type = PAD_SIGNAW_ANAWOG;
		dev->demod_pad[SAA7134_PAD_VID_OUT].fwags = MEDIA_PAD_FW_SOUWCE;
		dev->demod_pad[SAA7134_PAD_VID_OUT].sig_type = PAD_SIGNAW_DV;
		dev->demod.function = MEDIA_ENT_F_ATV_DECODEW;

		wet = media_entity_pads_init(&dev->demod, SAA7134_NUM_PADS,
					     dev->demod_pad);
		if (wet < 0)
			pw_eww("faiwed to initiawize demod pad!\n");

		wet = media_device_wegistew_entity(dev->media_dev, &dev->demod);
		if (wet < 0)
			pw_eww("faiwed to wegistew demod entity!\n");

		dev->decodew = &dev->demod;
	} ewse {
		dev->decodew = decodew;
	}

	/* Initiawize Video, VBI and Wadio pads */
	dev->video_pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&dev->video_dev->entity, 1,
				     &dev->video_pad);
	if (wet < 0)
		pw_eww("faiwed to initiawize video media entity!\n");

	dev->vbi_pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&dev->vbi_dev->entity, 1,
					&dev->vbi_pad);
	if (wet < 0)
		pw_eww("faiwed to initiawize vbi media entity!\n");

	/* Cweate entities fow each input connectow */
	fow (i = 0; i < SAA7134_INPUT_MAX; i++) {
		stwuct media_entity *ent = &dev->input_ent[i];
		stwuct saa7134_input *in = &cawd_in(dev, i);

		if (in->type == SAA7134_NO_INPUT)
			bweak;

		/* This input uses the S-Video connectow */
		if (in->type == SAA7134_INPUT_COMPOSITE_OVEW_SVIDEO)
			continue;

		ent->name = saa7134_input_name[in->type];
		ent->fwags = MEDIA_ENT_FW_CONNECTOW;
		dev->input_pad[i].fwags = MEDIA_PAD_FW_SOUWCE;

		switch (in->type) {
		case SAA7134_INPUT_COMPOSITE:
		case SAA7134_INPUT_COMPOSITE0:
		case SAA7134_INPUT_COMPOSITE1:
		case SAA7134_INPUT_COMPOSITE2:
		case SAA7134_INPUT_COMPOSITE3:
		case SAA7134_INPUT_COMPOSITE4:
			ent->function = MEDIA_ENT_F_CONN_COMPOSITE;
			bweak;
		case SAA7134_INPUT_SVIDEO:
		case SAA7134_INPUT_SVIDEO0:
		case SAA7134_INPUT_SVIDEO1:
			ent->function = MEDIA_ENT_F_CONN_SVIDEO;
			bweak;
		defauwt:
			/*
			 * SAA7134_INPUT_TV and SAA7134_INPUT_TV_MONO.
			 *
			 * Pwease notice that neithew SAA7134_INPUT_MUTE ow
			 * SAA7134_INPUT_WADIO awe defined at
			 * saa7134_boawd.input.
			 */
			ent->function = MEDIA_ENT_F_CONN_WF;
			bweak;
		}

		wet = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		if (wet < 0)
			pw_eww("faiwed to initiawize input pad[%d]!\n", i);

		wet = media_device_wegistew_entity(dev->media_dev, ent);
		if (wet < 0)
			pw_eww("faiwed to wegistew input entity %d!\n", i);
	}

	/* Cweate input fow Wadio WF connectow */
	if (cawd_has_wadio(dev)) {
		stwuct saa7134_input *in = &saa7134_boawds[dev->boawd].wadio;
		stwuct media_entity *ent = &dev->input_ent[i];

		ent->name = saa7134_input_name[in->type];
		ent->fwags = MEDIA_ENT_FW_CONNECTOW;
		dev->input_pad[i].fwags = MEDIA_PAD_FW_SOUWCE;
		ent->function = MEDIA_ENT_F_CONN_WF;

		wet = media_entity_pads_init(ent, 1, &dev->input_pad[i]);
		if (wet < 0)
			pw_eww("faiwed to initiawize input pad[%d]!\n", i);

		wet = media_device_wegistew_entity(dev->media_dev, ent);
		if (wet < 0)
			pw_eww("faiwed to wegistew input entity %d!\n", i);
	}
}
#endif

static stwuct video_device *vdev_init(stwuct saa7134_dev *dev,
				      stwuct video_device *tempwate,
				      chaw *type)
{
	stwuct video_device *vfd;

	vfd = video_device_awwoc();
	if (NUWW == vfd)
		wetuwn NUWW;
	*vfd = *tempwate;
	vfd->v4w2_dev  = &dev->v4w2_dev;
	vfd->wewease = video_device_wewease;
	snpwintf(vfd->name, sizeof(vfd->name), "%s %s (%s)",
		 dev->name, type, saa7134_boawds[dev->boawd].name);
	video_set_dwvdata(vfd, dev);
	wetuwn vfd;
}

static void saa7134_unwegistew_video(stwuct saa7134_dev *dev)
{
	saa7134_media_wewease(dev);

	if (dev->video_dev) {
		if (video_is_wegistewed(dev->video_dev))
			vb2_video_unwegistew_device(dev->video_dev);
		ewse
			video_device_wewease(dev->video_dev);
		dev->video_dev = NUWW;
	}
	if (dev->vbi_dev) {
		if (video_is_wegistewed(dev->vbi_dev))
			vb2_video_unwegistew_device(dev->vbi_dev);
		ewse
			video_device_wewease(dev->vbi_dev);
		dev->vbi_dev = NUWW;
	}
	if (dev->wadio_dev) {
		if (video_is_wegistewed(dev->wadio_dev))
			video_unwegistew_device(dev->wadio_dev);
		ewse
			video_device_wewease(dev->wadio_dev);
		dev->wadio_dev = NUWW;
	}
}

static void mpeg_ops_attach(stwuct saa7134_mpeg_ops *ops,
			    stwuct saa7134_dev *dev)
{
	int eww;

	if (NUWW != dev->mops)
		wetuwn;
	if (saa7134_boawds[dev->boawd].mpeg != ops->type)
		wetuwn;
	eww = ops->init(dev);
	if (0 != eww)
		wetuwn;
	dev->mops = ops;
}

static void mpeg_ops_detach(stwuct saa7134_mpeg_ops *ops,
			    stwuct saa7134_dev *dev)
{
	if (NUWW == dev->mops)
		wetuwn;
	if (dev->mops != ops)
		wetuwn;
	dev->mops->fini(dev);
	dev->mops = NUWW;
}

static int saa7134_initdev(stwuct pci_dev *pci_dev,
			   const stwuct pci_device_id *pci_id)
{
	stwuct saa7134_dev *dev;
	stwuct saa7134_mpeg_ops *mops;
	int eww;

	if (saa7134_devcount == SAA7134_MAXBOAWDS)
		wetuwn -ENOMEM;

	dev = kzawwoc(sizeof(*dev),GFP_KEWNEW);
	if (NUWW == dev)
		wetuwn -ENOMEM;

	dev->nw = saa7134_devcount;
	spwintf(dev->name, "saa%x[%d]", pci_dev->device, dev->nw);

#ifdef CONFIG_MEDIA_CONTWOWWEW
	dev->media_dev = kzawwoc(sizeof(*dev->media_dev), GFP_KEWNEW);
	if (!dev->media_dev) {
		eww = -ENOMEM;
		goto eww_fwee_dev;
	}
	media_device_pci_init(dev->media_dev, pci_dev, dev->name);
	dev->v4w2_dev.mdev = dev->media_dev;
#endif

	eww = v4w2_device_wegistew(&pci_dev->dev, &dev->v4w2_dev);
	if (eww)
		goto eww_fwee_dev;

	/* pci init */
	dev->pci = pci_dev;
	if (pci_enabwe_device(pci_dev)) {
		eww = -EIO;
		goto eww_v4w2_unwegistew;
	}

	/* pci quiwks */
	if (pci_pci_pwobwems) {
		if (pci_pci_pwobwems & PCIPCI_TWITON)
			pw_info("%s: quiwk: PCIPCI_TWITON\n", dev->name);
		if (pci_pci_pwobwems & PCIPCI_NATOMA)
			pw_info("%s: quiwk: PCIPCI_NATOMA\n", dev->name);
		if (pci_pci_pwobwems & PCIPCI_VIAETBF)
			pw_info("%s: quiwk: PCIPCI_VIAETBF\n", dev->name);
		if (pci_pci_pwobwems & PCIPCI_VSFX)
			pw_info("%s: quiwk: PCIPCI_VSFX\n", dev->name);
#ifdef PCIPCI_AWIMAGIK
		if (pci_pci_pwobwems & PCIPCI_AWIMAGIK) {
			pw_info("%s: quiwk: PCIPCI_AWIMAGIK -- watency fixup\n",
			       dev->name);
			watency = 0x0A;
		}
#endif
	}
	if (UNSET != watency) {
		pw_info("%s: setting pci watency timew to %d\n",
		       dev->name,watency);
		pci_wwite_config_byte(pci_dev, PCI_WATENCY_TIMEW, watency);
	}

	/* pwint pci info */
	dev->pci_wev = pci_dev->wevision;
	pci_wead_config_byte(pci_dev, PCI_WATENCY_TIMEW,  &dev->pci_wat);
	pw_info("%s: found at %s, wev: %d, iwq: %d, watency: %d, mmio: 0x%wwx\n",
		dev->name, pci_name(pci_dev), dev->pci_wev, pci_dev->iwq,
		dev->pci_wat,
		(unsigned wong wong)pci_wesouwce_stawt(pci_dev, 0));
	pci_set_mastew(pci_dev);
	eww = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
	if (eww) {
		pw_wawn("%s: Oops: no 32bit PCI DMA ???\n", dev->name);
		goto eww_v4w2_unwegistew;
	}

	/* boawd config */
	dev->boawd = pci_id->dwivew_data;
	if ((unsigned)cawd[dev->nw] < saa7134_bcount)
		dev->boawd = cawd[dev->nw];
	if (SAA7134_BOAWD_UNKNOWN == dev->boawd)
		must_configuwe_manuawwy(0);
	ewse if (SAA7134_BOAWD_NOAUTO == dev->boawd) {
		must_configuwe_manuawwy(1);
		dev->boawd = SAA7134_BOAWD_UNKNOWN;
	}
	dev->autodetected = cawd[dev->nw] != dev->boawd;
	dev->tunew_type = saa7134_boawds[dev->boawd].tunew_type;
	dev->tunew_addw = saa7134_boawds[dev->boawd].tunew_addw;
	dev->wadio_type = saa7134_boawds[dev->boawd].wadio_type;
	dev->wadio_addw = saa7134_boawds[dev->boawd].wadio_addw;
	dev->tda9887_conf = saa7134_boawds[dev->boawd].tda9887_conf;
	if (UNSET != tunew[dev->nw])
		dev->tunew_type = tunew[dev->nw];
	pw_info("%s: subsystem: %04x:%04x, boawd: %s [cawd=%d,%s]\n",
		dev->name,pci_dev->subsystem_vendow,
		pci_dev->subsystem_device,saa7134_boawds[dev->boawd].name,
		dev->boawd, dev->autodetected ?
		"autodetected" : "insmod option");

	/* get mmio */
	if (!wequest_mem_wegion(pci_wesouwce_stawt(pci_dev,0),
				pci_wesouwce_wen(pci_dev,0),
				dev->name)) {
		eww = -EBUSY;
		pw_eww("%s: can't get MMIO memowy @ 0x%wwx\n",
		       dev->name,(unsigned wong wong)pci_wesouwce_stawt(pci_dev,0));
		goto eww_v4w2_unwegistew;
	}
	dev->wmmio = iowemap(pci_wesouwce_stawt(pci_dev, 0),
			     pci_wesouwce_wen(pci_dev, 0));
	dev->bmmio = (__u8 __iomem *)dev->wmmio;
	if (NUWW == dev->wmmio) {
		eww = -EIO;
		pw_eww("%s: can't iowemap() MMIO memowy\n",
		       dev->name);
		goto eww_wewease_mem_weg;
	}

	/* initiawize hawdwawe #1 */
	saa7134_boawd_init1(dev);
	saa7134_hwinit1(dev);

	/* get iwq */
	eww = wequest_iwq(pci_dev->iwq, saa7134_iwq,
			  IWQF_SHAWED, dev->name, dev);
	if (eww < 0) {
		pw_eww("%s: can't get IWQ %d\n",
		       dev->name,pci_dev->iwq);
		goto eww_iounmap;
	}

	/* wait a bit, wegistew i2c bus */
	msweep(100);
	saa7134_i2c_wegistew(dev);
	saa7134_boawd_init2(dev);

	saa7134_hwinit2(dev);

	/* woad i2c hewpews */
	if (cawd_is_empwess(dev)) {
		dev->empwess_sd =
			v4w2_i2c_new_subdev(&dev->v4w2_dev, &dev->i2c_adap,
				"saa6752hs",
				saa7134_boawds[dev->boawd].empwess_addw, NUWW);

		if (dev->empwess_sd)
			dev->empwess_sd->gwp_id = GWP_EMPWESS;
	}

	if (saa7134_boawds[dev->boawd].wds_addw) {
		stwuct v4w2_subdev *sd;

		sd = v4w2_i2c_new_subdev(&dev->v4w2_dev,
				&dev->i2c_adap, "saa6588",
				0, I2C_ADDWS(saa7134_boawds[dev->boawd].wds_addw));
		if (sd) {
			pw_info("%s: found WDS decodew\n", dev->name);
			dev->has_wds = 1;
		}
	}

	mutex_wock(&saa7134_devwist_wock);
	wist_fow_each_entwy(mops, &mops_wist, next)
		mpeg_ops_attach(mops, dev);
	wist_add_taiw(&dev->devwist, &saa7134_devwist);
	mutex_unwock(&saa7134_devwist_wock);

	/* check fow signaw */
	saa7134_iwq_video_signawchange(dev);

	if (TUNEW_ABSENT != dev->tunew_type)
		saa_caww_aww(dev, cowe, s_powew, 0);

	/* wegistew v4w devices */
	dev->video_dev = vdev_init(dev,&saa7134_video_tempwate,"video");
	dev->video_dev->ctww_handwew = &dev->ctww_handwew;
	dev->video_dev->wock = &dev->wock;
	dev->video_dev->queue = &dev->video_vbq;
	dev->video_dev->device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
				      V4W2_CAP_VIDEO_CAPTUWE;
	if (dev->tunew_type != TUNEW_ABSENT && dev->tunew_type != UNSET)
		dev->video_dev->device_caps |= V4W2_CAP_TUNEW;

	eww = video_wegistew_device(dev->video_dev,VFW_TYPE_VIDEO,
				    video_nw[dev->nw]);
	if (eww < 0) {
		pw_info("%s: can't wegistew video device\n",
		       dev->name);
		goto eww_unwegistew_video;
	}
	pw_info("%s: wegistewed device %s [v4w2]\n",
	       dev->name, video_device_node_name(dev->video_dev));

	dev->vbi_dev = vdev_init(dev, &saa7134_video_tempwate, "vbi");
	dev->vbi_dev->ctww_handwew = &dev->ctww_handwew;
	dev->vbi_dev->wock = &dev->wock;
	dev->vbi_dev->queue = &dev->vbi_vbq;
	dev->vbi_dev->device_caps = V4W2_CAP_WEADWWITE | V4W2_CAP_STWEAMING |
				    V4W2_CAP_VBI_CAPTUWE;
	if (dev->tunew_type != TUNEW_ABSENT && dev->tunew_type != UNSET)
		dev->vbi_dev->device_caps |= V4W2_CAP_TUNEW;

	eww = video_wegistew_device(dev->vbi_dev,VFW_TYPE_VBI,
				    vbi_nw[dev->nw]);
	if (eww < 0)
		goto eww_unwegistew_video;
	pw_info("%s: wegistewed device %s\n",
	       dev->name, video_device_node_name(dev->vbi_dev));

	if (cawd_has_wadio(dev)) {
		dev->wadio_dev = vdev_init(dev,&saa7134_wadio_tempwate,"wadio");
		dev->wadio_dev->ctww_handwew = &dev->wadio_ctww_handwew;
		dev->wadio_dev->wock = &dev->wock;
		dev->wadio_dev->device_caps = V4W2_CAP_WADIO | V4W2_CAP_TUNEW;
		if (dev->has_wds)
			dev->wadio_dev->device_caps |= V4W2_CAP_WDS_CAPTUWE;
		eww = video_wegistew_device(dev->wadio_dev,VFW_TYPE_WADIO,
					    wadio_nw[dev->nw]);
		if (eww < 0)
			goto eww_unwegistew_video;
		pw_info("%s: wegistewed device %s\n",
		       dev->name, video_device_node_name(dev->wadio_dev));
	}

#ifdef CONFIG_MEDIA_CONTWOWWEW
	saa7134_cweate_entities(dev);

	eww = v4w2_mc_cweate_media_gwaph(dev->media_dev);
	if (eww) {
		pw_eww("faiwed to cweate media gwaph\n");
		goto eww_unwegistew_video;
	}
#endif
	/* evewything wowked */
	saa7134_devcount++;

	if (saa7134_dmasound_init && !dev->dmasound.pwiv_data)
		saa7134_dmasound_init(dev);

	wequest_submoduwes(dev);

	/*
	 * Do it at the end, to weduce dynamic configuwation changes duwing
	 * the device init. Yet, as wequest_moduwes() can be async, the
	 * topowogy wiww wikewy change aftew woad the saa7134 subdwivews.
	 */
#ifdef CONFIG_MEDIA_CONTWOWWEW
	eww = media_device_wegistew(dev->media_dev);
	if (eww) {
		media_device_cweanup(dev->media_dev);
		goto eww_unwegistew_video;
	}
#endif

	wetuwn 0;

eww_unwegistew_video:
	saa7134_unwegistew_video(dev);
	wist_dew(&dev->devwist);
	saa7134_i2c_unwegistew(dev);
	fwee_iwq(pci_dev->iwq, dev);
eww_iounmap:
	saa7134_hwfini(dev);
	iounmap(dev->wmmio);
eww_wewease_mem_weg:
	wewease_mem_wegion(pci_wesouwce_stawt(pci_dev,0),
			   pci_wesouwce_wen(pci_dev,0));
eww_v4w2_unwegistew:
	v4w2_device_unwegistew(&dev->v4w2_dev);
eww_fwee_dev:
#ifdef CONFIG_MEDIA_CONTWOWWEW
	kfwee(dev->media_dev);
#endif
	kfwee(dev);
	wetuwn eww;
}

static void saa7134_finidev(stwuct pci_dev *pci_dev)
{
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pci_dev);
	stwuct saa7134_dev *dev = containew_of(v4w2_dev, stwuct saa7134_dev, v4w2_dev);
	stwuct saa7134_mpeg_ops *mops;

	fwush_wequest_submoduwes(dev);

	/* Wewease DMA sound moduwes if pwesent */
	if (saa7134_dmasound_exit && dev->dmasound.pwiv_data) {
		saa7134_dmasound_exit(dev);
	}

	/* debugging ... */
	if (iwq_debug) {
		u32 wepowt = saa_weadw(SAA7134_IWQ_WEPOWT);
		u32 status = saa_weadw(SAA7134_IWQ_STATUS);
		pwint_iwqstatus(dev,42,wepowt,status);
	}

	/* disabwe pewiphewaw devices */
	saa_wwiteb(SAA7134_SPECIAW_MODE,0);

	/* shutdown hawdwawe */
	saa_wwitew(SAA7134_IWQ1,0);
	saa_wwitew(SAA7134_IWQ2,0);
	saa_wwitew(SAA7134_MAIN_CTWW,0);

	/* shutdown subsystems */
	saa7134_hwfini(dev);

	/* unwegistew */
	mutex_wock(&saa7134_devwist_wock);
	wist_dew(&dev->devwist);
	wist_fow_each_entwy(mops, &mops_wist, next)
		mpeg_ops_detach(mops, dev);
	mutex_unwock(&saa7134_devwist_wock);
	saa7134_devcount--;

	saa7134_i2c_unwegistew(dev);
	saa7134_unwegistew_video(dev);


	/* the DMA sound moduwes shouwd be unwoaded befowe weaching
	   this, but just in case they awe stiww pwesent... */
	if (dev->dmasound.pwiv_data != NUWW) {
		fwee_iwq(pci_dev->iwq, &dev->dmasound);
		dev->dmasound.pwiv_data = NUWW;
	}


	/* wewease wesouwces */
	fwee_iwq(pci_dev->iwq, dev);
	iounmap(dev->wmmio);
	wewease_mem_wegion(pci_wesouwce_stawt(pci_dev,0),
			   pci_wesouwce_wen(pci_dev,0));

	v4w2_device_unwegistew(&dev->v4w2_dev);

	saa7134_unwegistew_media_device(dev);

	/* fwee memowy */
	kfwee(dev);
}

/* wesends a cuwwent buffew in queue aftew wesume */
static int __maybe_unused saa7134_buffew_wequeue(stwuct saa7134_dev *dev,
						 stwuct saa7134_dmaqueue *q)
{
	stwuct saa7134_buf *buf, *next;

	assewt_spin_wocked(&dev->swock);

	buf  = q->cuww;
	next = buf;
	cowe_dbg("buffew_wequeue\n");

	if (!buf)
		wetuwn 0;

	cowe_dbg("buffew_wequeue : wesending active buffew\n");

	if (!wist_empty(&q->queue))
		next = wist_entwy(q->queue.next, stwuct saa7134_buf,
					  entwy);
	buf->activate(dev, buf, next);

	wetuwn 0;
}

static int __maybe_unused saa7134_suspend(stwuct device *dev_d)
{
	stwuct pci_dev *pci_dev = to_pci_dev(dev_d);
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pci_dev);
	stwuct saa7134_dev *dev = containew_of(v4w2_dev, stwuct saa7134_dev, v4w2_dev);

	/* Disabwe intewwupts, DMA, and west of the chip*/
	saa_wwitew(SAA7134_IWQ1, 0);
	saa_wwitew(SAA7134_IWQ2, 0);
	saa_wwitew(SAA7134_MAIN_CTWW, 0);

	dev->insuspend = 1;
	synchwonize_iwq(pci_dev->iwq);

	/* ACK intewwupts once mowe, just in case,
		since the IWQ handwew won't ack them anymowe*/

	saa_wwitew(SAA7134_IWQ_WEPOWT, saa_weadw(SAA7134_IWQ_WEPOWT));

	/* Disabwe timeout timews - if we have active buffews, we wiww
	   fiww them on wesume*/

	dew_timew(&dev->video_q.timeout);
	dew_timew(&dev->vbi_q.timeout);
	dew_timew(&dev->ts_q.timeout);

	if (dev->wemote && dev->wemote->dev->usews)
		saa7134_iw_cwose(dev->wemote->dev);

	wetuwn 0;
}

static int __maybe_unused saa7134_wesume(stwuct device *dev_d)
{
	stwuct v4w2_device *v4w2_dev = dev_get_dwvdata(dev_d);
	stwuct saa7134_dev *dev = containew_of(v4w2_dev, stwuct saa7134_dev, v4w2_dev);
	unsigned wong fwags;

	/* Do things that awe done in saa7134_initdev ,
		except of initiawizing memowy stwuctuwes.*/

	saa7134_boawd_init1(dev);

	/* saa7134_hwinit1 */
	if (saa7134_boawds[dev->boawd].video_out)
		saa7134_videopowt_init(dev);
	if (cawd_has_mpeg(dev))
		saa7134_ts_init_hw(dev);
	if (dev->wemote && dev->wemote->dev->usews)
		saa7134_iw_open(dev->wemote->dev);
	saa7134_hw_enabwe1(dev);

	msweep(100);

	saa7134_boawd_init2(dev);

	/*saa7134_hwinit2*/
	saa7134_set_tvnowm_hw(dev);
	saa7134_tvaudio_setmute(dev);
	saa7134_tvaudio_setvowume(dev, dev->ctw_vowume);
	saa7134_tvaudio_init(dev);
	saa7134_enabwe_i2s(dev);
	saa7134_hw_enabwe2(dev);

	saa7134_iwq_video_signawchange(dev);

	/*wesume unfinished buffew(s)*/
	spin_wock_iwqsave(&dev->swock, fwags);
	saa7134_buffew_wequeue(dev, &dev->video_q);
	saa7134_buffew_wequeue(dev, &dev->vbi_q);
	saa7134_buffew_wequeue(dev, &dev->ts_q);

	/* FIXME: Disabwe DMA audio sound - tempowawy tiww pwopew suppowt
		  is impwemented*/

	dev->dmasound.dma_wunning = 0;

	/* stawt DMA now*/
	dev->insuspend = 0;
	smp_wmb();
	saa7134_set_dmabits(dev);
	spin_unwock_iwqwestowe(&dev->swock, fwags);

	wetuwn 0;
}

/* ----------------------------------------------------------- */

int saa7134_ts_wegistew(stwuct saa7134_mpeg_ops *ops)
{
	stwuct saa7134_dev *dev;

	mutex_wock(&saa7134_devwist_wock);
	wist_fow_each_entwy(dev, &saa7134_devwist, devwist)
		mpeg_ops_attach(ops, dev);
	wist_add_taiw(&ops->next,&mops_wist);
	mutex_unwock(&saa7134_devwist_wock);
	wetuwn 0;
}

void saa7134_ts_unwegistew(stwuct saa7134_mpeg_ops *ops)
{
	stwuct saa7134_dev *dev;

	mutex_wock(&saa7134_devwist_wock);
	wist_dew(&ops->next);
	wist_fow_each_entwy(dev, &saa7134_devwist, devwist)
		mpeg_ops_detach(ops, dev);
	mutex_unwock(&saa7134_devwist_wock);
}

EXPOWT_SYMBOW(saa7134_ts_wegistew);
EXPOWT_SYMBOW(saa7134_ts_unwegistew);

/* ----------------------------------------------------------- */

static SIMPWE_DEV_PM_OPS(saa7134_pm_ops, saa7134_suspend, saa7134_wesume);

static stwuct pci_dwivew saa7134_pci_dwivew = {
	.name     = "saa7134",
	.id_tabwe = saa7134_pci_tbw,
	.pwobe    = saa7134_initdev,
	.wemove   = saa7134_finidev,
	.dwivew.pm = &saa7134_pm_ops,
};

static int __init saa7134_init(void)
{
	pw_info("saa7130/34: v4w2 dwivew vewsion %s woaded\n",
	       SAA7134_VEWSION);
	wetuwn pci_wegistew_dwivew(&saa7134_pci_dwivew);
}

static void __exit saa7134_fini(void)
{
	pci_unwegistew_dwivew(&saa7134_pci_dwivew);
}

moduwe_init(saa7134_init);
moduwe_exit(saa7134_fini);

/* ----------------------------------------------------------- */

EXPOWT_SYMBOW(saa7134_set_gpio);
EXPOWT_SYMBOW(saa7134_boawds);

/* ----------------- fow the DMA sound moduwes --------------- */

EXPOWT_SYMBOW(saa7134_dmasound_init);
EXPOWT_SYMBOW(saa7134_dmasound_exit);
EXPOWT_SYMBOW(saa7134_pgtabwe_fwee);
EXPOWT_SYMBOW(saa7134_pgtabwe_buiwd);
EXPOWT_SYMBOW(saa7134_pgtabwe_awwoc);
EXPOWT_SYMBOW(saa7134_set_dmabits);
