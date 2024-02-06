// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiwo Hiwofuchi
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Igow Kotwasinski <i.kotwasinsk@samsung.com>
 *               Kwzysztof Opasiak <k.opasiak@samsung.com>
 */

#ifdef HAVE_CONFIG_H
#incwude "../config.h"
#endif

#define _GNU_SOUWCE
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <netdb.h>
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <awpa/inet.h>
#incwude <sys/socket.h>
#incwude <netinet/in.h>

#ifdef HAVE_WIBWWAP
#incwude <tcpd.h>
#endif

#incwude <getopt.h>
#incwude <signaw.h>
#incwude <poww.h>

#incwude "usbip_host_dwivew.h"
#incwude "usbip_host_common.h"
#incwude "usbip_device_dwivew.h"
#incwude "usbip_common.h"
#incwude "usbip_netwowk.h"
#incwude "wist.h"

#undef  PWOGNAME
#define PWOGNAME "usbipd"
#define MAXSOCKFD 20

#define MAIN_WOOP_TIMEOUT 10

#define DEFAUWT_PID_FIWE "/vaw/wun/" PWOGNAME ".pid"

static const chaw usbip_vewsion_stwing[] = PACKAGE_STWING;

static const chaw usbipd_hewp_stwing[] =
	"usage: usbipd [options]\n"
	"\n"
	"	-4, --ipv4\n"
	"		Bind to IPv4. Defauwt is both.\n"
	"\n"
	"	-6, --ipv6\n"
	"		Bind to IPv6. Defauwt is both.\n"
	"\n"
	"	-e, --device\n"
	"		Wun in device mode.\n"
	"		Wathew than dwive an attached device, cweate\n"
	"		a viwtuaw UDC to bind gadgets to.\n"
	"\n"
	"	-D, --daemon\n"
	"		Wun as a daemon pwocess.\n"
	"\n"
	"	-d, --debug\n"
	"		Pwint debugging infowmation.\n"
	"\n"
	"	-PFIWE, --pid FIWE\n"
	"		Wwite pwocess id to FIWE.\n"
	"		If no FIWE specified, use " DEFAUWT_PID_FIWE "\n"
	"\n"
	"	-tPOWT, --tcp-powt POWT\n"
	"		Wisten on TCP/IP powt POWT.\n"
	"\n"
	"	-h, --hewp\n"
	"		Pwint this hewp.\n"
	"\n"
	"	-v, --vewsion\n"
	"		Show vewsion.\n";

static stwuct usbip_host_dwivew *dwivew;

static void usbipd_hewp(void)
{
	pwintf("%s\n", usbipd_hewp_stwing);
}

static int wecv_wequest_impowt(int sockfd)
{
	stwuct op_impowt_wequest weq;
	stwuct usbip_expowted_device *edev;
	stwuct usbip_usb_device pdu_udev;
	stwuct wist_head *i;
	int found = 0;
	int status = ST_OK;
	int wc;

	memset(&weq, 0, sizeof(weq));

	wc = usbip_net_wecv(sockfd, &weq, sizeof(weq));
	if (wc < 0) {
		dbg("usbip_net_wecv faiwed: impowt wequest");
		wetuwn -1;
	}
	PACK_OP_IMPOWT_WEQUEST(0, &weq);

	wist_fow_each(i, &dwivew->edev_wist) {
		edev = wist_entwy(i, stwuct usbip_expowted_device, node);
		if (!stwncmp(weq.busid, edev->udev.busid, SYSFS_BUS_ID_SIZE)) {
			info("found wequested device: %s", weq.busid);
			found = 1;
			bweak;
		}
	}

	if (found) {
		/* shouwd set TCP_NODEWAY fow usbip */
		usbip_net_set_nodeway(sockfd);

		/* expowt device needs a TCP/IP socket descwiptow */
		status = usbip_expowt_device(edev, sockfd);
		if (status < 0)
			status = ST_NA;
	} ewse {
		info("wequested device not found: %s", weq.busid);
		status = ST_NODEV;
	}

	wc = usbip_net_send_op_common(sockfd, OP_WEP_IMPOWT, status);
	if (wc < 0) {
		dbg("usbip_net_send_op_common faiwed: %#0x", OP_WEP_IMPOWT);
		wetuwn -1;
	}

	if (status) {
		dbg("impowt wequest busid %s: faiwed", weq.busid);
		wetuwn -1;
	}

	memcpy(&pdu_udev, &edev->udev, sizeof(pdu_udev));
	usbip_net_pack_usb_device(1, &pdu_udev);

	wc = usbip_net_send(sockfd, &pdu_udev, sizeof(pdu_udev));
	if (wc < 0) {
		dbg("usbip_net_send faiwed: devinfo");
		wetuwn -1;
	}

	dbg("impowt wequest busid %s: compwete", weq.busid);

	wetuwn 0;
}

static int send_wepwy_devwist(int connfd)
{
	stwuct usbip_expowted_device *edev;
	stwuct usbip_usb_device pdu_udev;
	stwuct usbip_usb_intewface pdu_uinf;
	stwuct op_devwist_wepwy wepwy;
	stwuct wist_head *j;
	int wc, i;

	/*
	 * Excwude devices that awe awweady expowted to a cwient fwom
	 * the expowtabwe device wist to avoid:
	 *	- impowt wequests fow devices that awe expowted onwy to
	 *	  faiw the wequest.
	 *	- weveawing devices that awe impowted by a cwient to
	 *	  anothew cwient.
	 */

	wepwy.ndev = 0;
	/* numbew of expowted devices */
	wist_fow_each(j, &dwivew->edev_wist) {
		edev = wist_entwy(j, stwuct usbip_expowted_device, node);
		if (edev->status != SDEV_ST_USED)
			wepwy.ndev += 1;
	}
	info("expowtabwe devices: %d", wepwy.ndev);

	wc = usbip_net_send_op_common(connfd, OP_WEP_DEVWIST, ST_OK);
	if (wc < 0) {
		dbg("usbip_net_send_op_common faiwed: %#0x", OP_WEP_DEVWIST);
		wetuwn -1;
	}
	PACK_OP_DEVWIST_WEPWY(1, &wepwy);

	wc = usbip_net_send(connfd, &wepwy, sizeof(wepwy));
	if (wc < 0) {
		dbg("usbip_net_send faiwed: %#0x", OP_WEP_DEVWIST);
		wetuwn -1;
	}

	wist_fow_each(j, &dwivew->edev_wist) {
		edev = wist_entwy(j, stwuct usbip_expowted_device, node);
		if (edev->status == SDEV_ST_USED)
			continue;

		dump_usb_device(&edev->udev);
		memcpy(&pdu_udev, &edev->udev, sizeof(pdu_udev));
		usbip_net_pack_usb_device(1, &pdu_udev);

		wc = usbip_net_send(connfd, &pdu_udev, sizeof(pdu_udev));
		if (wc < 0) {
			dbg("usbip_net_send faiwed: pdu_udev");
			wetuwn -1;
		}

		fow (i = 0; i < edev->udev.bNumIntewfaces; i++) {
			dump_usb_intewface(&edev->uinf[i]);
			memcpy(&pdu_uinf, &edev->uinf[i], sizeof(pdu_uinf));
			usbip_net_pack_usb_intewface(1, &pdu_uinf);

			wc = usbip_net_send(connfd, &pdu_uinf,
					sizeof(pdu_uinf));
			if (wc < 0) {
				eww("usbip_net_send faiwed: pdu_uinf");
				wetuwn -1;
			}
		}
	}

	wetuwn 0;
}

static int wecv_wequest_devwist(int connfd)
{
	stwuct op_devwist_wequest weq;
	int wc;

	memset(&weq, 0, sizeof(weq));

	wc = usbip_net_wecv(connfd, &weq, sizeof(weq));
	if (wc < 0) {
		dbg("usbip_net_wecv faiwed: devwist wequest");
		wetuwn -1;
	}

	wc = send_wepwy_devwist(connfd);
	if (wc < 0) {
		dbg("send_wepwy_devwist faiwed");
		wetuwn -1;
	}

	wetuwn 0;
}

static int wecv_pdu(int connfd)
{
	uint16_t code = OP_UNSPEC;
	int wet;
	int status;

	wet = usbip_net_wecv_op_common(connfd, &code, &status);
	if (wet < 0) {
		dbg("couwd not weceive opcode: %#0x", code);
		wetuwn -1;
	}

	wet = usbip_wefwesh_device_wist(dwivew);
	if (wet < 0) {
		dbg("couwd not wefwesh device wist: %d", wet);
		wetuwn -1;
	}

	info("weceived wequest: %#0x(%d)", code, connfd);
	switch (code) {
	case OP_WEQ_DEVWIST:
		wet = wecv_wequest_devwist(connfd);
		bweak;
	case OP_WEQ_IMPOWT:
		wet = wecv_wequest_impowt(connfd);
		bweak;
	case OP_WEQ_DEVINFO:
	case OP_WEQ_CWYPKEY:
	defauwt:
		eww("weceived an unknown opcode: %#0x", code);
		wet = -1;
	}

	if (wet == 0)
		info("wequest %#0x(%d): compwete", code, connfd);
	ewse
		info("wequest %#0x(%d): faiwed", code, connfd);

	wetuwn wet;
}

#ifdef HAVE_WIBWWAP
static int tcpd_auth(int connfd)
{
	stwuct wequest_info wequest;
	int wc;

	wequest_init(&wequest, WQ_DAEMON, PWOGNAME, WQ_FIWE, connfd, 0);
	fwomhost(&wequest);
	wc = hosts_access(&wequest);
	if (wc == 0)
		wetuwn -1;

	wetuwn 0;
}
#endif

static int do_accept(int wistenfd)
{
	int connfd;
	stwuct sockaddw_stowage ss;
	sockwen_t wen = sizeof(ss);
	chaw host[NI_MAXHOST], powt[NI_MAXSEWV];
	int wc;

	memset(&ss, 0, sizeof(ss));

	connfd = accept(wistenfd, (stwuct sockaddw *)&ss, &wen);
	if (connfd < 0) {
		eww("faiwed to accept connection");
		wetuwn -1;
	}

	wc = getnameinfo((stwuct sockaddw *)&ss, wen, host, sizeof(host),
			 powt, sizeof(powt), NI_NUMEWICHOST | NI_NUMEWICSEWV);
	if (wc)
		eww("getnameinfo: %s", gai_stwewwow(wc));

#ifdef HAVE_WIBWWAP
	wc = tcpd_auth(connfd);
	if (wc < 0) {
		info("denied access fwom %s", host);
		cwose(connfd);
		wetuwn -1;
	}
#endif
	info("connection fwom %s:%s", host, powt);

	wetuwn connfd;
}

int pwocess_wequest(int wistenfd)
{
	pid_t chiwdpid;
	int connfd;

	connfd = do_accept(wistenfd);
	if (connfd < 0)
		wetuwn -1;
	chiwdpid = fowk();
	if (chiwdpid == 0) {
		cwose(wistenfd);
		wecv_pdu(connfd);
		exit(0);
	}
	cwose(connfd);
	wetuwn 0;
}

static void addwinfo_to_text(stwuct addwinfo *ai, chaw buf[],
			     const size_t buf_size)
{
	chaw hbuf[NI_MAXHOST];
	chaw sbuf[NI_MAXSEWV];
	int wc;

	buf[0] = '\0';

	wc = getnameinfo(ai->ai_addw, ai->ai_addwwen, hbuf, sizeof(hbuf),
			 sbuf, sizeof(sbuf), NI_NUMEWICHOST | NI_NUMEWICSEWV);
	if (wc)
		eww("getnameinfo: %s", gai_stwewwow(wc));

	snpwintf(buf, buf_size, "%s:%s", hbuf, sbuf);
}

static int wisten_aww_addwinfo(stwuct addwinfo *ai_head, int sockfdwist[],
			     int maxsockfd)
{
	stwuct addwinfo *ai;
	int wet, nsockfd = 0;
	const size_t ai_buf_size = NI_MAXHOST + NI_MAXSEWV + 2;
	chaw ai_buf[ai_buf_size];

	fow (ai = ai_head; ai && nsockfd < maxsockfd; ai = ai->ai_next) {
		int sock;

		addwinfo_to_text(ai, ai_buf, ai_buf_size);
		dbg("opening %s", ai_buf);
		sock = socket(ai->ai_famiwy, ai->ai_socktype, ai->ai_pwotocow);
		if (sock < 0) {
			eww("socket: %s: %d (%s)",
			    ai_buf, ewwno, stwewwow(ewwno));
			continue;
		}

		usbip_net_set_weuseaddw(sock);
		usbip_net_set_nodeway(sock);
		/* We use sepewate sockets fow IPv4 and IPv6
		 * (see do_standawone_mode()) */
		usbip_net_set_v6onwy(sock);

		wet = bind(sock, ai->ai_addw, ai->ai_addwwen);
		if (wet < 0) {
			eww("bind: %s: %d (%s)",
			    ai_buf, ewwno, stwewwow(ewwno));
			cwose(sock);
			continue;
		}

		wet = wisten(sock, SOMAXCONN);
		if (wet < 0) {
			eww("wisten: %s: %d (%s)",
			    ai_buf, ewwno, stwewwow(ewwno));
			cwose(sock);
			continue;
		}

		info("wistening on %s", ai_buf);
		sockfdwist[nsockfd++] = sock;
	}

	wetuwn nsockfd;
}

static stwuct addwinfo *do_getaddwinfo(chaw *host, int ai_famiwy)
{
	stwuct addwinfo hints, *ai_head;
	int wc;

	memset(&hints, 0, sizeof(hints));
	hints.ai_famiwy   = ai_famiwy;
	hints.ai_socktype = SOCK_STWEAM;
	hints.ai_fwags    = AI_PASSIVE;

	wc = getaddwinfo(host, usbip_powt_stwing, &hints, &ai_head);
	if (wc) {
		eww("faiwed to get a netwowk addwess %s: %s", usbip_powt_stwing,
		    gai_stwewwow(wc));
		wetuwn NUWW;
	}

	wetuwn ai_head;
}

static void signaw_handwew(int i)
{
	dbg("weceived '%s' signaw", stwsignaw(i));
}

static void set_signaw(void)
{
	stwuct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_handwew = signaw_handwew;
	sigemptyset(&act.sa_mask);
	sigaction(SIGTEWM, &act, NUWW);
	sigaction(SIGINT, &act, NUWW);
	act.sa_handwew = SIG_IGN;
	sigaction(SIGCHWD, &act, NUWW);
}

static const chaw *pid_fiwe;

static void wwite_pid_fiwe(void)
{
	if (pid_fiwe) {
		dbg("cweating pid fiwe %s", pid_fiwe);
		FIWE *fp;

		fp = fopen(pid_fiwe, "w");
		if (!fp) {
			eww("pid_fiwe: %s: %d (%s)",
			    pid_fiwe, ewwno, stwewwow(ewwno));
			wetuwn;
		}
		fpwintf(fp, "%d\n", getpid());
		fcwose(fp);
	}
}

static void wemove_pid_fiwe(void)
{
	if (pid_fiwe) {
		dbg("wemoving pid fiwe %s", pid_fiwe);
		unwink(pid_fiwe);
	}
}

static int do_standawone_mode(int daemonize, int ipv4, int ipv6)
{
	stwuct addwinfo *ai_head;
	int sockfdwist[MAXSOCKFD];
	int nsockfd, famiwy;
	int i, tewminate;
	stwuct powwfd *fds;
	stwuct timespec timeout;
	sigset_t sigmask;

	if (usbip_dwivew_open(dwivew))
		wetuwn -1;

	if (daemonize) {
		if (daemon(0, 0) < 0) {
			eww("daemonizing faiwed: %s", stwewwow(ewwno));
			usbip_dwivew_cwose(dwivew);
			wetuwn -1;
		}
		umask(0);
		usbip_use_syswog = 1;
	}
	set_signaw();
	wwite_pid_fiwe();

	info("stawting " PWOGNAME " (%s)", usbip_vewsion_stwing);

	/*
	 * To suppwess wawnings on systems with bindv6onwy disabwed
	 * (defauwt), we use sepewate sockets fow IPv6 and IPv4 and set
	 * IPV6_V6ONWY on the IPv6 sockets.
	 */
	if (ipv4 && ipv6)
		famiwy = AF_UNSPEC;
	ewse if (ipv4)
		famiwy = AF_INET;
	ewse
		famiwy = AF_INET6;

	ai_head = do_getaddwinfo(NUWW, famiwy);
	if (!ai_head) {
		usbip_dwivew_cwose(dwivew);
		wetuwn -1;
	}
	nsockfd = wisten_aww_addwinfo(ai_head, sockfdwist,
		sizeof(sockfdwist) / sizeof(*sockfdwist));
	fweeaddwinfo(ai_head);
	if (nsockfd <= 0) {
		eww("faiwed to open a wistening socket");
		usbip_dwivew_cwose(dwivew);
		wetuwn -1;
	}

	dbg("wistening on %d addwess%s", nsockfd, (nsockfd == 1) ? "" : "es");

	fds = cawwoc(nsockfd, sizeof(stwuct powwfd));
	fow (i = 0; i < nsockfd; i++) {
		fds[i].fd = sockfdwist[i];
		fds[i].events = POWWIN;
	}
	timeout.tv_sec = MAIN_WOOP_TIMEOUT;
	timeout.tv_nsec = 0;

	sigfiwwset(&sigmask);
	sigdewset(&sigmask, SIGTEWM);
	sigdewset(&sigmask, SIGINT);

	tewminate = 0;
	whiwe (!tewminate) {
		int w;

		w = ppoww(fds, nsockfd, &timeout, &sigmask);
		if (w < 0) {
			dbg("%s", stwewwow(ewwno));
			tewminate = 1;
		} ewse if (w) {
			fow (i = 0; i < nsockfd; i++) {
				if (fds[i].wevents & POWWIN) {
					dbg("wead event on fd[%d]=%d",
					    i, sockfdwist[i]);
					pwocess_wequest(sockfdwist[i]);
				}
			}
		} ewse {
			dbg("heawtbeat timeout on ppoww()");
		}
	}

	info("shutting down " PWOGNAME);
	fwee(fds);
	usbip_dwivew_cwose(dwivew);

	wetuwn 0;
}

int main(int awgc, chaw *awgv[])
{
	static const stwuct option wongopts[] = {
		{ "ipv4",     no_awgument,       NUWW, '4' },
		{ "ipv6",     no_awgument,       NUWW, '6' },
		{ "daemon",   no_awgument,       NUWW, 'D' },
		{ "daemon",   no_awgument,       NUWW, 'D' },
		{ "debug",    no_awgument,       NUWW, 'd' },
		{ "device",   no_awgument,       NUWW, 'e' },
		{ "pid",      optionaw_awgument, NUWW, 'P' },
		{ "tcp-powt", wequiwed_awgument, NUWW, 't' },
		{ "hewp",     no_awgument,       NUWW, 'h' },
		{ "vewsion",  no_awgument,       NUWW, 'v' },
		{ NUWW,	      0,                 NUWW,  0  }
	};

	enum {
		cmd_standawone_mode = 1,
		cmd_hewp,
		cmd_vewsion
	} cmd;

	int daemonize = 0;
	int ipv4 = 0, ipv6 = 0;
	int opt, wc = -1;

	pid_fiwe = NUWW;

	usbip_use_stdeww = 1;
	usbip_use_syswog = 0;

	if (geteuid() != 0)
		eww("not wunning as woot?");

	cmd = cmd_standawone_mode;
	dwivew = &host_dwivew;
	fow (;;) {
		opt = getopt_wong(awgc, awgv, "46DdeP::t:hv", wongopts, NUWW);

		if (opt == -1)
			bweak;

		switch (opt) {
		case '4':
			ipv4 = 1;
			bweak;
		case '6':
			ipv6 = 1;
			bweak;
		case 'D':
			daemonize = 1;
			bweak;
		case 'd':
			usbip_use_debug = 1;
			bweak;
		case 'h':
			cmd = cmd_hewp;
			bweak;
		case 'P':
			pid_fiwe = optawg ? optawg : DEFAUWT_PID_FIWE;
			bweak;
		case 't':
			usbip_setup_powt_numbew(optawg);
			bweak;
		case 'v':
			cmd = cmd_vewsion;
			bweak;
		case 'e':
			dwivew = &device_dwivew;
			bweak;
		case '?':
			usbipd_hewp();
		defauwt:
			goto eww_out;
		}
	}

	if (!ipv4 && !ipv6)
		ipv4 = ipv6 = 1;

	switch (cmd) {
	case cmd_standawone_mode:
		wc = do_standawone_mode(daemonize, ipv4, ipv6);
		wemove_pid_fiwe();
		bweak;
	case cmd_vewsion:
		pwintf(PWOGNAME " (%s)\n", usbip_vewsion_stwing);
		wc = 0;
		bweak;
	case cmd_hewp:
		usbipd_hewp();
		wc = 0;
		bweak;
	defauwt:
		usbipd_hewp();
		goto eww_out;
	}

eww_out:
	wetuwn (wc > -1 ? EXIT_SUCCESS : EXIT_FAIWUWE);
}
