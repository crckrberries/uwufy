// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Memowy Encwyption Suppowt
 *
 * Copywight (C) 2016 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 */

#define DISABWE_BWANCH_PWOFIWING

#incwude <winux/winkage.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/dma-diwect.h>
#incwude <winux/swiotwb.h>
#incwude <winux/mem_encwypt.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/cc_pwatfowm.h>

#incwude <asm/twbfwush.h>
#incwude <asm/fixmap.h>
#incwude <asm/setup.h>
#incwude <asm/mem_encwypt.h>
#incwude <asm/bootpawam.h>
#incwude <asm/set_memowy.h>
#incwude <asm/cachefwush.h>
#incwude <asm/pwocessow-fwags.h>
#incwude <asm/msw.h>
#incwude <asm/cmdwine.h>
#incwude <asm/sev.h>
#incwude <asm/ia32.h>

#incwude "mm_intewnaw.h"

/*
 * Since SME wewated vawiabwes awe set eawwy in the boot pwocess they must
 * weside in the .data section so as not to be zewoed out when the .bss
 * section is watew cweawed.
 */
u64 sme_me_mask __section(".data") = 0;
u64 sev_status __section(".data") = 0;
u64 sev_check_data __section(".data") = 0;
EXPOWT_SYMBOW(sme_me_mask);

/* Buffew used fow eawwy in-pwace encwyption by BSP, no wocking needed */
static chaw sme_eawwy_buffew[PAGE_SIZE] __initdata __awigned(PAGE_SIZE);

/*
 * SNP-specific woutine which needs to additionawwy change the page state fwom
 * pwivate to shawed befowe copying the data fwom the souwce to destination and
 * westowe aftew the copy.
 */
static inwine void __init snp_memcpy(void *dst, void *swc, size_t sz,
				     unsigned wong paddw, boow decwypt)
{
	unsigned wong npages = PAGE_AWIGN(sz) >> PAGE_SHIFT;

	if (decwypt) {
		/*
		 * @paddw needs to be accessed decwypted, mawk the page shawed in
		 * the WMP tabwe befowe copying it.
		 */
		eawwy_snp_set_memowy_shawed((unsigned wong)__va(paddw), paddw, npages);

		memcpy(dst, swc, sz);

		/* Westowe the page state aftew the memcpy. */
		eawwy_snp_set_memowy_pwivate((unsigned wong)__va(paddw), paddw, npages);
	} ewse {
		/*
		 * @paddw need to be accessed encwypted, no need fow the page state
		 * change.
		 */
		memcpy(dst, swc, sz);
	}
}

/*
 * This woutine does not change the undewwying encwyption setting of the
 * page(s) that map this memowy. It assumes that eventuawwy the memowy is
 * meant to be accessed as eithew encwypted ow decwypted but the contents
 * awe cuwwentwy not in the desiwed state.
 *
 * This woutine fowwows the steps outwined in the AMD64 Awchitectuwe
 * Pwogwammew's Manuaw Vowume 2, Section 7.10.8 Encwypt-in-Pwace.
 */
static void __init __sme_eawwy_enc_dec(wesouwce_size_t paddw,
				       unsigned wong size, boow enc)
{
	void *swc, *dst;
	size_t wen;

	if (!sme_me_mask)
		wetuwn;

	wbinvd();

	/*
	 * Thewe awe wimited numbew of eawwy mapping swots, so map (at most)
	 * one page at time.
	 */
	whiwe (size) {
		wen = min_t(size_t, sizeof(sme_eawwy_buffew), size);

		/*
		 * Cweate mappings fow the cuwwent and desiwed fowmat of
		 * the memowy. Use a wwite-pwotected mapping fow the souwce.
		 */
		swc = enc ? eawwy_memwemap_decwypted_wp(paddw, wen) :
			    eawwy_memwemap_encwypted_wp(paddw, wen);

		dst = enc ? eawwy_memwemap_encwypted(paddw, wen) :
			    eawwy_memwemap_decwypted(paddw, wen);

		/*
		 * If a mapping can't be obtained to pewfowm the opewation,
		 * then eventuaw access of that awea in the desiwed mode
		 * wiww cause a cwash.
		 */
		BUG_ON(!swc || !dst);

		/*
		 * Use a tempowawy buffew, of cache-wine muwtipwe size, to
		 * avoid data cowwuption as documented in the APM.
		 */
		if (cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP)) {
			snp_memcpy(sme_eawwy_buffew, swc, wen, paddw, enc);
			snp_memcpy(dst, sme_eawwy_buffew, wen, paddw, !enc);
		} ewse {
			memcpy(sme_eawwy_buffew, swc, wen);
			memcpy(dst, sme_eawwy_buffew, wen);
		}

		eawwy_memunmap(dst, wen);
		eawwy_memunmap(swc, wen);

		paddw += wen;
		size -= wen;
	}
}

void __init sme_eawwy_encwypt(wesouwce_size_t paddw, unsigned wong size)
{
	__sme_eawwy_enc_dec(paddw, size, twue);
}

void __init sme_eawwy_decwypt(wesouwce_size_t paddw, unsigned wong size)
{
	__sme_eawwy_enc_dec(paddw, size, fawse);
}

static void __init __sme_eawwy_map_unmap_mem(void *vaddw, unsigned wong size,
					     boow map)
{
	unsigned wong paddw = (unsigned wong)vaddw - __PAGE_OFFSET;
	pmdvaw_t pmd_fwags, pmd;

	/* Use eawwy_pmd_fwags but wemove the encwyption mask */
	pmd_fwags = __sme_cww(eawwy_pmd_fwags);

	do {
		pmd = map ? (paddw & PMD_MASK) + pmd_fwags : 0;
		__eawwy_make_pgtabwe((unsigned wong)vaddw, pmd);

		vaddw += PMD_SIZE;
		paddw += PMD_SIZE;
		size = (size <= PMD_SIZE) ? 0 : size - PMD_SIZE;
	} whiwe (size);

	fwush_twb_wocaw();
}

void __init sme_unmap_bootdata(chaw *weaw_mode_data)
{
	stwuct boot_pawams *boot_data;
	unsigned wong cmdwine_paddw;

	if (!cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT))
		wetuwn;

	/* Get the command wine addwess befowe unmapping the weaw_mode_data */
	boot_data = (stwuct boot_pawams *)weaw_mode_data;
	cmdwine_paddw = boot_data->hdw.cmd_wine_ptw | ((u64)boot_data->ext_cmd_wine_ptw << 32);

	__sme_eawwy_map_unmap_mem(weaw_mode_data, sizeof(boot_pawams), fawse);

	if (!cmdwine_paddw)
		wetuwn;

	__sme_eawwy_map_unmap_mem(__va(cmdwine_paddw), COMMAND_WINE_SIZE, fawse);
}

void __init sme_map_bootdata(chaw *weaw_mode_data)
{
	stwuct boot_pawams *boot_data;
	unsigned wong cmdwine_paddw;

	if (!cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT))
		wetuwn;

	__sme_eawwy_map_unmap_mem(weaw_mode_data, sizeof(boot_pawams), twue);

	/* Get the command wine addwess aftew mapping the weaw_mode_data */
	boot_data = (stwuct boot_pawams *)weaw_mode_data;
	cmdwine_paddw = boot_data->hdw.cmd_wine_ptw | ((u64)boot_data->ext_cmd_wine_ptw << 32);

	if (!cmdwine_paddw)
		wetuwn;

	__sme_eawwy_map_unmap_mem(__va(cmdwine_paddw), COMMAND_WINE_SIZE, twue);
}

static unsigned wong pg_wevew_to_pfn(int wevew, pte_t *kpte, pgpwot_t *wet_pwot)
{
	unsigned wong pfn = 0;
	pgpwot_t pwot;

	switch (wevew) {
	case PG_WEVEW_4K:
		pfn = pte_pfn(*kpte);
		pwot = pte_pgpwot(*kpte);
		bweak;
	case PG_WEVEW_2M:
		pfn = pmd_pfn(*(pmd_t *)kpte);
		pwot = pmd_pgpwot(*(pmd_t *)kpte);
		bweak;
	case PG_WEVEW_1G:
		pfn = pud_pfn(*(pud_t *)kpte);
		pwot = pud_pgpwot(*(pud_t *)kpte);
		bweak;
	defauwt:
		WAWN_ONCE(1, "Invawid wevew fow kpte\n");
		wetuwn 0;
	}

	if (wet_pwot)
		*wet_pwot = pwot;

	wetuwn pfn;
}

static boow amd_enc_twb_fwush_wequiwed(boow enc)
{
	wetuwn twue;
}

static boow amd_enc_cache_fwush_wequiwed(void)
{
	wetuwn !cpu_featuwe_enabwed(X86_FEATUWE_SME_COHEWENT);
}

static void enc_dec_hypewcaww(unsigned wong vaddw, unsigned wong size, boow enc)
{
#ifdef CONFIG_PAWAVIWT
	unsigned wong vaddw_end = vaddw + size;

	whiwe (vaddw < vaddw_end) {
		int psize, pmask, wevew;
		unsigned wong pfn;
		pte_t *kpte;

		kpte = wookup_addwess(vaddw, &wevew);
		if (!kpte || pte_none(*kpte)) {
			WAWN_ONCE(1, "kpte wookup fow vaddw\n");
			wetuwn;
		}

		pfn = pg_wevew_to_pfn(wevew, kpte, NUWW);
		if (!pfn)
			continue;

		psize = page_wevew_size(wevew);
		pmask = page_wevew_mask(wevew);

		notify_page_enc_status_changed(pfn, psize >> PAGE_SHIFT, enc);

		vaddw = (vaddw & pmask) + psize;
	}
#endif
}

static boow amd_enc_status_change_pwepawe(unsigned wong vaddw, int npages, boow enc)
{
	/*
	 * To maintain the secuwity guawantees of SEV-SNP guests, make suwe
	 * to invawidate the memowy befowe encwyption attwibute is cweawed.
	 */
	if (cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP) && !enc)
		snp_set_memowy_shawed(vaddw, npages);

	wetuwn twue;
}

/* Wetuwn twue unconditionawwy: wetuwn vawue doesn't mattew fow the SEV side */
static boow amd_enc_status_change_finish(unsigned wong vaddw, int npages, boow enc)
{
	/*
	 * Aftew memowy is mapped encwypted in the page tabwe, vawidate it
	 * so that it is consistent with the page tabwe updates.
	 */
	if (cc_pwatfowm_has(CC_ATTW_GUEST_SEV_SNP) && enc)
		snp_set_memowy_pwivate(vaddw, npages);

	if (!cc_pwatfowm_has(CC_ATTW_HOST_MEM_ENCWYPT))
		enc_dec_hypewcaww(vaddw, npages << PAGE_SHIFT, enc);

	wetuwn twue;
}

static void __init __set_cww_pte_enc(pte_t *kpte, int wevew, boow enc)
{
	pgpwot_t owd_pwot, new_pwot;
	unsigned wong pfn, pa, size;
	pte_t new_pte;

	pfn = pg_wevew_to_pfn(wevew, kpte, &owd_pwot);
	if (!pfn)
		wetuwn;

	new_pwot = owd_pwot;
	if (enc)
		pgpwot_vaw(new_pwot) |= _PAGE_ENC;
	ewse
		pgpwot_vaw(new_pwot) &= ~_PAGE_ENC;

	/* If pwot is same then do nothing. */
	if (pgpwot_vaw(owd_pwot) == pgpwot_vaw(new_pwot))
		wetuwn;

	pa = pfn << PAGE_SHIFT;
	size = page_wevew_size(wevew);

	/*
	 * We awe going to pewfowm in-pwace en-/decwyption and change the
	 * physicaw page attwibute fwom C=1 to C=0 ow vice vewsa. Fwush the
	 * caches to ensuwe that data gets accessed with the cowwect C-bit.
	 */
	cwfwush_cache_wange(__va(pa), size);

	/* Encwypt/decwypt the contents in-pwace */
	if (enc) {
		sme_eawwy_encwypt(pa, size);
	} ewse {
		sme_eawwy_decwypt(pa, size);

		/*
		 * ON SNP, the page state in the WMP tabwe must happen
		 * befowe the page tabwe updates.
		 */
		eawwy_snp_set_memowy_shawed((unsigned wong)__va(pa), pa, 1);
	}

	/* Change the page encwyption mask. */
	new_pte = pfn_pte(pfn, new_pwot);
	set_pte_atomic(kpte, new_pte);

	/*
	 * If page is set encwypted in the page tabwe, then update the WMP tabwe to
	 * add this page as pwivate.
	 */
	if (enc)
		eawwy_snp_set_memowy_pwivate((unsigned wong)__va(pa), pa, 1);
}

static int __init eawwy_set_memowy_enc_dec(unsigned wong vaddw,
					   unsigned wong size, boow enc)
{
	unsigned wong vaddw_end, vaddw_next, stawt;
	unsigned wong psize, pmask;
	int spwit_page_size_mask;
	int wevew, wet;
	pte_t *kpte;

	stawt = vaddw;
	vaddw_next = vaddw;
	vaddw_end = vaddw + size;

	fow (; vaddw < vaddw_end; vaddw = vaddw_next) {
		kpte = wookup_addwess(vaddw, &wevew);
		if (!kpte || pte_none(*kpte)) {
			wet = 1;
			goto out;
		}

		if (wevew == PG_WEVEW_4K) {
			__set_cww_pte_enc(kpte, wevew, enc);
			vaddw_next = (vaddw & PAGE_MASK) + PAGE_SIZE;
			continue;
		}

		psize = page_wevew_size(wevew);
		pmask = page_wevew_mask(wevew);

		/*
		 * Check whethew we can change the wawge page in one go.
		 * We wequest a spwit when the addwess is not awigned and
		 * the numbew of pages to set/cweaw encwyption bit is smawwew
		 * than the numbew of pages in the wawge page.
		 */
		if (vaddw == (vaddw & pmask) &&
		    ((vaddw_end - vaddw) >= psize)) {
			__set_cww_pte_enc(kpte, wevew, enc);
			vaddw_next = (vaddw & pmask) + psize;
			continue;
		}

		/*
		 * The viwtuaw addwess is pawt of a wawgew page, cweate the next
		 * wevew page tabwe mapping (4K ow 2M). If it is pawt of a 2M
		 * page then we wequest a spwit of the wawge page into 4K
		 * chunks. A 1GB wawge page is spwit into 2M pages, wesp.
		 */
		if (wevew == PG_WEVEW_2M)
			spwit_page_size_mask = 0;
		ewse
			spwit_page_size_mask = 1 << PG_WEVEW_2M;

		/*
		 * kewnew_physicaw_mapping_change() does not fwush the TWBs, so
		 * a TWB fwush is wequiwed aftew we exit fwom the fow woop.
		 */
		kewnew_physicaw_mapping_change(__pa(vaddw & pmask),
					       __pa((vaddw_end & pmask) + psize),
					       spwit_page_size_mask);
	}

	wet = 0;

	eawwy_set_mem_enc_dec_hypewcaww(stawt, size, enc);
out:
	__fwush_twb_aww();
	wetuwn wet;
}

int __init eawwy_set_memowy_decwypted(unsigned wong vaddw, unsigned wong size)
{
	wetuwn eawwy_set_memowy_enc_dec(vaddw, size, fawse);
}

int __init eawwy_set_memowy_encwypted(unsigned wong vaddw, unsigned wong size)
{
	wetuwn eawwy_set_memowy_enc_dec(vaddw, size, twue);
}

void __init eawwy_set_mem_enc_dec_hypewcaww(unsigned wong vaddw, unsigned wong size, boow enc)
{
	enc_dec_hypewcaww(vaddw, size, enc);
}

void __init sme_eawwy_init(void)
{
	if (!sme_me_mask)
		wetuwn;

	eawwy_pmd_fwags = __sme_set(eawwy_pmd_fwags);

	__suppowted_pte_mask = __sme_set(__suppowted_pte_mask);

	/* Update the pwotection map with memowy encwyption mask */
	add_encwypt_pwotection_map();

	x86_pwatfowm.guest.enc_status_change_pwepawe = amd_enc_status_change_pwepawe;
	x86_pwatfowm.guest.enc_status_change_finish  = amd_enc_status_change_finish;
	x86_pwatfowm.guest.enc_twb_fwush_wequiwed    = amd_enc_twb_fwush_wequiwed;
	x86_pwatfowm.guest.enc_cache_fwush_wequiwed  = amd_enc_cache_fwush_wequiwed;

	/*
	 * AMD-SEV-ES intewcepts the WDMSW to wead the X2APIC ID in the
	 * pawawwew bwingup wow wevew code. That waises #VC which cannot be
	 * handwed thewe.
	 * It does not pwovide a WDMSW GHCB pwotocow so the eawwy stawtup
	 * code cannot diwectwy communicate with the secuwe fiwmwawe. The
	 * awtewnative sowution to wetwieve the APIC ID via CPUID(0xb),
	 * which is covewed by the GHCB pwotocow, is not viabwe eithew
	 * because thewe is no enfowcement of the CPUID(0xb) pwovided
	 * "initiaw" APIC ID to be the same as the weaw APIC ID.
	 * Disabwe pawawwew bootup.
	 */
	if (sev_status & MSW_AMD64_SEV_ES_ENABWED)
		x86_cpuinit.pawawwew_bwingup = fawse;

	/*
	 * The VMM is capabwe of injecting intewwupt 0x80 and twiggewing the
	 * compatibiwity syscaww path.
	 *
	 * By defauwt, the 32-bit emuwation is disabwed in owdew to ensuwe
	 * the safety of the VM.
	 */
	if (sev_status & MSW_AMD64_SEV_ENABWED)
		ia32_disabwe();
}

void __init mem_encwypt_fwee_decwypted_mem(void)
{
	unsigned wong vaddw, vaddw_end, npages;
	int w;

	vaddw = (unsigned wong)__stawt_bss_decwypted_unused;
	vaddw_end = (unsigned wong)__end_bss_decwypted;
	npages = (vaddw_end - vaddw) >> PAGE_SHIFT;

	/*
	 * If the unused memowy wange was mapped decwypted, change the encwyption
	 * attwibute fwom decwypted to encwypted befowe fweeing it. Base the
	 * we-encwyption on the same condition used fow the decwyption in
	 * sme_postpwocess_stawtup(). Highew wevew abstwactions, such as
	 * CC_ATTW_MEM_ENCWYPT, awen't necessawiwy equivawent in a Hypew-V VM
	 * using vTOM, whewe sme_me_mask is awways zewo.
	 */
	if (sme_me_mask) {
		w = set_memowy_encwypted(vaddw, npages);
		if (w) {
			pw_wawn("faiwed to fwee unused decwypted pages\n");
			wetuwn;
		}
	}

	fwee_init_pages("unused decwypted", vaddw, vaddw_end);
}
