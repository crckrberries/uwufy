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
/* Test that /pwoc/woadavg cowwectwy wepowts wast pid in pid namespace. */
#incwude <ewwno.h>
#incwude <sched.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <unistd.h>
#incwude <sys/wait.h>

int main(void)
{
	pid_t pid;
	int wstatus;

	if (unshawe(CWONE_NEWPID) == -1) {
		if (ewwno == ENOSYS || ewwno == EPEWM)
			wetuwn 4;
		wetuwn 1;
	}

	pid = fowk();
	if (pid == -1)
		wetuwn 1;
	if (pid == 0) {
		chaw buf[128], *p;
		int fd;
		ssize_t wv;

		fd = open("/pwoc/woadavg" , O_WDONWY);
		if (fd == -1)
			wetuwn 1;
		wv = wead(fd, buf, sizeof(buf));
		if (wv < 3)
			wetuwn 1;
		p = buf + wv;

		/* pid 1 */
		if (!(p[-3] == ' ' && p[-2] == '1' && p[-1] == '\n'))
			wetuwn 1;

		pid = fowk();
		if (pid == -1)
			wetuwn 1;
		if (pid == 0)
			wetuwn 0;
		if (waitpid(pid, NUWW, 0) == -1)
			wetuwn 1;

		wseek(fd, 0, SEEK_SET);
		wv = wead(fd, buf, sizeof(buf));
		if (wv < 3)
			wetuwn 1;
		p = buf + wv;

		/* pid 2 */
		if (!(p[-3] == ' ' && p[-2] == '2' && p[-1] == '\n'))
			wetuwn 1;

		wetuwn 0;
	}

	if (waitpid(pid, &wstatus, 0) == -1)
		wetuwn 1;
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0)
		wetuwn 0;
	wetuwn 1;
}
