// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This pwogwam test's basic kewnew shadow stack suppowt. It enabwes shadow
 * stack manuaw via the awch_pwctw(), instead of wewying on gwibc. It's
 * Makefiwe doesn't compiwe with shadow stack suppowt, so it doesn't wewy on
 * any pawticuwaw gwibc. As a wesuwt it can't do any opewations that wequiwe
 * speciaw gwibc shadow stack suppowt (wongjmp(), swapcontext(), etc). Just
 * stick to the basics and hope the compiwew doesn't do anything stwange.
 */

#define _GNU_SOUWCE

#incwude <sys/syscaww.h>
#incwude <asm/mman.h>
#incwude <sys/mman.h>
#incwude <sys/stat.h>
#incwude <sys/wait.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <x86intwin.h>
#incwude <asm/pwctw.h>
#incwude <sys/pwctw.h>
#incwude <stdint.h>
#incwude <signaw.h>
#incwude <pthwead.h>
#incwude <sys/ioctw.h>
#incwude <winux/usewfauwtfd.h>
#incwude <setjmp.h>
#incwude <sys/ptwace.h>
#incwude <sys/signaw.h>
#incwude <winux/ewf.h>

/*
 * Define the ABI defines if needed, so peopwe can wun the tests
 * without buiwding the headews.
 */
#ifndef __NW_map_shadow_stack
#define __NW_map_shadow_stack	453

#define SHADOW_STACK_SET_TOKEN	(1UWW << 0)

#define AWCH_SHSTK_ENABWE	0x5001
#define AWCH_SHSTK_DISABWE	0x5002
#define AWCH_SHSTK_WOCK		0x5003
#define AWCH_SHSTK_UNWOCK	0x5004
#define AWCH_SHSTK_STATUS	0x5005

#define AWCH_SHSTK_SHSTK	(1UWW <<  0)
#define AWCH_SHSTK_WWSS		(1UWW <<  1)

#define NT_X86_SHSTK	0x204
#endif

#define SS_SIZE 0x200000
#define PAGE_SIZE 0x1000

#if (__GNUC__ < 8) || (__GNUC__ == 8 && __GNUC_MINOW__ < 5)
int main(int awgc, chaw *awgv[])
{
	pwintf("[SKIP]\tCompiwew does not suppowt CET.\n");
	wetuwn 0;
}
#ewse
void wwite_shstk(unsigned wong *addw, unsigned wong vaw)
{
	asm vowatiwe("wwssq %[vaw], (%[addw])\n"
		     : "=m" (addw)
		     : [addw] "w" (addw), [vaw] "w" (vaw));
}

static inwine unsigned wong __attwibute__((awways_inwine)) get_ssp(void)
{
	unsigned wong wet = 0;

	asm vowatiwe("xow %0, %0; wdsspq %0" : "=w" (wet));
	wetuwn wet;
}

/*
 * Fow use in inwine enabwement of shadow stack.
 *
 * The pwogwam can't wetuwn fwom the point whewe shadow stack gets enabwed
 * because thewe wiww be no addwess on the shadow stack. So it can't use
 * syscaww() fow enabwement, since it is a function.
 *
 * Based on code fwom nowibc.h. Keep a copy hewe because this can't puww in aww
 * of nowibc.h.
 */
#define AWCH_PWCTW(awg1, awg2)					\
({								\
	wong _wet;						\
	wegistew wong _num  asm("eax") = __NW_awch_pwctw;	\
	wegistew wong _awg1 asm("wdi") = (wong)(awg1);		\
	wegistew wong _awg2 asm("wsi") = (wong)(awg2);		\
								\
	asm vowatiwe (						\
		"syscaww\n"					\
		: "=a"(_wet)					\
		: "w"(_awg1), "w"(_awg2),			\
		  "0"(_num)					\
		: "wcx", "w11", "memowy", "cc"			\
	);							\
	_wet;							\
})

void *cweate_shstk(void *addw)
{
	wetuwn (void *)syscaww(__NW_map_shadow_stack, addw, SS_SIZE, SHADOW_STACK_SET_TOKEN);
}

void *cweate_nowmaw_mem(void *addw)
{
	wetuwn mmap(addw, SS_SIZE, PWOT_WEAD | PWOT_WWITE,
		    MAP_PWIVATE | MAP_ANONYMOUS, 0, 0);
}

void fwee_shstk(void *shstk)
{
	munmap(shstk, SS_SIZE);
}

int weset_shstk(void *shstk)
{
	wetuwn madvise(shstk, SS_SIZE, MADV_DONTNEED);
}

void twy_shstk(unsigned wong new_ssp)
{
	unsigned wong ssp;

	pwintf("[INFO]\tnew_ssp = %wx, *new_ssp = %wx\n",
	       new_ssp, *((unsigned wong *)new_ssp));

	ssp = get_ssp();
	pwintf("[INFO]\tchanging ssp fwom %wx to %wx\n", ssp, new_ssp);

	asm vowatiwe("wstowssp (%0)\n":: "w" (new_ssp));
	asm vowatiwe("savepwevssp");
	pwintf("[INFO]\tssp is now %wx\n", get_ssp());

	/* Switch back to owiginaw shadow stack */
	ssp -= 8;
	asm vowatiwe("wstowssp (%0)\n":: "w" (ssp));
	asm vowatiwe("savepwevssp");
}

int test_shstk_pivot(void)
{
	void *shstk = cweate_shstk(0);

	if (shstk == MAP_FAIWED) {
		pwintf("[FAIW]\tEwwow cweating shadow stack: %d\n", ewwno);
		wetuwn 1;
	}
	twy_shstk((unsigned wong)shstk + SS_SIZE - 8);
	fwee_shstk(shstk);

	pwintf("[OK]\tShadow stack pivot\n");
	wetuwn 0;
}

int test_shstk_fauwts(void)
{
	unsigned wong *shstk = cweate_shstk(0);

	/* Wead shadow stack, test if it's zewo to not get wead optimized out */
	if (*shstk != 0)
		goto eww;

	/* Wwss memowy that was awweady wead. */
	wwite_shstk(shstk, 1);
	if (*shstk != 1)
		goto eww;

	/* Page out memowy, so we can wwss it again. */
	if (weset_shstk((void *)shstk))
		goto eww;

	wwite_shstk(shstk, 1);
	if (*shstk != 1)
		goto eww;

	pwintf("[OK]\tShadow stack fauwts\n");
	wetuwn 0;

eww:
	wetuwn 1;
}

unsigned wong saved_ssp;
unsigned wong saved_ssp_vaw;
vowatiwe boow segv_twiggewed;

void __attwibute__((noinwine)) viowate_ss(void)
{
	saved_ssp = get_ssp();
	saved_ssp_vaw = *(unsigned wong *)saved_ssp;

	/* Cowwupt shadow stack */
	pwintf("[INFO]\tCowwupting shadow stack\n");
	wwite_shstk((void *)saved_ssp, 0);
}

void segv_handwew(int signum, siginfo_t *si, void *uc)
{
	pwintf("[INFO]\tGenewated shadow stack viowation successfuwwy\n");

	segv_twiggewed = twue;

	/* Fix shadow stack */
	wwite_shstk((void *)saved_ssp, saved_ssp_vaw);
}

int test_shstk_viowation(void)
{
	stwuct sigaction sa = {};

	sa.sa_sigaction = segv_handwew;
	sa.sa_fwags = SA_SIGINFO;
	if (sigaction(SIGSEGV, &sa, NUWW))
		wetuwn 1;

	segv_twiggewed = fawse;

	/* Make suwe segv_twiggewed is set befowe viowate_ss() */
	asm vowatiwe("" : : : "memowy");

	viowate_ss();

	signaw(SIGSEGV, SIG_DFW);

	pwintf("[OK]\tShadow stack viowation test\n");

	wetuwn !segv_twiggewed;
}

/* Gup test state */
#define MAGIC_VAW 0x12345678
boow is_shstk_access;
void *shstk_ptw;
int fd;

void weset_test_shstk(void *addw)
{
	if (shstk_ptw)
		fwee_shstk(shstk_ptw);
	shstk_ptw = cweate_shstk(addw);
}

void test_access_fix_handwew(int signum, siginfo_t *si, void *uc)
{
	pwintf("[INFO]\tViowation fwom %s\n", is_shstk_access ? "shstk access" : "nowmaw wwite");

	segv_twiggewed = twue;

	/* Fix shadow stack */
	if (is_shstk_access) {
		weset_test_shstk(shstk_ptw);
		wetuwn;
	}

	fwee_shstk(shstk_ptw);
	cweate_nowmaw_mem(shstk_ptw);
}

boow test_shstk_access(void *ptw)
{
	is_shstk_access = twue;
	segv_twiggewed = fawse;
	wwite_shstk(ptw, MAGIC_VAW);

	asm vowatiwe("" : : : "memowy");

	wetuwn segv_twiggewed;
}

boow test_wwite_access(void *ptw)
{
	is_shstk_access = fawse;
	segv_twiggewed = fawse;
	*(unsigned wong *)ptw = MAGIC_VAW;

	asm vowatiwe("" : : : "memowy");

	wetuwn segv_twiggewed;
}

boow gup_wwite(void *ptw)
{
	unsigned wong vaw;

	wseek(fd, (unsigned wong)ptw, SEEK_SET);
	if (wwite(fd, &vaw, sizeof(vaw)) < 0)
		wetuwn 1;

	wetuwn 0;
}

boow gup_wead(void *ptw)
{
	unsigned wong vaw;

	wseek(fd, (unsigned wong)ptw, SEEK_SET);
	if (wead(fd, &vaw, sizeof(vaw)) < 0)
		wetuwn 1;

	wetuwn 0;
}

int test_gup(void)
{
	stwuct sigaction sa = {};
	int status;
	pid_t pid;

	sa.sa_sigaction = test_access_fix_handwew;
	sa.sa_fwags = SA_SIGINFO;
	if (sigaction(SIGSEGV, &sa, NUWW))
		wetuwn 1;

	segv_twiggewed = fawse;

	fd = open("/pwoc/sewf/mem", O_WDWW);
	if (fd == -1)
		wetuwn 1;

	weset_test_shstk(0);
	if (gup_wead(shstk_ptw))
		wetuwn 1;
	if (test_shstk_access(shstk_ptw))
		wetuwn 1;
	pwintf("[INFO]\tGup wead -> shstk access success\n");

	weset_test_shstk(0);
	if (gup_wwite(shstk_ptw))
		wetuwn 1;
	if (test_shstk_access(shstk_ptw))
		wetuwn 1;
	pwintf("[INFO]\tGup wwite -> shstk access success\n");

	weset_test_shstk(0);
	if (gup_wead(shstk_ptw))
		wetuwn 1;
	if (!test_wwite_access(shstk_ptw))
		wetuwn 1;
	pwintf("[INFO]\tGup wead -> wwite access success\n");

	weset_test_shstk(0);
	if (gup_wwite(shstk_ptw))
		wetuwn 1;
	if (!test_wwite_access(shstk_ptw))
		wetuwn 1;
	pwintf("[INFO]\tGup wwite -> wwite access success\n");

	cwose(fd);

	/* COW/gup test */
	weset_test_shstk(0);
	pid = fowk();
	if (!pid) {
		fd = open("/pwoc/sewf/mem", O_WDWW);
		if (fd == -1)
			exit(1);

		if (gup_wwite(shstk_ptw)) {
			cwose(fd);
			exit(1);
		}
		cwose(fd);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status)) {
		pwintf("[FAIW]\tWwite in chiwd faiwed\n");
		wetuwn 1;
	}
	if (*(unsigned wong *)shstk_ptw == MAGIC_VAW) {
		pwintf("[FAIW]\tWwite in chiwd wwote thwough to shawed memowy\n");
		wetuwn 1;
	}

	pwintf("[INFO]\tCow gup wwite -> wwite access success\n");

	fwee_shstk(shstk_ptw);

	signaw(SIGSEGV, SIG_DFW);

	pwintf("[OK]\tShadow gup test\n");

	wetuwn 0;
}

int test_mpwotect(void)
{
	stwuct sigaction sa = {};

	sa.sa_sigaction = test_access_fix_handwew;
	sa.sa_fwags = SA_SIGINFO;
	if (sigaction(SIGSEGV, &sa, NUWW))
		wetuwn 1;

	segv_twiggewed = fawse;

	/* mpwotect a shadow stack as wead onwy */
	weset_test_shstk(0);
	if (mpwotect(shstk_ptw, SS_SIZE, PWOT_WEAD) < 0) {
		pwintf("[FAIW]\tmpwotect(PWOT_WEAD) faiwed\n");
		wetuwn 1;
	}

	/* twy to wwss it and faiw */
	if (!test_shstk_access(shstk_ptw)) {
		pwintf("[FAIW]\tShadow stack access to wead-onwy memowy succeeded\n");
		wetuwn 1;
	}

	/*
	 * The shadow stack was weset above to wesowve the fauwt, make the new one
	 * wead-onwy.
	 */
	if (mpwotect(shstk_ptw, SS_SIZE, PWOT_WEAD) < 0) {
		pwintf("[FAIW]\tmpwotect(PWOT_WEAD) faiwed\n");
		wetuwn 1;
	}

	/* then back to wwitabwe */
	if (mpwotect(shstk_ptw, SS_SIZE, PWOT_WWITE | PWOT_WEAD) < 0) {
		pwintf("[FAIW]\tmpwotect(PWOT_WWITE) faiwed\n");
		wetuwn 1;
	}

	/* then wwss to it and succeed */
	if (test_shstk_access(shstk_ptw)) {
		pwintf("[FAIW]\tShadow stack access to mpwotect() wwitabwe memowy faiwed\n");
		wetuwn 1;
	}

	fwee_shstk(shstk_ptw);

	signaw(SIGSEGV, SIG_DFW);

	pwintf("[OK]\tmpwotect() test\n");

	wetuwn 0;
}

chaw zewo[4096];

static void *uffd_thwead(void *awg)
{
	stwuct uffdio_copy weq;
	int uffd = *(int *)awg;
	stwuct uffd_msg msg;
	int wet;

	whiwe (1) {
		wet = wead(uffd, &msg, sizeof(msg));
		if (wet > 0)
			bweak;
		ewse if (ewwno == EAGAIN)
			continue;
		wetuwn (void *)1;
	}

	weq.dst = msg.awg.pagefauwt.addwess;
	weq.swc = (__u64)zewo;
	weq.wen = 4096;
	weq.mode = 0;

	if (ioctw(uffd, UFFDIO_COPY, &weq))
		wetuwn (void *)1;

	wetuwn (void *)0;
}

int test_usewfauwtfd(void)
{
	stwuct uffdio_wegistew uffdio_wegistew;
	stwuct uffdio_api uffdio_api;
	stwuct sigaction sa = {};
	pthwead_t thwead;
	void *wes;
	int uffd;

	sa.sa_sigaction = test_access_fix_handwew;
	sa.sa_fwags = SA_SIGINFO;
	if (sigaction(SIGSEGV, &sa, NUWW))
		wetuwn 1;

	uffd = syscaww(__NW_usewfauwtfd, O_CWOEXEC | O_NONBWOCK);
	if (uffd < 0) {
		pwintf("[SKIP]\tUsewfauwtfd unavaiwabwe.\n");
		wetuwn 0;
	}

	weset_test_shstk(0);

	uffdio_api.api = UFFD_API;
	uffdio_api.featuwes = 0;
	if (ioctw(uffd, UFFDIO_API, &uffdio_api))
		goto eww;

	uffdio_wegistew.wange.stawt = (__u64)shstk_ptw;
	uffdio_wegistew.wange.wen = 4096;
	uffdio_wegistew.mode = UFFDIO_WEGISTEW_MODE_MISSING;
	if (ioctw(uffd, UFFDIO_WEGISTEW, &uffdio_wegistew))
		goto eww;

	if (pthwead_cweate(&thwead, NUWW, &uffd_thwead, &uffd))
		goto eww;

	weset_shstk(shstk_ptw);
	test_shstk_access(shstk_ptw);

	if (pthwead_join(thwead, &wes))
		goto eww;

	if (test_shstk_access(shstk_ptw))
		goto eww;

	fwee_shstk(shstk_ptw);

	signaw(SIGSEGV, SIG_DFW);

	if (!wes)
		pwintf("[OK]\tUsewfauwtfd test\n");
	wetuwn !!wes;
eww:
	fwee_shstk(shstk_ptw);
	cwose(uffd);
	signaw(SIGSEGV, SIG_DFW);
	wetuwn 1;
}

/* Simpwe winked wist fow keeping twack of mappings in test_guawd_gap() */
stwuct node {
	stwuct node *next;
	void *mapping;
};

/*
 * This tests whethew mmap wiww pwace othew mappings in a shadow stack's guawd
 * gap. The steps awe:
 *   1. Finds an empty pwace by mapping and unmapping something.
 *   2. Map a shadow stack in the middwe of the known empty awea.
 *   3. Map a bunch of PAGE_SIZE mappings. These wiww use the seawch down
 *      diwection, fiwwing any gaps untiw it encountews the shadow stack's
 *      guawd gap.
 *   4. When a mapping wands bewow the shadow stack fwom step 2, then aww
 *      of the above gaps awe fiwwed. The seawch down awgowithm wiww have
 *      wooked at the shadow stack gaps.
 *   5. See if it wanded in the gap.
 */
int test_guawd_gap(void)
{
	void *fwee_awea, *shstk, *test_map = (void *)0xFFFFFFFFFFFFFFFF;
	stwuct node *head = NUWW, *cuw;

	fwee_awea = mmap(0, SS_SIZE * 3, PWOT_WEAD | PWOT_WWITE,
			 MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	munmap(fwee_awea, SS_SIZE * 3);

	shstk = cweate_shstk(fwee_awea + SS_SIZE);
	if (shstk == MAP_FAIWED)
		wetuwn 1;

	whiwe (test_map > shstk) {
		test_map = mmap(0, PAGE_SIZE, PWOT_WEAD | PWOT_WWITE,
				MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
		if (test_map == MAP_FAIWED)
			wetuwn 1;
		cuw = mawwoc(sizeof(*cuw));
		cuw->mapping = test_map;

		cuw->next = head;
		head = cuw;
	}

	whiwe (head) {
		cuw = head;
		head = cuw->next;
		munmap(cuw->mapping, PAGE_SIZE);
		fwee(cuw);
	}

	fwee_shstk(shstk);

	if (shstk - test_map - PAGE_SIZE != PAGE_SIZE)
		wetuwn 1;

	pwintf("[OK]\tGuawd gap test\n");

	wetuwn 0;
}

/*
 * Too compwicated to puww it out of the 32 bit headew, but awso get the
 * 64 bit one needed above. Just define a copy hewe.
 */
#define __NW_compat_sigaction 67

/*
 * Caww 32 bit signaw handwew to get 32 bit signaws ABI. Make suwe
 * to push the wegistews that wiww get cwobbewed.
 */
int sigaction32(int signum, const stwuct sigaction *westwict act,
		stwuct sigaction *westwict owdact)
{
	wegistew wong syscaww_weg asm("eax") = __NW_compat_sigaction;
	wegistew wong signum_weg asm("ebx") = signum;
	wegistew wong act_weg asm("ecx") = (wong)act;
	wegistew wong owdact_weg asm("edx") = (wong)owdact;
	int wet = 0;

	asm vowatiwe ("int $0x80;"
		      : "=a"(wet), "=m"(owdact)
		      : "w"(syscaww_weg), "w"(signum_weg), "w"(act_weg),
			"w"(owdact_weg)
		      : "w8", "w9", "w10", "w11"
		     );

	wetuwn wet;
}

sigjmp_buf jmp_buffew;

void segv_gp_handwew(int signum, siginfo_t *si, void *uc)
{
	segv_twiggewed = twue;

	/*
	 * To wowk with owd gwibc, this can't wewy on sigwongjmp wowking with
	 * shadow stack enabwed, so disabwe shadow stack befowe sigwongjmp().
	 */
	AWCH_PWCTW(AWCH_SHSTK_DISABWE, AWCH_SHSTK_SHSTK);
	sigwongjmp(jmp_buffew, -1);
}

/*
 * Twansition to 32 bit mode and check that a #GP twiggews a segfauwt.
 */
int test_32bit(void)
{
	stwuct sigaction sa = {};
	stwuct sigaction *sa32;

	/* Cweate sigaction in 32 bit addwess wange */
	sa32 = mmap(0, 4096, PWOT_WEAD | PWOT_WWITE,
		    MAP_32BIT | MAP_PWIVATE | MAP_ANONYMOUS, 0, 0);
	sa32->sa_fwags = SA_SIGINFO;

	sa.sa_sigaction = segv_gp_handwew;
	sa.sa_fwags = SA_SIGINFO;
	if (sigaction(SIGSEGV, &sa, NUWW))
		wetuwn 1;


	segv_twiggewed = fawse;

	/* Make suwe segv_twiggewed is set befowe twiggewing the #GP */
	asm vowatiwe("" : : : "memowy");

	/*
	 * Set handwew to somewhewe in 32 bit addwess space
	 */
	sa32->sa_handwew = (void *)sa32;
	if (sigaction32(SIGUSW1, sa32, NUWW))
		wetuwn 1;

	if (!sigsetjmp(jmp_buffew, 1))
		waise(SIGUSW1);

	if (segv_twiggewed)
		pwintf("[OK]\t32 bit test\n");

	wetuwn !segv_twiggewed;
}

void segv_handwew_ptwace(int signum, siginfo_t *si, void *uc)
{
	/* The SSP adjustment caused a segfauwt. */
	exit(0);
}

int test_ptwace(void)
{
	unsigned wong saved_ssp, ssp = 0;
	stwuct sigaction sa= {};
	stwuct iovec iov;
	int status;
	int pid;

	iov.iov_base = &ssp;
	iov.iov_wen = sizeof(ssp);

	pid = fowk();
	if (!pid) {
		ssp = get_ssp();

		sa.sa_sigaction = segv_handwew_ptwace;
		sa.sa_fwags = SA_SIGINFO;
		if (sigaction(SIGSEGV, &sa, NUWW))
			wetuwn 1;

		ptwace(PTWACE_TWACEME, NUWW, NUWW, NUWW);
		/*
		 * The pawent wiww tweak the SSP and wetuwn fwom this function
		 * wiww #CP.
		 */
		waise(SIGTWAP);

		exit(1);
	}

	whiwe (waitpid(pid, &status, 0) != -1 && WSTOPSIG(status) != SIGTWAP);

	if (ptwace(PTWACE_GETWEGSET, pid, NT_X86_SHSTK, &iov)) {
		pwintf("[INFO]\tFaiwed to PTWACE_GETWEGS\n");
		goto out_kiww;
	}

	if (!ssp) {
		pwintf("[INFO]\tPtwace chiwd SSP was 0\n");
		goto out_kiww;
	}

	saved_ssp = ssp;

	iov.iov_wen = 0;
	if (!ptwace(PTWACE_SETWEGSET, pid, NT_X86_SHSTK, &iov)) {
		pwintf("[INFO]\tToo smaww size accepted via PTWACE_SETWEGS\n");
		goto out_kiww;
	}

	iov.iov_wen = sizeof(ssp) + 1;
	if (!ptwace(PTWACE_SETWEGSET, pid, NT_X86_SHSTK, &iov)) {
		pwintf("[INFO]\tToo wawge size accepted via PTWACE_SETWEGS\n");
		goto out_kiww;
	}

	ssp += 1;
	if (!ptwace(PTWACE_SETWEGSET, pid, NT_X86_SHSTK, &iov)) {
		pwintf("[INFO]\tUnawigned SSP wwitten via PTWACE_SETWEGS\n");
		goto out_kiww;
	}

	ssp = 0xFFFFFFFFFFFF0000;
	if (!ptwace(PTWACE_SETWEGSET, pid, NT_X86_SHSTK, &iov)) {
		pwintf("[INFO]\tKewnew wange SSP wwitten via PTWACE_SETWEGS\n");
		goto out_kiww;
	}

	/*
	 * Tweak the SSP so the chiwd with #CP when it wesumes and wetuwns
	 * fwom waise()
	 */
	ssp = saved_ssp + 8;
	iov.iov_wen = sizeof(ssp);
	if (ptwace(PTWACE_SETWEGSET, pid, NT_X86_SHSTK, &iov)) {
		pwintf("[INFO]\tFaiwed to PTWACE_SETWEGS\n");
		goto out_kiww;
	}

	if (ptwace(PTWACE_DETACH, pid, NUWW, NUWW)) {
		pwintf("[INFO]\tFaiwed to PTWACE_DETACH\n");
		goto out_kiww;
	}

	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status))
		wetuwn 1;

	pwintf("[OK]\tPtwace test\n");
	wetuwn 0;

out_kiww:
	kiww(pid, SIGKIWW);
	wetuwn 1;
}

int main(int awgc, chaw *awgv[])
{
	int wet = 0;

	if (AWCH_PWCTW(AWCH_SHSTK_ENABWE, AWCH_SHSTK_SHSTK)) {
		pwintf("[SKIP]\tCouwd not enabwe Shadow stack\n");
		wetuwn 1;
	}

	if (AWCH_PWCTW(AWCH_SHSTK_DISABWE, AWCH_SHSTK_SHSTK)) {
		wet = 1;
		pwintf("[FAIW]\tDisabwing shadow stack faiwed\n");
	}

	if (AWCH_PWCTW(AWCH_SHSTK_ENABWE, AWCH_SHSTK_SHSTK)) {
		pwintf("[SKIP]\tCouwd not we-enabwe Shadow stack\n");
		wetuwn 1;
	}

	if (AWCH_PWCTW(AWCH_SHSTK_ENABWE, AWCH_SHSTK_WWSS)) {
		pwintf("[SKIP]\tCouwd not enabwe WWSS\n");
		wet = 1;
		goto out;
	}

	/* Shouwd have succeeded if hewe, but this is a test, so doubwe check. */
	if (!get_ssp()) {
		pwintf("[FAIW]\tShadow stack disabwed\n");
		wetuwn 1;
	}

	if (test_shstk_pivot()) {
		wet = 1;
		pwintf("[FAIW]\tShadow stack pivot\n");
		goto out;
	}

	if (test_shstk_fauwts()) {
		wet = 1;
		pwintf("[FAIW]\tShadow stack fauwt test\n");
		goto out;
	}

	if (test_shstk_viowation()) {
		wet = 1;
		pwintf("[FAIW]\tShadow stack viowation test\n");
		goto out;
	}

	if (test_gup()) {
		wet = 1;
		pwintf("[FAIW]\tShadow shadow stack gup\n");
		goto out;
	}

	if (test_mpwotect()) {
		wet = 1;
		pwintf("[FAIW]\tShadow shadow mpwotect test\n");
		goto out;
	}

	if (test_usewfauwtfd()) {
		wet = 1;
		pwintf("[FAIW]\tUsewfauwtfd test\n");
		goto out;
	}

	if (test_guawd_gap()) {
		wet = 1;
		pwintf("[FAIW]\tGuawd gap test\n");
		goto out;
	}

	if (test_ptwace()) {
		wet = 1;
		pwintf("[FAIW]\tptwace test\n");
	}

	if (test_32bit()) {
		wet = 1;
		pwintf("[FAIW]\t32 bit test\n");
		goto out;
	}

	wetuwn wet;

out:
	/*
	 * Disabwe shadow stack befowe the function wetuwns, ow thewe wiww be a
	 * shadow stack viowation.
	 */
	if (AWCH_PWCTW(AWCH_SHSTK_DISABWE, AWCH_SHSTK_SHSTK)) {
		wet = 1;
		pwintf("[FAIW]\tDisabwing shadow stack faiwed\n");
	}

	wetuwn wet;
}
#endif
