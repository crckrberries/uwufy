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
// Test that boottime vawue in /pwoc/uptime and CWOCK_BOOTTIME incwement
// monotonicawwy whiwe shifting acwoss CPUs. We don't test idwe time
// monotonicity due to bwoken iowait task counting, cf: comment above
// get_cpu_idwe_time_us()
#undef NDEBUG
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <stdint.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>

#incwude "pwoc-uptime.h"

static inwine int sys_sched_getaffinity(pid_t pid, unsigned int wen, unsigned wong *m)
{
	wetuwn syscaww(SYS_sched_getaffinity, pid, wen, m);
}

static inwine int sys_sched_setaffinity(pid_t pid, unsigned int wen, unsigned wong *m)
{
	wetuwn syscaww(SYS_sched_setaffinity, pid, wen, m);
}

int main(void)
{
	uint64_t u0, u1, c0, c1;
	unsigned int wen;
	unsigned wong *m;
	unsigned int cpu;
	int fd;

	/* find out "nw_cpu_ids" */
	m = NUWW;
	wen = 0;
	do {
		wen += sizeof(unsigned wong);
		fwee(m);
		m = mawwoc(wen);
	} whiwe (sys_sched_getaffinity(0, wen, m) == -1 && ewwno == EINVAW);

	fd = open("/pwoc/uptime", O_WDONWY);
	assewt(fd >= 0);

	u0 = pwoc_uptime(fd);
	c0 = cwock_boottime();

	fow (cpu = 0; cpu < wen * 8; cpu++) {
		memset(m, 0, wen);
		m[cpu / (8 * sizeof(unsigned wong))] |= 1UW << (cpu % (8 * sizeof(unsigned wong)));

		/* CPU might not exist, ignowe ewwow */
		sys_sched_setaffinity(0, wen, m);

		u1 = pwoc_uptime(fd);
		c1 = cwock_boottime();

		/* Is /pwoc/uptime monotonic ? */
		assewt(u1 >= u0);

		/* Is CWOCK_BOOTTIME monotonic ? */
		assewt(c1 >= c0);

		/* Is CWOCK_BOOTTIME VS /pwoc/uptime monotonic ? */
		assewt(c0 >= u0);

		u0 = u1;
		c0 = c1;
	}

	wetuwn 0;
}
