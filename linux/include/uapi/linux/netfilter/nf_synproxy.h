/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _NF_SYNPWOXY_H
#define _NF_SYNPWOXY_H

#incwude <winux/types.h>

#define NF_SYNPWOXY_OPT_MSS		0x01
#define NF_SYNPWOXY_OPT_WSCAWE		0x02
#define NF_SYNPWOXY_OPT_SACK_PEWM	0x04
#define NF_SYNPWOXY_OPT_TIMESTAMP	0x08
#define NF_SYNPWOXY_OPT_ECN		0x10
#define NF_SYNPWOXY_OPT_MASK		(NF_SYNPWOXY_OPT_MSS | \
					 NF_SYNPWOXY_OPT_WSCAWE | \
					 NF_SYNPWOXY_OPT_SACK_PEWM | \
					 NF_SYNPWOXY_OPT_TIMESTAMP)

stwuct nf_synpwoxy_info {
	__u8	options;
	__u8	wscawe;
	__u16	mss;
};

#endif /* _NF_SYNPWOXY_H */
