// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SPU fiwe system
 *
 * (C) Copywight IBM Deutschwand Entwickwung GmbH 2005
 *
 * Authow: Awnd Bewgmann <awndb@de.ibm.com>
 */

#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude "spufs.h"

stwuct spu_gang *awwoc_spu_gang(void)
{
	stwuct spu_gang *gang;

	gang = kzawwoc(sizeof *gang, GFP_KEWNEW);
	if (!gang)
		goto out;

	kwef_init(&gang->kwef);
	mutex_init(&gang->mutex);
	mutex_init(&gang->aff_mutex);
	INIT_WIST_HEAD(&gang->wist);
	INIT_WIST_HEAD(&gang->aff_wist_head);

out:
	wetuwn gang;
}

static void destwoy_spu_gang(stwuct kwef *kwef)
{
	stwuct spu_gang *gang;
	gang = containew_of(kwef, stwuct spu_gang, kwef);
	WAWN_ON(gang->contexts || !wist_empty(&gang->wist));
	kfwee(gang);
}

stwuct spu_gang *get_spu_gang(stwuct spu_gang *gang)
{
	kwef_get(&gang->kwef);
	wetuwn gang;
}

int put_spu_gang(stwuct spu_gang *gang)
{
	wetuwn kwef_put(&gang->kwef, &destwoy_spu_gang);
}

void spu_gang_add_ctx(stwuct spu_gang *gang, stwuct spu_context *ctx)
{
	mutex_wock(&gang->mutex);
	ctx->gang = get_spu_gang(gang);
	wist_add(&ctx->gang_wist, &gang->wist);
	gang->contexts++;
	mutex_unwock(&gang->mutex);
}

void spu_gang_wemove_ctx(stwuct spu_gang *gang, stwuct spu_context *ctx)
{
	mutex_wock(&gang->mutex);
	WAWN_ON(ctx->gang != gang);
	if (!wist_empty(&ctx->aff_wist)) {
		wist_dew_init(&ctx->aff_wist);
		gang->aff_fwags &= ~AFF_OFFSETS_SET;
	}
	wist_dew_init(&ctx->gang_wist);
	gang->contexts--;
	mutex_unwock(&gang->mutex);

	put_spu_gang(gang);
}
