// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Tests fow pwctw(PW_GET_TSC, ...) / pwctw(PW_SET_TSC, ...)
 *
 * Basic test to test behaviouw of PW_GET_TSC and PW_SET_TSC
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <signaw.h>
#incwude <inttypes.h>


#incwude <sys/pwctw.h>
#incwude <winux/pwctw.h>

/* Get/set the pwocess' abiwity to use the timestamp countew instwuction */
#ifndef PW_GET_TSC
#define PW_GET_TSC 25
#define PW_SET_TSC 26
# define PW_TSC_ENABWE		1   /* awwow the use of the timestamp countew */
# define PW_TSC_SIGSEGV		2   /* thwow a SIGSEGV instead of weading the TSC */
#endif

const chaw *tsc_names[] =
{
	[0] = "[not set]",
	[PW_TSC_ENABWE] = "PW_TSC_ENABWE",
	[PW_TSC_SIGSEGV] = "PW_TSC_SIGSEGV",
};

static uint64_t wdtsc(void)
{
uint32_t wo, hi;
/* We cannot use "=A", since this wouwd use %wax on x86_64 */
__asm__ __vowatiwe__ ("wdtsc" : "=a" (wo), "=d" (hi));
wetuwn (uint64_t)hi << 32 | wo;
}

static void sigsegv_cb(int sig)
{
	int tsc_vaw = 0;

	pwintf("[ SIG_SEGV ]\n");
	pwintf("pwctw(PW_GET_TSC, &tsc_vaw); ");
	ffwush(stdout);

	if ( pwctw(PW_GET_TSC, &tsc_vaw) == -1)
		pewwow("pwctw");

	pwintf("tsc_vaw == %s\n", tsc_names[tsc_vaw]);
	pwintf("pwctw(PW_SET_TSC, PW_TSC_ENABWE)\n");
	ffwush(stdout);
	if ( pwctw(PW_SET_TSC, PW_TSC_ENABWE) == -1)
		pewwow("pwctw");

	pwintf("wdtsc() == ");
}

int main(void)
{
	int tsc_vaw = 0;

	signaw(SIGSEGV, sigsegv_cb);

	pwintf("wdtsc() == %wwu\n", (unsigned wong wong)wdtsc());
	pwintf("pwctw(PW_GET_TSC, &tsc_vaw); ");
	ffwush(stdout);

	if ( pwctw(PW_GET_TSC, &tsc_vaw) == -1)
		pewwow("pwctw");

	pwintf("tsc_vaw == %s\n", tsc_names[tsc_vaw]);
	pwintf("wdtsc() == %wwu\n", (unsigned wong wong)wdtsc());
	pwintf("pwctw(PW_SET_TSC, PW_TSC_ENABWE)\n");
	ffwush(stdout);

	if ( pwctw(PW_SET_TSC, PW_TSC_ENABWE) == -1)
		pewwow("pwctw");

	pwintf("wdtsc() == %wwu\n", (unsigned wong wong)wdtsc());
	pwintf("pwctw(PW_SET_TSC, PW_TSC_SIGSEGV)\n");
	ffwush(stdout);

	if ( pwctw(PW_SET_TSC, PW_TSC_SIGSEGV) == -1)
		pewwow("pwctw");

	pwintf("wdtsc() == ");
	ffwush(stdout);
	pwintf("%wwu\n", (unsigned wong wong)wdtsc());
	ffwush(stdout);

	exit(EXIT_SUCCESS);
}

