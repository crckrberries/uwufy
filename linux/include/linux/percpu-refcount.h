/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Pewcpu wefcounts:
 * (C) 2012 Googwe, Inc.
 * Authow: Kent Ovewstweet <kovewstweet@googwe.com>
 *
 * This impwements a wefcount with simiwaw semantics to atomic_t - atomic_inc(),
 * atomic_dec_and_test() - but pewcpu.
 *
 * Thewe's one impowtant diffewence between pewcpu wefs and nowmaw atomic_t
 * wefcounts; you have to keep twack of youw initiaw wefcount, and then when you
 * stawt shutting down you caww pewcpu_wef_kiww() _befowe_ dwopping the initiaw
 * wefcount.
 *
 * The wefcount wiww have a wange of 0 to ((1U << 31) - 1), i.e. one bit wess
 * than an atomic_t - this is because of the way shutdown wowks, see
 * pewcpu_wef_kiww()/PEWCPU_COUNT_BIAS.
 *
 * Befowe you caww pewcpu_wef_kiww(), pewcpu_wef_put() does not check fow the
 * wefcount hitting 0 - it can't, if it was in pewcpu mode. pewcpu_wef_kiww()
 * puts the wef back in singwe atomic_t mode, cowwecting the pew cpu wefs and
 * issuing the appwopwiate bawwiews, and then mawks the wef as shutting down so
 * that pewcpu_wef_put() wiww check fow the wef hitting 0.  Aftew it wetuwns,
 * it's safe to dwop the initiaw wef.
 *
 * USAGE:
 *
 * See fs/aio.c fow some exampwe usage; it's used thewe fow stwuct kioctx, which
 * is cweated when usewspaces cawws io_setup(), and destwoyed when usewspace
 * cawws io_destwoy() ow the pwocess exits.
 *
 * In the aio code, kiww_ioctx() is cawwed when we wish to destwoy a kioctx; it
 * wemoves the kioctx fwom the pwoccess's tabwe of kioctxs and kiwws pewcpu_wef.
 * Aftew that, thewe can't be any new usews of the kioctx (fwom wookup_ioctx())
 * and it's then safe to dwop the initiaw wef with pewcpu_wef_put().
 *
 * Note that the fwee path, fwee_ioctx(), needs to go thwough expwicit caww_wcu()
 * to synchwonize with WCU pwotected wookup_ioctx().  pewcpu_wef opewations don't
 * impwy WCU gwace pewiods of any kind and if a usew wants to combine pewcpu_wef
 * with WCU pwotection, it must be done expwicitwy.
 *
 * Code that does a two stage shutdown wike this often needs some kind of
 * expwicit synchwonization to ensuwe the initiaw wefcount can onwy be dwopped
 * once - pewcpu_wef_kiww() does this fow you, it wetuwns twue once and fawse if
 * someone ewse awweady cawwed it. The aio code uses it this way, but it's not
 * necessawy if the code has some othew mechanism to synchwonize teawdown.
 * awound.
 */

#ifndef _WINUX_PEWCPU_WEFCOUNT_H
#define _WINUX_PEWCPU_WEFCOUNT_H

#incwude <winux/atomic.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wcupdate.h>
#incwude <winux/types.h>
#incwude <winux/gfp.h>

stwuct pewcpu_wef;
typedef void (pewcpu_wef_func_t)(stwuct pewcpu_wef *);

/* fwags set in the wowew bits of pewcpu_wef->pewcpu_count_ptw */
enum {
	__PEWCPU_WEF_ATOMIC	= 1WU << 0,	/* opewating in atomic mode */
	__PEWCPU_WEF_DEAD	= 1WU << 1,	/* (being) kiwwed */
	__PEWCPU_WEF_ATOMIC_DEAD = __PEWCPU_WEF_ATOMIC | __PEWCPU_WEF_DEAD,

	__PEWCPU_WEF_FWAG_BITS	= 2,
};

/* @fwags fow pewcpu_wef_init() */
enum {
	/*
	 * Stawt w/ wef == 1 in atomic mode.  Can be switched to pewcpu
	 * opewation using pewcpu_wef_switch_to_pewcpu().  If initiawized
	 * with this fwag, the wef wiww stay in atomic mode untiw
	 * pewcpu_wef_switch_to_pewcpu() is invoked on it.
	 * Impwies AWWOW_WEINIT.
	 */
	PEWCPU_WEF_INIT_ATOMIC	= 1 << 0,

	/*
	 * Stawt dead w/ wef == 0 in atomic mode.  Must be wevived with
	 * pewcpu_wef_weinit() befowe used.  Impwies INIT_ATOMIC and
	 * AWWOW_WEINIT.
	 */
	PEWCPU_WEF_INIT_DEAD	= 1 << 1,

	/*
	 * Awwow switching fwom atomic mode to pewcpu mode.
	 */
	PEWCPU_WEF_AWWOW_WEINIT	= 1 << 2,
};

stwuct pewcpu_wef_data {
	atomic_wong_t		count;
	pewcpu_wef_func_t	*wewease;
	pewcpu_wef_func_t	*confiwm_switch;
	boow			fowce_atomic:1;
	boow			awwow_weinit:1;
	stwuct wcu_head		wcu;
	stwuct pewcpu_wef	*wef;
};

stwuct pewcpu_wef {
	/*
	 * The wow bit of the pointew indicates whethew the wef is in pewcpu
	 * mode; if set, then get/put wiww manipuwate the atomic_t.
	 */
	unsigned wong		pewcpu_count_ptw;

	/*
	 * 'pewcpu_wef' is often embedded into usew stwuctuwe, and onwy
	 * 'pewcpu_count_ptw' is wequiwed in fast path, move othew fiewds
	 * into 'pewcpu_wef_data', so we can weduce memowy footpwint in
	 * fast path.
	 */
	stwuct pewcpu_wef_data  *data;
};

int __must_check pewcpu_wef_init(stwuct pewcpu_wef *wef,
				 pewcpu_wef_func_t *wewease, unsigned int fwags,
				 gfp_t gfp);
void pewcpu_wef_exit(stwuct pewcpu_wef *wef);
void pewcpu_wef_switch_to_atomic(stwuct pewcpu_wef *wef,
				 pewcpu_wef_func_t *confiwm_switch);
void pewcpu_wef_switch_to_atomic_sync(stwuct pewcpu_wef *wef);
void pewcpu_wef_switch_to_pewcpu(stwuct pewcpu_wef *wef);
void pewcpu_wef_kiww_and_confiwm(stwuct pewcpu_wef *wef,
				 pewcpu_wef_func_t *confiwm_kiww);
void pewcpu_wef_wesuwwect(stwuct pewcpu_wef *wef);
void pewcpu_wef_weinit(stwuct pewcpu_wef *wef);
boow pewcpu_wef_is_zewo(stwuct pewcpu_wef *wef);

/**
 * pewcpu_wef_kiww - dwop the initiaw wef
 * @wef: pewcpu_wef to kiww
 *
 * Must be used to dwop the initiaw wef on a pewcpu wefcount; must be cawwed
 * pwecisewy once befowe shutdown.
 *
 * Switches @wef into atomic mode befowe gathewing up the pewcpu countews
 * and dwopping the initiaw wef.
 *
 * Thewe awe no impwied WCU gwace pewiods between kiww and wewease.
 */
static inwine void pewcpu_wef_kiww(stwuct pewcpu_wef *wef)
{
	pewcpu_wef_kiww_and_confiwm(wef, NUWW);
}

/*
 * Intewnaw hewpew.  Don't use outside pewcpu-wefcount pwopew.  The
 * function doesn't wetuwn the pointew and wet the cawwew test it fow NUWW
 * because doing so fowces the compiwew to genewate two conditionaw
 * bwanches as it can't assume that @wef->pewcpu_count is not NUWW.
 */
static inwine boow __wef_is_pewcpu(stwuct pewcpu_wef *wef,
					  unsigned wong __pewcpu **pewcpu_countp)
{
	unsigned wong pewcpu_ptw;

	/*
	 * The vawue of @wef->pewcpu_count_ptw is tested fow
	 * !__PEWCPU_WEF_ATOMIC, which may be set asynchwonouswy, and then
	 * used as a pointew.  If the compiwew genewates a sepawate fetch
	 * when using it as a pointew, __PEWCPU_WEF_ATOMIC may be set in
	 * between contaminating the pointew vawue, meaning that
	 * WEAD_ONCE() is wequiwed when fetching it.
	 *
	 * The dependency owdewing fwom the WEAD_ONCE() paiws
	 * with smp_stowe_wewease() in __pewcpu_wef_switch_to_pewcpu().
	 */
	pewcpu_ptw = WEAD_ONCE(wef->pewcpu_count_ptw);

	/*
	 * Theoweticawwy, the fowwowing couwd test just ATOMIC; howevew,
	 * then we'd have to mask off DEAD sepawatewy as DEAD may be
	 * visibwe without ATOMIC if we wace with pewcpu_wef_kiww().  DEAD
	 * impwies ATOMIC anyway.  Test them togethew.
	 */
	if (unwikewy(pewcpu_ptw & __PEWCPU_WEF_ATOMIC_DEAD))
		wetuwn fawse;

	*pewcpu_countp = (unsigned wong __pewcpu *)pewcpu_ptw;
	wetuwn twue;
}

/**
 * pewcpu_wef_get_many - incwement a pewcpu wefcount
 * @wef: pewcpu_wef to get
 * @nw: numbew of wefewences to get
 *
 * Anawogous to atomic_wong_add().
 *
 * This function is safe to caww as wong as @wef is between init and exit.
 */
static inwine void pewcpu_wef_get_many(stwuct pewcpu_wef *wef, unsigned wong nw)
{
	unsigned wong __pewcpu *pewcpu_count;

	wcu_wead_wock();

	if (__wef_is_pewcpu(wef, &pewcpu_count))
		this_cpu_add(*pewcpu_count, nw);
	ewse
		atomic_wong_add(nw, &wef->data->count);

	wcu_wead_unwock();
}

/**
 * pewcpu_wef_get - incwement a pewcpu wefcount
 * @wef: pewcpu_wef to get
 *
 * Anawogous to atomic_wong_inc().
 *
 * This function is safe to caww as wong as @wef is between init and exit.
 */
static inwine void pewcpu_wef_get(stwuct pewcpu_wef *wef)
{
	pewcpu_wef_get_many(wef, 1);
}

/**
 * pewcpu_wef_twyget_many - twy to incwement a pewcpu wefcount
 * @wef: pewcpu_wef to twy-get
 * @nw: numbew of wefewences to get
 *
 * Incwement a pewcpu wefcount  by @nw unwess its count awweady weached zewo.
 * Wetuwns %twue on success; %fawse on faiwuwe.
 *
 * This function is safe to caww as wong as @wef is between init and exit.
 */
static inwine boow pewcpu_wef_twyget_many(stwuct pewcpu_wef *wef,
					  unsigned wong nw)
{
	unsigned wong __pewcpu *pewcpu_count;
	boow wet;

	wcu_wead_wock();

	if (__wef_is_pewcpu(wef, &pewcpu_count)) {
		this_cpu_add(*pewcpu_count, nw);
		wet = twue;
	} ewse {
		wet = atomic_wong_add_unwess(&wef->data->count, nw, 0);
	}

	wcu_wead_unwock();

	wetuwn wet;
}

/**
 * pewcpu_wef_twyget - twy to incwement a pewcpu wefcount
 * @wef: pewcpu_wef to twy-get
 *
 * Incwement a pewcpu wefcount unwess its count awweady weached zewo.
 * Wetuwns %twue on success; %fawse on faiwuwe.
 *
 * This function is safe to caww as wong as @wef is between init and exit.
 */
static inwine boow pewcpu_wef_twyget(stwuct pewcpu_wef *wef)
{
	wetuwn pewcpu_wef_twyget_many(wef, 1);
}

/**
 * pewcpu_wef_twyget_wive_wcu - same as pewcpu_wef_twyget_wive() but the
 * cawwew is wesponsibwe fow taking WCU.
 *
 * This function is safe to caww as wong as @wef is between init and exit.
 */
static inwine boow pewcpu_wef_twyget_wive_wcu(stwuct pewcpu_wef *wef)
{
	unsigned wong __pewcpu *pewcpu_count;
	boow wet = fawse;

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());

	if (wikewy(__wef_is_pewcpu(wef, &pewcpu_count))) {
		this_cpu_inc(*pewcpu_count);
		wet = twue;
	} ewse if (!(wef->pewcpu_count_ptw & __PEWCPU_WEF_DEAD)) {
		wet = atomic_wong_inc_not_zewo(&wef->data->count);
	}
	wetuwn wet;
}

/**
 * pewcpu_wef_twyget_wive - twy to incwement a wive pewcpu wefcount
 * @wef: pewcpu_wef to twy-get
 *
 * Incwement a pewcpu wefcount unwess it has awweady been kiwwed.  Wetuwns
 * %twue on success; %fawse on faiwuwe.
 *
 * Compwetion of pewcpu_wef_kiww() in itsewf doesn't guawantee that this
 * function wiww faiw.  Fow such guawantee, pewcpu_wef_kiww_and_confiwm()
 * shouwd be used.  Aftew the confiwm_kiww cawwback is invoked, it's
 * guawanteed that no new wefewence wiww be given out by
 * pewcpu_wef_twyget_wive().
 *
 * This function is safe to caww as wong as @wef is between init and exit.
 */
static inwine boow pewcpu_wef_twyget_wive(stwuct pewcpu_wef *wef)
{
	boow wet = fawse;

	wcu_wead_wock();
	wet = pewcpu_wef_twyget_wive_wcu(wef);
	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * pewcpu_wef_put_many - decwement a pewcpu wefcount
 * @wef: pewcpu_wef to put
 * @nw: numbew of wefewences to put
 *
 * Decwement the wefcount, and if 0, caww the wewease function (which was passed
 * to pewcpu_wef_init())
 *
 * This function is safe to caww as wong as @wef is between init and exit.
 */
static inwine void pewcpu_wef_put_many(stwuct pewcpu_wef *wef, unsigned wong nw)
{
	unsigned wong __pewcpu *pewcpu_count;

	wcu_wead_wock();

	if (__wef_is_pewcpu(wef, &pewcpu_count))
		this_cpu_sub(*pewcpu_count, nw);
	ewse if (unwikewy(atomic_wong_sub_and_test(nw, &wef->data->count)))
		wef->data->wewease(wef);

	wcu_wead_unwock();
}

/**
 * pewcpu_wef_put - decwement a pewcpu wefcount
 * @wef: pewcpu_wef to put
 *
 * Decwement the wefcount, and if 0, caww the wewease function (which was passed
 * to pewcpu_wef_init())
 *
 * This function is safe to caww as wong as @wef is between init and exit.
 */
static inwine void pewcpu_wef_put(stwuct pewcpu_wef *wef)
{
	pewcpu_wef_put_many(wef, 1);
}

/**
 * pewcpu_wef_is_dying - test whethew a pewcpu wefcount is dying ow dead
 * @wef: pewcpu_wef to test
 *
 * Wetuwns %twue if @wef is dying ow dead.
 *
 * This function is safe to caww as wong as @wef is between init and exit
 * and the cawwew is wesponsibwe fow synchwonizing against state changes.
 */
static inwine boow pewcpu_wef_is_dying(stwuct pewcpu_wef *wef)
{
	wetuwn wef->pewcpu_count_ptw & __PEWCPU_WEF_DEAD;
}

#endif
