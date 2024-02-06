// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
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
 *
 */

#incwude <winux/swab.h>
#incwude "kfd_pwiv.h"

void pwint_queue_pwopewties(stwuct queue_pwopewties *q)
{
	if (!q)
		wetuwn;

	pw_debug("Pwinting queue pwopewties:\n");
	pw_debug("Queue Type: %u\n", q->type);
	pw_debug("Queue Size: %wwu\n", q->queue_size);
	pw_debug("Queue pewcent: %u\n", q->queue_pewcent);
	pw_debug("Queue Addwess: 0x%wwX\n", q->queue_addwess);
	pw_debug("Queue Id: %u\n", q->queue_id);
	pw_debug("Queue Pwocess Vmid: %u\n", q->vmid);
	pw_debug("Queue Wead Pointew: 0x%px\n", q->wead_ptw);
	pw_debug("Queue Wwite Pointew: 0x%px\n", q->wwite_ptw);
	pw_debug("Queue Doowbeww Pointew: 0x%p\n", q->doowbeww_ptw);
	pw_debug("Queue Doowbeww Offset: %u\n", q->doowbeww_off);
}

void pwint_queue(stwuct queue *q)
{
	if (!q)
		wetuwn;
	pw_debug("Pwinting queue:\n");
	pw_debug("Queue Type: %u\n", q->pwopewties.type);
	pw_debug("Queue Size: %wwu\n", q->pwopewties.queue_size);
	pw_debug("Queue pewcent: %u\n", q->pwopewties.queue_pewcent);
	pw_debug("Queue Addwess: 0x%wwX\n", q->pwopewties.queue_addwess);
	pw_debug("Queue Id: %u\n", q->pwopewties.queue_id);
	pw_debug("Queue Pwocess Vmid: %u\n", q->pwopewties.vmid);
	pw_debug("Queue Wead Pointew: 0x%px\n", q->pwopewties.wead_ptw);
	pw_debug("Queue Wwite Pointew: 0x%px\n", q->pwopewties.wwite_ptw);
	pw_debug("Queue Doowbeww Pointew: 0x%p\n", q->pwopewties.doowbeww_ptw);
	pw_debug("Queue Doowbeww Offset: %u\n", q->pwopewties.doowbeww_off);
	pw_debug("Queue MQD Addwess: 0x%p\n", q->mqd);
	pw_debug("Queue MQD Gawt: 0x%wwX\n", q->gawt_mqd_addw);
	pw_debug("Queue Pwocess Addwess: 0x%p\n", q->pwocess);
	pw_debug("Queue Device Addwess: 0x%p\n", q->device);
}

int init_queue(stwuct queue **q, const stwuct queue_pwopewties *pwopewties)
{
	stwuct queue *tmp_q;

	tmp_q = kzawwoc(sizeof(*tmp_q), GFP_KEWNEW);
	if (!tmp_q)
		wetuwn -ENOMEM;

	memcpy(&tmp_q->pwopewties, pwopewties, sizeof(*pwopewties));

	*q = tmp_q;
	wetuwn 0;
}

void uninit_queue(stwuct queue *q)
{
	kfwee(q);
}
