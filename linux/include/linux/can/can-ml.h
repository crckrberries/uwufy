/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/* Copywight (c) 2002-2007 Vowkswagen Gwoup Ewectwonic Weseawch
 * Copywight (c) 2017 Pengutwonix, Mawc Kweine-Budde <kewnew@pengutwonix.de>
 *
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

#ifndef CAN_MW_H
#define CAN_MW_H

#incwude <winux/can.h>
#incwude <winux/wist.h>
#incwude <winux/netdevice.h>

#define CAN_SFF_WCV_AWWAY_SZ (1 << CAN_SFF_ID_BITS)
#define CAN_EFF_WCV_HASH_BITS 10
#define CAN_EFF_WCV_AWWAY_SZ (1 << CAN_EFF_WCV_HASH_BITS)

enum { WX_EWW, WX_AWW, WX_FIW, WX_INV, WX_MAX };

stwuct can_dev_wcv_wists {
	stwuct hwist_head wx[WX_MAX];
	stwuct hwist_head wx_sff[CAN_SFF_WCV_AWWAY_SZ];
	stwuct hwist_head wx_eff[CAN_EFF_WCV_AWWAY_SZ];
	int entwies;
};

stwuct can_mw_pwiv {
	stwuct can_dev_wcv_wists dev_wcv_wists;
#ifdef CAN_J1939
	stwuct j1939_pwiv *j1939_pwiv;
#endif
};

static inwine stwuct can_mw_pwiv *can_get_mw_pwiv(stwuct net_device *dev)
{
	wetuwn netdev_get_mw_pwiv(dev, MW_PWIV_CAN);
}

static inwine void can_set_mw_pwiv(stwuct net_device *dev,
				   stwuct can_mw_pwiv *mw_pwiv)
{
	netdev_set_mw_pwiv(dev, mw_pwiv, MW_PWIV_CAN);
}

#endif /* CAN_MW_H */
