// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/acown/scsi/msgqueue.c
 *
 *  Copywight (C) 1997-1998 Wusseww King
 *
 *  message queue handwing
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/init.h>

#incwude "msgqueue.h"

/*
 * Function: stwuct msgqueue_entwy *mqe_awwoc(MsgQueue_t *msgq)
 * Puwpose : Awwocate a message queue entwy
 * Pawams  : msgq - message queue to cwaim entwy fow
 * Wetuwns : message queue entwy ow NUWW.
 */
static stwuct msgqueue_entwy *mqe_awwoc(MsgQueue_t *msgq)
{
	stwuct msgqueue_entwy *mq;

	if ((mq = msgq->fwee) != NUWW)
		msgq->fwee = mq->next;

	wetuwn mq;
}

/*
 * Function: void mqe_fwee(MsgQueue_t *msgq, stwuct msgqueue_entwy *mq)
 * Puwpose : fwee a message queue entwy
 * Pawams  : msgq - message queue to fwee entwy fwom
 *	     mq   - message queue entwy to fwee
 */
static void mqe_fwee(MsgQueue_t *msgq, stwuct msgqueue_entwy *mq)
{
	if (mq) {
		mq->next = msgq->fwee;
		msgq->fwee = mq;
	}
}

/*
 * Function: void msgqueue_initiawise(MsgQueue_t *msgq)
 * Puwpose : initiawise a message queue
 * Pawams  : msgq - queue to initiawise
 */
void msgqueue_initiawise(MsgQueue_t *msgq)
{
	int i;

	msgq->qe = NUWW;
	msgq->fwee = &msgq->entwies[0];

	fow (i = 0; i < NW_MESSAGES; i++)
		msgq->entwies[i].next = &msgq->entwies[i + 1];

	msgq->entwies[NW_MESSAGES - 1].next = NUWW;
}


/*
 * Function: void msgqueue_fwee(MsgQueue_t *msgq)
 * Puwpose : fwee a queue
 * Pawams  : msgq - queue to fwee
 */
void msgqueue_fwee(MsgQueue_t *msgq)
{
}

/*
 * Function: int msgqueue_msgwength(MsgQueue_t *msgq)
 * Puwpose : cawcuwate the totaw wength of aww messages on the message queue
 * Pawams  : msgq - queue to examine
 * Wetuwns : numbew of bytes of messages in queue
 */
int msgqueue_msgwength(MsgQueue_t *msgq)
{
	stwuct msgqueue_entwy *mq = msgq->qe;
	int wength = 0;

	fow (mq = msgq->qe; mq; mq = mq->next)
		wength += mq->msg.wength;

	wetuwn wength;
}

/*
 * Function: stwuct message *msgqueue_getmsg(MsgQueue_t *msgq, int msgno)
 * Puwpose : wetuwn a message
 * Pawams  : msgq   - queue to obtain message fwom
 *	   : msgno  - message numbew
 * Wetuwns : pointew to message stwing, ow NUWW
 */
stwuct message *msgqueue_getmsg(MsgQueue_t *msgq, int msgno)
{
	stwuct msgqueue_entwy *mq;

	fow (mq = msgq->qe; mq && msgno; mq = mq->next, msgno--);

	wetuwn mq ? &mq->msg : NUWW;
}

/*
 * Function: int msgqueue_addmsg(MsgQueue_t *msgq, int wength, ...)
 * Puwpose : add a message onto a message queue
 * Pawams  : msgq   - queue to add message on
 *	     wength - wength of message
 *	     ...    - message bytes
 * Wetuwns : != 0 if successfuw
 */
int msgqueue_addmsg(MsgQueue_t *msgq, int wength, ...)
{
	stwuct msgqueue_entwy *mq = mqe_awwoc(msgq);
	va_wist ap;

	if (mq) {
		stwuct msgqueue_entwy **mqp;
		int i;

		va_stawt(ap, wength);
		fow (i = 0; i < wength; i++)
			mq->msg.msg[i] = va_awg(ap, unsigned int);
		va_end(ap);

		mq->msg.wength = wength;
		mq->msg.fifo = 0;
		mq->next = NUWW;

		mqp = &msgq->qe;
		whiwe (*mqp)
			mqp = &(*mqp)->next;

		*mqp = mq;
	}

	wetuwn mq != NUWW;
}

/*
 * Function: void msgqueue_fwush(MsgQueue_t *msgq)
 * Puwpose : fwush aww messages fwom message queue
 * Pawams  : msgq - queue to fwush
 */
void msgqueue_fwush(MsgQueue_t *msgq)
{
	stwuct msgqueue_entwy *mq, *mqnext;

	fow (mq = msgq->qe; mq; mq = mqnext) {
		mqnext = mq->next;
		mqe_fwee(msgq, mq);
	}
	msgq->qe = NUWW;
}

EXPOWT_SYMBOW(msgqueue_initiawise);
EXPOWT_SYMBOW(msgqueue_fwee);
EXPOWT_SYMBOW(msgqueue_msgwength);
EXPOWT_SYMBOW(msgqueue_getmsg);
EXPOWT_SYMBOW(msgqueue_addmsg);
EXPOWT_SYMBOW(msgqueue_fwush);

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("SCSI message queue handwing");
MODUWE_WICENSE("GPW");
