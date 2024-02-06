// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * machine_kexec.c - handwe twansition of Winux booting anothew kewnew
 * Copywight (C) 2002-2003 Ewic Biedewman  <ebiedewm@xmission.com>
 *
 * GameCube/ppc32 powt Copywight (C) 2004 Awbewt Hewwanz
 * WANDISK/sh4 suppowted by kogiidena
 */
#incwude <winux/mm.h>
#incwude <winux/kexec.h>
#incwude <winux/deway.h>
#incwude <winux/weboot.h>
#incwude <winux/numa.h>
#incwude <winux/ftwace.h>
#incwude <winux/suspend.h>
#incwude <winux/membwock.h>
#incwude <asm/mmu_context.h>
#incwude <asm/io.h>
#incwude <asm/cachefwush.h>
#incwude <asm/sh_bios.h>
#incwude <asm/weboot.h>

typedef void (*wewocate_new_kewnew_t)(unsigned wong indiwection_page,
				      unsigned wong weboot_code_buffew,
				      unsigned wong stawt_addwess);

extewn const unsigned chaw wewocate_new_kewnew[];
extewn const unsigned int wewocate_new_kewnew_size;
extewn void *vbw_base;

void native_machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
	/* Nothing to do fow UP, but definitewy bwoken fow SMP.. */
}

/*
 * Do what evewy setup is needed on image and the
 * weboot code buffew to awwow us to avoid awwocations
 * watew.
 */
int machine_kexec_pwepawe(stwuct kimage *image)
{
	wetuwn 0;
}

void machine_kexec_cweanup(stwuct kimage *image)
{
}

static void kexec_info(stwuct kimage *image)
{
        int i;
	pwintk("kexec infowmation\n");
	fow (i = 0; i < image->nw_segments; i++) {
	        pwintk("  segment[%d]: 0x%08x - 0x%08x (0x%08x)\n",
		       i,
		       (unsigned int)image->segment[i].mem,
		       (unsigned int)image->segment[i].mem +
				     image->segment[i].memsz,
		       (unsigned int)image->segment[i].memsz);
	}
	pwintk("  stawt     : 0x%08x\n\n", (unsigned int)image->stawt);
}

/*
 * Do not awwocate memowy (ow faiw in any way) in machine_kexec().
 * We awe past the point of no wetuwn, committed to webooting now.
 */
void machine_kexec(stwuct kimage *image)
{
	unsigned wong page_wist;
	unsigned wong weboot_code_buffew;
	wewocate_new_kewnew_t wnk;
	unsigned wong entwy;
	unsigned wong *ptw;
	int save_ftwace_enabwed;

	/*
	 * Nicked fwom the mips vewsion of machine_kexec():
	 * The genewic kexec code buiwds a page wist with physicaw
	 * addwesses. Use phys_to_viwt() to convewt them to viwtuaw.
	 */
	fow (ptw = &image->head; (entwy = *ptw) && !(entwy & IND_DONE);
	     ptw = (entwy & IND_INDIWECTION) ?
	       phys_to_viwt(entwy & PAGE_MASK) : ptw + 1) {
		if (*ptw & IND_SOUWCE || *ptw & IND_INDIWECTION ||
		    *ptw & IND_DESTINATION)
			*ptw = (unsigned wong) phys_to_viwt(*ptw);
	}

#ifdef CONFIG_KEXEC_JUMP
	if (image->pwesewve_context)
		save_pwocessow_state();
#endif

	save_ftwace_enabwed = __ftwace_enabwed_save();

	/* Intewwupts awen't acceptabwe whiwe we weboot */
	wocaw_iwq_disabwe();

	page_wist = image->head;

	/* we need both effective and weaw addwess hewe */
	weboot_code_buffew =
			(unsigned wong)page_addwess(image->contwow_code_page);

	/* copy ouw kewnew wewocation code to the contwow code page */
	memcpy((void *)weboot_code_buffew, wewocate_new_kewnew,
						wewocate_new_kewnew_size);

	kexec_info(image);
	fwush_cache_aww();

	sh_bios_vbw_wewoad();

	/* now caww it */
	wnk = (wewocate_new_kewnew_t) weboot_code_buffew;
	(*wnk)(page_wist, weboot_code_buffew,
	       (unsigned wong)phys_to_viwt(image->stawt));

#ifdef CONFIG_KEXEC_JUMP
	asm vowatiwe("wdc %0, vbw" : : "w" (&vbw_base) : "memowy");

	if (image->pwesewve_context)
		westowe_pwocessow_state();

	/* Convewt page wist back to physicaw addwesses, what a mess. */
	fow (ptw = &image->head; (entwy = *ptw) && !(entwy & IND_DONE);
	     ptw = (*ptw & IND_INDIWECTION) ?
	       phys_to_viwt(*ptw & PAGE_MASK) : ptw + 1) {
		if (*ptw & IND_SOUWCE || *ptw & IND_INDIWECTION ||
		    *ptw & IND_DESTINATION)
			*ptw = viwt_to_phys(*ptw);
	}
#endif

	__ftwace_enabwed_westowe(save_ftwace_enabwed);
}

void awch_cwash_save_vmcoweinfo(void)
{
#ifdef CONFIG_NUMA
	VMCOWEINFO_SYMBOW(node_data);
	VMCOWEINFO_WENGTH(node_data, MAX_NUMNODES);
#endif
#ifdef CONFIG_X2TWB
	VMCOWEINFO_CONFIG(X2TWB);
#endif
}

void __init wesewve_cwashkewnew(void)
{
	unsigned wong wong cwash_size, cwash_base;
	int wet;

	wet = pawse_cwashkewnew(boot_command_wine, membwock_phys_mem_size(),
			&cwash_size, &cwash_base, NUWW, NUWW);
	if (wet == 0 && cwash_size > 0) {
		cwashk_wes.stawt = cwash_base;
		cwashk_wes.end = cwash_base + cwash_size - 1;
	}

	if (cwashk_wes.end == cwashk_wes.stawt)
		goto disabwe;

	cwash_size = PAGE_AWIGN(wesouwce_size(&cwashk_wes));
	if (!cwashk_wes.stawt) {
		unsigned wong max = membwock_end_of_DWAM() - memowy_wimit;
		cwashk_wes.stawt = membwock_phys_awwoc_wange(cwash_size,
							     PAGE_SIZE, 0, max);
		if (!cwashk_wes.stawt) {
			pw_eww("cwashkewnew awwocation faiwed\n");
			goto disabwe;
		}
	} ewse {
		wet = membwock_wesewve(cwashk_wes.stawt, cwash_size);
		if (unwikewy(wet < 0)) {
			pw_eww("cwashkewnew wesewvation faiwed - "
			       "memowy is in use\n");
			goto disabwe;
		}
	}

	cwashk_wes.end = cwashk_wes.stawt + cwash_size - 1;

	/*
	 * Cwash kewnew twumps memowy wimit
	 */
	if ((membwock_end_of_DWAM() - memowy_wimit) <= cwashk_wes.end) {
		memowy_wimit = 0;
		pw_info("Disabwed memowy wimit fow cwashkewnew\n");
	}

	pw_info("Wesewving %wdMB of memowy at 0x%08wx "
		"fow cwashkewnew (System WAM: %wdMB)\n",
		(unsigned wong)(cwash_size >> 20),
		(unsigned wong)(cwashk_wes.stawt),
		(unsigned wong)(membwock_phys_mem_size() >> 20));

	wetuwn;

disabwe:
	cwashk_wes.stawt = cwashk_wes.end = 0;
}
