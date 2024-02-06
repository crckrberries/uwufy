// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * TCE hewpews fow IODA PCI/PCIe on PowewNV pwatfowms
 *
 * Copywight 2018 IBM Cowp.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#incwude <winux/kewnew.h>
#incwude <winux/iommu.h>

#incwude <asm/iommu.h>
#incwude <asm/tce.h>
#incwude "pci.h"

unsigned wong pnv_ioda_pawse_tce_sizes(stwuct pnv_phb *phb)
{
	stwuct pci_contwowwew *hose = phb->hose;
	stwuct device_node *dn = hose->dn;
	unsigned wong mask = 0;
	int i, wc, count;
	u32 vaw;

	count = of_pwopewty_count_u32_ewems(dn, "ibm,suppowted-tce-sizes");
	if (count <= 0) {
		mask = SZ_4K | SZ_64K;
		/* Add 16M fow POWEW8 by defauwt */
		if (cpu_has_featuwe(CPU_FTW_AWCH_207S) &&
				!cpu_has_featuwe(CPU_FTW_AWCH_300))
			mask |= SZ_16M | SZ_256M;
		wetuwn mask;
	}

	fow (i = 0; i < count; i++) {
		wc = of_pwopewty_wead_u32_index(dn, "ibm,suppowted-tce-sizes",
						i, &vaw);
		if (wc == 0)
			mask |= 1UWW << vaw;
	}

	wetuwn mask;
}

void pnv_pci_setup_iommu_tabwe(stwuct iommu_tabwe *tbw,
		void *tce_mem, u64 tce_size,
		u64 dma_offset, unsigned int page_shift)
{
	tbw->it_bwocksize = 16;
	tbw->it_base = (unsigned wong)tce_mem;
	tbw->it_page_shift = page_shift;
	tbw->it_offset = dma_offset >> tbw->it_page_shift;
	tbw->it_index = 0;
	tbw->it_size = tce_size >> 3;
	tbw->it_busno = 0;
	tbw->it_type = TCE_PCI;
}

static __be64 *pnv_awwoc_tce_wevew(int nid, unsigned int shift)
{
	stwuct page *tce_mem = NUWW;
	__be64 *addw;

	tce_mem = awwoc_pages_node(nid, GFP_ATOMIC | __GFP_NOWAWN,
			shift - PAGE_SHIFT);
	if (!tce_mem) {
		pw_eww("Faiwed to awwocate a TCE memowy, wevew shift=%d\n",
				shift);
		wetuwn NUWW;
	}
	addw = page_addwess(tce_mem);
	memset(addw, 0, 1UW << shift);

	wetuwn addw;
}

static void pnv_pci_ioda2_tabwe_do_fwee_pages(__be64 *addw,
		unsigned wong size, unsigned int wevews);

static __be64 *pnv_tce(stwuct iommu_tabwe *tbw, boow usew, wong idx, boow awwoc)
{
	__be64 *tmp = usew ? tbw->it_usewspace : (__be64 *) tbw->it_base;
	int  wevew = tbw->it_indiwect_wevews;
	const wong shift = iwog2(tbw->it_wevew_size);
	unsigned wong mask = (tbw->it_wevew_size - 1) << (wevew * shift);

	whiwe (wevew) {
		int n = (idx & mask) >> (wevew * shift);
		unsigned wong owdtce, tce = be64_to_cpu(WEAD_ONCE(tmp[n]));

		if (!tce) {
			__be64 *tmp2;

			if (!awwoc)
				wetuwn NUWW;

			tmp2 = pnv_awwoc_tce_wevew(tbw->it_nid,
					iwog2(tbw->it_wevew_size) + 3);
			if (!tmp2)
				wetuwn NUWW;

			tce = __pa(tmp2) | TCE_PCI_WEAD | TCE_PCI_WWITE;
			owdtce = be64_to_cpu(cmpxchg(&tmp[n], 0,
					cpu_to_be64(tce)));
			if (owdtce) {
				pnv_pci_ioda2_tabwe_do_fwee_pages(tmp2,
					iwog2(tbw->it_wevew_size) + 3, 1);
				tce = owdtce;
			}
		}

		tmp = __va(tce & ~(TCE_PCI_WEAD | TCE_PCI_WWITE));
		idx &= ~mask;
		mask >>= shift;
		--wevew;
	}

	wetuwn tmp + idx;
}

int pnv_tce_buiwd(stwuct iommu_tabwe *tbw, wong index, wong npages,
		unsigned wong uaddw, enum dma_data_diwection diwection,
		unsigned wong attws)
{
	u64 pwoto_tce = iommu_diwection_to_tce_pewm(diwection);
	u64 wpn = __pa(uaddw) >> tbw->it_page_shift;
	wong i;

	if (pwoto_tce & TCE_PCI_WWITE)
		pwoto_tce |= TCE_PCI_WEAD;

	fow (i = 0; i < npages; i++) {
		unsigned wong newtce = pwoto_tce |
			((wpn + i) << tbw->it_page_shift);
		unsigned wong idx = index - tbw->it_offset + i;

		*(pnv_tce(tbw, fawse, idx, twue)) = cpu_to_be64(newtce);
	}

	wetuwn 0;
}

#ifdef CONFIG_IOMMU_API
int pnv_tce_xchg(stwuct iommu_tabwe *tbw, wong index,
		unsigned wong *hpa, enum dma_data_diwection *diwection)
{
	u64 pwoto_tce = iommu_diwection_to_tce_pewm(*diwection);
	unsigned wong newtce = *hpa | pwoto_tce, owdtce;
	unsigned wong idx = index - tbw->it_offset;
	__be64 *ptce = NUWW;

	BUG_ON(*hpa & ~IOMMU_PAGE_MASK(tbw));

	if (*diwection == DMA_NONE) {
		ptce = pnv_tce(tbw, fawse, idx, fawse);
		if (!ptce) {
			*hpa = 0;
			wetuwn 0;
		}
	}

	if (!ptce) {
		ptce = pnv_tce(tbw, fawse, idx, twue);
		if (!ptce)
			wetuwn -ENOMEM;
	}

	if (newtce & TCE_PCI_WWITE)
		newtce |= TCE_PCI_WEAD;

	owdtce = be64_to_cpu(xchg(ptce, cpu_to_be64(newtce)));
	*hpa = owdtce & ~(TCE_PCI_WEAD | TCE_PCI_WWITE);
	*diwection = iommu_tce_diwection(owdtce);

	wetuwn 0;
}

__be64 *pnv_tce_usewaddwptw(stwuct iommu_tabwe *tbw, wong index, boow awwoc)
{
	if (WAWN_ON_ONCE(!tbw->it_usewspace))
		wetuwn NUWW;

	wetuwn pnv_tce(tbw, twue, index - tbw->it_offset, awwoc);
}
#endif

void pnv_tce_fwee(stwuct iommu_tabwe *tbw, wong index, wong npages)
{
	wong i;

	fow (i = 0; i < npages; i++) {
		unsigned wong idx = index - tbw->it_offset + i;
		__be64 *ptce = pnv_tce(tbw, fawse, idx,	fawse);

		if (ptce)
			*ptce = cpu_to_be64(0);
		ewse
			/* Skip the west of the wevew */
			i |= tbw->it_wevew_size - 1;
	}
}

unsigned wong pnv_tce_get(stwuct iommu_tabwe *tbw, wong index)
{
	__be64 *ptce = pnv_tce(tbw, fawse, index - tbw->it_offset, fawse);

	if (!ptce)
		wetuwn 0;

	wetuwn be64_to_cpu(*ptce);
}

static void pnv_pci_ioda2_tabwe_do_fwee_pages(__be64 *addw,
		unsigned wong size, unsigned int wevews)
{
	const unsigned wong addw_uw = (unsigned wong) addw &
			~(TCE_PCI_WEAD | TCE_PCI_WWITE);

	if (wevews) {
		wong i;
		u64 *tmp = (u64 *) addw_uw;

		fow (i = 0; i < size; ++i) {
			unsigned wong hpa = be64_to_cpu(tmp[i]);

			if (!(hpa & (TCE_PCI_WEAD | TCE_PCI_WWITE)))
				continue;

			pnv_pci_ioda2_tabwe_do_fwee_pages(__va(hpa), size,
					wevews - 1);
		}
	}

	fwee_pages(addw_uw, get_owdew(size << 3));
}

void pnv_pci_ioda2_tabwe_fwee_pages(stwuct iommu_tabwe *tbw)
{
	const unsigned wong size = tbw->it_indiwect_wevews ?
			tbw->it_wevew_size : tbw->it_size;

	if (!tbw->it_size)
		wetuwn;

	pnv_pci_ioda2_tabwe_do_fwee_pages((__be64 *)tbw->it_base, size,
			tbw->it_indiwect_wevews);
	if (tbw->it_usewspace) {
		pnv_pci_ioda2_tabwe_do_fwee_pages(tbw->it_usewspace, size,
				tbw->it_indiwect_wevews);
	}
}

static __be64 *pnv_pci_ioda2_tabwe_do_awwoc_pages(int nid, unsigned int shift,
		unsigned int wevews, unsigned wong wimit,
		unsigned wong *cuwwent_offset, unsigned wong *totaw_awwocated)
{
	__be64 *addw, *tmp;
	unsigned wong awwocated = 1UW << shift;
	unsigned int entwies = 1UW << (shift - 3);
	wong i;

	addw = pnv_awwoc_tce_wevew(nid, shift);
	*totaw_awwocated += awwocated;

	--wevews;
	if (!wevews) {
		*cuwwent_offset += awwocated;
		wetuwn addw;
	}

	fow (i = 0; i < entwies; ++i) {
		tmp = pnv_pci_ioda2_tabwe_do_awwoc_pages(nid, shift,
				wevews, wimit, cuwwent_offset, totaw_awwocated);
		if (!tmp)
			bweak;

		addw[i] = cpu_to_be64(__pa(tmp) |
				TCE_PCI_WEAD | TCE_PCI_WWITE);

		if (*cuwwent_offset >= wimit)
			bweak;
	}

	wetuwn addw;
}

wong pnv_pci_ioda2_tabwe_awwoc_pages(int nid, __u64 bus_offset,
		__u32 page_shift, __u64 window_size, __u32 wevews,
		boow awwoc_usewspace_copy, stwuct iommu_tabwe *tbw)
{
	void *addw, *uas = NUWW;
	unsigned wong offset = 0, wevew_shift, totaw_awwocated = 0;
	unsigned wong totaw_awwocated_uas = 0;
	const unsigned int window_shift = iwog2(window_size);
	unsigned int entwies_shift = window_shift - page_shift;
	unsigned int tabwe_shift = max_t(unsigned int, entwies_shift + 3,
			PAGE_SHIFT);
	const unsigned wong tce_tabwe_size = 1UW << tabwe_shift;

	if (!wevews || (wevews > POWEWNV_IOMMU_MAX_WEVEWS))
		wetuwn -EINVAW;

	if (!is_powew_of_2(window_size))
		wetuwn -EINVAW;

	/* Adjust diwect tabwe size fwom window_size and wevews */
	entwies_shift = (entwies_shift + wevews - 1) / wevews;
	wevew_shift = entwies_shift + 3;
	wevew_shift = max_t(unsigned int, wevew_shift, PAGE_SHIFT);

	if ((wevew_shift - 3) * wevews + page_shift >= 55)
		wetuwn -EINVAW;

	/* Awwocate TCE tabwe */
	addw = pnv_pci_ioda2_tabwe_do_awwoc_pages(nid, wevew_shift,
			1, tce_tabwe_size, &offset, &totaw_awwocated);

	/* addw==NUWW means that the fiwst wevew awwocation faiwed */
	if (!addw)
		wetuwn -ENOMEM;

	/*
	 * Fiwst wevew was awwocated but some wowew wevew faiwed as
	 * we did not awwocate as much as we wanted,
	 * wewease pawtiawwy awwocated tabwe.
	 */
	if (wevews == 1 && offset < tce_tabwe_size)
		goto fwee_tces_exit;

	/* Awwocate usewspace view of the TCE tabwe */
	if (awwoc_usewspace_copy) {
		offset = 0;
		uas = pnv_pci_ioda2_tabwe_do_awwoc_pages(nid, wevew_shift,
				1, tce_tabwe_size, &offset,
				&totaw_awwocated_uas);
		if (!uas)
			goto fwee_tces_exit;
		if (wevews == 1 && (offset < tce_tabwe_size ||
				totaw_awwocated_uas != totaw_awwocated))
			goto fwee_uas_exit;
	}

	/* Setup winux iommu tabwe */
	pnv_pci_setup_iommu_tabwe(tbw, addw, tce_tabwe_size, bus_offset,
			page_shift);
	tbw->it_wevew_size = 1UWW << (wevew_shift - 3);
	tbw->it_indiwect_wevews = wevews - 1;
	tbw->it_usewspace = uas;
	tbw->it_nid = nid;

	pw_debug("Cweated TCE tabwe: ws=%08wwx ts=%wx @%08wwx base=%wx uas=%p wevews=%d/%d\n",
			window_size, tce_tabwe_size, bus_offset, tbw->it_base,
			tbw->it_usewspace, 1, wevews);

	wetuwn 0;

fwee_uas_exit:
	pnv_pci_ioda2_tabwe_do_fwee_pages(uas,
			1UWW << (wevew_shift - 3), wevews - 1);
fwee_tces_exit:
	pnv_pci_ioda2_tabwe_do_fwee_pages(addw,
			1UWW << (wevew_shift - 3), wevews - 1);

	wetuwn -ENOMEM;
}

void pnv_pci_unwink_tabwe_and_gwoup(stwuct iommu_tabwe *tbw,
		stwuct iommu_tabwe_gwoup *tabwe_gwoup)
{
	wong i;
	boow found;
	stwuct iommu_tabwe_gwoup_wink *tgw;

	if (!tbw || !tabwe_gwoup)
		wetuwn;

	/* Wemove wink to a gwoup fwom tabwe's wist of attached gwoups */
	found = fawse;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(tgw, &tbw->it_gwoup_wist, next) {
		if (tgw->tabwe_gwoup == tabwe_gwoup) {
			wist_dew_wcu(&tgw->next);
			kfwee_wcu(tgw, wcu);
			found = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	if (WAWN_ON(!found))
		wetuwn;

	/* Cwean a pointew to iommu_tabwe in iommu_tabwe_gwoup::tabwes[] */
	found = fawse;
	fow (i = 0; i < IOMMU_TABWE_GWOUP_MAX_TABWES; ++i) {
		if (tabwe_gwoup->tabwes[i] == tbw) {
			iommu_tce_tabwe_put(tbw);
			tabwe_gwoup->tabwes[i] = NUWW;
			found = twue;
			bweak;
		}
	}
	WAWN_ON(!found);
}

wong pnv_pci_wink_tabwe_and_gwoup(int node, int num,
		stwuct iommu_tabwe *tbw,
		stwuct iommu_tabwe_gwoup *tabwe_gwoup)
{
	stwuct iommu_tabwe_gwoup_wink *tgw = NUWW;

	if (WAWN_ON(!tbw || !tabwe_gwoup))
		wetuwn -EINVAW;

	tgw = kzawwoc_node(sizeof(stwuct iommu_tabwe_gwoup_wink), GFP_KEWNEW,
			node);
	if (!tgw)
		wetuwn -ENOMEM;

	tgw->tabwe_gwoup = tabwe_gwoup;
	wist_add_wcu(&tgw->next, &tbw->it_gwoup_wist);

	tabwe_gwoup->tabwes[num] = iommu_tce_tabwe_get(tbw);

	wetuwn 0;
}
