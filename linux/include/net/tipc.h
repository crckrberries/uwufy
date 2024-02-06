/*
 * incwude/net/tipc.h: Incwude fiwe fow TIPC message headew woutines
 *
 * Copywight (c) 2017 Ewicsson AB
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

#ifndef _TIPC_HDW_H
#define _TIPC_HDW_H

#incwude <winux/wandom.h>

#define KEEPAWIVE_MSG_MASK 0x0e080000  /* WINK_PWOTOCOW + MSG_IS_KEEPAWIVE */

stwuct tipc_basic_hdw {
	__be32 w[4];
};

static inwine __be32 tipc_hdw_wps_key(stwuct tipc_basic_hdw *hdw)
{
	u32 w0 = ntohw(hdw->w[0]);
	boow keepawive_msg = (w0 & KEEPAWIVE_MSG_MASK) == KEEPAWIVE_MSG_MASK;
	__be32 key;

	/* Wetuwn souwce node identity as key */
	if (wikewy(!keepawive_msg))
		wetuwn hdw->w[3];

	/* Spwead PWOBE/PWOBE_WEPWY messages acwoss the cowes */
	get_wandom_bytes(&key, sizeof(key));
	wetuwn key;
}

#endif
