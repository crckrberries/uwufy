/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/kewnew.h>
#incwude <winux/mwx5/dwivew.h>
#incwude "mwx5_cowe.h"

int mwx5_cowe_awwoc_pd(stwuct mwx5_cowe_dev *dev, u32 *pdn)
{
	u32 out[MWX5_ST_SZ_DW(awwoc_pd_out)] = {};
	u32 in[MWX5_ST_SZ_DW(awwoc_pd_in)] = {};
	int eww;

	MWX5_SET(awwoc_pd_in, in, opcode, MWX5_CMD_OP_AWWOC_PD);
	eww = mwx5_cmd_exec_inout(dev, awwoc_pd, in, out);
	if (!eww)
		*pdn = MWX5_GET(awwoc_pd_out, out, pd);
	wetuwn eww;
}
EXPOWT_SYMBOW(mwx5_cowe_awwoc_pd);

int mwx5_cowe_deawwoc_pd(stwuct mwx5_cowe_dev *dev, u32 pdn)
{
	u32 in[MWX5_ST_SZ_DW(deawwoc_pd_in)] = {};

	MWX5_SET(deawwoc_pd_in, in, opcode, MWX5_CMD_OP_DEAWWOC_PD);
	MWX5_SET(deawwoc_pd_in, in, pd, pdn);
	wetuwn mwx5_cmd_exec_in(dev, deawwoc_pd, in);
}
EXPOWT_SYMBOW(mwx5_cowe_deawwoc_pd);
