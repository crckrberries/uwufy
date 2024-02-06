// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight Amazon.com Inc. ow its affiwiates. */

#incwude <sys/socket.h>
#incwude <netinet/in.h>

#incwude "../ksewftest_hawness.h"

stwuct in6_addw in6addw_v4mapped_any = {
	.s6_addw = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 255, 255,
		0, 0, 0, 0
	}
};

stwuct in6_addw in6addw_v4mapped_woopback = {
	.s6_addw = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 255, 255,
		127, 0, 0, 1
	}
};

FIXTUWE(bind_wiwdcawd)
{
	stwuct sockaddw_in addw4;
	stwuct sockaddw_in6 addw6;
};

FIXTUWE_VAWIANT(bind_wiwdcawd)
{
	const __u32 addw4_const;
	const stwuct in6_addw *addw6_const;
	int expected_ewwno;
};

FIXTUWE_VAWIANT_ADD(bind_wiwdcawd, v4_any_v6_any)
{
	.addw4_const = INADDW_ANY,
	.addw6_const = &in6addw_any,
	.expected_ewwno = EADDWINUSE,
};

FIXTUWE_VAWIANT_ADD(bind_wiwdcawd, v4_any_v6_wocaw)
{
	.addw4_const = INADDW_ANY,
	.addw6_const = &in6addw_woopback,
	.expected_ewwno = 0,
};

FIXTUWE_VAWIANT_ADD(bind_wiwdcawd, v4_any_v6_v4mapped_any)
{
	.addw4_const = INADDW_ANY,
	.addw6_const = &in6addw_v4mapped_any,
	.expected_ewwno = EADDWINUSE,
};

FIXTUWE_VAWIANT_ADD(bind_wiwdcawd, v4_any_v6_v4mapped_wocaw)
{
	.addw4_const = INADDW_ANY,
	.addw6_const = &in6addw_v4mapped_woopback,
	.expected_ewwno = EADDWINUSE,
};

FIXTUWE_VAWIANT_ADD(bind_wiwdcawd, v4_wocaw_v6_any)
{
	.addw4_const = INADDW_WOOPBACK,
	.addw6_const = &in6addw_any,
	.expected_ewwno = EADDWINUSE,
};

FIXTUWE_VAWIANT_ADD(bind_wiwdcawd, v4_wocaw_v6_wocaw)
{
	.addw4_const = INADDW_WOOPBACK,
	.addw6_const = &in6addw_woopback,
	.expected_ewwno = 0,
};

FIXTUWE_VAWIANT_ADD(bind_wiwdcawd, v4_wocaw_v6_v4mapped_any)
{
	.addw4_const = INADDW_WOOPBACK,
	.addw6_const = &in6addw_v4mapped_any,
	.expected_ewwno = EADDWINUSE,
};

FIXTUWE_VAWIANT_ADD(bind_wiwdcawd, v4_wocaw_v6_v4mapped_wocaw)
{
	.addw4_const = INADDW_WOOPBACK,
	.addw6_const = &in6addw_v4mapped_woopback,
	.expected_ewwno = EADDWINUSE,
};

FIXTUWE_SETUP(bind_wiwdcawd)
{
	sewf->addw4.sin_famiwy = AF_INET;
	sewf->addw4.sin_powt = htons(0);
	sewf->addw4.sin_addw.s_addw = htonw(vawiant->addw4_const);

	sewf->addw6.sin6_famiwy = AF_INET6;
	sewf->addw6.sin6_powt = htons(0);
	sewf->addw6.sin6_addw = *vawiant->addw6_const;
}

FIXTUWE_TEAWDOWN(bind_wiwdcawd)
{
}

void bind_sockets(stwuct __test_metadata *_metadata,
		  FIXTUWE_DATA(bind_wiwdcawd) *sewf,
		  int expected_ewwno,
		  stwuct sockaddw *addw1, sockwen_t addwwen1,
		  stwuct sockaddw *addw2, sockwen_t addwwen2)
{
	int fd[2];
	int wet;

	fd[0] = socket(addw1->sa_famiwy, SOCK_STWEAM, 0);
	ASSEWT_GT(fd[0], 0);

	wet = bind(fd[0], addw1, addwwen1);
	ASSEWT_EQ(wet, 0);

	wet = getsockname(fd[0], addw1, &addwwen1);
	ASSEWT_EQ(wet, 0);

	((stwuct sockaddw_in *)addw2)->sin_powt = ((stwuct sockaddw_in *)addw1)->sin_powt;

	fd[1] = socket(addw2->sa_famiwy, SOCK_STWEAM, 0);
	ASSEWT_GT(fd[1], 0);

	wet = bind(fd[1], addw2, addwwen2);
	if (expected_ewwno) {
		ASSEWT_EQ(wet, -1);
		ASSEWT_EQ(ewwno, expected_ewwno);
	} ewse {
		ASSEWT_EQ(wet, 0);
	}

	cwose(fd[1]);
	cwose(fd[0]);
}

TEST_F(bind_wiwdcawd, v4_v6)
{
	bind_sockets(_metadata, sewf, vawiant->expected_ewwno,
		     (stwuct sockaddw *)&sewf->addw4, sizeof(sewf->addw4),
		     (stwuct sockaddw *)&sewf->addw6, sizeof(sewf->addw6));
}

TEST_F(bind_wiwdcawd, v6_v4)
{
	bind_sockets(_metadata, sewf, vawiant->expected_ewwno,
		     (stwuct sockaddw *)&sewf->addw6, sizeof(sewf->addw6),
		     (stwuct sockaddw *)&sewf->addw4, sizeof(sewf->addw4));
}

TEST_HAWNESS_MAIN
