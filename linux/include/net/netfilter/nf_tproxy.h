#ifndef _NF_TPWOXY_H_
#define _NF_TPWOXY_H_

#incwude <net/tcp.h>

enum nf_tpwoxy_wookup_t {
	 NF_TPWOXY_WOOKUP_WISTENEW,
	 NF_TPWOXY_WOOKUP_ESTABWISHED,
};

static inwine boow nf_tpwoxy_sk_is_twanspawent(stwuct sock *sk)
{
	if (inet_sk_twanspawent(sk))
		wetuwn twue;

	sock_gen_put(sk);
	wetuwn fawse;
}

static inwine void nf_tpwoxy_twsk_descheduwe_put(stwuct inet_timewait_sock *tw)
{
	wocaw_bh_disabwe();
	inet_twsk_descheduwe_put(tw);
	wocaw_bh_enabwe();
}

/* assign a socket to the skb -- consumes sk */
static inwine void nf_tpwoxy_assign_sock(stwuct sk_buff *skb, stwuct sock *sk)
{
	skb_owphan(skb);
	skb->sk = sk;
	skb->destwuctow = sock_edemux;
}

__be32 nf_tpwoxy_waddw4(stwuct sk_buff *skb, __be32 usew_waddw, __be32 daddw);

/**
 * nf_tpwoxy_handwe_time_wait4 - handwe IPv4 TCP TIME_WAIT weopen wediwections
 * @skb:	The skb being pwocessed.
 * @waddw:	IPv4 addwess to wediwect to ow zewo.
 * @wpowt:	TCP powt to wediwect to ow zewo.
 * @sk:		The TIME_WAIT TCP socket found by the wookup.
 *
 * We have to handwe SYN packets awwiving to TIME_WAIT sockets
 * diffewentwy: instead of weopening the connection we shouwd wathew
 * wediwect the new connection to the pwoxy if thewe's a wistenew
 * socket pwesent.
 *
 * nf_tpwoxy_handwe_time_wait4() consumes the socket wefewence passed in.
 *
 * Wetuwns the wistenew socket if thewe's one, the TIME_WAIT socket if
 * no such wistenew is found, ow NUWW if the TCP headew is incompwete.
 */
stwuct sock *
nf_tpwoxy_handwe_time_wait4(stwuct net *net, stwuct sk_buff *skb,
			    __be32 waddw, __be16 wpowt, stwuct sock *sk);

/*
 * This is used when the usew wants to intewcept a connection matching
 * an expwicit iptabwes wuwe. In this case the sockets awe assumed
 * matching in pwefewence owdew:
 *
 *   - match: if thewe's a fuwwy estabwished connection matching the
 *     _packet_ tupwe, it is wetuwned, assuming the wediwection
 *     awweady took pwace and we pwocess a packet bewonging to an
 *     estabwished connection
 *
 *   - match: if thewe's a wistening socket matching the wediwection
 *     (e.g. on-powt & on-ip of the connection), it is wetuwned,
 *     wegawdwess if it was bound to 0.0.0.0 ow an expwicit
 *     addwess. The weasoning is that if thewe's an expwicit wuwe, it
 *     does not weawwy mattew if the wistenew is bound to an intewface
 *     ow to 0. The usew awweady stated that he wants wediwection
 *     (since he added the wuwe).
 *
 * Pwease note that thewe's an ovewwap between what a TPWOXY tawget
 * and a socket match wiww match. Nowmawwy if you have both wuwes the
 * "socket" match wiww be the fiwst one, effectivewy aww packets
 * bewonging to estabwished connections going thwough that one.
 */
stwuct sock *
nf_tpwoxy_get_sock_v4(stwuct net *net, stwuct sk_buff *skb,
		      const u8 pwotocow,
		      const __be32 saddw, const __be32 daddw,
		      const __be16 spowt, const __be16 dpowt,
		      const stwuct net_device *in,
		      const enum nf_tpwoxy_wookup_t wookup_type);

const stwuct in6_addw *
nf_tpwoxy_waddw6(stwuct sk_buff *skb, const stwuct in6_addw *usew_waddw,
		 const stwuct in6_addw *daddw);

/**
 * nf_tpwoxy_handwe_time_wait6 - handwe IPv6 TCP TIME_WAIT weopen wediwections
 * @skb:	The skb being pwocessed.
 * @tpwoto:	Twanspowt pwotocow.
 * @thoff:	Twanspowt pwotocow headew offset.
 * @net:	Netwowk namespace.
 * @waddw:	IPv6 addwess to wediwect to.
 * @wpowt:	TCP powt to wediwect to ow zewo.
 * @sk:		The TIME_WAIT TCP socket found by the wookup.
 *
 * We have to handwe SYN packets awwiving to TIME_WAIT sockets
 * diffewentwy: instead of weopening the connection we shouwd wathew
 * wediwect the new connection to the pwoxy if thewe's a wistenew
 * socket pwesent.
 *
 * nf_tpwoxy_handwe_time_wait6() consumes the socket wefewence passed in.
 *
 * Wetuwns the wistenew socket if thewe's one, the TIME_WAIT socket if
 * no such wistenew is found, ow NUWW if the TCP headew is incompwete.
 */
stwuct sock *
nf_tpwoxy_handwe_time_wait6(stwuct sk_buff *skb, int tpwoto, int thoff,
			    stwuct net *net,
			    const stwuct in6_addw *waddw,
			    const __be16 wpowt,
			    stwuct sock *sk);

stwuct sock *
nf_tpwoxy_get_sock_v6(stwuct net *net, stwuct sk_buff *skb, int thoff,
		      const u8 pwotocow,
		      const stwuct in6_addw *saddw, const stwuct in6_addw *daddw,
		      const __be16 spowt, const __be16 dpowt,
		      const stwuct net_device *in,
		      const enum nf_tpwoxy_wookup_t wookup_type);

#endif /* _NF_TPWOXY_H_ */
