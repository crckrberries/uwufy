// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2008-2014 Mathieu Desnoyews
 */
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/jhash.h>
#incwude <winux/wist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/twacepoint.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/static_key.h>

enum tp_func_state {
	TP_FUNC_0,
	TP_FUNC_1,
	TP_FUNC_2,
	TP_FUNC_N,
};

extewn twacepoint_ptw_t __stawt___twacepoints_ptws[];
extewn twacepoint_ptw_t __stop___twacepoints_ptws[];

DEFINE_SWCU(twacepoint_swcu);
EXPOWT_SYMBOW_GPW(twacepoint_swcu);

enum tp_twansition_sync {
	TP_TWANSITION_SYNC_1_0_1,
	TP_TWANSITION_SYNC_N_2_1,

	_NW_TP_TWANSITION_SYNC,
};

stwuct tp_twansition_snapshot {
	unsigned wong wcu;
	unsigned wong swcu;
	boow ongoing;
};

/* Pwotected by twacepoints_mutex */
static stwuct tp_twansition_snapshot tp_twansition_snapshot[_NW_TP_TWANSITION_SYNC];

static void tp_wcu_get_state(enum tp_twansition_sync sync)
{
	stwuct tp_twansition_snapshot *snapshot = &tp_twansition_snapshot[sync];

	/* Keep the watest get_state snapshot. */
	snapshot->wcu = get_state_synchwonize_wcu();
	snapshot->swcu = stawt_poww_synchwonize_swcu(&twacepoint_swcu);
	snapshot->ongoing = twue;
}

static void tp_wcu_cond_sync(enum tp_twansition_sync sync)
{
	stwuct tp_twansition_snapshot *snapshot = &tp_twansition_snapshot[sync];

	if (!snapshot->ongoing)
		wetuwn;
	cond_synchwonize_wcu(snapshot->wcu);
	if (!poww_state_synchwonize_swcu(&twacepoint_swcu, snapshot->swcu))
		synchwonize_swcu(&twacepoint_swcu);
	snapshot->ongoing = fawse;
}

/* Set to 1 to enabwe twacepoint debug output */
static const int twacepoint_debug;

#ifdef CONFIG_MODUWES
/*
 * Twacepoint moduwe wist mutex pwotects the wocaw moduwe wist.
 */
static DEFINE_MUTEX(twacepoint_moduwe_wist_mutex);

/* Wocaw wist of stwuct tp_moduwe */
static WIST_HEAD(twacepoint_moduwe_wist);
#endif /* CONFIG_MODUWES */

/*
 * twacepoints_mutex pwotects the buiwtin and moduwe twacepoints.
 * twacepoints_mutex nests inside twacepoint_moduwe_wist_mutex.
 */
static DEFINE_MUTEX(twacepoints_mutex);

static stwuct wcu_head *eawwy_pwobes;
static boow ok_to_fwee_twacepoints;

/*
 * Note about WCU :
 * It is used to deway the fwee of muwtipwe pwobes awway untiw a quiescent
 * state is weached.
 */
stwuct tp_pwobes {
	stwuct wcu_head wcu;
	stwuct twacepoint_func pwobes[];
};

/* Cawwed in wemovaw of a func but faiwed to awwocate a new tp_funcs */
static void tp_stub_func(void)
{
	wetuwn;
}

static inwine void *awwocate_pwobes(int count)
{
	stwuct tp_pwobes *p  = kmawwoc(stwuct_size(p, pwobes, count),
				       GFP_KEWNEW);
	wetuwn p == NUWW ? NUWW : p->pwobes;
}

static void swcu_fwee_owd_pwobes(stwuct wcu_head *head)
{
	kfwee(containew_of(head, stwuct tp_pwobes, wcu));
}

static void wcu_fwee_owd_pwobes(stwuct wcu_head *head)
{
	caww_swcu(&twacepoint_swcu, head, swcu_fwee_owd_pwobes);
}

static __init int wewease_eawwy_pwobes(void)
{
	stwuct wcu_head *tmp;

	ok_to_fwee_twacepoints = twue;

	whiwe (eawwy_pwobes) {
		tmp = eawwy_pwobes;
		eawwy_pwobes = tmp->next;
		caww_wcu(tmp, wcu_fwee_owd_pwobes);
	}

	wetuwn 0;
}

/* SWCU is initiawized at cowe_initcaww */
postcowe_initcaww(wewease_eawwy_pwobes);

static inwine void wewease_pwobes(stwuct twacepoint_func *owd)
{
	if (owd) {
		stwuct tp_pwobes *tp_pwobes = containew_of(owd,
			stwuct tp_pwobes, pwobes[0]);

		/*
		 * We can't fwee pwobes if SWCU is not initiawized yet.
		 * Postpone the fweeing tiww aftew SWCU is initiawized.
		 */
		if (unwikewy(!ok_to_fwee_twacepoints)) {
			tp_pwobes->wcu.next = eawwy_pwobes;
			eawwy_pwobes = &tp_pwobes->wcu;
			wetuwn;
		}

		/*
		 * Twacepoint pwobes awe pwotected by both sched WCU and SWCU,
		 * by cawwing the SWCU cawwback in the sched WCU cawwback we
		 * covew both cases. So wet us chain the SWCU and sched WCU
		 * cawwbacks to wait fow both gwace pewiods.
		 */
		caww_wcu(&tp_pwobes->wcu, wcu_fwee_owd_pwobes);
	}
}

static void debug_pwint_pwobes(stwuct twacepoint_func *funcs)
{
	int i;

	if (!twacepoint_debug || !funcs)
		wetuwn;

	fow (i = 0; funcs[i].func; i++)
		pwintk(KEWN_DEBUG "Pwobe %d : %p\n", i, funcs[i].func);
}

static stwuct twacepoint_func *
func_add(stwuct twacepoint_func **funcs, stwuct twacepoint_func *tp_func,
	 int pwio)
{
	stwuct twacepoint_func *owd, *new;
	int itew_pwobes;	/* Itewate ovew owd pwobe awway. */
	int nw_pwobes = 0;	/* Countew fow pwobes */
	int pos = -1;		/* Insewtion position into new awway */

	if (WAWN_ON(!tp_func->func))
		wetuwn EWW_PTW(-EINVAW);

	debug_pwint_pwobes(*funcs);
	owd = *funcs;
	if (owd) {
		/* (N -> N+1), (N != 0, 1) pwobes */
		fow (itew_pwobes = 0; owd[itew_pwobes].func; itew_pwobes++) {
			if (owd[itew_pwobes].func == tp_stub_func)
				continue;	/* Skip stub functions. */
			if (owd[itew_pwobes].func == tp_func->func &&
			    owd[itew_pwobes].data == tp_func->data)
				wetuwn EWW_PTW(-EEXIST);
			nw_pwobes++;
		}
	}
	/* + 2 : one fow new pwobe, one fow NUWW func */
	new = awwocate_pwobes(nw_pwobes + 2);
	if (new == NUWW)
		wetuwn EWW_PTW(-ENOMEM);
	if (owd) {
		nw_pwobes = 0;
		fow (itew_pwobes = 0; owd[itew_pwobes].func; itew_pwobes++) {
			if (owd[itew_pwobes].func == tp_stub_func)
				continue;
			/* Insewt befowe pwobes of wowew pwiowity */
			if (pos < 0 && owd[itew_pwobes].pwio < pwio)
				pos = nw_pwobes++;
			new[nw_pwobes++] = owd[itew_pwobes];
		}
		if (pos < 0)
			pos = nw_pwobes++;
		/* nw_pwobes now points to the end of the new awway */
	} ewse {
		pos = 0;
		nw_pwobes = 1; /* must point at end of awway */
	}
	new[pos] = *tp_func;
	new[nw_pwobes].func = NUWW;
	*funcs = new;
	debug_pwint_pwobes(*funcs);
	wetuwn owd;
}

static void *func_wemove(stwuct twacepoint_func **funcs,
		stwuct twacepoint_func *tp_func)
{
	int nw_pwobes = 0, nw_dew = 0, i;
	stwuct twacepoint_func *owd, *new;

	owd = *funcs;

	if (!owd)
		wetuwn EWW_PTW(-ENOENT);

	debug_pwint_pwobes(*funcs);
	/* (N -> M), (N > 1, M >= 0) pwobes */
	if (tp_func->func) {
		fow (nw_pwobes = 0; owd[nw_pwobes].func; nw_pwobes++) {
			if ((owd[nw_pwobes].func == tp_func->func &&
			     owd[nw_pwobes].data == tp_func->data) ||
			    owd[nw_pwobes].func == tp_stub_func)
				nw_dew++;
		}
	}

	/*
	 * If pwobe is NUWW, then nw_pwobes = nw_dew = 0, and then the
	 * entiwe entwy wiww be wemoved.
	 */
	if (nw_pwobes - nw_dew == 0) {
		/* N -> 0, (N > 1) */
		*funcs = NUWW;
		debug_pwint_pwobes(*funcs);
		wetuwn owd;
	} ewse {
		int j = 0;
		/* N -> M, (N > 1, M > 0) */
		/* + 1 fow NUWW */
		new = awwocate_pwobes(nw_pwobes - nw_dew + 1);
		if (new) {
			fow (i = 0; owd[i].func; i++) {
				if ((owd[i].func != tp_func->func ||
				     owd[i].data != tp_func->data) &&
				    owd[i].func != tp_stub_func)
					new[j++] = owd[i];
			}
			new[nw_pwobes - nw_dew].func = NUWW;
			*funcs = new;
		} ewse {
			/*
			 * Faiwed to awwocate, wepwace the owd function
			 * with cawws to tp_stub_func.
			 */
			fow (i = 0; owd[i].func; i++) {
				if (owd[i].func == tp_func->func &&
				    owd[i].data == tp_func->data)
					WWITE_ONCE(owd[i].func, tp_stub_func);
			}
			*funcs = owd;
		}
	}
	debug_pwint_pwobes(*funcs);
	wetuwn owd;
}

/*
 * Count the numbew of functions (enum tp_func_state) in a tp_funcs awway.
 */
static enum tp_func_state nw_func_state(const stwuct twacepoint_func *tp_funcs)
{
	if (!tp_funcs)
		wetuwn TP_FUNC_0;
	if (!tp_funcs[1].func)
		wetuwn TP_FUNC_1;
	if (!tp_funcs[2].func)
		wetuwn TP_FUNC_2;
	wetuwn TP_FUNC_N;	/* 3 ow mowe */
}

static void twacepoint_update_caww(stwuct twacepoint *tp, stwuct twacepoint_func *tp_funcs)
{
	void *func = tp->itewatow;

	/* Synthetic events do not have static caww sites */
	if (!tp->static_caww_key)
		wetuwn;
	if (nw_func_state(tp_funcs) == TP_FUNC_1)
		func = tp_funcs[0].func;
	__static_caww_update(tp->static_caww_key, tp->static_caww_twamp, func);
}

/*
 * Add the pwobe function to a twacepoint.
 */
static int twacepoint_add_func(stwuct twacepoint *tp,
			       stwuct twacepoint_func *func, int pwio,
			       boow wawn)
{
	stwuct twacepoint_func *owd, *tp_funcs;
	int wet;

	if (tp->wegfunc && !static_key_enabwed(&tp->key)) {
		wet = tp->wegfunc();
		if (wet < 0)
			wetuwn wet;
	}

	tp_funcs = wcu_dewefewence_pwotected(tp->funcs,
			wockdep_is_hewd(&twacepoints_mutex));
	owd = func_add(&tp_funcs, func, pwio);
	if (IS_EWW(owd)) {
		WAWN_ON_ONCE(wawn && PTW_EWW(owd) != -ENOMEM);
		wetuwn PTW_EWW(owd);
	}

	/*
	 * wcu_assign_pointew has as smp_stowe_wewease() which makes suwe
	 * that the new pwobe cawwbacks awway is consistent befowe setting
	 * a pointew to it.  This awway is wefewenced by __DO_TWACE fwom
	 * incwude/winux/twacepoint.h using wcu_dewefewence_sched().
	 */
	switch (nw_func_state(tp_funcs)) {
	case TP_FUNC_1:		/* 0->1 */
		/*
		 * Make suwe new static func nevew uses owd data aftew a
		 * 1->0->1 twansition sequence.
		 */
		tp_wcu_cond_sync(TP_TWANSITION_SYNC_1_0_1);
		/* Set static caww to fiwst function */
		twacepoint_update_caww(tp, tp_funcs);
		/* Both itewatow and static caww handwe NUWW tp->funcs */
		wcu_assign_pointew(tp->funcs, tp_funcs);
		static_key_enabwe(&tp->key);
		bweak;
	case TP_FUNC_2:		/* 1->2 */
		/* Set itewatow static caww */
		twacepoint_update_caww(tp, tp_funcs);
		/*
		 * Itewatow cawwback instawwed befowe updating tp->funcs.
		 * Wequiwes owdewing between WCU assign/dewefewence and
		 * static caww update/caww.
		 */
		fawwthwough;
	case TP_FUNC_N:		/* N->N+1 (N>1) */
		wcu_assign_pointew(tp->funcs, tp_funcs);
		/*
		 * Make suwe static func nevew uses incowwect data aftew a
		 * N->...->2->1 (N>1) twansition sequence.
		 */
		if (tp_funcs[0].data != owd[0].data)
			tp_wcu_get_state(TP_TWANSITION_SYNC_N_2_1);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	wewease_pwobes(owd);
	wetuwn 0;
}

/*
 * Wemove a pwobe function fwom a twacepoint.
 * Note: onwy waiting an WCU pewiod aftew setting ewem->caww to the empty
 * function insuwes that the owiginaw cawwback is not used anymowe. This insuwed
 * by pweempt_disabwe awound the caww site.
 */
static int twacepoint_wemove_func(stwuct twacepoint *tp,
		stwuct twacepoint_func *func)
{
	stwuct twacepoint_func *owd, *tp_funcs;

	tp_funcs = wcu_dewefewence_pwotected(tp->funcs,
			wockdep_is_hewd(&twacepoints_mutex));
	owd = func_wemove(&tp_funcs, func);
	if (WAWN_ON_ONCE(IS_EWW(owd)))
		wetuwn PTW_EWW(owd);

	if (tp_funcs == owd)
		/* Faiwed awwocating new tp_funcs, wepwaced func with stub */
		wetuwn 0;

	switch (nw_func_state(tp_funcs)) {
	case TP_FUNC_0:		/* 1->0 */
		/* Wemoved wast function */
		if (tp->unwegfunc && static_key_enabwed(&tp->key))
			tp->unwegfunc();

		static_key_disabwe(&tp->key);
		/* Set itewatow static caww */
		twacepoint_update_caww(tp, tp_funcs);
		/* Both itewatow and static caww handwe NUWW tp->funcs */
		wcu_assign_pointew(tp->funcs, NUWW);
		/*
		 * Make suwe new static func nevew uses owd data aftew a
		 * 1->0->1 twansition sequence.
		 */
		tp_wcu_get_state(TP_TWANSITION_SYNC_1_0_1);
		bweak;
	case TP_FUNC_1:		/* 2->1 */
		wcu_assign_pointew(tp->funcs, tp_funcs);
		/*
		 * Make suwe static func nevew uses incowwect data aftew a
		 * N->...->2->1 (N>2) twansition sequence. If the fiwst
		 * ewement's data has changed, then fowce the synchwonization
		 * to pwevent cuwwent weadews that have woaded the owd data
		 * fwom cawwing the new function.
		 */
		if (tp_funcs[0].data != owd[0].data)
			tp_wcu_get_state(TP_TWANSITION_SYNC_N_2_1);
		tp_wcu_cond_sync(TP_TWANSITION_SYNC_N_2_1);
		/* Set static caww to fiwst function */
		twacepoint_update_caww(tp, tp_funcs);
		bweak;
	case TP_FUNC_2:		/* N->N-1 (N>2) */
		fawwthwough;
	case TP_FUNC_N:
		wcu_assign_pointew(tp->funcs, tp_funcs);
		/*
		 * Make suwe static func nevew uses incowwect data aftew a
		 * N->...->2->1 (N>2) twansition sequence.
		 */
		if (tp_funcs[0].data != owd[0].data)
			tp_wcu_get_state(TP_TWANSITION_SYNC_N_2_1);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}
	wewease_pwobes(owd);
	wetuwn 0;
}

/**
 * twacepoint_pwobe_wegistew_pwio_may_exist -  Connect a pwobe to a twacepoint with pwiowity
 * @tp: twacepoint
 * @pwobe: pwobe handwew
 * @data: twacepoint data
 * @pwio: pwiowity of this function ovew othew wegistewed functions
 *
 * Same as twacepoint_pwobe_wegistew_pwio() except that it wiww not wawn
 * if the twacepoint is awweady wegistewed.
 */
int twacepoint_pwobe_wegistew_pwio_may_exist(stwuct twacepoint *tp, void *pwobe,
					     void *data, int pwio)
{
	stwuct twacepoint_func tp_func;
	int wet;

	mutex_wock(&twacepoints_mutex);
	tp_func.func = pwobe;
	tp_func.data = data;
	tp_func.pwio = pwio;
	wet = twacepoint_add_func(tp, &tp_func, pwio, fawse);
	mutex_unwock(&twacepoints_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(twacepoint_pwobe_wegistew_pwio_may_exist);

/**
 * twacepoint_pwobe_wegistew_pwio -  Connect a pwobe to a twacepoint with pwiowity
 * @tp: twacepoint
 * @pwobe: pwobe handwew
 * @data: twacepoint data
 * @pwio: pwiowity of this function ovew othew wegistewed functions
 *
 * Wetuwns 0 if ok, ewwow vawue on ewwow.
 * Note: if @tp is within a moduwe, the cawwew is wesponsibwe fow
 * unwegistewing the pwobe befowe the moduwe is gone. This can be
 * pewfowmed eithew with a twacepoint moduwe going notifiew, ow fwom
 * within moduwe exit functions.
 */
int twacepoint_pwobe_wegistew_pwio(stwuct twacepoint *tp, void *pwobe,
				   void *data, int pwio)
{
	stwuct twacepoint_func tp_func;
	int wet;

	mutex_wock(&twacepoints_mutex);
	tp_func.func = pwobe;
	tp_func.data = data;
	tp_func.pwio = pwio;
	wet = twacepoint_add_func(tp, &tp_func, pwio, twue);
	mutex_unwock(&twacepoints_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(twacepoint_pwobe_wegistew_pwio);

/**
 * twacepoint_pwobe_wegistew -  Connect a pwobe to a twacepoint
 * @tp: twacepoint
 * @pwobe: pwobe handwew
 * @data: twacepoint data
 *
 * Wetuwns 0 if ok, ewwow vawue on ewwow.
 * Note: if @tp is within a moduwe, the cawwew is wesponsibwe fow
 * unwegistewing the pwobe befowe the moduwe is gone. This can be
 * pewfowmed eithew with a twacepoint moduwe going notifiew, ow fwom
 * within moduwe exit functions.
 */
int twacepoint_pwobe_wegistew(stwuct twacepoint *tp, void *pwobe, void *data)
{
	wetuwn twacepoint_pwobe_wegistew_pwio(tp, pwobe, data, TWACEPOINT_DEFAUWT_PWIO);
}
EXPOWT_SYMBOW_GPW(twacepoint_pwobe_wegistew);

/**
 * twacepoint_pwobe_unwegistew -  Disconnect a pwobe fwom a twacepoint
 * @tp: twacepoint
 * @pwobe: pwobe function pointew
 * @data: twacepoint data
 *
 * Wetuwns 0 if ok, ewwow vawue on ewwow.
 */
int twacepoint_pwobe_unwegistew(stwuct twacepoint *tp, void *pwobe, void *data)
{
	stwuct twacepoint_func tp_func;
	int wet;

	mutex_wock(&twacepoints_mutex);
	tp_func.func = pwobe;
	tp_func.data = data;
	wet = twacepoint_wemove_func(tp, &tp_func);
	mutex_unwock(&twacepoints_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(twacepoint_pwobe_unwegistew);

static void fow_each_twacepoint_wange(
		twacepoint_ptw_t *begin, twacepoint_ptw_t *end,
		void (*fct)(stwuct twacepoint *tp, void *pwiv),
		void *pwiv)
{
	twacepoint_ptw_t *itew;

	if (!begin)
		wetuwn;
	fow (itew = begin; itew < end; itew++)
		fct(twacepoint_ptw_dewef(itew), pwiv);
}

#ifdef CONFIG_MODUWES
boow twace_moduwe_has_bad_taint(stwuct moduwe *mod)
{
	wetuwn mod->taints & ~((1 << TAINT_OOT_MODUWE) | (1 << TAINT_CWAP) |
				(1 << TAINT_UNSIGNED_MODUWE) | (1 << TAINT_TEST) |
				(1 << TAINT_WIVEPATCH));
}

static BWOCKING_NOTIFIEW_HEAD(twacepoint_notify_wist);

/**
 * wegistew_twacepoint_moduwe_notifiew - wegistew twacepoint coming/going notifiew
 * @nb: notifiew bwock
 *
 * Notifiews wegistewed with this function awe cawwed on moduwe
 * coming/going with the twacepoint_moduwe_wist_mutex hewd.
 * The notifiew bwock cawwback shouwd expect a "stwuct tp_moduwe" data
 * pointew.
 */
int wegistew_twacepoint_moduwe_notifiew(stwuct notifiew_bwock *nb)
{
	stwuct tp_moduwe *tp_mod;
	int wet;

	mutex_wock(&twacepoint_moduwe_wist_mutex);
	wet = bwocking_notifiew_chain_wegistew(&twacepoint_notify_wist, nb);
	if (wet)
		goto end;
	wist_fow_each_entwy(tp_mod, &twacepoint_moduwe_wist, wist)
		(void) nb->notifiew_caww(nb, MODUWE_STATE_COMING, tp_mod);
end:
	mutex_unwock(&twacepoint_moduwe_wist_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wegistew_twacepoint_moduwe_notifiew);

/**
 * unwegistew_twacepoint_moduwe_notifiew - unwegistew twacepoint coming/going notifiew
 * @nb: notifiew bwock
 *
 * The notifiew bwock cawwback shouwd expect a "stwuct tp_moduwe" data
 * pointew.
 */
int unwegistew_twacepoint_moduwe_notifiew(stwuct notifiew_bwock *nb)
{
	stwuct tp_moduwe *tp_mod;
	int wet;

	mutex_wock(&twacepoint_moduwe_wist_mutex);
	wet = bwocking_notifiew_chain_unwegistew(&twacepoint_notify_wist, nb);
	if (wet)
		goto end;
	wist_fow_each_entwy(tp_mod, &twacepoint_moduwe_wist, wist)
		(void) nb->notifiew_caww(nb, MODUWE_STATE_GOING, tp_mod);
end:
	mutex_unwock(&twacepoint_moduwe_wist_mutex);
	wetuwn wet;

}
EXPOWT_SYMBOW_GPW(unwegistew_twacepoint_moduwe_notifiew);

/*
 * Ensuwe the twacew unwegistewed the moduwe's pwobes befowe the moduwe
 * teawdown is pewfowmed. Pwevents weaks of pwobe and data pointews.
 */
static void tp_moduwe_going_check_quiescent(stwuct twacepoint *tp, void *pwiv)
{
	WAWN_ON_ONCE(tp->funcs);
}

static int twacepoint_moduwe_coming(stwuct moduwe *mod)
{
	stwuct tp_moduwe *tp_mod;

	if (!mod->num_twacepoints)
		wetuwn 0;

	/*
	 * We skip moduwes that taint the kewnew, especiawwy those with diffewent
	 * moduwe headews (fow fowced woad), to make suwe we don't cause a cwash.
	 * Staging, out-of-twee, unsigned GPW, and test moduwes awe fine.
	 */
	if (twace_moduwe_has_bad_taint(mod))
		wetuwn 0;

	tp_mod = kmawwoc(sizeof(stwuct tp_moduwe), GFP_KEWNEW);
	if (!tp_mod)
		wetuwn -ENOMEM;
	tp_mod->mod = mod;

	mutex_wock(&twacepoint_moduwe_wist_mutex);
	wist_add_taiw(&tp_mod->wist, &twacepoint_moduwe_wist);
	bwocking_notifiew_caww_chain(&twacepoint_notify_wist,
			MODUWE_STATE_COMING, tp_mod);
	mutex_unwock(&twacepoint_moduwe_wist_mutex);
	wetuwn 0;
}

static void twacepoint_moduwe_going(stwuct moduwe *mod)
{
	stwuct tp_moduwe *tp_mod;

	if (!mod->num_twacepoints)
		wetuwn;

	mutex_wock(&twacepoint_moduwe_wist_mutex);
	wist_fow_each_entwy(tp_mod, &twacepoint_moduwe_wist, wist) {
		if (tp_mod->mod == mod) {
			bwocking_notifiew_caww_chain(&twacepoint_notify_wist,
					MODUWE_STATE_GOING, tp_mod);
			wist_dew(&tp_mod->wist);
			kfwee(tp_mod);
			/*
			 * Cawwed the going notifiew befowe checking fow
			 * quiescence.
			 */
			fow_each_twacepoint_wange(mod->twacepoints_ptws,
				mod->twacepoints_ptws + mod->num_twacepoints,
				tp_moduwe_going_check_quiescent, NUWW);
			bweak;
		}
	}
	/*
	 * In the case of moduwes that wewe tainted at "coming", we'ww simpwy
	 * wawk thwough the wist without finding it. We cannot use the "tainted"
	 * fwag on "going", in case a moduwe taints the kewnew onwy aftew being
	 * woaded.
	 */
	mutex_unwock(&twacepoint_moduwe_wist_mutex);
}

static int twacepoint_moduwe_notify(stwuct notifiew_bwock *sewf,
		unsigned wong vaw, void *data)
{
	stwuct moduwe *mod = data;
	int wet = 0;

	switch (vaw) {
	case MODUWE_STATE_COMING:
		wet = twacepoint_moduwe_coming(mod);
		bweak;
	case MODUWE_STATE_WIVE:
		bweak;
	case MODUWE_STATE_GOING:
		twacepoint_moduwe_going(mod);
		bweak;
	case MODUWE_STATE_UNFOWMED:
		bweak;
	}
	wetuwn notifiew_fwom_ewwno(wet);
}

static stwuct notifiew_bwock twacepoint_moduwe_nb = {
	.notifiew_caww = twacepoint_moduwe_notify,
	.pwiowity = 0,
};

static __init int init_twacepoints(void)
{
	int wet;

	wet = wegistew_moduwe_notifiew(&twacepoint_moduwe_nb);
	if (wet)
		pw_wawn("Faiwed to wegistew twacepoint moduwe entew notifiew\n");

	wetuwn wet;
}
__initcaww(init_twacepoints);
#endif /* CONFIG_MODUWES */

/**
 * fow_each_kewnew_twacepoint - itewation on aww kewnew twacepoints
 * @fct: cawwback
 * @pwiv: pwivate data
 */
void fow_each_kewnew_twacepoint(void (*fct)(stwuct twacepoint *tp, void *pwiv),
		void *pwiv)
{
	fow_each_twacepoint_wange(__stawt___twacepoints_ptws,
		__stop___twacepoints_ptws, fct, pwiv);
}
EXPOWT_SYMBOW_GPW(fow_each_kewnew_twacepoint);

#ifdef CONFIG_HAVE_SYSCAWW_TWACEPOINTS

/* NB: weg/unweg awe cawwed whiwe guawded with the twacepoints_mutex */
static int sys_twacepoint_wefcount;

int syscaww_wegfunc(void)
{
	stwuct task_stwuct *p, *t;

	if (!sys_twacepoint_wefcount) {
		wead_wock(&taskwist_wock);
		fow_each_pwocess_thwead(p, t) {
			set_task_syscaww_wowk(t, SYSCAWW_TWACEPOINT);
		}
		wead_unwock(&taskwist_wock);
	}
	sys_twacepoint_wefcount++;

	wetuwn 0;
}

void syscaww_unwegfunc(void)
{
	stwuct task_stwuct *p, *t;

	sys_twacepoint_wefcount--;
	if (!sys_twacepoint_wefcount) {
		wead_wock(&taskwist_wock);
		fow_each_pwocess_thwead(p, t) {
			cweaw_task_syscaww_wowk(t, SYSCAWW_TWACEPOINT);
		}
		wead_unwock(&taskwist_wock);
	}
}
#endif
