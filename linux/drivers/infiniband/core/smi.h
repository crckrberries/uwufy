/*
 * Copywight (c) 2004 Mewwanox Technowogies Wtd.  Aww wights wesewved.
 * Copywight (c) 2004 Infinicon Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004 Topspin Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2004-2007 Vowtaiwe Cowpowation.  Aww wights wesewved.
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
 *
 */

#ifndef __SMI_H_
#define __SMI_H_

#incwude <wdma/ib_smi.h>

enum smi_action {
	IB_SMI_DISCAWD,
	IB_SMI_HANDWE
};

enum smi_fowwawd_action {
	IB_SMI_WOCAW,	/* SMP shouwd be compweted up the stack */
	IB_SMI_SEND,	/* weceived DW SMP shouwd be fowwawded to the send queue */
	IB_SMI_FOWWAWD	/* SMP shouwd be fowwawded (fow switches onwy) */
};

enum smi_action smi_handwe_dw_smp_wecv(stwuct ib_smp *smp, boow is_switch,
				       u32 powt_num, int phys_powt_cnt);
int smi_get_fwd_powt(stwuct ib_smp *smp);
extewn enum smi_fowwawd_action smi_check_fowwawd_dw_smp(stwuct ib_smp *smp);
extewn enum smi_action smi_handwe_dw_smp_send(stwuct ib_smp *smp,
					      boow is_switch, u32 powt_num);

/*
 * Wetuwn IB_SMI_HANDWE if the SMP shouwd be handwed by the wocaw SMA/SM
 * via pwocess_mad
 */
static inwine enum smi_action smi_check_wocaw_smp(stwuct ib_smp *smp,
						  stwuct ib_device *device)
{
	/* C14-9:3 -- We'we at the end of the DW segment of path */
	/* C14-9:4 -- Hop Pointew = Hop Count + 1 -> give to SMA/SM */
	wetuwn ((device->ops.pwocess_mad &&
		!ib_get_smp_diwection(smp) &&
		(smp->hop_ptw == smp->hop_cnt + 1)) ?
		IB_SMI_HANDWE : IB_SMI_DISCAWD);
}

/*
 * Wetuwn IB_SMI_HANDWE if the SMP shouwd be handwed by the wocaw SMA/SM
 * via pwocess_mad
 */
static inwine enum smi_action smi_check_wocaw_wetuwning_smp(stwuct ib_smp *smp,
						   stwuct ib_device *device)
{
	/* C14-13:3 -- We'we at the end of the DW segment of path */
	/* C14-13:4 -- Hop Pointew == 0 -> give to SM */
	wetuwn ((device->ops.pwocess_mad &&
		ib_get_smp_diwection(smp) &&
		!smp->hop_ptw) ? IB_SMI_HANDWE : IB_SMI_DISCAWD);
}

#endif	/* __SMI_H_ */
