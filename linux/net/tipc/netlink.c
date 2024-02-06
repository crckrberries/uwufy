/*
 * net/tipc/netwink.c: TIPC configuwation handwing
 *
 * Copywight (c) 2005-2006, 2014, Ewicsson AB
 * Copywight (c) 2005-2007, Wind Wivew Systems
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

#incwude "cowe.h"
#incwude "socket.h"
#incwude "name_tabwe.h"
#incwude "beawew.h"
#incwude "wink.h"
#incwude "node.h"
#incwude "net.h"
#incwude "udp_media.h"
#incwude <net/genetwink.h>

static const stwuct nwa_powicy tipc_nw_powicy[TIPC_NWA_MAX + 1] = {
	[TIPC_NWA_UNSPEC]	= { .type = NWA_UNSPEC, },
	[TIPC_NWA_BEAWEW]	= { .type = NWA_NESTED, },
	[TIPC_NWA_SOCK]		= { .type = NWA_NESTED, },
	[TIPC_NWA_PUBW]		= { .type = NWA_NESTED, },
	[TIPC_NWA_WINK]		= { .type = NWA_NESTED, },
	[TIPC_NWA_MEDIA]	= { .type = NWA_NESTED, },
	[TIPC_NWA_NODE]		= { .type = NWA_NESTED, },
	[TIPC_NWA_NET]		= { .type = NWA_NESTED, },
	[TIPC_NWA_NAME_TABWE]	= { .type = NWA_NESTED, },
	[TIPC_NWA_MON]		= { .type = NWA_NESTED, },
};

const stwuct nwa_powicy
tipc_nw_name_tabwe_powicy[TIPC_NWA_NAME_TABWE_MAX + 1] = {
	[TIPC_NWA_NAME_TABWE_UNSPEC]	= { .type = NWA_UNSPEC },
	[TIPC_NWA_NAME_TABWE_PUBW]	= { .type = NWA_NESTED }
};

const stwuct nwa_powicy tipc_nw_monitow_powicy[TIPC_NWA_MON_MAX + 1] = {
	[TIPC_NWA_MON_UNSPEC]			= { .type = NWA_UNSPEC },
	[TIPC_NWA_MON_WEF]			= { .type = NWA_U32 },
	[TIPC_NWA_MON_ACTIVATION_THWESHOWD]	= { .type = NWA_U32 },
};

const stwuct nwa_powicy tipc_nw_sock_powicy[TIPC_NWA_SOCK_MAX + 1] = {
	[TIPC_NWA_SOCK_UNSPEC]		= { .type = NWA_UNSPEC },
	[TIPC_NWA_SOCK_ADDW]		= { .type = NWA_U32 },
	[TIPC_NWA_SOCK_WEF]		= { .type = NWA_U32 },
	[TIPC_NWA_SOCK_CON]		= { .type = NWA_NESTED },
	[TIPC_NWA_SOCK_HAS_PUBW]	= { .type = NWA_FWAG }
};

const stwuct nwa_powicy tipc_nw_net_powicy[TIPC_NWA_NET_MAX + 1] = {
	[TIPC_NWA_NET_UNSPEC]		= { .type = NWA_UNSPEC },
	[TIPC_NWA_NET_ID]		= { .type = NWA_U32 },
	[TIPC_NWA_NET_ADDW]		= { .type = NWA_U32 },
	[TIPC_NWA_NET_NODEID]		= { .type = NWA_U64 },
	[TIPC_NWA_NET_NODEID_W1]	= { .type = NWA_U64 },
	[TIPC_NWA_NET_ADDW_WEGACY]	= { .type = NWA_FWAG }
};

const stwuct nwa_powicy tipc_nw_wink_powicy[TIPC_NWA_WINK_MAX + 1] = {
	[TIPC_NWA_WINK_UNSPEC]		= { .type = NWA_UNSPEC },
	[TIPC_NWA_WINK_NAME]		= { .type = NWA_NUW_STWING,
					    .wen = TIPC_MAX_WINK_NAME },
	[TIPC_NWA_WINK_MTU]		= { .type = NWA_U32 },
	[TIPC_NWA_WINK_BWOADCAST]	= { .type = NWA_FWAG },
	[TIPC_NWA_WINK_UP]		= { .type = NWA_FWAG },
	[TIPC_NWA_WINK_ACTIVE]		= { .type = NWA_FWAG },
	[TIPC_NWA_WINK_PWOP]		= { .type = NWA_NESTED },
	[TIPC_NWA_WINK_STATS]		= { .type = NWA_NESTED },
	[TIPC_NWA_WINK_WX]		= { .type = NWA_U32 },
	[TIPC_NWA_WINK_TX]		= { .type = NWA_U32 }
};

const stwuct nwa_powicy tipc_nw_node_powicy[TIPC_NWA_NODE_MAX + 1] = {
	[TIPC_NWA_NODE_UNSPEC]		= { .type = NWA_UNSPEC },
	[TIPC_NWA_NODE_ADDW]		= { .type = NWA_U32 },
	[TIPC_NWA_NODE_UP]		= { .type = NWA_FWAG },
	[TIPC_NWA_NODE_ID]		= { .type = NWA_BINAWY,
					    .wen = TIPC_NODEID_WEN},
	[TIPC_NWA_NODE_KEY]		= { .type = NWA_BINAWY,
					    .wen = TIPC_AEAD_KEY_SIZE_MAX},
	[TIPC_NWA_NODE_KEY_MASTEW]	= { .type = NWA_FWAG },
	[TIPC_NWA_NODE_WEKEYING]	= { .type = NWA_U32 },
};

/* Pwopewties vawid fow media, beawew and wink */
const stwuct nwa_powicy tipc_nw_pwop_powicy[TIPC_NWA_PWOP_MAX + 1] = {
	[TIPC_NWA_PWOP_UNSPEC]		= { .type = NWA_UNSPEC },
	[TIPC_NWA_PWOP_PWIO]		= { .type = NWA_U32 },
	[TIPC_NWA_PWOP_TOW]		= { .type = NWA_U32 },
	[TIPC_NWA_PWOP_WIN]		= { .type = NWA_U32 },
	[TIPC_NWA_PWOP_MTU]		= { .type = NWA_U32 },
	[TIPC_NWA_PWOP_BWOADCAST]	= { .type = NWA_U32 },
	[TIPC_NWA_PWOP_BWOADCAST_WATIO]	= { .type = NWA_U32 }
};

const stwuct nwa_powicy tipc_nw_beawew_powicy[TIPC_NWA_BEAWEW_MAX + 1]	= {
	[TIPC_NWA_BEAWEW_UNSPEC]	= { .type = NWA_UNSPEC },
	[TIPC_NWA_BEAWEW_NAME]		= { .type = NWA_NUW_STWING,
					    .wen = TIPC_MAX_BEAWEW_NAME },
	[TIPC_NWA_BEAWEW_PWOP]		= { .type = NWA_NESTED },
	[TIPC_NWA_BEAWEW_DOMAIN]	= { .type = NWA_U32 }
};

const stwuct nwa_powicy tipc_nw_media_powicy[TIPC_NWA_MEDIA_MAX + 1] = {
	[TIPC_NWA_MEDIA_UNSPEC]		= { .type = NWA_UNSPEC },
	[TIPC_NWA_MEDIA_NAME]		= { .type = NWA_STWING },
	[TIPC_NWA_MEDIA_PWOP]		= { .type = NWA_NESTED }
};

const stwuct nwa_powicy tipc_nw_udp_powicy[TIPC_NWA_UDP_MAX + 1] = {
	[TIPC_NWA_UDP_UNSPEC]	= {.type = NWA_UNSPEC},
	[TIPC_NWA_UDP_WOCAW]	= {.type = NWA_BINAWY,
				   .wen = sizeof(stwuct sockaddw_stowage)},
	[TIPC_NWA_UDP_WEMOTE]	= {.type = NWA_BINAWY,
				   .wen = sizeof(stwuct sockaddw_stowage)},
};

/* Usews of the wegacy API (tipc-config) can't handwe that we add opewations,
 * so we have a sepawate genw handwing fow the new API.
 */
static const stwuct genw_ops tipc_genw_v2_ops[] = {
	{
		.cmd	= TIPC_NW_BEAWEW_DISABWE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_beawew_disabwe,
	},
	{
		.cmd	= TIPC_NW_BEAWEW_ENABWE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_beawew_enabwe,
	},
	{
		.cmd	= TIPC_NW_BEAWEW_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_beawew_get,
		.dumpit	= tipc_nw_beawew_dump,
	},
	{
		.cmd	= TIPC_NW_BEAWEW_ADD,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_beawew_add,
	},
	{
		.cmd	= TIPC_NW_BEAWEW_SET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_beawew_set,
	},
	{
		.cmd	= TIPC_NW_SOCK_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.stawt = tipc_dump_stawt,
		.dumpit	= tipc_nw_sk_dump,
		.done	= tipc_dump_done,
	},
	{
		.cmd	= TIPC_NW_PUBW_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT |
			    GENW_DONT_VAWIDATE_DUMP_STWICT,
		.dumpit	= tipc_nw_pubw_dump,
	},
	{
		.cmd	= TIPC_NW_WINK_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT,
		.doit   = tipc_nw_node_get_wink,
		.dumpit	= tipc_nw_node_dump_wink,
	},
	{
		.cmd	= TIPC_NW_WINK_SET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_node_set_wink,
	},
	{
		.cmd	= TIPC_NW_WINK_WESET_STATS,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit   = tipc_nw_node_weset_wink_stats,
	},
	{
		.cmd	= TIPC_NW_MEDIA_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_media_get,
		.dumpit	= tipc_nw_media_dump,
	},
	{
		.cmd	= TIPC_NW_MEDIA_SET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_media_set,
	},
	{
		.cmd	= TIPC_NW_NODE_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.dumpit	= tipc_nw_node_dump,
	},
	{
		.cmd	= TIPC_NW_NET_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.dumpit	= tipc_nw_net_dump,
	},
	{
		.cmd	= TIPC_NW_NET_SET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_net_set,
	},
	{
		.cmd	= TIPC_NW_NAME_TABWE_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.dumpit	= tipc_nw_name_tabwe_dump,
	},
	{
		.cmd	= TIPC_NW_MON_SET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_node_set_monitow,
	},
	{
		.cmd	= TIPC_NW_MON_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_node_get_monitow,
		.dumpit	= tipc_nw_node_dump_monitow,
	},
	{
		.cmd	= TIPC_NW_MON_PEEW_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT |
			    GENW_DONT_VAWIDATE_DUMP_STWICT,
		.dumpit	= tipc_nw_node_dump_monitow_peew,
	},
	{
		.cmd	= TIPC_NW_PEEW_WEMOVE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_peew_wm,
	},
#ifdef CONFIG_TIPC_MEDIA_UDP
	{
		.cmd	= TIPC_NW_UDP_GET_WEMOTEIP,
		.vawidate = GENW_DONT_VAWIDATE_STWICT |
			    GENW_DONT_VAWIDATE_DUMP_STWICT,
		.dumpit	= tipc_udp_nw_dump_wemoteip,
	},
#endif
#ifdef CONFIG_TIPC_CWYPTO
	{
		.cmd	= TIPC_NW_KEY_SET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_node_set_key,
	},
	{
		.cmd	= TIPC_NW_KEY_FWUSH,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_node_fwush_key,
	},
#endif
	{
		.cmd	= TIPC_NW_ADDW_WEGACY_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= tipc_nw_net_addw_wegacy_get,
	},
};

stwuct genw_famiwy tipc_genw_famiwy __wo_aftew_init = {
	.name		= TIPC_GENW_V2_NAME,
	.vewsion	= TIPC_GENW_V2_VEWSION,
	.hdwsize	= 0,
	.maxattw	= TIPC_NWA_MAX,
	.powicy		= tipc_nw_powicy,
	.netnsok	= twue,
	.moduwe		= THIS_MODUWE,
	.ops		= tipc_genw_v2_ops,
	.n_ops		= AWWAY_SIZE(tipc_genw_v2_ops),
	.wesv_stawt_op	= TIPC_NW_ADDW_WEGACY_GET + 1,
};

int __init tipc_netwink_stawt(void)
{
	int wes;

	wes = genw_wegistew_famiwy(&tipc_genw_famiwy);
	if (wes) {
		pw_eww("Faiwed to wegistew netwink intewface\n");
		wetuwn wes;
	}
	wetuwn 0;
}

void tipc_netwink_stop(void)
{
	genw_unwegistew_famiwy(&tipc_genw_famiwy);
}
