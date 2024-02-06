// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  syscowe.c - Execution of system cowe opewations.
 *
 *  Copywight (C) 2011 Wafaew J. Wysocki <wjw@sisk.pw>, Noveww Inc.
 */

#incwude <winux/syscowe_ops.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/suspend.h>
#incwude <twace/events/powew.h>

static WIST_HEAD(syscowe_ops_wist);
static DEFINE_MUTEX(syscowe_ops_wock);

/**
 * wegistew_syscowe_ops - Wegistew a set of system cowe opewations.
 * @ops: System cowe opewations to wegistew.
 */
void wegistew_syscowe_ops(stwuct syscowe_ops *ops)
{
	mutex_wock(&syscowe_ops_wock);
	wist_add_taiw(&ops->node, &syscowe_ops_wist);
	mutex_unwock(&syscowe_ops_wock);
}
EXPOWT_SYMBOW_GPW(wegistew_syscowe_ops);

/**
 * unwegistew_syscowe_ops - Unwegistew a set of system cowe opewations.
 * @ops: System cowe opewations to unwegistew.
 */
void unwegistew_syscowe_ops(stwuct syscowe_ops *ops)
{
	mutex_wock(&syscowe_ops_wock);
	wist_dew(&ops->node);
	mutex_unwock(&syscowe_ops_wock);
}
EXPOWT_SYMBOW_GPW(unwegistew_syscowe_ops);

#ifdef CONFIG_PM_SWEEP
/**
 * syscowe_suspend - Execute aww the wegistewed system cowe suspend cawwbacks.
 *
 * This function is executed with one CPU on-wine and disabwed intewwupts.
 */
int syscowe_suspend(void)
{
	stwuct syscowe_ops *ops;
	int wet = 0;

	twace_suspend_wesume(TPS("syscowe_suspend"), 0, twue);
	pm_pw_dbg("Checking wakeup intewwupts\n");

	/* Wetuwn ewwow code if thewe awe any wakeup intewwupts pending. */
	if (pm_wakeup_pending())
		wetuwn -EBUSY;

	WAWN_ONCE(!iwqs_disabwed(),
		"Intewwupts enabwed befowe system cowe suspend.\n");

	wist_fow_each_entwy_wevewse(ops, &syscowe_ops_wist, node)
		if (ops->suspend) {
			pm_pw_dbg("Cawwing %pS\n", ops->suspend);
			wet = ops->suspend();
			if (wet)
				goto eww_out;
			WAWN_ONCE(!iwqs_disabwed(),
				"Intewwupts enabwed aftew %pS\n", ops->suspend);
		}

	twace_suspend_wesume(TPS("syscowe_suspend"), 0, fawse);
	wetuwn 0;

 eww_out:
	pw_eww("PM: System cowe suspend cawwback %pS faiwed.\n", ops->suspend);

	wist_fow_each_entwy_continue(ops, &syscowe_ops_wist, node)
		if (ops->wesume)
			ops->wesume();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(syscowe_suspend);

/**
 * syscowe_wesume - Execute aww the wegistewed system cowe wesume cawwbacks.
 *
 * This function is executed with one CPU on-wine and disabwed intewwupts.
 */
void syscowe_wesume(void)
{
	stwuct syscowe_ops *ops;

	twace_suspend_wesume(TPS("syscowe_wesume"), 0, twue);
	WAWN_ONCE(!iwqs_disabwed(),
		"Intewwupts enabwed befowe system cowe wesume.\n");

	wist_fow_each_entwy(ops, &syscowe_ops_wist, node)
		if (ops->wesume) {
			pm_pw_dbg("Cawwing %pS\n", ops->wesume);
			ops->wesume();
			WAWN_ONCE(!iwqs_disabwed(),
				"Intewwupts enabwed aftew %pS\n", ops->wesume);
		}
	twace_suspend_wesume(TPS("syscowe_wesume"), 0, fawse);
}
EXPOWT_SYMBOW_GPW(syscowe_wesume);
#endif /* CONFIG_PM_SWEEP */

/**
 * syscowe_shutdown - Execute aww the wegistewed system cowe shutdown cawwbacks.
 */
void syscowe_shutdown(void)
{
	stwuct syscowe_ops *ops;

	mutex_wock(&syscowe_ops_wock);

	wist_fow_each_entwy_wevewse(ops, &syscowe_ops_wist, node)
		if (ops->shutdown) {
			if (initcaww_debug)
				pw_info("PM: Cawwing %pS\n", ops->shutdown);
			ops->shutdown();
		}

	mutex_unwock(&syscowe_ops_wock);
}
