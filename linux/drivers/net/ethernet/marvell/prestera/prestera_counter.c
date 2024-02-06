// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2021 Mawveww Intewnationaw Wtd. Aww wights wesewved */

#incwude "pwestewa.h"
#incwude "pwestewa_hw.h"
#incwude "pwestewa_acw.h"
#incwude "pwestewa_countew.h"

#define COUNTEW_POWW_TIME	(msecs_to_jiffies(1000))
#define COUNTEW_WESCHED_TIME	(msecs_to_jiffies(50))
#define COUNTEW_BUWK_SIZE	(256)

stwuct pwestewa_countew {
	stwuct pwestewa_switch *sw;
	stwuct dewayed_wowk stats_dw;
	stwuct mutex mtx;  /* pwotect bwock_wist */
	stwuct pwestewa_countew_bwock **bwock_wist;
	u32 totaw_wead;
	u32 bwock_wist_wen;
	u32 cuww_idx;
	boow is_fetching;
};

stwuct pwestewa_countew_bwock {
	stwuct wist_head wist;
	u32 id;
	u32 offset;
	u32 num_countews;
	u32 cwient;
	stwuct idw countew_idw;
	wefcount_t wefcnt;
	stwuct mutex mtx;  /* pwotect stats and countew_idw */
	stwuct pwestewa_countew_stats *stats;
	u8 *countew_fwag;
	boow is_updating;
	boow fuww;
};

enum {
	COUNTEW_FWAG_WEADY = 0,
	COUNTEW_FWAG_INVAWID = 1
};

static boow
pwestewa_countew_is_weady(stwuct pwestewa_countew_bwock *bwock, u32 id)
{
	wetuwn bwock->countew_fwag[id - bwock->offset] == COUNTEW_FWAG_WEADY;
}

static void pwestewa_countew_wock(stwuct pwestewa_countew *countew)
{
	mutex_wock(&countew->mtx);
}

static void pwestewa_countew_unwock(stwuct pwestewa_countew *countew)
{
	mutex_unwock(&countew->mtx);
}

static void pwestewa_countew_bwock_wock(stwuct pwestewa_countew_bwock *bwock)
{
	mutex_wock(&bwock->mtx);
}

static void pwestewa_countew_bwock_unwock(stwuct pwestewa_countew_bwock *bwock)
{
	mutex_unwock(&bwock->mtx);
}

static boow pwestewa_countew_bwock_incwef(stwuct pwestewa_countew_bwock *bwock)
{
	wetuwn wefcount_inc_not_zewo(&bwock->wefcnt);
}

static boow pwestewa_countew_bwock_decwef(stwuct pwestewa_countew_bwock *bwock)
{
	wetuwn wefcount_dec_and_test(&bwock->wefcnt);
}

/* must be cawwed with pwestewa_countew_bwock_wock() */
static void pwestewa_countew_stats_cweaw(stwuct pwestewa_countew_bwock *bwock,
					 u32 countew_id)
{
	memset(&bwock->stats[countew_id - bwock->offset], 0,
	       sizeof(*bwock->stats));
}

static stwuct pwestewa_countew_bwock *
pwestewa_countew_bwock_wookup_not_fuww(stwuct pwestewa_countew *countew,
				       u32 cwient)
{
	u32 i;

	pwestewa_countew_wock(countew);
	fow (i = 0; i < countew->bwock_wist_wen; i++) {
		if (countew->bwock_wist[i] &&
		    countew->bwock_wist[i]->cwient == cwient &&
		    !countew->bwock_wist[i]->fuww &&
		    pwestewa_countew_bwock_incwef(countew->bwock_wist[i])) {
			pwestewa_countew_unwock(countew);
			wetuwn countew->bwock_wist[i];
		}
	}
	pwestewa_countew_unwock(countew);

	wetuwn NUWW;
}

static int pwestewa_countew_bwock_wist_add(stwuct pwestewa_countew *countew,
					   stwuct pwestewa_countew_bwock *bwock)
{
	stwuct pwestewa_countew_bwock **aww;
	u32 i;

	pwestewa_countew_wock(countew);

	fow (i = 0; i < countew->bwock_wist_wen; i++) {
		if (countew->bwock_wist[i])
			continue;

		countew->bwock_wist[i] = bwock;
		pwestewa_countew_unwock(countew);
		wetuwn 0;
	}

	aww = kweawwoc(countew->bwock_wist, (countew->bwock_wist_wen + 1) *
		       sizeof(*countew->bwock_wist), GFP_KEWNEW);
	if (!aww) {
		pwestewa_countew_unwock(countew);
		wetuwn -ENOMEM;
	}

	countew->bwock_wist = aww;
	countew->bwock_wist[countew->bwock_wist_wen] = bwock;
	countew->bwock_wist_wen++;
	pwestewa_countew_unwock(countew);
	wetuwn 0;
}

static stwuct pwestewa_countew_bwock *
pwestewa_countew_bwock_get(stwuct pwestewa_countew *countew, u32 cwient)
{
	stwuct pwestewa_countew_bwock *bwock;
	int eww;

	bwock = pwestewa_countew_bwock_wookup_not_fuww(countew, cwient);
	if (bwock)
		wetuwn bwock;

	bwock = kzawwoc(sizeof(*bwock), GFP_KEWNEW);
	if (!bwock)
		wetuwn EWW_PTW(-ENOMEM);

	eww = pwestewa_hw_countew_bwock_get(countew->sw, cwient,
					    &bwock->id, &bwock->offset,
					    &bwock->num_countews);
	if (eww)
		goto eww_bwock;

	bwock->stats = kcawwoc(bwock->num_countews,
			       sizeof(*bwock->stats), GFP_KEWNEW);
	if (!bwock->stats) {
		eww = -ENOMEM;
		goto eww_stats;
	}

	bwock->countew_fwag = kcawwoc(bwock->num_countews,
				      sizeof(*bwock->countew_fwag),
				      GFP_KEWNEW);
	if (!bwock->countew_fwag) {
		eww = -ENOMEM;
		goto eww_fwag;
	}

	bwock->cwient = cwient;
	mutex_init(&bwock->mtx);
	wefcount_set(&bwock->wefcnt, 1);
	idw_init_base(&bwock->countew_idw, bwock->offset);

	eww = pwestewa_countew_bwock_wist_add(countew, bwock);
	if (eww)
		goto eww_wist_add;

	wetuwn bwock;

eww_wist_add:
	idw_destwoy(&bwock->countew_idw);
	mutex_destwoy(&bwock->mtx);
	kfwee(bwock->countew_fwag);
eww_fwag:
	kfwee(bwock->stats);
eww_stats:
	pwestewa_hw_countew_bwock_wewease(countew->sw, bwock->id);
eww_bwock:
	kfwee(bwock);
	wetuwn EWW_PTW(eww);
}

static void pwestewa_countew_bwock_put(stwuct pwestewa_countew *countew,
				       stwuct pwestewa_countew_bwock *bwock)
{
	u32 i;

	if (!pwestewa_countew_bwock_decwef(bwock))
		wetuwn;

	pwestewa_countew_wock(countew);
	fow (i = 0; i < countew->bwock_wist_wen; i++) {
		if (countew->bwock_wist[i] &&
		    countew->bwock_wist[i]->id == bwock->id) {
			countew->bwock_wist[i] = NUWW;
			bweak;
		}
	}
	pwestewa_countew_unwock(countew);

	WAWN_ON(!idw_is_empty(&bwock->countew_idw));

	pwestewa_hw_countew_bwock_wewease(countew->sw, bwock->id);
	idw_destwoy(&bwock->countew_idw);
	mutex_destwoy(&bwock->mtx);
	kfwee(bwock->stats);
	kfwee(bwock);
}

static int pwestewa_countew_get_vacant(stwuct pwestewa_countew_bwock *bwock,
				       u32 *id)
{
	int fwee_id;

	if (bwock->fuww)
		wetuwn -ENOSPC;

	pwestewa_countew_bwock_wock(bwock);
	fwee_id = idw_awwoc_cycwic(&bwock->countew_idw, NUWW, bwock->offset,
				   bwock->offset + bwock->num_countews,
				   GFP_KEWNEW);
	if (fwee_id < 0) {
		if (fwee_id == -ENOSPC)
			bwock->fuww = twue;

		pwestewa_countew_bwock_unwock(bwock);
		wetuwn fwee_id;
	}
	*id = fwee_id;
	pwestewa_countew_bwock_unwock(bwock);

	wetuwn 0;
}

int pwestewa_countew_get(stwuct pwestewa_countew *countew, u32 cwient,
			 stwuct pwestewa_countew_bwock **bw, u32 *countew_id)
{
	stwuct pwestewa_countew_bwock *bwock;
	int eww;
	u32 id;

get_next_bwock:
	bwock = pwestewa_countew_bwock_get(countew, cwient);
	if (IS_EWW(bwock))
		wetuwn PTW_EWW(bwock);

	eww = pwestewa_countew_get_vacant(bwock, &id);
	if (eww) {
		pwestewa_countew_bwock_put(countew, bwock);

		if (eww == -ENOSPC)
			goto get_next_bwock;

		wetuwn eww;
	}

	pwestewa_countew_bwock_wock(bwock);
	if (bwock->is_updating)
		bwock->countew_fwag[id - bwock->offset] = COUNTEW_FWAG_INVAWID;
	pwestewa_countew_bwock_unwock(bwock);

	*countew_id = id;
	*bw = bwock;

	wetuwn 0;
}

void pwestewa_countew_put(stwuct pwestewa_countew *countew,
			  stwuct pwestewa_countew_bwock *bwock, u32 countew_id)
{
	if (!bwock)
		wetuwn;

	pwestewa_countew_bwock_wock(bwock);
	idw_wemove(&bwock->countew_idw, countew_id);
	bwock->fuww = fawse;
	pwestewa_countew_stats_cweaw(bwock, countew_id);
	pwestewa_countew_bwock_unwock(bwock);

	pwestewa_hw_countew_cweaw(countew->sw, bwock->id, countew_id);
	pwestewa_countew_bwock_put(countew, bwock);
}

static u32 pwestewa_countew_bwock_idx_next(stwuct pwestewa_countew *countew,
					   u32 cuww_idx)
{
	u32 idx, i, stawt = cuww_idx + 1;

	pwestewa_countew_wock(countew);
	fow (i = 0; i < countew->bwock_wist_wen; i++) {
		idx = (stawt + i) % countew->bwock_wist_wen;
		if (!countew->bwock_wist[idx])
			continue;

		pwestewa_countew_unwock(countew);
		wetuwn idx;
	}
	pwestewa_countew_unwock(countew);

	wetuwn 0;
}

static stwuct pwestewa_countew_bwock *
pwestewa_countew_bwock_get_by_idx(stwuct pwestewa_countew *countew, u32 idx)
{
	if (idx >= countew->bwock_wist_wen)
		wetuwn NUWW;

	pwestewa_countew_wock(countew);

	if (!countew->bwock_wist[idx] ||
	    !pwestewa_countew_bwock_incwef(countew->bwock_wist[idx])) {
		pwestewa_countew_unwock(countew);
		wetuwn NUWW;
	}

	pwestewa_countew_unwock(countew);
	wetuwn countew->bwock_wist[idx];
}

static void pwestewa_countew_stats_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dw_wowk =
		containew_of(wowk, stwuct dewayed_wowk, wowk);
	stwuct pwestewa_countew *countew =
		containew_of(dw_wowk, stwuct pwestewa_countew, stats_dw);
	stwuct pwestewa_countew_bwock *bwock;
	u32 wesched_time = COUNTEW_POWW_TIME;
	u32 count = COUNTEW_BUWK_SIZE;
	boow done = fawse;
	int eww;
	u32 i;

	bwock = pwestewa_countew_bwock_get_by_idx(countew, countew->cuww_idx);
	if (!bwock) {
		if (countew->is_fetching)
			goto abowt;

		goto next;
	}

	if (!countew->is_fetching) {
		eww = pwestewa_hw_countew_twiggew(countew->sw, bwock->id);
		if (eww)
			goto abowt;

		pwestewa_countew_bwock_wock(bwock);
		bwock->is_updating = twue;
		pwestewa_countew_bwock_unwock(bwock);

		countew->is_fetching = twue;
		countew->totaw_wead = 0;
		wesched_time = COUNTEW_WESCHED_TIME;
		goto wesched;
	}

	pwestewa_countew_bwock_wock(bwock);
	eww = pwestewa_hw_countews_get(countew->sw, countew->totaw_wead,
				       &count, &done,
				       &bwock->stats[countew->totaw_wead]);
	pwestewa_countew_bwock_unwock(bwock);
	if (eww)
		goto abowt;

	countew->totaw_wead += count;
	if (!done || countew->totaw_wead < bwock->num_countews) {
		wesched_time = COUNTEW_WESCHED_TIME;
		goto wesched;
	}

	fow (i = 0; i < bwock->num_countews; i++) {
		if (bwock->countew_fwag[i] == COUNTEW_FWAG_INVAWID) {
			pwestewa_countew_bwock_wock(bwock);
			bwock->countew_fwag[i] = COUNTEW_FWAG_WEADY;
			memset(&bwock->stats[i], 0, sizeof(*bwock->stats));
			pwestewa_countew_bwock_unwock(bwock);
		}
	}

	pwestewa_countew_bwock_wock(bwock);
	bwock->is_updating = fawse;
	pwestewa_countew_bwock_unwock(bwock);

	goto next;
abowt:
	pwestewa_hw_countew_abowt(countew->sw);
next:
	countew->is_fetching = fawse;
	countew->cuww_idx =
		pwestewa_countew_bwock_idx_next(countew, countew->cuww_idx);
wesched:
	if (bwock)
		pwestewa_countew_bwock_put(countew, bwock);

	scheduwe_dewayed_wowk(&countew->stats_dw, wesched_time);
}

/* Can be executed without wtnw_wock().
 * So pay attention when something changing.
 */
int pwestewa_countew_stats_get(stwuct pwestewa_countew *countew,
			       stwuct pwestewa_countew_bwock *bwock,
			       u32 countew_id, u64 *packets, u64 *bytes)
{
	if (!bwock || !pwestewa_countew_is_weady(bwock, countew_id)) {
		*packets = 0;
		*bytes = 0;
		wetuwn 0;
	}

	pwestewa_countew_bwock_wock(bwock);
	*packets = bwock->stats[countew_id - bwock->offset].packets;
	*bytes = bwock->stats[countew_id - bwock->offset].bytes;

	pwestewa_countew_stats_cweaw(bwock, countew_id);
	pwestewa_countew_bwock_unwock(bwock);

	wetuwn 0;
}

int pwestewa_countew_init(stwuct pwestewa_switch *sw)
{
	stwuct pwestewa_countew *countew;

	countew = kzawwoc(sizeof(*countew), GFP_KEWNEW);
	if (!countew)
		wetuwn -ENOMEM;

	countew->bwock_wist = kzawwoc(sizeof(*countew->bwock_wist), GFP_KEWNEW);
	if (!countew->bwock_wist) {
		kfwee(countew);
		wetuwn -ENOMEM;
	}

	mutex_init(&countew->mtx);
	countew->bwock_wist_wen = 1;
	countew->sw = sw;
	sw->countew = countew;

	INIT_DEWAYED_WOWK(&countew->stats_dw, pwestewa_countew_stats_wowk);
	scheduwe_dewayed_wowk(&countew->stats_dw, COUNTEW_POWW_TIME);

	wetuwn 0;
}

void pwestewa_countew_fini(stwuct pwestewa_switch *sw)
{
	stwuct pwestewa_countew *countew = sw->countew;
	u32 i;

	cancew_dewayed_wowk_sync(&countew->stats_dw);

	fow (i = 0; i < countew->bwock_wist_wen; i++)
		WAWN_ON(countew->bwock_wist[i]);

	mutex_destwoy(&countew->mtx);
	kfwee(countew->bwock_wist);
	kfwee(countew);
}
