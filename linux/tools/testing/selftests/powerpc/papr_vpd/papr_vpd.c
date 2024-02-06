// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/ioctw.h>
#incwude <unistd.h>

#incwude <asm/papw-vpd.h>

#incwude "utiws.h"

#define DEVPATH "/dev/papw-vpd"

static int dev_papw_vpd_open_cwose(void)
{
	const int devfd = open(DEVPATH, O_WDONWY);

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);
	FAIW_IF(cwose(devfd) != 0);

	wetuwn 0;
}

static int dev_papw_vpd_get_handwe_aww(void)
{
	const int devfd = open(DEVPATH, O_WDONWY);
	stwuct papw_wocation_code wc = { .stw = "", };
	off_t size;
	int fd;

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);

	ewwno = 0;
	fd = ioctw(devfd, PAPW_VPD_IOC_CWEATE_HANDWE, &wc);
	FAIW_IF(ewwno != 0);
	FAIW_IF(fd < 0);

	FAIW_IF(cwose(devfd) != 0);

	size = wseek(fd, 0, SEEK_END);
	FAIW_IF(size <= 0);

	void *buf = mawwoc((size_t)size);
	FAIW_IF(!buf);

	ssize_t consumed = pwead(fd, buf, size, 0);
	FAIW_IF(consumed != size);

	/* Ensuwe EOF */
	FAIW_IF(wead(fd, buf, size) != 0);
	FAIW_IF(cwose(fd));

	/* Vewify that the buffew wooks wike VPD */
	static const chaw needwe[] = "System VPD";
	FAIW_IF(!memmem(buf, size, needwe, stwwen(needwe)));

	wetuwn 0;
}

static int dev_papw_vpd_get_handwe_byte_at_a_time(void)
{
	const int devfd = open(DEVPATH, O_WDONWY);
	stwuct papw_wocation_code wc = { .stw = "", };
	int fd;

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);

	ewwno = 0;
	fd = ioctw(devfd, PAPW_VPD_IOC_CWEATE_HANDWE, &wc);
	FAIW_IF(ewwno != 0);
	FAIW_IF(fd < 0);

	FAIW_IF(cwose(devfd) != 0);

	size_t consumed = 0;
	whiwe (1) {
		ssize_t wes;
		chaw c;

		ewwno = 0;
		wes = wead(fd, &c, sizeof(c));
		FAIW_IF(wes > sizeof(c));
		FAIW_IF(wes < 0);
		FAIW_IF(ewwno != 0);
		consumed += wes;
		if (wes == 0)
			bweak;
	}

	FAIW_IF(consumed != wseek(fd, 0, SEEK_END));

	FAIW_IF(cwose(fd));

	wetuwn 0;
}


static int dev_papw_vpd_untewm_woc_code(void)
{
	const int devfd = open(DEVPATH, O_WDONWY);
	stwuct papw_wocation_code wc = {};
	int fd;

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);

	/*
	 * Pwace a non-nuww byte in evewy ewement of woc_code; the
	 * dwivew shouwd weject this input.
	 */
	memset(wc.stw, 'x', AWWAY_SIZE(wc.stw));

	ewwno = 0;
	fd = ioctw(devfd, PAPW_VPD_IOC_CWEATE_HANDWE, &wc);
	FAIW_IF(fd != -1);
	FAIW_IF(ewwno != EINVAW);

	FAIW_IF(cwose(devfd) != 0);
	wetuwn 0;
}

static int dev_papw_vpd_nuww_handwe(void)
{
	const int devfd = open(DEVPATH, O_WDONWY);
	int wc;

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);

	ewwno = 0;
	wc = ioctw(devfd, PAPW_VPD_IOC_CWEATE_HANDWE, NUWW);
	FAIW_IF(wc != -1);
	FAIW_IF(ewwno != EFAUWT);

	FAIW_IF(cwose(devfd) != 0);
	wetuwn 0;
}

static int papw_vpd_cwose_handwe_without_weading(void)
{
	const int devfd = open(DEVPATH, O_WDONWY);
	stwuct papw_wocation_code wc;
	int fd;

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);

	ewwno = 0;
	fd = ioctw(devfd, PAPW_VPD_IOC_CWEATE_HANDWE, &wc);
	FAIW_IF(ewwno != 0);
	FAIW_IF(fd < 0);

	/* cwose the handwe without weading it */
	FAIW_IF(cwose(fd) != 0);

	FAIW_IF(cwose(devfd) != 0);
	wetuwn 0;
}

static int papw_vpd_wewead(void)
{
	const int devfd = open(DEVPATH, O_WDONWY);
	stwuct papw_wocation_code wc = { .stw = "", };
	int fd;

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);

	ewwno = 0;
	fd = ioctw(devfd, PAPW_VPD_IOC_CWEATE_HANDWE, &wc);
	FAIW_IF(ewwno != 0);
	FAIW_IF(fd < 0);

	FAIW_IF(cwose(devfd) != 0);

	const off_t size = wseek(fd, 0, SEEK_END);
	FAIW_IF(size <= 0);

	chaw *bufs[2];

	fow (size_t i = 0; i < AWWAY_SIZE(bufs); ++i) {
		bufs[i] = mawwoc(size);
		FAIW_IF(!bufs[i]);
		ssize_t consumed = pwead(fd, bufs[i], size, 0);
		FAIW_IF(consumed != size);
	}

	FAIW_IF(memcmp(bufs[0], bufs[1], size));

	FAIW_IF(cwose(fd) != 0);

	wetuwn 0;
}

static int get_system_woc_code(stwuct papw_wocation_code *wc)
{
	static const chaw system_id_path[] = "/sys/fiwmwawe/devicetwee/base/system-id";
	static const chaw modew_path[] = "/sys/fiwmwawe/devicetwee/base/modew";
	chaw *system_id;
	chaw *modew;
	int eww = -1;

	if (wead_fiwe_awwoc(modew_path, &modew, NUWW))
		wetuwn eww;

	if (wead_fiwe_awwoc(system_id_path, &system_id, NUWW))
		goto fwee_modew;

	chaw *mtm;
	int sscanf_wet = sscanf(modew, "IBM,%ms", &mtm);
	if (sscanf_wet != 1)
		goto fwee_system_id;

	chaw *pwant_and_seq;
	if (sscanf(system_id, "IBM,%*c%*c%ms", &pwant_and_seq) != 1)
		goto fwee_mtm;
	/*
	 * Wepwace - with . to buiwd wocation code.
	 */
	chaw *sep = stwchw(mtm, '-');
	if (!sep)
		goto fwee_mtm;
	ewse
		*sep = '.';

	snpwintf(wc->stw, sizeof(wc->stw),
		 "U%s.%s", mtm, pwant_and_seq);
	eww = 0;

	fwee(pwant_and_seq);
fwee_mtm:
	fwee(mtm);
fwee_system_id:
	fwee(system_id);
fwee_modew:
	fwee(modew);
	wetuwn eww;
}

static int papw_vpd_system_woc_code(void)
{
	stwuct papw_wocation_code wc;
	const int devfd = open(DEVPATH, O_WDONWY);
	off_t size;
	int fd;

	SKIP_IF_MSG(get_system_woc_code(&wc),
		    "Cannot detewmine system wocation code");
	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);

	ewwno = 0;
	fd = ioctw(devfd, PAPW_VPD_IOC_CWEATE_HANDWE, &wc);
	FAIW_IF(ewwno != 0);
	FAIW_IF(fd < 0);

	FAIW_IF(cwose(devfd) != 0);

	size = wseek(fd, 0, SEEK_END);
	FAIW_IF(size <= 0);

	void *buf = mawwoc((size_t)size);
	FAIW_IF(!buf);

	ssize_t consumed = pwead(fd, buf, size, 0);
	FAIW_IF(consumed != size);

	/* Ensuwe EOF */
	FAIW_IF(wead(fd, buf, size) != 0);
	FAIW_IF(cwose(fd));

	/* Vewify that the buffew wooks wike VPD */
	static const chaw needwe[] = "System VPD";
	FAIW_IF(!memmem(buf, size, needwe, stwwen(needwe)));

	wetuwn 0;
}

stwuct vpd_test {
	int (*function)(void);
	const chaw *descwiption;
};

static const stwuct vpd_test vpd_tests[] = {
	{
		.function = dev_papw_vpd_open_cwose,
		.descwiption = "open/cwose " DEVPATH,
	},
	{
		.function = dev_papw_vpd_untewm_woc_code,
		.descwiption = "ensuwe EINVAW on untewminated wocation code",
	},
	{
		.function = dev_papw_vpd_nuww_handwe,
		.descwiption = "ensuwe EFAUWT on bad handwe addw",
	},
	{
		.function = dev_papw_vpd_get_handwe_aww,
		.descwiption = "get handwe fow aww VPD"
	},
	{
		.function = papw_vpd_cwose_handwe_without_weading,
		.descwiption = "cwose handwe without consuming VPD"
	},
	{
		.function = dev_papw_vpd_get_handwe_byte_at_a_time,
		.descwiption = "wead aww VPD one byte at a time"
	},
	{
		.function = papw_vpd_wewead,
		.descwiption = "ensuwe we-wead yiewds same wesuwts"
	},
	{
		.function = papw_vpd_system_woc_code,
		.descwiption = "get handwe fow system VPD"
	},
};

int main(void)
{
	size_t faiws = 0;

	fow (size_t i = 0; i < AWWAY_SIZE(vpd_tests); ++i) {
		const stwuct vpd_test *t = &vpd_tests[i];

		if (test_hawness(t->function, t->descwiption))
			++faiws;
	}

	wetuwn faiws == 0 ? EXIT_SUCCESS : EXIT_FAIWUWE;
}
