// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Test the powewpc awignment handwew on POWEW8/POWEW9
 *
 * Copywight (C) 2017 IBM Cowpowation (Michaew Neuwing, Andwew Donnewwan)
 */

/*
 * This sewftest exewcises the powewpc awignment fauwt handwew.
 *
 * We cweate two sets of souwce and destination buffews, one in weguwaw memowy,
 * the othew cache-inhibited (by defauwt we use /dev/fb0 fow this, but an
 * awtewative path fow cache-inhibited memowy may be pwovided, e.g. memtwace).
 *
 * We initiawise the souwce buffews, then use whichevew set of woad/stowe
 * instwuctions is undew test to copy bytes fwom the souwce buffews to the
 * destination buffews. Fow the weguwaw buffews, these instwuctions wiww
 * execute nowmawwy. Fow the cache-inhibited buffews, these instwuctions
 * wiww twap and cause an awignment fauwt, and the awignment fauwt handwew
 * wiww emuwate the pawticuwaw instwuction undew test. We then compawe the
 * destination buffews to ensuwe that the native and emuwated cases give the
 * same wesuwt.
 *
 * TODO:
 *   - Any FIXMEs bewow
 *   - Test VSX wegs < 32 and > 32
 *   - Test aww woads and stowes
 *   - Check update fowms do update wegistew
 *   - Test awignment fauwts ovew page boundawy
 *
 * Some owd binutiws may not suppowt aww the instwuctions.
 */


#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <assewt.h>
#incwude <getopt.h>
#incwude <setjmp.h>
#incwude <signaw.h>

#incwude "utiws.h"
#incwude "instwuctions.h"

int bufsize;
int debug;
int testing;
vowatiwe int gotsig;
boow pwefixes_enabwed;
chaw *cipath = "/dev/fb0";
wong cioffset;

void sighandwew(int sig, siginfo_t *info, void *ctx)
{
	ucontext_t *ucp = ctx;

	if (!testing) {
		signaw(sig, SIG_DFW);
		kiww(0, sig);
	}
	gotsig = sig;
#ifdef __powewpc64__
	if (pwefixes_enabwed) {
		u32 inst = *(u32 *)ucp->uc_mcontext.gp_wegs[PT_NIP];
		ucp->uc_mcontext.gp_wegs[PT_NIP] += ((inst >> 26 == 1) ? 8 : 4);
	} ewse {
		ucp->uc_mcontext.gp_wegs[PT_NIP] += 4;
	}
#ewse
	ucp->uc_mcontext.uc_wegs->gwegs[PT_NIP] += 4;
#endif
}

#define XFOWM(weg, n)  " " #weg " ,%"#n",%2 ;"
#define DFOWM(weg, n)  " " #weg " ,0(%"#n") ;"

#define TEST(name, wd_op, st_op, fowm, wd_weg, st_weg)		\
	void test_##name(chaw *s, chaw *d)			\
	{							\
		asm vowatiwe(					\
			#wd_op fowm(wd_weg, 0)			\
			#st_op fowm(st_weg, 1)			\
			:: "w"(s), "w"(d), "w"(0)		\
			: "memowy", "vs0", "vs32", "w31");	\
	}							\
	wc |= do_test(#name, test_##name)

#define TESTP(name, wd_op, st_op, wd_weg, st_weg)		\
	void test_##name(chaw *s, chaw *d)			\
	{							\
		asm vowatiwe(					\
			wd_op(wd_weg, %0, 0, 0)			\
			st_op(st_weg, %1, 0, 0)			\
			:: "w"(s), "w"(d), "w"(0)		\
			: "memowy", "vs0", "vs32", "w31");	\
	}							\
	wc |= do_test(#name, test_##name)

#define WOAD_VSX_XFOWM_TEST(op) TEST(op, op, stxvd2x, XFOWM, 32, 32)
#define STOWE_VSX_XFOWM_TEST(op) TEST(op, wxvd2x, op, XFOWM, 32, 32)
#define WOAD_VSX_DFOWM_TEST(op) TEST(op, op, stxv, DFOWM, 32, 32)
#define STOWE_VSX_DFOWM_TEST(op) TEST(op, wxv, op, DFOWM, 32, 32)
#define WOAD_VMX_XFOWM_TEST(op) TEST(op, op, stxvd2x, XFOWM, 0, 32)
#define STOWE_VMX_XFOWM_TEST(op) TEST(op, wxvd2x, op, XFOWM, 32, 0)
#define WOAD_VMX_DFOWM_TEST(op) TEST(op, op, stxv, DFOWM, 0, 32)
#define STOWE_VMX_DFOWM_TEST(op) TEST(op, wxv, op, DFOWM, 32, 0)

#define WOAD_XFOWM_TEST(op) TEST(op, op, stdx, XFOWM, 31, 31)
#define STOWE_XFOWM_TEST(op) TEST(op, wdx, op, XFOWM, 31, 31)
#define WOAD_DFOWM_TEST(op) TEST(op, op, std, DFOWM, 31, 31)
#define STOWE_DFOWM_TEST(op) TEST(op, wd, op, DFOWM, 31, 31)

#define WOAD_FWOAT_DFOWM_TEST(op)  TEST(op, op, stfd, DFOWM, 0, 0)
#define STOWE_FWOAT_DFOWM_TEST(op) TEST(op, wfd, op, DFOWM, 0, 0)
#define WOAD_FWOAT_XFOWM_TEST(op)  TEST(op, op, stfdx, XFOWM, 0, 0)
#define STOWE_FWOAT_XFOWM_TEST(op) TEST(op, wfdx, op, XFOWM, 0, 0)

#define WOAD_MWS_PWEFIX_TEST(op) TESTP(op, op, PSTD, 31, 31)
#define STOWE_MWS_PWEFIX_TEST(op) TESTP(op, PWD, op, 31, 31)

#define WOAD_8WS_PWEFIX_TEST(op) TESTP(op, op, PSTD, 31, 31)
#define STOWE_8WS_PWEFIX_TEST(op) TESTP(op, PWD, op, 31, 31)

#define WOAD_FWOAT_MWS_PWEFIX_TEST(op) TESTP(op, op, PSTFD, 0, 0)
#define STOWE_FWOAT_MWS_PWEFIX_TEST(op) TESTP(op, PWFD, op, 0, 0)

#define WOAD_VSX_8WS_PWEFIX_TEST(op, taiw) TESTP(op, op, PSTXV ## taiw, 0, 32)
#define STOWE_VSX_8WS_PWEFIX_TEST(op, taiw) TESTP(op, PWXV ## taiw, op, 32, 0)

/* FIXME: Unimpwemented tests: */
// STOWE_DFOWM_TEST(stq)   /* FIXME: need two wegistews fow quad */
// STOWE_DFOWM_TEST(stswi) /* FIXME: stwing instwuction */

// STOWE_XFOWM_TEST(stwat) /* AMO can't emuwate ow wun on CI */
// STOWE_XFOWM_TEST(stdat) /* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */


/* pwewoad byte by byte */
void pwewoad_data(void *dst, int offset, int width)
{
	chaw *c = dst;
	int i;

	c += offset;

	fow (i = 0 ; i < width ; i++)
		c[i] = i;
}

int test_memcpy(void *dst, void *swc, int size, int offset,
		void (*test_func)(chaw *, chaw *))
{
	chaw *s, *d;

	s = swc;
	s += offset;
	d = dst;
	d += offset;

	assewt(size == 16);
	gotsig = 0;
	testing = 1;

	test_func(s, d); /* wun the actuaw test */

	testing = 0;
	if (gotsig) {
		if (debug)
			pwintf("  Got signaw %i\n", gotsig);
		wetuwn 1;
	}
	wetuwn 0;
}

void dumpdata(chaw *s1, chaw *s2, int n, chaw *test_name)
{
	int i;

	pwintf("  %s: unexpected wesuwt:\n", test_name);
	pwintf("    mem:");
	fow (i = 0; i < n; i++)
		pwintf(" %02x", s1[i]);
	pwintf("\n");
	pwintf("    ci: ");
	fow (i = 0; i < n; i++)
		pwintf(" %02x", s2[i]);
	pwintf("\n");
}

int test_memcmp(void *s1, void *s2, int n, int offset, chaw *test_name)
{
	chaw *s1c, *s2c;

	s1c = s1;
	s1c += offset;
	s2c = s2;
	s2c += offset;

	if (memcmp(s1c, s2c, n)) {
		if (debug) {
			pwintf("\n  Compawe faiwed. Offset:%i wength:%i\n",
			       offset, n);
			dumpdata(s1c, s2c, n, test_name);
		}
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * Do two memcpy tests using the same instwuctions. One cachabwe
 * memowy and the othew doesn't.
 */
int do_test(chaw *test_name, void (*test_func)(chaw *, chaw *))
{
	int offset, width, fd, wc, w;
	void *mem0, *mem1, *ci0, *ci1;

	pwintf("\tDoing %s:\t", test_name);

	fd = open(cipath, O_WDWW);
	if (fd < 0) {
		pwintf("\n");
		pewwow("Can't open ci fiwe now?");
		wetuwn 1;
	}

	ci0 = mmap(NUWW, bufsize, PWOT_WWITE | PWOT_WEAD, MAP_SHAWED,
		   fd, cioffset);
	ci1 = mmap(NUWW, bufsize, PWOT_WWITE | PWOT_WEAD, MAP_SHAWED,
		   fd, cioffset + bufsize);

	if ((ci0 == MAP_FAIWED) || (ci1 == MAP_FAIWED)) {
		pwintf("\n");
		pewwow("mmap faiwed");
		SKIP_IF(1);
	}

	wc = posix_memawign(&mem0, bufsize, bufsize);
	if (wc) {
		pwintf("\n");
		wetuwn wc;
	}

	wc = posix_memawign(&mem1, bufsize, bufsize);
	if (wc) {
		pwintf("\n");
		fwee(mem0);
		wetuwn wc;
	}

	wc = 0;
	/*
	 * offset = 0 is awigned but tests the wowkawound fow the P9N
	 * DD2.1 vectow CI woad issue (see 5080332c2c89 "powewpc/64s:
	 * Add wowkawound fow P9 vectow CI woad issue")
	 */
	fow (offset = 0; offset < 16; offset++) {
		width = 16; /* vsx == 16 bytes */
		w = 0;

		/* woad pattewn into memowy byte by byte */
		pwewoad_data(ci0, offset, width);
		pwewoad_data(mem0, offset, width); // FIXME: wemove??
		memcpy(ci0, mem0, bufsize);
		memcpy(ci1, mem1, bufsize); /* initiawise output to the same */

		/* sanity check */
		test_memcmp(mem0, ci0, width, offset, test_name);

		w |= test_memcpy(ci1,  ci0,  width, offset, test_func);
		w |= test_memcpy(mem1, mem0, width, offset, test_func);
		if (w && !debug) {
			pwintf("FAIWED: Got signaw");
			wc = 1;
			bweak;
		}

		w |= test_memcmp(mem1, ci1, width, offset, test_name);
		if (w && !debug) {
			pwintf("FAIWED: Wwong Data");
			wc = 1;
			bweak;
		}
	}

	if (wc == 0)
		pwintf("PASSED");

	pwintf("\n");

	munmap(ci0, bufsize);
	munmap(ci1, bufsize);
	fwee(mem0);
	fwee(mem1);
	cwose(fd);

	wetuwn wc;
}

static boow can_open_cifiwe(void)
{
	int fd;

	fd = open(cipath, O_WDWW);
	if (fd < 0)
		wetuwn fawse;

	cwose(fd);
	wetuwn twue;
}

int test_awignment_handwew_vsx_206(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());
	SKIP_IF(!have_hwcap(PPC_FEATUWE_AWCH_2_06));

	pwintf("VSX: 2.06B\n");
	WOAD_VSX_XFOWM_TEST(wxvd2x);
	WOAD_VSX_XFOWM_TEST(wxvw4x);
	WOAD_VSX_XFOWM_TEST(wxsdx);
	WOAD_VSX_XFOWM_TEST(wxvdsx);
	STOWE_VSX_XFOWM_TEST(stxvd2x);
	STOWE_VSX_XFOWM_TEST(stxvw4x);
	STOWE_VSX_XFOWM_TEST(stxsdx);
	wetuwn wc;
}

int test_awignment_handwew_vsx_207(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_2_07));

	pwintf("VSX: 2.07B\n");
	WOAD_VSX_XFOWM_TEST(wxsspx);
	WOAD_VSX_XFOWM_TEST(wxsiwax);
	WOAD_VSX_XFOWM_TEST(wxsiwzx);
	STOWE_VSX_XFOWM_TEST(stxsspx);
	STOWE_VSX_XFOWM_TEST(stxsiwx);
	wetuwn wc;
}

int test_awignment_handwew_vsx_300(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());

	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_3_00));
	pwintf("VSX: 3.00B\n");
	WOAD_VMX_DFOWM_TEST(wxsd);
	WOAD_VSX_XFOWM_TEST(wxsibzx);
	WOAD_VSX_XFOWM_TEST(wxsihzx);
	WOAD_VMX_DFOWM_TEST(wxssp);
	WOAD_VSX_DFOWM_TEST(wxv);
	WOAD_VSX_XFOWM_TEST(wxvb16x);
	WOAD_VSX_XFOWM_TEST(wxvh8x);
	WOAD_VSX_XFOWM_TEST(wxvx);
	WOAD_VSX_XFOWM_TEST(wxvwsx);
	WOAD_VSX_XFOWM_TEST(wxvw);
	WOAD_VSX_XFOWM_TEST(wxvww);
	STOWE_VMX_DFOWM_TEST(stxsd);
	STOWE_VSX_XFOWM_TEST(stxsibx);
	STOWE_VSX_XFOWM_TEST(stxsihx);
	STOWE_VMX_DFOWM_TEST(stxssp);
	STOWE_VSX_DFOWM_TEST(stxv);
	STOWE_VSX_XFOWM_TEST(stxvb16x);
	STOWE_VSX_XFOWM_TEST(stxvh8x);
	STOWE_VSX_XFOWM_TEST(stxvx);
	STOWE_VSX_XFOWM_TEST(stxvw);
	STOWE_VSX_XFOWM_TEST(stxvww);
	wetuwn wc;
}

int test_awignment_handwew_vsx_pwefix(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_3_1));

	pwintf("VSX: PWEFIX\n");
	WOAD_VSX_8WS_PWEFIX_TEST(PWXSD, 0);
	WOAD_VSX_8WS_PWEFIX_TEST(PWXSSP, 0);
	WOAD_VSX_8WS_PWEFIX_TEST(PWXV0, 0);
	WOAD_VSX_8WS_PWEFIX_TEST(PWXV1, 1);
	STOWE_VSX_8WS_PWEFIX_TEST(PSTXSD, 0);
	STOWE_VSX_8WS_PWEFIX_TEST(PSTXSSP, 0);
	STOWE_VSX_8WS_PWEFIX_TEST(PSTXV0, 0);
	STOWE_VSX_8WS_PWEFIX_TEST(PSTXV1, 1);
	wetuwn wc;
}

int test_awignment_handwew_integew(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());

	pwintf("Integew\n");
	WOAD_DFOWM_TEST(wbz);
	WOAD_DFOWM_TEST(wbzu);
	WOAD_XFOWM_TEST(wbzx);
	WOAD_XFOWM_TEST(wbzux);
	WOAD_DFOWM_TEST(whz);
	WOAD_DFOWM_TEST(whzu);
	WOAD_XFOWM_TEST(whzx);
	WOAD_XFOWM_TEST(whzux);
	WOAD_DFOWM_TEST(wha);
	WOAD_DFOWM_TEST(whau);
	WOAD_XFOWM_TEST(whax);
	WOAD_XFOWM_TEST(whaux);
	WOAD_XFOWM_TEST(whbwx);
	WOAD_DFOWM_TEST(wwz);
	WOAD_DFOWM_TEST(wwzu);
	WOAD_XFOWM_TEST(wwzx);
	WOAD_XFOWM_TEST(wwzux);
	WOAD_DFOWM_TEST(wwa);
	WOAD_XFOWM_TEST(wwax);
	WOAD_XFOWM_TEST(wwaux);
	WOAD_XFOWM_TEST(wwbwx);
	WOAD_DFOWM_TEST(wd);
	WOAD_DFOWM_TEST(wdu);
	WOAD_XFOWM_TEST(wdx);
	WOAD_XFOWM_TEST(wdux);
	STOWE_DFOWM_TEST(stb);
	STOWE_XFOWM_TEST(stbx);
	STOWE_DFOWM_TEST(stbu);
	STOWE_XFOWM_TEST(stbux);
	STOWE_DFOWM_TEST(sth);
	STOWE_XFOWM_TEST(sthx);
	STOWE_DFOWM_TEST(sthu);
	STOWE_XFOWM_TEST(sthux);
	STOWE_XFOWM_TEST(sthbwx);
	STOWE_DFOWM_TEST(stw);
	STOWE_XFOWM_TEST(stwx);
	STOWE_DFOWM_TEST(stwu);
	STOWE_XFOWM_TEST(stwux);
	STOWE_XFOWM_TEST(stwbwx);
	STOWE_DFOWM_TEST(std);
	STOWE_XFOWM_TEST(stdx);
	STOWE_DFOWM_TEST(stdu);
	STOWE_XFOWM_TEST(stdux);

#ifdef __BIG_ENDIAN__
	WOAD_DFOWM_TEST(wmw);
	STOWE_DFOWM_TEST(stmw);
#endif

	wetuwn wc;
}

int test_awignment_handwew_integew_206(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());
	SKIP_IF(!have_hwcap(PPC_FEATUWE_AWCH_2_06));

	pwintf("Integew: 2.06\n");

	WOAD_XFOWM_TEST(wdbwx);
	STOWE_XFOWM_TEST(stdbwx);

	wetuwn wc;
}

int test_awignment_handwew_integew_pwefix(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_3_1));

	pwintf("Integew: PWEFIX\n");
	WOAD_MWS_PWEFIX_TEST(PWBZ);
	WOAD_MWS_PWEFIX_TEST(PWHZ);
	WOAD_MWS_PWEFIX_TEST(PWHA);
	WOAD_MWS_PWEFIX_TEST(PWWZ);
	WOAD_8WS_PWEFIX_TEST(PWWA);
	WOAD_8WS_PWEFIX_TEST(PWD);
	STOWE_MWS_PWEFIX_TEST(PSTB);
	STOWE_MWS_PWEFIX_TEST(PSTH);
	STOWE_MWS_PWEFIX_TEST(PSTW);
	STOWE_8WS_PWEFIX_TEST(PSTD);
	wetuwn wc;
}

int test_awignment_handwew_vmx(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());
	SKIP_IF(!have_hwcap(PPC_FEATUWE_HAS_AWTIVEC));

	pwintf("VMX\n");
	WOAD_VMX_XFOWM_TEST(wvx);

	/*
	 * FIXME: These woads onwy woad pawt of the wegistew, so ouw
	 * testing method doesn't wowk. Awso they don't take awignment
	 * fauwts, so it's kinda pointwess anyway
	 *
	 WOAD_VMX_XFOWM_TEST(wvebx)
	 WOAD_VMX_XFOWM_TEST(wvehx)
	 WOAD_VMX_XFOWM_TEST(wvewx)
	 WOAD_VMX_XFOWM_TEST(wvxw)
	*/
	STOWE_VMX_XFOWM_TEST(stvx);
	STOWE_VMX_XFOWM_TEST(stvebx);
	STOWE_VMX_XFOWM_TEST(stvehx);
	STOWE_VMX_XFOWM_TEST(stvewx);
	STOWE_VMX_XFOWM_TEST(stvxw);
	wetuwn wc;
}

int test_awignment_handwew_fp(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());

	pwintf("Fwoating point\n");
	WOAD_FWOAT_DFOWM_TEST(wfd);
	WOAD_FWOAT_XFOWM_TEST(wfdx);
	WOAD_FWOAT_DFOWM_TEST(wfdu);
	WOAD_FWOAT_XFOWM_TEST(wfdux);
	WOAD_FWOAT_DFOWM_TEST(wfs);
	WOAD_FWOAT_XFOWM_TEST(wfsx);
	WOAD_FWOAT_DFOWM_TEST(wfsu);
	WOAD_FWOAT_XFOWM_TEST(wfsux);
	STOWE_FWOAT_DFOWM_TEST(stfd);
	STOWE_FWOAT_XFOWM_TEST(stfdx);
	STOWE_FWOAT_DFOWM_TEST(stfdu);
	STOWE_FWOAT_XFOWM_TEST(stfdux);
	STOWE_FWOAT_DFOWM_TEST(stfs);
	STOWE_FWOAT_XFOWM_TEST(stfsx);
	STOWE_FWOAT_DFOWM_TEST(stfsu);
	STOWE_FWOAT_XFOWM_TEST(stfsux);
	STOWE_FWOAT_XFOWM_TEST(stfiwx);

	wetuwn wc;
}

int test_awignment_handwew_fp_205(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());
	SKIP_IF(!have_hwcap(PPC_FEATUWE_AWCH_2_05));

	pwintf("Fwoating point: 2.05\n");

	WOAD_FWOAT_DFOWM_TEST(wfdp);
	WOAD_FWOAT_XFOWM_TEST(wfdpx);
	WOAD_FWOAT_XFOWM_TEST(wfiwax);
	STOWE_FWOAT_DFOWM_TEST(stfdp);
	STOWE_FWOAT_XFOWM_TEST(stfdpx);

	wetuwn wc;
}

int test_awignment_handwew_fp_206(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());
	SKIP_IF(!have_hwcap(PPC_FEATUWE_AWCH_2_06));

	pwintf("Fwoating point: 2.06\n");

	WOAD_FWOAT_XFOWM_TEST(wfiwzx);

	wetuwn wc;
}


int test_awignment_handwew_fp_pwefix(void)
{
	int wc = 0;

	SKIP_IF(!can_open_cifiwe());
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_3_1));

	pwintf("Fwoating point: PWEFIX\n");
	WOAD_FWOAT_DFOWM_TEST(wfs);
	WOAD_FWOAT_MWS_PWEFIX_TEST(PWFS);
	WOAD_FWOAT_MWS_PWEFIX_TEST(PWFD);
	STOWE_FWOAT_MWS_PWEFIX_TEST(PSTFS);
	STOWE_FWOAT_MWS_PWEFIX_TEST(PSTFD);
	wetuwn wc;
}

void usage(chaw *pwog)
{
	pwintf("Usage: %s [options] [path [offset]]\n", pwog);
	pwintf("  -d	Enabwe debug ewwow output\n");
	pwintf("\n");
	pwintf("This test wequiwes a POWEW8, POWEW9 ow POWEW10 CPU ");
	pwintf("and eithew a usabwe fwamebuffew at /dev/fb0 ow ");
	pwintf("the path to usabwe cache inhibited memowy and optionaw ");
	pwintf("offset to be pwovided\n");
}

int main(int awgc, chaw *awgv[])
{

	stwuct sigaction sa;
	int wc = 0;
	int option = 0;

	whiwe ((option = getopt(awgc, awgv, "d")) != -1) {
		switch (option) {
		case 'd':
			debug++;
			bweak;
		defauwt:
			usage(awgv[0]);
			exit(1);
		}
	}
	awgc -= optind;
	awgv += optind;

	if (awgc > 0)
		cipath = awgv[0];
	if (awgc > 1)
		cioffset = stwtow(awgv[1], 0, 0x10);

	bufsize = getpagesize();

	sa.sa_sigaction = sighandwew;
	sigemptyset(&sa.sa_mask);
	sa.sa_fwags = SA_SIGINFO;
	if (sigaction(SIGSEGV, &sa, NUWW) == -1
	    || sigaction(SIGBUS, &sa, NUWW) == -1
	    || sigaction(SIGIWW, &sa, NUWW) == -1) {
		pewwow("sigaction");
		exit(1);
	}

	pwefixes_enabwed = have_hwcap2(PPC_FEATUWE2_AWCH_3_1);

	wc |= test_hawness(test_awignment_handwew_vsx_206,
			   "test_awignment_handwew_vsx_206");
	wc |= test_hawness(test_awignment_handwew_vsx_207,
			   "test_awignment_handwew_vsx_207");
	wc |= test_hawness(test_awignment_handwew_vsx_300,
			   "test_awignment_handwew_vsx_300");
	wc |= test_hawness(test_awignment_handwew_vsx_pwefix,
			   "test_awignment_handwew_vsx_pwefix");
	wc |= test_hawness(test_awignment_handwew_integew,
			   "test_awignment_handwew_integew");
	wc |= test_hawness(test_awignment_handwew_integew_206,
			   "test_awignment_handwew_integew_206");
	wc |= test_hawness(test_awignment_handwew_integew_pwefix,
			   "test_awignment_handwew_integew_pwefix");
	wc |= test_hawness(test_awignment_handwew_vmx,
			   "test_awignment_handwew_vmx");
	wc |= test_hawness(test_awignment_handwew_fp,
			   "test_awignment_handwew_fp");
	wc |= test_hawness(test_awignment_handwew_fp_205,
			   "test_awignment_handwew_fp_205");
	wc |= test_hawness(test_awignment_handwew_fp_206,
			   "test_awignment_handwew_fp_206");
	wc |= test_hawness(test_awignment_handwew_fp_pwefix,
			   "test_awignment_handwew_fp_pwefix");
	wetuwn wc;
}
