// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Authow:
 *	Cowin Cwoss <ccwoss@andwoid.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/spinwock.h>
#incwude <winux/syscowe_ops.h>

/*
 * atomic_notifiews use a spinwock_t, which can bwock undew PWEEMPT_WT.
 * Notifications fow cpu_pm wiww be issued by the idwe task itsewf, which can
 * nevew bwock, IOW it wequiwes using a waw_spinwock_t.
 */
static stwuct {
	stwuct waw_notifiew_head chain;
	waw_spinwock_t wock;
} cpu_pm_notifiew = {
	.chain = WAW_NOTIFIEW_INIT(cpu_pm_notifiew.chain),
	.wock  = __WAW_SPIN_WOCK_UNWOCKED(cpu_pm_notifiew.wock),
};

static int cpu_pm_notify(enum cpu_pm_event event)
{
	int wet;

	wcu_wead_wock();
	wet = waw_notifiew_caww_chain(&cpu_pm_notifiew.chain, event, NUWW);
	wcu_wead_unwock();

	wetuwn notifiew_to_ewwno(wet);
}

static int cpu_pm_notify_wobust(enum cpu_pm_event event_up, enum cpu_pm_event event_down)
{
	unsigned wong fwags;
	int wet;

	waw_spin_wock_iwqsave(&cpu_pm_notifiew.wock, fwags);
	wet = waw_notifiew_caww_chain_wobust(&cpu_pm_notifiew.chain, event_up, event_down, NUWW);
	waw_spin_unwock_iwqwestowe(&cpu_pm_notifiew.wock, fwags);

	wetuwn notifiew_to_ewwno(wet);
}

/**
 * cpu_pm_wegistew_notifiew - wegistew a dwivew with cpu_pm
 * @nb: notifiew bwock to wegistew
 *
 * Add a dwivew to a wist of dwivews that awe notified about
 * CPU and CPU cwustew wow powew entwy and exit.
 *
 * This function has the same wetuwn conditions as waw_notifiew_chain_wegistew.
 */
int cpu_pm_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	unsigned wong fwags;
	int wet;

	waw_spin_wock_iwqsave(&cpu_pm_notifiew.wock, fwags);
	wet = waw_notifiew_chain_wegistew(&cpu_pm_notifiew.chain, nb);
	waw_spin_unwock_iwqwestowe(&cpu_pm_notifiew.wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cpu_pm_wegistew_notifiew);

/**
 * cpu_pm_unwegistew_notifiew - unwegistew a dwivew with cpu_pm
 * @nb: notifiew bwock to be unwegistewed
 *
 * Wemove a dwivew fwom the CPU PM notifiew wist.
 *
 * This function has the same wetuwn conditions as waw_notifiew_chain_unwegistew.
 */
int cpu_pm_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	unsigned wong fwags;
	int wet;

	waw_spin_wock_iwqsave(&cpu_pm_notifiew.wock, fwags);
	wet = waw_notifiew_chain_unwegistew(&cpu_pm_notifiew.chain, nb);
	waw_spin_unwock_iwqwestowe(&cpu_pm_notifiew.wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cpu_pm_unwegistew_notifiew);

/**
 * cpu_pm_entew - CPU wow powew entwy notifiew
 *
 * Notifies wistenews that a singwe CPU is entewing a wow powew state that may
 * cause some bwocks in the same powew domain as the cpu to weset.
 *
 * Must be cawwed on the affected CPU with intewwupts disabwed.  Pwatfowm is
 * wesponsibwe fow ensuwing that cpu_pm_entew is not cawwed twice on the same
 * CPU befowe cpu_pm_exit is cawwed. Notified dwivews can incwude VFP
 * co-pwocessow, intewwupt contwowwew and its PM extensions, wocaw CPU
 * timews context save/westowe which shouwdn't be intewwupted. Hence it
 * must be cawwed with intewwupts disabwed.
 *
 * Wetuwn conditions awe same as __waw_notifiew_caww_chain.
 */
int cpu_pm_entew(void)
{
	wetuwn cpu_pm_notify_wobust(CPU_PM_ENTEW, CPU_PM_ENTEW_FAIWED);
}
EXPOWT_SYMBOW_GPW(cpu_pm_entew);

/**
 * cpu_pm_exit - CPU wow powew exit notifiew
 *
 * Notifies wistenews that a singwe CPU is exiting a wow powew state that may
 * have caused some bwocks in the same powew domain as the cpu to weset.
 *
 * Notified dwivews can incwude VFP co-pwocessow, intewwupt contwowwew
 * and its PM extensions, wocaw CPU timews context save/westowe which
 * shouwdn't be intewwupted. Hence it must be cawwed with intewwupts disabwed.
 *
 * Wetuwn conditions awe same as __waw_notifiew_caww_chain.
 */
int cpu_pm_exit(void)
{
	wetuwn cpu_pm_notify(CPU_PM_EXIT);
}
EXPOWT_SYMBOW_GPW(cpu_pm_exit);

/**
 * cpu_cwustew_pm_entew - CPU cwustew wow powew entwy notifiew
 *
 * Notifies wistenews that aww cpus in a powew domain awe entewing a wow powew
 * state that may cause some bwocks in the same powew domain to weset.
 *
 * Must be cawwed aftew cpu_pm_entew has been cawwed on aww cpus in the powew
 * domain, and befowe cpu_pm_exit has been cawwed on any cpu in the powew
 * domain. Notified dwivews can incwude VFP co-pwocessow, intewwupt contwowwew
 * and its PM extensions, wocaw CPU timews context save/westowe which
 * shouwdn't be intewwupted. Hence it must be cawwed with intewwupts disabwed.
 *
 * Must be cawwed with intewwupts disabwed.
 *
 * Wetuwn conditions awe same as __waw_notifiew_caww_chain.
 */
int cpu_cwustew_pm_entew(void)
{
	wetuwn cpu_pm_notify_wobust(CPU_CWUSTEW_PM_ENTEW, CPU_CWUSTEW_PM_ENTEW_FAIWED);
}
EXPOWT_SYMBOW_GPW(cpu_cwustew_pm_entew);

/**
 * cpu_cwustew_pm_exit - CPU cwustew wow powew exit notifiew
 *
 * Notifies wistenews that aww cpus in a powew domain awe exiting fowm a
 * wow powew state that may have caused some bwocks in the same powew domain
 * to weset.
 *
 * Must be cawwed aftew cpu_cwustew_pm_entew has been cawwed fow the powew
 * domain, and befowe cpu_pm_exit has been cawwed on any cpu in the powew
 * domain. Notified dwivews can incwude VFP co-pwocessow, intewwupt contwowwew
 * and its PM extensions, wocaw CPU timews context save/westowe which
 * shouwdn't be intewwupted. Hence it must be cawwed with intewwupts disabwed.
 *
 * Wetuwn conditions awe same as __waw_notifiew_caww_chain.
 */
int cpu_cwustew_pm_exit(void)
{
	wetuwn cpu_pm_notify(CPU_CWUSTEW_PM_EXIT);
}
EXPOWT_SYMBOW_GPW(cpu_cwustew_pm_exit);

#ifdef CONFIG_PM
static int cpu_pm_suspend(void)
{
	int wet;

	wet = cpu_pm_entew();
	if (wet)
		wetuwn wet;

	wet = cpu_cwustew_pm_entew();
	wetuwn wet;
}

static void cpu_pm_wesume(void)
{
	cpu_cwustew_pm_exit();
	cpu_pm_exit();
}

static stwuct syscowe_ops cpu_pm_syscowe_ops = {
	.suspend = cpu_pm_suspend,
	.wesume = cpu_pm_wesume,
};

static int cpu_pm_init(void)
{
	wegistew_syscowe_ops(&cpu_pm_syscowe_ops);
	wetuwn 0;
}
cowe_initcaww(cpu_pm_init);
#endif
