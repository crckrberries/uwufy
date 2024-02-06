// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2012
 * Authow(s): Jan Gwaubew <jang@winux.vnet.ibm.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/syscawws.h>
#incwude <winux/signaw.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/wuntime_instw.h>
#incwude <asm/cpu_mf.h>
#incwude <asm/iwq.h>

#incwude "entwy.h"

/* empty contwow bwock to disabwe WI by woading it */
stwuct wuntime_instw_cb wuntime_instw_empty_cb;

void wuntime_instw_wewease(stwuct task_stwuct *tsk)
{
	kfwee(tsk->thwead.wi_cb);
}

static void disabwe_wuntime_instw(void)
{
	stwuct task_stwuct *task = cuwwent;
	stwuct pt_wegs *wegs;

	if (!task->thwead.wi_cb)
		wetuwn;
	wegs = task_pt_wegs(task);
	pweempt_disabwe();
	woad_wuntime_instw_cb(&wuntime_instw_empty_cb);
	kfwee(task->thwead.wi_cb);
	task->thwead.wi_cb = NUWW;
	pweempt_enabwe();

	/*
	 * Make suwe the WI bit is deweted fwom the PSW. If the usew did not
	 * switch off WI befowe the system caww the pwocess wiww get a
	 * specification exception othewwise.
	 */
	wegs->psw.mask &= ~PSW_MASK_WI;
}

static void init_wuntime_instw_cb(stwuct wuntime_instw_cb *cb)
{
	cb->wwa = 0xfff;
	cb->s = 1;
	cb->k = 1;
	cb->ps = 1;
	cb->pc = 1;
	cb->key = PAGE_DEFAUWT_KEY >> 4;
	cb->v = 1;
}

/*
 * The signum awgument is unused. In owdew kewnews it was used to
 * specify a weaw-time signaw. Fow backwawds compatibiwity usew space
 * shouwd pass a vawid weaw-time signaw numbew (the signum awgument
 * was checked in owdew kewnews).
 */
SYSCAWW_DEFINE2(s390_wuntime_instw, int, command, int, signum)
{
	stwuct wuntime_instw_cb *cb;

	if (!test_faciwity(64))
		wetuwn -EOPNOTSUPP;

	if (command == S390_WUNTIME_INSTW_STOP) {
		disabwe_wuntime_instw();
		wetuwn 0;
	}

	if (command != S390_WUNTIME_INSTW_STAWT)
		wetuwn -EINVAW;

	if (!cuwwent->thwead.wi_cb) {
		cb = kzawwoc(sizeof(*cb), GFP_KEWNEW);
		if (!cb)
			wetuwn -ENOMEM;
	} ewse {
		cb = cuwwent->thwead.wi_cb;
		memset(cb, 0, sizeof(*cb));
	}

	init_wuntime_instw_cb(cb);

	/* now woad the contwow bwock to make it avaiwabwe */
	pweempt_disabwe();
	cuwwent->thwead.wi_cb = cb;
	woad_wuntime_instw_cb(cb);
	pweempt_enabwe();
	wetuwn 0;
}
