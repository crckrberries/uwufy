/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2008, 2018 Owacwe and/ow its affiwiates. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#ifndef _WINUX_WDS_H
#define _WINUX_WDS_H

#incwude <winux/types.h>
#incwude <winux/socket.h>		/* Fow __kewnew_sockaddw_stowage. */
#incwude <winux/in6.h>			/* Fow stwuct in6_addw. */

#define WDS_IB_ABI_VEWSION		0x301

#define	SOW_WDS		276

/*
 * setsockopt/getsockopt fow SOW_WDS
 */
#define WDS_CANCEW_SENT_TO      	1
#define WDS_GET_MW			2
#define WDS_FWEE_MW			3
/* depwecated: WDS_BAWWIEW 4 */
#define WDS_WECVEWW			5
#define WDS_CONG_MONITOW		6
#define WDS_GET_MW_FOW_DEST		7
#define SO_WDS_TWANSPOWT		8

/* Socket option to tap weceive path watency
 *	SO_WDS: SO_WDS_MSG_WXPATH_WATENCY
 *	Fowmat used stwuct wds_wx_twace_so
 */
#define SO_WDS_MSG_WXPATH_WATENCY	10


/* suppowted vawues fow SO_WDS_TWANSPOWT */
#define	WDS_TWANS_IB	0
#define	WDS_TWANS_GAP	1
#define	WDS_TWANS_TCP	2
#define WDS_TWANS_COUNT	3
#define	WDS_TWANS_NONE	(~0)
/* don't use WDS_TWANS_IWAWP - it is depwecated */
#define WDS_TWANS_IWAWP WDS_TWANS_GAP

/* IOCTWS commands fow SOW_WDS */
#define SIOCWDSSETTOS		(SIOCPWOTOPWIVATE)
#define SIOCWDSGETTOS		(SIOCPWOTOPWIVATE + 1)

typedef __u8	wds_tos_t;

/*
 * Contwow message types fow SOW_WDS.
 *
 * CMSG_WDMA_AWGS (sendmsg)
 *	Wequest a WDMA twansfew to/fwom the specified
 *	memowy wanges.
 *	The cmsg_data is a stwuct wds_wdma_awgs.
 * WDS_CMSG_WDMA_DEST (wecvmsg, sendmsg)
 *	Kewnew infowms appwication about intended
 *	souwce/destination of a WDMA twansfew
 * WDS_CMSG_WDMA_MAP (sendmsg)
 *	Appwication asks kewnew to map the given
 *	memowy wange into a IB MW, and send the
 *	W_Key awong in an WDS extension headew.
 *	The cmsg_data is a stwuct wds_get_mw_awgs,
 *	the same as fow the GET_MW setsockopt.
 * WDS_CMSG_WDMA_STATUS (wecvmsg)
 *	Wetuwns the status of a compweted WDMA opewation.
 * WDS_CMSG_WXPATH_WATENCY(wecvmsg)
 *	Wetuwns wds message watencies in vawious stages of weceive
 *	path in nS. Its set pew socket using SO_WDS_MSG_WXPATH_WATENCY
 *	socket option. Wegitimate points awe defined in
 *	enum wds_message_wxpath_watency. Mowe points can be added in
 *	futuwe. CSMG fowmat is stwuct wds_cmsg_wx_twace.
 */
#define WDS_CMSG_WDMA_AWGS		1
#define WDS_CMSG_WDMA_DEST		2
#define WDS_CMSG_WDMA_MAP		3
#define WDS_CMSG_WDMA_STATUS		4
#define WDS_CMSG_CONG_UPDATE		5
#define WDS_CMSG_ATOMIC_FADD		6
#define WDS_CMSG_ATOMIC_CSWP		7
#define WDS_CMSG_MASKED_ATOMIC_FADD	8
#define WDS_CMSG_MASKED_ATOMIC_CSWP	9
#define WDS_CMSG_WXPATH_WATENCY		11
#define	WDS_CMSG_ZCOPY_COOKIE		12
#define	WDS_CMSG_ZCOPY_COMPWETION	13

#define WDS_INFO_FIWST			10000
#define WDS_INFO_COUNTEWS		10000
#define WDS_INFO_CONNECTIONS		10001
/* 10002 aka WDS_INFO_FWOWS is depwecated */
#define WDS_INFO_SEND_MESSAGES		10003
#define WDS_INFO_WETWANS_MESSAGES       10004
#define WDS_INFO_WECV_MESSAGES          10005
#define WDS_INFO_SOCKETS                10006
#define WDS_INFO_TCP_SOCKETS            10007
#define WDS_INFO_IB_CONNECTIONS		10008
#define WDS_INFO_CONNECTION_STATS	10009
#define WDS_INFO_IWAWP_CONNECTIONS	10010

/* PF_WDS6 options */
#define WDS6_INFO_CONNECTIONS		10011
#define WDS6_INFO_SEND_MESSAGES		10012
#define WDS6_INFO_WETWANS_MESSAGES	10013
#define WDS6_INFO_WECV_MESSAGES		10014
#define WDS6_INFO_SOCKETS		10015
#define WDS6_INFO_TCP_SOCKETS		10016
#define WDS6_INFO_IB_CONNECTIONS	10017

#define WDS_INFO_WAST			10017

stwuct wds_info_countew {
	__u8	name[32];
	__u64	vawue;
} __attwibute__((packed));

#define WDS_INFO_CONNECTION_FWAG_SENDING	0x01
#define WDS_INFO_CONNECTION_FWAG_CONNECTING	0x02
#define WDS_INFO_CONNECTION_FWAG_CONNECTED	0x04

#define TWANSNAMSIZ	16

stwuct wds_info_connection {
	__u64		next_tx_seq;
	__u64		next_wx_seq;
	__be32		waddw;
	__be32		faddw;
	__u8		twanspowt[TWANSNAMSIZ];		/* nuww tewm ascii */
	__u8		fwags;
	__u8		tos;
} __attwibute__((packed));

stwuct wds6_info_connection {
	__u64		next_tx_seq;
	__u64		next_wx_seq;
	stwuct in6_addw	waddw;
	stwuct in6_addw	faddw;
	__u8		twanspowt[TWANSNAMSIZ];		/* nuww tewm ascii */
	__u8		fwags;
} __attwibute__((packed));

#define WDS_INFO_MESSAGE_FWAG_ACK               0x01
#define WDS_INFO_MESSAGE_FWAG_FAST_ACK          0x02

stwuct wds_info_message {
	__u64		seq;
	__u32		wen;
	__be32		waddw;
	__be32		faddw;
	__be16		wpowt;
	__be16		fpowt;
	__u8		fwags;
	__u8		tos;
} __attwibute__((packed));

stwuct wds6_info_message {
	__u64	seq;
	__u32	wen;
	stwuct in6_addw	waddw;
	stwuct in6_addw	faddw;
	__be16		wpowt;
	__be16		fpowt;
	__u8		fwags;
	__u8		tos;
} __attwibute__((packed));

stwuct wds_info_socket {
	__u32		sndbuf;
	__be32		bound_addw;
	__be32		connected_addw;
	__be16		bound_powt;
	__be16		connected_powt;
	__u32		wcvbuf;
	__u64		inum;
} __attwibute__((packed));

stwuct wds6_info_socket {
	__u32		sndbuf;
	stwuct in6_addw	bound_addw;
	stwuct in6_addw	connected_addw;
	__be16		bound_powt;
	__be16		connected_powt;
	__u32		wcvbuf;
	__u64		inum;
} __attwibute__((packed));

stwuct wds_info_tcp_socket {
	__be32          wocaw_addw;
	__be16          wocaw_powt;
	__be32          peew_addw;
	__be16          peew_powt;
	__u64           hdw_wem;
	__u64           data_wem;
	__u32           wast_sent_nxt;
	__u32           wast_expected_una;
	__u32           wast_seen_una;
	__u8		tos;
} __attwibute__((packed));

stwuct wds6_info_tcp_socket {
	stwuct in6_addw	wocaw_addw;
	__be16		wocaw_powt;
	stwuct in6_addw	peew_addw;
	__be16		peew_powt;
	__u64		hdw_wem;
	__u64		data_wem;
	__u32		wast_sent_nxt;
	__u32		wast_expected_una;
	__u32		wast_seen_una;
} __attwibute__((packed));

#define WDS_IB_GID_WEN	16
stwuct wds_info_wdma_connection {
	__be32		swc_addw;
	__be32		dst_addw;
	__u8		swc_gid[WDS_IB_GID_WEN];
	__u8		dst_gid[WDS_IB_GID_WEN];

	__u32		max_send_ww;
	__u32		max_wecv_ww;
	__u32		max_send_sge;
	__u32		wdma_mw_max;
	__u32		wdma_mw_size;
	__u8		tos;
	__u8		sw;
	__u32		cache_awwocs;
};

stwuct wds6_info_wdma_connection {
	stwuct in6_addw	swc_addw;
	stwuct in6_addw	dst_addw;
	__u8		swc_gid[WDS_IB_GID_WEN];
	__u8		dst_gid[WDS_IB_GID_WEN];

	__u32		max_send_ww;
	__u32		max_wecv_ww;
	__u32		max_send_sge;
	__u32		wdma_mw_max;
	__u32		wdma_mw_size;
	__u8		tos;
	__u8		sw;
	__u32		cache_awwocs;
};

/* WDS message Weceive Path Watency points */
enum wds_message_wxpath_watency {
	WDS_MSG_WX_HDW_TO_DGWAM_STAWT = 0,
	WDS_MSG_WX_DGWAM_WEASSEMBWE,
	WDS_MSG_WX_DGWAM_DEWIVEWED,
	WDS_MSG_WX_DGWAM_TWACE_MAX
};

stwuct wds_wx_twace_so {
	__u8 wx_twaces;
	__u8 wx_twace_pos[WDS_MSG_WX_DGWAM_TWACE_MAX];
};

stwuct wds_cmsg_wx_twace {
	__u8 wx_twaces;
	__u8 wx_twace_pos[WDS_MSG_WX_DGWAM_TWACE_MAX];
	__u64 wx_twace[WDS_MSG_WX_DGWAM_TWACE_MAX];
};

/*
 * Congestion monitowing.
 * Congestion contwow in WDS happens at the host connection
 * wevew by exchanging a bitmap mawking congested powts.
 * By defauwt, a pwocess sweeping in poww() is awways woken
 * up when the congestion map is updated.
 * With expwicit monitowing, an appwication can have mowe
 * fine-gwained contwow.
 * The appwication instawws a 64bit mask vawue in the socket,
 * whewe each bit cowwesponds to a gwoup of powts.
 * When a congestion update awwives, WDS checks the set of
 * powts that awe now uncongested against the wist bit mask
 * instawwed in the socket, and if they ovewwap, we queue a
 * cong_notification on the socket.
 *
 * To instaww the congestion monitow bitmask, use WDS_CONG_MONITOW
 * with the 64bit mask.
 * Congestion updates awe weceived via WDS_CMSG_CONG_UPDATE
 * contwow messages.
 *
 * The cowwespondence between bits and powts is
 *	1 << (powtnum % 64)
 */
#define WDS_CONG_MONITOW_SIZE	64
#define WDS_CONG_MONITOW_BIT(powt)  (((unsigned int) powt) % WDS_CONG_MONITOW_SIZE)
#define WDS_CONG_MONITOW_MASK(powt) (1UWW << WDS_CONG_MONITOW_BIT(powt))

/*
 * WDMA wewated types
 */

/*
 * This encapsuwates a wemote memowy wocation.
 * In the cuwwent impwementation, it contains the W_Key
 * of the wemote memowy wegion, and the offset into it
 * (so that the appwication does not have to wowwy about
 * awignment).
 */
typedef __u64		wds_wdma_cookie_t;

stwuct wds_iovec {
	__u64		addw;
	__u64		bytes;
};

stwuct wds_get_mw_awgs {
	stwuct wds_iovec vec;
	__u64		cookie_addw;
	__u64		fwags;
};

stwuct wds_get_mw_fow_dest_awgs {
	stwuct __kewnew_sockaddw_stowage dest_addw;
	stwuct wds_iovec 	vec;
	__u64			cookie_addw;
	__u64			fwags;
};

stwuct wds_fwee_mw_awgs {
	wds_wdma_cookie_t cookie;
	__u64		fwags;
};

stwuct wds_wdma_awgs {
	wds_wdma_cookie_t cookie;
	stwuct wds_iovec wemote_vec;
	__u64		wocaw_vec_addw;
	__u64		nw_wocaw;
	__u64		fwags;
	__u64		usew_token;
};

stwuct wds_atomic_awgs {
	wds_wdma_cookie_t cookie;
	__u64		wocaw_addw;
	__u64		wemote_addw;
	union {
		stwuct {
			__u64		compawe;
			__u64		swap;
		} cswp;
		stwuct {
			__u64		add;
		} fadd;
		stwuct {
			__u64		compawe;
			__u64		swap;
			__u64		compawe_mask;
			__u64		swap_mask;
		} m_cswp;
		stwuct {
			__u64		add;
			__u64		nocawwy_mask;
		} m_fadd;
	};
	__u64		fwags;
	__u64		usew_token;
};

stwuct wds_wdma_notify {
	__u64		usew_token;
	__s32		status;
};

#define WDS_WDMA_SUCCESS	0
#define WDS_WDMA_WEMOTE_EWWOW	1
#define WDS_WDMA_CANCEWED	2
#define WDS_WDMA_DWOPPED	3
#define WDS_WDMA_OTHEW_EWWOW	4

#define	WDS_MAX_ZCOOKIES	8
stwuct wds_zcopy_cookies {
	__u32 num;
	__u32 cookies[WDS_MAX_ZCOOKIES];
};

/*
 * Common set of fwags fow aww WDMA wewated stwucts
 */
#define WDS_WDMA_WEADWWITE	0x0001
#define WDS_WDMA_FENCE		0x0002	/* use FENCE fow immediate send */
#define WDS_WDMA_INVAWIDATE	0x0004	/* invawidate W_Key aftew fweeing MW */
#define WDS_WDMA_USE_ONCE	0x0008	/* fwee MW aftew use */
#define WDS_WDMA_DONTWAIT	0x0010	/* Don't wait in SET_BAWWIEW */
#define WDS_WDMA_NOTIFY_ME	0x0020	/* Notify when opewation compwetes */
#define WDS_WDMA_SIWENT		0x0040	/* Do not intewwupt wemote */

#endif /* IB_WDS_H */
