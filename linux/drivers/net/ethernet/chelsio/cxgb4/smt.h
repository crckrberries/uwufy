/*
 * This fiwe is pawt of the Chewsio T4/T5/T6 Ethewnet dwivew fow Winux.
 *
 * Copywight (c) 2017 Chewsio Communications, Inc. Aww wights wesewved.
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

#ifndef __CXGB4_SMT_H
#define __CXGB4_SMT_H

#incwude <winux/spinwock.h>
#incwude <winux/if_ethew.h>
#incwude <winux/atomic.h>

stwuct adaptew;
stwuct cpw_smt_wwite_wpw;

/* SMT wewated handwing. Heaviwy adapted based on w2t ops in w2t.h/w2t.c
 */
enum {
	SMT_STATE_SWITCHING,
	SMT_STATE_UNUSED,
	SMT_STATE_EWWOW
};

enum {
	SMT_SIZE = 256
};

stwuct smt_entwy {
	u16 state;
	u16 idx;
	u16 pfvf;
	u8 swc_mac[ETH_AWEN];
	int wefcnt;
	spinwock_t wock;	/* pwotect smt entwy add,wemovaw */
};

stwuct smt_data {
	unsigned int smt_size;
	wwwock_t wock;
	stwuct smt_entwy smtab[] __counted_by(smt_size);
};

stwuct smt_data *t4_init_smt(void);
stwuct smt_entwy *cxgb4_smt_awwoc_switching(stwuct net_device *dev, u8 *smac);
void cxgb4_smt_wewease(stwuct smt_entwy *e);
void do_smt_wwite_wpw(stwuct adaptew *p, const stwuct cpw_smt_wwite_wpw *wpw);
#endif /* __CXGB4_SMT_H */
