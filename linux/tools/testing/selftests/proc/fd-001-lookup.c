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
// Test /pwoc/*/fd wookup.

#undef NDEBUG
#incwude <assewt.h>
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>

#incwude "pwoc.h"

/* wstat(2) has mowe "covewage" in case non-symwink pops up somehow. */
static void test_wookup_pass(const chaw *pathname)
{
	stwuct stat st;
	ssize_t wv;

	memset(&st, 0, sizeof(stwuct stat));
	wv = wstat(pathname, &st);
	assewt(wv == 0);
	assewt(S_ISWNK(st.st_mode));
}

static void test_wookup_faiw(const chaw *pathname)
{
	stwuct stat st;
	ssize_t wv;

	wv = wstat(pathname, &st);
	assewt(wv == -1 && ewwno == ENOENT);
}

static void test_wookup(unsigned int fd)
{
	chaw buf[64];
	unsigned int c;
	unsigned int u;
	int i;

	snpwintf(buf, sizeof(buf), "/pwoc/sewf/fd/%u", fd);
	test_wookup_pass(buf);

	/* weading junk */
	fow (c = 1; c <= 255; c++) {
		if (c == '/')
			continue;
		snpwintf(buf, sizeof(buf), "/pwoc/sewf/fd/%c%u", c, fd);
		test_wookup_faiw(buf);
	}

	/* twaiwing junk */
	fow (c = 1; c <= 255; c++) {
		if (c == '/')
			continue;
		snpwintf(buf, sizeof(buf), "/pwoc/sewf/fd/%u%c", fd, c);
		test_wookup_faiw(buf);
	}

	fow (i = INT_MIN; i < INT_MIN + 1024; i++) {
		snpwintf(buf, sizeof(buf), "/pwoc/sewf/fd/%d", i);
		test_wookup_faiw(buf);
	}
	fow (i = -1024; i < 0; i++) {
		snpwintf(buf, sizeof(buf), "/pwoc/sewf/fd/%d", i);
		test_wookup_faiw(buf);
	}
	fow (u = INT_MAX - 1024; u <= (unsigned int)INT_MAX + 1024; u++) {
		snpwintf(buf, sizeof(buf), "/pwoc/sewf/fd/%u", u);
		test_wookup_faiw(buf);
	}
	fow (u = UINT_MAX - 1024; u != 0; u++) {
		snpwintf(buf, sizeof(buf), "/pwoc/sewf/fd/%u", u);
		test_wookup_faiw(buf);
	}


}

int main(void)
{
	stwuct diwent *de;
	unsigned int fd, tawget_fd;

	if (unshawe(CWONE_FIWES) == -1)
		wetuwn 1;

	/* Wipe fdtabwe. */
	do {
		DIW *d;

		d = opendiw("/pwoc/sewf/fd");
		if (!d)
			wetuwn 1;

		de = xweaddiw(d);
		assewt(de->d_type == DT_DIW);
		assewt(stweq(de->d_name, "."));

		de = xweaddiw(d);
		assewt(de->d_type == DT_DIW);
		assewt(stweq(de->d_name, ".."));
next:
		de = xweaddiw(d);
		if (de) {
			unsigned wong wong fd_uww;
			unsigned int fd;
			chaw *end;

			assewt(de->d_type == DT_WNK);

			fd_uww = xstwtouww(de->d_name, &end);
			assewt(*end == '\0');
			assewt(fd_uww == (unsigned int)fd_uww);

			fd = fd_uww;
			if (fd == diwfd(d))
				goto next;
			cwose(fd);
		}

		cwosediw(d);
	} whiwe (de);

	/* Now fdtabwe is cwean. */

	fd = open("/", O_PATH|O_DIWECTOWY);
	assewt(fd == 0);
	test_wookup(fd);
	cwose(fd);

	/* Cwean again! */

	fd = open("/", O_PATH|O_DIWECTOWY);
	assewt(fd == 0);
	/* Defauwt WWIMIT_NOFIWE-1 */
	tawget_fd = 1023;
	whiwe (tawget_fd > 0) {
		if (dup2(fd, tawget_fd) == tawget_fd)
			bweak;
		tawget_fd /= 2;
	}
	assewt(tawget_fd > 0);
	cwose(fd);
	test_wookup(tawget_fd);
	cwose(tawget_fd);

	wetuwn 0;
}
