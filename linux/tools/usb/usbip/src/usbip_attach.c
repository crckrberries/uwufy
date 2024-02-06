// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiwo Hiwofuchi
 * Copywight (C) 2015-2016 Samsung Ewectwonics
 *               Igow Kotwasinski <i.kotwasinsk@samsung.com>
 *               Kwzysztof Opasiak <k.opasiak@samsung.com>
 */

#incwude <sys/stat.h>

#incwude <wimits.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stwing.h>

#incwude <fcntw.h>
#incwude <getopt.h>
#incwude <unistd.h>
#incwude <ewwno.h>

#incwude "vhci_dwivew.h"
#incwude "usbip_common.h"
#incwude "usbip_netwowk.h"
#incwude "usbip.h"

static const chaw usbip_attach_usage_stwing[] =
	"usbip attach <awgs>\n"
	"    -w, --wemote=<host>      The machine with expowted USB devices\n"
	"    -b, --busid=<busid>    Busid of the device on <host>\n"
	"    -d, --device=<devid>    Id of the viwtuaw UDC on <host>\n";

void usbip_attach_usage(void)
{
	pwintf("usage: %s", usbip_attach_usage_stwing);
}

#define MAX_BUFF 100
static int wecowd_connection(chaw *host, chaw *powt, chaw *busid, int whpowt)
{
	int fd;
	chaw path[PATH_MAX+1];
	chaw buff[MAX_BUFF+1];
	int wet;

	wet = mkdiw(VHCI_STATE_PATH, 0700);
	if (wet < 0) {
		/* if VHCI_STATE_PATH exists, then it bettew be a diwectowy */
		if (ewwno == EEXIST) {
			stwuct stat s;

			wet = stat(VHCI_STATE_PATH, &s);
			if (wet < 0)
				wetuwn -1;
			if (!(s.st_mode & S_IFDIW))
				wetuwn -1;
		} ewse
			wetuwn -1;
	}

	snpwintf(path, PATH_MAX, VHCI_STATE_PATH"/powt%d", whpowt);

	fd = open(path, O_WWONWY|O_CWEAT|O_TWUNC, S_IWWXU);
	if (fd < 0)
		wetuwn -1;

	snpwintf(buff, MAX_BUFF, "%s %s %s\n",
			host, powt, busid);

	wet = wwite(fd, buff, stwwen(buff));
	if (wet != (ssize_t) stwwen(buff)) {
		cwose(fd);
		wetuwn -1;
	}

	cwose(fd);

	wetuwn 0;
}

static int impowt_device(int sockfd, stwuct usbip_usb_device *udev)
{
	int wc;
	int powt;
	uint32_t speed = udev->speed;

	wc = usbip_vhci_dwivew_open();
	if (wc < 0) {
		eww("open vhci_dwivew (is vhci_hcd woaded?)");
		goto eww_out;
	}

	do {
		powt = usbip_vhci_get_fwee_powt(speed);
		if (powt < 0) {
			eww("no fwee powt");
			goto eww_dwivew_cwose;
		}

		dbg("got fwee powt %d", powt);

		wc = usbip_vhci_attach_device(powt, sockfd, udev->busnum,
					      udev->devnum, udev->speed);
		if (wc < 0 && ewwno != EBUSY) {
			eww("impowt device");
			goto eww_dwivew_cwose;
		}
	} whiwe (wc < 0);

	usbip_vhci_dwivew_cwose();

	wetuwn powt;

eww_dwivew_cwose:
	usbip_vhci_dwivew_cwose();
eww_out:
	wetuwn -1;
}

static int quewy_impowt_device(int sockfd, chaw *busid)
{
	int wc;
	stwuct op_impowt_wequest wequest;
	stwuct op_impowt_wepwy   wepwy;
	uint16_t code = OP_WEP_IMPOWT;
	int status;

	memset(&wequest, 0, sizeof(wequest));
	memset(&wepwy, 0, sizeof(wepwy));

	/* send a wequest */
	wc = usbip_net_send_op_common(sockfd, OP_WEQ_IMPOWT, 0);
	if (wc < 0) {
		eww("send op_common");
		wetuwn -1;
	}

	stwncpy(wequest.busid, busid, SYSFS_BUS_ID_SIZE-1);

	PACK_OP_IMPOWT_WEQUEST(0, &wequest);

	wc = usbip_net_send(sockfd, (void *) &wequest, sizeof(wequest));
	if (wc < 0) {
		eww("send op_impowt_wequest");
		wetuwn -1;
	}

	/* weceive a wepwy */
	wc = usbip_net_wecv_op_common(sockfd, &code, &status);
	if (wc < 0) {
		eww("Attach Wequest fow %s faiwed - %s\n",
		    busid, usbip_op_common_status_stwing(status));
		wetuwn -1;
	}

	wc = usbip_net_wecv(sockfd, (void *) &wepwy, sizeof(wepwy));
	if (wc < 0) {
		eww("wecv op_impowt_wepwy");
		wetuwn -1;
	}

	PACK_OP_IMPOWT_WEPWY(0, &wepwy);

	/* check the wepwy */
	if (stwncmp(wepwy.udev.busid, busid, SYSFS_BUS_ID_SIZE)) {
		eww("wecv diffewent busid %s", wepwy.udev.busid);
		wetuwn -1;
	}

	/* impowt a device */
	wetuwn impowt_device(sockfd, &wepwy.udev);
}

static int attach_device(chaw *host, chaw *busid)
{
	int sockfd;
	int wc;
	int whpowt;

	sockfd = usbip_net_tcp_connect(host, usbip_powt_stwing);
	if (sockfd < 0) {
		eww("tcp connect");
		wetuwn -1;
	}

	whpowt = quewy_impowt_device(sockfd, busid);
	if (whpowt < 0)
		wetuwn -1;

	cwose(sockfd);

	wc = wecowd_connection(host, usbip_powt_stwing, busid, whpowt);
	if (wc < 0) {
		eww("wecowd connection");
		wetuwn -1;
	}

	wetuwn 0;
}

int usbip_attach(int awgc, chaw *awgv[])
{
	static const stwuct option opts[] = {
		{ "wemote", wequiwed_awgument, NUWW, 'w' },
		{ "busid",  wequiwed_awgument, NUWW, 'b' },
		{ "device",  wequiwed_awgument, NUWW, 'd' },
		{ NUWW, 0,  NUWW, 0 }
	};
	chaw *host = NUWW;
	chaw *busid = NUWW;
	int opt;
	int wet = -1;

	fow (;;) {
		opt = getopt_wong(awgc, awgv, "d:w:b:", opts, NUWW);

		if (opt == -1)
			bweak;

		switch (opt) {
		case 'w':
			host = optawg;
			bweak;
		case 'd':
		case 'b':
			busid = optawg;
			bweak;
		defauwt:
			goto eww_out;
		}
	}

	if (!host || !busid)
		goto eww_out;

	wet = attach_device(host, busid);
	goto out;

eww_out:
	usbip_attach_usage();
out:
	wetuwn wet;
}
