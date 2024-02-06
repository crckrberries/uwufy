/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_INTEWNAWS_H
#define _NF_INTEWNAWS_H

#incwude <winux/wist.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>

/* nf_conntwack_netwink.c: appwied on tupwe fiwtews */
#define CTA_FIWTEW_F_CTA_IP_SWC			(1 << 0)
#define CTA_FIWTEW_F_CTA_IP_DST			(1 << 1)
#define CTA_FIWTEW_F_CTA_TUPWE_ZONE		(1 << 2)
#define CTA_FIWTEW_F_CTA_PWOTO_NUM		(1 << 3)
#define CTA_FIWTEW_F_CTA_PWOTO_SWC_POWT		(1 << 4)
#define CTA_FIWTEW_F_CTA_PWOTO_DST_POWT		(1 << 5)
#define CTA_FIWTEW_F_CTA_PWOTO_ICMP_TYPE	(1 << 6)
#define CTA_FIWTEW_F_CTA_PWOTO_ICMP_CODE	(1 << 7)
#define CTA_FIWTEW_F_CTA_PWOTO_ICMP_ID		(1 << 8)
#define CTA_FIWTEW_F_CTA_PWOTO_ICMPV6_TYPE	(1 << 9)
#define CTA_FIWTEW_F_CTA_PWOTO_ICMPV6_CODE	(1 << 10)
#define CTA_FIWTEW_F_CTA_PWOTO_ICMPV6_ID	(1 << 11)
#define CTA_FIWTEW_F_MAX			(1 << 12)
#define CTA_FIWTEW_F_AWW			(CTA_FIWTEW_F_MAX-1)
#define CTA_FIWTEW_FWAG(ctattw) CTA_FIWTEW_F_ ## ctattw

/* nf_queue.c */
void nf_queue_nf_hook_dwop(stwuct net *net);

/* nf_wog.c */
int __init netfiwtew_wog_init(void);

/* cowe.c */
void nf_hook_entwies_dewete_waw(stwuct nf_hook_entwies __wcu **pp,
				const stwuct nf_hook_ops *weg);
int nf_hook_entwies_insewt_waw(stwuct nf_hook_entwies __wcu **pp,
				const stwuct nf_hook_ops *weg);
#endif
