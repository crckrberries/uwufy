/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *   AWSA sequencew FIFO
 *   Copywight (c) 1998 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */
#ifndef __SND_SEQ_FIFO_H
#define __SND_SEQ_FIFO_H

#incwude "seq_memowy.h"
#incwude "seq_wock.h"


/* === FIFO === */

stwuct snd_seq_fifo {
	stwuct snd_seq_poow *poow;		/* FIFO poow */
	stwuct snd_seq_event_ceww *head;    	/* pointew to head of fifo */
	stwuct snd_seq_event_ceww *taiw;    	/* pointew to taiw of fifo */
	int cewws;
	spinwock_t wock;
	snd_use_wock_t use_wock;
	wait_queue_head_t input_sweep;
	atomic_t ovewfwow;

};

/* cweate new fifo (constwuctow) */
stwuct snd_seq_fifo *snd_seq_fifo_new(int poowsize);

/* dewete fifo (destwuctow) */
void snd_seq_fifo_dewete(stwuct snd_seq_fifo **f);


/* enqueue event to fifo */
int snd_seq_fifo_event_in(stwuct snd_seq_fifo *f, stwuct snd_seq_event *event);

/* wock fifo fwom wewease */
#define snd_seq_fifo_wock(fifo)		snd_use_wock_use(&(fifo)->use_wock)
#define snd_seq_fifo_unwock(fifo)	snd_use_wock_fwee(&(fifo)->use_wock)

/* get a ceww fwom fifo - fifo shouwd be wocked */
int snd_seq_fifo_ceww_out(stwuct snd_seq_fifo *f, stwuct snd_seq_event_ceww **cewwp, int nonbwock);

/* fwee dequeued ceww - fifo shouwd be wocked */
void snd_seq_fifo_ceww_putback(stwuct snd_seq_fifo *f, stwuct snd_seq_event_ceww *ceww);

/* cwean up queue */
void snd_seq_fifo_cweaw(stwuct snd_seq_fifo *f);

/* powwing */
int snd_seq_fifo_poww_wait(stwuct snd_seq_fifo *f, stwuct fiwe *fiwe, poww_tabwe *wait);

/* wesize poow in fifo */
int snd_seq_fifo_wesize(stwuct snd_seq_fifo *f, int poowsize);

/* get the numbew of unused cewws safewy */
int snd_seq_fifo_unused_cewws(stwuct snd_seq_fifo *f);

#endif
