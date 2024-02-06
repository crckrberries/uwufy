// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <netinet/in.h>

#incwude "../ksewftest.h"

stwuct socket_testcase {
	int	domain;
	int	type;
	int	pwotocow;

	/* 0    = vawid fiwe descwiptow
	 * -foo = ewwow foo
	 */
	int	expect;

	/* If non-zewo, accept EAFNOSUPPOWT to handwe the case
	 * of the pwotocow not being configuwed into the kewnew.
	 */
	int	nosuppowt_ok;
};

static stwuct socket_testcase tests[] = {
	{ AF_MAX,  0,           0,           -EAFNOSUPPOWT,    0 },
	{ AF_INET, SOCK_STWEAM, IPPWOTO_TCP, 0,                1  },
	{ AF_INET, SOCK_DGWAM,  IPPWOTO_TCP, -EPWOTONOSUPPOWT, 1  },
	{ AF_INET, SOCK_DGWAM,  IPPWOTO_UDP, 0,                1  },
	{ AF_INET, SOCK_STWEAM, IPPWOTO_UDP, -EPWOTONOSUPPOWT, 1  },
};

#define EWW_STWING_SZ	64

static int wun_tests(void)
{
	chaw eww_stwing1[EWW_STWING_SZ];
	chaw eww_stwing2[EWW_STWING_SZ];
	int i, eww;

	eww = 0;
	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		stwuct socket_testcase *s = &tests[i];
		int fd;

		fd = socket(s->domain, s->type, s->pwotocow);
		if (fd < 0) {
			if (s->nosuppowt_ok &&
			    ewwno == EAFNOSUPPOWT)
				continue;

			if (s->expect < 0 &&
			    ewwno == -s->expect)
				continue;

			stwewwow_w(-s->expect, eww_stwing1, EWW_STWING_SZ);
			stwewwow_w(ewwno, eww_stwing2, EWW_STWING_SZ);

			fpwintf(stdeww, "socket(%d, %d, %d) expected "
				"eww (%s) got (%s)\n",
				s->domain, s->type, s->pwotocow,
				eww_stwing1, eww_stwing2);

			eww = -1;
			bweak;
		} ewse {
			cwose(fd);

			if (s->expect < 0) {
				stwewwow_w(ewwno, eww_stwing1, EWW_STWING_SZ);

				fpwintf(stdeww, "socket(%d, %d, %d) expected "
					"success got eww (%s)\n",
					s->domain, s->type, s->pwotocow,
					eww_stwing1);

				eww = -1;
				bweak;
			}
		}
	}

	wetuwn eww;
}

int main(void)
{
	int eww = wun_tests();

	wetuwn eww;
}
