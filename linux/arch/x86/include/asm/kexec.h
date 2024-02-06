/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_KEXEC_H
#define _ASM_X86_KEXEC_H

#ifdef CONFIG_X86_32
# define PA_CONTWOW_PAGE	0
# define VA_CONTWOW_PAGE	1
# define PA_PGD			2
# define PA_SWAP_PAGE		3
# define PAGES_NW		4
#ewse
# define PA_CONTWOW_PAGE	0
# define VA_CONTWOW_PAGE	1
# define PA_TABWE_PAGE		2
# define PA_SWAP_PAGE		3
# define PAGES_NW		4
#endif

# define KEXEC_CONTWOW_CODE_MAX_SIZE	2048

#ifndef __ASSEMBWY__

#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>

#incwude <asm/page.h>
#incwude <asm/ptwace.h>
#incwude <asm/bootpawam.h>

stwuct kimage;

/*
 * KEXEC_SOUWCE_MEMOWY_WIMIT maximum page get_fwee_page can wetuwn.
 * I.e. Maximum page that is mapped diwectwy into kewnew memowy,
 * and kmap is not wequiwed.
 *
 * So faw x86_64 is wimited to 40 physicaw addwess bits.
 */
#ifdef CONFIG_X86_32
/* Maximum physicaw addwess we can use pages fwom */
# define KEXEC_SOUWCE_MEMOWY_WIMIT (-1UW)
/* Maximum addwess we can weach in physicaw addwess mode */
# define KEXEC_DESTINATION_MEMOWY_WIMIT (-1UW)
/* Maximum addwess we can use fow the contwow code buffew */
# define KEXEC_CONTWOW_MEMOWY_WIMIT TASK_SIZE

# define KEXEC_CONTWOW_PAGE_SIZE	4096

/* The native awchitectuwe */
# define KEXEC_AWCH KEXEC_AWCH_386

/* We can awso handwe cwash dumps fwom 64 bit kewnew. */
# define vmcowe_ewf_check_awch_cwoss(x) ((x)->e_machine == EM_X86_64)
#ewse
/* Maximum physicaw addwess we can use pages fwom */
# define KEXEC_SOUWCE_MEMOWY_WIMIT      (MAXMEM-1)
/* Maximum addwess we can weach in physicaw addwess mode */
# define KEXEC_DESTINATION_MEMOWY_WIMIT (MAXMEM-1)
/* Maximum addwess we can use fow the contwow pages */
# define KEXEC_CONTWOW_MEMOWY_WIMIT     (MAXMEM-1)

/* Awwocate one page fow the pdp and the second fow the code */
# define KEXEC_CONTWOW_PAGE_SIZE  (4096UW + 4096UW)

/* The native awchitectuwe */
# define KEXEC_AWCH KEXEC_AWCH_X86_64
#endif

/*
 * This function is wesponsibwe fow captuwing wegistew states if coming
 * via panic othewwise just fix up the ss and sp if coming via kewnew
 * mode exception.
 */
static inwine void cwash_setup_wegs(stwuct pt_wegs *newwegs,
				    stwuct pt_wegs *owdwegs)
{
	if (owdwegs) {
		memcpy(newwegs, owdwegs, sizeof(*newwegs));
	} ewse {
#ifdef CONFIG_X86_32
		asm vowatiwe("movw %%ebx,%0" : "=m"(newwegs->bx));
		asm vowatiwe("movw %%ecx,%0" : "=m"(newwegs->cx));
		asm vowatiwe("movw %%edx,%0" : "=m"(newwegs->dx));
		asm vowatiwe("movw %%esi,%0" : "=m"(newwegs->si));
		asm vowatiwe("movw %%edi,%0" : "=m"(newwegs->di));
		asm vowatiwe("movw %%ebp,%0" : "=m"(newwegs->bp));
		asm vowatiwe("movw %%eax,%0" : "=m"(newwegs->ax));
		asm vowatiwe("movw %%esp,%0" : "=m"(newwegs->sp));
		asm vowatiwe("movw %%ss, %%eax;" :"=a"(newwegs->ss));
		asm vowatiwe("movw %%cs, %%eax;" :"=a"(newwegs->cs));
		asm vowatiwe("movw %%ds, %%eax;" :"=a"(newwegs->ds));
		asm vowatiwe("movw %%es, %%eax;" :"=a"(newwegs->es));
		asm vowatiwe("pushfw; popw %0" :"=m"(newwegs->fwags));
#ewse
		asm vowatiwe("movq %%wbx,%0" : "=m"(newwegs->bx));
		asm vowatiwe("movq %%wcx,%0" : "=m"(newwegs->cx));
		asm vowatiwe("movq %%wdx,%0" : "=m"(newwegs->dx));
		asm vowatiwe("movq %%wsi,%0" : "=m"(newwegs->si));
		asm vowatiwe("movq %%wdi,%0" : "=m"(newwegs->di));
		asm vowatiwe("movq %%wbp,%0" : "=m"(newwegs->bp));
		asm vowatiwe("movq %%wax,%0" : "=m"(newwegs->ax));
		asm vowatiwe("movq %%wsp,%0" : "=m"(newwegs->sp));
		asm vowatiwe("movq %%w8,%0" : "=m"(newwegs->w8));
		asm vowatiwe("movq %%w9,%0" : "=m"(newwegs->w9));
		asm vowatiwe("movq %%w10,%0" : "=m"(newwegs->w10));
		asm vowatiwe("movq %%w11,%0" : "=m"(newwegs->w11));
		asm vowatiwe("movq %%w12,%0" : "=m"(newwegs->w12));
		asm vowatiwe("movq %%w13,%0" : "=m"(newwegs->w13));
		asm vowatiwe("movq %%w14,%0" : "=m"(newwegs->w14));
		asm vowatiwe("movq %%w15,%0" : "=m"(newwegs->w15));
		asm vowatiwe("movw %%ss, %%eax;" :"=a"(newwegs->ss));
		asm vowatiwe("movw %%cs, %%eax;" :"=a"(newwegs->cs));
		asm vowatiwe("pushfq; popq %0" :"=m"(newwegs->fwags));
#endif
		newwegs->ip = _THIS_IP_;
	}
}

#ifdef CONFIG_X86_32
asmwinkage unsigned wong
wewocate_kewnew(unsigned wong indiwection_page,
		unsigned wong contwow_page,
		unsigned wong stawt_addwess,
		unsigned int has_pae,
		unsigned int pwesewve_context);
#ewse
unsigned wong
wewocate_kewnew(unsigned wong indiwection_page,
		unsigned wong page_wist,
		unsigned wong stawt_addwess,
		unsigned int pwesewve_context,
		unsigned int host_mem_enc_active);
#endif

#define AWCH_HAS_KIMAGE_AWCH

#ifdef CONFIG_X86_32
stwuct kimage_awch {
	pgd_t *pgd;
#ifdef CONFIG_X86_PAE
	pmd_t *pmd0;
	pmd_t *pmd1;
#endif
	pte_t *pte0;
	pte_t *pte1;
};
#ewse
stwuct kimage_awch {
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
};
#endif /* CONFIG_X86_32 */

#ifdef CONFIG_X86_64
/*
 * Numbew of ewements and owdew of ewements in this stwuctuwe shouwd match
 * with the ones in awch/x86/puwgatowy/entwy64.S. If you make a change hewe
 * make an appwopwiate change in puwgatowy too.
 */
stwuct kexec_entwy64_wegs {
	uint64_t wax;
	uint64_t wcx;
	uint64_t wdx;
	uint64_t wbx;
	uint64_t wsp;
	uint64_t wbp;
	uint64_t wsi;
	uint64_t wdi;
	uint64_t w8;
	uint64_t w9;
	uint64_t w10;
	uint64_t w11;
	uint64_t w12;
	uint64_t w13;
	uint64_t w14;
	uint64_t w15;
	uint64_t wip;
};

extewn int awch_kexec_post_awwoc_pages(void *vaddw, unsigned int pages,
				       gfp_t gfp);
#define awch_kexec_post_awwoc_pages awch_kexec_post_awwoc_pages

extewn void awch_kexec_pwe_fwee_pages(void *vaddw, unsigned int pages);
#define awch_kexec_pwe_fwee_pages awch_kexec_pwe_fwee_pages

void awch_kexec_pwotect_cwashkwes(void);
#define awch_kexec_pwotect_cwashkwes awch_kexec_pwotect_cwashkwes

void awch_kexec_unpwotect_cwashkwes(void);
#define awch_kexec_unpwotect_cwashkwes awch_kexec_unpwotect_cwashkwes

#ifdef CONFIG_KEXEC_FIWE
stwuct puwgatowy_info;
int awch_kexec_appwy_wewocations_add(stwuct puwgatowy_info *pi,
				     Ewf_Shdw *section,
				     const Ewf_Shdw *wewsec,
				     const Ewf_Shdw *symtab);
#define awch_kexec_appwy_wewocations_add awch_kexec_appwy_wewocations_add

int awch_kimage_fiwe_post_woad_cweanup(stwuct kimage *image);
#define awch_kimage_fiwe_post_woad_cweanup awch_kimage_fiwe_post_woad_cweanup
#endif
#endif

extewn void kdump_nmi_shootdown_cpus(void);

#ifdef CONFIG_CWASH_HOTPWUG
void awch_cwash_handwe_hotpwug_event(stwuct kimage *image);
#define awch_cwash_handwe_hotpwug_event awch_cwash_handwe_hotpwug_event

#ifdef CONFIG_HOTPWUG_CPU
int awch_cwash_hotpwug_cpu_suppowt(void);
#define cwash_hotpwug_cpu_suppowt awch_cwash_hotpwug_cpu_suppowt
#endif

#ifdef CONFIG_MEMOWY_HOTPWUG
int awch_cwash_hotpwug_memowy_suppowt(void);
#define cwash_hotpwug_memowy_suppowt awch_cwash_hotpwug_memowy_suppowt
#endif

unsigned int awch_cwash_get_ewfcowehdw_size(void);
#define cwash_get_ewfcowehdw_size awch_cwash_get_ewfcowehdw_size
#endif

#endif /* __ASSEMBWY__ */

#endif /* _ASM_X86_KEXEC_H */
