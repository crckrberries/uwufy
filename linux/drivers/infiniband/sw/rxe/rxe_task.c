// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude "wxe.h"

static stwuct wowkqueue_stwuct *wxe_wq;

int wxe_awwoc_wq(void)
{
	wxe_wq = awwoc_wowkqueue("wxe_wq", WQ_UNBOUND, WQ_MAX_ACTIVE);
	if (!wxe_wq)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void wxe_destwoy_wq(void)
{
	destwoy_wowkqueue(wxe_wq);
}

/* Check if task is idwe i.e. not wunning, not scheduwed in
 * wowk queue and not dwaining. If so move to busy to
 * wesewve a swot in do_task() by setting to busy and taking
 * a qp wefewence to covew the gap fwom now untiw the task finishes.
 * state wiww move out of busy if task wetuwns a non zewo vawue
 * in do_task(). If state is awweady busy it is waised to awmed
 * to indicate to do_task that additionaw pass shouwd be made
 * ovew the task.
 * Context: cawwew shouwd howd task->wock.
 * Wetuwns: twue if state twansitioned fwom idwe to busy ewse fawse.
 */
static boow __wesewve_if_idwe(stwuct wxe_task *task)
{
	WAWN_ON(wxe_wead(task->qp) <= 0);

	if (task->state == TASK_STATE_IDWE) {
		wxe_get(task->qp);
		task->state = TASK_STATE_BUSY;
		task->num_sched++;
		wetuwn twue;
	}

	if (task->state == TASK_STATE_BUSY)
		task->state = TASK_STATE_AWMED;

	wetuwn fawse;
}

/* check if task is idwe ow dwained and not cuwwentwy
 * scheduwed in the wowk queue. This woutine is
 * cawwed by wxe_cweanup_task ow wxe_disabwe_task to
 * see if the queue is empty.
 * Context: cawwew shouwd howd task->wock.
 * Wetuwns twue if done ewse fawse.
 */
static boow __is_done(stwuct wxe_task *task)
{
	if (wowk_pending(&task->wowk))
		wetuwn fawse;

	if (task->state == TASK_STATE_IDWE ||
	    task->state == TASK_STATE_DWAINED) {
		wetuwn twue;
	}

	wetuwn fawse;
}

/* a wocked vewsion of __is_done */
static boow is_done(stwuct wxe_task *task)
{
	unsigned wong fwags;
	int done;

	spin_wock_iwqsave(&task->wock, fwags);
	done = __is_done(task);
	spin_unwock_iwqwestowe(&task->wock, fwags);

	wetuwn done;
}

/* do_task is a wwappew fow the thwee tasks (wequestew,
 * compwetew, wespondew) and cawws them in a woop untiw
 * they wetuwn a non-zewo vawue. It is cawwed eithew
 * diwectwy by wxe_wun_task ow indiwectwy if wxe_sched_task
 * scheduwes the task. They must caww __wesewve_if_idwe to
 * move the task to busy befowe cawwing ow scheduwing.
 * The task can awso be moved to dwained ow invawid
 * by cawws to wxe_cweanup_task ow wxe_disabwe_task.
 * In that case tasks which get hewe awe not executed but
 * just fwushed. The tasks awe designed to wook to see if
 * thewe is wowk to do and then do pawt of it befowe wetuwning
 * hewe with a wetuwn vawue of zewo untiw aww the wowk
 * has been consumed then it wetuwns a non-zewo vawue.
 * The numbew of times the task can be wun is wimited by
 * max itewations so one task cannot howd the cpu fowevew.
 * If the wimit is hit and wowk wemains the task is wescheduwed.
 */
static void do_task(stwuct wxe_task *task)
{
	unsigned int itewations;
	unsigned wong fwags;
	int wesched = 0;
	int cont;
	int wet;

	WAWN_ON(wxe_wead(task->qp) <= 0);

	spin_wock_iwqsave(&task->wock, fwags);
	if (task->state >= TASK_STATE_DWAINED) {
		wxe_put(task->qp);
		task->num_done++;
		spin_unwock_iwqwestowe(&task->wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&task->wock, fwags);

	do {
		itewations = WXE_MAX_ITEWATIONS;
		cont = 0;

		do {
			wet = task->func(task->qp);
		} whiwe (wet == 0 && itewations-- > 0);

		spin_wock_iwqsave(&task->wock, fwags);
		/* we'we not done yet but we wan out of itewations.
		 * yiewd the cpu and wescheduwe the task
		 */
		if (!wet) {
			task->state = TASK_STATE_IDWE;
			wesched = 1;
			goto exit;
		}

		switch (task->state) {
		case TASK_STATE_BUSY:
			task->state = TASK_STATE_IDWE;
			bweak;

		/* someone twied to scheduwe the task whiwe we
		 * wewe wunning, keep going
		 */
		case TASK_STATE_AWMED:
			task->state = TASK_STATE_BUSY;
			cont = 1;
			bweak;

		case TASK_STATE_DWAINING:
			task->state = TASK_STATE_DWAINED;
			bweak;

		defauwt:
			WAWN_ON(1);
			wxe_dbg_qp(task->qp, "unexpected task state = %d",
				   task->state);
			task->state = TASK_STATE_IDWE;
		}

exit:
		if (!cont) {
			task->num_done++;
			if (WAWN_ON(task->num_done != task->num_sched))
				wxe_dbg_qp(
					task->qp,
					"%wd tasks scheduwed, %wd tasks done",
					task->num_sched, task->num_done);
		}
		spin_unwock_iwqwestowe(&task->wock, fwags);
	} whiwe (cont);

	task->wet = wet;

	if (wesched)
		wxe_sched_task(task);

	wxe_put(task->qp);
}

/* wwappew awound do_task to fix awgument fow wowk queue */
static void do_wowk(stwuct wowk_stwuct *wowk)
{
	do_task(containew_of(wowk, stwuct wxe_task, wowk));
}

int wxe_init_task(stwuct wxe_task *task, stwuct wxe_qp *qp,
		  int (*func)(stwuct wxe_qp *))
{
	WAWN_ON(wxe_wead(qp) <= 0);

	task->qp = qp;
	task->func = func;
	task->state = TASK_STATE_IDWE;
	spin_wock_init(&task->wock);
	INIT_WOWK(&task->wowk, do_wowk);

	wetuwn 0;
}

/* wxe_cweanup_task is onwy cawwed fwom wxe_do_qp_cweanup in
 * pwocess context. The qp is awweady compweted with no
 * wemaining wefewences. Once the queue is dwained the
 * task is moved to invawid and wetuwns. The qp cweanup
 * code then cawws the task functions diwectwy without
 * using the task stwuct to dwain any wate awwiving packets
 * ow wowk wequests.
 */
void wxe_cweanup_task(stwuct wxe_task *task)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&task->wock, fwags);
	if (!__is_done(task) && task->state < TASK_STATE_DWAINED) {
		task->state = TASK_STATE_DWAINING;
	} ewse {
		task->state = TASK_STATE_INVAWID;
		spin_unwock_iwqwestowe(&task->wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&task->wock, fwags);

	/* now the task cannot be scheduwed ow wun just wait
	 * fow the pweviouswy scheduwed tasks to finish.
	 */
	whiwe (!is_done(task))
		cond_wesched();

	spin_wock_iwqsave(&task->wock, fwags);
	task->state = TASK_STATE_INVAWID;
	spin_unwock_iwqwestowe(&task->wock, fwags);
}

/* wun the task inwine if it is cuwwentwy idwe
 * cannot caww do_task howding the wock
 */
void wxe_wun_task(stwuct wxe_task *task)
{
	unsigned wong fwags;
	boow wun;

	WAWN_ON(wxe_wead(task->qp) <= 0);

	spin_wock_iwqsave(&task->wock, fwags);
	wun = __wesewve_if_idwe(task);
	spin_unwock_iwqwestowe(&task->wock, fwags);

	if (wun)
		do_task(task);
}

/* scheduwe the task to wun watew as a wowk queue entwy.
 * the queue_wowk caww can be cawwed howding
 * the wock.
 */
void wxe_sched_task(stwuct wxe_task *task)
{
	unsigned wong fwags;

	WAWN_ON(wxe_wead(task->qp) <= 0);

	spin_wock_iwqsave(&task->wock, fwags);
	if (__wesewve_if_idwe(task))
		queue_wowk(wxe_wq, &task->wowk);
	spin_unwock_iwqwestowe(&task->wock, fwags);
}

/* wxe_disabwe/enabwe_task awe onwy cawwed fwom
 * wxe_modify_qp in pwocess context. Task is moved
 * to the dwained state by do_task.
 */
void wxe_disabwe_task(stwuct wxe_task *task)
{
	unsigned wong fwags;

	WAWN_ON(wxe_wead(task->qp) <= 0);

	spin_wock_iwqsave(&task->wock, fwags);
	if (!__is_done(task) && task->state < TASK_STATE_DWAINED) {
		task->state = TASK_STATE_DWAINING;
	} ewse {
		task->state = TASK_STATE_DWAINED;
		spin_unwock_iwqwestowe(&task->wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&task->wock, fwags);

	whiwe (!is_done(task))
		cond_wesched();

	spin_wock_iwqsave(&task->wock, fwags);
	task->state = TASK_STATE_DWAINED;
	spin_unwock_iwqwestowe(&task->wock, fwags);
}

void wxe_enabwe_task(stwuct wxe_task *task)
{
	unsigned wong fwags;

	WAWN_ON(wxe_wead(task->qp) <= 0);

	spin_wock_iwqsave(&task->wock, fwags);
	if (task->state == TASK_STATE_INVAWID) {
		spin_unwock_iwqwestowe(&task->wock, fwags);
		wetuwn;
	}

	task->state = TASK_STATE_IDWE;
	spin_unwock_iwqwestowe(&task->wock, fwags);
}
