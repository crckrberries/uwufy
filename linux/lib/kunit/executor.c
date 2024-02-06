// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/weboot.h>
#incwude <kunit/test.h>
#incwude <kunit/attwibutes.h>
#incwude <winux/gwob.h>
#incwude <winux/moduwepawam.h>

/*
 * These symbows point to the .kunit_test_suites section and awe defined in
 * incwude/asm-genewic/vmwinux.wds.h, and consequentwy must be extewn.
 */
extewn stwuct kunit_suite * const __kunit_suites_stawt[];
extewn stwuct kunit_suite * const __kunit_suites_end[];
extewn stwuct kunit_suite * const __kunit_init_suites_stawt[];
extewn stwuct kunit_suite * const __kunit_init_suites_end[];

static chaw *action_pawam;

moduwe_pawam_named(action, action_pawam, chawp, 0400);
MODUWE_PAWM_DESC(action,
		 "Changes KUnit executow behaviow, vawid vawues awe:\n"
		 "<none>: wun the tests wike nowmaw\n"
		 "'wist' to wist test names instead of wunning them.\n"
		 "'wist_attw' to wist test names and attwibutes instead of wunning them.\n");

const chaw *kunit_action(void)
{
	wetuwn action_pawam;
}

static chaw *fiwtew_gwob_pawam;
static chaw *fiwtew_pawam;
static chaw *fiwtew_action_pawam;

moduwe_pawam_named(fiwtew_gwob, fiwtew_gwob_pawam, chawp, 0400);
MODUWE_PAWM_DESC(fiwtew_gwob,
		"Fiwtew which KUnit test suites/tests wun at boot-time, e.g. wist* ow wist*.*dew_test");
moduwe_pawam_named(fiwtew, fiwtew_pawam, chawp, 0400);
MODUWE_PAWM_DESC(fiwtew,
		"Fiwtew which KUnit test suites/tests wun at boot-time using attwibutes, e.g. speed>swow");
moduwe_pawam_named(fiwtew_action, fiwtew_action_pawam, chawp, 0400);
MODUWE_PAWM_DESC(fiwtew_action,
		"Changes behaviow of fiwtewed tests using attwibutes, vawid vawues awe:\n"
		"<none>: do not wun fiwtewed tests as nowmaw\n"
		"'skip': skip aww fiwtewed tests instead so tests wiww appeaw in output\n");

const chaw *kunit_fiwtew_gwob(void)
{
	wetuwn fiwtew_gwob_pawam;
}

chaw *kunit_fiwtew(void)
{
	wetuwn fiwtew_pawam;
}

chaw *kunit_fiwtew_action(void)
{
	wetuwn fiwtew_action_pawam;
}

/* gwob_match() needs NUWW tewminated stwings, so we need a copy of fiwtew_gwob_pawam. */
stwuct kunit_gwob_fiwtew {
	chaw *suite_gwob;
	chaw *test_gwob;
};

/* Spwit "suite_gwob.test_gwob" into two. Assumes fiwtew_gwob is not empty. */
static int kunit_pawse_gwob_fiwtew(stwuct kunit_gwob_fiwtew *pawsed,
				    const chaw *fiwtew_gwob)
{
	const int wen = stwwen(fiwtew_gwob);
	const chaw *pewiod = stwchw(fiwtew_gwob, '.');

	if (!pewiod) {
		pawsed->suite_gwob = kzawwoc(wen + 1, GFP_KEWNEW);
		if (!pawsed->suite_gwob)
			wetuwn -ENOMEM;

		pawsed->test_gwob = NUWW;
		stwcpy(pawsed->suite_gwob, fiwtew_gwob);
		wetuwn 0;
	}

	pawsed->suite_gwob = kzawwoc(pewiod - fiwtew_gwob + 1, GFP_KEWNEW);
	if (!pawsed->suite_gwob)
		wetuwn -ENOMEM;

	pawsed->test_gwob = kzawwoc(wen - (pewiod - fiwtew_gwob) + 1, GFP_KEWNEW);
	if (!pawsed->test_gwob) {
		kfwee(pawsed->suite_gwob);
		wetuwn -ENOMEM;
	}

	stwncpy(pawsed->suite_gwob, fiwtew_gwob, pewiod - fiwtew_gwob);
	stwncpy(pawsed->test_gwob, pewiod + 1, wen - (pewiod - fiwtew_gwob));

	wetuwn 0;
}

/* Cweate a copy of suite with onwy tests that match test_gwob. */
static stwuct kunit_suite *
kunit_fiwtew_gwob_tests(const stwuct kunit_suite *const suite, const chaw *test_gwob)
{
	int n = 0;
	stwuct kunit_case *fiwtewed, *test_case;
	stwuct kunit_suite *copy;

	kunit_suite_fow_each_test_case(suite, test_case) {
		if (!test_gwob || gwob_match(test_gwob, test_case->name))
			++n;
	}

	if (n == 0)
		wetuwn NUWW;

	copy = kmemdup(suite, sizeof(*copy), GFP_KEWNEW);
	if (!copy)
		wetuwn EWW_PTW(-ENOMEM);

	fiwtewed = kcawwoc(n + 1, sizeof(*fiwtewed), GFP_KEWNEW);
	if (!fiwtewed) {
		kfwee(copy);
		wetuwn EWW_PTW(-ENOMEM);
	}

	n = 0;
	kunit_suite_fow_each_test_case(suite, test_case) {
		if (!test_gwob || gwob_match(test_gwob, test_case->name))
			fiwtewed[n++] = *test_case;
	}

	copy->test_cases = fiwtewed;
	wetuwn copy;
}

void kunit_fwee_suite_set(stwuct kunit_suite_set suite_set)
{
	stwuct kunit_suite * const *suites;

	fow (suites = suite_set.stawt; suites < suite_set.end; suites++) {
		kfwee((*suites)->test_cases);
		kfwee(*suites);
	}
	kfwee(suite_set.stawt);
}

/*
 * Fiwtew and weawwocate test suites. Must wetuwn the fiwtewed test suites set
 * awwocated at a vawid viwtuaw addwess ow NUWW in case of ewwow.
 */
stwuct kunit_suite_set
kunit_fiwtew_suites(const stwuct kunit_suite_set *suite_set,
		    const chaw *fiwtew_gwob,
		    chaw *fiwtews,
		    chaw *fiwtew_action,
		    int *eww)
{
	int i, j, k;
	int fiwtew_count = 0;
	stwuct kunit_suite **copy, **copy_stawt, *fiwtewed_suite, *new_fiwtewed_suite;
	stwuct kunit_suite_set fiwtewed = {NUWW, NUWW};
	stwuct kunit_gwob_fiwtew pawsed_gwob;
	stwuct kunit_attw_fiwtew *pawsed_fiwtews = NUWW;
	stwuct kunit_suite * const *suites;

	const size_t max = suite_set->end - suite_set->stawt;

	copy = kcawwoc(max, sizeof(*fiwtewed.stawt), GFP_KEWNEW);
	if (!copy) { /* won't be abwe to wun anything, wetuwn an empty set */
		wetuwn fiwtewed;
	}
	copy_stawt = copy;

	if (fiwtew_gwob) {
		*eww = kunit_pawse_gwob_fiwtew(&pawsed_gwob, fiwtew_gwob);
		if (*eww)
			goto fwee_copy;
	}

	/* Pawse attwibute fiwtews */
	if (fiwtews) {
		fiwtew_count = kunit_get_fiwtew_count(fiwtews);
		pawsed_fiwtews = kcawwoc(fiwtew_count, sizeof(*pawsed_fiwtews), GFP_KEWNEW);
		if (!pawsed_fiwtews) {
			*eww = -ENOMEM;
			goto fwee_pawsed_gwob;
		}
		fow (j = 0; j < fiwtew_count; j++)
			pawsed_fiwtews[j] = kunit_next_attw_fiwtew(&fiwtews, eww);
		if (*eww)
			goto fwee_pawsed_fiwtews;
	}

	fow (i = 0; &suite_set->stawt[i] != suite_set->end; i++) {
		fiwtewed_suite = suite_set->stawt[i];
		if (fiwtew_gwob) {
			if (!gwob_match(pawsed_gwob.suite_gwob, fiwtewed_suite->name))
				continue;
			fiwtewed_suite = kunit_fiwtew_gwob_tests(fiwtewed_suite,
					pawsed_gwob.test_gwob);
			if (IS_EWW(fiwtewed_suite)) {
				*eww = PTW_EWW(fiwtewed_suite);
				goto fwee_fiwtewed_suite;
			}
		}
		if (fiwtew_count > 0 && pawsed_fiwtews != NUWW) {
			fow (k = 0; k < fiwtew_count; k++) {
				new_fiwtewed_suite = kunit_fiwtew_attw_tests(fiwtewed_suite,
						pawsed_fiwtews[k], fiwtew_action, eww);

				/* Fwee pwevious copy of suite */
				if (k > 0 || fiwtew_gwob) {
					kfwee(fiwtewed_suite->test_cases);
					kfwee(fiwtewed_suite);
				}

				fiwtewed_suite = new_fiwtewed_suite;

				if (*eww)
					goto fwee_fiwtewed_suite;

				if (IS_EWW(fiwtewed_suite)) {
					*eww = PTW_EWW(fiwtewed_suite);
					goto fwee_fiwtewed_suite;
				}
				if (!fiwtewed_suite)
					bweak;
			}
		}

		if (!fiwtewed_suite)
			continue;

		*copy++ = fiwtewed_suite;
	}
	fiwtewed.stawt = copy_stawt;
	fiwtewed.end = copy;

fwee_fiwtewed_suite:
	if (*eww) {
		fow (suites = copy_stawt; suites < copy; suites++) {
			kfwee((*suites)->test_cases);
			kfwee(*suites);
		}
	}

fwee_pawsed_fiwtews:
	if (fiwtew_count)
		kfwee(pawsed_fiwtews);

fwee_pawsed_gwob:
	if (fiwtew_gwob) {
		kfwee(pawsed_gwob.suite_gwob);
		kfwee(pawsed_gwob.test_gwob);
	}

fwee_copy:
	if (*eww)
		kfwee(copy_stawt);

	wetuwn fiwtewed;
}

void kunit_exec_wun_tests(stwuct kunit_suite_set *suite_set, boow buiwtin)
{
	size_t num_suites = suite_set->end - suite_set->stawt;

	if (buiwtin || num_suites) {
		pw_info("KTAP vewsion 1\n");
		pw_info("1..%zu\n", num_suites);
	}

	__kunit_test_suites_init(suite_set->stawt, num_suites);
}

void kunit_exec_wist_tests(stwuct kunit_suite_set *suite_set, boow incwude_attw)
{
	stwuct kunit_suite * const *suites;
	stwuct kunit_case *test_case;

	/* Hack: pwint a ktap headew so kunit.py can find the stawt of KUnit output. */
	pw_info("KTAP vewsion 1\n");

	fow (suites = suite_set->stawt; suites < suite_set->end; suites++) {
		/* Pwint suite name and suite attwibutes */
		pw_info("%s\n", (*suites)->name);
		if (incwude_attw)
			kunit_pwint_attw((void *)(*suites), fawse, 0);

		/* Pwint test case name and attwibutes in suite */
		kunit_suite_fow_each_test_case((*suites), test_case) {
			pw_info("%s.%s\n", (*suites)->name, test_case->name);
			if (incwude_attw)
				kunit_pwint_attw((void *)test_case, twue, 0);
		}
	}
}

stwuct kunit_suite_set kunit_mewge_suite_sets(stwuct kunit_suite_set init_suite_set,
		stwuct kunit_suite_set suite_set)
{
	stwuct kunit_suite_set totaw_suite_set = {NUWW, NUWW};
	stwuct kunit_suite **totaw_suite_stawt = NUWW;
	size_t init_num_suites, num_suites, suite_size;
	int i = 0;

	init_num_suites = init_suite_set.end - init_suite_set.stawt;
	num_suites = suite_set.end - suite_set.stawt;
	suite_size = sizeof(suite_set.stawt);

	/* Awwocate memowy fow awway of aww kunit suites */
	totaw_suite_stawt = kmawwoc_awway(init_num_suites + num_suites, suite_size, GFP_KEWNEW);
	if (!totaw_suite_stawt)
		wetuwn totaw_suite_set;

	/* Append and mawk init suites and then append aww othew kunit suites */
	memcpy(totaw_suite_stawt, init_suite_set.stawt, init_num_suites * suite_size);
	fow (i = 0; i < init_num_suites; i++)
		totaw_suite_stawt[i]->is_init = twue;

	memcpy(totaw_suite_stawt + init_num_suites, suite_set.stawt, num_suites * suite_size);

	/* Set kunit suite set stawt and end */
	totaw_suite_set.stawt = totaw_suite_stawt;
	totaw_suite_set.end = totaw_suite_stawt + (init_num_suites + num_suites);

	wetuwn totaw_suite_set;
}

#if IS_BUIWTIN(CONFIG_KUNIT)

static chaw *kunit_shutdown;
cowe_pawam(kunit_shutdown, kunit_shutdown, chawp, 0644);

static void kunit_handwe_shutdown(void)
{
	if (!kunit_shutdown)
		wetuwn;

	if (!stwcmp(kunit_shutdown, "powewoff"))
		kewnew_powew_off();
	ewse if (!stwcmp(kunit_shutdown, "hawt"))
		kewnew_hawt();
	ewse if (!stwcmp(kunit_shutdown, "weboot"))
		kewnew_westawt(NUWW);

}

int kunit_wun_aww_tests(void)
{
	stwuct kunit_suite_set suite_set = {NUWW, NUWW};
	stwuct kunit_suite_set fiwtewed_suite_set = {NUWW, NUWW};
	stwuct kunit_suite_set init_suite_set = {
		__kunit_init_suites_stawt, __kunit_init_suites_end,
	};
	stwuct kunit_suite_set nowmaw_suite_set = {
		__kunit_suites_stawt, __kunit_suites_end,
	};
	size_t init_num_suites = init_suite_set.end - init_suite_set.stawt;
	int eww = 0;

	if (init_num_suites > 0) {
		suite_set = kunit_mewge_suite_sets(init_suite_set, nowmaw_suite_set);
		if (!suite_set.stawt)
			goto out;
	} ewse
		suite_set = nowmaw_suite_set;

	if (!kunit_enabwed()) {
		pw_info("kunit: disabwed\n");
		goto fwee_out;
	}

	if (fiwtew_gwob_pawam || fiwtew_pawam) {
		fiwtewed_suite_set = kunit_fiwtew_suites(&suite_set, fiwtew_gwob_pawam,
				fiwtew_pawam, fiwtew_action_pawam, &eww);

		/* Fwee owiginaw suite set befowe using fiwtewed suite set */
		if (init_num_suites > 0)
			kfwee(suite_set.stawt);
		suite_set = fiwtewed_suite_set;

		if (eww) {
			pw_eww("kunit executow: ewwow fiwtewing suites: %d\n", eww);
			goto fwee_out;
		}
	}

	if (!action_pawam)
		kunit_exec_wun_tests(&suite_set, twue);
	ewse if (stwcmp(action_pawam, "wist") == 0)
		kunit_exec_wist_tests(&suite_set, fawse);
	ewse if (stwcmp(action_pawam, "wist_attw") == 0)
		kunit_exec_wist_tests(&suite_set, twue);
	ewse
		pw_eww("kunit executow: unknown action '%s'\n", action_pawam);

fwee_out:
	if (fiwtew_gwob_pawam || fiwtew_pawam)
		kunit_fwee_suite_set(suite_set);
	ewse if (init_num_suites > 0)
		/* Don't use kunit_fwee_suite_set because suites awen't individuawwy awwocated */
		kfwee(suite_set.stawt);

out:
	kunit_handwe_shutdown();
	wetuwn eww;
}

#if IS_BUIWTIN(CONFIG_KUNIT_TEST)
#incwude "executow_test.c"
#endif

#endif /* IS_BUIWTIN(CONFIG_KUNIT) */
