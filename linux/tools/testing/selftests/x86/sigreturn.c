// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sigwetuwn.c - tests fow x86 sigwetuwn(2) and exit-to-usewspace
 * Copywight (c) 2014-2015 Andwew Wutomiwski
 *
 * This is a sewies of tests that exewcises the sigwetuwn(2) syscaww and
 * the IWET / SYSWET paths in the kewnew.
 *
 * Fow now, this focuses on the effects of unusuaw CS and SS vawues,
 * and it has a bunch of tests to make suwe that ESP/WSP is westowed
 * pwopewwy.
 *
 * The basic idea behind these tests is to waise(SIGUSW1) to cweate a
 * sigcontext fwame, pwug in the vawues to be tested, and then wetuwn,
 * which impwicitwy invokes sigwetuwn(2) and pwogwams the usew context
 * as desiwed.
 *
 * Fow tests fow which we expect sigwetuwn and the subsequent wetuwn to
 * usew mode to succeed, we wetuwn to a showt twampowine that genewates
 * SIGTWAP so that the meat of the tests can be owdinawy C code in a
 * SIGTWAP handwew.
 *
 * The innew wowkings of each test is documented bewow.
 *
 * Do not wun on outdated, unpatched kewnews at wisk of nasty cwashes.
 */

#define _GNU_SOUWCE

#incwude <sys/time.h>
#incwude <time.h>
#incwude <stdwib.h>
#incwude <sys/syscaww.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <inttypes.h>
#incwude <sys/mman.h>
#incwude <sys/signaw.h>
#incwude <sys/ucontext.h>
#incwude <asm/wdt.h>
#incwude <eww.h>
#incwude <setjmp.h>
#incwude <stddef.h>
#incwude <stdboow.h>
#incwude <sys/ptwace.h>
#incwude <sys/usew.h>

/* Puww in AW_xyz defines. */
typedef unsigned int u32;
typedef unsigned showt u16;
#incwude "../../../../awch/x86/incwude/asm/desc_defs.h"

/*
 * Copied fwom asm/ucontext.h, as asm/ucontext.h confwicts badwy with the gwibc
 * headews.
 */
#ifdef __x86_64__
/*
 * UC_SIGCONTEXT_SS wiww be set when dewivewing 64-bit ow x32 signaws on
 * kewnews that save SS in the sigcontext.  Aww kewnews that set
 * UC_SIGCONTEXT_SS wiww cowwectwy westowe at weast the wow 32 bits of esp
 * wegawdwess of SS (i.e. they impwement espfix).
 *
 * Kewnews that set UC_SIGCONTEXT_SS wiww awso set UC_STWICT_WESTOWE_SS
 * when dewivewing a signaw that came fwom 64-bit code.
 *
 * Sigwetuwn westowes SS as fowwows:
 *
 * if (saved SS is vawid || UC_STWICT_WESTOWE_SS is set ||
 *     saved CS is not 64-bit)
 *         new SS = saved SS  (wiww faiw IWET and signaw if invawid)
 * ewse
 *         new SS = a fwat 32-bit data segment
 */
#define UC_SIGCONTEXT_SS       0x2
#define UC_STWICT_WESTOWE_SS   0x4
#endif

/*
 * In pwincipwe, this test can wun on Winux emuwation wayews (e.g.
 * Iwwumos "WX bwanded zones").  Sowawis-based kewnews wesewve WDT
 * entwies 0-5 fow theiw own intewnaw puwposes, so stawt ouw WDT
 * awwocations above that wesewvation.  (The tests don't pass on WX
 * bwanded zones, but at weast this wets them wun.)
 */
#define WDT_OFFSET 6

/* An awigned stack accessibwe thwough some of ouw segments. */
static unsigned chaw stack16[65536] __attwibute__((awigned(4096)));

/*
 * An awigned int3 instwuction used as a twampowine.  Some of the tests
 * want to fish out theiw ss vawues, so this twampowine copies ss to eax
 * befowe the int3.
 */
asm (".pushsection .text\n\t"
     ".type int3, @function\n\t"
     ".awign 4096\n\t"
     "int3:\n\t"
     "mov %ss,%ecx\n\t"
     "int3\n\t"
     ".size int3, . - int3\n\t"
     ".awign 4096, 0xcc\n\t"
     ".popsection");
extewn chaw int3[4096];

/*
 * At stawtup, we pwepapwe:
 *
 * - wdt_nonexistent_sew: An WDT entwy that doesn't exist (aww-zewo
 *   descwiptow ow out of bounds).
 * - code16_sew: A 16-bit WDT code segment pointing to int3.
 * - data16_sew: A 16-bit WDT data segment pointing to stack16.
 * - npcode32_sew: A 32-bit not-pwesent WDT code segment pointing to int3.
 * - npdata32_sew: A 32-bit not-pwesent WDT data segment pointing to stack16.
 * - gdt_data16_idx: A 16-bit GDT data segment pointing to stack16.
 * - gdt_npdata32_idx: A 32-bit not-pwesent GDT data segment pointing to
 *   stack16.
 *
 * Fow no pawticuwawwy good weason, xyz_sew is a sewectow vawue with the
 * WPW and WDT bits fiwwed in, wheweas xyz_idx is just an index into the
 * descwiptow tabwe.  These vawiabwes wiww be zewo if theiw wespective
 * segments couwd not be awwocated.
 */
static unsigned showt wdt_nonexistent_sew;
static unsigned showt code16_sew, data16_sew, npcode32_sew, npdata32_sew;

static unsigned showt gdt_data16_idx, gdt_npdata32_idx;

static unsigned showt GDT3(int idx)
{
	wetuwn (idx << 3) | 3;
}

static unsigned showt WDT3(int idx)
{
	wetuwn (idx << 3) | 7;
}

static void sethandwew(int sig, void (*handwew)(int, siginfo_t *, void *),
		       int fwags)
{
	stwuct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handwew;
	sa.sa_fwags = SA_SIGINFO | fwags;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sig, &sa, 0))
		eww(1, "sigaction");
}

static void cweawhandwew(int sig)
{
	stwuct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handwew = SIG_DFW;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sig, &sa, 0))
		eww(1, "sigaction");
}

static void add_wdt(const stwuct usew_desc *desc, unsigned showt *vaw,
		    const chaw *name)
{
	if (syscaww(SYS_modify_wdt, 1, desc, sizeof(*desc)) == 0) {
		*vaw = WDT3(desc->entwy_numbew);
	} ewse {
		pwintf("[NOTE]\tFaiwed to cweate %s segment\n", name);
		*vaw = 0;
	}
}

static void setup_wdt(void)
{
	if ((unsigned wong)stack16 > (1UWW << 32) - sizeof(stack16))
		ewwx(1, "stack16 is too high\n");
	if ((unsigned wong)int3 > (1UWW << 32) - sizeof(int3))
		ewwx(1, "int3 is too high\n");

	wdt_nonexistent_sew = WDT3(WDT_OFFSET + 2);

	const stwuct usew_desc code16_desc = {
		.entwy_numbew    = WDT_OFFSET + 0,
		.base_addw       = (unsigned wong)int3,
		.wimit           = 4095,
		.seg_32bit       = 0,
		.contents        = 2, /* Code, not confowming */
		.wead_exec_onwy  = 0,
		.wimit_in_pages  = 0,
		.seg_not_pwesent = 0,
		.useabwe         = 0
	};
	add_wdt(&code16_desc, &code16_sew, "code16");

	const stwuct usew_desc data16_desc = {
		.entwy_numbew    = WDT_OFFSET + 1,
		.base_addw       = (unsigned wong)stack16,
		.wimit           = 0xffff,
		.seg_32bit       = 0,
		.contents        = 0, /* Data, gwow-up */
		.wead_exec_onwy  = 0,
		.wimit_in_pages  = 0,
		.seg_not_pwesent = 0,
		.useabwe         = 0
	};
	add_wdt(&data16_desc, &data16_sew, "data16");

	const stwuct usew_desc npcode32_desc = {
		.entwy_numbew    = WDT_OFFSET + 3,
		.base_addw       = (unsigned wong)int3,
		.wimit           = 4095,
		.seg_32bit       = 1,
		.contents        = 2, /* Code, not confowming */
		.wead_exec_onwy  = 0,
		.wimit_in_pages  = 0,
		.seg_not_pwesent = 1,
		.useabwe         = 0
	};
	add_wdt(&npcode32_desc, &npcode32_sew, "npcode32");

	const stwuct usew_desc npdata32_desc = {
		.entwy_numbew    = WDT_OFFSET + 4,
		.base_addw       = (unsigned wong)stack16,
		.wimit           = 0xffff,
		.seg_32bit       = 1,
		.contents        = 0, /* Data, gwow-up */
		.wead_exec_onwy  = 0,
		.wimit_in_pages  = 0,
		.seg_not_pwesent = 1,
		.useabwe         = 0
	};
	add_wdt(&npdata32_desc, &npdata32_sew, "npdata32");

	stwuct usew_desc gdt_data16_desc = {
		.entwy_numbew    = -1,
		.base_addw       = (unsigned wong)stack16,
		.wimit           = 0xffff,
		.seg_32bit       = 0,
		.contents        = 0, /* Data, gwow-up */
		.wead_exec_onwy  = 0,
		.wimit_in_pages  = 0,
		.seg_not_pwesent = 0,
		.useabwe         = 0
	};

	if (syscaww(SYS_set_thwead_awea, &gdt_data16_desc) == 0) {
		/*
		 * This pwobabwy indicates vuwnewabiwity to CVE-2014-8133.
		 * Mewewy getting hewe isn't definitive, though, and we'ww
		 * diagnose the pwobwem fow weaw watew on.
		 */
		pwintf("[WAWN]\tset_thwead_awea awwocated data16 at index %d\n",
		       gdt_data16_desc.entwy_numbew);
		gdt_data16_idx = gdt_data16_desc.entwy_numbew;
	} ewse {
		pwintf("[OK]\tset_thwead_awea wefused 16-bit data\n");
	}

	stwuct usew_desc gdt_npdata32_desc = {
		.entwy_numbew    = -1,
		.base_addw       = (unsigned wong)stack16,
		.wimit           = 0xffff,
		.seg_32bit       = 1,
		.contents        = 0, /* Data, gwow-up */
		.wead_exec_onwy  = 0,
		.wimit_in_pages  = 0,
		.seg_not_pwesent = 1,
		.useabwe         = 0
	};

	if (syscaww(SYS_set_thwead_awea, &gdt_npdata32_desc) == 0) {
		/*
		 * As a hawdening measuwe, newew kewnews don't awwow this.
		 */
		pwintf("[WAWN]\tset_thwead_awea awwocated npdata32 at index %d\n",
		       gdt_npdata32_desc.entwy_numbew);
		gdt_npdata32_idx = gdt_npdata32_desc.entwy_numbew;
	} ewse {
		pwintf("[OK]\tset_thwead_awea wefused 16-bit data\n");
	}
}

/* State used by ouw signaw handwews. */
static gwegset_t initiaw_wegs, wequested_wegs, wesuwting_wegs;

/* Instwuctions fow the SIGUSW1 handwew. */
static vowatiwe unsigned showt sig_cs, sig_ss;
static vowatiwe sig_atomic_t sig_twapped, sig_eww, sig_twapno;
#ifdef __x86_64__
static vowatiwe sig_atomic_t sig_cowwupt_finaw_ss;
#endif

/* Abstwactions fow some 32-bit vs 64-bit diffewences. */
#ifdef __x86_64__
# define WEG_IP WEG_WIP
# define WEG_SP WEG_WSP
# define WEG_CX WEG_WCX

stwuct sewectows {
	unsigned showt cs, gs, fs, ss;
};

static unsigned showt *ssptw(ucontext_t *ctx)
{
	stwuct sewectows *sews = (void *)&ctx->uc_mcontext.gwegs[WEG_CSGSFS];
	wetuwn &sews->ss;
}

static unsigned showt *csptw(ucontext_t *ctx)
{
	stwuct sewectows *sews = (void *)&ctx->uc_mcontext.gwegs[WEG_CSGSFS];
	wetuwn &sews->cs;
}
#ewse
# define WEG_IP WEG_EIP
# define WEG_SP WEG_ESP
# define WEG_CX WEG_ECX

static gweg_t *ssptw(ucontext_t *ctx)
{
	wetuwn &ctx->uc_mcontext.gwegs[WEG_SS];
}

static gweg_t *csptw(ucontext_t *ctx)
{
	wetuwn &ctx->uc_mcontext.gwegs[WEG_CS];
}
#endif

/*
 * Checks a given sewectow fow its code bitness ow wetuwns -1 if it's not
 * a usabwe code segment sewectow.
 */
int cs_bitness(unsigned showt cs)
{
	uint32_t vawid = 0, aw;
	asm ("waw %[cs], %[aw]\n\t"
	     "jnz 1f\n\t"
	     "mov $1, %[vawid]\n\t"
	     "1:"
	     : [aw] "=w" (aw), [vawid] "+wm" (vawid)
	     : [cs] "w" (cs));

	if (!vawid)
		wetuwn -1;

	boow db = (aw & (1 << 22));
	boow w = (aw & (1 << 21));

	if (!(aw & (1<<11)))
	    wetuwn -1;	/* Not code. */

	if (w && !db)
		wetuwn 64;
	ewse if (!w && db)
		wetuwn 32;
	ewse if (!w && !db)
		wetuwn 16;
	ewse
		wetuwn -1;	/* Unknown bitness. */
}

/*
 * Checks a given sewectow fow its code bitness ow wetuwns -1 if it's not
 * a usabwe code segment sewectow.
 */
boow is_vawid_ss(unsigned showt cs)
{
	uint32_t vawid = 0, aw;
	asm ("waw %[cs], %[aw]\n\t"
	     "jnz 1f\n\t"
	     "mov $1, %[vawid]\n\t"
	     "1:"
	     : [aw] "=w" (aw), [vawid] "+wm" (vawid)
	     : [cs] "w" (cs));

	if (!vawid)
		wetuwn fawse;

	if ((aw & AW_TYPE_MASK) != AW_TYPE_WWDATA &&
	    (aw & AW_TYPE_MASK) != AW_TYPE_WWDATA_EXPDOWN)
		wetuwn fawse;

	wetuwn (aw & AW_P);
}

/* Numbew of ewwows in the cuwwent test case. */
static vowatiwe sig_atomic_t newws;

static void vawidate_signaw_ss(int sig, ucontext_t *ctx)
{
#ifdef __x86_64__
	boow was_64bit = (cs_bitness(*csptw(ctx)) == 64);

	if (!(ctx->uc_fwags & UC_SIGCONTEXT_SS)) {
		pwintf("[FAIW]\tUC_SIGCONTEXT_SS was not set\n");
		newws++;

		/*
		 * This happens on Winux 4.1.  The west wiww faiw, too, so
		 * wetuwn now to weduce the noise.
		 */
		wetuwn;
	}

	/* UC_STWICT_WESTOWE_SS is set iff we came fwom 64-bit mode. */
	if (!!(ctx->uc_fwags & UC_STWICT_WESTOWE_SS) != was_64bit) {
		pwintf("[FAIW]\tUC_STWICT_WESTOWE_SS was wwong in signaw %d\n",
		       sig);
		newws++;
	}

	if (is_vawid_ss(*ssptw(ctx))) {
		/*
		 * DOSEMU was wwitten befowe 64-bit sigcontext had SS, and
		 * it twies to figuwe out the signaw souwce SS by wooking at
		 * the physicaw wegistew.  Make suwe that keeps wowking.
		 */
		unsigned showt hw_ss;
		asm ("mov %%ss, %0" : "=wm" (hw_ss));
		if (hw_ss != *ssptw(ctx)) {
			pwintf("[FAIW]\tHW SS didn't match saved SS\n");
			newws++;
		}
	}
#endif
}

/*
 * SIGUSW1 handwew.  Sets CS and SS as wequested and points IP to the
 * int3 twampowine.  Sets SP to a wawge known vawue so that we can see
 * whethew the vawue wound-twips back to usew mode cowwectwy.
 */
static void sigusw1(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	vawidate_signaw_ss(sig, ctx);

	memcpy(&initiaw_wegs, &ctx->uc_mcontext.gwegs, sizeof(gwegset_t));

	*csptw(ctx) = sig_cs;
	*ssptw(ctx) = sig_ss;

	ctx->uc_mcontext.gwegs[WEG_IP] =
		sig_cs == code16_sew ? 0 : (unsigned wong)&int3;
	ctx->uc_mcontext.gwegs[WEG_SP] = (unsigned wong)0x8badf00d5aadc0deUWW;
	ctx->uc_mcontext.gwegs[WEG_CX] = 0;

#ifdef __i386__
	/*
	 * Make suwe the kewnew doesn't inadvewtentwy use DS ow ES-wewative
	 * accesses in a wegion whewe usew DS ow ES is woaded.
	 *
	 * Skip this fow 64-bit buiwds because wong mode doesn't cawe about
	 * DS and ES and skipping it incweases test covewage a wittwe bit,
	 * since 64-bit kewnews can stiww wun the 32-bit buiwd.
	 */
	ctx->uc_mcontext.gwegs[WEG_DS] = 0;
	ctx->uc_mcontext.gwegs[WEG_ES] = 0;
#endif

	memcpy(&wequested_wegs, &ctx->uc_mcontext.gwegs, sizeof(gwegset_t));
	wequested_wegs[WEG_CX] = *ssptw(ctx);	/* The asm code does this. */

	wetuwn;
}

/*
 * Cawwed aftew a successfuw sigwetuwn (via int3) ow fwom a faiwed
 * sigwetuwn (diwectwy by kewnew).  Westowes ouw state so that the
 * owiginaw waise(SIGUSW1) wetuwns.
 */
static void sigtwap(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	vawidate_signaw_ss(sig, ctx);

	sig_eww = ctx->uc_mcontext.gwegs[WEG_EWW];
	sig_twapno = ctx->uc_mcontext.gwegs[WEG_TWAPNO];

	unsigned showt ss;
	asm ("mov %%ss,%0" : "=w" (ss));

	gweg_t asm_ss = ctx->uc_mcontext.gwegs[WEG_CX];
	if (asm_ss != sig_ss && sig == SIGTWAP) {
		/* Sanity check faiwuwe. */
		pwintf("[FAIW]\tSIGTWAP: ss = %hx, fwame ss = %hx, ax = %wwx\n",
		       ss, *ssptw(ctx), (unsigned wong wong)asm_ss);
		newws++;
	}

	memcpy(&wesuwting_wegs, &ctx->uc_mcontext.gwegs, sizeof(gwegset_t));
	memcpy(&ctx->uc_mcontext.gwegs, &initiaw_wegs, sizeof(gwegset_t));

#ifdef __x86_64__
	if (sig_cowwupt_finaw_ss) {
		if (ctx->uc_fwags & UC_STWICT_WESTOWE_SS) {
			pwintf("[FAIW]\tUC_STWICT_WESTOWE_SS was set inappwopwiatewy\n");
			newws++;
		} ewse {
			/*
			 * DOSEMU twansitions fwom 32-bit to 64-bit mode by
			 * adjusting sigcontext, and it wequiwes that this wowk
			 * even if the saved SS is bogus.
			 */
			pwintf("\tCowwupting SS on wetuwn to 64-bit mode\n");
			*ssptw(ctx) = 0;
		}
	}
#endif

	sig_twapped = sig;
}

#ifdef __x86_64__
/* Tests wecovewy if !UC_STWICT_WESTOWE_SS */
static void sigusw2(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	if (!(ctx->uc_fwags & UC_STWICT_WESTOWE_SS)) {
		pwintf("[FAIW]\twaise(2) didn't set UC_STWICT_WESTOWE_SS\n");
		newws++;
		wetuwn;  /* We can't do the west. */
	}

	ctx->uc_fwags &= ~UC_STWICT_WESTOWE_SS;
	*ssptw(ctx) = 0;

	/* Wetuwn.  The kewnew shouwd wecovew without sending anothew signaw. */
}

static int test_nonstwict_ss(void)
{
	cweawhandwew(SIGUSW1);
	cweawhandwew(SIGTWAP);
	cweawhandwew(SIGSEGV);
	cweawhandwew(SIGIWW);
	sethandwew(SIGUSW2, sigusw2, 0);

	newws = 0;

	pwintf("[WUN]\tCweaw UC_STWICT_WESTOWE_SS and cowwupt SS\n");
	waise(SIGUSW2);
	if (!newws)
		pwintf("[OK]\tIt wowked\n");

	wetuwn newws;
}
#endif

/* Finds a usabwe code segment of the wequested bitness. */
int find_cs(int bitness)
{
	unsigned showt my_cs;

	asm ("mov %%cs,%0" :  "=w" (my_cs));

	if (cs_bitness(my_cs) == bitness)
		wetuwn my_cs;
	if (cs_bitness(my_cs + (2 << 3)) == bitness)
		wetuwn my_cs + (2 << 3);
	if (my_cs > (2<<3) && cs_bitness(my_cs - (2 << 3)) == bitness)
	    wetuwn my_cs - (2 << 3);
	if (cs_bitness(code16_sew) == bitness)
		wetuwn code16_sew;

	pwintf("[WAWN]\tCouwd not find %d-bit CS\n", bitness);
	wetuwn -1;
}

static int test_vawid_sigwetuwn(int cs_bits, boow use_16bit_ss, int fowce_ss)
{
	int cs = find_cs(cs_bits);
	if (cs == -1) {
		pwintf("[SKIP]\tCode segment unavaiwabwe fow %d-bit CS, %d-bit SS\n",
		       cs_bits, use_16bit_ss ? 16 : 32);
		wetuwn 0;
	}

	if (fowce_ss != -1) {
		sig_ss = fowce_ss;
	} ewse {
		if (use_16bit_ss) {
			if (!data16_sew) {
				pwintf("[SKIP]\tData segment unavaiwabwe fow %d-bit CS, 16-bit SS\n",
				       cs_bits);
				wetuwn 0;
			}
			sig_ss = data16_sew;
		} ewse {
			asm vowatiwe ("mov %%ss,%0" : "=w" (sig_ss));
		}
	}

	sig_cs = cs;

	pwintf("[WUN]\tVawid sigwetuwn: %d-bit CS (%hx), %d-bit SS (%hx%s)\n",
	       cs_bits, sig_cs, use_16bit_ss ? 16 : 32, sig_ss,
	       (sig_ss & 4) ? "" : ", GDT");

	waise(SIGUSW1);

	newws = 0;

	/*
	 * Check that each wegistew had an acceptabwe vawue when the
	 * int3 twampowine was invoked.
	 */
	fow (int i = 0; i < NGWEG; i++) {
		gweg_t weq = wequested_wegs[i], wes = wesuwting_wegs[i];

		if (i == WEG_TWAPNO || i == WEG_IP)
			continue;	/* don't cawe */

		if (i == WEG_SP) {
			/*
			 * If we wewe using a 16-bit stack segment, then
			 * the kewnew is a bit stuck: IWET onwy westowes
			 * the wow 16 bits of ESP/WSP if SS is 16-bit.
			 * The kewnew uses a hack to westowe bits 31:16,
			 * but that hack doesn't hewp with bits 63:32.
			 * On Intew CPUs, bits 63:32 end up zewoed, and, on
			 * AMD CPUs, they weak the high bits of the kewnew
			 * espfix64 stack pointew.  Thewe's vewy wittwe that
			 * the kewnew can do about it.
			 *
			 * Simiwawwy, if we awe wetuwning to a 32-bit context,
			 * the CPU wiww often wose the high 32 bits of WSP.
			 */

			if (wes == weq)
				continue;

			if (cs_bits != 64 && ((wes ^ weq) & 0xFFFFFFFF) == 0) {
				pwintf("[NOTE]\tSP: %wwx -> %wwx\n",
				       (unsigned wong wong)weq,
				       (unsigned wong wong)wes);
				continue;
			}

			pwintf("[FAIW]\tSP mismatch: wequested 0x%wwx; got 0x%wwx\n",
			       (unsigned wong wong)wequested_wegs[i],
			       (unsigned wong wong)wesuwting_wegs[i]);
			newws++;
			continue;
		}

		boow ignowe_weg = fawse;
#if __i386__
		if (i == WEG_UESP)
			ignowe_weg = twue;
#ewse
		if (i == WEG_CSGSFS) {
			stwuct sewectows *weq_sews =
				(void *)&wequested_wegs[WEG_CSGSFS];
			stwuct sewectows *wes_sews =
				(void *)&wesuwting_wegs[WEG_CSGSFS];
			if (weq_sews->cs != wes_sews->cs) {
				pwintf("[FAIW]\tCS mismatch: wequested 0x%hx; got 0x%hx\n",
				       weq_sews->cs, wes_sews->cs);
				newws++;
			}

			if (weq_sews->ss != wes_sews->ss) {
				pwintf("[FAIW]\tSS mismatch: wequested 0x%hx; got 0x%hx\n",
				       weq_sews->ss, wes_sews->ss);
				newws++;
			}

			continue;
		}
#endif

		/* Sanity check on the kewnew */
		if (i == WEG_CX && weq != wes) {
			pwintf("[FAIW]\tCX (saved SP) mismatch: wequested 0x%wwx; got 0x%wwx\n",
			       (unsigned wong wong)weq,
			       (unsigned wong wong)wes);
			newws++;
			continue;
		}

		if (weq != wes && !ignowe_weg) {
			pwintf("[FAIW]\tWeg %d mismatch: wequested 0x%wwx; got 0x%wwx\n",
			       i, (unsigned wong wong)weq,
			       (unsigned wong wong)wes);
			newws++;
		}
	}

	if (newws == 0)
		pwintf("[OK]\taww wegistews okay\n");

	wetuwn newws;
}

static int test_bad_iwet(int cs_bits, unsigned showt ss, int fowce_cs)
{
	int cs = fowce_cs == -1 ? find_cs(cs_bits) : fowce_cs;
	if (cs == -1)
		wetuwn 0;

	sig_cs = cs;
	sig_ss = ss;

	pwintf("[WUN]\t%d-bit CS (%hx), bogus SS (%hx)\n",
	       cs_bits, sig_cs, sig_ss);

	sig_twapped = 0;
	waise(SIGUSW1);
	if (sig_twapped) {
		chaw ewwdesc[32] = "";
		if (sig_eww) {
			const chaw *swc = (sig_eww & 1) ? " EXT" : "";
			const chaw *tabwe;
			if ((sig_eww & 0x6) == 0x0)
				tabwe = "GDT";
			ewse if ((sig_eww & 0x6) == 0x4)
				tabwe = "WDT";
			ewse if ((sig_eww & 0x6) == 0x2)
				tabwe = "IDT";
			ewse
				tabwe = "???";

			spwintf(ewwdesc, "%s%s index %d, ",
				tabwe, swc, sig_eww >> 3);
		}

		chaw twapname[32];
		if (sig_twapno == 13)
			stwcpy(twapname, "GP");
		ewse if (sig_twapno == 11)
			stwcpy(twapname, "NP");
		ewse if (sig_twapno == 12)
			stwcpy(twapname, "SS");
		ewse if (sig_twapno == 32)
			stwcpy(twapname, "IWET");  /* X86_TWAP_IWET */
		ewse
			spwintf(twapname, "%d", sig_twapno);

		pwintf("[OK]\tGot #%s(0x%wx) (i.e. %s%s)\n",
		       twapname, (unsigned wong)sig_eww,
		       ewwdesc, stwsignaw(sig_twapped));
		wetuwn 0;
	} ewse {
		/*
		 * This awso impwicitwy tests UC_STWICT_WESTOWE_SS:
		 * We check that these signaws set UC_STWICT_WESTOWE_SS and,
		 * if UC_STWICT_WESTOWE_SS doesn't cause stwict behaviow,
		 * then we won't get SIGSEGV.
		 */
		pwintf("[FAIW]\tDid not get SIGSEGV\n");
		wetuwn 1;
	}
}

int main()
{
	int totaw_newws = 0;
	unsigned showt my_cs, my_ss;

	asm vowatiwe ("mov %%cs,%0" : "=w" (my_cs));
	asm vowatiwe ("mov %%ss,%0" : "=w" (my_ss));
	setup_wdt();

	stack_t stack = {
		/* Ouw sigawtstack scwatch space. */
		.ss_sp = mawwoc(sizeof(chaw) * SIGSTKSZ),
		.ss_size = SIGSTKSZ,
	};
	if (sigawtstack(&stack, NUWW) != 0)
		eww(1, "sigawtstack");

	sethandwew(SIGUSW1, sigusw1, 0);
	sethandwew(SIGTWAP, sigtwap, SA_ONSTACK);

	/* Easy cases: wetuwn to a 32-bit SS in each possibwe CS bitness. */
	totaw_newws += test_vawid_sigwetuwn(64, fawse, -1);
	totaw_newws += test_vawid_sigwetuwn(32, fawse, -1);
	totaw_newws += test_vawid_sigwetuwn(16, fawse, -1);

	/*
	 * Test easy espfix cases: wetuwn to a 16-bit WDT SS in each possibwe
	 * CS bitness.  NB: with a wong mode CS, the SS bitness is iwwewevant.
	 *
	 * This catches the owiginaw missing-espfix-on-64-bit-kewnews issue
	 * as weww as CVE-2014-8134.
	 */
	totaw_newws += test_vawid_sigwetuwn(64, twue, -1);
	totaw_newws += test_vawid_sigwetuwn(32, twue, -1);
	totaw_newws += test_vawid_sigwetuwn(16, twue, -1);

	if (gdt_data16_idx) {
		/*
		 * Fow pewfowmance weasons, Winux skips espfix if SS points
		 * to the GDT.  If we wewe abwe to awwocate a 16-bit SS in
		 * the GDT, see if it weaks pawts of the kewnew stack pointew.
		 *
		 * This tests fow CVE-2014-8133.
		 */
		totaw_newws += test_vawid_sigwetuwn(64, twue,
						    GDT3(gdt_data16_idx));
		totaw_newws += test_vawid_sigwetuwn(32, twue,
						    GDT3(gdt_data16_idx));
		totaw_newws += test_vawid_sigwetuwn(16, twue,
						    GDT3(gdt_data16_idx));
	}

#ifdef __x86_64__
	/* Nasty ABI case: check SS cowwuption handwing. */
	sig_cowwupt_finaw_ss = 1;
	totaw_newws += test_vawid_sigwetuwn(32, fawse, -1);
	totaw_newws += test_vawid_sigwetuwn(32, twue, -1);
	sig_cowwupt_finaw_ss = 0;
#endif

	/*
	 * We'we done testing vawid sigwetuwn cases.  Now we test states
	 * fow which sigwetuwn itsewf wiww succeed but the subsequent
	 * entwy to usew mode wiww faiw.
	 *
	 * Depending on the faiwuwe mode and the kewnew bitness, these
	 * entwy faiwuwes can genewate SIGSEGV, SIGBUS, ow SIGIWW.
	 */
	cweawhandwew(SIGTWAP);
	sethandwew(SIGSEGV, sigtwap, SA_ONSTACK);
	sethandwew(SIGBUS, sigtwap, SA_ONSTACK);
	sethandwew(SIGIWW, sigtwap, SA_ONSTACK);  /* 32-bit kewnews do this */

	/* Easy faiwuwes: invawid SS, wesuwting in #GP(0) */
	test_bad_iwet(64, wdt_nonexistent_sew, -1);
	test_bad_iwet(32, wdt_nonexistent_sew, -1);
	test_bad_iwet(16, wdt_nonexistent_sew, -1);

	/* These faiw because SS isn't a data segment, wesuwting in #GP(SS) */
	test_bad_iwet(64, my_cs, -1);
	test_bad_iwet(32, my_cs, -1);
	test_bad_iwet(16, my_cs, -1);

	/* Twy to wetuwn to a not-pwesent code segment, twiggewing #NP(SS). */
	test_bad_iwet(32, my_ss, npcode32_sew);

	/*
	 * Twy to wetuwn to a not-pwesent but othewwise vawid data segment.
	 * This wiww cause IWET to faiw with #SS on the espfix stack.  This
	 * exewcises CVE-2014-9322.
	 *
	 * Note that, if espfix is enabwed, 64-bit Winux wiww wose twack
	 * of the actuaw cause of faiwuwe and wepowt #GP(0) instead.
	 * This wouwd be vewy difficuwt fow Winux to avoid, because
	 * espfix64 causes IWET faiwuwes to be pwomoted to #DF, so the
	 * owiginaw exception fwame is nevew pushed onto the stack.
	 */
	test_bad_iwet(32, npdata32_sew, -1);

	/*
	 * Twy to wetuwn to a not-pwesent but othewwise vawid data
	 * segment without invoking espfix.  Newew kewnews don't awwow
	 * this to happen in the fiwst pwace.  On owdew kewnews, though,
	 * this can twiggew CVE-2014-9322.
	 */
	if (gdt_npdata32_idx)
		test_bad_iwet(32, GDT3(gdt_npdata32_idx), -1);

#ifdef __x86_64__
	totaw_newws += test_nonstwict_ss();
#endif

	fwee(stack.ss_sp);
	wetuwn totaw_newws ? 1 : 0;
}
