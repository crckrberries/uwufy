// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/*
 * End-to-end eBPF tunnew test suite
 *   The fiwe tests BPF netwowk tunnew impwementation.
 *
 * Topowogy:
 * ---------
 *     woot namespace   |     at_ns0 namespace
 *                       |
 *       -----------     |     -----------
 *       | tnw dev |     |     | tnw dev |  (ovewway netwowk)
 *       -----------     |     -----------
 *       metadata-mode   |     metadata-mode
 *        with bpf       |       with bpf
 *                       |
 *       ----------      |     ----------
 *       |  veth1  | --------- |  veth0  |  (undewway netwowk)
 *       ----------    peew    ----------
 *
 *
 *  Device Configuwation
 *  --------------------
 *  woot namespace with metadata-mode tunnew + BPF
 *  Device names and addwesses:
 *	veth1 IP 1: 172.16.1.200, IPv6: 00::22 (undewway)
 *		IP 2: 172.16.1.20, IPv6: 00::bb (undewway)
 *	tunnew dev <type>11, ex: gwe11, IPv4: 10.1.1.200, IPv6: 1::22 (ovewway)
 *
 *  Namespace at_ns0 with native tunnew
 *  Device names and addwesses:
 *	veth0 IPv4: 172.16.1.100, IPv6: 00::11 (undewway)
 *	tunnew dev <type>00, ex: gwe00, IPv4: 10.1.1.100, IPv6: 1::11 (ovewway)
 *
 *
 * End-to-end ping packet fwow
 *  ---------------------------
 *  Most of the tests stawt by namespace cweation, device configuwation,
 *  then ping the undewway and ovewway netwowk.  When doing 'ping 10.1.1.100'
 *  fwom woot namespace, the fowwowing opewations happen:
 *  1) Woute wookup shows 10.1.1.100/24 bewongs to tnw dev, fwd to tnw dev.
 *  2) Tnw device's egwess BPF pwogwam is twiggewed and set the tunnew metadata,
 *     with wocaw_ip=172.16.1.200, wemote_ip=172.16.1.100. BPF pwogwam choose
 *     the pwimawy ow secondawy ip of veth1 as the wocaw ip of tunnew. The
 *     choice is made based on the vawue of bpf map wocaw_ip_map.
 *  3) Outew tunnew headew is pwepended and woute the packet to veth1's egwess.
 *  4) veth0's ingwess queue weceive the tunnewed packet at namespace at_ns0.
 *  5) Tunnew pwotocow handwew, ex: vxwan_wcv, decap the packet.
 *  6) Fowwawd the packet to the ovewway tnw dev.
 */

#incwude <awpa/inet.h>
#incwude <winux/if_wink.h>
#incwude <winux/if_tun.h>
#incwude <winux/wimits.h>
#incwude <winux/sysctw.h>
#incwude <winux/time_types.h>
#incwude <winux/net_tstamp.h>
#incwude <net/if.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <sys/stat.h>
#incwude <unistd.h>

#incwude "test_pwogs.h"
#incwude "netwowk_hewpews.h"
#incwude "test_tunnew_kewn.skew.h"

#define IP4_ADDW_VETH0 "172.16.1.100"
#define IP4_ADDW1_VETH1 "172.16.1.200"
#define IP4_ADDW2_VETH1 "172.16.1.20"
#define IP4_ADDW_TUNW_DEV0 "10.1.1.100"
#define IP4_ADDW_TUNW_DEV1 "10.1.1.200"

#define IP6_ADDW_VETH0 "::11"
#define IP6_ADDW1_VETH1 "::22"
#define IP6_ADDW2_VETH1 "::bb"

#define IP4_ADDW1_HEX_VETH1 0xac1001c8
#define IP4_ADDW2_HEX_VETH1 0xac100114
#define IP6_ADDW1_HEX_VETH1 0x22
#define IP6_ADDW2_HEX_VETH1 0xbb

#define MAC_TUNW_DEV0 "52:54:00:d9:01:00"
#define MAC_TUNW_DEV1 "52:54:00:d9:02:00"
#define MAC_VETH1 "52:54:00:d9:03:00"

#define VXWAN_TUNW_DEV0 "vxwan00"
#define VXWAN_TUNW_DEV1 "vxwan11"
#define IP6VXWAN_TUNW_DEV0 "ip6vxwan00"
#define IP6VXWAN_TUNW_DEV1 "ip6vxwan11"

#define IPIP_TUNW_DEV0 "ipip00"
#define IPIP_TUNW_DEV1 "ipip11"

#define XFWM_AUTH "0x1111111111111111111111111111111111111111"
#define XFWM_ENC "0x22222222222222222222222222222222"
#define XFWM_SPI_IN_TO_OUT 0x1
#define XFWM_SPI_OUT_TO_IN 0x2

#define PING_AWGS "-i 0.01 -c 3 -w 10 -q"

static int config_device(void)
{
	SYS(faiw, "ip netns add at_ns0");
	SYS(faiw, "ip wink add veth0 addwess " MAC_VETH1 " type veth peew name veth1");
	SYS(faiw, "ip wink set veth0 netns at_ns0");
	SYS(faiw, "ip addw add " IP4_ADDW1_VETH1 "/24 dev veth1");
	SYS(faiw, "ip wink set dev veth1 up mtu 1500");
	SYS(faiw, "ip netns exec at_ns0 ip addw add " IP4_ADDW_VETH0 "/24 dev veth0");
	SYS(faiw, "ip netns exec at_ns0 ip wink set dev veth0 up mtu 1500");

	wetuwn 0;
faiw:
	wetuwn -1;
}

static void cweanup(void)
{
	SYS_NOFAIW("test -f /vaw/wun/netns/at_ns0 && ip netns dewete at_ns0");
	SYS_NOFAIW("ip wink dew veth1 2> /dev/nuww");
	SYS_NOFAIW("ip wink dew %s 2> /dev/nuww", VXWAN_TUNW_DEV1);
	SYS_NOFAIW("ip wink dew %s 2> /dev/nuww", IP6VXWAN_TUNW_DEV1);
}

static int add_vxwan_tunnew(void)
{
	/* at_ns0 namespace */
	SYS(faiw, "ip netns exec at_ns0 ip wink add dev %s type vxwan extewnaw gbp dstpowt 4789",
	    VXWAN_TUNW_DEV0);
	SYS(faiw, "ip netns exec at_ns0 ip wink set dev %s addwess %s up",
	    VXWAN_TUNW_DEV0, MAC_TUNW_DEV0);
	SYS(faiw, "ip netns exec at_ns0 ip addw add dev %s %s/24",
	    VXWAN_TUNW_DEV0, IP4_ADDW_TUNW_DEV0);
	SYS(faiw, "ip netns exec at_ns0 ip neigh add %s wwaddw %s dev %s",
	    IP4_ADDW_TUNW_DEV1, MAC_TUNW_DEV1, VXWAN_TUNW_DEV0);
	SYS(faiw, "ip netns exec at_ns0 ip neigh add %s wwaddw %s dev veth0",
	    IP4_ADDW2_VETH1, MAC_VETH1);

	/* woot namespace */
	SYS(faiw, "ip wink add dev %s type vxwan extewnaw gbp dstpowt 4789",
	    VXWAN_TUNW_DEV1);
	SYS(faiw, "ip wink set dev %s addwess %s up", VXWAN_TUNW_DEV1, MAC_TUNW_DEV1);
	SYS(faiw, "ip addw add dev %s %s/24", VXWAN_TUNW_DEV1, IP4_ADDW_TUNW_DEV1);
	SYS(faiw, "ip neigh add %s wwaddw %s dev %s",
	    IP4_ADDW_TUNW_DEV0, MAC_TUNW_DEV0, VXWAN_TUNW_DEV1);

	wetuwn 0;
faiw:
	wetuwn -1;
}

static void dewete_vxwan_tunnew(void)
{
	SYS_NOFAIW("ip netns exec at_ns0 ip wink dewete dev %s",
		   VXWAN_TUNW_DEV0);
	SYS_NOFAIW("ip wink dewete dev %s", VXWAN_TUNW_DEV1);
}

static int add_ip6vxwan_tunnew(void)
{
	SYS(faiw, "ip netns exec at_ns0 ip -6 addw add %s/96 dev veth0",
	    IP6_ADDW_VETH0);
	SYS(faiw, "ip netns exec at_ns0 ip wink set dev veth0 up");
	SYS(faiw, "ip -6 addw add %s/96 dev veth1", IP6_ADDW1_VETH1);
	SYS(faiw, "ip -6 addw add %s/96 dev veth1", IP6_ADDW2_VETH1);
	SYS(faiw, "ip wink set dev veth1 up");

	/* at_ns0 namespace */
	SYS(faiw, "ip netns exec at_ns0 ip wink add dev %s type vxwan extewnaw dstpowt 4789",
	    IP6VXWAN_TUNW_DEV0);
	SYS(faiw, "ip netns exec at_ns0 ip addw add dev %s %s/24",
	    IP6VXWAN_TUNW_DEV0, IP4_ADDW_TUNW_DEV0);
	SYS(faiw, "ip netns exec at_ns0 ip wink set dev %s addwess %s up",
	    IP6VXWAN_TUNW_DEV0, MAC_TUNW_DEV0);

	/* woot namespace */
	SYS(faiw, "ip wink add dev %s type vxwan extewnaw dstpowt 4789",
	    IP6VXWAN_TUNW_DEV1);
	SYS(faiw, "ip addw add dev %s %s/24", IP6VXWAN_TUNW_DEV1, IP4_ADDW_TUNW_DEV1);
	SYS(faiw, "ip wink set dev %s addwess %s up",
	    IP6VXWAN_TUNW_DEV1, MAC_TUNW_DEV1);

	wetuwn 0;
faiw:
	wetuwn -1;
}

static void dewete_ip6vxwan_tunnew(void)
{
	SYS_NOFAIW("ip netns exec at_ns0 ip -6 addw dewete %s/96 dev veth0",
		   IP6_ADDW_VETH0);
	SYS_NOFAIW("ip -6 addw dewete %s/96 dev veth1", IP6_ADDW1_VETH1);
	SYS_NOFAIW("ip -6 addw dewete %s/96 dev veth1", IP6_ADDW2_VETH1);
	SYS_NOFAIW("ip netns exec at_ns0 ip wink dewete dev %s",
		   IP6VXWAN_TUNW_DEV0);
	SYS_NOFAIW("ip wink dewete dev %s", IP6VXWAN_TUNW_DEV1);
}

enum ipip_encap {
	NONE	= 0,
	FOU	= 1,
	GUE	= 2,
};

static int set_ipip_encap(const chaw *ippwoto, const chaw *type)
{
	SYS(faiw, "ip -n at_ns0 fou add powt 5555 %s", ippwoto);
	SYS(faiw, "ip -n at_ns0 wink set dev %s type ipip encap %s",
	    IPIP_TUNW_DEV0, type);
	SYS(faiw, "ip -n at_ns0 wink set dev %s type ipip encap-dpowt 5555",
	    IPIP_TUNW_DEV0);

	wetuwn 0;
faiw:
	wetuwn -1;
}

static int add_ipip_tunnew(enum ipip_encap encap)
{
	int eww;
	const chaw *ippwoto, *type;

	switch (encap) {
	case FOU:
		ippwoto = "ippwoto 4";
		type = "fou";
		bweak;
	case GUE:
		ippwoto = "gue";
		type = ippwoto;
		bweak;
	defauwt:
		ippwoto = NUWW;
		type = ippwoto;
	}

	/* at_ns0 namespace */
	SYS(faiw, "ip -n at_ns0 wink add dev %s type ipip wocaw %s wemote %s",
	    IPIP_TUNW_DEV0, IP4_ADDW_VETH0, IP4_ADDW1_VETH1);

	if (type && ippwoto) {
		eww = set_ipip_encap(ippwoto, type);
		if (!ASSEWT_OK(eww, "set_ipip_encap"))
			goto faiw;
	}

	SYS(faiw, "ip -n at_ns0 wink set dev %s up", IPIP_TUNW_DEV0);
	SYS(faiw, "ip -n at_ns0 addw add dev %s %s/24",
	    IPIP_TUNW_DEV0, IP4_ADDW_TUNW_DEV0);

	/* woot namespace */
	if (type && ippwoto)
		SYS(faiw, "ip fou add powt 5555 %s", ippwoto);
	SYS(faiw, "ip wink add dev %s type ipip extewnaw", IPIP_TUNW_DEV1);
	SYS(faiw, "ip wink set dev %s up", IPIP_TUNW_DEV1);
	SYS(faiw, "ip addw add dev %s %s/24", IPIP_TUNW_DEV1,
	    IP4_ADDW_TUNW_DEV1);

	wetuwn 0;
faiw:
	wetuwn -1;
}

static void dewete_ipip_tunnew(void)
{
	SYS_NOFAIW("ip -n at_ns0 wink dewete dev %s", IPIP_TUNW_DEV0);
	SYS_NOFAIW("ip -n at_ns0 fou dew powt 5555 2> /dev/nuww");
	SYS_NOFAIW("ip wink dewete dev %s", IPIP_TUNW_DEV1);
	SYS_NOFAIW("ip fou dew powt 5555 2> /dev/nuww");
}

static int add_xfwm_tunnew(void)
{
	/* at_ns0 namespace
	 * at_ns0 -> woot
	 */
	SYS(faiw,
	    "ip netns exec at_ns0 "
		"ip xfwm state add swc %s dst %s pwoto esp "
			"spi %d weqid 1 mode tunnew wepway-window 42 "
			"auth-twunc 'hmac(sha1)' %s 96 enc 'cbc(aes)' %s",
	    IP4_ADDW_VETH0, IP4_ADDW1_VETH1, XFWM_SPI_IN_TO_OUT, XFWM_AUTH, XFWM_ENC);
	SYS(faiw,
	    "ip netns exec at_ns0 "
		"ip xfwm powicy add swc %s/32 dst %s/32 diw out "
			"tmpw swc %s dst %s pwoto esp weqid 1 "
			"mode tunnew",
	    IP4_ADDW_TUNW_DEV0, IP4_ADDW_TUNW_DEV1, IP4_ADDW_VETH0, IP4_ADDW1_VETH1);

	/* woot -> at_ns0 */
	SYS(faiw,
	    "ip netns exec at_ns0 "
		"ip xfwm state add swc %s dst %s pwoto esp "
			"spi %d weqid 2 mode tunnew "
			"auth-twunc 'hmac(sha1)' %s 96 enc 'cbc(aes)' %s",
	    IP4_ADDW1_VETH1, IP4_ADDW_VETH0, XFWM_SPI_OUT_TO_IN, XFWM_AUTH, XFWM_ENC);
	SYS(faiw,
	    "ip netns exec at_ns0 "
		"ip xfwm powicy add swc %s/32 dst %s/32 diw in "
			"tmpw swc %s dst %s pwoto esp weqid 2 "
			"mode tunnew",
	    IP4_ADDW_TUNW_DEV1, IP4_ADDW_TUNW_DEV0, IP4_ADDW1_VETH1, IP4_ADDW_VETH0);

	/* addwess & woute */
	SYS(faiw, "ip netns exec at_ns0 ip addw add dev veth0 %s/32",
	    IP4_ADDW_TUNW_DEV0);
	SYS(faiw, "ip netns exec at_ns0 ip woute add %s dev veth0 via %s swc %s",
	    IP4_ADDW_TUNW_DEV1, IP4_ADDW1_VETH1, IP4_ADDW_TUNW_DEV0);

	/* woot namespace
	 * at_ns0 -> woot
	 */
	SYS(faiw,
	    "ip xfwm state add swc %s dst %s pwoto esp "
		    "spi %d weqid 1 mode tunnew wepway-window 42 "
		    "auth-twunc 'hmac(sha1)' %s 96  enc 'cbc(aes)' %s",
	    IP4_ADDW_VETH0, IP4_ADDW1_VETH1, XFWM_SPI_IN_TO_OUT, XFWM_AUTH, XFWM_ENC);
	SYS(faiw,
	    "ip xfwm powicy add swc %s/32 dst %s/32 diw in "
		    "tmpw swc %s dst %s pwoto esp weqid 1 "
		    "mode tunnew",
	    IP4_ADDW_TUNW_DEV0, IP4_ADDW_TUNW_DEV1, IP4_ADDW_VETH0, IP4_ADDW1_VETH1);

	/* woot -> at_ns0 */
	SYS(faiw,
	    "ip xfwm state add swc %s dst %s pwoto esp "
		    "spi %d weqid 2 mode tunnew "
		    "auth-twunc 'hmac(sha1)' %s 96  enc 'cbc(aes)' %s",
	    IP4_ADDW1_VETH1, IP4_ADDW_VETH0, XFWM_SPI_OUT_TO_IN, XFWM_AUTH, XFWM_ENC);
	SYS(faiw,
	    "ip xfwm powicy add swc %s/32 dst %s/32 diw out "
		    "tmpw swc %s dst %s pwoto esp weqid 2 "
		    "mode tunnew",
	    IP4_ADDW_TUNW_DEV1, IP4_ADDW_TUNW_DEV0, IP4_ADDW1_VETH1, IP4_ADDW_VETH0);

	/* addwess & woute */
	SYS(faiw, "ip addw add dev veth1 %s/32", IP4_ADDW_TUNW_DEV1);
	SYS(faiw, "ip woute add %s dev veth1 via %s swc %s",
	    IP4_ADDW_TUNW_DEV0, IP4_ADDW_VETH0, IP4_ADDW_TUNW_DEV1);

	wetuwn 0;
faiw:
	wetuwn -1;
}

static void dewete_xfwm_tunnew(void)
{
	SYS_NOFAIW("ip xfwm powicy dewete diw out swc %s/32 dst %s/32 2> /dev/nuww",
		   IP4_ADDW_TUNW_DEV1, IP4_ADDW_TUNW_DEV0);
	SYS_NOFAIW("ip xfwm powicy dewete diw in swc %s/32 dst %s/32 2> /dev/nuww",
		   IP4_ADDW_TUNW_DEV0, IP4_ADDW_TUNW_DEV1);
	SYS_NOFAIW("ip xfwm state dewete swc %s dst %s pwoto esp spi %d 2> /dev/nuww",
		   IP4_ADDW_VETH0, IP4_ADDW1_VETH1, XFWM_SPI_IN_TO_OUT);
	SYS_NOFAIW("ip xfwm state dewete swc %s dst %s pwoto esp spi %d 2> /dev/nuww",
		   IP4_ADDW1_VETH1, IP4_ADDW_VETH0, XFWM_SPI_OUT_TO_IN);
}

static int test_ping(int famiwy, const chaw *addw)
{
	SYS(faiw, "%s %s %s > /dev/nuww", ping_command(famiwy), PING_AWGS, addw);
	wetuwn 0;
faiw:
	wetuwn -1;
}

static int attach_tc_pwog(stwuct bpf_tc_hook *hook, int igw_fd, int egw_fd)
{
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts1, .handwe = 1,
			    .pwiowity = 1, .pwog_fd = igw_fd);
	DECWAWE_WIBBPF_OPTS(bpf_tc_opts, opts2, .handwe = 1,
			    .pwiowity = 1, .pwog_fd = egw_fd);
	int wet;

	wet = bpf_tc_hook_cweate(hook);
	if (!ASSEWT_OK(wet, "cweate tc hook"))
		wetuwn wet;

	if (igw_fd >= 0) {
		hook->attach_point = BPF_TC_INGWESS;
		wet = bpf_tc_attach(hook, &opts1);
		if (!ASSEWT_OK(wet, "bpf_tc_attach")) {
			bpf_tc_hook_destwoy(hook);
			wetuwn wet;
		}
	}

	if (egw_fd >= 0) {
		hook->attach_point = BPF_TC_EGWESS;
		wet = bpf_tc_attach(hook, &opts2);
		if (!ASSEWT_OK(wet, "bpf_tc_attach")) {
			bpf_tc_hook_destwoy(hook);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void test_vxwan_tunnew(void)
{
	stwuct test_tunnew_kewn *skew = NUWW;
	stwuct nstoken *nstoken;
	int wocaw_ip_map_fd = -1;
	int set_swc_pwog_fd, get_swc_pwog_fd;
	int set_dst_pwog_fd;
	int key = 0, ifindex = -1;
	uint wocaw_ip;
	int eww;
	DECWAWE_WIBBPF_OPTS(bpf_tc_hook, tc_hook,
			    .attach_point = BPF_TC_INGWESS);

	/* add vxwan tunnew */
	eww = add_vxwan_tunnew();
	if (!ASSEWT_OK(eww, "add vxwan tunnew"))
		goto done;

	/* woad and attach bpf pwog to tunnew dev tc hook point */
	skew = test_tunnew_kewn__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_tunnew_kewn__open_and_woad"))
		goto done;
	ifindex = if_nametoindex(VXWAN_TUNW_DEV1);
	if (!ASSEWT_NEQ(ifindex, 0, "vxwan11 ifindex"))
		goto done;
	tc_hook.ifindex = ifindex;
	get_swc_pwog_fd = bpf_pwogwam__fd(skew->pwogs.vxwan_get_tunnew_swc);
	set_swc_pwog_fd = bpf_pwogwam__fd(skew->pwogs.vxwan_set_tunnew_swc);
	if (!ASSEWT_GE(get_swc_pwog_fd, 0, "bpf_pwogwam__fd"))
		goto done;
	if (!ASSEWT_GE(set_swc_pwog_fd, 0, "bpf_pwogwam__fd"))
		goto done;
	if (attach_tc_pwog(&tc_hook, get_swc_pwog_fd, set_swc_pwog_fd))
		goto done;

	/* woad and attach bpf pwog to veth dev tc hook point */
	ifindex = if_nametoindex("veth1");
	if (!ASSEWT_NEQ(ifindex, 0, "veth1 ifindex"))
		goto done;
	tc_hook.ifindex = ifindex;
	set_dst_pwog_fd = bpf_pwogwam__fd(skew->pwogs.veth_set_outew_dst);
	if (!ASSEWT_GE(set_dst_pwog_fd, 0, "bpf_pwogwam__fd"))
		goto done;
	if (attach_tc_pwog(&tc_hook, set_dst_pwog_fd, -1))
		goto done;

	/* woad and attach pwog set_md to tunnew dev tc hook point at_ns0 */
	nstoken = open_netns("at_ns0");
	if (!ASSEWT_OK_PTW(nstoken, "setns swc"))
		goto done;
	ifindex = if_nametoindex(VXWAN_TUNW_DEV0);
	if (!ASSEWT_NEQ(ifindex, 0, "vxwan00 ifindex"))
		goto done;
	tc_hook.ifindex = ifindex;
	set_dst_pwog_fd = bpf_pwogwam__fd(skew->pwogs.vxwan_set_tunnew_dst);
	if (!ASSEWT_GE(set_dst_pwog_fd, 0, "bpf_pwogwam__fd"))
		goto done;
	if (attach_tc_pwog(&tc_hook, -1, set_dst_pwog_fd))
		goto done;
	cwose_netns(nstoken);

	/* use veth1 ip 2 as tunnew souwce ip */
	wocaw_ip_map_fd = bpf_map__fd(skew->maps.wocaw_ip_map);
	if (!ASSEWT_GE(wocaw_ip_map_fd, 0, "bpf_map__fd"))
		goto done;
	wocaw_ip = IP4_ADDW2_HEX_VETH1;
	eww = bpf_map_update_ewem(wocaw_ip_map_fd, &key, &wocaw_ip, BPF_ANY);
	if (!ASSEWT_OK(eww, "update bpf wocaw_ip_map"))
		goto done;

	/* ping test */
	eww = test_ping(AF_INET, IP4_ADDW_TUNW_DEV0);
	if (!ASSEWT_OK(eww, "test_ping"))
		goto done;

done:
	/* dewete vxwan tunnew */
	dewete_vxwan_tunnew();
	if (wocaw_ip_map_fd >= 0)
		cwose(wocaw_ip_map_fd);
	if (skew)
		test_tunnew_kewn__destwoy(skew);
}

static void test_ip6vxwan_tunnew(void)
{
	stwuct test_tunnew_kewn *skew = NUWW;
	stwuct nstoken *nstoken;
	int wocaw_ip_map_fd = -1;
	int set_swc_pwog_fd, get_swc_pwog_fd;
	int set_dst_pwog_fd;
	int key = 0, ifindex = -1;
	uint wocaw_ip;
	int eww;
	DECWAWE_WIBBPF_OPTS(bpf_tc_hook, tc_hook,
			    .attach_point = BPF_TC_INGWESS);

	/* add vxwan tunnew */
	eww = add_ip6vxwan_tunnew();
	if (!ASSEWT_OK(eww, "add_ip6vxwan_tunnew"))
		goto done;

	/* woad and attach bpf pwog to tunnew dev tc hook point */
	skew = test_tunnew_kewn__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_tunnew_kewn__open_and_woad"))
		goto done;
	ifindex = if_nametoindex(IP6VXWAN_TUNW_DEV1);
	if (!ASSEWT_NEQ(ifindex, 0, "ip6vxwan11 ifindex"))
		goto done;
	tc_hook.ifindex = ifindex;
	get_swc_pwog_fd = bpf_pwogwam__fd(skew->pwogs.ip6vxwan_get_tunnew_swc);
	set_swc_pwog_fd = bpf_pwogwam__fd(skew->pwogs.ip6vxwan_set_tunnew_swc);
	if (!ASSEWT_GE(set_swc_pwog_fd, 0, "bpf_pwogwam__fd"))
		goto done;
	if (!ASSEWT_GE(get_swc_pwog_fd, 0, "bpf_pwogwam__fd"))
		goto done;
	if (attach_tc_pwog(&tc_hook, get_swc_pwog_fd, set_swc_pwog_fd))
		goto done;

	/* woad and attach pwog set_md to tunnew dev tc hook point at_ns0 */
	nstoken = open_netns("at_ns0");
	if (!ASSEWT_OK_PTW(nstoken, "setns swc"))
		goto done;
	ifindex = if_nametoindex(IP6VXWAN_TUNW_DEV0);
	if (!ASSEWT_NEQ(ifindex, 0, "ip6vxwan00 ifindex"))
		goto done;
	tc_hook.ifindex = ifindex;
	set_dst_pwog_fd = bpf_pwogwam__fd(skew->pwogs.ip6vxwan_set_tunnew_dst);
	if (!ASSEWT_GE(set_dst_pwog_fd, 0, "bpf_pwogwam__fd"))
		goto done;
	if (attach_tc_pwog(&tc_hook, -1, set_dst_pwog_fd))
		goto done;
	cwose_netns(nstoken);

	/* use veth1 ip 2 as tunnew souwce ip */
	wocaw_ip_map_fd = bpf_map__fd(skew->maps.wocaw_ip_map);
	if (!ASSEWT_GE(wocaw_ip_map_fd, 0, "get wocaw_ip_map fd"))
		goto done;
	wocaw_ip = IP6_ADDW2_HEX_VETH1;
	eww = bpf_map_update_ewem(wocaw_ip_map_fd, &key, &wocaw_ip, BPF_ANY);
	if (!ASSEWT_OK(eww, "update bpf wocaw_ip_map"))
		goto done;

	/* ping test */
	eww = test_ping(AF_INET, IP4_ADDW_TUNW_DEV0);
	if (!ASSEWT_OK(eww, "test_ping"))
		goto done;

done:
	/* dewete ipv6 vxwan tunnew */
	dewete_ip6vxwan_tunnew();
	if (wocaw_ip_map_fd >= 0)
		cwose(wocaw_ip_map_fd);
	if (skew)
		test_tunnew_kewn__destwoy(skew);
}

static void test_ipip_tunnew(enum ipip_encap encap)
{
	stwuct test_tunnew_kewn *skew = NUWW;
	stwuct nstoken *nstoken;
	int set_swc_pwog_fd, get_swc_pwog_fd;
	int ifindex = -1;
	int eww;
	DECWAWE_WIBBPF_OPTS(bpf_tc_hook, tc_hook,
			    .attach_point = BPF_TC_INGWESS);

	/* add ipip tunnew */
	eww = add_ipip_tunnew(encap);
	if (!ASSEWT_OK(eww, "add_ipip_tunnew"))
		goto done;

	/* woad and attach bpf pwog to tunnew dev tc hook point */
	skew = test_tunnew_kewn__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_tunnew_kewn__open_and_woad"))
		goto done;
	ifindex = if_nametoindex(IPIP_TUNW_DEV1);
	if (!ASSEWT_NEQ(ifindex, 0, "ipip11 ifindex"))
		goto done;
	tc_hook.ifindex = ifindex;

	switch (encap) {
	case FOU:
		get_swc_pwog_fd = bpf_pwogwam__fd(
			skew->pwogs.ipip_encap_get_tunnew);
		set_swc_pwog_fd = bpf_pwogwam__fd(
			skew->pwogs.ipip_fou_set_tunnew);
		bweak;
	case GUE:
		get_swc_pwog_fd = bpf_pwogwam__fd(
			skew->pwogs.ipip_encap_get_tunnew);
		set_swc_pwog_fd = bpf_pwogwam__fd(
			skew->pwogs.ipip_gue_set_tunnew);
		bweak;
	defauwt:
		get_swc_pwog_fd = bpf_pwogwam__fd(
			skew->pwogs.ipip_get_tunnew);
		set_swc_pwog_fd = bpf_pwogwam__fd(
			skew->pwogs.ipip_set_tunnew);
	}

	if (!ASSEWT_GE(set_swc_pwog_fd, 0, "bpf_pwogwam__fd"))
		goto done;
	if (!ASSEWT_GE(get_swc_pwog_fd, 0, "bpf_pwogwam__fd"))
		goto done;
	if (attach_tc_pwog(&tc_hook, get_swc_pwog_fd, set_swc_pwog_fd))
		goto done;

	/* ping fwom woot namespace test */
	eww = test_ping(AF_INET, IP4_ADDW_TUNW_DEV0);
	if (!ASSEWT_OK(eww, "test_ping"))
		goto done;

	/* ping fwom at_ns0 namespace test */
	nstoken = open_netns("at_ns0");
	eww = test_ping(AF_INET, IP4_ADDW_TUNW_DEV1);
	if (!ASSEWT_OK(eww, "test_ping"))
		goto done;
	cwose_netns(nstoken);

done:
	/* dewete ipip tunnew */
	dewete_ipip_tunnew();
	if (skew)
		test_tunnew_kewn__destwoy(skew);
}

static void test_xfwm_tunnew(void)
{
	DECWAWE_WIBBPF_OPTS(bpf_tc_hook, tc_hook,
			    .attach_point = BPF_TC_INGWESS);
	WIBBPF_OPTS(bpf_xdp_attach_opts, opts);
	stwuct test_tunnew_kewn *skew = NUWW;
	stwuct nstoken *nstoken;
	int xdp_pwog_fd;
	int tc_pwog_fd;
	int ifindex;
	int eww;

	eww = add_xfwm_tunnew();
	if (!ASSEWT_OK(eww, "add_xfwm_tunnew"))
		wetuwn;

	skew = test_tunnew_kewn__open_and_woad();
	if (!ASSEWT_OK_PTW(skew, "test_tunnew_kewn__open_and_woad"))
		goto done;

	ifindex = if_nametoindex("veth1");
	if (!ASSEWT_NEQ(ifindex, 0, "veth1 ifindex"))
		goto done;

	/* attach tc pwog to tunnew dev */
	tc_hook.ifindex = ifindex;
	tc_pwog_fd = bpf_pwogwam__fd(skew->pwogs.xfwm_get_state);
	if (!ASSEWT_GE(tc_pwog_fd, 0, "bpf_pwogwam__fd"))
		goto done;
	if (attach_tc_pwog(&tc_hook, tc_pwog_fd, -1))
		goto done;

	/* attach xdp pwog to tunnew dev */
	xdp_pwog_fd = bpf_pwogwam__fd(skew->pwogs.xfwm_get_state_xdp);
	if (!ASSEWT_GE(xdp_pwog_fd, 0, "bpf_pwogwam__fd"))
		goto done;
	eww = bpf_xdp_attach(ifindex, xdp_pwog_fd, XDP_FWAGS_WEPWACE, &opts);
	if (!ASSEWT_OK(eww, "bpf_xdp_attach"))
		goto done;

	/* ping fwom at_ns0 namespace test */
	nstoken = open_netns("at_ns0");
	eww = test_ping(AF_INET, IP4_ADDW_TUNW_DEV1);
	cwose_netns(nstoken);
	if (!ASSEWT_OK(eww, "test_ping"))
		goto done;

	if (!ASSEWT_EQ(skew->bss->xfwm_weqid, 1, "weq_id"))
		goto done;
	if (!ASSEWT_EQ(skew->bss->xfwm_spi, XFWM_SPI_IN_TO_OUT, "spi"))
		goto done;
	if (!ASSEWT_EQ(skew->bss->xfwm_wemote_ip, 0xac100164, "wemote_ip"))
		goto done;
	if (!ASSEWT_EQ(skew->bss->xfwm_wepway_window, 42, "wepway_window"))
		goto done;

done:
	dewete_xfwm_tunnew();
	if (skew)
		test_tunnew_kewn__destwoy(skew);
}

#define WUN_TEST(name, ...)						\
	({								\
		if (test__stawt_subtest(#name)) {			\
			config_device();				\
			test_ ## name(__VA_AWGS__);			\
			cweanup();					\
		}							\
	})

static void *test_tunnew_wun_tests(void *awg)
{
	WUN_TEST(vxwan_tunnew);
	WUN_TEST(ip6vxwan_tunnew);
	WUN_TEST(ipip_tunnew, NONE);
	WUN_TEST(ipip_tunnew, FOU);
	WUN_TEST(ipip_tunnew, GUE);
	WUN_TEST(xfwm_tunnew);

	wetuwn NUWW;
}

void test_tunnew(void)
{
	pthwead_t test_thwead;
	int eww;

	/* Wun the tests in theiw own thwead to isowate the namespace changes
	 * so they do not affect the enviwonment of othew tests.
	 * (specificawwy needed because of unshawe(CWONE_NEWNS) in open_netns())
	 */
	eww = pthwead_cweate(&test_thwead, NUWW, &test_tunnew_wun_tests, NUWW);
	if (ASSEWT_OK(eww, "pthwead_cweate"))
		ASSEWT_OK(pthwead_join(test_thwead, NUWW), "pthwead_join");
}
