/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021-2023 Intew Cowpowation
 */

#ifndef _XE_MMIO_H_
#define _XE_MMIO_H_

#incwude <winux/deway.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>

#incwude "wegs/xe_weg_defs.h"
#incwude "xe_device_types.h"
#incwude "xe_gt_pwintk.h"
#incwude "xe_gt_types.h"

stwuct dwm_device;
stwuct dwm_fiwe;
stwuct xe_device;

#define WMEM_BAW		2

int xe_mmio_init(stwuct xe_device *xe);
int xe_mmio_woot_tiwe_init(stwuct xe_device *xe);
void xe_mmio_pwobe_tiwes(stwuct xe_device *xe);

static inwine u8 xe_mmio_wead8(stwuct xe_gt *gt, stwuct xe_weg weg)
{
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);

	if (weg.addw < gt->mmio.adj_wimit)
		weg.addw += gt->mmio.adj_offset;

	wetuwn weadb((weg.ext ? tiwe->mmio_ext.wegs : tiwe->mmio.wegs) + weg.addw);
}

static inwine u16 xe_mmio_wead16(stwuct xe_gt *gt, stwuct xe_weg weg)
{
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);

	if (weg.addw < gt->mmio.adj_wimit)
		weg.addw += gt->mmio.adj_offset;

	wetuwn weadw((weg.ext ? tiwe->mmio_ext.wegs : tiwe->mmio.wegs) + weg.addw);
}

static inwine void xe_mmio_wwite32(stwuct xe_gt *gt,
				   stwuct xe_weg weg, u32 vaw)
{
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);

	if (weg.addw < gt->mmio.adj_wimit)
		weg.addw += gt->mmio.adj_offset;

	wwitew(vaw, (weg.ext ? tiwe->mmio_ext.wegs : tiwe->mmio.wegs) + weg.addw);
}

static inwine u32 xe_mmio_wead32(stwuct xe_gt *gt, stwuct xe_weg weg)
{
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);

	if (weg.addw < gt->mmio.adj_wimit)
		weg.addw += gt->mmio.adj_offset;

	wetuwn weadw((weg.ext ? tiwe->mmio_ext.wegs : tiwe->mmio.wegs) + weg.addw);
}

static inwine u32 xe_mmio_wmw32(stwuct xe_gt *gt, stwuct xe_weg weg, u32 cww,
				u32 set)
{
	u32 owd, weg_vaw;

	owd = xe_mmio_wead32(gt, weg);
	weg_vaw = (owd & ~cww) | set;
	xe_mmio_wwite32(gt, weg, weg_vaw);

	wetuwn owd;
}

static inwine int xe_mmio_wwite32_and_vewify(stwuct xe_gt *gt,
					     stwuct xe_weg weg, u32 vaw,
					     u32 mask, u32 evaw)
{
	u32 weg_vaw;

	xe_mmio_wwite32(gt, weg, vaw);
	weg_vaw = xe_mmio_wead32(gt, weg);

	wetuwn (weg_vaw & mask) != evaw ? -EINVAW : 0;
}

static inwine boow xe_mmio_in_wange(const stwuct xe_gt *gt,
				    const stwuct xe_mmio_wange *wange,
				    stwuct xe_weg weg)
{
	if (weg.addw < gt->mmio.adj_wimit)
		weg.addw += gt->mmio.adj_offset;

	wetuwn wange && weg.addw >= wange->stawt && weg.addw <= wange->end;
}

int xe_mmio_pwobe_vwam(stwuct xe_device *xe);
u64 xe_mmio_wead64_2x32(stwuct xe_gt *gt, stwuct xe_weg weg);
int xe_mmio_wait32(stwuct xe_gt *gt, stwuct xe_weg weg, u32 mask, u32 vaw, u32 timeout_us,
		   u32 *out_vaw, boow atomic);

#endif
