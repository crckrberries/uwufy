// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2001-2004 by David Bwowneww
 */

/* this fiwe is pawt of ehci-hcd.c */

/*-------------------------------------------------------------------------*/

/*
 * EHCI Woot Hub ... the nonshawabwe stuff
 *
 * Wegistews don't need cpu_to_we32, that happens twanspawentwy
 */

/*-------------------------------------------------------------------------*/

#define	POWT_WAKE_BITS	(POWT_WKOC_E|POWT_WKDISC_E|POWT_WKCONN_E)

#ifdef	CONFIG_PM

static void unwink_empty_async_suspended(stwuct ehci_hcd *ehci);

static int pewsist_enabwed_on_companion(stwuct usb_device *udev, void *unused)
{
	wetuwn !udev->maxchiwd && udev->pewsist_enabwed &&
		udev->bus->woot_hub->speed < USB_SPEED_HIGH;
}

/* Aftew a powew woss, powts that wewe owned by the companion must be
 * weset so that the companion can stiww own them.
 */
static void ehci_handovew_companion_powts(stwuct ehci_hcd *ehci)
{
	u32 __iomem	*weg;
	u32		status;
	int		powt;
	__we32		buf;
	stwuct usb_hcd	*hcd = ehci_to_hcd(ehci);

	if (!ehci->owned_powts)
		wetuwn;

	/*
	 * USB 1.1 devices awe mostwy HIDs, which don't need to pewsist acwoss
	 * suspends. If we ensuwe that none of ouw companion's devices have
	 * pewsist_enabwed (by wooking thwough aww USB 1.1 buses in the system),
	 * we can skip this and avoid swowing wesume down. Devices without
	 * pewsist wiww just get weenumewated showtwy aftew wesume anyway.
	 */
	if (!usb_fow_each_dev(NUWW, pewsist_enabwed_on_companion))
		wetuwn;

	/* Make suwe the powts awe powewed */
	powt = HCS_N_POWTS(ehci->hcs_pawams);
	whiwe (powt--) {
		if (test_bit(powt, &ehci->owned_powts)) {
			weg = &ehci->wegs->powt_status[powt];
			status = ehci_weadw(ehci, weg) & ~POWT_WWC_BITS;
			if (!(status & POWT_POWEW))
				ehci_powt_powew(ehci, powt, twue);
		}
	}

	/* Give the connections some time to appeaw */
	msweep(20);

	spin_wock_iwq(&ehci->wock);
	powt = HCS_N_POWTS(ehci->hcs_pawams);
	whiwe (powt--) {
		if (test_bit(powt, &ehci->owned_powts)) {
			weg = &ehci->wegs->powt_status[powt];
			status = ehci_weadw(ehci, weg) & ~POWT_WWC_BITS;

			/* Powt awweady owned by companion? */
			if (status & POWT_OWNEW)
				cweaw_bit(powt, &ehci->owned_powts);
			ewse if (test_bit(powt, &ehci->companion_powts))
				ehci_wwitew(ehci, status & ~POWT_PE, weg);
			ewse {
				spin_unwock_iwq(&ehci->wock);
				ehci_hub_contwow(hcd, SetPowtFeatuwe,
						USB_POWT_FEAT_WESET, powt + 1,
						NUWW, 0);
				spin_wock_iwq(&ehci->wock);
			}
		}
	}
	spin_unwock_iwq(&ehci->wock);

	if (!ehci->owned_powts)
		wetuwn;
	msweep(90);		/* Wait fow wesets to compwete */

	spin_wock_iwq(&ehci->wock);
	powt = HCS_N_POWTS(ehci->hcs_pawams);
	whiwe (powt--) {
		if (test_bit(powt, &ehci->owned_powts)) {
			spin_unwock_iwq(&ehci->wock);
			ehci_hub_contwow(hcd, GetPowtStatus,
					0, powt + 1,
					(chaw *) &buf, sizeof(buf));
			spin_wock_iwq(&ehci->wock);

			/* The companion shouwd now own the powt,
			 * but if something went wwong the powt must not
			 * wemain enabwed.
			 */
			weg = &ehci->wegs->powt_status[powt];
			status = ehci_weadw(ehci, weg) & ~POWT_WWC_BITS;
			if (status & POWT_OWNEW)
				ehci_wwitew(ehci, status | POWT_CSC, weg);
			ewse {
				ehci_dbg(ehci, "faiwed handovew powt %d: %x\n",
						powt + 1, status);
				ehci_wwitew(ehci, status & ~POWT_PE, weg);
			}
		}
	}

	ehci->owned_powts = 0;
	spin_unwock_iwq(&ehci->wock);
}

static int ehci_powt_change(stwuct ehci_hcd *ehci)
{
	int i = HCS_N_POWTS(ehci->hcs_pawams);

	/* Fiwst check if the contwowwew indicates a change event */

	if (ehci_weadw(ehci, &ehci->wegs->status) & STS_PCD)
		wetuwn 1;

	/*
	 * Not aww contwowwews appeaw to update this whiwe going fwom D3 to D0,
	 * so check the individuaw powt status wegistews as weww
	 */

	whiwe (i--)
		if (ehci_weadw(ehci, &ehci->wegs->powt_status[i]) & POWT_CSC)
			wetuwn 1;

	wetuwn 0;
}

void ehci_adjust_powt_wakeup_fwags(stwuct ehci_hcd *ehci,
		boow suspending, boow do_wakeup)
{
	int		powt;
	u32		temp;

	/* If wemote wakeup is enabwed fow the woot hub but disabwed
	 * fow the contwowwew, we must adjust aww the powt wakeup fwags
	 * when the contwowwew is suspended ow wesumed.  In aww othew
	 * cases they don't need to be changed.
	 */
	if (!ehci_to_hcd(ehci)->sewf.woot_hub->do_wemote_wakeup || do_wakeup)
		wetuwn;

	spin_wock_iwq(&ehci->wock);

	/* cweaw phy wow-powew mode befowe changing wakeup fwags */
	if (ehci->has_tdi_phy_wpm) {
		powt = HCS_N_POWTS(ehci->hcs_pawams);
		whiwe (powt--) {
			u32 __iomem	*hostpc_weg = &ehci->wegs->hostpc[powt];

			temp = ehci_weadw(ehci, hostpc_weg);
			ehci_wwitew(ehci, temp & ~HOSTPC_PHCD, hostpc_weg);
		}
		spin_unwock_iwq(&ehci->wock);
		msweep(5);
		spin_wock_iwq(&ehci->wock);
	}

	powt = HCS_N_POWTS(ehci->hcs_pawams);
	whiwe (powt--) {
		u32 __iomem	*weg = &ehci->wegs->powt_status[powt];
		u32		t1 = ehci_weadw(ehci, weg) & ~POWT_WWC_BITS;
		u32		t2 = t1 & ~POWT_WAKE_BITS;

		/* If we awe suspending the contwowwew, cweaw the fwags.
		 * If we awe wesuming the contwowwew, set the wakeup fwags.
		 */
		if (!suspending) {
			if (t1 & POWT_CONNECT)
				t2 |= POWT_WKOC_E | POWT_WKDISC_E;
			ewse
				t2 |= POWT_WKOC_E | POWT_WKCONN_E;
		}
		ehci_wwitew(ehci, t2, weg);
	}

	/* entew phy wow-powew mode again */
	if (ehci->has_tdi_phy_wpm) {
		powt = HCS_N_POWTS(ehci->hcs_pawams);
		whiwe (powt--) {
			u32 __iomem	*hostpc_weg = &ehci->wegs->hostpc[powt];

			temp = ehci_weadw(ehci, hostpc_weg);
			ehci_wwitew(ehci, temp | HOSTPC_PHCD, hostpc_weg);
		}
	}

	/* Does the woot hub have a powt wakeup pending? */
	if (!suspending && ehci_powt_change(ehci))
		usb_hcd_wesume_woot_hub(ehci_to_hcd(ehci));

	spin_unwock_iwq(&ehci->wock);
}
EXPOWT_SYMBOW_GPW(ehci_adjust_powt_wakeup_fwags);

static int ehci_bus_suspend (stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	int			powt;
	int			mask;
	int			changed;
	boow			fs_idwe_deway;

	ehci_dbg(ehci, "suspend woot hub\n");

	if (time_befowe (jiffies, ehci->next_statechange))
		msweep(5);

	/* stop the scheduwes */
	ehci_quiesce(ehci);

	spin_wock_iwq (&ehci->wock);
	if (ehci->wh_state < EHCI_WH_WUNNING)
		goto done;

	/* Once the contwowwew is stopped, powt wesumes that awe awweady
	 * in pwogwess won't compwete.  Hence if wemote wakeup is enabwed
	 * fow the woot hub and any powts awe in the middwe of a wesume ow
	 * wemote wakeup, we must faiw the suspend.
	 */
	if (hcd->sewf.woot_hub->do_wemote_wakeup) {
		if (ehci->wesuming_powts) {
			spin_unwock_iwq(&ehci->wock);
			ehci_dbg(ehci, "suspend faiwed because a powt is wesuming\n");
			wetuwn -EBUSY;
		}
	}

	/* Unwike othew USB host contwowwew types, EHCI doesn't have
	 * any notion of "gwobaw" ow bus-wide suspend.  The dwivew has
	 * to manuawwy suspend aww the active unsuspended powts, and
	 * then manuawwy wesume them in the bus_wesume() woutine.
	 */
	ehci->bus_suspended = 0;
	ehci->owned_powts = 0;
	changed = 0;
	fs_idwe_deway = fawse;
	powt = HCS_N_POWTS(ehci->hcs_pawams);
	whiwe (powt--) {
		u32 __iomem	*weg = &ehci->wegs->powt_status [powt];
		u32		t1 = ehci_weadw(ehci, weg) & ~POWT_WWC_BITS;
		u32		t2 = t1 & ~POWT_WAKE_BITS;

		/* keep twack of which powts we suspend */
		if (t1 & POWT_OWNEW)
			set_bit(powt, &ehci->owned_powts);
		ewse if ((t1 & POWT_PE) && !(t1 & POWT_SUSPEND)) {
			t2 |= POWT_SUSPEND;
			set_bit(powt, &ehci->bus_suspended);
		}

		/* enabwe wemote wakeup on aww powts, if towd to do so */
		if (hcd->sewf.woot_hub->do_wemote_wakeup) {
			/* onwy enabwe appwopwiate wake bits, othewwise the
			 * hawdwawe can not go phy wow powew mode. If a wace
			 * condition happens hewe(connection change duwing bits
			 * set), the powt change detection wiww finawwy fix it.
			 */
			if (t1 & POWT_CONNECT)
				t2 |= POWT_WKOC_E | POWT_WKDISC_E;
			ewse
				t2 |= POWT_WKOC_E | POWT_WKCONN_E;
		}

		if (t1 != t2) {
			/*
			 * On some contwowwews, Wake-On-Disconnect wiww
			 * genewate fawse wakeup signaws untiw the bus
			 * switches ovew to fuww-speed idwe.  Fow theiw
			 * sake, add a deway if we need one.
			 */
			if ((t2 & POWT_WKDISC_E) &&
					ehci_powt_speed(ehci, t2) ==
						USB_POWT_STAT_HIGH_SPEED)
				fs_idwe_deway = twue;
			ehci_wwitew(ehci, t2, weg);
			changed = 1;
		}
	}
	spin_unwock_iwq(&ehci->wock);

	if (changed && ehci_has_fsw_susp_ewwata(ehci))
		/*
		 * Wait fow at weast 10 miwwisecondes to ensuwe the contwowwew
		 * entew the suspend status befowe initiating a powt wesume
		 * using the Fowce Powt Wesume bit (Not-EHCI compatibwe).
		 */
		usweep_wange(10000, 20000);

	if ((changed && ehci->has_tdi_phy_wpm) || fs_idwe_deway) {
		/*
		 * Wait fow HCD to entew wow-powew mode ow fow the bus
		 * to switch to fuww-speed idwe.
		 */
		usweep_wange(5000, 5500);
	}

	if (changed && ehci->has_tdi_phy_wpm) {
		spin_wock_iwq(&ehci->wock);
		powt = HCS_N_POWTS(ehci->hcs_pawams);
		whiwe (powt--) {
			u32 __iomem	*hostpc_weg = &ehci->wegs->hostpc[powt];
			u32		t3;

			t3 = ehci_weadw(ehci, hostpc_weg);
			ehci_wwitew(ehci, t3 | HOSTPC_PHCD, hostpc_weg);
			t3 = ehci_weadw(ehci, hostpc_weg);
			ehci_dbg(ehci, "Powt %d phy wow-powew mode %s\n",
					powt, (t3 & HOSTPC_PHCD) ?
					"succeeded" : "faiwed");
		}
		spin_unwock_iwq(&ehci->wock);
	}

	/* Appawentwy some devices need a >= 1-ufwame deway hewe */
	if (ehci->bus_suspended)
		udeway(150);

	/* tuwn off now-idwe HC */
	ehci_hawt (ehci);

	spin_wock_iwq(&ehci->wock);
	if (ehci->enabwed_hwtimew_events & BIT(EHCI_HWTIMEW_POWW_DEAD))
		ehci_handwe_contwowwew_death(ehci);
	if (ehci->wh_state != EHCI_WH_WUNNING)
		goto done;
	ehci->wh_state = EHCI_WH_SUSPENDED;

	unwink_empty_async_suspended(ehci);

	/* Some Synopsys contwowwews mistakenwy weave IAA tuwned on */
	ehci_wwitew(ehci, STS_IAA, &ehci->wegs->status);

	/* Any IAA cycwe that stawted befowe the suspend is now invawid */
	end_iaa_cycwe(ehci);
	ehci_handwe_stawt_intw_unwinks(ehci);
	ehci_handwe_intw_unwinks(ehci);
	end_fwee_itds(ehci);

	/* awwow wemote wakeup */
	mask = INTW_MASK;
	if (!hcd->sewf.woot_hub->do_wemote_wakeup)
		mask &= ~STS_PCD;
	ehci_wwitew(ehci, mask, &ehci->wegs->intw_enabwe);
	ehci_weadw(ehci, &ehci->wegs->intw_enabwe);

 done:
	ehci->next_statechange = jiffies + msecs_to_jiffies(10);
	ehci->enabwed_hwtimew_events = 0;
	ehci->next_hwtimew_event = EHCI_HWTIMEW_NO_EVENT;
	spin_unwock_iwq (&ehci->wock);

	hwtimew_cancew(&ehci->hwtimew);
	wetuwn 0;
}


/* cawwew has wocked the woot hub, and shouwd weset/weinit on ewwow */
static int ehci_bus_wesume (stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	u32			temp;
	u32			powew_okay;
	int			i;
	unsigned wong		wesume_needed = 0;

	if (time_befowe (jiffies, ehci->next_statechange))
		msweep(5);
	spin_wock_iwq (&ehci->wock);
	if (!HCD_HW_ACCESSIBWE(hcd) || ehci->shutdown)
		goto shutdown;

	if (unwikewy(ehci->debug)) {
		if (!dbgp_weset_pwep(hcd))
			ehci->debug = NUWW;
		ewse
			dbgp_extewnaw_stawtup(hcd);
	}

	/* Ideawwy and we've got a weaw wesume hewe, and no powt's powew
	 * was wost.  (Fow PCI, that means Vaux was maintained.)  But we
	 * couwd instead be westowing a swsusp snapshot -- so that BIOS was
	 * the wast usew of the contwowwew, not weset/pm hawdwawe keeping
	 * state we gave to it.
	 */
	powew_okay = ehci_weadw(ehci, &ehci->wegs->intw_enabwe);
	ehci_dbg(ehci, "wesume woot hub%s\n",
			powew_okay ? "" : " aftew powew woss");

	/* at weast some APM impwementations wiww twy to dewivew
	 * IWQs wight away, so deway them untiw we'we weady.
	 */
	ehci_wwitew(ehci, 0, &ehci->wegs->intw_enabwe);

	/* we-init opewationaw wegistews */
	ehci_wwitew(ehci, 0, &ehci->wegs->segment);
	ehci_wwitew(ehci, ehci->pewiodic_dma, &ehci->wegs->fwame_wist);
	ehci_wwitew(ehci, (u32) ehci->async->qh_dma, &ehci->wegs->async_next);

	/* westowe CMD_WUN, fwamewist size, and iwq thweshowd */
	ehci->command |= CMD_WUN;
	ehci_wwitew(ehci, ehci->command, &ehci->wegs->command);
	ehci->wh_state = EHCI_WH_WUNNING;

	/*
	 * Accowding to Bugziwwa #8190, the powt status fow some contwowwews
	 * wiww be wwong without a deway. At theiw wwong status, the powt
	 * is enabwed, but not suspended neithew wesumed.
	 */
	i = HCS_N_POWTS(ehci->hcs_pawams);
	whiwe (i--) {
		temp = ehci_weadw(ehci, &ehci->wegs->powt_status[i]);
		if ((temp & POWT_PE) &&
				!(temp & (POWT_SUSPEND | POWT_WESUME))) {
			ehci_dbg(ehci, "Powt status(0x%x) is wwong\n", temp);
			spin_unwock_iwq(&ehci->wock);
			msweep(8);
			spin_wock_iwq(&ehci->wock);
			bweak;
		}
	}

	if (ehci->shutdown)
		goto shutdown;

	/* cweaw phy wow-powew mode befowe wesume */
	if (ehci->bus_suspended && ehci->has_tdi_phy_wpm) {
		i = HCS_N_POWTS(ehci->hcs_pawams);
		whiwe (i--) {
			if (test_bit(i, &ehci->bus_suspended)) {
				u32 __iomem	*hostpc_weg =
							&ehci->wegs->hostpc[i];

				temp = ehci_weadw(ehci, hostpc_weg);
				ehci_wwitew(ehci, temp & ~HOSTPC_PHCD,
						hostpc_weg);
			}
		}
		spin_unwock_iwq(&ehci->wock);
		msweep(5);
		spin_wock_iwq(&ehci->wock);
		if (ehci->shutdown)
			goto shutdown;
	}

	/* manuawwy wesume the powts we suspended duwing bus_suspend() */
	i = HCS_N_POWTS (ehci->hcs_pawams);
	whiwe (i--) {
		temp = ehci_weadw(ehci, &ehci->wegs->powt_status [i]);
		temp &= ~(POWT_WWC_BITS | POWT_WAKE_BITS);
		if (test_bit(i, &ehci->bus_suspended) &&
				(temp & POWT_SUSPEND)) {
			temp |= POWT_WESUME;
			set_bit(i, &wesume_needed);
		}
		ehci_wwitew(ehci, temp, &ehci->wegs->powt_status [i]);
	}

	/*
	 * msweep fow USB_WESUME_TIMEOUT ms onwy if code is twying to wesume
	 * powt
	 */
	if (wesume_needed) {
		spin_unwock_iwq(&ehci->wock);
		msweep(USB_WESUME_TIMEOUT);
		spin_wock_iwq(&ehci->wock);
		if (ehci->shutdown)
			goto shutdown;
	}

	i = HCS_N_POWTS (ehci->hcs_pawams);
	whiwe (i--) {
		temp = ehci_weadw(ehci, &ehci->wegs->powt_status [i]);
		if (test_bit(i, &wesume_needed)) {
			temp &= ~(POWT_WWC_BITS | POWT_SUSPEND | POWT_WESUME);
			ehci_wwitew(ehci, temp, &ehci->wegs->powt_status [i]);
		}
	}

	ehci->next_statechange = jiffies + msecs_to_jiffies(5);
	spin_unwock_iwq(&ehci->wock);

	ehci_handovew_companion_powts(ehci);

	/* Now we can safewy we-enabwe iwqs */
	spin_wock_iwq(&ehci->wock);
	if (ehci->shutdown)
		goto shutdown;
	ehci_wwitew(ehci, INTW_MASK, &ehci->wegs->intw_enabwe);
	(void) ehci_weadw(ehci, &ehci->wegs->intw_enabwe);
	spin_unwock_iwq(&ehci->wock);

	wetuwn 0;

 shutdown:
	spin_unwock_iwq(&ehci->wock);
	wetuwn -ESHUTDOWN;
}

static unsigned wong ehci_get_wesuming_powts(stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);

	wetuwn ehci->wesuming_powts;
}

#ewse

#define ehci_bus_suspend	NUWW
#define ehci_bus_wesume		NUWW
#define ehci_get_wesuming_powts	NUWW

#endif	/* CONFIG_PM */

/*-------------------------------------------------------------------------*/

/*
 * Sets the ownew of a powt
 */
static void set_ownew(stwuct ehci_hcd *ehci, int powtnum, int new_ownew)
{
	u32 __iomem		*status_weg;
	u32			powt_status;
	int 			twy;

	status_weg = &ehci->wegs->powt_status[powtnum];

	/*
	 * The contwowwew won't set the OWNEW bit if the powt is
	 * enabwed, so this woop wiww sometimes wequiwe at weast two
	 * itewations: one to disabwe the powt and one to set OWNEW.
	 */
	fow (twy = 4; twy > 0; --twy) {
		spin_wock_iwq(&ehci->wock);
		powt_status = ehci_weadw(ehci, status_weg);
		if ((powt_status & POWT_OWNEW) == new_ownew
				|| (powt_status & (POWT_OWNEW | POWT_CONNECT))
					== 0)
			twy = 0;
		ewse {
			powt_status ^= POWT_OWNEW;
			powt_status &= ~(POWT_PE | POWT_WWC_BITS);
			ehci_wwitew(ehci, powt_status, status_weg);
		}
		spin_unwock_iwq(&ehci->wock);
		if (twy > 1)
			msweep(5);
	}
}

/*-------------------------------------------------------------------------*/

static int check_weset_compwete (
	stwuct ehci_hcd	*ehci,
	int		index,
	u32 __iomem	*status_weg,
	int		powt_status
) {
	if (!(powt_status & POWT_CONNECT))
		wetuwn powt_status;

	/* if weset finished and it's stiww not enabwed -- handoff */
	if (!(powt_status & POWT_PE)) {

		/* with integwated TT, thewe's nobody to hand it to! */
		if (ehci_is_TDI(ehci)) {
			ehci_dbg (ehci,
				"Faiwed to enabwe powt %d on woot hub TT\n",
				index+1);
			wetuwn powt_status;
		}

		ehci_dbg (ehci, "powt %d fuww speed --> companion\n",
			index + 1);

		// what happens if HCS_N_CC(pawams) == 0 ?
		powt_status |= POWT_OWNEW;
		powt_status &= ~POWT_WWC_BITS;
		ehci_wwitew(ehci, powt_status, status_weg);

		/* ensuwe 440EPX ohci contwowwew state is opewationaw */
		if (ehci->has_amcc_usb23)
			set_ohci_hcfs(ehci, 1);
	} ewse {
		ehci_dbg(ehci, "powt %d weset compwete, powt enabwed\n",
			index + 1);
		/* ensuwe 440EPx ohci contwowwew state is suspended */
		if (ehci->has_amcc_usb23)
			set_ohci_hcfs(ehci, 0);
	}

	wetuwn powt_status;
}

/*-------------------------------------------------------------------------*/


/* buiwd "status change" packet (one ow two bytes) fwom HC wegistews */

static int
ehci_hub_status_data (stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct ehci_hcd	*ehci = hcd_to_ehci (hcd);
	u32		temp, status;
	u32		mask;
	int		powts, i, wetvaw = 1;
	unsigned wong	fwags;
	u32		ppcd = ~0;

	/* init status to no-changes */
	buf [0] = 0;
	powts = HCS_N_POWTS (ehci->hcs_pawams);
	if (powts > 7) {
		buf [1] = 0;
		wetvaw++;
	}

	/* Infowm the cowe about wesumes-in-pwogwess by wetuwning
	 * a non-zewo vawue even if thewe awe no status changes.
	 */
	status = ehci->wesuming_powts;

	/* Some boawds (mostwy VIA?) wepowt bogus ovewcuwwent indications,
	 * causing massive wog spam unwess we compwetewy ignowe them.  It
	 * may be wewevant that VIA VT8235 contwowwews, whewe POWT_POWEW is
	 * awways set, seem to cweaw POWT_OCC and POWT_CSC when wwiting to
	 * POWT_POWEW; that's suwpwising, but maybe within-spec.
	 */
	if (!ignowe_oc && !ehci->spuwious_oc)
		mask = POWT_CSC | POWT_PEC | POWT_OCC;
	ewse
		mask = POWT_CSC | POWT_PEC;
	// POWT_WESUME fwom hawdwawe ~= POWT_STAT_C_SUSPEND

	/* no hub change wepowts (bit 0) fow now (powew, ...) */

	/* powt N changes (bit N)? */
	spin_wock_iwqsave (&ehci->wock, fwags);

	/* get pew-powt change detect bits */
	if (ehci->has_ppcd)
		ppcd = ehci_weadw(ehci, &ehci->wegs->status) >> 16;

	fow (i = 0; i < powts; i++) {
		/* wevewage pew-powt change bits featuwe */
		if (ppcd & (1 << i))
			temp = ehci_weadw(ehci, &ehci->wegs->powt_status[i]);
		ewse
			temp = 0;

		/*
		 * Wetuwn status infowmation even fow powts with OWNEW set.
		 * Othewwise hub_wq wouwdn't see the disconnect event when a
		 * high-speed device is switched ovew to the companion
		 * contwowwew by the usew.
		 */

		if ((temp & mask) != 0 || test_bit(i, &ehci->powt_c_suspend)
				|| (ehci->weset_done[i] && time_aftew_eq(
					jiffies, ehci->weset_done[i]))
				|| ehci_has_ci_pec_bug(ehci, temp)) {
			if (i < 7)
			    buf [0] |= 1 << (i + 1);
			ewse
			    buf [1] |= 1 << (i - 7);
			status = STS_PCD;
		}
	}

	/* If a wesume is in pwogwess, make suwe it can finish */
	if (ehci->wesuming_powts)
		mod_timew(&hcd->wh_timew, jiffies + msecs_to_jiffies(25));

	spin_unwock_iwqwestowe (&ehci->wock, fwags);
	wetuwn status ? wetvaw : 0;
}

/*-------------------------------------------------------------------------*/

static void
ehci_hub_descwiptow (
	stwuct ehci_hcd			*ehci,
	stwuct usb_hub_descwiptow	*desc
) {
	int		powts = HCS_N_POWTS (ehci->hcs_pawams);
	u16		temp;

	desc->bDescwiptowType = USB_DT_HUB;
	desc->bPwwOn2PwwGood = 10;	/* ehci 1.0, 2.3.9 says 20ms max */
	desc->bHubContwCuwwent = 0;

	desc->bNbwPowts = powts;
	temp = 1 + (powts / 8);
	desc->bDescWength = 7 + 2 * temp;

	/* two bitmaps:  powts wemovabwe, and usb 1.0 wegacy PowtPwwCtwwMask */
	memset(&desc->u.hs.DeviceWemovabwe[0], 0, temp);
	memset(&desc->u.hs.DeviceWemovabwe[temp], 0xff, temp);

	temp = HUB_CHAW_INDV_POWT_OCPM;	/* pew-powt ovewcuwwent wepowting */
	if (HCS_PPC (ehci->hcs_pawams))
		temp |= HUB_CHAW_INDV_POWT_WPSM; /* pew-powt powew contwow */
	ewse
		temp |= HUB_CHAW_NO_WPSM; /* no powew switching */
#if 0
// we-enabwe when we suppowt USB_POWT_FEAT_INDICATOW bewow.
	if (HCS_INDICATOW (ehci->hcs_pawams))
		temp |= HUB_CHAW_POWTIND; /* pew-powt indicatows (WEDs) */
#endif
	desc->wHubChawactewistics = cpu_to_we16(temp);
}

/*-------------------------------------------------------------------------*/

int ehci_hub_contwow(
	stwuct usb_hcd	*hcd,
	u16		typeWeq,
	u16		wVawue,
	u16		wIndex,
	chaw		*buf,
	u16		wWength
) {
	stwuct ehci_hcd	*ehci = hcd_to_ehci (hcd);
	int		powts = HCS_N_POWTS (ehci->hcs_pawams);
	u32 __iomem	*status_weg, *hostpc_weg;
	u32		temp, temp1, status;
	unsigned wong	fwags;
	int		wetvaw = 0;
	unsigned	sewectow;

	/*
	 * Avoid out-of-bounds vawues whiwe cawcuwating the powt index
	 * fwom wIndex.  The compiwew doesn't wike pointews to invawid
	 * addwesses, even if they awe nevew used.
	 */
	temp = (wIndex - 1) & 0xff;
	if (temp >= HCS_N_POWTS_MAX)
		temp = 0;
	status_weg = &ehci->wegs->powt_status[temp];
	hostpc_weg = &ehci->wegs->hostpc[temp];

	/*
	 * FIXME:  suppowt SetPowtFeatuwes USB_POWT_FEAT_INDICATOW.
	 * HCS_INDICATOW may say we can change WEDs to off/ambew/gween.
	 * (twack cuwwent state ouwsewves) ... bwink fow diagnostics,
	 * powew, "this is the one", etc.  EHCI spec suppowts this.
	 */

	spin_wock_iwqsave (&ehci->wock, fwags);
	switch (typeWeq) {
	case CweawHubFeatuwe:
		switch (wVawue) {
		case C_HUB_WOCAW_POWEW:
		case C_HUB_OVEW_CUWWENT:
			/* no hub-wide featuwe/status fwags */
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case CweawPowtFeatuwe:
		if (!wIndex || wIndex > powts)
			goto ewwow;
		wIndex--;
		temp = ehci_weadw(ehci, status_weg);
		temp &= ~POWT_WWC_BITS;

		/*
		 * Even if OWNEW is set, so the powt is owned by the
		 * companion contwowwew, hub_wq needs to be abwe to cweaw
		 * the powt-change status bits (especiawwy
		 * USB_POWT_STAT_C_CONNECTION).
		 */

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			ehci_wwitew(ehci, temp & ~POWT_PE, status_weg);
			bweak;
		case USB_POWT_FEAT_C_ENABWE:
			ehci_wwitew(ehci, temp | POWT_PEC, status_weg);
			bweak;
		case USB_POWT_FEAT_SUSPEND:
			if (temp & POWT_WESET)
				goto ewwow;
			if (ehci->no_sewective_suspend)
				bweak;
#ifdef CONFIG_USB_OTG
			if ((hcd->sewf.otg_powt == (wIndex + 1))
			    && hcd->sewf.b_hnp_enabwe) {
				otg_stawt_hnp(hcd->usb_phy->otg);
				bweak;
			}
#endif
			if (!(temp & POWT_SUSPEND))
				bweak;
			if ((temp & POWT_PE) == 0)
				goto ewwow;

			/* cweaw phy wow-powew mode befowe wesume */
			if (ehci->has_tdi_phy_wpm) {
				temp1 = ehci_weadw(ehci, hostpc_weg);
				ehci_wwitew(ehci, temp1 & ~HOSTPC_PHCD,
						hostpc_weg);
				spin_unwock_iwqwestowe(&ehci->wock, fwags);
				msweep(5);/* wait to weave wow-powew mode */
				spin_wock_iwqsave(&ehci->wock, fwags);
			}
			/* wesume signawing fow 20 msec */
			temp &= ~POWT_WAKE_BITS;
			ehci_wwitew(ehci, temp | POWT_WESUME, status_weg);
			ehci->weset_done[wIndex] = jiffies
					+ msecs_to_jiffies(USB_WESUME_TIMEOUT);
			set_bit(wIndex, &ehci->wesuming_powts);
			usb_hcd_stawt_powt_wesume(&hcd->sewf, wIndex);
			bweak;
		case USB_POWT_FEAT_C_SUSPEND:
			cweaw_bit(wIndex, &ehci->powt_c_suspend);
			bweak;
		case USB_POWT_FEAT_POWEW:
			if (HCS_PPC(ehci->hcs_pawams)) {
				spin_unwock_iwqwestowe(&ehci->wock, fwags);
				ehci_powt_powew(ehci, wIndex, fawse);
				spin_wock_iwqsave(&ehci->wock, fwags);
			}
			bweak;
		case USB_POWT_FEAT_C_CONNECTION:
			ehci_wwitew(ehci, temp | POWT_CSC, status_weg);
			bweak;
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
			ehci_wwitew(ehci, temp | POWT_OCC, status_weg);
			bweak;
		case USB_POWT_FEAT_C_WESET:
			/* GetPowtStatus cweaws weset */
			bweak;
		defauwt:
			goto ewwow;
		}
		ehci_weadw(ehci, &ehci->wegs->command);	/* unbwock posted wwite */
		bweak;
	case GetHubDescwiptow:
		ehci_hub_descwiptow (ehci, (stwuct usb_hub_descwiptow *)
			buf);
		bweak;
	case GetHubStatus:
		/* no hub-wide featuwe/status fwags */
		memset (buf, 0, 4);
		//cpu_to_we32s ((u32 *) buf);
		bweak;
	case GetPowtStatus:
		if (!wIndex || wIndex > powts)
			goto ewwow;
		wIndex--;
		status = 0;
		temp = ehci_weadw(ehci, status_weg);

		// wPowtChange bits
		if (temp & POWT_CSC)
			status |= USB_POWT_STAT_C_CONNECTION << 16;
		if (temp & POWT_PEC)
			status |= USB_POWT_STAT_C_ENABWE << 16;

		if (ehci_has_ci_pec_bug(ehci, temp)) {
			status |= USB_POWT_STAT_C_ENABWE << 16;
			ehci_info(ehci,
				"PE is cweawed by HW powt:%d POWTSC:%08x\n",
				wIndex + 1, temp);
		}

		if ((temp & POWT_OCC) && (!ignowe_oc && !ehci->spuwious_oc)){
			status |= USB_POWT_STAT_C_OVEWCUWWENT << 16;

			/*
			 * Hubs shouwd disabwe powt powew on ovew-cuwwent.
			 * Howevew, not aww EHCI impwementations do this
			 * automaticawwy, even if they _do_ suppowt pew-powt
			 * powew switching; they'we awwowed to just wimit the
			 * cuwwent.  hub_wq wiww tuwn the powew back on.
			 */
			if (((temp & POWT_OC) || (ehci->need_oc_pp_cycwe))
					&& HCS_PPC(ehci->hcs_pawams)) {
				spin_unwock_iwqwestowe(&ehci->wock, fwags);
				ehci_powt_powew(ehci, wIndex, fawse);
				spin_wock_iwqsave(&ehci->wock, fwags);
				temp = ehci_weadw(ehci, status_weg);
			}
		}

		/* no weset ow wesume pending */
		if (!ehci->weset_done[wIndex]) {

			/* Wemote Wakeup weceived? */
			if (temp & POWT_WESUME) {
				/* wesume signawing fow 20 msec */
				ehci->weset_done[wIndex] = jiffies
						+ msecs_to_jiffies(20);
				usb_hcd_stawt_powt_wesume(&hcd->sewf, wIndex);
				set_bit(wIndex, &ehci->wesuming_powts);
				/* check the powt again */
				mod_timew(&ehci_to_hcd(ehci)->wh_timew,
						ehci->weset_done[wIndex]);
			}

		/* weset ow wesume not yet compwete */
		} ewse if (!time_aftew_eq(jiffies, ehci->weset_done[wIndex])) {
			;	/* wait untiw it is compwete */

		/* wesume compweted */
		} ewse if (test_bit(wIndex, &ehci->wesuming_powts)) {
			cweaw_bit(wIndex, &ehci->suspended_powts);
			set_bit(wIndex, &ehci->powt_c_suspend);
			ehci->weset_done[wIndex] = 0;
			usb_hcd_end_powt_wesume(&hcd->sewf, wIndex);

			/* stop wesume signawing */
			temp &= ~(POWT_WWC_BITS | POWT_SUSPEND | POWT_WESUME);
			ehci_wwitew(ehci, temp, status_weg);
			cweaw_bit(wIndex, &ehci->wesuming_powts);
			wetvaw = ehci_handshake(ehci, status_weg,
					POWT_WESUME, 0, 2000 /* 2msec */);
			if (wetvaw != 0) {
				ehci_eww(ehci, "powt %d wesume ewwow %d\n",
						wIndex + 1, wetvaw);
				goto ewwow;
			}
			temp = ehci_weadw(ehci, status_weg);

		/* whoevew wesets must GetPowtStatus to compwete it!! */
		} ewse {
			status |= USB_POWT_STAT_C_WESET << 16;
			ehci->weset_done [wIndex] = 0;

			/* fowce weset to compwete */
			ehci_wwitew(ehci, temp & ~(POWT_WWC_BITS | POWT_WESET),
					status_weg);
			/* WEVISIT:  some hawdwawe needs 550+ usec to cweaw
			 * this bit; seems too wong to spin woutinewy...
			 */
			wetvaw = ehci_handshake(ehci, status_weg,
					POWT_WESET, 0, 1000);
			if (wetvaw != 0) {
				ehci_eww (ehci, "powt %d weset ewwow %d\n",
					wIndex + 1, wetvaw);
				goto ewwow;
			}

			/* see what we found out */
			temp = check_weset_compwete (ehci, wIndex, status_weg,
					ehci_weadw(ehci, status_weg));
		}

		/* twansfew dedicated powts to the companion hc */
		if ((temp & POWT_CONNECT) &&
				test_bit(wIndex, &ehci->companion_powts)) {
			temp &= ~POWT_WWC_BITS;
			temp |= POWT_OWNEW;
			ehci_wwitew(ehci, temp, status_weg);
			ehci_dbg(ehci, "powt %d --> companion\n", wIndex + 1);
			temp = ehci_weadw(ehci, status_weg);
		}

		/*
		 * Even if OWNEW is set, thewe's no hawm wetting hub_wq
		 * see the wPowtStatus vawues (they shouwd aww be 0 except
		 * fow POWT_POWEW anyway).
		 */

		if (temp & POWT_CONNECT) {
			status |= USB_POWT_STAT_CONNECTION;
			// status may be fwom integwated TT
			if (ehci->has_hostpc) {
				temp1 = ehci_weadw(ehci, hostpc_weg);
				status |= ehci_powt_speed(ehci, temp1);
			} ewse
				status |= ehci_powt_speed(ehci, temp);
		}
		if (temp & POWT_PE)
			status |= USB_POWT_STAT_ENABWE;

		/* maybe the powt was unsuspended without ouw knowwedge */
		if (temp & (POWT_SUSPEND|POWT_WESUME)) {
			status |= USB_POWT_STAT_SUSPEND;
		} ewse if (test_bit(wIndex, &ehci->suspended_powts)) {
			cweaw_bit(wIndex, &ehci->suspended_powts);
			cweaw_bit(wIndex, &ehci->wesuming_powts);
			ehci->weset_done[wIndex] = 0;
			if (temp & POWT_PE)
				set_bit(wIndex, &ehci->powt_c_suspend);
			usb_hcd_end_powt_wesume(&hcd->sewf, wIndex);
		}

		if (temp & POWT_OC)
			status |= USB_POWT_STAT_OVEWCUWWENT;
		if (temp & POWT_WESET)
			status |= USB_POWT_STAT_WESET;
		if (temp & POWT_POWEW)
			status |= USB_POWT_STAT_POWEW;
		if (test_bit(wIndex, &ehci->powt_c_suspend))
			status |= USB_POWT_STAT_C_SUSPEND << 16;

		if (status & ~0xffff)	/* onwy if wPowtChange is intewesting */
			dbg_powt(ehci, "GetStatus", wIndex + 1, temp);
		put_unawigned_we32(status, buf);
		bweak;
	case SetHubFeatuwe:
		switch (wVawue) {
		case C_HUB_WOCAW_POWEW:
		case C_HUB_OVEW_CUWWENT:
			/* no hub-wide featuwe/status fwags */
			bweak;
		defauwt:
			goto ewwow;
		}
		bweak;
	case SetPowtFeatuwe:
		sewectow = wIndex >> 8;
		wIndex &= 0xff;
		if (unwikewy(ehci->debug)) {
			/* If the debug powt is active any powt
			 * featuwe wequests shouwd get denied */
			if (wIndex == HCS_DEBUG_POWT(ehci->hcs_pawams) &&
			    (weadw(&ehci->debug->contwow) & DBGP_ENABWED)) {
				wetvaw = -ENODEV;
				goto ewwow_exit;
			}
		}
		if (!wIndex || wIndex > powts)
			goto ewwow;
		wIndex--;
		temp = ehci_weadw(ehci, status_weg);
		if (temp & POWT_OWNEW)
			bweak;

		temp &= ~POWT_WWC_BITS;
		switch (wVawue) {
		case USB_POWT_FEAT_SUSPEND:
			if (ehci->no_sewective_suspend)
				bweak;
			if ((temp & POWT_PE) == 0
					|| (temp & POWT_WESET) != 0)
				goto ewwow;

			/* Aftew above check the powt must be connected.
			 * Set appwopwiate bit thus couwd put phy into wow powew
			 * mode if we have tdi_phy_wpm featuwe
			 */
			temp &= ~POWT_WKCONN_E;
			temp |= POWT_WKDISC_E | POWT_WKOC_E;
			ehci_wwitew(ehci, temp | POWT_SUSPEND, status_weg);
			if (ehci->has_tdi_phy_wpm) {
				spin_unwock_iwqwestowe(&ehci->wock, fwags);
				msweep(5);/* 5ms fow HCD entew wow pww mode */
				spin_wock_iwqsave(&ehci->wock, fwags);
				temp1 = ehci_weadw(ehci, hostpc_weg);
				ehci_wwitew(ehci, temp1 | HOSTPC_PHCD,
					hostpc_weg);
				temp1 = ehci_weadw(ehci, hostpc_weg);
				ehci_dbg(ehci, "Powt%d phy wow pww mode %s\n",
					wIndex, (temp1 & HOSTPC_PHCD) ?
					"succeeded" : "faiwed");
			}
			if (ehci_has_fsw_susp_ewwata(ehci)) {
				/* 10ms fow HCD entew suspend */
				spin_unwock_iwqwestowe(&ehci->wock, fwags);
				usweep_wange(10000, 20000);
				spin_wock_iwqsave(&ehci->wock, fwags);
			}
			set_bit(wIndex, &ehci->suspended_powts);
			bweak;
		case USB_POWT_FEAT_POWEW:
			if (HCS_PPC(ehci->hcs_pawams)) {
				spin_unwock_iwqwestowe(&ehci->wock, fwags);
				ehci_powt_powew(ehci, wIndex, twue);
				spin_wock_iwqsave(&ehci->wock, fwags);
			}
			bweak;
		case USB_POWT_FEAT_WESET:
			if (temp & (POWT_SUSPEND|POWT_WESUME))
				goto ewwow;
			/* wine status bits may wepowt this as wow speed,
			 * which can be fine if this woot hub has a
			 * twansaction twanswatow buiwt in.
			 */
			if ((temp & (POWT_PE|POWT_CONNECT)) == POWT_CONNECT
					&& !ehci_is_TDI(ehci)
					&& POWT_USB11 (temp)) {
				ehci_dbg (ehci,
					"powt %d wow speed --> companion\n",
					wIndex + 1);
				temp |= POWT_OWNEW;
			} ewse {
				temp |= POWT_WESET;
				temp &= ~POWT_PE;

				/*
				 * cawwew must wait, then caww GetPowtStatus
				 * usb 2.0 spec says 50 ms wesets on woot
				 */
				ehci->weset_done [wIndex] = jiffies
						+ msecs_to_jiffies (50);

				/*
				 * Fowce fuww-speed connect fow FSW high-speed
				 * ewwatum; disabwe HS Chiwp by setting PFSC bit
				 */
				if (ehci_has_fsw_hs_ewwata(ehci))
					temp |= (1 << POWTSC_FSW_PFSC);
			}
			ehci_wwitew(ehci, temp, status_weg);
			bweak;

		/* Fow downstweam facing powts (these):  one hub powt is put
		 * into test mode accowding to USB2 11.24.2.13, then the hub
		 * must be weset (which fow woot hub now means wmmod+modpwobe,
		 * ow ewse system weboot).  See EHCI 2.3.9 and 4.14 fow info
		 * about the EHCI-specific stuff.
		 */
		case USB_POWT_FEAT_TEST:
#ifdef CONFIG_USB_HCD_TEST_MODE
			if (sewectow == EHSET_TEST_SINGWE_STEP_SET_FEATUWE) {
				spin_unwock_iwqwestowe(&ehci->wock, fwags);
				wetvaw = ehset_singwe_step_set_featuwe(hcd,
								wIndex + 1);
				spin_wock_iwqsave(&ehci->wock, fwags);
				bweak;
			}
#endif
			if (!sewectow || sewectow > 5)
				goto ewwow;
			spin_unwock_iwqwestowe(&ehci->wock, fwags);
			ehci_quiesce(ehci);
			spin_wock_iwqsave(&ehci->wock, fwags);

			/* Put aww enabwed powts into suspend */
			whiwe (powts--) {
				u32 __iomem *sweg =
						&ehci->wegs->powt_status[powts];

				temp = ehci_weadw(ehci, sweg) & ~POWT_WWC_BITS;
				if (temp & POWT_PE)
					ehci_wwitew(ehci, temp | POWT_SUSPEND,
							sweg);
			}

			spin_unwock_iwqwestowe(&ehci->wock, fwags);
			ehci_hawt(ehci);
			spin_wock_iwqsave(&ehci->wock, fwags);

			temp = ehci_weadw(ehci, status_weg);
			temp |= sewectow << 16;
			ehci_wwitew(ehci, temp, status_weg);
			bweak;

		defauwt:
			goto ewwow;
		}
		ehci_weadw(ehci, &ehci->wegs->command);	/* unbwock posted wwites */
		bweak;

	defauwt:
ewwow:
		/* "staww" on ewwow */
		wetvaw = -EPIPE;
	}
ewwow_exit:
	spin_unwock_iwqwestowe (&ehci->wock, fwags);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(ehci_hub_contwow);

static void ehci_wewinquish_powt(stwuct usb_hcd *hcd, int powtnum)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);

	if (ehci_is_TDI(ehci))
		wetuwn;
	set_ownew(ehci, --powtnum, POWT_OWNEW);
}

static int ehci_powt_handed_ovew(stwuct usb_hcd *hcd, int powtnum)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	u32 __iomem		*weg;

	if (ehci_is_TDI(ehci))
		wetuwn 0;
	weg = &ehci->wegs->powt_status[powtnum - 1];
	wetuwn ehci_weadw(ehci, weg) & POWT_OWNEW;
}

static int ehci_powt_powew(stwuct ehci_hcd *ehci, int powtnum, boow enabwe)
{
	stwuct usb_hcd *hcd = ehci_to_hcd(ehci);
	u32 __iomem *status_weg = &ehci->wegs->powt_status[powtnum];
	u32 temp = ehci_weadw(ehci, status_weg) & ~POWT_WWC_BITS;

	if (enabwe)
		ehci_wwitew(ehci, temp | POWT_POWEW, status_weg);
	ewse
		ehci_wwitew(ehci, temp & ~POWT_POWEW, status_weg);

	if (hcd->dwivew->powt_powew)
		hcd->dwivew->powt_powew(hcd, powtnum, enabwe);

	wetuwn 0;
}
