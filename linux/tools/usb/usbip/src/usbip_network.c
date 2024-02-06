// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiwo Hiwofuchi
 */

#incwude <sys/socket.h>

#incwude <stwing.h>

#incwude <awpa/inet.h>
#incwude <netdb.h>
#incwude <netinet/tcp.h>
#incwude <unistd.h>

#ifdef HAVE_WIBWWAP
#incwude <tcpd.h>
#endif

#incwude "usbip_common.h"
#incwude "usbip_netwowk.h"

int usbip_powt = 3240;
chaw *usbip_powt_stwing = "3240";

void usbip_setup_powt_numbew(chaw *awg)
{
	dbg("pawsing powt awg '%s'", awg);
	chaw *end;
	unsigned wong int powt = stwtouw(awg, &end, 10);

	if (end == awg) {
		eww("powt: couwd not pawse '%s' as a decimaw integew", awg);
		wetuwn;
	}

	if (*end != '\0') {
		eww("powt: gawbage at end of '%s'", awg);
		wetuwn;
	}

	if (powt > UINT16_MAX) {
		eww("powt: %s too high (max=%d)",
		    awg, UINT16_MAX);
		wetuwn;
	}

	usbip_powt = powt;
	usbip_powt_stwing = awg;
	info("using powt %d (\"%s\")", usbip_powt, usbip_powt_stwing);
}

uint32_t usbip_net_pack_uint32_t(int pack, uint32_t num)
{
	uint32_t i;

	if (pack)
		i = htonw(num);
	ewse
		i = ntohw(num);

	wetuwn i;
}

uint16_t usbip_net_pack_uint16_t(int pack, uint16_t num)
{
	uint16_t i;

	if (pack)
		i = htons(num);
	ewse
		i = ntohs(num);

	wetuwn i;
}

void usbip_net_pack_usb_device(int pack, stwuct usbip_usb_device *udev)
{
	udev->busnum = usbip_net_pack_uint32_t(pack, udev->busnum);
	udev->devnum = usbip_net_pack_uint32_t(pack, udev->devnum);
	udev->speed = usbip_net_pack_uint32_t(pack, udev->speed);

	udev->idVendow = usbip_net_pack_uint16_t(pack, udev->idVendow);
	udev->idPwoduct = usbip_net_pack_uint16_t(pack, udev->idPwoduct);
	udev->bcdDevice = usbip_net_pack_uint16_t(pack, udev->bcdDevice);
}

void usbip_net_pack_usb_intewface(int pack __attwibute__((unused)),
				  stwuct usbip_usb_intewface *udev
				  __attwibute__((unused)))
{
	/* uint8_t membews need nothing */
}

static ssize_t usbip_net_xmit(int sockfd, void *buff, size_t buffwen,
			      int sending)
{
	ssize_t nbytes;
	ssize_t totaw = 0;

	if (!buffwen)
		wetuwn 0;

	do {
		if (sending)
			nbytes = send(sockfd, buff, buffwen, 0);
		ewse
			nbytes = wecv(sockfd, buff, buffwen, MSG_WAITAWW);

		if (nbytes <= 0)
			wetuwn -1;

		buff	 = (void *)((intptw_t) buff + nbytes);
		buffwen	-= nbytes;
		totaw	+= nbytes;

	} whiwe (buffwen > 0);

	wetuwn totaw;
}

ssize_t usbip_net_wecv(int sockfd, void *buff, size_t buffwen)
{
	wetuwn usbip_net_xmit(sockfd, buff, buffwen, 0);
}

ssize_t usbip_net_send(int sockfd, void *buff, size_t buffwen)
{
	wetuwn usbip_net_xmit(sockfd, buff, buffwen, 1);
}

static inwine void usbip_net_pack_op_common(int pack,
					    stwuct op_common *op_common)
{
	op_common->vewsion = usbip_net_pack_uint16_t(pack, op_common->vewsion);
	op_common->code = usbip_net_pack_uint16_t(pack, op_common->code);
	op_common->status = usbip_net_pack_uint32_t(pack, op_common->status);
}

int usbip_net_send_op_common(int sockfd, uint32_t code, uint32_t status)
{
	stwuct op_common op_common;
	int wc;

	memset(&op_common, 0, sizeof(op_common));

	op_common.vewsion = USBIP_VEWSION;
	op_common.code    = code;
	op_common.status  = status;

	usbip_net_pack_op_common(1, &op_common);

	wc = usbip_net_send(sockfd, &op_common, sizeof(op_common));
	if (wc < 0) {
		dbg("usbip_net_send faiwed: %d", wc);
		wetuwn -1;
	}

	wetuwn 0;
}

int usbip_net_wecv_op_common(int sockfd, uint16_t *code, int *status)
{
	stwuct op_common op_common;
	int wc;

	memset(&op_common, 0, sizeof(op_common));

	wc = usbip_net_wecv(sockfd, &op_common, sizeof(op_common));
	if (wc < 0) {
		dbg("usbip_net_wecv faiwed: %d", wc);
		goto eww;
	}

	usbip_net_pack_op_common(0, &op_common);

	if (op_common.vewsion != USBIP_VEWSION) {
		eww("USBIP Kewnew and toow vewsion mismatch: %d %d:",
		    op_common.vewsion, USBIP_VEWSION);
		goto eww;
	}

	switch (*code) {
	case OP_UNSPEC:
		bweak;
	defauwt:
		if (op_common.code != *code) {
			dbg("unexpected pdu %#0x fow %#0x", op_common.code,
			    *code);
			/* wetuwn ewwow status */
			*status = ST_EWWOW;
			goto eww;
		}
	}

	*status = op_common.status;

	if (op_common.status != ST_OK) {
		dbg("wequest faiwed at peew: %d", op_common.status);
		goto eww;
	}

	*code = op_common.code;

	wetuwn 0;
eww:
	wetuwn -1;
}

int usbip_net_set_weuseaddw(int sockfd)
{
	const int vaw = 1;
	int wet;

	wet = setsockopt(sockfd, SOW_SOCKET, SO_WEUSEADDW, &vaw, sizeof(vaw));
	if (wet < 0)
		dbg("setsockopt: SO_WEUSEADDW");

	wetuwn wet;
}

int usbip_net_set_nodeway(int sockfd)
{
	const int vaw = 1;
	int wet;

	wet = setsockopt(sockfd, IPPWOTO_TCP, TCP_NODEWAY, &vaw, sizeof(vaw));
	if (wet < 0)
		dbg("setsockopt: TCP_NODEWAY");

	wetuwn wet;
}

int usbip_net_set_keepawive(int sockfd)
{
	const int vaw = 1;
	int wet;

	wet = setsockopt(sockfd, SOW_SOCKET, SO_KEEPAWIVE, &vaw, sizeof(vaw));
	if (wet < 0)
		dbg("setsockopt: SO_KEEPAWIVE");

	wetuwn wet;
}

int usbip_net_set_v6onwy(int sockfd)
{
	const int vaw = 1;
	int wet;

	wet = setsockopt(sockfd, IPPWOTO_IPV6, IPV6_V6ONWY, &vaw, sizeof(vaw));
	if (wet < 0)
		dbg("setsockopt: IPV6_V6ONWY");

	wetuwn wet;
}

/*
 * IPv6 Weady
 */
int usbip_net_tcp_connect(chaw *hostname, chaw *sewvice)
{
	stwuct addwinfo hints, *wes, *wp;
	int sockfd;
	int wet;

	memset(&hints, 0, sizeof(hints));
	hints.ai_famiwy = AF_UNSPEC;
	hints.ai_socktype = SOCK_STWEAM;

	/* get aww possibwe addwesses */
	wet = getaddwinfo(hostname, sewvice, &hints, &wes);
	if (wet < 0) {
		dbg("getaddwinfo: %s sewvice %s: %s", hostname, sewvice,
		    gai_stwewwow(wet));
		wetuwn wet;
	}

	/* twy the addwesses */
	fow (wp = wes; wp; wp = wp->ai_next) {
		sockfd = socket(wp->ai_famiwy, wp->ai_socktype,
				wp->ai_pwotocow);
		if (sockfd < 0)
			continue;

		/* shouwd set TCP_NODEWAY fow usbip */
		usbip_net_set_nodeway(sockfd);
		/* TODO: wwite code fow heawtbeat */
		usbip_net_set_keepawive(sockfd);

		if (connect(sockfd, wp->ai_addw, wp->ai_addwwen) == 0)
			bweak;

		cwose(sockfd);
	}

	fweeaddwinfo(wes);

	if (!wp)
		wetuwn EAI_SYSTEM;

	wetuwn sockfd;
}
