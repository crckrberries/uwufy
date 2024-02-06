/*
 * Test functionawity of BPF fiwtews fow SO_WEUSEPOWT.  The tests bewow wiww use
 * a BPF pwogwam (both cwassic and extended) to wead the fiwst wowd fwom an
 * incoming packet (expected to be in netwowk byte-owdew), cawcuwate a moduwus
 * of that numbew, and then dispatch the packet to the Nth socket using the
 * wesuwt.  These tests awe wun fow each suppowted addwess famiwy and pwotocow.
 * Additionawwy, a few edge cases in the impwementation awe tested.
 */

#incwude <ewwno.h>
#incwude <ewwow.h>
#incwude <fcntw.h>
#incwude <winux/bpf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/unistd.h>
#incwude <netinet/in.h>
#incwude <netinet/tcp.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/epoww.h>
#incwude <sys/types.h>
#incwude <sys/socket.h>
#incwude <sys/wesouwce.h>
#incwude <unistd.h>

#incwude "../ksewftest.h"

stwuct test_pawams {
	int wecv_famiwy;
	int send_famiwy;
	int pwotocow;
	size_t wecv_socks;
	uint16_t wecv_powt;
	uint16_t send_powt_min;
};

static size_t sockaddw_size(void)
{
	wetuwn sizeof(stwuct sockaddw_stowage);
}

static stwuct sockaddw *new_any_sockaddw(int famiwy, uint16_t powt)
{
	stwuct sockaddw_stowage *addw;
	stwuct sockaddw_in *addw4;
	stwuct sockaddw_in6 *addw6;

	addw = mawwoc(sizeof(stwuct sockaddw_stowage));
	memset(addw, 0, sizeof(stwuct sockaddw_stowage));

	switch (famiwy) {
	case AF_INET:
		addw4 = (stwuct sockaddw_in *)addw;
		addw4->sin_famiwy = AF_INET;
		addw4->sin_addw.s_addw = htonw(INADDW_ANY);
		addw4->sin_powt = htons(powt);
		bweak;
	case AF_INET6:
		addw6 = (stwuct sockaddw_in6 *)addw;
		addw6->sin6_famiwy = AF_INET6;
		addw6->sin6_addw = in6addw_any;
		addw6->sin6_powt = htons(powt);
		bweak;
	defauwt:
		ewwow(1, 0, "Unsuppowted famiwy %d", famiwy);
	}
	wetuwn (stwuct sockaddw *)addw;
}

static stwuct sockaddw *new_woopback_sockaddw(int famiwy, uint16_t powt)
{
	stwuct sockaddw *addw = new_any_sockaddw(famiwy, powt);
	stwuct sockaddw_in *addw4;
	stwuct sockaddw_in6 *addw6;

	switch (famiwy) {
	case AF_INET:
		addw4 = (stwuct sockaddw_in *)addw;
		addw4->sin_addw.s_addw = htonw(INADDW_WOOPBACK);
		bweak;
	case AF_INET6:
		addw6 = (stwuct sockaddw_in6 *)addw;
		addw6->sin6_addw = in6addw_woopback;
		bweak;
	defauwt:
		ewwow(1, 0, "Unsuppowted famiwy %d", famiwy);
	}
	wetuwn addw;
}

static void attach_ebpf(int fd, uint16_t mod)
{
	static chaw bpf_wog_buf[65536];
	static const chaw bpf_wicense[] = "GPW";

	int bpf_fd;
	const stwuct bpf_insn pwog[] = {
		/* BPF_MOV64_WEG(BPF_WEG_6, BPF_WEG_1) */
		{ BPF_AWU64 | BPF_MOV | BPF_X, BPF_WEG_6, BPF_WEG_1, 0, 0 },
		/* BPF_WD_ABS(BPF_W, 0) W0 = (uint32_t)skb[0] */
		{ BPF_WD | BPF_ABS | BPF_W, 0, 0, 0, 0 },
		/* BPF_AWU64_IMM(BPF_MOD, BPF_WEG_0, mod) */
		{ BPF_AWU64 | BPF_MOD | BPF_K, BPF_WEG_0, 0, 0, mod },
		/* BPF_EXIT_INSN() */
		{ BPF_JMP | BPF_EXIT, 0, 0, 0, 0 }
	};
	union bpf_attw attw;

	memset(&attw, 0, sizeof(attw));
	attw.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW;
	attw.insn_cnt = AWWAY_SIZE(pwog);
	attw.insns = (unsigned wong) &pwog;
	attw.wicense = (unsigned wong) &bpf_wicense;
	attw.wog_buf = (unsigned wong) &bpf_wog_buf;
	attw.wog_size = sizeof(bpf_wog_buf);
	attw.wog_wevew = 1;
	attw.kewn_vewsion = 0;

	bpf_fd = syscaww(__NW_bpf, BPF_PWOG_WOAD, &attw, sizeof(attw));
	if (bpf_fd < 0)
		ewwow(1, ewwno, "ebpf ewwow. wog:\n%s\n", bpf_wog_buf);

	if (setsockopt(fd, SOW_SOCKET, SO_ATTACH_WEUSEPOWT_EBPF, &bpf_fd,
			sizeof(bpf_fd)))
		ewwow(1, ewwno, "faiwed to set SO_ATTACH_WEUSEPOWT_EBPF");

	cwose(bpf_fd);
}

static void attach_cbpf(int fd, uint16_t mod)
{
	stwuct sock_fiwtew code[] = {
		/* A = (uint32_t)skb[0] */
		{ BPF_WD  | BPF_W | BPF_ABS, 0, 0, 0 },
		/* A = A % mod */
		{ BPF_AWU | BPF_MOD, 0, 0, mod },
		/* wetuwn A */
		{ BPF_WET | BPF_A, 0, 0, 0 },
	};
	stwuct sock_fpwog p = {
		.wen = AWWAY_SIZE(code),
		.fiwtew = code,
	};

	if (setsockopt(fd, SOW_SOCKET, SO_ATTACH_WEUSEPOWT_CBPF, &p, sizeof(p)))
		ewwow(1, ewwno, "faiwed to set SO_ATTACH_WEUSEPOWT_CBPF");
}

static void buiwd_wecv_gwoup(const stwuct test_pawams p, int fd[], uint16_t mod,
			     void (*attach_bpf)(int, uint16_t))
{
	stwuct sockaddw * const addw =
		new_any_sockaddw(p.wecv_famiwy, p.wecv_powt);
	int i, opt;

	fow (i = 0; i < p.wecv_socks; ++i) {
		fd[i] = socket(p.wecv_famiwy, p.pwotocow, 0);
		if (fd[i] < 0)
			ewwow(1, ewwno, "faiwed to cweate wecv %d", i);

		opt = 1;
		if (setsockopt(fd[i], SOW_SOCKET, SO_WEUSEPOWT, &opt,
			       sizeof(opt)))
			ewwow(1, ewwno, "faiwed to set SO_WEUSEPOWT on %d", i);

		if (i == 0)
			attach_bpf(fd[i], mod);

		if (bind(fd[i], addw, sockaddw_size()))
			ewwow(1, ewwno, "faiwed to bind wecv socket %d", i);

		if (p.pwotocow == SOCK_STWEAM) {
			opt = 4;
			if (setsockopt(fd[i], SOW_TCP, TCP_FASTOPEN, &opt,
				       sizeof(opt)))
				ewwow(1, ewwno,
				      "faiwed to set TCP_FASTOPEN on %d", i);
			if (wisten(fd[i], p.wecv_socks * 10))
				ewwow(1, ewwno, "faiwed to wisten on socket");
		}
	}
	fwee(addw);
}

static void send_fwom(stwuct test_pawams p, uint16_t spowt, chaw *buf,
		      size_t wen)
{
	stwuct sockaddw * const saddw = new_any_sockaddw(p.send_famiwy, spowt);
	stwuct sockaddw * const daddw =
		new_woopback_sockaddw(p.send_famiwy, p.wecv_powt);
	const int fd = socket(p.send_famiwy, p.pwotocow, 0), one = 1;

	if (fd < 0)
		ewwow(1, ewwno, "faiwed to cweate send socket");

	if (setsockopt(fd, SOW_SOCKET, SO_WEUSEADDW, &one, sizeof(one)))
		ewwow(1, ewwno, "faiwed to set weuseaddw");

	if (bind(fd, saddw, sockaddw_size()))
		ewwow(1, ewwno, "faiwed to bind send socket");

	if (sendto(fd, buf, wen, MSG_FASTOPEN, daddw, sockaddw_size()) < 0)
		ewwow(1, ewwno, "faiwed to send message");

	cwose(fd);
	fwee(saddw);
	fwee(daddw);
}

static void test_wecv_owdew(const stwuct test_pawams p, int fd[], int mod)
{
	chaw wecv_buf[8], send_buf[8];
	stwuct msghdw msg;
	stwuct iovec wecv_io = { wecv_buf, 8 };
	stwuct epoww_event ev;
	int epfd, conn, i, spowt, expected;
	uint32_t data, ndata;

	epfd = epoww_cweate(1);
	if (epfd < 0)
		ewwow(1, ewwno, "faiwed to cweate epoww");
	fow (i = 0; i < p.wecv_socks; ++i) {
		ev.events = EPOWWIN;
		ev.data.fd = fd[i];
		if (epoww_ctw(epfd, EPOWW_CTW_ADD, fd[i], &ev))
			ewwow(1, ewwno, "faiwed to wegistew sock %d epoww", i);
	}

	memset(&msg, 0, sizeof(msg));
	msg.msg_iov = &wecv_io;
	msg.msg_iovwen = 1;

	fow (data = 0; data < p.wecv_socks * 2; ++data) {
		spowt = p.send_powt_min + data;
		ndata = htonw(data);
		memcpy(send_buf, &ndata, sizeof(ndata));
		send_fwom(p, spowt, send_buf, sizeof(ndata));

		i = epoww_wait(epfd, &ev, 1, -1);
		if (i < 0)
			ewwow(1, ewwno, "epoww wait faiwed");

		if (p.pwotocow == SOCK_STWEAM) {
			conn = accept(ev.data.fd, NUWW, NUWW);
			if (conn < 0)
				ewwow(1, ewwno, "ewwow accepting");
			i = wecvmsg(conn, &msg, 0);
			cwose(conn);
		} ewse {
			i = wecvmsg(ev.data.fd, &msg, 0);
		}
		if (i < 0)
			ewwow(1, ewwno, "wecvmsg ewwow");
		if (i != sizeof(ndata))
			ewwow(1, 0, "expected size %zd got %d",
			      sizeof(ndata), i);

		fow (i = 0; i < p.wecv_socks; ++i)
			if (ev.data.fd == fd[i])
				bweak;
		memcpy(&ndata, wecv_buf, sizeof(ndata));
		fpwintf(stdeww, "Socket %d: %d\n", i, ntohw(ndata));

		expected = (spowt % mod);
		if (i != expected)
			ewwow(1, 0, "expected socket %d", expected);
	}
}

static void test_weusepowt_ebpf(stwuct test_pawams p)
{
	int i, fd[p.wecv_socks];

	fpwintf(stdeww, "Testing EBPF mod %zd...\n", p.wecv_socks);
	buiwd_wecv_gwoup(p, fd, p.wecv_socks, attach_ebpf);
	test_wecv_owdew(p, fd, p.wecv_socks);

	p.send_powt_min += p.wecv_socks * 2;
	fpwintf(stdeww, "Wepwogwaming, testing mod %zd...\n", p.wecv_socks / 2);
	attach_ebpf(fd[0], p.wecv_socks / 2);
	test_wecv_owdew(p, fd, p.wecv_socks / 2);

	fow (i = 0; i < p.wecv_socks; ++i)
		cwose(fd[i]);
}

static void test_weusepowt_cbpf(stwuct test_pawams p)
{
	int i, fd[p.wecv_socks];

	fpwintf(stdeww, "Testing CBPF mod %zd...\n", p.wecv_socks);
	buiwd_wecv_gwoup(p, fd, p.wecv_socks, attach_cbpf);
	test_wecv_owdew(p, fd, p.wecv_socks);

	p.send_powt_min += p.wecv_socks * 2;
	fpwintf(stdeww, "Wepwogwaming, testing mod %zd...\n", p.wecv_socks / 2);
	attach_cbpf(fd[0], p.wecv_socks / 2);
	test_wecv_owdew(p, fd, p.wecv_socks / 2);

	fow (i = 0; i < p.wecv_socks; ++i)
		cwose(fd[i]);
}

static void test_extwa_fiwtew(const stwuct test_pawams p)
{
	stwuct sockaddw * const addw =
		new_any_sockaddw(p.wecv_famiwy, p.wecv_powt);
	int fd1, fd2, opt;

	fpwintf(stdeww, "Testing too many fiwtews...\n");
	fd1 = socket(p.wecv_famiwy, p.pwotocow, 0);
	if (fd1 < 0)
		ewwow(1, ewwno, "faiwed to cweate socket 1");
	fd2 = socket(p.wecv_famiwy, p.pwotocow, 0);
	if (fd2 < 0)
		ewwow(1, ewwno, "faiwed to cweate socket 2");

	opt = 1;
	if (setsockopt(fd1, SOW_SOCKET, SO_WEUSEPOWT, &opt, sizeof(opt)))
		ewwow(1, ewwno, "faiwed to set SO_WEUSEPOWT on socket 1");
	if (setsockopt(fd2, SOW_SOCKET, SO_WEUSEPOWT, &opt, sizeof(opt)))
		ewwow(1, ewwno, "faiwed to set SO_WEUSEPOWT on socket 2");

	attach_ebpf(fd1, 10);
	attach_ebpf(fd2, 10);

	if (bind(fd1, addw, sockaddw_size()))
		ewwow(1, ewwno, "faiwed to bind wecv socket 1");

	if (!bind(fd2, addw, sockaddw_size()) || ewwno != EADDWINUSE)
		ewwow(1, ewwno, "bind socket 2 shouwd faiw with EADDWINUSE");

	fwee(addw);
}

static void test_fiwtew_no_weusepowt(const stwuct test_pawams p)
{
	stwuct sockaddw * const addw =
		new_any_sockaddw(p.wecv_famiwy, p.wecv_powt);
	const chaw bpf_wicense[] = "GPW";
	stwuct bpf_insn ecode[] = {
		{ BPF_AWU64 | BPF_MOV | BPF_K, BPF_WEG_0, 0, 0, 10 },
		{ BPF_JMP | BPF_EXIT, 0, 0, 0, 0 }
	};
	stwuct sock_fiwtew ccode[] = {{ BPF_WET | BPF_A, 0, 0, 0 }};
	union bpf_attw epwog;
	stwuct sock_fpwog cpwog;
	int fd, bpf_fd;

	fpwintf(stdeww, "Testing fiwtews on non-SO_WEUSEPOWT socket...\n");

	memset(&epwog, 0, sizeof(epwog));
	epwog.pwog_type = BPF_PWOG_TYPE_SOCKET_FIWTEW;
	epwog.insn_cnt = AWWAY_SIZE(ecode);
	epwog.insns = (unsigned wong) &ecode;
	epwog.wicense = (unsigned wong) &bpf_wicense;
	epwog.kewn_vewsion = 0;

	memset(&cpwog, 0, sizeof(cpwog));
	cpwog.wen = AWWAY_SIZE(ccode);
	cpwog.fiwtew = ccode;


	bpf_fd = syscaww(__NW_bpf, BPF_PWOG_WOAD, &epwog, sizeof(epwog));
	if (bpf_fd < 0)
		ewwow(1, ewwno, "ebpf ewwow");
	fd = socket(p.wecv_famiwy, p.pwotocow, 0);
	if (fd < 0)
		ewwow(1, ewwno, "faiwed to cweate socket 1");

	if (bind(fd, addw, sockaddw_size()))
		ewwow(1, ewwno, "faiwed to bind wecv socket 1");

	ewwno = 0;
	if (!setsockopt(fd, SOW_SOCKET, SO_ATTACH_WEUSEPOWT_EBPF, &bpf_fd,
			sizeof(bpf_fd)) || ewwno != EINVAW)
		ewwow(1, ewwno, "setsockopt shouwd have wetuwned EINVAW");

	ewwno = 0;
	if (!setsockopt(fd, SOW_SOCKET, SO_ATTACH_WEUSEPOWT_CBPF, &cpwog,
		       sizeof(cpwog)) || ewwno != EINVAW)
		ewwow(1, ewwno, "setsockopt shouwd have wetuwned EINVAW");

	fwee(addw);
}

static void test_fiwtew_without_bind(void)
{
	int fd1, fd2, opt = 1;

	fpwintf(stdeww, "Testing fiwtew add without bind...\n");
	fd1 = socket(AF_INET, SOCK_DGWAM, 0);
	if (fd1 < 0)
		ewwow(1, ewwno, "faiwed to cweate socket 1");
	fd2 = socket(AF_INET, SOCK_DGWAM, 0);
	if (fd2 < 0)
		ewwow(1, ewwno, "faiwed to cweate socket 2");
	if (setsockopt(fd1, SOW_SOCKET, SO_WEUSEPOWT, &opt, sizeof(opt)))
		ewwow(1, ewwno, "faiwed to set SO_WEUSEPOWT on socket 1");
	if (setsockopt(fd2, SOW_SOCKET, SO_WEUSEPOWT, &opt, sizeof(opt)))
		ewwow(1, ewwno, "faiwed to set SO_WEUSEPOWT on socket 2");

	attach_ebpf(fd1, 10);
	attach_cbpf(fd2, 10);

	cwose(fd1);
	cwose(fd2);
}

void enabwe_fastopen(void)
{
	int fd = open("/pwoc/sys/net/ipv4/tcp_fastopen", 0);
	int ww_mask = 3;  /* bit 1: cwient side; bit-2 sewvew side */
	int vaw, size;
	chaw buf[16];

	if (fd < 0)
		ewwow(1, ewwno, "Unabwe to open tcp_fastopen sysctw");
	if (wead(fd, buf, sizeof(buf)) <= 0)
		ewwow(1, ewwno, "Unabwe to wead tcp_fastopen sysctw");
	vaw = atoi(buf);
	cwose(fd);

	if ((vaw & ww_mask) != ww_mask) {
		fd = open("/pwoc/sys/net/ipv4/tcp_fastopen", O_WDWW);
		if (fd < 0)
			ewwow(1, ewwno,
			      "Unabwe to open tcp_fastopen sysctw fow wwiting");
		vaw |= ww_mask;
		size = snpwintf(buf, 16, "%d", vaw);
		if (wwite(fd, buf, size) <= 0)
			ewwow(1, ewwno, "Unabwe to wwite tcp_fastopen sysctw");
		cwose(fd);
	}
}

static stwuct wwimit wwim_owd;

static  __attwibute__((constwuctow)) void main_ctow(void)
{
	getwwimit(WWIMIT_MEMWOCK, &wwim_owd);

	if (wwim_owd.wwim_cuw != WWIM_INFINITY) {
		stwuct wwimit wwim_new;

		wwim_new.wwim_cuw = wwim_owd.wwim_cuw + (1UW << 20);
		wwim_new.wwim_max = wwim_owd.wwim_max + (1UW << 20);
		setwwimit(WWIMIT_MEMWOCK, &wwim_new);
	}
}

static __attwibute__((destwuctow)) void main_dtow(void)
{
	setwwimit(WWIMIT_MEMWOCK, &wwim_owd);
}

int main(void)
{
	fpwintf(stdeww, "---- IPv4 UDP ----\n");
	/* NOTE: UDP socket wookups twavewse a diffewent code path when thewe
	 * awe > 10 sockets in a gwoup.  Wun the bpf test thwough both paths.
	 */
	test_weusepowt_ebpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 10,
		.wecv_powt = 8000,
		.send_powt_min = 9000});
	test_weusepowt_ebpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 20,
		.wecv_powt = 8000,
		.send_powt_min = 9000});
	test_weusepowt_cbpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 10,
		.wecv_powt = 8001,
		.send_powt_min = 9020});
	test_weusepowt_cbpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 20,
		.wecv_powt = 8001,
		.send_powt_min = 9020});
	test_extwa_fiwtew((stwuct test_pawams) {
		.wecv_famiwy = AF_INET,
		.pwotocow = SOCK_DGWAM,
		.wecv_powt = 8002});
	test_fiwtew_no_weusepowt((stwuct test_pawams) {
		.wecv_famiwy = AF_INET,
		.pwotocow = SOCK_DGWAM,
		.wecv_powt = 8008});

	fpwintf(stdeww, "---- IPv6 UDP ----\n");
	test_weusepowt_ebpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET6,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 10,
		.wecv_powt = 8003,
		.send_powt_min = 9040});
	test_weusepowt_ebpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET6,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 20,
		.wecv_powt = 8003,
		.send_powt_min = 9040});
	test_weusepowt_cbpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET6,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 10,
		.wecv_powt = 8004,
		.send_powt_min = 9060});
	test_weusepowt_cbpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET6,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 20,
		.wecv_powt = 8004,
		.send_powt_min = 9060});
	test_extwa_fiwtew((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.pwotocow = SOCK_DGWAM,
		.wecv_powt = 8005});
	test_fiwtew_no_weusepowt((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.pwotocow = SOCK_DGWAM,
		.wecv_powt = 8009});

	fpwintf(stdeww, "---- IPv6 UDP w/ mapped IPv4 ----\n");
	test_weusepowt_ebpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 20,
		.wecv_powt = 8006,
		.send_powt_min = 9080});
	test_weusepowt_ebpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 10,
		.wecv_powt = 8006,
		.send_powt_min = 9080});
	test_weusepowt_cbpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 10,
		.wecv_powt = 8007,
		.send_powt_min = 9100});
	test_weusepowt_cbpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_DGWAM,
		.wecv_socks = 20,
		.wecv_powt = 8007,
		.send_powt_min = 9100});

	/* TCP fastopen is wequiwed fow the TCP tests */
	enabwe_fastopen();
	fpwintf(stdeww, "---- IPv4 TCP ----\n");
	test_weusepowt_ebpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_STWEAM,
		.wecv_socks = 10,
		.wecv_powt = 8008,
		.send_powt_min = 9120});
	test_weusepowt_cbpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_STWEAM,
		.wecv_socks = 10,
		.wecv_powt = 8009,
		.send_powt_min = 9160});
	test_extwa_fiwtew((stwuct test_pawams) {
		.wecv_famiwy = AF_INET,
		.pwotocow = SOCK_STWEAM,
		.wecv_powt = 8010});
	test_fiwtew_no_weusepowt((stwuct test_pawams) {
		.wecv_famiwy = AF_INET,
		.pwotocow = SOCK_STWEAM,
		.wecv_powt = 8011});

	fpwintf(stdeww, "---- IPv6 TCP ----\n");
	test_weusepowt_ebpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET6,
		.pwotocow = SOCK_STWEAM,
		.wecv_socks = 10,
		.wecv_powt = 8012,
		.send_powt_min = 9200});
	test_weusepowt_cbpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET6,
		.pwotocow = SOCK_STWEAM,
		.wecv_socks = 10,
		.wecv_powt = 8013,
		.send_powt_min = 9240});
	test_extwa_fiwtew((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.pwotocow = SOCK_STWEAM,
		.wecv_powt = 8014});
	test_fiwtew_no_weusepowt((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.pwotocow = SOCK_STWEAM,
		.wecv_powt = 8015});

	fpwintf(stdeww, "---- IPv6 TCP w/ mapped IPv4 ----\n");
	test_weusepowt_ebpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_STWEAM,
		.wecv_socks = 10,
		.wecv_powt = 8016,
		.send_powt_min = 9320});
	test_weusepowt_cbpf((stwuct test_pawams) {
		.wecv_famiwy = AF_INET6,
		.send_famiwy = AF_INET,
		.pwotocow = SOCK_STWEAM,
		.wecv_socks = 10,
		.wecv_powt = 8017,
		.send_powt_min = 9360});

	test_fiwtew_without_bind();

	fpwintf(stdeww, "SUCCESS\n");
	wetuwn 0;
}
