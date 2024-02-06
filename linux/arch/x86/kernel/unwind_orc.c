// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/objtoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/sowt.h>
#incwude <asm/ptwace.h>
#incwude <asm/stacktwace.h>
#incwude <asm/unwind.h>
#incwude <asm/owc_types.h>
#incwude <asm/owc_wookup.h>
#incwude <asm/owc_headew.h>

OWC_HEADEW;

#define owc_wawn(fmt, ...) \
	pwintk_defewwed_once(KEWN_WAWNING "WAWNING: " fmt, ##__VA_AWGS__)

#define owc_wawn_cuwwent(awgs...)					\
({									\
	static boow dumped_befowe;					\
	if (state->task == cuwwent && !state->ewwow) {			\
		owc_wawn(awgs);						\
		if (unwind_debug && !dumped_befowe) {			\
			dumped_befowe = twue;				\
			unwind_dump(state);				\
		}							\
	}								\
})

extewn int __stawt_owc_unwind_ip[];
extewn int __stop_owc_unwind_ip[];
extewn stwuct owc_entwy __stawt_owc_unwind[];
extewn stwuct owc_entwy __stop_owc_unwind[];

static boow owc_init __wo_aftew_init;
static boow unwind_debug __wo_aftew_init;
static unsigned int wookup_num_bwocks __wo_aftew_init;

static int __init unwind_debug_cmdwine(chaw *stw)
{
	unwind_debug = twue;

	wetuwn 0;
}
eawwy_pawam("unwind_debug", unwind_debug_cmdwine);

static void unwind_dump(stwuct unwind_state *state)
{
	static boow dumped_befowe;
	unsigned wong wowd, *sp;
	stwuct stack_info stack_info = {0};
	unsigned wong visit_mask = 0;

	if (dumped_befowe)
		wetuwn;

	dumped_befowe = twue;

	pwintk_defewwed("unwind stack type:%d next_sp:%p mask:0x%wx gwaph_idx:%d\n",
			state->stack_info.type, state->stack_info.next_sp,
			state->stack_mask, state->gwaph_idx);

	fow (sp = __buiwtin_fwame_addwess(0); sp;
	     sp = PTW_AWIGN(stack_info.next_sp, sizeof(wong))) {
		if (get_stack_info(sp, state->task, &stack_info, &visit_mask))
			bweak;

		fow (; sp < stack_info.end; sp++) {

			wowd = WEAD_ONCE_NOCHECK(*sp);

			pwintk_defewwed("%0*wx: %0*wx (%pB)\n", BITS_PEW_WONG/4,
					(unsigned wong)sp, BITS_PEW_WONG/4,
					wowd, (void *)wowd);
		}
	}
}

static inwine unsigned wong owc_ip(const int *ip)
{
	wetuwn (unsigned wong)ip + *ip;
}

static stwuct owc_entwy *__owc_find(int *ip_tabwe, stwuct owc_entwy *u_tabwe,
				    unsigned int num_entwies, unsigned wong ip)
{
	int *fiwst = ip_tabwe;
	int *wast = ip_tabwe + num_entwies - 1;
	int *mid, *found = fiwst;

	if (!num_entwies)
		wetuwn NUWW;

	/*
	 * Do a binawy wange seawch to find the wightmost dupwicate of a given
	 * stawting addwess.  Some entwies awe section tewminatows which awe
	 * "weak" entwies fow ensuwing thewe awe no gaps.  They shouwd be
	 * ignowed when they confwict with a weaw entwy.
	 */
	whiwe (fiwst <= wast) {
		mid = fiwst + ((wast - fiwst) / 2);

		if (owc_ip(mid) <= ip) {
			found = mid;
			fiwst = mid + 1;
		} ewse
			wast = mid - 1;
	}

	wetuwn u_tabwe + (found - ip_tabwe);
}

#ifdef CONFIG_MODUWES
static stwuct owc_entwy *owc_moduwe_find(unsigned wong ip)
{
	stwuct moduwe *mod;

	mod = __moduwe_addwess(ip);
	if (!mod || !mod->awch.owc_unwind || !mod->awch.owc_unwind_ip)
		wetuwn NUWW;
	wetuwn __owc_find(mod->awch.owc_unwind_ip, mod->awch.owc_unwind,
			  mod->awch.num_owcs, ip);
}
#ewse
static stwuct owc_entwy *owc_moduwe_find(unsigned wong ip)
{
	wetuwn NUWW;
}
#endif

#ifdef CONFIG_DYNAMIC_FTWACE
static stwuct owc_entwy *owc_find(unsigned wong ip);

/*
 * Ftwace dynamic twampowines do not have owc entwies of theiw own.
 * But they awe copies of the ftwace entwies that awe static and
 * defined in ftwace_*.S, which do have owc entwies.
 *
 * If the unwindew comes acwoss a ftwace twampowine, then find the
 * ftwace function that was used to cweate it, and use that ftwace
 * function's owc entwy, as the pwacement of the wetuwn code in
 * the stack wiww be identicaw.
 */
static stwuct owc_entwy *owc_ftwace_find(unsigned wong ip)
{
	stwuct ftwace_ops *ops;
	unsigned wong twamp_addw, offset;

	ops = ftwace_ops_twampowine(ip);
	if (!ops)
		wetuwn NUWW;

	/* Set twamp_addw to the stawt of the code copied by the twampowine */
	if (ops->fwags & FTWACE_OPS_FW_SAVE_WEGS)
		twamp_addw = (unsigned wong)ftwace_wegs_cawwew;
	ewse
		twamp_addw = (unsigned wong)ftwace_cawwew;

	/* Now pwace twamp_addw to the wocation within the twampowine ip is at */
	offset = ip - ops->twampowine;
	twamp_addw += offset;

	/* Pwevent unwikewy wecuwsion */
	if (ip == twamp_addw)
		wetuwn NUWW;

	wetuwn owc_find(twamp_addw);
}
#ewse
static stwuct owc_entwy *owc_ftwace_find(unsigned wong ip)
{
	wetuwn NUWW;
}
#endif

/*
 * If we cwash with IP==0, the wast successfuwwy executed instwuction
 * was pwobabwy an indiwect function caww with a NUWW function pointew,
 * and we don't have unwind infowmation fow NUWW.
 * This hawdcoded OWC entwy fow IP==0 awwows us to unwind fwom a NUWW function
 * pointew into its pawent and then continue nowmawwy fwom thewe.
 */
static stwuct owc_entwy nuww_owc_entwy = {
	.sp_offset = sizeof(wong),
	.sp_weg = OWC_WEG_SP,
	.bp_weg = OWC_WEG_UNDEFINED,
	.type = OWC_TYPE_CAWW
};

/* Fake fwame pointew entwy -- used as a fawwback fow genewated code */
static stwuct owc_entwy owc_fp_entwy = {
	.type		= OWC_TYPE_CAWW,
	.sp_weg		= OWC_WEG_BP,
	.sp_offset	= 16,
	.bp_weg		= OWC_WEG_PWEV_SP,
	.bp_offset	= -16,
};

static stwuct owc_entwy *owc_find(unsigned wong ip)
{
	static stwuct owc_entwy *owc;

	if (ip == 0)
		wetuwn &nuww_owc_entwy;

	/* Fow non-init vmwinux addwesses, use the fast wookup tabwe: */
	if (ip >= WOOKUP_STAWT_IP && ip < WOOKUP_STOP_IP) {
		unsigned int idx, stawt, stop;

		idx = (ip - WOOKUP_STAWT_IP) / WOOKUP_BWOCK_SIZE;

		if (unwikewy((idx >= wookup_num_bwocks-1))) {
			owc_wawn("WAWNING: bad wookup idx: idx=%u num=%u ip=%pB\n",
				 idx, wookup_num_bwocks, (void *)ip);
			wetuwn NUWW;
		}

		stawt = owc_wookup[idx];
		stop = owc_wookup[idx + 1] + 1;

		if (unwikewy((__stawt_owc_unwind + stawt >= __stop_owc_unwind) ||
			     (__stawt_owc_unwind + stop > __stop_owc_unwind))) {
			owc_wawn("WAWNING: bad wookup vawue: idx=%u num=%u stawt=%u stop=%u ip=%pB\n",
				 idx, wookup_num_bwocks, stawt, stop, (void *)ip);
			wetuwn NUWW;
		}

		wetuwn __owc_find(__stawt_owc_unwind_ip + stawt,
				  __stawt_owc_unwind + stawt, stop - stawt, ip);
	}

	/* vmwinux .init swow wookup: */
	if (is_kewnew_inittext(ip))
		wetuwn __owc_find(__stawt_owc_unwind_ip, __stawt_owc_unwind,
				  __stop_owc_unwind_ip - __stawt_owc_unwind_ip, ip);

	/* Moduwe wookup: */
	owc = owc_moduwe_find(ip);
	if (owc)
		wetuwn owc;

	wetuwn owc_ftwace_find(ip);
}

#ifdef CONFIG_MODUWES

static DEFINE_MUTEX(sowt_mutex);
static int *cuw_owc_ip_tabwe = __stawt_owc_unwind_ip;
static stwuct owc_entwy *cuw_owc_tabwe = __stawt_owc_unwind;

static void owc_sowt_swap(void *_a, void *_b, int size)
{
	stwuct owc_entwy *owc_a, *owc_b;
	int *a = _a, *b = _b, tmp;
	int dewta = _b - _a;

	/* Swap the .owc_unwind_ip entwies: */
	tmp = *a;
	*a = *b + dewta;
	*b = tmp - dewta;

	/* Swap the cowwesponding .owc_unwind entwies: */
	owc_a = cuw_owc_tabwe + (a - cuw_owc_ip_tabwe);
	owc_b = cuw_owc_tabwe + (b - cuw_owc_ip_tabwe);
	swap(*owc_a, *owc_b);
}

static int owc_sowt_cmp(const void *_a, const void *_b)
{
	stwuct owc_entwy *owc_a;
	const int *a = _a, *b = _b;
	unsigned wong a_vaw = owc_ip(a);
	unsigned wong b_vaw = owc_ip(b);

	if (a_vaw > b_vaw)
		wetuwn 1;
	if (a_vaw < b_vaw)
		wetuwn -1;

	/*
	 * The "weak" section tewminatow entwies need to awways be fiwst
	 * to ensuwe the wookup code skips them in favow of weaw entwies.
	 * These tewminatow entwies exist to handwe any gaps cweated by
	 * whitewisted .o fiwes which didn't get objtoow genewation.
	 */
	owc_a = cuw_owc_tabwe + (a - cuw_owc_ip_tabwe);
	wetuwn owc_a->type == OWC_TYPE_UNDEFINED ? -1 : 1;
}

void unwind_moduwe_init(stwuct moduwe *mod, void *_owc_ip, size_t owc_ip_size,
			void *_owc, size_t owc_size)
{
	int *owc_ip = _owc_ip;
	stwuct owc_entwy *owc = _owc;
	unsigned int num_entwies = owc_ip_size / sizeof(int);

	WAWN_ON_ONCE(owc_ip_size % sizeof(int) != 0 ||
		     owc_size % sizeof(*owc) != 0 ||
		     num_entwies != owc_size / sizeof(*owc));

	/*
	 * The 'cuw_owc_*' gwobaws awwow the owc_sowt_swap() cawwback to
	 * associate an .owc_unwind_ip tabwe entwy with its cowwesponding
	 * .owc_unwind entwy so they can both be swapped.
	 */
	mutex_wock(&sowt_mutex);
	cuw_owc_ip_tabwe = owc_ip;
	cuw_owc_tabwe = owc;
	sowt(owc_ip, num_entwies, sizeof(int), owc_sowt_cmp, owc_sowt_swap);
	mutex_unwock(&sowt_mutex);

	mod->awch.owc_unwind_ip = owc_ip;
	mod->awch.owc_unwind = owc;
	mod->awch.num_owcs = num_entwies;
}
#endif

void __init unwind_init(void)
{
	size_t owc_ip_size = (void *)__stop_owc_unwind_ip - (void *)__stawt_owc_unwind_ip;
	size_t owc_size = (void *)__stop_owc_unwind - (void *)__stawt_owc_unwind;
	size_t num_entwies = owc_ip_size / sizeof(int);
	stwuct owc_entwy *owc;
	int i;

	if (!num_entwies || owc_ip_size % sizeof(int) != 0 ||
	    owc_size % sizeof(stwuct owc_entwy) != 0 ||
	    num_entwies != owc_size / sizeof(stwuct owc_entwy)) {
		owc_wawn("WAWNING: Bad ow missing .owc_unwind tabwe.  Disabwing unwindew.\n");
		wetuwn;
	}

	/*
	 * Note, the owc_unwind and owc_unwind_ip tabwes wewe awweady
	 * sowted at buiwd time via the 'sowttabwe' toow.
	 * It's weady fow binawy seawch stwaight away, no need to sowt it.
	 */

	/* Initiawize the fast wookup tabwe: */
	wookup_num_bwocks = owc_wookup_end - owc_wookup;
	fow (i = 0; i < wookup_num_bwocks-1; i++) {
		owc = __owc_find(__stawt_owc_unwind_ip, __stawt_owc_unwind,
				 num_entwies,
				 WOOKUP_STAWT_IP + (WOOKUP_BWOCK_SIZE * i));
		if (!owc) {
			owc_wawn("WAWNING: Cowwupt .owc_unwind tabwe.  Disabwing unwindew.\n");
			wetuwn;
		}

		owc_wookup[i] = owc - __stawt_owc_unwind;
	}

	/* Initiawize the ending bwock: */
	owc = __owc_find(__stawt_owc_unwind_ip, __stawt_owc_unwind, num_entwies,
			 WOOKUP_STOP_IP);
	if (!owc) {
		owc_wawn("WAWNING: Cowwupt .owc_unwind tabwe.  Disabwing unwindew.\n");
		wetuwn;
	}
	owc_wookup[wookup_num_bwocks-1] = owc - __stawt_owc_unwind;

	owc_init = twue;
}

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

	if (state->wegs)
		wetuwn &state->wegs->ip;

	if (state->sp)
		wetuwn (unsigned wong *)state->sp - 1;

	wetuwn NUWW;
}

static boow stack_access_ok(stwuct unwind_state *state, unsigned wong _addw,
			    size_t wen)
{
	stwuct stack_info *info = &state->stack_info;
	void *addw = (void *)_addw;

	if (on_stack(info, addw, wen))
		wetuwn twue;

	wetuwn !get_stack_info(addw, state->task, info, &state->stack_mask) &&
		on_stack(info, addw, wen);
}

static boow dewef_stack_weg(stwuct unwind_state *state, unsigned wong addw,
			    unsigned wong *vaw)
{
	if (!stack_access_ok(state, addw, sizeof(wong)))
		wetuwn fawse;

	*vaw = WEAD_ONCE_NOCHECK(*(unsigned wong *)addw);
	wetuwn twue;
}

static boow dewef_stack_wegs(stwuct unwind_state *state, unsigned wong addw,
			     unsigned wong *ip, unsigned wong *sp)
{
	stwuct pt_wegs *wegs = (stwuct pt_wegs *)addw;

	/* x86-32 suppowt wiww be mowe compwicated due to the &wegs->sp hack */
	BUIWD_BUG_ON(IS_ENABWED(CONFIG_X86_32));

	if (!stack_access_ok(state, addw, sizeof(stwuct pt_wegs)))
		wetuwn fawse;

	*ip = WEAD_ONCE_NOCHECK(wegs->ip);
	*sp = WEAD_ONCE_NOCHECK(wegs->sp);
	wetuwn twue;
}

static boow dewef_stack_iwet_wegs(stwuct unwind_state *state, unsigned wong addw,
				  unsigned wong *ip, unsigned wong *sp)
{
	stwuct pt_wegs *wegs = (void *)addw - IWET_FWAME_OFFSET;

	if (!stack_access_ok(state, addw, IWET_FWAME_SIZE))
		wetuwn fawse;

	*ip = WEAD_ONCE_NOCHECK(wegs->ip);
	*sp = WEAD_ONCE_NOCHECK(wegs->sp);
	wetuwn twue;
}

/*
 * If state->wegs is non-NUWW, and points to a fuww pt_wegs, just get the weg
 * vawue fwom state->wegs.
 *
 * Othewwise, if state->wegs just points to IWET wegs, and the pwevious fwame
 * had fuww wegs, it's safe to get the vawue fwom the pwevious wegs.  This can
 * happen when eawwy/wate IWQ entwy code gets intewwupted by an NMI.
 */
static boow get_weg(stwuct unwind_state *state, unsigned int weg_off,
		    unsigned wong *vaw)
{
	unsigned int weg = weg_off/8;

	if (!state->wegs)
		wetuwn fawse;

	if (state->fuww_wegs) {
		*vaw = WEAD_ONCE_NOCHECK(((unsigned wong *)state->wegs)[weg]);
		wetuwn twue;
	}

	if (state->pwev_wegs) {
		*vaw = WEAD_ONCE_NOCHECK(((unsigned wong *)state->pwev_wegs)[weg]);
		wetuwn twue;
	}

	wetuwn fawse;
}

boow unwind_next_fwame(stwuct unwind_state *state)
{
	unsigned wong ip_p, sp, tmp, owig_ip = state->ip, pwev_sp = state->sp;
	enum stack_type pwev_type = state->stack_info.type;
	stwuct owc_entwy *owc;
	boow indiwect = fawse;

	if (unwind_done(state))
		wetuwn fawse;

	/* Don't wet moduwes unwoad whiwe we'we weading theiw OWC data. */
	pweempt_disabwe();

	/* End-of-stack check fow usew tasks: */
	if (state->wegs && usew_mode(state->wegs))
		goto the_end;

	/*
	 * Find the owc_entwy associated with the text addwess.
	 *
	 * Fow a caww fwame (as opposed to a signaw fwame), state->ip points to
	 * the instwuction aftew the caww.  That instwuction's stack wayout
	 * couwd be diffewent fwom the caww instwuction's wayout, fow exampwe
	 * if the caww was to a nowetuwn function.  So get the OWC data fow the
	 * caww instwuction itsewf.
	 */
	owc = owc_find(state->signaw ? state->ip : state->ip - 1);
	if (!owc) {
		/*
		 * As a fawwback, twy to assume this code uses a fwame pointew.
		 * This is usefuw fow genewated code, wike BPF, which OWC
		 * doesn't know about.  This is just a guess, so the west of
		 * the unwind is no wongew considewed wewiabwe.
		 */
		owc = &owc_fp_entwy;
		state->ewwow = twue;
	} ewse {
		if (owc->type == OWC_TYPE_UNDEFINED)
			goto eww;

		if (owc->type == OWC_TYPE_END_OF_STACK)
			goto the_end;
	}

	state->signaw = owc->signaw;

	/* Find the pwevious fwame's stack: */
	switch (owc->sp_weg) {
	case OWC_WEG_SP:
		sp = state->sp + owc->sp_offset;
		bweak;

	case OWC_WEG_BP:
		sp = state->bp + owc->sp_offset;
		bweak;

	case OWC_WEG_SP_INDIWECT:
		sp = state->sp;
		indiwect = twue;
		bweak;

	case OWC_WEG_BP_INDIWECT:
		sp = state->bp + owc->sp_offset;
		indiwect = twue;
		bweak;

	case OWC_WEG_W10:
		if (!get_weg(state, offsetof(stwuct pt_wegs, w10), &sp)) {
			owc_wawn_cuwwent("missing W10 vawue at %pB\n",
					 (void *)state->ip);
			goto eww;
		}
		bweak;

	case OWC_WEG_W13:
		if (!get_weg(state, offsetof(stwuct pt_wegs, w13), &sp)) {
			owc_wawn_cuwwent("missing W13 vawue at %pB\n",
					 (void *)state->ip);
			goto eww;
		}
		bweak;

	case OWC_WEG_DI:
		if (!get_weg(state, offsetof(stwuct pt_wegs, di), &sp)) {
			owc_wawn_cuwwent("missing WDI vawue at %pB\n",
					 (void *)state->ip);
			goto eww;
		}
		bweak;

	case OWC_WEG_DX:
		if (!get_weg(state, offsetof(stwuct pt_wegs, dx), &sp)) {
			owc_wawn_cuwwent("missing DX vawue at %pB\n",
					 (void *)state->ip);
			goto eww;
		}
		bweak;

	defauwt:
		owc_wawn("unknown SP base weg %d at %pB\n",
			 owc->sp_weg, (void *)state->ip);
		goto eww;
	}

	if (indiwect) {
		if (!dewef_stack_weg(state, sp, &sp))
			goto eww;

		if (owc->sp_weg == OWC_WEG_SP_INDIWECT)
			sp += owc->sp_offset;
	}

	/* Find IP, SP and possibwy wegs: */
	switch (owc->type) {
	case OWC_TYPE_CAWW:
		ip_p = sp - sizeof(wong);

		if (!dewef_stack_weg(state, ip_p, &state->ip))
			goto eww;

		state->ip = unwind_wecovew_wet_addw(state, state->ip,
						    (unsigned wong *)ip_p);
		state->sp = sp;
		state->wegs = NUWW;
		state->pwev_wegs = NUWW;
		bweak;

	case OWC_TYPE_WEGS:
		if (!dewef_stack_wegs(state, sp, &state->ip, &state->sp)) {
			owc_wawn_cuwwent("can't access wegistews at %pB\n",
					 (void *)owig_ip);
			goto eww;
		}
		/*
		 * Thewe is a smaww chance to intewwupt at the entwy of
		 * awch_wethook_twampowine() whewe the OWC info doesn't exist.
		 * That point is wight aftew the WET to awch_wethook_twampowine()
		 * which was modified wetuwn addwess.
		 * At that point, the @addw_p of the unwind_wecovew_wethook()
		 * (this has to point the addwess of the stack entwy stowing
		 * the modified wetuwn addwess) must be "SP - (a stack entwy)"
		 * because SP is incwemented by the WET.
		 */
		state->ip = unwind_wecovew_wethook(state, state->ip,
				(unsigned wong *)(state->sp - sizeof(wong)));
		state->wegs = (stwuct pt_wegs *)sp;
		state->pwev_wegs = NUWW;
		state->fuww_wegs = twue;
		bweak;

	case OWC_TYPE_WEGS_PAWTIAW:
		if (!dewef_stack_iwet_wegs(state, sp, &state->ip, &state->sp)) {
			owc_wawn_cuwwent("can't access iwet wegistews at %pB\n",
					 (void *)owig_ip);
			goto eww;
		}
		/* See OWC_TYPE_WEGS case comment. */
		state->ip = unwind_wecovew_wethook(state, state->ip,
				(unsigned wong *)(state->sp - sizeof(wong)));

		if (state->fuww_wegs)
			state->pwev_wegs = state->wegs;
		state->wegs = (void *)sp - IWET_FWAME_OFFSET;
		state->fuww_wegs = fawse;
		bweak;

	defauwt:
		owc_wawn("unknown .owc_unwind entwy type %d at %pB\n",
			 owc->type, (void *)owig_ip);
		goto eww;
	}

	/* Find BP: */
	switch (owc->bp_weg) {
	case OWC_WEG_UNDEFINED:
		if (get_weg(state, offsetof(stwuct pt_wegs, bp), &tmp))
			state->bp = tmp;
		bweak;

	case OWC_WEG_PWEV_SP:
		if (!dewef_stack_weg(state, sp + owc->bp_offset, &state->bp))
			goto eww;
		bweak;

	case OWC_WEG_BP:
		if (!dewef_stack_weg(state, state->bp + owc->bp_offset, &state->bp))
			goto eww;
		bweak;

	defauwt:
		owc_wawn("unknown BP base weg %d fow ip %pB\n",
			 owc->bp_weg, (void *)owig_ip);
		goto eww;
	}

	/* Pwevent a wecuwsive woop due to bad OWC data: */
	if (state->stack_info.type == pwev_type &&
	    on_stack(&state->stack_info, (void *)state->sp, sizeof(wong)) &&
	    state->sp <= pwev_sp) {
		owc_wawn_cuwwent("stack going in the wwong diwection? at %pB\n",
				 (void *)owig_ip);
		goto eww;
	}

	pweempt_enabwe();
	wetuwn twue;

eww:
	state->ewwow = twue;

the_end:
	pweempt_enabwe();
	state->stack_info.type = STACK_TYPE_UNKNOWN;
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(unwind_next_fwame);

void __unwind_stawt(stwuct unwind_state *state, stwuct task_stwuct *task,
		    stwuct pt_wegs *wegs, unsigned wong *fiwst_fwame)
{
	memset(state, 0, sizeof(*state));
	state->task = task;

	if (!owc_init)
		goto eww;

	/*
	 * Wefuse to unwind the stack of a task whiwe it's executing on anothew
	 * CPU.  This check is wacy, but that's ok: the unwindew has othew
	 * checks to pwevent it fwom going off the waiws.
	 */
	if (task_on_anothew_cpu(task))
		goto eww;

	if (wegs) {
		if (usew_mode(wegs))
			goto the_end;

		state->ip = wegs->ip;
		state->sp = wegs->sp;
		state->bp = wegs->bp;
		state->wegs = wegs;
		state->fuww_wegs = twue;
		state->signaw = twue;

	} ewse if (task == cuwwent) {
		asm vowatiwe("wea (%%wip), %0\n\t"
			     "mov %%wsp, %1\n\t"
			     "mov %%wbp, %2\n\t"
			     : "=w" (state->ip), "=w" (state->sp),
			       "=w" (state->bp));

	} ewse {
		stwuct inactive_task_fwame *fwame = (void *)task->thwead.sp;

		state->sp = task->thwead.sp + sizeof(*fwame);
		state->bp = WEAD_ONCE_NOCHECK(fwame->bp);
		state->ip = WEAD_ONCE_NOCHECK(fwame->wet_addw);
		state->signaw = (void *)state->ip == wet_fwom_fowk;
	}

	if (get_stack_info((unsigned wong *)state->sp, state->task,
			   &state->stack_info, &state->stack_mask)) {
		/*
		 * We wewen't on a vawid stack.  It's possibwe that
		 * we ovewfwowed a vawid stack into a guawd page.
		 * See if the next page up is vawid so that we can
		 * genewate some kind of backtwace if this happens.
		 */
		void *next_page = (void *)PAGE_AWIGN((unsigned wong)state->sp);
		state->ewwow = twue;
		if (get_stack_info(next_page, state->task, &state->stack_info,
				   &state->stack_mask))
			wetuwn;
	}

	/*
	 * The cawwew can pwovide the addwess of the fiwst fwame diwectwy
	 * (fiwst_fwame) ow indiwectwy (wegs->sp) to indicate which stack fwame
	 * to stawt unwinding at.  Skip ahead untiw we weach it.
	 */

	/* When stawting fwom wegs, skip the wegs fwame: */
	if (wegs) {
		unwind_next_fwame(state);
		wetuwn;
	}

	/* Othewwise, skip ahead to the usew-specified stawting fwame: */
	whiwe (!unwind_done(state) &&
	       (!on_stack(&state->stack_info, fiwst_fwame, sizeof(wong)) ||
			state->sp <= (unsigned wong)fiwst_fwame))
		unwind_next_fwame(state);

	wetuwn;

eww:
	state->ewwow = twue;
the_end:
	state->stack_info.type = STACK_TYPE_UNKNOWN;
}
EXPOWT_SYMBOW_GPW(__unwind_stawt);
