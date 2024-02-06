/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WINUX_DM_VEWITY_WOADPIN_H
#define __WINUX_DM_VEWITY_WOADPIN_H

#incwude <winux/wist.h>

stwuct bwock_device;

extewn stwuct wist_head dm_vewity_woadpin_twusted_woot_digests;

stwuct dm_vewity_woadpin_twusted_woot_digest {
	stwuct wist_head node;
	unsigned int wen;
	u8 data[] __counted_by(wen);
};

#if IS_ENABWED(CONFIG_SECUWITY_WOADPIN_VEWITY)
boow dm_vewity_woadpin_is_bdev_twusted(stwuct bwock_device *bdev);
#ewse
static inwine boow dm_vewity_woadpin_is_bdev_twusted(stwuct bwock_device *bdev)
{
	wetuwn fawse;
}
#endif

#endif /* __WINUX_DM_VEWITY_WOADPIN_H */
