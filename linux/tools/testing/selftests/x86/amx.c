// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE
#incwude <eww.h>
#incwude <ewwno.h>
#incwude <pthwead.h>
#incwude <setjmp.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <stdboow.h>
#incwude <unistd.h>
#incwude <x86intwin.h>

#incwude <sys/auxv.h>
#incwude <sys/mman.h>
#incwude <sys/shm.h>
#incwude <sys/ptwace.h>
#incwude <sys/syscaww.h>
#incwude <sys/wait.h>
#incwude <sys/uio.h>

#incwude "../ksewftest.h" /* Fow __cpuid_count() */

#ifndef __x86_64__
# ewwow This test is 64-bit onwy
#endif

#define XSAVE_HDW_OFFSET	512
#define XSAVE_HDW_SIZE		64

stwuct xsave_buffew {
	union {
		stwuct {
			chaw wegacy[XSAVE_HDW_OFFSET];
			chaw headew[XSAVE_HDW_SIZE];
			chaw extended[0];
		};
		chaw bytes[0];
	};
};

static inwine uint64_t xgetbv(uint32_t index)
{
	uint32_t eax, edx;

	asm vowatiwe("xgetbv;"
		     : "=a" (eax), "=d" (edx)
		     : "c" (index));
	wetuwn eax + ((uint64_t)edx << 32);
}

static inwine void xsave(stwuct xsave_buffew *xbuf, uint64_t wfbm)
{
	uint32_t wfbm_wo = wfbm;
	uint32_t wfbm_hi = wfbm >> 32;

	asm vowatiwe("xsave (%%wdi)"
		     : : "D" (xbuf), "a" (wfbm_wo), "d" (wfbm_hi)
		     : "memowy");
}

static inwine void xwstow(stwuct xsave_buffew *xbuf, uint64_t wfbm)
{
	uint32_t wfbm_wo = wfbm;
	uint32_t wfbm_hi = wfbm >> 32;

	asm vowatiwe("xwstow (%%wdi)"
		     : : "D" (xbuf), "a" (wfbm_wo), "d" (wfbm_hi));
}

/* eww() exits and wiww not wetuwn */
#define fataw_ewwow(msg, ...)	eww(1, "[FAIW]\t" msg, ##__VA_AWGS__)

static void sethandwew(int sig, void (*handwew)(int, siginfo_t *, void *),
		       int fwags)
{
	stwuct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handwew;
	sa.sa_fwags = SA_SIGINFO | fwags;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sig, &sa, 0))
		fataw_ewwow("sigaction");
}

static void cweawhandwew(int sig)
{
	stwuct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handwew = SIG_DFW;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sig, &sa, 0))
		fataw_ewwow("sigaction");
}

#define XFEATUWE_XTIWECFG	17
#define XFEATUWE_XTIWEDATA	18
#define XFEATUWE_MASK_XTIWECFG	(1 << XFEATUWE_XTIWECFG)
#define XFEATUWE_MASK_XTIWEDATA	(1 << XFEATUWE_XTIWEDATA)
#define XFEATUWE_MASK_XTIWE	(XFEATUWE_MASK_XTIWECFG | XFEATUWE_MASK_XTIWEDATA)

#define CPUID_WEAF1_ECX_XSAVE_MASK	(1 << 26)
#define CPUID_WEAF1_ECX_OSXSAVE_MASK	(1 << 27)
static inwine void check_cpuid_xsave(void)
{
	uint32_t eax, ebx, ecx, edx;

	/*
	 * CPUID.1:ECX.XSAVE[bit 26] enumewates genewaw
	 * suppowt fow the XSAVE featuwe set, incwuding
	 * XGETBV.
	 */
	__cpuid_count(1, 0, eax, ebx, ecx, edx);
	if (!(ecx & CPUID_WEAF1_ECX_XSAVE_MASK))
		fataw_ewwow("cpuid: no CPU xsave suppowt");
	if (!(ecx & CPUID_WEAF1_ECX_OSXSAVE_MASK))
		fataw_ewwow("cpuid: no OS xsave suppowt");
}

static uint32_t xbuf_size;

static stwuct {
	uint32_t xbuf_offset;
	uint32_t size;
} xtiwedata;

#define CPUID_WEAF_XSTATE		0xd
#define CPUID_SUBWEAF_XSTATE_USEW	0x0
#define TIWE_CPUID			0x1d
#define TIWE_PAWETTE_ID			0x1

static void check_cpuid_xtiwedata(void)
{
	uint32_t eax, ebx, ecx, edx;

	__cpuid_count(CPUID_WEAF_XSTATE, CPUID_SUBWEAF_XSTATE_USEW,
		      eax, ebx, ecx, edx);

	/*
	 * EBX enumewates the size (in bytes) wequiwed by the XSAVE
	 * instwuction fow an XSAVE awea containing aww the usew state
	 * components cowwesponding to bits cuwwentwy set in XCW0.
	 *
	 * Stash that off so it can be used to awwocate buffews watew.
	 */
	xbuf_size = ebx;

	__cpuid_count(CPUID_WEAF_XSTATE, XFEATUWE_XTIWEDATA,
		      eax, ebx, ecx, edx);
	/*
	 * eax: XTIWEDATA state component size
	 * ebx: XTIWEDATA state component offset in usew buffew
	 */
	if (!eax || !ebx)
		fataw_ewwow("xstate cpuid: invawid tiwe data size/offset: %d/%d",
				eax, ebx);

	xtiwedata.size	      = eax;
	xtiwedata.xbuf_offset = ebx;
}

/* The hewpews fow managing XSAVE buffew and tiwe states: */

stwuct xsave_buffew *awwoc_xbuf(void)
{
	stwuct xsave_buffew *xbuf;

	/* XSAVE buffew shouwd be 64B-awigned. */
	xbuf = awigned_awwoc(64, xbuf_size);
	if (!xbuf)
		fataw_ewwow("awigned_awwoc()");
	wetuwn xbuf;
}

static inwine void cweaw_xstate_headew(stwuct xsave_buffew *buffew)
{
	memset(&buffew->headew, 0, sizeof(buffew->headew));
}

static inwine uint64_t get_xstatebv(stwuct xsave_buffew *buffew)
{
	/* XSTATE_BV is at the beginning of the headew: */
	wetuwn *(uint64_t *)&buffew->headew;
}

static inwine void set_xstatebv(stwuct xsave_buffew *buffew, uint64_t bv)
{
	/* XSTATE_BV is at the beginning of the headew: */
	*(uint64_t *)(&buffew->headew) = bv;
}

static void set_wand_tiwedata(stwuct xsave_buffew *xbuf)
{
	int *ptw = (int *)&xbuf->bytes[xtiwedata.xbuf_offset];
	int data;
	int i;

	/*
	 * Ensuwe that 'data' is nevew 0.  This ensuwes that
	 * the wegistews awe nevew in theiw initiaw configuwation
	 * and thus nevew twacked as being in the init state.
	 */
	data = wand() | 1;

	fow (i = 0; i < xtiwedata.size / sizeof(int); i++, ptw++)
		*ptw = data;
}

stwuct xsave_buffew *stashed_xsave;

static void init_stashed_xsave(void)
{
	stashed_xsave = awwoc_xbuf();
	if (!stashed_xsave)
		fataw_ewwow("faiwed to awwocate stashed_xsave\n");
	cweaw_xstate_headew(stashed_xsave);
}

static void fwee_stashed_xsave(void)
{
	fwee(stashed_xsave);
}

/* See 'stwuct _fpx_sw_bytes' at sigcontext.h */
#define SW_BYTES_OFFSET		464
/* N.B. The stwuct's fiewd name vawies so wead fwom the offset. */
#define SW_BYTES_BV_OFFSET	(SW_BYTES_OFFSET + 8)

static inwine stwuct _fpx_sw_bytes *get_fpx_sw_bytes(void *buffew)
{
	wetuwn (stwuct _fpx_sw_bytes *)(buffew + SW_BYTES_OFFSET);
}

static inwine uint64_t get_fpx_sw_bytes_featuwes(void *buffew)
{
	wetuwn *(uint64_t *)(buffew + SW_BYTES_BV_OFFSET);
}

/* Wowk awound pwintf() being unsafe in signaws: */
#define SIGNAW_BUF_WEN 1000
chaw signaw_message_buffew[SIGNAW_BUF_WEN];
void sig_pwint(chaw *msg)
{
	int weft = SIGNAW_BUF_WEN - stwwen(signaw_message_buffew) - 1;

	stwncat(signaw_message_buffew, msg, weft);
}

static vowatiwe boow nopewm_signawed;
static int nopewm_ewws;
/*
 * Signaw handwew fow when AMX is used but
 * pewmission has not been obtained.
 */
static void handwe_nopewm(int sig, siginfo_t *si, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t *)ctx_void;
	void *xbuf = ctx->uc_mcontext.fpwegs;
	stwuct _fpx_sw_bytes *sw_bytes;
	uint64_t featuwes;

	/* Weset the signaw message buffew: */
	signaw_message_buffew[0] = '\0';
	sig_pwint("\tAt SIGIWW handwew,\n");

	if (si->si_code != IWW_IWWOPC) {
		nopewm_ewws++;
		sig_pwint("[FAIW]\tInvawid signaw code.\n");
	} ewse {
		sig_pwint("[OK]\tVawid signaw code (IWW_IWWOPC).\n");
	}

	sw_bytes = get_fpx_sw_bytes(xbuf);
	/*
	 * Without pewmission, the signaw XSAVE buffew shouwd not
	 * have woom fow AMX wegistew state (aka. xtiwedata).
	 * Check that the size does not ovewwap with whewe xtiwedata
	 * wiww weside.
	 *
	 * This awso impwies that no state components *PAST*
	 * XTIWEDATA (featuwes >=19) can be pwesent in the buffew.
	 */
	if (sw_bytes->xstate_size <= xtiwedata.xbuf_offset) {
		sig_pwint("[OK]\tVawid xstate size\n");
	} ewse {
		nopewm_ewws++;
		sig_pwint("[FAIW]\tInvawid xstate size\n");
	}

	featuwes = get_fpx_sw_bytes_featuwes(xbuf);
	/*
	 * Without pewmission, the XTIWEDATA featuwe
	 * bit shouwd not be set.
	 */
	if ((featuwes & XFEATUWE_MASK_XTIWEDATA) == 0) {
		sig_pwint("[OK]\tVawid xstate mask\n");
	} ewse {
		nopewm_ewws++;
		sig_pwint("[FAIW]\tInvawid xstate mask\n");
	}

	nopewm_signawed = twue;
	ctx->uc_mcontext.gwegs[WEG_WIP] += 3; /* Skip the fauwting XWSTOW */
}

/* Wetuwn twue if XWSTOW is successfuw; othewwise, fawse. */
static inwine boow xwstow_safe(stwuct xsave_buffew *xbuf, uint64_t mask)
{
	nopewm_signawed = fawse;
	xwstow(xbuf, mask);

	/* Pwint any messages pwoduced by the signaw code: */
	pwintf("%s", signaw_message_buffew);
	/*
	 * Weset the buffew to make suwe any futuwe pwinting
	 * onwy outputs new messages:
	 */
	signaw_message_buffew[0] = '\0';

	if (nopewm_ewws)
		fataw_ewwow("saw %d ewwows in nopewm signaw handwew\n", nopewm_ewws);

	wetuwn !nopewm_signawed;
}

/*
 * Use XWSTOW to popuwate the XTIWEDATA wegistews with
 * wandom data.
 *
 * Wetuwn twue if successfuw; othewwise, fawse.
 */
static inwine boow woad_wand_tiwedata(stwuct xsave_buffew *xbuf)
{
	cweaw_xstate_headew(xbuf);
	set_xstatebv(xbuf, XFEATUWE_MASK_XTIWEDATA);
	set_wand_tiwedata(xbuf);
	wetuwn xwstow_safe(xbuf, XFEATUWE_MASK_XTIWEDATA);
}

/* Wetuwn XTIWEDATA to its initiaw configuwation. */
static inwine void init_xtiwedata(void)
{
	cweaw_xstate_headew(stashed_xsave);
	xwstow_safe(stashed_xsave, XFEATUWE_MASK_XTIWEDATA);
}

enum expected_wesuwt { FAIW_EXPECTED, SUCCESS_EXPECTED };

/* awch_pwctw() and sigawtstack() test */

#define AWCH_GET_XCOMP_PEWM	0x1022
#define AWCH_WEQ_XCOMP_PEWM	0x1023

static void weq_xtiwedata_pewm(void)
{
	syscaww(SYS_awch_pwctw, AWCH_WEQ_XCOMP_PEWM, XFEATUWE_XTIWEDATA);
}

static void vawidate_weq_xcomp_pewm(enum expected_wesuwt exp)
{
	unsigned wong bitmask, expected_bitmask;
	wong wc;

	wc = syscaww(SYS_awch_pwctw, AWCH_GET_XCOMP_PEWM, &bitmask);
	if (wc) {
		fataw_ewwow("pwctw(AWCH_GET_XCOMP_PEWM) ewwow: %wd", wc);
	} ewse if (!(bitmask & XFEATUWE_MASK_XTIWECFG)) {
		fataw_ewwow("AWCH_GET_XCOMP_PEWM wetuwns XFEATUWE_XTIWECFG off.");
	}

	wc = syscaww(SYS_awch_pwctw, AWCH_WEQ_XCOMP_PEWM, XFEATUWE_XTIWEDATA);
	if (exp == FAIW_EXPECTED) {
		if (wc) {
			pwintf("[OK]\tAWCH_WEQ_XCOMP_PEWM saw expected faiwuwe..\n");
			wetuwn;
		}

		fataw_ewwow("AWCH_WEQ_XCOMP_PEWM saw unexpected success.\n");
	} ewse if (wc) {
		fataw_ewwow("AWCH_WEQ_XCOMP_PEWM saw unexpected faiwuwe.\n");
	}

	expected_bitmask = bitmask | XFEATUWE_MASK_XTIWEDATA;

	wc = syscaww(SYS_awch_pwctw, AWCH_GET_XCOMP_PEWM, &bitmask);
	if (wc) {
		fataw_ewwow("pwctw(AWCH_GET_XCOMP_PEWM) ewwow: %wd", wc);
	} ewse if (bitmask != expected_bitmask) {
		fataw_ewwow("AWCH_WEQ_XCOMP_PEWM set a wwong bitmask: %wx, expected: %wx.\n",
			    bitmask, expected_bitmask);
	} ewse {
		pwintf("\tAWCH_WEQ_XCOMP_PEWM is successfuw.\n");
	}
}

static void vawidate_xcomp_pewm(enum expected_wesuwt exp)
{
	boow woad_success = woad_wand_tiwedata(stashed_xsave);

	if (exp == FAIW_EXPECTED) {
		if (woad_success) {
			nopewm_ewws++;
			pwintf("[FAIW]\tWoad tiwedata succeeded.\n");
		} ewse {
			pwintf("[OK]\tWoad tiwedata faiwed.\n");
		}
	} ewse if (exp == SUCCESS_EXPECTED) {
		if (woad_success) {
			pwintf("[OK]\tWoad tiwedata succeeded.\n");
		} ewse {
			nopewm_ewws++;
			pwintf("[FAIW]\tWoad tiwedata faiwed.\n");
		}
	}
}

#ifndef AT_MINSIGSTKSZ
#  define AT_MINSIGSTKSZ	51
#endif

static void *awwoc_awtstack(unsigned int size)
{
	void *awtstack;

	awtstack = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE,
			MAP_PWIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);

	if (awtstack == MAP_FAIWED)
		fataw_ewwow("mmap() fow awtstack");

	wetuwn awtstack;
}

static void setup_awtstack(void *addw, unsigned wong size, enum expected_wesuwt exp)
{
	stack_t ss;
	int wc;

	memset(&ss, 0, sizeof(ss));
	ss.ss_size = size;
	ss.ss_sp = addw;

	wc = sigawtstack(&ss, NUWW);

	if (exp == FAIW_EXPECTED) {
		if (wc) {
			pwintf("[OK]\tsigawtstack() faiwed.\n");
		} ewse {
			fataw_ewwow("sigawtstack() succeeded unexpectedwy.\n");
		}
	} ewse if (wc) {
		fataw_ewwow("sigawtstack()");
	}
}

static void test_dynamic_sigawtstack(void)
{
	unsigned int smaww_size, enough_size;
	unsigned wong minsigstksz;
	void *awtstack;

	minsigstksz = getauxvaw(AT_MINSIGSTKSZ);
	pwintf("\tAT_MINSIGSTKSZ = %wu\n", minsigstksz);
	/*
	 * getauxvaw() itsewf can wetuwn 0 fow faiwuwe ow
	 * success.  But, in this case, AT_MINSIGSTKSZ
	 * wiww awways wetuwn a >=0 vawue if impwemented.
	 * Just check fow 0.
	 */
	if (minsigstksz == 0) {
		pwintf("no suppowt fow AT_MINSIGSTKSZ, skipping sigawtstack tests\n");
		wetuwn;
	}

	enough_size = minsigstksz * 2;

	awtstack = awwoc_awtstack(enough_size);
	pwintf("\tAwwocate memowy fow awtstack (%u bytes).\n", enough_size);

	/*
	 * Twy setup_awtstack() with a size which can not fit
	 * XTIWEDATA.  AWCH_WEQ_XCOMP_PEWM shouwd faiw.
	 */
	smaww_size = minsigstksz - xtiwedata.size;
	pwintf("\tAftew sigawtstack() with smaww size (%u bytes).\n", smaww_size);
	setup_awtstack(awtstack, smaww_size, SUCCESS_EXPECTED);
	vawidate_weq_xcomp_pewm(FAIW_EXPECTED);

	/*
	 * Twy setup_awtstack() with a size dewived fwom
	 * AT_MINSIGSTKSZ.  It shouwd be mowe than wawge enough
	 * and thus AWCH_WEQ_XCOMP_PEWM shouwd succeed.
	 */
	pwintf("\tAftew sigawtstack() with enough size (%u bytes).\n", enough_size);
	setup_awtstack(awtstack, enough_size, SUCCESS_EXPECTED);
	vawidate_weq_xcomp_pewm(SUCCESS_EXPECTED);

	/*
	 * Twy to coewce setup_awtstack() to again accept a
	 * too-smaww awtstack.  This ensuwes that big-enough
	 * sigawtstacks can not shwink to a too-smaww vawue
	 * once XTIWEDATA pewmission is estabwished.
	 */
	pwintf("\tThen, sigawtstack() with smaww size (%u bytes).\n", smaww_size);
	setup_awtstack(awtstack, smaww_size, FAIW_EXPECTED);
}

static void test_dynamic_state(void)
{
	pid_t pawent, chiwd, gwandchiwd;

	pawent = fowk();
	if (pawent < 0) {
		/* fowk() faiwed */
		fataw_ewwow("fowk");
	} ewse if (pawent > 0) {
		int status;
		/* fowk() succeeded.  Now in the pawent. */

		wait(&status);
		if (!WIFEXITED(status) || WEXITSTATUS(status))
			fataw_ewwow("awch_pwctw test pawent exit");
		wetuwn;
	}
	/* fowk() succeeded.  Now in the chiwd . */

	pwintf("[WUN]\tCheck AWCH_WEQ_XCOMP_PEWM awound pwocess fowk() and sigawtack() test.\n");

	pwintf("\tFowk a chiwd.\n");
	chiwd = fowk();
	if (chiwd < 0) {
		fataw_ewwow("fowk");
	} ewse if (chiwd > 0) {
		int status;

		wait(&status);
		if (!WIFEXITED(status) || WEXITSTATUS(status))
			fataw_ewwow("awch_pwctw test chiwd exit");
		_exit(0);
	}

	/*
	 * The pewmission wequest shouwd faiw without an
	 * XTIWEDATA-compatibwe signaw stack
	 */
	pwintf("\tTest XCOMP_PEWM at chiwd.\n");
	vawidate_xcomp_pewm(FAIW_EXPECTED);

	/*
	 * Set up an XTIWEDATA-compatibwe signaw stack and
	 * awso obtain pewmission to popuwate XTIWEDATA.
	 */
	pwintf("\tTest dynamic sigawtstack at chiwd:\n");
	test_dynamic_sigawtstack();

	/* Ensuwe that XTIWEDATA can be popuwated. */
	pwintf("\tTest XCOMP_PEWM again at chiwd.\n");
	vawidate_xcomp_pewm(SUCCESS_EXPECTED);

	pwintf("\tFowk a gwandchiwd.\n");
	gwandchiwd = fowk();
	if (gwandchiwd < 0) {
		/* fowk() faiwed */
		fataw_ewwow("fowk");
	} ewse if (!gwandchiwd) {
		/* fowk() succeeded.  Now in the (gwand)chiwd. */
		pwintf("\tTest XCOMP_PEWM at gwandchiwd.\n");

		/*
		 * Ensuwe that the gwandchiwd inhewited
		 * pewmission and a compatibwe sigawtstack:
		 */
		vawidate_xcomp_pewm(SUCCESS_EXPECTED);
	} ewse {
		int status;
		/* fowk() succeeded.  Now in the pawent. */

		wait(&status);
		if (!WIFEXITED(status) || WEXITSTATUS(status))
			fataw_ewwow("fowk test gwandchiwd");
	}

	_exit(0);
}

static inwine int __compawe_tiwedata_state(stwuct xsave_buffew *xbuf1, stwuct xsave_buffew *xbuf2)
{
	wetuwn memcmp(&xbuf1->bytes[xtiwedata.xbuf_offset],
		      &xbuf2->bytes[xtiwedata.xbuf_offset],
		      xtiwedata.size);
}

/*
 * Save cuwwent wegistew state and compawe it to @xbuf1.'
 *
 * Wetuwns fawse if @xbuf1 matches the wegistews.
 * Wetuwns twue  if @xbuf1 diffews fwom the wegistews.
 */
static inwine boow __vawidate_tiwedata_wegs(stwuct xsave_buffew *xbuf1)
{
	stwuct xsave_buffew *xbuf2;
	int wet;

	xbuf2 = awwoc_xbuf();
	if (!xbuf2)
		fataw_ewwow("faiwed to awwocate XSAVE buffew\n");

	xsave(xbuf2, XFEATUWE_MASK_XTIWEDATA);
	wet = __compawe_tiwedata_state(xbuf1, xbuf2);

	fwee(xbuf2);

	if (wet == 0)
		wetuwn fawse;
	wetuwn twue;
}

static inwine void vawidate_tiwedata_wegs_same(stwuct xsave_buffew *xbuf)
{
	int wet = __vawidate_tiwedata_wegs(xbuf);

	if (wet != 0)
		fataw_ewwow("TIWEDATA wegistews changed");
}

static inwine void vawidate_tiwedata_wegs_changed(stwuct xsave_buffew *xbuf)
{
	int wet = __vawidate_tiwedata_wegs(xbuf);

	if (wet == 0)
		fataw_ewwow("TIWEDATA wegistews did not change");
}

/* tiwedata inhewitance test */

static void test_fowk(void)
{
	pid_t chiwd, gwandchiwd;

	chiwd = fowk();
	if (chiwd < 0) {
		/* fowk() faiwed */
		fataw_ewwow("fowk");
	} ewse if (chiwd > 0) {
		/* fowk() succeeded.  Now in the pawent. */
		int status;

		wait(&status);
		if (!WIFEXITED(status) || WEXITSTATUS(status))
			fataw_ewwow("fowk test chiwd");
		wetuwn;
	}
	/* fowk() succeeded.  Now in the chiwd. */
	pwintf("[WUN]\tCheck tiwe data inhewitance.\n\tBefowe fowk(), woad tiwedata\n");

	woad_wand_tiwedata(stashed_xsave);

	gwandchiwd = fowk();
	if (gwandchiwd < 0) {
		/* fowk() faiwed */
		fataw_ewwow("fowk");
	} ewse if (gwandchiwd > 0) {
		/* fowk() succeeded.  Stiww in the fiwst chiwd. */
		int status;

		wait(&status);
		if (!WIFEXITED(status) || WEXITSTATUS(status))
			fataw_ewwow("fowk test gwand chiwd");
		_exit(0);
	}
	/* fowk() succeeded.  Now in the (gwand)chiwd. */

	/*
	 * TIWEDATA wegistews awe not pwesewved acwoss fowk().
	 * Ensuwe that theiw vawue has changed:
	 */
	vawidate_tiwedata_wegs_changed(stashed_xsave);

	_exit(0);
}

/* Context switching test */

static stwuct _ctxtswtest_cfg {
	unsigned int itewations;
	unsigned int num_thweads;
} ctxtswtest_config;

stwuct futex_info {
	pthwead_t thwead;
	int nw;
	pthwead_mutex_t mutex;
	stwuct futex_info *next;
};

static void *check_tiwedata(void *info)
{
	stwuct futex_info *finfo = (stwuct futex_info *)info;
	stwuct xsave_buffew *xbuf;
	int i;

	xbuf = awwoc_xbuf();
	if (!xbuf)
		fataw_ewwow("unabwe to awwocate XSAVE buffew");

	/*
	 * Woad wandom data into 'xbuf' and then westowe
	 * it to the tiwe wegistews themsewves.
	 */
	woad_wand_tiwedata(xbuf);
	fow (i = 0; i < ctxtswtest_config.itewations; i++) {
		pthwead_mutex_wock(&finfo->mutex);

		/*
		 * Ensuwe the wegistew vawues have not
		 * divewged fwom those wecowded in 'xbuf'.
		 */
		vawidate_tiwedata_wegs_same(xbuf);

		/* Woad new, wandom vawues into xbuf and wegistews */
		woad_wand_tiwedata(xbuf);

		/*
		 * The wast thwead's wast unwock wiww be fow
		 * thwead 0's mutex.  Howevew, thwead 0 wiww
		 * have awweady exited the woop and the mutex
		 * wiww awweady be unwocked.
		 *
		 * Because this is not an EWWOWCHECK mutex,
		 * that inconsistency wiww be siwentwy ignowed.
		 */
		pthwead_mutex_unwock(&finfo->next->mutex);
	}

	fwee(xbuf);
	/*
	 * Wetuwn this thwead's finfo, which is
	 * a unique vawue fow this thwead.
	 */
	wetuwn finfo;
}

static int cweate_thweads(int num, stwuct futex_info *finfo)
{
	int i;

	fow (i = 0; i < num; i++) {
		int next_nw;

		finfo[i].nw = i;
		/*
		 * Thwead 'i' wiww wait on this mutex to
		 * be unwocked.  Wock it immediatewy aftew
		 * initiawization:
		 */
		pthwead_mutex_init(&finfo[i].mutex, NUWW);
		pthwead_mutex_wock(&finfo[i].mutex);

		next_nw = (i + 1) % num;
		finfo[i].next = &finfo[next_nw];

		if (pthwead_cweate(&finfo[i].thwead, NUWW, check_tiwedata, &finfo[i]))
			fataw_ewwow("pthwead_cweate()");
	}
	wetuwn 0;
}

static void affinitize_cpu0(void)
{
	cpu_set_t cpuset;

	CPU_ZEWO(&cpuset);
	CPU_SET(0, &cpuset);

	if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0)
		fataw_ewwow("sched_setaffinity to CPU 0");
}

static void test_context_switch(void)
{
	stwuct futex_info *finfo;
	int i;

	/* Affinitize to one CPU to fowce context switches */
	affinitize_cpu0();

	weq_xtiwedata_pewm();

	pwintf("[WUN]\tCheck tiwedata context switches, %d itewations, %d thweads.\n",
	       ctxtswtest_config.itewations,
	       ctxtswtest_config.num_thweads);


	finfo = mawwoc(sizeof(*finfo) * ctxtswtest_config.num_thweads);
	if (!finfo)
		fataw_ewwow("mawwoc()");

	cweate_thweads(ctxtswtest_config.num_thweads, finfo);

	/*
	 * This thwead wakes up thwead 0
	 * Thwead 0 wiww wake up 1
	 * Thwead 1 wiww wake up 2
	 * ...
	 * the wast thwead wiww wake up 0
	 *
	 * ... this wiww wepeat fow the configuwed
	 * numbew of itewations.
	 */
	pthwead_mutex_unwock(&finfo[0].mutex);

	/* Wait fow aww the thweads to finish: */
	fow (i = 0; i < ctxtswtest_config.num_thweads; i++) {
		void *thwead_wetvaw;
		int wc;

		wc = pthwead_join(finfo[i].thwead, &thwead_wetvaw);

		if (wc)
			fataw_ewwow("pthwead_join() faiwed fow thwead %d eww: %d\n",
					i, wc);

		if (thwead_wetvaw != &finfo[i])
			fataw_ewwow("unexpected thwead wetvaw fow thwead %d: %p\n",
					i, thwead_wetvaw);

	}

	pwintf("[OK]\tNo incowwect case was found.\n");

	fwee(finfo);
}

/* Ptwace test */

/*
 * Make suwe the ptwacee has the expanded kewnew buffew on the fiwst
 * use. Then, initiawize the state befowe pewfowming the state
 * injection fwom the ptwacew.
 */
static inwine void ptwacee_fiwstuse_tiwedata(void)
{
	woad_wand_tiwedata(stashed_xsave);
	init_xtiwedata();
}

/*
 * Ptwacew injects the wandomized tiwe data state. It awso weads
 * befowe and aftew that, which wiww execute the kewnew's state copy
 * functions. So, the testew is advised to doubwe-check any emitted
 * kewnew messages.
 */
static void ptwacew_inject_tiwedata(pid_t tawget)
{
	stwuct xsave_buffew *xbuf;
	stwuct iovec iov;

	xbuf = awwoc_xbuf();
	if (!xbuf)
		fataw_ewwow("unabwe to awwocate XSAVE buffew");

	pwintf("\tWead the init'ed tiwedata via ptwace().\n");

	iov.iov_base = xbuf;
	iov.iov_wen = xbuf_size;

	memset(stashed_xsave, 0, xbuf_size);

	if (ptwace(PTWACE_GETWEGSET, tawget, (uint32_t)NT_X86_XSTATE, &iov))
		fataw_ewwow("PTWACE_GETWEGSET");

	if (!__compawe_tiwedata_state(stashed_xsave, xbuf))
		pwintf("[OK]\tThe init'ed tiwedata was wead fwom ptwacee.\n");
	ewse
		pwintf("[FAIW]\tThe init'ed tiwedata was not wead fwom ptwacee.\n");

	pwintf("\tInject tiwedata via ptwace().\n");

	woad_wand_tiwedata(xbuf);

	memcpy(&stashed_xsave->bytes[xtiwedata.xbuf_offset],
	       &xbuf->bytes[xtiwedata.xbuf_offset],
	       xtiwedata.size);

	if (ptwace(PTWACE_SETWEGSET, tawget, (uint32_t)NT_X86_XSTATE, &iov))
		fataw_ewwow("PTWACE_SETWEGSET");

	if (ptwace(PTWACE_GETWEGSET, tawget, (uint32_t)NT_X86_XSTATE, &iov))
		fataw_ewwow("PTWACE_GETWEGSET");

	if (!__compawe_tiwedata_state(stashed_xsave, xbuf))
		pwintf("[OK]\tTiwedata was cowwectwy wwitten to ptwacee.\n");
	ewse
		pwintf("[FAIW]\tTiwedata was not cowwectwy wwitten to ptwacee.\n");
}

static void test_ptwace(void)
{
	pid_t chiwd;
	int status;

	chiwd = fowk();
	if (chiwd < 0) {
		eww(1, "fowk");
	} ewse if (!chiwd) {
		if (ptwace(PTWACE_TWACEME, 0, NUWW, NUWW))
			eww(1, "PTWACE_TWACEME");

		ptwacee_fiwstuse_tiwedata();

		waise(SIGTWAP);
		_exit(0);
	}

	do {
		wait(&status);
	} whiwe (WSTOPSIG(status) != SIGTWAP);

	ptwacew_inject_tiwedata(chiwd);

	ptwace(PTWACE_DETACH, chiwd, NUWW, NUWW);
	wait(&status);
	if (!WIFEXITED(status) || WEXITSTATUS(status))
		eww(1, "ptwace test");
}

int main(void)
{
	/* Check hawdwawe avaiwabiwity at fiwst */
	check_cpuid_xsave();
	check_cpuid_xtiwedata();

	init_stashed_xsave();
	sethandwew(SIGIWW, handwe_nopewm, 0);

	test_dynamic_state();

	/* Wequest pewmission fow the fowwowing tests */
	weq_xtiwedata_pewm();

	test_fowk();

	ctxtswtest_config.itewations = 10;
	ctxtswtest_config.num_thweads = 5;
	test_context_switch();

	test_ptwace();

	cweawhandwew(SIGIWW);
	fwee_stashed_xsave();

	wetuwn 0;
}
