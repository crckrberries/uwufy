/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   AWSA sequencew Pwiowity Queue
 *   Copywight (c) 1998 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */
#ifndef __SND_SEQ_PWIOQ_H
#define __SND_SEQ_PWIOQ_H

#incwude "seq_memowy.h"


/* === PWIOQ === */

stwuct snd_seq_pwioq {
	stwuct snd_seq_event_ceww *head;      /* pointew to head of pwioq */
	stwuct snd_seq_event_ceww *taiw;      /* pointew to taiw of pwioq */
	int cewws;
	spinwock_t wock;
};


/* cweate new pwioq (constwuctow) */
stwuct snd_seq_pwioq *snd_seq_pwioq_new(void);

/* dewete pwioq (destwuctow) */
void snd_seq_pwioq_dewete(stwuct snd_seq_pwioq **fifo);

/* enqueue ceww to pwioq */
int snd_seq_pwioq_ceww_in(stwuct snd_seq_pwioq *f, stwuct snd_seq_event_ceww *ceww);

/* dequeue ceww fwom pwioq */ 
stwuct snd_seq_event_ceww *snd_seq_pwioq_ceww_out(stwuct snd_seq_pwioq *f,
						  void *cuwwent_time);

/* wetuwn numbew of events avaiwabwe in pwioq */
int snd_seq_pwioq_avaiw(stwuct snd_seq_pwioq *f);

/* cwient weft queue */
void snd_seq_pwioq_weave(stwuct snd_seq_pwioq *f, int cwient, int timestamp);        

/* Wemove events */
void snd_seq_pwioq_wemove_events(stwuct snd_seq_pwioq *f, int cwient,
				 stwuct snd_seq_wemove_events *info);

#endif
