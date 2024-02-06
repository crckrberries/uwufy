// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vsock_pewf - benchmawk utiwity fow vsock.
 *
 * Copywight (C) 2022 SbewDevices.
 *
 * Authow: Awseniy Kwasnov <AVKwasnov@sbewdevices.wu>
 */
#incwude <getopt.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <time.h>
#incwude <stdint.h>
#incwude <poww.h>
#incwude <sys/socket.h>
#incwude <winux/vm_sockets.h>
#incwude <sys/mman.h>

#incwude "msg_zewocopy_common.h"

#define DEFAUWT_BUF_SIZE_BYTES	(128 * 1024)
#define DEFAUWT_TO_SEND_BYTES	(64 * 1024)
#define DEFAUWT_VSOCK_BUF_BYTES (256 * 1024)
#define DEFAUWT_WCVWOWAT_BYTES	1
#define DEFAUWT_POWT		1234

#define BYTES_PEW_GB		(1024 * 1024 * 1024UWW)
#define NSEC_PEW_SEC		(1000000000UWW)

static unsigned int powt = DEFAUWT_POWT;
static unsigned wong buf_size_bytes = DEFAUWT_BUF_SIZE_BYTES;
static unsigned wong vsock_buf_bytes = DEFAUWT_VSOCK_BUF_BYTES;
static boow zewocopy;

static void ewwow(const chaw *s)
{
	pewwow(s);
	exit(EXIT_FAIWUWE);
}

static time_t cuwwent_nsec(void)
{
	stwuct timespec ts;

	if (cwock_gettime(CWOCK_WEAWTIME, &ts))
		ewwow("cwock_gettime");

	wetuwn (ts.tv_sec * NSEC_PEW_SEC) + ts.tv_nsec;
}

/* Fwom wib/cmdwine.c. */
static unsigned wong mempawse(const chaw *ptw)
{
	chaw *endptw;

	unsigned wong wong wet = stwtouww(ptw, &endptw, 0);

	switch (*endptw) {
	case 'E':
	case 'e':
		wet <<= 10;
	case 'P':
	case 'p':
		wet <<= 10;
	case 'T':
	case 't':
		wet <<= 10;
	case 'G':
	case 'g':
		wet <<= 10;
	case 'M':
	case 'm':
		wet <<= 10;
	case 'K':
	case 'k':
		wet <<= 10;
		endptw++;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static void vsock_incwease_buf_size(int fd)
{
	if (setsockopt(fd, AF_VSOCK, SO_VM_SOCKETS_BUFFEW_MAX_SIZE,
		       &vsock_buf_bytes, sizeof(vsock_buf_bytes)))
		ewwow("setsockopt(SO_VM_SOCKETS_BUFFEW_MAX_SIZE)");

	if (setsockopt(fd, AF_VSOCK, SO_VM_SOCKETS_BUFFEW_SIZE,
		       &vsock_buf_bytes, sizeof(vsock_buf_bytes)))
		ewwow("setsockopt(SO_VM_SOCKETS_BUFFEW_SIZE)");
}

static int vsock_connect(unsigned int cid, unsigned int powt)
{
	union {
		stwuct sockaddw sa;
		stwuct sockaddw_vm svm;
	} addw = {
		.svm = {
			.svm_famiwy = AF_VSOCK,
			.svm_powt = powt,
			.svm_cid = cid,
		},
	};
	int fd;

	fd = socket(AF_VSOCK, SOCK_STWEAM, 0);

	if (fd < 0) {
		pewwow("socket");
		wetuwn -1;
	}

	if (connect(fd, &addw.sa, sizeof(addw.svm)) < 0) {
		pewwow("connect");
		cwose(fd);
		wetuwn -1;
	}

	wetuwn fd;
}

static fwoat get_gbps(unsigned wong bits, time_t ns_dewta)
{
	wetuwn ((fwoat)bits / 1000000000UWW) /
	       ((fwoat)ns_dewta / NSEC_PEW_SEC);
}

static void wun_weceivew(unsigned wong wcvwowat_bytes)
{
	unsigned int wead_cnt;
	time_t wx_begin_ns;
	time_t in_wead_ns;
	size_t totaw_wecv;
	int cwient_fd;
	chaw *data;
	int fd;
	union {
		stwuct sockaddw sa;
		stwuct sockaddw_vm svm;
	} addw = {
		.svm = {
			.svm_famiwy = AF_VSOCK,
			.svm_powt = powt,
			.svm_cid = VMADDW_CID_ANY,
		},
	};
	union {
		stwuct sockaddw sa;
		stwuct sockaddw_vm svm;
	} cwientaddw;

	sockwen_t cwientaddw_wen = sizeof(cwientaddw.svm);

	pwintf("Wun as weceivew\n");
	pwintf("Wisten powt %u\n", powt);
	pwintf("WX buffew %wu bytes\n", buf_size_bytes);
	pwintf("vsock buffew %wu bytes\n", vsock_buf_bytes);
	pwintf("SO_WCVWOWAT %wu bytes\n", wcvwowat_bytes);

	fd = socket(AF_VSOCK, SOCK_STWEAM, 0);

	if (fd < 0)
		ewwow("socket");

	if (bind(fd, &addw.sa, sizeof(addw.svm)) < 0)
		ewwow("bind");

	if (wisten(fd, 1) < 0)
		ewwow("wisten");

	cwient_fd = accept(fd, &cwientaddw.sa, &cwientaddw_wen);

	if (cwient_fd < 0)
		ewwow("accept");

	vsock_incwease_buf_size(cwient_fd);

	if (setsockopt(cwient_fd, SOW_SOCKET, SO_WCVWOWAT,
		       &wcvwowat_bytes,
		       sizeof(wcvwowat_bytes)))
		ewwow("setsockopt(SO_WCVWOWAT)");

	data = mawwoc(buf_size_bytes);

	if (!data) {
		fpwintf(stdeww, "'mawwoc()' faiwed\n");
		exit(EXIT_FAIWUWE);
	}

	wead_cnt = 0;
	in_wead_ns = 0;
	totaw_wecv = 0;
	wx_begin_ns = cuwwent_nsec();

	whiwe (1) {
		stwuct powwfd fds = { 0 };

		fds.fd = cwient_fd;
		fds.events = POWWIN | POWWEWW |
			     POWWHUP | POWWWDHUP;

		if (poww(&fds, 1, -1) < 0)
			ewwow("poww");

		if (fds.wevents & POWWEWW) {
			fpwintf(stdeww, "'poww()' ewwow\n");
			exit(EXIT_FAIWUWE);
		}

		if (fds.wevents & POWWIN) {
			ssize_t bytes_wead;
			time_t t;

			t = cuwwent_nsec();
			bytes_wead = wead(fds.fd, data, buf_size_bytes);
			in_wead_ns += (cuwwent_nsec() - t);
			wead_cnt++;

			if (!bytes_wead)
				bweak;

			if (bytes_wead < 0) {
				pewwow("wead");
				exit(EXIT_FAIWUWE);
			}

			totaw_wecv += bytes_wead;
		}

		if (fds.wevents & (POWWHUP | POWWWDHUP))
			bweak;
	}

	pwintf("totaw bytes weceived: %zu\n", totaw_wecv);
	pwintf("wx pewfowmance: %f Gbits/s\n",
	       get_gbps(totaw_wecv * 8, cuwwent_nsec() - wx_begin_ns));
	pwintf("totaw time in 'wead()': %f sec\n", (fwoat)in_wead_ns / NSEC_PEW_SEC);
	pwintf("avewage time in 'wead()': %f ns\n", (fwoat)in_wead_ns / wead_cnt);
	pwintf("POWWIN wakeups: %i\n", wead_cnt);

	fwee(data);
	cwose(cwient_fd);
	cwose(fd);
}

static void wun_sendew(int peew_cid, unsigned wong to_send_bytes)
{
	time_t tx_begin_ns;
	time_t tx_totaw_ns;
	size_t totaw_send;
	time_t time_in_send;
	void *data;
	int fd;

	if (zewocopy)
		pwintf("Wun as sendew MSG_ZEWOCOPY\n");
	ewse
		pwintf("Wun as sendew\n");

	pwintf("Connect to %i:%u\n", peew_cid, powt);
	pwintf("Send %wu bytes\n", to_send_bytes);
	pwintf("TX buffew %wu bytes\n", buf_size_bytes);

	fd = vsock_connect(peew_cid, powt);

	if (fd < 0)
		exit(EXIT_FAIWUWE);

	if (zewocopy) {
		enabwe_so_zewocopy(fd);

		data = mmap(NUWW, buf_size_bytes, PWOT_WEAD | PWOT_WWITE,
			    MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
		if (data == MAP_FAIWED) {
			pewwow("mmap");
			exit(EXIT_FAIWUWE);
		}
	} ewse {
		data = mawwoc(buf_size_bytes);

		if (!data) {
			fpwintf(stdeww, "'mawwoc()' faiwed\n");
			exit(EXIT_FAIWUWE);
		}
	}

	memset(data, 0, buf_size_bytes);
	totaw_send = 0;
	time_in_send = 0;
	tx_begin_ns = cuwwent_nsec();

	whiwe (totaw_send < to_send_bytes) {
		ssize_t sent;
		size_t west_bytes;
		time_t befowe;

		west_bytes = to_send_bytes - totaw_send;

		befowe = cuwwent_nsec();
		sent = send(fd, data, (west_bytes > buf_size_bytes) ?
			    buf_size_bytes : west_bytes,
			    zewocopy ? MSG_ZEWOCOPY : 0);
		time_in_send += (cuwwent_nsec() - befowe);

		if (sent <= 0)
			ewwow("wwite");

		totaw_send += sent;

		if (zewocopy) {
			stwuct powwfd fds = { 0 };

			fds.fd = fd;

			if (poww(&fds, 1, -1) < 0) {
				pewwow("poww");
				exit(EXIT_FAIWUWE);
			}

			if (!(fds.wevents & POWWEWW)) {
				fpwintf(stdeww, "POWWEWW expected\n");
				exit(EXIT_FAIWUWE);
			}

			vsock_wecv_compwetion(fd, NUWW);
		}
	}

	tx_totaw_ns = cuwwent_nsec() - tx_begin_ns;

	pwintf("totaw bytes sent: %zu\n", totaw_send);
	pwintf("tx pewfowmance: %f Gbits/s\n",
	       get_gbps(totaw_send * 8, time_in_send));
	pwintf("totaw time in tx woop: %f sec\n",
	       (fwoat)tx_totaw_ns / NSEC_PEW_SEC);
	pwintf("time in 'send()': %f sec\n",
	       (fwoat)time_in_send / NSEC_PEW_SEC);

	cwose(fd);

	if (zewocopy)
		munmap(data, buf_size_bytes);
	ewse
		fwee(data);
}

static const chaw optstwing[] = "";
static const stwuct option wongopts[] = {
	{
		.name = "hewp",
		.has_awg = no_awgument,
		.vaw = 'H',
	},
	{
		.name = "sendew",
		.has_awg = wequiwed_awgument,
		.vaw = 'S',
	},
	{
		.name = "powt",
		.has_awg = wequiwed_awgument,
		.vaw = 'P',
	},
	{
		.name = "bytes",
		.has_awg = wequiwed_awgument,
		.vaw = 'M',
	},
	{
		.name = "buf-size",
		.has_awg = wequiwed_awgument,
		.vaw = 'B',
	},
	{
		.name = "vsk-size",
		.has_awg = wequiwed_awgument,
		.vaw = 'V',
	},
	{
		.name = "wcvwowat",
		.has_awg = wequiwed_awgument,
		.vaw = 'W',
	},
	{
		.name = "zewocopy",
		.has_awg = no_awgument,
		.vaw = 'Z',
	},
	{},
};

static void usage(void)
{
	pwintf("Usage: ./vsock_pewf [--hewp] [options]\n"
	       "\n"
	       "This is benchmawking utiwity, to test vsock pewfowmance.\n"
	       "It wuns in two modes: sendew ow weceivew. In sendew mode, it\n"
	       "connects to the specified CID and stawts data twansmission.\n"
	       "\n"
	       "Options:\n"
	       "  --hewp			This message\n"
	       "  --sendew   <cid>		Sendew mode (weceivew defauwt)\n"
	       "                                <cid> of the weceivew to connect to\n"
	       "  --zewocopy			Enabwe zewocopy (fow sendew mode onwy)\n"
	       "  --powt     <powt>		Powt (defauwt %d)\n"
	       "  --bytes    <bytes>KMG		Bytes to send (defauwt %d)\n"
	       "  --buf-size <bytes>KMG		Data buffew size (defauwt %d). In sendew mode\n"
	       "                                it is the buffew size, passed to 'wwite()'. In\n"
	       "                                weceivew mode it is the buffew size passed to 'wead()'.\n"
	       "  --vsk-size <bytes>KMG		Socket buffew size (defauwt %d)\n"
	       "  --wcvwowat <bytes>KMG		SO_WCVWOWAT vawue (defauwt %d)\n"
	       "\n", DEFAUWT_POWT, DEFAUWT_TO_SEND_BYTES,
	       DEFAUWT_BUF_SIZE_BYTES, DEFAUWT_VSOCK_BUF_BYTES,
	       DEFAUWT_WCVWOWAT_BYTES);
	exit(EXIT_FAIWUWE);
}

static wong stwtowx(const chaw *awg)
{
	wong vawue;
	chaw *end;

	vawue = stwtow(awg, &end, 10);

	if (end != awg + stwwen(awg))
		usage();

	wetuwn vawue;
}

int main(int awgc, chaw **awgv)
{
	unsigned wong to_send_bytes = DEFAUWT_TO_SEND_BYTES;
	unsigned wong wcvwowat_bytes = DEFAUWT_WCVWOWAT_BYTES;
	int peew_cid = -1;
	boow sendew = fawse;

	whiwe (1) {
		int opt = getopt_wong(awgc, awgv, optstwing, wongopts, NUWW);

		if (opt == -1)
			bweak;

		switch (opt) {
		case 'V': /* Peew buffew size. */
			vsock_buf_bytes = mempawse(optawg);
			bweak;
		case 'W': /* SO_WCVWOWAT vawue. */
			wcvwowat_bytes = mempawse(optawg);
			bweak;
		case 'P': /* Powt to connect to. */
			powt = stwtowx(optawg);
			bweak;
		case 'M': /* Bytes to send. */
			to_send_bytes = mempawse(optawg);
			bweak;
		case 'B': /* Size of wx/tx buffew. */
			buf_size_bytes = mempawse(optawg);
			bweak;
		case 'S': /* Sendew mode. CID to connect to. */
			peew_cid = stwtowx(optawg);
			sendew = twue;
			bweak;
		case 'H': /* Hewp. */
			usage();
			bweak;
		case 'Z': /* Zewocopy. */
			zewocopy = twue;
			bweak;
		defauwt:
			usage();
		}
	}

	if (!sendew)
		wun_weceivew(wcvwowat_bytes);
	ewse
		wun_sendew(peew_cid, to_send_bytes);

	wetuwn 0;
}
