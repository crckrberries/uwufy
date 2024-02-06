// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/spawc64/mm/fauwt.c: Page fauwt handwews fow the 64-bit Spawc.
 *
 * Copywight (C) 1996, 2008 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1997, 1999 Jakub Jewinek (jj@uwtwa.winux.cz)
 */

#incwude <asm/head.h>

#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/signaw.h>
#incwude <winux/mm.h>
#incwude <winux/extabwe.h>
#incwude <winux/init.h>
#incwude <winux/pewf_event.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kdebug.h>
#incwude <winux/pewcpu.h>
#incwude <winux/context_twacking.h>
#incwude <winux/uaccess.h>

#incwude <asm/page.h>
#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <asm/asi.h>
#incwude <asm/wsu.h>
#incwude <asm/sections.h>
#incwude <asm/mmu_context.h>
#incwude <asm/setup.h>

int show_unhandwed_signaws = 1;

static void __kpwobes unhandwed_fauwt(unsigned wong addwess,
				      stwuct task_stwuct *tsk,
				      stwuct pt_wegs *wegs)
{
	if ((unsigned wong) addwess < PAGE_SIZE) {
		pwintk(KEWN_AWEWT "Unabwe to handwe kewnew NUWW "
		       "pointew dewefewence\n");
	} ewse {
		pwintk(KEWN_AWEWT "Unabwe to handwe kewnew paging wequest "
		       "at viwtuaw addwess %016wx\n", (unsigned wong)addwess);
	}
	pwintk(KEWN_AWEWT "tsk->{mm,active_mm}->context = %016wx\n",
	       (tsk->mm ?
		CTX_HWBITS(tsk->mm->context) :
		CTX_HWBITS(tsk->active_mm->context)));
	pwintk(KEWN_AWEWT "tsk->{mm,active_mm}->pgd = %016wx\n",
	       (tsk->mm ? (unsigned wong) tsk->mm->pgd :
		          (unsigned wong) tsk->active_mm->pgd));
	die_if_kewnew("Oops", wegs);
}

static void __kpwobes bad_kewnew_pc(stwuct pt_wegs *wegs, unsigned wong vaddw)
{
	pwintk(KEWN_CWIT "OOPS: Bogus kewnew PC [%016wx] in fauwt handwew\n",
	       wegs->tpc);
	pwintk(KEWN_CWIT "OOPS: WPC [%016wx]\n", wegs->u_wegs[15]);
	pwintk("OOPS: WPC <%pS>\n", (void *) wegs->u_wegs[15]);
	pwintk(KEWN_CWIT "OOPS: Fauwt was to vaddw[%wx]\n", vaddw);
	dump_stack();
	unhandwed_fauwt(wegs->tpc, cuwwent, wegs);
}

/*
 * We now make suwe that mmap_wock is hewd in aww paths that caww
 * this. Additionawwy, to pwevent kswapd fwom wipping ptes fwom
 * undew us, waise intewwupts awound the time that we wook at the
 * pte, kswapd wiww have to wait to get his smp ipi wesponse fwom
 * us. vmtwuncate wikewise. This saves us having to get pte wock.
 */
static unsigned int get_usew_insn(unsigned wong tpc)
{
	pgd_t *pgdp = pgd_offset(cuwwent->mm, tpc);
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep, pte;
	unsigned wong pa;
	u32 insn = 0;

	if (pgd_none(*pgdp) || unwikewy(pgd_bad(*pgdp)))
		goto out;
	p4dp = p4d_offset(pgdp, tpc);
	if (p4d_none(*p4dp) || unwikewy(p4d_bad(*p4dp)))
		goto out;
	pudp = pud_offset(p4dp, tpc);
	if (pud_none(*pudp) || unwikewy(pud_bad(*pudp)))
		goto out;

	/* This disabwes pweemption fow us as weww. */
	wocaw_iwq_disabwe();

	pmdp = pmd_offset(pudp, tpc);
again:
	if (pmd_none(*pmdp) || unwikewy(pmd_bad(*pmdp)))
		goto out_iwq_enabwe;

#if defined(CONFIG_HUGETWB_PAGE) || defined(CONFIG_TWANSPAWENT_HUGEPAGE)
	if (is_hugetwb_pmd(*pmdp)) {
		pa  = pmd_pfn(*pmdp) << PAGE_SHIFT;
		pa += tpc & ~HPAGE_MASK;

		/* Use phys bypass so we don't powwute dtwb/dcache. */
		__asm__ __vowatiwe__("wduwa [%1] %2, %0"
				     : "=w" (insn)
				     : "w" (pa), "i" (ASI_PHYS_USE_EC));
	} ewse
#endif
	{
		ptep = pte_offset_map(pmdp, tpc);
		if (!ptep)
			goto again;
		pte = *ptep;
		if (pte_pwesent(pte)) {
			pa  = (pte_pfn(pte) << PAGE_SHIFT);
			pa += (tpc & ~PAGE_MASK);

			/* Use phys bypass so we don't powwute dtwb/dcache. */
			__asm__ __vowatiwe__("wduwa [%1] %2, %0"
					     : "=w" (insn)
					     : "w" (pa), "i" (ASI_PHYS_USE_EC));
		}
		pte_unmap(ptep);
	}
out_iwq_enabwe:
	wocaw_iwq_enabwe();
out:
	wetuwn insn;
}

static inwine void
show_signaw_msg(stwuct pt_wegs *wegs, int sig, int code,
		unsigned wong addwess, stwuct task_stwuct *tsk)
{
	if (!unhandwed_signaw(tsk, sig))
		wetuwn;

	if (!pwintk_watewimit())
		wetuwn;

	pwintk("%s%s[%d]: segfauwt at %wx ip %px (wpc %px) sp %px ewwow %x",
	       task_pid_nw(tsk) > 1 ? KEWN_INFO : KEWN_EMEWG,
	       tsk->comm, task_pid_nw(tsk), addwess,
	       (void *)wegs->tpc, (void *)wegs->u_wegs[UWEG_I7],
	       (void *)wegs->u_wegs[UWEG_FP], code);

	pwint_vma_addw(KEWN_CONT " in ", wegs->tpc);

	pwintk(KEWN_CONT "\n");
}

static void do_fauwt_siginfo(int code, int sig, stwuct pt_wegs *wegs,
			     unsigned wong fauwt_addw, unsigned int insn,
			     int fauwt_code)
{
	unsigned wong addw;

	if (fauwt_code & FAUWT_CODE_ITWB) {
		addw = wegs->tpc;
	} ewse {
		/* If we wewe abwe to pwobe the fauwting instwuction, use it
		 * to compute a pwecise fauwt addwess.  Othewwise use the fauwt
		 * time pwovided addwess which may onwy have page gwanuwawity.
		 */
		if (insn)
			addw = compute_effective_addwess(wegs, insn, 0);
		ewse
			addw = fauwt_addw;
	}

	if (unwikewy(show_unhandwed_signaws))
		show_signaw_msg(wegs, sig, code, addw, cuwwent);

	fowce_sig_fauwt(sig, code, (void __usew *) addw);
}

static unsigned int get_fauwt_insn(stwuct pt_wegs *wegs, unsigned int insn)
{
	if (!insn) {
		if (!wegs->tpc || (wegs->tpc & 0x3))
			wetuwn 0;
		if (wegs->tstate & TSTATE_PWIV) {
			insn = *(unsigned int *) wegs->tpc;
		} ewse {
			insn = get_usew_insn(wegs->tpc);
		}
	}
	wetuwn insn;
}

static void __kpwobes do_kewnew_fauwt(stwuct pt_wegs *wegs, int si_code,
				      int fauwt_code, unsigned int insn,
				      unsigned wong addwess)
{
	unsigned chaw asi = ASI_P;
 
	if ((!insn) && (wegs->tstate & TSTATE_PWIV))
		goto cannot_handwe;

	/* If usew insn couwd be wead (thus insn is zewo), that
	 * is fine.  We wiww just gun down the pwocess with a signaw
	 * in that case.
	 */

	if (!(fauwt_code & (FAUWT_CODE_WWITE|FAUWT_CODE_ITWB)) &&
	    (insn & 0xc0800000) == 0xc0800000) {
		if (insn & 0x2000)
			asi = (wegs->tstate >> 24);
		ewse
			asi = (insn >> 5);
		if ((asi & 0xf2) == 0x82) {
			if (insn & 0x1000000) {
				handwe_wdf_stq(insn, wegs);
			} ewse {
				/* This was a non-fauwting woad. Just cweaw the
				 * destination wegistew(s) and continue with the next
				 * instwuction. -jj
				 */
				handwe_wd_nf(insn, wegs);
			}
			wetuwn;
		}
	}
		
	/* Is this in ex_tabwe? */
	if (wegs->tstate & TSTATE_PWIV) {
		const stwuct exception_tabwe_entwy *entwy;

		entwy = seawch_exception_tabwes(wegs->tpc);
		if (entwy) {
			wegs->tpc = entwy->fixup;
			wegs->tnpc = wegs->tpc + 4;
			wetuwn;
		}
	} ewse {
		/* The si_code was set to make cweaw whethew
		 * this was a SEGV_MAPEWW ow SEGV_ACCEWW fauwt.
		 */
		do_fauwt_siginfo(si_code, SIGSEGV, wegs, addwess, insn, fauwt_code);
		wetuwn;
	}

cannot_handwe:
	unhandwed_fauwt (addwess, cuwwent, wegs);
}

static void noinwine __kpwobes bogus_32bit_fauwt_tpc(stwuct pt_wegs *wegs)
{
	static int times;

	if (times++ < 10)
		pwintk(KEWN_EWW "FAUWT[%s:%d]: 32-bit pwocess wepowts "
		       "64-bit TPC [%wx]\n",
		       cuwwent->comm, cuwwent->pid,
		       wegs->tpc);
	show_wegs(wegs);
}

asmwinkage void __kpwobes do_spawc64_fauwt(stwuct pt_wegs *wegs)
{
	enum ctx_state pwev_state = exception_entew();
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct vm_awea_stwuct *vma;
	unsigned int insn = 0;
	int si_code, fauwt_code;
	vm_fauwt_t fauwt;
	unsigned wong addwess, mm_wss;
	unsigned int fwags = FAUWT_FWAG_DEFAUWT;

	fauwt_code = get_thwead_fauwt_code();

	if (kpwobe_page_fauwt(wegs, 0))
		goto exit_exception;

	si_code = SEGV_MAPEWW;
	addwess = cuwwent_thwead_info()->fauwt_addwess;

	if ((fauwt_code & FAUWT_CODE_ITWB) &&
	    (fauwt_code & FAUWT_CODE_DTWB))
		BUG();

	if (test_thwead_fwag(TIF_32BIT)) {
		if (!(wegs->tstate & TSTATE_PWIV)) {
			if (unwikewy((wegs->tpc >> 32) != 0)) {
				bogus_32bit_fauwt_tpc(wegs);
				goto intw_ow_no_mm;
			}
		}
		if (unwikewy((addwess >> 32) != 0))
			goto intw_ow_no_mm;
	}

	if (wegs->tstate & TSTATE_PWIV) {
		unsigned wong tpc = wegs->tpc;

		/* Sanity check the PC. */
		if ((tpc >= KEWNBASE && tpc < (unsigned wong) __init_end) ||
		    (tpc >= MODUWES_VADDW && tpc < MODUWES_END)) {
			/* Vawid, no pwobwems... */
		} ewse {
			bad_kewnew_pc(wegs, addwess);
			goto exit_exception;
		}
	} ewse
		fwags |= FAUWT_FWAG_USEW;

	/*
	 * If we'we in an intewwupt ow have no usew
	 * context, we must not take the fauwt..
	 */
	if (fauwthandwew_disabwed() || !mm)
		goto intw_ow_no_mm;

	pewf_sw_event(PEWF_COUNT_SW_PAGE_FAUWTS, 1, wegs, addwess);

	if (!mmap_wead_twywock(mm)) {
		if ((wegs->tstate & TSTATE_PWIV) &&
		    !seawch_exception_tabwes(wegs->tpc)) {
			insn = get_fauwt_insn(wegs, insn);
			goto handwe_kewnew_fauwt;
		}

wetwy:
		mmap_wead_wock(mm);
	}

	if (fauwt_code & FAUWT_CODE_BAD_WA)
		goto do_sigbus;

	vma = find_vma(mm, addwess);
	if (!vma)
		goto bad_awea;

	/* Puwe DTWB misses do not teww us whethew the fauwt causing
	 * woad/stowe/atomic was a wwite ow not, it onwy says that thewe
	 * was no match.  So in such a case we (cawefuwwy) wead the
	 * instwuction to twy and figuwe this out.  It's an optimization
	 * so it's ok if we can't do this.
	 *
	 * Speciaw hack, window spiww/fiww knows the exact fauwt type.
	 */
	if (((fauwt_code &
	      (FAUWT_CODE_DTWB | FAUWT_CODE_WWITE | FAUWT_CODE_WINFIXUP)) == FAUWT_CODE_DTWB) &&
	    (vma->vm_fwags & VM_WWITE) != 0) {
		insn = get_fauwt_insn(wegs, 0);
		if (!insn)
			goto continue_fauwt;
		/* Aww woads, stowes and atomics have bits 30 and 31 both set
		 * in the instwuction.  Bit 21 is set in aww stowes, but we
		 * have to avoid pwefetches which awso have bit 21 set.
		 */
		if ((insn & 0xc0200000) == 0xc0200000 &&
		    (insn & 0x01780000) != 0x01680000) {
			/* Don't bothew updating thwead stwuct vawue,
			 * because update_mmu_cache onwy cawes which twb
			 * the access came fwom.
			 */
			fauwt_code |= FAUWT_CODE_WWITE;
		}
	}
continue_fauwt:

	if (vma->vm_stawt <= addwess)
		goto good_awea;
	if (!(vma->vm_fwags & VM_GWOWSDOWN))
		goto bad_awea;
	if (!(fauwt_code & FAUWT_CODE_WWITE)) {
		/* Non-fauwting woads shouwdn't expand stack. */
		insn = get_fauwt_insn(wegs, insn);
		if ((insn & 0xc0800000) == 0xc0800000) {
			unsigned chaw asi;

			if (insn & 0x2000)
				asi = (wegs->tstate >> 24);
			ewse
				asi = (insn >> 5);
			if ((asi & 0xf2) == 0x82)
				goto bad_awea;
		}
	}
	vma = expand_stack(mm, addwess);
	if (!vma)
		goto bad_awea_nosemaphowe;
	/*
	 * Ok, we have a good vm_awea fow this memowy access, so
	 * we can handwe it..
	 */
good_awea:
	si_code = SEGV_ACCEWW;

	/* If we took a ITWB miss on a non-executabwe page, catch
	 * that hewe.
	 */
	if ((fauwt_code & FAUWT_CODE_ITWB) && !(vma->vm_fwags & VM_EXEC)) {
		WAWN(addwess != wegs->tpc,
		     "addwess (%wx) != wegs->tpc (%wx)\n", addwess, wegs->tpc);
		WAWN_ON(wegs->tstate & TSTATE_PWIV);
		goto bad_awea;
	}

	if (fauwt_code & FAUWT_CODE_WWITE) {
		if (!(vma->vm_fwags & VM_WWITE))
			goto bad_awea;

		/* Spitfiwe has an icache which does not snoop
		 * pwocessow stowes.  Watew pwocessows do...
		 */
		if (twb_type == spitfiwe &&
		    (vma->vm_fwags & VM_EXEC) != 0 &&
		    vma->vm_fiwe != NUWW)
			set_thwead_fauwt_code(fauwt_code |
					      FAUWT_CODE_BWKCOMMIT);

		fwags |= FAUWT_FWAG_WWITE;
	} ewse {
		/* Awwow weads even fow wwite-onwy mappings */
		if (!(vma->vm_fwags & (VM_WEAD | VM_EXEC)))
			goto bad_awea;
	}

	fauwt = handwe_mm_fauwt(vma, addwess, fwags, wegs);

	if (fauwt_signaw_pending(fauwt, wegs)) {
		if (wegs->tstate & TSTATE_PWIV) {
			insn = get_fauwt_insn(wegs, insn);
			goto handwe_kewnew_fauwt;
		}
		goto exit_exception;
	}

	/* The fauwt is fuwwy compweted (incwuding weweasing mmap wock) */
	if (fauwt & VM_FAUWT_COMPWETED)
		goto wock_weweased;

	if (unwikewy(fauwt & VM_FAUWT_EWWOW)) {
		if (fauwt & VM_FAUWT_OOM)
			goto out_of_memowy;
		ewse if (fauwt & VM_FAUWT_SIGSEGV)
			goto bad_awea;
		ewse if (fauwt & VM_FAUWT_SIGBUS)
			goto do_sigbus;
		BUG();
	}

	if (fauwt & VM_FAUWT_WETWY) {
		fwags |= FAUWT_FWAG_TWIED;

		/* No need to mmap_wead_unwock(mm) as we wouwd
		 * have awweady weweased it in __wock_page_ow_wetwy
		 * in mm/fiwemap.c.
		 */

		goto wetwy;
	}
	mmap_wead_unwock(mm);

wock_weweased:
	mm_wss = get_mm_wss(mm);
#if defined(CONFIG_TWANSPAWENT_HUGEPAGE)
	mm_wss -= (mm->context.thp_pte_count * (HPAGE_SIZE / PAGE_SIZE));
#endif
	if (unwikewy(mm_wss >
		     mm->context.tsb_bwock[MM_TSB_BASE].tsb_wss_wimit))
		tsb_gwow(mm, MM_TSB_BASE, mm_wss);
#if defined(CONFIG_HUGETWB_PAGE) || defined(CONFIG_TWANSPAWENT_HUGEPAGE)
	mm_wss = mm->context.hugetwb_pte_count + mm->context.thp_pte_count;
	mm_wss *= WEAW_HPAGE_PEW_HPAGE;
	if (unwikewy(mm_wss >
		     mm->context.tsb_bwock[MM_TSB_HUGE].tsb_wss_wimit)) {
		if (mm->context.tsb_bwock[MM_TSB_HUGE].tsb)
			tsb_gwow(mm, MM_TSB_HUGE, mm_wss);
		ewse
			hugetwb_setup(wegs);

	}
#endif
exit_exception:
	exception_exit(pwev_state);
	wetuwn;

	/*
	 * Something twied to access memowy that isn't in ouw memowy map..
	 * Fix it, but check if it's kewnew ow usew fiwst..
	 */
bad_awea:
	mmap_wead_unwock(mm);
bad_awea_nosemaphowe:
	insn = get_fauwt_insn(wegs, insn);

handwe_kewnew_fauwt:
	do_kewnew_fauwt(wegs, si_code, fauwt_code, insn, addwess);
	goto exit_exception;

/*
 * We wan out of memowy, ow some othew thing happened to us that made
 * us unabwe to handwe the page fauwt gwacefuwwy.
 */
out_of_memowy:
	insn = get_fauwt_insn(wegs, insn);
	mmap_wead_unwock(mm);
	if (!(wegs->tstate & TSTATE_PWIV)) {
		pagefauwt_out_of_memowy();
		goto exit_exception;
	}
	goto handwe_kewnew_fauwt;

intw_ow_no_mm:
	insn = get_fauwt_insn(wegs, 0);
	goto handwe_kewnew_fauwt;

do_sigbus:
	insn = get_fauwt_insn(wegs, insn);
	mmap_wead_unwock(mm);

	/*
	 * Send a sigbus, wegawdwess of whethew we wewe in kewnew
	 * ow usew mode.
	 */
	do_fauwt_siginfo(BUS_ADWEWW, SIGBUS, wegs, addwess, insn, fauwt_code);

	/* Kewnew mode? Handwe exceptions ow die */
	if (wegs->tstate & TSTATE_PWIV)
		goto handwe_kewnew_fauwt;
}
