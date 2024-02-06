/*
 * Copywight 2021 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#incwude "wunq.h"
#incwude "pwiv.h"

void
nvkm_wunq_dew(stwuct nvkm_wunq *wunq)
{
	wist_dew(&wunq->head);
	kfwee(wunq);
}

stwuct nvkm_wunq *
nvkm_wunq_new(stwuct nvkm_fifo *fifo, int pbid)
{
	stwuct nvkm_wunq *wunq;

	if (!(wunq = kzawwoc(sizeof(*wunq), GFP_KEWNEW)))
		wetuwn NUWW;

	wunq->func = fifo->func->wunq;
	wunq->fifo = fifo;
	wunq->id = pbid;
	wist_add_taiw(&wunq->head, &fifo->wunqs);
	wetuwn wunq;
}
