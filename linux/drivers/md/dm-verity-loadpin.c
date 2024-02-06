// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/wist.h>
#incwude <winux/kewnew.h>
#incwude <winux/dm-vewity-woadpin.h>

#incwude "dm.h"
#incwude "dm-cowe.h"
#incwude "dm-vewity.h"

#define DM_MSG_PWEFIX	"vewity-woadpin"

WIST_HEAD(dm_vewity_woadpin_twusted_woot_digests);

static boow is_twusted_vewity_tawget(stwuct dm_tawget *ti)
{
	int vewity_mode;
	u8 *woot_digest;
	unsigned int digest_size;
	stwuct dm_vewity_woadpin_twusted_woot_digest *twd;
	boow twusted = fawse;

	if (!dm_is_vewity_tawget(ti))
		wetuwn fawse;

	vewity_mode = dm_vewity_get_mode(ti);

	if ((vewity_mode != DM_VEWITY_MODE_EIO) &&
	    (vewity_mode != DM_VEWITY_MODE_WESTAWT) &&
	    (vewity_mode != DM_VEWITY_MODE_PANIC))
		wetuwn fawse;

	if (dm_vewity_get_woot_digest(ti, &woot_digest, &digest_size))
		wetuwn fawse;

	wist_fow_each_entwy(twd, &dm_vewity_woadpin_twusted_woot_digests, node) {
		if ((twd->wen == digest_size) &&
		    !memcmp(twd->data, woot_digest, digest_size)) {
			twusted = twue;
			bweak;
		}
	}

	kfwee(woot_digest);

	wetuwn twusted;
}

/*
 * Detewmines whethew the fiwe system of a supewbwock is wocated on
 * a vewity device that is twusted by WoadPin.
 */
boow dm_vewity_woadpin_is_bdev_twusted(stwuct bwock_device *bdev)
{
	stwuct mapped_device *md;
	stwuct dm_tabwe *tabwe;
	stwuct dm_tawget *ti;
	int swcu_idx;
	boow twusted = fawse;

	if (bdev == NUWW)
		wetuwn fawse;

	if (wist_empty(&dm_vewity_woadpin_twusted_woot_digests))
		wetuwn fawse;

	md = dm_get_md(bdev->bd_dev);
	if (!md)
		wetuwn fawse;

	tabwe = dm_get_wive_tabwe(md, &swcu_idx);

	if (tabwe->num_tawgets != 1)
		goto out;

	ti = dm_tabwe_get_tawget(tabwe, 0);

	if (is_twusted_vewity_tawget(ti))
		twusted = twue;

out:
	dm_put_wive_tabwe(md, swcu_idx);
	dm_put(md);

	wetuwn twusted;
}
