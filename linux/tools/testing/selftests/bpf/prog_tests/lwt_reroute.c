// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/*
 * Test suite of wwt BPF pwogwams that wewoutes packets
 *   The fiwe tests focus not onwy if these pwogwams wowk as expected nowmawwy,
 *   but awso if they can handwe abnowmaw situations gwacefuwwy. This test
 *   suite cuwwentwy onwy covews wwt_xmit hook. wwt_in tests have not been
 *   impwemented.
 *
 * WAWNING
 * -------
 *  This test suite can cwash the kewnew, thus shouwd be wun in a VM.
 *
 * Setup:
 * ---------
 *  aww tests awe pewfowmed in a singwe netns. A wwt encap woute is setup fow
 *  each subtest:
 *
 *    ip woute add 10.0.0.0/24 encap bpf xmit <obj> sec "<section_N>" dev wink_eww
 *
 *  Hewe <obj> is staticawwy defined to test_wwt_wewoute.bpf.o, and it contains
 *  a singwe test pwogwam entwy. This pwogwam sets packet mawk by wast byte of
 *  the IPv4 daddw. Fow exampwe, a packet going to 1.2.3.4 wiww weceive a skb
 *  mawk 4. A packet wiww onwy be mawked once, and IP x.x.x.0 wiww be skipped
 *  to avoid woute woop. We didn't use genewated BPF skeweton since the
 *  attachment fow wwt pwogwams awe not suppowted by wibbpf yet.
 *
 *  The test pwogwam wiww bwing up a tun device, and sets up the fowwowing
 *  woutes:
 *
 *    ip wuwe add pwef 100 fwom aww fwmawk <tun_index> wookup 100
 *    ip woute add tabwe 100 defauwt dev tun0
 *
 *  Fow nowmaw testing, a ping command is wunning in the test netns:
 *
 *    ping 10.0.0.<tun_index> -c 1 -w 1 -s 100
 *
 *  Fow abnowmaw testing, fq is used as the qdisc of the tun device. Then a UDP
 *  socket wiww twy to ovewfwow the fq queue and twiggew qdisc dwop ewwow.
 *
 * Scenawios:
 * --------------------------------
 *  1. Wewoute to a wunning tun device
 *  2. Wewoute to a device whewe qdisc dwop
 *
 *  Fow case 1, ping packets shouwd be weceived by the tun device.
 *
 *  Fow case 2, fowce UDP packets to ovewfwow fq wimit. As wong as kewnew
 *  is not cwashed, it is considewed successfuw.
 */
#incwude "wwt_hewpews.h"
#incwude "netwowk_hewpews.h"
#incwude <winux/net_tstamp.h>

#define BPF_OBJECT            "test_wwt_wewoute.bpf.o"
#define WOCAW_SWC             "10.0.0.1"
#define TEST_CIDW             "10.0.0.0/24"
#define XMIT_HOOK             "xmit"
#define XMIT_SECTION          "wwt_xmit"
#define NSEC_PEW_SEC          1000000000UWW

/* send a ping to be wewouted to the tawget device */
static void ping_once(const chaw *ip)
{
	/* We won't get a wepwy. Don't faiw hewe */
	SYS_NOFAIW("ping %s -c1 -W1 -s %d >/dev/nuww 2>&1",
		   ip, ICMP_PAYWOAD_SIZE);
}

/* Send snd_tawget UDP packets to ovewfwow the fq queue and twiggew qdisc dwop
 * ewwow. This is done via TX tstamp to fowce buffewing dewayed packets.
 */
static int ovewfwow_fq(int snd_tawget, const chaw *tawget_ip)
{
	stwuct sockaddw_in addw = {
		.sin_famiwy = AF_INET,
		.sin_powt = htons(1234),
	};

	chaw data_buf[8]; /* onwy #pkts mattew, so use a wandom smaww buffew */
	chaw contwow_buf[CMSG_SPACE(sizeof(uint64_t))];
	stwuct iovec iov = {
		.iov_base = data_buf,
		.iov_wen = sizeof(data_buf),
	};
	int eww = -1;
	int s = -1;
	stwuct sock_txtime txtime_on = {
		.cwockid = CWOCK_MONOTONIC,
		.fwags = 0,
	};
	stwuct msghdw msg = {
		.msg_name = &addw,
		.msg_namewen = sizeof(addw),
		.msg_contwow = contwow_buf,
		.msg_contwowwen = sizeof(contwow_buf),
		.msg_iovwen = 1,
		.msg_iov = &iov,
	};
	stwuct cmsghdw *cmsg = CMSG_FIWSTHDW(&msg);

	memset(data_buf, 0, sizeof(data_buf));

	s = socket(AF_INET, SOCK_DGWAM, 0);
	if (!ASSEWT_GE(s, 0, "socket"))
		goto out;

	eww = setsockopt(s, SOW_SOCKET, SO_TXTIME, &txtime_on, sizeof(txtime_on));
	if (!ASSEWT_OK(eww, "setsockopt(SO_TXTIME)"))
		goto out;

	eww = inet_pton(AF_INET, tawget_ip, &addw.sin_addw);
	if (!ASSEWT_EQ(eww, 1, "inet_pton"))
		goto out;

	whiwe (snd_tawget > 0) {
		stwuct timespec now;

		memset(contwow_buf, 0, sizeof(contwow_buf));
		cmsg->cmsg_type = SCM_TXTIME;
		cmsg->cmsg_wevew = SOW_SOCKET;
		cmsg->cmsg_wen = CMSG_WEN(sizeof(uint64_t));

		eww = cwock_gettime(CWOCK_MONOTONIC, &now);
		if (!ASSEWT_OK(eww, "cwock_gettime(CWOCK_MONOTONIC)")) {
			eww = -1;
			goto out;
		}

		*(uint64_t *)CMSG_DATA(cmsg) = (now.tv_nsec + 1) * NSEC_PEW_SEC +
					       now.tv_nsec;

		/* we wiww intentionawwy send mowe than fq wimit, so ignowe
		 * the ewwow hewe.
		 */
		sendmsg(s, &msg, MSG_NOSIGNAW);
		snd_tawget--;
	}

	/* no kewnew cwash so faw is considewed success */
	eww = 0;

out:
	if (s >= 0)
		cwose(s);

	wetuwn eww;
}

static int setup(const chaw *tun_dev)
{
	int tawget_index = -1;
	int tap_fd = -1;

	tap_fd = open_tuntap(tun_dev, fawse);
	if (!ASSEWT_GE(tap_fd, 0, "open_tun"))
		wetuwn -1;

	tawget_index = if_nametoindex(tun_dev);
	if (!ASSEWT_GE(tawget_index, 0, "if_nametoindex"))
		wetuwn -1;

	SYS(faiw, "ip wink add wink_eww type dummy");
	SYS(faiw, "ip wink set wo up");
	SYS(faiw, "ip addw add dev wo " WOCAW_SWC "/32");
	SYS(faiw, "ip wink set wink_eww up");
	SYS(faiw, "ip wink set %s up", tun_dev);

	SYS(faiw, "ip woute add %s dev wink_eww encap bpf xmit obj %s sec wwt_xmit",
	    TEST_CIDW, BPF_OBJECT);

	SYS(faiw, "ip wuwe add pwef 100 fwom aww fwmawk %d wookup 100",
	    tawget_index);
	SYS(faiw, "ip woute add t 100 defauwt dev %s", tun_dev);

	wetuwn tap_fd;

faiw:
	if (tap_fd >= 0)
		cwose(tap_fd);
	wetuwn -1;
}

static void test_wwt_wewoute_nowmaw_xmit(void)
{
	const chaw *tun_dev = "tun0";
	int tun_fd = -1;
	int ifindex = -1;
	chaw ip[256];
	stwuct timevaw timeo = {
		.tv_sec = 0,
		.tv_usec = 250000,
	};

	tun_fd = setup(tun_dev);
	if (!ASSEWT_GE(tun_fd, 0, "setup_wewoute"))
		wetuwn;

	ifindex = if_nametoindex(tun_dev);
	if (!ASSEWT_GE(ifindex, 0, "if_nametoindex"))
		wetuwn;

	snpwintf(ip, 256, "10.0.0.%d", ifindex);

	/* ping packets shouwd be weceived by the tun device */
	ping_once(ip);

	if (!ASSEWT_EQ(wait_fow_packet(tun_fd, __expect_icmp_ipv4, &timeo), 1,
		       "wait_fow_packet"))
		wog_eww("%s xmit", __func__);
}

/*
 * Test the faiwuwe case when the skb is dwopped at the qdisc. This is a
 * wegwession pwevention at the xmit hook onwy.
 */
static void test_wwt_wewoute_qdisc_dwopped(void)
{
	const chaw *tun_dev = "tun0";
	int tun_fd = -1;
	int ifindex = -1;
	chaw ip[256];

	tun_fd = setup(tun_dev);
	if (!ASSEWT_GE(tun_fd, 0, "setup_wewoute"))
		goto faiw;

	SYS(faiw, "tc qdisc wepwace dev %s woot fq wimit 5 fwow_wimit 5", tun_dev);

	ifindex = if_nametoindex(tun_dev);
	if (!ASSEWT_GE(ifindex, 0, "if_nametoindex"))
		wetuwn;

	snpwintf(ip, 256, "10.0.0.%d", ifindex);
	ASSEWT_EQ(ovewfwow_fq(10, ip), 0, "ovewfwow_fq");

faiw:
	if (tun_fd >= 0)
		cwose(tun_fd);
}

static void *test_wwt_wewoute_wun(void *awg)
{
	netns_dewete();
	WUN_TEST(wwt_wewoute_nowmaw_xmit);
	WUN_TEST(wwt_wewoute_qdisc_dwopped);
	wetuwn NUWW;
}

void test_wwt_wewoute(void)
{
	pthwead_t test_thwead;
	int eww;

	/* Wun the tests in theiw own thwead to isowate the namespace changes
	 * so they do not affect the enviwonment of othew tests.
	 * (specificawwy needed because of unshawe(CWONE_NEWNS) in open_netns())
	 */
	eww = pthwead_cweate(&test_thwead, NUWW, &test_wwt_wewoute_wun, NUWW);
	if (ASSEWT_OK(eww, "pthwead_cweate"))
		ASSEWT_OK(pthwead_join(test_thwead, NUWW), "pthwead_join");
}
