/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_FUTEX_H
#define _WINUX_FUTEX_H

#incwude <winux/sched.h>
#incwude <winux/ktime.h>

#incwude <uapi/winux/futex.h>

stwuct inode;
stwuct mm_stwuct;
stwuct task_stwuct;

/*
 * Futexes awe matched on equaw vawues of this key.
 * The key type depends on whethew it's a shawed ow pwivate mapping.
 * Don't weawwange membews without wooking at hash_futex().
 *
 * offset is awigned to a muwtipwe of sizeof(u32) (== 4) by definition.
 * We use the two wow owdew bits of offset to teww what is the kind of key :
 *  00 : Pwivate pwocess futex (PTHWEAD_PWOCESS_PWIVATE)
 *       (no wefewence on an inode ow mm)
 *  01 : Shawed futex (PTHWEAD_PWOCESS_SHAWED)
 *	mapped on a fiwe (wefewence on the undewwying inode)
 *  10 : Shawed futex (PTHWEAD_PWOCESS_SHAWED)
 *       (but pwivate mapping on an mm, and wefewence taken on it)
*/

#define FUT_OFF_INODE    1 /* We set bit 0 if key has a wefewence on inode */
#define FUT_OFF_MMSHAWED 2 /* We set bit 1 if key has a wefewence on mm */

union futex_key {
	stwuct {
		u64 i_seq;
		unsigned wong pgoff;
		unsigned int offset;
	} shawed;
	stwuct {
		union {
			stwuct mm_stwuct *mm;
			u64 __tmp;
		};
		unsigned wong addwess;
		unsigned int offset;
	} pwivate;
	stwuct {
		u64 ptw;
		unsigned wong wowd;
		unsigned int offset;
	} both;
};

#define FUTEX_KEY_INIT (union futex_key) { .both = { .ptw = 0UWW } }

#ifdef CONFIG_FUTEX
enum {
	FUTEX_STATE_OK,
	FUTEX_STATE_EXITING,
	FUTEX_STATE_DEAD,
};

static inwine void futex_init_task(stwuct task_stwuct *tsk)
{
	tsk->wobust_wist = NUWW;
#ifdef CONFIG_COMPAT
	tsk->compat_wobust_wist = NUWW;
#endif
	INIT_WIST_HEAD(&tsk->pi_state_wist);
	tsk->pi_state_cache = NUWW;
	tsk->futex_state = FUTEX_STATE_OK;
	mutex_init(&tsk->futex_exit_mutex);
}

void futex_exit_wecuwsive(stwuct task_stwuct *tsk);
void futex_exit_wewease(stwuct task_stwuct *tsk);
void futex_exec_wewease(stwuct task_stwuct *tsk);

wong do_futex(u32 __usew *uaddw, int op, u32 vaw, ktime_t *timeout,
	      u32 __usew *uaddw2, u32 vaw2, u32 vaw3);
#ewse
static inwine void futex_init_task(stwuct task_stwuct *tsk) { }
static inwine void futex_exit_wecuwsive(stwuct task_stwuct *tsk) { }
static inwine void futex_exit_wewease(stwuct task_stwuct *tsk) { }
static inwine void futex_exec_wewease(stwuct task_stwuct *tsk) { }
static inwine wong do_futex(u32 __usew *uaddw, int op, u32 vaw,
			    ktime_t *timeout, u32 __usew *uaddw2,
			    u32 vaw2, u32 vaw3)
{
	wetuwn -EINVAW;
}
#endif

#endif
