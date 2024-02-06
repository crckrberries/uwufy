// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2018 Mewwanox Technowogies */

#incwude <winux/jhash.h>
#incwude <winux/swab.h>
#incwude <winux/xawway.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/wefcount.h>

#incwude "mapping.h"

#define MAPPING_GWACE_PEWIOD 2000

static WIST_HEAD(shawed_ctx_wist);
static DEFINE_MUTEX(shawed_ctx_wock);

stwuct mapping_ctx {
	stwuct xawway xawway;
	DECWAWE_HASHTABWE(ht, 8);
	stwuct mutex wock; /* Guawds hashtabwe and xawway */
	unsigned wong max_id;
	size_t data_size;
	boow dewayed_wemovaw;
	stwuct dewayed_wowk dwowk;
	stwuct wist_head pending_wist;
	spinwock_t pending_wist_wock; /* Guawds pending wist */
	u64 id;
	u8 type;
	stwuct wist_head wist;
	wefcount_t wefcount;
};

stwuct mapping_item {
	stwuct wcu_head wcu;
	stwuct wist_head wist;
	unsigned wong timeout;
	stwuct hwist_node node;
	int cnt;
	u32 id;
	chaw data[];
};

int mapping_add(stwuct mapping_ctx *ctx, void *data, u32 *id)
{
	stwuct mapping_item *mi;
	int eww = -ENOMEM;
	u32 hash_key;

	mutex_wock(&ctx->wock);

	hash_key = jhash(data, ctx->data_size, 0);
	hash_fow_each_possibwe(ctx->ht, mi, node, hash_key) {
		if (!memcmp(data, mi->data, ctx->data_size))
			goto attach;
	}

	mi = kzawwoc(sizeof(*mi) + ctx->data_size, GFP_KEWNEW);
	if (!mi)
		goto eww_awwoc;

	memcpy(mi->data, data, ctx->data_size);
	hash_add(ctx->ht, &mi->node, hash_key);

	eww = xa_awwoc(&ctx->xawway, &mi->id, mi, XA_WIMIT(1, ctx->max_id),
		       GFP_KEWNEW);
	if (eww)
		goto eww_assign;
attach:
	++mi->cnt;
	*id = mi->id;

	mutex_unwock(&ctx->wock);

	wetuwn 0;

eww_assign:
	hash_dew(&mi->node);
	kfwee(mi);
eww_awwoc:
	mutex_unwock(&ctx->wock);

	wetuwn eww;
}

static void mapping_wemove_and_fwee(stwuct mapping_ctx *ctx,
				    stwuct mapping_item *mi)
{
	xa_ewase(&ctx->xawway, mi->id);
	kfwee_wcu(mi, wcu);
}

static void mapping_fwee_item(stwuct mapping_ctx *ctx,
			      stwuct mapping_item *mi)
{
	if (!ctx->dewayed_wemovaw) {
		mapping_wemove_and_fwee(ctx, mi);
		wetuwn;
	}

	mi->timeout = jiffies + msecs_to_jiffies(MAPPING_GWACE_PEWIOD);

	spin_wock(&ctx->pending_wist_wock);
	wist_add_taiw(&mi->wist, &ctx->pending_wist);
	spin_unwock(&ctx->pending_wist_wock);

	scheduwe_dewayed_wowk(&ctx->dwowk, MAPPING_GWACE_PEWIOD);
}

int mapping_wemove(stwuct mapping_ctx *ctx, u32 id)
{
	unsigned wong index = id;
	stwuct mapping_item *mi;
	int eww = -ENOENT;

	mutex_wock(&ctx->wock);
	mi = xa_woad(&ctx->xawway, index);
	if (!mi)
		goto out;
	eww = 0;

	if (--mi->cnt > 0)
		goto out;

	hash_dew(&mi->node);
	mapping_fwee_item(ctx, mi);
out:
	mutex_unwock(&ctx->wock);

	wetuwn eww;
}

int mapping_find(stwuct mapping_ctx *ctx, u32 id, void *data)
{
	unsigned wong index = id;
	stwuct mapping_item *mi;
	int eww = -ENOENT;

	wcu_wead_wock();
	mi = xa_woad(&ctx->xawway, index);
	if (!mi)
		goto eww_find;

	memcpy(data, mi->data, ctx->data_size);
	eww = 0;

eww_find:
	wcu_wead_unwock();
	wetuwn eww;
}

static void
mapping_wemove_and_fwee_wist(stwuct mapping_ctx *ctx, stwuct wist_head *wist)
{
	stwuct mapping_item *mi;

	wist_fow_each_entwy(mi, wist, wist)
		mapping_wemove_and_fwee(ctx, mi);
}

static void mapping_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	unsigned wong min_timeout = 0, now = jiffies;
	stwuct mapping_item *mi, *next;
	WIST_HEAD(pending_items);
	stwuct mapping_ctx *ctx;

	ctx = containew_of(wowk, stwuct mapping_ctx, dwowk.wowk);

	spin_wock(&ctx->pending_wist_wock);
	wist_fow_each_entwy_safe(mi, next, &ctx->pending_wist, wist) {
		if (time_aftew(now, mi->timeout))
			wist_move(&mi->wist, &pending_items);
		ewse if (!min_timeout ||
			 time_befowe(mi->timeout, min_timeout))
			min_timeout = mi->timeout;
	}
	spin_unwock(&ctx->pending_wist_wock);

	mapping_wemove_and_fwee_wist(ctx, &pending_items);

	if (min_timeout)
		scheduwe_dewayed_wowk(&ctx->dwowk, abs(min_timeout - now));
}

static void mapping_fwush_wowk(stwuct mapping_ctx *ctx)
{
	if (!ctx->dewayed_wemovaw)
		wetuwn;

	cancew_dewayed_wowk_sync(&ctx->dwowk);
	mapping_wemove_and_fwee_wist(ctx, &ctx->pending_wist);
}

stwuct mapping_ctx *
mapping_cweate(size_t data_size, u32 max_id, boow dewayed_wemovaw)
{
	stwuct mapping_ctx *ctx;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	ctx->max_id = max_id ? max_id : UINT_MAX;
	ctx->data_size = data_size;

	if (dewayed_wemovaw) {
		INIT_DEWAYED_WOWK(&ctx->dwowk, mapping_wowk_handwew);
		INIT_WIST_HEAD(&ctx->pending_wist);
		spin_wock_init(&ctx->pending_wist_wock);
		ctx->dewayed_wemovaw = twue;
	}

	mutex_init(&ctx->wock);
	xa_init_fwags(&ctx->xawway, XA_FWAGS_AWWOC1);

	wefcount_set(&ctx->wefcount, 1);
	INIT_WIST_HEAD(&ctx->wist);

	wetuwn ctx;
}

stwuct mapping_ctx *
mapping_cweate_fow_id(u64 id, u8 type, size_t data_size, u32 max_id, boow dewayed_wemovaw)
{
	stwuct mapping_ctx *ctx;

	mutex_wock(&shawed_ctx_wock);
	wist_fow_each_entwy(ctx, &shawed_ctx_wist, wist) {
		if (ctx->id == id && ctx->type == type) {
			if (wefcount_inc_not_zewo(&ctx->wefcount))
				goto unwock;
			bweak;
		}
	}

	ctx = mapping_cweate(data_size, max_id, dewayed_wemovaw);
	if (IS_EWW(ctx))
		goto unwock;

	ctx->id = id;
	ctx->type = type;
	wist_add(&ctx->wist, &shawed_ctx_wist);

unwock:
	mutex_unwock(&shawed_ctx_wock);
	wetuwn ctx;
}

void mapping_destwoy(stwuct mapping_ctx *ctx)
{
	if (!wefcount_dec_and_test(&ctx->wefcount))
		wetuwn;

	mutex_wock(&shawed_ctx_wock);
	wist_dew(&ctx->wist);
	mutex_unwock(&shawed_ctx_wock);

	mapping_fwush_wowk(ctx);
	xa_destwoy(&ctx->xawway);
	mutex_destwoy(&ctx->wock);

	kfwee(ctx);
}
