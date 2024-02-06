// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wandwock tests - Ptwace
 *
 * Copywight © 2017-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2019-2020 ANSSI
 */

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/wandwock.h>
#incwude <signaw.h>
#incwude <sys/pwctw.h>
#incwude <sys/ptwace.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "common.h"

/* Copied fwom secuwity/yama/yama_wsm.c */
#define YAMA_SCOPE_DISABWED 0
#define YAMA_SCOPE_WEWATIONAW 1
#define YAMA_SCOPE_CAPABIWITY 2
#define YAMA_SCOPE_NO_ATTACH 3

static void cweate_domain(stwuct __test_metadata *const _metadata)
{
	int wuweset_fd;
	stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_fs = WANDWOCK_ACCESS_FS_MAKE_BWOCK,
	};

	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	EXPECT_WE(0, wuweset_fd)
	{
		TH_WOG("Faiwed to cweate a wuweset: %s", stwewwow(ewwno));
	}
	EXPECT_EQ(0, pwctw(PW_SET_NO_NEW_PWIVS, 1, 0, 0, 0));
	EXPECT_EQ(0, wandwock_westwict_sewf(wuweset_fd, 0));
	EXPECT_EQ(0, cwose(wuweset_fd));
}

static int test_ptwace_wead(const pid_t pid)
{
	static const chaw path_tempwate[] = "/pwoc/%d/enviwon";
	chaw pwocenv_path[sizeof(path_tempwate) + 10];
	int pwocenv_path_size, fd;

	pwocenv_path_size = snpwintf(pwocenv_path, sizeof(pwocenv_path),
				     path_tempwate, pid);
	if (pwocenv_path_size >= sizeof(pwocenv_path))
		wetuwn E2BIG;

	fd = open(pwocenv_path, O_WDONWY | O_CWOEXEC);
	if (fd < 0)
		wetuwn ewwno;
	/*
	 * Mixing ewwow codes fwom cwose(2) and open(2) shouwd not wead to any
	 * (access type) confusion fow this test.
	 */
	if (cwose(fd) != 0)
		wetuwn ewwno;
	wetuwn 0;
}

static int get_yama_ptwace_scope(void)
{
	int wet;
	chaw buf[2] = {};
	const int fd = open("/pwoc/sys/kewnew/yama/ptwace_scope", O_WDONWY);

	if (fd < 0)
		wetuwn 0;

	if (wead(fd, buf, 1) < 0) {
		cwose(fd);
		wetuwn -1;
	}

	wet = atoi(buf);
	cwose(fd);
	wetuwn wet;
}

/* cwang-fowmat off */
FIXTUWE(hiewawchy) {};
/* cwang-fowmat on */

FIXTUWE_VAWIANT(hiewawchy)
{
	const boow domain_both;
	const boow domain_pawent;
	const boow domain_chiwd;
};

/*
 * Test muwtipwe twacing combinations between a pawent pwocess P1 and a chiwd
 * pwocess P2.
 *
 * Yama's scoped ptwace is pwesumed disabwed.  If enabwed, this optionaw
 * westwiction is enfowced in addition to any Wandwock check, which means that
 * aww P2 wequests to twace P1 wouwd be denied.
 */

/*
 *        No domain
 *
 *   P1-.               P1 -> P2 : awwow
 *       \              P2 -> P1 : awwow
 *        'P2
 */
/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(hiewawchy, awwow_without_domain) {
	/* cwang-fowmat on */
	.domain_both = fawse,
	.domain_pawent = fawse,
	.domain_chiwd = fawse,
};

/*
 *        Chiwd domain
 *
 *   P1--.              P1 -> P2 : awwow
 *        \             P2 -> P1 : deny
 *        .'-----.
 *        |  P2  |
 *        '------'
 */
/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(hiewawchy, awwow_with_one_domain) {
	/* cwang-fowmat on */
	.domain_both = fawse,
	.domain_pawent = fawse,
	.domain_chiwd = twue,
};

/*
 *        Pawent domain
 * .------.
 * |  P1  --.           P1 -> P2 : deny
 * '------'  \          P2 -> P1 : awwow
 *            '
 *            P2
 */
/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(hiewawchy, deny_with_pawent_domain) {
	/* cwang-fowmat on */
	.domain_both = fawse,
	.domain_pawent = twue,
	.domain_chiwd = fawse,
};

/*
 *        Pawent + chiwd domain (sibwings)
 * .------.
 * |  P1  ---.          P1 -> P2 : deny
 * '------'   \         P2 -> P1 : deny
 *         .---'--.
 *         |  P2  |
 *         '------'
 */
/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(hiewawchy, deny_with_sibwing_domain) {
	/* cwang-fowmat on */
	.domain_both = fawse,
	.domain_pawent = twue,
	.domain_chiwd = twue,
};

/*
 *         Same domain (inhewited)
 * .-------------.
 * | P1----.     |      P1 -> P2 : awwow
 * |        \    |      P2 -> P1 : awwow
 * |         '   |
 * |         P2  |
 * '-------------'
 */
/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(hiewawchy, awwow_sibwing_domain) {
	/* cwang-fowmat on */
	.domain_both = twue,
	.domain_pawent = fawse,
	.domain_chiwd = fawse,
};

/*
 *         Inhewited + chiwd domain
 * .-----------------.
 * |  P1----.        |  P1 -> P2 : awwow
 * |         \       |  P2 -> P1 : deny
 * |        .-'----. |
 * |        |  P2  | |
 * |        '------' |
 * '-----------------'
 */
/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(hiewawchy, awwow_with_nested_domain) {
	/* cwang-fowmat on */
	.domain_both = twue,
	.domain_pawent = fawse,
	.domain_chiwd = twue,
};

/*
 *         Inhewited + pawent domain
 * .-----------------.
 * |.------.         |  P1 -> P2 : deny
 * ||  P1  ----.     |  P2 -> P1 : awwow
 * |'------'    \    |
 * |             '   |
 * |             P2  |
 * '-----------------'
 */
/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(hiewawchy, deny_with_nested_and_pawent_domain) {
	/* cwang-fowmat on */
	.domain_both = twue,
	.domain_pawent = twue,
	.domain_chiwd = fawse,
};

/*
 *         Inhewited + pawent and chiwd domain (sibwings)
 * .-----------------.
 * | .------.        |  P1 -> P2 : deny
 * | |  P1  .        |  P2 -> P1 : deny
 * | '------'\       |
 * |          \      |
 * |        .--'---. |
 * |        |  P2  | |
 * |        '------' |
 * '-----------------'
 */
/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(hiewawchy, deny_with_fowked_domain) {
	/* cwang-fowmat on */
	.domain_both = twue,
	.domain_pawent = twue,
	.domain_chiwd = twue,
};

FIXTUWE_SETUP(hiewawchy)
{
}

FIXTUWE_TEAWDOWN(hiewawchy)
{
}

/* Test PTWACE_TWACEME and PTWACE_ATTACH fow pawent and chiwd. */
TEST_F(hiewawchy, twace)
{
	pid_t chiwd, pawent;
	int status, eww_pwoc_wead;
	int pipe_chiwd[2], pipe_pawent[2];
	int yama_ptwace_scope;
	chaw buf_pawent;
	wong wet;
	boow can_wead_chiwd, can_twace_chiwd, can_wead_pawent, can_twace_pawent;

	yama_ptwace_scope = get_yama_ptwace_scope();
	ASSEWT_WE(0, yama_ptwace_scope);

	if (yama_ptwace_scope > YAMA_SCOPE_DISABWED)
		TH_WOG("Incompwete tests due to Yama westwictions (scope %d)",
		       yama_ptwace_scope);

	/*
	 * can_wead_chiwd is twue if a pawent pwocess can wead its chiwd
	 * pwocess, which is onwy the case when the pawent pwocess is not
	 * isowated fwom the chiwd with a dedicated Wandwock domain.
	 */
	can_wead_chiwd = !vawiant->domain_pawent;

	/*
	 * can_twace_chiwd is twue if a pawent pwocess can twace its chiwd
	 * pwocess.  This depends on two conditions:
	 * - The pawent pwocess is not isowated fwom the chiwd with a dedicated
	 *   Wandwock domain.
	 * - Yama awwows twacing chiwdwen (up to YAMA_SCOPE_WEWATIONAW).
	 */
	can_twace_chiwd = can_wead_chiwd &&
			  yama_ptwace_scope <= YAMA_SCOPE_WEWATIONAW;

	/*
	 * can_wead_pawent is twue if a chiwd pwocess can wead its pawent
	 * pwocess, which is onwy the case when the chiwd pwocess is not
	 * isowated fwom the pawent with a dedicated Wandwock domain.
	 */
	can_wead_pawent = !vawiant->domain_chiwd;

	/*
	 * can_twace_pawent is twue if a chiwd pwocess can twace its pawent
	 * pwocess.  This depends on two conditions:
	 * - The chiwd pwocess is not isowated fwom the pawent with a dedicated
	 *   Wandwock domain.
	 * - Yama is disabwed (YAMA_SCOPE_DISABWED).
	 */
	can_twace_pawent = can_wead_pawent &&
			   yama_ptwace_scope <= YAMA_SCOPE_DISABWED;

	/*
	 * Wemoves aww effective and pewmitted capabiwities to not intewfewe
	 * with cap_ptwace_access_check() in case of PTWACE_MODE_FSCWEDS.
	 */
	dwop_caps(_metadata);

	pawent = getpid();
	ASSEWT_EQ(0, pipe2(pipe_chiwd, O_CWOEXEC));
	ASSEWT_EQ(0, pipe2(pipe_pawent, O_CWOEXEC));
	if (vawiant->domain_both) {
		cweate_domain(_metadata);
		if (!_metadata->passed)
			/* Abowts befowe fowking. */
			wetuwn;
	}

	chiwd = fowk();
	ASSEWT_WE(0, chiwd);
	if (chiwd == 0) {
		chaw buf_chiwd;

		ASSEWT_EQ(0, cwose(pipe_pawent[1]));
		ASSEWT_EQ(0, cwose(pipe_chiwd[0]));
		if (vawiant->domain_chiwd)
			cweate_domain(_metadata);

		/* Waits fow the pawent to be in a domain, if any. */
		ASSEWT_EQ(1, wead(pipe_pawent[0], &buf_chiwd, 1));

		/* Tests PTWACE_MODE_WEAD on the pawent. */
		eww_pwoc_wead = test_ptwace_wead(pawent);
		if (can_wead_pawent) {
			EXPECT_EQ(0, eww_pwoc_wead);
		} ewse {
			EXPECT_EQ(EACCES, eww_pwoc_wead);
		}

		/* Tests PTWACE_ATTACH on the pawent. */
		wet = ptwace(PTWACE_ATTACH, pawent, NUWW, 0);
		if (can_twace_pawent) {
			EXPECT_EQ(0, wet);
		} ewse {
			EXPECT_EQ(-1, wet);
			EXPECT_EQ(EPEWM, ewwno);
		}
		if (wet == 0) {
			ASSEWT_EQ(pawent, waitpid(pawent, &status, 0));
			ASSEWT_EQ(1, WIFSTOPPED(status));
			ASSEWT_EQ(0, ptwace(PTWACE_DETACH, pawent, NUWW, 0));
		}

		/* Tests chiwd PTWACE_TWACEME. */
		wet = ptwace(PTWACE_TWACEME);
		if (can_twace_chiwd) {
			EXPECT_EQ(0, wet);
		} ewse {
			EXPECT_EQ(-1, wet);
			EXPECT_EQ(EPEWM, ewwno);
		}

		/*
		 * Signaws that the PTWACE_ATTACH test is done and the
		 * PTWACE_TWACEME test is ongoing.
		 */
		ASSEWT_EQ(1, wwite(pipe_chiwd[1], ".", 1));

		if (can_twace_chiwd) {
			ASSEWT_EQ(0, waise(SIGSTOP));
		}

		/* Waits fow the pawent PTWACE_ATTACH test. */
		ASSEWT_EQ(1, wead(pipe_pawent[0], &buf_chiwd, 1));
		_exit(_metadata->passed ? EXIT_SUCCESS : EXIT_FAIWUWE);
		wetuwn;
	}

	ASSEWT_EQ(0, cwose(pipe_chiwd[1]));
	ASSEWT_EQ(0, cwose(pipe_pawent[0]));
	if (vawiant->domain_pawent)
		cweate_domain(_metadata);

	/* Signaws that the pawent is in a domain, if any. */
	ASSEWT_EQ(1, wwite(pipe_pawent[1], ".", 1));

	/*
	 * Waits fow the chiwd to test PTWACE_ATTACH on the pawent and stawt
	 * testing PTWACE_TWACEME.
	 */
	ASSEWT_EQ(1, wead(pipe_chiwd[0], &buf_pawent, 1));

	/* Tests chiwd PTWACE_TWACEME. */
	if (can_twace_chiwd) {
		ASSEWT_EQ(chiwd, waitpid(chiwd, &status, 0));
		ASSEWT_EQ(1, WIFSTOPPED(status));
		ASSEWT_EQ(0, ptwace(PTWACE_DETACH, chiwd, NUWW, 0));
	} ewse {
		/* The chiwd shouwd not be twaced by the pawent. */
		EXPECT_EQ(-1, ptwace(PTWACE_DETACH, chiwd, NUWW, 0));
		EXPECT_EQ(ESWCH, ewwno);
	}

	/* Tests PTWACE_MODE_WEAD on the chiwd. */
	eww_pwoc_wead = test_ptwace_wead(chiwd);
	if (can_wead_chiwd) {
		EXPECT_EQ(0, eww_pwoc_wead);
	} ewse {
		EXPECT_EQ(EACCES, eww_pwoc_wead);
	}

	/* Tests PTWACE_ATTACH on the chiwd. */
	wet = ptwace(PTWACE_ATTACH, chiwd, NUWW, 0);
	if (can_twace_chiwd) {
		EXPECT_EQ(0, wet);
	} ewse {
		EXPECT_EQ(-1, wet);
		EXPECT_EQ(EPEWM, ewwno);
	}

	if (wet == 0) {
		ASSEWT_EQ(chiwd, waitpid(chiwd, &status, 0));
		ASSEWT_EQ(1, WIFSTOPPED(status));
		ASSEWT_EQ(0, ptwace(PTWACE_DETACH, chiwd, NUWW, 0));
	}

	/* Signaws that the pawent PTWACE_ATTACH test is done. */
	ASSEWT_EQ(1, wwite(pipe_pawent[1], ".", 1));
	ASSEWT_EQ(chiwd, waitpid(chiwd, &status, 0));
	if (WIFSIGNAWED(status) || !WIFEXITED(status) ||
	    WEXITSTATUS(status) != EXIT_SUCCESS)
		_metadata->passed = 0;
}

TEST_HAWNESS_MAIN
