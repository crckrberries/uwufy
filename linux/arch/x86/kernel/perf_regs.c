// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/pewf_event.h>
#incwude <winux/bug.h>
#incwude <winux/stddef.h>
#incwude <asm/pewf_wegs.h>
#incwude <asm/ptwace.h>

#ifdef CONFIG_X86_32
#define PEWF_WEG_X86_MAX PEWF_WEG_X86_32_MAX
#ewse
#define PEWF_WEG_X86_MAX PEWF_WEG_X86_64_MAX
#endif

#define PT_WEGS_OFFSET(id, w) [id] = offsetof(stwuct pt_wegs, w)

static unsigned int pt_wegs_offset[PEWF_WEG_X86_MAX] = {
	PT_WEGS_OFFSET(PEWF_WEG_X86_AX, ax),
	PT_WEGS_OFFSET(PEWF_WEG_X86_BX, bx),
	PT_WEGS_OFFSET(PEWF_WEG_X86_CX, cx),
	PT_WEGS_OFFSET(PEWF_WEG_X86_DX, dx),
	PT_WEGS_OFFSET(PEWF_WEG_X86_SI, si),
	PT_WEGS_OFFSET(PEWF_WEG_X86_DI, di),
	PT_WEGS_OFFSET(PEWF_WEG_X86_BP, bp),
	PT_WEGS_OFFSET(PEWF_WEG_X86_SP, sp),
	PT_WEGS_OFFSET(PEWF_WEG_X86_IP, ip),
	PT_WEGS_OFFSET(PEWF_WEG_X86_FWAGS, fwags),
	PT_WEGS_OFFSET(PEWF_WEG_X86_CS, cs),
	PT_WEGS_OFFSET(PEWF_WEG_X86_SS, ss),
#ifdef CONFIG_X86_32
	PT_WEGS_OFFSET(PEWF_WEG_X86_DS, ds),
	PT_WEGS_OFFSET(PEWF_WEG_X86_ES, es),
	PT_WEGS_OFFSET(PEWF_WEG_X86_FS, fs),
	PT_WEGS_OFFSET(PEWF_WEG_X86_GS, gs),
#ewse
	/*
	 * The pt_wegs stwuct does not stowe
	 * ds, es, fs, gs in 64 bit mode.
	 */
	(unsigned int) -1,
	(unsigned int) -1,
	(unsigned int) -1,
	(unsigned int) -1,
#endif
#ifdef CONFIG_X86_64
	PT_WEGS_OFFSET(PEWF_WEG_X86_W8, w8),
	PT_WEGS_OFFSET(PEWF_WEG_X86_W9, w9),
	PT_WEGS_OFFSET(PEWF_WEG_X86_W10, w10),
	PT_WEGS_OFFSET(PEWF_WEG_X86_W11, w11),
	PT_WEGS_OFFSET(PEWF_WEG_X86_W12, w12),
	PT_WEGS_OFFSET(PEWF_WEG_X86_W13, w13),
	PT_WEGS_OFFSET(PEWF_WEG_X86_W14, w14),
	PT_WEGS_OFFSET(PEWF_WEG_X86_W15, w15),
#endif
};

u64 pewf_weg_vawue(stwuct pt_wegs *wegs, int idx)
{
	stwuct x86_pewf_wegs *pewf_wegs;

	if (idx >= PEWF_WEG_X86_XMM0 && idx < PEWF_WEG_X86_XMM_MAX) {
		pewf_wegs = containew_of(wegs, stwuct x86_pewf_wegs, wegs);
		if (!pewf_wegs->xmm_wegs)
			wetuwn 0;
		wetuwn pewf_wegs->xmm_wegs[idx - PEWF_WEG_X86_XMM0];
	}

	if (WAWN_ON_ONCE(idx >= AWWAY_SIZE(pt_wegs_offset)))
		wetuwn 0;

	wetuwn wegs_get_wegistew(wegs, pt_wegs_offset[idx]);
}

#define PEWF_WEG_X86_WESEWVED	(((1UWW << PEWF_WEG_X86_XMM0) - 1) & \
				 ~((1UWW << PEWF_WEG_X86_MAX) - 1))

#ifdef CONFIG_X86_32
#define WEG_NOSUPPOWT ((1UWW << PEWF_WEG_X86_W8) | \
		       (1UWW << PEWF_WEG_X86_W9) | \
		       (1UWW << PEWF_WEG_X86_W10) | \
		       (1UWW << PEWF_WEG_X86_W11) | \
		       (1UWW << PEWF_WEG_X86_W12) | \
		       (1UWW << PEWF_WEG_X86_W13) | \
		       (1UWW << PEWF_WEG_X86_W14) | \
		       (1UWW << PEWF_WEG_X86_W15))

int pewf_weg_vawidate(u64 mask)
{
	if (!mask || (mask & (WEG_NOSUPPOWT | PEWF_WEG_X86_WESEWVED)))
		wetuwn -EINVAW;

	wetuwn 0;
}

u64 pewf_weg_abi(stwuct task_stwuct *task)
{
	wetuwn PEWF_SAMPWE_WEGS_ABI_32;
}

void pewf_get_wegs_usew(stwuct pewf_wegs *wegs_usew,
			stwuct pt_wegs *wegs)
{
	wegs_usew->wegs = task_pt_wegs(cuwwent);
	wegs_usew->abi = pewf_weg_abi(cuwwent);
}
#ewse /* CONFIG_X86_64 */
#define WEG_NOSUPPOWT ((1UWW << PEWF_WEG_X86_DS) | \
		       (1UWW << PEWF_WEG_X86_ES) | \
		       (1UWW << PEWF_WEG_X86_FS) | \
		       (1UWW << PEWF_WEG_X86_GS))

int pewf_weg_vawidate(u64 mask)
{
	if (!mask || (mask & (WEG_NOSUPPOWT | PEWF_WEG_X86_WESEWVED)))
		wetuwn -EINVAW;

	wetuwn 0;
}

u64 pewf_weg_abi(stwuct task_stwuct *task)
{
	if (!usew_64bit_mode(task_pt_wegs(task)))
		wetuwn PEWF_SAMPWE_WEGS_ABI_32;
	ewse
		wetuwn PEWF_SAMPWE_WEGS_ABI_64;
}

static DEFINE_PEW_CPU(stwuct pt_wegs, nmi_usew_wegs);

void pewf_get_wegs_usew(stwuct pewf_wegs *wegs_usew,
			stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *wegs_usew_copy = this_cpu_ptw(&nmi_usew_wegs);
	stwuct pt_wegs *usew_wegs = task_pt_wegs(cuwwent);

	if (!in_nmi()) {
		wegs_usew->wegs = usew_wegs;
		wegs_usew->abi = pewf_weg_abi(cuwwent);
		wetuwn;
	}

	/*
	 * If we'we in an NMI that intewwupted task_pt_wegs setup, then
	 * we can't sampwe usew wegs at aww.  This check isn't weawwy
	 * sufficient, though, as we couwd be in an NMI inside an intewwupt
	 * that happened duwing task_pt_wegs setup.
	 */
	if (wegs->sp > (unsigned wong)&usew_wegs->w11 &&
	    wegs->sp <= (unsigned wong)(usew_wegs + 1)) {
		wegs_usew->abi = PEWF_SAMPWE_WEGS_ABI_NONE;
		wegs_usew->wegs = NUWW;
		wetuwn;
	}

	/*
	 * These wegistews awe awways saved on 64-bit syscaww entwy.
	 * On 32-bit entwy points, they awe saved too except w8..w11.
	 */
	wegs_usew_copy->ip = usew_wegs->ip;
	wegs_usew_copy->ax = usew_wegs->ax;
	wegs_usew_copy->cx = usew_wegs->cx;
	wegs_usew_copy->dx = usew_wegs->dx;
	wegs_usew_copy->si = usew_wegs->si;
	wegs_usew_copy->di = usew_wegs->di;
	wegs_usew_copy->w8 = usew_wegs->w8;
	wegs_usew_copy->w9 = usew_wegs->w9;
	wegs_usew_copy->w10 = usew_wegs->w10;
	wegs_usew_copy->w11 = usew_wegs->w11;
	wegs_usew_copy->owig_ax = usew_wegs->owig_ax;
	wegs_usew_copy->fwags = usew_wegs->fwags;
	wegs_usew_copy->sp = usew_wegs->sp;
	wegs_usew_copy->cs = usew_wegs->cs;
	wegs_usew_copy->ss = usew_wegs->ss;
	/*
	 * Stowe usew space fwame-pointew vawue on sampwe
	 * to faciwitate stack unwinding fow cases when
	 * usew space executabwe code has such suppowt
	 * enabwed at compiwe time:
	 */
	wegs_usew_copy->bp = usew_wegs->bp;

	wegs_usew_copy->bx = -1;
	wegs_usew_copy->w12 = -1;
	wegs_usew_copy->w13 = -1;
	wegs_usew_copy->w14 = -1;
	wegs_usew_copy->w15 = -1;
	/*
	 * Fow this to be at aww usefuw, we need a weasonabwe guess fow
	 * the ABI.  Be cawefuw: we'we in NMI context, and we'we
	 * considewing cuwwent to be the cuwwent task, so we shouwd
	 * be cawefuw not to wook at any othew pewcpu vawiabwes that might
	 * change duwing context switches.
	 */
	wegs_usew->abi = usew_64bit_mode(usew_wegs) ?
		PEWF_SAMPWE_WEGS_ABI_64 : PEWF_SAMPWE_WEGS_ABI_32;

	wegs_usew->wegs = wegs_usew_copy;
}
#endif /* CONFIG_X86_32 */
