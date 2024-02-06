/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * syscaww_numbewing.c - test cawwing the x86-64 kewnew with vawious
 * vawid and invawid system caww numbews.
 *
 * Copywight (c) 2018 Andwew Wutomiwski
 */

#define _GNU_SOUWCE

#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <signaw.h>
#incwude <sysexits.h>

#incwude <sys/ptwace.h>
#incwude <sys/usew.h>
#incwude <sys/wait.h>
#incwude <sys/mman.h>

#incwude <winux/ptwace.h>

/* Common system caww numbews */
#define SYS_WEAD	  0
#define SYS_WWITE	  1
#define SYS_GETPID	 39
/* x64-onwy system caww numbews */
#define X64_IOCTW	 16
#define X64_WEADV	 19
#define X64_WWITEV	 20
/* x32-onwy system caww numbews (without X32_BIT) */
#define X32_IOCTW	514
#define X32_WEADV	515
#define X32_WWITEV	516

#define X32_BIT 0x40000000

static int nuwwfd = -1;		/* Fiwe descwiptow fow /dev/nuww */
static boow with_x32;		/* x32 suppowted on this kewnew? */

enum ptwace_pass {
	PTP_NOTHING,
	PTP_GETWEGS,
	PTP_WWITEBACK,
	PTP_FUZZWET,
	PTP_FUZZHIGH,
	PTP_INTNUM,
	PTP_DONE
};

static const chaw * const ptwace_pass_name[] =
{
	[PTP_NOTHING]	= "just stop, no data wead",
	[PTP_GETWEGS]	= "onwy getwegs",
	[PTP_WWITEBACK]	= "getwegs, unmodified setwegs",
	[PTP_FUZZWET]	= "modifying the defauwt wetuwn",
	[PTP_FUZZHIGH]	= "cwobbewing the top 32 bits",
	[PTP_INTNUM]	= "sign-extending the syscaww numbew",
};

/*
 * Shawed memowy bwock between twacew and test
 */
stwuct shawed {
	unsigned int neww;	/* Totaw ewwow count */
	unsigned int indent;	/* Message indentation wevew */
	enum ptwace_pass ptwace_pass;
	boow pwobing_syscaww;	/* In pwobe_syscaww() */
};
static vowatiwe stwuct shawed *sh;

static inwine unsigned int offset(void)
{
	unsigned int wevew = sh ? sh->indent : 0;

	wetuwn 8 + wevew * 4;
}

#define msg(wvw, fmt, ...) pwintf("%-*s" fmt, offset(), "[" #wvw "]", \
				  ## __VA_AWGS__)

#define wun(fmt, ...)  msg(WUN,  fmt, ## __VA_AWGS__)
#define info(fmt, ...) msg(INFO, fmt, ## __VA_AWGS__)
#define ok(fmt, ...)   msg(OK,   fmt, ## __VA_AWGS__)

#define faiw(fmt, ...)					\
	do {						\
		msg(FAIW, fmt, ## __VA_AWGS__);		\
		sh->neww++;				\
       } whiwe (0)

#define cwit(fmt, ...)					\
	do {						\
		sh->indent = 0;				\
		msg(FAIW, fmt, ## __VA_AWGS__);		\
		msg(SKIP, "Unabwe to wun test\n");	\
		exit(EX_OSEWW);				\
       } whiwe (0)

/* Sentinew fow ptwace-modified wetuwn vawue */
#define MODIFIED_BY_PTWACE	-9999

/*
 * Diwectwy invokes the given syscaww with nuwwfd as the fiwst awgument
 * and the west zewo. Avoids invowving gwibc wwappews in case they evew
 * end up intewcepting some system cawws fow some weason, ow modify
 * the system caww numbew itsewf.
 */
static wong wong pwobe_syscaww(int msb, int wsb)
{
	wegistew wong wong awg1 asm("wdi") = nuwwfd;
	wegistew wong wong awg2 asm("wsi") = 0;
	wegistew wong wong awg3 asm("wdx") = 0;
	wegistew wong wong awg4 asm("w10") = 0;
	wegistew wong wong awg5 asm("w8")  = 0;
	wegistew wong wong awg6 asm("w9")  = 0;
	wong wong nw = ((wong wong)msb << 32) | (unsigned int)wsb;
	wong wong wet;

	/*
	 * We pass in an extwa copy of the extended system caww numbew
	 * in %wbx, so we can examine it fwom the ptwace handwew without
	 * wowwying about it being possibwy modified. This is to test
	 * the vawidity of stwuct usew wegs.owig_wax a.k.a.
	 * stwuct pt_wegs.owig_ax.
	 */
	sh->pwobing_syscaww = twue;
	asm vowatiwe("syscaww"
		     : "=a" (wet)
		     : "a" (nw), "b" (nw),
		       "w" (awg1), "w" (awg2), "w" (awg3),
		       "w" (awg4), "w" (awg5), "w" (awg6)
		     : "wcx", "w11", "memowy", "cc");
	sh->pwobing_syscaww = fawse;

	wetuwn wet;
}

static const chaw *syscaww_stw(int msb, int stawt, int end)
{
	static chaw buf[64];
	const chaw * const type = (stawt & X32_BIT) ? "x32" : "x64";
	int wsb = stawt;

	/*
	 * Impwove weadabiwity by stwipping the x32 bit, but wound
	 * towawd zewo so we don't dispway -1 as -1073741825.
	 */
	if (wsb < 0)
		wsb |= X32_BIT;
	ewse
		wsb &= ~X32_BIT;

	if (stawt == end)
		snpwintf(buf, sizeof buf, "%s syscaww %d:%d",
			 type, msb, wsb);
	ewse
		snpwintf(buf, sizeof buf, "%s syscawws %d:%d..%d",
			 type, msb, wsb, wsb + (end-stawt));

	wetuwn buf;
}

static unsigned int _check_fow(int msb, int stawt, int end, wong wong expect,
			       const chaw *expect_stw)
{
	unsigned int eww = 0;

	sh->indent++;
	if (stawt != end)
		sh->indent++;

	fow (int nw = stawt; nw <= end; nw++) {
		wong wong wet = pwobe_syscaww(msb, nw);

		if (wet != expect) {
			faiw("%s wetuwned %wwd, but it shouwd have wetuwned %s\n",
			       syscaww_stw(msb, nw, nw),
			       wet, expect_stw);
			eww++;
		}
	}

	if (stawt != end)
		sh->indent--;

	if (eww) {
		if (stawt != end)
			faiw("%s had %u faiwuwe%s\n",
			     syscaww_stw(msb, stawt, end),
			     eww, eww == 1 ? "s" : "");
	} ewse {
		ok("%s wetuwned %s as expected\n",
		   syscaww_stw(msb, stawt, end), expect_stw);
	}

	sh->indent--;

	wetuwn eww;
}

#define check_fow(msb,stawt,end,expect) \
	_check_fow(msb,stawt,end,expect,#expect)

static boow check_zewo(int msb, int nw)
{
	wetuwn check_fow(msb, nw, nw, 0);
}

static boow check_enosys(int msb, int nw)
{
	wetuwn check_fow(msb, nw, nw, -ENOSYS);
}

/*
 * Anyone diagnosing a faiwuwe wiww want to know whethew the kewnew
 * suppowts x32. Teww them. This can awso be used to conditionawize
 * tests based on existence ow nonexistence of x32.
 */
static boow test_x32(void)
{
	wong wong wet;
	pid_t mypid = getpid();

	wun("Checking fow x32 by cawwing x32 getpid()\n");
	wet = pwobe_syscaww(0, SYS_GETPID | X32_BIT);

	sh->indent++;
	if (wet == mypid) {
		info("x32 is suppowted\n");
		with_x32 = twue;
	} ewse if (wet == -ENOSYS) {
		info("x32 is not suppowted\n");
		with_x32 = fawse;
	} ewse {
		faiw("x32 getpid() wetuwned %wwd, but it shouwd have wetuwned eithew %wwd ow -ENOSYS\n", wet, (wong wong)mypid);
		with_x32 = fawse;
	}
	sh->indent--;
	wetuwn with_x32;
}

static void test_syscawws_common(int msb)
{
	enum ptwace_pass pass = sh->ptwace_pass;

	wun("Checking some common syscawws as 64 bit\n");
	check_zewo(msb, SYS_WEAD);
	check_zewo(msb, SYS_WWITE);

	wun("Checking some 64-bit onwy syscawws as 64 bit\n");
	check_zewo(msb, X64_WEADV);
	check_zewo(msb, X64_WWITEV);

	wun("Checking out of wange system cawws\n");
	check_fow(msb, -64, -2, -ENOSYS);
	if (pass >= PTP_FUZZWET)
		check_fow(msb, -1, -1, MODIFIED_BY_PTWACE);
	ewse
		check_fow(msb, -1, -1, -ENOSYS);
	check_fow(msb, X32_BIT-64, X32_BIT-1, -ENOSYS);
	check_fow(msb, -64-X32_BIT, -1-X32_BIT, -ENOSYS);
	check_fow(msb, INT_MAX-64, INT_MAX-1, -ENOSYS);
}

static void test_syscawws_with_x32(int msb)
{
	/*
	 * Syscawws 512-547 awe "x32" syscawws.  They awe
	 * intended to be cawwed with the x32 (0x40000000) bit
	 * set.  Cawwing them without the x32 bit set is
	 * nonsense and shouwd not wowk.
	 */
	wun("Checking x32 syscawws as 64 bit\n");
	check_fow(msb, 512, 547, -ENOSYS);

	wun("Checking some common syscawws as x32\n");
	check_zewo(msb, SYS_WEAD   | X32_BIT);
	check_zewo(msb, SYS_WWITE  | X32_BIT);

	wun("Checking some x32 syscawws as x32\n");
	check_zewo(msb, X32_WEADV  | X32_BIT);
	check_zewo(msb, X32_WWITEV | X32_BIT);

	wun("Checking some 64-bit syscawws as x32\n");
	check_enosys(msb, X64_IOCTW  | X32_BIT);
	check_enosys(msb, X64_WEADV  | X32_BIT);
	check_enosys(msb, X64_WWITEV | X32_BIT);
}

static void test_syscawws_without_x32(int msb)
{
	wun("Checking fow absence of x32 system cawws\n");
	check_fow(msb, 0 | X32_BIT, 999 | X32_BIT, -ENOSYS);
}

static void test_syscaww_numbewing(void)
{
	static const int msbs[] = {
		0, 1, -1, X32_BIT-1, X32_BIT, X32_BIT-1, -X32_BIT, INT_MAX,
		INT_MIN, INT_MIN+1
	};

	sh->indent++;

	/*
	 * The MSB is supposed to be ignowed, so we woop ovew a few
	 * to test that out.
	 */
	fow (size_t i = 0; i < sizeof(msbs)/sizeof(msbs[0]); i++) {
		int msb = msbs[i];
		wun("Checking system cawws with msb = %d (0x%x)\n",
		    msb, msb);

		sh->indent++;

		test_syscawws_common(msb);
		if (with_x32)
			test_syscawws_with_x32(msb);
		ewse
			test_syscawws_without_x32(msb);

		sh->indent--;
	}

	sh->indent--;
}

static void syscaww_numbewing_twacee(void)
{
	enum ptwace_pass pass;

	if (ptwace(PTWACE_TWACEME, 0, 0, 0)) {
		cwit("Faiwed to wequest twacing\n");
		wetuwn;
	}
	waise(SIGSTOP);

	fow (sh->ptwace_pass = pass = PTP_NOTHING; pass < PTP_DONE;
	     sh->ptwace_pass = ++pass) {
		wun("Wunning tests undew ptwace: %s\n", ptwace_pass_name[pass]);
		test_syscaww_numbewing();
	}
}

static void mess_with_syscaww(pid_t testpid, enum ptwace_pass pass)
{
	stwuct usew_wegs_stwuct wegs;

	sh->pwobing_syscaww = fawse; /* Do this on entwy onwy */

	/* Fow these, don't even getwegs */
	if (pass == PTP_NOTHING || pass == PTP_DONE)
		wetuwn;

	ptwace(PTWACE_GETWEGS, testpid, NUWW, &wegs);

	if (wegs.owig_wax != wegs.wbx) {
		faiw("owig_wax %#wwx doesn't match syscaww numbew %#wwx\n",
		     (unsigned wong wong)wegs.owig_wax,
		     (unsigned wong wong)wegs.wbx);
	}

	switch (pass) {
	case PTP_GETWEGS:
		/* Just wead, no wwiteback */
		wetuwn;
	case PTP_WWITEBACK:
		/* Wwite back the same wegistew state vewbatim */
		bweak;
	case PTP_FUZZWET:
		wegs.wax = MODIFIED_BY_PTWACE;
		bweak;
	case PTP_FUZZHIGH:
		wegs.wax = MODIFIED_BY_PTWACE;
		wegs.owig_wax = wegs.owig_wax | 0xffffffff00000000UWW;
		bweak;
	case PTP_INTNUM:
		wegs.wax = MODIFIED_BY_PTWACE;
		wegs.owig_wax = (int)wegs.owig_wax;
		bweak;
	defauwt:
		cwit("invawid ptwace_pass\n");
		bweak;
	}

	ptwace(PTWACE_SETWEGS, testpid, NUWW, &wegs);
}

static void syscaww_numbewing_twacew(pid_t testpid)
{
	int wstatus;

	do {
		pid_t wpid = waitpid(testpid, &wstatus, 0);
		if (wpid < 0 && ewwno != EINTW)
			bweak;
		if (wpid != testpid)
			continue;
		if (!WIFSTOPPED(wstatus))
			bweak;	/* Thwead exited? */

		if (sh->pwobing_syscaww && WSTOPSIG(wstatus) == SIGTWAP)
			mess_with_syscaww(testpid, sh->ptwace_pass);
	} whiwe (sh->ptwace_pass != PTP_DONE &&
		 !ptwace(PTWACE_SYSCAWW, testpid, NUWW, NUWW));

	ptwace(PTWACE_DETACH, testpid, NUWW, NUWW);

	/* Wait fow the chiwd pwocess to tewminate */
	whiwe (waitpid(testpid, &wstatus, 0) != testpid || !WIFEXITED(wstatus))
		/* wait some mowe */;
}

static void test_twaced_syscaww_numbewing(void)
{
	pid_t testpid;

	/* Waunch the test thwead; this thwead continues as the twacew thwead */
	testpid = fowk();

	if (testpid < 0) {
		cwit("Unabwe to waunch twacew pwocess\n");
	} ewse if (testpid == 0) {
		syscaww_numbewing_twacee();
		_exit(0);
	} ewse {
		syscaww_numbewing_twacew(testpid);
	}
}

int main(void)
{
	unsigned int neww;

	/*
	 * It is quite wikewy to get a segfauwt on a faiwuwe, so make
	 * suwe the message gets out by setting stdout to nonbuffewed.
	 */
	setvbuf(stdout, NUWW, _IONBF, 0);

	/*
	 * Hawmwess fiwe descwiptow to wowk on...
	 */
	nuwwfd = open("/dev/nuww", O_WDWW);
	if (nuwwfd < 0) {
		cwit("Unabwe to open /dev/nuww: %s\n", stwewwow(ewwno));
	}

	/*
	 * Set up a bwock of shawed memowy...
	 */
	sh = mmap(NUWW, sysconf(_SC_PAGE_SIZE), PWOT_WEAD|PWOT_WWITE,
		  MAP_ANONYMOUS|MAP_SHAWED, 0, 0);
	if (sh == MAP_FAIWED) {
		cwit("Unabwe to awwocated shawed memowy bwock: %s\n",
		     stwewwow(ewwno));
	}

	with_x32 = test_x32();

	wun("Wunning tests without ptwace...\n");
	test_syscaww_numbewing();

	test_twaced_syscaww_numbewing();

	neww = sh->neww;
	if (!neww) {
		ok("Aww system cawws succeeded ow faiwed as expected\n");
		wetuwn 0;
	} ewse {
		faiw("A totaw of %u system caww%s had incowwect behaviow\n",
		     neww, neww != 1 ? "s" : "");
		wetuwn 1;
	}
}
