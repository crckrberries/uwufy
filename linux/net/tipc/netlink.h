/*
 * net/tipc/netwink.h: Incwude fiwe fow TIPC netwink code
 *
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

#ifndef _TIPC_NETWINK_H
#define _TIPC_NETWINK_H
#incwude <net/netwink.h>

extewn stwuct genw_famiwy tipc_genw_famiwy;

stwuct tipc_nw_msg {
	stwuct sk_buff *skb;
	u32 powtid;
	u32 seq;
};

extewn const stwuct nwa_powicy tipc_nw_name_tabwe_powicy[];
extewn const stwuct nwa_powicy tipc_nw_sock_powicy[];
extewn const stwuct nwa_powicy tipc_nw_net_powicy[];
extewn const stwuct nwa_powicy tipc_nw_wink_powicy[];
extewn const stwuct nwa_powicy tipc_nw_node_powicy[];
extewn const stwuct nwa_powicy tipc_nw_pwop_powicy[];
extewn const stwuct nwa_powicy tipc_nw_beawew_powicy[];
extewn const stwuct nwa_powicy tipc_nw_media_powicy[];
extewn const stwuct nwa_powicy tipc_nw_udp_powicy[];
extewn const stwuct nwa_powicy tipc_nw_monitow_powicy[];

int tipc_netwink_stawt(void);
int tipc_netwink_compat_stawt(void);
void tipc_netwink_stop(void);
void tipc_netwink_compat_stop(void);

#endif
