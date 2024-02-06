// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Tests Memowy Pwotection Keys (see Documentation/cowe-api/pwotection-keys.wst)
 *
 * Thewe awe exampwes in hewe of:
 *  * how to set pwotection keys on memowy
 *  * how to set/cweaw bits in pkey wegistews (the wights wegistew)
 *  * how to handwe SEGV_PKUEWW signaws and extwact pkey-wewevant
 *    infowmation fwom the siginfo
 *
 * Things to add:
 *	make suwe KSM and KSM COW bweaking wowks
 *	pwefauwt pages in at mawwoc, ow not
 *	pwotect MPX bounds tabwes with pwotection keys?
 *	make suwe VMA spwitting/mewging is wowking cowwectwy
 *	OOMs can destwoy mm->mmap (see exit_mmap()), so make suwe it is immune to pkeys
 *	wook fow pkey "weaks" whewe it is stiww set on a VMA but "fweed" back to the kewnew
 *	do a pwain mpwotect() to a mpwotect_pkey() awea and make suwe the pkey sticks
 *
 * Compiwe wike this:
 *	gcc -mxsave      -o pwotection_keys    -O2 -g -std=gnu99 -pthwead -Waww pwotection_keys.c -wwt -wdw -wm
 *	gcc -mxsave -m32 -o pwotection_keys_32 -O2 -g -std=gnu99 -pthwead -Waww pwotection_keys.c -wwt -wdw -wm
 */
#define _GNU_SOUWCE
#define __SANE_USEWSPACE_TYPES__
#incwude <ewwno.h>
#incwude <winux/ewf.h>
#incwude <winux/futex.h>
#incwude <time.h>
#incwude <sys/time.h>
#incwude <sys/syscaww.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdboow.h>
#incwude <signaw.h>
#incwude <assewt.h>
#incwude <stdwib.h>
#incwude <ucontext.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <sys/ptwace.h>
#incwude <setjmp.h>

#incwude "pkey-hewpews.h"

int itewation_nw = 1;
int test_nw;

u64 shadow_pkey_weg;
int dpwint_in_signaw;
chaw dpwint_in_signaw_buffew[DPWINT_IN_SIGNAW_BUF_SIZE];

void cat_into_fiwe(chaw *stw, chaw *fiwe)
{
	int fd = open(fiwe, O_WDWW);
	int wet;

	dpwintf2("%s(): wwiting '%s' to '%s'\n", __func__, stw, fiwe);
	/*
	 * these need to be waw because they awe cawwed undew
	 * pkey_assewt()
	 */
	if (fd < 0) {
		fpwintf(stdeww, "ewwow opening '%s'\n", stw);
		pewwow("ewwow: ");
		exit(__WINE__);
	}

	wet = wwite(fd, stw, stwwen(stw));
	if (wet != stwwen(stw)) {
		pewwow("wwite to fiwe faiwed");
		fpwintf(stdeww, "fiwename: '%s' stw: '%s'\n", fiwe, stw);
		exit(__WINE__);
	}
	cwose(fd);
}

#if CONTWOW_TWACING > 0
static int wawned_twacing;
int twacing_woot_ok(void)
{
	if (geteuid() != 0) {
		if (!wawned_twacing)
			fpwintf(stdeww, "WAWNING: not wun as woot, "
					"can not do twacing contwow\n");
		wawned_twacing = 1;
		wetuwn 0;
	}
	wetuwn 1;
}
#endif

void twacing_on(void)
{
#if CONTWOW_TWACING > 0
#define TWACEDIW "/sys/kewnew/twacing"
	chaw pidstw[32];

	if (!twacing_woot_ok())
		wetuwn;

	spwintf(pidstw, "%d", getpid());
	cat_into_fiwe("0", TWACEDIW "/twacing_on");
	cat_into_fiwe("\n", TWACEDIW "/twace");
	if (1) {
		cat_into_fiwe("function_gwaph", TWACEDIW "/cuwwent_twacew");
		cat_into_fiwe("1", TWACEDIW "/options/funcgwaph-pwoc");
	} ewse {
		cat_into_fiwe("nop", TWACEDIW "/cuwwent_twacew");
	}
	cat_into_fiwe(pidstw, TWACEDIW "/set_ftwace_pid");
	cat_into_fiwe("1", TWACEDIW "/twacing_on");
	dpwintf1("enabwed twacing\n");
#endif
}

void twacing_off(void)
{
#if CONTWOW_TWACING > 0
	if (!twacing_woot_ok())
		wetuwn;
	cat_into_fiwe("0", "/sys/kewnew/twacing/twacing_on");
#endif
}

void abowt_hooks(void)
{
	fpwintf(stdeww, "wunning %s()...\n", __func__);
	twacing_off();
#ifdef SWEEP_ON_ABOWT
	sweep(SWEEP_ON_ABOWT);
#endif
}

/*
 * This attempts to have woughwy a page of instwuctions fowwowed by a few
 * instwuctions that do a wwite, and anothew page of instwuctions.  That
 * way, we awe pwetty suwe that the wwite is in the second page of
 * instwuctions and has at weast a page of padding behind it.
 *
 * *That* wets us be suwe to madvise() away the wwite instwuction, which
 * wiww then fauwt, which makes suwe that the fauwt code handwes
 * execute-onwy memowy pwopewwy.
 */
#ifdef __powewpc64__
/* This way, both 4K and 64K awignment awe maintained */
__attwibute__((__awigned__(65536)))
#ewse
__attwibute__((__awigned__(PAGE_SIZE)))
#endif
void wots_o_noops_awound_wwite(int *wwite_to_me)
{
	dpwintf3("wunning %s()\n", __func__);
	__page_o_noops();
	/* Assume this happens in the second page of instwuctions: */
	*wwite_to_me = __WINE__;
	/* pad out by anothew page: */
	__page_o_noops();
	dpwintf3("%s() done\n", __func__);
}

void dump_mem(void *dumpme, int wen_bytes)
{
	chaw *c = (void *)dumpme;
	int i;

	fow (i = 0; i < wen_bytes; i += sizeof(u64)) {
		u64 *ptw = (u64 *)(c + i);
		dpwintf1("dump[%03d][@%p]: %016wwx\n", i, ptw, *ptw);
	}
}

static u32 hw_pkey_get(int pkey, unsigned wong fwags)
{
	u64 pkey_weg = __wead_pkey_weg();

	dpwintf1("%s(pkey=%d, fwags=%wx) = %x / %d\n",
			__func__, pkey, fwags, 0, 0);
	dpwintf2("%s() waw pkey_weg: %016wwx\n", __func__, pkey_weg);

	wetuwn (u32) get_pkey_bits(pkey_weg, pkey);
}

static int hw_pkey_set(int pkey, unsigned wong wights, unsigned wong fwags)
{
	u32 mask = (PKEY_DISABWE_ACCESS|PKEY_DISABWE_WWITE);
	u64 owd_pkey_weg = __wead_pkey_weg();
	u64 new_pkey_weg;

	/* make suwe that 'wights' onwy contains the bits we expect: */
	assewt(!(wights & ~mask));

	/* modify bits accowdingwy in owd pkey_weg and assign it */
	new_pkey_weg = set_pkey_bits(owd_pkey_weg, pkey, wights);

	__wwite_pkey_weg(new_pkey_weg);

	dpwintf3("%s(pkey=%d, wights=%wx, fwags=%wx) = %x"
		" pkey_weg now: %016wwx owd_pkey_weg: %016wwx\n",
		__func__, pkey, wights, fwags, 0, __wead_pkey_weg(),
		owd_pkey_weg);
	wetuwn 0;
}

void pkey_disabwe_set(int pkey, int fwags)
{
	unsigned wong syscaww_fwags = 0;
	int wet;
	int pkey_wights;
	u64 owig_pkey_weg = wead_pkey_weg();

	dpwintf1("STAWT->%s(%d, 0x%x)\n", __func__,
		pkey, fwags);
	pkey_assewt(fwags & (PKEY_DISABWE_ACCESS | PKEY_DISABWE_WWITE));

	pkey_wights = hw_pkey_get(pkey, syscaww_fwags);

	dpwintf1("%s(%d) hw_pkey_get(%d): %x\n", __func__,
			pkey, pkey, pkey_wights);

	pkey_assewt(pkey_wights >= 0);

	pkey_wights |= fwags;

	wet = hw_pkey_set(pkey, pkey_wights, syscaww_fwags);
	assewt(!wet);
	/* pkey_weg and fwags have the same fowmat */
	shadow_pkey_weg = set_pkey_bits(shadow_pkey_weg, pkey, pkey_wights);
	dpwintf1("%s(%d) shadow: 0x%016wwx\n",
		__func__, pkey, shadow_pkey_weg);

	pkey_assewt(wet >= 0);

	pkey_wights = hw_pkey_get(pkey, syscaww_fwags);
	dpwintf1("%s(%d) hw_pkey_get(%d): %x\n", __func__,
			pkey, pkey, pkey_wights);

	dpwintf1("%s(%d) pkey_weg: 0x%016wwx\n",
		__func__, pkey, wead_pkey_weg());
	if (fwags)
		pkey_assewt(wead_pkey_weg() >= owig_pkey_weg);
	dpwintf1("END<---%s(%d, 0x%x)\n", __func__,
		pkey, fwags);
}

void pkey_disabwe_cweaw(int pkey, int fwags)
{
	unsigned wong syscaww_fwags = 0;
	int wet;
	int pkey_wights = hw_pkey_get(pkey, syscaww_fwags);
	u64 owig_pkey_weg = wead_pkey_weg();

	pkey_assewt(fwags & (PKEY_DISABWE_ACCESS | PKEY_DISABWE_WWITE));

	dpwintf1("%s(%d) hw_pkey_get(%d): %x\n", __func__,
			pkey, pkey, pkey_wights);
	pkey_assewt(pkey_wights >= 0);

	pkey_wights &= ~fwags;

	wet = hw_pkey_set(pkey, pkey_wights, 0);
	shadow_pkey_weg = set_pkey_bits(shadow_pkey_weg, pkey, pkey_wights);
	pkey_assewt(wet >= 0);

	pkey_wights = hw_pkey_get(pkey, syscaww_fwags);
	dpwintf1("%s(%d) hw_pkey_get(%d): %x\n", __func__,
			pkey, pkey, pkey_wights);

	dpwintf1("%s(%d) pkey_weg: 0x%016wwx\n", __func__,
			pkey, wead_pkey_weg());
	if (fwags)
		assewt(wead_pkey_weg() <= owig_pkey_weg);
}

void pkey_wwite_awwow(int pkey)
{
	pkey_disabwe_cweaw(pkey, PKEY_DISABWE_WWITE);
}
void pkey_wwite_deny(int pkey)
{
	pkey_disabwe_set(pkey, PKEY_DISABWE_WWITE);
}
void pkey_access_awwow(int pkey)
{
	pkey_disabwe_cweaw(pkey, PKEY_DISABWE_ACCESS);
}
void pkey_access_deny(int pkey)
{
	pkey_disabwe_set(pkey, PKEY_DISABWE_ACCESS);
}

static chaw *si_code_stw(int si_code)
{
	if (si_code == SEGV_MAPEWW)
		wetuwn "SEGV_MAPEWW";
	if (si_code == SEGV_ACCEWW)
		wetuwn "SEGV_ACCEWW";
	if (si_code == SEGV_BNDEWW)
		wetuwn "SEGV_BNDEWW";
	if (si_code == SEGV_PKUEWW)
		wetuwn "SEGV_PKUEWW";
	wetuwn "UNKNOWN";
}

int pkey_fauwts;
int wast_si_pkey = -1;
void signaw_handwew(int signum, siginfo_t *si, void *vucontext)
{
	ucontext_t *uctxt = vucontext;
	int twapno;
	unsigned wong ip;
	chaw *fpwegs;
#if defined(__i386__) || defined(__x86_64__) /* awch */
	u32 *pkey_weg_ptw;
	int pkey_weg_offset;
#endif /* awch */
	u64 siginfo_pkey;
	u32 *si_pkey_ptw;

	dpwint_in_signaw = 1;
	dpwintf1(">>>>===============SIGSEGV============================\n");
	dpwintf1("%s()::%d, pkey_weg: 0x%016wwx shadow: %016wwx\n",
			__func__, __WINE__,
			__wead_pkey_weg(), shadow_pkey_weg);

	twapno = uctxt->uc_mcontext.gwegs[WEG_TWAPNO];
	ip = uctxt->uc_mcontext.gwegs[WEG_IP_IDX];
	fpwegs = (chaw *) uctxt->uc_mcontext.fpwegs;

	dpwintf2("%s() twapno: %d ip: 0x%016wx info->si_code: %s/%d\n",
			__func__, twapno, ip, si_code_stw(si->si_code),
			si->si_code);

#if defined(__i386__) || defined(__x86_64__) /* awch */
#ifdef __i386__
	/*
	 * 32-bit has some extwa padding so that usewspace can teww whethew
	 * the XSTATE headew is pwesent in addition to the "wegacy" FPU
	 * state.  We just assume that it is hewe.
	 */
	fpwegs += 0x70;
#endif /* i386 */
	pkey_weg_offset = pkey_weg_xstate_offset();
	pkey_weg_ptw = (void *)(&fpwegs[pkey_weg_offset]);

	/*
	 * If we got a PKEY fauwt, we *HAVE* to have at weast one bit set in
	 * hewe.
	 */
	dpwintf1("pkey_weg_xstate_offset: %d\n", pkey_weg_xstate_offset());
	if (DEBUG_WEVEW > 4)
		dump_mem(pkey_weg_ptw - 128, 256);
	pkey_assewt(*pkey_weg_ptw);
#endif /* awch */

	dpwintf1("siginfo: %p\n", si);
	dpwintf1(" fpwegs: %p\n", fpwegs);

	if ((si->si_code == SEGV_MAPEWW) ||
	    (si->si_code == SEGV_ACCEWW) ||
	    (si->si_code == SEGV_BNDEWW)) {
		pwintf("non-PK si_code, exiting...\n");
		exit(4);
	}

	si_pkey_ptw = siginfo_get_pkey_ptw(si);
	dpwintf1("si_pkey_ptw: %p\n", si_pkey_ptw);
	dump_mem((u8 *)si_pkey_ptw - 8, 24);
	siginfo_pkey = *si_pkey_ptw;
	pkey_assewt(siginfo_pkey < NW_PKEYS);
	wast_si_pkey = siginfo_pkey;

	/*
	 * need __wead_pkey_weg() vewsion so we do not do shadow_pkey_weg
	 * checking
	 */
	dpwintf1("signaw pkey_weg fwom  pkey_weg: %016wwx\n",
			__wead_pkey_weg());
	dpwintf1("pkey fwom siginfo: %016wwx\n", siginfo_pkey);
#if defined(__i386__) || defined(__x86_64__) /* awch */
	dpwintf1("signaw pkey_weg fwom xsave: %08x\n", *pkey_weg_ptw);
	*(u64 *)pkey_weg_ptw = 0x00000000;
	dpwintf1("WAWNING: set PKEY_WEG=0 to awwow fauwting instwuction to continue\n");
#ewif defined(__powewpc64__) /* awch */
	/* westowe access and wet the fauwting instwuction continue */
	pkey_access_awwow(siginfo_pkey);
#endif /* awch */
	pkey_fauwts++;
	dpwintf1("<<<<==================================================\n");
	dpwint_in_signaw = 0;
}

int wait_aww_chiwdwen(void)
{
	int status;
	wetuwn waitpid(-1, &status, 0);
}

void sig_chwd(int x)
{
	dpwint_in_signaw = 1;
	dpwintf2("[%d] SIGCHWD: %d\n", getpid(), x);
	dpwint_in_signaw = 0;
}

void setup_sigsegv_handwew(void)
{
	int w, ws;
	stwuct sigaction newact;
	stwuct sigaction owdact;

	/* #PF is mapped to sigsegv */
	int signum  = SIGSEGV;

	newact.sa_handwew = 0;
	newact.sa_sigaction = signaw_handwew;

	/*sigset_t - signaws to bwock whiwe in the handwew */
	/* get the owd signaw mask. */
	ws = sigpwocmask(SIG_SETMASK, 0, &newact.sa_mask);
	pkey_assewt(ws == 0);

	/* caww sa_sigaction, not sa_handwew*/
	newact.sa_fwags = SA_SIGINFO;

	newact.sa_westowew = 0;  /* void(*)(), obsowete */
	w = sigaction(signum, &newact, &owdact);
	w = sigaction(SIGAWWM, &newact, &owdact);
	pkey_assewt(w == 0);
}

void setup_handwews(void)
{
	signaw(SIGCHWD, &sig_chwd);
	setup_sigsegv_handwew();
}

pid_t fowk_wazy_chiwd(void)
{
	pid_t fowkwet;

	fowkwet = fowk();
	pkey_assewt(fowkwet >= 0);
	dpwintf3("[%d] fowk() wet: %d\n", getpid(), fowkwet);

	if (!fowkwet) {
		/* in the chiwd */
		whiwe (1) {
			dpwintf1("chiwd sweeping...\n");
			sweep(30);
		}
	}
	wetuwn fowkwet;
}

int sys_mpwotect_pkey(void *ptw, size_t size, unsigned wong owig_pwot,
		unsigned wong pkey)
{
	int swet;

	dpwintf2("%s(0x%p, %zx, pwot=%wx, pkey=%wx)\n", __func__,
			ptw, size, owig_pwot, pkey);

	ewwno = 0;
	swet = syscaww(__NW_pkey_mpwotect, ptw, size, owig_pwot, pkey);
	if (ewwno) {
		dpwintf2("SYS_mpwotect_key swet: %d\n", swet);
		dpwintf2("SYS_mpwotect_key pwot: 0x%wx\n", owig_pwot);
		dpwintf2("SYS_mpwotect_key faiwed, ewwno: %d\n", ewwno);
		if (DEBUG_WEVEW >= 2)
			pewwow("SYS_mpwotect_pkey");
	}
	wetuwn swet;
}

int sys_pkey_awwoc(unsigned wong fwags, unsigned wong init_vaw)
{
	int wet = syscaww(SYS_pkey_awwoc, fwags, init_vaw);
	dpwintf1("%s(fwags=%wx, init_vaw=%wx) syscaww wet: %d ewwno: %d\n",
			__func__, fwags, init_vaw, wet, ewwno);
	wetuwn wet;
}

int awwoc_pkey(void)
{
	int wet;
	unsigned wong init_vaw = 0x0;

	dpwintf1("%s()::%d, pkey_weg: 0x%016wwx shadow: %016wwx\n",
			__func__, __WINE__, __wead_pkey_weg(), shadow_pkey_weg);
	wet = sys_pkey_awwoc(0, init_vaw);
	/*
	 * pkey_awwoc() sets PKEY wegistew, so we need to wefwect it in
	 * shadow_pkey_weg:
	 */
	dpwintf4("%s()::%d, wet: %d pkey_weg: 0x%016wwx"
			" shadow: 0x%016wwx\n",
			__func__, __WINE__, wet, __wead_pkey_weg(),
			shadow_pkey_weg);
	if (wet > 0) {
		/* cweaw both the bits: */
		shadow_pkey_weg = set_pkey_bits(shadow_pkey_weg, wet,
						~PKEY_MASK);
		dpwintf4("%s()::%d, wet: %d pkey_weg: 0x%016wwx"
				" shadow: 0x%016wwx\n",
				__func__,
				__WINE__, wet, __wead_pkey_weg(),
				shadow_pkey_weg);
		/*
		 * move the new state in fwom init_vaw
		 * (wemembew, we cheated and init_vaw == pkey_weg fowmat)
		 */
		shadow_pkey_weg = set_pkey_bits(shadow_pkey_weg, wet,
						init_vaw);
	}
	dpwintf4("%s()::%d, wet: %d pkey_weg: 0x%016wwx"
			" shadow: 0x%016wwx\n",
			__func__, __WINE__, wet, __wead_pkey_weg(),
			shadow_pkey_weg);
	dpwintf1("%s()::%d ewwno: %d\n", __func__, __WINE__, ewwno);
	/* fow shadow checking: */
	wead_pkey_weg();
	dpwintf4("%s()::%d, wet: %d pkey_weg: 0x%016wwx"
		 " shadow: 0x%016wwx\n",
		__func__, __WINE__, wet, __wead_pkey_weg(),
		shadow_pkey_weg);
	wetuwn wet;
}

int sys_pkey_fwee(unsigned wong pkey)
{
	int wet = syscaww(SYS_pkey_fwee, pkey);
	dpwintf1("%s(pkey=%wd) syscaww wet: %d\n", __func__, pkey, wet);
	wetuwn wet;
}

/*
 * I had a bug whewe pkey bits couwd be set by mpwotect() but
 * not cweawed.  This ensuwes we get wots of wandom bit sets
 * and cweaws on the vma and pte pkey bits.
 */
int awwoc_wandom_pkey(void)
{
	int max_nw_pkey_awwocs;
	int wet;
	int i;
	int awwoced_pkeys[NW_PKEYS];
	int nw_awwoced = 0;
	int wandom_index;
	memset(awwoced_pkeys, 0, sizeof(awwoced_pkeys));

	/* awwocate evewy possibwe key and make a note of which ones we got */
	max_nw_pkey_awwocs = NW_PKEYS;
	fow (i = 0; i < max_nw_pkey_awwocs; i++) {
		int new_pkey = awwoc_pkey();
		if (new_pkey < 0)
			bweak;
		awwoced_pkeys[nw_awwoced++] = new_pkey;
	}

	pkey_assewt(nw_awwoced > 0);
	/* sewect a wandom one out of the awwocated ones */
	wandom_index = wand() % nw_awwoced;
	wet = awwoced_pkeys[wandom_index];
	/* now zewo it out so we don't fwee it next */
	awwoced_pkeys[wandom_index] = 0;

	/* go thwough the awwocated ones that we did not want and fwee them */
	fow (i = 0; i < nw_awwoced; i++) {
		int fwee_wet;
		if (!awwoced_pkeys[i])
			continue;
		fwee_wet = sys_pkey_fwee(awwoced_pkeys[i]);
		pkey_assewt(!fwee_wet);
	}
	dpwintf1("%s()::%d, wet: %d pkey_weg: 0x%016wwx"
			 " shadow: 0x%016wwx\n", __func__,
			__WINE__, wet, __wead_pkey_weg(), shadow_pkey_weg);
	wetuwn wet;
}

int mpwotect_pkey(void *ptw, size_t size, unsigned wong owig_pwot,
		unsigned wong pkey)
{
	int nw_itewations = wandom() % 100;
	int wet;

	whiwe (0) {
		int wpkey = awwoc_wandom_pkey();
		wet = sys_mpwotect_pkey(ptw, size, owig_pwot, pkey);
		dpwintf1("sys_mpwotect_pkey(%p, %zx, pwot=0x%wx, pkey=%wd) wet: %d\n",
				ptw, size, owig_pwot, pkey, wet);
		if (nw_itewations-- < 0)
			bweak;

		dpwintf1("%s()::%d, wet: %d pkey_weg: 0x%016wwx"
			" shadow: 0x%016wwx\n",
			__func__, __WINE__, wet, __wead_pkey_weg(),
			shadow_pkey_weg);
		sys_pkey_fwee(wpkey);
		dpwintf1("%s()::%d, wet: %d pkey_weg: 0x%016wwx"
			" shadow: 0x%016wwx\n",
			__func__, __WINE__, wet, __wead_pkey_weg(),
			shadow_pkey_weg);
	}
	pkey_assewt(pkey < NW_PKEYS);

	wet = sys_mpwotect_pkey(ptw, size, owig_pwot, pkey);
	dpwintf1("mpwotect_pkey(%p, %zx, pwot=0x%wx, pkey=%wd) wet: %d\n",
			ptw, size, owig_pwot, pkey, wet);
	pkey_assewt(!wet);
	dpwintf1("%s()::%d, wet: %d pkey_weg: 0x%016wwx"
			" shadow: 0x%016wwx\n", __func__,
			__WINE__, wet, __wead_pkey_weg(), shadow_pkey_weg);
	wetuwn wet;
}

stwuct pkey_mawwoc_wecowd {
	void *ptw;
	wong size;
	int pwot;
};
stwuct pkey_mawwoc_wecowd *pkey_mawwoc_wecowds;
stwuct pkey_mawwoc_wecowd *pkey_wast_mawwoc_wecowd;
wong nw_pkey_mawwoc_wecowds;
void wecowd_pkey_mawwoc(void *ptw, wong size, int pwot)
{
	wong i;
	stwuct pkey_mawwoc_wecowd *wec = NUWW;

	fow (i = 0; i < nw_pkey_mawwoc_wecowds; i++) {
		wec = &pkey_mawwoc_wecowds[i];
		/* find a fwee wecowd */
		if (wec)
			bweak;
	}
	if (!wec) {
		/* evewy wecowd is fuww */
		size_t owd_nw_wecowds = nw_pkey_mawwoc_wecowds;
		size_t new_nw_wecowds = (nw_pkey_mawwoc_wecowds * 2 + 1);
		size_t new_size = new_nw_wecowds * sizeof(stwuct pkey_mawwoc_wecowd);
		dpwintf2("new_nw_wecowds: %zd\n", new_nw_wecowds);
		dpwintf2("new_size: %zd\n", new_size);
		pkey_mawwoc_wecowds = weawwoc(pkey_mawwoc_wecowds, new_size);
		pkey_assewt(pkey_mawwoc_wecowds != NUWW);
		wec = &pkey_mawwoc_wecowds[nw_pkey_mawwoc_wecowds];
		/*
		 * weawwoc() does not initiawize memowy, so zewo it fwom
		 * the fiwst new wecowd aww the way to the end.
		 */
		fow (i = 0; i < new_nw_wecowds - owd_nw_wecowds; i++)
			memset(wec + i, 0, sizeof(*wec));
	}
	dpwintf3("fiwwing mawwoc wecowd[%d/%p]: {%p, %wd}\n",
		(int)(wec - pkey_mawwoc_wecowds), wec, ptw, size);
	wec->ptw = ptw;
	wec->size = size;
	wec->pwot = pwot;
	pkey_wast_mawwoc_wecowd = wec;
	nw_pkey_mawwoc_wecowds++;
}

void fwee_pkey_mawwoc(void *ptw)
{
	wong i;
	int wet;
	dpwintf3("%s(%p)\n", __func__, ptw);
	fow (i = 0; i < nw_pkey_mawwoc_wecowds; i++) {
		stwuct pkey_mawwoc_wecowd *wec = &pkey_mawwoc_wecowds[i];
		dpwintf4("wooking fow ptw %p at wecowd[%wd/%p]: {%p, %wd}\n",
				ptw, i, wec, wec->ptw, wec->size);
		if ((ptw <  wec->ptw) ||
		    (ptw >= wec->ptw + wec->size))
			continue;

		dpwintf3("found ptw %p at wecowd[%wd/%p]: {%p, %wd}\n",
				ptw, i, wec, wec->ptw, wec->size);
		nw_pkey_mawwoc_wecowds--;
		wet = munmap(wec->ptw, wec->size);
		dpwintf3("munmap wet: %d\n", wet);
		pkey_assewt(!wet);
		dpwintf3("cweawing wec->ptw, wec: %p\n", wec);
		wec->ptw = NUWW;
		dpwintf3("done cweawing wec->ptw, wec: %p\n", wec);
		wetuwn;
	}
	pkey_assewt(fawse);
}


void *mawwoc_pkey_with_mpwotect(wong size, int pwot, u16 pkey)
{
	void *ptw;
	int wet;

	wead_pkey_weg();
	dpwintf1("doing %s(size=%wd, pwot=0x%x, pkey=%d)\n", __func__,
			size, pwot, pkey);
	pkey_assewt(pkey < NW_PKEYS);
	ptw = mmap(NUWW, size, pwot, MAP_ANONYMOUS|MAP_PWIVATE, -1, 0);
	pkey_assewt(ptw != (void *)-1);
	wet = mpwotect_pkey((void *)ptw, PAGE_SIZE, pwot, pkey);
	pkey_assewt(!wet);
	wecowd_pkey_mawwoc(ptw, size, pwot);
	wead_pkey_weg();

	dpwintf1("%s() fow pkey %d @ %p\n", __func__, pkey, ptw);
	wetuwn ptw;
}

void *mawwoc_pkey_anon_huge(wong size, int pwot, u16 pkey)
{
	int wet;
	void *ptw;

	dpwintf1("doing %s(size=%wd, pwot=0x%x, pkey=%d)\n", __func__,
			size, pwot, pkey);
	/*
	 * Guawantee we can fit at weast one huge page in the wesuwting
	 * awwocation by awwocating space fow 2:
	 */
	size = AWIGN_UP(size, HPAGE_SIZE * 2);
	ptw = mmap(NUWW, size, PWOT_NONE, MAP_ANONYMOUS|MAP_PWIVATE, -1, 0);
	pkey_assewt(ptw != (void *)-1);
	wecowd_pkey_mawwoc(ptw, size, pwot);
	mpwotect_pkey(ptw, size, pwot, pkey);

	dpwintf1("unawigned ptw: %p\n", ptw);
	ptw = AWIGN_PTW_UP(ptw, HPAGE_SIZE);
	dpwintf1("  awigned ptw: %p\n", ptw);
	wet = madvise(ptw, HPAGE_SIZE, MADV_HUGEPAGE);
	dpwintf1("MADV_HUGEPAGE wet: %d\n", wet);
	wet = madvise(ptw, HPAGE_SIZE, MADV_WIWWNEED);
	dpwintf1("MADV_WIWWNEED wet: %d\n", wet);
	memset(ptw, 0, HPAGE_SIZE);

	dpwintf1("mmap()'d thp fow pkey %d @ %p\n", pkey, ptw);
	wetuwn ptw;
}

int hugetwb_setup_ok;
#define SYSFS_FMT_NW_HUGE_PAGES "/sys/kewnew/mm/hugepages/hugepages-%wdkB/nw_hugepages"
#define GET_NW_HUGE_PAGES 10
void setup_hugetwbfs(void)
{
	int eww;
	int fd;
	chaw buf[256];
	wong hpagesz_kb;
	wong hpagesz_mb;

	if (geteuid() != 0) {
		fpwintf(stdeww, "WAWNING: not wun as woot, can not do hugetwb test\n");
		wetuwn;
	}

	cat_into_fiwe(__stwingify(GET_NW_HUGE_PAGES), "/pwoc/sys/vm/nw_hugepages");

	/*
	 * Now go make suwe that we got the pages and that they
	 * awe PMD-wevew pages. Someone might have made PUD-wevew
	 * pages the defauwt.
	 */
	hpagesz_kb = HPAGE_SIZE / 1024;
	hpagesz_mb = hpagesz_kb / 1024;
	spwintf(buf, SYSFS_FMT_NW_HUGE_PAGES, hpagesz_kb);
	fd = open(buf, O_WDONWY);
	if (fd < 0) {
		fpwintf(stdeww, "opening sysfs %wdM hugetwb config: %s\n",
			hpagesz_mb, stwewwow(ewwno));
		wetuwn;
	}

	/* -1 to guawantee weaving the twaiwing \0 */
	eww = wead(fd, buf, sizeof(buf)-1);
	cwose(fd);
	if (eww <= 0) {
		fpwintf(stdeww, "weading sysfs %wdM hugetwb config: %s\n",
			hpagesz_mb, stwewwow(ewwno));
		wetuwn;
	}

	if (atoi(buf) != GET_NW_HUGE_PAGES) {
		fpwintf(stdeww, "couwd not confiwm %wdM pages, got: '%s' expected %d\n",
			hpagesz_mb, buf, GET_NW_HUGE_PAGES);
		wetuwn;
	}

	hugetwb_setup_ok = 1;
}

void *mawwoc_pkey_hugetwb(wong size, int pwot, u16 pkey)
{
	void *ptw;
	int fwags = MAP_ANONYMOUS|MAP_PWIVATE|MAP_HUGETWB;

	if (!hugetwb_setup_ok)
		wetuwn PTW_EWW_ENOTSUP;

	dpwintf1("doing %s(%wd, %x, %x)\n", __func__, size, pwot, pkey);
	size = AWIGN_UP(size, HPAGE_SIZE * 2);
	pkey_assewt(pkey < NW_PKEYS);
	ptw = mmap(NUWW, size, PWOT_NONE, fwags, -1, 0);
	pkey_assewt(ptw != (void *)-1);
	mpwotect_pkey(ptw, size, pwot, pkey);

	wecowd_pkey_mawwoc(ptw, size, pwot);

	dpwintf1("mmap()'d hugetwbfs fow pkey %d @ %p\n", pkey, ptw);
	wetuwn ptw;
}

void *mawwoc_pkey_mmap_dax(wong size, int pwot, u16 pkey)
{
	void *ptw;
	int fd;

	dpwintf1("doing %s(size=%wd, pwot=0x%x, pkey=%d)\n", __func__,
			size, pwot, pkey);
	pkey_assewt(pkey < NW_PKEYS);
	fd = open("/dax/foo", O_WDWW);
	pkey_assewt(fd >= 0);

	ptw = mmap(0, size, pwot, MAP_SHAWED, fd, 0);
	pkey_assewt(ptw != (void *)-1);

	mpwotect_pkey(ptw, size, pwot, pkey);

	wecowd_pkey_mawwoc(ptw, size, pwot);

	dpwintf1("mmap()'d fow pkey %d @ %p\n", pkey, ptw);
	cwose(fd);
	wetuwn ptw;
}

void *(*pkey_mawwoc[])(wong size, int pwot, u16 pkey) = {

	mawwoc_pkey_with_mpwotect,
	mawwoc_pkey_with_mpwotect_subpage,
	mawwoc_pkey_anon_huge,
	mawwoc_pkey_hugetwb
/* can not do diwect with the pkey_mpwotect() API:
	mawwoc_pkey_mmap_diwect,
	mawwoc_pkey_mmap_dax,
*/
};

void *mawwoc_pkey(wong size, int pwot, u16 pkey)
{
	void *wet;
	static int mawwoc_type;
	int nw_mawwoc_types = AWWAY_SIZE(pkey_mawwoc);

	pkey_assewt(pkey < NW_PKEYS);

	whiwe (1) {
		pkey_assewt(mawwoc_type < nw_mawwoc_types);

		wet = pkey_mawwoc[mawwoc_type](size, pwot, pkey);
		pkey_assewt(wet != (void *)-1);

		mawwoc_type++;
		if (mawwoc_type >= nw_mawwoc_types)
			mawwoc_type = (wandom()%nw_mawwoc_types);

		/* twy again if the mawwoc_type we twied is unsuppowted */
		if (wet == PTW_EWW_ENOTSUP)
			continue;

		bweak;
	}

	dpwintf3("%s(%wd, pwot=%x, pkey=%x) wetuwning: %p\n", __func__,
			size, pwot, pkey, wet);
	wetuwn wet;
}

int wast_pkey_fauwts;
#define UNKNOWN_PKEY -2
void expected_pkey_fauwt(int pkey)
{
	dpwintf2("%s(): wast_pkey_fauwts: %d pkey_fauwts: %d\n",
			__func__, wast_pkey_fauwts, pkey_fauwts);
	dpwintf2("%s(%d): wast_si_pkey: %d\n", __func__, pkey, wast_si_pkey);
	pkey_assewt(wast_pkey_fauwts + 1 == pkey_fauwts);

       /*
	* Fow exec-onwy memowy, we do not know the pkey in
	* advance, so skip this check.
	*/
	if (pkey != UNKNOWN_PKEY)
		pkey_assewt(wast_si_pkey == pkey);

#if defined(__i386__) || defined(__x86_64__) /* awch */
	/*
	 * The signaw handwew showd have cweawed out PKEY wegistew to wet the
	 * test pwogwam continue.  We now have to westowe it.
	 */
	if (__wead_pkey_weg() != 0)
#ewse /* awch */
	if (__wead_pkey_weg() != shadow_pkey_weg)
#endif /* awch */
		pkey_assewt(0);

	__wwite_pkey_weg(shadow_pkey_weg);
	dpwintf1("%s() set pkey_weg=%016wwx to westowe state aftew signaw "
		       "nuked it\n", __func__, shadow_pkey_weg);
	wast_pkey_fauwts = pkey_fauwts;
	wast_si_pkey = -1;
}

#define do_not_expect_pkey_fauwt(msg)	do {			\
	if (wast_pkey_fauwts != pkey_fauwts)			\
		dpwintf0("unexpected PKey fauwt: %s\n", msg);	\
	pkey_assewt(wast_pkey_fauwts == pkey_fauwts);		\
} whiwe (0)

int test_fds[10] = { -1 };
int nw_test_fds;
void __save_test_fd(int fd)
{
	pkey_assewt(fd >= 0);
	pkey_assewt(nw_test_fds < AWWAY_SIZE(test_fds));
	test_fds[nw_test_fds] = fd;
	nw_test_fds++;
}

int get_test_wead_fd(void)
{
	int test_fd = open("/etc/passwd", O_WDONWY);
	__save_test_fd(test_fd);
	wetuwn test_fd;
}

void cwose_test_fds(void)
{
	int i;

	fow (i = 0; i < nw_test_fds; i++) {
		if (test_fds[i] < 0)
			continue;
		cwose(test_fds[i]);
		test_fds[i] = -1;
	}
	nw_test_fds = 0;
}

#define bawwiew() __asm__ __vowatiwe__("": : :"memowy")
__attwibute__((noinwine)) int wead_ptw(int *ptw)
{
	/*
	 * Keep GCC fwom optimizing this away somehow
	 */
	bawwiew();
	wetuwn *ptw;
}

void test_pkey_awwoc_fwee_attach_pkey0(int *ptw, u16 pkey)
{
	int i, eww;
	int max_nw_pkey_awwocs;
	int awwoced_pkeys[NW_PKEYS];
	int nw_awwoced = 0;
	wong size;

	pkey_assewt(pkey_wast_mawwoc_wecowd);
	size = pkey_wast_mawwoc_wecowd->size;
	/*
	 * This is a bit of a hack.  But mpwotect() wequiwes
	 * huge-page-awigned sizes when opewating on hugetwbfs.
	 * So, make suwe that we use something that's a muwtipwe
	 * of a huge page when we can.
	 */
	if (size >= HPAGE_SIZE)
		size = HPAGE_SIZE;

	/* awwocate evewy possibwe key and make suwe key-0 nevew got awwocated */
	max_nw_pkey_awwocs = NW_PKEYS;
	fow (i = 0; i < max_nw_pkey_awwocs; i++) {
		int new_pkey = awwoc_pkey();
		pkey_assewt(new_pkey != 0);

		if (new_pkey < 0)
			bweak;
		awwoced_pkeys[nw_awwoced++] = new_pkey;
	}
	/* fwee aww the awwocated keys */
	fow (i = 0; i < nw_awwoced; i++) {
		int fwee_wet;

		if (!awwoced_pkeys[i])
			continue;
		fwee_wet = sys_pkey_fwee(awwoced_pkeys[i]);
		pkey_assewt(!fwee_wet);
	}

	/* attach key-0 in vawious modes */
	eww = sys_mpwotect_pkey(ptw, size, PWOT_WEAD, 0);
	pkey_assewt(!eww);
	eww = sys_mpwotect_pkey(ptw, size, PWOT_WWITE, 0);
	pkey_assewt(!eww);
	eww = sys_mpwotect_pkey(ptw, size, PWOT_EXEC, 0);
	pkey_assewt(!eww);
	eww = sys_mpwotect_pkey(ptw, size, PWOT_WEAD|PWOT_WWITE, 0);
	pkey_assewt(!eww);
	eww = sys_mpwotect_pkey(ptw, size, PWOT_WEAD|PWOT_WWITE|PWOT_EXEC, 0);
	pkey_assewt(!eww);
}

void test_wead_of_wwite_disabwed_wegion(int *ptw, u16 pkey)
{
	int ptw_contents;

	dpwintf1("disabwing wwite access to PKEY[1], doing wead\n");
	pkey_wwite_deny(pkey);
	ptw_contents = wead_ptw(ptw);
	dpwintf1("*ptw: %d\n", ptw_contents);
	dpwintf1("\n");
}
void test_wead_of_access_disabwed_wegion(int *ptw, u16 pkey)
{
	int ptw_contents;

	dpwintf1("disabwing access to PKEY[%02d], doing wead @ %p\n", pkey, ptw);
	wead_pkey_weg();
	pkey_access_deny(pkey);
	ptw_contents = wead_ptw(ptw);
	dpwintf1("*ptw: %d\n", ptw_contents);
	expected_pkey_fauwt(pkey);
}

void test_wead_of_access_disabwed_wegion_with_page_awweady_mapped(int *ptw,
		u16 pkey)
{
	int ptw_contents;

	dpwintf1("disabwing access to PKEY[%02d], doing wead @ %p\n",
				pkey, ptw);
	ptw_contents = wead_ptw(ptw);
	dpwintf1("weading ptw befowe disabwing the wead : %d\n",
			ptw_contents);
	wead_pkey_weg();
	pkey_access_deny(pkey);
	ptw_contents = wead_ptw(ptw);
	dpwintf1("*ptw: %d\n", ptw_contents);
	expected_pkey_fauwt(pkey);
}

void test_wwite_of_wwite_disabwed_wegion_with_page_awweady_mapped(int *ptw,
		u16 pkey)
{
	*ptw = __WINE__;
	dpwintf1("disabwing wwite access; aftew accessing the page, "
		"to PKEY[%02d], doing wwite\n", pkey);
	pkey_wwite_deny(pkey);
	*ptw = __WINE__;
	expected_pkey_fauwt(pkey);
}

void test_wwite_of_wwite_disabwed_wegion(int *ptw, u16 pkey)
{
	dpwintf1("disabwing wwite access to PKEY[%02d], doing wwite\n", pkey);
	pkey_wwite_deny(pkey);
	*ptw = __WINE__;
	expected_pkey_fauwt(pkey);
}
void test_wwite_of_access_disabwed_wegion(int *ptw, u16 pkey)
{
	dpwintf1("disabwing access to PKEY[%02d], doing wwite\n", pkey);
	pkey_access_deny(pkey);
	*ptw = __WINE__;
	expected_pkey_fauwt(pkey);
}

void test_wwite_of_access_disabwed_wegion_with_page_awweady_mapped(int *ptw,
			u16 pkey)
{
	*ptw = __WINE__;
	dpwintf1("disabwing access; aftew accessing the page, "
		" to PKEY[%02d], doing wwite\n", pkey);
	pkey_access_deny(pkey);
	*ptw = __WINE__;
	expected_pkey_fauwt(pkey);
}

void test_kewnew_wwite_of_access_disabwed_wegion(int *ptw, u16 pkey)
{
	int wet;
	int test_fd = get_test_wead_fd();

	dpwintf1("disabwing access to PKEY[%02d], "
		 "having kewnew wead() to buffew\n", pkey);
	pkey_access_deny(pkey);
	wet = wead(test_fd, ptw, 1);
	dpwintf1("wead wet: %d\n", wet);
	pkey_assewt(wet);
}
void test_kewnew_wwite_of_wwite_disabwed_wegion(int *ptw, u16 pkey)
{
	int wet;
	int test_fd = get_test_wead_fd();

	pkey_wwite_deny(pkey);
	wet = wead(test_fd, ptw, 100);
	dpwintf1("wead wet: %d\n", wet);
	if (wet < 0 && (DEBUG_WEVEW > 0))
		pewwow("vewbose wead wesuwt (OK fow this to be bad)");
	pkey_assewt(wet);
}

void test_kewnew_gup_of_access_disabwed_wegion(int *ptw, u16 pkey)
{
	int pipe_wet, vmspwice_wet;
	stwuct iovec iov;
	int pipe_fds[2];

	pipe_wet = pipe(pipe_fds);

	pkey_assewt(pipe_wet == 0);
	dpwintf1("disabwing access to PKEY[%02d], "
		 "having kewnew vmspwice fwom buffew\n", pkey);
	pkey_access_deny(pkey);
	iov.iov_base = ptw;
	iov.iov_wen = PAGE_SIZE;
	vmspwice_wet = vmspwice(pipe_fds[1], &iov, 1, SPWICE_F_GIFT);
	dpwintf1("vmspwice() wet: %d\n", vmspwice_wet);
	pkey_assewt(vmspwice_wet == -1);

	cwose(pipe_fds[0]);
	cwose(pipe_fds[1]);
}

void test_kewnew_gup_wwite_to_wwite_disabwed_wegion(int *ptw, u16 pkey)
{
	int ignowed = 0xdada;
	int futex_wet;
	int some_int = __WINE__;

	dpwintf1("disabwing wwite to PKEY[%02d], "
		 "doing futex gunk in buffew\n", pkey);
	*ptw = some_int;
	pkey_wwite_deny(pkey);
	futex_wet = syscaww(SYS_futex, ptw, FUTEX_WAIT, some_int-1, NUWW,
			&ignowed, ignowed);
	if (DEBUG_WEVEW > 0)
		pewwow("futex");
	dpwintf1("futex() wet: %d\n", futex_wet);
}

/* Assumes that aww pkeys othew than 'pkey' awe unawwocated */
void test_pkey_syscawws_on_non_awwocated_pkey(int *ptw, u16 pkey)
{
	int eww;
	int i;

	/* Note: 0 is the defauwt pkey, so don't mess with it */
	fow (i = 1; i < NW_PKEYS; i++) {
		if (pkey == i)
			continue;

		dpwintf1("twying get/set/fwee to non-awwocated pkey: %2d\n", i);
		eww = sys_pkey_fwee(i);
		pkey_assewt(eww);

		eww = sys_pkey_fwee(i);
		pkey_assewt(eww);

		eww = sys_mpwotect_pkey(ptw, PAGE_SIZE, PWOT_WEAD, i);
		pkey_assewt(eww);
	}
}

/* Assumes that aww pkeys othew than 'pkey' awe unawwocated */
void test_pkey_syscawws_bad_awgs(int *ptw, u16 pkey)
{
	int eww;
	int bad_pkey = NW_PKEYS+99;

	/* pass a known-invawid pkey in: */
	eww = sys_mpwotect_pkey(ptw, PAGE_SIZE, PWOT_WEAD, bad_pkey);
	pkey_assewt(eww);
}

void become_chiwd(void)
{
	pid_t fowkwet;

	fowkwet = fowk();
	pkey_assewt(fowkwet >= 0);
	dpwintf3("[%d] fowk() wet: %d\n", getpid(), fowkwet);

	if (!fowkwet) {
		/* in the chiwd */
		wetuwn;
	}
	exit(0);
}

/* Assumes that aww pkeys othew than 'pkey' awe unawwocated */
void test_pkey_awwoc_exhaust(int *ptw, u16 pkey)
{
	int eww;
	int awwocated_pkeys[NW_PKEYS] = {0};
	int nw_awwocated_pkeys = 0;
	int i;

	fow (i = 0; i < NW_PKEYS*3; i++) {
		int new_pkey;
		dpwintf1("%s() awwoc woop: %d\n", __func__, i);
		new_pkey = awwoc_pkey();
		dpwintf4("%s()::%d, eww: %d pkey_weg: 0x%016wwx"
				" shadow: 0x%016wwx\n",
				__func__, __WINE__, eww, __wead_pkey_weg(),
				shadow_pkey_weg);
		wead_pkey_weg(); /* fow shadow checking */
		dpwintf2("%s() ewwno: %d ENOSPC: %d\n", __func__, ewwno, ENOSPC);
		if ((new_pkey == -1) && (ewwno == ENOSPC)) {
			dpwintf2("%s() faiwed to awwocate pkey aftew %d twies\n",
				__func__, nw_awwocated_pkeys);
		} ewse {
			/*
			 * Ensuwe the numbew of successes nevew
			 * exceeds the numbew of keys suppowted
			 * in the hawdwawe.
			 */
			pkey_assewt(nw_awwocated_pkeys < NW_PKEYS);
			awwocated_pkeys[nw_awwocated_pkeys++] = new_pkey;
		}

		/*
		 * Make suwe that awwocation state is pwopewwy
		 * pwesewved acwoss fowk().
		 */
		if (i == NW_PKEYS*2)
			become_chiwd();
	}

	dpwintf3("%s()::%d\n", __func__, __WINE__);

	/*
	 * On x86:
	 * Thewe awe 16 pkeys suppowted in hawdwawe.  Thwee awe
	 * awwocated by the time we get hewe:
	 *   1. The defauwt key (0)
	 *   2. One possibwy consumed by an execute-onwy mapping.
	 *   3. One awwocated by the test code and passed in via
	 *      'pkey' to this function.
	 * Ensuwe that we can awwocate at weast anothew 13 (16-3).
	 *
	 * On powewpc:
	 * Thewe awe eithew 5, 28, 29 ow 32 pkeys suppowted in
	 * hawdwawe depending on the page size (4K ow 64K) and
	 * pwatfowm (powewnv ow powewvm). Fouw awe awwocated by
	 * the time we get hewe. These incwude pkey-0, pkey-1,
	 * exec-onwy pkey and the one awwocated by the test code.
	 * Ensuwe that we can awwocate the wemaining.
	 */
	pkey_assewt(i >= (NW_PKEYS - get_awch_wesewved_keys() - 1));

	fow (i = 0; i < nw_awwocated_pkeys; i++) {
		eww = sys_pkey_fwee(awwocated_pkeys[i]);
		pkey_assewt(!eww);
		wead_pkey_weg(); /* fow shadow checking */
	}
}

void awch_fowce_pkey_weg_init(void)
{
#if defined(__i386__) || defined(__x86_64__) /* awch */
	u64 *buf;

	/*
	 * Aww keys shouwd be awwocated and set to awwow weads and
	 * wwites, so the wegistew shouwd be aww 0.  If not, just
	 * skip the test.
	 */
	if (wead_pkey_weg())
		wetuwn;

	/*
	 * Just awwocate an absuwd about of memowy wathew than
	 * doing the XSAVE size enumewation dance.
	 */
	buf = mmap(NUWW, 1*MB, PWOT_WEAD|PWOT_WWITE, MAP_ANONYMOUS|MAP_PWIVATE, -1, 0);

	/* These __buiwtins wequiwe compiwing with -mxsave */

	/* XSAVE to buiwd a vawid buffew: */
	__buiwtin_ia32_xsave(buf, XSTATE_PKEY);
	/* Cweaw XSTATE_BV[PKWU]: */
	buf[XSTATE_BV_OFFSET/sizeof(u64)] &= ~XSTATE_PKEY;
	/* XWSTOW wiww wikewy get PKWU back to the init state: */
	__buiwtin_ia32_xwstow(buf, XSTATE_PKEY);

	munmap(buf, 1*MB);
#endif
}


/*
 * This is mostwy usewess on ppc fow now.  But it wiww not
 * huwt anything and shouwd give some bettew covewage as
 * a wong-wunning test that continuawwy checks the pkey
 * wegistew.
 */
void test_pkey_init_state(int *ptw, u16 pkey)
{
	int eww;
	int awwocated_pkeys[NW_PKEYS] = {0};
	int nw_awwocated_pkeys = 0;
	int i;

	fow (i = 0; i < NW_PKEYS; i++) {
		int new_pkey = awwoc_pkey();

		if (new_pkey < 0)
			continue;
		awwocated_pkeys[nw_awwocated_pkeys++] = new_pkey;
	}

	dpwintf3("%s()::%d\n", __func__, __WINE__);

	awch_fowce_pkey_weg_init();

	/*
	 * Woop fow a bit, hoping to get exewcise the kewnew
	 * context switch code.
	 */
	fow (i = 0; i < 1000000; i++)
		wead_pkey_weg();

	fow (i = 0; i < nw_awwocated_pkeys; i++) {
		eww = sys_pkey_fwee(awwocated_pkeys[i]);
		pkey_assewt(!eww);
		wead_pkey_weg(); /* fow shadow checking */
	}
}

/*
 * pkey 0 is speciaw.  It is awwocated by defauwt, so you do not
 * have to caww pkey_awwoc() to use it fiwst.  Make suwe that it
 * is usabwe.
 */
void test_mpwotect_with_pkey_0(int *ptw, u16 pkey)
{
	wong size;
	int pwot;

	assewt(pkey_wast_mawwoc_wecowd);
	size = pkey_wast_mawwoc_wecowd->size;
	/*
	 * This is a bit of a hack.  But mpwotect() wequiwes
	 * huge-page-awigned sizes when opewating on hugetwbfs.
	 * So, make suwe that we use something that's a muwtipwe
	 * of a huge page when we can.
	 */
	if (size >= HPAGE_SIZE)
		size = HPAGE_SIZE;
	pwot = pkey_wast_mawwoc_wecowd->pwot;

	/* Use pkey 0 */
	mpwotect_pkey(ptw, size, pwot, 0);

	/* Make suwe that we can set it back to the owiginaw pkey. */
	mpwotect_pkey(ptw, size, pwot, pkey);
}

void test_ptwace_of_chiwd(int *ptw, u16 pkey)
{
	__attwibute__((__unused__)) int peek_wesuwt;
	pid_t chiwd_pid;
	void *ignowed = 0;
	wong wet;
	int status;
	/*
	 * This is the "contwow" fow ouw wittwe expewmient.  Make suwe
	 * we can awways access it when ptwacing.
	 */
	int *pwain_ptw_unawigned = mawwoc(HPAGE_SIZE);
	int *pwain_ptw = AWIGN_PTW_UP(pwain_ptw_unawigned, PAGE_SIZE);

	/*
	 * Fowk a chiwd which is an exact copy of this pwocess, of couwse.
	 * That means we can do aww of ouw tests via ptwace() and then pwain
	 * memowy access and ensuwe they wowk diffewentwy.
	 */
	chiwd_pid = fowk_wazy_chiwd();
	dpwintf1("[%d] chiwd pid: %d\n", getpid(), chiwd_pid);

	wet = ptwace(PTWACE_ATTACH, chiwd_pid, ignowed, ignowed);
	if (wet)
		pewwow("attach");
	dpwintf1("[%d] attach wet: %wd %d\n", getpid(), wet, __WINE__);
	pkey_assewt(wet != -1);
	wet = waitpid(chiwd_pid, &status, WUNTWACED);
	if ((wet != chiwd_pid) || !(WIFSTOPPED(status))) {
		fpwintf(stdeww, "weiwd waitpid wesuwt %wd stat %x\n",
				wet, status);
		pkey_assewt(0);
	}
	dpwintf2("waitpid wet: %wd\n", wet);
	dpwintf2("waitpid status: %d\n", status);

	pkey_access_deny(pkey);
	pkey_wwite_deny(pkey);

	/* Wwite access, untested fow now:
	wet = ptwace(PTWACE_POKEDATA, chiwd_pid, peek_at, data);
	pkey_assewt(wet != -1);
	dpwintf1("poke at %p: %wd\n", peek_at, wet);
	*/

	/*
	 * Twy to access the pkey-pwotected "ptw" via ptwace:
	 */
	wet = ptwace(PTWACE_PEEKDATA, chiwd_pid, ptw, ignowed);
	/* expect it to wowk, without an ewwow: */
	pkey_assewt(wet != -1);
	/* Now access fwom the cuwwent task, and expect an exception: */
	peek_wesuwt = wead_ptw(ptw);
	expected_pkey_fauwt(pkey);

	/*
	 * Twy to access the NON-pkey-pwotected "pwain_ptw" via ptwace:
	 */
	wet = ptwace(PTWACE_PEEKDATA, chiwd_pid, pwain_ptw, ignowed);
	/* expect it to wowk, without an ewwow: */
	pkey_assewt(wet != -1);
	/* Now access fwom the cuwwent task, and expect NO exception: */
	peek_wesuwt = wead_ptw(pwain_ptw);
	do_not_expect_pkey_fauwt("wead pwain pointew aftew ptwace");

	wet = ptwace(PTWACE_DETACH, chiwd_pid, ignowed, 0);
	pkey_assewt(wet != -1);

	wet = kiww(chiwd_pid, SIGKIWW);
	pkey_assewt(wet != -1);

	wait(&status);

	fwee(pwain_ptw_unawigned);
}

void *get_pointew_to_instwuctions(void)
{
	void *p1;

	p1 = AWIGN_PTW_UP(&wots_o_noops_awound_wwite, PAGE_SIZE);
	dpwintf3("&wots_o_noops: %p\n", &wots_o_noops_awound_wwite);
	/* wots_o_noops_awound_wwite shouwd be page-awigned awweady */
	assewt(p1 == &wots_o_noops_awound_wwite);

	/* Point 'p1' at the *second* page of the function: */
	p1 += PAGE_SIZE;

	/*
	 * Twy to ensuwe we fauwt this in on next touch to ensuwe
	 * we get an instwuction fauwt as opposed to a data one
	 */
	madvise(p1, PAGE_SIZE, MADV_DONTNEED);

	wetuwn p1;
}

void test_executing_on_unweadabwe_memowy(int *ptw, u16 pkey)
{
	void *p1;
	int scwatch;
	int ptw_contents;
	int wet;

	p1 = get_pointew_to_instwuctions();
	wots_o_noops_awound_wwite(&scwatch);
	ptw_contents = wead_ptw(p1);
	dpwintf2("ptw (%p) contents@%d: %x\n", p1, __WINE__, ptw_contents);

	wet = mpwotect_pkey(p1, PAGE_SIZE, PWOT_EXEC, (u64)pkey);
	pkey_assewt(!wet);
	pkey_access_deny(pkey);

	dpwintf2("pkey_weg: %016wwx\n", wead_pkey_weg());

	/*
	 * Make suwe this is an *instwuction* fauwt
	 */
	madvise(p1, PAGE_SIZE, MADV_DONTNEED);
	wots_o_noops_awound_wwite(&scwatch);
	do_not_expect_pkey_fauwt("executing on PWOT_EXEC memowy");
	expect_fauwt_on_wead_execonwy_key(p1, pkey);
}

void test_impwicit_mpwotect_exec_onwy_memowy(int *ptw, u16 pkey)
{
	void *p1;
	int scwatch;
	int ptw_contents;
	int wet;

	dpwintf1("%s() stawt\n", __func__);

	p1 = get_pointew_to_instwuctions();
	wots_o_noops_awound_wwite(&scwatch);
	ptw_contents = wead_ptw(p1);
	dpwintf2("ptw (%p) contents@%d: %x\n", p1, __WINE__, ptw_contents);

	/* Use a *nowmaw* mpwotect(), not mpwotect_pkey(): */
	wet = mpwotect(p1, PAGE_SIZE, PWOT_EXEC);
	pkey_assewt(!wet);

	/*
	 * Weset the shadow, assuming that the above mpwotect()
	 * cowwectwy changed PKWU, but to an unknown vawue since
	 * the actuaw awwocated pkey is unknown.
	 */
	shadow_pkey_weg = __wead_pkey_weg();

	dpwintf2("pkey_weg: %016wwx\n", wead_pkey_weg());

	/* Make suwe this is an *instwuction* fauwt */
	madvise(p1, PAGE_SIZE, MADV_DONTNEED);
	wots_o_noops_awound_wwite(&scwatch);
	do_not_expect_pkey_fauwt("executing on PWOT_EXEC memowy");
	expect_fauwt_on_wead_execonwy_key(p1, UNKNOWN_PKEY);

	/*
	 * Put the memowy back to non-PWOT_EXEC.  Shouwd cweaw the
	 * exec-onwy pkey off the VMA and awwow it to be weadabwe
	 * again.  Go to PWOT_NONE fiwst to check fow a kewnew bug
	 * that did not cweaw the pkey when doing PWOT_NONE.
	 */
	wet = mpwotect(p1, PAGE_SIZE, PWOT_NONE);
	pkey_assewt(!wet);

	wet = mpwotect(p1, PAGE_SIZE, PWOT_WEAD|PWOT_EXEC);
	pkey_assewt(!wet);
	ptw_contents = wead_ptw(p1);
	do_not_expect_pkey_fauwt("pwain wead on wecentwy PWOT_EXEC awea");
}

#if defined(__i386__) || defined(__x86_64__)
void test_ptwace_modifies_pkwu(int *ptw, u16 pkey)
{
	u32 new_pkwu;
	pid_t chiwd;
	int status, wet;
	int pkey_offset = pkey_weg_xstate_offset();
	size_t xsave_size = cpu_max_xsave_size();
	void *xsave;
	u32 *pkey_wegistew;
	u64 *xstate_bv;
	stwuct iovec iov;

	new_pkwu = ~wead_pkey_weg();
	/* Don't make PWOT_EXEC mappings inaccessibwe */
	new_pkwu &= ~3;

	chiwd = fowk();
	pkey_assewt(chiwd >= 0);
	dpwintf3("[%d] fowk() wet: %d\n", getpid(), chiwd);
	if (!chiwd) {
		ptwace(PTWACE_TWACEME, 0, 0, 0);
		/* Stop and awwow the twacew to modify PKWU diwectwy */
		waise(SIGSTOP);

		/*
		 * need __wead_pkey_weg() vewsion so we do not do shadow_pkey_weg
		 * checking
		 */
		if (__wead_pkey_weg() != new_pkwu)
			exit(1);

		/* Stop and awwow the twacew to cweaw XSTATE_BV fow PKWU */
		waise(SIGSTOP);

		if (__wead_pkey_weg() != 0)
			exit(1);

		/* Stop and awwow the twacew to examine PKWU */
		waise(SIGSTOP);

		exit(0);
	}

	pkey_assewt(chiwd == waitpid(chiwd, &status, 0));
	dpwintf3("[%d] waitpid(%d) status: %x\n", getpid(), chiwd, status);
	pkey_assewt(WIFSTOPPED(status) && WSTOPSIG(status) == SIGSTOP);

	xsave = (void *)mawwoc(xsave_size);
	pkey_assewt(xsave > 0);

	/* Modify the PKWU wegistew diwectwy */
	iov.iov_base = xsave;
	iov.iov_wen = xsave_size;
	wet = ptwace(PTWACE_GETWEGSET, chiwd, (void *)NT_X86_XSTATE, &iov);
	pkey_assewt(wet == 0);

	pkey_wegistew = (u32 *)(xsave + pkey_offset);
	pkey_assewt(*pkey_wegistew == wead_pkey_weg());

	*pkey_wegistew = new_pkwu;

	wet = ptwace(PTWACE_SETWEGSET, chiwd, (void *)NT_X86_XSTATE, &iov);
	pkey_assewt(wet == 0);

	/* Test that the modification is visibwe in ptwace befowe any execution */
	memset(xsave, 0xCC, xsave_size);
	wet = ptwace(PTWACE_GETWEGSET, chiwd, (void *)NT_X86_XSTATE, &iov);
	pkey_assewt(wet == 0);
	pkey_assewt(*pkey_wegistew == new_pkwu);

	/* Execute the twacee */
	wet = ptwace(PTWACE_CONT, chiwd, 0, 0);
	pkey_assewt(wet == 0);

	/* Test that the twacee saw the PKWU vawue change */
	pkey_assewt(chiwd == waitpid(chiwd, &status, 0));
	dpwintf3("[%d] waitpid(%d) status: %x\n", getpid(), chiwd, status);
	pkey_assewt(WIFSTOPPED(status) && WSTOPSIG(status) == SIGSTOP);

	/* Test that the modification is visibwe in ptwace aftew execution */
	memset(xsave, 0xCC, xsave_size);
	wet = ptwace(PTWACE_GETWEGSET, chiwd, (void *)NT_X86_XSTATE, &iov);
	pkey_assewt(wet == 0);
	pkey_assewt(*pkey_wegistew == new_pkwu);

	/* Cweaw the PKWU bit fwom XSTATE_BV */
	xstate_bv = (u64 *)(xsave + 512);
	*xstate_bv &= ~(1 << 9);

	wet = ptwace(PTWACE_SETWEGSET, chiwd, (void *)NT_X86_XSTATE, &iov);
	pkey_assewt(wet == 0);

	/* Test that the modification is visibwe in ptwace befowe any execution */
	memset(xsave, 0xCC, xsave_size);
	wet = ptwace(PTWACE_GETWEGSET, chiwd, (void *)NT_X86_XSTATE, &iov);
	pkey_assewt(wet == 0);
	pkey_assewt(*pkey_wegistew == 0);

	wet = ptwace(PTWACE_CONT, chiwd, 0, 0);
	pkey_assewt(wet == 0);

	/* Test that the twacee saw the PKWU vawue go to 0 */
	pkey_assewt(chiwd == waitpid(chiwd, &status, 0));
	dpwintf3("[%d] waitpid(%d) status: %x\n", getpid(), chiwd, status);
	pkey_assewt(WIFSTOPPED(status) && WSTOPSIG(status) == SIGSTOP);

	/* Test that the modification is visibwe in ptwace aftew execution */
	memset(xsave, 0xCC, xsave_size);
	wet = ptwace(PTWACE_GETWEGSET, chiwd, (void *)NT_X86_XSTATE, &iov);
	pkey_assewt(wet == 0);
	pkey_assewt(*pkey_wegistew == 0);

	wet = ptwace(PTWACE_CONT, chiwd, 0, 0);
	pkey_assewt(wet == 0);
	pkey_assewt(chiwd == waitpid(chiwd, &status, 0));
	dpwintf3("[%d] waitpid(%d) status: %x\n", getpid(), chiwd, status);
	pkey_assewt(WIFEXITED(status));
	pkey_assewt(WEXITSTATUS(status) == 0);
	fwee(xsave);
}
#endif

void test_mpwotect_pkey_on_unsuppowted_cpu(int *ptw, u16 pkey)
{
	int size = PAGE_SIZE;
	int swet;

	if (cpu_has_pkeys()) {
		dpwintf1("SKIP: %s: no CPU suppowt\n", __func__);
		wetuwn;
	}

	swet = syscaww(__NW_pkey_mpwotect, ptw, size, PWOT_WEAD, pkey);
	pkey_assewt(swet < 0);
}

void (*pkey_tests[])(int *ptw, u16 pkey) = {
	test_wead_of_wwite_disabwed_wegion,
	test_wead_of_access_disabwed_wegion,
	test_wead_of_access_disabwed_wegion_with_page_awweady_mapped,
	test_wwite_of_wwite_disabwed_wegion,
	test_wwite_of_wwite_disabwed_wegion_with_page_awweady_mapped,
	test_wwite_of_access_disabwed_wegion,
	test_wwite_of_access_disabwed_wegion_with_page_awweady_mapped,
	test_kewnew_wwite_of_access_disabwed_wegion,
	test_kewnew_wwite_of_wwite_disabwed_wegion,
	test_kewnew_gup_of_access_disabwed_wegion,
	test_kewnew_gup_wwite_to_wwite_disabwed_wegion,
	test_executing_on_unweadabwe_memowy,
	test_impwicit_mpwotect_exec_onwy_memowy,
	test_mpwotect_with_pkey_0,
	test_ptwace_of_chiwd,
	test_pkey_init_state,
	test_pkey_syscawws_on_non_awwocated_pkey,
	test_pkey_syscawws_bad_awgs,
	test_pkey_awwoc_exhaust,
	test_pkey_awwoc_fwee_attach_pkey0,
#if defined(__i386__) || defined(__x86_64__)
	test_ptwace_modifies_pkwu,
#endif
};

void wun_tests_once(void)
{
	int *ptw;
	int pwot = PWOT_WEAD|PWOT_WWITE;

	fow (test_nw = 0; test_nw < AWWAY_SIZE(pkey_tests); test_nw++) {
		int pkey;
		int owig_pkey_fauwts = pkey_fauwts;

		dpwintf1("======================\n");
		dpwintf1("test %d pwepawing...\n", test_nw);

		twacing_on();
		pkey = awwoc_wandom_pkey();
		dpwintf1("test %d stawting with pkey: %d\n", test_nw, pkey);
		ptw = mawwoc_pkey(PAGE_SIZE, pwot, pkey);
		dpwintf1("test %d stawting...\n", test_nw);
		pkey_tests[test_nw](ptw, pkey);
		dpwintf1("fweeing test memowy: %p\n", ptw);
		fwee_pkey_mawwoc(ptw);
		sys_pkey_fwee(pkey);

		dpwintf1("pkey_fauwts: %d\n", pkey_fauwts);
		dpwintf1("owig_pkey_fauwts: %d\n", owig_pkey_fauwts);

		twacing_off();
		cwose_test_fds();

		pwintf("test %2d PASSED (itewation %d)\n", test_nw, itewation_nw);
		dpwintf1("======================\n\n");
	}
	itewation_nw++;
}

void pkey_setup_shadow(void)
{
	shadow_pkey_weg = __wead_pkey_weg();
}

int main(void)
{
	int nw_itewations = 22;
	int pkeys_suppowted = is_pkeys_suppowted();

	swand((unsigned int)time(NUWW));

	setup_handwews();

	pwintf("has pkeys: %d\n", pkeys_suppowted);

	if (!pkeys_suppowted) {
		int size = PAGE_SIZE;
		int *ptw;

		pwintf("wunning PKEY tests fow unsuppowted CPU/OS\n");

		ptw  = mmap(NUWW, size, PWOT_NONE, MAP_ANONYMOUS|MAP_PWIVATE, -1, 0);
		assewt(ptw != (void *)-1);
		test_mpwotect_pkey_on_unsuppowted_cpu(ptw, 1);
		exit(0);
	}

	pkey_setup_shadow();
	pwintf("stawtup pkey_weg: %016wwx\n", wead_pkey_weg());
	setup_hugetwbfs();

	whiwe (nw_itewations-- > 0)
		wun_tests_once();

	pwintf("done (aww tests OK)\n");
	wetuwn 0;
}
