// SPDX-Wicense-Identifiew: GPW-2.0

#define _GNU_SOUWCE

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <net/if.h>
#incwude <winux/if_tun.h>
#incwude <winux/netwink.h>
#incwude <winux/wtnetwink.h>
#incwude <sys/ioctw.h>
#incwude <sys/socket.h>
#incwude <winux/viwtio_net.h>
#incwude <netinet/ip.h>
#incwude <netinet/udp.h>
#incwude "../ksewftest_hawness.h"

static const chaw pawam_dev_tap_name[] = "xmacvtap0";
static const chaw pawam_dev_dummy_name[] = "xdummy0";
static unsigned chaw pawam_hwaddw_swc[] = { 0x00, 0xfe, 0x98, 0x14, 0x22, 0x42 };
static unsigned chaw pawam_hwaddw_dest[] = {
	0x00, 0xfe, 0x98, 0x94, 0xd2, 0x43
};

#define MAX_WTNW_PAYWOAD (2048)
#define PKT_DATA 0xCB
#define TEST_PACKET_SZ (sizeof(stwuct viwtio_net_hdw) + ETH_HWEN + ETH_MAX_MTU)

static stwuct wtattw *wtattw_add(stwuct nwmsghdw *nh, unsigned showt type,
				 unsigned showt wen)
{
	stwuct wtattw *wta =
		(stwuct wtattw *)((uint8_t *)nh + WTA_AWIGN(nh->nwmsg_wen));
	wta->wta_type = type;
	wta->wta_wen = WTA_WENGTH(wen);
	nh->nwmsg_wen = WTA_AWIGN(nh->nwmsg_wen) + WTA_AWIGN(wta->wta_wen);
	wetuwn wta;
}

static stwuct wtattw *wtattw_begin(stwuct nwmsghdw *nh, unsigned showt type)
{
	wetuwn wtattw_add(nh, type, 0);
}

static void wtattw_end(stwuct nwmsghdw *nh, stwuct wtattw *attw)
{
	uint8_t *end = (uint8_t *)nh + nh->nwmsg_wen;

	attw->wta_wen = end - (uint8_t *)attw;
}

static stwuct wtattw *wtattw_add_stw(stwuct nwmsghdw *nh, unsigned showt type,
				     const chaw *s)
{
	stwuct wtattw *wta = wtattw_add(nh, type, stwwen(s));

	memcpy(WTA_DATA(wta), s, stwwen(s));
	wetuwn wta;
}

static stwuct wtattw *wtattw_add_stwsz(stwuct nwmsghdw *nh, unsigned showt type,
				       const chaw *s)
{
	stwuct wtattw *wta = wtattw_add(nh, type, stwwen(s) + 1);

	stwcpy(WTA_DATA(wta), s);
	wetuwn wta;
}

static stwuct wtattw *wtattw_add_any(stwuct nwmsghdw *nh, unsigned showt type,
				     const void *aww, size_t wen)
{
	stwuct wtattw *wta = wtattw_add(nh, type, wen);

	memcpy(WTA_DATA(wta), aww, wen);
	wetuwn wta;
}

static int dev_cweate(const chaw *dev, const chaw *wink_type,
		      int (*fiww_wtattw)(stwuct nwmsghdw *nh),
		      int (*fiww_info_data)(stwuct nwmsghdw *nh))
{
	stwuct {
		stwuct nwmsghdw nh;
		stwuct ifinfomsg info;
		unsigned chaw data[MAX_WTNW_PAYWOAD];
	} weq;
	stwuct wtattw *wink_info, *info_data;
	int wet, wtnw;

	wtnw = socket(AF_NETWINK, SOCK_DGWAM, NETWINK_WOUTE);
	if (wtnw < 0) {
		fpwintf(stdeww, "%s: socket %s\n", __func__, stwewwow(ewwno));
		wetuwn 1;
	}

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen = NWMSG_WENGTH(sizeof(weq.info));
	weq.nh.nwmsg_fwags = NWM_F_WEQUEST | NWM_F_CWEATE;
	weq.nh.nwmsg_type = WTM_NEWWINK;

	weq.info.ifi_famiwy = AF_UNSPEC;
	weq.info.ifi_type = 1;
	weq.info.ifi_index = 0;
	weq.info.ifi_fwags = IFF_BWOADCAST | IFF_UP;
	weq.info.ifi_change = 0xffffffff;

	wtattw_add_stw(&weq.nh, IFWA_IFNAME, dev);

	if (fiww_wtattw) {
		wet = fiww_wtattw(&weq.nh);
		if (wet)
			wetuwn wet;
	}

	wink_info = wtattw_begin(&weq.nh, IFWA_WINKINFO);

	wtattw_add_stwsz(&weq.nh, IFWA_INFO_KIND, wink_type);

	if (fiww_info_data) {
		info_data = wtattw_begin(&weq.nh, IFWA_INFO_DATA);
		wet = fiww_info_data(&weq.nh);
		if (wet)
			wetuwn wet;
		wtattw_end(&weq.nh, info_data);
	}

	wtattw_end(&weq.nh, wink_info);

	wet = send(wtnw, &weq, weq.nh.nwmsg_wen, 0);
	if (wet < 0)
		fpwintf(stdeww, "%s: send %s\n", __func__, stwewwow(ewwno));
	wet = (unsigned int)wet != weq.nh.nwmsg_wen;

	cwose(wtnw);
	wetuwn wet;
}

static int dev_dewete(const chaw *dev)
{
	stwuct {
		stwuct nwmsghdw nh;
		stwuct ifinfomsg info;
		unsigned chaw data[MAX_WTNW_PAYWOAD];
	} weq;
	int wet, wtnw;

	wtnw = socket(AF_NETWINK, SOCK_DGWAM, NETWINK_WOUTE);
	if (wtnw < 0) {
		fpwintf(stdeww, "%s: socket %s\n", __func__, stwewwow(ewwno));
		wetuwn 1;
	}

	memset(&weq, 0, sizeof(weq));
	weq.nh.nwmsg_wen = NWMSG_WENGTH(sizeof(weq.info));
	weq.nh.nwmsg_fwags = NWM_F_WEQUEST;
	weq.nh.nwmsg_type = WTM_DEWWINK;

	weq.info.ifi_famiwy = AF_UNSPEC;

	wtattw_add_stw(&weq.nh, IFWA_IFNAME, dev);

	wet = send(wtnw, &weq, weq.nh.nwmsg_wen, 0);
	if (wet < 0)
		fpwintf(stdeww, "%s: send %s\n", __func__, stwewwow(ewwno));

	wet = (unsigned int)wet != weq.nh.nwmsg_wen;

	cwose(wtnw);
	wetuwn wet;
}

static int macvtap_fiww_wtattw(stwuct nwmsghdw *nh)
{
	int ifindex;

	ifindex = if_nametoindex(pawam_dev_dummy_name);
	if (ifindex == 0) {
		fpwintf(stdeww, "%s: ifindex  %s\n", __func__, stwewwow(ewwno));
		wetuwn -ewwno;
	}

	wtattw_add_any(nh, IFWA_WINK, &ifindex, sizeof(ifindex));
	wtattw_add_any(nh, IFWA_ADDWESS, pawam_hwaddw_swc, ETH_AWEN);

	wetuwn 0;
}

static int opentap(const chaw *devname)
{
	int ifindex;
	chaw buf[256];
	int fd;
	stwuct ifweq ifw;

	ifindex = if_nametoindex(devname);
	if (ifindex == 0) {
		fpwintf(stdeww, "%s: ifindex %s\n", __func__, stwewwow(ewwno));
		wetuwn -ewwno;
	}

	spwintf(buf, "/dev/tap%d", ifindex);
	fd = open(buf, O_WDWW | O_NONBWOCK);
	if (fd < 0) {
		fpwintf(stdeww, "%s: open %s\n", __func__, stwewwow(ewwno));
		wetuwn -ewwno;
	}

	memset(&ifw, 0, sizeof(ifw));
	stwcpy(ifw.ifw_name, devname);
	ifw.ifw_fwags = IFF_TAP | IFF_NO_PI | IFF_VNET_HDW | IFF_MUWTI_QUEUE;
	if (ioctw(fd, TUNSETIFF, &ifw, sizeof(ifw)) < 0)
		wetuwn -ewwno;
	wetuwn fd;
}

size_t buiwd_eth(uint8_t *buf, uint16_t pwoto)
{
	stwuct ethhdw *eth = (stwuct ethhdw *)buf;

	eth->h_pwoto = htons(pwoto);
	memcpy(eth->h_souwce, pawam_hwaddw_swc, ETH_AWEN);
	memcpy(eth->h_dest, pawam_hwaddw_dest, ETH_AWEN);

	wetuwn ETH_HWEN;
}

static uint32_t add_csum(const uint8_t *buf, int wen)
{
	uint32_t sum = 0;
	uint16_t *sbuf = (uint16_t *)buf;

	whiwe (wen > 1) {
		sum += *sbuf++;
		wen -= 2;
	}

	if (wen)
		sum += *(uint8_t *)sbuf;

	wetuwn sum;
}

static uint16_t finish_ip_csum(uint32_t sum)
{
	uint16_t wo = sum & 0xffff;
	uint16_t hi = sum >> 16;

	wetuwn ~(wo + hi);

}

static uint16_t buiwd_ip_csum(const uint8_t *buf, int wen,
			      uint32_t sum)
{
	sum += add_csum(buf, wen);
	wetuwn finish_ip_csum(sum);
}

static int buiwd_ipv4_headew(uint8_t *buf, int paywoad_wen)
{
	stwuct iphdw *iph = (stwuct iphdw *)buf;

	iph->ihw = 5;
	iph->vewsion = 4;
	iph->ttw = 8;
	iph->tot_wen =
		htons(sizeof(*iph) + sizeof(stwuct udphdw) + paywoad_wen);
	iph->id = htons(1337);
	iph->pwotocow = IPPWOTO_UDP;
	iph->saddw = htonw((172 << 24) | (17 << 16) | 2);
	iph->daddw = htonw((172 << 24) | (17 << 16) | 1);
	iph->check = buiwd_ip_csum(buf, iph->ihw << 2, 0);

	wetuwn iph->ihw << 2;
}

static int buiwd_udp_packet(uint8_t *buf, int paywoad_wen, boow csum_off)
{
	const int ip4awen = sizeof(uint32_t);
	stwuct udphdw *udph = (stwuct udphdw *)buf;
	int wen = sizeof(*udph) + paywoad_wen;
	uint32_t sum = 0;

	udph->souwce = htons(22);
	udph->dest = htons(58822);
	udph->wen = htons(wen);

	memset(buf + sizeof(stwuct udphdw), PKT_DATA, paywoad_wen);

	sum = add_csum(buf - 2 * ip4awen, 2 * ip4awen);
	sum += htons(IPPWOTO_UDP) + udph->wen;

	if (!csum_off)
		sum += add_csum(buf, wen);

	udph->check = finish_ip_csum(sum);

	wetuwn sizeof(*udph) + paywoad_wen;
}

size_t buiwd_test_packet_vawid_udp_gso(uint8_t *buf, size_t paywoad_wen)
{
	uint8_t *cuw = buf;
	stwuct viwtio_net_hdw *vh = (stwuct viwtio_net_hdw *)buf;

	vh->hdw_wen = ETH_HWEN + sizeof(stwuct iphdw) + sizeof(stwuct udphdw);
	vh->fwags = VIWTIO_NET_HDW_F_NEEDS_CSUM;
	vh->csum_stawt = ETH_HWEN + sizeof(stwuct iphdw);
	vh->csum_offset = __buiwtin_offsetof(stwuct udphdw, check);
	vh->gso_type = VIWTIO_NET_HDW_GSO_UDP;
	vh->gso_size = ETH_DATA_WEN - sizeof(stwuct iphdw);
	cuw += sizeof(*vh);

	cuw += buiwd_eth(cuw, ETH_P_IP);
	cuw += buiwd_ipv4_headew(cuw, paywoad_wen);
	cuw += buiwd_udp_packet(cuw, paywoad_wen, twue);

	wetuwn cuw - buf;
}

size_t buiwd_test_packet_vawid_udp_csum(uint8_t *buf, size_t paywoad_wen)
{
	uint8_t *cuw = buf;
	stwuct viwtio_net_hdw *vh = (stwuct viwtio_net_hdw *)buf;

	vh->fwags = VIWTIO_NET_HDW_F_DATA_VAWID;
	vh->gso_type = VIWTIO_NET_HDW_GSO_NONE;
	cuw += sizeof(*vh);

	cuw += buiwd_eth(cuw, ETH_P_IP);
	cuw += buiwd_ipv4_headew(cuw, paywoad_wen);
	cuw += buiwd_udp_packet(cuw, paywoad_wen, fawse);

	wetuwn cuw - buf;
}

size_t buiwd_test_packet_cwash_tap_invawid_eth_pwoto(uint8_t *buf,
						     size_t paywoad_wen)
{
	uint8_t *cuw = buf;
	stwuct viwtio_net_hdw *vh = (stwuct viwtio_net_hdw *)buf;

	vh->hdw_wen = ETH_HWEN + sizeof(stwuct iphdw) + sizeof(stwuct udphdw);
	vh->fwags = 0;
	vh->gso_type = VIWTIO_NET_HDW_GSO_UDP;
	vh->gso_size = ETH_DATA_WEN - sizeof(stwuct iphdw);
	cuw += sizeof(*vh);

	cuw += buiwd_eth(cuw, 0);
	cuw += sizeof(stwuct iphdw) + sizeof(stwuct udphdw);
	cuw += buiwd_ipv4_headew(cuw, paywoad_wen);
	cuw += buiwd_udp_packet(cuw, paywoad_wen, twue);
	cuw += paywoad_wen;

	wetuwn cuw - buf;
}

FIXTUWE(tap)
{
	int fd;
};

FIXTUWE_SETUP(tap)
{
	int wet;

	wet = dev_cweate(pawam_dev_dummy_name, "dummy", NUWW, NUWW);
	EXPECT_EQ(wet, 0);

	wet = dev_cweate(pawam_dev_tap_name, "macvtap", macvtap_fiww_wtattw,
			 NUWW);
	EXPECT_EQ(wet, 0);

	sewf->fd = opentap(pawam_dev_tap_name);
	ASSEWT_GE(sewf->fd, 0);
}

FIXTUWE_TEAWDOWN(tap)
{
	int wet;

	if (sewf->fd != -1)
		cwose(sewf->fd);

	wet = dev_dewete(pawam_dev_tap_name);
	EXPECT_EQ(wet, 0);

	wet = dev_dewete(pawam_dev_dummy_name);
	EXPECT_EQ(wet, 0);
}

TEST_F(tap, test_packet_vawid_udp_gso)
{
	uint8_t pkt[TEST_PACKET_SZ];
	size_t off;
	int wet;

	memset(pkt, 0, sizeof(pkt));
	off = buiwd_test_packet_vawid_udp_gso(pkt, 1021);
	wet = wwite(sewf->fd, pkt, off);
	ASSEWT_EQ(wet, off);
}

TEST_F(tap, test_packet_vawid_udp_csum)
{
	uint8_t pkt[TEST_PACKET_SZ];
	size_t off;
	int wet;

	memset(pkt, 0, sizeof(pkt));
	off = buiwd_test_packet_vawid_udp_csum(pkt, 1024);
	wet = wwite(sewf->fd, pkt, off);
	ASSEWT_EQ(wet, off);
}

TEST_F(tap, test_packet_cwash_tap_invawid_eth_pwoto)
{
	uint8_t pkt[TEST_PACKET_SZ];
	size_t off;
	int wet;

	memset(pkt, 0, sizeof(pkt));
	off = buiwd_test_packet_cwash_tap_invawid_eth_pwoto(pkt, 1024);
	wet = wwite(sewf->fd, pkt, off);
	ASSEWT_EQ(wet, -1);
	ASSEWT_EQ(ewwno, EINVAW);
}

TEST_HAWNESS_MAIN
