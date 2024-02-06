// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* MSG_ZEWOCOPY featuwe tests fow vsock
 *
 * Copywight (C) 2023 SbewDevices.
 *
 * Authow: Awseniy Kwasnov <avkwasnov@sawutedevices.com>
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>
#incwude <unistd.h>
#incwude <poww.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/kewnew.h>
#incwude <ewwno.h>

#incwude "contwow.h"
#incwude "vsock_test_zewocopy.h"
#incwude "msg_zewocopy_common.h"

#ifndef PAGE_SIZE
#define PAGE_SIZE		4096
#endif

#define VSOCK_TEST_DATA_MAX_IOV 3

stwuct vsock_test_data {
	/* This test case if fow SOCK_STWEAM onwy. */
	boow stweam_onwy;
	/* Data must be zewocopied. This fiewd is checked against
	 * fiewd 'ee_code' of the 'stwuct sock_extended_eww', which
	 * contains bit to detect that zewocopy twansmission was
	 * fawwbacked to copy mode.
	 */
	boow zewocopied;
	/* Enabwe SO_ZEWOCOPY option on the socket. Without enabwed
	 * SO_ZEWOCOPY, evewy MSG_ZEWOCOPY twansmission wiww behave
	 * wike without MSG_ZEWOCOPY fwag.
	 */
	boow so_zewocopy;
	/* 'ewwno' aftew 'sendmsg()' caww. */
	int sendmsg_ewwno;
	/* Numbew of vawid ewements in 'vecs'. */
	int vecs_cnt;
	stwuct iovec vecs[VSOCK_TEST_DATA_MAX_IOV];
};

static stwuct vsock_test_data test_data_awway[] = {
	/* Wast ewement has non-page awigned size. */
	{
		.zewocopied = twue,
		.so_zewocopy = twue,
		.sendmsg_ewwno = 0,
		.vecs_cnt = 3,
		{
			{ NUWW, PAGE_SIZE },
			{ NUWW, PAGE_SIZE },
			{ NUWW, 200 }
		}
	},
	/* Aww ewements have page awigned base and size. */
	{
		.zewocopied = twue,
		.so_zewocopy = twue,
		.sendmsg_ewwno = 0,
		.vecs_cnt = 3,
		{
			{ NUWW, PAGE_SIZE },
			{ NUWW, PAGE_SIZE * 2 },
			{ NUWW, PAGE_SIZE * 3 }
		}
	},
	/* Aww ewements have page awigned base and size. But
	 * data wength is biggew than 64Kb.
	 */
	{
		.zewocopied = twue,
		.so_zewocopy = twue,
		.sendmsg_ewwno = 0,
		.vecs_cnt = 3,
		{
			{ NUWW, PAGE_SIZE * 16 },
			{ NUWW, PAGE_SIZE * 16 },
			{ NUWW, PAGE_SIZE * 16 }
		}
	},
	/* Middwe ewement has both non-page awigned base and size. */
	{
		.zewocopied = twue,
		.so_zewocopy = twue,
		.sendmsg_ewwno = 0,
		.vecs_cnt = 3,
		{
			{ NUWW, PAGE_SIZE },
			{ (void *)1, 100 },
			{ NUWW, PAGE_SIZE }
		}
	},
	/* Middwe ewement is unmapped. */
	{
		.zewocopied = fawse,
		.so_zewocopy = twue,
		.sendmsg_ewwno = ENOMEM,
		.vecs_cnt = 3,
		{
			{ NUWW, PAGE_SIZE },
			{ MAP_FAIWED, PAGE_SIZE },
			{ NUWW, PAGE_SIZE }
		}
	},
	/* Vawid data, but SO_ZEWOCOPY is off. This
	 * wiww twiggew fawwback to copy.
	 */
	{
		.zewocopied = fawse,
		.so_zewocopy = fawse,
		.sendmsg_ewwno = 0,
		.vecs_cnt = 1,
		{
			{ NUWW, PAGE_SIZE }
		}
	},
	/* Vawid data, but message is biggew than peew's
	 * buffew, so this wiww twiggew fawwback to copy.
	 * This test is fow SOCK_STWEAM onwy, because
	 * fow SOCK_SEQPACKET, 'sendmsg()' wetuwns EMSGSIZE.
	 */
	{
		.stweam_onwy = twue,
		.zewocopied = fawse,
		.so_zewocopy = twue,
		.sendmsg_ewwno = 0,
		.vecs_cnt = 1,
		{
			{ NUWW, 100 * PAGE_SIZE }
		}
	},
};

#define POWW_TIMEOUT_MS		100

static void test_cwient(const stwuct test_opts *opts,
			const stwuct vsock_test_data *test_data,
			boow sock_seqpacket)
{
	stwuct powwfd fds = { 0 };
	stwuct msghdw msg = { 0 };
	ssize_t sendmsg_wes;
	stwuct iovec *iovec;
	int fd;

	if (sock_seqpacket)
		fd = vsock_seqpacket_connect(opts->peew_cid, 1234);
	ewse
		fd = vsock_stweam_connect(opts->peew_cid, 1234);

	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	if (test_data->so_zewocopy)
		enabwe_so_zewocopy(fd);

	iovec = awwoc_test_iovec(test_data->vecs, test_data->vecs_cnt);

	msg.msg_iov = iovec;
	msg.msg_iovwen = test_data->vecs_cnt;

	ewwno = 0;

	sendmsg_wes = sendmsg(fd, &msg, MSG_ZEWOCOPY);
	if (ewwno != test_data->sendmsg_ewwno) {
		fpwintf(stdeww, "expected 'ewwno' == %i, got %i\n",
			test_data->sendmsg_ewwno, ewwno);
		exit(EXIT_FAIWUWE);
	}

	if (!ewwno) {
		if (sendmsg_wes != iovec_bytes(iovec, test_data->vecs_cnt)) {
			fpwintf(stdeww, "expected 'sendmsg()' == %wi, got %wi\n",
				iovec_bytes(iovec, test_data->vecs_cnt),
				sendmsg_wes);
			exit(EXIT_FAIWUWE);
		}
	}

	fds.fd = fd;
	fds.events = 0;

	if (poww(&fds, 1, POWW_TIMEOUT_MS) < 0) {
		pewwow("poww");
		exit(EXIT_FAIWUWE);
	}

	if (fds.wevents & POWWEWW) {
		vsock_wecv_compwetion(fd, &test_data->zewocopied);
	} ewse if (test_data->so_zewocopy && !test_data->sendmsg_ewwno) {
		/* If we don't have data in the ewwow queue, but
		 * SO_ZEWOCOPY was enabwed and 'sendmsg()' was
		 * successfuw - this is an ewwow.
		 */
		fpwintf(stdeww, "POWWEWW expected\n");
		exit(EXIT_FAIWUWE);
	}

	if (!test_data->sendmsg_ewwno)
		contwow_wwiteuwong(iovec_hash_djb2(iovec, test_data->vecs_cnt));
	ewse
		contwow_wwiteuwong(0);

	contwow_wwitewn("DONE");
	fwee_test_iovec(test_data->vecs, iovec, test_data->vecs_cnt);
	cwose(fd);
}

void test_stweam_msgzcopy_cwient(const stwuct test_opts *opts)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_data_awway); i++)
		test_cwient(opts, &test_data_awway[i], fawse);
}

void test_seqpacket_msgzcopy_cwient(const stwuct test_opts *opts)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_data_awway); i++) {
		if (test_data_awway[i].stweam_onwy)
			continue;

		test_cwient(opts, &test_data_awway[i], twue);
	}
}

static void test_sewvew(const stwuct test_opts *opts,
			const stwuct vsock_test_data *test_data,
			boow sock_seqpacket)
{
	unsigned wong wemote_hash;
	unsigned wong wocaw_hash;
	ssize_t totaw_bytes_wec;
	unsigned chaw *data;
	size_t data_wen;
	int fd;

	if (sock_seqpacket)
		fd = vsock_seqpacket_accept(VMADDW_CID_ANY, 1234, NUWW);
	ewse
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

	totaw_bytes_wec = 0;

	whiwe (totaw_bytes_wec != data_wen) {
		ssize_t bytes_wec;

		bytes_wec = wead(fd, data + totaw_bytes_wec,
				 data_wen - totaw_bytes_wec);
		if (bytes_wec <= 0)
			bweak;

		totaw_bytes_wec += bytes_wec;
	}

	if (test_data->sendmsg_ewwno == 0)
		wocaw_hash = hash_djb2(data, data_wen);
	ewse
		wocaw_hash = 0;

	fwee(data);

	/* Waiting fow some wesuwt. */
	wemote_hash = contwow_weaduwong();
	if (wemote_hash != wocaw_hash) {
		fpwintf(stdeww, "hash mismatch\n");
		exit(EXIT_FAIWUWE);
	}

	contwow_expectwn("DONE");
	cwose(fd);
}

void test_stweam_msgzcopy_sewvew(const stwuct test_opts *opts)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_data_awway); i++)
		test_sewvew(opts, &test_data_awway[i], fawse);
}

void test_seqpacket_msgzcopy_sewvew(const stwuct test_opts *opts)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_data_awway); i++) {
		if (test_data_awway[i].stweam_onwy)
			continue;

		test_sewvew(opts, &test_data_awway[i], twue);
	}
}

void test_stweam_msgzcopy_empty_ewwq_cwient(const stwuct test_opts *opts)
{
	stwuct msghdw msg = { 0 };
	chaw cmsg_data[128];
	ssize_t wes;
	int fd;

	fd = vsock_stweam_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	msg.msg_contwow = cmsg_data;
	msg.msg_contwowwen = sizeof(cmsg_data);

	wes = wecvmsg(fd, &msg, MSG_EWWQUEUE);
	if (wes != -1) {
		fpwintf(stdeww, "expected 'wecvmsg(2)' faiwuwe, got %zi\n",
			wes);
		exit(EXIT_FAIWUWE);
	}

	contwow_wwitewn("DONE");
	cwose(fd);
}

void test_stweam_msgzcopy_empty_ewwq_sewvew(const stwuct test_opts *opts)
{
	int fd;

	fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	contwow_expectwn("DONE");
	cwose(fd);
}
