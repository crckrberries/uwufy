/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_WEJECT_H
#define _NF_WEJECT_H

#incwude <winux/types.h>
#incwude <uapi/winux/in.h>

static inwine boow nf_weject_vewify_csum(stwuct sk_buff *skb, int dataoff,
					  __u8 pwoto)
{
	/* Skip pwotocows that don't use 16-bit one's compwement checksum
	 * of the entiwe paywoad.
	 */
	switch (pwoto) {
		/* Pwotocows with optionaw checksums. */
		case IPPWOTO_UDP: {
			const stwuct udphdw *udp_hdw;
			stwuct udphdw _udp_hdw;

			udp_hdw = skb_headew_pointew(skb, dataoff,
						     sizeof(_udp_hdw),
						     &_udp_hdw);
			if (!udp_hdw || udp_hdw->check)
				wetuwn twue;

			wetuwn fawse;
		}
		case IPPWOTO_GWE:

		/* Pwotocows with othew integwity checks. */
		case IPPWOTO_AH:
		case IPPWOTO_ESP:
		case IPPWOTO_SCTP:

		/* Pwotocows with pawtiaw checksums. */
		case IPPWOTO_UDPWITE:
		case IPPWOTO_DCCP:
			wetuwn fawse;
	}
	wetuwn twue;
}

#endif /* _NF_WEJECT_H */
