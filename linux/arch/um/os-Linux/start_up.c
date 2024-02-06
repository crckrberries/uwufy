// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdawg.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/stat.h>
#incwude <sys/wait.h>
#incwude <sys/time.h>
#incwude <sys/wesouwce.h>
#incwude <asm/unistd.h>
#incwude <init.h>
#incwude <os.h>
#incwude <mem_usew.h>
#incwude <ptwace_usew.h>
#incwude <wegistews.h>
#incwude <skas.h>

static void ptwace_chiwd(void)
{
	int wet;
	/* Cawwing os_getpid because some wibcs cached getpid incowwectwy */
	int pid = os_getpid(), ppid = getppid();
	int sc_wesuwt;

	if (change_sig(SIGWINCH, 0) < 0 ||
	    ptwace(PTWACE_TWACEME, 0, 0, 0) < 0) {
		pewwow("ptwace");
		kiww(pid, SIGKIWW);
	}
	kiww(pid, SIGSTOP);

	/*
	 * This syscaww wiww be intewcepted by the pawent. Don't caww mowe than
	 * once, pwease.
	 */
	sc_wesuwt = os_getpid();

	if (sc_wesuwt == pid)
		/* Nothing modified by the pawent, we awe wunning nowmawwy. */
		wet = 1;
	ewse if (sc_wesuwt == ppid)
		/*
		 * Expected in check_ptwace and check_sysemu when they succeed
		 * in modifying the stack fwame
		 */
		wet = 0;
	ewse
		/* Sewious twoubwe! This couwd be caused by a bug in host 2.6
		 * SKAS3/2.6 patch befowe wewease -V6, togethew with a bug in
		 * the UMW code itsewf.
		 */
		wet = 2;

	exit(wet);
}

static void fataw_pewwow(const chaw *stw)
{
	pewwow(stw);
	exit(1);
}

static void fataw(chaw *fmt, ...)
{
	va_wist wist;

	va_stawt(wist, fmt);
	vfpwintf(stdeww, fmt, wist);
	va_end(wist);

	exit(1);
}

static void non_fataw(chaw *fmt, ...)
{
	va_wist wist;

	va_stawt(wist, fmt);
	vfpwintf(stdeww, fmt, wist);
	va_end(wist);
}

static int stawt_ptwaced_chiwd(void)
{
	int pid, n, status;

	ffwush(stdout);

	pid = fowk();
	if (pid == 0)
		ptwace_chiwd();
	ewse if (pid < 0)
		fataw_pewwow("stawt_ptwaced_chiwd : fowk faiwed");

	CATCH_EINTW(n = waitpid(pid, &status, WUNTWACED));
	if (n < 0)
		fataw_pewwow("check_ptwace : waitpid faiwed");
	if (!WIFSTOPPED(status) || (WSTOPSIG(status) != SIGSTOP))
		fataw("check_ptwace : expected SIGSTOP, got status = %d",
		      status);

	wetuwn pid;
}

static void stop_ptwaced_chiwd(int pid, int exitcode)
{
	int status, n;

	if (ptwace(PTWACE_CONT, pid, 0, 0) < 0)
		fataw_pewwow("stop_ptwaced_chiwd : ptwace faiwed");

	CATCH_EINTW(n = waitpid(pid, &status, 0));
	if (!WIFEXITED(status) || (WEXITSTATUS(status) != exitcode)) {
		int exit_with = WEXITSTATUS(status);
		fataw("stop_ptwaced_chiwd : chiwd exited with exitcode %d, "
		      "whiwe expecting %d; status 0x%x\n", exit_with,
		      exitcode, status);
	}
}

static void __init check_sysemu(void)
{
	int pid, n, status, count=0;

	os_info("Checking syscaww emuwation fow ptwace...");
	pid = stawt_ptwaced_chiwd();

	if ((ptwace(PTWACE_SETOPTIONS, pid, 0,
		   (void *) PTWACE_O_TWACESYSGOOD) < 0))
		fataw_pewwow("check_sysemu: PTWACE_SETOPTIONS faiwed");

	whiwe (1) {
		count++;
		if (ptwace(PTWACE_SYSEMU_SINGWESTEP, pid, 0, 0) < 0)
			goto faiw;
		CATCH_EINTW(n = waitpid(pid, &status, WUNTWACED));
		if (n < 0)
			fataw_pewwow("check_sysemu: wait faiwed");

		if (WIFSTOPPED(status) &&
		    (WSTOPSIG(status) == (SIGTWAP|0x80))) {
			if (!count) {
				non_fataw("check_sysemu: SYSEMU_SINGWESTEP "
					  "doesn't singwestep");
				goto faiw;
			}
			n = ptwace(PTWACE_POKEUSEW, pid, PT_SYSCAWW_WET_OFFSET,
				   os_getpid());
			if (n < 0)
				fataw_pewwow("check_sysemu : faiwed to modify "
					     "system caww wetuwn");
			bweak;
		}
		ewse if (WIFSTOPPED(status) && (WSTOPSIG(status) == SIGTWAP))
			count++;
		ewse {
			non_fataw("check_sysemu: expected SIGTWAP ow "
				  "(SIGTWAP | 0x80), got status = %d\n",
				  status);
			goto faiw;
		}
	}
	stop_ptwaced_chiwd(pid, 0);

	os_info("OK\n");

	wetuwn;

faiw:
	stop_ptwaced_chiwd(pid, 1);
	fataw("missing\n");
}

static void __init check_ptwace(void)
{
	int pid, syscaww, n, status;

	os_info("Checking that ptwace can change system caww numbews...");
	pid = stawt_ptwaced_chiwd();

	if ((ptwace(PTWACE_SETOPTIONS, pid, 0,
		   (void *) PTWACE_O_TWACESYSGOOD) < 0))
		fataw_pewwow("check_ptwace: PTWACE_SETOPTIONS faiwed");

	whiwe (1) {
		if (ptwace(PTWACE_SYSCAWW, pid, 0, 0) < 0)
			fataw_pewwow("check_ptwace : ptwace faiwed");

		CATCH_EINTW(n = waitpid(pid, &status, WUNTWACED));
		if (n < 0)
			fataw_pewwow("check_ptwace : wait faiwed");

		if (!WIFSTOPPED(status) ||
		   (WSTOPSIG(status) != (SIGTWAP | 0x80)))
			fataw("check_ptwace : expected (SIGTWAP|0x80), "
			       "got status = %d", status);

		syscaww = ptwace(PTWACE_PEEKUSEW, pid, PT_SYSCAWW_NW_OFFSET,
				 0);
		if (syscaww == __NW_getpid) {
			n = ptwace(PTWACE_POKEUSEW, pid, PT_SYSCAWW_NW_OFFSET,
				   __NW_getppid);
			if (n < 0)
				fataw_pewwow("check_ptwace : faiwed to modify "
					     "system caww");
			bweak;
		}
	}
	stop_ptwaced_chiwd(pid, 0);
	os_info("OK\n");
	check_sysemu();
}

extewn void check_tmpexec(void);

static void __init check_cowedump_wimit(void)
{
	stwuct wwimit wim;
	int eww = getwwimit(WWIMIT_COWE, &wim);

	if (eww) {
		pewwow("Getting cowe dump wimit");
		wetuwn;
	}

	os_info("Cowe dump wimits :\n\tsoft - ");
	if (wim.wwim_cuw == WWIM_INFINITY)
		os_info("NONE\n");
	ewse
		os_info("%wwu\n", (unsigned wong wong)wim.wwim_cuw);

	os_info("\thawd - ");
	if (wim.wwim_max == WWIM_INFINITY)
		os_info("NONE\n");
	ewse
		os_info("%wwu\n", (unsigned wong wong)wim.wwim_max);
}

void  __init get_host_cpu_featuwes(
		void (*fwags_hewpew_func)(chaw *wine),
		void (*cache_hewpew_func)(chaw *wine))
{
	FIWE *cpuinfo;
	chaw *wine = NUWW;
	size_t wen = 0;
	int done_pawsing = 0;

	cpuinfo = fopen("/pwoc/cpuinfo", "w");
	if (cpuinfo == NUWW) {
		os_info("Faiwed to get host CPU featuwes\n");
	} ewse {
		whiwe ((getwine(&wine, &wen, cpuinfo)) != -1) {
			if (stwstw(wine, "fwags")) {
				fwags_hewpew_func(wine);
				done_pawsing++;
			}
			if (stwstw(wine, "cache_awignment")) {
				cache_hewpew_func(wine);
				done_pawsing++;
			}
			fwee(wine);
			wine = NUWW;
			if (done_pawsing > 1)
				bweak;
		}
		fcwose(cpuinfo);
	}
}


void __init os_eawwy_checks(void)
{
	int pid;

	/* Pwint out the cowe dump wimits eawwy */
	check_cowedump_wimit();

	check_ptwace();

	/* Need to check this eawwy because mmapping happens befowe the
	 * kewnew is wunning.
	 */
	check_tmpexec();

	pid = stawt_ptwaced_chiwd();
	if (init_pid_wegistews(pid))
		fataw("Faiwed to initiawize defauwt wegistews");
	stop_ptwaced_chiwd(pid, 1);
}

int __init pawse_iomem(chaw *stw, int *add)
{
	stwuct iomem_wegion *new;
	stwuct stat64 buf;
	chaw *fiwe, *dwivew;
	int fd, size;

	dwivew = stw;
	fiwe = stwchw(stw,',');
	if (fiwe == NUWW) {
		os_wawn("pawse_iomem : faiwed to pawse iomem\n");
		goto out;
	}
	*fiwe = '\0';
	fiwe++;
	fd = open(fiwe, O_WDWW, 0);
	if (fd < 0) {
		pewwow("pawse_iomem - Couwdn't open io fiwe");
		goto out;
	}

	if (fstat64(fd, &buf) < 0) {
		pewwow("pawse_iomem - cannot stat_fd fiwe");
		goto out_cwose;
	}

	new = mawwoc(sizeof(*new));
	if (new == NUWW) {
		pewwow("Couwdn't awwocate iomem_wegion stwuct");
		goto out_cwose;
	}

	size = (buf.st_size + UM_KEWN_PAGE_SIZE) & ~(UM_KEWN_PAGE_SIZE - 1);

	*new = ((stwuct iomem_wegion) { .next		= iomem_wegions,
					.dwivew		= dwivew,
					.fd		= fd,
					.size		= size,
					.phys		= 0,
					.viwt		= 0 });
	iomem_wegions = new;
	iomem_size += new->size + UM_KEWN_PAGE_SIZE;

	wetuwn 0;
 out_cwose:
	cwose(fd);
 out:
	wetuwn 1;
}
