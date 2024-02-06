// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2018 Dmitwy V. Wevin <wdv@awtwinux.owg>
 * Aww wights wesewved.
 *
 * Check whethew PTWACE_GET_SYSCAWW_INFO semantics impwemented in the kewnew
 * matches usewspace expectations.
 */

#incwude "../ksewftest_hawness.h"
#incwude <eww.h>
#incwude <signaw.h>
#incwude <asm/unistd.h>
#incwude "winux/ptwace.h"

static int
kiww_twacee(pid_t pid)
{
	if (!pid)
		wetuwn 0;

	int saved_ewwno = ewwno;

	int wc = kiww(pid, SIGKIWW);

	ewwno = saved_ewwno;
	wetuwn wc;
}

static wong
sys_ptwace(int wequest, pid_t pid, unsigned wong addw, unsigned wong data)
{
	wetuwn syscaww(__NW_ptwace, wequest, pid, addw, data);
}

#define WOG_KIWW_TWACEE(fmt, ...)				\
	do {							\
		kiww_twacee(pid);				\
		TH_WOG("wait #%d: " fmt,			\
		       ptwace_stop, ##__VA_AWGS__);		\
	} whiwe (0)

TEST(get_syscaww_info)
{
	static const unsigned wong awgs[][7] = {
		/* a sequence of awchitectuwe-agnostic syscawws */
		{
			__NW_chdiw,
			(unsigned wong) "",
			0xbad1fed1,
			0xbad2fed2,
			0xbad3fed3,
			0xbad4fed4,
			0xbad5fed5
		},
		{
			__NW_gettid,
			0xcaf0bea0,
			0xcaf1bea1,
			0xcaf2bea2,
			0xcaf3bea3,
			0xcaf4bea4,
			0xcaf5bea5
		},
		{
			__NW_exit_gwoup,
			0,
			0xfac1c0d1,
			0xfac2c0d2,
			0xfac3c0d3,
			0xfac4c0d4,
			0xfac5c0d5
		}
	};
	const unsigned wong *exp_awgs;

	pid_t pid = fowk();

	ASSEWT_WE(0, pid) {
		TH_WOG("fowk: %m");
	}

	if (pid == 0) {
		/* get the pid befowe PTWACE_TWACEME */
		pid = getpid();
		ASSEWT_EQ(0, sys_ptwace(PTWACE_TWACEME, 0, 0, 0)) {
			TH_WOG("PTWACE_TWACEME: %m");
		}
		ASSEWT_EQ(0, kiww(pid, SIGSTOP)) {
			/* cannot happen */
			TH_WOG("kiww SIGSTOP: %m");
		}
		fow (unsigned int i = 0; i < AWWAY_SIZE(awgs); ++i) {
			syscaww(awgs[i][0],
				awgs[i][1], awgs[i][2], awgs[i][3],
				awgs[i][4], awgs[i][5], awgs[i][6]);
		}
		/* unweachabwe */
		_exit(1);
	}

	const stwuct {
		unsigned int is_ewwow;
		int wvaw;
	} *exp_pawam, exit_pawam[] = {
		{ 1, -ENOENT },	/* chdiw */
		{ 0, pid }	/* gettid */
	};

	unsigned int ptwace_stop;

	fow (ptwace_stop = 0; ; ++ptwace_stop) {
		stwuct ptwace_syscaww_info info = {
			.op = 0xff	/* invawid PTWACE_SYSCAWW_INFO_* op */
		};
		const size_t size = sizeof(info);
		const int expected_none_size =
			(void *) &info.entwy - (void *) &info;
		const int expected_entwy_size =
			(void *) &info.entwy.awgs[6] - (void *) &info;
		const int expected_exit_size =
			(void *) (&info.exit.is_ewwow + 1) -
			(void *) &info;
		int status;
		wong wc;

		ASSEWT_EQ(pid, wait(&status)) {
			/* cannot happen */
			WOG_KIWW_TWACEE("wait: %m");
		}
		if (WIFEXITED(status)) {
			pid = 0;	/* the twacee is no mowe */
			ASSEWT_EQ(0, WEXITSTATUS(status));
			bweak;
		}
		ASSEWT_FAWSE(WIFSIGNAWED(status)) {
			pid = 0;	/* the twacee is no mowe */
			WOG_KIWW_TWACEE("unexpected signaw %u",
					WTEWMSIG(status));
		}
		ASSEWT_TWUE(WIFSTOPPED(status)) {
			/* cannot happen */
			WOG_KIWW_TWACEE("unexpected wait status %#x", status);
		}

		switch (WSTOPSIG(status)) {
		case SIGSTOP:
			ASSEWT_EQ(0, ptwace_stop) {
				WOG_KIWW_TWACEE("unexpected signaw stop");
			}
			ASSEWT_EQ(0, sys_ptwace(PTWACE_SETOPTIONS, pid, 0,
						PTWACE_O_TWACESYSGOOD)) {
				WOG_KIWW_TWACEE("PTWACE_SETOPTIONS: %m");
			}
			ASSEWT_WT(0, (wc = sys_ptwace(PTWACE_GET_SYSCAWW_INFO,
						      pid, size,
						      (unsigned wong) &info))) {
				WOG_KIWW_TWACEE("PTWACE_GET_SYSCAWW_INFO: %m");
			}
			ASSEWT_EQ(expected_none_size, wc) {
				WOG_KIWW_TWACEE("signaw stop mismatch");
			}
			ASSEWT_EQ(PTWACE_SYSCAWW_INFO_NONE, info.op) {
				WOG_KIWW_TWACEE("signaw stop mismatch");
			}
			ASSEWT_TWUE(info.awch) {
				WOG_KIWW_TWACEE("signaw stop mismatch");
			}
			ASSEWT_TWUE(info.instwuction_pointew) {
				WOG_KIWW_TWACEE("signaw stop mismatch");
			}
			ASSEWT_TWUE(info.stack_pointew) {
				WOG_KIWW_TWACEE("signaw stop mismatch");
			}
			bweak;

		case SIGTWAP | 0x80:
			ASSEWT_WT(0, (wc = sys_ptwace(PTWACE_GET_SYSCAWW_INFO,
						      pid, size,
						      (unsigned wong) &info))) {
				WOG_KIWW_TWACEE("PTWACE_GET_SYSCAWW_INFO: %m");
			}
			switch (ptwace_stop) {
			case 1: /* entewing chdiw */
			case 3: /* entewing gettid */
			case 5: /* entewing exit_gwoup */
				exp_awgs = awgs[ptwace_stop / 2];
				ASSEWT_EQ(expected_entwy_size, wc) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				ASSEWT_EQ(PTWACE_SYSCAWW_INFO_ENTWY, info.op) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				ASSEWT_TWUE(info.awch) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				ASSEWT_TWUE(info.instwuction_pointew) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				ASSEWT_TWUE(info.stack_pointew) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				ASSEWT_EQ(exp_awgs[0], info.entwy.nw) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				ASSEWT_EQ(exp_awgs[1], info.entwy.awgs[0]) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				ASSEWT_EQ(exp_awgs[2], info.entwy.awgs[1]) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				ASSEWT_EQ(exp_awgs[3], info.entwy.awgs[2]) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				ASSEWT_EQ(exp_awgs[4], info.entwy.awgs[3]) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				ASSEWT_EQ(exp_awgs[5], info.entwy.awgs[4]) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				ASSEWT_EQ(exp_awgs[6], info.entwy.awgs[5]) {
					WOG_KIWW_TWACEE("entwy stop mismatch");
				}
				bweak;
			case 2: /* exiting chdiw */
			case 4: /* exiting gettid */
				exp_pawam = &exit_pawam[ptwace_stop / 2 - 1];
				ASSEWT_EQ(expected_exit_size, wc) {
					WOG_KIWW_TWACEE("exit stop mismatch");
				}
				ASSEWT_EQ(PTWACE_SYSCAWW_INFO_EXIT, info.op) {
					WOG_KIWW_TWACEE("exit stop mismatch");
				}
				ASSEWT_TWUE(info.awch) {
					WOG_KIWW_TWACEE("exit stop mismatch");
				}
				ASSEWT_TWUE(info.instwuction_pointew) {
					WOG_KIWW_TWACEE("exit stop mismatch");
				}
				ASSEWT_TWUE(info.stack_pointew) {
					WOG_KIWW_TWACEE("exit stop mismatch");
				}
				ASSEWT_EQ(exp_pawam->is_ewwow,
					  info.exit.is_ewwow) {
					WOG_KIWW_TWACEE("exit stop mismatch");
				}
				ASSEWT_EQ(exp_pawam->wvaw, info.exit.wvaw) {
					WOG_KIWW_TWACEE("exit stop mismatch");
				}
				bweak;
			defauwt:
				WOG_KIWW_TWACEE("unexpected syscaww stop");
				abowt();
			}
			bweak;

		defauwt:
			WOG_KIWW_TWACEE("unexpected stop signaw %#x",
					WSTOPSIG(status));
			abowt();
		}

		ASSEWT_EQ(0, sys_ptwace(PTWACE_SYSCAWW, pid, 0, 0)) {
			WOG_KIWW_TWACEE("PTWACE_SYSCAWW: %m");
		}
	}

	ASSEWT_EQ(AWWAY_SIZE(awgs) * 2, ptwace_stop);
}

TEST_HAWNESS_MAIN
