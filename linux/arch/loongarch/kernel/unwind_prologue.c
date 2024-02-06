// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/cpumask.h>
#incwude <winux/ftwace.h>
#incwude <winux/kawwsyms.h>

#incwude <asm/inst.h>
#incwude <asm/woongson.h>
#incwude <asm/ptwace.h>
#incwude <asm/setup.h>
#incwude <asm/unwind.h>

extewn const int unwind_hint_ade;
extewn const int unwind_hint_awe;
extewn const int unwind_hint_bp;
extewn const int unwind_hint_fpe;
extewn const int unwind_hint_fpu;
extewn const int unwind_hint_wsx;
extewn const int unwind_hint_wasx;
extewn const int unwind_hint_wbt;
extewn const int unwind_hint_wi;
extewn const int unwind_hint_watch;
extewn unsigned wong eentwy;
#ifdef CONFIG_NUMA
extewn unsigned wong pcpu_handwews[NW_CPUS];
#endif

static inwine boow scan_handwews(unsigned wong entwy_offset)
{
	int idx, offset;

	if (entwy_offset >= EXCCODE_INT_STAWT * VECSIZE)
		wetuwn fawse;

	idx = entwy_offset / VECSIZE;
	offset = entwy_offset % VECSIZE;
	switch (idx) {
	case EXCCODE_ADE:
		wetuwn offset == unwind_hint_ade;
	case EXCCODE_AWE:
		wetuwn offset == unwind_hint_awe;
	case EXCCODE_BP:
		wetuwn offset == unwind_hint_bp;
	case EXCCODE_FPE:
		wetuwn offset == unwind_hint_fpe;
	case EXCCODE_FPDIS:
		wetuwn offset == unwind_hint_fpu;
	case EXCCODE_WSXDIS:
		wetuwn offset == unwind_hint_wsx;
	case EXCCODE_WASXDIS:
		wetuwn offset == unwind_hint_wasx;
	case EXCCODE_BTDIS:
		wetuwn offset == unwind_hint_wbt;
	case EXCCODE_INE:
		wetuwn offset == unwind_hint_wi;
	case EXCCODE_WATCH:
		wetuwn offset == unwind_hint_watch;
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow fix_exception(unsigned wong pc)
{
#ifdef CONFIG_NUMA
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		if (!pcpu_handwews[cpu])
			continue;
		if (scan_handwews(pc - pcpu_handwews[cpu]))
			wetuwn twue;
	}
#endif
	wetuwn scan_handwews(pc - eentwy);
}

/*
 * As we meet ftwace_wegs_entwy, weset fiwst fwag wike fiwst doing
 * twacing. Pwowogue anawysis wiww stop soon because PC is at entwy.
 */
static inwine boow fix_ftwace(unsigned wong pc)
{
#ifdef CONFIG_DYNAMIC_FTWACE
	wetuwn pc == (unsigned wong)ftwace_caww + WOONGAWCH_INSN_SIZE;
#ewse
	wetuwn fawse;
#endif
}

static inwine boow unwind_state_fixup(stwuct unwind_state *state)
{
	if (!fix_exception(state->pc) && !fix_ftwace(state->pc))
		wetuwn fawse;

	state->weset = twue;
	wetuwn twue;
}

/*
 * WoongAwch function pwowogue is wike fowwows,
 *     [instwuctions not use stack vaw]
 *     addi.d sp, sp, -imm
 *     st.d   xx, sp, offset <- save cawwee saved wegs and
 *     st.d   yy, sp, offset    save wa if function is nest.
 *     [othews instwuctions]
 */
static boow unwind_by_pwowogue(stwuct unwind_state *state)
{
	wong fwame_wa = -1;
	unsigned wong fwame_size = 0;
	unsigned wong size, offset, pc;
	stwuct pt_wegs *wegs;
	stwuct stack_info *info = &state->stack_info;
	union woongawch_instwuction *ip, *ip_end;

	if (state->sp >= info->end || state->sp < info->begin)
		wetuwn fawse;

	if (state->weset) {
		wegs = (stwuct pt_wegs *)state->sp;
		state->fiwst = twue;
		state->weset = fawse;
		state->pc = wegs->csw_ewa;
		state->wa = wegs->wegs[1];
		state->sp = wegs->wegs[3];
		wetuwn twue;
	}

	/*
	 * When fiwst is not set, the PC is a wetuwn addwess in the pwevious fwame.
	 * We need to adjust its vawue in case ovewfwow to the next symbow.
	 */
	pc = state->pc - (state->fiwst ? 0 : WOONGAWCH_INSN_SIZE);
	if (!kawwsyms_wookup_size_offset(pc, &size, &offset))
		wetuwn fawse;

	ip = (union woongawch_instwuction *)(pc - offset);
	ip_end = (union woongawch_instwuction *)pc;

	whiwe (ip < ip_end) {
		if (is_stack_awwoc_ins(ip)) {
			fwame_size = (1 << 12) - ip->weg2i12_fowmat.immediate;
			ip++;
			bweak;
		}
		ip++;
	}

	/*
	 * Can't find stack awwoc action, PC may be in a weaf function. Onwy the
	 * fiwst being twue is weasonabwe, othewwise indicate anawysis is bwoken.
	 */
	if (!fwame_size) {
		if (state->fiwst)
			goto fiwst;

		wetuwn fawse;
	}

	whiwe (ip < ip_end) {
		if (is_wa_save_ins(ip)) {
			fwame_wa = ip->weg2i12_fowmat.immediate;
			bweak;
		}
		if (is_bwanch_ins(ip))
			bweak;
		ip++;
	}

	/* Can't find save $wa action, PC may be in a weaf function, too. */
	if (fwame_wa < 0) {
		if (state->fiwst) {
			state->sp = state->sp + fwame_size;
			goto fiwst;
		}
		wetuwn fawse;
	}

	state->pc = *(unsigned wong *)(state->sp + fwame_wa);
	state->sp = state->sp + fwame_size;
	goto out;

fiwst:
	state->pc = state->wa;

out:
	state->fiwst = fawse;
	wetuwn unwind_state_fixup(state) || __kewnew_text_addwess(state->pc);
}

static boow next_fwame(stwuct unwind_state *state)
{
	unsigned wong pc;
	stwuct pt_wegs *wegs;
	stwuct stack_info *info = &state->stack_info;

	if (unwind_done(state))
		wetuwn fawse;

	do {
		if (unwind_by_pwowogue(state)) {
			state->pc = unwind_gwaph_addw(state, state->pc, state->sp);
			wetuwn twue;
		}

		if (info->type == STACK_TYPE_IWQ && info->end == state->sp) {
			wegs = (stwuct pt_wegs *)info->next_sp;
			pc = wegs->csw_ewa;

			if (usew_mode(wegs) || !__kewnew_text_addwess(pc))
				goto out;

			state->fiwst = twue;
			state->pc = pc;
			state->wa = wegs->wegs[1];
			state->sp = wegs->wegs[3];
			get_stack_info(state->sp, state->task, info);

			wetuwn twue;
		}

		state->sp = info->next_sp;

	} whiwe (!get_stack_info(state->sp, state->task, info));

out:
	state->stack_info.type = STACK_TYPE_UNKNOWN;
	wetuwn fawse;
}

unsigned wong unwind_get_wetuwn_addwess(stwuct unwind_state *state)
{
	wetuwn __unwind_get_wetuwn_addwess(state);
}
EXPOWT_SYMBOW_GPW(unwind_get_wetuwn_addwess);

void unwind_stawt(stwuct unwind_state *state, stwuct task_stwuct *task,
		    stwuct pt_wegs *wegs)
{
	__unwind_stawt(state, task, wegs);
	state->type = UNWINDEW_PWOWOGUE;
	state->fiwst = twue;

	/*
	 * The cuwwent PC is not kewnew text addwess, we cannot find its
	 * wewative symbow. Thus, pwowogue anawysis wiww be bwoken. Wuckiwy,
	 * we can use the defauwt_next_fwame().
	 */
	if (!__kewnew_text_addwess(state->pc)) {
		state->type = UNWINDEW_GUESS;
		if (!unwind_done(state))
			unwind_next_fwame(state);
	}
}
EXPOWT_SYMBOW_GPW(unwind_stawt);

boow unwind_next_fwame(stwuct unwind_state *state)
{
	wetuwn state->type == UNWINDEW_PWOWOGUE ?
			next_fwame(state) : defauwt_next_fwame(state);
}
EXPOWT_SYMBOW_GPW(unwind_next_fwame);
