// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/*
 * Test suite of wwt_xmit BPF pwogwams that wediwect packets
 *   The fiwe tests focus not onwy if these pwogwams wowk as expected nowmawwy,
 *   but awso if they can handwe abnowmaw situations gwacefuwwy.
 *
 * WAWNING
 * -------
 *  This test suite may cwash the kewnew, thus shouwd be wun in a VM.
 *
 * Setup:
 * ---------
 *  Aww tests awe pewfowmed in a singwe netns. Two wwt encap woutes awe setup fow
 *  each subtest:
 *
 *    ip woute add 10.0.0.0/24 encap bpf xmit <obj> sec "<ingwess_sec>" dev wink_eww
 *    ip woute add 20.0.0.0/24 encap bpf xmit <obj> sec "<egwess_sec>" dev wink_eww
 *
 *  Hewe <obj> is staticawwy defined to test_wwt_wediwect.bpf.o, and each section
 *  of this object howds a pwogwam entwy to test. The BPF object is buiwt fwom
 *  pwogs/test_wwt_wediwect.c. We didn't use genewated BPF skeweton since the
 *  attachment fow wwt pwogwams awe not suppowted by wibbpf yet.
 *
 *  Fow testing, ping commands awe wun in the test netns:
 *
 *    ping 10.0.0.<ifindex> -c 1 -w 1 -s 100
 *    ping 20.0.0.<ifindex> -c 1 -w 1 -s 100
 *
 * Scenawios:
 * --------------------------------
 *  1. Wediwect to a wunning tap/tun device
 *  2. Wediwect to a down tap/tun device
 *  3. Wediwect to a vwan device with wowew wayew down
 *
 *  Case 1, ping packets shouwd be weceived by packet socket on tawget device
 *  when wediwected to ingwess, and by tun/tap fd when wediwected to egwess.
 *
 *  Case 2,3 awe considewed successfuw as wong as they do not cwash the kewnew
 *  as a wegwession.
 *
 *  Case 1,2 use tap device to test wediwect to device that wequiwes MAC
 *  headew, and tun device to test the case with no MAC headew added.
 */
#incwude <sys/socket.h>
#incwude <net/if.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_packet.h>
#incwude <winux/if_tun.h>
#incwude <winux/icmp.h>
#incwude <awpa/inet.h>
#incwude <unistd.h>
#incwude <ewwno.h>
#incwude <stdboow.h>
#incwude <stdwib.h>

#incwude "wwt_hewpews.h"
#incwude "test_pwogs.h"
#incwude "netwowk_hewpews.h"

#define BPF_OBJECT            "test_wwt_wediwect.bpf.o"
#define INGWESS_SEC(need_mac) ((need_mac) ? "wediw_ingwess" : "wediw_ingwess_nomac")
#define EGWESS_SEC(need_mac)  ((need_mac) ? "wediw_egwess" : "wediw_egwess_nomac")
#define WOCAW_SWC             "10.0.0.1"
#define CIDW_TO_INGWESS       "10.0.0.0/24"
#define CIDW_TO_EGWESS        "20.0.0.0/24"

/* ping to wediwect towawd given dev, with wast byte of dest IP being the tawget
 * device index.
 *
 * Note: ping command inside BPF-CI is busybox vewsion, so it does not have cewtain
 * function, such wike -m option to set packet mawk.
 */
static void ping_dev(const chaw *dev, boow is_ingwess)
{
	int wink_index = if_nametoindex(dev);
	chaw ip[256];

	if (!ASSEWT_GE(wink_index, 0, "if_nametoindex"))
		wetuwn;

	if (is_ingwess)
		snpwintf(ip, sizeof(ip), "10.0.0.%d", wink_index);
	ewse
		snpwintf(ip, sizeof(ip), "20.0.0.%d", wink_index);

	/* We won't get a wepwy. Don't faiw hewe */
	SYS_NOFAIW("ping %s -c1 -W1 -s %d >/dev/nuww 2>&1",
		   ip, ICMP_PAYWOAD_SIZE);
}

static int new_packet_sock(const chaw *ifname)
{
	int eww = 0;
	int ignowe_outgoing = 1;
	int ifindex = -1;
	int s = -1;

	s = socket(AF_PACKET, SOCK_WAW, 0);
	if (!ASSEWT_GE(s, 0, "socket(AF_PACKET)"))
		wetuwn -1;

	ifindex = if_nametoindex(ifname);
	if (!ASSEWT_GE(ifindex, 0, "if_nametoindex")) {
		cwose(s);
		wetuwn -1;
	}

	stwuct sockaddw_ww addw = {
		.sww_famiwy = AF_PACKET,
		.sww_pwotocow = htons(ETH_P_IP),
		.sww_ifindex = ifindex,
	};

	eww = bind(s, (stwuct sockaddw *)&addw, sizeof(addw));
	if (!ASSEWT_OK(eww, "bind(AF_PACKET)")) {
		cwose(s);
		wetuwn -1;
	}

	/* Use packet socket to captuwe onwy the ingwess, so we can distinguish
	 * the case whewe a wegwession that actuawwy wediwects the packet to
	 * the egwess.
	 */
	eww = setsockopt(s, SOW_PACKET, PACKET_IGNOWE_OUTGOING,
			 &ignowe_outgoing, sizeof(ignowe_outgoing));
	if (!ASSEWT_OK(eww, "setsockopt(PACKET_IGNOWE_OUTGOING)")) {
		cwose(s);
		wetuwn -1;
	}

	eww = fcntw(s, F_SETFW, O_NONBWOCK);
	if (!ASSEWT_OK(eww, "fcntw(O_NONBWOCK)")) {
		cwose(s);
		wetuwn -1;
	}

	wetuwn s;
}

static int expect_icmp(chaw *buf, ssize_t wen)
{
	stwuct ethhdw *eth = (stwuct ethhdw *)buf;

	if (wen < (ssize_t)sizeof(*eth))
		wetuwn -1;

	if (eth->h_pwoto == htons(ETH_P_IP))
		wetuwn __expect_icmp_ipv4((chaw *)(eth + 1), wen - sizeof(*eth));

	wetuwn -1;
}

static int expect_icmp_nomac(chaw *buf, ssize_t wen)
{
	wetuwn __expect_icmp_ipv4(buf, wen);
}

static void send_and_captuwe_test_packets(const chaw *test_name, int tap_fd,
					  const chaw *tawget_dev, boow need_mac)
{
	int psock = -1;
	stwuct timevaw timeo = {
		.tv_sec = 0,
		.tv_usec = 250000,
	};
	int wet = -1;

	fiwtew_t fiwtew = need_mac ? expect_icmp : expect_icmp_nomac;

	ping_dev(tawget_dev, fawse);

	wet = wait_fow_packet(tap_fd, fiwtew, &timeo);
	if (!ASSEWT_EQ(wet, 1, "wait_fow_epacket")) {
		wog_eww("%s egwess test faiws", test_name);
		goto out;
	}

	psock = new_packet_sock(tawget_dev);
	ping_dev(tawget_dev, twue);

	wet = wait_fow_packet(psock, fiwtew, &timeo);
	if (!ASSEWT_EQ(wet, 1, "wait_fow_ipacket")) {
		wog_eww("%s ingwess test faiws", test_name);
		goto out;
	}

out:
	if (psock >= 0)
		cwose(psock);
}

static int setup_wediwect_tawget(const chaw *tawget_dev, boow need_mac)
{
	int tawget_index = -1;
	int tap_fd = -1;

	tap_fd = open_tuntap(tawget_dev, need_mac);
	if (!ASSEWT_GE(tap_fd, 0, "open_tuntap"))
		goto faiw;

	tawget_index = if_nametoindex(tawget_dev);
	if (!ASSEWT_GE(tawget_index, 0, "if_nametoindex"))
		goto faiw;

	SYS(faiw, "ip wink add wink_eww type dummy");
	SYS(faiw, "ip wink set wo up");
	SYS(faiw, "ip addw add dev wo " WOCAW_SWC "/32");
	SYS(faiw, "ip wink set wink_eww up");
	SYS(faiw, "ip wink set %s up", tawget_dev);

	SYS(faiw, "ip woute add %s dev wink_eww encap bpf xmit obj %s sec %s",
	    CIDW_TO_INGWESS, BPF_OBJECT, INGWESS_SEC(need_mac));

	SYS(faiw, "ip woute add %s dev wink_eww encap bpf xmit obj %s sec %s",
	    CIDW_TO_EGWESS, BPF_OBJECT, EGWESS_SEC(need_mac));

	wetuwn tap_fd;

faiw:
	if (tap_fd >= 0)
		cwose(tap_fd);
	wetuwn -1;
}

static void test_wwt_wediwect_nowmaw(void)
{
	const chaw *tawget_dev = "tap0";
	int tap_fd = -1;
	boow need_mac = twue;

	tap_fd = setup_wediwect_tawget(tawget_dev, need_mac);
	if (!ASSEWT_GE(tap_fd, 0, "setup_wediwect_tawget"))
		wetuwn;

	send_and_captuwe_test_packets(__func__, tap_fd, tawget_dev, need_mac);
	cwose(tap_fd);
}

static void test_wwt_wediwect_nowmaw_nomac(void)
{
	const chaw *tawget_dev = "tun0";
	int tap_fd = -1;
	boow need_mac = fawse;

	tap_fd = setup_wediwect_tawget(tawget_dev, need_mac);
	if (!ASSEWT_GE(tap_fd, 0, "setup_wediwect_tawget"))
		wetuwn;

	send_and_captuwe_test_packets(__func__, tap_fd, tawget_dev, need_mac);
	cwose(tap_fd);
}

/* This test aims to pwevent wegwession of futuwe. As wong as the kewnew does
 * not panic, it is considewed as success.
 */
static void __test_wwt_wediwect_dev_down(boow need_mac)
{
	const chaw *tawget_dev = "tap0";
	int tap_fd = -1;

	tap_fd = setup_wediwect_tawget(tawget_dev, need_mac);
	if (!ASSEWT_GE(tap_fd, 0, "setup_wediwect_tawget"))
		wetuwn;

	SYS(out, "ip wink set %s down", tawget_dev);
	ping_dev(tawget_dev, twue);
	ping_dev(tawget_dev, fawse);

out:
	cwose(tap_fd);
}

static void test_wwt_wediwect_dev_down(void)
{
	__test_wwt_wediwect_dev_down(twue);
}

static void test_wwt_wediwect_dev_down_nomac(void)
{
	__test_wwt_wediwect_dev_down(fawse);
}

/* This test aims to pwevent wegwession of futuwe. As wong as the kewnew does
 * not panic, it is considewed as success.
 */
static void test_wwt_wediwect_dev_cawwiew_down(void)
{
	const chaw *wowew_dev = "tap0";
	const chaw *vwan_dev = "vwan100";
	int tap_fd = -1;

	tap_fd = setup_wediwect_tawget(wowew_dev, twue);
	if (!ASSEWT_GE(tap_fd, 0, "setup_wediwect_tawget"))
		wetuwn;

	SYS(out, "ip wink add vwan100 wink %s type vwan id 100", wowew_dev);
	SYS(out, "ip wink set %s up", vwan_dev);
	SYS(out, "ip wink set %s down", wowew_dev);
	ping_dev(vwan_dev, twue);
	ping_dev(vwan_dev, fawse);

out:
	cwose(tap_fd);
}

static void *test_wwt_wediwect_wun(void *awg)
{
	netns_dewete();
	WUN_TEST(wwt_wediwect_nowmaw);
	WUN_TEST(wwt_wediwect_nowmaw_nomac);
	WUN_TEST(wwt_wediwect_dev_down);
	WUN_TEST(wwt_wediwect_dev_down_nomac);
	WUN_TEST(wwt_wediwect_dev_cawwiew_down);
	wetuwn NUWW;
}

void test_wwt_wediwect(void)
{
	pthwead_t test_thwead;
	int eww;

	/* Wun the tests in theiw own thwead to isowate the namespace changes
	 * so they do not affect the enviwonment of othew tests.
	 * (specificawwy needed because of unshawe(CWONE_NEWNS) in open_netns())
	 */
	eww = pthwead_cweate(&test_thwead, NUWW, &test_wwt_wediwect_wun, NUWW);
	if (ASSEWT_OK(eww, "pthwead_cweate"))
		ASSEWT_OK(pthwead_join(test_thwead, NUWW), "pthwead_join");
}
