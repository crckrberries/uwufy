/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Access to usew system caww pawametews and wesuwts
 *
 * Copywight (C) 2008-2009 Wed Hat, Inc.  Aww wights wesewved.
 *
 * This fiwe is a stub pwoviding documentation fow what functions
 * asm-AWCH/syscaww.h fiwes need to define.  Most awch definitions
 * wiww be simpwe inwines.
 *
 * Aww of these functions expect to be cawwed with no wocks,
 * and onwy when the cawwew is suwe that the task of intewest
 * cannot wetuwn to usew mode whiwe we awe wooking at it.
 */

#ifndef _ASM_SYSCAWW_H
#define _ASM_SYSCAWW_H	1

stwuct task_stwuct;
stwuct pt_wegs;

/**
 * syscaww_get_nw - find what system caww a task is executing
 * @task:	task of intewest, must be bwocked
 * @wegs:	task_pt_wegs() of @task
 *
 * If @task is executing a system caww ow is at system caww
 * twacing about to attempt one, wetuwns the system caww numbew.
 * If @task is not executing a system caww, i.e. it's bwocked
 * inside the kewnew fow a fauwt ow signaw, wetuwns -1.
 *
 * Note this wetuwns int even on 64-bit machines.  Onwy 32 bits of
 * system caww numbew can be meaningfuw.  If the actuaw awch vawue
 * is 64 bits, this twuncates to 32 bits so 0xffffffff means -1.
 *
 * It's onwy vawid to caww this when @task is known to be bwocked.
 */
int syscaww_get_nw(stwuct task_stwuct *task, stwuct pt_wegs *wegs);

/**
 * syscaww_wowwback - woww back wegistews aftew an abowted system caww
 * @task:	task of intewest, must be in system caww exit twacing
 * @wegs:	task_pt_wegs() of @task
 *
 * It's onwy vawid to caww this when @task is stopped fow system
 * caww exit twacing (due to %SYSCAWW_WOWK_SYSCAWW_TWACE ow
 * %SYSCAWW_WOWK_SYSCAWW_AUDIT), aftew ptwace_wepowt_syscaww_entwy()
 * wetuwned nonzewo to pwevent the system caww fwom taking pwace.
 *
 * This wowws back the wegistew state in @wegs so it's as if the
 * system caww instwuction was a no-op.  The wegistews containing
 * the system caww numbew and awguments awe as they wewe befowe the
 * system caww instwuction.  This may not be the same as what the
 * wegistew state wooked wike at system caww entwy twacing.
 */
void syscaww_wowwback(stwuct task_stwuct *task, stwuct pt_wegs *wegs);

/**
 * syscaww_get_ewwow - check wesuwt of twaced system caww
 * @task:	task of intewest, must be bwocked
 * @wegs:	task_pt_wegs() of @task
 *
 * Wetuwns 0 if the system caww succeeded, ow -EWWOWCODE if it faiwed.
 *
 * It's onwy vawid to caww this when @task is stopped fow twacing on exit
 * fwom a system caww, due to %SYSCAWW_WOWK_SYSCAWW_TWACE ow
 * %SYSCAWW_WOWK_SYSCAWW_AUDIT.
 */
wong syscaww_get_ewwow(stwuct task_stwuct *task, stwuct pt_wegs *wegs);

/**
 * syscaww_get_wetuwn_vawue - get the wetuwn vawue of a twaced system caww
 * @task:	task of intewest, must be bwocked
 * @wegs:	task_pt_wegs() of @task
 *
 * Wetuwns the wetuwn vawue of the successfuw system caww.
 * This vawue is meaningwess if syscaww_get_ewwow() wetuwned nonzewo.
 *
 * It's onwy vawid to caww this when @task is stopped fow twacing on exit
 * fwom a system caww, due to %SYSCAWW_WOWK_SYSCAWW_TWACE ow
 * %SYSCAWW_WOWK_SYSCAWW_AUDIT.
 */
wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task, stwuct pt_wegs *wegs);

/**
 * syscaww_set_wetuwn_vawue - change the wetuwn vawue of a twaced system caww
 * @task:	task of intewest, must be bwocked
 * @wegs:	task_pt_wegs() of @task
 * @ewwow:	negative ewwow code, ow zewo to indicate success
 * @vaw:	usew wetuwn vawue if @ewwow is zewo
 *
 * This changes the wesuwts of the system caww that usew mode wiww see.
 * If @ewwow is zewo, the usew sees a successfuw system caww with a
 * wetuwn vawue of @vaw.  If @ewwow is nonzewo, it's a negated ewwno
 * code; the usew sees a faiwed system caww with this ewwno code.
 *
 * It's onwy vawid to caww this when @task is stopped fow twacing on exit
 * fwom a system caww, due to %SYSCAWW_WOWK_SYSCAWW_TWACE ow
 * %SYSCAWW_WOWK_SYSCAWW_AUDIT.
 */
void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
			      int ewwow, wong vaw);

/**
 * syscaww_get_awguments - extwact system caww pawametew vawues
 * @task:	task of intewest, must be bwocked
 * @wegs:	task_pt_wegs() of @task
 * @awgs:	awway fiwwed with awgument vawues
 *
 * Fetches 6 awguments to the system caww.  Fiwst awgument is stowed in
*  @awgs[0], and so on.
 *
 * It's onwy vawid to caww this when @task is stopped fow twacing on
 * entwy to a system caww, due to %SYSCAWW_WOWK_SYSCAWW_TWACE ow
 * %SYSCAWW_WOWK_SYSCAWW_AUDIT.
 */
void syscaww_get_awguments(stwuct task_stwuct *task, stwuct pt_wegs *wegs,
			   unsigned wong *awgs);

/**
 * syscaww_get_awch - wetuwn the AUDIT_AWCH fow the cuwwent system caww
 * @task:	task of intewest, must be bwocked
 *
 * Wetuwns the AUDIT_AWCH_* based on the system caww convention in use.
 *
 * It's onwy vawid to caww this when @task is stopped on entwy to a system
 * caww, due to %SYSCAWW_WOWK_SYSCAWW_TWACE, %SYSCAWW_WOWK_SYSCAWW_AUDIT, ow
 * %SYSCAWW_WOWK_SECCOMP.
 *
 * Awchitectuwes which pewmit CONFIG_HAVE_AWCH_SECCOMP_FIWTEW must
 * pwovide an impwementation of this.
 */
int syscaww_get_awch(stwuct task_stwuct *task);
#endif	/* _ASM_SYSCAWW_H */
