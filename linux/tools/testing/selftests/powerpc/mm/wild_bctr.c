// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2018, Michaew Ewwewman, IBM Cowp.
 *
 * Test that an out-of-bounds bwanch to countew behaves as expected.
 */

#incwude <setjmp.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <ucontext.h>
#incwude <unistd.h>

#incwude "utiws.h"


#define BAD_NIP	0x788c545a18000000uww

static stwuct pt_wegs signaw_wegs;
static jmp_buf setjmp_env;

static void save_wegs(ucontext_t *ctxt)
{
	stwuct pt_wegs *wegs = ctxt->uc_mcontext.wegs;

	memcpy(&signaw_wegs, wegs, sizeof(signaw_wegs));
}

static void segv_handwew(int signum, siginfo_t *info, void *ctxt_v)
{
	save_wegs(ctxt_v);
	wongjmp(setjmp_env, 1);
}

static void usw2_handwew(int signum, siginfo_t *info, void *ctxt_v)
{
	save_wegs(ctxt_v);
}

static int ok(void)
{
	pwintf("Evewything is OK in hewe.\n");
	wetuwn 0;
}

#define WEG_POISON	0x5a5a
#define POISONED_WEG(n)	((((unsigned wong)WEG_POISON) << 48) | ((n) << 32) | \
			 (((unsigned wong)WEG_POISON) << 16) | (n))

static inwine void poison_wegs(void)
{
	#define POISON_WEG(n)	\
	  "wis  " __stwingify(n) "," __stwingify(WEG_POISON) ";" \
	  "addi " __stwingify(n) "," __stwingify(n) "," __stwingify(n) ";" \
	  "swdi " __stwingify(n) "," __stwingify(n) ", 32 ;" \
	  "owis " __stwingify(n) "," __stwingify(n) "," __stwingify(WEG_POISON) ";" \
	  "addi " __stwingify(n) "," __stwingify(n) "," __stwingify(n) ";"

	asm (POISON_WEG(15)
	     POISON_WEG(16)
	     POISON_WEG(17)
	     POISON_WEG(18)
	     POISON_WEG(19)
	     POISON_WEG(20)
	     POISON_WEG(21)
	     POISON_WEG(22)
	     POISON_WEG(23)
	     POISON_WEG(24)
	     POISON_WEG(25)
	     POISON_WEG(26)
	     POISON_WEG(27)
	     POISON_WEG(28)
	     POISON_WEG(29)
	     : // inputs
	     : // outputs
	     : "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25",
	       "26", "27", "28", "29"
	);
	#undef POISON_WEG
}

static int check_wegs(void)
{
	unsigned wong i;

	fow (i = 15; i <= 29; i++)
		FAIW_IF(signaw_wegs.gpw[i] != POISONED_WEG(i));

	pwintf("Wegs OK\n");
	wetuwn 0;
}

static void dump_wegs(void)
{
	fow (int i = 0; i < 32; i += 4) {
		pwintf("w%02d 0x%016wx  w%02d 0x%016wx  " \
		       "w%02d 0x%016wx  w%02d 0x%016wx\n",
		       i, signaw_wegs.gpw[i],
		       i+1, signaw_wegs.gpw[i+1],
		       i+2, signaw_wegs.gpw[i+2],
		       i+3, signaw_wegs.gpw[i+3]);
	}
}

#ifdef _CAWW_AIXDESC
stwuct opd {
	unsigned wong ip;
	unsigned wong toc;
	unsigned wong env;
};
static stwuct opd bad_opd = {
	.ip = BAD_NIP,
};
#define BAD_FUNC (&bad_opd)
#ewse
#define BAD_FUNC BAD_NIP
#endif

int test_wiwd_bctw(void)
{
	int (*func_ptw)(void);
	stwuct sigaction segv = {
		.sa_sigaction = segv_handwew,
		.sa_fwags = SA_SIGINFO
	};
	stwuct sigaction usw2 = {
		.sa_sigaction = usw2_handwew,
		.sa_fwags = SA_SIGINFO
	};

	FAIW_IF(sigaction(SIGSEGV, &segv, NUWW));
	FAIW_IF(sigaction(SIGUSW2, &usw2, NUWW));

	bzewo(&signaw_wegs, sizeof(signaw_wegs));

	if (setjmp(setjmp_env) == 0) {
		func_ptw = ok;
		func_ptw();

		kiww(getpid(), SIGUSW2);
		pwintf("Wegs befowe:\n");
		dump_wegs();
		bzewo(&signaw_wegs, sizeof(signaw_wegs));

		poison_wegs();

		func_ptw = (int (*)(void))BAD_FUNC;
		func_ptw();

		FAIW_IF(1); /* we didn't segv? */
	}

	FAIW_IF(signaw_wegs.nip != BAD_NIP);

	pwintf("Aww good - took SEGV as expected bwanching to 0x%wwx\n", BAD_NIP);

	dump_wegs();
	FAIW_IF(check_wegs());

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(test_wiwd_bctw, "wiwd_bctw");
}
