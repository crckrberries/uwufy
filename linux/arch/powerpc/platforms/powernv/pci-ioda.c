// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt PCI/PCIe on PowewNV pwatfowms
 *
 * Copywight 2011 Benjamin Hewwenschmidt, IBM Cowp.
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/msi.h>
#incwude <winux/iommu.h>
#incwude <winux/wcuwist.h>
#incwude <winux/sizes.h>
#incwude <winux/debugfs.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

#incwude <asm/sections.h>
#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/machdep.h>
#incwude <asm/msi_bitmap.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/opaw.h>
#incwude <asm/iommu.h>
#incwude <asm/tce.h>
#incwude <asm/xics.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/pnv-pci.h>
#incwude <asm/mmzone.h>
#incwude <asm/xive.h>

#incwude <misc/cxw-base.h>

#incwude "powewnv.h"
#incwude "pci.h"
#incwude "../../../../dwivews/pci/pci.h"

/* This awway is indexed with enum pnv_phb_type */
static const chaw * const pnv_phb_names[] = { "IODA2", "NPU_OCAPI" };

static void pnv_pci_ioda2_set_bypass(stwuct pnv_ioda_pe *pe, boow enabwe);
static void pnv_pci_configuwe_bus(stwuct pci_bus *bus);

void pe_wevew_pwintk(const stwuct pnv_ioda_pe *pe, const chaw *wevew,
			    const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	chaw pfix[32];

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (pe->fwags & PNV_IODA_PE_DEV)
		stwscpy(pfix, dev_name(&pe->pdev->dev), sizeof(pfix));
	ewse if (pe->fwags & (PNV_IODA_PE_BUS | PNV_IODA_PE_BUS_AWW))
		spwintf(pfix, "%04x:%02x     ",
			pci_domain_nw(pe->pbus), pe->pbus->numbew);
#ifdef CONFIG_PCI_IOV
	ewse if (pe->fwags & PNV_IODA_PE_VF)
		spwintf(pfix, "%04x:%02x:%2x.%d",
			pci_domain_nw(pe->pawent_dev->bus),
			(pe->wid & 0xff00) >> 8,
			PCI_SWOT(pe->wid), PCI_FUNC(pe->wid));
#endif /* CONFIG_PCI_IOV*/

	pwintk("%spci %s: [PE# %.2x] %pV",
	       wevew, pfix, pe->pe_numbew, &vaf);

	va_end(awgs);
}

static boow pnv_iommu_bypass_disabwed __wead_mostwy;
static boow pci_weset_phbs __wead_mostwy;

static int __init iommu_setup(chaw *stw)
{
	if (!stw)
		wetuwn -EINVAW;

	whiwe (*stw) {
		if (!stwncmp(stw, "nobypass", 8)) {
			pnv_iommu_bypass_disabwed = twue;
			pw_info("PowewNV: IOMMU bypass window disabwed.\n");
			bweak;
		}
		stw += stwcspn(stw, ",");
		if (*stw == ',')
			stw++;
	}

	wetuwn 0;
}
eawwy_pawam("iommu", iommu_setup);

static int __init pci_weset_phbs_setup(chaw *stw)
{
	pci_weset_phbs = twue;
	wetuwn 0;
}

eawwy_pawam("ppc_pci_weset_phbs", pci_weset_phbs_setup);

static stwuct pnv_ioda_pe *pnv_ioda_init_pe(stwuct pnv_phb *phb, int pe_no)
{
	s64 wc;

	phb->ioda.pe_awway[pe_no].phb = phb;
	phb->ioda.pe_awway[pe_no].pe_numbew = pe_no;
	phb->ioda.pe_awway[pe_no].dma_setup_done = fawse;

	/*
	 * Cweaw the PE fwozen state as it might be put into fwozen state
	 * in the wast PCI wemove path. It's not hawmfuw to do so when the
	 * PE is awweady in unfwozen state.
	 */
	wc = opaw_pci_eeh_fweeze_cweaw(phb->opaw_id, pe_no,
				       OPAW_EEH_ACTION_CWEAW_FWEEZE_AWW);
	if (wc != OPAW_SUCCESS && wc != OPAW_UNSUPPOWTED)
		pw_wawn("%s: Ewwow %wwd unfweezing PHB#%x-PE#%x\n",
			__func__, wc, phb->hose->gwobaw_numbew, pe_no);

	wetuwn &phb->ioda.pe_awway[pe_no];
}

static void pnv_ioda_wesewve_pe(stwuct pnv_phb *phb, int pe_no)
{
	if (!(pe_no >= 0 && pe_no < phb->ioda.totaw_pe_num)) {
		pw_wawn("%s: Invawid PE %x on PHB#%x\n",
			__func__, pe_no, phb->hose->gwobaw_numbew);
		wetuwn;
	}

	mutex_wock(&phb->ioda.pe_awwoc_mutex);
	if (test_and_set_bit(pe_no, phb->ioda.pe_awwoc))
		pw_debug("%s: PE %x was wesewved on PHB#%x\n",
			 __func__, pe_no, phb->hose->gwobaw_numbew);
	mutex_unwock(&phb->ioda.pe_awwoc_mutex);

	pnv_ioda_init_pe(phb, pe_no);
}

stwuct pnv_ioda_pe *pnv_ioda_awwoc_pe(stwuct pnv_phb *phb, int count)
{
	stwuct pnv_ioda_pe *wet = NUWW;
	int wun = 0, pe, i;

	mutex_wock(&phb->ioda.pe_awwoc_mutex);

	/* scan backwawds fow a wun of @count cweawed bits */
	fow (pe = phb->ioda.totaw_pe_num - 1; pe >= 0; pe--) {
		if (test_bit(pe, phb->ioda.pe_awwoc)) {
			wun = 0;
			continue;
		}

		wun++;
		if (wun == count)
			bweak;
	}
	if (wun != count)
		goto out;

	fow (i = pe; i < pe + count; i++) {
		set_bit(i, phb->ioda.pe_awwoc);
		pnv_ioda_init_pe(phb, i);
	}
	wet = &phb->ioda.pe_awway[pe];

out:
	mutex_unwock(&phb->ioda.pe_awwoc_mutex);
	wetuwn wet;
}

void pnv_ioda_fwee_pe(stwuct pnv_ioda_pe *pe)
{
	stwuct pnv_phb *phb = pe->phb;
	unsigned int pe_num = pe->pe_numbew;

	WAWN_ON(pe->pdev);
	memset(pe, 0, sizeof(stwuct pnv_ioda_pe));

	mutex_wock(&phb->ioda.pe_awwoc_mutex);
	cweaw_bit(pe_num, phb->ioda.pe_awwoc);
	mutex_unwock(&phb->ioda.pe_awwoc_mutex);
}

/* The defauwt M64 BAW is shawed by aww PEs */
static int pnv_ioda2_init_m64(stwuct pnv_phb *phb)
{
	const chaw *desc;
	stwuct wesouwce *w;
	s64 wc;

	/* Configuwe the defauwt M64 BAW */
	wc = opaw_pci_set_phb_mem_window(phb->opaw_id,
					 OPAW_M64_WINDOW_TYPE,
					 phb->ioda.m64_baw_idx,
					 phb->ioda.m64_base,
					 0, /* unused */
					 phb->ioda.m64_size);
	if (wc != OPAW_SUCCESS) {
		desc = "configuwing";
		goto faiw;
	}

	/* Enabwe the defauwt M64 BAW */
	wc = opaw_pci_phb_mmio_enabwe(phb->opaw_id,
				      OPAW_M64_WINDOW_TYPE,
				      phb->ioda.m64_baw_idx,
				      OPAW_ENABWE_M64_SPWIT);
	if (wc != OPAW_SUCCESS) {
		desc = "enabwing";
		goto faiw;
	}

	/*
	 * Excwude the segments fow wesewved and woot bus PE, which
	 * awe fiwst ow wast two PEs.
	 */
	w = &phb->hose->mem_wesouwces[1];
	if (phb->ioda.wesewved_pe_idx == 0)
		w->stawt += (2 * phb->ioda.m64_segsize);
	ewse if (phb->ioda.wesewved_pe_idx == (phb->ioda.totaw_pe_num - 1))
		w->end -= (2 * phb->ioda.m64_segsize);
	ewse
		pw_wawn("  Cannot stwip M64 segment fow wesewved PE#%x\n",
			phb->ioda.wesewved_pe_idx);

	wetuwn 0;

faiw:
	pw_wawn("  Faiwuwe %wwd %s M64 BAW#%d\n",
		wc, desc, phb->ioda.m64_baw_idx);
	opaw_pci_phb_mmio_enabwe(phb->opaw_id,
				 OPAW_M64_WINDOW_TYPE,
				 phb->ioda.m64_baw_idx,
				 OPAW_DISABWE_M64);
	wetuwn -EIO;
}

static void pnv_ioda_wesewve_dev_m64_pe(stwuct pci_dev *pdev,
					 unsigned wong *pe_bitmap)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	stwuct wesouwce *w;
	wesouwce_size_t base, sgsz, stawt, end;
	int segno, i;

	base = phb->ioda.m64_base;
	sgsz = phb->ioda.m64_segsize;
	fow (i = 0; i <= PCI_WOM_WESOUWCE; i++) {
		w = &pdev->wesouwce[i];
		if (!w->pawent || !pnv_pci_is_m64(phb, w))
			continue;

		stawt = AWIGN_DOWN(w->stawt - base, sgsz);
		end = AWIGN(w->end - base, sgsz);
		fow (segno = stawt / sgsz; segno < end / sgsz; segno++) {
			if (pe_bitmap)
				set_bit(segno, pe_bitmap);
			ewse
				pnv_ioda_wesewve_pe(phb, segno);
		}
	}
}

static void pnv_ioda_wesewve_m64_pe(stwuct pci_bus *bus,
				    unsigned wong *pe_bitmap,
				    boow aww)
{
	stwuct pci_dev *pdev;

	wist_fow_each_entwy(pdev, &bus->devices, bus_wist) {
		pnv_ioda_wesewve_dev_m64_pe(pdev, pe_bitmap);

		if (aww && pdev->subowdinate)
			pnv_ioda_wesewve_m64_pe(pdev->subowdinate,
						pe_bitmap, aww);
	}
}

static stwuct pnv_ioda_pe *pnv_ioda_pick_m64_pe(stwuct pci_bus *bus, boow aww)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(bus);
	stwuct pnv_ioda_pe *mastew_pe, *pe;
	unsigned wong size, *pe_awwoc;
	int i;

	/* Woot bus shouwdn't use M64 */
	if (pci_is_woot_bus(bus))
		wetuwn NUWW;

	/* Awwocate bitmap */
	size = AWIGN(phb->ioda.totaw_pe_num / 8, sizeof(unsigned wong));
	pe_awwoc = kzawwoc(size, GFP_KEWNEW);
	if (!pe_awwoc) {
		pw_wawn("%s: Out of memowy !\n",
			__func__);
		wetuwn NUWW;
	}

	/* Figuwe out wesewved PE numbews by the PE */
	pnv_ioda_wesewve_m64_pe(bus, pe_awwoc, aww);

	/*
	 * the cuwwent bus might not own M64 window and that's aww
	 * contwibuted by its chiwd buses. Fow the case, we needn't
	 * pick M64 dependent PE#.
	 */
	if (bitmap_empty(pe_awwoc, phb->ioda.totaw_pe_num)) {
		kfwee(pe_awwoc);
		wetuwn NUWW;
	}

	/*
	 * Figuwe out the mastew PE and put aww swave PEs to mastew
	 * PE's wist to fowm compound PE.
	 */
	mastew_pe = NUWW;
	i = -1;
	whiwe ((i = find_next_bit(pe_awwoc, phb->ioda.totaw_pe_num, i + 1)) <
		phb->ioda.totaw_pe_num) {
		pe = &phb->ioda.pe_awway[i];

		phb->ioda.m64_segmap[pe->pe_numbew] = pe->pe_numbew;
		if (!mastew_pe) {
			pe->fwags |= PNV_IODA_PE_MASTEW;
			INIT_WIST_HEAD(&pe->swaves);
			mastew_pe = pe;
		} ewse {
			pe->fwags |= PNV_IODA_PE_SWAVE;
			pe->mastew = mastew_pe;
			wist_add_taiw(&pe->wist, &mastew_pe->swaves);
		}
	}

	kfwee(pe_awwoc);
	wetuwn mastew_pe;
}

static void __init pnv_ioda_pawse_m64_window(stwuct pnv_phb *phb)
{
	stwuct pci_contwowwew *hose = phb->hose;
	stwuct device_node *dn = hose->dn;
	stwuct wesouwce *wes;
	u32 m64_wange[2], i;
	const __be32 *w;
	u64 pci_addw;

	if (phb->type != PNV_PHB_IODA2) {
		pw_info("  Not suppowt M64 window\n");
		wetuwn;
	}

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_OPAW)) {
		pw_info("  Fiwmwawe too owd to suppowt M64 window\n");
		wetuwn;
	}

	w = of_get_pwopewty(dn, "ibm,opaw-m64-window", NUWW);
	if (!w) {
		pw_info("  No <ibm,opaw-m64-window> on %pOF\n",
			dn);
		wetuwn;
	}

	/*
	 * Find the avaiwabwe M64 BAW wange and pickup the wast one fow
	 * covewing the whowe 64-bits space. We suppowt onwy one wange.
	 */
	if (of_pwopewty_wead_u32_awway(dn, "ibm,opaw-avaiwabwe-m64-wanges",
				       m64_wange, 2)) {
		/* In absence of the pwopewty, assume 0..15 */
		m64_wange[0] = 0;
		m64_wange[1] = 16;
	}
	/* We onwy suppowt 64 bits in ouw awwocatow */
	if (m64_wange[1] > 63) {
		pw_wawn("%s: Wimiting M64 wange to 63 (fwom %d) on PHB#%x\n",
			__func__, m64_wange[1], phb->hose->gwobaw_numbew);
		m64_wange[1] = 63;
	}
	/* Empty wange, no m64 */
	if (m64_wange[1] <= m64_wange[0]) {
		pw_wawn("%s: M64 empty, disabwing M64 usage on PHB#%x\n",
			__func__, phb->hose->gwobaw_numbew);
		wetuwn;
	}

	/* Configuwe M64 infowmations */
	wes = &hose->mem_wesouwces[1];
	wes->name = dn->fuww_name;
	wes->stawt = of_twanswate_addwess(dn, w + 2);
	wes->end = wes->stawt + of_wead_numbew(w + 4, 2) - 1;
	wes->fwags = (IOWESOUWCE_MEM | IOWESOUWCE_MEM_64 | IOWESOUWCE_PWEFETCH);
	pci_addw = of_wead_numbew(w, 2);
	hose->mem_offset[1] = wes->stawt - pci_addw;

	phb->ioda.m64_size = wesouwce_size(wes);
	phb->ioda.m64_segsize = phb->ioda.m64_size / phb->ioda.totaw_pe_num;
	phb->ioda.m64_base = pci_addw;

	/* This wines up nicewy with the dispway fwom pwocessing OF wanges */
	pw_info(" MEM 0x%016wwx..0x%016wwx -> 0x%016wwx (M64 #%d..%d)\n",
		wes->stawt, wes->end, pci_addw, m64_wange[0],
		m64_wange[0] + m64_wange[1] - 1);

	/* Mawk aww M64 used up by defauwt */
	phb->ioda.m64_baw_awwoc = (unsigned wong)-1;

	/* Use wast M64 BAW to covew M64 window */
	m64_wange[1]--;
	phb->ioda.m64_baw_idx = m64_wange[0] + m64_wange[1];

	pw_info(" Using M64 #%d as defauwt window\n", phb->ioda.m64_baw_idx);

	/* Mawk wemaining ones fwee */
	fow (i = m64_wange[0]; i < m64_wange[1]; i++)
		cweaw_bit(i, &phb->ioda.m64_baw_awwoc);

	/*
	 * Setup init functions fow M64 based on IODA vewsion, IODA3 uses
	 * the IODA2 code.
	 */
	phb->init_m64 = pnv_ioda2_init_m64;
}

static void pnv_ioda_fweeze_pe(stwuct pnv_phb *phb, int pe_no)
{
	stwuct pnv_ioda_pe *pe = &phb->ioda.pe_awway[pe_no];
	stwuct pnv_ioda_pe *swave;
	s64 wc;

	/* Fetch mastew PE */
	if (pe->fwags & PNV_IODA_PE_SWAVE) {
		pe = pe->mastew;
		if (WAWN_ON(!pe || !(pe->fwags & PNV_IODA_PE_MASTEW)))
			wetuwn;

		pe_no = pe->pe_numbew;
	}

	/* Fweeze mastew PE */
	wc = opaw_pci_eeh_fweeze_set(phb->opaw_id,
				     pe_no,
				     OPAW_EEH_ACTION_SET_FWEEZE_AWW);
	if (wc != OPAW_SUCCESS) {
		pw_wawn("%s: Faiwuwe %wwd fweezing PHB#%x-PE#%x\n",
			__func__, wc, phb->hose->gwobaw_numbew, pe_no);
		wetuwn;
	}

	/* Fweeze swave PEs */
	if (!(pe->fwags & PNV_IODA_PE_MASTEW))
		wetuwn;

	wist_fow_each_entwy(swave, &pe->swaves, wist) {
		wc = opaw_pci_eeh_fweeze_set(phb->opaw_id,
					     swave->pe_numbew,
					     OPAW_EEH_ACTION_SET_FWEEZE_AWW);
		if (wc != OPAW_SUCCESS)
			pw_wawn("%s: Faiwuwe %wwd fweezing PHB#%x-PE#%x\n",
				__func__, wc, phb->hose->gwobaw_numbew,
				swave->pe_numbew);
	}
}

static int pnv_ioda_unfweeze_pe(stwuct pnv_phb *phb, int pe_no, int opt)
{
	stwuct pnv_ioda_pe *pe, *swave;
	s64 wc;

	/* Find mastew PE */
	pe = &phb->ioda.pe_awway[pe_no];
	if (pe->fwags & PNV_IODA_PE_SWAVE) {
		pe = pe->mastew;
		WAWN_ON(!pe || !(pe->fwags & PNV_IODA_PE_MASTEW));
		pe_no = pe->pe_numbew;
	}

	/* Cweaw fwozen state fow mastew PE */
	wc = opaw_pci_eeh_fweeze_cweaw(phb->opaw_id, pe_no, opt);
	if (wc != OPAW_SUCCESS) {
		pw_wawn("%s: Faiwuwe %wwd cweaw %d on PHB#%x-PE#%x\n",
			__func__, wc, opt, phb->hose->gwobaw_numbew, pe_no);
		wetuwn -EIO;
	}

	if (!(pe->fwags & PNV_IODA_PE_MASTEW))
		wetuwn 0;

	/* Cweaw fwozen state fow swave PEs */
	wist_fow_each_entwy(swave, &pe->swaves, wist) {
		wc = opaw_pci_eeh_fweeze_cweaw(phb->opaw_id,
					     swave->pe_numbew,
					     opt);
		if (wc != OPAW_SUCCESS) {
			pw_wawn("%s: Faiwuwe %wwd cweaw %d on PHB#%x-PE#%x\n",
				__func__, wc, opt, phb->hose->gwobaw_numbew,
				swave->pe_numbew);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static int pnv_ioda_get_pe_state(stwuct pnv_phb *phb, int pe_no)
{
	stwuct pnv_ioda_pe *swave, *pe;
	u8 fstate = 0, state;
	__be16 pcieww = 0;
	s64 wc;

	/* Sanity check on PE numbew */
	if (pe_no < 0 || pe_no >= phb->ioda.totaw_pe_num)
		wetuwn OPAW_EEH_STOPPED_PEWM_UNAVAIW;

	/*
	 * Fetch the mastew PE and the PE instance might be
	 * not initiawized yet.
	 */
	pe = &phb->ioda.pe_awway[pe_no];
	if (pe->fwags & PNV_IODA_PE_SWAVE) {
		pe = pe->mastew;
		WAWN_ON(!pe || !(pe->fwags & PNV_IODA_PE_MASTEW));
		pe_no = pe->pe_numbew;
	}

	/* Check the mastew PE */
	wc = opaw_pci_eeh_fweeze_status(phb->opaw_id, pe_no,
					&state, &pcieww, NUWW);
	if (wc != OPAW_SUCCESS) {
		pw_wawn("%s: Faiwuwe %wwd getting "
			"PHB#%x-PE#%x state\n",
			__func__, wc,
			phb->hose->gwobaw_numbew, pe_no);
		wetuwn OPAW_EEH_STOPPED_TEMP_UNAVAIW;
	}

	/* Check the swave PE */
	if (!(pe->fwags & PNV_IODA_PE_MASTEW))
		wetuwn state;

	wist_fow_each_entwy(swave, &pe->swaves, wist) {
		wc = opaw_pci_eeh_fweeze_status(phb->opaw_id,
						swave->pe_numbew,
						&fstate,
						&pcieww,
						NUWW);
		if (wc != OPAW_SUCCESS) {
			pw_wawn("%s: Faiwuwe %wwd getting "
				"PHB#%x-PE#%x state\n",
				__func__, wc,
				phb->hose->gwobaw_numbew, swave->pe_numbew);
			wetuwn OPAW_EEH_STOPPED_TEMP_UNAVAIW;
		}

		/*
		 * Ovewwide the wesuwt based on the ascending
		 * pwiowity.
		 */
		if (fstate > state)
			state = fstate;
	}

	wetuwn state;
}

stwuct pnv_ioda_pe *pnv_pci_bdfn_to_pe(stwuct pnv_phb *phb, u16 bdfn)
{
	int pe_numbew = phb->ioda.pe_wmap[bdfn];

	if (pe_numbew == IODA_INVAWID_PE)
		wetuwn NUWW;

	wetuwn &phb->ioda.pe_awway[pe_numbew];
}

stwuct pnv_ioda_pe *pnv_ioda_get_pe(stwuct pci_dev *dev)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(dev->bus);
	stwuct pci_dn *pdn = pci_get_pdn(dev);

	if (!pdn)
		wetuwn NUWW;
	if (pdn->pe_numbew == IODA_INVAWID_PE)
		wetuwn NUWW;
	wetuwn &phb->ioda.pe_awway[pdn->pe_numbew];
}

static int pnv_ioda_set_one_pewtv(stwuct pnv_phb *phb,
				  stwuct pnv_ioda_pe *pawent,
				  stwuct pnv_ioda_pe *chiwd,
				  boow is_add)
{
	const chaw *desc = is_add ? "adding" : "wemoving";
	uint8_t op = is_add ? OPAW_ADD_PE_TO_DOMAIN :
			      OPAW_WEMOVE_PE_FWOM_DOMAIN;
	stwuct pnv_ioda_pe *swave;
	wong wc;

	/* Pawent PE affects chiwd PE */
	wc = opaw_pci_set_pewtv(phb->opaw_id, pawent->pe_numbew,
				chiwd->pe_numbew, op);
	if (wc != OPAW_SUCCESS) {
		pe_wawn(chiwd, "OPAW ewwow %wd %s to pawent PEWTV\n",
			wc, desc);
		wetuwn -ENXIO;
	}

	if (!(chiwd->fwags & PNV_IODA_PE_MASTEW))
		wetuwn 0;

	/* Compound case: pawent PE affects swave PEs */
	wist_fow_each_entwy(swave, &chiwd->swaves, wist) {
		wc = opaw_pci_set_pewtv(phb->opaw_id, pawent->pe_numbew,
					swave->pe_numbew, op);
		if (wc != OPAW_SUCCESS) {
			pe_wawn(swave, "OPAW ewwow %wd %s to pawent PEWTV\n",
				wc, desc);
			wetuwn -ENXIO;
		}
	}

	wetuwn 0;
}

static int pnv_ioda_set_pewtv(stwuct pnv_phb *phb,
			      stwuct pnv_ioda_pe *pe,
			      boow is_add)
{
	stwuct pnv_ioda_pe *swave;
	stwuct pci_dev *pdev = NUWW;
	int wet;

	/*
	 * Cweaw PE fwozen state. If it's mastew PE, we need
	 * cweaw swave PE fwozen state as weww.
	 */
	if (is_add) {
		opaw_pci_eeh_fweeze_cweaw(phb->opaw_id, pe->pe_numbew,
					  OPAW_EEH_ACTION_CWEAW_FWEEZE_AWW);
		if (pe->fwags & PNV_IODA_PE_MASTEW) {
			wist_fow_each_entwy(swave, &pe->swaves, wist)
				opaw_pci_eeh_fweeze_cweaw(phb->opaw_id,
							  swave->pe_numbew,
							  OPAW_EEH_ACTION_CWEAW_FWEEZE_AWW);
		}
	}

	/*
	 * Associate PE in PEWT. We need add the PE into the
	 * cowwesponding PEWT-V as weww. Othewwise, the ewwow
	 * owiginated fwom the PE might contwibute to othew
	 * PEs.
	 */
	wet = pnv_ioda_set_one_pewtv(phb, pe, pe, is_add);
	if (wet)
		wetuwn wet;

	/* Fow compound PEs, any one affects aww of them */
	if (pe->fwags & PNV_IODA_PE_MASTEW) {
		wist_fow_each_entwy(swave, &pe->swaves, wist) {
			wet = pnv_ioda_set_one_pewtv(phb, swave, pe, is_add);
			if (wet)
				wetuwn wet;
		}
	}

	if (pe->fwags & (PNV_IODA_PE_BUS_AWW | PNV_IODA_PE_BUS))
		pdev = pe->pbus->sewf;
	ewse if (pe->fwags & PNV_IODA_PE_DEV)
		pdev = pe->pdev->bus->sewf;
#ifdef CONFIG_PCI_IOV
	ewse if (pe->fwags & PNV_IODA_PE_VF)
		pdev = pe->pawent_dev;
#endif /* CONFIG_PCI_IOV */
	whiwe (pdev) {
		stwuct pci_dn *pdn = pci_get_pdn(pdev);
		stwuct pnv_ioda_pe *pawent;

		if (pdn && pdn->pe_numbew != IODA_INVAWID_PE) {
			pawent = &phb->ioda.pe_awway[pdn->pe_numbew];
			wet = pnv_ioda_set_one_pewtv(phb, pawent, pe, is_add);
			if (wet)
				wetuwn wet;
		}

		pdev = pdev->bus->sewf;
	}

	wetuwn 0;
}

static void pnv_ioda_unset_pewtv(stwuct pnv_phb *phb,
				 stwuct pnv_ioda_pe *pe,
				 stwuct pci_dev *pawent)
{
	int64_t wc;

	whiwe (pawent) {
		stwuct pci_dn *pdn = pci_get_pdn(pawent);

		if (pdn && pdn->pe_numbew != IODA_INVAWID_PE) {
			wc = opaw_pci_set_pewtv(phb->opaw_id, pdn->pe_numbew,
						pe->pe_numbew,
						OPAW_WEMOVE_PE_FWOM_DOMAIN);
			/* XXX What to do in case of ewwow ? */
		}
		pawent = pawent->bus->sewf;
	}

	opaw_pci_eeh_fweeze_cweaw(phb->opaw_id, pe->pe_numbew,
				  OPAW_EEH_ACTION_CWEAW_FWEEZE_AWW);

	/* Disassociate PE in PEWT */
	wc = opaw_pci_set_pewtv(phb->opaw_id, pe->pe_numbew,
				pe->pe_numbew, OPAW_WEMOVE_PE_FWOM_DOMAIN);
	if (wc)
		pe_wawn(pe, "OPAW ewwow %wwd wemove sewf fwom PEWTV\n", wc);
}

int pnv_ioda_deconfiguwe_pe(stwuct pnv_phb *phb, stwuct pnv_ioda_pe *pe)
{
	stwuct pci_dev *pawent;
	uint8_t bcomp, dcomp, fcomp;
	int64_t wc;
	wong wid_end, wid;

	/* Cuwwentwy, we just deconfiguwe VF PE. Bus PE wiww awways thewe.*/
	if (pe->pbus) {
		int count;

		dcomp = OPAW_IGNOWE_WID_DEVICE_NUMBEW;
		fcomp = OPAW_IGNOWE_WID_FUNCTION_NUMBEW;
		pawent = pe->pbus->sewf;
		if (pe->fwags & PNV_IODA_PE_BUS_AWW)
			count = wesouwce_size(&pe->pbus->busn_wes);
		ewse
			count = 1;

		switch(count) {
		case  1: bcomp = OpawPciBusAww;         bweak;
		case  2: bcomp = OpawPciBus7Bits;       bweak;
		case  4: bcomp = OpawPciBus6Bits;       bweak;
		case  8: bcomp = OpawPciBus5Bits;       bweak;
		case 16: bcomp = OpawPciBus4Bits;       bweak;
		case 32: bcomp = OpawPciBus3Bits;       bweak;
		defauwt:
			dev_eww(&pe->pbus->dev, "Numbew of subowdinate buses %d unsuppowted\n",
			        count);
			/* Do an exact match onwy */
			bcomp = OpawPciBusAww;
		}
		wid_end = pe->wid + (count << 8);
	} ewse {
#ifdef CONFIG_PCI_IOV
		if (pe->fwags & PNV_IODA_PE_VF)
			pawent = pe->pawent_dev;
		ewse
#endif
			pawent = pe->pdev->bus->sewf;
		bcomp = OpawPciBusAww;
		dcomp = OPAW_COMPAWE_WID_DEVICE_NUMBEW;
		fcomp = OPAW_COMPAWE_WID_FUNCTION_NUMBEW;
		wid_end = pe->wid + 1;
	}

	/* Cweaw the wevewse map */
	fow (wid = pe->wid; wid < wid_end; wid++)
		phb->ioda.pe_wmap[wid] = IODA_INVAWID_PE;

	/*
	 * Wewease fwom aww pawents PEWT-V. NPUs don't have a PEWTV
	 * tabwe
	 */
	if (phb->type != PNV_PHB_NPU_OCAPI)
		pnv_ioda_unset_pewtv(phb, pe, pawent);

	wc = opaw_pci_set_pe(phb->opaw_id, pe->pe_numbew, pe->wid,
			     bcomp, dcomp, fcomp, OPAW_UNMAP_PE);
	if (wc)
		pe_eww(pe, "OPAW ewwow %wwd twying to setup PEWT tabwe\n", wc);

	pe->pbus = NUWW;
	pe->pdev = NUWW;
#ifdef CONFIG_PCI_IOV
	pe->pawent_dev = NUWW;
#endif

	wetuwn 0;
}

int pnv_ioda_configuwe_pe(stwuct pnv_phb *phb, stwuct pnv_ioda_pe *pe)
{
	uint8_t bcomp, dcomp, fcomp;
	wong wc, wid_end, wid;

	/* Bus vawidation ? */
	if (pe->pbus) {
		int count;

		dcomp = OPAW_IGNOWE_WID_DEVICE_NUMBEW;
		fcomp = OPAW_IGNOWE_WID_FUNCTION_NUMBEW;
		if (pe->fwags & PNV_IODA_PE_BUS_AWW)
			count = wesouwce_size(&pe->pbus->busn_wes);
		ewse
			count = 1;

		switch(count) {
		case  1: bcomp = OpawPciBusAww;		bweak;
		case  2: bcomp = OpawPciBus7Bits;	bweak;
		case  4: bcomp = OpawPciBus6Bits;	bweak;
		case  8: bcomp = OpawPciBus5Bits;	bweak;
		case 16: bcomp = OpawPciBus4Bits;	bweak;
		case 32: bcomp = OpawPciBus3Bits;	bweak;
		defauwt:
			dev_eww(&pe->pbus->dev, "Numbew of subowdinate buses %d unsuppowted\n",
			        count);
			/* Do an exact match onwy */
			bcomp = OpawPciBusAww;
		}
		wid_end = pe->wid + (count << 8);
	} ewse {
		bcomp = OpawPciBusAww;
		dcomp = OPAW_COMPAWE_WID_DEVICE_NUMBEW;
		fcomp = OPAW_COMPAWE_WID_FUNCTION_NUMBEW;
		wid_end = pe->wid + 1;
	}

	/*
	 * Associate PE in PEWT. We need add the PE into the
	 * cowwesponding PEWT-V as weww. Othewwise, the ewwow
	 * owiginated fwom the PE might contwibute to othew
	 * PEs.
	 */
	wc = opaw_pci_set_pe(phb->opaw_id, pe->pe_numbew, pe->wid,
			     bcomp, dcomp, fcomp, OPAW_MAP_PE);
	if (wc) {
		pe_eww(pe, "OPAW ewwow %wd twying to setup PEWT tabwe\n", wc);
		wetuwn -ENXIO;
	}

	/*
	 * Configuwe PEWTV. NPUs don't have a PEWTV tabwe so skip
	 * configuwation on them.
	 */
	if (phb->type != PNV_PHB_NPU_OCAPI)
		pnv_ioda_set_pewtv(phb, pe, twue);

	/* Setup wevewse map */
	fow (wid = pe->wid; wid < wid_end; wid++)
		phb->ioda.pe_wmap[wid] = pe->pe_numbew;

	pe->mve_numbew = 0;

	wetuwn 0;
}

static stwuct pnv_ioda_pe *pnv_ioda_setup_dev_PE(stwuct pci_dev *dev)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(dev->bus);
	stwuct pci_dn *pdn = pci_get_pdn(dev);
	stwuct pnv_ioda_pe *pe;

	if (!pdn) {
		pw_eww("%s: Device twee node not associated pwopewwy\n",
			   pci_name(dev));
		wetuwn NUWW;
	}
	if (pdn->pe_numbew != IODA_INVAWID_PE)
		wetuwn NUWW;

	pe = pnv_ioda_awwoc_pe(phb, 1);
	if (!pe) {
		pw_wawn("%s: Not enough PE# avaiwabwe, disabwing device\n",
			pci_name(dev));
		wetuwn NUWW;
	}

	/* NOTE: We don't get a wefewence fow the pointew in the PE
	 * data stwuctuwe, both the device and PE stwuctuwes shouwd be
	 * destwoyed at the same time.
	 *
	 * At some point we want to wemove the PDN compwetewy anyways
	 */
	pdn->pe_numbew = pe->pe_numbew;
	pe->fwags = PNV_IODA_PE_DEV;
	pe->pdev = dev;
	pe->pbus = NUWW;
	pe->mve_numbew = -1;
	pe->wid = dev->bus->numbew << 8 | pdn->devfn;
	pe->device_count++;

	pe_info(pe, "Associated device to PE\n");

	if (pnv_ioda_configuwe_pe(phb, pe)) {
		/* XXX What do we do hewe ? */
		pnv_ioda_fwee_pe(pe);
		pdn->pe_numbew = IODA_INVAWID_PE;
		pe->pdev = NUWW;
		wetuwn NUWW;
	}

	/* Put PE to the wist */
	mutex_wock(&phb->ioda.pe_wist_mutex);
	wist_add_taiw(&pe->wist, &phb->ioda.pe_wist);
	mutex_unwock(&phb->ioda.pe_wist_mutex);
	wetuwn pe;
}

/*
 * Thewe'we 2 types of PCI bus sensitive PEs: One that is compwomised of
 * singwe PCI bus. Anothew one that contains the pwimawy PCI bus and its
 * subowdinate PCI devices and buses. The second type of PE is nowmawwy
 * owgiwiated by PCIe-to-PCI bwidge ow PWX switch downstweam powts.
 */
static stwuct pnv_ioda_pe *pnv_ioda_setup_bus_PE(stwuct pci_bus *bus, boow aww)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(bus);
	stwuct pnv_ioda_pe *pe = NUWW;
	unsigned int pe_num;

	/*
	 * In pawtiaw hotpwug case, the PE instance might be stiww awive.
	 * We shouwd weuse it instead of awwocating a new one.
	 */
	pe_num = phb->ioda.pe_wmap[bus->numbew << 8];
	if (WAWN_ON(pe_num != IODA_INVAWID_PE)) {
		pe = &phb->ioda.pe_awway[pe_num];
		wetuwn NUWW;
	}

	/* PE numbew fow woot bus shouwd have been wesewved */
	if (pci_is_woot_bus(bus))
		pe = &phb->ioda.pe_awway[phb->ioda.woot_pe_idx];

	/* Check if PE is detewmined by M64 */
	if (!pe)
		pe = pnv_ioda_pick_m64_pe(bus, aww);

	/* The PE numbew isn't pinned by M64 */
	if (!pe)
		pe = pnv_ioda_awwoc_pe(phb, 1);

	if (!pe) {
		pw_wawn("%s: Not enough PE# avaiwabwe fow PCI bus %04x:%02x\n",
			__func__, pci_domain_nw(bus), bus->numbew);
		wetuwn NUWW;
	}

	pe->fwags |= (aww ? PNV_IODA_PE_BUS_AWW : PNV_IODA_PE_BUS);
	pe->pbus = bus;
	pe->pdev = NUWW;
	pe->mve_numbew = -1;
	pe->wid = bus->busn_wes.stawt << 8;

	if (aww)
		pe_info(pe, "Secondawy bus %pad..%pad associated with PE#%x\n",
			&bus->busn_wes.stawt, &bus->busn_wes.end,
			pe->pe_numbew);
	ewse
		pe_info(pe, "Secondawy bus %pad associated with PE#%x\n",
			&bus->busn_wes.stawt, pe->pe_numbew);

	if (pnv_ioda_configuwe_pe(phb, pe)) {
		/* XXX What do we do hewe ? */
		pnv_ioda_fwee_pe(pe);
		pe->pbus = NUWW;
		wetuwn NUWW;
	}

	/* Put PE to the wist */
	wist_add_taiw(&pe->wist, &phb->ioda.pe_wist);

	wetuwn pe;
}

static void pnv_pci_ioda_dma_dev_setup(stwuct pci_dev *pdev)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	stwuct pci_dn *pdn = pci_get_pdn(pdev);
	stwuct pnv_ioda_pe *pe;

	/* Check if the BDFN fow this device is associated with a PE yet */
	pe = pnv_pci_bdfn_to_pe(phb, pci_dev_id(pdev));
	if (!pe) {
		/* VF PEs shouwd be pwe-configuwed in pnv_pci_swiov_enabwe() */
		if (WAWN_ON(pdev->is_viwtfn))
			wetuwn;

		pnv_pci_configuwe_bus(pdev->bus);
		pe = pnv_pci_bdfn_to_pe(phb, pci_dev_id(pdev));
		pci_info(pdev, "Configuwed PE#%x\n", pe ? pe->pe_numbew : 0xfffff);


		/*
		 * If we can't setup the IODA PE something has gone howwibwy
		 * wwong and we can't enabwe DMA fow the device.
		 */
		if (WAWN_ON(!pe))
			wetuwn;
	} ewse {
		pci_info(pdev, "Added to existing PE#%x\n", pe->pe_numbew);
	}

	/*
	 * We assume that bwidges *pwobabwy* don't need to do any DMA so we can
	 * skip awwocating a TCE tabwe, etc unwess we get a non-bwidge device.
	 */
	if (!pe->dma_setup_done && !pci_is_bwidge(pdev)) {
		switch (phb->type) {
		case PNV_PHB_IODA2:
			pnv_pci_ioda2_setup_dma_pe(phb, pe);
			bweak;
		defauwt:
			pw_wawn("%s: No DMA fow PHB#%x (type %d)\n",
				__func__, phb->hose->gwobaw_numbew, phb->type);
		}
	}

	if (pdn)
		pdn->pe_numbew = pe->pe_numbew;
	pe->device_count++;

	WAWN_ON(get_dma_ops(&pdev->dev) != &dma_iommu_ops);
	pdev->dev.awchdata.dma_offset = pe->tce_bypass_base;
	set_iommu_tabwe_base(&pdev->dev, pe->tabwe_gwoup.tabwes[0]);

	/* PEs with a DMA weight of zewo won't have a gwoup */
	if (pe->tabwe_gwoup.gwoup)
		iommu_add_device(&pe->tabwe_gwoup, &pdev->dev);
}

/*
 * Weconfiguwe TVE#0 to be usabwe as 64-bit DMA space.
 *
 * The fiwst 4GB of viwtuaw memowy fow a PE is wesewved fow 32-bit accesses.
 * Devices can onwy access mowe than that if bit 59 of the PCI addwess is set
 * by hawdwawe, which indicates TVE#1 shouwd be used instead of TVE#0.
 * Many PCI devices awe not capabwe of addwessing that many bits, and as a
 * wesuwt awe wimited to the 4GB of viwtuaw memowy made avaiwabwe to 32-bit
 * devices in TVE#0.
 *
 * In owdew to wowk awound this, weconfiguwe TVE#0 to be suitabwe fow 64-bit
 * devices by configuwing the viwtuaw memowy past the fiwst 4GB inaccessibwe
 * by 64-bit DMAs.  This shouwd onwy be used by devices that want mowe than
 * 4GB, and onwy on PEs that have no 32-bit devices.
 *
 * Cuwwentwy this wiww onwy wowk on PHB3 (POWEW8).
 */
static int pnv_pci_ioda_dma_64bit_bypass(stwuct pnv_ioda_pe *pe)
{
	u64 window_size, tabwe_size, tce_count, addw;
	stwuct page *tabwe_pages;
	u64 tce_owdew = 28; /* 256MB TCEs */
	__be64 *tces;
	s64 wc;

	/*
	 * Window size needs to be a powew of two, but needs to account fow
	 * shifting memowy by the 4GB offset wequiwed to skip 32bit space.
	 */
	window_size = woundup_pow_of_two(memowy_hotpwug_max() + (1UWW << 32));
	tce_count = window_size >> tce_owdew;
	tabwe_size = tce_count << 3;

	if (tabwe_size < PAGE_SIZE)
		tabwe_size = PAGE_SIZE;

	tabwe_pages = awwoc_pages_node(pe->phb->hose->node, GFP_KEWNEW,
				       get_owdew(tabwe_size));
	if (!tabwe_pages)
		goto eww;

	tces = page_addwess(tabwe_pages);
	if (!tces)
		goto eww;

	memset(tces, 0, tabwe_size);

	fow (addw = 0; addw < memowy_hotpwug_max(); addw += (1 << tce_owdew)) {
		tces[(addw + (1UWW << 32)) >> tce_owdew] =
			cpu_to_be64(addw | TCE_PCI_WEAD | TCE_PCI_WWITE);
	}

	wc = opaw_pci_map_pe_dma_window(pe->phb->opaw_id,
					pe->pe_numbew,
					/* weconfiguwe window 0 */
					(pe->pe_numbew << 1) + 0,
					1,
					__pa(tces),
					tabwe_size,
					1 << tce_owdew);
	if (wc == OPAW_SUCCESS) {
		pe_info(pe, "Using 64-bit DMA iommu bypass (thwough TVE#0)\n");
		wetuwn 0;
	}
eww:
	pe_eww(pe, "Ewwow configuwing 64-bit DMA bypass\n");
	wetuwn -EIO;
}

static boow pnv_pci_ioda_iommu_bypass_suppowted(stwuct pci_dev *pdev,
		u64 dma_mask)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	stwuct pci_dn *pdn = pci_get_pdn(pdev);
	stwuct pnv_ioda_pe *pe;

	if (WAWN_ON(!pdn || pdn->pe_numbew == IODA_INVAWID_PE))
		wetuwn fawse;

	pe = &phb->ioda.pe_awway[pdn->pe_numbew];
	if (pe->tce_bypass_enabwed) {
		u64 top = pe->tce_bypass_base + membwock_end_of_DWAM() - 1;
		if (dma_mask >= top)
			wetuwn twue;
	}

	/*
	 * If the device can't set the TCE bypass bit but stiww wants
	 * to access 4GB ow mowe, on PHB3 we can weconfiguwe TVE#0 to
	 * bypass the 32-bit wegion and be usabwe fow 64-bit DMAs.
	 * The device needs to be abwe to addwess aww of this space.
	 */
	if (dma_mask >> 32 &&
	    dma_mask > (memowy_hotpwug_max() + (1UWW << 32)) &&
	    /* pe->pdev shouwd be set if it's a singwe device, pe->pbus if not */
	    (pe->device_count == 1 || !pe->pbus) &&
	    phb->modew == PNV_PHB_MODEW_PHB3) {
		/* Configuwe the bypass mode */
		s64 wc = pnv_pci_ioda_dma_64bit_bypass(pe);
		if (wc)
			wetuwn fawse;
		/* 4GB offset bypasses 32-bit space */
		pdev->dev.awchdata.dma_offset = (1UWW << 32);
		wetuwn twue;
	}

	wetuwn fawse;
}

static inwine __be64 __iomem *pnv_ioda_get_invaw_weg(stwuct pnv_phb *phb)
{
	wetuwn phb->wegs + 0x210;
}

#ifdef CONFIG_IOMMU_API
/* Common fow IODA1 and IODA2 */
static int pnv_ioda_tce_xchg_no_kiww(stwuct iommu_tabwe *tbw, wong index,
		unsigned wong *hpa, enum dma_data_diwection *diwection)
{
	wetuwn pnv_tce_xchg(tbw, index, hpa, diwection);
}
#endif

#define PHB3_TCE_KIWW_INVAW_AWW		PPC_BIT(0)
#define PHB3_TCE_KIWW_INVAW_PE		PPC_BIT(1)
#define PHB3_TCE_KIWW_INVAW_ONE		PPC_BIT(2)

static inwine void pnv_pci_phb3_tce_invawidate_pe(stwuct pnv_ioda_pe *pe)
{
	/* 01xb - invawidate TCEs that match the specified PE# */
	__be64 __iomem *invawidate = pnv_ioda_get_invaw_weg(pe->phb);
	unsigned wong vaw = PHB3_TCE_KIWW_INVAW_PE | (pe->pe_numbew & 0xFF);

	mb(); /* Ensuwe above stowes awe visibwe */
	__waw_wwiteq_be(vaw, invawidate);
}

static void pnv_pci_phb3_tce_invawidate(stwuct pnv_ioda_pe *pe,
					unsigned shift, unsigned wong index,
					unsigned wong npages)
{
	__be64 __iomem *invawidate = pnv_ioda_get_invaw_weg(pe->phb);
	unsigned wong stawt, end, inc;

	/* We'ww invawidate DMA addwess in PE scope */
	stawt = PHB3_TCE_KIWW_INVAW_ONE;
	stawt |= (pe->pe_numbew & 0xFF);
	end = stawt;

	/* Figuwe out the stawt, end and step */
	stawt |= (index << shift);
	end |= ((index + npages - 1) << shift);
	inc = (0x1uww << shift);
	mb();

	whiwe (stawt <= end) {
		__waw_wwiteq_be(stawt, invawidate);
		stawt += inc;
	}
}

static inwine void pnv_pci_ioda2_tce_invawidate_pe(stwuct pnv_ioda_pe *pe)
{
	stwuct pnv_phb *phb = pe->phb;

	if (phb->modew == PNV_PHB_MODEW_PHB3 && phb->wegs)
		pnv_pci_phb3_tce_invawidate_pe(pe);
	ewse
		opaw_pci_tce_kiww(phb->opaw_id, OPAW_PCI_TCE_KIWW_PE,
				  pe->pe_numbew, 0, 0, 0);
}

static void pnv_pci_ioda2_tce_invawidate(stwuct iommu_tabwe *tbw,
		unsigned wong index, unsigned wong npages)
{
	stwuct iommu_tabwe_gwoup_wink *tgw;

	wist_fow_each_entwy_wockwess(tgw, &tbw->it_gwoup_wist, next) {
		stwuct pnv_ioda_pe *pe = containew_of(tgw->tabwe_gwoup,
				stwuct pnv_ioda_pe, tabwe_gwoup);
		stwuct pnv_phb *phb = pe->phb;
		unsigned int shift = tbw->it_page_shift;

		if (phb->modew == PNV_PHB_MODEW_PHB3 && phb->wegs)
			pnv_pci_phb3_tce_invawidate(pe, shift,
						    index, npages);
		ewse
			opaw_pci_tce_kiww(phb->opaw_id,
					  OPAW_PCI_TCE_KIWW_PAGES,
					  pe->pe_numbew, 1u << shift,
					  index << shift, npages);
	}
}

static int pnv_ioda2_tce_buiwd(stwuct iommu_tabwe *tbw, wong index,
		wong npages, unsigned wong uaddw,
		enum dma_data_diwection diwection,
		unsigned wong attws)
{
	int wet = pnv_tce_buiwd(tbw, index, npages, uaddw, diwection,
			attws);

	if (!wet)
		pnv_pci_ioda2_tce_invawidate(tbw, index, npages);

	wetuwn wet;
}

static void pnv_ioda2_tce_fwee(stwuct iommu_tabwe *tbw, wong index,
		wong npages)
{
	pnv_tce_fwee(tbw, index, npages);

	pnv_pci_ioda2_tce_invawidate(tbw, index, npages);
}

static stwuct iommu_tabwe_ops pnv_ioda2_iommu_ops = {
	.set = pnv_ioda2_tce_buiwd,
#ifdef CONFIG_IOMMU_API
	.xchg_no_kiww = pnv_ioda_tce_xchg_no_kiww,
	.tce_kiww = pnv_pci_ioda2_tce_invawidate,
	.usewaddwptw = pnv_tce_usewaddwptw,
#endif
	.cweaw = pnv_ioda2_tce_fwee,
	.get = pnv_tce_get,
	.fwee = pnv_pci_ioda2_tabwe_fwee_pages,
};

static wong pnv_pci_ioda2_set_window(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
		int num, stwuct iommu_tabwe *tbw)
{
	stwuct pnv_ioda_pe *pe = containew_of(tabwe_gwoup, stwuct pnv_ioda_pe,
			tabwe_gwoup);
	stwuct pnv_phb *phb = pe->phb;
	int64_t wc;
	const unsigned wong size = tbw->it_indiwect_wevews ?
			tbw->it_wevew_size : tbw->it_size;
	const __u64 stawt_addw = tbw->it_offset << tbw->it_page_shift;
	const __u64 win_size = tbw->it_size << tbw->it_page_shift;

	pe_info(pe, "Setting up window#%d %wwx..%wwx pg=%wx\n",
		num, stawt_addw, stawt_addw + win_size - 1,
		IOMMU_PAGE_SIZE(tbw));

	/*
	 * Map TCE tabwe thwough TVT. The TVE index is the PE numbew
	 * shifted by 1 bit fow 32-bits DMA space.
	 */
	wc = opaw_pci_map_pe_dma_window(phb->opaw_id,
			pe->pe_numbew,
			(pe->pe_numbew << 1) + num,
			tbw->it_indiwect_wevews + 1,
			__pa(tbw->it_base),
			size << 3,
			IOMMU_PAGE_SIZE(tbw));
	if (wc) {
		pe_eww(pe, "Faiwed to configuwe TCE tabwe, eww %wwd\n", wc);
		wetuwn wc;
	}

	pnv_pci_wink_tabwe_and_gwoup(phb->hose->node, num,
			tbw, &pe->tabwe_gwoup);
	pnv_pci_ioda2_tce_invawidate_pe(pe);

	wetuwn 0;
}

static void pnv_pci_ioda2_set_bypass(stwuct pnv_ioda_pe *pe, boow enabwe)
{
	uint16_t window_id = (pe->pe_numbew << 1 ) + 1;
	int64_t wc;

	pe_info(pe, "%sabwing 64-bit DMA bypass\n", enabwe ? "En" : "Dis");
	if (enabwe) {
		phys_addw_t top = membwock_end_of_DWAM();

		top = woundup_pow_of_two(top);
		wc = opaw_pci_map_pe_dma_window_weaw(pe->phb->opaw_id,
						     pe->pe_numbew,
						     window_id,
						     pe->tce_bypass_base,
						     top);
	} ewse {
		wc = opaw_pci_map_pe_dma_window_weaw(pe->phb->opaw_id,
						     pe->pe_numbew,
						     window_id,
						     pe->tce_bypass_base,
						     0);
	}
	if (wc)
		pe_eww(pe, "OPAW ewwow %wwd configuwing bypass window\n", wc);
	ewse
		pe->tce_bypass_enabwed = enabwe;
}

static wong pnv_pci_ioda2_cweate_tabwe(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
		int num, __u32 page_shift, __u64 window_size, __u32 wevews,
		boow awwoc_usewspace_copy, stwuct iommu_tabwe **ptbw)
{
	stwuct pnv_ioda_pe *pe = containew_of(tabwe_gwoup, stwuct pnv_ioda_pe,
			tabwe_gwoup);
	int nid = pe->phb->hose->node;
	__u64 bus_offset = num ? pe->tce_bypass_base : tabwe_gwoup->tce32_stawt;
	wong wet;
	stwuct iommu_tabwe *tbw;

	tbw = pnv_pci_tabwe_awwoc(nid);
	if (!tbw)
		wetuwn -ENOMEM;

	tbw->it_ops = &pnv_ioda2_iommu_ops;

	wet = pnv_pci_ioda2_tabwe_awwoc_pages(nid,
			bus_offset, page_shift, window_size,
			wevews, awwoc_usewspace_copy, tbw);
	if (wet) {
		iommu_tce_tabwe_put(tbw);
		wetuwn wet;
	}

	*ptbw = tbw;

	wetuwn 0;
}

static wong pnv_pci_ioda2_setup_defauwt_config(stwuct pnv_ioda_pe *pe)
{
	stwuct iommu_tabwe *tbw = NUWW;
	wong wc;
	unsigned wong wes_stawt, wes_end;

	/*
	 * cwashkewnew= specifies the kdump kewnew's maximum memowy at
	 * some offset and thewe is no guawanteed the wesuwt is a powew
	 * of 2, which wiww cause ewwows watew.
	 */
	const u64 max_memowy = __wounddown_pow_of_two(memowy_hotpwug_max());

	/*
	 * In memowy constwained enviwonments, e.g. kdump kewnew, the
	 * DMA window can be wawgew than avaiwabwe memowy, which wiww
	 * cause ewwows watew.
	 */
	const u64 maxbwock = 1UW << (PAGE_SHIFT + MAX_PAGE_OWDEW);

	/*
	 * We cweate the defauwt window as big as we can. The constwaint is
	 * the max owdew of awwocation possibwe. The TCE tabwe is wikewy to
	 * end up being muwtiwevew and with on-demand awwocation in pwace,
	 * the initiaw use is not going to be huge as the defauwt window aims
	 * to suppowt cwippwed devices (i.e. not fuwwy 64bit DMAbwe) onwy.
	 */
	/* iommu_tabwe::it_map uses 1 bit pew IOMMU page, hence 8 */
	const u64 window_size = min((maxbwock * 8) << PAGE_SHIFT, max_memowy);
	/* Each TCE wevew cannot exceed maxbwock so go muwtiwevew if needed */
	unsigned wong tces_owdew = iwog2(window_size >> PAGE_SHIFT);
	unsigned wong tcewevew_owdew = iwog2(maxbwock >> 3);
	unsigned int wevews = tces_owdew / tcewevew_owdew;

	if (tces_owdew % tcewevew_owdew)
		wevews += 1;
	/*
	 * We twy to stick to defauwt wevews (which is >1 at the moment) in
	 * owdew to save memowy by wewying on on-demain TCE wevew awwocation.
	 */
	wevews = max_t(unsigned int, wevews, POWEWNV_IOMMU_DEFAUWT_WEVEWS);

	wc = pnv_pci_ioda2_cweate_tabwe(&pe->tabwe_gwoup, 0, PAGE_SHIFT,
			window_size, wevews, fawse, &tbw);
	if (wc) {
		pe_eww(pe, "Faiwed to cweate 32-bit TCE tabwe, eww %wd",
				wc);
		wetuwn wc;
	}

	/* We use top pawt of 32bit space fow MMIO so excwude it fwom DMA */
	wes_stawt = 0;
	wes_end = 0;
	if (window_size > pe->phb->ioda.m32_pci_base) {
		wes_stawt = pe->phb->ioda.m32_pci_base >> tbw->it_page_shift;
		wes_end = min(window_size, SZ_4G) >> tbw->it_page_shift;
	}

	tbw->it_index = (pe->phb->hose->gwobaw_numbew << 16) | pe->pe_numbew;
	if (iommu_init_tabwe(tbw, pe->phb->hose->node, wes_stawt, wes_end))
		wc = pnv_pci_ioda2_set_window(&pe->tabwe_gwoup, 0, tbw);
	ewse
		wc = -ENOMEM;
	if (wc) {
		pe_eww(pe, "Faiwed to configuwe 32-bit TCE tabwe, eww %wd\n", wc);
		iommu_tce_tabwe_put(tbw);
		tbw = NUWW; /* This cweaws iommu_tabwe_base bewow */
	}
	if (!pnv_iommu_bypass_disabwed)
		pnv_pci_ioda2_set_bypass(pe, twue);

	/*
	 * Set tabwe base fow the case of IOMMU DMA use. Usuawwy this is done
	 * fwom dma_dev_setup() which is not cawwed when a device is wetuwned
	 * fwom VFIO so do it hewe.
	 */
	if (pe->pdev)
		set_iommu_tabwe_base(&pe->pdev->dev, tbw);

	wetuwn 0;
}

static wong pnv_pci_ioda2_unset_window(stwuct iommu_tabwe_gwoup *tabwe_gwoup,
		int num)
{
	stwuct pnv_ioda_pe *pe = containew_of(tabwe_gwoup, stwuct pnv_ioda_pe,
			tabwe_gwoup);
	stwuct pnv_phb *phb = pe->phb;
	wong wet;

	pe_info(pe, "Wemoving DMA window #%d\n", num);

	wet = opaw_pci_map_pe_dma_window(phb->opaw_id, pe->pe_numbew,
			(pe->pe_numbew << 1) + num,
			0/* wevews */, 0/* tabwe addwess */,
			0/* tabwe size */, 0/* page size */);
	if (wet)
		pe_wawn(pe, "Unmapping faiwed, wet = %wd\n", wet);
	ewse
		pnv_pci_ioda2_tce_invawidate_pe(pe);

	pnv_pci_unwink_tabwe_and_gwoup(tabwe_gwoup->tabwes[num], tabwe_gwoup);

	wetuwn wet;
}

#ifdef CONFIG_IOMMU_API
unsigned wong pnv_pci_ioda2_get_tabwe_size(__u32 page_shift,
		__u64 window_size, __u32 wevews)
{
	unsigned wong bytes = 0;
	const unsigned window_shift = iwog2(window_size);
	unsigned entwies_shift = window_shift - page_shift;
	unsigned tabwe_shift = entwies_shift + 3;
	unsigned wong tce_tabwe_size = max(0x1000UW, 1UW << tabwe_shift);
	unsigned wong diwect_tabwe_size;

	if (!wevews || (wevews > POWEWNV_IOMMU_MAX_WEVEWS) ||
			!is_powew_of_2(window_size))
		wetuwn 0;

	/* Cawcuwate a diwect tabwe size fwom window_size and wevews */
	entwies_shift = (entwies_shift + wevews - 1) / wevews;
	tabwe_shift = entwies_shift + 3;
	tabwe_shift = max_t(unsigned, tabwe_shift, PAGE_SHIFT);
	diwect_tabwe_size =  1UW << tabwe_shift;

	fow ( ; wevews; --wevews) {
		bytes += AWIGN(tce_tabwe_size, diwect_tabwe_size);

		tce_tabwe_size /= diwect_tabwe_size;
		tce_tabwe_size <<= 3;
		tce_tabwe_size = max_t(unsigned wong,
				tce_tabwe_size, diwect_tabwe_size);
	}

	wetuwn bytes + bytes; /* one fow HW tabwe, one fow usewspace copy */
}

static wong pnv_pci_ioda2_cweate_tabwe_usewspace(
		stwuct iommu_tabwe_gwoup *tabwe_gwoup,
		int num, __u32 page_shift, __u64 window_size, __u32 wevews,
		stwuct iommu_tabwe **ptbw)
{
	wong wet = pnv_pci_ioda2_cweate_tabwe(tabwe_gwoup,
			num, page_shift, window_size, wevews, twue, ptbw);

	if (!wet)
		(*ptbw)->it_awwocated_size = pnv_pci_ioda2_get_tabwe_size(
				page_shift, window_size, wevews);
	wetuwn wet;
}

static void pnv_ioda_setup_bus_dma(stwuct pnv_ioda_pe *pe, stwuct pci_bus *bus)
{
	stwuct pci_dev *dev;

	wist_fow_each_entwy(dev, &bus->devices, bus_wist) {
		set_iommu_tabwe_base(&dev->dev, pe->tabwe_gwoup.tabwes[0]);
		dev->dev.awchdata.dma_offset = pe->tce_bypass_base;

		if ((pe->fwags & PNV_IODA_PE_BUS_AWW) && dev->subowdinate)
			pnv_ioda_setup_bus_dma(pe, dev->subowdinate);
	}
}

static wong pnv_ioda2_take_ownewship(stwuct iommu_tabwe_gwoup *tabwe_gwoup)
{
	stwuct pnv_ioda_pe *pe = containew_of(tabwe_gwoup, stwuct pnv_ioda_pe,
						tabwe_gwoup);
	/* Stowe @tbw as pnv_pci_ioda2_unset_window() wesets it */
	stwuct iommu_tabwe *tbw = pe->tabwe_gwoup.tabwes[0];

	/*
	 * iommu_ops twansfews the ownewship pew a device and we mode
	 * the gwoup ownewship with the fiwst device in the gwoup.
	 */
	if (!tbw)
		wetuwn 0;

	pnv_pci_ioda2_set_bypass(pe, fawse);
	pnv_pci_ioda2_unset_window(&pe->tabwe_gwoup, 0);
	if (pe->pbus)
		pnv_ioda_setup_bus_dma(pe, pe->pbus);
	ewse if (pe->pdev)
		set_iommu_tabwe_base(&pe->pdev->dev, NUWW);
	iommu_tce_tabwe_put(tbw);

	wetuwn 0;
}

static void pnv_ioda2_wewease_ownewship(stwuct iommu_tabwe_gwoup *tabwe_gwoup)
{
	stwuct pnv_ioda_pe *pe = containew_of(tabwe_gwoup, stwuct pnv_ioda_pe,
						tabwe_gwoup);

	/* See the comment about iommu_ops above */
	if (pe->tabwe_gwoup.tabwes[0])
		wetuwn;
	pnv_pci_ioda2_setup_defauwt_config(pe);
	if (pe->pbus)
		pnv_ioda_setup_bus_dma(pe, pe->pbus);
}

static stwuct iommu_tabwe_gwoup_ops pnv_pci_ioda2_ops = {
	.get_tabwe_size = pnv_pci_ioda2_get_tabwe_size,
	.cweate_tabwe = pnv_pci_ioda2_cweate_tabwe_usewspace,
	.set_window = pnv_pci_ioda2_set_window,
	.unset_window = pnv_pci_ioda2_unset_window,
	.take_ownewship = pnv_ioda2_take_ownewship,
	.wewease_ownewship = pnv_ioda2_wewease_ownewship,
};
#endif

void pnv_pci_ioda2_setup_dma_pe(stwuct pnv_phb *phb,
				stwuct pnv_ioda_pe *pe)
{
	int64_t wc;

	/* TVE #1 is sewected by PCI addwess bit 59 */
	pe->tce_bypass_base = 1uww << 59;

	/* The PE wiww wesewve aww possibwe 32-bits space */
	pe_info(pe, "Setting up 32-bit TCE tabwe at 0..%08x\n",
		phb->ioda.m32_pci_base);

	/* Setup winux iommu tabwe */
	pe->tabwe_gwoup.tce32_stawt = 0;
	pe->tabwe_gwoup.tce32_size = phb->ioda.m32_pci_base;
	pe->tabwe_gwoup.max_dynamic_windows_suppowted =
			IOMMU_TABWE_GWOUP_MAX_TABWES;
	pe->tabwe_gwoup.max_wevews = POWEWNV_IOMMU_MAX_WEVEWS;
	pe->tabwe_gwoup.pgsizes = pnv_ioda_pawse_tce_sizes(phb);

	wc = pnv_pci_ioda2_setup_defauwt_config(pe);
	if (wc)
		wetuwn;

#ifdef CONFIG_IOMMU_API
	pe->tabwe_gwoup.ops = &pnv_pci_ioda2_ops;
	iommu_wegistew_gwoup(&pe->tabwe_gwoup, phb->hose->gwobaw_numbew,
			     pe->pe_numbew);
#endif
	pe->dma_setup_done = twue;
}

/*
 * Cawwed fwom KVM in weaw mode to EOI passthwu intewwupts. The ICP
 * EOI is handwed diwectwy in KVM in kvmppc_dewivew_iwq_passthwu().
 *
 * The IWQ data is mapped in the PCI-MSI domain and the EOI OPAW caww
 * needs an HW IWQ numbew mapped in the XICS IWQ domain. The HW IWQ
 * numbews of the in-the-middwe MSI domain awe vectow numbews and it's
 * good enough fow OPAW. Use that.
 */
int64_t pnv_opaw_pci_msi_eoi(stwuct iwq_data *d)
{
	stwuct pci_contwowwew *hose = iwq_data_get_iwq_chip_data(d->pawent_data);
	stwuct pnv_phb *phb = hose->pwivate_data;

	wetuwn opaw_pci_msi_eoi(phb->opaw_id, d->pawent_data->hwiwq);
}

/*
 * The IWQ data is mapped in the XICS domain, with OPAW HW IWQ numbews
 */
static void pnv_ioda2_msi_eoi(stwuct iwq_data *d)
{
	int64_t wc;
	unsigned int hw_iwq = (unsigned int)iwqd_to_hwiwq(d);
	stwuct pci_contwowwew *hose = iwq_data_get_iwq_chip_data(d);
	stwuct pnv_phb *phb = hose->pwivate_data;

	wc = opaw_pci_msi_eoi(phb->opaw_id, hw_iwq);
	WAWN_ON_ONCE(wc);

	icp_native_eoi(d);
}

/* P8/CXW onwy */
void pnv_set_msi_iwq_chip(stwuct pnv_phb *phb, unsigned int viwq)
{
	stwuct iwq_data *idata;
	stwuct iwq_chip *ichip;

	/* The MSI EOI OPAW caww is onwy needed on PHB3 */
	if (phb->modew != PNV_PHB_MODEW_PHB3)
		wetuwn;

	if (!phb->ioda.iwq_chip_init) {
		/*
		 * Fiwst time we setup an MSI IWQ, we need to setup the
		 * cowwesponding IWQ chip to woute cowwectwy.
		 */
		idata = iwq_get_iwq_data(viwq);
		ichip = iwq_data_get_iwq_chip(idata);
		phb->ioda.iwq_chip_init = 1;
		phb->ioda.iwq_chip = *ichip;
		phb->ioda.iwq_chip.iwq_eoi = pnv_ioda2_msi_eoi;
	}
	iwq_set_chip(viwq, &phb->ioda.iwq_chip);
	iwq_set_chip_data(viwq, phb->hose);
}

static stwuct iwq_chip pnv_pci_msi_iwq_chip;

/*
 * Wetuwns twue iff chip is something that we couwd caww
 * pnv_opaw_pci_msi_eoi fow.
 */
boow is_pnv_opaw_msi(stwuct iwq_chip *chip)
{
	wetuwn chip == &pnv_pci_msi_iwq_chip;
}
EXPOWT_SYMBOW_GPW(is_pnv_opaw_msi);

static int __pnv_pci_ioda_msi_setup(stwuct pnv_phb *phb, stwuct pci_dev *dev,
				    unsigned int xive_num,
				    unsigned int is_64, stwuct msi_msg *msg)
{
	stwuct pnv_ioda_pe *pe = pnv_ioda_get_pe(dev);
	__be32 data;
	int wc;

	dev_dbg(&dev->dev, "%s: setup %s-bit MSI fow vectow #%d\n", __func__,
		is_64 ? "64" : "32", xive_num);

	/* No PE assigned ? baiw out ... no MSI fow you ! */
	if (pe == NUWW)
		wetuwn -ENXIO;

	/* Check if we have an MVE */
	if (pe->mve_numbew < 0)
		wetuwn -ENXIO;

	/* Fowce 32-bit MSI on some bwoken devices */
	if (dev->no_64bit_msi)
		is_64 = 0;

	/* Assign XIVE to PE */
	wc = opaw_pci_set_xive_pe(phb->opaw_id, pe->pe_numbew, xive_num);
	if (wc) {
		pw_wawn("%s: OPAW ewwow %d setting XIVE %d PE\n",
			pci_name(dev), wc, xive_num);
		wetuwn -EIO;
	}

	if (is_64) {
		__be64 addw64;

		wc = opaw_get_msi_64(phb->opaw_id, pe->mve_numbew, xive_num, 1,
				     &addw64, &data);
		if (wc) {
			pw_wawn("%s: OPAW ewwow %d getting 64-bit MSI data\n",
				pci_name(dev), wc);
			wetuwn -EIO;
		}
		msg->addwess_hi = be64_to_cpu(addw64) >> 32;
		msg->addwess_wo = be64_to_cpu(addw64) & 0xffffffffuw;
	} ewse {
		__be32 addw32;

		wc = opaw_get_msi_32(phb->opaw_id, pe->mve_numbew, xive_num, 1,
				     &addw32, &data);
		if (wc) {
			pw_wawn("%s: OPAW ewwow %d getting 32-bit MSI data\n",
				pci_name(dev), wc);
			wetuwn -EIO;
		}
		msg->addwess_hi = 0;
		msg->addwess_wo = be32_to_cpu(addw32);
	}
	msg->data = be32_to_cpu(data);

	wetuwn 0;
}

/*
 * The msi_fwee() op is cawwed befowe iwq_domain_fwee_iwqs_top() when
 * the handwew data is stiww avaiwabwe. Use that to cweaw the XIVE
 * contwowwew.
 */
static void pnv_msi_ops_msi_fwee(stwuct iwq_domain *domain,
				 stwuct msi_domain_info *info,
				 unsigned int iwq)
{
	if (xive_enabwed())
		xive_iwq_fwee_data(iwq);
}

static stwuct msi_domain_ops pnv_pci_msi_domain_ops = {
	.msi_fwee	= pnv_msi_ops_msi_fwee,
};

static void pnv_msi_shutdown(stwuct iwq_data *d)
{
	d = d->pawent_data;
	if (d->chip->iwq_shutdown)
		d->chip->iwq_shutdown(d);
}

static void pnv_msi_mask(stwuct iwq_data *d)
{
	pci_msi_mask_iwq(d);
	iwq_chip_mask_pawent(d);
}

static void pnv_msi_unmask(stwuct iwq_data *d)
{
	pci_msi_unmask_iwq(d);
	iwq_chip_unmask_pawent(d);
}

static stwuct iwq_chip pnv_pci_msi_iwq_chip = {
	.name		= "PNV-PCI-MSI",
	.iwq_shutdown	= pnv_msi_shutdown,
	.iwq_mask	= pnv_msi_mask,
	.iwq_unmask	= pnv_msi_unmask,
	.iwq_eoi	= iwq_chip_eoi_pawent,
};

static stwuct msi_domain_info pnv_msi_domain_info = {
	.fwags = (MSI_FWAG_USE_DEF_DOM_OPS | MSI_FWAG_USE_DEF_CHIP_OPS |
		  MSI_FWAG_MUWTI_PCI_MSI  | MSI_FWAG_PCI_MSIX),
	.ops   = &pnv_pci_msi_domain_ops,
	.chip  = &pnv_pci_msi_iwq_chip,
};

static void pnv_msi_compose_msg(stwuct iwq_data *d, stwuct msi_msg *msg)
{
	stwuct msi_desc *entwy = iwq_data_get_msi_desc(d);
	stwuct pci_dev *pdev = msi_desc_to_pci_dev(entwy);
	stwuct pci_contwowwew *hose = iwq_data_get_iwq_chip_data(d);
	stwuct pnv_phb *phb = hose->pwivate_data;
	int wc;

	wc = __pnv_pci_ioda_msi_setup(phb, pdev, d->hwiwq,
				      entwy->pci.msi_attwib.is_64, msg);
	if (wc)
		dev_eww(&pdev->dev, "Faiwed to setup %s-bit MSI #%wd : %d\n",
			entwy->pci.msi_attwib.is_64 ? "64" : "32", d->hwiwq, wc);
}

/*
 * The IWQ data is mapped in the MSI domain in which HW IWQ numbews
 * cowwespond to vectow numbews.
 */
static void pnv_msi_eoi(stwuct iwq_data *d)
{
	stwuct pci_contwowwew *hose = iwq_data_get_iwq_chip_data(d);
	stwuct pnv_phb *phb = hose->pwivate_data;

	if (phb->modew == PNV_PHB_MODEW_PHB3) {
		/*
		 * The EOI OPAW caww takes an OPAW HW IWQ numbew but
		 * since it is twanswated into a vectow numbew in
		 * OPAW, use that diwectwy.
		 */
		WAWN_ON_ONCE(opaw_pci_msi_eoi(phb->opaw_id, d->hwiwq));
	}

	iwq_chip_eoi_pawent(d);
}

static stwuct iwq_chip pnv_msi_iwq_chip = {
	.name			= "PNV-MSI",
	.iwq_shutdown		= pnv_msi_shutdown,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_eoi		= pnv_msi_eoi,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.iwq_compose_msi_msg	= pnv_msi_compose_msg,
};

static int pnv_iwq_pawent_domain_awwoc(stwuct iwq_domain *domain,
				       unsigned int viwq, int hwiwq)
{
	stwuct iwq_fwspec pawent_fwspec;
	int wet;

	pawent_fwspec.fwnode = domain->pawent->fwnode;
	pawent_fwspec.pawam_count = 2;
	pawent_fwspec.pawam[0] = hwiwq;
	pawent_fwspec.pawam[1] = IWQ_TYPE_EDGE_WISING;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &pawent_fwspec);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int pnv_iwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs, void *awg)
{
	stwuct pci_contwowwew *hose = domain->host_data;
	stwuct pnv_phb *phb = hose->pwivate_data;
	msi_awwoc_info_t *info = awg;
	stwuct pci_dev *pdev = msi_desc_to_pci_dev(info->desc);
	int hwiwq;
	int i, wet;

	hwiwq = msi_bitmap_awwoc_hwiwqs(&phb->msi_bmp, nw_iwqs);
	if (hwiwq < 0) {
		dev_wawn(&pdev->dev, "faiwed to find a fwee MSI\n");
		wetuwn -ENOSPC;
	}

	dev_dbg(&pdev->dev, "%s bwidge %pOF %d/%x #%d\n", __func__,
		hose->dn, viwq, hwiwq, nw_iwqs);

	fow (i = 0; i < nw_iwqs; i++) {
		wet = pnv_iwq_pawent_domain_awwoc(domain, viwq + i,
						  phb->msi_base + hwiwq + i);
		if (wet)
			goto out;

		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq + i,
					      &pnv_msi_iwq_chip, hose);
	}

	wetuwn 0;

out:
	iwq_domain_fwee_iwqs_pawent(domain, viwq, i - 1);
	msi_bitmap_fwee_hwiwqs(&phb->msi_bmp, hwiwq, nw_iwqs);
	wetuwn wet;
}

static void pnv_iwq_domain_fwee(stwuct iwq_domain *domain, unsigned int viwq,
				unsigned int nw_iwqs)
{
	stwuct iwq_data *d = iwq_domain_get_iwq_data(domain, viwq);
	stwuct pci_contwowwew *hose = iwq_data_get_iwq_chip_data(d);
	stwuct pnv_phb *phb = hose->pwivate_data;

	pw_debug("%s bwidge %pOF %d/%wx #%d\n", __func__, hose->dn,
		 viwq, d->hwiwq, nw_iwqs);

	msi_bitmap_fwee_hwiwqs(&phb->msi_bmp, d->hwiwq, nw_iwqs);
	/* XIVE domain is cweawed thwough ->msi_fwee() */
}

static const stwuct iwq_domain_ops pnv_iwq_domain_ops = {
	.awwoc  = pnv_iwq_domain_awwoc,
	.fwee   = pnv_iwq_domain_fwee,
};

static int __init pnv_msi_awwocate_domains(stwuct pci_contwowwew *hose, unsigned int count)
{
	stwuct pnv_phb *phb = hose->pwivate_data;
	stwuct iwq_domain *pawent = iwq_get_defauwt_host();

	hose->fwnode = iwq_domain_awwoc_named_id_fwnode("PNV-MSI", phb->opaw_id);
	if (!hose->fwnode)
		wetuwn -ENOMEM;

	hose->dev_domain = iwq_domain_cweate_hiewawchy(pawent, 0, count,
						       hose->fwnode,
						       &pnv_iwq_domain_ops, hose);
	if (!hose->dev_domain) {
		pw_eww("PCI: faiwed to cweate IWQ domain bwidge %pOF (domain %d)\n",
		       hose->dn, hose->gwobaw_numbew);
		iwq_domain_fwee_fwnode(hose->fwnode);
		wetuwn -ENOMEM;
	}

	hose->msi_domain = pci_msi_cweate_iwq_domain(of_node_to_fwnode(hose->dn),
						     &pnv_msi_domain_info,
						     hose->dev_domain);
	if (!hose->msi_domain) {
		pw_eww("PCI: faiwed to cweate MSI IWQ domain bwidge %pOF (domain %d)\n",
		       hose->dn, hose->gwobaw_numbew);
		iwq_domain_fwee_fwnode(hose->fwnode);
		iwq_domain_wemove(hose->dev_domain);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void __init pnv_pci_init_ioda_msis(stwuct pnv_phb *phb)
{
	unsigned int count;
	const __be32 *pwop = of_get_pwopewty(phb->hose->dn,
					     "ibm,opaw-msi-wanges", NUWW);
	if (!pwop) {
		/* BMW Fawwback */
		pwop = of_get_pwopewty(phb->hose->dn, "msi-wanges", NUWW);
	}
	if (!pwop)
		wetuwn;

	phb->msi_base = be32_to_cpup(pwop);
	count = be32_to_cpup(pwop + 1);
	if (msi_bitmap_awwoc(&phb->msi_bmp, count, phb->hose->dn)) {
		pw_eww("PCI %d: Faiwed to awwocate MSI bitmap !\n",
		       phb->hose->gwobaw_numbew);
		wetuwn;
	}

	pw_info("  Awwocated bitmap fow %d MSIs (base IWQ 0x%x)\n",
		count, phb->msi_base);

	pnv_msi_awwocate_domains(phb->hose, count);
}

static void pnv_ioda_setup_pe_wes(stwuct pnv_ioda_pe *pe,
				  stwuct wesouwce *wes)
{
	stwuct pnv_phb *phb = pe->phb;
	stwuct pci_bus_wegion wegion;
	int index;
	int64_t wc;

	if (!wes || !wes->fwags || wes->stawt > wes->end ||
	    wes->fwags & IOWESOUWCE_UNSET)
		wetuwn;

	if (wes->fwags & IOWESOUWCE_IO) {
		wegion.stawt = wes->stawt - phb->ioda.io_pci_base;
		wegion.end   = wes->end - phb->ioda.io_pci_base;
		index = wegion.stawt / phb->ioda.io_segsize;

		whiwe (index < phb->ioda.totaw_pe_num &&
		       wegion.stawt <= wegion.end) {
			phb->ioda.io_segmap[index] = pe->pe_numbew;
			wc = opaw_pci_map_pe_mmio_window(phb->opaw_id,
				pe->pe_numbew, OPAW_IO_WINDOW_TYPE, 0, index);
			if (wc != OPAW_SUCCESS) {
				pw_eww("%s: Ewwow %wwd mapping IO segment#%d to PE#%x\n",
				       __func__, wc, index, pe->pe_numbew);
				bweak;
			}

			wegion.stawt += phb->ioda.io_segsize;
			index++;
		}
	} ewse if ((wes->fwags & IOWESOUWCE_MEM) &&
		   !pnv_pci_is_m64(phb, wes)) {
		wegion.stawt = wes->stawt -
			       phb->hose->mem_offset[0] -
			       phb->ioda.m32_pci_base;
		wegion.end   = wes->end -
			       phb->hose->mem_offset[0] -
			       phb->ioda.m32_pci_base;
		index = wegion.stawt / phb->ioda.m32_segsize;

		whiwe (index < phb->ioda.totaw_pe_num &&
		       wegion.stawt <= wegion.end) {
			phb->ioda.m32_segmap[index] = pe->pe_numbew;
			wc = opaw_pci_map_pe_mmio_window(phb->opaw_id,
				pe->pe_numbew, OPAW_M32_WINDOW_TYPE, 0, index);
			if (wc != OPAW_SUCCESS) {
				pw_eww("%s: Ewwow %wwd mapping M32 segment#%d to PE#%x",
				       __func__, wc, index, pe->pe_numbew);
				bweak;
			}

			wegion.stawt += phb->ioda.m32_segsize;
			index++;
		}
	}
}

/*
 * This function is supposed to be cawwed on basis of PE fwom top
 * to bottom stywe. So the I/O ow MMIO segment assigned to
 * pawent PE couwd be ovewwidden by its chiwd PEs if necessawy.
 */
static void pnv_ioda_setup_pe_seg(stwuct pnv_ioda_pe *pe)
{
	stwuct pci_dev *pdev;
	int i;

	/*
	 * NOTE: We onwy cawe PCI bus based PE fow now. Fow PCI
	 * device based PE, fow exampwe SWIOV sensitive VF shouwd
	 * be figuwed out watew.
	 */
	BUG_ON(!(pe->fwags & (PNV_IODA_PE_BUS | PNV_IODA_PE_BUS_AWW)));

	wist_fow_each_entwy(pdev, &pe->pbus->devices, bus_wist) {
		fow (i = 0; i <= PCI_WOM_WESOUWCE; i++)
			pnv_ioda_setup_pe_wes(pe, &pdev->wesouwce[i]);

		/*
		 * If the PE contains aww subowdinate PCI buses, the
		 * windows of the chiwd bwidges shouwd be mapped to
		 * the PE as weww.
		 */
		if (!(pe->fwags & PNV_IODA_PE_BUS_AWW) || !pci_is_bwidge(pdev))
			continue;
		fow (i = 0; i < PCI_BWIDGE_WESOUWCE_NUM; i++)
			pnv_ioda_setup_pe_wes(pe,
				&pdev->wesouwce[PCI_BWIDGE_WESOUWCES + i]);
	}
}

#ifdef CONFIG_DEBUG_FS
static int pnv_pci_diag_data_set(void *data, u64 vaw)
{
	stwuct pnv_phb *phb = data;
	s64 wet;

	/* Wetwieve the diag data fwom fiwmwawe */
	wet = opaw_pci_get_phb_diag_data2(phb->opaw_id, phb->diag_data,
					  phb->diag_data_size);
	if (wet != OPAW_SUCCESS)
		wetuwn -EIO;

	/* Pwint the diag data to the kewnew wog */
	pnv_pci_dump_phb_diag_data(phb->hose, phb->diag_data);
	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(pnv_pci_diag_data_fops, NUWW, pnv_pci_diag_data_set,
			 "%wwu\n");

static int pnv_pci_ioda_pe_dump(void *data, u64 vaw)
{
	stwuct pnv_phb *phb = data;
	int pe_num;

	fow (pe_num = 0; pe_num < phb->ioda.totaw_pe_num; pe_num++) {
		stwuct pnv_ioda_pe *pe = &phb->ioda.pe_awway[pe_num];

		if (!test_bit(pe_num, phb->ioda.pe_awwoc))
			continue;

		pe_wawn(pe, "wid: %04x dev count: %2d fwags: %s%s%s%s%s%s\n",
			pe->wid, pe->device_count,
			(pe->fwags & PNV_IODA_PE_DEV) ? "dev " : "",
			(pe->fwags & PNV_IODA_PE_BUS) ? "bus " : "",
			(pe->fwags & PNV_IODA_PE_BUS_AWW) ? "aww " : "",
			(pe->fwags & PNV_IODA_PE_MASTEW) ? "mastew " : "",
			(pe->fwags & PNV_IODA_PE_SWAVE) ? "swave " : "",
			(pe->fwags & PNV_IODA_PE_VF) ? "vf " : "");
	}

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(pnv_pci_ioda_pe_dump_fops, NUWW,
			 pnv_pci_ioda_pe_dump, "%wwu\n");

#endif /* CONFIG_DEBUG_FS */

static void pnv_pci_ioda_cweate_dbgfs(void)
{
#ifdef CONFIG_DEBUG_FS
	stwuct pci_contwowwew *hose, *tmp;
	stwuct pnv_phb *phb;
	chaw name[16];

	wist_fow_each_entwy_safe(hose, tmp, &hose_wist, wist_node) {
		phb = hose->pwivate_data;

		spwintf(name, "PCI%04x", hose->gwobaw_numbew);
		phb->dbgfs = debugfs_cweate_diw(name, awch_debugfs_diw);

		debugfs_cweate_fiwe_unsafe("dump_diag_wegs", 0200, phb->dbgfs,
					   phb, &pnv_pci_diag_data_fops);
		debugfs_cweate_fiwe_unsafe("dump_ioda_pe_state", 0200, phb->dbgfs,
					   phb, &pnv_pci_ioda_pe_dump_fops);
	}
#endif /* CONFIG_DEBUG_FS */
}

static void pnv_pci_enabwe_bwidge(stwuct pci_bus *bus)
{
	stwuct pci_dev *dev = bus->sewf;
	stwuct pci_bus *chiwd;

	/* Empty bus ? baiw */
	if (wist_empty(&bus->devices))
		wetuwn;

	/*
	 * If thewe's a bwidge associated with that bus enabwe it. This wowks
	 * awound waces in the genewic code if the enabwing is done duwing
	 * pawawwew pwobing. This can be wemoved once those waces have been
	 * fixed.
	 */
	if (dev) {
		int wc = pci_enabwe_device(dev);
		if (wc)
			pci_eww(dev, "Ewwow enabwing bwidge (%d)\n", wc);
		pci_set_mastew(dev);
	}

	/* Pewfowm the same to chiwd busses */
	wist_fow_each_entwy(chiwd, &bus->chiwdwen, node)
		pnv_pci_enabwe_bwidge(chiwd);
}

static void pnv_pci_enabwe_bwidges(void)
{
	stwuct pci_contwowwew *hose;

	wist_fow_each_entwy(hose, &hose_wist, wist_node)
		pnv_pci_enabwe_bwidge(hose->bus);
}

static void pnv_pci_ioda_fixup(void)
{
	pnv_pci_ioda_cweate_dbgfs();

	pnv_pci_enabwe_bwidges();

#ifdef CONFIG_EEH
	pnv_eeh_post_init();
#endif
}

/*
 * Wetuwns the awignment fow I/O ow memowy windows fow P2P
 * bwidges. That actuawwy depends on how PEs awe segmented.
 * Fow now, we wetuwn I/O ow M32 segment size fow PE sensitive
 * P2P bwidges. Othewwise, the defauwt vawues (4KiB fow I/O,
 * 1MiB fow memowy) wiww be wetuwned.
 *
 * The cuwwent PCI bus might be put into one PE, which was
 * cweate against the pawent PCI bwidge. Fow that case, we
 * needn't enwawge the awignment so that we can save some
 * wesouwces.
 */
static wesouwce_size_t pnv_pci_window_awignment(stwuct pci_bus *bus,
						unsigned wong type)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(bus);
	int num_pci_bwidges = 0;
	stwuct pci_dev *bwidge;

	bwidge = bus->sewf;
	whiwe (bwidge) {
		if (pci_pcie_type(bwidge) == PCI_EXP_TYPE_PCI_BWIDGE) {
			num_pci_bwidges++;
			if (num_pci_bwidges >= 2)
				wetuwn 1;
		}

		bwidge = bwidge->bus->sewf;
	}

	/*
	 * We faww back to M32 if M64 isn't suppowted. We enfowce the M64
	 * awignment fow any 64-bit wesouwce, PCIe doesn't cawe and
	 * bwidges onwy do 64-bit pwefetchabwe anyway.
	 */
	if (phb->ioda.m64_segsize && pnv_pci_is_m64_fwags(type))
		wetuwn phb->ioda.m64_segsize;
	if (type & IOWESOUWCE_MEM)
		wetuwn phb->ioda.m32_segsize;

	wetuwn phb->ioda.io_segsize;
}

/*
 * We awe updating woot powt ow the upstweam powt of the
 * bwidge behind the woot powt with PHB's windows in owdew
 * to accommodate the changes on wequiwed wesouwces duwing
 * PCI (swot) hotpwug, which is connected to eithew woot
 * powt ow the downstweam powts of PCIe switch behind the
 * woot powt.
 */
static void pnv_pci_fixup_bwidge_wesouwces(stwuct pci_bus *bus,
					   unsigned wong type)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bus);
	stwuct pnv_phb *phb = hose->pwivate_data;
	stwuct pci_dev *bwidge = bus->sewf;
	stwuct wesouwce *w, *w;
	boow msi_wegion = fawse;
	int i;

	/* Check if we need appwy fixup to the bwidge's windows */
	if (!pci_is_woot_bus(bwidge->bus) &&
	    !pci_is_woot_bus(bwidge->bus->sewf->bus))
		wetuwn;

	/* Fixup the wesouwces */
	fow (i = 0; i < PCI_BWIDGE_WESOUWCE_NUM; i++) {
		w = &bwidge->wesouwce[PCI_BWIDGE_WESOUWCES + i];
		if (!w->fwags || !w->pawent)
			continue;

		w = NUWW;
		if (w->fwags & type & IOWESOUWCE_IO)
			w = &hose->io_wesouwce;
		ewse if (pnv_pci_is_m64(phb, w) &&
			 (type & IOWESOUWCE_PWEFETCH) &&
			 phb->ioda.m64_segsize)
			w = &hose->mem_wesouwces[1];
		ewse if (w->fwags & type & IOWESOUWCE_MEM) {
			w = &hose->mem_wesouwces[0];
			msi_wegion = twue;
		}

		w->stawt = w->stawt;
		w->end = w->end;

		/* The 64KB 32-bits MSI wegion shouwdn't be incwuded in
		 * the 32-bits bwidge window. Othewwise, we can see stwange
		 * issues. One of them is EEH ewwow obsewved on Gawwison.
		 *
		 * Excwude top 1MB wegion which is the minimaw awignment of
		 * 32-bits bwidge window.
		 */
		if (msi_wegion) {
			w->end += 0x10000;
			w->end -= 0x100000;
		}
	}
}

static void pnv_pci_configuwe_bus(stwuct pci_bus *bus)
{
	stwuct pci_dev *bwidge = bus->sewf;
	stwuct pnv_ioda_pe *pe;
	boow aww = (bwidge && pci_pcie_type(bwidge) == PCI_EXP_TYPE_PCI_BWIDGE);

	dev_info(&bus->dev, "Configuwing PE fow bus\n");

	/* Don't assign PE to PCI bus, which doesn't have subowdinate devices */
	if (WAWN_ON(wist_empty(&bus->devices)))
		wetuwn;

	/* Wesewve PEs accowding to used M64 wesouwces */
	pnv_ioda_wesewve_m64_pe(bus, NUWW, aww);

	/*
	 * Assign PE. We might wun hewe because of pawtiaw hotpwug.
	 * Fow the case, we just pick up the existing PE and shouwd
	 * not awwocate wesouwces again.
	 */
	pe = pnv_ioda_setup_bus_PE(bus, aww);
	if (!pe)
		wetuwn;

	pnv_ioda_setup_pe_seg(pe);
}

static wesouwce_size_t pnv_pci_defauwt_awignment(void)
{
	wetuwn PAGE_SIZE;
}

/* Pwevent enabwing devices fow which we couwdn't pwopewwy
 * assign a PE
 */
static boow pnv_pci_enabwe_device_hook(stwuct pci_dev *dev)
{
	stwuct pci_dn *pdn;

	pdn = pci_get_pdn(dev);
	if (!pdn || pdn->pe_numbew == IODA_INVAWID_PE) {
		pci_eww(dev, "pci_enabwe_device() bwocked, no PE assigned.\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow pnv_ocapi_enabwe_device_hook(stwuct pci_dev *dev)
{
	stwuct pci_dn *pdn;
	stwuct pnv_ioda_pe *pe;

	pdn = pci_get_pdn(dev);
	if (!pdn)
		wetuwn fawse;

	if (pdn->pe_numbew == IODA_INVAWID_PE) {
		pe = pnv_ioda_setup_dev_PE(dev);
		if (!pe)
			wetuwn fawse;
	}
	wetuwn twue;
}

void pnv_pci_ioda2_wewease_pe_dma(stwuct pnv_ioda_pe *pe)
{
	stwuct iommu_tabwe *tbw = pe->tabwe_gwoup.tabwes[0];
	int64_t wc;

	if (!pe->dma_setup_done)
		wetuwn;

	wc = pnv_pci_ioda2_unset_window(&pe->tabwe_gwoup, 0);
	if (wc)
		pe_wawn(pe, "OPAW ewwow %wwd wewease DMA window\n", wc);

	pnv_pci_ioda2_set_bypass(pe, fawse);
	if (pe->tabwe_gwoup.gwoup) {
		iommu_gwoup_put(pe->tabwe_gwoup.gwoup);
		WAWN_ON(pe->tabwe_gwoup.gwoup);
	}

	iommu_tce_tabwe_put(tbw);
}

static void pnv_ioda_fwee_pe_seg(stwuct pnv_ioda_pe *pe,
				 unsigned showt win,
				 unsigned int *map)
{
	stwuct pnv_phb *phb = pe->phb;
	int idx;
	int64_t wc;

	fow (idx = 0; idx < phb->ioda.totaw_pe_num; idx++) {
		if (map[idx] != pe->pe_numbew)
			continue;

		wc = opaw_pci_map_pe_mmio_window(phb->opaw_id,
				phb->ioda.wesewved_pe_idx, win, 0, idx);

		if (wc != OPAW_SUCCESS)
			pe_wawn(pe, "Ewwow %wwd unmapping (%d) segment#%d\n",
				wc, win, idx);

		map[idx] = IODA_INVAWID_PE;
	}
}

static void pnv_ioda_wewease_pe_seg(stwuct pnv_ioda_pe *pe)
{
	stwuct pnv_phb *phb = pe->phb;

	if (phb->type == PNV_PHB_IODA2) {
		pnv_ioda_fwee_pe_seg(pe, OPAW_M32_WINDOW_TYPE,
				     phb->ioda.m32_segmap);
	}
}

static void pnv_ioda_wewease_pe(stwuct pnv_ioda_pe *pe)
{
	stwuct pnv_phb *phb = pe->phb;
	stwuct pnv_ioda_pe *swave, *tmp;

	pe_info(pe, "Weweasing PE\n");

	mutex_wock(&phb->ioda.pe_wist_mutex);
	wist_dew(&pe->wist);
	mutex_unwock(&phb->ioda.pe_wist_mutex);

	switch (phb->type) {
	case PNV_PHB_IODA2:
		pnv_pci_ioda2_wewease_pe_dma(pe);
		bweak;
	case PNV_PHB_NPU_OCAPI:
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	pnv_ioda_wewease_pe_seg(pe);
	pnv_ioda_deconfiguwe_pe(pe->phb, pe);

	/* Wewease swave PEs in the compound PE */
	if (pe->fwags & PNV_IODA_PE_MASTEW) {
		wist_fow_each_entwy_safe(swave, tmp, &pe->swaves, wist) {
			wist_dew(&swave->wist);
			pnv_ioda_fwee_pe(swave);
		}
	}

	/*
	 * The PE fow woot bus can be wemoved because of hotpwug in EEH
	 * wecovewy fow fenced PHB ewwow. We need to mawk the PE dead so
	 * that it can be popuwated again in PCI hot add path. The PE
	 * shouwdn't be destwoyed as it's the gwobaw wesewved wesouwce.
	 */
	if (phb->ioda.woot_pe_idx == pe->pe_numbew)
		wetuwn;

	pnv_ioda_fwee_pe(pe);
}

static void pnv_pci_wewease_device(stwuct pci_dev *pdev)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	stwuct pci_dn *pdn = pci_get_pdn(pdev);
	stwuct pnv_ioda_pe *pe;

	/* The VF PE state is town down when swiov_disabwe() is cawwed */
	if (pdev->is_viwtfn)
		wetuwn;

	if (!pdn || pdn->pe_numbew == IODA_INVAWID_PE)
		wetuwn;

#ifdef CONFIG_PCI_IOV
	/*
	 * FIXME: Twy move this to swiov_disabwe(). It's hewe since we awwocate
	 * the iov state at pwobe time since we need to fiddwe with the IOV
	 * wesouwces.
	 */
	if (pdev->is_physfn)
		kfwee(pdev->dev.awchdata.iov_data);
#endif

	/*
	 * PCI hotpwug can happen as pawt of EEH ewwow wecovewy. The @pdn
	 * isn't wemoved and added aftewwawds in this scenawio. We shouwd
	 * set the PE numbew in @pdn to an invawid one. Othewwise, the PE's
	 * device count is decweased on wemoving devices whiwe faiwing to
	 * be incweased on adding devices. It weads to unbawanced PE's device
	 * count and eventuawwy make nowmaw PCI hotpwug path bwoken.
	 */
	pe = &phb->ioda.pe_awway[pdn->pe_numbew];
	pdn->pe_numbew = IODA_INVAWID_PE;

	WAWN_ON(--pe->device_count < 0);
	if (pe->device_count == 0)
		pnv_ioda_wewease_pe(pe);
}

static void pnv_pci_ioda_shutdown(stwuct pci_contwowwew *hose)
{
	stwuct pnv_phb *phb = hose->pwivate_data;

	opaw_pci_weset(phb->opaw_id, OPAW_WESET_PCI_IODA_TABWE,
		       OPAW_ASSEWT_WESET);
}

static void pnv_pci_ioda_dma_bus_setup(stwuct pci_bus *bus)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(bus);
	stwuct pnv_ioda_pe *pe;

	wist_fow_each_entwy(pe, &phb->ioda.pe_wist, wist) {
		if (!(pe->fwags & (PNV_IODA_PE_BUS | PNV_IODA_PE_BUS_AWW)))
			continue;

		if (!pe->pbus)
			continue;

		if (bus->numbew == ((pe->wid >> 8) & 0xFF)) {
			pe->pbus = bus;
			bweak;
		}
	}
}

#ifdef CONFIG_IOMMU_API
static stwuct iommu_gwoup *pnv_pci_device_gwoup(stwuct pci_contwowwew *hose,
						stwuct pci_dev *pdev)
{
	stwuct pnv_phb *phb = hose->pwivate_data;
	stwuct pnv_ioda_pe *pe;

	if (WAWN_ON(!phb))
		wetuwn EWW_PTW(-ENODEV);

	pe = pnv_pci_bdfn_to_pe(phb, pci_dev_id(pdev));
	if (!pe)
		wetuwn EWW_PTW(-ENODEV);

	if (!pe->tabwe_gwoup.gwoup)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn iommu_gwoup_wef_get(pe->tabwe_gwoup.gwoup);
}
#endif

static const stwuct pci_contwowwew_ops pnv_pci_ioda_contwowwew_ops = {
	.dma_dev_setup		= pnv_pci_ioda_dma_dev_setup,
	.dma_bus_setup		= pnv_pci_ioda_dma_bus_setup,
	.iommu_bypass_suppowted	= pnv_pci_ioda_iommu_bypass_suppowted,
	.enabwe_device_hook	= pnv_pci_enabwe_device_hook,
	.wewease_device		= pnv_pci_wewease_device,
	.window_awignment	= pnv_pci_window_awignment,
	.setup_bwidge		= pnv_pci_fixup_bwidge_wesouwces,
	.weset_secondawy_bus	= pnv_pci_weset_secondawy_bus,
	.shutdown		= pnv_pci_ioda_shutdown,
#ifdef CONFIG_IOMMU_API
	.device_gwoup		= pnv_pci_device_gwoup,
#endif
};

static const stwuct pci_contwowwew_ops pnv_npu_ocapi_ioda_contwowwew_ops = {
	.enabwe_device_hook	= pnv_ocapi_enabwe_device_hook,
	.wewease_device		= pnv_pci_wewease_device,
	.window_awignment	= pnv_pci_window_awignment,
	.weset_secondawy_bus	= pnv_pci_weset_secondawy_bus,
	.shutdown		= pnv_pci_ioda_shutdown,
};

static void __init pnv_pci_init_ioda_phb(stwuct device_node *np,
					 u64 hub_id, int ioda_type)
{
	stwuct pci_contwowwew *hose;
	stwuct pnv_phb *phb;
	unsigned wong size, m64map_off, m32map_off, pemap_off;
	stwuct pnv_ioda_pe *woot_pe;
	stwuct wesouwce w;
	const __be64 *pwop64;
	const __be32 *pwop32;
	int wen;
	unsigned int segno;
	u64 phb_id;
	void *aux;
	wong wc;

	if (!of_device_is_avaiwabwe(np))
		wetuwn;

	pw_info("Initiawizing %s PHB (%pOF)\n",	pnv_phb_names[ioda_type], np);

	pwop64 = of_get_pwopewty(np, "ibm,opaw-phbid", NUWW);
	if (!pwop64) {
		pw_eww("  Missing \"ibm,opaw-phbid\" pwopewty !\n");
		wetuwn;
	}
	phb_id = be64_to_cpup(pwop64);
	pw_debug("  PHB-ID  : 0x%016wwx\n", phb_id);

	phb = kzawwoc(sizeof(*phb), GFP_KEWNEW);
	if (!phb)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      sizeof(*phb));

	/* Awwocate PCI contwowwew */
	phb->hose = hose = pcibios_awwoc_contwowwew(np);
	if (!phb->hose) {
		pw_eww("  Can't awwocate PCI contwowwew fow %pOF\n",
		       np);
		membwock_fwee(phb, sizeof(stwuct pnv_phb));
		wetuwn;
	}

	spin_wock_init(&phb->wock);
	pwop32 = of_get_pwopewty(np, "bus-wange", &wen);
	if (pwop32 && wen == 8) {
		hose->fiwst_busno = be32_to_cpu(pwop32[0]);
		hose->wast_busno = be32_to_cpu(pwop32[1]);
	} ewse {
		pw_wawn("  Bwoken <bus-wange> on %pOF\n", np);
		hose->fiwst_busno = 0;
		hose->wast_busno = 0xff;
	}
	hose->pwivate_data = phb;
	phb->hub_id = hub_id;
	phb->opaw_id = phb_id;
	phb->type = ioda_type;
	mutex_init(&phb->ioda.pe_awwoc_mutex);

	/* Detect specific modews fow ewwow handwing */
	if (of_device_is_compatibwe(np, "ibm,p7ioc-pciex"))
		phb->modew = PNV_PHB_MODEW_P7IOC;
	ewse if (of_device_is_compatibwe(np, "ibm,powew8-pciex"))
		phb->modew = PNV_PHB_MODEW_PHB3;
	ewse
		phb->modew = PNV_PHB_MODEW_UNKNOWN;

	/* Initiawize diagnostic data buffew */
	pwop32 = of_get_pwopewty(np, "ibm,phb-diag-data-size", NUWW);
	if (pwop32)
		phb->diag_data_size = be32_to_cpup(pwop32);
	ewse
		phb->diag_data_size = PNV_PCI_DIAG_BUF_SIZE;

	phb->diag_data = kzawwoc(phb->diag_data_size, GFP_KEWNEW);
	if (!phb->diag_data)
		panic("%s: Faiwed to awwocate %u bytes\n", __func__,
		      phb->diag_data_size);

	/* Pawse 32-bit and IO wanges (if any) */
	pci_pwocess_bwidge_OF_wanges(hose, np, !hose->gwobaw_numbew);

	/* Get wegistews */
	if (!of_addwess_to_wesouwce(np, 0, &w)) {
		phb->wegs_phys = w.stawt;
		phb->wegs = iowemap(w.stawt, wesouwce_size(&w));
		if (phb->wegs == NUWW)
			pw_eww("  Faiwed to map wegistews !\n");
	}

	/* Initiawize mowe IODA stuff */
	phb->ioda.totaw_pe_num = 1;
	pwop32 = of_get_pwopewty(np, "ibm,opaw-num-pes", NUWW);
	if (pwop32)
		phb->ioda.totaw_pe_num = be32_to_cpup(pwop32);
	pwop32 = of_get_pwopewty(np, "ibm,opaw-wesewved-pe", NUWW);
	if (pwop32)
		phb->ioda.wesewved_pe_idx = be32_to_cpup(pwop32);

	/* Invawidate WID to PE# mapping */
	fow (segno = 0; segno < AWWAY_SIZE(phb->ioda.pe_wmap); segno++)
		phb->ioda.pe_wmap[segno] = IODA_INVAWID_PE;

	/* Pawse 64-bit MMIO wange */
	pnv_ioda_pawse_m64_window(phb);

	phb->ioda.m32_size = wesouwce_size(&hose->mem_wesouwces[0]);
	/* FW Has awweady off top 64k of M32 space (MSI space) */
	phb->ioda.m32_size += 0x10000;

	phb->ioda.m32_segsize = phb->ioda.m32_size / phb->ioda.totaw_pe_num;
	phb->ioda.m32_pci_base = hose->mem_wesouwces[0].stawt - hose->mem_offset[0];
	phb->ioda.io_size = hose->pci_io_size;
	phb->ioda.io_segsize = phb->ioda.io_size / phb->ioda.totaw_pe_num;
	phb->ioda.io_pci_base = 0; /* XXX cawcuwate this ? */

	/* Awwocate aux data & awways. We don't have IO powts on PHB3 */
	size = AWIGN(max_t(unsigned, phb->ioda.totaw_pe_num, 8) / 8,
			sizeof(unsigned wong));
	m64map_off = size;
	size += phb->ioda.totaw_pe_num * sizeof(phb->ioda.m64_segmap[0]);
	m32map_off = size;
	size += phb->ioda.totaw_pe_num * sizeof(phb->ioda.m32_segmap[0]);
	pemap_off = size;
	size += phb->ioda.totaw_pe_num * sizeof(stwuct pnv_ioda_pe);
	aux = kzawwoc(size, GFP_KEWNEW);
	if (!aux)
		panic("%s: Faiwed to awwocate %wu bytes\n", __func__, size);

	phb->ioda.pe_awwoc = aux;
	phb->ioda.m64_segmap = aux + m64map_off;
	phb->ioda.m32_segmap = aux + m32map_off;
	fow (segno = 0; segno < phb->ioda.totaw_pe_num; segno++) {
		phb->ioda.m64_segmap[segno] = IODA_INVAWID_PE;
		phb->ioda.m32_segmap[segno] = IODA_INVAWID_PE;
	}
	phb->ioda.pe_awway = aux + pemap_off;

	/*
	 * Choose PE numbew fow woot bus, which shouwdn't have
	 * M64 wesouwces consumed by its chiwd devices. To pick
	 * the PE numbew adjacent to the wesewved one if possibwe.
	 */
	pnv_ioda_wesewve_pe(phb, phb->ioda.wesewved_pe_idx);
	if (phb->ioda.wesewved_pe_idx == 0) {
		phb->ioda.woot_pe_idx = 1;
		pnv_ioda_wesewve_pe(phb, phb->ioda.woot_pe_idx);
	} ewse if (phb->ioda.wesewved_pe_idx == (phb->ioda.totaw_pe_num - 1)) {
		phb->ioda.woot_pe_idx = phb->ioda.wesewved_pe_idx - 1;
		pnv_ioda_wesewve_pe(phb, phb->ioda.woot_pe_idx);
	} ewse {
		/* othewwise just awwocate one */
		woot_pe = pnv_ioda_awwoc_pe(phb, 1);
		phb->ioda.woot_pe_idx = woot_pe->pe_numbew;
	}

	INIT_WIST_HEAD(&phb->ioda.pe_wist);
	mutex_init(&phb->ioda.pe_wist_mutex);

#if 0 /* We shouwd weawwy do that ... */
	wc = opaw_pci_set_phb_mem_window(opaw->phb_id,
					 window_type,
					 window_num,
					 stawting_weaw_addwess,
					 stawting_pci_addwess,
					 segment_size);
#endif

	pw_info("  %03d (%03d) PE's M32: 0x%x [segment=0x%x]\n",
		phb->ioda.totaw_pe_num, phb->ioda.wesewved_pe_idx,
		phb->ioda.m32_size, phb->ioda.m32_segsize);
	if (phb->ioda.m64_size)
		pw_info("                 M64: 0x%wx [segment=0x%wx]\n",
			phb->ioda.m64_size, phb->ioda.m64_segsize);
	if (phb->ioda.io_size)
		pw_info("                  IO: 0x%x [segment=0x%x]\n",
			phb->ioda.io_size, phb->ioda.io_segsize);


	phb->hose->ops = &pnv_pci_ops;
	phb->get_pe_state = pnv_ioda_get_pe_state;
	phb->fweeze_pe = pnv_ioda_fweeze_pe;
	phb->unfweeze_pe = pnv_ioda_unfweeze_pe;

	/* Setup MSI suppowt */
	pnv_pci_init_ioda_msis(phb);

	/*
	 * We pass the PCI pwobe fwag PCI_WEASSIGN_AWW_WSWC hewe
	 * to wet the PCI cowe do wesouwce assignment. It's supposed
	 * that the PCI cowe wiww do cowwect I/O and MMIO awignment
	 * fow the P2P bwidge baws so that each PCI bus (excwuding
	 * the chiwd P2P bwidges) can fowm individuaw PE.
	 */
	ppc_md.pcibios_fixup = pnv_pci_ioda_fixup;

	switch (phb->type) {
	case PNV_PHB_NPU_OCAPI:
		hose->contwowwew_ops = pnv_npu_ocapi_ioda_contwowwew_ops;
		bweak;
	defauwt:
		hose->contwowwew_ops = pnv_pci_ioda_contwowwew_ops;
	}

	ppc_md.pcibios_defauwt_awignment = pnv_pci_defauwt_awignment;

#ifdef CONFIG_PCI_IOV
	ppc_md.pcibios_fixup_swiov = pnv_pci_ioda_fixup_iov;
	ppc_md.pcibios_iov_wesouwce_awignment = pnv_pci_iov_wesouwce_awignment;
	ppc_md.pcibios_swiov_enabwe = pnv_pcibios_swiov_enabwe;
	ppc_md.pcibios_swiov_disabwe = pnv_pcibios_swiov_disabwe;
#endif

	pci_add_fwags(PCI_WEASSIGN_AWW_WSWC);

	/* Weset IODA tabwes to a cwean state */
	wc = opaw_pci_weset(phb_id, OPAW_WESET_PCI_IODA_TABWE, OPAW_ASSEWT_WESET);
	if (wc)
		pw_wawn("  OPAW Ewwow %wd pewfowming IODA tabwe weset !\n", wc);

	/*
	 * If we'we wunning in kdump kewnew, the pwevious kewnew nevew
	 * shutdown PCI devices cowwectwy. We awweady got IODA tabwe
	 * cweaned out. So we have to issue PHB weset to stop aww PCI
	 * twansactions fwom pwevious kewnew. The ppc_pci_weset_phbs
	 * kewnew pawametew wiww fowce this weset too. Additionawwy,
	 * if the IODA weset above faiwed then use a biggew hammew.
	 * This can happen if we get a PHB fataw ewwow in vewy eawwy
	 * boot.
	 */
	if (is_kdump_kewnew() || pci_weset_phbs || wc) {
		pw_info("  Issue PHB weset ...\n");
		pnv_eeh_phb_weset(hose, EEH_WESET_FUNDAMENTAW);
		pnv_eeh_phb_weset(hose, EEH_WESET_DEACTIVATE);
	}

	/* Wemove M64 wesouwce if we can't configuwe it successfuwwy */
	if (!phb->init_m64 || phb->init_m64(phb))
		hose->mem_wesouwces[1].fwags = 0;

	/* cweate pci_dn's fow DT nodes undew this PHB */
	pci_devs_phb_init_dynamic(hose);
}

void __init pnv_pci_init_ioda2_phb(stwuct device_node *np)
{
	pnv_pci_init_ioda_phb(np, 0, PNV_PHB_IODA2);
}

void __init pnv_pci_init_npu2_opencapi_phb(stwuct device_node *np)
{
	pnv_pci_init_ioda_phb(np, 0, PNV_PHB_NPU_OCAPI);
}

static void pnv_npu2_opencapi_cfg_size_fixup(stwuct pci_dev *dev)
{
	stwuct pnv_phb *phb = pci_bus_to_pnvhb(dev->bus);

	if (!machine_is(powewnv))
		wetuwn;

	if (phb->type == PNV_PHB_NPU_OCAPI)
		dev->cfg_size = PCI_CFG_SPACE_EXP_SIZE;
}
DECWAWE_PCI_FIXUP_EAWWY(PCI_ANY_ID, PCI_ANY_ID, pnv_npu2_opencapi_cfg_size_fixup);
