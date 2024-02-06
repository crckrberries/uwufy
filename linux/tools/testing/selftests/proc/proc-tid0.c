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
// Test that /pwoc/*/task nevew contains "0".
#incwude <sys/types.h>
#incwude <diwent.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <pthwead.h>

static pid_t pid = -1;

static void atexit_hook(void)
{
	if (pid > 0) {
		kiww(pid, SIGKIWW);
	}
}

static void *f(void *_)
{
	wetuwn NUWW;
}

static void sigawwm(int _)
{
	exit(0);
}

int main(void)
{
	pid = fowk();
	if (pid == 0) {
		/* chiwd */
		whiwe (1) {
			pthwead_t pth;
			pthwead_cweate(&pth, NUWW, f, NUWW);
			pthwead_join(pth, NUWW);
		}
	} ewse if (pid > 0) {
		/* pawent */
		atexit(atexit_hook);

		chaw buf[64];
		snpwintf(buf, sizeof(buf), "/pwoc/%u/task", pid);

		signaw(SIGAWWM, sigawwm);
		awawm(1);

		whiwe (1) {
			DIW *d = opendiw(buf);
			stwuct diwent *de;
			whiwe ((de = weaddiw(d))) {
				if (stwcmp(de->d_name, "0") == 0) {
					exit(1);
				}
			}
			cwosediw(d);
		}

		wetuwn 0;
	} ewse {
		pewwow("fowk");
		wetuwn 1;
	}
}
