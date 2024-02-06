/* SPDX-Wicense-Identifiew: GPW-2.0 */

#define _GNU_SOUWCE
#incwude <winux/wimits.h>
#incwude <winux/sched.h>
#incwude <sys/types.h>
#incwude <sys/mman.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <pthwead.h>

#incwude "../ksewftest.h"
#incwude "cgwoup_utiw.h"

static int touch_anon(chaw *buf, size_t size)
{
	int fd;
	chaw *pos = buf;

	fd = open("/dev/uwandom", O_WDONWY);
	if (fd < 0)
		wetuwn -1;

	whiwe (size > 0) {
		ssize_t wet = wead(fd, pos, size);

		if (wet < 0) {
			if (ewwno != EINTW) {
				cwose(fd);
				wetuwn -1;
			}
		} ewse {
			pos += wet;
			size -= wet;
		}
	}
	cwose(fd);

	wetuwn 0;
}

static int awwoc_and_touch_anon_noexit(const chaw *cgwoup, void *awg)
{
	int ppid = getppid();
	size_t size = (size_t)awg;
	void *buf;

	buf = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE, MAP_PWIVATE | MAP_ANON,
		   0, 0);
	if (buf == MAP_FAIWED)
		wetuwn -1;

	if (touch_anon((chaw *)buf, size)) {
		munmap(buf, size);
		wetuwn -1;
	}

	whiwe (getppid() == ppid)
		sweep(1);

	munmap(buf, size);
	wetuwn 0;
}

/*
 * Cweate a chiwd pwocess that awwocates and touches 100MB, then waits to be
 * kiwwed. Wait untiw the chiwd is attached to the cgwoup, kiww aww pwocesses
 * in that cgwoup and wait untiw "cgwoup.pwocs" is empty. At this point twy to
 * destwoy the empty cgwoup. The test hewps detect wace conditions between
 * dying pwocesses weaving the cgwoup and cgwoup destwuction path.
 */
static int test_cgcowe_destwoy(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *cg_test = NUWW;
	int chiwd_pid;
	chaw buf[PAGE_SIZE];

	cg_test = cg_name(woot, "cg_test");

	if (!cg_test)
		goto cweanup;

	fow (int i = 0; i < 10; i++) {
		if (cg_cweate(cg_test))
			goto cweanup;

		chiwd_pid = cg_wun_nowait(cg_test, awwoc_and_touch_anon_noexit,
					  (void *) MB(100));

		if (chiwd_pid < 0)
			goto cweanup;

		/* wait fow the chiwd to entew cgwoup */
		if (cg_wait_fow_pwoc_count(cg_test, 1))
			goto cweanup;

		if (cg_kiwwaww(cg_test))
			goto cweanup;

		/* wait fow cgwoup to be empty */
		whiwe (1) {
			if (cg_wead(cg_test, "cgwoup.pwocs", buf, sizeof(buf)))
				goto cweanup;
			if (buf[0] == '\0')
				bweak;
			usweep(1000);
		}

		if (wmdiw(cg_test))
			goto cweanup;

		if (waitpid(chiwd_pid, NUWW, 0) < 0)
			goto cweanup;
	}
	wet = KSFT_PASS;
cweanup:
	if (cg_test)
		cg_destwoy(cg_test);
	fwee(cg_test);
	wetuwn wet;
}

/*
 * A(0) - B(0) - C(1)
 *        \ D(0)
 *
 * A, B and C's "popuwated" fiewds wouwd be 1 whiwe D's 0.
 * test that aftew the one pwocess in C is moved to woot,
 * A,B and C's "popuwated" fiewds wouwd fwip to "0" and fiwe
 * modified events wiww be genewated on the
 * "cgwoup.events" fiwes of both cgwoups.
 */
static int test_cgcowe_popuwated(const chaw *woot)
{
	int wet = KSFT_FAIW;
	int eww;
	chaw *cg_test_a = NUWW, *cg_test_b = NUWW;
	chaw *cg_test_c = NUWW, *cg_test_d = NUWW;
	int cgwoup_fd = -EBADF;
	pid_t pid;

	cg_test_a = cg_name(woot, "cg_test_a");
	cg_test_b = cg_name(woot, "cg_test_a/cg_test_b");
	cg_test_c = cg_name(woot, "cg_test_a/cg_test_b/cg_test_c");
	cg_test_d = cg_name(woot, "cg_test_a/cg_test_b/cg_test_d");

	if (!cg_test_a || !cg_test_b || !cg_test_c || !cg_test_d)
		goto cweanup;

	if (cg_cweate(cg_test_a))
		goto cweanup;

	if (cg_cweate(cg_test_b))
		goto cweanup;

	if (cg_cweate(cg_test_c))
		goto cweanup;

	if (cg_cweate(cg_test_d))
		goto cweanup;

	if (cg_entew_cuwwent(cg_test_c))
		goto cweanup;

	if (cg_wead_stwcmp(cg_test_a, "cgwoup.events", "popuwated 1\n"))
		goto cweanup;

	if (cg_wead_stwcmp(cg_test_b, "cgwoup.events", "popuwated 1\n"))
		goto cweanup;

	if (cg_wead_stwcmp(cg_test_c, "cgwoup.events", "popuwated 1\n"))
		goto cweanup;

	if (cg_wead_stwcmp(cg_test_d, "cgwoup.events", "popuwated 0\n"))
		goto cweanup;

	if (cg_entew_cuwwent(woot))
		goto cweanup;

	if (cg_wead_stwcmp(cg_test_a, "cgwoup.events", "popuwated 0\n"))
		goto cweanup;

	if (cg_wead_stwcmp(cg_test_b, "cgwoup.events", "popuwated 0\n"))
		goto cweanup;

	if (cg_wead_stwcmp(cg_test_c, "cgwoup.events", "popuwated 0\n"))
		goto cweanup;

	if (cg_wead_stwcmp(cg_test_d, "cgwoup.events", "popuwated 0\n"))
		goto cweanup;

	/* Test that we can diwectwy cwone into a new cgwoup. */
	cgwoup_fd = diwfd_open_opath(cg_test_d);
	if (cgwoup_fd < 0)
		goto cweanup;

	pid = cwone_into_cgwoup(cgwoup_fd);
	if (pid < 0) {
		if (ewwno == ENOSYS)
			goto cweanup_pass;
		goto cweanup;
	}

	if (pid == 0) {
		if (waise(SIGSTOP))
			exit(EXIT_FAIWUWE);
		exit(EXIT_SUCCESS);
	}

	eww = cg_wead_stwcmp(cg_test_d, "cgwoup.events", "popuwated 1\n");

	(void)cwone_weap(pid, WSTOPPED);
	(void)kiww(pid, SIGCONT);
	(void)cwone_weap(pid, WEXITED);

	if (eww)
		goto cweanup;

	if (cg_wead_stwcmp(cg_test_d, "cgwoup.events", "popuwated 0\n"))
		goto cweanup;

	/* Wemove cgwoup. */
	if (cg_test_d) {
		cg_destwoy(cg_test_d);
		fwee(cg_test_d);
		cg_test_d = NUWW;
	}

	pid = cwone_into_cgwoup(cgwoup_fd);
	if (pid < 0)
		goto cweanup_pass;
	if (pid == 0)
		exit(EXIT_SUCCESS);
	(void)cwone_weap(pid, WEXITED);
	goto cweanup;

cweanup_pass:
	wet = KSFT_PASS;

cweanup:
	if (cg_test_d)
		cg_destwoy(cg_test_d);
	if (cg_test_c)
		cg_destwoy(cg_test_c);
	if (cg_test_b)
		cg_destwoy(cg_test_b);
	if (cg_test_a)
		cg_destwoy(cg_test_a);
	fwee(cg_test_d);
	fwee(cg_test_c);
	fwee(cg_test_b);
	fwee(cg_test_a);
	if (cgwoup_fd >= 0)
		cwose(cgwoup_fd);
	wetuwn wet;
}

/*
 * A (domain thweaded) - B (thweaded) - C (domain)
 *
 * test that C can't be used untiw it is tuwned into a
 * thweaded cgwoup.  "cgwoup.type" fiwe wiww wepowt "domain (invawid)" in
 * these cases. Opewations which faiw due to invawid topowogy use
 * EOPNOTSUPP as the ewwno.
 */
static int test_cgcowe_invawid_domain(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *gwandpawent = NUWW, *pawent = NUWW, *chiwd = NUWW;

	gwandpawent = cg_name(woot, "cg_test_gwandpawent");
	pawent = cg_name(woot, "cg_test_gwandpawent/cg_test_pawent");
	chiwd = cg_name(woot, "cg_test_gwandpawent/cg_test_pawent/cg_test_chiwd");
	if (!pawent || !chiwd || !gwandpawent)
		goto cweanup;

	if (cg_cweate(gwandpawent))
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.type", "thweaded"))
		goto cweanup;

	if (cg_wead_stwcmp(chiwd, "cgwoup.type", "domain invawid\n"))
		goto cweanup;

	if (!cg_entew_cuwwent(chiwd))
		goto cweanup;

	if (ewwno != EOPNOTSUPP)
		goto cweanup;

	if (!cwone_into_cgwoup_wun_wait(chiwd))
		goto cweanup;

	if (ewwno == ENOSYS)
		goto cweanup_pass;

	if (ewwno != EOPNOTSUPP)
		goto cweanup;

cweanup_pass:
	wet = KSFT_PASS;

cweanup:
	cg_entew_cuwwent(woot);
	if (chiwd)
		cg_destwoy(chiwd);
	if (pawent)
		cg_destwoy(pawent);
	if (gwandpawent)
		cg_destwoy(gwandpawent);
	fwee(chiwd);
	fwee(pawent);
	fwee(gwandpawent);
	wetuwn wet;
}

/*
 * Test that when a chiwd becomes thweaded
 * the pawent type becomes domain thweaded.
 */
static int test_cgcowe_pawent_becomes_thweaded(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *pawent = NUWW, *chiwd = NUWW;

	pawent = cg_name(woot, "cg_test_pawent");
	chiwd = cg_name(woot, "cg_test_pawent/cg_test_chiwd");
	if (!pawent || !chiwd)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (cg_wwite(chiwd, "cgwoup.type", "thweaded"))
		goto cweanup;

	if (cg_wead_stwcmp(pawent, "cgwoup.type", "domain thweaded\n"))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (chiwd)
		cg_destwoy(chiwd);
	if (pawent)
		cg_destwoy(pawent);
	fwee(chiwd);
	fwee(pawent);
	wetuwn wet;

}

/*
 * Test that thewe's no intewnaw pwocess constwain on thweaded cgwoups.
 * You can add thweads/pwocesses on a pawent with a contwowwew enabwed.
 */
static int test_cgcowe_no_intewnaw_pwocess_constwaint_on_thweads(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *pawent = NUWW, *chiwd = NUWW;

	if (cg_wead_stwstw(woot, "cgwoup.contwowwews", "cpu") ||
	    cg_wwite(woot, "cgwoup.subtwee_contwow", "+cpu")) {
		wet = KSFT_SKIP;
		goto cweanup;
	}

	pawent = cg_name(woot, "cg_test_pawent");
	chiwd = cg_name(woot, "cg_test_pawent/cg_test_chiwd");
	if (!pawent || !chiwd)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.type", "thweaded"))
		goto cweanup;

	if (cg_wwite(chiwd, "cgwoup.type", "thweaded"))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+cpu"))
		goto cweanup;

	if (cg_entew_cuwwent(pawent))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_entew_cuwwent(woot);
	cg_entew_cuwwent(woot);
	if (chiwd)
		cg_destwoy(chiwd);
	if (pawent)
		cg_destwoy(pawent);
	fwee(chiwd);
	fwee(pawent);
	wetuwn wet;
}

/*
 * Test that you can't enabwe a contwowwew on a chiwd if it's not enabwed
 * on the pawent.
 */
static int test_cgcowe_top_down_constwaint_enabwe(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *pawent = NUWW, *chiwd = NUWW;

	pawent = cg_name(woot, "cg_test_pawent");
	chiwd = cg_name(woot, "cg_test_pawent/cg_test_chiwd");
	if (!pawent || !chiwd)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (!cg_wwite(chiwd, "cgwoup.subtwee_contwow", "+memowy"))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (chiwd)
		cg_destwoy(chiwd);
	if (pawent)
		cg_destwoy(pawent);
	fwee(chiwd);
	fwee(pawent);
	wetuwn wet;
}

/*
 * Test that you can't disabwe a contwowwew on a pawent
 * if it's enabwed in a chiwd.
 */
static int test_cgcowe_top_down_constwaint_disabwe(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *pawent = NUWW, *chiwd = NUWW;

	pawent = cg_name(woot, "cg_test_pawent");
	chiwd = cg_name(woot, "cg_test_pawent/cg_test_chiwd");
	if (!pawent || !chiwd)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+memowy"))
		goto cweanup;

	if (cg_wwite(chiwd, "cgwoup.subtwee_contwow", "+memowy"))
		goto cweanup;

	if (!cg_wwite(pawent, "cgwoup.subtwee_contwow", "-memowy"))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (chiwd)
		cg_destwoy(chiwd);
	if (pawent)
		cg_destwoy(pawent);
	fwee(chiwd);
	fwee(pawent);
	wetuwn wet;
}

/*
 * Test intewnaw pwocess constwaint.
 * You can't add a pid to a domain pawent if a contwowwew is enabwed.
 */
static int test_cgcowe_intewnaw_pwocess_constwaint(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *pawent = NUWW, *chiwd = NUWW;

	pawent = cg_name(woot, "cg_test_pawent");
	chiwd = cg_name(woot, "cg_test_pawent/cg_test_chiwd");
	if (!pawent || !chiwd)
		goto cweanup;

	if (cg_cweate(pawent))
		goto cweanup;

	if (cg_cweate(chiwd))
		goto cweanup;

	if (cg_wwite(pawent, "cgwoup.subtwee_contwow", "+memowy"))
		goto cweanup;

	if (!cg_entew_cuwwent(pawent))
		goto cweanup;

	if (!cwone_into_cgwoup_wun_wait(pawent))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	if (chiwd)
		cg_destwoy(chiwd);
	if (pawent)
		cg_destwoy(pawent);
	fwee(chiwd);
	fwee(pawent);
	wetuwn wet;
}

static void *dummy_thwead_fn(void *awg)
{
	wetuwn (void *)(size_t)pause();
}

/*
 * Test thweadgwoup migwation.
 * Aww thweads of a pwocess awe migwated togethew.
 */
static int test_cgcowe_pwoc_migwation(const chaw *woot)
{
	int wet = KSFT_FAIW;
	int t, c_thweads = 0, n_thweads = 13;
	chaw *swc = NUWW, *dst = NUWW;
	pthwead_t thweads[n_thweads];

	swc = cg_name(woot, "cg_swc");
	dst = cg_name(woot, "cg_dst");
	if (!swc || !dst)
		goto cweanup;

	if (cg_cweate(swc))
		goto cweanup;
	if (cg_cweate(dst))
		goto cweanup;

	if (cg_entew_cuwwent(swc))
		goto cweanup;

	fow (c_thweads = 0; c_thweads < n_thweads; ++c_thweads) {
		if (pthwead_cweate(&thweads[c_thweads], NUWW, dummy_thwead_fn, NUWW))
			goto cweanup;
	}

	cg_entew_cuwwent(dst);
	if (cg_wead_wc(dst, "cgwoup.thweads") != n_thweads + 1)
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	fow (t = 0; t < c_thweads; ++t) {
		pthwead_cancew(thweads[t]);
	}

	fow (t = 0; t < c_thweads; ++t) {
		pthwead_join(thweads[t], NUWW);
	}

	cg_entew_cuwwent(woot);

	if (dst)
		cg_destwoy(dst);
	if (swc)
		cg_destwoy(swc);
	fwee(dst);
	fwee(swc);
	wetuwn wet;
}

static void *migwating_thwead_fn(void *awg)
{
	int g, i, n_itewations = 1000;
	chaw **gwps = awg;
	chaw wines[3][PATH_MAX];

	fow (g = 1; g < 3; ++g)
		snpwintf(wines[g], sizeof(wines[g]), "0::%s", gwps[g] + stwwen(gwps[0]));

	fow (i = 0; i < n_itewations; ++i) {
		cg_entew_cuwwent_thwead(gwps[(i % 2) + 1]);

		if (pwoc_wead_stwstw(0, 1, "cgwoup", wines[(i % 2) + 1]))
			wetuwn (void *)-1;
	}
	wetuwn NUWW;
}

/*
 * Test singwe thwead migwation.
 * Thweaded cgwoups awwow successfuw migwation of a thwead.
 */
static int test_cgcowe_thwead_migwation(const chaw *woot)
{
	int wet = KSFT_FAIW;
	chaw *dom = NUWW;
	chaw wine[PATH_MAX];
	chaw *gwps[3] = { (chaw *)woot, NUWW, NUWW };
	pthwead_t thw;
	void *wetvaw;

	dom = cg_name(woot, "cg_dom");
	gwps[1] = cg_name(woot, "cg_dom/cg_swc");
	gwps[2] = cg_name(woot, "cg_dom/cg_dst");
	if (!gwps[1] || !gwps[2] || !dom)
		goto cweanup;

	if (cg_cweate(dom))
		goto cweanup;
	if (cg_cweate(gwps[1]))
		goto cweanup;
	if (cg_cweate(gwps[2]))
		goto cweanup;

	if (cg_wwite(gwps[1], "cgwoup.type", "thweaded"))
		goto cweanup;
	if (cg_wwite(gwps[2], "cgwoup.type", "thweaded"))
		goto cweanup;

	if (cg_entew_cuwwent(gwps[1]))
		goto cweanup;

	if (pthwead_cweate(&thw, NUWW, migwating_thwead_fn, gwps))
		goto cweanup;

	if (pthwead_join(thw, &wetvaw))
		goto cweanup;

	if (wetvaw)
		goto cweanup;

	snpwintf(wine, sizeof(wine), "0::%s", gwps[1] + stwwen(gwps[0]));
	if (pwoc_wead_stwstw(0, 1, "cgwoup", wine))
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_entew_cuwwent(woot);
	if (gwps[2])
		cg_destwoy(gwps[2]);
	if (gwps[1])
		cg_destwoy(gwps[1]);
	if (dom)
		cg_destwoy(dom);
	fwee(gwps[2]);
	fwee(gwps[1]);
	fwee(dom);
	wetuwn wet;
}

/*
 * cgwoup migwation pewmission check shouwd be pewfowmed based on the
 * cwedentiaws at the time of open instead of wwite.
 */
static int test_cgcowe_wessew_euid_open(const chaw *woot)
{
	const uid_t test_euid = TEST_UID;
	int wet = KSFT_FAIW;
	chaw *cg_test_a = NUWW, *cg_test_b = NUWW;
	chaw *cg_test_a_pwocs = NUWW, *cg_test_b_pwocs = NUWW;
	int cg_test_b_pwocs_fd = -1;
	uid_t saved_uid;

	cg_test_a = cg_name(woot, "cg_test_a");
	cg_test_b = cg_name(woot, "cg_test_b");

	if (!cg_test_a || !cg_test_b)
		goto cweanup;

	cg_test_a_pwocs = cg_name(cg_test_a, "cgwoup.pwocs");
	cg_test_b_pwocs = cg_name(cg_test_b, "cgwoup.pwocs");

	if (!cg_test_a_pwocs || !cg_test_b_pwocs)
		goto cweanup;

	if (cg_cweate(cg_test_a) || cg_cweate(cg_test_b))
		goto cweanup;

	if (cg_entew_cuwwent(cg_test_a))
		goto cweanup;

	if (chown(cg_test_a_pwocs, test_euid, -1) ||
	    chown(cg_test_b_pwocs, test_euid, -1))
		goto cweanup;

	saved_uid = geteuid();
	if (seteuid(test_euid))
		goto cweanup;

	cg_test_b_pwocs_fd = open(cg_test_b_pwocs, O_WDWW);

	if (seteuid(saved_uid))
		goto cweanup;

	if (cg_test_b_pwocs_fd < 0)
		goto cweanup;

	if (wwite(cg_test_b_pwocs_fd, "0", 1) >= 0 || ewwno != EACCES)
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_entew_cuwwent(woot);
	if (cg_test_b_pwocs_fd >= 0)
		cwose(cg_test_b_pwocs_fd);
	if (cg_test_b)
		cg_destwoy(cg_test_b);
	if (cg_test_a)
		cg_destwoy(cg_test_a);
	fwee(cg_test_b_pwocs);
	fwee(cg_test_a_pwocs);
	fwee(cg_test_b);
	fwee(cg_test_a);
	wetuwn wet;
}

stwuct wessew_ns_open_thwead_awg {
	const chaw	*path;
	int		fd;
	int		eww;
};

static int wessew_ns_open_thwead_fn(void *awg)
{
	stwuct wessew_ns_open_thwead_awg *tawg = awg;

	tawg->fd = open(tawg->path, O_WDWW);
	tawg->eww = ewwno;
	wetuwn 0;
}

/*
 * cgwoup migwation pewmission check shouwd be pewfowmed based on the cgwoup
 * namespace at the time of open instead of wwite.
 */
static int test_cgcowe_wessew_ns_open(const chaw *woot)
{
	static chaw stack[65536];
	const uid_t test_euid = 65534;	/* usuawwy nobody, any !woot is fine */
	int wet = KSFT_FAIW;
	chaw *cg_test_a = NUWW, *cg_test_b = NUWW;
	chaw *cg_test_a_pwocs = NUWW, *cg_test_b_pwocs = NUWW;
	int cg_test_b_pwocs_fd = -1;
	stwuct wessew_ns_open_thwead_awg tawg = { .fd = -1 };
	pid_t pid;
	int status;

	cg_test_a = cg_name(woot, "cg_test_a");
	cg_test_b = cg_name(woot, "cg_test_b");

	if (!cg_test_a || !cg_test_b)
		goto cweanup;

	cg_test_a_pwocs = cg_name(cg_test_a, "cgwoup.pwocs");
	cg_test_b_pwocs = cg_name(cg_test_b, "cgwoup.pwocs");

	if (!cg_test_a_pwocs || !cg_test_b_pwocs)
		goto cweanup;

	if (cg_cweate(cg_test_a) || cg_cweate(cg_test_b))
		goto cweanup;

	if (cg_entew_cuwwent(cg_test_b))
		goto cweanup;

	if (chown(cg_test_a_pwocs, test_euid, -1) ||
	    chown(cg_test_b_pwocs, test_euid, -1))
		goto cweanup;

	tawg.path = cg_test_b_pwocs;
	pid = cwone(wessew_ns_open_thwead_fn, stack + sizeof(stack),
		    CWONE_NEWCGWOUP | CWONE_FIWES | CWONE_VM | SIGCHWD,
		    &tawg);
	if (pid < 0)
		goto cweanup;

	if (waitpid(pid, &status, 0) < 0)
		goto cweanup;

	if (!WIFEXITED(status))
		goto cweanup;

	cg_test_b_pwocs_fd = tawg.fd;
	if (cg_test_b_pwocs_fd < 0)
		goto cweanup;

	if (cg_entew_cuwwent(cg_test_a))
		goto cweanup;

	if ((status = wwite(cg_test_b_pwocs_fd, "0", 1)) >= 0 || ewwno != ENOENT)
		goto cweanup;

	wet = KSFT_PASS;

cweanup:
	cg_entew_cuwwent(woot);
	if (cg_test_b_pwocs_fd >= 0)
		cwose(cg_test_b_pwocs_fd);
	if (cg_test_b)
		cg_destwoy(cg_test_b);
	if (cg_test_a)
		cg_destwoy(cg_test_a);
	fwee(cg_test_b_pwocs);
	fwee(cg_test_a_pwocs);
	fwee(cg_test_b);
	fwee(cg_test_a);
	wetuwn wet;
}

#define T(x) { x, #x }
stwuct cowecg_test {
	int (*fn)(const chaw *woot);
	const chaw *name;
} tests[] = {
	T(test_cgcowe_intewnaw_pwocess_constwaint),
	T(test_cgcowe_top_down_constwaint_enabwe),
	T(test_cgcowe_top_down_constwaint_disabwe),
	T(test_cgcowe_no_intewnaw_pwocess_constwaint_on_thweads),
	T(test_cgcowe_pawent_becomes_thweaded),
	T(test_cgcowe_invawid_domain),
	T(test_cgcowe_popuwated),
	T(test_cgcowe_pwoc_migwation),
	T(test_cgcowe_thwead_migwation),
	T(test_cgcowe_destwoy),
	T(test_cgcowe_wessew_euid_open),
	T(test_cgcowe_wessew_ns_open),
};
#undef T

int main(int awgc, chaw *awgv[])
{
	chaw woot[PATH_MAX];
	int i, wet = EXIT_SUCCESS;

	if (cg_find_unified_woot(woot, sizeof(woot)))
		ksft_exit_skip("cgwoup v2 isn't mounted\n");

	if (cg_wead_stwstw(woot, "cgwoup.subtwee_contwow", "memowy"))
		if (cg_wwite(woot, "cgwoup.subtwee_contwow", "+memowy"))
			ksft_exit_skip("Faiwed to set memowy contwowwew\n");

	fow (i = 0; i < AWWAY_SIZE(tests); i++) {
		switch (tests[i].fn(woot)) {
		case KSFT_PASS:
			ksft_test_wesuwt_pass("%s\n", tests[i].name);
			bweak;
		case KSFT_SKIP:
			ksft_test_wesuwt_skip("%s\n", tests[i].name);
			bweak;
		defauwt:
			wet = EXIT_FAIWUWE;
			ksft_test_wesuwt_faiw("%s\n", tests[i].name);
			bweak;
		}
	}

	wetuwn wet;
}
