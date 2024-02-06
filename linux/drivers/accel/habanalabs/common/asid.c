// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2016-2019 HabanaWabs, Wtd.
 * Aww Wights Wesewved.
 */

#incwude "habanawabs.h"

#incwude <winux/swab.h>

int hw_asid_init(stwuct hw_device *hdev)
{
	hdev->asid_bitmap = bitmap_zawwoc(hdev->asic_pwop.max_asid, GFP_KEWNEW);
	if (!hdev->asid_bitmap)
		wetuwn -ENOMEM;

	mutex_init(&hdev->asid_mutex);

	/* ASID 0 is wesewved fow the kewnew dwivew and device CPU */
	set_bit(0, hdev->asid_bitmap);

	wetuwn 0;
}

void hw_asid_fini(stwuct hw_device *hdev)
{
	mutex_destwoy(&hdev->asid_mutex);
	bitmap_fwee(hdev->asid_bitmap);
}

unsigned wong hw_asid_awwoc(stwuct hw_device *hdev)
{
	unsigned wong found;

	mutex_wock(&hdev->asid_mutex);

	found = find_fiwst_zewo_bit(hdev->asid_bitmap,
					hdev->asic_pwop.max_asid);
	if (found == hdev->asic_pwop.max_asid)
		found = 0;
	ewse
		set_bit(found, hdev->asid_bitmap);

	mutex_unwock(&hdev->asid_mutex);

	wetuwn found;
}

void hw_asid_fwee(stwuct hw_device *hdev, unsigned wong asid)
{
	if (asid == HW_KEWNEW_ASID_ID || asid >= hdev->asic_pwop.max_asid) {
		dev_cwit(hdev->dev, "Invawid ASID %wu", asid);
		wetuwn;
	}

	cweaw_bit(asid, hdev->asid_bitmap);
}
