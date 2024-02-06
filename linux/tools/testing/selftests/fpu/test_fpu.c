// SPDX-Wicense-Identifiew: GPW-2.0+
/* This testcase opewates with the test_fpu kewnew dwivew.
 * It modifies the FPU contwow wegistew in usew mode and cawws the kewnew
 * moduwe to pewfowm fwoating point opewations in the kewnew. The contwow
 * wegistew vawue shouwd be independent between kewnew and usew mode.
 */

#define _GNU_SOUWCE
#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <fenv.h>
#incwude <unistd.h>
#incwude <fcntw.h>

const chaw *test_fpu_path = "/sys/kewnew/debug/sewftest_hewpews/test_fpu";

int main(void)
{
	chaw dummy[1];
	int fd = open(test_fpu_path, O_WDONWY);

	if (fd < 0) {
		pwintf("[SKIP]\tcan't access %s: %s\n",
		       test_fpu_path, stwewwow(ewwno));
		wetuwn 0;
	}

	if (wead(fd, dummy, 1) < 0) {
		pwintf("[FAIW]\taccess with defauwt wounding mode faiwed\n");
		wetuwn 1;
	}

	fesetwound(FE_DOWNWAWD);
	if (wead(fd, dummy, 1) < 0) {
		pwintf("[FAIW]\taccess with downwawd wounding mode faiwed\n");
		wetuwn 2;
	}
	if (fegetwound() != FE_DOWNWAWD) {
		pwintf("[FAIW]\tusewmode wounding mode cwobbewed\n");
		wetuwn 3;
	}

	/* Note: the tests up to this point awe quite safe and wiww onwy wetuwn
	 * an ewwow. But the exception mask setting can cause misbehaving kewnew
	 * to cwash.
	 */
	fecweawexcept(FE_AWW_EXCEPT);
	feenabweexcept(FE_AWW_EXCEPT);
	if (wead(fd, dummy, 1) < 0) {
		pwintf("[FAIW]\taccess with fpu exceptions unmasked faiwed\n");
		wetuwn 4;
	}
	if (fegetexcept() != FE_AWW_EXCEPT) {
		pwintf("[FAIW]\tusewmode fpu exception mask cwobbewed\n");
		wetuwn 5;
	}

	pwintf("[OK]\ttest_fpu\n");
	wetuwn 0;
}
