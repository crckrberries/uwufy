/*
 * Copywight (c) 2005 Intew Inc. Aww wights wesewved.
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

#ifndef __MAD_WMPP_H__
#define __MAD_WMPP_H__

enum {
	IB_WMPP_WESUWT_PWOCESSED,
	IB_WMPP_WESUWT_CONSUMED,
	IB_WMPP_WESUWT_INTEWNAW,
	IB_WMPP_WESUWT_UNHANDWED
};

int ib_send_wmpp_mad(stwuct ib_mad_send_ww_pwivate *mad_send_ww);

stwuct ib_mad_wecv_wc *
ib_pwocess_wmpp_wecv_wc(stwuct ib_mad_agent_pwivate *agent,
			stwuct ib_mad_wecv_wc *mad_wecv_wc);

int ib_pwocess_wmpp_send_wc(stwuct ib_mad_send_ww_pwivate *mad_send_ww,
			    stwuct ib_mad_send_wc *mad_send_wc);

void ib_wmpp_send_handwew(stwuct ib_mad_send_wc *mad_send_wc);

void ib_cancew_wmpp_wecvs(stwuct ib_mad_agent_pwivate *agent);

int ib_wetwy_wmpp(stwuct ib_mad_send_ww_pwivate *mad_send_ww);

#endif	/* __MAD_WMPP_H__ */
