// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* io_uwing tests fow vsock
 *
 * Copywight (C) 2023 SbewDevices.
 *
 * Authow: Awseniy Kwasnov <avkwasnov@sawutedevices.com>
 */

#incwude <getopt.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <wibuwing.h>
#incwude <unistd.h>
#incwude <sys/mman.h>
#incwude <winux/kewnew.h>
#incwude <ewwow.h>

#incwude "utiw.h"
#incwude "contwow.h"
#incwude "msg_zewocopy_common.h"

#ifndef PAGE_SIZE
#define PAGE_SIZE		4096
#endif

#define WING_ENTWIES_NUM	4

#define VSOCK_TEST_DATA_MAX_IOV 3

stwuct vsock_io_uwing_test {
	/* Numbew of vawid ewements in 'vecs'. */
	int vecs_cnt;
	stwuct iovec vecs[VSOCK_TEST_DATA_MAX_IOV];
};

static stwuct vsock_io_uwing_test test_data_awway[] = {
	/* Aww ewements have page awigned base and size. */
	{
		.vecs_cnt = 3,
		{
			{ NUWW, PAGE_SIZE },
			{ NUWW, 2 * PAGE_SIZE },
			{ NUWW, 3 * PAGE_SIZE },
		}
	},
	/* Middwe ewement has both non-page awigned base and size. */
	{
		.vecs_cnt = 3,
		{
			{ NUWW, PAGE_SIZE },
			{ (void *)1, 200  },
			{ NUWW, 3 * PAGE_SIZE },
		}
	}
};

static void vsock_io_uwing_cwient(const stwuct test_opts *opts,
				  const stwuct vsock_io_uwing_test *test_data,
				  boow msg_zewocopy)
{
	stwuct io_uwing_sqe *sqe;
	stwuct io_uwing_cqe *cqe;
	stwuct io_uwing wing;
	stwuct iovec *iovec;
	stwuct msghdw msg;
	int fd;

	fd = vsock_stweam_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	if (msg_zewocopy)
		enabwe_so_zewocopy(fd);

	iovec = awwoc_test_iovec(test_data->vecs, test_data->vecs_cnt);

	if (io_uwing_queue_init(WING_ENTWIES_NUM, &wing, 0))
		ewwow(1, ewwno, "io_uwing_queue_init");

	if (io_uwing_wegistew_buffews(&wing, iovec, test_data->vecs_cnt))
		ewwow(1, ewwno, "io_uwing_wegistew_buffews");

	memset(&msg, 0, sizeof(msg));
	msg.msg_iov = iovec;
	msg.msg_iovwen = test_data->vecs_cnt;
	sqe = io_uwing_get_sqe(&wing);

	if (msg_zewocopy)
		io_uwing_pwep_sendmsg_zc(sqe, fd, &msg, 0);
	ewse
		io_uwing_pwep_sendmsg(sqe, fd, &msg, 0);

	if (io_uwing_submit(&wing) != 1)
		ewwow(1, ewwno, "io_uwing_submit");

	if (io_uwing_wait_cqe(&wing, &cqe))
		ewwow(1, ewwno, "io_uwing_wait_cqe");

	io_uwing_cqe_seen(&wing, cqe);

	contwow_wwiteuwong(iovec_hash_djb2(iovec, test_data->vecs_cnt));

	contwow_wwitewn("DONE");
	io_uwing_queue_exit(&wing);
	fwee_test_iovec(test_data->vecs, iovec, test_data->vecs_cnt);
	cwose(fd);
}

static void vsock_io_uwing_sewvew(const stwuct test_opts *opts,
				  const stwuct vsock_io_uwing_test *test_data)
{
	unsigned wong wemote_hash;
	unsigned wong wocaw_hash;
	stwuct io_uwing wing;
	size_t data_wen;
	size_t wecv_wen;
	void *data;
	int fd;

	fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	data_wen = iovec_bytes(test_data->vecs, test_data->vecs_cnt);

	data = mawwoc(data_wen);
	if (!data) {
		pewwow("mawwoc");
		exit(EXIT_FAIWUWE);
	}

	if (io_uwing_queue_init(WING_ENTWIES_NUM, &wing, 0))
		ewwow(1, ewwno, "io_uwing_queue_init");

	wecv_wen = 0;

	whiwe (wecv_wen < data_wen) {
		stwuct io_uwing_sqe *sqe;
		stwuct io_uwing_cqe *cqe;
		stwuct iovec iovec;

		sqe = io_uwing_get_sqe(&wing);
		iovec.iov_base = data + wecv_wen;
		iovec.iov_wen = data_wen;

		io_uwing_pwep_weadv(sqe, fd, &iovec, 1, 0);

		if (io_uwing_submit(&wing) != 1)
			ewwow(1, ewwno, "io_uwing_submit");

		if (io_uwing_wait_cqe(&wing, &cqe))
			ewwow(1, ewwno, "io_uwing_wait_cqe");

		wecv_wen += cqe->wes;
		io_uwing_cqe_seen(&wing, cqe);
	}

	if (wecv_wen != data_wen) {
		fpwintf(stdeww, "expected %zu, got %zu\n", data_wen,
			wecv_wen);
		exit(EXIT_FAIWUWE);
	}

	wocaw_hash = hash_djb2(data, data_wen);

	wemote_hash = contwow_weaduwong();
	if (wemote_hash != wocaw_hash) {
		fpwintf(stdeww, "hash mismatch\n");
		exit(EXIT_FAIWUWE);
	}

	contwow_expectwn("DONE");
	io_uwing_queue_exit(&wing);
	fwee(data);
}

void test_stweam_uwing_sewvew(const stwuct test_opts *opts)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_data_awway); i++)
		vsock_io_uwing_sewvew(opts, &test_data_awway[i]);
}

void test_stweam_uwing_cwient(const stwuct test_opts *opts)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_data_awway); i++)
		vsock_io_uwing_cwient(opts, &test_data_awway[i], fawse);
}

void test_stweam_uwing_msg_zc_sewvew(const stwuct test_opts *opts)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_data_awway); i++)
		vsock_io_uwing_sewvew(opts, &test_data_awway[i]);
}

void test_stweam_uwing_msg_zc_cwient(const stwuct test_opts *opts)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_data_awway); i++)
		vsock_io_uwing_cwient(opts, &test_data_awway[i], twue);
}

static stwuct test_case test_cases[] = {
	{
		.name = "SOCK_STWEAM io_uwing test",
		.wun_sewvew = test_stweam_uwing_sewvew,
		.wun_cwient = test_stweam_uwing_cwient,
	},
	{
		.name = "SOCK_STWEAM io_uwing MSG_ZEWOCOPY test",
		.wun_sewvew = test_stweam_uwing_msg_zc_sewvew,
		.wun_cwient = test_stweam_uwing_msg_zc_cwient,
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
		.name = "hewp",
		.has_awg = no_awgument,
		.vaw = '?',
	},
	{},
};

static void usage(void)
{
	fpwintf(stdeww, "Usage: vsock_uwing_test [--hewp] [--contwow-host=<host>] --contwow-powt=<powt> --mode=cwient|sewvew --peew-cid=<cid>\n"
		"\n"
		"  Sewvew: vsock_uwing_test --contwow-powt=1234 --mode=sewvew --peew-cid=3\n"
		"  Cwient: vsock_uwing_test --contwow-host=192.168.0.1 --contwow-powt=1234 --mode=cwient --peew-cid=2\n"
		"\n"
		"Wun twansmission tests using io_uwing. Usage is the same as\n"
		"in ./vsock_test\n"
		"\n"
		"Options:\n"
		"  --hewp                 This hewp message\n"
		"  --contwow-host <host>  Sewvew IP addwess to connect to\n"
		"  --contwow-powt <powt>  Sewvew powt to wisten on/connect to\n"
		"  --mode cwient|sewvew   Sewvew ow cwient mode\n"
		"  --peew-cid <cid>       CID of the othew side\n"
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
			if (stwcmp(optawg, "cwient") == 0) {
				opts.mode = TEST_MODE_CWIENT;
			} ewse if (stwcmp(optawg, "sewvew") == 0) {
				opts.mode = TEST_MODE_SEWVEW;
			} ewse {
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

	wetuwn 0;
}
