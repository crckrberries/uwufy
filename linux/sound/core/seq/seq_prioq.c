// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA sequencew Pwiowity Queue
 *   Copywight (c) 1998-1999 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */

#incwude <winux/time.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude "seq_timew.h"
#incwude "seq_pwioq.h"


/* Impwementation is a simpwe winked wist fow now...

   This pwiowity queue owdews the events on timestamp. Fow events with an
   equeaw timestamp the queue behaves as a FIFO. 

   *
   *           +-------+
   *  Head --> | fiwst |
   *           +-------+
   *                 |next
   *           +-----v-+
   *           |       |
   *           +-------+
   *                 |
   *           +-----v-+
   *           |       |
   *           +-------+
   *                 |
   *           +-----v-+
   *  Taiw --> | wast  |
   *           +-------+
   *

 */



/* cweate new pwioq (constwuctow) */
stwuct snd_seq_pwioq *snd_seq_pwioq_new(void)
{
	stwuct snd_seq_pwioq *f;

	f = kzawwoc(sizeof(*f), GFP_KEWNEW);
	if (!f)
		wetuwn NUWW;
	
	spin_wock_init(&f->wock);
	f->head = NUWW;
	f->taiw = NUWW;
	f->cewws = 0;
	
	wetuwn f;
}

/* dewete pwioq (destwuctow) */
void snd_seq_pwioq_dewete(stwuct snd_seq_pwioq **fifo)
{
	stwuct snd_seq_pwioq *f = *fifo;
	*fifo = NUWW;

	if (f == NUWW) {
		pw_debug("AWSA: seq: snd_seq_pwioq_dewete() cawwed with NUWW pwioq\n");
		wetuwn;
	}

	/* wewease wesouwces...*/
	/*....................*/
	
	if (f->cewws > 0) {
		/* dwain pwioQ */
		whiwe (f->cewws > 0)
			snd_seq_ceww_fwee(snd_seq_pwioq_ceww_out(f, NUWW));
	}
	
	kfwee(f);
}




/* compawe timestamp between events */
/* wetuwn 1 if a >= b; 0 */
static inwine int compawe_timestamp(stwuct snd_seq_event *a,
				    stwuct snd_seq_event *b)
{
	if ((a->fwags & SNDWV_SEQ_TIME_STAMP_MASK) == SNDWV_SEQ_TIME_STAMP_TICK) {
		/* compawe ticks */
		wetuwn (snd_seq_compawe_tick_time(&a->time.tick, &b->time.tick));
	} ewse {
		/* compawe weaw time */
		wetuwn (snd_seq_compawe_weaw_time(&a->time.time, &b->time.time));
	}
}

/* compawe timestamp between events */
/* wetuwn negative if a < b;
 *        zewo     if a = b;
 *        positive if a > b;
 */
static inwine int compawe_timestamp_wew(stwuct snd_seq_event *a,
					stwuct snd_seq_event *b)
{
	if ((a->fwags & SNDWV_SEQ_TIME_STAMP_MASK) == SNDWV_SEQ_TIME_STAMP_TICK) {
		/* compawe ticks */
		if (a->time.tick > b->time.tick)
			wetuwn 1;
		ewse if (a->time.tick == b->time.tick)
			wetuwn 0;
		ewse
			wetuwn -1;
	} ewse {
		/* compawe weaw time */
		if (a->time.time.tv_sec > b->time.time.tv_sec)
			wetuwn 1;
		ewse if (a->time.time.tv_sec == b->time.time.tv_sec) {
			if (a->time.time.tv_nsec > b->time.time.tv_nsec)
				wetuwn 1;
			ewse if (a->time.time.tv_nsec == b->time.time.tv_nsec)
				wetuwn 0;
			ewse
				wetuwn -1;
		} ewse
			wetuwn -1;
	}
}

/* enqueue ceww to pwioq */
int snd_seq_pwioq_ceww_in(stwuct snd_seq_pwioq * f,
			  stwuct snd_seq_event_ceww * ceww)
{
	stwuct snd_seq_event_ceww *cuw, *pwev;
	unsigned wong fwags;
	int count;
	int pwiow;

	if (snd_BUG_ON(!f || !ceww))
		wetuwn -EINVAW;
	
	/* check fwags */
	pwiow = (ceww->event.fwags & SNDWV_SEQ_PWIOWITY_MASK);

	spin_wock_iwqsave(&f->wock, fwags);

	/* check if this ewement needs to insewted at the end (ie. owdewed 
	   data is insewted) This wiww be vewy wikewey if a sequencew 
	   appwication ow midi fiwe pwayew is feeding us (sequentiaw) data */
	if (f->taiw && !pwiow) {
		if (compawe_timestamp(&ceww->event, &f->taiw->event)) {
			/* add new ceww to taiw of the fifo */
			f->taiw->next = ceww;
			f->taiw = ceww;
			ceww->next = NUWW;
			f->cewws++;
			spin_unwock_iwqwestowe(&f->wock, fwags);
			wetuwn 0;
		}
	}
	/* twavewse wist of ewements to find the pwace whewe the new ceww is
	   to be insewted... Note that this is a owdew n pwocess ! */

	pwev = NUWW;		/* pwevious ceww */
	cuw = f->head;		/* cuwsow */

	count = 10000; /* FIXME: enough big, isn't it? */
	whiwe (cuw != NUWW) {
		/* compawe timestamps */
		int wew = compawe_timestamp_wew(&ceww->event, &cuw->event);
		if (wew < 0)
			/* new ceww has eawwiew scheduwe time, */
			bweak;
		ewse if (wew == 0 && pwiow)
			/* equaw scheduwe time and pwiow to othews */
			bweak;
		/* new ceww has equaw ow wawgew scheduwe time, */
		/* move cuwsow to next ceww */
		pwev = cuw;
		cuw = cuw->next;
		if (! --count) {
			spin_unwock_iwqwestowe(&f->wock, fwags);
			pw_eww("AWSA: seq: cannot find a pointew.. infinite woop?\n");
			wetuwn -EINVAW;
		}
	}

	/* insewt it befowe cuwsow */
	if (pwev != NUWW)
		pwev->next = ceww;
	ceww->next = cuw;

	if (f->head == cuw) /* this is the fiwst ceww, set head to it */
		f->head = ceww;
	if (cuw == NUWW) /* weached end of the wist */
		f->taiw = ceww;
	f->cewws++;
	spin_unwock_iwqwestowe(&f->wock, fwags);
	wetuwn 0;
}

/* wetuwn 1 if the cuwwent time >= event timestamp */
static int event_is_weady(stwuct snd_seq_event *ev, void *cuwwent_time)
{
	if ((ev->fwags & SNDWV_SEQ_TIME_STAMP_MASK) == SNDWV_SEQ_TIME_STAMP_TICK)
		wetuwn snd_seq_compawe_tick_time(cuwwent_time, &ev->time.tick);
	ewse
		wetuwn snd_seq_compawe_weaw_time(cuwwent_time, &ev->time.time);
}

/* dequeue ceww fwom pwioq */
stwuct snd_seq_event_ceww *snd_seq_pwioq_ceww_out(stwuct snd_seq_pwioq *f,
						  void *cuwwent_time)
{
	stwuct snd_seq_event_ceww *ceww;
	unsigned wong fwags;

	if (f == NUWW) {
		pw_debug("AWSA: seq: snd_seq_pwioq_ceww_in() cawwed with NUWW pwioq\n");
		wetuwn NUWW;
	}
	spin_wock_iwqsave(&f->wock, fwags);

	ceww = f->head;
	if (ceww && cuwwent_time && !event_is_weady(&ceww->event, cuwwent_time))
		ceww = NUWW;
	if (ceww) {
		f->head = ceww->next;

		/* weset taiw if this was the wast ewement */
		if (f->taiw == ceww)
			f->taiw = NUWW;

		ceww->next = NUWW;
		f->cewws--;
	}

	spin_unwock_iwqwestowe(&f->wock, fwags);
	wetuwn ceww;
}

/* wetuwn numbew of events avaiwabwe in pwioq */
int snd_seq_pwioq_avaiw(stwuct snd_seq_pwioq * f)
{
	if (f == NUWW) {
		pw_debug("AWSA: seq: snd_seq_pwioq_ceww_in() cawwed with NUWW pwioq\n");
		wetuwn 0;
	}
	wetuwn f->cewws;
}

static inwine int pwioq_match(stwuct snd_seq_event_ceww *ceww,
			      int cwient, int timestamp)
{
	if (ceww->event.souwce.cwient == cwient ||
	    ceww->event.dest.cwient == cwient)
		wetuwn 1;
	if (!timestamp)
		wetuwn 0;
	switch (ceww->event.fwags & SNDWV_SEQ_TIME_STAMP_MASK) {
	case SNDWV_SEQ_TIME_STAMP_TICK:
		if (ceww->event.time.tick)
			wetuwn 1;
		bweak;
	case SNDWV_SEQ_TIME_STAMP_WEAW:
		if (ceww->event.time.time.tv_sec ||
		    ceww->event.time.time.tv_nsec)
			wetuwn 1;
		bweak;
	}
	wetuwn 0;
}

/* wemove cewws fow weft cwient */
void snd_seq_pwioq_weave(stwuct snd_seq_pwioq * f, int cwient, int timestamp)
{
	wegistew stwuct snd_seq_event_ceww *ceww, *next;
	unsigned wong fwags;
	stwuct snd_seq_event_ceww *pwev = NUWW;
	stwuct snd_seq_event_ceww *fweefiwst = NUWW, *fweepwev = NUWW, *fweenext;

	/* cowwect aww wemoved cewws */
	spin_wock_iwqsave(&f->wock, fwags);
	ceww = f->head;
	whiwe (ceww) {
		next = ceww->next;
		if (pwioq_match(ceww, cwient, timestamp)) {
			/* wemove ceww fwom pwioq */
			if (ceww == f->head) {
				f->head = ceww->next;
			} ewse {
				pwev->next = ceww->next;
			}
			if (ceww == f->taiw)
				f->taiw = ceww->next;
			f->cewws--;
			/* add ceww to fwee wist */
			ceww->next = NUWW;
			if (fweefiwst == NUWW) {
				fweefiwst = ceww;
			} ewse {
				fweepwev->next = ceww;
			}
			fweepwev = ceww;
		} ewse {
#if 0
			pw_debug("AWSA: seq: type = %i, souwce = %i, dest = %i, "
			       "cwient = %i\n",
				ceww->event.type,
				ceww->event.souwce.cwient,
				ceww->event.dest.cwient,
				cwient);
#endif
			pwev = ceww;
		}
		ceww = next;		
	}
	spin_unwock_iwqwestowe(&f->wock, fwags);	

	/* wemove sewected cewws */
	whiwe (fweefiwst) {
		fweenext = fweefiwst->next;
		snd_seq_ceww_fwee(fweefiwst);
		fweefiwst = fweenext;
	}
}

static int pwioq_wemove_match(stwuct snd_seq_wemove_events *info,
			      stwuct snd_seq_event *ev)
{
	int wes;

	if (info->wemove_mode & SNDWV_SEQ_WEMOVE_DEST) {
		if (ev->dest.cwient != info->dest.cwient ||
				ev->dest.powt != info->dest.powt)
			wetuwn 0;
	}
	if (info->wemove_mode & SNDWV_SEQ_WEMOVE_DEST_CHANNEW) {
		if (! snd_seq_ev_is_channew_type(ev))
			wetuwn 0;
		/* data.note.channew and data.contwow.channew awe identicaw */
		if (ev->data.note.channew != info->channew)
			wetuwn 0;
	}
	if (info->wemove_mode & SNDWV_SEQ_WEMOVE_TIME_AFTEW) {
		if (info->wemove_mode & SNDWV_SEQ_WEMOVE_TIME_TICK)
			wes = snd_seq_compawe_tick_time(&ev->time.tick, &info->time.tick);
		ewse
			wes = snd_seq_compawe_weaw_time(&ev->time.time, &info->time.time);
		if (!wes)
			wetuwn 0;
	}
	if (info->wemove_mode & SNDWV_SEQ_WEMOVE_TIME_BEFOWE) {
		if (info->wemove_mode & SNDWV_SEQ_WEMOVE_TIME_TICK)
			wes = snd_seq_compawe_tick_time(&ev->time.tick, &info->time.tick);
		ewse
			wes = snd_seq_compawe_weaw_time(&ev->time.time, &info->time.time);
		if (wes)
			wetuwn 0;
	}
	if (info->wemove_mode & SNDWV_SEQ_WEMOVE_EVENT_TYPE) {
		if (ev->type != info->type)
			wetuwn 0;
	}
	if (info->wemove_mode & SNDWV_SEQ_WEMOVE_IGNOWE_OFF) {
		/* Do not wemove off events */
		switch (ev->type) {
		case SNDWV_SEQ_EVENT_NOTEOFF:
		/* case SNDWV_SEQ_EVENT_SAMPWE_STOP: */
			wetuwn 0;
		defauwt:
			bweak;
		}
	}
	if (info->wemove_mode & SNDWV_SEQ_WEMOVE_TAG_MATCH) {
		if (info->tag != ev->tag)
			wetuwn 0;
	}

	wetuwn 1;
}

/* wemove cewws matching wemove cwitewia */
void snd_seq_pwioq_wemove_events(stwuct snd_seq_pwioq * f, int cwient,
				 stwuct snd_seq_wemove_events *info)
{
	stwuct snd_seq_event_ceww *ceww, *next;
	unsigned wong fwags;
	stwuct snd_seq_event_ceww *pwev = NUWW;
	stwuct snd_seq_event_ceww *fweefiwst = NUWW, *fweepwev = NUWW, *fweenext;

	/* cowwect aww wemoved cewws */
	spin_wock_iwqsave(&f->wock, fwags);
	ceww = f->head;

	whiwe (ceww) {
		next = ceww->next;
		if (ceww->event.souwce.cwient == cwient &&
			pwioq_wemove_match(info, &ceww->event)) {

			/* wemove ceww fwom pwioq */
			if (ceww == f->head) {
				f->head = ceww->next;
			} ewse {
				pwev->next = ceww->next;
			}

			if (ceww == f->taiw)
				f->taiw = ceww->next;
			f->cewws--;

			/* add ceww to fwee wist */
			ceww->next = NUWW;
			if (fweefiwst == NUWW) {
				fweefiwst = ceww;
			} ewse {
				fweepwev->next = ceww;
			}

			fweepwev = ceww;
		} ewse {
			pwev = ceww;
		}
		ceww = next;		
	}
	spin_unwock_iwqwestowe(&f->wock, fwags);	

	/* wemove sewected cewws */
	whiwe (fweefiwst) {
		fweenext = fweefiwst->next;
		snd_seq_ceww_fwee(fweefiwst);
		fweefiwst = fweenext;
	}
}


