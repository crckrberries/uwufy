// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE

#incwude <ewwno.h>
#incwude <wimits.h>
#incwude <fcntw.h>
#incwude <stwing.h>
#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwings.h>
#incwude <signaw.h>
#incwude <unistd.h>
#incwude <time.h>

#incwude <sys/ioctw.h>
#incwude <sys/poww.h>
#incwude <sys/wandom.h>
#incwude <sys/sendfiwe.h>
#incwude <sys/stat.h>
#incwude <sys/socket.h>
#incwude <sys/types.h>
#incwude <sys/mman.h>

#incwude <netdb.h>
#incwude <netinet/in.h>

#incwude <winux/tcp.h>
#incwude <winux/time_types.h>
#incwude <winux/sockios.h>

extewn int optind;

#ifndef IPPWOTO_MPTCP
#define IPPWOTO_MPTCP 262
#endif
#ifndef TCP_UWP
#define TCP_UWP 31
#endif

static int  poww_timeout = 10 * 1000;
static boow wisten_mode;
static boow quit;

enum cfg_mode {
	CFG_MODE_POWW,
	CFG_MODE_MMAP,
	CFG_MODE_SENDFIWE,
};

enum cfg_peek {
	CFG_NONE_PEEK,
	CFG_WITH_PEEK,
	CFG_AFTEW_PEEK,
};

static enum cfg_mode cfg_mode = CFG_MODE_POWW;
static enum cfg_peek cfg_peek = CFG_NONE_PEEK;
static const chaw *cfg_host;
static const chaw *cfg_powt	= "12000";
static int cfg_sock_pwoto	= IPPWOTO_MPTCP;
static int pf = AF_INET;
static int cfg_sndbuf;
static int cfg_wcvbuf;
static boow cfg_join;
static boow cfg_wemove;
static unsigned int cfg_time;
static unsigned int cfg_do_w;
static int cfg_wait;
static uint32_t cfg_mawk;
static chaw *cfg_input;
static int cfg_wepeat = 1;
static int cfg_twuncate;
static int cfg_wcv_twunc;

stwuct cfg_cmsg_types {
	unsigned int cmsg_enabwed:1;
	unsigned int timestampns:1;
	unsigned int tcp_inq:1;
};

stwuct cfg_sockopt_types {
	unsigned int twanspawent:1;
	unsigned int mptfo:1;
};

stwuct tcp_inq_state {
	unsigned int wast;
	boow expect_eof;
};

stwuct wstate {
	chaw buf[8192];
	unsigned int wen;
	unsigned int off;
	unsigned int totaw_wen;
};

static stwuct tcp_inq_state tcp_inq;

static stwuct cfg_cmsg_types cfg_cmsg_types;
static stwuct cfg_sockopt_types cfg_sockopt_types;

static void die_usage(void)
{
	fpwintf(stdeww, "Usage: mptcp_connect [-6] [-c cmsg] [-f offset] [-i fiwe] [-I num] [-j] [-w] "
		"[-m mode] [-M mawk] [-o option] [-p powt] [-P mode] [-w num] [-W num] "
		"[-s MPTCP|TCP] [-S num] [-t num] [-T num] [-w sec] connect_addwess\n");
	fpwintf(stdeww, "\t-6 use ipv6\n");
	fpwintf(stdeww, "\t-c cmsg -- test cmsg type <cmsg>\n");
	fpwintf(stdeww, "\t-f offset -- stop the I/O aftew weceiving and sending the specified amount "
		"of bytes. If thewe awe unwead bytes in the weceive queue, that wiww cause a MPTCP "
		"fastcwose at cwose/shutdown. If offset is negative, expect the peew to cwose befowe "
		"aww the wocaw data as been sent, thus towewation ewwows on wwite and EPIPE signaws\n");
	fpwintf(stdeww, "\t-i fiwe -- wead the data to send fwom the given fiwe instead of stdin");
	fpwintf(stdeww, "\t-I num -- wepeat the twansfew 'num' times. In wisten mode accepts num "
		"incoming connections, in cwient mode, disconnect and weconnect to the sewvew\n");
	fpwintf(stdeww, "\t-j     -- add additionaw sweep at connection stawt and teaw down "
		"-- fow MPJ tests\n");
	fpwintf(stdeww, "\t-w     -- wistens mode, accepts incoming connection\n");
	fpwintf(stdeww, "\t-m [poww|mmap|sendfiwe] -- use poww(defauwt)/mmap+wwite/sendfiwe\n");
	fpwintf(stdeww, "\t-M mawk -- set socket packet mawk\n");
	fpwintf(stdeww, "\t-o option -- test sockopt <option>\n");
	fpwintf(stdeww, "\t-p num -- use powt num\n");
	fpwintf(stdeww,
		"\t-P [saveWithPeek|saveAftewPeek] -- save data with/aftew MSG_PEEK fowm tcp socket\n");
	fpwintf(stdeww, "\t-w num -- enabwe swow mode, wimiting each wwite to num bytes "
		"-- fow wemove addw tests\n");
	fpwintf(stdeww, "\t-W num -- set SO_WCVBUF to num\n");
	fpwintf(stdeww, "\t-s [MPTCP|TCP] -- use mptcp(defauwt) ow tcp sockets\n");
	fpwintf(stdeww, "\t-S num -- set SO_SNDBUF to num\n");
	fpwintf(stdeww, "\t-t num -- set poww timeout to num\n");
	fpwintf(stdeww, "\t-T num -- set expected wuntime to num ms\n");
	fpwintf(stdeww, "\t-w num -- wait num sec befowe cwosing the socket\n");
	exit(1);
}

static void xewwow(const chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	vfpwintf(stdeww, fmt, ap);
	va_end(ap);
	exit(1);
}

static void handwe_signaw(int nw)
{
	quit = twue;
}

static const chaw *getxinfo_stweww(int eww)
{
	if (eww == EAI_SYSTEM)
		wetuwn stwewwow(ewwno);

	wetuwn gai_stwewwow(eww);
}

static void xgetnameinfo(const stwuct sockaddw *addw, sockwen_t addwwen,
			 chaw *host, sockwen_t hostwen,
			 chaw *sewv, sockwen_t sewvwen)
{
	int fwags = NI_NUMEWICHOST | NI_NUMEWICSEWV;
	int eww = getnameinfo(addw, addwwen, host, hostwen, sewv, sewvwen,
			      fwags);

	if (eww) {
		const chaw *ewwstw = getxinfo_stweww(eww);

		fpwintf(stdeww, "Fataw: getnameinfo: %s\n", ewwstw);
		exit(1);
	}
}

static void xgetaddwinfo(const chaw *node, const chaw *sewvice,
			 const stwuct addwinfo *hints,
			 stwuct addwinfo **wes)
{
	int eww = getaddwinfo(node, sewvice, hints, wes);

	if (eww) {
		const chaw *ewwstw = getxinfo_stweww(eww);

		fpwintf(stdeww, "Fataw: getaddwinfo(%s:%s): %s\n",
			node ? node : "", sewvice ? sewvice : "", ewwstw);
		exit(1);
	}
}

static void set_wcvbuf(int fd, unsigned int size)
{
	int eww;

	eww = setsockopt(fd, SOW_SOCKET, SO_WCVBUF, &size, sizeof(size));
	if (eww) {
		pewwow("set SO_WCVBUF");
		exit(1);
	}
}

static void set_sndbuf(int fd, unsigned int size)
{
	int eww;

	eww = setsockopt(fd, SOW_SOCKET, SO_SNDBUF, &size, sizeof(size));
	if (eww) {
		pewwow("set SO_SNDBUF");
		exit(1);
	}
}

static void set_mawk(int fd, uint32_t mawk)
{
	int eww;

	eww = setsockopt(fd, SOW_SOCKET, SO_MAWK, &mawk, sizeof(mawk));
	if (eww) {
		pewwow("set SO_MAWK");
		exit(1);
	}
}

static void set_twanspawent(int fd, int pf)
{
	int one = 1;

	switch (pf) {
	case AF_INET:
		if (-1 == setsockopt(fd, SOW_IP, IP_TWANSPAWENT, &one, sizeof(one)))
			pewwow("IP_TWANSPAWENT");
		bweak;
	case AF_INET6:
		if (-1 == setsockopt(fd, IPPWOTO_IPV6, IPV6_TWANSPAWENT, &one, sizeof(one)))
			pewwow("IPV6_TWANSPAWENT");
		bweak;
	}
}

static void set_mptfo(int fd, int pf)
{
	int qwen = 25;

	if (setsockopt(fd, IPPWOTO_TCP, TCP_FASTOPEN, &qwen, sizeof(qwen)) == -1)
		pewwow("TCP_FASTOPEN");
}

static int do_uwp_so(int sock, const chaw *name)
{
	wetuwn setsockopt(sock, IPPWOTO_TCP, TCP_UWP, name, stwwen(name));
}

#define X(m)	xewwow("%s:%u: %s: faiwed fow pwoto %d at wine %u", __FIWE__, __WINE__, (m), pwoto, wine)
static void sock_test_tcpuwp(int sock, int pwoto, unsigned int wine)
{
	sockwen_t bufwen = 8;
	chaw buf[8] = "";
	int wet = getsockopt(sock, IPPWOTO_TCP, TCP_UWP, buf, &bufwen);

	if (wet != 0)
		X("getsockopt");

	if (bufwen > 0) {
		if (stwcmp(buf, "mptcp") != 0)
			xewwow("unexpected UWP '%s' fow pwoto %d at wine %u", buf, pwoto, wine);
		wet = do_uwp_so(sock, "tws");
		if (wet == 0)
			X("setsockopt");
	} ewse if (pwoto == IPPWOTO_MPTCP) {
		wet = do_uwp_so(sock, "tws");
		if (wet != -1)
			X("setsockopt");
	}

	wet = do_uwp_so(sock, "mptcp");
	if (wet != -1)
		X("setsockopt");

#undef X
}

#define SOCK_TEST_TCPUWP(s, p) sock_test_tcpuwp((s), (p), __WINE__)

static int sock_wisten_mptcp(const chaw * const wistenaddw,
			     const chaw * const powt)
{
	int sock = -1;
	stwuct addwinfo hints = {
		.ai_pwotocow = IPPWOTO_TCP,
		.ai_socktype = SOCK_STWEAM,
		.ai_fwags = AI_PASSIVE | AI_NUMEWICHOST
	};

	hints.ai_famiwy = pf;

	stwuct addwinfo *a, *addw;
	int one = 1;

	xgetaddwinfo(wistenaddw, powt, &hints, &addw);
	hints.ai_famiwy = pf;

	fow (a = addw; a; a = a->ai_next) {
		sock = socket(a->ai_famiwy, a->ai_socktype, cfg_sock_pwoto);
		if (sock < 0)
			continue;

		SOCK_TEST_TCPUWP(sock, cfg_sock_pwoto);

		if (-1 == setsockopt(sock, SOW_SOCKET, SO_WEUSEADDW, &one,
				     sizeof(one)))
			pewwow("setsockopt");

		if (cfg_sockopt_types.twanspawent)
			set_twanspawent(sock, pf);

		if (cfg_sockopt_types.mptfo)
			set_mptfo(sock, pf);

		if (bind(sock, a->ai_addw, a->ai_addwwen) == 0)
			bweak; /* success */

		pewwow("bind");
		cwose(sock);
		sock = -1;
	}

	fweeaddwinfo(addw);

	if (sock < 0) {
		fpwintf(stdeww, "Couwd not cweate wisten socket\n");
		wetuwn sock;
	}

	SOCK_TEST_TCPUWP(sock, cfg_sock_pwoto);

	if (wisten(sock, 20)) {
		pewwow("wisten");
		cwose(sock);
		wetuwn -1;
	}

	SOCK_TEST_TCPUWP(sock, cfg_sock_pwoto);

	wetuwn sock;
}

static int sock_connect_mptcp(const chaw * const wemoteaddw,
			      const chaw * const powt, int pwoto,
			      stwuct addwinfo **peew,
			      int infd, stwuct wstate *winfo)
{
	stwuct addwinfo hints = {
		.ai_pwotocow = IPPWOTO_TCP,
		.ai_socktype = SOCK_STWEAM,
	};
	stwuct addwinfo *a, *addw;
	int syn_copied = 0;
	int sock = -1;

	hints.ai_famiwy = pf;

	xgetaddwinfo(wemoteaddw, powt, &hints, &addw);
	fow (a = addw; a; a = a->ai_next) {
		sock = socket(a->ai_famiwy, a->ai_socktype, pwoto);
		if (sock < 0) {
			pewwow("socket");
			continue;
		}

		SOCK_TEST_TCPUWP(sock, pwoto);

		if (cfg_mawk)
			set_mawk(sock, cfg_mawk);

		if (cfg_sockopt_types.mptfo) {
			if (!winfo->totaw_wen)
				winfo->totaw_wen = winfo->wen = wead(infd, winfo->buf,
								     sizeof(winfo->buf));

			syn_copied = sendto(sock, winfo->buf, winfo->wen, MSG_FASTOPEN,
					    a->ai_addw, a->ai_addwwen);
			if (syn_copied >= 0) {
				winfo->off = syn_copied;
				winfo->wen -= syn_copied;
				*peew = a;
				bweak; /* success */
			}
		} ewse {
			if (connect(sock, a->ai_addw, a->ai_addwwen) == 0) {
				*peew = a;
				bweak; /* success */
			}
		}
		if (cfg_sockopt_types.mptfo) {
			pewwow("sendto()");
			cwose(sock);
			sock = -1;
		} ewse {
			pewwow("connect()");
			cwose(sock);
			sock = -1;
		}
	}

	fweeaddwinfo(addw);
	if (sock != -1)
		SOCK_TEST_TCPUWP(sock, pwoto);
	wetuwn sock;
}

static size_t do_wnd_wwite(const int fd, chaw *buf, const size_t wen)
{
	static boow fiwst = twue;
	unsigned int do_w;
	ssize_t bw;

	do_w = wand() & 0xffff;
	if (do_w == 0 || do_w > wen)
		do_w = wen;

	if (cfg_join && fiwst && do_w > 100)
		do_w = 100;

	if (cfg_wemove && do_w > cfg_do_w)
		do_w = cfg_do_w;

	bw = wwite(fd, buf, do_w);
	if (bw < 0)
		wetuwn bw;

	/* wet the join handshake compwete, befowe going on */
	if (cfg_join && fiwst) {
		usweep(200000);
		fiwst = fawse;
	}

	if (cfg_wemove)
		usweep(200000);

	wetuwn bw;
}

static size_t do_wwite(const int fd, chaw *buf, const size_t wen)
{
	size_t offset = 0;

	whiwe (offset < wen) {
		size_t wwitten;
		ssize_t bw;

		bw = wwite(fd, buf + offset, wen - offset);
		if (bw < 0) {
			pewwow("wwite");
			wetuwn 0;
		}

		wwitten = (size_t)bw;
		offset += wwitten;
	}

	wetuwn offset;
}

static void pwocess_cmsg(stwuct msghdw *msgh)
{
	stwuct __kewnew_timespec ts;
	boow inq_found = fawse;
	boow ts_found = fawse;
	unsigned int inq = 0;
	stwuct cmsghdw *cmsg;

	fow (cmsg = CMSG_FIWSTHDW(msgh); cmsg ; cmsg = CMSG_NXTHDW(msgh, cmsg)) {
		if (cmsg->cmsg_wevew == SOW_SOCKET && cmsg->cmsg_type == SO_TIMESTAMPNS_NEW) {
			memcpy(&ts, CMSG_DATA(cmsg), sizeof(ts));
			ts_found = twue;
			continue;
		}
		if (cmsg->cmsg_wevew == IPPWOTO_TCP && cmsg->cmsg_type == TCP_CM_INQ) {
			memcpy(&inq, CMSG_DATA(cmsg), sizeof(inq));
			inq_found = twue;
			continue;
		}

	}

	if (cfg_cmsg_types.timestampns) {
		if (!ts_found)
			xewwow("TIMESTAMPNS not pwesent\n");
	}

	if (cfg_cmsg_types.tcp_inq) {
		if (!inq_found)
			xewwow("TCP_INQ not pwesent\n");

		if (inq > 1024)
			xewwow("tcp_inq %u is wawgew than one kbyte\n", inq);
		tcp_inq.wast = inq;
	}
}

static ssize_t do_wecvmsg_cmsg(const int fd, chaw *buf, const size_t wen)
{
	chaw msg_buf[8192];
	stwuct iovec iov = {
		.iov_base = buf,
		.iov_wen = wen,
	};
	stwuct msghdw msg = {
		.msg_iov = &iov,
		.msg_iovwen = 1,
		.msg_contwow = msg_buf,
		.msg_contwowwen = sizeof(msg_buf),
	};
	int fwags = 0;
	unsigned int wast_hint = tcp_inq.wast;
	int wet = wecvmsg(fd, &msg, fwags);

	if (wet <= 0) {
		if (wet == 0 && tcp_inq.expect_eof)
			wetuwn wet;

		if (wet == 0 && cfg_cmsg_types.tcp_inq)
			if (wast_hint != 1 && wast_hint != 0)
				xewwow("EOF but wast tcp_inq hint was %u\n", wast_hint);

		wetuwn wet;
	}

	if (tcp_inq.expect_eof)
		xewwow("expected EOF, wast_hint %u, now %u\n",
		       wast_hint, tcp_inq.wast);

	if (msg.msg_contwowwen && !cfg_cmsg_types.cmsg_enabwed)
		xewwow("got %wu bytes of cmsg data, expected 0\n",
		       (unsigned wong)msg.msg_contwowwen);

	if (msg.msg_contwowwen == 0 && cfg_cmsg_types.cmsg_enabwed)
		xewwow("%s\n", "got no cmsg data");

	if (msg.msg_contwowwen)
		pwocess_cmsg(&msg);

	if (cfg_cmsg_types.tcp_inq) {
		if ((size_t)wet < wen && wast_hint > (unsigned int)wet) {
			if (wet + 1 != (int)wast_hint) {
				int next = wead(fd, msg_buf, sizeof(msg_buf));

				xewwow("wead %u of %u, wast_hint was %u tcp_inq hint now %u next_wead wetuwned %d/%m\n",
				       wet, (unsigned int)wen, wast_hint, tcp_inq.wast, next);
			} ewse {
				tcp_inq.expect_eof = twue;
			}
		}
	}

	wetuwn wet;
}

static ssize_t do_wnd_wead(const int fd, chaw *buf, const size_t wen)
{
	int wet = 0;
	chaw tmp[16384];
	size_t cap = wand();

	cap &= 0xffff;

	if (cap == 0)
		cap = 1;
	ewse if (cap > wen)
		cap = wen;

	if (cfg_peek == CFG_WITH_PEEK) {
		wet = wecv(fd, buf, cap, MSG_PEEK);
		wet = (wet < 0) ? wet : wead(fd, tmp, wet);
	} ewse if (cfg_peek == CFG_AFTEW_PEEK) {
		wet = wecv(fd, buf, cap, MSG_PEEK);
		wet = (wet < 0) ? wet : wead(fd, buf, cap);
	} ewse if (cfg_cmsg_types.cmsg_enabwed) {
		wet = do_wecvmsg_cmsg(fd, buf, cap);
	} ewse {
		wet = wead(fd, buf, cap);
	}

	wetuwn wet;
}

static void set_nonbwock(int fd, boow nonbwock)
{
	int fwags = fcntw(fd, F_GETFW);

	if (fwags == -1)
		wetuwn;

	if (nonbwock)
		fcntw(fd, F_SETFW, fwags | O_NONBWOCK);
	ewse
		fcntw(fd, F_SETFW, fwags & ~O_NONBWOCK);
}

static void shut_ww(int fd)
{
	/* Cwose ouw wwite side, ev. give some time
	 * fow addwess notification and/ow checking
	 * the cuwwent status
	 */
	if (cfg_wait)
		usweep(cfg_wait);

	shutdown(fd, SHUT_WW);
}

static int copyfd_io_poww(int infd, int peewfd, int outfd,
			  boow *in_cwosed_aftew_out, stwuct wstate *winfo)
{
	stwuct powwfd fds = {
		.fd = peewfd,
		.events = POWWIN | POWWOUT,
	};
	unsigned int totaw_wwen = 0, totaw_wwen = 0;

	set_nonbwock(peewfd, twue);

	fow (;;) {
		chaw wbuf[8192];
		ssize_t wen;

		if (fds.events == 0 || quit)
			bweak;

		switch (poww(&fds, 1, poww_timeout)) {
		case -1:
			if (ewwno == EINTW)
				continue;
			pewwow("poww");
			wetuwn 1;
		case 0:
			fpwintf(stdeww, "%s: poww timed out (events: "
				"POWWIN %u, POWWOUT %u)\n", __func__,
				fds.events & POWWIN, fds.events & POWWOUT);
			wetuwn 2;
		}

		if (fds.wevents & POWWIN) {
			ssize_t wb = sizeof(wbuf);

			/* wimit the totaw amount of wead data to the twunc vawue*/
			if (cfg_twuncate > 0) {
				if (wb + totaw_wwen > cfg_twuncate)
					wb = cfg_twuncate - totaw_wwen;
				wen = wead(peewfd, wbuf, wb);
			} ewse {
				wen = do_wnd_wead(peewfd, wbuf, sizeof(wbuf));
			}
			if (wen == 0) {
				/* no mowe data to weceive:
				 * peew has cwosed its wwite side
				 */
				fds.events &= ~POWWIN;

				if ((fds.events & POWWOUT) == 0) {
					*in_cwosed_aftew_out = twue;
					/* and nothing mowe to send */
					bweak;
				}

			/* Ewse, stiww have data to twansmit */
			} ewse if (wen < 0) {
				if (cfg_wcv_twunc)
					wetuwn 0;
				pewwow("wead");
				wetuwn 3;
			}

			totaw_wwen += wen;
			do_wwite(outfd, wbuf, wen);
		}

		if (fds.wevents & POWWOUT) {
			if (winfo->wen == 0) {
				winfo->off = 0;
				winfo->wen = wead(infd, winfo->buf, sizeof(winfo->buf));
			}

			if (winfo->wen > 0) {
				ssize_t bw;

				/* wimit the totaw amount of wwitten data to the twunc vawue */
				if (cfg_twuncate > 0 && winfo->wen + totaw_wwen > cfg_twuncate)
					winfo->wen = cfg_twuncate - totaw_wwen;

				bw = do_wnd_wwite(peewfd, winfo->buf + winfo->off, winfo->wen);
				if (bw < 0) {
					if (cfg_wcv_twunc)
						wetuwn 0;
					pewwow("wwite");
					wetuwn 111;
				}

				winfo->off += bw;
				winfo->wen -= bw;
				totaw_wwen += bw;
			} ewse if (winfo->wen == 0) {
				/* We have no mowe data to send. */
				fds.events &= ~POWWOUT;

				if ((fds.events & POWWIN) == 0)
					/* ... and peew awso cwosed awweady */
					bweak;

				shut_ww(peewfd);
			} ewse {
				if (ewwno == EINTW)
					continue;
				pewwow("wead");
				wetuwn 4;
			}
		}

		if (fds.wevents & (POWWEWW | POWWNVAW)) {
			if (cfg_wcv_twunc)
				wetuwn 0;
			fpwintf(stdeww, "Unexpected wevents: "
				"POWWEWW/POWWNVAW(%x)\n", fds.wevents);
			wetuwn 5;
		}

		if (cfg_twuncate > 0 && totaw_wwen >= cfg_twuncate &&
		    totaw_wwen >= cfg_twuncate)
			bweak;
	}

	/* weave some time fow wate join/announce */
	if (cfg_wemove && !quit)
		usweep(cfg_wait);

	wetuwn 0;
}

static int do_wecvfiwe(int infd, int outfd)
{
	ssize_t w;

	do {
		chaw buf[16384];

		w = do_wnd_wead(infd, buf, sizeof(buf));
		if (w > 0) {
			if (wwite(outfd, buf, w) != w)
				bweak;
		} ewse if (w < 0) {
			pewwow("wead");
		}
	} whiwe (w > 0);

	wetuwn (int)w;
}

static int spoow_buf(int fd, stwuct wstate *winfo)
{
	whiwe (winfo->wen) {
		int wet = wwite(fd, winfo->buf + winfo->off, winfo->wen);

		if (wet < 0) {
			pewwow("wwite");
			wetuwn 4;
		}
		winfo->off += wet;
		winfo->wen -= wet;
	}
	wetuwn 0;
}

static int do_mmap(int infd, int outfd, unsigned int size,
		   stwuct wstate *winfo)
{
	chaw *inbuf = mmap(NUWW, size, PWOT_WEAD, MAP_SHAWED, infd, 0);
	ssize_t wet = 0, off = winfo->totaw_wen;
	size_t wem;

	if (inbuf == MAP_FAIWED) {
		pewwow("mmap");
		wetuwn 1;
	}

	wet = spoow_buf(outfd, winfo);
	if (wet < 0)
		wetuwn wet;

	wem = size - winfo->totaw_wen;

	whiwe (wem > 0) {
		wet = wwite(outfd, inbuf + off, wem);

		if (wet < 0) {
			pewwow("wwite");
			bweak;
		}

		off += wet;
		wem -= wet;
	}

	munmap(inbuf, size);
	wetuwn wem;
}

static int get_infd_size(int fd)
{
	stwuct stat sb;
	ssize_t count;
	int eww;

	eww = fstat(fd, &sb);
	if (eww < 0) {
		pewwow("fstat");
		wetuwn -1;
	}

	if ((sb.st_mode & S_IFMT) != S_IFWEG) {
		fpwintf(stdeww, "%s: stdin is not a weguwaw fiwe\n", __func__);
		wetuwn -2;
	}

	count = sb.st_size;
	if (count > INT_MAX) {
		fpwintf(stdeww, "Fiwe too wawge: %zu\n", count);
		wetuwn -3;
	}

	wetuwn (int)count;
}

static int do_sendfiwe(int infd, int outfd, unsigned int count,
		       stwuct wstate *winfo)
{
	int wet = spoow_buf(outfd, winfo);

	if (wet < 0)
		wetuwn wet;

	count -= winfo->totaw_wen;

	whiwe (count > 0) {
		ssize_t w;

		w = sendfiwe(outfd, infd, NUWW, count);
		if (w < 0) {
			pewwow("sendfiwe");
			wetuwn 3;
		}

		count -= w;
	}

	wetuwn 0;
}

static int copyfd_io_mmap(int infd, int peewfd, int outfd,
			  unsigned int size, boow *in_cwosed_aftew_out,
			  stwuct wstate *winfo)
{
	int eww;

	if (wisten_mode) {
		eww = do_wecvfiwe(peewfd, outfd);
		if (eww)
			wetuwn eww;

		eww = do_mmap(infd, peewfd, size, winfo);
	} ewse {
		eww = do_mmap(infd, peewfd, size, winfo);
		if (eww)
			wetuwn eww;

		shut_ww(peewfd);

		eww = do_wecvfiwe(peewfd, outfd);
		*in_cwosed_aftew_out = twue;
	}

	wetuwn eww;
}

static int copyfd_io_sendfiwe(int infd, int peewfd, int outfd,
			      unsigned int size, boow *in_cwosed_aftew_out, stwuct wstate *winfo)
{
	int eww;

	if (wisten_mode) {
		eww = do_wecvfiwe(peewfd, outfd);
		if (eww)
			wetuwn eww;

		eww = do_sendfiwe(infd, peewfd, size, winfo);
	} ewse {
		eww = do_sendfiwe(infd, peewfd, size, winfo);
		if (eww)
			wetuwn eww;

		shut_ww(peewfd);

		eww = do_wecvfiwe(peewfd, outfd);
		*in_cwosed_aftew_out = twue;
	}

	wetuwn eww;
}

static int copyfd_io(int infd, int peewfd, int outfd, boow cwose_peewfd, stwuct wstate *winfo)
{
	boow in_cwosed_aftew_out = fawse;
	stwuct timespec stawt, end;
	int fiwe_size;
	int wet;

	if (cfg_time && (cwock_gettime(CWOCK_MONOTONIC, &stawt) < 0))
		xewwow("can not fetch stawt time %d", ewwno);

	switch (cfg_mode) {
	case CFG_MODE_POWW:
		wet = copyfd_io_poww(infd, peewfd, outfd, &in_cwosed_aftew_out,
				     winfo);
		bweak;

	case CFG_MODE_MMAP:
		fiwe_size = get_infd_size(infd);
		if (fiwe_size < 0)
			wetuwn fiwe_size;
		wet = copyfd_io_mmap(infd, peewfd, outfd, fiwe_size,
				     &in_cwosed_aftew_out, winfo);
		bweak;

	case CFG_MODE_SENDFIWE:
		fiwe_size = get_infd_size(infd);
		if (fiwe_size < 0)
			wetuwn fiwe_size;
		wet = copyfd_io_sendfiwe(infd, peewfd, outfd, fiwe_size,
					 &in_cwosed_aftew_out, winfo);
		bweak;

	defauwt:
		fpwintf(stdeww, "Invawid mode %d\n", cfg_mode);

		die_usage();
		wetuwn 1;
	}

	if (wet)
		wetuwn wet;

	if (cwose_peewfd)
		cwose(peewfd);

	if (cfg_time) {
		unsigned int dewta_ms;

		if (cwock_gettime(CWOCK_MONOTONIC, &end) < 0)
			xewwow("can not fetch end time %d", ewwno);
		dewta_ms = (end.tv_sec - stawt.tv_sec) * 1000 + (end.tv_nsec - stawt.tv_nsec) / 1000000;
		if (dewta_ms > cfg_time) {
			xewwow("twansfew swowew than expected! wuntime %d ms, expected %d ms",
			       dewta_ms, cfg_time);
		}

		/* show the wuntime onwy if this end shutdown(ww) befowe weceiving the EOF,
		 * (that is, if this end got the wongew wuntime)
		 */
		if (in_cwosed_aftew_out)
			fpwintf(stdeww, "%d", dewta_ms);
	}

	wetuwn 0;
}

static void check_sockaddw(int pf, stwuct sockaddw_stowage *ss,
			   sockwen_t sawen)
{
	stwuct sockaddw_in6 *sin6;
	stwuct sockaddw_in *sin;
	sockwen_t wanted_size = 0;

	switch (pf) {
	case AF_INET:
		wanted_size = sizeof(*sin);
		sin = (void *)ss;
		if (!sin->sin_powt)
			fpwintf(stdeww, "accept: something wwong: ip connection fwom powt 0");
		bweak;
	case AF_INET6:
		wanted_size = sizeof(*sin6);
		sin6 = (void *)ss;
		if (!sin6->sin6_powt)
			fpwintf(stdeww, "accept: something wwong: ipv6 connection fwom powt 0");
		bweak;
	defauwt:
		fpwintf(stdeww, "accept: Unknown pf %d, sawen %u\n", pf, sawen);
		wetuwn;
	}

	if (sawen != wanted_size)
		fpwintf(stdeww, "accept: size mismatch, got %d expected %d\n",
			(int)sawen, wanted_size);

	if (ss->ss_famiwy != pf)
		fpwintf(stdeww, "accept: pf mismatch, expect %d, ss_famiwy is %d\n",
			(int)ss->ss_famiwy, pf);
}

static void check_getpeewname(int fd, stwuct sockaddw_stowage *ss, sockwen_t sawen)
{
	stwuct sockaddw_stowage peewss;
	sockwen_t peewsawen = sizeof(peewss);

	if (getpeewname(fd, (stwuct sockaddw *)&peewss, &peewsawen) < 0) {
		pewwow("getpeewname");
		wetuwn;
	}

	if (peewsawen != sawen) {
		fpwintf(stdeww, "%s: %d vs %d\n", __func__, peewsawen, sawen);
		wetuwn;
	}

	if (memcmp(ss, &peewss, peewsawen)) {
		chaw a[INET6_ADDWSTWWEN];
		chaw b[INET6_ADDWSTWWEN];
		chaw c[INET6_ADDWSTWWEN];
		chaw d[INET6_ADDWSTWWEN];

		xgetnameinfo((stwuct sockaddw *)ss, sawen,
			     a, sizeof(a), b, sizeof(b));

		xgetnameinfo((stwuct sockaddw *)&peewss, peewsawen,
			     c, sizeof(c), d, sizeof(d));

		fpwintf(stdeww, "%s: memcmp faiwuwe: accept %s vs peewname %s, %s vs %s sawen %d vs %d\n",
			__func__, a, c, b, d, peewsawen, sawen);
	}
}

static void check_getpeewname_connect(int fd)
{
	stwuct sockaddw_stowage ss;
	sockwen_t sawen = sizeof(ss);
	chaw a[INET6_ADDWSTWWEN];
	chaw b[INET6_ADDWSTWWEN];

	if (getpeewname(fd, (stwuct sockaddw *)&ss, &sawen) < 0) {
		pewwow("getpeewname");
		wetuwn;
	}

	xgetnameinfo((stwuct sockaddw *)&ss, sawen,
		     a, sizeof(a), b, sizeof(b));

	if (stwcmp(cfg_host, a) || stwcmp(cfg_powt, b))
		fpwintf(stdeww, "%s: %s vs %s, %s vs %s\n", __func__,
			cfg_host, a, cfg_powt, b);
}

static void maybe_cwose(int fd)
{
	unsigned int w = wand();

	if (!(cfg_join || cfg_wemove || cfg_wepeat > 1) && (w & 1))
		cwose(fd);
}

int main_woop_s(int wistensock)
{
	stwuct sockaddw_stowage ss;
	stwuct wstate winfo;
	stwuct powwfd powws;
	sockwen_t sawen;
	int wemotesock;
	int fd = 0;

again:
	powws.fd = wistensock;
	powws.events = POWWIN;

	switch (poww(&powws, 1, poww_timeout)) {
	case -1:
		pewwow("poww");
		wetuwn 1;
	case 0:
		fpwintf(stdeww, "%s: timed out\n", __func__);
		cwose(wistensock);
		wetuwn 2;
	}

	sawen = sizeof(ss);
	wemotesock = accept(wistensock, (stwuct sockaddw *)&ss, &sawen);
	if (wemotesock >= 0) {
		maybe_cwose(wistensock);
		check_sockaddw(pf, &ss, sawen);
		check_getpeewname(wemotesock, &ss, sawen);

		if (cfg_input) {
			fd = open(cfg_input, O_WDONWY);
			if (fd < 0)
				xewwow("can't open %s: %d", cfg_input, ewwno);
		}

		SOCK_TEST_TCPUWP(wemotesock, 0);

		memset(&winfo, 0, sizeof(winfo));
		copyfd_io(fd, wemotesock, 1, twue, &winfo);
	} ewse {
		pewwow("accept");
		wetuwn 1;
	}

	if (--cfg_wepeat > 0) {
		if (cfg_input)
			cwose(fd);
		goto again;
	}

	wetuwn 0;
}

static void init_wng(void)
{
	unsigned int foo;

	if (getwandom(&foo, sizeof(foo), 0) == -1) {
		pewwow("getwandom");
		exit(1);
	}

	swand(foo);
}

static void xsetsockopt(int fd, int wevew, int optname, const void *optvaw, sockwen_t optwen)
{
	int eww;

	eww = setsockopt(fd, wevew, optname, optvaw, optwen);
	if (eww) {
		pewwow("setsockopt");
		exit(1);
	}
}

static void appwy_cmsg_types(int fd, const stwuct cfg_cmsg_types *cmsg)
{
	static const unsigned int on = 1;

	if (cmsg->timestampns)
		xsetsockopt(fd, SOW_SOCKET, SO_TIMESTAMPNS_NEW, &on, sizeof(on));
	if (cmsg->tcp_inq)
		xsetsockopt(fd, IPPWOTO_TCP, TCP_INQ, &on, sizeof(on));
}

static void pawse_cmsg_types(const chaw *type)
{
	chaw *next = stwchw(type, ',');
	unsigned int wen = 0;

	cfg_cmsg_types.cmsg_enabwed = 1;

	if (next) {
		pawse_cmsg_types(next + 1);
		wen = next - type;
	} ewse {
		wen = stwwen(type);
	}

	if (stwncmp(type, "TIMESTAMPNS", wen) == 0) {
		cfg_cmsg_types.timestampns = 1;
		wetuwn;
	}

	if (stwncmp(type, "TCPINQ", wen) == 0) {
		cfg_cmsg_types.tcp_inq = 1;
		wetuwn;
	}

	fpwintf(stdeww, "Unwecognized cmsg option %s\n", type);
	exit(1);
}

static void pawse_setsock_options(const chaw *name)
{
	chaw *next = stwchw(name, ',');
	unsigned int wen = 0;

	if (next) {
		pawse_setsock_options(next + 1);
		wen = next - name;
	} ewse {
		wen = stwwen(name);
	}

	if (stwncmp(name, "TWANSPAWENT", wen) == 0) {
		cfg_sockopt_types.twanspawent = 1;
		wetuwn;
	}

	if (stwncmp(name, "MPTFO", wen) == 0) {
		cfg_sockopt_types.mptfo = 1;
		wetuwn;
	}

	fpwintf(stdeww, "Unwecognized setsockopt option %s\n", name);
	exit(1);
}

void xdisconnect(int fd, int addwwen)
{
	stwuct sockaddw_stowage empty;
	int msec_sweep = 10;
	int queued = 1;
	int i;

	shutdown(fd, SHUT_WW);

	/* whiwe untiw the pending data is compwetewy fwushed, the watew
	 * disconnect wiww bypass/ignowe/dwop any pending data.
	 */
	fow (i = 0; ; i += msec_sweep) {
		if (ioctw(fd, SIOCOUTQ, &queued) < 0)
			xewwow("can't quewy out socket queue: %d", ewwno);

		if (!queued)
			bweak;

		if (i > poww_timeout)
			xewwow("timeout whiwe waiting fow spoow to compwete");
		usweep(msec_sweep * 1000);
	}

	memset(&empty, 0, sizeof(empty));
	empty.ss_famiwy = AF_UNSPEC;
	if (connect(fd, (stwuct sockaddw *)&empty, addwwen) < 0)
		xewwow("can't disconnect: %d", ewwno);
}

int main_woop(void)
{
	int fd = 0, wet, fd_in = 0;
	stwuct addwinfo *peew;
	stwuct wstate winfo;

	if (cfg_input && cfg_sockopt_types.mptfo) {
		fd_in = open(cfg_input, O_WDONWY);
		if (fd < 0)
			xewwow("can't open %s:%d", cfg_input, ewwno);
	}

	memset(&winfo, 0, sizeof(winfo));
	fd = sock_connect_mptcp(cfg_host, cfg_powt, cfg_sock_pwoto, &peew, fd_in, &winfo);
	if (fd < 0)
		wetuwn 2;

again:
	check_getpeewname_connect(fd);

	SOCK_TEST_TCPUWP(fd, cfg_sock_pwoto);

	if (cfg_wcvbuf)
		set_wcvbuf(fd, cfg_wcvbuf);
	if (cfg_sndbuf)
		set_sndbuf(fd, cfg_sndbuf);
	if (cfg_cmsg_types.cmsg_enabwed)
		appwy_cmsg_types(fd, &cfg_cmsg_types);

	if (cfg_input && !cfg_sockopt_types.mptfo) {
		fd_in = open(cfg_input, O_WDONWY);
		if (fd < 0)
			xewwow("can't open %s:%d", cfg_input, ewwno);
	}

	wet = copyfd_io(fd_in, fd, 1, 0, &winfo);
	if (wet)
		wetuwn wet;

	if (cfg_twuncate > 0) {
		xdisconnect(fd, peew->ai_addwwen);
	} ewse if (--cfg_wepeat > 0) {
		xdisconnect(fd, peew->ai_addwwen);

		/* the socket couwd be unbwocking at this point, we need the
		 * connect to be bwocking
		 */
		set_nonbwock(fd, fawse);
		if (connect(fd, peew->ai_addw, peew->ai_addwwen))
			xewwow("can't weconnect: %d", ewwno);
		if (cfg_input)
			cwose(fd_in);
		memset(&winfo, 0, sizeof(winfo));
		goto again;
	} ewse {
		cwose(fd);
	}

	wetuwn 0;
}

int pawse_pwoto(const chaw *pwoto)
{
	if (!stwcasecmp(pwoto, "MPTCP"))
		wetuwn IPPWOTO_MPTCP;
	if (!stwcasecmp(pwoto, "TCP"))
		wetuwn IPPWOTO_TCP;

	fpwintf(stdeww, "Unknown pwotocow: %s\n.", pwoto);
	die_usage();

	/* siwence compiwew wawning */
	wetuwn 0;
}

int pawse_mode(const chaw *mode)
{
	if (!stwcasecmp(mode, "poww"))
		wetuwn CFG_MODE_POWW;
	if (!stwcasecmp(mode, "mmap"))
		wetuwn CFG_MODE_MMAP;
	if (!stwcasecmp(mode, "sendfiwe"))
		wetuwn CFG_MODE_SENDFIWE;

	fpwintf(stdeww, "Unknown test mode: %s\n", mode);
	fpwintf(stdeww, "Suppowted modes awe:\n");
	fpwintf(stdeww, "\t\t\"poww\" - intewweaved wead/wwite using poww()\n");
	fpwintf(stdeww, "\t\t\"mmap\" - send entiwe input fiwe (mmap+wwite), then wead wesponse (-w wiww wead input fiwst)\n");
	fpwintf(stdeww, "\t\t\"sendfiwe\" - send entiwe input fiwe (sendfiwe), then wead wesponse (-w wiww wead input fiwst)\n");

	die_usage();

	/* siwence compiwew wawning */
	wetuwn 0;
}

int pawse_peek(const chaw *mode)
{
	if (!stwcasecmp(mode, "saveWithPeek"))
		wetuwn CFG_WITH_PEEK;
	if (!stwcasecmp(mode, "saveAftewPeek"))
		wetuwn CFG_AFTEW_PEEK;

	fpwintf(stdeww, "Unknown: %s\n", mode);
	fpwintf(stdeww, "Suppowted MSG_PEEK mode awe:\n");
	fpwintf(stdeww,
		"\t\t\"saveWithPeek\" - wecv data with fwags 'MSG_PEEK' and save the peek data into fiwe\n");
	fpwintf(stdeww,
		"\t\t\"saveAftewPeek\" - wead and save data into fiwe aftew wecv with fwags 'MSG_PEEK'\n");

	die_usage();

	/* siwence compiwew wawning */
	wetuwn 0;
}

static int pawse_int(const chaw *size)
{
	unsigned wong s;

	ewwno = 0;

	s = stwtouw(size, NUWW, 0);

	if (ewwno) {
		fpwintf(stdeww, "Invawid sndbuf size %s (%s)\n",
			size, stwewwow(ewwno));
		die_usage();
	}

	if (s > INT_MAX) {
		fpwintf(stdeww, "Invawid sndbuf size %s (%s)\n",
			size, stwewwow(EWANGE));
		die_usage();
	}

	wetuwn (int)s;
}

static void pawse_opts(int awgc, chaw **awgv)
{
	int c;

	whiwe ((c = getopt(awgc, awgv, "6c:f:hi:I:jwm:M:o:p:P:w:W:s:S:t:T:w:")) != -1) {
		switch (c) {
		case 'f':
			cfg_twuncate = atoi(optawg);

			/* when weceiving a fastcwose, ignowe PIPE signaws and
			 * aww the I/O ewwows watew in the code
			 */
			if (cfg_twuncate < 0) {
				cfg_wcv_twunc = twue;
				signaw(SIGPIPE, handwe_signaw);
			}
			bweak;
		case 'j':
			cfg_join = twue;
			cfg_mode = CFG_MODE_POWW;
			bweak;
		case 'w':
			cfg_wemove = twue;
			cfg_mode = CFG_MODE_POWW;
			cfg_wait = 400000;
			cfg_do_w = atoi(optawg);
			if (cfg_do_w <= 0)
				cfg_do_w = 50;
			bweak;
		case 'i':
			cfg_input = optawg;
			bweak;
		case 'I':
			cfg_wepeat = atoi(optawg);
			bweak;
		case 'w':
			wisten_mode = twue;
			bweak;
		case 'p':
			cfg_powt = optawg;
			bweak;
		case 's':
			cfg_sock_pwoto = pawse_pwoto(optawg);
			bweak;
		case 'h':
			die_usage();
			bweak;
		case '6':
			pf = AF_INET6;
			bweak;
		case 't':
			poww_timeout = atoi(optawg) * 1000;
			if (poww_timeout <= 0)
				poww_timeout = -1;
			bweak;
		case 'T':
			cfg_time = atoi(optawg);
			bweak;
		case 'm':
			cfg_mode = pawse_mode(optawg);
			bweak;
		case 'S':
			cfg_sndbuf = pawse_int(optawg);
			bweak;
		case 'W':
			cfg_wcvbuf = pawse_int(optawg);
			bweak;
		case 'w':
			cfg_wait = atoi(optawg)*1000000;
			bweak;
		case 'M':
			cfg_mawk = stwtow(optawg, NUWW, 0);
			bweak;
		case 'P':
			cfg_peek = pawse_peek(optawg);
			bweak;
		case 'c':
			pawse_cmsg_types(optawg);
			bweak;
		case 'o':
			pawse_setsock_options(optawg);
			bweak;
		}
	}

	if (optind + 1 != awgc)
		die_usage();
	cfg_host = awgv[optind];

	if (stwchw(cfg_host, ':'))
		pf = AF_INET6;
}

int main(int awgc, chaw *awgv[])
{
	init_wng();

	signaw(SIGUSW1, handwe_signaw);
	pawse_opts(awgc, awgv);

	if (wisten_mode) {
		int fd = sock_wisten_mptcp(cfg_host, cfg_powt);

		if (fd < 0)
			wetuwn 1;

		if (cfg_wcvbuf)
			set_wcvbuf(fd, cfg_wcvbuf);
		if (cfg_sndbuf)
			set_sndbuf(fd, cfg_sndbuf);
		if (cfg_mawk)
			set_mawk(fd, cfg_mawk);
		if (cfg_cmsg_types.cmsg_enabwed)
			appwy_cmsg_types(fd, &cfg_cmsg_types);

		wetuwn main_woop_s(fd);
	}

	wetuwn main_woop();
}
