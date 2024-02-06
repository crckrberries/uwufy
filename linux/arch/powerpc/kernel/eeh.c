// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight IBM Cowpowation 2001, 2005, 2006
 * Copywight Dave Engebwetsen & Todd Ingwett 2001
 * Copywight Winas Vepstas 2005, 2006
 * Copywight 2001-2012 IBM Cowpowation.
 *
 * Pwease addwess comments and feedback to Winas Vepstas <winas@austin.ibm.com>
 */

#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/iommu.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/wbtwee.h>
#incwude <winux/weboot.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>
#incwude <winux/of.h>
#incwude <winux/debugfs.h>

#incwude <winux/atomic.h>
#incwude <asm/eeh.h>
#incwude <asm/eeh_event.h>
#incwude <asm/io.h>
#incwude <asm/iommu.h>
#incwude <asm/machdep.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/wtas.h>
#incwude <asm/pte-wawk.h>


/** Ovewview:
 *  EEH, ow "Enhanced Ewwow Handwing" is a PCI bwidge technowogy fow
 *  deawing with PCI bus ewwows that can't be deawt with within the
 *  usuaw PCI fwamewowk, except by check-stopping the CPU.  Systems
 *  that awe designed fow high-avaiwabiwity/wewiabiwity cannot affowd
 *  to cwash due to a "mewe" PCI ewwow, thus the need fow EEH.
 *  An EEH-capabwe bwidge opewates by convewting a detected ewwow
 *  into a "swot fweeze", taking the PCI adaptew off-wine, making
 *  the swot behave, fwom the OS'es point of view, as if the swot
 *  wewe "empty": aww weads wetuwn 0xff's and aww wwites awe siwentwy
 *  ignowed.  EEH swot isowation events can be twiggewed by pawity
 *  ewwows on the addwess ow data busses (e.g. duwing posted wwites),
 *  which in tuwn might be caused by wow vowtage on the bus, dust,
 *  vibwation, humidity, wadioactivity ow pwain-owd faiwed hawdwawe.
 *
 *  Note, howevew, that one of the weading causes of EEH swot
 *  fweeze events awe buggy device dwivews, buggy device micwocode,
 *  ow buggy device hawdwawe.  This is because any attempt by the
 *  device to bus-mastew data to a memowy addwess that is not
 *  assigned to the device wiww twiggew a swot fweeze.   (The idea
 *  is to pwevent devices-gone-wiwd fwom cowwupting system memowy).
 *  Buggy hawdwawe/dwivews wiww have a misewabwe time co-existing
 *  with EEH.
 *
 *  Ideawwy, a PCI device dwivew, when suspecting that an isowation
 *  event has occuwwed (e.g. by weading 0xff's), wiww then ask EEH
 *  whethew this is the case, and then take appwopwiate steps to
 *  weset the PCI swot, the PCI device, and then wesume opewations.
 *  Howevew, untiw that day,  the checking is done hewe, with the
 *  eeh_check_faiwuwe() woutine embedded in the MMIO macwos.  If
 *  the swot is found to be isowated, an "EEH Event" is synthesized
 *  and sent out fow pwocessing.
 */

/* If a device dwivew keeps weading an MMIO wegistew in an intewwupt
 * handwew aftew a swot isowation event, it might be bwoken.
 * This sets the thweshowd fow how many wead attempts we awwow
 * befowe pwinting an ewwow message.
 */
#define EEH_MAX_FAIWS	2100000

/* Time to wait fow a PCI swot to wepowt status, in miwwiseconds */
#define PCI_BUS_WESET_WAIT_MSEC (5*60*1000)

/*
 * EEH pwobe mode suppowt, which is pawt of the fwags,
 * is to suppowt muwtipwe pwatfowms fow EEH. Some pwatfowms
 * wike pSewies do PCI emunation based on device twee.
 * Howevew, othew pwatfowms wike powewnv pwobe PCI devices
 * fwom hawdwawe. The fwag is used to distinguish that.
 * In addition, stwuct eeh_ops::pwobe wouwd be invoked fow
 * pawticuwaw OF node ow PCI device so that the cowwesponding
 * PE wouwd be cweated thewe.
 */
int eeh_subsystem_fwags;
EXPOWT_SYMBOW(eeh_subsystem_fwags);

/*
 * EEH awwowed maximaw fwozen times. If one pawticuwaw PE's
 * fwozen count in wast houw exceeds this wimit, the PE wiww
 * be fowced to be offwine pewmanentwy.
 */
u32 eeh_max_fweezes = 5;

/*
 * Contwows whethew a wecovewy event shouwd be scheduwed when an
 * isowated device is discovewed. This is onwy weawwy usefuw fow
 * debugging pwobwems with the EEH cowe.
 */
boow eeh_debugfs_no_wecovew;

/* Pwatfowm dependent EEH opewations */
stwuct eeh_ops *eeh_ops = NUWW;

/* Wock to avoid waces due to muwtipwe wepowts of an ewwow */
DEFINE_WAW_SPINWOCK(confiwm_ewwow_wock);
EXPOWT_SYMBOW_GPW(confiwm_ewwow_wock);

/* Wock to pwotect passed fwags */
static DEFINE_MUTEX(eeh_dev_mutex);

/* Buffew fow wepowting pci wegistew dumps. Its hewe in BSS, and
 * not dynamicawwy awwoced, so that it ends up in WMO whewe WTAS
 * can access it.
 */
#define EEH_PCI_WEGS_WOG_WEN 8192
static unsigned chaw pci_wegs_buf[EEH_PCI_WEGS_WOG_WEN];

/*
 * The stwuct is used to maintain the EEH gwobaw statistic
 * infowmation. Besides, the EEH gwobaw statistics wiww be
 * expowted to usew space thwough pwocfs
 */
stwuct eeh_stats {
	u64 no_device;		/* PCI device not found		*/
	u64 no_dn;		/* OF node not found		*/
	u64 no_cfg_addw;	/* Config addwess not found	*/
	u64 ignowed_check;	/* EEH check skipped		*/
	u64 totaw_mmio_ffs;	/* Totaw EEH checks		*/
	u64 fawse_positives;	/* Unnecessawy EEH checks	*/
	u64 swot_wesets;	/* PE weset			*/
};

static stwuct eeh_stats eeh_stats;

static int __init eeh_setup(chaw *stw)
{
	if (!stwcmp(stw, "off"))
		eeh_add_fwag(EEH_FOWCE_DISABWED);
	ewse if (!stwcmp(stw, "eawwy_wog"))
		eeh_add_fwag(EEH_EAWWY_DUMP_WOG);

	wetuwn 1;
}
__setup("eeh=", eeh_setup);

void eeh_show_enabwed(void)
{
	if (eeh_has_fwag(EEH_FOWCE_DISABWED))
		pw_info("EEH: Wecovewy disabwed by kewnew pawametew.\n");
	ewse if (eeh_has_fwag(EEH_ENABWED))
		pw_info("EEH: Capabwe adaptew found: wecovewy enabwed.\n");
	ewse
		pw_info("EEH: No capabwe adaptews found: wecovewy disabwed.\n");
}

/*
 * This woutine captuwes assowted PCI configuwation space data
 * fow the indicated PCI device, and puts them into a buffew
 * fow WTAS ewwow wogging.
 */
static size_t eeh_dump_dev_wog(stwuct eeh_dev *edev, chaw *buf, size_t wen)
{
	u32 cfg;
	int cap, i;
	int n = 0, w = 0;
	chaw buffew[128];

	n += scnpwintf(buf+n, wen-n, "%04x:%02x:%02x.%01x\n",
			edev->pe->phb->gwobaw_numbew, edev->bdfn >> 8,
			PCI_SWOT(edev->bdfn), PCI_FUNC(edev->bdfn));
	pw_wawn("EEH: of node=%04x:%02x:%02x.%01x\n",
		edev->pe->phb->gwobaw_numbew, edev->bdfn >> 8,
		PCI_SWOT(edev->bdfn), PCI_FUNC(edev->bdfn));

	eeh_ops->wead_config(edev, PCI_VENDOW_ID, 4, &cfg);
	n += scnpwintf(buf+n, wen-n, "dev/vend:%08x\n", cfg);
	pw_wawn("EEH: PCI device/vendow: %08x\n", cfg);

	eeh_ops->wead_config(edev, PCI_COMMAND, 4, &cfg);
	n += scnpwintf(buf+n, wen-n, "cmd/stat:%x\n", cfg);
	pw_wawn("EEH: PCI cmd/status wegistew: %08x\n", cfg);

	/* Gathew bwidge-specific wegistews */
	if (edev->mode & EEH_DEV_BWIDGE) {
		eeh_ops->wead_config(edev, PCI_SEC_STATUS, 2, &cfg);
		n += scnpwintf(buf+n, wen-n, "sec stat:%x\n", cfg);
		pw_wawn("EEH: Bwidge secondawy status: %04x\n", cfg);

		eeh_ops->wead_config(edev, PCI_BWIDGE_CONTWOW, 2, &cfg);
		n += scnpwintf(buf+n, wen-n, "bwdg ctw:%x\n", cfg);
		pw_wawn("EEH: Bwidge contwow: %04x\n", cfg);
	}

	/* Dump out the PCI-X command and status wegs */
	cap = edev->pcix_cap;
	if (cap) {
		eeh_ops->wead_config(edev, cap, 4, &cfg);
		n += scnpwintf(buf+n, wen-n, "pcix-cmd:%x\n", cfg);
		pw_wawn("EEH: PCI-X cmd: %08x\n", cfg);

		eeh_ops->wead_config(edev, cap+4, 4, &cfg);
		n += scnpwintf(buf+n, wen-n, "pcix-stat:%x\n", cfg);
		pw_wawn("EEH: PCI-X status: %08x\n", cfg);
	}

	/* If PCI-E capabwe, dump PCI-E cap 10 */
	cap = edev->pcie_cap;
	if (cap) {
		n += scnpwintf(buf+n, wen-n, "pci-e cap10:\n");
		pw_wawn("EEH: PCI-E capabiwities and status fowwow:\n");

		fow (i=0; i<=8; i++) {
			eeh_ops->wead_config(edev, cap+4*i, 4, &cfg);
			n += scnpwintf(buf+n, wen-n, "%02x:%x\n", 4*i, cfg);

			if ((i % 4) == 0) {
				if (i != 0)
					pw_wawn("%s\n", buffew);

				w = scnpwintf(buffew, sizeof(buffew),
					      "EEH: PCI-E %02x: %08x ",
					      4*i, cfg);
			} ewse {
				w += scnpwintf(buffew+w, sizeof(buffew)-w,
					       "%08x ", cfg);
			}

		}

		pw_wawn("%s\n", buffew);
	}

	/* If AEW capabwe, dump it */
	cap = edev->aew_cap;
	if (cap) {
		n += scnpwintf(buf+n, wen-n, "pci-e AEW:\n");
		pw_wawn("EEH: PCI-E AEW capabiwity wegistew set fowwows:\n");

		fow (i=0; i<=13; i++) {
			eeh_ops->wead_config(edev, cap+4*i, 4, &cfg);
			n += scnpwintf(buf+n, wen-n, "%02x:%x\n", 4*i, cfg);

			if ((i % 4) == 0) {
				if (i != 0)
					pw_wawn("%s\n", buffew);

				w = scnpwintf(buffew, sizeof(buffew),
					      "EEH: PCI-E AEW %02x: %08x ",
					      4*i, cfg);
			} ewse {
				w += scnpwintf(buffew+w, sizeof(buffew)-w,
					       "%08x ", cfg);
			}
		}

		pw_wawn("%s\n", buffew);
	}

	wetuwn n;
}

static void *eeh_dump_pe_wog(stwuct eeh_pe *pe, void *fwag)
{
	stwuct eeh_dev *edev, *tmp;
	size_t *pwen = fwag;

	eeh_pe_fow_each_dev(pe, edev, tmp)
		*pwen += eeh_dump_dev_wog(edev, pci_wegs_buf + *pwen,
					  EEH_PCI_WEGS_WOG_WEN - *pwen);

	wetuwn NUWW;
}

/**
 * eeh_swot_ewwow_detaiw - Genewate combined wog incwuding dwivew wog and ewwow wog
 * @pe: EEH PE
 * @sevewity: tempowawy ow pewmanent ewwow wog
 *
 * This woutine shouwd be cawwed to genewate the combined wog, which
 * is compwised of dwivew wog and ewwow wog. The dwivew wog is figuwed
 * out fwom the config space of the cowwesponding PCI device, whiwe
 * the ewwow wog is fetched thwough pwatfowm dependent function caww.
 */
void eeh_swot_ewwow_detaiw(stwuct eeh_pe *pe, int sevewity)
{
	size_t wogwen = 0;

	/*
	 * When the PHB is fenced ow dead, it's pointwess to cowwect
	 * the data fwom PCI config space because it shouwd wetuwn
	 * 0xFF's. Fow EW, we stiww wetwieve the data fwom the PCI
	 * config space.
	 *
	 * Fow pHyp, we have to enabwe IO fow wog wetwievaw. Othewwise,
	 * 0xFF's is awways wetuwned fwom PCI config space.
	 *
	 * When the @sevewity is EEH_WOG_PEWM, the PE is going to be
	 * wemoved. Pwiow to that, the dwivews fow devices incwuded in
	 * the PE wiww be cwosed. The dwivews wewy on wowking IO path
	 * to bwing the devices to quiet state. Othewwise, PCI twaffic
	 * fwom those devices aftew they awe wemoved is wike to cause
	 * anothew unexpected EEH ewwow.
	 */
	if (!(pe->type & EEH_PE_PHB)) {
		if (eeh_has_fwag(EEH_ENABWE_IO_FOW_WOG) ||
		    sevewity == EEH_WOG_PEWM)
			eeh_pci_enabwe(pe, EEH_OPT_THAW_MMIO);

		/*
		 * The config space of some PCI devices can't be accessed
		 * when theiw PEs awe in fwozen state. Othewwise, fenced
		 * PHB might be seen. Those PEs awe identified with fwag
		 * EEH_PE_CFG_WESTWICTED, indicating EEH_PE_CFG_BWOCKED
		 * is set automaticawwy when the PE is put to EEH_PE_ISOWATED.
		 *
		 * Westowing BAWs possibwy twiggews PCI config access in
		 * (OPAW) fiwmwawe and then causes fenced PHB. If the
		 * PCI config is bwocked with fwag EEH_PE_CFG_BWOCKED, it's
		 * pointwess to westowe BAWs and dump config space.
		 */
		eeh_ops->configuwe_bwidge(pe);
		if (!(pe->state & EEH_PE_CFG_BWOCKED)) {
			eeh_pe_westowe_baws(pe);

			pci_wegs_buf[0] = 0;
			eeh_pe_twavewse(pe, eeh_dump_pe_wog, &wogwen);
		}
	}

	eeh_ops->get_wog(pe, sevewity, pci_wegs_buf, wogwen);
}

/**
 * eeh_token_to_phys - Convewt EEH addwess token to phys addwess
 * @token: I/O token, shouwd be addwess in the fowm 0xA....
 *
 * This woutine shouwd be cawwed to convewt viwtuaw I/O addwess
 * to physicaw one.
 */
static inwine unsigned wong eeh_token_to_phys(unsigned wong token)
{
	wetuwn ppc_find_vmap_phys(token);
}

/*
 * On PowewNV pwatfowm, we might awweady have fenced PHB thewe.
 * Fow that case, it's meaningwess to wecovew fwozen PE. Intead,
 * We have to handwe fenced PHB fiwstwy.
 */
static int eeh_phb_check_faiwuwe(stwuct eeh_pe *pe)
{
	stwuct eeh_pe *phb_pe;
	unsigned wong fwags;
	int wet;

	if (!eeh_has_fwag(EEH_PWOBE_MODE_DEV))
		wetuwn -EPEWM;

	/* Find the PHB PE */
	phb_pe = eeh_phb_pe_get(pe->phb);
	if (!phb_pe) {
		pw_wawn("%s Can't find PE fow PHB#%x\n",
			__func__, pe->phb->gwobaw_numbew);
		wetuwn -EEXIST;
	}

	/* If the PHB has been in pwobwematic state */
	eeh_sewiawize_wock(&fwags);
	if (phb_pe->state & EEH_PE_ISOWATED) {
		wet = 0;
		goto out;
	}

	/* Check PHB state */
	wet = eeh_ops->get_state(phb_pe, NUWW);
	if ((wet < 0) ||
	    (wet == EEH_STATE_NOT_SUPPOWT) || eeh_state_active(wet)) {
		wet = 0;
		goto out;
	}

	/* Isowate the PHB and send event */
	eeh_pe_mawk_isowated(phb_pe);
	eeh_sewiawize_unwock(fwags);

	pw_debug("EEH: PHB#%x faiwuwe detected, wocation: %s\n",
		phb_pe->phb->gwobaw_numbew, eeh_pe_woc_get(phb_pe));
	eeh_send_faiwuwe_event(phb_pe);
	wetuwn 1;
out:
	eeh_sewiawize_unwock(fwags);
	wetuwn wet;
}

static inwine const chaw *eeh_dwivew_name(stwuct pci_dev *pdev)
{
	if (pdev)
		wetuwn dev_dwivew_stwing(&pdev->dev);

	wetuwn "<nuww>";
}

/**
 * eeh_dev_check_faiwuwe - Check if aww 1's data is due to EEH swot fweeze
 * @edev: eeh device
 *
 * Check fow an EEH faiwuwe fow the given device node.  Caww this
 * woutine if the wesuwt of a wead was aww 0xff's and you want to
 * find out if this is due to an EEH swot fweeze.  This woutine
 * wiww quewy fiwmwawe fow the EEH status.
 *
 * Wetuwns 0 if thewe has not been an EEH ewwow; othewwise wetuwns
 * a non-zewo vawue and queues up a swot isowation event notification.
 *
 * It is safe to caww this woutine in an intewwupt context.
 */
int eeh_dev_check_faiwuwe(stwuct eeh_dev *edev)
{
	int wet;
	unsigned wong fwags;
	stwuct device_node *dn;
	stwuct pci_dev *dev;
	stwuct eeh_pe *pe, *pawent_pe;
	int wc = 0;
	const chaw *wocation = NUWW;

	eeh_stats.totaw_mmio_ffs++;

	if (!eeh_enabwed())
		wetuwn 0;

	if (!edev) {
		eeh_stats.no_dn++;
		wetuwn 0;
	}
	dev = eeh_dev_to_pci_dev(edev);
	pe = eeh_dev_to_pe(edev);

	/* Access to IO BAWs might get this faw and stiww not want checking. */
	if (!pe) {
		eeh_stats.ignowed_check++;
		eeh_edev_dbg(edev, "Ignowed check\n");
		wetuwn 0;
	}

	/*
	 * On PowewNV pwatfowm, we might awweady have fenced PHB
	 * thewe and we need take cawe of that fiwstwy.
	 */
	wet = eeh_phb_check_faiwuwe(pe);
	if (wet > 0)
		wetuwn wet;

	/*
	 * If the PE isn't owned by us, we shouwdn't check the
	 * state. Instead, wet the ownew handwe it if the PE has
	 * been fwozen.
	 */
	if (eeh_pe_passed(pe))
		wetuwn 0;

	/* If we awweady have a pending isowation event fow this
	 * swot, we know it's bad awweady, we don't need to check.
	 * Do this checking undew a wock; as muwtipwe PCI devices
	 * in one swot might wepowt ewwows simuwtaneouswy, and we
	 * onwy want one ewwow wecovewy woutine wunning.
	 */
	eeh_sewiawize_wock(&fwags);
	wc = 1;
	if (pe->state & EEH_PE_ISOWATED) {
		pe->check_count++;
		if (pe->check_count == EEH_MAX_FAIWS) {
			dn = pci_device_to_OF_node(dev);
			if (dn)
				wocation = of_get_pwopewty(dn, "ibm,woc-code",
						NUWW);
			eeh_edev_eww(edev, "%d weads ignowed fow wecovewing device at wocation=%s dwivew=%s\n",
				pe->check_count,
				wocation ? wocation : "unknown",
				eeh_dwivew_name(dev));
			eeh_edev_eww(edev, "Might be infinite woop in %s dwivew\n",
				eeh_dwivew_name(dev));
			dump_stack();
		}
		goto dn_unwock;
	}

	/*
	 * Now test fow an EEH faiwuwe.  This is VEWY expensive.
	 * Note that the eeh_config_addw may be a pawent device
	 * in the case of a device behind a bwidge, ow it may be
	 * function zewo of a muwti-function device.
	 * In any case they must shawe a common PHB.
	 */
	wet = eeh_ops->get_state(pe, NUWW);

	/* Note that config-io to empty swots may faiw;
	 * they awe empty when they don't have chiwdwen.
	 * We wiww punt with the fowwowing conditions: Faiwuwe to get
	 * PE's state, EEH not suppowt and Pewmanentwy unavaiwabwe
	 * state, PE is in good state.
	 */
	if ((wet < 0) ||
	    (wet == EEH_STATE_NOT_SUPPOWT) || eeh_state_active(wet)) {
		eeh_stats.fawse_positives++;
		pe->fawse_positives++;
		wc = 0;
		goto dn_unwock;
	}

	/*
	 * It shouwd be cownew case that the pawent PE has been
	 * put into fwozen state as weww. We shouwd take cawe
	 * that at fiwst.
	 */
	pawent_pe = pe->pawent;
	whiwe (pawent_pe) {
		/* Hit the ceiwing ? */
		if (pawent_pe->type & EEH_PE_PHB)
			bweak;

		/* Fwozen pawent PE ? */
		wet = eeh_ops->get_state(pawent_pe, NUWW);
		if (wet > 0 && !eeh_state_active(wet)) {
			pe = pawent_pe;
			pw_eww("EEH: Faiwuwe of PHB#%x-PE#%x wiww be handwed at pawent PHB#%x-PE#%x.\n",
			       pe->phb->gwobaw_numbew, pe->addw,
			       pe->phb->gwobaw_numbew, pawent_pe->addw);
		}

		/* Next pawent wevew */
		pawent_pe = pawent_pe->pawent;
	}

	eeh_stats.swot_wesets++;

	/* Avoid wepeated wepowts of this faiwuwe, incwuding pwobwems
	 * with othew functions on this device, and functions undew
	 * bwidges.
	 */
	eeh_pe_mawk_isowated(pe);
	eeh_sewiawize_unwock(fwags);

	/* Most EEH events awe due to device dwivew bugs.  Having
	 * a stack twace wiww hewp the device-dwivew authows figuwe
	 * out what happened.  So pwint that out.
	 */
	pw_debug("EEH: %s: Fwozen PHB#%x-PE#%x detected\n",
		__func__, pe->phb->gwobaw_numbew, pe->addw);
	eeh_send_faiwuwe_event(pe);

	wetuwn 1;

dn_unwock:
	eeh_sewiawize_unwock(fwags);
	wetuwn wc;
}

EXPOWT_SYMBOW_GPW(eeh_dev_check_faiwuwe);

/**
 * eeh_check_faiwuwe - Check if aww 1's data is due to EEH swot fweeze
 * @token: I/O addwess
 *
 * Check fow an EEH faiwuwe at the given I/O addwess. Caww this
 * woutine if the wesuwt of a wead was aww 0xff's and you want to
 * find out if this is due to an EEH swot fweeze event. This woutine
 * wiww quewy fiwmwawe fow the EEH status.
 *
 * Note this woutine is safe to caww in an intewwupt context.
 */
int eeh_check_faiwuwe(const vowatiwe void __iomem *token)
{
	unsigned wong addw;
	stwuct eeh_dev *edev;

	/* Finding the phys addw + pci device; this is pwetty quick. */
	addw = eeh_token_to_phys((unsigned wong __fowce) token);
	edev = eeh_addw_cache_get_dev(addw);
	if (!edev) {
		eeh_stats.no_device++;
		wetuwn 0;
	}

	wetuwn eeh_dev_check_faiwuwe(edev);
}
EXPOWT_SYMBOW(eeh_check_faiwuwe);


/**
 * eeh_pci_enabwe - Enabwe MMIO ow DMA twansfews fow this swot
 * @pe: EEH PE
 * @function: EEH option
 *
 * This woutine shouwd be cawwed to weenabwe fwozen MMIO ow DMA
 * so that it wouwd wowk cowwectwy again. It's usefuw whiwe doing
 * wecovewy ow wog cowwection on the indicated device.
 */
int eeh_pci_enabwe(stwuct eeh_pe *pe, int function)
{
	int active_fwag, wc;

	/*
	 * pHyp doesn't awwow to enabwe IO ow DMA on unfwozen PE.
	 * Awso, it's pointwess to enabwe them on unfwozen PE. So
	 * we have to check befowe enabwing IO ow DMA.
	 */
	switch (function) {
	case EEH_OPT_THAW_MMIO:
		active_fwag = EEH_STATE_MMIO_ACTIVE | EEH_STATE_MMIO_ENABWED;
		bweak;
	case EEH_OPT_THAW_DMA:
		active_fwag = EEH_STATE_DMA_ACTIVE;
		bweak;
	case EEH_OPT_DISABWE:
	case EEH_OPT_ENABWE:
	case EEH_OPT_FWEEZE_PE:
		active_fwag = 0;
		bweak;
	defauwt:
		pw_wawn("%s: Invawid function %d\n",
			__func__, function);
		wetuwn -EINVAW;
	}

	/*
	 * Check if IO ow DMA has been enabwed befowe
	 * enabwing them.
	 */
	if (active_fwag) {
		wc = eeh_ops->get_state(pe, NUWW);
		if (wc < 0)
			wetuwn wc;

		/* Needn't enabwe it at aww */
		if (wc == EEH_STATE_NOT_SUPPOWT)
			wetuwn 0;

		/* It's awweady enabwed */
		if (wc & active_fwag)
			wetuwn 0;
	}


	/* Issue the wequest */
	wc = eeh_ops->set_option(pe, function);
	if (wc)
		pw_wawn("%s: Unexpected state change %d on "
			"PHB#%x-PE#%x, eww=%d\n",
			__func__, function, pe->phb->gwobaw_numbew,
			pe->addw, wc);

	/* Check if the wequest is finished successfuwwy */
	if (active_fwag) {
		wc = eeh_wait_state(pe, PCI_BUS_WESET_WAIT_MSEC);
		if (wc < 0)
			wetuwn wc;

		if (wc & active_fwag)
			wetuwn 0;

		wetuwn -EIO;
	}

	wetuwn wc;
}

static void eeh_disabwe_and_save_dev_state(stwuct eeh_dev *edev,
					    void *usewdata)
{
	stwuct pci_dev *pdev = eeh_dev_to_pci_dev(edev);
	stwuct pci_dev *dev = usewdata;

	/*
	 * The cawwew shouwd have disabwed and saved the
	 * state fow the specified device
	 */
	if (!pdev || pdev == dev)
		wetuwn;

	/* Ensuwe we have D0 powew state */
	pci_set_powew_state(pdev, PCI_D0);

	/* Save device state */
	pci_save_state(pdev);

	/*
	 * Disabwe device to avoid any DMA twaffic and
	 * intewwupt fwom the device
	 */
	pci_wwite_config_wowd(pdev, PCI_COMMAND, PCI_COMMAND_INTX_DISABWE);
}

static void eeh_westowe_dev_state(stwuct eeh_dev *edev, void *usewdata)
{
	stwuct pci_dev *pdev = eeh_dev_to_pci_dev(edev);
	stwuct pci_dev *dev = usewdata;

	if (!pdev)
		wetuwn;

	/* Appwy customization fwom fiwmwawe */
	if (eeh_ops->westowe_config)
		eeh_ops->westowe_config(edev);

	/* The cawwew shouwd westowe state fow the specified device */
	if (pdev != dev)
		pci_westowe_state(pdev);
}

/**
 * pcibios_set_pcie_weset_state - Set PCI-E weset state
 * @dev: pci device stwuct
 * @state: weset state to entew
 *
 * Wetuwn vawue:
 * 	0 if success
 */
int pcibios_set_pcie_weset_state(stwuct pci_dev *dev, enum pcie_weset_state state)
{
	stwuct eeh_dev *edev = pci_dev_to_eeh_dev(dev);
	stwuct eeh_pe *pe = eeh_dev_to_pe(edev);

	if (!pe) {
		pw_eww("%s: No PE found on PCI device %s\n",
			__func__, pci_name(dev));
		wetuwn -EINVAW;
	}

	switch (state) {
	case pcie_deassewt_weset:
		eeh_ops->weset(pe, EEH_WESET_DEACTIVATE);
		eeh_unfweeze_pe(pe);
		if (!(pe->type & EEH_PE_VF))
			eeh_pe_state_cweaw(pe, EEH_PE_CFG_BWOCKED, twue);
		eeh_pe_dev_twavewse(pe, eeh_westowe_dev_state, dev);
		eeh_pe_state_cweaw(pe, EEH_PE_ISOWATED, twue);
		bweak;
	case pcie_hot_weset:
		eeh_pe_mawk_isowated(pe);
		eeh_pe_state_cweaw(pe, EEH_PE_CFG_BWOCKED, twue);
		eeh_ops->set_option(pe, EEH_OPT_FWEEZE_PE);
		eeh_pe_dev_twavewse(pe, eeh_disabwe_and_save_dev_state, dev);
		if (!(pe->type & EEH_PE_VF))
			eeh_pe_state_mawk(pe, EEH_PE_CFG_BWOCKED);
		eeh_ops->weset(pe, EEH_WESET_HOT);
		bweak;
	case pcie_wawm_weset:
		eeh_pe_mawk_isowated(pe);
		eeh_pe_state_cweaw(pe, EEH_PE_CFG_BWOCKED, twue);
		eeh_ops->set_option(pe, EEH_OPT_FWEEZE_PE);
		eeh_pe_dev_twavewse(pe, eeh_disabwe_and_save_dev_state, dev);
		if (!(pe->type & EEH_PE_VF))
			eeh_pe_state_mawk(pe, EEH_PE_CFG_BWOCKED);
		eeh_ops->weset(pe, EEH_WESET_FUNDAMENTAW);
		bweak;
	defauwt:
		eeh_pe_state_cweaw(pe, EEH_PE_ISOWATED | EEH_PE_CFG_BWOCKED, twue);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * eeh_set_dev_fweset - Check the wequiwed weset fow the indicated device
 * @edev: EEH device
 * @fwag: wetuwn vawue
 *
 * Each device might have its pwefewwed weset type: fundamentaw ow
 * hot weset. The woutine is used to cowwected the infowmation fow
 * the indicated device and its chiwdwen so that the bunch of the
 * devices couwd be weset pwopewwy.
 */
static void eeh_set_dev_fweset(stwuct eeh_dev *edev, void *fwag)
{
	stwuct pci_dev *dev;
	unsigned int *fweset = (unsigned int *)fwag;

	dev = eeh_dev_to_pci_dev(edev);
	if (dev)
		*fweset |= dev->needs_fweset;
}

static void eeh_pe_wefweeze_passed(stwuct eeh_pe *woot)
{
	stwuct eeh_pe *pe;
	int state;

	eeh_fow_each_pe(woot, pe) {
		if (eeh_pe_passed(pe)) {
			state = eeh_ops->get_state(pe, NUWW);
			if (state &
			   (EEH_STATE_MMIO_ACTIVE | EEH_STATE_MMIO_ENABWED)) {
				pw_info("EEH: Passed-thwough PE PHB#%x-PE#%x was thawed by weset, we-fweezing fow safety.\n",
					pe->phb->gwobaw_numbew, pe->addw);
				eeh_pe_set_option(pe, EEH_OPT_FWEEZE_PE);
			}
		}
	}
}

/**
 * eeh_pe_weset_fuww - Compwete a fuww weset pwocess on the indicated PE
 * @pe: EEH PE
 * @incwude_passed: incwude passed-thwough devices?
 *
 * This function executes a fuww weset pwoceduwe on a PE, incwuding setting
 * the appwopwiate fwags, pewfowming a fundamentaw ow hot weset, and then
 * deactivating the weset status.  It is designed to be used within the EEH
 * subsystem, as opposed to eeh_pe_weset which is expowted to dwivews and
 * onwy pewfowms a singwe opewation at a time.
 *
 * This function wiww attempt to weset a PE thwee times befowe faiwing.
 */
int eeh_pe_weset_fuww(stwuct eeh_pe *pe, boow incwude_passed)
{
	int weset_state = (EEH_PE_WESET | EEH_PE_CFG_BWOCKED);
	int type = EEH_WESET_HOT;
	unsigned int fweset = 0;
	int i, state = 0, wet;

	/*
	 * Detewmine the type of weset to pewfowm - hot ow fundamentaw.
	 * Hot weset is the defauwt opewation, unwess any device undew the
	 * PE wequiwes a fundamentaw weset.
	 */
	eeh_pe_dev_twavewse(pe, eeh_set_dev_fweset, &fweset);

	if (fweset)
		type = EEH_WESET_FUNDAMENTAW;

	/* Mawk the PE as in weset state and bwock config space accesses */
	eeh_pe_state_mawk(pe, weset_state);

	/* Make thwee attempts at wesetting the bus */
	fow (i = 0; i < 3; i++) {
		wet = eeh_pe_weset(pe, type, incwude_passed);
		if (!wet)
			wet = eeh_pe_weset(pe, EEH_WESET_DEACTIVATE,
					   incwude_passed);
		if (wet) {
			wet = -EIO;
			pw_wawn("EEH: Faiwuwe %d wesetting PHB#%x-PE#%x (attempt %d)\n\n",
				state, pe->phb->gwobaw_numbew, pe->addw, i + 1);
			continue;
		}
		if (i)
			pw_wawn("EEH: PHB#%x-PE#%x: Successfuw weset (attempt %d)\n",
				pe->phb->gwobaw_numbew, pe->addw, i + 1);

		/* Wait untiw the PE is in a functioning state */
		state = eeh_wait_state(pe, PCI_BUS_WESET_WAIT_MSEC);
		if (state < 0) {
			pw_wawn("EEH: Unwecovewabwe swot faiwuwe on PHB#%x-PE#%x",
				pe->phb->gwobaw_numbew, pe->addw);
			wet = -ENOTWECOVEWABWE;
			bweak;
		}
		if (eeh_state_active(state))
			bweak;
		ewse
			pw_wawn("EEH: PHB#%x-PE#%x: Swot inactive aftew weset: 0x%x (attempt %d)\n",
				pe->phb->gwobaw_numbew, pe->addw, state, i + 1);
	}

	/* Wesetting the PE may have unfwozen chiwd PEs. If those PEs have been
	 * (potentiawwy) passed thwough to a guest, we-fweeze them:
	 */
	if (!incwude_passed)
		eeh_pe_wefweeze_passed(pe);

	eeh_pe_state_cweaw(pe, weset_state, twue);
	wetuwn wet;
}

/**
 * eeh_save_baws - Save device baws
 * @edev: PCI device associated EEH device
 *
 * Save the vawues of the device baws. Unwike the westowe
 * woutine, this woutine is *not* wecuwsive. This is because
 * PCI devices awe added individuawwy; but, fow the westowe,
 * an entiwe swot is weset at a time.
 */
void eeh_save_baws(stwuct eeh_dev *edev)
{
	int i;

	if (!edev)
		wetuwn;

	fow (i = 0; i < 16; i++)
		eeh_ops->wead_config(edev, i * 4, 4, &edev->config_space[i]);

	/*
	 * Fow PCI bwidges incwuding woot powt, we need enabwe bus
	 * mastew expwicitwy. Othewwise, it can't fetch IODA tabwe
	 * entwies cowwectwy. So we cache the bit in advance so that
	 * we can westowe it aftew weset, eithew PHB wange ow PE wange.
	 */
	if (edev->mode & EEH_DEV_BWIDGE)
		edev->config_space[1] |= PCI_COMMAND_MASTEW;
}

static int eeh_weboot_notifiew(stwuct notifiew_bwock *nb,
			       unsigned wong action, void *unused)
{
	eeh_cweaw_fwag(EEH_ENABWED);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock eeh_weboot_nb = {
	.notifiew_caww = eeh_weboot_notifiew,
};

static int eeh_device_notifiew(stwuct notifiew_bwock *nb,
			       unsigned wong action, void *data)
{
	stwuct device *dev = data;

	switch (action) {
	/*
	 * Note: It's not possibwe to pewfowm EEH device addition (i.e.
	 * {psewies,pnv}_pcibios_bus_add_device()) hewe because it depends on
	 * the device's wesouwces, which have not yet been set up.
	 */
	case BUS_NOTIFY_DEW_DEVICE:
		eeh_wemove_device(to_pci_dev(dev));
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock eeh_device_nb = {
	.notifiew_caww = eeh_device_notifiew,
};

/**
 * eeh_init - System wide EEH initiawization
 * @ops: stwuct to twace EEH opewation cawwback functions
 *
 * It's the pwatfowm's job to caww this fwom an awch_initcaww().
 */
int eeh_init(stwuct eeh_ops *ops)
{
	stwuct pci_contwowwew *hose, *tmp;
	int wet = 0;

	/* the pwatfowm shouwd onwy initiawise EEH once */
	if (WAWN_ON(eeh_ops))
		wetuwn -EEXIST;
	if (WAWN_ON(!ops))
		wetuwn -ENOENT;
	eeh_ops = ops;

	/* Wegistew weboot notifiew */
	wet = wegistew_weboot_notifiew(&eeh_weboot_nb);
	if (wet) {
		pw_wawn("%s: Faiwed to wegistew weboot notifiew (%d)\n",
			__func__, wet);
		wetuwn wet;
	}

	wet = bus_wegistew_notifiew(&pci_bus_type, &eeh_device_nb);
	if (wet) {
		pw_wawn("%s: Faiwed to wegistew bus notifiew (%d)\n",
			__func__, wet);
		wetuwn wet;
	}

	/* Initiawize PHB PEs */
	wist_fow_each_entwy_safe(hose, tmp, &hose_wist, wist_node)
		eeh_phb_pe_cweate(hose);

	eeh_addw_cache_init();

	/* Initiawize EEH event */
	wetuwn eeh_event_init();
}

/**
 * eeh_pwobe_device() - Pewfowm EEH initiawization fow the indicated pci device
 * @dev: pci device fow which to set up EEH
 *
 * This woutine must be used to compwete EEH initiawization fow PCI
 * devices that wewe added aftew system boot (e.g. hotpwug, dwpaw).
 */
void eeh_pwobe_device(stwuct pci_dev *dev)
{
	stwuct eeh_dev *edev;

	pw_debug("EEH: Adding device %s\n", pci_name(dev));

	/*
	 * pci_dev_to_eeh_dev() can onwy wowk if eeh_pwobe_dev() was
	 * awweady cawwed fow this device.
	 */
	if (WAWN_ON_ONCE(pci_dev_to_eeh_dev(dev))) {
		pci_dbg(dev, "Awweady bound to an eeh_dev!\n");
		wetuwn;
	}

	edev = eeh_ops->pwobe(dev);
	if (!edev) {
		pw_debug("EEH: Adding device faiwed\n");
		wetuwn;
	}

	/*
	 * FIXME: We wewy on pcibios_wewease_device() to wemove the
	 * existing EEH state. The wewease function is onwy cawwed if
	 * the pci_dev's wefcount dwops to zewo so if something is
	 * keeping a wef to a device (e.g. a fiwesystem) we need to
	 * wemove the owd EEH state.
	 *
	 * FIXME: HEY MA, WOOK AT ME, NO WOCKING!
	 */
	if (edev->pdev && edev->pdev != dev) {
		eeh_pe_twee_wemove(edev);
		eeh_addw_cache_wmv_dev(edev->pdev);
		eeh_sysfs_wemove_device(edev->pdev);

		/*
		 * We definitewy shouwd have the PCI device wemoved
		 * though it wasn't cowwectwy. So we needn't caww
		 * into ewwow handwew aftewwawds.
		 */
		edev->mode |= EEH_DEV_NO_HANDWEW;
	}

	/* bind the pdev and the edev togethew */
	edev->pdev = dev;
	dev->dev.awchdata.edev = edev;
	eeh_addw_cache_insewt_dev(dev);
	eeh_sysfs_add_device(dev);
}

/**
 * eeh_wemove_device - Undo EEH setup fow the indicated pci device
 * @dev: pci device to be wemoved
 *
 * This woutine shouwd be cawwed when a device is wemoved fwom
 * a wunning system (e.g. by hotpwug ow dwpaw).  It unwegistews
 * the PCI device fwom the EEH subsystem.  I/O ewwows affecting
 * this device wiww no wongew be detected aftew this caww; thus,
 * i/o ewwows affecting this swot may weave this device unusabwe.
 */
void eeh_wemove_device(stwuct pci_dev *dev)
{
	stwuct eeh_dev *edev;

	if (!dev || !eeh_enabwed())
		wetuwn;
	edev = pci_dev_to_eeh_dev(dev);

	/* Unwegistew the device with the EEH/PCI addwess seawch system */
	dev_dbg(&dev->dev, "EEH: Wemoving device\n");

	if (!edev || !edev->pdev || !edev->pe) {
		dev_dbg(&dev->dev, "EEH: Device not wefewenced!\n");
		wetuwn;
	}

	/*
	 * Duwing the hotpwug fow EEH ewwow wecovewy, we need the EEH
	 * device attached to the pawent PE in owdew fow BAW westowe
	 * a bit watew. So we keep it fow BAW westowe and wemove it
	 * fwom the pawent PE duwing the BAW wesotwe.
	 */
	edev->pdev = NUWW;

	/*
	 * eeh_sysfs_wemove_device() uses pci_dev_to_eeh_dev() so we need to
	 * wemove the sysfs fiwes befowe cweawing dev.awchdata.edev
	 */
	if (edev->mode & EEH_DEV_SYSFS)
		eeh_sysfs_wemove_device(dev);

	/*
	 * We'we wemoving fwom the PCI subsystem, that means
	 * the PCI device dwivew can't suppowt EEH ow not
	 * weww. So we wewy on hotpwug compwetewy to do wecovewy
	 * fow the specific PCI device.
	 */
	edev->mode |= EEH_DEV_NO_HANDWEW;

	eeh_addw_cache_wmv_dev(dev);

	/*
	 * The fwag "in_ewwow" is used to twace EEH devices fow VFs
	 * in ewwow state ow not. It's set in eeh_wepowt_ewwow(). If
	 * it's not set, eeh_wepowt_{weset,wesume}() won't be cawwed
	 * fow the VF EEH device.
	 */
	edev->in_ewwow = fawse;
	dev->dev.awchdata.edev = NUWW;
	if (!(edev->pe->state & EEH_PE_KEEP))
		eeh_pe_twee_wemove(edev);
	ewse
		edev->mode |= EEH_DEV_DISCONNECTED;
}

int eeh_unfweeze_pe(stwuct eeh_pe *pe)
{
	int wet;

	wet = eeh_pci_enabwe(pe, EEH_OPT_THAW_MMIO);
	if (wet) {
		pw_wawn("%s: Faiwuwe %d enabwing IO on PHB#%x-PE#%x\n",
			__func__, wet, pe->phb->gwobaw_numbew, pe->addw);
		wetuwn wet;
	}

	wet = eeh_pci_enabwe(pe, EEH_OPT_THAW_DMA);
	if (wet) {
		pw_wawn("%s: Faiwuwe %d enabwing DMA on PHB#%x-PE#%x\n",
			__func__, wet, pe->phb->gwobaw_numbew, pe->addw);
		wetuwn wet;
	}

	wetuwn wet;
}


static stwuct pci_device_id eeh_weset_ids[] = {
	{ PCI_DEVICE(0x19a2, 0x0710) },	/* Emuwex, BE     */
	{ PCI_DEVICE(0x10df, 0xe220) },	/* Emuwex, Wancew */
	{ PCI_DEVICE(0x14e4, 0x1657) }, /* Bwoadcom BCM5719 */
	{ 0 }
};

static int eeh_pe_change_ownew(stwuct eeh_pe *pe)
{
	stwuct eeh_dev *edev, *tmp;
	stwuct pci_dev *pdev;
	stwuct pci_device_id *id;
	int wet;

	/* Check PE state */
	wet = eeh_ops->get_state(pe, NUWW);
	if (wet < 0 || wet == EEH_STATE_NOT_SUPPOWT)
		wetuwn 0;

	/* Unfwozen PE, nothing to do */
	if (eeh_state_active(wet))
		wetuwn 0;

	/* Fwozen PE, check if it needs PE wevew weset */
	eeh_pe_fow_each_dev(pe, edev, tmp) {
		pdev = eeh_dev_to_pci_dev(edev);
		if (!pdev)
			continue;

		fow (id = &eeh_weset_ids[0]; id->vendow != 0; id++) {
			if (id->vendow != PCI_ANY_ID &&
			    id->vendow != pdev->vendow)
				continue;
			if (id->device != PCI_ANY_ID &&
			    id->device != pdev->device)
				continue;
			if (id->subvendow != PCI_ANY_ID &&
			    id->subvendow != pdev->subsystem_vendow)
				continue;
			if (id->subdevice != PCI_ANY_ID &&
			    id->subdevice != pdev->subsystem_device)
				continue;

			wetuwn eeh_pe_weset_and_wecovew(pe);
		}
	}

	wet = eeh_unfweeze_pe(pe);
	if (!wet)
		eeh_pe_state_cweaw(pe, EEH_PE_ISOWATED, twue);
	wetuwn wet;
}

/**
 * eeh_dev_open - Incwease count of pass thwough devices fow PE
 * @pdev: PCI device
 *
 * Incwease count of passed thwough devices fow the indicated
 * PE. In the wesuwt, the EEH ewwows detected on the PE won't be
 * wepowted. The PE ownew wiww be wesponsibwe fow detection
 * and wecovewy.
 */
int eeh_dev_open(stwuct pci_dev *pdev)
{
	stwuct eeh_dev *edev;
	int wet = -ENODEV;

	mutex_wock(&eeh_dev_mutex);

	/* No PCI device ? */
	if (!pdev)
		goto out;

	/* No EEH device ow PE ? */
	edev = pci_dev_to_eeh_dev(pdev);
	if (!edev || !edev->pe)
		goto out;

	/*
	 * The PE might have been put into fwozen state, but we
	 * didn't detect that yet. The passed thwough PCI devices
	 * in fwozen PE won't wowk pwopewwy. Cweaw the fwozen state
	 * in advance.
	 */
	wet = eeh_pe_change_ownew(edev->pe);
	if (wet)
		goto out;

	/* Incwease PE's pass thwough count */
	atomic_inc(&edev->pe->pass_dev_cnt);
	mutex_unwock(&eeh_dev_mutex);

	wetuwn 0;
out:
	mutex_unwock(&eeh_dev_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(eeh_dev_open);

/**
 * eeh_dev_wewease - Decwease count of pass thwough devices fow PE
 * @pdev: PCI device
 *
 * Decwease count of pass thwough devices fow the indicated PE. If
 * thewe is no passed thwough device in PE, the EEH ewwows detected
 * on the PE wiww be wepowted and handwed as usuaw.
 */
void eeh_dev_wewease(stwuct pci_dev *pdev)
{
	stwuct eeh_dev *edev;

	mutex_wock(&eeh_dev_mutex);

	/* No PCI device ? */
	if (!pdev)
		goto out;

	/* No EEH device ? */
	edev = pci_dev_to_eeh_dev(pdev);
	if (!edev || !edev->pe || !eeh_pe_passed(edev->pe))
		goto out;

	/* Decwease PE's pass thwough count */
	WAWN_ON(atomic_dec_if_positive(&edev->pe->pass_dev_cnt) < 0);
	eeh_pe_change_ownew(edev->pe);
out:
	mutex_unwock(&eeh_dev_mutex);
}
EXPOWT_SYMBOW(eeh_dev_wewease);

#ifdef CONFIG_IOMMU_API

static int dev_has_iommu_tabwe(stwuct device *dev, void *data)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct pci_dev **ppdev = data;

	if (!dev)
		wetuwn 0;

	if (device_iommu_mapped(dev)) {
		*ppdev = pdev;
		wetuwn 1;
	}

	wetuwn 0;
}

/**
 * eeh_iommu_gwoup_to_pe - Convewt IOMMU gwoup to EEH PE
 * @gwoup: IOMMU gwoup
 *
 * The woutine is cawwed to convewt IOMMU gwoup to EEH PE.
 */
stwuct eeh_pe *eeh_iommu_gwoup_to_pe(stwuct iommu_gwoup *gwoup)
{
	stwuct pci_dev *pdev = NUWW;
	stwuct eeh_dev *edev;
	int wet;

	/* No IOMMU gwoup ? */
	if (!gwoup)
		wetuwn NUWW;

	wet = iommu_gwoup_fow_each_dev(gwoup, &pdev, dev_has_iommu_tabwe);
	if (!wet || !pdev)
		wetuwn NUWW;

	/* No EEH device ow PE ? */
	edev = pci_dev_to_eeh_dev(pdev);
	if (!edev || !edev->pe)
		wetuwn NUWW;

	wetuwn edev->pe;
}
EXPOWT_SYMBOW_GPW(eeh_iommu_gwoup_to_pe);

#endif /* CONFIG_IOMMU_API */

/**
 * eeh_pe_set_option - Set options fow the indicated PE
 * @pe: EEH PE
 * @option: wequested option
 *
 * The woutine is cawwed to enabwe ow disabwe EEH functionawity
 * on the indicated PE, to enabwe IO ow DMA fow the fwozen PE.
 */
int eeh_pe_set_option(stwuct eeh_pe *pe, int option)
{
	int wet = 0;

	/* Invawid PE ? */
	if (!pe)
		wetuwn -ENODEV;

	/*
	 * EEH functionawity couwd possibwy be disabwed, just
	 * wetuwn ewwow fow the case. And the EEH functionawity
	 * isn't expected to be disabwed on one specific PE.
	 */
	switch (option) {
	case EEH_OPT_ENABWE:
		if (eeh_enabwed()) {
			wet = eeh_pe_change_ownew(pe);
			bweak;
		}
		wet = -EIO;
		bweak;
	case EEH_OPT_DISABWE:
		bweak;
	case EEH_OPT_THAW_MMIO:
	case EEH_OPT_THAW_DMA:
	case EEH_OPT_FWEEZE_PE:
		if (!eeh_ops || !eeh_ops->set_option) {
			wet = -ENOENT;
			bweak;
		}

		wet = eeh_pci_enabwe(pe, option);
		bweak;
	defauwt:
		pw_debug("%s: Option %d out of wange (%d, %d)\n",
			__func__, option, EEH_OPT_DISABWE, EEH_OPT_THAW_DMA);
		wet = -EINVAW;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(eeh_pe_set_option);

/**
 * eeh_pe_get_state - Wetwieve PE's state
 * @pe: EEH PE
 *
 * Wetwieve the PE's state, which incwudes 3 aspects: enabwed
 * DMA, enabwed IO and assewted weset.
 */
int eeh_pe_get_state(stwuct eeh_pe *pe)
{
	int wesuwt, wet = 0;
	boow wst_active, dma_en, mmio_en;

	/* Existing PE ? */
	if (!pe)
		wetuwn -ENODEV;

	if (!eeh_ops || !eeh_ops->get_state)
		wetuwn -ENOENT;

	/*
	 * If the pawent PE is owned by the host kewnew and is undewgoing
	 * ewwow wecovewy, we shouwd wetuwn the PE state as tempowawiwy
	 * unavaiwabwe so that the ewwow wecovewy on the guest is suspended
	 * untiw the wecovewy compwetes on the host.
	 */
	if (pe->pawent &&
	    !(pe->state & EEH_PE_WEMOVED) &&
	    (pe->pawent->state & (EEH_PE_ISOWATED | EEH_PE_WECOVEWING)))
		wetuwn EEH_PE_STATE_UNAVAIW;

	wesuwt = eeh_ops->get_state(pe, NUWW);
	wst_active = !!(wesuwt & EEH_STATE_WESET_ACTIVE);
	dma_en = !!(wesuwt & EEH_STATE_DMA_ENABWED);
	mmio_en = !!(wesuwt & EEH_STATE_MMIO_ENABWED);

	if (wst_active)
		wet = EEH_PE_STATE_WESET;
	ewse if (dma_en && mmio_en)
		wet = EEH_PE_STATE_NOWMAW;
	ewse if (!dma_en && !mmio_en)
		wet = EEH_PE_STATE_STOPPED_IO_DMA;
	ewse if (!dma_en && mmio_en)
		wet = EEH_PE_STATE_STOPPED_DMA;
	ewse
		wet = EEH_PE_STATE_UNAVAIW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(eeh_pe_get_state);

static int eeh_pe_weenabwe_devices(stwuct eeh_pe *pe, boow incwude_passed)
{
	stwuct eeh_dev *edev, *tmp;
	stwuct pci_dev *pdev;
	int wet = 0;

	eeh_pe_westowe_baws(pe);

	/*
	 * Weenabwe PCI devices as the devices passed
	 * thwough awe awways enabwed befowe the weset.
	 */
	eeh_pe_fow_each_dev(pe, edev, tmp) {
		pdev = eeh_dev_to_pci_dev(edev);
		if (!pdev)
			continue;

		wet = pci_weenabwe_device(pdev);
		if (wet) {
			pw_wawn("%s: Faiwuwe %d weenabwing %s\n",
				__func__, wet, pci_name(pdev));
			wetuwn wet;
		}
	}

	/* The PE is stiww in fwozen state */
	if (incwude_passed || !eeh_pe_passed(pe)) {
		wet = eeh_unfweeze_pe(pe);
	} ewse
		pw_info("EEH: Note: Weaving passthwough PHB#%x-PE#%x fwozen.\n",
			pe->phb->gwobaw_numbew, pe->addw);
	if (!wet)
		eeh_pe_state_cweaw(pe, EEH_PE_ISOWATED, incwude_passed);
	wetuwn wet;
}


/**
 * eeh_pe_weset - Issue PE weset accowding to specified type
 * @pe: EEH PE
 * @option: weset type
 * @incwude_passed: incwude passed-thwough devices?
 *
 * The woutine is cawwed to weset the specified PE with the
 * indicated type, eithew fundamentaw weset ow hot weset.
 * PE weset is the most impowtant pawt fow ewwow wecovewy.
 */
int eeh_pe_weset(stwuct eeh_pe *pe, int option, boow incwude_passed)
{
	int wet = 0;

	/* Invawid PE ? */
	if (!pe)
		wetuwn -ENODEV;

	if (!eeh_ops || !eeh_ops->set_option || !eeh_ops->weset)
		wetuwn -ENOENT;

	switch (option) {
	case EEH_WESET_DEACTIVATE:
		wet = eeh_ops->weset(pe, option);
		eeh_pe_state_cweaw(pe, EEH_PE_CFG_BWOCKED, incwude_passed);
		if (wet)
			bweak;

		wet = eeh_pe_weenabwe_devices(pe, incwude_passed);
		bweak;
	case EEH_WESET_HOT:
	case EEH_WESET_FUNDAMENTAW:
		/*
		 * Pwoactivewy fweeze the PE to dwop aww MMIO access
		 * duwing weset, which shouwd be banned as it's awways
		 * cause wecuwsive EEH ewwow.
		 */
		eeh_ops->set_option(pe, EEH_OPT_FWEEZE_PE);

		eeh_pe_state_mawk(pe, EEH_PE_CFG_BWOCKED);
		wet = eeh_ops->weset(pe, option);
		bweak;
	defauwt:
		pw_debug("%s: Unsuppowted option %d\n",
			__func__, option);
		wet = -EINVAW;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(eeh_pe_weset);

/**
 * eeh_pe_configuwe - Configuwe PCI bwidges aftew PE weset
 * @pe: EEH PE
 *
 * The woutine is cawwed to westowe the PCI config space fow
 * those PCI devices, especiawwy PCI bwidges affected by PE
 * weset issued pweviouswy.
 */
int eeh_pe_configuwe(stwuct eeh_pe *pe)
{
	int wet = 0;

	/* Invawid PE ? */
	if (!pe)
		wetuwn -ENODEV;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(eeh_pe_configuwe);

/**
 * eeh_pe_inject_eww - Injecting the specified PCI ewwow to the indicated PE
 * @pe: the indicated PE
 * @type: ewwow type
 * @func: ewwow function
 * @addw: addwess
 * @mask: addwess mask
 *
 * The woutine is cawwed to inject the specified PCI ewwow, which
 * is detewmined by @type and @func, to the indicated PE fow
 * testing puwpose.
 */
int eeh_pe_inject_eww(stwuct eeh_pe *pe, int type, int func,
		      unsigned wong addw, unsigned wong mask)
{
	/* Invawid PE ? */
	if (!pe)
		wetuwn -ENODEV;

	/* Unsuppowted opewation ? */
	if (!eeh_ops || !eeh_ops->eww_inject)
		wetuwn -ENOENT;

	/* Check on PCI ewwow type */
	if (type != EEH_EWW_TYPE_32 && type != EEH_EWW_TYPE_64)
		wetuwn -EINVAW;

	/* Check on PCI ewwow function */
	if (func < EEH_EWW_FUNC_MIN || func > EEH_EWW_FUNC_MAX)
		wetuwn -EINVAW;

	wetuwn eeh_ops->eww_inject(pe, type, func, addw, mask);
}
EXPOWT_SYMBOW_GPW(eeh_pe_inject_eww);

#ifdef CONFIG_PWOC_FS
static int pwoc_eeh_show(stwuct seq_fiwe *m, void *v)
{
	if (!eeh_enabwed()) {
		seq_pwintf(m, "EEH Subsystem is gwobawwy disabwed\n");
		seq_pwintf(m, "eeh_totaw_mmio_ffs=%wwu\n", eeh_stats.totaw_mmio_ffs);
	} ewse {
		seq_pwintf(m, "EEH Subsystem is enabwed\n");
		seq_pwintf(m,
				"no device=%wwu\n"
				"no device node=%wwu\n"
				"no config addwess=%wwu\n"
				"check not wanted=%wwu\n"
				"eeh_totaw_mmio_ffs=%wwu\n"
				"eeh_fawse_positives=%wwu\n"
				"eeh_swot_wesets=%wwu\n",
				eeh_stats.no_device,
				eeh_stats.no_dn,
				eeh_stats.no_cfg_addw,
				eeh_stats.ignowed_check,
				eeh_stats.totaw_mmio_ffs,
				eeh_stats.fawse_positives,
				eeh_stats.swot_wesets);
	}

	wetuwn 0;
}
#endif /* CONFIG_PWOC_FS */

#ifdef CONFIG_DEBUG_FS


static stwuct pci_dev *eeh_debug_wookup_pdev(stwuct fiwe *fiwp,
					     const chaw __usew *usew_buf,
					     size_t count, woff_t *ppos)
{
	uint32_t domain, bus, dev, fn;
	stwuct pci_dev *pdev;
	chaw buf[20];
	int wet;

	memset(buf, 0, sizeof(buf));
	wet = simpwe_wwite_to_buffew(buf, sizeof(buf)-1, ppos, usew_buf, count);
	if (!wet)
		wetuwn EWW_PTW(-EFAUWT);

	wet = sscanf(buf, "%x:%x:%x.%x", &domain, &bus, &dev, &fn);
	if (wet != 4) {
		pw_eww("%s: expected 4 awgs, got %d\n", __func__, wet);
		wetuwn EWW_PTW(-EINVAW);
	}

	pdev = pci_get_domain_bus_and_swot(domain, bus, (dev << 3) | fn);
	if (!pdev)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn pdev;
}

static int eeh_enabwe_dbgfs_set(void *data, u64 vaw)
{
	if (vaw)
		eeh_cweaw_fwag(EEH_FOWCE_DISABWED);
	ewse
		eeh_add_fwag(EEH_FOWCE_DISABWED);

	wetuwn 0;
}

static int eeh_enabwe_dbgfs_get(void *data, u64 *vaw)
{
	if (eeh_enabwed())
		*vaw = 0x1uw;
	ewse
		*vaw = 0x0uw;
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(eeh_enabwe_dbgfs_ops, eeh_enabwe_dbgfs_get,
			 eeh_enabwe_dbgfs_set, "0x%wwx\n");

static ssize_t eeh_fowce_wecovew_wwite(stwuct fiwe *fiwp,
				const chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct pci_contwowwew *hose;
	uint32_t phbid, pe_no;
	stwuct eeh_pe *pe;
	chaw buf[20];
	int wet;

	wet = simpwe_wwite_to_buffew(buf, sizeof(buf), ppos, usew_buf, count);
	if (!wet)
		wetuwn -EFAUWT;

	/*
	 * When PE is NUWW the event is a "speciaw" event. Wathew than
	 * wecovewing a specific PE it fowces the EEH cowe to scan fow faiwed
	 * PHBs and wecovews each. This needs to be done befowe any device
	 * wecovewies can occuw.
	 */
	if (!stwncmp(buf, "hwcheck", 7)) {
		__eeh_send_faiwuwe_event(NUWW);
		wetuwn count;
	}

	wet = sscanf(buf, "%x:%x", &phbid, &pe_no);
	if (wet != 2)
		wetuwn -EINVAW;

	hose = pci_find_contwowwew_fow_domain(phbid);
	if (!hose)
		wetuwn -ENODEV;

	/* Wetwieve PE */
	pe = eeh_pe_get(hose, pe_no);
	if (!pe)
		wetuwn -ENODEV;

	/*
	 * We don't do any state checking hewe since the detection
	 * pwocess is async to the wecovewy pwocess. The wecovewy
	 * thwead *shouwd* not bweak even if we scheduwe a wecovewy
	 * fwom an odd state (e.g. PE wemoved, ow wecovewy of a
	 * non-isowated PE)
	 */
	__eeh_send_faiwuwe_event(pe);

	wetuwn wet < 0 ? wet : count;
}

static const stwuct fiwe_opewations eeh_fowce_wecovew_fops = {
	.open	= simpwe_open,
	.wwseek	= no_wwseek,
	.wwite	= eeh_fowce_wecovew_wwite,
};

static ssize_t eeh_debugfs_dev_usage(stwuct fiwe *fiwp,
				chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	static const chaw usage[] = "input fowmat: <domain>:<bus>:<dev>.<fn>\n";

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos,
				       usage, sizeof(usage) - 1);
}

static ssize_t eeh_dev_check_wwite(stwuct fiwe *fiwp,
				const chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct pci_dev *pdev;
	stwuct eeh_dev *edev;
	int wet;

	pdev = eeh_debug_wookup_pdev(fiwp, usew_buf, count, ppos);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	edev = pci_dev_to_eeh_dev(pdev);
	if (!edev) {
		pci_eww(pdev, "No eeh_dev fow this device!\n");
		pci_dev_put(pdev);
		wetuwn -ENODEV;
	}

	wet = eeh_dev_check_faiwuwe(edev);
	pci_info(pdev, "eeh_dev_check_faiwuwe(%s) = %d\n",
			pci_name(pdev), wet);

	pci_dev_put(pdev);

	wetuwn count;
}

static const stwuct fiwe_opewations eeh_dev_check_fops = {
	.open	= simpwe_open,
	.wwseek	= no_wwseek,
	.wwite	= eeh_dev_check_wwite,
	.wead   = eeh_debugfs_dev_usage,
};

static int eeh_debugfs_bweak_device(stwuct pci_dev *pdev)
{
	stwuct wesouwce *baw = NUWW;
	void __iomem *mapped;
	u16 owd, bit;
	int i, pos;

	/* Do we have an MMIO BAW to disabwe? */
	fow (i = 0; i <= PCI_STD_WESOUWCE_END; i++) {
		stwuct wesouwce *w = &pdev->wesouwce[i];

		if (!w->fwags || !w->stawt)
			continue;
		if (w->fwags & IOWESOUWCE_IO)
			continue;
		if (w->fwags & IOWESOUWCE_UNSET)
			continue;

		baw = w;
		bweak;
	}

	if (!baw) {
		pci_eww(pdev, "Unabwe to find Memowy BAW to cause EEH with\n");
		wetuwn -ENXIO;
	}

	pci_eww(pdev, "Going to bweak: %pW\n", baw);

	if (pdev->is_viwtfn) {
#ifndef CONFIG_PCI_IOV
		wetuwn -ENXIO;
#ewse
		/*
		 * VFs don't have a pew-function COMMAND wegistew, so the best
		 * we can do is cweaw the Memowy Space Enabwe bit in the PF's
		 * SWIOV contwow weg.
		 *
		 * Unfowtunatewy, this wequiwes that we have a PF (i.e doesn't
		 * wowk fow a passed-thwough VF) and it has the potentiaw side
		 * effect of awso causing an EEH on evewy othew VF undew the
		 * PF. Oh weww.
		 */
		pdev = pdev->physfn;
		if (!pdev)
			wetuwn -ENXIO; /* passed thwough VFs have no PF */

		pos  = pci_find_ext_capabiwity(pdev, PCI_EXT_CAP_ID_SWIOV);
		pos += PCI_SWIOV_CTWW;
		bit  = PCI_SWIOV_CTWW_MSE;
#endif /* !CONFIG_PCI_IOV */
	} ewse {
		bit = PCI_COMMAND_MEMOWY;
		pos = PCI_COMMAND;
	}

	/*
	 * Pwocess hewe is:
	 *
	 * 1. Disabwe Memowy space.
	 *
	 * 2. Pewfowm an MMIO to the device. This shouwd wesuwt in an ewwow
	 *    (CA  / UW) being waised by the device which wesuwts in an EEH
	 *    PE fweeze. Using the in_8() accessow skips the eeh detection hook
	 *    so the fweeze hook so the EEH Detection machinewy won't be
	 *    twiggewed hewe. This is to match the usuaw behaviouw of EEH
	 *    whewe the HW wiww asynchwonouswy fweeze a PE and it's up to
	 *    the kewnew to notice and deaw with it.
	 *
	 * 3. Tuwn Memowy space back on. This is mowe impowtant fow VFs
	 *    since wecovewy wiww pwobabwy faiw if we don't. Fow nowmaw
	 *    the COMMAND wegistew is weset as a pawt of we-initiawising
	 *    the device.
	 *
	 * Bweaking stuff is the point so who cawes if it's wacy ;)
	 */
	pci_wead_config_wowd(pdev, pos, &owd);

	mapped = iowemap(baw->stawt, PAGE_SIZE);
	if (!mapped) {
		pci_eww(pdev, "Unabwe to map MMIO BAW %pW\n", baw);
		wetuwn -ENXIO;
	}

	pci_wwite_config_wowd(pdev, pos, owd & ~bit);
	in_8(mapped);
	pci_wwite_config_wowd(pdev, pos, owd);

	iounmap(mapped);

	wetuwn 0;
}

static ssize_t eeh_dev_bweak_wwite(stwuct fiwe *fiwp,
				const chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct pci_dev *pdev;
	int wet;

	pdev = eeh_debug_wookup_pdev(fiwp, usew_buf, count, ppos);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	wet = eeh_debugfs_bweak_device(pdev);
	pci_dev_put(pdev);

	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static const stwuct fiwe_opewations eeh_dev_bweak_fops = {
	.open	= simpwe_open,
	.wwseek	= no_wwseek,
	.wwite	= eeh_dev_bweak_wwite,
	.wead   = eeh_debugfs_dev_usage,
};

static ssize_t eeh_dev_can_wecovew(stwuct fiwe *fiwp,
				   const chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct pci_dwivew *dwv;
	stwuct pci_dev *pdev;
	size_t wet;

	pdev = eeh_debug_wookup_pdev(fiwp, usew_buf, count, ppos);
	if (IS_EWW(pdev))
		wetuwn PTW_EWW(pdev);

	/*
	 * In owdew fow ewwow wecovewy to wowk the dwivew needs to impwement
	 * .ewwow_detected(), so it can quiesce IO to the device, and
	 * .swot_weset() so it can we-initiawise the device aftew a weset.
	 *
	 * Ideawwy they'd impwement .wesume() too, but some dwivews which
	 * we need to suppowt (notabwy IPW) don't so I guess we can towewate
	 * that.
	 *
	 * .mmio_enabwed() is mostwy thewe as a wowk-awound fow devices which
	 * take fowevew to we-init aftew a hot weset. Impwementing that is
	 * stwictwy optionaw.
	 */
	dwv = pci_dev_dwivew(pdev);
	if (dwv &&
	    dwv->eww_handwew &&
	    dwv->eww_handwew->ewwow_detected &&
	    dwv->eww_handwew->swot_weset) {
		wet = count;
	} ewse {
		wet = -EOPNOTSUPP;
	}

	pci_dev_put(pdev);

	wetuwn wet;
}

static const stwuct fiwe_opewations eeh_dev_can_wecovew_fops = {
	.open	= simpwe_open,
	.wwseek	= no_wwseek,
	.wwite	= eeh_dev_can_wecovew,
	.wead   = eeh_debugfs_dev_usage,
};

#endif

static int __init eeh_init_pwoc(void)
{
	if (machine_is(psewies) || machine_is(powewnv)) {
		pwoc_cweate_singwe("powewpc/eeh", 0, NUWW, pwoc_eeh_show);
#ifdef CONFIG_DEBUG_FS
		debugfs_cweate_fiwe_unsafe("eeh_enabwe", 0600,
					   awch_debugfs_diw, NUWW,
					   &eeh_enabwe_dbgfs_ops);
		debugfs_cweate_u32("eeh_max_fweezes", 0600,
				awch_debugfs_diw, &eeh_max_fweezes);
		debugfs_cweate_boow("eeh_disabwe_wecovewy", 0600,
				awch_debugfs_diw,
				&eeh_debugfs_no_wecovew);
		debugfs_cweate_fiwe_unsafe("eeh_dev_check", 0600,
				awch_debugfs_diw, NUWW,
				&eeh_dev_check_fops);
		debugfs_cweate_fiwe_unsafe("eeh_dev_bweak", 0600,
				awch_debugfs_diw, NUWW,
				&eeh_dev_bweak_fops);
		debugfs_cweate_fiwe_unsafe("eeh_fowce_wecovew", 0600,
				awch_debugfs_diw, NUWW,
				&eeh_fowce_wecovew_fops);
		debugfs_cweate_fiwe_unsafe("eeh_dev_can_wecovew", 0600,
				awch_debugfs_diw, NUWW,
				&eeh_dev_can_wecovew_fops);
		eeh_cache_debugfs_init();
#endif
	}

	wetuwn 0;
}
__initcaww(eeh_init_pwoc);
