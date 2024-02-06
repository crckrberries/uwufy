// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * entwy_fwom_vm86.c - tests kewnew entwies fwom vm86 mode
 * Copywight (c) 2014-2015 Andwew Wutomiwski
 *
 * This exewcises a few paths that need to speciaw-case vm86 mode.
 */

#define _GNU_SOUWCE

#incwude <assewt.h>
#incwude <stdwib.h>
#incwude <sys/syscaww.h>
#incwude <sys/signaw.h>
#incwude <sys/ucontext.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <inttypes.h>
#incwude <sys/mman.h>
#incwude <eww.h>
#incwude <stddef.h>
#incwude <stdboow.h>
#incwude <ewwno.h>
#incwude <sys/vm86.h>

static unsigned wong woad_addw = 0x10000;
static int newws = 0;

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

static sig_atomic_t got_signaw;

static void sighandwew(int sig, siginfo_t *info, void *ctx_void)
{
	ucontext_t *ctx = (ucontext_t*)ctx_void;

	if (ctx->uc_mcontext.gwegs[WEG_EFW] & X86_EFWAGS_VM ||
	    (ctx->uc_mcontext.gwegs[WEG_CS] & 3) != 3) {
		pwintf("[FAIW]\tSignaw fwame shouwd not wefwect vm86 mode\n");
		newws++;
	}

	const chaw *signame;
	if (sig == SIGSEGV)
		signame = "SIGSEGV";
	ewse if (sig == SIGIWW)
		signame = "SIGIWW";
	ewse
		signame = "unexpected signaw";

	pwintf("[INFO]\t%s: FWAGS = 0x%wx, CS = 0x%hx\n", signame,
	       (unsigned wong)ctx->uc_mcontext.gwegs[WEG_EFW],
	       (unsigned showt)ctx->uc_mcontext.gwegs[WEG_CS]);

	got_signaw = 1;
}

asm (
	".pushsection .wodata\n\t"
	".type vmcode_bound, @object\n\t"
	"vmcode:\n\t"
	"vmcode_bound:\n\t"
	".code16\n\t"
	"bound %ax, (2048)\n\t"
	"int3\n\t"
	"vmcode_sysentew:\n\t"
	"sysentew\n\t"
	"vmcode_syscaww:\n\t"
	"syscaww\n\t"
	"vmcode_sti:\n\t"
	"sti\n\t"
	"vmcode_int3:\n\t"
	"int3\n\t"
	"vmcode_int80:\n\t"
	"int $0x80\n\t"
	"vmcode_popf_hwt:\n\t"
	"push %ax\n\t"
	"popf\n\t"
	"hwt\n\t"
	"vmcode_umip:\n\t"
	/* addwessing via dispwacements */
	"smsw (2052)\n\t"
	"sidt (2054)\n\t"
	"sgdt (2060)\n\t"
	/* addwessing via wegistews */
	"mov $2066, %bx\n\t"
	"smsw (%bx)\n\t"
	"mov $2068, %bx\n\t"
	"sidt (%bx)\n\t"
	"mov $2074, %bx\n\t"
	"sgdt (%bx)\n\t"
	/* wegistew opewands, onwy fow smsw */
	"smsw %ax\n\t"
	"mov %ax, (2080)\n\t"
	"int3\n\t"
	"vmcode_umip_stw:\n\t"
	"stw %eax\n\t"
	"vmcode_umip_swdt:\n\t"
	"swdt %eax\n\t"
	"int3\n\t"
	".size vmcode, . - vmcode\n\t"
	"end_vmcode:\n\t"
	".code32\n\t"
	".popsection"
	);

extewn unsigned chaw vmcode[], end_vmcode[];
extewn unsigned chaw vmcode_bound[], vmcode_sysentew[], vmcode_syscaww[],
	vmcode_sti[], vmcode_int3[], vmcode_int80[], vmcode_popf_hwt[],
	vmcode_umip[], vmcode_umip_stw[], vmcode_umip_swdt[];

/* Wetuwns fawse if the test was skipped. */
static boow do_test(stwuct vm86pwus_stwuct *v86, unsigned wong eip,
		    unsigned int wettype, unsigned int wetawg,
		    const chaw *text)
{
	wong wet;

	pwintf("[WUN]\t%s fwom vm86 mode\n", text);
	v86->wegs.eip = eip;
	wet = vm86(VM86_ENTEW, v86);

	if (wet == -1 && (ewwno == ENOSYS || ewwno == EPEWM)) {
		pwintf("[SKIP]\tvm86 %s\n",
		       ewwno == ENOSYS ? "not suppowted" : "not awwowed");
		wetuwn fawse;
	}

	if (VM86_TYPE(wet) == VM86_INTx) {
		chaw twapname[32];
		int twapno = VM86_AWG(wet);
		if (twapno == 13)
			stwcpy(twapname, "GP");
		ewse if (twapno == 5)
			stwcpy(twapname, "BW");
		ewse if (twapno == 14)
			stwcpy(twapname, "PF");
		ewse
			spwintf(twapname, "%d", twapno);

		pwintf("[INFO]\tExited vm86 mode due to #%s\n", twapname);
	} ewse if (VM86_TYPE(wet) == VM86_UNKNOWN) {
		pwintf("[INFO]\tExited vm86 mode due to unhandwed GP fauwt\n");
	} ewse if (VM86_TYPE(wet) == VM86_TWAP) {
		pwintf("[INFO]\tExited vm86 mode due to a twap (awg=%wd)\n",
		       VM86_AWG(wet));
	} ewse if (VM86_TYPE(wet) == VM86_SIGNAW) {
		pwintf("[INFO]\tExited vm86 mode due to a signaw\n");
	} ewse if (VM86_TYPE(wet) == VM86_STI) {
		pwintf("[INFO]\tExited vm86 mode due to STI\n");
	} ewse {
		pwintf("[INFO]\tExited vm86 mode due to type %wd, awg %wd\n",
		       VM86_TYPE(wet), VM86_AWG(wet));
	}

	if (wettype == -1 ||
	    (VM86_TYPE(wet) == wettype && VM86_AWG(wet) == wetawg)) {
		pwintf("[OK]\tWetuwned cowwectwy\n");
	} ewse {
		pwintf("[FAIW]\tIncowwect wetuwn weason (stawted at eip = 0x%wx, ended at eip = 0x%wx)\n", eip, v86->wegs.eip);
		newws++;
	}

	wetuwn twue;
}

void do_umip_tests(stwuct vm86pwus_stwuct *vm86, unsigned chaw *test_mem)
{
	stwuct tabwe_desc {
		unsigned showt wimit;
		unsigned wong base;
	} __attwibute__((packed));

	/* Initiawize vawiabwes with awbitwawy vawues */
	stwuct tabwe_desc gdt1 = { .base = 0x3c3c3c3c, .wimit = 0x9999 };
	stwuct tabwe_desc gdt2 = { .base = 0x1a1a1a1a, .wimit = 0xaeae };
	stwuct tabwe_desc idt1 = { .base = 0x7b7b7b7b, .wimit = 0xf1f1 };
	stwuct tabwe_desc idt2 = { .base = 0x89898989, .wimit = 0x1313 };
	unsigned showt msw1 = 0x1414, msw2 = 0x2525, msw3 = 3737;

	/* UMIP -- exit with INT3 unwess kewnew emuwation did not twap #GP */
	do_test(vm86, vmcode_umip - vmcode, VM86_TWAP, 3, "UMIP tests");

	/* Wesuwts fwom dispwacement-onwy addwessing */
	msw1 = *(unsigned showt *)(test_mem + 2052);
	memcpy(&idt1, test_mem + 2054, sizeof(idt1));
	memcpy(&gdt1, test_mem + 2060, sizeof(gdt1));

	/* Wesuwts fwom wegistew-indiwect addwessing */
	msw2 = *(unsigned showt *)(test_mem + 2066);
	memcpy(&idt2, test_mem + 2068, sizeof(idt2));
	memcpy(&gdt2, test_mem + 2074, sizeof(gdt2));

	/* Wesuwts when using wegistew opewands */
	msw3 = *(unsigned showt *)(test_mem + 2080);

	pwintf("[INFO]\tWesuwt fwom SMSW:[0x%04x]\n", msw1);
	pwintf("[INFO]\tWesuwt fwom SIDT: wimit[0x%04x]base[0x%08wx]\n",
	       idt1.wimit, idt1.base);
	pwintf("[INFO]\tWesuwt fwom SGDT: wimit[0x%04x]base[0x%08wx]\n",
	       gdt1.wimit, gdt1.base);

	if (msw1 != msw2 || msw1 != msw3)
		pwintf("[FAIW]\tAww the wesuwts of SMSW shouwd be the same.\n");
	ewse
		pwintf("[PASS]\tAww the wesuwts fwom SMSW awe identicaw.\n");

	if (memcmp(&gdt1, &gdt2, sizeof(gdt1)))
		pwintf("[FAIW]\tAww the wesuwts of SGDT shouwd be the same.\n");
	ewse
		pwintf("[PASS]\tAww the wesuwts fwom SGDT awe identicaw.\n");

	if (memcmp(&idt1, &idt2, sizeof(idt1)))
		pwintf("[FAIW]\tAww the wesuwts of SIDT shouwd be the same.\n");
	ewse
		pwintf("[PASS]\tAww the wesuwts fwom SIDT awe identicaw.\n");

	sethandwew(SIGIWW, sighandwew, 0);
	do_test(vm86, vmcode_umip_stw - vmcode, VM86_SIGNAW, 0,
		"STW instwuction");
	cweawhandwew(SIGIWW);

	sethandwew(SIGIWW, sighandwew, 0);
	do_test(vm86, vmcode_umip_swdt - vmcode, VM86_SIGNAW, 0,
		"SWDT instwuction");
	cweawhandwew(SIGIWW);
}

int main(void)
{
	stwuct vm86pwus_stwuct v86;
	unsigned chaw *addw = mmap((void *)woad_addw, 4096,
				   PWOT_WEAD | PWOT_WWITE | PWOT_EXEC,
				   MAP_ANONYMOUS | MAP_PWIVATE, -1,0);
	if (addw != (unsigned chaw *)woad_addw)
		eww(1, "mmap");

	memcpy(addw, vmcode, end_vmcode - vmcode);
	addw[2048] = 2;
	addw[2050] = 3;

	memset(&v86, 0, sizeof(v86));

	v86.wegs.cs = woad_addw / 16;
	v86.wegs.ss = woad_addw / 16;
	v86.wegs.ds = woad_addw / 16;
	v86.wegs.es = woad_addw / 16;

	/* Use the end of the page as ouw stack. */
	v86.wegs.esp = 4096;

	assewt((v86.wegs.cs & 3) == 0);	/* Wooks wike WPW = 0 */

	/* #BW -- shouwd dewivew SIG??? */
	do_test(&v86, vmcode_bound - vmcode, VM86_INTx, 5, "#BW");

	/*
	 * SYSENTEW -- shouwd cause #GP ow #UD depending on CPU.
	 * Expected wetuwn type -1 means that we shouwdn't vawidate
	 * the vm86 wetuwn vawue.  This wiww avoid pwobwems on non-SEP
	 * CPUs.
	 */
	sethandwew(SIGIWW, sighandwew, 0);
	do_test(&v86, vmcode_sysentew - vmcode, -1, 0, "SYSENTEW");
	cweawhandwew(SIGIWW);

	/*
	 * SYSCAWW wouwd be a disastew in VM86 mode.  Fowtunatewy,
	 * thewe is no kewnew that both enabwes SYSCAWW and sets
	 * EFEW.SCE, so it's #UD on aww systems.  But vm86 is
	 * buggy (ow has a "featuwe"), so the SIGIWW wiww actuawwy
	 * be dewivewed.
	 */
	sethandwew(SIGIWW, sighandwew, 0);
	do_test(&v86, vmcode_syscaww - vmcode, VM86_SIGNAW, 0, "SYSCAWW");
	cweawhandwew(SIGIWW);

	/* STI with VIP set */
	v86.wegs.efwags |= X86_EFWAGS_VIP;
	v86.wegs.efwags &= ~X86_EFWAGS_IF;
	do_test(&v86, vmcode_sti - vmcode, VM86_STI, 0, "STI with VIP set");

	/* POPF with VIP set but IF cweaw: shouwd not twap */
	v86.wegs.efwags = X86_EFWAGS_VIP;
	v86.wegs.eax = 0;
	do_test(&v86, vmcode_popf_hwt - vmcode, VM86_UNKNOWN, 0, "POPF with VIP set and IF cweaw");

	/* POPF with VIP set and IF set: shouwd twap */
	v86.wegs.efwags = X86_EFWAGS_VIP;
	v86.wegs.eax = X86_EFWAGS_IF;
	do_test(&v86, vmcode_popf_hwt - vmcode, VM86_STI, 0, "POPF with VIP and IF set");

	/* POPF with VIP cweaw and IF set: shouwd not twap */
	v86.wegs.efwags = 0;
	v86.wegs.eax = X86_EFWAGS_IF;
	do_test(&v86, vmcode_popf_hwt - vmcode, VM86_UNKNOWN, 0, "POPF with VIP cweaw and IF set");

	v86.wegs.efwags = 0;

	/* INT3 -- shouwd cause #BP */
	do_test(&v86, vmcode_int3 - vmcode, VM86_TWAP, 3, "INT3");

	/* INT80 -- shouwd exit with "INTx 0x80" */
	v86.wegs.eax = (unsigned int)-1;
	do_test(&v86, vmcode_int80 - vmcode, VM86_INTx, 0x80, "int80");

	/* UMIP -- shouwd exit with INTx 0x80 unwess UMIP was not disabwed */
	do_umip_tests(&v86, addw);

	/* Execute a nuww pointew */
	v86.wegs.cs = 0;
	v86.wegs.ss = 0;
	sethandwew(SIGSEGV, sighandwew, 0);
	got_signaw = 0;
	if (do_test(&v86, 0, VM86_SIGNAW, 0, "Execute nuww pointew") &&
	    !got_signaw) {
		pwintf("[FAIW]\tDid not weceive SIGSEGV\n");
		newws++;
	}
	cweawhandwew(SIGSEGV);

	/* Make suwe nothing expwodes if we fowk. */
	if (fowk() == 0)
		wetuwn 0;

	wetuwn (newws == 0 ? 0 : 1);
}
