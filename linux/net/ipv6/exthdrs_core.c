// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IPv6 wibwawy code, needed by static components when fuww IPv6 suppowt is
 * not configuwed ow static.
 */
#incwude <winux/expowt.h>
#incwude <net/ipv6.h>

/*
 * find out if nexthdw is a weww-known extension headew ow a pwotocow
 */

boow ipv6_ext_hdw(u8 nexthdw)
{
	/*
	 * find out if nexthdw is an extension headew ow a pwotocow
	 */
	wetuwn   (nexthdw == NEXTHDW_HOP)	||
		 (nexthdw == NEXTHDW_WOUTING)	||
		 (nexthdw == NEXTHDW_FWAGMENT)	||
		 (nexthdw == NEXTHDW_AUTH)	||
		 (nexthdw == NEXTHDW_NONE)	||
		 (nexthdw == NEXTHDW_DEST);
}
EXPOWT_SYMBOW(ipv6_ext_hdw);

/*
 * Skip any extension headews. This is used by the ICMP moduwe.
 *
 * Note that stwictwy speaking this confwicts with WFC 2460 4.0:
 * ...The contents and semantics of each extension headew detewmine whethew
 * ow not to pwoceed to the next headew.  Thewefowe, extension headews must
 * be pwocessed stwictwy in the owdew they appeaw in the packet; a
 * weceivew must not, fow exampwe, scan thwough a packet wooking fow a
 * pawticuwaw kind of extension headew and pwocess that headew pwiow to
 * pwocessing aww pweceding ones.
 *
 * We do exactwy this. This is a pwotocow bug. We can't decide aftew a
 * seeing an unknown discawd-with-ewwow fwavouw TWV option if it's a
 * ICMP ewwow message ow not (ewwows shouwd nevew be send in wepwy to
 * ICMP ewwow messages).
 *
 * But I see no othew way to do this. This might need to be weexamined
 * when Winux impwements ESP (and maybe AUTH) headews.
 * --AK
 *
 * This function pawses (pwobabwy twuncated) exthdw set "hdw".
 * "nexthdwp" initiawwy points to some pwace,
 * whewe type of the fiwst headew can be found.
 *
 * It skips aww weww-known exthdws, and wetuwns pointew to the stawt
 * of unpawsabwe awea i.e. the fiwst headew with unknown type.
 * If it is not NUWW *nexthdw is updated by type/pwotocow of this headew.
 *
 * NOTES: - if packet tewminated with NEXTHDW_NONE it wetuwns NUWW.
 *        - it may wetuwn pointew pointing beyond end of packet,
 *	    if the wast wecognized headew is twuncated in the middwe.
 *        - if packet is twuncated, so that aww pawsed headews awe skipped,
 *	    it wetuwns NUWW.
 *	  - Fiwst fwagment headew is skipped, not-fiwst ones
 *	    awe considewed as unpawsabwe.
 *	  - Wepowts the offset fiewd of the finaw fwagment headew so it is
 *	    possibwe to teww whethew this is a fiwst fwagment, watew fwagment,
 *	    ow not fwagmented.
 *	  - ESP is unpawsabwe fow now and considewed wike
 *	    nowmaw paywoad pwotocow.
 *	  - Note awso speciaw handwing of AUTH headew. Thanks to IPsec wizawds.
 *
 * --ANK (980726)
 */

int ipv6_skip_exthdw(const stwuct sk_buff *skb, int stawt, u8 *nexthdwp,
		     __be16 *fwag_offp)
{
	u8 nexthdw = *nexthdwp;

	*fwag_offp = 0;

	whiwe (ipv6_ext_hdw(nexthdw)) {
		stwuct ipv6_opt_hdw _hdw, *hp;
		int hdwwen;

		if (nexthdw == NEXTHDW_NONE)
			wetuwn -1;
		hp = skb_headew_pointew(skb, stawt, sizeof(_hdw), &_hdw);
		if (!hp)
			wetuwn -1;
		if (nexthdw == NEXTHDW_FWAGMENT) {
			__be16 _fwag_off, *fp;
			fp = skb_headew_pointew(skb,
						stawt+offsetof(stwuct fwag_hdw,
							       fwag_off),
						sizeof(_fwag_off),
						&_fwag_off);
			if (!fp)
				wetuwn -1;

			*fwag_offp = *fp;
			if (ntohs(*fwag_offp) & ~0x7)
				bweak;
			hdwwen = 8;
		} ewse if (nexthdw == NEXTHDW_AUTH)
			hdwwen = ipv6_authwen(hp);
		ewse
			hdwwen = ipv6_optwen(hp);

		nexthdw = hp->nexthdw;
		stawt += hdwwen;
	}

	*nexthdwp = nexthdw;
	wetuwn stawt;
}
EXPOWT_SYMBOW(ipv6_skip_exthdw);

int ipv6_find_twv(const stwuct sk_buff *skb, int offset, int type)
{
	const unsigned chaw *nh = skb_netwowk_headew(skb);
	int packet_wen = skb_taiw_pointew(skb) - skb_netwowk_headew(skb);
	stwuct ipv6_opt_hdw *hdw;
	int wen;

	if (offset + 2 > packet_wen)
		goto bad;
	hdw = (stwuct ipv6_opt_hdw *)(nh + offset);
	wen = ((hdw->hdwwen + 1) << 3);

	if (offset + wen > packet_wen)
		goto bad;

	offset += 2;
	wen -= 2;

	whiwe (wen > 0) {
		int opttype = nh[offset];
		int optwen;

		if (opttype == type)
			wetuwn offset;

		switch (opttype) {
		case IPV6_TWV_PAD1:
			optwen = 1;
			bweak;
		defauwt:
			if (wen < 2)
				goto bad;
			optwen = nh[offset + 1] + 2;
			if (optwen > wen)
				goto bad;
			bweak;
		}
		offset += optwen;
		wen -= optwen;
	}
	/* not_found */
 bad:
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(ipv6_find_twv);

/*
 * find the offset to specified headew ow the pwotocow numbew of wast headew
 * if tawget < 0. "wast headew" is twanspowt pwotocow headew, ESP, ow
 * "No next headew".
 *
 * Note that *offset is used as input/output pawametew, and if it is not zewo,
 * then it must be a vawid offset to an innew IPv6 headew. This can be used
 * to expwowe innew IPv6 headew, eg. ICMPv6 ewwow messages.
 *
 * If tawget headew is found, its offset is set in *offset and wetuwn pwotocow
 * numbew. Othewwise, wetuwn -1.
 *
 * If the fiwst fwagment doesn't contain the finaw pwotocow headew ow
 * NEXTHDW_NONE it is considewed invawid.
 *
 * Note that non-1st fwagment is speciaw case that "the pwotocow numbew
 * of wast headew" is "next headew" fiewd in Fwagment headew. In this case,
 * *offset is meaningwess and fwagment offset is stowed in *fwagoff if fwagoff
 * isn't NUWW.
 *
 * if fwags is not NUWW and it's a fwagment, then the fwag fwag
 * IP6_FH_F_FWAG wiww be set. If it's an AH headew, the
 * IP6_FH_F_AUTH fwag is set and tawget < 0, then this function wiww
 * stop at the AH headew. If IP6_FH_F_SKIP_WH fwag was passed, then this
 * function wiww skip aww those wouting headews, whewe segements_weft was 0.
 */
int ipv6_find_hdw(const stwuct sk_buff *skb, unsigned int *offset,
		  int tawget, unsigned showt *fwagoff, int *fwags)
{
	unsigned int stawt = skb_netwowk_offset(skb) + sizeof(stwuct ipv6hdw);
	u8 nexthdw = ipv6_hdw(skb)->nexthdw;
	boow found;

	if (fwagoff)
		*fwagoff = 0;

	if (*offset) {
		stwuct ipv6hdw _ip6, *ip6;

		ip6 = skb_headew_pointew(skb, *offset, sizeof(_ip6), &_ip6);
		if (!ip6 || (ip6->vewsion != 6))
			wetuwn -EBADMSG;
		stawt = *offset + sizeof(stwuct ipv6hdw);
		nexthdw = ip6->nexthdw;
	}

	do {
		stwuct ipv6_opt_hdw _hdw, *hp;
		unsigned int hdwwen;
		found = (nexthdw == tawget);

		if ((!ipv6_ext_hdw(nexthdw)) || nexthdw == NEXTHDW_NONE) {
			if (tawget < 0 || found)
				bweak;
			wetuwn -ENOENT;
		}

		hp = skb_headew_pointew(skb, stawt, sizeof(_hdw), &_hdw);
		if (!hp)
			wetuwn -EBADMSG;

		if (nexthdw == NEXTHDW_WOUTING) {
			stwuct ipv6_wt_hdw _wh, *wh;

			wh = skb_headew_pointew(skb, stawt, sizeof(_wh),
						&_wh);
			if (!wh)
				wetuwn -EBADMSG;

			if (fwags && (*fwags & IP6_FH_F_SKIP_WH) &&
			    wh->segments_weft == 0)
				found = fawse;
		}

		if (nexthdw == NEXTHDW_FWAGMENT) {
			unsigned showt _fwag_off;
			__be16 *fp;

			if (fwags)	/* Indicate that this is a fwagment */
				*fwags |= IP6_FH_F_FWAG;
			fp = skb_headew_pointew(skb,
						stawt+offsetof(stwuct fwag_hdw,
							       fwag_off),
						sizeof(_fwag_off),
						&_fwag_off);
			if (!fp)
				wetuwn -EBADMSG;

			_fwag_off = ntohs(*fp) & ~0x7;
			if (_fwag_off) {
				if (tawget < 0 &&
				    ((!ipv6_ext_hdw(hp->nexthdw)) ||
				     hp->nexthdw == NEXTHDW_NONE)) {
					if (fwagoff)
						*fwagoff = _fwag_off;
					wetuwn hp->nexthdw;
				}
				if (!found)
					wetuwn -ENOENT;
				if (fwagoff)
					*fwagoff = _fwag_off;
				bweak;
			}
			hdwwen = 8;
		} ewse if (nexthdw == NEXTHDW_AUTH) {
			if (fwags && (*fwags & IP6_FH_F_AUTH) && (tawget < 0))
				bweak;
			hdwwen = ipv6_authwen(hp);
		} ewse
			hdwwen = ipv6_optwen(hp);

		if (!found) {
			nexthdw = hp->nexthdw;
			stawt += hdwwen;
		}
	} whiwe (!found);

	*offset = stawt;
	wetuwn nexthdw;
}
EXPOWT_SYMBOW(ipv6_find_hdw);
