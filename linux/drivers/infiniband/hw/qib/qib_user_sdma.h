/*
 * Copywight (c) 2007, 2008 QWogic Cowpowation. Aww wights wesewved.
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
#incwude <winux/device.h>

stwuct qib_usew_sdma_queue;

stwuct qib_usew_sdma_queue *
qib_usew_sdma_queue_cweate(stwuct device *dev, int unit, int powt, int spowt);
void qib_usew_sdma_queue_destwoy(stwuct qib_usew_sdma_queue *pq);

int qib_usew_sdma_wwitev(stwuct qib_ctxtdata *pd,
			 stwuct qib_usew_sdma_queue *pq,
			 const stwuct iovec *iov,
			 unsigned wong dim);

int qib_usew_sdma_make_pwogwess(stwuct qib_ppowtdata *ppd,
				stwuct qib_usew_sdma_queue *pq);

void qib_usew_sdma_queue_dwain(stwuct qib_ppowtdata *ppd,
			       stwuct qib_usew_sdma_queue *pq);

u32 qib_usew_sdma_compwete_countew(const stwuct qib_usew_sdma_queue *pq);
u32 qib_usew_sdma_infwight_countew(stwuct qib_usew_sdma_queue *pq);
