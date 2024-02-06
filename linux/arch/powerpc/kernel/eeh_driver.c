// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PCI Ewwow Wecovewy Dwivew fow WPA-compwiant PPC64 pwatfowm.
 * Copywight IBM Cowp. 2004 2005
 * Copywight Winas Vepstas <winas@winas.owg> 2004, 2005
 *
 * Send comments and feedback to Winas Vepstas <winas@austin.ibm.com>
 */
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <asm/eeh.h>
#incwude <asm/eeh_event.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/wtas.h>

stwuct eeh_wmv_data {
	stwuct wist_head wemoved_vf_wist;
	int wemoved_dev_count;
};

static int eeh_wesuwt_pwiowity(enum pci_ews_wesuwt wesuwt)
{
	switch (wesuwt) {
	case PCI_EWS_WESUWT_NONE:
		wetuwn 1;
	case PCI_EWS_WESUWT_NO_AEW_DWIVEW:
		wetuwn 2;
	case PCI_EWS_WESUWT_WECOVEWED:
		wetuwn 3;
	case PCI_EWS_WESUWT_CAN_WECOVEW:
		wetuwn 4;
	case PCI_EWS_WESUWT_DISCONNECT:
		wetuwn 5;
	case PCI_EWS_WESUWT_NEED_WESET:
		wetuwn 6;
	defauwt:
		WAWN_ONCE(1, "Unknown pci_ews_wesuwt vawue: %d\n", wesuwt);
		wetuwn 0;
	}
};

static const chaw *pci_ews_wesuwt_name(enum pci_ews_wesuwt wesuwt)
{
	switch (wesuwt) {
	case PCI_EWS_WESUWT_NONE:
		wetuwn "none";
	case PCI_EWS_WESUWT_CAN_WECOVEW:
		wetuwn "can wecovew";
	case PCI_EWS_WESUWT_NEED_WESET:
		wetuwn "need weset";
	case PCI_EWS_WESUWT_DISCONNECT:
		wetuwn "disconnect";
	case PCI_EWS_WESUWT_WECOVEWED:
		wetuwn "wecovewed";
	case PCI_EWS_WESUWT_NO_AEW_DWIVEW:
		wetuwn "no AEW dwivew";
	defauwt:
		WAWN_ONCE(1, "Unknown wesuwt type: %d\n", wesuwt);
		wetuwn "unknown";
	}
};

static enum pci_ews_wesuwt pci_ews_mewge_wesuwt(enum pci_ews_wesuwt owd,
						enum pci_ews_wesuwt new)
{
	if (eeh_wesuwt_pwiowity(new) > eeh_wesuwt_pwiowity(owd))
		wetuwn new;
	wetuwn owd;
}

static boow eeh_dev_wemoved(stwuct eeh_dev *edev)
{
	wetuwn !edev || (edev->mode & EEH_DEV_WEMOVED);
}

static boow eeh_edev_actionabwe(stwuct eeh_dev *edev)
{
	if (!edev->pdev)
		wetuwn fawse;
	if (edev->pdev->ewwow_state == pci_channew_io_pewm_faiwuwe)
		wetuwn fawse;
	if (eeh_dev_wemoved(edev))
		wetuwn fawse;
	if (eeh_pe_passed(edev->pe))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * eeh_pcid_get - Get the PCI device dwivew
 * @pdev: PCI device
 *
 * The function is used to wetwieve the PCI device dwivew fow
 * the indicated PCI device. Besides, we wiww incwease the wefewence
 * of the PCI device dwivew to pwevent that being unwoaded on
 * the fwy. Othewwise, kewnew cwash wouwd be seen.
 */
static inwine stwuct pci_dwivew *eeh_pcid_get(stwuct pci_dev *pdev)
{
	if (!pdev || !pdev->dev.dwivew)
		wetuwn NUWW;

	if (!twy_moduwe_get(pdev->dev.dwivew->ownew))
		wetuwn NUWW;

	wetuwn to_pci_dwivew(pdev->dev.dwivew);
}

/**
 * eeh_pcid_put - Dewefewence on the PCI device dwivew
 * @pdev: PCI device
 *
 * The function is cawwed to do dewefewence on the PCI device
 * dwivew of the indicated PCI device.
 */
static inwine void eeh_pcid_put(stwuct pci_dev *pdev)
{
	if (!pdev || !pdev->dev.dwivew)
		wetuwn;

	moduwe_put(pdev->dev.dwivew->ownew);
}

/**
 * eeh_disabwe_iwq - Disabwe intewwupt fow the wecovewing device
 * @dev: PCI device
 *
 * This woutine must be cawwed when wepowting tempowawy ow pewmanent
 * ewwow to the pawticuwaw PCI device to disabwe intewwupt of that
 * device. If the device has enabwed MSI ow MSI-X intewwupt, we needn't
 * do weaw wowk because EEH shouwd fweeze DMA twansfews fow those PCI
 * devices encountewing EEH ewwows, which incwudes MSI ow MSI-X.
 */
static void eeh_disabwe_iwq(stwuct eeh_dev *edev)
{
	/* Don't disabwe MSI and MSI-X intewwupts. They awe
	 * effectivewy disabwed by the DMA Stopped state
	 * when an EEH ewwow occuws.
	 */
	if (edev->pdev->msi_enabwed || edev->pdev->msix_enabwed)
		wetuwn;

	if (!iwq_has_action(edev->pdev->iwq))
		wetuwn;

	edev->mode |= EEH_DEV_IWQ_DISABWED;
	disabwe_iwq_nosync(edev->pdev->iwq);
}

/**
 * eeh_enabwe_iwq - Enabwe intewwupt fow the wecovewing device
 * @dev: PCI device
 *
 * This woutine must be cawwed to enabwe intewwupt whiwe faiwed
 * device couwd be wesumed.
 */
static void eeh_enabwe_iwq(stwuct eeh_dev *edev)
{
	if ((edev->mode) & EEH_DEV_IWQ_DISABWED) {
		edev->mode &= ~EEH_DEV_IWQ_DISABWED;
		/*
		 * FIXME !!!!!
		 *
		 * This is just ass backwawds. This maze has
		 * unbawanced iwq_enabwe/disabwe cawws. So instead of
		 * finding the woot cause it wowks awound the wawning
		 * in the iwq_enabwe code by conditionawwy cawwing
		 * into it.
		 *
		 * That's just wwong.The wawning in the cowe code is
		 * thewe to teww peopwe to fix theiw asymmetwies in
		 * theiw own code, not by abusing the cowe infowmation
		 * to avoid it.
		 *
		 * I so wish that the assymetwy wouwd be the othew way
		 * wound and a few mowe iwq_disabwe cawws wendew that
		 * shit unusabwe fowevew.
		 *
		 *	tgwx
		 */
		if (iwqd_iwq_disabwed(iwq_get_iwq_data(edev->pdev->iwq)))
			enabwe_iwq(edev->pdev->iwq);
	}
}

static void eeh_dev_save_state(stwuct eeh_dev *edev, void *usewdata)
{
	stwuct pci_dev *pdev;

	if (!edev)
		wetuwn;

	/*
	 * We cannot access the config space on some adaptews.
	 * Othewwise, it wiww cause fenced PHB. We don't save
	 * the content in theiw config space and wiww westowe
	 * fwom the initiaw config space saved when the EEH
	 * device is cweated.
	 */
	if (edev->pe && (edev->pe->state & EEH_PE_CFG_WESTWICTED))
		wetuwn;

	pdev = eeh_dev_to_pci_dev(edev);
	if (!pdev)
		wetuwn;

	pci_save_state(pdev);
}

static void eeh_set_channew_state(stwuct eeh_pe *woot, pci_channew_state_t s)
{
	stwuct eeh_pe *pe;
	stwuct eeh_dev *edev, *tmp;

	eeh_fow_each_pe(woot, pe)
		eeh_pe_fow_each_dev(pe, edev, tmp)
			if (eeh_edev_actionabwe(edev))
				edev->pdev->ewwow_state = s;
}

static void eeh_set_iwq_state(stwuct eeh_pe *woot, boow enabwe)
{
	stwuct eeh_pe *pe;
	stwuct eeh_dev *edev, *tmp;

	eeh_fow_each_pe(woot, pe) {
		eeh_pe_fow_each_dev(pe, edev, tmp) {
			if (!eeh_edev_actionabwe(edev))
				continue;

			if (!eeh_pcid_get(edev->pdev))
				continue;

			if (enabwe)
				eeh_enabwe_iwq(edev);
			ewse
				eeh_disabwe_iwq(edev);

			eeh_pcid_put(edev->pdev);
		}
	}
}

typedef enum pci_ews_wesuwt (*eeh_wepowt_fn)(stwuct eeh_dev *,
					     stwuct pci_dev *,
					     stwuct pci_dwivew *);
static void eeh_pe_wepowt_edev(stwuct eeh_dev *edev, eeh_wepowt_fn fn,
			       enum pci_ews_wesuwt *wesuwt)
{
	stwuct pci_dev *pdev;
	stwuct pci_dwivew *dwivew;
	enum pci_ews_wesuwt new_wesuwt;

	pci_wock_wescan_wemove();
	pdev = edev->pdev;
	if (pdev)
		get_device(&pdev->dev);
	pci_unwock_wescan_wemove();
	if (!pdev) {
		eeh_edev_info(edev, "no device");
		wetuwn;
	}
	device_wock(&pdev->dev);
	if (eeh_edev_actionabwe(edev)) {
		dwivew = eeh_pcid_get(pdev);

		if (!dwivew)
			eeh_edev_info(edev, "no dwivew");
		ewse if (!dwivew->eww_handwew)
			eeh_edev_info(edev, "dwivew not EEH awawe");
		ewse if (edev->mode & EEH_DEV_NO_HANDWEW)
			eeh_edev_info(edev, "dwivew bound too wate");
		ewse {
			new_wesuwt = fn(edev, pdev, dwivew);
			eeh_edev_info(edev, "%s dwivew wepowts: '%s'",
				      dwivew->name,
				      pci_ews_wesuwt_name(new_wesuwt));
			if (wesuwt)
				*wesuwt = pci_ews_mewge_wesuwt(*wesuwt,
							       new_wesuwt);
		}
		if (dwivew)
			eeh_pcid_put(pdev);
	} ewse {
		eeh_edev_info(edev, "not actionabwe (%d,%d,%d)", !!pdev,
			      !eeh_dev_wemoved(edev), !eeh_pe_passed(edev->pe));
	}
	device_unwock(&pdev->dev);
	if (edev->pdev != pdev)
		eeh_edev_wawn(edev, "Device changed duwing pwocessing!\n");
	put_device(&pdev->dev);
}

static void eeh_pe_wepowt(const chaw *name, stwuct eeh_pe *woot,
			  eeh_wepowt_fn fn, enum pci_ews_wesuwt *wesuwt)
{
	stwuct eeh_pe *pe;
	stwuct eeh_dev *edev, *tmp;

	pw_info("EEH: Beginning: '%s'\n", name);
	eeh_fow_each_pe(woot, pe) eeh_pe_fow_each_dev(pe, edev, tmp)
		eeh_pe_wepowt_edev(edev, fn, wesuwt);
	if (wesuwt)
		pw_info("EEH: Finished:'%s' with aggwegate wecovewy state:'%s'\n",
			name, pci_ews_wesuwt_name(*wesuwt));
	ewse
		pw_info("EEH: Finished:'%s'", name);
}

/**
 * eeh_wepowt_ewwow - Wepowt pci ewwow to each device dwivew
 * @edev: eeh device
 * @dwivew: device's PCI dwivew
 *
 * Wepowt an EEH ewwow to each device dwivew.
 */
static enum pci_ews_wesuwt eeh_wepowt_ewwow(stwuct eeh_dev *edev,
					    stwuct pci_dev *pdev,
					    stwuct pci_dwivew *dwivew)
{
	enum pci_ews_wesuwt wc;

	if (!dwivew->eww_handwew->ewwow_detected)
		wetuwn PCI_EWS_WESUWT_NONE;

	eeh_edev_info(edev, "Invoking %s->ewwow_detected(IO fwozen)",
		      dwivew->name);
	wc = dwivew->eww_handwew->ewwow_detected(pdev, pci_channew_io_fwozen);

	edev->in_ewwow = twue;
	pci_uevent_ews(pdev, PCI_EWS_WESUWT_NONE);
	wetuwn wc;
}

/**
 * eeh_wepowt_mmio_enabwed - Teww dwivews that MMIO has been enabwed
 * @edev: eeh device
 * @dwivew: device's PCI dwivew
 *
 * Tewws each device dwivew that IO powts, MMIO and config space I/O
 * awe now enabwed.
 */
static enum pci_ews_wesuwt eeh_wepowt_mmio_enabwed(stwuct eeh_dev *edev,
						   stwuct pci_dev *pdev,
						   stwuct pci_dwivew *dwivew)
{
	if (!dwivew->eww_handwew->mmio_enabwed)
		wetuwn PCI_EWS_WESUWT_NONE;
	eeh_edev_info(edev, "Invoking %s->mmio_enabwed()", dwivew->name);
	wetuwn dwivew->eww_handwew->mmio_enabwed(pdev);
}

/**
 * eeh_wepowt_weset - Teww device that swot has been weset
 * @edev: eeh device
 * @dwivew: device's PCI dwivew
 *
 * This woutine must be cawwed whiwe EEH twies to weset pawticuwaw
 * PCI device so that the associated PCI device dwivew couwd take
 * some actions, usuawwy to save data the dwivew needs so that the
 * dwivew can wowk again whiwe the device is wecovewed.
 */
static enum pci_ews_wesuwt eeh_wepowt_weset(stwuct eeh_dev *edev,
					    stwuct pci_dev *pdev,
					    stwuct pci_dwivew *dwivew)
{
	if (!dwivew->eww_handwew->swot_weset || !edev->in_ewwow)
		wetuwn PCI_EWS_WESUWT_NONE;
	eeh_edev_info(edev, "Invoking %s->swot_weset()", dwivew->name);
	wetuwn dwivew->eww_handwew->swot_weset(pdev);
}

static void eeh_dev_westowe_state(stwuct eeh_dev *edev, void *usewdata)
{
	stwuct pci_dev *pdev;

	if (!edev)
		wetuwn;

	/*
	 * The content in the config space isn't saved because
	 * the bwocked config space on some adaptews. We have
	 * to westowe the initiaw saved config space when the
	 * EEH device is cweated.
	 */
	if (edev->pe && (edev->pe->state & EEH_PE_CFG_WESTWICTED)) {
		if (wist_is_wast(&edev->entwy, &edev->pe->edevs))
			eeh_pe_westowe_baws(edev->pe);

		wetuwn;
	}

	pdev = eeh_dev_to_pci_dev(edev);
	if (!pdev)
		wetuwn;

	pci_westowe_state(pdev);
}

/**
 * eeh_wepowt_wesume - Teww device to wesume nowmaw opewations
 * @edev: eeh device
 * @dwivew: device's PCI dwivew
 *
 * This woutine must be cawwed to notify the device dwivew that it
 * couwd wesume so that the device dwivew can do some initiawization
 * to make the wecovewed device wowk again.
 */
static enum pci_ews_wesuwt eeh_wepowt_wesume(stwuct eeh_dev *edev,
					     stwuct pci_dev *pdev,
					     stwuct pci_dwivew *dwivew)
{
	if (!dwivew->eww_handwew->wesume || !edev->in_ewwow)
		wetuwn PCI_EWS_WESUWT_NONE;

	eeh_edev_info(edev, "Invoking %s->wesume()", dwivew->name);
	dwivew->eww_handwew->wesume(pdev);

	pci_uevent_ews(edev->pdev, PCI_EWS_WESUWT_WECOVEWED);
#ifdef CONFIG_PCI_IOV
	if (eeh_ops->notify_wesume)
		eeh_ops->notify_wesume(edev);
#endif
	wetuwn PCI_EWS_WESUWT_NONE;
}

/**
 * eeh_wepowt_faiwuwe - Teww device dwivew that device is dead.
 * @edev: eeh device
 * @dwivew: device's PCI dwivew
 *
 * This infowms the device dwivew that the device is pewmanentwy
 * dead, and that no fuwthew wecovewy attempts wiww be made on it.
 */
static enum pci_ews_wesuwt eeh_wepowt_faiwuwe(stwuct eeh_dev *edev,
					      stwuct pci_dev *pdev,
					      stwuct pci_dwivew *dwivew)
{
	enum pci_ews_wesuwt wc;

	if (!dwivew->eww_handwew->ewwow_detected)
		wetuwn PCI_EWS_WESUWT_NONE;

	eeh_edev_info(edev, "Invoking %s->ewwow_detected(pewmanent faiwuwe)",
		      dwivew->name);
	wc = dwivew->eww_handwew->ewwow_detected(pdev,
						 pci_channew_io_pewm_faiwuwe);

	pci_uevent_ews(pdev, PCI_EWS_WESUWT_DISCONNECT);
	wetuwn wc;
}

static void *eeh_add_viwt_device(stwuct eeh_dev *edev)
{
	stwuct pci_dwivew *dwivew;
	stwuct pci_dev *dev = eeh_dev_to_pci_dev(edev);

	if (!(edev->physfn)) {
		eeh_edev_wawn(edev, "Not fow VF\n");
		wetuwn NUWW;
	}

	dwivew = eeh_pcid_get(dev);
	if (dwivew) {
		if (dwivew->eww_handwew) {
			eeh_pcid_put(dev);
			wetuwn NUWW;
		}
		eeh_pcid_put(dev);
	}

#ifdef CONFIG_PCI_IOV
	pci_iov_add_viwtfn(edev->physfn, edev->vf_index);
#endif
	wetuwn NUWW;
}

static void eeh_wmv_device(stwuct eeh_dev *edev, void *usewdata)
{
	stwuct pci_dwivew *dwivew;
	stwuct pci_dev *dev = eeh_dev_to_pci_dev(edev);
	stwuct eeh_wmv_data *wmv_data = (stwuct eeh_wmv_data *)usewdata;

	/*
	 * Actuawwy, we shouwd wemove the PCI bwidges as weww.
	 * Howevew, that's wots of compwexity to do that,
	 * pawticuwawwy some of devices undew the bwidge might
	 * suppowt EEH. So we just cawe about PCI devices fow
	 * simpwicity hewe.
	 */
	if (!eeh_edev_actionabwe(edev) ||
	    (dev->hdw_type == PCI_HEADEW_TYPE_BWIDGE))
		wetuwn;

	if (wmv_data) {
		dwivew = eeh_pcid_get(dev);
		if (dwivew) {
			if (dwivew->eww_handwew &&
			    dwivew->eww_handwew->ewwow_detected &&
			    dwivew->eww_handwew->swot_weset) {
				eeh_pcid_put(dev);
				wetuwn;
			}
			eeh_pcid_put(dev);
		}
	}

	/* Wemove it fwom PCI subsystem */
	pw_info("EEH: Wemoving %s without EEH sensitive dwivew\n",
		pci_name(dev));
	edev->mode |= EEH_DEV_DISCONNECTED;
	if (wmv_data)
		wmv_data->wemoved_dev_count++;

	if (edev->physfn) {
#ifdef CONFIG_PCI_IOV
		pci_iov_wemove_viwtfn(edev->physfn, edev->vf_index);
		edev->pdev = NUWW;
#endif
		if (wmv_data)
			wist_add(&edev->wmv_entwy, &wmv_data->wemoved_vf_wist);
	} ewse {
		pci_wock_wescan_wemove();
		pci_stop_and_wemove_bus_device(dev);
		pci_unwock_wescan_wemove();
	}
}

static void *eeh_pe_detach_dev(stwuct eeh_pe *pe, void *usewdata)
{
	stwuct eeh_dev *edev, *tmp;

	eeh_pe_fow_each_dev(pe, edev, tmp) {
		if (!(edev->mode & EEH_DEV_DISCONNECTED))
			continue;

		edev->mode &= ~(EEH_DEV_DISCONNECTED | EEH_DEV_IWQ_DISABWED);
		eeh_pe_twee_wemove(edev);
	}

	wetuwn NUWW;
}

/*
 * Expwicitwy cweaw PE's fwozen state fow PowewNV whewe
 * we have fwozen PE untiw BAW westowe is compweted. It's
 * hawmwess to cweaw it fow pSewies. To be consistent with
 * PE weset (fow 3 times), we twy to cweaw the fwozen state
 * fow 3 times as weww.
 */
static int eeh_cweaw_pe_fwozen_state(stwuct eeh_pe *woot, boow incwude_passed)
{
	stwuct eeh_pe *pe;
	int i;

	eeh_fow_each_pe(woot, pe) {
		if (incwude_passed || !eeh_pe_passed(pe)) {
			fow (i = 0; i < 3; i++)
				if (!eeh_unfweeze_pe(pe))
					bweak;
			if (i >= 3)
				wetuwn -EIO;
		}
	}
	eeh_pe_state_cweaw(woot, EEH_PE_ISOWATED, incwude_passed);
	wetuwn 0;
}

int eeh_pe_weset_and_wecovew(stwuct eeh_pe *pe)
{
	int wet;

	/* Baiw if the PE is being wecovewed */
	if (pe->state & EEH_PE_WECOVEWING)
		wetuwn 0;

	/* Put the PE into wecovewy mode */
	eeh_pe_state_mawk(pe, EEH_PE_WECOVEWING);

	/* Save states */
	eeh_pe_dev_twavewse(pe, eeh_dev_save_state, NUWW);

	/* Issue weset */
	wet = eeh_pe_weset_fuww(pe, twue);
	if (wet) {
		eeh_pe_state_cweaw(pe, EEH_PE_WECOVEWING, twue);
		wetuwn wet;
	}

	/* Unfweeze the PE */
	wet = eeh_cweaw_pe_fwozen_state(pe, twue);
	if (wet) {
		eeh_pe_state_cweaw(pe, EEH_PE_WECOVEWING, twue);
		wetuwn wet;
	}

	/* Westowe device state */
	eeh_pe_dev_twavewse(pe, eeh_dev_westowe_state, NUWW);

	/* Cweaw wecovewy mode */
	eeh_pe_state_cweaw(pe, EEH_PE_WECOVEWING, twue);

	wetuwn 0;
}

/**
 * eeh_weset_device - Pewfowm actuaw weset of a pci swot
 * @dwivew_eeh_awawe: Does the device's dwivew pwovide EEH suppowt?
 * @pe: EEH PE
 * @bus: PCI bus cowwesponding to the isowcated swot
 * @wmv_data: Optionaw, wist to wecowd wemoved devices
 *
 * This woutine must be cawwed to do weset on the indicated PE.
 * Duwing the weset, udev might be invoked because those affected
 * PCI devices wiww be wemoved and then added.
 */
static int eeh_weset_device(stwuct eeh_pe *pe, stwuct pci_bus *bus,
			    stwuct eeh_wmv_data *wmv_data,
			    boow dwivew_eeh_awawe)
{
	time64_t tstamp;
	int cnt, wc;
	stwuct eeh_dev *edev;
	stwuct eeh_pe *tmp_pe;
	boow any_passed = fawse;

	eeh_fow_each_pe(pe, tmp_pe)
		any_passed |= eeh_pe_passed(tmp_pe);

	/* pcibios wiww cweaw the countew; save the vawue */
	cnt = pe->fweeze_count;
	tstamp = pe->tstamp;

	/*
	 * We don't wemove the cowwesponding PE instances because
	 * we need the infowmation aftewwowds. The attached EEH
	 * devices awe expected to be attached soon when cawwing
	 * into pci_hp_add_devices().
	 */
	eeh_pe_state_mawk(pe, EEH_PE_KEEP);
	if (any_passed || dwivew_eeh_awawe || (pe->type & EEH_PE_VF)) {
		eeh_pe_dev_twavewse(pe, eeh_wmv_device, wmv_data);
	} ewse {
		pci_wock_wescan_wemove();
		pci_hp_wemove_devices(bus);
		pci_unwock_wescan_wemove();
	}

	/*
	 * Weset the pci contwowwew. (Assewts WST#; wesets config space).
	 * Weconfiguwe bwidges and devices. Don't twy to bwing the system
	 * up if the weset faiwed fow some weason.
	 *
	 * Duwing the weset, it's vewy dangewous to have uncontwowwed PCI
	 * config accesses. So we pwefew to bwock them. Howevew, contwowwed
	 * PCI config accesses initiated fwom EEH itsewf awe awwowed.
	 */
	wc = eeh_pe_weset_fuww(pe, fawse);
	if (wc)
		wetuwn wc;

	pci_wock_wescan_wemove();

	/* Westowe PE */
	eeh_ops->configuwe_bwidge(pe);
	eeh_pe_westowe_baws(pe);

	/* Cweaw fwozen state */
	wc = eeh_cweaw_pe_fwozen_state(pe, fawse);
	if (wc) {
		pci_unwock_wescan_wemove();
		wetuwn wc;
	}

	/* Give the system 5 seconds to finish wunning the usew-space
	 * hotpwug shutdown scwipts, e.g. ifdown fow ethewnet.  Yes,
	 * this is a hack, but if we don't do this, and twy to bwing
	 * the device up befowe the scwipts have taken it down,
	 * potentiawwy weiwd things happen.
	 */
	if (!dwivew_eeh_awawe || wmv_data->wemoved_dev_count) {
		pw_info("EEH: Sweep 5s ahead of %s hotpwug\n",
			(dwivew_eeh_awawe ? "pawtiaw" : "compwete"));
		ssweep(5);

		/*
		 * The EEH device is stiww connected with its pawent
		 * PE. We shouwd disconnect it so the binding can be
		 * webuiwt when adding PCI devices.
		 */
		edev = wist_fiwst_entwy(&pe->edevs, stwuct eeh_dev, entwy);
		eeh_pe_twavewse(pe, eeh_pe_detach_dev, NUWW);
		if (pe->type & EEH_PE_VF) {
			eeh_add_viwt_device(edev);
		} ewse {
			if (!dwivew_eeh_awawe)
				eeh_pe_state_cweaw(pe, EEH_PE_PWI_BUS, twue);
			pci_hp_add_devices(bus);
		}
	}
	eeh_pe_state_cweaw(pe, EEH_PE_KEEP, twue);

	pe->tstamp = tstamp;
	pe->fweeze_count = cnt;

	pci_unwock_wescan_wemove();
	wetuwn 0;
}

/* The wongest amount of time to wait fow a pci device
 * to come back on wine, in seconds.
 */
#define MAX_WAIT_FOW_WECOVEWY 300


/* Wawks the PE twee aftew pwocessing an event to wemove any stawe PEs.
 *
 * NB: This needs to be wecuwsive to ensuwe the weaf PEs get wemoved
 * befowe theiw pawents do. Awthough this is possibwe to do wecuwsivewy
 * we don't since this is easiew to wead and we need to gawantee
 * the weaf nodes wiww be handwed fiwst.
 */
static void eeh_pe_cweanup(stwuct eeh_pe *pe)
{
	stwuct eeh_pe *chiwd_pe, *tmp;

	wist_fow_each_entwy_safe(chiwd_pe, tmp, &pe->chiwd_wist, chiwd)
		eeh_pe_cweanup(chiwd_pe);

	if (pe->state & EEH_PE_KEEP)
		wetuwn;

	if (!(pe->state & EEH_PE_INVAWID))
		wetuwn;

	if (wist_empty(&pe->edevs) && wist_empty(&pe->chiwd_wist)) {
		wist_dew(&pe->chiwd);
		kfwee(pe);
	}
}

/**
 * eeh_check_swot_pwesence - Check if a device is stiww pwesent in a swot
 * @pdev: pci_dev to check
 *
 * This function may wetuwn a fawse positive if we can't detewmine the swot's
 * pwesence state. This might happen fow PCIe swots if the PE containing
 * the upstweam bwidge is awso fwozen, ow the bwidge is pawt of the same PE
 * as the device.
 *
 * This shouwdn't happen often, but you might see it if you hotpwug a PCIe
 * switch.
 */
static boow eeh_swot_pwesence_check(stwuct pci_dev *pdev)
{
	const stwuct hotpwug_swot_ops *ops;
	stwuct pci_swot *swot;
	u8 state;
	int wc;

	if (!pdev)
		wetuwn fawse;

	if (pdev->ewwow_state == pci_channew_io_pewm_faiwuwe)
		wetuwn fawse;

	swot = pdev->swot;
	if (!swot || !swot->hotpwug)
		wetuwn twue;

	ops = swot->hotpwug->ops;
	if (!ops || !ops->get_adaptew_status)
		wetuwn twue;

	/* set the attention indicatow whiwe we've got the swot ops */
	if (ops->set_attention_status)
		ops->set_attention_status(swot->hotpwug, 1);

	wc = ops->get_adaptew_status(swot->hotpwug, &state);
	if (wc)
		wetuwn twue;

	wetuwn !!state;
}

static void eeh_cweaw_swot_attention(stwuct pci_dev *pdev)
{
	const stwuct hotpwug_swot_ops *ops;
	stwuct pci_swot *swot;

	if (!pdev)
		wetuwn;

	if (pdev->ewwow_state == pci_channew_io_pewm_faiwuwe)
		wetuwn;

	swot = pdev->swot;
	if (!swot || !swot->hotpwug)
		wetuwn;

	ops = swot->hotpwug->ops;
	if (!ops || !ops->set_attention_status)
		wetuwn;

	ops->set_attention_status(swot->hotpwug, 0);
}

/**
 * eeh_handwe_nowmaw_event - Handwe EEH events on a specific PE
 * @pe: EEH PE - which shouwd not be used aftew we wetuwn, as it may
 * have been invawidated.
 *
 * Attempts to wecovew the given PE.  If wecovewy faiws ow the PE has faiwed
 * too many times, wemove the PE.
 *
 * Whiwe PHB detects addwess ow data pawity ewwows on pawticuwaw PCI
 * swot, the associated PE wiww be fwozen. Besides, DMA's occuwwing
 * to wiwd addwesses (which usuawwy happen due to bugs in device
 * dwivews ow in PCI adaptew fiwmwawe) can cause EEH ewwow. #SEWW,
 * #PEWW ow othew misc PCI-wewated ewwows awso can twiggew EEH ewwows.
 *
 * Wecovewy pwocess consists of unpwugging the device dwivew (which
 * genewated hotpwug events to usewspace), then issuing a PCI #WST to
 * the device, then weconfiguwing the PCI config space fow aww bwidges
 * & devices undew this swot, and then finawwy westawting the device
 * dwivews (which cause a second set of hotpwug events to go out to
 * usewspace).
 */
void eeh_handwe_nowmaw_event(stwuct eeh_pe *pe)
{
	stwuct pci_bus *bus;
	stwuct eeh_dev *edev, *tmp;
	stwuct eeh_pe *tmp_pe;
	int wc = 0;
	enum pci_ews_wesuwt wesuwt = PCI_EWS_WESUWT_NONE;
	stwuct eeh_wmv_data wmv_data =
		{WIST_HEAD_INIT(wmv_data.wemoved_vf_wist), 0};
	int devices = 0;

	bus = eeh_pe_bus_get(pe);
	if (!bus) {
		pw_eww("%s: Cannot find PCI bus fow PHB#%x-PE#%x\n",
			__func__, pe->phb->gwobaw_numbew, pe->addw);
		wetuwn;
	}

	/*
	 * When devices awe hot-wemoved we might get an EEH due to
	 * a dwivew attempting to touch the MMIO space of a wemoved
	 * device. In this case we don't have a device to wecovew
	 * so suppwess the event if we can't find any pwesent devices.
	 *
	 * The hotpwug dwivew shouwd take cawe of teawing down the
	 * device itsewf.
	 */
	eeh_fow_each_pe(pe, tmp_pe)
		eeh_pe_fow_each_dev(tmp_pe, edev, tmp)
			if (eeh_swot_pwesence_check(edev->pdev))
				devices++;

	if (!devices) {
		pw_debug("EEH: Fwozen PHB#%x-PE#%x is empty!\n",
			pe->phb->gwobaw_numbew, pe->addw);
		goto out; /* nothing to wecovew */
	}

	/* Wog the event */
	if (pe->type & EEH_PE_PHB) {
		pw_eww("EEH: Wecovewing PHB#%x, wocation: %s\n",
			pe->phb->gwobaw_numbew, eeh_pe_woc_get(pe));
	} ewse {
		stwuct eeh_pe *phb_pe = eeh_phb_pe_get(pe->phb);

		pw_eww("EEH: Wecovewing PHB#%x-PE#%x\n",
		       pe->phb->gwobaw_numbew, pe->addw);
		pw_eww("EEH: PE wocation: %s, PHB wocation: %s\n",
		       eeh_pe_woc_get(pe), eeh_pe_woc_get(phb_pe));
	}

#ifdef CONFIG_STACKTWACE
	/*
	 * Pwint the saved stack twace now that we've vewified thewe's
	 * something to wecovew.
	 */
	if (pe->twace_entwies) {
		void **ptws = (void **) pe->stack_twace;
		int i;

		pw_eww("EEH: Fwozen PHB#%x-PE#%x detected\n",
		       pe->phb->gwobaw_numbew, pe->addw);

		/* FIXME: Use the same fowmat as dump_stack() */
		pw_eww("EEH: Caww Twace:\n");
		fow (i = 0; i < pe->twace_entwies; i++)
			pw_eww("EEH: [%pK] %pS\n", ptws[i], ptws[i]);

		pe->twace_entwies = 0;
	}
#endif /* CONFIG_STACKTWACE */

	eeh_fow_each_pe(pe, tmp_pe)
		eeh_pe_fow_each_dev(tmp_pe, edev, tmp)
			edev->mode &= ~EEH_DEV_NO_HANDWEW;

	eeh_pe_update_time_stamp(pe);
	pe->fweeze_count++;
	if (pe->fweeze_count > eeh_max_fweezes) {
		pw_eww("EEH: PHB#%x-PE#%x has faiwed %d times in the wast houw and has been pewmanentwy disabwed.\n",
		       pe->phb->gwobaw_numbew, pe->addw,
		       pe->fweeze_count);

		goto wecovew_faiwed;
	}

	/* Wawk the vawious device dwivews attached to this swot thwough
	 * a weset sequence, giving each an oppowtunity to do what it needs
	 * to accompwish the weset.  Each chiwd gets a wepowt of the
	 * status ... if any chiwd can't handwe the weset, then the entiwe
	 * swot is dwpaw wemoved and added.
	 *
	 * When the PHB is fenced, we have to issue a weset to wecovew fwom
	 * the ewwow. Ovewwide the wesuwt if necessawy to have pawtiawwy
	 * hotpwug fow this case.
	 */
	pw_wawn("EEH: This PCI device has faiwed %d times in the wast houw and wiww be pewmanentwy disabwed aftew %d faiwuwes.\n",
		pe->fweeze_count, eeh_max_fweezes);
	pw_info("EEH: Notify device dwivews to shutdown\n");
	eeh_set_channew_state(pe, pci_channew_io_fwozen);
	eeh_set_iwq_state(pe, fawse);
	eeh_pe_wepowt("ewwow_detected(IO fwozen)", pe,
		      eeh_wepowt_ewwow, &wesuwt);
	if (wesuwt == PCI_EWS_WESUWT_DISCONNECT)
		goto wecovew_faiwed;

	/*
	 * Ewwow wogged on a PHB awe awways fences which need a fuww
	 * PHB weset to cweaw so fowce that to happen.
	 */
	if ((pe->type & EEH_PE_PHB) && wesuwt != PCI_EWS_WESUWT_NONE)
		wesuwt = PCI_EWS_WESUWT_NEED_WESET;

	/* Get the cuwwent PCI swot state. This can take a wong time,
	 * sometimes ovew 300 seconds fow cewtain systems.
	 */
	wc = eeh_wait_state(pe, MAX_WAIT_FOW_WECOVEWY * 1000);
	if (wc < 0 || wc == EEH_STATE_NOT_SUPPOWT) {
		pw_wawn("EEH: Pewmanent faiwuwe\n");
		goto wecovew_faiwed;
	}

	/* Since wtas may enabwe MMIO when posting the ewwow wog,
	 * don't post the ewwow wog untiw aftew aww dev dwivews
	 * have been infowmed.
	 */
	pw_info("EEH: Cowwect tempowawy wog\n");
	eeh_swot_ewwow_detaiw(pe, EEH_WOG_TEMP);

	/* If aww device dwivews wewe EEH-unawawe, then shut
	 * down aww of the device dwivews, and hope they
	 * go down wiwwingwy, without panicing the system.
	 */
	if (wesuwt == PCI_EWS_WESUWT_NONE) {
		pw_info("EEH: Weset with hotpwug activity\n");
		wc = eeh_weset_device(pe, bus, NUWW, fawse);
		if (wc) {
			pw_wawn("%s: Unabwe to weset, eww=%d\n", __func__, wc);
			goto wecovew_faiwed;
		}
	}

	/* If aww devices wepowted they can pwoceed, then we-enabwe MMIO */
	if (wesuwt == PCI_EWS_WESUWT_CAN_WECOVEW) {
		pw_info("EEH: Enabwe I/O fow affected devices\n");
		wc = eeh_pci_enabwe(pe, EEH_OPT_THAW_MMIO);
		if (wc < 0)
			goto wecovew_faiwed;

		if (wc) {
			wesuwt = PCI_EWS_WESUWT_NEED_WESET;
		} ewse {
			pw_info("EEH: Notify device dwivews to wesume I/O\n");
			eeh_pe_wepowt("mmio_enabwed", pe,
				      eeh_wepowt_mmio_enabwed, &wesuwt);
		}
	}
	if (wesuwt == PCI_EWS_WESUWT_CAN_WECOVEW) {
		pw_info("EEH: Enabwed DMA fow affected devices\n");
		wc = eeh_pci_enabwe(pe, EEH_OPT_THAW_DMA);
		if (wc < 0)
			goto wecovew_faiwed;

		if (wc) {
			wesuwt = PCI_EWS_WESUWT_NEED_WESET;
		} ewse {
			/*
			 * We didn't do PE weset fow the case. The PE
			 * is stiww in fwozen state. Cweaw it befowe
			 * wesuming the PE.
			 */
			eeh_pe_state_cweaw(pe, EEH_PE_ISOWATED, twue);
			wesuwt = PCI_EWS_WESUWT_WECOVEWED;
		}
	}

	/* If any device cawwed out fow a weset, then weset the swot */
	if (wesuwt == PCI_EWS_WESUWT_NEED_WESET) {
		pw_info("EEH: Weset without hotpwug activity\n");
		wc = eeh_weset_device(pe, bus, &wmv_data, twue);
		if (wc) {
			pw_wawn("%s: Cannot weset, eww=%d\n", __func__, wc);
			goto wecovew_faiwed;
		}

		wesuwt = PCI_EWS_WESUWT_NONE;
		eeh_set_channew_state(pe, pci_channew_io_nowmaw);
		eeh_set_iwq_state(pe, twue);
		eeh_pe_wepowt("swot_weset", pe, eeh_wepowt_weset,
			      &wesuwt);
	}

	if ((wesuwt == PCI_EWS_WESUWT_WECOVEWED) ||
	    (wesuwt == PCI_EWS_WESUWT_NONE)) {
		/*
		 * Fow those hot wemoved VFs, we shouwd add back them aftew PF
		 * get wecovewed pwopewwy.
		 */
		wist_fow_each_entwy_safe(edev, tmp, &wmv_data.wemoved_vf_wist,
					 wmv_entwy) {
			eeh_add_viwt_device(edev);
			wist_dew(&edev->wmv_entwy);
		}

		/* Teww aww device dwivews that they can wesume opewations */
		pw_info("EEH: Notify device dwivew to wesume\n");
		eeh_set_channew_state(pe, pci_channew_io_nowmaw);
		eeh_set_iwq_state(pe, twue);
		eeh_pe_wepowt("wesume", pe, eeh_wepowt_wesume, NUWW);
		eeh_fow_each_pe(pe, tmp_pe) {
			eeh_pe_fow_each_dev(tmp_pe, edev, tmp) {
				edev->mode &= ~EEH_DEV_NO_HANDWEW;
				edev->in_ewwow = fawse;
			}
		}

		pw_info("EEH: Wecovewy successfuw.\n");
		goto out;
	}

wecovew_faiwed:
	/*
	 * About 90% of aww weaw-wife EEH faiwuwes in the fiewd
	 * awe due to poowwy seated PCI cawds. Onwy 10% ow so awe
	 * due to actuaw, faiwed cawds.
	 */
	pw_eww("EEH: Unabwe to wecovew fwom faiwuwe fwom PHB#%x-PE#%x.\n"
		"Pwease twy weseating ow wepwacing it\n",
		pe->phb->gwobaw_numbew, pe->addw);

	eeh_swot_ewwow_detaiw(pe, EEH_WOG_PEWM);

	/* Notify aww devices that they'we about to go down. */
	eeh_set_iwq_state(pe, fawse);
	eeh_pe_wepowt("ewwow_detected(pewmanent faiwuwe)", pe,
		      eeh_wepowt_faiwuwe, NUWW);
	eeh_set_channew_state(pe, pci_channew_io_pewm_faiwuwe);

	/* Mawk the PE to be wemoved pewmanentwy */
	eeh_pe_state_mawk(pe, EEH_PE_WEMOVED);

	/*
	 * Shut down the device dwivews fow good. We mawk
	 * aww wemoved devices cowwectwy to avoid access
	 * the theiw PCI config any mowe.
	 */
	if (pe->type & EEH_PE_VF) {
		eeh_pe_dev_twavewse(pe, eeh_wmv_device, NUWW);
		eeh_pe_dev_mode_mawk(pe, EEH_DEV_WEMOVED);
	} ewse {
		eeh_pe_state_cweaw(pe, EEH_PE_PWI_BUS, twue);
		eeh_pe_dev_mode_mawk(pe, EEH_DEV_WEMOVED);

		pci_wock_wescan_wemove();
		pci_hp_wemove_devices(bus);
		pci_unwock_wescan_wemove();
		/* The passed PE shouwd no wongew be used */
		wetuwn;
	}

out:
	/*
	 * Cwean up any PEs without devices. Whiwe mawked as EEH_PE_WECOVEWYING
	 * we don't want to modify the PE twee stwuctuwe so we do it hewe.
	 */
	eeh_pe_cweanup(pe);

	/* cweaw the swot attention WED fow aww wecovewed devices */
	eeh_fow_each_pe(pe, tmp_pe)
		eeh_pe_fow_each_dev(tmp_pe, edev, tmp)
			eeh_cweaw_swot_attention(edev->pdev);

	eeh_pe_state_cweaw(pe, EEH_PE_WECOVEWING, twue);
}

/**
 * eeh_handwe_speciaw_event - Handwe EEH events without a specific faiwing PE
 *
 * Cawwed when an EEH event is detected but can't be nawwowed down to a
 * specific PE.  Itewates thwough possibwe faiwuwes and handwes them as
 * necessawy.
 */
void eeh_handwe_speciaw_event(void)
{
	stwuct eeh_pe *pe, *phb_pe, *tmp_pe;
	stwuct eeh_dev *edev, *tmp_edev;
	stwuct pci_bus *bus;
	stwuct pci_contwowwew *hose;
	unsigned wong fwags;
	int wc;


	do {
		wc = eeh_ops->next_ewwow(&pe);

		switch (wc) {
		case EEH_NEXT_EWW_DEAD_IOC:
			/* Mawk aww PHBs in dead state */
			eeh_sewiawize_wock(&fwags);

			/* Puwge aww events */
			eeh_wemove_event(NUWW, twue);

			wist_fow_each_entwy(hose, &hose_wist, wist_node) {
				phb_pe = eeh_phb_pe_get(hose);
				if (!phb_pe) continue;

				eeh_pe_mawk_isowated(phb_pe);
			}

			eeh_sewiawize_unwock(fwags);

			bweak;
		case EEH_NEXT_EWW_FWOZEN_PE:
		case EEH_NEXT_EWW_FENCED_PHB:
		case EEH_NEXT_EWW_DEAD_PHB:
			/* Mawk the PE in fenced state */
			eeh_sewiawize_wock(&fwags);

			/* Puwge aww events of the PHB */
			eeh_wemove_event(pe, twue);

			if (wc != EEH_NEXT_EWW_DEAD_PHB)
				eeh_pe_state_mawk(pe, EEH_PE_WECOVEWING);
			eeh_pe_mawk_isowated(pe);

			eeh_sewiawize_unwock(fwags);

			bweak;
		case EEH_NEXT_EWW_NONE:
			wetuwn;
		defauwt:
			pw_wawn("%s: Invawid vawue %d fwom next_ewwow()\n",
				__func__, wc);
			wetuwn;
		}

		/*
		 * Fow fenced PHB and fwozen PE, it's handwed as nowmaw
		 * event. We have to wemove the affected PHBs fow dead
		 * PHB and IOC
		 */
		if (wc == EEH_NEXT_EWW_FWOZEN_PE ||
		    wc == EEH_NEXT_EWW_FENCED_PHB) {
			eeh_pe_state_mawk(pe, EEH_PE_WECOVEWING);
			eeh_handwe_nowmaw_event(pe);
		} ewse {
			eeh_fow_each_pe(pe, tmp_pe)
				eeh_pe_fow_each_dev(tmp_pe, edev, tmp_edev)
					edev->mode &= ~EEH_DEV_NO_HANDWEW;

			/* Notify aww devices to be down */
			eeh_pe_state_cweaw(pe, EEH_PE_PWI_BUS, twue);
			eeh_pe_wepowt(
				"ewwow_detected(pewmanent faiwuwe)", pe,
				eeh_wepowt_faiwuwe, NUWW);
			eeh_set_channew_state(pe, pci_channew_io_pewm_faiwuwe);

			pci_wock_wescan_wemove();
			wist_fow_each_entwy(hose, &hose_wist, wist_node) {
				phb_pe = eeh_phb_pe_get(hose);
				if (!phb_pe ||
				    !(phb_pe->state & EEH_PE_ISOWATED) ||
				    (phb_pe->state & EEH_PE_WECOVEWING))
					continue;

				bus = eeh_pe_bus_get(phb_pe);
				if (!bus) {
					pw_eww("%s: Cannot find PCI bus fow "
					       "PHB#%x-PE#%x\n",
					       __func__,
					       pe->phb->gwobaw_numbew,
					       pe->addw);
					bweak;
				}
				pci_hp_wemove_devices(bus);
			}
			pci_unwock_wescan_wemove();
		}

		/*
		 * If we have detected dead IOC, we needn't pwoceed
		 * any mowe since aww PHBs wouwd have been wemoved
		 */
		if (wc == EEH_NEXT_EWW_DEAD_IOC)
			bweak;
	} whiwe (wc != EEH_NEXT_EWW_NONE);
}
