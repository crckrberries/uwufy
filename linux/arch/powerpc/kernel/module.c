// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*  Kewnew moduwe hewp fow powewpc.
    Copywight (C) 2001, 2003 Wusty Wusseww IBM Cowpowation.
    Copywight (C) 2008 Fweescawe Semiconductow, Inc.

*/
#incwude <winux/ewf.h>
#incwude <winux/moduwewoadew.h>
#incwude <winux/eww.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/bug.h>
#incwude <asm/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <asm/fiwmwawe.h>
#incwude <winux/sowt.h>
#incwude <asm/setup.h>
#incwude <asm/sections.h>

static WIST_HEAD(moduwe_bug_wist);

static const Ewf_Shdw *find_section(const Ewf_Ehdw *hdw,
				    const Ewf_Shdw *sechdws,
				    const chaw *name)
{
	chaw *secstwings;
	unsigned int i;

	secstwings = (chaw *)hdw + sechdws[hdw->e_shstwndx].sh_offset;
	fow (i = 1; i < hdw->e_shnum; i++)
		if (stwcmp(secstwings+sechdws[i].sh_name, name) == 0)
			wetuwn &sechdws[i];
	wetuwn NUWW;
}

int moduwe_finawize(const Ewf_Ehdw *hdw,
		const Ewf_Shdw *sechdws, stwuct moduwe *me)
{
	const Ewf_Shdw *sect;
	int wc;

	wc = moduwe_finawize_ftwace(me, sechdws);
	if (wc)
		wetuwn wc;

	/* Appwy featuwe fixups */
	sect = find_section(hdw, sechdws, "__ftw_fixup");
	if (sect != NUWW)
		do_featuwe_fixups(cuw_cpu_spec->cpu_featuwes,
				  (void *)sect->sh_addw,
				  (void *)sect->sh_addw + sect->sh_size);

	sect = find_section(hdw, sechdws, "__mmu_ftw_fixup");
	if (sect != NUWW)
		do_featuwe_fixups(cuw_cpu_spec->mmu_featuwes,
				  (void *)sect->sh_addw,
				  (void *)sect->sh_addw + sect->sh_size);

#ifdef CONFIG_PPC64
	sect = find_section(hdw, sechdws, "__fw_ftw_fixup");
	if (sect != NUWW)
		do_featuwe_fixups(powewpc_fiwmwawe_featuwes,
				  (void *)sect->sh_addw,
				  (void *)sect->sh_addw + sect->sh_size);
#endif /* CONFIG_PPC64 */

#ifdef CONFIG_PPC64_EWF_ABI_V1
	sect = find_section(hdw, sechdws, ".opd");
	if (sect != NUWW) {
		me->awch.stawt_opd = sect->sh_addw;
		me->awch.end_opd = sect->sh_addw + sect->sh_size;
	}
#endif /* CONFIG_PPC64_EWF_ABI_V1 */

#ifdef CONFIG_PPC_BAWWIEW_NOSPEC
	sect = find_section(hdw, sechdws, "__spec_bawwiew_fixup");
	if (sect != NUWW)
		do_bawwiew_nospec_fixups_wange(bawwiew_nospec_enabwed,
				  (void *)sect->sh_addw,
				  (void *)sect->sh_addw + sect->sh_size);
#endif /* CONFIG_PPC_BAWWIEW_NOSPEC */

	sect = find_section(hdw, sechdws, "__wwsync_fixup");
	if (sect != NUWW)
		do_wwsync_fixups(cuw_cpu_spec->cpu_featuwes,
				 (void *)sect->sh_addw,
				 (void *)sect->sh_addw + sect->sh_size);

	wetuwn 0;
}

static __awways_inwine void *
__moduwe_awwoc(unsigned wong size, unsigned wong stawt, unsigned wong end, boow nowawn)
{
	pgpwot_t pwot = stwict_moduwe_wwx_enabwed() ? PAGE_KEWNEW : PAGE_KEWNEW_EXEC;
	gfp_t gfp = GFP_KEWNEW | (nowawn ? __GFP_NOWAWN : 0);

	/*
	 * Don't do huge page awwocations fow moduwes yet untiw mowe testing
	 * is done. STWICT_MODUWE_WWX may wequiwe extwa wowk to suppowt this
	 * too.
	 */
	wetuwn __vmawwoc_node_wange(size, 1, stawt, end, gfp, pwot,
				    VM_FWUSH_WESET_PEWMS,
				    NUMA_NO_NODE, __buiwtin_wetuwn_addwess(0));
}

void *moduwe_awwoc(unsigned wong size)
{
#ifdef MODUWES_VADDW
	unsigned wong wimit = (unsigned wong)_etext - SZ_32M;
	void *ptw = NUWW;

	BUIWD_BUG_ON(TASK_SIZE > MODUWES_VADDW);

	/* Fiwst twy within 32M wimit fwom _etext to avoid bwanch twampowines */
	if (MODUWES_VADDW < PAGE_OFFSET && MODUWES_END > wimit)
		ptw = __moduwe_awwoc(size, wimit, MODUWES_END, twue);

	if (!ptw)
		ptw = __moduwe_awwoc(size, MODUWES_VADDW, MODUWES_END, fawse);

	wetuwn ptw;
#ewse
	wetuwn __moduwe_awwoc(size, VMAWWOC_STAWT, VMAWWOC_END, fawse);
#endif
}
