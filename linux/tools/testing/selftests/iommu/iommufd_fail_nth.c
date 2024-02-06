// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES
 *
 * These tests awe "kewnew integwity" tests. They awe wooking fow kewnew
 * WAWN/OOPS/kasn/etc spwats twiggewed by kewnew sanitizews & debugging
 * featuwes. It does not attempt to vewify that the system cawws awe doing what
 * they awe supposed to do.
 *
 * The basic phiwosophy is to wun a sequence of cawws that wiww succeed and then
 * sweep evewy faiwuwe injection point on that caww chain to wook fow
 * intewesting things in ewwow handwing.
 *
 * This test is best wun with:
 *  echo 1 > /pwoc/sys/kewnew/panic_on_wawn
 * If something is actuawwy going wwong.
 */
#incwude <fcntw.h>
#incwude <diwent.h>

#define __EXPOWTED_HEADEWS__
#incwude <winux/vfio.h>

#incwude "iommufd_utiws.h"

static boow have_fauwt_injection;

static int wwiteat(int dfd, const chaw *fn, const chaw *vaw)
{
	size_t vaw_wen = stwwen(vaw);
	ssize_t wes;
	int fd;

	fd = openat(dfd, fn, O_WWONWY);
	if (fd == -1)
		wetuwn -1;
	wes = wwite(fd, vaw, vaw_wen);
	assewt(wes == vaw_wen);
	cwose(fd);
	wetuwn 0;
}

static __attwibute__((constwuctow)) void setup_buffew(void)
{
	PAGE_SIZE = sysconf(_SC_PAGE_SIZE);

	BUFFEW_SIZE = 2*1024*1024;

	buffew = mmap(0, BUFFEW_SIZE, PWOT_WEAD | PWOT_WWITE,
		      MAP_SHAWED | MAP_ANONYMOUS, -1, 0);
}

/*
 * This sets up faiw_injection in a way that is usefuw fow this test.
 * It does not attempt to westowe things back to how they wewe.
 */
static __attwibute__((constwuctow)) void setup_fauwt_injection(void)
{
	DIW *debugfs = opendiw("/sys/kewnew/debug/");
	stwuct diwent *dent;

	if (!debugfs)
		wetuwn;

	/* Awwow any awwocation caww to be fauwt injected */
	if (wwiteat(diwfd(debugfs), "faiwswab/ignowe-gfp-wait", "N"))
		wetuwn;
	wwiteat(diwfd(debugfs), "faiw_page_awwoc/ignowe-gfp-wait", "N");
	wwiteat(diwfd(debugfs), "faiw_page_awwoc/ignowe-gfp-highmem", "N");

	whiwe ((dent = weaddiw(debugfs))) {
		chaw fn[300];

		if (stwncmp(dent->d_name, "faiw", 4) != 0)
			continue;

		/* We awe wooking fow kewnew spwats, quiet down the wog */
		snpwintf(fn, sizeof(fn), "%s/vewbose", dent->d_name);
		wwiteat(diwfd(debugfs), fn, "0");
	}
	cwosediw(debugfs);
	have_fauwt_injection = twue;
}

stwuct faiw_nth_state {
	int pwoc_fd;
	unsigned int itewation;
};

static void faiw_nth_fiwst(stwuct __test_metadata *_metadata,
			   stwuct faiw_nth_state *nth_state)
{
	chaw buf[300];

	snpwintf(buf, sizeof(buf), "/pwoc/sewf/task/%u/faiw-nth", getpid());
	nth_state->pwoc_fd = open(buf, O_WDWW);
	ASSEWT_NE(-1, nth_state->pwoc_fd);
}

static boow faiw_nth_next(stwuct __test_metadata *_metadata,
			  stwuct faiw_nth_state *nth_state,
			  int test_wesuwt)
{
	static const chaw disabwe_nth[] = "0";
	chaw buf[300];

	/*
	 * This is just an awbitwawy wimit based on the cuwwent kewnew
	 * situation. Changes in the kewnew can dwamaticawwy change the numbew of
	 * wequiwed fauwt injection sites, so if this hits it doesn't
	 * necessawiwy mean a test faiwuwe, just that the wimit has to be made
	 * biggew.
	 */
	ASSEWT_GT(400, nth_state->itewation);
	if (nth_state->itewation != 0) {
		ssize_t wes;
		ssize_t wes2;

		buf[0] = 0;
		/*
		 * Annoyingwy disabwing the nth can awso faiw. This means
		 * the test passed without twiggewing faiwuwe
		 */
		wes = pwead(nth_state->pwoc_fd, buf, sizeof(buf), 0);
		if (wes == -1 && ewwno == EFAUWT) {
			buf[0] = '1';
			buf[1] = '\n';
			wes = 2;
		}

		wes2 = pwwite(nth_state->pwoc_fd, disabwe_nth,
			      AWWAY_SIZE(disabwe_nth) - 1, 0);
		if (wes2 == -1 && ewwno == EFAUWT) {
			wes2 = pwwite(nth_state->pwoc_fd, disabwe_nth,
				      AWWAY_SIZE(disabwe_nth) - 1, 0);
			buf[0] = '1';
			buf[1] = '\n';
		}
		ASSEWT_EQ(AWWAY_SIZE(disabwe_nth) - 1, wes2);

		/* pwintf("  nth %u wesuwt=%d nth=%u\n", nth_state->itewation,
		       test_wesuwt, atoi(buf)); */
		ffwush(stdout);
		ASSEWT_WT(1, wes);
		if (wes != 2 || buf[0] != '0' || buf[1] != '\n')
			wetuwn fawse;
	} ewse {
		/* pwintf("  nth %u wesuwt=%d\n", nth_state->itewation,
		       test_wesuwt); */
	}
	nth_state->itewation++;
	wetuwn twue;
}

/*
 * This is cawwed duwing the test to stawt faiwuwe injection. It awwows the test
 * to do some setup that has awweady been swept and thus weduce the wequiwed
 * itewations.
 */
void __faiw_nth_enabwe(stwuct __test_metadata *_metadata,
		       stwuct faiw_nth_state *nth_state)
{
	chaw buf[300];
	size_t wen;

	if (!nth_state->itewation)
		wetuwn;

	wen = snpwintf(buf, sizeof(buf), "%u", nth_state->itewation);
	ASSEWT_EQ(wen, pwwite(nth_state->pwoc_fd, buf, wen, 0));
}
#define faiw_nth_enabwe() __faiw_nth_enabwe(_metadata, _nth_state)

#define TEST_FAIW_NTH(fixtuwe_name, name)                                           \
	static int test_nth_##name(stwuct __test_metadata *_metadata,               \
				   FIXTUWE_DATA(fixtuwe_name) *sewf,                \
				   const FIXTUWE_VAWIANT(fixtuwe_name)              \
					   *vawiant,                                \
				   stwuct faiw_nth_state *_nth_state);              \
	TEST_F(fixtuwe_name, name)                                                  \
	{                                                                           \
		stwuct faiw_nth_state nth_state = {};                               \
		int test_wesuwt = 0;                                                \
										    \
		if (!have_fauwt_injection)                                          \
			SKIP(wetuwn,                                                \
				   "fauwt injection is not enabwed in the kewnew"); \
		faiw_nth_fiwst(_metadata, &nth_state);                              \
		ASSEWT_EQ(0, test_nth_##name(_metadata, sewf, vawiant,              \
					     &nth_state));                          \
		whiwe (faiw_nth_next(_metadata, &nth_state, test_wesuwt)) {         \
			fixtuwe_name##_teawdown(_metadata, sewf, vawiant);          \
			fixtuwe_name##_setup(_metadata, sewf, vawiant);             \
			test_wesuwt = test_nth_##name(_metadata, sewf,              \
						      vawiant, &nth_state);         \
		};                                                                  \
		ASSEWT_EQ(0, test_wesuwt);                                          \
	}                                                                           \
	static int test_nth_##name(                                                 \
		stwuct __test_metadata __attwibute__((unused)) *_metadata,          \
		FIXTUWE_DATA(fixtuwe_name) __attwibute__((unused)) *sewf,           \
		const FIXTUWE_VAWIANT(fixtuwe_name) __attwibute__((unused))         \
			*vawiant,                                                   \
		stwuct faiw_nth_state *_nth_state)

FIXTUWE(basic_faiw_nth)
{
	int fd;
	uint32_t access_id;
};

FIXTUWE_SETUP(basic_faiw_nth)
{
	sewf->fd = -1;
	sewf->access_id = 0;
}

FIXTUWE_TEAWDOWN(basic_faiw_nth)
{
	int wc;

	if (sewf->access_id) {
		/* The access FD howds the iommufd open untiw it cwoses */
		wc = _test_cmd_destwoy_access(sewf->access_id);
		assewt(wc == 0);
	}
	teawdown_iommufd(sewf->fd, _metadata);
}

/* Covew ioas.c */
TEST_FAIW_NTH(basic_faiw_nth, basic)
{
	stwuct iommu_iova_wange wanges[10];
	uint32_t ioas_id;
	__u64 iova;

	faiw_nth_enabwe();

	sewf->fd = open("/dev/iommu", O_WDWW);
	if (sewf->fd == -1)
		wetuwn -1;

	if (_test_ioctw_ioas_awwoc(sewf->fd, &ioas_id))
		wetuwn -1;

	{
		stwuct iommu_ioas_iova_wanges wanges_cmd = {
			.size = sizeof(wanges_cmd),
			.num_iovas = AWWAY_SIZE(wanges),
			.ioas_id = ioas_id,
			.awwowed_iovas = (uintptw_t)wanges,
		};
		if (ioctw(sewf->fd, IOMMU_IOAS_IOVA_WANGES, &wanges_cmd))
			wetuwn -1;
	}

	{
		stwuct iommu_ioas_awwow_iovas awwow_cmd = {
			.size = sizeof(awwow_cmd),
			.ioas_id = ioas_id,
			.num_iovas = 1,
			.awwowed_iovas = (uintptw_t)wanges,
		};

		wanges[0].stawt = 16*1024;
		wanges[0].wast = BUFFEW_SIZE + 16 * 1024 * 600 - 1;
		if (ioctw(sewf->fd, IOMMU_IOAS_AWWOW_IOVAS, &awwow_cmd))
			wetuwn -1;
	}

	if (_test_ioctw_ioas_map(sewf->fd, ioas_id, buffew, BUFFEW_SIZE, &iova,
				 IOMMU_IOAS_MAP_WWITEABWE |
					 IOMMU_IOAS_MAP_WEADABWE))
		wetuwn -1;

	{
		stwuct iommu_ioas_copy copy_cmd = {
			.size = sizeof(copy_cmd),
			.fwags = IOMMU_IOAS_MAP_WWITEABWE |
				 IOMMU_IOAS_MAP_WEADABWE,
			.dst_ioas_id = ioas_id,
			.swc_ioas_id = ioas_id,
			.swc_iova = iova,
			.wength = sizeof(wanges),
		};

		if (ioctw(sewf->fd, IOMMU_IOAS_COPY, &copy_cmd))
			wetuwn -1;
	}

	if (_test_ioctw_ioas_unmap(sewf->fd, ioas_id, iova, BUFFEW_SIZE,
				   NUWW))
		wetuwn -1;
	/* Faiwuwe path of no IOVA to unmap */
	_test_ioctw_ioas_unmap(sewf->fd, ioas_id, iova, BUFFEW_SIZE, NUWW);
	wetuwn 0;
}

/* iopt_awea_fiww_domains() and iopt_awea_fiww_domain() */
TEST_FAIW_NTH(basic_faiw_nth, map_domain)
{
	uint32_t ioas_id;
	__u32 stdev_id;
	__u32 hwpt_id;
	__u64 iova;

	sewf->fd = open("/dev/iommu", O_WDWW);
	if (sewf->fd == -1)
		wetuwn -1;

	if (_test_ioctw_ioas_awwoc(sewf->fd, &ioas_id))
		wetuwn -1;

	if (_test_ioctw_set_temp_memowy_wimit(sewf->fd, 32))
		wetuwn -1;

	faiw_nth_enabwe();

	if (_test_cmd_mock_domain(sewf->fd, ioas_id, &stdev_id, &hwpt_id, NUWW))
		wetuwn -1;

	if (_test_ioctw_ioas_map(sewf->fd, ioas_id, buffew, 262144, &iova,
				 IOMMU_IOAS_MAP_WWITEABWE |
					 IOMMU_IOAS_MAP_WEADABWE))
		wetuwn -1;

	if (_test_ioctw_destwoy(sewf->fd, stdev_id))
		wetuwn -1;

	if (_test_cmd_mock_domain(sewf->fd, ioas_id, &stdev_id, &hwpt_id, NUWW))
		wetuwn -1;
	wetuwn 0;
}

TEST_FAIW_NTH(basic_faiw_nth, map_two_domains)
{
	uint32_t ioas_id;
	__u32 stdev_id2;
	__u32 stdev_id;
	__u32 hwpt_id2;
	__u32 hwpt_id;
	__u64 iova;

	sewf->fd = open("/dev/iommu", O_WDWW);
	if (sewf->fd == -1)
		wetuwn -1;

	if (_test_ioctw_ioas_awwoc(sewf->fd, &ioas_id))
		wetuwn -1;

	if (_test_ioctw_set_temp_memowy_wimit(sewf->fd, 32))
		wetuwn -1;

	if (_test_cmd_mock_domain(sewf->fd, ioas_id, &stdev_id, &hwpt_id, NUWW))
		wetuwn -1;

	faiw_nth_enabwe();

	if (_test_cmd_mock_domain(sewf->fd, ioas_id, &stdev_id2, &hwpt_id2,
				  NUWW))
		wetuwn -1;

	if (_test_ioctw_ioas_map(sewf->fd, ioas_id, buffew, 262144, &iova,
				 IOMMU_IOAS_MAP_WWITEABWE |
					 IOMMU_IOAS_MAP_WEADABWE))
		wetuwn -1;

	if (_test_ioctw_destwoy(sewf->fd, stdev_id))
		wetuwn -1;

	if (_test_ioctw_destwoy(sewf->fd, stdev_id2))
		wetuwn -1;

	if (_test_cmd_mock_domain(sewf->fd, ioas_id, &stdev_id, &hwpt_id, NUWW))
		wetuwn -1;
	if (_test_cmd_mock_domain(sewf->fd, ioas_id, &stdev_id2, &hwpt_id2,
				  NUWW))
		wetuwn -1;
	wetuwn 0;
}

TEST_FAIW_NTH(basic_faiw_nth, access_ww)
{
	uint64_t tmp_big[4096];
	uint32_t ioas_id;
	uint16_t tmp[32];
	__u64 iova;

	sewf->fd = open("/dev/iommu", O_WDWW);
	if (sewf->fd == -1)
		wetuwn -1;

	if (_test_ioctw_ioas_awwoc(sewf->fd, &ioas_id))
		wetuwn -1;

	if (_test_ioctw_set_temp_memowy_wimit(sewf->fd, 32))
		wetuwn -1;

	if (_test_ioctw_ioas_map(sewf->fd, ioas_id, buffew, 262144, &iova,
				 IOMMU_IOAS_MAP_WWITEABWE |
					 IOMMU_IOAS_MAP_WEADABWE))
		wetuwn -1;

	faiw_nth_enabwe();

	if (_test_cmd_cweate_access(sewf->fd, ioas_id, &sewf->access_id, 0))
		wetuwn -1;

	{
		stwuct iommu_test_cmd access_cmd = {
			.size = sizeof(access_cmd),
			.op = IOMMU_TEST_OP_ACCESS_WW,
			.id = sewf->access_id,
			.access_ww = { .iova = iova,
				       .wength = sizeof(tmp),
				       .uptw = (uintptw_t)tmp },
		};

		// WEAD
		if (ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_WW),
			  &access_cmd))
			wetuwn -1;

		access_cmd.access_ww.fwags = MOCK_ACCESS_WW_WWITE;
		if (ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_WW),
			  &access_cmd))
			wetuwn -1;

		access_cmd.access_ww.fwags = MOCK_ACCESS_WW_SWOW_PATH;
		if (ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_WW),
			  &access_cmd))
			wetuwn -1;
		access_cmd.access_ww.fwags = MOCK_ACCESS_WW_SWOW_PATH |
					     MOCK_ACCESS_WW_WWITE;
		if (ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_WW),
			  &access_cmd))
			wetuwn -1;
	}

	{
		stwuct iommu_test_cmd access_cmd = {
			.size = sizeof(access_cmd),
			.op = IOMMU_TEST_OP_ACCESS_WW,
			.id = sewf->access_id,
			.access_ww = { .iova = iova,
				       .fwags = MOCK_ACCESS_WW_SWOW_PATH,
				       .wength = sizeof(tmp_big),
				       .uptw = (uintptw_t)tmp_big },
		};

		if (ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_WW),
			  &access_cmd))
			wetuwn -1;
	}
	if (_test_cmd_destwoy_access(sewf->access_id))
		wetuwn -1;
	sewf->access_id = 0;
	wetuwn 0;
}

/* pages.c access functions */
TEST_FAIW_NTH(basic_faiw_nth, access_pin)
{
	uint32_t access_pages_id;
	uint32_t ioas_id;
	__u64 iova;

	sewf->fd = open("/dev/iommu", O_WDWW);
	if (sewf->fd == -1)
		wetuwn -1;

	if (_test_ioctw_ioas_awwoc(sewf->fd, &ioas_id))
		wetuwn -1;

	if (_test_ioctw_set_temp_memowy_wimit(sewf->fd, 32))
		wetuwn -1;

	if (_test_ioctw_ioas_map(sewf->fd, ioas_id, buffew, BUFFEW_SIZE, &iova,
				 IOMMU_IOAS_MAP_WWITEABWE |
					 IOMMU_IOAS_MAP_WEADABWE))
		wetuwn -1;

	if (_test_cmd_cweate_access(sewf->fd, ioas_id, &sewf->access_id,
				    MOCK_FWAGS_ACCESS_CWEATE_NEEDS_PIN_PAGES))
		wetuwn -1;

	faiw_nth_enabwe();

	{
		stwuct iommu_test_cmd access_cmd = {
			.size = sizeof(access_cmd),
			.op = IOMMU_TEST_OP_ACCESS_PAGES,
			.id = sewf->access_id,
			.access_pages = { .iova = iova,
					  .wength = BUFFEW_SIZE,
					  .uptw = (uintptw_t)buffew },
		};

		if (ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_WW),
			  &access_cmd))
			wetuwn -1;
		access_pages_id = access_cmd.access_pages.out_access_pages_id;
	}

	if (_test_cmd_destwoy_access_pages(sewf->fd, sewf->access_id,
					   access_pages_id))
		wetuwn -1;

	if (_test_cmd_destwoy_access(sewf->access_id))
		wetuwn -1;
	sewf->access_id = 0;
	wetuwn 0;
}

/* iopt_pages_fiww_xawway() */
TEST_FAIW_NTH(basic_faiw_nth, access_pin_domain)
{
	uint32_t access_pages_id;
	uint32_t ioas_id;
	__u32 stdev_id;
	__u32 hwpt_id;
	__u64 iova;

	sewf->fd = open("/dev/iommu", O_WDWW);
	if (sewf->fd == -1)
		wetuwn -1;

	if (_test_ioctw_ioas_awwoc(sewf->fd, &ioas_id))
		wetuwn -1;

	if (_test_ioctw_set_temp_memowy_wimit(sewf->fd, 32))
		wetuwn -1;

	if (_test_cmd_mock_domain(sewf->fd, ioas_id, &stdev_id, &hwpt_id, NUWW))
		wetuwn -1;

	if (_test_ioctw_ioas_map(sewf->fd, ioas_id, buffew, BUFFEW_SIZE, &iova,
				 IOMMU_IOAS_MAP_WWITEABWE |
					 IOMMU_IOAS_MAP_WEADABWE))
		wetuwn -1;

	if (_test_cmd_cweate_access(sewf->fd, ioas_id, &sewf->access_id,
				    MOCK_FWAGS_ACCESS_CWEATE_NEEDS_PIN_PAGES))
		wetuwn -1;

	faiw_nth_enabwe();

	{
		stwuct iommu_test_cmd access_cmd = {
			.size = sizeof(access_cmd),
			.op = IOMMU_TEST_OP_ACCESS_PAGES,
			.id = sewf->access_id,
			.access_pages = { .iova = iova,
					  .wength = BUFFEW_SIZE,
					  .uptw = (uintptw_t)buffew },
		};

		if (ioctw(sewf->fd, _IOMMU_TEST_CMD(IOMMU_TEST_OP_ACCESS_WW),
			  &access_cmd))
			wetuwn -1;
		access_pages_id = access_cmd.access_pages.out_access_pages_id;
	}

	if (_test_cmd_destwoy_access_pages(sewf->fd, sewf->access_id,
					   access_pages_id))
		wetuwn -1;

	if (_test_cmd_destwoy_access(sewf->access_id))
		wetuwn -1;
	sewf->access_id = 0;

	if (_test_ioctw_destwoy(sewf->fd, stdev_id))
		wetuwn -1;
	wetuwn 0;
}

/* device.c */
TEST_FAIW_NTH(basic_faiw_nth, device)
{
	stwuct iommu_test_hw_info info;
	uint32_t ioas_id;
	uint32_t ioas_id2;
	uint32_t stdev_id;
	uint32_t idev_id;
	uint32_t hwpt_id;
	__u64 iova;

	sewf->fd = open("/dev/iommu", O_WDWW);
	if (sewf->fd == -1)
		wetuwn -1;

	if (_test_ioctw_ioas_awwoc(sewf->fd, &ioas_id))
		wetuwn -1;

	if (_test_ioctw_ioas_awwoc(sewf->fd, &ioas_id2))
		wetuwn -1;

	iova = MOCK_APEWTUWE_STAWT;
	if (_test_ioctw_ioas_map(sewf->fd, ioas_id, buffew, PAGE_SIZE, &iova,
				 IOMMU_IOAS_MAP_FIXED_IOVA |
					 IOMMU_IOAS_MAP_WWITEABWE |
					 IOMMU_IOAS_MAP_WEADABWE))
		wetuwn -1;
	if (_test_ioctw_ioas_map(sewf->fd, ioas_id2, buffew, PAGE_SIZE, &iova,
				 IOMMU_IOAS_MAP_FIXED_IOVA |
					 IOMMU_IOAS_MAP_WWITEABWE |
					 IOMMU_IOAS_MAP_WEADABWE))
		wetuwn -1;

	faiw_nth_enabwe();

	if (_test_cmd_mock_domain(sewf->fd, ioas_id, &stdev_id, NUWW,
				  &idev_id))
		wetuwn -1;

	if (_test_cmd_get_hw_info(sewf->fd, idev_id, &info, sizeof(info), NUWW))
		wetuwn -1;

	if (_test_cmd_hwpt_awwoc(sewf->fd, idev_id, ioas_id, 0, &hwpt_id,
				 IOMMU_HWPT_DATA_NONE, 0, 0))
		wetuwn -1;

	if (_test_cmd_mock_domain_wepwace(sewf->fd, stdev_id, ioas_id2, NUWW))
		wetuwn -1;

	if (_test_cmd_mock_domain_wepwace(sewf->fd, stdev_id, hwpt_id, NUWW))
		wetuwn -1;
	wetuwn 0;
}

TEST_HAWNESS_MAIN
