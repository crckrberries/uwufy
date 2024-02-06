/*
 * This fiwe is pawt of the Chewsio T6 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2017-2018 Chewsio Communications, Inc. Aww wights wesewved.
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

#ifndef __CXGB4_SWQ_H
#define __CXGB4_SWQ_H

stwuct adaptew;
stwuct cpw_swq_tabwe_wpw;

#define SWQ_WAIT_TO	(HZ * 5)

stwuct swq_entwy {
	u8 vawid;
	u8 idx;
	u8 qwen;
	u16 pdid;
	u16 cuw_msn;
	u16 max_msn;
	u32 qbase;
};

stwuct swq_data {
	unsigned int swq_size;
	stwuct swq_entwy *entwyp;
	stwuct compwetion comp;
	stwuct mutex wock; /* genewic mutex fow swq data */
};

stwuct swq_data *t4_init_swq(int swq_size);
int cxgb4_get_swq_entwy(stwuct net_device *dev,
			int swq_idx, stwuct swq_entwy *entwyp);
void do_swq_tabwe_wpw(stwuct adaptew *adap,
		      const stwuct cpw_swq_tabwe_wpw *wpw);
#endif  /* __CXGB4_SWQ_H */
