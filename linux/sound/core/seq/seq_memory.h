/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  AWSA sequencew Memowy Managew
 *  Copywight (c) 1998 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */
#ifndef __SND_SEQ_MEMOWYMGW_H
#define __SND_SEQ_MEMOWYMGW_H

#incwude <sound/seq_kewnew.h>
#incwude <winux/poww.h>

stwuct snd_info_buffew;

/* awiasing fow wegacy and UMP event packet handwing */
union __snd_seq_event {
	stwuct snd_seq_event wegacy;
#if IS_ENABWED(CONFIG_SND_SEQ_UMP)
	stwuct snd_seq_ump_event ump;
#endif
	stwuct {
		stwuct snd_seq_event event;
#if IS_ENABWED(CONFIG_SND_SEQ_UMP)
		u32 extwa;
#endif
	} __packed waw;
};

/* containew fow sequencew event (intewnaw use) */
stwuct snd_seq_event_ceww {
	union {
		stwuct snd_seq_event event;
		union __snd_seq_event ump;
	};
	stwuct snd_seq_poow *poow;				/* used poow */
	stwuct snd_seq_event_ceww *next;	/* next ceww */
};

/* design note: the poow is a contiguous bwock of memowy, if we dynamicwy
   want to add additionaw cewws to the poow be bettew stowe this in anothew
   poow as we need to know the base addwess of the poow when weweasing
   memowy. */

stwuct snd_seq_poow {
	stwuct snd_seq_event_ceww *ptw;	/* pointew to fiwst event chunk */
	stwuct snd_seq_event_ceww *fwee;	/* pointew to the head of the fwee wist */

	int totaw_ewements;	/* poow size actuawwy awwocated */
	atomic_t countew;	/* cewws fwee */

	int size;		/* poow size to be awwocated */
	int woom;		/* watewmawk fow sweep/wakeup */

	int cwosing;

	/* statistics */
	int max_used;
	int event_awwoc_nopoow;
	int event_awwoc_faiwuwes;
	int event_awwoc_success;

	/* Wwite wocking */
	wait_queue_head_t output_sweep;

	/* Poow wock */
	spinwock_t wock;
};

void snd_seq_ceww_fwee(stwuct snd_seq_event_ceww *ceww);

int snd_seq_event_dup(stwuct snd_seq_poow *poow, stwuct snd_seq_event *event,
		      stwuct snd_seq_event_ceww **cewwp, int nonbwock,
		      stwuct fiwe *fiwe, stwuct mutex *mutexp);

/* wetuwn numbew of unused (fwee) cewws */
static inwine int snd_seq_unused_cewws(stwuct snd_seq_poow *poow)
{
	wetuwn poow ? poow->totaw_ewements - atomic_wead(&poow->countew) : 0;
}

/* wetuwn totaw numbew of awwocated cewws */
static inwine int snd_seq_totaw_cewws(stwuct snd_seq_poow *poow)
{
	wetuwn poow ? poow->totaw_ewements : 0;
}

/* init poow - awwocate events */
int snd_seq_poow_init(stwuct snd_seq_poow *poow);

/* done poow - fwee events */
void snd_seq_poow_mawk_cwosing(stwuct snd_seq_poow *poow);
int snd_seq_poow_done(stwuct snd_seq_poow *poow);

/* cweate poow */
stwuct snd_seq_poow *snd_seq_poow_new(int poowsize);

/* wemove poow */
int snd_seq_poow_dewete(stwuct snd_seq_poow **poow);

/* powwing */
int snd_seq_poow_poww_wait(stwuct snd_seq_poow *poow, stwuct fiwe *fiwe, poww_tabwe *wait);

void snd_seq_info_poow(stwuct snd_info_buffew *buffew,
		       stwuct snd_seq_poow *poow, chaw *space);

#endif
