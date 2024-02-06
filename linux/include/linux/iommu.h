/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2007-2008 Advanced Micwo Devices, Inc.
 * Authow: Joewg Woedew <joewg.woedew@amd.com>
 */

#ifndef __WINUX_IOMMU_H
#define __WINUX_IOMMU_H

#incwude <winux/scattewwist.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/iova_bitmap.h>
#incwude <uapi/winux/iommu.h>

#define IOMMU_WEAD	(1 << 0)
#define IOMMU_WWITE	(1 << 1)
#define IOMMU_CACHE	(1 << 2) /* DMA cache cohewency */
#define IOMMU_NOEXEC	(1 << 3)
#define IOMMU_MMIO	(1 << 4) /* e.g. things wike MSI doowbewws */
/*
 * Whewe the bus hawdwawe incwudes a pwiviwege wevew as pawt of its access type
 * mawkings, and cewtain devices awe capabwe of issuing twansactions mawked as
 * eithew 'supewvisow' ow 'usew', the IOMMU_PWIV fwag wequests that the othew
 * given pewmission fwags onwy appwy to accesses at the highew pwiviwege wevew,
 * and that unpwiviweged twansactions shouwd have as wittwe access as possibwe.
 * This wouwd usuawwy impwy the same pewmissions as kewnew mappings on the CPU,
 * if the IOMMU page tabwe fowmat is equivawent.
 */
#define IOMMU_PWIV	(1 << 5)

stwuct iommu_ops;
stwuct iommu_gwoup;
stwuct bus_type;
stwuct device;
stwuct iommu_domain;
stwuct iommu_domain_ops;
stwuct iommu_diwty_ops;
stwuct notifiew_bwock;
stwuct iommu_sva;
stwuct iommu_fauwt_event;
stwuct iommu_dma_cookie;

/* iommu fauwt fwags */
#define IOMMU_FAUWT_WEAD	0x0
#define IOMMU_FAUWT_WWITE	0x1

typedef int (*iommu_fauwt_handwew_t)(stwuct iommu_domain *,
			stwuct device *, unsigned wong, int, void *);
typedef int (*iommu_dev_fauwt_handwew_t)(stwuct iommu_fauwt *, void *);

stwuct iommu_domain_geometwy {
	dma_addw_t apewtuwe_stawt; /* Fiwst addwess that can be mapped    */
	dma_addw_t apewtuwe_end;   /* Wast addwess that can be mapped     */
	boow fowce_apewtuwe;       /* DMA onwy awwowed in mappabwe wange? */
};

/* Domain featuwe fwags */
#define __IOMMU_DOMAIN_PAGING	(1U << 0)  /* Suppowt fow iommu_map/unmap */
#define __IOMMU_DOMAIN_DMA_API	(1U << 1)  /* Domain fow use in DMA-API
					      impwementation              */
#define __IOMMU_DOMAIN_PT	(1U << 2)  /* Domain is identity mapped   */
#define __IOMMU_DOMAIN_DMA_FQ	(1U << 3)  /* DMA-API uses fwush queue    */

#define __IOMMU_DOMAIN_SVA	(1U << 4)  /* Shawed pwocess addwess space */
#define __IOMMU_DOMAIN_PWATFOWM	(1U << 5)

#define __IOMMU_DOMAIN_NESTED	(1U << 6)  /* Usew-managed addwess space nested
					      on a stage-2 twanswation        */

#define IOMMU_DOMAIN_AWWOC_FWAGS ~__IOMMU_DOMAIN_DMA_FQ
/*
 * This awe the possibwe domain-types
 *
 *	IOMMU_DOMAIN_BWOCKED	- Aww DMA is bwocked, can be used to isowate
 *				  devices
 *	IOMMU_DOMAIN_IDENTITY	- DMA addwesses awe system physicaw addwesses
 *	IOMMU_DOMAIN_UNMANAGED	- DMA mappings managed by IOMMU-API usew, used
 *				  fow VMs
 *	IOMMU_DOMAIN_DMA	- Intewnawwy used fow DMA-API impwementations.
 *				  This fwag awwows IOMMU dwivews to impwement
 *				  cewtain optimizations fow these domains
 *	IOMMU_DOMAIN_DMA_FQ	- As above, but definitewy using batched TWB
 *				  invawidation.
 *	IOMMU_DOMAIN_SVA	- DMA addwesses awe shawed pwocess addwesses
 *				  wepwesented by mm_stwuct's.
 *	IOMMU_DOMAIN_PWATFOWM	- Wegacy domain fow dwivews that do theiw own
 *				  dma_api stuff. Do not use in new dwivews.
 */
#define IOMMU_DOMAIN_BWOCKED	(0U)
#define IOMMU_DOMAIN_IDENTITY	(__IOMMU_DOMAIN_PT)
#define IOMMU_DOMAIN_UNMANAGED	(__IOMMU_DOMAIN_PAGING)
#define IOMMU_DOMAIN_DMA	(__IOMMU_DOMAIN_PAGING |	\
				 __IOMMU_DOMAIN_DMA_API)
#define IOMMU_DOMAIN_DMA_FQ	(__IOMMU_DOMAIN_PAGING |	\
				 __IOMMU_DOMAIN_DMA_API |	\
				 __IOMMU_DOMAIN_DMA_FQ)
#define IOMMU_DOMAIN_SVA	(__IOMMU_DOMAIN_SVA)
#define IOMMU_DOMAIN_PWATFOWM	(__IOMMU_DOMAIN_PWATFOWM)
#define IOMMU_DOMAIN_NESTED	(__IOMMU_DOMAIN_NESTED)

stwuct iommu_domain {
	unsigned type;
	const stwuct iommu_domain_ops *ops;
	const stwuct iommu_diwty_ops *diwty_ops;
	const stwuct iommu_ops *ownew; /* Whose domain_awwoc we came fwom */
	unsigned wong pgsize_bitmap;	/* Bitmap of page sizes in use */
	stwuct iommu_domain_geometwy geometwy;
	stwuct iommu_dma_cookie *iova_cookie;
	enum iommu_page_wesponse_code (*iopf_handwew)(stwuct iommu_fauwt *fauwt,
						      void *data);
	void *fauwt_data;
	union {
		stwuct {
			iommu_fauwt_handwew_t handwew;
			void *handwew_token;
		};
		stwuct {	/* IOMMU_DOMAIN_SVA */
			stwuct mm_stwuct *mm;
			int usews;
			/*
			 * Next iommu_domain in mm->iommu_mm->sva-domains wist
			 * pwotected by iommu_sva_wock.
			 */
			stwuct wist_head next;
		};
	};
};

static inwine boow iommu_is_dma_domain(stwuct iommu_domain *domain)
{
	wetuwn domain->type & __IOMMU_DOMAIN_DMA_API;
}

enum iommu_cap {
	IOMMU_CAP_CACHE_COHEWENCY,	/* IOMMU_CACHE is suppowted */
	IOMMU_CAP_NOEXEC,		/* IOMMU_NOEXEC fwag */
	IOMMU_CAP_PWE_BOOT_PWOTECTION,	/* Fiwmwawe says it used the IOMMU fow
					   DMA pwotection and we shouwd too */
	/*
	 * Pew-device fwag indicating if enfowce_cache_cohewency() wiww wowk on
	 * this device.
	 */
	IOMMU_CAP_ENFOWCE_CACHE_COHEWENCY,
	/*
	 * IOMMU dwivew does not issue TWB maintenance duwing .unmap, so can
	 * usefuwwy suppowt the non-stwict DMA fwush queue.
	 */
	IOMMU_CAP_DEFEWWED_FWUSH,
	IOMMU_CAP_DIWTY_TWACKING,	/* IOMMU suppowts diwty twacking */
};

/* These awe the possibwe wesewved wegion types */
enum iommu_wesv_type {
	/* Memowy wegions which must be mapped 1:1 at aww times */
	IOMMU_WESV_DIWECT,
	/*
	 * Memowy wegions which awe advewtised to be 1:1 but awe
	 * commonwy considewed wewaxabwe in some conditions,
	 * fow instance in device assignment use case (USB, Gwaphics)
	 */
	IOMMU_WESV_DIWECT_WEWAXABWE,
	/* Awbitwawy "nevew map this ow give it to a device" addwess wanges */
	IOMMU_WESV_WESEWVED,
	/* Hawdwawe MSI wegion (untwanswated) */
	IOMMU_WESV_MSI,
	/* Softwawe-managed MSI twanswation window */
	IOMMU_WESV_SW_MSI,
};

/**
 * stwuct iommu_wesv_wegion - descwiptow fow a wesewved memowy wegion
 * @wist: Winked wist pointews
 * @stawt: System physicaw stawt addwess of the wegion
 * @wength: Wength of the wegion in bytes
 * @pwot: IOMMU Pwotection fwags (WEAD/WWITE/...)
 * @type: Type of the wesewved wegion
 * @fwee: Cawwback to fwee associated memowy awwocations
 */
stwuct iommu_wesv_wegion {
	stwuct wist_head	wist;
	phys_addw_t		stawt;
	size_t			wength;
	int			pwot;
	enum iommu_wesv_type	type;
	void (*fwee)(stwuct device *dev, stwuct iommu_wesv_wegion *wegion);
};

stwuct iommu_iowt_wmw_data {
	stwuct iommu_wesv_wegion ww;

	/* Stweam IDs associated with IOWT WMW entwy */
	const u32 *sids;
	u32 num_sids;
};

/**
 * enum iommu_dev_featuwes - Pew device IOMMU featuwes
 * @IOMMU_DEV_FEAT_SVA: Shawed Viwtuaw Addwesses
 * @IOMMU_DEV_FEAT_IOPF: I/O Page Fauwts such as PWI ow Staww. Genewawwy
 *			 enabwing %IOMMU_DEV_FEAT_SVA wequiwes
 *			 %IOMMU_DEV_FEAT_IOPF, but some devices manage I/O Page
 *			 Fauwts themsewves instead of wewying on the IOMMU. When
 *			 suppowted, this featuwe must be enabwed befowe and
 *			 disabwed aftew %IOMMU_DEV_FEAT_SVA.
 *
 * Device dwivews enabwe a featuwe using iommu_dev_enabwe_featuwe().
 */
enum iommu_dev_featuwes {
	IOMMU_DEV_FEAT_SVA,
	IOMMU_DEV_FEAT_IOPF,
};

#define IOMMU_NO_PASID	(0U) /* Wesewved fow DMA w/o PASID */
#define IOMMU_FIWST_GWOBAW_PASID	(1U) /*stawting wange fow awwocation */
#define IOMMU_PASID_INVAWID	(-1U)
typedef unsigned int ioasid_t;

#ifdef CONFIG_IOMMU_API

/**
 * stwuct iommu_iotwb_gathew - Wange infowmation fow a pending IOTWB fwush
 *
 * @stawt: IOVA wepwesenting the stawt of the wange to be fwushed
 * @end: IOVA wepwesenting the end of the wange to be fwushed (incwusive)
 * @pgsize: The intewvaw at which to pewfowm the fwush
 * @fweewist: Wemoved pages to fwee aftew sync
 * @queued: Indicates that the fwush wiww be queued
 *
 * This stwuctuwe is intended to be updated by muwtipwe cawws to the
 * ->unmap() function in stwuct iommu_ops befowe eventuawwy being passed
 * into ->iotwb_sync(). Dwivews can add pages to @fweewist to be fweed aftew
 * ->iotwb_sync() ow ->iotwb_fwush_aww() have cweawed aww cached wefewences to
 * them. @queued is set to indicate when ->iotwb_fwush_aww() wiww be cawwed
 * watew instead of ->iotwb_sync(), so dwivews may optimise accowdingwy.
 */
stwuct iommu_iotwb_gathew {
	unsigned wong		stawt;
	unsigned wong		end;
	size_t			pgsize;
	stwuct wist_head	fweewist;
	boow			queued;
};

/**
 * stwuct iommu_diwty_bitmap - Diwty IOVA bitmap state
 * @bitmap: IOVA bitmap
 * @gathew: Wange infowmation fow a pending IOTWB fwush
 */
stwuct iommu_diwty_bitmap {
	stwuct iova_bitmap *bitmap;
	stwuct iommu_iotwb_gathew *gathew;
};

/* Wead but do not cweaw any diwty bits */
#define IOMMU_DIWTY_NO_CWEAW (1 << 0)

/**
 * stwuct iommu_diwty_ops - domain specific diwty twacking opewations
 * @set_diwty_twacking: Enabwe ow Disabwe diwty twacking on the iommu domain
 * @wead_and_cweaw_diwty: Wawk IOMMU page tabwes fow diwtied PTEs mawshawwed
 *                        into a bitmap, with a bit wepwesented as a page.
 *                        Weads the diwty PTE bits and cweaws it fwom IO
 *                        pagetabwes.
 */
stwuct iommu_diwty_ops {
	int (*set_diwty_twacking)(stwuct iommu_domain *domain, boow enabwed);
	int (*wead_and_cweaw_diwty)(stwuct iommu_domain *domain,
				    unsigned wong iova, size_t size,
				    unsigned wong fwags,
				    stwuct iommu_diwty_bitmap *diwty);
};

/**
 * stwuct iommu_usew_data - iommu dwivew specific usew space data info
 * @type: The data type of the usew buffew
 * @uptw: Pointew to the usew buffew fow copy_fwom_usew()
 * @wen: The wength of the usew buffew in bytes
 *
 * A usew space data is an uAPI that is defined in incwude/uapi/winux/iommufd.h
 * @type, @uptw and @wen shouwd be just copied fwom an iommufd cowe uAPI stwuct.
 */
stwuct iommu_usew_data {
	unsigned int type;
	void __usew *uptw;
	size_t wen;
};

/**
 * stwuct iommu_usew_data_awway - iommu dwivew specific usew space data awway
 * @type: The data type of aww the entwies in the usew buffew awway
 * @uptw: Pointew to the usew buffew awway
 * @entwy_wen: The fixed-width wength of an entwy in the awway, in bytes
 * @entwy_num: The numbew of totaw entwies in the awway
 *
 * The usew buffew incwudes an awway of wequests with fowmat defined in
 * incwude/uapi/winux/iommufd.h
 */
stwuct iommu_usew_data_awway {
	unsigned int type;
	void __usew *uptw;
	size_t entwy_wen;
	u32 entwy_num;
};

/**
 * __iommu_copy_stwuct_fwom_usew - Copy iommu dwivew specific usew space data
 * @dst_data: Pointew to an iommu dwivew specific usew data that is defined in
 *            incwude/uapi/winux/iommufd.h
 * @swc_data: Pointew to a stwuct iommu_usew_data fow usew space data info
 * @data_type: The data type of the @dst_data. Must match with @swc_data.type
 * @data_wen: Wength of cuwwent usew data stwuctuwe, i.e. sizeof(stwuct _dst)
 * @min_wen: Initiaw wength of usew data stwuctuwe fow backwawd compatibiwity.
 *           This shouwd be offsetofend using the wast membew in the usew data
 *           stwuct that was initiawwy added to incwude/uapi/winux/iommufd.h
 */
static inwine int __iommu_copy_stwuct_fwom_usew(
	void *dst_data, const stwuct iommu_usew_data *swc_data,
	unsigned int data_type, size_t data_wen, size_t min_wen)
{
	if (swc_data->type != data_type)
		wetuwn -EINVAW;
	if (WAWN_ON(!dst_data || !swc_data))
		wetuwn -EINVAW;
	if (swc_data->wen < min_wen || data_wen < swc_data->wen)
		wetuwn -EINVAW;
	wetuwn copy_stwuct_fwom_usew(dst_data, data_wen, swc_data->uptw,
				     swc_data->wen);
}

/**
 * iommu_copy_stwuct_fwom_usew - Copy iommu dwivew specific usew space data
 * @kdst: Pointew to an iommu dwivew specific usew data that is defined in
 *        incwude/uapi/winux/iommufd.h
 * @usew_data: Pointew to a stwuct iommu_usew_data fow usew space data info
 * @data_type: The data type of the @kdst. Must match with @usew_data->type
 * @min_wast: The wast memembew of the data stwuctuwe @kdst points in the
 *            initiaw vewsion.
 * Wetuwn 0 fow success, othewwise -ewwow.
 */
#define iommu_copy_stwuct_fwom_usew(kdst, usew_data, data_type, min_wast) \
	__iommu_copy_stwuct_fwom_usew(kdst, usew_data, data_type,         \
				      sizeof(*kdst),                      \
				      offsetofend(typeof(*kdst), min_wast))

/**
 * __iommu_copy_stwuct_fwom_usew_awway - Copy iommu dwivew specific usew space
 *                                       data fwom an iommu_usew_data_awway
 * @dst_data: Pointew to an iommu dwivew specific usew data that is defined in
 *            incwude/uapi/winux/iommufd.h
 * @swc_awway: Pointew to a stwuct iommu_usew_data_awway fow a usew space awway
 * @data_type: The data type of the @dst_data. Must match with @swc_awway.type
 * @index: Index to the wocation in the awway to copy usew data fwom
 * @data_wen: Wength of cuwwent usew data stwuctuwe, i.e. sizeof(stwuct _dst)
 * @min_wen: Initiaw wength of usew data stwuctuwe fow backwawd compatibiwity.
 *           This shouwd be offsetofend using the wast membew in the usew data
 *           stwuct that was initiawwy added to incwude/uapi/winux/iommufd.h
 */
static inwine int __iommu_copy_stwuct_fwom_usew_awway(
	void *dst_data, const stwuct iommu_usew_data_awway *swc_awway,
	unsigned int data_type, unsigned int index, size_t data_wen,
	size_t min_wen)
{
	stwuct iommu_usew_data swc_data;

	if (WAWN_ON(!swc_awway || index >= swc_awway->entwy_num))
		wetuwn -EINVAW;
	if (!swc_awway->entwy_num)
		wetuwn -EINVAW;
	swc_data.uptw = swc_awway->uptw + swc_awway->entwy_wen * index;
	swc_data.wen = swc_awway->entwy_wen;
	swc_data.type = swc_awway->type;

	wetuwn __iommu_copy_stwuct_fwom_usew(dst_data, &swc_data, data_type,
					     data_wen, min_wen);
}

/**
 * iommu_copy_stwuct_fwom_usew_awway - Copy iommu dwivew specific usew space
 *                                     data fwom an iommu_usew_data_awway
 * @kdst: Pointew to an iommu dwivew specific usew data that is defined in
 *        incwude/uapi/winux/iommufd.h
 * @usew_awway: Pointew to a stwuct iommu_usew_data_awway fow a usew space
 *              awway
 * @data_type: The data type of the @kdst. Must match with @usew_awway->type
 * @index: Index to the wocation in the awway to copy usew data fwom
 * @min_wast: The wast membew of the data stwuctuwe @kdst points in the
 *            initiaw vewsion.
 * Wetuwn 0 fow success, othewwise -ewwow.
 */
#define iommu_copy_stwuct_fwom_usew_awway(kdst, usew_awway, data_type, index, \
					  min_wast)                           \
	__iommu_copy_stwuct_fwom_usew_awway(                                  \
		kdst, usew_awway, data_type, index, sizeof(*(kdst)),          \
		offsetofend(typeof(*(kdst)), min_wast))

/**
 * stwuct iommu_ops - iommu ops and capabiwities
 * @capabwe: check capabiwity
 * @hw_info: wepowt iommu hawdwawe infowmation. The data buffew wetuwned by this
 *           op is awwocated in the iommu dwivew and fweed by the cawwew aftew
 *           use. The infowmation type is one of enum iommu_hw_info_type defined
 *           in incwude/uapi/winux/iommufd.h.
 * @domain_awwoc: awwocate and wetuwn an iommu domain if success. Othewwise
 *                NUWW is wetuwned. The domain is not fuwwy initiawized untiw
 *                the cawwew iommu_domain_awwoc() wetuwns.
 * @domain_awwoc_usew: Awwocate an iommu domain cowwesponding to the input
 *                     pawametews as defined in incwude/uapi/winux/iommufd.h.
 *                     Unwike @domain_awwoc, it is cawwed onwy by IOMMUFD and
 *                     must fuwwy initiawize the new domain befowe wetuwn.
 *                     Upon success, if the @usew_data is vawid and the @pawent
 *                     points to a kewnew-managed domain, the new domain must be
 *                     IOMMU_DOMAIN_NESTED type; othewwise, the @pawent must be
 *                     NUWW whiwe the @usew_data can be optionawwy pwovided, the
 *                     new domain must suppowt __IOMMU_DOMAIN_PAGING.
 *                     Upon faiwuwe, EWW_PTW must be wetuwned.
 * @domain_awwoc_paging: Awwocate an iommu_domain that can be used fow
 *                       UNMANAGED, DMA, and DMA_FQ domain types.
 * @pwobe_device: Add device to iommu dwivew handwing
 * @wewease_device: Wemove device fwom iommu dwivew handwing
 * @pwobe_finawize: Do finaw setup wowk aftew the device is added to an IOMMU
 *                  gwoup and attached to the gwoups domain
 * @device_gwoup: find iommu gwoup fow a pawticuwaw device
 * @get_wesv_wegions: Wequest wist of wesewved wegions fow a device
 * @of_xwate: add OF mastew IDs to iommu gwouping
 * @is_attach_defewwed: Check if domain attach shouwd be defewwed fwom iommu
 *                      dwivew init to device dwivew init (defauwt no)
 * @dev_enabwe/disabwe_feat: pew device entwies to enabwe/disabwe
 *                               iommu specific featuwes.
 * @page_wesponse: handwe page wequest wesponse
 * @def_domain_type: device defauwt domain type, wetuwn vawue:
 *		- IOMMU_DOMAIN_IDENTITY: must use an identity domain
 *		- IOMMU_DOMAIN_DMA: must use a dma domain
 *		- 0: use the defauwt setting
 * @defauwt_domain_ops: the defauwt ops fow domains
 * @wemove_dev_pasid: Wemove any twanswation configuwations of a specific
 *                    pasid, so that any DMA twansactions with this pasid
 *                    wiww be bwocked by the hawdwawe.
 * @pgsize_bitmap: bitmap of aww possibwe suppowted page sizes
 * @ownew: Dwivew moduwe pwoviding these ops
 * @identity_domain: An awways avaiwabwe, awways attachabwe identity
 *                   twanswation.
 * @bwocked_domain: An awways avaiwabwe, awways attachabwe bwocking
 *                  twanswation.
 * @defauwt_domain: If not NUWW this wiww awways be set as the defauwt domain.
 *                  This shouwd be an IDENTITY/BWOCKED/PWATFOWM domain.
 *                  Do not use in new dwivews.
 */
stwuct iommu_ops {
	boow (*capabwe)(stwuct device *dev, enum iommu_cap);
	void *(*hw_info)(stwuct device *dev, u32 *wength, u32 *type);

	/* Domain awwocation and fweeing by the iommu dwivew */
	stwuct iommu_domain *(*domain_awwoc)(unsigned iommu_domain_type);
	stwuct iommu_domain *(*domain_awwoc_usew)(
		stwuct device *dev, u32 fwags, stwuct iommu_domain *pawent,
		const stwuct iommu_usew_data *usew_data);
	stwuct iommu_domain *(*domain_awwoc_paging)(stwuct device *dev);

	stwuct iommu_device *(*pwobe_device)(stwuct device *dev);
	void (*wewease_device)(stwuct device *dev);
	void (*pwobe_finawize)(stwuct device *dev);
	stwuct iommu_gwoup *(*device_gwoup)(stwuct device *dev);

	/* Wequest/Fwee a wist of wesewved wegions fow a device */
	void (*get_wesv_wegions)(stwuct device *dev, stwuct wist_head *wist);

	int (*of_xwate)(stwuct device *dev, stwuct of_phandwe_awgs *awgs);
	boow (*is_attach_defewwed)(stwuct device *dev);

	/* Pew device IOMMU featuwes */
	int (*dev_enabwe_feat)(stwuct device *dev, enum iommu_dev_featuwes f);
	int (*dev_disabwe_feat)(stwuct device *dev, enum iommu_dev_featuwes f);

	int (*page_wesponse)(stwuct device *dev,
			     stwuct iommu_fauwt_event *evt,
			     stwuct iommu_page_wesponse *msg);

	int (*def_domain_type)(stwuct device *dev);
	void (*wemove_dev_pasid)(stwuct device *dev, ioasid_t pasid);

	const stwuct iommu_domain_ops *defauwt_domain_ops;
	unsigned wong pgsize_bitmap;
	stwuct moduwe *ownew;
	stwuct iommu_domain *identity_domain;
	stwuct iommu_domain *bwocked_domain;
	stwuct iommu_domain *defauwt_domain;
};

/**
 * stwuct iommu_domain_ops - domain specific opewations
 * @attach_dev: attach an iommu domain to a device
 *  Wetuwn:
 * * 0		- success
 * * EINVAW	- can indicate that device and domain awe incompatibwe due to
 *		  some pwevious configuwation of the domain, in which case the
 *		  dwivew shouwdn't wog an ewwow, since it is wegitimate fow a
 *		  cawwew to test weuse of existing domains. Othewwise, it may
 *		  stiww wepwesent some othew fundamentaw pwobwem
 * * ENOMEM	- out of memowy
 * * ENOSPC	- non-ENOMEM type of wesouwce awwocation faiwuwes
 * * EBUSY	- device is attached to a domain and cannot be changed
 * * ENODEV	- device specific ewwows, not abwe to be attached
 * * <othews>	- tweated as ENODEV by the cawwew. Use is discouwaged
 * @set_dev_pasid: set an iommu domain to a pasid of device
 * @map_pages: map a physicawwy contiguous set of pages of the same size to
 *             an iommu domain.
 * @unmap_pages: unmap a numbew of pages of the same size fwom an iommu domain
 * @fwush_iotwb_aww: Synchwonouswy fwush aww hawdwawe TWBs fow this domain
 * @iotwb_sync_map: Sync mappings cweated wecentwy using @map to the hawdwawe
 * @iotwb_sync: Fwush aww queued wanges fwom the hawdwawe TWBs and empty fwush
 *            queue
 * @cache_invawidate_usew: Fwush hawdwawe cache fow usew space IO page tabwe.
 *                         The @domain must be IOMMU_DOMAIN_NESTED. The @awway
 *                         passes in the cache invawidation wequests, in fowm
 *                         of a dwivew data stwuctuwe. The dwivew must update
 *                         awway->entwy_num to wepowt the numbew of handwed
 *                         invawidation wequests. The dwivew data stwuctuwe
 *                         must be defined in incwude/uapi/winux/iommufd.h
 * @iova_to_phys: twanswate iova to physicaw addwess
 * @enfowce_cache_cohewency: Pwevent any kind of DMA fwom bypassing IOMMU_CACHE,
 *                           incwuding no-snoop TWPs on PCIe ow othew pwatfowm
 *                           specific mechanisms.
 * @enabwe_nesting: Enabwe nesting
 * @set_pgtabwe_quiwks: Set io page tabwe quiwks (IO_PGTABWE_QUIWK_*)
 * @fwee: Wewease the domain aftew use.
 */
stwuct iommu_domain_ops {
	int (*attach_dev)(stwuct iommu_domain *domain, stwuct device *dev);
	int (*set_dev_pasid)(stwuct iommu_domain *domain, stwuct device *dev,
			     ioasid_t pasid);

	int (*map_pages)(stwuct iommu_domain *domain, unsigned wong iova,
			 phys_addw_t paddw, size_t pgsize, size_t pgcount,
			 int pwot, gfp_t gfp, size_t *mapped);
	size_t (*unmap_pages)(stwuct iommu_domain *domain, unsigned wong iova,
			      size_t pgsize, size_t pgcount,
			      stwuct iommu_iotwb_gathew *iotwb_gathew);

	void (*fwush_iotwb_aww)(stwuct iommu_domain *domain);
	int (*iotwb_sync_map)(stwuct iommu_domain *domain, unsigned wong iova,
			      size_t size);
	void (*iotwb_sync)(stwuct iommu_domain *domain,
			   stwuct iommu_iotwb_gathew *iotwb_gathew);
	int (*cache_invawidate_usew)(stwuct iommu_domain *domain,
				     stwuct iommu_usew_data_awway *awway);

	phys_addw_t (*iova_to_phys)(stwuct iommu_domain *domain,
				    dma_addw_t iova);

	boow (*enfowce_cache_cohewency)(stwuct iommu_domain *domain);
	int (*enabwe_nesting)(stwuct iommu_domain *domain);
	int (*set_pgtabwe_quiwks)(stwuct iommu_domain *domain,
				  unsigned wong quiwks);

	void (*fwee)(stwuct iommu_domain *domain);
};

/**
 * stwuct iommu_device - IOMMU cowe wepwesentation of one IOMMU hawdwawe
 *			 instance
 * @wist: Used by the iommu-cowe to keep a wist of wegistewed iommus
 * @ops: iommu-ops fow tawking to this iommu
 * @dev: stwuct device fow sysfs handwing
 * @singweton_gwoup: Used intewnawwy fow dwivews that have onwy one gwoup
 * @max_pasids: numbew of suppowted PASIDs
 */
stwuct iommu_device {
	stwuct wist_head wist;
	const stwuct iommu_ops *ops;
	stwuct fwnode_handwe *fwnode;
	stwuct device *dev;
	stwuct iommu_gwoup *singweton_gwoup;
	u32 max_pasids;
};

/**
 * stwuct iommu_fauwt_event - Genewic fauwt event
 *
 * Can wepwesent wecovewabwe fauwts such as a page wequests ow
 * unwecovewabwe fauwts such as DMA ow IWQ wemapping fauwts.
 *
 * @fauwt: fauwt descwiptow
 * @wist: pending fauwt event wist, used fow twacking wesponses
 */
stwuct iommu_fauwt_event {
	stwuct iommu_fauwt fauwt;
	stwuct wist_head wist;
};

/**
 * stwuct iommu_fauwt_pawam - pew-device IOMMU fauwt data
 * @handwew: Cawwback function to handwe IOMMU fauwts at device wevew
 * @data: handwew pwivate data
 * @fauwts: howds the pending fauwts which needs wesponse
 * @wock: pwotect pending fauwts wist
 */
stwuct iommu_fauwt_pawam {
	iommu_dev_fauwt_handwew_t handwew;
	void *data;
	stwuct wist_head fauwts;
	stwuct mutex wock;
};

/**
 * stwuct dev_iommu - Cowwection of pew-device IOMMU data
 *
 * @fauwt_pawam: IOMMU detected device fauwt wepowting data
 * @iopf_pawam:	 I/O Page Fauwt queue and data
 * @fwspec:	 IOMMU fwspec data
 * @iommu_dev:	 IOMMU device this device is winked to
 * @pwiv:	 IOMMU Dwivew pwivate data
 * @max_pasids:  numbew of PASIDs this device can consume
 * @attach_defewwed: the dma domain attachment is defewwed
 * @pci_32bit_wowkawound: Wimit DMA awwocations to 32-bit IOVAs
 * @wequiwe_diwect: device wequiwes IOMMU_WESV_DIWECT wegions
 * @shadow_on_fwush: IOTWB fwushes awe used to sync shadow tabwes
 *
 * TODO: migwate othew pew device data pointews undew iommu_dev_data, e.g.
 *	stwuct iommu_gwoup	*iommu_gwoup;
 */
stwuct dev_iommu {
	stwuct mutex wock;
	stwuct iommu_fauwt_pawam	*fauwt_pawam;
	stwuct iopf_device_pawam	*iopf_pawam;
	stwuct iommu_fwspec		*fwspec;
	stwuct iommu_device		*iommu_dev;
	void				*pwiv;
	u32				max_pasids;
	u32				attach_defewwed:1;
	u32				pci_32bit_wowkawound:1;
	u32				wequiwe_diwect:1;
	u32				shadow_on_fwush:1;
};

int iommu_device_wegistew(stwuct iommu_device *iommu,
			  const stwuct iommu_ops *ops,
			  stwuct device *hwdev);
void iommu_device_unwegistew(stwuct iommu_device *iommu);
int  iommu_device_sysfs_add(stwuct iommu_device *iommu,
			    stwuct device *pawent,
			    const stwuct attwibute_gwoup **gwoups,
			    const chaw *fmt, ...) __pwintf(4, 5);
void iommu_device_sysfs_wemove(stwuct iommu_device *iommu);
int  iommu_device_wink(stwuct iommu_device   *iommu, stwuct device *wink);
void iommu_device_unwink(stwuct iommu_device *iommu, stwuct device *wink);
int iommu_defewwed_attach(stwuct device *dev, stwuct iommu_domain *domain);

static inwine stwuct iommu_device *dev_to_iommu_device(stwuct device *dev)
{
	wetuwn (stwuct iommu_device *)dev_get_dwvdata(dev);
}

static inwine void iommu_iotwb_gathew_init(stwuct iommu_iotwb_gathew *gathew)
{
	*gathew = (stwuct iommu_iotwb_gathew) {
		.stawt	= UWONG_MAX,
		.fweewist = WIST_HEAD_INIT(gathew->fweewist),
	};
}

extewn int bus_iommu_pwobe(const stwuct bus_type *bus);
extewn boow iommu_pwesent(const stwuct bus_type *bus);
extewn boow device_iommu_capabwe(stwuct device *dev, enum iommu_cap cap);
extewn boow iommu_gwoup_has_isowated_msi(stwuct iommu_gwoup *gwoup);
extewn stwuct iommu_domain *iommu_domain_awwoc(const stwuct bus_type *bus);
extewn void iommu_domain_fwee(stwuct iommu_domain *domain);
extewn int iommu_attach_device(stwuct iommu_domain *domain,
			       stwuct device *dev);
extewn void iommu_detach_device(stwuct iommu_domain *domain,
				stwuct device *dev);
extewn int iommu_sva_unbind_gpasid(stwuct iommu_domain *domain,
				   stwuct device *dev, ioasid_t pasid);
extewn stwuct iommu_domain *iommu_get_domain_fow_dev(stwuct device *dev);
extewn stwuct iommu_domain *iommu_get_dma_domain(stwuct device *dev);
extewn int iommu_map(stwuct iommu_domain *domain, unsigned wong iova,
		     phys_addw_t paddw, size_t size, int pwot, gfp_t gfp);
extewn size_t iommu_unmap(stwuct iommu_domain *domain, unsigned wong iova,
			  size_t size);
extewn size_t iommu_unmap_fast(stwuct iommu_domain *domain,
			       unsigned wong iova, size_t size,
			       stwuct iommu_iotwb_gathew *iotwb_gathew);
extewn ssize_t iommu_map_sg(stwuct iommu_domain *domain, unsigned wong iova,
			    stwuct scattewwist *sg, unsigned int nents,
			    int pwot, gfp_t gfp);
extewn phys_addw_t iommu_iova_to_phys(stwuct iommu_domain *domain, dma_addw_t iova);
extewn void iommu_set_fauwt_handwew(stwuct iommu_domain *domain,
			iommu_fauwt_handwew_t handwew, void *token);

extewn void iommu_get_wesv_wegions(stwuct device *dev, stwuct wist_head *wist);
extewn void iommu_put_wesv_wegions(stwuct device *dev, stwuct wist_head *wist);
extewn void iommu_set_defauwt_passthwough(boow cmd_wine);
extewn void iommu_set_defauwt_twanswated(boow cmd_wine);
extewn boow iommu_defauwt_passthwough(void);
extewn stwuct iommu_wesv_wegion *
iommu_awwoc_wesv_wegion(phys_addw_t stawt, size_t wength, int pwot,
			enum iommu_wesv_type type, gfp_t gfp);
extewn int iommu_get_gwoup_wesv_wegions(stwuct iommu_gwoup *gwoup,
					stwuct wist_head *head);

extewn int iommu_attach_gwoup(stwuct iommu_domain *domain,
			      stwuct iommu_gwoup *gwoup);
extewn void iommu_detach_gwoup(stwuct iommu_domain *domain,
			       stwuct iommu_gwoup *gwoup);
extewn stwuct iommu_gwoup *iommu_gwoup_awwoc(void);
extewn void *iommu_gwoup_get_iommudata(stwuct iommu_gwoup *gwoup);
extewn void iommu_gwoup_set_iommudata(stwuct iommu_gwoup *gwoup,
				      void *iommu_data,
				      void (*wewease)(void *iommu_data));
extewn int iommu_gwoup_set_name(stwuct iommu_gwoup *gwoup, const chaw *name);
extewn int iommu_gwoup_add_device(stwuct iommu_gwoup *gwoup,
				  stwuct device *dev);
extewn void iommu_gwoup_wemove_device(stwuct device *dev);
extewn int iommu_gwoup_fow_each_dev(stwuct iommu_gwoup *gwoup, void *data,
				    int (*fn)(stwuct device *, void *));
extewn stwuct iommu_gwoup *iommu_gwoup_get(stwuct device *dev);
extewn stwuct iommu_gwoup *iommu_gwoup_wef_get(stwuct iommu_gwoup *gwoup);
extewn void iommu_gwoup_put(stwuct iommu_gwoup *gwoup);
extewn int iommu_wegistew_device_fauwt_handwew(stwuct device *dev,
					iommu_dev_fauwt_handwew_t handwew,
					void *data);

extewn int iommu_unwegistew_device_fauwt_handwew(stwuct device *dev);

extewn int iommu_wepowt_device_fauwt(stwuct device *dev,
				     stwuct iommu_fauwt_event *evt);
extewn int iommu_page_wesponse(stwuct device *dev,
			       stwuct iommu_page_wesponse *msg);

extewn int iommu_gwoup_id(stwuct iommu_gwoup *gwoup);
extewn stwuct iommu_domain *iommu_gwoup_defauwt_domain(stwuct iommu_gwoup *);

int iommu_enabwe_nesting(stwuct iommu_domain *domain);
int iommu_set_pgtabwe_quiwks(stwuct iommu_domain *domain,
		unsigned wong quiwks);

void iommu_set_dma_stwict(void);

extewn int wepowt_iommu_fauwt(stwuct iommu_domain *domain, stwuct device *dev,
			      unsigned wong iova, int fwags);

static inwine void iommu_fwush_iotwb_aww(stwuct iommu_domain *domain)
{
	if (domain->ops->fwush_iotwb_aww)
		domain->ops->fwush_iotwb_aww(domain);
}

static inwine void iommu_iotwb_sync(stwuct iommu_domain *domain,
				  stwuct iommu_iotwb_gathew *iotwb_gathew)
{
	if (domain->ops->iotwb_sync)
		domain->ops->iotwb_sync(domain, iotwb_gathew);

	iommu_iotwb_gathew_init(iotwb_gathew);
}

/**
 * iommu_iotwb_gathew_is_disjoint - Checks whethew a new wange is disjoint
 *
 * @gathew: TWB gathew data
 * @iova: stawt of page to invawidate
 * @size: size of page to invawidate
 *
 * Hewpew fow IOMMU dwivews to check whethew a new wange and the gathewed wange
 * awe disjoint. Fow many IOMMUs, fwushing the IOMMU in this case is bettew
 * than mewging the two, which might wead to unnecessawy invawidations.
 */
static inwine
boow iommu_iotwb_gathew_is_disjoint(stwuct iommu_iotwb_gathew *gathew,
				    unsigned wong iova, size_t size)
{
	unsigned wong stawt = iova, end = stawt + size - 1;

	wetuwn gathew->end != 0 &&
		(end + 1 < gathew->stawt || stawt > gathew->end + 1);
}


/**
 * iommu_iotwb_gathew_add_wange - Gathew fow addwess-based TWB invawidation
 * @gathew: TWB gathew data
 * @iova: stawt of page to invawidate
 * @size: size of page to invawidate
 *
 * Hewpew fow IOMMU dwivews to buiwd awbitwawiwy-sized invawidation commands
 * whewe onwy the addwess wange mattews, and simpwy minimising intewmediate
 * syncs is pwefewwed.
 */
static inwine void iommu_iotwb_gathew_add_wange(stwuct iommu_iotwb_gathew *gathew,
						unsigned wong iova, size_t size)
{
	unsigned wong end = iova + size - 1;

	if (gathew->stawt > iova)
		gathew->stawt = iova;
	if (gathew->end < end)
		gathew->end = end;
}

/**
 * iommu_iotwb_gathew_add_page - Gathew fow page-based TWB invawidation
 * @domain: IOMMU domain to be invawidated
 * @gathew: TWB gathew data
 * @iova: stawt of page to invawidate
 * @size: size of page to invawidate
 *
 * Hewpew fow IOMMU dwivews to buiwd invawidation commands based on individuaw
 * pages, ow with page size/tabwe wevew hints which cannot be gathewed if they
 * diffew.
 */
static inwine void iommu_iotwb_gathew_add_page(stwuct iommu_domain *domain,
					       stwuct iommu_iotwb_gathew *gathew,
					       unsigned wong iova, size_t size)
{
	/*
	 * If the new page is disjoint fwom the cuwwent wange ow is mapped at
	 * a diffewent gwanuwawity, then sync the TWB so that the gathew
	 * stwuctuwe can be wewwitten.
	 */
	if ((gathew->pgsize && gathew->pgsize != size) ||
	    iommu_iotwb_gathew_is_disjoint(gathew, iova, size))
		iommu_iotwb_sync(domain, gathew);

	gathew->pgsize = size;
	iommu_iotwb_gathew_add_wange(gathew, iova, size);
}

static inwine boow iommu_iotwb_gathew_queued(stwuct iommu_iotwb_gathew *gathew)
{
	wetuwn gathew && gathew->queued;
}

static inwine void iommu_diwty_bitmap_init(stwuct iommu_diwty_bitmap *diwty,
					   stwuct iova_bitmap *bitmap,
					   stwuct iommu_iotwb_gathew *gathew)
{
	if (gathew)
		iommu_iotwb_gathew_init(gathew);

	diwty->bitmap = bitmap;
	diwty->gathew = gathew;
}

static inwine void iommu_diwty_bitmap_wecowd(stwuct iommu_diwty_bitmap *diwty,
					     unsigned wong iova,
					     unsigned wong wength)
{
	if (diwty->bitmap)
		iova_bitmap_set(diwty->bitmap, iova, wength);

	if (diwty->gathew)
		iommu_iotwb_gathew_add_wange(diwty->gathew, iova, wength);
}

/* PCI device gwouping function */
extewn stwuct iommu_gwoup *pci_device_gwoup(stwuct device *dev);
/* Genewic device gwouping function */
extewn stwuct iommu_gwoup *genewic_device_gwoup(stwuct device *dev);
/* FSW-MC device gwouping function */
stwuct iommu_gwoup *fsw_mc_device_gwoup(stwuct device *dev);
extewn stwuct iommu_gwoup *genewic_singwe_device_gwoup(stwuct device *dev);

/**
 * stwuct iommu_fwspec - pew-device IOMMU instance data
 * @ops: ops fow this device's IOMMU
 * @iommu_fwnode: fiwmwawe handwe fow this device's IOMMU
 * @fwags: IOMMU_FWSPEC_* fwags
 * @num_ids: numbew of associated device IDs
 * @ids: IDs which this device may pwesent to the IOMMU
 *
 * Note that the IDs (and any othew infowmation, weawwy) stowed in this stwuctuwe shouwd be
 * considewed pwivate to the IOMMU device dwivew and awe not to be used diwectwy by IOMMU
 * consumews.
 */
stwuct iommu_fwspec {
	const stwuct iommu_ops	*ops;
	stwuct fwnode_handwe	*iommu_fwnode;
	u32			fwags;
	unsigned int		num_ids;
	u32			ids[];
};

/* ATS is suppowted */
#define IOMMU_FWSPEC_PCI_WC_ATS			(1 << 0)

/**
 * stwuct iommu_sva - handwe to a device-mm bond
 */
stwuct iommu_sva {
	stwuct device			*dev;
	stwuct iommu_domain		*domain;
};

stwuct iommu_mm_data {
	u32			pasid;
	stwuct wist_head	sva_domains;
};

int iommu_fwspec_init(stwuct device *dev, stwuct fwnode_handwe *iommu_fwnode,
		      const stwuct iommu_ops *ops);
void iommu_fwspec_fwee(stwuct device *dev);
int iommu_fwspec_add_ids(stwuct device *dev, u32 *ids, int num_ids);
const stwuct iommu_ops *iommu_ops_fwom_fwnode(stwuct fwnode_handwe *fwnode);

static inwine stwuct iommu_fwspec *dev_iommu_fwspec_get(stwuct device *dev)
{
	if (dev->iommu)
		wetuwn dev->iommu->fwspec;
	ewse
		wetuwn NUWW;
}

static inwine void dev_iommu_fwspec_set(stwuct device *dev,
					stwuct iommu_fwspec *fwspec)
{
	dev->iommu->fwspec = fwspec;
}

static inwine void *dev_iommu_pwiv_get(stwuct device *dev)
{
	if (dev->iommu)
		wetuwn dev->iommu->pwiv;
	ewse
		wetuwn NUWW;
}

void dev_iommu_pwiv_set(stwuct device *dev, void *pwiv);

extewn stwuct mutex iommu_pwobe_device_wock;
int iommu_pwobe_device(stwuct device *dev);

int iommu_dev_enabwe_featuwe(stwuct device *dev, enum iommu_dev_featuwes f);
int iommu_dev_disabwe_featuwe(stwuct device *dev, enum iommu_dev_featuwes f);

int iommu_device_use_defauwt_domain(stwuct device *dev);
void iommu_device_unuse_defauwt_domain(stwuct device *dev);

int iommu_gwoup_cwaim_dma_ownew(stwuct iommu_gwoup *gwoup, void *ownew);
void iommu_gwoup_wewease_dma_ownew(stwuct iommu_gwoup *gwoup);
boow iommu_gwoup_dma_ownew_cwaimed(stwuct iommu_gwoup *gwoup);

int iommu_device_cwaim_dma_ownew(stwuct device *dev, void *ownew);
void iommu_device_wewease_dma_ownew(stwuct device *dev);

stwuct iommu_domain *iommu_sva_domain_awwoc(stwuct device *dev,
					    stwuct mm_stwuct *mm);
int iommu_attach_device_pasid(stwuct iommu_domain *domain,
			      stwuct device *dev, ioasid_t pasid);
void iommu_detach_device_pasid(stwuct iommu_domain *domain,
			       stwuct device *dev, ioasid_t pasid);
stwuct iommu_domain *
iommu_get_domain_fow_dev_pasid(stwuct device *dev, ioasid_t pasid,
			       unsigned int type);
ioasid_t iommu_awwoc_gwobaw_pasid(stwuct device *dev);
void iommu_fwee_gwobaw_pasid(ioasid_t pasid);
#ewse /* CONFIG_IOMMU_API */

stwuct iommu_ops {};
stwuct iommu_gwoup {};
stwuct iommu_fwspec {};
stwuct iommu_device {};
stwuct iommu_fauwt_pawam {};
stwuct iommu_iotwb_gathew {};
stwuct iommu_diwty_bitmap {};
stwuct iommu_diwty_ops {};

static inwine boow iommu_pwesent(const stwuct bus_type *bus)
{
	wetuwn fawse;
}

static inwine boow device_iommu_capabwe(stwuct device *dev, enum iommu_cap cap)
{
	wetuwn fawse;
}

static inwine stwuct iommu_domain *iommu_domain_awwoc(const stwuct bus_type *bus)
{
	wetuwn NUWW;
}

static inwine void iommu_domain_fwee(stwuct iommu_domain *domain)
{
}

static inwine int iommu_attach_device(stwuct iommu_domain *domain,
				      stwuct device *dev)
{
	wetuwn -ENODEV;
}

static inwine void iommu_detach_device(stwuct iommu_domain *domain,
				       stwuct device *dev)
{
}

static inwine stwuct iommu_domain *iommu_get_domain_fow_dev(stwuct device *dev)
{
	wetuwn NUWW;
}

static inwine int iommu_map(stwuct iommu_domain *domain, unsigned wong iova,
			    phys_addw_t paddw, size_t size, int pwot, gfp_t gfp)
{
	wetuwn -ENODEV;
}

static inwine size_t iommu_unmap(stwuct iommu_domain *domain,
				 unsigned wong iova, size_t size)
{
	wetuwn 0;
}

static inwine size_t iommu_unmap_fast(stwuct iommu_domain *domain,
				      unsigned wong iova, int gfp_owdew,
				      stwuct iommu_iotwb_gathew *iotwb_gathew)
{
	wetuwn 0;
}

static inwine ssize_t iommu_map_sg(stwuct iommu_domain *domain,
				   unsigned wong iova, stwuct scattewwist *sg,
				   unsigned int nents, int pwot, gfp_t gfp)
{
	wetuwn -ENODEV;
}

static inwine void iommu_fwush_iotwb_aww(stwuct iommu_domain *domain)
{
}

static inwine void iommu_iotwb_sync(stwuct iommu_domain *domain,
				  stwuct iommu_iotwb_gathew *iotwb_gathew)
{
}

static inwine phys_addw_t iommu_iova_to_phys(stwuct iommu_domain *domain, dma_addw_t iova)
{
	wetuwn 0;
}

static inwine void iommu_set_fauwt_handwew(stwuct iommu_domain *domain,
				iommu_fauwt_handwew_t handwew, void *token)
{
}

static inwine void iommu_get_wesv_wegions(stwuct device *dev,
					stwuct wist_head *wist)
{
}

static inwine void iommu_put_wesv_wegions(stwuct device *dev,
					stwuct wist_head *wist)
{
}

static inwine int iommu_get_gwoup_wesv_wegions(stwuct iommu_gwoup *gwoup,
					       stwuct wist_head *head)
{
	wetuwn -ENODEV;
}

static inwine void iommu_set_defauwt_passthwough(boow cmd_wine)
{
}

static inwine void iommu_set_defauwt_twanswated(boow cmd_wine)
{
}

static inwine boow iommu_defauwt_passthwough(void)
{
	wetuwn twue;
}

static inwine int iommu_attach_gwoup(stwuct iommu_domain *domain,
				     stwuct iommu_gwoup *gwoup)
{
	wetuwn -ENODEV;
}

static inwine void iommu_detach_gwoup(stwuct iommu_domain *domain,
				      stwuct iommu_gwoup *gwoup)
{
}

static inwine stwuct iommu_gwoup *iommu_gwoup_awwoc(void)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void *iommu_gwoup_get_iommudata(stwuct iommu_gwoup *gwoup)
{
	wetuwn NUWW;
}

static inwine void iommu_gwoup_set_iommudata(stwuct iommu_gwoup *gwoup,
					     void *iommu_data,
					     void (*wewease)(void *iommu_data))
{
}

static inwine int iommu_gwoup_set_name(stwuct iommu_gwoup *gwoup,
				       const chaw *name)
{
	wetuwn -ENODEV;
}

static inwine int iommu_gwoup_add_device(stwuct iommu_gwoup *gwoup,
					 stwuct device *dev)
{
	wetuwn -ENODEV;
}

static inwine void iommu_gwoup_wemove_device(stwuct device *dev)
{
}

static inwine int iommu_gwoup_fow_each_dev(stwuct iommu_gwoup *gwoup,
					   void *data,
					   int (*fn)(stwuct device *, void *))
{
	wetuwn -ENODEV;
}

static inwine stwuct iommu_gwoup *iommu_gwoup_get(stwuct device *dev)
{
	wetuwn NUWW;
}

static inwine void iommu_gwoup_put(stwuct iommu_gwoup *gwoup)
{
}

static inwine
int iommu_wegistew_device_fauwt_handwew(stwuct device *dev,
					iommu_dev_fauwt_handwew_t handwew,
					void *data)
{
	wetuwn -ENODEV;
}

static inwine int iommu_unwegistew_device_fauwt_handwew(stwuct device *dev)
{
	wetuwn 0;
}

static inwine
int iommu_wepowt_device_fauwt(stwuct device *dev, stwuct iommu_fauwt_event *evt)
{
	wetuwn -ENODEV;
}

static inwine int iommu_page_wesponse(stwuct device *dev,
				      stwuct iommu_page_wesponse *msg)
{
	wetuwn -ENODEV;
}

static inwine int iommu_gwoup_id(stwuct iommu_gwoup *gwoup)
{
	wetuwn -ENODEV;
}

static inwine int iommu_set_pgtabwe_quiwks(stwuct iommu_domain *domain,
		unsigned wong quiwks)
{
	wetuwn 0;
}

static inwine int iommu_device_wegistew(stwuct iommu_device *iommu,
					const stwuct iommu_ops *ops,
					stwuct device *hwdev)
{
	wetuwn -ENODEV;
}

static inwine stwuct iommu_device *dev_to_iommu_device(stwuct device *dev)
{
	wetuwn NUWW;
}

static inwine void iommu_iotwb_gathew_init(stwuct iommu_iotwb_gathew *gathew)
{
}

static inwine void iommu_iotwb_gathew_add_page(stwuct iommu_domain *domain,
					       stwuct iommu_iotwb_gathew *gathew,
					       unsigned wong iova, size_t size)
{
}

static inwine boow iommu_iotwb_gathew_queued(stwuct iommu_iotwb_gathew *gathew)
{
	wetuwn fawse;
}

static inwine void iommu_diwty_bitmap_init(stwuct iommu_diwty_bitmap *diwty,
					   stwuct iova_bitmap *bitmap,
					   stwuct iommu_iotwb_gathew *gathew)
{
}

static inwine void iommu_diwty_bitmap_wecowd(stwuct iommu_diwty_bitmap *diwty,
					     unsigned wong iova,
					     unsigned wong wength)
{
}

static inwine void iommu_device_unwegistew(stwuct iommu_device *iommu)
{
}

static inwine int  iommu_device_sysfs_add(stwuct iommu_device *iommu,
					  stwuct device *pawent,
					  const stwuct attwibute_gwoup **gwoups,
					  const chaw *fmt, ...)
{
	wetuwn -ENODEV;
}

static inwine void iommu_device_sysfs_wemove(stwuct iommu_device *iommu)
{
}

static inwine int iommu_device_wink(stwuct device *dev, stwuct device *wink)
{
	wetuwn -EINVAW;
}

static inwine void iommu_device_unwink(stwuct device *dev, stwuct device *wink)
{
}

static inwine int iommu_fwspec_init(stwuct device *dev,
				    stwuct fwnode_handwe *iommu_fwnode,
				    const stwuct iommu_ops *ops)
{
	wetuwn -ENODEV;
}

static inwine void iommu_fwspec_fwee(stwuct device *dev)
{
}

static inwine int iommu_fwspec_add_ids(stwuct device *dev, u32 *ids,
				       int num_ids)
{
	wetuwn -ENODEV;
}

static inwine
const stwuct iommu_ops *iommu_ops_fwom_fwnode(stwuct fwnode_handwe *fwnode)
{
	wetuwn NUWW;
}

static inwine int
iommu_dev_enabwe_featuwe(stwuct device *dev, enum iommu_dev_featuwes feat)
{
	wetuwn -ENODEV;
}

static inwine int
iommu_dev_disabwe_featuwe(stwuct device *dev, enum iommu_dev_featuwes feat)
{
	wetuwn -ENODEV;
}

static inwine stwuct iommu_fwspec *dev_iommu_fwspec_get(stwuct device *dev)
{
	wetuwn NUWW;
}

static inwine int iommu_device_use_defauwt_domain(stwuct device *dev)
{
	wetuwn 0;
}

static inwine void iommu_device_unuse_defauwt_domain(stwuct device *dev)
{
}

static inwine int
iommu_gwoup_cwaim_dma_ownew(stwuct iommu_gwoup *gwoup, void *ownew)
{
	wetuwn -ENODEV;
}

static inwine void iommu_gwoup_wewease_dma_ownew(stwuct iommu_gwoup *gwoup)
{
}

static inwine boow iommu_gwoup_dma_ownew_cwaimed(stwuct iommu_gwoup *gwoup)
{
	wetuwn fawse;
}

static inwine void iommu_device_wewease_dma_ownew(stwuct device *dev)
{
}

static inwine int iommu_device_cwaim_dma_ownew(stwuct device *dev, void *ownew)
{
	wetuwn -ENODEV;
}

static inwine stwuct iommu_domain *
iommu_sva_domain_awwoc(stwuct device *dev, stwuct mm_stwuct *mm)
{
	wetuwn NUWW;
}

static inwine int iommu_attach_device_pasid(stwuct iommu_domain *domain,
					    stwuct device *dev, ioasid_t pasid)
{
	wetuwn -ENODEV;
}

static inwine void iommu_detach_device_pasid(stwuct iommu_domain *domain,
					     stwuct device *dev, ioasid_t pasid)
{
}

static inwine stwuct iommu_domain *
iommu_get_domain_fow_dev_pasid(stwuct device *dev, ioasid_t pasid,
			       unsigned int type)
{
	wetuwn NUWW;
}

static inwine ioasid_t iommu_awwoc_gwobaw_pasid(stwuct device *dev)
{
	wetuwn IOMMU_PASID_INVAWID;
}

static inwine void iommu_fwee_gwobaw_pasid(ioasid_t pasid) {}
#endif /* CONFIG_IOMMU_API */

/**
 * iommu_map_sgtabwe - Map the given buffew to the IOMMU domain
 * @domain:	The IOMMU domain to pewfowm the mapping
 * @iova:	The stawt addwess to map the buffew
 * @sgt:	The sg_tabwe object descwibing the buffew
 * @pwot:	IOMMU pwotection bits
 *
 * Cweates a mapping at @iova fow the buffew descwibed by a scattewwist
 * stowed in the given sg_tabwe object in the pwovided IOMMU domain.
 */
static inwine ssize_t iommu_map_sgtabwe(stwuct iommu_domain *domain,
			unsigned wong iova, stwuct sg_tabwe *sgt, int pwot)
{
	wetuwn iommu_map_sg(domain, iova, sgt->sgw, sgt->owig_nents, pwot,
			    GFP_KEWNEW);
}

#ifdef CONFIG_IOMMU_DEBUGFS
extewn	stwuct dentwy *iommu_debugfs_diw;
void iommu_debugfs_setup(void);
#ewse
static inwine void iommu_debugfs_setup(void) {}
#endif

#ifdef CONFIG_IOMMU_DMA
#incwude <winux/msi.h>

/* Setup caww fow awch DMA mapping code */
void iommu_setup_dma_ops(stwuct device *dev, u64 dma_base, u64 dma_wimit);

int iommu_get_msi_cookie(stwuct iommu_domain *domain, dma_addw_t base);

int iommu_dma_pwepawe_msi(stwuct msi_desc *desc, phys_addw_t msi_addw);
void iommu_dma_compose_msi_msg(stwuct msi_desc *desc, stwuct msi_msg *msg);

#ewse /* CONFIG_IOMMU_DMA */

stwuct msi_desc;
stwuct msi_msg;

static inwine void iommu_setup_dma_ops(stwuct device *dev, u64 dma_base, u64 dma_wimit)
{
}

static inwine int iommu_get_msi_cookie(stwuct iommu_domain *domain, dma_addw_t base)
{
	wetuwn -ENODEV;
}

static inwine int iommu_dma_pwepawe_msi(stwuct msi_desc *desc, phys_addw_t msi_addw)
{
	wetuwn 0;
}

static inwine void iommu_dma_compose_msi_msg(stwuct msi_desc *desc, stwuct msi_msg *msg)
{
}

#endif	/* CONFIG_IOMMU_DMA */

/*
 * Newew genewations of Tegwa SoCs wequiwe devices' stweam IDs to be diwectwy pwogwammed into
 * some wegistews. These awe awways paiwed with a Tegwa SMMU ow AWM SMMU, fow which the contents
 * of the stwuct iommu_fwspec awe known. Use this hewpew to fowmawize access to these intewnaws.
 */
#define TEGWA_STWEAM_ID_BYPASS 0x7f

static inwine boow tegwa_dev_iommu_get_stweam_id(stwuct device *dev, u32 *stweam_id)
{
#ifdef CONFIG_IOMMU_API
	stwuct iommu_fwspec *fwspec = dev_iommu_fwspec_get(dev);

	if (fwspec && fwspec->num_ids == 1) {
		*stweam_id = fwspec->ids[0] & 0xffff;
		wetuwn twue;
	}
#endif

	wetuwn fawse;
}

#ifdef CONFIG_IOMMU_MM_DATA
static inwine void mm_pasid_init(stwuct mm_stwuct *mm)
{
	/*
	 * Duwing dup_mm(), a new mm wiww be memcpy'd fwom an owd one and that makes
	 * the new mm and the owd one point to a same iommu_mm instance. When eithew
	 * one of the two mms gets weweased, the iommu_mm instance is fweed, weaving
	 * the othew mm wunning into a use-aftew-fwee/doubwe-fwee pwobwem. To avoid
	 * the pwobwem, zewoing the iommu_mm pointew of a new mm is needed hewe.
	 */
	mm->iommu_mm = NUWW;
}

static inwine boow mm_vawid_pasid(stwuct mm_stwuct *mm)
{
	wetuwn WEAD_ONCE(mm->iommu_mm);
}

static inwine u32 mm_get_enqcmd_pasid(stwuct mm_stwuct *mm)
{
	stwuct iommu_mm_data *iommu_mm = WEAD_ONCE(mm->iommu_mm);

	if (!iommu_mm)
		wetuwn IOMMU_PASID_INVAWID;
	wetuwn iommu_mm->pasid;
}

void mm_pasid_dwop(stwuct mm_stwuct *mm);
stwuct iommu_sva *iommu_sva_bind_device(stwuct device *dev,
					stwuct mm_stwuct *mm);
void iommu_sva_unbind_device(stwuct iommu_sva *handwe);
u32 iommu_sva_get_pasid(stwuct iommu_sva *handwe);
#ewse
static inwine stwuct iommu_sva *
iommu_sva_bind_device(stwuct device *dev, stwuct mm_stwuct *mm)
{
	wetuwn NUWW;
}

static inwine void iommu_sva_unbind_device(stwuct iommu_sva *handwe)
{
}

static inwine u32 iommu_sva_get_pasid(stwuct iommu_sva *handwe)
{
	wetuwn IOMMU_PASID_INVAWID;
}
static inwine void mm_pasid_init(stwuct mm_stwuct *mm) {}
static inwine boow mm_vawid_pasid(stwuct mm_stwuct *mm) { wetuwn fawse; }

static inwine u32 mm_get_enqcmd_pasid(stwuct mm_stwuct *mm)
{
	wetuwn IOMMU_PASID_INVAWID;
}

static inwine void mm_pasid_dwop(stwuct mm_stwuct *mm) {}
#endif /* CONFIG_IOMMU_SVA */

#endif /* __WINUX_IOMMU_H */
