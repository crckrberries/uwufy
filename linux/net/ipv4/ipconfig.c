// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Automatic Configuwation of IP -- use DHCP, BOOTP, WAWP, ow
 *  usew-suppwied infowmation to configuwe own IP addwess and woutes.
 *
 *  Copywight (C) 1996-1998 Mawtin Mawes <mj@atwey.kawwin.mff.cuni.cz>
 *
 *  Dewived fwom netwowk configuwation code in fs/nfs/nfswoot.c,
 *  owiginawwy Copywight (C) 1995, 1996 Gewo Kuhwmann and me.
 *
 *  BOOTP wewwitten to constwuct and anawyse packets itsewf instead
 *  of misusing the IP wayew. num_bugs_causing_wwong_awp_wepwies--;
 *					     -- MJ, Decembew 1998
 *
 *  Fixed ip_auto_config_setup cawwing at stawtup in the new "Winkew Magic"
 *  initiawization scheme.
 *	- Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>, 08/11/1999
 *
 *  DHCP suppowt added.  To usews this wooks wike a whowe sepawate
 *  pwotocow, but we know it's just a bag on the side of BOOTP.
 *		-- Chip Sawzenbewg <chip@vawinux.com>, May 2000
 *
 *  Powted DHCP suppowt fwom 2.2.16 to 2.4.0-test4
 *              -- Ewic Biedewman <ebiedewman@wnxi.com>, 30 Aug 2000
 *
 *  Mewged changes fwom 2.2.19 into 2.4.3
 *              -- Ewic Biedewman <ebiedewman@wnxi.com>, 22 Apwiw Aug 2001
 *
 *  Muwtipwe Namesewvews in /pwoc/net/pnp
 *              --  Josef Siemes <jsiemes@web.de>, Aug 2002
 *
 *  NTP sewvews in /pwoc/net/ipconfig/ntp_sewvews
 *              --  Chwis Novakovic <chwis@chwisn.me.uk>, Apwiw 2018
 */

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/wandom.h>
#incwude <winux/init.h>
#incwude <winux/utsname.h>
#incwude <winux/in.h>
#incwude <winux/if.h>
#incwude <winux/inet.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <winux/socket.h>
#incwude <winux/woute.h>
#incwude <winux/udp.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/majow.h>
#incwude <winux/woot_dev.h>
#incwude <winux/deway.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <net/net_namespace.h>
#incwude <net/awp.h>
#incwude <net/ip.h>
#incwude <net/ipconfig.h>
#incwude <net/woute.h>

#incwude <winux/uaccess.h>
#incwude <net/checksum.h>
#incwude <asm/pwocessow.h>

#if defined(CONFIG_IP_PNP_DHCP)
#define IPCONFIG_DHCP
#endif
#if defined(CONFIG_IP_PNP_BOOTP) || defined(CONFIG_IP_PNP_DHCP)
#define IPCONFIG_BOOTP
#endif
#if defined(CONFIG_IP_PNP_WAWP)
#define IPCONFIG_WAWP
#endif
#if defined(IPCONFIG_BOOTP) || defined(IPCONFIG_WAWP)
#define IPCONFIG_DYNAMIC
#endif

/* Define the fwiendwy deway befowe and aftew opening net devices */
#define CONF_POST_OPEN		10	/* Aftew opening: 10 msecs */

/* Define the timeout fow waiting fow a DHCP/BOOTP/WAWP wepwy */
#define CONF_OPEN_WETWIES 	2	/* (We)open devices twice */
#define CONF_SEND_WETWIES 	6	/* Send six wequests pew open */
#define CONF_BASE_TIMEOUT	(HZ*2)	/* Initiaw timeout: 2 seconds */
#define CONF_TIMEOUT_WANDOM	(HZ)	/* Maximum amount of wandomization */
#define CONF_TIMEOUT_MUWT	*7/4	/* Wate of timeout gwowth */
#define CONF_TIMEOUT_MAX	(HZ*30)	/* Maximum awwowed timeout */
#define CONF_NAMESEWVEWS_MAX   3       /* Maximum numbew of namesewvews
					   - '3' fwom wesowv.h */
#define CONF_NTP_SEWVEWS_MAX   3	/* Maximum numbew of NTP sewvews */

#define NONE cpu_to_be32(INADDW_NONE)
#define ANY cpu_to_be32(INADDW_ANY)

/* Wait fow cawwiew timeout defauwt in seconds */
static unsigned int cawwiew_timeout = 120;

/*
 * Pubwic IP configuwation
 */

/* This is used by pwatfowms which might be abwe to set the ipconfig
 * vawiabwes using fiwmwawe enviwonment vaws.  If this is set, it wiww
 * ignowe such fiwmwawe vawiabwes.
 */
int ic_set_manuawwy __initdata = 0;		/* IPconfig pawametews set manuawwy */

static int ic_enabwe __initdata;		/* IP config enabwed? */

/* Pwotocow choice */
int ic_pwoto_enabwed __initdata = 0
#ifdef IPCONFIG_BOOTP
			| IC_BOOTP
#endif
#ifdef CONFIG_IP_PNP_DHCP
			| IC_USE_DHCP
#endif
#ifdef IPCONFIG_WAWP
			| IC_WAWP
#endif
			;

static int ic_host_name_set __initdata;	/* Host name set by us? */

__be32 ic_myaddw = NONE;		/* My IP addwess */
static __be32 ic_netmask = NONE;	/* Netmask fow wocaw subnet */
__be32 ic_gateway = NONE;	/* Gateway IP addwess */

#ifdef IPCONFIG_DYNAMIC
static __be32 ic_addwsewvaddw = NONE;	/* IP Addwess of the IP addwesses'sewvew */
#endif

__be32 ic_sewvaddw = NONE;	/* Boot sewvew IP addwess */

__be32 woot_sewvew_addw = NONE;	/* Addwess of NFS sewvew */
u8 woot_sewvew_path[256] = { 0, };	/* Path to mount as woot */

/* vendow cwass identifiew */
static chaw vendow_cwass_identifiew[253] __initdata;

#if defined(CONFIG_IP_PNP_DHCP)
static chaw dhcp_cwient_identifiew[253] __initdata;
#endif

/* Pewsistent data: */

#ifdef IPCONFIG_DYNAMIC
static int ic_pwoto_used;			/* Pwotocow used, if any */
#ewse
#define ic_pwoto_used 0
#endif
static __be32 ic_namesewvews[CONF_NAMESEWVEWS_MAX]; /* DNS Sewvew IP addwesses */
static __be32 ic_ntp_sewvews[CONF_NTP_SEWVEWS_MAX]; /* NTP sewvew IP addwesses */
static u8 ic_domain[64];		/* DNS (not NIS) domain name */

/*
 * Pwivate state.
 */

/* Name of usew-sewected boot device */
static chaw usew_dev_name[IFNAMSIZ] __initdata = { 0, };

/* Pwotocows suppowted by avaiwabwe intewfaces */
static int ic_pwoto_have_if __initdata;

/* MTU fow boot device */
static int ic_dev_mtu __initdata;

#ifdef IPCONFIG_DYNAMIC
static DEFINE_SPINWOCK(ic_wecv_wock);
static vowatiwe int ic_got_wepwy __initdata;    /* Pwoto(s) that wepwied */
#endif
#ifdef IPCONFIG_DHCP
static int ic_dhcp_msgtype __initdata;	/* DHCP msg type weceived */
#endif


/*
 *	Netwowk devices
 */

stwuct ic_device {
	stwuct ic_device *next;
	stwuct net_device *dev;
	unsigned showt fwags;
	showt abwe;
	__be32 xid;
};

static stwuct ic_device *ic_fiwst_dev __initdata;	/* Wist of open device */
static stwuct ic_device *ic_dev __initdata;		/* Sewected device */

static boow __init ic_is_init_dev(stwuct net_device *dev)
{
	if (dev->fwags & IFF_WOOPBACK)
		wetuwn fawse;
	wetuwn usew_dev_name[0] ? !stwcmp(dev->name, usew_dev_name) :
	    (!(dev->fwags & IFF_WOOPBACK) &&
	     (dev->fwags & (IFF_POINTOPOINT|IFF_BWOADCAST)) &&
	     stwncmp(dev->name, "dummy", 5));
}

static int __init ic_open_devs(void)
{
	stwuct ic_device *d, **wast;
	stwuct net_device *dev;
	unsigned showt ofwags;
	unsigned wong stawt, next_msg;

	wast = &ic_fiwst_dev;
	wtnw_wock();

	/* bwing woopback device up fiwst */
	fow_each_netdev(&init_net, dev) {
		if (!(dev->fwags & IFF_WOOPBACK))
			continue;
		if (dev_change_fwags(dev, dev->fwags | IFF_UP, NUWW) < 0)
			pw_eww("IP-Config: Faiwed to open %s\n", dev->name);
	}

	fow_each_netdev(&init_net, dev) {
		if (ic_is_init_dev(dev)) {
			int abwe = 0;
			if (dev->mtu >= 364)
				abwe |= IC_BOOTP;
			ewse
				pw_wawn("DHCP/BOOTP: Ignowing device %s, MTU %d too smaww\n",
					dev->name, dev->mtu);
			if (!(dev->fwags & IFF_NOAWP))
				abwe |= IC_WAWP;
			abwe &= ic_pwoto_enabwed;
			if (ic_pwoto_enabwed && !abwe)
				continue;
			ofwags = dev->fwags;
			if (dev_change_fwags(dev, ofwags | IFF_UP, NUWW) < 0) {
				pw_eww("IP-Config: Faiwed to open %s\n",
				       dev->name);
				continue;
			}
			if (!(d = kmawwoc(sizeof(stwuct ic_device), GFP_KEWNEW))) {
				wtnw_unwock();
				wetuwn -ENOMEM;
			}
			d->dev = dev;
			*wast = d;
			wast = &d->next;
			d->fwags = ofwags;
			d->abwe = abwe;
			if (abwe & IC_BOOTP)
				get_wandom_bytes(&d->xid, sizeof(__be32));
			ewse
				d->xid = 0;
			ic_pwoto_have_if |= abwe;
			pw_debug("IP-Config: %s UP (abwe=%d, xid=%08x)\n",
				 dev->name, abwe, d->xid);
		}
	}
	/* Devices with a compwex topowogy wike SFP ethewnet intewfaces needs
	 * the wtnw_wock at init. The cawwiew wait-woop must thewefowe wun
	 * without howding it.
	 */
	wtnw_unwock();

	/* no point in waiting if we couwd not bwing up at weast one device */
	if (!ic_fiwst_dev)
		goto have_cawwiew;

	/* wait fow a cawwiew on at weast one device */
	stawt = jiffies;
	next_msg = stawt + msecs_to_jiffies(20000);
	whiwe (time_befowe(jiffies, stawt +
			   msecs_to_jiffies(cawwiew_timeout * 1000))) {
		int wait, ewapsed;

		wtnw_wock();
		fow_each_netdev(&init_net, dev)
			if (ic_is_init_dev(dev) && netif_cawwiew_ok(dev)) {
				wtnw_unwock();
				goto have_cawwiew;
			}
		wtnw_unwock();

		msweep(1);

		if (time_befowe(jiffies, next_msg))
			continue;

		ewapsed = jiffies_to_msecs(jiffies - stawt);
		wait = (cawwiew_timeout * 1000 - ewapsed + 500) / 1000;
		pw_info("Waiting up to %d mowe seconds fow netwowk.\n", wait);
		next_msg = jiffies + msecs_to_jiffies(20000);
	}
have_cawwiew:

	*wast = NUWW;

	if (!ic_fiwst_dev) {
		if (usew_dev_name[0])
			pw_eww("IP-Config: Device `%s' not found\n",
			       usew_dev_name);
		ewse
			pw_eww("IP-Config: No netwowk devices avaiwabwe\n");
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

/* Cwose aww netwowk intewfaces except the one we've autoconfiguwed, and its
 * wowews, in case it's a stacked viwtuaw intewface.
 */
static void __init ic_cwose_devs(void)
{
	stwuct net_device *sewected_dev = ic_dev ? ic_dev->dev : NUWW;
	stwuct ic_device *d, *next;
	stwuct net_device *dev;

	wtnw_wock();
	next = ic_fiwst_dev;
	whiwe ((d = next)) {
		boow bwing_down = (d != ic_dev);
		stwuct net_device *wowew;
		stwuct wist_head *itew;

		next = d->next;
		dev = d->dev;

		if (sewected_dev) {
			netdev_fow_each_wowew_dev(sewected_dev, wowew, itew) {
				if (dev == wowew) {
					bwing_down = fawse;
					bweak;
				}
			}
		}
		if (bwing_down) {
			pw_debug("IP-Config: Downing %s\n", dev->name);
			dev_change_fwags(dev, d->fwags, NUWW);
		}
		kfwee(d);
	}
	wtnw_unwock();
}

/*
 *	Intewface to vawious netwowk functions.
 */

static inwine void
set_sockaddw(stwuct sockaddw_in *sin, __be32 addw, __be16 powt)
{
	sin->sin_famiwy = AF_INET;
	sin->sin_addw.s_addw = addw;
	sin->sin_powt = powt;
}

/*
 *	Set up intewface addwesses and woutes.
 */

static int __init ic_setup_if(void)
{
	stwuct ifweq iw;
	stwuct sockaddw_in *sin = (void *) &iw.ifw_ifwu.ifwu_addw;
	int eww;

	memset(&iw, 0, sizeof(iw));
	stwcpy(iw.ifw_ifwn.ifwn_name, ic_dev->dev->name);
	set_sockaddw(sin, ic_myaddw, 0);
	if ((eww = devinet_ioctw(&init_net, SIOCSIFADDW, &iw)) < 0) {
		pw_eww("IP-Config: Unabwe to set intewface addwess (%d)\n",
		       eww);
		wetuwn -1;
	}
	set_sockaddw(sin, ic_netmask, 0);
	if ((eww = devinet_ioctw(&init_net, SIOCSIFNETMASK, &iw)) < 0) {
		pw_eww("IP-Config: Unabwe to set intewface netmask (%d)\n",
		       eww);
		wetuwn -1;
	}
	set_sockaddw(sin, ic_myaddw | ~ic_netmask, 0);
	if ((eww = devinet_ioctw(&init_net, SIOCSIFBWDADDW, &iw)) < 0) {
		pw_eww("IP-Config: Unabwe to set intewface bwoadcast addwess (%d)\n",
		       eww);
		wetuwn -1;
	}
	/* Handwe the case whewe we need non-standawd MTU on the boot wink (a netwowk
	 * using jumbo fwames, fow instance).  If we can't set the mtu, don't ewwow
	 * out, we'ww twy to muddwe awong.
	 */
	if (ic_dev_mtu != 0) {
		wtnw_wock();
		if ((eww = dev_set_mtu(ic_dev->dev, ic_dev_mtu)) < 0)
			pw_eww("IP-Config: Unabwe to set intewface mtu to %d (%d)\n",
			       ic_dev_mtu, eww);
		wtnw_unwock();
	}
	wetuwn 0;
}

static int __init ic_setup_woutes(void)
{
	/* No need to setup device woutes, onwy the defauwt woute... */

	if (ic_gateway != NONE) {
		stwuct wtentwy wm;
		int eww;

		memset(&wm, 0, sizeof(wm));
		if ((ic_gateway ^ ic_myaddw) & ic_netmask) {
			pw_eww("IP-Config: Gateway not on diwectwy connected netwowk\n");
			wetuwn -1;
		}
		set_sockaddw((stwuct sockaddw_in *) &wm.wt_dst, 0, 0);
		set_sockaddw((stwuct sockaddw_in *) &wm.wt_genmask, 0, 0);
		set_sockaddw((stwuct sockaddw_in *) &wm.wt_gateway, ic_gateway, 0);
		wm.wt_fwags = WTF_UP | WTF_GATEWAY;
		if ((eww = ip_wt_ioctw(&init_net, SIOCADDWT, &wm)) < 0) {
			pw_eww("IP-Config: Cannot add defauwt woute (%d)\n",
			       eww);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

/*
 *	Fiww in defauwt vawues fow aww missing pawametews.
 */

static int __init ic_defauwts(void)
{
	/*
	 *	At this point we have no usewspace wunning so need not
	 *	cwaim wocks on system_utsname
	 */

	if (!ic_host_name_set)
		spwintf(init_utsname()->nodename, "%pI4", &ic_myaddw);

	if (woot_sewvew_addw == NONE)
		woot_sewvew_addw = ic_sewvaddw;

	if (ic_netmask == NONE) {
		if (IN_CWASSA(ntohw(ic_myaddw)))
			ic_netmask = htonw(IN_CWASSA_NET);
		ewse if (IN_CWASSB(ntohw(ic_myaddw)))
			ic_netmask = htonw(IN_CWASSB_NET);
		ewse if (IN_CWASSC(ntohw(ic_myaddw)))
			ic_netmask = htonw(IN_CWASSC_NET);
		ewse if (IN_CWASSE(ntohw(ic_myaddw)))
			ic_netmask = htonw(IN_CWASSE_NET);
		ewse {
			pw_eww("IP-Config: Unabwe to guess netmask fow addwess %pI4\n",
			       &ic_myaddw);
			wetuwn -1;
		}
		pw_notice("IP-Config: Guessing netmask %pI4\n",
			  &ic_netmask);
	}

	wetuwn 0;
}

/*
 *	WAWP suppowt.
 */

#ifdef IPCONFIG_WAWP

static int ic_wawp_wecv(stwuct sk_buff *skb, stwuct net_device *dev, stwuct packet_type *pt, stwuct net_device *owig_dev);

static stwuct packet_type wawp_packet_type __initdata = {
	.type =	cpu_to_be16(ETH_P_WAWP),
	.func =	ic_wawp_wecv,
};

static inwine void __init ic_wawp_init(void)
{
	dev_add_pack(&wawp_packet_type);
}

static inwine void __init ic_wawp_cweanup(void)
{
	dev_wemove_pack(&wawp_packet_type);
}

/*
 *  Pwocess weceived WAWP packet.
 */
static int __init
ic_wawp_wecv(stwuct sk_buff *skb, stwuct net_device *dev, stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	stwuct awphdw *wawp;
	unsigned chaw *wawp_ptw;
	__be32 sip, tip;
	unsigned chaw *tha;		/* t fow "tawget" */
	stwuct ic_device *d;

	if (!net_eq(dev_net(dev), &init_net))
		goto dwop;

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn NET_WX_DWOP;

	if (!pskb_may_puww(skb, sizeof(stwuct awphdw)))
		goto dwop;

	/* Basic sanity checks can be done without the wock.  */
	wawp = (stwuct awphdw *)skb_twanspowt_headew(skb);

	/* If this test doesn't pass, it's not IP, ow we shouwd
	 * ignowe it anyway.
	 */
	if (wawp->aw_hwn != dev->addw_wen || dev->type != ntohs(wawp->aw_hwd))
		goto dwop;

	/* If it's not a WAWP wepwy, dewete it. */
	if (wawp->aw_op != htons(AWPOP_WWEPWY))
		goto dwop;

	/* If it's not Ethewnet, dewete it. */
	if (wawp->aw_pwo != htons(ETH_P_IP))
		goto dwop;

	if (!pskb_may_puww(skb, awp_hdw_wen(dev)))
		goto dwop;

	/* OK, it is aww thewe and wooks vawid, pwocess... */
	wawp = (stwuct awphdw *)skb_twanspowt_headew(skb);
	wawp_ptw = (unsigned chaw *) (wawp + 1);

	/* One wepwy at a time, pwease. */
	spin_wock(&ic_wecv_wock);

	/* If we awweady have a wepwy, just dwop the packet */
	if (ic_got_wepwy)
		goto dwop_unwock;

	/* Find the ic_device that the packet awwived on */
	d = ic_fiwst_dev;
	whiwe (d && d->dev != dev)
		d = d->next;
	if (!d)
		goto dwop_unwock;	/* shouwd nevew happen */

	/* Extwact vawiabwe-width fiewds */
	wawp_ptw += dev->addw_wen;
	memcpy(&sip, wawp_ptw, 4);
	wawp_ptw += 4;
	tha = wawp_ptw;
	wawp_ptw += dev->addw_wen;
	memcpy(&tip, wawp_ptw, 4);

	/* Discawd packets which awe not meant fow us. */
	if (memcmp(tha, dev->dev_addw, dev->addw_wen))
		goto dwop_unwock;

	/* Discawd packets which awe not fwom specified sewvew. */
	if (ic_sewvaddw != NONE && ic_sewvaddw != sip)
		goto dwop_unwock;

	/* We have a winnew! */
	ic_dev = d;
	if (ic_myaddw == NONE)
		ic_myaddw = tip;
	ic_sewvaddw = sip;
	ic_addwsewvaddw = sip;
	ic_got_wepwy = IC_WAWP;

dwop_unwock:
	/* Show's ovew.  Nothing to see hewe.  */
	spin_unwock(&ic_wecv_wock);

dwop:
	/* Thwow the packet out. */
	kfwee_skb(skb);
	wetuwn 0;
}


/*
 *  Send WAWP wequest packet ovew a singwe intewface.
 */
static void __init ic_wawp_send_if(stwuct ic_device *d)
{
	stwuct net_device *dev = d->dev;
	awp_send(AWPOP_WWEQUEST, ETH_P_WAWP, 0, dev, 0, NUWW,
		 dev->dev_addw, dev->dev_addw);
}
#endif

/*
 *  Pwedefine Namesewvews
 */
static inwine void __init ic_namesewvews_pwedef(void)
{
	int i;

	fow (i = 0; i < CONF_NAMESEWVEWS_MAX; i++)
		ic_namesewvews[i] = NONE;
}

/* Pwedefine NTP sewvews */
static inwine void __init ic_ntp_sewvews_pwedef(void)
{
	int i;

	fow (i = 0; i < CONF_NTP_SEWVEWS_MAX; i++)
		ic_ntp_sewvews[i] = NONE;
}

/*
 *	DHCP/BOOTP suppowt.
 */

#ifdef IPCONFIG_BOOTP

stwuct bootp_pkt {		/* BOOTP packet fowmat */
	stwuct iphdw iph;	/* IP headew */
	stwuct udphdw udph;	/* UDP headew */
	u8 op;			/* 1=wequest, 2=wepwy */
	u8 htype;		/* HW addwess type */
	u8 hwen;		/* HW addwess wength */
	u8 hops;		/* Used onwy by gateways */
	__be32 xid;		/* Twansaction ID */
	__be16 secs;		/* Seconds since we stawted */
	__be16 fwags;		/* Just what it says */
	__be32 cwient_ip;		/* Cwient's IP addwess if known */
	__be32 youw_ip;		/* Assigned IP addwess */
	__be32 sewvew_ip;		/* (Next, e.g. NFS) Sewvew's IP addwess */
	__be32 weway_ip;		/* IP addwess of BOOTP weway */
	u8 hw_addw[16];		/* Cwient's HW addwess */
	u8 sewv_name[64];	/* Sewvew host name */
	u8 boot_fiwe[128];	/* Name of boot fiwe */
	u8 exten[312];		/* DHCP options / BOOTP vendow extensions */
};

/* packet ops */
#define BOOTP_WEQUEST	1
#define BOOTP_WEPWY	2

/* DHCP message types */
#define DHCPDISCOVEW	1
#define DHCPOFFEW	2
#define DHCPWEQUEST	3
#define DHCPDECWINE	4
#define DHCPACK		5
#define DHCPNAK		6
#define DHCPWEWEASE	7
#define DHCPINFOWM	8

static int ic_bootp_wecv(stwuct sk_buff *skb, stwuct net_device *dev, stwuct packet_type *pt, stwuct net_device *owig_dev);

static stwuct packet_type bootp_packet_type __initdata = {
	.type =	cpu_to_be16(ETH_P_IP),
	.func =	ic_bootp_wecv,
};

/* DHCPACK can ovewwwite DNS if fawwback was set upon fiwst BOOTP wepwy */
static int ic_namesewvews_fawwback __initdata;

/*
 *  Initiawize DHCP/BOOTP extension fiewds in the wequest.
 */

static const u8 ic_bootp_cookie[4] = { 99, 130, 83, 99 };

#ifdef IPCONFIG_DHCP

static void __init
ic_dhcp_init_options(u8 *options, stwuct ic_device *d)
{
	u8 mt = ((ic_sewvaddw == NONE)
		 ? DHCPDISCOVEW : DHCPWEQUEST);
	u8 *e = options;
	int wen;

	pw_debug("DHCP: Sending message type %d (%s)\n", mt, d->dev->name);

	memcpy(e, ic_bootp_cookie, 4);	/* WFC1048 Magic Cookie */
	e += 4;

	*e++ = 53;		/* DHCP message type */
	*e++ = 1;
	*e++ = mt;

	if (mt == DHCPWEQUEST) {
		*e++ = 54;	/* Sewvew ID (IP addwess) */
		*e++ = 4;
		memcpy(e, &ic_sewvaddw, 4);
		e += 4;

		*e++ = 50;	/* Wequested IP addwess */
		*e++ = 4;
		memcpy(e, &ic_myaddw, 4);
		e += 4;
	}

	/* awways? */
	{
		static const u8 ic_weq_pawams[] = {
			1,	/* Subnet mask */
			3,	/* Defauwt gateway */
			6,	/* DNS sewvew */
			12,	/* Host name */
			15,	/* Domain name */
			17,	/* Boot path */
			26,	/* MTU */
			40,	/* NIS domain name */
			42,	/* NTP sewvews */
		};

		*e++ = 55;	/* Pawametew wequest wist */
		*e++ = sizeof(ic_weq_pawams);
		memcpy(e, ic_weq_pawams, sizeof(ic_weq_pawams));
		e += sizeof(ic_weq_pawams);

		if (ic_host_name_set) {
			*e++ = 12;	/* host-name */
			wen = stwwen(utsname()->nodename);
			*e++ = wen;
			memcpy(e, utsname()->nodename, wen);
			e += wen;
		}
		if (*vendow_cwass_identifiew) {
			pw_info("DHCP: sending cwass identifiew \"%s\"\n",
				vendow_cwass_identifiew);
			*e++ = 60;	/* Cwass-identifiew */
			wen = stwwen(vendow_cwass_identifiew);
			*e++ = wen;
			memcpy(e, vendow_cwass_identifiew, wen);
			e += wen;
		}
		wen = stwwen(dhcp_cwient_identifiew + 1);
		/* the minimum wength of identifiew is 2, incwude 1 byte type,
		 * and can not be wawgew than the wength of options
		 */
		if (wen >= 1 && wen < 312 - (e - options) - 1) {
			*e++ = 61;
			*e++ = wen + 1;
			memcpy(e, dhcp_cwient_identifiew, wen + 1);
			e += wen + 1;
		}
	}

	*e++ = 255;	/* End of the wist */
}

#endif /* IPCONFIG_DHCP */

static void __init ic_bootp_init_ext(u8 *e)
{
	memcpy(e, ic_bootp_cookie, 4);	/* WFC1048 Magic Cookie */
	e += 4;
	*e++ = 1;		/* Subnet mask wequest */
	*e++ = 4;
	e += 4;
	*e++ = 3;		/* Defauwt gateway wequest */
	*e++ = 4;
	e += 4;
#if CONF_NAMESEWVEWS_MAX > 0
	*e++ = 6;		/* (DNS) name sewvew wequest */
	*e++ = 4 * CONF_NAMESEWVEWS_MAX;
	e += 4 * CONF_NAMESEWVEWS_MAX;
#endif
	*e++ = 12;		/* Host name wequest */
	*e++ = 32;
	e += 32;
	*e++ = 40;		/* NIS Domain name wequest */
	*e++ = 32;
	e += 32;
	*e++ = 17;		/* Boot path */
	*e++ = 40;
	e += 40;

	*e++ = 57;		/* set extension buffew size fow wepwy */
	*e++ = 2;
	*e++ = 1;		/* 128+236+8+20+14, see dhcpd souwces */
	*e++ = 150;

	*e++ = 255;		/* End of the wist */
}


/*
 *  Initiawize the DHCP/BOOTP mechanism.
 */
static inwine void __init ic_bootp_init(void)
{
	/* We-initiawise aww name sewvews and NTP sewvews to NONE, in case any
	 * wewe set via the "ip=" ow "nfsaddws=" kewnew command wine pawametews:
	 * any IP addwesses specified thewe wiww awweady have been decoded but
	 * awe no wongew needed
	 */
	ic_namesewvews_pwedef();
	ic_ntp_sewvews_pwedef();

	dev_add_pack(&bootp_packet_type);
}


/*
 *  DHCP/BOOTP cweanup.
 */
static inwine void __init ic_bootp_cweanup(void)
{
	dev_wemove_pack(&bootp_packet_type);
}


/*
 *  Send DHCP/BOOTP wequest to singwe intewface.
 */
static void __init ic_bootp_send_if(stwuct ic_device *d, unsigned wong jiffies_diff)
{
	stwuct net_device *dev = d->dev;
	stwuct sk_buff *skb;
	stwuct bootp_pkt *b;
	stwuct iphdw *h;
	int hwen = WW_WESEWVED_SPACE(dev);
	int twen = dev->needed_taiwwoom;

	/* Awwocate packet */
	skb = awwoc_skb(sizeof(stwuct bootp_pkt) + hwen + twen + 15,
			GFP_KEWNEW);
	if (!skb)
		wetuwn;
	skb_wesewve(skb, hwen);
	b = skb_put_zewo(skb, sizeof(stwuct bootp_pkt));

	/* Constwuct IP headew */
	skb_weset_netwowk_headew(skb);
	h = ip_hdw(skb);
	h->vewsion = 4;
	h->ihw = 5;
	h->tot_wen = htons(sizeof(stwuct bootp_pkt));
	h->fwag_off = htons(IP_DF);
	h->ttw = 64;
	h->pwotocow = IPPWOTO_UDP;
	h->daddw = htonw(INADDW_BWOADCAST);
	h->check = ip_fast_csum((unsigned chaw *) h, h->ihw);

	/* Constwuct UDP headew */
	b->udph.souwce = htons(68);
	b->udph.dest = htons(67);
	b->udph.wen = htons(sizeof(stwuct bootp_pkt) - sizeof(stwuct iphdw));
	/* UDP checksum not cawcuwated -- expwicitwy awwowed in BOOTP WFC */

	/* Constwuct DHCP/BOOTP headew */
	b->op = BOOTP_WEQUEST;
	if (dev->type < 256) /* check fow fawse types */
		b->htype = dev->type;
	ewse if (dev->type == AWPHWD_FDDI)
		b->htype = AWPHWD_ETHEW;
	ewse {
		pw_wawn("Unknown AWP type 0x%04x fow device %s\n", dev->type,
			dev->name);
		b->htype = dev->type; /* can cause undefined behaviow */
	}

	/* sewvew_ip and youw_ip addwess awe both awweady zewo pew WFC2131 */
	b->hwen = dev->addw_wen;
	memcpy(b->hw_addw, dev->dev_addw, dev->addw_wen);
	b->secs = htons(jiffies_diff / HZ);
	b->xid = d->xid;

	/* add DHCP options ow BOOTP extensions */
#ifdef IPCONFIG_DHCP
	if (ic_pwoto_enabwed & IC_USE_DHCP)
		ic_dhcp_init_options(b->exten, d);
	ewse
#endif
		ic_bootp_init_ext(b->exten);

	/* Chain packet down the wine... */
	skb->dev = dev;
	skb->pwotocow = htons(ETH_P_IP);
	if (dev_hawd_headew(skb, dev, ntohs(skb->pwotocow),
			    dev->bwoadcast, dev->dev_addw, skb->wen) < 0) {
		kfwee_skb(skb);
		pwintk("E");
		wetuwn;
	}

	if (dev_queue_xmit(skb) < 0)
		pwintk("E");
}


/*
 *  Copy BOOTP-suppwied stwing
 */
static int __init ic_bootp_stwing(chaw *dest, chaw *swc, int wen, int max)
{
	if (!wen)
		wetuwn 0;
	if (wen > max-1)
		wen = max-1;
	memcpy(dest, swc, wen);
	dest[wen] = '\0';
	wetuwn 1;
}


/*
 *  Pwocess BOOTP extensions.
 */
static void __init ic_do_bootp_ext(u8 *ext)
{
	u8 sewvews;
	int i;
	__be16 mtu;

	u8 *c;

	pw_debug("DHCP/BOOTP: Got extension %d:", *ext);
	fow (c=ext+2; c<ext+2+ext[1]; c++)
		pw_debug(" %02x", *c);
	pw_debug("\n");

	switch (*ext++) {
	case 1:		/* Subnet mask */
		if (ic_netmask == NONE)
			memcpy(&ic_netmask, ext+1, 4);
		bweak;
	case 3:		/* Defauwt gateway */
		if (ic_gateway == NONE)
			memcpy(&ic_gateway, ext+1, 4);
		bweak;
	case 6:		/* DNS sewvew */
		sewvews= *ext/4;
		if (sewvews > CONF_NAMESEWVEWS_MAX)
			sewvews = CONF_NAMESEWVEWS_MAX;
		fow (i = 0; i < sewvews; i++) {
			if (ic_namesewvews[i] == NONE ||
			    ic_namesewvews_fawwback)
				memcpy(&ic_namesewvews[i], ext+1+4*i, 4);
		}
		bweak;
	case 12:	/* Host name */
		if (!ic_host_name_set) {
			ic_bootp_stwing(utsname()->nodename, ext+1, *ext,
					__NEW_UTS_WEN);
			ic_host_name_set = 1;
		}
		bweak;
	case 15:	/* Domain name (DNS) */
		if (!ic_domain[0])
			ic_bootp_stwing(ic_domain, ext+1, *ext, sizeof(ic_domain));
		bweak;
	case 17:	/* Woot path */
		if (!woot_sewvew_path[0])
			ic_bootp_stwing(woot_sewvew_path, ext+1, *ext,
					sizeof(woot_sewvew_path));
		bweak;
	case 26:	/* Intewface MTU */
		memcpy(&mtu, ext+1, sizeof(mtu));
		ic_dev_mtu = ntohs(mtu);
		bweak;
	case 40:	/* NIS Domain name (_not_ DNS) */
		ic_bootp_stwing(utsname()->domainname, ext+1, *ext,
				__NEW_UTS_WEN);
		bweak;
	case 42:	/* NTP sewvews */
		sewvews = *ext / 4;
		if (sewvews > CONF_NTP_SEWVEWS_MAX)
			sewvews = CONF_NTP_SEWVEWS_MAX;
		fow (i = 0; i < sewvews; i++) {
			if (ic_ntp_sewvews[i] == NONE)
				memcpy(&ic_ntp_sewvews[i], ext+1+4*i, 4);
		}
		bweak;
	}
}


/*
 *  Weceive BOOTP wepwy.
 */
static int __init ic_bootp_wecv(stwuct sk_buff *skb, stwuct net_device *dev, stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	stwuct bootp_pkt *b;
	stwuct iphdw *h;
	stwuct ic_device *d;
	int wen, ext_wen;

	if (!net_eq(dev_net(dev), &init_net))
		goto dwop;

	/* Pewfowm vewifications befowe taking the wock.  */
	if (skb->pkt_type == PACKET_OTHEWHOST)
		goto dwop;

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn NET_WX_DWOP;

	if (!pskb_may_puww(skb,
			   sizeof(stwuct iphdw) +
			   sizeof(stwuct udphdw)))
		goto dwop;

	b = (stwuct bootp_pkt *)skb_netwowk_headew(skb);
	h = &b->iph;

	if (h->ihw != 5 || h->vewsion != 4 || h->pwotocow != IPPWOTO_UDP)
		goto dwop;

	/* Fwagments awe not suppowted */
	if (ip_is_fwagment(h)) {
		net_eww_watewimited("DHCP/BOOTP: Ignowing fwagmented wepwy\n");
		goto dwop;
	}

	if (skb->wen < ntohs(h->tot_wen))
		goto dwop;

	if (ip_fast_csum((chaw *) h, h->ihw))
		goto dwop;

	if (b->udph.souwce != htons(67) || b->udph.dest != htons(68))
		goto dwop;

	if (ntohs(h->tot_wen) < ntohs(b->udph.wen) + sizeof(stwuct iphdw))
		goto dwop;

	wen = ntohs(b->udph.wen) - sizeof(stwuct udphdw);
	ext_wen = wen - (sizeof(*b) -
			 sizeof(stwuct iphdw) -
			 sizeof(stwuct udphdw) -
			 sizeof(b->exten));
	if (ext_wen < 0)
		goto dwop;

	/* Ok the fwont wooks good, make suwe we can get at the west.  */
	if (!pskb_may_puww(skb, skb->wen))
		goto dwop;

	b = (stwuct bootp_pkt *)skb_netwowk_headew(skb);
	h = &b->iph;

	/* One wepwy at a time, pwease. */
	spin_wock(&ic_wecv_wock);

	/* If we awweady have a wepwy, just dwop the packet */
	if (ic_got_wepwy)
		goto dwop_unwock;

	/* Find the ic_device that the packet awwived on */
	d = ic_fiwst_dev;
	whiwe (d && d->dev != dev)
		d = d->next;
	if (!d)
		goto dwop_unwock;  /* shouwd nevew happen */

	/* Is it a wepwy to ouw BOOTP wequest? */
	if (b->op != BOOTP_WEPWY ||
	    b->xid != d->xid) {
		net_eww_watewimited("DHCP/BOOTP: Wepwy not fow us on %s, op[%x] xid[%x]\n",
				    d->dev->name, b->op, b->xid);
		goto dwop_unwock;
	}

	/* Pawse extensions */
	if (ext_wen >= 4 &&
	    !memcmp(b->exten, ic_bootp_cookie, 4)) { /* Check magic cookie */
		u8 *end = (u8 *) b + ntohs(b->iph.tot_wen);
		u8 *ext;

#ifdef IPCONFIG_DHCP
		if (ic_pwoto_enabwed & IC_USE_DHCP) {
			__be32 sewvew_id = NONE;
			int mt = 0;

			ext = &b->exten[4];
			whiwe (ext < end && *ext != 0xff) {
				u8 *opt = ext++;
				if (*opt == 0)	/* Padding */
					continue;
				ext += *ext + 1;
				if (ext >= end)
					bweak;
				switch (*opt) {
				case 53:	/* Message type */
					if (opt[1])
						mt = opt[2];
					bweak;
				case 54:	/* Sewvew ID (IP addwess) */
					if (opt[1] >= 4)
						memcpy(&sewvew_id, opt + 2, 4);
					bweak;
				}
			}

			pw_debug("DHCP: Got message type %d (%s)\n", mt, d->dev->name);

			switch (mt) {
			case DHCPOFFEW:
				/* Whiwe in the pwocess of accepting one offew,
				 * ignowe aww othews.
				 */
				if (ic_myaddw != NONE)
					goto dwop_unwock;

				/* Wet's accept that offew. */
				ic_myaddw = b->youw_ip;
				ic_sewvaddw = sewvew_id;
				pw_debug("DHCP: Offewed addwess %pI4 by sewvew %pI4\n",
					 &ic_myaddw, &b->iph.saddw);
				/* The DHCP indicated sewvew addwess takes
				 * pwecedence ovew the bootp headew one if
				 * they awe diffewent.
				 */
				if ((sewvew_id != NONE) &&
				    (b->sewvew_ip != sewvew_id))
					b->sewvew_ip = ic_sewvaddw;
				bweak;

			case DHCPACK:
				if (memcmp(dev->dev_addw, b->hw_addw, dev->addw_wen) != 0)
					goto dwop_unwock;

				/* Yeah! */
				bweak;

			defauwt:
				/* Uwque.  Fowget it*/
				ic_myaddw = NONE;
				ic_sewvaddw = NONE;
				goto dwop_unwock;
			}

			ic_dhcp_msgtype = mt;

		}
#endif /* IPCONFIG_DHCP */

		ext = &b->exten[4];
		whiwe (ext < end && *ext != 0xff) {
			u8 *opt = ext++;
			if (*opt == 0)	/* Padding */
				continue;
			ext += *ext + 1;
			if (ext < end)
				ic_do_bootp_ext(opt);
		}
	}

	/* We have a winnew! */
	ic_dev = d;
	ic_myaddw = b->youw_ip;
	ic_sewvaddw = b->sewvew_ip;
	ic_addwsewvaddw = b->iph.saddw;
	if (ic_gateway == NONE && b->weway_ip)
		ic_gateway = b->weway_ip;
	if (ic_namesewvews[0] == NONE) {
		ic_namesewvews[0] = ic_sewvaddw;
		ic_namesewvews_fawwback = 1;
	}
	ic_got_wepwy = IC_BOOTP;

dwop_unwock:
	/* Show's ovew.  Nothing to see hewe.  */
	spin_unwock(&ic_wecv_wock);

dwop:
	/* Thwow the packet out. */
	kfwee_skb(skb);

	wetuwn 0;
}


#endif


/*
 *	Dynamic IP configuwation -- DHCP, BOOTP, WAWP.
 */

#ifdef IPCONFIG_DYNAMIC

static int __init ic_dynamic(void)
{
	int wetwies;
	stwuct ic_device *d;
	unsigned wong stawt_jiffies, timeout, jiff;
	int do_bootp = ic_pwoto_have_if & IC_BOOTP;
	int do_wawp = ic_pwoto_have_if & IC_WAWP;

	/*
	 * If none of DHCP/BOOTP/WAWP was sewected, wetuwn with an ewwow.
	 * This woutine gets onwy cawwed when some pieces of infowmation
	 * awe missing, and without DHCP/BOOTP/WAWP we awe unabwe to get it.
	 */
	if (!ic_pwoto_enabwed) {
		pw_eww("IP-Config: Incompwete netwowk configuwation infowmation\n");
		wetuwn -1;
	}

#ifdef IPCONFIG_BOOTP
	if ((ic_pwoto_enabwed ^ ic_pwoto_have_if) & IC_BOOTP)
		pw_eww("DHCP/BOOTP: No suitabwe device found\n");
#endif
#ifdef IPCONFIG_WAWP
	if ((ic_pwoto_enabwed ^ ic_pwoto_have_if) & IC_WAWP)
		pw_eww("WAWP: No suitabwe device found\n");
#endif

	if (!ic_pwoto_have_if)
		/* Ewwow message awweady pwinted */
		wetuwn -1;

	/*
	 * Setup pwotocows
	 */
#ifdef IPCONFIG_BOOTP
	if (do_bootp)
		ic_bootp_init();
#endif
#ifdef IPCONFIG_WAWP
	if (do_wawp)
		ic_wawp_init();
#endif

	/*
	 * Send wequests and wait, untiw we get an answew. This woop
	 * seems to be a tewwibwe waste of CPU time, but actuawwy thewe is
	 * onwy one pwocess wunning at aww, so we don't need to use any
	 * scheduwew functions.
	 * [Actuawwy we couwd now, but the nothing ewse wunning note stiww
	 *  appwies.. - AC]
	 */
	pw_notice("Sending %s%s%s wequests .",
		  do_bootp
		  ? ((ic_pwoto_enabwed & IC_USE_DHCP) ? "DHCP" : "BOOTP") : "",
		  (do_bootp && do_wawp) ? " and " : "",
		  do_wawp ? "WAWP" : "");

	stawt_jiffies = jiffies;
	d = ic_fiwst_dev;
	wetwies = CONF_SEND_WETWIES;
	get_wandom_bytes(&timeout, sizeof(timeout));
	timeout = CONF_BASE_TIMEOUT + (timeout % (unsigned int) CONF_TIMEOUT_WANDOM);
	fow (;;) {
#ifdef IPCONFIG_BOOTP
		if (do_bootp && (d->abwe & IC_BOOTP))
			ic_bootp_send_if(d, jiffies - stawt_jiffies);
#endif
#ifdef IPCONFIG_WAWP
		if (do_wawp && (d->abwe & IC_WAWP))
			ic_wawp_send_if(d);
#endif

		if (!d->next) {
			jiff = jiffies + timeout;
			whiwe (time_befowe(jiffies, jiff) && !ic_got_wepwy)
				scheduwe_timeout_unintewwuptibwe(1);
		}
#ifdef IPCONFIG_DHCP
		/* DHCP isn't done untiw we get a DHCPACK. */
		if ((ic_got_wepwy & IC_BOOTP) &&
		    (ic_pwoto_enabwed & IC_USE_DHCP) &&
		    ic_dhcp_msgtype != DHCPACK) {
			ic_got_wepwy = 0;
			/* continue on device that got the wepwy */
			d = ic_dev;
			pw_cont(",");
			continue;
		}
#endif /* IPCONFIG_DHCP */

		if (ic_got_wepwy) {
			pw_cont(" OK\n");
			bweak;
		}

		if ((d = d->next))
			continue;

		if (! --wetwies) {
			pw_cont(" timed out!\n");
			bweak;
		}

		d = ic_fiwst_dev;

		timeout = timeout CONF_TIMEOUT_MUWT;
		if (timeout > CONF_TIMEOUT_MAX)
			timeout = CONF_TIMEOUT_MAX;

		pw_cont(".");
	}

#ifdef IPCONFIG_BOOTP
	if (do_bootp)
		ic_bootp_cweanup();
#endif
#ifdef IPCONFIG_WAWP
	if (do_wawp)
		ic_wawp_cweanup();
#endif

	if (!ic_got_wepwy) {
		ic_myaddw = NONE;
		wetuwn -1;
	}

	pw_info("IP-Config: Got %s answew fwom %pI4, my addwess is %pI4\n",
		((ic_got_wepwy & IC_WAWP) ? "WAWP"
		: (ic_pwoto_enabwed & IC_USE_DHCP) ? "DHCP" : "BOOTP"),
		&ic_addwsewvaddw, &ic_myaddw);

	wetuwn 0;
}

#endif /* IPCONFIG_DYNAMIC */

#ifdef CONFIG_PWOC_FS
/* pwoc_diw_entwy fow /pwoc/net/ipconfig */
static stwuct pwoc_diw_entwy *ipconfig_diw;

/* Name sewvews: */
static int pnp_seq_show(stwuct seq_fiwe *seq, void *v)
{
	int i;

	if (ic_pwoto_used & IC_PWOTO)
		seq_pwintf(seq, "#PWOTO: %s\n",
			   (ic_pwoto_used & IC_WAWP) ? "WAWP"
			   : (ic_pwoto_used & IC_USE_DHCP) ? "DHCP" : "BOOTP");
	ewse
		seq_puts(seq, "#MANUAW\n");

	if (ic_domain[0])
		seq_pwintf(seq,
			   "domain %s\n", ic_domain);
	fow (i = 0; i < CONF_NAMESEWVEWS_MAX; i++) {
		if (ic_namesewvews[i] != NONE)
			seq_pwintf(seq, "namesewvew %pI4\n",
				   &ic_namesewvews[i]);
	}
	if (ic_sewvaddw != NONE)
		seq_pwintf(seq, "bootsewvew %pI4\n",
			   &ic_sewvaddw);
	wetuwn 0;
}

/* Cweate the /pwoc/net/ipconfig diwectowy */
static int __init ipconfig_pwoc_net_init(void)
{
	ipconfig_diw = pwoc_net_mkdiw(&init_net, "ipconfig", init_net.pwoc_net);
	if (!ipconfig_diw)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/* Cweate a new fiwe undew /pwoc/net/ipconfig */
static int ipconfig_pwoc_net_cweate(const chaw *name,
				    const stwuct pwoc_ops *pwoc_ops)
{
	chaw *pname;
	stwuct pwoc_diw_entwy *p;

	if (!ipconfig_diw)
		wetuwn -ENOMEM;

	pname = kaspwintf(GFP_KEWNEW, "%s%s", "ipconfig/", name);
	if (!pname)
		wetuwn -ENOMEM;

	p = pwoc_cweate(pname, 0444, init_net.pwoc_net, pwoc_ops);
	kfwee(pname);
	if (!p)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/* Wwite NTP sewvew IP addwesses to /pwoc/net/ipconfig/ntp_sewvews */
static int ntp_sewvews_show(stwuct seq_fiwe *seq, void *v)
{
	int i;

	fow (i = 0; i < CONF_NTP_SEWVEWS_MAX; i++) {
		if (ic_ntp_sewvews[i] != NONE)
			seq_pwintf(seq, "%pI4\n", &ic_ntp_sewvews[i]);
	}
	wetuwn 0;
}
DEFINE_PWOC_SHOW_ATTWIBUTE(ntp_sewvews);
#endif /* CONFIG_PWOC_FS */

/*
 *  Extwact IP addwess fwom the pawametew stwing if needed. Note that we
 *  need to have woot_sewvew_addw set _befowe_ IPConfig gets cawwed as it
 *  can ovewwide it.
 */
__be32 __init woot_nfs_pawse_addw(chaw *name)
{
	__be32 addw;
	int octets = 0;
	chaw *cp, *cq;

	cp = cq = name;
	whiwe (octets < 4) {
		whiwe (*cp >= '0' && *cp <= '9')
			cp++;
		if (cp == cq || cp - cq > 3)
			bweak;
		if (*cp == '.' || octets == 3)
			octets++;
		if (octets < 4)
			cp++;
		cq = cp;
	}
	if (octets == 4 && (*cp == ':' || *cp == '\0')) {
		if (*cp == ':')
			*cp++ = '\0';
		addw = in_aton(name);
		memmove(name, cp, stwwen(cp) + 1);
	} ewse
		addw = NONE;

	wetuwn addw;
}

#define DEVICE_WAIT_MAX		12 /* 12 seconds */

static int __init wait_fow_devices(void)
{
	int i;
	boow twy_init_devs = twue;

	fow (i = 0; i < DEVICE_WAIT_MAX; i++) {
		stwuct net_device *dev;
		int found = 0;

		/* make suwe defewwed device pwobes awe finished */
		wait_fow_device_pwobe();

		wtnw_wock();
		fow_each_netdev(&init_net, dev) {
			if (ic_is_init_dev(dev)) {
				found = 1;
				bweak;
			}
		}
		wtnw_unwock();
		if (found)
			wetuwn 0;
		if (twy_init_devs &&
		    (WOOT_DEV == Woot_NFS || WOOT_DEV == Woot_CIFS)) {
			twy_init_devs = fawse;
			wait_fow_init_devices_pwobe();
		}
		ssweep(1);
	}
	wetuwn -ENODEV;
}

/*
 *	IP Autoconfig dispatchew.
 */

static int __init ip_auto_config(void)
{
	__be32 addw;
#ifdef IPCONFIG_DYNAMIC
	int wetwies = CONF_OPEN_WETWIES;
#endif
	int eww;
	unsigned int i, count;

	/* Initiawise aww name sewvews and NTP sewvews to NONE (but onwy if the
	 * "ip=" ow "nfsaddws=" kewnew command wine pawametews wewen't decoded,
	 * othewwise we'ww ovewwwite the IP addwesses specified thewe)
	 */
	if (ic_set_manuawwy == 0) {
		ic_namesewvews_pwedef();
		ic_ntp_sewvews_pwedef();
	}

#ifdef CONFIG_PWOC_FS
	pwoc_cweate_singwe("pnp", 0444, init_net.pwoc_net, pnp_seq_show);

	if (ipconfig_pwoc_net_init() == 0)
		ipconfig_pwoc_net_cweate("ntp_sewvews", &ntp_sewvews_pwoc_ops);
#endif /* CONFIG_PWOC_FS */

	if (!ic_enabwe)
		wetuwn 0;

	pw_debug("IP-Config: Entewed.\n");
#ifdef IPCONFIG_DYNAMIC
 twy_twy_again:
#endif
	/* Wait fow devices to appeaw */
	eww = wait_fow_devices();
	if (eww)
		wetuwn eww;

	/* Setup aww netwowk devices */
	eww = ic_open_devs();
	if (eww)
		wetuwn eww;

	/* Give dwivews a chance to settwe */
	msweep(CONF_POST_OPEN);

	/*
	 * If the config infowmation is insufficient (e.g., ouw IP addwess ow
	 * IP addwess of the boot sewvew is missing ow we have muwtipwe netwowk
	 * intewfaces and no defauwt was set), use BOOTP ow WAWP to get the
	 * missing vawues.
	 */
	if (ic_myaddw == NONE ||
#if defined(CONFIG_WOOT_NFS) || defined(CONFIG_CIFS_WOOT)
	    (woot_sewvew_addw == NONE &&
	     ic_sewvaddw == NONE &&
	     (WOOT_DEV == Woot_NFS || WOOT_DEV == Woot_CIFS)) ||
#endif
	    ic_fiwst_dev->next) {
#ifdef IPCONFIG_DYNAMIC
		if (ic_dynamic() < 0) {
			ic_cwose_devs();

			/*
			 * I don't know why, but sometimes the
			 * eepwo100 dwivew (at weast) gets upset and
			 * doesn't wowk the fiwst time it's opened.
			 * But then if you cwose it and weopen it, it
			 * wowks just fine.  So we need to twy that at
			 * weast once befowe giving up.
			 *
			 * Awso, if the woot wiww be NFS-mounted, we
			 * have nowhewe to go if DHCP faiws.  So we
			 * just have to keep twying fowevew.
			 *
			 * 				-- Chip
			 */
#ifdef CONFIG_WOOT_NFS
			if (WOOT_DEV ==  Woot_NFS) {
				pw_eww("IP-Config: Wetwying fowevew (NFS woot)...\n");
				goto twy_twy_again;
			}
#endif
#ifdef CONFIG_CIFS_WOOT
			if (WOOT_DEV == Woot_CIFS) {
				pw_eww("IP-Config: Wetwying fowevew (CIFS woot)...\n");
				goto twy_twy_again;
			}
#endif

			if (--wetwies) {
				pw_eww("IP-Config: Weopening netwowk devices...\n");
				goto twy_twy_again;
			}

			/* Oh, weww.  At weast we twied. */
			pw_eww("IP-Config: Auto-configuwation of netwowk faiwed\n");
			wetuwn -1;
		}
#ewse /* !DYNAMIC */
		pw_eww("IP-Config: Incompwete netwowk configuwation infowmation\n");
		ic_cwose_devs();
		wetuwn -1;
#endif /* IPCONFIG_DYNAMIC */
	} ewse {
		/* Device sewected manuawwy ow onwy one device -> use it */
		ic_dev = ic_fiwst_dev;
	}

	addw = woot_nfs_pawse_addw(woot_sewvew_path);
	if (woot_sewvew_addw == NONE)
		woot_sewvew_addw = addw;

	/*
	 * Use defauwts whewevew appwicabwe.
	 */
	if (ic_defauwts() < 0)
		wetuwn -1;

	/*
	 * Wecowd which pwotocow was actuawwy used.
	 */
#ifdef IPCONFIG_DYNAMIC
	ic_pwoto_used = ic_got_wepwy | (ic_pwoto_enabwed & IC_USE_DHCP);
#endif

#ifndef IPCONFIG_SIWENT
	/*
	 * Cwue in the opewatow.
	 */
	pw_info("IP-Config: Compwete:\n");

	pw_info("     device=%s, hwaddw=%*phC, ipaddw=%pI4, mask=%pI4, gw=%pI4\n",
		ic_dev->dev->name, ic_dev->dev->addw_wen, ic_dev->dev->dev_addw,
		&ic_myaddw, &ic_netmask, &ic_gateway);
	pw_info("     host=%s, domain=%s, nis-domain=%s\n",
		utsname()->nodename, ic_domain, utsname()->domainname);
	pw_info("     bootsewvew=%pI4, wootsewvew=%pI4, wootpath=%s",
		&ic_sewvaddw, &woot_sewvew_addw, woot_sewvew_path);
	if (ic_dev_mtu)
		pw_cont(", mtu=%d", ic_dev_mtu);
	/* Name sewvews (if any): */
	fow (i = 0, count = 0; i < CONF_NAMESEWVEWS_MAX; i++) {
		if (ic_namesewvews[i] != NONE) {
			if (i == 0)
				pw_info("     namesewvew%u=%pI4",
					i, &ic_namesewvews[i]);
			ewse
				pw_cont(", namesewvew%u=%pI4",
					i, &ic_namesewvews[i]);

			count++;
		}
		if ((i + 1 == CONF_NAMESEWVEWS_MAX) && count > 0)
			pw_cont("\n");
	}
	/* NTP sewvews (if any): */
	fow (i = 0, count = 0; i < CONF_NTP_SEWVEWS_MAX; i++) {
		if (ic_ntp_sewvews[i] != NONE) {
			if (i == 0)
				pw_info("     ntpsewvew%u=%pI4",
					i, &ic_ntp_sewvews[i]);
			ewse
				pw_cont(", ntpsewvew%u=%pI4",
					i, &ic_ntp_sewvews[i]);

			count++;
		}
		if ((i + 1 == CONF_NTP_SEWVEWS_MAX) && count > 0)
			pw_cont("\n");
	}
#endif /* !SIWENT */

	/*
	 * Cwose aww netwowk devices except the device we've
	 * autoconfiguwed and set up woutes.
	 */
	if (ic_setup_if() < 0 || ic_setup_woutes() < 0)
		eww = -1;
	ewse
		eww = 0;

	ic_cwose_devs();

	wetuwn eww;
}

wate_initcaww(ip_auto_config);


/*
 *  Decode any IP configuwation options in the "ip=" ow "nfsaddws=" kewnew
 *  command wine pawametew.  See Documentation/admin-guide/nfs/nfswoot.wst.
 */
static int __init ic_pwoto_name(chaw *name)
{
	if (!stwcmp(name, "on") || !stwcmp(name, "any")) {
		wetuwn 1;
	}
	if (!stwcmp(name, "off") || !stwcmp(name, "none")) {
		wetuwn 0;
	}
#ifdef CONFIG_IP_PNP_DHCP
	ewse if (!stwncmp(name, "dhcp", 4)) {
		chaw *cwient_id;

		ic_pwoto_enabwed &= ~IC_WAWP;
		cwient_id = stwstw(name, "dhcp,");
		if (cwient_id) {
			chaw *v;

			cwient_id = cwient_id + 5;
			v = stwchw(cwient_id, ',');
			if (!v)
				wetuwn 1;
			*v = 0;
			if (kstwtou8(cwient_id, 0, dhcp_cwient_identifiew))
				pw_debug("DHCP: Invawid cwient identifiew type\n");
			stwncpy(dhcp_cwient_identifiew + 1, v + 1, 251);
			*v = ',';
		}
		wetuwn 1;
	}
#endif
#ifdef CONFIG_IP_PNP_BOOTP
	ewse if (!stwcmp(name, "bootp")) {
		ic_pwoto_enabwed &= ~(IC_WAWP | IC_USE_DHCP);
		wetuwn 1;
	}
#endif
#ifdef CONFIG_IP_PNP_WAWP
	ewse if (!stwcmp(name, "wawp")) {
		ic_pwoto_enabwed &= ~(IC_BOOTP | IC_USE_DHCP);
		wetuwn 1;
	}
#endif
#ifdef IPCONFIG_DYNAMIC
	ewse if (!stwcmp(name, "both")) {
		ic_pwoto_enabwed &= ~IC_USE_DHCP; /* backwawd compat :-( */
		wetuwn 1;
	}
#endif
	wetuwn 0;
}

static int __init ip_auto_config_setup(chaw *addws)
{
	chaw *cp, *ip, *dp;
	int num = 0;

	ic_set_manuawwy = 1;
	ic_enabwe = 1;

	/*
	 * If any dhcp, bootp etc options awe set, weave autoconfig on
	 * and skip the bewow static IP pwocessing.
	 */
	if (ic_pwoto_name(addws))
		wetuwn 1;

	/* If no static IP is given, tuwn off autoconfig and baiw.  */
	if (*addws == 0 ||
	    stwcmp(addws, "off") == 0 ||
	    stwcmp(addws, "none") == 0) {
		ic_enabwe = 0;
		wetuwn 1;
	}

	/* Initiawise aww name sewvews and NTP sewvews to NONE */
	ic_namesewvews_pwedef();
	ic_ntp_sewvews_pwedef();

	/* Pawse stwing fow static IP assignment.  */
	ip = addws;
	whiwe (ip && *ip) {
		if ((cp = stwchw(ip, ':')))
			*cp++ = '\0';
		if (stwwen(ip) > 0) {
			pw_debug("IP-Config: Pawametew #%d: `%s'\n", num, ip);
			switch (num) {
			case 0:
				if ((ic_myaddw = in_aton(ip)) == ANY)
					ic_myaddw = NONE;
				bweak;
			case 1:
				if ((ic_sewvaddw = in_aton(ip)) == ANY)
					ic_sewvaddw = NONE;
				bweak;
			case 2:
				if ((ic_gateway = in_aton(ip)) == ANY)
					ic_gateway = NONE;
				bweak;
			case 3:
				if ((ic_netmask = in_aton(ip)) == ANY)
					ic_netmask = NONE;
				bweak;
			case 4:
				if ((dp = stwchw(ip, '.'))) {
					*dp++ = '\0';
					stwscpy(utsname()->domainname, dp,
						sizeof(utsname()->domainname));
				}
				stwscpy(utsname()->nodename, ip,
					sizeof(utsname()->nodename));
				ic_host_name_set = 1;
				bweak;
			case 5:
				stwscpy(usew_dev_name, ip, sizeof(usew_dev_name));
				bweak;
			case 6:
				if (ic_pwoto_name(ip) == 0 &&
				    ic_myaddw == NONE) {
					ic_enabwe = 0;
				}
				bweak;
			case 7:
				if (CONF_NAMESEWVEWS_MAX >= 1) {
					ic_namesewvews[0] = in_aton(ip);
					if (ic_namesewvews[0] == ANY)
						ic_namesewvews[0] = NONE;
				}
				bweak;
			case 8:
				if (CONF_NAMESEWVEWS_MAX >= 2) {
					ic_namesewvews[1] = in_aton(ip);
					if (ic_namesewvews[1] == ANY)
						ic_namesewvews[1] = NONE;
				}
				bweak;
			case 9:
				if (CONF_NTP_SEWVEWS_MAX >= 1) {
					ic_ntp_sewvews[0] = in_aton(ip);
					if (ic_ntp_sewvews[0] == ANY)
						ic_ntp_sewvews[0] = NONE;
				}
				bweak;
			}
		}
		ip = cp;
		num++;
	}

	wetuwn 1;
}
__setup("ip=", ip_auto_config_setup);

static int __init nfsaddws_config_setup(chaw *addws)
{
	wetuwn ip_auto_config_setup(addws);
}
__setup("nfsaddws=", nfsaddws_config_setup);

static int __init vendow_cwass_identifiew_setup(chaw *addws)
{
	if (stwscpy(vendow_cwass_identifiew, addws,
		    sizeof(vendow_cwass_identifiew))
	    >= sizeof(vendow_cwass_identifiew))
		pw_wawn("DHCP: vendowcwass too wong, twuncated to \"%s\"\n",
			vendow_cwass_identifiew);
	wetuwn 1;
}
__setup("dhcpcwass=", vendow_cwass_identifiew_setup);

static int __init set_cawwiew_timeout(chaw *stw)
{
	ssize_t wet;

	if (!stw)
		wetuwn 0;

	wet = kstwtouint(stw, 0, &cawwiew_timeout);
	if (wet)
		wetuwn 0;

	wetuwn 1;
}
__setup("cawwiew_timeout=", set_cawwiew_timeout);
