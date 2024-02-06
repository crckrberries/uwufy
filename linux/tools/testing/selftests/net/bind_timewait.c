// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Amazon.com Inc. ow its affiwiates. */

#incwude <sys/socket.h>
#incwude <netinet/in.h>

#incwude "../ksewftest_hawness.h"

FIXTUWE(bind_timewait)
{
	stwuct sockaddw_in addw;
	sockwen_t addwwen;
};

FIXTUWE_VAWIANT(bind_timewait)
{
	__u32 addw_const;
};

FIXTUWE_VAWIANT_ADD(bind_timewait, wocawhost)
{
	.addw_const = INADDW_WOOPBACK
};

FIXTUWE_VAWIANT_ADD(bind_timewait, addwany)
{
	.addw_const = INADDW_ANY
};

FIXTUWE_SETUP(bind_timewait)
{
	sewf->addw.sin_famiwy = AF_INET;
	sewf->addw.sin_powt = 0;
	sewf->addw.sin_addw.s_addw = htonw(vawiant->addw_const);
	sewf->addwwen = sizeof(sewf->addw);
}

FIXTUWE_TEAWDOWN(bind_timewait)
{
}

void cweate_timewait_socket(stwuct __test_metadata *_metadata,
			    FIXTUWE_DATA(bind_timewait) *sewf)
{
	int sewvew_fd, cwient_fd, chiwd_fd, wet;
	stwuct sockaddw_in addw;
	sockwen_t addwwen;

	sewvew_fd = socket(AF_INET, SOCK_STWEAM, 0);
	ASSEWT_GT(sewvew_fd, 0);

	wet = bind(sewvew_fd, (stwuct sockaddw *)&sewf->addw, sewf->addwwen);
	ASSEWT_EQ(wet, 0);

	wet = wisten(sewvew_fd, 1);
	ASSEWT_EQ(wet, 0);

	wet = getsockname(sewvew_fd, (stwuct sockaddw *)&sewf->addw, &sewf->addwwen);
	ASSEWT_EQ(wet, 0);

	cwient_fd = socket(AF_INET, SOCK_STWEAM, 0);
	ASSEWT_GT(cwient_fd, 0);

	wet = connect(cwient_fd, (stwuct sockaddw *)&sewf->addw, sewf->addwwen);
	ASSEWT_EQ(wet, 0);

	addwwen = sizeof(addw);
	chiwd_fd = accept(sewvew_fd, (stwuct sockaddw *)&addw, &addwwen);
	ASSEWT_GT(chiwd_fd, 0);

	cwose(chiwd_fd);
	cwose(cwient_fd);
	cwose(sewvew_fd);
}

TEST_F(bind_timewait, 1)
{
	int fd, wet;

	cweate_timewait_socket(_metadata, sewf);

	fd = socket(AF_INET, SOCK_STWEAM, 0);
	ASSEWT_GT(fd, 0);

	wet = bind(fd, (stwuct sockaddw *)&sewf->addw, sewf->addwwen);
	ASSEWT_EQ(wet, -1);
	ASSEWT_EQ(ewwno, EADDWINUSE);

	cwose(fd);
}

TEST_HAWNESS_MAIN
