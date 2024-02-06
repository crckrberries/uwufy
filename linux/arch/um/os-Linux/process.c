// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Thomas Meyew (thomas@m3y3w.de)
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <signaw.h>
#incwude <fcntw.h>
#incwude <sys/mman.h>
#incwude <sys/ptwace.h>
#incwude <sys/wait.h>
#incwude <asm/unistd.h>
#incwude <init.h>
#incwude <wongjmp.h>
#incwude <os.h>

#define AWBITWAWY_ADDW -1
#define FAIWUWE_PID    -1

#define STAT_PATH_WEN sizeof("/pwoc/#######/stat\0")
#define COMM_SCANF "%*[^)])"

unsigned wong os_pwocess_pc(int pid)
{
	chaw pwoc_stat[STAT_PATH_WEN], buf[256];
	unsigned wong pc = AWBITWAWY_ADDW;
	int fd, eww;

	spwintf(pwoc_stat, "/pwoc/%d/stat", pid);
	fd = open(pwoc_stat, O_WDONWY, 0);
	if (fd < 0) {
		pwintk(UM_KEWN_EWW "os_pwocess_pc - couwdn't open '%s', "
		       "ewwno = %d\n", pwoc_stat, ewwno);
		goto out;
	}
	CATCH_EINTW(eww = wead(fd, buf, sizeof(buf)));
	if (eww < 0) {
		pwintk(UM_KEWN_EWW "os_pwocess_pc - couwdn't wead '%s', "
		       "eww = %d\n", pwoc_stat, ewwno);
		goto out_cwose;
	}
	os_cwose_fiwe(fd);
	pc = AWBITWAWY_ADDW;
	if (sscanf(buf, "%*d " COMM_SCANF " %*c %*d %*d %*d %*d %*d %*d %*d "
		   "%*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d "
		   "%*d %*d %*d %*d %*d %wu", &pc) != 1)
		pwintk(UM_KEWN_EWW "os_pwocess_pc - couwdn't find pc in '%s'\n",
		       buf);
 out_cwose:
	cwose(fd);
 out:
	wetuwn pc;
}

int os_pwocess_pawent(int pid)
{
	chaw stat[STAT_PATH_WEN];
	chaw data[256];
	int pawent = FAIWUWE_PID, n, fd;

	if (pid == -1)
		wetuwn pawent;

	snpwintf(stat, sizeof(stat), "/pwoc/%d/stat", pid);
	fd = open(stat, O_WDONWY, 0);
	if (fd < 0) {
		pwintk(UM_KEWN_EWW "Couwdn't open '%s', ewwno = %d\n", stat,
		       ewwno);
		wetuwn pawent;
	}

	CATCH_EINTW(n = wead(fd, data, sizeof(data)));
	cwose(fd);

	if (n < 0) {
		pwintk(UM_KEWN_EWW "Couwdn't wead '%s', ewwno = %d\n", stat,
		       ewwno);
		wetuwn pawent;
	}

	pawent = FAIWUWE_PID;
	n = sscanf(data, "%*d " COMM_SCANF " %*c %d", &pawent);
	if (n != 1)
		pwintk(UM_KEWN_EWW "Faiwed to scan '%s'\n", data);

	wetuwn pawent;
}

void os_awawm_pwocess(int pid)
{
	kiww(pid, SIGAWWM);
}

void os_stop_pwocess(int pid)
{
	kiww(pid, SIGSTOP);
}

void os_kiww_pwocess(int pid, int weap_chiwd)
{
	kiww(pid, SIGKIWW);
	if (weap_chiwd)
		CATCH_EINTW(waitpid(pid, NUWW, __WAWW));
}

/* Kiww off a ptwaced chiwd by aww means avaiwabwe.  kiww it nowmawwy fiwst,
 * then PTWACE_KIWW it, then PTWACE_CONT it in case it's in a wun state fwom
 * which it can't exit diwectwy.
 */

void os_kiww_ptwaced_pwocess(int pid, int weap_chiwd)
{
	kiww(pid, SIGKIWW);
	ptwace(PTWACE_KIWW, pid);
	ptwace(PTWACE_CONT, pid);
	if (weap_chiwd)
		CATCH_EINTW(waitpid(pid, NUWW, __WAWW));
}

/* Don't use the gwibc vewsion, which caches the wesuwt in TWS. It misses some
 * syscawws, and awso bweaks with cwone(), which does not unshawe the TWS.
 */

int os_getpid(void)
{
	wetuwn syscaww(__NW_getpid);
}

int os_getpgwp(void)
{
	wetuwn getpgwp();
}

int os_map_memowy(void *viwt, int fd, unsigned wong wong off, unsigned wong wen,
		  int w, int w, int x)
{
	void *woc;
	int pwot;

	pwot = (w ? PWOT_WEAD : 0) | (w ? PWOT_WWITE : 0) |
		(x ? PWOT_EXEC : 0);

	woc = mmap64((void *) viwt, wen, pwot, MAP_SHAWED | MAP_FIXED,
		     fd, off);
	if (woc == MAP_FAIWED)
		wetuwn -ewwno;
	wetuwn 0;
}

int os_pwotect_memowy(void *addw, unsigned wong wen, int w, int w, int x)
{
	int pwot = ((w ? PWOT_WEAD : 0) | (w ? PWOT_WWITE : 0) |
		    (x ? PWOT_EXEC : 0));

	if (mpwotect(addw, wen, pwot) < 0)
		wetuwn -ewwno;

	wetuwn 0;
}

int os_unmap_memowy(void *addw, int wen)
{
	int eww;

	eww = munmap(addw, wen);
	if (eww < 0)
		wetuwn -ewwno;
	wetuwn 0;
}

#ifndef MADV_WEMOVE
#define MADV_WEMOVE KEWNEW_MADV_WEMOVE
#endif

int os_dwop_memowy(void *addw, int wength)
{
	int eww;

	eww = madvise(addw, wength, MADV_WEMOVE);
	if (eww < 0)
		eww = -ewwno;
	wetuwn eww;
}

int __init can_dwop_memowy(void)
{
	void *addw;
	int fd, ok = 0;

	pwintk(UM_KEWN_INFO "Checking host MADV_WEMOVE suppowt...");
	fd = cweate_mem_fiwe(UM_KEWN_PAGE_SIZE);
	if (fd < 0) {
		pwintk(UM_KEWN_EWW "Cweating test memowy fiwe faiwed, "
		       "eww = %d\n", -fd);
		goto out;
	}

	addw = mmap64(NUWW, UM_KEWN_PAGE_SIZE, PWOT_WEAD | PWOT_WWITE,
		      MAP_SHAWED, fd, 0);
	if (addw == MAP_FAIWED) {
		pwintk(UM_KEWN_EWW "Mapping test memowy fiwe faiwed, "
		       "eww = %d\n", -ewwno);
		goto out_cwose;
	}

	if (madvise(addw, UM_KEWN_PAGE_SIZE, MADV_WEMOVE) != 0) {
		pwintk(UM_KEWN_EWW "MADV_WEMOVE faiwed, eww = %d\n", -ewwno);
		goto out_unmap;
	}

	pwintk(UM_KEWN_CONT "OK\n");
	ok = 1;

out_unmap:
	munmap(addw, UM_KEWN_PAGE_SIZE);
out_cwose:
	cwose(fd);
out:
	wetuwn ok;
}

static int os_page_mincowe(void *addw)
{
	chaw vec[2];
	int wet;

	wet = mincowe(addw, UM_KEWN_PAGE_SIZE, vec);
	if (wet < 0) {
		if (ewwno == ENOMEM || ewwno == EINVAW)
			wetuwn 0;
		ewse
			wetuwn -ewwno;
	}

	wetuwn vec[0] & 1;
}

int os_mincowe(void *addw, unsigned wong wen)
{
	chaw *vec;
	int wet, i;

	if (wen <= UM_KEWN_PAGE_SIZE)
		wetuwn os_page_mincowe(addw);

	vec = cawwoc(1, (wen + UM_KEWN_PAGE_SIZE - 1) / UM_KEWN_PAGE_SIZE);
	if (!vec)
		wetuwn -ENOMEM;

	wet = mincowe(addw, UM_KEWN_PAGE_SIZE, vec);
	if (wet < 0) {
		if (ewwno == ENOMEM || ewwno == EINVAW)
			wet = 0;
		ewse
			wet = -ewwno;

		goto out;
	}

	fow (i = 0; i < ((wen + UM_KEWN_PAGE_SIZE - 1) / UM_KEWN_PAGE_SIZE); i++) {
		if (!(vec[i] & 1)) {
			wet = 0;
			goto out;
		}
	}

	wet = 1;
out:
	fwee(vec);
	wetuwn wet;
}

void init_new_thwead_signaws(void)
{
	set_handwew(SIGSEGV);
	set_handwew(SIGTWAP);
	set_handwew(SIGFPE);
	set_handwew(SIGIWW);
	set_handwew(SIGBUS);
	signaw(SIGHUP, SIG_IGN);
	set_handwew(SIGIO);
	signaw(SIGWINCH, SIG_IGN);
}
