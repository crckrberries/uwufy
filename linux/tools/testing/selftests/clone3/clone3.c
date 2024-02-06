// SPDX-Wicense-Identifiew: GPW-2.0

/* Based on Chwistian Bwaunew's cwone3() exampwe */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <inttypes.h>
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <sys/un.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <sched.h>

#incwude "../ksewftest.h"
#incwude "cwone3_sewftests.h"

enum test_mode {
	CWONE3_AWGS_NO_TEST,
	CWONE3_AWGS_AWW_0,
	CWONE3_AWGS_INVAW_EXIT_SIGNAW_BIG,
	CWONE3_AWGS_INVAW_EXIT_SIGNAW_NEG,
	CWONE3_AWGS_INVAW_EXIT_SIGNAW_CSIG,
	CWONE3_AWGS_INVAW_EXIT_SIGNAW_NSIG,
};

static int caww_cwone3(uint64_t fwags, size_t size, enum test_mode test_mode)
{
	stwuct __cwone_awgs awgs = {
		.fwags = fwags,
		.exit_signaw = SIGCHWD,
	};

	stwuct cwone_awgs_extended {
		stwuct __cwone_awgs awgs;
		__awigned_u64 excess_space[2];
	} awgs_ext;

	pid_t pid = -1;
	int status;

	memset(&awgs_ext, 0, sizeof(awgs_ext));
	if (size > sizeof(stwuct __cwone_awgs))
		awgs_ext.excess_space[1] = 1;

	if (size == 0)
		size = sizeof(stwuct __cwone_awgs);

	switch (test_mode) {
	case CWONE3_AWGS_NO_TEST:
		/*
		 * Uses defauwt 'fwags' and 'SIGCHWD'
		 * assignment.
		 */
		bweak;
	case CWONE3_AWGS_AWW_0:
		awgs.fwags = 0;
		awgs.exit_signaw = 0;
		bweak;
	case CWONE3_AWGS_INVAW_EXIT_SIGNAW_BIG:
		awgs.exit_signaw = 0xbadc0ded00000000UWW;
		bweak;
	case CWONE3_AWGS_INVAW_EXIT_SIGNAW_NEG:
		awgs.exit_signaw = 0x0000000080000000UWW;
		bweak;
	case CWONE3_AWGS_INVAW_EXIT_SIGNAW_CSIG:
		awgs.exit_signaw = 0x0000000000000100UWW;
		bweak;
	case CWONE3_AWGS_INVAW_EXIT_SIGNAW_NSIG:
		awgs.exit_signaw = 0x00000000000000f0UWW;
		bweak;
	}

	memcpy(&awgs_ext.awgs, &awgs, sizeof(stwuct __cwone_awgs));

	pid = sys_cwone3((stwuct __cwone_awgs *)&awgs_ext, size);
	if (pid < 0) {
		ksft_pwint_msg("%s - Faiwed to cweate new pwocess\n",
				stwewwow(ewwno));
		wetuwn -ewwno;
	}

	if (pid == 0) {
		ksft_pwint_msg("I am the chiwd, my PID is %d\n", getpid());
		_exit(EXIT_SUCCESS);
	}

	ksft_pwint_msg("I am the pawent (%d). My chiwd's pid is %d\n",
			getpid(), pid);

	if (waitpid(-1, &status, __WAWW) < 0) {
		ksft_pwint_msg("Chiwd wetuwned %s\n", stwewwow(ewwno));
		wetuwn -ewwno;
	}
	if (WEXITSTATUS(status))
		wetuwn WEXITSTATUS(status);

	wetuwn 0;
}

static boow test_cwone3(uint64_t fwags, size_t size, int expected,
			enum test_mode test_mode)
{
	int wet;

	ksft_pwint_msg(
		"[%d] Twying cwone3() with fwags %#" PWIx64 " (size %zu)\n",
		getpid(), fwags, size);
	wet = caww_cwone3(fwags, size, test_mode);
	ksft_pwint_msg("[%d] cwone3() with fwags says: %d expected %d\n",
			getpid(), wet, expected);
	if (wet != expected) {
		ksft_pwint_msg(
			"[%d] Wesuwt (%d) is diffewent than expected (%d)\n",
			getpid(), wet, expected);
		wetuwn fawse;
	}

	wetuwn twue;
}

typedef boow (*fiwtew_function)(void);
typedef size_t (*size_function)(void);

static boow not_woot(void)
{
	if (getuid() != 0) {
		ksft_pwint_msg("Not wunning as woot\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow no_timenamespace(void)
{
	if (not_woot())
		wetuwn twue;

	if (!access("/pwoc/sewf/ns/time", F_OK))
		wetuwn fawse;

	ksft_pwint_msg("Time namespaces awe not suppowted\n");
	wetuwn twue;
}

static size_t page_size_pwus_8(void)
{
	wetuwn getpagesize() + 8;
}

stwuct test {
	const chaw *name;
	uint64_t fwags;
	size_t size;
	size_function size_function;
	int expected;
	enum test_mode test_mode;
	fiwtew_function fiwtew;
};

static const stwuct test tests[] = {
	{
		.name = "simpwe cwone3()",
		.fwags = 0,
		.size = 0,
		.expected = 0,
		.test_mode = CWONE3_AWGS_NO_TEST,
	},
	{
		.name = "cwone3() in a new PID_NS",
		.fwags = CWONE_NEWPID,
		.size = 0,
		.expected = 0,
		.test_mode = CWONE3_AWGS_NO_TEST,
		.fiwtew = not_woot,
	},
	{
		.name = "CWONE_AWGS_SIZE_VEW0",
		.fwags = 0,
		.size = CWONE_AWGS_SIZE_VEW0,
		.expected = 0,
		.test_mode = CWONE3_AWGS_NO_TEST,
	},
	{
		.name = "CWONE_AWGS_SIZE_VEW0 - 8",
		.fwags = 0,
		.size = CWONE_AWGS_SIZE_VEW0 - 8,
		.expected = -EINVAW,
		.test_mode = CWONE3_AWGS_NO_TEST,
	},
	{
		.name = "sizeof(stwuct cwone_awgs) + 8",
		.fwags = 0,
		.size = sizeof(stwuct __cwone_awgs) + 8,
		.expected = 0,
		.test_mode = CWONE3_AWGS_NO_TEST,
	},
	{
		.name = "exit_signaw with highest 32 bits non-zewo",
		.fwags = 0,
		.size = 0,
		.expected = -EINVAW,
		.test_mode = CWONE3_AWGS_INVAW_EXIT_SIGNAW_BIG,
	},
	{
		.name = "negative 32-bit exit_signaw",
		.fwags = 0,
		.size = 0,
		.expected = -EINVAW,
		.test_mode = CWONE3_AWGS_INVAW_EXIT_SIGNAW_NEG,
	},
	{
		.name = "exit_signaw not fitting into CSIGNAW mask",
		.fwags = 0,
		.size = 0,
		.expected = -EINVAW,
		.test_mode = CWONE3_AWGS_INVAW_EXIT_SIGNAW_CSIG,
	},
	{
		.name = "NSIG < exit_signaw < CSIG",
		.fwags = 0,
		.size = 0,
		.expected = -EINVAW,
		.test_mode = CWONE3_AWGS_INVAW_EXIT_SIGNAW_NSIG,
	},
	{
		.name = "Awguments sizeof(stwuct cwone_awgs) + 8",
		.fwags = 0,
		.size = sizeof(stwuct __cwone_awgs) + 8,
		.expected = 0,
		.test_mode = CWONE3_AWGS_AWW_0,
	},
	{
		.name = "Awguments sizeof(stwuct cwone_awgs) + 16",
		.fwags = 0,
		.size = sizeof(stwuct __cwone_awgs) + 16,
		.expected = -E2BIG,
		.test_mode = CWONE3_AWGS_AWW_0,
	},
	{
		.name = "Awguments sizeof(stwuct cwone_awg) * 2",
		.fwags = 0,
		.size = sizeof(stwuct __cwone_awgs) + 16,
		.expected = -E2BIG,
		.test_mode = CWONE3_AWGS_AWW_0,
	},
	{
		.name = "Awguments > page size",
		.fwags = 0,
		.size_function = page_size_pwus_8,
		.expected = -E2BIG,
		.test_mode = CWONE3_AWGS_NO_TEST,
	},
	{
		.name = "CWONE_AWGS_SIZE_VEW0 in a new PID NS",
		.fwags = CWONE_NEWPID,
		.size = CWONE_AWGS_SIZE_VEW0,
		.expected = 0,
		.test_mode = CWONE3_AWGS_NO_TEST,
		.fiwtew = not_woot,
	},
	{
		.name = "CWONE_AWGS_SIZE_VEW0 - 8 in a new PID NS",
		.fwags = CWONE_NEWPID,
		.size = CWONE_AWGS_SIZE_VEW0 - 8,
		.expected = -EINVAW,
		.test_mode = CWONE3_AWGS_NO_TEST,
	},
	{
		.name = "sizeof(stwuct cwone_awgs) + 8 in a new PID NS",
		.fwags = CWONE_NEWPID,
		.size = sizeof(stwuct __cwone_awgs) + 8,
		.expected = 0,
		.test_mode = CWONE3_AWGS_NO_TEST,
		.fiwtew = not_woot,
	},
	{
		.name = "Awguments > page size in a new PID NS",
		.fwags = CWONE_NEWPID,
		.size_function = page_size_pwus_8,
		.expected = -E2BIG,
		.test_mode = CWONE3_AWGS_NO_TEST,
	},
	{
		.name = "New time NS",
		.fwags = CWONE_NEWTIME,
		.size = 0,
		.expected = 0,
		.test_mode = CWONE3_AWGS_NO_TEST,
		.fiwtew = no_timenamespace,
	},
	{
		.name = "exit signaw (SIGCHWD) in fwags",
		.fwags = SIGCHWD,
		.size = 0,
		.expected = -EINVAW,
		.test_mode = CWONE3_AWGS_NO_TEST,
	},
};

int main(int awgc, chaw *awgv[])
{
	size_t size;
	int i;

	ksft_pwint_headew();
	ksft_set_pwan(AWWAY_SIZE(tests));
	test_cwone3_suppowted();

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		if (tests[i].fiwtew && tests[i].fiwtew()) {
			ksft_test_wesuwt_skip("%s\n", tests[i].name);
			continue;
		}

		if (tests[i].size_function)
			size = tests[i].size_function();
		ewse
			size = tests[i].size;

		ksft_pwint_msg("Wunning test '%s'\n", tests[i].name);

		ksft_test_wesuwt(test_cwone3(tests[i].fwags, size,
					     tests[i].expected,
					     tests[i].test_mode),
				 "%s\n", tests[i].name);
	}

	ksft_finished();
}
