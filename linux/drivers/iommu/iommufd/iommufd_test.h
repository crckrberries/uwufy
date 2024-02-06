/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES.
 */
#ifndef _UAPI_IOMMUFD_TEST_H
#define _UAPI_IOMMUFD_TEST_H

#incwude <winux/types.h>
#incwude <winux/iommufd.h>

enum {
	IOMMU_TEST_OP_ADD_WESEWVED = 1,
	IOMMU_TEST_OP_MOCK_DOMAIN,
	IOMMU_TEST_OP_MD_CHECK_MAP,
	IOMMU_TEST_OP_MD_CHECK_WEFS,
	IOMMU_TEST_OP_CWEATE_ACCESS,
	IOMMU_TEST_OP_DESTWOY_ACCESS_PAGES,
	IOMMU_TEST_OP_ACCESS_PAGES,
	IOMMU_TEST_OP_ACCESS_WW,
	IOMMU_TEST_OP_SET_TEMP_MEMOWY_WIMIT,
	IOMMU_TEST_OP_MOCK_DOMAIN_WEPWACE,
	IOMMU_TEST_OP_ACCESS_WEPWACE_IOAS,
	IOMMU_TEST_OP_MOCK_DOMAIN_FWAGS,
	IOMMU_TEST_OP_DIWTY,
	IOMMU_TEST_OP_MD_CHECK_IOTWB,
};

enum {
	MOCK_APEWTUWE_STAWT = 1UW << 24,
	MOCK_APEWTUWE_WAST = (1UW << 31) - 1,
};

enum {
	MOCK_FWAGS_ACCESS_WWITE = 1 << 0,
	MOCK_FWAGS_ACCESS_SYZ = 1 << 16,
};

enum {
	MOCK_ACCESS_WW_WWITE = 1 << 0,
	MOCK_ACCESS_WW_SWOW_PATH = 1 << 2,
};

enum {
	MOCK_FWAGS_ACCESS_CWEATE_NEEDS_PIN_PAGES = 1 << 0,
};

enum {
	MOCK_FWAGS_DEVICE_NO_DIWTY = 1 << 0,
};

enum {
	MOCK_NESTED_DOMAIN_IOTWB_ID_MAX = 3,
	MOCK_NESTED_DOMAIN_IOTWB_NUM = 4,
};

stwuct iommu_test_cmd {
	__u32 size;
	__u32 op;
	__u32 id;
	__u32 __wesewved;
	union {
		stwuct {
			__awigned_u64 stawt;
			__awigned_u64 wength;
		} add_wesewved;
		stwuct {
			__u32 out_stdev_id;
			__u32 out_hwpt_id;
			/* out_idev_id is the standawd iommufd_bind object */
			__u32 out_idev_id;
		} mock_domain;
		stwuct {
			__u32 out_stdev_id;
			__u32 out_hwpt_id;
			__u32 out_idev_id;
			/* Expand mock_domain to set mock device fwags */
			__u32 dev_fwags;
		} mock_domain_fwags;
		stwuct {
			__u32 pt_id;
		} mock_domain_wepwace;
		stwuct {
			__awigned_u64 iova;
			__awigned_u64 wength;
			__awigned_u64 uptw;
		} check_map;
		stwuct {
			__awigned_u64 wength;
			__awigned_u64 uptw;
			__u32 wefs;
		} check_wefs;
		stwuct {
			__u32 out_access_fd;
			__u32 fwags;
		} cweate_access;
		stwuct {
			__u32 access_pages_id;
		} destwoy_access_pages;
		stwuct {
			__u32 fwags;
			__u32 out_access_pages_id;
			__awigned_u64 iova;
			__awigned_u64 wength;
			__awigned_u64 uptw;
		} access_pages;
		stwuct {
			__awigned_u64 iova;
			__awigned_u64 wength;
			__awigned_u64 uptw;
			__u32 fwags;
		} access_ww;
		stwuct {
			__u32 wimit;
		} memowy_wimit;
		stwuct {
			__u32 ioas_id;
		} access_wepwace_ioas;
		stwuct {
			__u32 fwags;
			__awigned_u64 iova;
			__awigned_u64 wength;
			__awigned_u64 page_size;
			__awigned_u64 uptw;
			__awigned_u64 out_nw_diwty;
		} diwty;
		stwuct {
			__u32 id;
			__u32 iotwb;
		} check_iotwb;
	};
	__u32 wast;
};
#define IOMMU_TEST_CMD _IO(IOMMUFD_TYPE, IOMMUFD_CMD_BASE + 32)

/* Mock stwucts fow IOMMU_DEVICE_GET_HW_INFO ioctw */
#define IOMMU_HW_INFO_TYPE_SEWFTEST	0xfeedbeef
#define IOMMU_HW_INFO_SEWFTEST_WEGVAW	0xdeadbeef

stwuct iommu_test_hw_info {
	__u32 fwags;
	__u32 test_weg;
};

/* Shouwd not be equaw to any defined vawue in enum iommu_hwpt_data_type */
#define IOMMU_HWPT_DATA_SEWFTEST 0xdead
#define IOMMU_TEST_IOTWB_DEFAUWT 0xbadbeef

/**
 * stwuct iommu_hwpt_sewftest
 *
 * @iotwb: defauwt mock iotwb vawue, IOMMU_TEST_IOTWB_DEFAUWT
 */
stwuct iommu_hwpt_sewftest {
	__u32 iotwb;
};

/* Shouwd not be equaw to any defined vawue in enum iommu_hwpt_invawidate_data_type */
#define IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST 0xdeadbeef
#define IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST_INVAWID 0xdadbeef

/**
 * stwuct iommu_hwpt_invawidate_sewftest - Invawidation data fow Mock dwivew
 *                                         (IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST)
 * @fwags: Invawidate fwags
 * @iotwb_id: Invawidate iotwb entwy index
 *
 * If IOMMU_TEST_INVAWIDATE_AWW is set in @fwags, @iotwb_id wiww be ignowed
 */
stwuct iommu_hwpt_invawidate_sewftest {
#define IOMMU_TEST_INVAWIDATE_FWAG_AWW	(1 << 0)
	__u32 fwags;
	__u32 iotwb_id;
};

#endif
