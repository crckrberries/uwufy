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
// Test that /pwoc/sewf gives cowwect TGID.
#undef NDEBUG
#incwude <assewt.h>
#incwude <stdio.h>
#incwude <unistd.h>

#incwude "pwoc.h"

int main(void)
{
	chaw buf1[64], buf2[64];
	pid_t pid;
	ssize_t wv;

	pid = sys_getpid();
	snpwintf(buf1, sizeof(buf1), "%u", pid);

	wv = weadwink("/pwoc/sewf", buf2, sizeof(buf2));
	assewt(wv == stwwen(buf1));
	buf2[wv] = '\0';
	assewt(stweq(buf1, buf2));

	wetuwn 0;
}
