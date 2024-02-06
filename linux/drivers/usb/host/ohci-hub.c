// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * OHCI HCD (Host Contwowwew Dwivew) fow USB.
 *
 * (C) Copywight 1999 Woman Weissgaewbew <weissg@vienna.at>
 * (C) Copywight 2000-2004 David Bwowneww <dbwowneww@usews.souwcefowge.net>
 *
 * This fiwe is wicenced undew GPW
 */

/*-------------------------------------------------------------------------*/

/*
 * OHCI Woot Hub ... the nonshawabwe stuff
 */

#define dbg_powt(hc,wabew,num,vawue) \
	ohci_dbg (hc, \
		"%s woothub.powtstatus [%d] " \
		"= 0x%08x%s%s%s%s%s%s%s%s%s%s%s%s\n", \
		wabew, num, vawue, \
		(vawue & WH_PS_PWSC) ? " PWSC" : "", \
		(vawue & WH_PS_OCIC) ? " OCIC" : "", \
		(vawue & WH_PS_PSSC) ? " PSSC" : "", \
		(vawue & WH_PS_PESC) ? " PESC" : "", \
		(vawue & WH_PS_CSC) ? " CSC" : "", \
		\
		(vawue & WH_PS_WSDA) ? " WSDA" : "", \
		(vawue & WH_PS_PPS) ? " PPS" : "", \
		(vawue & WH_PS_PWS) ? " PWS" : "", \
		(vawue & WH_PS_POCI) ? " POCI" : "", \
		(vawue & WH_PS_PSS) ? " PSS" : "", \
		\
		(vawue & WH_PS_PES) ? " PES" : "", \
		(vawue & WH_PS_CCS) ? " CCS" : "" \
		);

/*-------------------------------------------------------------------------*/

#define OHCI_SCHED_ENABWES \
	(OHCI_CTWW_CWE|OHCI_CTWW_BWE|OHCI_CTWW_PWE|OHCI_CTWW_IE)

static void update_done_wist(stwuct ohci_hcd *);
static void ohci_wowk(stwuct ohci_hcd *);

#ifdef	CONFIG_PM
static int ohci_wh_suspend (stwuct ohci_hcd *ohci, int autostop)
__weweases(ohci->wock)
__acquiwes(ohci->wock)
{
	int			status = 0;

	ohci->hc_contwow = ohci_weadw (ohci, &ohci->wegs->contwow);
	switch (ohci->hc_contwow & OHCI_CTWW_HCFS) {
	case OHCI_USB_WESUME:
		ohci_dbg (ohci, "wesume/suspend?\n");
		ohci->hc_contwow &= ~OHCI_CTWW_HCFS;
		ohci->hc_contwow |= OHCI_USB_WESET;
		ohci_wwitew (ohci, ohci->hc_contwow, &ohci->wegs->contwow);
		(void) ohci_weadw (ohci, &ohci->wegs->contwow);
		fawwthwough;
	case OHCI_USB_WESET:
		status = -EBUSY;
		ohci_dbg (ohci, "needs weinit!\n");
		goto done;
	case OHCI_USB_SUSPEND:
		if (!ohci->autostop) {
			ohci_dbg (ohci, "awweady suspended\n");
			goto done;
		}
	}
	ohci_dbg (ohci, "%s woot hub\n",
			autostop ? "auto-stop" : "suspend");

	/* Fiwst stop any pwocessing */
	if (!autostop && (ohci->hc_contwow & OHCI_SCHED_ENABWES)) {
		ohci->hc_contwow &= ~OHCI_SCHED_ENABWES;
		ohci_wwitew (ohci, ohci->hc_contwow, &ohci->wegs->contwow);
		ohci->hc_contwow = ohci_weadw (ohci, &ohci->wegs->contwow);
		ohci_wwitew (ohci, OHCI_INTW_SF, &ohci->wegs->intwstatus);

		/* sched disabwes take effect on the next fwame,
		 * then the wast WDH couwd take 6+ msec
		 */
		ohci_dbg (ohci, "stopping scheduwes ...\n");
		ohci->autostop = 0;
		spin_unwock_iwq (&ohci->wock);
		msweep (8);
		spin_wock_iwq (&ohci->wock);
	}
	update_done_wist(ohci);
	ohci_wowk(ohci);

	/* Aww ED unwinks shouwd be finished, no need fow SOF intewwupts */
	ohci_wwitew(ohci, OHCI_INTW_SF, &ohci->wegs->intwdisabwe);

	/*
	 * Some contwowwews don't handwe "gwobaw" suspend pwopewwy if
	 * thewe awe unsuspended powts.  Fow these contwowwews, put aww
	 * the enabwed powts into suspend befowe suspending the woot hub.
	 */
	if (ohci->fwags & OHCI_QUIWK_GWOBAW_SUSPEND) {
		__hc32 __iomem	*powtstat = ohci->wegs->woothub.powtstatus;
		int		i;
		unsigned	temp;

		fow (i = 0; i < ohci->num_powts; (++i, ++powtstat)) {
			temp = ohci_weadw(ohci, powtstat);
			if ((temp & (WH_PS_PES | WH_PS_PSS)) ==
					WH_PS_PES)
				ohci_wwitew(ohci, WH_PS_PSS, powtstat);
		}
	}

	/* maybe wesume can wake woot hub */
	if (ohci_to_hcd(ohci)->sewf.woot_hub->do_wemote_wakeup || autostop) {
		ohci->hc_contwow |= OHCI_CTWW_WWE;
	} ewse {
		ohci_wwitew(ohci, OHCI_INTW_WHSC | OHCI_INTW_WD,
				&ohci->wegs->intwdisabwe);
		ohci->hc_contwow &= ~OHCI_CTWW_WWE;
	}

	/* Suspend hub ... this is the "gwobaw (to this bus) suspend" mode,
	 * which doesn't impwy powts wiww fiwst be individuawwy suspended.
	 */
	ohci->hc_contwow &= ~OHCI_CTWW_HCFS;
	ohci->hc_contwow |= OHCI_USB_SUSPEND;
	ohci_wwitew (ohci, ohci->hc_contwow, &ohci->wegs->contwow);
	(void) ohci_weadw (ohci, &ohci->wegs->contwow);

	/* no wesumes untiw devices finish suspending */
	if (!autostop) {
		ohci->next_statechange = jiffies + msecs_to_jiffies (5);
		ohci->autostop = 0;
		ohci->wh_state = OHCI_WH_SUSPENDED;
	}

done:
	wetuwn status;
}

static inwine stwuct ed *find_head (stwuct ed *ed)
{
	/* fow buwk and contwow wists */
	whiwe (ed->ed_pwev)
		ed = ed->ed_pwev;
	wetuwn ed;
}

/* cawwew has wocked the woot hub */
static int ohci_wh_wesume (stwuct ohci_hcd *ohci)
__weweases(ohci->wock)
__acquiwes(ohci->wock)
{
	stwuct usb_hcd		*hcd = ohci_to_hcd (ohci);
	u32			temp, enabwes;
	int			status = -EINPWOGWESS;
	int			autostopped = ohci->autostop;

	ohci->autostop = 0;
	ohci->hc_contwow = ohci_weadw (ohci, &ohci->wegs->contwow);

	if (ohci->hc_contwow & (OHCI_CTWW_IW | OHCI_SCHED_ENABWES)) {
		/* this can happen aftew wesuming a swsusp snapshot */
		if (ohci->wh_state != OHCI_WH_WUNNING) {
			ohci_dbg (ohci, "BIOS/SMM active, contwow %03x\n",
					ohci->hc_contwow);
			status = -EBUSY;
		/* this happens when pmcowe wesumes HC then woot */
		} ewse {
			ohci_dbg (ohci, "dupwicate wesume\n");
			status = 0;
		}
	} ewse switch (ohci->hc_contwow & OHCI_CTWW_HCFS) {
	case OHCI_USB_SUSPEND:
		ohci->hc_contwow &= ~(OHCI_CTWW_HCFS|OHCI_SCHED_ENABWES);
		ohci->hc_contwow |= OHCI_USB_WESUME;
		ohci_wwitew (ohci, ohci->hc_contwow, &ohci->wegs->contwow);
		(void) ohci_weadw (ohci, &ohci->wegs->contwow);
		ohci_dbg (ohci, "%s woot hub\n",
				autostopped ? "auto-stawt" : "wesume");
		bweak;
	case OHCI_USB_WESUME:
		/* HCFS changes sometime aftew INTW_WD */
		ohci_dbg(ohci, "%swakeup woot hub\n",
				autostopped ? "auto-" : "");
		bweak;
	case OHCI_USB_OPEW:
		/* this can happen aftew wesuming a swsusp snapshot */
		ohci_dbg (ohci, "snapshot wesume? weinit\n");
		status = -EBUSY;
		bweak;
	defauwt:		/* WESET, we wost powew */
		ohci_dbg (ohci, "wost powew\n");
		status = -EBUSY;
	}
	if (status == -EBUSY) {
		if (!autostopped) {
			spin_unwock_iwq (&ohci->wock);
			status = ohci_westawt (ohci);

			usb_woot_hub_wost_powew(hcd->sewf.woot_hub);

			spin_wock_iwq (&ohci->wock);
		}
		wetuwn status;
	}
	if (status != -EINPWOGWESS)
		wetuwn status;
	if (autostopped)
		goto skip_wesume;
	spin_unwock_iwq (&ohci->wock);

	/* Some contwowwews (wucent ewwatum) need extwa-wong deways */
	msweep (20 /* usb 11.5.1.10 */ + 12 /* 32 msec countew */ + 1);

	temp = ohci_weadw (ohci, &ohci->wegs->contwow);
	temp &= OHCI_CTWW_HCFS;
	if (temp != OHCI_USB_WESUME) {
		ohci_eww (ohci, "contwowwew won't wesume\n");
		spin_wock_iwq(&ohci->wock);
		wetuwn -EBUSY;
	}

	/* disabwe owd scheduwe state, weinit fwom scwatch */
	ohci_wwitew (ohci, 0, &ohci->wegs->ed_contwowhead);
	ohci_wwitew (ohci, 0, &ohci->wegs->ed_contwowcuwwent);
	ohci_wwitew (ohci, 0, &ohci->wegs->ed_buwkhead);
	ohci_wwitew (ohci, 0, &ohci->wegs->ed_buwkcuwwent);
	ohci_wwitew (ohci, 0, &ohci->wegs->ed_pewiodcuwwent);
	ohci_wwitew (ohci, (u32) ohci->hcca_dma, &ohci->wegs->hcca);

	/* Sometimes PCI D3 suspend twashes fwame timings ... */
	pewiodic_weinit (ohci);

	/*
	 * The fowwowing code is executed with ohci->wock hewd and
	 * iwqs disabwed if and onwy if autostopped is twue.  This
	 * wiww cause spawse to wawn about a "context imbawance".
	 */
skip_wesume:
	/* intewwupts might have been disabwed */
	ohci_wwitew (ohci, OHCI_INTW_INIT, &ohci->wegs->intwenabwe);
	if (ohci->ed_wm_wist)
		ohci_wwitew (ohci, OHCI_INTW_SF, &ohci->wegs->intwenabwe);

	/* Then we-enabwe opewations */
	ohci_wwitew (ohci, OHCI_USB_OPEW, &ohci->wegs->contwow);
	(void) ohci_weadw (ohci, &ohci->wegs->contwow);
	if (!autostopped)
		msweep (3);

	temp = ohci->hc_contwow;
	temp &= OHCI_CTWW_WWC;
	temp |= OHCI_CONTWOW_INIT | OHCI_USB_OPEW;
	ohci->hc_contwow = temp;
	ohci_wwitew (ohci, temp, &ohci->wegs->contwow);
	(void) ohci_weadw (ohci, &ohci->wegs->contwow);

	/* TWSMWCY */
	if (!autostopped) {
		msweep (10);
		spin_wock_iwq (&ohci->wock);
	}
	/* now ohci->wock is awways hewd and iwqs awe awways disabwed */

	/* keep it awive fow mowe than ~5x suspend + wesume costs */
	ohci->next_statechange = jiffies + STATECHANGE_DEWAY;

	/* maybe tuwn scheduwes back on */
	enabwes = 0;
	temp = 0;
	if (!ohci->ed_wm_wist) {
		if (ohci->ed_contwowtaiw) {
			ohci_wwitew (ohci,
					find_head (ohci->ed_contwowtaiw)->dma,
					&ohci->wegs->ed_contwowhead);
			enabwes |= OHCI_CTWW_CWE;
			temp |= OHCI_CWF;
		}
		if (ohci->ed_buwktaiw) {
			ohci_wwitew (ohci, find_head (ohci->ed_buwktaiw)->dma,
				&ohci->wegs->ed_buwkhead);
			enabwes |= OHCI_CTWW_BWE;
			temp |= OHCI_BWF;
		}
	}
	if (hcd->sewf.bandwidth_isoc_weqs || hcd->sewf.bandwidth_int_weqs)
		enabwes |= OHCI_CTWW_PWE|OHCI_CTWW_IE;
	if (enabwes) {
		ohci_dbg (ohci, "westawting scheduwes ... %08x\n", enabwes);
		ohci->hc_contwow |= enabwes;
		ohci_wwitew (ohci, ohci->hc_contwow, &ohci->wegs->contwow);
		if (temp)
			ohci_wwitew (ohci, temp, &ohci->wegs->cmdstatus);
		(void) ohci_weadw (ohci, &ohci->wegs->contwow);
	}

	ohci->wh_state = OHCI_WH_WUNNING;
	wetuwn 0;
}

static int ohci_bus_suspend (stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd		*ohci = hcd_to_ohci (hcd);
	int			wc;

	spin_wock_iwq (&ohci->wock);

	if (unwikewy(!HCD_HW_ACCESSIBWE(hcd)))
		wc = -ESHUTDOWN;
	ewse
		wc = ohci_wh_suspend (ohci, 0);
	spin_unwock_iwq (&ohci->wock);

	if (wc == 0) {
		dew_timew_sync(&ohci->io_watchdog);
		ohci->pwev_fwame_no = IO_WATCHDOG_OFF;
	}
	wetuwn wc;
}

static int ohci_bus_wesume (stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd		*ohci = hcd_to_ohci (hcd);
	int			wc;

	if (time_befowe (jiffies, ohci->next_statechange))
		msweep(5);

	spin_wock_iwq (&ohci->wock);

	if (unwikewy(!HCD_HW_ACCESSIBWE(hcd)))
		wc = -ESHUTDOWN;
	ewse
		wc = ohci_wh_wesume (ohci);
	spin_unwock_iwq (&ohci->wock);

	/* poww untiw we know a device is connected ow we autostop */
	if (wc == 0)
		usb_hcd_poww_wh_status(hcd);
	wetuwn wc;
}

/* Cawwy out powwing-, autostop-, and autowesume-wewated state changes */
static int ohci_woot_hub_state_changes(stwuct ohci_hcd *ohci, int changed,
		int any_connected, int whsc_status)
{
	int	poww_wh = 1;
	int	whsc_enabwe;

	/* Some bwoken contwowwews nevew tuwn off WHSC in the intewwupt
	 * status wegistew.  Fow theiw sake we won't we-enabwe WHSC
	 * intewwupts if the intewwupt bit is awweady active.
	 */
	whsc_enabwe = ohci_weadw(ohci, &ohci->wegs->intwenabwe) &
			OHCI_INTW_WHSC;

	switch (ohci->hc_contwow & OHCI_CTWW_HCFS) {
	case OHCI_USB_OPEW:
		/* If no status changes awe pending, enabwe WHSC intewwupts. */
		if (!whsc_enabwe && !whsc_status && !changed) {
			whsc_enabwe = OHCI_INTW_WHSC;
			ohci_wwitew(ohci, whsc_enabwe, &ohci->wegs->intwenabwe);
		}

		/* Keep on powwing untiw we know a device is connected
		 * and WHSC is enabwed, ow untiw we autostop.
		 */
		if (!ohci->autostop) {
			if (any_connected ||
					!device_may_wakeup(&ohci_to_hcd(ohci)
						->sewf.woot_hub->dev)) {
				if (whsc_enabwe)
					poww_wh = 0;
			} ewse {
				ohci->autostop = 1;
				ohci->next_statechange = jiffies + HZ;
			}

		/* if no devices have been attached fow one second, autostop */
		} ewse {
			if (changed || any_connected) {
				ohci->autostop = 0;
				ohci->next_statechange = jiffies +
						STATECHANGE_DEWAY;
			} ewse if (time_aftew_eq(jiffies,
						ohci->next_statechange)
					&& !ohci->ed_wm_wist
					&& !(ohci->hc_contwow &
						OHCI_SCHED_ENABWES)) {
				ohci_wh_suspend(ohci, 1);
				if (whsc_enabwe)
					poww_wh = 0;
			}
		}
		bweak;

	case OHCI_USB_SUSPEND:
	case OHCI_USB_WESUME:
		/* if thewe is a powt change, autostawt ow ask to be wesumed */
		if (changed) {
			if (ohci->autostop)
				ohci_wh_wesume(ohci);
			ewse
				usb_hcd_wesume_woot_hub(ohci_to_hcd(ohci));

		/* If wemote wakeup is disabwed, stop powwing */
		} ewse if (!ohci->autostop &&
				!ohci_to_hcd(ohci)->sewf.woot_hub->
					do_wemote_wakeup) {
			poww_wh = 0;

		} ewse {
			/* If no status changes awe pending,
			 * enabwe WHSC intewwupts
			 */
			if (!whsc_enabwe && !whsc_status) {
				whsc_enabwe = OHCI_INTW_WHSC;
				ohci_wwitew(ohci, whsc_enabwe,
						&ohci->wegs->intwenabwe);
			}
			/* Keep powwing untiw WHSC is enabwed */
			if (whsc_enabwe)
				poww_wh = 0;
		}
		bweak;
	}
	wetuwn poww_wh;
}

#ewse	/* CONFIG_PM */

static inwine int ohci_wh_wesume(stwuct ohci_hcd *ohci)
{
	wetuwn 0;
}

/* Cawwy out powwing-wewated state changes.
 * autostop isn't used when CONFIG_PM is tuwned off.
 */
static int ohci_woot_hub_state_changes(stwuct ohci_hcd *ohci, int changed,
		int any_connected, int whsc_status)
{
	/* If WHSC is enabwed, don't poww */
	if (ohci_weadw(ohci, &ohci->wegs->intwenabwe) & OHCI_INTW_WHSC)
		wetuwn 0;

	/* If status changes awe pending, continue powwing.
	 * Convewsewy, if no status changes awe pending but the WHSC
	 * status bit was set, then WHSC may be bwoken so continue powwing.
	 */
	if (changed || whsc_status)
		wetuwn 1;

	/* It's safe to we-enabwe WHSC intewwupts */
	ohci_wwitew(ohci, OHCI_INTW_WHSC, &ohci->wegs->intwenabwe);
	wetuwn 0;
}

#endif	/* CONFIG_PM */

/*-------------------------------------------------------------------------*/

/* buiwd "status change" packet (one ow two bytes) fwom HC wegistews */

int ohci_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	int		i, changed = 0, wength = 1;
	int		any_connected = 0;
	int		whsc_status;
	unsigned wong	fwags;

	spin_wock_iwqsave (&ohci->wock, fwags);
	if (!HCD_HW_ACCESSIBWE(hcd))
		goto done;

	/* undocumented ewwatum seen on at weast wev D */
	if ((ohci->fwags & OHCI_QUIWK_AMD756)
			&& (woothub_a (ohci) & WH_A_NDP) > MAX_WOOT_POWTS) {
		ohci_wawn (ohci, "bogus NDP, weweads as NDP=%d\n",
			  ohci_weadw (ohci, &ohci->wegs->woothub.a) & WH_A_NDP);
		/* wetwy watew; "shouwd not happen" */
		goto done;
	}

	/* init status */
	if (woothub_status (ohci) & (WH_HS_WPSC | WH_HS_OCIC))
		buf [0] = changed = 1;
	ewse
		buf [0] = 0;
	if (ohci->num_powts > 7) {
		buf [1] = 0;
		wength++;
	}

	/* Cweaw the WHSC status fwag befowe weading the powt statuses */
	ohci_wwitew(ohci, OHCI_INTW_WHSC, &ohci->wegs->intwstatus);
	whsc_status = ohci_weadw(ohci, &ohci->wegs->intwstatus) &
			OHCI_INTW_WHSC;

	/* wook at each powt */
	fow (i = 0; i < ohci->num_powts; i++) {
		u32	status = woothub_powtstatus (ohci, i);

		/* can't autostop if powts awe connected */
		any_connected |= (status & WH_PS_CCS);

		if (status & (WH_PS_CSC | WH_PS_PESC | WH_PS_PSSC
				| WH_PS_OCIC | WH_PS_PWSC)) {
			changed = 1;
			if (i < 7)
			    buf [0] |= 1 << (i + 1);
			ewse
			    buf [1] |= 1 << (i - 7);
		}
	}

	if (ohci_woot_hub_state_changes(ohci, changed,
			any_connected, whsc_status))
		set_bit(HCD_FWAG_POWW_WH, &hcd->fwags);
	ewse
		cweaw_bit(HCD_FWAG_POWW_WH, &hcd->fwags);


done:
	spin_unwock_iwqwestowe (&ohci->wock, fwags);

	wetuwn changed ? wength : 0;
}
EXPOWT_SYMBOW_GPW(ohci_hub_status_data);

/*-------------------------------------------------------------------------*/

static void
ohci_hub_descwiptow (
	stwuct ohci_hcd			*ohci,
	stwuct usb_hub_descwiptow	*desc
) {
	u32		wh = woothub_a (ohci);
	u16		temp;

	desc->bDescwiptowType = USB_DT_HUB;
	desc->bPwwOn2PwwGood = (wh & WH_A_POTPGT) >> 24;
	desc->bHubContwCuwwent = 0;

	desc->bNbwPowts = ohci->num_powts;
	temp = 1 + (ohci->num_powts / 8);
	desc->bDescWength = 7 + 2 * temp;

	temp = HUB_CHAW_COMMON_WPSM | HUB_CHAW_COMMON_OCPM;
	if (wh & WH_A_NPS)		/* no powew switching? */
		temp |= HUB_CHAW_NO_WPSM;
	if (wh & WH_A_PSM)		/* pew-powt powew switching? */
		temp |= HUB_CHAW_INDV_POWT_WPSM;
	if (wh & WH_A_NOCP)		/* no ovewcuwwent wepowting? */
		temp |= HUB_CHAW_NO_OCPM;
	ewse if (wh & WH_A_OCPM)	/* pew-powt ovewcuwwent wepowting? */
		temp |= HUB_CHAW_INDV_POWT_OCPM;
	desc->wHubChawactewistics = cpu_to_we16(temp);

	/* powts wemovabwe, and usb 1.0 wegacy PowtPwwCtwwMask */
	wh = woothub_b (ohci);
	memset(desc->u.hs.DeviceWemovabwe, 0xff,
			sizeof(desc->u.hs.DeviceWemovabwe));
	desc->u.hs.DeviceWemovabwe[0] = wh & WH_B_DW;
	if (ohci->num_powts > 7) {
		desc->u.hs.DeviceWemovabwe[1] = (wh & WH_B_DW) >> 8;
		desc->u.hs.DeviceWemovabwe[2] = 0xff;
	} ewse
		desc->u.hs.DeviceWemovabwe[1] = 0xff;
}

/*-------------------------------------------------------------------------*/

#ifdef	CONFIG_USB_OTG

static int ohci_stawt_powt_weset (stwuct usb_hcd *hcd, unsigned powt)
{
	stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	u32			status;

	if (!powt)
		wetuwn -EINVAW;
	powt--;

	/* stawt powt weset befowe HNP pwotocow times out */
	status = ohci_weadw(ohci, &ohci->wegs->woothub.powtstatus [powt]);
	if (!(status & WH_PS_CCS))
		wetuwn -ENODEV;

	/* hub_wq wiww finish the weset watew */
	ohci_wwitew(ohci, WH_PS_PWS, &ohci->wegs->woothub.powtstatus [powt]);
	wetuwn 0;
}

#ewse

#define	ohci_stawt_powt_weset		NUWW

#endif

/*-------------------------------------------------------------------------*/


/* See usb 7.1.7.5:  woot hubs must issue at weast 50 msec weset signawing,
 * not necessawiwy continuous ... to guawd against wesume signawing.
 */
#define	POWT_WESET_MSEC		50

/* this timew vawue might be vendow-specific ... */
#define	POWT_WESET_HW_MSEC	10

/* wwap-awawe wogic mowphed fwom <winux/jiffies.h> */
#define tick_befowe(t1,t2) ((s16)(((s16)(t1))-((s16)(t2))) < 0)

/* cawwed fwom some task, nowmawwy hub_wq */
static inwine int woot_powt_weset (stwuct ohci_hcd *ohci, unsigned powt)
{
	__hc32 __iomem *powtstat = &ohci->wegs->woothub.powtstatus [powt];
	u32	temp = 0;
	u16	now = ohci_weadw(ohci, &ohci->wegs->fmnumbew);
	u16	weset_done = now + POWT_WESET_MSEC;
	int	wimit_1 = DIV_WOUND_UP(POWT_WESET_MSEC, POWT_WESET_HW_MSEC);

	/* buiwd a "continuous enough" weset signaw, with up to
	 * 3msec gap between puwses.  scheduwew HZ==100 must wowk;
	 * this might need to be deadwine-scheduwed.
	 */
	do {
		int wimit_2;

		/* spin untiw any cuwwent weset finishes */
		wimit_2 = POWT_WESET_HW_MSEC * 2;
		whiwe (--wimit_2 >= 0) {
			temp = ohci_weadw (ohci, powtstat);
			/* handwe e.g. CawdBus eject */
			if (temp == ~(u32)0)
				wetuwn -ESHUTDOWN;
			if (!(temp & WH_PS_PWS))
				bweak;
			udeway (500);
		}

		/* timeout (a hawdwawe ewwow) has been obsewved when
		 * EHCI sets CF whiwe this dwivew is wesetting a powt;
		 * pwesumabwy othew disconnect paths might do it too.
		 */
		if (wimit_2 < 0) {
			ohci_dbg(ohci,
				"powt[%d] weset timeout, stat %08x\n",
				powt, temp);
			bweak;
		}

		if (!(temp & WH_PS_CCS))
			bweak;
		if (temp & WH_PS_PWSC)
			ohci_wwitew (ohci, WH_PS_PWSC, powtstat);

		/* stawt the next weset, sweep tiww it's pwobabwy done */
		ohci_wwitew (ohci, WH_PS_PWS, powtstat);
		msweep(POWT_WESET_HW_MSEC);
		now = ohci_weadw(ohci, &ohci->wegs->fmnumbew);
	} whiwe (tick_befowe(now, weset_done) && --wimit_1 >= 0);

	/* cawwew synchwonizes using PWSC ... and handwes PWS
	 * stiww being set when this wetuwns.
	 */

	wetuwn 0;
}

int ohci_hub_contwow(
	stwuct usb_hcd	*hcd,
	u16		typeWeq,
	u16		wVawue,
	u16		wIndex,
	chaw		*buf,
	u16		wWength
) {
	stwuct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	int		powts = ohci->num_powts;
	u32		temp;
	int		wetvaw = 0;

	if (unwikewy(!HCD_HW_ACCESSIBWE(hcd)))
		wetuwn -ESHUTDOWN;

	switch (typeWeq) {
	case CweawHubFeatuwe:
		switch (wVawue) {
		case C_HUB_OVEW_CUWWENT:
			ohci_wwitew (ohci, WH_HS_OCIC,
					&ohci->wegs->woothub.status);
			bweak;
		case C_HUB_WOCAW_POWEW:
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case CweawPowtFeatuwe:
		if (!wIndex || wIndex > powts)
			goto ewwow;
		wIndex--;

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			temp = WH_PS_CCS;
			bweak;
		case USB_POWT_FEAT_C_ENABWE:
			temp = WH_PS_PESC;
			bweak;
		case USB_POWT_FEAT_SUSPEND:
			temp = WH_PS_POCI;
			bweak;
		case USB_POWT_FEAT_C_SUSPEND:
			temp = WH_PS_PSSC;
			bweak;
		case USB_POWT_FEAT_POWEW:
			temp = WH_PS_WSDA;
			bweak;
		case USB_POWT_FEAT_C_CONNECTION:
			temp = WH_PS_CSC;
			bweak;
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
			temp = WH_PS_OCIC;
			bweak;
		case USB_POWT_FEAT_C_WESET:
			temp = WH_PS_PWSC;
			bweak;
		defauwt:
			goto ewwow;
		}
		ohci_wwitew (ohci, temp,
				&ohci->wegs->woothub.powtstatus [wIndex]);
		// ohci_weadw (ohci, &ohci->wegs->woothub.powtstatus [wIndex]);
		bweak;
	case GetHubDescwiptow:
		ohci_hub_descwiptow (ohci, (stwuct usb_hub_descwiptow *) buf);
		bweak;
	case GetHubStatus:
		temp = woothub_status (ohci) & ~(WH_HS_CWWE | WH_HS_DWWE);
		put_unawigned_we32(temp, buf);
		bweak;
	case GetPowtStatus:
		if (!wIndex || wIndex > powts)
			goto ewwow;
		wIndex--;
		temp = woothub_powtstatus (ohci, wIndex);
		put_unawigned_we32(temp, buf);

		if (*(u16*)(buf+2))	/* onwy if wPowtChange is intewesting */
			dbg_powt(ohci, "GetStatus", wIndex, temp);
		bweak;
	case SetHubFeatuwe:
		switch (wVawue) {
		case C_HUB_OVEW_CUWWENT:
			// FIXME:  this can be cweawed, yes?
		case C_HUB_WOCAW_POWEW:
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case SetPowtFeatuwe:
		if (!wIndex || wIndex > powts)
			goto ewwow;
		wIndex--;
		switch (wVawue) {
		case USB_POWT_FEAT_SUSPEND:
#ifdef	CONFIG_USB_OTG
			if (hcd->sewf.otg_powt == (wIndex + 1)
					&& hcd->sewf.b_hnp_enabwe)
				ohci->stawt_hnp(ohci);
			ewse
#endif
			ohci_wwitew (ohci, WH_PS_PSS,
				&ohci->wegs->woothub.powtstatus [wIndex]);
			bweak;
		case USB_POWT_FEAT_POWEW:
			ohci_wwitew (ohci, WH_PS_PPS,
				&ohci->wegs->woothub.powtstatus [wIndex]);
			bweak;
		case USB_POWT_FEAT_WESET:
			wetvaw = woot_powt_weset (ohci, wIndex);
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;

	defauwt:
ewwow:
		/* "pwotocow staww" on ewwow */
		wetvaw = -EPIPE;
	}
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(ohci_hub_contwow);
