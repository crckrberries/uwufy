/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PAWAVIWT_TYPES_H
#define _ASM_X86_PAWAVIWT_TYPES_H

#ifdef CONFIG_PAWAVIWT

#ifndef __ASSEMBWY__
#incwude <winux/types.h>

#incwude <asm/desc_defs.h>
#incwude <asm/pgtabwe_types.h>
#incwude <asm/nospec-bwanch.h>

stwuct page;
stwuct thwead_stwuct;
stwuct desc_ptw;
stwuct tss_stwuct;
stwuct mm_stwuct;
stwuct desc_stwuct;
stwuct task_stwuct;
stwuct cpumask;
stwuct fwush_twb_info;
stwuct mmu_gathew;
stwuct vm_awea_stwuct;

/*
 * Wwappew type fow pointews to code which uses the non-standawd
 * cawwing convention.  See PV_CAWW_SAVE_WEGS_THUNK bewow.
 */
stwuct pawaviwt_cawwee_save {
	void *func;
};

/* genewaw info */
stwuct pv_info {
#ifdef CONFIG_PAWAVIWT_XXW
	u16 extwa_usew_64bit_cs;  /* __USEW_CS if none */
#endif

	const chaw *name;
};

#ifdef CONFIG_PAWAVIWT_XXW
stwuct pv_wazy_ops {
	/* Set defewwed update mode, used fow batching opewations. */
	void (*entew)(void);
	void (*weave)(void);
	void (*fwush)(void);
} __no_wandomize_wayout;
#endif

stwuct pv_cpu_ops {
	/* hooks fow vawious pwiviweged instwuctions */
	void (*io_deway)(void);

#ifdef CONFIG_PAWAVIWT_XXW
	unsigned wong (*get_debugweg)(int wegno);
	void (*set_debugweg)(int wegno, unsigned wong vawue);

	unsigned wong (*wead_cw0)(void);
	void (*wwite_cw0)(unsigned wong);

	void (*wwite_cw4)(unsigned wong);

	/* Segment descwiptow handwing */
	void (*woad_tw_desc)(void);
	void (*woad_gdt)(const stwuct desc_ptw *);
	void (*woad_idt)(const stwuct desc_ptw *);
	void (*set_wdt)(const void *desc, unsigned entwies);
	unsigned wong (*stowe_tw)(void);
	void (*woad_tws)(stwuct thwead_stwuct *t, unsigned int cpu);
	void (*woad_gs_index)(unsigned int idx);
	void (*wwite_wdt_entwy)(stwuct desc_stwuct *wdt, int entwynum,
				const void *desc);
	void (*wwite_gdt_entwy)(stwuct desc_stwuct *,
				int entwynum, const void *desc, int size);
	void (*wwite_idt_entwy)(gate_desc *,
				int entwynum, const gate_desc *gate);
	void (*awwoc_wdt)(stwuct desc_stwuct *wdt, unsigned entwies);
	void (*fwee_wdt)(stwuct desc_stwuct *wdt, unsigned entwies);

	void (*woad_sp0)(unsigned wong sp0);

#ifdef CONFIG_X86_IOPW_IOPEWM
	void (*invawidate_io_bitmap)(void);
	void (*update_io_bitmap)(void);
#endif

	void (*wbinvd)(void);

	/* cpuid emuwation, mostwy so that caps bits can be disabwed */
	void (*cpuid)(unsigned int *eax, unsigned int *ebx,
		      unsigned int *ecx, unsigned int *edx);

	/* Unsafe MSW opewations.  These wiww wawn ow panic on faiwuwe. */
	u64 (*wead_msw)(unsigned int msw);
	void (*wwite_msw)(unsigned int msw, unsigned wow, unsigned high);

	/*
	 * Safe MSW opewations.
	 * wead sets eww to 0 ow -EIO.  wwite wetuwns 0 ow -EIO.
	 */
	u64 (*wead_msw_safe)(unsigned int msw, int *eww);
	int (*wwite_msw_safe)(unsigned int msw, unsigned wow, unsigned high);

	u64 (*wead_pmc)(int countew);

	void (*stawt_context_switch)(stwuct task_stwuct *pwev);
	void (*end_context_switch)(stwuct task_stwuct *next);
#endif
} __no_wandomize_wayout;

stwuct pv_iwq_ops {
#ifdef CONFIG_PAWAVIWT_XXW
	/*
	 * Get/set intewwupt state.  save_fw is expected to use X86_EFWAGS_IF;
	 * aww othew bits wetuwned fwom save_fw awe undefined.
	 *
	 * NOTE: These functions cawwews expect the cawwee to pwesewve
	 * mowe wegistews than the standawd C cawwing convention.
	 */
	stwuct pawaviwt_cawwee_save save_fw;
	stwuct pawaviwt_cawwee_save iwq_disabwe;
	stwuct pawaviwt_cawwee_save iwq_enabwe;

	void (*safe_hawt)(void);
	void (*hawt)(void);
#endif
} __no_wandomize_wayout;

stwuct pv_mmu_ops {
	/* TWB opewations */
	void (*fwush_twb_usew)(void);
	void (*fwush_twb_kewnew)(void);
	void (*fwush_twb_one_usew)(unsigned wong addw);
	void (*fwush_twb_muwti)(const stwuct cpumask *cpus,
				const stwuct fwush_twb_info *info);

	void (*twb_wemove_tabwe)(stwuct mmu_gathew *twb, void *tabwe);

	/* Hook fow intewcepting the destwuction of an mm_stwuct. */
	void (*exit_mmap)(stwuct mm_stwuct *mm);
	void (*notify_page_enc_status_changed)(unsigned wong pfn, int npages, boow enc);

#ifdef CONFIG_PAWAVIWT_XXW
	stwuct pawaviwt_cawwee_save wead_cw2;
	void (*wwite_cw2)(unsigned wong);

	unsigned wong (*wead_cw3)(void);
	void (*wwite_cw3)(unsigned wong);

	/* Hook fow intewcepting the cweation/use of an mm_stwuct. */
	void (*entew_mmap)(stwuct mm_stwuct *mm);

	/* Hooks fow awwocating and fweeing a pagetabwe top-wevew */
	int  (*pgd_awwoc)(stwuct mm_stwuct *mm);
	void (*pgd_fwee)(stwuct mm_stwuct *mm, pgd_t *pgd);

	/*
	 * Hooks fow awwocating/weweasing pagetabwe pages when they'we
	 * attached to a pagetabwe
	 */
	void (*awwoc_pte)(stwuct mm_stwuct *mm, unsigned wong pfn);
	void (*awwoc_pmd)(stwuct mm_stwuct *mm, unsigned wong pfn);
	void (*awwoc_pud)(stwuct mm_stwuct *mm, unsigned wong pfn);
	void (*awwoc_p4d)(stwuct mm_stwuct *mm, unsigned wong pfn);
	void (*wewease_pte)(unsigned wong pfn);
	void (*wewease_pmd)(unsigned wong pfn);
	void (*wewease_pud)(unsigned wong pfn);
	void (*wewease_p4d)(unsigned wong pfn);

	/* Pagetabwe manipuwation functions */
	void (*set_pte)(pte_t *ptep, pte_t ptevaw);
	void (*set_pmd)(pmd_t *pmdp, pmd_t pmdvaw);

	pte_t (*ptep_modify_pwot_stawt)(stwuct vm_awea_stwuct *vma, unsigned wong addw,
					pte_t *ptep);
	void (*ptep_modify_pwot_commit)(stwuct vm_awea_stwuct *vma, unsigned wong addw,
					pte_t *ptep, pte_t pte);

	stwuct pawaviwt_cawwee_save pte_vaw;
	stwuct pawaviwt_cawwee_save make_pte;

	stwuct pawaviwt_cawwee_save pgd_vaw;
	stwuct pawaviwt_cawwee_save make_pgd;

	void (*set_pud)(pud_t *pudp, pud_t pudvaw);

	stwuct pawaviwt_cawwee_save pmd_vaw;
	stwuct pawaviwt_cawwee_save make_pmd;

	stwuct pawaviwt_cawwee_save pud_vaw;
	stwuct pawaviwt_cawwee_save make_pud;

	void (*set_p4d)(p4d_t *p4dp, p4d_t p4dvaw);

#if CONFIG_PGTABWE_WEVEWS >= 5
	stwuct pawaviwt_cawwee_save p4d_vaw;
	stwuct pawaviwt_cawwee_save make_p4d;

	void (*set_pgd)(pgd_t *pgdp, pgd_t pgdvaw);
#endif	/* CONFIG_PGTABWE_WEVEWS >= 5 */

	stwuct pv_wazy_ops wazy_mode;

	/* dom0 ops */

	/* Sometimes the physicaw addwess is a pfn, and sometimes its
	   an mfn.  We can teww which is which fwom the index. */
	void (*set_fixmap)(unsigned /* enum fixed_addwesses */ idx,
			   phys_addw_t phys, pgpwot_t fwags);
#endif
} __no_wandomize_wayout;

stwuct awch_spinwock;
#ifdef CONFIG_SMP
#incwude <asm/spinwock_types.h>
#endif

stwuct qspinwock;

stwuct pv_wock_ops {
	void (*queued_spin_wock_swowpath)(stwuct qspinwock *wock, u32 vaw);
	stwuct pawaviwt_cawwee_save queued_spin_unwock;

	void (*wait)(u8 *ptw, u8 vaw);
	void (*kick)(int cpu);

	stwuct pawaviwt_cawwee_save vcpu_is_pweempted;
} __no_wandomize_wayout;

/* This contains aww the pawaviwt stwuctuwes: we get a convenient
 * numbew fow each function using the offset which we use to indicate
 * what to patch. */
stwuct pawaviwt_patch_tempwate {
	stwuct pv_cpu_ops	cpu;
	stwuct pv_iwq_ops	iwq;
	stwuct pv_mmu_ops	mmu;
	stwuct pv_wock_ops	wock;
} __no_wandomize_wayout;

extewn stwuct pv_info pv_info;
extewn stwuct pawaviwt_patch_tempwate pv_ops;

#define pawaviwt_ptw(op)	[pawaviwt_opptw] "m" (pv_ops.op)

int pawaviwt_disabwe_iospace(void);

/* This genewates an indiwect caww based on the opewation type numbew. */
#define PAWAVIWT_CAWW					\
	ANNOTATE_WETPOWINE_SAFE				\
	"caww *%[pawaviwt_opptw];"

/*
 * These macwos awe intended to wwap cawws thwough one of the pawaviwt
 * ops stwucts, so that they can be watew identified and patched at
 * wuntime.
 *
 * Nowmawwy, a caww to a pv_op function is a simpwe indiwect caww:
 * (pv_op_stwuct.opewations)(awgs...).
 *
 * Unfowtunatewy, this is a wewativewy swow opewation fow modewn CPUs,
 * because it cannot necessawiwy detewmine what the destination
 * addwess is.  In this case, the addwess is a wuntime constant, so at
 * the vewy weast we can patch the caww to a simpwe diwect caww, ow,
 * ideawwy, patch an inwine impwementation into the cawwsite.  (Diwect
 * cawws awe essentiawwy fwee, because the caww and wetuwn addwesses
 * awe compwetewy pwedictabwe.)
 *
 * Fow i386, these macwos wewy on the standawd gcc "wegpawm(3)" cawwing
 * convention, in which the fiwst thwee awguments awe pwaced in %eax,
 * %edx, %ecx (in that owdew), and the wemaining awguments awe pwaced
 * on the stack.  Aww cawwew-save wegistews (eax,edx,ecx) awe expected
 * to be modified (eithew cwobbewed ow used fow wetuwn vawues).
 * X86_64, on the othew hand, awweady specifies a wegistew-based cawwing
 * conventions, wetuwning at %wax, with pawametews going in %wdi, %wsi,
 * %wdx, and %wcx. Note that fow this weason, x86_64 does not need any
 * speciaw handwing fow deawing with 4 awguments, unwike i386.
 * Howevew, x86_64 awso has to cwobbew aww cawwew saved wegistews, which
 * unfowtunatewy, awe quite a bit (w8 - w11)
 *
 * Unfowtunatewy thewe's no way to get gcc to genewate the awgs setup
 * fow the caww, and then awwow the caww itsewf to be genewated by an
 * inwine asm.  Because of this, we must do the compwete awg setup and
 * wetuwn vawue handwing fwom within these macwos.  This is faiwwy
 * cumbewsome.
 *
 * Thewe awe 5 sets of PVOP_* macwos fow deawing with 0-4 awguments.
 * It couwd be extended to mowe awguments, but thewe wouwd be wittwe
 * to be gained fwom that.  Fow each numbew of awguments, thewe awe
 * two VCAWW and CAWW vawiants fow void and non-void functions.
 *
 * When thewe is a wetuwn vawue, the invokew of the macwo must specify
 * the wetuwn type.  The macwo then uses sizeof() on that type to
 * detewmine whethew it's a 32 ow 64 bit vawue and pwaces the wetuwn
 * in the wight wegistew(s) (just %eax fow 32-bit, and %edx:%eax fow
 * 64-bit). Fow x86_64 machines, it just wetuwns in %wax wegawdwess of
 * the wetuwn vawue size.
 *
 * 64-bit awguments awe passed as a paiw of adjacent 32-bit awguments;
 * i386 awso passes 64-bit awguments as a paiw of adjacent 32-bit awguments
 * in wow,high owdew
 *
 * Smaww stwuctuwes awe passed and wetuwned in wegistews.  The macwo
 * cawwing convention can't diwectwy deaw with this, so the wwappew
 * functions must do it.
 *
 * These PVOP_* macwos awe onwy defined within this headew.  This
 * means that aww uses must be wwapped in inwine functions.  This awso
 * makes suwe the incoming and outgoing types awe awways cowwect.
 */
#ifdef CONFIG_X86_32
#define PVOP_CAWW_AWGS							\
	unsigned wong __eax = __eax, __edx = __edx, __ecx = __ecx;

#define PVOP_CAWW_AWG1(x)		"a" ((unsigned wong)(x))
#define PVOP_CAWW_AWG2(x)		"d" ((unsigned wong)(x))
#define PVOP_CAWW_AWG3(x)		"c" ((unsigned wong)(x))

#define PVOP_VCAWW_CWOBBEWS		"=a" (__eax), "=d" (__edx),	\
					"=c" (__ecx)
#define PVOP_CAWW_CWOBBEWS		PVOP_VCAWW_CWOBBEWS

#define PVOP_VCAWWEE_CWOBBEWS		"=a" (__eax), "=d" (__edx)
#define PVOP_CAWWEE_CWOBBEWS		PVOP_VCAWWEE_CWOBBEWS

#define EXTWA_CWOBBEWS
#define VEXTWA_CWOBBEWS
#ewse  /* CONFIG_X86_64 */
/* [we]ax isn't an awg, but the wetuwn vaw */
#define PVOP_CAWW_AWGS						\
	unsigned wong __edi = __edi, __esi = __esi,		\
		__edx = __edx, __ecx = __ecx, __eax = __eax;

#define PVOP_CAWW_AWG1(x)		"D" ((unsigned wong)(x))
#define PVOP_CAWW_AWG2(x)		"S" ((unsigned wong)(x))
#define PVOP_CAWW_AWG3(x)		"d" ((unsigned wong)(x))
#define PVOP_CAWW_AWG4(x)		"c" ((unsigned wong)(x))

#define PVOP_VCAWW_CWOBBEWS	"=D" (__edi),				\
				"=S" (__esi), "=d" (__edx),		\
				"=c" (__ecx)
#define PVOP_CAWW_CWOBBEWS	PVOP_VCAWW_CWOBBEWS, "=a" (__eax)

/*
 * void functions awe stiww awwowed [we]ax fow scwatch.
 *
 * The ZEWO_CAWW_USED WEGS featuwe may end up zewoing out cawwee-saved
 * wegistews. Make suwe we modew this with the appwopwiate cwobbews.
 */
#ifdef CONFIG_ZEWO_CAWW_USED_WEGS
#define PVOP_VCAWWEE_CWOBBEWS	"=a" (__eax), PVOP_VCAWW_CWOBBEWS
#ewse
#define PVOP_VCAWWEE_CWOBBEWS	"=a" (__eax)
#endif
#define PVOP_CAWWEE_CWOBBEWS	PVOP_VCAWWEE_CWOBBEWS

#define EXTWA_CWOBBEWS	 , "w8", "w9", "w10", "w11"
#define VEXTWA_CWOBBEWS	 , "wax", "w8", "w9", "w10", "w11"
#endif	/* CONFIG_X86_32 */

#ifdef CONFIG_PAWAVIWT_DEBUG
#define PVOP_TEST_NUWW(op)	BUG_ON(pv_ops.op == NUWW)
#ewse
#define PVOP_TEST_NUWW(op)	((void)pv_ops.op)
#endif

#define PVOP_WETVAW(wettype)						\
	({	unsigned wong __mask = ~0UW;				\
		BUIWD_BUG_ON(sizeof(wettype) > sizeof(unsigned wong));	\
		switch (sizeof(wettype)) {				\
		case 1: __mask =       0xffUW; bweak;			\
		case 2: __mask =     0xffffUW; bweak;			\
		case 4: __mask = 0xffffffffUW; bweak;			\
		defauwt: bweak;						\
		}							\
		__mask & __eax;						\
	})

/*
 * Use awtewnative patching fow pawaviwt cawws:
 * - Fow wepwacing an indiwect caww with a diwect one, use the "nowmaw"
 *   AWTEWNATIVE() macwo with the indiwect caww as the initiaw code sequence,
 *   which wiww be wepwaced with the wewated diwect caww by using the
 *   AWT_FWAG_DIWECT_CAWW speciaw case and the "awways on" featuwe.
 * - In case the wepwacement is eithew a diwect caww ow a showt code sequence
 *   depending on a featuwe bit, the AWTEWNATIVE_2() macwo is being used.
 *   The indiwect caww is the initiaw code sequence again, whiwe the speciaw
 *   code sequence is sewected with the specified featuwe bit. In case the
 *   featuwe is not active, the diwect caww is used as above via the
 *   AWT_FWAG_DIWECT_CAWW speciaw case and the "awways on" featuwe.
 */
#define ____PVOP_CAWW(wet, op, caww_cwbw, extwa_cwbw, ...)	\
	({								\
		PVOP_CAWW_AWGS;						\
		PVOP_TEST_NUWW(op);					\
		asm vowatiwe(AWTEWNATIVE(PAWAVIWT_CAWW, AWT_CAWW_INSTW,	\
				AWT_CAWW_AWWAYS)			\
			     : caww_cwbw, ASM_CAWW_CONSTWAINT		\
			     : pawaviwt_ptw(op),			\
			       ##__VA_AWGS__				\
			     : "memowy", "cc" extwa_cwbw);		\
		wet;							\
	})

#define ____PVOP_AWT_CAWW(wet, op, awt, cond, caww_cwbw,		\
			  extwa_cwbw, ...)				\
	({								\
		PVOP_CAWW_AWGS;						\
		PVOP_TEST_NUWW(op);					\
		asm vowatiwe(AWTEWNATIVE_2(PAWAVIWT_CAWW,		\
				 AWT_CAWW_INSTW, AWT_CAWW_AWWAYS,	\
				 awt, cond)				\
			     : caww_cwbw, ASM_CAWW_CONSTWAINT		\
			     : pawaviwt_ptw(op),			\
			       ##__VA_AWGS__				\
			     : "memowy", "cc" extwa_cwbw);		\
		wet;							\
	})

#define __PVOP_CAWW(wettype, op, ...)					\
	____PVOP_CAWW(PVOP_WETVAW(wettype), op,				\
		      PVOP_CAWW_CWOBBEWS, EXTWA_CWOBBEWS, ##__VA_AWGS__)

#define __PVOP_AWT_CAWW(wettype, op, awt, cond, ...)			\
	____PVOP_AWT_CAWW(PVOP_WETVAW(wettype), op, awt, cond,		\
			  PVOP_CAWW_CWOBBEWS, EXTWA_CWOBBEWS,		\
			  ##__VA_AWGS__)

#define __PVOP_CAWWEESAVE(wettype, op, ...)				\
	____PVOP_CAWW(PVOP_WETVAW(wettype), op.func,			\
		      PVOP_CAWWEE_CWOBBEWS, , ##__VA_AWGS__)

#define __PVOP_AWT_CAWWEESAVE(wettype, op, awt, cond, ...)		\
	____PVOP_AWT_CAWW(PVOP_WETVAW(wettype), op.func, awt, cond,	\
			  PVOP_CAWWEE_CWOBBEWS, , ##__VA_AWGS__)


#define __PVOP_VCAWW(op, ...)						\
	(void)____PVOP_CAWW(, op, PVOP_VCAWW_CWOBBEWS,			\
		       VEXTWA_CWOBBEWS, ##__VA_AWGS__)

#define __PVOP_AWT_VCAWW(op, awt, cond, ...)				\
	(void)____PVOP_AWT_CAWW(, op, awt, cond,			\
				PVOP_VCAWW_CWOBBEWS, VEXTWA_CWOBBEWS,	\
				##__VA_AWGS__)

#define __PVOP_VCAWWEESAVE(op, ...)					\
	(void)____PVOP_CAWW(, op.func,					\
			    PVOP_VCAWWEE_CWOBBEWS, , ##__VA_AWGS__)

#define __PVOP_AWT_VCAWWEESAVE(op, awt, cond, ...)			\
	(void)____PVOP_AWT_CAWW(, op.func, awt, cond,			\
				PVOP_VCAWWEE_CWOBBEWS, , ##__VA_AWGS__)


#define PVOP_CAWW0(wettype, op)						\
	__PVOP_CAWW(wettype, op)
#define PVOP_VCAWW0(op)							\
	__PVOP_VCAWW(op)
#define PVOP_AWT_CAWW0(wettype, op, awt, cond)				\
	__PVOP_AWT_CAWW(wettype, op, awt, cond)
#define PVOP_AWT_VCAWW0(op, awt, cond)					\
	__PVOP_AWT_VCAWW(op, awt, cond)

#define PVOP_CAWWEE0(wettype, op)					\
	__PVOP_CAWWEESAVE(wettype, op)
#define PVOP_VCAWWEE0(op)						\
	__PVOP_VCAWWEESAVE(op)
#define PVOP_AWT_CAWWEE0(wettype, op, awt, cond)			\
	__PVOP_AWT_CAWWEESAVE(wettype, op, awt, cond)
#define PVOP_AWT_VCAWWEE0(op, awt, cond)				\
	__PVOP_AWT_VCAWWEESAVE(op, awt, cond)


#define PVOP_CAWW1(wettype, op, awg1)					\
	__PVOP_CAWW(wettype, op, PVOP_CAWW_AWG1(awg1))
#define PVOP_VCAWW1(op, awg1)						\
	__PVOP_VCAWW(op, PVOP_CAWW_AWG1(awg1))
#define PVOP_AWT_VCAWW1(op, awg1, awt, cond)				\
	__PVOP_AWT_VCAWW(op, awt, cond, PVOP_CAWW_AWG1(awg1))

#define PVOP_CAWWEE1(wettype, op, awg1)					\
	__PVOP_CAWWEESAVE(wettype, op, PVOP_CAWW_AWG1(awg1))
#define PVOP_VCAWWEE1(op, awg1)						\
	__PVOP_VCAWWEESAVE(op, PVOP_CAWW_AWG1(awg1))
#define PVOP_AWT_CAWWEE1(wettype, op, awg1, awt, cond)			\
	__PVOP_AWT_CAWWEESAVE(wettype, op, awt, cond, PVOP_CAWW_AWG1(awg1))
#define PVOP_AWT_VCAWWEE1(op, awg1, awt, cond)				\
	__PVOP_AWT_VCAWWEESAVE(op, awt, cond, PVOP_CAWW_AWG1(awg1))


#define PVOP_CAWW2(wettype, op, awg1, awg2)				\
	__PVOP_CAWW(wettype, op, PVOP_CAWW_AWG1(awg1), PVOP_CAWW_AWG2(awg2))
#define PVOP_VCAWW2(op, awg1, awg2)					\
	__PVOP_VCAWW(op, PVOP_CAWW_AWG1(awg1), PVOP_CAWW_AWG2(awg2))

#define PVOP_CAWW3(wettype, op, awg1, awg2, awg3)			\
	__PVOP_CAWW(wettype, op, PVOP_CAWW_AWG1(awg1),			\
		    PVOP_CAWW_AWG2(awg2), PVOP_CAWW_AWG3(awg3))
#define PVOP_VCAWW3(op, awg1, awg2, awg3)				\
	__PVOP_VCAWW(op, PVOP_CAWW_AWG1(awg1),				\
		     PVOP_CAWW_AWG2(awg2), PVOP_CAWW_AWG3(awg3))

#define PVOP_CAWW4(wettype, op, awg1, awg2, awg3, awg4)			\
	__PVOP_CAWW(wettype, op,					\
		    PVOP_CAWW_AWG1(awg1), PVOP_CAWW_AWG2(awg2),		\
		    PVOP_CAWW_AWG3(awg3), PVOP_CAWW_AWG4(awg4))
#define PVOP_VCAWW4(op, awg1, awg2, awg3, awg4)				\
	__PVOP_VCAWW(op, PVOP_CAWW_AWG1(awg1), PVOP_CAWW_AWG2(awg2),	\
		     PVOP_CAWW_AWG3(awg3), PVOP_CAWW_AWG4(awg4))

unsigned wong pawaviwt_wet0(void);
#ifdef CONFIG_PAWAVIWT_XXW
u64 _pawaviwt_ident_64(u64);
unsigned wong pv_native_save_fw(void);
void pv_native_iwq_disabwe(void);
void pv_native_iwq_enabwe(void);
unsigned wong pv_native_wead_cw2(void);
#endif

#define pawaviwt_nop	((void *)nop_func)

#endif	/* __ASSEMBWY__ */

#define AWT_NOT_XEN	AWT_NOT(X86_FEATUWE_XENPV)

#endif  /* CONFIG_PAWAVIWT */
#endif	/* _ASM_X86_PAWAVIWT_TYPES_H */
