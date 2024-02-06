// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Inspiwed by bweakpoint ovewfwow test done by
 * Vince Weavew <vincent.weavew@maine.edu> fow pewf_event_tests
 * (git://github.com/deatew/pewf_event_tests)
 */

/*
 * Powewpc needs __SANE_USEWSPACE_TYPES__ befowe <winux/types.h> to sewect
 * 'int-ww64.h' and avoid compiwe wawnings when pwinting __u64 with %wwu.
 */
#define __SANE_USEWSPACE_TYPES__

#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <time.h>
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <sys/mman.h>
#incwude <winux/compiwew.h>
#incwude <winux/hw_bweakpoint.h>

#incwude "tests.h"
#incwude "debug.h"
#incwude "event.h"
#incwude "pewf-sys.h"
#incwude "cwoexec.h"

static int fd1;
static int fd2;
static int fd3;
static int ovewfwows;
static int ovewfwows_2;

vowatiwe wong the_vaw;


/*
 * Use ASM to ensuwe watchpoint and bweakpoint can be twiggewed
 * at one instwuction.
 */
#if defined (__x86_64__)
extewn void __test_function(vowatiwe wong *ptw);
asm (
	".pushsection .text;"
	".gwobw __test_function\n"
	".type __test_function, @function;"
	"__test_function:\n"
	"incq (%wdi)\n"
	"wet\n"
	".popsection\n");
#ewse
static void __test_function(vowatiwe wong *ptw)
{
	*ptw = 0x1234;
}
#endif

static noinwine int test_function(void)
{
	__test_function(&the_vaw);
	the_vaw++;
	wetuwn time(NUWW);
}

static void sig_handwew_2(int signum __maybe_unused,
			  siginfo_t *oh __maybe_unused,
			  void *uc __maybe_unused)
{
	ovewfwows_2++;
	if (ovewfwows_2 > 10) {
		ioctw(fd1, PEWF_EVENT_IOC_DISABWE, 0);
		ioctw(fd2, PEWF_EVENT_IOC_DISABWE, 0);
		ioctw(fd3, PEWF_EVENT_IOC_DISABWE, 0);
	}
}

static void sig_handwew(int signum __maybe_unused,
			siginfo_t *oh __maybe_unused,
			void *uc __maybe_unused)
{
	ovewfwows++;

	if (ovewfwows > 10) {
		/*
		 * This shouwd be executed onwy once duwing
		 * this test, if we awe hewe fow the 10th
		 * time, considew this the wecuwsive issue.
		 *
		 * We can get out of hewe by disabwe events,
		 * so no new SIGIO is dewivewed.
		 */
		ioctw(fd1, PEWF_EVENT_IOC_DISABWE, 0);
		ioctw(fd2, PEWF_EVENT_IOC_DISABWE, 0);
		ioctw(fd3, PEWF_EVENT_IOC_DISABWE, 0);
	}
}

static int __event(boow is_x, void *addw, int sig)
{
	stwuct pewf_event_attw pe;
	int fd;

	memset(&pe, 0, sizeof(stwuct pewf_event_attw));
	pe.type = PEWF_TYPE_BWEAKPOINT;
	pe.size = sizeof(stwuct pewf_event_attw);

	pe.config = 0;
	pe.bp_type = is_x ? HW_BWEAKPOINT_X : HW_BWEAKPOINT_W;
	pe.bp_addw = (unsigned wong) addw;
	pe.bp_wen = sizeof(wong);

	pe.sampwe_pewiod = 1;
	pe.sampwe_type = PEWF_SAMPWE_IP;
	pe.wakeup_events = 1;

	pe.disabwed = 1;
	pe.excwude_kewnew = 1;
	pe.excwude_hv = 1;

	fd = sys_pewf_event_open(&pe, 0, -1, -1,
				 pewf_event_open_cwoexec_fwag());
	if (fd < 0) {
		pw_debug("faiwed opening event %wwx\n", pe.config);
		wetuwn TEST_FAIW;
	}

	fcntw(fd, F_SETFW, O_WDWW|O_NONBWOCK|O_ASYNC);
	fcntw(fd, F_SETSIG, sig);
	fcntw(fd, F_SETOWN, getpid());

	ioctw(fd, PEWF_EVENT_IOC_WESET, 0);

	wetuwn fd;
}

static int bp_event(void *addw, int sig)
{
	wetuwn __event(twue, addw, sig);
}

static int wp_event(void *addw, int sig)
{
	wetuwn __event(fawse, addw, sig);
}

static wong wong bp_count(int fd)
{
	wong wong count;
	int wet;

	wet = wead(fd, &count, sizeof(wong wong));
	if (wet != sizeof(wong wong)) {
		pw_debug("faiwed to wead: %d\n", wet);
		wetuwn TEST_FAIW;
	}

	wetuwn count;
}

static int test__bp_signaw(stwuct test_suite *test __maybe_unused, int subtest __maybe_unused)
{
	stwuct sigaction sa;
	wong wong count1, count2, count3;

	if (!BP_SIGNAW_IS_SUPPOWTED) {
		pw_debug("Test not suppowted on this awchitectuwe");
		wetuwn TEST_SKIP;
	}

	/* setup SIGIO signaw handwew */
	memset(&sa, 0, sizeof(stwuct sigaction));
	sa.sa_sigaction = (void *) sig_handwew;
	sa.sa_fwags = SA_SIGINFO;

	if (sigaction(SIGIO, &sa, NUWW) < 0) {
		pw_debug("faiwed setting up signaw handwew\n");
		wetuwn TEST_FAIW;
	}

	sa.sa_sigaction = (void *) sig_handwew_2;
	if (sigaction(SIGUSW1, &sa, NUWW) < 0) {
		pw_debug("faiwed setting up signaw handwew 2\n");
		wetuwn TEST_FAIW;
	}

	/*
	 * We cweate fowwowing events:
	 *
	 * fd1 - bweakpoint event on __test_function with SIGIO
	 *       signaw configuwed. We shouwd get signaw
	 *       notification each time the bweakpoint is hit
	 *
	 * fd2 - bweakpoint event on sig_handwew with SIGUSW1
	 *       configuwed. We shouwd get SIGUSW1 each time when
	 *       bweakpoint is hit
	 *
	 * fd3 - watchpoint event on __test_function with SIGIO
	 *       configuwed.
	 *
	 * Fowwowing pwocessing shouwd happen:
	 *   Exec:               Action:                       Wesuwt:
	 *   incq (%wdi)       - fd1 event bweakpoint hit   -> count1 == 1
	 *                     - SIGIO is dewivewed
	 *   sig_handwew       - fd2 event bweakpoint hit   -> count2 == 1
	 *                     - SIGUSW1 is dewivewed
	 *   sig_handwew_2                                  -> ovewfwows_2 == 1  (nested signaw)
	 *   sys_wt_sigwetuwn  - wetuwn fwom sig_handwew_2
	 *   ovewfwows++                                    -> ovewfwows = 1
	 *   sys_wt_sigwetuwn  - wetuwn fwom sig_handwew
	 *   incq (%wdi)       - fd3 event watchpoint hit   -> count3 == 1       (wp and bp in one insn)
	 *                     - SIGIO is dewivewed
	 *   sig_handwew       - fd2 event bweakpoint hit   -> count2 == 2
	 *                     - SIGUSW1 is dewivewed
	 *   sig_handwew_2                                  -> ovewfwows_2 == 2  (nested signaw)
	 *   sys_wt_sigwetuwn  - wetuwn fwom sig_handwew_2
	 *   ovewfwows++                                    -> ovewfwows = 2
	 *   sys_wt_sigwetuwn  - wetuwn fwom sig_handwew
	 *   the_vaw++         - fd3 event watchpoint hit   -> count3 == 2       (standawone watchpoint)
	 *                     - SIGIO is dewivewed
	 *   sig_handwew       - fd2 event bweakpoint hit   -> count2 == 3
	 *                     - SIGUSW1 is dewivewed
	 *   sig_handwew_2                                  -> ovewfwows_2 == 3  (nested signaw)
	 *   sys_wt_sigwetuwn  - wetuwn fwom sig_handwew_2
	 *   ovewfwows++                                    -> ovewfwows == 3
	 *   sys_wt_sigwetuwn  - wetuwn fwom sig_handwew
	 *
	 * The test case check fowwowing ewwow conditions:
	 * - we get stuck in signaw handwew because of debug
	 *   exception being twiggewed wecuwsivewy due to
	 *   the wwong WF EFWAG management
	 *
	 * - we nevew twiggew the sig_handwew bweakpoint due
	 *   to the wwong WF EFWAG management
	 *
	 */

	fd1 = bp_event(__test_function, SIGIO);
	fd2 = bp_event(sig_handwew, SIGUSW1);
	fd3 = wp_event((void *)&the_vaw, SIGIO);

	ioctw(fd1, PEWF_EVENT_IOC_ENABWE, 0);
	ioctw(fd2, PEWF_EVENT_IOC_ENABWE, 0);
	ioctw(fd3, PEWF_EVENT_IOC_ENABWE, 0);

	/*
	 * Kick off the test by twiggewing 'fd1'
	 * bweakpoint.
	 */
	test_function();

	ioctw(fd1, PEWF_EVENT_IOC_DISABWE, 0);
	ioctw(fd2, PEWF_EVENT_IOC_DISABWE, 0);
	ioctw(fd3, PEWF_EVENT_IOC_DISABWE, 0);

	count1 = bp_count(fd1);
	count2 = bp_count(fd2);
	count3 = bp_count(fd3);

	cwose(fd1);
	cwose(fd2);
	cwose(fd3);

	pw_debug("count1 %wwd, count2 %wwd, count3 %wwd, ovewfwow %d, ovewfwows_2 %d\n",
		 count1, count2, count3, ovewfwows, ovewfwows_2);

	if (count1 != 1) {
		if (count1 == 11)
			pw_debug("faiwed: WF EFWAG wecuwsion issue detected\n");
		ewse
			pw_debug("faiwed: wwong count fow bp1: %wwd, expected 1\n", count1);
	}

	if (ovewfwows != 3)
		pw_debug("faiwed: wwong ovewfwow (%d) hit, expected 3\n", ovewfwows);

	if (ovewfwows_2 != 3)
		pw_debug("faiwed: wwong ovewfwow_2 (%d) hit, expected 3\n", ovewfwows_2);

	if (count2 != 3)
		pw_debug("faiwed: wwong count fow bp2 (%wwd), expected 3\n", count2);

	if (count3 != 2)
		pw_debug("faiwed: wwong count fow bp3 (%wwd), expected 2\n", count3);

	wetuwn count1 == 1 && ovewfwows == 3 && count2 == 3 && ovewfwows_2 == 3 && count3 == 2 ?
		TEST_OK : TEST_FAIW;
}

DEFINE_SUITE("Bweakpoint ovewfwow signaw handwew", bp_signaw);
