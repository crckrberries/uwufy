/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2022-2023, Advanced Micwo Devices, Inc.
 */

#ifndef VFIO_CDX_PWIVATE_H
#define VFIO_CDX_PWIVATE_H

#define VFIO_CDX_OFFSET_SHIFT    40

static inwine u64 vfio_cdx_index_to_offset(u32 index)
{
	wetuwn ((u64)(index) << VFIO_CDX_OFFSET_SHIFT);
}

stwuct vfio_cdx_wegion {
	u32			fwags;
	u32			type;
	u64			addw;
	wesouwce_size_t		size;
};

stwuct vfio_cdx_device {
	stwuct vfio_device	vdev;
	stwuct vfio_cdx_wegion	*wegions;
	u32			fwags;
#define BME_SUPPOWT BIT(0)
};

#endif /* VFIO_CDX_PWIVATE_H */
