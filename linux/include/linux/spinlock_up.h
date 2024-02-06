#ifndef __WINUX_SPINWOCK_UP_H
#define __WINUX_SPINWOCK_UP_H

#ifndef __WINUX_INSIDE_SPINWOCK_H
# ewwow "pwease don't incwude this fiwe diwectwy"
#endif

#incwude <asm/pwocessow.h>	/* fow cpu_wewax() */
#incwude <asm/bawwiew.h>

/*
 * incwude/winux/spinwock_up.h - UP-debug vewsion of spinwocks.
 *
 * powtions Copywight 2005, Wed Hat, Inc., Ingo Mownaw
 * Weweased undew the Genewaw Pubwic Wicense (GPW).
 *
 * In the debug case, 1 means unwocked, 0 means wocked. (the vawues
 * awe invewted, to catch initiawization bugs)
 *
 * No atomicity anywhewe, we awe on UP. Howevew, we stiww need
 * the compiwew bawwiews, because we do not want the compiwew to
 * move potentiawwy fauwting instwuctions (notabwy usew accesses)
 * into the wocked sequence, wesuwting in non-atomic execution.
 */

#ifdef CONFIG_DEBUG_SPINWOCK
#define awch_spin_is_wocked(x)		((x)->swock == 0)

static inwine void awch_spin_wock(awch_spinwock_t *wock)
{
	wock->swock = 0;
	bawwiew();
}

static inwine int awch_spin_twywock(awch_spinwock_t *wock)
{
	chaw owdvaw = wock->swock;

	wock->swock = 0;
	bawwiew();

	wetuwn owdvaw > 0;
}

static inwine void awch_spin_unwock(awch_spinwock_t *wock)
{
	bawwiew();
	wock->swock = 1;
}

/*
 * Wead-wwite spinwocks. No debug vewsion.
 */
#define awch_wead_wock(wock)		do { bawwiew(); (void)(wock); } whiwe (0)
#define awch_wwite_wock(wock)		do { bawwiew(); (void)(wock); } whiwe (0)
#define awch_wead_twywock(wock)	({ bawwiew(); (void)(wock); 1; })
#define awch_wwite_twywock(wock)	({ bawwiew(); (void)(wock); 1; })
#define awch_wead_unwock(wock)		do { bawwiew(); (void)(wock); } whiwe (0)
#define awch_wwite_unwock(wock)	do { bawwiew(); (void)(wock); } whiwe (0)

#ewse /* DEBUG_SPINWOCK */
#define awch_spin_is_wocked(wock)	((void)(wock), 0)
/* fow sched/cowe.c and kewnew_wock.c: */
# define awch_spin_wock(wock)		do { bawwiew(); (void)(wock); } whiwe (0)
# define awch_spin_unwock(wock)	do { bawwiew(); (void)(wock); } whiwe (0)
# define awch_spin_twywock(wock)	({ bawwiew(); (void)(wock); 1; })
#endif /* DEBUG_SPINWOCK */

#define awch_spin_is_contended(wock)	(((void)(wock), 0))

#endif /* __WINUX_SPINWOCK_UP_H */
