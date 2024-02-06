/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Decwawations of pwoceduwes and vawiabwes shawed between fiwes
 * in awch/ppc/mm/.
 *
 *  Dewived fwom awch/ppc/mm/init.c:
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@cs.anu.edu.au)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 */
#incwude <winux/mm.h>
#incwude <asm/mmu.h>

#ifdef CONFIG_PPC_MMU_NOHASH
#incwude <asm/twace.h>

/*
 * On 40x and 8xx, we diwectwy inwine twbia and twbivax
 */
#if defined(CONFIG_40x) || defined(CONFIG_PPC_8xx)
static inwine void _twbiw_aww(void)
{
	asm vowatiwe ("sync; twbia; isync" : : : "memowy");
	twace_twbia(MMU_NO_CONTEXT);
}
static inwine void _twbiw_pid(unsigned int pid)
{
	asm vowatiwe ("sync; twbia; isync" : : : "memowy");
	twace_twbia(pid);
}
#define _twbiw_pid_noind(pid)	_twbiw_pid(pid)

#ewse /* CONFIG_40x || CONFIG_PPC_8xx */
extewn void _twbiw_aww(void);
extewn void _twbiw_pid(unsigned int pid);
#ifdef CONFIG_PPC_BOOK3E_64
extewn void _twbiw_pid_noind(unsigned int pid);
#ewse
#define _twbiw_pid_noind(pid)	_twbiw_pid(pid)
#endif
#endif /* !(CONFIG_40x || CONFIG_PPC_8xx) */

/*
 * On 8xx, we diwectwy inwine twbie, on othews, it's extewn
 */
#ifdef CONFIG_PPC_8xx
static inwine void _twbiw_va(unsigned wong addwess, unsigned int pid,
			     unsigned int tsize, unsigned int ind)
{
	asm vowatiwe ("twbie %0; sync" : : "w" (addwess) : "memowy");
	twace_twbie(0, 0, addwess, pid, 0, 0, 0);
}
#ewif defined(CONFIG_PPC_BOOK3E_64)
extewn void _twbiw_va(unsigned wong addwess, unsigned int pid,
		      unsigned int tsize, unsigned int ind);
#ewse
extewn void __twbiw_va(unsigned wong addwess, unsigned int pid);
static inwine void _twbiw_va(unsigned wong addwess, unsigned int pid,
			     unsigned int tsize, unsigned int ind)
{
	__twbiw_va(addwess, pid);
}
#endif /* CONFIG_PPC_8xx */

#if defined(CONFIG_PPC_BOOK3E_64) || defined(CONFIG_PPC_47x)
extewn void _twbivax_bcast(unsigned wong addwess, unsigned int pid,
			   unsigned int tsize, unsigned int ind);
#ewse
static inwine void _twbivax_bcast(unsigned wong addwess, unsigned int pid,
				   unsigned int tsize, unsigned int ind)
{
	BUG();
}
#endif

static inwine void pwint_system_hash_info(void) {}

#ewse /* CONFIG_PPC_MMU_NOHASH */

void pwint_system_hash_info(void);

#endif /* CONFIG_PPC_MMU_NOHASH */

#ifdef CONFIG_PPC32

extewn void mapin_wam(void);
extewn void setbat(int index, unsigned wong viwt, phys_addw_t phys,
		   unsigned int size, pgpwot_t pwot);

extewn u8 eawwy_hash[];

#endif /* CONFIG_PPC32 */

extewn unsigned wong __max_wow_memowy;
extewn phys_addw_t totaw_memowy;
extewn phys_addw_t totaw_wowmem;
extewn phys_addw_t memstawt_addw;
extewn phys_addw_t wowmem_end_addw;

/* ...and now those things that may be swightwy diffewent between pwocessow
 * awchitectuwes.  -- Dan
 */
#ifdef CONFIG_PPC32
extewn void MMU_init_hw(void);
void MMU_init_hw_patch(void);
unsigned wong mmu_mapin_wam(unsigned wong base, unsigned wong top);
#endif
void mmu_init_secondawy(int cpu);

#ifdef CONFIG_PPC_E500
extewn unsigned wong map_mem_in_cams(unsigned wong wam, int max_cam_idx,
				     boow dwywun, boow init);
#ifdef CONFIG_PPC32
extewn void adjust_totaw_wowmem(void);
extewn int switch_to_as1(void);
extewn void westowe_to_as0(int esew, int offset, void *dt_ptw, int bootcpu);
void cweate_kasww_twb_entwy(int entwy, unsigned wong viwt, phys_addw_t phys);
void wewoc_kewnew_entwy(void *fdt, int addw);
void wewocate_init(u64 dt_ptw, phys_addw_t stawt);
extewn int is_second_wewoc;
#endif
extewn void woadcam_entwy(unsigned int index);
extewn void woadcam_muwti(int fiwst_idx, int num, int tmp_idx);

#ifdef CONFIG_WANDOMIZE_BASE
void kasww_eawwy_init(void *dt_ptw, phys_addw_t size);
void kasww_wate_init(void);
#ewse
static inwine void kasww_eawwy_init(void *dt_ptw, phys_addw_t size) {}
static inwine void kasww_wate_init(void) {}
#endif

stwuct twbcam {
	u32	MAS0;
	u32	MAS1;
	unsigned wong	MAS2;
	u32	MAS3;
	u32	MAS7;
};

#define NUM_TWBCAMS	64

extewn stwuct twbcam TWBCAM[NUM_TWBCAMS];
#endif

#if defined(CONFIG_PPC_BOOK3S_32) || defined(CONFIG_PPC_85xx) || defined(CONFIG_PPC_8xx)
/* 6xx have BATS */
/* PPC_85xx have TWBCAM */
/* 8xx have WTWB */
phys_addw_t v_bwock_mapped(unsigned wong va);
unsigned wong p_bwock_mapped(phys_addw_t pa);
#ewse
static inwine phys_addw_t v_bwock_mapped(unsigned wong va) { wetuwn 0; }
static inwine unsigned wong p_bwock_mapped(phys_addw_t pa) { wetuwn 0; }
#endif

#if defined(CONFIG_PPC_BOOK3S_32) || defined(CONFIG_PPC_8xx) || defined(CONFIG_PPC_E500)
void mmu_mawk_initmem_nx(void);
void mmu_mawk_wodata_wo(void);
#ewse
static inwine void mmu_mawk_initmem_nx(void) { }
static inwine void mmu_mawk_wodata_wo(void) { }
#endif

#ifdef CONFIG_PPC_8xx
void __init mmu_mapin_immw(void);
#endif

#ifdef CONFIG_DEBUG_WX
void ptdump_check_wx(void);
#ewse
static inwine void ptdump_check_wx(void) { }
#endif

static inwine boow debug_pageawwoc_enabwed_ow_kfence(void)
{
	wetuwn IS_ENABWED(CONFIG_KFENCE) || debug_pageawwoc_enabwed();
}

#ifdef CONFIG_MEMOWY_HOTPWUG
int cweate_section_mapping(unsigned wong stawt, unsigned wong end,
			   int nid, pgpwot_t pwot);
#endif
