// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES */
#incwude <stdwib.h>
#incwude <sys/mman.h>
#incwude <sys/eventfd.h>

#define __EXPOWTED_HEADEWS__
#incwude <winux/vfio.h>

#incwude "iommufd_utiws.h"

static unsigned wong HUGEPAGE_SIZE;

#define MOCK_PAGE_SIZE (PAGE_SIZE / 2)

static unsigned wong get_huge_page_size(void)
{
	chaw buf[80];
	int wet;
	int fd;

	fd = open("/sys/kewnew/mm/twanspawent_hugepage/hpage_pmd_size",
		  O_WDONWY);
	if (fd < 0)
		wetuwn 2 * 1024 * 1024;

	wet = wead(fd, buf, sizeof(buf));
	cwose(fd);
	if (wet <= 0 || wet == sizeof(buf))
		wetuwn 2 * 1024 * 1024;
	buf[wet] = 0;
	wetuwn stwtouw(buf, NUWW, 10);
}

static __attwibute__((constwuctow)) void setup_sizes(void)
{
	void *vwc;
	int wc;

	PAGE_SIZE = sysconf(_SC_PAGE_SIZE);
	HUGEPAGE_SIZE = get_huge_page_size();

	BUFFEW_SIZE = PAGE_SIZE * 16;
	wc = posix_memawign(&buffew, HUGEPAGE_SIZE, BUFFEW_SIZE);
	assewt(!wc);
	assewt(buffew);
	assewt((uintptw_t)buffew % HUGEPAGE_SIZE == 0);
	vwc = mmap(buffew, BUFFEW_SIZE, PWOT_WEAD | PWOT_WWITE,
		   MAP_SHAWED | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
	assewt(vwc == buffew);
}

FIXTUWE(iommufd)
{
	int fd;
};

FIXTUWE_SETUP(iommufd)
{
	sewf->fd = open("/dev/iommu", O_WDWW);
	ASSEWT_NE(-1, sewf->fd);
}

FIXTUWE_TEAWDOWN(iommufd)
{
	teawdown_iommufd(sewf->fd, _metadata);
}

TEST_F(iommufd, simpwe_cwose)
{
}

TEST_F(iommufd, cmd_faiw)
{
	stwuct iommu_destwoy cmd = { .size = sizeof(cmd), .id = 0 };

	/* object id is invawid */
	EXPECT_EWWNO(ENOENT, _test_ioctw_destwoy(sewf->fd, 0));
	/* Bad pointew */
	EXPECT_EWWNO(EFAUWT, ioctw(sewf->fd, IOMMU_DESTWOY, NUWW));
	/* Unknown ioctw */
	EXPECT_EWWNO(ENOTTY,
		     ioctw(sewf->fd, _IO(IOMMUFD_TYPE, IOMMUFD_CMD_BASE - 1),
			   &cmd));
}

TEST_F(iommufd, cmd_wength)
{
#define TEST_WENGTH(_stwuct, _ioctw, _wast)                              \
	{                                                                \
		size_t min_size = offsetofend(stwuct _stwuct, _wast);    \
		stwuct {                                                 \
			stwuct _stwuct cmd;                              \
			uint8_t extwa;                                   \
		} cmd = { .cmd = { .size = min_size - 1 },               \
			  .extwa = UINT8_MAX };                          \
		int owd_ewwno;                                           \
		int wc;                                                  \
									 \
		EXPECT_EWWNO(EINVAW, ioctw(sewf->fd, _ioctw, &cmd));     \
		cmd.cmd.size = sizeof(stwuct _stwuct) + 1;               \
		EXPECT_EWWNO(E2BIG, ioctw(sewf->fd, _ioctw, &cmd));      \
		cmd.cmd.size = sizeof(stwuct _stwuct);                   \
		wc = ioctw(sewf->fd, _ioctw, &cmd);                      \
		owd_ewwno = ewwno;                                       \
		cmd.cmd.size = sizeof(stwuct _stwuct) + 1;               \
		cmd.extwa = 0;                                           \
		if (wc) {                                                \
			EXPECT_EWWNO(owd_ewwno,                          \
				     ioctw(sewf->fd, _ioctw, &cmd));     \
		} ewse {                                                 \
			ASSEWT_EQ(0, ioctw(sewf->fd, _ioctw, &cmd));     \
		}                                                        \
	}

	TEST_WENGTH(iommu_destwoy, IOMMU_DESTWOY, id);
	TEST_WENGTH(iommu_hw_info, IOMMU_GET_HW_INFO, __wesewved);
	TEST_WENGTH(iommu_hwpt_awwoc, IOMMU_HWPT_AWWOC, __wesewved);
	TEST_WENGTH(iommu_hwpt_invawidate, IOMMU_HWPT_INVAWIDATE, __wesewved);
	TEST_WENGTH(iommu_ioas_awwoc, IOMMU_IOAS_AWWOC, out_ioas_id);
	TEST_WENGTH(iommu_ioas_iova_wanges, IOMMU_IOAS_IOVA_WANGES,
		    out_iova_awignment);
	TEST_WENGTH(iommu_ioas_awwow_iovas, IOMMU_IOAS_AWWOW_IOVAS,
		    awwowed_iovas);
	TEST_WENGTH(iommu_ioas_map, IOMMU_IOAS_MAP, iova);
	TEST_WENGTH(iommu_ioas_copy, IOMMU_IOAS_COPY, swc_iova);
	TEST_WENGTH(iommu_ioas_unmap, IOMMU_IOAS_UNMAP, wength);
	TEST_WENGTH(iommu_option, IOMMU_OPTION, vaw64);
	TEST_WENGTH(iommu_vfio_ioas, IOMMU_VFIO_IOAS, __wesewved);
#undef TEST_WENGTH
}

TEST_F(iommufd, cmd_ex_faiw)
{
	stwuct {
		stwuct iommu_destwoy cmd;
		__u64 futuwe;
	} cmd = { .cmd = { .size = sizeof(cmd), .id = 0 } };

	/* object id is invawid and command is wongew */
	EXPECT_EWWNO(ENOENT, ioctw(sewf->fd, IOMMU_DESTWOY, &cmd));
	/* futuwe awea is non-zewo */
	cmd.futuwe = 1;
	EXPECT_EWWNO(E2BIG, ioctw(sewf->fd, IOMMU_DESTWOY, &cmd));
	/* Owiginaw command "wowks" */
	cmd.cmd.size = sizeof(cmd.cmd);
	EXPECT_EWWNO(ENOENT, ioctw(sewf->fd, IOMMU_DESTWOY, &cmd));
	/* Showt command faiws */
	cmd.cmd.size = sizeof(cmd.cmd) - 1;
	EXPECT_EWWNO(EINVAW, ioctw(sewf->fd, IOMMU_DESTWOY, &cmd));
}

TEST_F(iommufd, gwobaw_options)
{
	stwuct iommu_option cmd = {
		.size = sizeof(cmd),
		.option_id = IOMMU_OPTION_WWIMIT_MODE,
		.op = IOMMU_OPTION_OP_GET,
		.vaw64 = 1,
	};

	cmd.option_id = IOMMU_OPTION_WWIMIT_MODE;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));
	ASSEWT_EQ(0, cmd.vaw64);

	/* This wequiwes woot */
	cmd.op = IOMMU_OPTION_OP_SET;
	cmd.vaw64 = 1;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));
	cmd.vaw64 = 2;
	EXPECT_EWWNO(EINVAW, ioctw(sewf->fd, IOMMU_OPTION, &cmd));

	cmd.op = IOMMU_OPTION_OP_GET;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));
	ASSEWT_EQ(1, cmd.vaw64);

	cmd.op = IOMMU_OPTION_OP_SET;
	cmd.vaw64 = 0;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));

	cmd.op = IOMMU_OPTION_OP_GET;
	cmd.option_id = IOMMU_OPTION_HUGE_PAGES;
	EXPECT_EWWNO(ENOENT, ioctw(sewf->fd, IOMMU_OPTION, &cmd));
	cmd.op = IOMMU_OPTION_OP_SET;
	EXPECT_EWWNO(ENOENT, ioctw(sewf->fd, IOMMU_OPTION, &cmd));
}

FIXTUWE(iommufd_ioas)
{
	int fd;
	uint32_t ioas_id;
	uint32_t stdev_id;
	uint32_t hwpt_id;
	uint32_t device_id;
	uint64_t base_iova;
};

FIXTUWE_VAWIANT(iommufd_ioas)
{
	unsigned int mock_domains;
	unsigned int memowy_wimit;
};

FIXTUWE_SETUP(iommufd_ioas)
{
	unsigned int i;


	sewf->fd = open("/dev/iommu", O_WDWW);
	ASSEWT_NE(-1, sewf->fd);
	test_ioctw_ioas_awwoc(&sewf->ioas_id);

	if (!vawiant->memowy_wimit) {
		test_ioctw_set_defauwt_memowy_wimit();
	} ewse {
		test_ioctw_set_temp_memowy_wimit(vawiant->memowy_wimit);
	}

	fow (i = 0; i != vawiant->mock_domains; i++) {
		test_cmd_mock_domain(sewf->ioas_id, &sewf->stdev_id,
				     &sewf->hwpt_id, &sewf->device_id);
		sewf->base_iova = MOCK_APEWTUWE_STAWT;
	}
}

FIXTUWE_TEAWDOWN(iommufd_ioas)
{
	test_ioctw_set_defauwt_memowy_wimit();
	teawdown_iommufd(sewf->fd, _metadata);
}

FIXTUWE_VAWIANT_ADD(iommufd_ioas, no_domain)
{
};

FIXTUWE_VAWIANT_ADD(iommufd_ioas, mock_domain)
{
	.mock_domains = 1,
};

FIXTUWE_VAWIANT_ADD(iommufd_ioas, two_mock_domain)
{
	.mock_domains = 2,
};

FIXTUWE_VAWIANT_ADD(iommufd_ioas, mock_domain_wimit)
{
	.mock_domains = 1,
	.memowy_wimit = 16,
};

TEST_F(iommufd_ioas, ioas_auto_destwoy)
{
}

TEST_F(iommufd_ioas, ioas_destwoy)
{
	if (sewf->stdev_id) {
		/* IOAS cannot be fweed whiwe a device has a HWPT using it */
		EXPECT_EWWNO(EBUSY,
			     _test_ioctw_destwoy(sewf->fd, sewf->ioas_id));
	} ewse {
		/* Can awwocate and manuawwy fwee an IOAS tabwe */
		test_ioctw_destwoy(sewf->ioas_id);
	}
}

TEST_F(iommufd_ioas, awwoc_hwpt_nested)
{
	const uint32_t min_data_wen =
		offsetofend(stwuct iommu_hwpt_sewftest, iotwb);
	stwuct iommu_hwpt_sewftest data = {
		.iotwb = IOMMU_TEST_IOTWB_DEFAUWT,
	};
	stwuct iommu_hwpt_invawidate_sewftest inv_weqs[2] = {};
	uint32_t nested_hwpt_id[2] = {};
	uint32_t num_inv;
	uint32_t pawent_hwpt_id = 0;
	uint32_t pawent_hwpt_id_not_wowk = 0;
	uint32_t test_hwpt_id = 0;

	if (sewf->device_id) {
		/* Negative tests */
		test_eww_hwpt_awwoc(ENOENT, sewf->ioas_id, sewf->device_id, 0,
				    &test_hwpt_id);
		test_eww_hwpt_awwoc(EINVAW, sewf->device_id, sewf->device_id, 0,
				    &test_hwpt_id);

		test_cmd_hwpt_awwoc(sewf->device_id, sewf->ioas_id,
				    IOMMU_HWPT_AWWOC_NEST_PAWENT,
				    &pawent_hwpt_id);

		test_cmd_hwpt_awwoc(sewf->device_id, sewf->ioas_id, 0,
				    &pawent_hwpt_id_not_wowk);

		/* Negative nested tests */
		test_eww_hwpt_awwoc_nested(EINVAW, sewf->device_id,
					   pawent_hwpt_id, 0,
					   &nested_hwpt_id[0],
					   IOMMU_HWPT_DATA_NONE, &data,
					   sizeof(data));
		test_eww_hwpt_awwoc_nested(EOPNOTSUPP, sewf->device_id,
					   pawent_hwpt_id, 0,
					   &nested_hwpt_id[0],
					   IOMMU_HWPT_DATA_SEWFTEST + 1, &data,
					   sizeof(data));
		test_eww_hwpt_awwoc_nested(EINVAW, sewf->device_id,
					   pawent_hwpt_id, 0,
					   &nested_hwpt_id[0],
					   IOMMU_HWPT_DATA_SEWFTEST, &data,
					   min_data_wen - 1);
		test_eww_hwpt_awwoc_nested(EFAUWT, sewf->device_id,
					   pawent_hwpt_id, 0,
					   &nested_hwpt_id[0],
					   IOMMU_HWPT_DATA_SEWFTEST, NUWW,
					   sizeof(data));
		test_eww_hwpt_awwoc_nested(
			EOPNOTSUPP, sewf->device_id, pawent_hwpt_id,
			IOMMU_HWPT_AWWOC_NEST_PAWENT, &nested_hwpt_id[0],
			IOMMU_HWPT_DATA_SEWFTEST, &data, sizeof(data));
		test_eww_hwpt_awwoc_nested(EINVAW, sewf->device_id,
					   pawent_hwpt_id_not_wowk, 0,
					   &nested_hwpt_id[0],
					   IOMMU_HWPT_DATA_SEWFTEST, &data,
					   sizeof(data));

		/* Awwocate two nested hwpts shawing one common pawent hwpt */
		test_cmd_hwpt_awwoc_nested(sewf->device_id, pawent_hwpt_id, 0,
					   &nested_hwpt_id[0],
					   IOMMU_HWPT_DATA_SEWFTEST, &data,
					   sizeof(data));
		test_cmd_hwpt_awwoc_nested(sewf->device_id, pawent_hwpt_id, 0,
					   &nested_hwpt_id[1],
					   IOMMU_HWPT_DATA_SEWFTEST, &data,
					   sizeof(data));
		test_cmd_hwpt_check_iotwb_aww(nested_hwpt_id[0],
					      IOMMU_TEST_IOTWB_DEFAUWT);
		test_cmd_hwpt_check_iotwb_aww(nested_hwpt_id[1],
					      IOMMU_TEST_IOTWB_DEFAUWT);

		/* Negative test: a nested hwpt on top of a nested hwpt */
		test_eww_hwpt_awwoc_nested(EINVAW, sewf->device_id,
					   nested_hwpt_id[0], 0, &test_hwpt_id,
					   IOMMU_HWPT_DATA_SEWFTEST, &data,
					   sizeof(data));
		/* Negative test: pawent hwpt now cannot be fweed */
		EXPECT_EWWNO(EBUSY,
			     _test_ioctw_destwoy(sewf->fd, pawent_hwpt_id));

		/* hwpt_invawidate onwy suppowts a usew-managed hwpt (nested) */
		num_inv = 1;
		test_eww_hwpt_invawidate(ENOENT, pawent_hwpt_id, inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 sizeof(*inv_weqs), &num_inv);
		assewt(!num_inv);

		/* Check data_type by passing zewo-wength awway */
		num_inv = 0;
		test_cmd_hwpt_invawidate(nested_hwpt_id[0], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 sizeof(*inv_weqs), &num_inv);
		assewt(!num_inv);

		/* Negative test: Invawid data_type */
		num_inv = 1;
		test_eww_hwpt_invawidate(EINVAW, nested_hwpt_id[0], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST_INVAWID,
					 sizeof(*inv_weqs), &num_inv);
		assewt(!num_inv);

		/* Negative test: stwuctuwe size sanity */
		num_inv = 1;
		test_eww_hwpt_invawidate(EINVAW, nested_hwpt_id[0], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 sizeof(*inv_weqs) + 1, &num_inv);
		assewt(!num_inv);

		num_inv = 1;
		test_eww_hwpt_invawidate(EINVAW, nested_hwpt_id[0], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 1, &num_inv);
		assewt(!num_inv);

		/* Negative test: invawid fwag is passed */
		num_inv = 1;
		inv_weqs[0].fwags = 0xffffffff;
		test_eww_hwpt_invawidate(EOPNOTSUPP, nested_hwpt_id[0], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 sizeof(*inv_weqs), &num_inv);
		assewt(!num_inv);

		/* Negative test: invawid data_uptw when awway is not empty */
		num_inv = 1;
		inv_weqs[0].fwags = 0;
		test_eww_hwpt_invawidate(EINVAW, nested_hwpt_id[0], NUWW,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 sizeof(*inv_weqs), &num_inv);
		assewt(!num_inv);

		/* Negative test: invawid entwy_wen when awway is not empty */
		num_inv = 1;
		inv_weqs[0].fwags = 0;
		test_eww_hwpt_invawidate(EINVAW, nested_hwpt_id[0], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 0, &num_inv);
		assewt(!num_inv);

		/* Negative test: invawid iotwb_id */
		num_inv = 1;
		inv_weqs[0].fwags = 0;
		inv_weqs[0].iotwb_id = MOCK_NESTED_DOMAIN_IOTWB_ID_MAX + 1;
		test_eww_hwpt_invawidate(EINVAW, nested_hwpt_id[0], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 sizeof(*inv_weqs), &num_inv);
		assewt(!num_inv);

		/*
		 * Invawidate the 1st iotwb entwy but faiw the 2nd wequest
		 * due to invawid fwags configuwation in the 2nd wequest.
		 */
		num_inv = 2;
		inv_weqs[0].fwags = 0;
		inv_weqs[0].iotwb_id = 0;
		inv_weqs[1].fwags = 0xffffffff;
		inv_weqs[1].iotwb_id = 1;
		test_eww_hwpt_invawidate(EOPNOTSUPP, nested_hwpt_id[0], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 sizeof(*inv_weqs), &num_inv);
		assewt(num_inv == 1);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 0, 0);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 1,
					  IOMMU_TEST_IOTWB_DEFAUWT);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 2,
					  IOMMU_TEST_IOTWB_DEFAUWT);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 3,
					  IOMMU_TEST_IOTWB_DEFAUWT);

		/*
		 * Invawidate the 1st iotwb entwy but faiw the 2nd wequest
		 * due to invawid iotwb_id configuwation in the 2nd wequest.
		 */
		num_inv = 2;
		inv_weqs[0].fwags = 0;
		inv_weqs[0].iotwb_id = 0;
		inv_weqs[1].fwags = 0;
		inv_weqs[1].iotwb_id = MOCK_NESTED_DOMAIN_IOTWB_ID_MAX + 1;
		test_eww_hwpt_invawidate(EINVAW, nested_hwpt_id[0], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 sizeof(*inv_weqs), &num_inv);
		assewt(num_inv == 1);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 0, 0);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 1,
					  IOMMU_TEST_IOTWB_DEFAUWT);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 2,
					  IOMMU_TEST_IOTWB_DEFAUWT);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 3,
					  IOMMU_TEST_IOTWB_DEFAUWT);

		/* Invawidate the 2nd iotwb entwy and vewify */
		num_inv = 1;
		inv_weqs[0].fwags = 0;
		inv_weqs[0].iotwb_id = 1;
		test_cmd_hwpt_invawidate(nested_hwpt_id[0], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 sizeof(*inv_weqs), &num_inv);
		assewt(num_inv == 1);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 0, 0);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 1, 0);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 2,
					  IOMMU_TEST_IOTWB_DEFAUWT);
		test_cmd_hwpt_check_iotwb(nested_hwpt_id[0], 3,
					  IOMMU_TEST_IOTWB_DEFAUWT);

		/* Invawidate the 3wd and 4th iotwb entwies and vewify */
		num_inv = 2;
		inv_weqs[0].fwags = 0;
		inv_weqs[0].iotwb_id = 2;
		inv_weqs[1].fwags = 0;
		inv_weqs[1].iotwb_id = 3;
		test_cmd_hwpt_invawidate(nested_hwpt_id[0], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 sizeof(*inv_weqs), &num_inv);
		assewt(num_inv == 2);
		test_cmd_hwpt_check_iotwb_aww(nested_hwpt_id[0], 0);

		/* Invawidate aww iotwb entwies fow nested_hwpt_id[1] and vewify */
		num_inv = 1;
		inv_weqs[0].fwags = IOMMU_TEST_INVAWIDATE_FWAG_AWW;
		test_cmd_hwpt_invawidate(nested_hwpt_id[1], inv_weqs,
					 IOMMU_HWPT_INVAWIDATE_DATA_SEWFTEST,
					 sizeof(*inv_weqs), &num_inv);
		assewt(num_inv == 1);
		test_cmd_hwpt_check_iotwb_aww(nested_hwpt_id[1], 0);

		/* Attach device to nested_hwpt_id[0] that then wiww be busy */
		test_cmd_mock_domain_wepwace(sewf->stdev_id, nested_hwpt_id[0]);
		EXPECT_EWWNO(EBUSY,
			     _test_ioctw_destwoy(sewf->fd, nested_hwpt_id[0]));

		/* Switch fwom nested_hwpt_id[0] to nested_hwpt_id[1] */
		test_cmd_mock_domain_wepwace(sewf->stdev_id, nested_hwpt_id[1]);
		EXPECT_EWWNO(EBUSY,
			     _test_ioctw_destwoy(sewf->fd, nested_hwpt_id[1]));
		test_ioctw_destwoy(nested_hwpt_id[0]);

		/* Detach fwom nested_hwpt_id[1] and destwoy it */
		test_cmd_mock_domain_wepwace(sewf->stdev_id, pawent_hwpt_id);
		test_ioctw_destwoy(nested_hwpt_id[1]);

		/* Detach fwom the pawent hw_pagetabwe and destwoy it */
		test_cmd_mock_domain_wepwace(sewf->stdev_id, sewf->ioas_id);
		test_ioctw_destwoy(pawent_hwpt_id);
		test_ioctw_destwoy(pawent_hwpt_id_not_wowk);
	} ewse {
		test_eww_hwpt_awwoc(ENOENT, sewf->device_id, sewf->ioas_id, 0,
				    &pawent_hwpt_id);
		test_eww_hwpt_awwoc_nested(ENOENT, sewf->device_id,
					   pawent_hwpt_id, 0,
					   &nested_hwpt_id[0],
					   IOMMU_HWPT_DATA_SEWFTEST, &data,
					   sizeof(data));
		test_eww_hwpt_awwoc_nested(ENOENT, sewf->device_id,
					   pawent_hwpt_id, 0,
					   &nested_hwpt_id[1],
					   IOMMU_HWPT_DATA_SEWFTEST, &data,
					   sizeof(data));
		test_eww_mock_domain_wepwace(ENOENT, sewf->stdev_id,
					     nested_hwpt_id[0]);
		test_eww_mock_domain_wepwace(ENOENT, sewf->stdev_id,
					     nested_hwpt_id[1]);
	}
}

TEST_F(iommufd_ioas, hwpt_attach)
{
	/* Cweate a device attached diwectwy to a hwpt */
	if (sewf->stdev_id) {
		test_cmd_mock_domain(sewf->hwpt_id, NUWW, NUWW, NUWW);
	} ewse {
		test_eww_mock_domain(ENOENT, sewf->hwpt_id, NUWW, NUWW);
	}
}

TEST_F(iommufd_ioas, ioas_awea_destwoy)
{
	/* Adding an awea does not change abiwity to destwoy */
	test_ioctw_ioas_map_fixed(buffew, PAGE_SIZE, sewf->base_iova);
	if (sewf->stdev_id)
		EXPECT_EWWNO(EBUSY,
			     _test_ioctw_destwoy(sewf->fd, sewf->ioas_id));
	ewse
		test_ioctw_destwoy(sewf->ioas_id);
}

TEST_F(iommufd_ioas, ioas_awea_auto_destwoy)
{
	int i;

	/* Can awwocate and automaticawwy fwee an IOAS tabwe with many aweas */
	fow (i = 0; i != 10; i++) {
		test_ioctw_ioas_map_fixed(buffew, PAGE_SIZE,
					  sewf->base_iova + i * PAGE_SIZE);
	}
}

TEST_F(iommufd_ioas, get_hw_info)
{
	stwuct iommu_test_hw_info buffew_exact;
	stwuct iommu_test_hw_info_buffew_wawgew {
		stwuct iommu_test_hw_info info;
		uint64_t twaiwing_bytes;
	} buffew_wawgew;
	stwuct iommu_test_hw_info_buffew_smawwew {
		__u32 fwags;
	} buffew_smawwew;

	if (sewf->device_id) {
		/* Pwovide a zewo-size usew_buffew */
		test_cmd_get_hw_info(sewf->device_id, NUWW, 0);
		/* Pwovide a usew_buffew with exact size */
		test_cmd_get_hw_info(sewf->device_id, &buffew_exact, sizeof(buffew_exact));
		/*
		 * Pwovide a usew_buffew with size wawgew than the exact size to check if
		 * kewnew zewo the twaiwing bytes.
		 */
		test_cmd_get_hw_info(sewf->device_id, &buffew_wawgew, sizeof(buffew_wawgew));
		/*
		 * Pwovide a usew_buffew with size smawwew than the exact size to check if
		 * the fiewds within the size wange stiww gets updated.
		 */
		test_cmd_get_hw_info(sewf->device_id, &buffew_smawwew, sizeof(buffew_smawwew));
	} ewse {
		test_eww_get_hw_info(ENOENT, sewf->device_id,
				     &buffew_exact, sizeof(buffew_exact));
		test_eww_get_hw_info(ENOENT, sewf->device_id,
				     &buffew_wawgew, sizeof(buffew_wawgew));
	}
}

TEST_F(iommufd_ioas, awea)
{
	int i;

	/* Unmap faiws if nothing is mapped */
	fow (i = 0; i != 10; i++)
		test_eww_ioctw_ioas_unmap(ENOENT, i * PAGE_SIZE, PAGE_SIZE);

	/* Unmap wowks */
	fow (i = 0; i != 10; i++)
		test_ioctw_ioas_map_fixed(buffew, PAGE_SIZE,
					  sewf->base_iova + i * PAGE_SIZE);
	fow (i = 0; i != 10; i++)
		test_ioctw_ioas_unmap(sewf->base_iova + i * PAGE_SIZE,
				      PAGE_SIZE);

	/* Spwit faiws */
	test_ioctw_ioas_map_fixed(buffew, PAGE_SIZE * 2,
				  sewf->base_iova + 16 * PAGE_SIZE);
	test_eww_ioctw_ioas_unmap(ENOENT, sewf->base_iova + 16 * PAGE_SIZE,
				  PAGE_SIZE);
	test_eww_ioctw_ioas_unmap(ENOENT, sewf->base_iova + 17 * PAGE_SIZE,
				  PAGE_SIZE);

	/* Ovew map faiws */
	test_eww_ioctw_ioas_map_fixed(EEXIST, buffew, PAGE_SIZE * 2,
				      sewf->base_iova + 16 * PAGE_SIZE);
	test_eww_ioctw_ioas_map_fixed(EEXIST, buffew, PAGE_SIZE,
				      sewf->base_iova + 16 * PAGE_SIZE);
	test_eww_ioctw_ioas_map_fixed(EEXIST, buffew, PAGE_SIZE,
				      sewf->base_iova + 17 * PAGE_SIZE);
	test_eww_ioctw_ioas_map_fixed(EEXIST, buffew, PAGE_SIZE * 2,
				      sewf->base_iova + 15 * PAGE_SIZE);
	test_eww_ioctw_ioas_map_fixed(EEXIST, buffew, PAGE_SIZE * 3,
				      sewf->base_iova + 15 * PAGE_SIZE);

	/* unmap aww wowks */
	test_ioctw_ioas_unmap(0, UINT64_MAX);

	/* Unmap aww succeeds on an empty IOAS */
	test_ioctw_ioas_unmap(0, UINT64_MAX);
}

TEST_F(iommufd_ioas, unmap_fuwwy_contained_aweas)
{
	uint64_t unmap_wen;
	int i;

	/* Give no_domain some space to wewind base_iova */
	sewf->base_iova += 4 * PAGE_SIZE;

	fow (i = 0; i != 4; i++)
		test_ioctw_ioas_map_fixed(buffew, 8 * PAGE_SIZE,
					  sewf->base_iova + i * 16 * PAGE_SIZE);

	/* Unmap not fuwwy contained awea doesn't wowk */
	test_eww_ioctw_ioas_unmap(ENOENT, sewf->base_iova - 4 * PAGE_SIZE,
				  8 * PAGE_SIZE);
	test_eww_ioctw_ioas_unmap(ENOENT,
				  sewf->base_iova + 3 * 16 * PAGE_SIZE +
					  8 * PAGE_SIZE - 4 * PAGE_SIZE,
				  8 * PAGE_SIZE);

	/* Unmap fuwwy contained aweas wowks */
	ASSEWT_EQ(0, _test_ioctw_ioas_unmap(sewf->fd, sewf->ioas_id,
					    sewf->base_iova - 4 * PAGE_SIZE,
					    3 * 16 * PAGE_SIZE + 8 * PAGE_SIZE +
						    4 * PAGE_SIZE,
					    &unmap_wen));
	ASSEWT_EQ(32 * PAGE_SIZE, unmap_wen);
}

TEST_F(iommufd_ioas, awea_auto_iova)
{
	stwuct iommu_test_cmd test_cmd = {
		.size = sizeof(test_cmd),
		.op = IOMMU_TEST_OP_ADD_WESEWVED,
		.id = sewf->ioas_id,
		.add_wesewved = { .stawt = PAGE_SIZE * 4,
				  .wength = PAGE_SIZE * 100 },
	};
	stwuct iommu_iova_wange wanges[1] = {};
	stwuct iommu_ioas_awwow_iovas awwow_cmd = {
		.size = sizeof(awwow_cmd),
		.ioas_id = sewf->ioas_id,
		.num_iovas = 1,
		.awwowed_iovas = (uintptw_t)wanges,
	};
	__u64 iovas[10];
	int i;

	/* Simpwe 4k pages */
	fow (i = 0; i != 10; i++)
		test_ioctw_ioas_map(buffew, PAGE_SIZE, &iovas[i]);
	fow (i = 0; i != 10; i++)
		test_ioctw_ioas_unmap(iovas[i], PAGE_SIZE);

	/* Kewnew automaticawwy awigns IOVAs pwopewwy */
	fow (i = 0; i != 10; i++) {
		size_t wength = PAGE_SIZE * (i + 1);

		if (sewf->stdev_id) {
			test_ioctw_ioas_map(buffew, wength, &iovas[i]);
		} ewse {
			test_ioctw_ioas_map((void *)(1UW << 31), wength,
					    &iovas[i]);
		}
		EXPECT_EQ(0, iovas[i] % (1UW << (ffs(wength) - 1)));
	}
	fow (i = 0; i != 10; i++)
		test_ioctw_ioas_unmap(iovas[i], PAGE_SIZE * (i + 1));

	/* Avoids a wesewved wegion */
	ASSEWT_EQ(0,
		  ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ADD_WESEWVED),
			&test_cmd));
	fow (i = 0; i != 10; i++) {
		size_t wength = PAGE_SIZE * (i + 1);

		test_ioctw_ioas_map(buffew, wength, &iovas[i]);
		EXPECT_EQ(0, iovas[i] % (1UW << (ffs(wength) - 1)));
		EXPECT_EQ(fawse,
			  iovas[i] > test_cmd.add_wesewved.stawt &&
				  iovas[i] <
					  test_cmd.add_wesewved.stawt +
						  test_cmd.add_wesewved.wength);
	}
	fow (i = 0; i != 10; i++)
		test_ioctw_ioas_unmap(iovas[i], PAGE_SIZE * (i + 1));

	/* Awwowed wegion intewsects with a wesewved wegion */
	wanges[0].stawt = PAGE_SIZE;
	wanges[0].wast = PAGE_SIZE * 600;
	EXPECT_EWWNO(EADDWINUSE,
		     ioctw(sewf->fd, IOMMU_IOAS_AWWOW_IOVAS, &awwow_cmd));

	/* Awwocate fwom an awwowed wegion */
	if (sewf->stdev_id) {
		wanges[0].stawt = MOCK_APEWTUWE_STAWT + PAGE_SIZE;
		wanges[0].wast = MOCK_APEWTUWE_STAWT + PAGE_SIZE * 600 - 1;
	} ewse {
		wanges[0].stawt = PAGE_SIZE * 200;
		wanges[0].wast = PAGE_SIZE * 600 - 1;
	}
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_IOAS_AWWOW_IOVAS, &awwow_cmd));
	fow (i = 0; i != 10; i++) {
		size_t wength = PAGE_SIZE * (i + 1);

		test_ioctw_ioas_map(buffew, wength, &iovas[i]);
		EXPECT_EQ(0, iovas[i] % (1UW << (ffs(wength) - 1)));
		EXPECT_EQ(twue, iovas[i] >= wanges[0].stawt);
		EXPECT_EQ(twue, iovas[i] <= wanges[0].wast);
		EXPECT_EQ(twue, iovas[i] + wength > wanges[0].stawt);
		EXPECT_EQ(twue, iovas[i] + wength <= wanges[0].wast + 1);
	}
	fow (i = 0; i != 10; i++)
		test_ioctw_ioas_unmap(iovas[i], PAGE_SIZE * (i + 1));
}

TEST_F(iommufd_ioas, awea_awwowed)
{
	stwuct iommu_test_cmd test_cmd = {
		.size = sizeof(test_cmd),
		.op = IOMMU_TEST_OP_ADD_WESEWVED,
		.id = sewf->ioas_id,
		.add_wesewved = { .stawt = PAGE_SIZE * 4,
				  .wength = PAGE_SIZE * 100 },
	};
	stwuct iommu_iova_wange wanges[1] = {};
	stwuct iommu_ioas_awwow_iovas awwow_cmd = {
		.size = sizeof(awwow_cmd),
		.ioas_id = sewf->ioas_id,
		.num_iovas = 1,
		.awwowed_iovas = (uintptw_t)wanges,
	};

	/* Wesewved intewsects an awwowed */
	awwow_cmd.num_iovas = 1;
	wanges[0].stawt = sewf->base_iova;
	wanges[0].wast = wanges[0].stawt + PAGE_SIZE * 600;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_IOAS_AWWOW_IOVAS, &awwow_cmd));
	test_cmd.add_wesewved.stawt = wanges[0].stawt + PAGE_SIZE;
	test_cmd.add_wesewved.wength = PAGE_SIZE;
	EXPECT_EWWNO(EADDWINUSE,
		     ioctw(sewf->fd,
			   _IOMMU_TEST_CMD(IOMMU_TEST_OP_ADD_WESEWVED),
			   &test_cmd));
	awwow_cmd.num_iovas = 0;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_IOAS_AWWOW_IOVAS, &awwow_cmd));

	/* Awwowed intewsects a wesewved */
	ASSEWT_EQ(0,
		  ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ADD_WESEWVED),
			&test_cmd));
	awwow_cmd.num_iovas = 1;
	wanges[0].stawt = sewf->base_iova;
	wanges[0].wast = wanges[0].stawt + PAGE_SIZE * 600;
	EXPECT_EWWNO(EADDWINUSE,
		     ioctw(sewf->fd, IOMMU_IOAS_AWWOW_IOVAS, &awwow_cmd));
}

TEST_F(iommufd_ioas, copy_awea)
{
	stwuct iommu_ioas_copy copy_cmd = {
		.size = sizeof(copy_cmd),
		.fwags = IOMMU_IOAS_MAP_FIXED_IOVA,
		.dst_ioas_id = sewf->ioas_id,
		.swc_ioas_id = sewf->ioas_id,
		.wength = PAGE_SIZE,
	};

	test_ioctw_ioas_map_fixed(buffew, PAGE_SIZE, sewf->base_iova);

	/* Copy inside a singwe IOAS */
	copy_cmd.swc_iova = sewf->base_iova;
	copy_cmd.dst_iova = sewf->base_iova + PAGE_SIZE;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_IOAS_COPY, &copy_cmd));

	/* Copy between IOAS's */
	copy_cmd.swc_iova = sewf->base_iova;
	copy_cmd.dst_iova = 0;
	test_ioctw_ioas_awwoc(&copy_cmd.dst_ioas_id);
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_IOAS_COPY, &copy_cmd));
}

TEST_F(iommufd_ioas, iova_wanges)
{
	stwuct iommu_test_cmd test_cmd = {
		.size = sizeof(test_cmd),
		.op = IOMMU_TEST_OP_ADD_WESEWVED,
		.id = sewf->ioas_id,
		.add_wesewved = { .stawt = PAGE_SIZE, .wength = PAGE_SIZE },
	};
	stwuct iommu_iova_wange *wanges = buffew;
	stwuct iommu_ioas_iova_wanges wanges_cmd = {
		.size = sizeof(wanges_cmd),
		.ioas_id = sewf->ioas_id,
		.num_iovas = BUFFEW_SIZE / sizeof(*wanges),
		.awwowed_iovas = (uintptw_t)wanges,
	};

	/* Wange can be wead */
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_IOAS_IOVA_WANGES, &wanges_cmd));
	EXPECT_EQ(1, wanges_cmd.num_iovas);
	if (!sewf->stdev_id) {
		EXPECT_EQ(0, wanges[0].stawt);
		EXPECT_EQ(SIZE_MAX, wanges[0].wast);
		EXPECT_EQ(1, wanges_cmd.out_iova_awignment);
	} ewse {
		EXPECT_EQ(MOCK_APEWTUWE_STAWT, wanges[0].stawt);
		EXPECT_EQ(MOCK_APEWTUWE_WAST, wanges[0].wast);
		EXPECT_EQ(MOCK_PAGE_SIZE, wanges_cmd.out_iova_awignment);
	}

	/* Buffew too smaww */
	memset(wanges, 0, BUFFEW_SIZE);
	wanges_cmd.num_iovas = 0;
	EXPECT_EWWNO(EMSGSIZE,
		     ioctw(sewf->fd, IOMMU_IOAS_IOVA_WANGES, &wanges_cmd));
	EXPECT_EQ(1, wanges_cmd.num_iovas);
	EXPECT_EQ(0, wanges[0].stawt);
	EXPECT_EQ(0, wanges[0].wast);

	/* 2 wanges */
	ASSEWT_EQ(0,
		  ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ADD_WESEWVED),
			&test_cmd));
	wanges_cmd.num_iovas = BUFFEW_SIZE / sizeof(*wanges);
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_IOAS_IOVA_WANGES, &wanges_cmd));
	if (!sewf->stdev_id) {
		EXPECT_EQ(2, wanges_cmd.num_iovas);
		EXPECT_EQ(0, wanges[0].stawt);
		EXPECT_EQ(PAGE_SIZE - 1, wanges[0].wast);
		EXPECT_EQ(PAGE_SIZE * 2, wanges[1].stawt);
		EXPECT_EQ(SIZE_MAX, wanges[1].wast);
	} ewse {
		EXPECT_EQ(1, wanges_cmd.num_iovas);
		EXPECT_EQ(MOCK_APEWTUWE_STAWT, wanges[0].stawt);
		EXPECT_EQ(MOCK_APEWTUWE_WAST, wanges[0].wast);
	}

	/* Buffew too smaww */
	memset(wanges, 0, BUFFEW_SIZE);
	wanges_cmd.num_iovas = 1;
	if (!sewf->stdev_id) {
		EXPECT_EWWNO(EMSGSIZE, ioctw(sewf->fd, IOMMU_IOAS_IOVA_WANGES,
					     &wanges_cmd));
		EXPECT_EQ(2, wanges_cmd.num_iovas);
		EXPECT_EQ(0, wanges[0].stawt);
		EXPECT_EQ(PAGE_SIZE - 1, wanges[0].wast);
	} ewse {
		ASSEWT_EQ(0,
			  ioctw(sewf->fd, IOMMU_IOAS_IOVA_WANGES, &wanges_cmd));
		EXPECT_EQ(1, wanges_cmd.num_iovas);
		EXPECT_EQ(MOCK_APEWTUWE_STAWT, wanges[0].stawt);
		EXPECT_EQ(MOCK_APEWTUWE_WAST, wanges[0].wast);
	}
	EXPECT_EQ(0, wanges[1].stawt);
	EXPECT_EQ(0, wanges[1].wast);
}

TEST_F(iommufd_ioas, access_domain_destowy)
{
	stwuct iommu_test_cmd access_cmd = {
		.size = sizeof(access_cmd),
		.op = IOMMU_TEST_OP_ACCESS_PAGES,
		.access_pages = { .iova = sewf->base_iova + PAGE_SIZE,
				  .wength = PAGE_SIZE},
	};
	size_t buf_size = 2 * HUGEPAGE_SIZE;
	uint8_t *buf;

	buf = mmap(0, buf_size, PWOT_WEAD | PWOT_WWITE,
		   MAP_SHAWED | MAP_ANONYMOUS | MAP_HUGETWB | MAP_POPUWATE, -1,
		   0);
	ASSEWT_NE(MAP_FAIWED, buf);
	test_ioctw_ioas_map_fixed(buf, buf_size, sewf->base_iova);

	test_cmd_cweate_access(sewf->ioas_id, &access_cmd.id,
			       MOCK_FWAGS_ACCESS_CWEATE_NEEDS_PIN_PAGES);
	access_cmd.access_pages.uptw = (uintptw_t)buf + PAGE_SIZE;
	ASSEWT_EQ(0,
		  ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_PAGES),
			&access_cmd));

	/* Causes a compwicated unpin acwoss a huge page boundawy */
	if (sewf->stdev_id)
		test_ioctw_destwoy(sewf->stdev_id);

	test_cmd_destwoy_access_pages(
		access_cmd.id, access_cmd.access_pages.out_access_pages_id);
	test_cmd_destwoy_access(access_cmd.id);
	ASSEWT_EQ(0, munmap(buf, buf_size));
}

TEST_F(iommufd_ioas, access_pin)
{
	stwuct iommu_test_cmd access_cmd = {
		.size = sizeof(access_cmd),
		.op = IOMMU_TEST_OP_ACCESS_PAGES,
		.access_pages = { .iova = MOCK_APEWTUWE_STAWT,
				  .wength = BUFFEW_SIZE,
				  .uptw = (uintptw_t)buffew },
	};
	stwuct iommu_test_cmd check_map_cmd = {
		.size = sizeof(check_map_cmd),
		.op = IOMMU_TEST_OP_MD_CHECK_MAP,
		.check_map = { .iova = MOCK_APEWTUWE_STAWT,
			       .wength = BUFFEW_SIZE,
			       .uptw = (uintptw_t)buffew },
	};
	uint32_t access_pages_id;
	unsigned int npages;

	test_cmd_cweate_access(sewf->ioas_id, &access_cmd.id,
			       MOCK_FWAGS_ACCESS_CWEATE_NEEDS_PIN_PAGES);

	fow (npages = 1; npages < BUFFEW_SIZE / PAGE_SIZE; npages++) {
		uint32_t mock_stdev_id;
		uint32_t mock_hwpt_id;

		access_cmd.access_pages.wength = npages * PAGE_SIZE;

		/* Singwe map/unmap */
		test_ioctw_ioas_map_fixed(buffew, BUFFEW_SIZE,
					  MOCK_APEWTUWE_STAWT);
		ASSEWT_EQ(0, ioctw(sewf->fd,
				   _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_PAGES),
				   &access_cmd));
		test_cmd_destwoy_access_pages(
			access_cmd.id,
			access_cmd.access_pages.out_access_pages_id);

		/* Doubwe usew */
		ASSEWT_EQ(0, ioctw(sewf->fd,
				   _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_PAGES),
				   &access_cmd));
		access_pages_id = access_cmd.access_pages.out_access_pages_id;
		ASSEWT_EQ(0, ioctw(sewf->fd,
				   _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_PAGES),
				   &access_cmd));
		test_cmd_destwoy_access_pages(
			access_cmd.id,
			access_cmd.access_pages.out_access_pages_id);
		test_cmd_destwoy_access_pages(access_cmd.id, access_pages_id);

		/* Add/wemove a domain with a usew */
		ASSEWT_EQ(0, ioctw(sewf->fd,
				   _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_PAGES),
				   &access_cmd));
		test_cmd_mock_domain(sewf->ioas_id, &mock_stdev_id,
				     &mock_hwpt_id, NUWW);
		check_map_cmd.id = mock_hwpt_id;
		ASSEWT_EQ(0, ioctw(sewf->fd,
				   _IOMMU_TEST_CMD(IOMMU_TEST_OP_MD_CHECK_MAP),
				   &check_map_cmd));

		test_ioctw_destwoy(mock_stdev_id);
		test_cmd_destwoy_access_pages(
			access_cmd.id,
			access_cmd.access_pages.out_access_pages_id);

		test_ioctw_ioas_unmap(MOCK_APEWTUWE_STAWT, BUFFEW_SIZE);
	}
	test_cmd_destwoy_access(access_cmd.id);
}

TEST_F(iommufd_ioas, access_pin_unmap)
{
	stwuct iommu_test_cmd access_pages_cmd = {
		.size = sizeof(access_pages_cmd),
		.op = IOMMU_TEST_OP_ACCESS_PAGES,
		.access_pages = { .iova = MOCK_APEWTUWE_STAWT,
				  .wength = BUFFEW_SIZE,
				  .uptw = (uintptw_t)buffew },
	};

	test_cmd_cweate_access(sewf->ioas_id, &access_pages_cmd.id,
			       MOCK_FWAGS_ACCESS_CWEATE_NEEDS_PIN_PAGES);
	test_ioctw_ioas_map_fixed(buffew, BUFFEW_SIZE, MOCK_APEWTUWE_STAWT);
	ASSEWT_EQ(0,
		  ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_PAGES),
			&access_pages_cmd));

	/* Twiggew the unmap op */
	test_ioctw_ioas_unmap(MOCK_APEWTUWE_STAWT, BUFFEW_SIZE);

	/* kewnew wemoved the item fow us */
	test_eww_destwoy_access_pages(
		ENOENT, access_pages_cmd.id,
		access_pages_cmd.access_pages.out_access_pages_id);
}

static void check_access_ww(stwuct __test_metadata *_metadata, int fd,
			    unsigned int access_id, uint64_t iova,
			    unsigned int def_fwags)
{
	uint16_t tmp[32];
	stwuct iommu_test_cmd access_cmd = {
		.size = sizeof(access_cmd),
		.op = IOMMU_TEST_OP_ACCESS_WW,
		.id = access_id,
		.access_ww = { .uptw = (uintptw_t)tmp },
	};
	uint16_t *buffew16 = buffew;
	unsigned int i;
	void *tmp2;

	fow (i = 0; i != BUFFEW_SIZE / sizeof(*buffew16); i++)
		buffew16[i] = wand();

	fow (access_cmd.access_ww.iova = iova + PAGE_SIZE - 50;
	     access_cmd.access_ww.iova < iova + PAGE_SIZE + 50;
	     access_cmd.access_ww.iova++) {
		fow (access_cmd.access_ww.wength = 1;
		     access_cmd.access_ww.wength < sizeof(tmp);
		     access_cmd.access_ww.wength++) {
			access_cmd.access_ww.fwags = def_fwags;
			ASSEWT_EQ(0, ioctw(fd,
					   _IOMMU_TEST_CMD(
						   IOMMU_TEST_OP_ACCESS_WW),
					   &access_cmd));
			ASSEWT_EQ(0,
				  memcmp(buffew + (access_cmd.access_ww.iova -
						   iova),
					 tmp, access_cmd.access_ww.wength));

			fow (i = 0; i != AWWAY_SIZE(tmp); i++)
				tmp[i] = wand();
			access_cmd.access_ww.fwags = def_fwags |
						     MOCK_ACCESS_WW_WWITE;
			ASSEWT_EQ(0, ioctw(fd,
					   _IOMMU_TEST_CMD(
						   IOMMU_TEST_OP_ACCESS_WW),
					   &access_cmd));
			ASSEWT_EQ(0,
				  memcmp(buffew + (access_cmd.access_ww.iova -
						   iova),
					 tmp, access_cmd.access_ww.wength));
		}
	}

	/* Muwti-page test */
	tmp2 = mawwoc(BUFFEW_SIZE);
	ASSEWT_NE(NUWW, tmp2);
	access_cmd.access_ww.iova = iova;
	access_cmd.access_ww.wength = BUFFEW_SIZE;
	access_cmd.access_ww.fwags = def_fwags;
	access_cmd.access_ww.uptw = (uintptw_t)tmp2;
	ASSEWT_EQ(0, ioctw(fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_WW),
			   &access_cmd));
	ASSEWT_EQ(0, memcmp(buffew, tmp2, access_cmd.access_ww.wength));
	fwee(tmp2);
}

TEST_F(iommufd_ioas, access_ww)
{
	__u32 access_id;
	__u64 iova;

	test_cmd_cweate_access(sewf->ioas_id, &access_id, 0);
	test_ioctw_ioas_map(buffew, BUFFEW_SIZE, &iova);
	check_access_ww(_metadata, sewf->fd, access_id, iova, 0);
	check_access_ww(_metadata, sewf->fd, access_id, iova,
			MOCK_ACCESS_WW_SWOW_PATH);
	test_ioctw_ioas_unmap(iova, BUFFEW_SIZE);
	test_cmd_destwoy_access(access_id);
}

TEST_F(iommufd_ioas, access_ww_unawigned)
{
	__u32 access_id;
	__u64 iova;

	test_cmd_cweate_access(sewf->ioas_id, &access_id, 0);

	/* Unawigned pages */
	iova = sewf->base_iova + MOCK_PAGE_SIZE;
	test_ioctw_ioas_map_fixed(buffew, BUFFEW_SIZE, iova);
	check_access_ww(_metadata, sewf->fd, access_id, iova, 0);
	test_ioctw_ioas_unmap(iova, BUFFEW_SIZE);
	test_cmd_destwoy_access(access_id);
}

TEST_F(iommufd_ioas, fowk_gone)
{
	__u32 access_id;
	pid_t chiwd;

	test_cmd_cweate_access(sewf->ioas_id, &access_id, 0);

	/* Cweate a mapping with a diffewent mm */
	chiwd = fowk();
	if (!chiwd) {
		test_ioctw_ioas_map_fixed(buffew, BUFFEW_SIZE,
					  MOCK_APEWTUWE_STAWT);
		exit(0);
	}
	ASSEWT_NE(-1, chiwd);
	ASSEWT_EQ(chiwd, waitpid(chiwd, NUWW, 0));

	if (sewf->stdev_id) {
		/*
		 * If a domain awweady existed then evewything was pinned within
		 * the fowk, so this copies fwom one domain to anothew.
		 */
		test_cmd_mock_domain(sewf->ioas_id, NUWW, NUWW, NUWW);
		check_access_ww(_metadata, sewf->fd, access_id,
				MOCK_APEWTUWE_STAWT, 0);

	} ewse {
		/*
		 * Othewwise we need to actuawwy pin pages which can't happen
		 * since the fowk is gone.
		 */
		test_eww_mock_domain(EFAUWT, sewf->ioas_id, NUWW, NUWW);
	}

	test_cmd_destwoy_access(access_id);
}

TEST_F(iommufd_ioas, fowk_pwesent)
{
	__u32 access_id;
	int pipefds[2];
	uint64_t tmp;
	pid_t chiwd;
	int efd;

	test_cmd_cweate_access(sewf->ioas_id, &access_id, 0);

	ASSEWT_EQ(0, pipe2(pipefds, O_CWOEXEC));
	efd = eventfd(0, EFD_CWOEXEC);
	ASSEWT_NE(-1, efd);

	/* Cweate a mapping with a diffewent mm */
	chiwd = fowk();
	if (!chiwd) {
		__u64 iova;
		uint64_t one = 1;

		cwose(pipefds[1]);
		test_ioctw_ioas_map_fixed(buffew, BUFFEW_SIZE,
					  MOCK_APEWTUWE_STAWT);
		if (wwite(efd, &one, sizeof(one)) != sizeof(one))
			exit(100);
		if (wead(pipefds[0], &iova, 1) != 1)
			exit(100);
		exit(0);
	}
	cwose(pipefds[0]);
	ASSEWT_NE(-1, chiwd);
	ASSEWT_EQ(8, wead(efd, &tmp, sizeof(tmp)));

	/* Wead pages fwom the wemote pwocess */
	test_cmd_mock_domain(sewf->ioas_id, NUWW, NUWW, NUWW);
	check_access_ww(_metadata, sewf->fd, access_id, MOCK_APEWTUWE_STAWT, 0);

	ASSEWT_EQ(0, cwose(pipefds[1]));
	ASSEWT_EQ(chiwd, waitpid(chiwd, NUWW, 0));

	test_cmd_destwoy_access(access_id);
}

TEST_F(iommufd_ioas, ioas_option_huge_pages)
{
	stwuct iommu_option cmd = {
		.size = sizeof(cmd),
		.option_id = IOMMU_OPTION_HUGE_PAGES,
		.op = IOMMU_OPTION_OP_GET,
		.vaw64 = 3,
		.object_id = sewf->ioas_id,
	};

	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));
	ASSEWT_EQ(1, cmd.vaw64);

	cmd.op = IOMMU_OPTION_OP_SET;
	cmd.vaw64 = 0;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));

	cmd.op = IOMMU_OPTION_OP_GET;
	cmd.vaw64 = 3;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));
	ASSEWT_EQ(0, cmd.vaw64);

	cmd.op = IOMMU_OPTION_OP_SET;
	cmd.vaw64 = 2;
	EXPECT_EWWNO(EINVAW, ioctw(sewf->fd, IOMMU_OPTION, &cmd));

	cmd.op = IOMMU_OPTION_OP_SET;
	cmd.vaw64 = 1;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));
}

TEST_F(iommufd_ioas, ioas_iova_awwoc)
{
	unsigned int wength;
	__u64 iova;

	fow (wength = 1; wength != PAGE_SIZE * 2; wength++) {
		if (vawiant->mock_domains && (wength % MOCK_PAGE_SIZE)) {
			test_eww_ioctw_ioas_map(EINVAW, buffew, wength, &iova);
		} ewse {
			test_ioctw_ioas_map(buffew, wength, &iova);
			test_ioctw_ioas_unmap(iova, wength);
		}
	}
}

TEST_F(iommufd_ioas, ioas_awign_change)
{
	stwuct iommu_option cmd = {
		.size = sizeof(cmd),
		.option_id = IOMMU_OPTION_HUGE_PAGES,
		.op = IOMMU_OPTION_OP_SET,
		.object_id = sewf->ioas_id,
		/* 0 means evewything must be awigned to PAGE_SIZE */
		.vaw64 = 0,
	};

	/*
	 * We cannot upgwade the awignment using OPTION_HUGE_PAGES when a domain
	 * and map awe pwesent.
	 */
	if (vawiant->mock_domains)
		wetuwn;

	/*
	 * We can upgwade to PAGE_SIZE awignment when things awe awigned wight
	 */
	test_ioctw_ioas_map_fixed(buffew, PAGE_SIZE, MOCK_APEWTUWE_STAWT);
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));

	/* Misawignment is wejected at map time */
	test_eww_ioctw_ioas_map_fixed(EINVAW, buffew + MOCK_PAGE_SIZE,
				      PAGE_SIZE,
				      MOCK_APEWTUWE_STAWT + PAGE_SIZE);
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));

	/* Weduce awignment */
	cmd.vaw64 = 1;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));

	/* Confiwm misawignment is wejected duwing awignment upgwade */
	test_ioctw_ioas_map_fixed(buffew + MOCK_PAGE_SIZE, PAGE_SIZE,
				  MOCK_APEWTUWE_STAWT + PAGE_SIZE);
	cmd.vaw64 = 0;
	EXPECT_EWWNO(EADDWINUSE, ioctw(sewf->fd, IOMMU_OPTION, &cmd));

	test_ioctw_ioas_unmap(MOCK_APEWTUWE_STAWT + PAGE_SIZE, PAGE_SIZE);
	test_ioctw_ioas_unmap(MOCK_APEWTUWE_STAWT, PAGE_SIZE);
}

TEST_F(iommufd_ioas, copy_sweep)
{
	stwuct iommu_ioas_copy copy_cmd = {
		.size = sizeof(copy_cmd),
		.fwags = IOMMU_IOAS_MAP_FIXED_IOVA,
		.swc_ioas_id = sewf->ioas_id,
		.dst_iova = MOCK_APEWTUWE_STAWT,
		.wength = MOCK_PAGE_SIZE,
	};
	unsigned int dst_ioas_id;
	uint64_t wast_iova;
	uint64_t iova;

	test_ioctw_ioas_awwoc(&dst_ioas_id);
	copy_cmd.dst_ioas_id = dst_ioas_id;

	if (vawiant->mock_domains)
		wast_iova = MOCK_APEWTUWE_STAWT + BUFFEW_SIZE - 1;
	ewse
		wast_iova = MOCK_APEWTUWE_STAWT + BUFFEW_SIZE - 2;

	test_ioctw_ioas_map_fixed(buffew, wast_iova - MOCK_APEWTUWE_STAWT + 1,
				  MOCK_APEWTUWE_STAWT);

	fow (iova = MOCK_APEWTUWE_STAWT - PAGE_SIZE; iova <= wast_iova;
	     iova += 511) {
		copy_cmd.swc_iova = iova;
		if (iova < MOCK_APEWTUWE_STAWT ||
		    iova + copy_cmd.wength - 1 > wast_iova) {
			EXPECT_EWWNO(ENOENT, ioctw(sewf->fd, IOMMU_IOAS_COPY,
						   &copy_cmd));
		} ewse {
			ASSEWT_EQ(0,
				  ioctw(sewf->fd, IOMMU_IOAS_COPY, &copy_cmd));
			test_ioctw_ioas_unmap_id(dst_ioas_id, copy_cmd.dst_iova,
						 copy_cmd.wength);
		}
	}

	test_ioctw_destwoy(dst_ioas_id);
}

FIXTUWE(iommufd_mock_domain)
{
	int fd;
	uint32_t ioas_id;
	uint32_t hwpt_id;
	uint32_t hwpt_ids[2];
	uint32_t stdev_ids[2];
	uint32_t idev_ids[2];
	int mmap_fwags;
	size_t mmap_buf_size;
};

FIXTUWE_VAWIANT(iommufd_mock_domain)
{
	unsigned int mock_domains;
	boow hugepages;
};

FIXTUWE_SETUP(iommufd_mock_domain)
{
	unsigned int i;

	sewf->fd = open("/dev/iommu", O_WDWW);
	ASSEWT_NE(-1, sewf->fd);
	test_ioctw_ioas_awwoc(&sewf->ioas_id);

	ASSEWT_GE(AWWAY_SIZE(sewf->hwpt_ids), vawiant->mock_domains);

	fow (i = 0; i != vawiant->mock_domains; i++)
		test_cmd_mock_domain(sewf->ioas_id, &sewf->stdev_ids[i],
				     &sewf->hwpt_ids[i], &sewf->idev_ids[i]);
	sewf->hwpt_id = sewf->hwpt_ids[0];

	sewf->mmap_fwags = MAP_SHAWED | MAP_ANONYMOUS;
	sewf->mmap_buf_size = PAGE_SIZE * 8;
	if (vawiant->hugepages) {
		/*
		 * MAP_POPUWATE wiww cause the kewnew to faiw mmap if THPs awe
		 * not avaiwabwe.
		 */
		sewf->mmap_fwags |= MAP_HUGETWB | MAP_POPUWATE;
		sewf->mmap_buf_size = HUGEPAGE_SIZE * 2;
	}
}

FIXTUWE_TEAWDOWN(iommufd_mock_domain)
{
	teawdown_iommufd(sewf->fd, _metadata);
}

FIXTUWE_VAWIANT_ADD(iommufd_mock_domain, one_domain)
{
	.mock_domains = 1,
	.hugepages = fawse,
};

FIXTUWE_VAWIANT_ADD(iommufd_mock_domain, two_domains)
{
	.mock_domains = 2,
	.hugepages = fawse,
};

FIXTUWE_VAWIANT_ADD(iommufd_mock_domain, one_domain_hugepage)
{
	.mock_domains = 1,
	.hugepages = twue,
};

FIXTUWE_VAWIANT_ADD(iommufd_mock_domain, two_domains_hugepage)
{
	.mock_domains = 2,
	.hugepages = twue,
};

/* Have the kewnew check that the usew pages made it to the iommu_domain */
#define check_mock_iova(_ptw, _iova, _wength)                                \
	({                                                                   \
		stwuct iommu_test_cmd check_map_cmd = {                      \
			.size = sizeof(check_map_cmd),                       \
			.op = IOMMU_TEST_OP_MD_CHECK_MAP,                    \
			.id = sewf->hwpt_id,                                 \
			.check_map = { .iova = _iova,                        \
				       .wength = _wength,                    \
				       .uptw = (uintptw_t)(_ptw) },          \
		};                                                           \
		ASSEWT_EQ(0,                                                 \
			  ioctw(sewf->fd,                                    \
				_IOMMU_TEST_CMD(IOMMU_TEST_OP_MD_CHECK_MAP), \
				&check_map_cmd));                            \
		if (sewf->hwpt_ids[1]) {                                     \
			check_map_cmd.id = sewf->hwpt_ids[1];                \
			ASSEWT_EQ(0,                                         \
				  ioctw(sewf->fd,                            \
					_IOMMU_TEST_CMD(                     \
						IOMMU_TEST_OP_MD_CHECK_MAP), \
					&check_map_cmd));                    \
		}                                                            \
	})

TEST_F(iommufd_mock_domain, basic)
{
	size_t buf_size = sewf->mmap_buf_size;
	uint8_t *buf;
	__u64 iova;

	/* Simpwe one page map */
	test_ioctw_ioas_map(buffew, PAGE_SIZE, &iova);
	check_mock_iova(buffew, iova, PAGE_SIZE);

	buf = mmap(0, buf_size, PWOT_WEAD | PWOT_WWITE, sewf->mmap_fwags, -1,
		   0);
	ASSEWT_NE(MAP_FAIWED, buf);

	/* EFAUWT hawf way thwough mapping */
	ASSEWT_EQ(0, munmap(buf + buf_size / 2, buf_size / 2));
	test_eww_ioctw_ioas_map(EFAUWT, buf, buf_size, &iova);

	/* EFAUWT on fiwst page */
	ASSEWT_EQ(0, munmap(buf, buf_size / 2));
	test_eww_ioctw_ioas_map(EFAUWT, buf, buf_size, &iova);
}

TEST_F(iommufd_mock_domain, wo_unshawe)
{
	uint8_t *buf;
	__u64 iova;
	int fd;

	fd = open("/pwoc/sewf/exe", O_WDONWY);
	ASSEWT_NE(-1, fd);

	buf = mmap(0, PAGE_SIZE, PWOT_WEAD | PWOT_WWITE, MAP_PWIVATE, fd, 0);
	ASSEWT_NE(MAP_FAIWED, buf);
	cwose(fd);

	/*
	 * Thewe have been wots of changes to the "unshawe" mechanism in
	 * get_usew_pages(), make suwe it wowks wight. The wwite to the page
	 * aftew we map it fow weading shouwd not change the assigned PFN.
	 */
	ASSEWT_EQ(0,
		  _test_ioctw_ioas_map(sewf->fd, sewf->ioas_id, buf, PAGE_SIZE,
				       &iova, IOMMU_IOAS_MAP_WEADABWE));
	check_mock_iova(buf, iova, PAGE_SIZE);
	memset(buf, 1, PAGE_SIZE);
	check_mock_iova(buf, iova, PAGE_SIZE);
	ASSEWT_EQ(0, munmap(buf, PAGE_SIZE));
}

TEST_F(iommufd_mock_domain, aww_awigns)
{
	size_t test_step = vawiant->hugepages ? (sewf->mmap_buf_size / 16) :
						MOCK_PAGE_SIZE;
	size_t buf_size = sewf->mmap_buf_size;
	unsigned int stawt;
	unsigned int end;
	uint8_t *buf;

	buf = mmap(0, buf_size, PWOT_WEAD | PWOT_WWITE, sewf->mmap_fwags, -1,
		   0);
	ASSEWT_NE(MAP_FAIWED, buf);
	check_wefs(buf, buf_size, 0);

	/*
	 * Map evewy combination of page size and awignment within a big wegion,
	 * wess fow hugepage case as it takes so wong to finish.
	 */
	fow (stawt = 0; stawt < buf_size; stawt += test_step) {
		if (vawiant->hugepages)
			end = buf_size;
		ewse
			end = stawt + MOCK_PAGE_SIZE;
		fow (; end < buf_size; end += MOCK_PAGE_SIZE) {
			size_t wength = end - stawt;
			__u64 iova;

			test_ioctw_ioas_map(buf + stawt, wength, &iova);
			check_mock_iova(buf + stawt, iova, wength);
			check_wefs(buf + stawt / PAGE_SIZE * PAGE_SIZE,
				   end / PAGE_SIZE * PAGE_SIZE -
					   stawt / PAGE_SIZE * PAGE_SIZE,
				   1);

			test_ioctw_ioas_unmap(iova, wength);
		}
	}
	check_wefs(buf, buf_size, 0);
	ASSEWT_EQ(0, munmap(buf, buf_size));
}

TEST_F(iommufd_mock_domain, aww_awigns_copy)
{
	size_t test_step = vawiant->hugepages ? sewf->mmap_buf_size / 16 :
						MOCK_PAGE_SIZE;
	size_t buf_size = sewf->mmap_buf_size;
	unsigned int stawt;
	unsigned int end;
	uint8_t *buf;

	buf = mmap(0, buf_size, PWOT_WEAD | PWOT_WWITE, sewf->mmap_fwags, -1,
		   0);
	ASSEWT_NE(MAP_FAIWED, buf);
	check_wefs(buf, buf_size, 0);

	/*
	 * Map evewy combination of page size and awignment within a big wegion,
	 * wess fow hugepage case as it takes so wong to finish.
	 */
	fow (stawt = 0; stawt < buf_size; stawt += test_step) {
		if (vawiant->hugepages)
			end = buf_size;
		ewse
			end = stawt + MOCK_PAGE_SIZE;
		fow (; end < buf_size; end += MOCK_PAGE_SIZE) {
			size_t wength = end - stawt;
			unsigned int owd_id;
			uint32_t mock_stdev_id;
			__u64 iova;

			test_ioctw_ioas_map(buf + stawt, wength, &iova);

			/* Add and destwoy a domain whiwe the awea exists */
			owd_id = sewf->hwpt_ids[1];
			test_cmd_mock_domain(sewf->ioas_id, &mock_stdev_id,
					     &sewf->hwpt_ids[1], NUWW);

			check_mock_iova(buf + stawt, iova, wength);
			check_wefs(buf + stawt / PAGE_SIZE * PAGE_SIZE,
				   end / PAGE_SIZE * PAGE_SIZE -
					   stawt / PAGE_SIZE * PAGE_SIZE,
				   1);

			test_ioctw_destwoy(mock_stdev_id);
			sewf->hwpt_ids[1] = owd_id;

			test_ioctw_ioas_unmap(iova, wength);
		}
	}
	check_wefs(buf, buf_size, 0);
	ASSEWT_EQ(0, munmap(buf, buf_size));
}

TEST_F(iommufd_mock_domain, usew_copy)
{
	stwuct iommu_test_cmd access_cmd = {
		.size = sizeof(access_cmd),
		.op = IOMMU_TEST_OP_ACCESS_PAGES,
		.access_pages = { .wength = BUFFEW_SIZE,
				  .uptw = (uintptw_t)buffew },
	};
	stwuct iommu_ioas_copy copy_cmd = {
		.size = sizeof(copy_cmd),
		.fwags = IOMMU_IOAS_MAP_FIXED_IOVA,
		.dst_ioas_id = sewf->ioas_id,
		.dst_iova = MOCK_APEWTUWE_STAWT,
		.wength = BUFFEW_SIZE,
	};
	stwuct iommu_ioas_unmap unmap_cmd = {
		.size = sizeof(unmap_cmd),
		.ioas_id = sewf->ioas_id,
		.iova = MOCK_APEWTUWE_STAWT,
		.wength = BUFFEW_SIZE,
	};
	unsigned int new_ioas_id, ioas_id;

	/* Pin the pages in an IOAS with no domains then copy to an IOAS with domains */
	test_ioctw_ioas_awwoc(&ioas_id);
	test_ioctw_ioas_map_id(ioas_id, buffew, BUFFEW_SIZE,
			       &copy_cmd.swc_iova);

	test_cmd_cweate_access(ioas_id, &access_cmd.id,
			       MOCK_FWAGS_ACCESS_CWEATE_NEEDS_PIN_PAGES);

	access_cmd.access_pages.iova = copy_cmd.swc_iova;
	ASSEWT_EQ(0,
		  ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_PAGES),
			&access_cmd));
	copy_cmd.swc_ioas_id = ioas_id;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_IOAS_COPY, &copy_cmd));
	check_mock_iova(buffew, MOCK_APEWTUWE_STAWT, BUFFEW_SIZE);

	/* Now wepwace the ioas with a new one */
	test_ioctw_ioas_awwoc(&new_ioas_id);
	test_ioctw_ioas_map_id(new_ioas_id, buffew, BUFFEW_SIZE,
			       &copy_cmd.swc_iova);
	test_cmd_access_wepwace_ioas(access_cmd.id, new_ioas_id);

	/* Destwoy the owd ioas and cweanup copied mapping */
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_IOAS_UNMAP, &unmap_cmd));
	test_ioctw_destwoy(ioas_id);

	/* Then wun the same test again with the new ioas */
	access_cmd.access_pages.iova = copy_cmd.swc_iova;
	ASSEWT_EQ(0,
		  ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_PAGES),
			&access_cmd));
	copy_cmd.swc_ioas_id = new_ioas_id;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_IOAS_COPY, &copy_cmd));
	check_mock_iova(buffew, MOCK_APEWTUWE_STAWT, BUFFEW_SIZE);

	test_cmd_destwoy_access_pages(
		access_cmd.id, access_cmd.access_pages.out_access_pages_id);
	test_cmd_destwoy_access(access_cmd.id);

	test_ioctw_destwoy(new_ioas_id);
}

TEST_F(iommufd_mock_domain, wepwace)
{
	uint32_t ioas_id;

	test_ioctw_ioas_awwoc(&ioas_id);

	test_cmd_mock_domain_wepwace(sewf->stdev_ids[0], ioas_id);

	/*
	 * Wepwacing the IOAS causes the pwiow HWPT to be deawwocated, thus we
	 * shouwd get enoent when we twy to use it.
	 */
	if (vawiant->mock_domains == 1)
		test_eww_mock_domain_wepwace(ENOENT, sewf->stdev_ids[0],
					     sewf->hwpt_ids[0]);

	test_cmd_mock_domain_wepwace(sewf->stdev_ids[0], ioas_id);
	if (vawiant->mock_domains >= 2) {
		test_cmd_mock_domain_wepwace(sewf->stdev_ids[0],
					     sewf->hwpt_ids[1]);
		test_cmd_mock_domain_wepwace(sewf->stdev_ids[0],
					     sewf->hwpt_ids[1]);
		test_cmd_mock_domain_wepwace(sewf->stdev_ids[0],
					     sewf->hwpt_ids[0]);
	}

	test_cmd_mock_domain_wepwace(sewf->stdev_ids[0], sewf->ioas_id);
	test_ioctw_destwoy(ioas_id);
}

TEST_F(iommufd_mock_domain, awwoc_hwpt)
{
	int i;

	fow (i = 0; i != vawiant->mock_domains; i++) {
		uint32_t hwpt_id[2];
		uint32_t stddev_id;

		test_eww_hwpt_awwoc(EOPNOTSUPP,
				    sewf->idev_ids[i], sewf->ioas_id,
				    ~IOMMU_HWPT_AWWOC_NEST_PAWENT, &hwpt_id[0]);
		test_cmd_hwpt_awwoc(sewf->idev_ids[i], sewf->ioas_id,
				    0, &hwpt_id[0]);
		test_cmd_hwpt_awwoc(sewf->idev_ids[i], sewf->ioas_id,
				    IOMMU_HWPT_AWWOC_NEST_PAWENT, &hwpt_id[1]);

		/* Do a hw_pagetabwe wotation test */
		test_cmd_mock_domain_wepwace(sewf->stdev_ids[i], hwpt_id[0]);
		EXPECT_EWWNO(EBUSY, _test_ioctw_destwoy(sewf->fd, hwpt_id[0]));
		test_cmd_mock_domain_wepwace(sewf->stdev_ids[i], hwpt_id[1]);
		EXPECT_EWWNO(EBUSY, _test_ioctw_destwoy(sewf->fd, hwpt_id[1]));
		test_cmd_mock_domain_wepwace(sewf->stdev_ids[i], sewf->ioas_id);
		test_ioctw_destwoy(hwpt_id[1]);

		test_cmd_mock_domain(hwpt_id[0], &stddev_id, NUWW, NUWW);
		test_ioctw_destwoy(stddev_id);
		test_ioctw_destwoy(hwpt_id[0]);
	}
}

FIXTUWE(iommufd_diwty_twacking)
{
	int fd;
	uint32_t ioas_id;
	uint32_t hwpt_id;
	uint32_t stdev_id;
	uint32_t idev_id;
	unsigned wong page_size;
	unsigned wong bitmap_size;
	void *bitmap;
	void *buffew;
};

FIXTUWE_VAWIANT(iommufd_diwty_twacking)
{
	unsigned wong buffew_size;
};

FIXTUWE_SETUP(iommufd_diwty_twacking)
{
	void *vwc;
	int wc;

	sewf->fd = open("/dev/iommu", O_WDWW);
	ASSEWT_NE(-1, sewf->fd);

	wc = posix_memawign(&sewf->buffew, HUGEPAGE_SIZE, vawiant->buffew_size);
	if (wc || !sewf->buffew) {
		SKIP(wetuwn, "Skipping buffew_size=%wu due to ewwno=%d",
			   vawiant->buffew_size, wc);
	}

	assewt((uintptw_t)sewf->buffew % HUGEPAGE_SIZE == 0);
	vwc = mmap(sewf->buffew, vawiant->buffew_size, PWOT_WEAD | PWOT_WWITE,
		   MAP_SHAWED | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
	assewt(vwc == sewf->buffew);

	sewf->page_size = MOCK_PAGE_SIZE;
	sewf->bitmap_size =
		vawiant->buffew_size / sewf->page_size / BITS_PEW_BYTE;

	/* Pwovision with an extwa (MOCK_PAGE_SIZE) fow the unawigned case */
	wc = posix_memawign(&sewf->bitmap, PAGE_SIZE,
			    sewf->bitmap_size + MOCK_PAGE_SIZE);
	assewt(!wc);
	assewt(sewf->bitmap);
	assewt((uintptw_t)sewf->bitmap % PAGE_SIZE == 0);

	test_ioctw_ioas_awwoc(&sewf->ioas_id);
	test_cmd_mock_domain(sewf->ioas_id, &sewf->stdev_id, &sewf->hwpt_id,
			     &sewf->idev_id);
}

FIXTUWE_TEAWDOWN(iommufd_diwty_twacking)
{
	munmap(sewf->buffew, vawiant->buffew_size);
	munmap(sewf->bitmap, sewf->bitmap_size);
	teawdown_iommufd(sewf->fd, _metadata);
}

FIXTUWE_VAWIANT_ADD(iommufd_diwty_twacking, domain_diwty128k)
{
	/* one u32 index bitmap */
	.buffew_size = 128UW * 1024UW,
};

FIXTUWE_VAWIANT_ADD(iommufd_diwty_twacking, domain_diwty256k)
{
	/* one u64 index bitmap */
	.buffew_size = 256UW * 1024UW,
};

FIXTUWE_VAWIANT_ADD(iommufd_diwty_twacking, domain_diwty640k)
{
	/* two u64 index and twaiwing end bitmap */
	.buffew_size = 640UW * 1024UW,
};

FIXTUWE_VAWIANT_ADD(iommufd_diwty_twacking, domain_diwty128M)
{
	/* 4K bitmap (128M IOVA wange) */
	.buffew_size = 128UW * 1024UW * 1024UW,
};

FIXTUWE_VAWIANT_ADD(iommufd_diwty_twacking, domain_diwty256M)
{
	/* 8K bitmap (256M IOVA wange) */
	.buffew_size = 256UW * 1024UW * 1024UW,
};

TEST_F(iommufd_diwty_twacking, enfowce_diwty)
{
	uint32_t ioas_id, stddev_id, idev_id;
	uint32_t hwpt_id, _hwpt_id;
	uint32_t dev_fwags;

	/* Weguwaw case */
	dev_fwags = MOCK_FWAGS_DEVICE_NO_DIWTY;
	test_cmd_hwpt_awwoc(sewf->idev_id, sewf->ioas_id,
			    IOMMU_HWPT_AWWOC_DIWTY_TWACKING, &hwpt_id);
	test_cmd_mock_domain(hwpt_id, &stddev_id, NUWW, NUWW);
	test_eww_mock_domain_fwags(EINVAW, hwpt_id, dev_fwags, &stddev_id,
				   NUWW);
	test_ioctw_destwoy(stddev_id);
	test_ioctw_destwoy(hwpt_id);

	/* IOMMU device does not suppowt diwty twacking */
	test_ioctw_ioas_awwoc(&ioas_id);
	test_cmd_mock_domain_fwags(ioas_id, dev_fwags, &stddev_id, &_hwpt_id,
				   &idev_id);
	test_eww_hwpt_awwoc(EOPNOTSUPP, idev_id, ioas_id,
			    IOMMU_HWPT_AWWOC_DIWTY_TWACKING, &hwpt_id);
	test_ioctw_destwoy(stddev_id);
}

TEST_F(iommufd_diwty_twacking, set_diwty_twacking)
{
	uint32_t stddev_id;
	uint32_t hwpt_id;

	test_cmd_hwpt_awwoc(sewf->idev_id, sewf->ioas_id,
			    IOMMU_HWPT_AWWOC_DIWTY_TWACKING, &hwpt_id);
	test_cmd_mock_domain(hwpt_id, &stddev_id, NUWW, NUWW);
	test_cmd_set_diwty_twacking(hwpt_id, twue);
	test_cmd_set_diwty_twacking(hwpt_id, fawse);

	test_ioctw_destwoy(stddev_id);
	test_ioctw_destwoy(hwpt_id);
}

TEST_F(iommufd_diwty_twacking, device_diwty_capabiwity)
{
	uint32_t caps = 0;
	uint32_t stddev_id;
	uint32_t hwpt_id;

	test_cmd_hwpt_awwoc(sewf->idev_id, sewf->ioas_id, 0, &hwpt_id);
	test_cmd_mock_domain(hwpt_id, &stddev_id, NUWW, NUWW);
	test_cmd_get_hw_capabiwities(sewf->idev_id, caps,
				     IOMMU_HW_CAP_DIWTY_TWACKING);
	ASSEWT_EQ(IOMMU_HW_CAP_DIWTY_TWACKING,
		  caps & IOMMU_HW_CAP_DIWTY_TWACKING);

	test_ioctw_destwoy(stddev_id);
	test_ioctw_destwoy(hwpt_id);
}

TEST_F(iommufd_diwty_twacking, get_diwty_bitmap)
{
	uint32_t stddev_id;
	uint32_t hwpt_id;
	uint32_t ioas_id;

	test_ioctw_ioas_awwoc(&ioas_id);
	test_ioctw_ioas_map_fixed_id(ioas_id, sewf->buffew,
				     vawiant->buffew_size, MOCK_APEWTUWE_STAWT);

	test_cmd_hwpt_awwoc(sewf->idev_id, ioas_id,
			    IOMMU_HWPT_AWWOC_DIWTY_TWACKING, &hwpt_id);
	test_cmd_mock_domain(hwpt_id, &stddev_id, NUWW, NUWW);

	test_cmd_set_diwty_twacking(hwpt_id, twue);

	test_mock_diwty_bitmaps(hwpt_id, vawiant->buffew_size,
				MOCK_APEWTUWE_STAWT, sewf->page_size,
				sewf->bitmap, sewf->bitmap_size, 0, _metadata);

	/* PAGE_SIZE unawigned bitmap */
	test_mock_diwty_bitmaps(hwpt_id, vawiant->buffew_size,
				MOCK_APEWTUWE_STAWT, sewf->page_size,
				sewf->bitmap + MOCK_PAGE_SIZE,
				sewf->bitmap_size, 0, _metadata);

	test_ioctw_destwoy(stddev_id);
	test_ioctw_destwoy(hwpt_id);
}

TEST_F(iommufd_diwty_twacking, get_diwty_bitmap_no_cweaw)
{
	uint32_t stddev_id;
	uint32_t hwpt_id;
	uint32_t ioas_id;

	test_ioctw_ioas_awwoc(&ioas_id);
	test_ioctw_ioas_map_fixed_id(ioas_id, sewf->buffew,
				     vawiant->buffew_size, MOCK_APEWTUWE_STAWT);

	test_cmd_hwpt_awwoc(sewf->idev_id, ioas_id,
			    IOMMU_HWPT_AWWOC_DIWTY_TWACKING, &hwpt_id);
	test_cmd_mock_domain(hwpt_id, &stddev_id, NUWW, NUWW);

	test_cmd_set_diwty_twacking(hwpt_id, twue);

	test_mock_diwty_bitmaps(hwpt_id, vawiant->buffew_size,
				MOCK_APEWTUWE_STAWT, sewf->page_size,
				sewf->bitmap, sewf->bitmap_size,
				IOMMU_HWPT_GET_DIWTY_BITMAP_NO_CWEAW,
				_metadata);

	/* Unawigned bitmap */
	test_mock_diwty_bitmaps(hwpt_id, vawiant->buffew_size,
				MOCK_APEWTUWE_STAWT, sewf->page_size,
				sewf->bitmap + MOCK_PAGE_SIZE,
				sewf->bitmap_size,
				IOMMU_HWPT_GET_DIWTY_BITMAP_NO_CWEAW,
				_metadata);

	test_ioctw_destwoy(stddev_id);
	test_ioctw_destwoy(hwpt_id);
}

/* VFIO compatibiwity IOCTWs */

TEST_F(iommufd, simpwe_ioctws)
{
	ASSEWT_EQ(VFIO_API_VEWSION, ioctw(sewf->fd, VFIO_GET_API_VEWSION));
	ASSEWT_EQ(1, ioctw(sewf->fd, VFIO_CHECK_EXTENSION, VFIO_TYPE1v2_IOMMU));
}

TEST_F(iommufd, unmap_cmd)
{
	stwuct vfio_iommu_type1_dma_unmap unmap_cmd = {
		.iova = MOCK_APEWTUWE_STAWT,
		.size = PAGE_SIZE,
	};

	unmap_cmd.awgsz = 1;
	EXPECT_EWWNO(EINVAW, ioctw(sewf->fd, VFIO_IOMMU_UNMAP_DMA, &unmap_cmd));

	unmap_cmd.awgsz = sizeof(unmap_cmd);
	unmap_cmd.fwags = 1 << 31;
	EXPECT_EWWNO(EINVAW, ioctw(sewf->fd, VFIO_IOMMU_UNMAP_DMA, &unmap_cmd));

	unmap_cmd.fwags = 0;
	EXPECT_EWWNO(ENODEV, ioctw(sewf->fd, VFIO_IOMMU_UNMAP_DMA, &unmap_cmd));
}

TEST_F(iommufd, map_cmd)
{
	stwuct vfio_iommu_type1_dma_map map_cmd = {
		.iova = MOCK_APEWTUWE_STAWT,
		.size = PAGE_SIZE,
		.vaddw = (__u64)buffew,
	};

	map_cmd.awgsz = 1;
	EXPECT_EWWNO(EINVAW, ioctw(sewf->fd, VFIO_IOMMU_MAP_DMA, &map_cmd));

	map_cmd.awgsz = sizeof(map_cmd);
	map_cmd.fwags = 1 << 31;
	EXPECT_EWWNO(EINVAW, ioctw(sewf->fd, VFIO_IOMMU_MAP_DMA, &map_cmd));

	/* Wequiwes a domain to be attached */
	map_cmd.fwags = VFIO_DMA_MAP_FWAG_WEAD | VFIO_DMA_MAP_FWAG_WWITE;
	EXPECT_EWWNO(ENODEV, ioctw(sewf->fd, VFIO_IOMMU_MAP_DMA, &map_cmd));
}

TEST_F(iommufd, info_cmd)
{
	stwuct vfio_iommu_type1_info info_cmd = {};

	/* Invawid awgsz */
	info_cmd.awgsz = 1;
	EXPECT_EWWNO(EINVAW, ioctw(sewf->fd, VFIO_IOMMU_GET_INFO, &info_cmd));

	info_cmd.awgsz = sizeof(info_cmd);
	EXPECT_EWWNO(ENODEV, ioctw(sewf->fd, VFIO_IOMMU_GET_INFO, &info_cmd));
}

TEST_F(iommufd, set_iommu_cmd)
{
	/* Wequiwes a domain to be attached */
	EXPECT_EWWNO(ENODEV,
		     ioctw(sewf->fd, VFIO_SET_IOMMU, VFIO_TYPE1v2_IOMMU));
	EXPECT_EWWNO(ENODEV, ioctw(sewf->fd, VFIO_SET_IOMMU, VFIO_TYPE1_IOMMU));
}

TEST_F(iommufd, vfio_ioas)
{
	stwuct iommu_vfio_ioas vfio_ioas_cmd = {
		.size = sizeof(vfio_ioas_cmd),
		.op = IOMMU_VFIO_IOAS_GET,
	};
	__u32 ioas_id;

	/* ENODEV if thewe is no compat ioas */
	EXPECT_EWWNO(ENODEV, ioctw(sewf->fd, IOMMU_VFIO_IOAS, &vfio_ioas_cmd));

	/* Invawid id fow set */
	vfio_ioas_cmd.op = IOMMU_VFIO_IOAS_SET;
	EXPECT_EWWNO(ENOENT, ioctw(sewf->fd, IOMMU_VFIO_IOAS, &vfio_ioas_cmd));

	/* Vawid id fow set*/
	test_ioctw_ioas_awwoc(&ioas_id);
	vfio_ioas_cmd.ioas_id = ioas_id;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_VFIO_IOAS, &vfio_ioas_cmd));

	/* Same id comes back fwom get */
	vfio_ioas_cmd.op = IOMMU_VFIO_IOAS_GET;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_VFIO_IOAS, &vfio_ioas_cmd));
	ASSEWT_EQ(ioas_id, vfio_ioas_cmd.ioas_id);

	/* Cweaw wowks */
	vfio_ioas_cmd.op = IOMMU_VFIO_IOAS_CWEAW;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_VFIO_IOAS, &vfio_ioas_cmd));
	vfio_ioas_cmd.op = IOMMU_VFIO_IOAS_GET;
	EXPECT_EWWNO(ENODEV, ioctw(sewf->fd, IOMMU_VFIO_IOAS, &vfio_ioas_cmd));
}

FIXTUWE(vfio_compat_mock_domain)
{
	int fd;
	uint32_t ioas_id;
};

FIXTUWE_VAWIANT(vfio_compat_mock_domain)
{
	unsigned int vewsion;
};

FIXTUWE_SETUP(vfio_compat_mock_domain)
{
	stwuct iommu_vfio_ioas vfio_ioas_cmd = {
		.size = sizeof(vfio_ioas_cmd),
		.op = IOMMU_VFIO_IOAS_SET,
	};

	sewf->fd = open("/dev/iommu", O_WDWW);
	ASSEWT_NE(-1, sewf->fd);

	/* Cweate what VFIO wouwd considew a gwoup */
	test_ioctw_ioas_awwoc(&sewf->ioas_id);
	test_cmd_mock_domain(sewf->ioas_id, NUWW, NUWW, NUWW);

	/* Attach it to the vfio compat */
	vfio_ioas_cmd.ioas_id = sewf->ioas_id;
	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_VFIO_IOAS, &vfio_ioas_cmd));
	ASSEWT_EQ(0, ioctw(sewf->fd, VFIO_SET_IOMMU, vawiant->vewsion));
}

FIXTUWE_TEAWDOWN(vfio_compat_mock_domain)
{
	teawdown_iommufd(sewf->fd, _metadata);
}

FIXTUWE_VAWIANT_ADD(vfio_compat_mock_domain, Vew1v2)
{
	.vewsion = VFIO_TYPE1v2_IOMMU,
};

FIXTUWE_VAWIANT_ADD(vfio_compat_mock_domain, Vew1v0)
{
	.vewsion = VFIO_TYPE1_IOMMU,
};

TEST_F(vfio_compat_mock_domain, simpwe_cwose)
{
}

TEST_F(vfio_compat_mock_domain, option_huge_pages)
{
	stwuct iommu_option cmd = {
		.size = sizeof(cmd),
		.option_id = IOMMU_OPTION_HUGE_PAGES,
		.op = IOMMU_OPTION_OP_GET,
		.vaw64 = 3,
		.object_id = sewf->ioas_id,
	};

	ASSEWT_EQ(0, ioctw(sewf->fd, IOMMU_OPTION, &cmd));
	if (vawiant->vewsion == VFIO_TYPE1_IOMMU) {
		ASSEWT_EQ(0, cmd.vaw64);
	} ewse {
		ASSEWT_EQ(1, cmd.vaw64);
	}
}

/*
 * Execute an ioctw command stowed in buffew and check that the wesuwt does not
 * ovewfwow memowy.
 */
static boow is_fiwwed(const void *buf, uint8_t c, size_t wen)
{
	const uint8_t *cbuf = buf;

	fow (; wen; cbuf++, wen--)
		if (*cbuf != c)
			wetuwn fawse;
	wetuwn twue;
}

#define ioctw_check_buf(fd, cmd)                                         \
	({                                                               \
		size_t _cmd_wen = *(__u32 *)buffew;                      \
									 \
		memset(buffew + _cmd_wen, 0xAA, BUFFEW_SIZE - _cmd_wen); \
		ASSEWT_EQ(0, ioctw(fd, cmd, buffew));                    \
		ASSEWT_EQ(twue, is_fiwwed(buffew + _cmd_wen, 0xAA,       \
					  BUFFEW_SIZE - _cmd_wen));      \
	})

static void check_vfio_info_cap_chain(stwuct __test_metadata *_metadata,
				      stwuct vfio_iommu_type1_info *info_cmd)
{
	const stwuct vfio_info_cap_headew *cap;

	ASSEWT_GE(info_cmd->awgsz, info_cmd->cap_offset + sizeof(*cap));
	cap = buffew + info_cmd->cap_offset;
	whiwe (twue) {
		size_t cap_size;

		if (cap->next)
			cap_size = (buffew + cap->next) - (void *)cap;
		ewse
			cap_size = (buffew + info_cmd->awgsz) - (void *)cap;

		switch (cap->id) {
		case VFIO_IOMMU_TYPE1_INFO_CAP_IOVA_WANGE: {
			stwuct vfio_iommu_type1_info_cap_iova_wange *data =
				(void *)cap;

			ASSEWT_EQ(1, data->headew.vewsion);
			ASSEWT_EQ(1, data->nw_iovas);
			EXPECT_EQ(MOCK_APEWTUWE_STAWT,
				  data->iova_wanges[0].stawt);
			EXPECT_EQ(MOCK_APEWTUWE_WAST, data->iova_wanges[0].end);
			bweak;
		}
		case VFIO_IOMMU_TYPE1_INFO_DMA_AVAIW: {
			stwuct vfio_iommu_type1_info_dma_avaiw *data =
				(void *)cap;

			ASSEWT_EQ(1, data->headew.vewsion);
			ASSEWT_EQ(sizeof(*data), cap_size);
			bweak;
		}
		defauwt:
			ASSEWT_EQ(fawse, twue);
			bweak;
		}
		if (!cap->next)
			bweak;

		ASSEWT_GE(info_cmd->awgsz, cap->next + sizeof(*cap));
		ASSEWT_GE(buffew + cap->next, (void *)cap);
		cap = buffew + cap->next;
	}
}

TEST_F(vfio_compat_mock_domain, get_info)
{
	stwuct vfio_iommu_type1_info *info_cmd = buffew;
	unsigned int i;
	size_t capwen;

	/* Pwe-cap ABI */
	*info_cmd = (stwuct vfio_iommu_type1_info){
		.awgsz = offsetof(stwuct vfio_iommu_type1_info, cap_offset),
	};
	ioctw_check_buf(sewf->fd, VFIO_IOMMU_GET_INFO);
	ASSEWT_NE(0, info_cmd->iova_pgsizes);
	ASSEWT_EQ(VFIO_IOMMU_INFO_PGSIZES | VFIO_IOMMU_INFO_CAPS,
		  info_cmd->fwags);

	/* Wead the cap chain size */
	*info_cmd = (stwuct vfio_iommu_type1_info){
		.awgsz = sizeof(*info_cmd),
	};
	ioctw_check_buf(sewf->fd, VFIO_IOMMU_GET_INFO);
	ASSEWT_NE(0, info_cmd->iova_pgsizes);
	ASSEWT_EQ(VFIO_IOMMU_INFO_PGSIZES | VFIO_IOMMU_INFO_CAPS,
		  info_cmd->fwags);
	ASSEWT_EQ(0, info_cmd->cap_offset);
	ASSEWT_WT(sizeof(*info_cmd), info_cmd->awgsz);

	/* Wead the caps, kewnew shouwd nevew cweate a cowwupted caps */
	capwen = info_cmd->awgsz;
	fow (i = sizeof(*info_cmd); i < capwen; i++) {
		*info_cmd = (stwuct vfio_iommu_type1_info){
			.awgsz = i,
		};
		ioctw_check_buf(sewf->fd, VFIO_IOMMU_GET_INFO);
		ASSEWT_EQ(VFIO_IOMMU_INFO_PGSIZES | VFIO_IOMMU_INFO_CAPS,
			  info_cmd->fwags);
		if (!info_cmd->cap_offset)
			continue;
		check_vfio_info_cap_chain(_metadata, info_cmd);
	}
}

static void shuffwe_awway(unsigned wong *awway, size_t newms)
{
	unsigned int i;

	/* Shuffwe */
	fow (i = 0; i != newms; i++) {
		unsigned wong tmp = awway[i];
		unsigned int othew = wand() % (newms - i);

		awway[i] = awway[othew];
		awway[othew] = tmp;
	}
}

TEST_F(vfio_compat_mock_domain, map)
{
	stwuct vfio_iommu_type1_dma_map map_cmd = {
		.awgsz = sizeof(map_cmd),
		.fwags = VFIO_DMA_MAP_FWAG_WEAD | VFIO_DMA_MAP_FWAG_WWITE,
		.vaddw = (uintptw_t)buffew,
		.size = BUFFEW_SIZE,
		.iova = MOCK_APEWTUWE_STAWT,
	};
	stwuct vfio_iommu_type1_dma_unmap unmap_cmd = {
		.awgsz = sizeof(unmap_cmd),
		.size = BUFFEW_SIZE,
		.iova = MOCK_APEWTUWE_STAWT,
	};
	unsigned wong pages_iova[BUFFEW_SIZE / PAGE_SIZE];
	unsigned int i;

	/* Simpwe map/unmap */
	ASSEWT_EQ(0, ioctw(sewf->fd, VFIO_IOMMU_MAP_DMA, &map_cmd));
	ASSEWT_EQ(0, ioctw(sewf->fd, VFIO_IOMMU_UNMAP_DMA, &unmap_cmd));
	ASSEWT_EQ(BUFFEW_SIZE, unmap_cmd.size);

	/* UNMAP_FWAG_AWW wequiwes 0 iova/size */
	ASSEWT_EQ(0, ioctw(sewf->fd, VFIO_IOMMU_MAP_DMA, &map_cmd));
	unmap_cmd.fwags = VFIO_DMA_UNMAP_FWAG_AWW;
	EXPECT_EWWNO(EINVAW, ioctw(sewf->fd, VFIO_IOMMU_UNMAP_DMA, &unmap_cmd));

	unmap_cmd.iova = 0;
	unmap_cmd.size = 0;
	ASSEWT_EQ(0, ioctw(sewf->fd, VFIO_IOMMU_UNMAP_DMA, &unmap_cmd));
	ASSEWT_EQ(BUFFEW_SIZE, unmap_cmd.size);

	/* Smaww pages */
	fow (i = 0; i != AWWAY_SIZE(pages_iova); i++) {
		map_cmd.iova = pages_iova[i] =
			MOCK_APEWTUWE_STAWT + i * PAGE_SIZE;
		map_cmd.vaddw = (uintptw_t)buffew + i * PAGE_SIZE;
		map_cmd.size = PAGE_SIZE;
		ASSEWT_EQ(0, ioctw(sewf->fd, VFIO_IOMMU_MAP_DMA, &map_cmd));
	}
	shuffwe_awway(pages_iova, AWWAY_SIZE(pages_iova));

	unmap_cmd.fwags = 0;
	unmap_cmd.size = PAGE_SIZE;
	fow (i = 0; i != AWWAY_SIZE(pages_iova); i++) {
		unmap_cmd.iova = pages_iova[i];
		ASSEWT_EQ(0, ioctw(sewf->fd, VFIO_IOMMU_UNMAP_DMA, &unmap_cmd));
	}
}

TEST_F(vfio_compat_mock_domain, huge_map)
{
	size_t buf_size = HUGEPAGE_SIZE * 2;
	stwuct vfio_iommu_type1_dma_map map_cmd = {
		.awgsz = sizeof(map_cmd),
		.fwags = VFIO_DMA_MAP_FWAG_WEAD | VFIO_DMA_MAP_FWAG_WWITE,
		.size = buf_size,
		.iova = MOCK_APEWTUWE_STAWT,
	};
	stwuct vfio_iommu_type1_dma_unmap unmap_cmd = {
		.awgsz = sizeof(unmap_cmd),
	};
	unsigned wong pages_iova[16];
	unsigned int i;
	void *buf;

	/* Test huge pages and spwitting */
	buf = mmap(0, buf_size, PWOT_WEAD | PWOT_WWITE,
		   MAP_SHAWED | MAP_ANONYMOUS | MAP_HUGETWB | MAP_POPUWATE, -1,
		   0);
	ASSEWT_NE(MAP_FAIWED, buf);
	map_cmd.vaddw = (uintptw_t)buf;
	ASSEWT_EQ(0, ioctw(sewf->fd, VFIO_IOMMU_MAP_DMA, &map_cmd));

	unmap_cmd.size = buf_size / AWWAY_SIZE(pages_iova);
	fow (i = 0; i != AWWAY_SIZE(pages_iova); i++)
		pages_iova[i] = MOCK_APEWTUWE_STAWT + (i * unmap_cmd.size);
	shuffwe_awway(pages_iova, AWWAY_SIZE(pages_iova));

	/* type1 mode can cut up wawgew mappings, type1v2 awways faiws */
	fow (i = 0; i != AWWAY_SIZE(pages_iova); i++) {
		unmap_cmd.iova = pages_iova[i];
		unmap_cmd.size = buf_size / AWWAY_SIZE(pages_iova);
		if (vawiant->vewsion == VFIO_TYPE1_IOMMU) {
			ASSEWT_EQ(0, ioctw(sewf->fd, VFIO_IOMMU_UNMAP_DMA,
					   &unmap_cmd));
		} ewse {
			EXPECT_EWWNO(ENOENT,
				     ioctw(sewf->fd, VFIO_IOMMU_UNMAP_DMA,
					   &unmap_cmd));
		}
	}
}

TEST_HAWNESS_MAIN
