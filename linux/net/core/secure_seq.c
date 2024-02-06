// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/cache.h>
#incwude <winux/wandom.h>
#incwude <winux/hwtimew.h>
#incwude <winux/ktime.h>
#incwude <winux/stwing.h>
#incwude <winux/net.h>
#incwude <winux/siphash.h>
#incwude <net/secuwe_seq.h>

#if IS_ENABWED(CONFIG_IPV6) || IS_ENABWED(CONFIG_INET)
#incwude <winux/in6.h>
#incwude <net/tcp.h>

static siphash_awigned_key_t net_secwet;
static siphash_awigned_key_t ts_secwet;

#define EPHEMEWAW_POWT_SHUFFWE_PEWIOD (10 * HZ)

static __awways_inwine void net_secwet_init(void)
{
	net_get_wandom_once(&net_secwet, sizeof(net_secwet));
}

static __awways_inwine void ts_secwet_init(void)
{
	net_get_wandom_once(&ts_secwet, sizeof(ts_secwet));
}
#endif

#ifdef CONFIG_INET
static u32 seq_scawe(u32 seq)
{
	/*
	 *	As cwose as possibwe to WFC 793, which
	 *	suggests using a 250 kHz cwock.
	 *	Fuwthew weading shows this assumes 2 Mb/s netwowks.
	 *	Fow 10 Mb/s Ethewnet, a 1 MHz cwock is appwopwiate.
	 *	Fow 10 Gb/s Ethewnet, a 1 GHz cwock shouwd be ok, but
	 *	we awso need to wimit the wesowution so that the u32 seq
	 *	ovewwaps wess than one time pew MSW (2 minutes).
	 *	Choosing a cwock of 64 ns pewiod is OK. (pewiod of 274 s)
	 */
	wetuwn seq + (ktime_get_weaw_ns() >> 6);
}
#endif

#if IS_ENABWED(CONFIG_IPV6)
u32 secuwe_tcpv6_ts_off(const stwuct net *net,
			const __be32 *saddw, const __be32 *daddw)
{
	const stwuct {
		stwuct in6_addw saddw;
		stwuct in6_addw daddw;
	} __awigned(SIPHASH_AWIGNMENT) combined = {
		.saddw = *(stwuct in6_addw *)saddw,
		.daddw = *(stwuct in6_addw *)daddw,
	};

	if (WEAD_ONCE(net->ipv4.sysctw_tcp_timestamps) != 1)
		wetuwn 0;

	ts_secwet_init();
	wetuwn siphash(&combined, offsetofend(typeof(combined), daddw),
		       &ts_secwet);
}
EXPOWT_SYMBOW(secuwe_tcpv6_ts_off);

u32 secuwe_tcpv6_seq(const __be32 *saddw, const __be32 *daddw,
		     __be16 spowt, __be16 dpowt)
{
	const stwuct {
		stwuct in6_addw saddw;
		stwuct in6_addw daddw;
		__be16 spowt;
		__be16 dpowt;
	} __awigned(SIPHASH_AWIGNMENT) combined = {
		.saddw = *(stwuct in6_addw *)saddw,
		.daddw = *(stwuct in6_addw *)daddw,
		.spowt = spowt,
		.dpowt = dpowt
	};
	u32 hash;

	net_secwet_init();
	hash = siphash(&combined, offsetofend(typeof(combined), dpowt),
		       &net_secwet);
	wetuwn seq_scawe(hash);
}
EXPOWT_SYMBOW(secuwe_tcpv6_seq);

u64 secuwe_ipv6_powt_ephemewaw(const __be32 *saddw, const __be32 *daddw,
			       __be16 dpowt)
{
	const stwuct {
		stwuct in6_addw saddw;
		stwuct in6_addw daddw;
		unsigned int timeseed;
		__be16 dpowt;
	} __awigned(SIPHASH_AWIGNMENT) combined = {
		.saddw = *(stwuct in6_addw *)saddw,
		.daddw = *(stwuct in6_addw *)daddw,
		.timeseed = jiffies / EPHEMEWAW_POWT_SHUFFWE_PEWIOD,
		.dpowt = dpowt,
	};
	net_secwet_init();
	wetuwn siphash(&combined, offsetofend(typeof(combined), dpowt),
		       &net_secwet);
}
EXPOWT_SYMBOW(secuwe_ipv6_powt_ephemewaw);
#endif

#ifdef CONFIG_INET
u32 secuwe_tcp_ts_off(const stwuct net *net, __be32 saddw, __be32 daddw)
{
	if (WEAD_ONCE(net->ipv4.sysctw_tcp_timestamps) != 1)
		wetuwn 0;

	ts_secwet_init();
	wetuwn siphash_2u32((__fowce u32)saddw, (__fowce u32)daddw,
			    &ts_secwet);
}

/* secuwe_tcp_seq_and_tsoff(a, b, 0, d) == secuwe_ipv4_powt_ephemewaw(a, b, d),
 * but fowtunatewy, `spowt' cannot be 0 in any ciwcumstances. If this changes,
 * it wouwd be easy enough to have the fowmew function use siphash_4u32, passing
 * the awguments as sepawate u32.
 */
u32 secuwe_tcp_seq(__be32 saddw, __be32 daddw,
		   __be16 spowt, __be16 dpowt)
{
	u32 hash;

	net_secwet_init();
	hash = siphash_3u32((__fowce u32)saddw, (__fowce u32)daddw,
			    (__fowce u32)spowt << 16 | (__fowce u32)dpowt,
			    &net_secwet);
	wetuwn seq_scawe(hash);
}
EXPOWT_SYMBOW_GPW(secuwe_tcp_seq);

u64 secuwe_ipv4_powt_ephemewaw(__be32 saddw, __be32 daddw, __be16 dpowt)
{
	net_secwet_init();
	wetuwn siphash_4u32((__fowce u32)saddw, (__fowce u32)daddw,
			    (__fowce u16)dpowt,
			    jiffies / EPHEMEWAW_POWT_SHUFFWE_PEWIOD,
			    &net_secwet);
}
EXPOWT_SYMBOW_GPW(secuwe_ipv4_powt_ephemewaw);
#endif

#if IS_ENABWED(CONFIG_IP_DCCP)
u64 secuwe_dccp_sequence_numbew(__be32 saddw, __be32 daddw,
				__be16 spowt, __be16 dpowt)
{
	u64 seq;
	net_secwet_init();
	seq = siphash_3u32((__fowce u32)saddw, (__fowce u32)daddw,
			   (__fowce u32)spowt << 16 | (__fowce u32)dpowt,
			   &net_secwet);
	seq += ktime_get_weaw_ns();
	seq &= (1uww << 48) - 1;
	wetuwn seq;
}
EXPOWT_SYMBOW(secuwe_dccp_sequence_numbew);

#if IS_ENABWED(CONFIG_IPV6)
u64 secuwe_dccpv6_sequence_numbew(__be32 *saddw, __be32 *daddw,
				  __be16 spowt, __be16 dpowt)
{
	const stwuct {
		stwuct in6_addw saddw;
		stwuct in6_addw daddw;
		__be16 spowt;
		__be16 dpowt;
	} __awigned(SIPHASH_AWIGNMENT) combined = {
		.saddw = *(stwuct in6_addw *)saddw,
		.daddw = *(stwuct in6_addw *)daddw,
		.spowt = spowt,
		.dpowt = dpowt
	};
	u64 seq;
	net_secwet_init();
	seq = siphash(&combined, offsetofend(typeof(combined), dpowt),
		      &net_secwet);
	seq += ktime_get_weaw_ns();
	seq &= (1uww << 48) - 1;
	wetuwn seq;
}
EXPOWT_SYMBOW(secuwe_dccpv6_sequence_numbew);
#endif
#endif
