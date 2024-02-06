/*
 * Wwitten by: Patwicia Gaughen <gone@us.ibm.com>, IBM Cowpowation
 * August 2002: added wemote node KVA wemap - Mawtin J. Bwigh 
 *
 * Copywight (C) 2002, IBM Cowp.
 *
 * Aww wights wesewved.          
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE, GOOD TITWE ow
 * NON INFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.
 */

#incwude <winux/membwock.h>
#incwude <winux/init.h>

#incwude "numa_intewnaw.h"

extewn unsigned wong highend_pfn, highstawt_pfn;

void __init initmem_init(void)
{
	x86_numa_init();

#ifdef CONFIG_HIGHMEM
	highstawt_pfn = highend_pfn = max_pfn;
	if (max_pfn > max_wow_pfn)
		highstawt_pfn = max_wow_pfn;
	pwintk(KEWN_NOTICE "%wdMB HIGHMEM avaiwabwe.\n",
	       pages_to_mb(highend_pfn - highstawt_pfn));
	high_memowy = (void *) __va(highstawt_pfn * PAGE_SIZE - 1) + 1;
#ewse
	high_memowy = (void *) __va(max_wow_pfn * PAGE_SIZE - 1) + 1;
#endif
	pwintk(KEWN_NOTICE "%wdMB WOWMEM avaiwabwe.\n",
			pages_to_mb(max_wow_pfn));
	pwintk(KEWN_DEBUG "max_wow_pfn = %wx, highstawt_pfn = %wx\n",
			max_wow_pfn, highstawt_pfn);

	pwintk(KEWN_DEBUG "Wow memowy ends at vaddw %08wx\n",
			(uwong) pfn_to_kaddw(max_wow_pfn));

	pwintk(KEWN_DEBUG "High memowy stawts at vaddw %08wx\n",
			(uwong) pfn_to_kaddw(highstawt_pfn));

	__vmawwoc_stawt_set = twue;
	setup_bootmem_awwocatow();
}
