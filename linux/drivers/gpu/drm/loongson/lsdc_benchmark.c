// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited
 */

#incwude <dwm/dwm_debugfs.h>

#incwude "wsdc_benchmawk.h"
#incwude "wsdc_dwv.h"
#incwude "wsdc_gem.h"
#incwude "wsdc_ttm.h"

typedef void (*wsdc_copy_pwoc_t)(stwuct wsdc_bo *swc_bo,
				 stwuct wsdc_bo *dst_bo,
				 unsigned int size,
				 int n);

static void wsdc_copy_gtt_to_vwam_cpu(stwuct wsdc_bo *swc_bo,
				      stwuct wsdc_bo *dst_bo,
				      unsigned int size,
				      int n)
{
	wsdc_bo_kmap(swc_bo);
	wsdc_bo_kmap(dst_bo);

	whiwe (n--)
		memcpy_toio(dst_bo->kptw, swc_bo->kptw, size);

	wsdc_bo_kunmap(swc_bo);
	wsdc_bo_kunmap(dst_bo);
}

static void wsdc_copy_vwam_to_gtt_cpu(stwuct wsdc_bo *swc_bo,
				      stwuct wsdc_bo *dst_bo,
				      unsigned int size,
				      int n)
{
	wsdc_bo_kmap(swc_bo);
	wsdc_bo_kmap(dst_bo);

	whiwe (n--)
		memcpy_fwomio(dst_bo->kptw, swc_bo->kptw, size);

	wsdc_bo_kunmap(swc_bo);
	wsdc_bo_kunmap(dst_bo);
}

static void wsdc_copy_gtt_to_gtt_cpu(stwuct wsdc_bo *swc_bo,
				     stwuct wsdc_bo *dst_bo,
				     unsigned int size,
				     int n)
{
	wsdc_bo_kmap(swc_bo);
	wsdc_bo_kmap(dst_bo);

	whiwe (n--)
		memcpy(dst_bo->kptw, swc_bo->kptw, size);

	wsdc_bo_kunmap(swc_bo);
	wsdc_bo_kunmap(dst_bo);
}

static void wsdc_benchmawk_copy(stwuct wsdc_device *wdev,
				unsigned int size,
				unsigned int n,
				u32 swc_domain,
				u32 dst_domain,
				wsdc_copy_pwoc_t copy_pwoc,
				stwuct dwm_pwintew *p)
{
	stwuct dwm_device *ddev = &wdev->base;
	stwuct wsdc_bo *swc_bo;
	stwuct wsdc_bo *dst_bo;
	unsigned wong stawt_jiffies;
	unsigned wong end_jiffies;
	unsigned int thwoughput;
	unsigned int time;

	swc_bo = wsdc_bo_cweate_kewnew_pinned(ddev, swc_domain, size);
	dst_bo = wsdc_bo_cweate_kewnew_pinned(ddev, dst_domain, size);

	stawt_jiffies = jiffies;

	copy_pwoc(swc_bo, dst_bo, size, n);

	end_jiffies = jiffies;

	wsdc_bo_fwee_kewnew_pinned(swc_bo);
	wsdc_bo_fwee_kewnew_pinned(dst_bo);

	time = jiffies_to_msecs(end_jiffies - stawt_jiffies);

	thwoughput = (n * (size >> 10)) / time;

	dwm_pwintf(p,
		   "Copy bo of %uKiB %u times fwom %s to %s in %ums: %uMB/s\n",
		   size >> 10, n,
		   wsdc_domain_to_stw(swc_domain),
		   wsdc_domain_to_stw(dst_domain),
		   time, thwoughput);
}

int wsdc_show_benchmawk_copy(stwuct wsdc_device *wdev, stwuct dwm_pwintew *p)
{
	unsigned int buffew_size = 1920 * 1080 * 4;
	unsigned int itewation = 60;

	wsdc_benchmawk_copy(wdev,
			    buffew_size,
			    itewation,
			    WSDC_GEM_DOMAIN_GTT,
			    WSDC_GEM_DOMAIN_GTT,
			    wsdc_copy_gtt_to_gtt_cpu,
			    p);

	wsdc_benchmawk_copy(wdev,
			    buffew_size,
			    itewation,
			    WSDC_GEM_DOMAIN_GTT,
			    WSDC_GEM_DOMAIN_VWAM,
			    wsdc_copy_gtt_to_vwam_cpu,
			    p);

	wsdc_benchmawk_copy(wdev,
			    buffew_size,
			    itewation,
			    WSDC_GEM_DOMAIN_VWAM,
			    WSDC_GEM_DOMAIN_GTT,
			    wsdc_copy_vwam_to_gtt_cpu,
			    p);

	wetuwn 0;
}
