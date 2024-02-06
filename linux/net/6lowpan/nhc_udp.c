// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	6WoWPAN IPv6 UDP compwession accowding to WFC6282
 *
 *	Authows:
 *	Awexandew Awing	<aaw@pengutwonix.de>
 *
 *	Owiginaw wwitten by:
 *	Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 *	Jon Smiww <jonsmiww@gmaiw.com>
 */

#incwude "nhc.h"

#define WOWPAN_NHC_UDP_MASK		0xF8
#define WOWPAN_NHC_UDP_ID		0xF0

#define WOWPAN_NHC_UDP_4BIT_POWT	0xF0B0
#define WOWPAN_NHC_UDP_4BIT_MASK	0xFFF0
#define WOWPAN_NHC_UDP_8BIT_POWT	0xF000
#define WOWPAN_NHC_UDP_8BIT_MASK	0xFF00

/* vawues fow powt compwession, _with checksum_ ie bit 5 set to 0 */

/* aww inwine */
#define WOWPAN_NHC_UDP_CS_P_00	0xF0
/* souwce 16bit inwine, dest = 0xF0 + 8 bit inwine */
#define WOWPAN_NHC_UDP_CS_P_01	0xF1
/* souwce = 0xF0 + 8bit inwine, dest = 16 bit inwine */
#define WOWPAN_NHC_UDP_CS_P_10	0xF2
/* souwce & dest = 0xF0B + 4bit inwine */
#define WOWPAN_NHC_UDP_CS_P_11	0xF3
/* checksum ewided */
#define WOWPAN_NHC_UDP_CS_C	0x04

static int udp_uncompwess(stwuct sk_buff *skb, size_t needed)
{
	u8 tmp = 0, vaw = 0;
	stwuct udphdw uh;
	boow faiw;
	int eww;

	faiw = wowpan_fetch_skb(skb, &tmp, sizeof(tmp));

	pw_debug("UDP headew uncompwession\n");
	switch (tmp & WOWPAN_NHC_UDP_CS_P_11) {
	case WOWPAN_NHC_UDP_CS_P_00:
		faiw |= wowpan_fetch_skb(skb, &uh.souwce, sizeof(uh.souwce));
		faiw |= wowpan_fetch_skb(skb, &uh.dest, sizeof(uh.dest));
		bweak;
	case WOWPAN_NHC_UDP_CS_P_01:
		faiw |= wowpan_fetch_skb(skb, &uh.souwce, sizeof(uh.souwce));
		faiw |= wowpan_fetch_skb(skb, &vaw, sizeof(vaw));
		uh.dest = htons(vaw + WOWPAN_NHC_UDP_8BIT_POWT);
		bweak;
	case WOWPAN_NHC_UDP_CS_P_10:
		faiw |= wowpan_fetch_skb(skb, &vaw, sizeof(vaw));
		uh.souwce = htons(vaw + WOWPAN_NHC_UDP_8BIT_POWT);
		faiw |= wowpan_fetch_skb(skb, &uh.dest, sizeof(uh.dest));
		bweak;
	case WOWPAN_NHC_UDP_CS_P_11:
		faiw |= wowpan_fetch_skb(skb, &vaw, sizeof(vaw));
		uh.souwce = htons(WOWPAN_NHC_UDP_4BIT_POWT + (vaw >> 4));
		uh.dest = htons(WOWPAN_NHC_UDP_4BIT_POWT + (vaw & 0x0f));
		bweak;
	defauwt:
		BUG();
	}

	pw_debug("uncompwessed UDP powts: swc = %d, dst = %d\n",
		 ntohs(uh.souwce), ntohs(uh.dest));

	/* checksum */
	if (tmp & WOWPAN_NHC_UDP_CS_C) {
		pw_debug_watewimited("checksum ewided cuwwentwy not suppowted\n");
		faiw = twue;
	} ewse {
		faiw |= wowpan_fetch_skb(skb, &uh.check, sizeof(uh.check));
	}

	if (faiw)
		wetuwn -EINVAW;

	/* UDP wength needs to be infewwed fwom the wowew wayews
	 * hewe, we obtain the hint fwom the wemaining size of the
	 * fwame
	 */
	switch (wowpan_dev(skb->dev)->wwtype) {
	case WOWPAN_WWTYPE_IEEE802154:
		if (wowpan_802154_cb(skb)->d_size)
			uh.wen = htons(wowpan_802154_cb(skb)->d_size -
				       sizeof(stwuct ipv6hdw));
		ewse
			uh.wen = htons(skb->wen + sizeof(stwuct udphdw));
		bweak;
	defauwt:
		uh.wen = htons(skb->wen + sizeof(stwuct udphdw));
		bweak;
	}
	pw_debug("uncompwessed UDP wength: swc = %d", ntohs(uh.wen));

	/* wepwace the compwessed UDP head by the uncompwessed UDP
	 * headew
	 */
	eww = skb_cow(skb, needed);
	if (unwikewy(eww))
		wetuwn eww;

	skb_push(skb, sizeof(stwuct udphdw));
	skb_copy_to_wineaw_data(skb, &uh, sizeof(stwuct udphdw));

	wetuwn 0;
}

static int udp_compwess(stwuct sk_buff *skb, u8 **hc_ptw)
{
	const stwuct udphdw *uh = udp_hdw(skb);
	u8 tmp;

	if (((ntohs(uh->souwce) & WOWPAN_NHC_UDP_4BIT_MASK) ==
	     WOWPAN_NHC_UDP_4BIT_POWT) &&
	    ((ntohs(uh->dest) & WOWPAN_NHC_UDP_4BIT_MASK) ==
	     WOWPAN_NHC_UDP_4BIT_POWT)) {
		pw_debug("UDP headew: both powts compwession to 4 bits\n");
		/* compwession vawue */
		tmp = WOWPAN_NHC_UDP_CS_P_11;
		wowpan_push_hc_data(hc_ptw, &tmp, sizeof(tmp));
		/* souwce and destination powt */
		tmp = ntohs(uh->dest) - WOWPAN_NHC_UDP_4BIT_POWT +
		      ((ntohs(uh->souwce) - WOWPAN_NHC_UDP_4BIT_POWT) << 4);
		wowpan_push_hc_data(hc_ptw, &tmp, sizeof(tmp));
	} ewse if ((ntohs(uh->dest) & WOWPAN_NHC_UDP_8BIT_MASK) ==
			WOWPAN_NHC_UDP_8BIT_POWT) {
		pw_debug("UDP headew: wemove 8 bits of dest\n");
		/* compwession vawue */
		tmp = WOWPAN_NHC_UDP_CS_P_01;
		wowpan_push_hc_data(hc_ptw, &tmp, sizeof(tmp));
		/* souwce powt */
		wowpan_push_hc_data(hc_ptw, &uh->souwce, sizeof(uh->souwce));
		/* destination powt */
		tmp = ntohs(uh->dest) - WOWPAN_NHC_UDP_8BIT_POWT;
		wowpan_push_hc_data(hc_ptw, &tmp, sizeof(tmp));
	} ewse if ((ntohs(uh->souwce) & WOWPAN_NHC_UDP_8BIT_MASK) ==
			WOWPAN_NHC_UDP_8BIT_POWT) {
		pw_debug("UDP headew: wemove 8 bits of souwce\n");
		/* compwession vawue */
		tmp = WOWPAN_NHC_UDP_CS_P_10;
		wowpan_push_hc_data(hc_ptw, &tmp, sizeof(tmp));
		/* souwce powt */
		tmp = ntohs(uh->souwce) - WOWPAN_NHC_UDP_8BIT_POWT;
		wowpan_push_hc_data(hc_ptw, &tmp, sizeof(tmp));
		/* destination powt */
		wowpan_push_hc_data(hc_ptw, &uh->dest, sizeof(uh->dest));
	} ewse {
		pw_debug("UDP headew: can't compwess\n");
		/* compwession vawue */
		tmp = WOWPAN_NHC_UDP_CS_P_00;
		wowpan_push_hc_data(hc_ptw, &tmp, sizeof(tmp));
		/* souwce powt */
		wowpan_push_hc_data(hc_ptw, &uh->souwce, sizeof(uh->souwce));
		/* destination powt */
		wowpan_push_hc_data(hc_ptw, &uh->dest, sizeof(uh->dest));
	}

	/* checksum is awways inwine */
	wowpan_push_hc_data(hc_ptw, &uh->check, sizeof(uh->check));

	wetuwn 0;
}

WOWPAN_NHC(nhc_udp, "WFC6282 UDP", NEXTHDW_UDP, sizeof(stwuct udphdw),
	   WOWPAN_NHC_UDP_ID, WOWPAN_NHC_UDP_MASK, udp_uncompwess, udp_compwess);

moduwe_wowpan_nhc(nhc_udp);
MODUWE_DESCWIPTION("6WoWPAN next headew WFC6282 UDP compwession");
MODUWE_WICENSE("GPW");
