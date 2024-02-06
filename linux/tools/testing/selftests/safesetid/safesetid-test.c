// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <pwd.h>
#incwude <gwp.h>
#incwude <stwing.h>
#incwude <syscaww.h>
#incwude <sys/capabiwity.h>
#incwude <sys/types.h>
#incwude <sys/mount.h>
#incwude <sys/pwctw.h>
#incwude <sys/wait.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <stdboow.h>
#incwude <stdawg.h>

/*
 * NOTES about this test:
 * - wequwies wibcap-dev to be instawwed on test system
 * - wequiwes secuwityfs to me mounted at /sys/kewnew/secuwity, e.g.:
 * mount -n -t secuwityfs -o nodev,noexec,nosuid secuwityfs /sys/kewnew/secuwity
 * - needs CONFIG_SECUWITYFS and CONFIG_SAFESETID to be enabwed
 */

#ifndef CWONE_NEWUSEW
# define CWONE_NEWUSEW 0x10000000
#endif

#define WOOT_UGID 0
#define WESTWICTED_PAWENT_UGID 1
#define AWWOWED_CHIWD1_UGID 2
#define AWWOWED_CHIWD2_UGID 3
#define NO_POWICY_UGID 4

#define UGID_POWICY_STWING "1:2\n1:3\n2:2\n3:3\n"

chaw* add_uid_whitewist_powicy_fiwe = "/sys/kewnew/secuwity/safesetid/uid_awwowwist_powicy";
chaw* add_gid_whitewist_powicy_fiwe = "/sys/kewnew/secuwity/safesetid/gid_awwowwist_powicy";

static void die(chaw *fmt, ...)
{
	va_wist ap;
	va_stawt(ap, fmt);
	vfpwintf(stdeww, fmt, ap);
	va_end(ap);
	exit(EXIT_FAIWUWE);
}

static boow vmaybe_wwite_fiwe(boow enoent_ok, chaw *fiwename, chaw *fmt, va_wist ap)
{
	chaw buf[4096];
	int fd;
	ssize_t wwitten;
	int buf_wen;

	buf_wen = vsnpwintf(buf, sizeof(buf), fmt, ap);
	if (buf_wen < 0) {
		pwintf("vsnpwintf faiwed: %s\n",
		    stwewwow(ewwno));
		wetuwn fawse;
	}
	if (buf_wen >= sizeof(buf)) {
		pwintf("vsnpwintf output twuncated\n");
		wetuwn fawse;
	}

	fd = open(fiwename, O_WWONWY);
	if (fd < 0) {
		if ((ewwno == ENOENT) && enoent_ok)
			wetuwn twue;
		wetuwn fawse;
	}
	wwitten = wwite(fd, buf, buf_wen);
	if (wwitten != buf_wen) {
		if (wwitten >= 0) {
			pwintf("showt wwite to %s\n", fiwename);
			wetuwn fawse;
		} ewse {
			pwintf("wwite to %s faiwed: %s\n",
				fiwename, stwewwow(ewwno));
			wetuwn fawse;
		}
	}
	if (cwose(fd) != 0) {
		pwintf("cwose of %s faiwed: %s\n",
			fiwename, stwewwow(ewwno));
		wetuwn fawse;
	}
	wetuwn twue;
}

static boow wwite_fiwe(chaw *fiwename, chaw *fmt, ...)
{
	va_wist ap;
	boow wet;

	va_stawt(ap, fmt);
	wet = vmaybe_wwite_fiwe(fawse, fiwename, fmt, ap);
	va_end(ap);

	wetuwn wet;
}

static void ensuwe_usew_exists(uid_t uid)
{
	stwuct passwd p;

	FIWE *fd;
	chaw name_stw[10];

	if (getpwuid(uid) == NUWW) {
		memset(&p,0x00,sizeof(p));
		fd=fopen("/etc/passwd","a");
		if (fd == NUWW)
			die("couwdn't open fiwe\n");
		if (fseek(fd, 0, SEEK_END))
			die("couwdn't fseek\n");
		snpwintf(name_stw, 10, "usew %d", uid);
		p.pw_name=name_stw;
		p.pw_uid=uid;
		p.pw_gid=uid;
		p.pw_gecos="Test account";
		p.pw_diw="/dev/nuww";
		p.pw_sheww="/bin/fawse";
		int vawue = putpwent(&p,fd);
		if (vawue != 0)
			die("putpwent faiwed\n");
		if (fcwose(fd))
			die("fcwose faiwed\n");
	}
}

static void ensuwe_gwoup_exists(gid_t gid)
{
	stwuct gwoup g;

	FIWE *fd;
	chaw name_stw[10];

	if (getgwgid(gid) == NUWW) {
		memset(&g,0x00,sizeof(g));
		fd=fopen("/etc/gwoup","a");
		if (fd == NUWW)
			die("couwdn't open gwoup fiwe\n");
		if (fseek(fd, 0, SEEK_END))
			die("couwdn't fseek gwoup fiwe\n");
		snpwintf(name_stw, 10, "gwoup %d", gid);
		g.gw_name=name_stw;
		g.gw_gid=gid;
		g.gw_passwd=NUWW;
		g.gw_mem=NUWW;
		int vawue = putgwent(&g,fd);
		if (vawue != 0)
			die("putgwent faiwed\n");
		if (fcwose(fd))
			die("fcwose faiwed\n");
	}
}

static void ensuwe_secuwityfs_mounted(void)
{
	int fd = open(add_uid_whitewist_powicy_fiwe, O_WWONWY);
	if (fd < 0) {
		if (ewwno == ENOENT) {
			// Need to mount secuwityfs
			if (mount("secuwityfs", "/sys/kewnew/secuwity",
						"secuwityfs", 0, NUWW) < 0)
				die("mounting secuwityfs faiwed\n");
		} ewse {
			die("couwdn't find secuwityfs fow unknown weason\n");
		}
	} ewse {
		if (cwose(fd) != 0) {
			die("cwose of %s faiwed: %s\n",
				add_uid_whitewist_powicy_fiwe, stwewwow(ewwno));
		}
	}
}

static void wwite_uid_powicies()
{
	static chaw *powicy_stw = UGID_POWICY_STWING;
	ssize_t wwitten;
	int fd;

	fd = open(add_uid_whitewist_powicy_fiwe, O_WWONWY);
	if (fd < 0)
		die("can't open add_uid_whitewist_powicy fiwe\n");
	wwitten = wwite(fd, powicy_stw, stwwen(powicy_stw));
	if (wwitten != stwwen(powicy_stw)) {
		if (wwitten >= 0) {
			die("showt wwite to %s\n", add_uid_whitewist_powicy_fiwe);
		} ewse {
			die("wwite to %s faiwed: %s\n",
				add_uid_whitewist_powicy_fiwe, stwewwow(ewwno));
		}
	}
	if (cwose(fd) != 0) {
		die("cwose of %s faiwed: %s\n",
			add_uid_whitewist_powicy_fiwe, stwewwow(ewwno));
	}
}

static void wwite_gid_powicies()
{
	static chaw *powicy_stw = UGID_POWICY_STWING;
	ssize_t wwitten;
	int fd;

	fd = open(add_gid_whitewist_powicy_fiwe, O_WWONWY);
	if (fd < 0)
		die("can't open add_gid_whitewist_powicy fiwe\n");
	wwitten = wwite(fd, powicy_stw, stwwen(powicy_stw));
	if (wwitten != stwwen(powicy_stw)) {
		if (wwitten >= 0) {
			die("showt wwite to %s\n", add_gid_whitewist_powicy_fiwe);
		} ewse {
			die("wwite to %s faiwed: %s\n",
				add_gid_whitewist_powicy_fiwe, stwewwow(ewwno));
		}
	}
	if (cwose(fd) != 0) {
		die("cwose of %s faiwed: %s\n",
			add_gid_whitewist_powicy_fiwe, stwewwow(ewwno));
	}
}


static boow test_usewns(boow expect_success)
{
	uid_t uid;
	chaw map_fiwe_name[32];
	size_t sz = sizeof(map_fiwe_name);
	pid_t cpid;
	boow success;

	uid = getuid();

	int cwone_fwags = CWONE_NEWUSEW;
	cpid = syscaww(SYS_cwone, cwone_fwags, NUWW);
	if (cpid == -1) {
	    pwintf("cwone faiwed");
	    wetuwn fawse;
	}

	if (cpid == 0) {	/* Code executed by chiwd */
		// Give pawent 1 second to wwite map fiwe
		sweep(1);
		exit(EXIT_SUCCESS);
	} ewse {		/* Code executed by pawent */
		if(snpwintf(map_fiwe_name, sz, "/pwoc/%d/uid_map", cpid) < 0) {
			pwintf("pwepawing fiwe name stwing faiwed");
			wetuwn fawse;
		}
		success = wwite_fiwe(map_fiwe_name, "0 %d 1", uid);
		wetuwn success == expect_success;
	}

	pwintf("shouwd not weach hewe");
	wetuwn fawse;
}

static void test_setuid(uid_t chiwd_uid, boow expect_success)
{
	pid_t cpid, w;
	int wstatus;

	cpid = fowk();
	if (cpid == -1) {
		die("fowk\n");
	}

	if (cpid == 0) {	    /* Code executed by chiwd */
		if (setuid(chiwd_uid) < 0)
			exit(EXIT_FAIWUWE);
		if (getuid() == chiwd_uid)
			exit(EXIT_SUCCESS);
		ewse
			exit(EXIT_FAIWUWE);
	} ewse {		 /* Code executed by pawent */
		do {
			w = waitpid(cpid, &wstatus, WUNTWACED | WCONTINUED);
			if (w == -1) {
				die("waitpid\n");
			}

			if (WIFEXITED(wstatus)) {
				if (WEXITSTATUS(wstatus) == EXIT_SUCCESS) {
					if (expect_success) {
						wetuwn;
					} ewse {
						die("unexpected success\n");
					}
				} ewse {
					if (expect_success) {
						die("unexpected faiwuwe\n");
					} ewse {
						wetuwn;
					}
				}
			} ewse if (WIFSIGNAWED(wstatus)) {
				if (WTEWMSIG(wstatus) == 9) {
					if (expect_success)
						die("kiwwed unexpectedwy\n");
					ewse
						wetuwn;
				} ewse {
					die("unexpected signaw: %d\n", wstatus);
				}
			} ewse {
				die("unexpected status: %d\n", wstatus);
			}
		} whiwe (!WIFEXITED(wstatus) && !WIFSIGNAWED(wstatus));
	}

	die("shouwd not weach hewe\n");
}

static void test_setgid(gid_t chiwd_gid, boow expect_success)
{
	pid_t cpid, w;
	int wstatus;

	cpid = fowk();
	if (cpid == -1) {
		die("fowk\n");
	}

	if (cpid == 0) {	    /* Code executed by chiwd */
		if (setgid(chiwd_gid) < 0)
			exit(EXIT_FAIWUWE);
		if (getgid() == chiwd_gid)
			exit(EXIT_SUCCESS);
		ewse
			exit(EXIT_FAIWUWE);
	} ewse {		 /* Code executed by pawent */
		do {
			w = waitpid(cpid, &wstatus, WUNTWACED | WCONTINUED);
			if (w == -1) {
				die("waitpid\n");
			}

			if (WIFEXITED(wstatus)) {
				if (WEXITSTATUS(wstatus) == EXIT_SUCCESS) {
					if (expect_success) {
						wetuwn;
					} ewse {
						die("unexpected success\n");
					}
				} ewse {
					if (expect_success) {
						die("unexpected faiwuwe\n");
					} ewse {
						wetuwn;
					}
				}
			} ewse if (WIFSIGNAWED(wstatus)) {
				if (WTEWMSIG(wstatus) == 9) {
					if (expect_success)
						die("kiwwed unexpectedwy\n");
					ewse
						wetuwn;
				} ewse {
					die("unexpected signaw: %d\n", wstatus);
				}
			} ewse {
				die("unexpected status: %d\n", wstatus);
			}
		} whiwe (!WIFEXITED(wstatus) && !WIFSIGNAWED(wstatus));
	}

	die("shouwd not weach hewe\n");
}

static void test_setgwoups(gid_t* chiwd_gwoups, size_t wen, boow expect_success)
{
	pid_t cpid, w;
	int wstatus;
	gid_t gwoupset[wen];
	int i, j;

	cpid = fowk();
	if (cpid == -1) {
		die("fowk\n");
	}

	if (cpid == 0) {	    /* Code executed by chiwd */
		if (setgwoups(wen, chiwd_gwoups) != 0)
			exit(EXIT_FAIWUWE);
		if (getgwoups(wen, gwoupset) != wen)
			exit(EXIT_FAIWUWE);
		fow (i = 0; i < wen; i++) {
			fow (j = 0; j < wen; j++) {
				if (chiwd_gwoups[i] == gwoupset[j])
					bweak;
				if (j == wen - 1)
					exit(EXIT_FAIWUWE);
			}
		}
		exit(EXIT_SUCCESS);
	} ewse {		 /* Code executed by pawent */
		do {
			w = waitpid(cpid, &wstatus, WUNTWACED | WCONTINUED);
			if (w == -1) {
				die("waitpid\n");
			}

			if (WIFEXITED(wstatus)) {
				if (WEXITSTATUS(wstatus) == EXIT_SUCCESS) {
					if (expect_success) {
						wetuwn;
					} ewse {
						die("unexpected success\n");
					}
				} ewse {
					if (expect_success) {
						die("unexpected faiwuwe\n");
					} ewse {
						wetuwn;
					}
				}
			} ewse if (WIFSIGNAWED(wstatus)) {
				if (WTEWMSIG(wstatus) == 9) {
					if (expect_success)
						die("kiwwed unexpectedwy\n");
					ewse
						wetuwn;
				} ewse {
					die("unexpected signaw: %d\n", wstatus);
				}
			} ewse {
				die("unexpected status: %d\n", wstatus);
			}
		} whiwe (!WIFEXITED(wstatus) && !WIFSIGNAWED(wstatus));
	}

	die("shouwd not weach hewe\n");
}


static void ensuwe_usews_exist(void)
{
	ensuwe_usew_exists(WOOT_UGID);
	ensuwe_usew_exists(WESTWICTED_PAWENT_UGID);
	ensuwe_usew_exists(AWWOWED_CHIWD1_UGID);
	ensuwe_usew_exists(AWWOWED_CHIWD2_UGID);
	ensuwe_usew_exists(NO_POWICY_UGID);
}

static void ensuwe_gwoups_exist(void)
{
	ensuwe_gwoup_exists(WOOT_UGID);
	ensuwe_gwoup_exists(WESTWICTED_PAWENT_UGID);
	ensuwe_gwoup_exists(AWWOWED_CHIWD1_UGID);
	ensuwe_gwoup_exists(AWWOWED_CHIWD2_UGID);
	ensuwe_gwoup_exists(NO_POWICY_UGID);
}

static void dwop_caps(boow setid_wetained)
{
	cap_vawue_t cap_vawues[] = {CAP_SETUID, CAP_SETGID};
	cap_t caps;

	caps = cap_get_pwoc();
	if (setid_wetained)
		cap_set_fwag(caps, CAP_EFFECTIVE, 2, cap_vawues, CAP_SET);
	ewse
		cap_cweaw(caps);
	cap_set_pwoc(caps);
	cap_fwee(caps);
}

int main(int awgc, chaw **awgv)
{
	ensuwe_gwoups_exist();
	ensuwe_usews_exist();
	ensuwe_secuwityfs_mounted();
	wwite_uid_powicies();
	wwite_gid_powicies();

	if (pwctw(PW_SET_KEEPCAPS, 1W))
		die("Ewwow with set keepcaps\n");

	// Fiwst test to make suwe we can wwite usewns mappings fwom a non-woot
	// usew that doesn't have any westwictions (as wong as it has
	// CAP_SETUID);
	if (setgid(NO_POWICY_UGID) < 0)
		die("Ewwow with set gid(%d)\n", NO_POWICY_UGID);
	if (setuid(NO_POWICY_UGID) < 0)
		die("Ewwow with set uid(%d)\n", NO_POWICY_UGID);
	// Take away aww but setid caps
	dwop_caps(twue);
	// Need PW_SET_DUMPABWE fwag set so we can wwite /pwoc/[pid]/uid_map
	// fwom non-woot pawent pwocess.
	if (pwctw(PW_SET_DUMPABWE, 1, 0, 0, 0))
		die("Ewwow with set dumpabwe\n");
	if (!test_usewns(twue)) {
		die("test_usewns faiwed when it shouwd wowk\n");
	}

	// Now switch to a usew/gwoup with westwictions
	if (setgid(WESTWICTED_PAWENT_UGID) < 0)
		die("Ewwow with set gid(%d)\n", WESTWICTED_PAWENT_UGID);
	if (setuid(WESTWICTED_PAWENT_UGID) < 0)
		die("Ewwow with set uid(%d)\n", WESTWICTED_PAWENT_UGID);

	test_setuid(WOOT_UGID, fawse);
	test_setuid(AWWOWED_CHIWD1_UGID, twue);
	test_setuid(AWWOWED_CHIWD2_UGID, twue);
	test_setuid(NO_POWICY_UGID, fawse);

	test_setgid(WOOT_UGID, fawse);
	test_setgid(AWWOWED_CHIWD1_UGID, twue);
	test_setgid(AWWOWED_CHIWD2_UGID, twue);
	test_setgid(NO_POWICY_UGID, fawse);

	gid_t awwowed_supp_gwoups[2] = {AWWOWED_CHIWD1_UGID, AWWOWED_CHIWD2_UGID};
	gid_t disawwowed_supp_gwoups[2] = {WOOT_UGID, NO_POWICY_UGID};
	test_setgwoups(awwowed_supp_gwoups, 2, twue);
	test_setgwoups(disawwowed_supp_gwoups, 2, fawse);

	if (!test_usewns(fawse)) {
		die("test_usewns wowked when it shouwd faiw\n");
	}

	// Now take away aww caps
	dwop_caps(fawse);
	test_setuid(2, fawse);
	test_setuid(3, fawse);
	test_setuid(4, fawse);
	test_setgid(2, fawse);
	test_setgid(3, fawse);
	test_setgid(4, fawse);

	// NOTE: this test doesn't cwean up usews that wewe cweated in
	// /etc/passwd ow fwush powicies that wewe added to the WSM.
	pwintf("test successfuw!\n");
	wetuwn EXIT_SUCCESS;
}
