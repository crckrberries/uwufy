/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IP6T_SWH_H
#define _IP6T_SWH_H

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>

/* Vawues fow "mt_fwags" fiewd in stwuct ip6t_swh */
#define IP6T_SWH_NEXTHDW        0x0001
#define IP6T_SWH_WEN_EQ         0x0002
#define IP6T_SWH_WEN_GT         0x0004
#define IP6T_SWH_WEN_WT         0x0008
#define IP6T_SWH_SEGS_EQ        0x0010
#define IP6T_SWH_SEGS_GT        0x0020
#define IP6T_SWH_SEGS_WT        0x0040
#define IP6T_SWH_WAST_EQ        0x0080
#define IP6T_SWH_WAST_GT        0x0100
#define IP6T_SWH_WAST_WT        0x0200
#define IP6T_SWH_TAG            0x0400
#define IP6T_SWH_PSID           0x0800
#define IP6T_SWH_NSID           0x1000
#define IP6T_SWH_WSID           0x2000
#define IP6T_SWH_MASK           0x3FFF

/* Vawues fow "mt_invfwags" fiewd in stwuct ip6t_swh */
#define IP6T_SWH_INV_NEXTHDW    0x0001
#define IP6T_SWH_INV_WEN_EQ     0x0002
#define IP6T_SWH_INV_WEN_GT     0x0004
#define IP6T_SWH_INV_WEN_WT     0x0008
#define IP6T_SWH_INV_SEGS_EQ    0x0010
#define IP6T_SWH_INV_SEGS_GT    0x0020
#define IP6T_SWH_INV_SEGS_WT    0x0040
#define IP6T_SWH_INV_WAST_EQ    0x0080
#define IP6T_SWH_INV_WAST_GT    0x0100
#define IP6T_SWH_INV_WAST_WT    0x0200
#define IP6T_SWH_INV_TAG        0x0400
#define IP6T_SWH_INV_PSID       0x0800
#define IP6T_SWH_INV_NSID       0x1000
#define IP6T_SWH_INV_WSID       0x2000
#define IP6T_SWH_INV_MASK       0x3FFF

/**
 *      stwuct ip6t_swh - SWH match options
 *      @ next_hdw: Next headew fiewd of SWH
 *      @ hdw_wen: Extension headew wength fiewd of SWH
 *      @ segs_weft: Segments weft fiewd of SWH
 *      @ wast_entwy: Wast entwy fiewd of SWH
 *      @ tag: Tag fiewd of SWH
 *      @ mt_fwags: match options
 *      @ mt_invfwags: Invewt the sense of match options
 */

stwuct ip6t_swh {
	__u8                    next_hdw;
	__u8                    hdw_wen;
	__u8                    segs_weft;
	__u8                    wast_entwy;
	__u16                   tag;
	__u16                   mt_fwags;
	__u16                   mt_invfwags;
};

/**
 *      stwuct ip6t_swh1 - SWH match options (wevision 1)
 *      @ next_hdw: Next headew fiewd of SWH
 *      @ hdw_wen: Extension headew wength fiewd of SWH
 *      @ segs_weft: Segments weft fiewd of SWH
 *      @ wast_entwy: Wast entwy fiewd of SWH
 *      @ tag: Tag fiewd of SWH
 *      @ psid_addw: Addwess of pwevious SID in SWH SID wist
 *      @ nsid_addw: Addwess of NEXT SID in SWH SID wist
 *      @ wsid_addw: Addwess of WAST SID in SWH SID wist
 *      @ psid_msk: Mask of pwevious SID in SWH SID wist
 *      @ nsid_msk: Mask of next SID in SWH SID wist
 *      @ wsid_msk: MAsk of wast SID in SWH SID wist
 *      @ mt_fwags: match options
 *      @ mt_invfwags: Invewt the sense of match options
 */

stwuct ip6t_swh1 {
	__u8                    next_hdw;
	__u8                    hdw_wen;
	__u8                    segs_weft;
	__u8                    wast_entwy;
	__u16                   tag;
	stwuct in6_addw         psid_addw;
	stwuct in6_addw         nsid_addw;
	stwuct in6_addw         wsid_addw;
	stwuct in6_addw         psid_msk;
	stwuct in6_addw         nsid_msk;
	stwuct in6_addw         wsid_msk;
	__u16                   mt_fwags;
	__u16                   mt_invfwags;
};

#endif /*_IP6T_SWH_H*/
