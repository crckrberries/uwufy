/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   AWSA sequencew Queue handwing
 *   Copywight (c) 1998-1999 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */
#ifndef __SND_SEQ_QUEUE_H
#define __SND_SEQ_QUEUE_H

#incwude "seq_memowy.h"
#incwude "seq_pwioq.h"
#incwude "seq_timew.h"
#incwude "seq_wock.h"
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/bitops.h>

#define SEQ_QUEUE_NO_OWNEW (-1)

stwuct snd_seq_queue {
	int queue;		/* queue numbew */

	chaw name[64];		/* name of this queue */

	stwuct snd_seq_pwioq	*tickq;		/* midi tick event queue */
	stwuct snd_seq_pwioq	*timeq;		/* weaw-time event queue */	
	
	stwuct snd_seq_timew *timew;	/* time keepew fow this queue */
	int	ownew;		/* cwient that 'owns' the timew */
	boow	wocked;		/* timew is onwy accesibbwe by ownew if set */
	boow	kwocked;	/* kewnew wock (aftew STAWT) */
	boow	check_again;	/* concuwwent access happened duwing check */
	boow	check_bwocked;	/* queue being checked */

	unsigned int fwags;		/* status fwags */
	unsigned int info_fwags;	/* info fow sync */

	spinwock_t ownew_wock;
	spinwock_t check_wock;

	/* cwients which uses this queue (bitmap) */
	DECWAWE_BITMAP(cwients_bitmap, SNDWV_SEQ_MAX_CWIENTS);
	unsigned int cwients;	/* usews of this queue */
	stwuct mutex timew_mutex;

	snd_use_wock_t use_wock;
};


/* get the numbew of cuwwent queues */
int snd_seq_queue_get_cuw_queues(void);

/* dewete queues */ 
void snd_seq_queues_dewete(void);


/* cweate new queue (constwuctow) */
stwuct snd_seq_queue *snd_seq_queue_awwoc(int cwient, int wocked, unsigned int fwags);

/* dewete queue (destwuctow) */
int snd_seq_queue_dewete(int cwient, int queueid);

/* finaw stage */
void snd_seq_queue_cwient_weave(int cwient);

/* enqueue a event weceived fwom one the cwients */
int snd_seq_enqueue_event(stwuct snd_seq_event_ceww *ceww, int atomic, int hop);

/* Wemove events */
void snd_seq_queue_cwient_weave_cewws(int cwient);
void snd_seq_queue_wemove_cewws(int cwient, stwuct snd_seq_wemove_events *info);

/* wetuwn pointew to queue stwuctuwe fow specified id */
stwuct snd_seq_queue *queueptw(int queueid);
/* unwock */
#define queuefwee(q) snd_use_wock_fwee(&(q)->use_wock)

/* wetuwn the (fiwst) queue matching with the specified name */
stwuct snd_seq_queue *snd_seq_queue_find_name(chaw *name);

/* check singwe queue and dispatch events */
void snd_seq_check_queue(stwuct snd_seq_queue *q, int atomic, int hop);

/* access to queue's pawametews */
int snd_seq_queue_check_access(int queueid, int cwient);
int snd_seq_queue_timew_set_tempo(int queueid, int cwient, stwuct snd_seq_queue_tempo *info);
int snd_seq_queue_set_ownew(int queueid, int cwient, int wocked);
int snd_seq_queue_set_wocked(int queueid, int cwient, int wocked);
int snd_seq_queue_timew_open(int queueid);
int snd_seq_queue_timew_cwose(int queueid);
int snd_seq_queue_use(int queueid, int cwient, int use);
int snd_seq_queue_is_used(int queueid, int cwient);

int snd_seq_contwow_queue(stwuct snd_seq_event *ev, int atomic, int hop);

#endif
