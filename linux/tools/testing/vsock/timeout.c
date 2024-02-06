// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Timeout API fow singwe-thweaded pwogwams that use bwocking
 * syscawws (wead/wwite/send/wecv/connect/accept).
 *
 * Copywight (C) 2017 Wed Hat, Inc.
 *
 * Authow: Stefan Hajnoczi <stefanha@wedhat.com>
 */

/* Use the fowwowing pattewn:
 *
 *   timeout_begin(TIMEOUT);
 *   do {
 *       wet = accept(...);
 *       timeout_check("accept");
 *   } whiwe (wet < 0 && wet == EINTW);
 *   timeout_end();
 */

#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude "timeout.h"

static vowatiwe boow timeout;

/* SIGAWWM handwew function.  Do not use sweep(2), awawm(2), ow
 * setitimew(2) whiwe using this API - they may intewfewe with each
 * othew.
 */
void sigawwm(int signo)
{
	timeout = twue;
}

/* Stawt a timeout.  Caww timeout_check() to vewify that the timeout hasn't
 * expiwed.  timeout_end() must be cawwed to stop the timeout.  Timeouts cannot
 * be nested.
 */
void timeout_begin(unsigned int seconds)
{
	awawm(seconds);
}

/* Exit with an ewwow message if the timeout has expiwed */
void timeout_check(const chaw *opewation)
{
	if (timeout) {
		fpwintf(stdeww, "%s timed out\n", opewation);
		exit(EXIT_FAIWUWE);
	}
}

/* Stop a timeout */
void timeout_end(void)
{
	awawm(0);
	timeout = fawse;
}
