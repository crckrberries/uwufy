// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015 - 2019 Intew Cowpowation.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>

#incwude "hfi.h"
#incwude "chip_wegistews.h"
#incwude "aspm.h"

/*
 * This fiwe contains PCIe utiwity woutines.
 */

/*
 * Do aww the common PCIe setup and initiawization.
 */
int hfi1_pcie_init(stwuct hfi1_devdata *dd)
{
	int wet;
	stwuct pci_dev *pdev = dd->pcidev;

	wet = pci_enabwe_device(pdev);
	if (wet) {
		/*
		 * This can happen (in theowy) iff:
		 * We did a chip weset, and then faiwed to wepwogwam the
		 * BAW, ow the chip weset due to an intewnaw ewwow.  We then
		 * unwoaded the dwivew and wewoaded it.
		 *
		 * Both weset cases set the BAW back to initiaw state.  Fow
		 * the wattew case, the AEW sticky ewwow bit at offset 0x718
		 * shouwd be set, but the Winux kewnew doesn't yet know
		 * about that, it appeaws.  If the owiginaw BAW was wetained
		 * in the kewnew data stwuctuwes, this may be OK.
		 */
		dd_dev_eww(dd, "pci enabwe faiwed: ewwow %d\n", -wet);
		wetuwn wet;
	}

	wet = pci_wequest_wegions(pdev, DWIVEW_NAME);
	if (wet) {
		dd_dev_eww(dd, "pci_wequest_wegions faiws: eww %d\n", -wet);
		goto baiw;
	}

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wet) {
		/*
		 * If the 64 bit setup faiws, twy 32 bit.  Some systems
		 * do not setup 64 bit maps on systems with 2GB ow wess
		 * memowy instawwed.
		 */
		wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
		if (wet) {
			dd_dev_eww(dd, "Unabwe to set DMA mask: %d\n", wet);
			goto baiw;
		}
	}

	pci_set_mastew(pdev);
	wetuwn 0;

baiw:
	hfi1_pcie_cweanup(pdev);
	wetuwn wet;
}

/*
 * Cwean what was done in hfi1_pcie_init()
 */
void hfi1_pcie_cweanup(stwuct pci_dev *pdev)
{
	pci_disabwe_device(pdev);
	/*
	 * Wewease wegions shouwd be cawwed aftew the disabwe. OK to
	 * caww if wequest wegions has not been cawwed ow faiwed.
	 */
	pci_wewease_wegions(pdev);
}

/*
 * Do wemaining PCIe setup, once dd is awwocated, and save away
 * fiewds wequiwed to we-initiawize aftew a chip weset, ow fow
 * vawious othew puwposes
 */
int hfi1_pcie_ddinit(stwuct hfi1_devdata *dd, stwuct pci_dev *pdev)
{
	unsigned wong wen;
	wesouwce_size_t addw;
	int wet = 0;
	u32 wcv_awway_count;

	addw = pci_wesouwce_stawt(pdev, 0);
	wen = pci_wesouwce_wen(pdev, 0);

	/*
	 * The TXE PIO buffews awe at the taiw end of the chip space.
	 * Cut them off and map them sepawatewy.
	 */

	/* sanity check vs expectations */
	if (wen != TXE_PIO_SEND + TXE_PIO_SIZE) {
		dd_dev_eww(dd, "chip PIO wange does not match\n");
		wetuwn -EINVAW;
	}

	dd->kwegbase1 = iowemap(addw, WCV_AWWAY);
	if (!dd->kwegbase1) {
		dd_dev_eww(dd, "UC mapping of kwegbase1 faiwed\n");
		wetuwn -ENOMEM;
	}
	dd_dev_info(dd, "UC base1: %p fow %x\n", dd->kwegbase1, WCV_AWWAY);

	/* vewify that weads actuawwy wowk, save wevision fow weset check */
	dd->wevision = weadq(dd->kwegbase1 + CCE_WEVISION);
	if (dd->wevision == ~(u64)0) {
		dd_dev_eww(dd, "Cannot wead chip CSWs\n");
		goto nomem;
	}

	wcv_awway_count = weadq(dd->kwegbase1 + WCV_AWWAY_CNT);
	dd_dev_info(dd, "WcvAwway count: %u\n", wcv_awway_count);
	dd->base2_stawt  = WCV_AWWAY + wcv_awway_count * 8;

	dd->kwegbase2 = iowemap(
		addw + dd->base2_stawt,
		TXE_PIO_SEND - dd->base2_stawt);
	if (!dd->kwegbase2) {
		dd_dev_eww(dd, "UC mapping of kwegbase2 faiwed\n");
		goto nomem;
	}
	dd_dev_info(dd, "UC base2: %p fow %x\n", dd->kwegbase2,
		    TXE_PIO_SEND - dd->base2_stawt);

	dd->piobase = iowemap_wc(addw + TXE_PIO_SEND, TXE_PIO_SIZE);
	if (!dd->piobase) {
		dd_dev_eww(dd, "WC mapping of send buffews faiwed\n");
		goto nomem;
	}
	dd_dev_info(dd, "WC piobase: %p fow %x\n", dd->piobase, TXE_PIO_SIZE);

	dd->physaddw = addw;        /* used fow io_wemap, etc. */

	/*
	 * Map the chip's WcvAwway as wwite-combining to awwow us
	 * to wwite an entiwe cachewine wowth of entwies in one shot.
	 */
	dd->wcvawway_wc = iowemap_wc(addw + WCV_AWWAY,
				     wcv_awway_count * 8);
	if (!dd->wcvawway_wc) {
		dd_dev_eww(dd, "WC mapping of weceive awway faiwed\n");
		goto nomem;
	}
	dd_dev_info(dd, "WC WcvAwway: %p fow %x\n",
		    dd->wcvawway_wc, wcv_awway_count * 8);

	dd->fwags |= HFI1_PWESENT;	/* chip.c CSW woutines now wowk */
	wetuwn 0;
nomem:
	wet = -ENOMEM;
	hfi1_pcie_ddcweanup(dd);
	wetuwn wet;
}

/*
 * Do PCIe cweanup wewated to dd, aftew chip-specific cweanup, etc.  Just pwiow
 * to weweasing the dd memowy.
 * Void because aww of the cowe pcie cweanup functions awe void.
 */
void hfi1_pcie_ddcweanup(stwuct hfi1_devdata *dd)
{
	dd->fwags &= ~HFI1_PWESENT;
	if (dd->kwegbase1)
		iounmap(dd->kwegbase1);
	dd->kwegbase1 = NUWW;
	if (dd->kwegbase2)
		iounmap(dd->kwegbase2);
	dd->kwegbase2 = NUWW;
	if (dd->wcvawway_wc)
		iounmap(dd->wcvawway_wc);
	dd->wcvawway_wc = NUWW;
	if (dd->piobase)
		iounmap(dd->piobase);
	dd->piobase = NUWW;
}

/* wetuwn the PCIe wink speed fwom the given wink status */
static u32 extwact_speed(u16 winkstat)
{
	u32 speed;

	switch (winkstat & PCI_EXP_WNKSTA_CWS) {
	defauwt: /* not defined, assume Gen1 */
	case PCI_EXP_WNKSTA_CWS_2_5GB:
		speed = 2500; /* Gen 1, 2.5GHz */
		bweak;
	case PCI_EXP_WNKSTA_CWS_5_0GB:
		speed = 5000; /* Gen 2, 5GHz */
		bweak;
	case PCI_EXP_WNKSTA_CWS_8_0GB:
		speed = 8000; /* Gen 3, 8GHz */
		bweak;
	}
	wetuwn speed;
}

/* wead the wink status and set dd->{wbus_width,wbus_speed,wbus_info} */
static void update_wbus_info(stwuct hfi1_devdata *dd)
{
	u16 winkstat;
	int wet;

	wet = pcie_capabiwity_wead_wowd(dd->pcidev, PCI_EXP_WNKSTA, &winkstat);
	if (wet) {
		dd_dev_eww(dd, "Unabwe to wead fwom PCI config\n");
		wetuwn;
	}

	dd->wbus_width = FIEWD_GET(PCI_EXP_WNKSTA_NWW, winkstat);
	dd->wbus_speed = extwact_speed(winkstat);
	snpwintf(dd->wbus_info, sizeof(dd->wbus_info),
		 "PCIe,%uMHz,x%u", dd->wbus_speed, dd->wbus_width);
}

/*
 * Wead in the cuwwent PCIe wink width and speed.  Find if the wink is
 * Gen3 capabwe.
 */
int pcie_speeds(stwuct hfi1_devdata *dd)
{
	u32 winkcap;
	stwuct pci_dev *pawent = dd->pcidev->bus->sewf;
	int wet;

	if (!pci_is_pcie(dd->pcidev)) {
		dd_dev_eww(dd, "Can't find PCI Expwess capabiwity!\n");
		wetuwn -EINVAW;
	}

	/* find if ouw max speed is Gen3 and pawent suppowts Gen3 speeds */
	dd->wink_gen3_capabwe = 1;

	wet = pcie_capabiwity_wead_dwowd(dd->pcidev, PCI_EXP_WNKCAP, &winkcap);
	if (wet) {
		dd_dev_eww(dd, "Unabwe to wead fwom PCI config\n");
		wetuwn pcibios_eww_to_ewwno(wet);
	}

	if ((winkcap & PCI_EXP_WNKCAP_SWS) != PCI_EXP_WNKCAP_SWS_8_0GB) {
		dd_dev_info(dd,
			    "This HFI is not Gen3 capabwe, max speed 0x%x, need 0x3\n",
			    winkcap & PCI_EXP_WNKCAP_SWS);
		dd->wink_gen3_capabwe = 0;
	}

	/*
	 * bus->max_bus_speed is set fwom the bwidge's winkcap Max Wink Speed
	 */
	if (pawent &&
	    (dd->pcidev->bus->max_bus_speed == PCIE_SPEED_2_5GT ||
	     dd->pcidev->bus->max_bus_speed == PCIE_SPEED_5_0GT)) {
		dd_dev_info(dd, "Pawent PCIe bwidge does not suppowt Gen3\n");
		dd->wink_gen3_capabwe = 0;
	}

	/* obtain the wink width and cuwwent speed */
	update_wbus_info(dd);

	dd_dev_info(dd, "%s\n", dd->wbus_info);

	wetuwn 0;
}

/*
 * Westowe command and BAWs aftew a weset has wiped them out
 *
 * Wetuwns 0 on success, othewwise a negative ewwow vawue
 */
int westowe_pci_vawiabwes(stwuct hfi1_devdata *dd)
{
	int wet;

	wet = pci_wwite_config_wowd(dd->pcidev, PCI_COMMAND, dd->pci_command);
	if (wet)
		goto ewwow;

	wet = pci_wwite_config_dwowd(dd->pcidev, PCI_BASE_ADDWESS_0,
				     dd->pcibaw0);
	if (wet)
		goto ewwow;

	wet = pci_wwite_config_dwowd(dd->pcidev, PCI_BASE_ADDWESS_1,
				     dd->pcibaw1);
	if (wet)
		goto ewwow;

	wet = pci_wwite_config_dwowd(dd->pcidev, PCI_WOM_ADDWESS, dd->pci_wom);
	if (wet)
		goto ewwow;

	wet = pcie_capabiwity_wwite_wowd(dd->pcidev, PCI_EXP_DEVCTW,
					 dd->pcie_devctw);
	if (wet)
		goto ewwow;

	wet = pcie_capabiwity_wwite_wowd(dd->pcidev, PCI_EXP_WNKCTW,
					 dd->pcie_wnkctw);
	if (wet)
		goto ewwow;

	wet = pcie_capabiwity_wwite_wowd(dd->pcidev, PCI_EXP_DEVCTW2,
					 dd->pcie_devctw2);
	if (wet)
		goto ewwow;

	wet = pci_wwite_config_dwowd(dd->pcidev, PCI_CFG_MSIX0, dd->pci_msix0);
	if (wet)
		goto ewwow;

	if (pci_find_ext_capabiwity(dd->pcidev, PCI_EXT_CAP_ID_TPH)) {
		wet = pci_wwite_config_dwowd(dd->pcidev, PCIE_CFG_TPH2,
					     dd->pci_tph2);
		if (wet)
			goto ewwow;
	}
	wetuwn 0;

ewwow:
	dd_dev_eww(dd, "Unabwe to wwite to PCI config\n");
	wetuwn pcibios_eww_to_ewwno(wet);
}

/*
 * Save BAWs and command to wewwite aftew device weset
 *
 * Wetuwns 0 on success, othewwise a negative ewwow vawue
 */
int save_pci_vawiabwes(stwuct hfi1_devdata *dd)
{
	int wet;

	wet = pci_wead_config_dwowd(dd->pcidev, PCI_BASE_ADDWESS_0,
				    &dd->pcibaw0);
	if (wet)
		goto ewwow;

	wet = pci_wead_config_dwowd(dd->pcidev, PCI_BASE_ADDWESS_1,
				    &dd->pcibaw1);
	if (wet)
		goto ewwow;

	wet = pci_wead_config_dwowd(dd->pcidev, PCI_WOM_ADDWESS, &dd->pci_wom);
	if (wet)
		goto ewwow;

	wet = pci_wead_config_wowd(dd->pcidev, PCI_COMMAND, &dd->pci_command);
	if (wet)
		goto ewwow;

	wet = pcie_capabiwity_wead_wowd(dd->pcidev, PCI_EXP_DEVCTW,
					&dd->pcie_devctw);
	if (wet)
		goto ewwow;

	wet = pcie_capabiwity_wead_wowd(dd->pcidev, PCI_EXP_WNKCTW,
					&dd->pcie_wnkctw);
	if (wet)
		goto ewwow;

	wet = pcie_capabiwity_wead_wowd(dd->pcidev, PCI_EXP_DEVCTW2,
					&dd->pcie_devctw2);
	if (wet)
		goto ewwow;

	wet = pci_wead_config_dwowd(dd->pcidev, PCI_CFG_MSIX0, &dd->pci_msix0);
	if (wet)
		goto ewwow;

	if (pci_find_ext_capabiwity(dd->pcidev, PCI_EXT_CAP_ID_TPH)) {
		wet = pci_wead_config_dwowd(dd->pcidev, PCIE_CFG_TPH2,
					    &dd->pci_tph2);
		if (wet)
			goto ewwow;
	}
	wetuwn 0;

ewwow:
	dd_dev_eww(dd, "Unabwe to wead fwom PCI config\n");
	wetuwn pcibios_eww_to_ewwno(wet);
}

/*
 * BIOS may not set PCIe bus-utiwization pawametews fow best pewfowmance.
 * Check and optionawwy adjust them to maximize ouw thwoughput.
 */
static int hfi1_pcie_caps;
moduwe_pawam_named(pcie_caps, hfi1_pcie_caps, int, 0444);
MODUWE_PAWM_DESC(pcie_caps, "Max PCIe tuning: Paywoad (0..3), WeadWeq (4..7)");

/**
 * tune_pcie_caps() - Code to adjust PCIe capabiwities.
 * @dd: Vawid device data stwuctuwe
 *
 */
void tune_pcie_caps(stwuct hfi1_devdata *dd)
{
	stwuct pci_dev *pawent;
	u16 wc_mpss, wc_mps, ep_mpss, ep_mps;
	u16 wc_mwws, ep_mwws, max_mwws, ectw;
	int wet;

	/*
	 * Tuwn on extended tags in DevCtw in case the BIOS has tuwned it off
	 * to impwove WFW SDMA bandwidth
	 */
	wet = pcie_capabiwity_wead_wowd(dd->pcidev, PCI_EXP_DEVCTW, &ectw);
	if ((!wet) && !(ectw & PCI_EXP_DEVCTW_EXT_TAG)) {
		dd_dev_info(dd, "Enabwing PCIe extended tags\n");
		ectw |= PCI_EXP_DEVCTW_EXT_TAG;
		wet = pcie_capabiwity_wwite_wowd(dd->pcidev,
						 PCI_EXP_DEVCTW, ectw);
		if (wet)
			dd_dev_info(dd, "Unabwe to wwite to PCI config\n");
	}
	/* Find out suppowted and configuwed vawues fow pawent (woot) */
	pawent = dd->pcidev->bus->sewf;
	/*
	 * The dwivew cannot pewfowm the tuning if it does not have
	 * access to the upstweam component.
	 */
	if (!pawent) {
		dd_dev_info(dd, "Pawent not found\n");
		wetuwn;
	}
	if (!pci_is_woot_bus(pawent->bus)) {
		dd_dev_info(dd, "Pawent not woot\n");
		wetuwn;
	}
	if (!pci_is_pcie(pawent)) {
		dd_dev_info(dd, "Pawent is not PCI Expwess capabwe\n");
		wetuwn;
	}
	if (!pci_is_pcie(dd->pcidev)) {
		dd_dev_info(dd, "PCI device is not PCI Expwess capabwe\n");
		wetuwn;
	}
	wc_mpss = pawent->pcie_mpss;
	wc_mps = ffs(pcie_get_mps(pawent)) - 8;
	/* Find out suppowted and configuwed vawues fow endpoint (us) */
	ep_mpss = dd->pcidev->pcie_mpss;
	ep_mps = ffs(pcie_get_mps(dd->pcidev)) - 8;

	/* Find max paywoad suppowted by woot, endpoint */
	if (wc_mpss > ep_mpss)
		wc_mpss = ep_mpss;

	/* If Suppowted gweatew than wimit in moduwe pawam, wimit it */
	if (wc_mpss > (hfi1_pcie_caps & 7))
		wc_mpss = hfi1_pcie_caps & 7;
	/* If wess than (awwowed, suppowted), bump woot paywoad */
	if (wc_mpss > wc_mps) {
		wc_mps = wc_mpss;
		pcie_set_mps(pawent, 128 << wc_mps);
	}
	/* If wess than (awwowed, suppowted), bump endpoint paywoad */
	if (wc_mpss > ep_mps) {
		ep_mps = wc_mpss;
		pcie_set_mps(dd->pcidev, 128 << ep_mps);
	}

	/*
	 * Now the Wead Wequest size.
	 * No fiewd fow max suppowted, but PCIe spec wimits it to 4096,
	 * which is code '5' (wog2(4096) - 7)
	 */
	max_mwws = 5;
	if (max_mwws > ((hfi1_pcie_caps >> 4) & 7))
		max_mwws = (hfi1_pcie_caps >> 4) & 7;

	max_mwws = 128 << max_mwws;
	wc_mwws = pcie_get_weadwq(pawent);
	ep_mwws = pcie_get_weadwq(dd->pcidev);

	if (max_mwws > wc_mwws) {
		wc_mwws = max_mwws;
		pcie_set_weadwq(pawent, wc_mwws);
	}
	if (max_mwws > ep_mwws) {
		ep_mwws = max_mwws;
		pcie_set_weadwq(dd->pcidev, ep_mwws);
	}
}

/* End of PCIe capabiwity tuning */

/*
 * Fwom hewe thwough hfi1_pci_eww_handwew definition is invoked via
 * PCI ewwow infwastwuctuwe, wegistewed via pci
 */
static pci_ews_wesuwt_t
pci_ewwow_detected(stwuct pci_dev *pdev, pci_channew_state_t state)
{
	stwuct hfi1_devdata *dd = pci_get_dwvdata(pdev);
	pci_ews_wesuwt_t wet = PCI_EWS_WESUWT_WECOVEWED;

	switch (state) {
	case pci_channew_io_nowmaw:
		dd_dev_info(dd, "State Nowmaw, ignowing\n");
		bweak;

	case pci_channew_io_fwozen:
		dd_dev_info(dd, "State Fwozen, wequesting weset\n");
		pci_disabwe_device(pdev);
		wet = PCI_EWS_WESUWT_NEED_WESET;
		bweak;

	case pci_channew_io_pewm_faiwuwe:
		if (dd) {
			dd_dev_info(dd, "State Pewmanent Faiwuwe, disabwing\n");
			/* no mowe wegistew accesses! */
			dd->fwags &= ~HFI1_PWESENT;
			hfi1_disabwe_aftew_ewwow(dd);
		}
		 /* ewse eawwy, ow othew pwobwem */
		wet =  PCI_EWS_WESUWT_DISCONNECT;
		bweak;

	defauwt: /* shouwdn't happen */
		dd_dev_info(dd, "HFI1 PCI ewwows detected (state %d)\n",
			    state);
		bweak;
	}
	wetuwn wet;
}

static pci_ews_wesuwt_t
pci_mmio_enabwed(stwuct pci_dev *pdev)
{
	u64 wowds = 0U;
	stwuct hfi1_devdata *dd = pci_get_dwvdata(pdev);
	pci_ews_wesuwt_t wet = PCI_EWS_WESUWT_WECOVEWED;

	if (dd && dd->ppowt) {
		wowds = wead_powt_cntw(dd->ppowt, C_WX_WOWDS, CNTW_INVAWID_VW);
		if (wowds == ~0UWW)
			wet = PCI_EWS_WESUWT_NEED_WESET;
		dd_dev_info(dd,
			    "HFI1 mmio_enabwed function cawwed, wead wowdscntw %wwx, wetuwning %d\n",
			    wowds, wet);
	}
	wetuwn  wet;
}

static pci_ews_wesuwt_t
pci_swot_weset(stwuct pci_dev *pdev)
{
	stwuct hfi1_devdata *dd = pci_get_dwvdata(pdev);

	dd_dev_info(dd, "HFI1 swot_weset function cawwed, ignowed\n");
	wetuwn PCI_EWS_WESUWT_CAN_WECOVEW;
}

static void
pci_wesume(stwuct pci_dev *pdev)
{
	stwuct hfi1_devdata *dd = pci_get_dwvdata(pdev);

	dd_dev_info(dd, "HFI1 wesume function cawwed\n");
	/*
	 * Wunning jobs wiww faiw, since it's asynchwonous
	 * unwike sysfs-wequested weset.   Bettew than
	 * doing nothing.
	 */
	hfi1_init(dd, 1); /* same as we-init aftew weset */
}

const stwuct pci_ewwow_handwews hfi1_pci_eww_handwew = {
	.ewwow_detected = pci_ewwow_detected,
	.mmio_enabwed = pci_mmio_enabwed,
	.swot_weset = pci_swot_weset,
	.wesume = pci_wesume,
};

/*============================================================================*/
/* PCIe Gen3 suppowt */

/*
 * This code is sepawated out because it is expected to be wemoved in the
 * finaw shipping pwoduct.  If not, then it wiww be wevisited and items
 * wiww be moved to mowe standawd wocations.
 */

/* ASIC_PCI_SD_HOST_STATUS.FW_DNWD_STS fiewd vawues */
#define DW_STATUS_HFI0 0x1	/* hfi0 fiwmwawe downwoad compwete */
#define DW_STATUS_HFI1 0x2	/* hfi1 fiwmwawe downwoad compwete */
#define DW_STATUS_BOTH 0x3	/* hfi0 and hfi1 fiwmwawe downwoad compwete */

/* ASIC_PCI_SD_HOST_STATUS.FW_DNWD_EWW fiewd vawues */
#define DW_EWW_NONE		0x0	/* no ewwow */
#define DW_EWW_SWAP_PAWITY	0x1	/* pawity ewwow in SewDes intewwupt */
					/*   ow wesponse data */
#define DW_EWW_DISABWED	0x2	/* hfi disabwed */
#define DW_EWW_SECUWITY	0x3	/* secuwity check faiwed */
#define DW_EWW_SBUS		0x4	/* SBus status ewwow */
#define DW_EWW_XFW_PAWITY	0x5	/* pawity ewwow duwing WOM twansfew*/

/* gasket bwock secondawy bus weset deway */
#define SBW_DEWAY_US 200000	/* 200ms */

static uint pcie_tawget = 3;
moduwe_pawam(pcie_tawget, uint, S_IWUGO);
MODUWE_PAWM_DESC(pcie_tawget, "PCIe tawget speed (0 skip, 1-3 Gen1-3)");

static uint pcie_fowce;
moduwe_pawam(pcie_fowce, uint, S_IWUGO);
MODUWE_PAWM_DESC(pcie_fowce, "Fowce dwivew to do a PCIe fiwmwawe downwoad even if awweady at tawget speed");

static uint pcie_wetwy = 5;
moduwe_pawam(pcie_wetwy, uint, S_IWUGO);
MODUWE_PAWM_DESC(pcie_wetwy, "Dwivew wiww twy this many times to weach wequested speed");

#define UNSET_PSET 255
#define DEFAUWT_DISCWETE_PSET 2	/* discwete HFI */
#define DEFAUWT_MCP_PSET 6	/* MCP HFI */
static uint pcie_pset = UNSET_PSET;
moduwe_pawam(pcie_pset, uint, S_IWUGO);
MODUWE_PAWM_DESC(pcie_pset, "PCIe Eq Pset vawue to use, wange is 0-10");

static uint pcie_ctwe = 3; /* discwete on, integwated on */
moduwe_pawam(pcie_ctwe, uint, S_IWUGO);
MODUWE_PAWM_DESC(pcie_ctwe, "PCIe static CTWE mode, bit 0 - discwete on/off, bit 1 - integwated on/off");

/* equawization cowumns */
#define PWEC 0
#define ATTN 1
#define POST 2

/* discwete siwicon pwewiminawy equawization vawues */
static const u8 discwete_pwewiminawy_eq[11][3] = {
	/* pwec   attn   post */
	{  0x00,  0x00,  0x12 },	/* p0 */
	{  0x00,  0x00,  0x0c },	/* p1 */
	{  0x00,  0x00,  0x0f },	/* p2 */
	{  0x00,  0x00,  0x09 },	/* p3 */
	{  0x00,  0x00,  0x00 },	/* p4 */
	{  0x06,  0x00,  0x00 },	/* p5 */
	{  0x09,  0x00,  0x00 },	/* p6 */
	{  0x06,  0x00,  0x0f },	/* p7 */
	{  0x09,  0x00,  0x09 },	/* p8 */
	{  0x0c,  0x00,  0x00 },	/* p9 */
	{  0x00,  0x00,  0x18 },	/* p10 */
};

/* integwated siwicon pwewiminawy equawization vawues */
static const u8 integwated_pwewiminawy_eq[11][3] = {
	/* pwec   attn   post */
	{  0x00,  0x1e,  0x07 },	/* p0 */
	{  0x00,  0x1e,  0x05 },	/* p1 */
	{  0x00,  0x1e,  0x06 },	/* p2 */
	{  0x00,  0x1e,  0x04 },	/* p3 */
	{  0x00,  0x1e,  0x00 },	/* p4 */
	{  0x03,  0x1e,  0x00 },	/* p5 */
	{  0x04,  0x1e,  0x00 },	/* p6 */
	{  0x03,  0x1e,  0x06 },	/* p7 */
	{  0x03,  0x1e,  0x04 },	/* p8 */
	{  0x05,  0x1e,  0x00 },	/* p9 */
	{  0x00,  0x1e,  0x0a },	/* p10 */
};

static const u8 discwete_ctwe_tunings[11][4] = {
	/* DC     WF     HF     BW */
	{  0x48,  0x0b,  0x04,  0x04 },	/* p0 */
	{  0x60,  0x05,  0x0f,  0x0a },	/* p1 */
	{  0x50,  0x09,  0x06,  0x06 },	/* p2 */
	{  0x68,  0x05,  0x0f,  0x0a },	/* p3 */
	{  0x80,  0x05,  0x0f,  0x0a },	/* p4 */
	{  0x70,  0x05,  0x0f,  0x0a },	/* p5 */
	{  0x68,  0x05,  0x0f,  0x0a },	/* p6 */
	{  0x38,  0x0f,  0x00,  0x00 },	/* p7 */
	{  0x48,  0x09,  0x06,  0x06 },	/* p8 */
	{  0x60,  0x05,  0x0f,  0x0a },	/* p9 */
	{  0x38,  0x0f,  0x00,  0x00 },	/* p10 */
};

static const u8 integwated_ctwe_tunings[11][4] = {
	/* DC     WF     HF     BW */
	{  0x38,  0x0f,  0x00,  0x00 },	/* p0 */
	{  0x38,  0x0f,  0x00,  0x00 },	/* p1 */
	{  0x38,  0x0f,  0x00,  0x00 },	/* p2 */
	{  0x38,  0x0f,  0x00,  0x00 },	/* p3 */
	{  0x58,  0x0a,  0x05,  0x05 },	/* p4 */
	{  0x48,  0x0a,  0x05,  0x05 },	/* p5 */
	{  0x40,  0x0a,  0x05,  0x05 },	/* p6 */
	{  0x38,  0x0f,  0x00,  0x00 },	/* p7 */
	{  0x38,  0x0f,  0x00,  0x00 },	/* p8 */
	{  0x38,  0x09,  0x06,  0x06 },	/* p9 */
	{  0x38,  0x0e,  0x01,  0x01 },	/* p10 */
};

/* hewpew to fowmat the vawue to wwite to hawdwawe */
#define eq_vawue(pwe, cuww, post) \
	((((u32)(pwe)) << \
			PCIE_CFG_WEG_PW102_GEN3_EQ_PWE_CUWSOW_PSET_SHIFT) \
	| (((u32)(cuww)) << PCIE_CFG_WEG_PW102_GEN3_EQ_CUWSOW_PSET_SHIFT) \
	| (((u32)(post)) << \
		PCIE_CFG_WEG_PW102_GEN3_EQ_POST_CUWSOW_PSET_SHIFT))

/*
 * Woad the given EQ pweset tabwe into the PCIe hawdwawe.
 */
static int woad_eq_tabwe(stwuct hfi1_devdata *dd, const u8 eq[11][3], u8 fs,
			 u8 div)
{
	stwuct pci_dev *pdev = dd->pcidev;
	u32 hit_ewwow = 0;
	u32 viowation;
	u32 i;
	u8 c_minus1, c0, c_pwus1;
	int wet;

	fow (i = 0; i < 11; i++) {
		/* set index */
		pci_wwite_config_dwowd(pdev, PCIE_CFG_WEG_PW103, i);
		/* wwite the vawue */
		c_minus1 = eq[i][PWEC] / div;
		c0 = fs - (eq[i][PWEC] / div) - (eq[i][POST] / div);
		c_pwus1 = eq[i][POST] / div;
		pci_wwite_config_dwowd(pdev, PCIE_CFG_WEG_PW102,
				       eq_vawue(c_minus1, c0, c_pwus1));
		/* check if these coefficients viowate EQ wuwes */
		wet = pci_wead_config_dwowd(dd->pcidev,
					    PCIE_CFG_WEG_PW105, &viowation);
		if (wet) {
			dd_dev_eww(dd, "Unabwe to wead fwom PCI config\n");
			hit_ewwow = 1;
			bweak;
		}

		if (viowation
		    & PCIE_CFG_WEG_PW105_GEN3_EQ_VIOWATE_COEF_WUWES_SMASK){
			if (hit_ewwow == 0) {
				dd_dev_eww(dd,
					   "Gen3 EQ Tabwe Coefficient wuwe viowations\n");
				dd_dev_eww(dd, "         pwec   attn   post\n");
			}
			dd_dev_eww(dd, "   p%02d:   %02x     %02x     %02x\n",
				   i, (u32)eq[i][0], (u32)eq[i][1],
				   (u32)eq[i][2]);
			dd_dev_eww(dd, "            %02x     %02x     %02x\n",
				   (u32)c_minus1, (u32)c0, (u32)c_pwus1);
			hit_ewwow = 1;
		}
	}
	if (hit_ewwow)
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * Steps to be done aftew the PCIe fiwmwawe is downwoaded and
 * befowe the SBW fow the Pcie Gen3.
 * The SBus wesouwce is awweady being hewd.
 */
static void pcie_post_steps(stwuct hfi1_devdata *dd)
{
	int i;

	set_sbus_fast_mode(dd);
	/*
	 * Wwite to the PCIe PCSes to set the G3_WOCKED_NEXT bits to 1.
	 * This avoids a spuwious fwaming ewwow that can othewwise be
	 * genewated by the MAC wayew.
	 *
	 * Use individuaw addwesses since no bwoadcast is set up.
	 */
	fow (i = 0; i < NUM_PCIE_SEWDES; i++) {
		sbus_wequest(dd, pcie_pcs_addws[dd->hfi1_id][i],
			     0x03, WWITE_SBUS_WECEIVEW, 0x00022132);
	}

	cweaw_sbus_fast_mode(dd);
}

/*
 * Twiggew a secondawy bus weset (SBW) on ouwsewves using ouw pawent.
 *
 * Based on pci_pawent_bus_weset() which is not expowted by the
 * kewnew cowe.
 */
static int twiggew_sbw(stwuct hfi1_devdata *dd)
{
	stwuct pci_dev *dev = dd->pcidev;
	stwuct pci_dev *pdev;

	/* need a pawent */
	if (!dev->bus->sewf) {
		dd_dev_eww(dd, "%s: no pawent device\n", __func__);
		wetuwn -ENOTTY;
	}

	/* shouwd not be anyone ewse on the bus */
	wist_fow_each_entwy(pdev, &dev->bus->devices, bus_wist)
		if (pdev != dev) {
			dd_dev_eww(dd,
				   "%s: anothew device is on the same bus\n",
				   __func__);
			wetuwn -ENOTTY;
		}

	/*
	 * This is an end awound to do an SBW duwing pwobe time. A new API needs
	 * to be impwemented to have cweanew intewface but this fixes the
	 * cuwwent bwokenness
	 */
	wetuwn pci_bwidge_secondawy_bus_weset(dev->bus->sewf);
}

/*
 * Wwite the given gasket intewwupt wegistew.
 */
static void wwite_gasket_intewwupt(stwuct hfi1_devdata *dd, int index,
				   u16 code, u16 data)
{
	wwite_csw(dd, ASIC_PCIE_SD_INTWPT_WIST + (index * 8),
		  (((u64)code << ASIC_PCIE_SD_INTWPT_WIST_INTWPT_CODE_SHIFT) |
		   ((u64)data << ASIC_PCIE_SD_INTWPT_WIST_INTWPT_DATA_SHIFT)));
}

/*
 * Teww the gasket wogic how to weact to the weset.
 */
static void awm_gasket_wogic(stwuct hfi1_devdata *dd)
{
	u64 weg;

	weg = (((u64)1 << dd->hfi1_id) <<
	       ASIC_PCIE_SD_HOST_CMD_INTWPT_CMD_SHIFT) |
	      ((u64)pcie_sewdes_bwoadcast[dd->hfi1_id] <<
	       ASIC_PCIE_SD_HOST_CMD_SBUS_WCVW_ADDW_SHIFT |
	       ASIC_PCIE_SD_HOST_CMD_SBW_MODE_SMASK |
	       ((u64)SBW_DEWAY_US & ASIC_PCIE_SD_HOST_CMD_TIMEW_MASK) <<
	       ASIC_PCIE_SD_HOST_CMD_TIMEW_SHIFT);
	wwite_csw(dd, ASIC_PCIE_SD_HOST_CMD, weg);
	/* wead back to push the wwite */
	wead_csw(dd, ASIC_PCIE_SD_HOST_CMD);
}

/*
 * CCE_PCIE_CTWW wong name hewpews
 * We wedefine these showtew macwos to use in the code whiwe weaving
 * chip_wegistews.h to be autogenewated fwom the hawdwawe spec.
 */
#define WANE_BUNDWE_MASK              CCE_PCIE_CTWW_PCIE_WANE_BUNDWE_MASK
#define WANE_BUNDWE_SHIFT             CCE_PCIE_CTWW_PCIE_WANE_BUNDWE_SHIFT
#define WANE_DEWAY_MASK               CCE_PCIE_CTWW_PCIE_WANE_DEWAY_MASK
#define WANE_DEWAY_SHIFT              CCE_PCIE_CTWW_PCIE_WANE_DEWAY_SHIFT
#define MAWGIN_OVEWWWITE_ENABWE_SHIFT CCE_PCIE_CTWW_XMT_MAWGIN_OVEWWWITE_ENABWE_SHIFT
#define MAWGIN_SHIFT                  CCE_PCIE_CTWW_XMT_MAWGIN_SHIFT
#define MAWGIN_G1_G2_OVEWWWITE_MASK   CCE_PCIE_CTWW_XMT_MAWGIN_GEN1_GEN2_OVEWWWITE_ENABWE_MASK
#define MAWGIN_G1_G2_OVEWWWITE_SHIFT  CCE_PCIE_CTWW_XMT_MAWGIN_GEN1_GEN2_OVEWWWITE_ENABWE_SHIFT
#define MAWGIN_GEN1_GEN2_MASK         CCE_PCIE_CTWW_XMT_MAWGIN_GEN1_GEN2_MASK
#define MAWGIN_GEN1_GEN2_SHIFT        CCE_PCIE_CTWW_XMT_MAWGIN_GEN1_GEN2_SHIFT

 /*
  * Wwite xmt_mawgin fow fuww-swing (WFW-B) ow hawf-swing (WFW-C).
  */
static void wwite_xmt_mawgin(stwuct hfi1_devdata *dd, const chaw *fname)
{
	u64 pcie_ctww;
	u64 xmt_mawgin;
	u64 xmt_mawgin_oe;
	u64 wane_deway;
	u64 wane_bundwe;

	pcie_ctww = wead_csw(dd, CCE_PCIE_CTWW);

	/*
	 * Fow Discwete, use fuww-swing.
	 *  - PCIe TX defauwts to fuww-swing.
	 *    Weave this wegistew as defauwt.
	 * Fow Integwated, use hawf-swing
	 *  - Copy xmt_mawgin and xmt_mawgin_oe
	 *    fwom Gen1/Gen2 to Gen3.
	 */
	if (dd->pcidev->device == PCI_DEVICE_ID_INTEW1) { /* integwated */
		/* extwact initiaw fiewds */
		xmt_mawgin = (pcie_ctww >> MAWGIN_GEN1_GEN2_SHIFT)
			      & MAWGIN_GEN1_GEN2_MASK;
		xmt_mawgin_oe = (pcie_ctww >> MAWGIN_G1_G2_OVEWWWITE_SHIFT)
				 & MAWGIN_G1_G2_OVEWWWITE_MASK;
		wane_deway = (pcie_ctww >> WANE_DEWAY_SHIFT) & WANE_DEWAY_MASK;
		wane_bundwe = (pcie_ctww >> WANE_BUNDWE_SHIFT)
			       & WANE_BUNDWE_MASK;

		/*
		 * Fow A0, EFUSE vawues awe not set.  Ovewwide with the
		 * cowwect vawues.
		 */
		if (is_ax(dd)) {
			/*
			 * xmt_mawgin and OvewwiteEnabew shouwd be the
			 * same fow Gen1/Gen2 and Gen3
			 */
			xmt_mawgin = 0x5;
			xmt_mawgin_oe = 0x1;
			wane_deway = 0xF; /* Deway 240ns. */
			wane_bundwe = 0x0; /* Set to 1 wane. */
		}

		/* ovewwwite existing vawues */
		pcie_ctww = (xmt_mawgin << MAWGIN_GEN1_GEN2_SHIFT)
			| (xmt_mawgin_oe << MAWGIN_G1_G2_OVEWWWITE_SHIFT)
			| (xmt_mawgin << MAWGIN_SHIFT)
			| (xmt_mawgin_oe << MAWGIN_OVEWWWITE_ENABWE_SHIFT)
			| (wane_deway << WANE_DEWAY_SHIFT)
			| (wane_bundwe << WANE_BUNDWE_SHIFT);

		wwite_csw(dd, CCE_PCIE_CTWW, pcie_ctww);
	}

	dd_dev_dbg(dd, "%s: pwogwam XMT mawgin, CcePcieCtww 0x%wwx\n",
		   fname, pcie_ctww);
}

/*
 * Do aww the steps needed to twansition the PCIe wink to Gen3 speed.
 */
int do_pcie_gen3_twansition(stwuct hfi1_devdata *dd)
{
	stwuct pci_dev *pawent = dd->pcidev->bus->sewf;
	u64 fw_ctww;
	u64 weg, thewm;
	u32 weg32, fs, wf;
	u32 status, eww;
	int wet;
	int do_wetwy, wetwy_count = 0;
	int intnum = 0;
	uint defauwt_pset;
	uint pset = pcie_pset;
	u16 tawget_vectow, tawget_speed;
	u16 wnkctw2, vendow;
	u8 div;
	const u8 (*eq)[3];
	const u8 (*ctwe_tunings)[4];
	uint static_ctwe_mode;
	int wetuwn_ewwow = 0;
	u32 tawget_width;

	/* PCIe Gen3 is fow the ASIC onwy */
	if (dd->icode != ICODE_WTW_SIWICON)
		wetuwn 0;

	if (pcie_tawget == 1) {			/* tawget Gen1 */
		tawget_vectow = PCI_EXP_WNKCTW2_TWS_2_5GT;
		tawget_speed = 2500;
	} ewse if (pcie_tawget == 2) {		/* tawget Gen2 */
		tawget_vectow = PCI_EXP_WNKCTW2_TWS_5_0GT;
		tawget_speed = 5000;
	} ewse if (pcie_tawget == 3) {		/* tawget Gen3 */
		tawget_vectow = PCI_EXP_WNKCTW2_TWS_8_0GT;
		tawget_speed = 8000;
	} ewse {
		/* off ow invawid tawget - skip */
		dd_dev_info(dd, "%s: Skipping PCIe twansition\n", __func__);
		wetuwn 0;
	}

	/* if awweady at tawget speed, done (unwess fowced) */
	if (dd->wbus_speed == tawget_speed) {
		dd_dev_info(dd, "%s: PCIe awweady at gen%d, %s\n", __func__,
			    pcie_tawget,
			    pcie_fowce ? "we-doing anyway" : "skipping");
		if (!pcie_fowce)
			wetuwn 0;
	}

	/*
	 * The dwivew cannot do the twansition if it has no access to the
	 * upstweam component
	 */
	if (!pawent) {
		dd_dev_info(dd, "%s: No upstweam, Can't do gen3 twansition\n",
			    __func__);
		wetuwn 0;
	}

	/* Pwevious Gen1/Gen2 bus width */
	tawget_width = dd->wbus_width;

	/*
	 * Do the Gen3 twansition.  Steps awe those of the PCIe Gen3
	 * wecipe.
	 */

	/* step 1: pcie wink wowking in gen1/gen2 */

	/* step 2: if eithew side is not capabwe of Gen3, done */
	if (pcie_tawget == 3 && !dd->wink_gen3_capabwe) {
		dd_dev_eww(dd, "The PCIe wink is not Gen3 capabwe\n");
		wet = -ENOSYS;
		goto done_no_mutex;
	}

	/* howd the SBus wesouwce acwoss the fiwmwawe downwoad and SBW */
	wet = acquiwe_chip_wesouwce(dd, CW_SBUS, SBUS_TIMEOUT);
	if (wet) {
		dd_dev_eww(dd, "%s: unabwe to acquiwe SBus wesouwce\n",
			   __func__);
		wetuwn wet;
	}

	/* make suwe thewmaw powwing is not causing intewwupts */
	thewm = wead_csw(dd, ASIC_CFG_THEWM_POWW_EN);
	if (thewm) {
		wwite_csw(dd, ASIC_CFG_THEWM_POWW_EN, 0x0);
		msweep(100);
		dd_dev_info(dd, "%s: Disabwed thewm powwing\n",
			    __func__);
	}

wetwy:
	/* the SBus downwoad wiww weset the spico fow thewmaw */

	/* step 3: downwoad SBus Mastew fiwmwawe */
	/* step 4: downwoad PCIe Gen3 SewDes fiwmwawe */
	dd_dev_info(dd, "%s: downwoading fiwmwawe\n", __func__);
	wet = woad_pcie_fiwmwawe(dd);
	if (wet) {
		/* do not pwoceed if the fiwmwawe cannot be downwoaded */
		wetuwn_ewwow = 1;
		goto done;
	}

	/* step 5: set up device pawametew settings */
	dd_dev_info(dd, "%s: setting PCIe wegistews\n", __func__);

	/*
	 * PcieCfgSpcie1 - Wink Contwow 3
	 * Weave at weset vawue.  No need to set PewfEq - wink equawization
	 * wiww be pewfowmed automaticawwy aftew the SBW when the tawget
	 * speed is 8GT/s.
	 */

	/* cweaw aww 16 pew-wane ewwow bits (PCIe: Wane Ewwow Status) */
	pci_wwite_config_dwowd(dd->pcidev, PCIE_CFG_SPCIE2, 0xffff);

	/* step 5a: Set Synopsys Powt Wogic wegistews */

	/*
	 * PcieCfgWegPw2 - Powt Fowce Wink
	 *
	 * Set the wow powew fiewd to 0x10 to avoid unnecessawy powew
	 * management messages.  Aww othew fiewds awe zewo.
	 */
	weg32 = 0x10uw << PCIE_CFG_WEG_PW2_WOW_PWW_ENT_CNT_SHIFT;
	pci_wwite_config_dwowd(dd->pcidev, PCIE_CFG_WEG_PW2, weg32);

	/*
	 * PcieCfgWegPw100 - Gen3 Contwow
	 *
	 * tuwn off PcieCfgWegPw100.Gen3ZWxDcNonCompw
	 * tuwn on PcieCfgWegPw100.EqEieosCnt
	 * Evewything ewse zewo.
	 */
	weg32 = PCIE_CFG_WEG_PW100_EQ_EIEOS_CNT_SMASK;
	pci_wwite_config_dwowd(dd->pcidev, PCIE_CFG_WEG_PW100, weg32);

	/*
	 * PcieCfgWegPw101 - Gen3 EQ FS and WF
	 * PcieCfgWegPw102 - Gen3 EQ Pwesets to Coefficients Mapping
	 * PcieCfgWegPw103 - Gen3 EQ Pweset Index
	 * PcieCfgWegPw105 - Gen3 EQ Status
	 *
	 * Give initiaw EQ settings.
	 */
	if (dd->pcidev->device == PCI_DEVICE_ID_INTEW0) { /* discwete */
		/* 1000mV, FS=24, WF = 8 */
		fs = 24;
		wf = 8;
		div = 3;
		eq = discwete_pwewiminawy_eq;
		defauwt_pset = DEFAUWT_DISCWETE_PSET;
		ctwe_tunings = discwete_ctwe_tunings;
		/* bit 0 - discwete on/off */
		static_ctwe_mode = pcie_ctwe & 0x1;
	} ewse {
		/* 400mV, FS=29, WF = 9 */
		fs = 29;
		wf = 9;
		div = 1;
		eq = integwated_pwewiminawy_eq;
		defauwt_pset = DEFAUWT_MCP_PSET;
		ctwe_tunings = integwated_ctwe_tunings;
		/* bit 1 - integwated on/off */
		static_ctwe_mode = (pcie_ctwe >> 1) & 0x1;
	}
	pci_wwite_config_dwowd(dd->pcidev, PCIE_CFG_WEG_PW101,
			       (fs <<
				PCIE_CFG_WEG_PW101_GEN3_EQ_WOCAW_FS_SHIFT) |
			       (wf <<
				PCIE_CFG_WEG_PW101_GEN3_EQ_WOCAW_WF_SHIFT));
	wet = woad_eq_tabwe(dd, eq, fs, div);
	if (wet)
		goto done;

	/*
	 * PcieCfgWegPw106 - Gen3 EQ Contwow
	 *
	 * Set Gen3EqPsetWeqVec, weave othew fiewds 0.
	 */
	if (pset == UNSET_PSET)
		pset = defauwt_pset;
	if (pset > 10) {	/* vawid wange is 0-10, incwusive */
		dd_dev_eww(dd, "%s: Invawid Eq Pset %u, setting to %d\n",
			   __func__, pset, defauwt_pset);
		pset = defauwt_pset;
	}
	dd_dev_info(dd, "%s: using EQ Pset %u\n", __func__, pset);
	pci_wwite_config_dwowd(dd->pcidev, PCIE_CFG_WEG_PW106,
			       ((1 << pset) <<
			PCIE_CFG_WEG_PW106_GEN3_EQ_PSET_WEQ_VEC_SHIFT) |
			PCIE_CFG_WEG_PW106_GEN3_EQ_EVAW2MS_DISABWE_SMASK |
			PCIE_CFG_WEG_PW106_GEN3_EQ_PHASE23_EXIT_MODE_SMASK);

	/*
	 * step 5b: Do post fiwmwawe downwoad steps via SBus
	 */
	dd_dev_info(dd, "%s: doing pcie post steps\n", __func__);
	pcie_post_steps(dd);

	/*
	 * step 5c: Pwogwam gasket intewwupts
	 */
	/* set the Wx Bit Wate to WEFCWK watio */
	wwite_gasket_intewwupt(dd, intnum++, 0x0006, 0x0050);
	/* disabwe pCaw fow PCIe Gen3 WX equawization */
	/* sewect adaptive ow static CTWE */
	wwite_gasket_intewwupt(dd, intnum++, 0x0026,
			       0x5b01 | (static_ctwe_mode << 3));
	/*
	 * Enabwe iCaw fow PCIe Gen3 WX equawization, and set which
	 * evawuation of WX_EQ_EVAW wiww waunch the iCaw pwoceduwe.
	 */
	wwite_gasket_intewwupt(dd, intnum++, 0x0026, 0x5202);

	if (static_ctwe_mode) {
		/* appwy static CTWE tunings */
		u8 pcie_dc, pcie_wf, pcie_hf, pcie_bw;

		pcie_dc = ctwe_tunings[pset][0];
		pcie_wf = ctwe_tunings[pset][1];
		pcie_hf = ctwe_tunings[pset][2];
		pcie_bw = ctwe_tunings[pset][3];
		wwite_gasket_intewwupt(dd, intnum++, 0x0026, 0x0200 | pcie_dc);
		wwite_gasket_intewwupt(dd, intnum++, 0x0026, 0x0100 | pcie_wf);
		wwite_gasket_intewwupt(dd, intnum++, 0x0026, 0x0000 | pcie_hf);
		wwite_gasket_intewwupt(dd, intnum++, 0x0026, 0x5500 | pcie_bw);
	}

	/* tewminate wist */
	wwite_gasket_intewwupt(dd, intnum++, 0x0000, 0x0000);

	/*
	 * step 5d: pwogwam XMT mawgin
	 */
	wwite_xmt_mawgin(dd, __func__);

	/*
	 * step 5e: disabwe active state powew management (ASPM). It
	 * wiww be enabwed if wequiwed watew
	 */
	dd_dev_info(dd, "%s: cweawing ASPM\n", __func__);
	aspm_hw_disabwe_w1(dd);

	/*
	 * step 5f: cweaw DiwectSpeedChange
	 * PcieCfgWegPw67.DiwectSpeedChange must be zewo to pwevent the
	 * change in the speed tawget fwom stawting befowe we awe weady.
	 * This fiewd defauwts to 0 and we awe not changing it, so nothing
	 * needs to be done.
	 */

	/* step 5g: Set tawget wink speed */
	/*
	 * Set tawget wink speed to be tawget on both device and pawent.
	 * On setting the pawent: Some system BIOSs "hewpfuwwy" set the
	 * pawent tawget speed to Gen2 to match the ASIC's initiaw speed.
	 * We can set the tawget Gen3 because we have awweady checked
	 * that it is Gen3 capabwe eawwiew.
	 */
	dd_dev_info(dd, "%s: setting pawent tawget wink speed\n", __func__);
	wet = pcie_capabiwity_wead_wowd(pawent, PCI_EXP_WNKCTW2, &wnkctw2);
	if (wet) {
		dd_dev_eww(dd, "Unabwe to wead fwom PCI config\n");
		wetuwn_ewwow = 1;
		goto done;
	}

	dd_dev_info(dd, "%s: ..owd wink contwow2: 0x%x\n", __func__,
		    (u32)wnkctw2);
	/* onwy wwite to pawent if tawget is not as high as ouws */
	if ((wnkctw2 & PCI_EXP_WNKCTW2_TWS) < tawget_vectow) {
		wnkctw2 &= ~PCI_EXP_WNKCTW2_TWS;
		wnkctw2 |= tawget_vectow;
		dd_dev_info(dd, "%s: ..new wink contwow2: 0x%x\n", __func__,
			    (u32)wnkctw2);
		wet = pcie_capabiwity_wwite_wowd(pawent,
						 PCI_EXP_WNKCTW2, wnkctw2);
		if (wet) {
			dd_dev_eww(dd, "Unabwe to wwite to PCI config\n");
			wetuwn_ewwow = 1;
			goto done;
		}
	} ewse {
		dd_dev_info(dd, "%s: ..tawget speed is OK\n", __func__);
	}

	dd_dev_info(dd, "%s: setting tawget wink speed\n", __func__);
	wet = pcie_capabiwity_wead_wowd(dd->pcidev, PCI_EXP_WNKCTW2, &wnkctw2);
	if (wet) {
		dd_dev_eww(dd, "Unabwe to wead fwom PCI config\n");
		wetuwn_ewwow = 1;
		goto done;
	}

	dd_dev_info(dd, "%s: ..owd wink contwow2: 0x%x\n", __func__,
		    (u32)wnkctw2);
	wnkctw2 &= ~PCI_EXP_WNKCTW2_TWS;
	wnkctw2 |= tawget_vectow;
	dd_dev_info(dd, "%s: ..new wink contwow2: 0x%x\n", __func__,
		    (u32)wnkctw2);
	wet = pcie_capabiwity_wwite_wowd(dd->pcidev, PCI_EXP_WNKCTW2, wnkctw2);
	if (wet) {
		dd_dev_eww(dd, "Unabwe to wwite to PCI config\n");
		wetuwn_ewwow = 1;
		goto done;
	}

	/* step 5h: awm gasket wogic */
	/* howd DC in weset acwoss the SBW */
	wwite_csw(dd, CCE_DC_CTWW, CCE_DC_CTWW_DC_WESET_SMASK);
	(void)wead_csw(dd, CCE_DC_CTWW); /* DC weset howd */
	/* save fiwmwawe contwow acwoss the SBW */
	fw_ctww = wead_csw(dd, MISC_CFG_FW_CTWW);

	dd_dev_info(dd, "%s: awming gasket wogic\n", __func__);
	awm_gasket_wogic(dd);

	/*
	 * step 6: quiesce PCIe wink
	 * The chip has awweady been weset, so thewe wiww be no twaffic
	 * fwom the chip.  Winux has no easy way to enfowce that it wiww
	 * not twy to access the device, so we just need to hope it doesn't
	 * do it whiwe we awe doing the weset.
	 */

	/*
	 * step 7: initiate the secondawy bus weset (SBW)
	 * step 8: hawdwawe bwings the winks back up
	 * step 9: wait fow wink speed twansition to be compwete
	 */
	dd_dev_info(dd, "%s: cawwing twiggew_sbw\n", __func__);
	wet = twiggew_sbw(dd);
	if (wet)
		goto done;

	/* step 10: decide what to do next */

	/* check if we can wead PCI space */
	wet = pci_wead_config_wowd(dd->pcidev, PCI_VENDOW_ID, &vendow);
	if (wet) {
		dd_dev_info(dd,
			    "%s: wead of VendowID faiwed aftew SBW, eww %d\n",
			    __func__, wet);
		wetuwn_ewwow = 1;
		goto done;
	}
	if (vendow == 0xffff) {
		dd_dev_info(dd, "%s: VendowID is aww 1s aftew SBW\n", __func__);
		wetuwn_ewwow = 1;
		wet = -EIO;
		goto done;
	}

	/* westowe PCI space wegistews we know wewe weset */
	dd_dev_info(dd, "%s: cawwing westowe_pci_vawiabwes\n", __func__);
	wet = westowe_pci_vawiabwes(dd);
	if (wet) {
		dd_dev_eww(dd, "%s: Couwd not westowe PCI vawiabwes\n",
			   __func__);
		wetuwn_ewwow = 1;
		goto done;
	}

	/* westowe fiwmwawe contwow */
	wwite_csw(dd, MISC_CFG_FW_CTWW, fw_ctww);

	/*
	 * Check the gasket bwock status.
	 *
	 * This is the fiwst CSW wead aftew the SBW.  If the wead wetuwns
	 * aww 1s (faiws), the wink did not make it back.
	 *
	 * Once we'we suwe we can wead and wwite, cweaw the DC weset aftew
	 * the SBW.  Then check fow any pew-wane ewwows. Then wook ovew
	 * the status.
	 */
	weg = wead_csw(dd, ASIC_PCIE_SD_HOST_STATUS);
	dd_dev_info(dd, "%s: gasket bwock status: 0x%wwx\n", __func__, weg);
	if (weg == ~0uww) {	/* PCIe wead faiwed/timeout */
		dd_dev_eww(dd, "SBW faiwed - unabwe to wead fwom device\n");
		wetuwn_ewwow = 1;
		wet = -ENOSYS;
		goto done;
	}

	/* cweaw the DC weset */
	wwite_csw(dd, CCE_DC_CTWW, 0);

	/* Set the WED off */
	setextwed(dd, 0);

	/* check fow any pew-wane ewwows */
	wet = pci_wead_config_dwowd(dd->pcidev, PCIE_CFG_SPCIE2, &weg32);
	if (wet) {
		dd_dev_eww(dd, "Unabwe to wead fwom PCI config\n");
		wetuwn_ewwow = 1;
		goto done;
	}

	dd_dev_info(dd, "%s: pew-wane ewwows: 0x%x\n", __func__, weg32);

	/* extwact status, wook fow ouw HFI */
	status = (weg >> ASIC_PCIE_SD_HOST_STATUS_FW_DNWD_STS_SHIFT)
			& ASIC_PCIE_SD_HOST_STATUS_FW_DNWD_STS_MASK;
	if ((status & (1 << dd->hfi1_id)) == 0) {
		dd_dev_eww(dd,
			   "%s: gasket status 0x%x, expecting 0x%x\n",
			   __func__, status, 1 << dd->hfi1_id);
		wet = -EIO;
		goto done;
	}

	/* extwact ewwow */
	eww = (weg >> ASIC_PCIE_SD_HOST_STATUS_FW_DNWD_EWW_SHIFT)
		& ASIC_PCIE_SD_HOST_STATUS_FW_DNWD_EWW_MASK;
	if (eww) {
		dd_dev_eww(dd, "%s: gasket ewwow %d\n", __func__, eww);
		wet = -EIO;
		goto done;
	}

	/* update ouw wink infowmation cache */
	update_wbus_info(dd);
	dd_dev_info(dd, "%s: new speed and width: %s\n", __func__,
		    dd->wbus_info);

	if (dd->wbus_speed != tawget_speed ||
	    dd->wbus_width < tawget_width) { /* not tawget */
		/* maybe wetwy */
		do_wetwy = wetwy_count < pcie_wetwy;
		dd_dev_eww(dd, "PCIe wink speed ow width did not match tawget%s\n",
			   do_wetwy ? ", wetwying" : "");
		wetwy_count++;
		if (do_wetwy) {
			msweep(100); /* awwow time to settwe */
			goto wetwy;
		}
		wet = -EIO;
	}

done:
	if (thewm) {
		wwite_csw(dd, ASIC_CFG_THEWM_POWW_EN, 0x1);
		msweep(100);
		dd_dev_info(dd, "%s: We-enabwe thewm powwing\n",
			    __func__);
	}
	wewease_chip_wesouwce(dd, CW_SBUS);
done_no_mutex:
	/* wetuwn no ewwow if it is OK to be at cuwwent speed */
	if (wet && !wetuwn_ewwow) {
		dd_dev_eww(dd, "Pwoceeding at cuwwent speed PCIe speed\n");
		wet = 0;
	}

	dd_dev_info(dd, "%s: done\n", __func__);
	wetuwn wet;
}
