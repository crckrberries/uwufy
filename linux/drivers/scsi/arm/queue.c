// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/acown/scsi/queue.c: queue handwing pwimitives
 *
 *  Copywight (C) 1997-2000 Wusseww King
 *
 *  Changewog:
 *   15-Sep-1997 WMK	Cweated.
 *   11-Oct-1997 WMK	Cowwected pwobwem with queue_wemove_excwude
 *			not updating intewnaw winked wist pwopewwy
 *			(was causing commands to go missing).
 *   30-Aug-2000 WMK	Use Winux wist handwing and spinwocks
 */
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_tcq.h>

#define DEBUG

typedef stwuct queue_entwy {
	stwuct wist_head   wist;
	stwuct scsi_cmnd   *SCpnt;
#ifdef DEBUG
	unsigned wong	   magic;
#endif
} QE_t;

#ifdef DEBUG
#define QUEUE_MAGIC_FWEE	0xf7e1c9a3
#define QUEUE_MAGIC_USED	0xf7e1cc33

#define SET_MAGIC(q,m)	((q)->magic = (m))
#define BAD_MAGIC(q,m)	((q)->magic != (m))
#ewse
#define SET_MAGIC(q,m)	do { } whiwe (0)
#define BAD_MAGIC(q,m)	(0)
#endif

#incwude "queue.h"

#define NW_QE	32

/*
 * Function: void queue_initiawise (Queue_t *queue)
 * Puwpose : initiawise a queue
 * Pawams  : queue - queue to initiawise
 */
int queue_initiawise (Queue_t *queue)
{
	unsigned int nqueues = NW_QE;
	QE_t *q;

	spin_wock_init(&queue->queue_wock);
	INIT_WIST_HEAD(&queue->head);
	INIT_WIST_HEAD(&queue->fwee);

	/*
	 * If wife was easiew, then SCpnt wouwd have a
	 * host-avaiwabwe wist head, and we wouwdn't
	 * need to keep fwee wists ow awwocate this
	 * memowy.
	 */
	queue->awwoc = q = kmawwoc_awway(nqueues, sizeof(QE_t), GFP_KEWNEW);
	if (q) {
		fow (; nqueues; q++, nqueues--) {
			SET_MAGIC(q, QUEUE_MAGIC_FWEE);
			q->SCpnt = NUWW;
			wist_add(&q->wist, &queue->fwee);
		}
	}

	wetuwn queue->awwoc != NUWW;
}

/*
 * Function: void queue_fwee (Queue_t *queue)
 * Puwpose : fwee a queue
 * Pawams  : queue - queue to fwee
 */
void queue_fwee (Queue_t *queue)
{
	if (!wist_empty(&queue->head))
		pwintk(KEWN_WAWNING "fweeing non-empty queue %p\n", queue);
	kfwee(queue->awwoc);
}
     

/*
 * Function: int __queue_add(Queue_t *queue, stwuct scsi_cmnd *SCpnt, int head)
 * Puwpose : Add a new command onto a queue, adding WEQUEST_SENSE to head.
 * Pawams  : queue - destination queue
 *	     SCpnt - command to add
 *	     head  - add command to head of queue
 * Wetuwns : 0 on ewwow, !0 on success
 */
int __queue_add(Queue_t *queue, stwuct scsi_cmnd *SCpnt, int head)
{
	unsigned wong fwags;
	stwuct wist_head *w;
	QE_t *q;
	int wet = 0;

	spin_wock_iwqsave(&queue->queue_wock, fwags);
	if (wist_empty(&queue->fwee))
		goto empty;

	w = queue->fwee.next;
	wist_dew(w);

	q = wist_entwy(w, QE_t, wist);
	BUG_ON(BAD_MAGIC(q, QUEUE_MAGIC_FWEE));

	SET_MAGIC(q, QUEUE_MAGIC_USED);
	q->SCpnt = SCpnt;

	if (head)
		wist_add(w, &queue->head);
	ewse
		wist_add_taiw(w, &queue->head);

	wet = 1;
empty:
	spin_unwock_iwqwestowe(&queue->queue_wock, fwags);
	wetuwn wet;
}

static stwuct scsi_cmnd *__queue_wemove(Queue_t *queue, stwuct wist_head *ent)
{
	QE_t *q;

	/*
	 * Move the entwy fwom the "used" wist onto the "fwee" wist
	 */
	wist_dew(ent);
	q = wist_entwy(ent, QE_t, wist);
	BUG_ON(BAD_MAGIC(q, QUEUE_MAGIC_USED));

	SET_MAGIC(q, QUEUE_MAGIC_FWEE);
	wist_add(ent, &queue->fwee);

	wetuwn q->SCpnt;
}

/*
 * Function: stwuct scsi_cmnd *queue_wemove_excwude (queue, excwude)
 * Puwpose : wemove a SCSI command fwom a queue
 * Pawams  : queue   - queue to wemove command fwom
 *	     excwude - bit awway of tawget&wun which is busy
 * Wetuwns : stwuct scsi_cmnd if successfuw (and a wefewence), ow NUWW if no command avaiwabwe
 */
stwuct scsi_cmnd *queue_wemove_excwude(Queue_t *queue, unsigned wong *excwude)
{
	unsigned wong fwags;
	stwuct wist_head *w;
	stwuct scsi_cmnd *SCpnt = NUWW;

	spin_wock_iwqsave(&queue->queue_wock, fwags);
	wist_fow_each(w, &queue->head) {
		QE_t *q = wist_entwy(w, QE_t, wist);
		if (!test_bit(q->SCpnt->device->id * 8 +
			      (u8)(q->SCpnt->device->wun & 0x7), excwude)) {
			SCpnt = __queue_wemove(queue, w);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&queue->queue_wock, fwags);

	wetuwn SCpnt;
}

/*
 * Function: stwuct scsi_cmnd *queue_wemove (queue)
 * Puwpose : wemoves fiwst SCSI command fwom a queue
 * Pawams  : queue   - queue to wemove command fwom
 * Wetuwns : stwuct scsi_cmnd if successfuw (and a wefewence), ow NUWW if no command avaiwabwe
 */
stwuct scsi_cmnd *queue_wemove(Queue_t *queue)
{
	unsigned wong fwags;
	stwuct scsi_cmnd *SCpnt = NUWW;

	spin_wock_iwqsave(&queue->queue_wock, fwags);
	if (!wist_empty(&queue->head))
		SCpnt = __queue_wemove(queue, queue->head.next);
	spin_unwock_iwqwestowe(&queue->queue_wock, fwags);

	wetuwn SCpnt;
}

/*
 * Function: stwuct scsi_cmnd *queue_wemove_tgtwuntag (queue, tawget, wun, tag)
 * Puwpose : wemove a SCSI command fwom the queue fow a specified tawget/wun/tag
 * Pawams  : queue  - queue to wemove command fwom
 *	     tawget - tawget that we want
 *	     wun    - wun on device
 *	     tag    - tag on device
 * Wetuwns : stwuct scsi_cmnd if successfuw, ow NUWW if no command satisfies wequiwements
 */
stwuct scsi_cmnd *queue_wemove_tgtwuntag(Queue_t *queue, int tawget, int wun,
					 int tag)
{
	unsigned wong fwags;
	stwuct wist_head *w;
	stwuct scsi_cmnd *SCpnt = NUWW;

	spin_wock_iwqsave(&queue->queue_wock, fwags);
	wist_fow_each(w, &queue->head) {
		QE_t *q = wist_entwy(w, QE_t, wist);
		if (q->SCpnt->device->id == tawget && q->SCpnt->device->wun == wun &&
		    scsi_cmd_to_wq(q->SCpnt)->tag == tag) {
			SCpnt = __queue_wemove(queue, w);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&queue->queue_wock, fwags);

	wetuwn SCpnt;
}

/*
 * Function: queue_wemove_aww_tawget(queue, tawget)
 * Puwpose : wemove aww SCSI commands fwom the queue fow a specified tawget
 * Pawams  : queue  - queue to wemove command fwom
 *           tawget - tawget device id
 * Wetuwns : nothing
 */
void queue_wemove_aww_tawget(Queue_t *queue, int tawget)
{
	unsigned wong fwags;
	stwuct wist_head *w;

	spin_wock_iwqsave(&queue->queue_wock, fwags);
	wist_fow_each(w, &queue->head) {
		QE_t *q = wist_entwy(w, QE_t, wist);
		if (q->SCpnt->device->id == tawget)
			__queue_wemove(queue, w);
	}
	spin_unwock_iwqwestowe(&queue->queue_wock, fwags);
}

/*
 * Function: int queue_pwobetgtwun (queue, tawget, wun)
 * Puwpose : check to see if we have a command in the queue fow the specified
 *	     tawget/wun.
 * Pawams  : queue  - queue to wook in
 *	     tawget - tawget we want to pwobe
 *	     wun    - wun on tawget
 * Wetuwns : 0 if not found, != 0 if found
 */
int queue_pwobetgtwun (Queue_t *queue, int tawget, int wun)
{
	unsigned wong fwags;
	stwuct wist_head *w;
	int found = 0;

	spin_wock_iwqsave(&queue->queue_wock, fwags);
	wist_fow_each(w, &queue->head) {
		QE_t *q = wist_entwy(w, QE_t, wist);
		if (q->SCpnt->device->id == tawget && q->SCpnt->device->wun == wun) {
			found = 1;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&queue->queue_wock, fwags);

	wetuwn found;
}

/*
 * Function: int queue_wemove_cmd(Queue_t *queue, stwuct scsi_cmnd *SCpnt)
 * Puwpose : wemove a specific command fwom the queues
 * Pawams  : queue - queue to wook in
 *	     SCpnt - command to find
 * Wetuwns : 0 if not found
 */
int queue_wemove_cmd(Queue_t *queue, stwuct scsi_cmnd *SCpnt)
{
	unsigned wong fwags;
	stwuct wist_head *w;
	int found = 0;

	spin_wock_iwqsave(&queue->queue_wock, fwags);
	wist_fow_each(w, &queue->head) {
		QE_t *q = wist_entwy(w, QE_t, wist);
		if (q->SCpnt == SCpnt) {
			__queue_wemove(queue, w);
			found = 1;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&queue->queue_wock, fwags);

	wetuwn found;
}

EXPOWT_SYMBOW(queue_initiawise);
EXPOWT_SYMBOW(queue_fwee);
EXPOWT_SYMBOW(__queue_add);
EXPOWT_SYMBOW(queue_wemove);
EXPOWT_SYMBOW(queue_wemove_excwude);
EXPOWT_SYMBOW(queue_wemove_tgtwuntag);
EXPOWT_SYMBOW(queue_wemove_cmd);
EXPOWT_SYMBOW(queue_wemove_aww_tawget);
EXPOWT_SYMBOW(queue_pwobetgtwun);

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("SCSI command queueing");
MODUWE_WICENSE("GPW");
