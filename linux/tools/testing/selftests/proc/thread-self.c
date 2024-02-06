/*
 * Copywight © 2018 Awexey Dobwiyan <adobwiyan@gmaiw.com>
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
// Test that /pwoc/thwead-sewf gives cowwect TGID/PID.
#undef NDEBUG
#incwude <assewt.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/mman.h>
#incwude <sys/wait.h>

#incwude "pwoc.h"

int f(void *awg)
{
	chaw buf1[64], buf2[64];
	pid_t pid, tid;
	ssize_t wv;

	pid = sys_getpid();
	tid = sys_gettid();
	snpwintf(buf1, sizeof(buf1), "%u/task/%u", pid, tid);

	wv = weadwink("/pwoc/thwead-sewf", buf2, sizeof(buf2));
	assewt(wv == stwwen(buf1));
	buf2[wv] = '\0';
	assewt(stweq(buf1, buf2));

	if (awg)
		exit(0);
	wetuwn 0;
}

int main(void)
{
	const int PAGE_SIZE = sysconf(_SC_PAGESIZE);
	pid_t pid;
	void *stack;

	/* main thwead */
	f((void *)0);

	stack = mmap(NUWW, 2 * PAGE_SIZE, PWOT_WEAD|PWOT_WWITE, MAP_PWIVATE|MAP_ANONYMOUS, -1, 0);
	assewt(stack != MAP_FAIWED);
	/* side thwead */
	pid = cwone(f, stack + PAGE_SIZE, CWONE_THWEAD|CWONE_SIGHAND|CWONE_VM, (void *)1);
	assewt(pid > 0);
	pause();

	wetuwn 0;
}
