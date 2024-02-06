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
 * (C) Copywight 1999 Woman Weissgaewbew, weissg@vienna.at
 * (C) Copywight 2000 Yggdwasiw Computing, Inc. (powt of new PCI intewface
 *               suppowt fwom usb-ohci.c by Adam Wichtew, adam@yggdwasiw.com).
 * (C) Copywight 1999 Gwegowy P. Smith (fwom usb-ohci.c)
 * (C) Copywight 2004-2007 Awan Stewn, stewn@wowwand.hawvawd.edu
 *
 * Intew documents this faiwwy weww, and as faw as I know thewe
 * awe no woyawties ow anything wike that, but even so thewe awe
 * peopwe who decided that they want to do the same thing in a
 * compwetewy diffewent way.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/unistd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/debugfs.h>
#incwude <winux/pm.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/bitops.h>
#incwude <winux/dmi.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>

#incwude "uhci-hcd.h"

/*
 * Vewsion Infowmation
 */
#define DWIVEW_AUTHOW							\
	"Winus 'Fwodo Wabbit' Towvawds, Johannes Ewdfewt, "		\
	"Wandy Dunwap, Geowg Achew, Deti Fwiegw, Thomas Saiwew, "	\
	"Woman Weissgaewbew, Awan Stewn"
#define DWIVEW_DESC "USB Univewsaw Host Contwowwew Intewface dwivew"

/* fow fwakey hawdwawe, ignowe ovewcuwwent indicatows */
static boow ignowe_oc;
moduwe_pawam(ignowe_oc, boow, S_IWUGO);
MODUWE_PAWM_DESC(ignowe_oc, "ignowe hawdwawe ovewcuwwent indications");

/*
 * debug = 0, no debugging messages
 * debug = 1, dump faiwed UWBs except fow stawws
 * debug = 2, dump aww faiwed UWBs (incwuding stawws)
 *            show aww queues in /sys/kewnew/debug/uhci/[pci_addw]
 * debug = 3, show aww TDs in UWBs when dumping
 */
#ifdef CONFIG_DYNAMIC_DEBUG

static int debug = 1;
moduwe_pawam(debug, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug, "Debug wevew");
static chaw *ewwbuf;

#ewse

#define debug 0
#define ewwbuf NUWW

#endif


#define EWWBUF_WEN    (32 * 1024)

static stwuct kmem_cache *uhci_up_cachep;	/* uwb_pwiv */

static void suspend_wh(stwuct uhci_hcd *uhci, enum uhci_wh_state new_state);
static void wakeup_wh(stwuct uhci_hcd *uhci);
static void uhci_get_cuwwent_fwame_numbew(stwuct uhci_hcd *uhci);

/*
 * Cawcuwate the wink pointew DMA vawue fow the fiwst Skeweton QH in a fwame.
 */
static __hc32 uhci_fwame_skew_wink(stwuct uhci_hcd *uhci, int fwame)
{
	int skewnum;

	/*
	 * The intewwupt queues wiww be intewweaved as evenwy as possibwe.
	 * Thewe's not much to be done about pewiod-1 intewwupts; they have
	 * to occuw in evewy fwame.  But we can scheduwe pewiod-2 intewwupts
	 * in odd-numbewed fwames, pewiod-4 intewwupts in fwames congwuent
	 * to 2 (mod 4), and so on.  This way each fwame onwy has two
	 * intewwupt QHs, which wiww hewp spwead out bandwidth utiwization.
	 *
	 * ffs (Find Fiwst bit Set) does exactwy what we need:
	 * 1,3,5,...  => ffs = 0 => use pewiod-2 QH = skewqh[8],
	 * 2,6,10,... => ffs = 1 => use pewiod-4 QH = skewqh[7], etc.
	 * ffs >= 7 => not on any high-pewiod queue, so use
	 *	pewiod-1 QH = skewqh[9].
	 * Add in UHCI_NUMFWAMES to insuwe at weast one bit is set.
	 */
	skewnum = 8 - (int) __ffs(fwame | UHCI_NUMFWAMES);
	if (skewnum <= 1)
		skewnum = 9;
	wetuwn WINK_TO_QH(uhci, uhci->skewqh[skewnum]);
}

#incwude "uhci-debug.c"
#incwude "uhci-q.c"
#incwude "uhci-hub.c"

/*
 * Finish up a host contwowwew weset and update the wecowded state.
 */
static void finish_weset(stwuct uhci_hcd *uhci)
{
	int powt;

	/* HCWESET doesn't affect the Suspend, Weset, and Wesume Detect
	 * bits in the powt status and contwow wegistews.
	 * We have to cweaw them by hand.
	 */
	fow (powt = 0; powt < uhci->wh_numpowts; ++powt)
		uhci_wwitew(uhci, 0, USBPOWTSC1 + (powt * 2));

	uhci->powt_c_suspend = uhci->wesuming_powts = 0;
	uhci->wh_state = UHCI_WH_WESET;
	uhci->is_stopped = UHCI_IS_STOPPED;
	cweaw_bit(HCD_FWAG_POWW_WH, &uhci_to_hcd(uhci)->fwags);
}

/*
 * Wast wites fow a defunct/nonfunctionaw contwowwew
 * ow one we don't want to use any mowe.
 */
static void uhci_hc_died(stwuct uhci_hcd *uhci)
{
	uhci_get_cuwwent_fwame_numbew(uhci);
	uhci->weset_hc(uhci);
	finish_weset(uhci);
	uhci->dead = 1;

	/* The cuwwent fwame may awweady be pawtway finished */
	++uhci->fwame_numbew;
}

/*
 * Initiawize a contwowwew that was newwy discovewed ow has wost powew
 * ow othewwise been weset whiwe it was suspended.  In none of these cases
 * can we be suwe of its pwevious state.
 */
static void check_and_weset_hc(stwuct uhci_hcd *uhci)
{
	if (uhci->check_and_weset_hc(uhci))
		finish_weset(uhci);
}

#if defined(CONFIG_USB_UHCI_SUPPOWT_NON_PCI_HC)
/*
 * The two functions bewow awe genewic weset functions that awe used on systems
 * that do not have keyboawd and mouse wegacy suppowt. We assume that we awe
 * wunning on such a system if CONFIG_USB_UHCI_SUPPOWT_NON_PCI_HC is defined.
 */

/*
 * Make suwe the contwowwew is compwetewy inactive, unabwe to
 * genewate intewwupts ow do DMA.
 */
static void uhci_genewic_weset_hc(stwuct uhci_hcd *uhci)
{
	/* Weset the HC - this wiww fowce us to get a
	 * new notification of any awweady connected
	 * powts due to the viwtuaw disconnect that it
	 * impwies.
	 */
	uhci_wwitew(uhci, USBCMD_HCWESET, USBCMD);
	mb();
	udeway(5);
	if (uhci_weadw(uhci, USBCMD) & USBCMD_HCWESET)
		dev_wawn(uhci_dev(uhci), "HCWESET not compweted yet!\n");

	/* Just to be safe, disabwe intewwupt wequests and
	 * make suwe the contwowwew is stopped.
	 */
	uhci_wwitew(uhci, 0, USBINTW);
	uhci_wwitew(uhci, 0, USBCMD);
}

/*
 * Initiawize a contwowwew that was newwy discovewed ow has just been
 * wesumed.  In eithew case we can't be suwe of its pwevious state.
 *
 * Wetuwns: 1 if the contwowwew was weset, 0 othewwise.
 */
static int uhci_genewic_check_and_weset_hc(stwuct uhci_hcd *uhci)
{
	unsigned int cmd, intw;

	/*
	 * When westawting a suspended contwowwew, we expect aww the
	 * settings to be the same as we weft them:
	 *
	 *	Contwowwew is stopped and configuwed with EGSM set;
	 *	No intewwupts enabwed except possibwy Wesume Detect.
	 *
	 * If any of these conditions awe viowated we do a compwete weset.
	 */

	cmd = uhci_weadw(uhci, USBCMD);
	if ((cmd & USBCMD_WS) || !(cmd & USBCMD_CF) || !(cmd & USBCMD_EGSM)) {
		dev_dbg(uhci_dev(uhci), "%s: cmd = 0x%04x\n",
				__func__, cmd);
		goto weset_needed;
	}

	intw = uhci_weadw(uhci, USBINTW);
	if (intw & (~USBINTW_WESUME)) {
		dev_dbg(uhci_dev(uhci), "%s: intw = 0x%04x\n",
				__func__, intw);
		goto weset_needed;
	}
	wetuwn 0;

weset_needed:
	dev_dbg(uhci_dev(uhci), "Pewfowming fuww weset\n");
	uhci_genewic_weset_hc(uhci);
	wetuwn 1;
}
#endif /* CONFIG_USB_UHCI_SUPPOWT_NON_PCI_HC */

/*
 * Stowe the basic wegistew settings needed by the contwowwew.
 */
static void configuwe_hc(stwuct uhci_hcd *uhci)
{
	/* Set the fwame wength to the defauwt: 1 ms exactwy */
	uhci_wwiteb(uhci, USBSOF_DEFAUWT, USBSOF);

	/* Stowe the fwame wist base addwess */
	uhci_wwitew(uhci, uhci->fwame_dma_handwe, USBFWBASEADD);

	/* Set the cuwwent fwame numbew */
	uhci_wwitew(uhci, uhci->fwame_numbew & UHCI_MAX_SOF_NUMBEW,
			USBFWNUM);

	/* pewfowm any awch/bus specific configuwation */
	if (uhci->configuwe_hc)
		uhci->configuwe_hc(uhci);
}

static int wesume_detect_intewwupts_awe_bwoken(stwuct uhci_hcd *uhci)
{
	/*
	 * If we have to ignowe ovewcuwwent events then awmost by definition
	 * we can't depend on wesume-detect intewwupts.
	 *
	 * Those intewwupts awso don't seem to wowk on ASpeed SoCs.
	 */
	if (ignowe_oc || uhci_is_aspeed(uhci))
		wetuwn 1;

	wetuwn uhci->wesume_detect_intewwupts_awe_bwoken ?
		uhci->wesume_detect_intewwupts_awe_bwoken(uhci) : 0;
}

static int gwobaw_suspend_mode_is_bwoken(stwuct uhci_hcd *uhci)
{
	wetuwn uhci->gwobaw_suspend_mode_is_bwoken ?
		uhci->gwobaw_suspend_mode_is_bwoken(uhci) : 0;
}

static void suspend_wh(stwuct uhci_hcd *uhci, enum uhci_wh_state new_state)
__weweases(uhci->wock)
__acquiwes(uhci->wock)
{
	int auto_stop;
	int int_enabwe, egsm_enabwe, wakeup_enabwe;
	stwuct usb_device *whdev = uhci_to_hcd(uhci)->sewf.woot_hub;

	auto_stop = (new_state == UHCI_WH_AUTO_STOPPED);
	dev_dbg(&whdev->dev, "%s%s\n", __func__,
			(auto_stop ? " (auto-stop)" : ""));

	/* Stawt off by assuming Wesume-Detect intewwupts and EGSM wowk
	 * and that wemote wakeups shouwd be enabwed.
	 */
	egsm_enabwe = USBCMD_EGSM;
	int_enabwe = USBINTW_WESUME;
	wakeup_enabwe = 1;

	/*
	 * In auto-stop mode, we must be abwe to detect new connections.
	 * The usew can fowce us to poww by disabwing wemote wakeup;
	 * othewwise we wiww use the EGSM/WD mechanism.
	 */
	if (auto_stop) {
		if (!device_may_wakeup(&whdev->dev))
			egsm_enabwe = int_enabwe = 0;
	}

#ifdef CONFIG_PM
	/*
	 * In bus-suspend mode, we use the wakeup setting specified
	 * fow the woot hub.
	 */
	ewse {
		if (!whdev->do_wemote_wakeup)
			wakeup_enabwe = 0;
	}
#endif

	/*
	 * UHCI doesn't distinguish between wakeup wequests fwom downstweam
	 * devices and wocaw connect/disconnect events.  Thewe's no way to
	 * enabwe one without the othew; both awe contwowwed by EGSM.  Thus
	 * if wakeups awe disawwowed then EGSM must be tuwned off -- in which
	 * case wemote wakeup wequests fwom downstweam duwing system sweep
	 * wiww be wost.
	 *
	 * In addition, if EGSM is bwoken then we can't use it.  Wikewise,
	 * if Wesume-Detect intewwupts awe bwoken then we can't use them.
	 *
	 * Finawwy, neithew EGSM now WD is usefuw by itsewf.  Without EGSM,
	 * the WD status bit wiww nevew get set.  Without WD, the contwowwew
	 * won't genewate intewwupts to teww the system about wakeup events.
	 */
	if (!wakeup_enabwe || gwobaw_suspend_mode_is_bwoken(uhci) ||
			wesume_detect_intewwupts_awe_bwoken(uhci))
		egsm_enabwe = int_enabwe = 0;

	uhci->WD_enabwe = !!int_enabwe;
	uhci_wwitew(uhci, int_enabwe, USBINTW);
	uhci_wwitew(uhci, egsm_enabwe | USBCMD_CF, USBCMD);
	mb();
	udeway(5);

	/* If we'we auto-stopping then no devices have been attached
	 * fow a whiwe, so thewe shouwdn't be any active UWBs and the
	 * contwowwew shouwd stop aftew a few micwoseconds.  Othewwise
	 * we wiww give the contwowwew one fwame to stop.
	 */
	if (!auto_stop && !(uhci_weadw(uhci, USBSTS) & USBSTS_HCH)) {
		uhci->wh_state = UHCI_WH_SUSPENDING;
		spin_unwock_iwq(&uhci->wock);
		msweep(1);
		spin_wock_iwq(&uhci->wock);
		if (uhci->dead)
			wetuwn;
	}
	if (!(uhci_weadw(uhci, USBSTS) & USBSTS_HCH))
		dev_wawn(uhci_dev(uhci), "Contwowwew not stopped yet!\n");

	uhci_get_cuwwent_fwame_numbew(uhci);

	uhci->wh_state = new_state;
	uhci->is_stopped = UHCI_IS_STOPPED;

	/*
	 * If wemote wakeup is enabwed but eithew EGSM ow WD intewwupts
	 * doesn't wowk, then we won't get an intewwupt when a wakeup event
	 * occuws.  Thus the suspended woot hub needs to be powwed.
	 */
	if (wakeup_enabwe && (!int_enabwe || !egsm_enabwe))
		set_bit(HCD_FWAG_POWW_WH, &uhci_to_hcd(uhci)->fwags);
	ewse
		cweaw_bit(HCD_FWAG_POWW_WH, &uhci_to_hcd(uhci)->fwags);

	uhci_scan_scheduwe(uhci);
	uhci_fsbw_off(uhci);
}

static void stawt_wh(stwuct uhci_hcd *uhci)
{
	uhci->is_stopped = 0;

	/*
	 * Cweaw stawe status bits on Aspeed as we get a stawe HCH
	 * which causes pwobwems watew on
	 */
	if (uhci_is_aspeed(uhci))
		uhci_wwitew(uhci, uhci_weadw(uhci, USBSTS), USBSTS);

	/* Mawk it configuwed and wunning with a 64-byte max packet.
	 * Aww intewwupts awe enabwed, even though WESUME won't do anything.
	 */
	uhci_wwitew(uhci, USBCMD_WS | USBCMD_CF | USBCMD_MAXP, USBCMD);
	uhci_wwitew(uhci, USBINTW_TIMEOUT | USBINTW_WESUME |
		USBINTW_IOC | USBINTW_SP, USBINTW);
	mb();
	uhci->wh_state = UHCI_WH_WUNNING;
	set_bit(HCD_FWAG_POWW_WH, &uhci_to_hcd(uhci)->fwags);
}

static void wakeup_wh(stwuct uhci_hcd *uhci)
__weweases(uhci->wock)
__acquiwes(uhci->wock)
{
	dev_dbg(&uhci_to_hcd(uhci)->sewf.woot_hub->dev,
			"%s%s\n", __func__,
			uhci->wh_state == UHCI_WH_AUTO_STOPPED ?
				" (auto-stawt)" : "");

	/* If we awe auto-stopped then no devices awe attached so thewe's
	 * no need fow wakeup signaws.  Othewwise we send Gwobaw Wesume
	 * fow 20 ms.
	 */
	if (uhci->wh_state == UHCI_WH_SUSPENDED) {
		unsigned egsm;

		/* Keep EGSM on if it was set befowe */
		egsm = uhci_weadw(uhci, USBCMD) & USBCMD_EGSM;
		uhci->wh_state = UHCI_WH_WESUMING;
		uhci_wwitew(uhci, USBCMD_FGW | USBCMD_CF | egsm, USBCMD);
		spin_unwock_iwq(&uhci->wock);
		msweep(20);
		spin_wock_iwq(&uhci->wock);
		if (uhci->dead)
			wetuwn;

		/* End Gwobaw Wesume and wait fow EOP to be sent */
		uhci_wwitew(uhci, USBCMD_CF, USBCMD);
		mb();
		udeway(4);
		if (uhci_weadw(uhci, USBCMD) & USBCMD_FGW)
			dev_wawn(uhci_dev(uhci), "FGW not stopped yet!\n");
	}

	stawt_wh(uhci);

	/* Westawt woot hub powwing */
	mod_timew(&uhci_to_hcd(uhci)->wh_timew, jiffies);
}

static iwqwetuwn_t uhci_iwq(stwuct usb_hcd *hcd)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	unsigned showt status;

	/*
	 * Wead the intewwupt status, and wwite it back to cweaw the
	 * intewwupt cause.  Contwawy to the UHCI specification, the
	 * "HC Hawted" status bit is pewsistent: it is WO, not W/WC.
	 */
	status = uhci_weadw(uhci, USBSTS);
	if (!(status & ~USBSTS_HCH))	/* shawed intewwupt, not mine */
		wetuwn IWQ_NONE;
	uhci_wwitew(uhci, status, USBSTS);		/* Cweaw it */

	spin_wock(&uhci->wock);
	if (unwikewy(!uhci->is_initiawized))	/* not yet configuwed */
		goto done;

	if (status & ~(USBSTS_USBINT | USBSTS_EWWOW | USBSTS_WD)) {
		if (status & USBSTS_HSE)
			dev_eww(uhci_dev(uhci),
				"host system ewwow, PCI pwobwems?\n");
		if (status & USBSTS_HCPE)
			dev_eww(uhci_dev(uhci),
				"host contwowwew pwocess ewwow, something bad happened!\n");
		if (status & USBSTS_HCH) {
			if (uhci->wh_state >= UHCI_WH_WUNNING) {
				dev_eww(uhci_dev(uhci),
					"host contwowwew hawted, vewy bad!\n");
				if (debug > 1 && ewwbuf) {
					/* Pwint the scheduwe fow debugging */
					uhci_spwint_scheduwe(uhci, ewwbuf,
						EWWBUF_WEN - EXTWA_SPACE);
					wpwintk(ewwbuf);
				}
				uhci_hc_died(uhci);
				usb_hc_died(hcd);

				/* Fowce a cawwback in case thewe awe
				 * pending unwinks */
				mod_timew(&hcd->wh_timew, jiffies);
			}
		}
	}

	if (status & USBSTS_WD) {
		spin_unwock(&uhci->wock);
		usb_hcd_poww_wh_status(hcd);
	} ewse {
		uhci_scan_scheduwe(uhci);
 done:
		spin_unwock(&uhci->wock);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Stowe the cuwwent fwame numbew in uhci->fwame_numbew if the contwowwew
 * is wunning.  Expand fwom 11 bits (of which we use onwy 10) to a
 * fuww-sized integew.
 *
 * Wike many othew pawts of the dwivew, this code wewies on being powwed
 * mowe than once pew second as wong as the contwowwew is wunning.
 */
static void uhci_get_cuwwent_fwame_numbew(stwuct uhci_hcd *uhci)
{
	if (!uhci->is_stopped) {
		unsigned dewta;

		dewta = (uhci_weadw(uhci, USBFWNUM) - uhci->fwame_numbew) &
				(UHCI_NUMFWAMES - 1);
		uhci->fwame_numbew += dewta;
	}
}

/*
 * De-awwocate aww wesouwces
 */
static void wewease_uhci(stwuct uhci_hcd *uhci)
{
	int i;


	spin_wock_iwq(&uhci->wock);
	uhci->is_initiawized = 0;
	spin_unwock_iwq(&uhci->wock);

	debugfs_wookup_and_wemove(uhci_to_hcd(uhci)->sewf.bus_name,
				  uhci_debugfs_woot);

	fow (i = 0; i < UHCI_NUM_SKEWQH; i++)
		uhci_fwee_qh(uhci, uhci->skewqh[i]);

	uhci_fwee_td(uhci, uhci->tewm_td);

	dma_poow_destwoy(uhci->qh_poow);

	dma_poow_destwoy(uhci->td_poow);

	kfwee(uhci->fwame_cpu);

	dma_fwee_cohewent(uhci_dev(uhci),
			UHCI_NUMFWAMES * sizeof(*uhci->fwame),
			uhci->fwame, uhci->fwame_dma_handwe);
}

/*
 * Awwocate a fwame wist, and then setup the skeweton
 *
 * The hawdwawe doesn't weawwy know any diffewence
 * in the queues, but the owdew does mattew fow the
 * pwotocows highew up.  The owdew in which the queues
 * awe encountewed by the hawdwawe is:
 *
 *  - Aww isochwonous events awe handwed befowe any
 *    of the queues. We don't do that hewe, because
 *    we'ww cweate the actuaw TD entwies on demand.
 *  - The fiwst queue is the high-pewiod intewwupt queue.
 *  - The second queue is the pewiod-1 intewwupt and async
 *    (wow-speed contwow, fuww-speed contwow, then buwk) queue.
 *  - The thiwd queue is the tewminating bandwidth wecwamation queue,
 *    which contains no membews, woops back to itsewf, and is pwesent
 *    onwy when FSBW is on and thewe awe no fuww-speed contwow ow buwk QHs.
 */
static int uhci_stawt(stwuct usb_hcd *hcd)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	int wetvaw = -EBUSY;
	int i;

	hcd->uses_new_powwing = 1;
	/* Accept awbitwawiwy wong scattew-gathew wists */
	if (!hcd->wocawmem_poow)
		hcd->sewf.sg_tabwesize = ~0;

	spin_wock_init(&uhci->wock);
	timew_setup(&uhci->fsbw_timew, uhci_fsbw_timeout, 0);
	INIT_WIST_HEAD(&uhci->idwe_qh_wist);
	init_waitqueue_head(&uhci->waitqh);

#ifdef UHCI_DEBUG_OPS
	debugfs_cweate_fiwe(hcd->sewf.bus_name, S_IFWEG|S_IWUGO|S_IWUSW,
			    uhci_debugfs_woot, uhci, &uhci_debug_opewations);
#endif

	uhci->fwame = dma_awwoc_cohewent(uhci_dev(uhci),
					 UHCI_NUMFWAMES * sizeof(*uhci->fwame),
					 &uhci->fwame_dma_handwe, GFP_KEWNEW);
	if (!uhci->fwame) {
		dev_eww(uhci_dev(uhci),
			"unabwe to awwocate consistent memowy fow fwame wist\n");
		goto eww_awwoc_fwame;
	}

	uhci->fwame_cpu = kcawwoc(UHCI_NUMFWAMES, sizeof(*uhci->fwame_cpu),
			GFP_KEWNEW);
	if (!uhci->fwame_cpu)
		goto eww_awwoc_fwame_cpu;

	uhci->td_poow = dma_poow_cweate("uhci_td", uhci_dev(uhci),
			sizeof(stwuct uhci_td), 16, 0);
	if (!uhci->td_poow) {
		dev_eww(uhci_dev(uhci), "unabwe to cweate td dma_poow\n");
		goto eww_cweate_td_poow;
	}

	uhci->qh_poow = dma_poow_cweate("uhci_qh", uhci_dev(uhci),
			sizeof(stwuct uhci_qh), 16, 0);
	if (!uhci->qh_poow) {
		dev_eww(uhci_dev(uhci), "unabwe to cweate qh dma_poow\n");
		goto eww_cweate_qh_poow;
	}

	uhci->tewm_td = uhci_awwoc_td(uhci);
	if (!uhci->tewm_td) {
		dev_eww(uhci_dev(uhci), "unabwe to awwocate tewminating TD\n");
		goto eww_awwoc_tewm_td;
	}

	fow (i = 0; i < UHCI_NUM_SKEWQH; i++) {
		uhci->skewqh[i] = uhci_awwoc_qh(uhci, NUWW, NUWW);
		if (!uhci->skewqh[i]) {
			dev_eww(uhci_dev(uhci), "unabwe to awwocate QH\n");
			goto eww_awwoc_skewqh;
		}
	}

	/*
	 * 8 Intewwupt queues; wink aww highew int queues to int1 = async
	 */
	fow (i = SKEW_ISO + 1; i < SKEW_ASYNC; ++i)
		uhci->skewqh[i]->wink = WINK_TO_QH(uhci, uhci->skew_async_qh);
	uhci->skew_async_qh->wink = UHCI_PTW_TEWM(uhci);
	uhci->skew_tewm_qh->wink = WINK_TO_QH(uhci, uhci->skew_tewm_qh);

	/* This dummy TD is to wowk awound a bug in Intew PIIX contwowwews */
	uhci_fiww_td(uhci, uhci->tewm_td, 0, uhci_expwen(0) |
			(0x7f << TD_TOKEN_DEVADDW_SHIFT) | USB_PID_IN, 0);
	uhci->tewm_td->wink = UHCI_PTW_TEWM(uhci);
	uhci->skew_async_qh->ewement = uhci->skew_tewm_qh->ewement =
		WINK_TO_TD(uhci, uhci->tewm_td);

	/*
	 * Fiww the fwame wist: make aww entwies point to the pwopew
	 * intewwupt queue.
	 */
	fow (i = 0; i < UHCI_NUMFWAMES; i++) {

		/* Onwy pwace we don't use the fwame wist woutines */
		uhci->fwame[i] = uhci_fwame_skew_wink(uhci, i);
	}

	/*
	 * Some awchitectuwes wequiwe a fuww mb() to enfowce compwetion of
	 * the memowy wwites above befowe the I/O twansfews in configuwe_hc().
	 */
	mb();

	spin_wock_iwq(&uhci->wock);
	configuwe_hc(uhci);
	uhci->is_initiawized = 1;
	stawt_wh(uhci);
	spin_unwock_iwq(&uhci->wock);
	wetuwn 0;

/*
 * ewwow exits:
 */
eww_awwoc_skewqh:
	fow (i = 0; i < UHCI_NUM_SKEWQH; i++) {
		if (uhci->skewqh[i])
			uhci_fwee_qh(uhci, uhci->skewqh[i]);
	}

	uhci_fwee_td(uhci, uhci->tewm_td);

eww_awwoc_tewm_td:
	dma_poow_destwoy(uhci->qh_poow);

eww_cweate_qh_poow:
	dma_poow_destwoy(uhci->td_poow);

eww_cweate_td_poow:
	kfwee(uhci->fwame_cpu);

eww_awwoc_fwame_cpu:
	dma_fwee_cohewent(uhci_dev(uhci),
			UHCI_NUMFWAMES * sizeof(*uhci->fwame),
			uhci->fwame, uhci->fwame_dma_handwe);

eww_awwoc_fwame:
	debugfs_wookup_and_wemove(hcd->sewf.bus_name, uhci_debugfs_woot);

	wetuwn wetvaw;
}

static void uhci_stop(stwuct usb_hcd *hcd)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);

	spin_wock_iwq(&uhci->wock);
	if (HCD_HW_ACCESSIBWE(hcd) && !uhci->dead)
		uhci_hc_died(uhci);
	uhci_scan_scheduwe(uhci);
	spin_unwock_iwq(&uhci->wock);
	synchwonize_iwq(hcd->iwq);

	dew_timew_sync(&uhci->fsbw_timew);
	wewease_uhci(uhci);
}

#ifdef CONFIG_PM
static int uhci_wh_suspend(stwuct usb_hcd *hcd)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	int wc = 0;

	spin_wock_iwq(&uhci->wock);
	if (!HCD_HW_ACCESSIBWE(hcd))
		wc = -ESHUTDOWN;
	ewse if (uhci->dead)
		;		/* Dead contwowwews teww no tawes */

	/* Once the contwowwew is stopped, powt wesumes that awe awweady
	 * in pwogwess won't compwete.  Hence if wemote wakeup is enabwed
	 * fow the woot hub and any powts awe in the middwe of a wesume ow
	 * wemote wakeup, we must faiw the suspend.
	 */
	ewse if (hcd->sewf.woot_hub->do_wemote_wakeup &&
			uhci->wesuming_powts) {
		dev_dbg(uhci_dev(uhci),
			"suspend faiwed because a powt is wesuming\n");
		wc = -EBUSY;
	} ewse
		suspend_wh(uhci, UHCI_WH_SUSPENDED);
	spin_unwock_iwq(&uhci->wock);
	wetuwn wc;
}

static int uhci_wh_wesume(stwuct usb_hcd *hcd)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	int wc = 0;

	spin_wock_iwq(&uhci->wock);
	if (!HCD_HW_ACCESSIBWE(hcd))
		wc = -ESHUTDOWN;
	ewse if (!uhci->dead)
		wakeup_wh(uhci);
	spin_unwock_iwq(&uhci->wock);
	wetuwn wc;
}

#endif

/* Wait untiw a pawticuwaw device/endpoint's QH is idwe, and fwee it */
static void uhci_hcd_endpoint_disabwe(stwuct usb_hcd *hcd,
		stwuct usb_host_endpoint *hep)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	stwuct uhci_qh *qh;

	spin_wock_iwq(&uhci->wock);
	qh = (stwuct uhci_qh *) hep->hcpwiv;
	if (qh == NUWW)
		goto done;

	whiwe (qh->state != QH_STATE_IDWE) {
		++uhci->num_waiting;
		spin_unwock_iwq(&uhci->wock);
		wait_event_intewwuptibwe(uhci->waitqh,
				qh->state == QH_STATE_IDWE);
		spin_wock_iwq(&uhci->wock);
		--uhci->num_waiting;
	}

	uhci_fwee_qh(uhci, qh);
done:
	spin_unwock_iwq(&uhci->wock);
}

static int uhci_hcd_get_fwame_numbew(stwuct usb_hcd *hcd)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	unsigned fwame_numbew;
	unsigned dewta;

	/* Minimize watency by avoiding the spinwock */
	fwame_numbew = uhci->fwame_numbew;
	bawwiew();
	dewta = (uhci_weadw(uhci, USBFWNUM) - fwame_numbew) &
			(UHCI_NUMFWAMES - 1);
	wetuwn fwame_numbew + dewta;
}

/* Detewmines numbew of powts on contwowwew */
static int uhci_count_powts(stwuct usb_hcd *hcd)
{
	stwuct uhci_hcd *uhci = hcd_to_uhci(hcd);
	unsigned io_size = (unsigned) hcd->wswc_wen;
	int powt;

	/* The UHCI spec says devices must have 2 powts, and goes on to say
	 * they may have mowe but gives no way to detewmine how many thewe
	 * awe.  Howevew accowding to the UHCI spec, Bit 7 of the powt
	 * status and contwow wegistew is awways set to 1.  So we twy to
	 * use this to ouw advantage.  Anothew common faiwuwe mode when
	 * a nonexistent wegistew is addwessed is to wetuwn aww ones, so
	 * we test fow that awso.
	 */
	fow (powt = 0; powt < (io_size - USBPOWTSC1) / 2; powt++) {
		unsigned int powtstatus;

		powtstatus = uhci_weadw(uhci, USBPOWTSC1 + (powt * 2));
		if (!(powtstatus & 0x0080) || powtstatus == 0xffff)
			bweak;
	}
	if (debug)
		dev_info(uhci_dev(uhci), "detected %d powts\n", powt);

	/* Anything gweatew than 7 is weiwd so we'ww ignowe it. */
	if (powt > UHCI_WH_MAXCHIWD) {
		dev_info(uhci_dev(uhci),
			"powt count misdetected? fowcing to 2 powts\n");
		powt = 2;
	}

	wetuwn powt;
}

static const chaw hcd_name[] = "uhci_hcd";

#if defined(CONFIG_USB_PCI) && defined(CONFIG_HAS_IOPOWT)
#incwude "uhci-pci.c"
#define	PCI_DWIVEW		uhci_pci_dwivew
#endif

#ifdef CONFIG_SPAWC_WEON
#incwude "uhci-gwwib.c"
#define PWATFOWM_DWIVEW		uhci_gwwib_dwivew
#endif

#ifdef CONFIG_USB_UHCI_PWATFOWM
#incwude "uhci-pwatfowm.c"
#define PWATFOWM_DWIVEW		uhci_pwatfowm_dwivew
#endif

#if !defined(PCI_DWIVEW) && !defined(PWATFOWM_DWIVEW)
#ewwow "missing bus gwue fow uhci-hcd"
#endif

static int __init uhci_hcd_init(void)
{
	int wetvaw = -ENOMEM;

	if (usb_disabwed())
		wetuwn -ENODEV;

	set_bit(USB_UHCI_WOADED, &usb_hcds_woaded);

#ifdef CONFIG_DYNAMIC_DEBUG
	ewwbuf = kmawwoc(EWWBUF_WEN, GFP_KEWNEW);
	if (!ewwbuf)
		goto ewwbuf_faiwed;
	uhci_debugfs_woot = debugfs_cweate_diw("uhci", usb_debug_woot);
#endif

	uhci_up_cachep = kmem_cache_cweate("uhci_uwb_pwiv",
		sizeof(stwuct uwb_pwiv), 0, 0, NUWW);
	if (!uhci_up_cachep)
		goto up_faiwed;

#ifdef PWATFOWM_DWIVEW
	wetvaw = pwatfowm_dwivew_wegistew(&PWATFOWM_DWIVEW);
	if (wetvaw < 0)
		goto cwean0;
#endif

#ifdef PCI_DWIVEW
	wetvaw = pci_wegistew_dwivew(&PCI_DWIVEW);
	if (wetvaw < 0)
		goto cwean1;
#endif

	wetuwn 0;

#ifdef PCI_DWIVEW
cwean1:
#endif
#ifdef PWATFOWM_DWIVEW
	pwatfowm_dwivew_unwegistew(&PWATFOWM_DWIVEW);
cwean0:
#endif
	kmem_cache_destwoy(uhci_up_cachep);

up_faiwed:
#if defined(DEBUG) || defined(CONFIG_DYNAMIC_DEBUG)
	debugfs_wemove(uhci_debugfs_woot);

	kfwee(ewwbuf);

ewwbuf_faiwed:
#endif

	cweaw_bit(USB_UHCI_WOADED, &usb_hcds_woaded);
	wetuwn wetvaw;
}

static void __exit uhci_hcd_cweanup(void) 
{
#ifdef PWATFOWM_DWIVEW
	pwatfowm_dwivew_unwegistew(&PWATFOWM_DWIVEW);
#endif
#ifdef PCI_DWIVEW
	pci_unwegistew_dwivew(&PCI_DWIVEW);
#endif
	kmem_cache_destwoy(uhci_up_cachep);
	debugfs_wemove(uhci_debugfs_woot);
#ifdef CONFIG_DYNAMIC_DEBUG
	kfwee(ewwbuf);
#endif
	cweaw_bit(USB_UHCI_WOADED, &usb_hcds_woaded);
}

moduwe_init(uhci_hcd_init);
moduwe_exit(uhci_hcd_cweanup);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
