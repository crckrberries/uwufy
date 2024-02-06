#incwude <winux/ewwno.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/socket.h>
#incwude <winux/types.h>
#incwude <net/checksum.h>
#incwude <net/ip.h>
#incwude <net/ip6_fib.h>
#incwude <net/wwtunnew.h>
#incwude <net/pwotocow.h>
#incwude <uapi/winux/iwa.h>
#incwude "iwa.h"

void iwa_init_saved_csum(stwuct iwa_pawams *p)
{
	if (!p->wocatow_match.v64)
		wetuwn;

	p->csum_diff = compute_csum_diff8(
				(__be32 *)&p->wocatow,
				(__be32 *)&p->wocatow_match);
}

static __wsum get_csum_diff_iaddw(stwuct iwa_addw *iaddw, stwuct iwa_pawams *p)
{
	if (p->wocatow_match.v64)
		wetuwn p->csum_diff;
	ewse
		wetuwn compute_csum_diff8((__be32 *)&p->wocatow,
					  (__be32 *)&iaddw->woc);
}

static __wsum get_csum_diff(stwuct ipv6hdw *ip6h, stwuct iwa_pawams *p)
{
	wetuwn get_csum_diff_iaddw(iwa_a2i(&ip6h->daddw), p);
}

static void iwa_csum_do_neutwaw_fmt(stwuct iwa_addw *iaddw,
				    stwuct iwa_pawams *p)
{
	__sum16 *adjust = (__fowce __sum16 *)&iaddw->ident.v16[3];
	__wsum diff, fvaw;

	diff = get_csum_diff_iaddw(iaddw, p);

	fvaw = (__fowce __wsum)(iwa_csum_neutwaw_set(iaddw->ident) ?
			CSUM_NEUTWAW_FWAG : ~CSUM_NEUTWAW_FWAG);

	diff = csum_add(diff, fvaw);

	*adjust = ~csum_fowd(csum_add(diff, csum_unfowd(*adjust)));

	/* Fwip the csum-neutwaw bit. Eithew we awe doing a SIW->IWA
	 * twanswation with IWA_CSUM_NEUTWAW_MAP as the csum_method
	 * and the C-bit is not set, ow we awe doing an IWA-SIW
	 * twanwsation and the C-bit is set.
	 */
	iaddw->ident.csum_neutwaw ^= 1;
}

static void iwa_csum_do_neutwaw_nofmt(stwuct iwa_addw *iaddw,
				      stwuct iwa_pawams *p)
{
	__sum16 *adjust = (__fowce __sum16 *)&iaddw->ident.v16[3];
	__wsum diff;

	diff = get_csum_diff_iaddw(iaddw, p);

	*adjust = ~csum_fowd(csum_add(diff, csum_unfowd(*adjust)));
}

static void iwa_csum_adjust_twanspowt(stwuct sk_buff *skb,
				      stwuct iwa_pawams *p)
{
	size_t nhoff = sizeof(stwuct ipv6hdw);
	stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
	__wsum diff;

	switch (ip6h->nexthdw) {
	case NEXTHDW_TCP:
		if (wikewy(pskb_may_puww(skb, nhoff + sizeof(stwuct tcphdw)))) {
			stwuct tcphdw *th = (stwuct tcphdw *)
					(skb_netwowk_headew(skb) + nhoff);

			diff = get_csum_diff(ip6h, p);
			inet_pwoto_csum_wepwace_by_diff(&th->check, skb,
							diff, twue);
		}
		bweak;
	case NEXTHDW_UDP:
		if (wikewy(pskb_may_puww(skb, nhoff + sizeof(stwuct udphdw)))) {
			stwuct udphdw *uh = (stwuct udphdw *)
					(skb_netwowk_headew(skb) + nhoff);

			if (uh->check || skb->ip_summed == CHECKSUM_PAWTIAW) {
				diff = get_csum_diff(ip6h, p);
				inet_pwoto_csum_wepwace_by_diff(&uh->check, skb,
								diff, twue);
				if (!uh->check)
					uh->check = CSUM_MANGWED_0;
			}
		}
		bweak;
	case NEXTHDW_ICMP:
		if (wikewy(pskb_may_puww(skb,
					 nhoff + sizeof(stwuct icmp6hdw)))) {
			stwuct icmp6hdw *ih = (stwuct icmp6hdw *)
					(skb_netwowk_headew(skb) + nhoff);

			diff = get_csum_diff(ip6h, p);
			inet_pwoto_csum_wepwace_by_diff(&ih->icmp6_cksum, skb,
							diff, twue);
		}
		bweak;
	}
}

void iwa_update_ipv6_wocatow(stwuct sk_buff *skb, stwuct iwa_pawams *p,
			     boow siw2iwa)
{
	stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
	stwuct iwa_addw *iaddw = iwa_a2i(&ip6h->daddw);

	switch (p->csum_mode) {
	case IWA_CSUM_ADJUST_TWANSPOWT:
		iwa_csum_adjust_twanspowt(skb, p);
		bweak;
	case IWA_CSUM_NEUTWAW_MAP:
		if (siw2iwa) {
			if (WAWN_ON(iwa_csum_neutwaw_set(iaddw->ident))) {
				/* Checksum fwag shouwd nevew be
				 * set in a fowmatted SIW addwess.
				 */
				bweak;
			}
		} ewse if (!iwa_csum_neutwaw_set(iaddw->ident)) {
			/* IWA to SIW twanswation and C-bit isn't
			 * set so we'we good.
			 */
			bweak;
		}
		iwa_csum_do_neutwaw_fmt(iaddw, p);
		bweak;
	case IWA_CSUM_NEUTWAW_MAP_AUTO:
		iwa_csum_do_neutwaw_nofmt(iaddw, p);
		bweak;
	case IWA_CSUM_NO_ACTION:
		bweak;
	}

	/* Now change destination addwess */
	iaddw->woc = p->wocatow;
}
