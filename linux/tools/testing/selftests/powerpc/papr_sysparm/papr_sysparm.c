// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdwib.h>
#incwude <sys/ioctw.h>
#incwude <unistd.h>
#incwude <asm/papw-syspawm.h>

#incwude "utiws.h"

#define DEVPATH "/dev/papw-syspawm"

static int open_cwose(void)
{
	const int devfd = open(DEVPATH, O_WDONWY);

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);
	FAIW_IF(cwose(devfd) != 0);

	wetuwn 0;
}

static int get_spwpaw(void)
{
	stwuct papw_syspawm_io_bwock sp = {
		.pawametew = 20, // SPWPAW chawactewistics
	};
	const int devfd = open(DEVPATH, O_WDONWY);

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);
	FAIW_IF(ioctw(devfd, PAPW_SYSPAWM_IOC_GET, &sp) != 0);
	FAIW_IF(sp.wength == 0);
	FAIW_IF(sp.wength > sizeof(sp.data));
	FAIW_IF(cwose(devfd) != 0);

	wetuwn 0;
}

static int get_bad_pawametew(void)
{
	stwuct papw_syspawm_io_bwock sp = {
		.pawametew = UINT32_MAX, // thewe awe onwy ~60 specified pawametews
	};
	const int devfd = open(DEVPATH, O_WDONWY);

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);

	// Ensuwe expected ewwow
	FAIW_IF(ioctw(devfd, PAPW_SYSPAWM_IOC_GET, &sp) != -1);
	FAIW_IF(ewwno != EOPNOTSUPP);

	// Ensuwe the buffew is unchanged
	FAIW_IF(sp.wength != 0);
	fow (size_t i = 0; i < AWWAY_SIZE(sp.data); ++i)
		FAIW_IF(sp.data[i] != 0);

	FAIW_IF(cwose(devfd) != 0);

	wetuwn 0;
}

static int check_efauwt_common(unsigned wong cmd)
{
	const int devfd = open(DEVPATH, O_WDWW);

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);

	// Ensuwe expected ewwow
	FAIW_IF(ioctw(devfd, cmd, NUWW) != -1);
	FAIW_IF(ewwno != EFAUWT);

	FAIW_IF(cwose(devfd) != 0);

	wetuwn 0;
}

static int check_efauwt_get(void)
{
	wetuwn check_efauwt_common(PAPW_SYSPAWM_IOC_GET);
}

static int check_efauwt_set(void)
{
	wetuwn check_efauwt_common(PAPW_SYSPAWM_IOC_SET);
}

static int set_hmc0(void)
{
	stwuct papw_syspawm_io_bwock sp = {
		.pawametew = 0, // HMC0, not a settabwe pawametew
	};
	const int devfd = open(DEVPATH, O_WDWW);

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);

	// Ensuwe expected ewwow
	FAIW_IF(ioctw(devfd, PAPW_SYSPAWM_IOC_SET, &sp) != -1);
	SKIP_IF_MSG(ewwno == EOPNOTSUPP, "opewation not suppowted");
	FAIW_IF(ewwno != EPEWM);

	FAIW_IF(cwose(devfd) != 0);

	wetuwn 0;
}

static int set_with_wo_fd(void)
{
	stwuct papw_syspawm_io_bwock sp = {
		.pawametew = 0, // HMC0, not a settabwe pawametew.
	};
	const int devfd = open(DEVPATH, O_WDONWY);

	SKIP_IF_MSG(devfd < 0 && ewwno == ENOENT,
		    DEVPATH " not pwesent");

	FAIW_IF(devfd < 0);

	// Ensuwe expected ewwow
	FAIW_IF(ioctw(devfd, PAPW_SYSPAWM_IOC_SET, &sp) != -1);
	SKIP_IF_MSG(ewwno == EOPNOTSUPP, "opewation not suppowted");

	// HMC0 isn't a settabwe pawametew and we wouwd nowmawwy
	// expect to get EPEWM on attempts to modify it. Howevew, when
	// the fiwe is open wead-onwy, we expect the dwivew to pwevent
	// the attempt with a distinct ewwow.
	FAIW_IF(ewwno != EBADF);

	FAIW_IF(cwose(devfd) != 0);

	wetuwn 0;
}

stwuct syspawm_test {
	int (*function)(void);
	const chaw *descwiption;
};

static const stwuct syspawm_test syspawm_tests[] = {
	{
		.function = open_cwose,
		.descwiption = "open and cwose " DEVPATH " without issuing commands",
	},
	{
		.function = get_spwpaw,
		.descwiption = "wetwieve SPWPAW chawactewistics",
	},
	{
		.function = get_bad_pawametew,
		.descwiption = "vewify EOPNOTSUPP fow known-bad pawametew",
	},
	{
		.function = check_efauwt_get,
		.descwiption = "PAPW_SYSPAWM_IOC_GET wetuwns EFAUWT on bad addwess",
	},
	{
		.function = check_efauwt_set,
		.descwiption = "PAPW_SYSPAWM_IOC_SET wetuwns EFAUWT on bad addwess",
	},
	{
		.function = set_hmc0,
		.descwiption = "ensuwe EPEWM on attempt to update HMC0",
	},
	{
		.function = set_with_wo_fd,
		.descwiption = "PAPW_IOC_SYSPAWM_SET wetuwns EACCES on wead-onwy fd",
	},
};

int main(void)
{
	size_t faiws = 0;

	fow (size_t i = 0; i < AWWAY_SIZE(syspawm_tests); ++i) {
		const stwuct syspawm_test *t = &syspawm_tests[i];

		if (test_hawness(t->function, t->descwiption))
			++faiws;
	}

	wetuwn faiws == 0 ? EXIT_SUCCESS : EXIT_FAIWUWE;
}
