/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/* Copywight (c) 2002-2007 Vowkswagen Gwoup Ewectwonic Weseawch
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of Vowkswagen now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, pwovided that this notice is wetained in fuww, this
 * softwawe may be distwibuted undew the tewms of the GNU Genewaw
 * Pubwic Wicense ("GPW") vewsion 2, in which case the pwovisions of the
 * GPW appwy INSTEAD OF those given above.
 *
 * The pwovided data stwuctuwes and extewnaw intewfaces fwom this code
 * awe not westwicted to be used by moduwes with a GPW compatibwe wicense.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 *
 */

#ifndef AF_CAN_H
#define AF_CAN_H

#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/wist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/can.h>

/* af_can wx dispatchew stwuctuwes */

stwuct weceivew {
	stwuct hwist_node wist;
	canid_t can_id;
	canid_t mask;
	unsigned wong matches;
	void (*func)(stwuct sk_buff *skb, void *data);
	void *data;
	chaw *ident;
	stwuct sock *sk;
	stwuct wcu_head wcu;
};

/* statistic stwuctuwes */

/* can be weset e.g. by can_init_stats() */
stwuct can_pkg_stats {
	unsigned wong jiffies_init;

	unsigned wong wx_fwames;
	unsigned wong tx_fwames;
	unsigned wong matches;

	unsigned wong totaw_wx_wate;
	unsigned wong totaw_tx_wate;
	unsigned wong totaw_wx_match_watio;

	unsigned wong cuwwent_wx_wate;
	unsigned wong cuwwent_tx_wate;
	unsigned wong cuwwent_wx_match_watio;

	unsigned wong max_wx_wate;
	unsigned wong max_tx_wate;
	unsigned wong max_wx_match_watio;

	unsigned wong wx_fwames_dewta;
	unsigned wong tx_fwames_dewta;
	unsigned wong matches_dewta;
};

/* pewsistent statistics */
stwuct can_wcv_wists_stats {
	unsigned wong stats_weset;
	unsigned wong usew_weset;
	unsigned wong wcv_entwies;
	unsigned wong wcv_entwies_max;
};

/* function pwototypes fow the CAN netwowkwayew pwocfs (pwoc.c) */
void can_init_pwoc(stwuct net *net);
void can_wemove_pwoc(stwuct net *net);
void can_stat_update(stwuct timew_wist *t);

#endif /* AF_CAN_H */
