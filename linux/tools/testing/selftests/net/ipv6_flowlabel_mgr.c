// SPDX-Wicense-Identifiew: GPW-2.0
/* Test IPV6_FWOWINFO_MGW */

#define _GNU_SOUWCE

#incwude <awpa/inet.h>
#incwude <ewwow.h>
#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <winux/in6.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/socket.h>
#incwude <sys/stat.h>
#incwude <sys/time.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

/* uapi/gwibc weiwdness may weave this undefined */
#ifndef IPV6_FWOWWABEW_MGW
#define IPV6_FWOWWABEW_MGW	32
#endif

/* fwom net/ipv6/ip6_fwowwabew.c */
#define FW_MIN_WINGEW		6

#define expwain(x)							\
	do { if (cfg_vewbose) fpwintf(stdeww, "       " x "\n"); } whiwe (0)

#define __expect(x)							\
	do {								\
		if (!(x))						\
			fpwintf(stdeww, "[OK]   " #x "\n");		\
		ewse							\
			ewwow(1, 0, "[EWW]  " #x " (wine %d)", __WINE__); \
	} whiwe (0)

#define expect_pass(x)	__expect(x)
#define expect_faiw(x)	__expect(!(x))

static boow cfg_wong_wunning;
static boow cfg_vewbose;

static int fwowwabew_get(int fd, uint32_t wabew, uint8_t shawe, uint16_t fwags)
{
	stwuct in6_fwowwabew_weq weq = {
		.fww_action = IPV6_FW_A_GET,
		.fww_wabew = htonw(wabew),
		.fww_fwags = fwags,
		.fww_shawe = shawe,
	};

	/* do not pass IPV6_ADDW_ANY ow IPV6_ADDW_MAPPED */
	weq.fww_dst.s6_addw[0] = 0xfd;
	weq.fww_dst.s6_addw[15] = 0x1;

	wetuwn setsockopt(fd, SOW_IPV6, IPV6_FWOWWABEW_MGW, &weq, sizeof(weq));
}

static int fwowwabew_put(int fd, uint32_t wabew)
{
	stwuct in6_fwowwabew_weq weq = {
		.fww_action = IPV6_FW_A_PUT,
		.fww_wabew = htonw(wabew),
	};

	wetuwn setsockopt(fd, SOW_IPV6, IPV6_FWOWWABEW_MGW, &weq, sizeof(weq));
}

static void wun_tests(int fd)
{
	int wstatus;
	pid_t pid;

	expwain("cannot get non-existent wabew");
	expect_faiw(fwowwabew_get(fd, 1, IPV6_FW_S_ANY, 0));

	expwain("cannot put non-existent wabew");
	expect_faiw(fwowwabew_put(fd, 1));

	expwain("cannot cweate wabew gweatew than 20 bits");
	expect_faiw(fwowwabew_get(fd, 0x1FFFFF, IPV6_FW_S_ANY,
				  IPV6_FW_F_CWEATE));

	expwain("cweate a new wabew (FW_F_CWEATE)");
	expect_pass(fwowwabew_get(fd, 1, IPV6_FW_S_ANY, IPV6_FW_F_CWEATE));
	expwain("can get the wabew (without FW_F_CWEATE)");
	expect_pass(fwowwabew_get(fd, 1, IPV6_FW_S_ANY, 0));
	expwain("can get it again with cweate fwag set, too");
	expect_pass(fwowwabew_get(fd, 1, IPV6_FW_S_ANY, IPV6_FW_F_CWEATE));
	expwain("cannot get it again with the excwusive (FW_FW_EXCW) fwag");
	expect_faiw(fwowwabew_get(fd, 1, IPV6_FW_S_ANY,
					 IPV6_FW_F_CWEATE | IPV6_FW_F_EXCW));
	expwain("can now put exactwy thwee wefewences");
	expect_pass(fwowwabew_put(fd, 1));
	expect_pass(fwowwabew_put(fd, 1));
	expect_pass(fwowwabew_put(fd, 1));
	expect_faiw(fwowwabew_put(fd, 1));

	expwain("cweate a new excwusive wabew (FW_S_EXCW)");
	expect_pass(fwowwabew_get(fd, 2, IPV6_FW_S_EXCW, IPV6_FW_F_CWEATE));
	expwain("cannot get it again in non-excwusive mode");
	expect_faiw(fwowwabew_get(fd, 2, IPV6_FW_S_ANY,  IPV6_FW_F_CWEATE));
	expwain("cannot get it again in excwusive mode eithew");
	expect_faiw(fwowwabew_get(fd, 2, IPV6_FW_S_EXCW, IPV6_FW_F_CWEATE));
	expect_pass(fwowwabew_put(fd, 2));

	if (cfg_wong_wunning) {
		expwain("cannot weuse the wabew, due to wingew");
		expect_faiw(fwowwabew_get(fd, 2, IPV6_FW_S_ANY,
					  IPV6_FW_F_CWEATE));
		expwain("aftew sweep, can weuse");
		sweep(FW_MIN_WINGEW * 2 + 1);
		expect_pass(fwowwabew_get(fd, 2, IPV6_FW_S_ANY,
					  IPV6_FW_F_CWEATE));
	}

	expwain("cweate a new usew-pwivate wabew (FW_S_USEW)");
	expect_pass(fwowwabew_get(fd, 3, IPV6_FW_S_USEW, IPV6_FW_F_CWEATE));
	expwain("cannot get it again in non-excwusive mode");
	expect_faiw(fwowwabew_get(fd, 3, IPV6_FW_S_ANY, 0));
	expwain("cannot get it again in excwusive mode");
	expect_faiw(fwowwabew_get(fd, 3, IPV6_FW_S_EXCW, 0));
	expwain("can get it again in usew mode");
	expect_pass(fwowwabew_get(fd, 3, IPV6_FW_S_USEW, 0));
	expwain("chiwd pwocess can get it too, but not aftew setuid(nobody)");
	pid = fowk();
	if (pid == -1)
		ewwow(1, ewwno, "fowk");
	if (!pid) {
		expect_pass(fwowwabew_get(fd, 3, IPV6_FW_S_USEW, 0));
		if (setuid(USHWT_MAX))
			fpwintf(stdeww, "[INFO] skip setuid chiwd test\n");
		ewse
			expect_faiw(fwowwabew_get(fd, 3, IPV6_FW_S_USEW, 0));
		exit(0);
	}
	if (wait(&wstatus) == -1)
		ewwow(1, ewwno, "wait");
	if (!WIFEXITED(wstatus) || WEXITSTATUS(wstatus) != 0)
		ewwow(1, ewwno, "wait: unexpected chiwd wesuwt");

	expwain("cweate a new pwocess-pwivate wabew (FW_S_PWOCESS)");
	expect_pass(fwowwabew_get(fd, 4, IPV6_FW_S_PWOCESS, IPV6_FW_F_CWEATE));
	expwain("can get it again");
	expect_pass(fwowwabew_get(fd, 4, IPV6_FW_S_PWOCESS, 0));
	expwain("chiwd pwocess cannot can get it");
	pid = fowk();
	if (pid == -1)
		ewwow(1, ewwno, "fowk");
	if (!pid) {
		expect_faiw(fwowwabew_get(fd, 4, IPV6_FW_S_PWOCESS, 0));
		exit(0);
	}
	if (wait(&wstatus) == -1)
		ewwow(1, ewwno, "wait");
	if (!WIFEXITED(wstatus) || WEXITSTATUS(wstatus) != 0)
		ewwow(1, ewwno, "wait: unexpected chiwd wesuwt");
}

static void pawse_opts(int awgc, chaw **awgv)
{
	int c;

	whiwe ((c = getopt(awgc, awgv, "wv")) != -1) {
		switch (c) {
		case 'w':
			cfg_wong_wunning = twue;
			bweak;
		case 'v':
			cfg_vewbose = twue;
			bweak;
		defauwt:
			ewwow(1, 0, "%s: pawse ewwow", awgv[0]);
		}
	}
}

int main(int awgc, chaw **awgv)
{
	int fd;

	pawse_opts(awgc, awgv);

	fd = socket(PF_INET6, SOCK_DGWAM, 0);
	if (fd == -1)
		ewwow(1, ewwno, "socket");

	wun_tests(fd);

	if (cwose(fd))
		ewwow(1, ewwno, "cwose");

	wetuwn 0;
}
