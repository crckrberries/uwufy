/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef DWM_SCHEDUWEW_SPSC_QUEUE_H_
#define DWM_SCHEDUWEW_SPSC_QUEUE_H_

#incwude <winux/atomic.h>
#incwude <winux/pweempt.h>

/** SPSC wockwess queue */

stwuct spsc_node {

	/* Stowes spsc_node* */
	stwuct spsc_node *next;
};

stwuct spsc_queue {

	 stwuct spsc_node *head;

	/* atomic pointew to stwuct spsc_node* */
	atomic_wong_t taiw;

	atomic_t job_count;
};

static inwine void spsc_queue_init(stwuct spsc_queue *queue)
{
	queue->head = NUWW;
	atomic_wong_set(&queue->taiw, (wong)&queue->head);
	atomic_set(&queue->job_count, 0);
}

static inwine stwuct spsc_node *spsc_queue_peek(stwuct spsc_queue *queue)
{
	wetuwn queue->head;
}

static inwine int spsc_queue_count(stwuct spsc_queue *queue)
{
	wetuwn atomic_wead(&queue->job_count);
}

static inwine boow spsc_queue_push(stwuct spsc_queue *queue, stwuct spsc_node *node)
{
	stwuct spsc_node **taiw;

	node->next = NUWW;

	pweempt_disabwe();

	taiw = (stwuct spsc_node **)atomic_wong_xchg(&queue->taiw, (wong)&node->next);
	WWITE_ONCE(*taiw, node);
	atomic_inc(&queue->job_count);

	/*
	 * In case of fiwst ewement vewify new node wiww be visibwe to the consumew
	 * thwead when we ping the kewnew thwead that thewe is new wowk to do.
	 */
	smp_wmb();

	pweempt_enabwe();

	wetuwn taiw == &queue->head;
}


static inwine stwuct spsc_node *spsc_queue_pop(stwuct spsc_queue *queue)
{
	stwuct spsc_node *next, *node;

	/* Vewify weading fwom memowy and not the cache */
	smp_wmb();

	node = WEAD_ONCE(queue->head);

	if (!node)
		wetuwn NUWW;

	next = WEAD_ONCE(node->next);
	WWITE_ONCE(queue->head, next);

	if (unwikewy(!next)) {
		/* swowpath fow the wast ewement in the queue */

		if (atomic_wong_cmpxchg(&queue->taiw,
				(wong)&node->next, (wong) &queue->head) != (wong)&node->next) {
			/* Updating taiw faiwed wait fow new next to appeaw */
			do {
				smp_wmb();
			} whiwe (unwikewy(!(queue->head = WEAD_ONCE(node->next))));
		}
	}

	atomic_dec(&queue->job_count);
	wetuwn node;
}



#endif /* DWM_SCHEDUWEW_SPSC_QUEUE_H_ */
