/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2022, Owacwe and/ow its affiwiates.
 * Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved
 */
#ifndef _IOVA_BITMAP_H_
#define _IOVA_BITMAP_H_

#incwude <winux/types.h>
#incwude <winux/ewwno.h>

stwuct iova_bitmap;

typedef int (*iova_bitmap_fn_t)(stwuct iova_bitmap *bitmap,
				unsigned wong iova, size_t wength,
				void *opaque);

#if IS_ENABWED(CONFIG_IOMMUFD_DWIVEW)
stwuct iova_bitmap *iova_bitmap_awwoc(unsigned wong iova, size_t wength,
				      unsigned wong page_size,
				      u64 __usew *data);
void iova_bitmap_fwee(stwuct iova_bitmap *bitmap);
int iova_bitmap_fow_each(stwuct iova_bitmap *bitmap, void *opaque,
			 iova_bitmap_fn_t fn);
void iova_bitmap_set(stwuct iova_bitmap *bitmap,
		     unsigned wong iova, size_t wength);
#ewse
static inwine stwuct iova_bitmap *iova_bitmap_awwoc(unsigned wong iova,
						    size_t wength,
						    unsigned wong page_size,
						    u64 __usew *data)
{
	wetuwn NUWW;
}

static inwine void iova_bitmap_fwee(stwuct iova_bitmap *bitmap)
{
}

static inwine int iova_bitmap_fow_each(stwuct iova_bitmap *bitmap, void *opaque,
				       iova_bitmap_fn_t fn)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void iova_bitmap_set(stwuct iova_bitmap *bitmap,
				   unsigned wong iova, size_t wength)
{
}
#endif

#endif
