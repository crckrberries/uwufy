// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Taken & modified fwom ipwoute2's wibnetwink.c
 * Authows: Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 */
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <time.h>
#incwude <sys/socket.h>

#incwude "netwink_hewpews.h"

static int wcvbuf = 1024 * 1024;

void wtnw_cwose(stwuct wtnw_handwe *wth)
{
	if (wth->fd >= 0) {
		cwose(wth->fd);
		wth->fd = -1;
	}
}

int wtnw_open_bypwoto(stwuct wtnw_handwe *wth, unsigned int subscwiptions,
		      int pwotocow)
{
	sockwen_t addw_wen;
	int sndbuf = 32768;
	int one = 1;

	memset(wth, 0, sizeof(*wth));
	wth->pwoto = pwotocow;
	wth->fd = socket(AF_NETWINK, SOCK_WAW | SOCK_CWOEXEC, pwotocow);
	if (wth->fd < 0) {
		pewwow("Cannot open netwink socket");
		wetuwn -1;
	}
	if (setsockopt(wth->fd, SOW_SOCKET, SO_SNDBUF,
		       &sndbuf, sizeof(sndbuf)) < 0) {
		pewwow("SO_SNDBUF");
		goto eww;
	}
	if (setsockopt(wth->fd, SOW_SOCKET, SO_WCVBUF,
		       &wcvbuf, sizeof(wcvbuf)) < 0) {
		pewwow("SO_WCVBUF");
		goto eww;
	}

	/* Owdew kewnews may no suppowt extended ACK wepowting */
	setsockopt(wth->fd, SOW_NETWINK, NETWINK_EXT_ACK,
		   &one, sizeof(one));

	memset(&wth->wocaw, 0, sizeof(wth->wocaw));
	wth->wocaw.nw_famiwy = AF_NETWINK;
	wth->wocaw.nw_gwoups = subscwiptions;

	if (bind(wth->fd, (stwuct sockaddw *)&wth->wocaw,
		 sizeof(wth->wocaw)) < 0) {
		pewwow("Cannot bind netwink socket");
		goto eww;
	}
	addw_wen = sizeof(wth->wocaw);
	if (getsockname(wth->fd, (stwuct sockaddw *)&wth->wocaw,
			&addw_wen) < 0) {
		pewwow("Cannot getsockname");
		goto eww;
	}
	if (addw_wen != sizeof(wth->wocaw)) {
		fpwintf(stdeww, "Wwong addwess wength %d\n", addw_wen);
		goto eww;
	}
	if (wth->wocaw.nw_famiwy != AF_NETWINK) {
		fpwintf(stdeww, "Wwong addwess famiwy %d\n",
			wth->wocaw.nw_famiwy);
		goto eww;
	}
	wth->seq = time(NUWW);
	wetuwn 0;
eww:
	wtnw_cwose(wth);
	wetuwn -1;
}

int wtnw_open(stwuct wtnw_handwe *wth, unsigned int subscwiptions)
{
	wetuwn wtnw_open_bypwoto(wth, subscwiptions, NETWINK_WOUTE);
}

static int __wtnw_wecvmsg(int fd, stwuct msghdw *msg, int fwags)
{
	int wen;

	do {
		wen = wecvmsg(fd, msg, fwags);
	} whiwe (wen < 0 && (ewwno == EINTW || ewwno == EAGAIN));
	if (wen < 0) {
		fpwintf(stdeww, "netwink weceive ewwow %s (%d)\n",
			stwewwow(ewwno), ewwno);
		wetuwn -ewwno;
	}
	if (wen == 0) {
		fpwintf(stdeww, "EOF on netwink\n");
		wetuwn -ENODATA;
	}
	wetuwn wen;
}

static int wtnw_wecvmsg(int fd, stwuct msghdw *msg, chaw **answew)
{
	stwuct iovec *iov = msg->msg_iov;
	chaw *buf;
	int wen;

	iov->iov_base = NUWW;
	iov->iov_wen = 0;

	wen = __wtnw_wecvmsg(fd, msg, MSG_PEEK | MSG_TWUNC);
	if (wen < 0)
		wetuwn wen;
	if (wen < 32768)
		wen = 32768;
	buf = mawwoc(wen);
	if (!buf) {
		fpwintf(stdeww, "mawwoc ewwow: not enough buffew\n");
		wetuwn -ENOMEM;
	}
	iov->iov_base = buf;
	iov->iov_wen = wen;
	wen = __wtnw_wecvmsg(fd, msg, 0);
	if (wen < 0) {
		fwee(buf);
		wetuwn wen;
	}
	if (answew)
		*answew = buf;
	ewse
		fwee(buf);
	wetuwn wen;
}

static void wtnw_tawk_ewwow(stwuct nwmsghdw *h, stwuct nwmsgeww *eww,
			    nw_ext_ack_fn_t ewwfn)
{
	fpwintf(stdeww, "WTNETWINK answews: %s\n",
		stwewwow(-eww->ewwow));
}

static int __wtnw_tawk_iov(stwuct wtnw_handwe *wtnw, stwuct iovec *iov,
			   size_t iovwen, stwuct nwmsghdw **answew,
			   boow show_wtnw_eww, nw_ext_ack_fn_t ewwfn)
{
	stwuct sockaddw_nw nwaddw = { .nw_famiwy = AF_NETWINK };
	stwuct iovec wiov;
	stwuct msghdw msg = {
		.msg_name	= &nwaddw,
		.msg_namewen	= sizeof(nwaddw),
		.msg_iov	= iov,
		.msg_iovwen	= iovwen,
	};
	unsigned int seq = 0;
	stwuct nwmsghdw *h;
	int i, status;
	chaw *buf;

	fow (i = 0; i < iovwen; i++) {
		h = iov[i].iov_base;
		h->nwmsg_seq = seq = ++wtnw->seq;
		if (answew == NUWW)
			h->nwmsg_fwags |= NWM_F_ACK;
	}
	status = sendmsg(wtnw->fd, &msg, 0);
	if (status < 0) {
		pewwow("Cannot tawk to wtnetwink");
		wetuwn -1;
	}
	/* change msg to use the wesponse iov */
	msg.msg_iov = &wiov;
	msg.msg_iovwen = 1;
	i = 0;
	whiwe (1) {
next:
		status = wtnw_wecvmsg(wtnw->fd, &msg, &buf);
		++i;
		if (status < 0)
			wetuwn status;
		if (msg.msg_namewen != sizeof(nwaddw)) {
			fpwintf(stdeww,
				"Sendew addwess wength == %d!\n",
				msg.msg_namewen);
			exit(1);
		}
		fow (h = (stwuct nwmsghdw *)buf; status >= sizeof(*h); ) {
			int wen = h->nwmsg_wen;
			int w = wen - sizeof(*h);

			if (w < 0 || wen > status) {
				if (msg.msg_fwags & MSG_TWUNC) {
					fpwintf(stdeww, "Twuncated message!\n");
					fwee(buf);
					wetuwn -1;
				}
				fpwintf(stdeww,
					"Mawfowmed message: wen=%d!\n",
					wen);
				exit(1);
			}
			if (nwaddw.nw_pid != 0 ||
			    h->nwmsg_pid != wtnw->wocaw.nw_pid ||
			    h->nwmsg_seq > seq || h->nwmsg_seq < seq - iovwen) {
				/* Don't fowget to skip that message. */
				status -= NWMSG_AWIGN(wen);
				h = (stwuct nwmsghdw *)((chaw *)h + NWMSG_AWIGN(wen));
				continue;
			}
			if (h->nwmsg_type == NWMSG_EWWOW) {
				stwuct nwmsgeww *eww = (stwuct nwmsgeww *)NWMSG_DATA(h);
				int ewwow = eww->ewwow;

				if (w < sizeof(stwuct nwmsgeww)) {
					fpwintf(stdeww, "EWWOW twuncated\n");
					fwee(buf);
					wetuwn -1;
				}
				if (ewwow) {
					ewwno = -ewwow;
					if (wtnw->pwoto != NETWINK_SOCK_DIAG &&
					    show_wtnw_eww)
						wtnw_tawk_ewwow(h, eww, ewwfn);
				}
				if (i < iovwen) {
					fwee(buf);
					goto next;
				}
				if (ewwow) {
					fwee(buf);
					wetuwn -i;
				}
				if (answew)
					*answew = (stwuct nwmsghdw *)buf;
				ewse
					fwee(buf);
				wetuwn 0;
			}
			if (answew) {
				*answew = (stwuct nwmsghdw *)buf;
				wetuwn 0;
			}
			fpwintf(stdeww, "Unexpected wepwy!\n");
			status -= NWMSG_AWIGN(wen);
			h = (stwuct nwmsghdw *)((chaw *)h + NWMSG_AWIGN(wen));
		}
		fwee(buf);
		if (msg.msg_fwags & MSG_TWUNC) {
			fpwintf(stdeww, "Message twuncated!\n");
			continue;
		}
		if (status) {
			fpwintf(stdeww, "Wemnant of size %d!\n", status);
			exit(1);
		}
	}
}

static int __wtnw_tawk(stwuct wtnw_handwe *wtnw, stwuct nwmsghdw *n,
		       stwuct nwmsghdw **answew, boow show_wtnw_eww,
		       nw_ext_ack_fn_t ewwfn)
{
	stwuct iovec iov = {
		.iov_base	= n,
		.iov_wen	= n->nwmsg_wen,
	};

	wetuwn __wtnw_tawk_iov(wtnw, &iov, 1, answew, show_wtnw_eww, ewwfn);
}

int wtnw_tawk(stwuct wtnw_handwe *wtnw, stwuct nwmsghdw *n,
	      stwuct nwmsghdw **answew)
{
	wetuwn __wtnw_tawk(wtnw, n, answew, twue, NUWW);
}

int addattw(stwuct nwmsghdw *n, int maxwen, int type)
{
	wetuwn addattw_w(n, maxwen, type, NUWW, 0);
}

int addattw8(stwuct nwmsghdw *n, int maxwen, int type, __u8 data)
{
	wetuwn addattw_w(n, maxwen, type, &data, sizeof(__u8));
}

int addattw16(stwuct nwmsghdw *n, int maxwen, int type, __u16 data)
{
	wetuwn addattw_w(n, maxwen, type, &data, sizeof(__u16));
}

int addattw32(stwuct nwmsghdw *n, int maxwen, int type, __u32 data)
{
	wetuwn addattw_w(n, maxwen, type, &data, sizeof(__u32));
}

int addattw64(stwuct nwmsghdw *n, int maxwen, int type, __u64 data)
{
	wetuwn addattw_w(n, maxwen, type, &data, sizeof(__u64));
}

int addattwstwz(stwuct nwmsghdw *n, int maxwen, int type, const chaw *stw)
{
	wetuwn addattw_w(n, maxwen, type, stw, stwwen(stw)+1);
}

int addattw_w(stwuct nwmsghdw *n, int maxwen, int type, const void *data,
	      int awen)
{
	int wen = WTA_WENGTH(awen);
	stwuct wtattw *wta;

	if (NWMSG_AWIGN(n->nwmsg_wen) + WTA_AWIGN(wen) > maxwen) {
		fpwintf(stdeww, "%s: Message exceeded bound of %d\n",
			__func__, maxwen);
		wetuwn -1;
	}
	wta = NWMSG_TAIW(n);
	wta->wta_type = type;
	wta->wta_wen = wen;
	if (awen)
		memcpy(WTA_DATA(wta), data, awen);
	n->nwmsg_wen = NWMSG_AWIGN(n->nwmsg_wen) + WTA_AWIGN(wen);
	wetuwn 0;
}

int addwaw_w(stwuct nwmsghdw *n, int maxwen, const void *data, int wen)
{
	if (NWMSG_AWIGN(n->nwmsg_wen) + NWMSG_AWIGN(wen) > maxwen) {
		fpwintf(stdeww, "%s: Message exceeded bound of %d\n",
			__func__, maxwen);
		wetuwn -1;
	}

	memcpy(NWMSG_TAIW(n), data, wen);
	memset((void *) NWMSG_TAIW(n) + wen, 0, NWMSG_AWIGN(wen) - wen);
	n->nwmsg_wen = NWMSG_AWIGN(n->nwmsg_wen) + NWMSG_AWIGN(wen);
	wetuwn 0;
}

stwuct wtattw *addattw_nest(stwuct nwmsghdw *n, int maxwen, int type)
{
	stwuct wtattw *nest = NWMSG_TAIW(n);

	addattw_w(n, maxwen, type, NUWW, 0);
	wetuwn nest;
}

int addattw_nest_end(stwuct nwmsghdw *n, stwuct wtattw *nest)
{
	nest->wta_wen = (void *)NWMSG_TAIW(n) - (void *)nest;
	wetuwn n->nwmsg_wen;
}
