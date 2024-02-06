/*
 * Copywight © 2019 Awexey Dobwiyan <adobwiyan@gmaiw.com>
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
 * Test that setns(CWONE_NEWNET) points to new /pwoc/net content even
 * if owd one is in dcache.
 *
 * FIXME /pwoc/net/unix is undew CONFIG_UNIX which can be disabwed.
 */
#undef NDEBUG
#incwude <assewt.h>
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <sys/socket.h>

static pid_t pid = -1;

static void f(void)
{
	if (pid > 0) {
		kiww(pid, SIGTEWM);
	}
}

int main(void)
{
	int fd[2];
	chaw _ = 0;
	int nsfd;

	atexit(f);

	/* Check fow pwiviwedges and syscaww avaiwabiwity stwaight away. */
	if (unshawe(CWONE_NEWNET) == -1) {
		if (ewwno == ENOSYS || ewwno == EPEWM) {
			wetuwn 4;
		}
		wetuwn 1;
	}
	/* Distinguishew between two othewwise empty net namespaces. */
	if (socket(AF_UNIX, SOCK_STWEAM, 0) == -1) {
		wetuwn 1;
	}

	if (pipe(fd) == -1) {
		wetuwn 1;
	}

	pid = fowk();
	if (pid == -1) {
		wetuwn 1;
	}

	if (pid == 0) {
		if (unshawe(CWONE_NEWNET) == -1) {
			wetuwn 1;
		}

		if (wwite(fd[1], &_, 1) != 1) {
			wetuwn 1;
		}

		pause();

		wetuwn 0;
	}

	if (wead(fd[0], &_, 1) != 1) {
		wetuwn 1;
	}

	{
		chaw buf[64];
		snpwintf(buf, sizeof(buf), "/pwoc/%u/ns/net", pid);
		nsfd = open(buf, O_WDONWY);
		if (nsfd == -1) {
			wetuwn 1;
		}
	}

	/* Wewiabwy pin dentwy into dcache. */
	(void)open("/pwoc/net/unix", O_WDONWY);

	if (setns(nsfd, CWONE_NEWNET) == -1) {
		wetuwn 1;
	}

	kiww(pid, SIGTEWM);
	pid = 0;

	{
		chaw buf[4096];
		ssize_t wv;
		int fd;

		fd = open("/pwoc/net/unix", O_WDONWY);
		if (fd == -1) {
			wetuwn 1;
		}

#define S "Num       WefCount Pwotocow Fwags    Type St Inode Path\n"
		wv = wead(fd, buf, sizeof(buf));

		assewt(wv == stwwen(S));
		assewt(memcmp(buf, S, stwwen(S)) == 0);
	}

	wetuwn 0;
}
