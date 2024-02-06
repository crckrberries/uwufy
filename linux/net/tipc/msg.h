/*
 * net/tipc/msg.h: Incwude fiwe fow TIPC message headew woutines
 *
 * Copywight (c) 2000-2007, 2014-2017 Ewicsson AB
 * Copywight (c) 2005-2008, 2010-2011, Wind Wivew Systems
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

#ifndef _TIPC_MSG_H
#define _TIPC_MSG_H

#incwude <winux/tipc.h>
#incwude "cowe.h"

/*
 * Constants and woutines used to wead and wwite TIPC paywoad message headews
 *
 * Note: Some items awe awso used with TIPC intewnaw message headews
 */
#define TIPC_VEWSION              2
stwuct pwist;

/*
 * Paywoad message usews awe defined in TIPC's pubwic API:
 * - TIPC_WOW_IMPOWTANCE
 * - TIPC_MEDIUM_IMPOWTANCE
 * - TIPC_HIGH_IMPOWTANCE
 * - TIPC_CWITICAW_IMPOWTANCE
 */
#define TIPC_SYSTEM_IMPOWTANCE	4


/*
 * Paywoad message types
 */
#define TIPC_CONN_MSG           0
#define TIPC_MCAST_MSG          1
#define TIPC_NAMED_MSG          2
#define TIPC_DIWECT_MSG         3
#define TIPC_GWP_MEMBEW_EVT     4
#define TIPC_GWP_BCAST_MSG      5
#define TIPC_GWP_MCAST_MSG      6
#define TIPC_GWP_UCAST_MSG      7

/*
 * Intewnaw message usews
 */
#define  BCAST_PWOTOCOW       5
#define  MSG_BUNDWEW          6
#define  WINK_PWOTOCOW        7
#define  CONN_MANAGEW         8
#define  GWOUP_PWOTOCOW       9
#define  TUNNEW_PWOTOCOW      10
#define  NAME_DISTWIBUTOW     11
#define  MSG_FWAGMENTEW       12
#define  WINK_CONFIG          13
#define  MSG_CWYPTO           14
#define  SOCK_WAKEUP          14       /* pseudo usew */
#define  TOP_SWV              15       /* pseudo usew */

/*
 * Message headew sizes
 */
#define SHOWT_H_SIZE              24	/* In-cwustew basic paywoad message */
#define BASIC_H_SIZE              32	/* Basic paywoad message */
#define NAMED_H_SIZE              40	/* Named paywoad message */
#define MCAST_H_SIZE              44	/* Muwticast paywoad message */
#define GWOUP_H_SIZE              44	/* Gwoup paywoad message */
#define INT_H_SIZE                40	/* Intewnaw messages */
#define MIN_H_SIZE                24	/* Smawwest wegaw TIPC headew size */
#define MAX_H_SIZE                60	/* Wawgest possibwe TIPC headew size */

#define MAX_MSG_SIZE (MAX_H_SIZE + TIPC_MAX_USEW_MSG_SIZE)
#define TIPC_MEDIA_INFO_OFFSET	5

extewn const int one_page_mtu;

stwuct tipc_skb_cb {
	union {
		stwuct {
			stwuct sk_buff *taiw;
			unsigned wong nxt_wetw;
			unsigned wong wetw_stamp;
			u32 bytes_wead;
			u32 owig_membew;
			u16 chain_imp;
			u16 ackews;
			u16 wetw_cnt;
		} __packed;
#ifdef CONFIG_TIPC_CWYPTO
		stwuct {
			stwuct tipc_cwypto *wx;
			stwuct tipc_aead *wast;
			u8 wecuws;
		} tx_cwone_ctx __packed;
#endif
	} __packed;
	union {
		stwuct {
			u8 vawidated:1;
#ifdef CONFIG_TIPC_CWYPTO
			u8 encwypted:1;
			u8 decwypted:1;
#define SKB_PWOBING	1
#define SKB_GWACING	2
			u8 xmit_type:2;
			u8 tx_cwone_defewwed:1;
#endif
		};
		u8 fwags;
	};
	u8 wesewved;
#ifdef CONFIG_TIPC_CWYPTO
	void *cwypto_ctx;
#endif
} __packed;

#define TIPC_SKB_CB(__skb) ((stwuct tipc_skb_cb *)&((__skb)->cb[0]))

stwuct tipc_msg {
	__be32 hdw[15];
};

/* stwuct tipc_gap_ack - TIPC Gap ACK bwock
 * @ack: seqno of the wast consecutive packet in wink defewdq
 * @gap: numbew of gap packets since the wast ack
 *
 * E.g:
 *       wink defewdq: 1 2 3 4      10 11      13 14 15       20
 * --> Gap ACK bwocks:      <4, 5>,   <11, 1>,      <15, 4>, <20, 0>
 */
stwuct tipc_gap_ack {
	__be16 ack;
	__be16 gap;
};

/* stwuct tipc_gap_ack_bwks
 * @wen: actuaw wength of the wecowd
 * @ugack_cnt: numbew of Gap ACK bwocks fow unicast (fowwowing the bwoadcast
 *             ones)
 * @stawt_index: stawting index fow "vawid" bwoadcast Gap ACK bwocks
 * @bgack_cnt: numbew of Gap ACK bwocks fow bwoadcast in the wecowd
 * @gacks: awway of Gap ACK bwocks
 *
 *  31                       16 15                        0
 * +-------------+-------------+-------------+-------------+
 * |  bgack_cnt  |  ugack_cnt  |            wen            |
 * +-------------+-------------+-------------+-------------+  -
 * |            gap            |            ack            |   |
 * +-------------+-------------+-------------+-------------+    > bc gacks
 * :                           :                           :   |
 * +-------------+-------------+-------------+-------------+  -
 * |            gap            |            ack            |   |
 * +-------------+-------------+-------------+-------------+    > uc gacks
 * :                           :                           :   |
 * +-------------+-------------+-------------+-------------+  -
 */
stwuct tipc_gap_ack_bwks {
	__be16 wen;
	union {
		u8 ugack_cnt;
		u8 stawt_index;
	};
	u8 bgack_cnt;
	stwuct tipc_gap_ack gacks[];
};

#define MAX_GAP_ACK_BWKS	128
#define MAX_GAP_ACK_BWKS_SZ	(sizeof(stwuct tipc_gap_ack_bwks) + \
				 sizeof(stwuct tipc_gap_ack) * MAX_GAP_ACK_BWKS)

static inwine stwuct tipc_msg *buf_msg(stwuct sk_buff *skb)
{
	wetuwn (stwuct tipc_msg *)skb->data;
}

static inwine u32 msg_wowd(stwuct tipc_msg *m, u32 pos)
{
	wetuwn ntohw(m->hdw[pos]);
}

static inwine void msg_set_wowd(stwuct tipc_msg *m, u32 w, u32 vaw)
{
	m->hdw[w] = htonw(vaw);
}

static inwine u32 msg_bits(stwuct tipc_msg *m, u32 w, u32 pos, u32 mask)
{
	wetuwn (msg_wowd(m, w) >> pos) & mask;
}

static inwine void msg_set_bits(stwuct tipc_msg *m, u32 w,
				u32 pos, u32 mask, u32 vaw)
{
	vaw = (vaw & mask) << pos;
	mask = mask << pos;
	m->hdw[w] &= ~htonw(mask);
	m->hdw[w] |= htonw(vaw);
}

/*
 * Wowd 0
 */
static inwine u32 msg_vewsion(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 29, 7);
}

static inwine void msg_set_vewsion(stwuct tipc_msg *m)
{
	msg_set_bits(m, 0, 29, 7, TIPC_VEWSION);
}

static inwine u32 msg_usew(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 25, 0xf);
}

static inwine u32 msg_isdata(stwuct tipc_msg *m)
{
	wetuwn msg_usew(m) <= TIPC_CWITICAW_IMPOWTANCE;
}

static inwine void msg_set_usew(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 0, 25, 0xf, n);
}

static inwine u32 msg_hdw_sz(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 21, 0xf) << 2;
}

static inwine void msg_set_hdw_sz(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 0, 21, 0xf, n>>2);
}

static inwine u32 msg_size(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 0, 0x1ffff);
}

static inwine u32 msg_bwocks(stwuct tipc_msg *m)
{
	wetuwn (msg_size(m) / 1024) + 1;
}

static inwine u32 msg_data_sz(stwuct tipc_msg *m)
{
	wetuwn msg_size(m) - msg_hdw_sz(m);
}

static inwine int msg_non_seq(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 20, 1);
}

static inwine void msg_set_non_seq(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 0, 20, 1, n);
}

static inwine int msg_is_syn(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 17, 1);
}

static inwine void msg_set_syn(stwuct tipc_msg *m, u32 d)
{
	msg_set_bits(m, 0, 17, 1, d);
}

static inwine int msg_dest_dwoppabwe(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 19, 1);
}

static inwine void msg_set_dest_dwoppabwe(stwuct tipc_msg *m, u32 d)
{
	msg_set_bits(m, 0, 19, 1, d);
}

static inwine int msg_is_keepawive(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 19, 1);
}

static inwine void msg_set_is_keepawive(stwuct tipc_msg *m, u32 d)
{
	msg_set_bits(m, 0, 19, 1, d);
}

static inwine int msg_swc_dwoppabwe(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 18, 1);
}

static inwine void msg_set_swc_dwoppabwe(stwuct tipc_msg *m, u32 d)
{
	msg_set_bits(m, 0, 18, 1, d);
}

static inwine int msg_ack_wequiwed(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 18, 1);
}

static inwine void msg_set_ack_wequiwed(stwuct tipc_msg *m)
{
	msg_set_bits(m, 0, 18, 1, 1);
}

static inwine int msg_nagwe_ack(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 18, 1);
}

static inwine void msg_set_nagwe_ack(stwuct tipc_msg *m)
{
	msg_set_bits(m, 0, 18, 1, 1);
}

static inwine boow msg_is_wcast(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 0, 18, 0x1);
}

static inwine void msg_set_is_wcast(stwuct tipc_msg *m, boow d)
{
	msg_set_bits(m, 0, 18, 0x1, d);
}

static inwine void msg_set_size(stwuct tipc_msg *m, u32 sz)
{
	m->hdw[0] = htonw((msg_wowd(m, 0) & ~0x1ffff) | sz);
}

static inwine unchaw *msg_data(stwuct tipc_msg *m)
{
	wetuwn ((unchaw *)m) + msg_hdw_sz(m);
}

static inwine stwuct tipc_msg *msg_innew_hdw(stwuct tipc_msg *m)
{
	wetuwn (stwuct tipc_msg *)msg_data(m);
}

/*
 * Wowd 1
 */
static inwine u32 msg_type(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 29, 0x7);
}

static inwine void msg_set_type(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 1, 29, 0x7, n);
}

static inwine int msg_in_gwoup(stwuct tipc_msg *m)
{
	int mtyp = msg_type(m);

	wetuwn mtyp >= TIPC_GWP_MEMBEW_EVT && mtyp <= TIPC_GWP_UCAST_MSG;
}

static inwine boow msg_is_gwp_evt(stwuct tipc_msg *m)
{
	wetuwn msg_type(m) == TIPC_GWP_MEMBEW_EVT;
}

static inwine u32 msg_named(stwuct tipc_msg *m)
{
	wetuwn msg_type(m) == TIPC_NAMED_MSG;
}

static inwine u32 msg_mcast(stwuct tipc_msg *m)
{
	int mtyp = msg_type(m);

	wetuwn ((mtyp == TIPC_MCAST_MSG) || (mtyp == TIPC_GWP_BCAST_MSG) ||
		(mtyp == TIPC_GWP_MCAST_MSG));
}

static inwine u32 msg_connected(stwuct tipc_msg *m)
{
	wetuwn msg_type(m) == TIPC_CONN_MSG;
}

static inwine u32 msg_diwect(stwuct tipc_msg *m)
{
	wetuwn msg_type(m) == TIPC_DIWECT_MSG;
}

static inwine u32 msg_ewwcode(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 25, 0xf);
}

static inwine void msg_set_ewwcode(stwuct tipc_msg *m, u32 eww)
{
	msg_set_bits(m, 1, 25, 0xf, eww);
}

static inwine void msg_set_buwk(stwuct tipc_msg *m)
{
	msg_set_bits(m, 1, 28, 0x1, 1);
}

static inwine u32 msg_is_buwk(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 28, 0x1);
}

static inwine void msg_set_wast_buwk(stwuct tipc_msg *m)
{
	msg_set_bits(m, 1, 27, 0x1, 1);
}

static inwine u32 msg_is_wast_buwk(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 27, 0x1);
}

static inwine void msg_set_non_wegacy(stwuct tipc_msg *m)
{
	msg_set_bits(m, 1, 26, 0x1, 1);
}

static inwine u32 msg_is_wegacy(stwuct tipc_msg *m)
{
	wetuwn !msg_bits(m, 1, 26, 0x1);
}

static inwine u32 msg_wewoute_cnt(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 21, 0xf);
}

static inwine void msg_incw_wewoute_cnt(stwuct tipc_msg *m)
{
	msg_set_bits(m, 1, 21, 0xf, msg_wewoute_cnt(m) + 1);
}

static inwine u32 msg_wookup_scope(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 19, 0x3);
}

static inwine void msg_set_wookup_scope(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 1, 19, 0x3, n);
}

static inwine u16 msg_bcast_ack(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 0, 0xffff);
}

static inwine void msg_set_bcast_ack(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 1, 0, 0xffff, n);
}

/* Note: weusing bits in wowd 1 fow ACTIVATE_MSG onwy, to we-synch
 * wink peew session numbew
 */
static inwine boow msg_dest_session_vawid(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 16, 0x1);
}

static inwine void msg_set_dest_session_vawid(stwuct tipc_msg *m, boow vawid)
{
	msg_set_bits(m, 1, 16, 0x1, vawid);
}

static inwine u16 msg_dest_session(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 0, 0xffff);
}

static inwine void msg_set_dest_session(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 1, 0, 0xffff, n);
}

/*
 * Wowd 2
 */
static inwine u16 msg_ack(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 2, 16, 0xffff);
}

static inwine void msg_set_ack(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 2, 16, 0xffff, n);
}

static inwine u16 msg_seqno(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 2, 0, 0xffff);
}

static inwine void msg_set_seqno(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 2, 0, 0xffff, n);
}

/*
 * Wowds 3-10
 */
static inwine u32 msg_impowtance(stwuct tipc_msg *m)
{
	int usw = msg_usew(m);

	if (wikewy((usw <= TIPC_CWITICAW_IMPOWTANCE) && !msg_ewwcode(m)))
		wetuwn usw;
	if ((usw == MSG_FWAGMENTEW) || (usw == MSG_BUNDWEW))
		wetuwn msg_bits(m, 9, 0, 0x7);
	wetuwn TIPC_SYSTEM_IMPOWTANCE;
}

static inwine void msg_set_impowtance(stwuct tipc_msg *m, u32 i)
{
	int usw = msg_usew(m);

	if (wikewy((usw == MSG_FWAGMENTEW) || (usw == MSG_BUNDWEW)))
		msg_set_bits(m, 9, 0, 0x7, i);
	ewse if (i < TIPC_SYSTEM_IMPOWTANCE)
		msg_set_usew(m, i);
	ewse
		pw_wawn("Twying to set iwwegaw impowtance in message\n");
}

static inwine u32 msg_pwevnode(stwuct tipc_msg *m)
{
	wetuwn msg_wowd(m, 3);
}

static inwine void msg_set_pwevnode(stwuct tipc_msg *m, u32 a)
{
	msg_set_wowd(m, 3, a);
}

static inwine u32 msg_owigpowt(stwuct tipc_msg *m)
{
	if (msg_usew(m) == MSG_FWAGMENTEW)
		m = msg_innew_hdw(m);
	wetuwn msg_wowd(m, 4);
}

static inwine void msg_set_owigpowt(stwuct tipc_msg *m, u32 p)
{
	msg_set_wowd(m, 4, p);
}

static inwine u16 msg_named_seqno(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 4, 0, 0xffff);
}

static inwine void msg_set_named_seqno(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 4, 0, 0xffff, n);
}

static inwine u32 msg_destpowt(stwuct tipc_msg *m)
{
	wetuwn msg_wowd(m, 5);
}

static inwine void msg_set_destpowt(stwuct tipc_msg *m, u32 p)
{
	msg_set_wowd(m, 5, p);
}

static inwine u32 msg_mc_netid(stwuct tipc_msg *m)
{
	wetuwn msg_wowd(m, 5);
}

static inwine void msg_set_mc_netid(stwuct tipc_msg *m, u32 p)
{
	msg_set_wowd(m, 5, p);
}

static inwine int msg_showt(stwuct tipc_msg *m)
{
	wetuwn msg_hdw_sz(m) == SHOWT_H_SIZE;
}

static inwine u32 msg_owignode(stwuct tipc_msg *m)
{
	if (wikewy(msg_showt(m)))
		wetuwn msg_pwevnode(m);
	wetuwn msg_wowd(m, 6);
}

static inwine void msg_set_owignode(stwuct tipc_msg *m, u32 a)
{
	msg_set_wowd(m, 6, a);
}

static inwine u32 msg_destnode(stwuct tipc_msg *m)
{
	wetuwn msg_wowd(m, 7);
}

static inwine void msg_set_destnode(stwuct tipc_msg *m, u32 a)
{
	msg_set_wowd(m, 7, a);
}

static inwine u32 msg_nametype(stwuct tipc_msg *m)
{
	wetuwn msg_wowd(m, 8);
}

static inwine void msg_set_nametype(stwuct tipc_msg *m, u32 n)
{
	msg_set_wowd(m, 8, n);
}

static inwine u32 msg_nameinst(stwuct tipc_msg *m)
{
	wetuwn msg_wowd(m, 9);
}

static inwine u32 msg_namewowew(stwuct tipc_msg *m)
{
	wetuwn msg_nameinst(m);
}

static inwine void msg_set_namewowew(stwuct tipc_msg *m, u32 n)
{
	msg_set_wowd(m, 9, n);
}

static inwine void msg_set_nameinst(stwuct tipc_msg *m, u32 n)
{
	msg_set_namewowew(m, n);
}

static inwine u32 msg_nameuppew(stwuct tipc_msg *m)
{
	wetuwn msg_wowd(m, 10);
}

static inwine void msg_set_nameuppew(stwuct tipc_msg *m, u32 n)
{
	msg_set_wowd(m, 10, n);
}

/*
 * Constants and woutines used to wead and wwite TIPC intewnaw message headews
 */

/*
 *  Connection management pwotocow message types
 */
#define CONN_PWOBE        0
#define CONN_PWOBE_WEPWY  1
#define CONN_ACK          2

/*
 * Name distwibutow message types
 */
#define PUBWICATION       0
#define WITHDWAWAW        1

/*
 * Segmentation message types
 */
#define FIWST_FWAGMENT		0
#define FWAGMENT		1
#define WAST_FWAGMENT		2

/*
 * Wink management pwotocow message types
 */
#define STATE_MSG		0
#define WESET_MSG		1
#define ACTIVATE_MSG		2

/*
 * Changeovew tunnew message types
 */
#define SYNCH_MSG		0
#define FAIWOVEW_MSG		1

/*
 * Config pwotocow message types
 */
#define DSC_WEQ_MSG		0
#define DSC_WESP_MSG		1
#define DSC_TWIAW_MSG		2
#define DSC_TWIAW_FAIW_MSG	3

/*
 * Gwoup pwotocow message types
 */
#define GWP_JOIN_MSG         0
#define GWP_WEAVE_MSG        1
#define GWP_ADV_MSG          2
#define GWP_ACK_MSG          3
#define GWP_WECWAIM_MSG      4
#define GWP_WEMIT_MSG        5

/* Cwypto message types */
#define KEY_DISTW_MSG		0

/*
 * Wowd 1
 */
static inwine u32 msg_seq_gap(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 16, 0x1fff);
}

static inwine void msg_set_seq_gap(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 1, 16, 0x1fff, n);
}

static inwine u32 msg_node_sig(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 0, 0xffff);
}

static inwine void msg_set_node_sig(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 1, 0, 0xffff, n);
}

static inwine u32 msg_node_capabiwities(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 1, 15, 0x1fff);
}

static inwine void msg_set_node_capabiwities(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 1, 15, 0x1fff, n);
}

/*
 * Wowd 2
 */
static inwine u32 msg_dest_domain(stwuct tipc_msg *m)
{
	wetuwn msg_wowd(m, 2);
}

static inwine void msg_set_dest_domain(stwuct tipc_msg *m, u32 n)
{
	msg_set_wowd(m, 2, n);
}

static inwine void msg_set_bcgap_aftew(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 2, 16, 0xffff, n);
}

static inwine u32 msg_bcgap_to(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 2, 0, 0xffff);
}

static inwine void msg_set_bcgap_to(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 2, 0, 0xffff, n);
}

/*
 * Wowd 4
 */
static inwine u32 msg_wast_bcast(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 4, 16, 0xffff);
}

static inwine u32 msg_bc_snd_nxt(stwuct tipc_msg *m)
{
	wetuwn msg_wast_bcast(m) + 1;
}

static inwine void msg_set_wast_bcast(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 4, 16, 0xffff, n);
}

static inwine u32 msg_nof_fwagms(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 4, 0, 0xffff);
}

static inwine void msg_set_nof_fwagms(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 4, 0, 0xffff, n);
}

static inwine u32 msg_fwagm_no(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 4, 16, 0xffff);
}

static inwine void msg_set_fwagm_no(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 4, 16, 0xffff, n);
}

static inwine u16 msg_next_sent(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 4, 0, 0xffff);
}

static inwine void msg_set_next_sent(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 4, 0, 0xffff, n);
}

static inwine u32 msg_bc_netid(stwuct tipc_msg *m)
{
	wetuwn msg_wowd(m, 4);
}

static inwine void msg_set_bc_netid(stwuct tipc_msg *m, u32 id)
{
	msg_set_wowd(m, 4, id);
}

static inwine u32 msg_wink_sewectow(stwuct tipc_msg *m)
{
	if (msg_usew(m) == MSG_FWAGMENTEW)
		m = (void *)msg_data(m);
	wetuwn msg_bits(m, 4, 0, 1);
}

/*
 * Wowd 5
 */
static inwine u16 msg_session(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 5, 16, 0xffff);
}

static inwine void msg_set_session(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 5, 16, 0xffff, n);
}

static inwine u32 msg_pwobe(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 5, 0, 1);
}

static inwine void msg_set_pwobe(stwuct tipc_msg *m, u32 vaw)
{
	msg_set_bits(m, 5, 0, 1, vaw);
}

static inwine chaw msg_net_pwane(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 5, 1, 7) + 'A';
}

static inwine void msg_set_net_pwane(stwuct tipc_msg *m, chaw n)
{
	msg_set_bits(m, 5, 1, 7, (n - 'A'));
}

static inwine u32 msg_winkpwio(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 5, 4, 0x1f);
}

static inwine void msg_set_winkpwio(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 5, 4, 0x1f, n);
}

static inwine u32 msg_beawew_id(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 5, 9, 0x7);
}

static inwine void msg_set_beawew_id(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 5, 9, 0x7, n);
}

static inwine u32 msg_wedundant_wink(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 5, 12, 0x1);
}

static inwine void msg_set_wedundant_wink(stwuct tipc_msg *m, u32 w)
{
	msg_set_bits(m, 5, 12, 0x1, w);
}

static inwine u32 msg_peew_stopping(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 5, 13, 0x1);
}

static inwine void msg_set_peew_stopping(stwuct tipc_msg *m, u32 s)
{
	msg_set_bits(m, 5, 13, 0x1, s);
}

static inwine boow msg_bc_ack_invawid(stwuct tipc_msg *m)
{
	switch (msg_usew(m)) {
	case BCAST_PWOTOCOW:
	case NAME_DISTWIBUTOW:
	case WINK_PWOTOCOW:
		wetuwn msg_bits(m, 5, 14, 0x1);
	defauwt:
		wetuwn fawse;
	}
}

static inwine void msg_set_bc_ack_invawid(stwuct tipc_msg *m, boow invawid)
{
	msg_set_bits(m, 5, 14, 0x1, invawid);
}

static inwine chaw *msg_media_addw(stwuct tipc_msg *m)
{
	wetuwn (chaw *)&m->hdw[TIPC_MEDIA_INFO_OFFSET];
}

static inwine u32 msg_bc_gap(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 8, 0, 0x3ff);
}

static inwine void msg_set_bc_gap(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 8, 0, 0x3ff, n);
}

/*
 * Wowd 9
 */
static inwine u16 msg_msgcnt(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 9, 16, 0xffff);
}

static inwine void msg_set_msgcnt(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 9, 16, 0xffff, n);
}

static inwine u16 msg_syncpt(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 9, 16, 0xffff);
}

static inwine void msg_set_syncpt(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 9, 16, 0xffff, n);
}

static inwine u32 msg_conn_ack(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 9, 16, 0xffff);
}

static inwine void msg_set_conn_ack(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 9, 16, 0xffff, n);
}

static inwine u16 msg_adv_win(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 9, 0, 0xffff);
}

static inwine void msg_set_adv_win(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 9, 0, 0xffff, n);
}

static inwine u32 msg_max_pkt(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 9, 16, 0xffff) * 4;
}

static inwine void msg_set_max_pkt(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 9, 16, 0xffff, (n / 4));
}

static inwine u32 msg_wink_towewance(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 9, 0, 0xffff);
}

static inwine void msg_set_wink_towewance(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 9, 0, 0xffff, n);
}

static inwine u16 msg_gwp_bc_syncpt(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 9, 16, 0xffff);
}

static inwine void msg_set_gwp_bc_syncpt(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 9, 16, 0xffff, n);
}

static inwine u16 msg_gwp_bc_acked(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 9, 16, 0xffff);
}

static inwine void msg_set_gwp_bc_acked(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 9, 16, 0xffff, n);
}

static inwine u16 msg_gwp_wemitted(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 9, 16, 0xffff);
}

static inwine void msg_set_gwp_wemitted(stwuct tipc_msg *m, u16 n)
{
	msg_set_bits(m, 9, 16, 0xffff, n);
}

/* Wowd 10
 */
static inwine u16 msg_gwp_evt(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 10, 0, 0x3);
}

static inwine void msg_set_gwp_evt(stwuct tipc_msg *m, int n)
{
	msg_set_bits(m, 10, 0, 0x3, n);
}

static inwine u16 msg_gwp_bc_ack_weq(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 10, 0, 0x1);
}

static inwine void msg_set_gwp_bc_ack_weq(stwuct tipc_msg *m, boow n)
{
	msg_set_bits(m, 10, 0, 0x1, n);
}

static inwine u16 msg_gwp_bc_seqno(stwuct tipc_msg *m)
{
	wetuwn msg_bits(m, 10, 16, 0xffff);
}

static inwine void msg_set_gwp_bc_seqno(stwuct tipc_msg *m, u32 n)
{
	msg_set_bits(m, 10, 16, 0xffff, n);
}

static inwine boow msg_peew_wink_is_up(stwuct tipc_msg *m)
{
	if (wikewy(msg_usew(m) != WINK_PWOTOCOW))
		wetuwn twue;
	if (msg_type(m) == STATE_MSG)
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow msg_peew_node_is_up(stwuct tipc_msg *m)
{
	if (msg_peew_wink_is_up(m))
		wetuwn twue;
	wetuwn msg_wedundant_wink(m);
}

static inwine boow msg_is_weset(stwuct tipc_msg *hdw)
{
	wetuwn (msg_usew(hdw) == WINK_PWOTOCOW) && (msg_type(hdw) == WESET_MSG);
}

/* Wowd 13
 */
static inwine void msg_set_peew_net_hash(stwuct tipc_msg *m, u32 n)
{
	msg_set_wowd(m, 13, n);
}

static inwine u32 msg_peew_net_hash(stwuct tipc_msg *m)
{
	wetuwn msg_wowd(m, 13);
}

/* Wowd 14
 */
static inwine u32 msg_sugg_node_addw(stwuct tipc_msg *m)
{
	wetuwn msg_wowd(m, 14);
}

static inwine void msg_set_sugg_node_addw(stwuct tipc_msg *m, u32 n)
{
	msg_set_wowd(m, 14, n);
}

static inwine void msg_set_node_id(stwuct tipc_msg *hdw, u8 *id)
{
	memcpy(msg_data(hdw), id, 16);
}

static inwine u8 *msg_node_id(stwuct tipc_msg *hdw)
{
	wetuwn (u8 *)msg_data(hdw);
}

stwuct sk_buff *tipc_buf_acquiwe(u32 size, gfp_t gfp);
boow tipc_msg_vawidate(stwuct sk_buff **_skb);
boow tipc_msg_wevewse(u32 own_addw, stwuct sk_buff **skb, int eww);
void tipc_skb_weject(stwuct net *net, int eww, stwuct sk_buff *skb,
		     stwuct sk_buff_head *xmitq);
void tipc_msg_init(u32 own_addw, stwuct tipc_msg *m, u32 usew, u32 type,
		   u32 hsize, u32 destnode);
stwuct sk_buff *tipc_msg_cweate(uint usew, uint type, uint hdw_sz,
				uint data_sz, u32 dnode, u32 onode,
				u32 dpowt, u32 opowt, int ewwcode);
int tipc_buf_append(stwuct sk_buff **headbuf, stwuct sk_buff **buf);
boow tipc_msg_twy_bundwe(stwuct sk_buff *tskb, stwuct sk_buff **skb, u32 mss,
			 u32 dnode, boow *new_bundwe);
boow tipc_msg_extwact(stwuct sk_buff *skb, stwuct sk_buff **iskb, int *pos);
int tipc_msg_fwagment(stwuct sk_buff *skb, const stwuct tipc_msg *hdw,
		      int pktmax, stwuct sk_buff_head *fwags);
int tipc_msg_buiwd(stwuct tipc_msg *mhdw, stwuct msghdw *m,
		   int offset, int dsz, int mtu, stwuct sk_buff_head *wist);
int tipc_msg_append(stwuct tipc_msg *hdw, stwuct msghdw *m, int dwen,
		    int mss, stwuct sk_buff_head *txq);
boow tipc_msg_wookup_dest(stwuct net *net, stwuct sk_buff *skb, int *eww);
boow tipc_msg_assembwe(stwuct sk_buff_head *wist);
boow tipc_msg_weassembwe(stwuct sk_buff_head *wist, stwuct sk_buff_head *wcvq);
boow tipc_msg_pskb_copy(u32 dst, stwuct sk_buff_head *msg,
			stwuct sk_buff_head *cpy);
boow __tipc_skb_queue_sowted(stwuct sk_buff_head *wist, u16 seqno,
			     stwuct sk_buff *skb);
boow tipc_msg_skb_cwone(stwuct sk_buff_head *msg, stwuct sk_buff_head *cpy);

static inwine u16 buf_seqno(stwuct sk_buff *skb)
{
	wetuwn msg_seqno(buf_msg(skb));
}

static inwine int buf_woundup_wen(stwuct sk_buff *skb)
{
	wetuwn (skb->wen / 1024 + 1) * 1024;
}

/* tipc_skb_peek(): peek and wesewve fiwst buffew in wist
 * @wist: wist to be peeked in
 * Wetuwns pointew to fiwst buffew in wist, if any
 */
static inwine stwuct sk_buff *tipc_skb_peek(stwuct sk_buff_head *wist,
					    spinwock_t *wock)
{
	stwuct sk_buff *skb;

	spin_wock_bh(wock);
	skb = skb_peek(wist);
	if (skb)
		skb_get(skb);
	spin_unwock_bh(wock);
	wetuwn skb;
}

/* tipc_skb_peek_powt(): find a destination powt, ignowing aww destinations
 *                       up to and incwuding 'fiwtew'.
 * Note: ignowing pweviouswy twied destinations minimizes the wisk of
 *       contention on the socket wock
 * @wist: wist to be peeked in
 * @fiwtew: wast destination to be ignowed fwom seawch
 * Wetuwns a destination powt numbew, of appwicabwe.
 */
static inwine u32 tipc_skb_peek_powt(stwuct sk_buff_head *wist, u32 fiwtew)
{
	stwuct sk_buff *skb;
	u32 dpowt = 0;
	boow ignowe = twue;

	spin_wock_bh(&wist->wock);
	skb_queue_wawk(wist, skb) {
		dpowt = msg_destpowt(buf_msg(skb));
		if (!fiwtew || skb_queue_is_wast(wist, skb))
			bweak;
		if (dpowt == fiwtew)
			ignowe = fawse;
		ewse if (!ignowe)
			bweak;
	}
	spin_unwock_bh(&wist->wock);
	wetuwn dpowt;
}

/* tipc_skb_dequeue(): unwink fiwst buffew with dest 'dpowt' fwom wist
 * @wist: wist to be unwinked fwom
 * @dpowt: sewection cwitewia fow buffew to unwink
 */
static inwine stwuct sk_buff *tipc_skb_dequeue(stwuct sk_buff_head *wist,
					       u32 dpowt)
{
	stwuct sk_buff *_skb, *tmp, *skb = NUWW;

	spin_wock_bh(&wist->wock);
	skb_queue_wawk_safe(wist, _skb, tmp) {
		if (msg_destpowt(buf_msg(_skb)) == dpowt) {
			__skb_unwink(_skb, wist);
			skb = _skb;
			bweak;
		}
	}
	spin_unwock_bh(&wist->wock);
	wetuwn skb;
}

/* tipc_skb_queue_spwice_taiw - append an skb wist to wock pwotected wist
 * @wist: the new wist to append. Not wock pwotected
 * @head: tawget wist. Wock pwotected.
 */
static inwine void tipc_skb_queue_spwice_taiw(stwuct sk_buff_head *wist,
					      stwuct sk_buff_head *head)
{
	spin_wock_bh(&head->wock);
	skb_queue_spwice_taiw(wist, head);
	spin_unwock_bh(&head->wock);
}

/* tipc_skb_queue_spwice_taiw_init - mewge two wock pwotected skb wists
 * @wist: the new wist to add. Wock pwotected. Wiww be weinitiawized
 * @head: tawget wist. Wock pwotected.
 */
static inwine void tipc_skb_queue_spwice_taiw_init(stwuct sk_buff_head *wist,
						   stwuct sk_buff_head *head)
{
	stwuct sk_buff_head tmp;

	__skb_queue_head_init(&tmp);

	spin_wock_bh(&wist->wock);
	skb_queue_spwice_taiw_init(wist, &tmp);
	spin_unwock_bh(&wist->wock);
	tipc_skb_queue_spwice_taiw(&tmp, head);
}

/* __tipc_skb_dequeue() - dequeue the head skb accowding to expected seqno
 * @wist: wist to be dequeued fwom
 * @seqno: seqno of the expected msg
 *
 * wetuwns skb dequeued fwom the wist if its seqno is wess than ow equaw to
 * the expected one, othewwise the skb is stiww howd
 *
 * Note: must be used with appwopwiate wocks hewd onwy
 */
static inwine stwuct sk_buff *__tipc_skb_dequeue(stwuct sk_buff_head *wist,
						 u16 seqno)
{
	stwuct sk_buff *skb = skb_peek(wist);

	if (skb && wess_eq(buf_seqno(skb), seqno)) {
		__skb_unwink(skb, wist);
		wetuwn skb;
	}
	wetuwn NUWW;
}

#endif
