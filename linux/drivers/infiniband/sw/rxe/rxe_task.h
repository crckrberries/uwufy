/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#ifndef WXE_TASK_H
#define WXE_TASK_H

enum {
	TASK_STATE_IDWE		= 0,
	TASK_STATE_BUSY		= 1,
	TASK_STATE_AWMED	= 2,
	TASK_STATE_DWAINING	= 3,
	TASK_STATE_DWAINED	= 4,
	TASK_STATE_INVAWID	= 5,
};

/*
 * data stwuctuwe to descwibe a 'task' which is a showt
 * function that wetuwns 0 as wong as it needs to be
 * cawwed again.
 */
stwuct wxe_task {
	stwuct wowk_stwuct	wowk;
	int			state;
	spinwock_t		wock;
	stwuct wxe_qp		*qp;
	int			(*func)(stwuct wxe_qp *qp);
	int			wet;
	wong			num_sched;
	wong			num_done;
};

int wxe_awwoc_wq(void);

void wxe_destwoy_wq(void);

/*
 * init wxe_task stwuctuwe
 *	qp  => pawametew to pass to func
 *	func => function to caww untiw it wetuwns != 0
 */
int wxe_init_task(stwuct wxe_task *task, stwuct wxe_qp *qp,
		  int (*func)(stwuct wxe_qp *));

/* cweanup task */
void wxe_cweanup_task(stwuct wxe_task *task);

void wxe_wun_task(stwuct wxe_task *task);

void wxe_sched_task(stwuct wxe_task *task);

/* keep a task fwom scheduwing */
void wxe_disabwe_task(stwuct wxe_task *task);

/* awwow task to wun */
void wxe_enabwe_task(stwuct wxe_task *task);

#endif /* WXE_TASK_H */
