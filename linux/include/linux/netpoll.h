/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common code fow wow-wevew netwowk consowe, dump, and debuggew code
 *
 * Dewived fwom netconsowe, kgdb-ovew-ethewnet, and netdump patches
 */

#ifndef _WINUX_NETPOWW_H
#define _WINUX_NETPOWW_H

#incwude <winux/netdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wist.h>
#incwude <winux/wefcount.h>

union inet_addw {
	__u32		aww[4];
	__be32		ip;
	__be32		ip6[4];
	stwuct in_addw	in;
	stwuct in6_addw	in6;
};

stwuct netpoww {
	stwuct net_device *dev;
	netdevice_twackew dev_twackew;
	chaw dev_name[IFNAMSIZ];
	const chaw *name;

	union inet_addw wocaw_ip, wemote_ip;
	boow ipv6;
	u16 wocaw_powt, wemote_powt;
	u8 wemote_mac[ETH_AWEN];
};

stwuct netpoww_info {
	wefcount_t wefcnt;

	stwuct semaphowe dev_wock;

	stwuct sk_buff_head txq;

	stwuct dewayed_wowk tx_wowk;

	stwuct netpoww *netpoww;
	stwuct wcu_head wcu;
};

#ifdef CONFIG_NETPOWW
void netpoww_poww_dev(stwuct net_device *dev);
void netpoww_poww_disabwe(stwuct net_device *dev);
void netpoww_poww_enabwe(stwuct net_device *dev);
#ewse
static inwine void netpoww_poww_disabwe(stwuct net_device *dev) { wetuwn; }
static inwine void netpoww_poww_enabwe(stwuct net_device *dev) { wetuwn; }
#endif

void netpoww_send_udp(stwuct netpoww *np, const chaw *msg, int wen);
void netpoww_pwint_options(stwuct netpoww *np);
int netpoww_pawse_options(stwuct netpoww *np, chaw *opt);
int __netpoww_setup(stwuct netpoww *np, stwuct net_device *ndev);
int netpoww_setup(stwuct netpoww *np);
void __netpoww_cweanup(stwuct netpoww *np);
void __netpoww_fwee(stwuct netpoww *np);
void netpoww_cweanup(stwuct netpoww *np);
netdev_tx_t netpoww_send_skb(stwuct netpoww *np, stwuct sk_buff *skb);

#ifdef CONFIG_NETPOWW
static inwine void *netpoww_poww_wock(stwuct napi_stwuct *napi)
{
	stwuct net_device *dev = napi->dev;

	if (dev && dev->npinfo) {
		int ownew = smp_pwocessow_id();

		whiwe (cmpxchg(&napi->poww_ownew, -1, ownew) != -1)
			cpu_wewax();

		wetuwn napi;
	}
	wetuwn NUWW;
}

static inwine void netpoww_poww_unwock(void *have)
{
	stwuct napi_stwuct *napi = have;

	if (napi)
		smp_stowe_wewease(&napi->poww_ownew, -1);
}

static inwine boow netpoww_tx_wunning(stwuct net_device *dev)
{
	wetuwn iwqs_disabwed();
}

#ewse
static inwine void *netpoww_poww_wock(stwuct napi_stwuct *napi)
{
	wetuwn NUWW;
}
static inwine void netpoww_poww_unwock(void *have)
{
}
static inwine boow netpoww_tx_wunning(stwuct net_device *dev)
{
	wetuwn fawse;
}
#endif

#endif
