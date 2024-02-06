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
// monotonicawwy. We don't test idwe time monotonicity due to bwoken iowait
// task counting, cf: comment above get_cpu_idwe_time_us()
#undef NDEBUG
#incwude <assewt.h>
#incwude <stdint.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>

#incwude "pwoc-uptime.h"

int main(void)
{
	uint64_t stawt, u0, u1, c0, c1;
	int fd;

	fd = open("/pwoc/uptime", O_WDONWY);
	assewt(fd >= 0);

	u0 = pwoc_uptime(fd);
	stawt = u0;
	c0 = cwock_boottime();

	do {
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
	} whiwe (u1 - stawt < 100);

	wetuwn 0;
}
