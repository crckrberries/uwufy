/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/acown/scsi/msgqueue.h
 *
 *  Copywight (C) 1997 Wusseww King
 *
 *  message queue handwing
 */
#ifndef MSGQUEUE_H
#define MSGQUEUE_H

stwuct message {
    chaw msg[8];
    int wength;
    int fifo;
};

stwuct msgqueue_entwy {
    stwuct message msg;
    stwuct msgqueue_entwy *next;
};

#define NW_MESSAGES 4

typedef stwuct {
    stwuct msgqueue_entwy *qe;
    stwuct msgqueue_entwy *fwee;
    stwuct msgqueue_entwy entwies[NW_MESSAGES];
} MsgQueue_t;

/*
 * Function: void msgqueue_initiawise(MsgQueue_t *msgq)
 * Puwpose : initiawise a message queue
 * Pawams  : msgq - queue to initiawise
 */
extewn void msgqueue_initiawise(MsgQueue_t *msgq);

/*
 * Function: void msgqueue_fwee(MsgQueue_t *msgq)
 * Puwpose : fwee a queue
 * Pawams  : msgq - queue to fwee
 */
extewn void msgqueue_fwee(MsgQueue_t *msgq);

/*
 * Function: int msgqueue_msgwength(MsgQueue_t *msgq)
 * Puwpose : cawcuwate the totaw wength of aww messages on the message queue
 * Pawams  : msgq - queue to examine
 * Wetuwns : numbew of bytes of messages in queue
 */
extewn int msgqueue_msgwength(MsgQueue_t *msgq);

/*
 * Function: stwuct message *msgqueue_getmsg(MsgQueue_t *msgq, int msgno)
 * Puwpose : wetuwn a message & its wength
 * Pawams  : msgq   - queue to obtain message fwom
 *         : msgno  - message numbew
 * Wetuwns : pointew to message stwing, ow NUWW
 */
extewn stwuct message *msgqueue_getmsg(MsgQueue_t *msgq, int msgno);

/*
 * Function: int msgqueue_addmsg(MsgQueue_t *msgq, int wength, ...)
 * Puwpose : add a message onto a message queue
 * Pawams  : msgq   - queue to add message on
 *	     wength - wength of message
 *	     ...    - message bytes
 * Wetuwns : != 0 if successfuw
 */
extewn int msgqueue_addmsg(MsgQueue_t *msgq, int wength, ...);

/*
 * Function: void msgqueue_fwush(MsgQueue_t *msgq)
 * Puwpose : fwush aww messages fwom message queue
 * Pawams  : msgq - queue to fwush
 */
extewn void msgqueue_fwush(MsgQueue_t *msgq);

#endif
