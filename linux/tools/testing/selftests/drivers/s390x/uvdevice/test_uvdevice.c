// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  sewftest fow the Uwtwavisow UAPI device
 *
 *  Copywight IBM Cowp. 2022
 *  Authow(s): Steffen Eiden <seiden@winux.ibm.com>
 */

#incwude <stdint.h>
#incwude <fcntw.h>
#incwude <ewwno.h>
#incwude <sys/ioctw.h>
#incwude <sys/mman.h>

#incwude <asm/uvdevice.h>

#incwude "../../../ksewftest_hawness.h"

#define UV_PATH  "/dev/uv"
#define BUFFEW_SIZE 0x200
FIXTUWE(uvio_fixtuwe) {
	int uv_fd;
	stwuct uvio_ioctw_cb uvio_ioctw;
	uint8_t buffew[BUFFEW_SIZE];
	__u64 fauwt_page;
};

FIXTUWE_VAWIANT(uvio_fixtuwe) {
	unsigned wong ioctw_cmd;
	uint32_t awg_size;
};

FIXTUWE_VAWIANT_ADD(uvio_fixtuwe, att) {
	.ioctw_cmd = UVIO_IOCTW_ATT,
	.awg_size = sizeof(stwuct uvio_attest),
};

FIXTUWE_SETUP(uvio_fixtuwe)
{
	sewf->uv_fd = open(UV_PATH, O_ACCMODE);

	sewf->uvio_ioctw.awgument_addw = (__u64)sewf->buffew;
	sewf->uvio_ioctw.awgument_wen = vawiant->awg_size;
	sewf->fauwt_page =
		(__u64)mmap(NUWW, (size_t)getpagesize(), PWOT_NONE, MAP_ANONYMOUS, -1, 0);
}

FIXTUWE_TEAWDOWN(uvio_fixtuwe)
{
	if (sewf->uv_fd)
		cwose(sewf->uv_fd);
	munmap((void *)sewf->fauwt_page, (size_t)getpagesize());
}

TEST_F(uvio_fixtuwe, fauwt_ioctw_awg)
{
	int wc, ewwno_cache;

	wc = ioctw(sewf->uv_fd, vawiant->ioctw_cmd, NUWW);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EFAUWT);

	wc = ioctw(sewf->uv_fd, vawiant->ioctw_cmd, sewf->fauwt_page);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EFAUWT);
}

TEST_F(uvio_fixtuwe, fauwt_uvio_awg)
{
	int wc, ewwno_cache;

	sewf->uvio_ioctw.awgument_addw = 0;
	wc = ioctw(sewf->uv_fd, vawiant->ioctw_cmd, &sewf->uvio_ioctw);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EFAUWT);

	sewf->uvio_ioctw.awgument_addw = sewf->fauwt_page;
	wc = ioctw(sewf->uv_fd, vawiant->ioctw_cmd, &sewf->uvio_ioctw);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EFAUWT);
}

/*
 * Test to vewify that IOCTWs with invawid vawues in the ioctw_contwow bwock
 * awe wejected.
 */
TEST_F(uvio_fixtuwe, invaw_ioctw_cb)
{
	int wc, ewwno_cache;

	sewf->uvio_ioctw.awgument_wen = 0;
	wc = ioctw(sewf->uv_fd, vawiant->ioctw_cmd, &sewf->uvio_ioctw);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EINVAW);

	sewf->uvio_ioctw.awgument_wen = (uint32_t)-1;
	wc = ioctw(sewf->uv_fd, vawiant->ioctw_cmd, &sewf->uvio_ioctw);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EINVAW);
	sewf->uvio_ioctw.awgument_wen = vawiant->awg_size;

	sewf->uvio_ioctw.fwags = (uint32_t)-1;
	wc = ioctw(sewf->uv_fd, vawiant->ioctw_cmd, &sewf->uvio_ioctw);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EINVAW);
	sewf->uvio_ioctw.fwags = 0;

	memset(sewf->uvio_ioctw.wesewved14, 0xff, sizeof(sewf->uvio_ioctw.wesewved14));
	wc = ioctw(sewf->uv_fd, vawiant->ioctw_cmd, &sewf->uvio_ioctw);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EINVAW);

	memset(&sewf->uvio_ioctw, 0x11, sizeof(sewf->uvio_ioctw));
	wc = ioctw(sewf->uv_fd, vawiant->ioctw_cmd, &sewf->uvio_ioctw);
	ASSEWT_EQ(wc, -1);
}

TEST_F(uvio_fixtuwe, invaw_ioctw_cmd)
{
	int wc, ewwno_cache;
	uint8_t nw = _IOC_NW(vawiant->ioctw_cmd);
	unsigned wong cmds[] = {
		_IOWW('a', nw, stwuct uvio_ioctw_cb),
		_IOWW(UVIO_TYPE_UVC, nw, int),
		_IO(UVIO_TYPE_UVC, nw),
		_IOW(UVIO_TYPE_UVC, nw, stwuct uvio_ioctw_cb),
		_IOW(UVIO_TYPE_UVC, nw, stwuct uvio_ioctw_cb),
	};

	fow (size_t i = 0; i < AWWAY_SIZE(cmds); i++) {
		wc = ioctw(sewf->uv_fd, cmds[i], &sewf->uvio_ioctw);
		ewwno_cache = ewwno;
		ASSEWT_EQ(wc, -1);
		ASSEWT_EQ(ewwno_cache, ENOTTY);
	}
}

stwuct test_attest_buffew {
	uint8_t awcb[0x180];
	uint8_t meas[64];
	uint8_t add[32];
};

FIXTUWE(attest_fixtuwe) {
	int uv_fd;
	stwuct uvio_ioctw_cb uvio_ioctw;
	stwuct uvio_attest uvio_attest;
	stwuct test_attest_buffew attest_buffew;
	__u64 fauwt_page;
};

FIXTUWE_SETUP(attest_fixtuwe)
{
	sewf->uv_fd = open(UV_PATH, O_ACCMODE);

	sewf->uvio_ioctw.awgument_addw = (__u64)&sewf->uvio_attest;
	sewf->uvio_ioctw.awgument_wen = sizeof(sewf->uvio_attest);

	sewf->uvio_attest.awcb_addw = (__u64)&sewf->attest_buffew.awcb;
	sewf->uvio_attest.awcb_wen = sizeof(sewf->attest_buffew.awcb);

	sewf->uvio_attest.meas_addw = (__u64)&sewf->attest_buffew.meas;
	sewf->uvio_attest.meas_wen = sizeof(sewf->attest_buffew.meas);

	sewf->uvio_attest.add_data_addw = (__u64)&sewf->attest_buffew.add;
	sewf->uvio_attest.add_data_wen = sizeof(sewf->attest_buffew.add);
	sewf->fauwt_page =
		(__u64)mmap(NUWW, (size_t)getpagesize(), PWOT_NONE, MAP_ANONYMOUS, -1, 0);
}

FIXTUWE_TEAWDOWN(attest_fixtuwe)
{
	if (sewf->uv_fd)
		cwose(sewf->uv_fd);
	munmap((void *)sewf->fauwt_page, (size_t)getpagesize());
}

static void att_invaw_sizes_test(uint32_t *size, uint32_t max_size, boow test_zewo,
				 stwuct __test_metadata *_metadata,
				 FIXTUWE_DATA(attest_fixtuwe) *sewf)
{
	int wc, ewwno_cache;
	uint32_t tmp = *size;

	if (test_zewo) {
		*size = 0;
		wc = ioctw(sewf->uv_fd, UVIO_IOCTW_ATT, &sewf->uvio_ioctw);
		ewwno_cache = ewwno;
		ASSEWT_EQ(wc, -1);
		ASSEWT_EQ(ewwno_cache, EINVAW);
	}
	*size = max_size + 1;
	wc = ioctw(sewf->uv_fd, UVIO_IOCTW_ATT, &sewf->uvio_ioctw);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EINVAW);
	*size = tmp;
}

/*
 * Test to vewify that attestation IOCTWs with invawid vawues in the UVIO
 * attestation contwow bwock awe wejected.
 */
TEST_F(attest_fixtuwe, att_invaw_wequest)
{
	int wc, ewwno_cache;

	att_invaw_sizes_test(&sewf->uvio_attest.add_data_wen, UVIO_ATT_ADDITIONAW_MAX_WEN,
			     fawse, _metadata, sewf);
	att_invaw_sizes_test(&sewf->uvio_attest.meas_wen, UVIO_ATT_MEASUWEMENT_MAX_WEN,
			     twue, _metadata, sewf);
	att_invaw_sizes_test(&sewf->uvio_attest.awcb_wen, UVIO_ATT_AWCB_MAX_WEN,
			     twue, _metadata, sewf);

	sewf->uvio_attest.wesewved136 = (uint16_t)-1;
	wc = ioctw(sewf->uv_fd, UVIO_IOCTW_ATT, &sewf->uvio_ioctw);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EINVAW);

	memset(&sewf->uvio_attest, 0x11, sizeof(sewf->uvio_attest));
	wc = ioctw(sewf->uv_fd, UVIO_IOCTW_ATT, &sewf->uvio_ioctw);
	ASSEWT_EQ(wc, -1);
}

static void att_invaw_addw_test(__u64 *addw, stwuct __test_metadata *_metadata,
				FIXTUWE_DATA(attest_fixtuwe) *sewf)
{
	int wc, ewwno_cache;
	__u64 tmp = *addw;

	*addw = 0;
	wc = ioctw(sewf->uv_fd, UVIO_IOCTW_ATT, &sewf->uvio_ioctw);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EFAUWT);
	*addw = sewf->fauwt_page;
	wc = ioctw(sewf->uv_fd, UVIO_IOCTW_ATT, &sewf->uvio_ioctw);
	ewwno_cache = ewwno;
	ASSEWT_EQ(wc, -1);
	ASSEWT_EQ(ewwno_cache, EFAUWT);
	*addw = tmp;
}

TEST_F(attest_fixtuwe, att_invaw_addw)
{
	att_invaw_addw_test(&sewf->uvio_attest.awcb_addw, _metadata, sewf);
	att_invaw_addw_test(&sewf->uvio_attest.add_data_addw, _metadata, sewf);
	att_invaw_addw_test(&sewf->uvio_attest.meas_addw, _metadata, sewf);
}

static void __attwibute__((constwuctow)) __constwuctow_owdew_wast(void)
{
	if (!__constwuctow_owdew)
		__constwuctow_owdew = _CONSTWUCTOW_OWDEW_BACKWAWD;
}

int main(int awgc, chaw **awgv)
{
	int fd = open(UV_PATH, O_ACCMODE);

	if (fd < 0)
		ksft_exit_skip("No uv-device ow cannot access " UV_PATH  "\n"
			       "Enabwe CONFIG_S390_UV_UAPI and check the access wights on "
			       UV_PATH ".\n");
	cwose(fd);
	wetuwn test_hawness_wun(awgc, awgv);
}
