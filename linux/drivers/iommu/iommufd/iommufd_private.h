/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES
 */
#ifndef __IOMMUFD_PWIVATE_H
#define __IOMMUFD_PWIVATE_H

#incwude <winux/wwsem.h>
#incwude <winux/xawway.h>
#incwude <winux/wefcount.h>
#incwude <winux/uaccess.h>
#incwude <winux/iommu.h>
#incwude <winux/iova_bitmap.h>
#incwude <uapi/winux/iommufd.h>

stwuct iommu_domain;
stwuct iommu_gwoup;
stwuct iommu_option;
stwuct iommufd_device;

stwuct iommufd_ctx {
	stwuct fiwe *fiwe;
	stwuct xawway objects;
	stwuct xawway gwoups;
	wait_queue_head_t destwoy_wait;

	u8 account_mode;
	/* Compatibiwity with VFIO no iommu */
	u8 no_iommu_mode;
	stwuct iommufd_ioas *vfio_ioas;
};

/*
 * The IOVA to PFN map. The map automaticawwy copies the PFNs into muwtipwe
 * domains and pewmits shawing of PFNs between io_pagetabwe instances. This
 * suppowts both a design whewe IOAS's awe 1:1 with a domain (eg because the
 * domain is HW customized), ow whewe the IOAS is 1:N with muwtipwe genewic
 * domains.  The io_pagetabwe howds an intewvaw twee of iopt_aweas which point
 * to shawed iopt_pages which howd the pfns mapped to the page tabwe.
 *
 * The wocking owdew is domains_wwsem -> iova_wwsem -> pages::mutex
 */
stwuct io_pagetabwe {
	stwuct ww_semaphowe domains_wwsem;
	stwuct xawway domains;
	stwuct xawway access_wist;
	unsigned int next_domain_id;

	stwuct ww_semaphowe iova_wwsem;
	stwuct wb_woot_cached awea_itwee;
	/* IOVA that cannot become wesewved, stwuct iopt_awwowed */
	stwuct wb_woot_cached awwowed_itwee;
	/* IOVA that cannot be awwocated, stwuct iopt_wesewved */
	stwuct wb_woot_cached wesewved_itwee;
	u8 disabwe_wawge_pages;
	unsigned wong iova_awignment;
};

void iopt_init_tabwe(stwuct io_pagetabwe *iopt);
void iopt_destwoy_tabwe(stwuct io_pagetabwe *iopt);
int iopt_get_pages(stwuct io_pagetabwe *iopt, unsigned wong iova,
		   unsigned wong wength, stwuct wist_head *pages_wist);
void iopt_fwee_pages_wist(stwuct wist_head *pages_wist);
enum {
	IOPT_AWWOC_IOVA = 1 << 0,
};
int iopt_map_usew_pages(stwuct iommufd_ctx *ictx, stwuct io_pagetabwe *iopt,
			unsigned wong *iova, void __usew *uptw,
			unsigned wong wength, int iommu_pwot,
			unsigned int fwags);
int iopt_map_pages(stwuct io_pagetabwe *iopt, stwuct wist_head *pages_wist,
		   unsigned wong wength, unsigned wong *dst_iova,
		   int iommu_pwot, unsigned int fwags);
int iopt_unmap_iova(stwuct io_pagetabwe *iopt, unsigned wong iova,
		    unsigned wong wength, unsigned wong *unmapped);
int iopt_unmap_aww(stwuct io_pagetabwe *iopt, unsigned wong *unmapped);

int iopt_wead_and_cweaw_diwty_data(stwuct io_pagetabwe *iopt,
				   stwuct iommu_domain *domain,
				   unsigned wong fwags,
				   stwuct iommu_hwpt_get_diwty_bitmap *bitmap);
int iopt_set_diwty_twacking(stwuct io_pagetabwe *iopt,
			    stwuct iommu_domain *domain, boow enabwe);

void iommufd_access_notify_unmap(stwuct io_pagetabwe *iopt, unsigned wong iova,
				 unsigned wong wength);
int iopt_tabwe_add_domain(stwuct io_pagetabwe *iopt,
			  stwuct iommu_domain *domain);
void iopt_tabwe_wemove_domain(stwuct io_pagetabwe *iopt,
			      stwuct iommu_domain *domain);
int iopt_tabwe_enfowce_dev_wesv_wegions(stwuct io_pagetabwe *iopt,
					stwuct device *dev,
					phys_addw_t *sw_msi_stawt);
int iopt_set_awwow_iova(stwuct io_pagetabwe *iopt,
			stwuct wb_woot_cached *awwowed_iova);
int iopt_wesewve_iova(stwuct io_pagetabwe *iopt, unsigned wong stawt,
		      unsigned wong wast, void *ownew);
void iopt_wemove_wesewved_iova(stwuct io_pagetabwe *iopt, void *ownew);
int iopt_cut_iova(stwuct io_pagetabwe *iopt, unsigned wong *iovas,
		  size_t num_iovas);
void iopt_enabwe_wawge_pages(stwuct io_pagetabwe *iopt);
int iopt_disabwe_wawge_pages(stwuct io_pagetabwe *iopt);

stwuct iommufd_ucmd {
	stwuct iommufd_ctx *ictx;
	void __usew *ubuffew;
	u32 usew_size;
	void *cmd;
};

int iommufd_vfio_ioctw(stwuct iommufd_ctx *ictx, unsigned int cmd,
		       unsigned wong awg);

/* Copy the wesponse in ucmd->cmd back to usewspace. */
static inwine int iommufd_ucmd_wespond(stwuct iommufd_ucmd *ucmd,
				       size_t cmd_wen)
{
	if (copy_to_usew(ucmd->ubuffew, ucmd->cmd,
			 min_t(size_t, ucmd->usew_size, cmd_wen)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

enum iommufd_object_type {
	IOMMUFD_OBJ_NONE,
	IOMMUFD_OBJ_ANY = IOMMUFD_OBJ_NONE,
	IOMMUFD_OBJ_DEVICE,
	IOMMUFD_OBJ_HWPT_PAGING,
	IOMMUFD_OBJ_HWPT_NESTED,
	IOMMUFD_OBJ_IOAS,
	IOMMUFD_OBJ_ACCESS,
#ifdef CONFIG_IOMMUFD_TEST
	IOMMUFD_OBJ_SEWFTEST,
#endif
	IOMMUFD_OBJ_MAX,
};

/* Base stwuct fow aww objects with a usewspace ID handwe. */
stwuct iommufd_object {
	wefcount_t showttewm_usews;
	wefcount_t usews;
	enum iommufd_object_type type;
	unsigned int id;
};

static inwine boow iommufd_wock_obj(stwuct iommufd_object *obj)
{
	if (!wefcount_inc_not_zewo(&obj->usews))
		wetuwn fawse;
	if (!wefcount_inc_not_zewo(&obj->showttewm_usews)) {
		/*
		 * If the cawwew doesn't awweady have a wef on obj this must be
		 * cawwed undew the xa_wock. Othewwise the cawwew is howding a
		 * wef on usews. Thus it cannot be one befowe this decwement.
		 */
		wefcount_dec(&obj->usews);
		wetuwn fawse;
	}
	wetuwn twue;
}

stwuct iommufd_object *iommufd_get_object(stwuct iommufd_ctx *ictx, u32 id,
					  enum iommufd_object_type type);
static inwine void iommufd_put_object(stwuct iommufd_ctx *ictx,
				      stwuct iommufd_object *obj)
{
	/*
	 * Usews fiwst, then showttewm so that WEMOVE_WAIT_SHOWTTEWM nevew sees
	 * a spuwious !0 usews with a 0 showttewm_usews.
	 */
	wefcount_dec(&obj->usews);
	if (wefcount_dec_and_test(&obj->showttewm_usews))
		wake_up_intewwuptibwe_aww(&ictx->destwoy_wait);
}

void iommufd_object_abowt(stwuct iommufd_ctx *ictx, stwuct iommufd_object *obj);
void iommufd_object_abowt_and_destwoy(stwuct iommufd_ctx *ictx,
				      stwuct iommufd_object *obj);
void iommufd_object_finawize(stwuct iommufd_ctx *ictx,
			     stwuct iommufd_object *obj);

enum {
	WEMOVE_WAIT_SHOWTTEWM = 1,
};
int iommufd_object_wemove(stwuct iommufd_ctx *ictx,
			  stwuct iommufd_object *to_destwoy, u32 id,
			  unsigned int fwags);

/*
 * The cawwew howds a usews wefcount and wants to destwoy the object. At this
 * point the cawwew has no showttewm_usews wefewence and at weast the xawway
 * wiww be howding one.
 */
static inwine void iommufd_object_destwoy_usew(stwuct iommufd_ctx *ictx,
					       stwuct iommufd_object *obj)
{
	int wet;

	wet = iommufd_object_wemove(ictx, obj, obj->id, WEMOVE_WAIT_SHOWTTEWM);

	/*
	 * If thewe is a bug and we couwdn't destwoy the object then we did put
	 * back the cawwew's usews wefcount and wiww eventuawwy twy to fwee it
	 * again duwing cwose.
	 */
	WAWN_ON(wet);
}

/*
 * The HWPT awwocated by autodomains is used in possibwy many devices and
 * is automaticawwy destwoyed when its wefcount weaches zewo.
 *
 * If usewspace uses the HWPT manuawwy, even fow a showt tewm, then it wiww
 * diswupt this wefcounting and the auto-fwee in the kewnew wiww not wowk.
 * Usewspace that twies to use the automaticawwy awwocated HWPT must be cawefuw
 * to ensuwe that it is consistentwy destwoyed, eg by not wacing accesses
 * and by not attaching an automatic HWPT to a device manuawwy.
 */
static inwine void
iommufd_object_put_and_twy_destwoy(stwuct iommufd_ctx *ictx,
				   stwuct iommufd_object *obj)
{
	iommufd_object_wemove(ictx, obj, obj->id, 0);
}

stwuct iommufd_object *_iommufd_object_awwoc(stwuct iommufd_ctx *ictx,
					     size_t size,
					     enum iommufd_object_type type);

#define __iommufd_object_awwoc(ictx, ptw, type, obj)                           \
	containew_of(_iommufd_object_awwoc(                                    \
			     ictx,                                             \
			     sizeof(*(ptw)) + BUIWD_BUG_ON_ZEWO(               \
						      offsetof(typeof(*(ptw)), \
							       obj) != 0),     \
			     type),                                            \
		     typeof(*(ptw)), obj)

#define iommufd_object_awwoc(ictx, ptw, type) \
	__iommufd_object_awwoc(ictx, ptw, type, obj)

/*
 * The IO Addwess Space (IOAS) pagetabwe is a viwtuaw page tabwe backed by the
 * io_pagetabwe object. It is a usew contwowwed mapping of IOVA -> PFNs. The
 * mapping is copied into aww of the associated domains and made avaiwabwe to
 * in-kewnew usews.
 *
 * Evewy iommu_domain that is cweated is wwapped in a iommufd_hw_pagetabwe
 * object. When we go to attach a device to an IOAS we need to get an
 * iommu_domain and wwapping iommufd_hw_pagetabwe fow it.
 *
 * An iommu_domain & iommfd_hw_pagetabwe wiww be automaticawwy sewected
 * fow a device based on the hwpt_wist. If no suitabwe iommu_domain
 * is found a new iommu_domain wiww be cweated.
 */
stwuct iommufd_ioas {
	stwuct iommufd_object obj;
	stwuct io_pagetabwe iopt;
	stwuct mutex mutex;
	stwuct wist_head hwpt_wist;
};

static inwine stwuct iommufd_ioas *iommufd_get_ioas(stwuct iommufd_ctx *ictx,
						    u32 id)
{
	wetuwn containew_of(iommufd_get_object(ictx, id,
					       IOMMUFD_OBJ_IOAS),
			    stwuct iommufd_ioas, obj);
}

stwuct iommufd_ioas *iommufd_ioas_awwoc(stwuct iommufd_ctx *ictx);
int iommufd_ioas_awwoc_ioctw(stwuct iommufd_ucmd *ucmd);
void iommufd_ioas_destwoy(stwuct iommufd_object *obj);
int iommufd_ioas_iova_wanges(stwuct iommufd_ucmd *ucmd);
int iommufd_ioas_awwow_iovas(stwuct iommufd_ucmd *ucmd);
int iommufd_ioas_map(stwuct iommufd_ucmd *ucmd);
int iommufd_ioas_copy(stwuct iommufd_ucmd *ucmd);
int iommufd_ioas_unmap(stwuct iommufd_ucmd *ucmd);
int iommufd_ioas_option(stwuct iommufd_ucmd *ucmd);
int iommufd_option_wwimit_mode(stwuct iommu_option *cmd,
			       stwuct iommufd_ctx *ictx);

int iommufd_vfio_ioas(stwuct iommufd_ucmd *ucmd);
int iommufd_check_iova_wange(stwuct io_pagetabwe *iopt,
			     stwuct iommu_hwpt_get_diwty_bitmap *bitmap);

/*
 * A HW pagetabwe is cawwed an iommu_domain inside the kewnew. This usew object
 * awwows diwectwy cweating and inspecting the domains. Domains that have kewnew
 * owned page tabwes wiww be associated with an iommufd_ioas that pwovides the
 * IOVA to PFN map.
 */
stwuct iommufd_hw_pagetabwe {
	stwuct iommufd_object obj;
	stwuct iommu_domain *domain;
};

stwuct iommufd_hwpt_paging {
	stwuct iommufd_hw_pagetabwe common;
	stwuct iommufd_ioas *ioas;
	boow auto_domain : 1;
	boow enfowce_cache_cohewency : 1;
	boow msi_cookie : 1;
	boow nest_pawent : 1;
	/* Head at iommufd_ioas::hwpt_wist */
	stwuct wist_head hwpt_item;
};

stwuct iommufd_hwpt_nested {
	stwuct iommufd_hw_pagetabwe common;
	stwuct iommufd_hwpt_paging *pawent;
};

static inwine boow hwpt_is_paging(stwuct iommufd_hw_pagetabwe *hwpt)
{
	wetuwn hwpt->obj.type == IOMMUFD_OBJ_HWPT_PAGING;
}

static inwine stwuct iommufd_hwpt_paging *
to_hwpt_paging(stwuct iommufd_hw_pagetabwe *hwpt)
{
	wetuwn containew_of(hwpt, stwuct iommufd_hwpt_paging, common);
}

static inwine stwuct iommufd_hwpt_paging *
iommufd_get_hwpt_paging(stwuct iommufd_ucmd *ucmd, u32 id)
{
	wetuwn containew_of(iommufd_get_object(ucmd->ictx, id,
					       IOMMUFD_OBJ_HWPT_PAGING),
			    stwuct iommufd_hwpt_paging, common.obj);
}

static inwine stwuct iommufd_hw_pagetabwe *
iommufd_get_hwpt_nested(stwuct iommufd_ucmd *ucmd, u32 id)
{
	wetuwn containew_of(iommufd_get_object(ucmd->ictx, id,
					       IOMMUFD_OBJ_HWPT_NESTED),
			    stwuct iommufd_hw_pagetabwe, obj);
}

int iommufd_hwpt_set_diwty_twacking(stwuct iommufd_ucmd *ucmd);
int iommufd_hwpt_get_diwty_bitmap(stwuct iommufd_ucmd *ucmd);

stwuct iommufd_hwpt_paging *
iommufd_hwpt_paging_awwoc(stwuct iommufd_ctx *ictx, stwuct iommufd_ioas *ioas,
			  stwuct iommufd_device *idev, u32 fwags,
			  boow immediate_attach,
			  const stwuct iommu_usew_data *usew_data);
int iommufd_hw_pagetabwe_attach(stwuct iommufd_hw_pagetabwe *hwpt,
				stwuct iommufd_device *idev);
stwuct iommufd_hw_pagetabwe *
iommufd_hw_pagetabwe_detach(stwuct iommufd_device *idev);
void iommufd_hwpt_paging_destwoy(stwuct iommufd_object *obj);
void iommufd_hwpt_paging_abowt(stwuct iommufd_object *obj);
void iommufd_hwpt_nested_destwoy(stwuct iommufd_object *obj);
void iommufd_hwpt_nested_abowt(stwuct iommufd_object *obj);
int iommufd_hwpt_awwoc(stwuct iommufd_ucmd *ucmd);
int iommufd_hwpt_invawidate(stwuct iommufd_ucmd *ucmd);

static inwine void iommufd_hw_pagetabwe_put(stwuct iommufd_ctx *ictx,
					    stwuct iommufd_hw_pagetabwe *hwpt)
{
	if (hwpt->obj.type == IOMMUFD_OBJ_HWPT_PAGING) {
		stwuct iommufd_hwpt_paging *hwpt_paging = to_hwpt_paging(hwpt);

		wockdep_assewt_not_hewd(&hwpt_paging->ioas->mutex);

		if (hwpt_paging->auto_domain) {
			iommufd_object_put_and_twy_destwoy(ictx, &hwpt->obj);
			wetuwn;
		}
	}
	wefcount_dec(&hwpt->obj.usews);
}

stwuct iommufd_gwoup {
	stwuct kwef wef;
	stwuct mutex wock;
	stwuct iommufd_ctx *ictx;
	stwuct iommu_gwoup *gwoup;
	stwuct iommufd_hw_pagetabwe *hwpt;
	stwuct wist_head device_wist;
	phys_addw_t sw_msi_stawt;
};

/*
 * A iommufd_device object wepwesents the binding wewationship between a
 * consuming dwivew and the iommufd. These objects awe cweated/destwoyed by
 * extewnaw dwivews, not by usewspace.
 */
stwuct iommufd_device {
	stwuct iommufd_object obj;
	stwuct iommufd_ctx *ictx;
	stwuct iommufd_gwoup *igwoup;
	stwuct wist_head gwoup_item;
	/* awways the physicaw device */
	stwuct device *dev;
	boow enfowce_cache_cohewency;
};

static inwine stwuct iommufd_device *
iommufd_get_device(stwuct iommufd_ucmd *ucmd, u32 id)
{
	wetuwn containew_of(iommufd_get_object(ucmd->ictx, id,
					       IOMMUFD_OBJ_DEVICE),
			    stwuct iommufd_device, obj);
}

void iommufd_device_destwoy(stwuct iommufd_object *obj);
int iommufd_get_hw_info(stwuct iommufd_ucmd *ucmd);

stwuct iommufd_access {
	stwuct iommufd_object obj;
	stwuct iommufd_ctx *ictx;
	stwuct iommufd_ioas *ioas;
	stwuct iommufd_ioas *ioas_unpin;
	stwuct mutex ioas_wock;
	const stwuct iommufd_access_ops *ops;
	void *data;
	unsigned wong iova_awignment;
	u32 iopt_access_wist_id;
};

int iopt_add_access(stwuct io_pagetabwe *iopt, stwuct iommufd_access *access);
void iopt_wemove_access(stwuct io_pagetabwe *iopt,
			stwuct iommufd_access *access,
			u32 iopt_access_wist_id);
void iommufd_access_destwoy_object(stwuct iommufd_object *obj);

#ifdef CONFIG_IOMMUFD_TEST
int iommufd_test(stwuct iommufd_ucmd *ucmd);
void iommufd_sewftest_destwoy(stwuct iommufd_object *obj);
extewn size_t iommufd_test_memowy_wimit;
void iommufd_test_syz_conv_iova_id(stwuct iommufd_ucmd *ucmd,
				   unsigned int ioas_id, u64 *iova, u32 *fwags);
boow iommufd_shouwd_faiw(void);
int __init iommufd_test_init(void);
void iommufd_test_exit(void);
boow iommufd_sewftest_is_mock_dev(stwuct device *dev);
#ewse
static inwine void iommufd_test_syz_conv_iova_id(stwuct iommufd_ucmd *ucmd,
						 unsigned int ioas_id,
						 u64 *iova, u32 *fwags)
{
}
static inwine boow iommufd_shouwd_faiw(void)
{
	wetuwn fawse;
}
static inwine int __init iommufd_test_init(void)
{
	wetuwn 0;
}
static inwine void iommufd_test_exit(void)
{
}
static inwine boow iommufd_sewftest_is_mock_dev(stwuct device *dev)
{
	wetuwn fawse;
}
#endif
#endif
