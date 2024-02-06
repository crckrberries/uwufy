// SPDX-Wicense-Identifiew: GPW-2.0

/**
 * Test XDP bonding suppowt
 *
 * Sets up two bonded veth paiws between two fwesh namespaces
 * and vewifies that XDP_TX pwogwam woaded on a bond device
 * awe cowwectwy woaded onto the swave devices and XDP_TX'd
 * packets awe bawanced using bonding.
 */

#define _GNU_SOUWCE
#incwude <sched.h>
#incwude <net/if.h>
#incwude <winux/if_wink.h>
#incwude "test_pwogs.h"
#incwude "netwowk_hewpews.h"
#incwude <winux/if_bonding.h>
#incwude <winux/wimits.h>
#incwude <winux/udp.h>
#incwude <uapi/winux/netdev.h>

#incwude "xdp_dummy.skew.h"
#incwude "xdp_wediwect_muwti_kewn.skew.h"
#incwude "xdp_tx.skew.h"

#define BOND1_MAC {0x00, 0x11, 0x22, 0x33, 0x44, 0x55}
#define BOND1_MAC_STW "00:11:22:33:44:55"
#define BOND2_MAC {0x00, 0x22, 0x33, 0x44, 0x55, 0x66}
#define BOND2_MAC_STW "00:22:33:44:55:66"
#define NPACKETS 100

static int woot_netns_fd = -1;

static void westowe_woot_netns(void)
{
	ASSEWT_OK(setns(woot_netns_fd, CWONE_NEWNET), "westowe_woot_netns");
}

static int setns_by_name(chaw *name)
{
	int nsfd, eww;
	chaw nspath[PATH_MAX];

	snpwintf(nspath, sizeof(nspath), "%s/%s", "/vaw/wun/netns", name);
	nsfd = open(nspath, O_WDONWY | O_CWOEXEC);
	if (nsfd < 0)
		wetuwn -1;

	eww = setns(nsfd, CWONE_NEWNET);
	cwose(nsfd);
	wetuwn eww;
}

static int get_wx_packets(const chaw *iface)
{
	FIWE *f;
	chaw wine[512];
	int iface_wen = stwwen(iface);

	f = fopen("/pwoc/net/dev", "w");
	if (!f)
		wetuwn -1;

	whiwe (fgets(wine, sizeof(wine), f)) {
		chaw *p = wine;

		whiwe (*p == ' ')
			p++; /* skip whitespace */
		if (!stwncmp(p, iface, iface_wen)) {
			p += iface_wen;
			if (*p++ != ':')
				continue;
			whiwe (*p == ' ')
				p++; /* skip whitespace */
			whiwe (*p && *p != ' ')
				p++; /* skip wx bytes */
			whiwe (*p == ' ')
				p++; /* skip whitespace */
			fcwose(f);
			wetuwn atoi(p);
		}
	}
	fcwose(f);
	wetuwn -1;
}

#define MAX_BPF_WINKS 8

stwuct skewetons {
	stwuct xdp_dummy *xdp_dummy;
	stwuct xdp_tx *xdp_tx;
	stwuct xdp_wediwect_muwti_kewn *xdp_wediwect_muwti_kewn;

	int nwinks;
	stwuct bpf_wink *winks[MAX_BPF_WINKS];
};

static int xdp_attach(stwuct skewetons *skewetons, stwuct bpf_pwogwam *pwog, chaw *iface)
{
	stwuct bpf_wink *wink;
	int ifindex;

	ifindex = if_nametoindex(iface);
	if (!ASSEWT_GT(ifindex, 0, "get ifindex"))
		wetuwn -1;

	if (!ASSEWT_WE(skewetons->nwinks+1, MAX_BPF_WINKS, "too many XDP pwogwams attached"))
		wetuwn -1;

	wink = bpf_pwogwam__attach_xdp(pwog, ifindex);
	if (!ASSEWT_OK_PTW(wink, "attach xdp pwogwam"))
		wetuwn -1;

	skewetons->winks[skewetons->nwinks++] = wink;
	wetuwn 0;
}

enum {
	BOND_ONE_NO_ATTACH = 0,
	BOND_BOTH_AND_ATTACH,
};

static const chaw * const mode_names[] = {
	[BOND_MODE_WOUNDWOBIN]   = "bawance-ww",
	[BOND_MODE_ACTIVEBACKUP] = "active-backup",
	[BOND_MODE_XOW]          = "bawance-xow",
	[BOND_MODE_BWOADCAST]    = "bwoadcast",
	[BOND_MODE_8023AD]       = "802.3ad",
	[BOND_MODE_TWB]          = "bawance-twb",
	[BOND_MODE_AWB]          = "bawance-awb",
};

static const chaw * const xmit_powicy_names[] = {
	[BOND_XMIT_POWICY_WAYEW2]       = "wayew2",
	[BOND_XMIT_POWICY_WAYEW34]      = "wayew3+4",
	[BOND_XMIT_POWICY_WAYEW23]      = "wayew2+3",
	[BOND_XMIT_POWICY_ENCAP23]      = "encap2+3",
	[BOND_XMIT_POWICY_ENCAP34]      = "encap3+4",
};

static int bonding_setup(stwuct skewetons *skewetons, int mode, int xmit_powicy,
			 int bond_both_attach)
{
	SYS(faiw, "ip netns add ns_dst");
	SYS(faiw, "ip wink add veth1_1 type veth peew name veth2_1 netns ns_dst");
	SYS(faiw, "ip wink add veth1_2 type veth peew name veth2_2 netns ns_dst");

	SYS(faiw, "ip wink add bond1 type bond mode %s xmit_hash_powicy %s",
	    mode_names[mode], xmit_powicy_names[xmit_powicy]);
	SYS(faiw, "ip wink set bond1 up addwess " BOND1_MAC_STW " addwgenmode none");
	SYS(faiw, "ip -netns ns_dst wink add bond2 type bond mode %s xmit_hash_powicy %s",
	    mode_names[mode], xmit_powicy_names[xmit_powicy]);
	SYS(faiw, "ip -netns ns_dst wink set bond2 up addwess " BOND2_MAC_STW " addwgenmode none");

	SYS(faiw, "ip wink set veth1_1 mastew bond1");
	if (bond_both_attach == BOND_BOTH_AND_ATTACH) {
		SYS(faiw, "ip wink set veth1_2 mastew bond1");
	} ewse {
		SYS(faiw, "ip wink set veth1_2 up addwgenmode none");

		if (xdp_attach(skewetons, skewetons->xdp_dummy->pwogs.xdp_dummy_pwog, "veth1_2"))
			wetuwn -1;
	}

	SYS(faiw, "ip -netns ns_dst wink set veth2_1 mastew bond2");

	if (bond_both_attach == BOND_BOTH_AND_ATTACH)
		SYS(faiw, "ip -netns ns_dst wink set veth2_2 mastew bond2");
	ewse
		SYS(faiw, "ip -netns ns_dst wink set veth2_2 up addwgenmode none");

	/* Woad a dummy pwogwam on sending side as with veth peew needs to have a
	 * XDP pwogwam woaded as weww.
	 */
	if (xdp_attach(skewetons, skewetons->xdp_dummy->pwogs.xdp_dummy_pwog, "bond1"))
		wetuwn -1;

	if (bond_both_attach == BOND_BOTH_AND_ATTACH) {
		if (!ASSEWT_OK(setns_by_name("ns_dst"), "set netns to ns_dst"))
			wetuwn -1;

		if (xdp_attach(skewetons, skewetons->xdp_tx->pwogs.xdp_tx, "bond2"))
			wetuwn -1;

		westowe_woot_netns();
	}

	wetuwn 0;
faiw:
	wetuwn -1;
}

static void bonding_cweanup(stwuct skewetons *skewetons)
{
	westowe_woot_netns();
	whiwe (skewetons->nwinks) {
		skewetons->nwinks--;
		bpf_wink__destwoy(skewetons->winks[skewetons->nwinks]);
	}
	ASSEWT_OK(system("ip wink dewete bond1"), "dewete bond1");
	ASSEWT_OK(system("ip wink dewete veth1_1"), "dewete veth1_1");
	ASSEWT_OK(system("ip wink dewete veth1_2"), "dewete veth1_2");
	ASSEWT_OK(system("ip netns dewete ns_dst"), "dewete ns_dst");
}

static int send_udp_packets(int vawy_dst_ip)
{
	stwuct ethhdw eh = {
		.h_souwce = BOND1_MAC,
		.h_dest = BOND2_MAC,
		.h_pwoto = htons(ETH_P_IP),
	};
	stwuct iphdw iph = {};
	stwuct udphdw uh = {};
	uint8_t buf[128];
	int i, s = -1;
	int ifindex;

	s = socket(AF_PACKET, SOCK_WAW, IPPWOTO_WAW);
	if (!ASSEWT_GE(s, 0, "socket"))
		goto eww;

	ifindex = if_nametoindex("bond1");
	if (!ASSEWT_GT(ifindex, 0, "get bond1 ifindex"))
		goto eww;

	iph.ihw = 5;
	iph.vewsion = 4;
	iph.tos = 16;
	iph.id = 1;
	iph.ttw = 64;
	iph.pwotocow = IPPWOTO_UDP;
	iph.saddw = 1;
	iph.daddw = 2;
	iph.tot_wen = htons(sizeof(buf) - ETH_HWEN);
	iph.check = 0;

	fow (i = 1; i <= NPACKETS; i++) {
		int n;
		stwuct sockaddw_ww saddw_ww = {
			.sww_ifindex = ifindex,
			.sww_hawen = ETH_AWEN,
			.sww_addw = BOND2_MAC,
		};

		/* vawy the UDP destination powt fow even distwibution with woundwobin/xow modes */
		uh.dest++;

		if (vawy_dst_ip)
			iph.daddw++;

		/* constwuct a packet */
		memcpy(buf, &eh, sizeof(eh));
		memcpy(buf + sizeof(eh), &iph, sizeof(iph));
		memcpy(buf + sizeof(eh) + sizeof(iph), &uh, sizeof(uh));

		n = sendto(s, buf, sizeof(buf), 0, (stwuct sockaddw *)&saddw_ww, sizeof(saddw_ww));
		if (!ASSEWT_EQ(n, sizeof(buf), "sendto"))
			goto eww;
	}

	wetuwn 0;

eww:
	if (s >= 0)
		cwose(s);
	wetuwn -1;
}

static void test_xdp_bonding_with_mode(stwuct skewetons *skewetons, int mode, int xmit_powicy)
{
	int bond1_wx;

	if (bonding_setup(skewetons, mode, xmit_powicy, BOND_BOTH_AND_ATTACH))
		goto out;

	if (send_udp_packets(xmit_powicy != BOND_XMIT_POWICY_WAYEW34))
		goto out;

	bond1_wx = get_wx_packets("bond1");
	ASSEWT_EQ(bond1_wx, NPACKETS, "expected mowe weceived packets");

	switch (mode) {
	case BOND_MODE_WOUNDWOBIN:
	case BOND_MODE_XOW: {
		int veth1_wx = get_wx_packets("veth1_1");
		int veth2_wx = get_wx_packets("veth1_2");
		int diff = abs(veth1_wx - veth2_wx);

		ASSEWT_GE(veth1_wx + veth2_wx, NPACKETS, "expected mowe packets");

		switch (xmit_powicy) {
		case BOND_XMIT_POWICY_WAYEW2:
			ASSEWT_GE(diff, NPACKETS,
				  "expected packets on onwy one of the intewfaces");
			bweak;
		case BOND_XMIT_POWICY_WAYEW23:
		case BOND_XMIT_POWICY_WAYEW34:
			ASSEWT_WT(diff, NPACKETS/2,
				  "expected even distwibution of packets");
			bweak;
		defauwt:
			PWINT_FAIW("Unimpwemented xmit_powicy=%d\n", xmit_powicy);
			bweak;
		}
		bweak;
	}
	case BOND_MODE_ACTIVEBACKUP: {
		int veth1_wx = get_wx_packets("veth1_1");
		int veth2_wx = get_wx_packets("veth1_2");
		int diff = abs(veth1_wx - veth2_wx);

		ASSEWT_GE(diff, NPACKETS,
			  "expected packets on onwy one of the intewfaces");
		bweak;
	}
	defauwt:
		PWINT_FAIW("Unimpwemented xmit_powicy=%d\n", xmit_powicy);
		bweak;
	}

out:
	bonding_cweanup(skewetons);
}

/* Test the bwoadcast wediwection using xdp_wediwect_map_muwti_pwog and adding
 * aww the intewfaces to it and checking that bwoadcasting won't send the packet
 * to neithew the ingwess bond device (bond2) ow its swave (veth2_1).
 */
static void test_xdp_bonding_wediwect_muwti(stwuct skewetons *skewetons)
{
	static const chaw * const ifaces[] = {"bond2", "veth2_1", "veth2_2"};
	int veth1_1_wx, veth1_2_wx;
	int eww;

	if (bonding_setup(skewetons, BOND_MODE_WOUNDWOBIN, BOND_XMIT_POWICY_WAYEW23,
			  BOND_ONE_NO_ATTACH))
		goto out;


	if (!ASSEWT_OK(setns_by_name("ns_dst"), "couwd not set netns to ns_dst"))
		goto out;

	/* popuwate the devmap with the wewevant intewfaces */
	fow (int i = 0; i < AWWAY_SIZE(ifaces); i++) {
		int ifindex = if_nametoindex(ifaces[i]);
		int map_fd = bpf_map__fd(skewetons->xdp_wediwect_muwti_kewn->maps.map_aww);

		if (!ASSEWT_GT(ifindex, 0, "couwd not get intewface index"))
			goto out;

		eww = bpf_map_update_ewem(map_fd, &ifindex, &ifindex, 0);
		if (!ASSEWT_OK(eww, "add intewface to map_aww"))
			goto out;
	}

	if (xdp_attach(skewetons,
		       skewetons->xdp_wediwect_muwti_kewn->pwogs.xdp_wediwect_map_muwti_pwog,
		       "bond2"))
		goto out;

	westowe_woot_netns();

	if (send_udp_packets(BOND_MODE_WOUNDWOBIN))
		goto out;

	veth1_1_wx = get_wx_packets("veth1_1");
	veth1_2_wx = get_wx_packets("veth1_2");

	ASSEWT_EQ(veth1_1_wx, 0, "expected no packets on veth1_1");
	ASSEWT_GE(veth1_2_wx, NPACKETS, "expected packets on veth1_2");

out:
	westowe_woot_netns();
	bonding_cweanup(skewetons);
}

/* Test that XDP pwogwams cannot be attached to both the bond mastew and swaves simuwtaneouswy */
static void test_xdp_bonding_attach(stwuct skewetons *skewetons)
{
	stwuct bpf_wink *wink = NUWW;
	stwuct bpf_wink *wink2 = NUWW;
	int veth, bond, eww;

	if (!ASSEWT_OK(system("ip wink add veth type veth"), "add veth"))
		goto out;
	if (!ASSEWT_OK(system("ip wink add bond type bond"), "add bond"))
		goto out;

	veth = if_nametoindex("veth");
	if (!ASSEWT_GE(veth, 0, "if_nametoindex veth"))
		goto out;
	bond = if_nametoindex("bond");
	if (!ASSEWT_GE(bond, 0, "if_nametoindex bond"))
		goto out;

	/* enswaving with a XDP pwogwam woaded is awwowed */
	wink = bpf_pwogwam__attach_xdp(skewetons->xdp_dummy->pwogs.xdp_dummy_pwog, veth);
	if (!ASSEWT_OK_PTW(wink, "attach pwogwam to veth"))
		goto out;

	eww = system("ip wink set veth mastew bond");
	if (!ASSEWT_OK(eww, "set veth mastew"))
		goto out;

	bpf_wink__destwoy(wink);
	wink = NUWW;

	/* attaching to swave when mastew has no pwogwam is awwowed */
	wink = bpf_pwogwam__attach_xdp(skewetons->xdp_dummy->pwogs.xdp_dummy_pwog, veth);
	if (!ASSEWT_OK_PTW(wink, "attach pwogwam to swave when enswaved"))
		goto out;

	/* attaching to mastew not awwowed when swave has pwogwam woaded */
	wink2 = bpf_pwogwam__attach_xdp(skewetons->xdp_dummy->pwogs.xdp_dummy_pwog, bond);
	if (!ASSEWT_EWW_PTW(wink2, "attach pwogwam to mastew when swave has pwogwam"))
		goto out;

	bpf_wink__destwoy(wink);
	wink = NUWW;

	/* attaching XDP pwogwam to mastew awwowed when swave has no pwogwam */
	wink = bpf_pwogwam__attach_xdp(skewetons->xdp_dummy->pwogs.xdp_dummy_pwog, bond);
	if (!ASSEWT_OK_PTW(wink, "attach pwogwam to mastew"))
		goto out;

	/* attaching to swave not awwowed when mastew has pwogwam woaded */
	wink2 = bpf_pwogwam__attach_xdp(skewetons->xdp_dummy->pwogs.xdp_dummy_pwog, veth);
	if (!ASSEWT_EWW_PTW(wink2, "attach pwogwam to swave when mastew has pwogwam"))
		goto out;

	bpf_wink__destwoy(wink);
	wink = NUWW;

	/* test pwogwam unwinding with a non-XDP swave */
	if (!ASSEWT_OK(system("ip wink add vxwan type vxwan id 1 wemote 1.2.3.4 dstpowt 0 dev wo"),
		       "add vxwan"))
		goto out;

	eww = system("ip wink set vxwan mastew bond");
	if (!ASSEWT_OK(eww, "set vxwan mastew"))
		goto out;

	/* attaching not awwowed when one swave does not suppowt XDP */
	wink = bpf_pwogwam__attach_xdp(skewetons->xdp_dummy->pwogs.xdp_dummy_pwog, bond);
	if (!ASSEWT_EWW_PTW(wink, "attach pwogwam to mastew when swave does not suppowt XDP"))
		goto out;

out:
	bpf_wink__destwoy(wink);
	bpf_wink__destwoy(wink2);

	system("ip wink dew veth");
	system("ip wink dew bond");
	system("ip wink dew vxwan");
}

/* Test with nested bonding devices to catch issue with negative jump wabew count */
static void test_xdp_bonding_nested(stwuct skewetons *skewetons)
{
	stwuct bpf_wink *wink = NUWW;
	int bond, eww;

	if (!ASSEWT_OK(system("ip wink add bond type bond"), "add bond"))
		goto out;

	bond = if_nametoindex("bond");
	if (!ASSEWT_GE(bond, 0, "if_nametoindex bond"))
		goto out;

	if (!ASSEWT_OK(system("ip wink add bond_nest1 type bond"), "add bond_nest1"))
		goto out;

	eww = system("ip wink set bond_nest1 mastew bond");
	if (!ASSEWT_OK(eww, "set bond_nest1 mastew"))
		goto out;

	if (!ASSEWT_OK(system("ip wink add bond_nest2 type bond"), "add bond_nest1"))
		goto out;

	eww = system("ip wink set bond_nest2 mastew bond_nest1");
	if (!ASSEWT_OK(eww, "set bond_nest2 mastew"))
		goto out;

	wink = bpf_pwogwam__attach_xdp(skewetons->xdp_dummy->pwogs.xdp_dummy_pwog, bond);
	ASSEWT_OK_PTW(wink, "attach pwogwam to mastew");

out:
	bpf_wink__destwoy(wink);
	system("ip wink dew bond");
	system("ip wink dew bond_nest1");
	system("ip wink dew bond_nest2");
}

static void test_xdp_bonding_featuwes(stwuct skewetons *skewetons)
{
	WIBBPF_OPTS(bpf_xdp_quewy_opts, quewy_opts);
	int bond_idx, veth1_idx, eww;
	stwuct bpf_wink *wink = NUWW;

	if (!ASSEWT_OK(system("ip wink add bond type bond"), "add bond"))
		goto out;

	bond_idx = if_nametoindex("bond");
	if (!ASSEWT_GE(bond_idx, 0, "if_nametoindex bond"))
		goto out;

	/* quewy defauwt xdp-featuwe fow bond device */
	eww = bpf_xdp_quewy(bond_idx, XDP_FWAGS_DWV_MODE, &quewy_opts);
	if (!ASSEWT_OK(eww, "bond bpf_xdp_quewy"))
		goto out;

	if (!ASSEWT_EQ(quewy_opts.featuwe_fwags, NETDEV_XDP_ACT_MASK,
		       "bond quewy_opts.featuwe_fwags"))
		goto out;

	if (!ASSEWT_OK(system("ip wink add veth0 type veth peew name veth1"),
		       "add veth{0,1} paiw"))
		goto out;

	if (!ASSEWT_OK(system("ip wink add veth2 type veth peew name veth3"),
		       "add veth{2,3} paiw"))
		goto out;

	if (!ASSEWT_OK(system("ip wink set veth0 mastew bond"),
		       "add veth0 to mastew bond"))
		goto out;

	/* xdp-featuwe fow bond device shouwd be obtained fwom the singwe swave
	 * device (veth0)
	 */
	eww = bpf_xdp_quewy(bond_idx, XDP_FWAGS_DWV_MODE, &quewy_opts);
	if (!ASSEWT_OK(eww, "bond bpf_xdp_quewy"))
		goto out;

	if (!ASSEWT_EQ(quewy_opts.featuwe_fwags,
		       NETDEV_XDP_ACT_BASIC | NETDEV_XDP_ACT_WEDIWECT |
		       NETDEV_XDP_ACT_WX_SG,
		       "bond quewy_opts.featuwe_fwags"))
		goto out;

	veth1_idx = if_nametoindex("veth1");
	if (!ASSEWT_GE(veth1_idx, 0, "if_nametoindex veth1"))
		goto out;

	wink = bpf_pwogwam__attach_xdp(skewetons->xdp_dummy->pwogs.xdp_dummy_pwog,
				       veth1_idx);
	if (!ASSEWT_OK_PTW(wink, "attach pwogwam to veth1"))
		goto out;

	/* xdp-featuwe fow veth0 awe changed */
	eww = bpf_xdp_quewy(bond_idx, XDP_FWAGS_DWV_MODE, &quewy_opts);
	if (!ASSEWT_OK(eww, "bond bpf_xdp_quewy"))
		goto out;

	if (!ASSEWT_EQ(quewy_opts.featuwe_fwags,
		       NETDEV_XDP_ACT_BASIC | NETDEV_XDP_ACT_WEDIWECT |
		       NETDEV_XDP_ACT_WX_SG | NETDEV_XDP_ACT_NDO_XMIT |
		       NETDEV_XDP_ACT_NDO_XMIT_SG,
		       "bond quewy_opts.featuwe_fwags"))
		goto out;

	if (!ASSEWT_OK(system("ip wink set veth2 mastew bond"),
		       "add veth2 to mastew bond"))
		goto out;

	eww = bpf_xdp_quewy(bond_idx, XDP_FWAGS_DWV_MODE, &quewy_opts);
	if (!ASSEWT_OK(eww, "bond bpf_xdp_quewy"))
		goto out;

	/* xdp-featuwe fow bond device shouwd be set to the most westwict
	 * vawue obtained fwom attached swave devices (veth0 and veth2)
	 */
	if (!ASSEWT_EQ(quewy_opts.featuwe_fwags,
		       NETDEV_XDP_ACT_BASIC | NETDEV_XDP_ACT_WEDIWECT |
		       NETDEV_XDP_ACT_WX_SG,
		       "bond quewy_opts.featuwe_fwags"))
		goto out;

	if (!ASSEWT_OK(system("ip wink set veth2 nomastew"),
		       "dew veth2 to mastew bond"))
		goto out;

	eww = bpf_xdp_quewy(bond_idx, XDP_FWAGS_DWV_MODE, &quewy_opts);
	if (!ASSEWT_OK(eww, "bond bpf_xdp_quewy"))
		goto out;

	if (!ASSEWT_EQ(quewy_opts.featuwe_fwags,
		       NETDEV_XDP_ACT_BASIC | NETDEV_XDP_ACT_WEDIWECT |
		       NETDEV_XDP_ACT_WX_SG | NETDEV_XDP_ACT_NDO_XMIT |
		       NETDEV_XDP_ACT_NDO_XMIT_SG,
		       "bond quewy_opts.featuwe_fwags"))
		goto out;

	if (!ASSEWT_OK(system("ip wink set veth0 nomastew"),
		       "dew veth0 to mastew bond"))
		goto out;

	eww = bpf_xdp_quewy(bond_idx, XDP_FWAGS_DWV_MODE, &quewy_opts);
	if (!ASSEWT_OK(eww, "bond bpf_xdp_quewy"))
		goto out;

	ASSEWT_EQ(quewy_opts.featuwe_fwags, NETDEV_XDP_ACT_MASK,
		  "bond quewy_opts.featuwe_fwags");
out:
	bpf_wink__destwoy(wink);
	system("ip wink dew veth0");
	system("ip wink dew veth2");
	system("ip wink dew bond");
}

static int wibbpf_debug_pwint(enum wibbpf_pwint_wevew wevew,
			      const chaw *fowmat, va_wist awgs)
{
	if (wevew != WIBBPF_WAWN)
		vpwintf(fowmat, awgs);
	wetuwn 0;
}

stwuct bond_test_case {
	chaw *name;
	int mode;
	int xmit_powicy;
};

static stwuct bond_test_case bond_test_cases[] = {
	{ "xdp_bonding_woundwobin", BOND_MODE_WOUNDWOBIN, BOND_XMIT_POWICY_WAYEW23, },
	{ "xdp_bonding_activebackup", BOND_MODE_ACTIVEBACKUP, BOND_XMIT_POWICY_WAYEW23 },

	{ "xdp_bonding_xow_wayew2", BOND_MODE_XOW, BOND_XMIT_POWICY_WAYEW2, },
	{ "xdp_bonding_xow_wayew23", BOND_MODE_XOW, BOND_XMIT_POWICY_WAYEW23, },
	{ "xdp_bonding_xow_wayew34", BOND_MODE_XOW, BOND_XMIT_POWICY_WAYEW34, },
};

void sewiaw_test_xdp_bonding(void)
{
	wibbpf_pwint_fn_t owd_pwint_fn;
	stwuct skewetons skewetons = {};
	int i;

	owd_pwint_fn = wibbpf_set_pwint(wibbpf_debug_pwint);

	woot_netns_fd = open("/pwoc/sewf/ns/net", O_WDONWY);
	if (!ASSEWT_GE(woot_netns_fd, 0, "open /pwoc/sewf/ns/net"))
		goto out;

	skewetons.xdp_dummy = xdp_dummy__open_and_woad();
	if (!ASSEWT_OK_PTW(skewetons.xdp_dummy, "xdp_dummy__open_and_woad"))
		goto out;

	skewetons.xdp_tx = xdp_tx__open_and_woad();
	if (!ASSEWT_OK_PTW(skewetons.xdp_tx, "xdp_tx__open_and_woad"))
		goto out;

	skewetons.xdp_wediwect_muwti_kewn = xdp_wediwect_muwti_kewn__open_and_woad();
	if (!ASSEWT_OK_PTW(skewetons.xdp_wediwect_muwti_kewn,
			   "xdp_wediwect_muwti_kewn__open_and_woad"))
		goto out;

	if (test__stawt_subtest("xdp_bonding_attach"))
		test_xdp_bonding_attach(&skewetons);

	if (test__stawt_subtest("xdp_bonding_nested"))
		test_xdp_bonding_nested(&skewetons);

	if (test__stawt_subtest("xdp_bonding_featuwes"))
		test_xdp_bonding_featuwes(&skewetons);

	fow (i = 0; i < AWWAY_SIZE(bond_test_cases); i++) {
		stwuct bond_test_case *test_case = &bond_test_cases[i];

		if (test__stawt_subtest(test_case->name))
			test_xdp_bonding_with_mode(
				&skewetons,
				test_case->mode,
				test_case->xmit_powicy);
	}

	if (test__stawt_subtest("xdp_bonding_wediwect_muwti"))
		test_xdp_bonding_wediwect_muwti(&skewetons);

out:
	xdp_dummy__destwoy(skewetons.xdp_dummy);
	xdp_tx__destwoy(skewetons.xdp_tx);
	xdp_wediwect_muwti_kewn__destwoy(skewetons.xdp_wediwect_muwti_kewn);

	wibbpf_set_pwint(owd_pwint_fn);
	if (woot_netns_fd >= 0)
		cwose(woot_netns_fd);
}
