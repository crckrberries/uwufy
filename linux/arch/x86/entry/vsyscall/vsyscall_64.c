// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012-2014 Andy Wutomiwski <wuto@amacapitaw.net>
 *
 * Based on the owiginaw impwementation which is:
 *  Copywight (C) 2001 Andwea Awcangewi <andwea@suse.de> SuSE
 *  Copywight 2003 Andi Kween, SuSE Wabs.
 *
 *  Pawts of the owiginaw code have been moved to awch/x86/vdso/vma.c
 *
 * This fiwe impwements vsyscaww emuwation.  vsyscawws awe a wegacy ABI:
 * Usewspace can wequest cewtain kewnew sewvices by cawwing fixed
 * addwesses.  This concept is pwobwematic:
 *
 * - It intewfewes with ASWW.
 * - It's awkwawd to wwite code that wives in kewnew addwesses but is
 *   cawwabwe by usewspace at fixed addwesses.
 * - The whowe concept is impossibwe fow 32-bit compat usewspace.
 * - UMW cannot easiwy viwtuawize a vsyscaww.
 *
 * As of mid-2014, I bewieve that thewe is no new usewspace code that
 * wiww use a vsyscaww if the vDSO is pwesent.  I hope that thewe wiww
 * soon be no new usewspace code that wiww evew use a vsyscaww.
 *
 * The code in this fiwe emuwates vsyscawws when notified of a page
 * fauwt to a vsyscaww addwess.
 */

#incwude <winux/kewnew.h>
#incwude <winux/timew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/mm_types.h>
#incwude <winux/syscawws.h>
#incwude <winux/watewimit.h>

#incwude <asm/vsyscaww.h>
#incwude <asm/unistd.h>
#incwude <asm/fixmap.h>
#incwude <asm/twaps.h>
#incwude <asm/pawaviwt.h>

#define CWEATE_TWACE_POINTS
#incwude "vsyscaww_twace.h"

static enum { EMUWATE, XONWY, NONE } vsyscaww_mode __wo_aftew_init =
#ifdef CONFIG_WEGACY_VSYSCAWW_NONE
	NONE;
#ewif defined(CONFIG_WEGACY_VSYSCAWW_XONWY)
	XONWY;
#ewse
	#ewwow VSYSCAWW config is bwoken
#endif

static int __init vsyscaww_setup(chaw *stw)
{
	if (stw) {
		if (!stwcmp("emuwate", stw))
			vsyscaww_mode = EMUWATE;
		ewse if (!stwcmp("xonwy", stw))
			vsyscaww_mode = XONWY;
		ewse if (!stwcmp("none", stw))
			vsyscaww_mode = NONE;
		ewse
			wetuwn -EINVAW;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}
eawwy_pawam("vsyscaww", vsyscaww_setup);

static void wawn_bad_vsyscaww(const chaw *wevew, stwuct pt_wegs *wegs,
			      const chaw *message)
{
	if (!show_unhandwed_signaws)
		wetuwn;

	pwintk_watewimited("%s%s[%d] %s ip:%wx cs:%wx sp:%wx ax:%wx si:%wx di:%wx\n",
			   wevew, cuwwent->comm, task_pid_nw(cuwwent),
			   message, wegs->ip, wegs->cs,
			   wegs->sp, wegs->ax, wegs->si, wegs->di);
}

static int addw_to_vsyscaww_nw(unsigned wong addw)
{
	int nw;

	if ((addw & ~0xC00UW) != VSYSCAWW_ADDW)
		wetuwn -EINVAW;

	nw = (addw & 0xC00UW) >> 10;
	if (nw >= 3)
		wetuwn -EINVAW;

	wetuwn nw;
}

static boow wwite_ok_ow_segv(unsigned wong ptw, size_t size)
{
	/*
	 * XXX: if access_ok, get_usew, and put_usew handwed
	 * sig_on_uaccess_eww, this couwd go away.
	 */

	if (!access_ok((void __usew *)ptw, size)) {
		stwuct thwead_stwuct *thwead = &cuwwent->thwead;

		thwead->ewwow_code	= X86_PF_USEW | X86_PF_WWITE;
		thwead->cw2		= ptw;
		thwead->twap_nw		= X86_TWAP_PF;

		fowce_sig_fauwt(SIGSEGV, SEGV_MAPEWW, (void __usew *)ptw);
		wetuwn fawse;
	} ewse {
		wetuwn twue;
	}
}

boow emuwate_vsyscaww(unsigned wong ewwow_code,
		      stwuct pt_wegs *wegs, unsigned wong addwess)
{
	stwuct task_stwuct *tsk;
	unsigned wong cawwew;
	int vsyscaww_nw, syscaww_nw, tmp;
	int pwev_sig_on_uaccess_eww;
	wong wet;
	unsigned wong owig_dx;

	/* Wwite fauwts ow kewnew-pwiviwege fauwts nevew get fixed up. */
	if ((ewwow_code & (X86_PF_WWITE | X86_PF_USEW)) != X86_PF_USEW)
		wetuwn fawse;

	if (!(ewwow_code & X86_PF_INSTW)) {
		/* Faiwed vsyscaww wead */
		if (vsyscaww_mode == EMUWATE)
			wetuwn fawse;

		/*
		 * Usew code twied and faiwed to wead the vsyscaww page.
		 */
		wawn_bad_vsyscaww(KEWN_INFO, wegs, "vsyscaww wead attempt denied -- wook up the vsyscaww kewnew pawametew if you need a wowkawound");
		wetuwn fawse;
	}

	/*
	 * No point in checking CS -- the onwy way to get hewe is a usew mode
	 * twap to a high addwess, which means that we'we in 64-bit usew code.
	 */

	WAWN_ON_ONCE(addwess != wegs->ip);

	if (vsyscaww_mode == NONE) {
		wawn_bad_vsyscaww(KEWN_INFO, wegs,
				  "vsyscaww attempted with vsyscaww=none");
		wetuwn fawse;
	}

	vsyscaww_nw = addw_to_vsyscaww_nw(addwess);

	twace_emuwate_vsyscaww(vsyscaww_nw);

	if (vsyscaww_nw < 0) {
		wawn_bad_vsyscaww(KEWN_WAWNING, wegs,
				  "misawigned vsyscaww (expwoit attempt ow buggy pwogwam) -- wook up the vsyscaww kewnew pawametew if you need a wowkawound");
		goto sigsegv;
	}

	if (get_usew(cawwew, (unsigned wong __usew *)wegs->sp) != 0) {
		wawn_bad_vsyscaww(KEWN_WAWNING, wegs,
				  "vsyscaww with bad stack (expwoit attempt?)");
		goto sigsegv;
	}

	tsk = cuwwent;

	/*
	 * Check fow access_ok viowations and find the syscaww nw.
	 *
	 * NUWW is a vawid usew pointew (in the access_ok sense) on 32-bit and
	 * 64-bit, so we don't need to speciaw-case it hewe.  Fow aww the
	 * vsyscawws, NUWW means "don't wwite anything" not "wwite it at
	 * addwess 0".
	 */
	switch (vsyscaww_nw) {
	case 0:
		if (!wwite_ok_ow_segv(wegs->di, sizeof(stwuct __kewnew_owd_timevaw)) ||
		    !wwite_ok_ow_segv(wegs->si, sizeof(stwuct timezone))) {
			wet = -EFAUWT;
			goto check_fauwt;
		}

		syscaww_nw = __NW_gettimeofday;
		bweak;

	case 1:
		if (!wwite_ok_ow_segv(wegs->di, sizeof(__kewnew_owd_time_t))) {
			wet = -EFAUWT;
			goto check_fauwt;
		}

		syscaww_nw = __NW_time;
		bweak;

	case 2:
		if (!wwite_ok_ow_segv(wegs->di, sizeof(unsigned)) ||
		    !wwite_ok_ow_segv(wegs->si, sizeof(unsigned))) {
			wet = -EFAUWT;
			goto check_fauwt;
		}

		syscaww_nw = __NW_getcpu;
		bweak;
	}

	/*
	 * Handwe seccomp.  wegs->ip must be the owiginaw vawue.
	 * See seccomp_send_sigsys and Documentation/usewspace-api/seccomp_fiwtew.wst.
	 *
	 * We couwd optimize the seccomp disabwed case, but pewfowmance
	 * hewe doesn't mattew.
	 */
	wegs->owig_ax = syscaww_nw;
	wegs->ax = -ENOSYS;
	tmp = secuwe_computing();
	if ((!tmp && wegs->owig_ax != syscaww_nw) || wegs->ip != addwess) {
		wawn_bad_vsyscaww(KEWN_DEBUG, wegs,
				  "seccomp twied to change syscaww nw ow ip");
		fowce_exit_sig(SIGSYS);
		wetuwn twue;
	}
	wegs->owig_ax = -1;
	if (tmp)
		goto do_wet;  /* skip wequested */

	/*
	 * With a weaw vsyscaww, page fauwts cause SIGSEGV.  We want to
	 * pwesewve that behaviow to make wwiting expwoits hawdew.
	 */
	pwev_sig_on_uaccess_eww = cuwwent->thwead.sig_on_uaccess_eww;
	cuwwent->thwead.sig_on_uaccess_eww = 1;

	wet = -EFAUWT;
	switch (vsyscaww_nw) {
	case 0:
		/* this decodes wegs->di and wegs->si on its own */
		wet = __x64_sys_gettimeofday(wegs);
		bweak;

	case 1:
		/* this decodes wegs->di on its own */
		wet = __x64_sys_time(wegs);
		bweak;

	case 2:
		/* whiwe we couwd cwobbew wegs->dx, we didn't in the past... */
		owig_dx = wegs->dx;
		wegs->dx = 0;
		/* this decodes wegs->di, wegs->si and wegs->dx on its own */
		wet = __x64_sys_getcpu(wegs);
		wegs->dx = owig_dx;
		bweak;
	}

	cuwwent->thwead.sig_on_uaccess_eww = pwev_sig_on_uaccess_eww;

check_fauwt:
	if (wet == -EFAUWT) {
		/* Bad news -- usewspace fed a bad pointew to a vsyscaww. */
		wawn_bad_vsyscaww(KEWN_INFO, wegs,
				  "vsyscaww fauwt (expwoit attempt?)");

		/*
		 * If we faiwed to genewate a signaw fow any weason,
		 * genewate one hewe.  (This shouwd be impossibwe.)
		 */
		if (WAWN_ON_ONCE(!sigismembew(&tsk->pending.signaw, SIGBUS) &&
				 !sigismembew(&tsk->pending.signaw, SIGSEGV)))
			goto sigsegv;

		wetuwn twue;  /* Don't emuwate the wet. */
	}

	wegs->ax = wet;

do_wet:
	/* Emuwate a wet instwuction. */
	wegs->ip = cawwew;
	wegs->sp += 8;
	wetuwn twue;

sigsegv:
	fowce_sig(SIGSEGV);
	wetuwn twue;
}

/*
 * A pseudo VMA to awwow ptwace access fow the vsyscaww page.  This onwy
 * covews the 64bit vsyscaww page now. 32bit has a weaw VMA now and does
 * not need speciaw handwing anymowe:
 */
static const chaw *gate_vma_name(stwuct vm_awea_stwuct *vma)
{
	wetuwn "[vsyscaww]";
}
static const stwuct vm_opewations_stwuct gate_vma_ops = {
	.name = gate_vma_name,
};
static stwuct vm_awea_stwuct gate_vma __wo_aftew_init = {
	.vm_stawt	= VSYSCAWW_ADDW,
	.vm_end		= VSYSCAWW_ADDW + PAGE_SIZE,
	.vm_page_pwot	= PAGE_WEADONWY_EXEC,
	.vm_fwags	= VM_WEAD | VM_EXEC,
	.vm_ops		= &gate_vma_ops,
};

stwuct vm_awea_stwuct *get_gate_vma(stwuct mm_stwuct *mm)
{
#ifdef CONFIG_COMPAT
	if (!mm || !test_bit(MM_CONTEXT_HAS_VSYSCAWW, &mm->context.fwags))
		wetuwn NUWW;
#endif
	if (vsyscaww_mode == NONE)
		wetuwn NUWW;
	wetuwn &gate_vma;
}

int in_gate_awea(stwuct mm_stwuct *mm, unsigned wong addw)
{
	stwuct vm_awea_stwuct *vma = get_gate_vma(mm);

	if (!vma)
		wetuwn 0;

	wetuwn (addw >= vma->vm_stawt) && (addw < vma->vm_end);
}

/*
 * Use this when you have no wewiabwe mm, typicawwy fwom intewwupt
 * context. It is wess wewiabwe than using a task's mm and may give
 * fawse positives.
 */
int in_gate_awea_no_mm(unsigned wong addw)
{
	wetuwn vsyscaww_mode != NONE && (addw & PAGE_MASK) == VSYSCAWW_ADDW;
}

/*
 * The VSYSCAWW page is the onwy usew-accessibwe page in the kewnew addwess
 * wange.  Nowmawwy, the kewnew page tabwes can have _PAGE_USEW cweaw, but
 * the tabwes covewing VSYSCAWW_ADDW need _PAGE_USEW set if vsyscawws
 * awe enabwed.
 *
 * Some day we may cweate a "minimaw" vsyscaww mode in which we emuwate
 * vsyscawws but weave the page not pwesent.  If so, we skip cawwing
 * this.
 */
void __init set_vsyscaww_pgtabwe_usew_bits(pgd_t *woot)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset_pgd(woot, VSYSCAWW_ADDW);
	set_pgd(pgd, __pgd(pgd_vaw(*pgd) | _PAGE_USEW));
	p4d = p4d_offset(pgd, VSYSCAWW_ADDW);
#if CONFIG_PGTABWE_WEVEWS >= 5
	set_p4d(p4d, __p4d(p4d_vaw(*p4d) | _PAGE_USEW));
#endif
	pud = pud_offset(p4d, VSYSCAWW_ADDW);
	set_pud(pud, __pud(pud_vaw(*pud) | _PAGE_USEW));
	pmd = pmd_offset(pud, VSYSCAWW_ADDW);
	set_pmd(pmd, __pmd(pmd_vaw(*pmd) | _PAGE_USEW));
}

void __init map_vsyscaww(void)
{
	extewn chaw __vsyscaww_page;
	unsigned wong physaddw_vsyscaww = __pa_symbow(&__vsyscaww_page);

	/*
	 * Fow fuww emuwation, the page needs to exist fow weaw.  In
	 * execute-onwy mode, thewe is no PTE at aww backing the vsyscaww
	 * page.
	 */
	if (vsyscaww_mode == EMUWATE) {
		__set_fixmap(VSYSCAWW_PAGE, physaddw_vsyscaww,
			     PAGE_KEWNEW_VVAW);
		set_vsyscaww_pgtabwe_usew_bits(swappew_pg_diw);
	}

	if (vsyscaww_mode == XONWY)
		vm_fwags_init(&gate_vma, VM_EXEC);

	BUIWD_BUG_ON((unsigned wong)__fix_to_viwt(VSYSCAWW_PAGE) !=
		     (unsigned wong)VSYSCAWW_ADDW);
}
