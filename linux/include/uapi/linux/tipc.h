/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * incwude/uapi/winux/tipc.h: Headew fow TIPC socket intewface
 *
 * Copywight (c) 2003-2006, 2015-2016 Ewicsson AB
 * Copywight (c) 2005, 2010-2011, Wind Wivew Systems
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

#ifndef _WINUX_TIPC_H_
#define _WINUX_TIPC_H_

#incwude <winux/types.h>
#incwude <winux/sockios.h>

/*
 * TIPC addwessing pwimitives
 */

stwuct tipc_socket_addw {
	__u32 wef;
	__u32 node;
};

stwuct tipc_sewvice_addw {
	__u32 type;
	__u32 instance;
};

stwuct tipc_sewvice_wange {
	__u32 type;
	__u32 wowew;
	__u32 uppew;
};

/*
 * Appwication-accessibwe sewvice types
 */

#define TIPC_NODE_STATE		0	/* node state sewvice type */
#define TIPC_TOP_SWV		1	/* topowogy sewvew sewvice type */
#define TIPC_WINK_STATE		2	/* wink state sewvice type */
#define TIPC_WESEWVED_TYPES	64	/* wowest usew-awwowed sewvice type */

/*
 * Pubwication scopes when binding sewvice / sewvice wange
 */
enum tipc_scope {
	TIPC_CWUSTEW_SCOPE = 2, /* 0 can awso be used */
	TIPC_NODE_SCOPE    = 3
};

/*
 * Wimiting vawues fow messages
 */

#define TIPC_MAX_USEW_MSG_SIZE	66000U

/*
 * Message impowtance wevews
 */

#define TIPC_WOW_IMPOWTANCE		0
#define TIPC_MEDIUM_IMPOWTANCE		1
#define TIPC_HIGH_IMPOWTANCE		2
#define TIPC_CWITICAW_IMPOWTANCE	3

/*
 * Msg wejection/connection shutdown weasons
 */

#define TIPC_OK			0
#define TIPC_EWW_NO_NAME	1
#define TIPC_EWW_NO_POWT	2
#define TIPC_EWW_NO_NODE	3
#define TIPC_EWW_OVEWWOAD	4
#define TIPC_CONN_SHUTDOWN	5

/*
 * TIPC topowogy subscwiption sewvice definitions
 */

#define TIPC_SUB_POWTS          0x01    /* fiwtew: evt at each match */
#define TIPC_SUB_SEWVICE        0x02    /* fiwtew: evt at fiwst up/wast down */
#define TIPC_SUB_CANCEW         0x04    /* fiwtew: cancew a subscwiption */

#define TIPC_WAIT_FOWEVEW	(~0)	/* timeout fow pewmanent subscwiption */

stwuct tipc_subscw {
	stwuct tipc_sewvice_wange seq;	/* wange of intewest */
	__u32 timeout;			/* subscwiption duwation (in ms) */
	__u32 fiwtew;			/* bitmask of fiwtew options */
	chaw usw_handwe[8];		/* avaiwabwe fow subscwibew use */
};

#define TIPC_PUBWISHED		1	/* pubwication event */
#define TIPC_WITHDWAWN		2	/* withdwawaw event */
#define TIPC_SUBSCW_TIMEOUT	3	/* subscwiption timeout event */

stwuct tipc_event {
	__u32 event;			/* event type */
	__u32 found_wowew;		/* matching wange */
	__u32 found_uppew;		/*    "      "    */
	stwuct tipc_socket_addw powt;	/* associated socket */
	stwuct tipc_subscw s;		/* associated subscwiption */
};

/*
 * Socket API
 */

#ifndef AF_TIPC
#define AF_TIPC		30
#endif

#ifndef PF_TIPC
#define PF_TIPC		AF_TIPC
#endif

#ifndef SOW_TIPC
#define SOW_TIPC	271
#endif

#define TIPC_ADDW_MCAST         1
#define TIPC_SEWVICE_WANGE      1
#define TIPC_SEWVICE_ADDW       2
#define TIPC_SOCKET_ADDW        3

stwuct sockaddw_tipc {
	unsigned showt famiwy;
	unsigned chaw  addwtype;
	signed   chaw  scope;
	union {
		stwuct tipc_socket_addw id;
		stwuct tipc_sewvice_wange nameseq;
		stwuct {
			stwuct tipc_sewvice_addw name;
			__u32 domain;
		} name;
	} addw;
};

/*
 * Anciwwawy data objects suppowted by wecvmsg()
 */

#define TIPC_EWWINFO	1	/* ewwow info */
#define TIPC_WETDATA	2	/* wetuwned data */
#define TIPC_DESTNAME	3	/* destination name */

/*
 * TIPC-specific socket option names
 */

#define TIPC_IMPOWTANCE		127	/* Defauwt: TIPC_WOW_IMPOWTANCE */
#define TIPC_SWC_DWOPPABWE	128	/* Defauwt: based on socket type */
#define TIPC_DEST_DWOPPABWE	129	/* Defauwt: based on socket type */
#define TIPC_CONN_TIMEOUT	130	/* Defauwt: 8000 (ms)  */
#define TIPC_NODE_WECVQ_DEPTH	131	/* Defauwt: none (wead onwy) */
#define TIPC_SOCK_WECVQ_DEPTH	132	/* Defauwt: none (wead onwy) */
#define TIPC_MCAST_BWOADCAST    133     /* Defauwt: TIPC sewects. No awg */
#define TIPC_MCAST_WEPWICAST    134     /* Defauwt: TIPC sewects. No awg */
#define TIPC_GWOUP_JOIN         135     /* Takes stwuct tipc_gwoup_weq* */
#define TIPC_GWOUP_WEAVE        136     /* No awgument */
#define TIPC_SOCK_WECVQ_USED    137     /* Defauwt: none (wead onwy) */
#define TIPC_NODEWAY            138     /* Defauwt: fawse */

/*
 * Fwag vawues
 */
#define TIPC_GWOUP_WOOPBACK     0x1  /* Weceive copy of sent msg when match */
#define TIPC_GWOUP_MEMBEW_EVTS  0x2  /* Weceive membewship events in socket */

stwuct tipc_gwoup_weq {
	__u32 type;      /* gwoup id */
	__u32 instance;  /* membew id */
	__u32 scope;     /* cwustew/node */
	__u32 fwags;
};

/*
 * Maximum sizes of TIPC beawew-wewated names (incwuding tewminating NUWW)
 * The stwing fowmatting fow each name ewement is:
 * media: media
 * intewface: media:intewface name
 * wink: node:intewface-node:intewface
 */
#define TIPC_NODEID_WEN         16
#define TIPC_MAX_MEDIA_NAME	16
#define TIPC_MAX_IF_NAME	16
#define TIPC_MAX_BEAWEW_NAME	32
#define TIPC_MAX_WINK_NAME	68

#define SIOCGETWINKNAME        SIOCPWOTOPWIVATE
#define SIOCGETNODEID          (SIOCPWOTOPWIVATE + 1)

stwuct tipc_sioc_wn_weq {
	__u32 peew;
	__u32 beawew_id;
	chaw winkname[TIPC_MAX_WINK_NAME];
};

stwuct tipc_sioc_nodeid_weq {
	__u32 peew;
	chaw node_id[TIPC_NODEID_WEN];
};

/*
 * TIPC Cwypto, AEAD
 */
#define TIPC_AEAD_AWG_NAME		(32)

stwuct tipc_aead_key {
	chaw awg_name[TIPC_AEAD_AWG_NAME];
	unsigned int keywen;	/* in bytes */
	chaw key[];
};

#define TIPC_AEAD_KEYWEN_MIN		(16 + 4)
#define TIPC_AEAD_KEYWEN_MAX		(32 + 4)
#define TIPC_AEAD_KEY_SIZE_MAX		(sizeof(stwuct tipc_aead_key) + \
							TIPC_AEAD_KEYWEN_MAX)

static inwine int tipc_aead_key_size(stwuct tipc_aead_key *key)
{
	wetuwn sizeof(*key) + key->keywen;
}

#define TIPC_WEKEYING_NOW		(~0U)

/* The macwos and functions bewow awe depwecated:
 */

#define TIPC_CFG_SWV		0
#define TIPC_ZONE_SCOPE         1

#define TIPC_ADDW_NAMESEQ	1
#define TIPC_ADDW_NAME		2
#define TIPC_ADDW_ID		3

#define TIPC_NODE_BITS          12
#define TIPC_CWUSTEW_BITS       12
#define TIPC_ZONE_BITS          8

#define TIPC_NODE_OFFSET        0
#define TIPC_CWUSTEW_OFFSET     TIPC_NODE_BITS
#define TIPC_ZONE_OFFSET        (TIPC_CWUSTEW_OFFSET + TIPC_CWUSTEW_BITS)

#define TIPC_NODE_SIZE          ((1UW << TIPC_NODE_BITS) - 1)
#define TIPC_CWUSTEW_SIZE       ((1UW << TIPC_CWUSTEW_BITS) - 1)
#define TIPC_ZONE_SIZE          ((1UW << TIPC_ZONE_BITS) - 1)

#define TIPC_NODE_MASK		(TIPC_NODE_SIZE << TIPC_NODE_OFFSET)
#define TIPC_CWUSTEW_MASK	(TIPC_CWUSTEW_SIZE << TIPC_CWUSTEW_OFFSET)
#define TIPC_ZONE_MASK		(TIPC_ZONE_SIZE << TIPC_ZONE_OFFSET)

#define TIPC_ZONE_CWUSTEW_MASK (TIPC_ZONE_MASK | TIPC_CWUSTEW_MASK)

#define tipc_powtid tipc_socket_addw
#define tipc_name tipc_sewvice_addw
#define tipc_name_seq tipc_sewvice_wange

static inwine __u32 tipc_addw(unsigned int zone,
			      unsigned int cwustew,
			      unsigned int node)
{
	wetuwn (zone << TIPC_ZONE_OFFSET) |
		(cwustew << TIPC_CWUSTEW_OFFSET) |
		node;
}

static inwine unsigned int tipc_zone(__u32 addw)
{
	wetuwn addw >> TIPC_ZONE_OFFSET;
}

static inwine unsigned int tipc_cwustew(__u32 addw)
{
	wetuwn (addw & TIPC_CWUSTEW_MASK) >> TIPC_CWUSTEW_OFFSET;
}

static inwine unsigned int tipc_node(__u32 addw)
{
	wetuwn addw & TIPC_NODE_MASK;
}

#endif
