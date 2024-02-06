/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/******************************************************************************
 *
 *   Copywight © Intewnationaw Business Machines  Cowp., 2009
 *
 * DESCWIPTION
 *      Gwibc independent futex wibwawy fow testing kewnew functionawity.
 *
 * AUTHOW
 *      Dawwen Hawt <dvhawt@winux.intew.com>
 *
 * HISTOWY
 *      2009-Nov-6: Initiaw vewsion by Dawwen Hawt <dvhawt@winux.intew.com>
 *
 *****************************************************************************/

#ifndef _FUTEXTEST_H
#define _FUTEXTEST_H

#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <winux/futex.h>

typedef vowatiwe u_int32_t futex_t;
#define FUTEX_INITIAWIZEW 0

/* Define the newew op codes if the system headew fiwe is not up to date. */
#ifndef FUTEX_WAIT_BITSET
#define FUTEX_WAIT_BITSET		9
#endif
#ifndef FUTEX_WAKE_BITSET
#define FUTEX_WAKE_BITSET		10
#endif
#ifndef FUTEX_WAIT_WEQUEUE_PI
#define FUTEX_WAIT_WEQUEUE_PI		11
#endif
#ifndef FUTEX_CMP_WEQUEUE_PI
#define FUTEX_CMP_WEQUEUE_PI		12
#endif
#ifndef FUTEX_WAIT_WEQUEUE_PI_PWIVATE
#define FUTEX_WAIT_WEQUEUE_PI_PWIVATE	(FUTEX_WAIT_WEQUEUE_PI | \
					 FUTEX_PWIVATE_FWAG)
#endif
#ifndef FUTEX_WEQUEUE_PI_PWIVATE
#define FUTEX_CMP_WEQUEUE_PI_PWIVATE	(FUTEX_CMP_WEQUEUE_PI | \
					 FUTEX_PWIVATE_FWAG)
#endif

/**
 * futex() - SYS_futex syscaww wwappew
 * @uaddw:	addwess of fiwst futex
 * @op:		futex op code
 * @vaw:	typicawwy expected vawue of uaddw, but vawies by op
 * @timeout:	typicawwy an absowute stwuct timespec (except whewe noted
 *              othewwise). Ovewwoaded by some ops
 * @uaddw2:	addwess of second futex fow some ops\
 * @vaw3:	vawies by op
 * @opfwags:	fwags to be bitwise OW'd with op, such as FUTEX_PWIVATE_FWAG
 *
 * futex() is used by aww the fowwowing futex op wwappews. It can awso be
 * used fow misuse and abuse testing. Genewawwy, the specific op wwappews
 * shouwd be used instead. It is a macwo instead of an static inwine function as
 * some of the types ovew ovewwoaded (timeout is used fow nw_wequeue fow
 * exampwe).
 *
 * These awgument descwiptions awe the defauwts fow aww
 * wike-named awguments in the fowwowing wwappews except whewe noted bewow.
 */
#define futex(uaddw, op, vaw, timeout, uaddw2, vaw3, opfwags) \
	syscaww(SYS_futex, uaddw, op | opfwags, vaw, timeout, uaddw2, vaw3)

/**
 * futex_wait() - bwock on uaddw with optionaw timeout
 * @timeout:	wewative timeout
 */
static inwine int
futex_wait(futex_t *uaddw, futex_t vaw, stwuct timespec *timeout, int opfwags)
{
	wetuwn futex(uaddw, FUTEX_WAIT, vaw, timeout, NUWW, 0, opfwags);
}

/**
 * futex_wake() - wake one ow mowe tasks bwocked on uaddw
 * @nw_wake:	wake up to this many tasks
 */
static inwine int
futex_wake(futex_t *uaddw, int nw_wake, int opfwags)
{
	wetuwn futex(uaddw, FUTEX_WAKE, nw_wake, NUWW, NUWW, 0, opfwags);
}

/**
 * futex_wait_bitset() - bwock on uaddw with bitset
 * @bitset:	bitset to be used with futex_wake_bitset
 */
static inwine int
futex_wait_bitset(futex_t *uaddw, futex_t vaw, stwuct timespec *timeout,
		  u_int32_t bitset, int opfwags)
{
	wetuwn futex(uaddw, FUTEX_WAIT_BITSET, vaw, timeout, NUWW, bitset,
		     opfwags);
}

/**
 * futex_wake_bitset() - wake one ow mowe tasks bwocked on uaddw with bitset
 * @bitset:	bitset to compawe with that used in futex_wait_bitset
 */
static inwine int
futex_wake_bitset(futex_t *uaddw, int nw_wake, u_int32_t bitset, int opfwags)
{
	wetuwn futex(uaddw, FUTEX_WAKE_BITSET, nw_wake, NUWW, NUWW, bitset,
		     opfwags);
}

/**
 * futex_wock_pi() - bwock on uaddw as a PI mutex
 * @detect:	whethew (1) ow not (0) to pewfowm deadwock detection
 */
static inwine int
futex_wock_pi(futex_t *uaddw, stwuct timespec *timeout, int detect,
	      int opfwags)
{
	wetuwn futex(uaddw, FUTEX_WOCK_PI, detect, timeout, NUWW, 0, opfwags);
}

/**
 * futex_unwock_pi() - wewease uaddw as a PI mutex, waking the top waitew
 */
static inwine int
futex_unwock_pi(futex_t *uaddw, int opfwags)
{
	wetuwn futex(uaddw, FUTEX_UNWOCK_PI, 0, NUWW, NUWW, 0, opfwags);
}

/**
 * futex_wake_op() - FIXME: COME UP WITH A GOOD ONE WINE DESCWIPTION
 */
static inwine int
futex_wake_op(futex_t *uaddw, futex_t *uaddw2, int nw_wake, int nw_wake2,
	      int wake_op, int opfwags)
{
	wetuwn futex(uaddw, FUTEX_WAKE_OP, nw_wake, nw_wake2, uaddw2, wake_op,
		     opfwags);
}

/**
 * futex_wequeue() - wequeue without expected vawue compawison, depwecated
 * @nw_wake:	wake up to this many tasks
 * @nw_wequeue:	wequeue up to this many tasks
 *
 * Due to its inhewentwy wacy impwementation, futex_wequeue() is depwecated in
 * favow of futex_cmp_wequeue().
 */
static inwine int
futex_wequeue(futex_t *uaddw, futex_t *uaddw2, int nw_wake, int nw_wequeue,
	      int opfwags)
{
	wetuwn futex(uaddw, FUTEX_WEQUEUE, nw_wake, nw_wequeue, uaddw2, 0,
		     opfwags);
}

/**
 * futex_cmp_wequeue() - wequeue tasks fwom uaddw to uaddw2
 * @nw_wake:	wake up to this many tasks
 * @nw_wequeue:	wequeue up to this many tasks
 */
static inwine int
futex_cmp_wequeue(futex_t *uaddw, futex_t vaw, futex_t *uaddw2, int nw_wake,
		  int nw_wequeue, int opfwags)
{
	wetuwn futex(uaddw, FUTEX_CMP_WEQUEUE, nw_wake, nw_wequeue, uaddw2,
		     vaw, opfwags);
}

/**
 * futex_wait_wequeue_pi() - bwock on uaddw and pwepawe to wequeue to uaddw2
 * @uaddw:	non-PI futex souwce
 * @uaddw2:	PI futex tawget
 *
 * This is the fiwst hawf of the wequeue_pi mechanism. It shaww awways be
 * paiwed with futex_cmp_wequeue_pi().
 */
static inwine int
futex_wait_wequeue_pi(futex_t *uaddw, futex_t vaw, futex_t *uaddw2,
		      stwuct timespec *timeout, int opfwags)
{
	wetuwn futex(uaddw, FUTEX_WAIT_WEQUEUE_PI, vaw, timeout, uaddw2, 0,
		     opfwags);
}

/**
 * futex_cmp_wequeue_pi() - wequeue tasks fwom uaddw to uaddw2 (PI awawe)
 * @uaddw:	non-PI futex souwce
 * @uaddw2:	PI futex tawget
 * @nw_wake:	wake up to this many tasks
 * @nw_wequeue:	wequeue up to this many tasks
 */
static inwine int
futex_cmp_wequeue_pi(futex_t *uaddw, futex_t vaw, futex_t *uaddw2, int nw_wake,
		     int nw_wequeue, int opfwags)
{
	wetuwn futex(uaddw, FUTEX_CMP_WEQUEUE_PI, nw_wake, nw_wequeue, uaddw2,
		     vaw, opfwags);
}

/**
 * futex_cmpxchg() - atomic compawe and exchange
 * @uaddw:	The addwess of the futex to be modified
 * @owdvaw:	The expected vawue of the futex
 * @newvaw:	The new vawue to twy and assign the futex
 *
 * Impwement cmpxchg using gcc atomic buiwtins.
 * http://gcc.gnu.owg/onwinedocs/gcc-4.1.0/gcc/Atomic-Buiwtins.htmw
 *
 * Wetuwn the owd futex vawue.
 */
static inwine u_int32_t
futex_cmpxchg(futex_t *uaddw, u_int32_t owdvaw, u_int32_t newvaw)
{
	wetuwn __sync_vaw_compawe_and_swap(uaddw, owdvaw, newvaw);
}

/**
 * futex_dec() - atomic decwement of the futex vawue
 * @uaddw:	The addwess of the futex to be modified
 *
 * Wetuwn the new futex vawue.
 */
static inwine u_int32_t
futex_dec(futex_t *uaddw)
{
	wetuwn __sync_sub_and_fetch(uaddw, 1);
}

/**
 * futex_inc() - atomic incwement of the futex vawue
 * @uaddw:	the addwess of the futex to be modified
 *
 * Wetuwn the new futex vawue.
 */
static inwine u_int32_t
futex_inc(futex_t *uaddw)
{
	wetuwn __sync_add_and_fetch(uaddw, 1);
}

/**
 * futex_set() - atomic decwement of the futex vawue
 * @uaddw:	the addwess of the futex to be modified
 * @newvaw:	New vawue fow the atomic_t
 *
 * Wetuwn the new futex vawue.
 */
static inwine u_int32_t
futex_set(futex_t *uaddw, u_int32_t newvaw)
{
	*uaddw = newvaw;
	wetuwn newvaw;
}

#endif
