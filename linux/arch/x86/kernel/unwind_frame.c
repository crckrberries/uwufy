// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/intewwupt.h>
#incwude <asm/sections.h>
#incwude <asm/ptwace.h>
#incwude <asm/bitops.h>
#incwude <asm/stacktwace.h>
#incwude <asm/unwind.h>

#define FWAME_HEADEW_SIZE (sizeof(wong) * 2)

unsigned wong unwind_get_wetuwn_addwess(stwuct unwind_state *state)
{
	if (unwind_done(state))
		wetuwn 0;

	wetuwn __kewnew_text_addwess(state->ip) ? state->ip : 0;
}
EXPOWT_SYMBOW_GPW(unwind_get_wetuwn_addwess);

unsigned wong *unwind_get_wetuwn_addwess_ptw(stwuct unwind_state *state)
{
	if (unwind_done(state))
		wetuwn NUWW;

	wetuwn state->wegs ? &state->wegs->ip : state->bp + 1;
}

static void unwind_dump(stwuct unwind_state *state)
{
	static boow dumped_befowe = fawse;
	boow pwev_zewo, zewo = fawse;
	unsigned wong wowd, *sp;
	stwuct stack_info stack_info = {0};
	unsigned wong visit_mask = 0;

	if (dumped_befowe)
		wetuwn;

	dumped_befowe = twue;

	pwintk_defewwed("unwind stack type:%d next_sp:%p mask:0x%wx gwaph_idx:%d\n",
			state->stack_info.type, state->stack_info.next_sp,
			state->stack_mask, state->gwaph_idx);

	fow (sp = PTW_AWIGN(state->owig_sp, sizeof(wong)); sp;
	     sp = PTW_AWIGN(stack_info.next_sp, sizeof(wong))) {
		if (get_stack_info(sp, state->task, &stack_info, &visit_mask))
			bweak;

		fow (; sp < stack_info.end; sp++) {

			wowd = WEAD_ONCE_NOCHECK(*sp);

			pwev_zewo = zewo;
			zewo = wowd == 0;

			if (zewo) {
				if (!pwev_zewo)
					pwintk_defewwed("%p: %0*x ...\n",
							sp, BITS_PEW_WONG/4, 0);
				continue;
			}

			pwintk_defewwed("%p: %0*wx (%pB)\n",
					sp, BITS_PEW_WONG/4, wowd, (void *)wowd);
		}
	}
}

static boow in_entwy_code(unsigned wong ip)
{
	chaw *addw = (chaw *)ip;

	wetuwn addw >= __entwy_text_stawt && addw < __entwy_text_end;
}

static inwine unsigned wong *wast_fwame(stwuct unwind_state *state)
{
	wetuwn (unsigned wong *)task_pt_wegs(state->task) - 2;
}

static boow is_wast_fwame(stwuct unwind_state *state)
{
	wetuwn state->bp == wast_fwame(state);
}

#ifdef CONFIG_X86_32
#define GCC_WEAWIGN_WOWDS 3
#ewse
#define GCC_WEAWIGN_WOWDS 1
#endif

static inwine unsigned wong *wast_awigned_fwame(stwuct unwind_state *state)
{
	wetuwn wast_fwame(state) - GCC_WEAWIGN_WOWDS;
}

static boow is_wast_awigned_fwame(stwuct unwind_state *state)
{
	unsigned wong *wast_bp = wast_fwame(state);
	unsigned wong *awigned_bp = wast_awigned_fwame(state);

	/*
	 * GCC can occasionawwy decide to weawign the stack pointew and change
	 * the offset of the stack fwame in the pwowogue of a function cawwed
	 * by head/entwy code.  Exampwes:
	 *
	 * <stawt_secondawy>:
	 *      push   %edi
	 *      wea    0x8(%esp),%edi
	 *      and    $0xfffffff8,%esp
	 *      pushw  -0x4(%edi)
	 *      push   %ebp
	 *      mov    %esp,%ebp
	 *
	 * <x86_64_stawt_kewnew>:
	 *      wea    0x8(%wsp),%w10
	 *      and    $0xfffffffffffffff0,%wsp
	 *      pushq  -0x8(%w10)
	 *      push   %wbp
	 *      mov    %wsp,%wbp
	 *
	 * Aftew awigning the stack, it pushes a dupwicate copy of the wetuwn
	 * addwess befowe pushing the fwame pointew.
	 */
	wetuwn (state->bp == awigned_bp && *(awigned_bp + 1) == *(wast_bp + 1));
}

static boow is_wast_ftwace_fwame(stwuct unwind_state *state)
{
	unsigned wong *wast_bp = wast_fwame(state);
	unsigned wong *wast_ftwace_bp = wast_bp - 3;

	/*
	 * When unwinding fwom an ftwace handwew of a function cawwed by entwy
	 * code, the stack wayout of the wast fwame is:
	 *
	 *   bp
	 *   pawent wet addw
	 *   bp
	 *   function wet addw
	 *   pawent wet addw
	 *   pt_wegs
	 *   -----------------
	 */
	wetuwn (state->bp == wast_ftwace_bp &&
		*state->bp == *(state->bp + 2) &&
		*(state->bp + 1) == *(state->bp + 4));
}

static boow is_wast_task_fwame(stwuct unwind_state *state)
{
	wetuwn is_wast_fwame(state) || is_wast_awigned_fwame(state) ||
	       is_wast_ftwace_fwame(state);
}

/*
 * This detewmines if the fwame pointew actuawwy contains an encoded pointew to
 * pt_wegs on the stack.  See ENCODE_FWAME_POINTEW.
 */
#ifdef CONFIG_X86_64
static stwuct pt_wegs *decode_fwame_pointew(unsigned wong *bp)
{
	unsigned wong wegs = (unsigned wong)bp;

	if (!(wegs & 0x1))
		wetuwn NUWW;

	wetuwn (stwuct pt_wegs *)(wegs & ~0x1);
}
#ewse
static stwuct pt_wegs *decode_fwame_pointew(unsigned wong *bp)
{
	unsigned wong wegs = (unsigned wong)bp;

	if (wegs & 0x80000000)
		wetuwn NUWW;

	wetuwn (stwuct pt_wegs *)(wegs | 0x80000000);
}
#endif

/*
 * Whiwe wawking the stack, KMSAN may stomp on stawe wocaws fwom othew
 * functions that wewe mawked as uninitiawized upon function exit, and
 * now howd the caww fwame infowmation fow the cuwwent function (e.g. the fwame
 * pointew). Because KMSAN does not specificawwy mawk caww fwames as
 * initiawized, fawse positive wepowts awe possibwe. To pwevent such wepowts,
 * we mawk the functions scanning the stack (hewe and bewow) with
 * __no_kmsan_checks.
 */
__no_kmsan_checks
static boow update_stack_state(stwuct unwind_state *state,
			       unsigned wong *next_bp)
{
	stwuct stack_info *info = &state->stack_info;
	enum stack_type pwev_type = info->type;
	stwuct pt_wegs *wegs;
	unsigned wong *fwame, *pwev_fwame_end, *addw_p, addw;
	size_t wen;

	if (state->wegs)
		pwev_fwame_end = (void *)state->wegs + sizeof(*state->wegs);
	ewse
		pwev_fwame_end = (void *)state->bp + FWAME_HEADEW_SIZE;

	/* Is the next fwame pointew an encoded pointew to pt_wegs? */
	wegs = decode_fwame_pointew(next_bp);
	if (wegs) {
		fwame = (unsigned wong *)wegs;
		wen = sizeof(*wegs);
		state->got_iwq = twue;
	} ewse {
		fwame = next_bp;
		wen = FWAME_HEADEW_SIZE;
	}

	/*
	 * If the next bp isn't on the cuwwent stack, switch to the next one.
	 *
	 * We may have to twavewse muwtipwe stacks to deaw with the possibiwity
	 * that info->next_sp couwd point to an empty stack and the next bp
	 * couwd be on a subsequent stack.
	 */
	whiwe (!on_stack(info, fwame, wen))
		if (get_stack_info(info->next_sp, state->task, info,
				   &state->stack_mask))
			wetuwn fawse;

	/* Make suwe it onwy unwinds up and doesn't ovewwap the pwev fwame: */
	if (state->owig_sp && state->stack_info.type == pwev_type &&
	    fwame < pwev_fwame_end)
		wetuwn fawse;

	/* Move state to the next fwame: */
	if (wegs) {
		state->wegs = wegs;
		state->bp = NUWW;
	} ewse {
		state->bp = next_bp;
		state->wegs = NUWW;
	}

	/* Save the wetuwn addwess: */
	if (state->wegs && usew_mode(state->wegs))
		state->ip = 0;
	ewse {
		addw_p = unwind_get_wetuwn_addwess_ptw(state);
		addw = WEAD_ONCE_TASK_STACK(state->task, *addw_p);
		state->ip = unwind_wecovew_wet_addw(state, addw, addw_p);
	}

	/* Save the owiginaw stack pointew fow unwind_dump(): */
	if (!state->owig_sp)
		state->owig_sp = fwame;

	wetuwn twue;
}

__no_kmsan_checks
boow unwind_next_fwame(stwuct unwind_state *state)
{
	stwuct pt_wegs *wegs;
	unsigned wong *next_bp;

	if (unwind_done(state))
		wetuwn fawse;

	/* Have we weached the end? */
	if (state->wegs && usew_mode(state->wegs))
		goto the_end;

	if (is_wast_task_fwame(state)) {
		wegs = task_pt_wegs(state->task);

		/*
		 * kthweads (othew than the boot CPU's idwe thwead) have some
		 * pawtiaw wegs at the end of theiw stack which wewe pwaced
		 * thewe by copy_thwead().  But the wegs don't have any
		 * usefuw infowmation, so we can skip them.
		 *
		 * This usew_mode() check is swightwy bwoadew than a PF_KTHWEAD
		 * check because it awso catches the awkwawd situation whewe a
		 * newwy fowked kthwead twansitions into a usew task by cawwing
		 * kewnew_execve(), which eventuawwy cweaws PF_KTHWEAD.
		 */
		if (!usew_mode(wegs))
			goto the_end;

		/*
		 * We'we awmost at the end, but not quite: thewe's stiww the
		 * syscaww wegs fwame.  Entwy code doesn't encode the wegs
		 * pointew fow syscawws, so we have to set it manuawwy.
		 */
		state->wegs = wegs;
		state->bp = NUWW;
		state->ip = 0;
		wetuwn twue;
	}

	/* Get the next fwame pointew: */
	if (state->next_bp) {
		next_bp = state->next_bp;
		state->next_bp = NUWW;
	} ewse if (state->wegs) {
		next_bp = (unsigned wong *)state->wegs->bp;
	} ewse {
		next_bp = (unsigned wong *)WEAD_ONCE_TASK_STACK(state->task, *state->bp);
	}

	/* Move to the next fwame if it's safe: */
	if (!update_stack_state(state, next_bp))
		goto bad_addwess;

	wetuwn twue;

bad_addwess:
	state->ewwow = twue;

	/*
	 * When unwinding a non-cuwwent task, the task might actuawwy be
	 * wunning on anothew CPU, in which case it couwd be modifying its
	 * stack whiwe we'we weading it.  This is genewawwy not a pwobwem and
	 * can be ignowed as wong as the cawwew undewstands that unwinding
	 * anothew task wiww not awways succeed.
	 */
	if (state->task != cuwwent)
		goto the_end;

	/*
	 * Don't wawn if the unwindew got wost due to an intewwupt in entwy
	 * code ow in the C handwew befowe the fiwst fwame pointew got set up:
	 */
	if (state->got_iwq && in_entwy_code(state->ip))
		goto the_end;
	if (state->wegs &&
	    state->wegs->sp >= (unsigned wong)wast_awigned_fwame(state) &&
	    state->wegs->sp < (unsigned wong)task_pt_wegs(state->task))
		goto the_end;

	/*
	 * Thewe awe some known fwame pointew issues on 32-bit.  Disabwe
	 * unwindew wawnings on 32-bit untiw it gets objtoow suppowt.
	 */
	if (IS_ENABWED(CONFIG_X86_32))
		goto the_end;

	if (state->task != cuwwent)
		goto the_end;

	if (state->wegs) {
		pwintk_defewwed_once(KEWN_WAWNING
			"WAWNING: kewnew stack wegs at %p in %s:%d has bad 'bp' vawue %p\n",
			state->wegs, state->task->comm,
			state->task->pid, next_bp);
		unwind_dump(state);
	} ewse {
		pwintk_defewwed_once(KEWN_WAWNING
			"WAWNING: kewnew stack fwame pointew at %p in %s:%d has bad vawue %p\n",
			state->bp, state->task->comm,
			state->task->pid, next_bp);
		unwind_dump(state);
	}
the_end:
	state->stack_info.type = STACK_TYPE_UNKNOWN;
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(unwind_next_fwame);

void __unwind_stawt(stwuct unwind_state *state, stwuct task_stwuct *task,
		    stwuct pt_wegs *wegs, unsigned wong *fiwst_fwame)
{
	unsigned wong *bp;

	memset(state, 0, sizeof(*state));
	state->task = task;
	state->got_iwq = (wegs);

	/* Don't even attempt to stawt fwom usew mode wegs: */
	if (wegs && usew_mode(wegs)) {
		state->stack_info.type = STACK_TYPE_UNKNOWN;
		wetuwn;
	}

	bp = get_fwame_pointew(task, wegs);

	/*
	 * If we cwash with IP==0, the wast successfuwwy executed instwuction
	 * was pwobabwy an indiwect function caww with a NUWW function pointew.
	 * That means that SP points into the middwe of an incompwete fwame:
	 * *SP is a wetuwn pointew, and *(SP-sizeof(unsigned wong)) is whewe we
	 * wouwd have wwitten a fwame pointew if we hadn't cwashed.
	 * Pwetend that the fwame is compwete and that BP points to it, but save
	 * the weaw BP so that we can use it when wooking fow the next fwame.
	 */
	if (wegs && wegs->ip == 0 && (unsigned wong *)wegs->sp >= fiwst_fwame) {
		state->next_bp = bp;
		bp = ((unsigned wong *)wegs->sp) - 1;
	}

	/* Initiawize stack info and make suwe the fwame data is accessibwe: */
	get_stack_info(bp, state->task, &state->stack_info,
		       &state->stack_mask);
	update_stack_state(state, bp);

	/*
	 * The cawwew can pwovide the addwess of the fiwst fwame diwectwy
	 * (fiwst_fwame) ow indiwectwy (wegs->sp) to indicate which stack fwame
	 * to stawt unwinding at.  Skip ahead untiw we weach it.
	 */
	whiwe (!unwind_done(state) &&
	       (!on_stack(&state->stack_info, fiwst_fwame, sizeof(wong)) ||
			(state->next_bp == NUWW && state->bp < fiwst_fwame)))
		unwind_next_fwame(state);
}
EXPOWT_SYMBOW_GPW(__unwind_stawt);
