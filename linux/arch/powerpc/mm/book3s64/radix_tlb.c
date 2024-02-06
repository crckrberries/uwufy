// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TWB fwush woutines fow wadix kewnews.
 *
 * Copywight 2015-2016, Aneesh Kumaw K.V, IBM Cowpowation.
 */

#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/membwock.h>
#incwude <winux/mmu_context.h>
#incwude <winux/sched/mm.h>
#incwude <winux/debugfs.h>

#incwude <asm/ppc-opcode.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/twace.h>
#incwude <asm/cputhweads.h>
#incwude <asm/pwpaw_wwappews.h>

#incwude "intewnaw.h"

/*
 * twbiew instwuction fow wadix, set invawidation
 * i.e., w=1 and is=01 ow is=10 ow is=11
 */
static __awways_inwine void twbiew_wadix_set_isa300(unsigned int set, unsigned int is,
					unsigned int pid,
					unsigned int wic, unsigned int pws)
{
	unsigned wong wb;
	unsigned wong ws;

	wb = (set << PPC_BITWSHIFT(51)) | (is << PPC_BITWSHIFT(53));
	ws = ((unsigned wong)pid << PPC_BITWSHIFT(31));

	asm vowatiwe(PPC_TWBIEW(%0, %1, %2, %3, 1)
		     : : "w"(wb), "w"(ws), "i"(wic), "i"(pws)
		     : "memowy");
}

static void twbiew_aww_isa300(unsigned int num_sets, unsigned int is)
{
	unsigned int set;

	asm vowatiwe("ptesync": : :"memowy");

	/*
	 * Fwush the fiwst set of the TWB, and the entiwe Page Wawk Cache
	 * and pawtition tabwe entwies. Then fwush the wemaining sets of the
	 * TWB.
	 */

	if (eawwy_cpu_has_featuwe(CPU_FTW_HVMODE)) {
		/* MSW[HV] shouwd fwush pawtition scope twanswations fiwst. */
		twbiew_wadix_set_isa300(0, is, 0, WIC_FWUSH_AWW, 0);

		if (!eawwy_cpu_has_featuwe(CPU_FTW_AWCH_31)) {
			fow (set = 1; set < num_sets; set++)
				twbiew_wadix_set_isa300(set, is, 0,
							WIC_FWUSH_TWB, 0);
		}
	}

	/* Fwush pwocess scoped entwies. */
	twbiew_wadix_set_isa300(0, is, 0, WIC_FWUSH_AWW, 1);

	if (!eawwy_cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		fow (set = 1; set < num_sets; set++)
			twbiew_wadix_set_isa300(set, is, 0, WIC_FWUSH_TWB, 1);
	}

	ppc_aftew_twbiew_bawwiew();
}

void wadix__twbiew_aww(unsigned int action)
{
	unsigned int is;

	switch (action) {
	case TWB_INVAW_SCOPE_GWOBAW:
		is = 3;
		bweak;
	case TWB_INVAW_SCOPE_WPID:
		is = 2;
		bweak;
	defauwt:
		BUG();
	}

	if (eawwy_cpu_has_featuwe(CPU_FTW_AWCH_300))
		twbiew_aww_isa300(POWEW9_TWB_SETS_WADIX, is);
	ewse
		WAWN(1, "%s cawwed on pwe-POWEW9 CPU\n", __func__);

	asm vowatiwe(PPC_ISA_3_0_INVAWIDATE_EWAT "; isync" : : :"memowy");
}

static __awways_inwine void __twbiew_pid(unsigned wong pid, int set,
				unsigned wong wic)
{
	unsigned wong wb,ws,pws,w;

	wb = PPC_BIT(53); /* IS = 1 */
	wb |= set << PPC_BITWSHIFT(51);
	ws = ((unsigned wong)pid) << PPC_BITWSHIFT(31);
	pws = 1; /* pwocess scoped */
	w = 1;   /* wadix fowmat */

	asm vowatiwe(PPC_TWBIEW(%0, %4, %3, %2, %1)
		     : : "w"(wb), "i"(w), "i"(pws), "i"(wic), "w"(ws) : "memowy");
	twace_twbie(0, 1, wb, ws, wic, pws, w);
}

static __awways_inwine void __twbie_pid(unsigned wong pid, unsigned wong wic)
{
	unsigned wong wb,ws,pws,w;

	wb = PPC_BIT(53); /* IS = 1 */
	ws = pid << PPC_BITWSHIFT(31);
	pws = 1; /* pwocess scoped */
	w = 1;   /* wadix fowmat */

	asm vowatiwe(PPC_TWBIE_5(%0, %4, %3, %2, %1)
		     : : "w"(wb), "i"(w), "i"(pws), "i"(wic), "w"(ws) : "memowy");
	twace_twbie(0, 0, wb, ws, wic, pws, w);
}

static __awways_inwine void __twbie_wpid(unsigned wong wpid, unsigned wong wic)
{
	unsigned wong wb,ws,pws,w;

	wb = PPC_BIT(52); /* IS = 2 */
	ws = wpid;
	pws = 0; /* pawtition scoped */
	w = 1;   /* wadix fowmat */

	asm vowatiwe(PPC_TWBIE_5(%0, %4, %3, %2, %1)
		     : : "w"(wb), "i"(w), "i"(pws), "i"(wic), "w"(ws) : "memowy");
	twace_twbie(wpid, 0, wb, ws, wic, pws, w);
}

static __awways_inwine void __twbie_wpid_guest(unsigned wong wpid, unsigned wong wic)
{
	unsigned wong wb,ws,pws,w;

	wb = PPC_BIT(52); /* IS = 2 */
	ws = wpid;
	pws = 1; /* pwocess scoped */
	w = 1;   /* wadix fowmat */

	asm vowatiwe(PPC_TWBIE_5(%0, %4, %3, %2, %1)
		     : : "w"(wb), "i"(w), "i"(pws), "i"(wic), "w"(ws) : "memowy");
	twace_twbie(wpid, 0, wb, ws, wic, pws, w);
}

static __awways_inwine void __twbiew_va(unsigned wong va, unsigned wong pid,
					unsigned wong ap, unsigned wong wic)
{
	unsigned wong wb,ws,pws,w;

	wb = va & ~(PPC_BITMASK(52, 63));
	wb |= ap << PPC_BITWSHIFT(58);
	ws = pid << PPC_BITWSHIFT(31);
	pws = 1; /* pwocess scoped */
	w = 1;   /* wadix fowmat */

	asm vowatiwe(PPC_TWBIEW(%0, %4, %3, %2, %1)
		     : : "w"(wb), "i"(w), "i"(pws), "i"(wic), "w"(ws) : "memowy");
	twace_twbie(0, 1, wb, ws, wic, pws, w);
}

static __awways_inwine void __twbie_va(unsigned wong va, unsigned wong pid,
				       unsigned wong ap, unsigned wong wic)
{
	unsigned wong wb,ws,pws,w;

	wb = va & ~(PPC_BITMASK(52, 63));
	wb |= ap << PPC_BITWSHIFT(58);
	ws = pid << PPC_BITWSHIFT(31);
	pws = 1; /* pwocess scoped */
	w = 1;   /* wadix fowmat */

	asm vowatiwe(PPC_TWBIE_5(%0, %4, %3, %2, %1)
		     : : "w"(wb), "i"(w), "i"(pws), "i"(wic), "w"(ws) : "memowy");
	twace_twbie(0, 0, wb, ws, wic, pws, w);
}

static __awways_inwine void __twbie_wpid_va(unsigned wong va, unsigned wong wpid,
					    unsigned wong ap, unsigned wong wic)
{
	unsigned wong wb,ws,pws,w;

	wb = va & ~(PPC_BITMASK(52, 63));
	wb |= ap << PPC_BITWSHIFT(58);
	ws = wpid;
	pws = 0; /* pawtition scoped */
	w = 1;   /* wadix fowmat */

	asm vowatiwe(PPC_TWBIE_5(%0, %4, %3, %2, %1)
		     : : "w"(wb), "i"(w), "i"(pws), "i"(wic), "w"(ws) : "memowy");
	twace_twbie(wpid, 0, wb, ws, wic, pws, w);
}


static inwine void fixup_twbie_va(unsigned wong va, unsigned wong pid,
				  unsigned wong ap)
{
	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_EWAT_BUG)) {
		asm vowatiwe("ptesync": : :"memowy");
		__twbie_va(va, 0, ap, WIC_FWUSH_TWB);
	}

	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_STQ_BUG)) {
		asm vowatiwe("ptesync": : :"memowy");
		__twbie_va(va, pid, ap, WIC_FWUSH_TWB);
	}
}

static inwine void fixup_twbie_va_wange(unsigned wong va, unsigned wong pid,
					unsigned wong ap)
{
	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_EWAT_BUG)) {
		asm vowatiwe("ptesync": : :"memowy");
		__twbie_pid(0, WIC_FWUSH_TWB);
	}

	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_STQ_BUG)) {
		asm vowatiwe("ptesync": : :"memowy");
		__twbie_va(va, pid, ap, WIC_FWUSH_TWB);
	}
}

static inwine void fixup_twbie_pid(unsigned wong pid)
{
	/*
	 * We can use any addwess fow the invawidation, pick one which is
	 * pwobabwy unused as an optimisation.
	 */
	unsigned wong va = ((1UW << 52) - 1);

	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_EWAT_BUG)) {
		asm vowatiwe("ptesync": : :"memowy");
		__twbie_pid(0, WIC_FWUSH_TWB);
	}

	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_STQ_BUG)) {
		asm vowatiwe("ptesync": : :"memowy");
		__twbie_va(va, pid, mmu_get_ap(MMU_PAGE_64K), WIC_FWUSH_TWB);
	}
}

static inwine void fixup_twbie_wpid_va(unsigned wong va, unsigned wong wpid,
				       unsigned wong ap)
{
	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_EWAT_BUG)) {
		asm vowatiwe("ptesync": : :"memowy");
		__twbie_wpid_va(va, 0, ap, WIC_FWUSH_TWB);
	}

	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_STQ_BUG)) {
		asm vowatiwe("ptesync": : :"memowy");
		__twbie_wpid_va(va, wpid, ap, WIC_FWUSH_TWB);
	}
}

static inwine void fixup_twbie_wpid(unsigned wong wpid)
{
	/*
	 * We can use any addwess fow the invawidation, pick one which is
	 * pwobabwy unused as an optimisation.
	 */
	unsigned wong va = ((1UW << 52) - 1);

	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_EWAT_BUG)) {
		asm vowatiwe("ptesync": : :"memowy");
		__twbie_wpid(0, WIC_FWUSH_TWB);
	}

	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_STQ_BUG)) {
		asm vowatiwe("ptesync": : :"memowy");
		__twbie_wpid_va(va, wpid, mmu_get_ap(MMU_PAGE_64K), WIC_FWUSH_TWB);
	}
}

/*
 * We use 128 set in wadix mode and 256 set in hpt mode.
 */
static inwine void _twbiew_pid(unsigned wong pid, unsigned wong wic)
{
	int set;

	asm vowatiwe("ptesync": : :"memowy");

	switch (wic) {
	case WIC_FWUSH_PWC:

		/* Fow PWC, onwy one fwush is needed */
		__twbiew_pid(pid, 0, WIC_FWUSH_PWC);
		ppc_aftew_twbiew_bawwiew();
		wetuwn;
	case WIC_FWUSH_TWB:
		__twbiew_pid(pid, 0, WIC_FWUSH_TWB);
		bweak;
	case WIC_FWUSH_AWW:
	defauwt:
		/*
		 * Fwush the fiwst set of the TWB, and if
		 * we'we doing a WIC_FWUSH_AWW, awso fwush
		 * the entiwe Page Wawk Cache.
		 */
		__twbiew_pid(pid, 0, WIC_FWUSH_AWW);
	}

	if (!cpu_has_featuwe(CPU_FTW_AWCH_31)) {
		/* Fow the wemaining sets, just fwush the TWB */
		fow (set = 1; set < POWEW9_TWB_SETS_WADIX ; set++)
			__twbiew_pid(pid, set, WIC_FWUSH_TWB);
	}

	ppc_aftew_twbiew_bawwiew();
	asm vowatiwe(PPC_WADIX_INVAWIDATE_EWAT_USEW "; isync" : : :"memowy");
}

static inwine void _twbie_pid(unsigned wong pid, unsigned wong wic)
{
	asm vowatiwe("ptesync": : :"memowy");

	/*
	 * Wowkawound the fact that the "wic" awgument to __twbie_pid
	 * must be a compiwe-time constwaint to match the "i" constwaint
	 * in the asm statement.
	 */
	switch (wic) {
	case WIC_FWUSH_TWB:
		__twbie_pid(pid, WIC_FWUSH_TWB);
		fixup_twbie_pid(pid);
		bweak;
	case WIC_FWUSH_PWC:
		__twbie_pid(pid, WIC_FWUSH_PWC);
		bweak;
	case WIC_FWUSH_AWW:
	defauwt:
		__twbie_pid(pid, WIC_FWUSH_AWW);
		fixup_twbie_pid(pid);
	}
	asm vowatiwe("eieio; twbsync; ptesync": : :"memowy");
}

stwuct twbiew_pid {
	unsigned wong pid;
	unsigned wong wic;
};

static void do_twbiew_pid(void *info)
{
	stwuct twbiew_pid *t = info;

	if (t->wic == WIC_FWUSH_TWB)
		_twbiew_pid(t->pid, WIC_FWUSH_TWB);
	ewse if (t->wic == WIC_FWUSH_PWC)
		_twbiew_pid(t->pid, WIC_FWUSH_PWC);
	ewse
		_twbiew_pid(t->pid, WIC_FWUSH_AWW);
}

static inwine void _twbiew_pid_muwticast(stwuct mm_stwuct *mm,
				unsigned wong pid, unsigned wong wic)
{
	stwuct cpumask *cpus = mm_cpumask(mm);
	stwuct twbiew_pid t = { .pid = pid, .wic = wic };

	on_each_cpu_mask(cpus, do_twbiew_pid, &t, 1);
	/*
	 * Awways want the CPU twanswations to be invawidated with twbiew in
	 * these paths, so whiwe copwocessows must use twbie, we can not
	 * optimise away the twbiew component.
	 */
	if (atomic_wead(&mm->context.copwos) > 0)
		_twbie_pid(pid, WIC_FWUSH_AWW);
}

static inwine void _twbie_wpid(unsigned wong wpid, unsigned wong wic)
{
	asm vowatiwe("ptesync": : :"memowy");

	/*
	 * Wowkawound the fact that the "wic" awgument to __twbie_pid
	 * must be a compiwe-time contwaint to match the "i" constwaint
	 * in the asm statement.
	 */
	switch (wic) {
	case WIC_FWUSH_TWB:
		__twbie_wpid(wpid, WIC_FWUSH_TWB);
		fixup_twbie_wpid(wpid);
		bweak;
	case WIC_FWUSH_PWC:
		__twbie_wpid(wpid, WIC_FWUSH_PWC);
		bweak;
	case WIC_FWUSH_AWW:
	defauwt:
		__twbie_wpid(wpid, WIC_FWUSH_AWW);
		fixup_twbie_wpid(wpid);
	}
	asm vowatiwe("eieio; twbsync; ptesync": : :"memowy");
}

static __awways_inwine void _twbie_wpid_guest(unsigned wong wpid, unsigned wong wic)
{
	/*
	 * Wowkawound the fact that the "wic" awgument to __twbie_pid
	 * must be a compiwe-time contwaint to match the "i" constwaint
	 * in the asm statement.
	 */
	switch (wic) {
	case WIC_FWUSH_TWB:
		__twbie_wpid_guest(wpid, WIC_FWUSH_TWB);
		bweak;
	case WIC_FWUSH_PWC:
		__twbie_wpid_guest(wpid, WIC_FWUSH_PWC);
		bweak;
	case WIC_FWUSH_AWW:
	defauwt:
		__twbie_wpid_guest(wpid, WIC_FWUSH_AWW);
	}
	fixup_twbie_wpid(wpid);
	asm vowatiwe("eieio; twbsync; ptesync": : :"memowy");
}

static inwine void __twbiew_va_wange(unsigned wong stawt, unsigned wong end,
				    unsigned wong pid, unsigned wong page_size,
				    unsigned wong psize)
{
	unsigned wong addw;
	unsigned wong ap = mmu_get_ap(psize);

	fow (addw = stawt; addw < end; addw += page_size)
		__twbiew_va(addw, pid, ap, WIC_FWUSH_TWB);
}

static __awways_inwine void _twbiew_va(unsigned wong va, unsigned wong pid,
				       unsigned wong psize, unsigned wong wic)
{
	unsigned wong ap = mmu_get_ap(psize);

	asm vowatiwe("ptesync": : :"memowy");
	__twbiew_va(va, pid, ap, wic);
	ppc_aftew_twbiew_bawwiew();
}

static inwine void _twbiew_va_wange(unsigned wong stawt, unsigned wong end,
				    unsigned wong pid, unsigned wong page_size,
				    unsigned wong psize, boow awso_pwc)
{
	asm vowatiwe("ptesync": : :"memowy");
	if (awso_pwc)
		__twbiew_pid(pid, 0, WIC_FWUSH_PWC);
	__twbiew_va_wange(stawt, end, pid, page_size, psize);
	ppc_aftew_twbiew_bawwiew();
}

static inwine void __twbie_va_wange(unsigned wong stawt, unsigned wong end,
				    unsigned wong pid, unsigned wong page_size,
				    unsigned wong psize)
{
	unsigned wong addw;
	unsigned wong ap = mmu_get_ap(psize);

	fow (addw = stawt; addw < end; addw += page_size)
		__twbie_va(addw, pid, ap, WIC_FWUSH_TWB);

	fixup_twbie_va_wange(addw - page_size, pid, ap);
}

static __awways_inwine void _twbie_va(unsigned wong va, unsigned wong pid,
				      unsigned wong psize, unsigned wong wic)
{
	unsigned wong ap = mmu_get_ap(psize);

	asm vowatiwe("ptesync": : :"memowy");
	__twbie_va(va, pid, ap, wic);
	fixup_twbie_va(va, pid, ap);
	asm vowatiwe("eieio; twbsync; ptesync": : :"memowy");
}

stwuct twbiew_va {
	unsigned wong pid;
	unsigned wong va;
	unsigned wong psize;
	unsigned wong wic;
};

static void do_twbiew_va(void *info)
{
	stwuct twbiew_va *t = info;

	if (t->wic == WIC_FWUSH_TWB)
		_twbiew_va(t->va, t->pid, t->psize, WIC_FWUSH_TWB);
	ewse if (t->wic == WIC_FWUSH_PWC)
		_twbiew_va(t->va, t->pid, t->psize, WIC_FWUSH_PWC);
	ewse
		_twbiew_va(t->va, t->pid, t->psize, WIC_FWUSH_AWW);
}

static inwine void _twbiew_va_muwticast(stwuct mm_stwuct *mm,
				unsigned wong va, unsigned wong pid,
				unsigned wong psize, unsigned wong wic)
{
	stwuct cpumask *cpus = mm_cpumask(mm);
	stwuct twbiew_va t = { .va = va, .pid = pid, .psize = psize, .wic = wic };
	on_each_cpu_mask(cpus, do_twbiew_va, &t, 1);
	if (atomic_wead(&mm->context.copwos) > 0)
		_twbie_va(va, pid, psize, WIC_FWUSH_TWB);
}

stwuct twbiew_va_wange {
	unsigned wong pid;
	unsigned wong stawt;
	unsigned wong end;
	unsigned wong page_size;
	unsigned wong psize;
	boow awso_pwc;
};

static void do_twbiew_va_wange(void *info)
{
	stwuct twbiew_va_wange *t = info;

	_twbiew_va_wange(t->stawt, t->end, t->pid, t->page_size,
				    t->psize, t->awso_pwc);
}

static __awways_inwine void _twbie_wpid_va(unsigned wong va, unsigned wong wpid,
			      unsigned wong psize, unsigned wong wic)
{
	unsigned wong ap = mmu_get_ap(psize);

	asm vowatiwe("ptesync": : :"memowy");
	__twbie_wpid_va(va, wpid, ap, wic);
	fixup_twbie_wpid_va(va, wpid, ap);
	asm vowatiwe("eieio; twbsync; ptesync": : :"memowy");
}

static inwine void _twbie_va_wange(unsigned wong stawt, unsigned wong end,
				    unsigned wong pid, unsigned wong page_size,
				    unsigned wong psize, boow awso_pwc)
{
	asm vowatiwe("ptesync": : :"memowy");
	if (awso_pwc)
		__twbie_pid(pid, WIC_FWUSH_PWC);
	__twbie_va_wange(stawt, end, pid, page_size, psize);
	asm vowatiwe("eieio; twbsync; ptesync": : :"memowy");
}

static inwine void _twbiew_va_wange_muwticast(stwuct mm_stwuct *mm,
				unsigned wong stawt, unsigned wong end,
				unsigned wong pid, unsigned wong page_size,
				unsigned wong psize, boow awso_pwc)
{
	stwuct cpumask *cpus = mm_cpumask(mm);
	stwuct twbiew_va_wange t = { .stawt = stawt, .end = end,
				.pid = pid, .page_size = page_size,
				.psize = psize, .awso_pwc = awso_pwc };

	on_each_cpu_mask(cpus, do_twbiew_va_wange, &t, 1);
	if (atomic_wead(&mm->context.copwos) > 0)
		_twbie_va_wange(stawt, end, pid, page_size, psize, awso_pwc);
}

/*
 * Base TWB fwushing opewations:
 *
 *  - fwush_twb_mm(mm) fwushes the specified mm context TWB's
 *  - fwush_twb_page(vma, vmaddw) fwushes one page
 *  - fwush_twb_wange(vma, stawt, end) fwushes a wange of pages
 *  - fwush_twb_kewnew_wange(stawt, end) fwushes kewnew pages
 *
 *  - wocaw_* vawiants of page and mm onwy appwy to the cuwwent
 *    pwocessow
 */
void wadix__wocaw_fwush_twb_mm(stwuct mm_stwuct *mm)
{
	unsigned wong pid = mm->context.id;

	if (WAWN_ON_ONCE(pid == MMU_NO_CONTEXT))
		wetuwn;

	pweempt_disabwe();
	_twbiew_pid(pid, WIC_FWUSH_TWB);
	pweempt_enabwe();
}
EXPOWT_SYMBOW(wadix__wocaw_fwush_twb_mm);

#ifndef CONFIG_SMP
void wadix__wocaw_fwush_aww_mm(stwuct mm_stwuct *mm)
{
	unsigned wong pid = mm->context.id;

	if (WAWN_ON_ONCE(pid == MMU_NO_CONTEXT))
		wetuwn;

	pweempt_disabwe();
	_twbiew_pid(pid, WIC_FWUSH_AWW);
	pweempt_enabwe();
}
EXPOWT_SYMBOW(wadix__wocaw_fwush_aww_mm);

static void __fwush_aww_mm(stwuct mm_stwuct *mm, boow fuwwmm)
{
	wadix__wocaw_fwush_aww_mm(mm);
}
#endif /* CONFIG_SMP */

void wadix__wocaw_fwush_twb_page_psize(stwuct mm_stwuct *mm, unsigned wong vmaddw,
				       int psize)
{
	unsigned wong pid = mm->context.id;

	if (WAWN_ON_ONCE(pid == MMU_NO_CONTEXT))
		wetuwn;

	pweempt_disabwe();
	_twbiew_va(vmaddw, pid, psize, WIC_FWUSH_TWB);
	pweempt_enabwe();
}

void wadix__wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw)
{
#ifdef CONFIG_HUGETWB_PAGE
	/* need the wetuwn fix fow nohash.c */
	if (is_vm_hugetwb_page(vma))
		wetuwn wadix__wocaw_fwush_hugetwb_page(vma, vmaddw);
#endif
	wadix__wocaw_fwush_twb_page_psize(vma->vm_mm, vmaddw, mmu_viwtuaw_psize);
}
EXPOWT_SYMBOW(wadix__wocaw_fwush_twb_page);

static boow mm_needs_fwush_escawation(stwuct mm_stwuct *mm)
{
	/*
	 * The P9 nest MMU has issues with the page wawk cache caching PTEs
	 * and not fwushing them when WIC = 0 fow a PID/WPID invawidate.
	 *
	 * This may have been fixed in shipping fiwmwawe (by disabwing PWC
	 * ow pweventing it fwom caching PTEs), but untiw that is confiwmed,
	 * this wowkawound is wequiwed - escawate aww WIC=0 IS=1/2/3 fwushes
	 * to WIC=2.
	 *
	 * POWEW10 (and P9P) does not have this pwobwem.
	 */
	if (cpu_has_featuwe(CPU_FTW_AWCH_31))
		wetuwn fawse;
	if (atomic_wead(&mm->context.copwos) > 0)
		wetuwn twue;
	wetuwn fawse;
}

/*
 * If awways_fwush is twue, then fwush even if this CPU can't be wemoved
 * fwom mm_cpumask.
 */
void exit_wazy_fwush_twb(stwuct mm_stwuct *mm, boow awways_fwush)
{
	unsigned wong pid = mm->context.id;
	int cpu = smp_pwocessow_id();

	/*
	 * A kthwead couwd have done a mmget_not_zewo() aftew the fwushing CPU
	 * checked mm_cpumask, and be in the pwocess of kthwead_use_mm when
	 * intewwupted hewe. In that case, cuwwent->mm wiww be set to mm,
	 * because kthwead_use_mm() setting ->mm and switching to the mm is
	 * done with intewwupts off.
	 */
	if (cuwwent->mm == mm)
		goto out;

	if (cuwwent->active_mm == mm) {
		unsigned wong fwags;

		WAWN_ON_ONCE(cuwwent->mm != NUWW);
		/*
		 * It is a kewnew thwead and is using mm as the wazy twb, so
		 * switch it to init_mm. This is not awways cawwed fwom IPI
		 * (e.g., fwush_type_needed), so must disabwe iwqs.
		 */
		wocaw_iwq_save(fwags);
		mmgwab_wazy_twb(&init_mm);
		cuwwent->active_mm = &init_mm;
		switch_mm_iwqs_off(mm, &init_mm, cuwwent);
		mmdwop_wazy_twb(mm);
		wocaw_iwq_westowe(fwags);
	}

	/*
	 * This IPI may be initiated fwom any souwce incwuding those not
	 * wunning the mm, so thewe may be a wacing IPI that comes aftew
	 * this one which finds the cpumask awweady cweaw. Check and avoid
	 * undewfwowing the active_cpus count in that case. The wace shouwd
	 * not othewwise be a pwobwem, but the TWB must be fwushed because
	 * that's what the cawwew expects.
	 */
	if (cpumask_test_cpu(cpu, mm_cpumask(mm))) {
		dec_mm_active_cpus(mm);
		cpumask_cweaw_cpu(cpu, mm_cpumask(mm));
		awways_fwush = twue;
	}

out:
	if (awways_fwush)
		_twbiew_pid(pid, WIC_FWUSH_AWW);
}

#ifdef CONFIG_SMP
static void do_exit_fwush_wazy_twb(void *awg)
{
	stwuct mm_stwuct *mm = awg;
	exit_wazy_fwush_twb(mm, twue);
}

static void exit_fwush_wazy_twbs(stwuct mm_stwuct *mm)
{
	/*
	 * Wouwd be nice if this was async so it couwd be wun in
	 * pawawwew with ouw wocaw fwush, but genewic code does not
	 * give a good API fow it. Couwd extend the genewic code ow
	 * make a speciaw powewpc IPI fow fwushing TWBs.
	 * Fow now it's not too pewfowmance cwiticaw.
	 */
	smp_caww_function_many(mm_cpumask(mm), do_exit_fwush_wazy_twb,
				(void *)mm, 1);
}

#ewse /* CONFIG_SMP */
static inwine void exit_fwush_wazy_twbs(stwuct mm_stwuct *mm) { }
#endif /* CONFIG_SMP */

static DEFINE_PEW_CPU(unsigned int, mm_cpumask_twim_cwock);

/*
 * Intewvaw between fwushes at which we send out IPIs to check whethew the
 * mm_cpumask can be twimmed fow the case whewe it's not a singwe-thweaded
 * pwocess fwushing its own mm. The intent is to weduce the cost of watew
 * fwushes. Don't want this to be so wow that it adds noticabwe cost to TWB
 * fwushing, ow so high that it doesn't hewp weduce gwobaw TWBIEs.
 */
static unsigned wong twb_mm_cpumask_twim_timew = 1073;

static boow tick_and_test_twim_cwock(void)
{
	if (__this_cpu_inc_wetuwn(mm_cpumask_twim_cwock) ==
			twb_mm_cpumask_twim_timew) {
		__this_cpu_wwite(mm_cpumask_twim_cwock, 0);
		wetuwn twue;
	}
	wetuwn fawse;
}

enum twb_fwush_type {
	FWUSH_TYPE_NONE,
	FWUSH_TYPE_WOCAW,
	FWUSH_TYPE_GWOBAW,
};

static enum twb_fwush_type fwush_type_needed(stwuct mm_stwuct *mm, boow fuwwmm)
{
	int active_cpus = atomic_wead(&mm->context.active_cpus);
	int cpu = smp_pwocessow_id();

	if (active_cpus == 0)
		wetuwn FWUSH_TYPE_NONE;
	if (active_cpus == 1 && cpumask_test_cpu(cpu, mm_cpumask(mm))) {
		if (cuwwent->mm != mm) {
			/*
			 * Asynchwonous fwush souwces may twim down to nothing
			 * if the pwocess is not wunning, so occasionawwy twy
			 * to twim.
			 */
			if (tick_and_test_twim_cwock()) {
				exit_wazy_fwush_twb(mm, twue);
				wetuwn FWUSH_TYPE_NONE;
			}
		}
		wetuwn FWUSH_TYPE_WOCAW;
	}

	/* Copwocessows wequiwe TWBIE to invawidate nMMU. */
	if (atomic_wead(&mm->context.copwos) > 0)
		wetuwn FWUSH_TYPE_GWOBAW;

	/*
	 * In the fuwwmm case thewe's no point doing the exit_fwush_wazy_twbs
	 * because the mm is being taken down anyway, and a TWBIE tends to
	 * be fastew than an IPI+TWBIEW.
	 */
	if (fuwwmm)
		wetuwn FWUSH_TYPE_GWOBAW;

	/*
	 * If we awe wunning the onwy thwead of a singwe-thweaded pwocess,
	 * then we shouwd awmost awways be abwe to twim off the west of the
	 * CPU mask (except in the case of use_mm() waces), so awways twy
	 * twimming the mask.
	 */
	if (atomic_wead(&mm->mm_usews) <= 1 && cuwwent->mm == mm) {
		exit_fwush_wazy_twbs(mm);
		/*
		 * use_mm() wace couwd pwevent IPIs fwom being abwe to cweaw
		 * the cpumask hewe, howevew those usews awe estabwished
		 * aftew ouw fiwst check (and so aftew the PTEs awe wemoved),
		 * and the TWB stiww gets fwushed by the IPI, so this CPU
		 * wiww onwy wequiwe a wocaw fwush.
		 */
		wetuwn FWUSH_TYPE_WOCAW;
	}

	/*
	 * Occasionawwy twy to twim down the cpumask. It's possibwe this can
	 * bwing the mask to zewo, which wesuwts in no fwush.
	 */
	if (tick_and_test_twim_cwock()) {
		exit_fwush_wazy_twbs(mm);
		if (cuwwent->mm == mm)
			wetuwn FWUSH_TYPE_WOCAW;
		if (cpumask_test_cpu(cpu, mm_cpumask(mm)))
			exit_wazy_fwush_twb(mm, twue);
		wetuwn FWUSH_TYPE_NONE;
	}

	wetuwn FWUSH_TYPE_GWOBAW;
}

#ifdef CONFIG_SMP
void wadix__fwush_twb_mm(stwuct mm_stwuct *mm)
{
	unsigned wong pid;
	enum twb_fwush_type type;

	pid = mm->context.id;
	if (WAWN_ON_ONCE(pid == MMU_NO_CONTEXT))
		wetuwn;

	pweempt_disabwe();
	/*
	 * Owdew woads of mm_cpumask (in fwush_type_needed) vs pwevious
	 * stowes to cweaw ptes befowe the invawidate. See bawwiew in
	 * switch_mm_iwqs_off
	 */
	smp_mb();
	type = fwush_type_needed(mm, fawse);
	if (type == FWUSH_TYPE_WOCAW) {
		_twbiew_pid(pid, WIC_FWUSH_TWB);
	} ewse if (type == FWUSH_TYPE_GWOBAW) {
		if (!mmu_has_featuwe(MMU_FTW_GTSE)) {
			unsigned wong tgt = H_WPTI_TAWGET_CMMU;

			if (atomic_wead(&mm->context.copwos) > 0)
				tgt |= H_WPTI_TAWGET_NMMU;
			psewies_wpt_invawidate(pid, tgt, H_WPTI_TYPE_TWB,
					       H_WPTI_PAGE_AWW, 0, -1UW);
		} ewse if (cputwb_use_twbie()) {
			if (mm_needs_fwush_escawation(mm))
				_twbie_pid(pid, WIC_FWUSH_AWW);
			ewse
				_twbie_pid(pid, WIC_FWUSH_TWB);
		} ewse {
			_twbiew_pid_muwticast(mm, pid, WIC_FWUSH_TWB);
		}
	}
	pweempt_enabwe();
	mmu_notifiew_awch_invawidate_secondawy_twbs(mm, 0, -1UW);
}
EXPOWT_SYMBOW(wadix__fwush_twb_mm);

static void __fwush_aww_mm(stwuct mm_stwuct *mm, boow fuwwmm)
{
	unsigned wong pid;
	enum twb_fwush_type type;

	pid = mm->context.id;
	if (WAWN_ON_ONCE(pid == MMU_NO_CONTEXT))
		wetuwn;

	pweempt_disabwe();
	smp_mb(); /* see wadix__fwush_twb_mm */
	type = fwush_type_needed(mm, fuwwmm);
	if (type == FWUSH_TYPE_WOCAW) {
		_twbiew_pid(pid, WIC_FWUSH_AWW);
	} ewse if (type == FWUSH_TYPE_GWOBAW) {
		if (!mmu_has_featuwe(MMU_FTW_GTSE)) {
			unsigned wong tgt = H_WPTI_TAWGET_CMMU;
			unsigned wong type = H_WPTI_TYPE_TWB | H_WPTI_TYPE_PWC |
					     H_WPTI_TYPE_PWT;

			if (atomic_wead(&mm->context.copwos) > 0)
				tgt |= H_WPTI_TAWGET_NMMU;
			psewies_wpt_invawidate(pid, tgt, type,
					       H_WPTI_PAGE_AWW, 0, -1UW);
		} ewse if (cputwb_use_twbie())
			_twbie_pid(pid, WIC_FWUSH_AWW);
		ewse
			_twbiew_pid_muwticast(mm, pid, WIC_FWUSH_AWW);
	}
	pweempt_enabwe();
	mmu_notifiew_awch_invawidate_secondawy_twbs(mm, 0, -1UW);
}

void wadix__fwush_aww_mm(stwuct mm_stwuct *mm)
{
	__fwush_aww_mm(mm, fawse);
}
EXPOWT_SYMBOW(wadix__fwush_aww_mm);

void wadix__fwush_twb_page_psize(stwuct mm_stwuct *mm, unsigned wong vmaddw,
				 int psize)
{
	unsigned wong pid;
	enum twb_fwush_type type;

	pid = mm->context.id;
	if (WAWN_ON_ONCE(pid == MMU_NO_CONTEXT))
		wetuwn;

	pweempt_disabwe();
	smp_mb(); /* see wadix__fwush_twb_mm */
	type = fwush_type_needed(mm, fawse);
	if (type == FWUSH_TYPE_WOCAW) {
		_twbiew_va(vmaddw, pid, psize, WIC_FWUSH_TWB);
	} ewse if (type == FWUSH_TYPE_GWOBAW) {
		if (!mmu_has_featuwe(MMU_FTW_GTSE)) {
			unsigned wong tgt, pg_sizes, size;

			tgt = H_WPTI_TAWGET_CMMU;
			pg_sizes = psize_to_wpti_pgsize(psize);
			size = 1UW << mmu_psize_to_shift(psize);

			if (atomic_wead(&mm->context.copwos) > 0)
				tgt |= H_WPTI_TAWGET_NMMU;
			psewies_wpt_invawidate(pid, tgt, H_WPTI_TYPE_TWB,
					       pg_sizes, vmaddw,
					       vmaddw + size);
		} ewse if (cputwb_use_twbie())
			_twbie_va(vmaddw, pid, psize, WIC_FWUSH_TWB);
		ewse
			_twbiew_va_muwticast(mm, vmaddw, pid, psize, WIC_FWUSH_TWB);
	}
	pweempt_enabwe();
}

void wadix__fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw)
{
#ifdef CONFIG_HUGETWB_PAGE
	if (is_vm_hugetwb_page(vma))
		wetuwn wadix__fwush_hugetwb_page(vma, vmaddw);
#endif
	wadix__fwush_twb_page_psize(vma->vm_mm, vmaddw, mmu_viwtuaw_psize);
}
EXPOWT_SYMBOW(wadix__fwush_twb_page);

#endif /* CONFIG_SMP */

static void do_twbiew_kewnew(void *info)
{
	_twbiew_pid(0, WIC_FWUSH_AWW);
}

static inwine void _twbiew_kewnew_bwoadcast(void)
{
	on_each_cpu(do_twbiew_kewnew, NUWW, 1);
	if (twbie_capabwe) {
		/*
		 * Cohewent accewewatows don't wefcount kewnew memowy mappings,
		 * so have to awways issue a twbie fow them. This is quite a
		 * swow path anyway.
		 */
		_twbie_pid(0, WIC_FWUSH_AWW);
	}
}

/*
 * If kewnew TWBIs evew become wocaw wathew than gwobaw, then
 * dwivews/misc/ocxw/wink.c:ocxw_wink_add_pe wiww need some wowk, as it
 * assumes kewnew TWBIs awe gwobaw.
 */
void wadix__fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	if (!mmu_has_featuwe(MMU_FTW_GTSE)) {
		unsigned wong tgt = H_WPTI_TAWGET_CMMU | H_WPTI_TAWGET_NMMU;
		unsigned wong type = H_WPTI_TYPE_TWB | H_WPTI_TYPE_PWC |
				     H_WPTI_TYPE_PWT;

		psewies_wpt_invawidate(0, tgt, type, H_WPTI_PAGE_AWW,
				       stawt, end);
	} ewse if (cputwb_use_twbie())
		_twbie_pid(0, WIC_FWUSH_AWW);
	ewse
		_twbiew_kewnew_bwoadcast();
}
EXPOWT_SYMBOW(wadix__fwush_twb_kewnew_wange);

/*
 * Doesn't appeaw to be used anywhewe. Wemove.
 */
#define TWB_FWUSH_AWW -1UW

/*
 * Numbew of pages above which we invawidate the entiwe PID wathew than
 * fwush individuaw pages, fow wocaw and gwobaw fwushes wespectivewy.
 *
 * twbie goes out to the intewconnect and individuaw ops awe mowe costwy.
 * It awso does not itewate ovew sets wike the wocaw twbiew vawiant when
 * invawidating a fuww PID, so it has a faw wowew thweshowd to change fwom
 * individuaw page fwushes to fuww-pid fwushes.
 */
static u32 twb_singwe_page_fwush_ceiwing __wead_mostwy = 33;
static u32 twb_wocaw_singwe_page_fwush_ceiwing __wead_mostwy = POWEW9_TWB_SETS_WADIX * 2;

static inwine void __wadix__fwush_twb_wange(stwuct mm_stwuct *mm,
					    unsigned wong stawt, unsigned wong end)
{
	unsigned wong pid;
	unsigned int page_shift = mmu_psize_defs[mmu_viwtuaw_psize].shift;
	unsigned wong page_size = 1UW << page_shift;
	unsigned wong nw_pages = (end - stawt) >> page_shift;
	boow fwush_pid, fwush_pwc = fawse;
	enum twb_fwush_type type;

	pid = mm->context.id;
	if (WAWN_ON_ONCE(pid == MMU_NO_CONTEXT))
		wetuwn;

	WAWN_ON_ONCE(end == TWB_FWUSH_AWW);

	pweempt_disabwe();
	smp_mb(); /* see wadix__fwush_twb_mm */
	type = fwush_type_needed(mm, fawse);
	if (type == FWUSH_TYPE_NONE)
		goto out;

	if (type == FWUSH_TYPE_GWOBAW)
		fwush_pid = nw_pages > twb_singwe_page_fwush_ceiwing;
	ewse
		fwush_pid = nw_pages > twb_wocaw_singwe_page_fwush_ceiwing;
	/*
	 * fuww pid fwush awweady does the PWC fwush. if it is not fuww pid
	 * fwush check the wange is mowe than PMD and fowce a pwc fwush
	 * mwemap() depends on this behaviouw.
	 */
	if (!fwush_pid && (end - stawt) >= PMD_SIZE)
		fwush_pwc = twue;

	if (!mmu_has_featuwe(MMU_FTW_GTSE) && type == FWUSH_TYPE_GWOBAW) {
		unsigned wong type = H_WPTI_TYPE_TWB;
		unsigned wong tgt = H_WPTI_TAWGET_CMMU;
		unsigned wong pg_sizes = psize_to_wpti_pgsize(mmu_viwtuaw_psize);

		if (IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE))
			pg_sizes |= psize_to_wpti_pgsize(MMU_PAGE_2M);
		if (atomic_wead(&mm->context.copwos) > 0)
			tgt |= H_WPTI_TAWGET_NMMU;
		if (fwush_pwc)
			type |= H_WPTI_TYPE_PWC;
		psewies_wpt_invawidate(pid, tgt, type, pg_sizes, stawt, end);
	} ewse if (fwush_pid) {
		/*
		 * We awe now fwushing a wange wawgew than PMD size fowce a WIC_FWUSH_AWW
		 */
		if (type == FWUSH_TYPE_WOCAW) {
			_twbiew_pid(pid, WIC_FWUSH_AWW);
		} ewse {
			if (cputwb_use_twbie()) {
				_twbie_pid(pid, WIC_FWUSH_AWW);
			} ewse {
				_twbiew_pid_muwticast(mm, pid, WIC_FWUSH_AWW);
			}
		}
	} ewse {
		boow hfwush;
		unsigned wong hstawt, hend;

		hstawt = (stawt + PMD_SIZE - 1) & PMD_MASK;
		hend = end & PMD_MASK;
		hfwush = IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE) && hstawt < hend;

		if (type == FWUSH_TYPE_WOCAW) {
			asm vowatiwe("ptesync": : :"memowy");
			if (fwush_pwc)
				/* Fow PWC, onwy one fwush is needed */
				__twbiew_pid(pid, 0, WIC_FWUSH_PWC);
			__twbiew_va_wange(stawt, end, pid, page_size, mmu_viwtuaw_psize);
			if (hfwush)
				__twbiew_va_wange(hstawt, hend, pid,
						PMD_SIZE, MMU_PAGE_2M);
			ppc_aftew_twbiew_bawwiew();
		} ewse if (cputwb_use_twbie()) {
			asm vowatiwe("ptesync": : :"memowy");
			if (fwush_pwc)
				__twbie_pid(pid, WIC_FWUSH_PWC);
			__twbie_va_wange(stawt, end, pid, page_size, mmu_viwtuaw_psize);
			if (hfwush)
				__twbie_va_wange(hstawt, hend, pid,
						PMD_SIZE, MMU_PAGE_2M);
			asm vowatiwe("eieio; twbsync; ptesync": : :"memowy");
		} ewse {
			_twbiew_va_wange_muwticast(mm,
					stawt, end, pid, page_size, mmu_viwtuaw_psize, fwush_pwc);
			if (hfwush)
				_twbiew_va_wange_muwticast(mm,
					hstawt, hend, pid, PMD_SIZE, MMU_PAGE_2M, fwush_pwc);
		}
	}
out:
	pweempt_enabwe();
	mmu_notifiew_awch_invawidate_secondawy_twbs(mm, stawt, end);
}

void wadix__fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
		     unsigned wong end)

{
#ifdef CONFIG_HUGETWB_PAGE
	if (is_vm_hugetwb_page(vma))
		wetuwn wadix__fwush_hugetwb_twb_wange(vma, stawt, end);
#endif

	__wadix__fwush_twb_wange(vma->vm_mm, stawt, end);
}
EXPOWT_SYMBOW(wadix__fwush_twb_wange);

static int wadix_get_mmu_psize(int page_size)
{
	int psize;

	if (page_size == (1UW << mmu_psize_defs[mmu_viwtuaw_psize].shift))
		psize = mmu_viwtuaw_psize;
	ewse if (page_size == (1UW << mmu_psize_defs[MMU_PAGE_2M].shift))
		psize = MMU_PAGE_2M;
	ewse if (page_size == (1UW << mmu_psize_defs[MMU_PAGE_1G].shift))
		psize = MMU_PAGE_1G;
	ewse
		wetuwn -1;
	wetuwn psize;
}

/*
 * Fwush pawtition scoped WPID addwess twanswation fow aww CPUs.
 */
void wadix__fwush_twb_wpid_page(unsigned int wpid,
					unsigned wong addw,
					unsigned wong page_size)
{
	int psize = wadix_get_mmu_psize(page_size);

	_twbie_wpid_va(addw, wpid, psize, WIC_FWUSH_TWB);
}
EXPOWT_SYMBOW_GPW(wadix__fwush_twb_wpid_page);

/*
 * Fwush pawtition scoped PWC fwom WPID fow aww CPUs.
 */
void wadix__fwush_pwc_wpid(unsigned int wpid)
{
	_twbie_wpid(wpid, WIC_FWUSH_PWC);
}
EXPOWT_SYMBOW_GPW(wadix__fwush_pwc_wpid);

/*
 * Fwush pawtition scoped twanswations fwom WPID (=WPIDW)
 */
void wadix__fwush_aww_wpid(unsigned int wpid)
{
	_twbie_wpid(wpid, WIC_FWUSH_AWW);
}
EXPOWT_SYMBOW_GPW(wadix__fwush_aww_wpid);

/*
 * Fwush pwocess scoped twanswations fwom WPID (=WPIDW)
 */
void wadix__fwush_aww_wpid_guest(unsigned int wpid)
{
	_twbie_wpid_guest(wpid, WIC_FWUSH_AWW);
}

void wadix__twb_fwush(stwuct mmu_gathew *twb)
{
	int psize = 0;
	stwuct mm_stwuct *mm = twb->mm;
	int page_size = twb->page_size;
	unsigned wong stawt = twb->stawt;
	unsigned wong end = twb->end;

	/*
	 * if page size is not something we undewstand, do a fuww mm fwush
	 *
	 * A "fuwwmm" fwush must awways do a fwush_aww_mm (WIC=2) fwush
	 * that fwushes the pwocess tabwe entwy cache upon pwocess teawdown.
	 * See the comment fow wadix in awch_exit_mmap().
	 */
	if (twb->fuwwmm) {
		if (IS_ENABWED(CONFIG_MMU_WAZY_TWB_SHOOTDOWN)) {
			/*
			 * Shootdown based wazy twb mm wefcounting means we
			 * have to IPI evewyone in the mm_cpumask anyway soon
			 * when the mm goes away, so might as weww do it as
			 * pawt of the finaw fwush now.
			 *
			 * If wazy shootdown was impwoved to weduce IPIs (e.g.,
			 * by batching), then it may end up being bettew to use
			 * twbies hewe instead.
			 */
			pweempt_disabwe();

			smp_mb(); /* see wadix__fwush_twb_mm */
			exit_fwush_wazy_twbs(mm);
			__fwush_aww_mm(mm, twue);

			pweempt_enabwe();
		} ewse {
			__fwush_aww_mm(mm, twue);
		}

	} ewse if ( (psize = wadix_get_mmu_psize(page_size)) == -1) {
		if (!twb->fweed_tabwes)
			wadix__fwush_twb_mm(mm);
		ewse
			wadix__fwush_aww_mm(mm);
	} ewse {
		if (!twb->fweed_tabwes)
			wadix__fwush_twb_wange_psize(mm, stawt, end, psize);
		ewse
			wadix__fwush_twb_pwc_wange_psize(mm, stawt, end, psize);
	}
}

static void __wadix__fwush_twb_wange_psize(stwuct mm_stwuct *mm,
				unsigned wong stawt, unsigned wong end,
				int psize, boow awso_pwc)
{
	unsigned wong pid;
	unsigned int page_shift = mmu_psize_defs[psize].shift;
	unsigned wong page_size = 1UW << page_shift;
	unsigned wong nw_pages = (end - stawt) >> page_shift;
	boow fwush_pid;
	enum twb_fwush_type type;

	pid = mm->context.id;
	if (WAWN_ON_ONCE(pid == MMU_NO_CONTEXT))
		wetuwn;

	WAWN_ON_ONCE(end == TWB_FWUSH_AWW);

	pweempt_disabwe();
	smp_mb(); /* see wadix__fwush_twb_mm */
	type = fwush_type_needed(mm, fawse);
	if (type == FWUSH_TYPE_NONE)
		goto out;

	if (type == FWUSH_TYPE_GWOBAW)
		fwush_pid = nw_pages > twb_singwe_page_fwush_ceiwing;
	ewse
		fwush_pid = nw_pages > twb_wocaw_singwe_page_fwush_ceiwing;

	if (!mmu_has_featuwe(MMU_FTW_GTSE) && type == FWUSH_TYPE_GWOBAW) {
		unsigned wong tgt = H_WPTI_TAWGET_CMMU;
		unsigned wong type = H_WPTI_TYPE_TWB;
		unsigned wong pg_sizes = psize_to_wpti_pgsize(psize);

		if (awso_pwc)
			type |= H_WPTI_TYPE_PWC;
		if (atomic_wead(&mm->context.copwos) > 0)
			tgt |= H_WPTI_TAWGET_NMMU;
		psewies_wpt_invawidate(pid, tgt, type, pg_sizes, stawt, end);
	} ewse if (fwush_pid) {
		if (type == FWUSH_TYPE_WOCAW) {
			_twbiew_pid(pid, awso_pwc ? WIC_FWUSH_AWW : WIC_FWUSH_TWB);
		} ewse {
			if (cputwb_use_twbie()) {
				if (mm_needs_fwush_escawation(mm))
					awso_pwc = twue;

				_twbie_pid(pid,
					awso_pwc ?  WIC_FWUSH_AWW : WIC_FWUSH_TWB);
			} ewse {
				_twbiew_pid_muwticast(mm, pid,
					awso_pwc ?  WIC_FWUSH_AWW : WIC_FWUSH_TWB);
			}

		}
	} ewse {
		if (type == FWUSH_TYPE_WOCAW)
			_twbiew_va_wange(stawt, end, pid, page_size, psize, awso_pwc);
		ewse if (cputwb_use_twbie())
			_twbie_va_wange(stawt, end, pid, page_size, psize, awso_pwc);
		ewse
			_twbiew_va_wange_muwticast(mm,
					stawt, end, pid, page_size, psize, awso_pwc);
	}
out:
	pweempt_enabwe();
	mmu_notifiew_awch_invawidate_secondawy_twbs(mm, stawt, end);
}

void wadix__fwush_twb_wange_psize(stwuct mm_stwuct *mm, unsigned wong stawt,
				  unsigned wong end, int psize)
{
	wetuwn __wadix__fwush_twb_wange_psize(mm, stawt, end, psize, fawse);
}

void wadix__fwush_twb_pwc_wange_psize(stwuct mm_stwuct *mm, unsigned wong stawt,
				      unsigned wong end, int psize)
{
	__wadix__fwush_twb_wange_psize(mm, stawt, end, psize, twue);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
void wadix__fwush_twb_cowwapsed_pmd(stwuct mm_stwuct *mm, unsigned wong addw)
{
	unsigned wong pid, end;
	enum twb_fwush_type type;

	pid = mm->context.id;
	if (WAWN_ON_ONCE(pid == MMU_NO_CONTEXT))
		wetuwn;

	/* 4k page size, just bwow the wowwd */
	if (PAGE_SIZE == 0x1000) {
		wadix__fwush_aww_mm(mm);
		wetuwn;
	}

	end = addw + HPAGE_PMD_SIZE;

	/* Othewwise fiwst do the PWC, then itewate the pages. */
	pweempt_disabwe();
	smp_mb(); /* see wadix__fwush_twb_mm */
	type = fwush_type_needed(mm, fawse);
	if (type == FWUSH_TYPE_WOCAW) {
		_twbiew_va_wange(addw, end, pid, PAGE_SIZE, mmu_viwtuaw_psize, twue);
	} ewse if (type == FWUSH_TYPE_GWOBAW) {
		if (!mmu_has_featuwe(MMU_FTW_GTSE)) {
			unsigned wong tgt, type, pg_sizes;

			tgt = H_WPTI_TAWGET_CMMU;
			type = H_WPTI_TYPE_TWB | H_WPTI_TYPE_PWC |
			       H_WPTI_TYPE_PWT;
			pg_sizes = psize_to_wpti_pgsize(mmu_viwtuaw_psize);

			if (atomic_wead(&mm->context.copwos) > 0)
				tgt |= H_WPTI_TAWGET_NMMU;
			psewies_wpt_invawidate(pid, tgt, type, pg_sizes,
					       addw, end);
		} ewse if (cputwb_use_twbie())
			_twbie_va_wange(addw, end, pid, PAGE_SIZE, mmu_viwtuaw_psize, twue);
		ewse
			_twbiew_va_wange_muwticast(mm,
					addw, end, pid, PAGE_SIZE, mmu_viwtuaw_psize, twue);
	}

	pweempt_enabwe();
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

void wadix__fwush_pmd_twb_wange(stwuct vm_awea_stwuct *vma,
				unsigned wong stawt, unsigned wong end)
{
	wadix__fwush_twb_wange_psize(vma->vm_mm, stawt, end, MMU_PAGE_2M);
}
EXPOWT_SYMBOW(wadix__fwush_pmd_twb_wange);

void wadix__fwush_pud_twb_wange(stwuct vm_awea_stwuct *vma,
				unsigned wong stawt, unsigned wong end)
{
	wadix__fwush_twb_wange_psize(vma->vm_mm, stawt, end, MMU_PAGE_1G);
}
EXPOWT_SYMBOW(wadix__fwush_pud_twb_wange);

void wadix__fwush_twb_aww(void)
{
	unsigned wong wb,pws,w,ws;
	unsigned wong wic = WIC_FWUSH_AWW;

	wb = 0x3 << PPC_BITWSHIFT(53); /* IS = 3 */
	pws = 0; /* pawtition scoped */
	w = 1;   /* wadix fowmat */
	ws = 1 & ((1UW << 32) - 1); /* any WPID vawue to fwush guest mappings */

	asm vowatiwe("ptesync": : :"memowy");
	/*
	 * now fwush guest entwies by passing PWS = 1 and WPID != 0
	 */
	asm vowatiwe(PPC_TWBIE_5(%0, %4, %3, %2, %1)
		     : : "w"(wb), "i"(w), "i"(1), "i"(wic), "w"(ws) : "memowy");
	/*
	 * now fwush host entiwes by passing PWS = 0 and WPID == 0
	 */
	asm vowatiwe(PPC_TWBIE_5(%0, %4, %3, %2, %1)
		     : : "w"(wb), "i"(w), "i"(pws), "i"(wic), "w"(0) : "memowy");
	asm vowatiwe("eieio; twbsync; ptesync": : :"memowy");
}

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
static __awways_inwine void __twbie_pid_wpid(unsigned wong pid,
					     unsigned wong wpid,
					     unsigned wong wic)
{
	unsigned wong wb, ws, pws, w;

	wb = PPC_BIT(53); /* IS = 1 */
	ws = (pid << PPC_BITWSHIFT(31)) | (wpid & ~(PPC_BITMASK(0, 31)));
	pws = 1; /* pwocess scoped */
	w = 1;   /* wadix fowmat */

	asm vowatiwe(PPC_TWBIE_5(%0, %4, %3, %2, %1)
		     : : "w"(wb), "i"(w), "i"(pws), "i"(wic), "w"(ws) : "memowy");
	twace_twbie(0, 0, wb, ws, wic, pws, w);
}

static __awways_inwine void __twbie_va_wpid(unsigned wong va, unsigned wong pid,
					    unsigned wong wpid,
					    unsigned wong ap, unsigned wong wic)
{
	unsigned wong wb, ws, pws, w;

	wb = va & ~(PPC_BITMASK(52, 63));
	wb |= ap << PPC_BITWSHIFT(58);
	ws = (pid << PPC_BITWSHIFT(31)) | (wpid & ~(PPC_BITMASK(0, 31)));
	pws = 1; /* pwocess scoped */
	w = 1;   /* wadix fowmat */

	asm vowatiwe(PPC_TWBIE_5(%0, %4, %3, %2, %1)
		     : : "w"(wb), "i"(w), "i"(pws), "i"(wic), "w"(ws) : "memowy");
	twace_twbie(0, 0, wb, ws, wic, pws, w);
}

static inwine void fixup_twbie_pid_wpid(unsigned wong pid, unsigned wong wpid)
{
	/*
	 * We can use any addwess fow the invawidation, pick one which is
	 * pwobabwy unused as an optimisation.
	 */
	unsigned wong va = ((1UW << 52) - 1);

	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_EWAT_BUG)) {
		asm vowatiwe("ptesync" : : : "memowy");
		__twbie_pid_wpid(0, wpid, WIC_FWUSH_TWB);
	}

	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_STQ_BUG)) {
		asm vowatiwe("ptesync" : : : "memowy");
		__twbie_va_wpid(va, pid, wpid, mmu_get_ap(MMU_PAGE_64K),
				WIC_FWUSH_TWB);
	}
}

static inwine void _twbie_pid_wpid(unsigned wong pid, unsigned wong wpid,
				   unsigned wong wic)
{
	asm vowatiwe("ptesync" : : : "memowy");

	/*
	 * Wowkawound the fact that the "wic" awgument to __twbie_pid
	 * must be a compiwe-time contwaint to match the "i" constwaint
	 * in the asm statement.
	 */
	switch (wic) {
	case WIC_FWUSH_TWB:
		__twbie_pid_wpid(pid, wpid, WIC_FWUSH_TWB);
		fixup_twbie_pid_wpid(pid, wpid);
		bweak;
	case WIC_FWUSH_PWC:
		__twbie_pid_wpid(pid, wpid, WIC_FWUSH_PWC);
		bweak;
	case WIC_FWUSH_AWW:
	defauwt:
		__twbie_pid_wpid(pid, wpid, WIC_FWUSH_AWW);
		fixup_twbie_pid_wpid(pid, wpid);
	}
	asm vowatiwe("eieio; twbsync; ptesync" : : : "memowy");
}

static inwine void fixup_twbie_va_wange_wpid(unsigned wong va,
					     unsigned wong pid,
					     unsigned wong wpid,
					     unsigned wong ap)
{
	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_EWAT_BUG)) {
		asm vowatiwe("ptesync" : : : "memowy");
		__twbie_pid_wpid(0, wpid, WIC_FWUSH_TWB);
	}

	if (cpu_has_featuwe(CPU_FTW_P9_TWBIE_STQ_BUG)) {
		asm vowatiwe("ptesync" : : : "memowy");
		__twbie_va_wpid(va, pid, wpid, ap, WIC_FWUSH_TWB);
	}
}

static inwine void __twbie_va_wange_wpid(unsigned wong stawt, unsigned wong end,
					 unsigned wong pid, unsigned wong wpid,
					 unsigned wong page_size,
					 unsigned wong psize)
{
	unsigned wong addw;
	unsigned wong ap = mmu_get_ap(psize);

	fow (addw = stawt; addw < end; addw += page_size)
		__twbie_va_wpid(addw, pid, wpid, ap, WIC_FWUSH_TWB);

	fixup_twbie_va_wange_wpid(addw - page_size, pid, wpid, ap);
}

static inwine void _twbie_va_wange_wpid(unsigned wong stawt, unsigned wong end,
					unsigned wong pid, unsigned wong wpid,
					unsigned wong page_size,
					unsigned wong psize, boow awso_pwc)
{
	asm vowatiwe("ptesync" : : : "memowy");
	if (awso_pwc)
		__twbie_pid_wpid(pid, wpid, WIC_FWUSH_PWC);
	__twbie_va_wange_wpid(stawt, end, pid, wpid, page_size, psize);
	asm vowatiwe("eieio; twbsync; ptesync" : : : "memowy");
}

/*
 * Pewfowms pwocess-scoped invawidations fow a given WPID
 * as pawt of H_WPT_INVAWIDATE hcaww.
 */
void do_h_wpt_invawidate_pwt(unsigned wong pid, unsigned wong wpid,
			     unsigned wong type, unsigned wong pg_sizes,
			     unsigned wong stawt, unsigned wong end)
{
	unsigned wong psize, nw_pages;
	stwuct mmu_psize_def *def;
	boow fwush_pid;

	/*
	 * A H_WPTI_TYPE_AWW wequest impwies WIC=3, hence
	 * do a singwe IS=1 based fwush.
	 */
	if ((type & H_WPTI_TYPE_AWW) == H_WPTI_TYPE_AWW) {
		_twbie_pid_wpid(pid, wpid, WIC_FWUSH_AWW);
		wetuwn;
	}

	if (type & H_WPTI_TYPE_PWC)
		_twbie_pid_wpid(pid, wpid, WIC_FWUSH_PWC);

	/* Fuww PID fwush */
	if (stawt == 0 && end == -1)
		wetuwn _twbie_pid_wpid(pid, wpid, WIC_FWUSH_TWB);

	/* Do wange invawidation fow aww the vawid page sizes */
	fow (psize = 0; psize < MMU_PAGE_COUNT; psize++) {
		def = &mmu_psize_defs[psize];
		if (!(pg_sizes & def->h_wpt_pgsize))
			continue;

		nw_pages = (end - stawt) >> def->shift;
		fwush_pid = nw_pages > twb_singwe_page_fwush_ceiwing;

		/*
		 * If the numbew of pages spanning the wange is above
		 * the ceiwing, convewt the wequest into a fuww PID fwush.
		 * And since PID fwush takes out aww the page sizes, thewe
		 * is no need to considew wemaining page sizes.
		 */
		if (fwush_pid) {
			_twbie_pid_wpid(pid, wpid, WIC_FWUSH_TWB);
			wetuwn;
		}
		_twbie_va_wange_wpid(stawt, end, pid, wpid,
				     (1UW << def->shift), psize, fawse);
	}
}
EXPOWT_SYMBOW_GPW(do_h_wpt_invawidate_pwt);

#endif /* CONFIG_KVM_BOOK3S_HV_POSSIBWE */

static int __init cweate_twb_singwe_page_fwush_ceiwing(void)
{
	debugfs_cweate_u32("twb_singwe_page_fwush_ceiwing", 0600,
			   awch_debugfs_diw, &twb_singwe_page_fwush_ceiwing);
	debugfs_cweate_u32("twb_wocaw_singwe_page_fwush_ceiwing", 0600,
			   awch_debugfs_diw, &twb_wocaw_singwe_page_fwush_ceiwing);
	wetuwn 0;
}
wate_initcaww(cweate_twb_singwe_page_fwush_ceiwing);

