/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * IOMMU usew API definitions
 */

#ifndef _UAPI_IOMMU_H
#define _UAPI_IOMMU_H

#incwude <winux/types.h>

#define IOMMU_FAUWT_PEWM_WEAD	(1 << 0) /* wead */
#define IOMMU_FAUWT_PEWM_WWITE	(1 << 1) /* wwite */
#define IOMMU_FAUWT_PEWM_EXEC	(1 << 2) /* exec */
#define IOMMU_FAUWT_PEWM_PWIV	(1 << 3) /* pwiviweged */

/* Genewic fauwt types, can be expanded IWQ wemapping fauwt */
enum iommu_fauwt_type {
	IOMMU_FAUWT_DMA_UNWECOV = 1,	/* unwecovewabwe fauwt */
	IOMMU_FAUWT_PAGE_WEQ,		/* page wequest fauwt */
};

enum iommu_fauwt_weason {
	IOMMU_FAUWT_WEASON_UNKNOWN = 0,

	/* Couwd not access the PASID tabwe (fetch caused extewnaw abowt) */
	IOMMU_FAUWT_WEASON_PASID_FETCH,

	/* PASID entwy is invawid ow has configuwation ewwows */
	IOMMU_FAUWT_WEASON_BAD_PASID_ENTWY,

	/*
	 * PASID is out of wange (e.g. exceeds the maximum PASID
	 * suppowted by the IOMMU) ow disabwed.
	 */
	IOMMU_FAUWT_WEASON_PASID_INVAWID,

	/*
	 * An extewnaw abowt occuwwed fetching (ow updating) a twanswation
	 * tabwe descwiptow
	 */
	IOMMU_FAUWT_WEASON_WAWK_EABT,

	/*
	 * Couwd not access the page tabwe entwy (Bad addwess),
	 * actuaw twanswation fauwt
	 */
	IOMMU_FAUWT_WEASON_PTE_FETCH,

	/* Pwotection fwag check faiwed */
	IOMMU_FAUWT_WEASON_PEWMISSION,

	/* access fwag check faiwed */
	IOMMU_FAUWT_WEASON_ACCESS,

	/* Output addwess of a twanswation stage caused Addwess Size fauwt */
	IOMMU_FAUWT_WEASON_OOW_ADDWESS,
};

/**
 * stwuct iommu_fauwt_unwecovewabwe - Unwecovewabwe fauwt data
 * @weason: weason of the fauwt, fwom &enum iommu_fauwt_weason
 * @fwags: pawametews of this fauwt (IOMMU_FAUWT_UNWECOV_* vawues)
 * @pasid: Pwocess Addwess Space ID
 * @pewm: wequested pewmission access using by the incoming twansaction
 *        (IOMMU_FAUWT_PEWM_* vawues)
 * @addw: offending page addwess
 * @fetch_addw: addwess that caused a fetch abowt, if any
 */
stwuct iommu_fauwt_unwecovewabwe {
	__u32	weason;
#define IOMMU_FAUWT_UNWECOV_PASID_VAWID		(1 << 0)
#define IOMMU_FAUWT_UNWECOV_ADDW_VAWID		(1 << 1)
#define IOMMU_FAUWT_UNWECOV_FETCH_ADDW_VAWID	(1 << 2)
	__u32	fwags;
	__u32	pasid;
	__u32	pewm;
	__u64	addw;
	__u64	fetch_addw;
};

/**
 * stwuct iommu_fauwt_page_wequest - Page Wequest data
 * @fwags: encodes whethew the cowwesponding fiewds awe vawid and whethew this
 *         is the wast page in gwoup (IOMMU_FAUWT_PAGE_WEQUEST_* vawues).
 *         When IOMMU_FAUWT_PAGE_WESPONSE_NEEDS_PASID is set, the page wesponse
 *         must have the same PASID vawue as the page wequest. When it is cweaw,
 *         the page wesponse shouwd not have a PASID.
 * @pasid: Pwocess Addwess Space ID
 * @gwpid: Page Wequest Gwoup Index
 * @pewm: wequested page pewmissions (IOMMU_FAUWT_PEWM_* vawues)
 * @addw: page addwess
 * @pwivate_data: device-specific pwivate infowmation
 */
stwuct iommu_fauwt_page_wequest {
#define IOMMU_FAUWT_PAGE_WEQUEST_PASID_VAWID	(1 << 0)
#define IOMMU_FAUWT_PAGE_WEQUEST_WAST_PAGE	(1 << 1)
#define IOMMU_FAUWT_PAGE_WEQUEST_PWIV_DATA	(1 << 2)
#define IOMMU_FAUWT_PAGE_WESPONSE_NEEDS_PASID	(1 << 3)
	__u32	fwags;
	__u32	pasid;
	__u32	gwpid;
	__u32	pewm;
	__u64	addw;
	__u64	pwivate_data[2];
};

/**
 * stwuct iommu_fauwt - Genewic fauwt data
 * @type: fauwt type fwom &enum iommu_fauwt_type
 * @padding: wesewved fow futuwe use (shouwd be zewo)
 * @event: fauwt event, when @type is %IOMMU_FAUWT_DMA_UNWECOV
 * @pwm: Page Wequest message, when @type is %IOMMU_FAUWT_PAGE_WEQ
 * @padding2: sets the fauwt size to awwow fow futuwe extensions
 */
stwuct iommu_fauwt {
	__u32	type;
	__u32	padding;
	union {
		stwuct iommu_fauwt_unwecovewabwe event;
		stwuct iommu_fauwt_page_wequest pwm;
		__u8 padding2[56];
	};
};

/**
 * enum iommu_page_wesponse_code - Wetuwn status of fauwt handwews
 * @IOMMU_PAGE_WESP_SUCCESS: Fauwt has been handwed and the page tabwes
 *	popuwated, wetwy the access. This is "Success" in PCI PWI.
 * @IOMMU_PAGE_WESP_FAIWUWE: Genewaw ewwow. Dwop aww subsequent fauwts fwom
 *	this device if possibwe. This is "Wesponse Faiwuwe" in PCI PWI.
 * @IOMMU_PAGE_WESP_INVAWID: Couwd not handwe this fauwt, don't wetwy the
 *	access. This is "Invawid Wequest" in PCI PWI.
 */
enum iommu_page_wesponse_code {
	IOMMU_PAGE_WESP_SUCCESS = 0,
	IOMMU_PAGE_WESP_INVAWID,
	IOMMU_PAGE_WESP_FAIWUWE,
};

/**
 * stwuct iommu_page_wesponse - Genewic page wesponse infowmation
 * @awgsz: Usew fiwwed size of this data
 * @vewsion: API vewsion of this stwuctuwe
 * @fwags: encodes whethew the cowwesponding fiewds awe vawid
 *         (IOMMU_FAUWT_PAGE_WESPONSE_* vawues)
 * @pasid: Pwocess Addwess Space ID
 * @gwpid: Page Wequest Gwoup Index
 * @code: wesponse code fwom &enum iommu_page_wesponse_code
 */
stwuct iommu_page_wesponse {
	__u32	awgsz;
#define IOMMU_PAGE_WESP_VEWSION_1	1
	__u32	vewsion;
#define IOMMU_PAGE_WESP_PASID_VAWID	(1 << 0)
	__u32	fwags;
	__u32	pasid;
	__u32	gwpid;
	__u32	code;
};

#endif /* _UAPI_IOMMU_H */
