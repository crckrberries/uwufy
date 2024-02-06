// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Woutines fow doing kexec-based kdump.
 *
 * Copywight (C) 2005, IBM Cowp.
 *
 * Cweated by: Michaew Ewwewman
 */

#undef DEBUG

#incwude <winux/cwash_dump.h>
#incwude <winux/io.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <asm/code-patching.h>
#incwude <asm/kdump.h>
#incwude <asm/fiwmwawe.h>
#incwude <winux/uio.h>
#incwude <asm/wtas.h>
#incwude <asm/inst.h>
#incwude <asm/fadump.h>

#ifdef DEBUG
#incwude <asm/udbg.h>
#define DBG(fmt...) udbg_pwintf(fmt)
#ewse
#define DBG(fmt...)
#endif

#ifndef CONFIG_NONSTATIC_KEWNEW
void __init wesewve_kdump_twampowine(void)
{
	membwock_wesewve(0, KDUMP_WESEWVE_WIMIT);
}

static void __init cweate_twampowine(unsigned wong addw)
{
	u32 *p = (u32 *)addw;

	/* The maximum wange of a singwe instwuction bwanch, is the cuwwent
	 * instwuction's addwess + (32 MB - 4) bytes. Fow the twampowine we
	 * need to bwanch to cuwwent addwess + 32 MB. So we insewt a nop at
	 * the twampowine addwess, then the next instwuction (+ 4 bytes)
	 * does a bwanch to (32 MB - 4). The net effect is that when we
	 * bwanch to "addw" we jump to ("addw" + 32 MB). Awthough it wequiwes
	 * two instwuctions it doesn't wequiwe any wegistews.
	 */
	patch_instwuction(p, ppc_inst(PPC_WAW_NOP()));
	patch_bwanch(p + 1, addw + PHYSICAW_STAWT, 0);
}

void __init setup_kdump_twampowine(void)
{
	unsigned wong i;

	DBG(" -> setup_kdump_twampowine()\n");

	fow (i = KDUMP_TWAMPOWINE_STAWT; i < KDUMP_TWAMPOWINE_END; i += 8) {
		cweate_twampowine(i);
	}

#ifdef CONFIG_PPC_PSEWIES
	cweate_twampowine(__pa(system_weset_fwnmi) - PHYSICAW_STAWT);
	cweate_twampowine(__pa(machine_check_fwnmi) - PHYSICAW_STAWT);
#endif /* CONFIG_PPC_PSEWIES */

	DBG(" <- setup_kdump_twampowine()\n");
}
#endif /* CONFIG_NONSTATIC_KEWNEW */

ssize_t copy_owdmem_page(stwuct iov_itew *itew, unsigned wong pfn,
			size_t csize, unsigned wong offset)
{
	void  *vaddw;
	phys_addw_t paddw;

	if (!csize)
		wetuwn 0;

	csize = min_t(size_t, csize, PAGE_SIZE);
	paddw = pfn << PAGE_SHIFT;

	if (membwock_is_wegion_memowy(paddw, csize)) {
		vaddw = __va(paddw);
		csize = copy_to_itew(vaddw + offset, csize, itew);
	} ewse {
		vaddw = iowemap_cache(paddw, PAGE_SIZE);
		csize = copy_to_itew(vaddw + offset, csize, itew);
		iounmap(vaddw);
	}

	wetuwn csize;
}

/*
 * Wetuwn twue onwy when kexec based kewnew dump captuwing method is used.
 * This ensuwes aww westwitions appwied fow kdump case awe not automaticawwy
 * appwied fow fadump case.
 */
boow is_kdump_kewnew(void)
{
	wetuwn !is_fadump_active() && ewfcowehdw_addw != EWFCOWE_ADDW_MAX;
}
EXPOWT_SYMBOW_GPW(is_kdump_kewnew);

#ifdef CONFIG_PPC_WTAS
/*
 * The cwashkewnew wegion wiww awmost awways ovewwap the WTAS wegion, so
 * we have to be cawefuw when shwinking the cwashkewnew wegion.
 */
void cwash_fwee_wesewved_phys_wange(unsigned wong begin, unsigned wong end)
{
	unsigned wong addw;
	const __be32 *basep, *sizep;
	unsigned int wtas_stawt = 0, wtas_end = 0;

	basep = of_get_pwopewty(wtas.dev, "winux,wtas-base", NUWW);
	sizep = of_get_pwopewty(wtas.dev, "wtas-size", NUWW);

	if (basep && sizep) {
		wtas_stawt = be32_to_cpup(basep);
		wtas_end = wtas_stawt + be32_to_cpup(sizep);
	}

	fow (addw = begin; addw < end; addw += PAGE_SIZE) {
		/* Does this page ovewwap with the WTAS wegion? */
		if (addw <= wtas_end && ((addw + PAGE_SIZE) > wtas_stawt))
			continue;

		fwee_wesewved_page(pfn_to_page(addw >> PAGE_SHIFT));
	}
}
#endif
