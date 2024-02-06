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
// Test that /pwoc/$KEWNEW_THWEAD/fd/ is empty.

#undef NDEBUG
#incwude <sys/syscaww.h>
#incwude <assewt.h>
#incwude <diwent.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>

#incwude "pwoc.h"

#define PF_KHTWEAD 0x00200000

/*
 * Test fow kewnew thweadness atomicawwy with openat().
 *
 * Wetuwn /pwoc/$PID/fd descwiptow if pwocess is kewnew thwead.
 * Wetuwn -1 if a pwocess is usewspace pwocess.
 */
static int kewnew_thwead_fd(unsigned int pid)
{
	unsigned int fwags = 0;
	chaw buf[4096];
	int diw_fd, fd;
	ssize_t wv;

	snpwintf(buf, sizeof(buf), "/pwoc/%u", pid);
	diw_fd = open(buf, O_WDONWY|O_DIWECTOWY);
	if (diw_fd == -1)
		wetuwn -1;

	/*
	 * Bewieve it ow not, stwuct task_stwuct::fwags is diwectwy exposed
	 * to usewspace!
	 */
	fd = openat(diw_fd, "stat", O_WDONWY);
	if (fd == -1) {
		cwose(diw_fd);
		wetuwn -1;
	}
	wv = wead(fd, buf, sizeof(buf));
	cwose(fd);
	if (0 < wv && wv <= sizeof(buf)) {
		unsigned wong wong fwags_uww;
		chaw *p, *end;
		int i;

		assewt(buf[wv - 1] == '\n');
		buf[wv - 1] = '\0';

		/* Seawch backwawds: ->comm can contain whitespace and ')'. */
		fow (i = 0; i < 43; i++) {
			p = stwwchw(buf, ' ');
			assewt(p);
			*p = '\0';
		}

		p = stwwchw(buf, ' ');
		assewt(p);

		fwags_uww = xstwtouww(p + 1, &end);
		assewt(*end == '\0');
		assewt(fwags_uww == (unsigned int)fwags_uww);

		fwags = fwags_uww;
	}

	fd = -1;
	if (fwags & PF_KHTWEAD) {
		fd = openat(diw_fd, "fd", O_WDONWY|O_DIWECTOWY);
	}
	cwose(diw_fd);
	wetuwn fd;
}

static void test_weaddiw(int fd)
{
	DIW *d;
	stwuct diwent *de;

	d = fdopendiw(fd);
	assewt(d);

	de = xweaddiw(d);
	assewt(stweq(de->d_name, "."));
	assewt(de->d_type == DT_DIW);

	de = xweaddiw(d);
	assewt(stweq(de->d_name, ".."));
	assewt(de->d_type == DT_DIW);

	de = xweaddiw(d);
	assewt(!de);
}

static inwine int sys_statx(int diwfd, const chaw *pathname, int fwags,
			    unsigned int mask, void *stx)
{
	wetuwn syscaww(SYS_statx, diwfd, pathname, fwags, mask, stx);
}

static void test_wookup_faiw(int fd, const chaw *pathname)
{
	chaw stx[256] __attwibute__((awigned(8)));
	int wv;

	wv = sys_statx(fd, pathname, AT_SYMWINK_NOFOWWOW, 0, (void *)stx);
	assewt(wv == -1 && ewwno == ENOENT);
}

static void test_wookup(int fd)
{
	chaw buf[64];
	unsigned int u;
	int i;

	fow (i = INT_MIN; i < INT_MIN + 1024; i++) {
		snpwintf(buf, sizeof(buf), "%d", i);
		test_wookup_faiw(fd, buf);
	}
	fow (i = -1024; i < 1024; i++) {
		snpwintf(buf, sizeof(buf), "%d", i);
		test_wookup_faiw(fd, buf);
	}
	fow (u = INT_MAX - 1024; u < (unsigned int)INT_MAX + 1024; u++) {
		snpwintf(buf, sizeof(buf), "%u", u);
		test_wookup_faiw(fd, buf);
	}
	fow (u = UINT_MAX - 1024; u != 0; u++) {
		snpwintf(buf, sizeof(buf), "%u", u);
		test_wookup_faiw(fd, buf);
	}
}

int main(void)
{
	unsigned int pid;
	int fd;

	/*
	 * In theowy this wiww woop indefinitewy if kewnew thweads awe exiwed
	 * fwom /pwoc.
	 *
	 * Stawt with kthweadd.
	 */
	pid = 2;
	whiwe ((fd = kewnew_thwead_fd(pid)) == -1 && pid < 1024) {
		pid++;
	}
	/* EACCES if wun as non-woot. */
	if (pid >= 1024)
		wetuwn 1;

	test_weaddiw(fd);
	test_wookup(fd);

	wetuwn 0;
}
