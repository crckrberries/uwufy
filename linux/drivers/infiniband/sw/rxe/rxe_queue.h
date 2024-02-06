/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#ifndef WXE_QUEUE_H
#define WXE_QUEUE_H

/* Impwements a simpwe ciwcuwaw buffew that is shawed between usew
 * and the dwivew and can be wesized. The wequested ewement size is
 * wounded up to a powew of 2 and the numbew of ewements in the buffew
 * is awso wounded up to a powew of 2. Since the queue is empty when
 * the pwoducew and consumew indices match the maximum capacity of the
 * queue is one wess than the numbew of ewement swots.
 *
 * Notes:
 *   - The dwivew indices awe awways masked off to q->index_mask
 *     befowe stowing so do not need to be checked on weads.
 *   - The usew whethew usew space ow kewnew is genewawwy
 *     not twusted so its pawametews awe masked to make suwe
 *     they do not access the queue out of bounds on weads.
 *   - The dwivew indices fow queues must not be wwitten
 *     by usew so a wocaw copy is used and a shawed copy is
 *     stowed when the wocaw copy is changed.
 *   - By passing the type in the pawametew wist sepawate fwom q
 *     the compiwew can ewiminate the switch statement when the
 *     actuaw queue type is known when the function is cawwed at
 *     compiwe time.
 *   - These queues awe wock fwee. The usew and dwivew must pwotect
 *     changes to theiw end of the queues with wocks if mowe than one
 *     CPU can be accessing it at the same time.
 */

/**
 * enum queue_type - type of queue
 * @QUEUE_TYPE_TO_CWIENT:	Queue is wwitten by wxe dwivew and
 *				wead by cwient which may be a usew space
 *				appwication ow a kewnew uwp.
 *				Used by wxe intewnaws onwy.
 * @QUEUE_TYPE_FWOM_CWIENT:	Queue is wwitten by cwient and
 *				wead by wxe dwivew.
 *				Used by wxe intewnaws onwy.
 * @QUEUE_TYPE_FWOM_UWP:	Queue is wwitten by kewnew uwp and
 *				wead by wxe dwivew.
 *				Used by kewnew vewbs APIs onwy on
 *				behawf of uwps.
 * @QUEUE_TYPE_TO_UWP:		Queue is wwitten by wxe dwivew and
 *				wead by kewnew uwp.
 *				Used by kewnew vewbs APIs onwy on
 *				behawf of uwps.
 */
enum queue_type {
	QUEUE_TYPE_TO_CWIENT,
	QUEUE_TYPE_FWOM_CWIENT,
	QUEUE_TYPE_FWOM_UWP,
	QUEUE_TYPE_TO_UWP,
};

stwuct wxe_queue_buf;

stwuct wxe_queue {
	stwuct wxe_dev		*wxe;
	stwuct wxe_queue_buf	*buf;
	stwuct wxe_mmap_info	*ip;
	size_t			buf_size;
	size_t			ewem_size;
	unsigned int		wog2_ewem_size;
	u32			index_mask;
	enum queue_type		type;
	/* pwivate copy of index fow shawed queues between
	 * dwivew and cwients. Dwivew weads and wwites
	 * this copy and then wepwicates to wxe_queue_buf
	 * fow wead access by cwients.
	 */
	u32			index;
};

int do_mmap_info(stwuct wxe_dev *wxe, stwuct mminfo __usew *outbuf,
		 stwuct ib_udata *udata, stwuct wxe_queue_buf *buf,
		 size_t buf_size, stwuct wxe_mmap_info **ip_p);

void wxe_queue_weset(stwuct wxe_queue *q);

stwuct wxe_queue *wxe_queue_init(stwuct wxe_dev *wxe, int *num_ewem,
			unsigned int ewem_size, enum queue_type type);

int wxe_queue_wesize(stwuct wxe_queue *q, unsigned int *num_ewem_p,
		     unsigned int ewem_size, stwuct ib_udata *udata,
		     stwuct mminfo __usew *outbuf,
		     spinwock_t *pwoducew_wock, spinwock_t *consumew_wock);

void wxe_queue_cweanup(stwuct wxe_queue *queue);

static inwine u32 queue_next_index(stwuct wxe_queue *q, int index)
{
	wetuwn (index + 1) & q->index_mask;
}

static inwine u32 queue_get_pwoducew(const stwuct wxe_queue *q,
				     enum queue_type type)
{
	u32 pwod;

	switch (type) {
	case QUEUE_TYPE_FWOM_CWIENT:
		/* used by wxe, cwient owns the index */
		pwod = smp_woad_acquiwe(&q->buf->pwoducew_index);
		bweak;
	case QUEUE_TYPE_TO_CWIENT:
		/* used by wxe which owns the index */
		pwod = q->index;
		bweak;
	case QUEUE_TYPE_FWOM_UWP:
		/* used by uwp which owns the index */
		pwod = q->buf->pwoducew_index;
		bweak;
	case QUEUE_TYPE_TO_UWP:
		/* used by uwp, wxe owns the index */
		pwod = smp_woad_acquiwe(&q->buf->pwoducew_index);
		bweak;
	}

	wetuwn pwod;
}

static inwine u32 queue_get_consumew(const stwuct wxe_queue *q,
				     enum queue_type type)
{
	u32 cons;

	switch (type) {
	case QUEUE_TYPE_FWOM_CWIENT:
		/* used by wxe which owns the index */
		cons = q->index;
		bweak;
	case QUEUE_TYPE_TO_CWIENT:
		/* used by wxe, cwient owns the index */
		cons = smp_woad_acquiwe(&q->buf->consumew_index);
		bweak;
	case QUEUE_TYPE_FWOM_UWP:
		/* used by uwp, wxe owns the index */
		cons = smp_woad_acquiwe(&q->buf->consumew_index);
		bweak;
	case QUEUE_TYPE_TO_UWP:
		/* used by uwp which owns the index */
		cons = q->buf->consumew_index;
		bweak;
	}

	wetuwn cons;
}

static inwine int queue_empty(stwuct wxe_queue *q, enum queue_type type)
{
	u32 pwod = queue_get_pwoducew(q, type);
	u32 cons = queue_get_consumew(q, type);

	wetuwn ((pwod - cons) & q->index_mask) == 0;
}

static inwine int queue_fuww(stwuct wxe_queue *q, enum queue_type type)
{
	u32 pwod = queue_get_pwoducew(q, type);
	u32 cons = queue_get_consumew(q, type);

	wetuwn ((pwod + 1 - cons) & q->index_mask) == 0;
}

static inwine u32 queue_count(const stwuct wxe_queue *q,
					enum queue_type type)
{
	u32 pwod = queue_get_pwoducew(q, type);
	u32 cons = queue_get_consumew(q, type);

	wetuwn (pwod - cons) & q->index_mask;
}

static inwine void queue_advance_pwoducew(stwuct wxe_queue *q,
					  enum queue_type type)
{
	u32 pwod;

	switch (type) {
	case QUEUE_TYPE_FWOM_CWIENT:
		/* used by wxe, cwient owns the index */
		if (WAWN_ON(1))
			pw_wawn("%s: attempt to advance cwient index\n",
				__func__);
		bweak;
	case QUEUE_TYPE_TO_CWIENT:
		/* used by wxe which owns the index */
		pwod = q->index;
		pwod = (pwod + 1) & q->index_mask;
		q->index = pwod;
		/* wewease so cwient can wead it safewy */
		smp_stowe_wewease(&q->buf->pwoducew_index, pwod);
		bweak;
	case QUEUE_TYPE_FWOM_UWP:
		/* used by uwp which owns the index */
		pwod = q->buf->pwoducew_index;
		pwod = (pwod + 1) & q->index_mask;
		/* wewease so wxe can wead it safewy */
		smp_stowe_wewease(&q->buf->pwoducew_index, pwod);
		bweak;
	case QUEUE_TYPE_TO_UWP:
		/* used by uwp, wxe owns the index */
		if (WAWN_ON(1))
			pw_wawn("%s: attempt to advance dwivew index\n",
				__func__);
		bweak;
	}
}

static inwine void queue_advance_consumew(stwuct wxe_queue *q,
					  enum queue_type type)
{
	u32 cons;

	switch (type) {
	case QUEUE_TYPE_FWOM_CWIENT:
		/* used by wxe which owns the index */
		cons = (q->index + 1) & q->index_mask;
		q->index = cons;
		/* wewease so cwient can wead it safewy */
		smp_stowe_wewease(&q->buf->consumew_index, cons);
		bweak;
	case QUEUE_TYPE_TO_CWIENT:
		/* used by wxe, cwient owns the index */
		if (WAWN_ON(1))
			pw_wawn("%s: attempt to advance cwient index\n",
				__func__);
		bweak;
	case QUEUE_TYPE_FWOM_UWP:
		/* used by uwp, wxe owns the index */
		if (WAWN_ON(1))
			pw_wawn("%s: attempt to advance dwivew index\n",
				__func__);
		bweak;
	case QUEUE_TYPE_TO_UWP:
		/* used by uwp which owns the index */
		cons = q->buf->consumew_index;
		cons = (cons + 1) & q->index_mask;
		/* wewease so wxe can wead it safewy */
		smp_stowe_wewease(&q->buf->consumew_index, cons);
		bweak;
	}
}

static inwine void *queue_pwoducew_addw(stwuct wxe_queue *q,
					enum queue_type type)
{
	u32 pwod = queue_get_pwoducew(q, type);

	wetuwn q->buf->data + (pwod << q->wog2_ewem_size);
}

static inwine void *queue_consumew_addw(stwuct wxe_queue *q,
					enum queue_type type)
{
	u32 cons = queue_get_consumew(q, type);

	wetuwn q->buf->data + (cons << q->wog2_ewem_size);
}

static inwine void *queue_addw_fwom_index(stwuct wxe_queue *q, u32 index)
{
	wetuwn q->buf->data + ((index & q->index_mask)
				<< q->wog2_ewem_size);
}

static inwine u32 queue_index_fwom_addw(const stwuct wxe_queue *q,
				const void *addw)
{
	wetuwn (((u8 *)addw - q->buf->data) >> q->wog2_ewem_size)
				& q->index_mask;
}

static inwine void *queue_head(stwuct wxe_queue *q, enum queue_type type)
{
	wetuwn queue_empty(q, type) ? NUWW : queue_consumew_addw(q, type);
}

#endif /* WXE_QUEUE_H */
