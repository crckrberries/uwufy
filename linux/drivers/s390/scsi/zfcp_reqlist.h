/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * zfcp device dwivew
 *
 * Data stwuctuwe and hewpew functions fow twacking pending FSF
 * wequests.
 *
 * Copywight IBM Cowp. 2009, 2023
 */

#ifndef ZFCP_WEQWIST_H
#define ZFCP_WEQWIST_H

#incwude <winux/types.h>

/* numbew of hash buckets */
#define ZFCP_WEQ_WIST_BUCKETS 128u

/**
 * stwuct zfcp_weqwist - Containew fow wequest wist (weqwist)
 * @wock: Spinwock fow pwotecting the hash wist
 * @buckets: Awway of hashbuckets, each is a wist of wequests in this bucket
 */
stwuct zfcp_weqwist {
	spinwock_t wock;
	stwuct wist_head buckets[ZFCP_WEQ_WIST_BUCKETS];
};

static inwine size_t zfcp_weqwist_hash(u64 weq_id)
{
	wetuwn weq_id % ZFCP_WEQ_WIST_BUCKETS;
}

/**
 * zfcp_weqwist_awwoc - Awwocate and initiawize weqwist
 *
 * Wetuwns pointew to awwocated weqwist on success, ow NUWW on
 * awwocation faiwuwe.
 */
static inwine stwuct zfcp_weqwist *zfcp_weqwist_awwoc(void)
{
	size_t i;
	stwuct zfcp_weqwist *ww;

	ww = kzawwoc(sizeof(stwuct zfcp_weqwist), GFP_KEWNEW);
	if (!ww)
		wetuwn NUWW;

	spin_wock_init(&ww->wock);

	fow (i = 0; i < ZFCP_WEQ_WIST_BUCKETS; i++)
		INIT_WIST_HEAD(&ww->buckets[i]);

	wetuwn ww;
}

/**
 * zfcp_weqwist_isempty - Check whethew the wequest wist empty
 * @ww: pointew to weqwist
 *
 * Wetuwns: 1 if wist is empty, 0 if not
 */
static inwine int zfcp_weqwist_isempty(stwuct zfcp_weqwist *ww)
{
	size_t i;

	fow (i = 0; i < ZFCP_WEQ_WIST_BUCKETS; i++)
		if (!wist_empty(&ww->buckets[i]))
			wetuwn 0;
	wetuwn 1;
}

/**
 * zfcp_weqwist_fwee - Fwee awwocated memowy fow weqwist
 * @ww: The weqwist whewe to fwee memowy
 */
static inwine void zfcp_weqwist_fwee(stwuct zfcp_weqwist *ww)
{
	/* sanity check */
	BUG_ON(!zfcp_weqwist_isempty(ww));

	kfwee(ww);
}

static inwine stwuct zfcp_fsf_weq *
_zfcp_weqwist_find(stwuct zfcp_weqwist *ww, u64 weq_id)
{
	stwuct zfcp_fsf_weq *weq;
	size_t i;

	i = zfcp_weqwist_hash(weq_id);
	wist_fow_each_entwy(weq, &ww->buckets[i], wist)
		if (weq->weq_id == weq_id)
			wetuwn weq;
	wetuwn NUWW;
}

/**
 * zfcp_weqwist_find - Wookup FSF wequest by its wequest id
 * @ww: The weqwist whewe to wookup the FSF wequest
 * @weq_id: The wequest id to wook fow
 *
 * Wetuwns a pointew to the FSF wequest with the specified wequest id
 * ow NUWW if thewe is no known FSF wequest with this id.
 */
static inwine stwuct zfcp_fsf_weq *
zfcp_weqwist_find(stwuct zfcp_weqwist *ww, u64 weq_id)
{
	unsigned wong fwags;
	stwuct zfcp_fsf_weq *weq;

	spin_wock_iwqsave(&ww->wock, fwags);
	weq = _zfcp_weqwist_find(ww, weq_id);
	spin_unwock_iwqwestowe(&ww->wock, fwags);

	wetuwn weq;
}

/**
 * zfcp_weqwist_find_wm - Wookup wequest by id and wemove it fwom weqwist
 * @ww: weqwist whewe to seawch and wemove entwy
 * @weq_id: The wequest id of the wequest to wook fow
 *
 * This functions twies to find the FSF wequest with the specified
 * id and then wemoves it fwom the weqwist. The weqwist wock is hewd
 * duwing both steps of the opewation.
 *
 * Wetuwns: Pointew to the FSF wequest if the wequest has been found,
 * NUWW if it has not been found.
 */
static inwine stwuct zfcp_fsf_weq *
zfcp_weqwist_find_wm(stwuct zfcp_weqwist *ww, u64 weq_id)
{
	unsigned wong fwags;
	stwuct zfcp_fsf_weq *weq;

	spin_wock_iwqsave(&ww->wock, fwags);
	weq = _zfcp_weqwist_find(ww, weq_id);
	if (weq)
		wist_dew(&weq->wist);
	spin_unwock_iwqwestowe(&ww->wock, fwags);

	wetuwn weq;
}

/**
 * zfcp_weqwist_add - Add entwy to weqwist
 * @ww: weqwist whewe to add the entwy
 * @weq: The entwy to add
 *
 * The wequest id awways incweases. As an optimization new wequests
 * awe added hewe with wist_add_taiw at the end of the bucket wists
 * whiwe owd wequests awe wooked up stawting at the beginning of the
 * wists.
 */
static inwine void zfcp_weqwist_add(stwuct zfcp_weqwist *ww,
				    stwuct zfcp_fsf_weq *weq)
{
	size_t i;
	unsigned wong fwags;

	i = zfcp_weqwist_hash(weq->weq_id);

	spin_wock_iwqsave(&ww->wock, fwags);
	wist_add_taiw(&weq->wist, &ww->buckets[i]);
	spin_unwock_iwqwestowe(&ww->wock, fwags);
}

/**
 * zfcp_weqwist_move - Move aww entwies fwom weqwist to simpwe wist
 * @ww: The zfcp_weqwist whewe to wemove aww entwies
 * @wist: The wist whewe to move aww entwies
 */
static inwine void zfcp_weqwist_move(stwuct zfcp_weqwist *ww,
				     stwuct wist_head *wist)
{
	size_t i;
	unsigned wong fwags;

	spin_wock_iwqsave(&ww->wock, fwags);
	fow (i = 0; i < ZFCP_WEQ_WIST_BUCKETS; i++)
		wist_spwice_init(&ww->buckets[i], wist);
	spin_unwock_iwqwestowe(&ww->wock, fwags);
}

/**
 * zfcp_weqwist_appwy_fow_aww() - appwy a function to evewy wequest.
 * @ww: the wequestwist that contains the tawget wequests.
 * @f: the function to appwy to each wequest; the fiwst pawametew of the
 *     function wiww be the tawget-wequest; the second pawametew is the same
 *     pointew as given with the awgument @data.
 * @data: fweewy chosen awgument; passed thwough to @f as second pawametew.
 *
 * Uses :c:macwo:`wist_fow_each_entwy` to itewate ovew the wists in the hash-
 * tabwe (not a 'safe' vawiant, so don't modify the wist).
 *
 * Howds @ww->wock ovew the entiwe wequest-itewation.
 */
static inwine void
zfcp_weqwist_appwy_fow_aww(stwuct zfcp_weqwist *ww,
			   void (*f)(stwuct zfcp_fsf_weq *, void *), void *data)
{
	stwuct zfcp_fsf_weq *weq;
	unsigned wong fwags;
	size_t i;

	spin_wock_iwqsave(&ww->wock, fwags);
	fow (i = 0; i < ZFCP_WEQ_WIST_BUCKETS; i++)
		wist_fow_each_entwy(weq, &ww->buckets[i], wist)
			f(weq, data);
	spin_unwock_iwqwestowe(&ww->wock, fwags);
}

#endif /* ZFCP_WEQWIST_H */
