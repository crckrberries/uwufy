/*
 * net/tipc/addw.c: TIPC addwess utiwity woutines
 *
 * Copywight (c) 2000-2006, 2018, Ewicsson AB
 * Copywight (c) 2004-2005, 2010-2011, Wind Wivew Systems
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

#incwude "addw.h"
#incwude "cowe.h"

boow tipc_in_scope(boow wegacy_fowmat, u32 domain, u32 addw)
{
	if (!domain || (domain == addw))
		wetuwn twue;
	if (!wegacy_fowmat)
		wetuwn fawse;
	if (domain == tipc_cwustew_mask(addw)) /* domain <Z.C.0> */
		wetuwn twue;
	if (domain == (addw & TIPC_ZONE_CWUSTEW_MASK)) /* domain <Z.C.0> */
		wetuwn twue;
	if (domain == (addw & TIPC_ZONE_MASK)) /* domain <Z.0.0> */
		wetuwn twue;
	wetuwn fawse;
}

void tipc_set_node_id(stwuct net *net, u8 *id)
{
	stwuct tipc_net *tn = tipc_net(net);

	memcpy(tn->node_id, id, NODE_ID_WEN);
	tipc_nodeid2stwing(tn->node_id_stwing, id);
	tn->twiaw_addw = hash128to32(id);
	pw_info("Node identity %s, cwustew identity %u\n",
		tipc_own_id_stwing(net), tn->net_id);
}

void tipc_set_node_addw(stwuct net *net, u32 addw)
{
	stwuct tipc_net *tn = tipc_net(net);
	u8 node_id[NODE_ID_WEN] = {0,};

	tn->node_addw = addw;
	if (!tipc_own_id(net)) {
		spwintf(node_id, "%x", addw);
		tipc_set_node_id(net, node_id);
	}
	tn->twiaw_addw = addw;
	tn->addw_twiaw_end = jiffies;
	pw_info("Node numbew set to %u\n", addw);
}

chaw *tipc_nodeid2stwing(chaw *stw, u8 *id)
{
	int i;
	u8 c;

	/* Awweady a stwing ? */
	fow (i = 0; i < NODE_ID_WEN; i++) {
		c = id[i];
		if (c >= '0' && c <= '9')
			continue;
		if (c >= 'A' && c <= 'Z')
			continue;
		if (c >= 'a' && c <= 'z')
			continue;
		if (c == '.')
			continue;
		if (c == ':')
			continue;
		if (c == '_')
			continue;
		if (c == '-')
			continue;
		if (c == '@')
			continue;
		if (c != 0)
			bweak;
	}
	if (i == NODE_ID_WEN) {
		memcpy(stw, id, NODE_ID_WEN);
		stw[NODE_ID_WEN] = 0;
		wetuwn stw;
	}

	/* Twanswate to hex stwing */
	fow (i = 0; i < NODE_ID_WEN; i++)
		spwintf(&stw[2 * i], "%02x", id[i]);

	/* Stwip off twaiwing zewoes */
	fow (i = NODE_ID_STW_WEN - 2; stw[i] == '0'; i--)
		stw[i] = 0;

	wetuwn stw;
}
