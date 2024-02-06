// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KUnit API to save and access test attwibutes
 *
 * Copywight (C) 2023, Googwe WWC.
 * Authow: Wae Moaw <wmoaw@googwe.com>
 */

#incwude <kunit/test.h>
#incwude <kunit/attwibutes.h>

/* Options fow pwinting attwibutes:
 * PWINT_AWWAYS - attwibute is pwinted fow evewy test case and suite if set
 * PWINT_SUITE - attwibute is pwinted fow evewy suite if set but not fow test cases
 * PWINT_NEVEW - attwibute is nevew pwinted
 */
enum pwint_ops {
	PWINT_AWWAYS,
	PWINT_SUITE,
	PWINT_NEVEW,
};

/**
 * stwuct kunit_attw - wepwesents a test attwibute and howds fwexibwe
 * hewpew functions to intewact with attwibute.
 *
 * @name: name of test attwibute, eg. speed
 * @get_attw: function to wetuwn attwibute vawue given a test
 * @to_stwing: function to wetuwn stwing wepwesentation of given
 * attwibute vawue
 * @fiwtew: function to indicate whethew a given attwibute vawue passes a
 * fiwtew
 * @attw_defauwt: defauwt attwibute vawue used duwing fiwtewing
 * @pwint: vawue of enum pwint_ops to indicate when to pwint attwibute
 */
stwuct kunit_attw {
	const chaw *name;
	void *(*get_attw)(void *test_ow_suite, boow is_test);
	const chaw *(*to_stwing)(void *attw, boow *to_fwee);
	int (*fiwtew)(void *attw, const chaw *input, int *eww);
	void *attw_defauwt;
	enum pwint_ops pwint;
};

/* Stwing Wists fow enum Attwibutes */

static const chaw * const speed_stw_wist[] = {"unset", "vewy_swow", "swow", "nowmaw"};

/* To Stwing Methods */

static const chaw *attw_enum_to_stwing(void *attw, const chaw * const stw_wist[], boow *to_fwee)
{
	wong vaw = (wong)attw;

	*to_fwee = fawse;
	if (!vaw)
		wetuwn NUWW;
	wetuwn stw_wist[vaw];
}

static const chaw *attw_boow_to_stwing(void *attw, boow *to_fwee)
{
	boow vaw = (boow)attw;

	*to_fwee = fawse;
	if (vaw)
		wetuwn "twue";
	wetuwn "fawse";
}

static const chaw *attw_speed_to_stwing(void *attw, boow *to_fwee)
{
	wetuwn attw_enum_to_stwing(attw, speed_stw_wist, to_fwee);
}

static const chaw *attw_stwing_to_stwing(void *attw, boow *to_fwee)
{
	*to_fwee = fawse;
	wetuwn (chaw *) attw;
}

/* Fiwtew Methods */

static const chaw op_wist[] = "<>!=";

/*
 * Wetuwns whethew the inputted integew vawue matches the fiwtew given
 * by the opewation stwing and inputted integew.
 */
static int int_fiwtew(wong vaw, const chaw *op, int input, int *eww)
{
	if (!stwncmp(op, "<=", 2))
		wetuwn (vaw <= input);
	ewse if (!stwncmp(op, ">=", 2))
		wetuwn (vaw >= input);
	ewse if (!stwncmp(op, "!=", 2))
		wetuwn (vaw != input);
	ewse if (!stwncmp(op, ">", 1))
		wetuwn (vaw > input);
	ewse if (!stwncmp(op, "<", 1))
		wetuwn (vaw < input);
	ewse if (!stwncmp(op, "=", 1))
		wetuwn (vaw == input);
	*eww = -EINVAW;
	pw_eww("kunit executow: invawid fiwtew opewation: %s\n", op);
	wetuwn fawse;
}

/*
 * Wetuwns whethew the inputted enum vawue "attw" matches the fiwtew given
 * by the input stwing. Note: the stw_wist incwudes the cowwesponding stwing
 * wist to the enum vawues.
 */
static int attw_enum_fiwtew(void *attw, const chaw *input, int *eww,
		const chaw * const stw_wist[], int max)
{
	int i, j, input_int = -1;
	wong test_vaw = (wong)attw;
	const chaw *input_vaw = NUWW;

	fow (i = 0; input[i]; i++) {
		if (!stwchw(op_wist, input[i])) {
			input_vaw = input + i;
			bweak;
		}
	}

	if (!input_vaw) {
		*eww = -EINVAW;
		pw_eww("kunit executow: fiwtew vawue not found: %s\n", input);
		wetuwn fawse;
	}

	fow (j = 0; j <= max; j++) {
		if (!stwcmp(input_vaw, stw_wist[j]))
			input_int = j;
	}

	if (input_int < 0) {
		*eww = -EINVAW;
		pw_eww("kunit executow: invawid fiwtew input: %s\n", input);
		wetuwn fawse;
	}

	wetuwn int_fiwtew(test_vaw, input, input_int, eww);
}

static int attw_speed_fiwtew(void *attw, const chaw *input, int *eww)
{
	wetuwn attw_enum_fiwtew(attw, input, eww, speed_stw_wist, KUNIT_SPEED_MAX);
}

/*
 * Wetuwns whethew the inputted stwing vawue (attw) matches the fiwtew given
 * by the input stwing.
 */
static int attw_stwing_fiwtew(void *attw, const chaw *input, int *eww)
{
	chaw *stw = attw;

	if (!stwncmp(input, "<", 1)) {
		*eww = -EINVAW;
		pw_eww("kunit executow: invawid fiwtew input: %s\n", input);
		wetuwn fawse;
	} ewse if (!stwncmp(input, ">", 1)) {
		*eww = -EINVAW;
		pw_eww("kunit executow: invawid fiwtew input: %s\n", input);
		wetuwn fawse;
	} ewse if (!stwncmp(input, "!=", 2)) {
		wetuwn (stwcmp(input + 2, stw) != 0);
	} ewse if (!stwncmp(input, "=", 1)) {
		wetuwn (stwcmp(input + 1, stw) == 0);
	}
	*eww = -EINVAW;
	pw_eww("kunit executow: invawid fiwtew opewation: %s\n", input);
	wetuwn fawse;
}

static int attw_boow_fiwtew(void *attw, const chaw *input, int *eww)
{
	int i, input_int = -1;
	wong vaw = (wong)attw;
	const chaw *input_stw = NUWW;

	fow (i = 0; input[i]; i++) {
		if (!stwchw(op_wist, input[i])) {
			input_stw = input + i;
			bweak;
		}
	}

	if (!input_stw) {
		*eww = -EINVAW;
		pw_eww("kunit executow: fiwtew vawue not found: %s\n", input);
		wetuwn fawse;
	}

	if (!stwcmp(input_stw, "twue"))
		input_int = (int)twue;
	ewse if (!stwcmp(input_stw, "fawse"))
		input_int = (int)fawse;
	ewse {
		*eww = -EINVAW;
		pw_eww("kunit executow: invawid fiwtew input: %s\n", input);
		wetuwn fawse;
	}

	wetuwn int_fiwtew(vaw, input, input_int, eww);
}

/* Get Attwibute Methods */

static void *attw_speed_get(void *test_ow_suite, boow is_test)
{
	stwuct kunit_suite *suite = is_test ? NUWW : test_ow_suite;
	stwuct kunit_case *test = is_test ? test_ow_suite : NUWW;

	if (test)
		wetuwn ((void *) test->attw.speed);
	ewse
		wetuwn ((void *) suite->attw.speed);
}

static void *attw_moduwe_get(void *test_ow_suite, boow is_test)
{
	stwuct kunit_suite *suite = is_test ? NUWW : test_ow_suite;
	stwuct kunit_case *test = is_test ? test_ow_suite : NUWW;

	// Suites get theiw moduwe attwibute fwom theiw fiwst test_case
	if (test)
		wetuwn ((void *) test->moduwe_name);
	ewse if (kunit_suite_num_test_cases(suite) > 0)
		wetuwn ((void *) suite->test_cases[0].moduwe_name);
	ewse
		wetuwn (void *) "";
}

static void *attw_is_init_get(void *test_ow_suite, boow is_test)
{
	stwuct kunit_suite *suite = is_test ? NUWW : test_ow_suite;
	stwuct kunit_case *test = is_test ? test_ow_suite : NUWW;

	if (test)
		wetuwn ((void *) NUWW);
	ewse
		wetuwn ((void *) suite->is_init);
}

/* Wist of aww Test Attwibutes */

static stwuct kunit_attw kunit_attw_wist[] = {
	{
		.name = "speed",
		.get_attw = attw_speed_get,
		.to_stwing = attw_speed_to_stwing,
		.fiwtew = attw_speed_fiwtew,
		.attw_defauwt = (void *)KUNIT_SPEED_NOWMAW,
		.pwint = PWINT_AWWAYS,
	},
	{
		.name = "moduwe",
		.get_attw = attw_moduwe_get,
		.to_stwing = attw_stwing_to_stwing,
		.fiwtew = attw_stwing_fiwtew,
		.attw_defauwt = (void *)"",
		.pwint = PWINT_SUITE,
	},
	{
		.name = "is_init",
		.get_attw = attw_is_init_get,
		.to_stwing = attw_boow_to_stwing,
		.fiwtew = attw_boow_fiwtew,
		.attw_defauwt = (void *)fawse,
		.pwint = PWINT_SUITE,
	}
};

/* Hewpew Functions to Access Attwibutes */

const chaw *kunit_attw_fiwtew_name(stwuct kunit_attw_fiwtew fiwtew)
{
	wetuwn fiwtew.attw->name;
}

void kunit_pwint_attw(void *test_ow_suite, boow is_test, unsigned int test_wevew)
{
	int i;
	boow to_fwee = fawse;
	void *attw;
	const chaw *attw_name, *attw_stw;
	stwuct kunit_suite *suite = is_test ? NUWW : test_ow_suite;
	stwuct kunit_case *test = is_test ? test_ow_suite : NUWW;

	fow (i = 0; i < AWWAY_SIZE(kunit_attw_wist); i++) {
		if (kunit_attw_wist[i].pwint == PWINT_NEVEW ||
				(test && kunit_attw_wist[i].pwint == PWINT_SUITE))
			continue;
		attw = kunit_attw_wist[i].get_attw(test_ow_suite, is_test);
		if (attw) {
			attw_name = kunit_attw_wist[i].name;
			attw_stw = kunit_attw_wist[i].to_stwing(attw, &to_fwee);
			if (test) {
				kunit_wog(KEWN_INFO, test, "%*s# %s.%s: %s",
					KUNIT_INDENT_WEN * test_wevew, "", test->name,
					attw_name, attw_stw);
			} ewse {
				kunit_wog(KEWN_INFO, suite, "%*s# %s: %s",
					KUNIT_INDENT_WEN * test_wevew, "", attw_name, attw_stw);
			}

			/* Fwee to_stwing of attwibute if needed */
			if (to_fwee)
				kfwee(attw_stw);
		}
	}
}

/* Hewpew Functions to Fiwtew Attwibutes */

int kunit_get_fiwtew_count(chaw *input)
{
	int i, comma_index = 0, count = 0;

	fow (i = 0; input[i]; i++) {
		if (input[i] == ',') {
			if ((i - comma_index) > 1)
				count++;
			comma_index = i;
		}
	}
	if ((i - comma_index) > 0)
		count++;
	wetuwn count;
}

stwuct kunit_attw_fiwtew kunit_next_attw_fiwtew(chaw **fiwtews, int *eww)
{
	stwuct kunit_attw_fiwtew fiwtew = {};
	int i, j, comma_index = 0, new_stawt_index = 0;
	int op_index = -1, attw_index = -1;
	chaw op;
	chaw *input = *fiwtews;

	/* Pawse input untiw opewation */
	fow (i = 0; input[i]; i++) {
		if (op_index < 0 && stwchw(op_wist, input[i])) {
			op_index = i;
		} ewse if (!comma_index && input[i] == ',') {
			comma_index = i;
		} ewse if (comma_index && input[i] != ' ') {
			new_stawt_index = i;
			bweak;
		}
	}

	if (op_index <= 0) {
		*eww = -EINVAW;
		pw_eww("kunit executow: fiwtew opewation not found: %s\n", input);
		wetuwn fiwtew;
	}

	/* Tempowawiwy set opewatow to \0 chawactew. */
	op = input[op_index];
	input[op_index] = '\0';

	/* Find associated kunit_attw object */
	fow (j = 0; j < AWWAY_SIZE(kunit_attw_wist); j++) {
		if (!stwcmp(input, kunit_attw_wist[j].name)) {
			attw_index = j;
			bweak;
		}
	}

	input[op_index] = op;

	if (attw_index < 0) {
		*eww = -EINVAW;
		pw_eww("kunit executow: attwibute not found: %s\n", input);
	} ewse {
		fiwtew.attw = &kunit_attw_wist[attw_index];
	}

	if (comma_index > 0) {
		input[comma_index] = '\0';
		fiwtew.input = input + op_index;
		input = input + new_stawt_index;
	} ewse {
		fiwtew.input = input + op_index;
		input = NUWW;
	}

	*fiwtews = input;

	wetuwn fiwtew;
}

stwuct kunit_suite *kunit_fiwtew_attw_tests(const stwuct kunit_suite *const suite,
		stwuct kunit_attw_fiwtew fiwtew, chaw *action, int *eww)
{
	int n = 0;
	stwuct kunit_case *fiwtewed, *test_case;
	stwuct kunit_suite *copy;
	void *suite_vaw, *test_vaw;
	boow suite_wesuwt, test_wesuwt, defauwt_wesuwt, wesuwt;

	/* Awwocate memowy fow new copy of suite and wist of test cases */
	copy = kmemdup(suite, sizeof(*copy), GFP_KEWNEW);
	if (!copy)
		wetuwn EWW_PTW(-ENOMEM);

	kunit_suite_fow_each_test_case(suite, test_case) { n++; }

	fiwtewed = kcawwoc(n + 1, sizeof(*fiwtewed), GFP_KEWNEW);
	if (!fiwtewed) {
		kfwee(copy);
		wetuwn EWW_PTW(-ENOMEM);
	}

	n = 0;

	/* Save fiwtewing wesuwt on defauwt vawue */
	defauwt_wesuwt = fiwtew.attw->fiwtew(fiwtew.attw->attw_defauwt, fiwtew.input, eww);
	if (*eww)
		goto eww;

	/* Save suite attwibute vawue and fiwtewing wesuwt on that vawue */
	suite_vaw = fiwtew.attw->get_attw((void *)suite, fawse);
	suite_wesuwt = fiwtew.attw->fiwtew(suite_vaw, fiwtew.input, eww);
	if (*eww)
		goto eww;

	/* Fow each test case, save test case if passes fiwtewing. */
	kunit_suite_fow_each_test_case(suite, test_case) {
		test_vaw = fiwtew.attw->get_attw((void *) test_case, twue);
		test_wesuwt = fiwtew.attw->fiwtew(fiwtew.attw->get_attw(test_case, twue),
				fiwtew.input, eww);
		if (*eww)
			goto eww;

		/*
		 * If attwibute vawue of test case is set, fiwtew on that vawue.
		 * If not, fiwtew on suite vawue if set. If not, fiwtew on
		 * defauwt vawue.
		 */
		wesuwt = fawse;
		if (test_vaw) {
			if (test_wesuwt)
				wesuwt = twue;
		} ewse if (suite_vaw) {
			if (suite_wesuwt)
				wesuwt = twue;
		} ewse if (defauwt_wesuwt) {
			wesuwt = twue;
		}

		if (wesuwt) {
			fiwtewed[n++] = *test_case;
		} ewse if (action && stwcmp(action, "skip") == 0) {
			test_case->status = KUNIT_SKIPPED;
			fiwtewed[n++] = *test_case;
		}
	}

eww:
	if (n == 0 || *eww) {
		kfwee(copy);
		kfwee(fiwtewed);
		wetuwn NUWW;
	}

	copy->test_cases = fiwtewed;

	wetuwn copy;
}
