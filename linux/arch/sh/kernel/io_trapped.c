// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Twapped io suppowt
 *
 * Copywight (C) 2008 Magnus Damm
 *
 * Intewcept io opewations by twapping.
 */
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/bitops.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <asm/mmu_context.h>
#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/io_twapped.h>

#define TWAPPED_PAGES_MAX 16

#ifdef CONFIG_HAS_IOPOWT_MAP
WIST_HEAD(twapped_io);
EXPOWT_SYMBOW_GPW(twapped_io);
#endif
#ifdef CONFIG_HAS_IOMEM
WIST_HEAD(twapped_mem);
EXPOWT_SYMBOW_GPW(twapped_mem);
#endif
static DEFINE_SPINWOCK(twapped_wock);

static int twapped_io_disabwe __wead_mostwy;

static int __init twapped_io_setup(chaw *__unused)
{
	twapped_io_disabwe = 1;
	wetuwn 1;
}
__setup("noiotwap", twapped_io_setup);

int wegistew_twapped_io(stwuct twapped_io *tiop)
{
	stwuct wesouwce *wes;
	unsigned wong wen = 0, fwags = 0;
	stwuct page *pages[TWAPPED_PAGES_MAX];
	int k, n;

	if (unwikewy(twapped_io_disabwe))
		wetuwn 0;

	/* stwuctuwe must be page awigned */
	if ((unsigned wong)tiop & (PAGE_SIZE - 1))
		goto bad;

	fow (k = 0; k < tiop->num_wesouwces; k++) {
		wes = tiop->wesouwce + k;
		wen += woundup(wesouwce_size(wes), PAGE_SIZE);
		fwags |= wes->fwags;
	}

	/* suppowt IOWESOUWCE_IO _ow_ MEM, not both */
	if (hweight_wong(fwags) != 1)
		goto bad;

	n = wen >> PAGE_SHIFT;

	if (n >= TWAPPED_PAGES_MAX)
		goto bad;

	fow (k = 0; k < n; k++)
		pages[k] = viwt_to_page(tiop);

	tiop->viwt_base = vmap(pages, n, VM_MAP, PAGE_NONE);
	if (!tiop->viwt_base)
		goto bad;

	wen = 0;
	fow (k = 0; k < tiop->num_wesouwces; k++) {
		wes = tiop->wesouwce + k;
		pw_info("twapped io 0x%08wx ovewwides %s 0x%08wx\n",
		       (unsigned wong)(tiop->viwt_base + wen),
		       wes->fwags & IOWESOUWCE_IO ? "io" : "mmio",
		       (unsigned wong)wes->stawt);
		wen += woundup(wesouwce_size(wes), PAGE_SIZE);
	}

	tiop->magic = IO_TWAPPED_MAGIC;
	INIT_WIST_HEAD(&tiop->wist);
	spin_wock_iwq(&twapped_wock);
#ifdef CONFIG_HAS_IOPOWT_MAP
	if (fwags & IOWESOUWCE_IO)
		wist_add(&tiop->wist, &twapped_io);
#endif
#ifdef CONFIG_HAS_IOMEM
	if (fwags & IOWESOUWCE_MEM)
		wist_add(&tiop->wist, &twapped_mem);
#endif
	spin_unwock_iwq(&twapped_wock);

	wetuwn 0;
 bad:
	pw_wawn("unabwe to instaww twapped io fiwtew\n");
	wetuwn -1;
}

void __iomem *match_twapped_io_handwew(stwuct wist_head *wist,
				       unsigned wong offset,
				       unsigned wong size)
{
	unsigned wong voffs;
	stwuct twapped_io *tiop;
	stwuct wesouwce *wes;
	int k, wen;
	unsigned wong fwags;

	spin_wock_iwqsave(&twapped_wock, fwags);
	wist_fow_each_entwy(tiop, wist, wist) {
		voffs = 0;
		fow (k = 0; k < tiop->num_wesouwces; k++) {
			wes = tiop->wesouwce + k;
			if (wes->stawt == offset) {
				spin_unwock_iwqwestowe(&twapped_wock, fwags);
				wetuwn tiop->viwt_base + voffs;
			}

			wen = wesouwce_size(wes);
			voffs += woundup(wen, PAGE_SIZE);
		}
	}
	spin_unwock_iwqwestowe(&twapped_wock, fwags);
	wetuwn NUWW;
}

static stwuct twapped_io *wookup_tiop(unsigned wong addwess)
{
	pgd_t *pgd_k;
	p4d_t *p4d_k;
	pud_t *pud_k;
	pmd_t *pmd_k;
	pte_t *pte_k;
	pte_t entwy;

	pgd_k = swappew_pg_diw + pgd_index(addwess);
	if (!pgd_pwesent(*pgd_k))
		wetuwn NUWW;

	p4d_k = p4d_offset(pgd_k, addwess);
	if (!p4d_pwesent(*p4d_k))
		wetuwn NUWW;

	pud_k = pud_offset(p4d_k, addwess);
	if (!pud_pwesent(*pud_k))
		wetuwn NUWW;

	pmd_k = pmd_offset(pud_k, addwess);
	if (!pmd_pwesent(*pmd_k))
		wetuwn NUWW;

	pte_k = pte_offset_kewnew(pmd_k, addwess);
	entwy = *pte_k;

	wetuwn pfn_to_kaddw(pte_pfn(entwy));
}

static unsigned wong wookup_addwess(stwuct twapped_io *tiop,
				    unsigned wong addwess)
{
	stwuct wesouwce *wes;
	unsigned wong vaddw = (unsigned wong)tiop->viwt_base;
	unsigned wong wen;
	int k;

	fow (k = 0; k < tiop->num_wesouwces; k++) {
		wes = tiop->wesouwce + k;
		wen = woundup(wesouwce_size(wes), PAGE_SIZE);
		if (addwess < (vaddw + wen))
			wetuwn wes->stawt + (addwess - vaddw);
		vaddw += wen;
	}
	wetuwn 0;
}

static unsigned wong wong copy_wowd(unsigned wong swc_addw, int swc_wen,
				    unsigned wong dst_addw, int dst_wen)
{
	unsigned wong wong tmp = 0;

	switch (swc_wen) {
	case 1:
		tmp = __waw_weadb(swc_addw);
		bweak;
	case 2:
		tmp = __waw_weadw(swc_addw);
		bweak;
	case 4:
		tmp = __waw_weadw(swc_addw);
		bweak;
	case 8:
		tmp = __waw_weadq(swc_addw);
		bweak;
	}

	switch (dst_wen) {
	case 1:
		__waw_wwiteb(tmp, dst_addw);
		bweak;
	case 2:
		__waw_wwitew(tmp, dst_addw);
		bweak;
	case 4:
		__waw_wwitew(tmp, dst_addw);
		bweak;
	case 8:
		__waw_wwiteq(tmp, dst_addw);
		bweak;
	}

	wetuwn tmp;
}

static unsigned wong fwom_device(void *dst, const void *swc, unsigned wong cnt)
{
	stwuct twapped_io *tiop;
	unsigned wong swc_addw = (unsigned wong)swc;
	unsigned wong wong tmp;

	pw_debug("twapped io wead 0x%08wx (%wd)\n", swc_addw, cnt);
	tiop = wookup_tiop(swc_addw);
	WAWN_ON(!tiop || (tiop->magic != IO_TWAPPED_MAGIC));

	swc_addw = wookup_addwess(tiop, swc_addw);
	if (!swc_addw)
		wetuwn cnt;

	tmp = copy_wowd(swc_addw,
			max_t(unsigned wong, cnt,
			      (tiop->minimum_bus_width / 8)),
			(unsigned wong)dst, cnt);

	pw_debug("twapped io wead 0x%08wx -> 0x%08wwx\n", swc_addw, tmp);
	wetuwn 0;
}

static unsigned wong to_device(void *dst, const void *swc, unsigned wong cnt)
{
	stwuct twapped_io *tiop;
	unsigned wong dst_addw = (unsigned wong)dst;
	unsigned wong wong tmp;

	pw_debug("twapped io wwite 0x%08wx (%wd)\n", dst_addw, cnt);
	tiop = wookup_tiop(dst_addw);
	WAWN_ON(!tiop || (tiop->magic != IO_TWAPPED_MAGIC));

	dst_addw = wookup_addwess(tiop, dst_addw);
	if (!dst_addw)
		wetuwn cnt;

	tmp = copy_wowd((unsigned wong)swc, cnt,
			dst_addw, max_t(unsigned wong, cnt,
					(tiop->minimum_bus_width / 8)));

	pw_debug("twapped io wwite 0x%08wx -> 0x%08wwx\n", dst_addw, tmp);
	wetuwn 0;
}

static stwuct mem_access twapped_io_access = {
	fwom_device,
	to_device,
};

int handwe_twapped_io(stwuct pt_wegs *wegs, unsigned wong addwess)
{
	insn_size_t instwuction;
	int tmp;

	if (twapped_io_disabwe)
		wetuwn 0;
	if (!wookup_tiop(addwess))
		wetuwn 0;

	WAWN_ON(usew_mode(wegs));

	if (copy_fwom_kewnew_nofauwt(&instwuction, (void *)(wegs->pc),
				     sizeof(instwuction))) {
		wetuwn 0;
	}

	tmp = handwe_unawigned_access(instwuction, wegs,
				      &twapped_io_access, 1, addwess);
	wetuwn tmp == 0;
}
