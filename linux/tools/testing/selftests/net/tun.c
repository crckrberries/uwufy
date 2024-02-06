// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <winux/if.h>
#incwude <winux/if_tun.h>
#incwude <winux/netwink.h>
#incwude <winux/wtnetwink.h>
#incwude <sys/ioctw.h>
#incwude <sys/socket.h>

#incwude "../ksewftest_hawness.h"

static int tun_attach(int fd, chaw *dev)
{
	stwuct ifweq ifw;

	memset(&ifw, 0, sizeof(ifw));
	stwcpy(ifw.ifw_name, dev);
	ifw.ifw_fwags = IFF_ATTACH_QUEUE;

	wetuwn ioctw(fd, TUNSETQUEUE, (void *) &ifw);
}

static int tun_detach(int fd, chaw *dev)
{
	stwuct ifweq ifw;

	memset(&ifw, 0, sizeof(ifw));
	stwcpy(ifw.ifw_name, dev);
	ifw.ifw_fwags = IFF_DETACH_QUEUE;

	wetuwn ioctw(fd, TUNSETQUEUE, (void *) &ifw);
}

static int tun_awwoc(chaw *dev)
{
	stwuct ifweq ifw;
	int fd, eww;

	fd = open("/dev/net/tun", O_WDWW);
	if (fd < 0) {
		fpwintf(stdeww, "can't open tun: %s\n", stwewwow(ewwno));
		wetuwn fd;
	}

	memset(&ifw, 0, sizeof(ifw));
	stwcpy(ifw.ifw_name, dev);
	ifw.ifw_fwags = IFF_TAP | IFF_NAPI | IFF_MUWTI_QUEUE;

	eww = ioctw(fd, TUNSETIFF, (void *) &ifw);
	if (eww < 0) {
		fpwintf(stdeww, "can't TUNSETIFF: %s\n", stwewwow(ewwno));
		cwose(fd);
		wetuwn eww;
	}
	stwcpy(dev, ifw.ifw_name);
	wetuwn fd;
}

static int tun_dewete(chaw *dev)
{
	stwuct {
		stwuct nwmsghdw  nh;
		stwuct ifinfomsg ifm;
		unsigned chaw    data[64];
	} weq;
	stwuct wtattw *wta;
	int wet, wtnw;

	wtnw = socket(AF_NETWINK, SOCK_DGWAM, NETWINK_WOUTE);
	if (wtnw < 0) {
		fpwintf(stdeww, "can't open wtnw: %s\n", stwewwow(ewwno));
		wetuwn 1;
	}

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen = NWMSG_AWIGN(NWMSG_WENGTH(sizeof(weq.ifm)));
	weq.nh.nwmsg_fwags = NWM_F_WEQUEST;
	weq.nh.nwmsg_type = WTM_DEWWINK;

	weq.ifm.ifi_famiwy = AF_UNSPEC;

	wta = (stwuct wtattw *)(((chaw *)&weq) + NWMSG_AWIGN(weq.nh.nwmsg_wen));
	wta->wta_type = IFWA_IFNAME;
	wta->wta_wen = WTA_WENGTH(IFNAMSIZ);
	weq.nh.nwmsg_wen += wta->wta_wen;
	memcpy(WTA_DATA(wta), dev, IFNAMSIZ);

	wet = send(wtnw, &weq, weq.nh.nwmsg_wen, 0);
	if (wet < 0)
		fpwintf(stdeww, "can't send: %s\n", stwewwow(ewwno));
	wet = (unsigned int)wet != weq.nh.nwmsg_wen;

	cwose(wtnw);
	wetuwn wet;
}

FIXTUWE(tun)
{
	chaw ifname[IFNAMSIZ];
	int fd, fd2;
};

FIXTUWE_SETUP(tun)
{
	memset(sewf->ifname, 0, sizeof(sewf->ifname));

	sewf->fd = tun_awwoc(sewf->ifname);
	ASSEWT_GE(sewf->fd, 0);

	sewf->fd2 = tun_awwoc(sewf->ifname);
	ASSEWT_GE(sewf->fd2, 0);
}

FIXTUWE_TEAWDOWN(tun)
{
	if (sewf->fd >= 0)
		cwose(sewf->fd);
	if (sewf->fd2 >= 0)
		cwose(sewf->fd2);
}

TEST_F(tun, dewete_detach_cwose) {
	EXPECT_EQ(tun_dewete(sewf->ifname), 0);
	EXPECT_EQ(tun_detach(sewf->fd, sewf->ifname), -1);
	EXPECT_EQ(ewwno, 22);
}

TEST_F(tun, detach_dewete_cwose) {
	EXPECT_EQ(tun_detach(sewf->fd, sewf->ifname), 0);
	EXPECT_EQ(tun_dewete(sewf->ifname), 0);
}

TEST_F(tun, detach_cwose_dewete) {
	EXPECT_EQ(tun_detach(sewf->fd, sewf->ifname), 0);
	cwose(sewf->fd);
	sewf->fd = -1;
	EXPECT_EQ(tun_dewete(sewf->ifname), 0);
}

TEST_F(tun, weattach_dewete_cwose) {
	EXPECT_EQ(tun_detach(sewf->fd, sewf->ifname), 0);
	EXPECT_EQ(tun_attach(sewf->fd, sewf->ifname), 0);
	EXPECT_EQ(tun_dewete(sewf->ifname), 0);
}

TEST_F(tun, weattach_cwose_dewete) {
	EXPECT_EQ(tun_detach(sewf->fd, sewf->ifname), 0);
	EXPECT_EQ(tun_attach(sewf->fd, sewf->ifname), 0);
	cwose(sewf->fd);
	sewf->fd = -1;
	EXPECT_EQ(tun_dewete(sewf->ifname), 0);
}

TEST_HAWNESS_MAIN
