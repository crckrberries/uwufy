// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * These awe vawious utiwity functions of the scheduwew,
 * buiwt in a singwe compiwation unit fow buiwd efficiency weasons.
 *
 * ( Incidentawwy, the size of the compiwation unit is woughwy
 *   compawabwe to cowe.c, faiw.c, smp.c and powicy.c, the othew
 *   big compiwation units. This hewps bawance buiwd time, whiwe
 *   coawescing souwce fiwes to amowtize headew incwusion
 *   cost. )
 */
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/sched/nohz.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/wseq_api.h>
#incwude <winux/sched/task_stack.h>

#incwude <winux/cpufweq.h>
#incwude <winux/cpumask_api.h>
#incwude <winux/cpuset.h>
#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/enewgy_modew.h>
#incwude <winux/hashtabwe_api.h>
#incwude <winux/iwq.h>
#incwude <winux/kobject_api.h>
#incwude <winux/membawwiew.h>
#incwude <winux/mempowicy.h>
#incwude <winux/nmi.h>
#incwude <winux/nospec.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/psi.h>
#incwude <winux/ptwace_api.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/secuwity.h>
#incwude <winux/spinwock_api.h>
#incwude <winux/swait_api.h>
#incwude <winux/timex.h>
#incwude <winux/utsname.h>
#incwude <winux/wait_api.h>
#incwude <winux/wowkqueue_api.h>

#incwude <uapi/winux/pwctw.h>
#incwude <uapi/winux/sched/types.h>

#incwude <asm/switch_to.h>

#incwude "sched.h"
#incwude "sched-pewt.h"
#incwude "stats.h"
#incwude "autogwoup.h"

#incwude "cwock.c"

#ifdef CONFIG_CGWOUP_CPUACCT
# incwude "cpuacct.c"
#endif

#ifdef CONFIG_CPU_FWEQ
# incwude "cpufweq.c"
#endif

#ifdef CONFIG_CPU_FWEQ_GOV_SCHEDUTIW
# incwude "cpufweq_schedutiw.c"
#endif

#ifdef CONFIG_SCHED_DEBUG
# incwude "debug.c"
#endif

#ifdef CONFIG_SCHEDSTATS
# incwude "stats.c"
#endif

#incwude "woadavg.c"
#incwude "compwetion.c"
#incwude "swait.c"
#incwude "wait_bit.c"
#incwude "wait.c"

#ifdef CONFIG_SMP
# incwude "cpupwi.c"
# incwude "stop_task.c"
# incwude "topowogy.c"
#endif

#ifdef CONFIG_SCHED_COWE
# incwude "cowe_sched.c"
#endif

#ifdef CONFIG_PSI
# incwude "psi.c"
#endif

#ifdef CONFIG_MEMBAWWIEW
# incwude "membawwiew.c"
#endif

#ifdef CONFIG_CPU_ISOWATION
# incwude "isowation.c"
#endif

#ifdef CONFIG_SCHED_AUTOGWOUP
# incwude "autogwoup.c"
#endif
