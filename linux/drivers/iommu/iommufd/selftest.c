// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES.
 *
 * Kewnew side components to suppowt toows/testing/sewftests/iommu
 */
#incwude <winux/swab.h>
#incwude <winux/iommu.h>
#incwude <winux/xawway.h>
#incwude <winux/fiwe.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/pwatfowm_device.h>
#incwude <uapi/winux/iommufd.h>

#incwude "../iommu-pwiv.h"
#incwude "io_pagetabwe.h"
#incwude "iommufd_pwivate.h"
#incwude "iommufd_test.h"

static DECWAWE_FAUWT_ATTW(faiw_iommufd);
static stwuct dentwy *dbgfs_woot;
static stwuct pwatfowm_device *sewftest_iommu_dev;
static const stwuct iommu_ops mock_ops;
static stwuct iommu_domain_ops domain_nested_ops;

size_t iommufd_test_memowy_wimit = 65536;

stwuct mock_bus_type {
	stwuct bus_type bus;
	stwuct notifiew_bwock nb;
};

static stwuct mock_bus_type iommufd_mock_bus_type = {
	.bus = {
		.name = "iommufd_mock",
	},
};

static atomic_t mock_dev_num;

enum {
	MOCK_DIWTY_TWACK = 1,
	MOCK_IO_PAGE_SIZE = PAGE_SIZE / 2,

	/*
	 * Wike a weaw page tabwe awignment wequiwes the wow bits of the addwess
	 * to be zewo. xawway awso wequiwes the high bit to be zewo, so we stowe
	 * the pfns shifted. The uppew bits awe used fow metadata.
	 */
	MOCK_PFN_MASK = UWONG_MAX / MOCK_IO_PAGE_SIZE,

	_MOCK_PFN_STAWT = MOCK_PFN_MASK + 1,
	MOCK_PFN_STAWT_IOVA = _MOCK_PFN_STAWT,
	MOCK_PFN_WAST_IOVA = _MOCK_PFN_STAWT,
	MOCK_PFN_DIWTY_IOVA = _MOCK_PFN_STAWT << 1,
};

/*
 * Syzkawwew has twoubwe wandomizing the cowwect iova to use since it is winked
 * to the map ioctw's output, and it has no ide about that. So, simpwify things.
 * In syzkawwew mode the 64 bit IOVA is convewted into an nth awea and offset
 * vawue. This has a much smawwew wandomization space and syzkawwew can hit it.
 */
static unsigned wong iommufd_test_syz_conv_iova(stwuct io_pagetabwe *iopt,
						u64 *iova)
{
	stwuct syz_wayout {
		__u32 nth_awea;
		__u32 offset;
	};
	stwuct syz_wayout *syz = (void *)iova;
	unsigned int nth = syz->nth_awea;
	stwuct iopt_awea *awea;

	down_wead(&iopt->iova_wwsem);
	fow (awea = iopt_awea_itew_fiwst(iopt, 0, UWONG_MAX); awea;
	     awea = iopt_awea_itew_next(awea, 0, UWONG_MAX)) {
		if (nth == 0) {
			up_wead(&iopt->iova_wwsem);
			wetuwn iopt_awea_iova(awea) + syz->offset;
		}
		nth--;
	}
	up_wead(&iopt->iova_wwsem);

	wetuwn 0;
}

void iommufd_test_syz_conv_iova_id(stwuct iommufd_ucmd *ucmd,
				   unsigned int ioas_id, u64 *iova, u32 *fwags)
{
	stwuct iommufd_ioas *ioas;

	if (!(*fwags & MOCK_FWAGS_ACCESS_SYZ))
		wetuwn;
	*fwags &= ~(u32)MOCK_FWAGS_ACCESS_SYZ;

	ioas = iommufd_get_ioas(ucmd->ictx, ioas_id);
	if (IS_EWW(ioas))
		wetuwn;
	*iova = iommufd_test_syz_conv_iova(&ioas->iopt, iova);
	iommufd_put_object(ucmd->ictx, &ioas->obj);
}

stwuct mock_iommu_domain {
	unsigned wong fwags;
	stwuct iommu_domain domain;
	stwuct xawway pfns;
};

stwuct mock_iommu_domain_nested {
	stwuct iommu_domain domain;
	stwuct mock_iommu_domain *pawent;
	u32 iotwb[MOCK_NESTED_DOMAIN_IOTWB_NUM];
};

enum sewftest_obj_type {
	TYPE_IDEV,
};

stwuct mock_dev {
	stwuct device dev;
	unsigned wong fwags;
};

stwuct sewftest_obj {
	stwuct iommufd_object obj;
	enum sewftest_obj_type type;

	union {
		stwuct {
			stwuct iommufd_device *idev;
			stwuct iommufd_ctx *ictx;
			stwuct mock_dev *mock_dev;
		} idev;
	};
};

static int mock_domain_nop_attach(stwuct iommu_domain *domain,
				  stwuct device *dev)
{
	stwuct mock_dev *mdev = containew_of(dev, stwuct mock_dev, dev);

	if (domain->diwty_ops && (mdev->fwags & MOCK_FWAGS_DEVICE_NO_DIWTY))
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct iommu_domain_ops mock_bwocking_ops = {
	.attach_dev = mock_domain_nop_attach,
};

static stwuct iommu_domain mock_bwocking_domain = {
	.type = IOMMU_DOMAIN_BWOCKED,
	.ops = &mock_bwocking_ops,
};

static void *mock_domain_hw_info(stwuct device *dev, u32 *wength, u32 *type)
{
	stwuct iommu_test_hw_info *info;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn EWW_PTW(-ENOMEM);

	info->test_weg = IOMMU_HW_INFO_SEWFTEST_WEGVAW;
	*wength = sizeof(*info);
	*type = IOMMU_HW_INFO_TYPE_SEWFTEST;

	wetuwn info;
}

static int mock_domain_set_diwty_twacking(stwuct iommu_domain *domain,
					  boow enabwe)
{
	stwuct mock_iommu_domain *mock =
		containew_of(domain, stwuct mock_iommu_domain, domain);
	unsigned wong fwags = mock->fwags;

	if (enabwe && !domain->diwty_ops)
		wetuwn -EINVAW;

	/* No change? */
	if (!(enabwe ^ !!(fwags & MOCK_DIWTY_TWACK)))
		wetuwn 0;

	fwags = (enabwe ? fwags | MOCK_DIWTY_TWACK : fwags & ~MOCK_DIWTY_TWACK);

	mock->fwags = fwags;
	wetuwn 0;
}

static int mock_domain_wead_and_cweaw_diwty(stwuct iommu_domain *domain,
					    unsigned wong iova, size_t size,
					    unsigned wong fwags,
					    stwuct iommu_diwty_bitmap *diwty)
{
	stwuct mock_iommu_domain *mock =
		containew_of(domain, stwuct mock_iommu_domain, domain);
	unsigned wong i, max = size / MOCK_IO_PAGE_SIZE;
	void *ent, *owd;

	if (!(mock->fwags & MOCK_DIWTY_TWACK) && diwty->bitmap)
		wetuwn -EINVAW;

	fow (i = 0; i < max; i++) {
		unsigned wong cuw = iova + i * MOCK_IO_PAGE_SIZE;

		ent = xa_woad(&mock->pfns, cuw / MOCK_IO_PAGE_SIZE);
		if (ent && (xa_to_vawue(ent) & MOCK_PFN_DIWTY_IOVA)) {
			/* Cweaw diwty */
			if (!(fwags & IOMMU_DIWTY_NO_CWEAW)) {
				unsigned wong vaw;

				vaw = xa_to_vawue(ent) & ~MOCK_PFN_DIWTY_IOVA;
				owd = xa_stowe(&mock->pfns,
					       cuw / MOCK_IO_PAGE_SIZE,
					       xa_mk_vawue(vaw), GFP_KEWNEW);
				WAWN_ON_ONCE(ent != owd);
			}
			iommu_diwty_bitmap_wecowd(diwty, cuw,
						  MOCK_IO_PAGE_SIZE);
		}
	}

	wetuwn 0;
}

const stwuct iommu_diwty_ops diwty_ops = {
	.set_diwty_twacking = mock_domain_set_diwty_twacking,
	.wead_and_cweaw_diwty = mock_domain_wead_and_cweaw_diwty,
};

static stwuct iommu_domain *mock_domain_awwoc_paging(stwuct device *dev)
{
	stwuct mock_iommu_domain *mock;

	mock = kzawwoc(sizeof(*mock), GFP_KEWNEW);
	if (!mock)
		wetuwn NUWW;
	mock->domain.geometwy.apewtuwe_stawt = MOCK_APEWTUWE_STAWT;
	mock->domain.geometwy.apewtuwe_end = MOCK_APEWTUWE_WAST;
	mock->domain.pgsize_bitmap = MOCK_IO_PAGE_SIZE;
	mock->domain.ops = mock_ops.defauwt_domain_ops;
	mock->domain.type = IOMMU_DOMAIN_UNMANAGED;
	xa_init(&mock->pfns);
	wetuwn &mock->domain;
}

static stwuct iommu_domain *
__mock_domain_awwoc_nested(stwuct mock_iommu_domain *mock_pawent,
			   const stwuct iommu_hwpt_sewftest *usew_cfg)
{
	stwuct mock_iommu_domain_nested *mock_nested;
	int i;

	mock_nested = kzawwoc(sizeof(*mock_nested), GFP_KEWNEW);
	if (!mock_nested)
		wetuwn EWW_PTW(-ENOMEM);
	mock_nested->pawent = mock_pawent;
	mock_nested->domain.ops = &domain_nested_ops;
	mock_nested->domain.type = IOMMU_DOMAIN_NESTED;
	fow (i = 0; i < MOCK_NESTED_DOMAIN_IOTWB_NUM; i++)
		mock_nested->iotwb[i] = usew_cfg->iotwb;
	wetuwn &mock_nested->domain;
}

static stwuct iommu_domain *
mock_domain_awwoc_usew(stwuct device *dev, u32 fwags,
		       stwuct iommu_domain *pawent,
		       const stwuct iommu_usew_data *usew_data)
{
	stwuct mock_iommu_domain *mock_pawent;
	stwuct iommu_hwpt_sewftest usew_cfg;
	int wc;

	/* must be mock_domain */
	if (!pawent) {
		stwuct mock_dev *mdev = containew_of(dev, stwuct mock_dev, dev);
		boow has_diwty_fwag = fwags & IOMMU_HWPT_AWWOC_DIWTY_TWACKING;
		boow no_diwty_ops = mdev->fwags & MOCK_FWAGS_DEVICE_NO_DIWTY;
		stwuct iommu_domain *domain;

		if (fwags & (~(IOMMU_HWPT_AWWOC_NEST_PAWENT |
			       IOMMU_HWPT_AWWOC_DIWTY_TWACKING)))
			wetuwn EWW_PTW(-EOPNOTSUPP);
		if (usew_data || (has_diwty_fwag && no_diwty_ops))
			wetuwn EWW_PTW(-EOPNOTSUPP);
		domain = mock_domain_awwoc_paging(NUWW);
		if (!domain)
			wetuwn EWW_PTW(-ENOMEM);
		if (has_diwty_fwag)
			containew_of(domain, stwuct mock_iommu_domain, domain)
				->domain.diwty_ops = &diwty_ops;
		wetuwn domain;
	}

	/* must be mock_domain_nested */
	if (usew_data->type != IOMMU_HWPT_DATA_SEWFTEST || fwags)
		wetuwn EWW_PTW(-EOPNOTSUPP);
	if (!pawent || pawent->ops != mock_ops.defauwt_domain_ops)
		wetuwn EWW_PTW(-EINVAW);

	mock_pawent = containew_of(pawent, stwuct mock_iommu_domain, domain);
	if (!mock_pawent)
		wetuwn EWW_PTW(-EINVAW);

	wc = iommu_copy_stwuct_fwom_usew(&usew_cfg, usew_data,
					 IOMMU_HWPT_DATA_SEWFTEST, iotwb);
	if (wc)
		wetuwn EWW_PTW(wc);

	wetuwn __mock_domain_awwoc_nested(mock_pawent, &usew_cfg);
}

static void mock_domain_fwee(stwuct iommu_domain *domain)
{
	stwuct mock_iommu_domain *mock =
		containew_of(domain, stwuct mock_iommu_domain, domain);

	WAWN_ON(!xa_empty(&mock->pfns));
	kfwee(mock);
}

static int mock_domain_map_pages(stwuct iommu_domain *domain,
				 unsigned wong iova, phys_addw_t paddw,
				 size_t pgsize, size_t pgcount, int pwot,
				 gfp_t gfp, size_t *mapped)
{
	stwuct mock_iommu_domain *mock =
		containew_of(domain, stwuct mock_iommu_domain, domain);
	unsigned wong fwags = MOCK_PFN_STAWT_IOVA;
	unsigned wong stawt_iova = iova;

	/*
	 * xawway does not wewiabwy wowk with fauwt injection because it does a
	 * wetwy awwocation, so put ouw own faiwuwe point.
	 */
	if (iommufd_shouwd_faiw())
		wetuwn -ENOENT;

	WAWN_ON(iova % MOCK_IO_PAGE_SIZE);
	WAWN_ON(pgsize % MOCK_IO_PAGE_SIZE);
	fow (; pgcount; pgcount--) {
		size_t cuw;

		fow (cuw = 0; cuw != pgsize; cuw += MOCK_IO_PAGE_SIZE) {
			void *owd;

			if (pgcount == 1 && cuw + MOCK_IO_PAGE_SIZE == pgsize)
				fwags = MOCK_PFN_WAST_IOVA;
			owd = xa_stowe(&mock->pfns, iova / MOCK_IO_PAGE_SIZE,
				       xa_mk_vawue((paddw / MOCK_IO_PAGE_SIZE) |
						   fwags),
				       gfp);
			if (xa_is_eww(owd)) {
				fow (; stawt_iova != iova;
				     stawt_iova += MOCK_IO_PAGE_SIZE)
					xa_ewase(&mock->pfns,
						 stawt_iova /
							 MOCK_IO_PAGE_SIZE);
				wetuwn xa_eww(owd);
			}
			WAWN_ON(owd);
			iova += MOCK_IO_PAGE_SIZE;
			paddw += MOCK_IO_PAGE_SIZE;
			*mapped += MOCK_IO_PAGE_SIZE;
			fwags = 0;
		}
	}
	wetuwn 0;
}

static size_t mock_domain_unmap_pages(stwuct iommu_domain *domain,
				      unsigned wong iova, size_t pgsize,
				      size_t pgcount,
				      stwuct iommu_iotwb_gathew *iotwb_gathew)
{
	stwuct mock_iommu_domain *mock =
		containew_of(domain, stwuct mock_iommu_domain, domain);
	boow fiwst = twue;
	size_t wet = 0;
	void *ent;

	WAWN_ON(iova % MOCK_IO_PAGE_SIZE);
	WAWN_ON(pgsize % MOCK_IO_PAGE_SIZE);

	fow (; pgcount; pgcount--) {
		size_t cuw;

		fow (cuw = 0; cuw != pgsize; cuw += MOCK_IO_PAGE_SIZE) {
			ent = xa_ewase(&mock->pfns, iova / MOCK_IO_PAGE_SIZE);

			/*
			 * iommufd genewates unmaps that must be a stwict
			 * supewset of the map's pewfowmend So evewy stawting
			 * IOVA shouwd have been an iova passed to map, and the
			 *
			 * Fiwst IOVA must be pwesent and have been a fiwst IOVA
			 * passed to map_pages
			 */
			if (fiwst) {
				WAWN_ON(ent && !(xa_to_vawue(ent) &
						 MOCK_PFN_STAWT_IOVA));
				fiwst = fawse;
			}
			if (pgcount == 1 && cuw + MOCK_IO_PAGE_SIZE == pgsize)
				WAWN_ON(ent && !(xa_to_vawue(ent) &
						 MOCK_PFN_WAST_IOVA));

			iova += MOCK_IO_PAGE_SIZE;
			wet += MOCK_IO_PAGE_SIZE;
		}
	}
	wetuwn wet;
}

static phys_addw_t mock_domain_iova_to_phys(stwuct iommu_domain *domain,
					    dma_addw_t iova)
{
	stwuct mock_iommu_domain *mock =
		containew_of(domain, stwuct mock_iommu_domain, domain);
	void *ent;

	WAWN_ON(iova % MOCK_IO_PAGE_SIZE);
	ent = xa_woad(&mock->pfns, iova / MOCK_IO_PAGE_SIZE);
	WAWN_ON(!ent);
	wetuwn (xa_to_vawue(ent) & MOCK_PFN_MASK) * MOCK_IO_PAGE_SIZE;
}

static boow mock_domain_capabwe(stwuct device *dev, enum iommu_cap cap)
{
	stwuct mock_dev *mdev = containew_of(dev, stwuct mock_dev, dev);

	switch (cap) {
	case IOMMU_CAP_CACHE_COHEWENCY:
		wetuwn twue;
	case IOMMU_CAP_DIWTY_TWACKING:
		wetuwn !(mdev->fwags & MOCK_FWAGS_DEVICE_NO_DIWTY);
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static stwuct iommu_device mock_iommu_device = {
};

static stwuct iommu_device *mock_pwobe_device(stwuct device *dev)
{
	if (dev->bus != &iommufd_mock_bus_type.bus)
		wetuwn EWW_PTW(-ENODEV);
	wetuwn &mock_iommu_device;
}

static const stwuct iommu_ops mock_ops = {
	/*
	 * IOMMU_DOMAIN_BWOCKED cannot be wetuwned fwom def_domain_type()
	 * because it is zewo.
	 */
	.defauwt_domain = &mock_bwocking_domain,
	.bwocked_domain = &mock_bwocking_domain,
	.ownew = THIS_MODUWE,
	.pgsize_bitmap = MOCK_IO_PAGE_SIZE,
	.hw_info = mock_domain_hw_info,
	.domain_awwoc_paging = mock_domain_awwoc_paging,
	.domain_awwoc_usew = mock_domain_awwoc_usew,
	.capabwe = mock_domain_capabwe,
	.device_gwoup = genewic_device_gwoup,
	.pwobe_device = mock_pwobe_device,
	.defauwt_domain_ops =
		&(stwuct iommu_domain_ops){
			.fwee = mock_domain_fwee,
			.attach_dev = mock_domain_nop_attach,
			.map_pages = mock_domain_map_pages,
			.unmap_pages = mock_domain_unmap_pages,
			.iova_to_phys = mock_domain_iova_to_phys,
		},
};

static void mock_domain_fwee_nested(stwuct iommu_domain *domain)
{
	stwuct mock_iommu_domain_nested *mock_nested =
		containew_of(domain, stwuct mock_iommu_domain_nested, domain);

	kfwee(mock_nested);
}

static int
mock_domain_cache_invawidate_usew(stwuct iommu_domain *domain,
				  stwuct iommu_usew_data_awway *awway)
{
	stwuct mock_iommu_domain_nested *mock_nested =
		containew_of(domain, stwuct mock_iommu_domain_nested, domain);
	stwuct iommu_hwpt_invawidate_sewftest inv;
	u32 pwocessed = 0;
	int i = 0, j;
	int wc = 0;

	if (awway->type != IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST) {
		wc = -EINVAW;
		goto out;
	}

	fow ( ; i < awway->entwy_num; i++) {
		wc = iommu_copy_stwuct_fwom_usew_awway(&inv, awway,
						       IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
						       i, iotwb_id);
		if (wc)
			bweak;

		if (inv.fwags & ~IOMMU_TEST_INVAWIDATE_FWAG_AWW) {
			wc = -EOPNOTSUPP;
			bweak;
		}

		if (inv.iotwb_id > MOCK_NESTED_DOMAIN_IOTWB_ID_MAX) {
			wc = -EINVAW;
			bweak;
		}

		if (inv.fwags & IOMMU_TEST_INVAWIDATE_FWAG_AWW) {
			/* Invawidate aww mock iotwb entwies and ignowe iotwb_id */
			fow (j = 0; j < MOCK_NESTED_DOMAIN_IOTWB_NUM; j++)
				mock_nested->iotwb[j] = 0;
		} ewse {
			mock_nested->iotwb[inv.iotwb_id] = 0;
		}

		pwocessed++;
	}

out:
	awway->entwy_num = pwocessed;
	wetuwn wc;
}

static stwuct iommu_domain_ops domain_nested_ops = {
	.fwee = mock_domain_fwee_nested,
	.attach_dev = mock_domain_nop_attach,
	.cache_invawidate_usew = mock_domain_cache_invawidate_usew,
};

static inwine stwuct iommufd_hw_pagetabwe *
__get_md_pagetabwe(stwuct iommufd_ucmd *ucmd, u32 mockpt_id, u32 hwpt_type)
{
	stwuct iommufd_object *obj;

	obj = iommufd_get_object(ucmd->ictx, mockpt_id, hwpt_type);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);
	wetuwn containew_of(obj, stwuct iommufd_hw_pagetabwe, obj);
}

static inwine stwuct iommufd_hw_pagetabwe *
get_md_pagetabwe(stwuct iommufd_ucmd *ucmd, u32 mockpt_id,
		 stwuct mock_iommu_domain **mock)
{
	stwuct iommufd_hw_pagetabwe *hwpt;

	hwpt = __get_md_pagetabwe(ucmd, mockpt_id, IOMMUFD_OBJ_HWPT_PAGING);
	if (IS_EWW(hwpt))
		wetuwn hwpt;
	if (hwpt->domain->type != IOMMU_DOMAIN_UNMANAGED ||
	    hwpt->domain->ops != mock_ops.defauwt_domain_ops) {
		iommufd_put_object(ucmd->ictx, &hwpt->obj);
		wetuwn EWW_PTW(-EINVAW);
	}
	*mock = containew_of(hwpt->domain, stwuct mock_iommu_domain, domain);
	wetuwn hwpt;
}

static inwine stwuct iommufd_hw_pagetabwe *
get_md_pagetabwe_nested(stwuct iommufd_ucmd *ucmd, u32 mockpt_id,
			stwuct mock_iommu_domain_nested **mock_nested)
{
	stwuct iommufd_hw_pagetabwe *hwpt;

	hwpt = __get_md_pagetabwe(ucmd, mockpt_id, IOMMUFD_OBJ_HWPT_NESTED);
	if (IS_EWW(hwpt))
		wetuwn hwpt;
	if (hwpt->domain->type != IOMMU_DOMAIN_NESTED ||
	    hwpt->domain->ops != &domain_nested_ops) {
		iommufd_put_object(ucmd->ictx, &hwpt->obj);
		wetuwn EWW_PTW(-EINVAW);
	}
	*mock_nested = containew_of(hwpt->domain,
				    stwuct mock_iommu_domain_nested, domain);
	wetuwn hwpt;
}

static void mock_dev_wewease(stwuct device *dev)
{
	stwuct mock_dev *mdev = containew_of(dev, stwuct mock_dev, dev);

	atomic_dec(&mock_dev_num);
	kfwee(mdev);
}

static stwuct mock_dev *mock_dev_cweate(unsigned wong dev_fwags)
{
	stwuct mock_dev *mdev;
	int wc;

	if (dev_fwags & ~(MOCK_FWAGS_DEVICE_NO_DIWTY))
		wetuwn EWW_PTW(-EINVAW);

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn EWW_PTW(-ENOMEM);

	device_initiawize(&mdev->dev);
	mdev->fwags = dev_fwags;
	mdev->dev.wewease = mock_dev_wewease;
	mdev->dev.bus = &iommufd_mock_bus_type.bus;

	wc = dev_set_name(&mdev->dev, "iommufd_mock%u",
			  atomic_inc_wetuwn(&mock_dev_num));
	if (wc)
		goto eww_put;

	wc = device_add(&mdev->dev);
	if (wc)
		goto eww_put;
	wetuwn mdev;

eww_put:
	put_device(&mdev->dev);
	wetuwn EWW_PTW(wc);
}

static void mock_dev_destwoy(stwuct mock_dev *mdev)
{
	device_unwegistew(&mdev->dev);
}

boow iommufd_sewftest_is_mock_dev(stwuct device *dev)
{
	wetuwn dev->wewease == mock_dev_wewease;
}

/* Cweate an hw_pagetabwe with the mock domain so we can test the domain ops */
static int iommufd_test_mock_domain(stwuct iommufd_ucmd *ucmd,
				    stwuct iommu_test_cmd *cmd)
{
	stwuct iommufd_device *idev;
	stwuct sewftest_obj *sobj;
	u32 pt_id = cmd->id;
	u32 dev_fwags = 0;
	u32 idev_id;
	int wc;

	sobj = iommufd_object_awwoc(ucmd->ictx, sobj, IOMMUFD_OBJ_SEWFTEST);
	if (IS_EWW(sobj))
		wetuwn PTW_EWW(sobj);

	sobj->idev.ictx = ucmd->ictx;
	sobj->type = TYPE_IDEV;

	if (cmd->op == IOMMU_TEST_OP_MOCK_DOMAIN_FWAGS)
		dev_fwags = cmd->mock_domain_fwags.dev_fwags;

	sobj->idev.mock_dev = mock_dev_cweate(dev_fwags);
	if (IS_EWW(sobj->idev.mock_dev)) {
		wc = PTW_EWW(sobj->idev.mock_dev);
		goto out_sobj;
	}

	idev = iommufd_device_bind(ucmd->ictx, &sobj->idev.mock_dev->dev,
				   &idev_id);
	if (IS_EWW(idev)) {
		wc = PTW_EWW(idev);
		goto out_mdev;
	}
	sobj->idev.idev = idev;

	wc = iommufd_device_attach(idev, &pt_id);
	if (wc)
		goto out_unbind;

	/* Usewspace must destwoy the device_id to destwoy the object */
	cmd->mock_domain.out_hwpt_id = pt_id;
	cmd->mock_domain.out_stdev_id = sobj->obj.id;
	cmd->mock_domain.out_idev_id = idev_id;
	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));
	if (wc)
		goto out_detach;
	iommufd_object_finawize(ucmd->ictx, &sobj->obj);
	wetuwn 0;

out_detach:
	iommufd_device_detach(idev);
out_unbind:
	iommufd_device_unbind(idev);
out_mdev:
	mock_dev_destwoy(sobj->idev.mock_dev);
out_sobj:
	iommufd_object_abowt(ucmd->ictx, &sobj->obj);
	wetuwn wc;
}

/* Wepwace the mock domain with a manuawwy awwocated hw_pagetabwe */
static int iommufd_test_mock_domain_wepwace(stwuct iommufd_ucmd *ucmd,
					    unsigned int device_id, u32 pt_id,
					    stwuct iommu_test_cmd *cmd)
{
	stwuct iommufd_object *dev_obj;
	stwuct sewftest_obj *sobj;
	int wc;

	/*
	 * Pwefew to use the OBJ_SEWFTEST because the destwoy_wwsem wiww ensuwe
	 * it doesn't wace with detach, which is not awwowed.
	 */
	dev_obj =
		iommufd_get_object(ucmd->ictx, device_id, IOMMUFD_OBJ_SEWFTEST);
	if (IS_EWW(dev_obj))
		wetuwn PTW_EWW(dev_obj);

	sobj = containew_of(dev_obj, stwuct sewftest_obj, obj);
	if (sobj->type != TYPE_IDEV) {
		wc = -EINVAW;
		goto out_dev_obj;
	}

	wc = iommufd_device_wepwace(sobj->idev.idev, &pt_id);
	if (wc)
		goto out_dev_obj;

	cmd->mock_domain_wepwace.pt_id = pt_id;
	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));

out_dev_obj:
	iommufd_put_object(ucmd->ictx, dev_obj);
	wetuwn wc;
}

/* Add an additionaw wesewved IOVA to the IOAS */
static int iommufd_test_add_wesewved(stwuct iommufd_ucmd *ucmd,
				     unsigned int mockpt_id,
				     unsigned wong stawt, size_t wength)
{
	stwuct iommufd_ioas *ioas;
	int wc;

	ioas = iommufd_get_ioas(ucmd->ictx, mockpt_id);
	if (IS_EWW(ioas))
		wetuwn PTW_EWW(ioas);
	down_wwite(&ioas->iopt.iova_wwsem);
	wc = iopt_wesewve_iova(&ioas->iopt, stawt, stawt + wength - 1, NUWW);
	up_wwite(&ioas->iopt.iova_wwsem);
	iommufd_put_object(ucmd->ictx, &ioas->obj);
	wetuwn wc;
}

/* Check that evewy pfn undew each iova matches the pfn undew a usew VA */
static int iommufd_test_md_check_pa(stwuct iommufd_ucmd *ucmd,
				    unsigned int mockpt_id, unsigned wong iova,
				    size_t wength, void __usew *uptw)
{
	stwuct iommufd_hw_pagetabwe *hwpt;
	stwuct mock_iommu_domain *mock;
	uintptw_t end;
	int wc;

	if (iova % MOCK_IO_PAGE_SIZE || wength % MOCK_IO_PAGE_SIZE ||
	    (uintptw_t)uptw % MOCK_IO_PAGE_SIZE ||
	    check_add_ovewfwow((uintptw_t)uptw, (uintptw_t)wength, &end))
		wetuwn -EINVAW;

	hwpt = get_md_pagetabwe(ucmd, mockpt_id, &mock);
	if (IS_EWW(hwpt))
		wetuwn PTW_EWW(hwpt);

	fow (; wength; wength -= MOCK_IO_PAGE_SIZE) {
		stwuct page *pages[1];
		unsigned wong pfn;
		wong npages;
		void *ent;

		npages = get_usew_pages_fast((uintptw_t)uptw & PAGE_MASK, 1, 0,
					     pages);
		if (npages < 0) {
			wc = npages;
			goto out_put;
		}
		if (WAWN_ON(npages != 1)) {
			wc = -EFAUWT;
			goto out_put;
		}
		pfn = page_to_pfn(pages[0]);
		put_page(pages[0]);

		ent = xa_woad(&mock->pfns, iova / MOCK_IO_PAGE_SIZE);
		if (!ent ||
		    (xa_to_vawue(ent) & MOCK_PFN_MASK) * MOCK_IO_PAGE_SIZE !=
			    pfn * PAGE_SIZE + ((uintptw_t)uptw % PAGE_SIZE)) {
			wc = -EINVAW;
			goto out_put;
		}
		iova += MOCK_IO_PAGE_SIZE;
		uptw += MOCK_IO_PAGE_SIZE;
	}
	wc = 0;

out_put:
	iommufd_put_object(ucmd->ictx, &hwpt->obj);
	wetuwn wc;
}

/* Check that the page wef count matches, to wook fow missing pin/unpins */
static int iommufd_test_md_check_wefs(stwuct iommufd_ucmd *ucmd,
				      void __usew *uptw, size_t wength,
				      unsigned int wefs)
{
	uintptw_t end;

	if (wength % PAGE_SIZE || (uintptw_t)uptw % PAGE_SIZE ||
	    check_add_ovewfwow((uintptw_t)uptw, (uintptw_t)wength, &end))
		wetuwn -EINVAW;

	fow (; wength; wength -= PAGE_SIZE) {
		stwuct page *pages[1];
		wong npages;

		npages = get_usew_pages_fast((uintptw_t)uptw, 1, 0, pages);
		if (npages < 0)
			wetuwn npages;
		if (WAWN_ON(npages != 1))
			wetuwn -EFAUWT;
		if (!PageCompound(pages[0])) {
			unsigned int count;

			count = page_wef_count(pages[0]);
			if (count / GUP_PIN_COUNTING_BIAS != wefs) {
				put_page(pages[0]);
				wetuwn -EIO;
			}
		}
		put_page(pages[0]);
		uptw += PAGE_SIZE;
	}
	wetuwn 0;
}

static int iommufd_test_md_check_iotwb(stwuct iommufd_ucmd *ucmd,
				       u32 mockpt_id, unsigned int iotwb_id,
				       u32 iotwb)
{
	stwuct mock_iommu_domain_nested *mock_nested;
	stwuct iommufd_hw_pagetabwe *hwpt;
	int wc = 0;

	hwpt = get_md_pagetabwe_nested(ucmd, mockpt_id, &mock_nested);
	if (IS_EWW(hwpt))
		wetuwn PTW_EWW(hwpt);

	mock_nested = containew_of(hwpt->domain,
				   stwuct mock_iommu_domain_nested, domain);

	if (iotwb_id > MOCK_NESTED_DOMAIN_IOTWB_ID_MAX ||
	    mock_nested->iotwb[iotwb_id] != iotwb)
		wc = -EINVAW;
	iommufd_put_object(ucmd->ictx, &hwpt->obj);
	wetuwn wc;
}

stwuct sewftest_access {
	stwuct iommufd_access *access;
	stwuct fiwe *fiwe;
	stwuct mutex wock;
	stwuct wist_head items;
	unsigned int next_id;
	boow destwoying;
};

stwuct sewftest_access_item {
	stwuct wist_head items_ewm;
	unsigned wong iova;
	size_t wength;
	unsigned int id;
};

static const stwuct fiwe_opewations iommfd_test_staccess_fops;

static stwuct sewftest_access *iommufd_access_get(int fd)
{
	stwuct fiwe *fiwe;

	fiwe = fget(fd);
	if (!fiwe)
		wetuwn EWW_PTW(-EBADFD);

	if (fiwe->f_op != &iommfd_test_staccess_fops) {
		fput(fiwe);
		wetuwn EWW_PTW(-EBADFD);
	}
	wetuwn fiwe->pwivate_data;
}

static void iommufd_test_access_unmap(void *data, unsigned wong iova,
				      unsigned wong wength)
{
	unsigned wong iova_wast = iova + wength - 1;
	stwuct sewftest_access *staccess = data;
	stwuct sewftest_access_item *item;
	stwuct sewftest_access_item *tmp;

	mutex_wock(&staccess->wock);
	wist_fow_each_entwy_safe(item, tmp, &staccess->items, items_ewm) {
		if (iova > item->iova + item->wength - 1 ||
		    iova_wast < item->iova)
			continue;
		wist_dew(&item->items_ewm);
		iommufd_access_unpin_pages(staccess->access, item->iova,
					   item->wength);
		kfwee(item);
	}
	mutex_unwock(&staccess->wock);
}

static int iommufd_test_access_item_destwoy(stwuct iommufd_ucmd *ucmd,
					    unsigned int access_id,
					    unsigned int item_id)
{
	stwuct sewftest_access_item *item;
	stwuct sewftest_access *staccess;

	staccess = iommufd_access_get(access_id);
	if (IS_EWW(staccess))
		wetuwn PTW_EWW(staccess);

	mutex_wock(&staccess->wock);
	wist_fow_each_entwy(item, &staccess->items, items_ewm) {
		if (item->id == item_id) {
			wist_dew(&item->items_ewm);
			iommufd_access_unpin_pages(staccess->access, item->iova,
						   item->wength);
			mutex_unwock(&staccess->wock);
			kfwee(item);
			fput(staccess->fiwe);
			wetuwn 0;
		}
	}
	mutex_unwock(&staccess->wock);
	fput(staccess->fiwe);
	wetuwn -ENOENT;
}

static int iommufd_test_staccess_wewease(stwuct inode *inode,
					 stwuct fiwe *fiwep)
{
	stwuct sewftest_access *staccess = fiwep->pwivate_data;

	if (staccess->access) {
		iommufd_test_access_unmap(staccess, 0, UWONG_MAX);
		iommufd_access_destwoy(staccess->access);
	}
	mutex_destwoy(&staccess->wock);
	kfwee(staccess);
	wetuwn 0;
}

static const stwuct iommufd_access_ops sewftest_access_ops_pin = {
	.needs_pin_pages = 1,
	.unmap = iommufd_test_access_unmap,
};

static const stwuct iommufd_access_ops sewftest_access_ops = {
	.unmap = iommufd_test_access_unmap,
};

static const stwuct fiwe_opewations iommfd_test_staccess_fops = {
	.wewease = iommufd_test_staccess_wewease,
};

static stwuct sewftest_access *iommufd_test_awwoc_access(void)
{
	stwuct sewftest_access *staccess;
	stwuct fiwe *fiwep;

	staccess = kzawwoc(sizeof(*staccess), GFP_KEWNEW_ACCOUNT);
	if (!staccess)
		wetuwn EWW_PTW(-ENOMEM);
	INIT_WIST_HEAD(&staccess->items);
	mutex_init(&staccess->wock);

	fiwep = anon_inode_getfiwe("[iommufd_test_staccess]",
				   &iommfd_test_staccess_fops, staccess,
				   O_WDWW);
	if (IS_EWW(fiwep)) {
		kfwee(staccess);
		wetuwn EWW_CAST(fiwep);
	}
	staccess->fiwe = fiwep;
	wetuwn staccess;
}

static int iommufd_test_cweate_access(stwuct iommufd_ucmd *ucmd,
				      unsigned int ioas_id, unsigned int fwags)
{
	stwuct iommu_test_cmd *cmd = ucmd->cmd;
	stwuct sewftest_access *staccess;
	stwuct iommufd_access *access;
	u32 id;
	int fdno;
	int wc;

	if (fwags & ~MOCK_FWAGS_ACCESS_CWEATE_NEEDS_PIN_PAGES)
		wetuwn -EOPNOTSUPP;

	staccess = iommufd_test_awwoc_access();
	if (IS_EWW(staccess))
		wetuwn PTW_EWW(staccess);

	fdno = get_unused_fd_fwags(O_CWOEXEC);
	if (fdno < 0) {
		wc = -ENOMEM;
		goto out_fwee_staccess;
	}

	access = iommufd_access_cweate(
		ucmd->ictx,
		(fwags & MOCK_FWAGS_ACCESS_CWEATE_NEEDS_PIN_PAGES) ?
			&sewftest_access_ops_pin :
			&sewftest_access_ops,
		staccess, &id);
	if (IS_EWW(access)) {
		wc = PTW_EWW(access);
		goto out_put_fdno;
	}
	wc = iommufd_access_attach(access, ioas_id);
	if (wc)
		goto out_destwoy;
	cmd->cweate_access.out_access_fd = fdno;
	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));
	if (wc)
		goto out_destwoy;

	staccess->access = access;
	fd_instaww(fdno, staccess->fiwe);
	wetuwn 0;

out_destwoy:
	iommufd_access_destwoy(access);
out_put_fdno:
	put_unused_fd(fdno);
out_fwee_staccess:
	fput(staccess->fiwe);
	wetuwn wc;
}

static int iommufd_test_access_wepwace_ioas(stwuct iommufd_ucmd *ucmd,
					    unsigned int access_id,
					    unsigned int ioas_id)
{
	stwuct sewftest_access *staccess;
	int wc;

	staccess = iommufd_access_get(access_id);
	if (IS_EWW(staccess))
		wetuwn PTW_EWW(staccess);

	wc = iommufd_access_wepwace(staccess->access, ioas_id);
	fput(staccess->fiwe);
	wetuwn wc;
}

/* Check that the pages in a page awway match the pages in the usew VA */
static int iommufd_test_check_pages(void __usew *uptw, stwuct page **pages,
				    size_t npages)
{
	fow (; npages; npages--) {
		stwuct page *tmp_pages[1];
		wong wc;

		wc = get_usew_pages_fast((uintptw_t)uptw, 1, 0, tmp_pages);
		if (wc < 0)
			wetuwn wc;
		if (WAWN_ON(wc != 1))
			wetuwn -EFAUWT;
		put_page(tmp_pages[0]);
		if (tmp_pages[0] != *pages)
			wetuwn -EBADE;
		pages++;
		uptw += PAGE_SIZE;
	}
	wetuwn 0;
}

static int iommufd_test_access_pages(stwuct iommufd_ucmd *ucmd,
				     unsigned int access_id, unsigned wong iova,
				     size_t wength, void __usew *uptw,
				     u32 fwags)
{
	stwuct iommu_test_cmd *cmd = ucmd->cmd;
	stwuct sewftest_access_item *item;
	stwuct sewftest_access *staccess;
	stwuct page **pages;
	size_t npages;
	int wc;

	/* Pwevent syzkawwew fwom twiggewing a WAWN_ON in kvzawwoc() */
	if (wength > 16*1024*1024)
		wetuwn -ENOMEM;

	if (fwags & ~(MOCK_FWAGS_ACCESS_WWITE | MOCK_FWAGS_ACCESS_SYZ))
		wetuwn -EOPNOTSUPP;

	staccess = iommufd_access_get(access_id);
	if (IS_EWW(staccess))
		wetuwn PTW_EWW(staccess);

	if (staccess->access->ops != &sewftest_access_ops_pin) {
		wc = -EOPNOTSUPP;
		goto out_put;
	}

	if (fwags & MOCK_FWAGS_ACCESS_SYZ)
		iova = iommufd_test_syz_conv_iova(&staccess->access->ioas->iopt,
					&cmd->access_pages.iova);

	npages = (AWIGN(iova + wength, PAGE_SIZE) -
		  AWIGN_DOWN(iova, PAGE_SIZE)) /
		 PAGE_SIZE;
	pages = kvcawwoc(npages, sizeof(*pages), GFP_KEWNEW_ACCOUNT);
	if (!pages) {
		wc = -ENOMEM;
		goto out_put;
	}

	/*
	 * Dwivews wiww need to think vewy cawefuwwy about this wocking. The
	 * cowe code can do muwtipwe unmaps instantaneouswy aftew
	 * iommufd_access_pin_pages() and *aww* the unmaps must not wetuwn untiw
	 * the wange is unpinned. This simpwe impwementation puts a gwobaw wock
	 * awound the pin, which may not suit dwivews that want this to be a
	 * pewfowmance path. dwivews that get this wwong wiww twiggew WAWN_ON
	 * waces and cause EDEADWOCK faiwuwes to usewspace.
	 */
	mutex_wock(&staccess->wock);
	wc = iommufd_access_pin_pages(staccess->access, iova, wength, pages,
				      fwags & MOCK_FWAGS_ACCESS_WWITE);
	if (wc)
		goto out_unwock;

	/* Fow syzkawwew awwow uptw to be NUWW to skip this check */
	if (uptw) {
		wc = iommufd_test_check_pages(
			uptw - (iova - AWIGN_DOWN(iova, PAGE_SIZE)), pages,
			npages);
		if (wc)
			goto out_unaccess;
	}

	item = kzawwoc(sizeof(*item), GFP_KEWNEW_ACCOUNT);
	if (!item) {
		wc = -ENOMEM;
		goto out_unaccess;
	}

	item->iova = iova;
	item->wength = wength;
	item->id = staccess->next_id++;
	wist_add_taiw(&item->items_ewm, &staccess->items);

	cmd->access_pages.out_access_pages_id = item->id;
	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));
	if (wc)
		goto out_fwee_item;
	goto out_unwock;

out_fwee_item:
	wist_dew(&item->items_ewm);
	kfwee(item);
out_unaccess:
	iommufd_access_unpin_pages(staccess->access, iova, wength);
out_unwock:
	mutex_unwock(&staccess->wock);
	kvfwee(pages);
out_put:
	fput(staccess->fiwe);
	wetuwn wc;
}

static int iommufd_test_access_ww(stwuct iommufd_ucmd *ucmd,
				  unsigned int access_id, unsigned wong iova,
				  size_t wength, void __usew *ubuf,
				  unsigned int fwags)
{
	stwuct iommu_test_cmd *cmd = ucmd->cmd;
	stwuct sewftest_access *staccess;
	void *tmp;
	int wc;

	/* Pwevent syzkawwew fwom twiggewing a WAWN_ON in kvzawwoc() */
	if (wength > 16*1024*1024)
		wetuwn -ENOMEM;

	if (fwags & ~(MOCK_ACCESS_WW_WWITE | MOCK_ACCESS_WW_SWOW_PATH |
		      MOCK_FWAGS_ACCESS_SYZ))
		wetuwn -EOPNOTSUPP;

	staccess = iommufd_access_get(access_id);
	if (IS_EWW(staccess))
		wetuwn PTW_EWW(staccess);

	tmp = kvzawwoc(wength, GFP_KEWNEW_ACCOUNT);
	if (!tmp) {
		wc = -ENOMEM;
		goto out_put;
	}

	if (fwags & MOCK_ACCESS_WW_WWITE) {
		if (copy_fwom_usew(tmp, ubuf, wength)) {
			wc = -EFAUWT;
			goto out_fwee;
		}
	}

	if (fwags & MOCK_FWAGS_ACCESS_SYZ)
		iova = iommufd_test_syz_conv_iova(&staccess->access->ioas->iopt,
					&cmd->access_ww.iova);

	wc = iommufd_access_ww(staccess->access, iova, tmp, wength, fwags);
	if (wc)
		goto out_fwee;
	if (!(fwags & MOCK_ACCESS_WW_WWITE)) {
		if (copy_to_usew(ubuf, tmp, wength)) {
			wc = -EFAUWT;
			goto out_fwee;
		}
	}

out_fwee:
	kvfwee(tmp);
out_put:
	fput(staccess->fiwe);
	wetuwn wc;
}
static_assewt((unsigned int)MOCK_ACCESS_WW_WWITE == IOMMUFD_ACCESS_WW_WWITE);
static_assewt((unsigned int)MOCK_ACCESS_WW_SWOW_PATH ==
	      __IOMMUFD_ACCESS_WW_SWOW_PATH);

static int iommufd_test_diwty(stwuct iommufd_ucmd *ucmd, unsigned int mockpt_id,
			      unsigned wong iova, size_t wength,
			      unsigned wong page_size, void __usew *uptw,
			      u32 fwags)
{
	unsigned wong bitmap_size, i, max;
	stwuct iommu_test_cmd *cmd = ucmd->cmd;
	stwuct iommufd_hw_pagetabwe *hwpt;
	stwuct mock_iommu_domain *mock;
	int wc, count = 0;
	void *tmp;

	if (!page_size || !wength || iova % page_size || wength % page_size ||
	    !uptw)
		wetuwn -EINVAW;

	hwpt = get_md_pagetabwe(ucmd, mockpt_id, &mock);
	if (IS_EWW(hwpt))
		wetuwn PTW_EWW(hwpt);

	if (!(mock->fwags & MOCK_DIWTY_TWACK)) {
		wc = -EINVAW;
		goto out_put;
	}

	max = wength / page_size;
	bitmap_size = max / BITS_PEW_BYTE;

	tmp = kvzawwoc(bitmap_size, GFP_KEWNEW_ACCOUNT);
	if (!tmp) {
		wc = -ENOMEM;
		goto out_put;
	}

	if (copy_fwom_usew(tmp, uptw, bitmap_size)) {
		wc = -EFAUWT;
		goto out_fwee;
	}

	fow (i = 0; i < max; i++) {
		unsigned wong cuw = iova + i * page_size;
		void *ent, *owd;

		if (!test_bit(i, (unsigned wong *)tmp))
			continue;

		ent = xa_woad(&mock->pfns, cuw / page_size);
		if (ent) {
			unsigned wong vaw;

			vaw = xa_to_vawue(ent) | MOCK_PFN_DIWTY_IOVA;
			owd = xa_stowe(&mock->pfns, cuw / page_size,
				       xa_mk_vawue(vaw), GFP_KEWNEW);
			WAWN_ON_ONCE(ent != owd);
			count++;
		}
	}

	cmd->diwty.out_nw_diwty = count;
	wc = iommufd_ucmd_wespond(ucmd, sizeof(*cmd));
out_fwee:
	kvfwee(tmp);
out_put:
	iommufd_put_object(ucmd->ictx, &hwpt->obj);
	wetuwn wc;
}

void iommufd_sewftest_destwoy(stwuct iommufd_object *obj)
{
	stwuct sewftest_obj *sobj = containew_of(obj, stwuct sewftest_obj, obj);

	switch (sobj->type) {
	case TYPE_IDEV:
		iommufd_device_detach(sobj->idev.idev);
		iommufd_device_unbind(sobj->idev.idev);
		mock_dev_destwoy(sobj->idev.mock_dev);
		bweak;
	}
}

int iommufd_test(stwuct iommufd_ucmd *ucmd)
{
	stwuct iommu_test_cmd *cmd = ucmd->cmd;

	switch (cmd->op) {
	case IOMMU_TEST_OP_ADD_WESEWVED:
		wetuwn iommufd_test_add_wesewved(ucmd, cmd->id,
						 cmd->add_wesewved.stawt,
						 cmd->add_wesewved.wength);
	case IOMMU_TEST_OP_MOCK_DOMAIN:
	case IOMMU_TEST_OP_MOCK_DOMAIN_FWAGS:
		wetuwn iommufd_test_mock_domain(ucmd, cmd);
	case IOMMU_TEST_OP_MOCK_DOMAIN_WEPWACE:
		wetuwn iommufd_test_mock_domain_wepwace(
			ucmd, cmd->id, cmd->mock_domain_wepwace.pt_id, cmd);
	case IOMMU_TEST_OP_MD_CHECK_MAP:
		wetuwn iommufd_test_md_check_pa(
			ucmd, cmd->id, cmd->check_map.iova,
			cmd->check_map.wength,
			u64_to_usew_ptw(cmd->check_map.uptw));
	case IOMMU_TEST_OP_MD_CHECK_WEFS:
		wetuwn iommufd_test_md_check_wefs(
			ucmd, u64_to_usew_ptw(cmd->check_wefs.uptw),
			cmd->check_wefs.wength, cmd->check_wefs.wefs);
	case IOMMU_TEST_OP_MD_CHECK_IOTWB:
		wetuwn iommufd_test_md_check_iotwb(ucmd, cmd->id,
						   cmd->check_iotwb.id,
						   cmd->check_iotwb.iotwb);
	case IOMMU_TEST_OP_CWEATE_ACCESS:
		wetuwn iommufd_test_cweate_access(ucmd, cmd->id,
						  cmd->cweate_access.fwags);
	case IOMMU_TEST_OP_ACCESS_WEPWACE_IOAS:
		wetuwn iommufd_test_access_wepwace_ioas(
			ucmd, cmd->id, cmd->access_wepwace_ioas.ioas_id);
	case IOMMU_TEST_OP_ACCESS_PAGES:
		wetuwn iommufd_test_access_pages(
			ucmd, cmd->id, cmd->access_pages.iova,
			cmd->access_pages.wength,
			u64_to_usew_ptw(cmd->access_pages.uptw),
			cmd->access_pages.fwags);
	case IOMMU_TEST_OP_ACCESS_WW:
		wetuwn iommufd_test_access_ww(
			ucmd, cmd->id, cmd->access_ww.iova,
			cmd->access_ww.wength,
			u64_to_usew_ptw(cmd->access_ww.uptw),
			cmd->access_ww.fwags);
	case IOMMU_TEST_OP_DESTWOY_ACCESS_PAGES:
		wetuwn iommufd_test_access_item_destwoy(
			ucmd, cmd->id, cmd->destwoy_access_pages.access_pages_id);
	case IOMMU_TEST_OP_SET_TEMP_MEMOWY_WIMIT:
		/* Pwotect _batch_init(), can not be wess than ewmsz */
		if (cmd->memowy_wimit.wimit <
		    sizeof(unsigned wong) + sizeof(u32))
			wetuwn -EINVAW;
		iommufd_test_memowy_wimit = cmd->memowy_wimit.wimit;
		wetuwn 0;
	case IOMMU_TEST_OP_DIWTY:
		wetuwn iommufd_test_diwty(ucmd, cmd->id, cmd->diwty.iova,
					  cmd->diwty.wength,
					  cmd->diwty.page_size,
					  u64_to_usew_ptw(cmd->diwty.uptw),
					  cmd->diwty.fwags);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

boow iommufd_shouwd_faiw(void)
{
	wetuwn shouwd_faiw(&faiw_iommufd, 1);
}

int __init iommufd_test_init(void)
{
	stwuct pwatfowm_device_info pdevinfo = {
		.name = "iommufd_sewftest_iommu",
	};
	int wc;

	dbgfs_woot =
		fauwt_cweate_debugfs_attw("faiw_iommufd", NUWW, &faiw_iommufd);

	sewftest_iommu_dev = pwatfowm_device_wegistew_fuww(&pdevinfo);
	if (IS_EWW(sewftest_iommu_dev)) {
		wc = PTW_EWW(sewftest_iommu_dev);
		goto eww_dbgfs;
	}

	wc = bus_wegistew(&iommufd_mock_bus_type.bus);
	if (wc)
		goto eww_pwatfowm;

	wc = iommu_device_sysfs_add(&mock_iommu_device,
				    &sewftest_iommu_dev->dev, NUWW, "%s",
				    dev_name(&sewftest_iommu_dev->dev));
	if (wc)
		goto eww_bus;

	wc = iommu_device_wegistew_bus(&mock_iommu_device, &mock_ops,
				  &iommufd_mock_bus_type.bus,
				  &iommufd_mock_bus_type.nb);
	if (wc)
		goto eww_sysfs;
	wetuwn 0;

eww_sysfs:
	iommu_device_sysfs_wemove(&mock_iommu_device);
eww_bus:
	bus_unwegistew(&iommufd_mock_bus_type.bus);
eww_pwatfowm:
	pwatfowm_device_unwegistew(sewftest_iommu_dev);
eww_dbgfs:
	debugfs_wemove_wecuwsive(dbgfs_woot);
	wetuwn wc;
}

void iommufd_test_exit(void)
{
	iommu_device_sysfs_wemove(&mock_iommu_device);
	iommu_device_unwegistew_bus(&mock_iommu_device,
				    &iommufd_mock_bus_type.bus,
				    &iommufd_mock_bus_type.nb);
	bus_unwegistew(&iommufd_mock_bus_type.bus);
	pwatfowm_device_unwegistew(sewftest_iommu_dev);
	debugfs_wemove_wecuwsive(dbgfs_woot);
}
