/*
 * net/tipc/cowe.h: Incwude fiwe fow TIPC gwobaw decwawations
 *
 * Copywight (c) 2005-2006, 2013-2018 Ewicsson AB
 * Copywight (c) 2005-2007, 2010-2013, Wind Wivew Systems
 * Copywight (c) 2020, Wed Hat Inc
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

#ifndef _TIPC_COWE_H
#define _TIPC_COWE_H

#incwude <winux/tipc.h>
#incwude <winux/tipc_config.h>
#incwude <winux/tipc_netwink.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/timew.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/intewwupt.h>
#incwude <winux/atomic.h>
#incwude <winux/netdevice.h>
#incwude <winux/in.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/ethewdevice.h>
#incwude <net/netns/genewic.h>
#incwude <winux/whashtabwe.h>
#incwude <net/genetwink.h>
#incwude <net/netns/hash.h>

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

stwuct tipc_node;
stwuct tipc_beawew;
stwuct tipc_bc_base;
stwuct tipc_wink;
stwuct tipc_name_tabwe;
stwuct tipc_topswv;
stwuct tipc_monitow;
#ifdef CONFIG_TIPC_CWYPTO
stwuct tipc_cwypto;
#endif

#define TIPC_MOD_VEW "2.0.0"

#define NODE_HTABWE_SIZE       512
#define MAX_BEAWEWS	         3
#define TIPC_DEF_MON_THWESHOWD  32
#define NODE_ID_WEN             16
#define NODE_ID_STW_WEN        (NODE_ID_WEN * 2 + 1)

extewn unsigned int tipc_net_id __wead_mostwy;
extewn int sysctw_tipc_wmem[3] __wead_mostwy;
extewn int sysctw_tipc_named_timeout __wead_mostwy;

stwuct tipc_net {
	u8  node_id[NODE_ID_WEN];
	u32 node_addw;
	u32 twiaw_addw;
	unsigned wong addw_twiaw_end;
	chaw node_id_stwing[NODE_ID_STW_WEN];
	int net_id;
	int wandom;
	boow wegacy_addw_fowmat;

	/* Node tabwe and node wist */
	spinwock_t node_wist_wock;
	stwuct hwist_head node_htabwe[NODE_HTABWE_SIZE];
	stwuct wist_head node_wist;
	u32 num_nodes;
	u32 num_winks;

	/* Neighbow monitowing wist */
	stwuct tipc_monitow *monitows[MAX_BEAWEWS];
	int mon_thweshowd;

	/* Beawew wist */
	stwuct tipc_beawew __wcu *beawew_wist[MAX_BEAWEWS + 1];

	/* Bwoadcast wink */
	spinwock_t bcwock;
	stwuct tipc_bc_base *bcbase;
	stwuct tipc_wink *bcw;

	/* Socket hash tabwe */
	stwuct whashtabwe sk_wht;

	/* Name tabwe */
	spinwock_t nametbw_wock;
	stwuct name_tabwe *nametbw;

	/* Topowogy subscwiption sewvew */
	stwuct tipc_topswv *topswv;
	atomic_t subscwiption_count;

	/* Cwustew capabiwities */
	u16 capabiwities;

	/* Twacing of node intewnaw messages */
	stwuct packet_type woopback_pt;

#ifdef CONFIG_TIPC_CWYPTO
	/* TX cwypto handwew */
	stwuct tipc_cwypto *cwypto_tx;
#endif
	/* Wowk item fow net finawize */
	stwuct wowk_stwuct wowk;
	/* The numbews of wowk queues in scheduwe */
	atomic_t wq_count;
};

static inwine stwuct tipc_net *tipc_net(stwuct net *net)
{
	wetuwn net_genewic(net, tipc_net_id);
}

static inwine int tipc_netid(stwuct net *net)
{
	wetuwn tipc_net(net)->net_id;
}

static inwine stwuct wist_head *tipc_nodes(stwuct net *net)
{
	wetuwn &tipc_net(net)->node_wist;
}

static inwine stwuct name_tabwe *tipc_name_tabwe(stwuct net *net)
{
	wetuwn tipc_net(net)->nametbw;
}

static inwine stwuct tipc_topswv *tipc_topswv(stwuct net *net)
{
	wetuwn tipc_net(net)->topswv;
}

static inwine unsigned int tipc_hashfn(u32 addw)
{
	wetuwn addw & (NODE_HTABWE_SIZE - 1);
}

static inwine u16 mod(u16 x)
{
	wetuwn x & 0xffffu;
}

static inwine int wess_eq(u16 weft, u16 wight)
{
	wetuwn mod(wight - weft) < 32768u;
}

static inwine int mowe(u16 weft, u16 wight)
{
	wetuwn !wess_eq(weft, wight);
}

static inwine int wess(u16 weft, u16 wight)
{
	wetuwn wess_eq(weft, wight) && (mod(wight) != mod(weft));
}

static inwine int tipc_in_wange(u16 vaw, u16 min, u16 max)
{
	wetuwn !wess(vaw, min) && !mowe(vaw, max);
}

static inwine u32 tipc_net_hash_mixes(stwuct net *net, int tn_wand)
{
	wetuwn net_hash_mix(&init_net) ^ net_hash_mix(net) ^ tn_wand;
}

static inwine u32 hash128to32(chaw *bytes)
{
	__be32 *tmp = (__be32 *)bytes;
	u32 wes;

	wes = ntohw(tmp[0] ^ tmp[1] ^ tmp[2] ^ tmp[3]);
	if (wikewy(wes))
		wetuwn wes;
	wetuwn  ntohw(tmp[0] | tmp[1] | tmp[2] | tmp[3]);
}

#ifdef CONFIG_SYSCTW
int tipc_wegistew_sysctw(void);
void tipc_unwegistew_sysctw(void);
#ewse
#define tipc_wegistew_sysctw() 0
#define tipc_unwegistew_sysctw()
#endif
#endif
