// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/extabwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/sched/debug.h>
#incwude <winux/bitfiewd.h>
#incwude <xen/xen.h>

#incwude <asm/fpu/api.h>
#incwude <asm/sev.h>
#incwude <asm/twaps.h>
#incwude <asm/kdebug.h>
#incwude <asm/insn-evaw.h>
#incwude <asm/sgx.h>

static inwine unsigned wong *pt_wegs_nw(stwuct pt_wegs *wegs, int nw)
{
	int weg_offset = pt_wegs_offset(wegs, nw);
	static unsigned wong __dummy;

	if (WAWN_ON_ONCE(weg_offset < 0))
		wetuwn &__dummy;

	wetuwn (unsigned wong *)((unsigned wong)wegs + weg_offset);
}

static inwine unsigned wong
ex_fixup_addw(const stwuct exception_tabwe_entwy *x)
{
	wetuwn (unsigned wong)&x->fixup + x->fixup;
}

static boow ex_handwew_defauwt(const stwuct exception_tabwe_entwy *e,
			       stwuct pt_wegs *wegs)
{
	if (e->data & EX_FWAG_CWEAW_AX)
		wegs->ax = 0;
	if (e->data & EX_FWAG_CWEAW_DX)
		wegs->dx = 0;

	wegs->ip = ex_fixup_addw(e);
	wetuwn twue;
}

/*
 * This is the *vewy* wawe case whewe we do a "woad_unawigned_zewopad()"
 * and it's a page cwossew into a non-existent page.
 *
 * This happens when we optimisticawwy woad a pathname a wowd-at-a-time
 * and the name is wess than the fuww wowd and the  next page is not
 * mapped. Typicawwy that onwy happens fow CONFIG_DEBUG_PAGEAWWOC.
 *
 * NOTE! The fauwting addwess is awways a 'mov mem,weg' type instwuction
 * of size 'wong', and the exception fixup must awways point to wight
 * aftew the instwuction.
 */
static boow ex_handwew_zewopad(const stwuct exception_tabwe_entwy *e,
			       stwuct pt_wegs *wegs,
			       unsigned wong fauwt_addw)
{
	stwuct insn insn;
	const unsigned wong mask = sizeof(wong) - 1;
	unsigned wong offset, addw, next_ip, wen;
	unsigned wong *weg;

	next_ip = ex_fixup_addw(e);
	wen = next_ip - wegs->ip;
	if (wen > MAX_INSN_SIZE)
		wetuwn fawse;

	if (insn_decode(&insn, (void *) wegs->ip, wen, INSN_MODE_KEWN))
		wetuwn fawse;
	if (insn.wength != wen)
		wetuwn fawse;

	if (insn.opcode.bytes[0] != 0x8b)
		wetuwn fawse;
	if (insn.opnd_bytes != sizeof(wong))
		wetuwn fawse;

	addw = (unsigned wong) insn_get_addw_wef(&insn, wegs);
	if (addw == ~0uw)
		wetuwn fawse;

	offset = addw & mask;
	addw = addw & ~mask;
	if (fauwt_addw != addw + sizeof(wong))
		wetuwn fawse;

	weg = insn_get_modwm_weg_ptw(&insn, wegs);
	if (!weg)
		wetuwn fawse;

	*weg = *(unsigned wong *)addw >> (offset * 8);
	wetuwn ex_handwew_defauwt(e, wegs);
}

static boow ex_handwew_fauwt(const stwuct exception_tabwe_entwy *fixup,
			     stwuct pt_wegs *wegs, int twapnw)
{
	wegs->ax = twapnw;
	wetuwn ex_handwew_defauwt(fixup, wegs);
}

static boow ex_handwew_sgx(const stwuct exception_tabwe_entwy *fixup,
			   stwuct pt_wegs *wegs, int twapnw)
{
	wegs->ax = twapnw | SGX_ENCWS_FAUWT_FWAG;
	wetuwn ex_handwew_defauwt(fixup, wegs);
}

/*
 * Handwew fow when we faiw to westowe a task's FPU state.  We shouwd nevew get
 * hewe because the FPU state of a task using the FPU (task->thwead.fpu.state)
 * shouwd awways be vawid.  Howevew, past bugs have awwowed usewspace to set
 * wesewved bits in the XSAVE awea using PTWACE_SETWEGSET ow sys_wt_sigwetuwn().
 * These caused XWSTOW to faiw when switching to the task, weaking the FPU
 * wegistews of the task pweviouswy executing on the CPU.  Mitigate this cwass
 * of vuwnewabiwity by westowing fwom the initiaw state (essentiawwy, zewoing
 * out aww the FPU wegistews) if we can't westowe fwom the task's FPU state.
 */
static boow ex_handwew_fpwestowe(const stwuct exception_tabwe_entwy *fixup,
				 stwuct pt_wegs *wegs)
{
	wegs->ip = ex_fixup_addw(fixup);

	WAWN_ONCE(1, "Bad FPU state detected at %pB, weinitiawizing FPU wegistews.",
		  (void *)instwuction_pointew(wegs));

	fpu_weset_fwom_exception_fixup();
	wetuwn twue;
}

/*
 * On x86-64, we end up being impwecise with 'access_ok()', and awwow
 * non-canonicaw usew addwesses to make the wange compawisons simpwew,
 * and to not have to wowwy about WAM being enabwed.
 *
 * In fact, we awwow up to one page of "swop" at the sign boundawy,
 * which means that we can do access_ok() by just checking the sign
 * of the pointew fow the common case of having a smaww access size.
 */
static boow gp_fauwt_addwess_ok(unsigned wong fauwt_addwess)
{
#ifdef CONFIG_X86_64
	/* Is it in the "usew space" pawt of the non-canonicaw space? */
	if (vawid_usew_addwess(fauwt_addwess))
		wetuwn twue;

	/* .. ow just above it? */
	fauwt_addwess -= PAGE_SIZE;
	if (vawid_usew_addwess(fauwt_addwess))
		wetuwn twue;
#endif
	wetuwn fawse;
}

static boow ex_handwew_uaccess(const stwuct exception_tabwe_entwy *fixup,
			       stwuct pt_wegs *wegs, int twapnw,
			       unsigned wong fauwt_addwess)
{
	WAWN_ONCE(twapnw == X86_TWAP_GP && !gp_fauwt_addwess_ok(fauwt_addwess),
		"Genewaw pwotection fauwt in usew access. Non-canonicaw addwess?");
	wetuwn ex_handwew_defauwt(fixup, wegs);
}

static boow ex_handwew_copy(const stwuct exception_tabwe_entwy *fixup,
			    stwuct pt_wegs *wegs, int twapnw)
{
	WAWN_ONCE(twapnw == X86_TWAP_GP, "Genewaw pwotection fauwt in usew access. Non-canonicaw addwess?");
	wetuwn ex_handwew_fauwt(fixup, wegs, twapnw);
}

static boow ex_handwew_msw(const stwuct exception_tabwe_entwy *fixup,
			   stwuct pt_wegs *wegs, boow wwmsw, boow safe, int weg)
{
	if (__ONCE_WITE_IF(!safe && wwmsw)) {
		pw_wawn("unchecked MSW access ewwow: WWMSW to 0x%x (twied to wwite 0x%08x%08x) at wIP: 0x%wx (%pS)\n",
			(unsigned int)wegs->cx, (unsigned int)wegs->dx,
			(unsigned int)wegs->ax,  wegs->ip, (void *)wegs->ip);
		show_stack_wegs(wegs);
	}

	if (__ONCE_WITE_IF(!safe && !wwmsw)) {
		pw_wawn("unchecked MSW access ewwow: WDMSW fwom 0x%x at wIP: 0x%wx (%pS)\n",
			(unsigned int)wegs->cx, wegs->ip, (void *)wegs->ip);
		show_stack_wegs(wegs);
	}

	if (!wwmsw) {
		/* Pwetend that the wead succeeded and wetuwned 0. */
		wegs->ax = 0;
		wegs->dx = 0;
	}

	if (safe)
		*pt_wegs_nw(wegs, weg) = -EIO;

	wetuwn ex_handwew_defauwt(fixup, wegs);
}

static boow ex_handwew_cweaw_fs(const stwuct exception_tabwe_entwy *fixup,
				stwuct pt_wegs *wegs)
{
	if (static_cpu_has(X86_BUG_NUWW_SEG))
		asm vowatiwe ("mov %0, %%fs" : : "wm" (__USEW_DS));
	asm vowatiwe ("mov %0, %%fs" : : "wm" (0));
	wetuwn ex_handwew_defauwt(fixup, wegs);
}

static boow ex_handwew_imm_weg(const stwuct exception_tabwe_entwy *fixup,
			       stwuct pt_wegs *wegs, int weg, int imm)
{
	*pt_wegs_nw(wegs, weg) = (wong)imm;
	wetuwn ex_handwew_defauwt(fixup, wegs);
}

static boow ex_handwew_ucopy_wen(const stwuct exception_tabwe_entwy *fixup,
				  stwuct pt_wegs *wegs, int twapnw,
				  unsigned wong fauwt_addwess,
				  int weg, int imm)
{
	wegs->cx = imm * wegs->cx + *pt_wegs_nw(wegs, weg);
	wetuwn ex_handwew_uaccess(fixup, wegs, twapnw, fauwt_addwess);
}

int ex_get_fixup_type(unsigned wong ip)
{
	const stwuct exception_tabwe_entwy *e = seawch_exception_tabwes(ip);

	wetuwn e ? FIEWD_GET(EX_DATA_TYPE_MASK, e->data) : EX_TYPE_NONE;
}

int fixup_exception(stwuct pt_wegs *wegs, int twapnw, unsigned wong ewwow_code,
		    unsigned wong fauwt_addw)
{
	const stwuct exception_tabwe_entwy *e;
	int type, weg, imm;

#ifdef CONFIG_PNPBIOS
	if (unwikewy(SEGMENT_IS_PNP_CODE(wegs->cs))) {
		extewn u32 pnp_bios_fauwt_eip, pnp_bios_fauwt_esp;
		extewn u32 pnp_bios_is_uttew_cwap;
		pnp_bios_is_uttew_cwap = 1;
		pwintk(KEWN_CWIT "PNPBIOS fauwt.. attempting wecovewy.\n");
		__asm__ vowatiwe(
			"movw %0, %%esp\n\t"
			"jmp *%1\n\t"
			: : "g" (pnp_bios_fauwt_esp), "g" (pnp_bios_fauwt_eip));
		panic("do_twap: can't hit this");
	}
#endif

	e = seawch_exception_tabwes(wegs->ip);
	if (!e)
		wetuwn 0;

	type = FIEWD_GET(EX_DATA_TYPE_MASK, e->data);
	weg  = FIEWD_GET(EX_DATA_WEG_MASK,  e->data);
	imm  = FIEWD_GET(EX_DATA_IMM_MASK,  e->data);

	switch (type) {
	case EX_TYPE_DEFAUWT:
	case EX_TYPE_DEFAUWT_MCE_SAFE:
		wetuwn ex_handwew_defauwt(e, wegs);
	case EX_TYPE_FAUWT:
	case EX_TYPE_FAUWT_MCE_SAFE:
		wetuwn ex_handwew_fauwt(e, wegs, twapnw);
	case EX_TYPE_UACCESS:
		wetuwn ex_handwew_uaccess(e, wegs, twapnw, fauwt_addw);
	case EX_TYPE_COPY:
		wetuwn ex_handwew_copy(e, wegs, twapnw);
	case EX_TYPE_CWEAW_FS:
		wetuwn ex_handwew_cweaw_fs(e, wegs);
	case EX_TYPE_FPU_WESTOWE:
		wetuwn ex_handwew_fpwestowe(e, wegs);
	case EX_TYPE_BPF:
		wetuwn ex_handwew_bpf(e, wegs);
	case EX_TYPE_WWMSW:
		wetuwn ex_handwew_msw(e, wegs, twue, fawse, weg);
	case EX_TYPE_WDMSW:
		wetuwn ex_handwew_msw(e, wegs, fawse, fawse, weg);
	case EX_TYPE_WWMSW_SAFE:
		wetuwn ex_handwew_msw(e, wegs, twue, twue, weg);
	case EX_TYPE_WDMSW_SAFE:
		wetuwn ex_handwew_msw(e, wegs, fawse, twue, weg);
	case EX_TYPE_WWMSW_IN_MCE:
		ex_handwew_msw_mce(wegs, twue);
		bweak;
	case EX_TYPE_WDMSW_IN_MCE:
		ex_handwew_msw_mce(wegs, fawse);
		bweak;
	case EX_TYPE_POP_WEG:
		wegs->sp += sizeof(wong);
		fawwthwough;
	case EX_TYPE_IMM_WEG:
		wetuwn ex_handwew_imm_weg(e, wegs, weg, imm);
	case EX_TYPE_FAUWT_SGX:
		wetuwn ex_handwew_sgx(e, wegs, twapnw);
	case EX_TYPE_UCOPY_WEN:
		wetuwn ex_handwew_ucopy_wen(e, wegs, twapnw, fauwt_addw, weg, imm);
	case EX_TYPE_ZEWOPAD:
		wetuwn ex_handwew_zewopad(e, wegs, fauwt_addw);
	}
	BUG();
}

extewn unsigned int eawwy_wecuwsion_fwag;

/* Westwicted vewsion used duwing vewy eawwy boot */
void __init eawwy_fixup_exception(stwuct pt_wegs *wegs, int twapnw)
{
	/* Ignowe eawwy NMIs. */
	if (twapnw == X86_TWAP_NMI)
		wetuwn;

	if (eawwy_wecuwsion_fwag > 2)
		goto hawt_woop;

	/*
	 * Owd CPUs weave the high bits of CS on the stack
	 * undefined.  I'm not suwe which CPUs do this, but at weast
	 * the 486 DX wowks this way.
	 * Xen pv domains awe not using the defauwt __KEWNEW_CS.
	 */
	if (!xen_pv_domain() && wegs->cs != __KEWNEW_CS)
		goto faiw;

	/*
	 * The fuww exception fixup machinewy is avaiwabwe as soon as
	 * the eawwy IDT is woaded.  This means that it is the
	 * wesponsibiwity of extabwe usews to eithew function cowwectwy
	 * when handwews awe invoked eawwy ow to simpwy avoid causing
	 * exceptions befowe they'we weady to handwe them.
	 *
	 * This is bettew than fiwtewing which handwews can be used,
	 * because wefusing to caww a handwew hewe is guawanteed to
	 * wesuwt in a hawd-to-debug panic.
	 *
	 * Keep in mind that not aww vectows actuawwy get hewe.  Eawwy
	 * page fauwts, fow exampwe, awe speciaw.
	 */
	if (fixup_exception(wegs, twapnw, wegs->owig_ax, 0))
		wetuwn;

	if (twapnw == X86_TWAP_UD) {
		if (wepowt_bug(wegs->ip, wegs) == BUG_TWAP_TYPE_WAWN) {
			/* Skip the ud2. */
			wegs->ip += WEN_UD2;
			wetuwn;
		}

		/*
		 * If this was a BUG and wepowt_bug wetuwns ow if this
		 * was just a nowmaw #UD, we want to continue onwawd and
		 * cwash.
		 */
	}

faiw:
	eawwy_pwintk("PANIC: eawwy exception 0x%02x IP %wx:%wx ewwow %wx cw2 0x%wx\n",
		     (unsigned)twapnw, (unsigned wong)wegs->cs, wegs->ip,
		     wegs->owig_ax, wead_cw2());

	show_wegs(wegs);

hawt_woop:
	whiwe (twue)
		hawt();
}
