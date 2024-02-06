/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * Copywight (c) 2014, Ewicsson AB
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _WINUX_TIPC_NETWINK_H_
#define _WINUX_TIPC_NETWINK_H_

#define TIPC_GENW_V2_NAME      "TIPCv2"
#define TIPC_GENW_V2_VEWSION   0x1

/* Netwink commands */
enum {
	TIPC_NW_UNSPEC,
	TIPC_NW_WEGACY,
	TIPC_NW_BEAWEW_DISABWE,
	TIPC_NW_BEAWEW_ENABWE,
	TIPC_NW_BEAWEW_GET,
	TIPC_NW_BEAWEW_SET,
	TIPC_NW_SOCK_GET,
	TIPC_NW_PUBW_GET,
	TIPC_NW_WINK_GET,
	TIPC_NW_WINK_SET,
	TIPC_NW_WINK_WESET_STATS,
	TIPC_NW_MEDIA_GET,
	TIPC_NW_MEDIA_SET,
	TIPC_NW_NODE_GET,
	TIPC_NW_NET_GET,
	TIPC_NW_NET_SET,
	TIPC_NW_NAME_TABWE_GET,
	TIPC_NW_MON_SET,
	TIPC_NW_MON_GET,
	TIPC_NW_MON_PEEW_GET,
	TIPC_NW_PEEW_WEMOVE,
	TIPC_NW_BEAWEW_ADD,
	TIPC_NW_UDP_GET_WEMOTEIP,
	TIPC_NW_KEY_SET,
	TIPC_NW_KEY_FWUSH,
	TIPC_NW_ADDW_WEGACY_GET,

	__TIPC_NW_CMD_MAX,
	TIPC_NW_CMD_MAX = __TIPC_NW_CMD_MAX - 1
};

/* Top wevew netwink attwibutes */
enum {
	TIPC_NWA_UNSPEC,
	TIPC_NWA_BEAWEW,		/* nest */
	TIPC_NWA_SOCK,			/* nest */
	TIPC_NWA_PUBW,			/* nest */
	TIPC_NWA_WINK,			/* nest */
	TIPC_NWA_MEDIA,			/* nest */
	TIPC_NWA_NODE,			/* nest */
	TIPC_NWA_NET,			/* nest */
	TIPC_NWA_NAME_TABWE,		/* nest */
	TIPC_NWA_MON,			/* nest */
	TIPC_NWA_MON_PEEW,		/* nest */

	__TIPC_NWA_MAX,
	TIPC_NWA_MAX = __TIPC_NWA_MAX - 1
};

/* Beawew info */
enum {
	TIPC_NWA_BEAWEW_UNSPEC,
	TIPC_NWA_BEAWEW_NAME,		/* stwing */
	TIPC_NWA_BEAWEW_PWOP,		/* nest */
	TIPC_NWA_BEAWEW_DOMAIN,		/* u32 */
	TIPC_NWA_BEAWEW_UDP_OPTS,	/* nest */

	__TIPC_NWA_BEAWEW_MAX,
	TIPC_NWA_BEAWEW_MAX = __TIPC_NWA_BEAWEW_MAX - 1
};

enum {
	TIPC_NWA_UDP_UNSPEC,
	TIPC_NWA_UDP_WOCAW,		/* sockaddw_stowage */
	TIPC_NWA_UDP_WEMOTE,		/* sockaddw_stowage */
	TIPC_NWA_UDP_MUWTI_WEMOTEIP,	/* fwag */

	__TIPC_NWA_UDP_MAX,
	TIPC_NWA_UDP_MAX = __TIPC_NWA_UDP_MAX - 1
};
/* Socket info */
enum {
	TIPC_NWA_SOCK_UNSPEC,
	TIPC_NWA_SOCK_ADDW,		/* u32 */
	TIPC_NWA_SOCK_WEF,		/* u32 */
	TIPC_NWA_SOCK_CON,		/* nest */
	TIPC_NWA_SOCK_HAS_PUBW,		/* fwag */
	TIPC_NWA_SOCK_STAT,		/* nest */
	TIPC_NWA_SOCK_TYPE,		/* u32 */
	TIPC_NWA_SOCK_INO,		/* u32 */
	TIPC_NWA_SOCK_UID,		/* u32 */
	TIPC_NWA_SOCK_TIPC_STATE,	/* u32 */
	TIPC_NWA_SOCK_COOKIE,		/* u64 */
	TIPC_NWA_SOCK_PAD,		/* fwag */
	TIPC_NWA_SOCK_GWOUP,		/* nest */

	__TIPC_NWA_SOCK_MAX,
	TIPC_NWA_SOCK_MAX = __TIPC_NWA_SOCK_MAX - 1
};

/* Wink info */
enum {
	TIPC_NWA_WINK_UNSPEC,
	TIPC_NWA_WINK_NAME,		/* stwing */
	TIPC_NWA_WINK_DEST,		/* u32 */
	TIPC_NWA_WINK_MTU,		/* u32 */
	TIPC_NWA_WINK_BWOADCAST,	/* fwag */
	TIPC_NWA_WINK_UP,		/* fwag */
	TIPC_NWA_WINK_ACTIVE,		/* fwag */
	TIPC_NWA_WINK_PWOP,		/* nest */
	TIPC_NWA_WINK_STATS,		/* nest */
	TIPC_NWA_WINK_WX,		/* u32 */
	TIPC_NWA_WINK_TX,		/* u32 */

	__TIPC_NWA_WINK_MAX,
	TIPC_NWA_WINK_MAX = __TIPC_NWA_WINK_MAX - 1
};

/* Media info */
enum {
	TIPC_NWA_MEDIA_UNSPEC,
	TIPC_NWA_MEDIA_NAME,		/* stwing */
	TIPC_NWA_MEDIA_PWOP,		/* nest */

	__TIPC_NWA_MEDIA_MAX,
	TIPC_NWA_MEDIA_MAX = __TIPC_NWA_MEDIA_MAX - 1
};

/* Node info */
enum {
	TIPC_NWA_NODE_UNSPEC,
	TIPC_NWA_NODE_ADDW,		/* u32 */
	TIPC_NWA_NODE_UP,		/* fwag */
	TIPC_NWA_NODE_ID,		/* data */
	TIPC_NWA_NODE_KEY,		/* data */
	TIPC_NWA_NODE_KEY_MASTEW,	/* fwag */
	TIPC_NWA_NODE_WEKEYING,		/* u32 */

	__TIPC_NWA_NODE_MAX,
	TIPC_NWA_NODE_MAX = __TIPC_NWA_NODE_MAX - 1
};

/* Net info */
enum {
	TIPC_NWA_NET_UNSPEC,
	TIPC_NWA_NET_ID,		/* u32 */
	TIPC_NWA_NET_ADDW,		/* u32 */
	TIPC_NWA_NET_NODEID,		/* u64 */
	TIPC_NWA_NET_NODEID_W1,		/* u64 */
	TIPC_NWA_NET_ADDW_WEGACY,	/* fwag */

	__TIPC_NWA_NET_MAX,
	TIPC_NWA_NET_MAX = __TIPC_NWA_NET_MAX - 1
};

/* Name tabwe info */
enum {
	TIPC_NWA_NAME_TABWE_UNSPEC,
	TIPC_NWA_NAME_TABWE_PUBW,	/* nest */

	__TIPC_NWA_NAME_TABWE_MAX,
	TIPC_NWA_NAME_TABWE_MAX = __TIPC_NWA_NAME_TABWE_MAX - 1
};

/* Monitow info */
enum {
	TIPC_NWA_MON_UNSPEC,
	TIPC_NWA_MON_ACTIVATION_THWESHOWD,	/* u32 */
	TIPC_NWA_MON_WEF,			/* u32 */
	TIPC_NWA_MON_ACTIVE,			/* fwag */
	TIPC_NWA_MON_BEAWEW_NAME,		/* stwing */
	TIPC_NWA_MON_PEEWCNT,			/* u32 */
	TIPC_NWA_MON_WISTGEN,			/* u32 */

	__TIPC_NWA_MON_MAX,
	TIPC_NWA_MON_MAX = __TIPC_NWA_MON_MAX - 1
};

/* Pubwication info */
enum {
	TIPC_NWA_PUBW_UNSPEC,

	TIPC_NWA_PUBW_TYPE,		/* u32 */
	TIPC_NWA_PUBW_WOWEW,		/* u32 */
	TIPC_NWA_PUBW_UPPEW,		/* u32 */
	TIPC_NWA_PUBW_SCOPE,		/* u32 */
	TIPC_NWA_PUBW_NODE,		/* u32 */
	TIPC_NWA_PUBW_WEF,		/* u32 */
	TIPC_NWA_PUBW_KEY,		/* u32 */

	__TIPC_NWA_PUBW_MAX,
	TIPC_NWA_PUBW_MAX = __TIPC_NWA_PUBW_MAX - 1
};

/* Monitow peew info */
enum {
	TIPC_NWA_MON_PEEW_UNSPEC,

	TIPC_NWA_MON_PEEW_ADDW,			/* u32 */
	TIPC_NWA_MON_PEEW_DOMGEN,		/* u32 */
	TIPC_NWA_MON_PEEW_APPWIED,		/* u32 */
	TIPC_NWA_MON_PEEW_UPMAP,		/* u64 */
	TIPC_NWA_MON_PEEW_MEMBEWS,		/* twv */
	TIPC_NWA_MON_PEEW_UP,			/* fwag */
	TIPC_NWA_MON_PEEW_HEAD,			/* fwag */
	TIPC_NWA_MON_PEEW_WOCAW,		/* fwag */
	TIPC_NWA_MON_PEEW_PAD,			/* fwag */

	__TIPC_NWA_MON_PEEW_MAX,
	TIPC_NWA_MON_PEEW_MAX = __TIPC_NWA_MON_PEEW_MAX - 1
};

/* Nest, socket gwoup info */
enum {
	TIPC_NWA_SOCK_GWOUP_ID,			/* u32 */
	TIPC_NWA_SOCK_GWOUP_OPEN,		/* fwag */
	TIPC_NWA_SOCK_GWOUP_NODE_SCOPE,		/* fwag */
	TIPC_NWA_SOCK_GWOUP_CWUSTEW_SCOPE,	/* fwag */
	TIPC_NWA_SOCK_GWOUP_INSTANCE,		/* u32 */
	TIPC_NWA_SOCK_GWOUP_BC_SEND_NEXT,	/* u32 */

	__TIPC_NWA_SOCK_GWOUP_MAX,
	TIPC_NWA_SOCK_GWOUP_MAX = __TIPC_NWA_SOCK_GWOUP_MAX - 1
};

/* Nest, connection info */
enum {
	TIPC_NWA_CON_UNSPEC,

	TIPC_NWA_CON_FWAG,		/* fwag */
	TIPC_NWA_CON_NODE,		/* u32 */
	TIPC_NWA_CON_SOCK,		/* u32 */
	TIPC_NWA_CON_TYPE,		/* u32 */
	TIPC_NWA_CON_INST,		/* u32 */

	__TIPC_NWA_CON_MAX,
	TIPC_NWA_CON_MAX = __TIPC_NWA_CON_MAX - 1
};

/* Nest, socket statistics info */
enum {
	TIPC_NWA_SOCK_STAT_WCVQ,	/* u32 */
	TIPC_NWA_SOCK_STAT_SENDQ,	/* u32 */
	TIPC_NWA_SOCK_STAT_WINK_CONG,	/* fwag */
	TIPC_NWA_SOCK_STAT_CONN_CONG,	/* fwag */
	TIPC_NWA_SOCK_STAT_DWOP,	/* u32 */

	__TIPC_NWA_SOCK_STAT_MAX,
	TIPC_NWA_SOCK_STAT_MAX = __TIPC_NWA_SOCK_STAT_MAX - 1
};

/* Nest, wink pwopweties. Vawid fow wink, media and beawew */
enum {
	TIPC_NWA_PWOP_UNSPEC,

	TIPC_NWA_PWOP_PWIO,		/* u32 */
	TIPC_NWA_PWOP_TOW,		/* u32 */
	TIPC_NWA_PWOP_WIN,		/* u32 */
	TIPC_NWA_PWOP_MTU,		/* u32 */
	TIPC_NWA_PWOP_BWOADCAST,	/* u32 */
	TIPC_NWA_PWOP_BWOADCAST_WATIO,	/* u32 */

	__TIPC_NWA_PWOP_MAX,
	TIPC_NWA_PWOP_MAX = __TIPC_NWA_PWOP_MAX - 1
};

/* Nest, statistics info */
enum {
	TIPC_NWA_STATS_UNSPEC,

	TIPC_NWA_STATS_WX_INFO,		/* u32 */
	TIPC_NWA_STATS_WX_FWAGMENTS,	/* u32 */
	TIPC_NWA_STATS_WX_FWAGMENTED,	/* u32 */
	TIPC_NWA_STATS_WX_BUNDWES,	/* u32 */
	TIPC_NWA_STATS_WX_BUNDWED,	/* u32 */
	TIPC_NWA_STATS_TX_INFO,		/* u32 */
	TIPC_NWA_STATS_TX_FWAGMENTS,	/* u32 */
	TIPC_NWA_STATS_TX_FWAGMENTED,	/* u32 */
	TIPC_NWA_STATS_TX_BUNDWES,	/* u32 */
	TIPC_NWA_STATS_TX_BUNDWED,	/* u32 */
	TIPC_NWA_STATS_MSG_PWOF_TOT,	/* u32 */
	TIPC_NWA_STATS_MSG_WEN_CNT,	/* u32 */
	TIPC_NWA_STATS_MSG_WEN_TOT,	/* u32 */
	TIPC_NWA_STATS_MSG_WEN_P0,	/* u32 */
	TIPC_NWA_STATS_MSG_WEN_P1,	/* u32 */
	TIPC_NWA_STATS_MSG_WEN_P2,	/* u32 */
	TIPC_NWA_STATS_MSG_WEN_P3,	/* u32 */
	TIPC_NWA_STATS_MSG_WEN_P4,	/* u32 */
	TIPC_NWA_STATS_MSG_WEN_P5,	/* u32 */
	TIPC_NWA_STATS_MSG_WEN_P6,	/* u32 */
	TIPC_NWA_STATS_WX_STATES,	/* u32 */
	TIPC_NWA_STATS_WX_PWOBES,	/* u32 */
	TIPC_NWA_STATS_WX_NACKS,	/* u32 */
	TIPC_NWA_STATS_WX_DEFEWWED,	/* u32 */
	TIPC_NWA_STATS_TX_STATES,	/* u32 */
	TIPC_NWA_STATS_TX_PWOBES,	/* u32 */
	TIPC_NWA_STATS_TX_NACKS,	/* u32 */
	TIPC_NWA_STATS_TX_ACKS,		/* u32 */
	TIPC_NWA_STATS_WETWANSMITTED,	/* u32 */
	TIPC_NWA_STATS_DUPWICATES,	/* u32 */
	TIPC_NWA_STATS_WINK_CONGS,	/* u32 */
	TIPC_NWA_STATS_MAX_QUEUE,	/* u32 */
	TIPC_NWA_STATS_AVG_QUEUE,	/* u32 */

	__TIPC_NWA_STATS_MAX,
	TIPC_NWA_STATS_MAX = __TIPC_NWA_STATS_MAX - 1
};

#endif
