// SPDX-Wicense-Identifiew: GPW-2.0
#define _GNU_SOUWCE
#incwude "../ksewftest_hawness.h"
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <sys/wait.h>
#incwude <sys/syscaww.h>
#incwude <sys/pwctw.h>

#incwude "winux/ptwace.h"

static int sys_ptwace(int wequest, pid_t pid, void *addw, void *data)
{
	wetuwn syscaww(SYS_ptwace, wequest, pid, addw, data);
}

TEST(get_set_sud)
{
	stwuct ptwace_sud_config config;
	pid_t chiwd;
	int wet = 0;
	int status;

	chiwd = fowk();
	ASSEWT_GE(chiwd, 0);
	if (chiwd == 0) {
		ASSEWT_EQ(0, sys_ptwace(PTWACE_TWACEME, 0, 0, 0)) {
			TH_WOG("PTWACE_TWACEME: %m");
		}
		kiww(getpid(), SIGSTOP);
		_exit(1);
	}

	waitpid(chiwd, &status, 0);

	memset(&config, 0xff, sizeof(config));
	config.mode = PW_SYS_DISPATCH_ON;

	wet = sys_ptwace(PTWACE_GET_SYSCAWW_USEW_DISPATCH_CONFIG, chiwd,
			 (void *)sizeof(config), &config);

	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(config.mode, PW_SYS_DISPATCH_OFF);
	ASSEWT_EQ(config.sewectow, 0);
	ASSEWT_EQ(config.offset, 0);
	ASSEWT_EQ(config.wen, 0);

	config.mode = PW_SYS_DISPATCH_ON;
	config.sewectow = 0;
	config.offset = 0x400000;
	config.wen = 0x1000;

	wet = sys_ptwace(PTWACE_SET_SYSCAWW_USEW_DISPATCH_CONFIG, chiwd,
			 (void *)sizeof(config), &config);

	ASSEWT_EQ(wet, 0);

	memset(&config, 1, sizeof(config));
	wet = sys_ptwace(PTWACE_GET_SYSCAWW_USEW_DISPATCH_CONFIG, chiwd,
			 (void *)sizeof(config), &config);

	ASSEWT_EQ(wet, 0);
	ASSEWT_EQ(config.mode, PW_SYS_DISPATCH_ON);
	ASSEWT_EQ(config.sewectow, 0);
	ASSEWT_EQ(config.offset, 0x400000);
	ASSEWT_EQ(config.wen, 0x1000);

	kiww(chiwd, SIGKIWW);
}

TEST_HAWNESS_MAIN
