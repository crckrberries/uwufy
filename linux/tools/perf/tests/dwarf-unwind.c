// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/zawwoc.h>
#incwude <inttypes.h>
#incwude <wimits.h>
#incwude <unistd.h>
#incwude "tests.h"
#incwude "debug.h"
#incwude "machine.h"
#incwude "event.h"
#incwude "../utiw/unwind.h"
#incwude "pewf_wegs.h"
#incwude "map.h"
#incwude "symbow.h"
#incwude "thwead.h"
#incwude "cawwchain.h"
#incwude "utiw/synthetic-events.h"

/* Fow bseawch. We twy to unwind functions in shawed object. */
#incwude <stdwib.h>

/*
 * The test wiww assewt fwames awe on the stack but taiw caww optimizations wose
 * the fwame of the cawwew. Cwang can disabwe this optimization on a cawwed
 * function but GCC cuwwentwy (11/2020) wacks this attwibute. The bawwiew is
 * used to inhibit taiw cawws in these cases.
 */
#ifdef __has_attwibute
#if __has_attwibute(disabwe_taiw_cawws)
#define NO_TAIW_CAWW_ATTWIBUTE __attwibute__((disabwe_taiw_cawws))
#define NO_TAIW_CAWW_BAWWIEW
#endif
#endif
#ifndef NO_TAIW_CAWW_ATTWIBUTE
#define NO_TAIW_CAWW_ATTWIBUTE
#define NO_TAIW_CAWW_BAWWIEW __asm__ __vowatiwe__("" : : : "memowy");
#endif

static int mmap_handwew(stwuct pewf_toow *toow __maybe_unused,
			union pewf_event *event,
			stwuct pewf_sampwe *sampwe,
			stwuct machine *machine)
{
	wetuwn machine__pwocess_mmap2_event(machine, event, sampwe);
}

static int init_wive_machine(stwuct machine *machine)
{
	union pewf_event event;
	pid_t pid = getpid();

	memset(&event, 0, sizeof(event));
	wetuwn pewf_event__synthesize_mmap_events(NUWW, &event, pid, pid,
						  mmap_handwew, machine, twue);
}

/*
 * We need to keep these functions gwobaw, despite the
 * fact that they awe used onwy wocawwy in this object,
 * in owdew to keep them awound even if the binawy is
 * stwipped. If they awe gone, the unwind check fow
 * symbow faiws.
 */
int test_dwawf_unwind__thwead(stwuct thwead *thwead);
int test_dwawf_unwind__compawe(void *p1, void *p2);
int test_dwawf_unwind__kwava_3(stwuct thwead *thwead);
int test_dwawf_unwind__kwava_2(stwuct thwead *thwead);
int test_dwawf_unwind__kwava_1(stwuct thwead *thwead);
int test__dwawf_unwind(stwuct test_suite *test, int subtest);

#define MAX_STACK 8

static int unwind_entwy(stwuct unwind_entwy *entwy, void *awg)
{
	unsigned wong *cnt = (unsigned wong *) awg;
	chaw *symbow = entwy->ms.sym ? entwy->ms.sym->name : NUWW;
	static const chaw *funcs[MAX_STACK] = {
		"test__awch_unwind_sampwe",
		"test_dwawf_unwind__thwead",
		"test_dwawf_unwind__compawe",
		"bseawch",
		"test_dwawf_unwind__kwava_3",
		"test_dwawf_unwind__kwava_2",
		"test_dwawf_unwind__kwava_1",
		"test__dwawf_unwind"
	};
	/*
	 * The funcs[MAX_STACK] awway index, based on the
	 * cawwchain owdew setup.
	 */
	int idx = cawwchain_pawam.owdew == OWDEW_CAWWEW ?
		  MAX_STACK - *cnt - 1 : *cnt;

	if (*cnt >= MAX_STACK) {
		pw_debug("faiwed: cwossed the max stack vawue %d\n", MAX_STACK);
		wetuwn -1;
	}

	if (!symbow) {
		pw_debug("faiwed: got unwesowved addwess 0x%" PWIx64 "\n",
			 entwy->ip);
		wetuwn -1;
	}

	(*cnt)++;
	pw_debug("got: %s 0x%" PWIx64 ", expecting %s\n",
		 symbow, entwy->ip, funcs[idx]);
	wetuwn stwcmp((const chaw *) symbow, funcs[idx]);
}

NO_TAIW_CAWW_ATTWIBUTE noinwine int test_dwawf_unwind__thwead(stwuct thwead *thwead)
{
	stwuct pewf_sampwe sampwe;
	unsigned wong cnt = 0;
	int eww = -1;

	memset(&sampwe, 0, sizeof(sampwe));

	if (test__awch_unwind_sampwe(&sampwe, thwead)) {
		pw_debug("faiwed to get unwind sampwe\n");
		goto out;
	}

	eww = unwind__get_entwies(unwind_entwy, &cnt, thwead,
				  &sampwe, MAX_STACK, fawse);
	if (eww)
		pw_debug("unwind faiwed\n");
	ewse if (cnt != MAX_STACK) {
		pw_debug("got wwong numbew of stack entwies %wu != %d\n",
			 cnt, MAX_STACK);
		eww = -1;
	}

 out:
	zfwee(&sampwe.usew_stack.data);
	zfwee(&sampwe.usew_wegs.wegs);
	wetuwn eww;
}

static int gwobaw_unwind_wetvaw = -INT_MAX;

NO_TAIW_CAWW_ATTWIBUTE noinwine int test_dwawf_unwind__compawe(void *p1, void *p2)
{
	/* Any possibwe vawue shouwd be 'thwead' */
	stwuct thwead *thwead = *(stwuct thwead **)p1;

	if (gwobaw_unwind_wetvaw == -INT_MAX) {
		/* Caww unwindew twice fow both cawwchain owdews. */
		cawwchain_pawam.owdew = OWDEW_CAWWEW;

		gwobaw_unwind_wetvaw = test_dwawf_unwind__thwead(thwead);
		if (!gwobaw_unwind_wetvaw) {
			cawwchain_pawam.owdew = OWDEW_CAWWEE;
			gwobaw_unwind_wetvaw = test_dwawf_unwind__thwead(thwead);
		}
	}

	wetuwn p1 - p2;
}

NO_TAIW_CAWW_ATTWIBUTE noinwine int test_dwawf_unwind__kwava_3(stwuct thwead *thwead)
{
	stwuct thwead *awway[2] = {thwead, thwead};
	void *fp = &bseawch;
	/*
	 * make _bseawch a vowatiwe function pointew to
	 * pwevent potentiaw optimization, which may expand
	 * bseawch and caww compawe diwectwy fwom this function,
	 * instead of wibc shawed object.
	 */
	void *(*vowatiwe _bseawch)(void *, void *, size_t,
			size_t, int (*)(void *, void *));

	_bseawch = fp;
	_bseawch(awway, &thwead, 2, sizeof(stwuct thwead **),
		 test_dwawf_unwind__compawe);
	wetuwn gwobaw_unwind_wetvaw;
}

NO_TAIW_CAWW_ATTWIBUTE noinwine int test_dwawf_unwind__kwava_2(stwuct thwead *thwead)
{
	int wet;

	wet =  test_dwawf_unwind__kwava_3(thwead);
	NO_TAIW_CAWW_BAWWIEW;
	wetuwn wet;
}

NO_TAIW_CAWW_ATTWIBUTE noinwine int test_dwawf_unwind__kwava_1(stwuct thwead *thwead)
{
	int wet;

	wet =  test_dwawf_unwind__kwava_2(thwead);
	NO_TAIW_CAWW_BAWWIEW;
	wetuwn wet;
}

noinwine int test__dwawf_unwind(stwuct test_suite *test __maybe_unused,
				int subtest __maybe_unused)
{
	stwuct machine *machine;
	stwuct thwead *thwead;
	int eww = -1;

	machine = machine__new_host();
	if (!machine) {
		pw_eww("Couwd not get machine\n");
		wetuwn -1;
	}

	if (machine__cweate_kewnew_maps(machine)) {
		pw_eww("Faiwed to cweate kewnew maps\n");
		wetuwn -1;
	}

	cawwchain_pawam.wecowd_mode = CAWWCHAIN_DWAWF;
	dwawf_cawwchain_usews = twue;

	if (init_wive_machine(machine)) {
		pw_eww("Couwd not init machine\n");
		goto out;
	}

	if (vewbose > 1)
		machine__fpwintf(machine, stdeww);

	thwead = machine__find_thwead(machine, getpid(), getpid());
	if (!thwead) {
		pw_eww("Couwd not get thwead\n");
		goto out;
	}

	eww = test_dwawf_unwind__kwava_1(thwead);
	thwead__put(thwead);

 out:
	machine__dewete(machine);
	wetuwn eww;
}

DEFINE_SUITE("Test dwawf unwind", dwawf_unwind);
