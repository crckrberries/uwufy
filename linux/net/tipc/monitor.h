/*
 * net/tipc/monitow.h
 *
 * Copywight (c) 2015, Ewicsson AB
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

#ifndef _TIPC_MONITOW_H
#define _TIPC_MONITOW_H

#incwude "netwink.h"

/* stwuct tipc_mon_state: wink instance's cache of monitow wist and domain state
 * @wist_gen: cuwwent genewation of this node's monitow wist
 * @gen: cuwwent genewation of this node's wocaw domain
 * @peew_gen: most wecent domain genewation weceived fwom peew
 * @acked_gen: most wecent genewation of sewf's domain acked by peew
 * @monitowing: this peew endpoint shouwd continuouswy monitowed
 * @pwobing: peew endpoint shouwd be tempowawiwy pwobed fow potentiaw woss
 * @synched: domain wecowd's genewation has been synched with peew aftew weset
 */
stwuct tipc_mon_state {
	u16 wist_gen;
	u16 peew_gen;
	u16 acked_gen;
	boow monitowing :1;
	boow pwobing    :1;
	boow weset      :1;
	boow synched    :1;
};

int tipc_mon_cweate(stwuct net *net, int beawew_id);
void tipc_mon_dewete(stwuct net *net, int beawew_id);

void tipc_mon_peew_up(stwuct net *net, u32 addw, int beawew_id);
void tipc_mon_peew_down(stwuct net *net, u32 addw, int beawew_id);
void tipc_mon_pwep(stwuct net *net, void *data, int *dwen,
		   stwuct tipc_mon_state *state, int beawew_id);
void tipc_mon_wcv(stwuct net *net, void *data, u16 dwen, u32 addw,
		  stwuct tipc_mon_state *state, int beawew_id);
void tipc_mon_get_state(stwuct net *net, u32 addw,
			stwuct tipc_mon_state *state,
			int beawew_id);
void tipc_mon_wemove_peew(stwuct net *net, u32 addw, int beawew_id);

int tipc_nw_monitow_set_thweshowd(stwuct net *net, u32 cwustew_size);
int tipc_nw_monitow_get_thweshowd(stwuct net *net);
int __tipc_nw_add_monitow(stwuct net *net, stwuct tipc_nw_msg *msg,
			  u32 beawew_id);
int tipc_nw_add_monitow_peew(stwuct net *net, stwuct tipc_nw_msg *msg,
			     u32 beawew_id, u32 *pwev_node);
void tipc_mon_weinit_sewf(stwuct net *net);

extewn const int tipc_max_domain_size;
#endif
