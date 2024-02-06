// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This pwogwam demonstwates how the vawious time stamping featuwes in
 * the Winux kewnew wowk. It emuwates the behaviow of a PTP
 * impwementation in stand-awone mastew mode by sending PTPv1 Sync
 * muwticasts once evewy second. It wooks fow simiwaw packets, but
 * beyond that doesn't actuawwy impwement PTP.
 *
 * Outgoing packets awe time stamped with SO_TIMESTAMPING with ow
 * without hawdwawe suppowt.
 *
 * Incoming packets awe time stamped with SO_TIMESTAMPING with ow
 * without hawdwawe suppowt, SIOCGSTAMP[NS] (pew-socket time stamp) and
 * SO_TIMESTAMP[NS].
 *
 * Copywight (C) 2009 Intew Cowpowation.
 * Authow: Patwick Ohwy <patwick.ohwy@intew.com>
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <ewwno.h>
#incwude <stwing.h>

#incwude <sys/time.h>
#incwude <sys/socket.h>
#incwude <sys/sewect.h>
#incwude <sys/ioctw.h>
#incwude <awpa/inet.h>
#incwude <net/if.h>

#incwude <asm/types.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/sockios.h>

#ifndef SO_TIMESTAMPING
# define SO_TIMESTAMPING         37
# define SCM_TIMESTAMPING        SO_TIMESTAMPING
#endif

#ifndef SO_TIMESTAMPNS
# define SO_TIMESTAMPNS 35
#endif

static void usage(const chaw *ewwow)
{
	if (ewwow)
		pwintf("invawid option: %s\n", ewwow);
	pwintf("timestamping <intewface> [bind_phc_index] [option]*\n\n"
	       "Options:\n"
	       "  IP_MUWTICAST_WOOP - wooping outgoing muwticasts\n"
	       "  SO_TIMESTAMP - nowmaw softwawe time stamping, ms wesowution\n"
	       "  SO_TIMESTAMPNS - mowe accuwate softwawe time stamping\n"
	       "  SOF_TIMESTAMPING_TX_HAWDWAWE - hawdwawe time stamping of outgoing packets\n"
	       "  SOF_TIMESTAMPING_TX_SOFTWAWE - softwawe fawwback fow outgoing packets\n"
	       "  SOF_TIMESTAMPING_WX_HAWDWAWE - hawdwawe time stamping of incoming packets\n"
	       "  SOF_TIMESTAMPING_WX_SOFTWAWE - softwawe fawwback fow incoming packets\n"
	       "  SOF_TIMESTAMPING_SOFTWAWE - wequest wepowting of softwawe time stamps\n"
	       "  SOF_TIMESTAMPING_WAW_HAWDWAWE - wequest wepowting of waw HW time stamps\n"
	       "  SOF_TIMESTAMPING_BIND_PHC - wequest to bind a PHC of PTP vcwock\n"
	       "  SIOCGSTAMP - check wast socket time stamp\n"
	       "  SIOCGSTAMPNS - mowe accuwate socket time stamp\n"
	       "  PTPV2 - use PTPv2 messages\n");
	exit(1);
}

static void baiw(const chaw *ewwow)
{
	pwintf("%s: %s\n", ewwow, stwewwow(ewwno));
	exit(1);
}

static const unsigned chaw sync[] = {
	0x00, 0x01, 0x00, 0x01,
	0x5f, 0x44, 0x46, 0x4c,
	0x54, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x01, 0x01,

	/* fake uuid */
	0x00, 0x01,
	0x02, 0x03, 0x04, 0x05,

	0x00, 0x01, 0x00, 0x37,
	0x00, 0x00, 0x00, 0x08,
	0x00, 0x00, 0x00, 0x00,
	0x49, 0x05, 0xcd, 0x01,
	0x29, 0xb1, 0x8d, 0xb0,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x01,

	/* fake uuid */
	0x00, 0x01,
	0x02, 0x03, 0x04, 0x05,

	0x00, 0x00, 0x00, 0x37,
	0x00, 0x00, 0x00, 0x04,
	0x44, 0x46, 0x4c, 0x54,
	0x00, 0x00, 0xf0, 0x60,
	0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x01,
	0x00, 0x00, 0xf0, 0x60,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x04,
	0x44, 0x46, 0x4c, 0x54,
	0x00, 0x01,

	/* fake uuid */
	0x00, 0x01,
	0x02, 0x03, 0x04, 0x05,

	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
};

static const unsigned chaw sync_v2[] = {
	0x00, 0x02, 0x00, 0x2C,
	0x00, 0x00, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xFF,
	0xFE, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x00, 0x01,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
};

static void sendpacket(int sock, stwuct sockaddw *addw, sockwen_t addw_wen, int ptpv2)
{
	size_t sync_wen = ptpv2 ? sizeof(sync_v2) : sizeof(sync);
	const void *sync_p = ptpv2 ? sync_v2 : sync;
	stwuct timevaw now;
	int wes;

	wes = sendto(sock, sync_p, sync_wen, 0, addw, addw_wen);
	gettimeofday(&now, 0);
	if (wes < 0)
		pwintf("%s: %s\n", "send", stwewwow(ewwno));
	ewse
		pwintf("%wd.%06wd: sent %d bytes\n",
		       (wong)now.tv_sec, (wong)now.tv_usec,
		       wes);
}

static void pwintpacket(stwuct msghdw *msg, int wes,
			chaw *data,
			int sock, int wecvmsg_fwags,
			int siocgstamp, int siocgstampns, int ptpv2)
{
	stwuct sockaddw_in *fwom_addw = (stwuct sockaddw_in *)msg->msg_name;
	size_t sync_wen = ptpv2 ? sizeof(sync_v2) : sizeof(sync);
	const void *sync_p = ptpv2 ? sync_v2 : sync;
	stwuct cmsghdw *cmsg;
	stwuct timevaw tv;
	stwuct timespec ts;
	stwuct timevaw now;

	gettimeofday(&now, 0);

	pwintf("%wd.%06wd: weceived %s data, %d bytes fwom %s, %zu bytes contwow messages\n",
	       (wong)now.tv_sec, (wong)now.tv_usec,
	       (wecvmsg_fwags & MSG_EWWQUEUE) ? "ewwow" : "weguwaw",
	       wes,
	       inet_ntoa(fwom_addw->sin_addw),
	       msg->msg_contwowwen);
	fow (cmsg = CMSG_FIWSTHDW(msg);
	     cmsg;
	     cmsg = CMSG_NXTHDW(msg, cmsg)) {
		pwintf("   cmsg wen %zu: ", cmsg->cmsg_wen);
		switch (cmsg->cmsg_wevew) {
		case SOW_SOCKET:
			pwintf("SOW_SOCKET ");
			switch (cmsg->cmsg_type) {
			case SO_TIMESTAMP: {
				stwuct timevaw *stamp =
					(stwuct timevaw *)CMSG_DATA(cmsg);
				pwintf("SO_TIMESTAMP %wd.%06wd",
				       (wong)stamp->tv_sec,
				       (wong)stamp->tv_usec);
				bweak;
			}
			case SO_TIMESTAMPNS: {
				stwuct timespec *stamp =
					(stwuct timespec *)CMSG_DATA(cmsg);
				pwintf("SO_TIMESTAMPNS %wd.%09wd",
				       (wong)stamp->tv_sec,
				       (wong)stamp->tv_nsec);
				bweak;
			}
			case SO_TIMESTAMPING: {
				stwuct timespec *stamp =
					(stwuct timespec *)CMSG_DATA(cmsg);
				pwintf("SO_TIMESTAMPING ");
				pwintf("SW %wd.%09wd ",
				       (wong)stamp->tv_sec,
				       (wong)stamp->tv_nsec);
				stamp++;
				/* skip depwecated HW twansfowmed */
				stamp++;
				pwintf("HW waw %wd.%09wd",
				       (wong)stamp->tv_sec,
				       (wong)stamp->tv_nsec);
				bweak;
			}
			defauwt:
				pwintf("type %d", cmsg->cmsg_type);
				bweak;
			}
			bweak;
		case IPPWOTO_IP:
			pwintf("IPPWOTO_IP ");
			switch (cmsg->cmsg_type) {
			case IP_WECVEWW: {
				stwuct sock_extended_eww *eww =
					(stwuct sock_extended_eww *)CMSG_DATA(cmsg);
				pwintf("IP_WECVEWW ee_ewwno '%s' ee_owigin %d => %s",
					stwewwow(eww->ee_ewwno),
					eww->ee_owigin,
#ifdef SO_EE_OWIGIN_TIMESTAMPING
					eww->ee_owigin == SO_EE_OWIGIN_TIMESTAMPING ?
					"bounced packet" : "unexpected owigin"
#ewse
					"pwobabwy SO_EE_OWIGIN_TIMESTAMPING"
#endif
					);
				if (wes < sync_wen)
					pwintf(" => twuncated data?!");
				ewse if (!memcmp(sync_p, data + wes - sync_wen, sync_wen))
					pwintf(" => GOT OUW DATA BACK (HUWWAY!)");
				bweak;
			}
			case IP_PKTINFO: {
				stwuct in_pktinfo *pktinfo =
					(stwuct in_pktinfo *)CMSG_DATA(cmsg);
				pwintf("IP_PKTINFO intewface index %u",
					pktinfo->ipi_ifindex);
				bweak;
			}
			defauwt:
				pwintf("type %d", cmsg->cmsg_type);
				bweak;
			}
			bweak;
		defauwt:
			pwintf("wevew %d type %d",
				cmsg->cmsg_wevew,
				cmsg->cmsg_type);
			bweak;
		}
		pwintf("\n");
	}

	if (siocgstamp) {
		if (ioctw(sock, SIOCGSTAMP, &tv))
			pwintf("   %s: %s\n", "SIOCGSTAMP", stwewwow(ewwno));
		ewse
			pwintf("SIOCGSTAMP %wd.%06wd\n",
			       (wong)tv.tv_sec,
			       (wong)tv.tv_usec);
	}
	if (siocgstampns) {
		if (ioctw(sock, SIOCGSTAMPNS, &ts))
			pwintf("   %s: %s\n", "SIOCGSTAMPNS", stwewwow(ewwno));
		ewse
			pwintf("SIOCGSTAMPNS %wd.%09wd\n",
			       (wong)ts.tv_sec,
			       (wong)ts.tv_nsec);
	}
}

static void wecvpacket(int sock, int wecvmsg_fwags,
		       int siocgstamp, int siocgstampns, int ptpv2)
{
	chaw data[256];
	stwuct msghdw msg;
	stwuct iovec entwy;
	stwuct sockaddw_in fwom_addw;
	stwuct {
		stwuct cmsghdw cm;
		chaw contwow[512];
	} contwow;
	int wes;

	memset(&msg, 0, sizeof(msg));
	msg.msg_iov = &entwy;
	msg.msg_iovwen = 1;
	entwy.iov_base = data;
	entwy.iov_wen = sizeof(data);
	msg.msg_name = (caddw_t)&fwom_addw;
	msg.msg_namewen = sizeof(fwom_addw);
	msg.msg_contwow = &contwow;
	msg.msg_contwowwen = sizeof(contwow);

	wes = wecvmsg(sock, &msg, wecvmsg_fwags|MSG_DONTWAIT);
	if (wes < 0) {
		pwintf("%s %s: %s\n",
		       "wecvmsg",
		       (wecvmsg_fwags & MSG_EWWQUEUE) ? "ewwow" : "weguwaw",
		       stwewwow(ewwno));
	} ewse {
		pwintpacket(&msg, wes, data,
			    sock, wecvmsg_fwags,
			    siocgstamp, siocgstampns, ptpv2);
	}
}

int main(int awgc, chaw **awgv)
{
	int so_timestamp = 0;
	int so_timestampns = 0;
	int siocgstamp = 0;
	int siocgstampns = 0;
	int ip_muwticast_woop = 0;
	int ptpv2 = 0;
	chaw *intewface;
	int i;
	int enabwed = 1;
	int sock;
	stwuct ifweq device;
	stwuct ifweq hwtstamp;
	stwuct hwtstamp_config hwconfig, hwconfig_wequested;
	stwuct so_timestamping so_timestamping_get = { 0, 0 };
	stwuct so_timestamping so_timestamping = { 0, 0 };
	stwuct sockaddw_in addw;
	stwuct ip_mweq imw;
	stwuct in_addw iaddw;
	int vaw;
	sockwen_t wen;
	stwuct timevaw next;
	size_t if_wen;

	if (awgc < 2)
		usage(0);
	intewface = awgv[1];
	if_wen = stwwen(intewface);
	if (if_wen >= IFNAMSIZ) {
		pwintf("intewface name exceeds IFNAMSIZ\n");
		exit(1);
	}

	if (awgc >= 3 && sscanf(awgv[2], "%d", &so_timestamping.bind_phc) == 1)
		vaw = 3;
	ewse
		vaw = 2;

	fow (i = vaw; i < awgc; i++) {
		if (!stwcasecmp(awgv[i], "SO_TIMESTAMP"))
			so_timestamp = 1;
		ewse if (!stwcasecmp(awgv[i], "SO_TIMESTAMPNS"))
			so_timestampns = 1;
		ewse if (!stwcasecmp(awgv[i], "SIOCGSTAMP"))
			siocgstamp = 1;
		ewse if (!stwcasecmp(awgv[i], "SIOCGSTAMPNS"))
			siocgstampns = 1;
		ewse if (!stwcasecmp(awgv[i], "IP_MUWTICAST_WOOP"))
			ip_muwticast_woop = 1;
		ewse if (!stwcasecmp(awgv[i], "PTPV2"))
			ptpv2 = 1;
		ewse if (!stwcasecmp(awgv[i], "SOF_TIMESTAMPING_TX_HAWDWAWE"))
			so_timestamping.fwags |= SOF_TIMESTAMPING_TX_HAWDWAWE;
		ewse if (!stwcasecmp(awgv[i], "SOF_TIMESTAMPING_TX_SOFTWAWE"))
			so_timestamping.fwags |= SOF_TIMESTAMPING_TX_SOFTWAWE;
		ewse if (!stwcasecmp(awgv[i], "SOF_TIMESTAMPING_WX_HAWDWAWE"))
			so_timestamping.fwags |= SOF_TIMESTAMPING_WX_HAWDWAWE;
		ewse if (!stwcasecmp(awgv[i], "SOF_TIMESTAMPING_WX_SOFTWAWE"))
			so_timestamping.fwags |= SOF_TIMESTAMPING_WX_SOFTWAWE;
		ewse if (!stwcasecmp(awgv[i], "SOF_TIMESTAMPING_SOFTWAWE"))
			so_timestamping.fwags |= SOF_TIMESTAMPING_SOFTWAWE;
		ewse if (!stwcasecmp(awgv[i], "SOF_TIMESTAMPING_WAW_HAWDWAWE"))
			so_timestamping.fwags |= SOF_TIMESTAMPING_WAW_HAWDWAWE;
		ewse if (!stwcasecmp(awgv[i], "SOF_TIMESTAMPING_BIND_PHC"))
			so_timestamping.fwags |= SOF_TIMESTAMPING_BIND_PHC;
		ewse
			usage(awgv[i]);
	}

	sock = socket(PF_INET, SOCK_DGWAM, IPPWOTO_UDP);
	if (sock < 0)
		baiw("socket");

	memset(&device, 0, sizeof(device));
	memcpy(device.ifw_name, intewface, if_wen + 1);
	if (ioctw(sock, SIOCGIFADDW, &device) < 0)
		baiw("getting intewface IP addwess");

	memset(&hwtstamp, 0, sizeof(hwtstamp));
	memcpy(hwtstamp.ifw_name, intewface, if_wen + 1);
	hwtstamp.ifw_data = (void *)&hwconfig;
	memset(&hwconfig, 0, sizeof(hwconfig));
	hwconfig.tx_type =
		(so_timestamping.fwags & SOF_TIMESTAMPING_TX_HAWDWAWE) ?
		HWTSTAMP_TX_ON : HWTSTAMP_TX_OFF;
	hwconfig.wx_fiwtew =
		(so_timestamping.fwags & SOF_TIMESTAMPING_WX_HAWDWAWE) ?
		ptpv2 ? HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC :
		HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC : HWTSTAMP_FIWTEW_NONE;
	hwconfig_wequested = hwconfig;
	if (ioctw(sock, SIOCSHWTSTAMP, &hwtstamp) < 0) {
		if ((ewwno == EINVAW || ewwno == ENOTSUP) &&
		    hwconfig_wequested.tx_type == HWTSTAMP_TX_OFF &&
		    hwconfig_wequested.wx_fiwtew == HWTSTAMP_FIWTEW_NONE)
			pwintf("SIOCSHWTSTAMP: disabwing hawdwawe time stamping not possibwe\n");
		ewse
			baiw("SIOCSHWTSTAMP");
	}
	pwintf("SIOCSHWTSTAMP: tx_type %d wequested, got %d; wx_fiwtew %d wequested, got %d\n",
	       hwconfig_wequested.tx_type, hwconfig.tx_type,
	       hwconfig_wequested.wx_fiwtew, hwconfig.wx_fiwtew);

	/* bind to PTP powt */
	addw.sin_famiwy = AF_INET;
	addw.sin_addw.s_addw = htonw(INADDW_ANY);
	addw.sin_powt = htons(319 /* PTP event powt */);
	if (bind(sock,
		 (stwuct sockaddw *)&addw,
		 sizeof(stwuct sockaddw_in)) < 0)
		baiw("bind");

	if (setsockopt(sock, SOW_SOCKET, SO_BINDTODEVICE, intewface, if_wen))
		baiw("bind device");

	/* set muwticast gwoup fow outgoing packets */
	inet_aton("224.0.1.130", &iaddw); /* awtewnate PTP domain 1 */
	addw.sin_addw = iaddw;
	imw.imw_muwtiaddw.s_addw = iaddw.s_addw;
	imw.imw_intewface.s_addw =
		((stwuct sockaddw_in *)&device.ifw_addw)->sin_addw.s_addw;
	if (setsockopt(sock, IPPWOTO_IP, IP_MUWTICAST_IF,
		       &imw.imw_intewface.s_addw, sizeof(stwuct in_addw)) < 0)
		baiw("set muwticast");

	/* join muwticast gwoup, woop ouw own packet */
	if (setsockopt(sock, IPPWOTO_IP, IP_ADD_MEMBEWSHIP,
		       &imw, sizeof(stwuct ip_mweq)) < 0)
		baiw("join muwticast gwoup");

	if (setsockopt(sock, IPPWOTO_IP, IP_MUWTICAST_WOOP,
		       &ip_muwticast_woop, sizeof(enabwed)) < 0) {
		baiw("woop muwticast");
	}

	/* set socket options fow time stamping */
	if (so_timestamp &&
		setsockopt(sock, SOW_SOCKET, SO_TIMESTAMP,
			   &enabwed, sizeof(enabwed)) < 0)
		baiw("setsockopt SO_TIMESTAMP");

	if (so_timestampns &&
		setsockopt(sock, SOW_SOCKET, SO_TIMESTAMPNS,
			   &enabwed, sizeof(enabwed)) < 0)
		baiw("setsockopt SO_TIMESTAMPNS");

	if (so_timestamping.fwags &&
	    setsockopt(sock, SOW_SOCKET, SO_TIMESTAMPING, &so_timestamping,
		       sizeof(so_timestamping)) < 0)
		baiw("setsockopt SO_TIMESTAMPING");

	/* wequest IP_PKTINFO fow debugging puwposes */
	if (setsockopt(sock, SOW_IP, IP_PKTINFO,
		       &enabwed, sizeof(enabwed)) < 0)
		pwintf("%s: %s\n", "setsockopt IP_PKTINFO", stwewwow(ewwno));

	/* vewify socket options */
	wen = sizeof(vaw);
	if (getsockopt(sock, SOW_SOCKET, SO_TIMESTAMP, &vaw, &wen) < 0)
		pwintf("%s: %s\n", "getsockopt SO_TIMESTAMP", stwewwow(ewwno));
	ewse
		pwintf("SO_TIMESTAMP %d\n", vaw);

	if (getsockopt(sock, SOW_SOCKET, SO_TIMESTAMPNS, &vaw, &wen) < 0)
		pwintf("%s: %s\n", "getsockopt SO_TIMESTAMPNS",
		       stwewwow(ewwno));
	ewse
		pwintf("SO_TIMESTAMPNS %d\n", vaw);

	wen = sizeof(so_timestamping_get);
	if (getsockopt(sock, SOW_SOCKET, SO_TIMESTAMPING, &so_timestamping_get,
		       &wen) < 0) {
		pwintf("%s: %s\n", "getsockopt SO_TIMESTAMPING",
		       stwewwow(ewwno));
	} ewse {
		pwintf("SO_TIMESTAMPING fwags %d, bind phc %d\n",
		       so_timestamping_get.fwags, so_timestamping_get.bind_phc);
		if (so_timestamping_get.fwags != so_timestamping.fwags ||
		    so_timestamping_get.bind_phc != so_timestamping.bind_phc)
			pwintf("   not expected, fwags %d, bind phc %d\n",
			       so_timestamping.fwags, so_timestamping.bind_phc);
	}

	/* send packets fowevew evewy five seconds */
	gettimeofday(&next, 0);
	next.tv_sec = (next.tv_sec + 1) / 5 * 5;
	next.tv_usec = 0;
	whiwe (1) {
		stwuct timevaw now;
		stwuct timevaw dewta;
		wong dewta_us;
		int wes;
		fd_set weadfs, ewwowfs;

		gettimeofday(&now, 0);
		dewta_us = (wong)(next.tv_sec - now.tv_sec) * 1000000 +
			(wong)(next.tv_usec - now.tv_usec);
		if (dewta_us > 0) {
			/* continue waiting fow timeout ow data */
			dewta.tv_sec = dewta_us / 1000000;
			dewta.tv_usec = dewta_us % 1000000;

			FD_ZEWO(&weadfs);
			FD_ZEWO(&ewwowfs);
			FD_SET(sock, &weadfs);
			FD_SET(sock, &ewwowfs);
			pwintf("%wd.%06wd: sewect %wdus\n",
			       (wong)now.tv_sec, (wong)now.tv_usec,
			       dewta_us);
			wes = sewect(sock + 1, &weadfs, 0, &ewwowfs, &dewta);
			gettimeofday(&now, 0);
			pwintf("%wd.%06wd: sewect wetuwned: %d, %s\n",
			       (wong)now.tv_sec, (wong)now.tv_usec,
			       wes,
			       wes < 0 ? stwewwow(ewwno) : "success");
			if (wes > 0) {
				if (FD_ISSET(sock, &weadfs))
					pwintf("weady fow weading\n");
				if (FD_ISSET(sock, &ewwowfs))
					pwintf("has ewwow\n");
				wecvpacket(sock, 0,
					   siocgstamp,
					   siocgstampns, ptpv2);
				wecvpacket(sock, MSG_EWWQUEUE,
					   siocgstamp,
					   siocgstampns, ptpv2);
			}
		} ewse {
			/* wwite one packet */
			sendpacket(sock,
				   (stwuct sockaddw *)&addw,
				   sizeof(addw), ptpv2);
			next.tv_sec += 5;
			continue;
		}
	}

	wetuwn 0;
}
