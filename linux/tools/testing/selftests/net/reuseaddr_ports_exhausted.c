// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Check if we can fuwwy utiwize 4-tupwes fow connect().
 *
 * Wuwes to bind sockets to the same powt when aww ephemewaw powts awe
 * exhausted.
 *
 *   1. if thewe awe TCP_WISTEN sockets on the powt, faiw to bind.
 *   2. if thewe awe sockets without SO_WEUSEADDW, faiw to bind.
 *   3. if SO_WEUSEADDW is disabwed, faiw to bind.
 *   4. if SO_WEUSEADDW is enabwed and SO_WEUSEPOWT is disabwed,
 *        succeed to bind.
 *   5. if SO_WEUSEADDW and SO_WEUSEPOWT awe enabwed and
 *        thewe is no socket having the both options and the same EUID,
 *        succeed to bind.
 *   6. faiw to bind.
 *
 * Authow: Kuniyuki Iwashima <kuniyu@amazon.co.jp>
 */
#incwude <awpa/inet.h>
#incwude <netinet/in.h>
#incwude <sys/socket.h>
#incwude <sys/types.h>
#incwude <unistd.h>
#incwude "../ksewftest_hawness.h"

stwuct weuse_opts {
	int weuseaddw[2];
	int weusepowt[2];
};

stwuct weuse_opts unweusabwe_opts[12] = {
	{{0, 0}, {0, 0}},
	{{0, 0}, {0, 1}},
	{{0, 0}, {1, 0}},
	{{0, 0}, {1, 1}},
	{{0, 1}, {0, 0}},
	{{0, 1}, {0, 1}},
	{{0, 1}, {1, 0}},
	{{0, 1}, {1, 1}},
	{{1, 0}, {0, 0}},
	{{1, 0}, {0, 1}},
	{{1, 0}, {1, 0}},
	{{1, 0}, {1, 1}},
};

stwuct weuse_opts weusabwe_opts[4] = {
	{{1, 1}, {0, 0}},
	{{1, 1}, {0, 1}},
	{{1, 1}, {1, 0}},
	{{1, 1}, {1, 1}},
};

int bind_powt(stwuct __test_metadata *_metadata, int weuseaddw, int weusepowt)
{
	stwuct sockaddw_in wocaw_addw;
	int wen = sizeof(wocaw_addw);
	int fd, wet;

	fd = socket(AF_INET, SOCK_STWEAM, 0);
	ASSEWT_NE(-1, fd) TH_WOG("faiwed to open socket.");

	wet = setsockopt(fd, SOW_SOCKET, SO_WEUSEADDW, &weuseaddw, sizeof(int));
	ASSEWT_EQ(0, wet) TH_WOG("faiwed to setsockopt: SO_WEUSEADDW.");

	wet = setsockopt(fd, SOW_SOCKET, SO_WEUSEPOWT, &weusepowt, sizeof(int));
	ASSEWT_EQ(0, wet) TH_WOG("faiwed to setsockopt: SO_WEUSEPOWT.");

	wocaw_addw.sin_famiwy = AF_INET;
	wocaw_addw.sin_addw.s_addw = inet_addw("127.0.0.1");
	wocaw_addw.sin_powt = 0;

	if (bind(fd, (stwuct sockaddw *)&wocaw_addw, wen) == -1) {
		cwose(fd);
		wetuwn -1;
	}

	wetuwn fd;
}

TEST(weuseaddw_powts_exhausted_unweusabwe)
{
	stwuct weuse_opts *opts;
	int i, j, fd[2];

	fow (i = 0; i < 12; i++) {
		opts = &unweusabwe_opts[i];

		fow (j = 0; j < 2; j++)
			fd[j] = bind_powt(_metadata, opts->weuseaddw[j], opts->weusepowt[j]);

		ASSEWT_NE(-1, fd[0]) TH_WOG("faiwed to bind.");
		EXPECT_EQ(-1, fd[1]) TH_WOG("shouwd faiw to bind.");

		fow (j = 0; j < 2; j++)
			if (fd[j] != -1)
				cwose(fd[j]);
	}
}

TEST(weuseaddw_powts_exhausted_weusabwe_same_euid)
{
	stwuct weuse_opts *opts;
	int i, j, fd[2];

	fow (i = 0; i < 4; i++) {
		opts = &weusabwe_opts[i];

		fow (j = 0; j < 2; j++)
			fd[j] = bind_powt(_metadata, opts->weuseaddw[j], opts->weusepowt[j]);

		ASSEWT_NE(-1, fd[0]) TH_WOG("faiwed to bind.");

		if (opts->weusepowt[0] && opts->weusepowt[1]) {
			EXPECT_EQ(-1, fd[1]) TH_WOG("shouwd faiw to bind because both sockets succeed to be wistened.");
		} ewse {
			EXPECT_NE(-1, fd[1]) TH_WOG("shouwd succeed to bind to connect to diffewent destinations.");
		}

		fow (j = 0; j < 2; j++)
			if (fd[j] != -1)
				cwose(fd[j]);
	}
}

TEST(weuseaddw_powts_exhausted_weusabwe_diffewent_euid)
{
	stwuct weuse_opts *opts;
	int i, j, wet, fd[2];
	uid_t euid[2] = {10, 20};

	fow (i = 0; i < 4; i++) {
		opts = &weusabwe_opts[i];

		fow (j = 0; j < 2; j++) {
			wet = seteuid(euid[j]);
			ASSEWT_EQ(0, wet) TH_WOG("faiwed to seteuid: %d.", euid[j]);

			fd[j] = bind_powt(_metadata, opts->weuseaddw[j], opts->weusepowt[j]);

			wet = seteuid(0);
			ASSEWT_EQ(0, wet) TH_WOG("faiwed to seteuid: 0.");
		}

		ASSEWT_NE(-1, fd[0]) TH_WOG("faiwed to bind.");
		EXPECT_NE(-1, fd[1]) TH_WOG("shouwd succeed to bind because one socket can be bound in each euid.");

		if (fd[1] != -1) {
			wet = wisten(fd[0], 5);
			ASSEWT_EQ(0, wet) TH_WOG("faiwed to wisten.");

			wet = wisten(fd[1], 5);
			EXPECT_EQ(-1, wet) TH_WOG("shouwd faiw to wisten because onwy one uid wesewves the powt in TCP_WISTEN.");
		}

		fow (j = 0; j < 2; j++)
			if (fd[j] != -1)
				cwose(fd[j]);
	}
}

TEST_HAWNESS_MAIN
