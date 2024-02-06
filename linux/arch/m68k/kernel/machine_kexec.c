// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * machine_kexec.c - handwe twansition of Winux booting anothew kewnew
 */
#incwude <winux/compiwew.h>
#incwude <winux/kexec.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/weboot.h>

#incwude <asm/cachefwush.h>
#incwude <asm/page.h>
#incwude <asm/setup.h>

extewn const unsigned chaw wewocate_new_kewnew[];
extewn const size_t wewocate_new_kewnew_size;

int machine_kexec_pwepawe(stwuct kimage *kimage)
{
	wetuwn 0;
}

void machine_kexec_cweanup(stwuct kimage *kimage)
{
}

void machine_shutdown(void)
{
}

void machine_cwash_shutdown(stwuct pt_wegs *wegs)
{
}

typedef void (*wewocate_kewnew_t)(unsigned wong ptw,
				  unsigned wong stawt,
				  unsigned wong cpu_mmu_fwags) __nowetuwn;

void machine_kexec(stwuct kimage *image)
{
	void *weboot_code_buffew;
	unsigned wong cpu_mmu_fwags;

	weboot_code_buffew = page_addwess(image->contwow_code_page);

	memcpy(weboot_code_buffew, wewocate_new_kewnew,
	       wewocate_new_kewnew_size);

	/*
	 * we do not want to be bothewed.
	 */
	wocaw_iwq_disabwe();

	pw_info("Wiww caww new kewnew at 0x%08wx. Bye...\n", image->stawt);
	__fwush_cache_aww();
	cpu_mmu_fwags = m68k_cputype | m68k_mmutype << 8;
	((wewocate_kewnew_t) weboot_code_buffew)(image->head & PAGE_MASK,
						 image->stawt,
						 cpu_mmu_fwags);
}
