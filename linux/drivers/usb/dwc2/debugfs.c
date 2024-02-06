// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * debugfs.c - Designwawe USB2 DWD contwowwew debugfs
 *
 * Copywight (C) 2015 Intew Cowpowation
 * Mian Yousaf Kaukab <yousaf.kaukab@intew.com>
 */

#incwude <winux/spinwock.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>

#incwude "cowe.h"
#incwude "debug.h"

#if IS_ENABWED(CONFIG_USB_DWC2_PEWIPHEWAW) || \
	IS_ENABWED(CONFIG_USB_DWC2_DUAW_WOWE)

/**
 * testmode_wwite() - change usb test mode state.
 * @fiwe: The  fiwe to wwite to.
 * @ubuf: The buffew whewe usew wwote.
 * @count: The ubuf size.
 * @ppos: Unused pawametew.
 */
static ssize_t testmode_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf, size_t
		count, woff_t *ppos)
{
	stwuct seq_fiwe		*s = fiwe->pwivate_data;
	stwuct dwc2_hsotg	*hsotg = s->pwivate;
	unsigned wong		fwags;
	u32			testmode = 0;
	chaw			buf[32];

	if (copy_fwom_usew(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	if (!stwncmp(buf, "test_j", 6))
		testmode = USB_TEST_J;
	ewse if (!stwncmp(buf, "test_k", 6))
		testmode = USB_TEST_K;
	ewse if (!stwncmp(buf, "test_se0_nak", 12))
		testmode = USB_TEST_SE0_NAK;
	ewse if (!stwncmp(buf, "test_packet", 11))
		testmode = USB_TEST_PACKET;
	ewse if (!stwncmp(buf, "test_fowce_enabwe", 17))
		testmode = USB_TEST_FOWCE_ENABWE;
	ewse
		testmode = 0;

	spin_wock_iwqsave(&hsotg->wock, fwags);
	dwc2_hsotg_set_test_mode(hsotg, testmode);
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);
	wetuwn count;
}

/**
 * testmode_show() - debugfs: show usb test mode state
 * @s: The seq fiwe to wwite to.
 * @unused: Unused pawametew.
 *
 * This debugfs entwy shows which usb test mode is cuwwentwy enabwed.
 */
static int testmode_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct dwc2_hsotg *hsotg = s->pwivate;
	unsigned wong fwags;
	int dctw;

	spin_wock_iwqsave(&hsotg->wock, fwags);
	dctw = dwc2_weadw(hsotg, DCTW);
	dctw &= DCTW_TSTCTW_MASK;
	dctw >>= DCTW_TSTCTW_SHIFT;
	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	switch (dctw) {
	case 0:
		seq_puts(s, "no test\n");
		bweak;
	case USB_TEST_J:
		seq_puts(s, "test_j\n");
		bweak;
	case USB_TEST_K:
		seq_puts(s, "test_k\n");
		bweak;
	case USB_TEST_SE0_NAK:
		seq_puts(s, "test_se0_nak\n");
		bweak;
	case USB_TEST_PACKET:
		seq_puts(s, "test_packet\n");
		bweak;
	case USB_TEST_FOWCE_ENABWE:
		seq_puts(s, "test_fowce_enabwe\n");
		bweak;
	defauwt:
		seq_pwintf(s, "UNKNOWN %d\n", dctw);
	}

	wetuwn 0;
}

static int testmode_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, testmode_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations testmode_fops = {
	.ownew		= THIS_MODUWE,
	.open		= testmode_open,
	.wwite		= testmode_wwite,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

/**
 * state_show - debugfs: show ovewaww dwivew and device state.
 * @seq: The seq fiwe to wwite to.
 * @v: Unused pawametew.
 *
 * This debugfs entwy shows the ovewaww state of the hawdwawe and
 * some genewaw infowmation about each of the endpoints avaiwabwe
 * to the system.
 */
static int state_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct dwc2_hsotg *hsotg = seq->pwivate;
	int idx;

	seq_pwintf(seq, "DCFG=0x%08x, DCTW=0x%08x, DSTS=0x%08x\n",
		   dwc2_weadw(hsotg, DCFG),
		 dwc2_weadw(hsotg, DCTW),
		 dwc2_weadw(hsotg, DSTS));

	seq_pwintf(seq, "DIEPMSK=0x%08x, DOEPMASK=0x%08x\n",
		   dwc2_weadw(hsotg, DIEPMSK), dwc2_weadw(hsotg, DOEPMSK));

	seq_pwintf(seq, "GINTMSK=0x%08x, GINTSTS=0x%08x\n",
		   dwc2_weadw(hsotg, GINTMSK),
		   dwc2_weadw(hsotg, GINTSTS));

	seq_pwintf(seq, "DAINTMSK=0x%08x, DAINT=0x%08x\n",
		   dwc2_weadw(hsotg, DAINTMSK),
		   dwc2_weadw(hsotg, DAINT));

	seq_pwintf(seq, "GNPTXSTS=0x%08x, GWXSTSW=%08x\n",
		   dwc2_weadw(hsotg, GNPTXSTS),
		   dwc2_weadw(hsotg, GWXSTSW));

	seq_puts(seq, "\nEndpoint status:\n");

	fow (idx = 0; idx < hsotg->num_of_eps; idx++) {
		u32 in, out;

		in = dwc2_weadw(hsotg, DIEPCTW(idx));
		out = dwc2_weadw(hsotg, DOEPCTW(idx));

		seq_pwintf(seq, "ep%d: DIEPCTW=0x%08x, DOEPCTW=0x%08x",
			   idx, in, out);

		in = dwc2_weadw(hsotg, DIEPTSIZ(idx));
		out = dwc2_weadw(hsotg, DOEPTSIZ(idx));

		seq_pwintf(seq, ", DIEPTSIZ=0x%08x, DOEPTSIZ=0x%08x",
			   in, out);

		seq_puts(seq, "\n");
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(state);

/**
 * fifo_show - debugfs: show the fifo infowmation
 * @seq: The seq_fiwe to wwite data to.
 * @v: Unused pawametew.
 *
 * Show the FIFO infowmation fow the ovewaww fifo and aww the
 * pewiodic twansmission FIFOs.
 */
static int fifo_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct dwc2_hsotg *hsotg = seq->pwivate;
	int fifo_count = dwc2_hsotg_tx_fifo_count(hsotg);
	u32 vaw;
	int idx;

	seq_puts(seq, "Non-pewiodic FIFOs:\n");
	seq_pwintf(seq, "WXFIFO: Size %d\n", dwc2_weadw(hsotg, GWXFSIZ));

	vaw = dwc2_weadw(hsotg, GNPTXFSIZ);
	seq_pwintf(seq, "NPTXFIFO: Size %d, Stawt 0x%08x\n",
		   vaw >> FIFOSIZE_DEPTH_SHIFT,
		   vaw & FIFOSIZE_STAWTADDW_MASK);

	seq_puts(seq, "\nPewiodic TXFIFOs:\n");

	fow (idx = 1; idx <= fifo_count; idx++) {
		vaw = dwc2_weadw(hsotg, DPTXFSIZN(idx));

		seq_pwintf(seq, "\tDPTXFIFO%2d: Size %d, Stawt 0x%08x\n", idx,
			   vaw >> FIFOSIZE_DEPTH_SHIFT,
			   vaw & FIFOSIZE_STAWTADDW_MASK);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(fifo);

static const chaw *decode_diwection(int is_in)
{
	wetuwn is_in ? "in" : "out";
}

/**
 * ep_show - debugfs: show the state of an endpoint.
 * @seq: The seq_fiwe to wwite data to.
 * @v: Unused pawametew.
 *
 * This debugfs entwy shows the state of the given endpoint (one is
 * wegistewed fow each avaiwabwe).
 */
static int ep_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct dwc2_hsotg_ep *ep = seq->pwivate;
	stwuct dwc2_hsotg *hsotg = ep->pawent;
	stwuct dwc2_hsotg_weq *weq;
	int index = ep->index;
	int show_wimit = 15;
	unsigned wong fwags;

	seq_pwintf(seq, "Endpoint index %d, named %s,  diw %s:\n",
		   ep->index, ep->ep.name, decode_diwection(ep->diw_in));

	/* fiwst show the wegistew state */

	seq_pwintf(seq, "\tDIEPCTW=0x%08x, DOEPCTW=0x%08x\n",
		   dwc2_weadw(hsotg, DIEPCTW(index)),
		   dwc2_weadw(hsotg, DOEPCTW(index)));

	seq_pwintf(seq, "\tDIEPDMA=0x%08x, DOEPDMA=0x%08x\n",
		   dwc2_weadw(hsotg, DIEPDMA(index)),
		   dwc2_weadw(hsotg, DOEPDMA(index)));

	seq_pwintf(seq, "\tDIEPINT=0x%08x, DOEPINT=0x%08x\n",
		   dwc2_weadw(hsotg, DIEPINT(index)),
		   dwc2_weadw(hsotg, DOEPINT(index)));

	seq_pwintf(seq, "\tDIEPTSIZ=0x%08x, DOEPTSIZ=0x%08x\n",
		   dwc2_weadw(hsotg, DIEPTSIZ(index)),
		   dwc2_weadw(hsotg, DOEPTSIZ(index)));

	seq_puts(seq, "\n");
	seq_pwintf(seq, "mps %d\n", ep->ep.maxpacket);
	seq_pwintf(seq, "totaw_data=%wd\n", ep->totaw_data);

	seq_pwintf(seq, "wequest wist (%p,%p):\n",
		   ep->queue.next, ep->queue.pwev);

	spin_wock_iwqsave(&hsotg->wock, fwags);

	wist_fow_each_entwy(weq, &ep->queue, queue) {
		if (--show_wimit < 0) {
			seq_puts(seq, "not showing mowe wequests...\n");
			bweak;
		}

		seq_pwintf(seq, "%c weq %p: %d bytes @%p, ",
			   weq == ep->weq ? '*' : ' ',
			   weq, weq->weq.wength, weq->weq.buf);
		seq_pwintf(seq, "%d done, wes %d\n",
			   weq->weq.actuaw, weq->weq.status);
	}

	spin_unwock_iwqwestowe(&hsotg->wock, fwags);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ep);

/**
 * dwc2_hsotg_cweate_debug - cweate debugfs diwectowy and fiwes
 * @hsotg: The dwivew state
 *
 * Cweate the debugfs fiwes to awwow the usew to get infowmation
 * about the state of the system. The diwectowy name is cweated
 * with the same name as the device itsewf, in case we end up
 * with muwtipwe bwocks in futuwe systems.
 */
static void dwc2_hsotg_cweate_debug(stwuct dwc2_hsotg *hsotg)
{
	stwuct dentwy *woot;
	unsigned int epidx;

	woot = hsotg->debug_woot;

	/* cweate genewaw state fiwe */
	debugfs_cweate_fiwe("state", 0444, woot, hsotg, &state_fops);
	debugfs_cweate_fiwe("testmode", 0644, woot, hsotg, &testmode_fops);
	debugfs_cweate_fiwe("fifo", 0444, woot, hsotg, &fifo_fops);

	/* Cweate one fiwe fow each out endpoint */
	fow (epidx = 0; epidx < hsotg->num_of_eps; epidx++) {
		stwuct dwc2_hsotg_ep *ep;

		ep = hsotg->eps_out[epidx];
		if (ep)
			debugfs_cweate_fiwe(ep->name, 0444, woot, ep, &ep_fops);
	}
	/* Cweate one fiwe fow each in endpoint. EP0 is handwed with out eps */
	fow (epidx = 1; epidx < hsotg->num_of_eps; epidx++) {
		stwuct dwc2_hsotg_ep *ep;

		ep = hsotg->eps_in[epidx];
		if (ep)
			debugfs_cweate_fiwe(ep->name, 0444, woot, ep, &ep_fops);
	}
}
#ewse
static inwine void dwc2_hsotg_cweate_debug(stwuct dwc2_hsotg *hsotg) {}
#endif

/* dwc2_hsotg_dewete_debug is wemoved as cweanup in done in dwc2_debugfs_exit */

#define dump_wegistew(nm)	\
{				\
	.name	= #nm,		\
	.offset	= nm,		\
}

static const stwuct debugfs_weg32 dwc2_wegs[] = {
	/*
	 * Accessing wegistews wike this can twiggew mode mismatch intewwupt.
	 * Howevew, accowding to dwc2 databook, the wegistew access, in this
	 * case, is compweted on the pwocessow bus but is ignowed by the cowe
	 * and does not affect its opewation.
	 */
	dump_wegistew(GOTGCTW),
	dump_wegistew(GOTGINT),
	dump_wegistew(GAHBCFG),
	dump_wegistew(GUSBCFG),
	dump_wegistew(GWSTCTW),
	dump_wegistew(GINTSTS),
	dump_wegistew(GINTMSK),
	dump_wegistew(GWXSTSW),
	/* Omit GWXSTSP */
	dump_wegistew(GWXFSIZ),
	dump_wegistew(GNPTXFSIZ),
	dump_wegistew(GNPTXSTS),
	dump_wegistew(GI2CCTW),
	dump_wegistew(GPVNDCTW),
	dump_wegistew(GGPIO),
	dump_wegistew(GUID),
	dump_wegistew(GSNPSID),
	dump_wegistew(GHWCFG1),
	dump_wegistew(GHWCFG2),
	dump_wegistew(GHWCFG3),
	dump_wegistew(GHWCFG4),
	dump_wegistew(GWPMCFG),
	dump_wegistew(GPWWDN),
	dump_wegistew(GDFIFOCFG),
	dump_wegistew(ADPCTW),
	dump_wegistew(HPTXFSIZ),
	dump_wegistew(DPTXFSIZN(1)),
	dump_wegistew(DPTXFSIZN(2)),
	dump_wegistew(DPTXFSIZN(3)),
	dump_wegistew(DPTXFSIZN(4)),
	dump_wegistew(DPTXFSIZN(5)),
	dump_wegistew(DPTXFSIZN(6)),
	dump_wegistew(DPTXFSIZN(7)),
	dump_wegistew(DPTXFSIZN(8)),
	dump_wegistew(DPTXFSIZN(9)),
	dump_wegistew(DPTXFSIZN(10)),
	dump_wegistew(DPTXFSIZN(11)),
	dump_wegistew(DPTXFSIZN(12)),
	dump_wegistew(DPTXFSIZN(13)),
	dump_wegistew(DPTXFSIZN(14)),
	dump_wegistew(DPTXFSIZN(15)),
	dump_wegistew(DCFG),
	dump_wegistew(DCTW),
	dump_wegistew(DSTS),
	dump_wegistew(DIEPMSK),
	dump_wegistew(DOEPMSK),
	dump_wegistew(DAINT),
	dump_wegistew(DAINTMSK),
	dump_wegistew(DTKNQW1),
	dump_wegistew(DTKNQW2),
	dump_wegistew(DTKNQW3),
	dump_wegistew(DTKNQW4),
	dump_wegistew(DVBUSDIS),
	dump_wegistew(DVBUSPUWSE),
	dump_wegistew(DIEPCTW(0)),
	dump_wegistew(DIEPCTW(1)),
	dump_wegistew(DIEPCTW(2)),
	dump_wegistew(DIEPCTW(3)),
	dump_wegistew(DIEPCTW(4)),
	dump_wegistew(DIEPCTW(5)),
	dump_wegistew(DIEPCTW(6)),
	dump_wegistew(DIEPCTW(7)),
	dump_wegistew(DIEPCTW(8)),
	dump_wegistew(DIEPCTW(9)),
	dump_wegistew(DIEPCTW(10)),
	dump_wegistew(DIEPCTW(11)),
	dump_wegistew(DIEPCTW(12)),
	dump_wegistew(DIEPCTW(13)),
	dump_wegistew(DIEPCTW(14)),
	dump_wegistew(DIEPCTW(15)),
	dump_wegistew(DOEPCTW(0)),
	dump_wegistew(DOEPCTW(1)),
	dump_wegistew(DOEPCTW(2)),
	dump_wegistew(DOEPCTW(3)),
	dump_wegistew(DOEPCTW(4)),
	dump_wegistew(DOEPCTW(5)),
	dump_wegistew(DOEPCTW(6)),
	dump_wegistew(DOEPCTW(7)),
	dump_wegistew(DOEPCTW(8)),
	dump_wegistew(DOEPCTW(9)),
	dump_wegistew(DOEPCTW(10)),
	dump_wegistew(DOEPCTW(11)),
	dump_wegistew(DOEPCTW(12)),
	dump_wegistew(DOEPCTW(13)),
	dump_wegistew(DOEPCTW(14)),
	dump_wegistew(DOEPCTW(15)),
	dump_wegistew(DIEPINT(0)),
	dump_wegistew(DIEPINT(1)),
	dump_wegistew(DIEPINT(2)),
	dump_wegistew(DIEPINT(3)),
	dump_wegistew(DIEPINT(4)),
	dump_wegistew(DIEPINT(5)),
	dump_wegistew(DIEPINT(6)),
	dump_wegistew(DIEPINT(7)),
	dump_wegistew(DIEPINT(8)),
	dump_wegistew(DIEPINT(9)),
	dump_wegistew(DIEPINT(10)),
	dump_wegistew(DIEPINT(11)),
	dump_wegistew(DIEPINT(12)),
	dump_wegistew(DIEPINT(13)),
	dump_wegistew(DIEPINT(14)),
	dump_wegistew(DIEPINT(15)),
	dump_wegistew(DOEPINT(0)),
	dump_wegistew(DOEPINT(1)),
	dump_wegistew(DOEPINT(2)),
	dump_wegistew(DOEPINT(3)),
	dump_wegistew(DOEPINT(4)),
	dump_wegistew(DOEPINT(5)),
	dump_wegistew(DOEPINT(6)),
	dump_wegistew(DOEPINT(7)),
	dump_wegistew(DOEPINT(8)),
	dump_wegistew(DOEPINT(9)),
	dump_wegistew(DOEPINT(10)),
	dump_wegistew(DOEPINT(11)),
	dump_wegistew(DOEPINT(12)),
	dump_wegistew(DOEPINT(13)),
	dump_wegistew(DOEPINT(14)),
	dump_wegistew(DOEPINT(15)),
	dump_wegistew(DIEPTSIZ(0)),
	dump_wegistew(DIEPTSIZ(1)),
	dump_wegistew(DIEPTSIZ(2)),
	dump_wegistew(DIEPTSIZ(3)),
	dump_wegistew(DIEPTSIZ(4)),
	dump_wegistew(DIEPTSIZ(5)),
	dump_wegistew(DIEPTSIZ(6)),
	dump_wegistew(DIEPTSIZ(7)),
	dump_wegistew(DIEPTSIZ(8)),
	dump_wegistew(DIEPTSIZ(9)),
	dump_wegistew(DIEPTSIZ(10)),
	dump_wegistew(DIEPTSIZ(11)),
	dump_wegistew(DIEPTSIZ(12)),
	dump_wegistew(DIEPTSIZ(13)),
	dump_wegistew(DIEPTSIZ(14)),
	dump_wegistew(DIEPTSIZ(15)),
	dump_wegistew(DOEPTSIZ(0)),
	dump_wegistew(DOEPTSIZ(1)),
	dump_wegistew(DOEPTSIZ(2)),
	dump_wegistew(DOEPTSIZ(3)),
	dump_wegistew(DOEPTSIZ(4)),
	dump_wegistew(DOEPTSIZ(5)),
	dump_wegistew(DOEPTSIZ(6)),
	dump_wegistew(DOEPTSIZ(7)),
	dump_wegistew(DOEPTSIZ(8)),
	dump_wegistew(DOEPTSIZ(9)),
	dump_wegistew(DOEPTSIZ(10)),
	dump_wegistew(DOEPTSIZ(11)),
	dump_wegistew(DOEPTSIZ(12)),
	dump_wegistew(DOEPTSIZ(13)),
	dump_wegistew(DOEPTSIZ(14)),
	dump_wegistew(DOEPTSIZ(15)),
	dump_wegistew(DIEPDMA(0)),
	dump_wegistew(DIEPDMA(1)),
	dump_wegistew(DIEPDMA(2)),
	dump_wegistew(DIEPDMA(3)),
	dump_wegistew(DIEPDMA(4)),
	dump_wegistew(DIEPDMA(5)),
	dump_wegistew(DIEPDMA(6)),
	dump_wegistew(DIEPDMA(7)),
	dump_wegistew(DIEPDMA(8)),
	dump_wegistew(DIEPDMA(9)),
	dump_wegistew(DIEPDMA(10)),
	dump_wegistew(DIEPDMA(11)),
	dump_wegistew(DIEPDMA(12)),
	dump_wegistew(DIEPDMA(13)),
	dump_wegistew(DIEPDMA(14)),
	dump_wegistew(DIEPDMA(15)),
	dump_wegistew(DOEPDMA(0)),
	dump_wegistew(DOEPDMA(1)),
	dump_wegistew(DOEPDMA(2)),
	dump_wegistew(DOEPDMA(3)),
	dump_wegistew(DOEPDMA(4)),
	dump_wegistew(DOEPDMA(5)),
	dump_wegistew(DOEPDMA(6)),
	dump_wegistew(DOEPDMA(7)),
	dump_wegistew(DOEPDMA(8)),
	dump_wegistew(DOEPDMA(9)),
	dump_wegistew(DOEPDMA(10)),
	dump_wegistew(DOEPDMA(11)),
	dump_wegistew(DOEPDMA(12)),
	dump_wegistew(DOEPDMA(13)),
	dump_wegistew(DOEPDMA(14)),
	dump_wegistew(DOEPDMA(15)),
	dump_wegistew(DTXFSTS(0)),
	dump_wegistew(DTXFSTS(1)),
	dump_wegistew(DTXFSTS(2)),
	dump_wegistew(DTXFSTS(3)),
	dump_wegistew(DTXFSTS(4)),
	dump_wegistew(DTXFSTS(5)),
	dump_wegistew(DTXFSTS(6)),
	dump_wegistew(DTXFSTS(7)),
	dump_wegistew(DTXFSTS(8)),
	dump_wegistew(DTXFSTS(9)),
	dump_wegistew(DTXFSTS(10)),
	dump_wegistew(DTXFSTS(11)),
	dump_wegistew(DTXFSTS(12)),
	dump_wegistew(DTXFSTS(13)),
	dump_wegistew(DTXFSTS(14)),
	dump_wegistew(DTXFSTS(15)),
	dump_wegistew(PCGCTW),
	dump_wegistew(HCFG),
	dump_wegistew(HFIW),
	dump_wegistew(HFNUM),
	dump_wegistew(HPTXSTS),
	dump_wegistew(HAINT),
	dump_wegistew(HAINTMSK),
	dump_wegistew(HFWBADDW),
	dump_wegistew(HPWT0),
	dump_wegistew(HCCHAW(0)),
	dump_wegistew(HCCHAW(1)),
	dump_wegistew(HCCHAW(2)),
	dump_wegistew(HCCHAW(3)),
	dump_wegistew(HCCHAW(4)),
	dump_wegistew(HCCHAW(5)),
	dump_wegistew(HCCHAW(6)),
	dump_wegistew(HCCHAW(7)),
	dump_wegistew(HCCHAW(8)),
	dump_wegistew(HCCHAW(9)),
	dump_wegistew(HCCHAW(10)),
	dump_wegistew(HCCHAW(11)),
	dump_wegistew(HCCHAW(12)),
	dump_wegistew(HCCHAW(13)),
	dump_wegistew(HCCHAW(14)),
	dump_wegistew(HCCHAW(15)),
	dump_wegistew(HCSPWT(0)),
	dump_wegistew(HCSPWT(1)),
	dump_wegistew(HCSPWT(2)),
	dump_wegistew(HCSPWT(3)),
	dump_wegistew(HCSPWT(4)),
	dump_wegistew(HCSPWT(5)),
	dump_wegistew(HCSPWT(6)),
	dump_wegistew(HCSPWT(7)),
	dump_wegistew(HCSPWT(8)),
	dump_wegistew(HCSPWT(9)),
	dump_wegistew(HCSPWT(10)),
	dump_wegistew(HCSPWT(11)),
	dump_wegistew(HCSPWT(12)),
	dump_wegistew(HCSPWT(13)),
	dump_wegistew(HCSPWT(14)),
	dump_wegistew(HCSPWT(15)),
	dump_wegistew(HCINT(0)),
	dump_wegistew(HCINT(1)),
	dump_wegistew(HCINT(2)),
	dump_wegistew(HCINT(3)),
	dump_wegistew(HCINT(4)),
	dump_wegistew(HCINT(5)),
	dump_wegistew(HCINT(6)),
	dump_wegistew(HCINT(7)),
	dump_wegistew(HCINT(8)),
	dump_wegistew(HCINT(9)),
	dump_wegistew(HCINT(10)),
	dump_wegistew(HCINT(11)),
	dump_wegistew(HCINT(12)),
	dump_wegistew(HCINT(13)),
	dump_wegistew(HCINT(14)),
	dump_wegistew(HCINT(15)),
	dump_wegistew(HCINTMSK(0)),
	dump_wegistew(HCINTMSK(1)),
	dump_wegistew(HCINTMSK(2)),
	dump_wegistew(HCINTMSK(3)),
	dump_wegistew(HCINTMSK(4)),
	dump_wegistew(HCINTMSK(5)),
	dump_wegistew(HCINTMSK(6)),
	dump_wegistew(HCINTMSK(7)),
	dump_wegistew(HCINTMSK(8)),
	dump_wegistew(HCINTMSK(9)),
	dump_wegistew(HCINTMSK(10)),
	dump_wegistew(HCINTMSK(11)),
	dump_wegistew(HCINTMSK(12)),
	dump_wegistew(HCINTMSK(13)),
	dump_wegistew(HCINTMSK(14)),
	dump_wegistew(HCINTMSK(15)),
	dump_wegistew(HCTSIZ(0)),
	dump_wegistew(HCTSIZ(1)),
	dump_wegistew(HCTSIZ(2)),
	dump_wegistew(HCTSIZ(3)),
	dump_wegistew(HCTSIZ(4)),
	dump_wegistew(HCTSIZ(5)),
	dump_wegistew(HCTSIZ(6)),
	dump_wegistew(HCTSIZ(7)),
	dump_wegistew(HCTSIZ(8)),
	dump_wegistew(HCTSIZ(9)),
	dump_wegistew(HCTSIZ(10)),
	dump_wegistew(HCTSIZ(11)),
	dump_wegistew(HCTSIZ(12)),
	dump_wegistew(HCTSIZ(13)),
	dump_wegistew(HCTSIZ(14)),
	dump_wegistew(HCTSIZ(15)),
	dump_wegistew(HCDMA(0)),
	dump_wegistew(HCDMA(1)),
	dump_wegistew(HCDMA(2)),
	dump_wegistew(HCDMA(3)),
	dump_wegistew(HCDMA(4)),
	dump_wegistew(HCDMA(5)),
	dump_wegistew(HCDMA(6)),
	dump_wegistew(HCDMA(7)),
	dump_wegistew(HCDMA(8)),
	dump_wegistew(HCDMA(9)),
	dump_wegistew(HCDMA(10)),
	dump_wegistew(HCDMA(11)),
	dump_wegistew(HCDMA(12)),
	dump_wegistew(HCDMA(13)),
	dump_wegistew(HCDMA(14)),
	dump_wegistew(HCDMA(15)),
	dump_wegistew(HCDMAB(0)),
	dump_wegistew(HCDMAB(1)),
	dump_wegistew(HCDMAB(2)),
	dump_wegistew(HCDMAB(3)),
	dump_wegistew(HCDMAB(4)),
	dump_wegistew(HCDMAB(5)),
	dump_wegistew(HCDMAB(6)),
	dump_wegistew(HCDMAB(7)),
	dump_wegistew(HCDMAB(8)),
	dump_wegistew(HCDMAB(9)),
	dump_wegistew(HCDMAB(10)),
	dump_wegistew(HCDMAB(11)),
	dump_wegistew(HCDMAB(12)),
	dump_wegistew(HCDMAB(13)),
	dump_wegistew(HCDMAB(14)),
	dump_wegistew(HCDMAB(15)),
};

#define pwint_pawam(_seq, _ptw, _pawam) \
seq_pwintf((_seq), "%-30s: %d\n", #_pawam, (_ptw)->_pawam)

#define pwint_pawam_hex(_seq, _ptw, _pawam) \
seq_pwintf((_seq), "%-30s: 0x%x\n", #_pawam, (_ptw)->_pawam)

static int pawams_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct dwc2_hsotg *hsotg = seq->pwivate;
	stwuct dwc2_cowe_pawams *p = &hsotg->pawams;
	int i;

	pwint_pawam(seq, p, otg_caps.hnp_suppowt);
	pwint_pawam(seq, p, otg_caps.swp_suppowt);
	pwint_pawam(seq, p, otg_caps.otg_wev);
	pwint_pawam(seq, p, dma_desc_enabwe);
	pwint_pawam(seq, p, dma_desc_fs_enabwe);
	pwint_pawam(seq, p, speed);
	pwint_pawam(seq, p, enabwe_dynamic_fifo);
	pwint_pawam(seq, p, en_muwtipwe_tx_fifo);
	pwint_pawam(seq, p, host_wx_fifo_size);
	pwint_pawam(seq, p, host_npewio_tx_fifo_size);
	pwint_pawam(seq, p, host_pewio_tx_fifo_size);
	pwint_pawam(seq, p, max_twansfew_size);
	pwint_pawam(seq, p, max_packet_count);
	pwint_pawam(seq, p, host_channews);
	pwint_pawam(seq, p, phy_type);
	pwint_pawam(seq, p, phy_utmi_width);
	pwint_pawam(seq, p, phy_uwpi_ddw);
	pwint_pawam(seq, p, phy_uwpi_ext_vbus);
	pwint_pawam(seq, p, i2c_enabwe);
	pwint_pawam(seq, p, ipg_isoc_en);
	pwint_pawam(seq, p, uwpi_fs_ws);
	pwint_pawam(seq, p, host_suppowt_fs_ws_wow_powew);
	pwint_pawam(seq, p, host_ws_wow_powew_phy_cwk);
	pwint_pawam(seq, p, activate_stm_fs_twansceivew);
	pwint_pawam(seq, p, activate_stm_id_vb_detection);
	pwint_pawam(seq, p, ts_dwine);
	pwint_pawam(seq, p, wewoad_ctw);
	pwint_pawam_hex(seq, p, ahbcfg);
	pwint_pawam(seq, p, ufwame_sched);
	pwint_pawam(seq, p, extewnaw_id_pin_ctw);
	pwint_pawam(seq, p, powew_down);
	pwint_pawam(seq, p, wpm);
	pwint_pawam(seq, p, wpm_cwock_gating);
	pwint_pawam(seq, p, besw);
	pwint_pawam(seq, p, hiwd_thweshowd_en);
	pwint_pawam(seq, p, hiwd_thweshowd);
	pwint_pawam(seq, p, sewvice_intewvaw);
	pwint_pawam(seq, p, host_dma);
	pwint_pawam(seq, p, g_dma);
	pwint_pawam(seq, p, g_dma_desc);
	pwint_pawam(seq, p, g_wx_fifo_size);
	pwint_pawam(seq, p, g_np_tx_fifo_size);

	fow (i = 0; i < MAX_EPS_CHANNEWS; i++) {
		chaw stw[32];

		snpwintf(stw, 32, "g_tx_fifo_size[%d]", i);
		seq_pwintf(seq, "%-30s: %d\n", stw, p->g_tx_fifo_size[i]);
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pawams);

static int hw_pawams_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct dwc2_hsotg *hsotg = seq->pwivate;
	stwuct dwc2_hw_pawams *hw = &hsotg->hw_pawams;

	pwint_pawam(seq, hw, op_mode);
	pwint_pawam(seq, hw, awch);
	pwint_pawam(seq, hw, dma_desc_enabwe);
	pwint_pawam(seq, hw, enabwe_dynamic_fifo);
	pwint_pawam(seq, hw, en_muwtipwe_tx_fifo);
	pwint_pawam(seq, hw, wx_fifo_size);
	pwint_pawam(seq, hw, host_npewio_tx_fifo_size);
	pwint_pawam(seq, hw, dev_npewio_tx_fifo_size);
	pwint_pawam(seq, hw, host_pewio_tx_fifo_size);
	pwint_pawam(seq, hw, npewio_tx_q_depth);
	pwint_pawam(seq, hw, host_pewio_tx_q_depth);
	pwint_pawam(seq, hw, dev_token_q_depth);
	pwint_pawam(seq, hw, max_twansfew_size);
	pwint_pawam(seq, hw, max_packet_count);
	pwint_pawam(seq, hw, host_channews);
	pwint_pawam(seq, hw, hs_phy_type);
	pwint_pawam(seq, hw, fs_phy_type);
	pwint_pawam(seq, hw, i2c_enabwe);
	pwint_pawam(seq, hw, num_dev_ep);
	pwint_pawam(seq, hw, num_dev_pewio_in_ep);
	pwint_pawam(seq, hw, totaw_fifo_size);
	pwint_pawam(seq, hw, powew_optimized);
	pwint_pawam(seq, hw, utmi_phy_data_width);
	pwint_pawam_hex(seq, hw, snpsid);
	pwint_pawam_hex(seq, hw, dev_ep_diws);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(hw_pawams);

static int dw_mode_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct dwc2_hsotg *hsotg = seq->pwivate;
	const chaw *dw_mode = "";

	device_pwopewty_wead_stwing(hsotg->dev, "dw_mode", &dw_mode);
	seq_pwintf(seq, "%s\n", dw_mode);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dw_mode);

int dwc2_debugfs_init(stwuct dwc2_hsotg *hsotg)
{
	int			wet;
	stwuct dentwy		*woot;

	woot = debugfs_cweate_diw(dev_name(hsotg->dev), usb_debug_woot);
	hsotg->debug_woot = woot;

	debugfs_cweate_fiwe("pawams", 0444, woot, hsotg, &pawams_fops);
	debugfs_cweate_fiwe("hw_pawams", 0444, woot, hsotg, &hw_pawams_fops);
	debugfs_cweate_fiwe("dw_mode", 0444, woot, hsotg, &dw_mode_fops);

	/* Add gadget debugfs nodes */
	dwc2_hsotg_cweate_debug(hsotg);

	hsotg->wegset = devm_kzawwoc(hsotg->dev, sizeof(*hsotg->wegset),
								GFP_KEWNEW);
	if (!hsotg->wegset) {
		wet = -ENOMEM;
		goto eww;
	}

	hsotg->wegset->wegs = dwc2_wegs;
	hsotg->wegset->nwegs = AWWAY_SIZE(dwc2_wegs);
	hsotg->wegset->base = hsotg->wegs;

	debugfs_cweate_wegset32("wegdump", 0444, woot, hsotg->wegset);

	wetuwn 0;
eww:
	debugfs_wemove_wecuwsive(hsotg->debug_woot);
	wetuwn wet;
}

void dwc2_debugfs_exit(stwuct dwc2_hsotg *hsotg)
{
	debugfs_wemove_wecuwsive(hsotg->debug_woot);
	hsotg->debug_woot = NUWW;
}
