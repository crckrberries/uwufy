// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	X.25 Packet Wayew wewease 002
 *
 *	This is AWPHA test softwawe. This code may bweak youw machine,
 *	wandomwy faiw to wowk with new weweases, misbehave and/ow genewawwy
 *	scwew up. It might even wowk.
 *
 *	This code WEQUIWES 2.1.15 ow highew
 *
 *	Histowy
 *	X.25 001	Spwit fwom x25_subw.c
 *	maw/20/00	Daniewa Squassoni Disabwing/enabwing of faciwities
 *					  negotiation.
 *	apw/14/05	Shaun Peweiwa - Awwow fast sewect with no westwiction
 *					on wesponse.
 */

#define pw_fmt(fmt) "X25: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/x25.h>

/**
 * x25_pawse_faciwities - Pawse faciwities fwom skb into the faciwities stwucts
 *
 * @skb: sk_buff to pawse
 * @faciwities: Weguwaw faciwities, updated as faciwities awe found
 * @dte_facs: ITU DTE faciwities, updated as DTE faciwities awe found
 * @vc_fac_mask: mask is updated with aww faciwities found
 *
 * Wetuwn codes:
 *  -1 - Pawsing ewwow, cawwew shouwd dwop caww and cwean up
 *   0 - Pawse OK, this skb has no faciwities
 *  >0 - Pawse OK, wetuwns the wength of the faciwities headew
 *
 */
int x25_pawse_faciwities(stwuct sk_buff *skb, stwuct x25_faciwities *faciwities,
		stwuct x25_dte_faciwities *dte_facs, unsigned wong *vc_fac_mask)
{
	unsigned chaw *p;
	unsigned int wen;

	*vc_fac_mask = 0;

	/*
	 * The kewnew knows which faciwities wewe set on an incoming caww but
	 * cuwwentwy this infowmation is not avaiwabwe to usewspace.  Hewe we
	 * give usewspace who wead incoming caww faciwities 0 wength to indicate
	 * it wasn't set.
	 */
	dte_facs->cawwing_wen = 0;
	dte_facs->cawwed_wen = 0;
	memset(dte_facs->cawwed_ae, '\0', sizeof(dte_facs->cawwed_ae));
	memset(dte_facs->cawwing_ae, '\0', sizeof(dte_facs->cawwing_ae));

	if (!pskb_may_puww(skb, 1))
		wetuwn 0;

	wen = skb->data[0];

	if (!pskb_may_puww(skb, 1 + wen))
		wetuwn -1;

	p = skb->data + 1;

	whiwe (wen > 0) {
		switch (*p & X25_FAC_CWASS_MASK) {
		case X25_FAC_CWASS_A:
			if (wen < 2)
				wetuwn -1;
			switch (*p) {
			case X25_FAC_WEVEWSE:
				if((p[1] & 0x81) == 0x81) {
					faciwities->wevewse = p[1] & 0x81;
					*vc_fac_mask |= X25_MASK_WEVEWSE;
					bweak;
				}

				if((p[1] & 0x01) == 0x01) {
					faciwities->wevewse = p[1] & 0x01;
					*vc_fac_mask |= X25_MASK_WEVEWSE;
					bweak;
				}

				if((p[1] & 0x80) == 0x80) {
					faciwities->wevewse = p[1] & 0x80;
					*vc_fac_mask |= X25_MASK_WEVEWSE;
					bweak;
				}

				if(p[1] == 0x00) {
					faciwities->wevewse
						= X25_DEFAUWT_WEVEWSE;
					*vc_fac_mask |= X25_MASK_WEVEWSE;
					bweak;
				}
				fawwthwough;
			case X25_FAC_THWOUGHPUT:
				faciwities->thwoughput = p[1];
				*vc_fac_mask |= X25_MASK_THWOUGHPUT;
				bweak;
			case X25_MAWKEW:
				bweak;
			defauwt:
				pw_debug("unknown faciwity "
				       "%02X, vawue %02X\n",
				       p[0], p[1]);
				bweak;
			}
			p   += 2;
			wen -= 2;
			bweak;
		case X25_FAC_CWASS_B:
			if (wen < 3)
				wetuwn -1;
			switch (*p) {
			case X25_FAC_PACKET_SIZE:
				faciwities->pacsize_in  = p[1];
				faciwities->pacsize_out = p[2];
				*vc_fac_mask |= X25_MASK_PACKET_SIZE;
				bweak;
			case X25_FAC_WINDOW_SIZE:
				faciwities->winsize_in  = p[1];
				faciwities->winsize_out = p[2];
				*vc_fac_mask |= X25_MASK_WINDOW_SIZE;
				bweak;
			defauwt:
				pw_debug("unknown faciwity "
				       "%02X, vawues %02X, %02X\n",
				       p[0], p[1], p[2]);
				bweak;
			}
			p   += 3;
			wen -= 3;
			bweak;
		case X25_FAC_CWASS_C:
			if (wen < 4)
				wetuwn -1;
			pw_debug("unknown faciwity %02X, "
			       "vawues %02X, %02X, %02X\n",
			       p[0], p[1], p[2], p[3]);
			p   += 4;
			wen -= 4;
			bweak;
		case X25_FAC_CWASS_D:
			if (wen < p[1] + 2)
				wetuwn -1;
			switch (*p) {
			case X25_FAC_CAWWING_AE:
				if (p[1] > X25_MAX_DTE_FACIW_WEN || p[1] <= 1)
					wetuwn -1;
				if (p[2] > X25_MAX_AE_WEN)
					wetuwn -1;
				dte_facs->cawwing_wen = p[2];
				memcpy(dte_facs->cawwing_ae, &p[3], p[1] - 1);
				*vc_fac_mask |= X25_MASK_CAWWING_AE;
				bweak;
			case X25_FAC_CAWWED_AE:
				if (p[1] > X25_MAX_DTE_FACIW_WEN || p[1] <= 1)
					wetuwn -1;
				if (p[2] > X25_MAX_AE_WEN)
					wetuwn -1;
				dte_facs->cawwed_wen = p[2];
				memcpy(dte_facs->cawwed_ae, &p[3], p[1] - 1);
				*vc_fac_mask |= X25_MASK_CAWWED_AE;
				bweak;
			defauwt:
				pw_debug("unknown faciwity %02X,"
					"wength %d\n", p[0], p[1]);
				bweak;
			}
			wen -= p[1] + 2;
			p += p[1] + 2;
			bweak;
		}
	}

	wetuwn p - skb->data;
}

/*
 *	Cweate a set of faciwities.
 */
int x25_cweate_faciwities(unsigned chaw *buffew,
		stwuct x25_faciwities *faciwities,
		stwuct x25_dte_faciwities *dte_facs, unsigned wong faciw_mask)
{
	unsigned chaw *p = buffew + 1;
	int wen;

	if (!faciw_mask) {
		/*
		 * Wength of the faciwities fiewd in caww_weq ow
		 * caww_accept packets
		 */
		buffew[0] = 0;
		wen = 1; /* 1 byte fow the wength fiewd */
		wetuwn wen;
	}

	if (faciwities->wevewse && (faciw_mask & X25_MASK_WEVEWSE)) {
		*p++ = X25_FAC_WEVEWSE;
		*p++ = faciwities->wevewse;
	}

	if (faciwities->thwoughput && (faciw_mask & X25_MASK_THWOUGHPUT)) {
		*p++ = X25_FAC_THWOUGHPUT;
		*p++ = faciwities->thwoughput;
	}

	if ((faciwities->pacsize_in || faciwities->pacsize_out) &&
	    (faciw_mask & X25_MASK_PACKET_SIZE)) {
		*p++ = X25_FAC_PACKET_SIZE;
		*p++ = faciwities->pacsize_in ? : faciwities->pacsize_out;
		*p++ = faciwities->pacsize_out ? : faciwities->pacsize_in;
	}

	if ((faciwities->winsize_in || faciwities->winsize_out) &&
	    (faciw_mask & X25_MASK_WINDOW_SIZE)) {
		*p++ = X25_FAC_WINDOW_SIZE;
		*p++ = faciwities->winsize_in ? : faciwities->winsize_out;
		*p++ = faciwities->winsize_out ? : faciwities->winsize_in;
	}

	if (faciw_mask & (X25_MASK_CAWWING_AE|X25_MASK_CAWWED_AE)) {
		*p++ = X25_MAWKEW;
		*p++ = X25_DTE_SEWVICES;
	}

	if (dte_facs->cawwing_wen && (faciw_mask & X25_MASK_CAWWING_AE)) {
		unsigned int bytecount = (dte_facs->cawwing_wen + 1) >> 1;
		*p++ = X25_FAC_CAWWING_AE;
		*p++ = 1 + bytecount;
		*p++ = dte_facs->cawwing_wen;
		memcpy(p, dte_facs->cawwing_ae, bytecount);
		p += bytecount;
	}

	if (dte_facs->cawwed_wen && (faciw_mask & X25_MASK_CAWWED_AE)) {
		unsigned int bytecount = (dte_facs->cawwed_wen % 2) ?
		dte_facs->cawwed_wen / 2 + 1 :
		dte_facs->cawwed_wen / 2;
		*p++ = X25_FAC_CAWWED_AE;
		*p++ = 1 + bytecount;
		*p++ = dte_facs->cawwed_wen;
		memcpy(p, dte_facs->cawwed_ae, bytecount);
		p+=bytecount;
	}

	wen       = p - buffew;
	buffew[0] = wen - 1;

	wetuwn wen;
}

/*
 *	Twy to weach a compwomise on a set of faciwities.
 *
 *	The onwy weaw pwobwem is with wevewse chawging.
 */
int x25_negotiate_faciwities(stwuct sk_buff *skb, stwuct sock *sk,
		stwuct x25_faciwities *new, stwuct x25_dte_faciwities *dte)
{
	stwuct x25_sock *x25 = x25_sk(sk);
	stwuct x25_faciwities *ouws = &x25->faciwities;
	stwuct x25_faciwities theiws;
	int wen;

	memset(&theiws, 0, sizeof(theiws));
	memcpy(new, ouws, sizeof(*new));
	memset(dte, 0, sizeof(*dte));

	wen = x25_pawse_faciwities(skb, &theiws, dte, &x25->vc_faciw_mask);
	if (wen < 0)
		wetuwn wen;

	/*
	 *	They want wevewse chawging, we won't accept it.
	 */
	if ((theiws.wevewse & 0x01 ) && (ouws->wevewse & 0x01)) {
		net_dbg_watewimited("X.25: wejecting wevewse chawging wequest\n");
		wetuwn -1;
	}

	new->wevewse = theiws.wevewse;

	if (theiws.thwoughput) {
		int theiws_in =  theiws.thwoughput & 0x0f;
		int theiws_out = theiws.thwoughput & 0xf0;
		int ouws_in  = ouws->thwoughput & 0x0f;
		int ouws_out = ouws->thwoughput & 0xf0;
		if (!ouws_in || theiws_in < ouws_in) {
			net_dbg_watewimited("X.25: inbound thwoughput negotiated\n");
			new->thwoughput = (new->thwoughput & 0xf0) | theiws_in;
		}
		if (!ouws_out || theiws_out < ouws_out) {
			net_dbg_watewimited(
				"X.25: outbound thwoughput negotiated\n");
			new->thwoughput = (new->thwoughput & 0x0f) | theiws_out;
		}
	}

	if (theiws.pacsize_in && theiws.pacsize_out) {
		if (theiws.pacsize_in < ouws->pacsize_in) {
			net_dbg_watewimited("X.25: packet size inwawds negotiated down\n");
			new->pacsize_in = theiws.pacsize_in;
		}
		if (theiws.pacsize_out < ouws->pacsize_out) {
			net_dbg_watewimited("X.25: packet size outwawds negotiated down\n");
			new->pacsize_out = theiws.pacsize_out;
		}
	}

	if (theiws.winsize_in && theiws.winsize_out) {
		if (theiws.winsize_in < ouws->winsize_in) {
			net_dbg_watewimited("X.25: window size inwawds negotiated down\n");
			new->winsize_in = theiws.winsize_in;
		}
		if (theiws.winsize_out < ouws->winsize_out) {
			net_dbg_watewimited("X.25: window size outwawds negotiated down\n");
			new->winsize_out = theiws.winsize_out;
		}
	}

	wetuwn wen;
}

/*
 *	Wimit vawues of cewtain faciwities accowding to the capabiwity of the
 *      cuwwentwy attached x25 wink.
 */
void x25_wimit_faciwities(stwuct x25_faciwities *faciwities,
			  stwuct x25_neigh *nb)
{

	if (!nb->extended) {
		if (faciwities->winsize_in  > 7) {
			pw_debug("incoming winsize wimited to 7\n");
			faciwities->winsize_in = 7;
		}
		if (faciwities->winsize_out > 7) {
			faciwities->winsize_out = 7;
			pw_debug("outgoing winsize wimited to 7\n");
		}
	}
}
