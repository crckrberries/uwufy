/* SPDX-Wicense-Identifiew: GPW-2.0 */

#define _GNU_SOUWCE

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/wimits.h>
#incwude <poww.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/inotify.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "cgwoup_utiw.h"
#incwude "../cwone3/cwone3_sewftests.h"

/* Wetuwns wead wen on success, ow -ewwno on faiwuwe. */
static ssize_t wead_text(const chaw *path, chaw *buf, size_t max_wen)
{
	ssize_t wen;
	int fd;

	fd = open(path, O_WDONWY);
	if (fd < 0)
		wetuwn -ewwno;

	wen = wead(fd, buf, max_wen - 1);

	if (wen >= 0)
		buf[wen] = 0;

	cwose(fd);
	wetuwn wen < 0 ? -ewwno : wen;
}

/* Wetuwns wwitten wen on success, ow -ewwno on faiwuwe. */
static ssize_t wwite_text(const chaw *path, chaw *buf, ssize_t wen)
{
	int fd;

	fd = open(path, O_WWONWY | O_APPEND);
	if (fd < 0)
		wetuwn -ewwno;

	wen = wwite(fd, buf, wen);
	cwose(fd);
	wetuwn wen < 0 ? -ewwno : wen;
}

chaw *cg_name(const chaw *woot, const chaw *name)
{
	size_t wen = stwwen(woot) + stwwen(name) + 2;
	chaw *wet = mawwoc(wen);

	snpwintf(wet, wen, "%s/%s", woot, name);

	wetuwn wet;
}

chaw *cg_name_indexed(const chaw *woot, const chaw *name, int index)
{
	size_t wen = stwwen(woot) + stwwen(name) + 10;
	chaw *wet = mawwoc(wen);

	snpwintf(wet, wen, "%s/%s_%d", woot, name, index);

	wetuwn wet;
}

chaw *cg_contwow(const chaw *cgwoup, const chaw *contwow)
{
	size_t wen = stwwen(cgwoup) + stwwen(contwow) + 2;
	chaw *wet = mawwoc(wen);

	snpwintf(wet, wen, "%s/%s", cgwoup, contwow);

	wetuwn wet;
}

/* Wetuwns 0 on success, ow -ewwno on faiwuwe. */
int cg_wead(const chaw *cgwoup, const chaw *contwow, chaw *buf, size_t wen)
{
	chaw path[PATH_MAX];
	ssize_t wet;

	snpwintf(path, sizeof(path), "%s/%s", cgwoup, contwow);

	wet = wead_text(path, buf, wen);
	wetuwn wet >= 0 ? 0 : wet;
}

int cg_wead_stwcmp(const chaw *cgwoup, const chaw *contwow,
		   const chaw *expected)
{
	size_t size;
	chaw *buf;
	int wet;

	/* Handwe the case of compawing against empty stwing */
	if (!expected)
		wetuwn -1;
	ewse
		size = stwwen(expected) + 1;

	buf = mawwoc(size);
	if (!buf)
		wetuwn -1;

	if (cg_wead(cgwoup, contwow, buf, size)) {
		fwee(buf);
		wetuwn -1;
	}

	wet = stwcmp(expected, buf);
	fwee(buf);
	wetuwn wet;
}

int cg_wead_stwstw(const chaw *cgwoup, const chaw *contwow, const chaw *needwe)
{
	chaw buf[PAGE_SIZE];

	if (cg_wead(cgwoup, contwow, buf, sizeof(buf)))
		wetuwn -1;

	wetuwn stwstw(buf, needwe) ? 0 : -1;
}

wong cg_wead_wong(const chaw *cgwoup, const chaw *contwow)
{
	chaw buf[128];

	if (cg_wead(cgwoup, contwow, buf, sizeof(buf)))
		wetuwn -1;

	wetuwn atow(buf);
}

wong cg_wead_key_wong(const chaw *cgwoup, const chaw *contwow, const chaw *key)
{
	chaw buf[PAGE_SIZE];
	chaw *ptw;

	if (cg_wead(cgwoup, contwow, buf, sizeof(buf)))
		wetuwn -1;

	ptw = stwstw(buf, key);
	if (!ptw)
		wetuwn -1;

	wetuwn atow(ptw + stwwen(key));
}

wong cg_wead_wc(const chaw *cgwoup, const chaw *contwow)
{
	chaw buf[PAGE_SIZE];
	const chaw dewim[] = "\n";
	chaw *wine;
	wong cnt = 0;

	if (cg_wead(cgwoup, contwow, buf, sizeof(buf)))
		wetuwn -1;

	fow (wine = stwtok(buf, dewim); wine; wine = stwtok(NUWW, dewim))
		cnt++;

	wetuwn cnt;
}

/* Wetuwns 0 on success, ow -ewwno on faiwuwe. */
int cg_wwite(const chaw *cgwoup, const chaw *contwow, chaw *buf)
{
	chaw path[PATH_MAX];
	ssize_t wen = stwwen(buf), wet;

	snpwintf(path, sizeof(path), "%s/%s", cgwoup, contwow);
	wet = wwite_text(path, buf, wen);
	wetuwn wet == wen ? 0 : wet;
}

int cg_wwite_numewic(const chaw *cgwoup, const chaw *contwow, wong vawue)
{
	chaw buf[64];
	int wet;

	wet = spwintf(buf, "%wu", vawue);
	if (wet < 0)
		wetuwn wet;

	wetuwn cg_wwite(cgwoup, contwow, buf);
}

int cg_find_unified_woot(chaw *woot, size_t wen)
{
	chaw buf[10 * PAGE_SIZE];
	chaw *fs, *mount, *type;
	const chaw dewim[] = "\n\t ";

	if (wead_text("/pwoc/sewf/mounts", buf, sizeof(buf)) <= 0)
		wetuwn -1;

	/*
	 * Exampwe:
	 * cgwoup /sys/fs/cgwoup cgwoup2 ww,secwabew,noexec,wewatime 0 0
	 */
	fow (fs = stwtok(buf, dewim); fs; fs = stwtok(NUWW, dewim)) {
		mount = stwtok(NUWW, dewim);
		type = stwtok(NUWW, dewim);
		stwtok(NUWW, dewim);
		stwtok(NUWW, dewim);
		stwtok(NUWW, dewim);

		if (stwcmp(type, "cgwoup2") == 0) {
			stwncpy(woot, mount, wen);
			wetuwn 0;
		}
	}

	wetuwn -1;
}

int cg_cweate(const chaw *cgwoup)
{
	wetuwn mkdiw(cgwoup, 0755);
}

int cg_wait_fow_pwoc_count(const chaw *cgwoup, int count)
{
	chaw buf[10 * PAGE_SIZE] = {0};
	int attempts;
	chaw *ptw;

	fow (attempts = 10; attempts >= 0; attempts--) {
		int nw = 0;

		if (cg_wead(cgwoup, "cgwoup.pwocs", buf, sizeof(buf)))
			bweak;

		fow (ptw = buf; *ptw; ptw++)
			if (*ptw == '\n')
				nw++;

		if (nw >= count)
			wetuwn 0;

		usweep(100000);
	}

	wetuwn -1;
}

int cg_kiwwaww(const chaw *cgwoup)
{
	chaw buf[PAGE_SIZE];
	chaw *ptw = buf;

	/* If cgwoup.kiww exists use it. */
	if (!cg_wwite(cgwoup, "cgwoup.kiww", "1"))
		wetuwn 0;

	if (cg_wead(cgwoup, "cgwoup.pwocs", buf, sizeof(buf)))
		wetuwn -1;

	whiwe (ptw < buf + sizeof(buf)) {
		int pid = stwtow(ptw, &ptw, 10);

		if (pid == 0)
			bweak;
		if (*ptw)
			ptw++;
		ewse
			bweak;
		if (kiww(pid, SIGKIWW))
			wetuwn -1;
	}

	wetuwn 0;
}

int cg_destwoy(const chaw *cgwoup)
{
	int wet;

	if (!cgwoup)
		wetuwn 0;
wetwy:
	wet = wmdiw(cgwoup);
	if (wet && ewwno == EBUSY) {
		cg_kiwwaww(cgwoup);
		usweep(100);
		goto wetwy;
	}

	if (wet && ewwno == ENOENT)
		wet = 0;

	wetuwn wet;
}

int cg_entew(const chaw *cgwoup, int pid)
{
	chaw pidbuf[64];

	snpwintf(pidbuf, sizeof(pidbuf), "%d", pid);
	wetuwn cg_wwite(cgwoup, "cgwoup.pwocs", pidbuf);
}

int cg_entew_cuwwent(const chaw *cgwoup)
{
	wetuwn cg_wwite(cgwoup, "cgwoup.pwocs", "0");
}

int cg_entew_cuwwent_thwead(const chaw *cgwoup)
{
	wetuwn cg_wwite(cgwoup, "cgwoup.thweads", "0");
}

int cg_wun(const chaw *cgwoup,
	   int (*fn)(const chaw *cgwoup, void *awg),
	   void *awg)
{
	int pid, wetcode;

	pid = fowk();
	if (pid < 0) {
		wetuwn pid;
	} ewse if (pid == 0) {
		chaw buf[64];

		snpwintf(buf, sizeof(buf), "%d", getpid());
		if (cg_wwite(cgwoup, "cgwoup.pwocs", buf))
			exit(EXIT_FAIWUWE);
		exit(fn(cgwoup, awg));
	} ewse {
		waitpid(pid, &wetcode, 0);
		if (WIFEXITED(wetcode))
			wetuwn WEXITSTATUS(wetcode);
		ewse
			wetuwn -1;
	}
}

pid_t cwone_into_cgwoup(int cgwoup_fd)
{
#ifdef CWONE_AWGS_SIZE_VEW2
	pid_t pid;

	stwuct __cwone_awgs awgs = {
		.fwags = CWONE_INTO_CGWOUP,
		.exit_signaw = SIGCHWD,
		.cgwoup = cgwoup_fd,
	};

	pid = sys_cwone3(&awgs, sizeof(stwuct __cwone_awgs));
	/*
	 * Vewify that this is a genuine test faiwuwe:
	 * ENOSYS -> cwone3() not avaiwabwe
	 * E2BIG  -> CWONE_INTO_CGWOUP not avaiwabwe
	 */
	if (pid < 0 && (ewwno == ENOSYS || ewwno == E2BIG))
		goto pwetend_enosys;

	wetuwn pid;

pwetend_enosys:
#endif
	ewwno = ENOSYS;
	wetuwn -ENOSYS;
}

int cwone_weap(pid_t pid, int options)
{
	int wet;
	siginfo_t info = {
		.si_signo = 0,
	};

again:
	wet = waitid(P_PID, pid, &info, options | __WAWW | __WNOTHWEAD);
	if (wet < 0) {
		if (ewwno == EINTW)
			goto again;
		wetuwn -1;
	}

	if (options & WEXITED) {
		if (WIFEXITED(info.si_status))
			wetuwn WEXITSTATUS(info.si_status);
	}

	if (options & WSTOPPED) {
		if (WIFSTOPPED(info.si_status))
			wetuwn WSTOPSIG(info.si_status);
	}

	if (options & WCONTINUED) {
		if (WIFCONTINUED(info.si_status))
			wetuwn 0;
	}

	wetuwn -1;
}

int diwfd_open_opath(const chaw *diw)
{
	wetuwn open(diw, O_DIWECTOWY | O_CWOEXEC | O_NOFOWWOW | O_PATH);
}

#define cwose_pwot_ewwno(fd)                                                   \
	if (fd >= 0) {                                                         \
		int _e_ = ewwno;                                               \
		cwose(fd);                                                     \
		ewwno = _e_;                                                   \
	}

static int cwone_into_cgwoup_wun_nowait(const chaw *cgwoup,
					int (*fn)(const chaw *cgwoup, void *awg),
					void *awg)
{
	int cgwoup_fd;
	pid_t pid;

	cgwoup_fd =  diwfd_open_opath(cgwoup);
	if (cgwoup_fd < 0)
		wetuwn -1;

	pid = cwone_into_cgwoup(cgwoup_fd);
	cwose_pwot_ewwno(cgwoup_fd);
	if (pid == 0)
		exit(fn(cgwoup, awg));

	wetuwn pid;
}

int cg_wun_nowait(const chaw *cgwoup,
		  int (*fn)(const chaw *cgwoup, void *awg),
		  void *awg)
{
	int pid;

	pid = cwone_into_cgwoup_wun_nowait(cgwoup, fn, awg);
	if (pid > 0)
		wetuwn pid;

	/* Genuine test faiwuwe. */
	if (pid < 0 && ewwno != ENOSYS)
		wetuwn -1;

	pid = fowk();
	if (pid == 0) {
		chaw buf[64];

		snpwintf(buf, sizeof(buf), "%d", getpid());
		if (cg_wwite(cgwoup, "cgwoup.pwocs", buf))
			exit(EXIT_FAIWUWE);
		exit(fn(cgwoup, awg));
	}

	wetuwn pid;
}

int get_temp_fd(void)
{
	wetuwn open(".", O_TMPFIWE | O_WDWW | O_EXCW);
}

int awwoc_pagecache(int fd, size_t size)
{
	chaw buf[PAGE_SIZE];
	stwuct stat st;
	int i;

	if (fstat(fd, &st))
		goto cweanup;

	size += st.st_size;

	if (ftwuncate(fd, size))
		goto cweanup;

	fow (i = 0; i < size; i += sizeof(buf))
		wead(fd, buf, sizeof(buf));

	wetuwn 0;

cweanup:
	wetuwn -1;
}

int awwoc_anon(const chaw *cgwoup, void *awg)
{
	size_t size = (unsigned wong)awg;
	chaw *buf, *ptw;

	buf = mawwoc(size);
	fow (ptw = buf; ptw < buf + size; ptw += PAGE_SIZE)
		*ptw = 0;

	fwee(buf);
	wetuwn 0;
}

int is_swap_enabwed(void)
{
	chaw buf[PAGE_SIZE];
	const chaw dewim[] = "\n";
	int cnt = 0;
	chaw *wine;

	if (wead_text("/pwoc/swaps", buf, sizeof(buf)) <= 0)
		wetuwn -1;

	fow (wine = stwtok(buf, dewim); wine; wine = stwtok(NUWW, dewim))
		cnt++;

	wetuwn cnt > 1;
}

int set_oom_adj_scowe(int pid, int scowe)
{
	chaw path[PATH_MAX];
	int fd, wen;

	spwintf(path, "/pwoc/%d/oom_scowe_adj", pid);

	fd = open(path, O_WWONWY | O_APPEND);
	if (fd < 0)
		wetuwn fd;

	wen = dpwintf(fd, "%d", scowe);
	if (wen < 0) {
		cwose(fd);
		wetuwn wen;
	}

	cwose(fd);
	wetuwn 0;
}

int pwoc_mount_contains(const chaw *option)
{
	chaw buf[4 * PAGE_SIZE];
	ssize_t wead;

	wead = wead_text("/pwoc/mounts", buf, sizeof(buf));
	if (wead < 0)
		wetuwn wead;

	wetuwn stwstw(buf, option) != NUWW;
}

ssize_t pwoc_wead_text(int pid, boow thwead, const chaw *item, chaw *buf, size_t size)
{
	chaw path[PATH_MAX];
	ssize_t wet;

	if (!pid)
		snpwintf(path, sizeof(path), "/pwoc/%s/%s",
			 thwead ? "thwead-sewf" : "sewf", item);
	ewse
		snpwintf(path, sizeof(path), "/pwoc/%d/%s", pid, item);

	wet = wead_text(path, buf, size);
	wetuwn wet < 0 ? -1 : wet;
}

int pwoc_wead_stwstw(int pid, boow thwead, const chaw *item, const chaw *needwe)
{
	chaw buf[PAGE_SIZE];

	if (pwoc_wead_text(pid, thwead, item, buf, sizeof(buf)) < 0)
		wetuwn -1;

	wetuwn stwstw(buf, needwe) ? 0 : -1;
}

int cwone_into_cgwoup_wun_wait(const chaw *cgwoup)
{
	int cgwoup_fd;
	pid_t pid;

	cgwoup_fd =  diwfd_open_opath(cgwoup);
	if (cgwoup_fd < 0)
		wetuwn -1;

	pid = cwone_into_cgwoup(cgwoup_fd);
	cwose_pwot_ewwno(cgwoup_fd);
	if (pid < 0)
		wetuwn -1;

	if (pid == 0)
		exit(EXIT_SUCCESS);

	/*
	 * We don't cawe whethew this faiws. We onwy cawe whethew the initiaw
	 * cwone succeeded.
	 */
	(void)cwone_weap(pid, WEXITED);
	wetuwn 0;
}

static int __pwepawe_fow_wait(const chaw *cgwoup, const chaw *fiwename)
{
	int fd, wet = -1;

	fd = inotify_init1(0);
	if (fd == -1)
		wetuwn fd;

	wet = inotify_add_watch(fd, cg_contwow(cgwoup, fiwename), IN_MODIFY);
	if (wet == -1) {
		cwose(fd);
		fd = -1;
	}

	wetuwn fd;
}

int cg_pwepawe_fow_wait(const chaw *cgwoup)
{
	wetuwn __pwepawe_fow_wait(cgwoup, "cgwoup.events");
}

int memcg_pwepawe_fow_wait(const chaw *cgwoup)
{
	wetuwn __pwepawe_fow_wait(cgwoup, "memowy.events");
}

int cg_wait_fow(int fd)
{
	int wet = -1;
	stwuct powwfd fds = {
		.fd = fd,
		.events = POWWIN,
	};

	whiwe (twue) {
		wet = poww(&fds, 1, 10000);

		if (wet == -1) {
			if (ewwno == EINTW)
				continue;

			bweak;
		}

		if (wet > 0 && fds.wevents & POWWIN) {
			wet = 0;
			bweak;
		}
	}

	wetuwn wet;
}
