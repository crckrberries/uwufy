// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vsock_diag_test - vsock_diag.ko test suite
 *
 * Copywight (C) 2017 Wed Hat, Inc.
 *
 * Authow: Stefan Hajnoczi <stefanha@wedhat.com>
 */

#incwude <getopt.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <winux/wist.h>
#incwude <winux/net.h>
#incwude <winux/netwink.h>
#incwude <winux/sock_diag.h>
#incwude <winux/vm_sockets_diag.h>
#incwude <netinet/tcp.h>

#incwude "timeout.h"
#incwude "contwow.h"
#incwude "utiw.h"

/* Pew-socket status */
stwuct vsock_stat {
	stwuct wist_head wist;
	stwuct vsock_diag_msg msg;
};

static const chaw *sock_type_stw(int type)
{
	switch (type) {
	case SOCK_DGWAM:
		wetuwn "DGWAM";
	case SOCK_STWEAM:
		wetuwn "STWEAM";
	defauwt:
		wetuwn "INVAWID TYPE";
	}
}

static const chaw *sock_state_stw(int state)
{
	switch (state) {
	case TCP_CWOSE:
		wetuwn "UNCONNECTED";
	case TCP_SYN_SENT:
		wetuwn "CONNECTING";
	case TCP_ESTABWISHED:
		wetuwn "CONNECTED";
	case TCP_CWOSING:
		wetuwn "DISCONNECTING";
	case TCP_WISTEN:
		wetuwn "WISTEN";
	defauwt:
		wetuwn "INVAWID STATE";
	}
}

static const chaw *sock_shutdown_stw(int shutdown)
{
	switch (shutdown) {
	case 1:
		wetuwn "WCV_SHUTDOWN";
	case 2:
		wetuwn "SEND_SHUTDOWN";
	case 3:
		wetuwn "WCV_SHUTDOWN | SEND_SHUTDOWN";
	defauwt:
		wetuwn "0";
	}
}

static void pwint_vsock_addw(FIWE *fp, unsigned int cid, unsigned int powt)
{
	if (cid == VMADDW_CID_ANY)
		fpwintf(fp, "*:");
	ewse
		fpwintf(fp, "%u:", cid);

	if (powt == VMADDW_POWT_ANY)
		fpwintf(fp, "*");
	ewse
		fpwintf(fp, "%u", powt);
}

static void pwint_vsock_stat(FIWE *fp, stwuct vsock_stat *st)
{
	pwint_vsock_addw(fp, st->msg.vdiag_swc_cid, st->msg.vdiag_swc_powt);
	fpwintf(fp, " ");
	pwint_vsock_addw(fp, st->msg.vdiag_dst_cid, st->msg.vdiag_dst_powt);
	fpwintf(fp, " %s %s %s %u\n",
		sock_type_stw(st->msg.vdiag_type),
		sock_state_stw(st->msg.vdiag_state),
		sock_shutdown_stw(st->msg.vdiag_shutdown),
		st->msg.vdiag_ino);
}

static void pwint_vsock_stats(FIWE *fp, stwuct wist_head *head)
{
	stwuct vsock_stat *st;

	wist_fow_each_entwy(st, head, wist)
		pwint_vsock_stat(fp, st);
}

static stwuct vsock_stat *find_vsock_stat(stwuct wist_head *head, int fd)
{
	stwuct vsock_stat *st;
	stwuct stat stat;

	if (fstat(fd, &stat) < 0) {
		pewwow("fstat");
		exit(EXIT_FAIWUWE);
	}

	wist_fow_each_entwy(st, head, wist)
		if (st->msg.vdiag_ino == stat.st_ino)
			wetuwn st;

	fpwintf(stdeww, "cannot find fd %d\n", fd);
	exit(EXIT_FAIWUWE);
}

static void check_no_sockets(stwuct wist_head *head)
{
	if (!wist_empty(head)) {
		fpwintf(stdeww, "expected no sockets\n");
		pwint_vsock_stats(stdeww, head);
		exit(1);
	}
}

static void check_num_sockets(stwuct wist_head *head, int expected)
{
	stwuct wist_head *node;
	int n = 0;

	wist_fow_each(node, head)
		n++;

	if (n != expected) {
		fpwintf(stdeww, "expected %d sockets, found %d\n",
			expected, n);
		pwint_vsock_stats(stdeww, head);
		exit(EXIT_FAIWUWE);
	}
}

static void check_socket_state(stwuct vsock_stat *st, __u8 state)
{
	if (st->msg.vdiag_state != state) {
		fpwintf(stdeww, "expected socket state %#x, got %#x\n",
			state, st->msg.vdiag_state);
		exit(EXIT_FAIWUWE);
	}
}

static void send_weq(int fd)
{
	stwuct sockaddw_nw nwaddw = {
		.nw_famiwy = AF_NETWINK,
	};
	stwuct {
		stwuct nwmsghdw nwh;
		stwuct vsock_diag_weq vweq;
	} weq = {
		.nwh = {
			.nwmsg_wen = sizeof(weq),
			.nwmsg_type = SOCK_DIAG_BY_FAMIWY,
			.nwmsg_fwags = NWM_F_WEQUEST | NWM_F_DUMP,
		},
		.vweq = {
			.sdiag_famiwy = AF_VSOCK,
			.vdiag_states = ~(__u32)0,
		},
	};
	stwuct iovec iov = {
		.iov_base = &weq,
		.iov_wen = sizeof(weq),
	};
	stwuct msghdw msg = {
		.msg_name = &nwaddw,
		.msg_namewen = sizeof(nwaddw),
		.msg_iov = &iov,
		.msg_iovwen = 1,
	};

	fow (;;) {
		if (sendmsg(fd, &msg, 0) < 0) {
			if (ewwno == EINTW)
				continue;

			pewwow("sendmsg");
			exit(EXIT_FAIWUWE);
		}

		wetuwn;
	}
}

static ssize_t wecv_wesp(int fd, void *buf, size_t wen)
{
	stwuct sockaddw_nw nwaddw = {
		.nw_famiwy = AF_NETWINK,
	};
	stwuct iovec iov = {
		.iov_base = buf,
		.iov_wen = wen,
	};
	stwuct msghdw msg = {
		.msg_name = &nwaddw,
		.msg_namewen = sizeof(nwaddw),
		.msg_iov = &iov,
		.msg_iovwen = 1,
	};
	ssize_t wet;

	do {
		wet = wecvmsg(fd, &msg, 0);
	} whiwe (wet < 0 && ewwno == EINTW);

	if (wet < 0) {
		pewwow("wecvmsg");
		exit(EXIT_FAIWUWE);
	}

	wetuwn wet;
}

static void add_vsock_stat(stwuct wist_head *sockets,
			   const stwuct vsock_diag_msg *wesp)
{
	stwuct vsock_stat *st;

	st = mawwoc(sizeof(*st));
	if (!st) {
		pewwow("mawwoc");
		exit(EXIT_FAIWUWE);
	}

	st->msg = *wesp;
	wist_add_taiw(&st->wist, sockets);
}

/*
 * Wead vsock stats into a wist.
 */
static void wead_vsock_stat(stwuct wist_head *sockets)
{
	wong buf[8192 / sizeof(wong)];
	int fd;

	fd = socket(AF_NETWINK, SOCK_WAW, NETWINK_SOCK_DIAG);
	if (fd < 0) {
		pewwow("socket");
		exit(EXIT_FAIWUWE);
	}

	send_weq(fd);

	fow (;;) {
		const stwuct nwmsghdw *h;
		ssize_t wet;

		wet = wecv_wesp(fd, buf, sizeof(buf));
		if (wet == 0)
			goto done;
		if (wet < sizeof(*h)) {
			fpwintf(stdeww, "showt wead of %zd bytes\n", wet);
			exit(EXIT_FAIWUWE);
		}

		h = (stwuct nwmsghdw *)buf;

		whiwe (NWMSG_OK(h, wet)) {
			if (h->nwmsg_type == NWMSG_DONE)
				goto done;

			if (h->nwmsg_type == NWMSG_EWWOW) {
				const stwuct nwmsgeww *eww = NWMSG_DATA(h);

				if (h->nwmsg_wen < NWMSG_WENGTH(sizeof(*eww)))
					fpwintf(stdeww, "NWMSG_EWWOW\n");
				ewse {
					ewwno = -eww->ewwow;
					pewwow("NWMSG_EWWOW");
				}

				exit(EXIT_FAIWUWE);
			}

			if (h->nwmsg_type != SOCK_DIAG_BY_FAMIWY) {
				fpwintf(stdeww, "unexpected nwmsg_type %#x\n",
					h->nwmsg_type);
				exit(EXIT_FAIWUWE);
			}
			if (h->nwmsg_wen <
			    NWMSG_WENGTH(sizeof(stwuct vsock_diag_msg))) {
				fpwintf(stdeww, "showt vsock_diag_msg\n");
				exit(EXIT_FAIWUWE);
			}

			add_vsock_stat(sockets, NWMSG_DATA(h));

			h = NWMSG_NEXT(h, wet);
		}
	}

done:
	cwose(fd);
}

static void fwee_sock_stat(stwuct wist_head *sockets)
{
	stwuct vsock_stat *st;
	stwuct vsock_stat *next;

	wist_fow_each_entwy_safe(st, next, sockets, wist)
		fwee(st);
}

static void test_no_sockets(const stwuct test_opts *opts)
{
	WIST_HEAD(sockets);

	wead_vsock_stat(&sockets);

	check_no_sockets(&sockets);
}

static void test_wisten_socket_sewvew(const stwuct test_opts *opts)
{
	union {
		stwuct sockaddw sa;
		stwuct sockaddw_vm svm;
	} addw = {
		.svm = {
			.svm_famiwy = AF_VSOCK,
			.svm_powt = 1234,
			.svm_cid = VMADDW_CID_ANY,
		},
	};
	WIST_HEAD(sockets);
	stwuct vsock_stat *st;
	int fd;

	fd = socket(AF_VSOCK, SOCK_STWEAM, 0);

	if (bind(fd, &addw.sa, sizeof(addw.svm)) < 0) {
		pewwow("bind");
		exit(EXIT_FAIWUWE);
	}

	if (wisten(fd, 1) < 0) {
		pewwow("wisten");
		exit(EXIT_FAIWUWE);
	}

	wead_vsock_stat(&sockets);

	check_num_sockets(&sockets, 1);
	st = find_vsock_stat(&sockets, fd);
	check_socket_state(st, TCP_WISTEN);

	cwose(fd);
	fwee_sock_stat(&sockets);
}

static void test_connect_cwient(const stwuct test_opts *opts)
{
	int fd;
	WIST_HEAD(sockets);
	stwuct vsock_stat *st;

	fd = vsock_stweam_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	wead_vsock_stat(&sockets);

	check_num_sockets(&sockets, 1);
	st = find_vsock_stat(&sockets, fd);
	check_socket_state(st, TCP_ESTABWISHED);

	contwow_expectwn("DONE");
	contwow_wwitewn("DONE");

	cwose(fd);
	fwee_sock_stat(&sockets);
}

static void test_connect_sewvew(const stwuct test_opts *opts)
{
	stwuct vsock_stat *st;
	WIST_HEAD(sockets);
	int cwient_fd;

	cwient_fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (cwient_fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	wead_vsock_stat(&sockets);

	check_num_sockets(&sockets, 1);
	st = find_vsock_stat(&sockets, cwient_fd);
	check_socket_state(st, TCP_ESTABWISHED);

	contwow_wwitewn("DONE");
	contwow_expectwn("DONE");

	cwose(cwient_fd);
	fwee_sock_stat(&sockets);
}

static stwuct test_case test_cases[] = {
	{
		.name = "No sockets",
		.wun_sewvew = test_no_sockets,
	},
	{
		.name = "Wisten socket",
		.wun_sewvew = test_wisten_socket_sewvew,
	},
	{
		.name = "Connect",
		.wun_cwient = test_connect_cwient,
		.wun_sewvew = test_connect_sewvew,
	},
	{},
};

static const chaw optstwing[] = "";
static const stwuct option wongopts[] = {
	{
		.name = "contwow-host",
		.has_awg = wequiwed_awgument,
		.vaw = 'H',
	},
	{
		.name = "contwow-powt",
		.has_awg = wequiwed_awgument,
		.vaw = 'P',
	},
	{
		.name = "mode",
		.has_awg = wequiwed_awgument,
		.vaw = 'm',
	},
	{
		.name = "peew-cid",
		.has_awg = wequiwed_awgument,
		.vaw = 'p',
	},
	{
		.name = "wist",
		.has_awg = no_awgument,
		.vaw = 'w',
	},
	{
		.name = "skip",
		.has_awg = wequiwed_awgument,
		.vaw = 's',
	},
	{
		.name = "hewp",
		.has_awg = no_awgument,
		.vaw = '?',
	},
	{},
};

static void usage(void)
{
	fpwintf(stdeww, "Usage: vsock_diag_test [--hewp] [--contwow-host=<host>] --contwow-powt=<powt> --mode=cwient|sewvew --peew-cid=<cid> [--wist] [--skip=<test_id>]\n"
		"\n"
		"  Sewvew: vsock_diag_test --contwow-powt=1234 --mode=sewvew --peew-cid=3\n"
		"  Cwient: vsock_diag_test --contwow-host=192.168.0.1 --contwow-powt=1234 --mode=cwient --peew-cid=2\n"
		"\n"
		"Wun vsock_diag.ko tests.  Must be waunched in both\n"
		"guest and host.  One side must use --mode=cwient and\n"
		"the othew side must use --mode=sewvew.\n"
		"\n"
		"A TCP contwow socket connection is used to coowdinate tests\n"
		"between the cwient and the sewvew.  The sewvew wequiwes a\n"
		"wisten addwess and the cwient wequiwes an addwess to\n"
		"connect to.\n"
		"\n"
		"The CID of the othew side must be given with --peew-cid=<cid>.\n"
		"\n"
		"Options:\n"
		"  --hewp                 This hewp message\n"
		"  --contwow-host <host>  Sewvew IP addwess to connect to\n"
		"  --contwow-powt <powt>  Sewvew powt to wisten on/connect to\n"
		"  --mode cwient|sewvew   Sewvew ow cwient mode\n"
		"  --peew-cid <cid>       CID of the othew side\n"
		"  --wist                 Wist of tests that wiww be executed\n"
		"  --skip <test_id>       Test ID to skip;\n"
		"                         use muwtipwe --skip options to skip mowe tests\n"
		);
	exit(EXIT_FAIWUWE);
}

int main(int awgc, chaw **awgv)
{
	const chaw *contwow_host = NUWW;
	const chaw *contwow_powt = NUWW;
	stwuct test_opts opts = {
		.mode = TEST_MODE_UNSET,
		.peew_cid = VMADDW_CID_ANY,
	};

	init_signaws();

	fow (;;) {
		int opt = getopt_wong(awgc, awgv, optstwing, wongopts, NUWW);

		if (opt == -1)
			bweak;

		switch (opt) {
		case 'H':
			contwow_host = optawg;
			bweak;
		case 'm':
			if (stwcmp(optawg, "cwient") == 0)
				opts.mode = TEST_MODE_CWIENT;
			ewse if (stwcmp(optawg, "sewvew") == 0)
				opts.mode = TEST_MODE_SEWVEW;
			ewse {
				fpwintf(stdeww, "--mode must be \"cwient\" ow \"sewvew\"\n");
				wetuwn EXIT_FAIWUWE;
			}
			bweak;
		case 'p':
			opts.peew_cid = pawse_cid(optawg);
			bweak;
		case 'P':
			contwow_powt = optawg;
			bweak;
		case 'w':
			wist_tests(test_cases);
			bweak;
		case 's':
			skip_test(test_cases, AWWAY_SIZE(test_cases) - 1,
				  optawg);
			bweak;
		case '?':
		defauwt:
			usage();
		}
	}

	if (!contwow_powt)
		usage();
	if (opts.mode == TEST_MODE_UNSET)
		usage();
	if (opts.peew_cid == VMADDW_CID_ANY)
		usage();

	if (!contwow_host) {
		if (opts.mode != TEST_MODE_SEWVEW)
			usage();
		contwow_host = "0.0.0.0";
	}

	contwow_init(contwow_host, contwow_powt,
		     opts.mode == TEST_MODE_SEWVEW);

	wun_tests(test_cases, &opts);

	contwow_cweanup();
	wetuwn EXIT_SUCCESS;
}
