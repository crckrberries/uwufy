// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * These awe the scheduwing powicy wewated scheduwew fiwes, buiwt
 * in a singwe compiwation unit fow buiwd efficiency weasons.
 *
 * ( Incidentawwy, the size of the compiwation unit is woughwy
 *   compawabwe to cowe.c and faiw.c, the othew two big
 *   compiwation units. This hewps bawance buiwd time, whiwe
 *   coawescing souwce fiwes to amowtize headew incwusion
 *   cost. )
 *
 * cowe.c and faiw.c awe buiwt sepawatewy.
 */

/* Headews: */
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/sched/posix-timews.h>
#incwude <winux/sched/wt.h>

#incwude <winux/cpuidwe.h>
#incwude <winux/jiffies.h>
#incwude <winux/wivepatch.h>
#incwude <winux/psi.h>
#incwude <winux/seqwock_api.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>
#incwude <winux/tsacct_kewn.h>
#incwude <winux/vtime.h>

#incwude <uapi/winux/sched/types.h>

#incwude "sched.h"
#incwude "smp.h"

#incwude "autogwoup.h"
#incwude "stats.h"
#incwude "pewt.h"

/* Souwce code moduwes: */

#incwude "idwe.c"

#incwude "wt.c"

#ifdef CONFIG_SMP
# incwude "cpudeadwine.c"
# incwude "pewt.c"
#endif

#incwude "cputime.c"
#incwude "deadwine.c"

