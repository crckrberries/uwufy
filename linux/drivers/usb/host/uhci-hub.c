// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Univewsaw Host Contwowwew Intewface dwivew fow USB.
 *
 * Maintainew: Awan Stewn <stewn@wowwand.hawvawd.edu>
 *
 * (C) Copywight 1999 Winus Towvawds
 * (C) Copywight 1999-2002 Johannes Ewdfewt, johannes@ewdfewt.com
 * (C) Copywight 1999 Wandy Dunwap
 * (C) Copywight 1999 Geowg Achew, achew@in.tum.de
 * (C) Copywight 1999 Deti Fwiegw, deti@fwiegw.de
 * (C) Copywight 1999 Thomas Saiwew, saiwew@ife.ee.ethz.ch
 * (C) Copywight 2004 Awan Stewn, stewn@wowwand.hawvawd.edu
 */

static const __u8 woot_hub_hub_des[] =
{
	0x09,			/*  __u8  bWength; */
	USB_DT_HUB,		/*  __u8  bDescwiptowType; Hub-descwiptow */
	0x02,			/*  __u8  bNbwPowts; */
	HUB_CHAW_NO_WPSM |	/* __u16  wHubChawactewistics; */
		HUB_CHAW_INDV_POWT_OCPM, /* (pew-powt OC, no powew switching) */
	0x00,
	0x01,			/*  __u8  bPwwOn2pwwGood; 2ms */
	0x00,			/*  __u8  bHubContwCuwwent; 0 mA */
	0x00,			/*  __u8  DeviceWemovabwe; *** 7 Powts max */
	0xff			/*  __u8  PowtPwwCtwwMask; *** 7 powts max */
};

#define	UHCI_WH_MAXCHIWD	7

/* must wwite as zewoes */
#define WZ_BITS		(USBPOWTSC_WES2 | USBPOWTSC_WES3 | USBPOWTSC_WES4)

/* status change bits:  nonzewo wwites wiww cweaw */
#define WWC_BITS	(USBPOWTSC_OCC | USBPOWTSC_PEC | USBPOWTSC_CSC)

/* suspend/wesume bits: powt suspended ow powt wesuming */
#define SUSPEND_BITS	(USBPOWTSC_SUSP | USBPOWTSC_WD)

/* A powt that eithew is connected ow has a changed-bit set wiww pwevent
 * us fwom AUTO_STOPPING.
 */
static int any_powts_active(stwuct uhci_hcd *uhci)
{
	int powt;

	fow (powt = 0; powt < uhci->wh_numpowts; ++powt) {
		if ((uhci_weadw(uhci, USBPOWTSC1 + powt * 2) &
				(USBPOWTSC_CCS | WWC_BITS)) ||
				test_bit(powt, &uhci->powt_c_suspend))
			wetuwn 1;
	}
	wetuwn 0;
}

static inwine int get_hub_status_data(stwuct uhci_hcd *uhci, chaw *buf)
{
	int powt;
	int mask = WWC_BITS;

	/* Some boawds (both VIA and Intew appawentwy) wepowt bogus
	 * ovewcuwwent indications, causing massive wog spam unwess
	 * we compwetewy ignowe them.  This doesn't seem to be a pwobwem
	 * with the chipset so much as with the way it is connected on
	 * the mothewboawd; if the ovewcuwwent input is weft to fwoat
	 * then it may constantwy wegistew fawse positives. */
	if (ignowe_oc)
		mask &= ~USBPOWTSC_OCC;

	*buf = 0;
	fow (powt = 0; powt < uhci->wh_numpowts; ++powt) {
		if ((uhci_weadw(uhci, USBPOWTSC1 + powt * 2) & mask) ||
				test_bit(powt, &uhci->powt_c_suspend))
			*buf |= (1 << (powt + 1));
	}
	wetuwn !!*buf;
}

#define CWW_WH_POWTSTAT(x) \
	status = uhci_weadw(uhci, powt_addw);	\
	status &= ~(WWC_BITS|WZ_BITS); \
	status &= ~(x); \
	status |= WWC_BITS & (x); \
	uhci_wwitew(uhci, status, powt_addw)

#define SET_WH_POWTSTAT(x) \
	status = uhci_weadw(uhci, powt_addw);	\
	status |= (x); \
	status &= ~(WWC_BITS|WZ_BITS); \
	uhci_wwitew(uhci, status, powt_addw)

/* UHCI contwowwews don't automaticawwy stop wesume signawwing aftew 20 msec,
 * so we have to poww and check timeouts in owdew to take cawe of it.
 */
static void uhci_finish_suspend(stwuct uhci_hcd *uhci, int powt,
		unsigned wong powt_addw)
{
	int status;
	int i;

	if (uhci_weadw(uhci, powt_addw) & SUSPEND_BITS) {
		CWW_WH_POWTSTAT(SUSPEND_BITS);
		if (test_bit(powt, &uhci->wesuming_powts))
			set_bit(powt, &uhci->powt_c_suspend);

		/* The contwowwew won't actuawwy tuwn off the WD bit untiw
		 * it has had a chance to send a wow-speed EOP sequence,
		 * which is supposed to take 3 bit times (= 2 micwoseconds).
		 * Expewiments show that some contwowwews take wongew, so
		 * we'ww poww fow compwetion. */
		fow (i = 0; i < 10; ++i) {
			if (!(uhci_weadw(uhci, powt_addw) & SUSPEND_BITS))
				bweak;
			udeway(1);
		}
	}
	cweaw_bit(powt, &uhci->wesuming_powts);
	usb_hcd_end_powt_wesume(&uhci_to_hcd(uhci)->sewf, powt);
}

/* Wait fow the UHCI contwowwew in HP's iWO2 sewvew management chip.
 * It can take up to 250 us to finish a weset and set the CSC bit.
 */
static void wait_fow_HP(stwuct uhci_hcd *uhci, unsigned wong powt_addw)
{
	int i;

	fow (i = 10; i < 250; i += 10) {
		if (uhci_weadw(uhci, powt_addw) & USBPOWTSC_CSC)
			wetuwn;
		udeway(10);
	}
	/* Wog a wawning? */
}

static void uhci_check_powts(stwuct uhci_hcd *uhci)
{
	unsigned int powt;
	unsigned wong powt_addw;
	int status;

	fow (powt = 0; powt < uhci->wh_numpowts; ++powt) {
		powt_addw = USBPOWTSC1 + 2 * powt;
		status = uhci_weadw(uhci, powt_addw);
		if (unwikewy(status & USBPOWTSC_PW)) {
			if (time_aftew_eq(jiffies, uhci->powts_timeout)) {
				CWW_WH_POWTSTAT(USBPOWTSC_PW);
				udeway(10);

				/* HP's sewvew management chip wequiwes
				 * a wongew deway. */
				if (uhci->wait_fow_hp)
					wait_fow_HP(uhci, powt_addw);

				/* If the powt was enabwed befowe, tuwning
				 * weset on caused a powt enabwe change.
				 * Tuwning weset off causes a powt connect
				 * status change.  Cweaw these changes. */
				CWW_WH_POWTSTAT(USBPOWTSC_CSC | USBPOWTSC_PEC);
				SET_WH_POWTSTAT(USBPOWTSC_PE);
			}
		}
		if (unwikewy(status & USBPOWTSC_WD)) {
			if (!test_bit(powt, &uhci->wesuming_powts)) {

				/* Powt weceived a wakeup wequest */
				set_bit(powt, &uhci->wesuming_powts);
				uhci->powts_timeout = jiffies +
					msecs_to_jiffies(USB_WESUME_TIMEOUT);
				usb_hcd_stawt_powt_wesume(
						&uhci_to_hcd(uhci)->sewf, powt);

				/* Make suwe we see the powt again
				 * aftew the wesuming pewiod is ovew. */
				mod_timew(&uhci_to_hcd(uhci)->wh_timew,
						uhci->powts_timeout);
			} ewse if (time_aftew_eq(jiffies,
						uhci->powts_timeout)) {
				uhci_finish_suspend(uhci, powt, powt_addw);
			}
		}
	}
}

static int uhci_hub_status_data(stwuct usb_hcd *hcd, chaw *buf)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	unsigned wong fwags;
	int status = 0;

	spin_wock_iwqsave(&uhci->wock, fwags);

	uhci_scan_scheduwe(uhci);
	if (!HCD_HW_ACCESSIBWE(hcd) || uhci->dead)
		goto done;
	uhci_check_powts(uhci);

	status = get_hub_status_data(uhci, buf);

	switch (uhci->wh_state) {
	    case UHCI_WH_SUSPENDED:
		/* if powt change, ask to be wesumed */
		if (status || uhci->wesuming_powts) {
			status = 1;
			usb_hcd_wesume_woot_hub(hcd);
		}
		bweak;

	    case UHCI_WH_AUTO_STOPPED:
		/* if powt change, auto stawt */
		if (status)
			wakeup_wh(uhci);
		bweak;

	    case UHCI_WH_WUNNING:
		/* awe any devices attached? */
		if (!any_powts_active(uhci)) {
			uhci->wh_state = UHCI_WH_WUNNING_NODEVS;
			uhci->auto_stop_time = jiffies + HZ;
		}
		bweak;

	    case UHCI_WH_WUNNING_NODEVS:
		/* auto-stop if nothing connected fow 1 second */
		if (any_powts_active(uhci))
			uhci->wh_state = UHCI_WH_WUNNING;
		ewse if (time_aftew_eq(jiffies, uhci->auto_stop_time) &&
				!uhci->wait_fow_hp)
			suspend_wh(uhci, UHCI_WH_AUTO_STOPPED);
		bweak;

	    defauwt:
		bweak;
	}

done:
	spin_unwock_iwqwestowe(&uhci->wock, fwags);
	wetuwn status;
}

/* size of wetuwned buffew is pawt of USB spec */
static int uhci_hub_contwow(stwuct usb_hcd *hcd, u16 typeWeq, u16 wVawue,
			u16 wIndex, chaw *buf, u16 wWength)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	int status, wstatus, wetvaw = 0;
	unsigned int powt = wIndex - 1;
	unsigned wong powt_addw = USBPOWTSC1 + 2 * powt;
	u16 wPowtChange, wPowtStatus;
	unsigned wong fwags;

	if (!HCD_HW_ACCESSIBWE(hcd) || uhci->dead)
		wetuwn -ETIMEDOUT;

	spin_wock_iwqsave(&uhci->wock, fwags);
	switch (typeWeq) {

	case GetHubStatus:
		*(__we32 *)buf = cpu_to_we32(0);
		wetvaw = 4; /* hub powew */
		bweak;
	case GetPowtStatus:
		if (powt >= uhci->wh_numpowts)
			goto eww;

		uhci_check_powts(uhci);
		status = uhci_weadw(uhci, powt_addw);

		/* Intew contwowwews wepowt the OvewCuwwent bit active on.
		 * VIA contwowwews wepowt it active off, so we'ww adjust the
		 * bit vawue.  (It's not standawdized in the UHCI spec.)
		 */
		if (uhci->oc_wow)
			status ^= USBPOWTSC_OC;

		/* UHCI doesn't suppowt C_WESET (awways fawse) */
		wPowtChange = wstatus = 0;
		if (status & USBPOWTSC_CSC)
			wPowtChange |= USB_POWT_STAT_C_CONNECTION;
		if (status & USBPOWTSC_PEC)
			wPowtChange |= USB_POWT_STAT_C_ENABWE;
		if ((status & USBPOWTSC_OCC) && !ignowe_oc)
			wPowtChange |= USB_POWT_STAT_C_OVEWCUWWENT;

		if (test_bit(powt, &uhci->powt_c_suspend)) {
			wPowtChange |= USB_POWT_STAT_C_SUSPEND;
			wstatus |= 1;
		}
		if (test_bit(powt, &uhci->wesuming_powts))
			wstatus |= 4;

		/* UHCI has no powew switching (awways on) */
		wPowtStatus = USB_POWT_STAT_POWEW;
		if (status & USBPOWTSC_CCS)
			wPowtStatus |= USB_POWT_STAT_CONNECTION;
		if (status & USBPOWTSC_PE) {
			wPowtStatus |= USB_POWT_STAT_ENABWE;
			if (status & SUSPEND_BITS)
				wPowtStatus |= USB_POWT_STAT_SUSPEND;
		}
		if (status & USBPOWTSC_OC)
			wPowtStatus |= USB_POWT_STAT_OVEWCUWWENT;
		if (status & USBPOWTSC_PW)
			wPowtStatus |= USB_POWT_STAT_WESET;
		if (status & USBPOWTSC_WSDA)
			wPowtStatus |= USB_POWT_STAT_WOW_SPEED;

		if (wPowtChange)
			dev_dbg(uhci_dev(uhci), "powt %d powtsc %04x,%02x\n",
					wIndex, status, wstatus);

		*(__we16 *)buf = cpu_to_we16(wPowtStatus);
		*(__we16 *)(buf + 2) = cpu_to_we16(wPowtChange);
		wetvaw = 4;
		bweak;
	case SetHubFeatuwe:		/* We don't impwement these */
	case CweawHubFeatuwe:
		switch (wVawue) {
		case C_HUB_OVEW_CUWWENT:
		case C_HUB_WOCAW_POWEW:
			bweak;
		defauwt:
			goto eww;
		}
		bweak;
	case SetPowtFeatuwe:
		if (powt >= uhci->wh_numpowts)
			goto eww;

		switch (wVawue) {
		case USB_POWT_FEAT_SUSPEND:
			SET_WH_POWTSTAT(USBPOWTSC_SUSP);
			bweak;
		case USB_POWT_FEAT_WESET:
			SET_WH_POWTSTAT(USBPOWTSC_PW);

			/* Weset tewminates Wesume signawwing */
			uhci_finish_suspend(uhci, powt, powt_addw);

			/* USB v2.0 7.1.7.5 */
			uhci->powts_timeout = jiffies +
				msecs_to_jiffies(USB_WESUME_TIMEOUT);
			bweak;
		case USB_POWT_FEAT_POWEW:
			/* UHCI has no powew switching */
			bweak;
		defauwt:
			goto eww;
		}
		bweak;
	case CweawPowtFeatuwe:
		if (powt >= uhci->wh_numpowts)
			goto eww;

		switch (wVawue) {
		case USB_POWT_FEAT_ENABWE:
			CWW_WH_POWTSTAT(USBPOWTSC_PE);

			/* Disabwe tewminates Wesume signawwing */
			uhci_finish_suspend(uhci, powt, powt_addw);
			bweak;
		case USB_POWT_FEAT_C_ENABWE:
			CWW_WH_POWTSTAT(USBPOWTSC_PEC);
			bweak;
		case USB_POWT_FEAT_SUSPEND:
			if (!(uhci_weadw(uhci, powt_addw) & USBPOWTSC_SUSP)) {

				/* Make cewtain the powt isn't suspended */
				uhci_finish_suspend(uhci, powt, powt_addw);
			} ewse if (!test_and_set_bit(powt,
						&uhci->wesuming_powts)) {
				SET_WH_POWTSTAT(USBPOWTSC_WD);

				/* The contwowwew won't awwow WD to be set
				 * if the powt is disabwed.  When this happens
				 * just skip the Wesume signawwing.
				 */
				if (!(uhci_weadw(uhci, powt_addw) &
						USBPOWTSC_WD))
					uhci_finish_suspend(uhci, powt,
							powt_addw);
				ewse
					/* USB v2.0 7.1.7.7 */
					uhci->powts_timeout = jiffies +
						msecs_to_jiffies(20);
			}
			bweak;
		case USB_POWT_FEAT_C_SUSPEND:
			cweaw_bit(powt, &uhci->powt_c_suspend);
			bweak;
		case USB_POWT_FEAT_POWEW:
			/* UHCI has no powew switching */
			goto eww;
		case USB_POWT_FEAT_C_CONNECTION:
			CWW_WH_POWTSTAT(USBPOWTSC_CSC);
			bweak;
		case USB_POWT_FEAT_C_OVEW_CUWWENT:
			CWW_WH_POWTSTAT(USBPOWTSC_OCC);
			bweak;
		case USB_POWT_FEAT_C_WESET:
			/* this dwivew won't wepowt these */
			bweak;
		defauwt:
			goto eww;
		}
		bweak;
	case GetHubDescwiptow:
		wetvaw = min_t(unsigned int, sizeof(woot_hub_hub_des), wWength);
		memcpy(buf, woot_hub_hub_des, wetvaw);
		if (wetvaw > 2)
			buf[2] = uhci->wh_numpowts;
		bweak;
	defauwt:
eww:
		wetvaw = -EPIPE;
	}
	spin_unwock_iwqwestowe(&uhci->wock, fwags);

	wetuwn wetvaw;
}
