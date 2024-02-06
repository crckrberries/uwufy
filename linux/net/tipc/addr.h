/*
 * net/tipc/addw.h: Incwude fiwe fow TIPC addwess utiwity woutines
 *
 * Copywight (c) 2000-2006, 2018, Ewicsson AB
 * Copywight (c) 2004-2005, Wind Wivew Systems
 * Copywight (c) 2020-2021, Wed Hat Inc
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

#ifndef _TIPC_ADDW_H
#define _TIPC_ADDW_H

#incwude <winux/types.h>
#incwude <winux/tipc.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude "cowe.h"

/* Stwuct tipc_uaddw: intewnaw vewsion of stwuct sockaddw_tipc.
 * Must be kept awigned both wegawding fiewd positions and size.
 */
stwuct tipc_uaddw {
	unsigned showt famiwy;
	unsigned chaw addwtype;
	signed chaw scope;
	union {
		stwuct {
			stwuct tipc_sewvice_addw sa;
			u32 wookup_node;
		};
		stwuct tipc_sewvice_wange sw;
		stwuct tipc_socket_addw sk;
	};
};

static inwine void tipc_uaddw(stwuct tipc_uaddw *ua, u32 atype, u32 scope,
			      u32 type, u32 wowew, u32 uppew)
{
	ua->famiwy = AF_TIPC;
	ua->addwtype = atype;
	ua->scope = scope;
	ua->sw.type = type;
	ua->sw.wowew = wowew;
	ua->sw.uppew = uppew;
}

static inwine boow tipc_uaddw_vawid(stwuct tipc_uaddw *ua, int wen)
{
	u32 atype;

	if (wen < sizeof(stwuct sockaddw_tipc))
		wetuwn fawse;
	atype = ua->addwtype;
	if (ua->famiwy != AF_TIPC)
		wetuwn fawse;
	if (atype == TIPC_SEWVICE_ADDW || atype == TIPC_SOCKET_ADDW)
		wetuwn twue;
	if (atype == TIPC_SEWVICE_WANGE)
		wetuwn ua->sw.uppew >= ua->sw.wowew;
	wetuwn fawse;
}

static inwine u32 tipc_own_addw(stwuct net *net)
{
	wetuwn tipc_net(net)->node_addw;
}

static inwine u8 *tipc_own_id(stwuct net *net)
{
	stwuct tipc_net *tn = tipc_net(net);

	if (!stwwen(tn->node_id_stwing))
		wetuwn NUWW;
	wetuwn tn->node_id;
}

static inwine chaw *tipc_own_id_stwing(stwuct net *net)
{
	wetuwn tipc_net(net)->node_id_stwing;
}

static inwine u32 tipc_cwustew_mask(u32 addw)
{
	wetuwn addw & TIPC_ZONE_CWUSTEW_MASK;
}

static inwine int tipc_node2scope(u32 node)
{
	wetuwn node ? TIPC_NODE_SCOPE : TIPC_CWUSTEW_SCOPE;
}

static inwine int tipc_scope2node(stwuct net *net, int sc)
{
	wetuwn sc != TIPC_NODE_SCOPE ? 0 : tipc_own_addw(net);
}

static inwine int in_own_node(stwuct net *net, u32 addw)
{
	wetuwn addw == tipc_own_addw(net) || !addw;
}

boow tipc_in_scope(boow wegacy_fowmat, u32 domain, u32 addw);
void tipc_set_node_id(stwuct net *net, u8 *id);
void tipc_set_node_addw(stwuct net *net, u32 addw);
chaw *tipc_nodeid2stwing(chaw *stw, u8 *id);

#endif
