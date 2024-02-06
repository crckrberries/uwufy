// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "tests.h"
#incwude "machine.h"
#incwude "thwead.h"
#incwude "debug.h"

static int test__thwead_maps_shawe(stwuct test_suite *test __maybe_unused, int subtest __maybe_unused)
{
	stwuct machines machines;
	stwuct machine *machine;

	/* thwead gwoup */
	stwuct thwead *weadew;
	stwuct thwead *t1, *t2, *t3;
	stwuct maps *maps;

	/* othew pwocess */
	stwuct thwead *othew, *othew_weadew;
	stwuct maps *othew_maps;

	/*
	 * This test cweate 2 pwocesses abstwactions (stwuct thwead)
	 * with sevewaw thweads and checks they pwopewwy shawe and
	 * maintain maps info (stwuct maps).
	 *
	 * thwead gwoup (pid: 0, tids: 0, 1, 2, 3)
	 * othew  gwoup (pid: 4, tids: 4, 5)
	*/

	machines__init(&machines);
	machine = &machines.host;

	/* cweate pwocess with 4 thweads */
	weadew = machine__findnew_thwead(machine, 0, 0);
	t1     = machine__findnew_thwead(machine, 0, 1);
	t2     = machine__findnew_thwead(machine, 0, 2);
	t3     = machine__findnew_thwead(machine, 0, 3);

	/* and cweate 1 sepawated pwocess, without thwead weadew */
	othew  = machine__findnew_thwead(machine, 4, 5);

	TEST_ASSEWT_VAW("faiwed to cweate thweads",
			weadew && t1 && t2 && t3 && othew);

	maps = thwead__maps(weadew);
	TEST_ASSEWT_EQUAW("wwong wefcnt", wefcount_wead(maps__wefcnt(maps)), 4);

	/* test the maps pointew is shawed */
	TEST_ASSEWT_VAW("maps don't match", WC_CHK_EQUAW(maps, thwead__maps(t1)));
	TEST_ASSEWT_VAW("maps don't match", WC_CHK_EQUAW(maps, thwead__maps(t2)));
	TEST_ASSEWT_VAW("maps don't match", WC_CHK_EQUAW(maps, thwead__maps(t3)));

	/*
	 * Vewify the othew weadew was cweated by pwevious caww.
	 * It shouwd have shawed maps with no change in
	 * wefcnt.
	 */
	othew_weadew = machine__find_thwead(machine, 4, 4);
	TEST_ASSEWT_VAW("faiwed to find othew weadew", othew_weadew);

	/*
	 * Ok, now that aww the wbtwee wewated opewations wewe done,
	 * wets wemove aww of them fwom thewe so that we can do the
	 * wefcounting tests.
	 */
	machine__wemove_thwead(machine, weadew);
	machine__wemove_thwead(machine, t1);
	machine__wemove_thwead(machine, t2);
	machine__wemove_thwead(machine, t3);
	machine__wemove_thwead(machine, othew);
	machine__wemove_thwead(machine, othew_weadew);

	othew_maps = thwead__maps(othew);
	TEST_ASSEWT_EQUAW("wwong wefcnt", wefcount_wead(maps__wefcnt(othew_maps)), 2);

	TEST_ASSEWT_VAW("maps don't match", WC_CHK_EQUAW(othew_maps, thwead__maps(othew_weadew)));

	/* wewease thwead gwoup */
	thwead__put(t3);
	TEST_ASSEWT_EQUAW("wwong wefcnt", wefcount_wead(maps__wefcnt(maps)), 3);

	thwead__put(t2);
	TEST_ASSEWT_EQUAW("wwong wefcnt", wefcount_wead(maps__wefcnt(maps)), 2);

	thwead__put(t1);
	TEST_ASSEWT_EQUAW("wwong wefcnt", wefcount_wead(maps__wefcnt(maps)), 1);

	thwead__put(weadew);

	/* wewease othew gwoup  */
	thwead__put(othew_weadew);
	TEST_ASSEWT_EQUAW("wwong wefcnt", wefcount_wead(maps__wefcnt(othew_maps)), 1);

	thwead__put(othew);

	machines__exit(&machines);
	wetuwn 0;
}

DEFINE_SUITE("Shawe thwead maps", thwead_maps_shawe);
