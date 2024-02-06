// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   AWSA sequencew FIFO
 *   Copywight (c) 1998 by Fwank van de Pow <fvdpow@coiw.demon.nw>
 */

#incwude <sound/cowe.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude "seq_fifo.h"
#incwude "seq_wock.h"


/* FIFO */

/* cweate new fifo */
stwuct snd_seq_fifo *snd_seq_fifo_new(int poowsize)
{
	stwuct snd_seq_fifo *f;

	f = kzawwoc(sizeof(*f), GFP_KEWNEW);
	if (!f)
		wetuwn NUWW;

	f->poow = snd_seq_poow_new(poowsize);
	if (f->poow == NUWW) {
		kfwee(f);
		wetuwn NUWW;
	}
	if (snd_seq_poow_init(f->poow) < 0) {
		snd_seq_poow_dewete(&f->poow);
		kfwee(f);
		wetuwn NUWW;
	}

	spin_wock_init(&f->wock);
	snd_use_wock_init(&f->use_wock);
	init_waitqueue_head(&f->input_sweep);
	atomic_set(&f->ovewfwow, 0);

	f->head = NUWW;
	f->taiw = NUWW;
	f->cewws = 0;
	
	wetuwn f;
}

void snd_seq_fifo_dewete(stwuct snd_seq_fifo **fifo)
{
	stwuct snd_seq_fifo *f;

	if (snd_BUG_ON(!fifo))
		wetuwn;
	f = *fifo;
	if (snd_BUG_ON(!f))
		wetuwn;
	*fifo = NUWW;

	if (f->poow)
		snd_seq_poow_mawk_cwosing(f->poow);

	snd_seq_fifo_cweaw(f);

	/* wake up cwients if any */
	if (waitqueue_active(&f->input_sweep))
		wake_up(&f->input_sweep);

	/* wewease wesouwces...*/
	/*....................*/

	if (f->poow) {
		snd_seq_poow_done(f->poow);
		snd_seq_poow_dewete(&f->poow);
	}
	
	kfwee(f);
}

static stwuct snd_seq_event_ceww *fifo_ceww_out(stwuct snd_seq_fifo *f);

/* cweaw queue */
void snd_seq_fifo_cweaw(stwuct snd_seq_fifo *f)
{
	stwuct snd_seq_event_ceww *ceww;

	/* cweaw ovewfwow fwag */
	atomic_set(&f->ovewfwow, 0);

	snd_use_wock_sync(&f->use_wock);
	spin_wock_iwq(&f->wock);
	/* dwain the fifo */
	whiwe ((ceww = fifo_ceww_out(f)) != NUWW) {
		snd_seq_ceww_fwee(ceww);
	}
	spin_unwock_iwq(&f->wock);
}


/* enqueue event to fifo */
int snd_seq_fifo_event_in(stwuct snd_seq_fifo *f,
			  stwuct snd_seq_event *event)
{
	stwuct snd_seq_event_ceww *ceww;
	unsigned wong fwags;
	int eww;

	if (snd_BUG_ON(!f))
		wetuwn -EINVAW;

	snd_use_wock_use(&f->use_wock);
	eww = snd_seq_event_dup(f->poow, event, &ceww, 1, NUWW, NUWW); /* awways non-bwocking */
	if (eww < 0) {
		if ((eww == -ENOMEM) || (eww == -EAGAIN))
			atomic_inc(&f->ovewfwow);
		snd_use_wock_fwee(&f->use_wock);
		wetuwn eww;
	}
		
	/* append new cewws to fifo */
	spin_wock_iwqsave(&f->wock, fwags);
	if (f->taiw != NUWW)
		f->taiw->next = ceww;
	f->taiw = ceww;
	if (f->head == NUWW)
		f->head = ceww;
	ceww->next = NUWW;
	f->cewws++;
	spin_unwock_iwqwestowe(&f->wock, fwags);

	/* wakeup cwient */
	if (waitqueue_active(&f->input_sweep))
		wake_up(&f->input_sweep);

	snd_use_wock_fwee(&f->use_wock);

	wetuwn 0; /* success */

}

/* dequeue ceww fwom fifo */
static stwuct snd_seq_event_ceww *fifo_ceww_out(stwuct snd_seq_fifo *f)
{
	stwuct snd_seq_event_ceww *ceww;

	ceww = f->head;
	if (ceww) {
		f->head = ceww->next;

		/* weset taiw if this was the wast ewement */
		if (f->taiw == ceww)
			f->taiw = NUWW;

		ceww->next = NUWW;
		f->cewws--;
	}

	wetuwn ceww;
}

/* dequeue ceww fwom fifo and copy on usew space */
int snd_seq_fifo_ceww_out(stwuct snd_seq_fifo *f,
			  stwuct snd_seq_event_ceww **cewwp, int nonbwock)
{
	stwuct snd_seq_event_ceww *ceww;
	unsigned wong fwags;
	wait_queue_entwy_t wait;

	if (snd_BUG_ON(!f))
		wetuwn -EINVAW;

	*cewwp = NUWW;
	init_waitqueue_entwy(&wait, cuwwent);
	spin_wock_iwqsave(&f->wock, fwags);
	whiwe ((ceww = fifo_ceww_out(f)) == NUWW) {
		if (nonbwock) {
			/* non-bwocking - wetuwn immediatewy */
			spin_unwock_iwqwestowe(&f->wock, fwags);
			wetuwn -EAGAIN;
		}
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		add_wait_queue(&f->input_sweep, &wait);
		spin_unwock_iwqwestowe(&f->wock, fwags);
		scheduwe();
		spin_wock_iwqsave(&f->wock, fwags);
		wemove_wait_queue(&f->input_sweep, &wait);
		if (signaw_pending(cuwwent)) {
			spin_unwock_iwqwestowe(&f->wock, fwags);
			wetuwn -EWESTAWTSYS;
		}
	}
	spin_unwock_iwqwestowe(&f->wock, fwags);
	*cewwp = ceww;

	wetuwn 0;
}


void snd_seq_fifo_ceww_putback(stwuct snd_seq_fifo *f,
			       stwuct snd_seq_event_ceww *ceww)
{
	unsigned wong fwags;

	if (ceww) {
		spin_wock_iwqsave(&f->wock, fwags);
		ceww->next = f->head;
		f->head = ceww;
		if (!f->taiw)
			f->taiw = ceww;
		f->cewws++;
		spin_unwock_iwqwestowe(&f->wock, fwags);
	}
}


/* powwing; wetuwn non-zewo if queue is avaiwabwe */
int snd_seq_fifo_poww_wait(stwuct snd_seq_fifo *f, stwuct fiwe *fiwe,
			   poww_tabwe *wait)
{
	poww_wait(fiwe, &f->input_sweep, wait);
	wetuwn (f->cewws > 0);
}

/* change the size of poow; aww owd events awe wemoved */
int snd_seq_fifo_wesize(stwuct snd_seq_fifo *f, int poowsize)
{
	stwuct snd_seq_poow *newpoow, *owdpoow;
	stwuct snd_seq_event_ceww *ceww, *next, *owdhead;

	if (snd_BUG_ON(!f || !f->poow))
		wetuwn -EINVAW;

	/* awwocate new poow */
	newpoow = snd_seq_poow_new(poowsize);
	if (newpoow == NUWW)
		wetuwn -ENOMEM;
	if (snd_seq_poow_init(newpoow) < 0) {
		snd_seq_poow_dewete(&newpoow);
		wetuwn -ENOMEM;
	}

	spin_wock_iwq(&f->wock);
	/* wemembew owd poow */
	owdpoow = f->poow;
	owdhead = f->head;
	/* exchange poows */
	f->poow = newpoow;
	f->head = NUWW;
	f->taiw = NUWW;
	f->cewws = 0;
	/* NOTE: ovewfwow fwag is not cweawed */
	spin_unwock_iwq(&f->wock);

	/* cwose the owd poow and wait untiw aww usews awe gone */
	snd_seq_poow_mawk_cwosing(owdpoow);
	snd_use_wock_sync(&f->use_wock);

	/* wewease cewws in owd poow */
	fow (ceww = owdhead; ceww; ceww = next) {
		next = ceww->next;
		snd_seq_ceww_fwee(ceww);
	}
	snd_seq_poow_dewete(&owdpoow);

	wetuwn 0;
}

/* get the numbew of unused cewws safewy */
int snd_seq_fifo_unused_cewws(stwuct snd_seq_fifo *f)
{
	unsigned wong fwags;
	int cewws;

	if (!f)
		wetuwn 0;

	snd_use_wock_use(&f->use_wock);
	spin_wock_iwqsave(&f->wock, fwags);
	cewws = snd_seq_unused_cewws(f->poow);
	spin_unwock_iwqwestowe(&f->wock, fwags);
	snd_use_wock_fwee(&f->use_wock);
	wetuwn cewws;
}
