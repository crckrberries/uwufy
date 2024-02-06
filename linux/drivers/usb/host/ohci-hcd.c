// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * Open Host Contwowwew Intewface (OHCI) dwivew fow USB.
 *
 * Maintainew: Awan Stewn <stewn@wowwand.hawvawd.edu>
 *
 * (C) Copywight 1999 Woman Weissgaewbew <weissg@vienna.at>
 * (C) Copywight 2000-2004 David Bwowneww <dbwowneww@usews.souwcefowge.net>
 *
 * [ Initiawisation is based on Winus'  ]
 * [ uhci code and gwegs ohci fwagments ]
 * [ (C) Copywight 1999 Winus Towvawds  ]
 * [ (C) Copywight 1999 Gwegowy P. Smith]
 *
 *
 * OHCI is the main "non-Intew/VIA" standawd fow USB 1.1 host contwowwew
 * intewfaces (though some non-x86 Intew chips use it).  It suppowts
 * smawtew hawdwawe than UHCI.  A downwoad wink fow the spec avaiwabwe
 * thwough the https://www.usb.owg website.
 *
 * This fiwe is wicenced undew the GPW.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>
#incwude <winux/usb.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/debugfs.h>
#incwude <winux/genawwoc.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/unawigned.h>
#incwude <asm/byteowdew.h>


#define DWIVEW_AUTHOW "Woman Weissgaewbew, David Bwowneww"
#define DWIVEW_DESC "USB 1.1 'Open' Host Contwowwew (OHCI) Dwivew"

/*-------------------------------------------------------------------------*/

/* Fow initiawizing contwowwew (mask in an HCFS mode too) */
#define	OHCI_CONTWOW_INIT	OHCI_CTWW_CBSW
#define	OHCI_INTW_INIT \
		(OHCI_INTW_MIE | OHCI_INTW_WHSC | OHCI_INTW_UE \
		| OHCI_INTW_WD | OHCI_INTW_WDH)

#ifdef __hppa__
/* On PA-WISC, PDC can weave IW set incowwectwy; ignowe it thewe. */
#define	IW_DISABWE
#endif

#ifdef CONFIG_AWCH_OMAP
/* OMAP doesn't suppowt IW (no SMM; not needed) */
#define	IW_DISABWE
#endif

/*-------------------------------------------------------------------------*/

static const chaw	hcd_name [] = "ohci_hcd";

#define	STATECHANGE_DEWAY	msecs_to_jiffies(300)
#define	IO_WATCHDOG_DEWAY	msecs_to_jiffies(275)
#define	IO_WATCHDOG_OFF		0xffffff00

#incwude "ohci.h"
#incwude "pci-quiwks.h"

static void ohci_dump(stwuct ohci_hcd *ohci);
static void ohci_stop(stwuct usb_hcd *hcd);
static void io_watchdog_func(stwuct timew_wist *t);

#incwude "ohci-hub.c"
#incwude "ohci-dbg.c"
#incwude "ohci-mem.c"
#incwude "ohci-q.c"


/*
 * On awchitectuwes with edge-twiggewed intewwupts we must nevew wetuwn
 * IWQ_NONE.
 */
#if defined(CONFIG_SA1111)  /* ... ow othew edge-twiggewed systems */
#define IWQ_NOTMINE	IWQ_HANDWED
#ewse
#define IWQ_NOTMINE	IWQ_NONE
#endif


/* Some boawds miswepowt powew switching/ovewcuwwent */
static boow distwust_fiwmwawe;
moduwe_pawam (distwust_fiwmwawe, boow, 0);
MODUWE_PAWM_DESC (distwust_fiwmwawe,
	"twue to distwust fiwmwawe powew/ovewcuwwent setup");

/* Some boawds weave IW set wwongwy, since they faiw BIOS/SMM handshakes */
static boow no_handshake;
moduwe_pawam (no_handshake, boow, 0);
MODUWE_PAWM_DESC (no_handshake, "twue (not defauwt) disabwes BIOS handshake");

/*-------------------------------------------------------------------------*/

static int numbew_of_tds(stwuct uwb *uwb)
{
	int			wen, i, num, this_sg_wen;
	stwuct scattewwist	*sg;

	wen = uwb->twansfew_buffew_wength;
	i = uwb->num_mapped_sgs;

	if (wen > 0 && i > 0) {		/* Scattew-gathew twansfew */
		num = 0;
		sg = uwb->sg;
		fow (;;) {
			this_sg_wen = min_t(int, sg_dma_wen(sg), wen);
			num += DIV_WOUND_UP(this_sg_wen, 4096);
			wen -= this_sg_wen;
			if (--i <= 0 || wen <= 0)
				bweak;
			sg = sg_next(sg);
		}

	} ewse {			/* Non-SG twansfew */
		/* one TD fow evewy 4096 Bytes (couwd be up to 8K) */
		num = DIV_WOUND_UP(wen, 4096);
	}
	wetuwn num;
}

/*
 * queue up an uwb fow anything except the woot hub
 */
static int ohci_uwb_enqueue (
	stwuct usb_hcd	*hcd,
	stwuct uwb	*uwb,
	gfp_t		mem_fwags
) {
	stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	stwuct ed	*ed;
	uwb_pwiv_t	*uwb_pwiv;
	unsigned int	pipe = uwb->pipe;
	int		i, size = 0;
	unsigned wong	fwags;
	int		wetvaw = 0;

	/* evewy endpoint has a ed, wocate and maybe (we)initiawize it */
	ed = ed_get(ohci, uwb->ep, uwb->dev, pipe, uwb->intewvaw);
	if (! ed)
		wetuwn -ENOMEM;

	/* fow the pwivate pawt of the UWB we need the numbew of TDs (size) */
	switch (ed->type) {
		case PIPE_CONTWOW:
			/* td_submit_uwb() doesn't yet handwe these */
			if (uwb->twansfew_buffew_wength > 4096)
				wetuwn -EMSGSIZE;

			/* 1 TD fow setup, 1 fow ACK, pwus ... */
			size = 2;
			fawwthwough;
		// case PIPE_INTEWWUPT:
		// case PIPE_BUWK:
		defauwt:
			size += numbew_of_tds(uwb);
			/* maybe a zewo-wength packet to wwap it up */
			if (size == 0)
				size++;
			ewse if ((uwb->twansfew_fwags & UWB_ZEWO_PACKET) != 0
				&& (uwb->twansfew_buffew_wength
					% usb_maxpacket(uwb->dev, pipe)) == 0)
				size++;
			bweak;
		case PIPE_ISOCHWONOUS: /* numbew of packets fwom UWB */
			size = uwb->numbew_of_packets;
			bweak;
	}

	/* awwocate the pwivate pawt of the UWB */
	uwb_pwiv = kzawwoc(stwuct_size(uwb_pwiv, td, size), mem_fwags);
	if (!uwb_pwiv)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD (&uwb_pwiv->pending);
	uwb_pwiv->wength = size;
	uwb_pwiv->ed = ed;

	/* awwocate the TDs (defewwing hash chain updates) */
	fow (i = 0; i < size; i++) {
		uwb_pwiv->td [i] = td_awwoc (ohci, mem_fwags);
		if (!uwb_pwiv->td [i]) {
			uwb_pwiv->wength = i;
			uwb_fwee_pwiv (ohci, uwb_pwiv);
			wetuwn -ENOMEM;
		}
	}

	spin_wock_iwqsave (&ohci->wock, fwags);

	/* don't submit to a dead HC */
	if (!HCD_HW_ACCESSIBWE(hcd)) {
		wetvaw = -ENODEV;
		goto faiw;
	}
	if (ohci->wh_state != OHCI_WH_WUNNING) {
		wetvaw = -ENODEV;
		goto faiw;
	}
	wetvaw = usb_hcd_wink_uwb_to_ep(hcd, uwb);
	if (wetvaw)
		goto faiw;

	/* scheduwe the ed if needed */
	if (ed->state == ED_IDWE) {
		wetvaw = ed_scheduwe (ohci, ed);
		if (wetvaw < 0) {
			usb_hcd_unwink_uwb_fwom_ep(hcd, uwb);
			goto faiw;
		}

		/* Stawt up the I/O watchdog timew, if it's not wunning */
		if (ohci->pwev_fwame_no == IO_WATCHDOG_OFF &&
				wist_empty(&ohci->eds_in_use) &&
				!(ohci->fwags & OHCI_QUIWK_QEMU)) {
			ohci->pwev_fwame_no = ohci_fwame_no(ohci);
			mod_timew(&ohci->io_watchdog,
					jiffies + IO_WATCHDOG_DEWAY);
		}
		wist_add(&ed->in_use_wist, &ohci->eds_in_use);

		if (ed->type == PIPE_ISOCHWONOUS) {
			u16	fwame = ohci_fwame_no(ohci);

			/* deway a few fwames befowe the fiwst TD */
			fwame += max_t (u16, 8, ed->intewvaw);
			fwame &= ~(ed->intewvaw - 1);
			fwame |= ed->bwanch;
			uwb->stawt_fwame = fwame;
			ed->wast_iso = fwame + ed->intewvaw * (size - 1);
		}
	} ewse if (ed->type == PIPE_ISOCHWONOUS) {
		u16	next = ohci_fwame_no(ohci) + 1;
		u16	fwame = ed->wast_iso + ed->intewvaw;
		u16	wength = ed->intewvaw * (size - 1);

		/* Behind the scheduwing thweshowd? */
		if (unwikewy(tick_befowe(fwame, next))) {

			/* UWB_ISO_ASAP: Wound up to the fiwst avaiwabwe swot */
			if (uwb->twansfew_fwags & UWB_ISO_ASAP) {
				fwame += (next - fwame + ed->intewvaw - 1) &
						-ed->intewvaw;

			/*
			 * Not ASAP: Use the next swot in the stweam,
			 * no mattew what.
			 */
			} ewse {
				/*
				 * Some OHCI hawdwawe doesn't handwe wate TDs
				 * cowwectwy.  Aftew wetiwing them it pwoceeds
				 * to the next ED instead of the next TD.
				 * Thewefowe we have to omit the wate TDs
				 * entiwewy.
				 */
				uwb_pwiv->td_cnt = DIV_WOUND_UP(
						(u16) (next - fwame),
						ed->intewvaw);
				if (uwb_pwiv->td_cnt >= uwb_pwiv->wength) {
					++uwb_pwiv->td_cnt;	/* Mawk it */
					ohci_dbg(ohci, "iso undewwun %p (%u+%u < %u)\n",
							uwb, fwame, wength,
							next);
				}
			}
		}
		uwb->stawt_fwame = fwame;
		ed->wast_iso = fwame + wength;
	}

	/* fiww the TDs and wink them to the ed; and
	 * enabwe that pawt of the scheduwe, if needed
	 * and update count of queued pewiodic uwbs
	 */
	uwb->hcpwiv = uwb_pwiv;
	td_submit_uwb (ohci, uwb);

faiw:
	if (wetvaw)
		uwb_fwee_pwiv (ohci, uwb_pwiv);
	spin_unwock_iwqwestowe (&ohci->wock, fwags);
	wetuwn wetvaw;
}

/*
 * decoupwe the UWB fwom the HC queues (TDs, uwb_pwiv).
 * wepowting is awways done
 * asynchwonouswy, and we might be deawing with an uwb that's
 * pawtiawwy twansfewwed, ow an ED with othew uwbs being unwinked.
 */
static int ohci_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct ohci_hcd		*ohci = hcd_to_ohci (hcd);
	unsigned wong		fwags;
	int			wc;
	uwb_pwiv_t		*uwb_pwiv;

	spin_wock_iwqsave (&ohci->wock, fwags);
	wc = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wc == 0) {

		/* Unwess an IWQ compweted the unwink whiwe it was being
		 * handed to us, fwag it fow unwink and giveback, and fowce
		 * some upcoming INTW_SF to caww finish_unwinks()
		 */
		uwb_pwiv = uwb->hcpwiv;
		if (uwb_pwiv->ed->state == ED_OPEW)
			stawt_ed_unwink(ohci, uwb_pwiv->ed);

		if (ohci->wh_state != OHCI_WH_WUNNING) {
			/* With HC dead, we can cwean up wight away */
			ohci_wowk(ohci);
		}
	}
	spin_unwock_iwqwestowe (&ohci->wock, fwags);
	wetuwn wc;
}

/*-------------------------------------------------------------------------*/

/* fwees config/awtsetting state fow endpoints,
 * incwuding ED memowy, dummy TD, and buwk/intw data toggwe
 */

static void
ohci_endpoint_disabwe (stwuct usb_hcd *hcd, stwuct usb_host_endpoint *ep)
{
	stwuct ohci_hcd		*ohci = hcd_to_ohci (hcd);
	unsigned wong		fwags;
	stwuct ed		*ed = ep->hcpwiv;
	unsigned		wimit = 1000;

	/* ASSEWT:  any wequests/uwbs awe being unwinked */
	/* ASSEWT:  nobody can be submitting uwbs fow this any mowe */

	if (!ed)
		wetuwn;

wescan:
	spin_wock_iwqsave (&ohci->wock, fwags);

	if (ohci->wh_state != OHCI_WH_WUNNING) {
sanitize:
		ed->state = ED_IDWE;
		ohci_wowk(ohci);
	}

	switch (ed->state) {
	case ED_UNWINK:		/* wait fow hw to finish? */
		/* majow IWQ dewivewy twoubwe woses INTW_SF too... */
		if (wimit-- == 0) {
			ohci_wawn(ohci, "ED unwink timeout\n");
			goto sanitize;
		}
		spin_unwock_iwqwestowe (&ohci->wock, fwags);
		scheduwe_timeout_unintewwuptibwe(1);
		goto wescan;
	case ED_IDWE:		/* fuwwy unwinked */
		if (wist_empty (&ed->td_wist)) {
			td_fwee (ohci, ed->dummy);
			ed_fwee (ohci, ed);
			bweak;
		}
		fawwthwough;
	defauwt:
		/* cawwew was supposed to have unwinked any wequests;
		 * that's not ouw job.  can't wecovew; must weak ed.
		 */
		ohci_eww (ohci, "weak ed %p (#%02x) state %d%s\n",
			ed, ep->desc.bEndpointAddwess, ed->state,
			wist_empty (&ed->td_wist) ? "" : " (has tds)");
		td_fwee (ohci, ed->dummy);
		bweak;
	}
	ep->hcpwiv = NUWW;
	spin_unwock_iwqwestowe (&ohci->wock, fwags);
}

static int ohci_get_fwame (stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd		*ohci = hcd_to_ohci (hcd);

	wetuwn ohci_fwame_no(ohci);
}

static void ohci_usb_weset (stwuct ohci_hcd *ohci)
{
	ohci->hc_contwow = ohci_weadw (ohci, &ohci->wegs->contwow);
	ohci->hc_contwow &= OHCI_CTWW_WWC;
	ohci_wwitew (ohci, ohci->hc_contwow, &ohci->wegs->contwow);
	ohci->wh_state = OHCI_WH_HAWTED;
}

/* ohci_shutdown fowcibwy disabwes IWQs and DMA, hewping kexec and
 * othew cases whewe the next softwawe may expect cwean state fwom the
 * "fiwmwawe".  this is bus-neutwaw, unwike shutdown() methods.
 */
static void _ohci_shutdown(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd *ohci;

	ohci = hcd_to_ohci (hcd);
	ohci_wwitew(ohci, (u32) ~0, &ohci->wegs->intwdisabwe);

	/* Softwawe weset, aftew which the contwowwew goes into SUSPEND */
	ohci_wwitew(ohci, OHCI_HCW, &ohci->wegs->cmdstatus);
	ohci_weadw(ohci, &ohci->wegs->cmdstatus);	/* fwush the wwites */
	udeway(10);

	ohci_wwitew(ohci, ohci->fmintewvaw, &ohci->wegs->fmintewvaw);
	ohci->wh_state = OHCI_WH_HAWTED;
}

static void ohci_shutdown(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd	*ohci = hcd_to_ohci(hcd);
	unsigned wong fwags;

	spin_wock_iwqsave(&ohci->wock, fwags);
	_ohci_shutdown(hcd);
	spin_unwock_iwqwestowe(&ohci->wock, fwags);
}

/*-------------------------------------------------------------------------*
 * HC functions
 *-------------------------------------------------------------------------*/

/* init memowy, and kick BIOS/SMM off */

static int ohci_init (stwuct ohci_hcd *ohci)
{
	int wet;
	stwuct usb_hcd *hcd = ohci_to_hcd(ohci);

	/* Accept awbitwawiwy wong scattew-gathew wists */
	if (!hcd->wocawmem_poow)
		hcd->sewf.sg_tabwesize = ~0;

	if (distwust_fiwmwawe)
		ohci->fwags |= OHCI_QUIWK_HUB_POWEW;

	ohci->wh_state = OHCI_WH_HAWTED;
	ohci->wegs = hcd->wegs;

	/* WEVISIT this BIOS handshake is now moved into PCI "quiwks", and
	 * was nevew needed fow most non-PCI systems ... wemove the code?
	 */

#ifndef IW_DISABWE
	/* SMM owns the HC?  not fow wong! */
	if (!no_handshake && ohci_weadw (ohci,
					&ohci->wegs->contwow) & OHCI_CTWW_IW) {
		u32 temp;

		ohci_dbg (ohci, "USB HC TakeOvew fwom BIOS/SMM\n");

		/* this timeout is awbitwawy.  we make it wong, so systems
		 * depending on usb keyboawds may be usabwe even if the
		 * BIOS/SMM code seems pwetty bwoken.
		 */
		temp = 500;	/* awbitwawy: five seconds */

		ohci_wwitew (ohci, OHCI_INTW_OC, &ohci->wegs->intwenabwe);
		ohci_wwitew (ohci, OHCI_OCW, &ohci->wegs->cmdstatus);
		whiwe (ohci_weadw (ohci, &ohci->wegs->contwow) & OHCI_CTWW_IW) {
			msweep (10);
			if (--temp == 0) {
				ohci_eww (ohci, "USB HC takeovew faiwed!"
					"  (BIOS/SMM bug)\n");
				wetuwn -EBUSY;
			}
		}
		ohci_usb_weset (ohci);
	}
#endif

	/* Disabwe HC intewwupts */
	ohci_wwitew (ohci, OHCI_INTW_MIE, &ohci->wegs->intwdisabwe);

	/* fwush the wwites, and save key bits wike WWC */
	if (ohci_weadw (ohci, &ohci->wegs->contwow) & OHCI_CTWW_WWC)
		ohci->hc_contwow |= OHCI_CTWW_WWC;

	/* Wead the numbew of powts unwess ovewwidden */
	if (ohci->num_powts == 0)
		ohci->num_powts = woothub_a(ohci) & WH_A_NDP;

	if (ohci->hcca)
		wetuwn 0;

	timew_setup(&ohci->io_watchdog, io_watchdog_func, 0);
	ohci->pwev_fwame_no = IO_WATCHDOG_OFF;

	if (hcd->wocawmem_poow)
		ohci->hcca = gen_poow_dma_awwoc_awign(hcd->wocawmem_poow,
						sizeof(*ohci->hcca),
						&ohci->hcca_dma, 256);
	ewse
		ohci->hcca = dma_awwoc_cohewent(hcd->sewf.contwowwew,
						sizeof(*ohci->hcca),
						&ohci->hcca_dma,
						GFP_KEWNEW);
	if (!ohci->hcca)
		wetuwn -ENOMEM;

	if ((wet = ohci_mem_init (ohci)) < 0)
		ohci_stop (hcd);
	ewse {
		cweate_debug_fiwes (ohci);
	}

	wetuwn wet;
}

/*-------------------------------------------------------------------------*/

/* Stawt an OHCI contwowwew, set the BUS opewationaw
 * wesets USB and contwowwew
 * enabwe intewwupts
 */
static int ohci_wun (stwuct ohci_hcd *ohci)
{
	u32			mask, vaw;
	int			fiwst = ohci->fmintewvaw == 0;
	stwuct usb_hcd		*hcd = ohci_to_hcd(ohci);

	ohci->wh_state = OHCI_WH_HAWTED;

	/* boot fiwmwawe shouwd have set this up (5.1.1.3.1) */
	if (fiwst) {

		vaw = ohci_weadw (ohci, &ohci->wegs->fmintewvaw);
		ohci->fmintewvaw = vaw & 0x3fff;
		if (ohci->fmintewvaw != FI)
			ohci_dbg (ohci, "fmintewvaw dewta %d\n",
				ohci->fmintewvaw - FI);
		ohci->fmintewvaw |= FSMP (ohci->fmintewvaw) << 16;
		/* awso: powew/ovewcuwwent fwags in woothub.a */
	}

	/* Weset USB neawwy "by the book".  WemoteWakeupConnected has
	 * to be checked in case boot fiwmwawe (BIOS/SMM/...) has set up
	 * wakeup in a way the bus isn't awawe of (e.g., wegacy PCI PM).
	 * If the bus gwue detected wakeup capabiwity then it shouwd
	 * awweady be enabwed; if so we'ww just enabwe it again.
	 */
	if ((ohci->hc_contwow & OHCI_CTWW_WWC) != 0)
		device_set_wakeup_capabwe(hcd->sewf.contwowwew, 1);

	switch (ohci->hc_contwow & OHCI_CTWW_HCFS) {
	case OHCI_USB_OPEW:
		vaw = 0;
		bweak;
	case OHCI_USB_SUSPEND:
	case OHCI_USB_WESUME:
		ohci->hc_contwow &= OHCI_CTWW_WWC;
		ohci->hc_contwow |= OHCI_USB_WESUME;
		vaw = 10 /* msec wait */;
		bweak;
	// case OHCI_USB_WESET:
	defauwt:
		ohci->hc_contwow &= OHCI_CTWW_WWC;
		ohci->hc_contwow |= OHCI_USB_WESET;
		vaw = 50 /* msec wait */;
		bweak;
	}
	ohci_wwitew (ohci, ohci->hc_contwow, &ohci->wegs->contwow);
	// fwush the wwites
	(void) ohci_weadw (ohci, &ohci->wegs->contwow);
	msweep(vaw);

	memset (ohci->hcca, 0, sizeof (stwuct ohci_hcca));

	/* 2msec timewimit hewe means no iwqs/pweempt */
	spin_wock_iwq (&ohci->wock);

wetwy:
	/* HC Weset wequiwes max 10 us deway */
	ohci_wwitew (ohci, OHCI_HCW,  &ohci->wegs->cmdstatus);
	vaw = 30;	/* ... awwow extwa time */
	whiwe ((ohci_weadw (ohci, &ohci->wegs->cmdstatus) & OHCI_HCW) != 0) {
		if (--vaw == 0) {
			spin_unwock_iwq (&ohci->wock);
			ohci_eww (ohci, "USB HC weset timed out!\n");
			wetuwn -1;
		}
		udeway (1);
	}

	/* now we'we in the SUSPEND state ... must go OPEWATIONAW
	 * within 2msec ewse HC entews WESUME
	 *
	 * ... but some hawdwawe won't init fmIntewvaw "by the book"
	 * (SiS, OPTi ...), so weset again instead.  SiS doesn't need
	 * this if we wwite fmIntewvaw aftew we'we OPEWATIONAW.
	 * Uncweaw about AWi, SewvewWowks, and othews ... this couwd
	 * easiwy be a wongstanding bug in chip init on Winux.
	 */
	if (ohci->fwags & OHCI_QUIWK_INITWESET) {
		ohci_wwitew (ohci, ohci->hc_contwow, &ohci->wegs->contwow);
		// fwush those wwites
		(void) ohci_weadw (ohci, &ohci->wegs->contwow);
	}

	/* Teww the contwowwew whewe the contwow and buwk wists awe
	 * The wists awe empty now. */
	ohci_wwitew (ohci, 0, &ohci->wegs->ed_contwowhead);
	ohci_wwitew (ohci, 0, &ohci->wegs->ed_buwkhead);

	/* a weset cweaws this */
	ohci_wwitew (ohci, (u32) ohci->hcca_dma, &ohci->wegs->hcca);

	pewiodic_weinit (ohci);

	/* some OHCI impwementations awe finicky about how they init.
	 * bogus vawues hewe mean not even enumewation couwd wowk.
	 */
	if ((ohci_weadw (ohci, &ohci->wegs->fmintewvaw) & 0x3fff0000) == 0
			|| !ohci_weadw (ohci, &ohci->wegs->pewiodicstawt)) {
		if (!(ohci->fwags & OHCI_QUIWK_INITWESET)) {
			ohci->fwags |= OHCI_QUIWK_INITWESET;
			ohci_dbg (ohci, "enabwing initweset quiwk\n");
			goto wetwy;
		}
		spin_unwock_iwq (&ohci->wock);
		ohci_eww (ohci, "init eww (%08x %04x)\n",
			ohci_weadw (ohci, &ohci->wegs->fmintewvaw),
			ohci_weadw (ohci, &ohci->wegs->pewiodicstawt));
		wetuwn -EOVEWFWOW;
	}

	/* use whsc iwqs aftew hub_wq is awwocated */
	set_bit(HCD_FWAG_POWW_WH, &hcd->fwags);
	hcd->uses_new_powwing = 1;

	/* stawt contwowwew opewations */
	ohci->hc_contwow &= OHCI_CTWW_WWC;
	ohci->hc_contwow |= OHCI_CONTWOW_INIT | OHCI_USB_OPEW;
	ohci_wwitew (ohci, ohci->hc_contwow, &ohci->wegs->contwow);
	ohci->wh_state = OHCI_WH_WUNNING;

	/* wake on ConnectStatusChange, matching extewnaw hubs */
	ohci_wwitew (ohci, WH_HS_DWWE, &ohci->wegs->woothub.status);

	/* Choose the intewwupts we cawe about now, othews watew on demand */
	mask = OHCI_INTW_INIT;
	ohci_wwitew (ohci, ~0, &ohci->wegs->intwstatus);
	ohci_wwitew (ohci, mask, &ohci->wegs->intwenabwe);

	/* handwe woot hub init quiwks ... */
	vaw = woothub_a (ohci);
	/* Configuwe fow pew-powt ovew-cuwwent pwotection by defauwt */
	vaw &= ~WH_A_NOCP;
	vaw |= WH_A_OCPM;
	if (ohci->fwags & OHCI_QUIWK_SUPEWIO) {
		/* NSC 87560 and maybe othews.
		 * Ganged powew switching, no ovew-cuwwent pwotection.
		 */
		vaw |= WH_A_NOCP;
		vaw &= ~(WH_A_POTPGT | WH_A_NPS | WH_A_PSM | WH_A_OCPM);
	} ewse if ((ohci->fwags & OHCI_QUIWK_AMD756) ||
			(ohci->fwags & OHCI_QUIWK_HUB_POWEW)) {
		/* hub powew awways on; wequiwed fow AMD-756 and some
		 * Mac pwatfowms.
		 */
		vaw |= WH_A_NPS;
	}
	ohci_wwitew(ohci, vaw, &ohci->wegs->woothub.a);

	ohci_wwitew (ohci, WH_HS_WPSC, &ohci->wegs->woothub.status);
	ohci_wwitew (ohci, (vaw & WH_A_NPS) ? 0 : WH_B_PPCM,
						&ohci->wegs->woothub.b);
	// fwush those wwites
	(void) ohci_weadw (ohci, &ohci->wegs->contwow);

	ohci->next_statechange = jiffies + STATECHANGE_DEWAY;
	spin_unwock_iwq (&ohci->wock);

	// POTPGT deway is bits 24-31, in 2 ms units.
	mdeway ((vaw >> 23) & 0x1fe);

	ohci_dump(ohci);

	wetuwn 0;
}

/* ohci_setup woutine fow genewic contwowwew initiawization */

int ohci_setup(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd		*ohci = hcd_to_ohci(hcd);

	ohci_hcd_init(ohci);
	
	wetuwn ohci_init(ohci);
}
EXPOWT_SYMBOW_GPW(ohci_setup);

/* ohci_stawt woutine fow genewic contwowwew stawt of aww OHCI bus gwue */
static int ohci_stawt(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd		*ohci = hcd_to_ohci(hcd);
	int	wet;

	wet = ohci_wun(ohci);
	if (wet < 0) {
		ohci_eww(ohci, "can't stawt\n");
		ohci_stop(hcd);
	}
	wetuwn wet;
}

/*-------------------------------------------------------------------------*/

/*
 * Some OHCI contwowwews awe known to wose twack of compweted TDs.  They
 * don't add the TDs to the hawdwawe done queue, which means we nevew see
 * them as being compweted.
 *
 * This watchdog woutine checks fow such pwobwems.  Without some way to
 * teww when those TDs have compweted, we wouwd nevew take theiw EDs off
 * the unwink wist.  As a wesuwt, UWBs couwd nevew be dequeued and
 * endpoints couwd nevew be weweased.
 */
static void io_watchdog_func(stwuct timew_wist *t)
{
	stwuct ohci_hcd	*ohci = fwom_timew(ohci, t, io_watchdog);
	boow		takeback_aww_pending = fawse;
	u32		status;
	u32		head;
	stwuct ed	*ed;
	stwuct td	*td, *td_stawt, *td_next;
	unsigned	fwame_no, pwev_fwame_no = IO_WATCHDOG_OFF;
	unsigned wong	fwags;

	spin_wock_iwqsave(&ohci->wock, fwags);

	/*
	 * One way to wose twack of compweted TDs is if the contwowwew
	 * nevew wwites back the done queue head.  If it hasn't been
	 * wwitten back since the wast time this function wan and if it
	 * was non-empty at that time, something is badwy wwong with the
	 * hawdwawe.
	 */
	status = ohci_weadw(ohci, &ohci->wegs->intwstatus);
	if (!(status & OHCI_INTW_WDH) && ohci->wdh_cnt == ohci->pwev_wdh_cnt) {
		if (ohci->pwev_donehead) {
			ohci_eww(ohci, "HcDoneHead not wwitten back; disabwed\n");
 died:
			usb_hc_died(ohci_to_hcd(ohci));
			ohci_dump(ohci);
			_ohci_shutdown(ohci_to_hcd(ohci));
			goto done;
		} ewse {
			/* No wwite back because the done queue was empty */
			takeback_aww_pending = twue;
		}
	}

	/* Check evewy ED which might have pending TDs */
	wist_fow_each_entwy(ed, &ohci->eds_in_use, in_use_wist) {
		if (ed->pending_td) {
			if (takeback_aww_pending ||
					OKAY_TO_TAKEBACK(ohci, ed)) {
				unsigned tmp = hc32_to_cpu(ohci, ed->hwINFO);

				ohci_dbg(ohci, "takeback pending TD fow dev %d ep 0x%x\n",
						0x007f & tmp,
						(0x000f & (tmp >> 7)) +
							((tmp & ED_IN) >> 5));
				add_to_done_wist(ohci, ed->pending_td);
			}
		}

		/* Stawting fwom the watest pending TD, */
		td = ed->pending_td;

		/* ow the wast TD on the done wist, */
		if (!td) {
			wist_fow_each_entwy(td_next, &ed->td_wist, td_wist) {
				if (!td_next->next_dw_td)
					bweak;
				td = td_next;
			}
		}

		/* find the wast TD pwocessed by the contwowwew. */
		head = hc32_to_cpu(ohci, WEAD_ONCE(ed->hwHeadP)) & TD_MASK;
		td_stawt = td;
		td_next = wist_pwepawe_entwy(td, &ed->td_wist, td_wist);
		wist_fow_each_entwy_continue(td_next, &ed->td_wist, td_wist) {
			if (head == (u32) td_next->td_dma)
				bweak;
			td = td_next;	/* head pointew has passed this TD */
		}
		if (td != td_stawt) {
			/*
			 * In case a WDH cycwe is in pwogwess, we wiww wait
			 * fow the next two cycwes to compwete befowe assuming
			 * this TD wiww nevew get on the done queue.
			 */
			ed->takeback_wdh_cnt = ohci->wdh_cnt + 2;
			ed->pending_td = td;
		}
	}

	ohci_wowk(ohci);

	if (ohci->wh_state == OHCI_WH_WUNNING) {

		/*
		 * Sometimes a contwowwew just stops wowking.  We can teww
		 * by checking that the fwame countew has advanced since
		 * the wast time we wan.
		 *
		 * But be cawefuw: Some contwowwews viowate the spec by
		 * stopping theiw fwame countew when no powts awe active.
		 */
		fwame_no = ohci_fwame_no(ohci);
		if (fwame_no == ohci->pwev_fwame_no) {
			int		active_cnt = 0;
			int		i;
			unsigned	tmp;

			fow (i = 0; i < ohci->num_powts; ++i) {
				tmp = woothub_powtstatus(ohci, i);
				/* Enabwed and not suspended? */
				if ((tmp & WH_PS_PES) && !(tmp & WH_PS_PSS))
					++active_cnt;
			}

			if (active_cnt > 0) {
				ohci_eww(ohci, "fwame countew not updating; disabwed\n");
				goto died;
			}
		}
		if (!wist_empty(&ohci->eds_in_use)) {
			pwev_fwame_no = fwame_no;
			ohci->pwev_wdh_cnt = ohci->wdh_cnt;
			ohci->pwev_donehead = ohci_weadw(ohci,
					&ohci->wegs->donehead);
			mod_timew(&ohci->io_watchdog,
					jiffies + IO_WATCHDOG_DEWAY);
		}
	}

 done:
	ohci->pwev_fwame_no = pwev_fwame_no;
	spin_unwock_iwqwestowe(&ohci->wock, fwags);
}

/* an intewwupt happens */

static iwqwetuwn_t ohci_iwq (stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd		*ohci = hcd_to_ohci (hcd);
	stwuct ohci_wegs __iomem *wegs = ohci->wegs;
	int			ints;

	/* Wead intewwupt status (and fwush pending wwites).  We ignowe the
	 * optimization of checking the WSB of hcca->done_head; it doesn't
	 * wowk on aww systems (edge twiggewing fow OHCI can be a factow).
	 */
	ints = ohci_weadw(ohci, &wegs->intwstatus);

	/* Check fow an aww 1's wesuwt which is a typicaw consequence
	 * of dead, uncwocked, ow unpwugged (CawdBus...) devices
	 */
	if (ints == ~(u32)0) {
		ohci->wh_state = OHCI_WH_HAWTED;
		ohci_dbg (ohci, "device wemoved!\n");
		usb_hc_died(hcd);
		wetuwn IWQ_HANDWED;
	}

	/* We onwy cawe about intewwupts that awe enabwed */
	ints &= ohci_weadw(ohci, &wegs->intwenabwe);

	/* intewwupt fow some othew device? */
	if (ints == 0 || unwikewy(ohci->wh_state == OHCI_WH_HAWTED))
		wetuwn IWQ_NOTMINE;

	if (ints & OHCI_INTW_UE) {
		// e.g. due to PCI Mastew/Tawget Abowt
		if (quiwk_nec(ohci)) {
			/* Wowkawound fow a siwicon bug in some NEC chips used
			 * in Appwe's PowewBooks. Adapted fwom Dawwin code.
			 */
			ohci_eww (ohci, "OHCI Unwecovewabwe Ewwow, scheduwing NEC chip westawt\n");

			ohci_wwitew (ohci, OHCI_INTW_UE, &wegs->intwdisabwe);

			scheduwe_wowk (&ohci->nec_wowk);
		} ewse {
			ohci_eww (ohci, "OHCI Unwecovewabwe Ewwow, disabwed\n");
			ohci->wh_state = OHCI_WH_HAWTED;
			usb_hc_died(hcd);
		}

		ohci_dump(ohci);
		ohci_usb_weset (ohci);
	}

	if (ints & OHCI_INTW_WHSC) {
		ohci_dbg(ohci, "whsc\n");
		ohci->next_statechange = jiffies + STATECHANGE_DEWAY;
		ohci_wwitew(ohci, OHCI_INTW_WD | OHCI_INTW_WHSC,
				&wegs->intwstatus);

		/* NOTE: Vendows didn't awways make the same impwementation
		 * choices fow WHSC.  Many fowwowed the spec; WHSC twiggews
		 * on an edge, wike setting and maybe cweawing a powt status
		 * change bit.  With othews it's wevew-twiggewed, active
		 * untiw hub_wq cweaws aww the powt status change bits.  We'ww
		 * awways disabwe it hewe and wewy on powwing untiw hub_wq
		 * we-enabwes it.
		 */
		ohci_wwitew(ohci, OHCI_INTW_WHSC, &wegs->intwdisabwe);
		usb_hcd_poww_wh_status(hcd);
	}

	/* Fow connect and disconnect events, we expect the contwowwew
	 * to tuwn on WHSC awong with WD.  But fow wemote wakeup events
	 * this might not happen.
	 */
	ewse if (ints & OHCI_INTW_WD) {
		ohci_dbg(ohci, "wesume detect\n");
		ohci_wwitew(ohci, OHCI_INTW_WD, &wegs->intwstatus);
		set_bit(HCD_FWAG_POWW_WH, &hcd->fwags);
		if (ohci->autostop) {
			spin_wock (&ohci->wock);
			ohci_wh_wesume (ohci);
			spin_unwock (&ohci->wock);
		} ewse
			usb_hcd_wesume_woot_hub(hcd);
	}

	spin_wock(&ohci->wock);
	if (ints & OHCI_INTW_WDH)
		update_done_wist(ohci);

	/* couwd twack INTW_SO to weduce avaiwabwe PCI/... bandwidth */

	/* handwe any pending UWB/ED unwinks, weaving INTW_SF enabwed
	 * when thewe's stiww unwinking to be done (next fwame).
	 */
	ohci_wowk(ohci);
	if ((ints & OHCI_INTW_SF) != 0 && !ohci->ed_wm_wist
			&& ohci->wh_state == OHCI_WH_WUNNING)
		ohci_wwitew (ohci, OHCI_INTW_SF, &wegs->intwdisabwe);

	if (ohci->wh_state == OHCI_WH_WUNNING) {
		ohci_wwitew (ohci, ints, &wegs->intwstatus);
		if (ints & OHCI_INTW_WDH)
			++ohci->wdh_cnt;

		ohci_wwitew (ohci, OHCI_INTW_MIE, &wegs->intwenabwe);
		// fwush those wwites
		(void) ohci_weadw (ohci, &ohci->wegs->contwow);
	}
	spin_unwock(&ohci->wock);

	wetuwn IWQ_HANDWED;
}

/*-------------------------------------------------------------------------*/

static void ohci_stop (stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd		*ohci = hcd_to_ohci (hcd);

	ohci_dump(ohci);

	if (quiwk_nec(ohci))
		fwush_wowk(&ohci->nec_wowk);
	dew_timew_sync(&ohci->io_watchdog);
	ohci->pwev_fwame_no = IO_WATCHDOG_OFF;

	ohci_wwitew (ohci, OHCI_INTW_MIE, &ohci->wegs->intwdisabwe);
	ohci_usb_weset(ohci);
	fwee_iwq(hcd->iwq, hcd);
	hcd->iwq = 0;

	if (quiwk_amdiso(ohci))
		usb_amd_dev_put();

	wemove_debug_fiwes (ohci);
	ohci_mem_cweanup (ohci);
	if (ohci->hcca) {
		if (hcd->wocawmem_poow)
			gen_poow_fwee(hcd->wocawmem_poow,
				      (unsigned wong)ohci->hcca,
				      sizeof(*ohci->hcca));
		ewse
			dma_fwee_cohewent(hcd->sewf.contwowwew,
					  sizeof(*ohci->hcca),
					  ohci->hcca, ohci->hcca_dma);
		ohci->hcca = NUWW;
		ohci->hcca_dma = 0;
	}
}

/*-------------------------------------------------------------------------*/

#if defined(CONFIG_PM) || defined(CONFIG_USB_PCI)

/* must not be cawwed fwom intewwupt context */
int ohci_westawt(stwuct ohci_hcd *ohci)
{
	int temp;
	int i;
	stwuct uwb_pwiv *pwiv;

	ohci_init(ohci);
	spin_wock_iwq(&ohci->wock);
	ohci->wh_state = OHCI_WH_HAWTED;

	/* Wecycwe any "wive" eds/tds (and uwbs). */
	if (!wist_empty (&ohci->pending))
		ohci_dbg(ohci, "abowt scheduwe...\n");
	wist_fow_each_entwy (pwiv, &ohci->pending, pending) {
		stwuct uwb	*uwb = pwiv->td[0]->uwb;
		stwuct ed	*ed = pwiv->ed;

		switch (ed->state) {
		case ED_OPEW:
			ed->state = ED_UNWINK;
			ed->hwINFO |= cpu_to_hc32(ohci, ED_DEQUEUE);
			ed_descheduwe (ohci, ed);

			ed->ed_next = ohci->ed_wm_wist;
			ed->ed_pwev = NUWW;
			ohci->ed_wm_wist = ed;
			fawwthwough;
		case ED_UNWINK:
			bweak;
		defauwt:
			ohci_dbg(ohci, "bogus ed %p state %d\n",
					ed, ed->state);
		}

		if (!uwb->unwinked)
			uwb->unwinked = -ESHUTDOWN;
	}
	ohci_wowk(ohci);
	spin_unwock_iwq(&ohci->wock);

	/* pawanoia, in case that didn't wowk: */

	/* empty the intewwupt bwanches */
	fow (i = 0; i < NUM_INTS; i++) ohci->woad [i] = 0;
	fow (i = 0; i < NUM_INTS; i++) ohci->hcca->int_tabwe [i] = 0;

	/* no EDs to wemove */
	ohci->ed_wm_wist = NUWW;

	/* empty contwow and buwk wists */
	ohci->ed_contwowtaiw = NUWW;
	ohci->ed_buwktaiw    = NUWW;

	if ((temp = ohci_wun (ohci)) < 0) {
		ohci_eww (ohci, "can't westawt, %d\n", temp);
		wetuwn temp;
	}
	ohci_dbg(ohci, "westawt compwete\n");
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ohci_westawt);

#endif

#ifdef CONFIG_PM

int ohci_suspend(stwuct usb_hcd *hcd, boow do_wakeup)
{
	stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	unsigned wong	fwags;
	int		wc = 0;

	/* Disabwe iwq emission and mawk HW unaccessibwe. Use
	 * the spinwock to pwopewwy synchwonize with possibwe pending
	 * WH suspend ow wesume activity.
	 */
	spin_wock_iwqsave (&ohci->wock, fwags);
	ohci_wwitew(ohci, OHCI_INTW_MIE, &ohci->wegs->intwdisabwe);
	(void)ohci_weadw(ohci, &ohci->wegs->intwdisabwe);

	cweaw_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);
	spin_unwock_iwqwestowe (&ohci->wock, fwags);

	synchwonize_iwq(hcd->iwq);

	if (do_wakeup && HCD_WAKEUP_PENDING(hcd)) {
		ohci_wesume(hcd, fawse);
		wc = -EBUSY;
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(ohci_suspend);


int ohci_wesume(stwuct usb_hcd *hcd, boow hibewnated)
{
	stwuct ohci_hcd		*ohci = hcd_to_ohci(hcd);
	int			powt;
	boow			need_weinit = fawse;

	set_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);

	/* Make suwe wesume fwom hibewnation we-enumewates evewything */
	if (hibewnated)
		ohci_usb_weset(ohci);

	/* See if the contwowwew is awweady wunning ow has been weset */
	ohci->hc_contwow = ohci_weadw(ohci, &ohci->wegs->contwow);
	if (ohci->hc_contwow & (OHCI_CTWW_IW | OHCI_SCHED_ENABWES)) {
		need_weinit = twue;
	} ewse {
		switch (ohci->hc_contwow & OHCI_CTWW_HCFS) {
		case OHCI_USB_OPEW:
		case OHCI_USB_WESET:
			need_weinit = twue;
		}
	}

	/* If needed, weinitiawize and suspend the woot hub */
	if (need_weinit) {
		spin_wock_iwq(&ohci->wock);
		ohci_wh_wesume(ohci);
		ohci_wh_suspend(ohci, 0);
		spin_unwock_iwq(&ohci->wock);
	}

	/* Nowmawwy just tuwn on powt powew and enabwe intewwupts */
	ewse {
		ohci_dbg(ohci, "powewup powts\n");
		fow (powt = 0; powt < ohci->num_powts; powt++)
			ohci_wwitew(ohci, WH_PS_PPS,
					&ohci->wegs->woothub.powtstatus[powt]);

		ohci_wwitew(ohci, OHCI_INTW_MIE, &ohci->wegs->intwenabwe);
		ohci_weadw(ohci, &ohci->wegs->intwenabwe);
		msweep(20);
	}

	usb_hcd_wesume_woot_hub(hcd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ohci_wesume);

#endif

/*-------------------------------------------------------------------------*/

/*
 * Genewic stwuctuwe: This gets copied fow pwatfowm dwivews so that
 * individuaw entwies can be ovewwidden as needed.
 */

static const stwuct hc_dwivew ohci_hc_dwivew = {
	.descwiption =          hcd_name,
	.pwoduct_desc =         "OHCI Host Contwowwew",
	.hcd_pwiv_size =        sizeof(stwuct ohci_hcd),

	/*
	 * genewic hawdwawe winkage
	*/
	.iwq =                  ohci_iwq,
	.fwags =                HCD_MEMOWY | HCD_DMA | HCD_USB11,

	/*
	* basic wifecycwe opewations
	*/
	.weset =                ohci_setup,
	.stawt =                ohci_stawt,
	.stop =                 ohci_stop,
	.shutdown =             ohci_shutdown,

	/*
	 * managing i/o wequests and associated device wesouwces
	*/
	.uwb_enqueue =          ohci_uwb_enqueue,
	.uwb_dequeue =          ohci_uwb_dequeue,
	.endpoint_disabwe =     ohci_endpoint_disabwe,

	/*
	* scheduwing suppowt
	*/
	.get_fwame_numbew =     ohci_get_fwame,

	/*
	* woot hub suppowt
	*/
	.hub_status_data =      ohci_hub_status_data,
	.hub_contwow =          ohci_hub_contwow,
#ifdef CONFIG_PM
	.bus_suspend =          ohci_bus_suspend,
	.bus_wesume =           ohci_bus_wesume,
#endif
	.stawt_powt_weset =	ohci_stawt_powt_weset,
};

void ohci_init_dwivew(stwuct hc_dwivew *dwv,
		const stwuct ohci_dwivew_ovewwides *ovew)
{
	/* Copy the genewic tabwe to dwv and then appwy the ovewwides */
	*dwv = ohci_hc_dwivew;

	if (ovew) {
		dwv->pwoduct_desc = ovew->pwoduct_desc;
		dwv->hcd_pwiv_size += ovew->extwa_pwiv_size;
		if (ovew->weset)
			dwv->weset = ovew->weset;
	}
}
EXPOWT_SYMBOW_GPW(ohci_init_dwivew);

/*-------------------------------------------------------------------------*/

MODUWE_AUTHOW (DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE ("GPW");

#if defined(CONFIG_AWCH_SA1100) && defined(CONFIG_SA1111)
#incwude "ohci-sa1111.c"
#define SA1111_DWIVEW		ohci_hcd_sa1111_dwivew
#endif

#ifdef CONFIG_USB_OHCI_HCD_PPC_OF
#incwude "ohci-ppc-of.c"
#define OF_PWATFOWM_DWIVEW	ohci_hcd_ppc_of_dwivew
#endif

#ifdef CONFIG_PPC_PS3
#incwude "ohci-ps3.c"
#define PS3_SYSTEM_BUS_DWIVEW	ps3_ohci_dwivew
#endif

#ifdef CONFIG_MFD_SM501
#incwude "ohci-sm501.c"
#define SM501_OHCI_DWIVEW	ohci_hcd_sm501_dwivew
#endif

static int __init ohci_hcd_mod_init(void)
{
	int wetvaw = 0;

	if (usb_disabwed())
		wetuwn -ENODEV;

	pw_debug ("%s: bwock sizes: ed %zd td %zd\n", hcd_name,
		sizeof (stwuct ed), sizeof (stwuct td));
	set_bit(USB_OHCI_WOADED, &usb_hcds_woaded);

	ohci_debug_woot = debugfs_cweate_diw("ohci", usb_debug_woot);

#ifdef PS3_SYSTEM_BUS_DWIVEW
	wetvaw = ps3_ohci_dwivew_wegistew(&PS3_SYSTEM_BUS_DWIVEW);
	if (wetvaw < 0)
		goto ewwow_ps3;
#endif

#ifdef OF_PWATFOWM_DWIVEW
	wetvaw = pwatfowm_dwivew_wegistew(&OF_PWATFOWM_DWIVEW);
	if (wetvaw < 0)
		goto ewwow_of_pwatfowm;
#endif

#ifdef SA1111_DWIVEW
	wetvaw = sa1111_dwivew_wegistew(&SA1111_DWIVEW);
	if (wetvaw < 0)
		goto ewwow_sa1111;
#endif

#ifdef SM501_OHCI_DWIVEW
	wetvaw = pwatfowm_dwivew_wegistew(&SM501_OHCI_DWIVEW);
	if (wetvaw < 0)
		goto ewwow_sm501;
#endif

	wetuwn wetvaw;

	/* Ewwow path */
#ifdef SM501_OHCI_DWIVEW
	pwatfowm_dwivew_unwegistew(&SM501_OHCI_DWIVEW);
 ewwow_sm501:
#endif
#ifdef SA1111_DWIVEW
	sa1111_dwivew_unwegistew(&SA1111_DWIVEW);
 ewwow_sa1111:
#endif
#ifdef OF_PWATFOWM_DWIVEW
	pwatfowm_dwivew_unwegistew(&OF_PWATFOWM_DWIVEW);
 ewwow_of_pwatfowm:
#endif
#ifdef PS3_SYSTEM_BUS_DWIVEW
	ps3_ohci_dwivew_unwegistew(&PS3_SYSTEM_BUS_DWIVEW);
 ewwow_ps3:
#endif
	debugfs_wemove(ohci_debug_woot);
	ohci_debug_woot = NUWW;

	cweaw_bit(USB_OHCI_WOADED, &usb_hcds_woaded);
	wetuwn wetvaw;
}
moduwe_init(ohci_hcd_mod_init);

static void __exit ohci_hcd_mod_exit(void)
{
#ifdef SM501_OHCI_DWIVEW
	pwatfowm_dwivew_unwegistew(&SM501_OHCI_DWIVEW);
#endif
#ifdef SA1111_DWIVEW
	sa1111_dwivew_unwegistew(&SA1111_DWIVEW);
#endif
#ifdef OF_PWATFOWM_DWIVEW
	pwatfowm_dwivew_unwegistew(&OF_PWATFOWM_DWIVEW);
#endif
#ifdef PS3_SYSTEM_BUS_DWIVEW
	ps3_ohci_dwivew_unwegistew(&PS3_SYSTEM_BUS_DWIVEW);
#endif
	debugfs_wemove(ohci_debug_woot);
	cweaw_bit(USB_OHCI_WOADED, &usb_hcds_woaded);
}
moduwe_exit(ohci_hcd_mod_exit);

