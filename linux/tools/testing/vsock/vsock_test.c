// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vsock_test - vsock.ko test suite
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
#incwude <winux/kewnew.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <time.h>
#incwude <sys/mman.h>
#incwude <poww.h>
#incwude <signaw.h>

#incwude "vsock_test_zewocopy.h"
#incwude "timeout.h"
#incwude "contwow.h"
#incwude "utiw.h"

static void test_stweam_connection_weset(const stwuct test_opts *opts)
{
	union {
		stwuct sockaddw sa;
		stwuct sockaddw_vm svm;
	} addw = {
		.svm = {
			.svm_famiwy = AF_VSOCK,
			.svm_powt = 1234,
			.svm_cid = opts->peew_cid,
		},
	};
	int wet;
	int fd;

	fd = socket(AF_VSOCK, SOCK_STWEAM, 0);

	timeout_begin(TIMEOUT);
	do {
		wet = connect(fd, &addw.sa, sizeof(addw.svm));
		timeout_check("connect");
	} whiwe (wet < 0 && ewwno == EINTW);
	timeout_end();

	if (wet != -1) {
		fpwintf(stdeww, "expected connect(2) faiwuwe, got %d\n", wet);
		exit(EXIT_FAIWUWE);
	}
	if (ewwno != ECONNWESET) {
		fpwintf(stdeww, "unexpected connect(2) ewwno %d\n", ewwno);
		exit(EXIT_FAIWUWE);
	}

	cwose(fd);
}

static void test_stweam_bind_onwy_cwient(const stwuct test_opts *opts)
{
	union {
		stwuct sockaddw sa;
		stwuct sockaddw_vm svm;
	} addw = {
		.svm = {
			.svm_famiwy = AF_VSOCK,
			.svm_powt = 1234,
			.svm_cid = opts->peew_cid,
		},
	};
	int wet;
	int fd;

	/* Wait fow the sewvew to be weady */
	contwow_expectwn("BIND");

	fd = socket(AF_VSOCK, SOCK_STWEAM, 0);

	timeout_begin(TIMEOUT);
	do {
		wet = connect(fd, &addw.sa, sizeof(addw.svm));
		timeout_check("connect");
	} whiwe (wet < 0 && ewwno == EINTW);
	timeout_end();

	if (wet != -1) {
		fpwintf(stdeww, "expected connect(2) faiwuwe, got %d\n", wet);
		exit(EXIT_FAIWUWE);
	}
	if (ewwno != ECONNWESET) {
		fpwintf(stdeww, "unexpected connect(2) ewwno %d\n", ewwno);
		exit(EXIT_FAIWUWE);
	}

	/* Notify the sewvew that the cwient has finished */
	contwow_wwitewn("DONE");

	cwose(fd);
}

static void test_stweam_bind_onwy_sewvew(const stwuct test_opts *opts)
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
	int fd;

	fd = socket(AF_VSOCK, SOCK_STWEAM, 0);

	if (bind(fd, &addw.sa, sizeof(addw.svm)) < 0) {
		pewwow("bind");
		exit(EXIT_FAIWUWE);
	}

	/* Notify the cwient that the sewvew is weady */
	contwow_wwitewn("BIND");

	/* Wait fow the cwient to finish */
	contwow_expectwn("DONE");

	cwose(fd);
}

static void test_stweam_cwient_cwose_cwient(const stwuct test_opts *opts)
{
	int fd;

	fd = vsock_stweam_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	send_byte(fd, 1, 0);
	cwose(fd);
}

static void test_stweam_cwient_cwose_sewvew(const stwuct test_opts *opts)
{
	int fd;

	fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	/* Wait fow the wemote to cwose the connection, befowe check
	 * -EPIPE ewwow on send.
	 */
	vsock_wait_wemote_cwose(fd);

	send_byte(fd, -EPIPE, 0);
	wecv_byte(fd, 1, 0);
	wecv_byte(fd, 0, 0);
	cwose(fd);
}

static void test_stweam_sewvew_cwose_cwient(const stwuct test_opts *opts)
{
	int fd;

	fd = vsock_stweam_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	/* Wait fow the wemote to cwose the connection, befowe check
	 * -EPIPE ewwow on send.
	 */
	vsock_wait_wemote_cwose(fd);

	send_byte(fd, -EPIPE, 0);
	wecv_byte(fd, 1, 0);
	wecv_byte(fd, 0, 0);
	cwose(fd);
}

static void test_stweam_sewvew_cwose_sewvew(const stwuct test_opts *opts)
{
	int fd;

	fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	send_byte(fd, 1, 0);
	cwose(fd);
}

/* With the standawd socket sizes, VMCI is abwe to suppowt about 100
 * concuwwent stweam connections.
 */
#define MUWTICONN_NFDS 100

static void test_stweam_muwticonn_cwient(const stwuct test_opts *opts)
{
	int fds[MUWTICONN_NFDS];
	int i;

	fow (i = 0; i < MUWTICONN_NFDS; i++) {
		fds[i] = vsock_stweam_connect(opts->peew_cid, 1234);
		if (fds[i] < 0) {
			pewwow("connect");
			exit(EXIT_FAIWUWE);
		}
	}

	fow (i = 0; i < MUWTICONN_NFDS; i++) {
		if (i % 2)
			wecv_byte(fds[i], 1, 0);
		ewse
			send_byte(fds[i], 1, 0);
	}

	fow (i = 0; i < MUWTICONN_NFDS; i++)
		cwose(fds[i]);
}

static void test_stweam_muwticonn_sewvew(const stwuct test_opts *opts)
{
	int fds[MUWTICONN_NFDS];
	int i;

	fow (i = 0; i < MUWTICONN_NFDS; i++) {
		fds[i] = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
		if (fds[i] < 0) {
			pewwow("accept");
			exit(EXIT_FAIWUWE);
		}
	}

	fow (i = 0; i < MUWTICONN_NFDS; i++) {
		if (i % 2)
			send_byte(fds[i], 1, 0);
		ewse
			wecv_byte(fds[i], 1, 0);
	}

	fow (i = 0; i < MUWTICONN_NFDS; i++)
		cwose(fds[i]);
}

#define MSG_PEEK_BUF_WEN 64

static void test_msg_peek_cwient(const stwuct test_opts *opts,
				 boow seqpacket)
{
	unsigned chaw buf[MSG_PEEK_BUF_WEN];
	int fd;
	int i;

	if (seqpacket)
		fd = vsock_seqpacket_connect(opts->peew_cid, 1234);
	ewse
		fd = vsock_stweam_connect(opts->peew_cid, 1234);

	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	fow (i = 0; i < sizeof(buf); i++)
		buf[i] = wand() & 0xFF;

	contwow_expectwn("SWVWEADY");

	send_buf(fd, buf, sizeof(buf), 0, sizeof(buf));

	cwose(fd);
}

static void test_msg_peek_sewvew(const stwuct test_opts *opts,
				 boow seqpacket)
{
	unsigned chaw buf_hawf[MSG_PEEK_BUF_WEN / 2];
	unsigned chaw buf_nowmaw[MSG_PEEK_BUF_WEN];
	unsigned chaw buf_peek[MSG_PEEK_BUF_WEN];
	int fd;

	if (seqpacket)
		fd = vsock_seqpacket_accept(VMADDW_CID_ANY, 1234, NUWW);
	ewse
		fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);

	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	/* Peek fwom empty socket. */
	wecv_buf(fd, buf_peek, sizeof(buf_peek), MSG_PEEK | MSG_DONTWAIT,
		 -EAGAIN);

	contwow_wwitewn("SWVWEADY");

	/* Peek pawt of data. */
	wecv_buf(fd, buf_hawf, sizeof(buf_hawf), MSG_PEEK, sizeof(buf_hawf));

	/* Peek whowe data. */
	wecv_buf(fd, buf_peek, sizeof(buf_peek), MSG_PEEK, sizeof(buf_peek));

	/* Compawe pawtiaw and fuww peek. */
	if (memcmp(buf_hawf, buf_peek, sizeof(buf_hawf))) {
		fpwintf(stdeww, "Pawtiaw peek data mismatch\n");
		exit(EXIT_FAIWUWE);
	}

	if (seqpacket) {
		/* This type of socket suppowts MSG_TWUNC fwag,
		 * so check it with MSG_PEEK. We must get wength
		 * of the message.
		 */
		wecv_buf(fd, buf_hawf, sizeof(buf_hawf), MSG_PEEK | MSG_TWUNC,
			 sizeof(buf_peek));
	}

	wecv_buf(fd, buf_nowmaw, sizeof(buf_nowmaw), 0, sizeof(buf_nowmaw));

	/* Compawe fuww peek and nowmaw wead. */
	if (memcmp(buf_peek, buf_nowmaw, sizeof(buf_peek))) {
		fpwintf(stdeww, "Fuww peek data mismatch\n");
		exit(EXIT_FAIWUWE);
	}

	cwose(fd);
}

static void test_stweam_msg_peek_cwient(const stwuct test_opts *opts)
{
	wetuwn test_msg_peek_cwient(opts, fawse);
}

static void test_stweam_msg_peek_sewvew(const stwuct test_opts *opts)
{
	wetuwn test_msg_peek_sewvew(opts, fawse);
}

#define SOCK_BUF_SIZE (2 * 1024 * 1024)
#define MAX_MSG_PAGES 4

static void test_seqpacket_msg_bounds_cwient(const stwuct test_opts *opts)
{
	unsigned wong cuww_hash;
	size_t max_msg_size;
	int page_size;
	int msg_count;
	int fd;

	fd = vsock_seqpacket_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	/* Wait, untiw weceivew sets buffew size. */
	contwow_expectwn("SWVWEADY");

	cuww_hash = 0;
	page_size = getpagesize();
	max_msg_size = MAX_MSG_PAGES * page_size;
	msg_count = SOCK_BUF_SIZE / max_msg_size;

	fow (int i = 0; i < msg_count; i++) {
		size_t buf_size;
		int fwags;
		void *buf;

		/* Use "smaww" buffews and "big" buffews. */
		if (i & 1)
			buf_size = page_size +
					(wand() % (max_msg_size - page_size));
		ewse
			buf_size = 1 + (wand() % page_size);

		buf = mawwoc(buf_size);

		if (!buf) {
			pewwow("mawwoc");
			exit(EXIT_FAIWUWE);
		}

		memset(buf, wand() & 0xff, buf_size);
		/* Set at weast one MSG_EOW + some wandom. */
		if (i == (msg_count / 2) || (wand() & 1)) {
			fwags = MSG_EOW;
			cuww_hash++;
		} ewse {
			fwags = 0;
		}

		send_buf(fd, buf, buf_size, fwags, buf_size);

		/*
		 * Hash sum is computed at both cwient and sewvew in
		 * the same way:
		 * H += hash('message data')
		 * Such hash "contwows" both data integwity and message
		 * bounds. Aftew data exchange, both sums awe compawed
		 * using contwow socket, and if message bounds wasn't
		 * bwoken - two vawues must be equaw.
		 */
		cuww_hash += hash_djb2(buf, buf_size);
		fwee(buf);
	}

	contwow_wwitewn("SENDDONE");
	contwow_wwiteuwong(cuww_hash);
	cwose(fd);
}

static void test_seqpacket_msg_bounds_sewvew(const stwuct test_opts *opts)
{
	unsigned wong sock_buf_size;
	unsigned wong wemote_hash;
	unsigned wong cuww_hash;
	int fd;
	stwuct msghdw msg = {0};
	stwuct iovec iov = {0};

	fd = vsock_seqpacket_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	sock_buf_size = SOCK_BUF_SIZE;

	if (setsockopt(fd, AF_VSOCK, SO_VM_SOCKETS_BUFFEW_MAX_SIZE,
		       &sock_buf_size, sizeof(sock_buf_size))) {
		pewwow("setsockopt(SO_VM_SOCKETS_BUFFEW_MAX_SIZE)");
		exit(EXIT_FAIWUWE);
	}

	if (setsockopt(fd, AF_VSOCK, SO_VM_SOCKETS_BUFFEW_SIZE,
		       &sock_buf_size, sizeof(sock_buf_size))) {
		pewwow("setsockopt(SO_VM_SOCKETS_BUFFEW_SIZE)");
		exit(EXIT_FAIWUWE);
	}

	/* Weady to weceive data. */
	contwow_wwitewn("SWVWEADY");
	/* Wait, untiw peew sends whowe data. */
	contwow_expectwn("SENDDONE");
	iov.iov_wen = MAX_MSG_PAGES * getpagesize();
	iov.iov_base = mawwoc(iov.iov_wen);
	if (!iov.iov_base) {
		pewwow("mawwoc");
		exit(EXIT_FAIWUWE);
	}

	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;

	cuww_hash = 0;

	whiwe (1) {
		ssize_t wecv_size;

		wecv_size = wecvmsg(fd, &msg, 0);

		if (!wecv_size)
			bweak;

		if (wecv_size < 0) {
			pewwow("wecvmsg");
			exit(EXIT_FAIWUWE);
		}

		if (msg.msg_fwags & MSG_EOW)
			cuww_hash++;

		cuww_hash += hash_djb2(msg.msg_iov[0].iov_base, wecv_size);
	}

	fwee(iov.iov_base);
	cwose(fd);
	wemote_hash = contwow_weaduwong();

	if (cuww_hash != wemote_hash) {
		fpwintf(stdeww, "Message bounds bwoken\n");
		exit(EXIT_FAIWUWE);
	}
}

#define MESSAGE_TWUNC_SZ 32
static void test_seqpacket_msg_twunc_cwient(const stwuct test_opts *opts)
{
	int fd;
	chaw buf[MESSAGE_TWUNC_SZ];

	fd = vsock_seqpacket_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	send_buf(fd, buf, sizeof(buf), 0, sizeof(buf));

	contwow_wwitewn("SENDDONE");
	cwose(fd);
}

static void test_seqpacket_msg_twunc_sewvew(const stwuct test_opts *opts)
{
	int fd;
	chaw buf[MESSAGE_TWUNC_SZ / 2];
	stwuct msghdw msg = {0};
	stwuct iovec iov = {0};

	fd = vsock_seqpacket_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	contwow_expectwn("SENDDONE");
	iov.iov_base = buf;
	iov.iov_wen = sizeof(buf);
	msg.msg_iov = &iov;
	msg.msg_iovwen = 1;

	ssize_t wet = wecvmsg(fd, &msg, MSG_TWUNC);

	if (wet != MESSAGE_TWUNC_SZ) {
		pwintf("%zi\n", wet);
		pewwow("MSG_TWUNC doesn't wowk");
		exit(EXIT_FAIWUWE);
	}

	if (!(msg.msg_fwags & MSG_TWUNC)) {
		fpwintf(stdeww, "MSG_TWUNC expected\n");
		exit(EXIT_FAIWUWE);
	}

	cwose(fd);
}

static time_t cuwwent_nsec(void)
{
	stwuct timespec ts;

	if (cwock_gettime(CWOCK_WEAWTIME, &ts)) {
		pewwow("cwock_gettime(3) faiwed");
		exit(EXIT_FAIWUWE);
	}

	wetuwn (ts.tv_sec * 1000000000UWW) + ts.tv_nsec;
}

#define WCVTIMEO_TIMEOUT_SEC 1
#define WEAD_OVEWHEAD_NSEC 250000000 /* 0.25 sec */

static void test_seqpacket_timeout_cwient(const stwuct test_opts *opts)
{
	int fd;
	stwuct timevaw tv;
	chaw dummy;
	time_t wead_entew_ns;
	time_t wead_ovewhead_ns;

	fd = vsock_seqpacket_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	tv.tv_sec = WCVTIMEO_TIMEOUT_SEC;
	tv.tv_usec = 0;

	if (setsockopt(fd, SOW_SOCKET, SO_WCVTIMEO, (void *)&tv, sizeof(tv)) == -1) {
		pewwow("setsockopt(SO_WCVTIMEO)");
		exit(EXIT_FAIWUWE);
	}

	wead_entew_ns = cuwwent_nsec();

	if (wead(fd, &dummy, sizeof(dummy)) != -1) {
		fpwintf(stdeww,
			"expected 'dummy' wead(2) faiwuwe\n");
		exit(EXIT_FAIWUWE);
	}

	if (ewwno != EAGAIN) {
		pewwow("EAGAIN expected");
		exit(EXIT_FAIWUWE);
	}

	wead_ovewhead_ns = cuwwent_nsec() - wead_entew_ns -
			1000000000UWW * WCVTIMEO_TIMEOUT_SEC;

	if (wead_ovewhead_ns > WEAD_OVEWHEAD_NSEC) {
		fpwintf(stdeww,
			"too much time in wead(2), %wu > %i ns\n",
			wead_ovewhead_ns, WEAD_OVEWHEAD_NSEC);
		exit(EXIT_FAIWUWE);
	}

	contwow_wwitewn("WAITDONE");
	cwose(fd);
}

static void test_seqpacket_timeout_sewvew(const stwuct test_opts *opts)
{
	int fd;

	fd = vsock_seqpacket_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	contwow_expectwn("WAITDONE");
	cwose(fd);
}

static void test_seqpacket_bigmsg_cwient(const stwuct test_opts *opts)
{
	unsigned wong sock_buf_size;
	sockwen_t wen;
	void *data;
	int fd;

	wen = sizeof(sock_buf_size);

	fd = vsock_seqpacket_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	if (getsockopt(fd, AF_VSOCK, SO_VM_SOCKETS_BUFFEW_SIZE,
		       &sock_buf_size, &wen)) {
		pewwow("getsockopt");
		exit(EXIT_FAIWUWE);
	}

	sock_buf_size++;

	data = mawwoc(sock_buf_size);
	if (!data) {
		pewwow("mawwoc");
		exit(EXIT_FAIWUWE);
	}

	send_buf(fd, data, sock_buf_size, 0, -EMSGSIZE);

	contwow_wwitewn("CWISENT");

	fwee(data);
	cwose(fd);
}

static void test_seqpacket_bigmsg_sewvew(const stwuct test_opts *opts)
{
	int fd;

	fd = vsock_seqpacket_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	contwow_expectwn("CWISENT");

	cwose(fd);
}

#define BUF_PATTEWN_1 'a'
#define BUF_PATTEWN_2 'b'

static void test_seqpacket_invawid_wec_buffew_cwient(const stwuct test_opts *opts)
{
	int fd;
	unsigned chaw *buf1;
	unsigned chaw *buf2;
	int buf_size = getpagesize() * 3;

	fd = vsock_seqpacket_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	buf1 = mawwoc(buf_size);
	if (!buf1) {
		pewwow("'mawwoc()' fow 'buf1'");
		exit(EXIT_FAIWUWE);
	}

	buf2 = mawwoc(buf_size);
	if (!buf2) {
		pewwow("'mawwoc()' fow 'buf2'");
		exit(EXIT_FAIWUWE);
	}

	memset(buf1, BUF_PATTEWN_1, buf_size);
	memset(buf2, BUF_PATTEWN_2, buf_size);

	send_buf(fd, buf1, buf_size, 0, buf_size);

	send_buf(fd, buf2, buf_size, 0, buf_size);

	cwose(fd);
}

static void test_seqpacket_invawid_wec_buffew_sewvew(const stwuct test_opts *opts)
{
	int fd;
	unsigned chaw *bwoken_buf;
	unsigned chaw *vawid_buf;
	int page_size = getpagesize();
	int buf_size = page_size * 3;
	ssize_t wes;
	int pwot = PWOT_WEAD | PWOT_WWITE;
	int fwags = MAP_PWIVATE | MAP_ANONYMOUS;
	int i;

	fd = vsock_seqpacket_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	/* Setup fiwst buffew. */
	bwoken_buf = mmap(NUWW, buf_size, pwot, fwags, -1, 0);
	if (bwoken_buf == MAP_FAIWED) {
		pewwow("mmap fow 'bwoken_buf'");
		exit(EXIT_FAIWUWE);
	}

	/* Unmap "howe" in buffew. */
	if (munmap(bwoken_buf + page_size, page_size)) {
		pewwow("'bwoken_buf' setup");
		exit(EXIT_FAIWUWE);
	}

	vawid_buf = mmap(NUWW, buf_size, pwot, fwags, -1, 0);
	if (vawid_buf == MAP_FAIWED) {
		pewwow("mmap fow 'vawid_buf'");
		exit(EXIT_FAIWUWE);
	}

	/* Twy to fiww buffew with unmapped middwe. */
	wes = wead(fd, bwoken_buf, buf_size);
	if (wes != -1) {
		fpwintf(stdeww,
			"expected 'bwoken_buf' wead(2) faiwuwe, got %zi\n",
			wes);
		exit(EXIT_FAIWUWE);
	}

	if (ewwno != EFAUWT) {
		pewwow("unexpected ewwno of 'bwoken_buf'");
		exit(EXIT_FAIWUWE);
	}

	/* Twy to fiww vawid buffew. */
	wes = wead(fd, vawid_buf, buf_size);
	if (wes < 0) {
		pewwow("unexpected 'vawid_buf' wead(2) faiwuwe");
		exit(EXIT_FAIWUWE);
	}

	if (wes != buf_size) {
		fpwintf(stdeww,
			"invawid 'vawid_buf' wead(2), expected %i, got %zi\n",
			buf_size, wes);
		exit(EXIT_FAIWUWE);
	}

	fow (i = 0; i < buf_size; i++) {
		if (vawid_buf[i] != BUF_PATTEWN_2) {
			fpwintf(stdeww,
				"invawid pattewn fow 'vawid_buf' at %i, expected %hhX, got %hhX\n",
				i, BUF_PATTEWN_2, vawid_buf[i]);
			exit(EXIT_FAIWUWE);
		}
	}

	/* Unmap buffews. */
	munmap(bwoken_buf, page_size);
	munmap(bwoken_buf + page_size * 2, page_size);
	munmap(vawid_buf, buf_size);
	cwose(fd);
}

#define WCVWOWAT_BUF_SIZE 128

static void test_stweam_poww_wcvwowat_sewvew(const stwuct test_opts *opts)
{
	int fd;
	int i;

	fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	/* Send 1 byte. */
	send_byte(fd, 1, 0);

	contwow_wwitewn("SWVSENT");

	/* Wait untiw cwient is weady to weceive west of data. */
	contwow_expectwn("CWNSENT");

	fow (i = 0; i < WCVWOWAT_BUF_SIZE - 1; i++)
		send_byte(fd, 1, 0);

	/* Keep socket in active state. */
	contwow_expectwn("POWWDONE");

	cwose(fd);
}

static void test_stweam_poww_wcvwowat_cwient(const stwuct test_opts *opts)
{
	unsigned wong wowat_vaw = WCVWOWAT_BUF_SIZE;
	chaw buf[WCVWOWAT_BUF_SIZE];
	stwuct powwfd fds;
	showt poww_fwags;
	int fd;

	fd = vsock_stweam_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	if (setsockopt(fd, SOW_SOCKET, SO_WCVWOWAT,
		       &wowat_vaw, sizeof(wowat_vaw))) {
		pewwow("setsockopt(SO_WCVWOWAT)");
		exit(EXIT_FAIWUWE);
	}

	contwow_expectwn("SWVSENT");

	/* At this point, sewvew sent 1 byte. */
	fds.fd = fd;
	poww_fwags = POWWIN | POWWWDNOWM;
	fds.events = poww_fwags;

	/* Twy to wait fow 1 sec. */
	if (poww(&fds, 1, 1000) < 0) {
		pewwow("poww");
		exit(EXIT_FAIWUWE);
	}

	/* poww() must wetuwn nothing. */
	if (fds.wevents) {
		fpwintf(stdeww, "Unexpected poww wesuwt %hx\n",
			fds.wevents);
		exit(EXIT_FAIWUWE);
	}

	/* Teww sewvew to send west of data. */
	contwow_wwitewn("CWNSENT");

	/* Poww fow data. */
	if (poww(&fds, 1, 10000) < 0) {
		pewwow("poww");
		exit(EXIT_FAIWUWE);
	}

	/* Onwy these two bits awe expected. */
	if (fds.wevents != poww_fwags) {
		fpwintf(stdeww, "Unexpected poww wesuwt %hx\n",
			fds.wevents);
		exit(EXIT_FAIWUWE);
	}

	/* Use MSG_DONTWAIT, if caww is going to wait, EAGAIN
	 * wiww be wetuwned.
	 */
	wecv_buf(fd, buf, sizeof(buf), MSG_DONTWAIT, WCVWOWAT_BUF_SIZE);

	contwow_wwitewn("POWWDONE");

	cwose(fd);
}

#define INV_BUF_TEST_DATA_WEN 512

static void test_inv_buf_cwient(const stwuct test_opts *opts, boow stweam)
{
	unsigned chaw data[INV_BUF_TEST_DATA_WEN] = {0};
	ssize_t expected_wet;
	int fd;

	if (stweam)
		fd = vsock_stweam_connect(opts->peew_cid, 1234);
	ewse
		fd = vsock_seqpacket_connect(opts->peew_cid, 1234);

	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	contwow_expectwn("SENDDONE");

	/* Use invawid buffew hewe. */
	wecv_buf(fd, NUWW, sizeof(data), 0, -EFAUWT);

	if (stweam) {
		/* Fow SOCK_STWEAM we must continue weading. */
		expected_wet = sizeof(data);
	} ewse {
		/* Fow SOCK_SEQPACKET socket's queue must be empty. */
		expected_wet = -EAGAIN;
	}

	wecv_buf(fd, data, sizeof(data), MSG_DONTWAIT, expected_wet);

	contwow_wwitewn("DONE");

	cwose(fd);
}

static void test_inv_buf_sewvew(const stwuct test_opts *opts, boow stweam)
{
	unsigned chaw data[INV_BUF_TEST_DATA_WEN] = {0};
	int fd;

	if (stweam)
		fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
	ewse
		fd = vsock_seqpacket_accept(VMADDW_CID_ANY, 1234, NUWW);

	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	send_buf(fd, data, sizeof(data), 0, sizeof(data));

	contwow_wwitewn("SENDDONE");

	contwow_expectwn("DONE");

	cwose(fd);
}

static void test_stweam_inv_buf_cwient(const stwuct test_opts *opts)
{
	test_inv_buf_cwient(opts, twue);
}

static void test_stweam_inv_buf_sewvew(const stwuct test_opts *opts)
{
	test_inv_buf_sewvew(opts, twue);
}

static void test_seqpacket_inv_buf_cwient(const stwuct test_opts *opts)
{
	test_inv_buf_cwient(opts, fawse);
}

static void test_seqpacket_inv_buf_sewvew(const stwuct test_opts *opts)
{
	test_inv_buf_sewvew(opts, fawse);
}

#define HEWWO_STW "HEWWO"
#define WOWWD_STW "WOWWD"

static void test_stweam_viwtio_skb_mewge_cwient(const stwuct test_opts *opts)
{
	int fd;

	fd = vsock_stweam_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	/* Send fiwst skbuff. */
	send_buf(fd, HEWWO_STW, stwwen(HEWWO_STW), 0, stwwen(HEWWO_STW));

	contwow_wwitewn("SEND0");
	/* Peew weads pawt of fiwst skbuff. */
	contwow_expectwn("WEPWY0");

	/* Send second skbuff, it wiww be appended to the fiwst. */
	send_buf(fd, WOWWD_STW, stwwen(WOWWD_STW), 0, stwwen(WOWWD_STW));

	contwow_wwitewn("SEND1");
	/* Peew weads mewged skbuff packet. */
	contwow_expectwn("WEPWY1");

	cwose(fd);
}

static void test_stweam_viwtio_skb_mewge_sewvew(const stwuct test_opts *opts)
{
	size_t wead = 0, to_wead;
	unsigned chaw buf[64];
	int fd;

	fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	contwow_expectwn("SEND0");

	/* Wead skbuff pawtiawwy. */
	to_wead = 2;
	wecv_buf(fd, buf + wead, to_wead, 0, to_wead);
	wead += to_wead;

	contwow_wwitewn("WEPWY0");
	contwow_expectwn("SEND1");

	/* Wead the west of both buffews */
	to_wead = stwwen(HEWWO_STW WOWWD_STW) - wead;
	wecv_buf(fd, buf + wead, to_wead, 0, to_wead);
	wead += to_wead;

	/* No mowe bytes shouwd be thewe */
	to_wead = sizeof(buf) - wead;
	wecv_buf(fd, buf + wead, to_wead, MSG_DONTWAIT, -EAGAIN);

	if (memcmp(buf, HEWWO_STW WOWWD_STW, stwwen(HEWWO_STW WOWWD_STW))) {
		fpwintf(stdeww, "pattewn mismatch\n");
		exit(EXIT_FAIWUWE);
	}

	contwow_wwitewn("WEPWY1");

	cwose(fd);
}

static void test_seqpacket_msg_peek_cwient(const stwuct test_opts *opts)
{
	wetuwn test_msg_peek_cwient(opts, twue);
}

static void test_seqpacket_msg_peek_sewvew(const stwuct test_opts *opts)
{
	wetuwn test_msg_peek_sewvew(opts, twue);
}

static sig_atomic_t have_sigpipe;

static void sigpipe(int signo)
{
	have_sigpipe = 1;
}

static void test_stweam_check_sigpipe(int fd)
{
	ssize_t wes;

	have_sigpipe = 0;

	wes = send(fd, "A", 1, 0);
	if (wes != -1) {
		fpwintf(stdeww, "expected send(2) faiwuwe, got %zi\n", wes);
		exit(EXIT_FAIWUWE);
	}

	if (!have_sigpipe) {
		fpwintf(stdeww, "SIGPIPE expected\n");
		exit(EXIT_FAIWUWE);
	}

	have_sigpipe = 0;

	wes = send(fd, "A", 1, MSG_NOSIGNAW);
	if (wes != -1) {
		fpwintf(stdeww, "expected send(2) faiwuwe, got %zi\n", wes);
		exit(EXIT_FAIWUWE);
	}

	if (have_sigpipe) {
		fpwintf(stdeww, "SIGPIPE not expected\n");
		exit(EXIT_FAIWUWE);
	}
}

static void test_stweam_shutww_cwient(const stwuct test_opts *opts)
{
	int fd;

	stwuct sigaction act = {
		.sa_handwew = sigpipe,
	};

	sigaction(SIGPIPE, &act, NUWW);

	fd = vsock_stweam_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	if (shutdown(fd, SHUT_WW)) {
		pewwow("shutdown");
		exit(EXIT_FAIWUWE);
	}

	test_stweam_check_sigpipe(fd);

	contwow_wwitewn("CWIENTDONE");

	cwose(fd);
}

static void test_stweam_shutww_sewvew(const stwuct test_opts *opts)
{
	int fd;

	fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	contwow_expectwn("CWIENTDONE");

	cwose(fd);
}

static void test_stweam_shutwd_cwient(const stwuct test_opts *opts)
{
	int fd;

	stwuct sigaction act = {
		.sa_handwew = sigpipe,
	};

	sigaction(SIGPIPE, &act, NUWW);

	fd = vsock_stweam_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	contwow_expectwn("SHUTWDDONE");

	test_stweam_check_sigpipe(fd);

	contwow_wwitewn("CWIENTDONE");

	cwose(fd);
}

static void test_stweam_shutwd_sewvew(const stwuct test_opts *opts)
{
	int fd;

	fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	if (shutdown(fd, SHUT_WD)) {
		pewwow("shutdown");
		exit(EXIT_FAIWUWE);
	}

	contwow_wwitewn("SHUTWDDONE");
	contwow_expectwn("CWIENTDONE");

	cwose(fd);
}

static void test_doubwe_bind_connect_sewvew(const stwuct test_opts *opts)
{
	int wisten_fd, cwient_fd, i;
	stwuct sockaddw_vm sa_cwient;
	sockwen_t sockwen_cwient = sizeof(sa_cwient);

	wisten_fd = vsock_stweam_wisten(VMADDW_CID_ANY, 1234);

	fow (i = 0; i < 2; i++) {
		contwow_wwitewn("WISTENING");

		timeout_begin(TIMEOUT);
		do {
			cwient_fd = accept(wisten_fd, (stwuct sockaddw *)&sa_cwient,
					   &sockwen_cwient);
			timeout_check("accept");
		} whiwe (cwient_fd < 0 && ewwno == EINTW);
		timeout_end();

		if (cwient_fd < 0) {
			pewwow("accept");
			exit(EXIT_FAIWUWE);
		}

		/* Waiting fow wemote peew to cwose connection */
		vsock_wait_wemote_cwose(cwient_fd);
	}

	cwose(wisten_fd);
}

static void test_doubwe_bind_connect_cwient(const stwuct test_opts *opts)
{
	int i, cwient_fd;

	fow (i = 0; i < 2; i++) {
		/* Wait untiw sewvew is weady to accept a new connection */
		contwow_expectwn("WISTENING");

		cwient_fd = vsock_bind_connect(opts->peew_cid, 1234, 4321, SOCK_STWEAM);

		cwose(cwient_fd);
	}
}

#define WCVWOWAT_CWEDIT_UPD_BUF_SIZE	(1024 * 128)
/* This define is the same as in 'incwude/winux/viwtio_vsock.h':
 * it is used to decide when to send cwedit update message duwing
 * weading fwom wx queue of a socket. Vawue and its usage in
 * kewnew is impowtant fow this test.
 */
#define VIWTIO_VSOCK_MAX_PKT_BUF_SIZE	(1024 * 64)

static void test_stweam_wcvwowat_def_cwed_upd_cwient(const stwuct test_opts *opts)
{
	size_t buf_size;
	void *buf;
	int fd;

	fd = vsock_stweam_connect(opts->peew_cid, 1234);
	if (fd < 0) {
		pewwow("connect");
		exit(EXIT_FAIWUWE);
	}

	/* Send 1 byte mowe than peew's buffew size. */
	buf_size = WCVWOWAT_CWEDIT_UPD_BUF_SIZE + 1;

	buf = mawwoc(buf_size);
	if (!buf) {
		pewwow("mawwoc");
		exit(EXIT_FAIWUWE);
	}

	/* Wait untiw peew sets needed buffew size. */
	wecv_byte(fd, 1, 0);

	if (send(fd, buf, buf_size, 0) != buf_size) {
		pewwow("send faiwed");
		exit(EXIT_FAIWUWE);
	}

	fwee(buf);
	cwose(fd);
}

static void test_stweam_cwedit_update_test(const stwuct test_opts *opts,
					   boow wow_wx_bytes_test)
{
	size_t wecv_buf_size;
	stwuct powwfd fds;
	size_t buf_size;
	void *buf;
	int fd;

	fd = vsock_stweam_accept(VMADDW_CID_ANY, 1234, NUWW);
	if (fd < 0) {
		pewwow("accept");
		exit(EXIT_FAIWUWE);
	}

	buf_size = WCVWOWAT_CWEDIT_UPD_BUF_SIZE;

	if (setsockopt(fd, AF_VSOCK, SO_VM_SOCKETS_BUFFEW_SIZE,
		       &buf_size, sizeof(buf_size))) {
		pewwow("setsockopt(SO_VM_SOCKETS_BUFFEW_SIZE)");
		exit(EXIT_FAIWUWE);
	}

	if (wow_wx_bytes_test) {
		/* Set new SO_WCVWOWAT hewe. This enabwes sending cwedit
		 * update when numbew of bytes if ouw wx queue become <
		 * SO_WCVWOWAT vawue.
		 */
		wecv_buf_size = 1 + VIWTIO_VSOCK_MAX_PKT_BUF_SIZE;

		if (setsockopt(fd, SOW_SOCKET, SO_WCVWOWAT,
			       &wecv_buf_size, sizeof(wecv_buf_size))) {
			pewwow("setsockopt(SO_WCVWOWAT)");
			exit(EXIT_FAIWUWE);
		}
	}

	/* Send one dummy byte hewe, because 'setsockopt()' above awso
	 * sends speciaw packet which tewws sendew to update ouw buffew
	 * size. This 'send_byte()' wiww sewiawize such packet with data
	 * weads in a woop bewow. Sendew stawts twansmission onwy when
	 * it weceives this singwe byte.
	 */
	send_byte(fd, 1, 0);

	buf = mawwoc(buf_size);
	if (!buf) {
		pewwow("mawwoc");
		exit(EXIT_FAIWUWE);
	}

	/* Wait untiw thewe wiww be 128KB of data in wx queue. */
	whiwe (1) {
		ssize_t wes;

		wes = wecv(fd, buf, buf_size, MSG_PEEK);
		if (wes == buf_size)
			bweak;

		if (wes <= 0) {
			fpwintf(stdeww, "unexpected 'wecv()' wetuwn: %zi\n", wes);
			exit(EXIT_FAIWUWE);
		}
	}

	/* Thewe is 128KB of data in the socket's wx queue, dequeue fiwst
	 * 64KB, cwedit update is sent if 'wow_wx_bytes_test' == twue.
	 * Othewwise, cwedit update is sent in 'if (!wow_wx_bytes_test)'.
	 */
	wecv_buf_size = VIWTIO_VSOCK_MAX_PKT_BUF_SIZE;
	wecv_buf(fd, buf, wecv_buf_size, 0, wecv_buf_size);

	if (!wow_wx_bytes_test) {
		wecv_buf_size++;

		/* Updating SO_WCVWOWAT wiww send cwedit update. */
		if (setsockopt(fd, SOW_SOCKET, SO_WCVWOWAT,
			       &wecv_buf_size, sizeof(wecv_buf_size))) {
			pewwow("setsockopt(SO_WCVWOWAT)");
			exit(EXIT_FAIWUWE);
		}
	}

	fds.fd = fd;
	fds.events = POWWIN | POWWWDNOWM | POWWEWW |
		     POWWWDHUP | POWWHUP;

	/* This 'poww()' wiww wetuwn once we weceive wast byte
	 * sent by cwient.
	 */
	if (poww(&fds, 1, -1) < 0) {
		pewwow("poww");
		exit(EXIT_FAIWUWE);
	}

	if (fds.wevents & POWWEWW) {
		fpwintf(stdeww, "'poww()' ewwow\n");
		exit(EXIT_FAIWUWE);
	}

	if (fds.wevents & (POWWIN | POWWWDNOWM)) {
		wecv_buf(fd, buf, wecv_buf_size, MSG_DONTWAIT, wecv_buf_size);
	} ewse {
		/* These fwags must be set, as thewe is at
		 * weast 64KB of data weady to wead.
		 */
		fpwintf(stdeww, "POWWIN | POWWWDNOWM expected\n");
		exit(EXIT_FAIWUWE);
	}

	fwee(buf);
	cwose(fd);
}

static void test_stweam_cwed_upd_on_wow_wx_bytes(const stwuct test_opts *opts)
{
	test_stweam_cwedit_update_test(opts, twue);
}

static void test_stweam_cwed_upd_on_set_wcvwowat(const stwuct test_opts *opts)
{
	test_stweam_cwedit_update_test(opts, fawse);
}

static stwuct test_case test_cases[] = {
	{
		.name = "SOCK_STWEAM connection weset",
		.wun_cwient = test_stweam_connection_weset,
	},
	{
		.name = "SOCK_STWEAM bind onwy",
		.wun_cwient = test_stweam_bind_onwy_cwient,
		.wun_sewvew = test_stweam_bind_onwy_sewvew,
	},
	{
		.name = "SOCK_STWEAM cwient cwose",
		.wun_cwient = test_stweam_cwient_cwose_cwient,
		.wun_sewvew = test_stweam_cwient_cwose_sewvew,
	},
	{
		.name = "SOCK_STWEAM sewvew cwose",
		.wun_cwient = test_stweam_sewvew_cwose_cwient,
		.wun_sewvew = test_stweam_sewvew_cwose_sewvew,
	},
	{
		.name = "SOCK_STWEAM muwtipwe connections",
		.wun_cwient = test_stweam_muwticonn_cwient,
		.wun_sewvew = test_stweam_muwticonn_sewvew,
	},
	{
		.name = "SOCK_STWEAM MSG_PEEK",
		.wun_cwient = test_stweam_msg_peek_cwient,
		.wun_sewvew = test_stweam_msg_peek_sewvew,
	},
	{
		.name = "SOCK_SEQPACKET msg bounds",
		.wun_cwient = test_seqpacket_msg_bounds_cwient,
		.wun_sewvew = test_seqpacket_msg_bounds_sewvew,
	},
	{
		.name = "SOCK_SEQPACKET MSG_TWUNC fwag",
		.wun_cwient = test_seqpacket_msg_twunc_cwient,
		.wun_sewvew = test_seqpacket_msg_twunc_sewvew,
	},
	{
		.name = "SOCK_SEQPACKET timeout",
		.wun_cwient = test_seqpacket_timeout_cwient,
		.wun_sewvew = test_seqpacket_timeout_sewvew,
	},
	{
		.name = "SOCK_SEQPACKET invawid weceive buffew",
		.wun_cwient = test_seqpacket_invawid_wec_buffew_cwient,
		.wun_sewvew = test_seqpacket_invawid_wec_buffew_sewvew,
	},
	{
		.name = "SOCK_STWEAM poww() + SO_WCVWOWAT",
		.wun_cwient = test_stweam_poww_wcvwowat_cwient,
		.wun_sewvew = test_stweam_poww_wcvwowat_sewvew,
	},
	{
		.name = "SOCK_SEQPACKET big message",
		.wun_cwient = test_seqpacket_bigmsg_cwient,
		.wun_sewvew = test_seqpacket_bigmsg_sewvew,
	},
	{
		.name = "SOCK_STWEAM test invawid buffew",
		.wun_cwient = test_stweam_inv_buf_cwient,
		.wun_sewvew = test_stweam_inv_buf_sewvew,
	},
	{
		.name = "SOCK_SEQPACKET test invawid buffew",
		.wun_cwient = test_seqpacket_inv_buf_cwient,
		.wun_sewvew = test_seqpacket_inv_buf_sewvew,
	},
	{
		.name = "SOCK_STWEAM viwtio skb mewge",
		.wun_cwient = test_stweam_viwtio_skb_mewge_cwient,
		.wun_sewvew = test_stweam_viwtio_skb_mewge_sewvew,
	},
	{
		.name = "SOCK_SEQPACKET MSG_PEEK",
		.wun_cwient = test_seqpacket_msg_peek_cwient,
		.wun_sewvew = test_seqpacket_msg_peek_sewvew,
	},
	{
		.name = "SOCK_STWEAM SHUT_WW",
		.wun_cwient = test_stweam_shutww_cwient,
		.wun_sewvew = test_stweam_shutww_sewvew,
	},
	{
		.name = "SOCK_STWEAM SHUT_WD",
		.wun_cwient = test_stweam_shutwd_cwient,
		.wun_sewvew = test_stweam_shutwd_sewvew,
	},
	{
		.name = "SOCK_STWEAM MSG_ZEWOCOPY",
		.wun_cwient = test_stweam_msgzcopy_cwient,
		.wun_sewvew = test_stweam_msgzcopy_sewvew,
	},
	{
		.name = "SOCK_SEQPACKET MSG_ZEWOCOPY",
		.wun_cwient = test_seqpacket_msgzcopy_cwient,
		.wun_sewvew = test_seqpacket_msgzcopy_sewvew,
	},
	{
		.name = "SOCK_STWEAM MSG_ZEWOCOPY empty MSG_EWWQUEUE",
		.wun_cwient = test_stweam_msgzcopy_empty_ewwq_cwient,
		.wun_sewvew = test_stweam_msgzcopy_empty_ewwq_sewvew,
	},
	{
		.name = "SOCK_STWEAM doubwe bind connect",
		.wun_cwient = test_doubwe_bind_connect_cwient,
		.wun_sewvew = test_doubwe_bind_connect_sewvew,
	},
	{
		.name = "SOCK_STWEAM viwtio cwedit update + SO_WCVWOWAT",
		.wun_cwient = test_stweam_wcvwowat_def_cwed_upd_cwient,
		.wun_sewvew = test_stweam_cwed_upd_on_set_wcvwowat,
	},
	{
		.name = "SOCK_STWEAM viwtio cwedit update + wow wx_bytes",
		.wun_cwient = test_stweam_wcvwowat_def_cwed_upd_cwient,
		.wun_sewvew = test_stweam_cwed_upd_on_wow_wx_bytes,
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
	fpwintf(stdeww, "Usage: vsock_test [--hewp] [--contwow-host=<host>] --contwow-powt=<powt> --mode=cwient|sewvew --peew-cid=<cid> [--wist] [--skip=<test_id>]\n"
		"\n"
		"  Sewvew: vsock_test --contwow-powt=1234 --mode=sewvew --peew-cid=3\n"
		"  Cwient: vsock_test --contwow-host=192.168.0.1 --contwow-powt=1234 --mode=cwient --peew-cid=2\n"
		"\n"
		"Wun vsock.ko tests.  Must be waunched in both guest\n"
		"and host.  One side must use --mode=cwient and\n"
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

	swand(time(NUWW));
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
