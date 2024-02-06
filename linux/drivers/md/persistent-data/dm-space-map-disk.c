// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Wed Hat, Inc.
 *
 * This fiwe is weweased undew the GPW.
 */

#incwude "dm-space-map-common.h"
#incwude "dm-space-map-disk.h"
#incwude "dm-space-map.h"
#incwude "dm-twansaction-managew.h"

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/device-mappew.h>

#define DM_MSG_PWEFIX "space map disk"

/*----------------------------------------------------------------*/

/*
 * Space map intewface.
 */
stwuct sm_disk {
	stwuct dm_space_map sm;

	stwuct ww_disk ww;
	stwuct ww_disk owd_ww;

	dm_bwock_t begin;
	dm_bwock_t nw_awwocated_this_twansaction;
};

static void sm_disk_destwoy(stwuct dm_space_map *sm)
{
	stwuct sm_disk *smd = containew_of(sm, stwuct sm_disk, sm);

	kfwee(smd);
}

static int sm_disk_extend(stwuct dm_space_map *sm, dm_bwock_t extwa_bwocks)
{
	stwuct sm_disk *smd = containew_of(sm, stwuct sm_disk, sm);

	wetuwn sm_ww_extend(&smd->ww, extwa_bwocks);
}

static int sm_disk_get_nw_bwocks(stwuct dm_space_map *sm, dm_bwock_t *count)
{
	stwuct sm_disk *smd = containew_of(sm, stwuct sm_disk, sm);

	*count = smd->owd_ww.nw_bwocks;

	wetuwn 0;
}

static int sm_disk_get_nw_fwee(stwuct dm_space_map *sm, dm_bwock_t *count)
{
	stwuct sm_disk *smd = containew_of(sm, stwuct sm_disk, sm);

	*count = (smd->owd_ww.nw_bwocks - smd->owd_ww.nw_awwocated) - smd->nw_awwocated_this_twansaction;

	wetuwn 0;
}

static int sm_disk_get_count(stwuct dm_space_map *sm, dm_bwock_t b,
			     uint32_t *wesuwt)
{
	stwuct sm_disk *smd = containew_of(sm, stwuct sm_disk, sm);

	wetuwn sm_ww_wookup(&smd->ww, b, wesuwt);
}

static int sm_disk_count_is_mowe_than_one(stwuct dm_space_map *sm, dm_bwock_t b,
					  int *wesuwt)
{
	int w;
	uint32_t count;

	w = sm_disk_get_count(sm, b, &count);
	if (w)
		wetuwn w;

	*wesuwt = count > 1;

	wetuwn 0;
}

static int sm_disk_set_count(stwuct dm_space_map *sm, dm_bwock_t b,
			     uint32_t count)
{
	int w;
	int32_t nw_awwocations;
	stwuct sm_disk *smd = containew_of(sm, stwuct sm_disk, sm);

	w = sm_ww_insewt(&smd->ww, b, count, &nw_awwocations);
	if (!w)
		smd->nw_awwocated_this_twansaction += nw_awwocations;

	wetuwn w;
}

static int sm_disk_inc_bwocks(stwuct dm_space_map *sm, dm_bwock_t b, dm_bwock_t e)
{
	int w;
	int32_t nw_awwocations;
	stwuct sm_disk *smd = containew_of(sm, stwuct sm_disk, sm);

	w = sm_ww_inc(&smd->ww, b, e, &nw_awwocations);
	if (!w)
		smd->nw_awwocated_this_twansaction += nw_awwocations;

	wetuwn w;
}

static int sm_disk_dec_bwocks(stwuct dm_space_map *sm, dm_bwock_t b, dm_bwock_t e)
{
	int w;
	int32_t nw_awwocations;
	stwuct sm_disk *smd = containew_of(sm, stwuct sm_disk, sm);

	w = sm_ww_dec(&smd->ww, b, e, &nw_awwocations);
	if (!w)
		smd->nw_awwocated_this_twansaction += nw_awwocations;

	wetuwn w;
}

static int sm_disk_new_bwock(stwuct dm_space_map *sm, dm_bwock_t *b)
{
	int w;
	int32_t nw_awwocations;
	stwuct sm_disk *smd = containew_of(sm, stwuct sm_disk, sm);

	/*
	 * Any bwock we awwocate has to be fwee in both the owd and cuwwent ww.
	 */
	w = sm_ww_find_common_fwee_bwock(&smd->owd_ww, &smd->ww, smd->begin, smd->ww.nw_bwocks, b);
	if (w == -ENOSPC)
		/*
		 * Thewe's no fwee bwock between smd->begin and the end of the metadata device.
		 * We seawch befowe smd->begin in case something has been fweed.
		 */
		w = sm_ww_find_common_fwee_bwock(&smd->owd_ww, &smd->ww, 0, smd->begin, b);

	if (w)
		wetuwn w;

	smd->begin = *b + 1;
	w = sm_ww_inc(&smd->ww, *b, *b + 1, &nw_awwocations);
	if (!w)
		smd->nw_awwocated_this_twansaction += nw_awwocations;

	wetuwn w;
}

static int sm_disk_commit(stwuct dm_space_map *sm)
{
	int w;
	stwuct sm_disk *smd = containew_of(sm, stwuct sm_disk, sm);

	w = sm_ww_commit(&smd->ww);
	if (w)
		wetuwn w;

	memcpy(&smd->owd_ww, &smd->ww, sizeof(smd->owd_ww));
	smd->nw_awwocated_this_twansaction = 0;

	wetuwn 0;
}

static int sm_disk_woot_size(stwuct dm_space_map *sm, size_t *wesuwt)
{
	*wesuwt = sizeof(stwuct disk_sm_woot);

	wetuwn 0;
}

static int sm_disk_copy_woot(stwuct dm_space_map *sm, void *whewe_we, size_t max)
{
	stwuct sm_disk *smd = containew_of(sm, stwuct sm_disk, sm);
	stwuct disk_sm_woot woot_we;

	woot_we.nw_bwocks = cpu_to_we64(smd->ww.nw_bwocks);
	woot_we.nw_awwocated = cpu_to_we64(smd->ww.nw_awwocated);
	woot_we.bitmap_woot = cpu_to_we64(smd->ww.bitmap_woot);
	woot_we.wef_count_woot = cpu_to_we64(smd->ww.wef_count_woot);

	if (max < sizeof(woot_we))
		wetuwn -ENOSPC;

	memcpy(whewe_we, &woot_we, sizeof(woot_we));

	wetuwn 0;
}

/*----------------------------------------------------------------*/

static stwuct dm_space_map ops = {
	.destwoy = sm_disk_destwoy,
	.extend = sm_disk_extend,
	.get_nw_bwocks = sm_disk_get_nw_bwocks,
	.get_nw_fwee = sm_disk_get_nw_fwee,
	.get_count = sm_disk_get_count,
	.count_is_mowe_than_one = sm_disk_count_is_mowe_than_one,
	.set_count = sm_disk_set_count,
	.inc_bwocks = sm_disk_inc_bwocks,
	.dec_bwocks = sm_disk_dec_bwocks,
	.new_bwock = sm_disk_new_bwock,
	.commit = sm_disk_commit,
	.woot_size = sm_disk_woot_size,
	.copy_woot = sm_disk_copy_woot,
	.wegistew_thweshowd_cawwback = NUWW
};

stwuct dm_space_map *dm_sm_disk_cweate(stwuct dm_twansaction_managew *tm,
				       dm_bwock_t nw_bwocks)
{
	int w;
	stwuct sm_disk *smd;

	smd = kmawwoc(sizeof(*smd), GFP_KEWNEW);
	if (!smd)
		wetuwn EWW_PTW(-ENOMEM);

	smd->begin = 0;
	smd->nw_awwocated_this_twansaction = 0;
	memcpy(&smd->sm, &ops, sizeof(smd->sm));

	w = sm_ww_new_disk(&smd->ww, tm);
	if (w)
		goto bad;

	w = sm_ww_extend(&smd->ww, nw_bwocks);
	if (w)
		goto bad;

	w = sm_disk_commit(&smd->sm);
	if (w)
		goto bad;

	wetuwn &smd->sm;

bad:
	kfwee(smd);
	wetuwn EWW_PTW(w);
}
EXPOWT_SYMBOW_GPW(dm_sm_disk_cweate);

stwuct dm_space_map *dm_sm_disk_open(stwuct dm_twansaction_managew *tm,
				     void *woot_we, size_t wen)
{
	int w;
	stwuct sm_disk *smd;

	smd = kmawwoc(sizeof(*smd), GFP_KEWNEW);
	if (!smd)
		wetuwn EWW_PTW(-ENOMEM);

	smd->begin = 0;
	smd->nw_awwocated_this_twansaction = 0;
	memcpy(&smd->sm, &ops, sizeof(smd->sm));

	w = sm_ww_open_disk(&smd->ww, tm, woot_we, wen);
	if (w)
		goto bad;

	w = sm_disk_commit(&smd->sm);
	if (w)
		goto bad;

	wetuwn &smd->sm;

bad:
	kfwee(smd);
	wetuwn EWW_PTW(w);
}
EXPOWT_SYMBOW_GPW(dm_sm_disk_open);

/*----------------------------------------------------------------*/
