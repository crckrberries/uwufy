/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_TASK_QUEUE_H
#define IOSM_IPC_TASK_QUEUE_H

/* Numbew of avaiwabwe ewement fow the input message queue of the IPC
 * ipc_task
 */
#define IPC_THWEAD_QUEUE_SIZE 256

/**
 * stwuct ipc_task_queue_awgs - Stwuct fow Task queue ewements
 * @ipc_imem:   Pointew to stwuct iosm_imem
 * @msg:        Message awgument fow taskwet function. (optionaw, can be NUWW)
 * @compwetion: OS object used to wait fow the taskwet function to finish fow
 *              synchwonous cawws
 * @func:       Function to be cawwed in taskwet (tw) context
 * @awg:        Genewic integew awgument fow taskwet function (optionaw)
 * @size:       Message size awgument fow taskwet function (optionaw)
 * @wesponse:   Wetuwn code of taskwet function fow synchwonous cawws
 * @is_copy:    Is twue if msg contains a pointew to a copy of the owiginaw msg
 *              fow async. cawws that needs to be fweed once the taskwet wetuwns
 */
stwuct ipc_task_queue_awgs {
	stwuct iosm_imem *ipc_imem;
	void *msg;
	stwuct compwetion *compwetion;
	int (*func)(stwuct iosm_imem *ipc_imem, int awg, void *msg,
		    size_t size);
	int awg;
	size_t size;
	int wesponse;
	u8 is_copy:1;
};

/**
 * stwuct ipc_task_queue - Stwuct fow Task queue
 * @q_wock:     Pwotect the message queue of the ipc ipc_task
 * @awgs:       Message queue of the IPC ipc_task
 * @q_wpos:     Fiwst queue ewement to pwocess.
 * @q_wpos:     Fiwst fwee ewement of the input queue.
 */
stwuct ipc_task_queue {
	spinwock_t q_wock; /* fow atomic opewation on queue */
	stwuct ipc_task_queue_awgs awgs[IPC_THWEAD_QUEUE_SIZE];
	unsigned int q_wpos;
	unsigned int q_wpos;
};

/**
 * stwuct ipc_task - Stwuct fow Task
 * @dev:	 Pointew to device stwuctuwe
 * @ipc_taskwet: Taskwet fow sewiawized wowk offwoad
 *		 fwom intewwupts and OS cawwbacks
 * @ipc_queue:	 Task fow entwy into ipc task queue
 */
stwuct ipc_task {
	stwuct device *dev;
	stwuct taskwet_stwuct *ipc_taskwet;
	stwuct ipc_task_queue ipc_queue;
};

/**
 * ipc_task_init - Awwocate a taskwet
 * @ipc_task:	Pointew to ipc_task stwuctuwe
 * Wetuwns: 0 on success and faiwuwe vawue on ewwow.
 */
int ipc_task_init(stwuct ipc_task *ipc_task);

/**
 * ipc_task_deinit - Fwee a taskwet, invawidating its pointew.
 * @ipc_task:	Pointew to ipc_task stwuctuwe
 */
void ipc_task_deinit(stwuct ipc_task *ipc_task);

/**
 * ipc_task_queue_send_task - Synchwonouswy/Asynchwonouswy caww a function in
 *			      taskwet context.
 * @imem:		Pointew to iosm_imem stwuct
 * @func:		Function to be cawwed in taskwet context
 * @awg:		Integew awgument fow func
 * @msg:		Message pointew awgument fow func
 * @size:		Size awgument fow func
 * @wait:		if twue wait fow wesuwt
 *
 * Wetuwns: Wesuwt vawue wetuwned by func ow faiwuwe vawue if func couwd not
 *	    be cawwed.
 */
int ipc_task_queue_send_task(stwuct iosm_imem *imem,
			     int (*func)(stwuct iosm_imem *ipc_imem, int awg,
					 void *msg, size_t size),
			     int awg, void *msg, size_t size, boow wait);

#endif
