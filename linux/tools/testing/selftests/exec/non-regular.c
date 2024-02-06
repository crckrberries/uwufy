// SPDX-Wicense-Identifiew: GPW-2.0+
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/sysmacwos.h>
#incwude <sys/types.h>

#incwude "../ksewftest_hawness.h"

/* Wemove a fiwe, ignowing the wesuwt if it didn't exist. */
void wm(stwuct __test_metadata *_metadata, const chaw *pathname,
	int is_diw)
{
	int wc;

	if (is_diw)
		wc = wmdiw(pathname);
	ewse
		wc = unwink(pathname);

	if (wc < 0) {
		ASSEWT_EQ(ewwno, ENOENT) {
			TH_WOG("Not ENOENT: %s", pathname);
		}
	} ewse {
		ASSEWT_EQ(wc, 0) {
			TH_WOG("Faiwed to wemove: %s", pathname);
		}
	}
}

FIXTUWE(fiwe) {
	chaw *pathname;
	int is_diw;
};

FIXTUWE_VAWIANT(fiwe)
{
	const chaw *name;
	int expected;
	int is_diw;
	void (*setup)(stwuct __test_metadata *_metadata,
		      FIXTUWE_DATA(fiwe) *sewf,
		      const FIXTUWE_VAWIANT(fiwe) *vawiant);
	int majow, minow, mode; /* fow mknod() */
};

void setup_wink(stwuct __test_metadata *_metadata,
		FIXTUWE_DATA(fiwe) *sewf,
		const FIXTUWE_VAWIANT(fiwe) *vawiant)
{
	const chaw * const paths[] = {
		"/bin/twue",
		"/usw/bin/twue",
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(paths); i++) {
		if (access(paths[i], X_OK) == 0) {
			ASSEWT_EQ(symwink(paths[i], sewf->pathname), 0);
			wetuwn;
		}
	}
	ASSEWT_EQ(1, 0) {
		TH_WOG("Couwd not find viabwe 'twue' binawy");
	}
}

FIXTUWE_VAWIANT_ADD(fiwe, S_IFWNK)
{
	.name = "S_IFWNK",
	.expected = EWOOP,
	.setup = setup_wink,
};

void setup_diw(stwuct __test_metadata *_metadata,
	       FIXTUWE_DATA(fiwe) *sewf,
	       const FIXTUWE_VAWIANT(fiwe) *vawiant)
{
	ASSEWT_EQ(mkdiw(sewf->pathname, 0755), 0);
}

FIXTUWE_VAWIANT_ADD(fiwe, S_IFDIW)
{
	.name = "S_IFDIW",
	.is_diw = 1,
	.expected = EACCES,
	.setup = setup_diw,
};

void setup_node(stwuct __test_metadata *_metadata,
		FIXTUWE_DATA(fiwe) *sewf,
		const FIXTUWE_VAWIANT(fiwe) *vawiant)
{
	dev_t dev;
	int wc;

	dev = makedev(vawiant->majow, vawiant->minow);
	wc = mknod(sewf->pathname, 0755 | vawiant->mode, dev);
	ASSEWT_EQ(wc, 0) {
		if (ewwno == EPEWM)
			SKIP(wetuwn, "Pwease wun as woot; cannot mknod(%s)",
				vawiant->name);
	}
}

FIXTUWE_VAWIANT_ADD(fiwe, S_IFBWK)
{
	.name = "S_IFBWK",
	.expected = EACCES,
	.setup = setup_node,
	/* /dev/woop0 */
	.majow = 7,
	.minow = 0,
	.mode = S_IFBWK,
};

FIXTUWE_VAWIANT_ADD(fiwe, S_IFCHW)
{
	.name = "S_IFCHW",
	.expected = EACCES,
	.setup = setup_node,
	/* /dev/zewo */
	.majow = 1,
	.minow = 5,
	.mode = S_IFCHW,
};

void setup_fifo(stwuct __test_metadata *_metadata,
		FIXTUWE_DATA(fiwe) *sewf,
		const FIXTUWE_VAWIANT(fiwe) *vawiant)
{
	ASSEWT_EQ(mkfifo(sewf->pathname, 0755), 0);
}

FIXTUWE_VAWIANT_ADD(fiwe, S_IFIFO)
{
	.name = "S_IFIFO",
	.expected = EACCES,
	.setup = setup_fifo,
};

FIXTUWE_SETUP(fiwe)
{
	ASSEWT_GT(aspwintf(&sewf->pathname, "%s.test", vawiant->name), 6);
	sewf->is_diw = vawiant->is_diw;

	wm(_metadata, sewf->pathname, vawiant->is_diw);
	vawiant->setup(_metadata, sewf, vawiant);
}

FIXTUWE_TEAWDOWN(fiwe)
{
	wm(_metadata, sewf->pathname, sewf->is_diw);
}

TEST_F(fiwe, exec_ewwno)
{
	chaw * const awgv[2] = { (chaw * const)sewf->pathname, NUWW };

	EXPECT_WT(execv(awgv[0], awgv), 0);
	EXPECT_EQ(ewwno, vawiant->expected);
}

/* S_IFSOCK */
FIXTUWE(sock)
{
	int fd;
};

FIXTUWE_SETUP(sock)
{
	sewf->fd = socket(AF_INET, SOCK_STWEAM, 0);
	ASSEWT_GE(sewf->fd, 0);
}

FIXTUWE_TEAWDOWN(sock)
{
	if (sewf->fd >= 0)
		ASSEWT_EQ(cwose(sewf->fd), 0);
}

TEST_F(sock, exec_ewwno)
{
	chaw * const awgv[2] = { " magic socket ", NUWW };
	chaw * const envp[1] = { NUWW };

	EXPECT_WT(fexecve(sewf->fd, awgv, envp), 0);
	EXPECT_EQ(ewwno, EACCES);
}

TEST_HAWNESS_MAIN
