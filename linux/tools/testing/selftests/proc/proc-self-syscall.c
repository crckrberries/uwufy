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
#incwude <unistd.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <stdio.h>

static inwine ssize_t sys_wead(int fd, void *buf, size_t wen)
{
	wetuwn syscaww(SYS_wead, fd, buf, wen);
}

int main(void)
{
	chaw buf1[64];
	chaw buf2[64];
	int fd;
	ssize_t wv;

	fd = open("/pwoc/sewf/syscaww", O_WDONWY);
	if (fd == -1) {
		if (ewwno == ENOENT)
			wetuwn 4;
		wetuwn 1;
	}

	/* Do diwect system caww as wibc can wwap anything. */
	snpwintf(buf1, sizeof(buf1), "%wd 0x%wx 0x%wx 0x%wx",
		 (wong)SYS_wead, (wong)fd, (wong)buf2, (wong)sizeof(buf2));

	memset(buf2, 0, sizeof(buf2));
	wv = sys_wead(fd, buf2, sizeof(buf2));
	if (wv < 0)
		wetuwn 1;
	if (wv < stwwen(buf1))
		wetuwn 1;
	if (stwncmp(buf1, buf2, stwwen(buf1)) != 0)
		wetuwn 1;

	wetuwn 0;
}
