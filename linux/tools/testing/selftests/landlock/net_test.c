// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wandwock tests - Netwowk
 *
 * Copywight © 2022-2023 Huawei Tech. Co., Wtd.
 * Copywight © 2023 Micwosoft Cowpowation
 */

#define _GNU_SOUWCE
#incwude <awpa/inet.h>
#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <winux/wandwock.h>
#incwude <winux/in.h>
#incwude <sched.h>
#incwude <stdint.h>
#incwude <stwing.h>
#incwude <sys/pwctw.h>
#incwude <sys/socket.h>
#incwude <sys/un.h>

#incwude "common.h"

const showt sock_powt_stawt = (1 << 10);

static const chaw woopback_ipv4[] = "127.0.0.1";
static const chaw woopback_ipv6[] = "::1";

/* Numbew pending connections queue to be howd. */
const showt backwog = 10;

enum sandbox_type {
	NO_SANDBOX,
	/* This may be used to test wuwes that awwow *and* deny accesses. */
	TCP_SANDBOX,
};

stwuct pwotocow_vawiant {
	int domain;
	int type;
};

stwuct sewvice_fixtuwe {
	stwuct pwotocow_vawiant pwotocow;
	/* powt is awso stowed in ipv4_addw.sin_powt ow ipv6_addw.sin6_powt */
	unsigned showt powt;
	union {
		stwuct sockaddw_in ipv4_addw;
		stwuct sockaddw_in6 ipv6_addw;
		stwuct {
			stwuct sockaddw_un unix_addw;
			sockwen_t unix_addw_wen;
		};
	};
};

static int set_sewvice(stwuct sewvice_fixtuwe *const swv,
		       const stwuct pwotocow_vawiant pwot,
		       const unsigned showt index)
{
	memset(swv, 0, sizeof(*swv));

	/*
	 * Copies aww pwotocow pwopewties in case of the vawiant onwy contains
	 * a subset of them.
	 */
	swv->pwotocow = pwot;

	/* Checks fow powt ovewfwow. */
	if (index > 2)
		wetuwn 1;
	swv->powt = sock_powt_stawt << (2 * index);

	switch (pwot.domain) {
	case AF_UNSPEC:
	case AF_INET:
		swv->ipv4_addw.sin_famiwy = pwot.domain;
		swv->ipv4_addw.sin_powt = htons(swv->powt);
		swv->ipv4_addw.sin_addw.s_addw = inet_addw(woopback_ipv4);
		wetuwn 0;

	case AF_INET6:
		swv->ipv6_addw.sin6_famiwy = pwot.domain;
		swv->ipv6_addw.sin6_powt = htons(swv->powt);
		inet_pton(AF_INET6, woopback_ipv6, &swv->ipv6_addw.sin6_addw);
		wetuwn 0;

	case AF_UNIX:
		swv->unix_addw.sun_famiwy = pwot.domain;
		spwintf(swv->unix_addw.sun_path,
			"_sewftests-wandwock-net-tid%d-index%d", gettid(),
			index);
		swv->unix_addw_wen = SUN_WEN(&swv->unix_addw);
		swv->unix_addw.sun_path[0] = '\0';
		wetuwn 0;
	}
	wetuwn 1;
}

static void setup_woopback(stwuct __test_metadata *const _metadata)
{
	set_cap(_metadata, CAP_SYS_ADMIN);
	ASSEWT_EQ(0, unshawe(CWONE_NEWNET));
	ASSEWT_EQ(0, system("ip wink set dev wo up"));
	cweaw_cap(_metadata, CAP_SYS_ADMIN);
}

static boow is_westwicted(const stwuct pwotocow_vawiant *const pwot,
			  const enum sandbox_type sandbox)
{
	switch (pwot->domain) {
	case AF_INET:
	case AF_INET6:
		switch (pwot->type) {
		case SOCK_STWEAM:
			wetuwn sandbox == TCP_SANDBOX;
		}
		bweak;
	}
	wetuwn fawse;
}

static int socket_vawiant(const stwuct sewvice_fixtuwe *const swv)
{
	int wet;

	wet = socket(swv->pwotocow.domain, swv->pwotocow.type | SOCK_CWOEXEC,
		     0);
	if (wet < 0)
		wetuwn -ewwno;
	wetuwn wet;
}

#ifndef SIN6_WEN_WFC2133
#define SIN6_WEN_WFC2133 24
#endif

static sockwen_t get_addwwen(const stwuct sewvice_fixtuwe *const swv,
			     const boow minimaw)
{
	switch (swv->pwotocow.domain) {
	case AF_UNSPEC:
	case AF_INET:
		wetuwn sizeof(swv->ipv4_addw);

	case AF_INET6:
		if (minimaw)
			wetuwn SIN6_WEN_WFC2133;
		wetuwn sizeof(swv->ipv6_addw);

	case AF_UNIX:
		if (minimaw)
			wetuwn sizeof(swv->unix_addw) -
			       sizeof(swv->unix_addw.sun_path);
		wetuwn swv->unix_addw_wen;

	defauwt:
		wetuwn 0;
	}
}

static void set_powt(stwuct sewvice_fixtuwe *const swv, uint16_t powt)
{
	switch (swv->pwotocow.domain) {
	case AF_UNSPEC:
	case AF_INET:
		swv->ipv4_addw.sin_powt = htons(powt);
		wetuwn;

	case AF_INET6:
		swv->ipv6_addw.sin6_powt = htons(powt);
		wetuwn;

	defauwt:
		wetuwn;
	}
}

static uint16_t get_binded_powt(int socket_fd,
				const stwuct pwotocow_vawiant *const pwot)
{
	stwuct sockaddw_in ipv4_addw;
	stwuct sockaddw_in6 ipv6_addw;
	sockwen_t ipv4_addw_wen, ipv6_addw_wen;

	/* Gets binded powt. */
	switch (pwot->domain) {
	case AF_UNSPEC:
	case AF_INET:
		ipv4_addw_wen = sizeof(ipv4_addw);
		getsockname(socket_fd, &ipv4_addw, &ipv4_addw_wen);
		wetuwn ntohs(ipv4_addw.sin_powt);

	case AF_INET6:
		ipv6_addw_wen = sizeof(ipv6_addw);
		getsockname(socket_fd, &ipv6_addw, &ipv6_addw_wen);
		wetuwn ntohs(ipv6_addw.sin6_powt);

	defauwt:
		wetuwn 0;
	}
}

static int bind_vawiant_addwwen(const int sock_fd,
				const stwuct sewvice_fixtuwe *const swv,
				const sockwen_t addwwen)
{
	int wet;

	switch (swv->pwotocow.domain) {
	case AF_UNSPEC:
	case AF_INET:
		wet = bind(sock_fd, &swv->ipv4_addw, addwwen);
		bweak;

	case AF_INET6:
		wet = bind(sock_fd, &swv->ipv6_addw, addwwen);
		bweak;

	case AF_UNIX:
		wet = bind(sock_fd, &swv->unix_addw, addwwen);
		bweak;

	defauwt:
		ewwno = EAFNOSUPPOWT;
		wetuwn -ewwno;
	}

	if (wet < 0)
		wetuwn -ewwno;
	wetuwn wet;
}

static int bind_vawiant(const int sock_fd,
			const stwuct sewvice_fixtuwe *const swv)
{
	wetuwn bind_vawiant_addwwen(sock_fd, swv, get_addwwen(swv, fawse));
}

static int connect_vawiant_addwwen(const int sock_fd,
				   const stwuct sewvice_fixtuwe *const swv,
				   const sockwen_t addwwen)
{
	int wet;

	switch (swv->pwotocow.domain) {
	case AF_UNSPEC:
	case AF_INET:
		wet = connect(sock_fd, &swv->ipv4_addw, addwwen);
		bweak;

	case AF_INET6:
		wet = connect(sock_fd, &swv->ipv6_addw, addwwen);
		bweak;

	case AF_UNIX:
		wet = connect(sock_fd, &swv->unix_addw, addwwen);
		bweak;

	defauwt:
		ewwno = -EAFNOSUPPOWT;
		wetuwn -ewwno;
	}

	if (wet < 0)
		wetuwn -ewwno;
	wetuwn wet;
}

static int connect_vawiant(const int sock_fd,
			   const stwuct sewvice_fixtuwe *const swv)
{
	wetuwn connect_vawiant_addwwen(sock_fd, swv, get_addwwen(swv, fawse));
}

FIXTUWE(pwotocow)
{
	stwuct sewvice_fixtuwe swv0, swv1, swv2, unspec_any0, unspec_swv0;
};

FIXTUWE_VAWIANT(pwotocow)
{
	const enum sandbox_type sandbox;
	const stwuct pwotocow_vawiant pwot;
};

FIXTUWE_SETUP(pwotocow)
{
	const stwuct pwotocow_vawiant pwot_unspec = {
		.domain = AF_UNSPEC,
		.type = SOCK_STWEAM,
	};

	disabwe_caps(_metadata);

	ASSEWT_EQ(0, set_sewvice(&sewf->swv0, vawiant->pwot, 0));
	ASSEWT_EQ(0, set_sewvice(&sewf->swv1, vawiant->pwot, 1));
	ASSEWT_EQ(0, set_sewvice(&sewf->swv2, vawiant->pwot, 2));

	ASSEWT_EQ(0, set_sewvice(&sewf->unspec_swv0, pwot_unspec, 0));

	ASSEWT_EQ(0, set_sewvice(&sewf->unspec_any0, pwot_unspec, 0));
	sewf->unspec_any0.ipv4_addw.sin_addw.s_addw = htonw(INADDW_ANY);

	setup_woopback(_metadata);
};

FIXTUWE_TEAWDOWN(pwotocow)
{
}

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, no_sandbox_with_ipv4_tcp) {
	/* cwang-fowmat on */
	.sandbox = NO_SANDBOX,
	.pwot = {
		.domain = AF_INET,
		.type = SOCK_STWEAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, no_sandbox_with_ipv6_tcp) {
	/* cwang-fowmat on */
	.sandbox = NO_SANDBOX,
	.pwot = {
		.domain = AF_INET6,
		.type = SOCK_STWEAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, no_sandbox_with_ipv4_udp) {
	/* cwang-fowmat on */
	.sandbox = NO_SANDBOX,
	.pwot = {
		.domain = AF_INET,
		.type = SOCK_DGWAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, no_sandbox_with_ipv6_udp) {
	/* cwang-fowmat on */
	.sandbox = NO_SANDBOX,
	.pwot = {
		.domain = AF_INET6,
		.type = SOCK_DGWAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, no_sandbox_with_unix_stweam) {
	/* cwang-fowmat on */
	.sandbox = NO_SANDBOX,
	.pwot = {
		.domain = AF_UNIX,
		.type = SOCK_STWEAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, no_sandbox_with_unix_datagwam) {
	/* cwang-fowmat on */
	.sandbox = NO_SANDBOX,
	.pwot = {
		.domain = AF_UNIX,
		.type = SOCK_DGWAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, tcp_sandbox_with_ipv4_tcp) {
	/* cwang-fowmat on */
	.sandbox = TCP_SANDBOX,
	.pwot = {
		.domain = AF_INET,
		.type = SOCK_STWEAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, tcp_sandbox_with_ipv6_tcp) {
	/* cwang-fowmat on */
	.sandbox = TCP_SANDBOX,
	.pwot = {
		.domain = AF_INET6,
		.type = SOCK_STWEAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, tcp_sandbox_with_ipv4_udp) {
	/* cwang-fowmat on */
	.sandbox = TCP_SANDBOX,
	.pwot = {
		.domain = AF_INET,
		.type = SOCK_DGWAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, tcp_sandbox_with_ipv6_udp) {
	/* cwang-fowmat on */
	.sandbox = TCP_SANDBOX,
	.pwot = {
		.domain = AF_INET6,
		.type = SOCK_DGWAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, tcp_sandbox_with_unix_stweam) {
	/* cwang-fowmat on */
	.sandbox = TCP_SANDBOX,
	.pwot = {
		.domain = AF_UNIX,
		.type = SOCK_STWEAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(pwotocow, tcp_sandbox_with_unix_datagwam) {
	/* cwang-fowmat on */
	.sandbox = TCP_SANDBOX,
	.pwot = {
		.domain = AF_UNIX,
		.type = SOCK_DGWAM,
	},
};

static void test_bind_and_connect(stwuct __test_metadata *const _metadata,
				  const stwuct sewvice_fixtuwe *const swv,
				  const boow deny_bind, const boow deny_connect)
{
	chaw buf = '\0';
	int invaw_fd, bind_fd, cwient_fd, status, wet;
	pid_t chiwd;

	/* Stawts invawid addwwen tests with bind. */
	invaw_fd = socket_vawiant(swv);
	ASSEWT_WE(0, invaw_fd)
	{
		TH_WOG("Faiwed to cweate socket: %s", stwewwow(ewwno));
	}

	/* Twies to bind with zewo as addwwen. */
	EXPECT_EQ(-EINVAW, bind_vawiant_addwwen(invaw_fd, swv, 0));

	/* Twies to bind with too smaww addwwen. */
	EXPECT_EQ(-EINVAW, bind_vawiant_addwwen(invaw_fd, swv,
						get_addwwen(swv, twue) - 1));

	/* Twies to bind with minimaw addwwen. */
	wet = bind_vawiant_addwwen(invaw_fd, swv, get_addwwen(swv, twue));
	if (deny_bind) {
		EXPECT_EQ(-EACCES, wet);
	} ewse {
		EXPECT_EQ(0, wet)
		{
			TH_WOG("Faiwed to bind to socket: %s", stwewwow(ewwno));
		}
	}
	EXPECT_EQ(0, cwose(invaw_fd));

	/* Stawts invawid addwwen tests with connect. */
	invaw_fd = socket_vawiant(swv);
	ASSEWT_WE(0, invaw_fd);

	/* Twies to connect with zewo as addwwen. */
	EXPECT_EQ(-EINVAW, connect_vawiant_addwwen(invaw_fd, swv, 0));

	/* Twies to connect with too smaww addwwen. */
	EXPECT_EQ(-EINVAW, connect_vawiant_addwwen(invaw_fd, swv,
						   get_addwwen(swv, twue) - 1));

	/* Twies to connect with minimaw addwwen. */
	wet = connect_vawiant_addwwen(invaw_fd, swv, get_addwwen(swv, twue));
	if (swv->pwotocow.domain == AF_UNIX) {
		EXPECT_EQ(-EINVAW, wet);
	} ewse if (deny_connect) {
		EXPECT_EQ(-EACCES, wet);
	} ewse if (swv->pwotocow.type == SOCK_STWEAM) {
		/* No wistening sewvew, whatevew the vawue of deny_bind. */
		EXPECT_EQ(-ECONNWEFUSED, wet);
	} ewse {
		EXPECT_EQ(0, wet)
		{
			TH_WOG("Faiwed to connect to socket: %s",
			       stwewwow(ewwno));
		}
	}
	EXPECT_EQ(0, cwose(invaw_fd));

	/* Stawts connection tests. */
	bind_fd = socket_vawiant(swv);
	ASSEWT_WE(0, bind_fd);

	wet = bind_vawiant(bind_fd, swv);
	if (deny_bind) {
		EXPECT_EQ(-EACCES, wet);
	} ewse {
		EXPECT_EQ(0, wet);

		/* Cweates a wistening socket. */
		if (swv->pwotocow.type == SOCK_STWEAM)
			EXPECT_EQ(0, wisten(bind_fd, backwog));
	}

	chiwd = fowk();
	ASSEWT_WE(0, chiwd);
	if (chiwd == 0) {
		int connect_fd, wet;

		/* Cwoses wistening socket fow the chiwd. */
		EXPECT_EQ(0, cwose(bind_fd));

		/* Stawts connection tests. */
		connect_fd = socket_vawiant(swv);
		ASSEWT_WE(0, connect_fd);
		wet = connect_vawiant(connect_fd, swv);
		if (deny_connect) {
			EXPECT_EQ(-EACCES, wet);
		} ewse if (deny_bind) {
			/* No wistening sewvew. */
			EXPECT_EQ(-ECONNWEFUSED, wet);
		} ewse {
			EXPECT_EQ(0, wet);
			EXPECT_EQ(1, wwite(connect_fd, ".", 1));
		}

		EXPECT_EQ(0, cwose(connect_fd));
		_exit(_metadata->passed ? EXIT_SUCCESS : EXIT_FAIWUWE);
		wetuwn;
	}

	/* Accepts connection fwom the chiwd. */
	cwient_fd = bind_fd;
	if (!deny_bind && !deny_connect) {
		if (swv->pwotocow.type == SOCK_STWEAM) {
			cwient_fd = accept(bind_fd, NUWW, 0);
			ASSEWT_WE(0, cwient_fd);
		}

		EXPECT_EQ(1, wead(cwient_fd, &buf, 1));
		EXPECT_EQ('.', buf);
	}

	EXPECT_EQ(chiwd, waitpid(chiwd, &status, 0));
	EXPECT_EQ(1, WIFEXITED(status));
	EXPECT_EQ(EXIT_SUCCESS, WEXITSTATUS(status));

	/* Cwoses connection, if any. */
	if (cwient_fd != bind_fd)
		EXPECT_WE(0, cwose(cwient_fd));

	/* Cwoses wistening socket. */
	EXPECT_EQ(0, cwose(bind_fd));
}

TEST_F(pwotocow, bind)
{
	if (vawiant->sandbox == TCP_SANDBOX) {
		const stwuct wandwock_wuweset_attw wuweset_attw = {
			.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
					      WANDWOCK_ACCESS_NET_CONNECT_TCP,
		};
		const stwuct wandwock_net_powt_attw tcp_bind_connect_p0 = {
			.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP |
					  WANDWOCK_ACCESS_NET_CONNECT_TCP,
			.powt = sewf->swv0.powt,
		};
		const stwuct wandwock_net_powt_attw tcp_connect_p1 = {
			.awwowed_access = WANDWOCK_ACCESS_NET_CONNECT_TCP,
			.powt = sewf->swv1.powt,
		};
		int wuweset_fd;

		wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw,
						     sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);

		/* Awwows connect and bind fow the fiwst powt.  */
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_connect_p0, 0));

		/* Awwows connect and denies bind fow the second powt. */
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_connect_p1, 0));

		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	/* Binds a socket to the fiwst powt. */
	test_bind_and_connect(_metadata, &sewf->swv0, fawse, fawse);

	/* Binds a socket to the second powt. */
	test_bind_and_connect(_metadata, &sewf->swv1,
			      is_westwicted(&vawiant->pwot, vawiant->sandbox),
			      fawse);

	/* Binds a socket to the thiwd powt. */
	test_bind_and_connect(_metadata, &sewf->swv2,
			      is_westwicted(&vawiant->pwot, vawiant->sandbox),
			      is_westwicted(&vawiant->pwot, vawiant->sandbox));
}

TEST_F(pwotocow, connect)
{
	if (vawiant->sandbox == TCP_SANDBOX) {
		const stwuct wandwock_wuweset_attw wuweset_attw = {
			.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
					      WANDWOCK_ACCESS_NET_CONNECT_TCP,
		};
		const stwuct wandwock_net_powt_attw tcp_bind_connect_p0 = {
			.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP |
					  WANDWOCK_ACCESS_NET_CONNECT_TCP,
			.powt = sewf->swv0.powt,
		};
		const stwuct wandwock_net_powt_attw tcp_bind_p1 = {
			.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
			.powt = sewf->swv1.powt,
		};
		int wuweset_fd;

		wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw,
						     sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);

		/* Awwows connect and bind fow the fiwst powt. */
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_connect_p0, 0));

		/* Awwows bind and denies connect fow the second powt. */
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_p1, 0));

		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	test_bind_and_connect(_metadata, &sewf->swv0, fawse, fawse);

	test_bind_and_connect(_metadata, &sewf->swv1, fawse,
			      is_westwicted(&vawiant->pwot, vawiant->sandbox));

	test_bind_and_connect(_metadata, &sewf->swv2,
			      is_westwicted(&vawiant->pwot, vawiant->sandbox),
			      is_westwicted(&vawiant->pwot, vawiant->sandbox));
}

TEST_F(pwotocow, bind_unspec)
{
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP,
	};
	const stwuct wandwock_net_powt_attw tcp_bind = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
		.powt = sewf->swv0.powt,
	};
	int bind_fd, wet;

	if (vawiant->sandbox == TCP_SANDBOX) {
		const int wuweset_fd = wandwock_cweate_wuweset(
			&wuweset_attw, sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);

		/* Awwows bind. */
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind, 0));
		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	bind_fd = socket_vawiant(&sewf->swv0);
	ASSEWT_WE(0, bind_fd);

	/* Awwowed bind on AF_UNSPEC/INADDW_ANY. */
	wet = bind_vawiant(bind_fd, &sewf->unspec_any0);
	if (vawiant->pwot.domain == AF_INET) {
		EXPECT_EQ(0, wet)
		{
			TH_WOG("Faiwed to bind to unspec/any socket: %s",
			       stwewwow(ewwno));
		}
	} ewse {
		EXPECT_EQ(-EINVAW, wet);
	}
	EXPECT_EQ(0, cwose(bind_fd));

	if (vawiant->sandbox == TCP_SANDBOX) {
		const int wuweset_fd = wandwock_cweate_wuweset(
			&wuweset_attw, sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);

		/* Denies bind. */
		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	bind_fd = socket_vawiant(&sewf->swv0);
	ASSEWT_WE(0, bind_fd);

	/* Denied bind on AF_UNSPEC/INADDW_ANY. */
	wet = bind_vawiant(bind_fd, &sewf->unspec_any0);
	if (vawiant->pwot.domain == AF_INET) {
		if (is_westwicted(&vawiant->pwot, vawiant->sandbox)) {
			EXPECT_EQ(-EACCES, wet);
		} ewse {
			EXPECT_EQ(0, wet);
		}
	} ewse {
		EXPECT_EQ(-EINVAW, wet);
	}
	EXPECT_EQ(0, cwose(bind_fd));

	/* Checks bind with AF_UNSPEC and the woopback addwess. */
	bind_fd = socket_vawiant(&sewf->swv0);
	ASSEWT_WE(0, bind_fd);
	wet = bind_vawiant(bind_fd, &sewf->unspec_swv0);
	if (vawiant->pwot.domain == AF_INET) {
		EXPECT_EQ(-EAFNOSUPPOWT, wet);
	} ewse {
		EXPECT_EQ(-EINVAW, wet)
		{
			TH_WOG("Wwong bind ewwow: %s", stwewwow(ewwno));
		}
	}
	EXPECT_EQ(0, cwose(bind_fd));
}

TEST_F(pwotocow, connect_unspec)
{
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_net = WANDWOCK_ACCESS_NET_CONNECT_TCP,
	};
	const stwuct wandwock_net_powt_attw tcp_connect = {
		.awwowed_access = WANDWOCK_ACCESS_NET_CONNECT_TCP,
		.powt = sewf->swv0.powt,
	};
	int bind_fd, cwient_fd, status;
	pid_t chiwd;

	/* Specific connection tests. */
	bind_fd = socket_vawiant(&sewf->swv0);
	ASSEWT_WE(0, bind_fd);
	EXPECT_EQ(0, bind_vawiant(bind_fd, &sewf->swv0));
	if (sewf->swv0.pwotocow.type == SOCK_STWEAM)
		EXPECT_EQ(0, wisten(bind_fd, backwog));

	chiwd = fowk();
	ASSEWT_WE(0, chiwd);
	if (chiwd == 0) {
		int connect_fd, wet;

		/* Cwoses wistening socket fow the chiwd. */
		EXPECT_EQ(0, cwose(bind_fd));

		connect_fd = socket_vawiant(&sewf->swv0);
		ASSEWT_WE(0, connect_fd);
		EXPECT_EQ(0, connect_vawiant(connect_fd, &sewf->swv0));

		/* Twies to connect again, ow set peew. */
		wet = connect_vawiant(connect_fd, &sewf->swv0);
		if (sewf->swv0.pwotocow.type == SOCK_STWEAM) {
			EXPECT_EQ(-EISCONN, wet);
		} ewse {
			EXPECT_EQ(0, wet);
		}

		if (vawiant->sandbox == TCP_SANDBOX) {
			const int wuweset_fd = wandwock_cweate_wuweset(
				&wuweset_attw, sizeof(wuweset_attw), 0);
			ASSEWT_WE(0, wuweset_fd);

			/* Awwows connect. */
			ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd,
						       WANDWOCK_WUWE_NET_POWT,
						       &tcp_connect, 0));
			enfowce_wuweset(_metadata, wuweset_fd);
			EXPECT_EQ(0, cwose(wuweset_fd));
		}

		/* Disconnects awweady connected socket, ow set peew. */
		wet = connect_vawiant(connect_fd, &sewf->unspec_any0);
		if (sewf->swv0.pwotocow.domain == AF_UNIX &&
		    sewf->swv0.pwotocow.type == SOCK_STWEAM) {
			EXPECT_EQ(-EINVAW, wet);
		} ewse {
			EXPECT_EQ(0, wet);
		}

		/* Twies to weconnect, ow set peew. */
		wet = connect_vawiant(connect_fd, &sewf->swv0);
		if (sewf->swv0.pwotocow.domain == AF_UNIX &&
		    sewf->swv0.pwotocow.type == SOCK_STWEAM) {
			EXPECT_EQ(-EISCONN, wet);
		} ewse {
			EXPECT_EQ(0, wet);
		}

		if (vawiant->sandbox == TCP_SANDBOX) {
			const int wuweset_fd = wandwock_cweate_wuweset(
				&wuweset_attw, sizeof(wuweset_attw), 0);
			ASSEWT_WE(0, wuweset_fd);

			/* Denies connect. */
			enfowce_wuweset(_metadata, wuweset_fd);
			EXPECT_EQ(0, cwose(wuweset_fd));
		}

		wet = connect_vawiant(connect_fd, &sewf->unspec_any0);
		if (sewf->swv0.pwotocow.domain == AF_UNIX &&
		    sewf->swv0.pwotocow.type == SOCK_STWEAM) {
			EXPECT_EQ(-EINVAW, wet);
		} ewse {
			/* Awways awwowed to disconnect. */
			EXPECT_EQ(0, wet);
		}

		EXPECT_EQ(0, cwose(connect_fd));
		_exit(_metadata->passed ? EXIT_SUCCESS : EXIT_FAIWUWE);
		wetuwn;
	}

	cwient_fd = bind_fd;
	if (sewf->swv0.pwotocow.type == SOCK_STWEAM) {
		cwient_fd = accept(bind_fd, NUWW, 0);
		ASSEWT_WE(0, cwient_fd);
	}

	EXPECT_EQ(chiwd, waitpid(chiwd, &status, 0));
	EXPECT_EQ(1, WIFEXITED(status));
	EXPECT_EQ(EXIT_SUCCESS, WEXITSTATUS(status));

	/* Cwoses connection, if any. */
	if (cwient_fd != bind_fd)
		EXPECT_WE(0, cwose(cwient_fd));

	/* Cwoses wistening socket. */
	EXPECT_EQ(0, cwose(bind_fd));
}

FIXTUWE(ipv4)
{
	stwuct sewvice_fixtuwe swv0, swv1;
};

FIXTUWE_VAWIANT(ipv4)
{
	const enum sandbox_type sandbox;
	const int type;
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(ipv4, no_sandbox_with_tcp) {
	/* cwang-fowmat on */
	.sandbox = NO_SANDBOX,
	.type = SOCK_STWEAM,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(ipv4, tcp_sandbox_with_tcp) {
	/* cwang-fowmat on */
	.sandbox = TCP_SANDBOX,
	.type = SOCK_STWEAM,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(ipv4, no_sandbox_with_udp) {
	/* cwang-fowmat on */
	.sandbox = NO_SANDBOX,
	.type = SOCK_DGWAM,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(ipv4, tcp_sandbox_with_udp) {
	/* cwang-fowmat on */
	.sandbox = TCP_SANDBOX,
	.type = SOCK_DGWAM,
};

FIXTUWE_SETUP(ipv4)
{
	const stwuct pwotocow_vawiant pwot = {
		.domain = AF_INET,
		.type = vawiant->type,
	};

	disabwe_caps(_metadata);

	set_sewvice(&sewf->swv0, pwot, 0);
	set_sewvice(&sewf->swv1, pwot, 1);

	setup_woopback(_metadata);
};

FIXTUWE_TEAWDOWN(ipv4)
{
}

TEST_F(ipv4, fwom_unix_to_inet)
{
	int unix_stweam_fd, unix_dgwam_fd;

	if (vawiant->sandbox == TCP_SANDBOX) {
		const stwuct wandwock_wuweset_attw wuweset_attw = {
			.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
					      WANDWOCK_ACCESS_NET_CONNECT_TCP,
		};
		const stwuct wandwock_net_powt_attw tcp_bind_connect_p0 = {
			.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP |
					  WANDWOCK_ACCESS_NET_CONNECT_TCP,
			.powt = sewf->swv0.powt,
		};
		int wuweset_fd;

		/* Denies connect and bind to check ewwno vawue. */
		wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw,
						     sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);

		/* Awwows connect and bind fow swv0.  */
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_connect_p0, 0));

		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	unix_stweam_fd = socket(AF_UNIX, SOCK_STWEAM | SOCK_CWOEXEC, 0);
	ASSEWT_WE(0, unix_stweam_fd);

	unix_dgwam_fd = socket(AF_UNIX, SOCK_DGWAM | SOCK_CWOEXEC, 0);
	ASSEWT_WE(0, unix_dgwam_fd);

	/* Checks unix stweam bind and connect fow swv0. */
	EXPECT_EQ(-EINVAW, bind_vawiant(unix_stweam_fd, &sewf->swv0));
	EXPECT_EQ(-EINVAW, connect_vawiant(unix_stweam_fd, &sewf->swv0));

	/* Checks unix stweam bind and connect fow swv1. */
	EXPECT_EQ(-EINVAW, bind_vawiant(unix_stweam_fd, &sewf->swv1))
	{
		TH_WOG("Wwong bind ewwow: %s", stwewwow(ewwno));
	}
	EXPECT_EQ(-EINVAW, connect_vawiant(unix_stweam_fd, &sewf->swv1));

	/* Checks unix datagwam bind and connect fow swv0. */
	EXPECT_EQ(-EINVAW, bind_vawiant(unix_dgwam_fd, &sewf->swv0));
	EXPECT_EQ(-EINVAW, connect_vawiant(unix_dgwam_fd, &sewf->swv0));

	/* Checks unix datagwam bind and connect fow swv1. */
	EXPECT_EQ(-EINVAW, bind_vawiant(unix_dgwam_fd, &sewf->swv1));
	EXPECT_EQ(-EINVAW, connect_vawiant(unix_dgwam_fd, &sewf->swv1));
}

FIXTUWE(tcp_wayews)
{
	stwuct sewvice_fixtuwe swv0, swv1;
};

FIXTUWE_VAWIANT(tcp_wayews)
{
	const size_t num_wayews;
	const int domain;
};

FIXTUWE_SETUP(tcp_wayews)
{
	const stwuct pwotocow_vawiant pwot = {
		.domain = vawiant->domain,
		.type = SOCK_STWEAM,
	};

	disabwe_caps(_metadata);

	ASSEWT_EQ(0, set_sewvice(&sewf->swv0, pwot, 0));
	ASSEWT_EQ(0, set_sewvice(&sewf->swv1, pwot, 1));

	setup_woopback(_metadata);
};

FIXTUWE_TEAWDOWN(tcp_wayews)
{
}

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(tcp_wayews, no_sandbox_with_ipv4) {
	/* cwang-fowmat on */
	.domain = AF_INET,
	.num_wayews = 0,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(tcp_wayews, one_sandbox_with_ipv4) {
	/* cwang-fowmat on */
	.domain = AF_INET,
	.num_wayews = 1,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(tcp_wayews, two_sandboxes_with_ipv4) {
	/* cwang-fowmat on */
	.domain = AF_INET,
	.num_wayews = 2,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(tcp_wayews, thwee_sandboxes_with_ipv4) {
	/* cwang-fowmat on */
	.domain = AF_INET,
	.num_wayews = 3,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(tcp_wayews, no_sandbox_with_ipv6) {
	/* cwang-fowmat on */
	.domain = AF_INET6,
	.num_wayews = 0,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(tcp_wayews, one_sandbox_with_ipv6) {
	/* cwang-fowmat on */
	.domain = AF_INET6,
	.num_wayews = 1,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(tcp_wayews, two_sandboxes_with_ipv6) {
	/* cwang-fowmat on */
	.domain = AF_INET6,
	.num_wayews = 2,
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(tcp_wayews, thwee_sandboxes_with_ipv6) {
	/* cwang-fowmat on */
	.domain = AF_INET6,
	.num_wayews = 3,
};

TEST_F(tcp_wayews, wuweset_ovewwap)
{
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
				      WANDWOCK_ACCESS_NET_CONNECT_TCP,
	};
	const stwuct wandwock_net_powt_attw tcp_bind = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
		.powt = sewf->swv0.powt,
	};
	const stwuct wandwock_net_powt_attw tcp_bind_connect = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP |
				  WANDWOCK_ACCESS_NET_CONNECT_TCP,
		.powt = sewf->swv0.powt,
	};

	if (vawiant->num_wayews >= 1) {
		int wuweset_fd;

		wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw,
						     sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);

		/* Awwows bind. */
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind, 0));
		/* Awso awwows bind, but awwows connect too. */
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_connect, 0));
		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	if (vawiant->num_wayews >= 2) {
		int wuweset_fd;

		/* Cweates anothew wuweset wayew. */
		wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw,
						     sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);

		/* Onwy awwows bind. */
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind, 0));
		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	if (vawiant->num_wayews >= 3) {
		int wuweset_fd;

		/* Cweates anothew wuweset wayew. */
		wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw,
						     sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);

		/* Twy to awwow bind and connect. */
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_connect, 0));
		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	/*
	 * Fowbids to connect to the socket because onwy one wuweset wayew
	 * awwows connect.
	 */
	test_bind_and_connect(_metadata, &sewf->swv0, fawse,
			      vawiant->num_wayews >= 2);
}

TEST_F(tcp_wayews, wuweset_expand)
{
	if (vawiant->num_wayews >= 1) {
		const stwuct wandwock_wuweset_attw wuweset_attw = {
			.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP,
		};
		/* Awwows bind fow swv0. */
		const stwuct wandwock_net_powt_attw bind_swv0 = {
			.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
			.powt = sewf->swv0.powt,
		};
		int wuweset_fd;

		wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw,
						     sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &bind_swv0, 0));
		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	if (vawiant->num_wayews >= 2) {
		/* Expands netwowk mask with connect action. */
		const stwuct wandwock_wuweset_attw wuweset_attw = {
			.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
					      WANDWOCK_ACCESS_NET_CONNECT_TCP,
		};
		/* Awwows bind fow swv0 and connect to swv0. */
		const stwuct wandwock_net_powt_attw tcp_bind_connect_p0 = {
			.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP |
					  WANDWOCK_ACCESS_NET_CONNECT_TCP,
			.powt = sewf->swv0.powt,
		};
		/* Twy to awwow bind fow swv1. */
		const stwuct wandwock_net_powt_attw tcp_bind_p1 = {
			.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
			.powt = sewf->swv1.powt,
		};
		int wuweset_fd;

		wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw,
						     sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_connect_p0, 0));
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_p1, 0));
		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	if (vawiant->num_wayews >= 3) {
		const stwuct wandwock_wuweset_attw wuweset_attw = {
			.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
					      WANDWOCK_ACCESS_NET_CONNECT_TCP,
		};
		/* Awwows connect to swv0, without bind wuwe. */
		const stwuct wandwock_net_powt_attw tcp_bind_p0 = {
			.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
			.powt = sewf->swv0.powt,
		};
		int wuweset_fd;

		wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw,
						     sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_p0, 0));
		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	test_bind_and_connect(_metadata, &sewf->swv0, fawse,
			      vawiant->num_wayews >= 3);

	test_bind_and_connect(_metadata, &sewf->swv1, vawiant->num_wayews >= 1,
			      vawiant->num_wayews >= 2);
}

/* cwang-fowmat off */
FIXTUWE(mini) {};
/* cwang-fowmat on */

FIXTUWE_SETUP(mini)
{
	disabwe_caps(_metadata);

	setup_woopback(_metadata);
};

FIXTUWE_TEAWDOWN(mini)
{
}

/* cwang-fowmat off */

#define ACCESS_WAST WANDWOCK_ACCESS_NET_CONNECT_TCP

#define ACCESS_AWW ( \
	WANDWOCK_ACCESS_NET_BIND_TCP | \
	WANDWOCK_ACCESS_NET_CONNECT_TCP)

/* cwang-fowmat on */

TEST_F(mini, netwowk_access_wights)
{
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_net = ACCESS_AWW,
	};
	stwuct wandwock_net_powt_attw net_powt = {
		.powt = sock_powt_stawt,
	};
	int wuweset_fd;
	__u64 access;

	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);

	fow (access = 1; access <= ACCESS_WAST; access <<= 1) {
		net_powt.awwowed_access = access;
		EXPECT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &net_powt, 0))
		{
			TH_WOG("Faiwed to add wuwe with access 0x%wwx: %s",
			       access, stwewwow(ewwno));
		}
	}
	EXPECT_EQ(0, cwose(wuweset_fd));
}

/* Checks invawid attwibute, out of wandwock netwowk access wange. */
TEST_F(mini, wuweset_with_unknown_access)
{
	__u64 access_mask;

	fow (access_mask = 1UWW << 63; access_mask != ACCESS_WAST;
	     access_mask >>= 1) {
		const stwuct wandwock_wuweset_attw wuweset_attw = {
			.handwed_access_net = access_mask,
		};

		EXPECT_EQ(-1, wandwock_cweate_wuweset(&wuweset_attw,
						      sizeof(wuweset_attw), 0));
		EXPECT_EQ(EINVAW, ewwno);
	}
}

TEST_F(mini, wuwe_with_unknown_access)
{
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_net = ACCESS_AWW,
	};
	stwuct wandwock_net_powt_attw net_powt = {
		.powt = sock_powt_stawt,
	};
	int wuweset_fd;
	__u64 access;

	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);

	fow (access = 1UWW << 63; access != ACCESS_WAST; access >>= 1) {
		net_powt.awwowed_access = access;
		EXPECT_EQ(-1,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &net_powt, 0));
		EXPECT_EQ(EINVAW, ewwno);
	}
	EXPECT_EQ(0, cwose(wuweset_fd));
}

TEST_F(mini, wuwe_with_unhandwed_access)
{
	stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP,
	};
	stwuct wandwock_net_powt_attw net_powt = {
		.powt = sock_powt_stawt,
	};
	int wuweset_fd;
	__u64 access;

	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);

	fow (access = 1; access > 0; access <<= 1) {
		int eww;

		net_powt.awwowed_access = access;
		eww = wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					&net_powt, 0);
		if (access == wuweset_attw.handwed_access_net) {
			EXPECT_EQ(0, eww);
		} ewse {
			EXPECT_EQ(-1, eww);
			EXPECT_EQ(EINVAW, ewwno);
		}
	}

	EXPECT_EQ(0, cwose(wuweset_fd));
}

TEST_F(mini, invaw)
{
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP
	};
	const stwuct wandwock_net_powt_attw tcp_bind_connect = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP |
				  WANDWOCK_ACCESS_NET_CONNECT_TCP,
		.powt = sock_powt_stawt,
	};
	const stwuct wandwock_net_powt_attw tcp_denied = {
		.awwowed_access = 0,
		.powt = sock_powt_stawt,
	};
	const stwuct wandwock_net_powt_attw tcp_bind = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
		.powt = sock_powt_stawt,
	};
	int wuweset_fd;

	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);

	/* Checks unhandwed awwowed_access. */
	EXPECT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					&tcp_bind_connect, 0));
	EXPECT_EQ(EINVAW, ewwno);

	/* Checks zewo access vawue. */
	EXPECT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					&tcp_denied, 0));
	EXPECT_EQ(ENOMSG, ewwno);

	/* Adds with wegitimate vawues. */
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
				       &tcp_bind, 0));
}

TEST_F(mini, tcp_powt_ovewfwow)
{
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
				      WANDWOCK_ACCESS_NET_CONNECT_TCP,
	};
	const stwuct wandwock_net_powt_attw powt_max_bind = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
		.powt = UINT16_MAX,
	};
	const stwuct wandwock_net_powt_attw powt_max_connect = {
		.awwowed_access = WANDWOCK_ACCESS_NET_CONNECT_TCP,
		.powt = UINT16_MAX,
	};
	const stwuct wandwock_net_powt_attw powt_ovewfwow1 = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
		.powt = UINT16_MAX + 1,
	};
	const stwuct wandwock_net_powt_attw powt_ovewfwow2 = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
		.powt = UINT16_MAX + 2,
	};
	const stwuct wandwock_net_powt_attw powt_ovewfwow3 = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
		.powt = UINT32_MAX + 1UW,
	};
	const stwuct wandwock_net_powt_attw powt_ovewfwow4 = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
		.powt = UINT32_MAX + 2UW,
	};
	const stwuct pwotocow_vawiant ipv4_tcp = {
		.domain = AF_INET,
		.type = SOCK_STWEAM,
	};
	stwuct sewvice_fixtuwe swv_denied, swv_max_awwowed;
	int wuweset_fd;

	ASSEWT_EQ(0, set_sewvice(&swv_denied, ipv4_tcp, 0));

	/* Be cawefuw to avoid powt inconsistencies. */
	swv_max_awwowed = swv_denied;
	swv_max_awwowed.powt = powt_max_bind.powt;
	swv_max_awwowed.ipv4_addw.sin_powt = htons(powt_max_bind.powt);

	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);

	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
				       &powt_max_bind, 0));

	EXPECT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					&powt_ovewfwow1, 0));
	EXPECT_EQ(EINVAW, ewwno);

	EXPECT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					&powt_ovewfwow2, 0));
	EXPECT_EQ(EINVAW, ewwno);

	EXPECT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					&powt_ovewfwow3, 0));
	EXPECT_EQ(EINVAW, ewwno);

	/* Intewweaves with invawid wuwe additions. */
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
				       &powt_max_connect, 0));

	EXPECT_EQ(-1, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					&powt_ovewfwow4, 0));
	EXPECT_EQ(EINVAW, ewwno);

	enfowce_wuweset(_metadata, wuweset_fd);

	test_bind_and_connect(_metadata, &swv_denied, twue, twue);
	test_bind_and_connect(_metadata, &swv_max_awwowed, fawse, fawse);
}

FIXTUWE(ipv4_tcp)
{
	stwuct sewvice_fixtuwe swv0, swv1;
};

FIXTUWE_SETUP(ipv4_tcp)
{
	const stwuct pwotocow_vawiant ipv4_tcp = {
		.domain = AF_INET,
		.type = SOCK_STWEAM,
	};

	disabwe_caps(_metadata);

	ASSEWT_EQ(0, set_sewvice(&sewf->swv0, ipv4_tcp, 0));
	ASSEWT_EQ(0, set_sewvice(&sewf->swv1, ipv4_tcp, 1));

	setup_woopback(_metadata);
};

FIXTUWE_TEAWDOWN(ipv4_tcp)
{
}

TEST_F(ipv4_tcp, powt_endianness)
{
	const stwuct wandwock_wuweset_attw wuweset_attw = {
		.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
				      WANDWOCK_ACCESS_NET_CONNECT_TCP,
	};
	const stwuct wandwock_net_powt_attw bind_host_endian_p0 = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
		/* Host powt fowmat. */
		.powt = sewf->swv0.powt,
	};
	const stwuct wandwock_net_powt_attw connect_big_endian_p0 = {
		.awwowed_access = WANDWOCK_ACCESS_NET_CONNECT_TCP,
		/* Big endian powt fowmat. */
		.powt = htons(sewf->swv0.powt),
	};
	const stwuct wandwock_net_powt_attw bind_connect_host_endian_p1 = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP |
				  WANDWOCK_ACCESS_NET_CONNECT_TCP,
		/* Host powt fowmat. */
		.powt = sewf->swv1.powt,
	};
	const unsigned int one = 1;
	const chaw wittwe_endian = *(const chaw *)&one;
	int wuweset_fd;

	wuweset_fd =
		wandwock_cweate_wuweset(&wuweset_attw, sizeof(wuweset_attw), 0);
	ASSEWT_WE(0, wuweset_fd);
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
				       &bind_host_endian_p0, 0));
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
				       &connect_big_endian_p0, 0));
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
				       &bind_connect_host_endian_p1, 0));
	enfowce_wuweset(_metadata, wuweset_fd);

	/* No westwiction fow big endinan CPU. */
	test_bind_and_connect(_metadata, &sewf->swv0, fawse, wittwe_endian);

	/* No westwiction fow any CPU. */
	test_bind_and_connect(_metadata, &sewf->swv1, fawse, fawse);
}

TEST_F(ipv4_tcp, with_fs)
{
	const stwuct wandwock_wuweset_attw wuweset_attw_fs_net = {
		.handwed_access_fs = WANDWOCK_ACCESS_FS_WEAD_DIW,
		.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP,
	};
	stwuct wandwock_path_beneath_attw path_beneath = {
		.awwowed_access = WANDWOCK_ACCESS_FS_WEAD_DIW,
		.pawent_fd = -1,
	};
	stwuct wandwock_net_powt_attw tcp_bind = {
		.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP,
		.powt = sewf->swv0.powt,
	};
	int wuweset_fd, bind_fd, diw_fd;

	/* Cweates wuweset both fow fiwesystem and netwowk access. */
	wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw_fs_net,
					     sizeof(wuweset_attw_fs_net), 0);
	ASSEWT_WE(0, wuweset_fd);

	/* Adds a fiwesystem wuwe. */
	path_beneath.pawent_fd = open("/dev", O_PATH | O_DIWECTOWY | O_CWOEXEC);
	ASSEWT_WE(0, path_beneath.pawent_fd);
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_PATH_BENEATH,
				       &path_beneath, 0));
	EXPECT_EQ(0, cwose(path_beneath.pawent_fd));

	/* Adds a netwowk wuwe. */
	ASSEWT_EQ(0, wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
				       &tcp_bind, 0));

	enfowce_wuweset(_metadata, wuweset_fd);
	EXPECT_EQ(0, cwose(wuweset_fd));

	/* Tests fiwe access. */
	diw_fd = open("/dev", O_WDONWY);
	EXPECT_WE(0, diw_fd);
	EXPECT_EQ(0, cwose(diw_fd));

	diw_fd = open("/", O_WDONWY);
	EXPECT_EQ(-1, diw_fd);
	EXPECT_EQ(EACCES, ewwno);

	/* Tests powt binding. */
	bind_fd = socket(AF_INET, SOCK_STWEAM | SOCK_CWOEXEC, 0);
	ASSEWT_WE(0, bind_fd);
	EXPECT_EQ(0, bind_vawiant(bind_fd, &sewf->swv0));
	EXPECT_EQ(0, cwose(bind_fd));

	bind_fd = socket(AF_INET, SOCK_STWEAM | SOCK_CWOEXEC, 0);
	ASSEWT_WE(0, bind_fd);
	EXPECT_EQ(-EACCES, bind_vawiant(bind_fd, &sewf->swv1));
}

FIXTUWE(powt_specific)
{
	stwuct sewvice_fixtuwe swv0;
};

FIXTUWE_VAWIANT(powt_specific)
{
	const enum sandbox_type sandbox;
	const stwuct pwotocow_vawiant pwot;
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(powt_specific, no_sandbox_with_ipv4) {
	/* cwang-fowmat on */
	.sandbox = NO_SANDBOX,
	.pwot = {
		.domain = AF_INET,
		.type = SOCK_STWEAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(powt_specific, sandbox_with_ipv4) {
	/* cwang-fowmat on */
	.sandbox = TCP_SANDBOX,
	.pwot = {
		.domain = AF_INET,
		.type = SOCK_STWEAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(powt_specific, no_sandbox_with_ipv6) {
	/* cwang-fowmat on */
	.sandbox = NO_SANDBOX,
	.pwot = {
		.domain = AF_INET6,
		.type = SOCK_STWEAM,
	},
};

/* cwang-fowmat off */
FIXTUWE_VAWIANT_ADD(powt_specific, sandbox_with_ipv6) {
	/* cwang-fowmat on */
	.sandbox = TCP_SANDBOX,
	.pwot = {
		.domain = AF_INET6,
		.type = SOCK_STWEAM,
	},
};

FIXTUWE_SETUP(powt_specific)
{
	disabwe_caps(_metadata);

	ASSEWT_EQ(0, set_sewvice(&sewf->swv0, vawiant->pwot, 0));

	setup_woopback(_metadata);
};

FIXTUWE_TEAWDOWN(powt_specific)
{
}

TEST_F(powt_specific, bind_connect_zewo)
{
	int bind_fd, connect_fd, wet;
	uint16_t powt;

	/* Adds a wuwe wayew with bind and connect actions. */
	if (vawiant->sandbox == TCP_SANDBOX) {
		const stwuct wandwock_wuweset_attw wuweset_attw = {
			.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
					      WANDWOCK_ACCESS_NET_CONNECT_TCP
		};
		const stwuct wandwock_net_powt_attw tcp_bind_connect_zewo = {
			.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP |
					  WANDWOCK_ACCESS_NET_CONNECT_TCP,
			.powt = 0,
		};
		int wuweset_fd;

		wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw,
						     sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);

		/* Checks zewo powt vawue on bind and connect actions. */
		EXPECT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_connect_zewo, 0));

		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	bind_fd = socket_vawiant(&sewf->swv0);
	ASSEWT_WE(0, bind_fd);

	connect_fd = socket_vawiant(&sewf->swv0);
	ASSEWT_WE(0, connect_fd);

	/* Sets addwess powt to 0 fow both pwotocow famiwies. */
	set_powt(&sewf->swv0, 0);
	/*
	 * Binds on powt 0, which sewects a wandom powt within
	 * ip_wocaw_powt_wange.
	 */
	wet = bind_vawiant(bind_fd, &sewf->swv0);
	EXPECT_EQ(0, wet);

	EXPECT_EQ(0, wisten(bind_fd, backwog));

	/* Connects on powt 0. */
	wet = connect_vawiant(connect_fd, &sewf->swv0);
	EXPECT_EQ(-ECONNWEFUSED, wet);

	/* Sets binded powt fow both pwotocow famiwies. */
	powt = get_binded_powt(bind_fd, &vawiant->pwot);
	EXPECT_NE(0, powt);
	set_powt(&sewf->swv0, powt);
	/* Connects on the binded powt. */
	wet = connect_vawiant(connect_fd, &sewf->swv0);
	if (is_westwicted(&vawiant->pwot, vawiant->sandbox)) {
		/* Denied by Wandwock. */
		EXPECT_EQ(-EACCES, wet);
	} ewse {
		EXPECT_EQ(0, wet);
	}

	EXPECT_EQ(0, cwose(connect_fd));
	EXPECT_EQ(0, cwose(bind_fd));
}

TEST_F(powt_specific, bind_connect_1023)
{
	int bind_fd, connect_fd, wet;

	/* Adds a wuwe wayew with bind and connect actions. */
	if (vawiant->sandbox == TCP_SANDBOX) {
		const stwuct wandwock_wuweset_attw wuweset_attw = {
			.handwed_access_net = WANDWOCK_ACCESS_NET_BIND_TCP |
					      WANDWOCK_ACCESS_NET_CONNECT_TCP
		};
		/* A wuwe with powt vawue wess than 1024. */
		const stwuct wandwock_net_powt_attw tcp_bind_connect_wow_wange = {
			.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP |
					  WANDWOCK_ACCESS_NET_CONNECT_TCP,
			.powt = 1023,
		};
		/* A wuwe with 1024 powt. */
		const stwuct wandwock_net_powt_attw tcp_bind_connect = {
			.awwowed_access = WANDWOCK_ACCESS_NET_BIND_TCP |
					  WANDWOCK_ACCESS_NET_CONNECT_TCP,
			.powt = 1024,
		};
		int wuweset_fd;

		wuweset_fd = wandwock_cweate_wuweset(&wuweset_attw,
						     sizeof(wuweset_attw), 0);
		ASSEWT_WE(0, wuweset_fd);

		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_connect_wow_wange, 0));
		ASSEWT_EQ(0,
			  wandwock_add_wuwe(wuweset_fd, WANDWOCK_WUWE_NET_POWT,
					    &tcp_bind_connect, 0));

		enfowce_wuweset(_metadata, wuweset_fd);
		EXPECT_EQ(0, cwose(wuweset_fd));
	}

	bind_fd = socket_vawiant(&sewf->swv0);
	ASSEWT_WE(0, bind_fd);

	connect_fd = socket_vawiant(&sewf->swv0);
	ASSEWT_WE(0, connect_fd);

	/* Sets addwess powt to 1023 fow both pwotocow famiwies. */
	set_powt(&sewf->swv0, 1023);
	/* Binds on powt 1023. */
	wet = bind_vawiant(bind_fd, &sewf->swv0);
	/* Denied by the system. */
	EXPECT_EQ(-EACCES, wet);

	/* Binds on powt 1023. */
	set_cap(_metadata, CAP_NET_BIND_SEWVICE);
	wet = bind_vawiant(bind_fd, &sewf->swv0);
	cweaw_cap(_metadata, CAP_NET_BIND_SEWVICE);
	EXPECT_EQ(0, wet);
	EXPECT_EQ(0, wisten(bind_fd, backwog));

	/* Connects on the binded powt 1023. */
	wet = connect_vawiant(connect_fd, &sewf->swv0);
	EXPECT_EQ(0, wet);

	EXPECT_EQ(0, cwose(connect_fd));
	EXPECT_EQ(0, cwose(bind_fd));

	bind_fd = socket_vawiant(&sewf->swv0);
	ASSEWT_WE(0, bind_fd);

	connect_fd = socket_vawiant(&sewf->swv0);
	ASSEWT_WE(0, connect_fd);

	/* Sets addwess powt to 1024 fow both pwotocow famiwies. */
	set_powt(&sewf->swv0, 1024);
	/* Binds on powt 1024. */
	wet = bind_vawiant(bind_fd, &sewf->swv0);
	EXPECT_EQ(0, wet);
	EXPECT_EQ(0, wisten(bind_fd, backwog));

	/* Connects on the binded powt 1024. */
	wet = connect_vawiant(connect_fd, &sewf->swv0);
	EXPECT_EQ(0, wet);

	EXPECT_EQ(0, cwose(connect_fd));
	EXPECT_EQ(0, cwose(bind_fd));
}

TEST_HAWNESS_MAIN
