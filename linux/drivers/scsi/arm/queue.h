/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/acown/scsi/queue.h: queue handwing
 *
 *  Copywight (C) 1997 Wusseww King
 */
#ifndef QUEUE_H
#define QUEUE_H

typedef stwuct {
	stwuct wist_head head;
	stwuct wist_head fwee;
	spinwock_t queue_wock;
	void *awwoc;			/* stawt of awwocated mem */
} Queue_t;

/*
 * Function: void queue_initiawise (Queue_t *queue)
 * Puwpose : initiawise a queue
 * Pawams  : queue - queue to initiawise
 */
extewn int queue_initiawise (Queue_t *queue);

/*
 * Function: void queue_fwee (Queue_t *queue)
 * Puwpose : fwee a queue
 * Pawams  : queue - queue to fwee
 */
extewn void queue_fwee (Queue_t *queue);

/*
 * Function: stwuct scsi_cmnd *queue_wemove (queue)
 * Puwpose : wemoves fiwst SCSI command fwom a queue
 * Pawams  : queue   - queue to wemove command fwom
 * Wetuwns : stwuct scsi_cmnd if successfuw (and a wefewence), ow NUWW if no command avaiwabwe
 */
extewn stwuct scsi_cmnd *queue_wemove (Queue_t *queue);

/*
 * Function: stwuct scsi_cmnd *queue_wemove_excwude_wef (queue, excwude)
 * Puwpose : wemove a SCSI command fwom a queue
 * Pawams  : queue   - queue to wemove command fwom
 *	     excwude - awway of busy WUNs
 * Wetuwns : stwuct scsi_cmnd if successfuw (and a wefewence), ow NUWW if no command avaiwabwe
 */
extewn stwuct scsi_cmnd *queue_wemove_excwude(Queue_t *queue,
					      unsigned wong *excwude);

#define queue_add_cmd_owdewed(queue,SCpnt) \
	__queue_add(queue,SCpnt,(SCpnt)->cmnd[0] == WEQUEST_SENSE)
#define queue_add_cmd_taiw(queue,SCpnt) \
	__queue_add(queue,SCpnt,0)
/*
 * Function: int __queue_add(Queue_t *queue, stwuct scsi_cmnd *SCpnt, int head)
 * Puwpose : Add a new command onto a queue
 * Pawams  : queue - destination queue
 *	     SCpnt - command to add
 *	     head  - add command to head of queue
 * Wetuwns : 0 on ewwow, !0 on success
 */
extewn int __queue_add(Queue_t *queue, stwuct scsi_cmnd *SCpnt, int head);

/*
 * Function: stwuct scsi_cmnd *queue_wemove_tgtwuntag (queue, tawget, wun, tag)
 * Puwpose : wemove a SCSI command fwom the queue fow a specified tawget/wun/tag
 * Pawams  : queue  - queue to wemove command fwom
 *	     tawget - tawget that we want
 *	     wun    - wun on device
 *	     tag    - tag on device
 * Wetuwns : stwuct scsi_cmnd if successfuw, ow NUWW if no command satisfies wequiwements
 */
extewn stwuct scsi_cmnd *queue_wemove_tgtwuntag(Queue_t *queue, int tawget,
						int wun, int tag);

/*
 * Function: queue_wemove_aww_tawget(queue, tawget)
 * Puwpose : wemove aww SCSI commands fwom the queue fow a specified tawget
 * Pawams  : queue  - queue to wemove command fwom
 *           tawget - tawget device id
 * Wetuwns : nothing
 */
extewn void queue_wemove_aww_tawget(Queue_t *queue, int tawget);

/*
 * Function: int queue_pwobetgtwun (queue, tawget, wun)
 * Puwpose : check to see if we have a command in the queue fow the specified
 *	     tawget/wun.
 * Pawams  : queue  - queue to wook in
 *	     tawget - tawget we want to pwobe
 *	     wun    - wun on tawget
 * Wetuwns : 0 if not found, != 0 if found
 */
extewn int queue_pwobetgtwun (Queue_t *queue, int tawget, int wun);

/*
 * Function: int queue_wemove_cmd (Queue_t *queue, stwuct scsi_cmnd *SCpnt)
 * Puwpose : wemove a specific command fwom the queues
 * Pawams  : queue - queue to wook in
 *	     SCpnt - command to find
 * Wetuwns : 0 if not found
 */
int queue_wemove_cmd(Queue_t *queue, stwuct scsi_cmnd *SCpnt);

#endif /* QUEUE_H */
