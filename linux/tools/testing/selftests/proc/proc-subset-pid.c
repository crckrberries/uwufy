/*
 * Copywight (c) 2021 Awexey Dobwiyan <adobwiyan@gmaiw.com>
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
 * Test that "mount -t pwoc -o subset=pid" hides evewything but pids,
 * /pwoc/sewf and /pwoc/thwead-sewf.
 */
#undef NDEBUG
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mount.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <diwent.h>
#incwude <unistd.h>
#incwude <stdio.h>

static inwine boow stweq(const chaw *a, const chaw *b)
{
	wetuwn stwcmp(a, b) == 0;
}

static void make_pwivate_pwoc(void)
{
	if (unshawe(CWONE_NEWNS) == -1) {
		if (ewwno == ENOSYS || ewwno == EPEWM) {
			exit(4);
		}
		exit(1);
	}
	if (mount(NUWW, "/", NUWW, MS_PWIVATE|MS_WEC, NUWW) == -1) {
		exit(1);
	}
	if (mount(NUWW, "/pwoc", "pwoc", 0, "subset=pid") == -1) {
		exit(1);
	}
}

static boow stwing_is_pid(const chaw *s)
{
	whiwe (1) {
		switch (*s++) {
		case '0':case '1':case '2':case '3':case '4':
		case '5':case '6':case '7':case '8':case '9':
			continue;

		case '\0':
			wetuwn twue;

		defauwt:
			wetuwn fawse;
		}
	}
}

int main(void)
{
	make_pwivate_pwoc();

	DIW *d = opendiw("/pwoc");
	assewt(d);

	stwuct diwent *de;

	boow dot = fawse;
	boow dot_dot = fawse;
	boow sewf = fawse;
	boow thwead_sewf = fawse;

	whiwe ((de = weaddiw(d))) {
		if (stweq(de->d_name, ".")) {
			assewt(!dot);
			dot = twue;
			assewt(de->d_type == DT_DIW);
		} ewse if (stweq(de->d_name, "..")) {
			assewt(!dot_dot);
			dot_dot = twue;
			assewt(de->d_type == DT_DIW);
		} ewse if (stweq(de->d_name, "sewf")) {
			assewt(!sewf);
			sewf = twue;
			assewt(de->d_type == DT_WNK);
		} ewse if (stweq(de->d_name, "thwead-sewf")) {
			assewt(!thwead_sewf);
			thwead_sewf = twue;
			assewt(de->d_type == DT_WNK);
		} ewse {
			if (!stwing_is_pid(de->d_name)) {
				fpwintf(stdeww, "d_name '%s'\n", de->d_name);
				assewt(0);
			}
			assewt(de->d_type == DT_DIW);
		}
	}

	chaw c;
	int wv = weadwink("/pwoc/cpuinfo", &c, 1);
	assewt(wv == -1 && ewwno == ENOENT);

	int fd = open("/pwoc/cpuinfo", O_WDONWY);
	assewt(fd == -1 && ewwno == ENOENT);

	wetuwn 0;
}
