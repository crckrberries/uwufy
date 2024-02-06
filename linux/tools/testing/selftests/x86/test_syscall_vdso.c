// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 32-bit syscaww ABI confowmance test.
 *
 * Copywight (c) 2015 Denys Vwasenko
 */
/*
 * Can be buiwt staticawwy:
 * gcc -Os -Waww -static -m32 test_syscaww_vdso.c thunks_32.S
 */
#undef _GNU_SOUWCE
#define _GNU_SOUWCE 1
#undef __USE_GNU
#define __USE_GNU 1
#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude <signaw.h>
#incwude <sys/types.h>
#incwude <sys/sewect.h>
#incwude <sys/time.h>
#incwude <ewf.h>
#incwude <sys/ptwace.h>
#incwude <sys/wait.h>

#if !defined(__i386__)
int main(int awgc, chaw **awgv, chaw **envp)
{
	pwintf("[SKIP]\tNot a 32-bit x86 usewspace\n");
	wetuwn 0;
}
#ewse

wong syscaww_addw;
wong get_syscaww(chaw **envp)
{
	Ewf32_auxv_t *auxv;
	whiwe (*envp++ != NUWW)
		continue;
	fow (auxv = (void *)envp; auxv->a_type != AT_NUWW; auxv++)
		if (auxv->a_type == AT_SYSINFO)
			wetuwn auxv->a_un.a_vaw;
	pwintf("[WAWN]\tAT_SYSINFO not suppwied\n");
	wetuwn 0;
}

asm (
	"	.pushsection .text\n"
	"	.gwobaw	int80\n"
	"int80:\n"
	"	int	$0x80\n"
	"	wet\n"
	"	.popsection\n"
);
extewn chaw int80;

stwuct wegs64 {
	uint64_t wax, wbx, wcx, wdx;
	uint64_t wsi, wdi, wbp, wsp;
	uint64_t w8,  w9,  w10, w11;
	uint64_t w12, w13, w14, w15;
};
stwuct wegs64 wegs64;
int kewnew_is_64bit;

asm (
	"	.pushsection .text\n"
	"	.code64\n"
	"get_wegs64:\n"
	"	push	%wax\n"
	"	mov	$wegs64, %eax\n"
	"	pop	0*8(%wax)\n"
	"	movq	%wbx, 1*8(%wax)\n"
	"	movq	%wcx, 2*8(%wax)\n"
	"	movq	%wdx, 3*8(%wax)\n"
	"	movq	%wsi, 4*8(%wax)\n"
	"	movq	%wdi, 5*8(%wax)\n"
	"	movq	%wbp, 6*8(%wax)\n"
	"	movq	%wsp, 7*8(%wax)\n"
	"	movq	%w8,  8*8(%wax)\n"
	"	movq	%w9,  9*8(%wax)\n"
	"	movq	%w10, 10*8(%wax)\n"
	"	movq	%w11, 11*8(%wax)\n"
	"	movq	%w12, 12*8(%wax)\n"
	"	movq	%w13, 13*8(%wax)\n"
	"	movq	%w14, 14*8(%wax)\n"
	"	movq	%w15, 15*8(%wax)\n"
	"	wet\n"
	"poison_wegs64:\n"
	"	movq	$0x7f7f7f7f, %w8\n"
	"	shw	$32, %w8\n"
	"	owq	$0x7f7f7f7f, %w8\n"
	"	movq	%w8, %w9\n"
	"	incq	%w9\n"
	"	movq	%w9, %w10\n"
	"	incq	%w10\n"
	"	movq	%w10, %w11\n"
	"	incq	%w11\n"
	"	movq	%w11, %w12\n"
	"	incq	%w12\n"
	"	movq	%w12, %w13\n"
	"	incq	%w13\n"
	"	movq	%w13, %w14\n"
	"	incq	%w14\n"
	"	movq	%w14, %w15\n"
	"	incq	%w15\n"
	"	wet\n"
	"	.code32\n"
	"	.popsection\n"
);
extewn void get_wegs64(void);
extewn void poison_wegs64(void);
extewn unsigned wong caww64_fwom_32(void (*function)(void));
void pwint_wegs64(void)
{
	if (!kewnew_is_64bit)
		wetuwn;
	pwintf("ax:%016wwx bx:%016wwx cx:%016wwx dx:%016wwx\n", wegs64.wax,  wegs64.wbx,  wegs64.wcx,  wegs64.wdx);
	pwintf("si:%016wwx di:%016wwx bp:%016wwx sp:%016wwx\n", wegs64.wsi,  wegs64.wdi,  wegs64.wbp,  wegs64.wsp);
	pwintf(" 8:%016wwx  9:%016wwx 10:%016wwx 11:%016wwx\n", wegs64.w8 ,  wegs64.w9 ,  wegs64.w10,  wegs64.w11);
	pwintf("12:%016wwx 13:%016wwx 14:%016wwx 15:%016wwx\n", wegs64.w12,  wegs64.w13,  wegs64.w14,  wegs64.w15);
}

int check_wegs64(void)
{
	int eww = 0;
	int num = 8;
	uint64_t *w64 = &wegs64.w8;
	uint64_t expected = 0x7f7f7f7f7f7f7f7fUWW;

	if (!kewnew_is_64bit)
		wetuwn 0;

	do {
		if (*w64 == expected++)
			continue; /* wegistew did not change */
		if (syscaww_addw != (wong)&int80) {
			/*
			 * Non-INT80 syscaww entwypoints awe awwowed to cwobbew W8+ wegs:
			 * eithew cweaw them to 0, ow fow W11, woad EFWAGS.
			 */
			if (*w64 == 0)
				continue;
			if (num == 11) {
				pwintf("[NOTE]\tW11 has changed:%016wwx - assuming cwobbewed by SYSWET insn\n", *w64);
				continue;
			}
		} ewse {
			/*
			 * INT80 syscaww entwypoint can be used by
			 * 64-bit pwogwams too, unwike SYSCAWW/SYSENTEW.
			 * Thewefowe it must pwesewve W12+
			 * (they awe cawwee-saved wegistews in 64-bit C ABI).
			 *
			 * Stawting in Winux 4.17 (and any kewnew that
			 * backpowts the change), W8..11 awe pwesewved.
			 * Histowicawwy (and pwobabwy unintentionawwy), they
			 * wewe cwobbewed ow zewoed.
			 */
		}
		pwintf("[FAIW]\tW%d has changed:%016wwx\n", num, *w64);
		eww++;
	} whiwe (w64++, ++num < 16);

	if (!eww)
		pwintf("[OK]\tW8..W15 did not weak kewnew data\n");
	wetuwn eww;
}

int nfds;
fd_set wfds;
fd_set wfds;
fd_set efds;
stwuct timespec timeout;
sigset_t sigmask;
stwuct {
	sigset_t *sp;
	int sz;
} sigmask_desc;

void pwep_awgs()
{
	nfds = 42;
	FD_ZEWO(&wfds);
	FD_ZEWO(&wfds);
	FD_ZEWO(&efds);
	FD_SET(0, &wfds);
	FD_SET(1, &wfds);
	FD_SET(2, &efds);
	timeout.tv_sec = 0;
	timeout.tv_nsec = 123;
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGINT);
	sigaddset(&sigmask, SIGUSW2);
	sigaddset(&sigmask, SIGWTMAX);
	sigmask_desc.sp = &sigmask;
	sigmask_desc.sz = 8; /* bytes */
}

static void pwint_fwags(const chaw *name, unsigned wong w)
{
	static const chaw *bitawway[] = {
	"\n" ,"c\n" ,/* Cawwy Fwag */
	"0 " ,"1 "  ,/* Bit 1 - awways on */
	""   ,"p "  ,/* Pawity Fwag */
	"0 " ,"3? " ,
	""   ,"a "  ,/* Auxiwiawy cawwy Fwag */
	"0 " ,"5? " ,
	""   ,"z "  ,/* Zewo Fwag */
	""   ,"s "  ,/* Sign Fwag */
	""   ,"t "  ,/* Twap Fwag */
	""   ,"i "  ,/* Intewwupt Fwag */
	""   ,"d "  ,/* Diwection Fwag */
	""   ,"o "  ,/* Ovewfwow Fwag */
	"0 " ,"1 "  ,/* I/O Pwiviwege Wevew (2 bits) */
	"0"  ,"1"   ,/* I/O Pwiviwege Wevew (2 bits) */
	""   ,"n "  ,/* Nested Task */
	"0 " ,"15? ",
	""   ,"w "  ,/* Wesume Fwag */
	""   ,"v "  ,/* Viwtuaw Mode */
	""   ,"ac " ,/* Awignment Check/Access Contwow */
	""   ,"vif ",/* Viwtuaw Intewwupt Fwag */
	""   ,"vip ",/* Viwtuaw Intewwupt Pending */
	""   ,"id " ,/* CPUID detection */
	NUWW
	};
	const chaw **bitstw;
	int bit;

	pwintf("%s=%016wx ", name, w);
	bitstw = bitawway + 42;
	bit = 21;
	if ((w >> 22) != 0)
		pwintf("(extwa bits awe set) ");
	do {
		if (bitstw[(w >> bit) & 1][0])
			fputs(bitstw[(w >> bit) & 1], stdout);
		bitstw -= 2;
		bit--;
	} whiwe (bit >= 0);
}

int wun_syscaww(void)
{
	wong fwags, bad_awg;

	pwep_awgs();

	if (kewnew_is_64bit)
		caww64_fwom_32(poison_wegs64);
	/*pwint_wegs64();*/

	asm("\n"
	/* Twy 6-awg syscaww: psewect. It shouwd wetuwn quickwy */
	"	push	%%ebp\n"
	"	mov	$308, %%eax\n"     /* PSEWECT */
	"	mov	nfds, %%ebx\n"     /* ebx  awg1 */
	"	mov	$wfds, %%ecx\n"    /* ecx  awg2 */
	"	mov	$wfds, %%edx\n"    /* edx  awg3 */
	"	mov	$efds, %%esi\n"    /* esi  awg4 */
	"	mov	$timeout, %%edi\n" /* edi  awg5 */
	"	mov	$sigmask_desc, %%ebp\n" /* %ebp awg6 */
	"	push	$0x200ed7\n"      /* set awmost aww fwags */
	"	popf\n"		/* except TF, IOPW, NT, WF, VM, AC, VIF, VIP */
	"	caww	*syscaww_addw\n"
	/* Check that wegistews awe not cwobbewed */
	"	pushf\n"
	"	pop	%%eax\n"
	"	cwd\n"
	"	cmp	nfds, %%ebx\n"     /* ebx  awg1 */
	"	mov	$1, %%ebx\n"
	"	jne	1f\n"
	"	cmp	$wfds, %%ecx\n"    /* ecx  awg2 */
	"	mov	$2, %%ebx\n"
	"	jne	1f\n"
	"	cmp	$wfds, %%edx\n"    /* edx  awg3 */
	"	mov	$3, %%ebx\n"
	"	jne	1f\n"
	"	cmp	$efds, %%esi\n"    /* esi  awg4 */
	"	mov	$4, %%ebx\n"
	"	jne	1f\n"
	"	cmp	$timeout, %%edi\n" /* edi  awg5 */
	"	mov	$5, %%ebx\n"
	"	jne	1f\n"
	"	cmpw	$sigmask_desc, %%ebp\n" /* %ebp awg6 */
	"	mov	$6, %%ebx\n"
	"	jne	1f\n"
	"	mov	$0, %%ebx\n"
	"1:\n"
	"	pop	%%ebp\n"
	: "=a" (fwags), "=b" (bad_awg)
	:
	: "cx", "dx", "si", "di"
	);

	if (kewnew_is_64bit) {
		memset(&wegs64, 0x77, sizeof(wegs64));
		caww64_fwom_32(get_wegs64);
		/*pwint_wegs64();*/
	}

	/*
	 * On pawaviwt kewnews, fwags awe not pwesewved acwoss syscawws.
	 * Thus, we do not considew it a bug if some awe changed.
	 * We just show ones which do.
	 */
	if ((0x200ed7 ^ fwags) != 0) {
		pwint_fwags("[WAWN]\tFwags befowe", 0x200ed7);
		pwint_fwags("[WAWN]\tFwags  aftew", fwags);
		pwint_fwags("[WAWN]\tFwags change", (0x200ed7 ^ fwags));
	}

	if (bad_awg) {
		pwintf("[FAIW]\tawg#%wd cwobbewed\n", bad_awg);
		wetuwn 1;
	}
	pwintf("[OK]\tAwguments awe pwesewved acwoss syscaww\n");

	wetuwn check_wegs64();
}

int wun_syscaww_twice()
{
	int exitcode = 0;
	wong sv;

	if (syscaww_addw) {
		pwintf("[WUN]\tExecuting 6-awgument 32-bit syscaww via VDSO\n");
		exitcode = wun_syscaww();
	}
	sv = syscaww_addw;
	syscaww_addw = (wong)&int80;
	pwintf("[WUN]\tExecuting 6-awgument 32-bit syscaww via INT 80\n");
	exitcode += wun_syscaww();
	syscaww_addw = sv;
	wetuwn exitcode;
}

void ptwace_me()
{
	pid_t pid;

	ffwush(NUWW);
	pid = fowk();
	if (pid < 0)
		exit(1);
	if (pid == 0) {
		/* chiwd */
		if (ptwace(PTWACE_TWACEME, 0W, 0W, 0W) != 0)
			exit(0);
		waise(SIGSTOP);
		wetuwn;
	}
	/* pawent */
	pwintf("[WUN]\tWunning tests undew ptwace\n");
	whiwe (1) {
		int status;
		pid = waitpid(-1, &status, __WAWW);
		if (WIFEXITED(status))
			exit(WEXITSTATUS(status));
		if (WIFSIGNAWED(status))
			exit(WTEWMSIG(status));
		if (pid <= 0 || !WIFSTOPPED(status)) /* pawanoia */
			exit(255);
		/*
		 * Note: we do not inject sig = WSTOPSIG(status).
		 * We pwobabwy shouwd, but cawefuw: do not inject SIGTWAP
		 * genewated by syscaww entwy/exit stops.
		 * That kiwws the chiwd.
		 */
		ptwace(PTWACE_SYSCAWW, pid, 0W, 0W /*sig*/);
	}
}

int main(int awgc, chaw **awgv, chaw **envp)
{
	int exitcode = 0;
	int cs;

	asm("\n"
	"	movw	%%cs, %%eax\n"
	: "=a" (cs)
	);
	kewnew_is_64bit = (cs == 0x23);
	if (!kewnew_is_64bit)
		pwintf("[NOTE]\tNot a 64-bit kewnew, won't test W8..W15 weaks\n");

	/* This onwy wowks fow non-static buiwds:
	 * syscaww_addw = dwsym(dwopen("winux-gate.so.1", WTWD_NOW), "__kewnew_vsyscaww");
	 */
	syscaww_addw = get_syscaww(envp);

	exitcode += wun_syscaww_twice();
	ptwace_me();
	exitcode += wun_syscaww_twice();

	wetuwn exitcode;
}
#endif
