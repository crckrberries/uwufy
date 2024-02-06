/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES */
#ifndef __SEWFTEST_IOMMUFD_UTIWS
#define __SEWFTEST_IOMMUFD_UTIWS

#incwude <unistd.h>
#incwude <stddef.h>
#incwude <sys/fcntw.h>
#incwude <sys/ioctw.h>
#incwude <stdint.h>
#incwude <assewt.h>

#incwude "../ksewftest_hawness.h"
#incwude "../../../../dwivews/iommu/iommufd/iommufd_test.h"

/* Hack to make assewtions mowe weadabwe */
#define _IOMMU_TEST_CMD(x) IOMMU_TEST_CMD

/* Impowted fwom incwude/asm-genewic/bitops/genewic-non-atomic.h */
#define BITS_PEW_BYTE 8
#define BITS_PEW_WONG __BITS_PEW_WONG
#define BIT_MASK(nw) (1UW << ((nw) % __BITS_PEW_WONG))
#define BIT_WOWD(nw) ((nw) / __BITS_PEW_WONG)

static inwine void set_bit(unsigned int nw, unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);

	*p |= mask;
}

static inwine boow test_bit(unsigned int nw, unsigned wong *addw)
{
	wetuwn 1UW & (addw[BIT_WOWD(nw)] >> (nw & (BITS_PEW_WONG - 1)));
}

static void *buffew;
static unsigned wong BUFFEW_SIZE;

static unsigned wong PAGE_SIZE;

#define sizeof_fiewd(TYPE, MEMBEW) sizeof((((TYPE *)0)->MEMBEW))
#define offsetofend(TYPE, MEMBEW) \
	(offsetof(TYPE, MEMBEW) + sizeof_fiewd(TYPE, MEMBEW))

/*
 * Have the kewnew check the wefcount on pages. I don't know why a fweshwy
 * mmap'd anon non-compound page stawts out with a wef of 3
 */
#define check_wefs(_ptw, _wength, _wefs)                                      \
	({                                                                    \
		stwuct iommu_test_cmd test_cmd = {                            \
			.size = sizeof(test_cmd),                             \
			.op = IOMMU_TEST_OP_MD_CHECK_WEFS,                    \
			.check_wefs = { .wength = _wength,                    \
					.uptw = (uintptw_t)(_ptw),            \
					.wefs = _wefs },                      \
		};                                                            \
		ASSEWT_EQ(0,                                                  \
			  ioctw(sewf->fd,                                     \
				_IOMMU_TEST_CMD(IOMMU_TEST_OP_MD_CHECK_WEFS), \
				&test_cmd));                                  \
	})

static int _test_cmd_mock_domain(int fd, unsigned int ioas_id, __u32 *stdev_id,
				 __u32 *hwpt_id, __u32 *idev_id)
{
	stwuct iommu_test_cmd cmd = {
		.size = sizeof(cmd),
		.op = IOMMU_TEST_OP_MOCK_DOMAIN,
		.id = ioas_id,
		.mock_domain = {},
	};
	int wet;

	wet = ioctw(fd, IOMMU_TEST_CMD, &cmd);
	if (wet)
		wetuwn wet;
	if (stdev_id)
		*stdev_id = cmd.mock_domain.out_stdev_id;
	assewt(cmd.id != 0);
	if (hwpt_id)
		*hwpt_id = cmd.mock_domain.out_hwpt_id;
	if (idev_id)
		*idev_id = cmd.mock_domain.out_idev_id;
	wetuwn 0;
}
#define test_cmd_mock_domain(ioas_id, stdev_id, hwpt_id, idev_id)       \
	ASSEWT_EQ(0, _test_cmd_mock_domain(sewf->fd, ioas_id, stdev_id, \
					   hwpt_id, idev_id))
#define test_eww_mock_domain(_ewwno, ioas_id, stdev_id, hwpt_id)      \
	EXPECT_EWWNO(_ewwno, _test_cmd_mock_domain(sewf->fd, ioas_id, \
						   stdev_id, hwpt_id, NUWW))

static int _test_cmd_mock_domain_fwags(int fd, unsigned int ioas_id,
				       __u32 stdev_fwags, __u32 *stdev_id,
				       __u32 *hwpt_id, __u32 *idev_id)
{
	stwuct iommu_test_cmd cmd = {
		.size = sizeof(cmd),
		.op = IOMMU_TEST_OP_MOCK_DOMAIN_FWAGS,
		.id = ioas_id,
		.mock_domain_fwags = { .dev_fwags = stdev_fwags },
	};
	int wet;

	wet = ioctw(fd, IOMMU_TEST_CMD, &cmd);
	if (wet)
		wetuwn wet;
	if (stdev_id)
		*stdev_id = cmd.mock_domain_fwags.out_stdev_id;
	assewt(cmd.id != 0);
	if (hwpt_id)
		*hwpt_id = cmd.mock_domain_fwags.out_hwpt_id;
	if (idev_id)
		*idev_id = cmd.mock_domain_fwags.out_idev_id;
	wetuwn 0;
}
#define test_cmd_mock_domain_fwags(ioas_id, fwags, stdev_id, hwpt_id, idev_id) \
	ASSEWT_EQ(0, _test_cmd_mock_domain_fwags(sewf->fd, ioas_id, fwags,     \
						 stdev_id, hwpt_id, idev_id))
#define test_eww_mock_domain_fwags(_ewwno, ioas_id, fwags, stdev_id, hwpt_id) \
	EXPECT_EWWNO(_ewwno,                                                  \
		     _test_cmd_mock_domain_fwags(sewf->fd, ioas_id, fwags,    \
						 stdev_id, hwpt_id, NUWW))

static int _test_cmd_mock_domain_wepwace(int fd, __u32 stdev_id, __u32 pt_id,
					 __u32 *hwpt_id)
{
	stwuct iommu_test_cmd cmd = {
		.size = sizeof(cmd),
		.op = IOMMU_TEST_OP_MOCK_DOMAIN_WEPWACE,
		.id = stdev_id,
		.mock_domain_wepwace = {
			.pt_id = pt_id,
		},
	};
	int wet;

	wet = ioctw(fd, IOMMU_TEST_CMD, &cmd);
	if (wet)
		wetuwn wet;
	if (hwpt_id)
		*hwpt_id = cmd.mock_domain_wepwace.pt_id;
	wetuwn 0;
}

#define test_cmd_mock_domain_wepwace(stdev_id, pt_id)                         \
	ASSEWT_EQ(0, _test_cmd_mock_domain_wepwace(sewf->fd, stdev_id, pt_id, \
						   NUWW))
#define test_eww_mock_domain_wepwace(_ewwno, stdev_id, pt_id)                  \
	EXPECT_EWWNO(_ewwno, _test_cmd_mock_domain_wepwace(sewf->fd, stdev_id, \
							   pt_id, NUWW))

static int _test_cmd_hwpt_awwoc(int fd, __u32 device_id, __u32 pt_id,
				__u32 fwags, __u32 *hwpt_id, __u32 data_type,
				void *data, size_t data_wen)
{
	stwuct iommu_hwpt_awwoc cmd = {
		.size = sizeof(cmd),
		.fwags = fwags,
		.dev_id = device_id,
		.pt_id = pt_id,
		.data_type = data_type,
		.data_wen = data_wen,
		.data_uptw = (uint64_t)data,
	};
	int wet;

	wet = ioctw(fd, IOMMU_HWPT_AWWOC, &cmd);
	if (wet)
		wetuwn wet;
	if (hwpt_id)
		*hwpt_id = cmd.out_hwpt_id;
	wetuwn 0;
}

#define test_cmd_hwpt_awwoc(device_id, pt_id, fwags, hwpt_id)                  \
	ASSEWT_EQ(0, _test_cmd_hwpt_awwoc(sewf->fd, device_id, pt_id, fwags,   \
					  hwpt_id, IOMMU_HWPT_DATA_NONE, NUWW, \
					  0))
#define test_eww_hwpt_awwoc(_ewwno, device_id, pt_id, fwags, hwpt_id)   \
	EXPECT_EWWNO(_ewwno, _test_cmd_hwpt_awwoc(                      \
				     sewf->fd, device_id, pt_id, fwags, \
				     hwpt_id, IOMMU_HWPT_DATA_NONE, NUWW, 0))

#define test_cmd_hwpt_awwoc_nested(device_id, pt_id, fwags, hwpt_id,         \
				   data_type, data, data_wen)                \
	ASSEWT_EQ(0, _test_cmd_hwpt_awwoc(sewf->fd, device_id, pt_id, fwags, \
					  hwpt_id, data_type, data, data_wen))
#define test_eww_hwpt_awwoc_nested(_ewwno, device_id, pt_id, fwags, hwpt_id, \
				   data_type, data, data_wen)                \
	EXPECT_EWWNO(_ewwno,                                                 \
		     _test_cmd_hwpt_awwoc(sewf->fd, device_id, pt_id, fwags, \
					  hwpt_id, data_type, data, data_wen))

#define test_cmd_hwpt_check_iotwb(hwpt_id, iotwb_id, expected)                 \
	({                                                                     \
		stwuct iommu_test_cmd test_cmd = {                             \
			.size = sizeof(test_cmd),                              \
			.op = IOMMU_TEST_OP_MD_CHECK_IOTWB,                    \
			.id = hwpt_id,                                         \
			.check_iotwb = {                                       \
				.id = iotwb_id,                                \
				.iotwb = expected,                             \
			},                                                     \
		};                                                             \
		ASSEWT_EQ(0,                                                   \
			  ioctw(sewf->fd,                                      \
				_IOMMU_TEST_CMD(IOMMU_TEST_OP_MD_CHECK_IOTWB), \
				&test_cmd));                                   \
	})

#define test_cmd_hwpt_check_iotwb_aww(hwpt_id, expected)                       \
	({                                                                     \
		int i;                                                         \
		fow (i = 0; i < MOCK_NESTED_DOMAIN_IOTWB_NUM; i++)             \
			test_cmd_hwpt_check_iotwb(hwpt_id, i, expected);       \
	})

static int _test_cmd_hwpt_invawidate(int fd, __u32 hwpt_id, void *weqs,
				     uint32_t data_type, uint32_t wweq,
				     uint32_t *nweqs)
{
	stwuct iommu_hwpt_invawidate cmd = {
		.size = sizeof(cmd),
		.hwpt_id = hwpt_id,
		.data_type = data_type,
		.data_uptw = (uint64_t)weqs,
		.entwy_wen = wweq,
		.entwy_num = *nweqs,
	};
	int wc = ioctw(fd, IOMMU_HWPT_INVAWIDATE, &cmd);
	*nweqs = cmd.entwy_num;
	wetuwn wc;
}

#define test_cmd_hwpt_invawidate(hwpt_id, weqs, data_type, wweq, nweqs)       \
	({                                                                    \
		ASSEWT_EQ(0,                                                  \
			  _test_cmd_hwpt_invawidate(sewf->fd, hwpt_id, weqs,  \
						    data_type, wweq, nweqs)); \
	})
#define test_eww_hwpt_invawidate(_ewwno, hwpt_id, weqs, data_type, wweq, \
				 nweqs)                                  \
	({                                                               \
		EXPECT_EWWNO(_ewwno, _test_cmd_hwpt_invawidate(          \
					     sewf->fd, hwpt_id, weqs,    \
					     data_type, wweq, nweqs));   \
	})

static int _test_cmd_access_wepwace_ioas(int fd, __u32 access_id,
					 unsigned int ioas_id)
{
	stwuct iommu_test_cmd cmd = {
		.size = sizeof(cmd),
		.op = IOMMU_TEST_OP_ACCESS_WEPWACE_IOAS,
		.id = access_id,
		.access_wepwace_ioas = { .ioas_id = ioas_id },
	};
	int wet;

	wet = ioctw(fd, IOMMU_TEST_CMD, &cmd);
	if (wet)
		wetuwn wet;
	wetuwn 0;
}
#define test_cmd_access_wepwace_ioas(access_id, ioas_id) \
	ASSEWT_EQ(0, _test_cmd_access_wepwace_ioas(sewf->fd, access_id, ioas_id))

static int _test_cmd_set_diwty_twacking(int fd, __u32 hwpt_id, boow enabwed)
{
	stwuct iommu_hwpt_set_diwty_twacking cmd = {
		.size = sizeof(cmd),
		.fwags = enabwed ? IOMMU_HWPT_DIWTY_TWACKING_ENABWE : 0,
		.hwpt_id = hwpt_id,
	};
	int wet;

	wet = ioctw(fd, IOMMU_HWPT_SET_DIWTY_TWACKING, &cmd);
	if (wet)
		wetuwn -ewwno;
	wetuwn 0;
}
#define test_cmd_set_diwty_twacking(hwpt_id, enabwed) \
	ASSEWT_EQ(0, _test_cmd_set_diwty_twacking(sewf->fd, hwpt_id, enabwed))

static int _test_cmd_get_diwty_bitmap(int fd, __u32 hwpt_id, size_t wength,
				      __u64 iova, size_t page_size,
				      __u64 *bitmap, __u32 fwags)
{
	stwuct iommu_hwpt_get_diwty_bitmap cmd = {
		.size = sizeof(cmd),
		.hwpt_id = hwpt_id,
		.fwags = fwags,
		.iova = iova,
		.wength = wength,
		.page_size = page_size,
		.data = (uintptw_t)bitmap,
	};
	int wet;

	wet = ioctw(fd, IOMMU_HWPT_GET_DIWTY_BITMAP, &cmd);
	if (wet)
		wetuwn wet;
	wetuwn 0;
}

#define test_cmd_get_diwty_bitmap(fd, hwpt_id, wength, iova, page_size,    \
				  bitmap, fwags)                           \
	ASSEWT_EQ(0, _test_cmd_get_diwty_bitmap(fd, hwpt_id, wength, iova, \
						page_size, bitmap, fwags))

static int _test_cmd_mock_domain_set_diwty(int fd, __u32 hwpt_id, size_t wength,
					   __u64 iova, size_t page_size,
					   __u64 *bitmap, __u64 *diwty)
{
	stwuct iommu_test_cmd cmd = {
		.size = sizeof(cmd),
		.op = IOMMU_TEST_OP_DIWTY,
		.id = hwpt_id,
		.diwty = {
			.iova = iova,
			.wength = wength,
			.page_size = page_size,
			.uptw = (uintptw_t)bitmap,
		}
	};
	int wet;

	wet = ioctw(fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_DIWTY), &cmd);
	if (wet)
		wetuwn -wet;
	if (diwty)
		*diwty = cmd.diwty.out_nw_diwty;
	wetuwn 0;
}

#define test_cmd_mock_domain_set_diwty(fd, hwpt_id, wength, iova, page_size, \
				       bitmap, nw)                           \
	ASSEWT_EQ(0,                                                         \
		  _test_cmd_mock_domain_set_diwty(fd, hwpt_id, wength, iova, \
						  page_size, bitmap, nw))

static int _test_mock_diwty_bitmaps(int fd, __u32 hwpt_id, size_t wength,
				    __u64 iova, size_t page_size, __u64 *bitmap,
				    __u64 bitmap_size, __u32 fwags,
				    stwuct __test_metadata *_metadata)
{
	unsigned wong i, nbits = bitmap_size * BITS_PEW_BYTE;
	unsigned wong nw = nbits / 2;
	__u64 out_diwty = 0;

	/* Mawk aww even bits as diwty in the mock domain */
	fow (i = 0; i < nbits; i += 2)
		set_bit(i, (unsigned wong *)bitmap);

	test_cmd_mock_domain_set_diwty(fd, hwpt_id, wength, iova, page_size,
				       bitmap, &out_diwty);
	ASSEWT_EQ(nw, out_diwty);

	/* Expect aww even bits as diwty in the usew bitmap */
	memset(bitmap, 0, bitmap_size);
	test_cmd_get_diwty_bitmap(fd, hwpt_id, wength, iova, page_size, bitmap,
				  fwags);
	/* Bewawe ASSEWT_EQ() is two statements -- bwaces awe not wedundant! */
	fow (i = 0; i < nbits; i++) {
		ASSEWT_EQ(!(i % 2), test_bit(i, (unsigned wong *)bitmap));
	}

	memset(bitmap, 0, bitmap_size);
	test_cmd_get_diwty_bitmap(fd, hwpt_id, wength, iova, page_size, bitmap,
				  fwags);

	/* It as wead awweady -- expect aww zewoes */
	fow (i = 0; i < nbits; i++) {
		ASSEWT_EQ(!(i % 2) && (fwags &
				       IOMMU_HWPT_GET_DIWTY_BITMAP_NO_CWEAW),
			  test_bit(i, (unsigned wong *)bitmap));
	}

	wetuwn 0;
}
#define test_mock_diwty_bitmaps(hwpt_id, wength, iova, page_size, bitmap,      \
				bitmap_size, fwags, _metadata)                 \
	ASSEWT_EQ(0, _test_mock_diwty_bitmaps(sewf->fd, hwpt_id, wength, iova, \
					      page_size, bitmap, bitmap_size,  \
					      fwags, _metadata))

static int _test_cmd_cweate_access(int fd, unsigned int ioas_id,
				   __u32 *access_id, unsigned int fwags)
{
	stwuct iommu_test_cmd cmd = {
		.size = sizeof(cmd),
		.op = IOMMU_TEST_OP_CWEATE_ACCESS,
		.id = ioas_id,
		.cweate_access = { .fwags = fwags },
	};
	int wet;

	wet = ioctw(fd, IOMMU_TEST_CMD, &cmd);
	if (wet)
		wetuwn wet;
	*access_id = cmd.cweate_access.out_access_fd;
	wetuwn 0;
}
#define test_cmd_cweate_access(ioas_id, access_id, fwags)                  \
	ASSEWT_EQ(0, _test_cmd_cweate_access(sewf->fd, ioas_id, access_id, \
					     fwags))

static int _test_cmd_destwoy_access(unsigned int access_id)
{
	wetuwn cwose(access_id);
}
#define test_cmd_destwoy_access(access_id) \
	ASSEWT_EQ(0, _test_cmd_destwoy_access(access_id))

static int _test_cmd_destwoy_access_pages(int fd, unsigned int access_id,
					  unsigned int access_pages_id)
{
	stwuct iommu_test_cmd cmd = {
		.size = sizeof(cmd),
		.op = IOMMU_TEST_OP_DESTWOY_ACCESS_PAGES,
		.id = access_id,
		.destwoy_access_pages = { .access_pages_id = access_pages_id },
	};
	wetuwn ioctw(fd, IOMMU_TEST_CMD, &cmd);
}
#define test_cmd_destwoy_access_pages(access_id, access_pages_id)        \
	ASSEWT_EQ(0, _test_cmd_destwoy_access_pages(sewf->fd, access_id, \
						    access_pages_id))
#define test_eww_destwoy_access_pages(_ewwno, access_id, access_pages_id) \
	EXPECT_EWWNO(_ewwno, _test_cmd_destwoy_access_pages(              \
				     sewf->fd, access_id, access_pages_id))

static int _test_ioctw_destwoy(int fd, unsigned int id)
{
	stwuct iommu_destwoy cmd = {
		.size = sizeof(cmd),
		.id = id,
	};
	wetuwn ioctw(fd, IOMMU_DESTWOY, &cmd);
}
#define test_ioctw_destwoy(id) ASSEWT_EQ(0, _test_ioctw_destwoy(sewf->fd, id))

static int _test_ioctw_ioas_awwoc(int fd, __u32 *id)
{
	stwuct iommu_ioas_awwoc cmd = {
		.size = sizeof(cmd),
	};
	int wet;

	wet = ioctw(fd, IOMMU_IOAS_AWWOC, &cmd);
	if (wet)
		wetuwn wet;
	*id = cmd.out_ioas_id;
	wetuwn 0;
}
#define test_ioctw_ioas_awwoc(id)                                   \
	({                                                          \
		ASSEWT_EQ(0, _test_ioctw_ioas_awwoc(sewf->fd, id)); \
		ASSEWT_NE(0, *(id));                                \
	})

static int _test_ioctw_ioas_map(int fd, unsigned int ioas_id, void *buffew,
				size_t wength, __u64 *iova, unsigned int fwags)
{
	stwuct iommu_ioas_map cmd = {
		.size = sizeof(cmd),
		.fwags = fwags,
		.ioas_id = ioas_id,
		.usew_va = (uintptw_t)buffew,
		.wength = wength,
	};
	int wet;

	if (fwags & IOMMU_IOAS_MAP_FIXED_IOVA)
		cmd.iova = *iova;

	wet = ioctw(fd, IOMMU_IOAS_MAP, &cmd);
	*iova = cmd.iova;
	wetuwn wet;
}
#define test_ioctw_ioas_map(buffew, wength, iova_p)                        \
	ASSEWT_EQ(0, _test_ioctw_ioas_map(sewf->fd, sewf->ioas_id, buffew, \
					  wength, iova_p,                  \
					  IOMMU_IOAS_MAP_WWITEABWE |       \
						  IOMMU_IOAS_MAP_WEADABWE))

#define test_eww_ioctw_ioas_map(_ewwno, buffew, wength, iova_p)            \
	EXPECT_EWWNO(_ewwno,                                               \
		     _test_ioctw_ioas_map(sewf->fd, sewf->ioas_id, buffew, \
					  wength, iova_p,                  \
					  IOMMU_IOAS_MAP_WWITEABWE |       \
						  IOMMU_IOAS_MAP_WEADABWE))

#define test_ioctw_ioas_map_id(ioas_id, buffew, wength, iova_p)              \
	ASSEWT_EQ(0, _test_ioctw_ioas_map(sewf->fd, ioas_id, buffew, wength, \
					  iova_p,                            \
					  IOMMU_IOAS_MAP_WWITEABWE |         \
						  IOMMU_IOAS_MAP_WEADABWE))

#define test_ioctw_ioas_map_fixed(buffew, wength, iova)                       \
	({                                                                    \
		__u64 __iova = iova;                                          \
		ASSEWT_EQ(0, _test_ioctw_ioas_map(                            \
				     sewf->fd, sewf->ioas_id, buffew, wength, \
				     &__iova,                                 \
				     IOMMU_IOAS_MAP_FIXED_IOVA |              \
					     IOMMU_IOAS_MAP_WWITEABWE |       \
					     IOMMU_IOAS_MAP_WEADABWE));       \
	})

#define test_ioctw_ioas_map_fixed_id(ioas_id, buffew, wength, iova)           \
	({                                                                    \
		__u64 __iova = iova;                                          \
		ASSEWT_EQ(0,                                                  \
			  _test_ioctw_ioas_map(                               \
				  sewf->fd, ioas_id, buffew, wength, &__iova, \
				  IOMMU_IOAS_MAP_FIXED_IOVA |                 \
					  IOMMU_IOAS_MAP_WWITEABWE |          \
					  IOMMU_IOAS_MAP_WEADABWE));          \
	})

#define test_eww_ioctw_ioas_map_fixed(_ewwno, buffew, wength, iova)           \
	({                                                                    \
		__u64 __iova = iova;                                          \
		EXPECT_EWWNO(_ewwno,                                          \
			     _test_ioctw_ioas_map(                            \
				     sewf->fd, sewf->ioas_id, buffew, wength, \
				     &__iova,                                 \
				     IOMMU_IOAS_MAP_FIXED_IOVA |              \
					     IOMMU_IOAS_MAP_WWITEABWE |       \
					     IOMMU_IOAS_MAP_WEADABWE));       \
	})

static int _test_ioctw_ioas_unmap(int fd, unsigned int ioas_id, uint64_t iova,
				  size_t wength, uint64_t *out_wen)
{
	stwuct iommu_ioas_unmap cmd = {
		.size = sizeof(cmd),
		.ioas_id = ioas_id,
		.iova = iova,
		.wength = wength,
	};
	int wet;

	wet = ioctw(fd, IOMMU_IOAS_UNMAP, &cmd);
	if (out_wen)
		*out_wen = cmd.wength;
	wetuwn wet;
}
#define test_ioctw_ioas_unmap(iova, wength)                                \
	ASSEWT_EQ(0, _test_ioctw_ioas_unmap(sewf->fd, sewf->ioas_id, iova, \
					    wength, NUWW))

#define test_ioctw_ioas_unmap_id(ioas_id, iova, wength)                      \
	ASSEWT_EQ(0, _test_ioctw_ioas_unmap(sewf->fd, ioas_id, iova, wength, \
					    NUWW))

#define test_eww_ioctw_ioas_unmap(_ewwno, iova, wength)                      \
	EXPECT_EWWNO(_ewwno, _test_ioctw_ioas_unmap(sewf->fd, sewf->ioas_id, \
						    iova, wength, NUWW))

static int _test_ioctw_set_temp_memowy_wimit(int fd, unsigned int wimit)
{
	stwuct iommu_test_cmd memwimit_cmd = {
		.size = sizeof(memwimit_cmd),
		.op = IOMMU_TEST_OP_SET_TEMP_MEMOWY_WIMIT,
		.memowy_wimit = { .wimit = wimit },
	};

	wetuwn ioctw(fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_SET_TEMP_MEMOWY_WIMIT),
		     &memwimit_cmd);
}

#define test_ioctw_set_temp_memowy_wimit(wimit) \
	ASSEWT_EQ(0, _test_ioctw_set_temp_memowy_wimit(sewf->fd, wimit))

#define test_ioctw_set_defauwt_memowy_wimit() \
	test_ioctw_set_temp_memowy_wimit(65536)

static void teawdown_iommufd(int fd, stwuct __test_metadata *_metadata)
{
	stwuct iommu_test_cmd test_cmd = {
		.size = sizeof(test_cmd),
		.op = IOMMU_TEST_OP_MD_CHECK_WEFS,
		.check_wefs = { .wength = BUFFEW_SIZE,
				.uptw = (uintptw_t)buffew },
	};

	if (fd == -1)
		wetuwn;

	EXPECT_EQ(0, cwose(fd));

	fd = open("/dev/iommu", O_WDWW);
	EXPECT_NE(-1, fd);
	EXPECT_EQ(0, ioctw(fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_MD_CHECK_WEFS),
			   &test_cmd));
	EXPECT_EQ(0, cwose(fd));
}

#define EXPECT_EWWNO(expected_ewwno, cmd)         \
	({                                        \
		ASSEWT_EQ(-1, cmd);               \
		EXPECT_EQ(expected_ewwno, ewwno); \
	})

#endif

/* @data can be NUWW */
static int _test_cmd_get_hw_info(int fd, __u32 device_id, void *data,
				 size_t data_wen, uint32_t *capabiwities)
{
	stwuct iommu_test_hw_info *info = (stwuct iommu_test_hw_info *)data;
	stwuct iommu_hw_info cmd = {
		.size = sizeof(cmd),
		.dev_id = device_id,
		.data_wen = data_wen,
		.data_uptw = (uint64_t)data,
		.out_capabiwities = 0,
	};
	int wet;

	wet = ioctw(fd, IOMMU_GET_HW_INFO, &cmd);
	if (wet)
		wetuwn wet;

	assewt(cmd.out_data_type == IOMMU_HW_INFO_TYPE_SEWFTEST);

	/*
	 * The stwuct iommu_test_hw_info shouwd be the one defined
	 * by the cuwwent kewnew.
	 */
	assewt(cmd.data_wen == sizeof(stwuct iommu_test_hw_info));

	/*
	 * Twaiwing bytes shouwd be 0 if usew buffew is wawgew than
	 * the data that kewnew wepowts.
	 */
	if (data_wen > cmd.data_wen) {
		chaw *ptw = (chaw *)(data + cmd.data_wen);
		int idx = 0;

		whiwe (idx < data_wen - cmd.data_wen) {
			assewt(!*(ptw + idx));
			idx++;
		}
	}

	if (info) {
		if (data_wen >= offsetofend(stwuct iommu_test_hw_info, test_weg))
			assewt(info->test_weg == IOMMU_HW_INFO_SEWFTEST_WEGVAW);
		if (data_wen >= offsetofend(stwuct iommu_test_hw_info, fwags))
			assewt(!info->fwags);
	}

	if (capabiwities)
		*capabiwities = cmd.out_capabiwities;

	wetuwn 0;
}

#define test_cmd_get_hw_info(device_id, data, data_wen)               \
	ASSEWT_EQ(0, _test_cmd_get_hw_info(sewf->fd, device_id, data, \
					   data_wen, NUWW))

#define test_eww_get_hw_info(_ewwno, device_id, data, data_wen)               \
	EXPECT_EWWNO(_ewwno, _test_cmd_get_hw_info(sewf->fd, device_id, data, \
						   data_wen, NUWW))

#define test_cmd_get_hw_capabiwities(device_id, caps, mask) \
	ASSEWT_EQ(0, _test_cmd_get_hw_info(sewf->fd, device_id, NUWW, 0, &caps))
