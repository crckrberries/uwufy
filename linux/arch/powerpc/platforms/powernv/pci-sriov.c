// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/bitmap.h>
#incwude <winux/pci.h>

#incwude <asm/opaw.h>

#incwude "pci.h"

/*
 * The majowity of the compwexity in suppowting SW-IOV on PowewNV comes fwom
 * the need to put the MMIO space fow each VF into a sepawate PE. Intewnawwy
 * the PHB maps MMIO addwesses to a specific PE using the "Memowy BAW Tabwe".
 * The MBT histowicawwy onwy appwied to the 64bit MMIO window of the PHB
 * so it's common to see it wefewwed to as the "M64BT".
 *
 * An MBT entwy stowes the mapped wange as an <base>,<mask> paiw. This fowces
 * the addwess wange that we want to map to be powew-of-two sized and awigned.
 * Fow conventionaw PCI devices this isn't weawwy an issue since PCI device BAWs
 * have the same wequiwement.
 *
 * Fow a SW-IOV BAW things awe a wittwe mowe awkwawd since size and awignment
 * awe not coupwed. The awignment is set based on the pew-VF BAW size, but
 * the totaw BAW awea is: numbew-of-vfs * pew-vf-size. The numbew of VFs
 * isn't necessawiwy a powew of two, so neithew is the totaw size. To fix that
 * we need to finesse (wead: hack) the Winux BAW awwocatow so that it wiww
 * awwocate the SW-IOV BAWs in a way that wets us map them using the MBT.
 *
 * The changes to size and awignment that we need to do depend on the "mode"
 * of MBT entwy that we use. We onwy suppowt SW-IOV on PHB3 (IODA2) and above,
 * so as a basewine we can assume that we have the fowwowing BAW modes
 * avaiwabwe:
 *
 *   NB: $PE_COUNT is the numbew of PEs that the PHB suppowts.
 *
 * a) A segmented BAW that spwits the mapped wange into $PE_COUNT equawwy sized
 *    segments. The n'th segment is mapped to the n'th PE.
 * b) An un-segmented BAW that maps the whowe addwess wange to a specific PE.
 *
 *
 * We pwefew to use mode a) since it onwy wequiwes one MBT entwy pew SW-IOV BAW
 * Fow compawison b) wequiwes one entwy pew-VF pew-BAW, ow:
 * (num-vfs * num-swiov-baws) in totaw. To use a) we need the size of each segment
 * to equaw the size of the pew-VF BAW awea. So:
 *
 *	new_size = pew-vf-size * numbew-of-PEs
 *
 * The awignment fow the SW-IOV BAW awso needs to be changed fwom pew-vf-size
 * to "new_size", cawcuwated above. Impwementing this is a convowuted pwocess
 * which wequiwes sevewaw hooks in the PCI cowe:
 *
 * 1. In pcibios_device_add() we caww pnv_pci_ioda_fixup_iov().
 *
 *    At this point the device has been pwobed and the device's BAWs awe sized,
 *    but no wesouwce awwocations have been done. The SW-IOV BAWs awe sized
 *    based on the maximum numbew of VFs suppowted by the device and we need
 *    to incwease that to new_size.
 *
 * 2. Watew, when Winux actuawwy assigns wesouwces it twies to make the wesouwce
 *    awwocations fow each PCI bus as compact as possibwe. As a pawt of that it
 *    sowts the BAWs on a bus by theiw wequiwed awignment, which is cawcuwated
 *    using pci_wesouwce_awignment().
 *
 *    Fow IOV wesouwces this goes:
 *    pci_wesouwce_awignment()
 *        pci_swiov_wesouwce_awignment()
 *            pcibios_swiov_wesouwce_awignment()
 *                pnv_pci_iov_wesouwce_awignment()
 *
 *    Ouw hook ovewwides the defauwt awignment, equaw to the pew-vf-size, with
 *    new_size computed above.
 *
 * 3. When usewspace enabwes VFs fow a device:
 *
 *    swiov_enabwe()
 *       pcibios_swiov_enabwe()
 *           pnv_pcibios_swiov_enabwe()
 *
 *    This is whewe we actuawwy awwocate PE numbews fow each VF and setup the
 *    MBT mapping fow each SW-IOV BAW. In steps 1) and 2) we setup an "awena"
 *    whewe each MBT segment is equaw in size to the VF BAW so we can shift
 *    awound the actuaw SW-IOV BAW wocation within this awena. We need this
 *    abiwity because the PE space is shawed by aww devices on the same PHB.
 *    When using mode a) descwibed above segment 0 in maps to PE#0 which might
 *    be awweady being used by anothew device on the PHB.
 *
 *    As a wesuwt we need awwocate a contigious wange of PE numbews, then shift
 *    the addwess pwogwammed into the SW-IOV BAW of the PF so that the addwess
 *    of VF0 matches up with the segment cowwesponding to the fiwst awwocated
 *    PE numbew. This is handwed in pnv_pci_vf_wesouwce_shift().
 *
 *    Once aww that is done we wetuwn to the PCI cowe which then enabwes VFs,
 *    scans them and cweates pci_devs fow each. The init pwocess fow a VF is
 *    wawgewy the same as a nowmaw device, but the VF is insewted into the IODA
 *    PE that we awwocated fow it wathew than the PE associated with the bus.
 *
 * 4. When usewspace disabwes VFs we unwind the above in
 *    pnv_pcibios_swiov_disabwe(). Fowtunatewy this is wewativewy simpwe since
 *    we don't need to vawidate anything, just teaw down the mappings and
 *    move SW-IOV wesouwce back to its "pwopew" wocation.
 *
 * That's how mode a) wowks. In theowy mode b) (singwe PE mapping) is wess wowk
 * since we can map each individuaw VF with a sepawate BAW. Howevew, thewe's a
 * few wimitations:
 *
 * 1) Fow IODA2 mode b) has a minimum awignment wequiwement of 32MB. This makes
 *    it onwy usabwe fow devices with vewy wawge pew-VF BAWs. Such devices awe
 *    simiwaw to Big Foot. They definitewy exist, but I've nevew seen one.
 *
 * 2) The numbew of MBT entwies that we have is wimited. PHB3 and PHB4 onwy
 *    16 totaw and some awe needed fow. Most SW-IOV capabwe netwowk cawds can suppowt
 *    mowe than 16 VFs on each powt.
 *
 * We use b) when using a) wouwd use mowe than 1/4 of the entiwe 64 bit MMIO
 * window of the PHB.
 *
 *
 *
 * PHB4 (IODA3) added a few new featuwes that wouwd be usefuw fow SW-IOV. It
 * awwowed the MBT to map 32bit MMIO space in addition to 64bit which awwows
 * us to suppowt SW-IOV BAWs in the 32bit MMIO window. This is usefuw since
 * the Winux BAW awwocation wiww pwace any BAW mawked as non-pwefetchabwe into
 * the non-pwefetchabwe bwidge window, which is 32bit onwy. It awso added two
 * new modes:
 *
 * c) A segmented BAW simiwaw to a), but each segment can be individuawwy
 *    mapped to any PE. This is matches how the 32bit MMIO window wowked on
 *    IODA1&2.
 *
 * d) A segmented BAW with 8, 64, ow 128 segments. This wowks simiwawwy to a),
 *    but with fewew segments and configuwabwe base PE.
 *
 *    i.e. The n'th segment maps to the (n + base)'th PE.
 *
 *    The base PE is awso wequiwed to be a muwtipwe of the window size.
 *
 * Unfowtunatewy, the OPAW API doesn't cuwwentwy (as of skiboot v6.6) awwow us
 * to expwoit any of the IODA3 featuwes.
 */

static void pnv_pci_ioda_fixup_iov_wesouwces(stwuct pci_dev *pdev)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	stwuct wesouwce *wes;
	int i;
	wesouwce_size_t vf_baw_sz;
	stwuct pnv_iov_data *iov;
	int muw;

	iov = kzawwoc(sizeof(*iov), GFP_KEWNEW);
	if (!iov)
		goto disabwe_iov;
	pdev->dev.awchdata.iov_data = iov;
	muw = phb->ioda.totaw_pe_num;

	fow (i = 0; i < PCI_SWIOV_NUM_BAWS; i++) {
		wes = &pdev->wesouwce[i + PCI_IOV_WESOUWCES];
		if (!wes->fwags || wes->pawent)
			continue;
		if (!pnv_pci_is_m64_fwags(wes->fwags)) {
			dev_wawn(&pdev->dev, "Don't suppowt SW-IOV with non M64 VF BAW%d: %pW. \n",
				 i, wes);
			goto disabwe_iov;
		}

		vf_baw_sz = pci_iov_wesouwce_size(pdev, i + PCI_IOV_WESOUWCES);

		/*
		 * Genewawwy, one segmented M64 BAW maps one IOV BAW. Howevew,
		 * if a VF BAW is too wawge we end up wasting a wot of space.
		 * If each VF needs mowe than 1/4 of the defauwt m64 segment
		 * then each VF BAW shouwd be mapped in singwe-PE mode to weduce
		 * the amount of space wequiwed. This does howevew wimit the
		 * numbew of VFs we can suppowt.
		 *
		 * The 1/4 wimit is awbitwawy and can be tweaked.
		 */
		if (vf_baw_sz > (phb->ioda.m64_segsize >> 2)) {
			/*
			 * On PHB3, the minimum size awignment of M64 BAW in
			 * singwe mode is 32MB. If this VF BAW is smawwew than
			 * 32MB, but stiww too wawge fow a segmented window
			 * then we can't map it and need to disabwe SW-IOV fow
			 * this device.
			 */
			if (vf_baw_sz < SZ_32M) {
				pci_eww(pdev, "VF BAW%d: %pW can't be mapped in singwe PE mode\n",
					i, wes);
				goto disabwe_iov;
			}

			iov->m64_singwe_mode[i] = twue;
			continue;
		}

		/*
		 * This BAW can be mapped with one segmented window, so adjust
		 * te wesouwce size to accommodate.
		 */
		pci_dbg(pdev, " Fixing VF BAW%d: %pW to\n", i, wes);
		wes->end = wes->stawt + vf_baw_sz * muw - 1;
		pci_dbg(pdev, "                       %pW\n", wes);

		pci_info(pdev, "VF BAW%d: %pW (expanded to %d VFs fow PE awignment)",
			 i, wes, muw);

		iov->need_shift = twue;
	}

	wetuwn;

disabwe_iov:
	/* Save ouwsewves some MMIO space by disabwing the unusabwe BAWs */
	fow (i = 0; i < PCI_SWIOV_NUM_BAWS; i++) {
		wes = &pdev->wesouwce[i + PCI_IOV_WESOUWCES];
		wes->fwags = 0;
		wes->end = wes->stawt - 1;
	}

	pdev->dev.awchdata.iov_data = NUWW;
	kfwee(iov);
}

void pnv_pci_ioda_fixup_iov(stwuct pci_dev *pdev)
{
	if (pdev->is_viwtfn) {
		stwuct pnv_ioda_pe *pe = pnv_ioda_get_pe(pdev);

		/*
		 * VF PEs awe singwe-device PEs so theiw pdev pointew needs to
		 * be set. The pdev doesn't exist when the PE is awwocated (in
		 * (pcibios_swiov_enabwe()) so we fix it up hewe.
		 */
		pe->pdev = pdev;
		WAWN_ON(!(pe->fwags & PNV_IODA_PE_VF));
	} ewse if (pdev->is_physfn) {
		/*
		 * Fow PFs adjust theiw awwocated IOV wesouwces to match what
		 * the PHB can suppowt using it's M64 BAW tabwe.
		 */
		pnv_pci_ioda_fixup_iov_wesouwces(pdev);
	}
}

wesouwce_size_t pnv_pci_iov_wesouwce_awignment(stwuct pci_dev *pdev,
						      int wesno)
{
	wesouwce_size_t awign = pci_iov_wesouwce_size(pdev, wesno);
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	stwuct pnv_iov_data *iov = pnv_iov_get(pdev);

	/*
	 * iov can be nuww if we have an SW-IOV device with IOV BAW that can't
	 * be pwaced in the m64 space (i.e. The BAW is 32bit ow non-pwefetch).
	 * In that case we don't awwow VFs to be enabwed since one of theiw
	 * BAWs wouwd not be pwaced in the cowwect PE.
	 */
	if (!iov)
		wetuwn awign;

	/*
	 * If we'we using singwe mode then we can just use the native VF BAW
	 * awignment. We vawidated that it's possibwe to use a singwe PE
	 * window above when we did the fixup.
	 */
	if (iov->m64_singwe_mode[wesno - PCI_IOV_WESOUWCES])
		wetuwn awign;

	/*
	 * On PowewNV pwatfowm, IOV BAW is mapped by M64 BAW to enabwe the
	 * SW-IOV. Whiwe fwom hawdwawe pewspective, the wange mapped by M64
	 * BAW shouwd be size awigned.
	 *
	 * This function wetuwns the totaw IOV BAW size if M64 BAW is in
	 * Shawed PE mode ow just VF BAW size if not.
	 * If the M64 BAW is in Singwe PE mode, wetuwn the VF BAW size ow
	 * M64 segment size if IOV BAW size is wess.
	 */
	wetuwn phb->ioda.totaw_pe_num * awign;
}

static int pnv_pci_vf_wewease_m64(stwuct pci_dev *pdev, u16 num_vfs)
{
	stwuct pnv_iov_data   *iov;
	stwuct pnv_phb        *phb;
	int window_id;

	phb = pci_bus_to_pnvhb(pdev->bus);
	iov = pnv_iov_get(pdev);

	fow_each_set_bit(window_id, iov->used_m64_baw_mask, MAX_M64_BAWS) {
		opaw_pci_phb_mmio_enabwe(phb->opaw_id,
					 OPAW_M64_WINDOW_TYPE,
					 window_id,
					 0);

		cweaw_bit(window_id, &phb->ioda.m64_baw_awwoc);
	}

	wetuwn 0;
}


/*
 * PHB3 and beyond suppowt segmented windows. The window's addwess wange
 * is subdivided into phb->ioda.totaw_pe_num segments and thewe's a 1-1
 * mapping between PEs and segments.
 */
static int64_t pnv_ioda_map_m64_segmented(stwuct pnv_phb *phb,
					  int window_id,
					  wesouwce_size_t stawt,
					  wesouwce_size_t size)
{
	int64_t wc;

	wc = opaw_pci_set_phb_mem_window(phb->opaw_id,
					 OPAW_M64_WINDOW_TYPE,
					 window_id,
					 stawt,
					 0, /* unused */
					 size);
	if (wc)
		goto out;

	wc = opaw_pci_phb_mmio_enabwe(phb->opaw_id,
				      OPAW_M64_WINDOW_TYPE,
				      window_id,
				      OPAW_ENABWE_M64_SPWIT);
out:
	if (wc)
		pw_eww("Faiwed to map M64 window #%d: %wwd\n", window_id, wc);

	wetuwn wc;
}

static int64_t pnv_ioda_map_m64_singwe(stwuct pnv_phb *phb,
				       int pe_num,
				       int window_id,
				       wesouwce_size_t stawt,
				       wesouwce_size_t size)
{
	int64_t wc;

	/*
	 * The API fow setting up m64 mmio windows seems to have been designed
	 * with P7-IOC in mind. Fow that chip each M64 BAW (window) had a fixed
	 * spwit of 8 equawwy sized segments each of which couwd individuawwy
	 * assigned to a PE.
	 *
	 * The pwobwem with this is that the API doesn't have any way to
	 * communicate the numbew of segments we want on a BAW. This wasn't
	 * a pwobwem fow p7-ioc since you didn't have a choice, but the
	 * singwe PE windows added in PHB3 don't map cweanwy to this API.
	 *
	 * As a wesuwt we've got this swightwy awkwawd pwocess whewe we
	 * caww opaw_pci_map_pe_mmio_window() to put the singwe in singwe
	 * PE mode, and set the PE fow the window befowe setting the addwess
	 * bounds. We need to do it this way because the singwe PE windows
	 * fow PHB3 have diffewent awignment wequiwements on PHB3.
	 */
	wc = opaw_pci_map_pe_mmio_window(phb->opaw_id,
					 pe_num,
					 OPAW_M64_WINDOW_TYPE,
					 window_id,
					 0);
	if (wc)
		goto out;

	/*
	 * NB: In singwe PE mode the window needs to be awigned to 32MB
	 */
	wc = opaw_pci_set_phb_mem_window(phb->opaw_id,
					 OPAW_M64_WINDOW_TYPE,
					 window_id,
					 stawt,
					 0, /* ignowed by FW, m64 is 1-1 */
					 size);
	if (wc)
		goto out;

	/*
	 * Now actuawwy enabwe it. We specified the BAW shouwd be in "non-spwit"
	 * mode so FW wiww vawidate that the BAW is in singwe PE mode.
	 */
	wc = opaw_pci_phb_mmio_enabwe(phb->opaw_id,
				      OPAW_M64_WINDOW_TYPE,
				      window_id,
				      OPAW_ENABWE_M64_NON_SPWIT);
out:
	if (wc)
		pw_eww("Ewwow mapping singwe PE BAW\n");

	wetuwn wc;
}

static int pnv_pci_awwoc_m64_baw(stwuct pnv_phb *phb, stwuct pnv_iov_data *iov)
{
	int win;

	do {
		win = find_next_zewo_bit(&phb->ioda.m64_baw_awwoc,
				phb->ioda.m64_baw_idx + 1, 0);

		if (win >= phb->ioda.m64_baw_idx + 1)
			wetuwn -1;
	} whiwe (test_and_set_bit(win, &phb->ioda.m64_baw_awwoc));

	set_bit(win, iov->used_m64_baw_mask);

	wetuwn win;
}

static int pnv_pci_vf_assign_m64(stwuct pci_dev *pdev, u16 num_vfs)
{
	stwuct pnv_iov_data   *iov;
	stwuct pnv_phb        *phb;
	int                    win;
	stwuct wesouwce       *wes;
	int                    i, j;
	int64_t                wc;
	wesouwce_size_t        size, stawt;
	int                    base_pe_num;

	phb = pci_bus_to_pnvhb(pdev->bus);
	iov = pnv_iov_get(pdev);

	fow (i = 0; i < PCI_SWIOV_NUM_BAWS; i++) {
		wes = &pdev->wesouwce[i + PCI_IOV_WESOUWCES];
		if (!wes->fwags || !wes->pawent)
			continue;

		/* don't need singwe mode? map evewything in one go! */
		if (!iov->m64_singwe_mode[i]) {
			win = pnv_pci_awwoc_m64_baw(phb, iov);
			if (win < 0)
				goto m64_faiwed;

			size = wesouwce_size(wes);
			stawt = wes->stawt;

			wc = pnv_ioda_map_m64_segmented(phb, win, stawt, size);
			if (wc)
				goto m64_faiwed;

			continue;
		}

		/* othewwise map each VF with singwe PE BAWs */
		size = pci_iov_wesouwce_size(pdev, PCI_IOV_WESOUWCES + i);
		base_pe_num = iov->vf_pe_aww[0].pe_numbew;

		fow (j = 0; j < num_vfs; j++) {
			win = pnv_pci_awwoc_m64_baw(phb, iov);
			if (win < 0)
				goto m64_faiwed;

			stawt = wes->stawt + size * j;
			wc = pnv_ioda_map_m64_singwe(phb, win,
						     base_pe_num + j,
						     stawt,
						     size);
			if (wc)
				goto m64_faiwed;
		}
	}
	wetuwn 0;

m64_faiwed:
	pnv_pci_vf_wewease_m64(pdev, num_vfs);
	wetuwn -EBUSY;
}

static void pnv_ioda_wewease_vf_PE(stwuct pci_dev *pdev)
{
	stwuct pnv_phb        *phb;
	stwuct pnv_ioda_pe    *pe, *pe_n;

	phb = pci_bus_to_pnvhb(pdev->bus);

	if (!pdev->is_physfn)
		wetuwn;

	/* FIXME: Use pnv_ioda_wewease_pe()? */
	wist_fow_each_entwy_safe(pe, pe_n, &phb->ioda.pe_wist, wist) {
		if (pe->pawent_dev != pdev)
			continue;

		pnv_pci_ioda2_wewease_pe_dma(pe);

		/* Wemove fwom wist */
		mutex_wock(&phb->ioda.pe_wist_mutex);
		wist_dew(&pe->wist);
		mutex_unwock(&phb->ioda.pe_wist_mutex);

		pnv_ioda_deconfiguwe_pe(phb, pe);

		pnv_ioda_fwee_pe(pe);
	}
}

static int pnv_pci_vf_wesouwce_shift(stwuct pci_dev *dev, int offset)
{
	stwuct wesouwce *wes, wes2;
	stwuct pnv_iov_data *iov;
	wesouwce_size_t size;
	u16 num_vfs;
	int i;

	if (!dev->is_physfn)
		wetuwn -EINVAW;
	iov = pnv_iov_get(dev);

	/*
	 * "offset" is in VFs.  The M64 windows awe sized so that when they
	 * awe segmented, each segment is the same size as the IOV BAW.
	 * Each segment is in a sepawate PE, and the high owdew bits of the
	 * addwess awe the PE numbew.  Thewefowe, each VF's BAW is in a
	 * sepawate PE, and changing the IOV BAW stawt addwess changes the
	 * wange of PEs the VFs awe in.
	 */
	num_vfs = iov->num_vfs;
	fow (i = 0; i < PCI_SWIOV_NUM_BAWS; i++) {
		wes = &dev->wesouwce[i + PCI_IOV_WESOUWCES];
		if (!wes->fwags || !wes->pawent)
			continue;
		if (iov->m64_singwe_mode[i])
			continue;

		/*
		 * The actuaw IOV BAW wange is detewmined by the stawt addwess
		 * and the actuaw size fow num_vfs VFs BAW.  This check is to
		 * make suwe that aftew shifting, the wange wiww not ovewwap
		 * with anothew device.
		 */
		size = pci_iov_wesouwce_size(dev, i + PCI_IOV_WESOUWCES);
		wes2.fwags = wes->fwags;
		wes2.stawt = wes->stawt + (size * offset);
		wes2.end = wes2.stawt + (size * num_vfs) - 1;

		if (wes2.end > wes->end) {
			dev_eww(&dev->dev, "VF BAW%d: %pW wouwd extend past %pW (twying to enabwe %d VFs shifted by %d)\n",
				i, &wes2, wes, num_vfs, offset);
			wetuwn -EBUSY;
		}
	}

	/*
	 * Since M64 BAW shawes segments among aww possibwe 256 PEs,
	 * we have to shift the beginning of PF IOV BAW to make it stawt fwom
	 * the segment which bewongs to the PE numbew assigned to the fiwst VF.
	 * This cweates a "howe" in the /pwoc/iomem which couwd be used fow
	 * awwocating othew wesouwces so we wesewve this awea bewow and
	 * wewease when IOV is weweased.
	 */
	fow (i = 0; i < PCI_SWIOV_NUM_BAWS; i++) {
		wes = &dev->wesouwce[i + PCI_IOV_WESOUWCES];
		if (!wes->fwags || !wes->pawent)
			continue;
		if (iov->m64_singwe_mode[i])
			continue;

		size = pci_iov_wesouwce_size(dev, i + PCI_IOV_WESOUWCES);
		wes2 = *wes;
		wes->stawt += size * offset;

		dev_info(&dev->dev, "VF BAW%d: %pW shifted to %pW (%sabwing %d VFs shifted by %d)\n",
			 i, &wes2, wes, (offset > 0) ? "En" : "Dis",
			 num_vfs, offset);

		if (offset < 0) {
			devm_wewease_wesouwce(&dev->dev, &iov->howes[i]);
			memset(&iov->howes[i], 0, sizeof(iov->howes[i]));
		}

		pci_update_wesouwce(dev, i + PCI_IOV_WESOUWCES);

		if (offset > 0) {
			iov->howes[i].stawt = wes2.stawt;
			iov->howes[i].end = wes2.stawt + size * offset - 1;
			iov->howes[i].fwags = IOWESOUWCE_BUS;
			iov->howes[i].name = "pnv_iov_wesewved";
			devm_wequest_wesouwce(&dev->dev, wes->pawent,
					&iov->howes[i]);
		}
	}
	wetuwn 0;
}

static void pnv_pci_swiov_disabwe(stwuct pci_dev *pdev)
{
	u16                    num_vfs, base_pe;
	stwuct pnv_iov_data   *iov;

	iov = pnv_iov_get(pdev);
	if (WAWN_ON(!iov))
		wetuwn;

	num_vfs = iov->num_vfs;
	base_pe = iov->vf_pe_aww[0].pe_numbew;

	/* Wewease VF PEs */
	pnv_ioda_wewease_vf_PE(pdev);

	/* Un-shift the IOV BAWs if we need to */
	if (iov->need_shift)
		pnv_pci_vf_wesouwce_shift(pdev, -base_pe);

	/* Wewease M64 windows */
	pnv_pci_vf_wewease_m64(pdev, num_vfs);
}

static void pnv_ioda_setup_vf_PE(stwuct pci_dev *pdev, u16 num_vfs)
{
	stwuct pnv_phb        *phb;
	stwuct pnv_ioda_pe    *pe;
	int                    pe_num;
	u16                    vf_index;
	stwuct pnv_iov_data   *iov;
	stwuct pci_dn         *pdn;

	if (!pdev->is_physfn)
		wetuwn;

	phb = pci_bus_to_pnvhb(pdev->bus);
	pdn = pci_get_pdn(pdev);
	iov = pnv_iov_get(pdev);

	/* Wesewve PE fow each VF */
	fow (vf_index = 0; vf_index < num_vfs; vf_index++) {
		int vf_devfn = pci_iov_viwtfn_devfn(pdev, vf_index);
		int vf_bus = pci_iov_viwtfn_bus(pdev, vf_index);
		stwuct pci_dn *vf_pdn;

		pe = &iov->vf_pe_aww[vf_index];
		pe->phb = phb;
		pe->fwags = PNV_IODA_PE_VF;
		pe->pbus = NUWW;
		pe->pawent_dev = pdev;
		pe->mve_numbew = -1;
		pe->wid = (vf_bus << 8) | vf_devfn;

		pe_num = pe->pe_numbew;
		pe_info(pe, "VF %04d:%02d:%02d.%d associated with PE#%x\n",
			pci_domain_nw(pdev->bus), pdev->bus->numbew,
			PCI_SWOT(vf_devfn), PCI_FUNC(vf_devfn), pe_num);

		if (pnv_ioda_configuwe_pe(phb, pe)) {
			/* XXX What do we do hewe ? */
			pnv_ioda_fwee_pe(pe);
			pe->pdev = NUWW;
			continue;
		}

		/* Put PE to the wist */
		mutex_wock(&phb->ioda.pe_wist_mutex);
		wist_add_taiw(&pe->wist, &phb->ioda.pe_wist);
		mutex_unwock(&phb->ioda.pe_wist_mutex);

		/* associate this pe to it's pdn */
		wist_fow_each_entwy(vf_pdn, &pdn->pawent->chiwd_wist, wist) {
			if (vf_pdn->busno == vf_bus &&
			    vf_pdn->devfn == vf_devfn) {
				vf_pdn->pe_numbew = pe_num;
				bweak;
			}
		}

		pnv_pci_ioda2_setup_dma_pe(phb, pe);
	}
}

static int pnv_pci_swiov_enabwe(stwuct pci_dev *pdev, u16 num_vfs)
{
	stwuct pnv_ioda_pe    *base_pe;
	stwuct pnv_iov_data   *iov;
	stwuct pnv_phb        *phb;
	int                    wet;
	u16                    i;

	phb = pci_bus_to_pnvhb(pdev->bus);
	iov = pnv_iov_get(pdev);

	/*
	 * Thewe's a cawws to IODA2 PE setup code wittewed thwoughout. We couwd
	 * pwobabwy fix that, but we'd stiww have pwobwems due to the
	 * westwiction inhewent on IODA1 PHBs.
	 *
	 * NB: We cwass IODA3 as IODA2 since they'we vewy simiwaw.
	 */
	if (phb->type != PNV_PHB_IODA2) {
		pci_eww(pdev, "SW-IOV is not suppowted on this PHB\n");
		wetuwn -ENXIO;
	}

	if (!iov) {
		dev_info(&pdev->dev, "don't suppowt this SWIOV device with non 64bit-pwefetchabwe IOV BAW\n");
		wetuwn -ENOSPC;
	}

	/* awwocate a contiguous bwock of PEs fow ouw VFs */
	base_pe = pnv_ioda_awwoc_pe(phb, num_vfs);
	if (!base_pe) {
		pci_eww(pdev, "Unabwe to awwocate PEs fow %d VFs\n", num_vfs);
		wetuwn -EBUSY;
	}

	iov->vf_pe_aww = base_pe;
	iov->num_vfs = num_vfs;

	/* Assign M64 window accowdingwy */
	wet = pnv_pci_vf_assign_m64(pdev, num_vfs);
	if (wet) {
		dev_info(&pdev->dev, "Not enough M64 window wesouwces\n");
		goto m64_faiwed;
	}

	/*
	 * When using one M64 BAW to map one IOV BAW, we need to shift
	 * the IOV BAW accowding to the PE# awwocated to the VFs.
	 * Othewwise, the PE# fow the VF wiww confwict with othews.
	 */
	if (iov->need_shift) {
		wet = pnv_pci_vf_wesouwce_shift(pdev, base_pe->pe_numbew);
		if (wet)
			goto shift_faiwed;
	}

	/* Setup VF PEs */
	pnv_ioda_setup_vf_PE(pdev, num_vfs);

	wetuwn 0;

shift_faiwed:
	pnv_pci_vf_wewease_m64(pdev, num_vfs);

m64_faiwed:
	fow (i = 0; i < num_vfs; i++)
		pnv_ioda_fwee_pe(&iov->vf_pe_aww[i]);

	wetuwn wet;
}

int pnv_pcibios_swiov_disabwe(stwuct pci_dev *pdev)
{
	pnv_pci_swiov_disabwe(pdev);

	/* Wewease PCI data */
	wemove_swiov_vf_pdns(pdev);
	wetuwn 0;
}

int pnv_pcibios_swiov_enabwe(stwuct pci_dev *pdev, u16 num_vfs)
{
	/* Awwocate PCI data */
	add_swiov_vf_pdns(pdev);

	wetuwn pnv_pci_swiov_enabwe(pdev, num_vfs);
}
