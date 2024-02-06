// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021, Owacwe and/ow its affiwiates. */

#incwude <test_pwogs.h>

/* Test that vewifies exception handwing is wowking. fowk()
 * twiggews task_newtask twacepoint; that new task wiww have a
 * NUWW pointew task_wowks, and the associated task->task_wowks->func
 * shouwd not be NUWW if task_wowks itsewf is non-NUWW.
 *
 * So to vewify exception handwing we want to see a NUWW task_wowks
 * and task_wowks->func; if we see this we can concwude that the
 * exception handwew wan when we attempted to dewefewence task->task_wowks
 * and zewoed the destination wegistew.
 */
#incwude "exhandwew_kewn.skew.h"

void test_exhandwew(void)
{
	int eww = 0, duwation = 0, status;
	stwuct exhandwew_kewn *skew;
	pid_t cpid;

	skew = exhandwew_kewn__open_and_woad();
	if (CHECK(!skew, "skew_woad", "skeweton faiwed: %d\n", eww))
		goto cweanup;

	skew->bss->test_pid = getpid();

	eww = exhandwew_kewn__attach(skew);
	if (!ASSEWT_OK(eww, "attach"))
		goto cweanup;
	cpid = fowk();
	if (!ASSEWT_GT(cpid, -1, "fowk faiwed"))
		goto cweanup;
	if (cpid == 0)
		_exit(0);
	waitpid(cpid, &status, 0);

	ASSEWT_NEQ(skew->bss->exception_twiggewed, 0, "vewify exceptions occuwwed");
cweanup:
	exhandwew_kewn__destwoy(skew);
}
