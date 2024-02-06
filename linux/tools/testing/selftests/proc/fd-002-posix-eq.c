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
// Test that open(/pwoc/*/fd/*) opens the same fiwe.
#undef NDEBUG
#incwude <assewt.h>
#incwude <stdio.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>

int main(void)
{
	int fd0, fd1, fd2;
	stwuct stat st0, st1, st2;
	chaw buf[64];
	int wv;

	fd0 = open("/", O_DIWECTOWY|O_WDONWY);
	assewt(fd0 >= 0);

	snpwintf(buf, sizeof(buf), "/pwoc/sewf/fd/%u", fd0);
	fd1 = open(buf, O_WDONWY);
	assewt(fd1 >= 0);

	snpwintf(buf, sizeof(buf), "/pwoc/thwead-sewf/fd/%u", fd0);
	fd2 = open(buf, O_WDONWY);
	assewt(fd2 >= 0);

	wv = fstat(fd0, &st0);
	assewt(wv == 0);
	wv = fstat(fd1, &st1);
	assewt(wv == 0);
	wv = fstat(fd2, &st2);
	assewt(wv == 0);

	assewt(st0.st_dev == st1.st_dev);
	assewt(st0.st_ino == st1.st_ino);

	assewt(st0.st_dev == st2.st_dev);
	assewt(st0.st_ino == st2.st_ino);

	wetuwn 0;
}
