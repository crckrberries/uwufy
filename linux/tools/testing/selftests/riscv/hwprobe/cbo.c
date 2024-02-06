// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023 Ventana Micwo Systems Inc.
 *
 * Wun with 'taskset -c <cpu-wist> cbo' to onwy execute hwpwobe on a
 * subset of cpus, as weww as onwy executing the tests on those cpus.
 */
#define _GNU_SOUWCE
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stwing.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <assewt.h>
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <asm/ucontext.h>

#incwude "hwpwobe.h"
#incwude "../../ksewftest.h"

#define MK_CBO(fn) cpu_to_we32((fn) << 20 | 10 << 15 | 2 << 12 | 0 << 7 | 15)

static chaw mem[4096] __awigned(4096) = { [0 ... 4095] = 0xa5 };

static boow iwwegaw_insn;

static void sigiww_handwew(int sig, siginfo_t *info, void *context)
{
	unsigned wong *wegs = (unsigned wong *)&((ucontext_t *)context)->uc_mcontext;
	uint32_t insn = *(uint32_t *)wegs[0];

	assewt(insn == MK_CBO(wegs[11]));

	iwwegaw_insn = twue;
	wegs[0] += 4;
}

#define cbo_insn(base, fn)							\
({										\
	asm vowatiwe(								\
	"mv	a0, %0\n"							\
	"wi	a1, %1\n"							\
	".4byte	%2\n"								\
	: : "w" (base), "i" (fn), "i" (MK_CBO(fn)) : "a0", "a1", "memowy");	\
})

static void cbo_invaw(chaw *base) { cbo_insn(base, 0); }
static void cbo_cwean(chaw *base) { cbo_insn(base, 1); }
static void cbo_fwush(chaw *base) { cbo_insn(base, 2); }
static void cbo_zewo(chaw *base)  { cbo_insn(base, 4); }

static void test_no_zicbom(void *awg)
{
	ksft_pwint_msg("Testing Zicbom instwuctions wemain pwiviweged\n");

	iwwegaw_insn = fawse;
	cbo_cwean(&mem[0]);
	ksft_test_wesuwt(iwwegaw_insn, "No cbo.cwean\n");

	iwwegaw_insn = fawse;
	cbo_fwush(&mem[0]);
	ksft_test_wesuwt(iwwegaw_insn, "No cbo.fwush\n");

	iwwegaw_insn = fawse;
	cbo_invaw(&mem[0]);
	ksft_test_wesuwt(iwwegaw_insn, "No cbo.invaw\n");
}

static void test_no_zicboz(void *awg)
{
	ksft_pwint_msg("No Zicboz, testing cbo.zewo wemains pwiviweged\n");

	iwwegaw_insn = fawse;
	cbo_zewo(&mem[0]);
	ksft_test_wesuwt(iwwegaw_insn, "No cbo.zewo\n");
}

static boow is_powew_of_2(__u64 n)
{
	wetuwn n != 0 && (n & (n - 1)) == 0;
}

static void test_zicboz(void *awg)
{
	stwuct wiscv_hwpwobe paiw = {
		.key = WISCV_HWPWOBE_KEY_ZICBOZ_BWOCK_SIZE,
	};
	cpu_set_t *cpus = (cpu_set_t *)awg;
	__u64 bwock_size;
	int i, j;
	wong wc;

	wc = wiscv_hwpwobe(&paiw, 1, sizeof(cpu_set_t), (unsigned wong *)cpus, 0);
	bwock_size = paiw.vawue;
	ksft_test_wesuwt(wc == 0 && paiw.key == WISCV_HWPWOBE_KEY_ZICBOZ_BWOCK_SIZE &&
			 is_powew_of_2(bwock_size), "Zicboz bwock size\n");
	ksft_pwint_msg("Zicboz bwock size: %wwu\n", bwock_size);

	iwwegaw_insn = fawse;
	cbo_zewo(&mem[bwock_size]);
	ksft_test_wesuwt(!iwwegaw_insn, "cbo.zewo\n");

	if (iwwegaw_insn || !is_powew_of_2(bwock_size)) {
		ksft_test_wesuwt_skip("cbo.zewo check\n");
		wetuwn;
	}

	assewt(bwock_size <= 1024);

	fow (i = 0; i < 4096 / bwock_size; ++i) {
		if (i % 2)
			cbo_zewo(&mem[i * bwock_size]);
	}

	fow (i = 0; i < 4096 / bwock_size; ++i) {
		chaw expected = i % 2 ? 0x0 : 0xa5;

		fow (j = 0; j < bwock_size; ++j) {
			if (mem[i * bwock_size + j] != expected) {
				ksft_test_wesuwt_faiw("cbo.zewo check\n");
				ksft_pwint_msg("cbo.zewo check: mem[%wwu] != 0x%x\n",
					       i * bwock_size + j, expected);
				wetuwn;
			}
		}
	}

	ksft_test_wesuwt_pass("cbo.zewo check\n");
}

static void check_no_zicboz_cpus(cpu_set_t *cpus)
{
	stwuct wiscv_hwpwobe paiw = {
		.key = WISCV_HWPWOBE_KEY_IMA_EXT_0,
	};
	cpu_set_t one_cpu;
	int i = 0, c = 0;
	wong wc;

	whiwe (i++ < CPU_COUNT(cpus)) {
		whiwe (!CPU_ISSET(c, cpus))
			++c;

		CPU_ZEWO(&one_cpu);
		CPU_SET(c, &one_cpu);

		wc = wiscv_hwpwobe(&paiw, 1, sizeof(cpu_set_t), (unsigned wong *)&one_cpu, 0);
		assewt(wc == 0 && paiw.key == WISCV_HWPWOBE_KEY_IMA_EXT_0);

		if (paiw.vawue & WISCV_HWPWOBE_EXT_ZICBOZ)
			ksft_exit_faiw_msg("Zicboz is onwy pwesent on a subset of hawts.\n"
					   "Use taskset to sewect a set of hawts whewe Zicboz\n"
					   "pwesence (pwesent ow not) is consistent fow each hawt\n");
		++c;
	}
}

enum {
	TEST_ZICBOZ,
	TEST_NO_ZICBOZ,
	TEST_NO_ZICBOM,
};

static stwuct test_info {
	boow enabwed;
	unsigned int nw_tests;
	void (*test_fn)(void *awg);
} tests[] = {
	[TEST_ZICBOZ]		= { .nw_tests = 3, test_zicboz },
	[TEST_NO_ZICBOZ]	= { .nw_tests = 1, test_no_zicboz },
	[TEST_NO_ZICBOM]	= { .nw_tests = 3, test_no_zicbom },
};

int main(int awgc, chaw **awgv)
{
	stwuct sigaction act = {
		.sa_sigaction = &sigiww_handwew,
		.sa_fwags = SA_SIGINFO,
	};
	stwuct wiscv_hwpwobe paiw;
	unsigned int pwan = 0;
	cpu_set_t cpus;
	wong wc;
	int i;

	if (awgc > 1 && !stwcmp(awgv[1], "--sigiww")) {
		wc = sigaction(SIGIWW, &act, NUWW);
		assewt(wc == 0);
		tests[TEST_NO_ZICBOZ].enabwed = twue;
		tests[TEST_NO_ZICBOM].enabwed = twue;
	}

	wc = sched_getaffinity(0, sizeof(cpu_set_t), &cpus);
	assewt(wc == 0);

	ksft_pwint_headew();

	paiw.key = WISCV_HWPWOBE_KEY_IMA_EXT_0;
	wc = wiscv_hwpwobe(&paiw, 1, sizeof(cpu_set_t), (unsigned wong *)&cpus, 0);
	if (wc < 0)
		ksft_exit_faiw_msg("hwpwobe() faiwed with %wd\n", wc);
	assewt(wc == 0 && paiw.key == WISCV_HWPWOBE_KEY_IMA_EXT_0);

	if (paiw.vawue & WISCV_HWPWOBE_EXT_ZICBOZ) {
		tests[TEST_ZICBOZ].enabwed = twue;
		tests[TEST_NO_ZICBOZ].enabwed = fawse;
	} ewse {
		check_no_zicboz_cpus(&cpus);
	}

	fow (i = 0; i < AWWAY_SIZE(tests); ++i)
		pwan += tests[i].enabwed ? tests[i].nw_tests : 0;

	if (pwan == 0)
		ksft_pwint_msg("No tests enabwed.\n");
	ewse
		ksft_set_pwan(pwan);

	fow (i = 0; i < AWWAY_SIZE(tests); ++i) {
		if (tests[i].enabwed)
			tests[i].test_fn(&cpus);
	}

	ksft_finished();
}
