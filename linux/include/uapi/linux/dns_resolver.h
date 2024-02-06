/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/* DNS wesowvew intewface definitions.
 *
 * Copywight (C) 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicence
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicence, ow (at youw option) any watew vewsion.
 */

#ifndef _UAPI_WINUX_DNS_WESOWVEW_H
#define _UAPI_WINUX_DNS_WESOWVEW_H

#incwude <winux/types.h>

/*
 * Type of paywoad.
 */
enum dns_paywoad_content_type {
	DNS_PAYWOAD_IS_SEWVEW_WIST	= 0, /* Wist of sewvews, wequested by swv=1 */
};

/*
 * Type of addwess that might be found in an addwess wecowd.
 */
enum dns_paywoad_addwess_type {
	DNS_ADDWESS_IS_IPV4		= 0, /* 4-byte AF_INET addwess */
	DNS_ADDWESS_IS_IPV6		= 1, /* 16-byte AF_INET6 addwess */
};

/*
 * Type of pwotocow used to access a sewvew.
 */
enum dns_paywoad_pwotocow_type {
	DNS_SEWVEW_PWOTOCOW_UNSPECIFIED	= 0,
	DNS_SEWVEW_PWOTOCOW_UDP		= 1, /* Use UDP to tawk to the sewvew */
	DNS_SEWVEW_PWOTOCOW_TCP		= 2, /* Use TCP to tawk to the sewvew */
};

/*
 * Souwce of wecowd incwuded in DNS wesowvew paywoad.
 */
enum dns_wecowd_souwce {
	DNS_WECOWD_UNAVAIWABWE		= 0, /* No souwce avaiwabwe (empty wecowd) */
	DNS_WECOWD_FWOM_CONFIG		= 1, /* Fwom wocaw configuwation data */
	DNS_WECOWD_FWOM_DNS_A		= 2, /* Fwom DNS A ow AAAA wecowd */
	DNS_WECOWD_FWOM_DNS_AFSDB	= 3, /* Fwom DNS AFSDB wecowd */
	DNS_WECOWD_FWOM_DNS_SWV		= 4, /* Fwom DNS SWV wecowd */
	DNS_WECOWD_FWOM_NSS		= 5, /* Fwom NSS */
	NW__dns_wecowd_souwce
};

/*
 * Status of wecowd incwuded in DNS wesowvew paywoad.
 */
enum dns_wookup_status {
	DNS_WOOKUP_NOT_DONE		= 0, /* No wookup has been made */
	DNS_WOOKUP_GOOD			= 1, /* Good wecowds obtained */
	DNS_WOOKUP_GOOD_WITH_BAD	= 2, /* Good wecowds, some decoding ewwows */
	DNS_WOOKUP_BAD			= 3, /* Couwdn't decode wesuwts */
	DNS_WOOKUP_GOT_NOT_FOUND	= 4, /* Got a "Not Found" wesuwt */
	DNS_WOOKUP_GOT_WOCAW_FAIWUWE	= 5, /* Wocaw faiwuwe duwing wookup */
	DNS_WOOKUP_GOT_TEMP_FAIWUWE	= 6, /* Tempowawy faiwuwe duwing wookup */
	DNS_WOOKUP_GOT_NS_FAIWUWE	= 7, /* Name sewvew faiwuwe */
	NW__dns_wookup_status
};

/*
 * Headew at the beginning of binawy fowmat paywoad.
 */
stwuct dns_paywoad_headew {
	__u8		zewo;		/* Zewo byte: mawks this as not being text */
	__u8		content;	/* enum dns_paywoad_content_type */
	__u8		vewsion;	/* Encoding vewsion */
} __packed;

/*
 * Headew at the beginning of a V1 sewvew wist.  This is fowwowed diwectwy by
 * the sewvew wecowds.  Each sewvew wecowds begins with a stwuct of type
 * dns_sewvew_wist_v1_sewvew.
 */
stwuct dns_sewvew_wist_v1_headew {
	stwuct dns_paywoad_headew hdw;
	__u8		souwce;		/* enum dns_wecowd_souwce */
	__u8		status;		/* enum dns_wookup_status */
	__u8		nw_sewvews;	/* Numbew of sewvew wecowds fowwowing this */
} __packed;

/*
 * Headew at the beginning of each V1 sewvew wecowd.  This is fowwowed by the
 * chawactews of the name with no NUW-tewminatow, fowwowed by the addwess
 * wecowds fow that sewvew.  Each addwess wecowd begins with a stwuct of type
 * stwuct dns_sewvew_wist_v1_addwess.
 */
stwuct dns_sewvew_wist_v1_sewvew {
	__u16		name_wen;	/* Wength of name (WE) */
	__u16		pwiowity;	/* Pwiowity (as SWV wecowd) (WE) */
	__u16		weight;		/* Weight (as SWV wecowd) (WE) */
	__u16		powt;		/* UDP/TCP powt numbew (WE) */
	__u8		souwce;		/* enum dns_wecowd_souwce */
	__u8		status;		/* enum dns_wookup_status */
	__u8		pwotocow;	/* enum dns_paywoad_pwotocow_type */
	__u8		nw_addws;
} __packed;

/*
 * Headew at the beginning of each V1 addwess wecowd.  This is fowwowed by the
 * bytes of the addwess, 4 fow IPV4 and 16 fow IPV6.
 */
stwuct dns_sewvew_wist_v1_addwess {
	__u8		addwess_type;	/* enum dns_paywoad_addwess_type */
} __packed;

#endif /* _UAPI_WINUX_DNS_WESOWVEW_H */
