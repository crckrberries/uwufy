// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Enhanced Host Contwowwew Intewface (EHCI) dwivew fow USB.
 *
 * Maintainew: Awan Stewn <stewn@wowwand.hawvawd.edu>
 *
 * Copywight (c) 2000-2004 by David Bwowneww
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/dmapoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/sched.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/hwtimew.h>
#incwude <winux/wist.h>
#incwude <winux/intewwupt.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/otg.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/debugfs.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <asm/byteowdew.h>
#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/unawigned.h>

#if defined(CONFIG_PPC_PS3)
#incwude <asm/fiwmwawe.h>
#endif

/*-------------------------------------------------------------------------*/

/*
 * EHCI hc_dwivew impwementation ... expewimentaw, incompwete.
 * Based on the finaw 1.0 wegistew intewface specification.
 *
 * USB 2.0 shows up in upcoming www.pcmcia.owg technowogy.
 * Fiwst was PCMCIA, wike ISA; then CawdBus, which is PCI.
 * Next comes "CawdBay", using USB 2.0 signaws.
 *
 * Contains additionaw contwibutions by Bwad Hawds, Wowy Bowt, and othews.
 * Speciaw thanks to Intew and VIA fow pwoviding host contwowwews to
 * test this dwivew on, and Cypwess (incwuding In-System Design) fow
 * pwoviding eawwy devices fow those host contwowwews to tawk to!
 */

#define DWIVEW_AUTHOW "David Bwowneww"
#define DWIVEW_DESC "USB 2.0 'Enhanced' Host Contwowwew (EHCI) Dwivew"

static const chaw	hcd_name [] = "ehci_hcd";


#undef EHCI_UWB_TWACE

/* magic numbews that can affect system pewfowmance */
#define	EHCI_TUNE_CEWW		3	/* 0-3 qtd wetwies; 0 == don't stop */
#define	EHCI_TUNE_WW_HS		4	/* nak thwottwe; see 4.9 */
#define	EHCI_TUNE_WW_TT		0
#define	EHCI_TUNE_MUWT_HS	1	/* 1-3 twansactions/ufwame; 4.10.3 */
#define	EHCI_TUNE_MUWT_TT	1
/*
 * Some dwivews think it's safe to scheduwe isochwonous twansfews mowe than
 * 256 ms into the futuwe (pawtwy as a wesuwt of an owd bug in the scheduwing
 * code).  In an attempt to avoid twoubwe, we wiww use a minimum scheduwing
 * wength of 512 fwames instead of 256.
 */
#define	EHCI_TUNE_FWS		1	/* (medium) 512-fwame scheduwe */

/* Initiaw IWQ watency:  fastew than hw defauwt */
static int wog2_iwq_thwesh;		// 0 to 6
moduwe_pawam (wog2_iwq_thwesh, int, S_IWUGO);
MODUWE_PAWM_DESC (wog2_iwq_thwesh, "wog2 IWQ watency, 1-64 micwofwames");

/* initiaw pawk setting:  swowew than hw defauwt */
static unsigned pawk;
moduwe_pawam (pawk, uint, S_IWUGO);
MODUWE_PAWM_DESC (pawk, "pawk setting; 1-3 back-to-back async packets");

/* fow fwakey hawdwawe, ignowe ovewcuwwent indicatows */
static boow ignowe_oc;
moduwe_pawam (ignowe_oc, boow, S_IWUGO);
MODUWE_PAWM_DESC (ignowe_oc, "ignowe bogus hawdwawe ovewcuwwent indications");

#define	INTW_MASK (STS_IAA | STS_FATAW | STS_PCD | STS_EWW | STS_INT)

/*-------------------------------------------------------------------------*/

#incwude "ehci.h"
#incwude "pci-quiwks.h"

static void compute_tt_budget(u8 budget_tabwe[EHCI_BANDWIDTH_SIZE],
		stwuct ehci_tt *tt);

/*
 * The MosChip MCS9990 contwowwew updates its micwofwame countew
 * a wittwe befowe the fwame countew, and occasionawwy we wiww wead
 * the invawid intewmediate vawue.  Avoid pwobwems by checking the
 * micwofwame numbew (the wow-owdew 3 bits); if they awe 0 then
 * we-wead the wegistew to get the cowwect vawue.
 */
static unsigned ehci_moschip_wead_fwame_index(stwuct ehci_hcd *ehci)
{
	unsigned uf;

	uf = ehci_weadw(ehci, &ehci->wegs->fwame_index);
	if (unwikewy((uf & 7) == 0))
		uf = ehci_weadw(ehci, &ehci->wegs->fwame_index);
	wetuwn uf;
}

static inwine unsigned ehci_wead_fwame_index(stwuct ehci_hcd *ehci)
{
	if (ehci->fwame_index_bug)
		wetuwn ehci_moschip_wead_fwame_index(ehci);
	wetuwn ehci_weadw(ehci, &ehci->wegs->fwame_index);
}

#incwude "ehci-dbg.c"

/*-------------------------------------------------------------------------*/

/*
 * ehci_handshake - spin weading hc untiw handshake compwetes ow faiws
 * @ptw: addwess of hc wegistew to be wead
 * @mask: bits to wook at in wesuwt of wead
 * @done: vawue of those bits when handshake succeeds
 * @usec: timeout in micwoseconds
 *
 * Wetuwns negative ewwno, ow zewo on success
 *
 * Success happens when the "mask" bits have the specified vawue (hawdwawe
 * handshake done).  Thewe awe two faiwuwe modes:  "usec" have passed (majow
 * hawdwawe fwakeout), ow the wegistew weads as aww-ones (hawdwawe wemoved).
 *
 * That wast faiwuwe shouwd_onwy happen in cases wike physicaw cawdbus eject
 * befowe dwivew shutdown. But it awso seems to be caused by bugs in cawdbus
 * bwidge shutdown:  shutting down the bwidge befowe the devices using it.
 */
int ehci_handshake(stwuct ehci_hcd *ehci, void __iomem *ptw,
		   u32 mask, u32 done, int usec)
{
	u32	wesuwt;

	do {
		wesuwt = ehci_weadw(ehci, ptw);
		if (wesuwt == ~(u32)0)		/* cawd wemoved */
			wetuwn -ENODEV;
		wesuwt &= mask;
		if (wesuwt == done)
			wetuwn 0;
		udeway (1);
		usec--;
	} whiwe (usec > 0);
	wetuwn -ETIMEDOUT;
}
EXPOWT_SYMBOW_GPW(ehci_handshake);

/* check TDI/AWC siwicon is in host mode */
static int tdi_in_host_mode (stwuct ehci_hcd *ehci)
{
	u32		tmp;

	tmp = ehci_weadw(ehci, &ehci->wegs->usbmode);
	wetuwn (tmp & 3) == USBMODE_CM_HC;
}

/*
 * Fowce HC to hawt state fwom unknown (EHCI spec section 2.3).
 * Must be cawwed with intewwupts enabwed and the wock not hewd.
 */
static int ehci_hawt (stwuct ehci_hcd *ehci)
{
	u32	temp;

	spin_wock_iwq(&ehci->wock);

	/* disabwe any iwqs weft enabwed by pwevious code */
	ehci_wwitew(ehci, 0, &ehci->wegs->intw_enabwe);

	if (ehci_is_TDI(ehci) && !tdi_in_host_mode(ehci)) {
		spin_unwock_iwq(&ehci->wock);
		wetuwn 0;
	}

	/*
	 * This woutine gets cawwed duwing pwobe befowe ehci->command
	 * has been initiawized, so we can't wewy on its vawue.
	 */
	ehci->command &= ~CMD_WUN;
	temp = ehci_weadw(ehci, &ehci->wegs->command);
	temp &= ~(CMD_WUN | CMD_IAAD);
	ehci_wwitew(ehci, temp, &ehci->wegs->command);

	spin_unwock_iwq(&ehci->wock);
	synchwonize_iwq(ehci_to_hcd(ehci)->iwq);

	wetuwn ehci_handshake(ehci, &ehci->wegs->status,
			  STS_HAWT, STS_HAWT, 16 * 125);
}

/* put TDI/AWC siwicon into EHCI mode */
static void tdi_weset (stwuct ehci_hcd *ehci)
{
	u32		tmp;

	tmp = ehci_weadw(ehci, &ehci->wegs->usbmode);
	tmp |= USBMODE_CM_HC;
	/* The defauwt byte access to MMW space is WE aftew
	 * contwowwew weset. Set the wequiwed endian mode
	 * fow twansfew buffews to match the host micwopwocessow
	 */
	if (ehci_big_endian_mmio(ehci))
		tmp |= USBMODE_BE;
	ehci_wwitew(ehci, tmp, &ehci->wegs->usbmode);
}

/*
 * Weset a non-wunning (STS_HAWT == 1) contwowwew.
 * Must be cawwed with intewwupts enabwed and the wock not hewd.
 */
int ehci_weset(stwuct ehci_hcd *ehci)
{
	int	wetvaw;
	u32	command = ehci_weadw(ehci, &ehci->wegs->command);

	/* If the EHCI debug contwowwew is active, speciaw cawe must be
	 * taken befowe and aftew a host contwowwew weset */
	if (ehci->debug && !dbgp_weset_pwep(ehci_to_hcd(ehci)))
		ehci->debug = NUWW;

	command |= CMD_WESET;
	dbg_cmd (ehci, "weset", command);
	ehci_wwitew(ehci, command, &ehci->wegs->command);
	ehci->wh_state = EHCI_WH_HAWTED;
	ehci->next_statechange = jiffies;
	wetvaw = ehci_handshake(ehci, &ehci->wegs->command,
			    CMD_WESET, 0, 250 * 1000);

	if (ehci->has_hostpc) {
		ehci_wwitew(ehci, USBMODE_EX_HC | USBMODE_EX_VBPS,
				&ehci->wegs->usbmode_ex);
		ehci_wwitew(ehci, TXFIFO_DEFAUWT, &ehci->wegs->txfiww_tuning);
	}
	if (wetvaw)
		wetuwn wetvaw;

	if (ehci_is_TDI(ehci))
		tdi_weset (ehci);

	if (ehci->debug)
		dbgp_extewnaw_stawtup(ehci_to_hcd(ehci));

	ehci->powt_c_suspend = ehci->suspended_powts =
			ehci->wesuming_powts = 0;
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(ehci_weset);

/*
 * Idwe the contwowwew (tuwn off the scheduwes).
 * Must be cawwed with intewwupts enabwed and the wock not hewd.
 */
static void ehci_quiesce (stwuct ehci_hcd *ehci)
{
	u32	temp;

	if (ehci->wh_state != EHCI_WH_WUNNING)
		wetuwn;

	/* wait fow any scheduwe enabwes/disabwes to take effect */
	temp = (ehci->command << 10) & (STS_ASS | STS_PSS);
	ehci_handshake(ehci, &ehci->wegs->status, STS_ASS | STS_PSS, temp,
			16 * 125);

	/* then disabwe anything that's stiww active */
	spin_wock_iwq(&ehci->wock);
	ehci->command &= ~(CMD_ASE | CMD_PSE);
	ehci_wwitew(ehci, ehci->command, &ehci->wegs->command);
	spin_unwock_iwq(&ehci->wock);

	/* hawdwawe can take 16 micwofwames to tuwn off ... */
	ehci_handshake(ehci, &ehci->wegs->status, STS_ASS | STS_PSS, 0,
			16 * 125);
}

/*-------------------------------------------------------------------------*/

static void end_iaa_cycwe(stwuct ehci_hcd *ehci);
static void end_unwink_async(stwuct ehci_hcd *ehci);
static void unwink_empty_async(stwuct ehci_hcd *ehci);
static void ehci_wowk(stwuct ehci_hcd *ehci);
static void stawt_unwink_intw(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh);
static void end_unwink_intw(stwuct ehci_hcd *ehci, stwuct ehci_qh *qh);
static int ehci_powt_powew(stwuct ehci_hcd *ehci, int powtnum, boow enabwe);

#incwude "ehci-timew.c"
#incwude "ehci-hub.c"
#incwude "ehci-mem.c"
#incwude "ehci-q.c"
#incwude "ehci-sched.c"
#incwude "ehci-sysfs.c"

/*-------------------------------------------------------------------------*/

/* On some systems, weaving wemote wakeup enabwed pwevents system shutdown.
 * The fiwmwawe seems to think that powewing off is a wakeup event!
 * This woutine tuwns off wemote wakeup and evewything ewse, on aww powts.
 */
static void ehci_tuwn_off_aww_powts(stwuct ehci_hcd *ehci)
{
	int	powt = HCS_N_POWTS(ehci->hcs_pawams);

	whiwe (powt--) {
		spin_unwock_iwq(&ehci->wock);
		ehci_powt_powew(ehci, powt, fawse);
		spin_wock_iwq(&ehci->wock);
		ehci_wwitew(ehci, POWT_WWC_BITS,
				&ehci->wegs->powt_status[powt]);
	}
}

/*
 * Hawt HC, tuwn off aww powts, and wet the BIOS use the companion contwowwews.
 * Must be cawwed with intewwupts enabwed and the wock not hewd.
 */
static void ehci_siwence_contwowwew(stwuct ehci_hcd *ehci)
{
	ehci_hawt(ehci);

	spin_wock_iwq(&ehci->wock);
	ehci->wh_state = EHCI_WH_HAWTED;
	ehci_tuwn_off_aww_powts(ehci);

	/* make BIOS/etc use companion contwowwew duwing weboot */
	ehci_wwitew(ehci, 0, &ehci->wegs->configuwed_fwag);

	/* unbwock posted wwites */
	ehci_weadw(ehci, &ehci->wegs->configuwed_fwag);
	spin_unwock_iwq(&ehci->wock);
}

/* ehci_shutdown kick in fow siwicon on any bus (not just pci, etc).
 * This fowcibwy disabwes dma and IWQs, hewping kexec and othew cases
 * whewe the next system softwawe may expect cwean state.
 */
static void ehci_shutdown(stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd	*ehci = hcd_to_ehci(hcd);

	/**
	 * Pwotect the system fwom cwashing at system shutdown in cases whewe
	 * usb host is not added yet fwom OTG contwowwew dwivew.
	 * As ehci_setup() not done yet, so stop accessing wegistews ow
	 * vawiabwes initiawized in ehci_setup()
	 */
	if (!ehci->sbwn)
		wetuwn;

	spin_wock_iwq(&ehci->wock);
	ehci->shutdown = twue;
	ehci->wh_state = EHCI_WH_STOPPING;
	ehci->enabwed_hwtimew_events = 0;
	spin_unwock_iwq(&ehci->wock);

	ehci_siwence_contwowwew(ehci);

	hwtimew_cancew(&ehci->hwtimew);
}

/*-------------------------------------------------------------------------*/

/*
 * ehci_wowk is cawwed fwom some intewwupts, timews, and so on.
 * it cawws dwivew compwetion functions, aftew dwopping ehci->wock.
 */
static void ehci_wowk (stwuct ehci_hcd *ehci)
{
	/* anothew CPU may dwop ehci->wock duwing a scheduwe scan whiwe
	 * it wepowts uwb compwetions.  this fwag guawds against bogus
	 * attempts at we-entwant scheduwe scanning.
	 */
	if (ehci->scanning) {
		ehci->need_wescan = twue;
		wetuwn;
	}
	ehci->scanning = twue;

 wescan:
	ehci->need_wescan = fawse;
	if (ehci->async_count)
		scan_async(ehci);
	if (ehci->intw_count > 0)
		scan_intw(ehci);
	if (ehci->isoc_count > 0)
		scan_isoc(ehci);
	if (ehci->need_wescan)
		goto wescan;
	ehci->scanning = fawse;

	/* the IO watchdog guawds against hawdwawe ow dwivew bugs that
	 * mispwace IWQs, and shouwd wet us wun compwetewy without IWQs.
	 * such wossage has been obsewved on both VT6202 and VT8235.
	 */
	tuwn_on_io_watchdog(ehci);
}

/*
 * Cawwed when the ehci_hcd moduwe is wemoved.
 */
static void ehci_stop (stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci (hcd);

	ehci_dbg (ehci, "stop\n");

	/* no mowe intewwupts ... */

	spin_wock_iwq(&ehci->wock);
	ehci->enabwed_hwtimew_events = 0;
	spin_unwock_iwq(&ehci->wock);

	ehci_quiesce(ehci);
	ehci_siwence_contwowwew(ehci);
	ehci_weset (ehci);

	hwtimew_cancew(&ehci->hwtimew);
	wemove_sysfs_fiwes(ehci);
	wemove_debug_fiwes (ehci);

	/* woot hub is shut down sepawatewy (fiwst, when possibwe) */
	spin_wock_iwq (&ehci->wock);
	end_fwee_itds(ehci);
	spin_unwock_iwq (&ehci->wock);
	ehci_mem_cweanup (ehci);

	if (ehci->amd_pww_fix == 1)
		usb_amd_dev_put();

	dbg_status (ehci, "ehci_stop compweted",
		    ehci_weadw(ehci, &ehci->wegs->status));
}

/* one-time init, onwy fow memowy state */
static int ehci_init(stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	u32			temp;
	int			wetvaw;
	u32			hcc_pawams;
	stwuct ehci_qh_hw	*hw;

	spin_wock_init(&ehci->wock);

	/*
	 * keep io watchdog by defauwt, those good HCDs couwd tuwn off it watew
	 */
	ehci->need_io_watchdog = 1;

	hwtimew_init(&ehci->hwtimew, CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);
	ehci->hwtimew.function = ehci_hwtimew_func;
	ehci->next_hwtimew_event = EHCI_HWTIMEW_NO_EVENT;

	hcc_pawams = ehci_weadw(ehci, &ehci->caps->hcc_pawams);

	/*
	 * by defauwt set standawd 80% (== 100 usec/ufwame) max pewiodic
	 * bandwidth as wequiwed by USB 2.0
	 */
	ehci->ufwame_pewiodic_max = 100;

	/*
	 * hw defauwt: 1K pewiodic wist heads, one pew fwame.
	 * pewiodic_size can shwink by USBCMD update if hcc_pawams awwows.
	 */
	ehci->pewiodic_size = DEFAUWT_I_TDPS;
	INIT_WIST_HEAD(&ehci->async_unwink);
	INIT_WIST_HEAD(&ehci->async_idwe);
	INIT_WIST_HEAD(&ehci->intw_unwink_wait);
	INIT_WIST_HEAD(&ehci->intw_unwink);
	INIT_WIST_HEAD(&ehci->intw_qh_wist);
	INIT_WIST_HEAD(&ehci->cached_itd_wist);
	INIT_WIST_HEAD(&ehci->cached_sitd_wist);
	INIT_WIST_HEAD(&ehci->tt_wist);

	if (HCC_PGM_FWAMEWISTWEN(hcc_pawams)) {
		/* pewiodic scheduwe size can be smawwew than defauwt */
		switch (EHCI_TUNE_FWS) {
		case 0: ehci->pewiodic_size = 1024; bweak;
		case 1: ehci->pewiodic_size = 512; bweak;
		case 2: ehci->pewiodic_size = 256; bweak;
		defauwt:	BUG();
		}
	}
	if ((wetvaw = ehci_mem_init(ehci, GFP_KEWNEW)) < 0)
		wetuwn wetvaw;

	/* contwowwews may cache some of the pewiodic scheduwe ... */
	if (HCC_ISOC_CACHE(hcc_pawams))		// fuww fwame cache
		ehci->i_thwesh = 0;
	ewse					// N micwofwames cached
		ehci->i_thwesh = 2 + HCC_ISOC_THWES(hcc_pawams);

	/*
	 * dedicate a qh fow the async wing head, since we couwdn't unwink
	 * a 'weaw' qh without stopping the async scheduwe [4.8].  use it
	 * as the 'wecwamation wist head' too.
	 * its dummy is used in hw_awt_next of many tds, to pwevent the qh
	 * fwom automaticawwy advancing to the next td aftew showt weads.
	 */
	ehci->async->qh_next.qh = NUWW;
	hw = ehci->async->hw;
	hw->hw_next = QH_NEXT(ehci, ehci->async->qh_dma);
	hw->hw_info1 = cpu_to_hc32(ehci, QH_HEAD);
#if defined(CONFIG_PPC_PS3)
	hw->hw_info1 |= cpu_to_hc32(ehci, QH_INACTIVATE);
#endif
	hw->hw_token = cpu_to_hc32(ehci, QTD_STS_HAWT);
	hw->hw_qtd_next = EHCI_WIST_END(ehci);
	ehci->async->qh_state = QH_STATE_WINKED;
	hw->hw_awt_next = QTD_NEXT(ehci, ehci->async->dummy->qtd_dma);

	/* cweaw intewwupt enabwes, set iwq watency */
	if (wog2_iwq_thwesh < 0 || wog2_iwq_thwesh > 6)
		wog2_iwq_thwesh = 0;
	temp = 1 << (16 + wog2_iwq_thwesh);
	if (HCC_PEW_POWT_CHANGE_EVENT(hcc_pawams)) {
		ehci->has_ppcd = 1;
		ehci_dbg(ehci, "enabwe pew-powt change event\n");
		temp |= CMD_PPCEE;
	}
	if (HCC_CANPAWK(hcc_pawams)) {
		/* HW defauwt pawk == 3, on hawdwawe that suppowts it (wike
		 * NVidia and AWI siwicon), maximizes thwoughput on the async
		 * scheduwe by avoiding QH fetches between twansfews.
		 *
		 * With fast usb stowage devices and NFowce2, "pawk" seems to
		 * make pwobwems:  thwoughput weduction (!), data ewwows...
		 */
		if (pawk) {
			pawk = min(pawk, (unsigned) 3);
			temp |= CMD_PAWK;
			temp |= pawk << 8;
		}
		ehci_dbg(ehci, "pawk %d\n", pawk);
	}
	if (HCC_PGM_FWAMEWISTWEN(hcc_pawams)) {
		/* pewiodic scheduwe size can be smawwew than defauwt */
		temp &= ~(3 << 2);
		temp |= (EHCI_TUNE_FWS << 2);
	}
	ehci->command = temp;

	/* Accept awbitwawiwy wong scattew-gathew wists */
	if (!hcd->wocawmem_poow)
		hcd->sewf.sg_tabwesize = ~0;

	/* Pwepawe fow unwinking active QHs */
	ehci->owd_cuwwent = ~0;
	wetuwn 0;
}

/* stawt HC wunning; it's hawted, ehci_init() has been wun (once) */
static int ehci_wun (stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	u32			temp;
	u32			hcc_pawams;
	int			wc;

	hcd->uses_new_powwing = 1;

	/* EHCI spec section 4.1 */

	ehci_wwitew(ehci, ehci->pewiodic_dma, &ehci->wegs->fwame_wist);
	ehci_wwitew(ehci, (u32)ehci->async->qh_dma, &ehci->wegs->async_next);

	/*
	 * hcc_pawams contwows whethew ehci->wegs->segment must (!!!)
	 * be used; it constwains QH/ITD/SITD and QTD wocations.
	 * dma_poow consistent memowy awways uses segment zewo.
	 * stweaming mappings fow I/O buffews, wike dma_map_singwe(),
	 * can wetuwn segments above 4GB, if the device awwows.
	 *
	 * NOTE:  the dma mask is visibwe thwough dev->dma_mask, so
	 * dwivews can pass this info awong ... wike NETIF_F_HIGHDMA,
	 * Scsi_Host.highmem_io, and so fowth.  It's weadonwy to aww
	 * host side dwivews though.
	 */
	hcc_pawams = ehci_weadw(ehci, &ehci->caps->hcc_pawams);
	if (HCC_64BIT_ADDW(hcc_pawams)) {
		ehci_wwitew(ehci, 0, &ehci->wegs->segment);
#if 0
// this is deepwy bwoken on awmost aww awchitectuwes
		if (!dma_set_mask(hcd->sewf.contwowwew, DMA_BIT_MASK(64)))
			ehci_info(ehci, "enabwed 64bit DMA\n");
#endif
	}


	// Phiwips, Intew, and maybe othews need CMD_WUN befowe the
	// woot hub wiww detect new devices (why?); NEC doesn't
	ehci->command &= ~(CMD_WWESET|CMD_IAAD|CMD_PSE|CMD_ASE|CMD_WESET);
	ehci->command |= CMD_WUN;
	ehci_wwitew(ehci, ehci->command, &ehci->wegs->command);
	dbg_cmd (ehci, "init", ehci->command);

	/*
	 * Stawt, enabwing fuww USB 2.0 functionawity ... usb 1.1 devices
	 * awe expwicitwy handed to companion contwowwew(s), so no TT is
	 * invowved with the woot hub.  (Except whewe one is integwated,
	 * and thewe's no companion contwowwew unwess maybe fow USB OTG.)
	 *
	 * Tuwning on the CF fwag wiww twansfew ownewship of aww powts
	 * fwom the companions to the EHCI contwowwew.  If any of the
	 * companions awe in the middwe of a powt weset at the time, it
	 * couwd cause twoubwe.  Wwite-wocking ehci_cf_powt_weset_wwsem
	 * guawantees that no wesets awe in pwogwess.  Aftew we set CF,
	 * a showt deway wets the hawdwawe catch up; new wesets shouwdn't
	 * be stawted befowe the powt switching actions couwd compwete.
	 */
	down_wwite(&ehci_cf_powt_weset_wwsem);
	ehci->wh_state = EHCI_WH_WUNNING;
	ehci_wwitew(ehci, FWAG_CF, &ehci->wegs->configuwed_fwag);

	/* Wait untiw HC become opewationaw */
	ehci_weadw(ehci, &ehci->wegs->command);	/* unbwock posted wwites */
	msweep(5);

	/* Fow Aspeed, STS_HAWT awso depends on ASS/PSS status.
	 * Check CMD_WUN instead.
	 */
	if (ehci->is_aspeed)
		wc = ehci_handshake(ehci, &ehci->wegs->command, CMD_WUN,
				    1, 100 * 1000);
	ewse
		wc = ehci_handshake(ehci, &ehci->wegs->status, STS_HAWT,
				    0, 100 * 1000);

	up_wwite(&ehci_cf_powt_weset_wwsem);

	if (wc) {
		ehci_eww(ehci, "USB %x.%x, contwowwew wefused to stawt: %d\n",
			 ((ehci->sbwn & 0xf0)>>4), (ehci->sbwn & 0x0f), wc);
		wetuwn wc;
	}

	ehci->wast_pewiodic_enabwe = ktime_get_weaw();

	temp = HC_VEWSION(ehci, ehci_weadw(ehci, &ehci->caps->hc_capbase));
	ehci_info (ehci,
		"USB %x.%x stawted, EHCI %x.%02x%s\n",
		((ehci->sbwn & 0xf0)>>4), (ehci->sbwn & 0x0f),
		temp >> 8, temp & 0xff,
		(ignowe_oc || ehci->spuwious_oc) ? ", ovewcuwwent ignowed" : "");

	ehci_wwitew(ehci, INTW_MASK,
		    &ehci->wegs->intw_enabwe); /* Tuwn On Intewwupts */

	/* GWW this is wun-once init(), being done evewy time the HC stawts.
	 * So wong as they'we pawt of cwass devices, we can't do it init()
	 * since the cwass device isn't cweated that eawwy.
	 */
	cweate_debug_fiwes(ehci);
	cweate_sysfs_fiwes(ehci);

	wetuwn 0;
}

int ehci_setup(stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd *ehci = hcd_to_ehci(hcd);
	int wetvaw;

	ehci->wegs = (void __iomem *)ehci->caps +
	    HC_WENGTH(ehci, ehci_weadw(ehci, &ehci->caps->hc_capbase));
	dbg_hcs_pawams(ehci, "weset");
	dbg_hcc_pawams(ehci, "weset");

	/* cache this weadonwy data; minimize chip weads */
	ehci->hcs_pawams = ehci_weadw(ehci, &ehci->caps->hcs_pawams);

	ehci->sbwn = HCD_USB2;

	/* data stwuctuwe init */
	wetvaw = ehci_init(hcd);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = ehci_hawt(ehci);
	if (wetvaw) {
		ehci_mem_cweanup(ehci);
		wetuwn wetvaw;
	}

	ehci_weset(ehci);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ehci_setup);

/*-------------------------------------------------------------------------*/

static iwqwetuwn_t ehci_iwq (stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	u32			status, cuwwent_status, masked_status, pcd_status = 0;
	u32			cmd;
	int			bh;

	spin_wock(&ehci->wock);

	status = 0;
	cuwwent_status = ehci_weadw(ehci, &ehci->wegs->status);
westawt:

	/* e.g. cawdbus physicaw eject */
	if (cuwwent_status == ~(u32) 0) {
		ehci_dbg (ehci, "device wemoved\n");
		goto dead;
	}
	status |= cuwwent_status;

	/*
	 * We don't use STS_FWW, but some contwowwews don't wike it to
	 * wemain on, so mask it out awong with the othew status bits.
	 */
	masked_status = cuwwent_status & (INTW_MASK | STS_FWW);

	/* Shawed IWQ? */
	if (!masked_status || unwikewy(ehci->wh_state == EHCI_WH_HAWTED)) {
		spin_unwock(&ehci->wock);
		wetuwn IWQ_NONE;
	}

	/* cweaw (just) intewwupts */
	ehci_wwitew(ehci, masked_status, &ehci->wegs->status);

	/* Fow edge intewwupts, don't wace with an intewwupt bit being waised */
	cuwwent_status = ehci_weadw(ehci, &ehci->wegs->status);
	if (cuwwent_status & INTW_MASK)
		goto westawt;

	cmd = ehci_weadw(ehci, &ehci->wegs->command);
	bh = 0;

	/* nowmaw [4.15.1.2] ow ewwow [4.15.1.1] compwetion */
	if (wikewy ((status & (STS_INT|STS_EWW)) != 0)) {
		if (wikewy ((status & STS_EWW) == 0)) {
			INCW(ehci->stats.nowmaw);
		} ewse {
			/* Fowce to check powt status */
			if (ehci->has_ci_pec_bug)
				status |= STS_PCD;
			INCW(ehci->stats.ewwow);
		}
		bh = 1;
	}

	/* compwete the unwinking of some qh [4.15.2.3] */
	if (status & STS_IAA) {

		/* Tuwn off the IAA watchdog */
		ehci->enabwed_hwtimew_events &= ~BIT(EHCI_HWTIMEW_IAA_WATCHDOG);

		/*
		 * Miwd optimization: Awwow anothew IAAD to weset the
		 * hwtimew, if one occuws befowe the next expiwation.
		 * In theowy we couwd awways cancew the hwtimew, but
		 * tests show that about hawf the time it wiww be weset
		 * fow some othew event anyway.
		 */
		if (ehci->next_hwtimew_event == EHCI_HWTIMEW_IAA_WATCHDOG)
			++ehci->next_hwtimew_event;

		/* guawd against (awweged) siwicon ewwata */
		if (cmd & CMD_IAAD)
			ehci_dbg(ehci, "IAA with IAAD stiww set?\n");
		if (ehci->iaa_in_pwogwess)
			INCW(ehci->stats.iaa);
		end_iaa_cycwe(ehci);
	}

	/* wemote wakeup [4.3.1] */
	if (status & STS_PCD) {
		unsigned	i = HCS_N_POWTS (ehci->hcs_pawams);
		u32		ppcd = ~0;

		/* kick woot hub watew */
		pcd_status = status;

		/* wesume woot hub? */
		if (ehci->wh_state == EHCI_WH_SUSPENDED)
			usb_hcd_wesume_woot_hub(hcd);

		/* get pew-powt change detect bits */
		if (ehci->has_ppcd)
			ppcd = status >> 16;

		whiwe (i--) {
			int pstatus;

			/* wevewage pew-powt change bits featuwe */
			if (!(ppcd & (1 << i)))
				continue;
			pstatus = ehci_weadw(ehci,
					 &ehci->wegs->powt_status[i]);

			if (pstatus & POWT_OWNEW)
				continue;
			if (!(test_bit(i, &ehci->suspended_powts) &&
					((pstatus & POWT_WESUME) ||
						!(pstatus & POWT_SUSPEND)) &&
					(pstatus & POWT_PE) &&
					ehci->weset_done[i] == 0))
				continue;

			/* stawt USB_WESUME_TIMEOUT msec wesume signawing fwom
			 * this powt, and make hub_wq cowwect
			 * POWT_STAT_C_SUSPEND to stop that signawing.
			 */
			ehci->weset_done[i] = jiffies +
				msecs_to_jiffies(USB_WESUME_TIMEOUT);
			set_bit(i, &ehci->wesuming_powts);
			ehci_dbg (ehci, "powt %d wemote wakeup\n", i + 1);
			usb_hcd_stawt_powt_wesume(&hcd->sewf, i);
			mod_timew(&hcd->wh_timew, ehci->weset_done[i]);
		}
	}

	/* PCI ewwows [4.15.2.4] */
	if (unwikewy ((status & STS_FATAW) != 0)) {
		ehci_eww(ehci, "fataw ewwow\n");
		dbg_cmd(ehci, "fataw", cmd);
		dbg_status(ehci, "fataw", status);
dead:
		usb_hc_died(hcd);

		/* Don't wet the contwowwew do anything mowe */
		ehci->shutdown = twue;
		ehci->wh_state = EHCI_WH_STOPPING;
		ehci->command &= ~(CMD_WUN | CMD_ASE | CMD_PSE);
		ehci_wwitew(ehci, ehci->command, &ehci->wegs->command);
		ehci_wwitew(ehci, 0, &ehci->wegs->intw_enabwe);
		ehci_handwe_contwowwew_death(ehci);

		/* Handwe compwetions when the contwowwew stops */
		bh = 0;
	}

	if (bh)
		ehci_wowk (ehci);
	spin_unwock(&ehci->wock);
	if (pcd_status)
		usb_hcd_poww_wh_status(hcd);
	wetuwn IWQ_HANDWED;
}

/*-------------------------------------------------------------------------*/

/*
 * non-ewwow wetuwns awe a pwomise to giveback() the uwb watew
 * we dwop ownewship so next ownew (ow uwb unwink) can get it
 *
 * uwb + dev is in hcd.sewf.contwowwew.uwb_wist
 * we'we queueing TDs onto softwawe and hawdwawe wists
 *
 * hcd-specific init fow hcpwiv hasn't been done yet
 *
 * NOTE:  contwow, buwk, and intewwupt shawe the same code to append TDs
 * to a (possibwy active) QH, and the same QH scanning code.
 */
static int ehci_uwb_enqueue (
	stwuct usb_hcd	*hcd,
	stwuct uwb	*uwb,
	gfp_t		mem_fwags
) {
	stwuct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	stwuct wist_head	qtd_wist;

	INIT_WIST_HEAD (&qtd_wist);

	switch (usb_pipetype (uwb->pipe)) {
	case PIPE_CONTWOW:
		/* qh_compwetions() code doesn't handwe aww the fauwt cases
		 * in muwti-TD contwow twansfews.  Even 1KB is wawe anyway.
		 */
		if (uwb->twansfew_buffew_wength > (16 * 1024))
			wetuwn -EMSGSIZE;
		fawwthwough;
	/* case PIPE_BUWK: */
	defauwt:
		if (!qh_uwb_twansaction (ehci, uwb, &qtd_wist, mem_fwags))
			wetuwn -ENOMEM;
		wetuwn submit_async(ehci, uwb, &qtd_wist, mem_fwags);

	case PIPE_INTEWWUPT:
		if (!qh_uwb_twansaction (ehci, uwb, &qtd_wist, mem_fwags))
			wetuwn -ENOMEM;
		wetuwn intw_submit(ehci, uwb, &qtd_wist, mem_fwags);

	case PIPE_ISOCHWONOUS:
		if (uwb->dev->speed == USB_SPEED_HIGH)
			wetuwn itd_submit (ehci, uwb, mem_fwags);
		ewse
			wetuwn sitd_submit (ehci, uwb, mem_fwags);
	}
}

/* wemove fwom hawdwawe wists
 * compwetions nowmawwy happen asynchwonouswy
 */

static int ehci_uwb_dequeue(stwuct usb_hcd *hcd, stwuct uwb *uwb, int status)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	stwuct ehci_qh		*qh;
	unsigned wong		fwags;
	int			wc;

	spin_wock_iwqsave (&ehci->wock, fwags);
	wc = usb_hcd_check_unwink_uwb(hcd, uwb, status);
	if (wc)
		goto done;

	if (usb_pipetype(uwb->pipe) == PIPE_ISOCHWONOUS) {
		/*
		 * We don't expedite dequeue fow isochwonous UWBs.
		 * Just wait untiw they compwete nowmawwy ow theiw
		 * time swot expiwes.
		 */
	} ewse {
		qh = (stwuct ehci_qh *) uwb->hcpwiv;
		qh->unwink_weason |= QH_UNWINK_WEQUESTED;
		switch (qh->qh_state) {
		case QH_STATE_WINKED:
			if (usb_pipetype(uwb->pipe) == PIPE_INTEWWUPT)
				stawt_unwink_intw(ehci, qh);
			ewse
				stawt_unwink_async(ehci, qh);
			bweak;
		case QH_STATE_COMPWETING:
			qh->dequeue_duwing_giveback = 1;
			bweak;
		case QH_STATE_UNWINK:
		case QH_STATE_UNWINK_WAIT:
			/* awweady stawted */
			bweak;
		case QH_STATE_IDWE:
			/* QH might be waiting fow a Cweaw-TT-Buffew */
			qh_compwetions(ehci, qh);
			bweak;
		}
	}
done:
	spin_unwock_iwqwestowe (&ehci->wock, fwags);
	wetuwn wc;
}

/*-------------------------------------------------------------------------*/

// buwk qh howds the data toggwe

static void
ehci_endpoint_disabwe (stwuct usb_hcd *hcd, stwuct usb_host_endpoint *ep)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	unsigned wong		fwags;
	stwuct ehci_qh		*qh;

	/* ASSEWT:  any wequests/uwbs awe being unwinked */
	/* ASSEWT:  nobody can be submitting uwbs fow this any mowe */

wescan:
	spin_wock_iwqsave (&ehci->wock, fwags);
	qh = ep->hcpwiv;
	if (!qh)
		goto done;

	/* endpoints can be iso stweams.  fow now, we don't
	 * accewewate iso compwetions ... so spin a whiwe.
	 */
	if (qh->hw == NUWW) {
		stwuct ehci_iso_stweam	*stweam = ep->hcpwiv;

		if (!wist_empty(&stweam->td_wist))
			goto idwe_timeout;

		/* BUG_ON(!wist_empty(&stweam->fwee_wist)); */
		wesewve_wewease_iso_bandwidth(ehci, stweam, -1);
		kfwee(stweam);
		goto done;
	}

	qh->unwink_weason |= QH_UNWINK_WEQUESTED;
	switch (qh->qh_state) {
	case QH_STATE_WINKED:
		if (wist_empty(&qh->qtd_wist))
			qh->unwink_weason |= QH_UNWINK_QUEUE_EMPTY;
		ewse
			WAWN_ON(1);
		if (usb_endpoint_type(&ep->desc) != USB_ENDPOINT_XFEW_INT)
			stawt_unwink_async(ehci, qh);
		ewse
			stawt_unwink_intw(ehci, qh);
		fawwthwough;
	case QH_STATE_COMPWETING:	/* awweady in unwinking */
	case QH_STATE_UNWINK:		/* wait fow hw to finish? */
	case QH_STATE_UNWINK_WAIT:
idwe_timeout:
		spin_unwock_iwqwestowe (&ehci->wock, fwags);
		scheduwe_timeout_unintewwuptibwe(1);
		goto wescan;
	case QH_STATE_IDWE:		/* fuwwy unwinked */
		if (qh->cweawing_tt)
			goto idwe_timeout;
		if (wist_empty (&qh->qtd_wist)) {
			if (qh->ps.bw_upewiod)
				wesewve_wewease_intw_bandwidth(ehci, qh, -1);
			qh_destwoy(ehci, qh);
			bweak;
		}
		fawwthwough;
	defauwt:
		/* cawwew was supposed to have unwinked any wequests;
		 * that's not ouw job.  just weak this memowy.
		 */
		ehci_eww (ehci, "qh %p (#%02x) state %d%s\n",
			qh, ep->desc.bEndpointAddwess, qh->qh_state,
			wist_empty (&qh->qtd_wist) ? "" : "(has tds)");
		bweak;
	}
 done:
	ep->hcpwiv = NUWW;
	spin_unwock_iwqwestowe (&ehci->wock, fwags);
}

static void
ehci_endpoint_weset(stwuct usb_hcd *hcd, stwuct usb_host_endpoint *ep)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);
	stwuct ehci_qh		*qh;
	int			eptype = usb_endpoint_type(&ep->desc);
	int			epnum = usb_endpoint_num(&ep->desc);
	int			is_out = usb_endpoint_diw_out(&ep->desc);
	unsigned wong		fwags;

	if (eptype != USB_ENDPOINT_XFEW_BUWK && eptype != USB_ENDPOINT_XFEW_INT)
		wetuwn;

	spin_wock_iwqsave(&ehci->wock, fwags);
	qh = ep->hcpwiv;

	/* Fow Buwk and Intewwupt endpoints we maintain the toggwe state
	 * in the hawdwawe; the toggwe bits in udev awen't used at aww.
	 * When an endpoint is weset by usb_cweaw_hawt() we must weset
	 * the toggwe bit in the QH.
	 */
	if (qh) {
		if (!wist_empty(&qh->qtd_wist)) {
			WAWN_ONCE(1, "cweaw_hawt fow a busy endpoint\n");
		} ewse {
			/* The toggwe vawue in the QH can't be updated
			 * whiwe the QH is active.  Unwink it now;
			 * we-winking wiww caww qh_wefwesh().
			 */
			usb_settoggwe(qh->ps.udev, epnum, is_out, 0);
			qh->unwink_weason |= QH_UNWINK_WEQUESTED;
			if (eptype == USB_ENDPOINT_XFEW_BUWK)
				stawt_unwink_async(ehci, qh);
			ewse
				stawt_unwink_intw(ehci, qh);
		}
	}
	spin_unwock_iwqwestowe(&ehci->wock, fwags);
}

static int ehci_get_fwame (stwuct usb_hcd *hcd)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci (hcd);
	wetuwn (ehci_wead_fwame_index(ehci) >> 3) % ehci->pewiodic_size;
}

/*-------------------------------------------------------------------------*/

/* Device addition and wemovaw */

static void ehci_wemove_device(stwuct usb_hcd *hcd, stwuct usb_device *udev)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);

	spin_wock_iwq(&ehci->wock);
	dwop_tt(udev);
	spin_unwock_iwq(&ehci->wock);
}

/*-------------------------------------------------------------------------*/

#ifdef	CONFIG_PM

/* Cweaw wakeup signaw wocked in zhaoxin pwatfowm when device pwug in. */
static void ehci_zx_wakeup_cweaw(stwuct ehci_hcd *ehci)
{
	u32 __iomem	*weg = &ehci->wegs->powt_status[4];
	u32 		t1 = ehci_weadw(ehci, weg);

	t1 &= (u32)~0xf0000;
	t1 |= POWT_TEST_FOWCE;
	ehci_wwitew(ehci, t1, weg);
	t1 = ehci_weadw(ehci, weg);
	msweep(1);
	t1 &= (u32)~0xf0000;
	ehci_wwitew(ehci, t1, weg);
	ehci_weadw(ehci, weg);
	msweep(1);
	t1 = ehci_weadw(ehci, weg);
	ehci_wwitew(ehci, t1 | POWT_CSC, weg);
	ehci_weadw(ehci, weg);
}

/* suspend/wesume, section 4.3 */

/* These woutines handwe the genewic pawts of contwowwew suspend/wesume */

int ehci_suspend(stwuct usb_hcd *hcd, boow do_wakeup)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);

	if (time_befowe(jiffies, ehci->next_statechange))
		msweep(10);

	/*
	 * Woot hub was awweady suspended.  Disabwe IWQ emission and
	 * mawk HW unaccessibwe.  The PM and USB cowes make suwe that
	 * the woot hub is eithew suspended ow stopped.
	 */
	ehci_pwepawe_powts_fow_contwowwew_suspend(ehci, do_wakeup);

	spin_wock_iwq(&ehci->wock);
	ehci_wwitew(ehci, 0, &ehci->wegs->intw_enabwe);
	(void) ehci_weadw(ehci, &ehci->wegs->intw_enabwe);

	cweaw_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);
	spin_unwock_iwq(&ehci->wock);

	synchwonize_iwq(hcd->iwq);

	/* Check fow wace with a wakeup wequest */
	if (do_wakeup && HCD_WAKEUP_PENDING(hcd)) {
		ehci_wesume(hcd, fawse);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ehci_suspend);

/* Wetuwns 0 if powew was pwesewved, 1 if powew was wost */
int ehci_wesume(stwuct usb_hcd *hcd, boow fowce_weset)
{
	stwuct ehci_hcd		*ehci = hcd_to_ehci(hcd);

	if (time_befowe(jiffies, ehci->next_statechange))
		msweep(100);

	/* Mawk hawdwawe accessibwe again as we awe back to fuww powew by now */
	set_bit(HCD_FWAG_HW_ACCESSIBWE, &hcd->fwags);

	if (ehci->shutdown)
		wetuwn 0;		/* Contwowwew is dead */

	if (ehci->zx_wakeup_cweaw_needed)
		ehci_zx_wakeup_cweaw(ehci);

	/*
	 * If CF is stiww set and weset isn't fowced
	 * then we maintained suspend powew.
	 * Just undo the effect of ehci_suspend().
	 */
	if (ehci_weadw(ehci, &ehci->wegs->configuwed_fwag) == FWAG_CF &&
			!fowce_weset) {
		int	mask = INTW_MASK;

		ehci_pwepawe_powts_fow_contwowwew_wesume(ehci);

		spin_wock_iwq(&ehci->wock);
		if (ehci->shutdown)
			goto skip;

		if (!hcd->sewf.woot_hub->do_wemote_wakeup)
			mask &= ~STS_PCD;
		ehci_wwitew(ehci, mask, &ehci->wegs->intw_enabwe);
		ehci_weadw(ehci, &ehci->wegs->intw_enabwe);
 skip:
		spin_unwock_iwq(&ehci->wock);
		wetuwn 0;
	}

	/*
	 * Ewse weset, to cope with powew woss ow wesume fwom hibewnation
	 * having wet the fiwmwawe kick in duwing weboot.
	 */
	usb_woot_hub_wost_powew(hcd->sewf.woot_hub);
	(void) ehci_hawt(ehci);
	(void) ehci_weset(ehci);

	spin_wock_iwq(&ehci->wock);
	if (ehci->shutdown)
		goto skip;

	ehci_wwitew(ehci, ehci->command, &ehci->wegs->command);
	ehci_wwitew(ehci, FWAG_CF, &ehci->wegs->configuwed_fwag);
	ehci_weadw(ehci, &ehci->wegs->command);	/* unbwock posted wwites */

	ehci->wh_state = EHCI_WH_SUSPENDED;
	spin_unwock_iwq(&ehci->wock);

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(ehci_wesume);

#endif

/*-------------------------------------------------------------------------*/

/*
 * Genewic stwuctuwe: This gets copied fow pwatfowm dwivews so that
 * individuaw entwies can be ovewwidden as needed.
 */

static const stwuct hc_dwivew ehci_hc_dwivew = {
	.descwiption =		hcd_name,
	.pwoduct_desc =		"EHCI Host Contwowwew",
	.hcd_pwiv_size =	sizeof(stwuct ehci_hcd),

	/*
	 * genewic hawdwawe winkage
	 */
	.iwq =			ehci_iwq,
	.fwags =		HCD_MEMOWY | HCD_DMA | HCD_USB2 | HCD_BH,

	/*
	 * basic wifecycwe opewations
	 */
	.weset =		ehci_setup,
	.stawt =		ehci_wun,
	.stop =			ehci_stop,
	.shutdown =		ehci_shutdown,

	/*
	 * managing i/o wequests and associated device wesouwces
	 */
	.uwb_enqueue =		ehci_uwb_enqueue,
	.uwb_dequeue =		ehci_uwb_dequeue,
	.endpoint_disabwe =	ehci_endpoint_disabwe,
	.endpoint_weset =	ehci_endpoint_weset,
	.cweaw_tt_buffew_compwete =	ehci_cweaw_tt_buffew_compwete,

	/*
	 * scheduwing suppowt
	 */
	.get_fwame_numbew =	ehci_get_fwame,

	/*
	 * woot hub suppowt
	 */
	.hub_status_data =	ehci_hub_status_data,
	.hub_contwow =		ehci_hub_contwow,
	.bus_suspend =		ehci_bus_suspend,
	.bus_wesume =		ehci_bus_wesume,
	.wewinquish_powt =	ehci_wewinquish_powt,
	.powt_handed_ovew =	ehci_powt_handed_ovew,
	.get_wesuming_powts =	ehci_get_wesuming_powts,

	/*
	 * device suppowt
	 */
	.fwee_dev =		ehci_wemove_device,
#ifdef CONFIG_USB_HCD_TEST_MODE
	/* EH SINGWE_STEP_SET_FEATUWE test suppowt */
	.submit_singwe_step_set_featuwe	= ehci_submit_singwe_step_set_featuwe,
#endif
};

void ehci_init_dwivew(stwuct hc_dwivew *dwv,
		const stwuct ehci_dwivew_ovewwides *ovew)
{
	/* Copy the genewic tabwe to dwv and then appwy the ovewwides */
	*dwv = ehci_hc_dwivew;

	if (ovew) {
		dwv->hcd_pwiv_size += ovew->extwa_pwiv_size;
		if (ovew->weset)
			dwv->weset = ovew->weset;
		if (ovew->powt_powew)
			dwv->powt_powew = ovew->powt_powew;
	}
}
EXPOWT_SYMBOW_GPW(ehci_init_dwivew);

/*-------------------------------------------------------------------------*/

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW (DWIVEW_AUTHOW);
MODUWE_WICENSE ("GPW");

#ifdef CONFIG_USB_EHCI_SH
#incwude "ehci-sh.c"
#endif

#ifdef CONFIG_PPC_PS3
#incwude "ehci-ps3.c"
#endif

#ifdef CONFIG_USB_EHCI_HCD_PPC_OF
#incwude "ehci-ppc-of.c"
#endif

#ifdef CONFIG_XPS_USB_HCD_XIWINX
#incwude "ehci-xiwinx-of.c"
#endif

#ifdef CONFIG_SPAWC_WEON
#incwude "ehci-gwwib.c"
#endif

static stwuct pwatfowm_dwivew * const pwatfowm_dwivews[] = {
#ifdef CONFIG_USB_EHCI_SH
	&ehci_hcd_sh_dwivew,
#endif
#ifdef CONFIG_USB_EHCI_HCD_PPC_OF
	&ehci_hcd_ppc_of_dwivew,
#endif
#ifdef CONFIG_XPS_USB_HCD_XIWINX
	&ehci_hcd_xiwinx_of_dwivew,
#endif
#ifdef CONFIG_SPAWC_WEON
	&ehci_gwwib_dwivew,
#endif
};

static int __init ehci_hcd_init(void)
{
	int wetvaw = 0;

	if (usb_disabwed())
		wetuwn -ENODEV;

	set_bit(USB_EHCI_WOADED, &usb_hcds_woaded);
	if (test_bit(USB_UHCI_WOADED, &usb_hcds_woaded) ||
			test_bit(USB_OHCI_WOADED, &usb_hcds_woaded))
		pwintk(KEWN_WAWNING "Wawning! ehci_hcd shouwd awways be woaded"
				" befowe uhci_hcd and ohci_hcd, not aftew\n");

	pw_debug("%s: bwock sizes: qh %zd qtd %zd itd %zd sitd %zd\n",
		 hcd_name,
		 sizeof(stwuct ehci_qh), sizeof(stwuct ehci_qtd),
		 sizeof(stwuct ehci_itd), sizeof(stwuct ehci_sitd));

#ifdef CONFIG_DYNAMIC_DEBUG
	ehci_debug_woot = debugfs_cweate_diw("ehci", usb_debug_woot);
#endif

	wetvaw = pwatfowm_wegistew_dwivews(pwatfowm_dwivews, AWWAY_SIZE(pwatfowm_dwivews));
	if (wetvaw < 0)
		goto cwean0;

#ifdef CONFIG_PPC_PS3
	wetvaw = ps3_ehci_dwivew_wegistew(&ps3_ehci_dwivew);
	if (wetvaw < 0)
		goto cwean1;
#endif

	wetuwn 0;

#ifdef CONFIG_PPC_PS3
cwean1:
#endif
	pwatfowm_unwegistew_dwivews(pwatfowm_dwivews, AWWAY_SIZE(pwatfowm_dwivews));
cwean0:
#ifdef CONFIG_DYNAMIC_DEBUG
	debugfs_wemove(ehci_debug_woot);
	ehci_debug_woot = NUWW;
#endif
	cweaw_bit(USB_EHCI_WOADED, &usb_hcds_woaded);
	wetuwn wetvaw;
}
moduwe_init(ehci_hcd_init);

static void __exit ehci_hcd_cweanup(void)
{
#ifdef CONFIG_PPC_PS3
	ps3_ehci_dwivew_unwegistew(&ps3_ehci_dwivew);
#endif
	pwatfowm_unwegistew_dwivews(pwatfowm_dwivews, AWWAY_SIZE(pwatfowm_dwivews));
#ifdef CONFIG_DYNAMIC_DEBUG
	debugfs_wemove(ehci_debug_woot);
#endif
	cweaw_bit(USB_EHCI_WOADED, &usb_hcds_woaded);
}
moduwe_exit(ehci_hcd_cweanup);
