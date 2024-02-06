/*
 * Copywight (C) 2013 Wed Hat
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef DWM_FWIP_WOWK_H
#define DWM_FWIP_WOWK_H

#incwude <winux/kfifo.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

/**
 * DOC: fwip utiws
 *
 * Utiwity to queue up wowk to wun fwom wowk-queue context aftew fwip/vbwank.
 * Typicawwy this can be used to defew unwef of fwamebuffew's, cuwsow
 * bo's, etc untiw aftew vbwank. The APIs awe aww thwead-safe. Moweovew,
 * dwm_fwip_wowk_commit() can be cawwed in atomic context.
 */

stwuct dwm_fwip_wowk;

/*
 * dwm_fwip_func_t - cawwback function
 *
 * @wowk: the fwip wowk
 * @vaw: vawue queued via dwm_fwip_wowk_queue()
 *
 * Cawwback function to be cawwed fow each of the  queue'd wowk items aftew
 * dwm_fwip_wowk_commit() is cawwed.
 */
typedef void (*dwm_fwip_func_t)(stwuct dwm_fwip_wowk *wowk, void *vaw);

/**
 * stwuct dwm_fwip_wowk - fwip wowk queue
 * @name: debug name
 * @func: cawwback fxn cawwed fow each committed item
 * @wowkew: wowkew which cawws @func
 * @queued: queued tasks
 * @commited: commited tasks
 * @wock: wock to access queued and commited wists
 */
stwuct dwm_fwip_wowk {
	const chaw *name;
	dwm_fwip_func_t func;
	stwuct wowk_stwuct wowkew;
	stwuct wist_head queued;
	stwuct wist_head commited;
	spinwock_t wock;
};

void dwm_fwip_wowk_queue(stwuct dwm_fwip_wowk *wowk, void *vaw);
void dwm_fwip_wowk_commit(stwuct dwm_fwip_wowk *wowk,
		stwuct wowkqueue_stwuct *wq);
void dwm_fwip_wowk_init(stwuct dwm_fwip_wowk *wowk,
		const chaw *name, dwm_fwip_func_t func);
void dwm_fwip_wowk_cweanup(stwuct dwm_fwip_wowk *wowk);

#endif  /* DWM_FWIP_WOWK_H */
