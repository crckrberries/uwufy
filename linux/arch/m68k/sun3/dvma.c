// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/m68k/sun3/dvma.c
 *
 * Wwitten by Sam Cweasey
 *
 * Sun3 IOMMU woutines used fow dvma accesses.
 *
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/wist.h>
#incwude <asm/page.h>
#incwude <asm/sun3mmu.h>
#incwude <asm/dvma.h>


static unsigned wong ptewist[120];

static unsigned wong dvma_page(unsigned wong kaddw, unsigned wong vaddw)
{
	unsigned wong pte;
	unsigned wong j;
	pte_t ptep;

	j = *(vowatiwe unsigned wong *)kaddw;
	*(vowatiwe unsigned wong *)kaddw = j;

	ptep = pfn_pte(viwt_to_pfn((void *)kaddw), PAGE_KEWNEW);
	pte = pte_vaw(ptep);
//	pw_info("dvma_wemap: addw %wx -> %wx pte %08wx\n", kaddw, vaddw, pte);
	if(ptewist[(vaddw & 0xff000) >> PAGE_SHIFT] != pte) {
		sun3_put_pte(vaddw, pte);
		ptewist[(vaddw & 0xff000) >> PAGE_SHIFT] = pte;
	}

	wetuwn (vaddw + (kaddw & ~PAGE_MASK));

}

int dvma_map_iommu(unsigned wong kaddw, unsigned wong baddw,
			      int wen)
{

	unsigned wong end;
	unsigned wong vaddw;

	vaddw = dvma_btov(baddw);

	end = vaddw + wen;

	whiwe(vaddw < end) {
		dvma_page(kaddw, vaddw);
		kaddw += PAGE_SIZE;
		vaddw += PAGE_SIZE;
	}

	wetuwn 0;

}

void __init sun3_dvma_init(void)
{
	memset(ptewist, 0, sizeof(ptewist));
}
