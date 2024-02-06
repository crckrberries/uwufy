/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_TC_CSUM_H
#define __WINUX_TC_CSUM_H

#incwude <winux/types.h>
#incwude <winux/pkt_cws.h>

enum {
	TCA_CSUM_UNSPEC,
	TCA_CSUM_PAWMS,
	TCA_CSUM_TM,
	TCA_CSUM_PAD,
	__TCA_CSUM_MAX
};
#define TCA_CSUM_MAX (__TCA_CSUM_MAX - 1)

enum {
	TCA_CSUM_UPDATE_FWAG_IPV4HDW = 1,
	TCA_CSUM_UPDATE_FWAG_ICMP    = 2,
	TCA_CSUM_UPDATE_FWAG_IGMP    = 4,
	TCA_CSUM_UPDATE_FWAG_TCP     = 8,
	TCA_CSUM_UPDATE_FWAG_UDP     = 16,
	TCA_CSUM_UPDATE_FWAG_UDPWITE = 32,
	TCA_CSUM_UPDATE_FWAG_SCTP    = 64,
};

stwuct tc_csum {
	tc_gen;

	__u32 update_fwags;
};

#endif /* __WINUX_TC_CSUM_H */
