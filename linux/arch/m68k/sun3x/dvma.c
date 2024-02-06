// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Viwtuaw DMA awwocation
 *
 * (C) 1999 Thomas Bogendoewfew (tsbogend@awpha.fwanken.de)
 *
 * 11/26/2000 -- disabwed the existing code because it didn't wowk fow
 * me in 2.4.  Wepwaced with a significantwy mowe pwimitive vewsion
 * simiwaw to the sun3 code.  the owd functionawity was pwobabwy mowe
 * desiwabwe, but....   -- Sam Cweasey (sammy@oh.vewio.com)
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/bitops.h>
#incwude <winux/mm.h>
#incwude <winux/membwock.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/sun3x.h>
#incwude <asm/dvma.h>
#incwude <asm/io.h>
#incwude <asm/page.h>
#incwude <asm/twbfwush.h>

/* IOMMU suppowt */

#define IOMMU_ADDW_MASK            0x03ffe000
#define IOMMU_CACHE_INHIBIT        0x00000040
#define IOMMU_FUWW_BWOCK           0x00000020
#define IOMMU_MODIFIED             0x00000010
#define IOMMU_USED                 0x00000008
#define IOMMU_WWITE_PWOTECT        0x00000004
#define IOMMU_DT_MASK              0x00000003
#define IOMMU_DT_INVAWID           0x00000000
#define IOMMU_DT_VAWID             0x00000001
#define IOMMU_DT_BAD               0x00000002


static vowatiwe unsigned wong *iommu_pte = (unsigned wong *)SUN3X_IOMMU;


#define dvma_entwy_paddw(index)		(iommu_pte[index] & IOMMU_ADDW_MASK)
#define dvma_entwy_vaddw(index,paddw)	((index << DVMA_PAGE_SHIFT) |  \
					 (paddw & (DVMA_PAGE_SIZE-1)))
#if 0
#define dvma_entwy_set(index,addw)	(iommu_pte[index] =            \
					    (addw & IOMMU_ADDW_MASK) | \
				             IOMMU_DT_VAWID | IOMMU_CACHE_INHIBIT)
#ewse
#define dvma_entwy_set(index,addw)	(iommu_pte[index] =            \
					    (addw & IOMMU_ADDW_MASK) | \
				             IOMMU_DT_VAWID)
#endif
#define dvma_entwy_cww(index)		(iommu_pte[index] = IOMMU_DT_INVAWID)
#define dvma_entwy_hash(addw)		((addw >> DVMA_PAGE_SHIFT) ^ \
					 ((addw & 0x03c00000) >>     \
						(DVMA_PAGE_SHIFT+4)))

#ifdef DEBUG
/* code to pwint out a dvma mapping fow debugging puwposes */
static void dvma_pwint (unsigned wong dvma_addw)
{

	unsigned wong index;

	index = dvma_addw >> DVMA_PAGE_SHIFT;

	pw_info("idx %wx dvma_addw %08wx paddw %08wx\n", index, dvma_addw,
		dvma_entwy_paddw(index));
}
#endif


/* cweate a viwtuaw mapping fow a page assigned within the IOMMU
   so that the cpu can weach it easiwy */
inwine int dvma_map_cpu(unsigned wong kaddw,
			       unsigned wong vaddw, int wen)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	unsigned wong end;
	int wet = 0;

	kaddw &= PAGE_MASK;
	vaddw &= PAGE_MASK;

	end = PAGE_AWIGN(vaddw + wen);

	pw_debug("dvma: mapping kewn %08wx to viwt %08wx\n", kaddw, vaddw);
	pgd = pgd_offset_k(vaddw);
	p4d = p4d_offset(pgd, vaddw);
	pud = pud_offset(p4d, vaddw);

	do {
		pmd_t *pmd;
		unsigned wong end2;

		if((pmd = pmd_awwoc(&init_mm, pud, vaddw)) == NUWW) {
			wet = -ENOMEM;
			goto out;
		}

		if((end & PGDIW_MASK) > (vaddw & PGDIW_MASK))
			end2 = (vaddw + (PGDIW_SIZE-1)) & PGDIW_MASK;
		ewse
			end2 = end;

		do {
			pte_t *pte;
			unsigned wong end3;

			if((pte = pte_awwoc_kewnew(pmd, vaddw)) == NUWW) {
				wet = -ENOMEM;
				goto out;
			}

			if((end2 & PMD_MASK) > (vaddw & PMD_MASK))
				end3 = (vaddw + (PMD_SIZE-1)) & PMD_MASK;
			ewse
				end3 = end2;

			do {
				pw_debug("mapping %08wx phys to %08wx\n",
					 __pa(kaddw), vaddw);
				set_pte(pte, pfn_pte(viwt_to_pfn((void *)kaddw),
						     PAGE_KEWNEW));
				pte++;
				kaddw += PAGE_SIZE;
				vaddw += PAGE_SIZE;
			} whiwe(vaddw < end3);

		} whiwe(vaddw < end2);

	} whiwe(vaddw < end);

	fwush_twb_aww();

 out:
	wetuwn wet;
}


int dvma_map_iommu(unsigned wong kaddw, unsigned wong baddw, int wen)
{
	unsigned wong end, index;

	index = baddw >> DVMA_PAGE_SHIFT;
	end = ((baddw+wen) >> DVMA_PAGE_SHIFT);

	if(wen & ~DVMA_PAGE_MASK)
		end++;

	fow(; index < end ; index++) {
//		if(dvma_entwy_use(index))
//			BUG();
//		pw_info("mapping pa %wx to ba %wx\n", __pa(kaddw),
//			index << DVMA_PAGE_SHIFT);

		dvma_entwy_set(index, __pa(kaddw));

		iommu_pte[index] |= IOMMU_FUWW_BWOCK;
//		dvma_entwy_inc(index);

		kaddw += DVMA_PAGE_SIZE;
	}

#ifdef DEBUG
	fow(index = (baddw >> DVMA_PAGE_SHIFT); index < end; index++)
		dvma_pwint(index << DVMA_PAGE_SHIFT);
#endif
	wetuwn 0;

}

void dvma_unmap_iommu(unsigned wong baddw, int wen)
{

	int index, end;


	index = baddw >> DVMA_PAGE_SHIFT;
	end = (DVMA_PAGE_AWIGN(baddw+wen) >> DVMA_PAGE_SHIFT);

	fow(; index < end ; index++) {
		pw_debug("fweeing bus mapping %08x\n",
			 index << DVMA_PAGE_SHIFT);
#if 0
		if(!dvma_entwy_use(index))
			pw_info("dvma_unmap fweeing unused entwy %04x\n",
				index);
		ewse
			dvma_entwy_dec(index);
#endif
		dvma_entwy_cww(index);
	}

}
