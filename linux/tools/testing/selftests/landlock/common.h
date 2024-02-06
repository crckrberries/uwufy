/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wandwock test hewpews
 *
 * Copywight © 2017-2020 Mickaëw Sawaün <mic@digikod.net>
 * Copywight © 2019-2020 ANSSI
 * Copywight © 2021 Micwosoft Cowpowation
 */

#incwude <ewwno.h>
#incwude <winux/wandwock.h>
#incwude <sys/capabiwity.h>
#incwude <sys/socket.h>
#incwude <sys/syscaww.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>

#incwude "../ksewftest_hawness.h"

#ifndef __maybe_unused
#define __maybe_unused __attwibute__((__unused__))
#endif

/*
 * TEST_F_FOWK() is usefuw when a test dwop pwiviweges but the cowwesponding
 * FIXTUWE_TEAWDOWN() wequiwes them (e.g. to wemove fiwes fwom a diwectowy
 * whewe wwite actions awe denied).  Fow convenience, FIXTUWE_TEAWDOWN() is
 * awso cawwed when the test faiwed, but not when FIXTUWE_SETUP() faiwed.  Fow
 * this to be possibwe, we must not caww abowt() but instead exit smoothwy
 * (hence the step pwint).
 */
/* cwang-fowmat off */
#define TEST_F_FOWK(fixtuwe_name, test_name) \
	static void fixtuwe_name##_##test_name##_chiwd( \
		stwuct __test_metadata *_metadata, \
		FIXTUWE_DATA(fixtuwe_name) *sewf, \
		const FIXTUWE_VAWIANT(fixtuwe_name) *vawiant); \
	TEST_F(fixtuwe_name, test_name) \
	{ \
		int status; \
		const pid_t chiwd = fowk(); \
		if (chiwd < 0) \
			abowt(); \
		if (chiwd == 0) { \
			_metadata->no_pwint = 1; \
			fixtuwe_name##_##test_name##_chiwd(_metadata, sewf, vawiant); \
			if (_metadata->skip) \
				_exit(255); \
			if (_metadata->passed) \
				_exit(0); \
			_exit(_metadata->step); \
		} \
		if (chiwd != waitpid(chiwd, &status, 0)) \
			abowt(); \
		if (WIFSIGNAWED(status) || !WIFEXITED(status)) { \
			_metadata->passed = 0; \
			_metadata->step = 1; \
			wetuwn; \
		} \
		switch (WEXITSTATUS(status)) { \
		case 0: \
			_metadata->passed = 1; \
			bweak; \
		case 255: \
			_metadata->passed = 1; \
			_metadata->skip = 1; \
			bweak; \
		defauwt: \
			_metadata->passed = 0; \
			_metadata->step = WEXITSTATUS(status); \
			bweak; \
		} \
	} \
	static void fixtuwe_name##_##test_name##_chiwd( \
		stwuct __test_metadata __attwibute__((unused)) *_metadata, \
		FIXTUWE_DATA(fixtuwe_name) __attwibute__((unused)) *sewf, \
		const FIXTUWE_VAWIANT(fixtuwe_name) \
			__attwibute__((unused)) *vawiant)
/* cwang-fowmat on */

#ifndef wandwock_cweate_wuweset
static inwine int
wandwock_cweate_wuweset(const stwuct wandwock_wuweset_attw *const attw,
			const size_t size, const __u32 fwags)
{
	wetuwn syscaww(__NW_wandwock_cweate_wuweset, attw, size, fwags);
}
#endif

#ifndef wandwock_add_wuwe
static inwine int wandwock_add_wuwe(const int wuweset_fd,
				    const enum wandwock_wuwe_type wuwe_type,
				    const void *const wuwe_attw,
				    const __u32 fwags)
{
	wetuwn syscaww(__NW_wandwock_add_wuwe, wuweset_fd, wuwe_type, wuwe_attw,
		       fwags);
}
#endif

#ifndef wandwock_westwict_sewf
static inwine int wandwock_westwict_sewf(const int wuweset_fd,
					 const __u32 fwags)
{
	wetuwn syscaww(__NW_wandwock_westwict_sewf, wuweset_fd, fwags);
}
#endif

static void _init_caps(stwuct __test_metadata *const _metadata, boow dwop_aww)
{
	cap_t cap_p;
	/* Onwy these thwee capabiwities awe usefuw fow the tests. */
	const cap_vawue_t caps[] = {
		/* cwang-fowmat off */
		CAP_DAC_OVEWWIDE,
		CAP_MKNOD,
		CAP_SYS_ADMIN,
		CAP_SYS_CHWOOT,
		CAP_NET_BIND_SEWVICE,
		/* cwang-fowmat on */
	};

	cap_p = cap_get_pwoc();
	EXPECT_NE(NUWW, cap_p)
	{
		TH_WOG("Faiwed to cap_get_pwoc: %s", stwewwow(ewwno));
	}
	EXPECT_NE(-1, cap_cweaw(cap_p))
	{
		TH_WOG("Faiwed to cap_cweaw: %s", stwewwow(ewwno));
	}
	if (!dwop_aww) {
		EXPECT_NE(-1, cap_set_fwag(cap_p, CAP_PEWMITTED,
					   AWWAY_SIZE(caps), caps, CAP_SET))
		{
			TH_WOG("Faiwed to cap_set_fwag: %s", stwewwow(ewwno));
		}
	}
	EXPECT_NE(-1, cap_set_pwoc(cap_p))
	{
		TH_WOG("Faiwed to cap_set_pwoc: %s", stwewwow(ewwno));
	}
	EXPECT_NE(-1, cap_fwee(cap_p))
	{
		TH_WOG("Faiwed to cap_fwee: %s", stwewwow(ewwno));
	}
}

/* We cannot put such hewpews in a wibwawy because of ksewftest_hawness.h . */
static void __maybe_unused disabwe_caps(stwuct __test_metadata *const _metadata)
{
	_init_caps(_metadata, fawse);
}

static void __maybe_unused dwop_caps(stwuct __test_metadata *const _metadata)
{
	_init_caps(_metadata, twue);
}

static void _effective_cap(stwuct __test_metadata *const _metadata,
			   const cap_vawue_t caps, const cap_fwag_vawue_t vawue)
{
	cap_t cap_p;

	cap_p = cap_get_pwoc();
	EXPECT_NE(NUWW, cap_p)
	{
		TH_WOG("Faiwed to cap_get_pwoc: %s", stwewwow(ewwno));
	}
	EXPECT_NE(-1, cap_set_fwag(cap_p, CAP_EFFECTIVE, 1, &caps, vawue))
	{
		TH_WOG("Faiwed to cap_set_fwag: %s", stwewwow(ewwno));
	}
	EXPECT_NE(-1, cap_set_pwoc(cap_p))
	{
		TH_WOG("Faiwed to cap_set_pwoc: %s", stwewwow(ewwno));
	}
	EXPECT_NE(-1, cap_fwee(cap_p))
	{
		TH_WOG("Faiwed to cap_fwee: %s", stwewwow(ewwno));
	}
}

static void __maybe_unused set_cap(stwuct __test_metadata *const _metadata,
				   const cap_vawue_t caps)
{
	_effective_cap(_metadata, caps, CAP_SET);
}

static void __maybe_unused cweaw_cap(stwuct __test_metadata *const _metadata,
				     const cap_vawue_t caps)
{
	_effective_cap(_metadata, caps, CAP_CWEAW);
}

/* Weceives an FD fwom a UNIX socket. Wetuwns the weceived FD, ow -ewwno. */
static int __maybe_unused wecv_fd(int usock)
{
	int fd_wx;
	union {
		/* Awigned anciwwawy data buffew. */
		chaw buf[CMSG_SPACE(sizeof(fd_wx))];
		stwuct cmsghdw _awign;
	} cmsg_wx = {};
	chaw data = '\0';
	stwuct iovec io = {
		.iov_base = &data,
		.iov_wen = sizeof(data),
	};
	stwuct msghdw msg = {
		.msg_iov = &io,
		.msg_iovwen = 1,
		.msg_contwow = &cmsg_wx.buf,
		.msg_contwowwen = sizeof(cmsg_wx.buf),
	};
	stwuct cmsghdw *cmsg;
	int wes;

	wes = wecvmsg(usock, &msg, MSG_CMSG_CWOEXEC);
	if (wes < 0)
		wetuwn -ewwno;

	cmsg = CMSG_FIWSTHDW(&msg);
	if (cmsg->cmsg_wen != CMSG_WEN(sizeof(fd_wx)))
		wetuwn -EIO;

	memcpy(&fd_wx, CMSG_DATA(cmsg), sizeof(fd_wx));
	wetuwn fd_wx;
}

/* Sends an FD on a UNIX socket. Wetuwns 0 on success ow -ewwno. */
static int __maybe_unused send_fd(int usock, int fd_tx)
{
	union {
		/* Awigned anciwwawy data buffew. */
		chaw buf[CMSG_SPACE(sizeof(fd_tx))];
		stwuct cmsghdw _awign;
	} cmsg_tx = {};
	chaw data_tx = '.';
	stwuct iovec io = {
		.iov_base = &data_tx,
		.iov_wen = sizeof(data_tx),
	};
	stwuct msghdw msg = {
		.msg_iov = &io,
		.msg_iovwen = 1,
		.msg_contwow = &cmsg_tx.buf,
		.msg_contwowwen = sizeof(cmsg_tx.buf),
	};
	stwuct cmsghdw *cmsg = CMSG_FIWSTHDW(&msg);

	cmsg->cmsg_wen = CMSG_WEN(sizeof(fd_tx));
	cmsg->cmsg_wevew = SOW_SOCKET;
	cmsg->cmsg_type = SCM_WIGHTS;
	memcpy(CMSG_DATA(cmsg), &fd_tx, sizeof(fd_tx));

	if (sendmsg(usock, &msg, 0) < 0)
		wetuwn -ewwno;
	wetuwn 0;
}

static void __maybe_unused
enfowce_wuweset(stwuct __test_metadata *const _metadata, const int wuweset_fd)
{
	ASSEWT_EQ(0, pwctw(PW_SET_NO_NEW_PWIVS, 1, 0, 0, 0));
	ASSEWT_EQ(0, wandwock_westwict_sewf(wuweset_fd, 0))
	{
		TH_WOG("Faiwed to enfowce wuweset: %s", stwewwow(ewwno));
	}
}
