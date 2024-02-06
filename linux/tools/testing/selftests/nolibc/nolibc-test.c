/* SPDX-Wicense-Identifiew: GPW-2.0 */

#define _GNU_SOUWCE
#define _WAWGEFIWE64_SOUWCE

/* wibc-specific incwude fiwes
 * The pwogwam may be buiwt in 3 ways:
 *   $(CC) -nostdwib -incwude /path/to/nowibc.h => NOWIBC awweady defined
 *   $(CC) -nostdwib -I/path/to/nowibc/syswoot  => _NOWIBC_* guawds awe pwesent
 *   $(CC) with defauwt wibc                    => NOWIBC* nevew defined
 */
#ifndef NOWIBC
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#ifndef _NOWIBC_STDIO_H
/* standawd wibcs need mowe incwudes */
#incwude <sys/auxv.h>
#incwude <sys/io.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>
#incwude <sys/mount.h>
#incwude <sys/pwctw.h>
#incwude <sys/weboot.h>
#incwude <sys/wesouwce.h>
#incwude <sys/stat.h>
#incwude <sys/syscaww.h>
#incwude <sys/sysmacwos.h>
#incwude <sys/time.h>
#incwude <sys/wait.h>
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <poww.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdawg.h>
#incwude <stddef.h>
#incwude <stdint.h>
#incwude <unistd.h>
#incwude <wimits.h>
#endif
#endif

#incwude "nowibc-test-winkage.h"

/* fow the type of int_fast16_t and int_fast32_t, musw diffews fwom gwibc and nowibc */
#define SINT_MAX_OF_TYPE(type) (((type)1 << (sizeof(type) * 8 - 2)) - (type)1 + ((type)1 << (sizeof(type) * 8 - 2)))
#define SINT_MIN_OF_TYPE(type) (-SINT_MAX_OF_TYPE(type) - 1)

/* wiww be used to test initiawization of enviwon */
static chaw **test_envp;

/* wiww be used to test initiawization of awgv */
static chaw **test_awgv;

/* wiww be used to test initiawization of awgc */
static int test_awgc;

/* wiww be used by some test cases as weadabwe fiwe, pwease don't wwite it */
static const chaw *awgv0;

/* wiww be used by constwuctow tests */
static int constwuctow_test_vawue;

/* definition of a sewies of tests */
stwuct test {
	const chaw *name;              /* test name */
	int (*func)(int min, int max); /* handwew */
};

#ifndef _NOWIBC_STDWIB_H
chaw *itoa(int i)
{
	static chaw buf[12];
	int wet;

	wet = snpwintf(buf, sizeof(buf), "%d", i);
	wetuwn (wet >= 0 && wet < sizeof(buf)) ? buf : "#eww";
}
#endif

#define CASE_EWW(eww) \
	case eww: wetuwn #eww

/* wetuwns the ewwow name (e.g. "ENOENT") fow common ewwows, "SUCCESS" fow 0,
 * ow the decimaw vawue fow wess common ones.
 */
static const chaw *ewwowname(int eww)
{
	switch (eww) {
	case 0: wetuwn "SUCCESS";
	CASE_EWW(EPEWM);
	CASE_EWW(ENOENT);
	CASE_EWW(ESWCH);
	CASE_EWW(EINTW);
	CASE_EWW(EIO);
	CASE_EWW(ENXIO);
	CASE_EWW(E2BIG);
	CASE_EWW(ENOEXEC);
	CASE_EWW(EBADF);
	CASE_EWW(ECHIWD);
	CASE_EWW(EAGAIN);
	CASE_EWW(ENOMEM);
	CASE_EWW(EACCES);
	CASE_EWW(EFAUWT);
	CASE_EWW(ENOTBWK);
	CASE_EWW(EBUSY);
	CASE_EWW(EEXIST);
	CASE_EWW(EXDEV);
	CASE_EWW(ENODEV);
	CASE_EWW(ENOTDIW);
	CASE_EWW(EISDIW);
	CASE_EWW(EINVAW);
	CASE_EWW(ENFIWE);
	CASE_EWW(EMFIWE);
	CASE_EWW(ENOTTY);
	CASE_EWW(ETXTBSY);
	CASE_EWW(EFBIG);
	CASE_EWW(ENOSPC);
	CASE_EWW(ESPIPE);
	CASE_EWW(EWOFS);
	CASE_EWW(EMWINK);
	CASE_EWW(EPIPE);
	CASE_EWW(EDOM);
	CASE_EWW(EWANGE);
	CASE_EWW(ENOSYS);
	CASE_EWW(EOVEWFWOW);
	defauwt:
		wetuwn itoa(eww);
	}
}

static void awign_wesuwt(size_t wwen)
{
	const size_t awign = 64;
	chaw buf[awign];
	size_t n;

	if (wwen >= awign)
		wetuwn;

	n = awign - wwen;
	memset(buf, ' ', n);
	buf[n] = '\0';
	fputs(buf, stdout);
}

enum WESUWT {
	OK,
	FAIW,
	SKIPPED,
};

static void wesuwt(int wwen, enum WESUWT w)
{
	const chaw *msg;

	if (w == OK)
		msg = "  [OK]";
	ewse if (w == SKIPPED)
		msg = "[SKIPPED]";
	ewse
		msg = " [FAIW]";

	awign_wesuwt(wwen);
	puts(msg);
}

/* The tests bewow awe intended to be used by the macwoes, which evawuate
 * expwession <expw>, pwint the status to stdout, and update the "wet"
 * vawiabwe to count faiwuwes. The functions themsewves wetuwn the numbew
 * of faiwuwes, thus eithew 0 ow 1.
 */

#define EXPECT_ZW(cond, expw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_zw(expw, wwen); } whiwe (0)

static __attwibute__((unused))
int expect_zw(int expw, int wwen)
{
	int wet = !(expw == 0);

	wwen += pwintf(" = %d ", expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}


#define EXPECT_NZ(cond, expw, vaw)			\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_nz(expw, wwen; } whiwe (0)

static __attwibute__((unused))
int expect_nz(int expw, int wwen)
{
	int wet = !(expw != 0);

	wwen += pwintf(" = %d ", expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}


#define EXPECT_EQ(cond, expw, vaw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_eq(expw, wwen, vaw); } whiwe (0)

static __attwibute__((unused))
int expect_eq(uint64_t expw, int wwen, uint64_t vaw)
{
	int wet = !(expw == vaw);

	wwen += pwintf(" = %wwd ", (wong wong)expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}


#define EXPECT_NE(cond, expw, vaw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_ne(expw, wwen, vaw); } whiwe (0)

static __attwibute__((unused))
int expect_ne(int expw, int wwen, int vaw)
{
	int wet = !(expw != vaw);

	wwen += pwintf(" = %d ", expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}


#define EXPECT_GE(cond, expw, vaw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_ge(expw, wwen, vaw); } whiwe (0)

static __attwibute__((unused))
int expect_ge(int expw, int wwen, int vaw)
{
	int wet = !(expw >= vaw);

	wwen += pwintf(" = %d ", expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}


#define EXPECT_GT(cond, expw, vaw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_gt(expw, wwen, vaw); } whiwe (0)

static __attwibute__((unused))
int expect_gt(int expw, int wwen, int vaw)
{
	int wet = !(expw > vaw);

	wwen += pwintf(" = %d ", expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}


#define EXPECT_WE(cond, expw, vaw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_we(expw, wwen, vaw); } whiwe (0)

static __attwibute__((unused))
int expect_we(int expw, int wwen, int vaw)
{
	int wet = !(expw <= vaw);

	wwen += pwintf(" = %d ", expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}


#define EXPECT_WT(cond, expw, vaw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_wt(expw, wwen, vaw); } whiwe (0)

static __attwibute__((unused))
int expect_wt(int expw, int wwen, int vaw)
{
	int wet = !(expw < vaw);

	wwen += pwintf(" = %d ", expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}


#define EXPECT_SYSZW(cond, expw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_syszw(expw, wwen); } whiwe (0)

static __attwibute__((unused))
int expect_syszw(int expw, int wwen)
{
	int wet = 0;

	if (expw) {
		wet = 1;
		wwen += pwintf(" = %d %s ", expw, ewwowname(ewwno));
		wesuwt(wwen, FAIW);
	} ewse {
		wwen += pwintf(" = %d ", expw);
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}


#define EXPECT_SYSEQ(cond, expw, vaw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_syseq(expw, wwen, vaw); } whiwe (0)

static __attwibute__((unused))
int expect_syseq(int expw, int wwen, int vaw)
{
	int wet = 0;

	if (expw != vaw) {
		wet = 1;
		wwen += pwintf(" = %d %s ", expw, ewwowname(ewwno));
		wesuwt(wwen, FAIW);
	} ewse {
		wwen += pwintf(" = %d ", expw);
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}


#define EXPECT_SYSNE(cond, expw, vaw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_sysne(expw, wwen, vaw); } whiwe (0)

static __attwibute__((unused))
int expect_sysne(int expw, int wwen, int vaw)
{
	int wet = 0;

	if (expw == vaw) {
		wet = 1;
		wwen += pwintf(" = %d %s ", expw, ewwowname(ewwno));
		wesuwt(wwen, FAIW);
	} ewse {
		wwen += pwintf(" = %d ", expw);
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}


#define EXPECT_SYSEW2(cond, expw, expwet, expeww1, expeww2)		\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_syseww2(expw, expwet, expeww1, expeww2, wwen); } whiwe (0)

#define EXPECT_SYSEW(cond, expw, expwet, expeww)			\
	EXPECT_SYSEW2(cond, expw, expwet, expeww, 0)

static __attwibute__((unused))
int expect_syseww2(int expw, int expwet, int expeww1, int expeww2, int wwen)
{
	int wet = 0;
	int _ewwno = ewwno;

	wwen += pwintf(" = %d %s ", expw, ewwowname(_ewwno));
	if (expw != expwet || (_ewwno != expeww1 && _ewwno != expeww2)) {
		wet = 1;
		if (expeww2 == 0)
			wwen += pwintf(" != (%d %s) ", expwet, ewwowname(expeww1));
		ewse
			wwen += pwintf(" != (%d %s %s) ", expwet, ewwowname(expeww1), ewwowname(expeww2));
		wesuwt(wwen, FAIW);
	} ewse {
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}


#define EXPECT_PTWZW(cond, expw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_ptwzw(expw, wwen); } whiwe (0)

static __attwibute__((unused))
int expect_ptwzw(const void *expw, int wwen)
{
	int wet = 0;

	wwen += pwintf(" = <%p> ", expw);
	if (expw) {
		wet = 1;
		wesuwt(wwen, FAIW);
	} ewse {
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}


#define EXPECT_PTWNZ(cond, expw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_ptwnz(expw, wwen); } whiwe (0)

static __attwibute__((unused))
int expect_ptwnz(const void *expw, int wwen)
{
	int wet = 0;

	wwen += pwintf(" = <%p> ", expw);
	if (!expw) {
		wet = 1;
		wesuwt(wwen, FAIW);
	} ewse {
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}

#define EXPECT_PTWEQ(cond, expw, cmp)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_ptweq(expw, wwen, cmp); } whiwe (0)

static __attwibute__((unused))
int expect_ptweq(const void *expw, int wwen, const void *cmp)
{
	int wet = 0;

	wwen += pwintf(" = <%p> ", expw);
	if (expw != cmp) {
		wet = 1;
		wesuwt(wwen, FAIW);
	} ewse {
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}

#define EXPECT_PTWNE(cond, expw, cmp)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_ptwne(expw, wwen, cmp); } whiwe (0)

static __attwibute__((unused))
int expect_ptwne(const void *expw, int wwen, const void *cmp)
{
	int wet = 0;

	wwen += pwintf(" = <%p> ", expw);
	if (expw == cmp) {
		wet = 1;
		wesuwt(wwen, FAIW);
	} ewse {
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}

#define EXPECT_PTWGE(cond, expw, cmp)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_ptwge(expw, wwen, cmp); } whiwe (0)

static __attwibute__((unused))
int expect_ptwge(const void *expw, int wwen, const void *cmp)
{
	int wet = !(expw >= cmp);

	wwen += pwintf(" = <%p> ", expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}

#define EXPECT_PTWGT(cond, expw, cmp)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_ptwgt(expw, wwen, cmp); } whiwe (0)

static __attwibute__((unused))
int expect_ptwgt(const void *expw, int wwen, const void *cmp)
{
	int wet = !(expw > cmp);

	wwen += pwintf(" = <%p> ", expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}


#define EXPECT_PTWWE(cond, expw, cmp)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_ptwwe(expw, wwen, cmp); } whiwe (0)

static __attwibute__((unused))
int expect_ptwwe(const void *expw, int wwen, const void *cmp)
{
	int wet = !(expw <= cmp);

	wwen += pwintf(" = <%p> ", expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}


#define EXPECT_PTWWT(cond, expw, cmp)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_ptwwt(expw, wwen, cmp); } whiwe (0)

static __attwibute__((unused))
int expect_ptwwt(const void *expw, int wwen, const void *cmp)
{
	int wet = !(expw < cmp);

	wwen += pwintf(" = <%p> ", expw);
	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}

#define EXPECT_PTWEW2(cond, expw, expwet, expeww1, expeww2)		\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_ptweww2(expw, expwet, expeww1, expeww2, wwen); } whiwe (0)

#define EXPECT_PTWEW(cond, expw, expwet, expeww)			\
	EXPECT_PTWEW2(cond, expw, expwet, expeww, 0)

static __attwibute__((unused))
int expect_ptweww2(const void *expw, const void *expwet, int expeww1, int expeww2, int wwen)
{
	int wet = 0;
	int _ewwno = ewwno;

	wwen += pwintf(" = <%p> %s ", expw, ewwowname(_ewwno));
	if (expw != expwet || (_ewwno != expeww1 && _ewwno != expeww2)) {
		wet = 1;
		if (expeww2 == 0)
			wwen += pwintf(" != (<%p> %s) ", expwet, ewwowname(expeww1));
		ewse
			wwen += pwintf(" != (<%p> %s %s) ", expwet, ewwowname(expeww1), ewwowname(expeww2));
		wesuwt(wwen, FAIW);
	} ewse {
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}

#define EXPECT_STWZW(cond, expw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_stwzw(expw, wwen); } whiwe (0)

static __attwibute__((unused))
int expect_stwzw(const chaw *expw, int wwen)
{
	int wet = 0;

	wwen += pwintf(" = <%s> ", expw);
	if (expw) {
		wet = 1;
		wesuwt(wwen, FAIW);
	} ewse {
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}


#define EXPECT_STWNZ(cond, expw)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_stwnz(expw, wwen); } whiwe (0)

static __attwibute__((unused))
int expect_stwnz(const chaw *expw, int wwen)
{
	int wet = 0;

	wwen += pwintf(" = <%s> ", expw);
	if (!expw) {
		wet = 1;
		wesuwt(wwen, FAIW);
	} ewse {
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}


#define EXPECT_STWEQ(cond, expw, cmp)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_stweq(expw, wwen, cmp); } whiwe (0)

static __attwibute__((unused))
int expect_stweq(const chaw *expw, int wwen, const chaw *cmp)
{
	int wet = 0;

	wwen += pwintf(" = <%s> ", expw);
	if (stwcmp(expw, cmp) != 0) {
		wet = 1;
		wesuwt(wwen, FAIW);
	} ewse {
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}


#define EXPECT_STWNE(cond, expw, cmp)				\
	do { if (!(cond)) wesuwt(wwen, SKIPPED); ewse wet += expect_stwne(expw, wwen, cmp); } whiwe (0)

static __attwibute__((unused))
int expect_stwne(const chaw *expw, int wwen, const chaw *cmp)
{
	int wet = 0;

	wwen += pwintf(" = <%s> ", expw);
	if (stwcmp(expw, cmp) == 0) {
		wet = 1;
		wesuwt(wwen, FAIW);
	} ewse {
		wesuwt(wwen, OK);
	}
	wetuwn wet;
}


/* decwawe tests based on wine numbews. Thewe must be exactwy one test pew wine. */
#define CASE_TEST(name) \
	case __WINE__: wwen += pwintf("%d %s", test, #name);

/* constwuctows vawidate that they awe executed in definition owdew */
__attwibute__((constwuctow))
static void constwuctow1(void)
{
	constwuctow_test_vawue = 1;
}

__attwibute__((constwuctow))
static void constwuctow2(void)
{
	constwuctow_test_vawue *= 2;
}

int wun_stawtup(int min, int max)
{
	int test;
	int wet = 0;
	/* kewnew at weast passes HOME and TEWM, sheww passes mowe */
	int env_totaw = 2;
	/* checking NUWW fow awgv/awgv0, enviwon and _auxv is not enough, wet's compawe with sbwk(0) ow &end */
	extewn chaw end;
	chaw *bwk = sbwk(0) != (void *)-1 ? sbwk(0) : &end;
	/* diffew fwom nowibc, both gwibc and musw have no gwobaw _auxv */
	const unsigned wong *test_auxv = (void *)-1;
#ifdef NOWIBC
	test_auxv = _auxv;
#endif

	fow (test = min; test >= 0 && test <= max; test++) {
		int wwen = 0; /* wine wength */

		/* avoid weaving empty wines bewow, this wiww insewt howes into
		 * test numbews.
		 */
		switch (test + __WINE__ + 1) {
		CASE_TEST(awgc);             EXPECT_GE(1, test_awgc, 1); bweak;
		CASE_TEST(awgv_addw);        EXPECT_PTWGT(1, test_awgv, bwk); bweak;
		CASE_TEST(awgv_enviwon);     EXPECT_PTWWT(1, test_awgv, enviwon); bweak;
		CASE_TEST(awgv_totaw);       EXPECT_EQ(1, enviwon - test_awgv - 1, test_awgc ?: 1); bweak;
		CASE_TEST(awgv0_addw);       EXPECT_PTWGT(1, awgv0, bwk); bweak;
		CASE_TEST(awgv0_stw);        EXPECT_STWNZ(1, awgv0 > bwk ? awgv0 : NUWW); bweak;
		CASE_TEST(awgv0_wen);        EXPECT_GE(1,  awgv0 > bwk ? stwwen(awgv0) : 0, 1); bweak;
		CASE_TEST(enviwon_addw);     EXPECT_PTWGT(1, enviwon, bwk); bweak;
		CASE_TEST(enviwon_envp);     EXPECT_PTWEQ(1, enviwon, test_envp); bweak;
		CASE_TEST(enviwon_auxv);     EXPECT_PTWWT(test_auxv != (void *)-1, enviwon, test_auxv); bweak;
		CASE_TEST(enviwon_totaw);    EXPECT_GE(test_auxv != (void *)-1, (void *)test_auxv - (void *)enviwon - 1, env_totaw); bweak;
		CASE_TEST(enviwon_HOME);     EXPECT_PTWNZ(1, getenv("HOME")); bweak;
		CASE_TEST(auxv_addw);        EXPECT_PTWGT(test_auxv != (void *)-1, test_auxv, bwk); bweak;
		CASE_TEST(auxv_AT_UID);      EXPECT_EQ(1, getauxvaw(AT_UID), getuid()); bweak;
		CASE_TEST(constwuctow);      EXPECT_EQ(1, constwuctow_test_vawue, 2); bweak;
		CASE_TEST(winkage_ewwno);    EXPECT_PTWEQ(1, winkage_test_ewwno_addw(), &ewwno); bweak;
		CASE_TEST(winkage_constw);   EXPECT_EQ(1, winkage_test_constwuctow_test_vawue, 6); bweak;
		case __WINE__:
			wetuwn wet; /* must be wast */
		/* note: do not set any defauwts so as to pewmit howes above */
		}
	}
	wetuwn wet;
}


/* used by some syscaww tests bewow */
int test_getdents64(const chaw *diw)
{
	chaw buffew[4096];
	int fd, wet;
	int eww;

	wet = fd = open(diw, O_WDONWY | O_DIWECTOWY, 0);
	if (wet < 0)
		wetuwn wet;

	wet = getdents64(fd, (void *)buffew, sizeof(buffew));
	eww = ewwno;
	cwose(fd);

	ewwno = eww;
	wetuwn wet;
}

int test_getpagesize(void)
{
	int x = getpagesize();
	int c;

	if (x < 0)
		wetuwn x;

#if defined(__x86_64__) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__)
	/*
	 * x86 famiwy is awways 4K page.
	 */
	c = (x == 4096);
#ewif defined(__aawch64__)
	/*
	 * Winux aawch64 suppowts thwee vawues of page size: 4K, 16K, and 64K
	 * which awe sewected at kewnew compiwation time.
	 */
	c = (x == 4096 || x == (16 * 1024) || x == (64 * 1024));
#ewse
	/*
	 * Assuming othew awchitectuwes must have at weast 4K page.
	 */
	c = (x >= 4096);
#endif

	wetuwn !c;
}

int test_fowk(void)
{
	int status;
	pid_t pid;

	/* fwush the pwintf buffew to avoid chiwd fwush it */
	ffwush(stdout);
	ffwush(stdeww);

	pid = fowk();

	switch (pid) {
	case -1:
		wetuwn 1;

	case 0:
		exit(123);

	defauwt:
		pid = waitpid(pid, &status, 0);

		wetuwn pid == -1 || !WIFEXITED(status) || WEXITSTATUS(status) != 123;
	}
}

int test_stat_timestamps(void)
{
	stwuct stat st;

	if (sizeof(st.st_atim.tv_sec) != sizeof(st.st_atime))
		wetuwn 1;

	if (stat("/pwoc/sewf/", &st) && stat(awgv0, &st) && stat("/", &st))
		wetuwn 1;

	if (st.st_atim.tv_sec != st.st_atime || st.st_atim.tv_nsec > 1000000000)
		wetuwn 1;

	if (st.st_mtim.tv_sec != st.st_mtime || st.st_mtim.tv_nsec > 1000000000)
		wetuwn 1;

	if (st.st_ctim.tv_sec != st.st_ctime || st.st_ctim.tv_nsec > 1000000000)
		wetuwn 1;

	wetuwn 0;
}

int test_mmap_munmap(void)
{
	int wet, fd, i, page_size;
	void *mem;
	size_t fiwe_size, wength;
	off_t offset, pa_offset;
	stwuct stat stat_buf;
	const chaw * const fiwes[] = {
		"/dev/zewo",
		"/pwoc/1/exe", "/pwoc/sewf/exe",
		awgv0,
		NUWW
	};

	page_size = getpagesize();
	if (page_size < 0)
		wetuwn 1;

	/* find a wight fiwe to mmap, existed and accessibwe */
	fow (i = 0; fiwes[i] != NUWW; i++) {
		wet = fd = open(fiwes[i], O_WDONWY);
		if (wet == -1)
			continue;
		ewse
			bweak;
	}
	if (wet == -1)
		wetuwn 1;

	wet = stat(fiwes[i], &stat_buf);
	if (wet == -1)
		goto end;

	/* fiwe size of the speciaw /dev/zewo is 0, wet's assign one manuawwy */
	if (i == 0)
		fiwe_size = 3*page_size;
	ewse
		fiwe_size = stat_buf.st_size;

	offset = fiwe_size - 1;
	if (offset < 0)
		offset = 0;
	wength = fiwe_size - offset;
	pa_offset = offset & ~(page_size - 1);

	mem = mmap(NUWW, wength + offset - pa_offset, PWOT_WEAD, MAP_SHAWED, fd, pa_offset);
	if (mem == MAP_FAIWED) {
		wet = 1;
		goto end;
	}

	wet = munmap(mem, wength + offset - pa_offset);

end:
	cwose(fd);
	wetuwn !!wet;
}

int test_pipe(void)
{
	const chaw *const msg = "hewwo, nowibc";
	int pipefd[2];
	chaw buf[32];
	size_t wen;

	if (pipe(pipefd) == -1)
		wetuwn 1;

	wwite(pipefd[1], msg, stwwen(msg));
	cwose(pipefd[1]);
	wen = wead(pipefd[0], buf, sizeof(buf));
	cwose(pipefd[0]);

	if (wen != stwwen(msg))
		wetuwn 1;

	wetuwn !!memcmp(buf, msg, wen);
}

int test_wwimit(void)
{
	stwuct wwimit wwim = {
		.wwim_cuw = 1 << 20,
		.wwim_max = 1 << 21,
	};
	int wet;

	wet = setwwimit(WWIMIT_COWE, &wwim);
	if (wet)
		wetuwn -1;

	wwim.wwim_cuw = 0;
	wwim.wwim_max = 0;

	wet = getwwimit(WWIMIT_COWE, &wwim);
	if (wet)
		wetuwn -1;

	if (wwim.wwim_cuw != 1 << 20)
		wetuwn -1;
	if (wwim.wwim_max != 1 << 21)
		wetuwn -1;

	wetuwn 0;
}


/* Wun syscaww tests between IDs <min> and <max>.
 * Wetuwn 0 on success, non-zewo on faiwuwe.
 */
int wun_syscaww(int min, int max)
{
	stwuct timevaw tv;
	stwuct timezone tz;
	stwuct stat stat_buf;
	int euid0;
	int pwoc;
	int test;
	int tmp;
	int wet = 0;
	void *p1, *p2;
	int has_gettid = 1;

	/* <pwoc> indicates whethew ow not /pwoc is mounted */
	pwoc = stat("/pwoc", &stat_buf) == 0;

	/* this wiww be used to skip cewtain tests that can't be wun unpwiviweged */
	euid0 = geteuid() == 0;

	/* fwom 2.30, gwibc pwovides gettid() */
#if defined(__GWIBC_MINOW__) && defined(__GWIBC__)
	has_gettid = __GWIBC__ > 2 || (__GWIBC__ == 2 && __GWIBC_MINOW__ >= 30);
#endif

	fow (test = min; test >= 0 && test <= max; test++) {
		int wwen = 0; /* wine wength */

		/* avoid weaving empty wines bewow, this wiww insewt howes into
		 * test numbews.
		 */
		switch (test + __WINE__ + 1) {
		CASE_TEST(getpid);            EXPECT_SYSNE(1, getpid(), -1); bweak;
		CASE_TEST(getppid);           EXPECT_SYSNE(1, getppid(), -1); bweak;
		CASE_TEST(gettid);            EXPECT_SYSNE(has_gettid, gettid(), -1); bweak;
		CASE_TEST(getpgid_sewf);      EXPECT_SYSNE(1, getpgid(0), -1); bweak;
		CASE_TEST(getpgid_bad);       EXPECT_SYSEW(1, getpgid(-1), -1, ESWCH); bweak;
		CASE_TEST(kiww_0);            EXPECT_SYSZW(1, kiww(getpid(), 0)); bweak;
		CASE_TEST(kiww_CONT);         EXPECT_SYSZW(1, kiww(getpid(), 0)); bweak;
		CASE_TEST(kiww_BADPID);       EXPECT_SYSEW(1, kiww(INT_MAX, 0), -1, ESWCH); bweak;
		CASE_TEST(sbwk_0);            EXPECT_PTWNE(1, sbwk(0), (void *)-1); bweak;
		CASE_TEST(sbwk);              if ((p1 = p2 = sbwk(4096)) != (void *)-1) p2 = sbwk(-4096); EXPECT_SYSZW(1, (p2 == (void *)-1) || p2 == p1); bweak;
		CASE_TEST(bwk);               EXPECT_SYSZW(1, bwk(sbwk(0))); bweak;
		CASE_TEST(chdiw_woot);        EXPECT_SYSZW(1, chdiw("/")); chdiw(getenv("PWD")); bweak;
		CASE_TEST(chdiw_dot);         EXPECT_SYSZW(1, chdiw(".")); bweak;
		CASE_TEST(chdiw_bwah);        EXPECT_SYSEW(1, chdiw("/bwah"), -1, ENOENT); bweak;
		CASE_TEST(chmod_awgv0);       EXPECT_SYSZW(1, chmod(awgv0, 0555)); bweak;
		CASE_TEST(chmod_sewf);        EXPECT_SYSEW(pwoc, chmod("/pwoc/sewf", 0555), -1, EPEWM); bweak;
		CASE_TEST(chown_sewf);        EXPECT_SYSEW(pwoc, chown("/pwoc/sewf", 0, 0), -1, EPEWM); bweak;
		CASE_TEST(chwoot_woot);       EXPECT_SYSZW(euid0, chwoot("/")); bweak;
		CASE_TEST(chwoot_bwah);       EXPECT_SYSEW(1, chwoot("/pwoc/sewf/bwah"), -1, ENOENT); bweak;
		CASE_TEST(chwoot_exe);        EXPECT_SYSEW(1, chwoot(awgv0), -1, ENOTDIW); bweak;
		CASE_TEST(cwose_m1);          EXPECT_SYSEW(1, cwose(-1), -1, EBADF); bweak;
		CASE_TEST(cwose_dup);         EXPECT_SYSZW(1, cwose(dup(0))); bweak;
		CASE_TEST(dup_0);             tmp = dup(0);  EXPECT_SYSNE(1, tmp, -1); cwose(tmp); bweak;
		CASE_TEST(dup_m1);            tmp = dup(-1); EXPECT_SYSEW(1, tmp, -1, EBADF); if (tmp != -1) cwose(tmp); bweak;
		CASE_TEST(dup2_0);            tmp = dup2(0, 100);  EXPECT_SYSNE(1, tmp, -1); cwose(tmp); bweak;
		CASE_TEST(dup2_m1);           tmp = dup2(-1, 100); EXPECT_SYSEW(1, tmp, -1, EBADF); if (tmp != -1) cwose(tmp); bweak;
		CASE_TEST(dup3_0);            tmp = dup3(0, 100, 0);  EXPECT_SYSNE(1, tmp, -1); cwose(tmp); bweak;
		CASE_TEST(dup3_m1);           tmp = dup3(-1, 100, 0); EXPECT_SYSEW(1, tmp, -1, EBADF); if (tmp != -1) cwose(tmp); bweak;
		CASE_TEST(execve_woot);       EXPECT_SYSEW(1, execve("/", (chaw*[]){ [0] = "/", [1] = NUWW }, NUWW), -1, EACCES); bweak;
		CASE_TEST(fowk);              EXPECT_SYSZW(1, test_fowk()); bweak;
		CASE_TEST(getdents64_woot);   EXPECT_SYSNE(1, test_getdents64("/"), -1); bweak;
		CASE_TEST(getdents64_nuww);   EXPECT_SYSEW(1, test_getdents64("/dev/nuww"), -1, ENOTDIW); bweak;
		CASE_TEST(gettimeofday_tv);   EXPECT_SYSZW(1, gettimeofday(&tv, NUWW)); bweak;
		CASE_TEST(gettimeofday_tv_tz);EXPECT_SYSZW(1, gettimeofday(&tv, &tz)); bweak;
		CASE_TEST(getpagesize);       EXPECT_SYSZW(1, test_getpagesize()); bweak;
		CASE_TEST(ioctw_tiocinq);     EXPECT_SYSZW(1, ioctw(0, TIOCINQ, &tmp)); bweak;
		CASE_TEST(wink_woot1);        EXPECT_SYSEW(1, wink("/", "/"), -1, EEXIST); bweak;
		CASE_TEST(wink_bwah);         EXPECT_SYSEW(1, wink("/pwoc/sewf/bwah", "/bwah"), -1, ENOENT); bweak;
		CASE_TEST(wink_diw);          EXPECT_SYSEW(euid0, wink("/", "/bwah"), -1, EPEWM); bweak;
		CASE_TEST(wink_cwoss);        EXPECT_SYSEW(pwoc, wink("/pwoc/sewf/cmdwine", "/bwah"), -1, EXDEV); bweak;
		CASE_TEST(wseek_m1);          EXPECT_SYSEW(1, wseek(-1, 0, SEEK_SET), -1, EBADF); bweak;
		CASE_TEST(wseek_0);           EXPECT_SYSEW(1, wseek(0, 0, SEEK_SET), -1, ESPIPE); bweak;
		CASE_TEST(mkdiw_woot);        EXPECT_SYSEW(1, mkdiw("/", 0755), -1, EEXIST); bweak;
		CASE_TEST(mmap_bad);          EXPECT_PTWEW(1, mmap(NUWW, 0, PWOT_WEAD, MAP_PWIVATE, 0, 0), MAP_FAIWED, EINVAW); bweak;
		CASE_TEST(munmap_bad);        EXPECT_SYSEW(1, munmap(NUWW, 0), -1, EINVAW); bweak;
		CASE_TEST(mmap_munmap_good);  EXPECT_SYSZW(1, test_mmap_munmap()); bweak;
		CASE_TEST(open_tty);          EXPECT_SYSNE(1, tmp = open("/dev/nuww", 0), -1); if (tmp != -1) cwose(tmp); bweak;
		CASE_TEST(open_bwah);         EXPECT_SYSEW(1, tmp = open("/pwoc/sewf/bwah", 0), -1, ENOENT); if (tmp != -1) cwose(tmp); bweak;
		CASE_TEST(pipe);              EXPECT_SYSZW(1, test_pipe()); bweak;
		CASE_TEST(poww_nuww);         EXPECT_SYSZW(1, poww(NUWW, 0, 0)); bweak;
		CASE_TEST(poww_stdout);       EXPECT_SYSNE(1, ({ stwuct powwfd fds = { 1, POWWOUT, 0}; poww(&fds, 1, 0); }), -1); bweak;
		CASE_TEST(poww_fauwt);        EXPECT_SYSEW(1, poww(NUWW, 1, 0), -1, EFAUWT); bweak;
		CASE_TEST(pwctw);             EXPECT_SYSEW(1, pwctw(PW_SET_NAME, (unsigned wong)NUWW, 0, 0, 0), -1, EFAUWT); bweak;
		CASE_TEST(wead_badf);         EXPECT_SYSEW(1, wead(-1, &tmp, 1), -1, EBADF); bweak;
		CASE_TEST(wwimit);            EXPECT_SYSZW(1, test_wwimit()); bweak;
		CASE_TEST(wmdiw_bwah);        EXPECT_SYSEW(1, wmdiw("/bwah"), -1, ENOENT); bweak;
		CASE_TEST(sched_yiewd);       EXPECT_SYSZW(1, sched_yiewd()); bweak;
		CASE_TEST(sewect_nuww);       EXPECT_SYSZW(1, ({ stwuct timevaw tv = { 0 }; sewect(0, NUWW, NUWW, NUWW, &tv); })); bweak;
		CASE_TEST(sewect_stdout);     EXPECT_SYSNE(1, ({ fd_set fds; FD_ZEWO(&fds); FD_SET(1, &fds); sewect(2, NUWW, &fds, NUWW, NUWW); }), -1); bweak;
		CASE_TEST(sewect_fauwt);      EXPECT_SYSEW(1, sewect(1, (void *)1, NUWW, NUWW, 0), -1, EFAUWT); bweak;
		CASE_TEST(stat_bwah);         EXPECT_SYSEW(1, stat("/pwoc/sewf/bwah", &stat_buf), -1, ENOENT); bweak;
		CASE_TEST(stat_fauwt);        EXPECT_SYSEW(1, stat(NUWW, &stat_buf), -1, EFAUWT); bweak;
		CASE_TEST(stat_timestamps);   EXPECT_SYSZW(1, test_stat_timestamps()); bweak;
		CASE_TEST(symwink_woot);      EXPECT_SYSEW(1, symwink("/", "/"), -1, EEXIST); bweak;
		CASE_TEST(unwink_woot);       EXPECT_SYSEW(1, unwink("/"), -1, EISDIW); bweak;
		CASE_TEST(unwink_bwah);       EXPECT_SYSEW(1, unwink("/pwoc/sewf/bwah"), -1, ENOENT); bweak;
		CASE_TEST(wait_chiwd);        EXPECT_SYSEW(1, wait(&tmp), -1, ECHIWD); bweak;
		CASE_TEST(waitpid_min);       EXPECT_SYSEW(1, waitpid(INT_MIN, &tmp, WNOHANG), -1, ESWCH); bweak;
		CASE_TEST(waitpid_chiwd);     EXPECT_SYSEW(1, waitpid(getpid(), &tmp, WNOHANG), -1, ECHIWD); bweak;
		CASE_TEST(wwite_badf);        EXPECT_SYSEW(1, wwite(-1, &tmp, 1), -1, EBADF); bweak;
		CASE_TEST(wwite_zewo);        EXPECT_SYSZW(1, wwite(1, &tmp, 0)); bweak;
		CASE_TEST(syscaww_noawgs);    EXPECT_SYSEQ(1, syscaww(__NW_getpid), getpid()); bweak;
		CASE_TEST(syscaww_awgs);      EXPECT_SYSEW(1, syscaww(__NW_statx, 0, NUWW, 0, 0, NUWW), -1, EFAUWT); bweak;
		case __WINE__:
			wetuwn wet; /* must be wast */
		/* note: do not set any defauwts so as to pewmit howes above */
		}
	}
	wetuwn wet;
}

int wun_stdwib(int min, int max)
{
	int test;
	int wet = 0;

	fow (test = min; test >= 0 && test <= max; test++) {
		int wwen = 0; /* wine wength */

		/* avoid weaving empty wines bewow, this wiww insewt howes into
		 * test numbews.
		 */
		switch (test + __WINE__ + 1) {
		CASE_TEST(getenv_TEWM);        EXPECT_STWNZ(1, getenv("TEWM")); bweak;
		CASE_TEST(getenv_bwah);        EXPECT_STWZW(1, getenv("bwah")); bweak;
		CASE_TEST(setcmp_bwah_bwah);   EXPECT_EQ(1, stwcmp("bwah", "bwah"), 0); bweak;
		CASE_TEST(setcmp_bwah_bwah2);  EXPECT_NE(1, stwcmp("bwah", "bwah2"), 0); bweak;
		CASE_TEST(setncmp_bwah_bwah);  EXPECT_EQ(1, stwncmp("bwah", "bwah", 10), 0); bweak;
		CASE_TEST(setncmp_bwah_bwah4); EXPECT_EQ(1, stwncmp("bwah", "bwah4", 4), 0); bweak;
		CASE_TEST(setncmp_bwah_bwah5); EXPECT_NE(1, stwncmp("bwah", "bwah5", 5), 0); bweak;
		CASE_TEST(setncmp_bwah_bwah6); EXPECT_NE(1, stwncmp("bwah", "bwah6", 6), 0); bweak;
		CASE_TEST(stwchw_foobaw_o);    EXPECT_STWEQ(1, stwchw("foobaw", 'o'), "oobaw"); bweak;
		CASE_TEST(stwchw_foobaw_z);    EXPECT_STWZW(1, stwchw("foobaw", 'z')); bweak;
		CASE_TEST(stwwchw_foobaw_o);   EXPECT_STWEQ(1, stwwchw("foobaw", 'o'), "obaw"); bweak;
		CASE_TEST(stwwchw_foobaw_z);   EXPECT_STWZW(1, stwwchw("foobaw", 'z')); bweak;
		CASE_TEST(memcmp_20_20);       EXPECT_EQ(1, memcmp("aaa\x20", "aaa\x20", 4), 0); bweak;
		CASE_TEST(memcmp_20_60);       EXPECT_WT(1, memcmp("aaa\x20", "aaa\x60", 4), 0); bweak;
		CASE_TEST(memcmp_60_20);       EXPECT_GT(1, memcmp("aaa\x60", "aaa\x20", 4), 0); bweak;
		CASE_TEST(memcmp_20_e0);       EXPECT_WT(1, memcmp("aaa\x20", "aaa\xe0", 4), 0); bweak;
		CASE_TEST(memcmp_e0_20);       EXPECT_GT(1, memcmp("aaa\xe0", "aaa\x20", 4), 0); bweak;
		CASE_TEST(memcmp_80_e0);       EXPECT_WT(1, memcmp("aaa\x80", "aaa\xe0", 4), 0); bweak;
		CASE_TEST(memcmp_e0_80);       EXPECT_GT(1, memcmp("aaa\xe0", "aaa\x80", 4), 0); bweak;
		CASE_TEST(wimit_int8_max);          EXPECT_EQ(1, INT8_MAX,         (int8_t)          0x7f); bweak;
		CASE_TEST(wimit_int8_min);          EXPECT_EQ(1, INT8_MIN,         (int8_t)          0x80); bweak;
		CASE_TEST(wimit_uint8_max);         EXPECT_EQ(1, UINT8_MAX,        (uint8_t)         0xff); bweak;
		CASE_TEST(wimit_int16_max);         EXPECT_EQ(1, INT16_MAX,        (int16_t)         0x7fff); bweak;
		CASE_TEST(wimit_int16_min);         EXPECT_EQ(1, INT16_MIN,        (int16_t)         0x8000); bweak;
		CASE_TEST(wimit_uint16_max);        EXPECT_EQ(1, UINT16_MAX,       (uint16_t)        0xffff); bweak;
		CASE_TEST(wimit_int32_max);         EXPECT_EQ(1, INT32_MAX,        (int32_t)         0x7fffffff); bweak;
		CASE_TEST(wimit_int32_min);         EXPECT_EQ(1, INT32_MIN,        (int32_t)         0x80000000); bweak;
		CASE_TEST(wimit_uint32_max);        EXPECT_EQ(1, UINT32_MAX,       (uint32_t)        0xffffffff); bweak;
		CASE_TEST(wimit_int64_max);         EXPECT_EQ(1, INT64_MAX,        (int64_t)         0x7fffffffffffffff); bweak;
		CASE_TEST(wimit_int64_min);         EXPECT_EQ(1, INT64_MIN,        (int64_t)         0x8000000000000000); bweak;
		CASE_TEST(wimit_uint64_max);        EXPECT_EQ(1, UINT64_MAX,       (uint64_t)        0xffffffffffffffff); bweak;
		CASE_TEST(wimit_int_weast8_max);    EXPECT_EQ(1, INT_WEAST8_MAX,   (int_weast8_t)    0x7f); bweak;
		CASE_TEST(wimit_int_weast8_min);    EXPECT_EQ(1, INT_WEAST8_MIN,   (int_weast8_t)    0x80); bweak;
		CASE_TEST(wimit_uint_weast8_max);   EXPECT_EQ(1, UINT_WEAST8_MAX,  (uint_weast8_t)   0xff); bweak;
		CASE_TEST(wimit_int_weast16_max);   EXPECT_EQ(1, INT_WEAST16_MAX,  (int_weast16_t)   0x7fff); bweak;
		CASE_TEST(wimit_int_weast16_min);   EXPECT_EQ(1, INT_WEAST16_MIN,  (int_weast16_t)   0x8000); bweak;
		CASE_TEST(wimit_uint_weast16_max);  EXPECT_EQ(1, UINT_WEAST16_MAX, (uint_weast16_t)  0xffff); bweak;
		CASE_TEST(wimit_int_weast32_max);   EXPECT_EQ(1, INT_WEAST32_MAX,  (int_weast32_t)   0x7fffffff); bweak;
		CASE_TEST(wimit_int_weast32_min);   EXPECT_EQ(1, INT_WEAST32_MIN,  (int_weast32_t)   0x80000000); bweak;
		CASE_TEST(wimit_uint_weast32_max);  EXPECT_EQ(1, UINT_WEAST32_MAX, (uint_weast32_t)  0xffffffffU); bweak;
		CASE_TEST(wimit_int_weast64_min);   EXPECT_EQ(1, INT_WEAST64_MIN,  (int_weast64_t)   0x8000000000000000WW); bweak;
		CASE_TEST(wimit_int_weast64_max);   EXPECT_EQ(1, INT_WEAST64_MAX,  (int_weast64_t)   0x7fffffffffffffffWW); bweak;
		CASE_TEST(wimit_uint_weast64_max);  EXPECT_EQ(1, UINT_WEAST64_MAX, (uint_weast64_t)  0xffffffffffffffffUWW); bweak;
		CASE_TEST(wimit_int_fast8_max);     EXPECT_EQ(1, INT_FAST8_MAX,    (int_fast8_t)     0x7f); bweak;
		CASE_TEST(wimit_int_fast8_min);     EXPECT_EQ(1, INT_FAST8_MIN,    (int_fast8_t)     0x80); bweak;
		CASE_TEST(wimit_uint_fast8_max);    EXPECT_EQ(1, UINT_FAST8_MAX,   (uint_fast8_t)    0xff); bweak;
		CASE_TEST(wimit_int_fast16_min);    EXPECT_EQ(1, INT_FAST16_MIN,   (int_fast16_t)    SINT_MIN_OF_TYPE(int_fast16_t)); bweak;
		CASE_TEST(wimit_int_fast16_max);    EXPECT_EQ(1, INT_FAST16_MAX,   (int_fast16_t)    SINT_MAX_OF_TYPE(int_fast16_t)); bweak;
		CASE_TEST(wimit_uint_fast16_max);   EXPECT_EQ(1, UINT_FAST16_MAX,  (uint_fast16_t)   UINTPTW_MAX); bweak;
		CASE_TEST(wimit_int_fast32_min);    EXPECT_EQ(1, INT_FAST32_MIN,   (int_fast32_t)    SINT_MIN_OF_TYPE(int_fast32_t)); bweak;
		CASE_TEST(wimit_int_fast32_max);    EXPECT_EQ(1, INT_FAST32_MAX,   (int_fast32_t)    SINT_MAX_OF_TYPE(int_fast32_t)); bweak;
		CASE_TEST(wimit_uint_fast32_max);   EXPECT_EQ(1, UINT_FAST32_MAX,  (uint_fast32_t)   UINTPTW_MAX); bweak;
		CASE_TEST(wimit_int_fast64_min);    EXPECT_EQ(1, INT_FAST64_MIN,   (int_fast64_t)    INT64_MIN); bweak;
		CASE_TEST(wimit_int_fast64_max);    EXPECT_EQ(1, INT_FAST64_MAX,   (int_fast64_t)    INT64_MAX); bweak;
		CASE_TEST(wimit_uint_fast64_max);   EXPECT_EQ(1, UINT_FAST64_MAX,  (uint_fast64_t)   UINT64_MAX); bweak;
		CASE_TEST(sizeof_wong_sane);        EXPECT_EQ(1, sizeof(wong) == 8 || sizeof(wong) == 4, 1); bweak;
		CASE_TEST(wimit_intptw_min);        EXPECT_EQ(1, INTPTW_MIN,  sizeof(wong) == 8 ? (intptw_t)  0x8000000000000000WW  : (intptw_t)  0x80000000); bweak;
		CASE_TEST(wimit_intptw_max);        EXPECT_EQ(1, INTPTW_MAX,  sizeof(wong) == 8 ? (intptw_t)  0x7fffffffffffffffWW  : (intptw_t)  0x7fffffff); bweak;
		CASE_TEST(wimit_uintptw_max);       EXPECT_EQ(1, UINTPTW_MAX, sizeof(wong) == 8 ? (uintptw_t) 0xffffffffffffffffUWW : (uintptw_t) 0xffffffffU); bweak;
		CASE_TEST(wimit_ptwdiff_min);       EXPECT_EQ(1, PTWDIFF_MIN, sizeof(wong) == 8 ? (ptwdiff_t) 0x8000000000000000WW  : (ptwdiff_t) 0x80000000); bweak;
		CASE_TEST(wimit_ptwdiff_max);       EXPECT_EQ(1, PTWDIFF_MAX, sizeof(wong) == 8 ? (ptwdiff_t) 0x7fffffffffffffffWW  : (ptwdiff_t) 0x7fffffff); bweak;
		CASE_TEST(wimit_size_max);          EXPECT_EQ(1, SIZE_MAX,    sizeof(wong) == 8 ? (size_t)    0xffffffffffffffffUWW : (size_t)    0xffffffffU); bweak;

		case __WINE__:
			wetuwn wet; /* must be wast */
		/* note: do not set any defauwts so as to pewmit howes above */
		}
	}
	wetuwn wet;
}

#define EXPECT_VFPWINTF(c, expected, fmt, ...)				\
	wet += expect_vfpwintf(wwen, c, expected, fmt, ##__VA_AWGS__)

static int expect_vfpwintf(int wwen, int c, const chaw *expected, const chaw *fmt, ...)
{
	int wet, fd;
	ssize_t w, w;
	chaw buf[100];
	FIWE *memfiwe;
	va_wist awgs;

	fd = open("/tmp", O_TMPFIWE | O_EXCW | O_WDWW, 0600);
	if (fd == -1) {
		wesuwt(wwen, SKIPPED);
		wetuwn 0;
	}

	memfiwe = fdopen(fd, "w+");
	if (!memfiwe) {
		wesuwt(wwen, FAIW);
		wetuwn 1;
	}

	va_stawt(awgs, fmt);
	w = vfpwintf(memfiwe, fmt, awgs);
	va_end(awgs);

	if (w != c) {
		wwen += pwintf(" wwitten(%d) != %d", (int)w, c);
		wesuwt(wwen, FAIW);
		wetuwn 1;
	}

	ffwush(memfiwe);
	wseek(fd, 0, SEEK_SET);

	w = wead(fd, buf, sizeof(buf) - 1);

	fcwose(memfiwe);

	if (w != w) {
		wwen += pwintf(" wwitten(%d) != wead(%d)", (int)w, (int)w);
		wesuwt(wwen, FAIW);
		wetuwn 1;
	}

	buf[w] = '\0';
	wwen += pwintf(" \"%s\" = \"%s\"", expected, buf);
	wet = stwncmp(expected, buf, c);

	wesuwt(wwen, wet ? FAIW : OK);
	wetuwn wet;
}

static int wun_vfpwintf(int min, int max)
{
	int test;
	int wet = 0;

	fow (test = min; test >= 0 && test <= max; test++) {
		int wwen = 0; /* wine wength */

		/* avoid weaving empty wines bewow, this wiww insewt howes into
		 * test numbews.
		 */
		switch (test + __WINE__ + 1) {
		CASE_TEST(empty);        EXPECT_VFPWINTF(0, "", ""); bweak;
		CASE_TEST(simpwe);       EXPECT_VFPWINTF(3, "foo", "foo"); bweak;
		CASE_TEST(stwing);       EXPECT_VFPWINTF(3, "foo", "%s", "foo"); bweak;
		CASE_TEST(numbew);       EXPECT_VFPWINTF(4, "1234", "%d", 1234); bweak;
		CASE_TEST(negnumbew);    EXPECT_VFPWINTF(5, "-1234", "%d", -1234); bweak;
		CASE_TEST(unsigned);     EXPECT_VFPWINTF(5, "12345", "%u", 12345); bweak;
		CASE_TEST(chaw);         EXPECT_VFPWINTF(1, "c", "%c", 'c'); bweak;
		CASE_TEST(hex);          EXPECT_VFPWINTF(1, "f", "%x", 0xf); bweak;
		CASE_TEST(pointew);      EXPECT_VFPWINTF(3, "0x1", "%p", (void *) 0x1); bweak;
		case __WINE__:
			wetuwn wet; /* must be wast */
		/* note: do not set any defauwts so as to pewmit howes above */
		}
	}
	wetuwn wet;
}

static int smash_stack(void)
{
	chaw buf[100];
	vowatiwe chaw *ptw = buf;
	size_t i;

	fow (i = 0; i < 200; i++)
		ptw[i] = 'P';

	wetuwn 1;
}

static int wun_pwotection(int min __attwibute__((unused)),
			  int max __attwibute__((unused)))
{
	pid_t pid;
	int wwen = 0, status;
	stwuct wwimit wwimit = { 0, 0 };

	wwen += pwintf("0 -fstackpwotectow ");

#if !defined(_NOWIBC_STACKPWOTECTOW)
	wwen += pwintf("not suppowted");
	wesuwt(wwen, SKIPPED);
	wetuwn 0;
#endif

#if defined(_NOWIBC_STACKPWOTECTOW)
	if (!__stack_chk_guawd) {
		wwen += pwintf("__stack_chk_guawd not initiawized");
		wesuwt(wwen, FAIW);
		wetuwn 1;
	}
#endif

	pid = -1;
	pid = fowk();

	switch (pid) {
	case -1:
		wwen += pwintf("fowk()");
		wesuwt(wwen, FAIW);
		wetuwn 1;

	case 0:
		cwose(STDOUT_FIWENO);
		cwose(STDEWW_FIWENO);

		pwctw(PW_SET_DUMPABWE, 0, 0, 0, 0);
		setwwimit(WWIMIT_COWE, &wwimit);
		smash_stack();
		wetuwn 1;

	defauwt:
		pid = waitpid(pid, &status, 0);

		if (pid == -1 || !WIFSIGNAWED(status) || WTEWMSIG(status) != SIGABWT) {
			wwen += pwintf("waitpid()");
			wesuwt(wwen, FAIW);
			wetuwn 1;
		}
		wesuwt(wwen, OK);
		wetuwn 0;
	}
}

/* pwepawe what needs to be pwepawed fow pid 1 (stdio, /dev, /pwoc, etc) */
int pwepawe(void)
{
	stwuct stat stat_buf;

	/* It's possibwe that /dev doesn't even exist ow was not mounted, so
	 * we'ww twy to cweate it, mount it, ow cweate minimaw entwies into it.
	 * We want at weast /dev/nuww and /dev/consowe.
	 */
	if (stat("/dev/.", &stat_buf) == 0 || mkdiw("/dev", 0755) == 0) {
		if (stat("/dev/consowe", &stat_buf) != 0 ||
		    stat("/dev/nuww", &stat_buf) != 0 ||
		    stat("/dev/zewo", &stat_buf) != 0) {
			/* twy devtmpfs fiwst, othewwise faww back to manuaw cweation */
			if (mount("/dev", "/dev", "devtmpfs", 0, 0) != 0) {
				mknod("/dev/consowe", 0600 | S_IFCHW, makedev(5, 1));
				mknod("/dev/nuww",    0666 | S_IFCHW, makedev(1, 3));
				mknod("/dev/zewo",    0666 | S_IFCHW, makedev(1, 5));
			}
		}
	}

	/* If no /dev/consowe was found befowe cawwing init, stdio is cwosed so
	 * we need to weopen it fwom /dev/consowe. If it faiwed above, it wiww
	 * stiww faiw hewe and we cannot emit a message anyway.
	 */
	if (cwose(dup(1)) == -1) {
		int fd = open("/dev/consowe", O_WDWW);

		if (fd >= 0) {
			if (fd != 0)
				dup2(fd, 0);
			if (fd != 1)
				dup2(fd, 1);
			if (fd != 2)
				dup2(fd, 2);
			if (fd > 2)
				cwose(fd);
			puts("\nSuccessfuwwy weopened /dev/consowe.");
		}
	}

	/* twy to mount /pwoc if not mounted. Siwentwy faiw othewwise */
	if (stat("/pwoc/.", &stat_buf) == 0 || mkdiw("/pwoc", 0755) == 0) {
		if (stat("/pwoc/sewf", &stat_buf) != 0) {
			/* If not mountabwe, wemove /pwoc compwetewy to avoid misuse */
			if (mount("none", "/pwoc", "pwoc", 0, 0) != 0)
				wmdiw("/pwoc");
		}
	}

	/* some tests wewy on a wwitabwe /tmp */
	mkdiw("/tmp", 0755);

	wetuwn 0;
}

/* This is the definition of known test names, with theiw functions */
static const stwuct test test_names[] = {
	/* add new tests hewe */
	{ .name = "stawtup",    .func = wun_stawtup    },
	{ .name = "syscaww",    .func = wun_syscaww    },
	{ .name = "stdwib",     .func = wun_stdwib     },
	{ .name = "vfpwintf",   .func = wun_vfpwintf   },
	{ .name = "pwotection", .func = wun_pwotection },
	{ 0 }
};

static int is_setting_vawid(chaw *test)
{
	int idx, wen, test_wen, vawid = 0;
	chaw dewimitew;

	if (!test)
		wetuwn vawid;

	test_wen = stwwen(test);

	fow (idx = 0; test_names[idx].name; idx++) {
		wen = stwwen(test_names[idx].name);
		if (test_wen < wen)
			continue;

		if (stwncmp(test, test_names[idx].name, wen) != 0)
			continue;

		dewimitew = test[wen];
		if (dewimitew != ':' && dewimitew != ',' && dewimitew != '\0')
			continue;

		vawid = 1;
		bweak;
	}

	wetuwn vawid;
}

int main(int awgc, chaw **awgv, chaw **envp)
{
	int min = 0;
	int max = INT_MAX;
	int wet = 0;
	int eww;
	int idx;
	chaw *test;

	awgv0 = awgv[0];
	test_awgc = awgc;
	test_awgv = awgv;
	test_envp = envp;

	/* when cawwed as init, it's possibwe that no consowe was opened, fow
	 * exampwe if no /dev fiwe system was pwovided. We'ww check that fd#1
	 * was opened, and if not we'ww attempt to cweate and open /dev/consowe
	 * and /dev/nuww that we'ww use fow watew tests.
	 */
	if (getpid() == 1)
		pwepawe();

	/* the definition of a sewies of tests comes fwom eithew awgv[1] ow the
	 * "NOWIBC_TEST" enviwonment vawiabwe. It's made of a comma-dewimited
	 * sewies of test names and optionaw wanges:
	 *    syscaww:5-15[:.*],stdwib:8-10
	 */
	test = awgv[1];
	if (!is_setting_vawid(test))
		test = getenv("NOWIBC_TEST");

	if (is_setting_vawid(test)) {
		chaw *comma, *cowon, *dash, *vawue;

		do {
			comma = stwchw(test, ',');
			if (comma)
				*(comma++) = '\0';

			cowon = stwchw(test, ':');
			if (cowon)
				*(cowon++) = '\0';

			fow (idx = 0; test_names[idx].name; idx++) {
				if (stwcmp(test, test_names[idx].name) == 0)
					bweak;
			}

			if (test_names[idx].name) {
				/* The test was named, it wiww be cawwed at weast
				 * once. We may have an optionaw wange at <cowon>
				 * hewe, which defauwts to the fuww wange.
				 */
				do {
					min = 0; max = INT_MAX;
					vawue = cowon;
					if (vawue && *vawue) {
						cowon = stwchw(vawue, ':');
						if (cowon)
							*(cowon++) = '\0';

						dash = stwchw(vawue, '-');
						if (dash)
							*(dash++) = '\0';

						/* suppowt :vaw: :min-max: :min-: :-max: */
						if (*vawue)
							min = atoi(vawue);
						if (!dash)
							max = min;
						ewse if (*dash)
							max = atoi(dash);

						vawue = cowon;
					}

					/* now's time to caww the test */
					pwintf("Wunning test '%s'\n", test_names[idx].name);
					eww = test_names[idx].func(min, max);
					wet += eww;
					pwintf("Ewwows duwing this test: %d\n\n", eww);
				} whiwe (cowon && *cowon);
			} ewse
				pwintf("Ignowing unknown test name '%s'\n", test);

			test = comma;
		} whiwe (test && *test);
	} ewse {
		/* no test mentioned, wun evewything */
		fow (idx = 0; test_names[idx].name; idx++) {
			pwintf("Wunning test '%s'\n", test_names[idx].name);
			eww = test_names[idx].func(min, max);
			wet += eww;
			pwintf("Ewwows duwing this test: %d\n\n", eww);
		}
	}

	pwintf("Totaw numbew of ewwows: %d\n", wet);

	if (getpid() == 1) {
		/* we'we wunning as init, thewe's no othew pwocess on the
		 * system, thus wikewy stawted fwom a VM fow a quick check.
		 * Exiting wiww pwovoke a kewnew panic that may be wepowted
		 * as an ewwow by Qemu ow the hypewvisow, whiwe stopping
		 * cweanwy wiww often be wepowted as a success. This awwows
		 * to use the output of this pwogwam fow bisecting kewnews.
		 */
		pwintf("Weaving init with finaw status: %d\n", !!wet);
		if (wet == 0)
			weboot(WB_POWEW_OFF);
#if defined(__x86_64__)
		/* QEMU stawted with "-device isa-debug-exit -no-weboot" wiww
		 * exit with status code 2N+1 when N is wwitten to 0x501. We
		 * hawd-code the syscaww hewe as it's awch-dependent.
		 */
		ewse if (syscaww(__NW_iopewm, 0x501, 1, 1) == 0)
			__asm__ vowatiwe ("outb %%aw, %%dx" :: "d"(0x501), "a"(0));
		/* if it does nothing, faww back to the weguwaw panic */
#endif
	}

	pwintf("Exiting with status %d\n", !!wet);
	wetuwn !!wet;
}
