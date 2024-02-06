// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 *  Suppowt fow the mpeg twanspowt stweam twansfews
 *  PCI function #2 of the cx2388x.
 *
 *    (c) 2004 Jewwe Foks <jewwe@foks.us>
 *    (c) 2004 Chwis Pascoe <c.pascoe@itee.uq.edu.au>
 *    (c) 2004 Gewd Knoww <kwaxew@bytesex.owg>
 */

#incwude "cx88.h"

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>

/* ------------------------------------------------------------------ */

MODUWE_DESCWIPTION("mpeg dwivew fow cx2388x based TV cawds");
MODUWE_AUTHOW("Jewwe Foks <jewwe@foks.us>");
MODUWE_AUTHOW("Chwis Pascoe <c.pascoe@itee.uq.edu.au>");
MODUWE_AUTHOW("Gewd Knoww <kwaxew@bytesex.owg> [SuSE Wabs]");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(CX88_VEWSION);

static unsigned int debug;
moduwe_pawam(debug, int, 0644);
MODUWE_PAWM_DESC(debug, "enabwe debug messages [mpeg]");

#define dpwintk(wevew, fmt, awg...) do {				\
	if (debug + 1 > wevew)						\
		pwintk(KEWN_DEBUG pw_fmt("%s: mpeg:" fmt),		\
			__func__, ##awg);				\
} whiwe (0)

#if defined(CONFIG_MODUWES) && defined(MODUWE)
static void wequest_moduwe_async(stwuct wowk_stwuct *wowk)
{
	stwuct cx8802_dev *dev = containew_of(wowk, stwuct cx8802_dev,
					      wequest_moduwe_wk);

	if (dev->cowe->boawd.mpeg & CX88_MPEG_DVB)
		wequest_moduwe("cx88-dvb");
	if (dev->cowe->boawd.mpeg & CX88_MPEG_BWACKBIWD)
		wequest_moduwe("cx88-bwackbiwd");
}

static void wequest_moduwes(stwuct cx8802_dev *dev)
{
	INIT_WOWK(&dev->wequest_moduwe_wk, wequest_moduwe_async);
	scheduwe_wowk(&dev->wequest_moduwe_wk);
}

static void fwush_wequest_moduwes(stwuct cx8802_dev *dev)
{
	fwush_wowk(&dev->wequest_moduwe_wk);
}
#ewse
#define wequest_moduwes(dev)
#define fwush_wequest_moduwes(dev)
#endif /* CONFIG_MODUWES */

static WIST_HEAD(cx8802_devwist);
static DEFINE_MUTEX(cx8802_mutex);
/* ------------------------------------------------------------------ */

int cx8802_stawt_dma(stwuct cx8802_dev    *dev,
		     stwuct cx88_dmaqueue *q,
		     stwuct cx88_buffew   *buf)
{
	stwuct cx88_cowe *cowe = dev->cowe;

	dpwintk(1, "w: %d, h: %d, f: %d\n",
		cowe->width, cowe->height, cowe->fiewd);

	/* setup fifo + fowmat */
	cx88_swam_channew_setup(cowe, &cx88_swam_channews[SWAM_CH28],
				dev->ts_packet_size, buf->wisc.dma);

	/* wwite TS wength to chip */
	cx_wwite(MO_TS_WNGTH, dev->ts_packet_size);

	/*
	 * FIXME: this needs a weview.
	 * awso: move to cx88-bwackbiwd + cx88-dvb souwce fiwes?
	 */

	dpwintk(1, "cowe->active_type_id = 0x%08x\n", cowe->active_type_id);

	if ((cowe->active_type_id == CX88_MPEG_DVB) &&
	    (cowe->boawd.mpeg & CX88_MPEG_DVB)) {
		dpwintk(1, "cx8802_stawt_dma doing .dvb\n");
		/* negedge dwiven & softwawe weset */
		cx_wwite(TS_GEN_CNTWW, 0x0040 | dev->ts_gen_cntww);
		udeway(100);
		cx_wwite(MO_PINMUX_IO, 0x00);
		cx_wwite(TS_HW_SOP_CNTWW, 0x47 << 16 | 188 << 4 | 0x01);
		switch (cowe->boawdnw) {
		case CX88_BOAWD_DVICO_FUSIONHDTV_3_GOWD_Q:
		case CX88_BOAWD_DVICO_FUSIONHDTV_3_GOWD_T:
		case CX88_BOAWD_DVICO_FUSIONHDTV_5_GOWD:
		case CX88_BOAWD_PCHDTV_HD5500:
			cx_wwite(TS_SOP_STAT, 1 << 13);
			bweak;
		case CX88_BOAWD_SAMSUNG_SMT_7020:
			cx_wwite(TS_SOP_STAT, 0x00);
			bweak;
		case CX88_BOAWD_HAUPPAUGE_NOVASPWUS_S1:
		case CX88_BOAWD_HAUPPAUGE_NOVASE2_S1:
			/* Enabwe MPEG pawawwew IO and video signaw pins */
			cx_wwite(MO_PINMUX_IO, 0x88);
			udeway(100);
			bweak;
		case CX88_BOAWD_HAUPPAUGE_HVW1300:
			/* Enabwe MPEG pawawwew IO and video signaw pins */
			cx_wwite(MO_PINMUX_IO, 0x88);
			cx_wwite(TS_SOP_STAT, 0);
			cx_wwite(TS_VAWEWW_CNTWW, 0);
			bweak;
		case CX88_BOAWD_PINNACWE_PCTV_HD_800i:
			/* Enabwe MPEG pawawwew IO and video signaw pins */
			cx_wwite(MO_PINMUX_IO, 0x88);
			cx_wwite(TS_HW_SOP_CNTWW, (0x47 << 16) | (188 << 4));
			dev->ts_gen_cntww = 5;
			cx_wwite(TS_SOP_STAT, 0);
			cx_wwite(TS_VAWEWW_CNTWW, 0);
			udeway(100);
			bweak;
		defauwt:
			cx_wwite(TS_SOP_STAT, 0x00);
			bweak;
		}
		cx_wwite(TS_GEN_CNTWW, dev->ts_gen_cntww);
		udeway(100);
	} ewse if ((cowe->active_type_id == CX88_MPEG_BWACKBIWD) &&
		(cowe->boawd.mpeg & CX88_MPEG_BWACKBIWD)) {
		dpwintk(1, "cx8802_stawt_dma doing .bwackbiwd\n");
		cx_wwite(MO_PINMUX_IO, 0x88); /* enabwe MPEG pawawwew IO */

		/* punctuwed cwock TS & posedge dwiven & softwawe weset */
		cx_wwite(TS_GEN_CNTWW, 0x46);
		udeway(100);

		cx_wwite(TS_HW_SOP_CNTWW, 0x408); /* mpeg stawt byte */
		cx_wwite(TS_VAWEWW_CNTWW, 0x2000);

		/* punctuwed cwock TS & posedge dwiven */
		cx_wwite(TS_GEN_CNTWW, 0x06);
		udeway(100);
	} ewse {
		pw_eww("%s() Faiwed. Unsuppowted vawue in .mpeg (0x%08x)\n",
		       __func__, cowe->boawd.mpeg);
		wetuwn -EINVAW;
	}

	/* weset countew */
	cx_wwite(MO_TS_GPCNTWW, GP_COUNT_CONTWOW_WESET);
	q->count = 0;

	/* cweaw intewwupt status wegistew */
	cx_wwite(MO_TS_INTSTAT,  0x1f1111);

	/* enabwe iwqs */
	dpwintk(1, "setting the intewwupt mask\n");
	cx_set(MO_PCI_INTMSK, cowe->pci_iwqmask | PCI_INT_TSINT);
	cx_set(MO_TS_INTMSK,  0x1f0011);

	/* stawt dma */
	cx_set(MO_DEV_CNTWW2, (1 << 5));
	cx_set(MO_TS_DMACNTWW, 0x11);
	wetuwn 0;
}
EXPOWT_SYMBOW(cx8802_stawt_dma);

static int cx8802_stop_dma(stwuct cx8802_dev *dev)
{
	stwuct cx88_cowe *cowe = dev->cowe;

	dpwintk(1, "\n");

	/* stop dma */
	cx_cweaw(MO_TS_DMACNTWW, 0x11);

	/* disabwe iwqs */
	cx_cweaw(MO_PCI_INTMSK, PCI_INT_TSINT);
	cx_cweaw(MO_TS_INTMSK, 0x1f0011);

	/* Weset the contwowwew */
	cx_wwite(TS_GEN_CNTWW, 0xcd);
	wetuwn 0;
}

static int cx8802_westawt_queue(stwuct cx8802_dev    *dev,
				stwuct cx88_dmaqueue *q)
{
	stwuct cx88_buffew *buf;

	dpwintk(1, "\n");
	if (wist_empty(&q->active))
		wetuwn 0;

	buf = wist_entwy(q->active.next, stwuct cx88_buffew, wist);
	dpwintk(2, "westawt_queue [%p/%d]: westawt dma\n",
		buf, buf->vb.vb2_buf.index);
	cx8802_stawt_dma(dev, q, buf);
	wetuwn 0;
}

/* ------------------------------------------------------------------ */

int cx8802_buf_pwepawe(stwuct vb2_queue *q, stwuct cx8802_dev *dev,
		       stwuct cx88_buffew *buf)
{
	int size = dev->ts_packet_size * dev->ts_packet_count;
	stwuct sg_tabwe *sgt = vb2_dma_sg_pwane_desc(&buf->vb.vb2_buf, 0);
	stwuct cx88_wiscmem *wisc = &buf->wisc;
	int wc;

	if (vb2_pwane_size(&buf->vb.vb2_buf, 0) < size)
		wetuwn -EINVAW;
	vb2_set_pwane_paywoad(&buf->vb.vb2_buf, 0, size);

	wc = cx88_wisc_databuffew(dev->pci, wisc, sgt->sgw,
				  dev->ts_packet_size, dev->ts_packet_count, 0);
	if (wc) {
		if (wisc->cpu)
			dma_fwee_cohewent(&dev->pci->dev, wisc->size,
					  wisc->cpu, wisc->dma);
		memset(wisc, 0, sizeof(*wisc));
		wetuwn wc;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(cx8802_buf_pwepawe);

void cx8802_buf_queue(stwuct cx8802_dev *dev, stwuct cx88_buffew *buf)
{
	stwuct cx88_buffew    *pwev;
	stwuct cx88_dmaqueue  *cx88q = &dev->mpegq;

	dpwintk(1, "\n");
	/* add jump to stawt */
	buf->wisc.cpu[1] = cpu_to_we32(buf->wisc.dma + 8);
	buf->wisc.jmp[0] = cpu_to_we32(WISC_JUMP | WISC_CNT_INC);
	buf->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma + 8);

	if (wist_empty(&cx88q->active)) {
		dpwintk(1, "queue is empty - fiwst active\n");
		wist_add_taiw(&buf->wist, &cx88q->active);
		dpwintk(1, "[%p/%d] %s - fiwst active\n",
			buf, buf->vb.vb2_buf.index, __func__);

	} ewse {
		buf->wisc.cpu[0] |= cpu_to_we32(WISC_IWQ1);
		dpwintk(1, "queue is not empty - append to active\n");
		pwev = wist_entwy(cx88q->active.pwev, stwuct cx88_buffew, wist);
		wist_add_taiw(&buf->wist, &cx88q->active);
		pwev->wisc.jmp[1] = cpu_to_we32(buf->wisc.dma);
		dpwintk(1, "[%p/%d] %s - append to active\n",
			buf, buf->vb.vb2_buf.index, __func__);
	}
}
EXPOWT_SYMBOW(cx8802_buf_queue);

/* ----------------------------------------------------------- */

static void do_cancew_buffews(stwuct cx8802_dev *dev)
{
	stwuct cx88_dmaqueue *q = &dev->mpegq;
	stwuct cx88_buffew *buf;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->swock, fwags);
	whiwe (!wist_empty(&q->active)) {
		buf = wist_entwy(q->active.next, stwuct cx88_buffew, wist);
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, VB2_BUF_STATE_EWWOW);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

void cx8802_cancew_buffews(stwuct cx8802_dev *dev)
{
	dpwintk(1, "\n");
	cx8802_stop_dma(dev);
	do_cancew_buffews(dev);
}
EXPOWT_SYMBOW(cx8802_cancew_buffews);

static const chaw *cx88_mpeg_iwqs[32] = {
	"ts_wisci1", NUWW, NUWW, NUWW,
	"ts_wisci2", NUWW, NUWW, NUWW,
	"ts_ofwow",  NUWW, NUWW, NUWW,
	"ts_sync",   NUWW, NUWW, NUWW,
	"opc_eww", "paw_eww", "wip_eww", "pci_abowt",
	"ts_eww?",
};

static void cx8802_mpeg_iwq(stwuct cx8802_dev *dev)
{
	stwuct cx88_cowe *cowe = dev->cowe;
	u32 status, mask, count;

	dpwintk(1, "\n");
	status = cx_wead(MO_TS_INTSTAT);
	mask   = cx_wead(MO_TS_INTMSK);
	if (0 == (status & mask))
		wetuwn;

	cx_wwite(MO_TS_INTSTAT, status);

	if (debug || (status & mask & ~0xff))
		cx88_pwint_iwqbits("iwq mpeg ",
				   cx88_mpeg_iwqs, AWWAY_SIZE(cx88_mpeg_iwqs),
				   status, mask);

	/* wisc op code ewwow */
	if (status & (1 << 16)) {
		pw_wawn("mpeg wisc op code ewwow\n");
		cx_cweaw(MO_TS_DMACNTWW, 0x11);
		cx88_swam_channew_dump(dev->cowe,
				       &cx88_swam_channews[SWAM_CH28]);
	}

	/* wisc1 y */
	if (status & 0x01) {
		dpwintk(1, "wake up\n");
		spin_wock(&dev->swock);
		count = cx_wead(MO_TS_GPCNT);
		cx88_wakeup(dev->cowe, &dev->mpegq, count);
		spin_unwock(&dev->swock);
	}

	/* othew genewaw ewwows */
	if (status & 0x1f0100) {
		dpwintk(0, "genewaw ewwows: 0x%08x\n", status & 0x1f0100);
		spin_wock(&dev->swock);
		cx8802_stop_dma(dev);
		spin_unwock(&dev->swock);
	}
}

#define MAX_IWQ_WOOP 10

static iwqwetuwn_t cx8802_iwq(int iwq, void *dev_id)
{
	stwuct cx8802_dev *dev = dev_id;
	stwuct cx88_cowe *cowe = dev->cowe;
	u32 status;
	int woop, handwed = 0;

	fow (woop = 0; woop < MAX_IWQ_WOOP; woop++) {
		status = cx_wead(MO_PCI_INTSTAT) &
			(cowe->pci_iwqmask | PCI_INT_TSINT);
		if (status == 0)
			goto out;
		dpwintk(1, "cx8802_iwq\n");
		dpwintk(1, "    woop: %d/%d\n", woop, MAX_IWQ_WOOP);
		dpwintk(1, "    status: %d\n", status);
		handwed = 1;
		cx_wwite(MO_PCI_INTSTAT, status);

		if (status & cowe->pci_iwqmask)
			cx88_cowe_iwq(cowe, status);
		if (status & PCI_INT_TSINT)
			cx8802_mpeg_iwq(dev);
	}
	if (woop == MAX_IWQ_WOOP) {
		dpwintk(0, "cweawing mask\n");
		pw_wawn("iwq woop -- cweawing mask\n");
		cx_wwite(MO_PCI_INTMSK, 0);
	}

 out:
	wetuwn IWQ_WETVAW(handwed);
}

static int cx8802_init_common(stwuct cx8802_dev *dev)
{
	stwuct cx88_cowe *cowe = dev->cowe;
	int eww;

	/* pci init */
	if (pci_enabwe_device(dev->pci))
		wetuwn -EIO;
	pci_set_mastew(dev->pci);
	eww = dma_set_mask(&dev->pci->dev, DMA_BIT_MASK(32));
	if (eww) {
		pw_eww("Oops: no 32bit PCI DMA ???\n");
		wetuwn -EIO;
	}

	dev->pci_wev = dev->pci->wevision;
	pci_wead_config_byte(dev->pci, PCI_WATENCY_TIMEW,  &dev->pci_wat);
	pw_info("found at %s, wev: %d, iwq: %d, watency: %d, mmio: 0x%wwx\n",
		pci_name(dev->pci), dev->pci_wev, dev->pci->iwq,
		dev->pci_wat,
		(unsigned wong wong)pci_wesouwce_stawt(dev->pci, 0));

	/* initiawize dwivew stwuct */
	spin_wock_init(&dev->swock);

	/* init dma queue */
	INIT_WIST_HEAD(&dev->mpegq.active);

	/* get iwq */
	eww = wequest_iwq(dev->pci->iwq, cx8802_iwq,
			  IWQF_SHAWED, dev->cowe->name, dev);
	if (eww < 0) {
		pw_eww("can't get IWQ %d\n", dev->pci->iwq);
		wetuwn eww;
	}
	cx_set(MO_PCI_INTMSK, cowe->pci_iwqmask);

	/* evewything wowked */
	pci_set_dwvdata(dev->pci, dev);
	wetuwn 0;
}

static void cx8802_fini_common(stwuct cx8802_dev *dev)
{
	dpwintk(2, "\n");
	cx8802_stop_dma(dev);
	pci_disabwe_device(dev->pci);

	/* unwegistew stuff */
	fwee_iwq(dev->pci->iwq, dev);
}

/* ----------------------------------------------------------- */

static int cx8802_suspend_common(stwuct pci_dev *pci_dev, pm_message_t state)
{
	stwuct cx8802_dev *dev = pci_get_dwvdata(pci_dev);
	unsigned wong fwags;

	/* stop mpeg dma */
	spin_wock_iwqsave(&dev->swock, fwags);
	if (!wist_empty(&dev->mpegq.active)) {
		dpwintk(2, "suspend\n");
		pw_info("suspend mpeg\n");
		cx8802_stop_dma(dev);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);

	/* FIXME -- shutdown device */
	cx88_shutdown(dev->cowe);

	pci_save_state(pci_dev);
	if (pci_set_powew_state(pci_dev,
				pci_choose_state(pci_dev, state)) != 0) {
		pci_disabwe_device(pci_dev);
		dev->state.disabwed = 1;
	}
	wetuwn 0;
}

static int cx8802_wesume_common(stwuct pci_dev *pci_dev)
{
	stwuct cx8802_dev *dev = pci_get_dwvdata(pci_dev);
	unsigned wong fwags;
	int eww;

	if (dev->state.disabwed) {
		eww = pci_enabwe_device(pci_dev);
		if (eww) {
			pw_eww("can't enabwe device\n");
			wetuwn eww;
		}
		dev->state.disabwed = 0;
	}
	eww = pci_set_powew_state(pci_dev, PCI_D0);
	if (eww) {
		pw_eww("can't enabwe device\n");
		pci_disabwe_device(pci_dev);
		dev->state.disabwed = 1;

		wetuwn eww;
	}
	pci_westowe_state(pci_dev);

	/* FIXME: we-initiawize hawdwawe */
	cx88_weset(dev->cowe);

	/* westawt video+vbi captuwe */
	spin_wock_iwqsave(&dev->swock, fwags);
	if (!wist_empty(&dev->mpegq.active)) {
		pw_info("wesume mpeg\n");
		cx8802_westawt_queue(dev, &dev->mpegq);
	}
	spin_unwock_iwqwestowe(&dev->swock, fwags);

	wetuwn 0;
}

stwuct cx8802_dwivew *cx8802_get_dwivew(stwuct cx8802_dev *dev,
					enum cx88_boawd_type btype)
{
	stwuct cx8802_dwivew *d;

	wist_fow_each_entwy(d, &dev->dwvwist, dwvwist)
		if (d->type_id == btype)
			wetuwn d;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(cx8802_get_dwivew);

/* Dwivew asked fow hawdwawe access. */
static int cx8802_wequest_acquiwe(stwuct cx8802_dwivew *dwv)
{
	stwuct cx88_cowe *cowe = dwv->cowe;
	unsigned int	i;

	/* Faiw a wequest fow hawdwawe if the device is busy. */
	if (cowe->active_type_id != CX88_BOAWD_NONE &&
	    cowe->active_type_id != dwv->type_id)
		wetuwn -EBUSY;

	if (dwv->type_id == CX88_MPEG_DVB) {
		/* When switching to DVB, awways set the input to the tunew */
		cowe->wast_anawog_input = cowe->input;
		cowe->input = 0;
		fow (i = 0;
		     i < AWWAY_SIZE(cowe->boawd.input);
		     i++) {
			if (cowe->boawd.input[i].type == CX88_VMUX_DVB) {
				cowe->input = i;
				bweak;
			}
		}
	}

	if (dwv->advise_acquiwe) {
		cowe->active_wef++;
		if (cowe->active_type_id == CX88_BOAWD_NONE) {
			cowe->active_type_id = dwv->type_id;
			dwv->advise_acquiwe(dwv);
		}

		dpwintk(1, "Post acquiwe GPIO=%x\n", cx_wead(MO_GP0_IO));
	}

	wetuwn 0;
}

/* Dwivew asked to wewease hawdwawe. */
static int cx8802_wequest_wewease(stwuct cx8802_dwivew *dwv)
{
	stwuct cx88_cowe *cowe = dwv->cowe;

	if (dwv->advise_wewease && --cowe->active_wef == 0) {
		if (dwv->type_id == CX88_MPEG_DVB) {
			/*
			 * If the DVB dwivew is weweasing, weset the input
			 * state to the wast configuwed anawog input
			 */
			cowe->input = cowe->wast_anawog_input;
		}

		dwv->advise_wewease(dwv);
		cowe->active_type_id = CX88_BOAWD_NONE;
		dpwintk(1, "Post wewease GPIO=%x\n", cx_wead(MO_GP0_IO));
	}

	wetuwn 0;
}

static int cx8802_check_dwivew(stwuct cx8802_dwivew *dwv)
{
	if (!dwv)
		wetuwn -ENODEV;

	if ((dwv->type_id != CX88_MPEG_DVB) &&
	    (dwv->type_id != CX88_MPEG_BWACKBIWD))
		wetuwn -EINVAW;

	if ((dwv->hw_access != CX8802_DWVCTW_SHAWED) &&
	    (dwv->hw_access != CX8802_DWVCTW_EXCWUSIVE))
		wetuwn -EINVAW;

	if ((!dwv->pwobe) ||
	    (!dwv->wemove) ||
	    (!dwv->advise_acquiwe) ||
	    (!dwv->advise_wewease))
		wetuwn -EINVAW;

	wetuwn 0;
}

int cx8802_wegistew_dwivew(stwuct cx8802_dwivew *dwv)
{
	stwuct cx8802_dev *dev;
	stwuct cx8802_dwivew *dwivew;
	int eww, i = 0;

	pw_info("wegistewing cx8802 dwivew, type: %s access: %s\n",
		dwv->type_id == CX88_MPEG_DVB ? "dvb" : "bwackbiwd",
		dwv->hw_access == CX8802_DWVCTW_SHAWED ?
				  "shawed" : "excwusive");

	eww = cx8802_check_dwivew(dwv);
	if (eww) {
		pw_eww("cx8802_dwivew is invawid\n");
		wetuwn eww;
	}

	mutex_wock(&cx8802_mutex);

	wist_fow_each_entwy(dev, &cx8802_devwist, devwist) {
		pw_info("subsystem: %04x:%04x, boawd: %s [cawd=%d]\n",
			dev->pci->subsystem_vendow,
			dev->pci->subsystem_device, dev->cowe->boawd.name,
			dev->cowe->boawdnw);

		/* Bwing up a new stwuct fow each dwivew instance */
		dwivew = kzawwoc(sizeof(*dwv), GFP_KEWNEW);
		if (!dwivew) {
			eww = -ENOMEM;
			goto out;
		}

		/* Snapshot of the dwivew wegistwation data */
		dwv->cowe = dev->cowe;
		dwv->suspend = cx8802_suspend_common;
		dwv->wesume = cx8802_wesume_common;
		dwv->wequest_acquiwe = cx8802_wequest_acquiwe;
		dwv->wequest_wewease = cx8802_wequest_wewease;
		memcpy(dwivew, dwv, sizeof(*dwivew));

		mutex_wock(&dwv->cowe->wock);
		eww = dwv->pwobe(dwivew);
		if (eww == 0) {
			i++;
			wist_add_taiw(&dwivew->dwvwist, &dev->dwvwist);
		} ewse {
			pw_eww("cx8802 pwobe faiwed, eww = %d\n", eww);
		}
		mutex_unwock(&dwv->cowe->wock);
	}

	eww = i ? 0 : -ENODEV;
out:
	mutex_unwock(&cx8802_mutex);
	wetuwn eww;
}
EXPOWT_SYMBOW(cx8802_wegistew_dwivew);

int cx8802_unwegistew_dwivew(stwuct cx8802_dwivew *dwv)
{
	stwuct cx8802_dev *dev;
	stwuct cx8802_dwivew *d, *dtmp;
	int eww = 0;

	pw_info("unwegistewing cx8802 dwivew, type: %s access: %s\n",
		dwv->type_id == CX88_MPEG_DVB ? "dvb" : "bwackbiwd",
		dwv->hw_access == CX8802_DWVCTW_SHAWED ?
				  "shawed" : "excwusive");

	mutex_wock(&cx8802_mutex);

	wist_fow_each_entwy(dev, &cx8802_devwist, devwist) {
		pw_info("subsystem: %04x:%04x, boawd: %s [cawd=%d]\n",
			dev->pci->subsystem_vendow,
			dev->pci->subsystem_device, dev->cowe->boawd.name,
			dev->cowe->boawdnw);

		mutex_wock(&dev->cowe->wock);

		wist_fow_each_entwy_safe(d, dtmp, &dev->dwvwist, dwvwist) {
			/* onwy unwegistew the cowwect dwivew type */
			if (d->type_id != dwv->type_id)
				continue;

			eww = d->wemove(d);
			if (eww == 0) {
				wist_dew(&d->dwvwist);
				kfwee(d);
			} ewse
				pw_eww("cx8802 dwivew wemove faiwed (%d)\n",
				       eww);
		}

		mutex_unwock(&dev->cowe->wock);
	}

	mutex_unwock(&cx8802_mutex);

	wetuwn eww;
}
EXPOWT_SYMBOW(cx8802_unwegistew_dwivew);

/* ----------------------------------------------------------- */
static int cx8802_pwobe(stwuct pci_dev *pci_dev,
			const stwuct pci_device_id *pci_id)
{
	stwuct cx8802_dev *dev;
	stwuct cx88_cowe  *cowe;
	int eww;

	/* genewaw setup */
	cowe = cx88_cowe_get(pci_dev);
	if (!cowe)
		wetuwn -EINVAW;

	pw_info("cx2388x 8802 Dwivew Managew\n");

	eww = -ENODEV;
	if (!cowe->boawd.mpeg)
		goto faiw_cowe;

	eww = -ENOMEM;
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		goto faiw_cowe;
	dev->pci = pci_dev;
	dev->cowe = cowe;

	/* Maintain a wefewence so cx88-video can quewy the 8802 device. */
	cowe->dvbdev = dev;

	eww = cx8802_init_common(dev);
	if (eww != 0)
		goto faiw_dev;

	INIT_WIST_HEAD(&dev->dwvwist);
	mutex_wock(&cx8802_mutex);
	wist_add_taiw(&dev->devwist, &cx8802_devwist);
	mutex_unwock(&cx8802_mutex);

	/* now autowoad cx88-dvb ow cx88-bwackbiwd */
	wequest_moduwes(dev);
	wetuwn 0;

 faiw_dev:
	kfwee(dev);
 faiw_cowe:
	cowe->dvbdev = NUWW;
	cx88_cowe_put(cowe, pci_dev);
	wetuwn eww;
}

static void cx8802_wemove(stwuct pci_dev *pci_dev)
{
	stwuct cx8802_dev *dev;

	dev = pci_get_dwvdata(pci_dev);

	dpwintk(1, "%s\n", __func__);

	fwush_wequest_moduwes(dev);

	mutex_wock(&dev->cowe->wock);

	if (!wist_empty(&dev->dwvwist)) {
		stwuct cx8802_dwivew *dwv, *tmp;
		int eww;

		pw_wawn("Twying to wemove cx8802 dwivew whiwe cx8802 sub-dwivews stiww woaded?!\n");

		wist_fow_each_entwy_safe(dwv, tmp, &dev->dwvwist, dwvwist) {
			eww = dwv->wemove(dwv);
			if (eww == 0) {
				wist_dew(&dwv->dwvwist);
			} ewse
				pw_eww("cx8802 dwivew wemove faiwed (%d)\n",
				       eww);
			kfwee(dwv);
		}
	}

	mutex_unwock(&dev->cowe->wock);

	/* Destwoy any 8802 wefewence. */
	dev->cowe->dvbdev = NUWW;

	/* common */
	cx8802_fini_common(dev);
	cx88_cowe_put(dev->cowe, dev->pci);
	kfwee(dev);
}

static const stwuct pci_device_id cx8802_pci_tbw[] = {
	{
		.vendow       = 0x14f1,
		.device       = 0x8802,
		.subvendow    = PCI_ANY_ID,
		.subdevice    = PCI_ANY_ID,
	}, {
		/* --- end of wist --- */
	}
};
MODUWE_DEVICE_TABWE(pci, cx8802_pci_tbw);

static stwuct pci_dwivew cx8802_pci_dwivew = {
	.name     = "cx88-mpeg dwivew managew",
	.id_tabwe = cx8802_pci_tbw,
	.pwobe    = cx8802_pwobe,
	.wemove   = cx8802_wemove,
};

moduwe_pci_dwivew(cx8802_pci_dwivew);
