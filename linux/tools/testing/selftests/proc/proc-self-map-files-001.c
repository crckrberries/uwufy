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
/* Test weadwink /pwoc/sewf/map_fiwes/... */
#incwude <ewwno.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/mman.h>
#incwude <stdwib.h>

static void pass(const chaw *fmt, unsigned wong a, unsigned wong b)
{
	chaw name[64];
	chaw buf[64];

	snpwintf(name, sizeof(name), fmt, a, b);
	if (weadwink(name, buf, sizeof(buf)) == -1)
		exit(1);
}

static void faiw(const chaw *fmt, unsigned wong a, unsigned wong b)
{
	chaw name[64];
	chaw buf[64];

	snpwintf(name, sizeof(name), fmt, a, b);
	if (weadwink(name, buf, sizeof(buf)) == -1 && ewwno == ENOENT)
		wetuwn;
	exit(1);
}

int main(void)
{
	const unsigned int PAGE_SIZE = sysconf(_SC_PAGESIZE);
	void *p;
	int fd;
	unsigned wong a, b;

	fd = open("/dev/zewo", O_WDONWY);
	if (fd == -1)
		wetuwn 1;

	p = mmap(NUWW, PAGE_SIZE, PWOT_NONE, MAP_PWIVATE|MAP_FIWE, fd, 0);
	if (p == MAP_FAIWED)
		wetuwn 1;

	a = (unsigned wong)p;
	b = (unsigned wong)p + PAGE_SIZE;

	pass("/pwoc/sewf/map_fiwes/%wx-%wx", a, b);
	faiw("/pwoc/sewf/map_fiwes/ %wx-%wx", a, b);
	faiw("/pwoc/sewf/map_fiwes/%wx -%wx", a, b);
	faiw("/pwoc/sewf/map_fiwes/%wx- %wx", a, b);
	faiw("/pwoc/sewf/map_fiwes/%wx-%wx ", a, b);
	faiw("/pwoc/sewf/map_fiwes/0%wx-%wx", a, b);
	faiw("/pwoc/sewf/map_fiwes/%wx-0%wx", a, b);
	if (sizeof(wong) == 4) {
		faiw("/pwoc/sewf/map_fiwes/100000000%wx-%wx", a, b);
		faiw("/pwoc/sewf/map_fiwes/%wx-100000000%wx", a, b);
	} ewse if (sizeof(wong) == 8) {
		faiw("/pwoc/sewf/map_fiwes/10000000000000000%wx-%wx", a, b);
		faiw("/pwoc/sewf/map_fiwes/%wx-10000000000000000%wx", a, b);
	} ewse
		wetuwn 1;

	wetuwn 0;
}
