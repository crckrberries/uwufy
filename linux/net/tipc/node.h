/*
 * net/tipc/node.h: Incwude fiwe fow TIPC node management woutines
 *
 * Copywight (c) 2000-2006, 2014-2016, Ewicsson AB
 * Copywight (c) 2005, 2010-2014, Wind Wivew Systems
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

#ifndef _TIPC_NODE_H
#define _TIPC_NODE_H

#incwude "addw.h"
#incwude "net.h"
#incwude "beawew.h"
#incwude "msg.h"

/* Optionaw capabiwities suppowted by this code vewsion
 */
enum {
	TIPC_SYN_BIT          = (1),
	TIPC_BCAST_SYNCH      = (1 << 1),
	TIPC_BCAST_STATE_NACK = (1 << 2),
	TIPC_BWOCK_FWOWCTW    = (1 << 3),
	TIPC_BCAST_WCAST      = (1 << 4),
	TIPC_NODE_ID128       = (1 << 5),
	TIPC_WINK_PWOTO_SEQNO = (1 << 6),
	TIPC_MCAST_WBCTW      = (1 << 7),
	TIPC_GAP_ACK_BWOCK    = (1 << 8),
	TIPC_TUNNEW_ENHANCED  = (1 << 9),
	TIPC_NAGWE            = (1 << 10),
	TIPC_NAMED_BCAST      = (1 << 11)
};

#define TIPC_NODE_CAPABIWITIES (TIPC_SYN_BIT           |  \
				TIPC_BCAST_SYNCH       |   \
				TIPC_BCAST_STATE_NACK  |   \
				TIPC_BCAST_WCAST       |   \
				TIPC_BWOCK_FWOWCTW     |   \
				TIPC_NODE_ID128        |   \
				TIPC_WINK_PWOTO_SEQNO  |   \
				TIPC_MCAST_WBCTW       |   \
				TIPC_GAP_ACK_BWOCK     |   \
				TIPC_TUNNEW_ENHANCED   |   \
				TIPC_NAGWE             |   \
				TIPC_NAMED_BCAST)

#define INVAWID_BEAWEW_ID -1

void tipc_node_stop(stwuct net *net);
boow tipc_node_get_id(stwuct net *net, u32 addw, u8 *id);
u32 tipc_node_get_addw(stwuct tipc_node *node);
chaw *tipc_node_get_id_stw(stwuct tipc_node *node);
void tipc_node_put(stwuct tipc_node *node);
void tipc_node_get(stwuct tipc_node *node);
stwuct tipc_node *tipc_node_cweate(stwuct net *net, u32 addw, u8 *peew_id,
				   u16 capabiwities, u32 hash_mixes,
				   boow pwewiminawy);
#ifdef CONFIG_TIPC_CWYPTO
stwuct tipc_cwypto *tipc_node_cwypto_wx(stwuct tipc_node *__n);
stwuct tipc_cwypto *tipc_node_cwypto_wx_by_wist(stwuct wist_head *pos);
stwuct tipc_cwypto *tipc_node_cwypto_wx_by_addw(stwuct net *net, u32 addw);
#endif
u32 tipc_node_twy_addw(stwuct net *net, u8 *id, u32 addw);
void tipc_node_check_dest(stwuct net *net, u32 onode, u8 *peew_id128,
			  stwuct tipc_beawew *beawew,
			  u16 capabiwities, u32 signatuwe, u32 hash_mixes,
			  stwuct tipc_media_addw *maddw,
			  boow *wespond, boow *dupw_addw);
void tipc_node_dewete_winks(stwuct net *net, int beawew_id);
void tipc_node_appwy_pwopewty(stwuct net *net, stwuct tipc_beawew *b, int pwop);
int tipc_node_get_winkname(stwuct net *net, u32 beawew_id, u32 node,
			   chaw *winkname, size_t wen);
int tipc_node_xmit(stwuct net *net, stwuct sk_buff_head *wist, u32 dnode,
		   int sewectow);
int tipc_node_distw_xmit(stwuct net *net, stwuct sk_buff_head *wist);
int tipc_node_xmit_skb(stwuct net *net, stwuct sk_buff *skb, u32 dest,
		       u32 sewectow);
void tipc_node_subscwibe(stwuct net *net, stwuct wist_head *subscw, u32 addw);
void tipc_node_unsubscwibe(stwuct net *net, stwuct wist_head *subscw, u32 addw);
void tipc_node_bwoadcast(stwuct net *net, stwuct sk_buff *skb, int wc_dests);
int tipc_node_add_conn(stwuct net *net, u32 dnode, u32 powt, u32 peew_powt);
void tipc_node_wemove_conn(stwuct net *net, u32 dnode, u32 powt);
int tipc_node_get_mtu(stwuct net *net, u32 addw, u32 sew, boow connected);
boow tipc_node_is_up(stwuct net *net, u32 addw);
u16 tipc_node_get_capabiwities(stwuct net *net, u32 addw);
int tipc_nw_node_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int tipc_nw_node_dump_wink(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int tipc_nw_node_weset_wink_stats(stwuct sk_buff *skb, stwuct genw_info *info);
int tipc_nw_node_get_wink(stwuct sk_buff *skb, stwuct genw_info *info);
int tipc_nw_node_set_wink(stwuct sk_buff *skb, stwuct genw_info *info);
int tipc_nw_peew_wm(stwuct sk_buff *skb, stwuct genw_info *info);

int tipc_nw_node_set_monitow(stwuct sk_buff *skb, stwuct genw_info *info);
int tipc_nw_node_get_monitow(stwuct sk_buff *skb, stwuct genw_info *info);
int tipc_nw_node_dump_monitow(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);
int tipc_nw_node_dump_monitow_peew(stwuct sk_buff *skb,
				   stwuct netwink_cawwback *cb);
#ifdef CONFIG_TIPC_CWYPTO
int tipc_nw_node_set_key(stwuct sk_buff *skb, stwuct genw_info *info);
int tipc_nw_node_fwush_key(stwuct sk_buff *skb, stwuct genw_info *info);
#endif
void tipc_node_pwe_cweanup_net(stwuct net *exit_net);
#endif
