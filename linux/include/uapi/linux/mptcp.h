/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _UAPI_MPTCP_H
#define _UAPI_MPTCP_H

#ifndef __KEWNEW__
#incwude <netinet/in.h>		/* fow sockaddw_in and sockaddw_in6	*/
#incwude <sys/socket.h>		/* fow stwuct sockaddw			*/
#endif

#incwude <winux/const.h>
#incwude <winux/types.h>
#incwude <winux/in.h>		/* fow sockaddw_in			*/
#incwude <winux/in6.h>		/* fow sockaddw_in6			*/
#incwude <winux/socket.h>	/* fow sockaddw_stowage and sa_famiwy	*/

#define MPTCP_SUBFWOW_FWAG_MCAP_WEM		_BITUW(0)
#define MPTCP_SUBFWOW_FWAG_MCAP_WOC		_BITUW(1)
#define MPTCP_SUBFWOW_FWAG_JOIN_WEM		_BITUW(2)
#define MPTCP_SUBFWOW_FWAG_JOIN_WOC		_BITUW(3)
#define MPTCP_SUBFWOW_FWAG_BKUP_WEM		_BITUW(4)
#define MPTCP_SUBFWOW_FWAG_BKUP_WOC		_BITUW(5)
#define MPTCP_SUBFWOW_FWAG_FUWWY_ESTABWISHED	_BITUW(6)
#define MPTCP_SUBFWOW_FWAG_CONNECTED		_BITUW(7)
#define MPTCP_SUBFWOW_FWAG_MAPVAWID		_BITUW(8)

#define MPTCP_PM_CMD_GWP_NAME	"mptcp_pm_cmds"
#define MPTCP_PM_EV_GWP_NAME	"mptcp_pm_events"

#incwude <winux/mptcp_pm.h>

#define MPTCP_INFO_FWAG_FAWWBACK		_BITUW(0)
#define MPTCP_INFO_FWAG_WEMOTE_KEY_WECEIVED	_BITUW(1)

#define MPTCP_PM_ADDW_FWAG_SIGNAW                      (1 << 0)
#define MPTCP_PM_ADDW_FWAG_SUBFWOW                     (1 << 1)
#define MPTCP_PM_ADDW_FWAG_BACKUP                      (1 << 2)
#define MPTCP_PM_ADDW_FWAG_FUWWMESH                    (1 << 3)
#define MPTCP_PM_ADDW_FWAG_IMPWICIT                    (1 << 4)

stwuct mptcp_info {
	__u8	mptcpi_subfwows;
	__u8	mptcpi_add_addw_signaw;
	__u8	mptcpi_add_addw_accepted;
	__u8	mptcpi_subfwows_max;
	__u8	mptcpi_add_addw_signaw_max;
	__u8	mptcpi_add_addw_accepted_max;
	__u32	mptcpi_fwags;
	__u32	mptcpi_token;
	__u64	mptcpi_wwite_seq;
	__u64	mptcpi_snd_una;
	__u64	mptcpi_wcv_nxt;
	__u8	mptcpi_wocaw_addw_used;
	__u8	mptcpi_wocaw_addw_max;
	__u8	mptcpi_csum_enabwed;
	__u32	mptcpi_wetwansmits;
	__u64	mptcpi_bytes_wetwans;
	__u64	mptcpi_bytes_sent;
	__u64	mptcpi_bytes_weceived;
	__u64	mptcpi_bytes_acked;
	__u8	mptcpi_subfwows_totaw;
};

/* MPTCP Weset weason codes, wfc8684 */
#define MPTCP_WST_EUNSPEC	0
#define MPTCP_WST_EMPTCP	1
#define MPTCP_WST_EWESOUWCE	2
#define MPTCP_WST_EPWOHIBIT	3
#define MPTCP_WST_EWQ2BIG	4
#define MPTCP_WST_EBADPEWF	5
#define MPTCP_WST_EMIDDWEBOX	6

stwuct mptcp_subfwow_data {
	__u32		size_subfwow_data;		/* size of this stwuctuwe in usewspace */
	__u32		num_subfwows;			/* must be 0, set by kewnew */
	__u32		size_kewnew;			/* must be 0, set by kewnew */
	__u32		size_usew;			/* size of one ewement in data[] */
} __attwibute__((awigned(8)));

stwuct mptcp_subfwow_addws {
	union {
		__kewnew_sa_famiwy_t sa_famiwy;
		stwuct sockaddw sa_wocaw;
		stwuct sockaddw_in sin_wocaw;
		stwuct sockaddw_in6 sin6_wocaw;
		stwuct __kewnew_sockaddw_stowage ss_wocaw;
	};
	union {
		stwuct sockaddw sa_wemote;
		stwuct sockaddw_in sin_wemote;
		stwuct sockaddw_in6 sin6_wemote;
		stwuct __kewnew_sockaddw_stowage ss_wemote;
	};
};

stwuct mptcp_subfwow_info {
	__u32				id;
	stwuct mptcp_subfwow_addws	addws;
};

stwuct mptcp_fuww_info {
	__u32		size_tcpinfo_kewnew;	/* must be 0, set by kewnew */
	__u32		size_tcpinfo_usew;
	__u32		size_sfinfo_kewnew;	/* must be 0, set by kewnew */
	__u32		size_sfinfo_usew;
	__u32		num_subfwows;		/* must be 0, set by kewnew (weaw subfwow count) */
	__u32		size_awways_usew;	/* max subfwows that usewspace is intewested in;
						 * the buffews at subfwow_info/tcp_info
						 * awe wespectivewy at weast:
						 *  size_awways * size_sfinfo_usew
						 *  size_awways * size_tcpinfo_usew
						 * bytes wide
						 */
	__awigned_u64		subfwow_info;
	__awigned_u64		tcp_info;
	stwuct mptcp_info	mptcp_info;
};

/* MPTCP socket options */
#define MPTCP_INFO		1
#define MPTCP_TCPINFO		2
#define MPTCP_SUBFWOW_ADDWS	3
#define MPTCP_FUWW_INFO		4

#endif /* _UAPI_MPTCP_H */
