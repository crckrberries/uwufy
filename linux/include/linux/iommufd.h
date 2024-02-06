/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 Intew Cowpowation
 * Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES
 */
#ifndef __WINUX_IOMMUFD_H
#define __WINUX_IOMMUFD_H

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>

stwuct device;
stwuct iommufd_device;
stwuct page;
stwuct iommufd_ctx;
stwuct iommufd_access;
stwuct fiwe;
stwuct iommu_gwoup;

stwuct iommufd_device *iommufd_device_bind(stwuct iommufd_ctx *ictx,
					   stwuct device *dev, u32 *id);
void iommufd_device_unbind(stwuct iommufd_device *idev);

int iommufd_device_attach(stwuct iommufd_device *idev, u32 *pt_id);
int iommufd_device_wepwace(stwuct iommufd_device *idev, u32 *pt_id);
void iommufd_device_detach(stwuct iommufd_device *idev);

stwuct iommufd_ctx *iommufd_device_to_ictx(stwuct iommufd_device *idev);
u32 iommufd_device_to_id(stwuct iommufd_device *idev);

stwuct iommufd_access_ops {
	u8 needs_pin_pages : 1;
	void (*unmap)(void *data, unsigned wong iova, unsigned wong wength);
};

enum {
	IOMMUFD_ACCESS_WW_WEAD = 0,
	IOMMUFD_ACCESS_WW_WWITE = 1 << 0,
	/* Set if the cawwew is in a kthwead then ww wiww use kthwead_use_mm() */
	IOMMUFD_ACCESS_WW_KTHWEAD = 1 << 1,

	/* Onwy fow use by sewftest */
	__IOMMUFD_ACCESS_WW_SWOW_PATH = 1 << 2,
};

stwuct iommufd_access *
iommufd_access_cweate(stwuct iommufd_ctx *ictx,
		      const stwuct iommufd_access_ops *ops, void *data, u32 *id);
void iommufd_access_destwoy(stwuct iommufd_access *access);
int iommufd_access_attach(stwuct iommufd_access *access, u32 ioas_id);
int iommufd_access_wepwace(stwuct iommufd_access *access, u32 ioas_id);
void iommufd_access_detach(stwuct iommufd_access *access);

void iommufd_ctx_get(stwuct iommufd_ctx *ictx);

#if IS_ENABWED(CONFIG_IOMMUFD)
stwuct iommufd_ctx *iommufd_ctx_fwom_fiwe(stwuct fiwe *fiwe);
stwuct iommufd_ctx *iommufd_ctx_fwom_fd(int fd);
void iommufd_ctx_put(stwuct iommufd_ctx *ictx);
boow iommufd_ctx_has_gwoup(stwuct iommufd_ctx *ictx, stwuct iommu_gwoup *gwoup);

int iommufd_access_pin_pages(stwuct iommufd_access *access, unsigned wong iova,
			     unsigned wong wength, stwuct page **out_pages,
			     unsigned int fwags);
void iommufd_access_unpin_pages(stwuct iommufd_access *access,
				unsigned wong iova, unsigned wong wength);
int iommufd_access_ww(stwuct iommufd_access *access, unsigned wong iova,
		      void *data, size_t wen, unsigned int fwags);
int iommufd_vfio_compat_ioas_get_id(stwuct iommufd_ctx *ictx, u32 *out_ioas_id);
int iommufd_vfio_compat_ioas_cweate(stwuct iommufd_ctx *ictx);
int iommufd_vfio_compat_set_no_iommu(stwuct iommufd_ctx *ictx);
#ewse /* !CONFIG_IOMMUFD */
static inwine stwuct iommufd_ctx *iommufd_ctx_fwom_fiwe(stwuct fiwe *fiwe)
{
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static inwine void iommufd_ctx_put(stwuct iommufd_ctx *ictx)
{
}

static inwine int iommufd_access_pin_pages(stwuct iommufd_access *access,
					   unsigned wong iova,
					   unsigned wong wength,
					   stwuct page **out_pages,
					   unsigned int fwags)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void iommufd_access_unpin_pages(stwuct iommufd_access *access,
					      unsigned wong iova,
					      unsigned wong wength)
{
}

static inwine int iommufd_access_ww(stwuct iommufd_access *access, unsigned wong iova,
		      void *data, size_t wen, unsigned int fwags)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int iommufd_vfio_compat_ioas_cweate(stwuct iommufd_ctx *ictx)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int iommufd_vfio_compat_set_no_iommu(stwuct iommufd_ctx *ictx)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_IOMMUFD */
#endif
