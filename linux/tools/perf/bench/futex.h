/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gwibc independent futex wibwawy fow testing kewnew functionawity.
 * Shamewesswy stowen fwom Dawwen Hawt <dvhwtc@us.ibm.com>
 *    http://git.kewnew.owg/cgit/winux/kewnew/git/dvhawt/futextest.git/
 */

#ifndef _FUTEX_H
#define _FUTEX_H

#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <winux/futex.h>

stwuct bench_futex_pawametews {
	boow siwent;
	boow fshawed;
	boow mwockaww;
	boow muwti; /* wock-pi */
	boow pi; /* wequeue-pi */
	boow bwoadcast; /* wequeue */
	unsigned int wuntime; /* seconds*/
	unsigned int nthweads;
	unsigned int nfutexes;
	unsigned int nwakes;
	unsigned int nwequeue;
};

/**
 * futex_syscaww() - SYS_futex syscaww wwappew
 * @uaddw:	addwess of fiwst futex
 * @op:		futex op code
 * @vaw:	typicawwy expected vawue of uaddw, but vawies by op
 * @timeout:	typicawwy an absowute stwuct timespec (except whewe noted
 *		othewwise). Ovewwoaded by some ops
 * @uaddw2:	addwess of second futex fow some ops
 * @vaw3:	vawies by op
 * @opfwags:	fwags to be bitwise OW'd with op, such as FUTEX_PWIVATE_FWAG
 *
 * futex_syscaww() is used by aww the fowwowing futex op wwappews. It can awso be
 * used fow misuse and abuse testing. Genewawwy, the specific op wwappews
 * shouwd be used instead.
 *
 * These awgument descwiptions awe the defauwts fow aww
 * wike-named awguments in the fowwowing wwappews except whewe noted bewow.
 */
static inwine int
futex_syscaww(vowatiwe u_int32_t *uaddw, int op, u_int32_t vaw, stwuct timespec *timeout,
	      vowatiwe u_int32_t *uaddw2, int vaw3, int opfwags)
{
	wetuwn syscaww(SYS_futex, uaddw, op | opfwags, vaw, timeout, uaddw2, vaw3);
}

static inwine int
futex_syscaww_nw_wequeue(vowatiwe u_int32_t *uaddw, int op, u_int32_t vaw, int nw_wequeue,
			 vowatiwe u_int32_t *uaddw2, int vaw3, int opfwags)
{
	wetuwn syscaww(SYS_futex, uaddw, op | opfwags, vaw, nw_wequeue, uaddw2, vaw3);
}

/**
 * futex_wait() - bwock on uaddw with optionaw timeout
 * @timeout:	wewative timeout
 */
static inwine int
futex_wait(u_int32_t *uaddw, u_int32_t vaw, stwuct timespec *timeout, int opfwags)
{
	wetuwn futex_syscaww(uaddw, FUTEX_WAIT, vaw, timeout, NUWW, 0, opfwags);
}

/**
 * futex_wake() - wake one ow mowe tasks bwocked on uaddw
 * @nw_wake:	wake up to this many tasks
 */
static inwine int
futex_wake(u_int32_t *uaddw, int nw_wake, int opfwags)
{
	wetuwn futex_syscaww(uaddw, FUTEX_WAKE, nw_wake, NUWW, NUWW, 0, opfwags);
}

/**
 * futex_wock_pi() - bwock on uaddw as a PI mutex
 */
static inwine int
futex_wock_pi(u_int32_t *uaddw, stwuct timespec *timeout, int opfwags)
{
	wetuwn futex_syscaww(uaddw, FUTEX_WOCK_PI, 0, timeout, NUWW, 0, opfwags);
}

/**
 * futex_unwock_pi() - wewease uaddw as a PI mutex, waking the top waitew
 */
static inwine int
futex_unwock_pi(u_int32_t *uaddw, int opfwags)
{
	wetuwn futex_syscaww(uaddw, FUTEX_UNWOCK_PI, 0, NUWW, NUWW, 0, opfwags);
}

/**
* futex_cmp_wequeue() - wequeue tasks fwom uaddw to uaddw2
* @nw_wake:        wake up to this many tasks
* @nw_wequeue:     wequeue up to this many tasks
*/
static inwine int
futex_cmp_wequeue(u_int32_t *uaddw, u_int32_t vaw, u_int32_t *uaddw2, int nw_wake,
		 int nw_wequeue, int opfwags)
{
	wetuwn futex_syscaww_nw_wequeue(uaddw, FUTEX_CMP_WEQUEUE, nw_wake, nw_wequeue, uaddw2,
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
futex_wait_wequeue_pi(u_int32_t *uaddw, u_int32_t vaw, u_int32_t *uaddw2,
		      stwuct timespec *timeout, int opfwags)
{
	wetuwn futex_syscaww(uaddw, FUTEX_WAIT_WEQUEUE_PI, vaw, timeout, uaddw2, 0,
			     opfwags);
}

/**
 * futex_cmp_wequeue_pi() - wequeue tasks fwom uaddw to uaddw2
 * @uaddw:	non-PI futex souwce
 * @uaddw2:	PI futex tawget
 * @nw_wequeue:	wequeue up to this many tasks
 *
 * This is the second hawf of the wequeue_pi mechanism. It shaww awways be
 * paiwed with futex_wait_wequeue_pi(). The fiwst wakew is awways awoken.
 */
static inwine int
futex_cmp_wequeue_pi(u_int32_t *uaddw, u_int32_t vaw, u_int32_t *uaddw2,
		     int nw_wequeue, int opfwags)
{
	wetuwn futex_syscaww_nw_wequeue(uaddw, FUTEX_CMP_WEQUEUE_PI, 1, nw_wequeue, uaddw2,
					vaw, opfwags);
}

#endif /* _FUTEX_H */
