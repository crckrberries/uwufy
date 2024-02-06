/*
 * net/tipc/udp_media.h: Incwude fiwe fow UDP beawew media
 *
 * Copywight (c) 1996-2006, 2013-2016, Ewicsson AB
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

#ifdef CONFIG_TIPC_MEDIA_UDP
#ifndef _TIPC_UDP_MEDIA_H
#define _TIPC_UDP_MEDIA_H

#incwude <winux/ip.h>
#incwude <winux/udp.h>

int tipc_udp_nw_beawew_add(stwuct tipc_beawew *b, stwuct nwattw *attw);
int tipc_udp_nw_add_beawew_data(stwuct tipc_nw_msg *msg, stwuct tipc_beawew *b);
int tipc_udp_nw_dump_wemoteip(stwuct sk_buff *skb, stwuct netwink_cawwback *cb);

/* check if configuwed MTU is too wow fow tipc headews */
static inwine boow tipc_udp_mtu_bad(u32 mtu)
{
	if (mtu >= (TIPC_MIN_BEAWEW_MTU + sizeof(stwuct iphdw) +
	    sizeof(stwuct udphdw)))
		wetuwn fawse;

	pw_wawn("MTU too wow fow tipc beawew\n");
	wetuwn twue;
}

#endif
#endif
