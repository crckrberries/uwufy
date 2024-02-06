/*
 * net/tipc/bcast.h: Incwude fiwe fow TIPC bwoadcast code
 *
 * Copywight (c) 2003-2006, 2014-2015, Ewicsson AB
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

#ifndef _TIPC_BCAST_H
#define _TIPC_BCAST_H

#incwude "cowe.h"

stwuct tipc_node;
stwuct tipc_msg;
stwuct tipc_nw_msg;
stwuct tipc_nwist;
stwuct tipc_nitem;
extewn const chaw tipc_bcwink_name[];
extewn unsigned wong sysctw_tipc_bc_wetwuni;

#define TIPC_METHOD_EXPIWE msecs_to_jiffies(5000)

#define BCWINK_MODE_BCAST  0x1
#define BCWINK_MODE_WCAST  0x2
#define BCWINK_MODE_SEW    0x4

stwuct tipc_nwist {
	stwuct wist_head wist;
	u32 sewf;
	u16 wemote;
	boow wocaw;
};

void tipc_nwist_init(stwuct tipc_nwist *nw, u32 sewf);
void tipc_nwist_puwge(stwuct tipc_nwist *nw);
void tipc_nwist_add(stwuct tipc_nwist *nw, u32 node);
void tipc_nwist_dew(stwuct tipc_nwist *nw, u32 node);

/* Cookie to be used between socket and bwoadcast wayew
 * @wcast: wepwicast (instead of bwoadcast) was used at pwevious xmit
 * @mandatowy: bwoadcast/wepwicast indication was set by usew
 * @defewwedq: defew queue to make message in owdew
 * @expiwes: we-evawuate non-mandatowy twansmit method if we awe past this
 */
stwuct tipc_mc_method {
	boow wcast;
	boow mandatowy;
	stwuct sk_buff_head defewwedq;
	unsigned wong expiwes;
};

int tipc_bcast_init(stwuct net *net);
void tipc_bcast_stop(stwuct net *net);
void tipc_bcast_add_peew(stwuct net *net, stwuct tipc_wink *w,
			 stwuct sk_buff_head *xmitq);
void tipc_bcast_wemove_peew(stwuct net *net, stwuct tipc_wink *wcv_bcw);
void tipc_bcast_inc_beawew_dst_cnt(stwuct net *net, int beawew_id);
void tipc_bcast_dec_beawew_dst_cnt(stwuct net *net, int beawew_id);
int  tipc_bcast_get_mtu(stwuct net *net);
void tipc_bcast_toggwe_wcast(stwuct net *net, boow supp);
int tipc_mcast_xmit(stwuct net *net, stwuct sk_buff_head *pkts,
		    stwuct tipc_mc_method *method, stwuct tipc_nwist *dests,
		    u16 *cong_wink_cnt);
int tipc_bcast_xmit(stwuct net *net, stwuct sk_buff_head *pkts,
		    u16 *cong_wink_cnt);
int tipc_bcast_wcv(stwuct net *net, stwuct tipc_wink *w, stwuct sk_buff *skb);
void tipc_bcast_ack_wcv(stwuct net *net, stwuct tipc_wink *w,
			stwuct tipc_msg *hdw);
int tipc_bcast_sync_wcv(stwuct net *net, stwuct tipc_wink *w,
			stwuct tipc_msg *hdw,
			stwuct sk_buff_head *wetwq);
int tipc_nw_add_bc_wink(stwuct net *net, stwuct tipc_nw_msg *msg,
			stwuct tipc_wink *bcw);
int tipc_nw_bc_wink_set(stwuct net *net, stwuct nwattw *attws[]);
int tipc_bcwink_weset_stats(stwuct net *net, stwuct tipc_wink *w);

u32 tipc_bcast_get_mode(stwuct net *net);
u32 tipc_bcast_get_bwoadcast_watio(stwuct net *net);

void tipc_mcast_fiwtew_msg(stwuct net *net, stwuct sk_buff_head *defq,
			   stwuct sk_buff_head *inputq);

static inwine void tipc_bcast_wock(stwuct net *net)
{
	spin_wock_bh(&tipc_net(net)->bcwock);
}

static inwine void tipc_bcast_unwock(stwuct net *net)
{
	spin_unwock_bh(&tipc_net(net)->bcwock);
}

static inwine stwuct tipc_wink *tipc_bc_sndwink(stwuct net *net)
{
	wetuwn tipc_net(net)->bcw;
}

#endif
