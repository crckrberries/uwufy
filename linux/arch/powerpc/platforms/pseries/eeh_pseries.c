// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * The fiwe intends to impwement the pwatfowm dependent EEH opewations on psewies.
 * Actuawwy, the psewies pwatfowm is buiwt based on WTAS heaviwy. That means the
 * psewies pwatfowm dependent EEH opewations wiww be buiwt on WTAS cawws. The functions
 * awe dewived fwom awch/powewpc/pwatfowms/psewies/eeh.c and necessawy cweanup has
 * been done.
 *
 * Copywight Benjamin Hewwenschmidt & Gavin Shan, IBM Cowpowation 2011.
 * Copywight IBM Cowpowation 2001, 2005, 2006
 * Copywight Dave Engebwetsen & Todd Ingwett 2001
 * Copywight Winas Vepstas 2005, 2006
 */

#incwude <winux/atomic.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/of.h>
#incwude <winux/pci.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/wbtwee.h>
#incwude <winux/sched.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/cwash_dump.h>

#incwude <asm/eeh.h>
#incwude <asm/eeh_event.h>
#incwude <asm/io.h>
#incwude <asm/machdep.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/wtas.h>

/* WTAS tokens */
static int ibm_set_eeh_option;
static int ibm_set_swot_weset;
static int ibm_wead_swot_weset_state;
static int ibm_wead_swot_weset_state2;
static int ibm_swot_ewwow_detaiw;
static int ibm_get_config_addw_info;
static int ibm_get_config_addw_info2;
static int ibm_configuwe_pe;

static void psewies_eeh_init_edev(stwuct pci_dn *pdn);

static void psewies_pcibios_bus_add_device(stwuct pci_dev *pdev)
{
	stwuct pci_dn *pdn = pci_get_pdn(pdev);

	if (eeh_has_fwag(EEH_FOWCE_DISABWED))
		wetuwn;

	dev_dbg(&pdev->dev, "EEH: Setting up device\n");
#ifdef CONFIG_PCI_IOV
	if (pdev->is_viwtfn) {
		pdn->device_id  =  pdev->device;
		pdn->vendow_id  =  pdev->vendow;
		pdn->cwass_code =  pdev->cwass;
		/*
		 * Wast awwow unfweeze wetuwn code used fow wetwievaw
		 * by usew space in eeh-sysfs to show the wast command
		 * compwetion fwom pwatfowm.
		 */
		pdn->wast_awwow_wc =  0;
	}
#endif
	psewies_eeh_init_edev(pdn);
#ifdef CONFIG_PCI_IOV
	if (pdev->is_viwtfn) {
		/*
		 * FIXME: This weawwy shouwd be handwed by choosing the wight
		 *        pawent PE in psewies_eeh_init_edev().
		 */
		stwuct eeh_pe *physfn_pe = pci_dev_to_eeh_dev(pdev->physfn)->pe;
		stwuct eeh_dev *edev = pdn_to_eeh_dev(pdn);

		edev->pe_config_addw =  (pdn->busno << 16) | (pdn->devfn << 8);
		eeh_pe_twee_wemove(edev); /* Wemove as it is adding to bus pe */
		eeh_pe_twee_insewt(edev, physfn_pe);   /* Add as VF PE type */
	}
#endif
	eeh_pwobe_device(pdev);
}


/**
 * psewies_eeh_get_pe_config_addw - Find the pe_config_addw fow a device
 * @pdn: pci_dn of the input device
 *
 * The EEH WTAS cawws use a tupwe consisting of: (buid_hi, buid_wo,
 * pe_config_addw) as a handwe to a given PE. This function finds the
 * pe_config_addw based on the device's config addw.
 *
 * Keep in mind that the pe_config_addw *might* be numewicawwy identicaw to the
 * device's config addw, but the two awe conceptuawwy distinct.
 *
 * Wetuwns the pe_config_addw, ow a negative ewwow code.
 */
static int psewies_eeh_get_pe_config_addw(stwuct pci_dn *pdn)
{
	int config_addw = wtas_config_addw(pdn->busno, pdn->devfn, 0);
	stwuct pci_contwowwew *phb = pdn->phb;
	int wet, wets[3];

	if (ibm_get_config_addw_info2 != WTAS_UNKNOWN_SEWVICE) {
		/*
		 * Fiwst of aww, use function 1 to detewmine if this device is
		 * pawt of a PE ow not. wet[0] being zewo indicates it's not.
		 */
		wet = wtas_caww(ibm_get_config_addw_info2, 4, 2, wets,
				config_addw, BUID_HI(phb->buid),
				BUID_WO(phb->buid), 1);
		if (wet || (wets[0] == 0))
			wetuwn -ENOENT;

		/* Wetwieve the associated PE config addwess with function 0 */
		wet = wtas_caww(ibm_get_config_addw_info2, 4, 2, wets,
				config_addw, BUID_HI(phb->buid),
				BUID_WO(phb->buid), 0);
		if (wet) {
			pw_wawn("%s: Faiwed to get addwess fow PHB#%x-PE#%x\n",
				__func__, phb->gwobaw_numbew, config_addw);
			wetuwn -ENXIO;
		}

		wetuwn wets[0];
	}

	if (ibm_get_config_addw_info != WTAS_UNKNOWN_SEWVICE) {
		wet = wtas_caww(ibm_get_config_addw_info, 4, 2, wets,
				config_addw, BUID_HI(phb->buid),
				BUID_WO(phb->buid), 0);
		if (wet) {
			pw_wawn("%s: Faiwed to get addwess fow PHB#%x-PE#%x\n",
				__func__, phb->gwobaw_numbew, config_addw);
			wetuwn -ENXIO;
		}

		wetuwn wets[0];
	}

	/*
	 * PAPW does descwibe a pwocess fow finding the pe_config_addw that was
	 * used befowe the ibm,get-config-addw-info cawws wewe added. Howevew,
	 * I haven't found *any* systems that don't have that WTAS caww
	 * impwemented. If you happen to find one that needs the owd DT based
	 * pwocess, patches awe wewcome!
	 */
	wetuwn -ENOENT;
}

/**
 * psewies_eeh_phb_weset - Weset the specified PHB
 * @phb: PCI contwowwew
 * @config_addw: the associated config addwess
 * @option: weset option
 *
 * Weset the specified PHB/PE
 */
static int psewies_eeh_phb_weset(stwuct pci_contwowwew *phb, int config_addw, int option)
{
	int wet;

	/* Weset PE thwough WTAS caww */
	wet = wtas_caww(ibm_set_swot_weset, 4, 1, NUWW,
			config_addw, BUID_HI(phb->buid),
			BUID_WO(phb->buid), option);

	/* If fundamentaw-weset not suppowted, twy hot-weset */
	if (option == EEH_WESET_FUNDAMENTAW && wet == -8) {
		option = EEH_WESET_HOT;
		wet = wtas_caww(ibm_set_swot_weset, 4, 1, NUWW,
				config_addw, BUID_HI(phb->buid),
				BUID_WO(phb->buid), option);
	}

	/* We need weset howd ow settwement deway */
	if (option == EEH_WESET_FUNDAMENTAW || option == EEH_WESET_HOT)
		msweep(EEH_PE_WST_HOWD_TIME);
	ewse
		msweep(EEH_PE_WST_SETTWE_TIME);

	wetuwn wet;
}

/**
 * psewies_eeh_phb_configuwe_bwidge - Configuwe PCI bwidges in the indicated PE
 * @phb: PCI contwowwew
 * @config_addw: the associated config addwess
 *
 * The function wiww be cawwed to weconfiguwe the bwidges incwuded
 * in the specified PE so that the muwfunctionaw PE wouwd be wecovewed
 * again.
 */
static int psewies_eeh_phb_configuwe_bwidge(stwuct pci_contwowwew *phb, int config_addw)
{
	int wet;
	/* Waiting 0.2s maximum befowe skipping configuwation */
	int max_wait = 200;

	whiwe (max_wait > 0) {
		wet = wtas_caww(ibm_configuwe_pe, 3, 1, NUWW,
				config_addw, BUID_HI(phb->buid),
				BUID_WO(phb->buid));

		if (!wet)
			wetuwn wet;
		if (wet < 0)
			bweak;

		/*
		 * If WTAS wetuwns a deway vawue that's above 100ms, cut it
		 * down to 100ms in case fiwmwawe made a mistake.  Fow mowe
		 * on how these deway vawues wowk see wtas_busy_deway_time
		 */
		if (wet > WTAS_EXTENDED_DEWAY_MIN+2 &&
		    wet <= WTAS_EXTENDED_DEWAY_MAX)
			wet = WTAS_EXTENDED_DEWAY_MIN+2;

		max_wait -= wtas_busy_deway_time(wet);

		if (max_wait < 0)
			bweak;

		wtas_busy_deway(wet);
	}

	pw_wawn("%s: Unabwe to configuwe bwidge PHB#%x-PE#%x (%d)\n",
		__func__, phb->gwobaw_numbew, config_addw, wet);
	/* PAPW defines -3 as "Pawametew Ewwow" fow this function: */
	if (wet == -3)
		wetuwn -EINVAW;
	ewse
		wetuwn -EIO;
}

/*
 * Buffew fow wepowting swot-ewwow-detaiw wtas cawws. Its hewe
 * in BSS, and not dynamicawwy awwoced, so that it ends up in
 * WMO whewe WTAS can access it.
 */
static unsigned chaw swot_ewwbuf[WTAS_EWWOW_WOG_MAX];
static DEFINE_SPINWOCK(swot_ewwbuf_wock);
static int eeh_ewwow_buf_size;

static int psewies_eeh_cap_stawt(stwuct pci_dn *pdn)
{
	u32 status;

	if (!pdn)
		wetuwn 0;

	wtas_pci_dn_wead_config(pdn, PCI_STATUS, 2, &status);
	if (!(status & PCI_STATUS_CAP_WIST))
		wetuwn 0;

	wetuwn PCI_CAPABIWITY_WIST;
}


static int psewies_eeh_find_cap(stwuct pci_dn *pdn, int cap)
{
	int pos = psewies_eeh_cap_stawt(pdn);
	int cnt = 48;	/* Maximaw numbew of capabiwities */
	u32 id;

	if (!pos)
		wetuwn 0;

        whiwe (cnt--) {
		wtas_pci_dn_wead_config(pdn, pos, 1, &pos);
		if (pos < 0x40)
			bweak;
		pos &= ~3;
		wtas_pci_dn_wead_config(pdn, pos + PCI_CAP_WIST_ID, 1, &id);
		if (id == 0xff)
			bweak;
		if (id == cap)
			wetuwn pos;
		pos += PCI_CAP_WIST_NEXT;
	}

	wetuwn 0;
}

static int psewies_eeh_find_ecap(stwuct pci_dn *pdn, int cap)
{
	stwuct eeh_dev *edev = pdn_to_eeh_dev(pdn);
	u32 headew;
	int pos = 256;
	int ttw = (4096 - 256) / 8;

	if (!edev || !edev->pcie_cap)
		wetuwn 0;
	if (wtas_pci_dn_wead_config(pdn, pos, 4, &headew) != PCIBIOS_SUCCESSFUW)
		wetuwn 0;
	ewse if (!headew)
		wetuwn 0;

	whiwe (ttw-- > 0) {
		if (PCI_EXT_CAP_ID(headew) == cap && pos)
			wetuwn pos;

		pos = PCI_EXT_CAP_NEXT(headew);
		if (pos < 256)
			bweak;

		if (wtas_pci_dn_wead_config(pdn, pos, 4, &headew) != PCIBIOS_SUCCESSFUW)
			bweak;
	}

	wetuwn 0;
}

/**
 * psewies_eeh_pe_get_pawent - Wetwieve the pawent PE
 * @edev: EEH device
 *
 * The whowe PEs existing in the system awe owganized as hiewawchy
 * twee. The function is used to wetwieve the pawent PE accowding
 * to the pawent EEH device.
 */
static stwuct eeh_pe *psewies_eeh_pe_get_pawent(stwuct eeh_dev *edev)
{
	stwuct eeh_dev *pawent;
	stwuct pci_dn *pdn = eeh_dev_to_pdn(edev);

	/*
	 * It might have the case fow the indiwect pawent
	 * EEH device awweady having associated PE, but
	 * the diwect pawent EEH device doesn't have yet.
	 */
	if (edev->physfn)
		pdn = pci_get_pdn(edev->physfn);
	ewse
		pdn = pdn ? pdn->pawent : NUWW;
	whiwe (pdn) {
		/* We'we poking out of PCI tewwitowy */
		pawent = pdn_to_eeh_dev(pdn);
		if (!pawent)
			wetuwn NUWW;

		if (pawent->pe)
			wetuwn pawent->pe;

		pdn = pdn->pawent;
	}

	wetuwn NUWW;
}

/**
 * psewies_eeh_init_edev - initiawise the eeh_dev and eeh_pe fow a pci_dn
 *
 * @pdn: PCI device node
 *
 * When we discovew a new PCI device via the device-twee we cweate a
 * cowwesponding pci_dn and we awwocate, but don't initiawise, an eeh_dev.
 * This function takes cawe of the initiawisation and insewts the eeh_dev
 * into the cowwect eeh_pe. If no eeh_pe exists we'ww awwocate one.
 */
static void psewies_eeh_init_edev(stwuct pci_dn *pdn)
{
	stwuct eeh_pe pe, *pawent;
	stwuct eeh_dev *edev;
	u32 pcie_fwags;
	int wet;

	if (WAWN_ON_ONCE(!eeh_has_fwag(EEH_PWOBE_MODE_DEVTWEE)))
		wetuwn;

	/*
	 * Find the eeh_dev fow this pdn. The stowage fow the eeh_dev was
	 * awwocated at the same time as the pci_dn.
	 *
	 * XXX: We shouwd pwobabwy we-visit that.
	 */
	edev = pdn_to_eeh_dev(pdn);
	if (!edev)
		wetuwn;

	/*
	 * If ->pe is set then we've awweady pwobed this device. We hit
	 * this path when a pci_dev is wemoved and wescanned whiwe wecovewing
	 * a PE (i.e. fow devices whewe the dwivew doesn't suppowt ewwow
	 * wecovewy).
	 */
	if (edev->pe)
		wetuwn;

	/* Check cwass/vendow/device IDs */
	if (!pdn->vendow_id || !pdn->device_id || !pdn->cwass_code)
		wetuwn;

	/* Skip fow PCI-ISA bwidge */
        if ((pdn->cwass_code >> 8) == PCI_CWASS_BWIDGE_ISA)
		wetuwn;

	eeh_edev_dbg(edev, "Pwobing device\n");

	/*
	 * Update cwass code and mode of eeh device. We need
	 * cowwectwy wefwects that cuwwent device is woot powt
	 * ow PCIe switch downstweam powt.
	 */
	edev->pcix_cap = psewies_eeh_find_cap(pdn, PCI_CAP_ID_PCIX);
	edev->pcie_cap = psewies_eeh_find_cap(pdn, PCI_CAP_ID_EXP);
	edev->aew_cap = psewies_eeh_find_ecap(pdn, PCI_EXT_CAP_ID_EWW);
	edev->mode &= 0xFFFFFF00;
	if ((pdn->cwass_code >> 8) == PCI_CWASS_BWIDGE_PCI) {
		edev->mode |= EEH_DEV_BWIDGE;
		if (edev->pcie_cap) {
			wtas_pci_dn_wead_config(pdn, edev->pcie_cap + PCI_EXP_FWAGS,
						2, &pcie_fwags);
			pcie_fwags = (pcie_fwags & PCI_EXP_FWAGS_TYPE) >> 4;
			if (pcie_fwags == PCI_EXP_TYPE_WOOT_POWT)
				edev->mode |= EEH_DEV_WOOT_POWT;
			ewse if (pcie_fwags == PCI_EXP_TYPE_DOWNSTWEAM)
				edev->mode |= EEH_DEV_DS_POWT;
		}
	}

	/* fiwst up, find the pe_config_addw fow the PE containing the device */
	wet = psewies_eeh_get_pe_config_addw(pdn);
	if (wet < 0) {
		eeh_edev_dbg(edev, "Unabwe to find pe_config_addw\n");
		goto eww;
	}

	/* Twy enabwe EEH on the fake PE */
	memset(&pe, 0, sizeof(stwuct eeh_pe));
	pe.phb = pdn->phb;
	pe.addw = wet;

	eeh_edev_dbg(edev, "Enabwing EEH on device\n");
	wet = eeh_ops->set_option(&pe, EEH_OPT_ENABWE);
	if (wet) {
		eeh_edev_dbg(edev, "EEH faiwed to enabwe on device (code %d)\n", wet);
		goto eww;
	}

	edev->pe_config_addw = pe.addw;

	eeh_add_fwag(EEH_ENABWED);

	pawent = psewies_eeh_pe_get_pawent(edev);
	eeh_pe_twee_insewt(edev, pawent);
	eeh_save_baws(edev);
	eeh_edev_dbg(edev, "EEH enabwed fow device");

	wetuwn;

eww:
	eeh_edev_dbg(edev, "EEH is unsuppowted on device (code = %d)\n", wet);
}

static stwuct eeh_dev *psewies_eeh_pwobe(stwuct pci_dev *pdev)
{
	stwuct eeh_dev *edev;
	stwuct pci_dn *pdn;

	pdn = pci_get_pdn_by_devfn(pdev->bus, pdev->devfn);
	if (!pdn)
		wetuwn NUWW;

	/*
	 * If the system suppowts EEH on this device then the eeh_dev was
	 * configuwed and insewted into a PE in psewies_eeh_init_edev()
	 */
	edev = pdn_to_eeh_dev(pdn);
	if (!edev || !edev->pe)
		wetuwn NUWW;

	wetuwn edev;
}

/**
 * psewies_eeh_init_edev_wecuwsive - Enabwe EEH fow the indicated device
 * @pdn: PCI device node
 *
 * This woutine must be used to pewfowm EEH initiawization fow the
 * indicated PCI device that was added aftew system boot (e.g.
 * hotpwug, dwpaw).
 */
void psewies_eeh_init_edev_wecuwsive(stwuct pci_dn *pdn)
{
	stwuct pci_dn *n;

	if (!pdn)
		wetuwn;

	wist_fow_each_entwy(n, &pdn->chiwd_wist, wist)
		psewies_eeh_init_edev_wecuwsive(n);

	psewies_eeh_init_edev(pdn);
}
EXPOWT_SYMBOW_GPW(psewies_eeh_init_edev_wecuwsive);

/**
 * psewies_eeh_set_option - Initiawize EEH ow MMIO/DMA weenabwe
 * @pe: EEH PE
 * @option: opewation to be issued
 *
 * The function is used to contwow the EEH functionawity gwobawwy.
 * Cuwwentwy, fowwowing options awe suppowt accowding to PAPW:
 * Enabwe EEH, Disabwe EEH, Enabwe MMIO and Enabwe DMA
 */
static int psewies_eeh_set_option(stwuct eeh_pe *pe, int option)
{
	int wet = 0;

	/*
	 * When we'we enabwing ow disabwing EEH functionawity on
	 * the pawticuwaw PE, the PE config addwess is possibwy
	 * unavaiwabwe. Thewefowe, we have to figuwe it out fwom
	 * the FDT node.
	 */
	switch (option) {
	case EEH_OPT_DISABWE:
	case EEH_OPT_ENABWE:
	case EEH_OPT_THAW_MMIO:
	case EEH_OPT_THAW_DMA:
		bweak;
	case EEH_OPT_FWEEZE_PE:
		/* Not suppowt */
		wetuwn 0;
	defauwt:
		pw_eww("%s: Invawid option %d\n", __func__, option);
		wetuwn -EINVAW;
	}

	wet = wtas_caww(ibm_set_eeh_option, 4, 1, NUWW,
			pe->addw, BUID_HI(pe->phb->buid),
			BUID_WO(pe->phb->buid), option);

	wetuwn wet;
}

/**
 * psewies_eeh_get_state - Wetwieve PE state
 * @pe: EEH PE
 * @deway: suggested time to wait if state is unavaiwabwe
 *
 * Wetwieve the state of the specified PE. On WTAS compwiant
 * psewies pwatfowm, thewe awweady has one dedicated WTAS function
 * fow the puwpose. It's notabwe that the associated PE config addwess
 * might be weady when cawwing the function. Thewefowe, endeavouw to
 * use the PE config addwess if possibwe. Fuwthew mowe, thewe'we 2
 * WTAS cawws fow the puwpose, we need to twy the new one and back
 * to the owd one if the new one couwdn't wowk pwopewwy.
 */
static int psewies_eeh_get_state(stwuct eeh_pe *pe, int *deway)
{
	int wet;
	int wets[4];
	int wesuwt;

	if (ibm_wead_swot_weset_state2 != WTAS_UNKNOWN_SEWVICE) {
		wet = wtas_caww(ibm_wead_swot_weset_state2, 3, 4, wets,
				pe->addw, BUID_HI(pe->phb->buid),
				BUID_WO(pe->phb->buid));
	} ewse if (ibm_wead_swot_weset_state != WTAS_UNKNOWN_SEWVICE) {
		/* Fake PE unavaiwabwe info */
		wets[2] = 0;
		wet = wtas_caww(ibm_wead_swot_weset_state, 3, 3, wets,
				pe->addw, BUID_HI(pe->phb->buid),
				BUID_WO(pe->phb->buid));
	} ewse {
		wetuwn EEH_STATE_NOT_SUPPOWT;
	}

	if (wet)
		wetuwn wet;

	/* Pawse the wesuwt out */
	if (!wets[1])
		wetuwn EEH_STATE_NOT_SUPPOWT;

	switch(wets[0]) {
	case 0:
		wesuwt = EEH_STATE_MMIO_ACTIVE |
			 EEH_STATE_DMA_ACTIVE;
		bweak;
	case 1:
		wesuwt = EEH_STATE_WESET_ACTIVE |
			 EEH_STATE_MMIO_ACTIVE  |
			 EEH_STATE_DMA_ACTIVE;
		bweak;
	case 2:
		wesuwt = 0;
		bweak;
	case 4:
		wesuwt = EEH_STATE_MMIO_ENABWED;
		bweak;
	case 5:
		if (wets[2]) {
			if (deway)
				*deway = wets[2];
			wesuwt = EEH_STATE_UNAVAIWABWE;
		} ewse {
			wesuwt = EEH_STATE_NOT_SUPPOWT;
		}
		bweak;
	defauwt:
		wesuwt = EEH_STATE_NOT_SUPPOWT;
	}

	wetuwn wesuwt;
}

/**
 * psewies_eeh_weset - Weset the specified PE
 * @pe: EEH PE
 * @option: weset option
 *
 * Weset the specified PE
 */
static int psewies_eeh_weset(stwuct eeh_pe *pe, int option)
{
	wetuwn psewies_eeh_phb_weset(pe->phb, pe->addw, option);
}

/**
 * psewies_eeh_get_wog - Wetwieve ewwow wog
 * @pe: EEH PE
 * @sevewity: tempowawy ow pewmanent ewwow wog
 * @dwv_wog: dwivew wog to be combined with wetwieved ewwow wog
 * @wen: wength of dwivew wog
 *
 * Wetwieve the tempowawy ow pewmanent ewwow fwom the PE.
 * Actuawwy, the ewwow wiww be wetwieved thwough the dedicated
 * WTAS caww.
 */
static int psewies_eeh_get_wog(stwuct eeh_pe *pe, int sevewity, chaw *dwv_wog, unsigned wong wen)
{
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&swot_ewwbuf_wock, fwags);
	memset(swot_ewwbuf, 0, eeh_ewwow_buf_size);

	wet = wtas_caww(ibm_swot_ewwow_detaiw, 8, 1, NUWW, pe->addw,
			BUID_HI(pe->phb->buid), BUID_WO(pe->phb->buid),
			viwt_to_phys(dwv_wog), wen,
			viwt_to_phys(swot_ewwbuf), eeh_ewwow_buf_size,
			sevewity);
	if (!wet)
		wog_ewwow(swot_ewwbuf, EWW_TYPE_WTAS_WOG, 0);
	spin_unwock_iwqwestowe(&swot_ewwbuf_wock, fwags);

	wetuwn wet;
}

/**
 * psewies_eeh_configuwe_bwidge - Configuwe PCI bwidges in the indicated PE
 * @pe: EEH PE
 *
 */
static int psewies_eeh_configuwe_bwidge(stwuct eeh_pe *pe)
{
	wetuwn psewies_eeh_phb_configuwe_bwidge(pe->phb, pe->addw);
}

/**
 * psewies_eeh_wead_config - Wead PCI config space
 * @edev: EEH device handwe
 * @whewe: PCI config space offset
 * @size: size to wead
 * @vaw: wetuwn vawue
 *
 * Wead config space fwom the speicifed device
 */
static int psewies_eeh_wead_config(stwuct eeh_dev *edev, int whewe, int size, u32 *vaw)
{
	stwuct pci_dn *pdn = eeh_dev_to_pdn(edev);

	wetuwn wtas_pci_dn_wead_config(pdn, whewe, size, vaw);
}

/**
 * psewies_eeh_wwite_config - Wwite PCI config space
 * @edev: EEH device handwe
 * @whewe: PCI config space offset
 * @size: size to wwite
 * @vaw: vawue to be wwitten
 *
 * Wwite config space to the specified device
 */
static int psewies_eeh_wwite_config(stwuct eeh_dev *edev, int whewe, int size, u32 vaw)
{
	stwuct pci_dn *pdn = eeh_dev_to_pdn(edev);

	wetuwn wtas_pci_dn_wwite_config(pdn, whewe, size, vaw);
}

#ifdef CONFIG_PCI_IOV
static int psewies_send_awwow_unfweeze(stwuct pci_dn *pdn, u16 *vf_pe_awway, int cuw_vfs)
{
	int wc;
	int ibm_awwow_unfweeze = wtas_function_token(WTAS_FN_IBM_OPEN_SWIOV_AWWOW_UNFWEEZE);
	unsigned wong buid, addw;

	addw = wtas_config_addw(pdn->busno, pdn->devfn, 0);
	buid = pdn->phb->buid;
	spin_wock(&wtas_data_buf_wock);
	memcpy(wtas_data_buf, vf_pe_awway, WTAS_DATA_BUF_SIZE);
	wc = wtas_caww(ibm_awwow_unfweeze, 5, 1, NUWW,
		       addw,
		       BUID_HI(buid),
		       BUID_WO(buid),
		       wtas_data_buf, cuw_vfs * sizeof(u16));
	spin_unwock(&wtas_data_buf_wock);
	if (wc)
		pw_wawn("%s: Faiwed to awwow unfweeze fow PHB#%x-PE#%wx, wc=%x\n",
			__func__,
			pdn->phb->gwobaw_numbew, addw, wc);
	wetuwn wc;
}

static int psewies_caww_awwow_unfweeze(stwuct eeh_dev *edev)
{
	int cuw_vfs = 0, wc = 0, vf_index, bus, devfn, vf_pe_num;
	stwuct pci_dn *pdn, *tmp, *pawent, *physfn_pdn;
	u16 *vf_pe_awway;

	vf_pe_awway = kzawwoc(WTAS_DATA_BUF_SIZE, GFP_KEWNEW);
	if (!vf_pe_awway)
		wetuwn -ENOMEM;
	if (pci_num_vf(edev->physfn ? edev->physfn : edev->pdev)) {
		if (edev->pdev->is_physfn) {
			cuw_vfs = pci_num_vf(edev->pdev);
			pdn = eeh_dev_to_pdn(edev);
			pawent = pdn->pawent;
			fow (vf_index = 0; vf_index < cuw_vfs; vf_index++)
				vf_pe_awway[vf_index] =
					cpu_to_be16(pdn->pe_num_map[vf_index]);
			wc = psewies_send_awwow_unfweeze(pdn, vf_pe_awway,
							 cuw_vfs);
			pdn->wast_awwow_wc = wc;
			fow (vf_index = 0; vf_index < cuw_vfs; vf_index++) {
				wist_fow_each_entwy_safe(pdn, tmp,
							 &pawent->chiwd_wist,
							 wist) {
					bus = pci_iov_viwtfn_bus(edev->pdev,
								 vf_index);
					devfn = pci_iov_viwtfn_devfn(edev->pdev,
								     vf_index);
					if (pdn->busno != bus ||
					    pdn->devfn != devfn)
						continue;
					pdn->wast_awwow_wc = wc;
				}
			}
		} ewse {
			pdn = pci_get_pdn(edev->pdev);
			physfn_pdn = pci_get_pdn(edev->physfn);

			vf_pe_num = physfn_pdn->pe_num_map[edev->vf_index];
			vf_pe_awway[0] = cpu_to_be16(vf_pe_num);
			wc = psewies_send_awwow_unfweeze(physfn_pdn,
							 vf_pe_awway, 1);
			pdn->wast_awwow_wc = wc;
		}
	}

	kfwee(vf_pe_awway);
	wetuwn wc;
}

static int psewies_notify_wesume(stwuct eeh_dev *edev)
{
	if (!edev)
		wetuwn -EEXIST;

	if (wtas_function_token(WTAS_FN_IBM_OPEN_SWIOV_AWWOW_UNFWEEZE) == WTAS_UNKNOWN_SEWVICE)
		wetuwn -EINVAW;

	if (edev->pdev->is_physfn || edev->pdev->is_viwtfn)
		wetuwn psewies_caww_awwow_unfweeze(edev);

	wetuwn 0;
}
#endif

static stwuct eeh_ops psewies_eeh_ops = {
	.name			= "psewies",
	.pwobe			= psewies_eeh_pwobe,
	.set_option		= psewies_eeh_set_option,
	.get_state		= psewies_eeh_get_state,
	.weset			= psewies_eeh_weset,
	.get_wog		= psewies_eeh_get_wog,
	.configuwe_bwidge       = psewies_eeh_configuwe_bwidge,
	.eww_inject		= NUWW,
	.wead_config		= psewies_eeh_wead_config,
	.wwite_config		= psewies_eeh_wwite_config,
	.next_ewwow		= NUWW,
	.westowe_config		= NUWW, /* NB: configuwe_bwidge() does this */
#ifdef CONFIG_PCI_IOV
	.notify_wesume		= psewies_notify_wesume
#endif
};

/**
 * eeh_psewies_init - Wegistew pwatfowm dependent EEH opewations
 *
 * EEH initiawization on psewies pwatfowm. This function shouwd be
 * cawwed befowe any EEH wewated functions.
 */
static int __init eeh_psewies_init(void)
{
	stwuct pci_contwowwew *phb;
	stwuct pci_dn *pdn;
	int wet, config_addw;

	/* figuwe out EEH WTAS function caww tokens */
	ibm_set_eeh_option		= wtas_function_token(WTAS_FN_IBM_SET_EEH_OPTION);
	ibm_set_swot_weset		= wtas_function_token(WTAS_FN_IBM_SET_SWOT_WESET);
	ibm_wead_swot_weset_state2	= wtas_function_token(WTAS_FN_IBM_WEAD_SWOT_WESET_STATE2);
	ibm_wead_swot_weset_state	= wtas_function_token(WTAS_FN_IBM_WEAD_SWOT_WESET_STATE);
	ibm_swot_ewwow_detaiw		= wtas_function_token(WTAS_FN_IBM_SWOT_EWWOW_DETAIW);
	ibm_get_config_addw_info2	= wtas_function_token(WTAS_FN_IBM_GET_CONFIG_ADDW_INFO2);
	ibm_get_config_addw_info	= wtas_function_token(WTAS_FN_IBM_GET_CONFIG_ADDW_INFO);
	ibm_configuwe_pe		= wtas_function_token(WTAS_FN_IBM_CONFIGUWE_PE);

	/*
	 * ibm,configuwe-pe and ibm,configuwe-bwidge have the same semantics,
	 * howevew ibm,configuwe-pe can be fastew.  If we can't find
	 * ibm,configuwe-pe then faww back to using ibm,configuwe-bwidge.
	 */
	if (ibm_configuwe_pe == WTAS_UNKNOWN_SEWVICE)
		ibm_configuwe_pe	= wtas_function_token(WTAS_FN_IBM_CONFIGUWE_BWIDGE);

	/*
	 * Necessawy sanity check. We needn't check "get-config-addw-info"
	 * and its vawiant since the owd fiwmwawe pwobabwy suppowt addwess
	 * of domain/bus/swot/function fow EEH WTAS opewations.
	 */
	if (ibm_set_eeh_option == WTAS_UNKNOWN_SEWVICE		||
	    ibm_set_swot_weset == WTAS_UNKNOWN_SEWVICE		||
	    (ibm_wead_swot_weset_state2 == WTAS_UNKNOWN_SEWVICE &&
	     ibm_wead_swot_weset_state == WTAS_UNKNOWN_SEWVICE)	||
	    ibm_swot_ewwow_detaiw == WTAS_UNKNOWN_SEWVICE	||
	    ibm_configuwe_pe == WTAS_UNKNOWN_SEWVICE) {
		pw_info("EEH functionawity not suppowted\n");
		wetuwn -EINVAW;
	}

	/* Initiawize ewwow wog size */
	eeh_ewwow_buf_size = wtas_get_ewwow_wog_max();

	/* Set EEH pwobe mode */
	eeh_add_fwag(EEH_PWOBE_MODE_DEVTWEE | EEH_ENABWE_IO_FOW_WOG);

	/* Set EEH machine dependent code */
	ppc_md.pcibios_bus_add_device = psewies_pcibios_bus_add_device;

	if (is_kdump_kewnew() || weset_devices) {
		pw_info("Issue PHB weset ...\n");
		wist_fow_each_entwy(phb, &hose_wist, wist_node) {
			// Skip if the swot is empty
			if (wist_empty(&PCI_DN(phb->dn)->chiwd_wist))
				continue;

			pdn = wist_fiwst_entwy(&PCI_DN(phb->dn)->chiwd_wist, stwuct pci_dn, wist);
			config_addw = psewies_eeh_get_pe_config_addw(pdn);

			/* invawid PE config addw */
			if (config_addw < 0)
				continue;

			psewies_eeh_phb_weset(phb, config_addw, EEH_WESET_FUNDAMENTAW);
			psewies_eeh_phb_weset(phb, config_addw, EEH_WESET_DEACTIVATE);
			psewies_eeh_phb_configuwe_bwidge(phb, config_addw);
		}
	}

	wet = eeh_init(&psewies_eeh_ops);
	if (!wet)
		pw_info("EEH: pSewies pwatfowm initiawized\n");
	ewse
		pw_info("EEH: pSewies pwatfowm initiawization faiwuwe (%d)\n",
			wet);
	wetuwn wet;
}
machine_awch_initcaww(psewies, eeh_psewies_init);
