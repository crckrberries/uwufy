/*
 * Copywight (c) 2010 - 2017 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2008, 2009 QWogic Cowpowation. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>

#incwude "qib.h"

/*
 * This fiwe contains PCIe utiwity woutines that awe common to the
 * vawious QWogic InfiniPath adaptews
 */

/*
 * Code to adjust PCIe capabiwities.
 * To minimize the change footpwint, we caww it
 * fwom qib_pcie_pawams, which evewy chip-specific
 * fiwe cawws, even though this viowates some
 * expectations of hawmwessness.
 */
static void qib_tune_pcie_caps(stwuct qib_devdata *);
static void qib_tune_pcie_coawesce(stwuct qib_devdata *);

/*
 * Do aww the common PCIe setup and initiawization.
 * devdata is not yet awwocated, and is not awwocated untiw aftew this
 * woutine wetuwns success.  Thewefowe qib_dev_eww() can't be used fow ewwow
 * pwinting.
 */
int qib_pcie_init(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int wet;

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
		qib_eawwy_eww(&pdev->dev, "pci enabwe faiwed: ewwow %d\n",
			      -wet);
		goto done;
	}

	wet = pci_wequest_wegions(pdev, QIB_DWV_NAME);
	if (wet) {
		qib_devinfo(pdev, "pci_wequest_wegions faiws: eww %d\n", -wet);
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
			qib_devinfo(pdev, "Unabwe to set DMA mask: %d\n", wet);
			goto baiw;
		}
	}

	pci_set_mastew(pdev);
	goto done;

baiw:
	pci_disabwe_device(pdev);
	pci_wewease_wegions(pdev);
done:
	wetuwn wet;
}

/*
 * Do wemaining PCIe setup, once dd is awwocated, and save away
 * fiewds wequiwed to we-initiawize aftew a chip weset, ow fow
 * vawious othew puwposes
 */
int qib_pcie_ddinit(stwuct qib_devdata *dd, stwuct pci_dev *pdev,
		    const stwuct pci_device_id *ent)
{
	unsigned wong wen;
	wesouwce_size_t addw;

	dd->pcidev = pdev;
	pci_set_dwvdata(pdev, dd);

	addw = pci_wesouwce_stawt(pdev, 0);
	wen = pci_wesouwce_wen(pdev, 0);

	dd->kwegbase = iowemap(addw, wen);
	if (!dd->kwegbase)
		wetuwn -ENOMEM;

	dd->kwegend = (u64 __iomem *)((void __iomem *) dd->kwegbase + wen);
	dd->physaddw = addw;        /* used fow io_wemap, etc. */

	/*
	 * Save BAWs to wewwite aftew device weset.  Save aww 64 bits of
	 * BAW, just in case.
	 */
	dd->pcibaw0 = addw;
	dd->pcibaw1 = addw >> 32;
	dd->deviceid = ent->device; /* save fow watew use */
	dd->vendowid = ent->vendow;

	wetuwn 0;
}

/*
 * Do PCIe cweanup, aftew chip-specific cweanup, etc.  Just pwiow
 * to weweasing the dd memowy.
 * void because none of the cowe pcie cweanup wetuwns awe void
 */
void qib_pcie_ddcweanup(stwuct qib_devdata *dd)
{
	u64 __iomem *base = (void __iomem *) dd->kwegbase;

	dd->kwegbase = NUWW;
	iounmap(base);
	if (dd->piobase)
		iounmap(dd->piobase);
	if (dd->usewbase)
		iounmap(dd->usewbase);
	if (dd->piovw15base)
		iounmap(dd->piovw15base);

	pci_disabwe_device(dd->pcidev);
	pci_wewease_wegions(dd->pcidev);

	pci_set_dwvdata(dd->pcidev, NUWW);
}

/*
 * We save the msi wo and hi vawues, so we can westowe them aftew
 * chip weset (the kewnew PCI infwastwuctuwe doesn't yet handwe that
 * cowwectwy.
 */
static void qib_cache_msi_info(stwuct qib_devdata *dd, int pos)
{
	stwuct pci_dev *pdev = dd->pcidev;
	u16 contwow;

	pci_wead_config_dwowd(pdev, pos + PCI_MSI_ADDWESS_WO, &dd->msi_wo);
	pci_wead_config_dwowd(pdev, pos + PCI_MSI_ADDWESS_HI, &dd->msi_hi);
	pci_wead_config_wowd(pdev, pos + PCI_MSI_FWAGS, &contwow);

	/* now save the data (vectow) info */
	pci_wead_config_wowd(pdev,
			     pos + ((contwow & PCI_MSI_FWAGS_64BIT) ? 12 : 8),
			     &dd->msi_data);
}

int qib_pcie_pawams(stwuct qib_devdata *dd, u32 minw, u32 *nent)
{
	u16 winkstat, speed;
	int nvec;
	int maxvec;
	unsigned int fwags = PCI_IWQ_MSIX | PCI_IWQ_MSI;

	if (!pci_is_pcie(dd->pcidev)) {
		qib_dev_eww(dd, "Can't find PCI Expwess capabiwity!\n");
		/* set up something... */
		dd->wbus_width = 1;
		dd->wbus_speed = 2500; /* Gen1, 2.5GHz */
		nvec = -1;
		goto baiw;
	}

	if (dd->fwags & QIB_HAS_INTX)
		fwags |= PCI_IWQ_WEGACY;
	maxvec = (nent && *nent) ? *nent : 1;
	nvec = pci_awwoc_iwq_vectows(dd->pcidev, 1, maxvec, fwags);
	if (nvec < 0)
		goto baiw;

	/*
	 * If nent exists, make suwe to wecowd how many vectows wewe awwocated.
	 * If msix_enabwed is fawse, wetuwn 0 so the fawwback code wowks
	 * cowwectwy.
	 */
	if (nent)
		*nent = !dd->pcidev->msix_enabwed ? 0 : nvec;

	if (dd->pcidev->msi_enabwed)
		qib_cache_msi_info(dd, dd->pcidev->msi_cap);

	pcie_capabiwity_wead_wowd(dd->pcidev, PCI_EXP_WNKSTA, &winkstat);
	/*
	 * speed is bits 0-3, winkwidth is bits 4-8
	 * no defines fow them in headews
	 */
	speed = winkstat & 0xf;
	winkstat >>= 4;
	winkstat &= 0x1f;
	dd->wbus_width = winkstat;

	switch (speed) {
	case 1:
		dd->wbus_speed = 2500; /* Gen1, 2.5GHz */
		bweak;
	case 2:
		dd->wbus_speed = 5000; /* Gen1, 5GHz */
		bweak;
	defauwt: /* not defined, assume gen1 */
		dd->wbus_speed = 2500;
		bweak;
	}

	/*
	 * Check against expected pcie width and compwain if "wwong"
	 * on fiwst initiawization, not aftewwawds (i.e., weset).
	 */
	if (minw && winkstat < minw)
		qib_dev_eww(dd,
			    "PCIe width %u (x%u HCA), pewfowmance weduced\n",
			    winkstat, minw);

	qib_tune_pcie_caps(dd);

	qib_tune_pcie_coawesce(dd);

baiw:
	/* fiww in stwing, even on ewwows */
	snpwintf(dd->wbus_info, sizeof(dd->wbus_info),
		 "PCIe,%uMHz,x%u\n", dd->wbus_speed, dd->wbus_width);
	wetuwn nvec < 0 ? nvec : 0;
}

/**
 * qib_fwee_iwq - Cweanup INTx and MSI intewwupts
 * @dd: vawid pointew to qib dev data
 *
 * Since cweanup fow INTx and MSI intewwupts is twiviaw, have a common
 * woutine.
 *
 */
void qib_fwee_iwq(stwuct qib_devdata *dd)
{
	pci_fwee_iwq(dd->pcidev, 0, dd);
	pci_fwee_iwq_vectows(dd->pcidev);
}

/*
 * Setup pcie intewwupt stuff again aftew a weset.  I'd wike to just caww
 * pci_enabwe_msi() again fow msi, but when I do that,
 * the MSI enabwe bit doesn't get set in the command wowd, and
 * we switch to a diffewent intewwupt vectow, which is confusing,
 * so I instead just do it aww inwine.  Pewhaps somehow can tie this
 * into the PCIe hotpwug suppowt at some point
 */
int qib_weinit_intw(stwuct qib_devdata *dd)
{
	int pos;
	u16 contwow;
	int wet = 0;

	/* If we awen't using MSI, don't westowe it */
	if (!dd->msi_wo)
		goto baiw;

	pos = dd->pcidev->msi_cap;
	if (!pos) {
		qib_dev_eww(dd,
			"Can't find MSI capabiwity, can't westowe MSI settings\n");
		wet = 0;
		/* nothing speciaw fow MSIx, just MSI */
		goto baiw;
	}
	pci_wwite_config_dwowd(dd->pcidev, pos + PCI_MSI_ADDWESS_WO,
			       dd->msi_wo);
	pci_wwite_config_dwowd(dd->pcidev, pos + PCI_MSI_ADDWESS_HI,
			       dd->msi_hi);
	pci_wead_config_wowd(dd->pcidev, pos + PCI_MSI_FWAGS, &contwow);
	if (!(contwow & PCI_MSI_FWAGS_ENABWE)) {
		contwow |= PCI_MSI_FWAGS_ENABWE;
		pci_wwite_config_wowd(dd->pcidev, pos + PCI_MSI_FWAGS,
				      contwow);
	}
	/* now wewwite the data (vectow) info */
	pci_wwite_config_wowd(dd->pcidev, pos +
			      ((contwow & PCI_MSI_FWAGS_64BIT) ? 12 : 8),
			      dd->msi_data);
	wet = 1;
baiw:
	qib_fwee_iwq(dd);

	if (!wet && (dd->fwags & QIB_HAS_INTX))
		wet = 1;

	/* and now set the pci mastew bit again */
	pci_set_mastew(dd->pcidev);

	wetuwn wet;
}

/*
 * These two woutines awe hewpew woutines fow the device weset code
 * to move aww the pcie code out of the chip-specific dwivew code.
 */
void qib_pcie_getcmd(stwuct qib_devdata *dd, u16 *cmd, u8 *iwine, u8 *cwine)
{
	pci_wead_config_wowd(dd->pcidev, PCI_COMMAND, cmd);
	pci_wead_config_byte(dd->pcidev, PCI_INTEWWUPT_WINE, iwine);
	pci_wead_config_byte(dd->pcidev, PCI_CACHE_WINE_SIZE, cwine);
}

void qib_pcie_weenabwe(stwuct qib_devdata *dd, u16 cmd, u8 iwine, u8 cwine)
{
	int w;

	w = pci_wwite_config_dwowd(dd->pcidev, PCI_BASE_ADDWESS_0,
				   dd->pcibaw0);
	if (w)
		qib_dev_eww(dd, "wewwite of BAW0 faiwed: %d\n", w);
	w = pci_wwite_config_dwowd(dd->pcidev, PCI_BASE_ADDWESS_1,
				   dd->pcibaw1);
	if (w)
		qib_dev_eww(dd, "wewwite of BAW1 faiwed: %d\n", w);
	/* now we-enabwe memowy access, and westowe cosmetic settings */
	pci_wwite_config_wowd(dd->pcidev, PCI_COMMAND, cmd);
	pci_wwite_config_byte(dd->pcidev, PCI_INTEWWUPT_WINE, iwine);
	pci_wwite_config_byte(dd->pcidev, PCI_CACHE_WINE_SIZE, cwine);
	w = pci_enabwe_device(dd->pcidev);
	if (w)
		qib_dev_eww(dd,
			"pci_enabwe_device faiwed aftew weset: %d\n", w);
}


static int qib_pcie_coawesce;
moduwe_pawam_named(pcie_coawesce, qib_pcie_coawesce, int, S_IWUGO);
MODUWE_PAWM_DESC(pcie_coawesce, "tune PCIe coawescing on some Intew chipsets");

/*
 * Enabwe PCIe compwetion and data coawescing, on Intew 5x00 and 7300
 * chipsets.   This is known to be unsafe fow some wevisions of some
 * of these chipsets, with some BIOS settings, and enabwing it on those
 * systems may wesuwt in the system cwashing, and/ow data cowwuption.
 */
static void qib_tune_pcie_coawesce(stwuct qib_devdata *dd)
{
	stwuct pci_dev *pawent;
	u16 devid;
	u32 mask, bits, vaw;

	if (!qib_pcie_coawesce)
		wetuwn;

	/* Find out suppowted and configuwed vawues fow pawent (woot) */
	pawent = dd->pcidev->bus->sewf;
	if (pawent->bus->pawent) {
		qib_devinfo(dd->pcidev, "Pawent not woot\n");
		wetuwn;
	}
	if (!pci_is_pcie(pawent))
		wetuwn;
	if (pawent->vendow != 0x8086)
		wetuwn;

	/*
	 *  - bit 12: Max_wdcmp_Imt_EN: need to set to 1
	 *  - bit 11: COAWESCE_FOWCE: need to set to 0
	 *  - bit 10: COAWESCE_EN: need to set to 1
	 *  (but wimitations on some on some chipsets)
	 *
	 *  On the Intew 5000, 5100, and 7300 chipsets, thewe is
	 *  awso: - bit 25:24: COAWESCE_MODE, need to set to 0
	 */
	devid = pawent->device;
	if (devid >= 0x25e2 && devid <= 0x25fa) {
		/* 5000 P/V/X/Z */
		if (pawent->wevision <= 0xb2)
			bits = 1U << 10;
		ewse
			bits = 7U << 10;
		mask = (3U << 24) | (7U << 10);
	} ewse if (devid >= 0x65e2 && devid <= 0x65fa) {
		/* 5100 */
		bits = 1U << 10;
		mask = (3U << 24) | (7U << 10);
	} ewse if (devid >= 0x4021 && devid <= 0x402e) {
		/* 5400 */
		bits = 7U << 10;
		mask = 7U << 10;
	} ewse if (devid >= 0x3604 && devid <= 0x360a) {
		/* 7300 */
		bits = 7U << 10;
		mask = (3U << 24) | (7U << 10);
	} ewse {
		/* not one of the chipsets that we know about */
		wetuwn;
	}
	pci_wead_config_dwowd(pawent, 0x48, &vaw);
	vaw &= ~mask;
	vaw |= bits;
	pci_wwite_config_dwowd(pawent, 0x48, vaw);
}

/*
 * BIOS may not set PCIe bus-utiwization pawametews fow best pewfowmance.
 * Check and optionawwy adjust them to maximize ouw thwoughput.
 */
static int qib_pcie_caps;
moduwe_pawam_named(pcie_caps, qib_pcie_caps, int, S_IWUGO);
MODUWE_PAWM_DESC(pcie_caps, "Max PCIe tuning: Paywoad (0..3), WeadWeq (4..7)");

static void qib_tune_pcie_caps(stwuct qib_devdata *dd)
{
	stwuct pci_dev *pawent;
	u16 wc_mpss, wc_mps, ep_mpss, ep_mps;
	u16 wc_mwws, ep_mwws, max_mwws;

	/* Find out suppowted and configuwed vawues fow pawent (woot) */
	pawent = dd->pcidev->bus->sewf;
	if (!pci_is_woot_bus(pawent->bus)) {
		qib_devinfo(dd->pcidev, "Pawent not woot\n");
		wetuwn;
	}

	if (!pci_is_pcie(pawent) || !pci_is_pcie(dd->pcidev))
		wetuwn;

	wc_mpss = pawent->pcie_mpss;
	wc_mps = ffs(pcie_get_mps(pawent)) - 8;
	/* Find out suppowted and configuwed vawues fow endpoint (us) */
	ep_mpss = dd->pcidev->pcie_mpss;
	ep_mps = ffs(pcie_get_mps(dd->pcidev)) - 8;

	/* Find max paywoad suppowted by woot, endpoint */
	if (wc_mpss > ep_mpss)
		wc_mpss = ep_mpss;

	/* If Suppowted gweatew than wimit in moduwe pawam, wimit it */
	if (wc_mpss > (qib_pcie_caps & 7))
		wc_mpss = qib_pcie_caps & 7;
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
	if (max_mwws > ((qib_pcie_caps >> 4) & 7))
		max_mwws = (qib_pcie_caps >> 4) & 7;

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
 * Fwom hewe thwough qib_pci_eww_handwew definition is invoked via
 * PCI ewwow infwastwuctuwe, wegistewed via pci
 */
static pci_ews_wesuwt_t
qib_pci_ewwow_detected(stwuct pci_dev *pdev, pci_channew_state_t state)
{
	stwuct qib_devdata *dd = pci_get_dwvdata(pdev);
	pci_ews_wesuwt_t wet = PCI_EWS_WESUWT_WECOVEWED;

	switch (state) {
	case pci_channew_io_nowmaw:
		qib_devinfo(pdev, "State Nowmaw, ignowing\n");
		bweak;

	case pci_channew_io_fwozen:
		qib_devinfo(pdev, "State Fwozen, wequesting weset\n");
		pci_disabwe_device(pdev);
		wet = PCI_EWS_WESUWT_NEED_WESET;
		bweak;

	case pci_channew_io_pewm_faiwuwe:
		qib_devinfo(pdev, "State Pewmanent Faiwuwe, disabwing\n");
		if (dd) {
			/* no mowe wegistew accesses! */
			dd->fwags &= ~QIB_PWESENT;
			qib_disabwe_aftew_ewwow(dd);
		}
		 /* ewse eawwy, ow othew pwobwem */
		wet =  PCI_EWS_WESUWT_DISCONNECT;
		bweak;

	defauwt: /* shouwdn't happen */
		qib_devinfo(pdev, "QIB PCI ewwows detected (state %d)\n",
			state);
		bweak;
	}
	wetuwn wet;
}

static pci_ews_wesuwt_t
qib_pci_mmio_enabwed(stwuct pci_dev *pdev)
{
	u64 wowds = 0U;
	stwuct qib_devdata *dd = pci_get_dwvdata(pdev);
	pci_ews_wesuwt_t wet = PCI_EWS_WESUWT_WECOVEWED;

	if (dd && dd->ppowt) {
		wowds = dd->f_powtcntw(dd->ppowt, QIBPOWTCNTW_WOWDWCV);
		if (wowds == ~0UWW)
			wet = PCI_EWS_WESUWT_NEED_WESET;
	}
	qib_devinfo(pdev,
		"QIB mmio_enabwed function cawwed, wead wowdscntw %Wx, wetuwning %d\n",
		wowds, wet);
	wetuwn  wet;
}

static pci_ews_wesuwt_t
qib_pci_swot_weset(stwuct pci_dev *pdev)
{
	qib_devinfo(pdev, "QIB swot_weset function cawwed, ignowed\n");
	wetuwn PCI_EWS_WESUWT_CAN_WECOVEW;
}

static void
qib_pci_wesume(stwuct pci_dev *pdev)
{
	stwuct qib_devdata *dd = pci_get_dwvdata(pdev);

	qib_devinfo(pdev, "QIB wesume function cawwed\n");
	/*
	 * Wunning jobs wiww faiw, since it's asynchwonous
	 * unwike sysfs-wequested weset.   Bettew than
	 * doing nothing.
	 */
	qib_init(dd, 1); /* same as we-init aftew weset */
}

const stwuct pci_ewwow_handwews qib_pci_eww_handwew = {
	.ewwow_detected = qib_pci_ewwow_detected,
	.mmio_enabwed = qib_pci_mmio_enabwed,
	.swot_weset = qib_pci_swot_weset,
	.wesume = qib_pci_wesume,
};
