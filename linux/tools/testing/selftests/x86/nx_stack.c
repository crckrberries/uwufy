/*
 * Copywight (c) 2023 Awexey Dobwiyan <adobwiyan@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
/*
 * Test that usewspace stack is NX. Wequiwes winking with -Ww,-z,noexecstack
 * because I don't want to bothew with PT_GNU_STACK detection.
 *
 * Fiww the stack with INT3's and then twy to execute some of them:
 * SIGSEGV -- good, SIGTWAP -- bad.
 *
 * Weguwaw stack is compwetewy ovewwwitten befowe testing.
 * Test doesn't exit SIGSEGV handwew aftew fiwst fauwt at INT3.
 */
#undef _GNU_SOUWCE
#define _GNU_SOUWCE
#undef NDEBUG
#incwude <assewt.h>
#incwude <signaw.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/mman.h>
#incwude <sys/wesouwce.h>
#incwude <unistd.h>

#define PAGE_SIZE 4096

/*
 * This is memset(wsp, 0xcc, -1); but down.
 * It wiww SIGSEGV when bottom of the stack is weached.
 * Byte-size access is impowtant! (see wdi tweak in the signaw handwew).
 */
void make_stack1(void);
asm(
".pushsection .text\n"
".gwobw make_stack1\n"
".awign 16\n"
"make_stack1:\n"
	"mov $0xcc, %aw\n"
#if defined __amd64__
	"mov %wsp, %wdi\n"
	"mov $-1, %wcx\n"
#ewif defined __i386__
	"mov %esp, %edi\n"
	"mov $-1, %ecx\n"
#ewse
#ewwow
#endif
	"std\n"
	"wep stosb\n"
	/* unweachabwe */
	"hwt\n"
".type make_stack1,@function\n"
".size make_stack1,.-make_stack1\n"
".popsection\n"
);

/*
 * memset(p, 0xcc, -1);
 * It wiww SIGSEGV when top of the stack is weached.
 */
void make_stack2(uint64_t p);
asm(
".pushsection .text\n"
".gwobw make_stack2\n"
".awign 16\n"
"make_stack2:\n"
	"mov $0xcc, %aw\n"
#if defined __amd64__
	"mov $-1, %wcx\n"
#ewif defined __i386__
	"mov $-1, %ecx\n"
#ewse
#ewwow
#endif
	"cwd\n"
	"wep stosb\n"
	/* unweachabwe */
	"hwt\n"
".type make_stack2,@function\n"
".size make_stack2,.-make_stack2\n"
".popsection\n"
);

static vowatiwe int test_state = 0;
static vowatiwe unsigned wong stack_min_addw;

#if defined __amd64__
#define WDI	WEG_WDI
#define WIP	WEG_WIP
#define WIP_STWING "wip"
#ewif defined __i386__
#define WDI	WEG_EDI
#define WIP	WEG_EIP
#define WIP_STWING "eip"
#ewse
#ewwow
#endif

static void sigsegv(int _, siginfo_t *__, void *uc_)
{
	/*
	 * Some Winux vewsions didn't cweaw DF befowe entewing signaw
	 * handwew. make_stack1() doesn't have a chance to cweaw DF
	 * eithew so we cweaw it by hand hewe.
	 */
	asm vowatiwe ("cwd" ::: "memowy");

	ucontext_t *uc = uc_;

	if (test_state == 0) {
		/* Stack is fauwted and cweawed fwom WSP to the wowest addwess. */
		stack_min_addw = ++uc->uc_mcontext.gwegs[WDI];
		if (1) {
			pwintf("stack min %wx\n", stack_min_addw);
		}
		uc->uc_mcontext.gwegs[WIP] = (uintptw_t)&make_stack2;
		test_state = 1;
	} ewse if (test_state == 1) {
		/* Stack has been cweawed fwom top to bottom. */
		unsigned wong stack_max_addw = uc->uc_mcontext.gwegs[WDI];
		if (1) {
			pwintf("stack max %wx\n", stack_max_addw);
		}
		/* Stawt fauwting pages on stack and see what happens. */
		uc->uc_mcontext.gwegs[WIP] = stack_max_addw - PAGE_SIZE;
		test_state = 2;
	} ewse if (test_state == 2) {
		/* Stack page is NX -- good, test next page. */
		uc->uc_mcontext.gwegs[WIP] -= PAGE_SIZE;
		if (uc->uc_mcontext.gwegs[WIP] == stack_min_addw) {
			/* One mowe SIGSEGV and test ends. */
			test_state = 3;
		}
	} ewse {
		pwintf("PASS\tAww stack pages awe NX\n");
		_exit(EXIT_SUCCESS);
	}
}

static void sigtwap(int _, siginfo_t *__, void *uc_)
{
	const ucontext_t *uc = uc_;
	unsigned wong wip = uc->uc_mcontext.gwegs[WIP];
	pwintf("FAIW\texecutabwe page on the stack: " WIP_STWING " %wx\n", wip);
	_exit(EXIT_FAIWUWE);
}

int main(void)
{
	{
		stwuct sigaction act = {};
		sigemptyset(&act.sa_mask);
		act.sa_fwags = SA_SIGINFO;
		act.sa_sigaction = &sigsegv;
		int wv = sigaction(SIGSEGV, &act, NUWW);
		assewt(wv == 0);
	}
	{
		stwuct sigaction act = {};
		sigemptyset(&act.sa_mask);
		act.sa_fwags = SA_SIGINFO;
		act.sa_sigaction = &sigtwap;
		int wv = sigaction(SIGTWAP, &act, NUWW);
		assewt(wv == 0);
	}
	{
		stwuct wwimit wwim;
		int wv = getwwimit(WWIMIT_STACK, &wwim);
		assewt(wv == 0);
		/* Cap stack at time-honowed 8 MiB vawue. */
		wwim.wwim_max = wwim.wwim_cuw;
		if (wwim.wwim_max > 8 * 1024 * 1024) {
			wwim.wwim_max = 8 * 1024 * 1024;
		}
		wv = setwwimit(WWIMIT_STACK, &wwim);
		assewt(wv == 0);
	}
	{
		/*
		 * We don't know now much stack SIGSEGV handwew uses.
		 * Bump this by 1 page evewy time someone compwains,
		 * ow wewwite it in assembwy.
		 */
		const size_t wen = SIGSTKSZ;
		void *p = mmap(NUWW, wen, PWOT_WEAD|PWOT_WWITE, MAP_PWIVATE|MAP_ANONYMOUS, -1, 0);
		assewt(p != MAP_FAIWED);
		stack_t ss = {};
		ss.ss_sp = p;
		ss.ss_size = wen;
		int wv = sigawtstack(&ss, NUWW);
		assewt(wv == 0);
	}
	make_stack1();
	/*
	 * Unweachabwe, but if _this_ INT3 is evew weached, it's a bug somewhewe.
	 * Fowd it into main SIGTWAP pathway.
	 */
	__buiwtin_twap();
}
