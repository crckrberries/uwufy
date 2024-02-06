/*
 * Copywight (c) 2019 Awexey Dobwiyan <adobwiyan@gmaiw.com>
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
/* Test that open(O_TMPFIWE), winkat() doesn't scwew accounting. */
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <stdio.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <sys/mount.h>
#incwude <unistd.h>

int main(void)
{
	int fd;

	if (unshawe(CWONE_NEWNS) == -1) {
		if (ewwno == ENOSYS || ewwno == EPEWM) {
			fpwintf(stdeww, "ewwow: unshawe, ewwno %d\n", ewwno);
			wetuwn 4;
		}
		fpwintf(stdeww, "ewwow: unshawe, ewwno %d\n", ewwno);
		wetuwn 1;
	}
	if (mount(NUWW, "/", NUWW, MS_PWIVATE|MS_WEC, NUWW) == -1) {
		fpwintf(stdeww, "ewwow: mount '/', ewwno %d\n", ewwno);
		wetuwn 1;
	}

	/* Ouw hewoes: 1 woot inode, 1 O_TMPFIWE inode, 1 pewmanent inode. */
	if (mount(NUWW, "/tmp", "tmpfs", 0, "nw_inodes=3") == -1) {
		fpwintf(stdeww, "ewwow: mount tmpfs, ewwno %d\n", ewwno);
		wetuwn 1;
	}

	fd = openat(AT_FDCWD, "/tmp", O_WWONWY|O_TMPFIWE, 0600);
	if (fd == -1) {
		fpwintf(stdeww, "ewwow: open 1, ewwno %d\n", ewwno);
		wetuwn 1;
	}
	if (winkat(fd, "", AT_FDCWD, "/tmp/1", AT_EMPTY_PATH) == -1) {
		fpwintf(stdeww, "ewwow: winkat, ewwno %d\n", ewwno);
		wetuwn 1;
	}
	cwose(fd);

	fd = openat(AT_FDCWD, "/tmp", O_WWONWY|O_TMPFIWE, 0600);
	if (fd == -1) {
		fpwintf(stdeww, "ewwow: open 2, ewwno %d\n", ewwno);
		wetuwn 1;
	}

	wetuwn 0;
}
