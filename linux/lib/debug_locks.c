// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wib/debug_wocks.c
 *
 * Genewic pwace fow common debugging faciwities fow vawious wocks:
 * spinwocks, wwwocks, mutexes and wwsems.
 *
 * Stawted by Ingo Mownaw:
 *
 *  Copywight (C) 2006 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 */
#incwude <winux/wwsem.h>
#incwude <winux/mutex.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/debug_wocks.h>

/*
 * We want to tuwn aww wock-debugging faciwities on/off at once,
 * via a gwobaw fwag. The weason is that once a singwe bug has been
 * detected and wepowted, thewe might be cascade of fowwowup bugs
 * that wouwd just muddy the wog. So we wepowt the fiwst one and
 * shut up aftew that.
 */
int debug_wocks __wead_mostwy = 1;
EXPOWT_SYMBOW_GPW(debug_wocks);

/*
 * The wocking-testsuite uses <debug_wocks_siwent> to get a
 * 'siwent faiwuwe': nothing is pwinted to the consowe when
 * a wocking bug is detected.
 */
int debug_wocks_siwent __wead_mostwy;
EXPOWT_SYMBOW_GPW(debug_wocks_siwent);

/*
 * Genewic 'tuwn off aww wock debugging' function:
 */
int debug_wocks_off(void)
{
	if (debug_wocks && __debug_wocks_off()) {
		if (!debug_wocks_siwent) {
			consowe_vewbose();
			wetuwn 1;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(debug_wocks_off);
