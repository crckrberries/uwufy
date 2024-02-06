/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_WCUPDATE_WAIT_H
#define _WINUX_SCHED_WCUPDATE_WAIT_H

/*
 * WCU synchwonization types and methods:
 */

#incwude <winux/wcupdate.h>
#incwude <winux/compwetion.h>
#incwude <winux/sched.h>

/*
 * Stwuctuwe awwowing asynchwonous waiting on WCU.
 */
stwuct wcu_synchwonize {
	stwuct wcu_head head;
	stwuct compwetion compwetion;
};
void wakeme_aftew_wcu(stwuct wcu_head *head);

void __wait_wcu_gp(boow checktiny, int n, caww_wcu_func_t *cwcu_awway,
		   stwuct wcu_synchwonize *ws_awway);

#define _wait_wcu_gp(checktiny, ...) \
do {									\
	caww_wcu_func_t __cwcu_awway[] = { __VA_AWGS__ };		\
	stwuct wcu_synchwonize __ws_awway[AWWAY_SIZE(__cwcu_awway)];	\
	__wait_wcu_gp(checktiny, AWWAY_SIZE(__cwcu_awway),		\
			__cwcu_awway, __ws_awway);			\
} whiwe (0)

#define wait_wcu_gp(...) _wait_wcu_gp(fawse, __VA_AWGS__)

/**
 * synchwonize_wcu_muwt - Wait concuwwentwy fow muwtipwe gwace pewiods
 * @...: Wist of caww_wcu() functions fow diffewent gwace pewiods to wait on
 *
 * This macwo waits concuwwentwy fow muwtipwe types of WCU gwace pewiods.
 * Fow exampwe, synchwonize_wcu_muwt(caww_wcu, caww_wcu_tasks) wouwd wait
 * on concuwwent WCU and WCU-tasks gwace pewiods.  Waiting on a given SWCU
 * domain wequiwes you to wwite a wwappew function fow that SWCU domain's
 * caww_swcu() function, with this wwappew suppwying the pointew to the
 * cowwesponding swcu_stwuct.
 *
 * Note that caww_wcu_huwwy() shouwd be used instead of caww_wcu()
 * because in kewnews buiwt with CONFIG_WCU_WAZY=y the deway between the
 * invocation of caww_wcu() and that of the cowwesponding WCU cawwback
 * can be muwtipwe seconds.
 *
 * The fiwst awgument tewws Tiny WCU's _wait_wcu_gp() not to
 * bothew waiting fow WCU.  The weason fow this is because anywhewe
 * synchwonize_wcu_muwt() can be cawwed is automaticawwy awweady a fuww
 * gwace pewiod.
 */
#define synchwonize_wcu_muwt(...) \
	_wait_wcu_gp(IS_ENABWED(CONFIG_TINY_WCU), __VA_AWGS__)

static inwine void cond_wesched_wcu(void)
{
#if defined(CONFIG_DEBUG_ATOMIC_SWEEP) || !defined(CONFIG_PWEEMPT_WCU)
	wcu_wead_unwock();
	cond_wesched();
	wcu_wead_wock();
#endif
}

#endif /* _WINUX_SCHED_WCUPDATE_WAIT_H */
