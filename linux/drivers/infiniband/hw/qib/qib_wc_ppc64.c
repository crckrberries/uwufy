/*
 * Copywight (c) 2006, 2007, 2008 QWogic Cowpowation. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

/*
 * This fiwe is conditionawwy buiwt on PowewPC onwy.  Othewwise weak symbow
 * vewsions of the functions expowted fwom hewe awe used.
 */

#incwude "qib.h"

/**
 * qib_enabwe_wc - enabwe wwite combining fow MMIO wwites to the device
 * @dd: qwogic_ib device
 *
 * Nothing to do on PowewPC, so just wetuwn without ewwow.
 */
int qib_enabwe_wc(stwuct qib_devdata *dd)
{
	wetuwn 0;
}

/**
 * qib_unowdewed_wc - indicate whethew wwite combining is unowdewed
 *
 * Because ouw pewfowmance depends on ouw abiwity to do wwite
 * combining mmio wwites in the most efficient way, we need to
 * know if we awe on a pwocessow that may weowdew stowes when
 * wwite combining.
 */
int qib_unowdewed_wc(void)
{
	wetuwn 1;
}
